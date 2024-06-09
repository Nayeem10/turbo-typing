#ifndef CONSTANT
#define CONSTANT

#define WIDTH 1800
#define HEIGHT 1000

#define FPS 90
#define FRAME_TARGET_TIME (1000/FPS)

#define PORT 12345
#define SERVER_IP "172.220.150.176"

SDL_Color White = {255, 255, 255};
SDL_Color Black = {0, 0, 0};
SDL_Color Red = {255, 0, 0};
SDL_Color Green = {0, 255, 0};
SDL_Color Blue = {0, 0, 255};
SDL_Color Yellow = {255, 255, 0};
SDL_Color Cyan = {0, 255, 255};
SDL_Color Magenta = {255, 0, 255};
SDL_Color Orange = {255, 165, 0};
SDL_Color Purple = {128, 0, 128};
SDL_Color Pink = {255, 192, 203};
SDL_Color Brown = {165, 42, 42};
SDL_Color LightGray = {192, 192, 192};
SDL_Color DarkGray = {128, 128, 128};
SDL_Color Olive = {128, 128, 0};
SDL_Color Teal = {0, 128, 128};
SDL_Color Navy = {0, 0, 128};
SDL_Color Maroon = {128, 0, 0};
SDL_Color Lime = {0, 255, 0};
SDL_Color Aqua = {0, 255, 255};
SDL_Color Silver = {100, 100, 100};

typedef struct rectangle{
    float x, y;
    float width, height;
    SDL_Color color;
} Rec;

Rec rec;

typedef struct Avatar {
    float x, y, w, h;
    float curx;
    char name[200];
    SDL_Texture *texture;
} Avatar;

Avatar myAvatar, oppAvatar;
Avatar first = {20, 100, 200, 150, 20};
Avatar second = {20, 250, 220, 100, 20};

SDL_Rect retryBox = {1650, 860, 70, 70};
SDL_Rect backBox = {1650, 50, 70, 70};
SDL_Rect musicBox = {1700, 900, 60, 60};
SDL_Rect profileBox = {1550, 50, 60, 60};
SDL_Rect practiceBox = {200, 340, 600, 400};
SDL_Rect multiplayerBox = {950, 340, 600, 400};
SDL_Rect typingBox = {170, 140, 550, 60};
SDL_Rect yesBox = {480, 280, 200, 60};
SDL_Rect cancelBox = {220, 280, 200, 60};
SDL_Rect easyBox = {300, 200, 300, 150};
SDL_Rect mediumBox = {300, 400, 300, 150};
SDL_Rect hardBox = {300, 600, 300, 150};
SDL_Rect winnerBox = {900, 200, 400, 240};
SDL_Rect loserBox = {900, 200, 400, 240};

float textPosx = 80.0, textPosy = 200.0;
int mulTexty = 500;

typedef struct Inputs{
    int pressedKey, mouseX, mouseY;
    bool keyUp, keyDown, mouseDown;
} Inputs;

char *Font_Style[] = {
    "TTF/Comic.TTF",
    "TTF/Comic.TTF",
    "TTF/Arial.TTF"
};

char *Music[] = {
    "sakura.mp3",
    "click.wav"
};

char username[32];

char shift_map[] = {
    [' '] = ' ',
    ['1'] = '!',
    ['2'] = '@',
    ['3'] = '#',
    ['4'] = '$',
    ['5'] = '%',
    ['6'] = '^',
    ['7'] = '&',
    ['8'] = '*',
    ['9'] = '(',
    ['0'] = ')',
    ['-'] = '_',
    ['='] = '+',
    ['['] = '{',
    [']'] = '}',
    ['\\'] = '|',
    [';'] = ':',
    ['\''] = '"',
    [','] = '<',
    ['.'] = '>',
    ['/'] = '?',
    ['`'] = '~',
    ['a'] = 'A',
    ['b'] = 'B',
    ['c'] = 'C',
    ['d'] = 'D',
    ['e'] = 'E',
    ['f'] = 'F',
    ['g'] = 'G',
    ['h'] = 'H',
    ['i'] = 'I',
    ['j'] = 'J',
    ['k'] = 'K',
    ['l'] = 'L',
    ['m'] = 'M',
    ['n'] = 'N',
    ['o'] = 'O',
    ['p'] = 'P',
    ['q'] = 'Q',
    ['r'] = 'R',
    ['s'] = 'S',
    ['t'] = 'T',
    ['u'] = 'U',
    ['v'] = 'V',
    ['w'] = 'W',
    ['x'] = 'X',
    ['y'] = 'Y',
    ['z'] = 'Z'
};

#endif
