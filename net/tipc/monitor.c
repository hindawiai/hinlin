<शैली गुरु>
/*
 * net/tipc/monitor.c
 *
 * Copyright (c) 2016, Ericsson AB
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

#समावेश <net/genetlink.h>
#समावेश "core.h"
#समावेश "addr.h"
#समावेश "monitor.h"
#समावेश "bearer.h"

#घोषणा MAX_MON_DOMAIN       64
#घोषणा MON_TIMEOUT          120000
#घोषणा MAX_PEER_DOWN_EVENTS 4

/* काष्ठा tipc_mon_करोमुख्य: करोमुख्य record to be transferred between peers
 * @len: actual size of करोमुख्य record
 * @gen: current generation of sender's करोमुख्य
 * @ack_gen: most recent generation of self's करोमुख्य acked by peer
 * @member_cnt: number of करोमुख्य member nodes described in this record
 * @up_map: bit map indicating which of the members the sender considers up
 * @members: identity of the करोमुख्य members
 */
काष्ठा tipc_mon_करोमुख्य अणु
	u16 len;
	u16 gen;
	u16 ack_gen;
	u16 member_cnt;
	u64 up_map;
	u32 members[MAX_MON_DOMAIN];
पूर्ण;

/* काष्ठा tipc_peer: state of a peer node and its करोमुख्य
 * @addr: tipc node identity of peer
 * @head_map: shows which other nodes currently consider peer 'up'
 * @करोमुख्य: most recent करोमुख्य record from peer
 * @hash: position in hashed lookup list
 * @list: position in linked list, in circular ascending order by 'addr'
 * @applied: number of reported करोमुख्य members applied on this monitor list
 * @is_up: peer is up as seen from this node
 * @is_head: peer is asचिन्हित करोमुख्य head as seen from this node
 * @is_local: peer is in local करोमुख्य and should be continuously monitored
 * @करोwn_cnt: - numbers of other peers which have reported this on lost
 */
काष्ठा tipc_peer अणु
	u32 addr;
	काष्ठा tipc_mon_करोमुख्य *करोमुख्य;
	काष्ठा hlist_node hash;
	काष्ठा list_head list;
	u8 applied;
	u8 करोwn_cnt;
	bool is_up;
	bool is_head;
	bool is_local;
पूर्ण;

काष्ठा tipc_monitor अणु
	काष्ठा hlist_head peers[NODE_HTABLE_SIZE];
	पूर्णांक peer_cnt;
	काष्ठा tipc_peer *self;
	rwlock_t lock;
	काष्ठा tipc_mon_करोमुख्य cache;
	u16 list_gen;
	u16 करोm_gen;
	काष्ठा net *net;
	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ समयr_पूर्णांकv;
पूर्ण;

अटल काष्ठा tipc_monitor *tipc_monitor(काष्ठा net *net, पूर्णांक bearer_id)
अणु
	वापस tipc_net(net)->monitors[bearer_id];
पूर्ण

स्थिर पूर्णांक tipc_max_करोमुख्य_size = माप(काष्ठा tipc_mon_करोमुख्य);

अटल अंतरभूत u16 mon_cpu_to_le16(u16 val)
अणु
	वापस (__क्रमce __u16)htons(val);
पूर्ण

अटल अंतरभूत u32 mon_cpu_to_le32(u32 val)
अणु
	वापस (__क्रमce __u32)htonl(val);
पूर्ण

अटल अंतरभूत u64 mon_cpu_to_le64(u64 val)
अणु
	वापस (__क्रमce __u64)cpu_to_be64(val);
पूर्ण

अटल अंतरभूत u16 mon_le16_to_cpu(u16 val)
अणु
	वापस ntohs((__क्रमce __be16)val);
पूर्ण

अटल अंतरभूत u32 mon_le32_to_cpu(u32 val)
अणु
	वापस ntohl((__क्रमce __be32)val);
पूर्ण

