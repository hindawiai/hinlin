<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Steven Whitehouse GW7RRM (stevew@acm.org)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
 * Copyright (C) Hans-Joachim Hetscher DD8NE (dd8ne@bnv-bamberg.de)
 * Copyright (C) Frederic Rible F1OAT (frible@teaser.fr)
 */

#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/समयr.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>

अटल ax25_route *ax25_route_list;
DEFINE_RWLOCK(ax25_route_lock);

व्योम ax25_rt_device_करोwn(काष्ठा net_device *dev)
अणु
	ax25_route *s, *t, *ax25_rt;

	ग_लिखो_lock_bh(&ax25_route_lock);
	ax25_rt = ax25_route_list;
	जबतक (ax25_rt != शून्य) अणु
		s       = ax25_rt;
		ax25_rt = ax25_rt->next;

		अगर (s->dev == dev) अणु
			अगर (ax25_route_list == s) अणु
				ax25_route_list = s->next;
				kमुक्त(s->digipeat);
				kमुक्त(s);
			पूर्ण अन्यथा अणु
				क्रम (t = ax25_route_list; t != शून्य; t = t->next) अणु
					अगर (t->next == s) अणु
						t->next = s->next;
						kमुक्त(s->digipeat);
						kमुक्त(s);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_bh(&ax25_route_lock);
पूर्ण

अटल पूर्णांक __must_check ax25_rt_add(काष्ठा ax25_routes_काष्ठा *route)
अणु
	ax25_route *ax25_rt;
	ax25_dev *ax25_dev;
	पूर्णांक i;

	अगर ((ax25_dev = ax25_addr_ax25dev(&route->port_addr)) == शून्य)
		वापस -EINVAL;
	अगर (route->digi_count > AX25_MAX_DIGIS)
		वापस -EINVAL;

	ग_लिखो_lock_bh(&ax25_route_lock);

	ax25_rt = ax25_route_list;
	जबतक (ax25_rt != शून्य) अणु
		अगर (ax25cmp(&ax25_rt->callsign, &route->dest_addr) == 0 &&
			    ax25_rt->dev == ax25_dev->dev) अणु
			kमुक्त(ax25_rt->digipeat);
			ax25_rt->digipeat = शून्य;
			अगर (route->digi_count != 0) अणु
				अगर ((ax25_rt->digipeat = kदो_स्मृति(माप(ax25_digi), GFP_ATOMIC)) == शून्य) अणु
					ग_लिखो_unlock_bh(&ax25_route_lock);
					वापस -ENOMEM;
				पूर्ण
				ax25_rt->digipeat->lastrepeat = -1;
				ax25_rt->digipeat->ndigi      = route->digi_count;
				क्रम (i = 0; i < route->digi_count; i++) अणु
					ax25_rt->digipeat->repeated[i] = 0;
					ax25_rt->digipeat->calls[i]    = route->digi_addr[i];
				पूर्ण
			पूर्ण
			ग_लिखो_unlock_bh(&ax25_route_lock);
			वापस 0;
		पूर्ण
		ax25_rt = ax25_rt->next;
	पूर्ण

	अगर ((ax25_rt = kदो_स्मृति(माप(ax25_route), GFP_ATOMIC)) == शून्य) अणु
		ग_लिखो_unlock_bh(&ax25_route_lock);
		वापस -ENOMEM;
	पूर्ण

	refcount_set(&ax25_rt->refcount, 1);
	ax25_rt->callsign     = route->dest_addr;
	ax25_rt->dev          = ax25_dev->dev;
	ax25_rt->digipeat     = शून्य;
	ax25_rt->ip_mode      = ' ';
	अगर (route->digi_count != 0) अणु
		अगर ((ax25_rt->digipeat = kदो_स्मृति(माप(ax25_digi), GFP_ATOMIC)) == शून्य) अणु
			ग_लिखो_unlock_bh(&ax25_route_lock);
			kमुक्त(ax25_rt);
			वापस -ENOMEM;
		पूर्ण
		ax25_rt->digipeat->lastrepeat = -1;
		ax25_rt->digipeat->ndigi      = route->digi_count;
		क्रम (i = 0; i < route->digi_count; i++) अणु
			ax25_rt->digipeat->repeated[i] = 0;
			ax25_rt->digipeat->calls[i]    = route->digi_addr[i];
		पूर्ण
	पूर्ण
	ax25_rt->next   = ax25_route_list;
	ax25_route_list = ax25_rt;
	ग_लिखो_unlock_bh(&ax25_route_lock);

	वापस 0;
