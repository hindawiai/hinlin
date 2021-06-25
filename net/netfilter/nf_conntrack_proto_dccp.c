<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DCCP connection tracking protocol helper
 *
 * Copyright (c) 2005, 2006, 2008 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/dccp.h>
#समावेश <linux/slab.h>

#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/netfilter/nfnetlink_conntrack.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <net/netfilter/nf_log.h>

/* Timeouts are based on values from RFC4340:
 *
 * - REQUEST:
 *
 *   8.1.2. Client Request
 *
 *   A client MAY give up on its DCCP-Requests after some समय
 *   (3 minutes, क्रम example).
 *
 * - RESPOND:
 *
 *   8.1.3. Server Response
 *
 *   It MAY also leave the RESPOND state क्रम CLOSED after a समयout of
 *   not less than 4MSL (8 minutes);
 *
 * - PARTOPEN:
 *
 *   8.1.5. Handshake Completion
 *
 *   If the client reमुख्यs in PARTOPEN क्रम more than 4MSL (8 minutes),
 *   it SHOULD reset the connection with Reset Code 2, "Aborted".
 *
 * - OPEN:
 *
 *   The DCCP बारtamp overflows after 11.9 hours. If the connection
 *   stays idle this दीर्घ the sequence number won't be recognized
 *   as valid anymore.
 *
 * - CLOSEREQ/CLOSING:
 *
 *   8.3. Termination
 *
 *   The retransmission समयr should initially be set to go off in two
 *   round-trip बार and should back off to not less than once every
 *   64 seconds ...
 *
 * - TIMEWAIT:
 *
 *   4.3. States
 *
 *   A server or client socket reमुख्यs in this state क्रम 2MSL (4 minutes)
 *   after the connection has been town करोwn, ...
 */

#घोषणा DCCP_MSL (2 * 60 * HZ)

अटल स्थिर अक्षर * स्थिर dccp_state_names[] = अणु
	[CT_DCCP_NONE]		= "NONE",
	[CT_DCCP_REQUEST]	= "REQUEST",
	[CT_DCCP_RESPOND]	= "RESPOND",
	[CT_DCCP_PARTOPEN]	= "PARTOPEN",
	[CT_DCCP_OPEN]		= "OPEN",
	[CT_DCCP_CLOSEREQ]	= "CLOSEREQ",
	[CT_DCCP_CLOSING]	= "CLOSING",
	[CT_DCCP_TIMEWAIT]	= "TIMEWAIT",
	[CT_DCCP_IGNORE]	= "IGNORE",
	[CT_DCCP_INVALID]	= "INVALID",
पूर्ण;

#घोषणा sNO	CT_DCCP_NONE
#घोषणा sRQ	CT_DCCP_REQUEST
#घोषणा sRS	CT_DCCP_RESPOND
#घोषणा sPO	CT_DCCP_PARTOPEN
#घोषणा sOP	CT_DCCP_OPEN
#घोषणा sCR	CT_DCCP_CLOSEREQ
#घोषणा sCG	CT_DCCP_CLOSING
#घोषणा sTW	CT_DCCP_TIMEWAIT
#घोषणा sIG	CT_DCCP_IGNORE
#घोषणा sIV	CT_DCCP_INVALID

/*
 * DCCP state transition table
 *
 * The assumption is the same as क्रम TCP tracking:
 *
 * We are the man in the middle. All the packets go through us but might
 * get lost in transit to the destination. It is assumed that the destination
 * can't receive segments we haven't seen.
 *
 * The following states exist:
 *
 * NONE:	Initial state, expecting Request
 * REQUEST:	Request seen, रुकोing क्रम Response from server
 * RESPOND:	Response from server seen, रुकोing क्रम Ack from client
 * PARTOPEN:	Ack after Response seen, रुकोing क्रम packet other than Response,
 * 		Reset or Sync from server
 * OPEN:	Packet other than Response, Reset or Sync seen
 * CLOSEREQ:	CloseReq from server seen, expecting Close from client
 * CLOSING:	Close seen, expecting Reset
 * TIMEWAIT:	Reset seen
 * IGNORE:	Not determinable whether packet is valid
 *
 * Some states exist only on one side of the connection: REQUEST, RESPOND,
 * PARTOPEN, CLOSEREQ. For the other side these states are equivalent to
 * the one it was in beक्रमe.
 *
 * Packets are marked as ignored (sIG) अगर we करोn't know if they're valid
 * (क्रम example a reincarnation of a connection we didn't notice is dead
 * alपढ़ोy) and the server may send back a connection closing Reset or a
 * Response. They're also used for Sync/SyncAck packets, which we don't
 * care about.
 */
