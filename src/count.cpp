#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <set>

void toLowerCase(std::string &str)
{
  for(int i=0; i<str.size(); ++i)
    str[i] = std::tolower(str[i]);
}

double median(std::vector<int> const& v)
{
  unsigned const n = v.size();
  if (n % 2) // if odd
    return v[ (n-1)/2  ];
  else if (n > 1)
    return .5*(v[n/2] + v[n/2-1]);
  else return 0.;
}

// Sorted insertion. I use this function to maintain a vector always sorted.
template<class V, class T>
static
typename V::iterator insert_sort(V &vec, T value)
{
  typename V::iterator it = std::lower_bound(vec.begin(), vec.end(), value);
  return vec.insert(it, value);
}

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cout << "usage:\n";
    std::cout << "./count [<file>]\n\n";
    std::cout << "  file           Path to the input file containing the tweets\n";
    return 1;
  }

  std::cout << "executing " << argv[0] << std::endl;

  std::string directory;
  const size_t last_slash_idx = std::string(argv[0]).rfind('/');
  if (std::string::npos != last_slash_idx)
  {
    directory = std::string(argv[0]).substr(0, last_slash_idx);
  }

  std::string tweets;  

  if (argc == 2) 
    tweets = std::string(argv[1]);
  else
    tweets = directory + "/../tweet_input/tweets.txt";

  int max_string_size = 0;
  std::map<std::string, int> table;
  std::string aa = directory + "/../tweet_output/ft1.txt";
  std::string bb = directory + "/../tweet_output/ft2.txt"; 
  std::ofstream wc_result(aa.c_str());
  std::ofstream ft2(bb.c_str());
  std::ifstream file;

  file.open(tweets.c_str());
  if (!file.is_open())
  { 
    std::cerr << "ERROR: file not found "  << tweets << std::endl;
    throw;
  }
  if (!wc_result.is_open())
  {
    std::cerr << "ERROR: can not create ouput file" << std::endl;
    throw;
  };

  std::vector<int> words_per_line;
  std::string line;
  while (std::getline(file, line))
  {
    std::set<std::string> line_words;

    //std::cout << line << std::endl;
    std::istringstream is(line);
    std::string word;
    while (is >> word)
    {
      line_words.insert(word);
      if (max_string_size < word.size())
        max_string_size = word.size();
      std::map<std::string, int>::iterator here = table.find(word);
      if (here == table.end())
        table.insert(std::make_pair(word, 1));
      else
       (*here).second ++;
    }
    insert_sort(words_per_line, line_words.size());
    ft2 << std::fixed << std::setprecision(1) << median(words_per_line) << std::endl;
    //ft2 << median(words_per_line) << std::endl;
  }

  file.close();

  std::map<std::string, int>::iterator it = table.begin();

  for ( ; it != table.end(); ++it)
  {
    wc_result << std::left << std::setw(max_string_size) << std::setfill(' ')        << (*it).first;
    wc_result << " " << (*it).second << std::endl;
  }

  wc_result.close();

}


