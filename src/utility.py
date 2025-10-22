import pygame,sys,os,pathlib
from pygame.math import Vector2

base_path = pathlib.Path(r'C:\projects\PyDew-Valley')

# -- constant values --
WIDTH = 700
HEIGHT = 520
GAMETITLE = 'PyDew Valley'
BACKGROUNDCOLOR = 'light blue'
FPS = 60

#   -- physics constants --
FRICTION = 0.4

# -- game states --
STARTGAME = 'start game'
CLOSEGAME = 'close game'
EDITORMODE = 'editor mode'
INGAME = 'in game'

# -- character constants --
IDLE = 'idle'
TOOL = 'tool'
MOVE = 'move'
AXE = 'axe'
HOE = 'hoe'
WATER = 'water'

#   -- directional constants --
LEFT = 'left'
RIGHT = 'right'
UP = 'up'
DOWN = 'down'

# -- textures --
GRAPHICS = base_path/'assets'/'graphics'

CHARACTERTEXTURES = {
    MOVE:{
        DOWN:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'down').iterdir()
        ],
        UP:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'up').iterdir()
        ],
        LEFT:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'left').iterdir()
        ],
        RIGHT:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'right').iterdir()
        ]
    },
    IDLE:{
        DOWN:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'down_idle').iterdir()
        ],
        UP:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'up_idle').iterdir()
        ],
        LEFT:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'left_idle').iterdir()
        ],
        RIGHT:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'right_idle').iterdir()
        ]
    },
    TOOL:{
        WATER:{
            DOWN:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'down_water').iterdir()
            ],
            UP:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'up_water').iterdir()
            ],
            LEFT:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'left_water').iterdir()
            ],
            RIGHT:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'right_water').iterdir()
            ]   
        },
        HOE:{
            DOWN:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'down_hoe').iterdir()
            ],
            UP:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'up_hoe').iterdir()
            ],
            LEFT:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'left_hoe').iterdir()
            ],
            RIGHT:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'right_hoe').iterdir()
            ]
        },
        AXE:{
            DOWN:[
            pygame.image.load(file_path)
            for file_path in (GRAPHICS/'character'/'down_axe').iterdir()
            ],
            UP:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'up_axe').iterdir()
            ],
            LEFT:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'left_axe').iterdir()
            ],
            RIGHT:[
                pygame.image.load(file_path)
                for file_path in (GRAPHICS/'character'/'right_axe').iterdir()
            ]
        }
    }
}


if __name__ == "__main__":

    pass

    
