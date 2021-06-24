<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * net/tipc/crypto.c: TIPC crypto क्रम key handling & packet en/decryption
 *
 * Copyright (c) 2019, Ericsson AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <crypto/aead.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/rng.h>
#समावेश "crypto.h"
#समावेश "msg.h"
#समावेश "bcast.h"

#घोषणा TIPC_TX_GRACE_PERIOD	msecs_to_jअगरfies(5000) /* 5s */
#घोषणा TIPC_TX_LASTING_TIME	msecs_to_jअगरfies(10000) /* 10s */
#घोषणा TIPC_RX_ACTIVE_LIM	msecs_to_jअगरfies(3000) /* 3s */
#घोषणा TIPC_RX_PASSIVE_LIM	msecs_to_jअगरfies(15000) /* 15s */

#घोषणा TIPC_MAX_TFMS_DEF	10
#घोषणा TIPC_MAX_TFMS_LIM	1000

#घोषणा TIPC_REKEYING_INTV_DEF	(60 * 24) /* शेष: 1 day */

/*
 * TIPC Key ids
 */
क्रमागत अणु
	KEY_MASTER = 0,
	KEY_MIN = KEY_MASTER,
	KEY_1 = 1,
	KEY_2,
	KEY_3,
	KEY_MAX = KEY_3,
पूर्ण;

/*
 * TIPC Crypto statistics
 */
क्रमागत अणु
	STAT_OK,
	STAT_NOK,
	STAT_ASYNC,
	STAT_ASYNC_OK,
	STAT_ASYNC_NOK,
	STAT_BADKEYS, /* tx only */
	STAT_BADMSGS = STAT_BADKEYS, /* rx only */
	STAT_NOKEYS,
	STAT_SWITCHES,

	MAX_STATS,
पूर्ण;

/* TIPC crypto statistics' header */
अटल स्थिर अक्षर *hstats[MAX_STATS] = अणु"ok", "nok", "async", "async_ok",
					"async_nok", "badmsgs", "nokeys",
					"switches"पूर्ण;

/* Max TFMs number per key */
पूर्णांक sysctl_tipc_max_tfms __पढ़ो_mostly = TIPC_MAX_TFMS_DEF;
/* Key exchange चयन, शेष: on */
पूर्णांक sysctl_tipc_key_exchange_enabled __पढ़ो_mostly = 1;

/*
 * काष्ठा tipc_key - TIPC keys' status indicator
 *
 *         7     6     5     4     3     2     1     0
 *      +-----+-----+-----+-----+-----+-----+-----+-----+
 * key: | (reserved)|passive idx| active idx|pending idx|
 *      +-----+-----+-----+-----+-----+-----+-----+-----+
 */
काष्ठा tipc_key अणु
#घोषणा KEY_BITS (2)
#घोषणा KEY_MASK ((1 << KEY_BITS) - 1)
	जोड़ अणु
		काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
			u8 pending:2,
			   active:2,
			   passive:2, /* rx only */
			   reserved:2;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
			u8 reserved:2,
			   passive:2, /* rx only */
			   active:2,
			   pending:2;
#अन्यथा
#त्रुटि  "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
		पूर्ण __packed;
		u8 keys;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा tipc_tfm - TIPC TFM काष्ठाure to क्रमm a list of TFMs
 * @tfm: cipher handle/key
 * @list: linked list of TFMs
 */
काष्ठा tipc_tfm अणु
	काष्ठा crypto_aead *tfm;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा tipc_aead - TIPC AEAD key काष्ठाure
 * @tfm_entry: per-cpu poपूर्णांकer to one entry in TFM list
 * @crypto: TIPC crypto owns this key
 * @cloned: reference to the source key in हाल cloning
 * @users: the number of the key users (TX/RX)
 * @salt: the key's SALT value
 * @authsize: authentication tag size (max = 16)
 * @mode: crypto mode is applied to the key
 * @hपूर्णांक: a hपूर्णांक क्रम user key
 * @rcu: काष्ठा rcu_head
 * @key: the aead key
 * @gen: the key's generation
 * @seqno: the key seqno (cluster scope)
 * @refcnt: the key reference counter
 */
काष्ठा tipc_aead अणु
#घोषणा TIPC_AEAD_HINT_LEN (5)
	काष्ठा tipc_tfm * __percpu *tfm_entry;
	काष्ठा tipc_crypto *crypto;
	काष्ठा tipc_aead *cloned;
	atomic_t users;
	u32 salt;
	u8 authsize;
	u8 mode;
	अक्षर hपूर्णांक[2 * TIPC_AEAD_HINT_LEN + 1];
	काष्ठा rcu_head rcu;
	काष्ठा tipc_aead_key *key;
	u16 gen;

	atomic64_t seqno ____cacheline_aligned;
	refcount_t refcnt ____cacheline_aligned;

पूर्ण ____cacheline_aligned;

/**
 * काष्ठा tipc_crypto_stats - TIPC Crypto statistics
 * @stat: array of crypto statistics
 */
काष्ठा tipc_crypto_stats अणु
	अचिन्हित पूर्णांक stat[MAX_STATS];
पूर्ण;

/**
 * काष्ठा tipc_crypto - TIPC TX/RX crypto काष्ठाure
 * @net: काष्ठा net
 * @node: TIPC node (RX)
 * @aead: array of poपूर्णांकers to AEAD keys क्रम encryption/decryption
 * @peer_rx_active: replicated peer RX active key index
 * @key_gen: TX/RX key generation
 * @key: the key states
 * @skey_mode: session key's mode
 * @skey: received session key
 * @wq: common workqueue on TX crypto
 * @work: delayed work sched क्रम TX/RX
 * @key_distr: key distributing state
 * @rekeying_पूर्णांकv: rekeying पूर्णांकerval (in minutes)
 * @stats: the crypto statistics
 * @name: the crypto name
 * @sndnxt: the per-peer sndnxt (TX)
 * @समयr1: general समयr 1 (jअगरfies)
 * @समयr2: general समयr 2 (jअगरfies)
 * @working: the crypto is working or not
 * @key_master: flag indicates अगर master key exists
 * @legacy_user: flag indicates अगर a peer joins w/o master key (क्रम bwd comp.)
 * @nokey: no key indication
 * @flags: combined flags field
 * @lock: tipc_key lock
 */
काष्ठा tipc_crypto अणु
	काष्ठा net *net;
	काष्ठा tipc_node *node;
	काष्ठा tipc_aead __rcu *aead[KEY_MAX + 1];
	atomic_t peer_rx_active;
	u16 key_gen;
	काष्ठा tipc_key key;
	u8 skey_mode;
	काष्ठा tipc_aead_key *skey;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा delayed_work work;
#घोषणा KEY_DISTR_SCHED		1
#घोषणा KEY_DISTR_COMPL		2
	atomic_t key_distr;
	u32 rekeying_पूर्णांकv;

	काष्ठा tipc_crypto_stats __percpu *stats;
	अक्षर name[48];

	atomic64_t sndnxt ____cacheline_aligned;
	अचिन्हित दीर्घ समयr1;
	अचिन्हित दीर्घ समयr2;
	जोड़ अणु
		काष्ठा अणु
			u8 working:1;
			u8 key_master:1;
			u8 legacy_user:1;
			u8 nokey: 1;
		पूर्ण;
		u8 flags;
	पूर्ण;
	spinlock_t lock; /* crypto lock */

पूर्ण ____cacheline_aligned;

/* काष्ठा tipc_crypto_tx_ctx - TX context क्रम callbacks */
काष्ठा tipc_crypto_tx_ctx अणु
	काष्ठा tipc_aead *aead;
	काष्ठा tipc_bearer *bearer;
	काष्ठा tipc_media_addr dst;
पूर्ण;

/* काष्ठा tipc_crypto_rx_ctx - RX context क्रम callbacks */
काष्ठा tipc_crypto_rx_ctx अणु
	काष्ठा tipc_aead *aead;
	काष्ठा tipc_bearer *bearer;
पूर्ण;

अटल काष्ठा tipc_aead *tipc_aead_get(काष्ठा tipc_aead __rcu *aead);
अटल अंतरभूत व्योम tipc_aead_put(काष्ठा tipc_aead *aead);
अटल व्योम tipc_aead_मुक्त(काष्ठा rcu_head *rp);
अटल पूर्णांक tipc_aead_users(काष्ठा tipc_aead __rcu *aead);
अटल व्योम tipc_aead_users_inc(काष्ठा tipc_aead __rcu *aead, पूर्णांक lim);
अटल व्योम tipc_aead_users_dec(काष्ठा tipc_aead __rcu *aead, पूर्णांक lim);
अटल व्योम tipc_aead_users_set(काष्ठा tipc_aead __rcu *aead, पूर्णांक val);
अटल काष्ठा crypto_aead *tipc_aead_tfm_next(काष्ठा tipc_aead *aead);
अटल पूर्णांक tipc_aead_init(काष्ठा tipc_aead **aead, काष्ठा tipc_aead_key *ukey,
			  u8 mode);
अटल पूर्णांक tipc_aead_clone(काष्ठा tipc_aead **dst, काष्ठा tipc_aead *src);
अटल व्योम *tipc_aead_mem_alloc(काष्ठा crypto_aead *tfm,
				 अचिन्हित पूर्णांक crypto_ctx_size,
				 u8 **iv, काष्ठा aead_request **req,
				 काष्ठा scatterlist **sg, पूर्णांक nsg);
अटल पूर्णांक tipc_aead_encrypt(काष्ठा tipc_aead *aead, काष्ठा sk_buff *skb,
			     काष्ठा tipc_bearer *b,
			     काष्ठा tipc_media_addr *dst,
			     काष्ठा tipc_node *__dnode);
अटल व्योम tipc_aead_encrypt_करोne(काष्ठा crypto_async_request *base, पूर्णांक err);
अटल पूर्णांक tipc_aead_decrypt(काष्ठा net *net, काष्ठा tipc_aead *aead,
			     काष्ठा sk_buff *skb, काष्ठा tipc_bearer *b);
अटल व्योम tipc_aead_decrypt_करोne(काष्ठा crypto_async_request *base, पूर्णांक err);
अटल अंतरभूत पूर्णांक tipc_ehdr_size(काष्ठा tipc_ehdr *ehdr);
अटल पूर्णांक tipc_ehdr_build(काष्ठा net *net, काष्ठा tipc_aead *aead,
			   u8 tx_key, काष्ठा sk_buff *skb,
			   काष्ठा tipc_crypto *__rx);
अटल अंतरभूत व्योम tipc_crypto_key_set_state(काष्ठा tipc_crypto *c,
					     u8 new_passive,
					     u8 new_active,
					     u8 new_pending);
अटल पूर्णांक tipc_crypto_key_attach(काष्ठा tipc_crypto *c,
				  काष्ठा tipc_aead *aead, u8 pos,
				  bool master_key);
अटल bool tipc_crypto_key_try_align(काष्ठा tipc_crypto *rx, u8 new_pending);
अटल काष्ठा tipc_aead *tipc_crypto_key_pick_tx(काष्ठा tipc_crypto *tx,
						 काष्ठा tipc_crypto *rx,
						 काष्ठा sk_buff *skb,
						 u8 tx_key);
अटल व्योम tipc_crypto_key_synch(काष्ठा tipc_crypto *rx, काष्ठा sk_buff *skb);
अटल पूर्णांक tipc_crypto_key_revoke(काष्ठा net *net, u8 tx_key);
अटल अंतरभूत व्योम tipc_crypto_clone_msg(काष्ठा net *net, काष्ठा sk_buff *_skb,
					 काष्ठा tipc_bearer *b,
					 काष्ठा tipc_media_addr *dst,
					 काष्ठा tipc_node *__dnode, u8 type);
अटल व्योम tipc_crypto_rcv_complete(काष्ठा net *net, काष्ठा tipc_aead *aead,
				     काष्ठा tipc_bearer *b,
				     काष्ठा sk_buff **skb, पूर्णांक err);
अटल व्योम tipc_crypto_करो_cmd(काष्ठा net *net, पूर्णांक cmd);
अटल अक्षर *tipc_crypto_key_dump(काष्ठा tipc_crypto *c, अक्षर *buf);
अटल अक्षर *tipc_key_change_dump(काष्ठा tipc_key old, काष्ठा tipc_key new,
				  अक्षर *buf);
