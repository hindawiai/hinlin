<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <traceevent/event-parse.h>
#समावेश <api/fs/tracing_path.h>
#समावेश <api/fs/fs.h>
#समावेश "trace-event.h"
#समावेश "machine.h"

/*
 * global trace_event object used by trace_event__tp_क्रमmat
 *
 * TODO There's no cleanup call क्रम this. Add some sort of
 * __निकास function support and call trace_event__cleanup
 * there.
 */
अटल काष्ठा trace_event tevent;
अटल bool tevent_initialized;

पूर्णांक trace_event__init(काष्ठा trace_event *t)
अणु
	काष्ठा tep_handle *pevent = tep_alloc();

	अगर (pevent) अणु
		t->plugin_list = tep_load_plugins(pevent);
		t->pevent  = pevent;
	पूर्ण

	वापस pevent ? 0 : -1;
पूर्ण

अटल पूर्णांक trace_event__init2(व्योम)
अणु
	पूर्णांक be = tep_is_bigendian();
	काष्ठा tep_handle *pevent;

	अगर (trace_event__init(&tevent))
		वापस -1;

	pevent = tevent.pevent;
	tep_set_flag(pevent, TEP_NSEC_OUTPUT);
	tep_set_file_bigendian(pevent, be);
	tep_set_local_bigendian(pevent, be);
	tevent_initialized = true;
	वापस 0;
पूर्ण

पूर्णांक trace_event__रेजिस्टर_resolver(काष्ठा machine *machine,
				   tep_func_resolver_t *func)
अणु
	अगर (!tevent_initialized && trace_event__init2())
		वापस -1;

	वापस tep_set_function_resolver(tevent.pevent, func, machine);
पूर्ण

व्योम trace_event__cleanup(काष्ठा trace_event *t)
अणु
	tep_unload_plugins(t->plugin_list, t->pevent);
	tep_मुक्त(t->pevent);
पूर्ण

/*
 * Returns poपूर्णांकer with encoded error via <linux/err.h> पूर्णांकerface.
 */
अटल काष्ठा tep_event*
tp_क्रमmat(स्थिर अक्षर *sys, स्थिर अक्षर *name)
अणु
	अक्षर *tp_dir = get_events_file(sys);
	काष्ठा tep_handle *pevent = tevent.pevent;
	काष्ठा tep_event *event = शून्य;
	अक्षर path[PATH_MAX];
	माप_प्रकार size;
	अक्षर *data;
	पूर्णांक err;

	अगर (!tp_dir)
		वापस ERR_PTR(-त्रुटि_सं);

	scnम_लिखो(path, PATH_MAX, "%s/%s/format", tp_dir, name);
	put_events_file(tp_dir);

	err = filename__पढ़ो_str(path, &data, &size);
	अगर (err)
		वापस ERR_PTR(err);

	tep_parse_क्रमmat(pevent, &event, data, size, sys);

	मुक्त(data);
	वापस event;
पूर्ण

/*
 * Returns poपूर्णांकer with encoded error via <linux/err.h> पूर्णांकerface.
 */
काष्ठा tep_event*
trace_event__tp_क्रमmat(स्थिर अक्षर *sys, स्थिर अक्षर *name)
अणु
	अगर (!tevent_initialized && trace_event__init2())
		वापस ERR_PTR(-ENOMEM);

	वापस tp_क्रमmat(sys, name);
पूर्ण

काष्ठा tep_event *trace_event__tp_क्रमmat_id(पूर्णांक id)
अणु
	अगर (!tevent_initialized && trace_event__init2())
		वापस ERR_PTR(-ENOMEM);

	वापस tep_find_event(tevent.pevent, id);
पूर्ण
