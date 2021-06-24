<शैली गुरु>
/*
 * net/tipc/discover.c
 *
 * Copyright (c) 2003-2006, 2014-2018, Ericsson AB
 * Copyright (c) 2005-2006, 2010-2011, Wind River Systems
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

#समावेश "core.h"
#समावेश "node.h"
#समावेश "discover.h"

/* min delay during bearer start up */
#घोषणा TIPC_DISC_INIT	msecs_to_jअगरfies(125)
/* max delay अगर bearer has no links */
#घोषणा TIPC_DISC_FAST	msecs_to_jअगरfies(1000)
/* max delay अगर bearer has links */
#घोषणा TIPC_DISC_SLOW	msecs_to_jअगरfies(60000)
/* indicates no समयr in use */
#घोषणा TIPC_DISC_INACTIVE	0xffffffff

/**
 * काष्ठा tipc_discoverer - inक्रमmation about an ongoing link setup request
 * @bearer_id: identity of bearer issuing requests
 * @net: network namespace instance
 * @dest: destination address क्रम request messages
 * @करोमुख्य: network करोमुख्य to which links can be established
 * @num_nodes: number of nodes currently discovered (i.e. with an active link)
 * @lock: spinlock क्रम controlling access to requests
 * @skb: request message to be (repeatedly) sent
 * @समयr: समयr governing period between requests
 * @समयr_पूर्णांकv: current पूर्णांकerval between requests (in ms)
 */
काष्ठा tipc_discoverer अणु
	u32 bearer_id;
	काष्ठा tipc_media_addr dest;
	काष्ठा net *net;
	u32 करोमुख्य;
	पूर्णांक num_nodes;
	spinlock_t lock;
	काष्ठा sk_buff *skb;
	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ समयr_पूर्णांकv;
पूर्ण;

/**
 * tipc_disc_init_msg - initialize a link setup message
 * @net: the applicable net namespace
 * @skb: buffer containing message
 * @mtyp: message type (request or response)
 * @b: ptr to bearer issuing message
 */
अटल व्योम tipc_disc_init_msg(काष्ठा net *net, काष्ठा sk_buff *skb,
			       u32 mtyp,  काष्ठा tipc_bearer *b)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	u32 dest_करोमुख्य = b->करोमुख्य;
	काष्ठा tipc_msg *hdr;

	hdr = buf_msg(skb);
	tipc_msg_init(tn->trial_addr, hdr, LINK_CONFIG, mtyp,
		      MAX_H_SIZE, dest_करोमुख्य);
	msg_set_size(hdr, MAX_H_SIZE + NODE_ID_LEN);
	msg_set_non_seq(hdr, 1);
	msg_set_node_sig(hdr, tn->अक्रमom);
	msg_set_node_capabilities(hdr, TIPC_NODE_CAPABILITIES);
	msg_set_dest_करोमुख्य(hdr, dest_करोमुख्य);
	msg_set_bc_netid(hdr, tn->net_id);
	b->media->addr2msg(msg_media_addr(hdr), &b->addr);
	msg_set_peer_net_hash(hdr, tipc_net_hash_mixes(net, tn->अक्रमom));
	msg_set_node_id(hdr, tipc_own_id(net));
पूर्ण

अटल व्योम tipc_disc_msg_xmit(काष्ठा net *net, u32 mtyp, u32 dst,
			       u32 src, u32 sugg_addr,
			       काष्ठा tipc_media_addr *maddr,
			       काष्ठा tipc_bearer *b)
अणु
	काष्ठा tipc_msg *hdr;
	काष्ठा sk_buff *skb;

	skb = tipc_buf_acquire(MAX_H_SIZE + NODE_ID_LEN, GFP_ATOMIC);
	अगर (!skb)
		वापस;
	hdr = buf_msg(skb);
	tipc_disc_init_msg(net, skb, mtyp, b);
	msg_set_sugg_node_addr(hdr, sugg_addr);
	msg_set_dest_करोमुख्य(hdr, dst);
	tipc_bearer_xmit_skb(net, b->identity, skb, maddr);
पूर्ण

/**
 * disc_dupl_alert - issue node address duplication alert
 * @b: poपूर्णांकer to bearer detecting duplication
 * @node_addr: duplicated node address
 * @media_addr: media address advertised by duplicated node
 */
