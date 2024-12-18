#pragma once
#include "header.hpp"

struct random_work_failure : std::exception {};

template <class typePoint, class typeSegment>
class random_segs_generator {
  bool check_collinear(const typePoint& p1, const typePoint& q1, const typePoint& p2, const typePoint& q2) {
    return std::max(p1.x, q1.x) >= std::min(p2.x, q2.x) && std::min(p1.x, q1.x) <= std::max(p2.x, q2.x) &&
           std::max(p1.y, q1.y) >= std::min(p2.y, q2.y) && std::min(p1.y, q1.y) <= std::max(p2.y, q2.y);
  }

  double crossProduct(const typePoint& A, const typePoint& B, const typePoint& C) noexcept {
    return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
  }

  bool intersect(const typeSegment& seg1, const typeSegment& seg2) noexcept {
    const typePoint& p1 = seg1.start;
    const typePoint& q1 = seg1.stop;
    const typePoint& p2 = seg2.start;
    const typePoint& q2 = seg2.stop;
    double d1 = crossProduct(p1, q1, p2);
    double d2 = crossProduct(p1, q1, q2);
    double d3 = crossProduct(p2, q2, p1);
    double d4 = crossProduct(p2, q2, q1);

    // base case
    if ((d1 > 0 && d2 < 0 || d1 < 0 && d2 > 0) && (d3 > 0 && d4 < 0 || d3 < 0 && d4 > 0)) return true;

    // check if both of line_seg are on the same line
    if (d1 == 0 && d2 == 0 && d3 == 0 && d4 == 0) {
      return check_collinear(p1, q1, p2, q2);
    }

    return false;
  }

  typePoint gen_rand_point(double from, double till) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_x(from, till);
    std::uniform_real_distribution<> dis_y(0, 1);

    return typePoint(dis_x(gen), dis_y(gen));
  }
  void writeLineSegmentsToFile(const std::vector<typeSegment>& segments) {
    std::ofstream file("../../AIAS2/source_folder/outstream.txt");

    if (!file.is_open()) {
      return;
    }

    for (const auto& segment : segments) {
      file << "(" << segment.start.x << "," << segment.start.y << ") "
           << "(" << segment.stop.x << "," << segment.stop.y << ")" << std::endl;
    }

    file.close();
  }

  bool generate_no_intersect_segs(std::vector<typeSegment>& segments, size_t size, size_t start_from, double from_x,
                                  double till_x, int maxAttempts = 100000) {
    int attempts = 0;
    // Check if new seg does not intersect any other existing

    while (attempts < maxAttempts) {
      typeSegment newSegment(gen_rand_point(from_x, till_x), gen_rand_point(from_x, till_x));
      bool intersects = false;
      for (auto i = start_from; i != size; ++i) {
        if (intersect(segments[i], newSegment)) {
          intersects = true;
          break;
        }
      }
      if (!intersects) {
        if (newSegment.start.x > newSegment.stop.x) {
          std::swap(newSegment.start, newSegment.stop);
        }
        segments.push_back(newSegment);
        return true;
      }
      attempts++;
    }
    return false;
  }

  // create seg k+1 intersecting k+2 seg
  void generate_intersecting_segs(std::vector<typeSegment>& segments, double from_x, double till_x) {
    typePoint p1 = gen_rand_point(from_x, till_x);
    typePoint p2 = gen_rand_point(from_x, till_x);
    typePoint p3 = gen_rand_point(from_x, till_x);
    typePoint p4 = gen_rand_point(from_x, till_x);

    typeSegment seg1(p1, p2);
    typeSegment seg2(p3, p4);

    while (!intersect(seg1, seg2)) {
      p3 = gen_rand_point(from_x, till_x);
      p4 = gen_rand_point(from_x, till_x);
      seg2 = typeSegment(p3, p4);
    }
    if (seg1.start.x > seg1.stop.x) std::swap(seg1.start, seg1.stop);
    if (seg2.start.x > seg2.stop.x) std::swap(seg2.start, seg2.stop);
    segments.push_back(seg1);
    segments.push_back(seg2);
    //std::cout << seg1.loc_id << "  " << seg2.loc_id << std::endl;
    //auto t = seg1;
    //std::cout << t.start.x << ' ' << t.start.y << "  " << t.stop.x << ' ' << t.stop.y << std::endl;
    //t = seg2;
    //std::cout << t.start.x << ' ' << t.start.y << "  " << t.stop.x << ' ' << t.stop.y << std::endl;
  }

  void generate_random_segs_not_specified_k(std::vector<typeSegment>& segments) {
    typePoint p1 = gen_rand_point(0, 1);
    typePoint p2 = gen_rand_point(0, 1);

    typeSegment seg1(p1, p2);
    if (seg1.start.x > seg1.stop.x) std::swap(seg1.start, seg1.stop);
    segments.push_back(seg1);
  }

  double rand_angle(int left, int right) { 
     static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_x(left, right);
    return dis_x(rd);
  }

  typeSegment randSegsByLength(double len) {
    double angle = rand_angle(-90, 90);
    while (angle == 90) angle = rand_angle(-90, 90);


    auto point = gen_rand_point(0, 1);
    double middleX = point.x;
    double middleY = point.y;
    double x1 = middleX - len * std::cos(angle) / 2.0;
    double x2 = middleX + len * std::cos(angle) / 2.0;
    double y1 = middleY - len * std::sin(angle) / 2.0;
    double y2 = middleY + len * std::sin(angle) / 2.0;

    typePoint p1(x1, y1), p2(x2, y2);
    return typeSegment(p1, p2);
  }
 public:
  random_segs_generator operator()(std::vector<typeSegment>& vec_input, size_t n, size_t k) {
    double first_k_x = double(k) / double(n);

    for (size_t i = 0; i < k; ++i) {
      if (!generate_no_intersect_segs(vec_input, i, 0, 0, first_k_x)) {
        throw std::exception("could not generate random line segs");
      }
    }
    auto bound_for_intersect = first_k_x + double(3) / double(n); //test
    generate_intersecting_segs(vec_input, first_k_x, bound_for_intersect);
    if (n > 10) {
      size_t left = n - k - 2;
      for (size_t i = 0; i < left; ++i) {
        if (!generate_no_intersect_segs(vec_input, k, 0, bound_for_intersect, 1)) {
          throw std::exception("could not generate random line segs");
        }
      }
    }
  }

  void gener(std::vector<typeSegment>& vec_input, size_t n) {
    for (size_t i = 0; i < n; ++i) {
      generate_random_segs_not_specified_k(vec_input);
    }
  }

  void gener_lenght_segs(std::vector<typeSegment>& vec_input,double lenght,size_t size)
  { 
      for (int n = 0; n < size; n += 10)
      {
        vec_input.push_back(randSegsByLength(lenght));
      }
  }

  void gener_lenght_segs_l_v(std::vector<typeSegment>& vec_input, double lenght, size_t size) {
    for (int n=0 ; n < size; n += 1) {
      vec_input.push_back(randSegsByLength(lenght));
    }
  }
};



