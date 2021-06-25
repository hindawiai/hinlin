<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 David Daney
 */

#समावेश <linux/sched.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/watch.h>

/*
 * Install the watch रेजिस्टरs क्रम the current thपढ़ो.	A maximum of
 * four रेजिस्टरs are installed although the machine may have more.
 */
व्योम mips_install_watch_रेजिस्टरs(काष्ठा task_काष्ठा *t)
अणु
	काष्ठा mips3264_watch_reg_state *watches = &t->thपढ़ो.watch.mips3264;
	अचिन्हित पूर्णांक watchhi = MIPS_WATCHHI_G |		/* Trap all ASIDs */
			       MIPS_WATCHHI_IRW;	/* Clear result bits */

	चयन (current_cpu_data.watch_reg_use_cnt) अणु
	शेष:
		BUG();
	हाल 4:
		ग_लिखो_c0_watchlo3(watches->watchlo[3]);
		ग_लिखो_c0_watchhi3(watchhi | watches->watchhi[3]);
		fallthrough;
	हाल 3:
		ग_लिखो_c0_watchlo2(watches->watchlo[2]);
		ग_लिखो_c0_watchhi2(watchhi | watches->watchhi[2]);
		fallthrough;
	हाल 2:
		ग_लिखो_c0_watchlo1(watches->watchlo[1]);
		ग_लिखो_c0_watchhi1(watchhi | watches->watchhi[1]);
		fallthrough;
	हाल 1:
		ग_लिखो_c0_watchlo0(watches->watchlo[0]);
		ग_लिखो_c0_watchhi0(watchhi | watches->watchhi[0]);
	पूर्ण
पूर्ण

/*
 * Read back the watchhi रेजिस्टरs so the user space debugger has
 * access to the I, R, and W bits.  A maximum of four रेजिस्टरs are
 * पढ़ो although the machine may have more.
 */
व्योम mips_पढ़ो_watch_रेजिस्टरs(व्योम)
अणु
	काष्ठा mips3264_watch_reg_state *watches =
		&current->thपढ़ो.watch.mips3264;
	अचिन्हित पूर्णांक watchhi_mask = MIPS_WATCHHI_MASK | MIPS_WATCHHI_IRW;

	चयन (current_cpu_data.watch_reg_use_cnt) अणु
	शेष:
		BUG();
	हाल 4:
		watches->watchhi[3] = (पढ़ो_c0_watchhi3() & watchhi_mask);
		fallthrough;
	हाल 3:
		watches->watchhi[2] = (पढ़ो_c0_watchhi2() & watchhi_mask);
		fallthrough;
	हाल 2:
		watches->watchhi[1] = (पढ़ो_c0_watchhi1() & watchhi_mask);
		fallthrough;
	हाल 1:
		watches->watchhi[0] = (पढ़ो_c0_watchhi0() & watchhi_mask);
	पूर्ण
	अगर (current_cpu_data.watch_reg_use_cnt == 1 &&
	    (watches->watchhi[0] & MIPS_WATCHHI_IRW) == 0) अणु
		/* Pathological हाल of release 1 architecture that
		 * करोesn't set the condition bits.  We assume that
		 * since we got here, the watch condition was met and
		 * संकेत that the conditions requested in watchlo
		 * were met.  */
		watches->watchhi[0] |= (watches->watchlo[0] & MIPS_WATCHHI_IRW);
	पूर्ण
 पूर्ण

/*
 * Disable all watch रेजिस्टरs.	 Although only four रेजिस्टरs are
 * installed, all are cleared to eliminate the possibility of endless
 * looping in the watch handler.
 */
व्योम mips_clear_watch_रेजिस्टरs(व्योम)
अणु
	चयन (current_cpu_data.watch_reg_count) अणु
	शेष:
		BUG();
	हाल 8:
		ग_लिखो_c0_watchlo7(0);
		fallthrough;
	हाल 7:
		ग_लिखो_c0_watchlo6(0);
		fallthrough;
	हाल 6:
		ग_लिखो_c0_watchlo5(0);
		fallthrough;
	हाल 5:
		ग_लिखो_c0_watchlo4(0);
		fallthrough;
	हाल 4:
		ग_लिखो_c0_watchlo3(0);
		fallthrough;
	हाल 3:
		ग_लिखो_c0_watchlo2(0);
		fallthrough;
	हाल 2:
		ग_लिखो_c0_watchlo1(0);
		fallthrough;
	हाल 1:
		ग_लिखो_c0_watchlo0(0);
	पूर्ण
