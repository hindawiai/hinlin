<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Authentication token and access key management पूर्णांकernal defs
 *
 * Copyright (C) 2003-5, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _INTERNAL_H
#घोषणा _INTERNAL_H

#समावेश <linux/sched.h>
#समावेश <linux/रुको_bit.h>
#समावेश <linux/cred.h>
#समावेश <linux/key-type.h>
#समावेश <linux/task_work.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/refcount.h>
#समावेश <linux/watch_queue.h>
#समावेश <linux/compat.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>

काष्ठा iovec;

#अगर_घोषित __KDEBUG
#घोषणा kenter(FMT, ...) \
	prपूर्णांकk(KERN_DEBUG "==> %s("FMT")\n", __func__, ##__VA_ARGS__)
#घोषणा kleave(FMT, ...) \
	prपूर्णांकk(KERN_DEBUG "<== %s()"FMT"\n", __func__, ##__VA_ARGS__)
#घोषणा kdebug(FMT, ...) \
	prपूर्णांकk(KERN_DEBUG "   "FMT"\n", ##__VA_ARGS__)
#अन्यथा
#घोषणा kenter(FMT, ...) \
	no_prपूर्णांकk(KERN_DEBUG "==> %s("FMT")\n", __func__, ##__VA_ARGS__)
#घोषणा kleave(FMT, ...) \
	no_prपूर्णांकk(KERN_DEBUG "<== %s()"FMT"\n", __func__, ##__VA_ARGS__)
#घोषणा kdebug(FMT, ...) \
	no_prपूर्णांकk(KERN_DEBUG FMT"\n", ##__VA_ARGS__)
#पूर्ण_अगर

बाह्य काष्ठा key_type key_type_dead;
बाह्य काष्ठा key_type key_type_user;
बाह्य काष्ठा key_type key_type_logon;

/*****************************************************************************/
/*
 * Keep track of keys क्रम a user.
 *
 * This needs to be separate to user_काष्ठा to aव्योम a refcount-loop
 * (user_काष्ठा pins some keyrings which pin this काष्ठा).
 *
 * We also keep track of keys under request from userspace क्रम this UID here.
 */
काष्ठा key_user अणु
	काष्ठा rb_node		node;
	काष्ठा mutex		cons_lock;	/* स्थिरruction initiation lock */
	spinlock_t		lock;
	refcount_t		usage;		/* क्रम accessing qnkeys & qnbytes */
	atomic_t		nkeys;		/* number of keys */
	atomic_t		nikeys;		/* number of instantiated keys */
	kuid_t			uid;
	पूर्णांक			qnkeys;		/* number of keys allocated to this user */
	पूर्णांक			qnbytes;	/* number of bytes allocated to this user */
पूर्ण;

बाह्य काष्ठा rb_root	key_user_tree;
बाह्य spinlock_t	key_user_lock;
बाह्य काष्ठा key_user	root_key_user;

बाह्य काष्ठा key_user *key_user_lookup(kuid_t uid);
बाह्य व्योम key_user_put(काष्ठा key_user *user);

/*
 * Key quota limits.
 * - root has its own separate limits to everyone अन्यथा
 */
बाह्य अचिन्हित key_quota_root_maxkeys;
बाह्य अचिन्हित key_quota_root_maxbytes;
बाह्य अचिन्हित key_quota_maxkeys;
बाह्य अचिन्हित key_quota_maxbytes;

#घोषणा KEYQUOTA_LINK_BYTES	4		/* a link in a keyring is worth 4 bytes */


बाह्य काष्ठा kmem_cache *key_jar;
बाह्य काष्ठा rb_root key_serial_tree;
बाह्य spinlock_t key_serial_lock;
बाह्य काष्ठा mutex key_स्थिरruction_mutex;
बाह्य रुको_queue_head_t request_key_conswq;

बाह्य व्योम key_set_index_key(काष्ठा keyring_index_key *index_key);
बाह्य काष्ठा key_type *key_type_lookup(स्थिर अक्षर *type);
बाह्य व्योम key_type_put(काष्ठा key_type *ktype);

बाह्य पूर्णांक __key_link_lock(काष्ठा key *keyring,
			   स्थिर काष्ठा keyring_index_key *index_key);
बाह्य पूर्णांक __key_move_lock(काष्ठा key *l_keyring, काष्ठा key *u_keyring,
			   स्थिर काष्ठा keyring_index_key *index_key);
बाह्य पूर्णांक __key_link_begin(काष्ठा key *keyring,
			    स्थिर काष्ठा keyring_index_key *index_key,
			    काष्ठा assoc_array_edit **_edit);
बाह्य पूर्णांक __key_link_check_live_key(काष्ठा key *keyring, काष्ठा key *key);
बाह्य व्योम __key_link(काष्ठा key *keyring, काष्ठा key *key,
		       काष्ठा assoc_array_edit **_edit);
बाह्य व्योम __key_link_end(काष्ठा key *keyring,
			   स्थिर काष्ठा keyring_index_key *index_key,
			   काष्ठा assoc_array_edit *edit);

बाह्य key_ref_t find_key_to_update(key_ref_t keyring_ref,
				    स्थिर काष्ठा keyring_index_key *index_key);

बाह्य काष्ठा key *keyring_search_instkey(काष्ठा key *keyring,
					  key_serial_t target_id);

बाह्य पूर्णांक iterate_over_keyring(स्थिर काष्ठा key *keyring,
				पूर्णांक (*func)(स्थिर काष्ठा key *key, व्योम *data),
				व्योम *data);

काष्ठा keyring_search_context अणु
	काष्ठा keyring_index_key index_key;
	स्थिर काष्ठा cred	*cred;
	काष्ठा key_match_data	match_data;
	अचिन्हित		flags;
#घोषणा KEYRING_SEARCH_NO_STATE_CHECK	0x0001	/* Skip state checks */
#घोषणा KEYRING_SEARCH_DO_STATE_CHECK	0x0002	/* Override NO_STATE_CHECK */
#घोषणा KEYRING_SEARCH_NO_UPDATE_TIME	0x0004	/* Don't update बार */
#घोषणा KEYRING_SEARCH_NO_CHECK_PERM	0x0008	/* Don't check permissions */
#घोषणा KEYRING_SEARCH_DETECT_TOO_DEEP	0x0010	/* Give an error on excessive depth */
#घोषणा KEYRING_SEARCH_SKIP_EXPIRED	0x0020	/* Ignore expired keys (पूर्णांकention to replace) */
#घोषणा KEYRING_SEARCH_RECURSE		0x0040	/* Search child keyrings also */

	पूर्णांक (*iterator)(स्थिर व्योम *object, व्योम *iterator_data);

	/* Internal stuff */
	पूर्णांक			skipped_ret;
	bool			possessed;
	key_ref_t		result;
	समय64_t		now;
पूर्ण;

बाह्य bool key_शेष_cmp(स्थिर काष्ठा key *key,
			    स्थिर काष्ठा key_match_data *match_data);
बाह्य key_ref_t keyring_search_rcu(key_ref_t keyring_ref,
				    काष्ठा keyring_search_context *ctx);

बाह्य key_ref_t search_cred_keyrings_rcu(काष्ठा keyring_search_context *ctx);
बाह्य key_ref_t search_process_keyrings_rcu(काष्ठा keyring_search_context *ctx);

बाह्य काष्ठा key *find_keyring_by_name(स्थिर अक्षर *name, bool uid_keyring);

बाह्य पूर्णांक look_up_user_keyrings(काष्ठा key **, काष्ठा key **);
बाह्य काष्ठा key *get_user_session_keyring_rcu(स्थिर काष्ठा cred *);
बाह्य पूर्णांक install_thपढ़ो_keyring_to_cred(काष्ठा cred *);
बाह्य पूर्णांक install_process_keyring_to_cred(काष्ठा cred *);
बाह्य पूर्णांक install_session_keyring_to_cred(काष्ठा cred *, काष्ठा key *);

बाह्य काष्ठा key *request_key_and_link(काष्ठा key_type *type,
					स्थिर अक्षर *description,
					काष्ठा key_tag *करोमुख्य_tag,
					स्थिर व्योम *callout_info,
					माप_प्रकार callout_len,
					व्योम *aux,
					काष्ठा key *dest_keyring,
					अचिन्हित दीर्घ flags);

बाह्य bool lookup_user_key_possessed(स्थिर काष्ठा key *key,
				      स्थिर काष्ठा key_match_data *match_data);
#घोषणा KEY_LOOKUP_CREATE	0x01
#घोषणा KEY_LOOKUP_PARTIAL	0x02

बाह्य दीर्घ join_session_keyring(स्थिर अक्षर *name);
बाह्य व्योम key_change_session_keyring(काष्ठा callback_head *twork);

बाह्य काष्ठा work_काष्ठा key_gc_work;
बाह्य अचिन्हित key_gc_delay;
बाह्य व्योम keyring_gc(काष्ठा key *keyring, समय64_t limit);
बाह्य व्योम keyring_restriction_gc(काष्ठा key *keyring,
				   काष्ठा key_type *dead_type);
बाह्य व्योम key_schedule_gc(समय64_t gc_at);
बाह्य व्योम key_schedule_gc_links(व्योम);
बाह्य व्योम key_gc_keytype(काष्ठा key_type *ktype);

बाह्य पूर्णांक key_task_permission(स्थिर key_ref_t key_ref,
			       स्थिर काष्ठा cred *cred,
			       क्रमागत key_need_perm need_perm);

अटल अंतरभूत व्योम notअगरy_key(काष्ठा key *key,
			      क्रमागत key_notअगरication_subtype subtype, u32 aux)
अणु
#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
	काष्ठा key_notअगरication n = अणु
		.watch.type	= WATCH_TYPE_KEY_NOTIFY,
		.watch.subtype	= subtype,
		.watch.info	= watch_माप(n),
		.key_id		= key_serial(key),
		.aux		= aux,
	पूर्ण;

	post_watch_notअगरication(key->watchers, &n.watch, current_cred(),
				n.key_id);
#पूर्ण_अगर
पूर्ण

/*
 * Check to see whether permission is granted to use a key in the desired way.
 */
अटल अंतरभूत पूर्णांक key_permission(स्थिर key_ref_t key_ref,
				 क्रमागत key_need_perm need_perm)
अणु
	वापस key_task_permission(key_ref, current_cred(), need_perm);
पूर्ण

बाह्य काष्ठा key_type key_type_request_key_auth;
बाह्य काष्ठा key *request_key_auth_new(काष्ठा key *target,
					स्थिर अक्षर *op,
					स्थिर व्योम *callout_info,
					माप_प्रकार callout_len,
					काष्ठा key *dest_keyring);

बाह्य काष्ठा key *key_get_instantiation_authkey(key_serial_t target_id);

/*
 * Determine whether a key is dead.
 */
अटल अंतरभूत bool key_is_dead(स्थिर काष्ठा key *key, समय64_t limit)
अणु
	वापस
		key->flags & ((1 << KEY_FLAG_DEAD) |
			      (1 << KEY_FLAG_INVALIDATED)) ||
		(key->expiry > 0 && key->expiry <= limit) ||
		key->करोमुख्य_tag->हटाओd;
पूर्ण

/*
 * keyctl() functions
 */
बाह्य दीर्घ keyctl_get_keyring_ID(key_serial_t, पूर्णांक);
बाह्य दीर्घ keyctl_join_session_keyring(स्थिर अक्षर __user *);
बाह्य दीर्घ keyctl_update_key(key_serial_t, स्थिर व्योम __user *, माप_प्रकार);
बाह्य दीर्घ keyctl_revoke_key(key_serial_t);
बाह्य दीर्घ keyctl_keyring_clear(key_serial_t);
बाह्य दीर्घ keyctl_keyring_link(key_serial_t, key_serial_t);
बाह्य दीर्घ keyctl_keyring_move(key_serial_t, key_serial_t, key_serial_t, अचिन्हित पूर्णांक);
बाह्य दीर्घ keyctl_keyring_unlink(key_serial_t, key_serial_t);
बाह्य दीर्घ keyctl_describe_key(key_serial_t, अक्षर __user *, माप_प्रकार);
बाह्य दीर्घ keyctl_keyring_search(key_serial_t, स्थिर अक्षर __user *,
				  स्थिर अक्षर __user *, key_serial_t);
बाह्य दीर्घ keyctl_पढ़ो_key(key_serial_t, अक्षर __user *, माप_प्रकार);
बाह्य दीर्घ keyctl_chown_key(key_serial_t, uid_t, gid_t);
बाह्य दीर्घ keyctl_setperm_key(key_serial_t, key_perm_t);
बाह्य दीर्घ keyctl_instantiate_key(key_serial_t, स्थिर व्योम __user *,
				   माप_प्रकार, key_serial_t);
बाह्य दीर्घ keyctl_negate_key(key_serial_t, अचिन्हित, key_serial_t);
बाह्य दीर्घ keyctl_set_reqkey_keyring(पूर्णांक);
बाह्य दीर्घ keyctl_set_समयout(key_serial_t, अचिन्हित);
बाह्य दीर्घ keyctl_assume_authority(key_serial_t);
बाह्य दीर्घ keyctl_get_security(key_serial_t keyid, अक्षर __user *buffer,
				माप_प्रकार buflen);
बाह्य दीर्घ keyctl_session_to_parent(व्योम);
बाह्य दीर्घ keyctl_reject_key(key_serial_t, अचिन्हित, अचिन्हित, key_serial_t);
बाह्य दीर्घ keyctl_instantiate_key_iov(key_serial_t,
				       स्थिर काष्ठा iovec __user *,
				       अचिन्हित, key_serial_t);
बाह्य दीर्घ keyctl_invalidate_key(key_serial_t);
बाह्य दीर्घ keyctl_restrict_keyring(key_serial_t id,
				    स्थिर अक्षर __user *_type,
				    स्थिर अक्षर __user *_restriction);
#अगर_घोषित CONFIG_PERSISTENT_KEYRINGS
बाह्य दीर्घ keyctl_get_persistent(uid_t, key_serial_t);
बाह्य अचिन्हित persistent_keyring_expiry;
#अन्यथा
अटल अंतरभूत दीर्घ keyctl_get_persistent(uid_t uid, key_serial_t destring)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEY_DH_OPERATIONS
बाह्य दीर्घ keyctl_dh_compute(काष्ठा keyctl_dh_params __user *, अक्षर __user *,
			      माप_प्रकार, काष्ठा keyctl_kdf_params __user *);
बाह्य दीर्घ __keyctl_dh_compute(काष्ठा keyctl_dh_params __user *, अक्षर __user *,
				माप_प्रकार, काष्ठा keyctl_kdf_params *);
#अगर_घोषित CONFIG_COMPAT
बाह्य दीर्घ compat_keyctl_dh_compute(काष्ठा keyctl_dh_params __user *params,
				अक्षर __user *buffer, माप_प्रकार buflen,
				काष्ठा compat_keyctl_kdf_params __user *kdf);
#पूर्ण_अगर
#घोषणा KEYCTL_KDF_MAX_OUTPUT_LEN	1024	/* max length of KDF output */
#घोषणा KEYCTL_KDF_MAX_OI_LEN		64	/* max length of otherinfo */
#अन्यथा
अटल अंतरभूत दीर्घ keyctl_dh_compute(काष्ठा keyctl_dh_params __user *params,
				     अक्षर __user *buffer, माप_प्रकार buflen,
				     काष्ठा keyctl_kdf_params __user *kdf)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल अंतरभूत दीर्घ compat_keyctl_dh_compute(
				काष्ठा keyctl_dh_params __user *params,
				अक्षर __user *buffer, माप_प्रकार buflen,
				काष्ठा keyctl_kdf_params __user *kdf)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_ASYMMETRIC_KEY_TYPE
बाह्य दीर्घ keyctl_pkey_query(key_serial_t,
			      स्थिर अक्षर __user *,
			      काष्ठा keyctl_pkey_query __user *);

बाह्य दीर्घ keyctl_pkey_verअगरy(स्थिर काष्ठा keyctl_pkey_params __user *,
			       स्थिर अक्षर __user *,
			       स्थिर व्योम __user *, स्थिर व्योम __user *);

बाह्य दीर्घ keyctl_pkey_e_d_s(पूर्णांक,
			      स्थिर काष्ठा keyctl_pkey_params __user *,
			      स्थिर अक्षर __user *,
			      स्थिर व्योम __user *, व्योम __user *);
#अन्यथा
अटल अंतरभूत दीर्घ keyctl_pkey_query(key_serial_t id,
				     स्थिर अक्षर __user *_info,
				     काष्ठा keyctl_pkey_query __user *_res)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत दीर्घ keyctl_pkey_verअगरy(स्थिर काष्ठा keyctl_pkey_params __user *params,
				      स्थिर अक्षर __user *_info,
				      स्थिर व्योम __user *_in,
				      स्थिर व्योम __user *_in2)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत दीर्घ keyctl_pkey_e_d_s(पूर्णांक op,
				     स्थिर काष्ठा keyctl_pkey_params __user *params,
				     स्थिर अक्षर __user *_info,
				     स्थिर व्योम __user *_in,
				     व्योम __user *_out)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

बाह्य दीर्घ keyctl_capabilities(अचिन्हित अक्षर __user *_buffer, माप_प्रकार buflen);

#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
बाह्य दीर्घ keyctl_watch_key(key_serial_t, पूर्णांक, पूर्णांक);
#अन्यथा
अटल अंतरभूत दीर्घ keyctl_watch_key(key_serial_t key_id, पूर्णांक watch_fd, पूर्णांक watch_id)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

/*
 * Debugging key validation
 */
#अगर_घोषित KEY_DEBUGGING
बाह्य व्योम __key_check(स्थिर काष्ठा key *);

अटल अंतरभूत व्योम key_check(स्थिर काष्ठा key *key)
अणु
	अगर (key && (IS_ERR(key) || key->magic != KEY_DEBUG_MAGIC))
		__key_check(key);
पूर्ण

#अन्यथा

#घोषणा key_check(key) करो अणुपूर्ण जबतक(0)

#पूर्ण_अगर
#पूर्ण_अगर /* _INTERNAL_H */
