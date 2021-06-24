<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <stdbool.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "event.h"
#समावेश "evsel.h"
#समावेश "debug.h"
#समावेश "util/synthetic-events.h"

#समावेश "tests/tests.h"
#समावेश "arch-tests.h"

#घोषणा COMP(m) करो अणु					\
	अगर (s1->m != s2->m) अणु				\
		pr_debug("Samples differ at '"#m"'\n");	\
		वापस false;				\
	पूर्ण						\
पूर्ण जबतक (0)

अटल bool samples_same(स्थिर काष्ठा perf_sample *s1,
			 स्थिर काष्ठा perf_sample *s2,
			 u64 type)
अणु
	अगर (type & PERF_SAMPLE_WEIGHT_STRUCT)
		COMP(ins_lat);

	वापस true;
पूर्ण

अटल पूर्णांक करो_test(u64 sample_type)
अणु
	काष्ठा evsel evsel = अणु
		.needs_swap = false,
		.core = अणु
			. attr = अणु
				.sample_type = sample_type,
				.पढ़ो_क्रमmat = 0,
			पूर्ण,
		पूर्ण,
	पूर्ण;
	जोड़ perf_event *event;
	काष्ठा perf_sample sample = अणु
		.weight		= 101,
		.ins_lat        = 102,
	पूर्ण;
	काष्ठा perf_sample sample_out;
	माप_प्रकार i, sz, bufsz;
	पूर्णांक err, ret = -1;

	sz = perf_event__sample_event_size(&sample, sample_type, 0);
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

	err = perf_event__synthesize_sample(event, sample_type, 0, &sample);
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

	अगर (!samples_same(&sample, &sample_out, sample_type)) अणु
		pr_debug("parsing failed for sample_type %#"PRIx64"\n",
			 sample_type);
		जाओ out_मुक्त;
	पूर्ण

	ret = 0;
out_मुक्त:
	मुक्त(event);

	वापस ret;
पूर्ण

/**
 * test__x86_sample_parsing - test X86 specअगरic sample parsing
 *
 * This function implements a test that synthesizes a sample event, parses it
 * and then checks that the parsed sample matches the original sample. If the
 * test passes %0 is वापसed, otherwise %-1 is वापसed.
 *
 * For now, the PERF_SAMPLE_WEIGHT_STRUCT is the only X86 specअगरic sample type.
 * The test only checks the PERF_SAMPLE_WEIGHT_STRUCT type.
 */
पूर्णांक test__x86_sample_parsing(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	वापस करो_test(PERF_SAMPLE_WEIGHT_STRUCT);
पूर्ण
