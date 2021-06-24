<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NetLabel System
 *
 * The NetLabel प्रणाली manages अटल and dynamic label mappings क्रम network
 * protocols such as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006, 2008
 */

#अगर_अघोषित _NETLABEL_H
#घोषणा _NETLABEL_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <net/netlink.h>
#समावेश <net/request_sock.h>
#समावेश <linux/refcount.h>

काष्ठा cipso_v4_करोi;
काष्ठा calipso_करोi;

/*
 * NetLabel - A management पूर्णांकerface क्रम मुख्यtaining network packet label
 *            mapping tables क्रम explicit packet labling protocols.
 *
 * Network protocols such as CIPSO and RIPSO require a label translation layer
 * to convert the label on the packet पूर्णांकo something meaningful on the host
 * machine.  In the current Linux implementation these mapping tables live
 * inside the kernel; NetLabel provides a mechanism क्रम user space applications
 * to manage these mapping tables.
 *
 * NetLabel makes use of the Generic NETLINK mechanism as a transport layer to
 * send messages between kernel and user space.  The general क्रमmat of a
 * NetLabel message is shown below:
 *
 *  +-----------------+-------------------+--------- --- -- -
 *  | काष्ठा nlmsghdr | काष्ठा genlmsghdr | payload
 *  +-----------------+-------------------+--------- --- -- -
 *
 * The 'nlmsghdr' and 'genlmsghdr' काष्ठाs should be dealt with like normal.
 * The payload is dependent on the subप्रणाली specअगरied in the
 * 'nlmsghdr->nlmsg_type' and should be defined below, supporting functions
 * should be defined in the corresponding net/netlabel/netlabel_<subsys>.h|c
 * file.  All of the fields in the NetLabel payload are NETLINK attributes, see
 * the include/net/netlink.h file क्रम more inक्रमmation on NETLINK attributes.
 *
 */

/*
 * NetLabel NETLINK protocol
 */

/* NetLabel NETLINK protocol version
 *  1: initial version
 *  2: added अटल labels क्रम unlabeled connections
 *  3: network selectors added to the NetLabel/LSM करोमुख्य mapping and the
 *     CIPSO_V4_MAP_LOCAL CIPSO mapping was added
 */
#घोषणा NETLBL_PROTO_VERSION            3

/* NetLabel NETLINK types/families */
#घोषणा NETLBL_NLTYPE_NONE              0
#घोषणा NETLBL_NLTYPE_MGMT              1
#घोषणा NETLBL_NLTYPE_MGMT_NAME         "NLBL_MGMT"
#घोषणा NETLBL_NLTYPE_RIPSO             2
#घोषणा NETLBL_NLTYPE_RIPSO_NAME        "NLBL_RIPSO"
#घोषणा NETLBL_NLTYPE_CIPSOV4           3
#घोषणा NETLBL_NLTYPE_CIPSOV4_NAME      "NLBL_CIPSOv4"
#घोषणा NETLBL_NLTYPE_CIPSOV6           4
#घोषणा NETLBL_NLTYPE_CIPSOV6_NAME      "NLBL_CIPSOv6"
#घोषणा NETLBL_NLTYPE_UNLABELED         5
#घोषणा NETLBL_NLTYPE_UNLABELED_NAME    "NLBL_UNLBL"
#घोषणा NETLBL_NLTYPE_ADDRSELECT        6
#घोषणा NETLBL_NLTYPE_ADDRSELECT_NAME   "NLBL_ADRSEL"
#घोषणा NETLBL_NLTYPE_CALIPSO           7
#घोषणा NETLBL_NLTYPE_CALIPSO_NAME      "NLBL_CALIPSO"

/*
 * NetLabel - Kernel API क्रम accessing the network packet label mappings.
 *
 * The following functions are provided क्रम use by other kernel modules,
 * specअगरically kernel LSM modules, to provide a consistent, transparent API
 * क्रम dealing with explicit packet labeling protocols such as CIPSO and
 * RIPSO.  The functions defined here are implemented in the
 * net/netlabel/netlabel_kapi.c file.
 *
 */

