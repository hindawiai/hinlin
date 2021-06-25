<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* procfs files क्रम key database क्रमागतeration
 *
 * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश "internal.h"

अटल व्योम *proc_keys_start(काष्ठा seq_file *p, loff_t *_pos);
अटल व्योम *proc_keys_next(काष्ठा seq_file *p, व्योम *v, loff_t *_pos);
अटल व्योम proc_keys_stop(काष्ठा seq_file *p, व्योम *v);
अटल पूर्णांक proc_keys_show(काष्ठा seq_file *m, व्योम *v);

अटल स्थिर काष्ठा seq_operations proc_keys_ops = अणु
	.start	= proc_keys_start,
	.next	= proc_keys_next,
	.stop	= proc_keys_stop,
	.show	= proc_keys_show,
पूर्ण;

अटल व्योम *proc_key_users_start(काष्ठा seq_file *p, loff_t *_pos);
अटल व्योम *proc_key_users_next(काष्ठा seq_file *p, व्योम *v, loff_t *_pos);
अटल व्योम proc_key_users_stop(काष्ठा seq_file *p, व्योम *v);
अटल पूर्णांक proc_key_users_show(काष्ठा seq_file *m, व्योम *v);

अटल स्थिर काष्ठा seq_operations proc_key_users_ops = अणु
	.start	= proc_key_users_start,
	.next	= proc_key_users_next,
	.stop	= proc_key_users_stop,
	.show	= proc_key_users_show,
पूर्ण;

/*
 * Declare the /proc files.
 */
अटल पूर्णांक __init key_proc_init(व्योम)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_create_seq("keys", 0, शून्य, &proc_keys_ops);
	अगर (!p)
		panic("Cannot create /proc/keys\n");

	p = proc_create_seq("key-users", 0, शून्य, &proc_key_users_ops);
	अगर (!p)
		panic("Cannot create /proc/key-users\n");

	वापस 0;
पूर्ण

__initcall(key_proc_init);

/*
 * Implement "/proc/keys" to provide a list of the keys on the प्रणाली that
 * grant View permission to the caller.
 */
अटल काष्ठा rb_node *key_serial_next(काष्ठा seq_file *p, काष्ठा rb_node *n)
अणु
	काष्ठा user_namespace *user_ns = seq_user_ns(p);

	n = rb_next(n);
	जबतक (n) अणु
		काष्ठा key *key = rb_entry(n, काष्ठा key, serial_node);
		अगर (kuid_has_mapping(user_ns, key->user->uid))
			अवरोध;
		n = rb_next(n);
	पूर्ण
	वापस n;
पूर्ण

अटल काष्ठा key *find_ge_key(काष्ठा seq_file *p, key_serial_t id)
अणु
	काष्ठा user_namespace *user_ns = seq_user_ns(p);
	काष्ठा rb_node *n = key_serial_tree.rb_node;
	काष्ठा key *minkey = शून्य;

	जबतक (n) अणु
		काष्ठा key *key = rb_entry(n, काष्ठा key, serial_node);
		अगर (id < key->serial) अणु
			अगर (!minkey || minkey->serial > key->serial)
				minkey = key;
			n = n->rb_left;
		पूर्ण अन्यथा अगर (id > key->serial) अणु
			n = n->rb_right;
		पूर्ण अन्यथा अणु
			minkey = key;
			अवरोध;
		पूर्ण
		key = शून्य;
	पूर्ण

	अगर (!minkey)
		वापस शून्य;

	क्रम (;;) अणु
		अगर (kuid_has_mapping(user_ns, minkey->user->uid))
			वापस minkey;
		n = rb_next(&minkey->serial_node);
		अगर (!n)
			वापस शून्य;
		minkey = rb_entry(n, काष्ठा key, serial_node);
	पूर्ण
पूर्ण

अटल व्योम *proc_keys_start(काष्ठा seq_file *p, loff_t *_pos)
	__acquires(key_serial_lock)
