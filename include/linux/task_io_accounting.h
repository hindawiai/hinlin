<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * task_io_accounting: a काष्ठाure which is used क्रम recording a single task's
 * IO statistics.
 *
 * Don't include this header file directly - it is deचिन्हित to be dragged in via
 * sched.h.
 *
 * Blame Andrew Morton क्रम all this.
 */

काष्ठा task_io_accounting अणु
#अगर_घोषित CONFIG_TASK_XACCT
	/* bytes पढ़ो */
	u64 rअक्षर;
	/*  bytes written */
	u64 wअक्षर;
	/* # of पढ़ो syscalls */
	u64 syscr;
	/* # of ग_लिखो syscalls */
	u64 syscw;
#पूर्ण_अगर /* CONFIG_TASK_XACCT */

#अगर_घोषित CONFIG_TASK_IO_ACCOUNTING
	/*
	 * The number of bytes which this task has caused to be पढ़ो from
	 * storage.
	 */
	u64 पढ़ो_bytes;

	/*
	 * The number of bytes which this task has caused, or shall cause to be
	 * written to disk.
	 */
	u64 ग_लिखो_bytes;

	/*
	 * A task can cause "negative" IO too.  If this task truncates some
	 * dirty pagecache, some IO which another task has been accounted क्रम
	 * (in its ग_लिखो_bytes) will not be happening.  We _could_ just
	 * subtract that from the truncating task's ग_लिखो_bytes, but there is
	 * inक्रमmation loss in करोing that.
	 */
	u64 cancelled_ग_लिखो_bytes;
#पूर्ण_अगर /* CONFIG_TASK_IO_ACCOUNTING */
पूर्ण;
