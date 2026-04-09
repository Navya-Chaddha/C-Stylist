#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Outfit
 {
    string name;
    string category;
    vector<string> occasions;
    vector<string> weatherTags;
    vector<string> bodyTypes;
    vector<string> colorPalettes;
    vector<string> genders;
    vector<string> dressCodes;
    vector<string> styleTags;
    vector<string> comfortTags;
    vector<string> footwearOptions;
    vector<string> jewelryOptions;
    int minBudget;
};

struct UserInput 
{
    string name;
    string gender;
    string occasion;
    string weather;
    string bodyType;
    string colorPreference;
    string dressCode;
    int comfortVsStyle; // 1 = pure comfort, 10 = pure style
    int budget;
    bool wantsLayers;
};

string toLower(string s) 
{
    for (size_t i = 0; i < s.size(); ++i)
     {
        s[i] = static_cast<char>(tolower(static_cast<unsigned char>(s[i])));
    }
    return s;
}

bool contains(const vector<string> &arr, const string &value) 
{
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

int askOption(const string &question, const vector<string> &options) {
    cout << "\n" << question << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        cout << "  " << (i + 1) << ". " << options[i] << "\n";
    }
    cout << "Choose option number: ";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > static_cast<int>(options.size())) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid option number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice - 1;
}

