<शैली गुरु>
/*
 * Routines to compress and uncompress tcp packets (क्रम transmission
 * over low speed serial lines).
 *
 * Copyright (c) 1989 Regents of the University of Calअगरornia.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such क्रमms and that any करोcumentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of Calअगरornia, Berkeley.  The name of the
 * University may not be used to enकरोrse or promote products derived
 * from this software without specअगरic prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Van Jacobson (van@helios.ee.lbl.gov), Dec 31, 1989:
 *	- Initial distribution.
 *
 *
 * modअगरied क्रम KA9Q Internet Software Package by
 * Katie Stevens (dkstevens@ucdavis.edu)
 * University of Calअगरornia, Davis
 * Computing Services
 *	- 01-31-90	initial adaptation (from 1.19)
 *	PPP.05	02-15-90 [ks]
 *	PPP.08	05-02-90 [ks]	use PPP protocol field to संकेत compression
 *	PPP.15	09-90	 [ks]	improve mbuf handling
 *	PPP.16	11-02	 [karn]	substantially rewritten to use NOS facilities
 *
 *	- Feb 1991	Bill_Simpson@um.cc.umich.edu
 *			variable number of conversation slots
 *			allow zero or one slots
 *			separate routines
 *			status display
 *	- Jul 1994	Dmitry Gorodchanin
 *			Fixes क्रम memory leaks.
 *      - Oct 1994      Dmitry Gorodchanin
 *                      Modularization.
 *	- Jan 1995	Bjorn Ekwall
 *			Use ip_fast_csum from ip.h
 *	- July 1995	Christos A. Polyzols
 *			Spotted bug in tcp option checking
 *
 *
 *	This module is a dअगरficult issue. It's clearly inet code but it's also clearly
 *	driver code beदीर्घing बंद to PPP and SLIP
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <net/slhc_vj.h>

#अगर_घोषित CONFIG_INET
/* Entire module is क्रम IP only */
#समावेश <linux/mm.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/termios.h>
#समावेश <linux/in.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/icmp.h>
#समावेश <net/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/uaccess.h>
#समावेश <net/checksum.h>
#समावेश <यंत्र/unaligned.h>

अटल अचिन्हित अक्षर *encode(अचिन्हित अक्षर *cp, अचिन्हित लघु n);
अटल दीर्घ decode(अचिन्हित अक्षर **cpp);
अटल अचिन्हित अक्षर * put16(अचिन्हित अक्षर *cp, अचिन्हित लघु x);
अटल अचिन्हित लघु pull16(अचिन्हित अक्षर **cpp);

/* Allocate compression data काष्ठाure
 *	slots must be in range 0 to 255 (zero meaning no compression)
 * Returns poपूर्णांकer to काष्ठाure or ERR_PTR() on error.
 */
काष्ठा slcompress *
slhc_init(पूर्णांक rslots, पूर्णांक tslots)
अणु
	लघु i;
	काष्ठा cstate *ts;
	काष्ठा slcompress *comp;

	अगर (rslots < 0 || rslots > 255 || tslots < 0 || tslots > 255)
		वापस ERR_PTR(-EINVAL);

	comp = kzalloc(माप(काष्ठा slcompress), GFP_KERNEL);
	अगर (! comp)
		जाओ out_fail;

	अगर (rslots > 0) अणु
		माप_प्रकार rsize = rslots * माप(काष्ठा cstate);
		comp->rstate = kzalloc(rsize, GFP_KERNEL);
		अगर (! comp->rstate)
			जाओ out_मुक्त;
		comp->rslot_limit = rslots - 1;
	पूर्ण

	अगर (tslots > 0) अणु
		माप_प्रकार tsize = tslots * माप(काष्ठा cstate);
		comp->tstate = kzalloc(tsize, GFP_KERNEL);
		अगर (! comp->tstate)
			जाओ out_मुक्त2;
		comp->tslot_limit = tslots - 1;
	पूर्ण

	comp->xmit_oldest = 0;
	comp->xmit_current = 255;
	comp->recv_current = 255;
	/*
	 * करोn't accept any packets with implicit index until we get
	 * one with an explicit index.  Otherwise the uncompress code
	 * will try to use connection 255, which is almost certainly
	 * out of range
	 */
	comp->flags |= SLF_TOSS;

	अगर ( tslots > 0 ) अणु
		ts = comp->tstate;
		क्रम(i = comp->tslot_limit; i > 0; --i)अणु
			ts[i].cs_this = i;
			ts[i].next = &(ts[i - 1]);
		पूर्ण
		ts[0].next = &(ts[comp->tslot_limit]);
		ts[0].cs_this = 0;
	पूर्ण
	वापस comp;

