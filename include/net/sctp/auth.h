<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel implementation
 * (C) Copyright 2007 Hewlett-Packard Development Company, L.P.
 *
 * This file is part of the SCTP kernel implementation
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *   Vlad Yasevich     <vladislav.yasevich@hp.com>
 */

#अगर_अघोषित __sctp_auth_h__
#घोषणा __sctp_auth_h__

#समावेश <linux/list.h>
#समावेश <linux/refcount.h>

काष्ठा sctp_endpoपूर्णांक;
काष्ठा sctp_association;
काष्ठा sctp_authkey;
काष्ठा sctp_hmacalgo;
काष्ठा crypto_shash;

/*
 * Define a generic काष्ठा that will hold all the info
 * necessary क्रम an HMAC transक्रमm
 */
काष्ठा sctp_hmac अणु
	__u16 hmac_id;		/* one of the above ids */
	अक्षर *hmac_name;	/* name क्रम loading */
	__u16 hmac_len;		/* length of the signature */
पूर्ण;

/* This is generic काष्ठाure that containst authentication bytes used
 * as keying material.  It's a what is referred to as byte-vector all
 * over SCTP-AUTH
 */
काष्ठा sctp_auth_bytes अणु
	refcount_t refcnt;
	__u32 len;
	__u8  data[];
पूर्ण;

/* Definition क्रम a shared key, weather endpoपूर्णांक or association */
काष्ठा sctp_shared_key अणु
	काष्ठा list_head key_list;
	काष्ठा sctp_auth_bytes *key;
	refcount_t refcnt;
	__u16 key_id;
	__u8 deactivated;
पूर्ण;

#घोषणा key_क्रम_each(__key, __list_head) \
	list_क्रम_each_entry(__key, __list_head, key_list)

#घोषणा key_क्रम_each_safe(__key, __पंचांगp, __list_head) \
	list_क्रम_each_entry_safe(__key, __पंचांगp, __list_head, key_list)

अटल अंतरभूत व्योम sctp_auth_key_hold(काष्ठा sctp_auth_bytes *key)
अणु
	अगर (!key)
		वापस;

	refcount_inc(&key->refcnt);
पूर्ण

व्योम sctp_auth_key_put(काष्ठा sctp_auth_bytes *key);
काष्ठा sctp_shared_key *sctp_auth_shkey_create(__u16 key_id, gfp_t gfp);
व्योम sctp_auth_destroy_keys(काष्ठा list_head *keys);
पूर्णांक sctp_auth_asoc_init_active_key(काष्ठा sctp_association *asoc, gfp_t gfp);
काष्ठा sctp_shared_key *sctp_auth_get_shkey(
				स्थिर काष्ठा sctp_association *asoc,
				__u16 key_id);
पूर्णांक sctp_auth_asoc_copy_shkeys(स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				काष्ठा sctp_association *asoc,
				gfp_t gfp);
पूर्णांक sctp_auth_init_hmacs(काष्ठा sctp_endpoपूर्णांक *ep, gfp_t gfp);
व्योम sctp_auth_destroy_hmacs(काष्ठा crypto_shash *auth_hmacs[]);
काष्ठा sctp_hmac *sctp_auth_get_hmac(__u16 hmac_id);
काष्ठा sctp_hmac *sctp_auth_asoc_get_hmac(स्थिर काष्ठा sctp_association *asoc);
व्योम sctp_auth_asoc_set_शेष_hmac(काष्ठा sctp_association *asoc,
				     काष्ठा sctp_hmac_algo_param *hmacs);
पूर्णांक sctp_auth_asoc_verअगरy_hmac_id(स्थिर काष्ठा sctp_association *asoc,
				    __be16 hmac_id);
पूर्णांक sctp_auth_send_cid(क्रमागत sctp_cid chunk,
		       स्थिर काष्ठा sctp_association *asoc);
पूर्णांक sctp_auth_recv_cid(क्रमागत sctp_cid chunk,
		       स्थिर काष्ठा sctp_association *asoc);
व्योम sctp_auth_calculate_hmac(स्थिर काष्ठा sctp_association *asoc,
			      काष्ठा sk_buff *skb, काष्ठा sctp_auth_chunk *auth,
			      काष्ठा sctp_shared_key *ep_key, gfp_t gfp);
व्योम sctp_auth_shkey_release(काष्ठा sctp_shared_key *sh_key);
व्योम sctp_auth_shkey_hold(काष्ठा sctp_shared_key *sh_key);

/* API Helpers */
पूर्णांक sctp_auth_ep_add_chunkid(काष्ठा sctp_endpoपूर्णांक *ep, __u8 chunk_id);
पूर्णांक sctp_auth_ep_set_hmacs(काष्ठा sctp_endpoपूर्णांक *ep,
			    काष्ठा sctp_hmacalgo *hmacs);
पूर्णांक sctp_auth_set_key(काष्ठा sctp_endpoपूर्णांक *ep, काष्ठा sctp_association *asoc,
		      काष्ठा sctp_authkey *auth_key);
पूर्णांक sctp_auth_set_active_key(काष्ठा sctp_endpoपूर्णांक *ep,
			     काष्ठा sctp_association *asoc, __u16 key_id);
पूर्णांक sctp_auth_del_key_id(काष्ठा sctp_endpoपूर्णांक *ep,
			 काष्ठा sctp_association *asoc, __u16 key_id);
पूर्णांक sctp_auth_deact_key_id(काष्ठा sctp_endpoपूर्णांक *ep,
			   काष्ठा sctp_association *asoc, __u16 key_id);
पूर्णांक sctp_auth_init(काष्ठा sctp_endpoपूर्णांक *ep, gfp_t gfp);
व्योम sctp_auth_मुक्त(काष्ठा sctp_endpoपूर्णांक *ep);

#पूर्ण_अगर