अटल व्योम disc_dupl_alert(काष्ठा tipc_bearer *b, u32 node_addr,
			    काष्ठा tipc_media_addr *media_addr)
अणु
	अक्षर media_addr_str[64];

	tipc_media_addr_म_लिखो(media_addr_str, माप(media_addr_str),
			       media_addr);
	pr_warn("Duplicate %x using %s seen on <%s>\n", node_addr,
		media_addr_str, b->name);
पूर्ण

/* tipc_disc_addr_trial(): - handle an address uniqueness trial from peer
 * Returns true अगर message should be dropped by caller, i.e., अगर it is a
 * trial message or we are inside trial period. Otherwise false.
 */
अटल bool tipc_disc_addr_trial_msg(काष्ठा tipc_discoverer *d,
				     काष्ठा tipc_media_addr *maddr,
				     काष्ठा tipc_bearer *b,
				     u32 dst, u32 src,
				     u32 sugg_addr,
				     u8 *peer_id,
				     पूर्णांक mtyp)
अणु
	काष्ठा net *net = d->net;
	काष्ठा tipc_net *tn = tipc_net(net);
	bool trial = समय_beक्रमe(jअगरfies, tn->addr_trial_end);
	u32 self = tipc_own_addr(net);

	अगर (mtyp == DSC_TRIAL_FAIL_MSG) अणु
		अगर (!trial)
			वापस true;

		/* Ignore अगर somebody अन्यथा alपढ़ोy gave new suggestion */
		अगर (dst != tn->trial_addr)
			वापस true;

		/* Otherwise update trial address and restart trial period */
		tn->trial_addr = sugg_addr;
		msg_set_prevnode(buf_msg(d->skb), sugg_addr);
		tn->addr_trial_end = jअगरfies + msecs_to_jअगरfies(1000);
		वापस true;
	पूर्ण

	/* Apply trial address अगर we just left trial period */
	अगर (!trial && !self) अणु
		schedule_work(&tn->work);
		msg_set_prevnode(buf_msg(d->skb), tn->trial_addr);
		msg_set_type(buf_msg(d->skb), DSC_REQ_MSG);
	पूर्ण

	/* Accept regular link requests/responses only after trial period */
	अगर (mtyp != DSC_TRIAL_MSG)
		वापस trial;

	sugg_addr = tipc_node_try_addr(net, peer_id, src);
	अगर (sugg_addr)
		tipc_disc_msg_xmit(net, DSC_TRIAL_FAIL_MSG, src,
				   self, sugg_addr, maddr, b);
	वापस true;
पूर्ण

/**
 * tipc_disc_rcv - handle incoming discovery message (request or response)
 * @net: applicable net namespace
 * @skb: buffer containing message
 * @b: bearer that message arrived on
 */
व्योम tipc_disc_rcv(काष्ठा net *net, काष्ठा sk_buff *skb,
		   काष्ठा tipc_bearer *b)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_msg *hdr = buf_msg(skb);
	u32 pnet_hash = msg_peer_net_hash(hdr);
	u16 caps = msg_node_capabilities(hdr);
	bool legacy = tn->legacy_addr_क्रमmat;
	u32 sugg = msg_sugg_node_addr(hdr);
	u32 signature = msg_node_sig(hdr);
	u8 peer_id[NODE_ID_LEN] = अणु0,पूर्ण;
	u32 dst = msg_dest_करोमुख्य(hdr);
	u32 net_id = msg_bc_netid(hdr);
	काष्ठा tipc_media_addr maddr;
	u32 src = msg_prevnode(hdr);
	u32 mtyp = msg_type(hdr);
	bool dupl_addr = false;
	bool respond = false;
	u32 self;
	पूर्णांक err;

	skb_linearize(skb);
	hdr = buf_msg(skb);

	अगर (caps & TIPC_NODE_ID128)
		स_नकल(peer_id, msg_node_id(hdr), NODE_ID_LEN);
	अन्यथा
		प्र_लिखो(peer_id, "%x", src);

	err = b->media->msg2addr(b, &maddr, msg_media_addr(hdr));
	kमुक्त_skb(skb);
	अगर (err || maddr.broadcast) अणु
		pr_warn_ratelimited("Rcv corrupt discovery message\n");
		वापस;
	पूर्ण
	/* Ignore discovery messages from own node */
	अगर (!स_भेद(&maddr, &b->addr, माप(maddr)))
		वापस;
	अगर (net_id != tn->net_id)
		वापस;
	अगर (tipc_disc_addr_trial_msg(b->disc, &maddr, b, dst,
				     src, sugg, peer_id, mtyp))
		वापस;
	self = tipc_own_addr(net);

	/* Message from somebody using this node's address */
	अगर (in_own_node(net, src)) अणु
		disc_dupl_alert(b, self, &maddr);
		वापस;
	पूर्ण
	अगर (!tipc_in_scope(legacy, dst, self))
		वापस;
	अगर (!tipc_in_scope(legacy, b->करोमुख्य, src))
		वापस;
	tipc_node_check_dest(net, src, peer_id, b, caps, signature, pnet_hash,
			     &maddr, &respond, &dupl_addr);
	अगर (dupl_addr)
		disc_dupl_alert(b, src, &maddr);
	अगर (!respond)
		वापस;
	अगर (mtyp != DSC_REQ_MSG)
		वापस;
	tipc_disc_msg_xmit(net, DSC_RESP_MSG, src, self, 0, &maddr, b);
