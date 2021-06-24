<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sysctl operations क्रम Coda fileप्रणाली
 * Original version: (C) 1996 P. Braam and M. Callahan
 * Rewritten क्रम Linux 2.1. (C) 1997 Carnegie Mellon University
 * 
 * Carnegie Mellon encourages users to contribute improvements to
 * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).
 */

#समावेश <linux/sysctl.h>

#समावेश "coda_int.h"

अटल काष्ठा ctl_table_header *fs_table_header;

अटल काष्ठा ctl_table coda_table[] = अणु
	अणु
		.procname	= "timeout",
		.data		= &coda_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "hard",
		.data		= &coda_hard,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "fake_statfs",
		.data		= &coda_fake_statfs,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0600,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table fs_table[] = अणु
	अणु
		.procname	= "coda",
		.mode		= 0555,
		.child		= coda_table
	पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम coda_sysctl_init(व्योम)
अणु
	अगर ( !fs_table_header )
		fs_table_header = रेजिस्टर_sysctl_table(fs_table);
पूर्ण

व्योम coda_sysctl_clean(व्योम)
अणु
	अगर ( fs_table_header ) अणु
		unरेजिस्टर_sysctl_table(fs_table_header);
		fs_table_header = शून्य;
	पूर्ण
पूर्ण
