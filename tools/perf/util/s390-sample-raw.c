<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2019
 * Author(s): Thomas Richter <पंचांगricht@linux.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License (version 2 only)
 * as published by the Free Software Foundation.
 *
 * Architecture specअगरic trace_event function. Save event's bc000 raw data
 * to file. File name is aux.ctr.## where ## stands क्रम the CPU number the
 * sample was taken from.
 */

#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>

#समावेश <sys/स्थिति.स>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "debug.h"
#समावेश "session.h"
#समावेश "evlist.h"
#समावेश "color.h"
#समावेश "sample-raw.h"
#समावेश "s390-cpumcf-kernel.h"
#समावेश "pmu-events/pmu-events.h"

अटल माप_प्रकार ctrset_size(काष्ठा cf_ctrset_entry *set)
अणु
	वापस माप(*set) + set->ctr * माप(u64);
पूर्ण

अटल bool ctrset_valid(काष्ठा cf_ctrset_entry *set)
अणु
	वापस set->def == S390_CPUMCF_DIAG_DEF;
पूर्ण

/* CPU Measurement Counter Facility raw data is a byte stream. It is 8 byte
 * aligned and might have trailing padding bytes.
 * Display the raw data on screen.
 */
अटल bool s390_cpumcfdg_testctr(काष्ठा perf_sample *sample)
अणु
	माप_प्रकार len = sample->raw_size, offset = 0;
	अचिन्हित अक्षर *buf = sample->raw_data;
	काष्ठा cf_trailer_entry *te;
	काष्ठा cf_ctrset_entry *cep, ce;

	अगर (!len)
		वापस false;
	जबतक (offset < len) अणु
		cep = (काष्ठा cf_ctrset_entry *)(buf + offset);
		ce.def = be16_to_cpu(cep->def);
		ce.set = be16_to_cpu(cep->set);
		ce.ctr = be16_to_cpu(cep->ctr);
		ce.res1 = be16_to_cpu(cep->res1);

		अगर (!ctrset_valid(&ce) || offset + ctrset_size(&ce) > len) अणु
			/* Raw data क्रम counter sets are always multiple of 8
			 * bytes. Prepending a 4 bytes size field to the
			 * raw data block in the sample causes the perf tool
			 * to append 4 padding bytes to make the raw data part
			 * of the sample a multiple of eight bytes again.
			 *
			 * If the last entry (trailer) is 4 bytes off the raw
			 * area data end, all is good.
			 */
			अगर (len - offset - माप(*te) == 4)
				अवरोध;
			pr_err("Invalid counter set entry at %zd\n", offset);
			वापस false;
		पूर्ण
		offset += ctrset_size(&ce);
	पूर्ण
	वापस true;
पूर्ण

/* Dump event bc000 on screen, alपढ़ोy tested on correctness. */
अटल व्योम s390_cpumcfdg_dumptrail(स्थिर अक्षर *color, माप_प्रकार offset,
				    काष्ठा cf_trailer_entry *tep)
अणु
	काष्ठा cf_trailer_entry  te;

	te.flags = be64_to_cpu(tep->flags);
	te.cfvn = be16_to_cpu(tep->cfvn);
	te.csvn = be16_to_cpu(tep->csvn);
	te.cpu_speed = be32_to_cpu(tep->cpu_speed);
	te.बारtamp = be64_to_cpu(tep->बारtamp);
	te.progusage1 = be64_to_cpu(tep->progusage1);
	te.progusage2 = be64_to_cpu(tep->progusage2);
	te.progusage3 = be64_to_cpu(tep->progusage3);
	te.tod_base = be64_to_cpu(tep->tod_base);
	te.mach_type = be16_to_cpu(tep->mach_type);
	te.res1 = be16_to_cpu(tep->res1);
	te.res2 = be32_to_cpu(tep->res2);

	color_ख_लिखो(मानक_निकास, color, "    [%#08zx] Trailer:%c%c%c%c%c"
		      " Cfvn:%d Csvn:%d Speed:%d TOD:%#llx\n",
		      offset, te.घड़ी_base ? 'T' : ' ',
		      te.speed ? 'S' : ' ', te.mtda ? 'M' : ' ',
		      te.caca ? 'C' : ' ', te.lcda ? 'L' : ' ',
		      te.cfvn, te.csvn, te.cpu_speed, te.बारtamp);
	color_ख_लिखो(मानक_निकास, color, "\t\t1:%lx 2:%lx 3:%lx TOD-Base:%#llx"
		      " Type:%x\n\n",
		      te.progusage1, te.progusage2, te.progusage3,
		      te.tod_base, te.mach_type);