/* NetLabel audit inक्रमmation */
काष्ठा netlbl_audit अणु
	u32 secid;
	kuid_t loginuid;
	अचिन्हित पूर्णांक sessionid;
पूर्ण;

/*
 * LSM security attributes
 */

/**
 * काष्ठा netlbl_lsm_cache - NetLabel LSM security attribute cache
 * @refcount: atomic reference counter
 * @मुक्त: LSM supplied function to मुक्त the cache data
 * @data: LSM supplied cache data
 *
 * Description:
 * This काष्ठाure is provided क्रम LSMs which wish to make use of the NetLabel
 * caching mechanism to store LSM specअगरic data/attributes in the NetLabel
 * cache.  If the LSM has to perक्रमm a lot of translation from the NetLabel
 * security attributes पूर्णांकo it's own पूर्णांकernal representation then the cache
 * mechanism can provide a way to eliminate some or all of that translation
 * overhead on a cache hit.
 *
 */
काष्ठा netlbl_lsm_cache अणु
	refcount_t refcount;
	व्योम (*मुक्त) (स्थिर व्योम *data);
	व्योम *data;
पूर्ण;

/**
 * काष्ठा netlbl_lsm_caपंचांगap - NetLabel LSM secattr category biपंचांगap
 * @startbit: the value of the lowest order bit in the biपंचांगap
 * @biपंचांगap: the category biपंचांगap
 * @next: poपूर्णांकer to the next biपंचांगap "node" or शून्य
 *
 * Description:
 * This काष्ठाure is used to represent category biपंचांगaps.  Due to the large
 * number of categories supported by most labeling protocols it is not
 * practical to transfer a full biपंचांगap पूर्णांकernally so NetLabel aकरोpts a sparse
 * biपंचांगap काष्ठाure modeled after SELinux's ebiपंचांगap काष्ठाure.
 * The caपंचांगap biपंचांगap field MUST be a घातer of two in length and large
 * enough to hold at least 240 bits.  Special care (i.e. check the code!)
 * should be used when changing these values as the LSM implementation
 * probably has functions which rely on the sizes of these types to speed
 * processing.
 *
 */
#घोषणा NETLBL_CATMAP_MAPTYPE           u64
#घोषणा NETLBL_CATMAP_MAPCNT            4
#घोषणा NETLBL_CATMAP_MAPSIZE           (माप(NETLBL_CATMAP_MAPTYPE) * 8)
#घोषणा NETLBL_CATMAP_SIZE              (NETLBL_CATMAP_MAPSIZE * \
					 NETLBL_CATMAP_MAPCNT)
#घोषणा NETLBL_CATMAP_BIT               (NETLBL_CATMAP_MAPTYPE)0x01
काष्ठा netlbl_lsm_caपंचांगap अणु
	u32 startbit;
	NETLBL_CATMAP_MAPTYPE biपंचांगap[NETLBL_CATMAP_MAPCNT];
	काष्ठा netlbl_lsm_caपंचांगap *next;
पूर्ण;

/**
 * काष्ठा netlbl_lsm_secattr - NetLabel LSM security attributes
 * @flags: indicate काष्ठाure attributes, see NETLBL_SECATTR_*
 * @type: indicate the NLTYPE of the attributes
 * @करोमुख्य: the NetLabel LSM करोमुख्य
 * @cache: NetLabel LSM specअगरic cache
 * @attr.mls: MLS sensitivity label
 * @attr.mls.cat: MLS category biपंचांगap
 * @attr.mls.lvl: MLS sensitivity level
 * @attr.secid: LSM specअगरic secid token
 *
 * Description:
 * This काष्ठाure is used to pass security attributes between NetLabel and the
 * LSM modules.  The flags field is used to specअगरy which fields within the
 * काष्ठा are valid and valid values can be created by bitwise OR'ing the
 * NETLBL_SECATTR_* defines.  The करोमुख्य field is typically set by the LSM to
 * specअगरy करोमुख्य specअगरic configuration settings and is not usually used by
 * NetLabel itself when वापसing security attributes to the LSM.
 *
 */
