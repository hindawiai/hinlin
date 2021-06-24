<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Multipath TCP token management
 * Copyright (c) 2017 - 2019, Intel Corporation.
 *
 * Note: This code is based on mptcp_ctrl.c from multipath-tcp.org,
 *       authored by:
 *
 *       Sथऊbastien Barrथऊ <sebastien.barre@uclouvain.be>
 *       Christoph Paasch <christoph.paasch@uclouvain.be>
 *       Jaakko Korkeaniemi <jaakko.korkeaniemi@aalto.fi>
 *       Gregory Detal <gregory.detal@uclouvain.be>
 *       Fabien Duchथऋne <fabien.duchene@uclouvain.be>
 *       Andreas Seelinger <Andreas.Seelinger@rwth-aachen.de>
 *       Lavkesh Lahngir <lavkesh51@gmail.com>
 *       Andreas Ripke <ripke@neclab.eu>
 *       Vlad Dogaru <vlad.करोgaru@पूर्णांकel.com>
 *       Octavian Purdila <octavian.purdila@पूर्णांकel.com>
 *       John Ronan <jronan@tssg.org>
 *       Catalin Nicutar <catalin.nicutar@gmail.com>
 *       Bअक्रमon Heller <bअक्रमonh@stanक्रमd.edu>
 */

#घोषणा pr_fmt(fmt) "MPTCP: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/memblock.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <net/sock.h>
#समावेश <net/inet_common.h>
#समावेश <net/protocol.h>
#समावेश <net/mptcp.h>
#समावेश "protocol.h"

#घोषणा TOKEN_MAX_RETRIES	4
#घोषणा TOKEN_MAX_CHAIN_LEN	4

काष्ठा token_bucket अणु
	spinlock_t		lock;
	पूर्णांक			chain_len;
	काष्ठा hlist_nulls_head	req_chain;
	काष्ठा hlist_nulls_head	msk_chain;
पूर्ण;

अटल काष्ठा token_bucket *token_hash __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक token_mask __पढ़ो_mostly;

अटल काष्ठा token_bucket *token_bucket(u32 token)
अणु
	वापस &token_hash[token & token_mask];
पूर्ण

/* called with bucket lock held */
अटल काष्ठा mptcp_subflow_request_sock *
__token_lookup_req(काष्ठा token_bucket *t, u32 token)
अणु
	काष्ठा mptcp_subflow_request_sock *req;
	काष्ठा hlist_nulls_node *pos;

	hlist_nulls_क्रम_each_entry_rcu(req, pos, &t->req_chain, token_node)
		अगर (req->token == token)
			वापस req;
	वापस शून्य;
पूर्ण

/* called with bucket lock held */
अटल काष्ठा mptcp_sock *
__token_lookup_msk(काष्ठा token_bucket *t, u32 token)
अणु
	काष्ठा hlist_nulls_node *pos;
	काष्ठा sock *sk;

	sk_nulls_क्रम_each_rcu(sk, pos, &t->msk_chain)
		अगर (mptcp_sk(sk)->token == token)
			वापस mptcp_sk(sk);
	वापस शून्य;
पूर्ण

अटल bool __token_bucket_busy(काष्ठा token_bucket *t, u32 token)
अणु
	वापस !token || t->chain_len >= TOKEN_MAX_CHAIN_LEN ||
	       __token_lookup_req(t, token) || __token_lookup_msk(t, token);
पूर्ण

अटल व्योम mptcp_crypto_key_gen_sha(u64 *key, u32 *token, u64 *idsn)
अणु
	/* we might consider a faster version that computes the key as a
	 * hash of some inक्रमmation available in the MPTCP socket. Use
	 * अक्रमom data at the moment, as it's probably the safest option
	 * in हाल multiple sockets are खोलोed in dअगरferent namespaces at
	 * the same समय.
	 */
	get_अक्रमom_bytes(key, माप(u64));
	mptcp_crypto_key_sha(*key, token, idsn);
पूर्ण

/**
 * mptcp_token_new_request - create new key/idsn/token क्रम subflow_request
 * @req: the request socket
 *
 * This function is called when a new mptcp connection is coming in.
 *
 * It creates a unique token to identअगरy the new mptcp connection,
 * a secret local key and the initial data sequence number (idsn).
 *
 * Returns 0 on success.
 */
पूर्णांक mptcp_token_new_request(काष्ठा request_sock *req)
अणु
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);
	काष्ठा token_bucket *bucket;
	u32 token;

	mptcp_crypto_key_sha(subflow_req->local_key,
			     &subflow_req->token,
			     &subflow_req->idsn);
	pr_debug("req=%p local_key=%llu, token=%u, idsn=%llu\n",
		 req, subflow_req->local_key, subflow_req->token,
		 subflow_req->idsn);

	token = subflow_req->token;
	bucket = token_bucket(token);
	spin_lock_bh(&bucket->lock);
	अगर (__token_bucket_busy(bucket, token)) अणु
		spin_unlock_bh(&bucket->lock);
		वापस -EBUSY;
	पूर्ण

	hlist_nulls_add_head_rcu(&subflow_req->token_node, &bucket->req_chain);
	bucket->chain_len++;
	spin_unlock_bh(&bucket->lock);
	वापस 0;
