<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/err.h>
#समावेश <traceevent/event-parse.h>
#समावेश "evsel.h"
#समावेश "tests.h"
#समावेश "debug.h"

अटल पूर्णांक evsel__test_field(काष्ठा evsel *evsel, स्थिर अक्षर *name, पूर्णांक size, bool should_be_चिन्हित)
अणु
	काष्ठा tep_क्रमmat_field *field = evsel__field(evsel, name);
	पूर्णांक is_चिन्हित;
	पूर्णांक ret = 0;

	अगर (field == शून्य) अणु
		pr_debug("%s: \"%s\" field not found!\n", evsel->name, name);
		वापस -1;
	पूर्ण

	is_चिन्हित = !!(field->flags & TEP_FIELD_IS_SIGNED);
	अगर (should_be_चिन्हित && !is_चिन्हित) अणु
		pr_debug("%s: \"%s\" signedness(%d) is wrong, should be %d\n",
			 evsel->name, name, is_चिन्हित, should_be_चिन्हित);
		ret = -1;
	पूर्ण

	अगर (field->size != size) अणु
		pr_debug("%s: \"%s\" size (%d) should be %d!\n",
			 evsel->name, name, field->size, size);
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक test__perf_evsel__tp_sched_test(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा evsel *evsel = evsel__newtp("sched", "sched_switch");
	पूर्णांक ret = 0;

	अगर (IS_ERR(evsel)) अणु
		pr_debug("evsel__newtp failed with %ld\n", PTR_ERR(evsel));
		वापस -1;
	पूर्ण

	अगर (evsel__test_field(evsel, "prev_comm", 16, false))
		ret = -1;

	अगर (evsel__test_field(evsel, "prev_pid", 4, true))
		ret = -1;

	अगर (evsel__test_field(evsel, "prev_prio", 4, true))
		ret = -1;

	अगर (evsel__test_field(evsel, "prev_state", माप(दीर्घ), true))
		ret = -1;

	अगर (evsel__test_field(evsel, "next_comm", 16, false))
		ret = -1;

	अगर (evsel__test_field(evsel, "next_pid", 4, true))
		ret = -1;

	अगर (evsel__test_field(evsel, "next_prio", 4, true))
		ret = -1;

	evsel__delete(evsel);

	evsel = evsel__newtp("sched", "sched_wakeup");

	अगर (IS_ERR(evsel)) अणु
		pr_debug("evsel__newtp failed with %ld\n", PTR_ERR(evsel));
		वापस -1;
	पूर्ण

	अगर (evsel__test_field(evsel, "comm", 16, false))
		ret = -1;

	अगर (evsel__test_field(evsel, "pid", 4, true))
		ret = -1;

	अगर (evsel__test_field(evsel, "prio", 4, true))
		ret = -1;

	अगर (evsel__test_field(evsel, "target_cpu", 4, true))
		ret = -1;

	evsel__delete(evsel);
	वापस ret;
पूर्ण