काष्ठा netlbl_lsm_secattr अणु
	u32 flags;
	/* biपंचांगap values क्रम 'flags' */
#घोषणा NETLBL_SECATTR_NONE             0x00000000
#घोषणा NETLBL_SECATTR_DOMAIN           0x00000001
#घोषणा NETLBL_SECATTR_DOMAIN_CPY       (NETLBL_SECATTR_DOMAIN | \
					 NETLBL_SECATTR_FREE_DOMAIN)
#घोषणा NETLBL_SECATTR_CACHE            0x00000002
#घोषणा NETLBL_SECATTR_MLS_LVL          0x00000004
#घोषणा NETLBL_SECATTR_MLS_CAT          0x00000008
#घोषणा NETLBL_SECATTR_SECID            0x00000010
	/* biपंचांगap meta-values क्रम 'flags' */
#घोषणा NETLBL_SECATTR_FREE_DOMAIN      0x01000000
#घोषणा NETLBL_SECATTR_CACHEABLE        (NETLBL_SECATTR_MLS_LVL | \
					 NETLBL_SECATTR_MLS_CAT | \
					 NETLBL_SECATTR_SECID)
	u32 type;
	अक्षर *करोमुख्य;
	काष्ठा netlbl_lsm_cache *cache;
	काष्ठा अणु
		काष्ठा अणु
			काष्ठा netlbl_lsm_caपंचांगap *cat;
			u32 lvl;
		पूर्ण mls;
		u32 secid;
	पूर्ण attr;
पूर्ण;

/**
 * काष्ठा netlbl_calipso_ops - NetLabel CALIPSO operations
 * @करोi_add: add a CALIPSO DOI
 * @करोi_मुक्त: मुक्त a CALIPSO DOI
 * @करोi_getdef: वापसs a reference to a DOI
 * @करोi_putdef: releases a reference of a DOI
 * @करोi_walk: क्रमागतerate the DOI list
 * @sock_getattr: retrieve the socket's attr
 * @sock_setattr: set the socket's attr
 * @sock_delattr: हटाओ the socket's attr
 * @req_setattr: set the req socket's attr
 * @req_delattr: हटाओ the req socket's attr
 * @opt_getattr: retrieve attr from memory block
 * @skbuff_optptr: find option in packet
 * @skbuff_setattr: set the skbuff's attr
 * @skbuff_delattr: हटाओ the skbuff's attr
 * @cache_invalidate: invalidate cache
 * @cache_add: add cache entry
 *
 * Description:
 * This काष्ठाure is filled out by the CALIPSO engine and passed
 * to the NetLabel core via a call to netlbl_calipso_ops_रेजिस्टर().
 * It enables the CALIPSO engine (and hence IPv6) to be compiled
 * as a module.
 */
