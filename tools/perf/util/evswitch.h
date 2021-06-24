<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (C) 2019, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
#अगर_अघोषित __PERF_EVSWITCH_H
#घोषणा __PERF_EVSWITCH_H 1

#समावेश <stdbool.h>
#समावेश <मानकपन.स>

काष्ठा evsel;
काष्ठा evlist;

काष्ठा evचयन अणु
	काष्ठा evsel *on, *off;
	स्थिर अक्षर   *on_name, *off_name;
	bool	     discarding;
	bool	     show_on_off_events;
पूर्ण;

पूर्णांक evचयन__init(काष्ठा evचयन *evचयन, काष्ठा evlist *evlist, खाता *fp);

bool evचयन__discard(काष्ठा evचयन *evचयन, काष्ठा evsel *evsel);

#घोषणा OPTS_EVSWITCH(evचयन)								  \
	OPT_STRING(0, "switch-on", &(evचयन)->on_name,				  \
		   "event", "Consider events after the ocurrence of this event"),	  \
	OPT_STRING(0, "switch-off", &(evचयन)->off_name,				  \
		   "event", "Stop considering events after the ocurrence of this event"), \
	OPT_BOOLEAN(0, "show-on-off-events", &(evचयन)->show_on_off_events,		  \
		    "Show the on/off switch events, used with --switch-on and --switch-off")

#पूर्ण_अगर /* __PERF_EVSWITCH_H */
