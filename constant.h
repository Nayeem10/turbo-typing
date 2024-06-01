#define WIDTH 1800
#define HEIGHT 1000

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

#define PORT 12345
#define SERVER_IP "192.168.0.183"

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

typedef struct rectangle{
    float x, y;
    float width, height;
    SDL_Color color;
} Rec;
Rec rec;
Rec startTypingBox = {760, 500, 280, 50, {0, 255, 255}};
Rec playAgainBox = {760, 500, 280, 50, {0, 128, 128}};
Rec practiceMode = {760, 450, 380, 50, {0, 255, 255}};
Rec multiPlayerMode = {760, 550, 380, 50, {0, 255, 255}};
Rec diff = {350, 440, 345, 80, {0, 255, 255}};
Rec diff_e = {1097, 405, 210, 75, {0, 255, 255}};
Rec diff_m = {1222, 516, 222, 78, {0, 255, 255}};
Rec diff_h = {1097, 635, 210, 83, {0, 255, 255}};
Rec opt = {350, 570, 345, 80, {0, 255, 255}};
Rec opt_m = {1165, 450, 258, 102, {0, 255, 255}};
Rec opt_s = {1165, 625, 258, 102, {0, 255, 255}};

SDL_Rect retryBox = {1650, 860, 70, 70};
SDL_Rect backBox = {1650, 50, 70, 70};
SDL_Rect musicBox = {1700, 900, 60, 60};
SDL_Rect profileBox = {1550, 50, 60, 60};
SDL_Rect practiceBox = {150, 240, 700, 400};
SDL_Rect multiplayerBox = {950, 240, 700, 400};
SDL_Rect typingBox = {170, 140, 550, 60};
SDL_Rect yesBox = {480, 280, 200, 60};
SDL_Rect cancelBox = {220, 280, 200, 60};

float textPosx = 80.0, textPosy = 200.0;

float showTextx = 60, showTexty = 400.0;

typedef struct Inputs{
    int pressedKey, mouseX, mouseY;
    bool keyUp, keyDown, mouseDown;
} Inputs;

char *Font_Style[] = {
    "TTF/Comic.TTF",
    "TTF/Comic.TTF",
    "TTF/Arial.TTF"
};

char *Background[] = {
    "1.jpg"
};

char *Images[] = {
    "santa.png",
    "space.jpg",
    "player1.png",
    "player2.png",
    "profile.png",
    "retry.png"
};

char *Music[] = {
    "sakura.mp3",
    "click.wav"
};



char username[1000];

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

char *Texts[] = {

    "Good name in man and woman, dear my lord, Is the immediate jewel of their souls: Who steals my \npurse steals trash; 'tis something, nothing; 'Twas mine, 'tis his, and has been slave to thousands; \nBut he that filches from me my good name Robs me of that which not enriches him, And makes me \npoor indeed.",
    "Maycomb was a tired, old town when i first knew it. \npeople moved slowly, they ambled across the square, shuffled \nin and out of the stores around it - everything that happened \nseemed to happen in slow motion.",
    "SDL, O goddess, the anger of Achilles son of Peleus, that brought countless ills upon the Achaeans. \nMany a brave soul did it send hurrying down to Hades, and many a hero did it yield a prey to dogs \nand vultures, for so were the counsels of Jove fulfilled from the day on which the son of Atreus, \nking of men, and great Achilles, first fell out with one another.",

};
