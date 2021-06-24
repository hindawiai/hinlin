<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/sysctl.c
 *
 * Sysctl पूर्णांकerface to sunrpc module.
 *
 * I would prefer to रेजिस्टर the sunrpc table below sys/net, but that's
 * impossible at the moment.
 */

#समावेश <linux/types.h>
#समावेश <linux/linkage.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fs.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/module.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/sunrpc/types.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/svc_xprt.h>

#समावेश "netns.h"

/*
 * Declare the debug flags here
 */
अचिन्हित पूर्णांक	rpc_debug;
EXPORT_SYMBOL_GPL(rpc_debug);

अचिन्हित पूर्णांक	nfs_debug;
EXPORT_SYMBOL_GPL(nfs_debug);

अचिन्हित पूर्णांक	nfsd_debug;
EXPORT_SYMBOL_GPL(nfsd_debug);

अचिन्हित पूर्णांक	nlm_debug;
EXPORT_SYMBOL_GPL(nlm_debug);

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)

अटल काष्ठा ctl_table_header *sunrpc_table_header;
अटल काष्ठा ctl_table sunrpc_table[];

व्योम
rpc_रेजिस्टर_sysctl(व्योम)
अणु
	अगर (!sunrpc_table_header)
		sunrpc_table_header = रेजिस्टर_sysctl_table(sunrpc_table);
पूर्ण

व्योम
rpc_unरेजिस्टर_sysctl(व्योम)
अणु
	अगर (sunrpc_table_header) अणु
		unरेजिस्टर_sysctl_table(sunrpc_table_header);
		sunrpc_table_header = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक proc_करो_xprt(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अक्षर पंचांगpbuf[256];
	sमाप_प्रकार len;

	अगर (ग_लिखो || *ppos) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण
	len = svc_prपूर्णांक_xprts(पंचांगpbuf, माप(पंचांगpbuf));
	len = memory_पढ़ो_from_buffer(buffer, *lenp, ppos, पंचांगpbuf, len);

	अगर (len < 0) अणु
		*lenp = 0;
		वापस -EINVAL;
	पूर्ण
	*lenp = len;
	वापस 0;
पूर्ण

अटल पूर्णांक
proc_करोdebug(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer, माप_प्रकार *lenp,
	     loff_t *ppos)
अणु
	अक्षर		पंचांगpbuf[20], *s = शून्य;
	अक्षर *p;
	अचिन्हित पूर्णांक	value;
	माप_प्रकार		left, len;

	अगर ((*ppos && !ग_लिखो) || !*lenp) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	left = *lenp;

	अगर (ग_लिखो) अणु
		p = buffer;
		जबतक (left && है_खाली(*p)) अणु
			left--;
			p++;
		पूर्ण
		अगर (!left)
			जाओ करोne;

		अगर (left > माप(पंचांगpbuf) - 1)
			वापस -EINVAL;
		स_नकल(पंचांगpbuf, p, left);
		पंचांगpbuf[left] = '\0';

		value = simple_म_से_दीर्घ(पंचांगpbuf, &s, 0);
		अगर (s) अणु
			left -= (s - पंचांगpbuf);
			अगर (left && !है_खाली(*s))
				वापस -EINVAL;
			जबतक (left && है_खाली(*s)) अणु
				left--;
				s++;
			पूर्ण
		पूर्ण अन्यथा
			left = 0;
		*(अचिन्हित पूर्णांक *) table->data = value;
		/* Display the RPC tasks on writing to rpc_debug */
		अगर (म_भेद(table->procname, "rpc_debug") == 0)
			rpc_show_tasks(&init_net);
	पूर्ण अन्यथा अणु
		len = प्र_लिखो(पंचांगpbuf, "0x%04x", *(अचिन्हित पूर्णांक *) table->data);
		अगर (len > left)
			len = left;
		स_नकल(buffer, पंचांगpbuf, len);
		अगर ((left -= len) > 0) अणु
			*((अक्षर *)buffer + len) = '\n';
			left--;
		पूर्ण
	पूर्ण

करोne:
	*lenp -= left;
	*ppos += *lenp;
	वापस 0;
पूर्ण


अटल काष्ठा ctl_table debug_table[] = अणु
	अणु
		.procname	= "rpc_debug",
		.data		= &rpc_debug,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोdebug
	पूर्ण,
	अणु
		.procname	= "nfs_debug",
		.data		= &nfs_debug,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोdebug
	पूर्ण,
	अणु
		.procname	= "nfsd_debug",
		.data		= &nfsd_debug,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोdebug
	पूर्ण,
	अणु
		.procname	= "nlm_debug",
		.data		= &nlm_debug,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोdebug
	पूर्ण,
	अणु
		.procname	= "transports",
		.maxlen		= 256,
		.mode		= 0444,
		.proc_handler	= proc_करो_xprt,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table sunrpc_table[] = अणु
	अणु
		.procname	= "sunrpc",
		.mode		= 0555,
		.child		= debug_table
	पूर्ण,
	अणु पूर्ण
पूर्ण;

#पूर्ण_अगर