पूर्ण

व्योम __ax25_put_route(ax25_route *ax25_rt)
अणु
	kमुक्त(ax25_rt->digipeat);
	kमुक्त(ax25_rt);
पूर्ण

अटल पूर्णांक ax25_rt_del(काष्ठा ax25_routes_काष्ठा *route)
अणु
	ax25_route *s, *t, *ax25_rt;
	ax25_dev *ax25_dev;

	अगर ((ax25_dev = ax25_addr_ax25dev(&route->port_addr)) == शून्य)
		वापस -EINVAL;

	ग_लिखो_lock_bh(&ax25_route_lock);

	ax25_rt = ax25_route_list;
	जबतक (ax25_rt != शून्य) अणु
		s       = ax25_rt;
		ax25_rt = ax25_rt->next;
		अगर (s->dev == ax25_dev->dev &&
		    ax25cmp(&route->dest_addr, &s->callsign) == 0) अणु
			अगर (ax25_route_list == s) अणु
				ax25_route_list = s->next;
				ax25_put_route(s);
			पूर्ण अन्यथा अणु
				क्रम (t = ax25_route_list; t != शून्य; t = t->next) अणु
					अगर (t->next == s) अणु
						t->next = s->next;
						ax25_put_route(s);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_bh(&ax25_route_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ax25_rt_opt(काष्ठा ax25_route_opt_काष्ठा *rt_option)
अणु
	ax25_route *ax25_rt;
	ax25_dev *ax25_dev;
	पूर्णांक err = 0;

	अगर ((ax25_dev = ax25_addr_ax25dev(&rt_option->port_addr)) == शून्य)
		वापस -EINVAL;

	ग_लिखो_lock_bh(&ax25_route_lock);

	ax25_rt = ax25_route_list;
	जबतक (ax25_rt != शून्य) अणु
		अगर (ax25_rt->dev == ax25_dev->dev &&
		    ax25cmp(&rt_option->dest_addr, &ax25_rt->callsign) == 0) अणु
			चयन (rt_option->cmd) अणु
			हाल AX25_SET_RT_IPMODE:
				चयन (rt_option->arg) अणु
				हाल ' ':
				हाल 'D':
				हाल 'V':
					ax25_rt->ip_mode = rt_option->arg;
					अवरोध;
				शेष:
					err = -EINVAL;
					जाओ out;
				पूर्ण
				अवरोध;
			शेष:
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
		ax25_rt = ax25_rt->next;
	पूर्ण

out:
	ग_लिखो_unlock_bh(&ax25_route_lock);
	वापस err;
पूर्ण

पूर्णांक ax25_rt_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा ax25_route_opt_काष्ठा rt_option;
	काष्ठा ax25_routes_काष्ठा route;

	चयन (cmd) अणु
	हाल SIOCADDRT:
		अगर (copy_from_user(&route, arg, माप(route)))
			वापस -EFAULT;
		वापस ax25_rt_add(&route);

	हाल SIOCDELRT:
		अगर (copy_from_user(&route, arg, माप(route)))
			वापस -EFAULT;
		वापस ax25_rt_del(&route);

	हाल SIOCAX25OPTRT:
		अगर (copy_from_user(&rt_option, arg, माप(rt_option)))
			वापस -EFAULT;
		वापस ax25_rt_opt(&rt_option);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम *ax25_rt_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(ax25_route_lock)
अणु
	काष्ठा ax25_route *ax25_rt;
	पूर्णांक i = 1;

	पढ़ो_lock(&ax25_route_lock);
	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	क्रम (ax25_rt = ax25_route_list; ax25_rt != शून्य; ax25_rt = ax25_rt->next) अणु
		अगर (i == *pos)
			वापस ax25_rt;
		++i;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *ax25_rt_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस (v == SEQ_START_TOKEN) ? ax25_route_list :
		((काष्ठा ax25_route *) v)->next;
पूर्ण

अटल व्योम ax25_rt_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(ax25_route_lock)
अणु
	पढ़ो_unlock(&ax25_route_lock);
पूर्ण

अटल पूर्णांक ax25_rt_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर buf[11];

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "callsign  dev  mode digipeaters\n");
	अन्यथा अणु
		काष्ठा ax25_route *ax25_rt = v;
		स्थिर अक्षर *callsign;
		पूर्णांक i;

		अगर (ax25cmp(&ax25_rt->callsign, &null_ax25_address) == 0)
			callsign = "default";
		अन्यथा
			callsign = ax2asc(buf, &ax25_rt->callsign);

		seq_म_लिखो(seq, "%-9s %-4s",
			callsign,
			ax25_rt->dev ? ax25_rt->dev->name : "???");

		चयन (ax25_rt->ip_mode) अणु
		हाल 'V':
			seq_माला_दो(seq, "   vc");
			अवरोध;
		हाल 'D':
			seq_माला_दो(seq, "   dg");
			अवरोध;
		शेष:
			seq_माला_दो(seq, "    *");
			अवरोध;
		पूर्ण

		अगर (ax25_rt->digipeat != शून्य)
			क्रम (i = 0; i < ax25_rt->digipeat->ndigi; i++)
				seq_म_लिखो(seq, " %s",
				     ax2asc(buf, &ax25_rt->digipeat->calls[i]));

		seq_माला_दो(seq, "\n");
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations ax25_rt_seqops = अणु
	.start = ax25_rt_seq_start,
	.next = ax25_rt_seq_next,
	.stop = ax25_rt_seq_stop,
	.show = ax25_rt_seq_show,
