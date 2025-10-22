#python src/main.py
from utility import *
from game import Game

if __name__ == "__main__":
    
    os.system('cls')
    game = Game()

    while True:
        if game.state == CLOSEGAME:
            break 
        game.handle_events()
        game.update()
        game.render()
    pygame.quit()
    sys.exit()

