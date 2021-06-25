<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <stdbool.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "map_symbol.h"
#समावेश "branch.h"
#समावेश "event.h"
#समावेश "evsel.h"
#समावेश "debug.h"
#समावेश "util/synthetic-events.h"

#समावेश "tests.h"

#घोषणा COMP(m) करो अणु					\
	अगर (s1->m != s2->m) अणु				\
		pr_debug("Samples differ at '"#m"'\n");	\
		वापस false;				\
	पूर्ण						\
पूर्ण जबतक (0)

#घोषणा MCOMP(m) करो अणु					\
	अगर (स_भेद(&s1->m, &s2->m, माप(s1->m))) अणु	\
		pr_debug("Samples differ at '"#m"'\n");	\
		वापस false;				\
	पूर्ण						\
पूर्ण जबतक (0)

अटल bool samples_same(स्थिर काष्ठा perf_sample *s1,
			 स्थिर काष्ठा perf_sample *s2,
			 u64 type, u64 पढ़ो_क्रमmat)
अणु
	माप_प्रकार i;

	अगर (type & PERF_SAMPLE_IDENTIFIER)
		COMP(id);

	अगर (type & PERF_SAMPLE_IP)
		COMP(ip);

	अगर (type & PERF_SAMPLE_TID) अणु
		COMP(pid);
		COMP(tid);
	पूर्ण

	अगर (type & PERF_SAMPLE_TIME)
		COMP(समय);

	अगर (type & PERF_SAMPLE_ADDR)
		COMP(addr);

	अगर (type & PERF_SAMPLE_ID)
		COMP(id);

	अगर (type & PERF_SAMPLE_STREAM_ID)
		COMP(stream_id);

	अगर (type & PERF_SAMPLE_CPU)
		COMP(cpu);

	अगर (type & PERF_SAMPLE_PERIOD)
		COMP(period);

	अगर (type & PERF_SAMPLE_READ) अणु
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP)
			COMP(पढ़ो.group.nr);
		अन्यथा
			COMP(पढ़ो.one.value);
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
			COMP(पढ़ो.समय_enabled);
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
			COMP(पढ़ो.समय_running);
		/* PERF_FORMAT_ID is क्रमced क्रम PERF_SAMPLE_READ */
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP) अणु
			क्रम (i = 0; i < s1->पढ़ो.group.nr; i++)
				MCOMP(पढ़ो.group.values[i]);
		पूर्ण अन्यथा अणु
			COMP(पढ़ो.one.id);
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_CALLCHAIN) अणु
		COMP(callchain->nr);
		क्रम (i = 0; i < s1->callchain->nr; i++)
			COMP(callchain->ips[i]);
	पूर्ण

	अगर (type & PERF_SAMPLE_RAW) अणु
		COMP(raw_size);
		अगर (स_भेद(s1->raw_data, s2->raw_data, s1->raw_size)) अणु
			pr_debug("Samples differ at 'raw_data'\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_BRANCH_STACK) अणु
		COMP(branch_stack->nr);
		COMP(branch_stack->hw_idx);
		क्रम (i = 0; i < s1->branch_stack->nr; i++)
			MCOMP(branch_stack->entries[i]);
	पूर्ण

	अगर (type & PERF_SAMPLE_REGS_USER) अणु
		माप_प्रकार sz = hweight_दीर्घ(s1->user_regs.mask) * माप(u64);

		COMP(user_regs.mask);
		COMP(user_regs.abi);
		अगर (s1->user_regs.abi &&
		    (!s1->user_regs.regs || !s2->user_regs.regs ||
		     स_भेद(s1->user_regs.regs, s2->user_regs.regs, sz))) अणु
			pr_debug("Samples differ at 'user_regs'\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_STACK_USER) अणु
		COMP(user_stack.size);
		अगर (स_भेद(s1->user_stack.data, s2->user_stack.data,
			   s1->user_stack.size)) अणु
			pr_debug("Samples differ at 'user_stack'\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_WEIGHT)
		COMP(weight);

	अगर (type & PERF_SAMPLE_DATA_SRC)
		COMP(data_src);

	अगर (type & PERF_SAMPLE_TRANSACTION)
		COMP(transaction);

	अगर (type & PERF_SAMPLE_REGS_INTR) अणु
		माप_प्रकार sz = hweight_दीर्घ(s1->पूर्णांकr_regs.mask) * माप(u64);

		COMP(पूर्णांकr_regs.mask);
		COMP(पूर्णांकr_regs.abi);
		अगर (s1->पूर्णांकr_regs.abi &&
		    (!s1->पूर्णांकr_regs.regs || !s2->पूर्णांकr_regs.regs ||
		     स_भेद(s1->पूर्णांकr_regs.regs, s2->पूर्णांकr_regs.regs, sz))) अणु
			pr_debug("Samples differ at 'intr_regs'\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_PHYS_ADDR)
		COMP(phys_addr);

	अगर (type & PERF_SAMPLE_CGROUP)
		COMP(cgroup);

	अगर (type & PERF_SAMPLE_DATA_PAGE_SIZE)
		COMP(data_page_size);

	अगर (type & PERF_SAMPLE_CODE_PAGE_SIZE)
		COMP(code_page_size);

	अगर (type & PERF_SAMPLE_AUX) अणु
		COMP(aux_sample.size);
		अगर (स_भेद(s1->aux_sample.data, s2->aux_sample.data,
			   s1->aux_sample.size)) अणु
			pr_debug("Samples differ at 'aux_sample'\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक करो_test(u64 sample_type, u64 sample_regs, u64 पढ़ो_क्रमmat)
अणु
	काष्ठा evsel evsel = अणु
		.needs_swap = false,
		.core = अणु
			. attr = अणु
				.sample_type = sample_type,
				.पढ़ो_क्रमmat = पढ़ो_क्रमmat,
			पूर्ण,
		पूर्ण,
	पूर्ण;
	जोड़ perf_event *event;
	जोड़ अणु
		काष्ठा ip_callchain callchain;
		u64 data[64];
	पूर्ण callchain = अणु
		/* 3 ips */
		.data = अणु3, 201, 202, 203पूर्ण,
	पूर्ण;
	जोड़ अणु
		काष्ठा branch_stack branch_stack;
		u64 data[64];
	पूर्ण branch_stack = अणु
		/* 1 branch_entry */
		.data = अणु1, -1ULL, 211, 212, 213पूर्ण,
	पूर्ण;
	u64 regs[64];
	स्थिर u32 raw_data[] = अणु0x12345678, 0x0a0b0c0d, 0x11020304, 0x05060708, 0 पूर्ण;
	स्थिर u64 data[] = अणु0x2211443366558877ULL, 0, 0xaabbccddeeff4321ULLपूर्ण;
	स्थिर u64 aux_data[] = अणु0xa55a, 0, 0xeeddee, 0x0282028202820282पूर्ण;
	काष्ठा perf_sample sample = अणु
		.ip		= 101,
		.pid		= 102,
		.tid		= 103,
		.समय		= 104,
		.addr		= 105,
		.id		= 106,
		.stream_id	= 107,
		.period		= 108,
		.weight		= 109,
		.cpu		= 110,
		.raw_size	= माप(raw_data),
		.data_src	= 111,
		.transaction	= 112,
		.raw_data	= (व्योम *)raw_data,
		.callchain	= &callchain.callchain,
		.no_hw_idx      = false,
		.branch_stack	= &branch_stack.branch_stack,
		.user_regs	= अणु
			.abi	= PERF_SAMPLE_REGS_ABI_64,
			.mask	= sample_regs,
			.regs	= regs,
		पूर्ण,
		.user_stack	= अणु
			.size	= माप(data),
			.data	= (व्योम *)data,
		पूर्ण,
		.पढ़ो		= अणु
			.समय_enabled = 0x030a59d664fca7deULL,
			.समय_running = 0x011b6ae553eb98edULL,
		पूर्ण,
		.पूर्णांकr_regs	= अणु
			.abi	= PERF_SAMPLE_REGS_ABI_64,
			.mask	= sample_regs,
			.regs	= regs,
		पूर्ण,
		.phys_addr	= 113,
		.cgroup		= 114,
		.data_page_size = 115,
		.code_page_size = 116,
		.aux_sample	= अणु
			.size	= माप(aux_data),
			.data	= (व्योम *)aux_data,
		पूर्ण,
	पूर्ण;
	काष्ठा sample_पढ़ो_value values[] = अणुअणु1, 5पूर्ण, अणु9, 3पूर्ण, अणु2, 7पूर्ण, अणु6, 4पूर्ण,पूर्ण;
	काष्ठा perf_sample sample_out;
	माप_प्रकार i, sz, bufsz;
	पूर्णांक err, ret = -1;

	अगर (sample_type & PERF_SAMPLE_REGS_USER)
		evsel.core.attr.sample_regs_user = sample_regs;

	अगर (sample_type & PERF_SAMPLE_REGS_INTR)
		evsel.core.attr.sample_regs_पूर्णांकr = sample_regs;

	अगर (sample_type & PERF_SAMPLE_BRANCH_STACK)
		evsel.core.attr.branch_sample_type |= PERF_SAMPLE_BRANCH_HW_INDEX;

	क्रम (i = 0; i < माप(regs); i++)
		*(i + (u8 *)regs) = i & 0xfe;

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP) अणु
		sample.पढ़ो.group.nr     = 4;
		sample.पढ़ो.group.values = values;
	पूर्ण अन्यथा अणु
		sample.पढ़ो.one.value = 0x08789faeb786aa87ULL;
		sample.पढ़ो.one.id    = 99;
	पूर्ण

	sz = perf_event__sample_event_size(&sample, sample_type, पढ़ो_क्रमmat);
	bufsz = sz + 4096; /* Add a bit क्रम overrun checking */
	event = दो_स्मृति(bufsz);
	अगर (!event) अणु
		pr_debug("malloc failed\n");
		वापस -1;
	पूर्ण

	स_रखो(event, 0xff, bufsz);
	event->header.type = PERF_RECORD_SAMPLE;
	event->header.misc = 0;
	event->header.size = sz;

	err = perf_event__synthesize_sample(event, sample_type, पढ़ो_क्रमmat,
					    &sample);
	अगर (err) अणु
		pr_debug("%s failed for sample_type %#"PRIx64", error %d\n",
			 "perf_event__synthesize_sample", sample_type, err);
		जाओ out_मुक्त;
	पूर्ण

	/* The data करोes not contain 0xff so we use that to check the size */
	क्रम (i = bufsz; i > 0; i--) अणु
		अगर (*(i - 1 + (u8 *)event) != 0xff)
			अवरोध;
	पूर्ण
	अगर (i != sz) अणु
		pr_debug("Event size mismatch: actual %zu vs expected %zu\n",
			 i, sz);
		जाओ out_मुक्त;
	पूर्ण

	evsel.sample_size = __evsel__sample_size(sample_type);

	err = evsel__parse_sample(&evsel, event, &sample_out);
	अगर (err) अणु
		pr_debug("%s failed for sample_type %#"PRIx64", error %d\n",
			 "evsel__parse_sample", sample_type, err);
		जाओ out_मुक्त;
	पूर्ण

	अगर (!samples_same(&sample, &sample_out, sample_type, पढ़ो_क्रमmat)) अणु
		pr_debug("parsing failed for sample_type %#"PRIx64"\n",
			 sample_type);
		जाओ out_मुक्त;
	पूर्ण

	ret = 0;
out_मुक्त:
	मुक्त(event);
	अगर (ret && पढ़ो_क्रमmat)
		pr_debug("read_format %#"PRIx64"\n", पढ़ो_क्रमmat);
	वापस ret;
पूर्ण

/**
 * test__sample_parsing - test sample parsing.
 *
 * This function implements a test that synthesizes a sample event, parses it
 * and then checks that the parsed sample matches the original sample.  The test
 * checks sample क्रमmat bits separately and together.  If the test passes %0 is
 * वापसed, otherwise %-1 is वापसed.
 */
पूर्णांक test__sample_parsing(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	स्थिर u64 rf[] = अणु4, 5, 6, 7, 12, 13, 14, 15पूर्ण;
	u64 sample_type;
	u64 sample_regs;
	माप_प्रकार i;
	पूर्णांक err;

	/*
	 * Fail the test अगर it has not been updated when new sample क्रमmat bits
	 * were added.  Please actually update the test rather than just change
	 * the condition below.
	 */
	अगर (PERF_SAMPLE_MAX > PERF_SAMPLE_WEIGHT_STRUCT << 1) अणु
		pr_debug("sample format has changed, some new PERF_SAMPLE_ bit was introduced - test needs updating\n");
		वापस -1;
	पूर्ण

	/* Test each sample क्रमmat bit separately */
	क्रम (sample_type = 1; sample_type != PERF_SAMPLE_MAX;
	     sample_type <<= 1) अणु
		/* Test पढ़ो_क्रमmat variations */
		अगर (sample_type == PERF_SAMPLE_READ) अणु
			क्रम (i = 0; i < ARRAY_SIZE(rf); i++) अणु
				err = करो_test(sample_type, 0, rf[i]);
				अगर (err)
					वापस err;
			पूर्ण
			जारी;
		पूर्ण
		sample_regs = 0;

		अगर (sample_type == PERF_SAMPLE_REGS_USER)
			sample_regs = 0x3fff;

		अगर (sample_type == PERF_SAMPLE_REGS_INTR)
			sample_regs = 0xff0fff;

		err = करो_test(sample_type, sample_regs, 0);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Test all sample क्रमmat bits together
	 * Note: PERF_SAMPLE_WEIGHT and PERF_SAMPLE_WEIGHT_STRUCT cannot
	 *       be set simultaneously.
	 */
	sample_type = (PERF_SAMPLE_MAX - 1) & ~PERF_SAMPLE_WEIGHT;
	sample_regs = 0x3fff; /* shared yb पूर्णांकr and user regs */
	क्रम (i = 0; i < ARRAY_SIZE(rf); i++) अणु
		err = करो_test(sample_type, sample_regs, rf[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
