<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#घोषणा _GNU_SOURCE	/* For CPU_ZERO etc. */

#समावेश <sched.h>
#समावेश <sys/रुको.h>
#समावेश <समलाँघ.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "trace.h"
#समावेश "ebb.h"


व्योम (*ebb_user_func)(व्योम);

व्योम ebb_hook(व्योम)
अणु
	अगर (ebb_user_func)
		ebb_user_func();
पूर्ण

काष्ठा ebb_state ebb_state;

u64 sample_period = 0x40000000ull;

व्योम reset_ebb_with_clear_mask(अचिन्हित दीर्घ mmcr0_clear_mask)
अणु
	u64 val;

	/* 2) clear MMCR0[PMAO] - करोcs say BESCR[PMEO] should करो this */
	/* 3) set MMCR0[PMAE]	- करोcs say BESCR[PME] should करो this */
	val = mfspr(SPRN_MMCR0);
	mtspr(SPRN_MMCR0, (val & ~mmcr0_clear_mask) | MMCR0_PMAE);

	/* 4) clear BESCR[PMEO] */
	mtspr(SPRN_BESCRR, BESCR_PMEO);

	/* 5) set BESCR[PME] */
	mtspr(SPRN_BESCRS, BESCR_PME);

	/* 6) rfebb 1 - करोne in our caller */
पूर्ण

व्योम reset_ebb(व्योम)
अणु
	reset_ebb_with_clear_mask(MMCR0_PMAO | MMCR0_FC);
पूर्ण

/* Called outside of the EBB handler to check MMCR0 is sane */
पूर्णांक ebb_check_mmcr0(व्योम)
अणु
	u64 val;

	val = mfspr(SPRN_MMCR0);
	अगर ((val & (MMCR0_FC | MMCR0_PMAO)) == MMCR0_FC) अणु
		/* It's OK अगर we see FC & PMAO, but not FC by itself */
		म_लिखो("Outside of loop, only FC set 0x%llx\n", val);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

bool ebb_check_count(पूर्णांक pmc, u64 sample_period, पूर्णांक fudge)
अणु
	u64 count, upper, lower;

	count = ebb_state.stats.pmc_count[PMC_INDEX(pmc)];

	lower = ebb_state.stats.ebb_count * (sample_period - fudge);

	अगर (count < lower) अणु
		म_लिखो("PMC%d count (0x%llx) below lower limit 0x%llx (-0x%llx)\n",
			pmc, count, lower, lower - count);
		वापस false;
	पूर्ण

	upper = ebb_state.stats.ebb_count * (sample_period + fudge);

	अगर (count > upper) अणु
		म_लिखो("PMC%d count (0x%llx) above upper limit 0x%llx (+0x%llx)\n",
			pmc, count, upper, count - upper);
		वापस false;
	पूर्ण

	म_लिखो("PMC%d count (0x%llx) is between 0x%llx and 0x%llx delta +0x%llx/-0x%llx\n",
		pmc, count, lower, upper, count - lower, upper - count);

	वापस true;
पूर्ण

व्योम standard_ebb_callee(व्योम)
अणु
	पूर्णांक found, i;
	u64 val;

	val = mfspr(SPRN_BESCR);
	अगर (!(val & BESCR_PMEO)) अणु
		ebb_state.stats.spurious++;
		जाओ out;
	पूर्ण

	ebb_state.stats.ebb_count++;
	trace_log_counter(ebb_state.trace, ebb_state.stats.ebb_count);

	val = mfspr(SPRN_MMCR0);
	trace_log_reg(ebb_state.trace, SPRN_MMCR0, val);

	found = 0;
	क्रम (i = 1; i <= 6; i++) अणु
		अगर (ebb_state.pmc_enable[PMC_INDEX(i)])
			found += count_pmc(i, sample_period);
	पूर्ण

	अगर (!found)
		ebb_state.stats.no_overflow++;

out:
	reset_ebb();
पूर्ण

बाह्य व्योम ebb_handler(व्योम);

व्योम setup_ebb_handler(व्योम (*callee)(व्योम))
अणु
	u64 entry;

#अगर defined(_CALL_ELF) && _CALL_ELF == 2
	entry = (u64)ebb_handler;
#अन्यथा
	काष्ठा opd
	अणु
	    u64 entry;
	    u64 toc;
	पूर्ण *opd;

	opd = (काष्ठा opd *)ebb_handler;
	entry = opd->entry;
#पूर्ण_अगर
	म_लिखो("EBB Handler is at %#llx\n", entry);

	ebb_user_func = callee;

	/* Ensure ebb_user_func is set beक्रमe we set the handler */
	mb();
	mtspr(SPRN_EBBHR, entry);

	/* Make sure the handler is set beक्रमe we वापस */
	mb();
पूर्ण

व्योम clear_ebb_stats(व्योम)
अणु
	स_रखो(&ebb_state.stats, 0, माप(ebb_state.stats));
पूर्ण

