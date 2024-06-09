#ifndef VARIABLE
#define VARIBALE
// States
bool game_is_running = 0;
bool start = 0;
bool finished = 0;
bool usernameSaved = 0;
bool win = 0, loss = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Window *usernameWin = NULL;
SDL_Renderer *usernameRenderer = NULL;

TTF_Font* comic = NULL;
TTF_Font* comicLarge = NULL;
TTF_Font* dejavu = NULL;

SDL_Texture* usernameTexture = NULL;
SDL_Texture* gameStartTexture = NULL;
SDL_Texture* selectorTexture = NULL;
SDL_Texture* boardTexture = NULL;

SDL_Texture* player1ImageTexture = NULL;
SDL_Texture* player2ImageTexture = NULL;
SDL_Texture* profileTexture = NULL;

SDL_Texture* practiceTexture = NULL;
SDL_Texture* multiplayerTexture = NULL;

SDL_Texture* winnerTexture = NULL;
SDL_Texture* loserTexture = NULL;

Mix_Music* music;


int last_frame_time = 0;
int startTime = 0;
int endTime = 0;

char* currentText;
int maxTextSize = 0;
int currentCharIndex = 0;
float curWidth = 0;

bool match = 0;
bool notMatch = 0;
bool back = 0;

//Graph
SDL_Point center = {800, 700};
SDL_Point points[10000];
int pointGap = 5000; // 5s
int pointCount = 0;
int nextPointX = 0;
//

int fontHeight = 0, fontWidth[128];
float movementPerMatch = 0;

int username_index = 0;
bool user_max_length = 0;
bool user_least_length = 0;

bool windowState[10];

bool musicOn = 1;

int charCount = 0, wordCount = 0, WPM = 0, CPM = 0;
int totalTypedChar = 0, correctTypedChar = 0;
int accuracy = 0;
int myChar = 0, oppChar = 0;

#endif