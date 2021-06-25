<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kgdbts is a test suite क्रम kgdb क्रम the sole purpose of validating
 * that key pieces of the kgdb पूर्णांकernals are working properly such as
 * HW/SW अवरोधpoपूर्णांकs, single stepping, and NMI.
 *
 * Created by: Jason Wessel <jason.wessel@windriver.com>
 *
 * Copyright (c) 2008 Wind River Systems, Inc.
 */
/* Inक्रमmation about the kgdb test suite.
 * -------------------------------------
 *
 * The kgdb test suite is deचिन्हित as a KGDB I/O module which
 * simulates the communications that a debugger would have with kgdb.
 * The tests are broken up in to a line by line and referenced here as
 * a "get" which is kgdb requesting input and "put" which is kgdb
 * sending a response.
 *
 * The kgdb suite can be invoked from the kernel command line
 * arguments प्रणाली or executed dynamically at run समय.  The test
 * suite uses the variable "kgdbts" to obtain the inक्रमmation about
 * which tests to run and to configure the verbosity level.  The
 * following are the various अक्षरacters you can use with the kgdbts=
 * line:
 *
 * When using the "kgdbts=" you only choose one of the following core
 * test types:
 * A = Run all the core tests silently
 * V1 = Run all the core tests with minimal output
 * V2 = Run all the core tests in debug mode
 *
 * You can also specअगरy optional tests:
 * N## = Go to sleep with पूर्णांकerrupts of क्रम ## seconds
 *       to test the HW NMI watchकरोg
 * F## = Break at kernel_clone क्रम ## iterations
 * S## = Break at sys_खोलो क्रम ## iterations
 * I## = Run the single step test ## iterations
 *
 * NOTE: that the kernel_clone and sys_खोलो tests are mutually exclusive.
 *
 * To invoke the kgdb test suite from boot you use a kernel start
 * argument as follows:
 * 	kgdbts=V1 kgdbरुको
 * Or अगर you wanted to perक्रमm the NMI test क्रम 6 seconds and kernel_clone
 * test क्रम 100 विभाजनs, you could use:
 * 	kgdbts=V1N6F100 kgdbरुको
 *
 * The test suite can also be invoked at run समय with:
 *	echo kgdbts=V1N6F100 > /sys/module/kgdbts/parameters/kgdbts
 * Or as another example:
 *	echo kgdbts=V2 > /sys/module/kgdbts/parameters/kgdbts
 *
 * When developing a new kgdb arch specअगरic implementation or
 * using these tests क्रम the purpose of regression testing,
 * several invocations are required.
 *
 * 1) Boot with the test suite enabled by using the kernel arguments
 *       "kgdbts=V1F100 kgdbwait"
 *    ## If kgdb arch specअगरic implementation has NMI use
 *       "kgdbts=V1N6F100
 *
 * 2) After the प्रणाली boot run the basic test.
 * echo kgdbts=V1 > /sys/module/kgdbts/parameters/kgdbts
 *
 * 3) Run the concurrency tests.  It is best to use n+1
 *    जबतक loops where n is the number of cpus you have
 *    in your प्रणाली.  The example below uses only two
 *    loops.
 *
 * ## This tests अवरोध poपूर्णांकs on sys_खोलो
 * जबतक [ 1 ] ; करो find / > /dev/null 2>&1 ; करोne &
 * जबतक [ 1 ] ; करो find / > /dev/null 2>&1 ; करोne &
 * echo kgdbts=V1S10000 > /sys/module/kgdbts/parameters/kgdbts
 * fg # and hit control-c
 * fg # and hit control-c
 * ## This tests अवरोध poपूर्णांकs on kernel_clone
 * जबतक [ 1 ] ; करो date > /dev/null ; करोne &
 * जबतक [ 1 ] ; करो date > /dev/null ; करोne &
 * echo kgdbts=V1F1000 > /sys/module/kgdbts/parameters/kgdbts
 * fg # and hit control-c
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/nmi.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/kallsyms.h>

#समावेश <यंत्र/sections.h>

#घोषणा v1prपूर्णांकk(a...) करो अणु		\
	अगर (verbose)			\
		prपूर्णांकk(KERN_INFO a);	\
पूर्ण जबतक (0)
#घोषणा v2prपूर्णांकk(a...) करो अणु		\
	अगर (verbose > 1) अणु		\
		prपूर्णांकk(KERN_INFO a);	\
	पूर्ण				\
	touch_nmi_watchकरोg();		\
पूर्ण जबतक (0)
#घोषणा eprपूर्णांकk(a...) करो अणु		\
	prपूर्णांकk(KERN_ERR a);		\
	WARN_ON(1);			\
पूर्ण जबतक (0)
#घोषणा MAX_CONFIG_LEN		40

अटल काष्ठा kgdb_io kgdbts_io_ops;
अटल अक्षर get_buf[BUFMAX];
अटल पूर्णांक get_buf_cnt;
अटल अक्षर put_buf[BUFMAX];
अटल पूर्णांक put_buf_cnt;
अटल अक्षर scratch_buf[BUFMAX];
अटल पूर्णांक verbose;
अटल पूर्णांक repeat_test;
अटल पूर्णांक test_complete;
अटल पूर्णांक send_ack;
अटल पूर्णांक final_ack;
अटल पूर्णांक क्रमce_hwbrks;
अटल पूर्णांक hwअवरोधs_ok;
अटल पूर्णांक hw_अवरोध_val;
अटल पूर्णांक hw_अवरोध_val2;
अटल पूर्णांक cont_instead_of_sstep;
अटल अचिन्हित दीर्घ cont_thपढ़ो_id;
अटल अचिन्हित दीर्घ sstep_thपढ़ो_id;
#अगर defined(CONFIG_ARM) || defined(CONFIG_MIPS) || defined(CONFIG_SPARC)
अटल पूर्णांक arch_needs_sstep_emulation = 1;
#अन्यथा
अटल पूर्णांक arch_needs_sstep_emulation;
#पूर्ण_अगर
अटल अचिन्हित दीर्घ cont_addr;
अटल अचिन्हित दीर्घ sstep_addr;
अटल पूर्णांक restart_from_top_after_ग_लिखो;
अटल पूर्णांक sstep_state;

/* Storage क्रम the रेजिस्टरs, in GDB क्रमmat. */
अटल अचिन्हित दीर्घ kgdbts_gdb_regs[(NUMREGBYTES +
					माप(अचिन्हित दीर्घ) - 1) /
					माप(अचिन्हित दीर्घ)];