out_मुक्त2:
	kमुक्त(comp->rstate);
out_मुक्त:
	kमुक्त(comp);
out_fail:
	वापस ERR_PTR(-ENOMEM);
पूर्ण


/* Free a compression data काष्ठाure */
व्योम
slhc_मुक्त(काष्ठा slcompress *comp)
अणु
	अगर ( IS_ERR_OR_शून्य(comp) )
		वापस;

	अगर ( comp->tstate != शून्यSLSTATE )
		kमुक्त( comp->tstate );

	अगर ( comp->rstate != शून्यSLSTATE )
		kमुक्त( comp->rstate );

	kमुक्त( comp );
पूर्ण


/* Put a लघु in host order पूर्णांकo a अक्षर array in network order */
अटल अंतरभूत अचिन्हित अक्षर *
put16(अचिन्हित अक्षर *cp, अचिन्हित लघु x)
अणु
	*cp++ = x >> 8;
	*cp++ = x;

	वापस cp;
पूर्ण


/* Encode a number */
अटल अचिन्हित अक्षर *
encode(अचिन्हित अक्षर *cp, अचिन्हित लघु n)
अणु
	अगर(n >= 256 || n == 0)अणु
		*cp++ = 0;
		cp = put16(cp,n);
	पूर्ण अन्यथा अणु
		*cp++ = n;
	पूर्ण
	वापस cp;
पूर्ण

/* Pull a 16-bit पूर्णांकeger in host order from buffer in network byte order */
अटल अचिन्हित लघु
pull16(अचिन्हित अक्षर **cpp)
अणु
	लघु rval;

	rval = *(*cpp)++;
	rval <<= 8;
	rval |= *(*cpp)++;
	वापस rval;
पूर्ण

/* Decode a number */
अटल दीर्घ
decode(अचिन्हित अक्षर **cpp)
अणु
	पूर्णांक x;

	x = *(*cpp)++;
	अगर(x == 0)अणु
		वापस pull16(cpp) & 0xffff;	/* pull16 वापसs -1 on error */
	पूर्ण अन्यथा अणु
		वापस x & 0xff;		/* -1 अगर PULLCHAR वापसed error */
	पूर्ण
पूर्ण

/*
 * icp and isize are the original packet.
 * ocp is a place to put a copy अगर necessary.
 * cpp is initially a poपूर्णांकer to icp.  If the copy is used,
 *    change it to ocp.
 */

पूर्णांक
slhc_compress(काष्ठा slcompress *comp, अचिन्हित अक्षर *icp, पूर्णांक isize,
	अचिन्हित अक्षर *ocp, अचिन्हित अक्षर **cpp, पूर्णांक compress_cid)