काष्ठा netlbl_calipso_ops अणु
	पूर्णांक (*करोi_add)(काष्ठा calipso_करोi *करोi_def,
		       काष्ठा netlbl_audit *audit_info);
	व्योम (*करोi_मुक्त)(काष्ठा calipso_करोi *करोi_def);
	पूर्णांक (*करोi_हटाओ)(u32 करोi, काष्ठा netlbl_audit *audit_info);
	काष्ठा calipso_करोi *(*करोi_getdef)(u32 करोi);
	व्योम (*करोi_putdef)(काष्ठा calipso_करोi *करोi_def);
	पूर्णांक (*करोi_walk)(u32 *skip_cnt,
			पूर्णांक (*callback)(काष्ठा calipso_करोi *करोi_def, व्योम *arg),
			व्योम *cb_arg);
	पूर्णांक (*sock_getattr)(काष्ठा sock *sk,
			    काष्ठा netlbl_lsm_secattr *secattr);
	पूर्णांक (*sock_setattr)(काष्ठा sock *sk,
			    स्थिर काष्ठा calipso_करोi *करोi_def,
			    स्थिर काष्ठा netlbl_lsm_secattr *secattr);
	व्योम (*sock_delattr)(काष्ठा sock *sk);
	पूर्णांक (*req_setattr)(काष्ठा request_sock *req,
			   स्थिर काष्ठा calipso_करोi *करोi_def,
			   स्थिर काष्ठा netlbl_lsm_secattr *secattr);
	व्योम (*req_delattr)(काष्ठा request_sock *req);
	पूर्णांक (*opt_getattr)(स्थिर अचिन्हित अक्षर *calipso,
			   काष्ठा netlbl_lsm_secattr *secattr);
	अचिन्हित अक्षर *(*skbuff_optptr)(स्थिर काष्ठा sk_buff *skb);
	पूर्णांक (*skbuff_setattr)(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा calipso_करोi *करोi_def,
			      स्थिर काष्ठा netlbl_lsm_secattr *secattr);
	पूर्णांक (*skbuff_delattr)(काष्ठा sk_buff *skb);
	व्योम (*cache_invalidate)(व्योम);
	पूर्णांक (*cache_add)(स्थिर अचिन्हित अक्षर *calipso_ptr,
			 स्थिर काष्ठा netlbl_lsm_secattr *secattr);
पूर्ण;

/*
 * LSM security attribute operations (अंतरभूत)
 */

/**
 * netlbl_secattr_cache_alloc - Allocate and initialize a secattr cache
 * @flags: the memory allocation flags
 *
 * Description:
 * Allocate and initialize a netlbl_lsm_cache काष्ठाure.  Returns a poपूर्णांकer
 * on success, शून्य on failure.
 *
 */
अटल अंतरभूत काष्ठा netlbl_lsm_cache *netlbl_secattr_cache_alloc(gfp_t flags)
अणु
	काष्ठा netlbl_lsm_cache *cache;

	cache = kzalloc(माप(*cache), flags);
	अगर (cache)
		refcount_set(&cache->refcount, 1);
	वापस cache;
पूर्ण

/**
 * netlbl_secattr_cache_मुक्त - Frees a netlbl_lsm_cache काष्ठा
 * @cache: the काष्ठा to मुक्त
 *
 * Description:
 * Frees @secattr including all of the पूर्णांकernal buffers.
 *
 */
अटल अंतरभूत व्योम netlbl_secattr_cache_मुक्त(काष्ठा netlbl_lsm_cache *cache)
अणु
	अगर (!refcount_dec_and_test(&cache->refcount))
		वापस;

	अगर (cache->मुक्त)
		cache->मुक्त(cache->data);
	kमुक्त(cache);
पूर्ण

/**
 * netlbl_caपंचांगap_alloc - Allocate a LSM secattr caपंचांगap
 * @flags: memory allocation flags
 *
 * Description:
 * Allocate memory क्रम a LSM secattr caपंचांगap, वापसs a poपूर्णांकer on success, शून्य
 * on failure.
 *
 */
अटल अंतरभूत काष्ठा netlbl_lsm_caपंचांगap *netlbl_caपंचांगap_alloc(gfp_t flags)
अणु
	वापस kzalloc(माप(काष्ठा netlbl_lsm_caपंचांगap), flags);
पूर्ण

/**
 * netlbl_caपंचांगap_मुक्त - Free a LSM secattr caपंचांगap
 * @caपंचांगap: the category biपंचांगap
 *
 * Description:
 * Free a LSM secattr caपंचांगap.
 *
 */
अटल अंतरभूत व्योम netlbl_caपंचांगap_मुक्त(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap)
अणु
	काष्ठा netlbl_lsm_caपंचांगap *iter;

	जबतक (caपंचांगap) अणु
		iter = caपंचांगap;
		caपंचांगap = caपंचांगap->next;
		kमुक्त(iter);
	पूर्ण