int askIntInRange(const string &question, int minVal, int maxVal) {
    cout << "\n" << question << " (" << minVal << "-" << maxVal << "): ";
    int value;
    while (!(cin >> value) || value < minVal || value > maxVal) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number in range " << minVal << "-" << maxVal << ": ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

bool askYesNo(const string &question) {
    cout << "\n" << question << " (y/n): ";
    char ch;
    while (!(cin >> ch) || (tolower(ch) != 'y' && tolower(ch) != 'n')) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please type y or n: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return tolower(ch) == 'y';
}

vector<Outfit> getOutfitCatalog() {
    return {
        {"Classic navy blazer + white shirt + slim trousers", "formal",
         {"office", "wedding", "formal dinner"}, {"mild", "cold"}, {"all"},
         {"neutral", "blue", "pastel"}, {"male", "non-binary"}, {"formal", "smart casual"},
         {"polished", "minimal"}, {"moderate"}, {"oxfords", "loafers"},
         {"silver watch", "cufflinks", "minimal bracelet"}, 2500},

        {"A-line midi dress + cropped jacket", "dressy",
         {"date", "party", "wedding"}, {"mild", "cold"}, {"pear", "hourglass", "all"},
         {"red", "pastel", "jewel"}, {"female", "non-binary"}, {"semi-formal", "formal"},
         {"chic", "elegant"}, {"moderate"}, {"block heels", "ankle boots"},
         {"drop earrings", "layered necklace", "delicate bracelet"}, 2200},

        {"Oversized tee + straight jeans + sneakers", "casual",
         {"college", "shopping", "travel", "casual outing"}, {"hot", "mild"}, {"all"},
         {"neutral", "earthy", "black"}, {"all"}, {"casual"},
         {"street", "minimal"}, {"high"}, {"sneakers", "slip-ons"},
         {"hoop earrings", "chain necklace", "beaded bracelet"}, 1200},

        {"Kurta set + dupatta + juttis", "ethnic",
         {"festival", "family function", "wedding"}, {"hot", "mild", "cold"}, {"all"},
         {"jewel", "pastel", "earthy"}, {"all"}, {"traditional", "semi-formal"},
         {"elegant", "cultural"}, {"moderate"}, {"juttis", "mojari"},
         {"jhumkas", "bangles", "statement ring"}, 1800},

        {"Linen shirt + chinos + loafers", "smart casual",
         {"office", "brunch", "date"}, {"hot", "mild"}, {"all"},
         {"neutral", "pastel", "earthy"}, {"male", "female", "non-binary"}, {"smart casual"},
         {"clean", "smart"}, {"high"}, {"loafers", "sneakers"},
         {"leather strap watch", "minimal chain", "simple studs"}, 2000},

        {"Monochrome co-ord set + statement belt", "trend",
         {"party", "date", "shopping"}, {"mild", "hot"}, {"all"},
         {"black", "neutral", "jewel"}, {"female", "non-binary"}, {"casual", "semi-formal"},
         {"bold", "fashion"}, {"moderate"}, {"heels", "platform sneakers"},
         {"statement earrings", "stack rings", "layered chain"}, 2300},

        {"Turtleneck + overcoat + tailored pants", "winter formal",
         {"office", "formal dinner", "event"}, {"cold"}, {"all"},
         {"neutral", "black", "blue"}, {"all"}, {"formal", "smart casual"},
         {"polished", "elevated"}, {"low"}, {"boots", "oxfords"},
         {"metal watch", "signet ring", "minimal chain"}, 3200},

        {"Breathable cotton shirt + relaxed shorts + sandals", "summer casual",
         {"beach", "travel", "casual outing"}, {"hot"}, {"all"},
         {"pastel", "earthy", "white"}, {"all"}, {"casual"},
         {"relaxed", "easy"}, {"high"}, {"sandals", "slip-ons"},
         {"anklet", "bead bracelet", "light chain"}, 900},

        {"Structured jumpsuit + blazer", "power look",
         {"office", "presentation", "formal dinner"}, {"mild", "cold"}, {"rectangle", "hourglass", "all"},
         {"black", "neutral", "jewel"}, {"female", "non-binary"}, {"formal", "semi-formal"},
         {"sharp", "confident"}, {"moderate"}, {"pumps", "pointed flats"},
         {"stud earrings", "sleek cuff", "pendant"}, 2800},

        {"Hoodie + joggers + chunky sneakers", "athleisure",
         {"travel", "college", "casual outing"}, {"mild", "cold"}, {"all"},
         {"neutral", "black", "earthy"}, {"all"}, {"casual"},
         {"sporty", "street"}, {"high"}, {"chunky sneakers", "running shoes"},
         {"smartwatch", "cap", "rubber band bracelet"}, 1500}
    };
}

int scoreOutfit(const Outfit &outfit, const UserInput &user, mt19937 &rng) {
    int score = 0;

    if (contains(outfit.genders, "all") || contains(outfit.genders, user.gender)) {
        score += 12;
    }

    if (contains(outfit.occasions, user.occasion)) {
        score += 18;
    }

    if (contains(outfit.weatherTags, user.weather)) {
        score += 16;
    }

    if (contains(outfit.bodyTypes, "all") || contains(outfit.bodyTypes, user.bodyType)) {
        score += 10;
    }

    if (contains(outfit.colorPalettes, user.colorPreference)) {
        score += 12;
    }

    if (contains(outfit.dressCodes, user.dressCode)) {
        score += 12;
    }

    if (user.comfortVsStyle <= 4 && contains(outfit.comfortTags, "high")) {
        score += 12;
    } else if (user.comfortVsStyle >= 7 && contains(outfit.styleTags, "bold")) {
        score += 9;
    } else {
        score += 5;
    }

    if (user.wantsLayers && (contains(outfit.weatherTags, "cold") || contains(outfit.weatherTags, "mild"))) {
        score += 7;
    }

    if (user.budget >= outfit.minBudget) {
        score += 9;
    } else if (user.budget + 500 >= outfit.minBudget) {
        score += 4;
    } else {
        score -= 8;
    }

    // Tiny controlled randomness helps avoid repetitive identical ranking.
    uniform_int_distribution<int> jitter(-3, 3);
    score += jitter(rng);

    return score;
}

string pickRandom(const vector<string> &items, mt19937 &rng) {
    if (items.empty()) {
        return "No suggestion";
    }
    uniform_int_distribution<int> dist(0, static_cast<int>(items.size()) - 1);
    return items[dist(rng)];
}

vector<string> buildFitSuggestions(const UserInput &user, const Outfit &outfit) {
    vector<string> fitSuggestions;

    if (user.comfortVsStyle <= 4) {
        fitSuggestions.push_back("Prioritize relaxed or regular fit for easy movement.");
    } else if (user.comfortVsStyle >= 8) {
        fitSuggestions.push_back("Choose a sharper silhouette: slim/tailored fit for structure.");
    } else {
        fitSuggestions.push_back("Go with a balanced fit: semi-tailored with slight ease.");
    }

    if (user.bodyType == "pear") {
        fitSuggestions.push_back("Use fitted upper + slightly flared/straight lower for proportion.");
    } else if (user.bodyType == "hourglass") {
        fitSuggestions.push_back("Define waist with belt or darted cuts for a clean shape.");
    } else if (user.bodyType == "rectangle") {
        fitSuggestions.push_back("Add structure with layering or waist emphasis to create dimension.");
    } else if (user.bodyType == "athletic") {
        fitSuggestions.push_back("Use tapered bottoms and softer drape on top for balance.");
    } else {
        fitSuggestions.push_back("Choose clean lines with neither extra-tight nor overly loose cuts.");
    }

    if (user.weather == "hot") {
        fitSuggestions.push_back("Pick breathable, anti-cling fabrics with airflow (linen/cotton).");
    } else if (user.weather == "cold") {
        fitSuggestions.push_back("Keep enough room for thermal layers without bulk.");
    } else {
        fitSuggestions.push_back("Mid-weight fabric with light layering gives best all-day fit.");
    }

    if (user.wantsLayers && (outfit.category == "winter formal" || outfit.category == "formal" ||
                             outfit.category == "power look")) {
        fitSuggestions.push_back("For blazers/coats, keep shoulder fit exact and sleeves wrist-length.");
    }

    return fitSuggestions;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937 rng(static_cast<unsigned int>(time(nullptr)));

    vector<string> openingPrompts = {
        "StyleBot online! Let's build your perfect look.",
        "Welcome to Outfit AI Matcher!",
        "Hello! Time to get a personalized outfit combo."
    };
    cout << pickRandom(openingPrompts, rng) << "\n";

    UserInput user;
    cout << "\nTell me your name: ";
    getline(cin, user.name);
    if (user.name.empty()) {
        user.name = "Friend";
    }

    vector<string> genderOptions = {"male", "female", "non-binary", "prefer not to say"};
    user.gender = genderOptions[askOption("Select your gender preference:", genderOptions)];
    if (user.gender == "prefer not to say") {
        user.gender = "all";
    }

    vector<string> occasionOptions = {"office", "college", "wedding", "party", "date", "travel",
                                      "festival", "formal dinner", "shopping", "casual outing", "beach", "presentation"};
    user.occasion = occasionOptions[askOption("What is the occasion?", occasionOptions)];

    vector<string> weatherOptions = {"hot", "mild", "cold"};
    user.weather = weatherOptions[askOption("Current weather condition?", weatherOptions)];

    vector<string> bodyTypeOptions = {"all", "rectangle", "pear", "hourglass", "athletic"};
    user.bodyType = bodyTypeOptions[askOption("Body type (for better fit suggestions):", bodyTypeOptions)];

    vector<string> colorOptions = {"neutral", "black", "blue", "red", "pastel", "jewel", "earthy", "white"};
    user.colorPreference = colorOptions[askOption("Color preference today:", colorOptions)];

    vector<string> dressCodeOptions = {"casual", "smart casual", "semi-formal", "formal", "traditional"};
    user.dressCode = dressCodeOptions[askOption("Expected dress code:", dressCodeOptions)];

    user.comfortVsStyle =
        askIntInRange("Comfort vs Style slider (1 = max comfort, 10 = max style)", 1, 10);

    user.budget = askIntInRange("Budget in INR for the full look", 500, 10000);

    user.wantsLayers = askYesNo("Do you want layering (jackets, shrugs, overcoats)?");

    vector<Outfit> catalog = getOutfitCatalog();
    vector<pair<int, int> > ranked; // {score, index}
    for (size_t i = 0; i < catalog.size(); ++i) {
        int score = scoreOutfit(catalog[i], user, rng);
        ranked.push_back(make_pair(score, static_cast<int>(i)));
    }

    sort(ranked.begin(), ranked.end(), greater<pair<int, int> >());

    vector<string> outroTitles = {
        "Top AI-picked outfit combos for you:",
        "Best matches crafted from your preferences:",
        "Here are your highest scoring style picks:"
    };

    cout << "\n" << pickRandom(outroTitles, rng) << "\n";
    cout << "---------------------------------------------\n";

    int showCount = min(3, static_cast<int>(ranked.size()));
    for (int i = 0; i < showCount; ++i) {
        const Outfit &choice = catalog[ranked[i].second];
        int score = ranked[i].first;

        string footwear = pickRandom(choice.footwearOptions, rng);
        string jewelry = pickRandom(choice.jewelryOptions, rng);
        vector<string> fitSuggestions = buildFitSuggestions(user, choice);
        string fitPick = pickRandom(fitSuggestions, rng);

        cout << "\nOption " << (i + 1) << ": " << choice.name << "\n";
        cout << "AI Score: " << score << "/100 (relative match score)\n";
        cout << "Fit suggestion: " << fitPick << "\n";
        cout << "Footwear combo: " << footwear << "\n";
        cout << "Jewelry suggestion: " << jewelry << "\n";
        cout << "Estimated budget need: around INR " << choice.minBudget << "+\n";
    }

    vector<string> endingTips = {
        "Pro tip: switch one accessory color to create a fresh variant instantly.",
        "Try mixing one bold piece with one neutral piece for a premium look.",
        "For photos, pick one metallic jewelry item to elevate the outfit."
    };
    cout << "\n" << pickRandom(endingTips, rng) << "\n";
    cout << "\nThanks, " << user.name << "! Run again anytime for new combinations.\n";

    return 0;
}
