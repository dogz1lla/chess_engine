#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ws.h>
#include "bitboard.h"
#include "engine_context.h"
#include "msg_protocol.h"

// TODO: move to separate file
int algebraic_to_index(char file, char rank) {
    int f = file - 'a';     // a–h  -> 0–7
    int r = rank - '1';     // 1–8  -> 0–7
    return r * 8 + f;       // your board indexing
}


/**
 * @brief This function is called whenever a new connection is opened.
 * @param client Client connection.
 */
void onopen(ws_cli_conn_t client)
{
    char *cli;
    cli = ws_getaddress(client);
    printf("Connection opened, addr: %s\n", cli);
}

/**
 * @brief This function is called whenever a connection is closed.
 * @param client Client connection.
 */
void onclose(ws_cli_conn_t client)
{
    char *cli;
    cli = ws_getaddress(client);
    printf("Connection closed, addr: %s\n", cli);
}

/**
 * @brief Message events goes here.
 * @param client Client connection.
 * @param msg    Message content.
 * @param size   Message size.
 * @param type   Message type.
 */
void onmessage(ws_cli_conn_t client,
    const unsigned char *msg, uint64_t size, int type)
{
    char *cli;
    cli = ws_getaddress(client);
    printf("I receive a message: %s (%zu), from: %s\n", msg,
        size, cli);

    sleep(2);
    ws_sendframe_txt(client, "hello");
    sleep(2);
    ws_sendframe_txt(client, "world");
    /* TODO
     * - [ ] read the msg into a c str;
     * - [ ] parse the msg;
     * - [ ] if move -> make move;
     * - [ ] if attack -> make attack;
     * - [ ] eval and find the engine's next move;
     * - [ ] update the board and send back to client to render;
     *
     *   how can i encode the msgs? i could use json but i dont want to depend on another third
     *   party library
     *   how about encoding through strings that contain words separated by spaces?
     *   Examples:
     *   'move white pawn e2e4'
     *   'take white pawn black pawn e2d3'
     *   'promote black pawn queen e2e1'
     *   etc.
     * */
    EngineContext *ctx = (EngineContext *)ws_get_server_context(client);
    print_bits(ctx->board->occupied, 0);

    char buffer[256];
    strncpy(buffer, (const char*)msg, size);
    buffer[size] = '\0';

    char *cmd = strtok(buffer, " ");
    if (!cmd) return;
    else printf("The message is of type: %s\n", cmd);

    if (strcmp(cmd, "m") == 0) {
        char *color = strtok(NULL, " ");
        char *piece = strtok(NULL, " ");
        char *move  = strtok(NULL, " "); // e2e4

        printf("Got a request to move %s %s (%s)\n", color, piece, move);
        int from = algebraic_to_index(move[0], move[1]);
        int to   = algebraic_to_index(move[2], move[3]);

        Move m = make_move_from_strings(color, piece, from, to);
        move_piece(ctx->board, &m);
        // send_state(client, &ctx->board);
    } else {
        printf("Error: message of type %s is not supported\n", cmd);
    }
    print_bits(ctx->board->occupied, 0);
}

int main(void)
{
    /*
     * Main loop, this function never* returns.
     *
     * *If the .thread_loop is != 0, a new thread is created
     * to handle new connections and ws_socket() becomes
     * non-blocking.
     */
    EngineContext *ctx = calloc(1, sizeof(EngineContext));
    Board *b = calloc(1, sizeof(Board));
    if (b == NULL) {
        printf("%s\n", "Board allocation failed.");
        return 1;
    }
    ctx->board = b;
    init_board(b);

    ws_socket(&(struct ws_server){
        /*
         * Bind host, such as:
         * localhost -> localhost/127.0.0.1
         * 0.0.0.0   -> global IPv4
         * ::        -> global IPv4+IPv6 (Dual stack)
         */
        .host = "localhost",
        .port = 8080,
        .thread_loop   = 0,
        .timeout_ms    = 1000,
        .evs.onopen    = &onopen,
        .evs.onclose   = &onclose,
        .evs.onmessage = &onmessage,
        .context = ctx
    });

    return (0);
}
