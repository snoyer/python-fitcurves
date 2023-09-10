#include <Python.h>
#include "gems/GraphicsGems.h"

extern void *FitCurve();

void AppendBezierCurve(int n, Point2 *curve, PyObject *list)
{
	PyObject *tuple = PyTuple_New(n + 1);
	for (int i = 0; i <= n; ++i)
		PyTuple_SET_ITEM(tuple, i, PyComplex_FromDoubles(curve[i].x, curve[i].y));
	PyList_Append(list, tuple);
}

static PyObject *method_FitCurve(PyObject *self, PyObject *args)
{
	PyObject *py_points = PyList_New(0);
	double sq_error = 1.;
	int max_points = 1000;

	if (!PyArg_ParseTuple(args, "Odi", &py_points, &sq_error, &max_points))
		return NULL;

	const unsigned long n = Py_SIZE(py_points);
	Point2 c_points[n];
	for (unsigned long i = 0; i < n; ++i)
	{
		PyObject *item = PyList_GET_ITEM(py_points, i);
		if (!PyComplex_Check(item))
			return PyErr_Format(PyExc_ValueError, "expected complex number");

		const Py_complex py_point = PyComplex_AsCComplex(item);
		const Point2 c_point = {py_point.real, py_point.imag};
		c_points[i] = c_point;
	}

	PyObject *py_beziers = PyList_New(0);
	FitCurve(c_points, n, sq_error, max_points, &AppendBezierCurve, py_beziers);
	return py_beziers;
}

static PyMethodDef fitcurves_graphicgems_methods[] = {
	{"FitCurve", method_FitCurve, METH_VARARGS, "..."},
	{NULL, NULL, 0, NULL},
};

static struct PyModuleDef fitcurves_graphicgems_module = {
	PyModuleDef_HEAD_INIT,
	"fitcurves_graphicgems",
	"...",
	-1,
	fitcurves_graphicgems_methods};

PyMODINIT_FUNC PyInit_fitcurves_graphicgems(void)
{
	return PyModule_Create(&fitcurves_graphicgems_module);
}