अटल स्थिर u_पूर्णांक8_t
dccp_state_table[CT_DCCP_ROLE_MAX + 1][DCCP_PKT_SYNCACK + 1][CT_DCCP_MAX + 1] = अणु
	[CT_DCCP_ROLE_CLIENT] = अणु
		[DCCP_PKT_REQUEST] = अणु
		/*
		 * sNO -> sRQ		Regular Request
		 * sRQ -> sRQ		Retransmitted Request or reincarnation
		 * sRS -> sRS		Retransmitted Request (apparently Response
		 * 			got lost after we saw it) or reincarnation
		 * sPO -> sIG		Ignore, conntrack might be out of sync
		 * sOP -> sIG		Ignore, conntrack might be out of sync
		 * sCR -> sIG		Ignore, conntrack might be out of sync
		 * sCG -> sIG		Ignore, conntrack might be out of sync
		 * sTW -> sRQ		Reincarnation
		 *
		 *	sNO, sRQ, sRS, sPO. sOP, sCR, sCG, sTW, */
			sRQ, sRQ, sRS, sIG, sIG, sIG, sIG, sRQ,
		पूर्ण,
		[DCCP_PKT_RESPONSE] = अणु
		/*
		 * sNO -> sIV		Invalid
		 * sRQ -> sIG		Ignore, might be response to ignored Request
		 * sRS -> sIG		Ignore, might be response to ignored Request
		 * sPO -> sIG		Ignore, might be response to ignored Request
		 * sOP -> sIG		Ignore, might be response to ignored Request
		 * sCR -> sIG		Ignore, might be response to ignored Request
		 * sCG -> sIG		Ignore, might be response to ignored Request
		 * sTW -> sIV		Invalid, reincarnation in reverse direction
		 *			goes through sRQ
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIV,
		पूर्ण,
		[DCCP_PKT_ACK] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sIV		No connection
		 * sRS -> sPO		Ack क्रम Response, move to PARTOPEN (8.1.5.)
		 * sPO -> sPO		Retransmitted Ack क्रम Response, reमुख्य in PARTOPEN
		 * sOP -> sOP		Regular ACK, reमुख्य in OPEN
		 * sCR -> sCR		Ack in CLOSEREQ MAY be processed (8.3.)
		 * sCG -> sCG		Ack in CLOSING MAY be processed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sPO, sPO, sOP, sCR, sCG, sIV
		पूर्ण,
		[DCCP_PKT_DATA] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sIV		No connection
		 * sRS -> sIV		No connection
		 * sPO -> sIV		MUST use DataAck in PARTOPEN state (8.1.5.)
		 * sOP -> sOP		Regular Data packet
		 * sCR -> sCR		Data in CLOSEREQ MAY be processed (8.3.)
		 * sCG -> sCG		Data in CLOSING MAY be processed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sIV, sIV, sOP, sCR, sCG, sIV,
		पूर्ण,
		[DCCP_PKT_DATAACK] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sIV		No connection
		 * sRS -> sPO		Ack क्रम Response, move to PARTOPEN (8.1.5.)
		 * sPO -> sPO		Reमुख्य in PARTOPEN state
		 * sOP -> sOP		Regular DataAck packet in OPEN state
		 * sCR -> sCR		DataAck in CLOSEREQ MAY be processed (8.3.)
		 * sCG -> sCG		DataAck in CLOSING MAY be processed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sPO, sPO, sOP, sCR, sCG, sIV
		पूर्ण,
		[DCCP_PKT_CLOSEREQ] = अणु
		/*
		 * CLOSEREQ may only be sent by the server.
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sIV, sIV, sIV, sIV, sIV, sIV
		पूर्ण,
		[DCCP_PKT_CLOSE] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sIV		No connection
		 * sRS -> sIV		No connection
		 * sPO -> sCG		Client-initiated बंद
		 * sOP -> sCG		Client-initiated बंद
		 * sCR -> sCG		Close in response to CloseReq (8.3.)
		 * sCG -> sCG		Retransmit
		 * sTW -> sIV		Late retransmit, alपढ़ोy in TIME_WAIT
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sIV, sCG, sCG, sCG, sIV, sIV
		पूर्ण,
		[DCCP_PKT_RESET] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sTW		Sync received or समयout, SHOULD send Reset (8.1.1.)
		 * sRS -> sTW		Response received without Request
		 * sPO -> sTW		Timeout, SHOULD send Reset (8.1.5.)
		 * sOP -> sTW		Connection reset
		 * sCR -> sTW		Connection reset
		 * sCG -> sTW		Connection reset
		 * sTW -> sIG		Ignore (करोn't refresh समयr)
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sTW, sTW, sTW, sTW, sTW, sTW, sIG
		पूर्ण,
		[DCCP_PKT_SYNC] = अणु
		/*
		 * We currently ignore Sync packets
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIG,
		पूर्ण,
		[DCCP_PKT_SYNCACK] = अणु
		/*
		 * We currently ignore SyncAck packets
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIG,
		पूर्ण,
	पूर्ण,
	[CT_DCCP_ROLE_SERVER] = अणु
		[DCCP_PKT_REQUEST] = अणु
		/*
		 * sNO -> sIV		Invalid
		 * sRQ -> sIG		Ignore, conntrack might be out of sync
		 * sRS -> sIG		Ignore, conntrack might be out of sync
		 * sPO -> sIG		Ignore, conntrack might be out of sync
		 * sOP -> sIG		Ignore, conntrack might be out of sync
		 * sCR -> sIG		Ignore, conntrack might be out of sync
		 * sCG -> sIG		Ignore, conntrack might be out of sync
		 * sTW -> sRQ		Reincarnation, must reverse roles
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sRQ
		पूर्ण,
		[DCCP_PKT_RESPONSE] = अणु
		/*
		 * sNO -> sIV		Response without Request
		 * sRQ -> sRS		Response to clients Request
		 * sRS -> sRS		Retransmitted Response (8.1.3. SHOULD NOT)
		 * sPO -> sIG		Response to an ignored Request or late retransmit
		 * sOP -> sIG		Ignore, might be response to ignored Request
		 * sCR -> sIG		Ignore, might be response to ignored Request
		 * sCG -> sIG		Ignore, might be response to ignored Request
		 * sTW -> sIV		Invalid, Request from client in sTW moves to sRQ
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sRS, sRS, sIG, sIG, sIG, sIG, sIV
		पूर्ण,
		[DCCP_PKT_ACK] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sIV		No connection
		 * sRS -> sIV		No connection
		 * sPO -> sOP		Enter OPEN state (8.1.5.)
		 * sOP -> sOP		Regular Ack in OPEN state
		 * sCR -> sIV		Waiting क्रम Close from client
		 * sCG -> sCG		Ack in CLOSING MAY be processed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sIV, sOP, sOP, sIV, sCG, sIV
		पूर्ण,
		[DCCP_PKT_DATA] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sIV		No connection
		 * sRS -> sIV		No connection
		 * sPO -> sOP		Enter OPEN state (8.1.5.)
		 * sOP -> sOP		Regular Data packet in OPEN state
		 * sCR -> sIV		Waiting क्रम Close from client
		 * sCG -> sCG		Data in CLOSING MAY be processed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sIV, sOP, sOP, sIV, sCG, sIV
		पूर्ण,
		[DCCP_PKT_DATAACK] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sIV		No connection
		 * sRS -> sIV		No connection
		 * sPO -> sOP		Enter OPEN state (8.1.5.)
		 * sOP -> sOP		Regular DataAck in OPEN state
		 * sCR -> sIV		Waiting क्रम Close from client
		 * sCG -> sCG		Data in CLOSING MAY be processed (8.3.)
		 * sTW -> sIV
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sIV, sOP, sOP, sIV, sCG, sIV
		पूर्ण,
		[DCCP_PKT_CLOSEREQ] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sIV		No connection
		 * sRS -> sIV		No connection
		 * sPO -> sOP -> sCR	Move directly to CLOSEREQ (8.1.5.)
		 * sOP -> sCR		CloseReq in OPEN state
		 * sCR -> sCR		Retransmit
		 * sCG -> sCR		Simultaneous बंद, client sends another Close
		 * sTW -> sIV		Alपढ़ोy बंदd
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sIV, sCR, sCR, sCR, sCR, sIV
		पूर्ण,
		[DCCP_PKT_CLOSE] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sIV		No connection
		 * sRS -> sIV		No connection
		 * sPO -> sOP -> sCG	Move direcly to CLOSING
		 * sOP -> sCG		Move to CLOSING
		 * sCR -> sIV		Close after CloseReq is invalid
		 * sCG -> sCG		Retransmit
		 * sTW -> sIV		Alपढ़ोy बंदd
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIV, sIV, sCG, sCG, sIV, sCG, sIV
		पूर्ण,
		[DCCP_PKT_RESET] = अणु
		/*
		 * sNO -> sIV		No connection
		 * sRQ -> sTW		Reset in response to Request
		 * sRS -> sTW		Timeout, SHOULD send Reset (8.1.3.)
		 * sPO -> sTW		Timeout, SHOULD send Reset (8.1.3.)
		 * sOP -> sTW
		 * sCR -> sTW
		 * sCG -> sTW
		 * sTW -> sIG		Ignore (करोn't refresh समयr)
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW, sTW */
			sIV, sTW, sTW, sTW, sTW, sTW, sTW, sTW, sIG
		पूर्ण,
		[DCCP_PKT_SYNC] = अणु
		/*
		 * We currently ignore Sync packets
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIG,
		पूर्ण,
		[DCCP_PKT_SYNCACK] = अणु
		/*
		 * We currently ignore SyncAck packets
		 *
		 *	sNO, sRQ, sRS, sPO, sOP, sCR, sCG, sTW */
			sIV, sIG, sIG, sIG, sIG, sIG, sIG, sIG,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल noअंतरभूत bool