पूर्ण;
#पूर्ण_अगर

/*
 *	Find AX.25 route
 *
 *	Only routes with a reference count of zero can be destroyed.
 *	Must be called with ax25_route_lock पढ़ो locked.
 */
ax25_route *ax25_get_route(ax25_address *addr, काष्ठा net_device *dev)
अणु
	ax25_route *ax25_spe_rt = शून्य;
	ax25_route *ax25_def_rt = शून्य;
	ax25_route *ax25_rt;

	/*
	 *	Bind to the physical पूर्णांकerface we heard them on, or the शेष
	 *	route अगर none is found;
	 */
	क्रम (ax25_rt = ax25_route_list; ax25_rt != शून्य; ax25_rt = ax25_rt->next) अणु
		अगर (dev == शून्य) अणु
			अगर (ax25cmp(&ax25_rt->callsign, addr) == 0 && ax25_rt->dev != शून्य)
				ax25_spe_rt = ax25_rt;
			अगर (ax25cmp(&ax25_rt->callsign, &null_ax25_address) == 0 && ax25_rt->dev != शून्य)
				ax25_def_rt = ax25_rt;
		पूर्ण अन्यथा अणु
			अगर (ax25cmp(&ax25_rt->callsign, addr) == 0 && ax25_rt->dev == dev)
				ax25_spe_rt = ax25_rt;
			अगर (ax25cmp(&ax25_rt->callsign, &null_ax25_address) == 0 && ax25_rt->dev == dev)
				ax25_def_rt = ax25_rt;
		पूर्ण
	पूर्ण

	ax25_rt = ax25_def_rt;
	अगर (ax25_spe_rt != शून्य)
		ax25_rt = ax25_spe_rt;

	वापस ax25_rt;
पूर्ण

/*
 *	Adjust path: If you specअगरy a शेष route and want to connect
 *      a target on the digipeater path but w/o having a special route
 *	set beक्रमe, the path has to be truncated from your target on.
 */
