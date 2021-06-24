<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <माला.स>

#समावेश <linux/compiler.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/barrier.h>

#समावेश "event.h"
#समावेश "synthetic-events.h"
#समावेश "debug.h"
#समावेश "tsc.h"

u64 perf_समय_प्रकारo_tsc(u64 ns, काष्ठा perf_tsc_conversion *tc)
अणु
	u64 t, quot, rem;

	t = ns - tc->समय_zero;
	quot = t / tc->समय_mult;
	rem  = t % tc->समय_mult;
	वापस (quot << tc->समय_shअगरt) +
	       (rem << tc->समय_shअगरt) / tc->समय_mult;
पूर्ण

u64 tsc_to_perf_समय(u64 cyc, काष्ठा perf_tsc_conversion *tc)
अणु
	u64 quot, rem;

	अगर (tc->cap_user_समय_लघु)
		cyc = tc->समय_cycles +
			((cyc - tc->समय_cycles) & tc->समय_mask);

	quot = cyc >> tc->समय_shअगरt;
	rem  = cyc & (((u64)1 << tc->समय_shअगरt) - 1);
	वापस tc->समय_zero + quot * tc->समय_mult +
	       ((rem * tc->समय_mult) >> tc->समय_shअगरt);
पूर्ण

पूर्णांक perf_पढ़ो_tsc_conversion(स्थिर काष्ठा perf_event_mmap_page *pc,
			     काष्ठा perf_tsc_conversion *tc)
अणु
	u32 seq;
	पूर्णांक i = 0;

	जबतक (1) अणु
		seq = pc->lock;
		rmb();
		tc->समय_mult = pc->समय_mult;
		tc->समय_shअगरt = pc->समय_shअगरt;
		tc->समय_zero = pc->समय_zero;
		tc->समय_cycles = pc->समय_cycles;
		tc->समय_mask = pc->समय_mask;
		tc->cap_user_समय_zero = pc->cap_user_समय_zero;
		tc->cap_user_समय_लघु	= pc->cap_user_समय_लघु;
		rmb();
		अगर (pc->lock == seq && !(seq & 1))
			अवरोध;
		अगर (++i > 10000) अणु
			pr_debug("failed to get perf_event_mmap_page lock\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!tc->cap_user_समय_zero)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

पूर्णांक perf_event__synth_समय_conv(स्थिर काष्ठा perf_event_mmap_page *pc,
				काष्ठा perf_tool *tool,
				perf_event__handler_t process,
				काष्ठा machine *machine)
अणु
	जोड़ perf_event event = अणु
		.समय_conv = अणु
			.header = अणु
				.type = PERF_RECORD_TIME_CONV,
				.size = माप(काष्ठा perf_record_समय_conv),
			पूर्ण,
		पूर्ण,
	पूर्ण;
	काष्ठा perf_tsc_conversion tc;
	पूर्णांक err;

	अगर (!pc)
		वापस 0;
	err = perf_पढ़ो_tsc_conversion(pc, &tc);
	अगर (err == -EOPNOTSUPP)
		वापस 0;
	अगर (err)
		वापस err;

	pr_debug2("Synthesizing TSC conversion information\n");

	event.समय_conv.समय_mult  = tc.समय_mult;
	event.समय_conv.समय_shअगरt = tc.समय_shअगरt;
	event.समय_conv.समय_zero  = tc.समय_zero;
	event.समय_conv.समय_cycles = tc.समय_cycles;
	event.समय_conv.समय_mask = tc.समय_mask;
	event.समय_conv.cap_user_समय_zero = tc.cap_user_समय_zero;
	event.समय_conv.cap_user_समय_लघु = tc.cap_user_समय_लघु;

	वापस process(tool, &event, शून्य, machine);
पूर्ण

u64 __weak rdtsc(व्योम)
अणु
	वापस 0;
पूर्ण

माप_प्रकार perf_event__ख_लिखो_समय_conv(जोड़ perf_event *event, खाता *fp)
अणु
	काष्ठा perf_record_समय_conv *tc = (काष्ठा perf_record_समय_conv *)event;
	माप_प्रकार ret;

	ret  = ख_लिखो(fp, "\n... Time Shift      %" PRI_lu64 "\n", tc->समय_shअगरt);
	ret += ख_लिखो(fp, "... Time Muliplier  %" PRI_lu64 "\n", tc->समय_mult);
	ret += ख_लिखो(fp, "... Time Zero       %" PRI_lu64 "\n", tc->समय_zero);

	/*
	 * The event TIME_CONV was extended क्रम the fields from "time_cycles"
	 * when supported cap_user_समय_लघु, क्रम backward compatibility,
	 * prपूर्णांकs the extended fields only अगर they are contained in the event.
	 */
	अगर (event_contains(*tc, समय_cycles)) अणु
		ret += ख_लिखो(fp, "... Time Cycles     %" PRI_lu64 "\n",
			       tc->समय_cycles);
		ret += ख_लिखो(fp, "... Time Mask       %#" PRI_lx64 "\n",
			       tc->समय_mask);
		ret += ख_लिखो(fp, "... Cap Time Zero   %" PRId32 "\n",
			       tc->cap_user_समय_zero);
		ret += ख_लिखो(fp, "... Cap Time Short  %" PRId32 "\n",
			       tc->cap_user_समय_लघु);
	पूर्ण

	वापस ret;
पूर्ण
