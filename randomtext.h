#ifndef RANDOM_TEXT
#define RANDOM_TEXT

#include <time.h>
#include <ctype.h>
#include <string.h>

// 100
const char *Nouns[] = {"cat", "dog", "house", "tree", "car", "book", "chair", "computer", "table", "flower", "river", "mountain", "beach", "bicycle", "phone", "pen", "pencil", "bird", "fish", "elephant", "tiger", "lion", "bear", "rabbit", "snake", "frog", "vine", "spider", "ant", "horse", "cow", "sheep", "goat", "pig", "chicken", "duck", "eagle", "owl", "wolf", "fox", "kid", "monkey", "gorilla", "dolphin", "whale", "shark", "octopus", "crab", "lobster", "mask", "starfish", "seagull", "peacock", "penguin", "kangaroo", "koala", "giraffe", "zebra", "wool", "quilt", "urn", "alligator", "lizard", "turtle", "snail", "slug", "worm", "mosquito", "fly", "bee", "wasp", "dragonfly", "bat", "raccoon", "skunk", "otter", "beaver", "hedgehog", "chipmunk", "ferret", "hamster", "gerbil", "guinea", "pig", "glue", "parrot", "toucan", "hummingbird", "woodpecker", "magpie", "sparrow", "finch", "crow", "hawk", "falcon", "vulture", "stork", "heron", "egret", "ibis"};
// 3
const char *Articles[] = {"a", "an", "the"};
// 20
const char *Pronouns[] = {"I", "you", "he", "she", "it", "we", "they", "me", "you", "him", "her", "us", "them", "myself", "yourself", "himself", "herself", "itself", "ourselves", "yourselves"};
// 150
const char *Verbs[] = {"run", "jump", "walk", "eat", "sleep", "talk", "laugh", "cry", "sing", "dance", "read", "write", "draw", "paint", "swim", "fly", "crawl", "climb", "skip", "hop", "jog", "bike", "drive", "ride", "cook", "bake", "clean", "wash", "brush", "comb", "cut", "sew", "knit", "crochet", "plant", "water", "harvest", "dig", "build", "destroy", "fix", "repair", "create", "invent", "discover", "explore", "learn", "teach", "study", "boil", "clean", "interpret", "mop", "know", "iron", "forget", "believe", "doubt", "trust", "knit", "love", "hate", "like", "dislike", "enjoy", "fear", "respect", "admire", "envy", "sketch", "mend", "apologize", "forgive", "blame", "praise", "quiz", "study", "test", "support", "oppose", "agree", "disagree", "argue", "debate", "discuss", "chat", "gossip", "joke", "tease", "flirt", "impress", "surprise", "shock", "scare", "amuse", "entertain", "bore", "annoy", "search", "frustrate", "seek", "trade", "collaborate", "communicate", "comprehend", "lock", "tie", "hop", "skip", "whistle", "hum", "chew", "evaluate", "bite", "sip", "implement", "spill", "innovate", "stir", "chop", "manipulate", "mediate", "negotiate", "toss", "kiss", "tap", "nod", "reconcile", "reevaluate", "reinvent", "plead", "part", "shout", "boo", "scold", "warn", "list", "erase", "click", "synthesize", "save", "transform", "validate", "verify", "visualize", "spot", "speculate", "sail", "corroborate", "rip"};
//100
const char *Adverbs[] = {"quickly", "slowly", "quietly", "loudly", "softly", "harshly", "gently", "firmly", "weakly", "strongly", "happily", "sadly", "angrily", "calmly", "fast", "now", "then", "once", "soon", "eagerly", "lazily", "early", "next", "here", "almost", "smoothly", "roughly", "cleanly", "messily", "neatly", "maybe", "politely", "rudely", "kindly", "cruelly", "only", "right", "honestly", "wrong", "bravely", "cowardly", "wisely", "fully", "cleverly", "stupidly", "fairly", "unfairly", "evenly", "unevenly", "evenly", "unevenly", "properly", "often", "correctly", "below", "precisely", "above", "exactly", "roughly", "outside", "inside", "though", "today", "soon", "about", "anywhere", "perfectly", "nearby", "neatly", "messily", "coherently", "however", "clearly", "again", "vividly", "vaguely", "deeply", "therein", "thoroughly", "forever", "properly", "improperly", "well", "poorly", "thoroughly", "partially", "completely", "partly", "fully", "hardly", "barely", "almost", "nearly", "entirely", "wholly", "totally", "utterly", "completely", "fully", "absolutely"};
//100
const char *Adjectives[] = {"big" ,"small" ,"red" ,"blue" ,"green" ,"yellow" ,"orange" ,"purple" ,"black" ,"white" ,"gray" ,"brown" ,"pink" ,"beautiful" ,"ugly" ,"pretty" ,"handsome" ,"cute" ,"adorable" ,"lovely" ,"charming" ,"elegant" ,"graceful" ,"rugged" ,"rough" ,"smooth" ,"shiny" ,"dull" ,"bright" ,"dim" ,"light" ,"dark" ,"sunny" ,"cloudy" ,"rainy" ,"snowy" ,"windy" ,"calm" ,"stormy" ,"hot" ,"cold" ,"warm" ,"cool" ,"freezing" ,"boiling" ,"wet" ,"dry" ,"humid" ,"arid" ,"lush" ,"barren" ,"fertile" ,"infertile" ,"fertile" ,"infertile" ,"rich" ,"poor" ,"wealthy" ,"affluent" ,"impoverished" ,"crowded" ,"deserted" ,"noisy" ,"quiet" ,"peaceful" ,"chaotic" ,"organized" ,"tidy" ,"messy" ,"clean" ,"dirty" ,"polluted" ,"pristine" ,"polluted" ,"pristine" ,"polluted" ,"polluted" ,"fresh" ,"stale" ,"rotten" ,"ripe" ,"unripe" ,"ripe" ,"unripe" ,"delicious" ,"tasteless" ,"sweet" ,"sour" ,"bitter" ,"salty" ,"savory" ,"spicy" ,"bland" ,"flavorful" ,"tasteless" ,"aromatic" ,"fragrant" ,"smelly" ,"odorous" ,"scentless"};
//100
const char *Prepositions[] = {"about" ,"above" ,"across" ,"after" ,"against" ,"along" ,"amid" ,"among" ,"around" ,"as" ,"at" ,"before" ,"behind" ,"below" ,"beneath" ,"beside" ,"besides" ,"between" ,"beyond" ,"but" ,"by" ,"concerning" ,"considering" ,"despite" ,"down" ,"during" ,"except" ,"for" ,"from" ,"in" ,"inside" ,"into" ,"like" ,"near" ,"next" ,"of" ,"off" ,"on" ,"onto" ,"out" ,"outside" ,"over" ,"past" ,"regarding" ,"round" ,"since" ,"through" ,"throughout" ,"till" ,"to" ,"toward" ,"towards" ,"under" ,"underneath" ,"unlike" ,"until" ,"unto" ,"up" ,"upon" ,"with" ,"within" ,"without" ,"aboard" ,"afore" ,"alongst" ,"amidst" ,"amongs" ,"athwart" ,"bating" ,"because" ,"behindhand" ,"betweenwhile" ,"betwixt" ,"beyondforth" ,"buttwixt" ,"cuz" ,"despiteward" ,"duringst" ,"enow" ,"forby" ,"fornenst" ,"forenenst" ,"forsooth" ,"fromward" ,"midwards" ,"notwithstanding" ,"oer" ,"outwith" ,"sincewards" ,"syne" ,"thro" ,"tilward" ,"tother" ,"underne" ,"untilward" ,"whilere" ,"withal" ,"withinforth" ,"withoutforth" ,"worth"};
//100
const char *Conjunctions[] = {"and" ,"but" ,"or" ,"yet" ,"so" ,"for" ,"nor" ,"because" ,"although" ,"since" ,"unless" ,"until" ,"while" ,"whilst" ,"if" ,"then" ,"therefore" ,"hence" ,"thus" ,"consequently" ,"however" ,"nevertheless" ,"nonetheless" ,"moreover" ,"furthermore" ,"additionally" ,"also" ,"besides" ,"otherwise" ,"instead" ,"nonetheless" ,"nevertheless" ,"meanwhile" ,"subsequently" ,"afterwards" ,"afterward" ,"before" ,"after" ,"when" ,"while" ,"whereas" ,"though" ,"although" ,"even" ,"though" ,"inasmuch" ,"as" ,"wherever" ,"when" ,"while" ,"whereas" ,"though" ,"although" ,"even" ,"though" ,"inasmuch" ,"as" ,"wherever" ,"whenever" ,"whatever" ,"whoever" ,"whichever" ,"however" ,"nevertheless" ,"nonetheless" ,"moreover" ,"furthermore" ,"additionally" ,"also" ,"besides" ,"otherwise" ,"instead" ,"meanwhile" ,"subsequently" ,"afterwards" ,"afterward" ,"before" ,"after" ,"whatever" ,"whoever" ,"whichever" ,"however" ,"nevertheless" ,"nonetheless" ,"moreover" ,"furthermore" ,"additionally" ,"also" ,"besides" ,"otherwise" ,"instead" ,"meanwhile" ,"subsequently" ,"afterwards" ,"afterward" ,"before" ,"after" ,"amongs" ,"athwart" ,"bating"};
//7
const char *Punctuation_pronouns[] = {"i'm" ,"you're" ,"he's" ,"she's" ,"it's" ,"we're" ,"they're"};
//50
const char *verbs_ing[] = {"running", "walking", "talking", "eating", "drinking", "reading", "writing", "singing", "dancing", "swimming","cooking", "baking", "cleaning", "playing", "watching", "listening", "learning", "teaching", "driving", "shopping", "studying", "working", "sleeping", "drawing", "painting", "building", "fixing", "flying", "hiking", "climbing", "jogging", "smiling", "laughing", "crying", "yawning", "shouting", "whispering", "typing", "browsing", "surfing", "knitting", "sewing", "gardening", "fishing", "camping", "traveling", "exploring", "inventing", "designing", "organizing"};
//10
const char *words_with_punctuation[] = {"co-op" ,"re-enter" ,"o'clock" ,"rock'n'roll" ,"jack-o'-lantern" ,"mother-in-law" ,"x-ray" ,"twenty-one" ,"mind-blowing" ,"t-shirt"};
//9
const char *WH_words[] = {"who" , "what" ,"when" ,"where" ,"why" ,"which" ,"whom" ,"whose" ,"how"};
//15
const char *auxiliary_verbs[] = {"am" ,"is" ,"are" ,"was" ,"were" ,"do" ,"did" ,"done" ,"does" ,"being" ,"been" ,"have" ,"hase" ,"had" ,"having"};