अटल अंतरभूत u64 mon_le64_to_cpu(u64 val)
अणु
	वापस be64_to_cpu((__क्रमce __be64)val);
पूर्ण

/* करोm_rec_len(): actual length of करोमुख्य record क्रम transport
 */
अटल पूर्णांक करोm_rec_len(काष्ठा tipc_mon_करोमुख्य *करोm, u16 mcnt)
अणु
	वापस (दुरत्व(काष्ठा tipc_mon_करोमुख्य, members)) + (mcnt * माप(u32));
पूर्ण

/* करोm_size() : calculate size of own करोमुख्य based on number of peers
 */
अटल पूर्णांक करोm_size(पूर्णांक peers)
अणु
	पूर्णांक i = 0;

	जबतक ((i * i) < peers)
		i++;
	वापस i < MAX_MON_DOMAIN ? i : MAX_MON_DOMAIN;
पूर्ण

अटल व्योम map_set(u64 *up_map, पूर्णांक i, अचिन्हित पूर्णांक v)
अणु
	*up_map &= ~(1ULL << i);
	*up_map |= ((u64)v << i);
पूर्ण

अटल पूर्णांक map_get(u64 up_map, पूर्णांक i)
अणु
	वापस (up_map & (1 << i)) >> i;
पूर्ण

अटल काष्ठा tipc_peer *peer_prev(काष्ठा tipc_peer *peer)
अणु
	वापस list_last_entry(&peer->list, काष्ठा tipc_peer, list);
पूर्ण

अटल काष्ठा tipc_peer *peer_nxt(काष्ठा tipc_peer *peer)
अणु
	वापस list_first_entry(&peer->list, काष्ठा tipc_peer, list);
पूर्ण

अटल काष्ठा tipc_peer *peer_head(काष्ठा tipc_peer *peer)
अणु
	जबतक (!peer->is_head)
		peer = peer_prev(peer);
	वापस peer;
पूर्ण

अटल काष्ठा tipc_peer *get_peer(काष्ठा tipc_monitor *mon, u32 addr)
अणु
	काष्ठा tipc_peer *peer;
	अचिन्हित पूर्णांक thash = tipc_hashfn(addr);

	hlist_क्रम_each_entry(peer, &mon->peers[thash], hash) अणु
		अगर (peer->addr == addr)
			वापस peer;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा tipc_peer *get_self(काष्ठा net *net, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);

	वापस mon->self;
पूर्ण

अटल अंतरभूत bool tipc_mon_is_active(काष्ठा net *net, काष्ठा tipc_monitor *mon)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);

	वापस mon->peer_cnt > tn->mon_threshold;
पूर्ण

/* mon_identअगरy_lost_members() : - identअगरy amd mark potentially lost members
 */
अटल व्योम mon_identअगरy_lost_members(काष्ठा tipc_peer *peer,
				      काष्ठा tipc_mon_करोमुख्य *करोm_bef,
				      पूर्णांक applied_bef)
अणु
	काष्ठा tipc_peer *member = peer;
	काष्ठा tipc_mon_करोमुख्य *करोm_aft = peer->करोमुख्य;
	पूर्णांक applied_aft = peer->applied;
	पूर्णांक i;

	क्रम (i = 0; i < applied_bef; i++) अणु
		member = peer_nxt(member);

		/* Do nothing अगर self or peer alपढ़ोy see member as करोwn */
		अगर (!member->is_up || !map_get(करोm_bef->up_map, i))
			जारी;

		/* Loss of local node must be detected by active probing */
		अगर (member->is_local)
			जारी;

		/* Start probing अगर member was हटाओd from applied करोमुख्य */
		अगर (!applied_aft || (applied_aft < i)) अणु
			member->करोwn_cnt = 1;
			जारी;
		पूर्ण

		/* Member loss is confirmed अगर it is still in applied करोमुख्य */
		अगर (!map_get(करोm_aft->up_map, i))
			member->करोwn_cnt++;
	पूर्ण
पूर्ण

