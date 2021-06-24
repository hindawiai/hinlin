<शैली गुरु>
/*
 * trace-event-python.  Feed trace events to an embedded Python पूर्णांकerpreter.
 *
 * Copyright (C) 2010 Tom Zanussi <tzanussi@gmail.com>
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#समावेश <Python.h>

#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <stdbool.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/compiler.h>
#समावेश <linux/समय64.h>

#समावेश "../build-id.h"
#समावेश "../counts.h"
#समावेश "../debug.h"
#समावेश "../dso.h"
#समावेश "../callchain.h"
#समावेश "../evsel.h"
#समावेश "../event.h"
#समावेश "../thread.h"
#समावेश "../comm.h"
#समावेश "../machine.h"
#समावेश "../db-export.h"
#समावेश "../thread-stack.h"
#समावेश "../trace-event.h"
#समावेश "../call-path.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "thread_map.h"
#समावेश "print_binary.h"
#समावेश "stat.h"
#समावेश "mem-events.h"

#अगर PY_MAJOR_VERSION < 3
#घोषणा _PyUnicode_FromString(arg) \
  PyString_FromString(arg)
#घोषणा _PyUnicode_FromStringAndSize(arg1, arg2) \
  PyString_FromStringAndSize((arg1), (arg2))
#घोषणा _PyBytes_FromStringAndSize(arg1, arg2) \
  PyString_FromStringAndSize((arg1), (arg2))
#घोषणा _PyLong_FromLong(arg) \
  PyInt_FromLong(arg)
#घोषणा _PyLong_AsLong(arg) \
  PyInt_AsLong(arg)
#घोषणा _PyCapsule_New(arg1, arg2, arg3) \
  PyCObject_FromVoidPtr((arg1), (arg2))

PyMODINIT_FUNC initperf_trace_context(व्योम);
#अन्यथा
#घोषणा _PyUnicode_FromString(arg) \
  PyUnicode_FromString(arg)
#घोषणा _PyUnicode_FromStringAndSize(arg1, arg2) \
  PyUnicode_FromStringAndSize((arg1), (arg2))
#घोषणा _PyBytes_FromStringAndSize(arg1, arg2) \
  PyBytes_FromStringAndSize((arg1), (arg2))
#घोषणा _PyLong_FromLong(arg) \
  PyLong_FromLong(arg)
#घोषणा _PyLong_AsLong(arg) \
  PyLong_AsLong(arg)
#घोषणा _PyCapsule_New(arg1, arg2, arg3) \
  PyCapsule_New((arg1), (arg2), (arg3))

PyMODINIT_FUNC PyInit_perf_trace_context(व्योम);
#पूर्ण_अगर

#घोषणा TRACE_EVENT_TYPE_MAX				\
	((1 << (माप(अचिन्हित लघु) * 8)) - 1)

अटल DECLARE_BITMAP(events_defined, TRACE_EVENT_TYPE_MAX);

#घोषणा MAX_FIELDS	64
#घोषणा N_COMMON_FIELDS	7

बाह्य काष्ठा scripting_context *scripting_context;

अटल अक्षर *cur_field_name;
अटल पूर्णांक zero_flag_atom;

अटल PyObject *मुख्य_module, *मुख्य_dict;

काष्ठा tables अणु
	काष्ठा db_export	dbe;
	PyObject		*evsel_handler;
	PyObject		*machine_handler;
	PyObject		*thपढ़ो_handler;
	PyObject		*comm_handler;
	PyObject		*comm_thपढ़ो_handler;
	PyObject		*dso_handler;
	PyObject		*symbol_handler;
	PyObject		*branch_type_handler;
	PyObject		*sample_handler;
	PyObject		*call_path_handler;
	PyObject		*call_वापस_handler;
	PyObject		*synth_handler;
	PyObject		*context_चयन_handler;
	bool			db_export_mode;
पूर्ण;

अटल काष्ठा tables tables_global;

अटल व्योम handler_call_die(स्थिर अक्षर *handler_name) __noवापस;
अटल व्योम handler_call_die(स्थिर अक्षर *handler_name)
अणु
	PyErr_Prपूर्णांक();
	Py_FatalError("problem in Python trace event handler");
	// Py_FatalError करोes not वापस
	// but we have to make the compiler happy
	पात();
पूर्ण

/*
 * Insert val पूर्णांकo पूर्णांकo the dictionary and decrement the reference counter.
 * This is necessary क्रम dictionaries since PyDict_SetItemString() करोes not
 * steal a reference, as opposed to PyTuple_SetItem().
 */
अटल व्योम pydict_set_item_string_decref(PyObject *dict, स्थिर अक्षर *key, PyObject *val)
अणु
	PyDict_SetItemString(dict, key, val);
	Py_DECREF(val);
पूर्ण

अटल PyObject *get_handler(स्थिर अक्षर *handler_name)
अणु
	PyObject *handler;

	handler = PyDict_GetItemString(मुख्य_dict, handler_name);
	अगर (handler && !PyCallable_Check(handler))
		वापस शून्य;
	वापस handler;
पूर्ण

अटल पूर्णांक get_argument_count(PyObject *handler)
अणु
	पूर्णांक arg_count = 0;

	/*
	 * The attribute क्रम the code object is func_code in Python 2,
	 * whereas it is __code__ in Python 3.0+.
	 */
	PyObject *code_obj = PyObject_GetAttrString(handler,
		"func_code");
	अगर (PyErr_Occurred()) अणु
		PyErr_Clear();
		code_obj = PyObject_GetAttrString(handler,
			"__code__");
	पूर्ण
	PyErr_Clear();
	अगर (code_obj) अणु
		PyObject *arg_count_obj = PyObject_GetAttrString(code_obj,
			"co_argcount");
		अगर (arg_count_obj) अणु
			arg_count = (पूर्णांक) _PyLong_AsLong(arg_count_obj);
			Py_DECREF(arg_count_obj);
		पूर्ण
		Py_DECREF(code_obj);
	पूर्ण
	वापस arg_count;
पूर्ण

अटल व्योम call_object(PyObject *handler, PyObject *args, स्थिर अक्षर *die_msg)
अणु
	PyObject *retval;

	retval = PyObject_CallObject(handler, args);
	अगर (retval == शून्य)
		handler_call_die(die_msg);
	Py_DECREF(retval);
पूर्ण

अटल व्योम try_call_object(स्थिर अक्षर *handler_name, PyObject *args)
अणु
	PyObject *handler;

	handler = get_handler(handler_name);
	अगर (handler)
		call_object(handler, args, handler_name);
पूर्ण

अटल व्योम define_value(क्रमागत tep_prपूर्णांक_arg_type field_type,
			 स्थिर अक्षर *ev_name,
			 स्थिर अक्षर *field_name,
			 स्थिर अक्षर *field_value,
			 स्थिर अक्षर *field_str)
अणु
	स्थिर अक्षर *handler_name = "define_flag_value";
	PyObject *t;
	अचिन्हित दीर्घ दीर्घ value;
	अचिन्हित n = 0;

	अगर (field_type == TEP_PRINT_SYMBOL)
		handler_name = "define_symbolic_value";

	t = PyTuple_New(4);
	अगर (!t)
		Py_FatalError("couldn't create Python tuple");

	value = eval_flag(field_value);

	PyTuple_SetItem(t, n++, _PyUnicode_FromString(ev_name));
	PyTuple_SetItem(t, n++, _PyUnicode_FromString(field_name));
	PyTuple_SetItem(t, n++, _PyLong_FromLong(value));
	PyTuple_SetItem(t, n++, _PyUnicode_FromString(field_str));

	try_call_object(handler_name, t);

	Py_DECREF(t);
पूर्ण

अटल व्योम define_values(क्रमागत tep_prपूर्णांक_arg_type field_type,
			  काष्ठा tep_prपूर्णांक_flag_sym *field,
			  स्थिर अक्षर *ev_name,
			  स्थिर अक्षर *field_name)
अणु
	define_value(field_type, ev_name, field_name, field->value,
		     field->str);

	अगर (field->next)
		define_values(field_type, field->next, ev_name, field_name);
पूर्ण

अटल व्योम define_field(क्रमागत tep_prपूर्णांक_arg_type field_type,
			 स्थिर अक्षर *ev_name,
			 स्थिर अक्षर *field_name,
			 स्थिर अक्षर *delim)
