#include "../include/voice.hpp"

using namespace std;

int voice(bool hear_flag, string desired_command)
{
	if(hear_flag) {
				char const *cfg;

				int argc=3;
				char *argv[3];
				argv[0] = "./testing_mic";
				argv[1] = "-argfile";
				argv[2] = "arguments.txt";

				config = cmd_ln_parse_r(NULL, cont_args_def, argc, argv, TRUE);

				/* Handle argument file as -argfile. */
				if (config && (cfg = cmd_ln_str_r(config, "-argfile")) != NULL) {
								config = cmd_ln_parse_file_r(config, cont_args_def, cfg, FALSE);
				}

				ps_default_search_args(config);
				ps = ps_init(config);
				if (ps == NULL) {
								cmd_ln_free_r(config);
								return 1;
				}

				E_INFO("%s COMPILED ON: %s, AT: %s\n\n", argv[0], __DATE__, __TIME__);

				if (cmd_ln_str_r(config, "-infile") != NULL) {
								// nothing
				} else if (cmd_ln_boolean_r(config, "-inmic")) {
								recognize_from_microphone(desired_command);
				}

				ps_free(ps);
				cmd_ln_free_r(config);

				return 0;
	}
}
