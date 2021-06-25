<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/zभाग.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <सीमा.स>
#समावेश <unistd.h>
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "machine.h"
#समावेश "event.h"
#समावेश "../util/unwind.h"
#समावेश "perf_regs.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "thread.h"
#समावेश "callchain.h"
#समावेश "util/synthetic-events.h"

#अगर defined (__x86_64__) || defined (__i386__) || defined (__घातerpc__)
#समावेश "arch-tests.h"
#पूर्ण_अगर

/* For द्वा_खोज. We try to unwind functions in shared object. */
#समावेश <मानककोष.स>

अटल पूर्णांक mmap_handler(काष्ठा perf_tool *tool __maybe_unused,
			जोड़ perf_event *event,
			काष्ठा perf_sample *sample,
			काष्ठा machine *machine)
अणु
	वापस machine__process_mmap2_event(machine, event, sample);
पूर्ण

अटल पूर्णांक init_live_machine(काष्ठा machine *machine)
अणु
	जोड़ perf_event event;
	pid_t pid = getpid();

	स_रखो(&event, 0, माप(event));
	वापस perf_event__synthesize_mmap_events(शून्य, &event, pid, pid,
						  mmap_handler, machine, true);
पूर्ण

/*
 * We need to keep these functions global, despite the
 * fact that they are used only locally in this object,
 * in order to keep them around even अगर the binary is
 * stripped. If they are gone, the unwind check क्रम
 * symbol fails.
 */
पूर्णांक test_dwarf_unwind__thपढ़ो(काष्ठा thपढ़ो *thपढ़ो);
पूर्णांक test_dwarf_unwind__compare(व्योम *p1, व्योम *p2);
पूर्णांक test_dwarf_unwind__krava_3(काष्ठा thपढ़ो *thपढ़ो);
पूर्णांक test_dwarf_unwind__krava_2(काष्ठा thपढ़ो *thपढ़ो);
पूर्णांक test_dwarf_unwind__krava_1(काष्ठा thपढ़ो *thपढ़ो);

#घोषणा MAX_STACK 8

अटल पूर्णांक unwind_entry(काष्ठा unwind_entry *entry, व्योम *arg)
अणु
	अचिन्हित दीर्घ *cnt = (अचिन्हित दीर्घ *) arg;
	अक्षर *symbol = entry->ms.sym ? entry->ms.sym->name : शून्य;
	अटल स्थिर अक्षर *funcs[MAX_STACK] = अणु
		"test__arch_unwind_sample",
		"test_dwarf_unwind__thread",
		"test_dwarf_unwind__compare",
		"bsearch",
		"test_dwarf_unwind__krava_3",
		"test_dwarf_unwind__krava_2",
		"test_dwarf_unwind__krava_1",
		"test__dwarf_unwind"
	पूर्ण;
	/*
	 * The funcs[MAX_STACK] array index, based on the
	 * callchain order setup.
	 */
	पूर्णांक idx = callchain_param.order == ORDER_CALLER ?
		  MAX_STACK - *cnt - 1 : *cnt;

	अगर (*cnt >= MAX_STACK) अणु
		pr_debug("failed: crossed the max stack value %d\n", MAX_STACK);
		वापस -1;
	पूर्ण

	अगर (!symbol) अणु
		pr_debug("failed: got unresolved address 0x%" PRIx64 "\n",
			 entry->ip);
		वापस -1;
	पूर्ण

	(*cnt)++;
	pr_debug("got: %s 0x%" PRIx64 ", expecting %s\n",
		 symbol, entry->ip, funcs[idx]);
	वापस म_भेद((स्थिर अक्षर *) symbol, funcs[idx]);
पूर्ण