अणु
	स्थिर अक्षर *handler_name = "define_flag_field";
	PyObject *t;
	अचिन्हित n = 0;

	अगर (field_type == TEP_PRINT_SYMBOL)
		handler_name = "define_symbolic_field";

	अगर (field_type == TEP_PRINT_FLAGS)
		t = PyTuple_New(3);
	अन्यथा
		t = PyTuple_New(2);
	अगर (!t)
		Py_FatalError("couldn't create Python tuple");

	PyTuple_SetItem(t, n++, _PyUnicode_FromString(ev_name));
	PyTuple_SetItem(t, n++, _PyUnicode_FromString(field_name));
	अगर (field_type == TEP_PRINT_FLAGS)
		PyTuple_SetItem(t, n++, _PyUnicode_FromString(delim));

	try_call_object(handler_name, t);

	Py_DECREF(t);
पूर्ण

अटल व्योम define_event_symbols(काष्ठा tep_event *event,
				 स्थिर अक्षर *ev_name,
				 काष्ठा tep_prपूर्णांक_arg *args)
अणु
	अगर (args == शून्य)
		वापस;

	चयन (args->type) अणु
	हाल TEP_PRINT_शून्य:
		अवरोध;
	हाल TEP_PRINT_ATOM:
		define_value(TEP_PRINT_FLAGS, ev_name, cur_field_name, "0",
			     args->atom.atom);
		zero_flag_atom = 0;
		अवरोध;
	हाल TEP_PRINT_FIELD:
		मुक्त(cur_field_name);
		cur_field_name = strdup(args->field.name);
		अवरोध;
	हाल TEP_PRINT_FLAGS:
		define_event_symbols(event, ev_name, args->flags.field);
		define_field(TEP_PRINT_FLAGS, ev_name, cur_field_name,
			     args->flags.delim);
		define_values(TEP_PRINT_FLAGS, args->flags.flags, ev_name,
			      cur_field_name);
		अवरोध;
	हाल TEP_PRINT_SYMBOL:
		define_event_symbols(event, ev_name, args->symbol.field);
		define_field(TEP_PRINT_SYMBOL, ev_name, cur_field_name, शून्य);
		define_values(TEP_PRINT_SYMBOL, args->symbol.symbols, ev_name,
			      cur_field_name);
		अवरोध;
	हाल TEP_PRINT_HEX:
	हाल TEP_PRINT_HEX_STR:
		define_event_symbols(event, ev_name, args->hex.field);
		define_event_symbols(event, ev_name, args->hex.size);
		अवरोध;
	हाल TEP_PRINT_INT_ARRAY:
		define_event_symbols(event, ev_name, args->पूर्णांक_array.field);
		define_event_symbols(event, ev_name, args->पूर्णांक_array.count);
		define_event_symbols(event, ev_name, args->पूर्णांक_array.el_size);
		अवरोध;
	हाल TEP_PRINT_STRING:
		अवरोध;
	हाल TEP_PRINT_TYPE:
		define_event_symbols(event, ev_name, args->typecast.item);
		अवरोध;
	हाल TEP_PRINT_OP:
		अगर (म_भेद(args->op.op, ":") == 0)
			zero_flag_atom = 1;
		define_event_symbols(event, ev_name, args->op.left);
		define_event_symbols(event, ev_name, args->op.right);
		अवरोध;
	शेष:
		/* gcc warns क्रम these? */
	हाल TEP_PRINT_BSTRING:
	हाल TEP_PRINT_DYNAMIC_ARRAY:
	हाल TEP_PRINT_DYNAMIC_ARRAY_LEN:
	हाल TEP_PRINT_FUNC:
	हाल TEP_PRINT_BITMASK:
		/* we should warn... */
		वापस;
	पूर्ण

	अगर (args->next)
		define_event_symbols(event, ev_name, args->next);
पूर्ण

अटल PyObject *get_field_numeric_entry(काष्ठा tep_event *event,
		काष्ठा tep_क्रमmat_field *field, व्योम *data)
अणु
	bool is_array = field->flags & TEP_FIELD_IS_ARRAY;
	PyObject *obj = शून्य, *list = शून्य;
	अचिन्हित दीर्घ दीर्घ val;
	अचिन्हित पूर्णांक item_size, n_items, i;

	अगर (is_array) अणु
		list = PyList_New(field->arraylen);
		item_size = field->size / field->arraylen;
		n_items = field->arraylen;
	पूर्ण अन्यथा अणु
		item_size = field->size;
		n_items = 1;
	पूर्ण

	क्रम (i = 0; i < n_items; i++) अणु

		val = पढ़ो_size(event, data + field->offset + i * item_size,
				item_size);
		अगर (field->flags & TEP_FIELD_IS_SIGNED) अणु
			अगर ((दीर्घ दीर्घ)val >= दीर्घ_न्यून &&
					(दीर्घ दीर्घ)val <= दीर्घ_उच्च)
				obj = _PyLong_FromLong(val);
			अन्यथा
				obj = PyLong_FromLongLong(val);
		पूर्ण अन्यथा अणु
			अगर (val <= दीर्घ_उच्च)
				obj = _PyLong_FromLong(val);
			अन्यथा
				obj = PyLong_FromUnचिन्हितLongLong(val);
		पूर्ण
		अगर (is_array)
			PyList_SET_ITEM(list, i, obj);
	पूर्ण
	अगर (is_array)
		obj = list;
	वापस obj;
पूर्ण

अटल स्थिर अक्षर *get_dsoname(काष्ठा map *map)
अणु
	स्थिर अक्षर *dsoname = "[unknown]";

	अगर (map && map->dso) अणु
		अगर (symbol_conf.show_kernel_path && map->dso->दीर्घ_name)
			dsoname = map->dso->दीर्घ_name;
		अन्यथा
			dsoname = map->dso->name;
	पूर्ण

	वापस dsoname;
पूर्ण

अटल PyObject *python_process_callchain(काष्ठा perf_sample *sample,
					 काष्ठा evsel *evsel,
					 काष्ठा addr_location *al)
अणु
	PyObject *pylist;

	pylist = PyList_New(0);
	अगर (!pylist)
		Py_FatalError("couldn't create Python list");

	अगर (!symbol_conf.use_callchain || !sample->callchain)
		जाओ निकास;

	अगर (thपढ़ो__resolve_callchain(al->thपढ़ो, &callchain_cursor, evsel,
				      sample, शून्य, शून्य,
				      scripting_max_stack) != 0) अणु
		pr_err("Failed to resolve callchain. Skipping\n");
		जाओ निकास;
	पूर्ण
	callchain_cursor_commit(&callchain_cursor);


	जबतक (1) अणु
		PyObject *pyelem;
		काष्ठा callchain_cursor_node *node;
		node = callchain_cursor_current(&callchain_cursor);
		अगर (!node)
			अवरोध;

		pyelem = PyDict_New();
		अगर (!pyelem)
			Py_FatalError("couldn't create Python dictionary");


		pydict_set_item_string_decref(pyelem, "ip",
				PyLong_FromUnचिन्हितLongLong(node->ip));

		अगर (node->ms.sym) अणु
			PyObject *pysym  = PyDict_New();
			अगर (!pysym)
				Py_FatalError("couldn't create Python dictionary");
			pydict_set_item_string_decref(pysym, "start",
					PyLong_FromUnचिन्हितLongLong(node->ms.sym->start));
			pydict_set_item_string_decref(pysym, "end",
					PyLong_FromUnचिन्हितLongLong(node->ms.sym->end));
			pydict_set_item_string_decref(pysym, "binding",
					_PyLong_FromLong(node->ms.sym->binding));
			pydict_set_item_string_decref(pysym, "name",
					_PyUnicode_FromStringAndSize(node->ms.sym->name,
							node->ms.sym->namelen));
			pydict_set_item_string_decref(pyelem, "sym", pysym);
		पूर्ण

		अगर (node->ms.map) अणु
			स्थिर अक्षर *dsoname = get_dsoname(node->ms.map);

			pydict_set_item_string_decref(pyelem, "dso",
					_PyUnicode_FromString(dsoname));
		पूर्ण

		callchain_cursor_advance(&callchain_cursor);
		PyList_Append(pylist, pyelem);
		Py_DECREF(pyelem);
	पूर्ण

निकास:
	वापस pylist;
पूर्ण