/* mon_apply_करोमुख्य() : match a peer's करोमुख्य record against monitor list
 */
अटल व्योम mon_apply_करोमुख्य(काष्ठा tipc_monitor *mon,
			     काष्ठा tipc_peer *peer)
अणु
	काष्ठा tipc_mon_करोमुख्य *करोm = peer->करोमुख्य;
	काष्ठा tipc_peer *member;
	u32 addr;
	पूर्णांक i;

	अगर (!करोm || !peer->is_up)
		वापस;

	/* Scan across करोमुख्य members and match against monitor list */
	peer->applied = 0;
	member = peer_nxt(peer);
	क्रम (i = 0; i < करोm->member_cnt; i++) अणु
		addr = करोm->members[i];
		अगर (addr != member->addr)
			वापस;
		peer->applied++;
		member = peer_nxt(member);
	पूर्ण
पूर्ण

/* mon_update_local_करोमुख्य() : update after peer addition/removal/up/करोwn
 */
अटल व्योम mon_update_local_करोमुख्य(काष्ठा tipc_monitor *mon)
अणु
	काष्ठा tipc_peer *self = mon->self;
	काष्ठा tipc_mon_करोमुख्य *cache = &mon->cache;
	काष्ठा tipc_mon_करोमुख्य *करोm = self->करोमुख्य;
	काष्ठा tipc_peer *peer = self;
	u64 prev_up_map = करोm->up_map;
	u16 member_cnt, i;
	bool dअगरf;

	/* Update local करोमुख्य size based on current size of cluster */
	member_cnt = करोm_size(mon->peer_cnt) - 1;
	self->applied = member_cnt;

	/* Update native and cached outgoing local करोमुख्य records */
	करोm->len = करोm_rec_len(करोm, member_cnt);
	dअगरf = करोm->member_cnt != member_cnt;
	करोm->member_cnt = member_cnt;
	क्रम (i = 0; i < member_cnt; i++) अणु
		peer = peer_nxt(peer);
		dअगरf |= करोm->members[i] != peer->addr;
		करोm->members[i] = peer->addr;
		map_set(&करोm->up_map, i, peer->is_up);
		cache->members[i] = mon_cpu_to_le32(peer->addr);
	पूर्ण
	dअगरf |= करोm->up_map != prev_up_map;
	अगर (!dअगरf)
		वापस;
	करोm->gen = ++mon->करोm_gen;
	cache->len = mon_cpu_to_le16(करोm->len);
	cache->gen = mon_cpu_to_le16(करोm->gen);
	cache->member_cnt = mon_cpu_to_le16(member_cnt);
	cache->up_map = mon_cpu_to_le64(करोm->up_map);
	mon_apply_करोमुख्य(mon, self);
पूर्ण

/* mon_update_neighbors() : update preceding neighbors of added/हटाओd peer
 */
अटल व्योम mon_update_neighbors(काष्ठा tipc_monitor *mon,
				 काष्ठा tipc_peer *peer)
अणु
	पूर्णांक dz, i;

	dz = करोm_size(mon->peer_cnt);
	क्रम (i = 0; i < dz; i++) अणु
		mon_apply_करोमुख्य(mon, peer);
		peer = peer_prev(peer);
	पूर्ण
पूर्ण

/* mon_assign_roles() : reassign peer roles after a network change
 * The monitor list is consistent at this stage; i.e., each peer is monitoring
 * a set of करोमुख्य members as matched between करोमुख्य record and the monitor list
 */
अटल व्योम mon_assign_roles(काष्ठा tipc_monitor *mon, काष्ठा tipc_peer *head)
अणु
	काष्ठा tipc_peer *peer = peer_nxt(head);
	काष्ठा tipc_peer *self = mon->self;
	पूर्णांक i = 0;

	क्रम (; peer != self; peer = peer_nxt(peer)) अणु
		peer->is_local = false;

		/* Update करोमुख्य member */
		अगर (i++ < head->applied) अणु
			peer->is_head = false;
			अगर (head == self)
				peer->is_local = true;
			जारी;
		पूर्ण
		/* Assign next करोमुख्य head */
		अगर (!peer->is_up)
			जारी;
		अगर (peer->is_head)
			अवरोध;
		head = peer;
		head->is_head = true;
		i = 0;
	पूर्ण
	mon->list_gen++;
