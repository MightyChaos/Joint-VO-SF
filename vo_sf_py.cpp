#include <pybind11/pybind11.h>
#include "joint_vo_sf.h"
// #include "ndarray_converter.h"


int add(int i, int j) {
    return i + j+1000;
}

void vo_sf_imagepair(Eigen::MatrixXf im1, Eigen::MatrixXf depth1, 
    Eigen::MatrixXf im2, Eigen::MatrixXf depth2)
{
    const unsigned int res_factor = 2;
    // print im1(0,0)
	// VO_SF cf(res_factor, 1.4*704, 1.4*704, 704, 384);
    // cf.loadImagePair(im1, depth1, im2, depth2, res_factor);
    // cf.run_VO_SF(false);

}

namespace py = pybind11;

PYBIND11_MODULE(cmake_example, m) {

    // NDArrayConverter::init_numpy();

    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: cmake_example
        .. autosummary::
           :toctree: _generate
           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers
        Some other explanation about the add function.
    )pbdoc");

    m.def("vo_sf_imagepair", &vo_sf_imagepair);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}