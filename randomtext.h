#include <ctype.h>
#include <string.h>
#include <time.h>

// 100
char *Nouns[] = {"cat", "dog", "house", "tree", "car", "book", "chair", "computer", "table", "flower", "river", "mountain", "beach", "bicycle", "phone", "pen", "pencil", "bird", "fish", "elephant", "tiger", "lion", "bear", "rabbit", "snake", "frog", "butterfly", "spider", "ant", "horse", "cow", "sheep", "goat", "pig", "chicken", "duck", "eagle", "owl", "wolf", "fox", "squirrel", "monkey", "gorilla", "dolphin", "whale", "shark", "octopus", "crab", "lobster", "jellyfish", "starfish", "seagull", "peacock", "penguin", "kangaroo", "koala", "giraffe", "zebra", "rhinoceros", "hippopotamus", "crocodile", "alligator", "lizard", "turtle", "snail", "slug", "worm", "mosquito", "fly", "bee", "wasp", "dragonfly", "bat", "raccoon", "skunk", "otter", "beaver", "hedgehog", "chipmunk", "ferret", "hamster", "gerbil", "guinea", "pig", "chinchilla", "parrot", "toucan", "hummingbird", "woodpecker", "magpie", "sparrow", "finch", "crow", "hawk", "falcon", "vulture", "stork", "heron", "egret", "ibis"};
// 3
char *Articles[] = {"the", "a", "an"};
// 20
char *Pronouns[] = {"I", "you", "he", "she", "it", "we", "they", "me", "you", "him", "her", "us", "them", "myself", "yourself", "himself", "herself", "itself", "ourselves", "yourselves"};
// 150
char *Verbs[] = {"run", "jump", "walk", "eat", "sleep", "talk", "laugh", "cry", "sing", "dance", "read", "write", "draw", "paint", "swim", "fly", "crawl", "climb", "skip", "hop", "jog", "bike", "drive", "ride", "cook", "bake", "clean", "wash", "brush", "comb", "cut", "sew", "knit", "crochet", "plant", "water", "harvest", "dig", "build", "destroy", "fix", "repair", "create", "invent", "discover", "explore", "learn", "teach", "study", "research", "analyze", "interpret", "understand", "know", "remember", "forget", "believe", "doubt", "trust", "mistrust", "love", "hate", "like", "dislike", "enjoy", "fear", "respect", "admire", "envy", "appreciate", "congratulate", "apologize", "forgive", "blame", "praise", "criticize", "encourage", "discourage", "support", "oppose", "agree", "disagree", "argue", "debate", "discuss", "chat", "gossip", "joke", "tease", "flirt", "impress", "surprise", "shock", "scare", "amuse", "entertain", "bore", "annoy", "irritate", "frustrate", "apprehend", "ascertain", "collaborate", "communicate", "comprehend", "conceptualize", "consolidate", "contemplate", "coordinate", "corroborate", "demonstrate", "elucidate", "evaluate", "extrapolate", "facilitate", "implement", "incorporate", "innovate", "integrate", "investigate", "manipulate", "mediate", "negotiate", "orchestrate", "perpetuate", "prioritize", "rationalize", "reconcile", "reevaluate", "reinvent", "rejuvenate", "relinquish", "remediate", "restructure", "revitalize", "scrutinize", "strategize", "substantiate", "synchronize", "synthesize", "systematize", "transform", "validate", "verify", "visualize", "hypothesize", "speculate", "syncretize", "corroborate", "conceptualize"};
//100
char *Adverbs[] = {"quickly", "slowly", "quietly", "loudly", "softly", "harshly", "gently", "firmly", "weakly", "strongly", "happily", "sadly", "angrily", "calmly", "nervously", "confidently", "doubtfully", "carelessly", "cautiously", "eagerly", "lazily", "energetically", "sluggishly", "gracefully", "clumsily", "smoothly", "roughly", "cleanly", "messily", "neatly", "sloppily", "politely", "rudely", "kindly", "cruelly", "generously", "selfishly", "honestly", "dishonestly", "bravely", "cowardly", "wisely", "foolishly", "cleverly", "stupidly", "fairly", "unfairly", "evenly", "unevenly", "evenly", "unevenly", "properly", "improperly", "correctly", "incorrectly", "precisely", "approximately", "exactly", "roughly", "precisely", "approximately", "exactly", "precisely", "approximately", "about", "exactly", "perfectly", "flawlessly", "neatly", "messily", "coherently", "incoherently", "clearly", "unclearly", "vividly", "vaguely", "deeply", "shallowly", "thoroughly", "superficially", "properly", "improperly", "well", "poorly", "thoroughly", "partially", "completely", "partly", "fully", "hardly", "barely", "almost", "nearly", "entirely", "wholly", "totally", "utterly", "completely", "fully", "absolutely"};
//100
char *Adjectives[] = {"big" ,"small" ,"red" ,"blue" ,"green" ,"yellow" ,"orange" ,"purple" ,"black" ,"white" ,"gray" ,"brown" ,"pink" ,"beautiful" ,"ugly" ,"pretty" ,"handsome" ,"cute" ,"adorable" ,"lovely" ,"charming" ,"elegant" ,"graceful" ,"rugged" ,"rough" ,"smooth" ,"shiny" ,"dull" ,"bright" ,"dim" ,"light" ,"dark" ,"sunny" ,"cloudy" ,"rainy" ,"snowy" ,"windy" ,"calm" ,"stormy" ,"hot" ,"cold" ,"warm" ,"cool" ,"freezing" ,"boiling" ,"wet" ,"dry" ,"humid" ,"arid" ,"lush" ,"barren" ,"fertile" ,"infertile" ,"fertile" ,"infertile" ,"rich" ,"poor" ,"wealthy" ,"affluent" ,"impoverished" ,"crowded" ,"deserted" ,"noisy" ,"quiet" ,"peaceful" ,"chaotic" ,"organized" ,"tidy" ,"messy" ,"clean" ,"dirty" ,"polluted" ,"pristine" ,"polluted" ,"pristine" ,"polluted" ,"polluted" ,"fresh" ,"stale" ,"rotten" ,"ripe" ,"unripe" ,"ripe" ,"unripe" ,"delicious" ,"tasteless" ,"sweet" ,"sour" ,"bitter" ,"salty" ,"savory" ,"spicy" ,"bland" ,"flavorful" ,"tasteless" ,"aromatic" ,"fragrant" ,"smelly" ,"odorous" ,"scentless"};
//100
char *Prepositions[] = {"about" ,"above" ,"across" ,"after" ,"against" ,"along" ,"amid" ,"among" ,"around" ,"as" ,"at" ,"before" ,"behind" ,"below" ,"beneath" ,"beside" ,"besides" ,"between" ,"beyond" ,"but" ,"by" ,"concerning" ,"considering" ,"despite" ,"down" ,"during" ,"except" ,"for" ,"from" ,"in" ,"inside" ,"into" ,"like" ,"near" ,"next" ,"of" ,"off" ,"on" ,"onto" ,"out" ,"outside" ,"over" ,"past" ,"regarding" ,"round" ,"since" ,"through" ,"throughout" ,"till" ,"to" ,"toward" ,"towards" ,"under" ,"underneath" ,"unlike" ,"until" ,"unto" ,"up" ,"upon" ,"with" ,"within" ,"without" ,"aboard" ,"afore" ,"alongst" ,"amidst" ,"amongs" ,"athwart" ,"bating" ,"because" ,"behindhand" ,"betweenwhile" ,"betwixt" ,"beyondforth" ,"buttwixt" ,"cuz" ,"despiteward" ,"duringst" ,"enow" ,"forby" ,"fornenst" ,"forenenst" ,"forsooth" ,"fromward" ,"midwards" ,"notwithstanding" ,"oer" ,"outwith" ,"sincewards" ,"syne" ,"thro" ,"tilward" ,"tother" ,"underne" ,"untilward" ,"whilere" ,"withal" ,"withinforth" ,"withoutforth" ,"worth"};
//100
char *Conjunctions[] = {"and" ,"but" ,"or" ,"yet" ,"so" ,"for" ,"nor" ,"because" ,"although" ,"since" ,"unless" ,"until" ,"while" ,"whilst" ,"if" ,"then" ,"therefore" ,"hence" ,"thus" ,"consequently" ,"however" ,"nevertheless" ,"nonetheless" ,"moreover" ,"furthermore" ,"additionally" ,"also" ,"besides" ,"otherwise" ,"instead" ,"nonetheless" ,"nevertheless" ,"meanwhile" ,"subsequently" ,"afterwards" ,"afterward" ,"before" ,"after" ,"when" ,"while" ,"whereas" ,"though" ,"although" ,"even" ,"though" ,"inasmuch" ,"as" ,"wherever" ,"when" ,"while" ,"whereas" ,"though" ,"although" ,"even" ,"though" ,"inasmuch" ,"as" ,"wherever" ,"whenever" ,"whatever" ,"whoever" ,"whichever" ,"however" ,"nevertheless" ,"nonetheless" ,"moreover" ,"furthermore" ,"additionally" ,"also" ,"besides" ,"otherwise" ,"instead" ,"meanwhile" ,"subsequently" ,"afterwards" ,"afterward" ,"before" ,"after" ,"whatever" ,"whoever" ,"whichever" ,"however" ,"nevertheless" ,"nonetheless" ,"moreover" ,"furthermore" ,"additionally" ,"also" ,"besides" ,"otherwise" ,"instead" ,"meanwhile" ,"subsequently" ,"afterwards" ,"afterward" ,"before" ,"after" ,"amongs" ,"athwart" ,"bating"};