पूर्ण

/**
 * netlbl_secattr_init - Initialize a netlbl_lsm_secattr काष्ठा
 * @secattr: the काष्ठा to initialize
 *
 * Description:
 * Initialize an alपढ़ोy allocated netlbl_lsm_secattr काष्ठा.
 *
 */
अटल अंतरभूत व्योम netlbl_secattr_init(काष्ठा netlbl_lsm_secattr *secattr)
अणु
	स_रखो(secattr, 0, माप(*secattr));
पूर्ण

/**
 * netlbl_secattr_destroy - Clears a netlbl_lsm_secattr काष्ठा
 * @secattr: the काष्ठा to clear
 *
 * Description:
 * Destroys the @secattr काष्ठा, including मुक्तing all of the पूर्णांकernal buffers.
 * The काष्ठा must be reset with a call to netlbl_secattr_init() beक्रमe reuse.
 *
 */
अटल अंतरभूत व्योम netlbl_secattr_destroy(काष्ठा netlbl_lsm_secattr *secattr)
अणु
	अगर (secattr->flags & NETLBL_SECATTR_FREE_DOMAIN)
		kमुक्त(secattr->करोमुख्य);
	अगर (secattr->flags & NETLBL_SECATTR_CACHE)
		netlbl_secattr_cache_मुक्त(secattr->cache);
	अगर (secattr->flags & NETLBL_SECATTR_MLS_CAT)
		netlbl_caपंचांगap_मुक्त(secattr->attr.mls.cat);
पूर्ण

/**
 * netlbl_secattr_alloc - Allocate and initialize a netlbl_lsm_secattr काष्ठा
 * @flags: the memory allocation flags
 *
 * Description:
 * Allocate and initialize a netlbl_lsm_secattr काष्ठा.  Returns a valid
 * poपूर्णांकer on success, or शून्य on failure.
 *
 */
अटल अंतरभूत काष्ठा netlbl_lsm_secattr *netlbl_secattr_alloc(gfp_t flags)
अणु
	वापस kzalloc(माप(काष्ठा netlbl_lsm_secattr), flags);
पूर्ण

/**
 * netlbl_secattr_मुक्त - Frees a netlbl_lsm_secattr काष्ठा
 * @secattr: the काष्ठा to मुक्त
 *
 * Description:
 * Frees @secattr including all of the पूर्णांकernal buffers.
 *
 */
अटल अंतरभूत व्योम netlbl_secattr_मुक्त(काष्ठा netlbl_lsm_secattr *secattr)
अणु
	netlbl_secattr_destroy(secattr);
	kमुक्त(secattr);
पूर्ण

#अगर_घोषित CONFIG_NETLABEL
/*
 * LSM configuration operations
 */