अणु
	key_serial_t pos = *_pos;
	काष्ठा key *key;

	spin_lock(&key_serial_lock);

	अगर (*_pos > पूर्णांक_उच्च)
		वापस शून्य;
	key = find_ge_key(p, pos);
	अगर (!key)
		वापस शून्य;
	*_pos = key->serial;
	वापस &key->serial_node;
पूर्ण

अटल अंतरभूत key_serial_t key_node_serial(काष्ठा rb_node *n)
अणु
	काष्ठा key *key = rb_entry(n, काष्ठा key, serial_node);
	वापस key->serial;
पूर्ण

अटल व्योम *proc_keys_next(काष्ठा seq_file *p, व्योम *v, loff_t *_pos)
अणु
	काष्ठा rb_node *n;

	n = key_serial_next(p, v);
	अगर (n)
		*_pos = key_node_serial(n);
	अन्यथा
		(*_pos)++;
	वापस n;
पूर्ण

अटल व्योम proc_keys_stop(काष्ठा seq_file *p, व्योम *v)
	__releases(key_serial_lock)
अणु
	spin_unlock(&key_serial_lock);
पूर्ण

अटल पूर्णांक proc_keys_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rb_node *_p = v;
	काष्ठा key *key = rb_entry(_p, काष्ठा key, serial_node);
	अचिन्हित दीर्घ flags;
	key_ref_t key_ref, skey_ref;
	समय64_t now, expiry;
	अक्षर xbuf[16];
	लघु state;
	u64 timo;
	पूर्णांक rc;

	काष्ठा keyring_search_context ctx = अणु
		.index_key		= key->index_key,
		.cred			= m->file->f_cred,
		.match_data.cmp		= lookup_user_key_possessed,
		.match_data.raw_data	= key,
		.match_data.lookup_type	= KEYRING_SEARCH_LOOKUP_सूचीECT,
		.flags			= (KEYRING_SEARCH_NO_STATE_CHECK |
					   KEYRING_SEARCH_RECURSE),
	पूर्ण;

	key_ref = make_key_ref(key, 0);

	/* determine अगर the key is possessed by this process (a test we can
	 * skip अगर the key करोes not indicate the possessor can view it
	 */
	अगर (key->perm & KEY_POS_VIEW) अणु
		rcu_पढ़ो_lock();
		skey_ref = search_cred_keyrings_rcu(&ctx);
		rcu_पढ़ो_unlock();
		अगर (!IS_ERR(skey_ref)) अणु
			key_ref_put(skey_ref);
			key_ref = make_key_ref(key, 1);
		पूर्ण
	पूर्ण

	/* check whether the current task is allowed to view the key */
	rc = key_task_permission(key_ref, ctx.cred, KEY_NEED_VIEW);
	अगर (rc < 0)
		वापस 0;

	now = kसमय_get_real_seconds();

	rcu_पढ़ो_lock();

	/* come up with a suitable समयout value */
	expiry = READ_ONCE(key->expiry);
	अगर (expiry == 0) अणु
		स_नकल(xbuf, "perm", 5);
	पूर्ण अन्यथा अगर (now >= expiry) अणु
		स_नकल(xbuf, "expd", 5);
	पूर्ण अन्यथा अणु
		timo = expiry - now;

		अगर (timo < 60)
			प्र_लिखो(xbuf, "%llus", timo);
		अन्यथा अगर (timo < 60*60)
			प्र_लिखो(xbuf, "%llum", भाग_u64(timo, 60));
		अन्यथा अगर (timo < 60*60*24)
			प्र_लिखो(xbuf, "%lluh", भाग_u64(timo, 60 * 60));
		अन्यथा अगर (timo < 60*60*24*7)
			प्र_लिखो(xbuf, "%llud", भाग_u64(timo, 60 * 60 * 24));
		अन्यथा
			प्र_लिखो(xbuf, "%lluw", भाग_u64(timo, 60 * 60 * 24 * 7));
	पूर्ण

	state = key_पढ़ो_state(key);