dccp_new(काष्ठा nf_conn *ct, स्थिर काष्ठा sk_buff *skb,
	 स्थिर काष्ठा dccp_hdr *dh)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_dccp_net *dn;
	स्थिर अक्षर *msg;
	u_पूर्णांक8_t state;

	state = dccp_state_table[CT_DCCP_ROLE_CLIENT][dh->dccph_type][CT_DCCP_NONE];
	चयन (state) अणु
	शेष:
		dn = nf_dccp_pernet(net);
		अगर (dn->dccp_loose == 0) अणु
			msg = "not picking up existing connection ";
			जाओ out_invalid;
		पूर्ण
		अवरोध;
	हाल CT_DCCP_REQUEST:
		अवरोध;
	हाल CT_DCCP_INVALID:
		msg = "invalid state transition ";
		जाओ out_invalid;
	पूर्ण

	ct->proto.dccp.role[IP_CT_सूची_ORIGINAL] = CT_DCCP_ROLE_CLIENT;
	ct->proto.dccp.role[IP_CT_सूची_REPLY] = CT_DCCP_ROLE_SERVER;
	ct->proto.dccp.state = CT_DCCP_NONE;
	ct->proto.dccp.last_pkt = DCCP_PKT_REQUEST;
	ct->proto.dccp.last_dir = IP_CT_सूची_ORIGINAL;
	ct->proto.dccp.handshake_seq = 0;
	वापस true;