पूर्ण

व्योम mips_probe_watch_रेजिस्टरs(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक t;

	अगर ((c->options & MIPS_CPU_WATCH) == 0)
		वापस;
	/*
	 * Check which of the I,R and W bits are supported, then
	 * disable the रेजिस्टर.
	 */
	ग_लिखो_c0_watchlo0(MIPS_WATCHLO_IRW);
	back_to_back_c0_hazard();
	t = पढ़ो_c0_watchlo0();
	ग_लिखो_c0_watchlo0(0);
	c->watch_reg_masks[0] = t & MIPS_WATCHLO_IRW;

	/* Write the mask bits and पढ़ो them back to determine which
	 * can be used. */
	c->watch_reg_count = 1;
	c->watch_reg_use_cnt = 1;
	t = पढ़ो_c0_watchhi0();
	ग_लिखो_c0_watchhi0(t | MIPS_WATCHHI_MASK);
	back_to_back_c0_hazard();
	t = पढ़ो_c0_watchhi0();
	c->watch_reg_masks[0] |= (t & MIPS_WATCHHI_MASK);
	अगर ((t & MIPS_WATCHHI_M) == 0)
		वापस;

	ग_लिखो_c0_watchlo1(MIPS_WATCHLO_IRW);
	back_to_back_c0_hazard();
	t = पढ़ो_c0_watchlo1();
	ग_लिखो_c0_watchlo1(0);
	c->watch_reg_masks[1] = t & MIPS_WATCHLO_IRW;

	c->watch_reg_count = 2;
	c->watch_reg_use_cnt = 2;
	t = पढ़ो_c0_watchhi1();
	ग_लिखो_c0_watchhi1(t | MIPS_WATCHHI_MASK);
	back_to_back_c0_hazard();
	t = पढ़ो_c0_watchhi1();
	c->watch_reg_masks[1] |= (t & MIPS_WATCHHI_MASK);
	अगर ((t & MIPS_WATCHHI_M) == 0)
		वापस;

	ग_लिखो_c0_watchlo2(MIPS_WATCHLO_IRW);
	back_to_back_c0_hazard();
	t = पढ़ो_c0_watchlo2();
	ग_लिखो_c0_watchlo2(0);
	c->watch_reg_masks[2] = t & MIPS_WATCHLO_IRW;

	c->watch_reg_count = 3;
	c->watch_reg_use_cnt = 3;
	t = पढ़ो_c0_watchhi2();
	ग_लिखो_c0_watchhi2(t | MIPS_WATCHHI_MASK);
	back_to_back_c0_hazard();
	t = पढ़ो_c0_watchhi2();
	c->watch_reg_masks[2] |= (t & MIPS_WATCHHI_MASK);
	अगर ((t & MIPS_WATCHHI_M) == 0)
		वापस;

	ग_लिखो_c0_watchlo3(MIPS_WATCHLO_IRW);
	back_to_back_c0_hazard();
	t = पढ़ो_c0_watchlo3();
	ग_लिखो_c0_watchlo3(0);
	c->watch_reg_masks[3] = t & MIPS_WATCHLO_IRW;

	c->watch_reg_count = 4;
	c->watch_reg_use_cnt = 4;
	t = पढ़ो_c0_watchhi3();
	ग_लिखो_c0_watchhi3(t | MIPS_WATCHHI_MASK);
	back_to_back_c0_hazard();
	t = पढ़ो_c0_watchhi3();
	c->watch_reg_masks[3] |= (t & MIPS_WATCHHI_MASK);
	अगर ((t & MIPS_WATCHHI_M) == 0)
		वापस;

	/* We use at most 4, but probe and report up to 8. */
	c->watch_reg_count = 5;
	t = पढ़ो_c0_watchhi4();
	अगर ((t & MIPS_WATCHHI_M) == 0)
		वापस;

	c->watch_reg_count = 6;
	t = पढ़ो_c0_watchhi5();
	अगर ((t & MIPS_WATCHHI_M) == 0)
		वापस;

	c->watch_reg_count = 7;
	t = पढ़ो_c0_watchhi6();
	अगर ((t & MIPS_WATCHHI_M) == 0)
		वापस;

	c->watch_reg_count = 8;
पूर्ण