व्योम dump_summary_ebb_state(व्योम)
अणु
	म_लिखो("ebb_state:\n"			\
	       "  ebb_count    = %d\n"		\
	       "  spurious     = %d\n"		\
	       "  negative     = %d\n"		\
	       "  no_overflow  = %d\n"		\
	       "  pmc[1] count = 0x%llx\n"	\
	       "  pmc[2] count = 0x%llx\n"	\
	       "  pmc[3] count = 0x%llx\n"	\
	       "  pmc[4] count = 0x%llx\n"	\
	       "  pmc[5] count = 0x%llx\n"	\
	       "  pmc[6] count = 0x%llx\n",
		ebb_state.stats.ebb_count, ebb_state.stats.spurious,
		ebb_state.stats.negative, ebb_state.stats.no_overflow,
		ebb_state.stats.pmc_count[0], ebb_state.stats.pmc_count[1],
		ebb_state.stats.pmc_count[2], ebb_state.stats.pmc_count[3],
		ebb_state.stats.pmc_count[4], ebb_state.stats.pmc_count[5]);
पूर्ण

अटल अक्षर *decode_mmcr0(u32 value)
अणु
	अटल अक्षर buf[16];

	buf[0] = '\0';

	अगर (value & (1 << 31))
		म_जोड़ो(buf, "FC ");
	अगर (value & (1 << 26))
		म_जोड़ो(buf, "PMAE ");
	अगर (value & (1 << 7))
		म_जोड़ो(buf, "PMAO ");

	वापस buf;
पूर्ण

अटल अक्षर *decode_bescr(u64 value)
अणु
	अटल अक्षर buf[16];

	buf[0] = '\0';

	अगर (value & (1ull << 63))
		म_जोड़ो(buf, "GE ");
	अगर (value & (1ull << 32))
		म_जोड़ो(buf, "PMAE ");
	अगर (value & 1)
		म_जोड़ो(buf, "PMAO ");

	वापस buf;
पूर्ण

व्योम dump_ebb_hw_state(व्योम)
अणु
	u64 bescr;
	u32 mmcr0;

	mmcr0 = mfspr(SPRN_MMCR0);
	bescr = mfspr(SPRN_BESCR);

	म_लिखो("HW state:\n"		\
	       "MMCR0 0x%016x %s\n"	\
	       "MMCR2 0x%016lx\n"	\
	       "EBBHR 0x%016lx\n"	\
	       "BESCR 0x%016llx %s\n"	\
	       "PMC1  0x%016lx\n"	\
	       "PMC2  0x%016lx\n"	\
	       "PMC3  0x%016lx\n"	\
	       "PMC4  0x%016lx\n"	\
	       "PMC5  0x%016lx\n"	\
	       "PMC6  0x%016lx\n"	\
	       "SIAR  0x%016lx\n",
	       mmcr0, decode_mmcr0(mmcr0), mfspr(SPRN_MMCR2),
	       mfspr(SPRN_EBBHR), bescr, decode_bescr(bescr),
	       mfspr(SPRN_PMC1), mfspr(SPRN_PMC2), mfspr(SPRN_PMC3),
	       mfspr(SPRN_PMC4), mfspr(SPRN_PMC5), mfspr(SPRN_PMC6),
	       mfspr(SPRN_SIAR));
पूर्ण

व्योम dump_ebb_state(व्योम)
अणु
	dump_summary_ebb_state();

	dump_ebb_hw_state();

	trace_buffer_prपूर्णांक(ebb_state.trace);
पूर्ण

पूर्णांक count_pmc(पूर्णांक pmc, uपूर्णांक32_t sample_period)
अणु
	uपूर्णांक32_t start_value;
	u64 val;

	/* 0) Read PMC */
	start_value = pmc_sample_period(sample_period);

	val = पढ़ो_pmc(pmc);
	अगर (val < start_value)
		ebb_state.stats.negative++;
	अन्यथा
		ebb_state.stats.pmc_count[PMC_INDEX(pmc)] += val - start_value;

	trace_log_reg(ebb_state.trace, SPRN_PMC1 + pmc - 1, val);

	/* 1) Reset PMC */
	ग_लिखो_pmc(pmc, start_value);

	/* Report अगर we overflowed */
	वापस val >= COUNTER_OVERFLOW;
पूर्ण

पूर्णांक ebb_event_enable(काष्ठा event *e)
अणु
	पूर्णांक rc;

	/* Ensure any SPR ग_लिखोs are ordered vs us */
	mb();

	rc = ioctl(e->fd, PERF_EVENT_IOC_ENABLE);
	अगर (rc)
		वापस rc;

	rc = event_पढ़ो(e);

	/* Ditto */
	mb();

	वापस rc;
पूर्ण

व्योम ebb_मुक्तze_pmcs(व्योम)
अणु
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) | MMCR0_FC);
	mb();
पूर्ण

व्योम ebb_unमुक्तze_pmcs(व्योम)
अणु
	/* Unमुक्तze counters */
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~MMCR0_FC);
	mb();
पूर्ण

व्योम ebb_global_enable(व्योम)
अणु
	/* Enable EBBs globally and PMU EBBs */
	mtspr(SPRN_BESCR, 0x8000000100000000ull);
	mb();
पूर्ण

