<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2007
 *
 *  Author: Eric Biederman <ebiederm@xmision.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/uts.h>
#समावेश <linux/utsname.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/रुको.h>
#समावेश <linux/rwsem.h>

#अगर_घोषित CONFIG_PROC_SYSCTL

अटल व्योम *get_uts(काष्ठा ctl_table *table)
अणु
	अक्षर *which = table->data;
	काष्ठा uts_namespace *uts_ns;

	uts_ns = current->nsproxy->uts_ns;
	which = (which - (अक्षर *)&init_uts_ns) + (अक्षर *)uts_ns;

	वापस which;
पूर्ण

/*
 *	Special हाल of करोstring क्रम the UTS काष्ठाure. This has locks
 *	to observe. Should this be in kernel/sys.c ????
 */
अटल पूर्णांक proc_करो_uts_string(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table uts_table;
	पूर्णांक r;
	अक्षर पंचांगp_data[__NEW_UTS_LEN + 1];

	स_नकल(&uts_table, table, माप(uts_table));
	uts_table.data = पंचांगp_data;

	/*
	 * Buffer the value in पंचांगp_data so that proc_करोstring() can be called
	 * without holding any locks.
	 * We also need to पढ़ो the original value in the ग_लिखो==1 हाल to
	 * support partial ग_लिखोs.
	 */
	करोwn_पढ़ो(&uts_sem);
	स_नकल(पंचांगp_data, get_uts(table), माप(पंचांगp_data));
	up_पढ़ो(&uts_sem);
	r = proc_करोstring(&uts_table, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो) अणु
		/*
		 * Write back the new value.
		 * Note that, since we dropped uts_sem, the result can
		 * theoretically be incorrect अगर there are two parallel ग_लिखोs
		 * at non-zero offsets to the same sysctl.
		 */
		करोwn_ग_लिखो(&uts_sem);
		स_नकल(get_uts(table), पंचांगp_data, माप(पंचांगp_data));
		up_ग_लिखो(&uts_sem);
		proc_sys_poll_notअगरy(table->poll);
	पूर्ण

	वापस r;
पूर्ण
#अन्यथा
#घोषणा proc_करो_uts_string शून्य
#पूर्ण_अगर

अटल DEFINE_CTL_TABLE_POLL(hostname_poll);
अटल DEFINE_CTL_TABLE_POLL(करोमुख्यname_poll);

अटल काष्ठा ctl_table uts_kern_table[] = अणु
	अणु
		.procname	= "ostype",
		.data		= init_uts_ns.name.sysname,
		.maxlen		= माप(init_uts_ns.name.sysname),
		.mode		= 0444,
		.proc_handler	= proc_करो_uts_string,
	पूर्ण,
	अणु
		.procname	= "osrelease",
		.data		= init_uts_ns.name.release,
		.maxlen		= माप(init_uts_ns.name.release),
		.mode		= 0444,
		.proc_handler	= proc_करो_uts_string,
	पूर्ण,
	अणु
		.procname	= "version",
		.data		= init_uts_ns.name.version,
		.maxlen		= माप(init_uts_ns.name.version),
		.mode		= 0444,
		.proc_handler	= proc_करो_uts_string,
	पूर्ण,
	अणु
		.procname	= "hostname",
		.data		= init_uts_ns.name.nodename,
		.maxlen		= माप(init_uts_ns.name.nodename),
		.mode		= 0644,
		.proc_handler	= proc_करो_uts_string,
		.poll		= &hostname_poll,
	पूर्ण,
	अणु
		.procname	= "domainname",
		.data		= init_uts_ns.name.करोमुख्यname,
		.maxlen		= माप(init_uts_ns.name.करोमुख्यname),
		.mode		= 0644,
		.proc_handler	= proc_करो_uts_string,
		.poll		= &करोमुख्यname_poll,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table uts_root_table[] = अणु
	अणु
		.procname	= "kernel",
		.mode		= 0555,
		.child		= uts_kern_table,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PROC_SYSCTL
/*
 * Notअगरy userspace about a change in a certain entry of uts_kern_table,
 * identअगरied by the parameter proc.
 */
व्योम uts_proc_notअगरy(क्रमागत uts_proc proc)
अणु
	काष्ठा ctl_table *table = &uts_kern_table[proc];

	proc_sys_poll_notअगरy(table->poll);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init utsname_sysctl_init(व्योम)
अणु
	रेजिस्टर_sysctl_table(uts_root_table);
	वापस 0;
पूर्ण

device_initcall(utsname_sysctl_init);
