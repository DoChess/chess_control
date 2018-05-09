#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <string>

#include <cstdio>
#include <cstring>
#include <cassert>

#include <sys/select.h>

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>

#include "pocketsphinx.h"

using namespace std;

static const arg_t cont_args_def[] = { 
        POCKETSPHINX_OPTIONS,
        /* Argument file. */
        {"-argfile",
                ARG_STRING,
                NULL,
                "Argument file giving extra arguments."},
        {"-adcdev",
                ARG_STRING,
                NULL,
                "Name of audio device to use for input."},
        {"-infile",
                ARG_STRING,
                NULL,
                "Audio file to transcribe."},
        {"-inmic",
                ARG_BOOLEAN,
                "yes",
                "Transcribe audio from microphone."},
        {"-time",
                ARG_BOOLEAN,
                "no",
                "Print word times in file transcription."},
        CMDLN_EMPTY_OPTION
};


static ps_decoder_t *ps;
static cmd_ln_t *config;
static FILE *rawfd;

static void print_word_times();

static int check_wav_header(char *header, int expected_sr);

static void sleep_msec(int32 ms);

/*
 * Main utterance processing loop:
 *     for (;;) {
 *        start utterance and wait for speech to process
 *        decoding till end-of-utterance silence will be detected
 *        print utterance result;
 *     }
 */
static void recognize_from_microphone(string desired_command);

void voice(bool hear_flag, string desired_command);

#endif