अटल PyObject *python_process_brstack(काष्ठा perf_sample *sample,
					काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा branch_stack *br = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	PyObject *pylist;
	u64 i;

	pylist = PyList_New(0);
	अगर (!pylist)
		Py_FatalError("couldn't create Python list");

	अगर (!(br && br->nr))
		जाओ निकास;

	क्रम (i = 0; i < br->nr; i++) अणु
		PyObject *pyelem;
		काष्ठा addr_location al;
		स्थिर अक्षर *dsoname;

		pyelem = PyDict_New();
		अगर (!pyelem)
			Py_FatalError("couldn't create Python dictionary");

		pydict_set_item_string_decref(pyelem, "from",
		    PyLong_FromUnचिन्हितLongLong(entries[i].from));
		pydict_set_item_string_decref(pyelem, "to",
		    PyLong_FromUnचिन्हितLongLong(entries[i].to));
		pydict_set_item_string_decref(pyelem, "mispred",
		    PyBool_FromLong(entries[i].flags.mispred));
		pydict_set_item_string_decref(pyelem, "predicted",
		    PyBool_FromLong(entries[i].flags.predicted));
		pydict_set_item_string_decref(pyelem, "in_tx",
		    PyBool_FromLong(entries[i].flags.in_tx));
		pydict_set_item_string_decref(pyelem, "abort",
		    PyBool_FromLong(entries[i].flags.पात));
		pydict_set_item_string_decref(pyelem, "cycles",
		    PyLong_FromUnचिन्हितLongLong(entries[i].flags.cycles));

		thपढ़ो__find_map_fb(thपढ़ो, sample->cpumode,
				    entries[i].from, &al);
		dsoname = get_dsoname(al.map);
		pydict_set_item_string_decref(pyelem, "from_dsoname",
					      _PyUnicode_FromString(dsoname));

		thपढ़ो__find_map_fb(thपढ़ो, sample->cpumode,
				    entries[i].to, &al);
		dsoname = get_dsoname(al.map);
		pydict_set_item_string_decref(pyelem, "to_dsoname",
					      _PyUnicode_FromString(dsoname));

		PyList_Append(pylist, pyelem);
		Py_DECREF(pyelem);
	पूर्ण

निकास:
	वापस pylist;
पूर्ण

अटल अचिन्हित दीर्घ get_offset(काष्ठा symbol *sym, काष्ठा addr_location *al)
अणु
	अचिन्हित दीर्घ offset;

	अगर (al->addr < sym->end)
		offset = al->addr - sym->start;
	अन्यथा
		offset = al->addr - al->map->start - sym->start;

	वापस offset;
पूर्ण

अटल पूर्णांक get_symoff(काष्ठा symbol *sym, काष्ठा addr_location *al,
		      bool prपूर्णांक_off, अक्षर *bf, पूर्णांक size)
अणु
	अचिन्हित दीर्घ offset;

	अगर (!sym || !sym->name[0])
		वापस scnम_लिखो(bf, size, "%s", "[unknown]");

	अगर (!prपूर्णांक_off)
		वापस scnम_लिखो(bf, size, "%s", sym->name);

	offset = get_offset(sym, al);

	वापस scnम_लिखो(bf, size, "%s+0x%x", sym->name, offset);
पूर्ण

अटल पूर्णांक get_br_mspred(काष्ठा branch_flags *flags, अक्षर *bf, पूर्णांक size)
अणु
	अगर (!flags->mispred  && !flags->predicted)
		वापस scnम_लिखो(bf, size, "%s", "-");

	अगर (flags->mispred)
		वापस scnम_लिखो(bf, size, "%s", "M");

	वापस scnम_लिखो(bf, size, "%s", "P");
पूर्ण

अटल PyObject *python_process_brstacksym(काष्ठा perf_sample *sample,
					   काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा branch_stack *br = sample->branch_stack;
	काष्ठा branch_entry *entries = perf_sample__branch_entries(sample);
	PyObject *pylist;
	u64 i;
	अक्षर bf[512];
	काष्ठा addr_location al;

	pylist = PyList_New(0);
	अगर (!pylist)
		Py_FatalError("couldn't create Python list");

	अगर (!(br && br->nr))
		जाओ निकास;

	क्रम (i = 0; i < br->nr; i++) अणु
		PyObject *pyelem;

		pyelem = PyDict_New();
		अगर (!pyelem)
			Py_FatalError("couldn't create Python dictionary");

		thपढ़ो__find_symbol_fb(thपढ़ो, sample->cpumode,
				       entries[i].from, &al);
		get_symoff(al.sym, &al, true, bf, माप(bf));
		pydict_set_item_string_decref(pyelem, "from",
					      _PyUnicode_FromString(bf));

		thपढ़ो__find_symbol_fb(thपढ़ो, sample->cpumode,
				       entries[i].to, &al);
		get_symoff(al.sym, &al, true, bf, माप(bf));
		pydict_set_item_string_decref(pyelem, "to",
					      _PyUnicode_FromString(bf));

		get_br_mspred(&entries[i].flags, bf, माप(bf));
		pydict_set_item_string_decref(pyelem, "pred",
					      _PyUnicode_FromString(bf));

		अगर (entries[i].flags.in_tx) अणु
			pydict_set_item_string_decref(pyelem, "in_tx",
					      _PyUnicode_FromString("X"));
		पूर्ण अन्यथा अणु
			pydict_set_item_string_decref(pyelem, "in_tx",
					      _PyUnicode_FromString("-"));
		पूर्ण

		अगर (entries[i].flags.पात) अणु
			pydict_set_item_string_decref(pyelem, "abort",
					      _PyUnicode_FromString("A"));
		पूर्ण अन्यथा अणु
			pydict_set_item_string_decref(pyelem, "abort",
					      _PyUnicode_FromString("-"));
		पूर्ण

		PyList_Append(pylist, pyelem);
		Py_DECREF(pyelem);
	पूर्ण

निकास:
	वापस pylist;
पूर्ण

अटल PyObject *get_sample_value_as_tuple(काष्ठा sample_पढ़ो_value *value)
अणु
	PyObject *t;

	t = PyTuple_New(2);
	अगर (!t)
		Py_FatalError("couldn't create Python tuple");
	PyTuple_SetItem(t, 0, PyLong_FromUnचिन्हितLongLong(value->id));
	PyTuple_SetItem(t, 1, PyLong_FromUnचिन्हितLongLong(value->value));
	वापस t;
पूर्ण

अटल व्योम set_sample_पढ़ो_in_dict(PyObject *dict_sample,
					 काष्ठा perf_sample *sample,
					 काष्ठा evsel *evsel)
अणु
	u64 पढ़ो_क्रमmat = evsel->core.attr.पढ़ो_क्रमmat;
	PyObject *values;
	अचिन्हित पूर्णांक i;

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED) अणु
		pydict_set_item_string_decref(dict_sample, "time_enabled",
			PyLong_FromUnचिन्हितLongLong(sample->पढ़ो.समय_enabled));
	पूर्ण

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING) अणु
		pydict_set_item_string_decref(dict_sample, "time_running",
			PyLong_FromUnचिन्हितLongLong(sample->पढ़ो.समय_running));
	पूर्ण

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP)
		values = PyList_New(sample->पढ़ो.group.nr);
	अन्यथा
		values = PyList_New(1);

	अगर (!values)
		Py_FatalError("couldn't create Python list");

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP) अणु
		क्रम (i = 0; i < sample->पढ़ो.group.nr; i++) अणु
			PyObject *t = get_sample_value_as_tuple(&sample->पढ़ो.group.values[i]);
			PyList_SET_ITEM(values, i, t);
		पूर्ण
	पूर्ण अन्यथा अणु
		PyObject *t = get_sample_value_as_tuple(&sample->पढ़ो.one);
		PyList_SET_ITEM(values, 0, t);
	पूर्ण
	pydict_set_item_string_decref(dict_sample, "values", values);
पूर्ण

अटल व्योम set_sample_datasrc_in_dict(PyObject *dict,
				       काष्ठा perf_sample *sample)
अणु
	काष्ठा mem_info mi = अणु .data_src.val = sample->data_src पूर्ण;
	अक्षर decode[100];

	pydict_set_item_string_decref(dict, "datasrc",
			PyLong_FromUnचिन्हितLongLong(sample->data_src));

	perf_script__meminfo_scnम_लिखो(decode, 100, &mi);

	pydict_set_item_string_decref(dict, "datasrc_decode",
			_PyUnicode_FromString(decode));
पूर्ण

अटल पूर्णांक regs_map(काष्ठा regs_dump *regs, uपूर्णांक64_t mask, अक्षर *bf, पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i = 0, r;
	पूर्णांक prपूर्णांकed = 0;

	bf[0] = 0;

	अगर (!regs || !regs->regs)
		वापस 0;

	क्रम_each_set_bit(r, (अचिन्हित दीर्घ *) &mask, माप(mask) * 8) अणु
		u64 val = regs->regs[i++];

		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed,
				     "%5s:0x%" PRIx64 " ",
				     perf_reg_name(r), val);
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

