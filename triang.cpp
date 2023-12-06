#include "triang.h"

void Triang::getOption() {
    po::options_description desc("Allowed options");
    desc.add_options()("help,h", "produce help message");
    desc.add_options()("input,i", po::value<std::string>(), "set input file");
    desc.add_options()("output,o", po::value<std::string>(), "set output file");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
    } catch (po::error& e) {
        std::cout << e.what() << std::endl;
        std::cout << desc << std::endl;
    }
    if (vm.count("help"))
        std::cout << desc << std::endl;

    if (vm.count("input")) {
        iFile = vm["input"].as<std::string>();
        openFile();
    }

    if (vm.count("output"))
        oFile = vm["output"].as<std::string>();
}

void Triang::openFile() {
    std::ifstream fin(iFile, std::ios_base::in);

    if (!fin.is_open())
        throw std::ifstream::failure("Failed to open the file");

    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        int id;
        double x, y, z;
        char comma;
        if (iss >> id >> comma >> x >> comma >> y >> comma >> z) {
            Point point(x, y, z);
            pointCloud.emplace_back(point);
            idPoints[point] = id;
        } else {
            // std::cout << "Error reading line: " << line << std::endl;
        }
    }

    fin.close();
}

void Triang::createPoly() {
    std::ofstream ofs(oFile, std::ios::out);

    if (!ofs.is_open())
        throw std::ofstream::failure("Failed to open the file for writing");

    Delaunay dt(pointCloud.begin(), pointCloud.end());

    ofs << std::fixed << std::setprecision(6);
    ofs << "*   N,            X             Y             Z\n";
    ofs << "*Nodes\n";
    int nodes_index = 1;
    for (auto it = pointCloud.begin(); it != pointCloud.end(); ++it) {
        ofs << nodes_index++ << "," << std::setw(15) << it->x() << ","
            << std::setw(15) << it->y() << "," << std::setw(15) << it->z()
            << "\n";
    }

    ofs << "\n*Elements\n";
    int element_index = 1;
    for (auto it = dt.finite_cells_begin(); it != dt.finite_cells_end(); ++it) {
        ofs << element_index++ << "," << std::setw(15)
            << idPoints[it->vertex(0)->point()] << "," << std::setw(15)
            << idPoints[it->vertex(1)->point()] << "," << std::setw(15)
            << idPoints[it->vertex(2)->point()] << "\n";
    }

    ofs.close();
}
