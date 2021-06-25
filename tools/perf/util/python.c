<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <Python.h>
#समावेश <काष्ठाmember.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <poll.h>
#समावेश <linux/err.h>
#समावेश <perf/cpumap.h>
#समावेश <traceevent/event-parse.h>
#समावेश <perf/mmap.h>
#समावेश "evlist.h"
#समावेश "callchain.h"
#समावेश "evsel.h"
#समावेश "event.h"
#समावेश "print_binary.h"
#समावेश "thread_map.h"
#समावेश "trace-event.h"
#समावेश "mmap.h"
#समावेश "stat.h"
#समावेश "metricgroup.h"
#समावेश "util/env.h"
#समावेश <पूर्णांकernal/lib.h>
#समावेश "util.h"

#अगर PY_MAJOR_VERSION < 3
#घोषणा _PyUnicode_FromString(arg) \
  PyString_FromString(arg)
#घोषणा _PyUnicode_AsString(arg) \
  PyString_AsString(arg)
#घोषणा _PyUnicode_FromFormat(...) \
  PyString_FromFormat(__VA_ARGS__)
#घोषणा _PyLong_FromLong(arg) \
  PyInt_FromLong(arg)

#अन्यथा

#घोषणा _PyUnicode_FromString(arg) \
  PyUnicode_FromString(arg)
#घोषणा _PyUnicode_FromFormat(...) \
  PyUnicode_FromFormat(__VA_ARGS__)
#घोषणा _PyLong_FromLong(arg) \
  PyLong_FromLong(arg)
#पूर्ण_अगर

#अगर_अघोषित Py_TYPE
#घोषणा Py_TYPE(ob) (((PyObject*)(ob))->ob_type)
#पूर्ण_अगर

/*
 * Provide these two so that we करोn't have to link against callchain.c and
 * start dragging hist.c, etc.
 */
काष्ठा callchain_param callchain_param;

पूर्णांक parse_callchain_record(स्थिर अक्षर *arg __maybe_unused,
			   काष्ठा callchain_param *param __maybe_unused)
अणु
	वापस 0;
पूर्ण

/*
 * Add this one here not to drag util/env.c
 */
काष्ठा perf_env perf_env;

/*
 * Add this one here not to drag util/stat-shaकरोw.c
 */
व्योम perf_stat__collect_metric_expr(काष्ठा evlist *evsel_list)
अणु
पूर्ण

/*
 * Add this one here not to drag util/metricgroup.c
 */
पूर्णांक metricgroup__copy_metric_events(काष्ठा evlist *evlist, काष्ठा cgroup *cgrp,
				    काष्ठा rblist *new_metric_events,
				    काष्ठा rblist *old_metric_events)
अणु
	वापस 0;
पूर्ण

/*
 * XXX: All these evsel deकाष्ठाors need some better mechanism, like a linked
 * list of deकाष्ठाors रेजिस्टरed when the relevant code indeed is used instead
 * of having more and more calls in perf_evsel__delete(). -- acme
 *
 * For now, add some more:
 *
 * Not to drag the BPF bandwagon...
 */
व्योम bpf_counter__destroy(काष्ठा evsel *evsel);
पूर्णांक bpf_counter__install_pe(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक fd);
पूर्णांक bpf_counter__disable(काष्ठा evsel *evsel);

व्योम bpf_counter__destroy(काष्ठा evsel *evsel __maybe_unused)
अणु
पूर्ण

पूर्णांक bpf_counter__install_pe(काष्ठा evsel *evsel __maybe_unused, पूर्णांक cpu __maybe_unused, पूर्णांक fd __maybe_unused)
अणु
	वापस 0;
पूर्ण

पूर्णांक bpf_counter__disable(काष्ठा evsel *evsel __maybe_unused)
अणु
	वापस 0;
पूर्ण

/*
 * Support debug prपूर्णांकing even though util/debug.c is not linked.  That means
 * implementing 'verbose' and 'eprintf'.
 */
पूर्णांक verbose;
पूर्णांक debug_peo_args;

पूर्णांक eम_लिखो(पूर्णांक level, पूर्णांक var, स्थिर अक्षर *fmt, ...);