अटल व्योम set_regs_in_dict(PyObject *dict,
			     काष्ठा perf_sample *sample,
			     काष्ठा evsel *evsel)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	अक्षर bf[512];

	regs_map(&sample->पूर्णांकr_regs, attr->sample_regs_पूर्णांकr, bf, माप(bf));

	pydict_set_item_string_decref(dict, "iregs",
			_PyUnicode_FromString(bf));

	regs_map(&sample->user_regs, attr->sample_regs_user, bf, माप(bf));

	pydict_set_item_string_decref(dict, "uregs",
			_PyUnicode_FromString(bf));
पूर्ण

अटल PyObject *get_perf_sample_dict(काष्ठा perf_sample *sample,
					 काष्ठा evsel *evsel,
					 काष्ठा addr_location *al,
					 PyObject *callchain)
अणु
	PyObject *dict, *dict_sample, *brstack, *brstacksym;

	dict = PyDict_New();
	अगर (!dict)
		Py_FatalError("couldn't create Python dictionary");

	dict_sample = PyDict_New();
	अगर (!dict_sample)
		Py_FatalError("couldn't create Python dictionary");

	pydict_set_item_string_decref(dict, "ev_name", _PyUnicode_FromString(evsel__name(evsel)));
	pydict_set_item_string_decref(dict, "attr", _PyBytes_FromStringAndSize((स्थिर अक्षर *)&evsel->core.attr, माप(evsel->core.attr)));

	pydict_set_item_string_decref(dict_sample, "pid",
			_PyLong_FromLong(sample->pid));
	pydict_set_item_string_decref(dict_sample, "tid",
			_PyLong_FromLong(sample->tid));
	pydict_set_item_string_decref(dict_sample, "cpu",
			_PyLong_FromLong(sample->cpu));
	pydict_set_item_string_decref(dict_sample, "ip",
			PyLong_FromUnचिन्हितLongLong(sample->ip));
	pydict_set_item_string_decref(dict_sample, "time",
			PyLong_FromUnचिन्हितLongLong(sample->समय));
	pydict_set_item_string_decref(dict_sample, "period",
			PyLong_FromUnचिन्हितLongLong(sample->period));
	pydict_set_item_string_decref(dict_sample, "phys_addr",
			PyLong_FromUnचिन्हितLongLong(sample->phys_addr));
	pydict_set_item_string_decref(dict_sample, "addr",
			PyLong_FromUnचिन्हितLongLong(sample->addr));
	set_sample_पढ़ो_in_dict(dict_sample, sample, evsel);
	pydict_set_item_string_decref(dict_sample, "weight",
			PyLong_FromUnचिन्हितLongLong(sample->weight));
	pydict_set_item_string_decref(dict_sample, "transaction",
			PyLong_FromUnचिन्हितLongLong(sample->transaction));
	set_sample_datasrc_in_dict(dict_sample, sample);
	pydict_set_item_string_decref(dict, "sample", dict_sample);

	pydict_set_item_string_decref(dict, "raw_buf", _PyBytes_FromStringAndSize(
			(स्थिर अक्षर *)sample->raw_data, sample->raw_size));
	pydict_set_item_string_decref(dict, "comm",
			_PyUnicode_FromString(thपढ़ो__comm_str(al->thपढ़ो)));
	अगर (al->map) अणु
		pydict_set_item_string_decref(dict, "dso",
			_PyUnicode_FromString(al->map->dso->name));
	पूर्ण
	अगर (al->sym) अणु
		pydict_set_item_string_decref(dict, "symbol",
			_PyUnicode_FromString(al->sym->name));
	पूर्ण

	pydict_set_item_string_decref(dict, "callchain", callchain);

	brstack = python_process_brstack(sample, al->thपढ़ो);
	pydict_set_item_string_decref(dict, "brstack", brstack);

	brstacksym = python_process_brstacksym(sample, al->thपढ़ो);
	pydict_set_item_string_decref(dict, "brstacksym", brstacksym);

	set_regs_in_dict(dict, sample, evsel);

	वापस dict;
पूर्ण

अटल व्योम python_process_tracepoपूर्णांक(काष्ठा perf_sample *sample,
				      काष्ठा evsel *evsel,
				      काष्ठा addr_location *al)
अणु
	काष्ठा tep_event *event = evsel->tp_क्रमmat;
	PyObject *handler, *context, *t, *obj = शून्य, *callchain;
	PyObject *dict = शून्य, *all_entries_dict = शून्य;
	अटल अक्षर handler_name[256];
	काष्ठा tep_क्रमmat_field *field;
	अचिन्हित दीर्घ s, ns;
	अचिन्हित n = 0;
	पूर्णांक pid;
	पूर्णांक cpu = sample->cpu;
	व्योम *data = sample->raw_data;
	अचिन्हित दीर्घ दीर्घ nsecs = sample->समय;
	स्थिर अक्षर *comm = thपढ़ो__comm_str(al->thपढ़ो);
	स्थिर अक्षर *शेष_handler_name = "trace_unhandled";

	अगर (!event) अणु
		snम_लिखो(handler_name, माप(handler_name),
			 "ug! no event found for type %" PRIu64, (u64)evsel->core.attr.config);
		Py_FatalError(handler_name);
	पूर्ण

	pid = raw_field_value(event, "common_pid", data);

	प्र_लिखो(handler_name, "%s__%s", event->प्रणाली, event->name);

	अगर (!test_and_set_bit(event->id, events_defined))
		define_event_symbols(event, handler_name, event->prपूर्णांक_fmt.args);

	handler = get_handler(handler_name);
	अगर (!handler) अणु
		handler = get_handler(शेष_handler_name);
		अगर (!handler)
			वापस;
		dict = PyDict_New();
		अगर (!dict)
			Py_FatalError("couldn't create Python dict");
	पूर्ण

	t = PyTuple_New(MAX_FIELDS);
	अगर (!t)
		Py_FatalError("couldn't create Python tuple");


	s = nsecs / NSEC_PER_SEC;
	ns = nsecs - s * NSEC_PER_SEC;

	scripting_context->event_data = data;
	scripting_context->pevent = evsel->tp_क्रमmat->tep;

	context = _PyCapsule_New(scripting_context, शून्य, शून्य);

	PyTuple_SetItem(t, n++, _PyUnicode_FromString(handler_name));
	PyTuple_SetItem(t, n++, context);

	/* ip unwinding */
	callchain = python_process_callchain(sample, evsel, al);
	/* Need an additional reference क्रम the perf_sample dict */
	Py_INCREF(callchain);

	अगर (!dict) अणु
		PyTuple_SetItem(t, n++, _PyLong_FromLong(cpu));
		PyTuple_SetItem(t, n++, _PyLong_FromLong(s));
		PyTuple_SetItem(t, n++, _PyLong_FromLong(ns));
		PyTuple_SetItem(t, n++, _PyLong_FromLong(pid));
		PyTuple_SetItem(t, n++, _PyUnicode_FromString(comm));
		PyTuple_SetItem(t, n++, callchain);
	पूर्ण अन्यथा अणु
		pydict_set_item_string_decref(dict, "common_cpu", _PyLong_FromLong(cpu));
		pydict_set_item_string_decref(dict, "common_s", _PyLong_FromLong(s));
		pydict_set_item_string_decref(dict, "common_ns", _PyLong_FromLong(ns));
		pydict_set_item_string_decref(dict, "common_pid", _PyLong_FromLong(pid));
		pydict_set_item_string_decref(dict, "common_comm", _PyUnicode_FromString(comm));
		pydict_set_item_string_decref(dict, "common_callchain", callchain);
	पूर्ण
	क्रम (field = event->क्रमmat.fields; field; field = field->next) अणु
		अचिन्हित पूर्णांक offset, len;
		अचिन्हित दीर्घ दीर्घ val;

		अगर (field->flags & TEP_FIELD_IS_ARRAY) अणु
			offset = field->offset;
			len    = field->size;
			अगर (field->flags & TEP_FIELD_IS_DYNAMIC) अणु
				val     = tep_पढ़ो_number(scripting_context->pevent,
							  data + offset, len);
				offset  = val;
				len     = offset >> 16;
				offset &= 0xffff;
			पूर्ण
			अगर (field->flags & TEP_FIELD_IS_STRING &&
			    is_prपूर्णांकable_array(data + offset, len)) अणु
				obj = _PyUnicode_FromString((अक्षर *) data + offset);
			पूर्ण अन्यथा अणु
				obj = PyByteArray_FromStringAndSize((स्थिर अक्षर *) data + offset, len);
				field->flags &= ~TEP_FIELD_IS_STRING;
			पूर्ण
		पूर्ण अन्यथा अणु /* FIELD_IS_NUMERIC */
			obj = get_field_numeric_entry(event, field, data);
		पूर्ण
		अगर (!dict)
			PyTuple_SetItem(t, n++, obj);
		अन्यथा
			pydict_set_item_string_decref(dict, field->name, obj);

	पूर्ण

	अगर (dict)
		PyTuple_SetItem(t, n++, dict);

	अगर (get_argument_count(handler) == (पूर्णांक) n + 1) अणु
		all_entries_dict = get_perf_sample_dict(sample, evsel, al,
			callchain);
		PyTuple_SetItem(t, n++,	all_entries_dict);
	पूर्ण अन्यथा अणु
		Py_DECREF(callchain);
	पूर्ण

	अगर (_PyTuple_Resize(&t, n) == -1)
		Py_FatalError("error resizing Python tuple");

	अगर (!dict)
		call_object(handler, t, handler_name);
	अन्यथा
		call_object(handler, t, शेष_handler_name);

	Py_DECREF(t);
