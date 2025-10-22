from utility import *

class PhysicsBody:
    def __init__(self):
        pass

class SpriteBody:
    def __init__(self):
        
        self.image = pygame.Surface((30,30))
        self.image.fill('light green')
        self.rect = self.image.get_rect(center = pygame.display.get_surface().get_rect().center)


class GroupObject:
    def __init__(self):
        self.members = []
    def draw(self,surface:pygame.Surface):
        '''
        -   Draws elements in members attribute to a surface
        -   Uses pygame.Surface.blits method
        '''
        draw_args = []
        for obj in self.members:
            obj:Object
            draw_args.append(obj.get_draw_args())
        surface.blits(draw_args)

    def add_member(self,obj):
        self.members.append(obj)

    

class Object:
    def __init__(self,group:GroupObject):
        
        self.sprite = SpriteBody()
        self.body =  PhysicsBody()

        group.add_member(self)

    def get_draw_args(self)->tuple[pygame.Surface,pygame.Rect]:
        return self.sprite.image,self.sprite.rect