out_invalid:
	nf_ct_l4proto_log_invalid(skb, ct, "%s", msg);
	वापस false;
पूर्ण

अटल u64 dccp_ack_seq(स्थिर काष्ठा dccp_hdr *dh)
अणु
	स्थिर काष्ठा dccp_hdr_ack_bits *dhack;

	dhack = (व्योम *)dh + __dccp_basic_hdr_len(dh);
	वापस ((u64)ntohs(dhack->dccph_ack_nr_high) << 32) +
		     ntohl(dhack->dccph_ack_nr_low);
पूर्ण

अटल bool dccp_error(स्थिर काष्ठा dccp_hdr *dh,
		       काष्ठा sk_buff *skb, अचिन्हित पूर्णांक dataoff,
		       स्थिर काष्ठा nf_hook_state *state)
अणु
	अचिन्हित पूर्णांक dccp_len = skb->len - dataoff;
	अचिन्हित पूर्णांक cscov;
	स्थिर अक्षर *msg;

	अगर (dh->dccph_करोff * 4 < माप(काष्ठा dccp_hdr) ||
	    dh->dccph_करोff * 4 > dccp_len) अणु
		msg = "nf_ct_dccp: truncated/malformed packet ";
		जाओ out_invalid;
	पूर्ण

	cscov = dccp_len;
	अगर (dh->dccph_cscov) अणु
		cscov = (dh->dccph_cscov - 1) * 4;
		अगर (cscov > dccp_len) अणु
			msg = "nf_ct_dccp: bad checksum coverage ";
			जाओ out_invalid;
		पूर्ण
	पूर्ण

	अगर (state->hook == NF_INET_PRE_ROUTING &&
	    state->net->ct.sysctl_checksum &&
	    nf_checksum_partial(skb, state->hook, dataoff, cscov,
				IPPROTO_DCCP, state->pf)) अणु
		msg = "nf_ct_dccp: bad checksum ";
		जाओ out_invalid;
	पूर्ण

	अगर (dh->dccph_type >= DCCP_PKT_INVALID) अणु
		msg = "nf_ct_dccp: reserved packet type ";
		जाओ out_invalid;
	पूर्ण
	वापस false;
