#include "../include/recognition.hpp"

using namespace std;

static void print_word_times()
{
  int frame_rate = cmd_ln_int32_r(config, "-frate");
  ps_seg_t *iter = ps_seg_iter(ps);
  while (iter != NULL) {
    int32 sf, ef, pprob;
    float conf;

    ps_seg_frames(iter, &sf, &ef);
    pprob = ps_seg_prob(iter, NULL, NULL, NULL);
    conf = logmath_exp(ps_get_logmath(ps), pprob);
    printf("%s %.3f %.3f %f\n", ps_seg_word(iter), ((float)sf / frame_rate),
        ((float) ef / frame_rate), conf);
    iter = ps_seg_next(iter);
  }
}

static int check_wav_header(char *header, int expected_sr)
{
  int sr;

  if (header[34] != 0x10) {
    E_ERROR("Input audio file has [%d] bits per sample instead of 16\n", header[34]);
    return 0;
  }
  if (header[20] != 0x1) {
    E_ERROR("Input audio file has compression [%d] and not required PCM\n", header[20]);
    return 0;
  }
  if (header[22] != 0x1) {
    E_ERROR("Input audio file has [%d] channels, expected single channel mono\n", header[22]);
    return 0;
  }
  sr = ((header[24] & 0xFF) | ((header[25] & 0xFF) << 8) | ((header[26] & 0xFF) << 16) | ((header[27] & 0xFF) << 24));
  if (sr != expected_sr) {
    E_ERROR("Input audio file has sample rate [%d], but decoder expects [%d]\n", sr, expected_sr);
    return 0;
  }
  return 1;
}

static void sleep_msec(int32 ms)
{
  /* ------------------- Unix ------------------ */
  struct timeval tmo;

  tmo.tv_sec = 0;
  tmo.tv_usec = ms * 1000;

  select(0, NULL, NULL, NULL, &tmo);
}

/*
 * Main utterance processing loop:
 *     for (;;) {
 *        start utterance and wait for speech to process
 *        decoding till end-of-utterance silence will be detected
 *        print utterance result;
 *     }
 */

// TODO send return when fail to match grammar
static string recognize_from_microphone(bool hear_flag, string desired_command)
{
  // Returns the value talked. !ERROR!->BAD word->GOOD
  string command = HEAR_ERROR;

  ad_rec_t *ad;
  int16 adbuf[2048];
  uint8 utt_started, in_speech;
  int32 k;
  char const *hyp;

  if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),
          (int) cmd_ln_float32_r(config,
            "-samprate"))) == NULL)
    E_FATAL("Failed to open audio device\n");
  if (ad_start_rec(ad) < 0)
    E_FATAL("Failed to start recording\n");

  if (ps_start_utt(ps) < 0)
    E_FATAL("Failed to start utterance\n");
  utt_started = FALSE;
  E_INFO("Ready....\n");

  // Control listening.
  while(hear_flag){
    if ((k = ad_read(ad, adbuf, 2048)) < 0){
      E_FATAL("Failed to read audio\n");
    }
    ps_process_raw(ps, adbuf, k, FALSE, FALSE);
    in_speech = ps_get_in_speech(ps);

    // If have someone talking and not statarted to hear. So start 
    // listening.
    if (in_speech && !utt_started) {
      utt_started = TRUE;
      E_INFO("Listening...\n");
      printf("Listening...\n");
    }

    // If no one is talking and is hearing. So stop it, and print the 
    // result.
    if (!in_speech && utt_started) {
      /* speech -> silence transition, time to start new utterance  */
      ps_end_utt(ps);
      hyp = ps_get_hyp(ps, NULL );
      if (hyp != NULL) {
        // Print the value recognized.
        //printf("%s\n", hyp);
        if(desired_command == HEAR_COMMAND){ 
          if(strcmp(hyp, CHESS_COMMAND.c_str())   &&
             strcmp(hyp, BEGIN_COMMAND.c_str())   &&
             strcmp(hyp, RESUME_COMMAND.c_str())  &&
             strcmp(hyp, REPEAT_COMMAND.c_str())    &&
             strcmp(hyp, MOVE_COMMAND.c_str())    &&
             strcmp(hyp, STOP_COMMAND.c_str())    &&
             strcmp(hyp, END_COMMAND.c_str())){
            command = hyp;
            printf("Understand command: %s\n", command.c_str());
            hear_flag = false;
          }
        } else if(!strcmp(hyp, desired_command.c_str())){ 
          command = hyp;
          printf("Understand command: %s\n", command.c_str());
          hear_flag = false;
        }
        fflush(stdout);
      }

      if (ps_start_utt(ps) < 0)
        E_FATAL("Failed to start utterance\n");
      utt_started = FALSE;
      E_INFO("Ready....\n");
      printf("Ready....\n");
    }
    sleep_msec(100);
  }
  ad_close(ad);
  return command;
}