#घोषणा showflag(FLAGS, LETTER, FLAG) \
	((FLAGS & (1 << FLAG)) ? LETTER : '-')

	flags = READ_ONCE(key->flags);
	seq_म_लिखो(m, "%08x %c%c%c%c%c%c%c %5d %4s %08x %5d %5d %-9.9s ",
		   key->serial,
		   state != KEY_IS_UNINSTANTIATED ? 'I' : '-',
		   showflag(flags, 'R', KEY_FLAG_REVOKED),
		   showflag(flags, 'D', KEY_FLAG_DEAD),
		   showflag(flags, 'Q', KEY_FLAG_IN_QUOTA),
		   showflag(flags, 'U', KEY_FLAG_USER_CONSTRUCT),
		   state < 0 ? 'N' : '-',
		   showflag(flags, 'i', KEY_FLAG_INVALIDATED),
		   refcount_पढ़ो(&key->usage),
		   xbuf,
		   key->perm,
		   from_kuid_munged(seq_user_ns(m), key->uid),
		   from_kgid_munged(seq_user_ns(m), key->gid),
		   key->type->name);

#अघोषित showflag

	अगर (key->type->describe)
		key->type->describe(key, m);
	seq_अ_दो(m, '\n');

	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल काष्ठा rb_node *__key_user_next(काष्ठा user_namespace *user_ns, काष्ठा rb_node *n)
अणु
	जबतक (n) अणु
		काष्ठा key_user *user = rb_entry(n, काष्ठा key_user, node);
		अगर (kuid_has_mapping(user_ns, user->uid))
			अवरोध;
		n = rb_next(n);
	पूर्ण
	वापस n;
पूर्ण

अटल काष्ठा rb_node *key_user_next(काष्ठा user_namespace *user_ns, काष्ठा rb_node *n)
अणु
	वापस __key_user_next(user_ns, rb_next(n));
पूर्ण

अटल काष्ठा rb_node *key_user_first(काष्ठा user_namespace *user_ns, काष्ठा rb_root *r)
अणु
	काष्ठा rb_node *n = rb_first(r);
	वापस __key_user_next(user_ns, n);
पूर्ण

अटल व्योम *proc_key_users_start(काष्ठा seq_file *p, loff_t *_pos)
	__acquires(key_user_lock)
अणु
	काष्ठा rb_node *_p;
	loff_t pos = *_pos;

	spin_lock(&key_user_lock);

	_p = key_user_first(seq_user_ns(p), &key_user_tree);
	जबतक (pos > 0 && _p) अणु
		pos--;
		_p = key_user_next(seq_user_ns(p), _p);
	पूर्ण

	वापस _p;
पूर्ण

अटल व्योम *proc_key_users_next(काष्ठा seq_file *p, व्योम *v, loff_t *_pos)
अणु
	(*_pos)++;
	वापस key_user_next(seq_user_ns(p), (काष्ठा rb_node *)v);
पूर्ण

अटल व्योम proc_key_users_stop(काष्ठा seq_file *p, व्योम *v)
	__releases(key_user_lock)
अणु
	spin_unlock(&key_user_lock);
पूर्ण

अटल पूर्णांक proc_key_users_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rb_node *_p = v;
	काष्ठा key_user *user = rb_entry(_p, काष्ठा key_user, node);
	अचिन्हित maxkeys = uid_eq(user->uid, GLOBAL_ROOT_UID) ?
		key_quota_root_maxkeys : key_quota_maxkeys;
	अचिन्हित maxbytes = uid_eq(user->uid, GLOBAL_ROOT_UID) ?
		key_quota_root_maxbytes : key_quota_maxbytes;

	seq_म_लिखो(m, "%5u: %5d %d/%d %d/%d %d/%d\n",
		   from_kuid_munged(seq_user_ns(m), user->uid),
		   refcount_पढ़ो(&user->usage),
		   atomic_पढ़ो(&user->nkeys),
		   atomic_पढ़ो(&user->nikeys),
		   user->qnkeys,
		   maxkeys,
		   user->qnbytes,
		   maxbytes);

	वापस 0;
पूर्ण