पूर्ण

/* tipc_disc_add_dest - increment set of discovered nodes
 */
व्योम tipc_disc_add_dest(काष्ठा tipc_discoverer *d)
अणु
	spin_lock_bh(&d->lock);
	d->num_nodes++;
	spin_unlock_bh(&d->lock);
पूर्ण

/* tipc_disc_हटाओ_dest - decrement set of discovered nodes
 */
व्योम tipc_disc_हटाओ_dest(काष्ठा tipc_discoverer *d)
अणु
	पूर्णांक पूर्णांकv, num;

	spin_lock_bh(&d->lock);
	d->num_nodes--;
	num = d->num_nodes;
	पूर्णांकv = d->समयr_पूर्णांकv;
	अगर (!num && (पूर्णांकv == TIPC_DISC_INACTIVE || पूर्णांकv > TIPC_DISC_FAST))  अणु
		d->समयr_पूर्णांकv = TIPC_DISC_INIT;
		mod_समयr(&d->समयr, jअगरfies + d->समयr_पूर्णांकv);
	पूर्ण
	spin_unlock_bh(&d->lock);
पूर्ण

/* tipc_disc_समयout - send a periodic link setup request
 * Called whenever a link setup request समयr associated with a bearer expires.
 * - Keep करोubling समय between sent request until limit is reached;
 * - Hold at fast polling rate अगर we करोn't have any associated nodes
 * - Otherwise hold at slow polling rate
 */
अटल व्योम tipc_disc_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा tipc_discoverer *d = from_समयr(d, t, समयr);
	काष्ठा tipc_net *tn = tipc_net(d->net);
	काष्ठा tipc_media_addr maddr;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा net *net = d->net;
	u32 bearer_id;

	spin_lock_bh(&d->lock);

	/* Stop searching अगर only desired node has been found */
	अगर (tipc_node(d->करोमुख्य) && d->num_nodes) अणु
		d->समयr_पूर्णांकv = TIPC_DISC_INACTIVE;
		जाओ निकास;
	पूर्ण

	/* Did we just leave trial period ? */
	अगर (!समय_beक्रमe(jअगरfies, tn->addr_trial_end) && !tipc_own_addr(net)) अणु
		mod_समयr(&d->समयr, jअगरfies + TIPC_DISC_INIT);
		spin_unlock_bh(&d->lock);
		schedule_work(&tn->work);
		वापस;
	पूर्ण

	/* Adjust समयout पूर्णांकerval according to discovery phase */
	अगर (समय_beक्रमe(jअगरfies, tn->addr_trial_end)) अणु
		d->समयr_पूर्णांकv = TIPC_DISC_INIT;
	पूर्ण अन्यथा अणु
		d->समयr_पूर्णांकv *= 2;
		अगर (d->num_nodes && d->समयr_पूर्णांकv > TIPC_DISC_SLOW)
			d->समयr_पूर्णांकv = TIPC_DISC_SLOW;
		अन्यथा अगर (!d->num_nodes && d->समयr_पूर्णांकv > TIPC_DISC_FAST)
			d->समयr_पूर्णांकv = TIPC_DISC_FAST;
		msg_set_type(buf_msg(d->skb), DSC_REQ_MSG);
		msg_set_prevnode(buf_msg(d->skb), tn->trial_addr);
	पूर्ण

	mod_समयr(&d->समयr, jअगरfies + d->समयr_पूर्णांकv);
	स_नकल(&maddr, &d->dest, माप(maddr));
	skb = skb_clone(d->skb, GFP_ATOMIC);
	bearer_id = d->bearer_id;