पूर्ण

/**
 * mptcp_token_new_connect - create new key/idsn/token क्रम subflow
 * @sk: the socket that will initiate a connection
 *
 * This function is called when a new outgoing mptcp connection is
 * initiated.
 *
 * It creates a unique token to identअगरy the new mptcp connection,
 * a secret local key and the initial data sequence number (idsn).
 *
 * On success, the mptcp connection can be found again using
 * the computed token at a later समय, this is needed to process
 * join requests.
 *
 * वापसs 0 on success.
 */
पूर्णांक mptcp_token_new_connect(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(sk);
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);
	पूर्णांक retries = TOKEN_MAX_RETRIES;
	काष्ठा token_bucket *bucket;

	pr_debug("ssk=%p, local_key=%llu, token=%u, idsn=%llu\n",
		 sk, subflow->local_key, subflow->token, subflow->idsn);

again:
	mptcp_crypto_key_gen_sha(&subflow->local_key, &subflow->token,
				 &subflow->idsn);

	bucket = token_bucket(subflow->token);
	spin_lock_bh(&bucket->lock);
	अगर (__token_bucket_busy(bucket, subflow->token)) अणु
		spin_unlock_bh(&bucket->lock);
		अगर (!--retries)
			वापस -EBUSY;
		जाओ again;
	पूर्ण

	WRITE_ONCE(msk->token, subflow->token);
	__sk_nulls_add_node_rcu((काष्ठा sock *)msk, &bucket->msk_chain);
	bucket->chain_len++;
	spin_unlock_bh(&bucket->lock);
	वापस 0;
पूर्ण

/**
 * mptcp_token_accept - replace a req sk with full sock in token hash
 * @req: the request socket to be हटाओd
 * @msk: the just cloned socket linked to the new connection
 *
 * Called when a SYN packet creates a new logical connection, i.e.
 * is not a join request.
 */
व्योम mptcp_token_accept(काष्ठा mptcp_subflow_request_sock *req,
			काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_request_sock *pos;
	काष्ठा token_bucket *bucket;

	bucket = token_bucket(req->token);
	spin_lock_bh(&bucket->lock);

	/* pedantic lookup check क्रम the moved token */
	pos = __token_lookup_req(bucket, req->token);
	अगर (!WARN_ON_ONCE(pos != req))
		hlist_nulls_del_init_rcu(&req->token_node);
	__sk_nulls_add_node_rcu((काष्ठा sock *)msk, &bucket->msk_chain);
	spin_unlock_bh(&bucket->lock);
पूर्ण

bool mptcp_token_exists(u32 token)
अणु
	काष्ठा hlist_nulls_node *pos;
	काष्ठा token_bucket *bucket;
	काष्ठा mptcp_sock *msk;
	काष्ठा sock *sk;

	rcu_पढ़ो_lock();
	bucket = token_bucket(token);

again:
	sk_nulls_क्रम_each_rcu(sk, pos, &bucket->msk_chain) अणु
		msk = mptcp_sk(sk);
		अगर (READ_ONCE(msk->token) == token)
			जाओ found;
	पूर्ण
	अगर (get_nulls_value(pos) != (token & token_mask))
		जाओ again;

	rcu_पढ़ो_unlock();
	वापस false;
found:
	rcu_पढ़ो_unlock();
	वापस true;
पूर्ण

/**
 * mptcp_token_get_sock - retrieve mptcp connection sock using its token
 * @token: token of the mptcp connection to retrieve
 *
 * This function वापसs the mptcp connection काष्ठाure with the given token.
 * A reference count on the mptcp socket वापसed is taken.
 *
 * वापसs शून्य अगर no connection with the given token value exists.
 */
काष्ठा mptcp_sock *mptcp_token_get_sock(u32 token)
अणु
	काष्ठा hlist_nulls_node *pos;
	काष्ठा token_bucket *bucket;
	काष्ठा mptcp_sock *msk;
	काष्ठा sock *sk;

	rcu_पढ़ो_lock();
	bucket = token_bucket(token);

again:
	sk_nulls_क्रम_each_rcu(sk, pos, &bucket->msk_chain) अणु
		msk = mptcp_sk(sk);
		अगर (READ_ONCE(msk->token) != token)
			जारी;
		अगर (!refcount_inc_not_zero(&sk->sk_refcnt))
			जाओ not_found;
		अगर (READ_ONCE(msk->token) != token) अणु
			sock_put(sk);
			जाओ again;
		पूर्ण
		जाओ found;
	पूर्ण
	अगर (get_nulls_value(pos) != (token & token_mask))
		जाओ again;

not_found:
	msk = शून्य;

found:
	rcu_पढ़ो_unlock();
	वापस msk;
पूर्ण
EXPORT_SYMBOL_GPL(mptcp_token_get_sock);

/**
 * mptcp_token_iter_next - iterate over the token container from given pos
 * @net: namespace to be iterated
 * @s_slot: start slot number
 * @s_num: start number inside the given lock
 *
 * This function वापसs the first mptcp connection काष्ठाure found inside the
 * token container starting from the specअगरied position, or शून्य.
 *
 * On successful iteration, the iterator is move to the next position and the
 * the acquires a reference to the वापसed socket.
 */
काष्ठा mptcp_sock *mptcp_token_iter_next(स्थिर काष्ठा net *net, दीर्घ *s_slot,
					 दीर्घ *s_num)
अणु
	काष्ठा mptcp_sock *ret = शून्य;
	काष्ठा hlist_nulls_node *pos;
	पूर्णांक slot, num = 0;

	क्रम (slot = *s_slot; slot <= token_mask; *s_num = 0, slot++) अणु
		काष्ठा token_bucket *bucket = &token_hash[slot];
		काष्ठा sock *sk;

		num = 0;

		अगर (hlist_nulls_empty(&bucket->msk_chain))
			जारी;

		rcu_पढ़ो_lock();
		sk_nulls_क्रम_each_rcu(sk, pos, &bucket->msk_chain) अणु
			++num;
			अगर (!net_eq(sock_net(sk), net))
				जारी;

			अगर (num <= *s_num)
				जारी;

			अगर (!refcount_inc_not_zero(&sk->sk_refcnt))
				जारी;

			अगर (!net_eq(sock_net(sk), net)) अणु
				sock_put(sk);
				जारी;
			पूर्ण

			ret = mptcp_sk(sk);
			rcu_पढ़ो_unlock();
			जाओ out;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

out:
	*s_slot = slot;
	*s_num = num;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mptcp_token_iter_next);

