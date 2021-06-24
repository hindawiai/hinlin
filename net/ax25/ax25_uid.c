<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 */

#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/export.h>
#समावेश <net/ip.h>
#समावेश <net/arp.h>

/*
 *	Callsign/UID mapper. This is in kernel space क्रम security on multi-amateur machines.
 */

अटल HLIST_HEAD(ax25_uid_list);
अटल DEFINE_RWLOCK(ax25_uid_lock);

पूर्णांक ax25_uid_policy;

EXPORT_SYMBOL(ax25_uid_policy);

ax25_uid_assoc *ax25_findbyuid(kuid_t uid)
अणु
	ax25_uid_assoc *ax25_uid, *res = शून्य;

	पढ़ो_lock(&ax25_uid_lock);
	ax25_uid_क्रम_each(ax25_uid, &ax25_uid_list) अणु
		अगर (uid_eq(ax25_uid->uid, uid)) अणु
			ax25_uid_hold(ax25_uid);
			res = ax25_uid;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&ax25_uid_lock);

	वापस res;
पूर्ण

EXPORT_SYMBOL(ax25_findbyuid);

पूर्णांक ax25_uid_ioctl(पूर्णांक cmd, काष्ठा sockaddr_ax25 *sax)
अणु
	ax25_uid_assoc *ax25_uid;
	ax25_uid_assoc *user;
	अचिन्हित दीर्घ res;

	चयन (cmd) अणु
	हाल SIOCAX25GETUID:
		res = -ENOENT;
		पढ़ो_lock(&ax25_uid_lock);
		ax25_uid_क्रम_each(ax25_uid, &ax25_uid_list) अणु
			अगर (ax25cmp(&sax->sax25_call, &ax25_uid->call) == 0) अणु
				res = from_kuid_munged(current_user_ns(), ax25_uid->uid);
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock(&ax25_uid_lock);

		वापस res;

	हाल SIOCAX25ADDUID:
	अणु
		kuid_t sax25_kuid;
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		sax25_kuid = make_kuid(current_user_ns(), sax->sax25_uid);
		अगर (!uid_valid(sax25_kuid))
			वापस -EINVAL;
		user = ax25_findbyuid(sax25_kuid);
		अगर (user) अणु
			ax25_uid_put(user);
			वापस -EEXIST;
		पूर्ण
		अगर (sax->sax25_uid == 0)
			वापस -EINVAL;
		अगर ((ax25_uid = kदो_स्मृति(माप(*ax25_uid), GFP_KERNEL)) == शून्य)
			वापस -ENOMEM;

		refcount_set(&ax25_uid->refcount, 1);
		ax25_uid->uid  = sax25_kuid;
		ax25_uid->call = sax->sax25_call;

		ग_लिखो_lock(&ax25_uid_lock);
		hlist_add_head(&ax25_uid->uid_node, &ax25_uid_list);
		ग_लिखो_unlock(&ax25_uid_lock);

		वापस 0;
	पूर्ण
	हाल SIOCAX25DELUID:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		ax25_uid = शून्य;
		ग_लिखो_lock(&ax25_uid_lock);
		ax25_uid_क्रम_each(ax25_uid, &ax25_uid_list) अणु
			अगर (ax25cmp(&sax->sax25_call, &ax25_uid->call) == 0)
				अवरोध;
		पूर्ण
		अगर (ax25_uid == शून्य) अणु
			ग_लिखो_unlock(&ax25_uid_lock);
			वापस -ENOENT;
		पूर्ण
		hlist_del_init(&ax25_uid->uid_node);
		ax25_uid_put(ax25_uid);
		ग_लिखो_unlock(&ax25_uid_lock);

		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;	/*NOTREACHED */
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम *ax25_uid_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(ax25_uid_lock)
अणु
	पढ़ो_lock(&ax25_uid_lock);
	वापस seq_hlist_start_head(&ax25_uid_list, *pos);
पूर्ण

अटल व्योम *ax25_uid_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_hlist_next(v, &ax25_uid_list, pos);
पूर्ण

अटल व्योम ax25_uid_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(ax25_uid_lock)
अणु
	पढ़ो_unlock(&ax25_uid_lock);
पूर्ण

अटल पूर्णांक ax25_uid_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर buf[11];

	अगर (v == SEQ_START_TOKEN)
		seq_म_लिखो(seq, "Policy: %d\n", ax25_uid_policy);
	अन्यथा अणु
		काष्ठा ax25_uid_assoc *pt;

		pt = hlist_entry(v, काष्ठा ax25_uid_assoc, uid_node);
		seq_म_लिखो(seq, "%6d %s\n",
			from_kuid_munged(seq_user_ns(seq), pt->uid),
			ax2asc(buf, &pt->call));
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations ax25_uid_seqops = अणु
	.start = ax25_uid_seq_start,
	.next = ax25_uid_seq_next,
	.stop = ax25_uid_seq_stop,
	.show = ax25_uid_seq_show,
पूर्ण;
#पूर्ण_अगर

/*
 *	Free all memory associated with UID/Callsign काष्ठाures.
 */
व्योम __निकास ax25_uid_मुक्त(व्योम)
अणु
	ax25_uid_assoc *ax25_uid;

	ग_लिखो_lock(&ax25_uid_lock);
again:
	ax25_uid_क्रम_each(ax25_uid, &ax25_uid_list) अणु
		hlist_del_init(&ax25_uid->uid_node);
		ax25_uid_put(ax25_uid);
		जाओ again;
	पूर्ण
	ग_लिखो_unlock(&ax25_uid_lock);
पूर्ण
