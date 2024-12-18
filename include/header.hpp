#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "tree.hpp"
struct point {
  double x;
  double y;
  point(double x = 0, double y = 0) : x(x), y(y) {}
  bool operator==(const point& rhs) { return rhs.x == x && rhs.y == y; }
};
struct line_segment {
  point start;
  point stop;
  size_t loc_id = 0;
  static size_t id;
  line_segment(double p1, double q1, double p2, double q2) : start{p1, q1}, stop{p2, q2} {};

  line_segment(point& p1, point& p2) {
    std::swap(p1, start);
    std::swap(p2, stop);
    loc_id = ++id;
  }
  line_segment(){};
};
size_t line_segment::id = 0;

class plain_naive {
  std::vector<line_segment> segs;

  bool check_collinear(const point& p1, const point& q1, const point& p2, const point& q2) {
    return std::max(p1.x, q1.x) >= std::min(p2.x, q2.x) && std::min(p1.x, q1.x) <= std::max(p2.x, q2.x) &&
           std::max(p1.y, q1.y) >= std::min(p2.y, q2.y) && std::min(p1.y, q1.y) <= std::max(p2.y, q2.y);
  }

  double crossProduct(const point& A, const point& B, const point& C) noexcept {
    return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
  }

  bool intersect(const line_segment& seg1, const line_segment& seg2) noexcept {
    const point& p1 = seg1.start;
    const point& q1 = seg1.stop;
    const point& p2 = seg2.start;
    const point& q2 = seg2.stop;
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

 public:
  plain_naive() { segs.reserve(100); }

  plain_naive(std::vector<line_segment>& vec) {
    for (auto&& seg : vec) add_seg(seg);
  }
  bool find_intersect(size_t& f, size_t& s) {
    auto size = segs.size();

    for (int i = 0; i < size - 1; ++i) {
      for (int j = i + 1; j < size; ++j) {
        if (intersect(segs[i], segs[j])) {
          f = segs[i].loc_id;
          s = segs[i].loc_id;
#ifdef visual
          std::cout << segs[i].start.x << "  " << segs[i].start.y << "  " << segs[i].stop.x << "  " << segs[i].stop.y
                    << std::endl;
          std::cout << segs[j].start.x << "  " << segs[j].start.y << "  " << segs[j].stop.x << "  " << segs[j].stop.y
                    << std::endl;
#endif
          return true;
        }
      }
    }
    return false;
  }

  void add_seg(point& one, point& two) { segs.emplace_back(one, two); }
  void add_seg(line_segment& seg) { segs.push_back(seg); }
  ~plain_naive(){};
};

struct line_segment_AVL;
struct point_AVL : public point {
  line_segment_AVL* ref_to_line = nullptr;

  point_AVL(double p1, double q1, line_segment_AVL* ref = nullptr) : point{p1, q1}, ref_to_line(ref){};
};
struct line_segment_AVL {
  point_AVL start{0, 0, nullptr};
  point_AVL stop{0, 0, nullptr};
  size_t loc_id = 0;
  static size_t id;
  bool is_in_tree = false;
  line_segment_AVL(double p1, double q1, double p2, double q2) : start{p1, q1, this}, stop{p2, q2, this} {
    loc_id = ++id;
  };

  line_segment_AVL(point_AVL& p1, point_AVL& p2) : start(p1), stop(p2) { loc_id = ++id; }
  line_segment_AVL(){};
};
size_t line_segment_AVL::id = 0;

class plain_AVL {
  struct proxy_for_sort {
    const bool operator()(const point_AVL& lhs, const point_AVL& rhs) const { return lhs.x < rhs.x; }
  };
  std::vector<line_segment_AVL> segs;
  std::vector<point_AVL> points;
  AVL_Tree<double, line_segment_AVL> tree;
  void add_seg(line_segment_AVL& seg) { segs.push_back(seg); }

  bool check_collinear(const point_AVL& p1, const point_AVL& q1, const point_AVL& p2, const point_AVL& q2) {
    return std::max(p1.x, q1.x) >= std::min(p2.x, q2.x) && std::min(p1.x, q1.x) <= std::max(p2.x, q2.x) &&
           std::max(p1.y, q1.y) >= std::min(p2.y, q2.y) && std::min(p1.y, q1.y) <= std::max(p2.y, q2.y);
  }

  double crossProduct(const point_AVL& A, const point_AVL& B, const point_AVL& C) noexcept {
    return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
  }

  bool intersect(const line_segment_AVL& seg1, const line_segment_AVL& seg2) noexcept {
    const point_AVL& p1 = seg1.start;
    const point_AVL& q1 = seg1.stop;
    const point_AVL& p2 = seg2.start;
    const point_AVL& q2 = seg2.stop;
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
  std::vector<line_segment_AVL*> ctd;
  bool flag_vec_init = false;

 public:
  plain_AVL(std::vector<line_segment_AVL>& vec) {
    points.reserve(2 * vec.size());
    for (auto&& t : vec) {
      t.start.ref_to_line = &t;
      t.stop.ref_to_line = &t;
      points.push_back(t.start);
      points.push_back(t.stop);
      add_seg(t);
    }
    flag_vec_init = true;
    sort_points();
  }
  plain_AVL() = default;
  void add_seg(point_AVL one, point_AVL two) {
    line_segment_AVL t(one, two);

    segs.push_back(t);
  }
  void add_seg(double x1, double y1, double x2, double y2) { segs.emplace_back(x1, y1, x2, y2); }
  void sort_points() { std::sort(points.begin(), points.end(), proxy_for_sort()); }

  bool find_intersect(size_t& f, size_t& s) {
    sort_points();//std::sort()
    ctd.resize(3);

    for (auto&& point_curr : points)  // 2n instances
    {
      if (!point_curr.ref_to_line->is_in_tree) {
        point_curr.ref_to_line->is_in_tree = true;
        tree.insert(point_curr.y, *point_curr.ref_to_line);//O(log(n))

        tree.find_segs_for_checking(point_curr.x, point_curr.y, ctd); //O(log(n))

        if (ctd[1] != nullptr) {
          if (intersect(*ctd[0], *ctd[1])) { //O(const)
            f = ctd[0]->loc_id;
            s = ctd[1]->loc_id;
            return true;
          }
        }
        if (ctd[2] != nullptr) {
          if (intersect(*ctd[0], *ctd[2])) { //O(const)
            f = ctd[0]->loc_id;
            s = ctd[2]->loc_id;
            return true;
          }
        }
      } else {
        tree.find_segs_for_checking(point_curr.x, point_curr.y, ctd);
        if (ctd[1] != nullptr && ctd[2] != nullptr) {
          if (intersect(*ctd[1], *ctd[2])) { //O(const)
            f = ctd[0]->loc_id;
            s = ctd[1]->loc_id;
            return true;
          }
        }
        tree.remove(point_curr.y); // O(log(n))
      }
    }
    return false;
  };

  ~plain_AVL() {
  
  }
};
