<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Authentication token and access key management
 *
 * Copyright (C) 2004, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * See Documentation/security/keys/core.rst क्रम inक्रमmation on keys/keyrings.
 */

#अगर_अघोषित _LINUX_KEY_H
#घोषणा _LINUX_KEY_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/atomic.h>
#समावेश <linux/assoc_array.h>
#समावेश <linux/refcount.h>
#समावेश <linux/समय64.h>

#अगर_घोषित __KERNEL__
#समावेश <linux/uidgid.h>

/* key handle serial number */
प्रकार पूर्णांक32_t key_serial_t;

/* key handle permissions mask */
प्रकार uपूर्णांक32_t key_perm_t;

काष्ठा key;
काष्ठा net;

#अगर_घोषित CONFIG_KEYS

#अघोषित KEY_DEBUGGING

#घोषणा KEY_POS_VIEW	0x01000000	/* possessor can view a key's attributes */
#घोषणा KEY_POS_READ	0x02000000	/* possessor can पढ़ो key payload / view keyring */
#घोषणा KEY_POS_WRITE	0x04000000	/* possessor can update key payload / add link to keyring */
#घोषणा KEY_POS_SEARCH	0x08000000	/* possessor can find a key in search / search a keyring */
#घोषणा KEY_POS_LINK	0x10000000	/* possessor can create a link to a key/keyring */
#घोषणा KEY_POS_SETATTR	0x20000000	/* possessor can set key attributes */
#घोषणा KEY_POS_ALL	0x3f000000

#घोषणा KEY_USR_VIEW	0x00010000	/* user permissions... */
#घोषणा KEY_USR_READ	0x00020000
#घोषणा KEY_USR_WRITE	0x00040000
#घोषणा KEY_USR_SEARCH	0x00080000
#घोषणा KEY_USR_LINK	0x00100000
#घोषणा KEY_USR_SETATTR	0x00200000
#घोषणा KEY_USR_ALL	0x003f0000

#घोषणा KEY_GRP_VIEW	0x00000100	/* group permissions... */
#घोषणा KEY_GRP_READ	0x00000200
#घोषणा KEY_GRP_WRITE	0x00000400
#घोषणा KEY_GRP_SEARCH	0x00000800
#घोषणा KEY_GRP_LINK	0x00001000
#घोषणा KEY_GRP_SETATTR	0x00002000
#घोषणा KEY_GRP_ALL	0x00003f00

#घोषणा KEY_OTH_VIEW	0x00000001	/* third party permissions... */
#घोषणा KEY_OTH_READ	0x00000002
#घोषणा KEY_OTH_WRITE	0x00000004
#घोषणा KEY_OTH_SEARCH	0x00000008
#घोषणा KEY_OTH_LINK	0x00000010
#घोषणा KEY_OTH_SETATTR	0x00000020
#घोषणा KEY_OTH_ALL	0x0000003f

#घोषणा KEY_PERM_UNDEF	0xffffffff

/*
 * The permissions required on a key that we're looking up.
 */
क्रमागत key_need_perm अणु
	KEY_NEED_UNSPECIFIED,	/* Needed permission unspecअगरied */
	KEY_NEED_VIEW,		/* Require permission to view attributes */
	KEY_NEED_READ,		/* Require permission to पढ़ो content */
	KEY_NEED_WRITE,		/* Require permission to update / modअगरy */
	KEY_NEED_SEARCH,	/* Require permission to search (keyring) or find (key) */
	KEY_NEED_LINK,		/* Require permission to link */
	KEY_NEED_SETATTR,	/* Require permission to change attributes */
	KEY_NEED_UNLINK,	/* Require permission to unlink key */
	KEY_SYSADMIN_OVERRIDE,	/* Special: override by CAP_SYS_ADMIN */
	KEY_AUTHTOKEN_OVERRIDE,	/* Special: override by possession of auth token */
	KEY_DEFER_PERM_CHECK,	/* Special: permission check is deferred */
पूर्ण;

काष्ठा seq_file;
काष्ठा user_काष्ठा;
काष्ठा संकेत_काष्ठा;
काष्ठा cred;

काष्ठा key_type;
काष्ठा key_owner;
काष्ठा key_tag;
काष्ठा keyring_list;
काष्ठा keyring_name;

काष्ठा key_tag अणु
	काष्ठा rcu_head		rcu;
	refcount_t		usage;
	bool			हटाओd;	/* T when subject हटाओd */
पूर्ण;