पूर्ण

/* Return starting number of a counter set */
अटल पूर्णांक get_counterset_start(पूर्णांक setnr)
अणु
	चयन (setnr) अणु
	हाल CPUMF_CTR_SET_BASIC:		/* Basic counter set */
		वापस 0;
	हाल CPUMF_CTR_SET_USER:		/* Problem state counter set */
		वापस 32;
	हाल CPUMF_CTR_SET_CRYPTO:		/* Crypto counter set */
		वापस 64;
	हाल CPUMF_CTR_SET_EXT:			/* Extended counter set */
		वापस 128;
	हाल CPUMF_CTR_SET_MT_DIAG:		/* Diagnostic counter set */
		वापस 448;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

/* Scan the PMU table and extract the logical name of a counter from the
 * PMU events table. Input is the counter set and counter number with in the
 * set. Conकाष्ठा the event number and use this as key. If they match वापस
 * the name of this counter.
 * If no match is found a शून्य poपूर्णांकer is वापसed.
 */
अटल स्थिर अक्षर *get_counter_name(पूर्णांक set, पूर्णांक nr, काष्ठा pmu_events_map *map)
अणु
	पूर्णांक rc, event_nr, wanted = get_counterset_start(set) + nr;

	अगर (map) अणु
		काष्ठा pmu_event *evp = map->table;

		क्रम (; evp->name || evp->event || evp->desc; ++evp) अणु
			अगर (evp->name == शून्य || evp->event == शून्य)
				जारी;
			rc = माला_पूछो(evp->event, "event=%x", &event_nr);
			अगर (rc == 1 && event_nr == wanted)
				वापस evp->name;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम s390_cpumcfdg_dump(काष्ठा perf_sample *sample)
अणु
	माप_प्रकार i, len = sample->raw_size, offset = 0;
	अचिन्हित अक्षर *buf = sample->raw_data;
	स्थिर अक्षर *color = PERF_COLOR_BLUE;
	काष्ठा cf_ctrset_entry *cep, ce;
	काष्ठा pmu_events_map *map;
	u64 *p;

	map = pmu_events_map__find();
	जबतक (offset < len) अणु
		cep = (काष्ठा cf_ctrset_entry *)(buf + offset);

		ce.def = be16_to_cpu(cep->def);
		ce.set = be16_to_cpu(cep->set);
		ce.ctr = be16_to_cpu(cep->ctr);
		ce.res1 = be16_to_cpu(cep->res1);

		अगर (!ctrset_valid(&ce)) अणु	/* Prपूर्णांक trailer */
			s390_cpumcfdg_dumptrail(color, offset,
						(काष्ठा cf_trailer_entry *)cep);
			वापस;
		पूर्ण

		color_ख_लिखो(मानक_निकास, color, "    [%#08zx] Counterset:%d"
			      " Counters:%d\n", offset, ce.set, ce.ctr);
		क्रम (i = 0, p = (u64 *)(cep + 1); i < ce.ctr; ++i, ++p) अणु
			स्थिर अक्षर *ev_name = get_counter_name(ce.set, i, map);

			color_ख_लिखो(मानक_निकास, color,
				      "\tCounter:%03d %s Value:%#018lx\n", i,
				      ev_name ?: "<unknown>", be64_to_cpu(*p));
		पूर्ण
		offset += ctrset_size(&ce);
	पूर्ण
पूर्ण

/* S390 specअगरic trace event function. Check क्रम PERF_RECORD_SAMPLE events
 * and अगर the event was triggered by a counter set diagnostic event display
 * its raw data.
 * The function is only invoked when the dump flag -D is set.
 */
व्योम evlist__s390_sample_raw(काष्ठा evlist *evlist, जोड़ perf_event *event, काष्ठा perf_sample *sample)
अणु
	काष्ठा evsel *ev_bc000;

	अगर (event->header.type != PERF_RECORD_SAMPLE)
		वापस;

	ev_bc000 = evlist__event2evsel(evlist, event);
	अगर (ev_bc000 == शून्य ||
	    ev_bc000->core.attr.config != PERF_EVENT_CPUM_CF_DIAG)
		वापस;

	/* Display raw data on screen */
	अगर (!s390_cpumcfdg_testctr(sample)) अणु
		pr_err("Invalid counter set data encountered\n");
		वापस;
	पूर्ण
	s390_cpumcfdg_dump(sample);
पूर्ण