पूर्णांक netlbl_cfg_map_del(स्थिर अक्षर *करोमुख्य,
		       u16 family,
		       स्थिर व्योम *addr,
		       स्थिर व्योम *mask,
		       काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_cfg_unlbl_map_add(स्थिर अक्षर *करोमुख्य,
			     u16 family,
			     स्थिर व्योम *addr,
			     स्थिर व्योम *mask,
			     काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_cfg_unlbl_अटल_add(काष्ठा net *net,
				स्थिर अक्षर *dev_name,
				स्थिर व्योम *addr,
				स्थिर व्योम *mask,
				u16 family,
				u32 secid,
				काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_cfg_unlbl_अटल_del(काष्ठा net *net,
				स्थिर अक्षर *dev_name,
				स्थिर व्योम *addr,
				स्थिर व्योम *mask,
				u16 family,
				काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_cfg_cipsov4_add(काष्ठा cipso_v4_करोi *करोi_def,
			   काष्ठा netlbl_audit *audit_info);
व्योम netlbl_cfg_cipsov4_del(u32 करोi, काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_cfg_cipsov4_map_add(u32 करोi,
			       स्थिर अक्षर *करोमुख्य,
			       स्थिर काष्ठा in_addr *addr,
			       स्थिर काष्ठा in_addr *mask,
			       काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_cfg_calipso_add(काष्ठा calipso_करोi *करोi_def,
			   काष्ठा netlbl_audit *audit_info);
व्योम netlbl_cfg_calipso_del(u32 करोi, काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_cfg_calipso_map_add(u32 करोi,
			       स्थिर अक्षर *करोमुख्य,
			       स्थिर काष्ठा in6_addr *addr,
			       स्थिर काष्ठा in6_addr *mask,
			       काष्ठा netlbl_audit *audit_info);
/*
 * LSM security attribute operations
 */
पूर्णांक netlbl_caपंचांगap_walk(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap, u32 offset);
पूर्णांक netlbl_caपंचांगap_walkrng(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap, u32 offset);
पूर्णांक netlbl_caपंचांगap_getदीर्घ(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap,
			  u32 *offset,
			  अचिन्हित दीर्घ *biपंचांगap);
पूर्णांक netlbl_caपंचांगap_setbit(काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
			 u32 bit,
			 gfp_t flags);
पूर्णांक netlbl_caपंचांगap_setrng(काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
			 u32 start,
			 u32 end,
			 gfp_t flags);
पूर्णांक netlbl_caपंचांगap_setदीर्घ(काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
			  u32 offset,
			  अचिन्हित दीर्घ biपंचांगap,
			  gfp_t flags);

/* Biपंचांगap functions
 */
पूर्णांक netlbl_biपंचांगap_walk(स्थिर अचिन्हित अक्षर *biपंचांगap, u32 biपंचांगap_len,
		       u32 offset, u8 state);
व्योम netlbl_biपंचांगap_setbit(अचिन्हित अक्षर *biपंचांगap, u32 bit, u8 state);

/*
 * LSM protocol operations (NetLabel LSM/kernel API)
 */
पूर्णांक netlbl_enabled(व्योम);
पूर्णांक netlbl_sock_setattr(काष्ठा sock *sk,
			u16 family,
			स्थिर काष्ठा netlbl_lsm_secattr *secattr);
व्योम netlbl_sock_delattr(काष्ठा sock *sk);
पूर्णांक netlbl_sock_getattr(काष्ठा sock *sk,
			काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक netlbl_conn_setattr(काष्ठा sock *sk,
			काष्ठा sockaddr *addr,
			स्थिर काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक netlbl_req_setattr(काष्ठा request_sock *req,
		       स्थिर काष्ठा netlbl_lsm_secattr *secattr);
व्योम netlbl_req_delattr(काष्ठा request_sock *req);
पूर्णांक netlbl_skbuff_setattr(काष्ठा sk_buff *skb,
			  u16 family,
			  स्थिर काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक netlbl_skbuff_getattr(स्थिर काष्ठा sk_buff *skb,
			  u16 family,
			  काष्ठा netlbl_lsm_secattr *secattr);
व्योम netlbl_skbuff_err(काष्ठा sk_buff *skb, u16 family, पूर्णांक error, पूर्णांक gateway);

/*
 * LSM label mapping cache operations
 */
व्योम netlbl_cache_invalidate(व्योम);
पूर्णांक netlbl_cache_add(स्थिर काष्ठा sk_buff *skb, u16 family,
		     स्थिर काष्ठा netlbl_lsm_secattr *secattr);

/*
 * Protocol engine operations
 */
काष्ठा audit_buffer *netlbl_audit_start(पूर्णांक type,
					काष्ठा netlbl_audit *audit_info);
#अन्यथा
अटल अंतरभूत पूर्णांक netlbl_cfg_map_del(स्थिर अक्षर *करोमुख्य,
				     u16 family,
				     स्थिर व्योम *addr,
				     स्थिर व्योम *mask,
				     काष्ठा netlbl_audit *audit_info)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_cfg_unlbl_map_add(स्थिर अक्षर *करोमुख्य,
					   u16 family,
					   व्योम *addr,
					   व्योम *mask,
					   काष्ठा netlbl_audit *audit_info)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_cfg_unlbl_अटल_add(काष्ठा net *net,
					      स्थिर अक्षर *dev_name,
					      स्थिर व्योम *addr,
					      स्थिर व्योम *mask,
					      u16 family,
					      u32 secid,
					      काष्ठा netlbl_audit *audit_info)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_cfg_unlbl_अटल_del(काष्ठा net *net,
					      स्थिर अक्षर *dev_name,
					      स्थिर व्योम *addr,
					      स्थिर व्योम *mask,
					      u16 family,
					      काष्ठा netlbl_audit *audit_info)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_cfg_cipsov4_add(काष्ठा cipso_v4_करोi *करोi_def,
					 काष्ठा netlbl_audit *audit_info)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम netlbl_cfg_cipsov4_del(u32 करोi,
					  काष्ठा netlbl_audit *audit_info)
अणु
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_cfg_cipsov4_map_add(u32 करोi,
					     स्थिर अक्षर *करोमुख्य,
					     स्थिर काष्ठा in_addr *addr,
					     स्थिर काष्ठा in_addr *mask,
					     काष्ठा netlbl_audit *audit_info)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_cfg_calipso_add(काष्ठा calipso_करोi *करोi_def,
					 काष्ठा netlbl_audit *audit_info)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम netlbl_cfg_calipso_del(u32 करोi,
					  काष्ठा netlbl_audit *audit_info)
अणु
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_cfg_calipso_map_add(u32 करोi,
					     स्थिर अक्षर *करोमुख्य,
					     स्थिर काष्ठा in6_addr *addr,
					     स्थिर काष्ठा in6_addr *mask,
					     काष्ठा netlbl_audit *audit_info)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_caपंचांगap_walk(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap,
				     u32 offset)
अणु
	वापस -ENOENT;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_caपंचांगap_walkrng(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap,
					u32 offset)
अणु
	वापस -ENOENT;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_caपंचांगap_getदीर्घ(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap,
					u32 *offset,
					अचिन्हित दीर्घ *biपंचांगap)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_caपंचांगap_setbit(काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
				       u32 bit,
				       gfp_t flags)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_caपंचांगap_setrng(काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
				       u32 start,
				       u32 end,
				       gfp_t flags)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_caपंचांगap_setदीर्घ(काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
					u32 offset,
					अचिन्हित दीर्घ biपंचांगap,
					gfp_t flags)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_enabled(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_sock_setattr(काष्ठा sock *sk,
				      u16 family,
				      स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम netlbl_sock_delattr(काष्ठा sock *sk)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_sock_getattr(काष्ठा sock *sk,
				      काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_conn_setattr(काष्ठा sock *sk,
				      काष्ठा sockaddr *addr,
				      स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_req_setattr(काष्ठा request_sock *req,
				     स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम netlbl_req_delattr(काष्ठा request_sock *req)
अणु
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_skbuff_setattr(काष्ठा sk_buff *skb,
				      u16 family,
				      स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_skbuff_getattr(स्थिर काष्ठा sk_buff *skb,
					u16 family,
					काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम netlbl_skbuff_err(काष्ठा sk_buff *skb,
				     पूर्णांक error,
				     पूर्णांक gateway)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम netlbl_cache_invalidate(व्योम)
अणु
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक netlbl_cache_add(स्थिर काष्ठा sk_buff *skb, u16 family,
				   स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा audit_buffer *netlbl_audit_start(पूर्णांक type,
						काष्ठा netlbl_audit *audit_info)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */

स्थिर काष्ठा netlbl_calipso_ops *
netlbl_calipso_ops_रेजिस्टर(स्थिर काष्ठा netlbl_calipso_ops *ops);

#पूर्ण_अगर /* _NETLABEL_H */