अणु
	काष्ठा cstate *ocs = &(comp->tstate[comp->xmit_oldest]);
	काष्ठा cstate *lcs = ocs;
	काष्ठा cstate *cs = lcs->next;
	अचिन्हित दीर्घ deltaS, deltaA;
	लघु changes = 0;
	पूर्णांक nlen, hlen;
	अचिन्हित अक्षर new_seq[16];
	अचिन्हित अक्षर *cp = new_seq;
	काष्ठा iphdr *ip;
	काष्ठा tcphdr *th, *oth;
	__sum16 csum;


	/*
	 *	Don't play with runt packets.
	 */

	अगर(isize<माप(काष्ठा iphdr))
		वापस isize;

	ip = (काष्ठा iphdr *) icp;
	अगर (ip->version != 4 || ip->ihl < 5)
		वापस isize;

	/* Bail अगर this packet isn't TCP, or is an IP fragment */
	अगर (ip->protocol != IPPROTO_TCP || (ntohs(ip->frag_off) & 0x3fff)) अणु
		/* Send as regular IP */
		अगर(ip->protocol != IPPROTO_TCP)
			comp->sls_o_nontcp++;
		अन्यथा
			comp->sls_o_tcp++;
		वापस isize;
	पूर्ण
	nlen = ip->ihl * 4;
	अगर (isize < nlen + माप(*th))
		वापस isize;

	th = (काष्ठा tcphdr *)(icp + nlen);
	अगर (th->करोff < माप(काष्ठा tcphdr) / 4)
		वापस isize;
	hlen = nlen + th->करोff * 4;

	/*  Bail अगर the TCP packet isn't `compressible' (i.e., ACK isn't set or
	 *  some other control bit is set). Also uncompressible अगर
	 *  it's a runt.
	 */
	अगर(hlen > isize || th->syn || th->fin || th->rst ||
	    ! (th->ack))अणु
		/* TCP connection stuff; send as regular IP */
		comp->sls_o_tcp++;
		वापस isize;
	पूर्ण
	/*
	 * Packet is compressible -- we're going to send either a
	 * COMPRESSED_TCP or UNCOMPRESSED_TCP packet.  Either way,
	 * we need to locate (or create) the connection state.
	 *
	 * States are kept in a circularly linked list with
	 * xmit_oldest poपूर्णांकing to the end of the list.  The
	 * list is kept in lru order by moving a state to the
	 * head of the list whenever it is referenced.  Since
	 * the list is लघु and, empirically, the connection
	 * we want is almost always near the front, we locate
	 * states via linear search.  If we करोn't find a state
	 * क्रम the datagram, the oldest state is (re-)used.
	 */
	क्रम ( ; ; ) अणु
		अगर( ip->saddr == cs->cs_ip.saddr
		 && ip->daddr == cs->cs_ip.daddr
		 && th->source == cs->cs_tcp.source
		 && th->dest == cs->cs_tcp.dest)
			जाओ found;

		/* अगर current equal oldest, at end of list */
		अगर ( cs == ocs )
			अवरोध;
		lcs = cs;
		cs = cs->next;
		comp->sls_o_searches++;
	पूर्ण
	/*
	 * Didn't find it -- re-use oldest cstate.  Send an
	 * uncompressed packet that tells the other side what
	 * connection number we're using क्रम this conversation.
	 *
	 * Note that since the state list is circular, the oldest
	 * state poपूर्णांकs to the newest and we only need to set
	 * xmit_oldest to update the lru linkage.
	 */
	comp->sls_o_misses++;
	comp->xmit_oldest = lcs->cs_this;
	जाओ uncompressed;

