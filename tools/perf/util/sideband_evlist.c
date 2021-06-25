<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "util/debug.h"
#समावेश "util/evlist.h"
#समावेश "util/evsel.h"
#समावेश "util/mmap.h"
#समावेश "util/perf_api_probe.h"
#समावेश <perf/mmap.h>
#समावेश <linux/perf_event.h>
#समावेश <सीमा.स>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <stdbool.h>

पूर्णांक evlist__add_sb_event(काष्ठा evlist *evlist, काष्ठा perf_event_attr *attr,
			 evsel__sb_cb_t cb, व्योम *data)
अणु
	काष्ठा evsel *evsel;

	अगर (!attr->sample_id_all) अणु
		pr_warning("enabling sample_id_all for all side band events\n");
		attr->sample_id_all = 1;
	पूर्ण

	evsel = evsel__new_idx(attr, evlist->core.nr_entries);
	अगर (!evsel)
		वापस -1;

	evsel->side_band.cb = cb;
	evsel->side_band.data = data;
	evlist__add(evlist, evsel);
	वापस 0;
पूर्ण

अटल व्योम *perf_evlist__poll_thपढ़ो(व्योम *arg)
अणु
	काष्ठा evlist *evlist = arg;
	bool draining = false;
	पूर्णांक i, करोne = 0;
	/*
	 * In order to पढ़ो symbols from other namespaces perf to needs to call
	 * setns(2).  This isn't permitted अगर the काष्ठा_fs has multiple users.
	 * unshare(2) the fs so that we may जारी to setns पूर्णांकo namespaces
	 * that we're observing when, क्रम instance, पढ़ोing the build-ids at
	 * the end of a 'perf record' session.
	 */
	unshare(CLONE_FS);

	जबतक (!करोne) अणु
		bool got_data = false;

		अगर (evlist->thपढ़ो.करोne)
			draining = true;

		अगर (!draining)
			evlist__poll(evlist, 1000);

		क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
			काष्ठा mmap *map = &evlist->mmap[i];
			जोड़ perf_event *event;

			अगर (perf_mmap__पढ़ो_init(&map->core))
				जारी;
			जबतक ((event = perf_mmap__पढ़ो_event(&map->core)) != शून्य) अणु
				काष्ठा evsel *evsel = evlist__event2evsel(evlist, event);

				अगर (evsel && evsel->side_band.cb)
					evsel->side_band.cb(event, evsel->side_band.data);
				अन्यथा
					pr_warning("cannot locate proper evsel for the side band event\n");

				perf_mmap__consume(&map->core);
				got_data = true;
			पूर्ण
			perf_mmap__पढ़ो_करोne(&map->core);
		पूर्ण

		अगर (draining && !got_data)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम evlist__set_cb(काष्ठा evlist *evlist, evsel__sb_cb_t cb, व्योम *data)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		evsel->core.attr.sample_id_all    = 1;
		evsel->core.attr.watermark        = 1;
		evsel->core.attr.wakeup_watermark = 1;
		evsel->side_band.cb   = cb;
		evsel->side_band.data = data;
      पूर्ण
पूर्ण

पूर्णांक evlist__start_sb_thपढ़ो(काष्ठा evlist *evlist, काष्ठा target *target)
अणु
	काष्ठा evsel *counter;

	अगर (!evlist)
		वापस 0;

	अगर (evlist__create_maps(evlist, target))
		जाओ out_delete_evlist;

	अगर (evlist->core.nr_entries > 1) अणु
		bool can_sample_identअगरier = perf_can_sample_identअगरier();

		evlist__क्रम_each_entry(evlist, counter)
			evsel__set_sample_id(counter, can_sample_identअगरier);

		evlist__set_id_pos(evlist);
	पूर्ण

	evlist__क्रम_each_entry(evlist, counter) अणु
		अगर (evsel__खोलो(counter, evlist->core.cpus, evlist->core.thपढ़ोs) < 0)
			जाओ out_delete_evlist;
	पूर्ण

	अगर (evlist__mmap(evlist, अच_पूर्णांक_उच्च))
		जाओ out_delete_evlist;

	evlist__क्रम_each_entry(evlist, counter) अणु
		अगर (evsel__enable(counter))
			जाओ out_delete_evlist;
	पूर्ण

	evlist->thपढ़ो.करोne = 0;
	अगर (pthपढ़ो_create(&evlist->thपढ़ो.th, शून्य, perf_evlist__poll_thपढ़ो, evlist))
		जाओ out_delete_evlist;

	वापस 0;

out_delete_evlist:
	evlist__delete(evlist);
	evlist = शून्य;
	वापस -1;
पूर्ण

व्योम evlist__stop_sb_thपढ़ो(काष्ठा evlist *evlist)
अणु
	अगर (!evlist)
		वापस;
	evlist->thपढ़ो.करोne = 1;
	pthपढ़ो_join(evlist->thपढ़ो.th, शून्य);
	evlist__delete(evlist);
पूर्ण