out_invalid:
	nf_l4proto_log_invalid(skb, state->net, state->pf,
			       IPPROTO_DCCP, "%s", msg);
	वापस true;
पूर्ण

पूर्णांक nf_conntrack_dccp_packet(काष्ठा nf_conn *ct, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक dataoff,
			     क्रमागत ip_conntrack_info ctinfo,
			     स्थिर काष्ठा nf_hook_state *state)
अणु
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	काष्ठा dccp_hdr _dh, *dh;
	u_पूर्णांक8_t type, old_state, new_state;
	क्रमागत ct_dccp_roles role;
	अचिन्हित पूर्णांक *समयouts;

	dh = skb_header_poपूर्णांकer(skb, dataoff, माप(_dh), &_dh);
	अगर (!dh)
		वापस NF_DROP;

	अगर (dccp_error(dh, skb, dataoff, state))
		वापस -NF_ACCEPT;

	type = dh->dccph_type;
	अगर (!nf_ct_is_confirmed(ct) && !dccp_new(ct, skb, dh))
		वापस -NF_ACCEPT;

	अगर (type == DCCP_PKT_RESET &&
	    !test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) अणु
		/* Tear करोwn connection immediately अगर only reply is a RESET */
		nf_ct_समाप्त_acct(ct, ctinfo, skb);
		वापस NF_ACCEPT;
	पूर्ण

	spin_lock_bh(&ct->lock);

	role = ct->proto.dccp.role[dir];
	old_state = ct->proto.dccp.state;
	new_state = dccp_state_table[role][type][old_state];

	चयन (new_state) अणु
	हाल CT_DCCP_REQUEST:
		अगर (old_state == CT_DCCP_TIMEWAIT &&
		    role == CT_DCCP_ROLE_SERVER) अणु
			/* Reincarnation in the reverse direction: reखोलो and
			 * reverse client/server roles. */
			ct->proto.dccp.role[dir] = CT_DCCP_ROLE_CLIENT;
			ct->proto.dccp.role[!dir] = CT_DCCP_ROLE_SERVER;
		पूर्ण
		अवरोध;
	हाल CT_DCCP_RESPOND:
		अगर (old_state == CT_DCCP_REQUEST)
			ct->proto.dccp.handshake_seq = dccp_hdr_seq(dh);
		अवरोध;
	हाल CT_DCCP_PARTOPEN:
		अगर (old_state == CT_DCCP_RESPOND &&
		    type == DCCP_PKT_ACK &&
		    dccp_ack_seq(dh) == ct->proto.dccp.handshake_seq)
			set_bit(IPS_ASSURED_BIT, &ct->status);
		अवरोध;
	हाल CT_DCCP_IGNORE:
		/*
		 * Connection tracking might be out of sync, so we ignore
		 * packets that might establish a new connection and resync
		 * अगर the server responds with a valid Response.
		 */
		अगर (ct->proto.dccp.last_dir == !dir &&
		    ct->proto.dccp.last_pkt == DCCP_PKT_REQUEST &&
		    type == DCCP_PKT_RESPONSE) अणु
			ct->proto.dccp.role[!dir] = CT_DCCP_ROLE_CLIENT;
			ct->proto.dccp.role[dir] = CT_DCCP_ROLE_SERVER;
			ct->proto.dccp.handshake_seq = dccp_hdr_seq(dh);
			new_state = CT_DCCP_RESPOND;
			अवरोध;
		पूर्ण
		ct->proto.dccp.last_dir = dir;
		ct->proto.dccp.last_pkt = type;

		spin_unlock_bh(&ct->lock);
		nf_ct_l4proto_log_invalid(skb, ct, "%s", "invalid packet");
		वापस NF_ACCEPT;
	हाल CT_DCCP_INVALID:
		spin_unlock_bh(&ct->lock);
		nf_ct_l4proto_log_invalid(skb, ct, "%s", "invalid state transition");
		वापस -NF_ACCEPT;
	पूर्ण

	ct->proto.dccp.last_dir = dir;
	ct->proto.dccp.last_pkt = type;
	ct->proto.dccp.state = new_state;
	spin_unlock_bh(&ct->lock);

	अगर (new_state != old_state)
		nf_conntrack_event_cache(IPCT_PROTOINFO, ct);

	समयouts = nf_ct_समयout_lookup(ct);
	अगर (!समयouts)
		समयouts = nf_dccp_pernet(nf_ct_net(ct))->dccp_समयout;
	nf_ct_refresh_acct(ct, ctinfo, skb, समयouts[new_state]);

	वापस NF_ACCEPT;