काष्ठा keyring_index_key अणु
	/* [!] If this काष्ठाure is altered, the जोड़ in काष्ठा key must change too! */
	अचिन्हित दीर्घ		hash;			/* Hash value */
	जोड़ अणु
		काष्ठा अणु
#अगर_घोषित __LITTLE_ENDIAN /* Put desc_len at the LSB of x */
			u16	desc_len;
			अक्षर	desc[माप(दीर्घ) - 2];	/* First few अक्षरs of description */
#अन्यथा
			अक्षर	desc[माप(दीर्घ) - 2];	/* First few अक्षरs of description */
			u16	desc_len;
#पूर्ण_अगर
		पूर्ण;
		अचिन्हित दीर्घ x;
	पूर्ण;
	काष्ठा key_type		*type;
	काष्ठा key_tag		*करोमुख्य_tag;	/* Doमुख्य of operation */
	स्थिर अक्षर		*description;
पूर्ण;

जोड़ key_payload अणु
	व्योम __rcu		*rcu_data0;
	व्योम			*data[4];
पूर्ण;

/*****************************************************************************/
/*
 * key reference with possession attribute handling
 *
 * NOTE! key_ref_t is a प्रकार'd poपूर्णांकer to a type that is not actually
 * defined. This is because we abuse the bottom bit of the reference to carry a
 * flag to indicate whether the calling process possesses that key in one of
 * its keyrings.
 *
 * the key_ref_t has been made a separate type so that the compiler can reject
 * attempts to dereference it without proper conversion.
 *
 * the three functions are used to assemble and disassemble references
 */
प्रकार काष्ठा __key_reference_with_attributes *key_ref_t;

अटल अंतरभूत key_ref_t make_key_ref(स्थिर काष्ठा key *key,
				     bool possession)
अणु
	वापस (key_ref_t) ((अचिन्हित दीर्घ) key | possession);
पूर्ण

अटल अंतरभूत काष्ठा key *key_ref_to_ptr(स्थिर key_ref_t key_ref)
अणु
	वापस (काष्ठा key *) ((अचिन्हित दीर्घ) key_ref & ~1UL);
पूर्ण

अटल अंतरभूत bool is_key_possessed(स्थिर key_ref_t key_ref)
अणु
	वापस (अचिन्हित दीर्घ) key_ref & 1UL;
पूर्ण

प्रकार पूर्णांक (*key_restrict_link_func_t)(काष्ठा key *dest_keyring,
					स्थिर काष्ठा key_type *type,
					स्थिर जोड़ key_payload *payload,
					काष्ठा key *restriction_key);

काष्ठा key_restriction अणु
	key_restrict_link_func_t check;
	काष्ठा key *key;
	काष्ठा key_type *keytype;
पूर्ण;

क्रमागत key_state अणु
	KEY_IS_UNINSTANTIATED,
	KEY_IS_POSITIVE,		/* Positively instantiated */
पूर्ण;

/*****************************************************************************/
/*
 * authentication token / access credential / keyring
 * - types of key include:
 *   - keyrings
 *   - disk encryption IDs
 *   - Kerberos TGTs and tickets
 */
काष्ठा key अणु
	refcount_t		usage;		/* number of references */
	key_serial_t		serial;		/* key serial number */
	जोड़ अणु
		काष्ठा list_head graveyard_link;
		काष्ठा rb_node	serial_node;
	पूर्ण;
#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
	काष्ठा watch_list	*watchers;	/* Entities watching this key क्रम changes */
#पूर्ण_अगर
	काष्ठा rw_semaphore	sem;		/* change vs change sem */
	काष्ठा key_user		*user;		/* owner of this key */
	व्योम			*security;	/* security data क्रम this key */
	जोड़ अणु
		समय64_t	expiry;		/* समय at which key expires (or 0) */
		समय64_t	revoked_at;	/* समय at which key was revoked */
	पूर्ण;
	समय64_t		last_used_at;	/* last समय used क्रम LRU keyring discard */
	kuid_t			uid;
	kgid_t			gid;
	key_perm_t		perm;		/* access permissions */
	अचिन्हित लघु		quotalen;	/* length added to quota */
	अचिन्हित लघु		datalen;	/* payload data length
						 * - may not match RCU dereferenced payload
						 * - payload should contain own length
						 */
	लघु			state;		/* Key state (+) or rejection error (-) */

#अगर_घोषित KEY_DEBUGGING
	अचिन्हित		magic;
#घोषणा KEY_DEBUG_MAGIC		0x18273645u
#पूर्ण_अगर

	अचिन्हित दीर्घ		flags;		/* status flags (change with bitops) */
