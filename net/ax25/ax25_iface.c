<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

अटल काष्ठा ax25_protocol *protocol_list;
अटल DEFINE_RWLOCK(protocol_list_lock);

अटल HLIST_HEAD(ax25_linkfail_list);
अटल DEFINE_SPINLOCK(linkfail_lock);

अटल काष्ठा listen_काष्ठा अणु
	काष्ठा listen_काष्ठा *next;
	ax25_address  callsign;
	काष्ठा net_device *dev;
पूर्ण *listen_list = शून्य;
अटल DEFINE_SPINLOCK(listen_lock);

/*
 * Do not रेजिस्टर the पूर्णांकernal protocols AX25_P_TEXT, AX25_P_SEGMENT,
 * AX25_P_IP or AX25_P_ARP ...
 */
व्योम ax25_रेजिस्टर_pid(काष्ठा ax25_protocol *ap)
अणु
	ग_लिखो_lock_bh(&protocol_list_lock);
	ap->next = protocol_list;
	protocol_list = ap;
	ग_लिखो_unlock_bh(&protocol_list_lock);
पूर्ण

EXPORT_SYMBOL_GPL(ax25_रेजिस्टर_pid);

व्योम ax25_protocol_release(अचिन्हित पूर्णांक pid)
अणु
	काष्ठा ax25_protocol *protocol;

	ग_लिखो_lock_bh(&protocol_list_lock);
	protocol = protocol_list;
	अगर (protocol == शून्य)
		जाओ out;

	अगर (protocol->pid == pid) अणु
		protocol_list = protocol->next;
		जाओ out;
	पूर्ण

	जबतक (protocol != शून्य && protocol->next != शून्य) अणु
		अगर (protocol->next->pid == pid) अणु
			protocol->next = protocol->next->next;
			जाओ out;
		पूर्ण

		protocol = protocol->next;
	पूर्ण
out:
	ग_लिखो_unlock_bh(&protocol_list_lock);
पूर्ण

EXPORT_SYMBOL(ax25_protocol_release);

व्योम ax25_linkfail_रेजिस्टर(काष्ठा ax25_linkfail *lf)
अणु
	spin_lock_bh(&linkfail_lock);
	hlist_add_head(&lf->lf_node, &ax25_linkfail_list);
	spin_unlock_bh(&linkfail_lock);
पूर्ण

EXPORT_SYMBOL(ax25_linkfail_रेजिस्टर);

व्योम ax25_linkfail_release(काष्ठा ax25_linkfail *lf)
अणु
	spin_lock_bh(&linkfail_lock);
	hlist_del_init(&lf->lf_node);
	spin_unlock_bh(&linkfail_lock);
पूर्ण

EXPORT_SYMBOL(ax25_linkfail_release);

पूर्णांक ax25_listen_रेजिस्टर(ax25_address *callsign, काष्ठा net_device *dev)
अणु
	काष्ठा listen_काष्ठा *listen;

	अगर (ax25_listen_mine(callsign, dev))
		वापस 0;

	अगर ((listen = kदो_स्मृति(माप(*listen), GFP_ATOMIC)) == शून्य)
		वापस -ENOMEM;

	listen->callsign = *callsign;
	listen->dev      = dev;

	spin_lock_bh(&listen_lock);
	listen->next = listen_list;
	listen_list  = listen;
	spin_unlock_bh(&listen_lock);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(ax25_listen_रेजिस्टर);

व्योम ax25_listen_release(ax25_address *callsign, काष्ठा net_device *dev)
अणु
	काष्ठा listen_काष्ठा *s, *listen;

	spin_lock_bh(&listen_lock);
	listen = listen_list;
	अगर (listen == शून्य) अणु
		spin_unlock_bh(&listen_lock);
		वापस;
	पूर्ण

	अगर (ax25cmp(&listen->callsign, callsign) == 0 && listen->dev == dev) अणु
		listen_list = listen->next;
		spin_unlock_bh(&listen_lock);
		kमुक्त(listen);
		वापस;
	पूर्ण

	जबतक (listen != शून्य && listen->next != शून्य) अणु
		अगर (ax25cmp(&listen->next->callsign, callsign) == 0 && listen->next->dev == dev) अणु
			s = listen->next;
			listen->next = listen->next->next;
			spin_unlock_bh(&listen_lock);
			kमुक्त(s);
			वापस;
		पूर्ण

		listen = listen->next;
	पूर्ण
	spin_unlock_bh(&listen_lock);
पूर्ण

EXPORT_SYMBOL(ax25_listen_release);

पूर्णांक (*ax25_protocol_function(अचिन्हित पूर्णांक pid))(काष्ठा sk_buff *, ax25_cb *)
अणु
	पूर्णांक (*res)(काष्ठा sk_buff *, ax25_cb *) = शून्य;
	काष्ठा ax25_protocol *protocol;

	पढ़ो_lock(&protocol_list_lock);
	क्रम (protocol = protocol_list; protocol != शून्य; protocol = protocol->next)
		अगर (protocol->pid == pid) अणु
			res = protocol->func;
			अवरोध;
		पूर्ण
	पढ़ो_unlock(&protocol_list_lock);

	वापस res;
पूर्ण

पूर्णांक ax25_listen_mine(ax25_address *callsign, काष्ठा net_device *dev)
अणु
	काष्ठा listen_काष्ठा *listen;

	spin_lock_bh(&listen_lock);
	क्रम (listen = listen_list; listen != शून्य; listen = listen->next)
		अगर (ax25cmp(&listen->callsign, callsign) == 0 &&
		    (listen->dev == dev || listen->dev == शून्य)) अणु
			spin_unlock_bh(&listen_lock);
			वापस 1;
	पूर्ण
	spin_unlock_bh(&listen_lock);

	वापस 0;
पूर्ण

व्योम ax25_link_failed(ax25_cb *ax25, पूर्णांक reason)
अणु
	काष्ठा ax25_linkfail *lf;

	spin_lock_bh(&linkfail_lock);
	hlist_क्रम_each_entry(lf, &ax25_linkfail_list, lf_node)
		lf->func(ax25, reason);
	spin_unlock_bh(&linkfail_lock);
पूर्ण

पूर्णांक ax25_protocol_is_रेजिस्टरed(अचिन्हित पूर्णांक pid)
अणु
	काष्ठा ax25_protocol *protocol;
	पूर्णांक res = 0;

	पढ़ो_lock_bh(&protocol_list_lock);
	क्रम (protocol = protocol_list; protocol != शून्य; protocol = protocol->next)
		अगर (protocol->pid == pid) अणु
			res = 1;
			अवरोध;
		पूर्ण
	पढ़ो_unlock_bh(&protocol_list_lock);

	वापस res;
पूर्ण