पूर्ण

अटल PyObject *tuple_new(अचिन्हित पूर्णांक sz)
अणु
	PyObject *t;

	t = PyTuple_New(sz);
	अगर (!t)
		Py_FatalError("couldn't create Python tuple");
	वापस t;
पूर्ण

अटल पूर्णांक tuple_set_u64(PyObject *t, अचिन्हित पूर्णांक pos, u64 val)
अणु
#अगर BITS_PER_LONG == 64
	वापस PyTuple_SetItem(t, pos, _PyLong_FromLong(val));
#पूर्ण_अगर
#अगर BITS_PER_LONG == 32
	वापस PyTuple_SetItem(t, pos, PyLong_FromLongLong(val));
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक tuple_set_s32(PyObject *t, अचिन्हित पूर्णांक pos, s32 val)
अणु
	वापस PyTuple_SetItem(t, pos, _PyLong_FromLong(val));
पूर्ण

अटल पूर्णांक tuple_set_string(PyObject *t, अचिन्हित पूर्णांक pos, स्थिर अक्षर *s)
अणु
	वापस PyTuple_SetItem(t, pos, _PyUnicode_FromString(s));
पूर्ण

अटल पूर्णांक tuple_set_bytes(PyObject *t, अचिन्हित पूर्णांक pos, व्योम *bytes,
			   अचिन्हित पूर्णांक sz)
अणु
	वापस PyTuple_SetItem(t, pos, _PyBytes_FromStringAndSize(bytes, sz));
पूर्ण