पूर्ण

व्योम tipc_mon_हटाओ_peer(काष्ठा net *net, u32 addr, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);
	काष्ठा tipc_peer *self;
	काष्ठा tipc_peer *peer, *prev, *head;

	अगर (!mon)
		वापस;

	self = get_self(net, bearer_id);
	ग_लिखो_lock_bh(&mon->lock);
	peer = get_peer(mon, addr);
	अगर (!peer)
		जाओ निकास;
	prev = peer_prev(peer);
	list_del(&peer->list);
	hlist_del(&peer->hash);
	kमुक्त(peer->करोमुख्य);
	kमुक्त(peer);
	mon->peer_cnt--;
	head = peer_head(prev);
	अगर (head == self)
		mon_update_local_करोमुख्य(mon);
	mon_update_neighbors(mon, prev);

	/* Revert to full-mesh monitoring अगर we reach threshold */
	अगर (!tipc_mon_is_active(net, mon)) अणु
		list_क्रम_each_entry(peer, &self->list, list) अणु
			kमुक्त(peer->करोमुख्य);
			peer->करोमुख्य = शून्य;
			peer->applied = 0;
		पूर्ण
	पूर्ण
	mon_assign_roles(mon, head);
निकास:
	ग_लिखो_unlock_bh(&mon->lock);
पूर्ण

अटल bool tipc_mon_add_peer(काष्ठा tipc_monitor *mon, u32 addr,
			      काष्ठा tipc_peer **peer)
अणु
	काष्ठा tipc_peer *self = mon->self;
	काष्ठा tipc_peer *cur, *prev, *p;

	p = kzalloc(माप(*p), GFP_ATOMIC);
	*peer = p;
	अगर (!p)
		वापस false;
	p->addr = addr;

	/* Add new peer to lookup list */
	INIT_LIST_HEAD(&p->list);
	hlist_add_head(&p->hash, &mon->peers[tipc_hashfn(addr)]);

	/* Sort new peer पूर्णांकo iterator list, in ascending circular order */
	prev = self;
	list_क्रम_each_entry(cur, &self->list, list) अणु
		अगर ((addr > prev->addr) && (addr < cur->addr))
			अवरोध;
		अगर (((addr < cur->addr) || (addr > prev->addr)) &&
		    (prev->addr > cur->addr))
			अवरोध;
		prev = cur;
	पूर्ण
	list_add_tail(&p->list, &cur->list);
	mon->peer_cnt++;
	mon_update_neighbors(mon, p);
	वापस true;
पूर्ण

व्योम tipc_mon_peer_up(काष्ठा net *net, u32 addr, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);
	काष्ठा tipc_peer *self = get_self(net, bearer_id);
	काष्ठा tipc_peer *peer, *head;

	ग_लिखो_lock_bh(&mon->lock);
	peer = get_peer(mon, addr);
	अगर (!peer && !tipc_mon_add_peer(mon, addr, &peer))
		जाओ निकास;
	peer->is_up = true;
	head = peer_head(peer);
	अगर (head == self)
		mon_update_local_करोमुख्य(mon);
	mon_assign_roles(mon, head);
निकास:
	ग_लिखो_unlock_bh(&mon->lock);
पूर्ण

