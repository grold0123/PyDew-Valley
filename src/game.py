from utility import *
from gameobjects import Object , GroupObject
class Game:

    def __init__(self):
        
        self.display = pygame.display.set_mode((WIDTH,HEIGHT));pygame.display.set_caption(GAMETITLE)    
        self.clock = pygame.time.Clock()
        self.state = STARTGAME
    
        self.test_group = GroupObject()

        self.test = Object(self.test_group)

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.state = CLOSEGAME

    def update(self):
        self.test.sprite.rect.x,self.test.sprite.rect.y = pygame.mouse.get_pos()

    def render(self):
        self.display.fill(BACKGROUNDCOLOR)
        self.test_group.draw(self.display)
        pygame.display.flip()


    