अटल पूर्णांक tipc_crypto_key_xmit(काष्ठा net *net, काष्ठा tipc_aead_key *skey,
				u16 gen, u8 mode, u32 dnode);
अटल bool tipc_crypto_key_rcv(काष्ठा tipc_crypto *rx, काष्ठा tipc_msg *hdr);
अटल व्योम tipc_crypto_work_tx(काष्ठा work_काष्ठा *work);
अटल व्योम tipc_crypto_work_rx(काष्ठा work_काष्ठा *work);
अटल पूर्णांक tipc_aead_key_generate(काष्ठा tipc_aead_key *skey);

#घोषणा is_tx(crypto) (!(crypto)->node)
#घोषणा is_rx(crypto) (!is_tx(crypto))

#घोषणा key_next(cur) ((cur) % KEY_MAX + 1)

#घोषणा tipc_aead_rcu_ptr(rcu_ptr, lock)				\
	rcu_dereference_रक्षित((rcu_ptr), lockdep_is_held(lock))

#घोषणा tipc_aead_rcu_replace(rcu_ptr, ptr, lock)			\
करो अणु									\
	काष्ठा tipc_aead *__पंचांगp = rcu_dereference_रक्षित((rcu_ptr),	\
						lockdep_is_held(lock));	\
	rcu_assign_poपूर्णांकer((rcu_ptr), (ptr));				\
	tipc_aead_put(__पंचांगp);						\
पूर्ण जबतक (0)

#घोषणा tipc_crypto_key_detach(rcu_ptr, lock)				\
	tipc_aead_rcu_replace((rcu_ptr), शून्य, lock)

/**
 * tipc_aead_key_validate - Validate a AEAD user key
 * @ukey: poपूर्णांकer to user key data
 * @info: netlink info poपूर्णांकer
 */
पूर्णांक tipc_aead_key_validate(काष्ठा tipc_aead_key *ukey, काष्ठा genl_info *info)
अणु
	पूर्णांक keylen;

	/* Check अगर algorithm exists */
	अगर (unlikely(!crypto_has_alg(ukey->alg_name, 0, 0))) अणु
		GENL_SET_ERR_MSG(info, "unable to load the algorithm (module existed?)");
		वापस -ENODEV;
	पूर्ण

	/* Currently, we only support the "gcm(aes)" cipher algorithm */
	अगर (म_भेद(ukey->alg_name, "gcm(aes)")) अणु
		GENL_SET_ERR_MSG(info, "not supported yet the algorithm");
		वापस -ENOTSUPP;
	पूर्ण

	/* Check अगर key size is correct */
	keylen = ukey->keylen - TIPC_AES_GCM_SALT_SIZE;
	अगर (unlikely(keylen != TIPC_AES_GCM_KEY_SIZE_128 &&
		     keylen != TIPC_AES_GCM_KEY_SIZE_192 &&
		     keylen != TIPC_AES_GCM_KEY_SIZE_256)) अणु
		GENL_SET_ERR_MSG(info, "incorrect key length (20, 28 or 36 octets?)");
		वापस -EKEYREJECTED;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tipc_aead_key_generate - Generate new session key
 * @skey: input/output key with new content
 *
 * Return: 0 in हाल of success, otherwise < 0
 */
अटल पूर्णांक tipc_aead_key_generate(काष्ठा tipc_aead_key *skey)
अणु
	पूर्णांक rc = 0;

	/* Fill the key's content with a अक्रमom value via RNG cipher */
	rc = crypto_get_शेष_rng();
	अगर (likely(!rc)) अणु
		rc = crypto_rng_get_bytes(crypto_शेष_rng, skey->key,
					  skey->keylen);
		crypto_put_शेष_rng();
	पूर्ण

	वापस rc;
पूर्ण

अटल काष्ठा tipc_aead *tipc_aead_get(काष्ठा tipc_aead __rcu *aead)
अणु
	काष्ठा tipc_aead *पंचांगp;

	rcu_पढ़ो_lock();
	पंचांगp = rcu_dereference(aead);
	अगर (unlikely(!पंचांगp || !refcount_inc_not_zero(&पंचांगp->refcnt)))
		पंचांगp = शून्य;
	rcu_पढ़ो_unlock();

	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम tipc_aead_put(काष्ठा tipc_aead *aead)
अणु
	अगर (aead && refcount_dec_and_test(&aead->refcnt))
		call_rcu(&aead->rcu, tipc_aead_मुक्त);
पूर्ण

/**
 * tipc_aead_मुक्त - Release AEAD key incl. all the TFMs in the list
 * @rp: rcu head poपूर्णांकer
 */
अटल व्योम tipc_aead_मुक्त(काष्ठा rcu_head *rp)
अणु
	काष्ठा tipc_aead *aead = container_of(rp, काष्ठा tipc_aead, rcu);
	काष्ठा tipc_tfm *tfm_entry, *head, *पंचांगp;

	अगर (aead->cloned) अणु
		tipc_aead_put(aead->cloned);
	पूर्ण अन्यथा अणु
		head = *get_cpu_ptr(aead->tfm_entry);
		put_cpu_ptr(aead->tfm_entry);
		list_क्रम_each_entry_safe(tfm_entry, पंचांगp, &head->list, list) अणु
			crypto_मुक्त_aead(tfm_entry->tfm);
			list_del(&tfm_entry->list);
			kमुक्त(tfm_entry);
		पूर्ण
		/* Free the head */
		crypto_मुक्त_aead(head->tfm);
		list_del(&head->list);
		kमुक्त(head);
	पूर्ण
	मुक्त_percpu(aead->tfm_entry);
	kमुक्त_sensitive(aead->key);
	kमुक्त(aead);
पूर्ण

अटल पूर्णांक tipc_aead_users(काष्ठा tipc_aead __rcu *aead)
अणु
	काष्ठा tipc_aead *पंचांगp;
	पूर्णांक users = 0;

	rcu_पढ़ो_lock();
	पंचांगp = rcu_dereference(aead);
	अगर (पंचांगp)
		users = atomic_पढ़ो(&पंचांगp->users);
	rcu_पढ़ो_unlock();

	वापस users;
पूर्ण

अटल व्योम tipc_aead_users_inc(काष्ठा tipc_aead __rcu *aead, पूर्णांक lim)
अणु
	काष्ठा tipc_aead *पंचांगp;

	rcu_पढ़ो_lock();
	पंचांगp = rcu_dereference(aead);
	अगर (पंचांगp)
		atomic_add_unless(&पंचांगp->users, 1, lim);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम tipc_aead_users_dec(काष्ठा tipc_aead __rcu *aead, पूर्णांक lim)
अणु
	काष्ठा tipc_aead *पंचांगp;

	rcu_पढ़ो_lock();
	पंचांगp = rcu_dereference(aead);
	अगर (पंचांगp)
		atomic_add_unless(&rcu_dereference(aead)->users, -1, lim);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम tipc_aead_users_set(काष्ठा tipc_aead __rcu *aead, पूर्णांक val)
अणु
	काष्ठा tipc_aead *पंचांगp;
	पूर्णांक cur;

	rcu_पढ़ो_lock();
	पंचांगp = rcu_dereference(aead);
	अगर (पंचांगp) अणु
		करो अणु
			cur = atomic_पढ़ो(&पंचांगp->users);
			अगर (cur == val)
				अवरोध;
		पूर्ण जबतक (atomic_cmpxchg(&पंचांगp->users, cur, val) != cur);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * tipc_aead_tfm_next - Move TFM entry to the next one in list and वापस it
 * @aead: the AEAD key poपूर्णांकer
 */
अटल काष्ठा crypto_aead *tipc_aead_tfm_next(काष्ठा tipc_aead *aead)
अणु
	काष्ठा tipc_tfm **tfm_entry;
	काष्ठा crypto_aead *tfm;

	tfm_entry = get_cpu_ptr(aead->tfm_entry);
	*tfm_entry = list_next_entry(*tfm_entry, list);
	tfm = (*tfm_entry)->tfm;
	put_cpu_ptr(tfm_entry);

	वापस tfm;
पूर्ण

/**
 * tipc_aead_init - Initiate TIPC AEAD
 * @aead: वापसed new TIPC AEAD key handle poपूर्णांकer
 * @ukey: poपूर्णांकer to user key data
 * @mode: the key mode
 *
 * Allocate a (list of) new cipher transक्रमmation (TFM) with the specअगरic user
 * key data अगर valid. The number of the allocated TFMs can be set via the sysfs
 * "net/tipc/max_tfms" first.
 * Also, all the other AEAD data are also initialized.
 *
 * Return: 0 अगर the initiation is successful, otherwise: < 0
 */
अटल पूर्णांक tipc_aead_init(काष्ठा tipc_aead **aead, काष्ठा tipc_aead_key *ukey,
			  u8 mode)
अणु
	काष्ठा tipc_tfm *tfm_entry, *head;
	काष्ठा crypto_aead *tfm;
	काष्ठा tipc_aead *पंचांगp;
	पूर्णांक keylen, err, cpu;
	पूर्णांक tfm_cnt = 0;

	अगर (unlikely(*aead))
		वापस -EEXIST;

	/* Allocate a new AEAD */
	पंचांगp = kzalloc(माप(*पंचांगp), GFP_ATOMIC);
	अगर (unlikely(!पंचांगp))
		वापस -ENOMEM;

	/* The key consists of two parts: [AES-KEY][SALT] */
	keylen = ukey->keylen - TIPC_AES_GCM_SALT_SIZE;

	/* Allocate per-cpu TFM entry poपूर्णांकer */
	पंचांगp->tfm_entry = alloc_percpu(काष्ठा tipc_tfm *);
	अगर (!पंचांगp->tfm_entry) अणु
		kमुक्त_sensitive(पंचांगp);
		वापस -ENOMEM;
	पूर्ण

	/* Make a list of TFMs with the user key data */
	करो अणु
		tfm = crypto_alloc_aead(ukey->alg_name, 0, 0);
		अगर (IS_ERR(tfm)) अणु
			err = PTR_ERR(tfm);
			अवरोध;
		पूर्ण

		अगर (unlikely(!tfm_cnt &&
			     crypto_aead_ivsize(tfm) != TIPC_AES_GCM_IV_SIZE)) अणु
			crypto_मुक्त_aead(tfm);
			err = -ENOTSUPP;
			अवरोध;
		पूर्ण

		err = crypto_aead_setauthsize(tfm, TIPC_AES_GCM_TAG_SIZE);
		err |= crypto_aead_setkey(tfm, ukey->key, keylen);
		अगर (unlikely(err)) अणु
			crypto_मुक्त_aead(tfm);
			अवरोध;
		पूर्ण

		tfm_entry = kदो_स्मृति(माप(*tfm_entry), GFP_KERNEL);
		अगर (unlikely(!tfm_entry)) अणु
			crypto_मुक्त_aead(tfm);
			err = -ENOMEM;
			अवरोध;
		पूर्ण
		INIT_LIST_HEAD(&tfm_entry->list);
		tfm_entry->tfm = tfm;

		/* First entry? */
		अगर (!tfm_cnt) अणु
			head = tfm_entry;
			क्रम_each_possible_cpu(cpu) अणु
				*per_cpu_ptr(पंचांगp->tfm_entry, cpu) = head;
			पूर्ण
		पूर्ण अन्यथा अणु
			list_add_tail(&tfm_entry->list, &head->list);
		पूर्ण

	पूर्ण जबतक (++tfm_cnt < sysctl_tipc_max_tfms);

	/* Not any TFM is allocated? */
	अगर (!tfm_cnt) अणु
		मुक्त_percpu(पंचांगp->tfm_entry);
		kमुक्त_sensitive(पंचांगp);
		वापस err;
	पूर्ण

	/* Form a hex string of some last bytes as the key's hपूर्णांक */
	bin2hex(पंचांगp->hपूर्णांक, ukey->key + keylen - TIPC_AEAD_HINT_LEN,
		TIPC_AEAD_HINT_LEN);

	/* Initialize the other data */
	पंचांगp->mode = mode;
	पंचांगp->cloned = शून्य;
	पंचांगp->authsize = TIPC_AES_GCM_TAG_SIZE;
	पंचांगp->key = kmemdup(ukey, tipc_aead_key_size(ukey), GFP_KERNEL);
	स_नकल(&पंचांगp->salt, ukey->key + keylen, TIPC_AES_GCM_SALT_SIZE);
	atomic_set(&पंचांगp->users, 0);
	atomic64_set(&पंचांगp->seqno, 0);
	refcount_set(&पंचांगp->refcnt, 1);

	*aead = पंचांगp;
	वापस 0;
