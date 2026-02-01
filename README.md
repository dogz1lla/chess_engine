# To use the ws
- create a lib dir
- run `git clone https://github.com/Theldus/wsServer lib/wsServer`
- use `compile_ws.sh` to build

# To generate `compile_commands.json`
- install `bear`:
```
pacman -S bear
```
- run in the root of the project
```
bear -- make
```

# References
## Piece moves
- [move encoding](https://www.chessprogramming.org/Encoding_Moves)
- [sliding piece target squares bitboards](https://www.chessprogramming.org/Classical_Approach)
- [pawn attacks](https://www.chessprogramming.org/Pawn_Attacks_(Bitboards))
- [knight attacks/moves](https://www.chessprogramming.org/Knight_Pattern)
