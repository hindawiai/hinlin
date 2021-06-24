<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		INET protocol dispatch tables.
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 * Fixes:
 *		Alan Cox	: Ahah! udp icmp errors करोn't work because
 *				  udp_err is never called!
 *		Alan Cox	: Added new fields क्रम init and पढ़ोy क्रम
 *				  proper fragmentation (_NO_ 4K limits!)
 *		Riअक्षरd Colella	: Hang on hash collision
 *		Vince Laviano	: Modअगरied inet_del_protocol() to correctly
 *				  मुख्यtain copy bit.
 */
#समावेश <linux/cache.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <net/protocol.h>

काष्ठा net_protocol __rcu *inet_protos[MAX_INET_PROTOS] __पढ़ो_mostly;
EXPORT_SYMBOL(inet_protos);
स्थिर काष्ठा net_offload __rcu *inet_offloads[MAX_INET_PROTOS] __पढ़ो_mostly;
EXPORT_SYMBOL(inet_offloads);

पूर्णांक inet_add_protocol(स्थिर काष्ठा net_protocol *prot, अचिन्हित अक्षर protocol)
अणु
	अगर (!prot->netns_ok) अणु
		pr_err("Protocol %u is not namespace aware, cannot register.\n",
			protocol);
		वापस -EINVAL;
	पूर्ण

	वापस !cmpxchg((स्थिर काष्ठा net_protocol **)&inet_protos[protocol],
			शून्य, prot) ? 0 : -1;
पूर्ण
EXPORT_SYMBOL(inet_add_protocol);

पूर्णांक inet_add_offload(स्थिर काष्ठा net_offload *prot, अचिन्हित अक्षर protocol)
अणु
	वापस !cmpxchg((स्थिर काष्ठा net_offload **)&inet_offloads[protocol],
			शून्य, prot) ? 0 : -1;
पूर्ण
EXPORT_SYMBOL(inet_add_offload);

पूर्णांक inet_del_protocol(स्थिर काष्ठा net_protocol *prot, अचिन्हित अक्षर protocol)
अणु
	पूर्णांक ret;

	ret = (cmpxchg((स्थिर काष्ठा net_protocol **)&inet_protos[protocol],
		       prot, शून्य) == prot) ? 0 : -1;

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(inet_del_protocol);

पूर्णांक inet_del_offload(स्थिर काष्ठा net_offload *prot, अचिन्हित अक्षर protocol)
अणु
	पूर्णांक ret;

	ret = (cmpxchg((स्थिर काष्ठा net_offload **)&inet_offloads[protocol],
		       prot, शून्य) == prot) ? 0 : -1;

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(inet_del_offload);
