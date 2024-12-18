#include "tests_header.hpp"


void calculate_routine_autogen_k_varies(size_t N) {
  std::cout << "k varies " << std::endl;
  std::vector<line_segment_AVL> temp2;
  random_segs_generator<point_AVL, line_segment_AVL> random_segments_generator2;
  size_t f = 0, s = 0;
  for (size_t k = 1; k < 10001; k += 100) {
    temp2.reserve(N);
    random_segments_generator2(temp2, N, k);
    plain_AVL plain(temp2);
    auto clock = std::clock();
    std::cout << plain.find_intersect(f, s) << "  " << f << "  " << s << ":  ";

    clock = std::clock() - clock;
    std::cout << k << " -> " << clock << std::endl;

    std::vector<line_segment> temp;
    for (auto&& t : temp2) {
      temp.emplace_back(t.start, t.stop);
    }

    plain_naive plain_base(temp);
    clock = std::clock();
    std::cout << plain.find_intersect(f, s) << "  " << f << "  " << s << ":  ";
    clock = std::clock() - clock;
    std::cout << k << " -> " << clock << std::endl;
    temp.clear();
  }
}

void calculate_routine_autogen_k_not_defined(size_t N) {
  std::cout << "k not defined default routine" << std ::endl;
  std::vector<line_segment_AVL> temp2;
  random_segs_generator<point_AVL, line_segment_AVL> random_segments_generator2;
  size_t f = 0, s = 0;
  for (size_t n = 1; n < N; n += 100) {
    temp2.reserve(N);
    random_segments_generator2(temp2, N, n / 2);
    plain_AVL plain(temp2);
    auto clock = std::clock();
    std::cout << plain.find_intersect(f, s) << "  " << f << "  " << s << ":  ";

    clock = std::clock() - clock;
    std::cout << n << " -> " << clock << std::endl;

    std::vector<line_segment> temp;
    for (auto&& t : temp2) {
      temp.emplace_back(t.start, t.stop);
    }

    plain_naive plain_base(temp);
    clock = std::clock();
    std::cout << plain.find_intersect(f, s) << "  " << f << "  " << s << ":  ";
    clock = std::clock() - clock;
    std::cout << n << " -> " << clock << std::endl;
    temp.clear();
  }
}

void calculate_routine_autogen_k_defined(size_t k, size_t N) {
  std::cout << "k is defined routine" << std ::endl;
  std::vector<line_segment_AVL> temp2;
  random_segs_generator<point_AVL, line_segment_AVL> random_segments_generator2;
  size_t f = 0, s = 0;
  for (size_t n = k; n < N; n += 100) {
    temp2.reserve(N);
    random_segments_generator2(temp2, N, k);
    plain_AVL plain(temp2);
    auto clock = std::clock();
    std::cout << plain.find_intersect(f, s) << "  " << f << "  " << s << ":  ";

    clock = std::clock() - clock;
    std::cout << n << " -> " << clock << std::endl;

    std::vector<line_segment> temp;
    for (auto&& t : temp2) {
      temp.emplace_back(t.start, t.stop);
    }

    plain_naive plain_base(temp);
    clock = std::clock();
    std::cout << plain.find_intersect(f, s) << "  " << f << "  " << s << ":  ";
    clock = std::clock() - clock;
    std::cout << n << " -> " << clock << std::endl;
    temp.clear();
  }
}
void calculate_type_autogen_1(char** argv) {
  std::string argv_t = argv[2];
  if (argv_t == "k_varies") {
    size_t N = 10003;
    calculate_routine_autogen_k_varies(N);
    return;
  }
  if (!std::stoi(argv[2])) {
    size_t N = 10001;
    calculate_routine_autogen_k_not_defined(N);
  } else {
    size_t N = 10001;
    calculate_routine_autogen_k_defined(std::stoi(argv_t), N);
  }
}

void file_read(std::string t) {
  auto fin = std::ifstream();
  if (t == "sample2.txt") 
      fin = std::ifstream("../../AIAS2/source_folder/sample2.txt");
  if (t == "sample.txt") 
      fin = std::ifstream("../../AIAS2/source_folder/sample.txt");
  if (fin.is_open()) {
    std::stringstream ss;
    std::string temp;
    plain_naive plain;
    plain_AVL avl_p;

    char ignore;
    double x1, y1, x2, y2;
    while (std::getline(fin, temp)) {
      ss.str(temp);
      ss >> ignore >> x1 >> ignore >> y1 >> ignore >> ignore >> x2 >> ignore >> y2 >> ignore;
      if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
      }
      point f{x1, y1};
      point s{x2, y2};
      plain.add_seg(f, s);
      point_AVL fir(x1, y1);
      point_AVL sec(x2, y2);
      avl_p.add_seg(fir, sec);
    }
  }
#ifdef visual
  std::cout << (plain.find_intersect() ? "there`s intersection (n^2 impl)" : "there`s NO intersection (n^2 impl)")
            << "  " << std::endl;

  bool tmp = avl_p.find_intersect();
  std::cout << (tmp ? "there`s intersection (nlogn impl)" : "there`s NO intersection (nlogn impl)");
#endif
}