पूर्ण

अटल bool dccp_can_early_drop(स्थिर काष्ठा nf_conn *ct)
अणु
	चयन (ct->proto.dccp.state) अणु
	हाल CT_DCCP_CLOSEREQ:
	हाल CT_DCCP_CLOSING:
	हाल CT_DCCP_TIMEWAIT:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
अटल व्योम dccp_prपूर्णांक_conntrack(काष्ठा seq_file *s, काष्ठा nf_conn *ct)
अणु
	seq_म_लिखो(s, "%s ", dccp_state_names[ct->proto.dccp.state]);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)
अटल पूर्णांक dccp_to_nlattr(काष्ठा sk_buff *skb, काष्ठा nlattr *nla,
			  काष्ठा nf_conn *ct, bool destroy)
अणु
	काष्ठा nlattr *nest_parms;

	spin_lock_bh(&ct->lock);
	nest_parms = nla_nest_start(skb, CTA_PROTOINFO_DCCP);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, CTA_PROTOINFO_DCCP_STATE, ct->proto.dccp.state))
		जाओ nla_put_failure;

	अगर (destroy)
		जाओ skip_state;

	अगर (nla_put_u8(skb, CTA_PROTOINFO_DCCP_ROLE,
		       ct->proto.dccp.role[IP_CT_सूची_ORIGINAL]) ||
	    nla_put_be64(skb, CTA_PROTOINFO_DCCP_HANDSHAKE_SEQ,
			 cpu_to_be64(ct->proto.dccp.handshake_seq),
			 CTA_PROTOINFO_DCCP_PAD))
		जाओ nla_put_failure;
