<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * debugfs file to track समय spent in suspend
 *
 * Copyright (c) 2011, Google, Inc.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/suspend.h>
#समावेश <linux/समय.स>

#समावेश "timekeeping_internal.h"

#घोषणा NUM_BINS 32

अटल अचिन्हित पूर्णांक sleep_समय_bin[NUM_BINS] = अणु0पूर्ण;

अटल पूर्णांक tk_debug_sleep_समय_show(काष्ठा seq_file *s, व्योम *data)
अणु
	अचिन्हित पूर्णांक bin;
	seq_माला_दो(s, "      time (secs)        count\n");
	seq_माला_दो(s, "------------------------------\n");
	क्रम (bin = 0; bin < 32; bin++) अणु
		अगर (sleep_समय_bin[bin] == 0)
			जारी;
		seq_म_लिखो(s, "%10u - %-10u %4u\n",
			bin ? 1 << (bin - 1) : 0, 1 << bin,
				sleep_समय_bin[bin]);
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(tk_debug_sleep_समय);

अटल पूर्णांक __init tk_debug_sleep_समय_init(व्योम)
अणु
	debugfs_create_file("sleep_time", 0444, शून्य, शून्य,
			    &tk_debug_sleep_समय_fops);
	वापस 0;
पूर्ण
late_initcall(tk_debug_sleep_समय_init);

व्योम tk_debug_account_sleep_समय(स्थिर काष्ठा बारpec64 *t)
अणु
	/* Cap bin index so we करोn't overflow the array */
	पूर्णांक bin = min(fls(t->tv_sec), NUM_BINS-1);

	sleep_समय_bin[bin]++;
	pm_deferred_pr_dbg("Timekeeping suspended for %lld.%03lu seconds\n",
			   (s64)t->tv_sec, t->tv_nsec / NSEC_PER_MSEC);
पूर्ण

