#include "pch.h"
#define Py_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <vector>

PyModuleDef HelloModule;
std::string SayHello(std::string& name) {
 
    return "Hello, " + name + "!";
}

PyObject* SayHelloWrap(PyObject* self, PyObject* args)
{
    char* name;
    if (PyArg_ParseTuple(args, "s", &name)){
    std::string temp = name;
    return PyUnicode_FromString((SayHello(temp).c_str()));
   }
    return 0;
}

std::vector<PyMethodDef> methods;
PyMODINIT_FUNC PyInit_HelloModule()
{
    HelloModule.m_name = "MyModule HelloModule";
    HelloModule.m_doc = "This module can say hello";

    PyMethodDef add_method;
    add_method.ml_name = "SayHello";
    add_method.ml_doc = "This is method for saying hello";
    add_method.ml_meth = SayHelloWrap;
    add_method.ml_flags = METH_VARARGS;
    methods.push_back(add_method);

    PyMethodDef terminator{};
    methods.push_back(terminator);

    HelloModule.m_methods = methods.data();
    
    return PyModule_Create(&HelloModule);
}