string voice(bool hear_flag, string desired_command)
{
  string command="";
  if(hear_flag) {
    char const *cfg;

    int argc=3;
    char *argv[3];
    char argv0[14] = "./testing_mic";
    char argv1[9] = "-argfile";
    char argv2[14] = "arguments.txt";
    argv[0] = argv0;
    argv[1] = argv1;
    argv[2] = argv2;


    config = cmd_ln_parse_r(NULL, cont_args_def, argc, argv, TRUE);

    /* Handle argument file as -argfile. */
    if (config && (cfg = cmd_ln_str_r(config, "-argfile")) != NULL) {
      config = cmd_ln_parse_file_r(config, cont_args_def, cfg, FALSE);
    }

    ps_default_search_args(config);
    ps = ps_init(config);
    if (ps == NULL) {
      cmd_ln_free_r(config);
      exit(1);
    }

    E_INFO("%s COMPILED ON: %s, AT: %s\n\n", argv[0], __DATE__, __TIME__);

    if (cmd_ln_str_r(config, "-infile") != NULL) {
      // nothing
    } else if (cmd_ln_boolean_r(config, "-inmic")) {
      command = recognize_from_microphone(hear_flag, desired_command);
      if(command == HEAR_ERROR){
        printf("Error when runing recognize_from_microphone()!");
        exit(1);
      }
    }

    ps_free(ps);
    cmd_ln_free_r(config);
  }
  return command;
}

void hear_begin(bool hear_flag, string desired_command) {
	printf("Waiting for %s\n", BEGIN_COMMAND.c_str());
  hear_flag = true;
  desired_command = BEGIN_COMMAND;
  voice(hear_flag, desired_command);
}

// Removed from grammar/chess_grammar.jsgf, need to add | end game | if needed.
void hear_end(bool hear_flag, string desired_command) {
	printf("Waiting for %s\n", END_COMMAND.c_str());
  hear_flag = true;
  desired_command = END_COMMAND;
  voice(hear_flag, desired_command);
}

void hear_chess(bool hear_flag, string desired_command) {
	printf("Waiting for %s\n", CHESS_COMMAND.c_str());
  hear_flag = true;
  desired_command = CHESS_COMMAND;
  desired_command = voice(hear_flag, desired_command);
}

void hear_repeat(bool hear_flag, string desired_command) {
	printf("Waiting for %s\n", REPEAT_COMMAND.c_str());
  hear_flag = true;
  desired_command = REPEAT_COMMAND;
  desired_command = voice(hear_flag, desired_command);
}

void hear_move(bool hear_flag, string desired_command) {
	printf("Waiting for %s\n", MOVE_COMMAND.c_str());
  hear_flag = true;
  desired_command = MOVE_COMMAND;
  desired_command = voice(hear_flag, desired_command);
}

string hear_command(bool hear_flag, string desired_command) {
	printf("Waiting for %s\n", HEAR_COMMAND.c_str());
  hear_flag = true;
  desired_command = HEAR_COMMAND;
  desired_command = voice(hear_flag, desired_command);

  transform(desired_command.begin(), desired_command.end(), desired_command.begin(), ::toupper);

  return desired_command;
}

void hear_stop(bool hear_flag, string desired_command){
	printf("Waiting for %s\n", STOP_COMMAND.c_str());
  hear_flag = true;
  desired_command = STOP_COMMAND;
  voice(hear_flag, desired_command);
}

void hear_resume(bool hear_flag, string desired_command){
	printf("Waiting for %s\n", RESUME_COMMAND.c_str());
  hear_flag = true;
  desired_command = RESUME_COMMAND;
  voice(hear_flag, desired_command);
}
