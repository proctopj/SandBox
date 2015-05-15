#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <omp.h>

std::vector<int> col_sums(const std::vector<std::vector<short>>& data) {
    unsigned int height = data.size(), width = data[0].size();
    std::vector<int> totalSums(width, 0), threadSums(width, 0);

    #pragma omp parallel firstprivate(threadSums)
    {
        #pragma omp for
        for (unsigned int i = 0; i < height; i++) {
            threadSums.data()[0:width] += data[i].data()[0:width];
        }
        #pragma omp atomic
        totalSums.data()[0:width] += threadSums.data()[0:width];
    }
    return totalSums;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Run program as \"executable <rows> <columns>\n";
    } else {
        std::stringstream args;
        args << argv[1] << " " << argv[2];
        int rows, columns;
        args >> rows >> columns;
        std::vector<std::vector<short>> data(rows, std::vector<short>(columns));
        std::vector<int> columnSums = col_sums(data);
    }
}    
