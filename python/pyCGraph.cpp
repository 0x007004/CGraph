#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "CGraph.h"
#include "wrapper/PyWrapperInclude.h"

using namespace CGraph;
namespace py = pybind11;

PYBIND11_MODULE(pyCGraph, m) {
    py::class_<CStatus>(m, "CStatus")
        .def(py::init<>())
        .def("getCode", &CStatus::getCode)
        .def("getInfo", &CStatus::getInfo)
        .def("isOK", &CStatus::isOK);

    py::class_<GPipelinePy, std::unique_ptr<GPipelinePy, py::nodelete> >(m, "GPipeline")
        .def(py::init<>())
        .def("init", &GPipelinePy::init)
        .def("run", &GPipelinePy::run, py::call_guard<py::gil_scoped_release>())
        .def("process", &GPipelinePy::process, py::call_guard<py::gil_scoped_release>(), 
             py::arg("runTimes") = 1)
        .def("destroy", &GPipelinePy::destroy)
        .def("registerGElement", &GPipelinePy::registerGElement,
             py::arg("element"),
             py::arg("depends") = GElementPtrSet{},
             py::arg("name") = CGRAPH_EMPTY,
             py::arg("loop") = CGRAPH_DEFAULT_LOOP_TIMES,
             "register a GElement with dependencies, name, and loop count.");

    py::class_<GElement, GElementPyw, std::unique_ptr<GElement, py::nodelete> >(m, "GElement")
        .def(py::init<>());

    py::class_<GNode, GNodePyw, GElement, std::unique_ptr<GNode, py::nodelete> >(m, "GNode")
        .def(py::init<>())
        .def("getName", &GNode::getName);
}
