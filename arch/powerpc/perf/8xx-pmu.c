<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance event support - PPC 8xx
 *
 * Copyright 2016 Christophe Leroy, CS Systemes d'Inक्रमmation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <यंत्र/pmc.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/inst.h>

#घोषणा PERF_8xx_ID_CPU_CYCLES		1
#घोषणा PERF_8xx_ID_HW_INSTRUCTIONS	2
#घोषणा PERF_8xx_ID_ITLB_LOAD_MISS	3
#घोषणा PERF_8xx_ID_DTLB_LOAD_MISS	4

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x
#घोषणा DTLB_LOAD_MISS	(C(DTLB) | (C(OP_READ) << 8) | (C(RESULT_MISS) << 16))
#घोषणा ITLB_LOAD_MISS	(C(ITLB) | (C(OP_READ) << 8) | (C(RESULT_MISS) << 16))

बाह्य अचिन्हित दीर्घ itlb_miss_counter, dtlb_miss_counter;
बाह्य atomic_t inकाष्ठाion_counter;

अटल atomic_t insn_ctr_ref;
अटल atomic_t itlb_miss_ref;
अटल atomic_t dtlb_miss_ref;

अटल s64 get_insn_ctr(व्योम)
अणु
	पूर्णांक ctr;
	अचिन्हित दीर्घ counta;

	करो अणु
		ctr = atomic_पढ़ो(&inकाष्ठाion_counter);
		counta = mfspr(SPRN_COUNTA);
	पूर्ण जबतक (ctr != atomic_पढ़ो(&inकाष्ठाion_counter));

	वापस ((s64)ctr << 16) | (counta >> 16);
पूर्ण

अटल पूर्णांक event_type(काष्ठा perf_event *event)
अणु
	चयन (event->attr.type) अणु
	हाल PERF_TYPE_HARDWARE:
		अगर (event->attr.config == PERF_COUNT_HW_CPU_CYCLES)
			वापस PERF_8xx_ID_CPU_CYCLES;
		अगर (event->attr.config == PERF_COUNT_HW_INSTRUCTIONS)
			वापस PERF_8xx_ID_HW_INSTRUCTIONS;
		अवरोध;
	हाल PERF_TYPE_HW_CACHE:
		अगर (event->attr.config == ITLB_LOAD_MISS)
			वापस PERF_8xx_ID_ITLB_LOAD_MISS;
		अगर (event->attr.config == DTLB_LOAD_MISS)
			वापस PERF_8xx_ID_DTLB_LOAD_MISS;
		अवरोध;
	हाल PERF_TYPE_RAW:
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mpc8xx_pmu_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक type = event_type(event);

	अगर (type < 0)
		वापस type;
	वापस 0;
पूर्ण

अटल पूर्णांक mpc8xx_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक type = event_type(event);
	s64 val = 0;

	अगर (type < 0)
		वापस type;

	चयन (type) अणु
	हाल PERF_8xx_ID_CPU_CYCLES:
		val = get_tb();
		अवरोध;
	हाल PERF_8xx_ID_HW_INSTRUCTIONS:
		अगर (atomic_inc_वापस(&insn_ctr_ref) == 1)
			mtspr(SPRN_ICTRL, 0xc0080007);
		val = get_insn_ctr();
		अवरोध;
	हाल PERF_8xx_ID_ITLB_LOAD_MISS:
		अगर (atomic_inc_वापस(&itlb_miss_ref) == 1) अणु
			अचिन्हित दीर्घ target = patch_site_addr(&patch__itlbmiss_perf);

			patch_branch_site(&patch__itlbmiss_निकास_1, target, 0);
		पूर्ण
		val = itlb_miss_counter;
		अवरोध;
	हाल PERF_8xx_ID_DTLB_LOAD_MISS:
		अगर (atomic_inc_वापस(&dtlb_miss_ref) == 1) अणु
			अचिन्हित दीर्घ target = patch_site_addr(&patch__dtlbmiss_perf);

			patch_branch_site(&patch__dtlbmiss_निकास_1, target, 0);
		पूर्ण
		val = dtlb_miss_counter;
		अवरोध;
	पूर्ण
	local64_set(&event->hw.prev_count, val);
	वापस 0;
पूर्ण

अटल व्योम mpc8xx_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	पूर्णांक type = event_type(event);
	s64 prev, val = 0, delta = 0;

	अगर (type < 0)
		वापस;

	करो अणु
		prev = local64_पढ़ो(&event->hw.prev_count);
		चयन (type) अणु
		हाल PERF_8xx_ID_CPU_CYCLES:
			val = get_tb();
			delta = 16 * (val - prev);
			अवरोध;
		हाल PERF_8xx_ID_HW_INSTRUCTIONS:
			val = get_insn_ctr();
			delta = prev - val;
			अगर (delta < 0)
				delta += 0x1000000000000LL;
			अवरोध;
		हाल PERF_8xx_ID_ITLB_LOAD_MISS:
			val = itlb_miss_counter;
			delta = (s64)((s32)val - (s32)prev);
			अवरोध;
		हाल PERF_8xx_ID_DTLB_LOAD_MISS:
			val = dtlb_miss_counter;
			delta = (s64)((s32)val - (s32)prev);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (local64_cmpxchg(&event->hw.prev_count, prev, val) != prev);

	local64_add(delta, &event->count);
पूर्ण

अटल व्योम mpc8xx_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा ppc_inst insn = ppc_inst(PPC_RAW_MFSPR(10, SPRN_SPRG_SCRATCH2));

	mpc8xx_pmu_पढ़ो(event);

	/* If it was the last user, stop counting to aव्योम useles overhead */
	चयन (event_type(event)) अणु
	हाल PERF_8xx_ID_CPU_CYCLES:
		अवरोध;
	हाल PERF_8xx_ID_HW_INSTRUCTIONS:
		अगर (atomic_dec_वापस(&insn_ctr_ref) == 0)
			mtspr(SPRN_ICTRL, 7);
		अवरोध;
	हाल PERF_8xx_ID_ITLB_LOAD_MISS:
		अगर (atomic_dec_वापस(&itlb_miss_ref) == 0)
			patch_inकाष्ठाion_site(&patch__itlbmiss_निकास_1, insn);
		अवरोध;
	हाल PERF_8xx_ID_DTLB_LOAD_MISS:
		अगर (atomic_dec_वापस(&dtlb_miss_ref) == 0)
			patch_inकाष्ठाion_site(&patch__dtlbmiss_निकास_1, insn);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा pmu mpc8xx_pmu = अणु
	.event_init	= mpc8xx_pmu_event_init,
	.add		= mpc8xx_pmu_add,
	.del		= mpc8xx_pmu_del,
	.पढ़ो		= mpc8xx_pmu_पढ़ो,
	.capabilities	= PERF_PMU_CAP_NO_INTERRUPT |
			  PERF_PMU_CAP_NO_NMI,
पूर्ण;

अटल पूर्णांक init_mpc8xx_pmu(व्योम)
अणु
	mtspr(SPRN_ICTRL, 7);
	mtspr(SPRN_CMPA, 0);
	mtspr(SPRN_COUNTA, 0xffff);

	वापस perf_pmu_रेजिस्टर(&mpc8xx_pmu, "cpu", PERF_TYPE_RAW);
पूर्ण

early_initcall(init_mpc8xx_pmu);