found:
	/*
	 * Found it -- move to the front on the connection list.
	 */
	अगर(lcs == ocs) अणु
 		/* found at most recently used */
	पूर्ण अन्यथा अगर (cs == ocs) अणु
		/* found at least recently used */
		comp->xmit_oldest = lcs->cs_this;
	पूर्ण अन्यथा अणु
		/* more than 2 elements */
		lcs->next = cs->next;
		cs->next = ocs->next;
		ocs->next = cs;
	पूर्ण

	/*
	 * Make sure that only what we expect to change changed.
	 * Check the following:
	 * IP protocol version, header length & type of service.
	 * The "Don't fragment" bit.
	 * The समय-to-live field.
	 * The TCP header length.
	 * IP options, अगर any.
	 * TCP options, अगर any.
	 * If any of these things are dअगरferent between the previous &
	 * current datagram, we send the current datagram `uncompressed'.
	 */
	oth = &cs->cs_tcp;

	अगर(ip->version != cs->cs_ip.version || ip->ihl != cs->cs_ip.ihl
	 || ip->tos != cs->cs_ip.tos
	 || (ip->frag_off & htons(0x4000)) != (cs->cs_ip.frag_off & htons(0x4000))
	 || ip->ttl != cs->cs_ip.ttl
	 || th->करोff != cs->cs_tcp.करोff
	 || (ip->ihl > 5 && स_भेद(ip+1,cs->cs_ipopt,((ip->ihl)-5)*4) != 0)
	 || (th->करोff > 5 && स_भेद(th+1,cs->cs_tcpopt,((th->करोff)-5)*4) != 0))अणु
		जाओ uncompressed;
	पूर्ण

	/*
	 * Figure out which of the changing fields changed.  The
	 * receiver expects changes in the order: urgent, winकरोw,
	 * ack, seq (the order minimizes the number of temporaries
	 * needed in this section of code).
	 */
	अगर(th->urg)अणु
		deltaS = ntohs(th->urg_ptr);
		cp = encode(cp,deltaS);
		changes |= NEW_U;
	पूर्ण अन्यथा अगर(th->urg_ptr != oth->urg_ptr)अणु
		/* argh! URG not set but urp changed -- a sensible
		 * implementation should never करो this but RFC793
		 * करोesn't prohibit the change so we have to deal
		 * with it. */
		जाओ uncompressed;
	पूर्ण
	अगर((deltaS = ntohs(th->winकरोw) - ntohs(oth->winकरोw)) != 0)अणु
		cp = encode(cp,deltaS);
		changes |= NEW_W;
	पूर्ण
	अगर((deltaA = ntohl(th->ack_seq) - ntohl(oth->ack_seq)) != 0L)अणु
		अगर(deltaA > 0x0000ffff)
			जाओ uncompressed;
		cp = encode(cp,deltaA);
		changes |= NEW_A;
	पूर्ण
	अगर((deltaS = ntohl(th->seq) - ntohl(oth->seq)) != 0L)अणु
		अगर(deltaS > 0x0000ffff)
			जाओ uncompressed;
		cp = encode(cp,deltaS);
		changes |= NEW_S;
	पूर्ण

	चयन(changes)अणु
	हाल 0:	/* Nothing changed. If this packet contains data and the
		 * last one didn't, this is probably a data packet following
		 * an ack (normal on an पूर्णांकeractive connection) and we send
		 * it compressed.  Otherwise it's probably a retransmit,
		 * retransmitted ack or winकरोw probe.  Send it uncompressed
		 * in हाल the other side missed the compressed version.
		 */
		अगर(ip->tot_len != cs->cs_ip.tot_len &&
		   ntohs(cs->cs_ip.tot_len) == hlen)
			अवरोध;
		जाओ uncompressed;
	हाल SPECIAL_I:
	हाल SPECIAL_D:
		/* actual changes match one of our special हाल encodings --
		 * send packet uncompressed.
		 */
		जाओ uncompressed;
	हाल NEW_S|NEW_A:
		अगर(deltaS == deltaA &&
		    deltaS == ntohs(cs->cs_ip.tot_len) - hlen)अणु
			/* special हाल क्रम echoed terminal traffic */
			changes = SPECIAL_I;
			cp = new_seq;
		पूर्ण
		अवरोध;
	हाल NEW_S:
		अगर(deltaS == ntohs(cs->cs_ip.tot_len) - hlen)अणु
			/* special हाल क्रम data xfer */
			changes = SPECIAL_D;
			cp = new_seq;
		पूर्ण
		अवरोध;
	पूर्ण
	deltaS = ntohs(ip->id) - ntohs(cs->cs_ip.id);
	अगर(deltaS != 1)अणु
		cp = encode(cp,deltaS);
		changes |= NEW_I;
	पूर्ण
	अगर(th->psh)
		changes |= TCP_PUSH_BIT;
	/* Grab the cksum beक्रमe we overग_लिखो it below.  Then update our
	 * state with this packet's header.
	 */
	csum = th->check;
	स_नकल(&cs->cs_ip,ip,20);
	स_नकल(&cs->cs_tcp,th,20);
	/* We want to use the original packet as our compressed packet.
	 * (cp - new_seq) is the number of bytes we need क्रम compressed
	 * sequence numbers.  In addition we need one byte क्रम the change
	 * mask, one क्रम the connection id and two क्रम the tcp checksum.
	 * So, (cp - new_seq) + 4 bytes of header are needed.
	 */
	deltaS = cp - new_seq;
	अगर(compress_cid == 0 || comp->xmit_current != cs->cs_this)अणु
		cp = ocp;
		*cpp = ocp;
		*cp++ = changes | NEW_C;
		*cp++ = cs->cs_this;
		comp->xmit_current = cs->cs_this;
	पूर्ण अन्यथा अणु
		cp = ocp;
		*cpp = ocp;
		*cp++ = changes;
	पूर्ण
	*(__sum16 *)cp = csum;
	cp += 2;