/**
 * mptcp_token_destroy_request - हटाओ mptcp connection/token
 * @req: mptcp request socket dropping the token
 *
 * Remove the token associated to @req.
 */
व्योम mptcp_token_destroy_request(काष्ठा request_sock *req)
अणु
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);
	काष्ठा mptcp_subflow_request_sock *pos;
	काष्ठा token_bucket *bucket;

	अगर (hlist_nulls_unhashed(&subflow_req->token_node))
		वापस;

	bucket = token_bucket(subflow_req->token);
	spin_lock_bh(&bucket->lock);
	pos = __token_lookup_req(bucket, subflow_req->token);
	अगर (!WARN_ON_ONCE(pos != subflow_req)) अणु
		hlist_nulls_del_init_rcu(&pos->token_node);
		bucket->chain_len--;
	पूर्ण
	spin_unlock_bh(&bucket->lock);
पूर्ण

/**
 * mptcp_token_destroy - हटाओ mptcp connection/token
 * @msk: mptcp connection dropping the token
 *
 * Remove the token associated to @msk
 */
व्योम mptcp_token_destroy(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा token_bucket *bucket;
	काष्ठा mptcp_sock *pos;

	अगर (sk_unhashed((काष्ठा sock *)msk))
		वापस;

	bucket = token_bucket(msk->token);
	spin_lock_bh(&bucket->lock);
	pos = __token_lookup_msk(bucket, msk->token);
	अगर (!WARN_ON_ONCE(pos != msk)) अणु
		__sk_nulls_del_node_init_rcu((काष्ठा sock *)pos);
		bucket->chain_len--;
	पूर्ण
	spin_unlock_bh(&bucket->lock);
पूर्ण

व्योम __init mptcp_token_init(व्योम)
अणु
	पूर्णांक i;

	token_hash = alloc_large_प्रणाली_hash("MPTCP token",
					     माप(काष्ठा token_bucket),
					     0,
					     20,/* one slot per 1MB of memory */
					     HASH_ZERO,
					     शून्य,
					     &token_mask,
					     0,
					     64 * 1024);
	क्रम (i = 0; i < token_mask + 1; ++i) अणु
		INIT_HLIST_शून्यS_HEAD(&token_hash[i].req_chain, i);
		INIT_HLIST_शून्यS_HEAD(&token_hash[i].msk_chain, i);
		spin_lock_init(&token_hash[i].lock);
	पूर्ण
पूर्ण

#अगर IS_MODULE(CONFIG_MPTCP_KUNIT_TEST)
EXPORT_SYMBOL_GPL(mptcp_token_new_request);
EXPORT_SYMBOL_GPL(mptcp_token_new_connect);
EXPORT_SYMBOL_GPL(mptcp_token_accept);
EXPORT_SYMBOL_GPL(mptcp_token_destroy_request);
EXPORT_SYMBOL_GPL(mptcp_token_destroy);
#पूर्ण_अगर