noअंतरभूत पूर्णांक test_dwarf_unwind__thपढ़ो(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा perf_sample sample;
	अचिन्हित दीर्घ cnt = 0;
	पूर्णांक err = -1;

	स_रखो(&sample, 0, माप(sample));

	अगर (test__arch_unwind_sample(&sample, thपढ़ो)) अणु
		pr_debug("failed to get unwind sample\n");
		जाओ out;
	पूर्ण

	err = unwind__get_entries(unwind_entry, &cnt, thपढ़ो,
				  &sample, MAX_STACK);
	अगर (err)
		pr_debug("unwind failed\n");
	अन्यथा अगर (cnt != MAX_STACK) अणु
		pr_debug("got wrong number of stack entries %lu != %d\n",
			 cnt, MAX_STACK);
		err = -1;
	पूर्ण

 out:
	zमुक्त(&sample.user_stack.data);
	zमुक्त(&sample.user_regs.regs);
	वापस err;
पूर्ण

अटल पूर्णांक global_unwind_retval = -पूर्णांक_उच्च;

noअंतरभूत पूर्णांक test_dwarf_unwind__compare(व्योम *p1, व्योम *p2)
अणु
	/* Any possible value should be 'thread' */
	काष्ठा thपढ़ो *thपढ़ो = *(काष्ठा thपढ़ो **)p1;

	अगर (global_unwind_retval == -पूर्णांक_उच्च) अणु
		/* Call unwinder twice क्रम both callchain orders. */
		callchain_param.order = ORDER_CALLER;

		global_unwind_retval = test_dwarf_unwind__thपढ़ो(thपढ़ो);
		अगर (!global_unwind_retval) अणु
			callchain_param.order = ORDER_CALLEE;
			global_unwind_retval = test_dwarf_unwind__thपढ़ो(thपढ़ो);
		पूर्ण
	पूर्ण

	वापस p1 - p2;
पूर्ण

noअंतरभूत पूर्णांक test_dwarf_unwind__krava_3(काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा thपढ़ो *array[2] = अणुthपढ़ो, thपढ़ोपूर्ण;
	व्योम *fp = &द्वा_खोज;
	/*
	 * make _द्वा_खोज a अस्थिर function poपूर्णांकer to
	 * prevent potential optimization, which may expand
	 * द्वा_खोज and call compare directly from this function,
	 * instead of libc shared object.
	 */
	व्योम *(*अस्थिर _द्वा_खोज)(व्योम *, व्योम *, माप_प्रकार,
			माप_प्रकार, पूर्णांक (*)(व्योम *, व्योम *));

	_द्वा_खोज = fp;
	_द्वा_खोज(array, &thपढ़ो, 2, माप(काष्ठा thपढ़ो **),
		 test_dwarf_unwind__compare);
	वापस global_unwind_retval;
पूर्ण

noअंतरभूत पूर्णांक test_dwarf_unwind__krava_2(काष्ठा thपढ़ो *thपढ़ो)
अणु
	वापस test_dwarf_unwind__krava_3(thपढ़ो);
पूर्ण

noअंतरभूत पूर्णांक test_dwarf_unwind__krava_1(काष्ठा thपढ़ो *thपढ़ो)
अणु
	वापस test_dwarf_unwind__krava_2(thपढ़ो);
पूर्ण

पूर्णांक test__dwarf_unwind(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा machine *machine;
	काष्ठा thपढ़ो *thपढ़ो;
	पूर्णांक err = -1;

	machine = machine__new_host();
	अगर (!machine) अणु
		pr_err("Could not get machine\n");
		वापस -1;
	पूर्ण

	अगर (machine__create_kernel_maps(machine)) अणु
		pr_err("Failed to create kernel maps\n");
		वापस -1;
	पूर्ण

	callchain_param.record_mode = CALLCHAIN_DWARF;
	dwarf_callchain_users = true;

	अगर (init_live_machine(machine)) अणु
		pr_err("Could not init machine\n");
		जाओ out;
	पूर्ण

	अगर (verbose > 1)
		machine__ख_लिखो(machine, मानक_त्रुटि);

	thपढ़ो = machine__find_thपढ़ो(machine, getpid(), getpid());
	अगर (!thपढ़ो) अणु
		pr_err("Could not get thread\n");
		जाओ out;
	पूर्ण

	err = test_dwarf_unwind__krava_1(thपढ़ो);
	thपढ़ो__put(thपढ़ो);

 out:
	machine__delete_thपढ़ोs(machine);
	machine__delete(machine);
	वापस err;
पूर्ण