अटल काष्ठा pt_regs kgdbts_regs;

/* -1 = init not run yet, 0 = unconfigured, 1 = configured. */
अटल पूर्णांक configured		= -1;

#अगर_घोषित CONFIG_KGDB_TESTS_BOOT_STRING
अटल अक्षर config[MAX_CONFIG_LEN] = CONFIG_KGDB_TESTS_BOOT_STRING;
#अन्यथा
अटल अक्षर config[MAX_CONFIG_LEN];
#पूर्ण_अगर
अटल काष्ठा kparam_string kps = अणु
	.string			= config,
	.maxlen			= MAX_CONFIG_LEN,
पूर्ण;

अटल व्योम fill_get_buf(अक्षर *buf);

काष्ठा test_काष्ठा अणु
	अक्षर *get;
	अक्षर *put;
	व्योम (*get_handler)(अक्षर *);
	पूर्णांक (*put_handler)(अक्षर *, अक्षर *);
पूर्ण;

काष्ठा test_state अणु
	अक्षर *name;
	काष्ठा test_काष्ठा *tst;
	पूर्णांक idx;
	पूर्णांक (*run_test) (पूर्णांक, पूर्णांक);
	पूर्णांक (*validate_put) (अक्षर *);
पूर्ण;

अटल काष्ठा test_state ts;

अटल पूर्णांक kgdbts_unreg_thपढ़ो(व्योम *ptr)
अणु
	/* Wait until the tests are complete and then ungresiter the I/O
	 * driver.
	 */
	जबतक (!final_ack)
		msleep_पूर्णांकerruptible(1500);
	/* Pause क्रम any other thपढ़ोs to निकास after final ack. */
	msleep_पूर्णांकerruptible(1000);
	अगर (configured)
		kgdb_unरेजिस्टर_io_module(&kgdbts_io_ops);
	configured = 0;

	वापस 0;
पूर्ण

/* This is noअंतरभूत such that it can be used क्रम a single location to
 * place a अवरोधpoपूर्णांक
 */
अटल noअंतरभूत व्योम kgdbts_अवरोध_test(व्योम)
अणु
	v2prपूर्णांकk("kgdbts: breakpoint complete\n");
पूर्ण

/*
 * This is a cached wrapper क्रम kallsyms_lookup_name().
 *
 * The cache is a big win क्रम several tests. For example it more the द्विगुनs
 * the cycles per second during the sys_खोलो test. This is not theoretic,
 * the perक्रमmance improvement shows up at human scale, especially when
 * testing using emulators.
 *
 * Obviously neither re-entrant nor thपढ़ो-safe but that is OK since it
 * can only be called from the debug trap (and thereक्रमe all other CPUs
 * are halted).
 */
अटल अचिन्हित दीर्घ lookup_addr(अक्षर *arg)
अणु
	अटल अक्षर cached_arg[KSYM_NAME_LEN];
	अटल अचिन्हित दीर्घ cached_addr;

	अगर (म_भेद(arg, cached_arg)) अणु
		strscpy(cached_arg, arg, KSYM_NAME_LEN);
		cached_addr = kallsyms_lookup_name(arg);
	पूर्ण

	वापस (अचिन्हित दीर्घ)dereference_function_descriptor(
			(व्योम *)cached_addr);
पूर्ण

