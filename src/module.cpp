#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pthread.h>
#include "accumulator.h"

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

int accmulate_integers(py::list l, int n_threads)
{
    std::vector<int> vec;
    vec.reserve(l.size());
    for (auto i : l)
    {
        vec.push_back(i.cast<int>());   
    }
    return accumulate(vec, n_threads);
}

PYBIND11_MODULE(test_module, m) {
    m.doc() = "A simple example module using pybind11";
    m.def("add", &add, "A function that adds two numbers");
    m.def("accmulate_integers", &accmulate_integers, "Add a list of integers with multi threads", py::arg("l"), py::arg("n_threads"));
}