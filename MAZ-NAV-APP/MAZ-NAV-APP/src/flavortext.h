#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#define numberOfConstructiveVerbs 100
#define numberOfDestructiveVerbs 100
#define numberOfNouns 100

std::string constructiveVerbs[] = {
  "Align",
  "Build",
  "Calibrat",
  "Instanc",
  "Configur",
  "Snort",
  "Microwav",
  "Tweak",
  "Wrangl",
  "Hack",

  "Pwn",
  "Boot",
  "Allocat",
  "Bind",
  "Revv",
  "Polish",
  "Fabricat",
  "Ping",
  "Refactor",
  "Load",

  "Quantify",
  "Assembl",
  "Distill",
  "Bak",
  "Receiv",
  "Unlock",
  "Compil",
  "Pressuriz",
  "Chooch",
  "Mak",

  "Engag",
  "Decrypt",
  "Synthesiz",
  "Predict",
  "Analyz",
  "Dispens",
  "Fir",
  "Insert",
  "Align",
  "Encourag",

  "Extrud",
  "Access",
  "Sharpen",
  "Enhanc",
  "Crank",
  "Stack",
  "Craft",
  "Render",
  "Mount",
  "Generat",

  "Implement",
  "Download",
  "Construct",
  "Wow! Amaz",
  "Moisten",
  "Customiz",
  "Compensat",
  "Buffer",
  "Transferr",
  "Induct",

  "Emitt",
  "Unzipp",
  "Squirt",
  "Feed",
  "Buy",
  "Spark",
  "Implant",
  "Triangulat",
  "Inject",
  "Link",
  "Brew",

  "Process",
  "Deploy",
  "Tun",
  "Attach",
  "Train",
  "Ignor",
  "Tapp",
  "Reload",
  "Simulat",
  "Fluff",

  "Fill",
  "Sort",
  "Updat",
  "Upgrad",
  "Prim",
  "Trac",
  "Inflat",
  "Wangjangl",
  "Charg",
  "Crack",

  "Ignor",
  "Activat",
  "Dial",
  "Pimp",
  "Collect",
  "Approach",
  "Approv",
  "Sampl",
  "Energiz",
  "Stuff"
};

std::string destructiveVerbs[] = {
  "Deallocat",
  "Trash",
  "Unplugg",
  "Revok",
  "Forgett",
  "Discard",
  "Dropp",
  "Holster",
  "Shredd",
  "Jettison",

  "Dissolv",
  "Liquidat",
  "Releas",
  "Collimat",
  "Eject",
  "Ditch",
  "Leak",
  "Sell",
  "Banish",
  "Dereferenc",

  "Sacrific",
  "Desolder",
  "Destruct",
  "Decompil",
  "Blow",
  "Disengag",
  "Digest",
  "Smash",
  "Encrypt",
  "Crash",

  "Lock",
  "Purg",
  "Regrett",
  "Rewind",
  "Free",
  "Delet",
  "Clos",
  "Retract",
  "Collaps",
  "Liquefy",

  "Derezz",
  "Stow",
  "Archiv",
  "Suspend",
  "Suppress",
  "Clean",
  "Squash",
  "Secur",
  "Withdraw",
  "Dump",

  "Obfuscat",
  "Break",
  "Scrubb",
  "Abandon",
  "Flatten",
  "Stash",
  "Finish",
  "Evacuat",
  "Scrambl",
  "Recycl",

  "Crush",
  "Zipp",
  "Unload",
  "Disconnect",
  "Loosen",
  "Contain",
  "Debat",
  "Detach",
  "Neutraliz",
  "Salvag",

  "Empty",
  "Hid",
  "Disarm",
  "Pickl",
  "Disregard",
  "Yeet",
  "Scrapp",
  "Deflat",
  "Discharg",
  "Deactivat",

  "Steriliz",
  "Reliev",
  "Nuk",
  "Degauss",
  "Dismiss",
  "Drain",
  "Reject",
  "Nerf",
  "Pay",
  "Return",

  "Unstick",
  "Splitt",
  "Cancell",
  "Sham",
  "Embezzl",
  "Fling",
  "Regrett",
  "Halt",
  "Arrest",
  "Bury"
};

std::string nouns[numberOfNouns] = {
  "content",
  "your mom",
  "the shmoo",
  "API",
  "the BJT man",
  "aesthetics",
  "backstory",
  "tactics",
  "bugs",
  "sauce",

  "warp drive",
  "data",
  "the funk",
  "AI",
  "crystals",
  "spaghetti",
  "fluxgate",
  "electrons",
  "loud noises",
  "wires",

  "bytecode",
  "the truth",
  "magic",
  "hot lava",
  "bits",
  "Brad",
  "Teensy",
  "sensors",
  "photons",
  "signal",

  "the planet",
  "password",
  "chips",
  "circuits",
  "privacy",
  "synergy",
  "widgets",
  "love",
  "packets",
  "reality",

  "lasers",
  "protocols",
  "voltage",
  "registers",
  "puns",
  "dogecoins",
  "kittens",
  "magic smoke",
  "plot device",
  "the core",

  "dank memes",
  "subroutines",
  "radiation",
  "steam",
  "trousers",
  "beer",
  "protocol",
  "one-liners",
  "the Gibson",
  "software",

  "a fat one",
  "holograms",
  "magnets",
  "inductors",
  "resistors",
  "capacitors",
  "viewers",
  "subscribers",
  "sausage",
  "my wife",

  "drama",
  "the future",
  "vectors",
  "the clowns",
  "a Palm Pilot",
  "5G implant",
  "monkeys",
  "breadboard",
  "Patreon",
  "money",

  "the Internet",
  "fluids",
  "the impostor",
  "beats",
  "dopamine",
  "fedora",
  "neural net",
  "comments",
  "ports",
  "you. Yes you",

  "mixtape",
  "[REDACTED]",
  "hot tub",
  "paperwork",
  "Nerf",
  "cyber-doobie",
  "the 1%",
  "the Matrix",
  "variables",
  "IP address"
};

std::string getRandomString(bool isConstructive) {
    int verbIndex, nounIndex;

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    std::string output;
    

    if (isConstructive) {
        // Select a random index for constructive verbs and nouns
        verbIndex = rand() % numberOfConstructiveVerbs;
        nounIndex = rand() % numberOfNouns;
        output.append(constructiveVerbs[verbIndex]);
        output.append("ing ");
        output.append(nouns[nounIndex]);
        return output;
    }
    else {
        // Select a random index for destructive verbs and nouns
        verbIndex = rand() % numberOfDestructiveVerbs;
        nounIndex = rand() % numberOfNouns;

        output.append(destructiveVerbs[verbIndex]);
        output.append("ing ");
        output.append(nouns[nounIndex]);
        return output;
    }
}