पूर्ण

/**
 * tipc_aead_clone - Clone a TIPC AEAD key
 * @dst: dest key क्रम the cloning
 * @src: source key to clone from
 *
 * Make a "copy" of the source AEAD key data to the dest, the TFMs list is
 * common क्रम the keys.
 * A reference to the source is hold in the "cloned" poपूर्णांकer क्रम the later
 * मुक्तing purposes.
 *
 * Note: this must be करोne in cluster-key mode only!
 * Return: 0 in हाल of success, otherwise < 0
 */
अटल पूर्णांक tipc_aead_clone(काष्ठा tipc_aead **dst, काष्ठा tipc_aead *src)
अणु
	काष्ठा tipc_aead *aead;
	पूर्णांक cpu;

	अगर (!src)
		वापस -ENOKEY;

	अगर (src->mode != CLUSTER_KEY)
		वापस -EINVAL;

	अगर (unlikely(*dst))
		वापस -EEXIST;

	aead = kzalloc(माप(*aead), GFP_ATOMIC);
	अगर (unlikely(!aead))
		वापस -ENOMEM;

	aead->tfm_entry = alloc_percpu_gfp(काष्ठा tipc_tfm *, GFP_ATOMIC);
	अगर (unlikely(!aead->tfm_entry)) अणु
		kमुक्त_sensitive(aead);
		वापस -ENOMEM;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		*per_cpu_ptr(aead->tfm_entry, cpu) =
				*per_cpu_ptr(src->tfm_entry, cpu);
	पूर्ण

	स_नकल(aead->hपूर्णांक, src->hपूर्णांक, माप(src->hपूर्णांक));
	aead->mode = src->mode;
	aead->salt = src->salt;
	aead->authsize = src->authsize;
	atomic_set(&aead->users, 0);
	atomic64_set(&aead->seqno, 0);
	refcount_set(&aead->refcnt, 1);

	WARN_ON(!refcount_inc_not_zero(&src->refcnt));
	aead->cloned = src;

	*dst = aead;
	वापस 0;
पूर्ण

/**
 * tipc_aead_mem_alloc - Allocate memory क्रम AEAD request operations
 * @tfm: cipher handle to be रेजिस्टरed with the request
 * @crypto_ctx_size: size of crypto context क्रम callback
 * @iv: वापसed poपूर्णांकer to IV data
 * @req: वापसed poपूर्णांकer to AEAD request data
 * @sg: वापसed poपूर्णांकer to SG lists
 * @nsg: number of SG lists to be allocated
 *
 * Allocate memory to store the crypto context data, AEAD request, IV and SG
 * lists, the memory layout is as follows:
 * crypto_ctx || iv || aead_req || sg[]
 *
 * Return: the poपूर्णांकer to the memory areas in हाल of success, otherwise शून्य
 */
अटल व्योम *tipc_aead_mem_alloc(काष्ठा crypto_aead *tfm,
				 अचिन्हित पूर्णांक crypto_ctx_size,
				 u8 **iv, काष्ठा aead_request **req,
				 काष्ठा scatterlist **sg, पूर्णांक nsg)
अणु
	अचिन्हित पूर्णांक iv_size, req_size;
	अचिन्हित पूर्णांक len;
	u8 *mem;

	iv_size = crypto_aead_ivsize(tfm);
	req_size = माप(**req) + crypto_aead_reqsize(tfm);

	len = crypto_ctx_size;
	len += iv_size;
	len += crypto_aead_alignmask(tfm) & ~(crypto_tfm_ctx_alignment() - 1);
	len = ALIGN(len, crypto_tfm_ctx_alignment());
	len += req_size;
	len = ALIGN(len, __alignof__(काष्ठा scatterlist));
	len += nsg * माप(**sg);

	mem = kदो_स्मृति(len, GFP_ATOMIC);
	अगर (!mem)
		वापस शून्य;

	*iv = (u8 *)PTR_ALIGN(mem + crypto_ctx_size,
			      crypto_aead_alignmask(tfm) + 1);
	*req = (काष्ठा aead_request *)PTR_ALIGN(*iv + iv_size,
						crypto_tfm_ctx_alignment());
	*sg = (काष्ठा scatterlist *)PTR_ALIGN((u8 *)*req + req_size,
					      __alignof__(काष्ठा scatterlist));

	वापस (व्योम *)mem;
पूर्ण

/**
 * tipc_aead_encrypt - Encrypt a message
 * @aead: TIPC AEAD key क्रम the message encryption
 * @skb: the input/output skb
 * @b: TIPC bearer where the message will be delivered after the encryption
 * @dst: the destination media address
 * @__dnode: TIPC dest node अगर "known"
 *
 * Return:
 * * 0                   : अगर the encryption has completed
 * * -EINPROGRESS/-EBUSY : अगर a callback will be perक्रमmed
 * * < 0                 : the encryption has failed
 */
अटल पूर्णांक tipc_aead_encrypt(काष्ठा tipc_aead *aead, काष्ठा sk_buff *skb,
			     काष्ठा tipc_bearer *b,
			     काष्ठा tipc_media_addr *dst,
			     काष्ठा tipc_node *__dnode)
अणु
	काष्ठा crypto_aead *tfm = tipc_aead_tfm_next(aead);
	काष्ठा tipc_crypto_tx_ctx *tx_ctx;
	काष्ठा aead_request *req;
	काष्ठा sk_buff *trailer;
	काष्ठा scatterlist *sg;
	काष्ठा tipc_ehdr *ehdr;
	पूर्णांक ehsz, len, tailen, nsg, rc;
	व्योम *ctx;
	u32 salt;
	u8 *iv;

	/* Make sure message len at least 4-byte aligned */
	len = ALIGN(skb->len, 4);
	tailen = len - skb->len + aead->authsize;

	/* Expand skb tail क्रम authentication tag:
	 * As क्रम simplicity, we'd have made sure skb having enough tailroom
	 * क्रम authentication tag @skb allocation. Even when skb is nonlinear
	 * but there is no frag_list, it should be still fine!
	 * Otherwise, we must cow it to be a writable buffer with the tailroom.
	 */
	SKB_LINEAR_ASSERT(skb);
	अगर (tailen > skb_tailroom(skb)) अणु
		pr_debug("TX(): skb tailroom is not enough: %d, requires: %d\n",
			 skb_tailroom(skb), tailen);
	पूर्ण

	अगर (unlikely(!skb_cloned(skb) && tailen <= skb_tailroom(skb))) अणु
		nsg = 1;
		trailer = skb;
	पूर्ण अन्यथा अणु
		/* TODO: We could aव्योम skb_cow_data() अगर skb has no frag_list
		 * e.g. by skb_fill_page_desc() to add another page to the skb
		 * with the wanted tailen... However, page skbs look not often,
		 * so take it easy now!
		 * Cloned skbs e.g. from link_xmit() seems no choice though :(
		 */
		nsg = skb_cow_data(skb, tailen, &trailer);
		अगर (unlikely(nsg < 0)) अणु
			pr_err("TX: skb_cow_data() returned %d\n", nsg);
			वापस nsg;
		पूर्ण
	पूर्ण

	pskb_put(skb, trailer, tailen);

	/* Allocate memory क्रम the AEAD operation */
	ctx = tipc_aead_mem_alloc(tfm, माप(*tx_ctx), &iv, &req, &sg, nsg);
	अगर (unlikely(!ctx))
		वापस -ENOMEM;
	TIPC_SKB_CB(skb)->crypto_ctx = ctx;

	/* Map skb to the sg lists */
	sg_init_table(sg, nsg);
	rc = skb_to_sgvec(skb, sg, 0, skb->len);
	अगर (unlikely(rc < 0)) अणु
		pr_err("TX: skb_to_sgvec() returned %d, nsg %d!\n", rc, nsg);
		जाओ निकास;
	पूर्ण

	/* Prepare IV: [SALT (4 octets)][SEQNO (8 octets)]
	 * In हाल we're in cluster-key mode, SALT is varied by xor-ing with
	 * the source address (or w0 of id), otherwise with the dest address
	 * अगर dest is known.
	 */
	ehdr = (काष्ठा tipc_ehdr *)skb->data;
	salt = aead->salt;
	अगर (aead->mode == CLUSTER_KEY)
		salt ^= __be32_to_cpu(ehdr->addr);
	अन्यथा अगर (__dnode)
		salt ^= tipc_node_get_addr(__dnode);
	स_नकल(iv, &salt, 4);
	स_नकल(iv + 4, (u8 *)&ehdr->seqno, 8);

	/* Prepare request */
	ehsz = tipc_ehdr_size(ehdr);
	aead_request_set_tfm(req, tfm);
	aead_request_set_ad(req, ehsz);
	aead_request_set_crypt(req, sg, sg, len - ehsz, iv);

	/* Set callback function & data */
	aead_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  tipc_aead_encrypt_करोne, skb);
	tx_ctx = (काष्ठा tipc_crypto_tx_ctx *)ctx;
	tx_ctx->aead = aead;
	tx_ctx->bearer = b;
	स_नकल(&tx_ctx->dst, dst, माप(*dst));

	/* Hold bearer */
	अगर (unlikely(!tipc_bearer_hold(b))) अणु
		rc = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* Now, करो encrypt */
	rc = crypto_aead_encrypt(req);
	अगर (rc == -EINPROGRESS || rc == -EBUSY)
		वापस rc;

	tipc_bearer_put(b);

निकास:
	kमुक्त(ctx);
	TIPC_SKB_CB(skb)->crypto_ctx = शून्य;
	वापस rc;
पूर्ण

अटल व्योम tipc_aead_encrypt_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	काष्ठा sk_buff *skb = base->data;
	काष्ठा tipc_crypto_tx_ctx *tx_ctx = TIPC_SKB_CB(skb)->crypto_ctx;
	काष्ठा tipc_bearer *b = tx_ctx->bearer;
	काष्ठा tipc_aead *aead = tx_ctx->aead;
	काष्ठा tipc_crypto *tx = aead->crypto;
	काष्ठा net *net = tx->net;

	चयन (err) अणु
	हाल 0:
		this_cpu_inc(tx->stats->stat[STAT_ASYNC_OK]);
		rcu_पढ़ो_lock();
		अगर (likely(test_bit(0, &b->up)))
			b->media->send_msg(net, skb, b, &tx_ctx->dst);
		अन्यथा
			kमुक्त_skb(skb);
		rcu_पढ़ो_unlock();
		अवरोध;
	हाल -EINPROGRESS:
		वापस;
	शेष:
		this_cpu_inc(tx->stats->stat[STAT_ASYNC_NOK]);
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

	kमुक्त(tx_ctx);
	tipc_bearer_put(b);
	tipc_aead_put(aead);
पूर्ण

/**
 * tipc_aead_decrypt - Decrypt an encrypted message
 * @net: काष्ठा net
 * @aead: TIPC AEAD क्रम the message decryption
 * @skb: the input/output skb
 * @b: TIPC bearer where the message has been received
 *
 * Return:
 * * 0                   : अगर the decryption has completed
 * * -EINPROGRESS/-EBUSY : अगर a callback will be perक्रमmed
 * * < 0                 : the decryption has failed
 */
अटल पूर्णांक tipc_aead_decrypt(काष्ठा net *net, काष्ठा tipc_aead *aead,
			     काष्ठा sk_buff *skb, काष्ठा tipc_bearer *b)