/* deltaS is now the size of the change section of the compressed header */
	स_नकल(cp,new_seq,deltaS);	/* Write list of deltas */
	स_नकल(cp+deltaS,icp+hlen,isize-hlen);
	comp->sls_o_compressed++;
	ocp[0] |= SL_TYPE_COMPRESSED_TCP;
	वापस isize - hlen + deltaS + (cp - ocp);

	/* Update connection state cs & send uncompressed packet (i.e.,
	 * a regular ip/tcp packet but with the 'conversation id' we hope
	 * to use on future compressed packets in the protocol field).
	 */
uncompressed:
	स_नकल(&cs->cs_ip,ip,20);
	स_नकल(&cs->cs_tcp,th,20);
	अगर (ip->ihl > 5)
	  स_नकल(cs->cs_ipopt, ip+1, ((ip->ihl) - 5) * 4);
	अगर (th->करोff > 5)
	  स_नकल(cs->cs_tcpopt, th+1, ((th->करोff) - 5) * 4);
	comp->xmit_current = cs->cs_this;
	comp->sls_o_uncompressed++;
	स_नकल(ocp, icp, isize);
	*cpp = ocp;
	ocp[9] = cs->cs_this;
	ocp[0] |= SL_TYPE_UNCOMPRESSED_TCP;
	वापस isize;
पूर्ण


पूर्णांक
slhc_uncompress(काष्ठा slcompress *comp, अचिन्हित अक्षर *icp, पूर्णांक isize)
अणु
	पूर्णांक changes;
	दीर्घ x;
	काष्ठा tcphdr *thp;
	काष्ठा iphdr *ip;
	काष्ठा cstate *cs;
	पूर्णांक len, hdrlen;
	अचिन्हित अक्षर *cp = icp;

	/* We've got a compressed packet; पढ़ो the change byte */
	comp->sls_i_compressed++;
	अगर(isize < 3)अणु
		comp->sls_i_error++;
		वापस 0;
	पूर्ण
	changes = *cp++;
	अगर(changes & NEW_C)अणु
		/* Make sure the state index is in range, then grab the state.
		 * If we have a good state index, clear the 'discard' flag.
		 */
		x = *cp++;	/* Read conn index */
		अगर(x < 0 || x > comp->rslot_limit)
			जाओ bad;

		/* Check अगर the cstate is initialized */
		अगर (!comp->rstate[x].initialized)
			जाओ bad;

		comp->flags &=~ SLF_TOSS;
		comp->recv_current = x;
	पूर्ण अन्यथा अणु
		/* this packet has an implicit state index.  If we've
		 * had a line error since the last समय we got an
		 * explicit state index, we have to toss the packet. */
		अगर(comp->flags & SLF_TOSS)अणु
			comp->sls_i_tossed++;
			वापस 0;
		पूर्ण
	पूर्ण
	cs = &comp->rstate[comp->recv_current];
	thp = &cs->cs_tcp;
	ip = &cs->cs_ip;

	thp->check = *(__sum16 *)cp;
	cp += 2;

	thp->psh = (changes & TCP_PUSH_BIT) ? 1 : 0;