पूर्णांक eम_लिखो(पूर्णांक level, पूर्णांक var, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक ret = 0;

	अगर (var >= level) अणु
		बहु_शुरू(args, fmt);
		ret = भख_लिखो(मानक_त्रुटि, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण

	वापस ret;
पूर्ण

/* Define PyVarObject_HEAD_INIT क्रम python 2.5 */
#अगर_अघोषित PyVarObject_HEAD_INIT
# define PyVarObject_HEAD_INIT(type, size) PyObject_HEAD_INIT(type) size,
#पूर्ण_अगर

#अगर PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initperf(व्योम);
#अन्यथा
PyMODINIT_FUNC PyInit_perf(व्योम);
#पूर्ण_अगर

#घोषणा member_def(type, member, ptype, help) \
	अणु #member, ptype, \
	  दुरत्व(काष्ठा pyrf_event, event) + दुरत्व(काष्ठा type, member), \
	  0, help पूर्ण

#घोषणा sample_member_def(name, member, ptype, help) \
	अणु #name, ptype, \
	  दुरत्व(काष्ठा pyrf_event, sample) + दुरत्व(काष्ठा perf_sample, member), \
	  0, help पूर्ण

काष्ठा pyrf_event अणु
	PyObject_HEAD
	काष्ठा evsel *evsel;
	काष्ठा perf_sample sample;
	जोड़ perf_event   event;
पूर्ण;

#घोषणा sample_members \
	sample_member_def(sample_ip, ip, T_ULONGLONG, "event type"),			 \
	sample_member_def(sample_pid, pid, T_INT, "event pid"),			 \
	sample_member_def(sample_tid, tid, T_INT, "event tid"),			 \
	sample_member_def(sample_समय, समय, T_ULONGLONG, "event timestamp"),		 \
	sample_member_def(sample_addr, addr, T_ULONGLONG, "event addr"),		 \
	sample_member_def(sample_id, id, T_ULONGLONG, "event id"),			 \
	sample_member_def(sample_stream_id, stream_id, T_ULONGLONG, "event stream id"), \
	sample_member_def(sample_period, period, T_ULONGLONG, "event period"),		 \
	sample_member_def(sample_cpu, cpu, T_UINT, "event cpu"),

अटल अक्षर pyrf_mmap_event__करोc[] = PyDoc_STR("perf mmap event object.");

अटल PyMemberDef pyrf_mmap_event__members[] = अणु
	sample_members
	member_def(perf_event_header, type, T_UINT, "event type"),
	member_def(perf_event_header, misc, T_UINT, "event misc"),
	member_def(perf_record_mmap, pid, T_UINT, "event pid"),
	member_def(perf_record_mmap, tid, T_UINT, "event tid"),
	member_def(perf_record_mmap, start, T_ULONGLONG, "start of the map"),
	member_def(perf_record_mmap, len, T_ULONGLONG, "map length"),
	member_def(perf_record_mmap, pgoff, T_ULONGLONG, "page offset"),
	member_def(perf_record_mmap, filename, T_STRING_INPLACE, "backing store"),
	अणु .name = शून्य, पूर्ण,
पूर्ण;

अटल PyObject *pyrf_mmap_event__repr(काष्ठा pyrf_event *pevent)
अणु
	PyObject *ret;
	अक्षर *s;

	अगर (aप्र_लिखो(&s, "{ type: mmap, pid: %u, tid: %u, start: %#" PRI_lx64 ", "
			 "length: %#" PRI_lx64 ", offset: %#" PRI_lx64 ", "
			 "filename: %s }",
		     pevent->event.mmap.pid, pevent->event.mmap.tid,
		     pevent->event.mmap.start, pevent->event.mmap.len,
		     pevent->event.mmap.pgoff, pevent->event.mmap.filename) < 0) अणु
		ret = PyErr_NoMemory();
	पूर्ण अन्यथा अणु
		ret = _PyUnicode_FromString(s);
		मुक्त(s);
	पूर्ण
	वापस ret;
पूर्ण

अटल PyTypeObject pyrf_mmap_event__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.mmap_event",
	.tp_basicsize	= माप(काष्ठा pyrf_event),
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_mmap_event__करोc,
	.tp_members	= pyrf_mmap_event__members,
	.tp_repr	= (reprfunc)pyrf_mmap_event__repr,
पूर्ण;

अटल अक्षर pyrf_task_event__करोc[] = PyDoc_STR("perf task (fork/exit) event object.");

अटल PyMemberDef pyrf_task_event__members[] = अणु
	sample_members
	member_def(perf_event_header, type, T_UINT, "event type"),
	member_def(perf_record_विभाजन, pid, T_UINT, "event pid"),
	member_def(perf_record_विभाजन, ppid, T_UINT, "event ppid"),
	member_def(perf_record_विभाजन, tid, T_UINT, "event tid"),
	member_def(perf_record_विभाजन, ptid, T_UINT, "event ptid"),
	member_def(perf_record_विभाजन, समय, T_ULONGLONG, "timestamp"),
	अणु .name = शून्य, पूर्ण,
पूर्ण;

अटल PyObject *pyrf_task_event__repr(काष्ठा pyrf_event *pevent)
अणु
	वापस _PyUnicode_FromFormat("{ type: %s, pid: %u, ppid: %u, tid: %u, "
				   "ptid: %u, time: %" PRI_lu64 "}",
				   pevent->event.header.type == PERF_RECORD_FORK ? "fork" : "exit",
				   pevent->event.विभाजन.pid,
				   pevent->event.विभाजन.ppid,
				   pevent->event.विभाजन.tid,
				   pevent->event.विभाजन.ptid,
				   pevent->event.विभाजन.समय);
पूर्ण

अटल PyTypeObject pyrf_task_event__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.task_event",
	.tp_basicsize	= माप(काष्ठा pyrf_event),
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_task_event__करोc,
	.tp_members	= pyrf_task_event__members,
	.tp_repr	= (reprfunc)pyrf_task_event__repr,
पूर्ण;

अटल अक्षर pyrf_comm_event__करोc[] = PyDoc_STR("perf comm event object.");

अटल PyMemberDef pyrf_comm_event__members[] = अणु
	sample_members
	member_def(perf_event_header, type, T_UINT, "event type"),
	member_def(perf_record_comm, pid, T_UINT, "event pid"),
	member_def(perf_record_comm, tid, T_UINT, "event tid"),
	member_def(perf_record_comm, comm, T_STRING_INPLACE, "process name"),
	अणु .name = शून्य, पूर्ण,
पूर्ण;

अटल PyObject *pyrf_comm_event__repr(काष्ठा pyrf_event *pevent)
अणु
	वापस _PyUnicode_FromFormat("{ type: comm, pid: %u, tid: %u, comm: %s }",
				   pevent->event.comm.pid,
				   pevent->event.comm.tid,
				   pevent->event.comm.comm);
पूर्ण

अटल PyTypeObject pyrf_comm_event__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.comm_event",
	.tp_basicsize	= माप(काष्ठा pyrf_event),
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_comm_event__करोc,
	.tp_members	= pyrf_comm_event__members,
	.tp_repr	= (reprfunc)pyrf_comm_event__repr,
पूर्ण;

अटल अक्षर pyrf_throttle_event__करोc[] = PyDoc_STR("perf throttle event object.");

अटल PyMemberDef pyrf_throttle_event__members[] = अणु
	sample_members
	member_def(perf_event_header, type, T_UINT, "event type"),
	member_def(perf_record_throttle, समय, T_ULONGLONG, "timestamp"),
	member_def(perf_record_throttle, id, T_ULONGLONG, "event id"),
	member_def(perf_record_throttle, stream_id, T_ULONGLONG, "event stream id"),
	अणु .name = शून्य, पूर्ण,
पूर्ण;

अटल PyObject *pyrf_throttle_event__repr(काष्ठा pyrf_event *pevent)
अणु
	काष्ठा perf_record_throttle *te = (काष्ठा perf_record_throttle *)(&pevent->event.header + 1);

	वापस _PyUnicode_FromFormat("{ type: %sthrottle, time: %" PRI_lu64 ", id: %" PRI_lu64
				   ", stream_id: %" PRI_lu64 " }",
				   pevent->event.header.type == PERF_RECORD_THROTTLE ? "" : "un",
				   te->समय, te->id, te->stream_id);
पूर्ण

अटल PyTypeObject pyrf_throttle_event__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.throttle_event",
	.tp_basicsize	= माप(काष्ठा pyrf_event),
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_throttle_event__करोc,
	.tp_members	= pyrf_throttle_event__members,
	.tp_repr	= (reprfunc)pyrf_throttle_event__repr,
पूर्ण;

अटल अक्षर pyrf_lost_event__करोc[] = PyDoc_STR("perf lost event object.");

अटल PyMemberDef pyrf_lost_event__members[] = अणु
	sample_members
	member_def(perf_record_lost, id, T_ULONGLONG, "event id"),
	member_def(perf_record_lost, lost, T_ULONGLONG, "number of lost events"),
	अणु .name = शून्य, पूर्ण,
पूर्ण;

अटल PyObject *pyrf_lost_event__repr(काष्ठा pyrf_event *pevent)
अणु
	PyObject *ret;
	अक्षर *s;

	अगर (aप्र_लिखो(&s, "{ type: lost, id: %#" PRI_lx64 ", "
			 "lost: %#" PRI_lx64 " }",
		     pevent->event.lost.id, pevent->event.lost.lost) < 0) अणु
		ret = PyErr_NoMemory();
	पूर्ण अन्यथा अणु
		ret = _PyUnicode_FromString(s);
		मुक्त(s);
	पूर्ण
	वापस ret;
पूर्ण

अटल PyTypeObject pyrf_lost_event__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.lost_event",
	.tp_basicsize	= माप(काष्ठा pyrf_event),
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_lost_event__करोc,
	.tp_members	= pyrf_lost_event__members,
	.tp_repr	= (reprfunc)pyrf_lost_event__repr,
पूर्ण;

अटल अक्षर pyrf_पढ़ो_event__करोc[] = PyDoc_STR("perf read event object.");

अटल PyMemberDef pyrf_पढ़ो_event__members[] = अणु
	sample_members
	member_def(perf_record_पढ़ो, pid, T_UINT, "event pid"),
	member_def(perf_record_पढ़ो, tid, T_UINT, "event tid"),
	अणु .name = शून्य, पूर्ण,
पूर्ण;

अटल PyObject *pyrf_पढ़ो_event__repr(काष्ठा pyrf_event *pevent)
अणु
	वापस _PyUnicode_FromFormat("{ type: read, pid: %u, tid: %u }",
				   pevent->event.पढ़ो.pid,
				   pevent->event.पढ़ो.tid);
	/*
 	 * FIXME: वापस the array of पढ़ो values,
 	 * making this method useful ;-)
 	 */
पूर्ण

अटल PyTypeObject pyrf_पढ़ो_event__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.read_event",
	.tp_basicsize	= माप(काष्ठा pyrf_event),
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_पढ़ो_event__करोc,
	.tp_members	= pyrf_पढ़ो_event__members,
	.tp_repr	= (reprfunc)pyrf_पढ़ो_event__repr,
पूर्ण;

अटल अक्षर pyrf_sample_event__करोc[] = PyDoc_STR("perf sample event object.");

अटल PyMemberDef pyrf_sample_event__members[] = अणु
	sample_members
	member_def(perf_event_header, type, T_UINT, "event type"),
	अणु .name = शून्य, पूर्ण,
पूर्ण;

अटल PyObject *pyrf_sample_event__repr(काष्ठा pyrf_event *pevent)
अणु
	PyObject *ret;
	अक्षर *s;

	अगर (aप्र_लिखो(&s, "{ type: sample }") < 0) अणु
		ret = PyErr_NoMemory();
	पूर्ण अन्यथा अणु
		ret = _PyUnicode_FromString(s);
		मुक्त(s);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool is_tracepoपूर्णांक(काष्ठा pyrf_event *pevent)
अणु
	वापस pevent->evsel->core.attr.type == PERF_TYPE_TRACEPOINT;
पूर्ण

अटल PyObject*
tracepoपूर्णांक_field(काष्ठा pyrf_event *pe, काष्ठा tep_क्रमmat_field *field)
अणु
	काष्ठा tep_handle *pevent = field->event->tep;
	व्योम *data = pe->sample.raw_data;
	PyObject *ret = शून्य;
	अचिन्हित दीर्घ दीर्घ val;
	अचिन्हित पूर्णांक offset, len;

	अगर (field->flags & TEP_FIELD_IS_ARRAY) अणु
		offset = field->offset;
		len    = field->size;
		अगर (field->flags & TEP_FIELD_IS_DYNAMIC) अणु
			val     = tep_पढ़ो_number(pevent, data + offset, len);
			offset  = val;
			len     = offset >> 16;
			offset &= 0xffff;
		पूर्ण
		अगर (field->flags & TEP_FIELD_IS_STRING &&
		    is_prपूर्णांकable_array(data + offset, len)) अणु
			ret = _PyUnicode_FromString((अक्षर *)data + offset);
		पूर्ण अन्यथा अणु
			ret = PyByteArray_FromStringAndSize((स्थिर अक्षर *) data + offset, len);
			field->flags &= ~TEP_FIELD_IS_STRING;
		पूर्ण
	पूर्ण अन्यथा अणु
		val = tep_पढ़ो_number(pevent, data + field->offset,
				      field->size);
		अगर (field->flags & TEP_FIELD_IS_POINTER)
			ret = PyLong_FromUnचिन्हितLong((अचिन्हित दीर्घ) val);
		अन्यथा अगर (field->flags & TEP_FIELD_IS_SIGNED)
			ret = PyLong_FromLong((दीर्घ) val);
		अन्यथा
			ret = PyLong_FromUnचिन्हितLong((अचिन्हित दीर्घ) val);
	पूर्ण

	वापस ret;
पूर्ण

अटल PyObject*
get_tracepoपूर्णांक_field(काष्ठा pyrf_event *pevent, PyObject *attr_name)
अणु
	स्थिर अक्षर *str = _PyUnicode_AsString(PyObject_Str(attr_name));
	काष्ठा evsel *evsel = pevent->evsel;
	काष्ठा tep_क्रमmat_field *field;

	अगर (!evsel->tp_क्रमmat) अणु
		काष्ठा tep_event *tp_क्रमmat;

		tp_क्रमmat = trace_event__tp_क्रमmat_id(evsel->core.attr.config);
		अगर (!tp_क्रमmat)
			वापस शून्य;

		evsel->tp_क्रमmat = tp_क्रमmat;
	पूर्ण

	field = tep_find_any_field(evsel->tp_क्रमmat, str);
	अगर (!field)
		वापस शून्य;

	वापस tracepoपूर्णांक_field(pevent, field);
पूर्ण

अटल PyObject*
pyrf_sample_event__getattro(काष्ठा pyrf_event *pevent, PyObject *attr_name)
अणु
	PyObject *obj = शून्य;

	अगर (is_tracepoपूर्णांक(pevent))
		obj = get_tracepoपूर्णांक_field(pevent, attr_name);

	वापस obj ?: PyObject_GenericGetAttr((PyObject *) pevent, attr_name);
पूर्ण

अटल PyTypeObject pyrf_sample_event__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.sample_event",
	.tp_basicsize	= माप(काष्ठा pyrf_event),
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_sample_event__करोc,
	.tp_members	= pyrf_sample_event__members,
	.tp_repr	= (reprfunc)pyrf_sample_event__repr,
	.tp_getattro	= (getattrofunc) pyrf_sample_event__getattro,
पूर्ण;

अटल अक्षर pyrf_context_चयन_event__करोc[] = PyDoc_STR("perf context_switch event object.");

अटल PyMemberDef pyrf_context_चयन_event__members[] = अणु
	sample_members
	member_def(perf_event_header, type, T_UINT, "event type"),
	member_def(perf_record_चयन, next_prev_pid, T_UINT, "next/prev pid"),
	member_def(perf_record_चयन, next_prev_tid, T_UINT, "next/prev tid"),
	अणु .name = शून्य, पूर्ण,
पूर्ण;

अटल PyObject *pyrf_context_चयन_event__repr(काष्ठा pyrf_event *pevent)
अणु
	PyObject *ret;
	अक्षर *s;

	अगर (aप्र_लिखो(&s, "{ type: context_switch, next_prev_pid: %u, next_prev_tid: %u, switch_out: %u }",
		     pevent->event.context_चयन.next_prev_pid,
		     pevent->event.context_चयन.next_prev_tid,
		     !!(pevent->event.header.misc & PERF_RECORD_MISC_SWITCH_OUT)) < 0) अणु
		ret = PyErr_NoMemory();
	पूर्ण अन्यथा अणु
		ret = _PyUnicode_FromString(s);
		मुक्त(s);
	पूर्ण
	वापस ret;
पूर्ण

अटल PyTypeObject pyrf_context_चयन_event__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.context_switch_event",
	.tp_basicsize	= माप(काष्ठा pyrf_event),
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_context_चयन_event__करोc,
	.tp_members	= pyrf_context_चयन_event__members,
	.tp_repr	= (reprfunc)pyrf_context_चयन_event__repr,
पूर्ण;

अटल पूर्णांक pyrf_event__setup_types(व्योम)
अणु
	पूर्णांक err;
	pyrf_mmap_event__type.tp_new =
	pyrf_task_event__type.tp_new =
	pyrf_comm_event__type.tp_new =
	pyrf_lost_event__type.tp_new =
	pyrf_पढ़ो_event__type.tp_new =
	pyrf_sample_event__type.tp_new =
	pyrf_context_चयन_event__type.tp_new =
	pyrf_throttle_event__type.tp_new = PyType_GenericNew;
	err = PyType_Ready(&pyrf_mmap_event__type);
	अगर (err < 0)
		जाओ out;
	err = PyType_Ready(&pyrf_lost_event__type);
	अगर (err < 0)
		जाओ out;
	err = PyType_Ready(&pyrf_task_event__type);
	अगर (err < 0)
		जाओ out;
	err = PyType_Ready(&pyrf_comm_event__type);
	अगर (err < 0)
		जाओ out;
	err = PyType_Ready(&pyrf_throttle_event__type);
	अगर (err < 0)
		जाओ out;
	err = PyType_Ready(&pyrf_पढ़ो_event__type);
	अगर (err < 0)
		जाओ out;
	err = PyType_Ready(&pyrf_sample_event__type);
	अगर (err < 0)
		जाओ out;
	err = PyType_Ready(&pyrf_context_चयन_event__type);
	अगर (err < 0)
		जाओ out;
out:
	वापस err;
पूर्ण

अटल PyTypeObject *pyrf_event__type[] = अणु
	[PERF_RECORD_MMAP]	 = &pyrf_mmap_event__type,
	[PERF_RECORD_LOST]	 = &pyrf_lost_event__type,
	[PERF_RECORD_COMM]	 = &pyrf_comm_event__type,
	[PERF_RECORD_EXIT]	 = &pyrf_task_event__type,
	[PERF_RECORD_THROTTLE]	 = &pyrf_throttle_event__type,
	[PERF_RECORD_UNTHROTTLE] = &pyrf_throttle_event__type,
	[PERF_RECORD_FORK]	 = &pyrf_task_event__type,
	[PERF_RECORD_READ]	 = &pyrf_पढ़ो_event__type,
	[PERF_RECORD_SAMPLE]	 = &pyrf_sample_event__type,
	[PERF_RECORD_SWITCH]	 = &pyrf_context_चयन_event__type,
	[PERF_RECORD_SWITCH_CPU_WIDE]  = &pyrf_context_चयन_event__type,
पूर्ण;

अटल PyObject *pyrf_event__new(जोड़ perf_event *event)
अणु
	काष्ठा pyrf_event *pevent;
	PyTypeObject *ptype;

	अगर ((event->header.type < PERF_RECORD_MMAP ||
	     event->header.type > PERF_RECORD_SAMPLE) &&
	    !(event->header.type == PERF_RECORD_SWITCH ||
	      event->header.type == PERF_RECORD_SWITCH_CPU_WIDE))
		वापस शून्य;

	ptype = pyrf_event__type[event->header.type];
	pevent = PyObject_New(काष्ठा pyrf_event, ptype);
	अगर (pevent != शून्य)
		स_नकल(&pevent->event, event, event->header.size);
	वापस (PyObject *)pevent;
पूर्ण

काष्ठा pyrf_cpu_map अणु
	PyObject_HEAD

	काष्ठा perf_cpu_map *cpus;
पूर्ण;

अटल पूर्णांक pyrf_cpu_map__init(काष्ठा pyrf_cpu_map *pcpus,
			      PyObject *args, PyObject *kwargs)
अणु
	अटल अक्षर *kwlist[] = अणु "cpustr", शून्य पूर्ण;
	अक्षर *cpustr = शून्य;

	अगर (!PyArg_ParseTupleAndKeywords(args, kwargs, "|s",
					 kwlist, &cpustr))
		वापस -1;

	pcpus->cpus = perf_cpu_map__new(cpustr);
	अगर (pcpus->cpus == शून्य)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम pyrf_cpu_map__delete(काष्ठा pyrf_cpu_map *pcpus)
अणु
	perf_cpu_map__put(pcpus->cpus);
	Py_TYPE(pcpus)->tp_मुक्त((PyObject*)pcpus);
पूर्ण

अटल Py_sमाप_प्रकार pyrf_cpu_map__length(PyObject *obj)
अणु
	काष्ठा pyrf_cpu_map *pcpus = (व्योम *)obj;

	वापस pcpus->cpus->nr;
पूर्ण

अटल PyObject *pyrf_cpu_map__item(PyObject *obj, Py_sमाप_प्रकार i)
अणु
	काष्ठा pyrf_cpu_map *pcpus = (व्योम *)obj;

	अगर (i >= pcpus->cpus->nr)
		वापस शून्य;

	वापस Py_BuildValue("i", pcpus->cpus->map[i]);
पूर्ण

अटल PySequenceMethods pyrf_cpu_map__sequence_methods = अणु
	.sq_length = pyrf_cpu_map__length,
	.sq_item   = pyrf_cpu_map__item,
पूर्ण;

अटल अक्षर pyrf_cpu_map__करोc[] = PyDoc_STR("cpu map object.");

अटल PyTypeObject pyrf_cpu_map__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.cpu_map",
	.tp_basicsize	= माप(काष्ठा pyrf_cpu_map),
	.tp_dealloc	= (deकाष्ठाor)pyrf_cpu_map__delete,
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_cpu_map__करोc,
	.tp_as_sequence	= &pyrf_cpu_map__sequence_methods,
	.tp_init	= (initproc)pyrf_cpu_map__init,
पूर्ण;

अटल पूर्णांक pyrf_cpu_map__setup_types(व्योम)
अणु
	pyrf_cpu_map__type.tp_new = PyType_GenericNew;
	वापस PyType_Ready(&pyrf_cpu_map__type);
पूर्ण

काष्ठा pyrf_thपढ़ो_map अणु
	PyObject_HEAD

	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
पूर्ण;

अटल पूर्णांक pyrf_thपढ़ो_map__init(काष्ठा pyrf_thपढ़ो_map *pthपढ़ोs,
				 PyObject *args, PyObject *kwargs)
अणु
	अटल अक्षर *kwlist[] = अणु "pid", "tid", "uid", शून्य पूर्ण;
	पूर्णांक pid = -1, tid = -1, uid = अच_पूर्णांक_उच्च;

	अगर (!PyArg_ParseTupleAndKeywords(args, kwargs, "|iii",
					 kwlist, &pid, &tid, &uid))
		वापस -1;

	pthपढ़ोs->thपढ़ोs = thपढ़ो_map__new(pid, tid, uid);
	अगर (pthपढ़ोs->thपढ़ोs == शून्य)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम pyrf_thपढ़ो_map__delete(काष्ठा pyrf_thपढ़ो_map *pthपढ़ोs)
अणु
	perf_thपढ़ो_map__put(pthपढ़ोs->thपढ़ोs);
	Py_TYPE(pthपढ़ोs)->tp_मुक्त((PyObject*)pthपढ़ोs);
पूर्ण

अटल Py_sमाप_प्रकार pyrf_thपढ़ो_map__length(PyObject *obj)
अणु
	काष्ठा pyrf_thपढ़ो_map *pthपढ़ोs = (व्योम *)obj;

	वापस pthपढ़ोs->thपढ़ोs->nr;
पूर्ण

अटल PyObject *pyrf_thपढ़ो_map__item(PyObject *obj, Py_sमाप_प्रकार i)
अणु
	काष्ठा pyrf_thपढ़ो_map *pthपढ़ोs = (व्योम *)obj;

	अगर (i >= pthपढ़ोs->thपढ़ोs->nr)
		वापस शून्य;

	वापस Py_BuildValue("i", pthपढ़ोs->thपढ़ोs->map[i]);
पूर्ण

अटल PySequenceMethods pyrf_thपढ़ो_map__sequence_methods = अणु
	.sq_length = pyrf_thपढ़ो_map__length,
	.sq_item   = pyrf_thपढ़ो_map__item,
पूर्ण;

अटल अक्षर pyrf_thपढ़ो_map__करोc[] = PyDoc_STR("thread map object.");

अटल PyTypeObject pyrf_thपढ़ो_map__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.thread_map",
	.tp_basicsize	= माप(काष्ठा pyrf_thपढ़ो_map),
	.tp_dealloc	= (deकाष्ठाor)pyrf_thपढ़ो_map__delete,
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_thपढ़ो_map__करोc,
	.tp_as_sequence	= &pyrf_thपढ़ो_map__sequence_methods,
	.tp_init	= (initproc)pyrf_thपढ़ो_map__init,
पूर्ण;

अटल पूर्णांक pyrf_thपढ़ो_map__setup_types(व्योम)
अणु
	pyrf_thपढ़ो_map__type.tp_new = PyType_GenericNew;
	वापस PyType_Ready(&pyrf_thपढ़ो_map__type);
पूर्ण

काष्ठा pyrf_evsel अणु
	PyObject_HEAD

	काष्ठा evsel evsel;
पूर्ण;

अटल पूर्णांक pyrf_evsel__init(काष्ठा pyrf_evsel *pevsel,
			    PyObject *args, PyObject *kwargs)
अणु
	काष्ठा perf_event_attr attr = अणु
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_CPU_CYCLES,
		.sample_type = PERF_SAMPLE_PERIOD | PERF_SAMPLE_TID,
	पूर्ण;
	अटल अक्षर *kwlist[] = अणु
		"type",
		"config",
		"sample_freq",
		"sample_period",
		"sample_type",
		"read_format",
		"disabled",
		"inherit",
		"pinned",
		"exclusive",
		"exclude_user",
		"exclude_kernel",
		"exclude_hv",
		"exclude_idle",
		"mmap",
		"context_switch",
		"comm",
		"freq",
		"inherit_stat",
		"enable_on_exec",
		"task",
		"watermark",
		"precise_ip",
		"mmap_data",
		"sample_id_all",
		"wakeup_events",
		"bp_type",
		"bp_addr",
		"bp_len",
		 शून्य
	पूर्ण;
	u64 sample_period = 0;
	u32 disabled = 0,
	    inherit = 0,
	    pinned = 0,
	    exclusive = 0,
	    exclude_user = 0,
	    exclude_kernel = 0,
	    exclude_hv = 0,
	    exclude_idle = 0,
	    mmap = 0,
	    context_चयन = 0,
	    comm = 0,
	    freq = 1,
	    inherit_stat = 0,
	    enable_on_exec = 0,
	    task = 0,
	    watermark = 0,
	    precise_ip = 0,
	    mmap_data = 0,
	    sample_id_all = 1;
	पूर्णांक idx = 0;

	अगर (!PyArg_ParseTupleAndKeywords(args, kwargs,
					 "|iKiKKiiiiiiiiiiiiiiiiiiiiiiKK", kwlist,
					 &attr.type, &attr.config, &attr.sample_freq,
					 &sample_period, &attr.sample_type,
					 &attr.पढ़ो_क्रमmat, &disabled, &inherit,
					 &pinned, &exclusive, &exclude_user,
					 &exclude_kernel, &exclude_hv, &exclude_idle,
					 &mmap, &context_चयन, &comm, &freq, &inherit_stat,
					 &enable_on_exec, &task, &watermark,
					 &precise_ip, &mmap_data, &sample_id_all,
					 &attr.wakeup_events, &attr.bp_type,
					 &attr.bp_addr, &attr.bp_len, &idx))
		वापस -1;

	/* जोड़... */
	अगर (sample_period != 0) अणु
		अगर (attr.sample_freq != 0)
			वापस -1; /* FIXME: throw right exception */
		attr.sample_period = sample_period;
	पूर्ण

	/* Bitfields */
	attr.disabled	    = disabled;
	attr.inherit	    = inherit;
	attr.pinned	    = pinned;
	attr.exclusive	    = exclusive;
	attr.exclude_user   = exclude_user;
	attr.exclude_kernel = exclude_kernel;
	attr.exclude_hv	    = exclude_hv;
	attr.exclude_idle   = exclude_idle;
	attr.mmap	    = mmap;
	attr.context_चयन = context_चयन;
	attr.comm	    = comm;
	attr.freq	    = freq;
	attr.inherit_stat   = inherit_stat;
	attr.enable_on_exec = enable_on_exec;
	attr.task	    = task;
	attr.watermark	    = watermark;
	attr.precise_ip	    = precise_ip;
	attr.mmap_data	    = mmap_data;
	attr.sample_id_all  = sample_id_all;
	attr.size	    = माप(attr);

	evsel__init(&pevsel->evsel, &attr, idx);
	वापस 0;
पूर्ण

अटल व्योम pyrf_evsel__delete(काष्ठा pyrf_evsel *pevsel)
अणु
	evsel__निकास(&pevsel->evsel);
	Py_TYPE(pevsel)->tp_मुक्त((PyObject*)pevsel);
पूर्ण

अटल PyObject *pyrf_evsel__खोलो(काष्ठा pyrf_evsel *pevsel,
				  PyObject *args, PyObject *kwargs)
अणु
	काष्ठा evsel *evsel = &pevsel->evsel;
	काष्ठा perf_cpu_map *cpus = शून्य;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = शून्य;
	PyObject *pcpus = शून्य, *pthपढ़ोs = शून्य;
	पूर्णांक group = 0, inherit = 0;
	अटल अक्षर *kwlist[] = अणु "cpus", "threads", "group", "inherit", शून्य पूर्ण;

	अगर (!PyArg_ParseTupleAndKeywords(args, kwargs, "|OOii", kwlist,
					 &pcpus, &pthपढ़ोs, &group, &inherit))
		वापस शून्य;

	अगर (pthपढ़ोs != शून्य)
		thपढ़ोs = ((काष्ठा pyrf_thपढ़ो_map *)pthपढ़ोs)->thपढ़ोs;

	अगर (pcpus != शून्य)
		cpus = ((काष्ठा pyrf_cpu_map *)pcpus)->cpus;

	evsel->core.attr.inherit = inherit;
	/*
	 * This will group just the fds क्रम this single evsel, to group
	 * multiple events, use evlist.खोलो().
	 */
	अगर (evsel__खोलो(evsel, cpus, thपढ़ोs) < 0) अणु
		PyErr_SetFromErrno(PyExc_OSError);
		वापस शून्य;
	पूर्ण

	Py_INCREF(Py_None);
	वापस Py_None;
पूर्ण

अटल PyMethodDef pyrf_evsel__methods[] = अणु
	अणु
		.ml_name  = "open",
		.ml_meth  = (PyCFunction)pyrf_evsel__खोलो,
		.ml_flags = METH_VARARGS | METH_KEYWORDS,
		.ml_करोc	  = PyDoc_STR("open the event selector file descriptor table.")
	पूर्ण,
	अणु .ml_name = शून्य, पूर्ण
पूर्ण;

अटल अक्षर pyrf_evsel__करोc[] = PyDoc_STR("perf event selector list object.");

अटल PyTypeObject pyrf_evsel__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.evsel",
	.tp_basicsize	= माप(काष्ठा pyrf_evsel),
	.tp_dealloc	= (deकाष्ठाor)pyrf_evsel__delete,
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_करोc		= pyrf_evsel__करोc,
	.tp_methods	= pyrf_evsel__methods,
	.tp_init	= (initproc)pyrf_evsel__init,
पूर्ण;

अटल पूर्णांक pyrf_evsel__setup_types(व्योम)
अणु
	pyrf_evsel__type.tp_new = PyType_GenericNew;
	वापस PyType_Ready(&pyrf_evsel__type);
पूर्ण

काष्ठा pyrf_evlist अणु
	PyObject_HEAD

	काष्ठा evlist evlist;
पूर्ण;

अटल पूर्णांक pyrf_evlist__init(काष्ठा pyrf_evlist *pevlist,
			     PyObject *args, PyObject *kwargs __maybe_unused)
अणु
	PyObject *pcpus = शून्य, *pthपढ़ोs = शून्य;
	काष्ठा perf_cpu_map *cpus;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;

	अगर (!PyArg_ParseTuple(args, "OO", &pcpus, &pthपढ़ोs))
		वापस -1;

	thपढ़ोs = ((काष्ठा pyrf_thपढ़ो_map *)pthपढ़ोs)->thपढ़ोs;
	cpus = ((काष्ठा pyrf_cpu_map *)pcpus)->cpus;
	evlist__init(&pevlist->evlist, cpus, thपढ़ोs);
	वापस 0;
पूर्ण

अटल व्योम pyrf_evlist__delete(काष्ठा pyrf_evlist *pevlist)
अणु
	evlist__निकास(&pevlist->evlist);
	Py_TYPE(pevlist)->tp_मुक्त((PyObject*)pevlist);
पूर्ण

अटल PyObject *pyrf_evlist__mmap(काष्ठा pyrf_evlist *pevlist,
				   PyObject *args, PyObject *kwargs)
अणु
	काष्ठा evlist *evlist = &pevlist->evlist;
	अटल अक्षर *kwlist[] = अणु "pages", "overwrite", शून्य पूर्ण;
	पूर्णांक pages = 128, overग_लिखो = false;

	अगर (!PyArg_ParseTupleAndKeywords(args, kwargs, "|ii", kwlist,
					 &pages, &overग_लिखो))
		वापस शून्य;

	अगर (evlist__mmap(evlist, pages) < 0) अणु
		PyErr_SetFromErrno(PyExc_OSError);
		वापस शून्य;
	पूर्ण

	Py_INCREF(Py_None);
	वापस Py_None;
पूर्ण

अटल PyObject *pyrf_evlist__poll(काष्ठा pyrf_evlist *pevlist,
				   PyObject *args, PyObject *kwargs)
अणु
	काष्ठा evlist *evlist = &pevlist->evlist;
	अटल अक्षर *kwlist[] = अणु "timeout", शून्य पूर्ण;
	पूर्णांक समयout = -1, n;

	अगर (!PyArg_ParseTupleAndKeywords(args, kwargs, "|i", kwlist, &समयout))
		वापस शून्य;

	n = evlist__poll(evlist, समयout);
	अगर (n < 0) अणु
		PyErr_SetFromErrno(PyExc_OSError);
		वापस शून्य;
	पूर्ण

	वापस Py_BuildValue("i", n);
पूर्ण

अटल PyObject *pyrf_evlist__get_pollfd(काष्ठा pyrf_evlist *pevlist,
					 PyObject *args __maybe_unused,
					 PyObject *kwargs __maybe_unused)
अणु
	काष्ठा evlist *evlist = &pevlist->evlist;
        PyObject *list = PyList_New(0);
	पूर्णांक i;

	क्रम (i = 0; i < evlist->core.pollfd.nr; ++i) अणु
		PyObject *file;
#अगर PY_MAJOR_VERSION < 3
		खाता *fp = fकरोpen(evlist->core.pollfd.entries[i].fd, "r");

		अगर (fp == शून्य)
			जाओ मुक्त_list;

		file = PyFile_FromFile(fp, "perf", "r", शून्य);
#अन्यथा
		file = PyFile_FromFd(evlist->core.pollfd.entries[i].fd, "perf", "r", -1,
				     शून्य, शून्य, शून्य, 0);
#पूर्ण_अगर
		अगर (file == शून्य)
			जाओ मुक्त_list;

		अगर (PyList_Append(list, file) != 0) अणु
			Py_DECREF(file);
			जाओ मुक्त_list;
		पूर्ण

		Py_DECREF(file);
	पूर्ण

	वापस list;
मुक्त_list:
	वापस PyErr_NoMemory();
पूर्ण


अटल PyObject *pyrf_evlist__add(काष्ठा pyrf_evlist *pevlist,
				  PyObject *args,
				  PyObject *kwargs __maybe_unused)
अणु
	काष्ठा evlist *evlist = &pevlist->evlist;
	PyObject *pevsel;
	काष्ठा evsel *evsel;

	अगर (!PyArg_ParseTuple(args, "O", &pevsel))
		वापस शून्य;

	Py_INCREF(pevsel);
	evsel = &((काष्ठा pyrf_evsel *)pevsel)->evsel;
	evsel->idx = evlist->core.nr_entries;
	evlist__add(evlist, evsel);

	वापस Py_BuildValue("i", evlist->core.nr_entries);
पूर्ण

अटल काष्ठा mmap *get_md(काष्ठा evlist *evlist, पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		काष्ठा mmap *md = &evlist->mmap[i];

		अगर (md->core.cpu == cpu)
			वापस md;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल PyObject *pyrf_evlist__पढ़ो_on_cpu(काष्ठा pyrf_evlist *pevlist,
					  PyObject *args, PyObject *kwargs)
अणु
	काष्ठा evlist *evlist = &pevlist->evlist;
	जोड़ perf_event *event;
	पूर्णांक sample_id_all = 1, cpu;
	अटल अक्षर *kwlist[] = अणु "cpu", "sample_id_all", शून्य पूर्ण;
	काष्ठा mmap *md;
	पूर्णांक err;

	अगर (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|i", kwlist,
					 &cpu, &sample_id_all))
		वापस शून्य;

	md = get_md(evlist, cpu);
	अगर (!md)
		वापस शून्य;

	अगर (perf_mmap__पढ़ो_init(&md->core) < 0)
		जाओ end;

	event = perf_mmap__पढ़ो_event(&md->core);
	अगर (event != शून्य) अणु
		PyObject *pyevent = pyrf_event__new(event);
		काष्ठा pyrf_event *pevent = (काष्ठा pyrf_event *)pyevent;
		काष्ठा evsel *evsel;

		अगर (pyevent == शून्य)
			वापस PyErr_NoMemory();

		evsel = evlist__event2evsel(evlist, event);
		अगर (!evsel) अणु
			Py_INCREF(Py_None);
			वापस Py_None;
		पूर्ण

		pevent->evsel = evsel;

		err = evsel__parse_sample(evsel, event, &pevent->sample);

		/* Consume the even only after we parsed it out. */
		perf_mmap__consume(&md->core);

		अगर (err)
			वापस PyErr_Format(PyExc_OSError,
					    "perf: can't parse sample, err=%d", err);
		वापस pyevent;
	पूर्ण
end:
	Py_INCREF(Py_None);
	वापस Py_None;
पूर्ण

अटल PyObject *pyrf_evlist__खोलो(काष्ठा pyrf_evlist *pevlist,
				   PyObject *args, PyObject *kwargs)
अणु
	काष्ठा evlist *evlist = &pevlist->evlist;
	पूर्णांक group = 0;
	अटल अक्षर *kwlist[] = अणु "group", शून्य पूर्ण;

	अगर (!PyArg_ParseTupleAndKeywords(args, kwargs, "|OOii", kwlist, &group))
		वापस शून्य;

	अगर (group)
		evlist__set_leader(evlist);

	अगर (evlist__खोलो(evlist) < 0) अणु
		PyErr_SetFromErrno(PyExc_OSError);
		वापस शून्य;
	पूर्ण

	Py_INCREF(Py_None);
	वापस Py_None;
पूर्ण

अटल PyMethodDef pyrf_evlist__methods[] = अणु
	अणु
		.ml_name  = "mmap",
		.ml_meth  = (PyCFunction)pyrf_evlist__mmap,
		.ml_flags = METH_VARARGS | METH_KEYWORDS,
		.ml_करोc	  = PyDoc_STR("mmap the file descriptor table.")
	पूर्ण,
	अणु
		.ml_name  = "open",
		.ml_meth  = (PyCFunction)pyrf_evlist__खोलो,
		.ml_flags = METH_VARARGS | METH_KEYWORDS,
		.ml_करोc	  = PyDoc_STR("open the file descriptors.")
	पूर्ण,
	अणु
		.ml_name  = "poll",
		.ml_meth  = (PyCFunction)pyrf_evlist__poll,
		.ml_flags = METH_VARARGS | METH_KEYWORDS,
		.ml_करोc	  = PyDoc_STR("poll the file descriptor table.")
	पूर्ण,
	अणु
		.ml_name  = "get_pollfd",
		.ml_meth  = (PyCFunction)pyrf_evlist__get_pollfd,
		.ml_flags = METH_VARARGS | METH_KEYWORDS,
		.ml_करोc	  = PyDoc_STR("get the poll file descriptor table.")
	पूर्ण,
	अणु
		.ml_name  = "add",
		.ml_meth  = (PyCFunction)pyrf_evlist__add,
		.ml_flags = METH_VARARGS | METH_KEYWORDS,
		.ml_करोc	  = PyDoc_STR("adds an event selector to the list.")
	पूर्ण,
	अणु
		.ml_name  = "read_on_cpu",
		.ml_meth  = (PyCFunction)pyrf_evlist__पढ़ो_on_cpu,
		.ml_flags = METH_VARARGS | METH_KEYWORDS,
		.ml_करोc	  = PyDoc_STR("reads an event.")
	पूर्ण,
	अणु .ml_name = शून्य, पूर्ण
पूर्ण;

अटल Py_sमाप_प्रकार pyrf_evlist__length(PyObject *obj)
अणु
	काष्ठा pyrf_evlist *pevlist = (व्योम *)obj;

	वापस pevlist->evlist.core.nr_entries;
पूर्ण

अटल PyObject *pyrf_evlist__item(PyObject *obj, Py_sमाप_प्रकार i)
अणु
	काष्ठा pyrf_evlist *pevlist = (व्योम *)obj;
	काष्ठा evsel *pos;

	अगर (i >= pevlist->evlist.core.nr_entries)
		वापस शून्य;

	evlist__क्रम_each_entry(&pevlist->evlist, pos) अणु
		अगर (i-- == 0)
			अवरोध;
	पूर्ण

	वापस Py_BuildValue("O", container_of(pos, काष्ठा pyrf_evsel, evsel));
पूर्ण

अटल PySequenceMethods pyrf_evlist__sequence_methods = अणु
	.sq_length = pyrf_evlist__length,
	.sq_item   = pyrf_evlist__item,
पूर्ण;

अटल अक्षर pyrf_evlist__करोc[] = PyDoc_STR("perf event selector list object.");

अटल PyTypeObject pyrf_evlist__type = अणु
	PyVarObject_HEAD_INIT(शून्य, 0)
	.tp_name	= "perf.evlist",
	.tp_basicsize	= माप(काष्ठा pyrf_evlist),
	.tp_dealloc	= (deकाष्ठाor)pyrf_evlist__delete,
	.tp_flags	= Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
	.tp_as_sequence	= &pyrf_evlist__sequence_methods,
	.tp_करोc		= pyrf_evlist__करोc,
	.tp_methods	= pyrf_evlist__methods,
	.tp_init	= (initproc)pyrf_evlist__init,
पूर्ण;

अटल पूर्णांक pyrf_evlist__setup_types(व्योम)
अणु
	pyrf_evlist__type.tp_new = PyType_GenericNew;
	वापस PyType_Ready(&pyrf_evlist__type);
पूर्ण

#घोषणा PERF_CONST(name) अणु #name, PERF_##name पूर्ण

अटल काष्ठा अणु
	स्थिर अक्षर *name;
	पूर्णांक	    value;
पूर्ण perf__स्थिरants[] = अणु
	PERF_CONST(TYPE_HARDWARE),
	PERF_CONST(TYPE_SOFTWARE),
	PERF_CONST(TYPE_TRACEPOINT),
	PERF_CONST(TYPE_HW_CACHE),
	PERF_CONST(TYPE_RAW),
	PERF_CONST(TYPE_BREAKPOINT),

	PERF_CONST(COUNT_HW_CPU_CYCLES),
	PERF_CONST(COUNT_HW_INSTRUCTIONS),
	PERF_CONST(COUNT_HW_CACHE_REFERENCES),
	PERF_CONST(COUNT_HW_CACHE_MISSES),
	PERF_CONST(COUNT_HW_BRANCH_INSTRUCTIONS),
	PERF_CONST(COUNT_HW_BRANCH_MISSES),
	PERF_CONST(COUNT_HW_BUS_CYCLES),
	PERF_CONST(COUNT_HW_CACHE_L1D),
	PERF_CONST(COUNT_HW_CACHE_L1I),
	PERF_CONST(COUNT_HW_CACHE_LL),
	PERF_CONST(COUNT_HW_CACHE_DTLB),
	PERF_CONST(COUNT_HW_CACHE_ITLB),
	PERF_CONST(COUNT_HW_CACHE_BPU),
	PERF_CONST(COUNT_HW_CACHE_OP_READ),
	PERF_CONST(COUNT_HW_CACHE_OP_WRITE),
	PERF_CONST(COUNT_HW_CACHE_OP_PREFETCH),
	PERF_CONST(COUNT_HW_CACHE_RESULT_ACCESS),
	PERF_CONST(COUNT_HW_CACHE_RESULT_MISS),

	PERF_CONST(COUNT_HW_STALLED_CYCLES_FRONTEND),
	PERF_CONST(COUNT_HW_STALLED_CYCLES_BACKEND),

	PERF_CONST(COUNT_SW_CPU_CLOCK),
	PERF_CONST(COUNT_SW_TASK_CLOCK),
	PERF_CONST(COUNT_SW_PAGE_FAULTS),
	PERF_CONST(COUNT_SW_CONTEXT_SWITCHES),
	PERF_CONST(COUNT_SW_CPU_MIGRATIONS),
	PERF_CONST(COUNT_SW_PAGE_FAULTS_MIN),
	PERF_CONST(COUNT_SW_PAGE_FAULTS_MAJ),
	PERF_CONST(COUNT_SW_ALIGNMENT_FAULTS),
	PERF_CONST(COUNT_SW_EMULATION_FAULTS),
	PERF_CONST(COUNT_SW_DUMMY),

	PERF_CONST(SAMPLE_IP),
	PERF_CONST(SAMPLE_TID),
	PERF_CONST(SAMPLE_TIME),
	PERF_CONST(SAMPLE_ADDR),
	PERF_CONST(SAMPLE_READ),
	PERF_CONST(SAMPLE_CALLCHAIN),
	PERF_CONST(SAMPLE_ID),
	PERF_CONST(SAMPLE_CPU),
	PERF_CONST(SAMPLE_PERIOD),
	PERF_CONST(SAMPLE_STREAM_ID),
	PERF_CONST(SAMPLE_RAW),

	PERF_CONST(FORMAT_TOTAL_TIME_ENABLED),
	PERF_CONST(FORMAT_TOTAL_TIME_RUNNING),
	PERF_CONST(FORMAT_ID),
	PERF_CONST(FORMAT_GROUP),

	PERF_CONST(RECORD_MMAP),
	PERF_CONST(RECORD_LOST),
	PERF_CONST(RECORD_COMM),
	PERF_CONST(RECORD_EXIT),
	PERF_CONST(RECORD_THROTTLE),
	PERF_CONST(RECORD_UNTHROTTLE),
	PERF_CONST(RECORD_FORK),
	PERF_CONST(RECORD_READ),
	PERF_CONST(RECORD_SAMPLE),
	PERF_CONST(RECORD_MMAP2),
	PERF_CONST(RECORD_AUX),
	PERF_CONST(RECORD_ITRACE_START),
	PERF_CONST(RECORD_LOST_SAMPLES),
	PERF_CONST(RECORD_SWITCH),
	PERF_CONST(RECORD_SWITCH_CPU_WIDE),

	PERF_CONST(RECORD_MISC_SWITCH_OUT),
	अणु .name = शून्य, पूर्ण,
पूर्ण;

अटल PyObject *pyrf__tracepoपूर्णांक(काष्ठा pyrf_evsel *pevsel,
				  PyObject *args, PyObject *kwargs)
अणु
	काष्ठा tep_event *tp_क्रमmat;
	अटल अक्षर *kwlist[] = अणु "sys", "name", शून्य पूर्ण;
	अक्षर *sys  = शून्य;
	अक्षर *name = शून्य;

	अगर (!PyArg_ParseTupleAndKeywords(args, kwargs, "|ss", kwlist,
					 &sys, &name))
		वापस शून्य;

	tp_क्रमmat = trace_event__tp_क्रमmat(sys, name);
	अगर (IS_ERR(tp_क्रमmat))
		वापस _PyLong_FromLong(-1);

	वापस _PyLong_FromLong(tp_क्रमmat->id);
पूर्ण

अटल PyMethodDef perf__methods[] = अणु
	अणु
		.ml_name  = "tracepoint",
		.ml_meth  = (PyCFunction) pyrf__tracepoपूर्णांक,
		.ml_flags = METH_VARARGS | METH_KEYWORDS,
		.ml_करोc	  = PyDoc_STR("Get tracepoint config.")
	पूर्ण,
	अणु .ml_name = शून्य, पूर्ण
पूर्ण;

#अगर PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initperf(व्योम)
#अन्यथा
PyMODINIT_FUNC PyInit_perf(व्योम)
#पूर्ण_अगर
अणु
	PyObject *obj;
	पूर्णांक i;
	PyObject *dict;
#अगर PY_MAJOR_VERSION < 3
	PyObject *module = Py_InitModule("perf", perf__methods);
#अन्यथा
	अटल काष्ठा PyModuleDef moduledef = अणु
		PyModuleDef_HEAD_INIT,
		"perf",			/* m_name */
		"",			/* m_करोc */
		-1,			/* m_size */
		perf__methods,		/* m_methods */
		शून्य,			/* m_reload */
		शून्य,			/* m_traverse */
		शून्य,			/* m_clear */
		शून्य,			/* m_मुक्त */
	पूर्ण;
	PyObject *module = PyModule_Create(&moduledef);
#पूर्ण_अगर

	अगर (module == शून्य ||
	    pyrf_event__setup_types() < 0 ||
	    pyrf_evlist__setup_types() < 0 ||
	    pyrf_evsel__setup_types() < 0 ||
	    pyrf_thपढ़ो_map__setup_types() < 0 ||
	    pyrf_cpu_map__setup_types() < 0)
#अगर PY_MAJOR_VERSION < 3
		वापस;
#अन्यथा
		वापस module;
#पूर्ण_अगर

	/* The page_size is placed in util object. */
	page_size = sysconf(_SC_PAGE_SIZE);

	Py_INCREF(&pyrf_evlist__type);
	PyModule_AddObject(module, "evlist", (PyObject*)&pyrf_evlist__type);

	Py_INCREF(&pyrf_evsel__type);
	PyModule_AddObject(module, "evsel", (PyObject*)&pyrf_evsel__type);

	Py_INCREF(&pyrf_mmap_event__type);
	PyModule_AddObject(module, "mmap_event", (PyObject *)&pyrf_mmap_event__type);

	Py_INCREF(&pyrf_lost_event__type);
	PyModule_AddObject(module, "lost_event", (PyObject *)&pyrf_lost_event__type);

	Py_INCREF(&pyrf_comm_event__type);
	PyModule_AddObject(module, "comm_event", (PyObject *)&pyrf_comm_event__type);

	Py_INCREF(&pyrf_task_event__type);
	PyModule_AddObject(module, "task_event", (PyObject *)&pyrf_task_event__type);

	Py_INCREF(&pyrf_throttle_event__type);
	PyModule_AddObject(module, "throttle_event", (PyObject *)&pyrf_throttle_event__type);

	Py_INCREF(&pyrf_task_event__type);
	PyModule_AddObject(module, "task_event", (PyObject *)&pyrf_task_event__type);

	Py_INCREF(&pyrf_पढ़ो_event__type);
	PyModule_AddObject(module, "read_event", (PyObject *)&pyrf_पढ़ो_event__type);

	Py_INCREF(&pyrf_sample_event__type);
	PyModule_AddObject(module, "sample_event", (PyObject *)&pyrf_sample_event__type);

	Py_INCREF(&pyrf_context_चयन_event__type);
	PyModule_AddObject(module, "switch_event", (PyObject *)&pyrf_context_चयन_event__type);

	Py_INCREF(&pyrf_thपढ़ो_map__type);
	PyModule_AddObject(module, "thread_map", (PyObject*)&pyrf_thपढ़ो_map__type);

	Py_INCREF(&pyrf_cpu_map__type);
	PyModule_AddObject(module, "cpu_map", (PyObject*)&pyrf_cpu_map__type);

	dict = PyModule_GetDict(module);
	अगर (dict == शून्य)
		जाओ error;

	क्रम (i = 0; perf__स्थिरants[i].name != शून्य; i++) अणु
		obj = _PyLong_FromLong(perf__स्थिरants[i].value);
		अगर (obj == शून्य)
			जाओ error;
		PyDict_SetItemString(dict, perf__स्थिरants[i].name, obj);
		Py_DECREF(obj);
	पूर्ण

error:
	अगर (PyErr_Occurred())
		PyErr_SetString(PyExc_ImportError, "perf: Init failed!");
#अगर PY_MAJOR_VERSION >= 3
	वापस module;
#पूर्ण_अगर
पूर्ण

/*
 * Dummy, to aव्योम dragging all the test_attr infraकाष्ठाure in the python
 * binding.
 */
व्योम test_attr__खोलो(काष्ठा perf_event_attr *attr, pid_t pid, पूर्णांक cpu,
                     पूर्णांक fd, पूर्णांक group_fd, अचिन्हित दीर्घ flags)
अणु
पूर्ण
