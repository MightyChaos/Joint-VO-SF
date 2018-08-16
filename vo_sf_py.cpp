#include <pybind11/pybind11.h>
#include "joint_vo_sf.h"
#include <pybind11/eigen.h>
// #include "ndarray_converter.h"


int add(int i, int j) {
    return i + j+1000;
}

auto vo_sf_imagepair(Eigen::MatrixXf &im1, Eigen::MatrixXf &depth1, 
Eigen::MatrixXf &im2, Eigen::MatrixXf &depth2,
double fx, double fy)
{
    const unsigned int res_factor = 2;
    std::cout<<im1(0,0);
    int imH = im1.rows();
    int imW = im1.cols();
    std::cout<<imH<<" "<<imW<<std::endl;
	VO_SF cf(res_factor, fx, fy, imW, imH);

    cf.loadImagePair(im1, depth1, im2, depth2, res_factor);
    cf.run_VO_SF(false);
    Eigen::MatrixXf T_clusters(NUM_LABELS*4,4);
    // int data_head = 0;
    for(int i=0; i<NUM_LABELS; i++)
    {
        for(int r=0; r<4; r++)
        for(int c=0; c<4; c++)
        {
            T_clusters(i*4+r,c) = cf.T_clusters[i](r,c);
        }
    }
    // std::vector<Eigen::Matrix4f> T_clusters(NUM_LABELS);
    // for(int i=0; i<NUM_LABELS; i++)
    // {
    //     T_clusters.push_back(cf.T_clusters[i]);
    // }
    int max_level = round(log2(cf.width/cf.cols));
    return std::make_tuple(cf.T_odometry, T_clusters, 
        cf.labels[max_level],
        cf.label_static,
        cf.label_dynamic,
        cf.b_segm);

}

namespace py = pybind11;

PYBIND11_MODULE(jvo_util, m) {

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