from utility import *
from gameobjects import Object , GroupObject
class Game:

    def __init__(self):
        
        self.display = pygame.display.set_mode((WIDTH,HEIGHT));pygame.display.set_caption(GAMETITLE)    
        self.clock = pygame.time.Clock()
        self.state = STARTGAME
    
        self.test_group = GroupObject()

        self.test = Object(self.test_group)
        self.test_2 = Object(self.test_group)
        self.test_2.sprite.image.fill('yellow')

        #   --editor mode attributes--
        self.editor_object_index = 0        

    def handle_events(self):
        for event in pygame.event.get():
            match event.type:
                case pygame.QUIT:
                    self.state = CLOSEGAME
                case pygame.KEYDOWN:

                    #   -- enter editor mode --
                    if event.key == pygame.K_0:
                        self.state = EDITORMODE
                        continue

                    if self.state == EDITORMODE:
                        match event.key:

                            #   --  exit editor mode --
                            case pygame.K_ESCAPE:
                                self.state = INGAME    

                            #   -- move object selection --
                            case pygame.K_RIGHT:
                                self.editor_object_index += 1 
                                if self.editor_object_index > len(self.test_group.members):
                                    self.editor_object_index = len(self.test_group.members)
                            case pygame.K_LEFT:
                                self.editor_object_index -= 1
                                if self.editor_object_index < 0:
                                    self.editor_object_index = 0
                        
                
    def get_editor_object(self):
        return self.test_group.members[self.editor_object_index]

    def update(self):

        if self.state == EDITORMODE:
            selected = self.get_editor_object()
            selected.sprite.rect.x,selected.sprite.rect.y = pygame.mouse.get_pos()

        elif self.state == INGAME:
            pass

    def render(self):
        self.display.fill(BACKGROUNDCOLOR)
        self.test_group.draw(self.display)
        pygame.display.flip()


    