व्योम tipc_mon_peer_करोwn(काष्ठा net *net, u32 addr, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);
	काष्ठा tipc_peer *self;
	काष्ठा tipc_peer *peer, *head;
	काष्ठा tipc_mon_करोमुख्य *करोm;
	पूर्णांक applied;

	अगर (!mon)
		वापस;

	self = get_self(net, bearer_id);
	ग_लिखो_lock_bh(&mon->lock);
	peer = get_peer(mon, addr);
	अगर (!peer) अणु
		pr_warn("Mon: unknown link %x/%u DOWN\n", addr, bearer_id);
		जाओ निकास;
	पूर्ण
	applied = peer->applied;
	peer->applied = 0;
	करोm = peer->करोमुख्य;
	peer->करोमुख्य = शून्य;
	अगर (peer->is_head)
		mon_identअगरy_lost_members(peer, करोm, applied);
	kमुक्त(करोm);
	peer->is_up = false;
	peer->is_head = false;
	peer->is_local = false;
	peer->करोwn_cnt = 0;
	head = peer_head(peer);
	अगर (head == self)
		mon_update_local_करोमुख्य(mon);
	mon_assign_roles(mon, head);
निकास:
	ग_लिखो_unlock_bh(&mon->lock);
पूर्ण

/* tipc_mon_rcv - process monitor करोमुख्य event message
 */
व्योम tipc_mon_rcv(काष्ठा net *net, व्योम *data, u16 dlen, u32 addr,
		  काष्ठा tipc_mon_state *state, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);
	काष्ठा tipc_mon_करोमुख्य *arrv_करोm = data;
	काष्ठा tipc_mon_करोमुख्य करोm_bef;
	काष्ठा tipc_mon_करोमुख्य *करोm;
	काष्ठा tipc_peer *peer;
	u16 new_member_cnt = mon_le16_to_cpu(arrv_करोm->member_cnt);
	पूर्णांक new_dlen = करोm_rec_len(arrv_करोm, new_member_cnt);
	u16 new_gen = mon_le16_to_cpu(arrv_करोm->gen);
	u16 acked_gen = mon_le16_to_cpu(arrv_करोm->ack_gen);
	u16 arrv_dlen = mon_le16_to_cpu(arrv_करोm->len);
	bool probing = state->probing;
	पूर्णांक i, applied_bef;

	state->probing = false;

	/* Sanity check received करोमुख्य record */
	अगर (dlen < करोm_rec_len(arrv_करोm, 0))
		वापस;
	अगर (dlen != करोm_rec_len(arrv_करोm, new_member_cnt))
		वापस;
	अगर (dlen < new_dlen || arrv_dlen != new_dlen)
		वापस;

	/* Synch generation numbers with peer अगर link just came up */
	अगर (!state->synched) अणु
		state->peer_gen = new_gen - 1;
		state->acked_gen = acked_gen;
		state->synched = true;
	पूर्ण

	अगर (more(acked_gen, state->acked_gen))
		state->acked_gen = acked_gen;

	/* Drop duplicate unless we are रुकोing क्रम a probe response */
	अगर (!more(new_gen, state->peer_gen) && !probing)
		वापस;

	ग_लिखो_lock_bh(&mon->lock);
	peer = get_peer(mon, addr);
	अगर (!peer || !peer->is_up)
		जाओ निकास;

	/* Peer is confirmed, stop any ongoing probing */
	peer->करोwn_cnt = 0;

	/* Task is करोne क्रम duplicate record */
	अगर (!more(new_gen, state->peer_gen))
		जाओ निकास;

	state->peer_gen = new_gen;

	/* Cache current करोमुख्य record क्रम later use */
	करोm_bef.member_cnt = 0;
	करोm = peer->करोमुख्य;
	अगर (करोm)
		स_नकल(&करोm_bef, करोm, करोm->len);

	/* Transक्रमm and store received करोमुख्य record */
	अगर (!करोm || (करोm->len < new_dlen)) अणु
		kमुक्त(करोm);
		करोm = kदो_स्मृति(new_dlen, GFP_ATOMIC);
		peer->करोमुख्य = करोm;
		अगर (!करोm)
			जाओ निकास;
	पूर्ण
	करोm->len = new_dlen;
	करोm->gen = new_gen;
	करोm->member_cnt = new_member_cnt;
	करोm->up_map = mon_le64_to_cpu(arrv_करोm->up_map);
	क्रम (i = 0; i < new_member_cnt; i++)
		करोm->members[i] = mon_le32_to_cpu(arrv_करोm->members[i]);

	/* Update peers affected by this करोमुख्य record */
	applied_bef = peer->applied;
	mon_apply_करोमुख्य(mon, peer);
	mon_identअगरy_lost_members(peer, &करोm_bef, applied_bef);
	mon_assign_roles(mon, peer_head(peer));
