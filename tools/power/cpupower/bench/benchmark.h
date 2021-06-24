<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  cpufreq-bench CPUFreq microbenchmark
 *
 *  Copyright (C) 2008 Christian Kornacker <ckornacker@suse.de>
 */

/* load loop, this schould take about 1 to 2ms to complete */
#घोषणा ROUNDS(x) अणुअचिन्हित पूर्णांक rcnt;			       \
		क्रम (rcnt = 0; rcnt < x*1000; rcnt++) अणु \
			(व्योम)(((पूर्णांक)(घात(rcnt, rcnt) * \
				      वर्ग_मूल(rcnt*7230970)) ^ 7230716) ^ \
				      (पूर्णांक)atan2(rcnt, rcnt));	       \
		पूर्ण पूर्ण							\


व्योम start_benchmark(काष्ठा config *config);
