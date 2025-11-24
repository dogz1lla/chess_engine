struct Board* init_board(void);
int load_position_from_fen(struct Board *b, char* fen);
char* get_piece_symbol(int piece_code);
void draw_board(struct Board *b);