#घोषणा KEY_FLAG_DEAD		0	/* set अगर key type has been deleted */
#घोषणा KEY_FLAG_REVOKED	1	/* set अगर key had been revoked */
#घोषणा KEY_FLAG_IN_QUOTA	2	/* set अगर key consumes quota */
#घोषणा KEY_FLAG_USER_CONSTRUCT	3	/* set अगर key is being स्थिरructed in userspace */
#घोषणा KEY_FLAG_ROOT_CAN_CLEAR	4	/* set अगर key can be cleared by root without permission */
#घोषणा KEY_FLAG_INVALIDATED	5	/* set अगर key has been invalidated */
#घोषणा KEY_FLAG_BUILTIN	6	/* set अगर key is built in to the kernel */
#घोषणा KEY_FLAG_ROOT_CAN_INVAL	7	/* set अगर key can be invalidated by root without permission */
#घोषणा KEY_FLAG_KEEP		8	/* set अगर key should not be हटाओd */
#घोषणा KEY_FLAG_UID_KEYRING	9	/* set अगर key is a user or user session keyring */

	/* the key type and key description string
	 * - the desc is used to match a key against search criteria
	 * - it should be a prपूर्णांकable string
	 * - eg: क्रम krb5 AFS, this might be "afs@REDHAT.COM"
	 */
	जोड़ अणु
		काष्ठा keyring_index_key index_key;
		काष्ठा अणु
			अचिन्हित दीर्घ	hash;
			अचिन्हित दीर्घ	len_desc;
			काष्ठा key_type	*type;		/* type of key */
			काष्ठा key_tag	*करोमुख्य_tag;	/* Doमुख्य of operation */
			अक्षर		*description;
		पूर्ण;
	पूर्ण;

	/* key data
	 * - this is used to hold the data actually used in cryptography or
	 *   whatever
	 */
	जोड़ अणु
		जोड़ key_payload payload;
		काष्ठा अणु
			/* Keyring bits */
			काष्ठा list_head name_link;
			काष्ठा assoc_array keys;
		पूर्ण;
	पूर्ण;

	/* This is set on a keyring to restrict the addition of a link to a key
	 * to it.  If this काष्ठाure isn't provided then it is assumed that the
	 * keyring is खोलो to any addition.  It is ignored क्रम non-keyring
	 * keys. Only set this value using keyring_restrict(), keyring_alloc(),
	 * or key_alloc().
	 *
	 * This is पूर्णांकended क्रम use with rings of trusted keys whereby addition
	 * to the keyring needs to be controlled.  KEY_ALLOC_BYPASS_RESTRICTION
	 * overrides this, allowing the kernel to add extra keys without
	 * restriction.
	 */
	काष्ठा key_restriction *restrict_link;
पूर्ण;

बाह्य काष्ठा key *key_alloc(काष्ठा key_type *type,
			     स्थिर अक्षर *desc,
			     kuid_t uid, kgid_t gid,
			     स्थिर काष्ठा cred *cred,
			     key_perm_t perm,
			     अचिन्हित दीर्घ flags,
			     काष्ठा key_restriction *restrict_link);


#घोषणा KEY_ALLOC_IN_QUOTA		0x0000	/* add to quota, reject अगर would overrun */
#घोषणा KEY_ALLOC_QUOTA_OVERRUN		0x0001	/* add to quota, permit even अगर overrun */
#घोषणा KEY_ALLOC_NOT_IN_QUOTA		0x0002	/* not in quota */
#घोषणा KEY_ALLOC_BUILT_IN		0x0004	/* Key is built पूर्णांकo kernel */
#घोषणा KEY_ALLOC_BYPASS_RESTRICTION	0x0008	/* Override the check on restricted keyrings */
#घोषणा KEY_ALLOC_UID_KEYRING		0x0010	/* allocating a user or user session keyring */
#घोषणा KEY_ALLOC_SET_KEEP		0x0020	/* Set the KEEP flag on the key/keyring */

बाह्य व्योम key_revoke(काष्ठा key *key);
बाह्य व्योम key_invalidate(काष्ठा key *key);
बाह्य व्योम key_put(काष्ठा key *key);
बाह्य bool key_put_tag(काष्ठा key_tag *tag);
बाह्य व्योम key_हटाओ_करोमुख्य(काष्ठा key_tag *करोमुख्य_tag);

अटल अंतरभूत काष्ठा key *__key_get(काष्ठा key *key)
अणु
	refcount_inc(&key->usage);
	वापस key;
पूर्ण