/*
 * we can use the same number क्रम the length of the saved header and
 * the current one, because the packet wouldn't have been sent
 * as compressed unless the options were the same as the previous one
 */

	hdrlen = ip->ihl * 4 + thp->करोff * 4;

	चयन(changes & SPECIALS_MASK)अणु
	हाल SPECIAL_I:		/* Echoed terminal traffic */
		अणु
		लघु i;
		i = ntohs(ip->tot_len) - hdrlen;
		thp->ack_seq = htonl( ntohl(thp->ack_seq) + i);
		thp->seq = htonl( ntohl(thp->seq) + i);
		पूर्ण
		अवरोध;

	हाल SPECIAL_D:			/* Unidirectional data */
		thp->seq = htonl( ntohl(thp->seq) +
				  ntohs(ip->tot_len) - hdrlen);
		अवरोध;

	शेष:
		अगर(changes & NEW_U)अणु
			thp->urg = 1;
			अगर((x = decode(&cp)) == -1) अणु
				जाओ bad;
			पूर्ण
			thp->urg_ptr = htons(x);
		पूर्ण अन्यथा
			thp->urg = 0;
		अगर(changes & NEW_W)अणु
			अगर((x = decode(&cp)) == -1) अणु
				जाओ bad;
			पूर्ण
			thp->winकरोw = htons( ntohs(thp->winकरोw) + x);
		पूर्ण
		अगर(changes & NEW_A)अणु
			अगर((x = decode(&cp)) == -1) अणु
				जाओ bad;
			पूर्ण
			thp->ack_seq = htonl( ntohl(thp->ack_seq) + x);
		पूर्ण
		अगर(changes & NEW_S)अणु
			अगर((x = decode(&cp)) == -1) अणु
				जाओ bad;
			पूर्ण
			thp->seq = htonl( ntohl(thp->seq) + x);
		पूर्ण
		अवरोध;
	पूर्ण
	अगर(changes & NEW_I)अणु
		अगर((x = decode(&cp)) == -1) अणु
			जाओ bad;
		पूर्ण
		ip->id = htons (ntohs (ip->id) + x);
	पूर्ण अन्यथा
		ip->id = htons (ntohs (ip->id) + 1);

	/*
	 * At this poपूर्णांक, cp poपूर्णांकs to the first byte of data in the
	 * packet.  Put the reस्थिरructed TCP and IP headers back on the
	 * packet.  Recalculate IP checksum (but not TCP checksum).
	 */

	len = isize - (cp - icp);
	अगर (len < 0)
		जाओ bad;
	len += hdrlen;
	ip->tot_len = htons(len);
	ip->check = 0;

	स_हटाओ(icp + hdrlen, cp, len - hdrlen);

	cp = icp;
	स_नकल(cp, ip, 20);
	cp += 20;

	अगर (ip->ihl > 5) अणु
	  स_नकल(cp, cs->cs_ipopt, (ip->ihl - 5) * 4);
	  cp += (ip->ihl - 5) * 4;
	पूर्ण

	put_unaligned(ip_fast_csum(icp, ip->ihl),
		      &((काष्ठा iphdr *)icp)->check);

	स_नकल(cp, thp, 20);
	cp += 20;

	अगर (thp->करोff > 5) अणु
	  स_नकल(cp, cs->cs_tcpopt, ((thp->करोff) - 5) * 4);
	  cp += ((thp->करोff) - 5) * 4;
	पूर्ण

	वापस len;
bad:
	comp->sls_i_error++;
	वापस slhc_toss( comp );
पूर्ण


