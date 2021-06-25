<शैली गुरु>
/*
 * Kernel Debugger Architecture Independent Stack Traceback
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1999-2004 Silicon Graphics, Inc.  All Rights Reserved.
 * Copyright (c) 2009 Wind River Systems, Inc.  All Rights Reserved.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/kdb.h>
#समावेश <linux/nmi.h>
#समावेश "kdb_private.h"


अटल व्योम kdb_show_stack(काष्ठा task_काष्ठा *p, व्योम *addr)
अणु
	kdb_trap_prपूर्णांकk++;

	अगर (!addr && kdb_task_has_cpu(p)) अणु
		पूर्णांक old_lvl = console_loglevel;

		console_loglevel = CONSOLE_LOGLEVEL_MOTORMOUTH;
		kdb_dump_stack_on_cpu(kdb_process_cpu(p));
		console_loglevel = old_lvl;
	पूर्ण अन्यथा अणु
		show_stack(p, addr, KERN_EMERG);
	पूर्ण

	kdb_trap_prपूर्णांकk--;
पूर्ण

/*
 * kdb_bt
 *
 *	This function implements the 'bt' command.  Prपूर्णांक a stack
 *	traceback.
 *
 *	bt [<address-expression>]	(addr-exp is क्रम alternate stacks)
 *	btp <pid>			Kernel stack क्रम <pid>
 *	btt <address-expression>	Kernel stack क्रम task काष्ठाure at
 *					<address-expression>
 *	bta [DRSTCZEUIMA]		All useful processes, optionally
 *					filtered by state
 *	btc [<cpu>]			The current process on one cpu,
 *					शेष is all cpus
 *
 *	bt <address-expression> refers to a address on the stack, that location
 *	is assumed to contain a वापस address.
 *
 *	btt <address-expression> refers to the address of a काष्ठा task.
 *
 * Inमाला_दो:
 *	argc	argument count
 *	argv	argument vector
 * Outमाला_दो:
 *	None.
 * Returns:
 *	zero क्रम success, a kdb diagnostic अगर error
 * Locking:
 *	none.
 * Remarks:
 *	Backtrack works best when the code uses frame poपूर्णांकers.  But even
 *	without frame poपूर्णांकers we should get a reasonable trace.
 *
 *	mds comes in handy when examining the stack to करो a manual traceback or
 *	to get a starting poपूर्णांक क्रम bt <address-expression>.
 */

अटल पूर्णांक
kdb_bt1(काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ mask, bool btaprompt)
अणु
	अक्षर ch;

	अगर (kdb_getarea(ch, (अचिन्हित दीर्घ)p) ||
	    kdb_getarea(ch, (अचिन्हित दीर्घ)(p+1)-1))
		वापस KDB_BADADDR;
	अगर (!kdb_task_state(p, mask))
		वापस 0;
	kdb_म_लिखो("Stack traceback for pid %d\n", p->pid);
	kdb_ps1(p);
	kdb_show_stack(p, शून्य);
	अगर (btaprompt) अणु
		kdb_म_लिखो("Enter <q> to end, <cr> or <space> to continue:");
		करो अणु
			ch = kdb_अक्षर_लो();
		पूर्ण जबतक (!म_अक्षर("\r\n q", ch));
		kdb_म_लिखो("\n");

		/* reset the pager */
		kdb_nextline = 1;

		अगर (ch == 'q')
			वापस 1;
	पूर्ण
	touch_nmi_watchकरोg();
	वापस 0;
पूर्ण

अटल व्योम
kdb_bt_cpu(अचिन्हित दीर्घ cpu)
अणु
	काष्ठा task_काष्ठा *kdb_tsk;

	अगर (cpu >= num_possible_cpus() || !cpu_online(cpu)) अणु
		kdb_म_लिखो("WARNING: no process for cpu %ld\n", cpu);
		वापस;
	पूर्ण

	/* If a CPU failed to round up we could be here */
	kdb_tsk = KDB_TSK(cpu);
	अगर (!kdb_tsk) अणु
		kdb_म_लिखो("WARNING: no task for cpu %ld\n", cpu);
		वापस;
	पूर्ण

	kdb_bt1(kdb_tsk, ~0UL, false);