अणु
	काष्ठा tipc_crypto_rx_ctx *rx_ctx;
	काष्ठा aead_request *req;
	काष्ठा crypto_aead *tfm;
	काष्ठा sk_buff *unused;
	काष्ठा scatterlist *sg;
	काष्ठा tipc_ehdr *ehdr;
	पूर्णांक ehsz, nsg, rc;
	व्योम *ctx;
	u32 salt;
	u8 *iv;

	अगर (unlikely(!aead))
		वापस -ENOKEY;

	/* Cow skb data अगर needed */
	अगर (likely(!skb_cloned(skb) &&
		   (!skb_is_nonlinear(skb) || !skb_has_frag_list(skb)))) अणु
		nsg = 1 + skb_shinfo(skb)->nr_frags;
	पूर्ण अन्यथा अणु
		nsg = skb_cow_data(skb, 0, &unused);
		अगर (unlikely(nsg < 0)) अणु
			pr_err("RX: skb_cow_data() returned %d\n", nsg);
			वापस nsg;
		पूर्ण
	पूर्ण

	/* Allocate memory क्रम the AEAD operation */
	tfm = tipc_aead_tfm_next(aead);
	ctx = tipc_aead_mem_alloc(tfm, माप(*rx_ctx), &iv, &req, &sg, nsg);
	अगर (unlikely(!ctx))
		वापस -ENOMEM;
	TIPC_SKB_CB(skb)->crypto_ctx = ctx;

	/* Map skb to the sg lists */
	sg_init_table(sg, nsg);
	rc = skb_to_sgvec(skb, sg, 0, skb->len);
	अगर (unlikely(rc < 0)) अणु
		pr_err("RX: skb_to_sgvec() returned %d, nsg %d\n", rc, nsg);
		जाओ निकास;
	पूर्ण

	/* Reस्थिरruct IV: */
	ehdr = (काष्ठा tipc_ehdr *)skb->data;
	salt = aead->salt;
	अगर (aead->mode == CLUSTER_KEY)
		salt ^= __be32_to_cpu(ehdr->addr);
	अन्यथा अगर (ehdr->destined)
		salt ^= tipc_own_addr(net);
	स_नकल(iv, &salt, 4);
	स_नकल(iv + 4, (u8 *)&ehdr->seqno, 8);

	/* Prepare request */
	ehsz = tipc_ehdr_size(ehdr);
	aead_request_set_tfm(req, tfm);
	aead_request_set_ad(req, ehsz);
	aead_request_set_crypt(req, sg, sg, skb->len - ehsz, iv);

	/* Set callback function & data */
	aead_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  tipc_aead_decrypt_करोne, skb);
	rx_ctx = (काष्ठा tipc_crypto_rx_ctx *)ctx;
	rx_ctx->aead = aead;
	rx_ctx->bearer = b;

	/* Hold bearer */
	अगर (unlikely(!tipc_bearer_hold(b))) अणु
		rc = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* Now, करो decrypt */
	rc = crypto_aead_decrypt(req);
	अगर (rc == -EINPROGRESS || rc == -EBUSY)
		वापस rc;

	tipc_bearer_put(b);

निकास:
	kमुक्त(ctx);
	TIPC_SKB_CB(skb)->crypto_ctx = शून्य;
	वापस rc;
पूर्ण

अटल व्योम tipc_aead_decrypt_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	काष्ठा sk_buff *skb = base->data;
	काष्ठा tipc_crypto_rx_ctx *rx_ctx = TIPC_SKB_CB(skb)->crypto_ctx;
	काष्ठा tipc_bearer *b = rx_ctx->bearer;
	काष्ठा tipc_aead *aead = rx_ctx->aead;
	काष्ठा tipc_crypto_stats __percpu *stats = aead->crypto->stats;
	काष्ठा net *net = aead->crypto->net;

	चयन (err) अणु
	हाल 0:
		this_cpu_inc(stats->stat[STAT_ASYNC_OK]);
		अवरोध;
	हाल -EINPROGRESS:
		वापस;
	शेष:
		this_cpu_inc(stats->stat[STAT_ASYNC_NOK]);
		अवरोध;
	पूर्ण

	kमुक्त(rx_ctx);
	tipc_crypto_rcv_complete(net, aead, b, &skb, err);
	अगर (likely(skb)) अणु
		अगर (likely(test_bit(0, &b->up)))
			tipc_rcv(net, skb, b);
		अन्यथा
			kमुक्त_skb(skb);
	पूर्ण

	tipc_bearer_put(b);
पूर्ण

अटल अंतरभूत पूर्णांक tipc_ehdr_size(काष्ठा tipc_ehdr *ehdr)
अणु
	वापस (ehdr->user != LINK_CONFIG) ? EHDR_SIZE : EHDR_CFG_SIZE;
पूर्ण

/**
 * tipc_ehdr_validate - Validate an encryption message
 * @skb: the message buffer
 *
 * Return: "true" अगर this is a valid encryption message, otherwise "false"
 */
bool tipc_ehdr_validate(काष्ठा sk_buff *skb)
अणु
	काष्ठा tipc_ehdr *ehdr;
	पूर्णांक ehsz;

	अगर (unlikely(!pskb_may_pull(skb, EHDR_MIN_SIZE)))
		वापस false;

	ehdr = (काष्ठा tipc_ehdr *)skb->data;
	अगर (unlikely(ehdr->version != TIPC_EVERSION))
		वापस false;
	ehsz = tipc_ehdr_size(ehdr);
	अगर (unlikely(!pskb_may_pull(skb, ehsz)))
		वापस false;
	अगर (unlikely(skb->len <= ehsz + TIPC_AES_GCM_TAG_SIZE))
		वापस false;

	वापस true;
पूर्ण

/**
 * tipc_ehdr_build - Build TIPC encryption message header
 * @net: काष्ठा net
 * @aead: TX AEAD key to be used क्रम the message encryption
 * @tx_key: key id used क्रम the message encryption
 * @skb: input/output message skb
 * @__rx: RX crypto handle अगर dest is "known"
 *
 * Return: the header size अगर the building is successful, otherwise < 0
 */
अटल पूर्णांक tipc_ehdr_build(काष्ठा net *net, काष्ठा tipc_aead *aead,
			   u8 tx_key, काष्ठा sk_buff *skb,
			   काष्ठा tipc_crypto *__rx)
अणु
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	काष्ठा tipc_ehdr *ehdr;
	u32 user = msg_user(hdr);
	u64 seqno;
	पूर्णांक ehsz;

	/* Make room क्रम encryption header */
	ehsz = (user != LINK_CONFIG) ? EHDR_SIZE : EHDR_CFG_SIZE;
	WARN_ON(skb_headroom(skb) < ehsz);
	ehdr = (काष्ठा tipc_ehdr *)skb_push(skb, ehsz);

	/* Obtain a seqno first:
	 * Use the key seqno (= cluster wise) अगर dest is unknown or we're in
	 * cluster key mode, otherwise it's better क्रम a per-peer seqno!
	 */
	अगर (!__rx || aead->mode == CLUSTER_KEY)
		seqno = atomic64_inc_वापस(&aead->seqno);
	अन्यथा
		seqno = atomic64_inc_वापस(&__rx->sndnxt);

	/* Revoke the key अगर seqno is wrapped around */
	अगर (unlikely(!seqno))
		वापस tipc_crypto_key_revoke(net, tx_key);

	/* Word 1-2 */
	ehdr->seqno = cpu_to_be64(seqno);

	/* Words 0, 3- */
	ehdr->version = TIPC_EVERSION;
	ehdr->user = 0;
	ehdr->keepalive = 0;
	ehdr->tx_key = tx_key;
	ehdr->destined = (__rx) ? 1 : 0;
	ehdr->rx_key_active = (__rx) ? __rx->key.active : 0;
	ehdr->rx_nokey = (__rx) ? __rx->nokey : 0;
	ehdr->master_key = aead->crypto->key_master;
	ehdr->reserved_1 = 0;
	ehdr->reserved_2 = 0;

	चयन (user) अणु
	हाल LINK_CONFIG:
		ehdr->user = LINK_CONFIG;
		स_नकल(ehdr->id, tipc_own_id(net), NODE_ID_LEN);
		अवरोध;
	शेष:
		अगर (user == LINK_PROTOCOL && msg_type(hdr) == STATE_MSG) अणु
			ehdr->user = LINK_PROTOCOL;
			ehdr->keepalive = msg_is_keepalive(hdr);
		पूर्ण
		ehdr->addr = hdr->hdr[3];
		अवरोध;
	पूर्ण

	वापस ehsz;
पूर्ण

अटल अंतरभूत व्योम tipc_crypto_key_set_state(काष्ठा tipc_crypto *c,
					     u8 new_passive,
					     u8 new_active,
					     u8 new_pending)
अणु
	काष्ठा tipc_key old = c->key;
	अक्षर buf[32];

	c->key.keys = ((new_passive & KEY_MASK) << (KEY_BITS * 2)) |
		      ((new_active  & KEY_MASK) << (KEY_BITS)) |
		      ((new_pending & KEY_MASK));

	pr_debug("%s: key changing %s ::%pS\n", c->name,
		 tipc_key_change_dump(old, c->key, buf),
		 __builtin_वापस_address(0));
पूर्ण

/**
 * tipc_crypto_key_init - Initiate a new user / AEAD key
 * @c: TIPC crypto to which new key is attached
 * @ukey: the user key
 * @mode: the key mode (CLUSTER_KEY or PER_NODE_KEY)
 * @master_key: specअगरy this is a cluster master key
 *
 * A new TIPC AEAD key will be allocated and initiated with the specअगरied user
 * key, then attached to the TIPC crypto.
 *
 * Return: new key id in हाल of success, otherwise: < 0
 */
पूर्णांक tipc_crypto_key_init(काष्ठा tipc_crypto *c, काष्ठा tipc_aead_key *ukey,
			 u8 mode, bool master_key)
अणु
	काष्ठा tipc_aead *aead = शून्य;
	पूर्णांक rc = 0;

	/* Initiate with the new user key */
	rc = tipc_aead_init(&aead, ukey, mode);

	/* Attach it to the crypto */
	अगर (likely(!rc)) अणु
		rc = tipc_crypto_key_attach(c, aead, 0, master_key);
		अगर (rc < 0)
			tipc_aead_मुक्त(&aead->rcu);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * tipc_crypto_key_attach - Attach a new AEAD key to TIPC crypto
 * @c: TIPC crypto to which the new AEAD key is attached
 * @aead: the new AEAD key poपूर्णांकer
 * @pos: desired slot in the crypto key array, = 0 अगर any!
 * @master_key: specअगरy this is a cluster master key
 *
 * Return: new key id in हाल of success, otherwise: -EBUSY
 */
अटल पूर्णांक tipc_crypto_key_attach(काष्ठा tipc_crypto *c,
				  काष्ठा tipc_aead *aead, u8 pos,
				  bool master_key)
अणु
	काष्ठा tipc_key key;
	पूर्णांक rc = -EBUSY;
	u8 new_key;

	spin_lock_bh(&c->lock);
	key = c->key;
	अगर (master_key) अणु
		new_key = KEY_MASTER;
		जाओ attach;
	पूर्ण
	अगर (key.active && key.passive)
		जाओ निकास;
	अगर (key.pending) अणु
		अगर (tipc_aead_users(c->aead[key.pending]) > 0)
			जाओ निकास;
		/* अगर (pos): ok with replacing, will be aligned when needed */
		/* Replace it */
		new_key = key.pending;
	पूर्ण अन्यथा अणु
		अगर (pos) अणु
			अगर (key.active && pos != key_next(key.active)) अणु
				key.passive = pos;
				new_key = pos;
				जाओ attach;
			पूर्ण अन्यथा अगर (!key.active && !key.passive) अणु
				key.pending = pos;
				new_key = pos;
				जाओ attach;
			पूर्ण
		पूर्ण
		key.pending = key_next(key.active ?: key.passive);
		new_key = key.pending;
	पूर्ण

attach:
	aead->crypto = c;
	aead->gen = (is_tx(c)) ? ++c->key_gen : c->key_gen;
	tipc_aead_rcu_replace(c->aead[new_key], aead, &c->lock);
	अगर (likely(c->key.keys != key.keys))
		tipc_crypto_key_set_state(c, key.passive, key.active,
					  key.pending);
	c->working = 1;
	c->nokey = 0;
	c->key_master |= master_key;
	rc = new_key;

निकास:
	spin_unlock_bh(&c->lock);
	वापस rc;
पूर्ण

