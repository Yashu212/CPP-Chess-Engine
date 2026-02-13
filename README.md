# ♟️ CPP Chess Engine

A classical chess engine built from scratch in **C++**, implementing legal move generation, alpha-beta pruning, quiescence search, and heuristic-based evaluation.

This project demonstrates core search algorithms, state management, and performance-aware design used in traditional chess engines.

---

## 🚀 Features

- Full legal move generation
- Check detection
- Checkmate & stalemate detection
- Pawn promotion
- Alpha-beta pruning
- Quiescence search
- Piece-square table evaluation
- Mobility bonus
- Center control bonus
- Perft testing for correctness
- Playable via terminal interface

---

## 📁 Project Structure

```
board.cpp        - Board representation & move application
movegen.cpp      - Move generation (legal moves)
attack.cpp       - Attack detection logic
eval.cpp         - Position evaluation
search.cpp       - Alpha-beta search + quiescence
main.cpp         - CLI interface & perft mode
```

---

## 🧠 Engine Design

### Board Representation

- 8x8 2D character array
- Uppercase → White pieces
- Lowercase → Black pieces
- Move application with undo system

---

### Move Generation

- Pseudo-legal move generation per piece
- Legal filtering by:
  - Simulating move
  - Checking king safety
  - Undoing move

---

### Search Algorithm

- Minimax
- Alpha-beta pruning
- Quiescence search (prevents horizon effect)

---

### Evaluation Function

Evaluation considers:

- Material balance
- Piece-square tables
- Mobility bonus
- Center control bonus

---

## 🔍 Perft Validation

Perft testing validates correctness of move generation.

From starting position:

```
Depth 1 = 20
Depth 2 = 400
Depth 3 = 8902
Depth 4 = 197281
Depth 5 = 4865351
```

- Depth 1–4 match standard known perft values exactly.
- Depth 5 differs due to omission of castling and en passant rules.

---

## ⚙️ How To Run

### Prerequisites

Make sure `g++` compiler is installed on your system.

---

### Clone the Repository

```bash
git clone <repo_url>
cd <repo_name>
```

---

### Compile

```bash
g++ main.cpp board.cpp movegen.cpp attack.cpp eval.cpp search.cpp -o chess
```

---

### Run

```bash
./chess
```

---

## 🎮 Usage

You can choose:

- Play vs Engine
- Run Perft mode

---

### Playing Format

Moves are entered using coordinate notation:

```
e2e4
g1f3
```

Promotion example:

```
e7e8q
```

Type `quit` to exit the game.

---

## ⚠️ Current Limitations

- Castling not implemented
- En passant not implemented
- No opening book
- No endgame tablebases
- No UCI protocol support
- No time control management

---

## 🔮 Possible Future Improvements

- Add castling support
- Add en passant support
- Implement FEN parsing
- Add UCI protocol support
- Add transposition tables (Zobrist hashing)
- Use bitboard representation
- Add killer move & history heuristics
- Add null-move pruning
- Add opening book
- Add nodes-per-second reporting
- Evaluation tuning

---

## 👤 Author

**Yash Shukla**  
C++ | Backend | Systems Engineering
