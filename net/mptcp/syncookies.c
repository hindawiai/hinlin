<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/skbuff.h>

#समावेश "protocol.h"

/* Syncookies करो not work क्रम JOIN requests.
 *
 * Unlike MP_CAPABLE, where the ACK cookie contains the needed MPTCP
 * options to reस्थिरruct the initial syn state, MP_JOIN करोes not contain
 * the token to obtain the mptcp socket nor the server-generated nonce
 * that was used in the cookie SYN/ACK response.
 *
 * Keep a small best efक्रमt state table to store the syn/synack data,
 * indexed by skb hash.
 *
 * A MP_JOIN SYN packet handled by syn cookies is only stored अगर the 32bit
 * token matches a known mptcp connection that can still accept more subflows.
 *
 * There is no समयout handling -- state is only re-स्थिरructed
 * when the TCP ACK passed the cookie validation check.
 */

काष्ठा join_entry अणु
	u32 token;
	u32 remote_nonce;
	u32 local_nonce;
	u8 join_id;
	u8 local_id;
	u8 backup;
	u8 valid;
पूर्ण;

#घोषणा COOKIE_JOIN_SLOTS	1024

अटल काष्ठा join_entry join_entries[COOKIE_JOIN_SLOTS] __cacheline_aligned_in_smp;
अटल spinlock_t join_entry_locks[COOKIE_JOIN_SLOTS] __cacheline_aligned_in_smp;

अटल u32 mptcp_join_entry_hash(काष्ठा sk_buff *skb, काष्ठा net *net)
अणु
	u32 i = skb_get_hash(skb) ^ net_hash_mix(net);

	वापस i % ARRAY_SIZE(join_entries);
पूर्ण

अटल व्योम mptcp_join_store_state(काष्ठा join_entry *entry,
				   स्थिर काष्ठा mptcp_subflow_request_sock *subflow_req)
अणु
	entry->token = subflow_req->token;
	entry->remote_nonce = subflow_req->remote_nonce;
	entry->local_nonce = subflow_req->local_nonce;
	entry->backup = subflow_req->backup;
	entry->join_id = subflow_req->remote_id;
	entry->local_id = subflow_req->local_id;
	entry->valid = 1;
पूर्ण

व्योम subflow_init_req_cookie_join_save(स्थिर काष्ठा mptcp_subflow_request_sock *subflow_req,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = पढ़ो_pnet(&subflow_req->sk.req.ireq_net);
	u32 i = mptcp_join_entry_hash(skb, net);

	/* No use in रुकोing अगर other cpu is alपढ़ोy using this slot --
	 * would overग_लिखो the data that got stored.
	 */
	spin_lock_bh(&join_entry_locks[i]);
	mptcp_join_store_state(&join_entries[i], subflow_req);
	spin_unlock_bh(&join_entry_locks[i]);
पूर्ण

/* Called क्रम a cookie-ack with MP_JOIN option present.
 * Look up the saved state based on skb hash & check token matches msk
 * in same netns.
 *
 * Caller will check msk can still accept another subflow.  The hmac
 * present in the cookie ACK mptcp option space will be checked later.
 */
bool mptcp_token_join_cookie_init_state(काष्ठा mptcp_subflow_request_sock *subflow_req,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = पढ़ो_pnet(&subflow_req->sk.req.ireq_net);
	u32 i = mptcp_join_entry_hash(skb, net);
	काष्ठा mptcp_sock *msk;
	काष्ठा join_entry *e;

	e = &join_entries[i];

	spin_lock_bh(&join_entry_locks[i]);

	अगर (e->valid == 0) अणु
		spin_unlock_bh(&join_entry_locks[i]);
		वापस false;
	पूर्ण

	e->valid = 0;

	msk = mptcp_token_get_sock(e->token);
	अगर (!msk) अणु
		spin_unlock_bh(&join_entry_locks[i]);
		वापस false;
	पूर्ण

	/* If this fails, the token got re-used in the mean समय by another
	 * mptcp socket in a dअगरferent netns, i.e. entry is outdated.
	 */
	अगर (!net_eq(sock_net((काष्ठा sock *)msk), net))
		जाओ err_put;

	subflow_req->remote_nonce = e->remote_nonce;
	subflow_req->local_nonce = e->local_nonce;
	subflow_req->backup = e->backup;
	subflow_req->remote_id = e->join_id;
	subflow_req->token = e->token;
	subflow_req->msk = msk;
	spin_unlock_bh(&join_entry_locks[i]);
	वापस true;

err_put:
	spin_unlock_bh(&join_entry_locks[i]);
	sock_put((काष्ठा sock *)msk);
	वापस false;
पूर्ण

व्योम __init mptcp_join_cookie_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < COOKIE_JOIN_SLOTS; i++)
		spin_lock_init(&join_entry_locks[i]);
पूर्ण