अटल अंतरभूत काष्ठा key *key_get(काष्ठा key *key)
अणु
	वापस key ? __key_get(key) : key;
पूर्ण

अटल अंतरभूत व्योम key_ref_put(key_ref_t key_ref)
अणु
	key_put(key_ref_to_ptr(key_ref));
पूर्ण

बाह्य काष्ठा key *request_key_tag(काष्ठा key_type *type,
				   स्थिर अक्षर *description,
				   काष्ठा key_tag *करोमुख्य_tag,
				   स्थिर अक्षर *callout_info);

बाह्य काष्ठा key *request_key_rcu(काष्ठा key_type *type,
				   स्थिर अक्षर *description,
				   काष्ठा key_tag *करोमुख्य_tag);

बाह्य काष्ठा key *request_key_with_auxdata(काष्ठा key_type *type,
					    स्थिर अक्षर *description,
					    काष्ठा key_tag *करोमुख्य_tag,
					    स्थिर व्योम *callout_info,
					    माप_प्रकार callout_len,
					    व्योम *aux);

/**
 * request_key - Request a key and रुको क्रम स्थिरruction
 * @type: Type of key.
 * @description: The searchable description of the key.
 * @callout_info: The data to pass to the instantiation upcall (or शून्य).
 *
 * As क्रम request_key_tag(), but with the शेष global करोमुख्य tag.
 */
अटल अंतरभूत काष्ठा key *request_key(काष्ठा key_type *type,
				      स्थिर अक्षर *description,
				      स्थिर अक्षर *callout_info)
अणु
	वापस request_key_tag(type, description, शून्य, callout_info);
पूर्ण

#अगर_घोषित CONFIG_NET
/**
 * request_key_net - Request a key क्रम a net namespace and रुको क्रम स्थिरruction
 * @type: Type of key.
 * @description: The searchable description of the key.
 * @net: The network namespace that is the key's करोमुख्य of operation.
 * @callout_info: The data to pass to the instantiation upcall (or शून्य).
 *
 * As क्रम request_key() except that it करोes not add the वापसed key to a
 * keyring अगर found, new keys are always allocated in the user's quota, the
 * callout_info must be a NUL-terminated string and no auxiliary data can be
 * passed.  Only keys that operate the specअगरied network namespace are used.
 *
 * Furthermore, it then works as रुको_क्रम_key_स्थिरruction() to रुको क्रम the
 * completion of keys undergoing स्थिरruction with a non-पूर्णांकerruptible रुको.
 */
#घोषणा request_key_net(type, description, net, callout_info) \
	request_key_tag(type, description, net->key_करोमुख्य, callout_info)

/**
 * request_key_net_rcu - Request a key क्रम a net namespace under RCU conditions
 * @type: Type of key.
 * @description: The searchable description of the key.
 * @net: The network namespace that is the key's करोमुख्य of operation.
 *
 * As क्रम request_key_rcu() except that only keys that operate the specअगरied
 * network namespace are used.
 */
#घोषणा request_key_net_rcu(type, description, net) \
	request_key_rcu(type, description, net->key_करोमुख्य)
#पूर्ण_अगर /* CONFIG_NET */

बाह्य पूर्णांक रुको_क्रम_key_स्थिरruction(काष्ठा key *key, bool पूर्णांकr);

बाह्य पूर्णांक key_validate(स्थिर काष्ठा key *key);

बाह्य key_ref_t key_create_or_update(key_ref_t keyring,
				      स्थिर अक्षर *type,
				      स्थिर अक्षर *description,
				      स्थिर व्योम *payload,
				      माप_प्रकार plen,
				      key_perm_t perm,
				      अचिन्हित दीर्घ flags);

बाह्य पूर्णांक key_update(key_ref_t key,
		      स्थिर व्योम *payload,
		      माप_प्रकार plen);

बाह्य पूर्णांक key_link(काष्ठा key *keyring,
		    काष्ठा key *key);

बाह्य पूर्णांक key_move(काष्ठा key *key,
		    काष्ठा key *from_keyring,
		    काष्ठा key *to_keyring,
		    अचिन्हित पूर्णांक flags);

बाह्य पूर्णांक key_unlink(काष्ठा key *keyring,
		      काष्ठा key *key);

बाह्य काष्ठा key *keyring_alloc(स्थिर अक्षर *description, kuid_t uid, kgid_t gid,
				 स्थिर काष्ठा cred *cred,
				 key_perm_t perm,
				 अचिन्हित दीर्घ flags,
				 काष्ठा key_restriction *restrict_link,
				 काष्ठा key *dest);