अटल अंतरभूत व्योम ax25_adjust_path(ax25_address *addr, ax25_digi *digipeat)
अणु
	पूर्णांक k;

	क्रम (k = 0; k < digipeat->ndigi; k++) अणु
		अगर (ax25cmp(addr, &digipeat->calls[k]) == 0)
			अवरोध;
	पूर्ण

	digipeat->ndigi = k;
पूर्ण


/*
 *	Find which पूर्णांकerface to use.
 */
पूर्णांक ax25_rt_स्वतःbind(ax25_cb *ax25, ax25_address *addr)
अणु
	ax25_uid_assoc *user;
	ax25_route *ax25_rt;
	पूर्णांक err = 0;

	ax25_route_lock_use();
	ax25_rt = ax25_get_route(addr, शून्य);
	अगर (!ax25_rt) अणु
		ax25_route_lock_unuse();
		वापस -EHOSTUNREACH;
	पूर्ण
	अगर ((ax25->ax25_dev = ax25_dev_ax25dev(ax25_rt->dev)) == शून्य) अणु
		err = -EHOSTUNREACH;
		जाओ put;
	पूर्ण

	user = ax25_findbyuid(current_euid());
	अगर (user) अणु
		ax25->source_addr = user->call;
		ax25_uid_put(user);
	पूर्ण अन्यथा अणु
		अगर (ax25_uid_policy && !capable(CAP_NET_BIND_SERVICE)) अणु
			err = -EPERM;
			जाओ put;
		पूर्ण
		ax25->source_addr = *(ax25_address *)ax25->ax25_dev->dev->dev_addr;
	पूर्ण

	अगर (ax25_rt->digipeat != शून्य) अणु
		ax25->digipeat = kmemdup(ax25_rt->digipeat, माप(ax25_digi),
					 GFP_ATOMIC);
		अगर (ax25->digipeat == शून्य) अणु
			err = -ENOMEM;
			जाओ put;
		पूर्ण
		ax25_adjust_path(addr, ax25->digipeat);
	पूर्ण

	अगर (ax25->sk != शून्य) अणु
		local_bh_disable();
		bh_lock_sock(ax25->sk);
		sock_reset_flag(ax25->sk, SOCK_ZAPPED);
		bh_unlock_sock(ax25->sk);
		local_bh_enable();
	पूर्ण

put:
	ax25_route_lock_unuse();
	वापस err;
पूर्ण

काष्ठा sk_buff *ax25_rt_build_path(काष्ठा sk_buff *skb, ax25_address *src,
	ax25_address *dest, ax25_digi *digi)
अणु
	काष्ठा sk_buff *skbn;
	अचिन्हित अक्षर *bp;
	पूर्णांक len;

	len = digi->ndigi * AX25_ADDR_LEN;

	अगर (skb_headroom(skb) < len) अणु
		अगर ((skbn = skb_पुनः_स्मृति_headroom(skb, len)) == शून्य) अणु
			prपूर्णांकk(KERN_CRIT "AX.25: ax25_dg_build_path - out of memory\n");
			वापस शून्य;
		पूर्ण

		अगर (skb->sk != शून्य)
			skb_set_owner_w(skbn, skb->sk);

		consume_skb(skb);

		skb = skbn;
	पूर्ण

	bp = skb_push(skb, len);

	ax25_addr_build(bp, src, dest, digi, AX25_COMMAND, AX25_MODULUS);

	वापस skb;
पूर्ण

/*
 *	Free all memory associated with routing काष्ठाures.
 */
व्योम __निकास ax25_rt_मुक्त(व्योम)
अणु
	ax25_route *s, *ax25_rt = ax25_route_list;

	ग_लिखो_lock_bh(&ax25_route_lock);
	जबतक (ax25_rt != शून्य) अणु
		s       = ax25_rt;
		ax25_rt = ax25_rt->next;

		kमुक्त(s->digipeat);
		kमुक्त(s);
	पूर्ण
	ग_लिखो_unlock_bh(&ax25_route_lock);
पूर्ण
