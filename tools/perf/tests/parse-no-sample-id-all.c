<शैली गुरु>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <मानकघोष.स>

#समावेश "tests.h"

#समावेश "event.h"
#समावेश "evlist.h"
#समावेश "header.h"
#समावेश "debug.h"

अटल पूर्णांक process_event(काष्ठा evlist **pevlist, जोड़ perf_event *event)
अणु
	काष्ठा perf_sample sample;

	अगर (event->header.type == PERF_RECORD_HEADER_ATTR) अणु
		अगर (perf_event__process_attr(शून्य, event, pevlist)) अणु
			pr_debug("perf_event__process_attr failed\n");
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (event->header.type >= PERF_RECORD_USER_TYPE_START)
		वापस -1;

	अगर (!*pevlist)
		वापस -1;

	अगर (evlist__parse_sample(*pevlist, event, &sample)) अणु
		pr_debug("evlist__parse_sample failed\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_events(जोड़ perf_event **events, माप_प्रकार count)
अणु
	काष्ठा evlist *evlist = शून्य;
	पूर्णांक err = 0;
	माप_प्रकार i;

	क्रम (i = 0; i < count && !err; i++)
		err = process_event(&evlist, events[i]);

	evlist__delete(evlist);

	वापस err;
पूर्ण

काष्ठा test_attr_event अणु
	काष्ठा perf_event_header header;
	काष्ठा perf_event_attr	 attr;
	u64 id;
पूर्ण;

/**
 * test__parse_no_sample_id_all - test parsing with no sample_id_all bit set.
 *
 * This function tests parsing data produced on kernel's that करो not support the
 * sample_id_all bit.  Without the sample_id_all bit, non-sample events (such as
 * mmap events) करो not have an id sample appended, and consequently logic
 * deचिन्हित to determine the id will not work.  That हाल happens when there is
 * more than one selected event, so this test processes three events: 2
 * attributes representing the selected events and one mmap event.
 *
 * Return: %0 on success, %-1 अगर the test fails.
 */
पूर्णांक test__parse_no_sample_id_all(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err;

	काष्ठा test_attr_event event1 = अणु
		.header = अणु
			.type = PERF_RECORD_HEADER_ATTR,
			.size = माप(काष्ठा test_attr_event),
		पूर्ण,
		.id = 1,
	पूर्ण;
	काष्ठा test_attr_event event2 = अणु
		.header = अणु
			.type = PERF_RECORD_HEADER_ATTR,
			.size = माप(काष्ठा test_attr_event),
		पूर्ण,
		.id = 2,
	पूर्ण;
	काष्ठा perf_record_mmap event3 = अणु
		.header = अणु
			.type = PERF_RECORD_MMAP,
			.size = माप(काष्ठा perf_record_mmap),
		पूर्ण,
	पूर्ण;
	जोड़ perf_event *events[] = अणु
		(जोड़ perf_event *)&event1,
		(जोड़ perf_event *)&event2,
		(जोड़ perf_event *)&event3,
	पूर्ण;

	err = process_events(events, ARRAY_SIZE(events));
	अगर (err)
		वापस -1;

	वापस 0;
पूर्ण