पूर्ण

पूर्णांक
kdb_bt(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक diag;
	पूर्णांक btaprompt = 1;
	पूर्णांक nextarg;
	अचिन्हित दीर्घ addr;
	दीर्घ offset;

	/* Prompt after each proc in bta */
	kdbgetपूर्णांकenv("BTAPROMPT", &btaprompt);

	अगर (म_भेद(argv[0], "bta") == 0) अणु
		काष्ठा task_काष्ठा *g, *p;
		अचिन्हित दीर्घ cpu;
		अचिन्हित दीर्घ mask = kdb_task_state_string(argc ? argv[1] :
							   शून्य);
		अगर (argc == 0)
			kdb_ps_suppressed();
		/* Run the active tasks first */
		क्रम_each_online_cpu(cpu) अणु
			p = kdb_curr_task(cpu);
			अगर (kdb_bt1(p, mask, btaprompt))
				वापस 0;
		पूर्ण
		/* Now the inactive tasks */
		क्रम_each_process_thपढ़ो(g, p) अणु
			अगर (KDB_FLAG(CMD_INTERRUPT))
				वापस 0;
			अगर (task_curr(p))
				जारी;
			अगर (kdb_bt1(p, mask, btaprompt))
				वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेद(argv[0], "btp") == 0) अणु
		काष्ठा task_काष्ठा *p;
		अचिन्हित दीर्घ pid;
		अगर (argc != 1)
			वापस KDB_ARGCOUNT;
		diag = kdbgetularg((अक्षर *)argv[1], &pid);
		अगर (diag)
			वापस diag;
		p = find_task_by_pid_ns(pid, &init_pid_ns);
		अगर (p)
			वापस kdb_bt1(p, ~0UL, false);
		kdb_म_लिखो("No process with pid == %ld found\n", pid);
		वापस 0;
	पूर्ण अन्यथा अगर (म_भेद(argv[0], "btt") == 0) अणु
		अगर (argc != 1)
			वापस KDB_ARGCOUNT;
		diag = kdbgetularg((अक्षर *)argv[1], &addr);
		अगर (diag)
			वापस diag;
		वापस kdb_bt1((काष्ठा task_काष्ठा *)addr, ~0UL, false);
	पूर्ण अन्यथा अगर (म_भेद(argv[0], "btc") == 0) अणु
		अचिन्हित दीर्घ cpu = ~0;
		अगर (argc > 1)
			वापस KDB_ARGCOUNT;
		अगर (argc == 1) अणु
			diag = kdbgetularg((अक्षर *)argv[1], &cpu);
			अगर (diag)
				वापस diag;
		पूर्ण
		अगर (cpu != ~0) अणु
			kdb_bt_cpu(cpu);
		पूर्ण अन्यथा अणु
			/*
			 * Recursive use of kdb_parse, करो not use argv after
			 * this poपूर्णांक.
			 */
			argv = शून्य;
			kdb_म_लिखो("btc: cpu status: ");
			kdb_parse("cpu\n");
			क्रम_each_online_cpu(cpu) अणु
				kdb_bt_cpu(cpu);
				touch_nmi_watchकरोg();
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (argc) अणु
			nextarg = 1;
			diag = kdbgetaddrarg(argc, argv, &nextarg, &addr,
					     &offset, शून्य);
			अगर (diag)
				वापस diag;
			kdb_show_stack(kdb_current_task, (व्योम *)addr);
			वापस 0;
		पूर्ण अन्यथा अणु
			वापस kdb_bt1(kdb_current_task, ~0UL, false);
		पूर्ण
	पूर्ण

	/* NOTREACHED */
	वापस 0;
पूर्ण
