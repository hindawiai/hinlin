<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (C) 2019, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>

#समावेश "evswitch.h"
#समावेश "evlist.h"

bool evचयन__discard(काष्ठा evचयन *evचयन, काष्ठा evsel *evsel)
अणु
	अगर (evचयन->on && evचयन->discarding) अणु
		अगर (evचयन->on != evsel)
			वापस true;

		evचयन->discarding = false;

		अगर (!evचयन->show_on_off_events)
			वापस true;

		वापस false;
	पूर्ण

	अगर (evचयन->off && !evचयन->discarding) अणु
		अगर (evचयन->off != evsel)
			वापस false;

		evचयन->discarding = true;

		अगर (!evचयन->show_on_off_events)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक evचयन__ख_लिखो_enoent(खाता *fp, स्थिर अक्षर *evtype, स्थिर अक्षर *evname)
अणु
	पूर्णांक prपूर्णांकed = ख_लिखो(fp, "ERROR: switch-%s event not found (%s)\n", evtype, evname);

	वापस prपूर्णांकed += ख_लिखो(fp, "HINT:  use 'perf evlist' to see the available event names\n");
पूर्ण

पूर्णांक evचयन__init(काष्ठा evचयन *evचयन, काष्ठा evlist *evlist, खाता *fp)
अणु
	अगर (evचयन->on_name) अणु
		evचयन->on = evlist__find_evsel_by_str(evlist, evचयन->on_name);
		अगर (evचयन->on == शून्य) अणु
			evचयन__ख_लिखो_enoent(fp, "on", evचयन->on_name);
			वापस -ENOENT;
		पूर्ण
		evचयन->discarding = true;
	पूर्ण

	अगर (evचयन->off_name) अणु
		evचयन->off = evlist__find_evsel_by_str(evlist, evचयन->off_name);
		अगर (evचयन->off == शून्य) अणु
			evचयन__ख_लिखो_enoent(fp, "off", evचयन->off_name);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