पूर्णांक
slhc_remember(काष्ठा slcompress *comp, अचिन्हित अक्षर *icp, पूर्णांक isize)
अणु
	काष्ठा cstate *cs;
	अचिन्हित ihl;

	अचिन्हित अक्षर index;

	अगर(isize < 20) अणु
		/* The packet is लघुer than a legal IP header */
		comp->sls_i_runt++;
		वापस slhc_toss( comp );
	पूर्ण
	/* Peek at the IP header's IHL field to find its length */
	ihl = icp[0] & 0xf;
	अगर(ihl < 20 / 4)अणु
		/* The IP header length field is too small */
		comp->sls_i_runt++;
		वापस slhc_toss( comp );
	पूर्ण
	index = icp[9];
	icp[9] = IPPROTO_TCP;

	अगर (ip_fast_csum(icp, ihl)) अणु
		/* Bad IP header checksum; discard */
		comp->sls_i_badcheck++;
		वापस slhc_toss( comp );
	पूर्ण
	अगर(index > comp->rslot_limit) अणु
		comp->sls_i_error++;
		वापस slhc_toss(comp);
	पूर्ण

	/* Update local state */
	cs = &comp->rstate[comp->recv_current = index];
	comp->flags &=~ SLF_TOSS;
	स_नकल(&cs->cs_ip,icp,20);
	स_नकल(&cs->cs_tcp,icp + ihl*4,20);
	अगर (ihl > 5)
	  स_नकल(cs->cs_ipopt, icp + माप(काष्ठा iphdr), (ihl - 5) * 4);
	अगर (cs->cs_tcp.करोff > 5)
	  स_नकल(cs->cs_tcpopt, icp + ihl*4 + माप(काष्ठा tcphdr), (cs->cs_tcp.करोff - 5) * 4);
	cs->cs_hsize = ihl*2 + cs->cs_tcp.करोff*2;
	cs->initialized = true;
	/* Put headers back on packet
	 * Neither header checksum is recalculated
	 */
	comp->sls_i_uncompressed++;
	वापस isize;
पूर्ण

पूर्णांक
slhc_toss(काष्ठा slcompress *comp)
अणु
	अगर ( comp == शून्यSLCOMPR )
		वापस 0;

	comp->flags |= SLF_TOSS;
	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_INET */

पूर्णांक
slhc_toss(काष्ठा slcompress *comp)
अणु
  prपूर्णांकk(KERN_DEBUG "Called IP function on non IP-system: slhc_toss");
  वापस -EINVAL;
पूर्ण
पूर्णांक
slhc_uncompress(काष्ठा slcompress *comp, अचिन्हित अक्षर *icp, पूर्णांक isize)
अणु
  prपूर्णांकk(KERN_DEBUG "Called IP function on non IP-system: slhc_uncompress");
  वापस -EINVAL;
पूर्ण
पूर्णांक
slhc_compress(काष्ठा slcompress *comp, अचिन्हित अक्षर *icp, पूर्णांक isize,
	अचिन्हित अक्षर *ocp, अचिन्हित अक्षर **cpp, पूर्णांक compress_cid)
अणु
  prपूर्णांकk(KERN_DEBUG "Called IP function on non IP-system: slhc_compress");
  वापस -EINVAL;
पूर्ण

पूर्णांक
slhc_remember(काष्ठा slcompress *comp, अचिन्हित अक्षर *icp, पूर्णांक isize)
अणु
  prपूर्णांकk(KERN_DEBUG "Called IP function on non IP-system: slhc_remember");
  वापस -EINVAL;
पूर्ण

व्योम
slhc_मुक्त(काष्ठा slcompress *comp)
अणु
  prपूर्णांकk(KERN_DEBUG "Called IP function on non IP-system: slhc_free");
पूर्ण
काष्ठा slcompress *
slhc_init(पूर्णांक rslots, पूर्णांक tslots)
अणु
  prपूर्णांकk(KERN_DEBUG "Called IP function on non IP-system: slhc_init");
  वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_INET */

/* VJ header compression */
EXPORT_SYMBOL(slhc_init);
EXPORT_SYMBOL(slhc_मुक्त);
EXPORT_SYMBOL(slhc_remember);
EXPORT_SYMBOL(slhc_compress);
EXPORT_SYMBOL(slhc_uncompress);
EXPORT_SYMBOL(slhc_toss);

MODULE_LICENSE("Dual BSD/GPL");