void check(char *word, char *text, int *curLen){
    if(*curLen + strlen(word) > 95) {
        strcat(text, "\n"); 
        *curLen = 0;
    }
    *curLen += strlen(word);
}

void addSimpleSentence(char *word, char *text, int *curLen){

    for(int i=0; i<4; i++) {

        int word_choice = rand() % 4;

        switch(word_choice) {
            case 0:
                strcpy(word, Nouns[rand() % 100]); 
                strcat(word, " ");
                check(word, text, curLen);
                strcat(text, word);
                break;
            case 1:
                strcpy(word, Verbs[rand() % 150]); 
                strcat(word, " ");
                check(word, text, curLen);
                strcat(text, word);
                break;
            case 2:
                strcpy(word, Adjectives[rand() % 100]); 
                strcat(word, " ");
                check(word, text, curLen);
                strcat(text, word);
                break;
            case 3:
                strcpy(word, Adverbs[rand() % 100]); 
                strcat(word, " ");
                check(word, text, curLen);
                strcat(text, word);
                break;
        }
    }
}

void addComplexSentence(char *word, char *text, int *curLen){
    strcpy(word, Pronouns[rand() % 20]); 
    strcat(word, " ");
    check(word, text, curLen);
    word[0] = toupper(word[0]);
    strcat(text, word);

    strcpy(word, Verbs[rand() % 150]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);
    
    strcpy(word, Nouns[rand() % 100]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Conjunctions[rand() % 100]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Pronouns[rand() % 20]); 
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Verbs[rand() % 150]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Prepositions[rand() % 100]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Nouns[rand() % 100]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);
}