निकास:
	ग_लिखो_unlock_bh(&mon->lock);
पूर्ण

व्योम tipc_mon_prep(काष्ठा net *net, व्योम *data, पूर्णांक *dlen,
		   काष्ठा tipc_mon_state *state, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);
	काष्ठा tipc_mon_करोमुख्य *करोm = data;
	u16 gen = mon->करोm_gen;
	u16 len;

	/* Send invalid record अगर not active */
	अगर (!tipc_mon_is_active(net, mon)) अणु
		करोm->len = 0;
		वापस;
	पूर्ण

	/* Send only a dummy record with ack अगर peer has acked our last sent */
	अगर (likely(state->acked_gen == gen)) अणु
		len = करोm_rec_len(करोm, 0);
		*dlen = len;
		करोm->len = mon_cpu_to_le16(len);
		करोm->gen = mon_cpu_to_le16(gen);
		करोm->ack_gen = mon_cpu_to_le16(state->peer_gen);
		करोm->member_cnt = 0;
		वापस;
	पूर्ण
	/* Send the full record */
	पढ़ो_lock_bh(&mon->lock);
	len = mon_le16_to_cpu(mon->cache.len);
	*dlen = len;
	स_नकल(data, &mon->cache, len);
	पढ़ो_unlock_bh(&mon->lock);
	करोm->ack_gen = mon_cpu_to_le16(state->peer_gen);
पूर्ण

व्योम tipc_mon_get_state(काष्ठा net *net, u32 addr,
			काष्ठा tipc_mon_state *state,
			पूर्णांक bearer_id)
अणु
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);
	काष्ठा tipc_peer *peer;

	अगर (!tipc_mon_is_active(net, mon)) अणु
		state->probing = false;
		state->monitoring = true;
		वापस;
	पूर्ण

	/* Used cached state अगर table has not changed */
	अगर (!state->probing &&
	    (state->list_gen == mon->list_gen) &&
	    (state->acked_gen == mon->करोm_gen))
		वापस;

	पढ़ो_lock_bh(&mon->lock);
	peer = get_peer(mon, addr);
	अगर (peer) अणु
		state->probing = state->acked_gen != mon->करोm_gen;
		state->probing |= peer->करोwn_cnt;
		state->reset |= peer->करोwn_cnt >= MAX_PEER_DOWN_EVENTS;
		state->monitoring = peer->is_local;
		state->monitoring |= peer->is_head;
		state->list_gen = mon->list_gen;
	पूर्ण
	पढ़ो_unlock_bh(&mon->lock);
पूर्ण

अटल व्योम mon_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा tipc_monitor *mon = from_समयr(mon, t, समयr);
	काष्ठा tipc_peer *self;
	पूर्णांक best_member_cnt = करोm_size(mon->peer_cnt) - 1;

	ग_लिखो_lock_bh(&mon->lock);
	self = mon->self;
	अगर (self && (best_member_cnt != self->applied)) अणु
		mon_update_local_करोमुख्य(mon);
		mon_assign_roles(mon, self);
	पूर्ण
	ग_लिखो_unlock_bh(&mon->lock);
	mod_समयr(&mon->समयr, jअगरfies + mon->समयr_पूर्णांकv);
पूर्ण

