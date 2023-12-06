#ifndef TRIANG_H
#define TRIANG_H

#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <boost/program_options.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

namespace po = boost::program_options;

class Triang {
  public:
    using K = CGAL::Exact_predicates_inexact_constructions_kernel;
    using Delaunay = CGAL::Delaunay_triangulation_3<K>;
    using Point = K::Point_3;

    explicit Triang(int argc = 1, char** argv = nullptr) : ac(argc), av(argv) {}
    ~Triang() {}

    void getOption();
    void openFile();
    void createPoly();

  private:
    int ac;
    char** av;
    std::string iFile;
    std::string oFile;
    std::vector<Point> pointCloud;
    std::map<Point, int> idPoints;

}; // namespace Triang

#endif // TRIANG_H