char *generate_random_text() {
    srand(time(NULL));

    int sentence_structure;
    int curLen = 0;

    char *text;
    text = (char*) malloc(400*sizeof(char)); text[0] = '\0';
    while(strlen(text) <= 100){
        char word[200];
        sentence_structure = rand() % 3;
        switch (sentence_structure) {
            
            case 0: // Simple text: noun + verb + adverb
                strcpy(word, Nouns[rand() % 100]); 
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                word[0] = toupper(word[0]);
                strcat(text, word);

                strcpy(word, Verbs[rand() % 150]);
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);

                strcpy(word, Adverbs[rand() % 100]);
                strcat(word, ". ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);

                break;
            case 1: // Compound text: pronoun + verb + conjunction + pronoun + verb
                strcpy(word, Nouns[rand() % 100]); 
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                word[0] = toupper(word[0]);
                strcat(text, word);

                strcpy(word, Verbs[rand() % 150]);
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);

                strcat(text, word);

                strcpy(word, Conjunctions[rand() % 100]);
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);

                strcpy(word, Pronouns[rand() % 20]);
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);
                
                strcpy(word, Verbs[rand() % 150]);
                strcat(word, ". ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);
                break;
            case 2: // Complex text: article + adjective + noun + verb + preposition + noun
                strcpy(word, Articles[rand() % 3]); 
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                word[0] = toupper(word[0]);
                strcat(text, word);

                strcpy(word, Adjectives[rand() % 100]);
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);

                strcpy(word, Nouns[rand() % 100]);
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);

                strcpy(word, Verbs[rand() % 150]);
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);

                strcpy(word, Prepositions[rand() % 100]);
                strcat(word, " ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);
                
                strcpy(word, Nouns[rand() % 100]);
                strcat(word, ". ");
                if(curLen + strlen(word) > 95) {
                    strcat(text, "\n"); curLen = 0;
                }
                curLen += strlen(word);
                strcat(text, word);
                break;
        }
    }
    text[strlen(text) - 1] = '\0';
    return text;
}
