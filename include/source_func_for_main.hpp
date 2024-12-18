#include "tests_header.hpp"

namespace func_for_main {

void writeToFile(double value1, size_t value2, size_t value3,
                 const std::string& filename = "../../AIAS2/source_folder/outstream.txt") {
  std::ofstream file(filename, std::ios::app);

  if (!file.is_open()) {
    std::cerr << "could not open file !" << std::endl;
    return;
  }
  file << value1 << " -> " << value2 << "\t" << value3 << "\n";

  file.close();
}

void calculate_routine_autogen_k_varies(size_t N) {
  std::cout << "k varies " << std::endl;
  std::vector<line_segment_AVL> temp2;
  std::vector<line_segment> temp;
  random_segs_generator<point_AVL, line_segment_AVL> random_segments_generator2;

  size_t f = 0, s = 0;
  for (size_t k = 1; k < 10001; k += 100) {
    temp2.reserve(N);
    random_segments_generator2(temp2, N, k);

    plain_AVL plain(temp2);
    temp.reserve(N);

    auto clock = std::clock();
    plain.find_intersect(f, s);
    // std::cout<< "  " << f << "  " << s << ":  ";

    auto clock1 = std::clock() - clock;

    for (auto&& t : temp2) {
      temp.emplace_back(t.start, t.stop);
      temp.back().loc_id = t.loc_id;
    }

    plain_naive plain_base(temp);
    clock = std ::clock();
    plain_base.find_intersect(f, s);
    // std::cout << "  " << f << "  " << s << ":  ";
    clock = std::clock() - clock;
    writeToFile(k, clock1, clock, "../../AIAS2/source_folder/outstream2.txt");
    temp.clear();
    temp2.clear();
    line_segment::id = 0;
    line_segment_AVL::id = 0;
    std::cout << std::endl << std::endl;
  }
}

void calculate_routine_autogen_k_not_defined(size_t N) {
  std::cout << "k not defined default routine" << std ::endl;
  std::vector<line_segment_AVL> temp2;
  std::vector<line_segment> temp;
  random_segs_generator<point_AVL, line_segment_AVL> random_segments_generator2;
  size_t f = 0, s = 0;
  for (size_t n = 10; n < N; n += 100) {
    temp2.reserve(n);
    random_segments_generator2(temp2, n, n-2);
    plain_AVL plain(temp2);
    auto clock = std::clock();
    plain.find_intersect(f, s);
    // std::cout<< "  " << f << "  " << s << ":  ";

    auto clock1 = std::clock() - clock;

    temp.reserve(n);
    for (auto&& t : temp2) {
      temp.emplace_back(t.start, t.stop);
      temp.back().loc_id = t.loc_id;
    }

    plain_naive plain_base(temp);
    clock = std ::clock();
    plain_base.find_intersect(f, s);
    // std::cout << "  " << f << "  " << s << ":  ";
    clock = std::clock() - clock;
    writeToFile(n, clock1, clock);
    temp.clear();
    temp2.clear();
    line_segment::id = 0;
    line_segment_AVL::id = 0;
    std::cout << std::endl << std::endl;
  }
}

void calculate_routine_autogen_length_base(size_t k, size_t N) {
  std::cout << "length is defined routine" << std ::endl;
  std::vector<line_segment_AVL> temp2;
  std::vector<line_segment> temp;
  random_segs_generator<point_AVL, line_segment_AVL> random_segments_generator2;
  size_t f = 0, s = 0;
  for (size_t n = 1; n < N; n += 100) {
    temp2.reserve(N);
    random_segments_generator2.gener_lenght_segs(temp2, 0.001, n);
    plain_AVL plain(temp2);
    temp.reserve(N);

    auto clock = std::clock();
    plain.find_intersect(f, s);
    // std::cout<< "  " << f << "  " << s << ":  ";

    auto clock1 = std::clock() - clock;

    for (auto&& t : temp2) {
      temp.emplace_back(t.start, t.stop);
      temp.back().loc_id = t.loc_id;
    }

    plain_naive plain_base(temp);
    clock = std ::clock();
    plain_base.find_intersect(f, s);
    // std::cout << "  " << f << "  " << s << ":  ";
    clock = std::clock() - clock;
    writeToFile(n, clock1, clock, "../../AIAS2/source_folder/outstream3.txt");
    temp.clear();
    temp2.clear();
    line_segment::id = 0;
    line_segment_AVL::id = 0;
    std::cout << std::endl << std::endl;
  }
}
void calculate_routine_autogen_length_varies(size_t N) {
  std::cout << "length varies routine" << std ::endl;
  std::vector<line_segment_AVL> temp2;
  std::vector<line_segment> temp;
  random_segs_generator<point_AVL, line_segment_AVL> random_segments_generator2;
  size_t f = 0, s = 0;
  for (double length = 0.0001; length < 0.01; length += 0.0001) {
    temp2.reserve(N);
    random_segments_generator2.gener_lenght_segs_l_v(temp2, length, N);
    plain_AVL plain(temp2);
    temp.reserve(N);

    auto clock = std::clock();
    plain.find_intersect(f, s);
    // std::cout<< "  " << f << "  " << s << ":  ";

    auto clock1 = std::clock() - clock;

    for (auto&& t : temp2) {
      temp.emplace_back(t.start, t.stop);
      temp.back().loc_id = t.loc_id;
    }

    plain_naive plain_base(temp);
    clock = std ::clock();
    plain_base.find_intersect(f, s);
    // std::cout << "  " << f << "  " << s << ":  ";
    clock = std::clock() - clock;
    writeToFile(length, clock1, clock, "../../AIAS2/source_folder/outstream4.txt");
    temp.clear();
    temp2.clear();
    line_segment::id = 0;
    line_segment_AVL::id = 0;
    std::cout << std::endl << std::endl;
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
    std::vector<line_segment> temp;
    for (auto&& t : temp2) {
      temp.emplace_back(t.start, t.stop);
    }
    plain_AVL plain(temp2);
    auto clock = std::clock();
    // std::cout << plain.find_intersect(f, s) << "  " << f << "  " << s << ":  ";

    clock = std::clock() - clock;
    std::cout << n << " -> " << clock << std::endl;

    plain_naive plain_base(temp);
    clock = std::clock();
    // std::cout << plain.find_intersect(f, s) << "  " << f << "  " << s << ":  ";
    clock = std::clock() - clock;
    std::cout << n << " -> " << clock << std::endl;
    temp.clear();
  }
}
void calculate_type_autogen_1(int argc, char** argv) {
  if (argc == 2) {
    size_t N = 10001;
    calculate_routine_autogen_k_not_defined(N);
  }
  std::string argv_t = argv[2];
  if (argv_t == "k_varies") {
    size_t N = 10003;
    calculate_routine_autogen_k_varies(N);
    return;
  } else if (argv_t == "length_test") {
    size_t N = 10001;
    calculate_routine_autogen_length_base(0, N);
  } else if (argv_t == "length_varies") {
    size_t N = 10001;
    calculate_routine_autogen_length_varies(N);
  }
}

void file_read(std::string t) {
  auto fin = std::ifstream();
  if (t == "sample2.txt") fin = std::ifstream("../../AIAS2/source_folder/sample2.txt");
  if (t == "sample.txt") fin = std::ifstream("../../AIAS2/source_folder/sample.txt");
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
}
}  // namespace func_for_main