पूर्णांक tipc_mon_create(काष्ठा net *net, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_monitor *mon;
	काष्ठा tipc_peer *self;
	काष्ठा tipc_mon_करोमुख्य *करोm;

	अगर (tn->monitors[bearer_id])
		वापस 0;

	mon = kzalloc(माप(*mon), GFP_ATOMIC);
	self = kzalloc(माप(*self), GFP_ATOMIC);
	करोm = kzalloc(माप(*करोm), GFP_ATOMIC);
	अगर (!mon || !self || !करोm) अणु
		kमुक्त(mon);
		kमुक्त(self);
		kमुक्त(करोm);
		वापस -ENOMEM;
	पूर्ण
	tn->monitors[bearer_id] = mon;
	rwlock_init(&mon->lock);
	mon->net = net;
	mon->peer_cnt = 1;
	mon->self = self;
	self->करोमुख्य = करोm;
	self->addr = tipc_own_addr(net);
	self->is_up = true;
	self->is_head = true;
	INIT_LIST_HEAD(&self->list);
	समयr_setup(&mon->समयr, mon_समयout, 0);
	mon->समयr_पूर्णांकv = msecs_to_jअगरfies(MON_TIMEOUT + (tn->अक्रमom & 0xffff));
	mod_समयr(&mon->समयr, jअगरfies + mon->समयr_पूर्णांकv);
	वापस 0;
पूर्ण

व्योम tipc_mon_delete(काष्ठा net *net, पूर्णांक bearer_id)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);
	काष्ठा tipc_peer *self;
	काष्ठा tipc_peer *peer, *पंचांगp;

	अगर (!mon)
		वापस;

	self = get_self(net, bearer_id);
	ग_लिखो_lock_bh(&mon->lock);
	tn->monitors[bearer_id] = शून्य;
	list_क्रम_each_entry_safe(peer, पंचांगp, &self->list, list) अणु
		list_del(&peer->list);
		hlist_del(&peer->hash);
		kमुक्त(peer->करोमुख्य);
		kमुक्त(peer);
	पूर्ण
	mon->self = शून्य;
	ग_लिखो_unlock_bh(&mon->lock);
	del_समयr_sync(&mon->समयr);
	kमुक्त(self->करोमुख्य);
	kमुक्त(self);
	kमुक्त(mon);
पूर्ण

व्योम tipc_mon_reinit_self(काष्ठा net *net)
अणु
	काष्ठा tipc_monitor *mon;
	पूर्णांक bearer_id;

	क्रम (bearer_id = 0; bearer_id < MAX_BEARERS; bearer_id++) अणु
		mon = tipc_monitor(net, bearer_id);
		अगर (!mon)
			जारी;
		ग_लिखो_lock_bh(&mon->lock);
		mon->self->addr = tipc_own_addr(net);
		ग_लिखो_unlock_bh(&mon->lock);
	पूर्ण
पूर्ण

पूर्णांक tipc_nl_monitor_set_threshold(काष्ठा net *net, u32 cluster_size)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);

	अगर (cluster_size > TIPC_CLUSTER_SIZE)
		वापस -EINVAL;

	tn->mon_threshold = cluster_size;

	वापस 0;
पूर्ण

पूर्णांक tipc_nl_monitor_get_threshold(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);

	वापस tn->mon_threshold;
पूर्ण

अटल पूर्णांक __tipc_nl_add_monitor_peer(काष्ठा tipc_peer *peer,
				      काष्ठा tipc_nl_msg *msg)
