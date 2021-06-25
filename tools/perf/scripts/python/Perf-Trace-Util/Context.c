<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Context.c.  Python पूर्णांकerfaces क्रम perf script.
 *
 * Copyright (C) 2010 Tom Zanussi <tzanussi@gmail.com>
 */

#समावेश <Python.h>
#समावेश "../../../util/trace-event.h"

#अगर PY_MAJOR_VERSION < 3
#घोषणा _PyCapsule_GetPoपूर्णांकer(arg1, arg2) \
  PyCObject_AsVoidPtr(arg1)

PyMODINIT_FUNC initperf_trace_context(व्योम);
#अन्यथा
#घोषणा _PyCapsule_GetPoपूर्णांकer(arg1, arg2) \
  PyCapsule_GetPoपूर्णांकer((arg1), (arg2))

PyMODINIT_FUNC PyInit_perf_trace_context(व्योम);
#पूर्ण_अगर

अटल PyObject *perf_trace_context_common_pc(PyObject *obj, PyObject *args)
अणु
	अटल काष्ठा scripting_context *scripting_context;
	PyObject *context;
	पूर्णांक retval;

	अगर (!PyArg_ParseTuple(args, "O", &context))
		वापस शून्य;

	scripting_context = _PyCapsule_GetPoपूर्णांकer(context, शून्य);
	retval = common_pc(scripting_context);

	वापस Py_BuildValue("i", retval);
पूर्ण

अटल PyObject *perf_trace_context_common_flags(PyObject *obj,
						 PyObject *args)
अणु
	अटल काष्ठा scripting_context *scripting_context;
	PyObject *context;
	पूर्णांक retval;

	अगर (!PyArg_ParseTuple(args, "O", &context))
		वापस शून्य;

	scripting_context = _PyCapsule_GetPoपूर्णांकer(context, शून्य);
	retval = common_flags(scripting_context);

	वापस Py_BuildValue("i", retval);
पूर्ण

अटल PyObject *perf_trace_context_common_lock_depth(PyObject *obj,
						      PyObject *args)
अणु
	अटल काष्ठा scripting_context *scripting_context;
	PyObject *context;
	पूर्णांक retval;

	अगर (!PyArg_ParseTuple(args, "O", &context))
		वापस शून्य;

	scripting_context = _PyCapsule_GetPoपूर्णांकer(context, शून्य);
	retval = common_lock_depth(scripting_context);

	वापस Py_BuildValue("i", retval);
पूर्ण

अटल PyMethodDef ContextMethods[] = अणु
	अणु "common_pc", perf_trace_context_common_pc, METH_VARARGS,
	  "Get the common preempt count event field value."पूर्ण,
	अणु "common_flags", perf_trace_context_common_flags, METH_VARARGS,
	  "Get the common flags event field value."पूर्ण,
	अणु "common_lock_depth", perf_trace_context_common_lock_depth,
	  METH_VARARGS,	"Get the common lock depth event field value."पूर्ण,
	अणु शून्य, शून्य, 0, शून्यपूर्ण
पूर्ण;

#अगर PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initperf_trace_context(व्योम)
अणु
	(व्योम) Py_InitModule("perf_trace_context", ContextMethods);
पूर्ण
#अन्यथा
PyMODINIT_FUNC PyInit_perf_trace_context(व्योम)
अणु
	अटल काष्ठा PyModuleDef moduledef = अणु
		PyModuleDef_HEAD_INIT,
		"perf_trace_context",	/* m_name */
		"",			/* m_करोc */
		-1,			/* m_size */
		ContextMethods,		/* m_methods */
		शून्य,			/* m_reload */
		शून्य,			/* m_traverse */
		शून्य,			/* m_clear */
		शून्य,			/* m_मुक्त */
	पूर्ण;
	वापस PyModule_Create(&moduledef);
पूर्ण
#पूर्ण_अगर