बाह्य पूर्णांक restrict_link_reject(काष्ठा key *keyring,
				स्थिर काष्ठा key_type *type,
				स्थिर जोड़ key_payload *payload,
				काष्ठा key *restriction_key);

बाह्य पूर्णांक keyring_clear(काष्ठा key *keyring);

बाह्य key_ref_t keyring_search(key_ref_t keyring,
				काष्ठा key_type *type,
				स्थिर अक्षर *description,
				bool recurse);

बाह्य पूर्णांक keyring_add_key(काष्ठा key *keyring,
			   काष्ठा key *key);

बाह्य पूर्णांक keyring_restrict(key_ref_t keyring, स्थिर अक्षर *type,
			    स्थिर अक्षर *restriction);

बाह्य काष्ठा key *key_lookup(key_serial_t id);

अटल अंतरभूत key_serial_t key_serial(स्थिर काष्ठा key *key)
अणु
	वापस key ? key->serial : 0;
पूर्ण

बाह्य व्योम key_set_समयout(काष्ठा key *, अचिन्हित);

बाह्य key_ref_t lookup_user_key(key_serial_t id, अचिन्हित दीर्घ flags,
				 क्रमागत key_need_perm need_perm);
बाह्य व्योम key_मुक्त_user_ns(काष्ठा user_namespace *);

अटल अंतरभूत लघु key_पढ़ो_state(स्थिर काष्ठा key *key)
अणु
	/* Barrier versus mark_key_instantiated(). */
	वापस smp_load_acquire(&key->state);
पूर्ण

/**
 * key_is_positive - Determine अगर a key has been positively instantiated
 * @key: The key to check.
 *
 * Return true अगर the specअगरied key has been positively instantiated, false
 * otherwise.
 */
अटल अंतरभूत bool key_is_positive(स्थिर काष्ठा key *key)
अणु
	वापस key_पढ़ो_state(key) == KEY_IS_POSITIVE;
पूर्ण

अटल अंतरभूत bool key_is_negative(स्थिर काष्ठा key *key)
अणु
	वापस key_पढ़ो_state(key) < 0;
पूर्ण

#घोषणा dereference_key_rcu(KEY)					\
	(rcu_dereference((KEY)->payload.rcu_data0))

#घोषणा dereference_key_locked(KEY)					\
	(rcu_dereference_रक्षित((KEY)->payload.rcu_data0,		\
				   rwsem_is_locked(&((काष्ठा key *)(KEY))->sem)))

#घोषणा rcu_assign_keypoपूर्णांकer(KEY, PAYLOAD)				\
करो अणु									\
	rcu_assign_poपूर्णांकer((KEY)->payload.rcu_data0, (PAYLOAD));	\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_SYSCTL
बाह्य काष्ठा ctl_table key_sysctls[];
#पूर्ण_अगर
/*
 * the userspace पूर्णांकerface
 */
बाह्य पूर्णांक install_thपढ़ो_keyring_to_cred(काष्ठा cred *cred);
बाह्य व्योम key_fsuid_changed(काष्ठा cred *new_cred);
बाह्य व्योम key_fsgid_changed(काष्ठा cred *new_cred);
बाह्य व्योम key_init(व्योम);

#अन्यथा /* CONFIG_KEYS */

#घोषणा key_validate(k)			0
#घोषणा key_serial(k)			0
#घोषणा key_get(k) 			(अणु शून्य; पूर्ण)
#घोषणा key_revoke(k)			करो अणु पूर्ण जबतक(0)
#घोषणा key_invalidate(k)		करो अणु पूर्ण जबतक(0)
#घोषणा key_put(k)			करो अणु पूर्ण जबतक(0)
#घोषणा key_ref_put(k)			करो अणु पूर्ण जबतक(0)
#घोषणा make_key_ref(k, p)		शून्य
#घोषणा key_ref_to_ptr(k)		शून्य
#घोषणा is_key_possessed(k)		0
#घोषणा key_fsuid_changed(c)		करो अणु पूर्ण जबतक(0)
#घोषणा key_fsgid_changed(c)		करो अणु पूर्ण जबतक(0)
#घोषणा key_init()			करो अणु पूर्ण जबतक(0)
#घोषणा key_मुक्त_user_ns(ns)		करो अणु पूर्ण जबतक(0)
#घोषणा key_हटाओ_करोमुख्य(d)		करो अणु पूर्ण जबतक(0)

#पूर्ण_अगर /* CONFIG_KEYS */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _LINUX_KEY_H */
