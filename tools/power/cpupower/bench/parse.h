<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  cpufreq-bench CPUFreq microbenchmark
 *
 *  Copyright (C) 2008 Christian Kornacker <ckornacker@suse.de>
 */

/* काष्ठा that holds the required config parameters */
काष्ठा config
अणु
	दीर्घ sleep;		/* sleep समय in तगs */
	दीर्घ load;		/* load समय in तगs */
	दीर्घ sleep_step;	/* समय value which changes the
				 * sleep समय after every round in तगs */
	दीर्घ load_step;		/* समय value which changes the
				 * load समय after every round in तगs */
	अचिन्हित पूर्णांक cycles;	/* calculation cycles with the same sleep/load समय */
	अचिन्हित पूर्णांक rounds;	/* calculation rounds with iterated sleep/load समय */
	अचिन्हित पूर्णांक cpu;	/* cpu क्रम which the affinity is set */
	अक्षर governor[15];	/* cpufreq governor */
	क्रमागत sched_prio		/* possible scheduler priorities */
	अणु
		SCHED_ERR = -1,
		SCHED_HIGH,
		SCHED_DEFAULT,
		SCHED_LOW
	पूर्ण prio;

	अचिन्हित पूर्णांक verbose;	/* verbose output */
	खाता *output;		/* logfile */
	अक्षर *output_filename;	/* logfile name, must be मुक्तd at the end
				   अगर output != शून्य and output != मानक_निकास*/
पूर्ण;

क्रमागत sched_prio string_to_prio(स्थिर अक्षर *str);

खाता *prepare_output(स्थिर अक्षर *dir);

पूर्णांक prepare_config(स्थिर अक्षर *path, काष्ठा config *config);
काष्ठा config *prepare_शेष_config();