skip_state:
	nla_nest_end(skb, nest_parms);
	spin_unlock_bh(&ct->lock);

	वापस 0;

nla_put_failure:
	spin_unlock_bh(&ct->lock);
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nla_policy dccp_nla_policy[CTA_PROTOINFO_DCCP_MAX + 1] = अणु
	[CTA_PROTOINFO_DCCP_STATE]	= अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTOINFO_DCCP_ROLE]	= अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTOINFO_DCCP_HANDSHAKE_SEQ] = अणु .type = NLA_U64 पूर्ण,
	[CTA_PROTOINFO_DCCP_PAD]	= अणु .type = NLA_UNSPEC पूर्ण,
पूर्ण;

#घोषणा DCCP_NLATTR_SIZE ( \
	NLA_ALIGN(NLA_HDRLEN + 1) + \
	NLA_ALIGN(NLA_HDRLEN + 1) + \
	NLA_ALIGN(NLA_HDRLEN + माप(u64)) + \
	NLA_ALIGN(NLA_HDRLEN + 0))

अटल पूर्णांक nlattr_to_dccp(काष्ठा nlattr *cda[], काष्ठा nf_conn *ct)
अणु
	काष्ठा nlattr *attr = cda[CTA_PROTOINFO_DCCP];
	काष्ठा nlattr *tb[CTA_PROTOINFO_DCCP_MAX + 1];
	पूर्णांक err;

	अगर (!attr)
		वापस 0;

	err = nla_parse_nested_deprecated(tb, CTA_PROTOINFO_DCCP_MAX, attr,
					  dccp_nla_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[CTA_PROTOINFO_DCCP_STATE] ||
	    !tb[CTA_PROTOINFO_DCCP_ROLE] ||
	    nla_get_u8(tb[CTA_PROTOINFO_DCCP_ROLE]) > CT_DCCP_ROLE_MAX ||
	    nla_get_u8(tb[CTA_PROTOINFO_DCCP_STATE]) >= CT_DCCP_IGNORE) अणु
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&ct->lock);
	ct->proto.dccp.state = nla_get_u8(tb[CTA_PROTOINFO_DCCP_STATE]);
	अगर (nla_get_u8(tb[CTA_PROTOINFO_DCCP_ROLE]) == CT_DCCP_ROLE_CLIENT) अणु
		ct->proto.dccp.role[IP_CT_सूची_ORIGINAL] = CT_DCCP_ROLE_CLIENT;
		ct->proto.dccp.role[IP_CT_सूची_REPLY] = CT_DCCP_ROLE_SERVER;
	पूर्ण अन्यथा अणु
		ct->proto.dccp.role[IP_CT_सूची_ORIGINAL] = CT_DCCP_ROLE_SERVER;
		ct->proto.dccp.role[IP_CT_सूची_REPLY] = CT_DCCP_ROLE_CLIENT;
	पूर्ण
	अगर (tb[CTA_PROTOINFO_DCCP_HANDSHAKE_SEQ]) अणु
		ct->proto.dccp.handshake_seq =
		be64_to_cpu(nla_get_be64(tb[CTA_PROTOINFO_DCCP_HANDSHAKE_SEQ]));
	पूर्ण
	spin_unlock_bh(&ct->lock);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_ctसमयout.h>

अटल पूर्णांक dccp_समयout_nlattr_to_obj(काष्ठा nlattr *tb[],
				      काष्ठा net *net, व्योम *data)