व्योम tipc_crypto_key_flush(काष्ठा tipc_crypto *c)
अणु
	काष्ठा tipc_crypto *tx, *rx;
	पूर्णांक k;

	spin_lock_bh(&c->lock);
	अगर (is_rx(c)) अणु
		/* Try to cancel pending work */
		rx = c;
		tx = tipc_net(rx->net)->crypto_tx;
		अगर (cancel_delayed_work(&rx->work)) अणु
			kमुक्त(rx->skey);
			rx->skey = शून्य;
			atomic_xchg(&rx->key_distr, 0);
			tipc_node_put(rx->node);
		पूर्ण
		/* RX stopping => decrease TX key users अगर any */
		k = atomic_xchg(&rx->peer_rx_active, 0);
		अगर (k) अणु
			tipc_aead_users_dec(tx->aead[k], 0);
			/* Mark the poपूर्णांक TX key users changed */
			tx->समयr1 = jअगरfies;
		पूर्ण
	पूर्ण

	c->flags = 0;
	tipc_crypto_key_set_state(c, 0, 0, 0);
	क्रम (k = KEY_MIN; k <= KEY_MAX; k++)
		tipc_crypto_key_detach(c->aead[k], &c->lock);
	atomic64_set(&c->sndnxt, 0);
	spin_unlock_bh(&c->lock);
पूर्ण

/**
 * tipc_crypto_key_try_align - Align RX keys अगर possible
 * @rx: RX crypto handle
 * @new_pending: new pending slot अगर aligned (= TX key from peer)
 *
 * Peer has used an unknown key slot, this only happens when peer has left and
 * rejoned, or we are newcomer.
 * That means, there must be no active key but a pending key at unaligned slot.
 * If so, we try to move the pending key to the new slot.
 * Note: A potential passive key can exist, it will be shअगरted correspondingly!
 *
 * Return: "true" अगर key is successfully aligned, otherwise "false"
 */
अटल bool tipc_crypto_key_try_align(काष्ठा tipc_crypto *rx, u8 new_pending)
अणु
	काष्ठा tipc_aead *पंचांगp1, *पंचांगp2 = शून्य;
	काष्ठा tipc_key key;
	bool aligned = false;
	u8 new_passive = 0;
	पूर्णांक x;

	spin_lock(&rx->lock);
	key = rx->key;
	अगर (key.pending == new_pending) अणु
		aligned = true;
		जाओ निकास;
	पूर्ण
	अगर (key.active)
		जाओ निकास;
	अगर (!key.pending)
		जाओ निकास;
	अगर (tipc_aead_users(rx->aead[key.pending]) > 0)
		जाओ निकास;

	/* Try to "isolate" this pending key first */
	पंचांगp1 = tipc_aead_rcu_ptr(rx->aead[key.pending], &rx->lock);
	अगर (!refcount_dec_अगर_one(&पंचांगp1->refcnt))
		जाओ निकास;
	rcu_assign_poपूर्णांकer(rx->aead[key.pending], शून्य);

	/* Move passive key अगर any */
	अगर (key.passive) अणु
		पंचांगp2 = rcu_replace_poपूर्णांकer(rx->aead[key.passive], पंचांगp2, lockdep_is_held(&rx->lock));
		x = (key.passive - key.pending + new_pending) % KEY_MAX;
		new_passive = (x <= 0) ? x + KEY_MAX : x;
	पूर्ण

	/* Re-allocate the key(s) */
	tipc_crypto_key_set_state(rx, new_passive, 0, new_pending);
	rcu_assign_poपूर्णांकer(rx->aead[new_pending], पंचांगp1);
	अगर (new_passive)
		rcu_assign_poपूर्णांकer(rx->aead[new_passive], पंचांगp2);
	refcount_set(&पंचांगp1->refcnt, 1);
	aligned = true;
	pr_info_ratelimited("%s: key[%d] -> key[%d]\n", rx->name, key.pending,
			    new_pending);

निकास:
	spin_unlock(&rx->lock);
	वापस aligned;
पूर्ण

/**
 * tipc_crypto_key_pick_tx - Pick one TX key क्रम message decryption
 * @tx: TX crypto handle
 * @rx: RX crypto handle (can be शून्य)
 * @skb: the message skb which will be decrypted later
 * @tx_key: peer TX key id
 *
 * This function looks up the existing TX keys and pick one which is suitable
 * क्रम the message decryption, that must be a cluster key and not used beक्रमe
 * on the same message (i.e. recursive).
 *
 * Return: the TX AEAD key handle in हाल of success, otherwise शून्य
 */
अटल काष्ठा tipc_aead *tipc_crypto_key_pick_tx(काष्ठा tipc_crypto *tx,
						 काष्ठा tipc_crypto *rx,
						 काष्ठा sk_buff *skb,
						 u8 tx_key)
अणु
	काष्ठा tipc_skb_cb *skb_cb = TIPC_SKB_CB(skb);
	काष्ठा tipc_aead *aead = शून्य;
	काष्ठा tipc_key key = tx->key;
	u8 k, i = 0;

	/* Initialize data अगर not yet */
	अगर (!skb_cb->tx_clone_deferred) अणु
		skb_cb->tx_clone_deferred = 1;
		स_रखो(&skb_cb->tx_clone_ctx, 0, माप(skb_cb->tx_clone_ctx));
	पूर्ण

	skb_cb->tx_clone_ctx.rx = rx;
	अगर (++skb_cb->tx_clone_ctx.recurs > 2)
		वापस शून्य;

	/* Pick one TX key */
	spin_lock(&tx->lock);
	अगर (tx_key == KEY_MASTER) अणु
		aead = tipc_aead_rcu_ptr(tx->aead[KEY_MASTER], &tx->lock);
		जाओ करोne;
	पूर्ण
	करो अणु
		k = (i == 0) ? key.pending :
			((i == 1) ? key.active : key.passive);
		अगर (!k)
			जारी;
		aead = tipc_aead_rcu_ptr(tx->aead[k], &tx->lock);
		अगर (!aead)
			जारी;
		अगर (aead->mode != CLUSTER_KEY ||
		    aead == skb_cb->tx_clone_ctx.last) अणु
			aead = शून्य;
			जारी;
		पूर्ण
		/* Ok, found one cluster key */
		skb_cb->tx_clone_ctx.last = aead;
		WARN_ON(skb->next);
		skb->next = skb_clone(skb, GFP_ATOMIC);
		अगर (unlikely(!skb->next))
			pr_warn("Failed to clone skb for next round if any\n");
		अवरोध;
	पूर्ण जबतक (++i < 3);

करोne:
	अगर (likely(aead))
		WARN_ON(!refcount_inc_not_zero(&aead->refcnt));
	spin_unlock(&tx->lock);

	वापस aead;
पूर्ण

/**
 * tipc_crypto_key_synch: Synch own key data according to peer key status
 * @rx: RX crypto handle
 * @skb: TIPCv2 message buffer (incl. the ehdr from peer)
 *
 * This function updates the peer node related data as the peer RX active key
 * has changed, so the number of TX keys' users on this node are increased and
 * decreased correspondingly.
 *
 * It also considers अगर peer has no key, then we need to make own master key
 * (अगर any) taking over i.e. starting grace period and also trigger key
 * distributing process.
 *
 * The "per-peer" sndnxt is also reset when the peer key has चयनed.
 */
अटल व्योम tipc_crypto_key_synch(काष्ठा tipc_crypto *rx, काष्ठा sk_buff *skb)
अणु
	काष्ठा tipc_ehdr *ehdr = (काष्ठा tipc_ehdr *)skb_network_header(skb);
	काष्ठा tipc_crypto *tx = tipc_net(rx->net)->crypto_tx;
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	u32 self = tipc_own_addr(rx->net);
	u8 cur, new;
	अचिन्हित दीर्घ delay;

	/* Update RX 'key_master' flag according to peer, also mark "legacy" अगर
	 * a peer has no master key.
	 */
	rx->key_master = ehdr->master_key;
	अगर (!rx->key_master)
		tx->legacy_user = 1;

	/* For later हालs, apply only अगर message is destined to this node */
	अगर (!ehdr->destined || msg_लघु(hdr) || msg_destnode(hdr) != self)
		वापस;

	/* Case 1: Peer has no keys, let's make master key take over */
	अगर (ehdr->rx_nokey) अणु
		/* Set or extend grace period */
		tx->समयr2 = jअगरfies;
		/* Schedule key distributing क्रम the peer अगर not yet */
		अगर (tx->key.keys &&
		    !atomic_cmpxchg(&rx->key_distr, 0, KEY_DISTR_SCHED)) अणु
			get_अक्रमom_bytes(&delay, 2);
			delay %= 5;
			delay = msecs_to_jअगरfies(500 * ++delay);
			अगर (queue_delayed_work(tx->wq, &rx->work, delay))
				tipc_node_get(rx->node);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Cancel a pending key distributing अगर any */
		atomic_xchg(&rx->key_distr, 0);
	पूर्ण

	/* Case 2: Peer RX active key has changed, let's update own TX users */
	cur = atomic_पढ़ो(&rx->peer_rx_active);
	new = ehdr->rx_key_active;
	अगर (tx->key.keys &&
	    cur != new &&
	    atomic_cmpxchg(&rx->peer_rx_active, cur, new) == cur) अणु
		अगर (new)
			tipc_aead_users_inc(tx->aead[new], पूर्णांक_उच्च);
		अगर (cur)
			tipc_aead_users_dec(tx->aead[cur], 0);

		atomic64_set(&rx->sndnxt, 0);
		/* Mark the poपूर्णांक TX key users changed */
		tx->समयr1 = jअगरfies;

		pr_debug("%s: key users changed %d-- %d++, peer %s\n",
			 tx->name, cur, new, rx->name);
	पूर्ण
पूर्ण

अटल पूर्णांक tipc_crypto_key_revoke(काष्ठा net *net, u8 tx_key)
अणु
	काष्ठा tipc_crypto *tx = tipc_net(net)->crypto_tx;
	काष्ठा tipc_key key;

	spin_lock(&tx->lock);
	key = tx->key;
	WARN_ON(!key.active || tx_key != key.active);

	/* Free the active key */
	tipc_crypto_key_set_state(tx, key.passive, 0, key.pending);
	tipc_crypto_key_detach(tx->aead[key.active], &tx->lock);
	spin_unlock(&tx->lock);

	pr_warn("%s: key is revoked\n", tx->name);
	वापस -EKEYREVOKED;
पूर्ण

पूर्णांक tipc_crypto_start(काष्ठा tipc_crypto **crypto, काष्ठा net *net,
		      काष्ठा tipc_node *node)
अणु
	काष्ठा tipc_crypto *c;

	अगर (*crypto)
		वापस -EEXIST;

	/* Allocate crypto */
	c = kzalloc(माप(*c), GFP_ATOMIC);
	अगर (!c)
		वापस -ENOMEM;

	/* Allocate workqueue on TX */
	अगर (!node) अणु
		c->wq = alloc_ordered_workqueue("tipc_crypto", 0);
		अगर (!c->wq) अणु
			kमुक्त(c);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Allocate statistic काष्ठाure */
	c->stats = alloc_percpu_gfp(काष्ठा tipc_crypto_stats, GFP_ATOMIC);
	अगर (!c->stats) अणु
		अगर (c->wq)
			destroy_workqueue(c->wq);
		kमुक्त_sensitive(c);
		वापस -ENOMEM;
	पूर्ण

	c->flags = 0;
	c->net = net;
	c->node = node;
	get_अक्रमom_bytes(&c->key_gen, 2);
	tipc_crypto_key_set_state(c, 0, 0, 0);
	atomic_set(&c->key_distr, 0);
	atomic_set(&c->peer_rx_active, 0);
	atomic64_set(&c->sndnxt, 0);
	c->समयr1 = jअगरfies;
	c->समयr2 = jअगरfies;
	c->rekeying_पूर्णांकv = TIPC_REKEYING_INTV_DEF;
	spin_lock_init(&c->lock);
	scnम_लिखो(c->name, 48, "%s(%s)", (is_rx(c)) ? "RX" : "TX",
		  (is_rx(c)) ? tipc_node_get_id_str(c->node) :
			       tipc_own_id_string(c->net));

	अगर (is_rx(c))
		INIT_DELAYED_WORK(&c->work, tipc_crypto_work_rx);
	अन्यथा
		INIT_DELAYED_WORK(&c->work, tipc_crypto_work_tx);

	*crypto = c;
	वापस 0;
पूर्ण