व्योम ebb_global_disable(व्योम)
अणु
	/* Disable EBBs & मुक्तze counters, events are still scheduled */
	mtspr(SPRN_BESCRR, BESCR_PME);
	mb();
पूर्ण

bool ebb_is_supported(व्योम)
अणु
#अगर_घोषित PPC_FEATURE2_EBB
	/* EBB requires at least POWER8 */
	वापस have_hwcap2(PPC_FEATURE2_EBB);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

व्योम event_ebb_init(काष्ठा event *e)
अणु
	e->attr.config |= (1ull << 63);
पूर्ण

व्योम event_bhrb_init(काष्ठा event *e, अचिन्हित अगरm)
अणु
	e->attr.config |= (1ull << 62) | ((u64)अगरm << 60);
पूर्ण

व्योम event_leader_ebb_init(काष्ठा event *e)
अणु
	event_ebb_init(e);

	e->attr.exclusive = 1;
	e->attr.pinned = 1;
पूर्ण

पूर्णांक ebb_child(जोड़ pipe पढ़ो_pipe, जोड़ pipe ग_लिखो_pipe)
अणु
	काष्ठा event event;
	uपूर्णांक64_t val;

	FAIL_IF(रुको_क्रम_parent(पढ़ो_pipe));

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो(&event));

	ebb_enable_pmc_counting(1);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();

	FAIL_IF(event_enable(&event));

	अगर (event_पढ़ो(&event)) अणु
		/*
		 * Some tests expect to fail here, so करोn't report an error on
		 * this line, and वापस a distinguisable error code. Tell the
		 * parent an error happened.
		 */
		notअगरy_parent_of_error(ग_लिखो_pipe);
		वापस 2;
	पूर्ण

	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	FAIL_IF(notअगरy_parent(ग_लिखो_pipe));
	FAIL_IF(रुको_क्रम_parent(पढ़ो_pipe));
	FAIL_IF(notअगरy_parent(ग_लिखो_pipe));

	जबतक (ebb_state.stats.ebb_count < 20) अणु
		FAIL_IF(core_busy_loop());

		/* To try and hit संक_अवैध हाल */
		val  = mfspr(SPRN_MMCRA);
		val |= mfspr(SPRN_MMCR2);
		val |= mfspr(SPRN_MMCR0);
	पूर्ण

	ebb_global_disable();
	ebb_मुक्तze_pmcs();

	dump_ebb_state();

	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);

	वापस 0;
पूर्ण

अटल लाँघ_बफ बनाओ_लाँघ_env;

अटल व्योम sigill_handler(पूर्णांक संकेत)
अणु
	म_लिखो("Took sigill\n");
	दीर्घ_लाँघ(बनाओ_लाँघ_env, 1);
पूर्ण

अटल काष्ठा sigaction sigill_action = अणु
	.sa_handler = sigill_handler,
पूर्ण;

पूर्णांक catch_sigill(व्योम (*func)(व्योम))
अणु
	अगर (sigaction(संक_अवैध, &sigill_action, शून्य)) अणु
		लिखो_त्रुटि("sigaction");
		वापस 1;
	पूर्ण

	अगर (बनाओ_लाँघ(बनाओ_लाँघ_env) == 0) अणु
		func();
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ग_लिखो_pmc1(व्योम)
अणु
	mtspr(SPRN_PMC1, 0);
पूर्ण

व्योम ग_लिखो_pmc(पूर्णांक pmc, u64 value)
अणु
	चयन (pmc) अणु
		हाल 1: mtspr(SPRN_PMC1, value); अवरोध;
		हाल 2: mtspr(SPRN_PMC2, value); अवरोध;
		हाल 3: mtspr(SPRN_PMC3, value); अवरोध;
		हाल 4: mtspr(SPRN_PMC4, value); अवरोध;
		हाल 5: mtspr(SPRN_PMC5, value); अवरोध;
		हाल 6: mtspr(SPRN_PMC6, value); अवरोध;
	पूर्ण
पूर्ण

u64 पढ़ो_pmc(पूर्णांक pmc)
अणु
	चयन (pmc) अणु
		हाल 1: वापस mfspr(SPRN_PMC1);
		हाल 2: वापस mfspr(SPRN_PMC2);
		हाल 3: वापस mfspr(SPRN_PMC3);
		हाल 4: वापस mfspr(SPRN_PMC4);
		हाल 5: वापस mfspr(SPRN_PMC5);
		हाल 6: वापस mfspr(SPRN_PMC6);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम term_handler(पूर्णांक संकेत)
अणु
	dump_summary_ebb_state();
	dump_ebb_hw_state();
	पात();
पूर्ण

काष्ठा sigaction term_action = अणु
	.sa_handler = term_handler,
पूर्ण;

अटल व्योम __attribute__((स्थिरructor)) ebb_init(व्योम)
अणु
	clear_ebb_stats();

	अगर (sigaction(संक_इति, &term_action, शून्य))
		लिखो_त्रुटि("sigaction");

	ebb_state.trace = trace_buffer_allocate(1 * 1024 * 1024);
पूर्ण
