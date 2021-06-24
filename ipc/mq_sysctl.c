<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2007 IBM Corporation
 *
 *  Author: Cedric Le Goater <clg@fr.ibm.com>
 */

#समावेश <linux/nsproxy.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/sysctl.h>

#अगर_घोषित CONFIG_PROC_SYSCTL
अटल व्योम *get_mq(काष्ठा ctl_table *table)
अणु
	अक्षर *which = table->data;
	काष्ठा ipc_namespace *ipc_ns = current->nsproxy->ipc_ns;
	which = (which - (अक्षर *)&init_ipc_ns) + (अक्षर *)ipc_ns;
	वापस which;
पूर्ण

अटल पूर्णांक proc_mq_करोपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table mq_table;
	स_नकल(&mq_table, table, माप(mq_table));
	mq_table.data = get_mq(table);

	वापस proc_करोपूर्णांकvec(&mq_table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल पूर्णांक proc_mq_करोपूर्णांकvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table mq_table;
	स_नकल(&mq_table, table, माप(mq_table));
	mq_table.data = get_mq(table);

	वापस proc_करोपूर्णांकvec_minmax(&mq_table, ग_लिखो, buffer,
					lenp, ppos);
पूर्ण
#अन्यथा
#घोषणा proc_mq_करोपूर्णांकvec शून्य
#घोषणा proc_mq_करोपूर्णांकvec_minmax शून्य
#पूर्ण_अगर

अटल पूर्णांक msg_max_limit_min = MIN_MSGMAX;
अटल पूर्णांक msg_max_limit_max = HARD_MSGMAX;

अटल पूर्णांक msg_maxsize_limit_min = MIN_MSGSIZEMAX;
अटल पूर्णांक msg_maxsize_limit_max = HARD_MSGSIZEMAX;

अटल काष्ठा ctl_table mq_sysctls[] = अणु
	अणु
		.procname	= "queues_max",
		.data		= &init_ipc_ns.mq_queues_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_mq_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "msg_max",
		.data		= &init_ipc_ns.mq_msg_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_mq_करोपूर्णांकvec_minmax,
		.extra1		= &msg_max_limit_min,
		.extra2		= &msg_max_limit_max,
	पूर्ण,
	अणु
		.procname	= "msgsize_max",
		.data		= &init_ipc_ns.mq_msgsize_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_mq_करोपूर्णांकvec_minmax,
		.extra1		= &msg_maxsize_limit_min,
		.extra2		= &msg_maxsize_limit_max,
	पूर्ण,
	अणु
		.procname	= "msg_default",
		.data		= &init_ipc_ns.mq_msg_शेष,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_mq_करोपूर्णांकvec_minmax,
		.extra1		= &msg_max_limit_min,
		.extra2		= &msg_max_limit_max,
	पूर्ण,
	अणु
		.procname	= "msgsize_default",
		.data		= &init_ipc_ns.mq_msgsize_शेष,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_mq_करोपूर्णांकvec_minmax,
		.extra1		= &msg_maxsize_limit_min,
		.extra2		= &msg_maxsize_limit_max,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table mq_sysctl_dir[] = अणु
	अणु
		.procname	= "mqueue",
		.mode		= 0555,
		.child		= mq_sysctls,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table mq_sysctl_root[] = अणु
	अणु
		.procname	= "fs",
		.mode		= 0555,
		.child		= mq_sysctl_dir,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा ctl_table_header *mq_रेजिस्टर_sysctl_table(व्योम)
अणु
	वापस रेजिस्टर_sysctl_table(mq_sysctl_root);
पूर्ण