void addCompoundSentence(char *word, char *text, int *curLen){
    strcpy(word, Pronouns[rand() % 20]); 
    strcat(word, " ");
    check(word, text, curLen);
    word[0] = toupper(word[0]);
    strcat(text, word);

    strcpy(word, Verbs[rand() % 150]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);
    
    strcpy(word, Prepositions[rand() % 100]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Verbs[rand() % 150]);
    strcat(word, ", ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Conjunctions[rand() % 100]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Pronouns[rand() % 20]); 
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Verbs[rand() % 150]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);
    
    strcpy(word, Prepositions[rand() % 100]);
    strcat(word, " ");
    check(word, text, curLen);
    strcat(text, word);

    strcpy(word, Verbs[rand() % 150]);
    strcat(word, ". ");
    check(word, text, curLen);
    strcat(text, word);
}

char *generate_random_text(int difficulty, int randomTextSize) {
    srand(time(NULL));

    int curLen = 0, sentence_type = 0;

    char *text;
    text = (char*) malloc(400*sizeof(char)); text[0] = '\0';
    while(strlen(text) <= randomTextSize){
        char word[200];
        switch (difficulty) {
            
            case 0:
                addSimpleSentence(word, text, &curLen);
                break;
            case 1:
                sentence_type = rand() % 2;
                if(sentence_type == 0) {
                    addComplexSentence(word, text, &curLen);
                }
                else { // Complex text: Punctuation_pronouns + verbs_ing + adverbs
                    strcpy(word, Punctuation_pronouns[rand() % 7]); 
                    strcat(word, " ");
                    check(word, text, &curLen);
                    word[0] = toupper(word[0]);
                    strcat(text, word);

                    strcpy(word, verbs_ing[rand() % 50]);
                    strcat(word, " ");
                    check(word, text, &curLen);
                    strcat(text, word);

                    strcpy(word, Adverbs[rand() % 100]);
                    strcat(word, ". ");
                    check(word, text, &curLen);
                    strcat(text, word);

                    break;
                }
            case 2: 
                sentence_type = rand() % 4;
                if(sentence_type == 0) {
                    addCompoundSentence(word, text, &curLen);
                    break;
                }else if(sentence_type == 1) {
                    strcpy(word, Punctuation_pronouns[rand() % 7]); 
                    strcat(word, " ");
                    check(word, text, &curLen);
                    word[0] = toupper(word[0]);
                    strcat(text, word);

                    strcpy(word, verbs_ing[rand() % 50]);
                    strcat(word, " ");
                    check(word, text, &curLen);
                    strcat(text, word);

                    strcpy(word, Adverbs[rand() % 100]);
                    strcat(word, ". ");
                    check(word, text, &curLen);
                    strcat(text, word);

                    break;
                }else if(sentence_type == 2) {
                    strcpy(word, words_with_punctuation[rand() % 10]); 
                    strcat(word, " ");
                    check(word, text, &curLen);
                    word[0] = toupper(word[0]);
                    strcat(text, word);

                    strcpy(word, verbs_ing[rand() % 50]);
                    strcat(word, ", ");
                    check(word, text, &curLen);
                    strcat(text, word);

                    strcpy(word, Adverbs[rand() % 100]);
                    strcat(word, ". ");
                    check(word, text, &curLen);
                    strcat(text, word);

                    break;
                }else {
                    strcpy(word, Nouns[rand() % 100]); 
                    strcat(word, " ");
                    check(word, text, &curLen);
                    word[0] = toupper(word[0]);
                    strcat(text, word);

                    strcpy(word, "says, \"");
                    check(word, text, &curLen);
                    strcat(text, word);

                    strcpy(word, Nouns[rand() % 100]);
                    strcat(word, " "); 
                    check(word, text, &curLen);
                    word[0] = toupper(word[0]);
                    strcat(text, word);

                    strcpy(word, Verbs[rand() % 150]);
                    strcat(word, " ");
                    check(word, text, &curLen);
                    strcat(text, word);

                    strcpy(word, Conjunctions[rand() % 100]);
                    strcat(word, " ");
                    check(word, text, &curLen);
                    strcat(text, word);

                    strcpy(word, Pronouns[rand() % 20]);
                    strcat(word, " ");
                    check(word, text, &curLen);
                    strcat(text, word);
                    
                    strcpy(word, Verbs[rand() % 150]);
                    strcat(word, ".\" ");
                    check(word, text, &curLen);
                    strcat(text, word);
                    break;
                }
        }
    }
    text[strlen(text) - 1] = '\0';
    return text;
}

#endif