अणु
	काष्ठा nf_dccp_net *dn = nf_dccp_pernet(net);
	अचिन्हित पूर्णांक *समयouts = data;
	पूर्णांक i;

	अगर (!समयouts)
		 समयouts = dn->dccp_समयout;

	/* set शेष DCCP समयouts. */
	क्रम (i=0; i<CT_DCCP_MAX; i++)
		समयouts[i] = dn->dccp_समयout[i];

	/* there's a 1:1 mapping between attributes and protocol states. */
	क्रम (i=CTA_TIMEOUT_DCCP_UNSPEC+1; i<CTA_TIMEOUT_DCCP_MAX+1; i++) अणु
		अगर (tb[i]) अणु
			समयouts[i] = ntohl(nla_get_be32(tb[i])) * HZ;
		पूर्ण
	पूर्ण

	समयouts[CTA_TIMEOUT_DCCP_UNSPEC] = समयouts[CTA_TIMEOUT_DCCP_REQUEST];
	वापस 0;
पूर्ण

अटल पूर्णांक
dccp_समयout_obj_to_nlattr(काष्ठा sk_buff *skb, स्थिर व्योम *data)
अणु
        स्थिर अचिन्हित पूर्णांक *समयouts = data;
	पूर्णांक i;

	क्रम (i=CTA_TIMEOUT_DCCP_UNSPEC+1; i<CTA_TIMEOUT_DCCP_MAX+1; i++) अणु
		अगर (nla_put_be32(skb, i, htonl(समयouts[i] / HZ)))
			जाओ nla_put_failure;
	पूर्ण
	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल स्थिर काष्ठा nla_policy
dccp_समयout_nla_policy[CTA_TIMEOUT_DCCP_MAX+1] = अणु
	[CTA_TIMEOUT_DCCP_REQUEST]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_DCCP_RESPOND]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_DCCP_PARTOPEN]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_DCCP_OPEN]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_DCCP_CLOSEREQ]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_DCCP_CLOSING]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_DCCP_TIMEWAIT]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

व्योम nf_conntrack_dccp_init_net(काष्ठा net *net)
अणु
	काष्ठा nf_dccp_net *dn = nf_dccp_pernet(net);

	/* शेष values */
	dn->dccp_loose = 1;
	dn->dccp_समयout[CT_DCCP_REQUEST]	= 2 * DCCP_MSL;
	dn->dccp_समयout[CT_DCCP_RESPOND]	= 4 * DCCP_MSL;
	dn->dccp_समयout[CT_DCCP_PARTOPEN]	= 4 * DCCP_MSL;
	dn->dccp_समयout[CT_DCCP_OPEN]		= 12 * 3600 * HZ;
	dn->dccp_समयout[CT_DCCP_CLOSEREQ]	= 64 * HZ;
	dn->dccp_समयout[CT_DCCP_CLOSING]	= 64 * HZ;
	dn->dccp_समयout[CT_DCCP_TIMEWAIT]	= 2 * DCCP_MSL;

	/* समयouts[0] is unused, make it same as SYN_SENT so
	 * ->समयouts[0] contains 'new' समयout, like udp or icmp.
	 */
	dn->dccp_समयout[CT_DCCP_NONE] = dn->dccp_समयout[CT_DCCP_REQUEST];
पूर्ण

स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_dccp = अणु
	.l4proto		= IPPROTO_DCCP,
	.can_early_drop		= dccp_can_early_drop,
#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
	.prपूर्णांक_conntrack	= dccp_prपूर्णांक_conntrack,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)
	.nlattr_size		= DCCP_NLATTR_SIZE,
	.to_nlattr		= dccp_to_nlattr,
	.from_nlattr		= nlattr_to_dccp,
	.tuple_to_nlattr	= nf_ct_port_tuple_to_nlattr,
	.nlattr_tuple_size	= nf_ct_port_nlattr_tuple_size,
	.nlattr_to_tuple	= nf_ct_port_nlattr_to_tuple,
	.nla_policy		= nf_ct_port_nla_policy,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	.ctnl_समयout		= अणु
		.nlattr_to_obj	= dccp_समयout_nlattr_to_obj,
		.obj_to_nlattr	= dccp_समयout_obj_to_nlattr,
		.nlattr_max	= CTA_TIMEOUT_DCCP_MAX,
		.obj_size	= माप(अचिन्हित पूर्णांक) * CT_DCCP_MAX,
		.nla_policy	= dccp_समयout_nla_policy,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */
पूर्ण;
