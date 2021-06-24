<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		PF_INET6 protocol dispatch tables.
 *
 * Authors:	Pedro Roque	<roque@di.fc.ul.pt>
 */

/*
 *      Changes:
 *
 *      Vince Laviano (vince@cs.stanक्रमd.edu)       16 May 2001
 *      - Removed unused variable 'inet6_protocol_base'
 *      - Modअगरied inet6_del_protocol() to correctly मुख्यtain copy bit.
 */
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <net/protocol.h>

#अगर IS_ENABLED(CONFIG_IPV6)
काष्ठा inet6_protocol __rcu *inet6_protos[MAX_INET_PROTOS] __पढ़ो_mostly;
EXPORT_SYMBOL(inet6_protos);

पूर्णांक inet6_add_protocol(स्थिर काष्ठा inet6_protocol *prot, अचिन्हित अक्षर protocol)
अणु
	वापस !cmpxchg((स्थिर काष्ठा inet6_protocol **)&inet6_protos[protocol],
			शून्य, prot) ? 0 : -1;
पूर्ण
EXPORT_SYMBOL(inet6_add_protocol);

पूर्णांक inet6_del_protocol(स्थिर काष्ठा inet6_protocol *prot, अचिन्हित अक्षर protocol)
अणु
	पूर्णांक ret;

	ret = (cmpxchg((स्थिर काष्ठा inet6_protocol **)&inet6_protos[protocol],
		       prot, शून्य) == prot) ? 0 : -1;

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(inet6_del_protocol);
#पूर्ण_अगर

स्थिर काष्ठा net_offload __rcu *inet6_offloads[MAX_INET_PROTOS] __पढ़ो_mostly;
EXPORT_SYMBOL(inet6_offloads);

पूर्णांक inet6_add_offload(स्थिर काष्ठा net_offload *prot, अचिन्हित अक्षर protocol)
अणु
	वापस !cmpxchg((स्थिर काष्ठा net_offload **)&inet6_offloads[protocol],
			शून्य, prot) ? 0 : -1;
पूर्ण
EXPORT_SYMBOL(inet6_add_offload);

पूर्णांक inet6_del_offload(स्थिर काष्ठा net_offload *prot, अचिन्हित अक्षर protocol)
अणु
	पूर्णांक ret;

	ret = (cmpxchg((स्थिर काष्ठा net_offload **)&inet6_offloads[protocol],
		       prot, शून्य) == prot) ? 0 : -1;

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(inet6_del_offload);