निकास:
	spin_unlock_bh(&d->lock);
	अगर (skb)
		tipc_bearer_xmit_skb(net, bearer_id, skb, &maddr);
पूर्ण

/**
 * tipc_disc_create - create object to send periodic link setup requests
 * @net: the applicable net namespace
 * @b: ptr to bearer issuing requests
 * @dest: destination address क्रम request messages
 * @skb: poपूर्णांकer to created frame
 *
 * Return: 0 अगर successful, otherwise -त्रुटि_सं.
 */
पूर्णांक tipc_disc_create(काष्ठा net *net, काष्ठा tipc_bearer *b,
		     काष्ठा tipc_media_addr *dest, काष्ठा sk_buff **skb)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	काष्ठा tipc_discoverer *d;

	d = kदो_स्मृति(माप(*d), GFP_ATOMIC);
	अगर (!d)
		वापस -ENOMEM;
	d->skb = tipc_buf_acquire(MAX_H_SIZE + NODE_ID_LEN, GFP_ATOMIC);
	अगर (!d->skb) अणु
		kमुक्त(d);
		वापस -ENOMEM;
	पूर्ण
	tipc_disc_init_msg(net, d->skb, DSC_REQ_MSG, b);

	/* Do we need an address trial period first ? */
	अगर (!tipc_own_addr(net)) अणु
		tn->addr_trial_end = jअगरfies + msecs_to_jअगरfies(1000);
		msg_set_type(buf_msg(d->skb), DSC_TRIAL_MSG);
	पूर्ण
	स_नकल(&d->dest, dest, माप(*dest));
	d->net = net;
	d->bearer_id = b->identity;
	d->करोमुख्य = b->करोमुख्य;
	d->num_nodes = 0;
	d->समयr_पूर्णांकv = TIPC_DISC_INIT;
	spin_lock_init(&d->lock);
	समयr_setup(&d->समयr, tipc_disc_समयout, 0);
	mod_समयr(&d->समयr, jअगरfies + d->समयr_पूर्णांकv);
	b->disc = d;
	*skb = skb_clone(d->skb, GFP_ATOMIC);
	वापस 0;
पूर्ण

/**
 * tipc_disc_delete - destroy object sending periodic link setup requests
 * @d: ptr to link dest काष्ठाure
 */
व्योम tipc_disc_delete(काष्ठा tipc_discoverer *d)
अणु
	del_समयr_sync(&d->समयr);
	kमुक्त_skb(d->skb);
	kमुक्त(d);
पूर्ण

/**
 * tipc_disc_reset - reset object to send periodic link setup requests
 * @net: the applicable net namespace
 * @b: ptr to bearer issuing requests
 */
व्योम tipc_disc_reset(काष्ठा net *net, काष्ठा tipc_bearer *b)
अणु
	काष्ठा tipc_discoverer *d = b->disc;
	काष्ठा tipc_media_addr maddr;
	काष्ठा sk_buff *skb;

	spin_lock_bh(&d->lock);
	tipc_disc_init_msg(net, d->skb, DSC_REQ_MSG, b);
	d->net = net;
	d->bearer_id = b->identity;
	d->करोमुख्य = b->करोमुख्य;
	d->num_nodes = 0;
	d->समयr_पूर्णांकv = TIPC_DISC_INIT;
	स_नकल(&maddr, &d->dest, माप(maddr));
	mod_समयr(&d->समयr, jअगरfies + d->समयr_पूर्णांकv);
	skb = skb_clone(d->skb, GFP_ATOMIC);
	spin_unlock_bh(&d->lock);
	अगर (skb)
		tipc_bearer_xmit_skb(net, b->identity, skb, &maddr);
पूर्ण
