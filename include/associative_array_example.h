// loop_status_t command_start(game_t *game, char *input);
// loop_status_t command_turn(game_t *game, char *input);
// loop_status_t command_begin(game_t *game, char *input);
// loop_status_t command_board(game_t *game, char *input);
// loop_status_t command_info(game_t *game, char *input);
// loop_status_t command_end(game_t *game, char *input);
// loop_status_t command_about(game_t *game, char *input);

// static const struct {
//     char *command;
//     loop_status_t (*command_func)(game_t *game, char *input);
// } COMMANDS_TO_FUNCS[] = {
//     {"START", command_start},
//     {"TURN", command_turn},
//     {"BEGIN", command_begin},
//     {"BOARD", command_board},
//     {"INFO", command_info},
//     {"ABOUT", command_about}
// };
// #define NB_COMMANDS sizeof(COMMANDS_TO_FUNCS) / sizeof(COMMANDS_TO_FUNCS[0])