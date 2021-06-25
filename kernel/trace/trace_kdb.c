<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kdb helper क्रम dumping the ftrace buffer
 *
 * Copyright (C) 2010 Jason Wessel <jason.wessel@windriver.com>
 *
 * ftrace_dump_buf based on ftrace_dump:
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 * Copyright (C) 2008 Ingo Molnar <mingo@redhat.com>
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdb.h>
#समावेश <linux/ftrace.h>

#समावेश "trace.h"
#समावेश "trace_output.h"

अटल काष्ठा trace_iterator iter;
अटल काष्ठा ring_buffer_iter *buffer_iter[CONFIG_NR_CPUS];

अटल व्योम ftrace_dump_buf(पूर्णांक skip_entries, दीर्घ cpu_file)
अणु
	काष्ठा trace_array *tr;
	अचिन्हित पूर्णांक old_userobj;
	पूर्णांक cnt = 0, cpu;

	tr = iter.tr;

	old_userobj = tr->trace_flags;

	/* करोn't look at user memory in panic mode */
	tr->trace_flags &= ~TRACE_ITER_SYM_USEROBJ;

	kdb_म_लिखो("Dumping ftrace buffer:\n");
	अगर (skip_entries)
		kdb_म_लिखो("(skipping %d entries)\n", skip_entries);

	trace_iterator_reset(&iter);
	iter.iter_flags |= TRACE_खाता_LAT_FMT;

	अगर (cpu_file == RING_BUFFER_ALL_CPUS) अणु
		क्रम_each_tracing_cpu(cpu) अणु
			iter.buffer_iter[cpu] =
			ring_buffer_पढ़ो_prepare(iter.array_buffer->buffer,
						 cpu, GFP_ATOMIC);
			ring_buffer_पढ़ो_start(iter.buffer_iter[cpu]);
			tracing_iter_reset(&iter, cpu);
		पूर्ण
	पूर्ण अन्यथा अणु
		iter.cpu_file = cpu_file;
		iter.buffer_iter[cpu_file] =
			ring_buffer_पढ़ो_prepare(iter.array_buffer->buffer,
						 cpu_file, GFP_ATOMIC);
		ring_buffer_पढ़ो_start(iter.buffer_iter[cpu_file]);
		tracing_iter_reset(&iter, cpu_file);
	पूर्ण

	जबतक (trace_find_next_entry_inc(&iter)) अणु
		अगर (!cnt)
			kdb_म_लिखो("---------------------------------\n");
		cnt++;

		अगर (!skip_entries) अणु
			prपूर्णांक_trace_line(&iter);
			trace_prपूर्णांकk_seq(&iter.seq);
		पूर्ण अन्यथा अणु
			skip_entries--;
		पूर्ण

		अगर (KDB_FLAG(CMD_INTERRUPT))
			जाओ out;
	पूर्ण

	अगर (!cnt)
		kdb_म_लिखो("   (ftrace buffer empty)\n");
	अन्यथा
		kdb_म_लिखो("---------------------------------\n");

out:
	tr->trace_flags = old_userobj;

	क्रम_each_tracing_cpu(cpu) अणु
		अगर (iter.buffer_iter[cpu]) अणु
			ring_buffer_पढ़ो_finish(iter.buffer_iter[cpu]);
			iter.buffer_iter[cpu] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * kdb_ftdump - Dump the ftrace log buffer
 */
अटल पूर्णांक kdb_ftdump(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक skip_entries = 0;
	दीर्घ cpu_file;
	अक्षर *cp;
	पूर्णांक cnt;
	पूर्णांक cpu;

	अगर (argc > 2)
		वापस KDB_ARGCOUNT;

	अगर (argc) अणु
		skip_entries = simple_म_से_दीर्घ(argv[1], &cp, 0);
		अगर (*cp)
			skip_entries = 0;
	पूर्ण

	अगर (argc == 2) अणु
		cpu_file = simple_म_से_दीर्घ(argv[2], &cp, 0);
		अगर (*cp || cpu_file >= NR_CPUS || cpu_file < 0 ||
		    !cpu_online(cpu_file))
			वापस KDB_BADINT;
	पूर्ण अन्यथा अणु
		cpu_file = RING_BUFFER_ALL_CPUS;
	पूर्ण

	kdb_trap_prपूर्णांकk++;

	trace_init_global_iter(&iter);
	iter.buffer_iter = buffer_iter;

	क्रम_each_tracing_cpu(cpu) अणु
		atomic_inc(&per_cpu_ptr(iter.array_buffer->data, cpu)->disabled);
	पूर्ण

	/* A negative skip_entries means skip all but the last entries */
	अगर (skip_entries < 0) अणु
		अगर (cpu_file == RING_BUFFER_ALL_CPUS)
			cnt = trace_total_entries(शून्य);
		अन्यथा
			cnt = trace_total_entries_cpu(शून्य, cpu_file);
		skip_entries = max(cnt + skip_entries, 0);
	पूर्ण

	ftrace_dump_buf(skip_entries, cpu_file);

	क्रम_each_tracing_cpu(cpu) अणु
		atomic_dec(&per_cpu_ptr(iter.array_buffer->data, cpu)->disabled);
	पूर्ण

	kdb_trap_prपूर्णांकk--;

	वापस 0;
पूर्ण

अटल __init पूर्णांक kdb_ftrace_रेजिस्टर(व्योम)
अणु
	kdb_रेजिस्टर_flags("ftdump", kdb_ftdump, "[skip_#entries] [cpu]",
			    "Dump ftrace log; -skip dumps last #entries", 0,
			    KDB_ENABLE_ALWAYS_SAFE);
	वापस 0;
पूर्ण

late_initcall(kdb_ftrace_रेजिस्टर);