अटल पूर्णांक python_export_evsel(काष्ठा db_export *dbe, काष्ठा evsel *evsel)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;

	t = tuple_new(2);

	tuple_set_u64(t, 0, evsel->db_id);
	tuple_set_string(t, 1, evsel__name(evsel));

	call_object(tables->evsel_handler, t, "evsel_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_machine(काष्ठा db_export *dbe,
				 काष्ठा machine *machine)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;

	t = tuple_new(3);

	tuple_set_u64(t, 0, machine->db_id);
	tuple_set_s32(t, 1, machine->pid);
	tuple_set_string(t, 2, machine->root_dir ? machine->root_dir : "");

	call_object(tables->machine_handler, t, "machine_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_thपढ़ो(काष्ठा db_export *dbe, काष्ठा thपढ़ो *thपढ़ो,
				u64 मुख्य_thपढ़ो_db_id, काष्ठा machine *machine)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;

	t = tuple_new(5);

	tuple_set_u64(t, 0, thपढ़ो->db_id);
	tuple_set_u64(t, 1, machine->db_id);
	tuple_set_u64(t, 2, मुख्य_thपढ़ो_db_id);
	tuple_set_s32(t, 3, thपढ़ो->pid_);
	tuple_set_s32(t, 4, thपढ़ो->tid);

	call_object(tables->thपढ़ो_handler, t, "thread_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_comm(काष्ठा db_export *dbe, काष्ठा comm *comm,
			      काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;

	t = tuple_new(5);

	tuple_set_u64(t, 0, comm->db_id);
	tuple_set_string(t, 1, comm__str(comm));
	tuple_set_u64(t, 2, thपढ़ो->db_id);
	tuple_set_u64(t, 3, comm->start);
	tuple_set_s32(t, 4, comm->exec);

	call_object(tables->comm_handler, t, "comm_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_comm_thपढ़ो(काष्ठा db_export *dbe, u64 db_id,
				     काष्ठा comm *comm, काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;

	t = tuple_new(3);

	tuple_set_u64(t, 0, db_id);
	tuple_set_u64(t, 1, comm->db_id);
	tuple_set_u64(t, 2, thपढ़ो->db_id);

	call_object(tables->comm_thपढ़ो_handler, t, "comm_thread_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_dso(काष्ठा db_export *dbe, काष्ठा dso *dso,
			     काष्ठा machine *machine)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	अक्षर sbuild_id[SBUILD_ID_SIZE];
	PyObject *t;

	build_id__प्र_लिखो(&dso->bid, sbuild_id);

	t = tuple_new(5);

	tuple_set_u64(t, 0, dso->db_id);
	tuple_set_u64(t, 1, machine->db_id);
	tuple_set_string(t, 2, dso->लघु_name);
	tuple_set_string(t, 3, dso->दीर्घ_name);
	tuple_set_string(t, 4, sbuild_id);

	call_object(tables->dso_handler, t, "dso_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_symbol(काष्ठा db_export *dbe, काष्ठा symbol *sym,
				काष्ठा dso *dso)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	u64 *sym_db_id = symbol__priv(sym);
	PyObject *t;

	t = tuple_new(6);

	tuple_set_u64(t, 0, *sym_db_id);
	tuple_set_u64(t, 1, dso->db_id);
	tuple_set_u64(t, 2, sym->start);
	tuple_set_u64(t, 3, sym->end);
	tuple_set_s32(t, 4, sym->binding);
	tuple_set_string(t, 5, sym->name);

	call_object(tables->symbol_handler, t, "symbol_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_branch_type(काष्ठा db_export *dbe, u32 branch_type,
				     स्थिर अक्षर *name)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;

	t = tuple_new(2);

	tuple_set_s32(t, 0, branch_type);
	tuple_set_string(t, 1, name);

	call_object(tables->branch_type_handler, t, "branch_type_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल व्योम python_export_sample_table(काष्ठा db_export *dbe,
				       काष्ठा export_sample *es)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;

	t = tuple_new(24);

	tuple_set_u64(t, 0, es->db_id);
	tuple_set_u64(t, 1, es->evsel->db_id);
	tuple_set_u64(t, 2, es->al->maps->machine->db_id);
	tuple_set_u64(t, 3, es->al->thपढ़ो->db_id);
	tuple_set_u64(t, 4, es->comm_db_id);
	tuple_set_u64(t, 5, es->dso_db_id);
	tuple_set_u64(t, 6, es->sym_db_id);
	tuple_set_u64(t, 7, es->offset);
	tuple_set_u64(t, 8, es->sample->ip);
	tuple_set_u64(t, 9, es->sample->समय);
	tuple_set_s32(t, 10, es->sample->cpu);
	tuple_set_u64(t, 11, es->addr_dso_db_id);
	tuple_set_u64(t, 12, es->addr_sym_db_id);
	tuple_set_u64(t, 13, es->addr_offset);
	tuple_set_u64(t, 14, es->sample->addr);
	tuple_set_u64(t, 15, es->sample->period);
	tuple_set_u64(t, 16, es->sample->weight);
	tuple_set_u64(t, 17, es->sample->transaction);
	tuple_set_u64(t, 18, es->sample->data_src);
	tuple_set_s32(t, 19, es->sample->flags & PERF_BRANCH_MASK);
	tuple_set_s32(t, 20, !!(es->sample->flags & PERF_IP_FLAG_IN_TX));
	tuple_set_u64(t, 21, es->call_path_id);
	tuple_set_u64(t, 22, es->sample->insn_cnt);
	tuple_set_u64(t, 23, es->sample->cyc_cnt);

	call_object(tables->sample_handler, t, "sample_table");

	Py_DECREF(t);
पूर्ण

अटल व्योम python_export_synth(काष्ठा db_export *dbe, काष्ठा export_sample *es)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;

	t = tuple_new(3);

	tuple_set_u64(t, 0, es->db_id);
	tuple_set_u64(t, 1, es->evsel->core.attr.config);
	tuple_set_bytes(t, 2, es->sample->raw_data, es->sample->raw_size);

	call_object(tables->synth_handler, t, "synth_data");

	Py_DECREF(t);
पूर्ण

अटल पूर्णांक python_export_sample(काष्ठा db_export *dbe,
				काष्ठा export_sample *es)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);

	python_export_sample_table(dbe, es);

	अगर (es->evsel->core.attr.type == PERF_TYPE_SYNTH && tables->synth_handler)
		python_export_synth(dbe, es);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_call_path(काष्ठा db_export *dbe, काष्ठा call_path *cp)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;
	u64 parent_db_id, sym_db_id;

	parent_db_id = cp->parent ? cp->parent->db_id : 0;
	sym_db_id = cp->sym ? *(u64 *)symbol__priv(cp->sym) : 0;

	t = tuple_new(4);

	tuple_set_u64(t, 0, cp->db_id);
	tuple_set_u64(t, 1, parent_db_id);
	tuple_set_u64(t, 2, sym_db_id);
	tuple_set_u64(t, 3, cp->ip);

	call_object(tables->call_path_handler, t, "call_path_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_call_वापस(काष्ठा db_export *dbe,
				     काष्ठा call_वापस *cr)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	u64 comm_db_id = cr->comm ? cr->comm->db_id : 0;
	PyObject *t;

	t = tuple_new(14);

	tuple_set_u64(t, 0, cr->db_id);
	tuple_set_u64(t, 1, cr->thपढ़ो->db_id);
	tuple_set_u64(t, 2, comm_db_id);
	tuple_set_u64(t, 3, cr->cp->db_id);
	tuple_set_u64(t, 4, cr->call_समय);
	tuple_set_u64(t, 5, cr->वापस_समय);
	tuple_set_u64(t, 6, cr->branch_count);
	tuple_set_u64(t, 7, cr->call_ref);
	tuple_set_u64(t, 8, cr->वापस_ref);
	tuple_set_u64(t, 9, cr->cp->parent->db_id);
	tuple_set_s32(t, 10, cr->flags);
	tuple_set_u64(t, 11, cr->parent_db_id);
	tuple_set_u64(t, 12, cr->insn_count);
	tuple_set_u64(t, 13, cr->cyc_count);

	call_object(tables->call_वापस_handler, t, "call_return_table");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_export_context_चयन(काष्ठा db_export *dbe, u64 db_id,
					काष्ठा machine *machine,
					काष्ठा perf_sample *sample,
					u64 th_out_id, u64 comm_out_id,
					u64 th_in_id, u64 comm_in_id, पूर्णांक flags)
अणु
	काष्ठा tables *tables = container_of(dbe, काष्ठा tables, dbe);
	PyObject *t;

	t = tuple_new(9);

	tuple_set_u64(t, 0, db_id);
	tuple_set_u64(t, 1, machine->db_id);
	tuple_set_u64(t, 2, sample->समय);
	tuple_set_s32(t, 3, sample->cpu);
	tuple_set_u64(t, 4, th_out_id);
	tuple_set_u64(t, 5, comm_out_id);
	tuple_set_u64(t, 6, th_in_id);
	tuple_set_u64(t, 7, comm_in_id);
	tuple_set_s32(t, 8, flags);

	call_object(tables->context_चयन_handler, t, "context_switch");

	Py_DECREF(t);

	वापस 0;
पूर्ण

अटल पूर्णांक python_process_call_वापस(काष्ठा call_वापस *cr, u64 *parent_db_id,
				      व्योम *data)
अणु
	काष्ठा db_export *dbe = data;

	वापस db_export__call_वापस(dbe, cr, parent_db_id);
पूर्ण

अटल व्योम python_process_general_event(काष्ठा perf_sample *sample,
					 काष्ठा evsel *evsel,
					 काष्ठा addr_location *al)
अणु
	PyObject *handler, *t, *dict, *callchain;
	अटल अक्षर handler_name[64];
	अचिन्हित n = 0;

	snम_लिखो(handler_name, माप(handler_name), "%s", "process_event");

	handler = get_handler(handler_name);
	अगर (!handler)
		वापस;

	/*
	 * Use the MAX_FIELDS to make the function expandable, though
	 * currently there is only one item क्रम the tuple.
	 */
	t = PyTuple_New(MAX_FIELDS);
	अगर (!t)
		Py_FatalError("couldn't create Python tuple");

	/* ip unwinding */
	callchain = python_process_callchain(sample, evsel, al);
	dict = get_perf_sample_dict(sample, evsel, al, callchain);

	PyTuple_SetItem(t, n++, dict);
	अगर (_PyTuple_Resize(&t, n) == -1)
		Py_FatalError("error resizing Python tuple");

	call_object(handler, t, handler_name);

	Py_DECREF(t);
पूर्ण

अटल व्योम python_process_event(जोड़ perf_event *event,
				 काष्ठा perf_sample *sample,
				 काष्ठा evsel *evsel,
				 काष्ठा addr_location *al)
अणु
	काष्ठा tables *tables = &tables_global;

	चयन (evsel->core.attr.type) अणु
	हाल PERF_TYPE_TRACEPOINT:
		python_process_tracepoपूर्णांक(sample, evsel, al);
		अवरोध;
	/* Reserve क्रम future process_hw/sw/raw APIs */
	शेष:
		अगर (tables->db_export_mode)
			db_export__sample(&tables->dbe, event, sample, evsel, al);
		अन्यथा
			python_process_general_event(sample, evsel, al);
	पूर्ण
पूर्ण

अटल व्योम python_process_चयन(जोड़ perf_event *event,
				  काष्ठा perf_sample *sample,
				  काष्ठा machine *machine)
अणु
	काष्ठा tables *tables = &tables_global;

	अगर (tables->db_export_mode)
		db_export__चयन(&tables->dbe, event, sample, machine);
पूर्ण

अटल व्योम get_handler_name(अक्षर *str, माप_प्रकार size,
			     काष्ठा evsel *evsel)
अणु
	अक्षर *p = str;

	scnम_लिखो(str, size, "stat__%s", evsel__name(evsel));

	जबतक ((p = म_अक्षर(p, ':'))) अणु
		*p = '_';
		p++;
	पूर्ण
पूर्ण

अटल व्योम
process_stat(काष्ठा evsel *counter, पूर्णांक cpu, पूर्णांक thपढ़ो, u64 tstamp,
	     काष्ठा perf_counts_values *count)
अणु
	PyObject *handler, *t;
	अटल अक्षर handler_name[256];
	पूर्णांक n = 0;

	t = PyTuple_New(MAX_FIELDS);
	अगर (!t)
		Py_FatalError("couldn't create Python tuple");

	get_handler_name(handler_name, माप(handler_name),
			 counter);

	handler = get_handler(handler_name);
	अगर (!handler) अणु
		pr_debug("can't find python handler %s\n", handler_name);
		वापस;
	पूर्ण

	PyTuple_SetItem(t, n++, _PyLong_FromLong(cpu));
	PyTuple_SetItem(t, n++, _PyLong_FromLong(thपढ़ो));

	tuple_set_u64(t, n++, tstamp);
	tuple_set_u64(t, n++, count->val);
	tuple_set_u64(t, n++, count->ena);
	tuple_set_u64(t, n++, count->run);

	अगर (_PyTuple_Resize(&t, n) == -1)
		Py_FatalError("error resizing Python tuple");

	call_object(handler, t, handler_name);

	Py_DECREF(t);
पूर्ण

अटल व्योम python_process_stat(काष्ठा perf_stat_config *config,
				काष्ठा evsel *counter, u64 tstamp)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = counter->core.thपढ़ोs;
	काष्ठा perf_cpu_map *cpus = counter->core.cpus;
	पूर्णांक cpu, thपढ़ो;

	अगर (config->aggr_mode == AGGR_GLOBAL) अणु
		process_stat(counter, -1, -1, tstamp,
			     &counter->counts->aggr);
		वापस;
	पूर्ण

	क्रम (thपढ़ो = 0; thपढ़ो < thपढ़ोs->nr; thपढ़ो++) अणु
		क्रम (cpu = 0; cpu < cpus->nr; cpu++) अणु
			process_stat(counter, cpus->map[cpu],
				     perf_thपढ़ो_map__pid(thपढ़ोs, thपढ़ो), tstamp,
				     perf_counts(counter->counts, cpu, thपढ़ो));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम python_process_stat_पूर्णांकerval(u64 tstamp)
अणु
	PyObject *handler, *t;
	अटल स्थिर अक्षर handler_name[] = "stat__interval";
	पूर्णांक n = 0;

	t = PyTuple_New(MAX_FIELDS);
	अगर (!t)
		Py_FatalError("couldn't create Python tuple");

	handler = get_handler(handler_name);
	अगर (!handler) अणु
		pr_debug("can't find python handler %s\n", handler_name);
		वापस;
	पूर्ण

	tuple_set_u64(t, n++, tstamp);

	अगर (_PyTuple_Resize(&t, n) == -1)
		Py_FatalError("error resizing Python tuple");

	call_object(handler, t, handler_name);

	Py_DECREF(t);
पूर्ण

अटल पूर्णांक run_start_sub(व्योम)
अणु
	मुख्य_module = PyImport_AddModule("__main__");
	अगर (मुख्य_module == शून्य)
		वापस -1;
	Py_INCREF(मुख्य_module);

	मुख्य_dict = PyModule_GetDict(मुख्य_module);
	अगर (मुख्य_dict == शून्य)
		जाओ error;
	Py_INCREF(मुख्य_dict);

	try_call_object("trace_begin", शून्य);

	वापस 0;

error:
	Py_XDECREF(मुख्य_dict);
	Py_XDECREF(मुख्य_module);
	वापस -1;
पूर्ण

#घोषणा SET_TABLE_HANDLER_(name, handler_name, table_name) करो अणु		\
	tables->handler_name = get_handler(#table_name);		\
	अगर (tables->handler_name)					\
		tables->dbe.export_ ## name = python_export_ ## name;	\
पूर्ण जबतक (0)

#घोषणा SET_TABLE_HANDLER(name) \
	SET_TABLE_HANDLER_(name, name ## _handler, name ## _table)

अटल व्योम set_table_handlers(काष्ठा tables *tables)
अणु
	स्थिर अक्षर *perf_db_export_mode = "perf_db_export_mode";
	स्थिर अक्षर *perf_db_export_calls = "perf_db_export_calls";
	स्थिर अक्षर *perf_db_export_callchains = "perf_db_export_callchains";
	PyObject *db_export_mode, *db_export_calls, *db_export_callchains;
	bool export_calls = false;
	bool export_callchains = false;
	पूर्णांक ret;

	स_रखो(tables, 0, माप(काष्ठा tables));
	अगर (db_export__init(&tables->dbe))
		Py_FatalError("failed to initialize export");

	db_export_mode = PyDict_GetItemString(मुख्य_dict, perf_db_export_mode);
	अगर (!db_export_mode)
		वापस;

	ret = PyObject_IsTrue(db_export_mode);
	अगर (ret == -1)
		handler_call_die(perf_db_export_mode);
	अगर (!ret)
		वापस;

	/* handle export calls */
	tables->dbe.crp = शून्य;
	db_export_calls = PyDict_GetItemString(मुख्य_dict, perf_db_export_calls);
	अगर (db_export_calls) अणु
		ret = PyObject_IsTrue(db_export_calls);
		अगर (ret == -1)
			handler_call_die(perf_db_export_calls);
		export_calls = !!ret;
	पूर्ण

	अगर (export_calls) अणु
		tables->dbe.crp =
			call_वापस_processor__new(python_process_call_वापस,
						   &tables->dbe);
		अगर (!tables->dbe.crp)
			Py_FatalError("failed to create calls processor");
	पूर्ण

	/* handle export callchains */
	tables->dbe.cpr = शून्य;
	db_export_callchains = PyDict_GetItemString(मुख्य_dict,
						    perf_db_export_callchains);
	अगर (db_export_callchains) अणु
		ret = PyObject_IsTrue(db_export_callchains);
		अगर (ret == -1)
			handler_call_die(perf_db_export_callchains);
		export_callchains = !!ret;
	पूर्ण

	अगर (export_callchains) अणु
		/*
		 * Attempt to use the call path root from the call वापस
		 * processor, अगर the call वापस processor is in use. Otherwise,
		 * we allocate a new call path root. This prevents exporting
		 * duplicate call path ids when both are in use simultaneously.
		 */
		अगर (tables->dbe.crp)
			tables->dbe.cpr = tables->dbe.crp->cpr;
		अन्यथा
			tables->dbe.cpr = call_path_root__new();

		अगर (!tables->dbe.cpr)
			Py_FatalError("failed to create call path root");
	पूर्ण

	tables->db_export_mode = true;
	/*
	 * Reserve per symbol space क्रम symbol->db_id via symbol__priv()
	 */
	symbol_conf.priv_size = माप(u64);

	SET_TABLE_HANDLER(evsel);
	SET_TABLE_HANDLER(machine);
	SET_TABLE_HANDLER(thपढ़ो);
	SET_TABLE_HANDLER(comm);
	SET_TABLE_HANDLER(comm_thपढ़ो);
	SET_TABLE_HANDLER(dso);
	SET_TABLE_HANDLER(symbol);
	SET_TABLE_HANDLER(branch_type);
	SET_TABLE_HANDLER(sample);
	SET_TABLE_HANDLER(call_path);
	SET_TABLE_HANDLER(call_वापस);
	SET_TABLE_HANDLER(context_चयन);

	/*
	 * Synthesized events are samples but with architecture-specअगरic data
	 * stored in sample->raw_data. They are exported via
	 * python_export_sample() and consequently करो not need a separate export
	 * callback.
	 */
	tables->synth_handler = get_handler("synth_data");
पूर्ण

#अगर PY_MAJOR_VERSION < 3
अटल व्योम _मुक्त_command_line(स्थिर अक्षर **command_line, पूर्णांक num)
अणु
	मुक्त(command_line);
पूर्ण
#अन्यथा
अटल व्योम _मुक्त_command_line(ब_अक्षर_प्रकार **command_line, पूर्णांक num)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < num; i++)
		PyMem_RawFree(command_line[i]);
	मुक्त(command_line);
पूर्ण
#पूर्ण_अगर


/*
 * Start trace script
 */
अटल पूर्णांक python_start_script(स्थिर अक्षर *script, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा tables *tables = &tables_global;
#अगर PY_MAJOR_VERSION < 3
	स्थिर अक्षर **command_line;
#अन्यथा
	ब_अक्षर_प्रकार **command_line;
#पूर्ण_अगर
	/*
	 * Use a non-स्थिर name variable to cope with python 2.6's
	 * PyImport_AppendInittab prototype
	 */
	अक्षर buf[PATH_MAX], name[19] = "perf_trace_context";
	पूर्णांक i, err = 0;
	खाता *fp;

#अगर PY_MAJOR_VERSION < 3
	command_line = दो_स्मृति((argc + 1) * माप(स्थिर अक्षर *));
	command_line[0] = script;
	क्रम (i = 1; i < argc + 1; i++)
		command_line[i] = argv[i - 1];
	PyImport_AppendInittab(name, initperf_trace_context);
#अन्यथा
	command_line = दो_स्मृति((argc + 1) * माप(ब_अक्षर_प्रकार *));
	command_line[0] = Py_DecodeLocale(script, शून्य);
	क्रम (i = 1; i < argc + 1; i++)
		command_line[i] = Py_DecodeLocale(argv[i - 1], शून्य);
	PyImport_AppendInittab(name, PyInit_perf_trace_context);
#पूर्ण_अगर
	Py_Initialize();

#अगर PY_MAJOR_VERSION < 3
	PySys_SetArgv(argc + 1, (अक्षर **)command_line);
#अन्यथा
	PySys_SetArgv(argc + 1, command_line);
#पूर्ण_अगर

	fp = ख_खोलो(script, "r");
	अगर (!fp) अणु
		प्र_लिखो(buf, "Can't open python script \"%s\"", script);
		लिखो_त्रुटि(buf);
		err = -1;
		जाओ error;
	पूर्ण

	err = PyRun_SimpleFile(fp, script);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "Error running python script %s\n", script);
		जाओ error;
	पूर्ण

	err = run_start_sub();
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "Error starting python script %s\n", script);
		जाओ error;
	पूर्ण

	set_table_handlers(tables);

	अगर (tables->db_export_mode) अणु
		err = db_export__branch_types(&tables->dbe);
		अगर (err)
			जाओ error;
	पूर्ण

	_मुक्त_command_line(command_line, argc + 1);

	वापस err;
error:
	Py_Finalize();
	_मुक्त_command_line(command_line, argc + 1);

	वापस err;
पूर्ण

अटल पूर्णांक python_flush_script(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * Stop trace script
 */
अटल पूर्णांक python_stop_script(व्योम)
अणु
	काष्ठा tables *tables = &tables_global;

	try_call_object("trace_end", शून्य);

	db_export__निकास(&tables->dbe);

	Py_XDECREF(मुख्य_dict);
	Py_XDECREF(मुख्य_module);
	Py_Finalize();

	वापस 0;
पूर्ण

अटल पूर्णांक python_generate_script(काष्ठा tep_handle *pevent, स्थिर अक्षर *outfile)
अणु
	पूर्णांक i, not_first, count, nr_events;
	काष्ठा tep_event **all_events;
	काष्ठा tep_event *event = शून्य;
	काष्ठा tep_क्रमmat_field *f;
	अक्षर fname[PATH_MAX];
	खाता *ofp;

	प्र_लिखो(fname, "%s.py", outfile);
	ofp = ख_खोलो(fname, "w");
	अगर (ofp == शून्य) अणु
		ख_लिखो(मानक_त्रुटि, "couldn't open %s\n", fname);
		वापस -1;
	पूर्ण
	ख_लिखो(ofp, "# perf script event handlers, "
		"generated by perf script -g python\n");

	ख_लिखो(ofp, "# Licensed under the terms of the GNU GPL"
		" License version 2\n\n");

	ख_लिखो(ofp, "# The common_* event handler fields are the most useful "
		"fields common to\n");

	ख_लिखो(ofp, "# all events.  They don't necessarily correspond to "
		"the 'common_*' fields\n");

	ख_लिखो(ofp, "# in the format files.  Those fields not available as "
		"handler params can\n");

	ख_लिखो(ofp, "# be retrieved using Python functions of the form "
		"common_*(context).\n");

	ख_लिखो(ofp, "# See the perf-script-python Documentation for the list "
		"of available functions.\n\n");

	ख_लिखो(ofp, "from __future__ import print_function\n\n");
	ख_लिखो(ofp, "import os\n");
	ख_लिखो(ofp, "import sys\n\n");

	ख_लिखो(ofp, "sys.path.append(os.environ['PERF_EXEC_PATH'] + \\\n");
	ख_लिखो(ofp, "\t'/scripts/python/Perf-Trace-Util/lib/Perf/Trace')\n");
	ख_लिखो(ofp, "\nfrom perf_trace_context import *\n");
	ख_लिखो(ofp, "from Core import *\n\n\n");

	ख_लिखो(ofp, "def trace_begin():\n");
	ख_लिखो(ofp, "\tprint(\"in trace_begin\")\n\n");

	ख_लिखो(ofp, "def trace_end():\n");
	ख_लिखो(ofp, "\tprint(\"in trace_end\")\n\n");

	nr_events = tep_get_events_count(pevent);
	all_events = tep_list_events(pevent, TEP_EVENT_SORT_ID);

	क्रम (i = 0; all_events && i < nr_events; i++) अणु
		event = all_events[i];
		ख_लिखो(ofp, "def %s__%s(", event->प्रणाली, event->name);
		ख_लिखो(ofp, "event_name, ");
		ख_लिखो(ofp, "context, ");
		ख_लिखो(ofp, "common_cpu,\n");
		ख_लिखो(ofp, "\tcommon_secs, ");
		ख_लिखो(ofp, "common_nsecs, ");
		ख_लिखो(ofp, "common_pid, ");
		ख_लिखो(ofp, "common_comm,\n\t");
		ख_लिखो(ofp, "common_callchain, ");

		not_first = 0;
		count = 0;

		क्रम (f = event->क्रमmat.fields; f; f = f->next) अणु
			अगर (not_first++)
				ख_लिखो(ofp, ", ");
			अगर (++count % 5 == 0)
				ख_लिखो(ofp, "\n\t");

			ख_लिखो(ofp, "%s", f->name);
		पूर्ण
		अगर (not_first++)
			ख_लिखो(ofp, ", ");
		अगर (++count % 5 == 0)
			ख_लिखो(ofp, "\n\t\t");
		ख_लिखो(ofp, "perf_sample_dict");

		ख_लिखो(ofp, "):\n");

		ख_लिखो(ofp, "\t\tprint_header(event_name, common_cpu, "
			"common_secs, common_nsecs,\n\t\t\t"
			"common_pid, common_comm)\n\n");

		ख_लिखो(ofp, "\t\tprint(\"");

		not_first = 0;
		count = 0;

		क्रम (f = event->क्रमmat.fields; f; f = f->next) अणु
			अगर (not_first++)
				ख_लिखो(ofp, ", ");
			अगर (count && count % 3 == 0) अणु
				ख_लिखो(ofp, "\" \\\n\t\t\"");
			पूर्ण
			count++;

			ख_लिखो(ofp, "%s=", f->name);
			अगर (f->flags & TEP_FIELD_IS_STRING ||
			    f->flags & TEP_FIELD_IS_FLAG ||
			    f->flags & TEP_FIELD_IS_ARRAY ||
			    f->flags & TEP_FIELD_IS_SYMBOLIC)
				ख_लिखो(ofp, "%%s");
			अन्यथा अगर (f->flags & TEP_FIELD_IS_SIGNED)
				ख_लिखो(ofp, "%%d");
			अन्यथा
				ख_लिखो(ofp, "%%u");
		पूर्ण

		ख_लिखो(ofp, "\" %% \\\n\t\t(");

		not_first = 0;
		count = 0;

		क्रम (f = event->क्रमmat.fields; f; f = f->next) अणु
			अगर (not_first++)
				ख_लिखो(ofp, ", ");

			अगर (++count % 5 == 0)
				ख_लिखो(ofp, "\n\t\t");

			अगर (f->flags & TEP_FIELD_IS_FLAG) अणु
				अगर ((count - 1) % 5 != 0) अणु
					ख_लिखो(ofp, "\n\t\t");
					count = 4;
				पूर्ण
				ख_लिखो(ofp, "flag_str(\"");
				ख_लिखो(ofp, "%s__%s\", ", event->प्रणाली,
					event->name);
				ख_लिखो(ofp, "\"%s\", %s)", f->name,
					f->name);
			पूर्ण अन्यथा अगर (f->flags & TEP_FIELD_IS_SYMBOLIC) अणु
				अगर ((count - 1) % 5 != 0) अणु
					ख_लिखो(ofp, "\n\t\t");
					count = 4;
				पूर्ण
				ख_लिखो(ofp, "symbol_str(\"");
				ख_लिखो(ofp, "%s__%s\", ", event->प्रणाली,
					event->name);
				ख_लिखो(ofp, "\"%s\", %s)", f->name,
					f->name);
			पूर्ण अन्यथा
				ख_लिखो(ofp, "%s", f->name);
		पूर्ण

		ख_लिखो(ofp, "))\n\n");

		ख_लिखो(ofp, "\t\tprint('Sample: {'+"
			"get_dict_as_string(perf_sample_dict['sample'], ', ')+'}')\n\n");

		ख_लिखो(ofp, "\t\tfor node in common_callchain:");
		ख_लिखो(ofp, "\n\t\t\tif 'sym' in node:");
		ख_लिखो(ofp, "\n\t\t\t\tprint(\"\\t[%%x] %%s\" %% (node['ip'], node['sym']['name']))");
		ख_लिखो(ofp, "\n\t\t\telse:");
		ख_लिखो(ofp, "\n\t\t\t\tprint(\"\t[%%x]\" %% (node['ip']))\n\n");
		ख_लिखो(ofp, "\t\tprint()\n\n");

	पूर्ण

	ख_लिखो(ofp, "def trace_unhandled(event_name, context, "
		"event_fields_dict, perf_sample_dict):\n");

	ख_लिखो(ofp, "\t\tprint(get_dict_as_string(event_fields_dict))\n");
	ख_लिखो(ofp, "\t\tprint('Sample: {'+"
		"get_dict_as_string(perf_sample_dict['sample'], ', ')+'}')\n\n");

	ख_लिखो(ofp, "def print_header("
		"event_name, cpu, secs, nsecs, pid, comm):\n"
		"\tprint(\"%%-20s %%5u %%05u.%%09u %%8u %%-20s \" %% \\\n\t"
		"(event_name, cpu, secs, nsecs, pid, comm), end=\"\")\n\n");

	ख_लिखो(ofp, "def get_dict_as_string(a_dict, delimiter=' '):\n"
		"\treturn delimiter.join"
		"(['%%s=%%s'%%(k,str(v))for k,v in sorted(a_dict.items())])\n");

	ख_बंद(ofp);

	ख_लिखो(मानक_त्रुटि, "generated Python script: %s\n", fname);

	वापस 0;
पूर्ण

काष्ठा scripting_ops python_scripting_ops = अणु
	.name			= "Python",
	.start_script		= python_start_script,
	.flush_script		= python_flush_script,
	.stop_script		= python_stop_script,
	.process_event		= python_process_event,
	.process_चयन		= python_process_चयन,
	.process_stat		= python_process_stat,
	.process_stat_पूर्णांकerval	= python_process_stat_पूर्णांकerval,
	.generate_script	= python_generate_script,
पूर्ण;