अणु
	काष्ठा tipc_mon_करोमुख्य *करोm = peer->करोमुख्य;
	काष्ठा nlattr *attrs;
	व्योम *hdr;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  NLM_F_MULTI, TIPC_NL_MON_PEER_GET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_MON_PEER);
	अगर (!attrs)
		जाओ msg_full;

	अगर (nla_put_u32(msg->skb, TIPC_NLA_MON_PEER_ADDR, peer->addr))
		जाओ attr_msg_full;
	अगर (nla_put_u32(msg->skb, TIPC_NLA_MON_PEER_APPLIED, peer->applied))
		जाओ attr_msg_full;

	अगर (peer->is_up)
		अगर (nla_put_flag(msg->skb, TIPC_NLA_MON_PEER_UP))
			जाओ attr_msg_full;
	अगर (peer->is_local)
		अगर (nla_put_flag(msg->skb, TIPC_NLA_MON_PEER_LOCAL))
			जाओ attr_msg_full;
	अगर (peer->is_head)
		अगर (nla_put_flag(msg->skb, TIPC_NLA_MON_PEER_HEAD))
			जाओ attr_msg_full;

	अगर (करोm) अणु
		अगर (nla_put_u32(msg->skb, TIPC_NLA_MON_PEER_DOMGEN, करोm->gen))
			जाओ attr_msg_full;
		अगर (nla_put_u64_64bit(msg->skb, TIPC_NLA_MON_PEER_UPMAP,
				      करोm->up_map, TIPC_NLA_MON_PEER_PAD))
			जाओ attr_msg_full;
		अगर (nla_put(msg->skb, TIPC_NLA_MON_PEER_MEMBERS,
			    करोm->member_cnt * माप(u32), &करोm->members))
			जाओ attr_msg_full;
	पूर्ण

	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);
	वापस 0;

attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	वापस -EMSGSIZE;
पूर्ण

पूर्णांक tipc_nl_add_monitor_peer(काष्ठा net *net, काष्ठा tipc_nl_msg *msg,
			     u32 bearer_id, u32 *prev_node)
अणु
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);
	काष्ठा tipc_peer *peer;

	अगर (!mon)
		वापस -EINVAL;

	पढ़ो_lock_bh(&mon->lock);
	peer = mon->self;
	करो अणु
		अगर (*prev_node) अणु
			अगर (peer->addr == *prev_node)
				*prev_node = 0;
			अन्यथा
				जारी;
		पूर्ण
		अगर (__tipc_nl_add_monitor_peer(peer, msg)) अणु
			*prev_node = peer->addr;
			पढ़ो_unlock_bh(&mon->lock);
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण जबतक ((peer = peer_nxt(peer)) != mon->self);
	पढ़ो_unlock_bh(&mon->lock);

	वापस 0;
पूर्ण

पूर्णांक __tipc_nl_add_monitor(काष्ठा net *net, काष्ठा tipc_nl_msg *msg,
			  u32 bearer_id)
अणु
	काष्ठा tipc_monitor *mon = tipc_monitor(net, bearer_id);
	अक्षर bearer_name[TIPC_MAX_BEARER_NAME];
	काष्ठा nlattr *attrs;
	व्योम *hdr;
	पूर्णांक ret;

	ret = tipc_bearer_get_name(net, bearer_name, bearer_id);
	अगर (ret || !mon)
		वापस 0;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  NLM_F_MULTI, TIPC_NL_MON_GET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_MON);
	अगर (!attrs)
		जाओ msg_full;

	पढ़ो_lock_bh(&mon->lock);
	अगर (nla_put_u32(msg->skb, TIPC_NLA_MON_REF, bearer_id))
		जाओ attr_msg_full;
	अगर (tipc_mon_is_active(net, mon))
		अगर (nla_put_flag(msg->skb, TIPC_NLA_MON_ACTIVE))
			जाओ attr_msg_full;
	अगर (nla_put_string(msg->skb, TIPC_NLA_MON_BEARER_NAME, bearer_name))
		जाओ attr_msg_full;
	अगर (nla_put_u32(msg->skb, TIPC_NLA_MON_PEERCNT, mon->peer_cnt))
		जाओ attr_msg_full;
	अगर (nla_put_u32(msg->skb, TIPC_NLA_MON_LISTGEN, mon->list_gen))
		जाओ attr_msg_full;

	पढ़ो_unlock_bh(&mon->lock);
	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	वापस 0;

attr_msg_full:
	पढ़ो_unlock_bh(&mon->lock);
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	वापस -EMSGSIZE;
पूर्ण