अटल व्योम अवरोध_helper(अक्षर *bp_type, अक्षर *arg, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ addr;

	अगर (arg)
		addr = lookup_addr(arg);
	अन्यथा
		addr = vaddr;

	प्र_लिखो(scratch_buf, "%s,%lx,%i", bp_type, addr,
		BREAK_INSTR_SIZE);
	fill_get_buf(scratch_buf);
पूर्ण

अटल व्योम sw_अवरोध(अक्षर *arg)
अणु
	अवरोध_helper(क्रमce_hwbrks ? "Z1" : "Z0", arg, 0);
पूर्ण

अटल व्योम sw_rem_अवरोध(अक्षर *arg)
अणु
	अवरोध_helper(क्रमce_hwbrks ? "z1" : "z0", arg, 0);
पूर्ण

अटल व्योम hw_अवरोध(अक्षर *arg)
अणु
	अवरोध_helper("Z1", arg, 0);
पूर्ण

अटल व्योम hw_rem_अवरोध(अक्षर *arg)
अणु
	अवरोध_helper("z1", arg, 0);
पूर्ण

अटल व्योम hw_ग_लिखो_अवरोध(अक्षर *arg)
अणु
	अवरोध_helper("Z2", arg, 0);
पूर्ण

अटल व्योम hw_rem_ग_लिखो_अवरोध(अक्षर *arg)
अणु
	अवरोध_helper("z2", arg, 0);
पूर्ण

अटल व्योम hw_access_अवरोध(अक्षर *arg)
अणु
	अवरोध_helper("Z4", arg, 0);
पूर्ण

अटल व्योम hw_rem_access_अवरोध(अक्षर *arg)
अणु
	अवरोध_helper("z4", arg, 0);
पूर्ण

अटल व्योम hw_अवरोध_val_access(व्योम)
अणु
	hw_अवरोध_val2 = hw_अवरोध_val;
पूर्ण

अटल व्योम hw_अवरोध_val_ग_लिखो(व्योम)
अणु
	hw_अवरोध_val++;
पूर्ण

अटल पूर्णांक get_thपढ़ो_id_जारी(अक्षर *put_str, अक्षर *arg)
अणु
	अक्षर *ptr = &put_str[11];

	अगर (put_str[1] != 'T' || put_str[2] != '0')
		वापस 1;
	kgdb_hex2दीर्घ(&ptr, &cont_thपढ़ो_id);
	वापस 0;
पूर्ण

अटल पूर्णांक check_and_शुरुआत_pc(अक्षर *put_str, अक्षर *arg)
अणु
	अचिन्हित दीर्घ addr = lookup_addr(arg);
	अचिन्हित दीर्घ ip;
	पूर्णांक offset = 0;

	kgdb_hex2mem(&put_str[1], (अक्षर *)kgdbts_gdb_regs,
		 NUMREGBYTES);
	gdb_regs_to_pt_regs(kgdbts_gdb_regs, &kgdbts_regs);
	ip = inकाष्ठाion_poपूर्णांकer(&kgdbts_regs);
	v2prपूर्णांकk("Stopped at IP: %lx\n", ip);
#अगर_घोषित GDB_ADJUSTS_BREAK_OFFSET
	/* On some arches, a अवरोधpoपूर्णांक stop requires it to be decremented */
	अगर (addr + BREAK_INSTR_SIZE == ip)
		offset = -BREAK_INSTR_SIZE;
#पूर्ण_अगर

	अगर (arch_needs_sstep_emulation && sstep_addr &&
	    ip + offset == sstep_addr &&
	    ((!म_भेद(arg, "do_sys_openat2") || !म_भेद(arg, "kernel_clone")))) अणु
		/* This is special हाल क्रम emulated single step */
		v2prपूर्णांकk("Emul: rewind hit single step bp\n");
		restart_from_top_after_ग_लिखो = 1;
	पूर्ण अन्यथा अगर (म_भेद(arg, "silent") && ip + offset != addr) अणु
		eprपूर्णांकk("kgdbts: BP mismatch %lx expected %lx\n",
			   ip + offset, addr);
		वापस 1;
	पूर्ण
	/* Readjust the inकाष्ठाion poपूर्णांकer अगर needed */
	ip += offset;
	cont_addr = ip;
#अगर_घोषित GDB_ADJUSTS_BREAK_OFFSET
	inकाष्ठाion_poपूर्णांकer_set(&kgdbts_regs, ip);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक check_single_step(अक्षर *put_str, अक्षर *arg)
अणु
	अचिन्हित दीर्घ addr = lookup_addr(arg);
	अटल पूर्णांक matched_id;

	/*
	 * From an arch indepent poपूर्णांक of view the inकाष्ठाion poपूर्णांकer
	 * should be on a dअगरferent inकाष्ठाion
	 */
	kgdb_hex2mem(&put_str[1], (अक्षर *)kgdbts_gdb_regs,
		 NUMREGBYTES);
	gdb_regs_to_pt_regs(kgdbts_gdb_regs, &kgdbts_regs);
	v2prपूर्णांकk("Singlestep stopped at IP: %lx\n",
		   inकाष्ठाion_poपूर्णांकer(&kgdbts_regs));

	अगर (sstep_thपढ़ो_id != cont_thपढ़ो_id) अणु
		/*
		 * Ensure we stopped in the same thपढ़ो id as beक्रमe, अन्यथा the
		 * debugger should जारी until the original thपढ़ो that was
		 * single stepped is scheduled again, emulating gdb's behavior.
		 */
		v2prपूर्णांकk("ThrID does not match: %lx\n", cont_thपढ़ो_id);
		अगर (arch_needs_sstep_emulation) अणु
			अगर (matched_id &&
			    inकाष्ठाion_poपूर्णांकer(&kgdbts_regs) != addr)
				जाओ जारी_test;
			matched_id++;
			ts.idx -= 2;
			sstep_state = 0;
			वापस 0;
		पूर्ण
		cont_instead_of_sstep = 1;
		ts.idx -= 4;
		वापस 0;
	पूर्ण
जारी_test:
	matched_id = 0;
	अगर (inकाष्ठाion_poपूर्णांकer(&kgdbts_regs) == addr) अणु
		eprपूर्णांकk("kgdbts: SingleStep failed at %lx\n",
			   inकाष्ठाion_poपूर्णांकer(&kgdbts_regs));
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ग_लिखो_regs(अक्षर *arg)
अणु
	स_रखो(scratch_buf, 0, माप(scratch_buf));
	scratch_buf[0] = 'G';
	pt_regs_to_gdb_regs(kgdbts_gdb_regs, &kgdbts_regs);
	kgdb_mem2hex((अक्षर *)kgdbts_gdb_regs, &scratch_buf[1], NUMREGBYTES);
	fill_get_buf(scratch_buf);
पूर्ण

अटल व्योम skip_back_repeat_test(अक्षर *arg)
अणु
	पूर्णांक go_back = simple_म_से_दीर्घ(arg, शून्य, 10);

	repeat_test--;
	अगर (repeat_test <= 0) अणु
		ts.idx++;
	पूर्ण अन्यथा अणु
		अगर (repeat_test % 100 == 0)
			v1prपूर्णांकk("kgdbts:RUN ... %d remaining\n", repeat_test);

		ts.idx -= go_back;
	पूर्ण
	fill_get_buf(ts.tst[ts.idx].get);
पूर्ण

अटल पूर्णांक got_अवरोध(अक्षर *put_str, अक्षर *arg)
अणु
	test_complete = 1;
	अगर (!म_भेदन(put_str+1, arg, 2)) अणु
		अगर (!म_भेदन(arg, "T0", 2))
			test_complete = 2;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम get_cont_catch(अक्षर *arg)
अणु
	/* Always send detach because the test is completed at this poपूर्णांक */
	fill_get_buf("D");
पूर्ण

अटल पूर्णांक put_cont_catch(अक्षर *put_str, अक्षर *arg)
अणु
	/* This is at the end of the test and we catch any and all input */
	v2prपूर्णांकk("kgdbts: cleanup task: %lx\n", sstep_thपढ़ो_id);
	ts.idx--;
	वापस 0;
पूर्ण

अटल पूर्णांक emul_reset(अक्षर *put_str, अक्षर *arg)
अणु
	अगर (म_भेदन(put_str, "$OK", 3))
		वापस 1;
	अगर (restart_from_top_after_ग_लिखो) अणु
		restart_from_top_after_ग_लिखो = 0;
		ts.idx = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम emul_sstep_get(अक्षर *arg)
अणु
	अगर (!arch_needs_sstep_emulation) अणु
		अगर (cont_instead_of_sstep) अणु
			cont_instead_of_sstep = 0;
			fill_get_buf("c");
		पूर्ण अन्यथा अणु
			fill_get_buf(arg);
		पूर्ण
		वापस;
	पूर्ण
	चयन (sstep_state) अणु
	हाल 0:
		v2prपूर्णांकk("Emulate single step\n");
		/* Start by looking at the current PC */
		fill_get_buf("g");
		अवरोध;
	हाल 1:
		/* set अवरोधpoपूर्णांक */
		अवरोध_helper("Z0", शून्य, sstep_addr);
		अवरोध;
	हाल 2:
		/* Continue */
		fill_get_buf("c");
		अवरोध;
	हाल 3:
		/* Clear अवरोधpoपूर्णांक */
		अवरोध_helper("z0", शून्य, sstep_addr);
		अवरोध;
	शेष:
		eprपूर्णांकk("kgdbts: ERROR failed sstep get emulation\n");
	पूर्ण
	sstep_state++;
पूर्ण

अटल पूर्णांक emul_sstep_put(अक्षर *put_str, अक्षर *arg)
अणु
	अगर (!arch_needs_sstep_emulation) अणु
		अक्षर *ptr = &put_str[11];
		अगर (put_str[1] != 'T' || put_str[2] != '0')
			वापस 1;
		kgdb_hex2दीर्घ(&ptr, &sstep_thपढ़ो_id);
		वापस 0;
	पूर्ण
	चयन (sstep_state) अणु
	हाल 1:
		/* validate the "g" packet to get the IP */
		kgdb_hex2mem(&put_str[1], (अक्षर *)kgdbts_gdb_regs,
			 NUMREGBYTES);
		gdb_regs_to_pt_regs(kgdbts_gdb_regs, &kgdbts_regs);
		v2prपूर्णांकk("Stopped at IP: %lx\n",
			 inकाष्ठाion_poपूर्णांकer(&kgdbts_regs));
		/* Want to stop at IP + अवरोध inकाष्ठाion size by शेष */
		sstep_addr = cont_addr + BREAK_INSTR_SIZE;
		अवरोध;
	हाल 2:
		अगर (म_भेदन(put_str, "$OK", 3)) अणु
			eprपूर्णांकk("kgdbts: failed sstep break set\n");
			वापस 1;
		पूर्ण
		अवरोध;
	हाल 3:
		अगर (म_भेदन(put_str, "$T0", 3)) अणु
			eprपूर्णांकk("kgdbts: failed continue sstep\n");
			वापस 1;
		पूर्ण अन्यथा अणु
			अक्षर *ptr = &put_str[11];
			kgdb_hex2दीर्घ(&ptr, &sstep_thपढ़ो_id);
		पूर्ण
		अवरोध;
	हाल 4:
		अगर (म_भेदन(put_str, "$OK", 3)) अणु
			eprपूर्णांकk("kgdbts: failed sstep break unset\n");
			वापस 1;
		पूर्ण
		/* Single step is complete so जारी on! */
		sstep_state = 0;
		वापस 0;
	शेष:
		eprपूर्णांकk("kgdbts: ERROR failed sstep put emulation\n");
	पूर्ण

	/* Continue on the same test line until emulation is complete */
	ts.idx--;
	वापस 0;
पूर्ण

अटल पूर्णांक final_ack_set(अक्षर *put_str, अक्षर *arg)
अणु
	अगर (म_भेदन(put_str+1, arg, 2))
		वापस 1;
	final_ack = 1;
	वापस 0;
पूर्ण
/*
 * Test to plant a अवरोधpoपूर्णांक and detach, which should clear out the
 * अवरोधpoपूर्णांक and restore the original inकाष्ठाion.
 */
अटल काष्ठा test_काष्ठा plant_and_detach_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "kgdbts_break_test", "OK", sw_अवरोध, पूर्ण, /* set sw अवरोधpoपूर्णांक */
	अणु "D", "OK" पूर्ण, /* Detach */
	अणु "", "" पूर्ण,
पूर्ण;

/*
 * Simple test to ग_लिखो in a software अवरोधpoपूर्णांक, check क्रम the
 * correct stop location and detach.
 */
अटल काष्ठा test_काष्ठा sw_अवरोधpoपूर्णांक_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "kgdbts_break_test", "OK", sw_अवरोध, पूर्ण, /* set sw अवरोधpoपूर्णांक */
	अणु "c", "T0*", पूर्ण, /* Continue */
	अणु "g", "kgdbts_break_test", शून्य, check_and_शुरुआत_pc पूर्ण,
	अणु "write", "OK", ग_लिखो_regs पूर्ण,
	अणु "kgdbts_break_test", "OK", sw_rem_अवरोध पूर्ण, /*हटाओ अवरोधpoपूर्णांक */
	अणु "D", "OK" पूर्ण, /* Detach */
	अणु "D", "OK", शून्य,  got_अवरोध पूर्ण, /* On success we made it here */
	अणु "", "" पूर्ण,
पूर्ण;

/*
 * Test a known bad memory पढ़ो location to test the fault handler and
 * पढ़ो bytes 1-8 at the bad address
 */
अटल काष्ठा test_काष्ठा bad_पढ़ो_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "m0,1", "E*" पूर्ण, /* पढ़ो 1 byte at address 1 */
	अणु "m0,2", "E*" पूर्ण, /* पढ़ो 1 byte at address 2 */
	अणु "m0,3", "E*" पूर्ण, /* पढ़ो 1 byte at address 3 */
	अणु "m0,4", "E*" पूर्ण, /* पढ़ो 1 byte at address 4 */
	अणु "m0,5", "E*" पूर्ण, /* पढ़ो 1 byte at address 5 */
	अणु "m0,6", "E*" पूर्ण, /* पढ़ो 1 byte at address 6 */
	अणु "m0,7", "E*" पूर्ण, /* पढ़ो 1 byte at address 7 */
	अणु "m0,8", "E*" पूर्ण, /* पढ़ो 1 byte at address 8 */
	अणु "D", "OK" पूर्ण, /* Detach which हटाओs all अवरोधpoपूर्णांकs and जारीs */
	अणु "", "" पूर्ण,
पूर्ण;

/*
 * Test क्रम hitting a अवरोधpoपूर्णांक, हटाओ it, single step, plant it
 * again and detach.
 */
अटल काष्ठा test_काष्ठा singlestep_अवरोध_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "kgdbts_break_test", "OK", sw_अवरोध, पूर्ण, /* set sw अवरोधpoपूर्णांक */
	अणु "c", "T0*", शून्य, get_thपढ़ो_id_जारी पूर्ण, /* Continue */
	अणु "kgdbts_break_test", "OK", sw_rem_अवरोध पूर्ण, /*हटाओ अवरोधpoपूर्णांक */
	अणु "g", "kgdbts_break_test", शून्य, check_and_शुरुआत_pc पूर्ण,
	अणु "write", "OK", ग_लिखो_regs पूर्ण, /* Write रेजिस्टरs */
	अणु "s", "T0*", emul_sstep_get, emul_sstep_put पूर्ण, /* Single step */
	अणु "g", "kgdbts_break_test", शून्य, check_single_step पूर्ण,
	अणु "kgdbts_break_test", "OK", sw_अवरोध, पूर्ण, /* set sw अवरोधpoपूर्णांक */
	अणु "c", "T0*", पूर्ण, /* Continue */
	अणु "g", "kgdbts_break_test", शून्य, check_and_शुरुआत_pc पूर्ण,
	अणु "write", "OK", ग_लिखो_regs पूर्ण, /* Write रेजिस्टरs */
	अणु "D", "OK" पूर्ण, /* Remove all अवरोधpoपूर्णांकs and जारीs */
	अणु "", "" पूर्ण,
पूर्ण;

/*
 * Test क्रम hitting a अवरोधpoपूर्णांक at kernel_clone क्रम what ever the number
 * of iterations required by the variable repeat_test.
 */
अटल काष्ठा test_काष्ठा करो_kernel_clone_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "kernel_clone", "OK", sw_अवरोध, पूर्ण, /* set sw अवरोधpoपूर्णांक */
	अणु "c", "T0*", शून्य, get_thपढ़ो_id_जारी पूर्ण, /* Continue */
	अणु "kernel_clone", "OK", sw_rem_अवरोध पूर्ण, /*हटाओ अवरोधpoपूर्णांक */
	अणु "g", "kernel_clone", शून्य, check_and_शुरुआत_pc पूर्ण, /* check location */
	अणु "write", "OK", ग_लिखो_regs, emul_reset पूर्ण, /* Write रेजिस्टरs */
	अणु "s", "T0*", emul_sstep_get, emul_sstep_put पूर्ण, /* Single step */
	अणु "g", "kernel_clone", शून्य, check_single_step पूर्ण,
	अणु "kernel_clone", "OK", sw_अवरोध, पूर्ण, /* set sw अवरोधpoपूर्णांक */
	अणु "7", "T0*", skip_back_repeat_test पूर्ण, /* Loop based on repeat_test */
	अणु "D", "OK", शून्य, final_ack_set पूर्ण, /* detach and unरेजिस्टर I/O */
	अणु "", "", get_cont_catch, put_cont_catch पूर्ण,
पूर्ण;

/* Test क्रम hitting a अवरोधpoपूर्णांक at sys_खोलो क्रम what ever the number
 * of iterations required by the variable repeat_test.
 */
अटल काष्ठा test_काष्ठा sys_खोलो_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "do_sys_openat2", "OK", sw_अवरोध, पूर्ण, /* set sw अवरोधpoपूर्णांक */
	अणु "c", "T0*", शून्य, get_thपढ़ो_id_जारी पूर्ण, /* Continue */
	अणु "do_sys_openat2", "OK", sw_rem_अवरोध पूर्ण, /*हटाओ अवरोधpoपूर्णांक */
	अणु "g", "do_sys_openat2", शून्य, check_and_शुरुआत_pc पूर्ण, /* check location */
	अणु "write", "OK", ग_लिखो_regs, emul_reset पूर्ण, /* Write रेजिस्टरs */
	अणु "s", "T0*", emul_sstep_get, emul_sstep_put पूर्ण, /* Single step */
	अणु "g", "do_sys_openat2", शून्य, check_single_step पूर्ण,
	अणु "do_sys_openat2", "OK", sw_अवरोध, पूर्ण, /* set sw अवरोधpoपूर्णांक */
	अणु "7", "T0*", skip_back_repeat_test पूर्ण, /* Loop based on repeat_test */
	अणु "D", "OK", शून्य, final_ack_set पूर्ण, /* detach and unरेजिस्टर I/O */
	अणु "", "", get_cont_catch, put_cont_catch पूर्ण,
पूर्ण;

/*
 * Test क्रम hitting a simple hw अवरोधpoपूर्णांक
 */
अटल काष्ठा test_काष्ठा hw_अवरोधpoपूर्णांक_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "kgdbts_break_test", "OK", hw_अवरोध, पूर्ण, /* set hw अवरोधpoपूर्णांक */
	अणु "c", "T0*", पूर्ण, /* Continue */
	अणु "g", "kgdbts_break_test", शून्य, check_and_शुरुआत_pc पूर्ण,
	अणु "write", "OK", ग_लिखो_regs पूर्ण,
	अणु "kgdbts_break_test", "OK", hw_rem_अवरोध पूर्ण, /*हटाओ अवरोधpoपूर्णांक */
	अणु "D", "OK" पूर्ण, /* Detach */
	अणु "D", "OK", शून्य,  got_अवरोध पूर्ण, /* On success we made it here */
	अणु "", "" पूर्ण,
पूर्ण;

/*
 * Test क्रम hitting a hw ग_लिखो अवरोधpoपूर्णांक
 */
अटल काष्ठा test_काष्ठा hw_ग_लिखो_अवरोध_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "hw_break_val", "OK", hw_ग_लिखो_अवरोध, पूर्ण, /* set hw अवरोधpoपूर्णांक */
	अणु "c", "T0*", शून्य, got_अवरोध पूर्ण, /* Continue */
	अणु "g", "silent", शून्य, check_and_शुरुआत_pc पूर्ण,
	अणु "write", "OK", ग_लिखो_regs पूर्ण,
	अणु "hw_break_val", "OK", hw_rem_ग_लिखो_अवरोध पूर्ण, /*हटाओ अवरोधpoपूर्णांक */
	अणु "D", "OK" पूर्ण, /* Detach */
	अणु "D", "OK", शून्य,  got_अवरोध पूर्ण, /* On success we made it here */
	अणु "", "" पूर्ण,
पूर्ण;

/*
 * Test क्रम hitting a hw access अवरोधpoपूर्णांक
 */
अटल काष्ठा test_काष्ठा hw_access_अवरोध_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "hw_break_val", "OK", hw_access_अवरोध, पूर्ण, /* set hw अवरोधpoपूर्णांक */
	अणु "c", "T0*", शून्य, got_अवरोध पूर्ण, /* Continue */
	अणु "g", "silent", शून्य, check_and_शुरुआत_pc पूर्ण,
	अणु "write", "OK", ग_लिखो_regs पूर्ण,
	अणु "hw_break_val", "OK", hw_rem_access_अवरोध पूर्ण, /*हटाओ अवरोधpoपूर्णांक */
	अणु "D", "OK" पूर्ण, /* Detach */
	अणु "D", "OK", शून्य,  got_अवरोध पूर्ण, /* On success we made it here */
	अणु "", "" पूर्ण,
पूर्ण;

/*
 * Test क्रम hitting a hw access अवरोधpoपूर्णांक
 */
अटल काष्ठा test_काष्ठा nmi_sleep_test[] = अणु
	अणु "?", "S0*" पूर्ण, /* Clear अवरोध poपूर्णांकs */
	अणु "c", "T0*", शून्य, got_अवरोध पूर्ण, /* Continue */
	अणु "D", "OK" पूर्ण, /* Detach */
	अणु "D", "OK", शून्य,  got_अवरोध पूर्ण, /* On success we made it here */
	अणु "", "" पूर्ण,
पूर्ण;

अटल व्योम fill_get_buf(अक्षर *buf)
अणु
	अचिन्हित अक्षर checksum = 0;
	पूर्णांक count = 0;
	अक्षर ch;

	म_नकल(get_buf, "$");
	म_जोड़ो(get_buf, buf);
	जबतक ((ch = buf[count])) अणु
		checksum += ch;
		count++;
	पूर्ण
	म_जोड़ो(get_buf, "#");
	get_buf[count + 2] = hex_asc_hi(checksum);
	get_buf[count + 3] = hex_asc_lo(checksum);
	get_buf[count + 4] = '\0';
	v2prपूर्णांकk("get%i: %s\n", ts.idx, get_buf);
पूर्ण

अटल पूर्णांक validate_simple_test(अक्षर *put_str)
अणु
	अक्षर *chk_str;

	अगर (ts.tst[ts.idx].put_handler)
		वापस ts.tst[ts.idx].put_handler(put_str,
			ts.tst[ts.idx].put);

	chk_str = ts.tst[ts.idx].put;
	अगर (*put_str == '$')
		put_str++;

	जबतक (*chk_str != '\0' && *put_str != '\0') अणु
		/* If someone करोes a * to match the rest of the string, allow
		 * it, or stop अगर the received string is complete.
		 */
		अगर (*put_str == '#' || *chk_str == '*')
			वापस 0;
		अगर (*put_str != *chk_str)
			वापस 1;

		chk_str++;
		put_str++;
	पूर्ण
	अगर (*chk_str == '\0' && (*put_str == '\0' || *put_str == '#'))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक run_simple_test(पूर्णांक is_get_अक्षर, पूर्णांक chr)
अणु
	पूर्णांक ret = 0;
	अगर (is_get_अक्षर) अणु
		/* Send an ACK on the get अगर a prior put completed and set the
		 * send ack variable
		 */
		अगर (send_ack) अणु
			send_ack = 0;
			वापस '+';
		पूर्ण
		/* On the first get अक्षर, fill the transmit buffer and then
		 * take from the get_string.
		 */
		अगर (get_buf_cnt == 0) अणु
			अगर (ts.tst[ts.idx].get_handler)
				ts.tst[ts.idx].get_handler(ts.tst[ts.idx].get);
			अन्यथा
				fill_get_buf(ts.tst[ts.idx].get);
		पूर्ण

		अगर (get_buf[get_buf_cnt] == '\0') अणु
			eprपूर्णांकk("kgdbts: ERROR GET: EOB on '%s' at %i\n",
			   ts.name, ts.idx);
			get_buf_cnt = 0;
			fill_get_buf("D");
		पूर्ण
		ret = get_buf[get_buf_cnt];
		get_buf_cnt++;
		वापस ret;
	पूर्ण

	/* This callback is a put अक्षर which is when kgdb sends data to
	 * this I/O module.
	 */
	अगर (ts.tst[ts.idx].get[0] == '\0' && ts.tst[ts.idx].put[0] == '\0' &&
	    !ts.tst[ts.idx].get_handler) अणु
		eprपूर्णांकk("kgdbts: ERROR: beyond end of test on"
			   " '%s' line %i\n", ts.name, ts.idx);
		वापस 0;
	पूर्ण

	अगर (put_buf_cnt >= BUFMAX) अणु
		eprपूर्णांकk("kgdbts: ERROR: put buffer overflow on"
			   " '%s' line %i\n", ts.name, ts.idx);
		put_buf_cnt = 0;
		वापस 0;
	पूर्ण
	/* Ignore everything until the first valid packet start '$' */
	अगर (put_buf_cnt == 0 && chr != '$')
		वापस 0;

	put_buf[put_buf_cnt] = chr;
	put_buf_cnt++;

	/* End of packet == #XX so look क्रम the '#' */
	अगर (put_buf_cnt > 3 && put_buf[put_buf_cnt - 3] == '#') अणु
		अगर (put_buf_cnt >= BUFMAX) अणु
			eprपूर्णांकk("kgdbts: ERROR: put buffer overflow on"
				" '%s' line %i\n", ts.name, ts.idx);
			put_buf_cnt = 0;
			वापस 0;
		पूर्ण
		put_buf[put_buf_cnt] = '\0';
		v2prपूर्णांकk("put%i: %s\n", ts.idx, put_buf);
		/* Trigger check here */
		अगर (ts.validate_put && ts.validate_put(put_buf)) अणु
			eprपूर्णांकk("kgdbts: ERROR PUT: end of test "
			   "buffer on '%s' line %i expected %s got %s\n",
			   ts.name, ts.idx, ts.tst[ts.idx].put, put_buf);
		पूर्ण
		ts.idx++;
		put_buf_cnt = 0;
		get_buf_cnt = 0;
		send_ack = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम init_simple_test(व्योम)
अणु
	स_रखो(&ts, 0, माप(ts));
	ts.run_test = run_simple_test;
	ts.validate_put = validate_simple_test;
पूर्ण

अटल व्योम run_plant_and_detach_test(पूर्णांक is_early)
अणु
	अक्षर beक्रमe[BREAK_INSTR_SIZE];
	अक्षर after[BREAK_INSTR_SIZE];

	copy_from_kernel_nofault(beक्रमe, (अक्षर *)kgdbts_अवरोध_test,
	  BREAK_INSTR_SIZE);
	init_simple_test();
	ts.tst = plant_and_detach_test;
	ts.name = "plant_and_detach_test";
	/* Activate test with initial अवरोधpoपूर्णांक */
	अगर (!is_early)
		kgdb_अवरोधpoपूर्णांक();
	copy_from_kernel_nofault(after, (अक्षर *)kgdbts_अवरोध_test,
			BREAK_INSTR_SIZE);
	अगर (स_भेद(beक्रमe, after, BREAK_INSTR_SIZE)) अणु
		prपूर्णांकk(KERN_CRIT "kgdbts: ERROR kgdb corrupted memory\n");
		panic("kgdb memory corruption");
	पूर्ण

	/* complete the detach test */
	अगर (!is_early)
		kgdbts_अवरोध_test();
पूर्ण

अटल व्योम run_अवरोधpoपूर्णांक_test(पूर्णांक is_hw_अवरोधpoपूर्णांक)
अणु
	test_complete = 0;
	init_simple_test();
	अगर (is_hw_अवरोधpoपूर्णांक) अणु
		ts.tst = hw_अवरोधpoपूर्णांक_test;
		ts.name = "hw_breakpoint_test";
	पूर्ण अन्यथा अणु
		ts.tst = sw_अवरोधpoपूर्णांक_test;
		ts.name = "sw_breakpoint_test";
	पूर्ण
	/* Activate test with initial अवरोधpoपूर्णांक */
	kgdb_अवरोधpoपूर्णांक();
	/* run code with the अवरोध poपूर्णांक in it */
	kgdbts_अवरोध_test();
	kgdb_अवरोधpoपूर्णांक();

	अगर (test_complete)
		वापस;

	eprपूर्णांकk("kgdbts: ERROR %s test failed\n", ts.name);
	अगर (is_hw_अवरोधpoपूर्णांक)
		hwअवरोधs_ok = 0;
पूर्ण

अटल व्योम run_hw_अवरोध_test(पूर्णांक is_ग_लिखो_test)
अणु
	test_complete = 0;
	init_simple_test();
	अगर (is_ग_लिखो_test) अणु
		ts.tst = hw_ग_लिखो_अवरोध_test;
		ts.name = "hw_write_break_test";
	पूर्ण अन्यथा अणु
		ts.tst = hw_access_अवरोध_test;
		ts.name = "hw_access_break_test";
	पूर्ण
	/* Activate test with initial अवरोधpoपूर्णांक */
	kgdb_अवरोधpoपूर्णांक();
	hw_अवरोध_val_access();
	अगर (is_ग_लिखो_test) अणु
		अगर (test_complete == 2) अणु
			eprपूर्णांकk("kgdbts: ERROR %s broke on access\n",
				ts.name);
			hwअवरोधs_ok = 0;
		पूर्ण
		hw_अवरोध_val_ग_लिखो();
	पूर्ण
	kgdb_अवरोधpoपूर्णांक();

	अगर (test_complete == 1)
		वापस;

	eprपूर्णांकk("kgdbts: ERROR %s test failed\n", ts.name);
	hwअवरोधs_ok = 0;
पूर्ण

अटल व्योम run_nmi_sleep_test(पूर्णांक nmi_sleep)
अणु
	अचिन्हित दीर्घ flags;

	init_simple_test();
	ts.tst = nmi_sleep_test;
	ts.name = "nmi_sleep_test";
	/* Activate test with initial अवरोधpoपूर्णांक */
	kgdb_अवरोधpoपूर्णांक();
	local_irq_save(flags);
	mdelay(nmi_sleep*1000);
	touch_nmi_watchकरोg();
	local_irq_restore(flags);
	अगर (test_complete != 2)
		eprपूर्णांकk("kgdbts: ERROR nmi_test did not hit nmi\n");
	kgdb_अवरोधpoपूर्णांक();
	अगर (test_complete == 1)
		वापस;

	eprपूर्णांकk("kgdbts: ERROR %s test failed\n", ts.name);
पूर्ण

अटल व्योम run_bad_पढ़ो_test(व्योम)
अणु
	init_simple_test();
	ts.tst = bad_पढ़ो_test;
	ts.name = "bad_read_test";
	/* Activate test with initial अवरोधpoपूर्णांक */
	kgdb_अवरोधpoपूर्णांक();
पूर्ण

अटल व्योम run_kernel_clone_test(व्योम)
अणु
	init_simple_test();
	ts.tst = करो_kernel_clone_test;
	ts.name = "do_kernel_clone_test";
	/* Activate test with initial अवरोधpoपूर्णांक */
	kgdb_अवरोधpoपूर्णांक();
पूर्ण

अटल व्योम run_sys_खोलो_test(व्योम)
अणु
	init_simple_test();
	ts.tst = sys_खोलो_test;
	ts.name = "sys_open_test";
	/* Activate test with initial अवरोधpoपूर्णांक */
	kgdb_अवरोधpoपूर्णांक();
पूर्ण

अटल व्योम run_singlestep_अवरोध_test(व्योम)
अणु
	init_simple_test();
	ts.tst = singlestep_अवरोध_test;
	ts.name = "singlestep_breakpoint_test";
	/* Activate test with initial अवरोधpoपूर्णांक */
	kgdb_अवरोधpoपूर्णांक();
	kgdbts_अवरोध_test();
	kgdbts_अवरोध_test();
पूर्ण

अटल व्योम kgdbts_run_tests(व्योम)
अणु
	अक्षर *ptr;
	पूर्णांक clone_test = 0;
	पूर्णांक करो_sys_खोलो_test = 0;
	पूर्णांक sstep_test = 1000;
	पूर्णांक nmi_sleep = 0;
	पूर्णांक i;

	verbose = 0;
	अगर (म_माला(config, "V1"))
		verbose = 1;
	अगर (म_माला(config, "V2"))
		verbose = 2;

	ptr = म_अक्षर(config, 'F');
	अगर (ptr)
		clone_test = simple_म_से_दीर्घ(ptr + 1, शून्य, 10);
	ptr = म_अक्षर(config, 'S');
	अगर (ptr)
		करो_sys_खोलो_test = simple_म_से_दीर्घ(ptr + 1, शून्य, 10);
	ptr = म_अक्षर(config, 'N');
	अगर (ptr)
		nmi_sleep = simple_म_से_दीर्घ(ptr+1, शून्य, 10);
	ptr = म_अक्षर(config, 'I');
	अगर (ptr)
		sstep_test = simple_म_से_दीर्घ(ptr+1, शून्य, 10);

	/* All HW अवरोध poपूर्णांक tests */
	अगर (arch_kgdb_ops.flags & KGDB_HW_BREAKPOINT) अणु
		hwअवरोधs_ok = 1;
		v1prपूर्णांकk("kgdbts:RUN hw breakpoint test\n");
		run_अवरोधpoपूर्णांक_test(1);
		v1prपूर्णांकk("kgdbts:RUN hw write breakpoint test\n");
		run_hw_अवरोध_test(1);
		v1prपूर्णांकk("kgdbts:RUN access write breakpoint test\n");
		run_hw_अवरोध_test(0);
	पूर्ण

	/* required पूर्णांकernal KGDB tests */
	v1prपूर्णांकk("kgdbts:RUN plant and detach test\n");
	run_plant_and_detach_test(0);
	v1prपूर्णांकk("kgdbts:RUN sw breakpoint test\n");
	run_अवरोधpoपूर्णांक_test(0);
	v1prपूर्णांकk("kgdbts:RUN bad memory access test\n");
	run_bad_पढ़ो_test();
	v1prपूर्णांकk("kgdbts:RUN singlestep test %i iterations\n", sstep_test);
	क्रम (i = 0; i < sstep_test; i++) अणु
		run_singlestep_अवरोध_test();
		अगर (i % 100 == 0)
			v1prपूर्णांकk("kgdbts:RUN singlestep [%i/%i]\n",
				 i, sstep_test);
	पूर्ण

	/* ===Optional tests=== */

	अगर (nmi_sleep) अणु
		v1prपूर्णांकk("kgdbts:RUN NMI sleep %i seconds test\n", nmi_sleep);
		run_nmi_sleep_test(nmi_sleep);
	पूर्ण

	/* If the kernel_clone test is run it will be the last test that is
	 * executed because a kernel thपढ़ो will be spawned at the very
	 * end to unरेजिस्टर the debug hooks.
	 */
	अगर (clone_test) अणु
		repeat_test = clone_test;
		prपूर्णांकk(KERN_INFO "kgdbts:RUN kernel_clone for %i breakpoints\n",
			repeat_test);
		kthपढ़ो_run(kgdbts_unreg_thपढ़ो, शून्य, "kgdbts_unreg");
		run_kernel_clone_test();
		वापस;
	पूर्ण

	/* If the sys_खोलो test is run it will be the last test that is
	 * executed because a kernel thपढ़ो will be spawned at the very
	 * end to unरेजिस्टर the debug hooks.
	 */
	अगर (करो_sys_खोलो_test) अणु
		repeat_test = करो_sys_खोलो_test;
		prपूर्णांकk(KERN_INFO "kgdbts:RUN sys_open for %i breakpoints\n",
			repeat_test);
		kthपढ़ो_run(kgdbts_unreg_thपढ़ो, शून्य, "kgdbts_unreg");
		run_sys_खोलो_test();
		वापस;
	पूर्ण
	/* Shutकरोwn and unरेजिस्टर */
	kgdb_unरेजिस्टर_io_module(&kgdbts_io_ops);
	configured = 0;
पूर्ण

अटल पूर्णांक kgdbts_option_setup(अक्षर *opt)
अणु
	अगर (म_माप(opt) >= MAX_CONFIG_LEN) अणु
		prपूर्णांकk(KERN_ERR "kgdbts: config string too long\n");
		वापस -ENOSPC;
	पूर्ण
	म_नकल(config, opt);
	वापस 0;
पूर्ण

__setup("kgdbts=", kgdbts_option_setup);

अटल पूर्णांक configure_kgdbts(व्योम)
अणु
	पूर्णांक err = 0;

	अगर (!म_माप(config) || है_खाली(config[0]))
		जाओ noconfig;

	final_ack = 0;
	run_plant_and_detach_test(1);

	err = kgdb_रेजिस्टर_io_module(&kgdbts_io_ops);
	अगर (err) अणु
		configured = 0;
		वापस err;
	पूर्ण
	configured = 1;
	kgdbts_run_tests();

	वापस err;

noconfig:
	config[0] = 0;
	configured = 0;

	वापस err;
पूर्ण

अटल पूर्णांक __init init_kgdbts(व्योम)
अणु
	/* Alपढ़ोy configured? */
	अगर (configured == 1)
		वापस 0;

	वापस configure_kgdbts();
पूर्ण
device_initcall(init_kgdbts);

अटल पूर्णांक kgdbts_get_अक्षर(व्योम)
अणु
	पूर्णांक val = 0;

	अगर (ts.run_test)
		val = ts.run_test(1, 0);

	वापस val;
पूर्ण

अटल व्योम kgdbts_put_अक्षर(u8 chr)
अणु
	अगर (ts.run_test)
		ts.run_test(0, chr);
पूर्ण

अटल पूर्णांक param_set_kgdbts_var(स्थिर अक्षर *kmessage,
				स्थिर काष्ठा kernel_param *kp)
अणु
	माप_प्रकार len = म_माप(kmessage);

	अगर (len >= MAX_CONFIG_LEN) अणु
		prपूर्णांकk(KERN_ERR "kgdbts: config string too long\n");
		वापस -ENOSPC;
	पूर्ण

	/* Only copy in the string अगर the init function has not run yet */
	अगर (configured < 0) अणु
		म_नकल(config, kmessage);
		वापस 0;
	पूर्ण

	अगर (configured == 1) अणु
		prपूर्णांकk(KERN_ERR "kgdbts: ERROR: Already configured and running.\n");
		वापस -EBUSY;
	पूर्ण

	म_नकल(config, kmessage);
	/* Chop out \न अक्षर as a result of echo */
	अगर (len && config[len - 1] == '\n')
		config[len - 1] = '\0';

	/* Go and configure with the new params. */
	वापस configure_kgdbts();
पूर्ण

अटल व्योम kgdbts_pre_exp_handler(व्योम)
अणु
	/* Increment the module count when the debugger is active */
	अगर (!kgdb_connected)
		try_module_get(THIS_MODULE);
पूर्ण

अटल व्योम kgdbts_post_exp_handler(व्योम)
अणु
	/* decrement the module count when the debugger detaches */
	अगर (!kgdb_connected)
		module_put(THIS_MODULE);
पूर्ण

अटल काष्ठा kgdb_io kgdbts_io_ops = अणु
	.name			= "kgdbts",
	.पढ़ो_अक्षर		= kgdbts_get_अक्षर,
	.ग_लिखो_अक्षर		= kgdbts_put_अक्षर,
	.pre_exception		= kgdbts_pre_exp_handler,
	.post_exception		= kgdbts_post_exp_handler,
पूर्ण;

/*
 * not really modular, but the easiest way to keep compat with existing
 * bootargs behaviour is to जारी using module_param here.
 */
module_param_call(kgdbts, param_set_kgdbts_var, param_get_string, &kps, 0644);
MODULE_PARM_DESC(kgdbts, "<A|V1|V2>[F#|S#][N#]");
