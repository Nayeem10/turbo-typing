// States
bool previous = 0;
bool game_is_running = 0;
bool pre_menu = 1;
bool user_name = 0;
bool select_menu = 0;
bool single_menu = 0;
bool multi_menu = 0;
bool practice = 0;
bool multiplayer = 0;
bool start = 0;
bool finished = 0;
bool playAgain = 0;
bool usernameSaved = 0;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

TTF_Font* comic = NULL;
TTF_Font* comicLarge = NULL;
TTF_Font* dejavu = NULL;

SDL_Texture* Username = NULL;
SDL_Texture* preMenuImageTexture = NULL;
SDL_Texture* Menu_selector = NULL;
SDL_Texture* practiceBackgroundTexture = NULL;
SDL_Texture* Main_menu = NULL;
SDL_Texture* Multi_menu = NULL;

SDL_Texture* spaceImageTexture = NULL;
SDL_Texture* player1ImageTexture = NULL;
SDL_Texture* player2ImageTexture = NULL;
SDL_Texture* profileTexture = NULL;

SDL_Texture* practiceTexture = NULL;
SDL_Texture* multiplayerTexture = NULL;

Mix_Music* music;


int last_frame_time = 0;
int next_input_time = 0;
int charCount = 0;

char* currentText;
int maxTextSize = 0;
int currentCharIndex = 0;
float curWidth = 0;

bool match = 0;
bool notMatch = 0;
bool back = 0;


int fontHeight = 0, fontWidth[128];

float player1x = 0, player1y = 0;
float player1Height = 0, player1Width = 0;
float player1mx = 0, player1my = 0;

float player2x = 0, player2y = 0;
float player2Height = 0, player2Width = 0;
float player2mx = 0, player2my = 0;

float movementPerMatch = 0;

int startTime = 0;
int endTime = 0;

int username_index = 0;
bool user_max_length = 0;
bool user_least_length = 0;

bool windowState[10];


bool musicOn = 1;

int wordCount = 0, WPM = 0;