व्योम tipc_crypto_stop(काष्ठा tipc_crypto **crypto)
अणु
	काष्ठा tipc_crypto *c = *crypto;
	u8 k;

	अगर (!c)
		वापस;

	/* Flush any queued works & destroy wq */
	अगर (is_tx(c)) अणु
		c->rekeying_पूर्णांकv = 0;
		cancel_delayed_work_sync(&c->work);
		destroy_workqueue(c->wq);
	पूर्ण

	/* Release AEAD keys */
	rcu_पढ़ो_lock();
	क्रम (k = KEY_MIN; k <= KEY_MAX; k++)
		tipc_aead_put(rcu_dereference(c->aead[k]));
	rcu_पढ़ो_unlock();
	pr_debug("%s: has been stopped\n", c->name);

	/* Free this crypto statistics */
	मुक्त_percpu(c->stats);

	*crypto = शून्य;
	kमुक्त_sensitive(c);
पूर्ण

व्योम tipc_crypto_समयout(काष्ठा tipc_crypto *rx)
अणु
	काष्ठा tipc_net *tn = tipc_net(rx->net);
	काष्ठा tipc_crypto *tx = tn->crypto_tx;
	काष्ठा tipc_key key;
	पूर्णांक cmd;

	/* TX pending: taking all users & stable -> active */
	spin_lock(&tx->lock);
	key = tx->key;
	अगर (key.active && tipc_aead_users(tx->aead[key.active]) > 0)
		जाओ s1;
	अगर (!key.pending || tipc_aead_users(tx->aead[key.pending]) <= 0)
		जाओ s1;
	अगर (समय_beक्रमe(jअगरfies, tx->समयr1 + TIPC_TX_LASTING_TIME))
		जाओ s1;

	tipc_crypto_key_set_state(tx, key.passive, key.pending, 0);
	अगर (key.active)
		tipc_crypto_key_detach(tx->aead[key.active], &tx->lock);
	this_cpu_inc(tx->stats->stat[STAT_SWITCHES]);
	pr_info("%s: key[%d] is activated\n", tx->name, key.pending);

s1:
	spin_unlock(&tx->lock);

	/* RX pending: having user -> active */
	spin_lock(&rx->lock);
	key = rx->key;
	अगर (!key.pending || tipc_aead_users(rx->aead[key.pending]) <= 0)
		जाओ s2;

	अगर (key.active)
		key.passive = key.active;
	key.active = key.pending;
	rx->समयr2 = jअगरfies;
	tipc_crypto_key_set_state(rx, key.passive, key.active, 0);
	this_cpu_inc(rx->stats->stat[STAT_SWITCHES]);
	pr_info("%s: key[%d] is activated\n", rx->name, key.pending);
	जाओ s5;

s2:
	/* RX pending: not working -> हटाओ */
	अगर (!key.pending || tipc_aead_users(rx->aead[key.pending]) > -10)
		जाओ s3;

	tipc_crypto_key_set_state(rx, key.passive, key.active, 0);
	tipc_crypto_key_detach(rx->aead[key.pending], &rx->lock);
	pr_debug("%s: key[%d] is removed\n", rx->name, key.pending);
	जाओ s5;

s3:
	/* RX active: समयd out or no user -> pending */
	अगर (!key.active)
		जाओ s4;
	अगर (समय_beक्रमe(jअगरfies, rx->समयr1 + TIPC_RX_ACTIVE_LIM) &&
	    tipc_aead_users(rx->aead[key.active]) > 0)
		जाओ s4;

	अगर (key.pending)
		key.passive = key.active;
	अन्यथा
		key.pending = key.active;
	rx->समयr2 = jअगरfies;
	tipc_crypto_key_set_state(rx, key.passive, 0, key.pending);
	tipc_aead_users_set(rx->aead[key.pending], 0);
	pr_debug("%s: key[%d] is deactivated\n", rx->name, key.active);
	जाओ s5;

s4:
	/* RX passive: outdated or not working -> मुक्त */
	अगर (!key.passive)
		जाओ s5;
	अगर (समय_beक्रमe(jअगरfies, rx->समयr2 + TIPC_RX_PASSIVE_LIM) &&
	    tipc_aead_users(rx->aead[key.passive]) > -10)
		जाओ s5;

	tipc_crypto_key_set_state(rx, 0, key.active, key.pending);
	tipc_crypto_key_detach(rx->aead[key.passive], &rx->lock);
	pr_debug("%s: key[%d] is freed\n", rx->name, key.passive);

s5:
	spin_unlock(&rx->lock);

	/* Relax it here, the flag will be set again अगर it really is, but only
	 * when we are not in grace period क्रम safety!
	 */
	अगर (समय_after(jअगरfies, tx->समयr2 + TIPC_TX_GRACE_PERIOD))
		tx->legacy_user = 0;

	/* Limit max_tfms & करो debug commands अगर needed */
	अगर (likely(sysctl_tipc_max_tfms <= TIPC_MAX_TFMS_LIM))
		वापस;

	cmd = sysctl_tipc_max_tfms;
	sysctl_tipc_max_tfms = TIPC_MAX_TFMS_DEF;
	tipc_crypto_करो_cmd(rx->net, cmd);
पूर्ण

अटल अंतरभूत व्योम tipc_crypto_clone_msg(काष्ठा net *net, काष्ठा sk_buff *_skb,
					 काष्ठा tipc_bearer *b,
					 काष्ठा tipc_media_addr *dst,
					 काष्ठा tipc_node *__dnode, u8 type)
अणु
	काष्ठा sk_buff *skb;

	skb = skb_clone(_skb, GFP_ATOMIC);
	अगर (skb) अणु
		TIPC_SKB_CB(skb)->xmit_type = type;
		tipc_crypto_xmit(net, &skb, b, dst, __dnode);
		अगर (skb)
			b->media->send_msg(net, skb, b, dst);
	पूर्ण
पूर्ण

/**
 * tipc_crypto_xmit - Build & encrypt TIPC message क्रम xmit
 * @net: काष्ठा net
 * @skb: input/output message skb poपूर्णांकer
 * @b: bearer used क्रम xmit later
 * @dst: destination media address
 * @__dnode: destination node क्रम reference अगर any
 *
 * First, build an encryption message header on the top of the message, then
 * encrypt the original TIPC message by using the pending, master or active
 * key with this preference order.
 * If the encryption is successful, the encrypted skb is वापसed directly or
 * via the callback.
 * Otherwise, the skb is मुक्तd!
 *
 * Return:
 * * 0                   : the encryption has succeeded (or no encryption)
 * * -EINPROGRESS/-EBUSY : the encryption is ongoing, a callback will be made
 * * -ENOKEK             : the encryption has failed due to no key
 * * -EKEYREVOKED        : the encryption has failed due to key revoked
 * * -ENOMEM             : the encryption has failed due to no memory
 * * < 0                 : the encryption has failed due to other reasons
 */
पूर्णांक tipc_crypto_xmit(काष्ठा net *net, काष्ठा sk_buff **skb,
		     काष्ठा tipc_bearer *b, काष्ठा tipc_media_addr *dst,
		     काष्ठा tipc_node *__dnode)
अणु
	काष्ठा tipc_crypto *__rx = tipc_node_crypto_rx(__dnode);
	काष्ठा tipc_crypto *tx = tipc_net(net)->crypto_tx;
	काष्ठा tipc_crypto_stats __percpu *stats = tx->stats;
	काष्ठा tipc_msg *hdr = buf_msg(*skb);
	काष्ठा tipc_key key = tx->key;
	काष्ठा tipc_aead *aead = शून्य;
	u32 user = msg_user(hdr);
	u32 type = msg_type(hdr);
	पूर्णांक rc = -ENOKEY;
	u8 tx_key = 0;

	/* No encryption? */
	अगर (!tx->working)
		वापस 0;

	/* Pending key अगर peer has active on it or probing समय */
	अगर (unlikely(key.pending)) अणु
		tx_key = key.pending;
		अगर (!tx->key_master && !key.active)
			जाओ encrypt;
		अगर (__rx && atomic_पढ़ो(&__rx->peer_rx_active) == tx_key)
			जाओ encrypt;
		अगर (TIPC_SKB_CB(*skb)->xmit_type == SKB_PROBING) अणु
			pr_debug("%s: probing for key[%d]\n", tx->name,
				 key.pending);
			जाओ encrypt;
		पूर्ण
		अगर (user == LINK_CONFIG || user == LINK_PROTOCOL)
			tipc_crypto_clone_msg(net, *skb, b, dst, __dnode,
					      SKB_PROBING);
	पूर्ण

	/* Master key अगर this is a *vital* message or in grace period */
	अगर (tx->key_master) अणु
		tx_key = KEY_MASTER;
		अगर (!key.active)
			जाओ encrypt;
		अगर (TIPC_SKB_CB(*skb)->xmit_type == SKB_GRACING) अणु
			pr_debug("%s: gracing for msg (%d %d)\n", tx->name,
				 user, type);
			जाओ encrypt;
		पूर्ण
		अगर (user == LINK_CONFIG ||
		    (user == LINK_PROTOCOL && type == RESET_MSG) ||
		    (user == MSG_CRYPTO && type == KEY_DISTR_MSG) ||
		    समय_beक्रमe(jअगरfies, tx->समयr2 + TIPC_TX_GRACE_PERIOD)) अणु
			अगर (__rx && __rx->key_master &&
			    !atomic_पढ़ो(&__rx->peer_rx_active))
				जाओ encrypt;
			अगर (!__rx) अणु
				अगर (likely(!tx->legacy_user))
					जाओ encrypt;
				tipc_crypto_clone_msg(net, *skb, b, dst,
						      __dnode, SKB_GRACING);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Else, use the active key अगर any */
	अगर (likely(key.active)) अणु
		tx_key = key.active;
		जाओ encrypt;
	पूर्ण

	जाओ निकास;

encrypt:
	aead = tipc_aead_get(tx->aead[tx_key]);
	अगर (unlikely(!aead))
		जाओ निकास;
	rc = tipc_ehdr_build(net, aead, tx_key, *skb, __rx);
	अगर (likely(rc > 0))
		rc = tipc_aead_encrypt(aead, *skb, b, dst, __dnode);

निकास:
	चयन (rc) अणु
	हाल 0:
		this_cpu_inc(stats->stat[STAT_OK]);
		अवरोध;
	हाल -EINPROGRESS:
	हाल -EBUSY:
		this_cpu_inc(stats->stat[STAT_ASYNC]);
		*skb = शून्य;
		वापस rc;
	शेष:
		this_cpu_inc(stats->stat[STAT_NOK]);
		अगर (rc == -ENOKEY)
			this_cpu_inc(stats->stat[STAT_NOKEYS]);
		अन्यथा अगर (rc == -EKEYREVOKED)
			this_cpu_inc(stats->stat[STAT_BADKEYS]);
		kमुक्त_skb(*skb);
		*skb = शून्य;
		अवरोध;
	पूर्ण

	tipc_aead_put(aead);
	वापस rc;
पूर्ण

/**
 * tipc_crypto_rcv - Decrypt an encrypted TIPC message from peer
 * @net: काष्ठा net
 * @rx: RX crypto handle
 * @skb: input/output message skb poपूर्णांकer
 * @b: bearer where the message has been received
 *
 * If the decryption is successful, the decrypted skb is वापसed directly or
 * as the callback, the encryption header and auth tag will be trimed out
 * beक्रमe क्रमwarding to tipc_rcv() via the tipc_crypto_rcv_complete().
 * Otherwise, the skb will be मुक्तd!
 * Note: RX key(s) can be re-aligned, or in हाल of no key suitable, TX
 * cluster key(s) can be taken क्रम decryption (- recursive).
 *
 * Return:
 * * 0                   : the decryption has successfully completed
 * * -EINPROGRESS/-EBUSY : the decryption is ongoing, a callback will be made
 * * -ENOKEY             : the decryption has failed due to no key
 * * -EBADMSG            : the decryption has failed due to bad message
 * * -ENOMEM             : the decryption has failed due to no memory
 * * < 0                 : the decryption has failed due to other reasons
 */
पूर्णांक tipc_crypto_rcv(काष्ठा net *net, काष्ठा tipc_crypto *rx,
		    काष्ठा sk_buff **skb, काष्ठा tipc_bearer *b)
