/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "oxoxox oxox"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 *
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> namelist;
  std::ifstream in(filename);
  std::string line;

  while (std::getline(in, line)) {
    namelist.insert(line);
  }

  return namelist;
}

std::string get_string(const std::string& name) {
  std::string init;
  bool start = true;

  for (char c : name) {
    if (c == ' ') {
      start = true;
    } else if (start) {
      init += c;
      start = false;
    }
  }

  return init;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> matches;
  std::string init_name = get_string(name);

  for (const auto& x : students) {
    if (get_string(x) == init_name) {
      matches.push(&x);
    }
  }

  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  std::string final = "";
  std::size_t min_diff = static_cast<std::size_t>(-1);

  if (matches.empty()) {
    return "NO MATCHES FOUND.";
  }

  auto candidates = matches;

  while (!candidates.empty()) {
    std::string str = *candidates.front();
    std::size_t diff = str.size() >= kYourName.size()
                           ? str.size() - kYourName.size()
                           : kYourName.size() - str.size();
    if (diff < min_diff) {
      min_diff = diff;
      final = str;
    }
    candidates.pop();
  }

  return final;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
