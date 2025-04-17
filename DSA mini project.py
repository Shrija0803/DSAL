import tkinter as tk
import random

# Snakes and ladders positions
snakes = {16: 6, 47: 26, 49: 11, 56: 53, 62: 19, 64: 60, 87: 24, 93: 73, 95: 75, 98: 78}
ladders = {1: 38, 4: 14, 9: 31, 21: 42, 28: 84, 36: 44, 51: 67, 71: 91, 80: 100}

class SnakeLadderGame:
    def __init__(self, root):
        self.root = root
        self.root.title("Snake and Ladder Game")
        self.canvas = tk.Canvas(root, width=600, height=600, bg="#f0e6d6")
        self.canvas.pack()

        self.board = {}
        self.draw_board()
        self.draw_snakes_and_ladders()
        
        self.players = [0, 0]
        self.tokens = [self.canvas.create_oval(10, 550, 30, 570, fill="blue"),
                       self.canvas.create_oval(10, 520, 30, 540, fill="red")]
        
        self.turn = 0

        self.info = tk.Label(root, text="Player 1's Turn (Blue)", font=('Arial', 14))
        self.info.pack()

        self.roll_btn = tk.Button(root, text="🎲 Roll Dice", command=self.play_turn, font=('Arial', 14))
        self.roll_btn.pack()

        self.dice_label = tk.Label(root, text="", font=('Arial', 24))
        self.dice_label.pack(pady=10)

    def draw_board(self):
        size = 60
        num = 100
        for row in range(10):
            for col in range(10):
                x = col * size if row % 2 == 0 else (9 - col) * size
                y = row * size
                self.canvas.create_rectangle(x, y, x + size, y + size, fill="white", outline="black")
                self.canvas.create_text(x + 30, y + 30, text=str(num), font=("Arial", 10, "bold"))
                self.board[num] = (x + 10, y + 10)
                num -= 1

    def draw_snakes_and_ladders(self):
        # Draw ladders in green
        for start, end in ladders.items():
            x1, y1 = self.get_center(start)
            x2, y2 = self.get_center(end)
            self.canvas.create_line(x1, y1, x2, y2, fill="green", width=4, arrow=tk.LAST)

        # Draw snakes in red
        for start, end in snakes.items():
            x1, y1 = self.get_center(start)
            x2, y2 = self.get_center(end)
            self.canvas.create_line(x1, y1, x2, y2, fill="red", width=4, arrow=tk.LAST)

    def get_center(self, position):
        x, y = self.board[position]
        return (x + 10, y + 10)

    def get_coords(self, position):
        if position == 0:
            return (10, 550)
        return self.board[position]

    def move_token(self, player):
        x, y = self.get_coords(self.players[player])
        self.canvas.coords(self.tokens[player], x, y, x + 20, y + 20)

    def play_turn(self):
        dice = random.randint(1, 6)
        self.dice_label.config(text=f"🎲 {dice}")
        
        curr = self.players[self.turn]
        next_pos = curr + dice

        if next_pos > 100:
            next_pos = curr  # don't move

        msg = f"Player {self.turn + 1} rolled a {dice}"

        if next_pos in snakes:
            msg += f"\n🐍 Snake from {next_pos} to {snakes[next_pos]}"
            next_pos = snakes[next_pos]
        elif next_pos in ladders:
            msg += f"\n🪜 Ladder from {next_pos} to {ladders[next_pos]}"
            next_pos = ladders[next_pos]

        self.players[self.turn] = next_pos
        self.move_token(self.turn)

        if next_pos == 100:
            self.info.config(text=f"🏆 Player {self.turn + 1} wins!")
            self.roll_btn.config(state='disabled')
        else:
            self.turn = 1 - self.turn
            self.info.config(text=msg + f"\nPlayer {self.turn + 1}'s Turn")

# Run the game
root = tk.Tk()
game = SnakeLadderGame(root)
root.mainloop()