अणु
	काष्ठा tipc_crypto *tx = tipc_net(net)->crypto_tx;
	काष्ठा tipc_crypto_stats __percpu *stats;
	काष्ठा tipc_aead *aead = शून्य;
	काष्ठा tipc_key key;
	पूर्णांक rc = -ENOKEY;
	u8 tx_key, n;

	tx_key = ((काष्ठा tipc_ehdr *)(*skb)->data)->tx_key;

	/* New peer?
	 * Let's try with TX key (i.e. cluster mode) & verअगरy the skb first!
	 */
	अगर (unlikely(!rx || tx_key == KEY_MASTER))
		जाओ pick_tx;

	/* Pick RX key according to TX key अगर any */
	key = rx->key;
	अगर (tx_key == key.active || tx_key == key.pending ||
	    tx_key == key.passive)
		जाओ decrypt;

	/* Unknown key, let's try to align RX key(s) */
	अगर (tipc_crypto_key_try_align(rx, tx_key))
		जाओ decrypt;

pick_tx:
	/* No key suitable? Try to pick one from TX... */
	aead = tipc_crypto_key_pick_tx(tx, rx, *skb, tx_key);
	अगर (aead)
		जाओ decrypt;
	जाओ निकास;

decrypt:
	rcu_पढ़ो_lock();
	अगर (!aead)
		aead = tipc_aead_get(rx->aead[tx_key]);
	rc = tipc_aead_decrypt(net, aead, *skb, b);
	rcu_पढ़ो_unlock();

निकास:
	stats = ((rx) ?: tx)->stats;
	चयन (rc) अणु
	हाल 0:
		this_cpu_inc(stats->stat[STAT_OK]);
		अवरोध;
	हाल -EINPROGRESS:
	हाल -EBUSY:
		this_cpu_inc(stats->stat[STAT_ASYNC]);
		*skb = शून्य;
		वापस rc;
	शेष:
		this_cpu_inc(stats->stat[STAT_NOK]);
		अगर (rc == -ENOKEY) अणु
			kमुक्त_skb(*skb);
			*skb = शून्य;
			अगर (rx) अणु
				/* Mark rx->nokey only अगर we करोnt have a
				 * pending received session key, nor a newer
				 * one i.e. in the next slot.
				 */
				n = key_next(tx_key);
				rx->nokey = !(rx->skey ||
					      rcu_access_poपूर्णांकer(rx->aead[n]));
				pr_debug_ratelimited("%s: nokey %d, key %d/%x\n",
						     rx->name, rx->nokey,
						     tx_key, rx->key.keys);
				tipc_node_put(rx->node);
			पूर्ण
			this_cpu_inc(stats->stat[STAT_NOKEYS]);
			वापस rc;
		पूर्ण अन्यथा अगर (rc == -EBADMSG) अणु
			this_cpu_inc(stats->stat[STAT_BADMSGS]);
		पूर्ण
		अवरोध;
	पूर्ण

	tipc_crypto_rcv_complete(net, aead, b, skb, rc);
	वापस rc;
पूर्ण

अटल व्योम tipc_crypto_rcv_complete(काष्ठा net *net, काष्ठा tipc_aead *aead,
				     काष्ठा tipc_bearer *b,
				     काष्ठा sk_buff **skb, पूर्णांक err)
अणु
	काष्ठा tipc_skb_cb *skb_cb = TIPC_SKB_CB(*skb);
	काष्ठा tipc_crypto *rx = aead->crypto;
	काष्ठा tipc_aead *पंचांगp = शून्य;
	काष्ठा tipc_ehdr *ehdr;
	काष्ठा tipc_node *n;

	/* Is this completed by TX? */
	अगर (unlikely(is_tx(aead->crypto))) अणु
		rx = skb_cb->tx_clone_ctx.rx;
		pr_debug("TX->RX(%s): err %d, aead %p, skb->next %p, flags %x\n",
			 (rx) ? tipc_node_get_id_str(rx->node) : "-", err, aead,
			 (*skb)->next, skb_cb->flags);
		pr_debug("skb_cb [recurs %d, last %p], tx->aead [%p %p %p]\n",
			 skb_cb->tx_clone_ctx.recurs, skb_cb->tx_clone_ctx.last,
			 aead->crypto->aead[1], aead->crypto->aead[2],
			 aead->crypto->aead[3]);
		अगर (unlikely(err)) अणु
			अगर (err == -EBADMSG && (*skb)->next)
				tipc_rcv(net, (*skb)->next, b);
			जाओ मुक्त_skb;
		पूर्ण

		अगर (likely((*skb)->next)) अणु
			kमुक्त_skb((*skb)->next);
			(*skb)->next = शून्य;
		पूर्ण
		ehdr = (काष्ठा tipc_ehdr *)(*skb)->data;
		अगर (!rx) अणु
			WARN_ON(ehdr->user != LINK_CONFIG);
			n = tipc_node_create(net, 0, ehdr->id, 0xffffu, 0,
					     true);
			rx = tipc_node_crypto_rx(n);
			अगर (unlikely(!rx))
				जाओ मुक्त_skb;
		पूर्ण

		/* Ignore cloning अगर it was TX master key */
		अगर (ehdr->tx_key == KEY_MASTER)
			जाओ rcv;
		अगर (tipc_aead_clone(&पंचांगp, aead) < 0)
			जाओ rcv;
		WARN_ON(!refcount_inc_not_zero(&पंचांगp->refcnt));
		अगर (tipc_crypto_key_attach(rx, पंचांगp, ehdr->tx_key, false) < 0) अणु
			tipc_aead_मुक्त(&पंचांगp->rcu);
			जाओ rcv;
		पूर्ण
		tipc_aead_put(aead);
		aead = पंचांगp;
	पूर्ण

	अगर (unlikely(err)) अणु
		tipc_aead_users_dec((काष्ठा tipc_aead __क्रमce __rcu *)aead, पूर्णांक_न्यून);
		जाओ मुक्त_skb;
	पूर्ण

	/* Set the RX key's user */
	tipc_aead_users_set((काष्ठा tipc_aead __क्रमce __rcu *)aead, 1);

	/* Mark this poपूर्णांक, RX works */
	rx->समयr1 = jअगरfies;

rcv:
	/* Remove ehdr & auth. tag prior to tipc_rcv() */
	ehdr = (काष्ठा tipc_ehdr *)(*skb)->data;

	/* Mark this poपूर्णांक, RX passive still works */
	अगर (rx->key.passive && ehdr->tx_key == rx->key.passive)
		rx->समयr2 = jअगरfies;

	skb_reset_network_header(*skb);
	skb_pull(*skb, tipc_ehdr_size(ehdr));
	pskb_trim(*skb, (*skb)->len - aead->authsize);

	/* Validate TIPCv2 message */
	अगर (unlikely(!tipc_msg_validate(skb))) अणु
		pr_err_ratelimited("Packet dropped after decryption!\n");
		जाओ मुक्त_skb;
	पूर्ण

	/* Ok, everything's fine, try to synch own keys according to peers' */
	tipc_crypto_key_synch(rx, *skb);

	/* Mark skb decrypted */
	skb_cb->decrypted = 1;

	/* Clear clone cxt अगर any */
	अगर (likely(!skb_cb->tx_clone_deferred))
		जाओ निकास;
	skb_cb->tx_clone_deferred = 0;
	स_रखो(&skb_cb->tx_clone_ctx, 0, माप(skb_cb->tx_clone_ctx));
	जाओ निकास;

मुक्त_skb:
	kमुक्त_skb(*skb);
	*skb = शून्य;

निकास:
	tipc_aead_put(aead);
	अगर (rx)
		tipc_node_put(rx->node);
पूर्ण

अटल व्योम tipc_crypto_करो_cmd(काष्ठा net *net, पूर्णांक cmd)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_crypto *tx = tn->crypto_tx, *rx;
	काष्ठा list_head *p;
	अचिन्हित पूर्णांक stat;
	पूर्णांक i, j, cpu;
	अक्षर buf[200];

	/* Currently only one command is supported */
	चयन (cmd) अणु
	हाल 0xfff1:
		जाओ prपूर्णांक_stats;
	शेष:
		वापस;
	पूर्ण

prपूर्णांक_stats:
	/* Prपूर्णांक a header */
	pr_info("\n=============== TIPC Crypto Statistics ===============\n\n");

	/* Prपूर्णांक key status */
	pr_info("Key status:\n");
	pr_info("TX(%7.7s)\n%s", tipc_own_id_string(net),
		tipc_crypto_key_dump(tx, buf));

	rcu_पढ़ो_lock();
	क्रम (p = tn->node_list.next; p != &tn->node_list; p = p->next) अणु
		rx = tipc_node_crypto_rx_by_list(p);
		pr_info("RX(%7.7s)\n%s", tipc_node_get_id_str(rx->node),
			tipc_crypto_key_dump(rx, buf));
	पूर्ण
	rcu_पढ़ो_unlock();

	/* Prपूर्णांक crypto statistics */
	क्रम (i = 0, j = 0; i < MAX_STATS; i++)
		j += scnम_लिखो(buf + j, 200 - j, "|%11s ", hstats[i]);
	pr_info("Counter     %s", buf);

	स_रखो(buf, '-', 115);
	buf[115] = '\0';
	pr_info("%s\n", buf);

	j = scnम_लिखो(buf, 200, "TX(%7.7s) ", tipc_own_id_string(net));
	क्रम_each_possible_cpu(cpu) अणु
		क्रम (i = 0; i < MAX_STATS; i++) अणु
			stat = per_cpu_ptr(tx->stats, cpu)->stat[i];
			j += scnम_लिखो(buf + j, 200 - j, "|%11d ", stat);
		पूर्ण
		pr_info("%s", buf);
		j = scnम_लिखो(buf, 200, "%12s", " ");
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम (p = tn->node_list.next; p != &tn->node_list; p = p->next) अणु
		rx = tipc_node_crypto_rx_by_list(p);
		j = scnम_लिखो(buf, 200, "RX(%7.7s) ",
			      tipc_node_get_id_str(rx->node));
		क्रम_each_possible_cpu(cpu) अणु
			क्रम (i = 0; i < MAX_STATS; i++) अणु
				stat = per_cpu_ptr(rx->stats, cpu)->stat[i];
				j += scnम_लिखो(buf + j, 200 - j, "|%11d ",
					       stat);
			पूर्ण
			pr_info("%s", buf);
			j = scnम_लिखो(buf, 200, "%12s", " ");
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	pr_info("\n======================== Done ========================\n");
पूर्ण

अटल अक्षर *tipc_crypto_key_dump(काष्ठा tipc_crypto *c, अक्षर *buf)
अणु
	काष्ठा tipc_key key = c->key;
	काष्ठा tipc_aead *aead;
	पूर्णांक k, i = 0;
	अक्षर *s;

	क्रम (k = KEY_MIN; k <= KEY_MAX; k++) अणु
		अगर (k == KEY_MASTER) अणु
			अगर (is_rx(c))
				जारी;
			अगर (समय_beक्रमe(jअगरfies,
					c->समयr2 + TIPC_TX_GRACE_PERIOD))
				s = "ACT";
			अन्यथा
				s = "PAS";
		पूर्ण अन्यथा अणु
			अगर (k == key.passive)
				s = "PAS";
			अन्यथा अगर (k == key.active)
				s = "ACT";
			अन्यथा अगर (k == key.pending)
				s = "PEN";
			अन्यथा
				s = "-";
		पूर्ण
		i += scnम_लिखो(buf + i, 200 - i, "\tKey%d: %s", k, s);

		rcu_पढ़ो_lock();
		aead = rcu_dereference(c->aead[k]);
		अगर (aead)
			i += scnम_लिखो(buf + i, 200 - i,
				       "{\"0x...%s\", \"%s\"}/%d:%d",
				       aead->hपूर्णांक,
				       (aead->mode == CLUSTER_KEY) ? "c" : "p",
				       atomic_पढ़ो(&aead->users),
				       refcount_पढ़ो(&aead->refcnt));
		rcu_पढ़ो_unlock();
		i += scnम_लिखो(buf + i, 200 - i, "\n");
	पूर्ण

	अगर (is_rx(c))
		i += scnम_लिखो(buf + i, 200 - i, "\tPeer RX active: %d\n",
			       atomic_पढ़ो(&c->peer_rx_active));

	वापस buf;
पूर्ण

अटल अक्षर *tipc_key_change_dump(काष्ठा tipc_key old, काष्ठा tipc_key new,
				  अक्षर *buf)
अणु
	काष्ठा tipc_key *key = &old;
	पूर्णांक k, i = 0;
	अक्षर *s;

	/* Output क्रमmat: "[%s %s %s] -> [%s %s %s]", max len = 32 */
