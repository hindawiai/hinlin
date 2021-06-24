<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  cpufreq-bench CPUFreq microbenchmark
 *
 *  Copyright (C) 2008 Christian Kornacker <ckornacker@suse.de>
 */

#समावेश "parse.h"

दीर्घ दीर्घ get_समय();

पूर्णांक set_cpufreq_governor(अक्षर *governor, अचिन्हित पूर्णांक cpu);
पूर्णांक set_cpu_affinity(अचिन्हित पूर्णांक cpu);
पूर्णांक set_process_priority(पूर्णांक priority);

व्योम prepare_user(स्थिर काष्ठा config *config);
व्योम prepare_प्रणाली(स्थिर काष्ठा config *config);