again:
	i += scnम_लिखो(buf + i, 32 - i, "[");
	क्रम (k = KEY_1; k <= KEY_3; k++) अणु
		अगर (k == key->passive)
			s = "pas";
		अन्यथा अगर (k == key->active)
			s = "act";
		अन्यथा अगर (k == key->pending)
			s = "pen";
		अन्यथा
			s = "-";
		i += scnम_लिखो(buf + i, 32 - i,
			       (k != KEY_3) ? "%s " : "%s", s);
	पूर्ण
	अगर (key != &new) अणु
		i += scnम_लिखो(buf + i, 32 - i, "] -> ");
		key = &new;
		जाओ again;
	पूर्ण
	i += scnम_लिखो(buf + i, 32 - i, "]");
	वापस buf;
पूर्ण

/**
 * tipc_crypto_msg_rcv - Common 'MSG_CRYPTO' processing poपूर्णांक
 * @net: the काष्ठा net
 * @skb: the receiving message buffer
 */
व्योम tipc_crypto_msg_rcv(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	काष्ठा tipc_crypto *rx;
	काष्ठा tipc_msg *hdr;

	अगर (unlikely(skb_linearize(skb)))
		जाओ निकास;

	hdr = buf_msg(skb);
	rx = tipc_node_crypto_rx_by_addr(net, msg_prevnode(hdr));
	अगर (unlikely(!rx))
		जाओ निकास;

	चयन (msg_type(hdr)) अणु
	हाल KEY_DISTR_MSG:
		अगर (tipc_crypto_key_rcv(rx, hdr))
			जाओ निकास;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	tipc_node_put(rx->node);

निकास:
	kमुक्त_skb(skb);
पूर्ण

/**
 * tipc_crypto_key_distr - Distribute a TX key
 * @tx: the TX crypto
 * @key: the key's index
 * @dest: the destination tipc node, = शून्य अगर distributing to all nodes
 *
 * Return: 0 in हाल of success, otherwise < 0
 */
पूर्णांक tipc_crypto_key_distr(काष्ठा tipc_crypto *tx, u8 key,
			  काष्ठा tipc_node *dest)
अणु
	काष्ठा tipc_aead *aead;
	u32 dnode = tipc_node_get_addr(dest);
	पूर्णांक rc = -ENOKEY;

	अगर (!sysctl_tipc_key_exchange_enabled)
		वापस 0;

	अगर (key) अणु
		rcu_पढ़ो_lock();
		aead = tipc_aead_get(tx->aead[key]);
		अगर (likely(aead)) अणु
			rc = tipc_crypto_key_xmit(tx->net, aead->key,
						  aead->gen, aead->mode,
						  dnode);
			tipc_aead_put(aead);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	वापस rc;
पूर्ण

/**
 * tipc_crypto_key_xmit - Send a session key
 * @net: the काष्ठा net
 * @skey: the session key to be sent
 * @gen: the key's generation
 * @mode: the key's mode
 * @dnode: the destination node address, = 0 अगर broadcasting to all nodes
 *
 * The session key 'skey' is packed in a TIPC v2 'MSG_CRYPTO/KEY_DISTR_MSG'
 * as its data section, then xmit-ed through the uc/bc link.
 *
 * Return: 0 in हाल of success, otherwise < 0
 */
अटल पूर्णांक tipc_crypto_key_xmit(काष्ठा net *net, काष्ठा tipc_aead_key *skey,
				u16 gen, u8 mode, u32 dnode)
अणु
	काष्ठा sk_buff_head pkts;
	काष्ठा tipc_msg *hdr;
	काष्ठा sk_buff *skb;
	u16 size, cong_link_cnt;
	u8 *data;
	पूर्णांक rc;

	size = tipc_aead_key_size(skey);
	skb = tipc_buf_acquire(INT_H_SIZE + size, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = buf_msg(skb);
	tipc_msg_init(tipc_own_addr(net), hdr, MSG_CRYPTO, KEY_DISTR_MSG,
		      INT_H_SIZE, dnode);
	msg_set_size(hdr, INT_H_SIZE + size);
	msg_set_key_gen(hdr, gen);
	msg_set_key_mode(hdr, mode);

	data = msg_data(hdr);
	*((__be32 *)(data + TIPC_AEAD_ALG_NAME)) = htonl(skey->keylen);
	स_नकल(data, skey->alg_name, TIPC_AEAD_ALG_NAME);
	स_नकल(data + TIPC_AEAD_ALG_NAME + माप(__be32), skey->key,
	       skey->keylen);

	__skb_queue_head_init(&pkts);
	__skb_queue_tail(&pkts, skb);
	अगर (dnode)
		rc = tipc_node_xmit(net, &pkts, dnode, 0);
	अन्यथा
		rc = tipc_bcast_xmit(net, &pkts, &cong_link_cnt);

	वापस rc;
पूर्ण

/**
 * tipc_crypto_key_rcv - Receive a session key
 * @rx: the RX crypto
 * @hdr: the TIPC v2 message incl. the receiving session key in its data
 *
 * This function retrieves the session key in the message from peer, then
 * schedules a RX work to attach the key to the corresponding RX crypto.
 *
 * Return: "true" अगर the key has been scheduled क्रम attaching, otherwise
 * "false".
 */
अटल bool tipc_crypto_key_rcv(काष्ठा tipc_crypto *rx, काष्ठा tipc_msg *hdr)
अणु
	काष्ठा tipc_crypto *tx = tipc_net(rx->net)->crypto_tx;
	काष्ठा tipc_aead_key *skey = शून्य;
	u16 key_gen = msg_key_gen(hdr);
	u16 size = msg_data_sz(hdr);
	u8 *data = msg_data(hdr);

	spin_lock(&rx->lock);
	अगर (unlikely(rx->skey || (key_gen == rx->key_gen && rx->key.keys))) अणु
		pr_err("%s: key existed <%p>, gen %d vs %d\n", rx->name,
		       rx->skey, key_gen, rx->key_gen);
		जाओ निकास;
	पूर्ण

	/* Allocate memory क्रम the key */
	skey = kदो_स्मृति(size, GFP_ATOMIC);
	अगर (unlikely(!skey)) अणु
		pr_err("%s: unable to allocate memory for skey\n", rx->name);
		जाओ निकास;
	पूर्ण

	/* Copy key from msg data */
	skey->keylen = ntohl(*((__be32 *)(data + TIPC_AEAD_ALG_NAME)));
	स_नकल(skey->alg_name, data, TIPC_AEAD_ALG_NAME);
	स_नकल(skey->key, data + TIPC_AEAD_ALG_NAME + माप(__be32),
	       skey->keylen);

	/* Sanity check */
	अगर (unlikely(size != tipc_aead_key_size(skey))) अणु
		kमुक्त(skey);
		skey = शून्य;
		जाओ निकास;
	पूर्ण

	rx->key_gen = key_gen;
	rx->skey_mode = msg_key_mode(hdr);
	rx->skey = skey;
	rx->nokey = 0;
	mb(); /* क्रम nokey flag */

निकास:
	spin_unlock(&rx->lock);

	/* Schedule the key attaching on this crypto */
	अगर (likely(skey && queue_delayed_work(tx->wq, &rx->work, 0)))
		वापस true;

	वापस false;
पूर्ण

/**
 * tipc_crypto_work_rx - Scheduled RX works handler
 * @work: the काष्ठा RX work
 *
 * The function processes the previous scheduled works i.e. distributing TX key
 * or attaching a received session key on RX crypto.
 */
अटल व्योम tipc_crypto_work_rx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा tipc_crypto *rx = container_of(dwork, काष्ठा tipc_crypto, work);
	काष्ठा tipc_crypto *tx = tipc_net(rx->net)->crypto_tx;
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(5000);
	bool resched = false;
	u8 key;
	पूर्णांक rc;

	/* Case 1: Distribute TX key to peer अगर scheduled */
	अगर (atomic_cmpxchg(&rx->key_distr,
			   KEY_DISTR_SCHED,
			   KEY_DISTR_COMPL) == KEY_DISTR_SCHED) अणु
		/* Always pick the newest one क्रम distributing */
		key = tx->key.pending ?: tx->key.active;
		rc = tipc_crypto_key_distr(tx, key, rx->node);
		अगर (unlikely(rc))
			pr_warn("%s: unable to distr key[%d] to %s, err %d\n",
				tx->name, key, tipc_node_get_id_str(rx->node),
				rc);

		/* Sched क्रम key_distr releasing */
		resched = true;
	पूर्ण अन्यथा अणु
		atomic_cmpxchg(&rx->key_distr, KEY_DISTR_COMPL, 0);
	पूर्ण

	/* Case 2: Attach a pending received session key from peer अगर any */
	अगर (rx->skey) अणु
		rc = tipc_crypto_key_init(rx, rx->skey, rx->skey_mode, false);
		अगर (unlikely(rc < 0))
			pr_warn("%s: unable to attach received skey, err %d\n",
				rx->name, rc);
		चयन (rc) अणु
		हाल -EBUSY:
		हाल -ENOMEM:
			/* Resched the key attaching */
			resched = true;
			अवरोध;
		शेष:
			synchronize_rcu();
			kमुक्त(rx->skey);
			rx->skey = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (resched && queue_delayed_work(tx->wq, &rx->work, delay))
		वापस;

	tipc_node_put(rx->node);
पूर्ण

/**
 * tipc_crypto_rekeying_sched - (Re)schedule rekeying w/o new पूर्णांकerval
 * @tx: TX crypto
 * @changed: अगर the rekeying needs to be rescheduled with new पूर्णांकerval
 * @new_पूर्णांकv: new rekeying पूर्णांकerval (when "changed" = true)
 */
व्योम tipc_crypto_rekeying_sched(काष्ठा tipc_crypto *tx, bool changed,
				u32 new_पूर्णांकv)
अणु
	अचिन्हित दीर्घ delay;
	bool now = false;

	अगर (changed) अणु
		अगर (new_पूर्णांकv == TIPC_REKEYING_NOW)
			now = true;
		अन्यथा
			tx->rekeying_पूर्णांकv = new_पूर्णांकv;
		cancel_delayed_work_sync(&tx->work);
	पूर्ण

	अगर (tx->rekeying_पूर्णांकv || now) अणु
		delay = (now) ? 0 : tx->rekeying_पूर्णांकv * 60 * 1000;
		queue_delayed_work(tx->wq, &tx->work, msecs_to_jअगरfies(delay));
	पूर्ण
पूर्ण

/**
 * tipc_crypto_work_tx - Scheduled TX works handler
 * @work: the काष्ठा TX work
 *
 * The function processes the previous scheduled work, i.e. key rekeying, by
 * generating a new session key based on current one, then attaching it to the
 * TX crypto and finally distributing it to peers. It also re-schedules the
 * rekeying अगर needed.
 */
अटल व्योम tipc_crypto_work_tx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा tipc_crypto *tx = container_of(dwork, काष्ठा tipc_crypto, work);
	काष्ठा tipc_aead_key *skey = शून्य;
	काष्ठा tipc_key key = tx->key;
	काष्ठा tipc_aead *aead;
	पूर्णांक rc = -ENOMEM;

	अगर (unlikely(key.pending))
		जाओ resched;

	/* Take current key as a ढाँचा */
	rcu_पढ़ो_lock();
	aead = rcu_dereference(tx->aead[key.active ?: KEY_MASTER]);
	अगर (unlikely(!aead)) अणु
		rcu_पढ़ो_unlock();
		/* At least one key should exist क्रम securing */
		वापस;
	पूर्ण

	/* Lets duplicate it first */
	skey = kmemdup(aead->key, tipc_aead_key_size(aead->key), GFP_ATOMIC);
	rcu_पढ़ो_unlock();

	/* Now, generate new key, initiate & distribute it */
	अगर (likely(skey)) अणु
		rc = tipc_aead_key_generate(skey) ?:
		     tipc_crypto_key_init(tx, skey, PER_NODE_KEY, false);
		अगर (likely(rc > 0))
			rc = tipc_crypto_key_distr(tx, rc, शून्य);
		kमुक्त_sensitive(skey);
	पूर्ण

	अगर (unlikely(rc))
		pr_warn_ratelimited("%s: rekeying returns %d\n", tx->name, rc);

resched:
	/* Re-schedule rekeying अगर any */
	tipc_crypto_rekeying_sched(tx, false, 0);
पूर्ण
