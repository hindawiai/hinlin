<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001-2002 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions work with the state functions in sctp_sm_statefuns.c
 * to implement the state operations.  These functions implement the
 * steps which require modअगरying existing data काष्ठाures.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    C. Robin              <chris@hundredacre.ac.uk>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Xingang Guo           <xingang.guo@पूर्णांकel.com>
 *    Dajiang Zhang	    <dajiang.zhang@nokia.com>
 *    Sridhar Samudrala	    <sri@us.ibm.com>
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 *    Kevin Gao             <kevin.gao@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <crypto/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/net.h>
#समावेश <linux/inet.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>

#समावेश <linux/skbuff.h>
#समावेश <linux/अक्रमom.h>	/* क्रम get_अक्रमom_bytes */
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

अटल काष्ठा sctp_chunk *sctp_make_control(स्थिर काष्ठा sctp_association *asoc,
					    __u8 type, __u8 flags, पूर्णांक paylen,
					    gfp_t gfp);
अटल काष्ठा sctp_chunk *sctp_make_data(स्थिर काष्ठा sctp_association *asoc,
					 __u8 flags, पूर्णांक paylen, gfp_t gfp);
अटल काष्ठा sctp_chunk *_sctp_make_chunk(स्थिर काष्ठा sctp_association *asoc,
					   __u8 type, __u8 flags, पूर्णांक paylen,
					   gfp_t gfp);
अटल काष्ठा sctp_cookie_param *sctp_pack_cookie(
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *init_chunk,
					पूर्णांक *cookie_len,
					स्थिर __u8 *raw_addrs, पूर्णांक addrs_len);
अटल पूर्णांक sctp_process_param(काष्ठा sctp_association *asoc,
			      जोड़ sctp_params param,
			      स्थिर जोड़ sctp_addr *peer_addr,
			      gfp_t gfp);
अटल व्योम *sctp_addto_param(काष्ठा sctp_chunk *chunk, पूर्णांक len,
			      स्थिर व्योम *data);

/* Control chunk deकाष्ठाor */
अटल व्योम sctp_control_release_owner(काष्ठा sk_buff *skb)
अणु
	काष्ठा sctp_chunk *chunk = skb_shinfo(skb)->deकाष्ठाor_arg;

	अगर (chunk->shkey) अणु
		काष्ठा sctp_shared_key *shkey = chunk->shkey;
		काष्ठा sctp_association *asoc = chunk->asoc;

		/* refcnt == 2 and !list_empty mean after this release, it's
		 * not being used anywhere, and it's समय to notअगरy userland
		 * that this shkey can be मुक्तd अगर it's been deactivated.
		 */
		अगर (shkey->deactivated && !list_empty(&shkey->key_list) &&
		    refcount_पढ़ो(&shkey->refcnt) == 2) अणु
			काष्ठा sctp_ulpevent *ev;

			ev = sctp_ulpevent_make_authkey(asoc, shkey->key_id,
							SCTP_AUTH_FREE_KEY,
							GFP_KERNEL);
			अगर (ev)
				asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
		पूर्ण
		sctp_auth_shkey_release(chunk->shkey);
	पूर्ण
पूर्ण

अटल व्योम sctp_control_set_owner_w(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_association *asoc = chunk->asoc;
	काष्ठा sk_buff *skb = chunk->skb;

	/* TODO: properly account क्रम control chunks.
	 * To करो it right we'll need:
	 *  1) endpoपूर्णांक अगर association isn't known.
	 *  2) proper memory accounting.
	 *
	 *  For now करोn't करो anything क्रम now.
	 */
	अगर (chunk->auth) अणु
		chunk->shkey = asoc->shkey;
		sctp_auth_shkey_hold(chunk->shkey);
	पूर्ण
	skb->sk = asoc ? asoc->base.sk : शून्य;
	skb_shinfo(skb)->deकाष्ठाor_arg = chunk;
	skb->deकाष्ठाor = sctp_control_release_owner;
पूर्ण

/* What was the inbound पूर्णांकerface क्रम this chunk? */
पूर्णांक sctp_chunk_iअगर(स्थिर काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sk_buff *skb = chunk->skb;

	वापस SCTP_INPUT_CB(skb)->af->skb_iअगर(skb);
पूर्ण

/* RFC 2960 3.3.2 Initiation (INIT) (1)
 *
 * Note 2: The ECN capable field is reserved क्रम future use of
 * Explicit Congestion Notअगरication.
 */
अटल स्थिर काष्ठा sctp_paramhdr ecap_param = अणु
	SCTP_PARAM_ECN_CAPABLE,
	cpu_to_be16(माप(काष्ठा sctp_paramhdr)),
पूर्ण;
अटल स्थिर काष्ठा sctp_paramhdr prsctp_param = अणु
	SCTP_PARAM_FWD_TSN_SUPPORT,
	cpu_to_be16(माप(काष्ठा sctp_paramhdr)),
पूर्ण;

/* A helper to initialize an op error inside a provided chunk, as most
 * cause codes will be embedded inside an पात chunk.
 */
पूर्णांक sctp_init_cause(काष्ठा sctp_chunk *chunk, __be16 cause_code,
		    माप_प्रकार paylen)
अणु
	काष्ठा sctp_errhdr err;
	__u16 len;

	/* Cause code स्थिरants are now defined in network order.  */
	err.cause = cause_code;
	len = माप(err) + paylen;
	err.length = htons(len);

	अगर (skb_tailroom(chunk->skb) < len)
		वापस -ENOSPC;

	chunk->subh.err_hdr = sctp_addto_chunk(chunk, माप(err), &err);

	वापस 0;
पूर्ण

/* 3.3.2 Initiation (INIT) (1)
 *
 * This chunk is used to initiate a SCTP association between two
 * endpoपूर्णांकs. The क्रमmat of the INIT chunk is shown below:
 *
 *     0                   1                   2                   3
 *     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |   Type = 1    |  Chunk Flags  |      Chunk Length             |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |                         Initiate Tag                          |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |           Advertised Receiver Winकरोw Credit (a_rwnd)          |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |  Number of Outbound Streams   |  Number of Inbound Streams    |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |                          Initial TSN                          |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    \                                                               \
 *    /              Optional/Variable-Length Parameters              /
 *    \                                                               \
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 * The INIT chunk contains the following parameters. Unless otherwise
 * noted, each parameter MUST only be included once in the INIT chunk.
 *
 * Fixed Parameters                     Status
 * ----------------------------------------------
 * Initiate Tag                        Mandatory
 * Advertised Receiver Winकरोw Credit   Mandatory
 * Number of Outbound Streams          Mandatory
 * Number of Inbound Streams           Mandatory
 * Initial TSN                         Mandatory
 *
 * Variable Parameters                  Status     Type Value
 * -------------------------------------------------------------
 * IPv4 Address (Note 1)               Optional    5
 * IPv6 Address (Note 1)               Optional    6
 * Cookie Preservative                 Optional    9
 * Reserved क्रम ECN Capable (Note 2)   Optional    32768 (0x8000)
 * Host Name Address (Note 3)          Optional    11
 * Supported Address Types (Note 4)    Optional    12
 */
काष्ठा sctp_chunk *sctp_make_init(स्थिर काष्ठा sctp_association *asoc,
				  स्थिर काष्ठा sctp_bind_addr *bp,
				  gfp_t gfp, पूर्णांक vparam_len)
अणु
	काष्ठा sctp_supported_ext_param ext_param;
	काष्ठा sctp_adaptation_ind_param aiparam;
	काष्ठा sctp_paramhdr *auth_chunks = शून्य;
	काष्ठा sctp_paramhdr *auth_hmacs = शून्य;
	काष्ठा sctp_supported_addrs_param sat;
	काष्ठा sctp_endpoपूर्णांक *ep = asoc->ep;
	काष्ठा sctp_chunk *retval = शून्य;
	पूर्णांक num_types, addrs_len = 0;
	काष्ठा sctp_inithdr init;
	जोड़ sctp_params addrs;
	काष्ठा sctp_sock *sp;
	__u8 extensions[5];
	माप_प्रकार chunksize;
	__be16 types[2];
	पूर्णांक num_ext = 0;

	/* RFC 2960 3.3.2 Initiation (INIT) (1)
	 *
	 * Note 1: The INIT chunks can contain multiple addresses that
	 * can be IPv4 and/or IPv6 in any combination.
	 */

	/* Convert the provided bind address list to raw क्रमmat. */
	addrs = sctp_bind_addrs_to_raw(bp, &addrs_len, gfp);

	init.init_tag		   = htonl(asoc->c.my_vtag);
	init.a_rwnd		   = htonl(asoc->rwnd);
	init.num_outbound_streams  = htons(asoc->c.sinit_num_ostreams);
	init.num_inbound_streams   = htons(asoc->c.sinit_max_instreams);
	init.initial_tsn	   = htonl(asoc->c.initial_tsn);

	/* How many address types are needed? */
	sp = sctp_sk(asoc->base.sk);
	num_types = sp->pf->supported_addrs(sp, types);

	chunksize = माप(init) + addrs_len;
	chunksize += SCTP_PAD4(SCTP_SAT_LEN(num_types));

	अगर (asoc->ep->ecn_enable)
		chunksize += माप(ecap_param);

	अगर (asoc->ep->prsctp_enable)
		chunksize += माप(prsctp_param);

	/* ADDIP: Section 4.2.7:
	 *  An implementation supporting this extension [ADDIP] MUST list
	 *  the ASCONF,the ASCONF-ACK, and the AUTH  chunks in its INIT and
	 *  INIT-ACK parameters.
	 */
	अगर (asoc->ep->asconf_enable) अणु
		extensions[num_ext] = SCTP_CID_ASCONF;
		extensions[num_ext+1] = SCTP_CID_ASCONF_ACK;
		num_ext += 2;
	पूर्ण

	अगर (asoc->ep->reconf_enable) अणु
		extensions[num_ext] = SCTP_CID_RECONF;
		num_ext += 1;
	पूर्ण

	अगर (sp->adaptation_ind)
		chunksize += माप(aiparam);

	अगर (asoc->ep->पूर्णांकl_enable) अणु
		extensions[num_ext] = SCTP_CID_I_DATA;
		num_ext += 1;
	पूर्ण

	chunksize += vparam_len;

	/* Account क्रम AUTH related parameters */
	अगर (ep->auth_enable) अणु
		/* Add अक्रमom parameter length*/
		chunksize += माप(asoc->c.auth_अक्रमom);

		/* Add HMACS parameter length अगर any were defined */
		auth_hmacs = (काष्ठा sctp_paramhdr *)asoc->c.auth_hmacs;
		अगर (auth_hmacs->length)
			chunksize += SCTP_PAD4(ntohs(auth_hmacs->length));
		अन्यथा
			auth_hmacs = शून्य;

		/* Add CHUNKS parameter length */
		auth_chunks = (काष्ठा sctp_paramhdr *)asoc->c.auth_chunks;
		अगर (auth_chunks->length)
			chunksize += SCTP_PAD4(ntohs(auth_chunks->length));
		अन्यथा
			auth_chunks = शून्य;

		extensions[num_ext] = SCTP_CID_AUTH;
		num_ext += 1;
	पूर्ण

	/* If we have any extensions to report, account क्रम that */
	अगर (num_ext)
		chunksize += SCTP_PAD4(माप(ext_param) + num_ext);

	/* RFC 2960 3.3.2 Initiation (INIT) (1)
	 *
	 * Note 3: An INIT chunk MUST NOT contain more than one Host
	 * Name address parameter. Moreover, the sender of the INIT
	 * MUST NOT combine any other address types with the Host Name
	 * address in the INIT. The receiver of INIT MUST ignore any
	 * other address types अगर the Host Name address parameter is
	 * present in the received INIT chunk.
	 *
	 * PLEASE DO NOT FIXME [This version करोes not support Host Name.]
	 */

	retval = sctp_make_control(asoc, SCTP_CID_INIT, 0, chunksize, gfp);
	अगर (!retval)
		जाओ nodata;

	retval->subh.init_hdr =
		sctp_addto_chunk(retval, माप(init), &init);
	retval->param_hdr.v =
		sctp_addto_chunk(retval, addrs_len, addrs.v);

	/* RFC 2960 3.3.2 Initiation (INIT) (1)
	 *
	 * Note 4: This parameter, when present, specअगरies all the
	 * address types the sending endpoपूर्णांक can support. The असलence
	 * of this parameter indicates that the sending endpoपूर्णांक can
	 * support any address type.
	 */
	sat.param_hdr.type = SCTP_PARAM_SUPPORTED_ADDRESS_TYPES;
	sat.param_hdr.length = htons(SCTP_SAT_LEN(num_types));
	sctp_addto_chunk(retval, माप(sat), &sat);
	sctp_addto_chunk(retval, num_types * माप(__u16), &types);

	अगर (asoc->ep->ecn_enable)
		sctp_addto_chunk(retval, माप(ecap_param), &ecap_param);

	/* Add the supported extensions parameter.  Be nice and add this
	 * fist beक्रमe addiding the parameters क्रम the extensions themselves
	 */
	अगर (num_ext) अणु
		ext_param.param_hdr.type = SCTP_PARAM_SUPPORTED_EXT;
		ext_param.param_hdr.length = htons(माप(ext_param) + num_ext);
		sctp_addto_chunk(retval, माप(ext_param), &ext_param);
		sctp_addto_param(retval, num_ext, extensions);
	पूर्ण

	अगर (asoc->ep->prsctp_enable)
		sctp_addto_chunk(retval, माप(prsctp_param), &prsctp_param);

	अगर (sp->adaptation_ind) अणु
		aiparam.param_hdr.type = SCTP_PARAM_ADAPTATION_LAYER_IND;
		aiparam.param_hdr.length = htons(माप(aiparam));
		aiparam.adaptation_ind = htonl(sp->adaptation_ind);
		sctp_addto_chunk(retval, माप(aiparam), &aiparam);
	पूर्ण

	/* Add SCTP-AUTH chunks to the parameter list */
	अगर (ep->auth_enable) अणु
		sctp_addto_chunk(retval, माप(asoc->c.auth_अक्रमom),
				 asoc->c.auth_अक्रमom);
		अगर (auth_hmacs)
			sctp_addto_chunk(retval, ntohs(auth_hmacs->length),
					auth_hmacs);
		अगर (auth_chunks)
			sctp_addto_chunk(retval, ntohs(auth_chunks->length),
					auth_chunks);
	पूर्ण
nodata:
	kमुक्त(addrs.v);
	वापस retval;
पूर्ण

काष्ठा sctp_chunk *sctp_make_init_ack(स्थिर काष्ठा sctp_association *asoc,
				      स्थिर काष्ठा sctp_chunk *chunk,
				      gfp_t gfp, पूर्णांक unkparam_len)
अणु
	काष्ठा sctp_supported_ext_param ext_param;
	काष्ठा sctp_adaptation_ind_param aiparam;
	काष्ठा sctp_paramhdr *auth_chunks = शून्य;
	काष्ठा sctp_paramhdr *auth_अक्रमom = शून्य;
	काष्ठा sctp_paramhdr *auth_hmacs = शून्य;
	काष्ठा sctp_chunk *retval = शून्य;
	काष्ठा sctp_cookie_param *cookie;
	काष्ठा sctp_inithdr initack;
	जोड़ sctp_params addrs;
	काष्ठा sctp_sock *sp;
	__u8 extensions[5];
	माप_प्रकार chunksize;
	पूर्णांक num_ext = 0;
	पूर्णांक cookie_len;
	पूर्णांक addrs_len;

	/* Note: there may be no addresses to embed. */
	addrs = sctp_bind_addrs_to_raw(&asoc->base.bind_addr, &addrs_len, gfp);

	initack.init_tag	        = htonl(asoc->c.my_vtag);
	initack.a_rwnd			= htonl(asoc->rwnd);
	initack.num_outbound_streams	= htons(asoc->c.sinit_num_ostreams);
	initack.num_inbound_streams	= htons(asoc->c.sinit_max_instreams);
	initack.initial_tsn		= htonl(asoc->c.initial_tsn);

	/* FIXME:  We really ought to build the cookie right
	 * पूर्णांकo the packet instead of allocating more fresh memory.
	 */
	cookie = sctp_pack_cookie(asoc->ep, asoc, chunk, &cookie_len,
				  addrs.v, addrs_len);
	अगर (!cookie)
		जाओ nomem_cookie;

	/* Calculate the total size of allocation, include the reserved
	 * space क्रम reporting unknown parameters अगर it is specअगरied.
	 */
	sp = sctp_sk(asoc->base.sk);
	chunksize = माप(initack) + addrs_len + cookie_len + unkparam_len;

	/* Tell peer that we'll करो ECN only अगर peer advertised such cap.  */
	अगर (asoc->peer.ecn_capable)
		chunksize += माप(ecap_param);

	अगर (asoc->peer.prsctp_capable)
		chunksize += माप(prsctp_param);

	अगर (asoc->peer.asconf_capable) अणु
		extensions[num_ext] = SCTP_CID_ASCONF;
		extensions[num_ext+1] = SCTP_CID_ASCONF_ACK;
		num_ext += 2;
	पूर्ण

	अगर (asoc->peer.reconf_capable) अणु
		extensions[num_ext] = SCTP_CID_RECONF;
		num_ext += 1;
	पूर्ण

	अगर (sp->adaptation_ind)
		chunksize += माप(aiparam);

	अगर (asoc->peer.पूर्णांकl_capable) अणु
		extensions[num_ext] = SCTP_CID_I_DATA;
		num_ext += 1;
	पूर्ण

	अगर (asoc->peer.auth_capable) अणु
		auth_अक्रमom = (काष्ठा sctp_paramhdr *)asoc->c.auth_अक्रमom;
		chunksize += ntohs(auth_अक्रमom->length);

		auth_hmacs = (काष्ठा sctp_paramhdr *)asoc->c.auth_hmacs;
		अगर (auth_hmacs->length)
			chunksize += SCTP_PAD4(ntohs(auth_hmacs->length));
		अन्यथा
			auth_hmacs = शून्य;

		auth_chunks = (काष्ठा sctp_paramhdr *)asoc->c.auth_chunks;
		अगर (auth_chunks->length)
			chunksize += SCTP_PAD4(ntohs(auth_chunks->length));
		अन्यथा
			auth_chunks = शून्य;

		extensions[num_ext] = SCTP_CID_AUTH;
		num_ext += 1;
	पूर्ण

	अगर (num_ext)
		chunksize += SCTP_PAD4(माप(ext_param) + num_ext);

	/* Now allocate and fill out the chunk.  */
	retval = sctp_make_control(asoc, SCTP_CID_INIT_ACK, 0, chunksize, gfp);
	अगर (!retval)
		जाओ nomem_chunk;

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [INIT ACK back to where the INIT came from.]
	 */
	अगर (chunk->transport)
		retval->transport =
			sctp_assoc_lookup_paddr(asoc,
						&chunk->transport->ipaddr);

	retval->subh.init_hdr =
		sctp_addto_chunk(retval, माप(initack), &initack);
	retval->param_hdr.v = sctp_addto_chunk(retval, addrs_len, addrs.v);
	sctp_addto_chunk(retval, cookie_len, cookie);
	अगर (asoc->peer.ecn_capable)
		sctp_addto_chunk(retval, माप(ecap_param), &ecap_param);
	अगर (num_ext) अणु
		ext_param.param_hdr.type = SCTP_PARAM_SUPPORTED_EXT;
		ext_param.param_hdr.length = htons(माप(ext_param) + num_ext);
		sctp_addto_chunk(retval, माप(ext_param), &ext_param);
		sctp_addto_param(retval, num_ext, extensions);
	पूर्ण
	अगर (asoc->peer.prsctp_capable)
		sctp_addto_chunk(retval, माप(prsctp_param), &prsctp_param);

	अगर (sp->adaptation_ind) अणु
		aiparam.param_hdr.type = SCTP_PARAM_ADAPTATION_LAYER_IND;
		aiparam.param_hdr.length = htons(माप(aiparam));
		aiparam.adaptation_ind = htonl(sp->adaptation_ind);
		sctp_addto_chunk(retval, माप(aiparam), &aiparam);
	पूर्ण

	अगर (asoc->peer.auth_capable) अणु
		sctp_addto_chunk(retval, ntohs(auth_अक्रमom->length),
				 auth_अक्रमom);
		अगर (auth_hmacs)
			sctp_addto_chunk(retval, ntohs(auth_hmacs->length),
					auth_hmacs);
		अगर (auth_chunks)
			sctp_addto_chunk(retval, ntohs(auth_chunks->length),
					auth_chunks);
	पूर्ण

	/* We need to हटाओ the स्थिर qualअगरier at this poपूर्णांक.  */
	retval->asoc = (काष्ठा sctp_association *) asoc;

nomem_chunk:
	kमुक्त(cookie);
nomem_cookie:
	kमुक्त(addrs.v);
	वापस retval;
पूर्ण

/* 3.3.11 Cookie Echo (COOKIE ECHO) (10):
 *
 * This chunk is used only during the initialization of an association.
 * It is sent by the initiator of an association to its peer to complete
 * the initialization process. This chunk MUST precede any DATA chunk
 * sent within the association, but MAY be bundled with one or more DATA
 * chunks in the same packet.
 *
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |   Type = 10   |Chunk  Flags   |         Length                |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     /                     Cookie                                    /
 *     \                                                               \
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Chunk Flags: 8 bit
 *
 *   Set to zero on transmit and ignored on receipt.
 *
 * Length: 16 bits (अचिन्हित पूर्णांकeger)
 *
 *   Set to the size of the chunk in bytes, including the 4 bytes of
 *   the chunk header and the size of the Cookie.
 *
 * Cookie: variable size
 *
 *   This field must contain the exact cookie received in the
 *   State Cookie parameter from the previous INIT ACK.
 *
 *   An implementation SHOULD make the cookie as small as possible
 *   to insure पूर्णांकeroperability.
 */
काष्ठा sctp_chunk *sctp_make_cookie_echo(स्थिर काष्ठा sctp_association *asoc,
					 स्थिर काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_chunk *retval;
	पूर्णांक cookie_len;
	व्योम *cookie;

	cookie = asoc->peer.cookie;
	cookie_len = asoc->peer.cookie_len;

	/* Build a cookie echo chunk.  */
	retval = sctp_make_control(asoc, SCTP_CID_COOKIE_ECHO, 0,
				   cookie_len, GFP_ATOMIC);
	अगर (!retval)
		जाओ nodata;
	retval->subh.cookie_hdr =
		sctp_addto_chunk(retval, cookie_len, cookie);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [COOKIE ECHO back to where the INIT ACK came from.]
	 */
	अगर (chunk)
		retval->transport = chunk->transport;

nodata:
	वापस retval;
पूर्ण

/* 3.3.12 Cookie Acknowledgement (COOKIE ACK) (11):
 *
 * This chunk is used only during the initialization of an
 * association.  It is used to acknowledge the receipt of a COOKIE
 * ECHO chunk.  This chunk MUST precede any DATA or SACK chunk sent
 * within the association, but MAY be bundled with one or more DATA
 * chunks or SACK chunk in the same SCTP packet.
 *
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |   Type = 11   |Chunk  Flags   |     Length = 4                |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Chunk Flags: 8 bits
 *
 *   Set to zero on transmit and ignored on receipt.
 */
काष्ठा sctp_chunk *sctp_make_cookie_ack(स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_control(asoc, SCTP_CID_COOKIE_ACK, 0, 0, GFP_ATOMIC);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [COOKIE ACK back to where the COOKIE ECHO came from.]
	 */
	अगर (retval && chunk && chunk->transport)
		retval->transport =
			sctp_assoc_lookup_paddr(asoc,
						&chunk->transport->ipaddr);

	वापस retval;
पूर्ण

/*
 *  Appendix A: Explicit Congestion Notअगरication:
 *  CWR:
 *
 *  RFC 2481 details a specअगरic bit क्रम a sender to send in the header of
 *  its next outbound TCP segment to indicate to its peer that it has
 *  reduced its congestion winकरोw.  This is termed the CWR bit.  For
 *  SCTP the same indication is made by including the CWR chunk.
 *  This chunk contains one data element, i.e. the TSN number that
 *  was sent in the ECNE chunk.  This element represents the lowest
 *  TSN number in the datagram that was originally marked with the
 *  CE bit.
 *
 *     0                   1                   2                   3
 *     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    | Chunk Type=13 | Flags=00000000|    Chunk Length = 8           |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |                      Lowest TSN Number                        |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *     Note: The CWR is considered a Control chunk.
 */
काष्ठा sctp_chunk *sctp_make_cwr(स्थिर काष्ठा sctp_association *asoc,
				 स्थिर __u32 lowest_tsn,
				 स्थिर काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_chunk *retval;
	काष्ठा sctp_cwrhdr cwr;

	cwr.lowest_tsn = htonl(lowest_tsn);
	retval = sctp_make_control(asoc, SCTP_CID_ECN_CWR, 0,
				   माप(cwr), GFP_ATOMIC);

	अगर (!retval)
		जाओ nodata;

	retval->subh.ecn_cwr_hdr =
		sctp_addto_chunk(retval, माप(cwr), &cwr);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [Report a reduced congestion winकरोw back to where the ECNE
	 * came from.]
	 */
	अगर (chunk)
		retval->transport = chunk->transport;

nodata:
	वापस retval;
पूर्ण

/* Make an ECNE chunk.  This is a congestion experienced report.  */
काष्ठा sctp_chunk *sctp_make_ecne(स्थिर काष्ठा sctp_association *asoc,
				  स्थिर __u32 lowest_tsn)
अणु
	काष्ठा sctp_chunk *retval;
	काष्ठा sctp_ecnehdr ecne;

	ecne.lowest_tsn = htonl(lowest_tsn);
	retval = sctp_make_control(asoc, SCTP_CID_ECN_ECNE, 0,
				   माप(ecne), GFP_ATOMIC);
	अगर (!retval)
		जाओ nodata;
	retval->subh.ecne_hdr =
		sctp_addto_chunk(retval, माप(ecne), &ecne);

nodata:
	वापस retval;
पूर्ण

/* Make a DATA chunk क्रम the given association from the provided
 * parameters.  However, करो not populate the data payload.
 */
काष्ठा sctp_chunk *sctp_make_datafrag_empty(स्थिर काष्ठा sctp_association *asoc,
					    स्थिर काष्ठा sctp_sndrcvinfo *sinfo,
					    पूर्णांक len, __u8 flags, gfp_t gfp)
अणु
	काष्ठा sctp_chunk *retval;
	काष्ठा sctp_datahdr dp;

	/* We assign the TSN as LATE as possible, not here when
	 * creating the chunk.
	 */
	स_रखो(&dp, 0, माप(dp));
	dp.ppid = sinfo->sinfo_ppid;
	dp.stream = htons(sinfo->sinfo_stream);

	/* Set the flags क्रम an unordered send.  */
	अगर (sinfo->sinfo_flags & SCTP_UNORDERED)
		flags |= SCTP_DATA_UNORDERED;

	retval = sctp_make_data(asoc, flags, माप(dp) + len, gfp);
	अगर (!retval)
		वापस शून्य;

	retval->subh.data_hdr = sctp_addto_chunk(retval, माप(dp), &dp);
	स_नकल(&retval->sinfo, sinfo, माप(काष्ठा sctp_sndrcvinfo));

	वापस retval;
पूर्ण

/* Create a selective ackowledgement (SACK) क्रम the given
 * association.  This reports on which TSN's we've seen to date,
 * including duplicates and gaps.
 */
काष्ठा sctp_chunk *sctp_make_sack(काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_tsnmap *map = (काष्ठा sctp_tsnmap *)&asoc->peer.tsn_map;
	काष्ठा sctp_gap_ack_block gअसल[SCTP_MAX_GABS];
	__u16 num_gअसल, num_dup_tsns;
	काष्ठा sctp_transport *trans;
	काष्ठा sctp_chunk *retval;
	काष्ठा sctp_sackhdr sack;
	__u32 ctsn;
	पूर्णांक len;

	स_रखो(gअसल, 0, माप(gअसल));
	ctsn = sctp_tsnmap_get_ctsn(map);

	pr_debug("%s: sackCTSNAck sent:0x%x\n", __func__, ctsn);

	/* How much room is needed in the chunk? */
	num_gअसल = sctp_tsnmap_num_gअसल(map, gअसल);
	num_dup_tsns = sctp_tsnmap_num_dups(map);

	/* Initialize the SACK header.  */
	sack.cum_tsn_ack	    = htonl(ctsn);
	sack.a_rwnd 		    = htonl(asoc->a_rwnd);
	sack.num_gap_ack_blocks     = htons(num_gअसल);
	sack.num_dup_tsns           = htons(num_dup_tsns);

	len = माप(sack)
		+ माप(काष्ठा sctp_gap_ack_block) * num_gअसल
		+ माप(__u32) * num_dup_tsns;

	/* Create the chunk.  */
	retval = sctp_make_control(asoc, SCTP_CID_SACK, 0, len, GFP_ATOMIC);
	अगर (!retval)
		जाओ nodata;

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, etc.) to the same destination transport
	 * address from which it received the DATA or control chunk to
	 * which it is replying.  This rule should also be followed अगर
	 * the endpoपूर्णांक is bundling DATA chunks together with the
	 * reply chunk.
	 *
	 * However, when acknowledging multiple DATA chunks received
	 * in packets from dअगरferent source addresses in a single
	 * SACK, the SACK chunk may be transmitted to one of the
	 * destination transport addresses from which the DATA or
	 * control chunks being acknowledged were received.
	 *
	 * [BUG:  We करो not implement the following paragraph.
	 * Perhaps we should remember the last transport we used क्रम a
	 * SACK and aव्योम that (अगर possible) अगर we have seen any
	 * duplicates. --piggy]
	 *
	 * When a receiver of a duplicate DATA chunk sends a SACK to a
	 * multi- homed endpoपूर्णांक it MAY be beneficial to vary the
	 * destination address and not use the source address of the
	 * DATA chunk.  The reason being that receiving a duplicate
	 * from a multi-homed endpoपूर्णांक might indicate that the वापस
	 * path (as specअगरied in the source address of the DATA chunk)
	 * क्रम the SACK is broken.
	 *
	 * [Send to the address from which we last received a DATA chunk.]
	 */
	retval->transport = asoc->peer.last_data_from;

	retval->subh.sack_hdr =
		sctp_addto_chunk(retval, माप(sack), &sack);

	/* Add the gap ack block inक्रमmation.   */
	अगर (num_gअसल)
		sctp_addto_chunk(retval, माप(__u32) * num_gअसल,
				 gअसल);

	/* Add the duplicate TSN inक्रमmation.  */
	अगर (num_dup_tsns) अणु
		asoc->stats.idupchunks += num_dup_tsns;
		sctp_addto_chunk(retval, माप(__u32) * num_dup_tsns,
				 sctp_tsnmap_get_dups(map));
	पूर्ण
	/* Once we have a sack generated, check to see what our sack
	 * generation is, अगर its 0, reset the transports to 0, and reset
	 * the association generation to 1
	 *
	 * The idea is that zero is never used as a valid generation क्रम the
	 * association so no transport will match after a wrap event like this,
	 * Until the next sack
	 */
	अगर (++asoc->peer.sack_generation == 0) अणु
		list_क्रम_each_entry(trans, &asoc->peer.transport_addr_list,
				    transports)
			trans->sack_generation = 0;
		asoc->peer.sack_generation = 1;
	पूर्ण
nodata:
	वापस retval;
पूर्ण

/* Make a SHUTDOWN chunk. */
काष्ठा sctp_chunk *sctp_make_shutकरोwn(स्थिर काष्ठा sctp_association *asoc,
				      स्थिर काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_shutकरोwnhdr shut;
	काष्ठा sctp_chunk *retval;
	__u32 ctsn;

	ctsn = sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map);
	shut.cum_tsn_ack = htonl(ctsn);

	retval = sctp_make_control(asoc, SCTP_CID_SHUTDOWN, 0,
				   माप(shut), GFP_ATOMIC);
	अगर (!retval)
		जाओ nodata;

	retval->subh.shutकरोwn_hdr =
		sctp_addto_chunk(retval, माप(shut), &shut);

	अगर (chunk)
		retval->transport = chunk->transport;
nodata:
	वापस retval;
पूर्ण

काष्ठा sctp_chunk *sctp_make_shutकरोwn_ack(स्थिर काष्ठा sctp_association *asoc,
					  स्थिर काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_control(asoc, SCTP_CID_SHUTDOWN_ACK, 0, 0,
				   GFP_ATOMIC);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [ACK back to where the SHUTDOWN came from.]
	 */
	अगर (retval && chunk)
		retval->transport = chunk->transport;

	वापस retval;
पूर्ण

काष्ठा sctp_chunk *sctp_make_shutकरोwn_complete(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_chunk *retval;
	__u8 flags = 0;

	/* Set the T-bit अगर we have no association (vtag will be
	 * reflected)
	 */
	flags |= asoc ? 0 : SCTP_CHUNK_FLAG_T;

	retval = sctp_make_control(asoc, SCTP_CID_SHUTDOWN_COMPLETE, flags,
				   0, GFP_ATOMIC);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [Report SHUTDOWN COMPLETE back to where the SHUTDOWN ACK
	 * came from.]
	 */
	अगर (retval && chunk)
		retval->transport = chunk->transport;

	वापस retval;
पूर्ण

/* Create an ABORT.  Note that we set the T bit अगर we have no
 * association, except when responding to an INIT (sctpimpguide 2.41).
 */
काष्ठा sctp_chunk *sctp_make_पात(स्थिर काष्ठा sctp_association *asoc,
				   स्थिर काष्ठा sctp_chunk *chunk,
				   स्थिर माप_प्रकार hपूर्णांक)
अणु
	काष्ठा sctp_chunk *retval;
	__u8 flags = 0;

	/* Set the T-bit अगर we have no association and 'chunk' is not
	 * an INIT (vtag will be reflected).
	 */
	अगर (!asoc) अणु
		अगर (chunk && chunk->chunk_hdr &&
		    chunk->chunk_hdr->type == SCTP_CID_INIT)
			flags = 0;
		अन्यथा
			flags = SCTP_CHUNK_FLAG_T;
	पूर्ण

	retval = sctp_make_control(asoc, SCTP_CID_ABORT, flags, hपूर्णांक,
				   GFP_ATOMIC);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [ABORT back to where the offender came from.]
	 */
	अगर (retval && chunk)
		retval->transport = chunk->transport;

	वापस retval;
पूर्ण

/* Helper to create ABORT with a NO_USER_DATA error.  */
काष्ठा sctp_chunk *sctp_make_पात_no_data(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk,
					__u32 tsn)
अणु
	काष्ठा sctp_chunk *retval;
	__be32 payload;

	retval = sctp_make_पात(asoc, chunk,
				 माप(काष्ठा sctp_errhdr) + माप(tsn));

	अगर (!retval)
		जाओ no_mem;

	/* Put the tsn back पूर्णांकo network byte order.  */
	payload = htonl(tsn);
	sctp_init_cause(retval, SCTP_ERROR_NO_DATA, माप(payload));
	sctp_addto_chunk(retval, माप(payload), (स्थिर व्योम *)&payload);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [ABORT back to where the offender came from.]
	 */
	अगर (chunk)
		retval->transport = chunk->transport;

no_mem:
	वापस retval;
पूर्ण

/* Helper to create ABORT with a SCTP_ERROR_USER_ABORT error.  */
काष्ठा sctp_chunk *sctp_make_पात_user(स्थिर काष्ठा sctp_association *asoc,
					काष्ठा msghdr *msg,
					माप_प्रकार paylen)
अणु
	काष्ठा sctp_chunk *retval;
	व्योम *payload = शून्य;
	पूर्णांक err;

	retval = sctp_make_पात(asoc, शून्य,
				 माप(काष्ठा sctp_errhdr) + paylen);
	अगर (!retval)
		जाओ err_chunk;

	अगर (paylen) अणु
		/* Put the msg_iov together पूर्णांकo payload.  */
		payload = kदो_स्मृति(paylen, GFP_KERNEL);
		अगर (!payload)
			जाओ err_payload;

		err = स_नकल_from_msg(payload, msg, paylen);
		अगर (err < 0)
			जाओ err_copy;
	पूर्ण

	sctp_init_cause(retval, SCTP_ERROR_USER_ABORT, paylen);
	sctp_addto_chunk(retval, paylen, payload);

	अगर (paylen)
		kमुक्त(payload);

	वापस retval;

err_copy:
	kमुक्त(payload);
err_payload:
	sctp_chunk_मुक्त(retval);
	retval = शून्य;
err_chunk:
	वापस retval;
पूर्ण

/* Append bytes to the end of a parameter.  Will panic अगर chunk is not big
 * enough.
 */
अटल व्योम *sctp_addto_param(काष्ठा sctp_chunk *chunk, पूर्णांक len,
			      स्थिर व्योम *data)
अणु
	पूर्णांक chunklen = ntohs(chunk->chunk_hdr->length);
	व्योम *target;

	target = skb_put(chunk->skb, len);

	अगर (data)
		स_नकल(target, data, len);
	अन्यथा
		स_रखो(target, 0, len);

	/* Adjust the chunk length field.  */
	chunk->chunk_hdr->length = htons(chunklen + len);
	chunk->chunk_end = skb_tail_poपूर्णांकer(chunk->skb);

	वापस target;
पूर्ण

/* Make an ABORT chunk with a PROTOCOL VIOLATION cause code. */
काष्ठा sctp_chunk *sctp_make_पात_violation(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk,
					स्थिर __u8 *payload,
					स्थिर माप_प्रकार paylen)
अणु
	काष्ठा sctp_chunk  *retval;
	काष्ठा sctp_paramhdr phdr;

	retval = sctp_make_पात(asoc, chunk, माप(काष्ठा sctp_errhdr) +
					      paylen + माप(phdr));
	अगर (!retval)
		जाओ end;

	sctp_init_cause(retval, SCTP_ERROR_PROTO_VIOLATION, paylen +
							    माप(phdr));

	phdr.type = htons(chunk->chunk_hdr->type);
	phdr.length = chunk->chunk_hdr->length;
	sctp_addto_chunk(retval, paylen, payload);
	sctp_addto_param(retval, माप(phdr), &phdr);

end:
	वापस retval;
पूर्ण

काष्ठा sctp_chunk *sctp_make_violation_paramlen(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk,
					काष्ठा sctp_paramhdr *param)
अणु
	अटल स्थिर अक्षर error[] = "The following parameter had invalid length:";
	माप_प्रकार payload_len = माप(error) + माप(काष्ठा sctp_errhdr) +
			     माप(*param);
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_पात(asoc, chunk, payload_len);
	अगर (!retval)
		जाओ nodata;

	sctp_init_cause(retval, SCTP_ERROR_PROTO_VIOLATION,
			माप(error) + माप(*param));
	sctp_addto_chunk(retval, माप(error), error);
	sctp_addto_param(retval, माप(*param), param);

nodata:
	वापस retval;
पूर्ण

काष्ठा sctp_chunk *sctp_make_violation_max_retrans(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk)
अणु
	अटल स्थिर अक्षर error[] = "Association exceeded its max_retrans count";
	माप_प्रकार payload_len = माप(error) + माप(काष्ठा sctp_errhdr);
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_पात(asoc, chunk, payload_len);
	अगर (!retval)
		जाओ nodata;

	sctp_init_cause(retval, SCTP_ERROR_PROTO_VIOLATION, माप(error));
	sctp_addto_chunk(retval, माप(error), error);

nodata:
	वापस retval;
पूर्ण

काष्ठा sctp_chunk *sctp_make_new_encap_port(स्थिर काष्ठा sctp_association *asoc,
					    स्थिर काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_new_encap_port_hdr nep;
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_पात(asoc, chunk,
				 माप(काष्ठा sctp_errhdr) + माप(nep));
	अगर (!retval)
		जाओ nodata;

	sctp_init_cause(retval, SCTP_ERROR_NEW_ENCAP_PORT, माप(nep));
	nep.cur_port = SCTP_INPUT_CB(chunk->skb)->encap_port;
	nep.new_port = chunk->transport->encap_port;
	sctp_addto_chunk(retval, माप(nep), &nep);

nodata:
	वापस retval;
पूर्ण

/* Make a HEARTBEAT chunk.  */
काष्ठा sctp_chunk *sctp_make_heartbeat(स्थिर काष्ठा sctp_association *asoc,
				       स्थिर काष्ठा sctp_transport *transport)
अणु
	काष्ठा sctp_sender_hb_info hbinfo;
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_control(asoc, SCTP_CID_HEARTBEAT, 0,
				   माप(hbinfo), GFP_ATOMIC);

	अगर (!retval)
		जाओ nodata;

	hbinfo.param_hdr.type = SCTP_PARAM_HEARTBEAT_INFO;
	hbinfo.param_hdr.length = htons(माप(hbinfo));
	hbinfo.daddr = transport->ipaddr;
	hbinfo.sent_at = jअगरfies;
	hbinfo.hb_nonce = transport->hb_nonce;

	/* Cast away the 'const', as this is just telling the chunk
	 * what transport it beदीर्घs to.
	 */
	retval->transport = (काष्ठा sctp_transport *) transport;
	retval->subh.hbs_hdr = sctp_addto_chunk(retval, माप(hbinfo),
						&hbinfo);

nodata:
	वापस retval;
पूर्ण

काष्ठा sctp_chunk *sctp_make_heartbeat_ack(स्थिर काष्ठा sctp_association *asoc,
					   स्थिर काष्ठा sctp_chunk *chunk,
					   स्थिर व्योम *payload,
					   स्थिर माप_प्रकार paylen)
अणु
	काष्ठा sctp_chunk *retval;

	retval  = sctp_make_control(asoc, SCTP_CID_HEARTBEAT_ACK, 0, paylen,
				    GFP_ATOMIC);
	अगर (!retval)
		जाओ nodata;

	retval->subh.hbs_hdr = sctp_addto_chunk(retval, paylen, payload);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [HBACK back to where the HEARTBEAT came from.]
	 */
	अगर (chunk)
		retval->transport = chunk->transport;

nodata:
	वापस retval;
पूर्ण

/* Create an Operation Error chunk with the specअगरied space reserved.
 * This routine can be used क्रम containing multiple causes in the chunk.
 */
अटल काष्ठा sctp_chunk *sctp_make_op_error_space(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk,
					माप_प्रकार size)
अणु
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_control(asoc, SCTP_CID_ERROR, 0,
				   माप(काष्ठा sctp_errhdr) + size,
				   GFP_ATOMIC);
	अगर (!retval)
		जाओ nodata;

	/* RFC 2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
	 *
	 * An endpoपूर्णांक SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, etc.) to the same destination transport
	 * address from which it received the DATA or control chunk
	 * to which it is replying.
	 *
	 */
	अगर (chunk)
		retval->transport = chunk->transport;

nodata:
	वापस retval;
पूर्ण

/* Create an Operation Error chunk of a fixed size, specअगरically,
 * min(asoc->pathmtu, SCTP_DEFAULT_MAXSEGMENT) - overheads.
 * This is a helper function to allocate an error chunk क्रम those
 * invalid parameter codes in which we may not want to report all the
 * errors, अगर the incoming chunk is large. If it can't fit in a single
 * packet, we ignore it.
 */
अटल अंतरभूत काष्ठा sctp_chunk *sctp_make_op_error_limited(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk)
अणु
	माप_प्रकार size = SCTP_DEFAULT_MAXSEGMENT;
	काष्ठा sctp_sock *sp = शून्य;

	अगर (asoc) अणु
		size = min_t(माप_प्रकार, size, asoc->pathmtu);
		sp = sctp_sk(asoc->base.sk);
	पूर्ण

	size = sctp_mtu_payload(sp, size, माप(काष्ठा sctp_errhdr));

	वापस sctp_make_op_error_space(asoc, chunk, size);
पूर्ण

/* Create an Operation Error chunk.  */
काष्ठा sctp_chunk *sctp_make_op_error(स्थिर काष्ठा sctp_association *asoc,
				      स्थिर काष्ठा sctp_chunk *chunk,
				      __be16 cause_code, स्थिर व्योम *payload,
				      माप_प्रकार paylen, माप_प्रकार reserve_tail)
अणु
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_op_error_space(asoc, chunk, paylen + reserve_tail);
	अगर (!retval)
		जाओ nodata;

	sctp_init_cause(retval, cause_code, paylen + reserve_tail);
	sctp_addto_chunk(retval, paylen, payload);
	अगर (reserve_tail)
		sctp_addto_param(retval, reserve_tail, शून्य);

nodata:
	वापस retval;
पूर्ण

काष्ठा sctp_chunk *sctp_make_auth(स्थिर काष्ठा sctp_association *asoc,
				  __u16 key_id)
अणु
	काष्ठा sctp_authhdr auth_hdr;
	काष्ठा sctp_hmac *hmac_desc;
	काष्ठा sctp_chunk *retval;

	/* Get the first hmac that the peer told us to use */
	hmac_desc = sctp_auth_asoc_get_hmac(asoc);
	अगर (unlikely(!hmac_desc))
		वापस शून्य;

	retval = sctp_make_control(asoc, SCTP_CID_AUTH, 0,
				   hmac_desc->hmac_len + माप(auth_hdr),
				   GFP_ATOMIC);
	अगर (!retval)
		वापस शून्य;

	auth_hdr.hmac_id = htons(hmac_desc->hmac_id);
	auth_hdr.shkey_id = htons(key_id);

	retval->subh.auth_hdr = sctp_addto_chunk(retval, माप(auth_hdr),
						 &auth_hdr);

	skb_put_zero(retval->skb, hmac_desc->hmac_len);

	/* Adjust the chunk header to include the empty MAC */
	retval->chunk_hdr->length =
		htons(ntohs(retval->chunk_hdr->length) + hmac_desc->hmac_len);
	retval->chunk_end = skb_tail_poपूर्णांकer(retval->skb);

	वापस retval;
पूर्ण


/********************************************************************
 * 2nd Level Abstractions
 ********************************************************************/

/* Turn an skb पूर्णांकo a chunk.
 * FIXME: Eventually move the काष्ठाure directly inside the skb->cb[].
 *
 * sctpimpguide-05.txt Section 2.8.2
 * M1) Each समय a new DATA chunk is transmitted
 * set the 'TSN.Missing.Report' count क्रम that TSN to 0. The
 * 'TSN.Missing.Report' count will be used to determine missing chunks
 * and when to fast retransmit.
 *
 */
काष्ठा sctp_chunk *sctp_chunkअगरy(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा sctp_association *asoc,
				 काष्ठा sock *sk, gfp_t gfp)
अणु
	काष्ठा sctp_chunk *retval;

	retval = kmem_cache_zalloc(sctp_chunk_cachep, gfp);

	अगर (!retval)
		जाओ nodata;
	अगर (!sk)
		pr_debug("%s: chunkifying skb:%p w/o an sk\n", __func__, skb);

	INIT_LIST_HEAD(&retval->list);
	retval->skb		= skb;
	retval->asoc		= (काष्ठा sctp_association *)asoc;
	retval->singleton	= 1;

	retval->fast_retransmit = SCTP_CAN_FRTX;

	/* Polish the bead hole.  */
	INIT_LIST_HEAD(&retval->transmitted_list);
	INIT_LIST_HEAD(&retval->frag_list);
	SCTP_DBG_OBJCNT_INC(chunk);
	refcount_set(&retval->refcnt, 1);

nodata:
	वापस retval;
पूर्ण

/* Set chunk->source and dest based on the IP header in chunk->skb.  */
व्योम sctp_init_addrs(काष्ठा sctp_chunk *chunk, जोड़ sctp_addr *src,
		     जोड़ sctp_addr *dest)
अणु
	स_नकल(&chunk->source, src, माप(जोड़ sctp_addr));
	स_नकल(&chunk->dest, dest, माप(जोड़ sctp_addr));
पूर्ण

/* Extract the source address from a chunk.  */
स्थिर जोड़ sctp_addr *sctp_source(स्थिर काष्ठा sctp_chunk *chunk)
अणु
	/* If we have a known transport, use that.  */
	अगर (chunk->transport) अणु
		वापस &chunk->transport->ipaddr;
	पूर्ण अन्यथा अणु
		/* Otherwise, extract it from the IP header.  */
		वापस &chunk->source;
	पूर्ण
पूर्ण

/* Create a new chunk, setting the type and flags headers from the
 * arguments, reserving enough space क्रम a 'paylen' byte payload.
 */
अटल काष्ठा sctp_chunk *_sctp_make_chunk(स्थिर काष्ठा sctp_association *asoc,
					   __u8 type, __u8 flags, पूर्णांक paylen,
					   gfp_t gfp)
अणु
	काष्ठा sctp_chunkhdr *chunk_hdr;
	काष्ठा sctp_chunk *retval;
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk;
	पूर्णांक chunklen;

	chunklen = SCTP_PAD4(माप(*chunk_hdr) + paylen);
	अगर (chunklen > SCTP_MAX_CHUNK_LEN)
		जाओ nodata;

	/* No need to allocate LL here, as this is only a chunk. */
	skb = alloc_skb(chunklen, gfp);
	अगर (!skb)
		जाओ nodata;

	/* Make room क्रम the chunk header.  */
	chunk_hdr = (काष्ठा sctp_chunkhdr *)skb_put(skb, माप(*chunk_hdr));
	chunk_hdr->type	  = type;
	chunk_hdr->flags  = flags;
	chunk_hdr->length = htons(माप(*chunk_hdr));

	sk = asoc ? asoc->base.sk : शून्य;
	retval = sctp_chunkअगरy(skb, asoc, sk, gfp);
	अगर (!retval) अणु
		kमुक्त_skb(skb);
		जाओ nodata;
	पूर्ण

	retval->chunk_hdr = chunk_hdr;
	retval->chunk_end = ((__u8 *)chunk_hdr) + माप(*chunk_hdr);

	/* Determine अगर the chunk needs to be authenticated */
	अगर (sctp_auth_send_cid(type, asoc))
		retval->auth = 1;

	वापस retval;
nodata:
	वापस शून्य;
पूर्ण

अटल काष्ठा sctp_chunk *sctp_make_data(स्थिर काष्ठा sctp_association *asoc,
					 __u8 flags, पूर्णांक paylen, gfp_t gfp)
अणु
	वापस _sctp_make_chunk(asoc, SCTP_CID_DATA, flags, paylen, gfp);
पूर्ण

काष्ठा sctp_chunk *sctp_make_idata(स्थिर काष्ठा sctp_association *asoc,
				   __u8 flags, पूर्णांक paylen, gfp_t gfp)
अणु
	वापस _sctp_make_chunk(asoc, SCTP_CID_I_DATA, flags, paylen, gfp);
पूर्ण

अटल काष्ठा sctp_chunk *sctp_make_control(स्थिर काष्ठा sctp_association *asoc,
					    __u8 type, __u8 flags, पूर्णांक paylen,
					    gfp_t gfp)
अणु
	काष्ठा sctp_chunk *chunk;

	chunk = _sctp_make_chunk(asoc, type, flags, paylen, gfp);
	अगर (chunk)
		sctp_control_set_owner_w(chunk);

	वापस chunk;
पूर्ण

/* Release the memory occupied by a chunk.  */
अटल व्योम sctp_chunk_destroy(काष्ठा sctp_chunk *chunk)
अणु
	BUG_ON(!list_empty(&chunk->list));
	list_del_init(&chunk->transmitted_list);

	consume_skb(chunk->skb);
	consume_skb(chunk->auth_chunk);

	SCTP_DBG_OBJCNT_DEC(chunk);
	kmem_cache_मुक्त(sctp_chunk_cachep, chunk);
पूर्ण

/* Possibly, मुक्त the chunk.  */
व्योम sctp_chunk_मुक्त(काष्ठा sctp_chunk *chunk)
अणु
	/* Release our reference on the message tracker. */
	अगर (chunk->msg)
		sctp_datamsg_put(chunk->msg);

	sctp_chunk_put(chunk);
पूर्ण

/* Grab a reference to the chunk. */
व्योम sctp_chunk_hold(काष्ठा sctp_chunk *ch)
अणु
	refcount_inc(&ch->refcnt);
पूर्ण

/* Release a reference to the chunk. */
व्योम sctp_chunk_put(काष्ठा sctp_chunk *ch)
अणु
	अगर (refcount_dec_and_test(&ch->refcnt))
		sctp_chunk_destroy(ch);
पूर्ण

/* Append bytes to the end of a chunk.  Will panic अगर chunk is not big
 * enough.
 */
व्योम *sctp_addto_chunk(काष्ठा sctp_chunk *chunk, पूर्णांक len, स्थिर व्योम *data)
अणु
	पूर्णांक chunklen = ntohs(chunk->chunk_hdr->length);
	पूर्णांक padlen = SCTP_PAD4(chunklen) - chunklen;
	व्योम *target;

	skb_put_zero(chunk->skb, padlen);
	target = skb_put_data(chunk->skb, data, len);

	/* Adjust the chunk length field.  */
	chunk->chunk_hdr->length = htons(chunklen + padlen + len);
	chunk->chunk_end = skb_tail_poपूर्णांकer(chunk->skb);

	वापस target;
पूर्ण

/* Append bytes from user space to the end of a chunk.  Will panic अगर
 * chunk is not big enough.
 * Returns a kernel err value.
 */
पूर्णांक sctp_user_addto_chunk(काष्ठा sctp_chunk *chunk, पूर्णांक len,
			  काष्ठा iov_iter *from)
अणु
	व्योम *target;

	/* Make room in chunk क्रम data.  */
	target = skb_put(chunk->skb, len);

	/* Copy data (whole iovec) पूर्णांकo chunk */
	अगर (!copy_from_iter_full(target, len, from))
		वापस -EFAULT;

	/* Adjust the chunk length field.  */
	chunk->chunk_hdr->length =
		htons(ntohs(chunk->chunk_hdr->length) + len);
	chunk->chunk_end = skb_tail_poपूर्णांकer(chunk->skb);

	वापस 0;
पूर्ण

/* Helper function to assign a TSN अगर needed.  This assumes that both
 * the data_hdr and association have alपढ़ोy been asचिन्हित.
 */
व्योम sctp_chunk_assign_ssn(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_stream *stream;
	काष्ठा sctp_chunk *lchunk;
	काष्ठा sctp_datamsg *msg;
	__u16 ssn, sid;

	अगर (chunk->has_ssn)
		वापस;

	/* All fragments will be on the same stream */
	sid = ntohs(chunk->subh.data_hdr->stream);
	stream = &chunk->asoc->stream;

	/* Now assign the sequence number to the entire message.
	 * All fragments must have the same stream sequence number.
	 */
	msg = chunk->msg;
	list_क्रम_each_entry(lchunk, &msg->chunks, frag_list) अणु
		अगर (lchunk->chunk_hdr->flags & SCTP_DATA_UNORDERED) अणु
			ssn = 0;
		पूर्ण अन्यथा अणु
			अगर (lchunk->chunk_hdr->flags & SCTP_DATA_LAST_FRAG)
				ssn = sctp_ssn_next(stream, out, sid);
			अन्यथा
				ssn = sctp_ssn_peek(stream, out, sid);
		पूर्ण

		lchunk->subh.data_hdr->ssn = htons(ssn);
		lchunk->has_ssn = 1;
	पूर्ण
पूर्ण

/* Helper function to assign a TSN अगर needed.  This assumes that both
 * the data_hdr and association have alपढ़ोy been asचिन्हित.
 */
व्योम sctp_chunk_assign_tsn(काष्ठा sctp_chunk *chunk)
अणु
	अगर (!chunk->has_tsn) अणु
		/* This is the last possible instant to
		 * assign a TSN.
		 */
		chunk->subh.data_hdr->tsn =
			htonl(sctp_association_get_next_tsn(chunk->asoc));
		chunk->has_tsn = 1;
	पूर्ण
पूर्ण

/* Create a CLOSED association to use with an incoming packet.  */
काष्ठा sctp_association *sctp_make_temp_asoc(स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					     काष्ठा sctp_chunk *chunk,
					     gfp_t gfp)
अणु
	काष्ठा sctp_association *asoc;
	क्रमागत sctp_scope scope;
	काष्ठा sk_buff *skb;

	/* Create the bare association.  */
	scope = sctp_scope(sctp_source(chunk));
	asoc = sctp_association_new(ep, ep->base.sk, scope, gfp);
	अगर (!asoc)
		जाओ nodata;
	asoc->temp = 1;
	skb = chunk->skb;
	/* Create an entry क्रम the source address of the packet.  */
	SCTP_INPUT_CB(skb)->af->from_skb(&asoc->c.peer_addr, skb, 1);

nodata:
	वापस asoc;
पूर्ण

/* Build a cookie representing asoc.
 * This INCLUDES the param header needed to put the cookie in the INIT ACK.
 */
अटल काष्ठा sctp_cookie_param *sctp_pack_cookie(
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *init_chunk,
					पूर्णांक *cookie_len, स्थिर __u8 *raw_addrs,
					पूर्णांक addrs_len)
अणु
	काष्ठा sctp_चिन्हित_cookie *cookie;
	काष्ठा sctp_cookie_param *retval;
	पूर्णांक headersize, bodysize;

	/* Header size is अटल data prior to the actual cookie, including
	 * any padding.
	 */
	headersize = माप(काष्ठा sctp_paramhdr) +
		     (माप(काष्ठा sctp_चिन्हित_cookie) -
		      माप(काष्ठा sctp_cookie));
	bodysize = माप(काष्ठा sctp_cookie)
		+ ntohs(init_chunk->chunk_hdr->length) + addrs_len;

	/* Pad out the cookie to a multiple to make the signature
	 * functions simpler to ग_लिखो.
	 */
	अगर (bodysize % SCTP_COOKIE_MULTIPLE)
		bodysize += SCTP_COOKIE_MULTIPLE
			- (bodysize % SCTP_COOKIE_MULTIPLE);
	*cookie_len = headersize + bodysize;

	/* Clear this memory since we are sending this data काष्ठाure
	 * out on the network.
	 */
	retval = kzalloc(*cookie_len, GFP_ATOMIC);
	अगर (!retval)
		जाओ nodata;

	cookie = (काष्ठा sctp_चिन्हित_cookie *) retval->body;

	/* Set up the parameter header.  */
	retval->p.type = SCTP_PARAM_STATE_COOKIE;
	retval->p.length = htons(*cookie_len);

	/* Copy the cookie part of the association itself.  */
	cookie->c = asoc->c;
	/* Save the raw address list length in the cookie. */
	cookie->c.raw_addr_list_len = addrs_len;

	/* Remember PR-SCTP capability. */
	cookie->c.prsctp_capable = asoc->peer.prsctp_capable;

	/* Save adaptation indication in the cookie. */
	cookie->c.adaptation_ind = asoc->peer.adaptation_ind;

	/* Set an expiration समय क्रम the cookie.  */
	cookie->c.expiration = kसमय_add(asoc->cookie_lअगरe,
					 kसमय_get_real());

	/* Copy the peer's init packet.  */
	स_नकल(&cookie->c.peer_init[0], init_chunk->chunk_hdr,
	       ntohs(init_chunk->chunk_hdr->length));

	/* Copy the raw local address list of the association. */
	स_नकल((__u8 *)&cookie->c.peer_init[0] +
	       ntohs(init_chunk->chunk_hdr->length), raw_addrs, addrs_len);

	अगर (sctp_sk(ep->base.sk)->hmac) अणु
		काष्ठा crypto_shash *tfm = sctp_sk(ep->base.sk)->hmac;
		पूर्णांक err;

		/* Sign the message.  */
		err = crypto_shash_setkey(tfm, ep->secret_key,
					  माप(ep->secret_key)) ?:
		      crypto_shash_tfm_digest(tfm, (u8 *)&cookie->c, bodysize,
					      cookie->signature);
		अगर (err)
			जाओ मुक्त_cookie;
	पूर्ण

	वापस retval;

मुक्त_cookie:
	kमुक्त(retval);
nodata:
	*cookie_len = 0;
	वापस शून्य;
पूर्ण

/* Unpack the cookie from COOKIE ECHO chunk, recreating the association.  */
काष्ठा sctp_association *sctp_unpack_cookie(
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk, gfp_t gfp,
					पूर्णांक *error, काष्ठा sctp_chunk **errp)
अणु
	काष्ठा sctp_association *retval = शून्य;
	पूर्णांक headersize, bodysize, fixed_size;
	काष्ठा sctp_चिन्हित_cookie *cookie;
	काष्ठा sk_buff *skb = chunk->skb;
	काष्ठा sctp_cookie *bear_cookie;
	__u8 *digest = ep->digest;
	क्रमागत sctp_scope scope;
	अचिन्हित पूर्णांक len;
	kसमय_प्रकार kt;

	/* Header size is अटल data prior to the actual cookie, including
	 * any padding.
	 */
	headersize = माप(काष्ठा sctp_chunkhdr) +
		     (माप(काष्ठा sctp_चिन्हित_cookie) -
		      माप(काष्ठा sctp_cookie));
	bodysize = ntohs(chunk->chunk_hdr->length) - headersize;
	fixed_size = headersize + माप(काष्ठा sctp_cookie);

	/* Verअगरy that the chunk looks like it even has a cookie.
	 * There must be enough room क्रम our cookie and our peer's
	 * INIT chunk.
	 */
	len = ntohs(chunk->chunk_hdr->length);
	अगर (len < fixed_size + माप(काष्ठा sctp_chunkhdr))
		जाओ malक्रमmed;

	/* Verअगरy that the cookie has been padded out. */
	अगर (bodysize % SCTP_COOKIE_MULTIPLE)
		जाओ malक्रमmed;

	/* Process the cookie.  */
	cookie = chunk->subh.cookie_hdr;
	bear_cookie = &cookie->c;

	अगर (!sctp_sk(ep->base.sk)->hmac)
		जाओ no_hmac;

	/* Check the signature.  */
	अणु
		काष्ठा crypto_shash *tfm = sctp_sk(ep->base.sk)->hmac;
		पूर्णांक err;

		err = crypto_shash_setkey(tfm, ep->secret_key,
					  माप(ep->secret_key)) ?:
		      crypto_shash_tfm_digest(tfm, (u8 *)bear_cookie, bodysize,
					      digest);
		अगर (err) अणु
			*error = -SCTP_IERROR_NOMEM;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (स_भेद(digest, cookie->signature, SCTP_SIGNATURE_SIZE)) अणु
		*error = -SCTP_IERROR_BAD_SIG;
		जाओ fail;
	पूर्ण

no_hmac:
	/* IG Section 2.35.2:
	 *  3) Compare the port numbers and the verअगरication tag contained
	 *     within the COOKIE ECHO chunk to the actual port numbers and the
	 *     verअगरication tag within the SCTP common header of the received
	 *     packet. If these values करो not match the packet MUST be silently
	 *     discarded,
	 */
	अगर (ntohl(chunk->sctp_hdr->vtag) != bear_cookie->my_vtag) अणु
		*error = -SCTP_IERROR_BAD_TAG;
		जाओ fail;
	पूर्ण

	अगर (chunk->sctp_hdr->source != bear_cookie->peer_addr.v4.sin_port ||
	    ntohs(chunk->sctp_hdr->dest) != bear_cookie->my_port) अणु
		*error = -SCTP_IERROR_BAD_PORTS;
		जाओ fail;
	पूर्ण

	/* Check to see अगर the cookie is stale.  If there is alपढ़ोy
	 * an association, there is no need to check cookie's expiration
	 * क्रम init collision हाल of lost COOKIE ACK.
	 * If skb has been बारtamped, then use the stamp, otherwise
	 * use current समय.  This पूर्णांकroduces a small possibility that
	 * a cookie may be considered expired, but this would only slow
	 * करोwn the new association establishment instead of every packet.
	 */
	अगर (sock_flag(ep->base.sk, SOCK_TIMESTAMP))
		kt = skb_get_kसमय(skb);
	अन्यथा
		kt = kसमय_get_real();

	अगर (!asoc && kसमय_beक्रमe(bear_cookie->expiration, kt)) अणु
		suseconds_t usecs = kसमय_प्रकारo_us(kसमय_sub(kt, bear_cookie->expiration));
		__be32 n = htonl(usecs);

		/*
		 * Section 3.3.10.3 Stale Cookie Error (3)
		 *
		 * Cause of error
		 * ---------------
		 * Stale Cookie Error:  Indicates the receipt of a valid State
		 * Cookie that has expired.
		 */
		*errp = sctp_make_op_error(asoc, chunk,
					   SCTP_ERROR_STALE_COOKIE, &n,
					   माप(n), 0);
		अगर (*errp)
			*error = -SCTP_IERROR_STALE_COOKIE;
		अन्यथा
			*error = -SCTP_IERROR_NOMEM;

		जाओ fail;
	पूर्ण

	/* Make a new base association.  */
	scope = sctp_scope(sctp_source(chunk));
	retval = sctp_association_new(ep, ep->base.sk, scope, gfp);
	अगर (!retval) अणु
		*error = -SCTP_IERROR_NOMEM;
		जाओ fail;
	पूर्ण

	/* Set up our peer's port number.  */
	retval->peer.port = ntohs(chunk->sctp_hdr->source);

	/* Populate the association from the cookie.  */
	स_नकल(&retval->c, bear_cookie, माप(*bear_cookie));

	अगर (sctp_assoc_set_bind_addr_from_cookie(retval, bear_cookie,
						 GFP_ATOMIC) < 0) अणु
		*error = -SCTP_IERROR_NOMEM;
		जाओ fail;
	पूर्ण

	/* Also, add the destination address. */
	अगर (list_empty(&retval->base.bind_addr.address_list)) अणु
		sctp_add_bind_addr(&retval->base.bind_addr, &chunk->dest,
				   माप(chunk->dest), SCTP_ADDR_SRC,
				   GFP_ATOMIC);
	पूर्ण

	retval->next_tsn = retval->c.initial_tsn;
	retval->ctsn_ack_poपूर्णांक = retval->next_tsn - 1;
	retval->addip_serial = retval->c.initial_tsn;
	retval->strreset_outseq = retval->c.initial_tsn;
	retval->adv_peer_ack_poपूर्णांक = retval->ctsn_ack_poपूर्णांक;
	retval->peer.prsctp_capable = retval->c.prsctp_capable;
	retval->peer.adaptation_ind = retval->c.adaptation_ind;

	/* The INIT stuff will be करोne by the side effects.  */
	वापस retval;

fail:
	अगर (retval)
		sctp_association_मुक्त(retval);

	वापस शून्य;

malक्रमmed:
	/* Yikes!  The packet is either corrupt or deliberately
	 * malक्रमmed.
	 */
	*error = -SCTP_IERROR_MALFORMED;
	जाओ fail;
पूर्ण

/********************************************************************
 * 3rd Level Abstractions
 ********************************************************************/

काष्ठा __sctp_missing अणु
	__be32 num_missing;
	__be16 type;
पूर्ण  __packed;

/*
 * Report a missing mandatory parameter.
 */
अटल पूर्णांक sctp_process_missing_param(स्थिर काष्ठा sctp_association *asoc,
				      क्रमागत sctp_param paramtype,
				      काष्ठा sctp_chunk *chunk,
				      काष्ठा sctp_chunk **errp)
अणु
	काष्ठा __sctp_missing report;
	__u16 len;

	len = SCTP_PAD4(माप(report));

	/* Make an ERROR chunk, preparing enough room क्रम
	 * वापसing multiple unknown parameters.
	 */
	अगर (!*errp)
		*errp = sctp_make_op_error_space(asoc, chunk, len);

	अगर (*errp) अणु
		report.num_missing = htonl(1);
		report.type = paramtype;
		sctp_init_cause(*errp, SCTP_ERROR_MISS_PARAM,
				माप(report));
		sctp_addto_chunk(*errp, माप(report), &report);
	पूर्ण

	/* Stop processing this chunk. */
	वापस 0;
पूर्ण

/* Report an Invalid Mandatory Parameter.  */
अटल पूर्णांक sctp_process_inv_mandatory(स्थिर काष्ठा sctp_association *asoc,
				      काष्ठा sctp_chunk *chunk,
				      काष्ठा sctp_chunk **errp)
अणु
	/* Invalid Mandatory Parameter Error has no payload. */

	अगर (!*errp)
		*errp = sctp_make_op_error_space(asoc, chunk, 0);

	अगर (*errp)
		sctp_init_cause(*errp, SCTP_ERROR_INV_PARAM, 0);

	/* Stop processing this chunk. */
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_process_inv_paramlength(स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_paramhdr *param,
					स्थिर काष्ठा sctp_chunk *chunk,
					काष्ठा sctp_chunk **errp)
अणु
	/* This is a fatal error.  Any accumulated non-fatal errors are
	 * not reported.
	 */
	अगर (*errp)
		sctp_chunk_मुक्त(*errp);

	/* Create an error chunk and fill it in with our payload. */
	*errp = sctp_make_violation_paramlen(asoc, chunk, param);

	वापस 0;
पूर्ण


/* Do not attempt to handle the HOST_NAME parm.  However, करो
 * send back an indicator to the peer.
 */
अटल पूर्णांक sctp_process_hn_param(स्थिर काष्ठा sctp_association *asoc,
				 जोड़ sctp_params param,
				 काष्ठा sctp_chunk *chunk,
				 काष्ठा sctp_chunk **errp)
अणु
	__u16 len = ntohs(param.p->length);

	/* Processing of the HOST_NAME parameter will generate an
	 * ABORT.  If we've accumulated any non-fatal errors, they
	 * would be unrecognized parameters and we should not include
	 * them in the ABORT.
	 */
	अगर (*errp)
		sctp_chunk_मुक्त(*errp);

	*errp = sctp_make_op_error(asoc, chunk, SCTP_ERROR_DNS_FAILED,
				   param.v, len, 0);

	/* Stop processing this chunk. */
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_verअगरy_ext_param(काष्ठा net *net,
				 स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
				 जोड़ sctp_params param)
अणु
	__u16 num_ext = ntohs(param.p->length) - माप(काष्ठा sctp_paramhdr);
	पूर्णांक have_asconf = 0;
	पूर्णांक have_auth = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num_ext; i++) अणु
		चयन (param.ext->chunks[i]) अणु
		हाल SCTP_CID_AUTH:
			have_auth = 1;
			अवरोध;
		हाल SCTP_CID_ASCONF:
		हाल SCTP_CID_ASCONF_ACK:
			have_asconf = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* ADD-IP Security: The draft requires us to ABORT or ignore the
	 * INIT/INIT-ACK अगर ADD-IP is listed, but AUTH is not.  Do this
	 * only अगर ADD-IP is turned on and we are not backward-compatible
	 * mode.
	 */
	अगर (net->sctp.addip_noauth)
		वापस 1;

	अगर (ep->asconf_enable && !have_auth && have_asconf)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम sctp_process_ext_param(काष्ठा sctp_association *asoc,
				   जोड़ sctp_params param)
अणु
	__u16 num_ext = ntohs(param.p->length) - माप(काष्ठा sctp_paramhdr);
	पूर्णांक i;

	क्रम (i = 0; i < num_ext; i++) अणु
		चयन (param.ext->chunks[i]) अणु
		हाल SCTP_CID_RECONF:
			अगर (asoc->ep->reconf_enable)
				asoc->peer.reconf_capable = 1;
			अवरोध;
		हाल SCTP_CID_FWD_TSN:
			अगर (asoc->ep->prsctp_enable)
				asoc->peer.prsctp_capable = 1;
			अवरोध;
		हाल SCTP_CID_AUTH:
			/* अगर the peer reports AUTH, assume that he
			 * supports AUTH.
			 */
			अगर (asoc->ep->auth_enable)
				asoc->peer.auth_capable = 1;
			अवरोध;
		हाल SCTP_CID_ASCONF:
		हाल SCTP_CID_ASCONF_ACK:
			अगर (asoc->ep->asconf_enable)
				asoc->peer.asconf_capable = 1;
			अवरोध;
		हाल SCTP_CID_I_DATA:
			अगर (asoc->ep->पूर्णांकl_enable)
				asoc->peer.पूर्णांकl_capable = 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* RFC 3.2.1 & the Implementers Guide 2.2.
 *
 * The Parameter Types are encoded such that the
 * highest-order two bits specअगरy the action that must be
 * taken अगर the processing endpoपूर्णांक करोes not recognize the
 * Parameter Type.
 *
 * 00 - Stop processing this parameter; करो not process any further
 * 	parameters within this chunk
 *
 * 01 - Stop processing this parameter, करो not process any further
 *	parameters within this chunk, and report the unrecognized
 *	parameter in an 'Unrecognized Parameter' ERROR chunk.
 *
 * 10 - Skip this parameter and जारी processing.
 *
 * 11 - Skip this parameter and जारी processing but
 *	report the unrecognized parameter in an
 *	'Unrecognized Parameter' ERROR chunk.
 *
 * Return value:
 * 	SCTP_IERROR_NO_ERROR - जारी with the chunk
 * 	SCTP_IERROR_ERROR    - stop and report an error.
 * 	SCTP_IERROR_NOMEME   - out of memory.
 */
अटल क्रमागत sctp_ierror sctp_process_unk_param(
					स्थिर काष्ठा sctp_association *asoc,
					जोड़ sctp_params param,
					काष्ठा sctp_chunk *chunk,
					काष्ठा sctp_chunk **errp)
अणु
	पूर्णांक retval = SCTP_IERROR_NO_ERROR;

	चयन (param.p->type & SCTP_PARAM_ACTION_MASK) अणु
	हाल SCTP_PARAM_ACTION_DISCARD:
		retval =  SCTP_IERROR_ERROR;
		अवरोध;
	हाल SCTP_PARAM_ACTION_SKIP:
		अवरोध;
	हाल SCTP_PARAM_ACTION_DISCARD_ERR:
		retval =  SCTP_IERROR_ERROR;
		fallthrough;
	हाल SCTP_PARAM_ACTION_SKIP_ERR:
		/* Make an ERROR chunk, preparing enough room क्रम
		 * वापसing multiple unknown parameters.
		 */
		अगर (!*errp) अणु
			*errp = sctp_make_op_error_limited(asoc, chunk);
			अगर (!*errp) अणु
				/* If there is no memory क्रम generating the
				 * ERROR report as specअगरied, an ABORT will be
				 * triggered to the peer and the association
				 * won't be established.
				 */
				retval = SCTP_IERROR_NOMEM;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!sctp_init_cause(*errp, SCTP_ERROR_UNKNOWN_PARAM,
				     ntohs(param.p->length)))
			sctp_addto_chunk(*errp, ntohs(param.p->length),
					 param.v);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

/* Verअगरy variable length parameters
 * Return values:
 * 	SCTP_IERROR_ABORT - trigger an ABORT
 * 	SCTP_IERROR_NOMEM - out of memory (पात)
 *	SCTP_IERROR_ERROR - stop processing, trigger an ERROR
 * 	SCTP_IERROR_NO_ERROR - जारी with the chunk
 */
अटल क्रमागत sctp_ierror sctp_verअगरy_param(काष्ठा net *net,
					  स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					  स्थिर काष्ठा sctp_association *asoc,
					  जोड़ sctp_params param,
					  क्रमागत sctp_cid cid,
					  काष्ठा sctp_chunk *chunk,
					  काष्ठा sctp_chunk **err_chunk)
अणु
	काष्ठा sctp_hmac_algo_param *hmacs;
	पूर्णांक retval = SCTP_IERROR_NO_ERROR;
	__u16 n_elt, id = 0;
	पूर्णांक i;

	/* FIXME - This routine is not looking at each parameter per the
	 * chunk type, i.e., unrecognized parameters should be further
	 * identअगरied based on the chunk id.
	 */

	चयन (param.p->type) अणु
	हाल SCTP_PARAM_IPV4_ADDRESS:
	हाल SCTP_PARAM_IPV6_ADDRESS:
	हाल SCTP_PARAM_COOKIE_PRESERVATIVE:
	हाल SCTP_PARAM_SUPPORTED_ADDRESS_TYPES:
	हाल SCTP_PARAM_STATE_COOKIE:
	हाल SCTP_PARAM_HEARTBEAT_INFO:
	हाल SCTP_PARAM_UNRECOGNIZED_PARAMETERS:
	हाल SCTP_PARAM_ECN_CAPABLE:
	हाल SCTP_PARAM_ADAPTATION_LAYER_IND:
		अवरोध;

	हाल SCTP_PARAM_SUPPORTED_EXT:
		अगर (!sctp_verअगरy_ext_param(net, ep, param))
			वापस SCTP_IERROR_ABORT;
		अवरोध;

	हाल SCTP_PARAM_SET_PRIMARY:
		अगर (ep->asconf_enable)
			अवरोध;
		जाओ unhandled;

	हाल SCTP_PARAM_HOST_NAME_ADDRESS:
		/* Tell the peer, we won't support this param.  */
		sctp_process_hn_param(asoc, param, chunk, err_chunk);
		retval = SCTP_IERROR_ABORT;
		अवरोध;

	हाल SCTP_PARAM_FWD_TSN_SUPPORT:
		अगर (ep->prsctp_enable)
			अवरोध;
		जाओ unhandled;

	हाल SCTP_PARAM_RANDOM:
		अगर (!ep->auth_enable)
			जाओ unhandled;

		/* SCTP-AUTH: Secion 6.1
		 * If the अक्रमom number is not 32 byte दीर्घ the association
		 * MUST be पातed.  The ABORT chunk SHOULD contain the error
		 * cause 'Protocol Violation'.
		 */
		अगर (SCTP_AUTH_RANDOM_LENGTH != ntohs(param.p->length) -
					       माप(काष्ठा sctp_paramhdr)) अणु
			sctp_process_inv_paramlength(asoc, param.p,
						     chunk, err_chunk);
			retval = SCTP_IERROR_ABORT;
		पूर्ण
		अवरोध;

	हाल SCTP_PARAM_CHUNKS:
		अगर (!ep->auth_enable)
			जाओ unhandled;

		/* SCTP-AUTH: Section 3.2
		 * The CHUNKS parameter MUST be included once in the INIT or
		 *  INIT-ACK chunk अगर the sender wants to receive authenticated
		 *  chunks.  Its maximum length is 260 bytes.
		 */
		अगर (260 < ntohs(param.p->length)) अणु
			sctp_process_inv_paramlength(asoc, param.p,
						     chunk, err_chunk);
			retval = SCTP_IERROR_ABORT;
		पूर्ण
		अवरोध;

	हाल SCTP_PARAM_HMAC_ALGO:
		अगर (!ep->auth_enable)
			जाओ unhandled;

		hmacs = (काष्ठा sctp_hmac_algo_param *)param.p;
		n_elt = (ntohs(param.p->length) -
			 माप(काष्ठा sctp_paramhdr)) >> 1;

		/* SCTP-AUTH: Section 6.1
		 * The HMAC algorithm based on SHA-1 MUST be supported and
		 * included in the HMAC-ALGO parameter.
		 */
		क्रम (i = 0; i < n_elt; i++) अणु
			id = ntohs(hmacs->hmac_ids[i]);

			अगर (id == SCTP_AUTH_HMAC_ID_SHA1)
				अवरोध;
		पूर्ण

		अगर (id != SCTP_AUTH_HMAC_ID_SHA1) अणु
			sctp_process_inv_paramlength(asoc, param.p, chunk,
						     err_chunk);
			retval = SCTP_IERROR_ABORT;
		पूर्ण
		अवरोध;
unhandled:
	शेष:
		pr_debug("%s: unrecognized param:%d for chunk:%d\n",
			 __func__, ntohs(param.p->type), cid);

		retval = sctp_process_unk_param(asoc, param, chunk, err_chunk);
		अवरोध;
	पूर्ण
	वापस retval;
पूर्ण

/* Verअगरy the INIT packet beक्रमe we process it.  */
पूर्णांक sctp_verअगरy_init(काष्ठा net *net, स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
		     स्थिर काष्ठा sctp_association *asoc, क्रमागत sctp_cid cid,
		     काष्ठा sctp_init_chunk *peer_init,
		     काष्ठा sctp_chunk *chunk, काष्ठा sctp_chunk **errp)
अणु
	जोड़ sctp_params param;
	bool has_cookie = false;
	पूर्णांक result;

	/* Check क्रम missing mandatory parameters. Note: Initial TSN is
	 * also mandatory, but is not checked here since the valid range
	 * is 0..2**32-1. RFC4960, section 3.3.3.
	 */
	अगर (peer_init->init_hdr.num_outbound_streams == 0 ||
	    peer_init->init_hdr.num_inbound_streams == 0 ||
	    peer_init->init_hdr.init_tag == 0 ||
	    ntohl(peer_init->init_hdr.a_rwnd) < SCTP_DEFAULT_MINWINDOW)
		वापस sctp_process_inv_mandatory(asoc, chunk, errp);

	sctp_walk_params(param, peer_init, init_hdr.params) अणु
		अगर (param.p->type == SCTP_PARAM_STATE_COOKIE)
			has_cookie = true;
	पूर्ण

	/* There is a possibility that a parameter length was bad and
	 * in that हाल we would have stoped walking the parameters.
	 * The current param.p would poपूर्णांक at the bad one.
	 * Current consensus on the mailing list is to generate a PROTOCOL
	 * VIOLATION error.  We build the ERROR chunk here and let the normal
	 * error handling code build and send the packet.
	 */
	अगर (param.v != (व्योम *)chunk->chunk_end)
		वापस sctp_process_inv_paramlength(asoc, param.p, chunk, errp);

	/* The only missing mandatory param possible today is
	 * the state cookie क्रम an INIT-ACK chunk.
	 */
	अगर ((SCTP_CID_INIT_ACK == cid) && !has_cookie)
		वापस sctp_process_missing_param(asoc, SCTP_PARAM_STATE_COOKIE,
						  chunk, errp);

	/* Verअगरy all the variable length parameters */
	sctp_walk_params(param, peer_init, init_hdr.params) अणु
		result = sctp_verअगरy_param(net, ep, asoc, param, cid,
					   chunk, errp);
		चयन (result) अणु
		हाल SCTP_IERROR_ABORT:
		हाल SCTP_IERROR_NOMEM:
			वापस 0;
		हाल SCTP_IERROR_ERROR:
			वापस 1;
		हाल SCTP_IERROR_NO_ERROR:
		शेष:
			अवरोध;
		पूर्ण

	पूर्ण /* क्रम (loop through all parameters) */

	वापस 1;
पूर्ण

/* Unpack the parameters in an INIT packet पूर्णांकo an association.
 * Returns 0 on failure, अन्यथा success.
 * FIXME:  This is an association method.
 */
पूर्णांक sctp_process_init(काष्ठा sctp_association *asoc, काष्ठा sctp_chunk *chunk,
		      स्थिर जोड़ sctp_addr *peer_addr,
		      काष्ठा sctp_init_chunk *peer_init, gfp_t gfp)
अणु
	काष्ठा sctp_transport *transport;
	काष्ठा list_head *pos, *temp;
	जोड़ sctp_params param;
	जोड़ sctp_addr addr;
	काष्ठा sctp_af *af;
	पूर्णांक src_match = 0;

	/* We must include the address that the INIT packet came from.
	 * This is the only address that matters क्रम an INIT packet.
	 * When processing a COOKIE ECHO, we retrieve the from address
	 * of the INIT from the cookie.
	 */

	/* This implementation शेषs to making the first transport
	 * added as the primary transport.  The source address seems to
	 * be a better choice than any of the embedded addresses.
	 */
	asoc->encap_port = SCTP_INPUT_CB(chunk->skb)->encap_port;
	अगर (!sctp_assoc_add_peer(asoc, peer_addr, gfp, SCTP_ACTIVE))
		जाओ nomem;

	अगर (sctp_cmp_addr_exact(sctp_source(chunk), peer_addr))
		src_match = 1;

	/* Process the initialization parameters.  */
	sctp_walk_params(param, peer_init, init_hdr.params) अणु
		अगर (!src_match && (param.p->type == SCTP_PARAM_IPV4_ADDRESS ||
		    param.p->type == SCTP_PARAM_IPV6_ADDRESS)) अणु
			af = sctp_get_af_specअगरic(param_type2af(param.p->type));
			af->from_addr_param(&addr, param.addr,
					    chunk->sctp_hdr->source, 0);
			अगर (sctp_cmp_addr_exact(sctp_source(chunk), &addr))
				src_match = 1;
		पूर्ण

		अगर (!sctp_process_param(asoc, param, peer_addr, gfp))
			जाओ clean_up;
	पूर्ण

	/* source address of chunk may not match any valid address */
	अगर (!src_match)
		जाओ clean_up;

	/* AUTH: After processing the parameters, make sure that we
	 * have all the required info to potentially करो authentications.
	 */
	अगर (asoc->peer.auth_capable && (!asoc->peer.peer_अक्रमom ||
					!asoc->peer.peer_hmacs))
		asoc->peer.auth_capable = 0;

	/* In a non-backward compatible mode, अगर the peer claims
	 * support क्रम ADD-IP but not AUTH,  the ADD-IP spec states
	 * that we MUST ABORT the association. Section 6.  The section
	 * also give us an option to silently ignore the packet, which
	 * is what we'll करो here.
	 */
	अगर (!asoc->base.net->sctp.addip_noauth &&
	    (asoc->peer.asconf_capable && !asoc->peer.auth_capable)) अणु
		asoc->peer.addip_disabled_mask |= (SCTP_PARAM_ADD_IP |
						  SCTP_PARAM_DEL_IP |
						  SCTP_PARAM_SET_PRIMARY);
		asoc->peer.asconf_capable = 0;
		जाओ clean_up;
	पूर्ण

	/* Walk list of transports, removing transports in the UNKNOWN state. */
	list_क्रम_each_safe(pos, temp, &asoc->peer.transport_addr_list) अणु
		transport = list_entry(pos, काष्ठा sctp_transport, transports);
		अगर (transport->state == SCTP_UNKNOWN) अणु
			sctp_assoc_rm_peer(asoc, transport);
		पूर्ण
	पूर्ण

	/* The fixed INIT headers are always in network byte
	 * order.
	 */
	asoc->peer.i.init_tag =
		ntohl(peer_init->init_hdr.init_tag);
	asoc->peer.i.a_rwnd =
		ntohl(peer_init->init_hdr.a_rwnd);
	asoc->peer.i.num_outbound_streams =
		ntohs(peer_init->init_hdr.num_outbound_streams);
	asoc->peer.i.num_inbound_streams =
		ntohs(peer_init->init_hdr.num_inbound_streams);
	asoc->peer.i.initial_tsn =
		ntohl(peer_init->init_hdr.initial_tsn);

	asoc->strreset_inseq = asoc->peer.i.initial_tsn;

	/* Apply the upper bounds क्रम output streams based on peer's
	 * number of inbound streams.
	 */
	अगर (asoc->c.sinit_num_ostreams  >
	    ntohs(peer_init->init_hdr.num_inbound_streams)) अणु
		asoc->c.sinit_num_ostreams =
			ntohs(peer_init->init_hdr.num_inbound_streams);
	पूर्ण

	अगर (asoc->c.sinit_max_instreams >
	    ntohs(peer_init->init_hdr.num_outbound_streams)) अणु
		asoc->c.sinit_max_instreams =
			ntohs(peer_init->init_hdr.num_outbound_streams);
	पूर्ण

	/* Copy Initiation tag from INIT to VT_peer in cookie.   */
	asoc->c.peer_vtag = asoc->peer.i.init_tag;

	/* Peer Rwnd   : Current calculated value of the peer's rwnd.  */
	asoc->peer.rwnd = asoc->peer.i.a_rwnd;

	/* RFC 2960 7.2.1 The initial value of ssthresh MAY be arbitrarily
	 * high (क्रम example, implementations MAY use the size of the receiver
	 * advertised winकरोw).
	 */
	list_क्रम_each_entry(transport, &asoc->peer.transport_addr_list,
			transports) अणु
		transport->ssthresh = asoc->peer.i.a_rwnd;
	पूर्ण

	/* Set up the TSN tracking pieces.  */
	अगर (!sctp_tsnmap_init(&asoc->peer.tsn_map, SCTP_TSN_MAP_INITIAL,
				asoc->peer.i.initial_tsn, gfp))
		जाओ clean_up;

	/* RFC 2960 6.5 Stream Identअगरier and Stream Sequence Number
	 *
	 * The stream sequence number in all the streams shall start
	 * from 0 when the association is established.  Also, when the
	 * stream sequence number reaches the value 65535 the next
	 * stream sequence number shall be set to 0.
	 */

	अगर (sctp_stream_init(&asoc->stream, asoc->c.sinit_num_ostreams,
			     asoc->c.sinit_max_instreams, gfp))
		जाओ clean_up;

	/* Update frag_poपूर्णांक when stream_पूर्णांकerleave may get changed. */
	sctp_assoc_update_frag_poपूर्णांक(asoc);

	अगर (!asoc->temp && sctp_assoc_set_id(asoc, gfp))
		जाओ clean_up;

	/* ADDIP Section 4.1 ASCONF Chunk Procedures
	 *
	 * When an endpoपूर्णांक has an ASCONF संकेतed change to be sent to the
	 * remote endpoपूर्णांक it should करो the following:
	 * ...
	 * A2) A serial number should be asचिन्हित to the Chunk. The serial
	 * number should be a monotonically increasing number. All serial
	 * numbers are defined to be initialized at the start of the
	 * association to the same value as the Initial TSN.
	 */
	asoc->peer.addip_serial = asoc->peer.i.initial_tsn - 1;
	वापस 1;

clean_up:
	/* Release the transport काष्ठाures. */
	list_क्रम_each_safe(pos, temp, &asoc->peer.transport_addr_list) अणु
		transport = list_entry(pos, काष्ठा sctp_transport, transports);
		अगर (transport->state != SCTP_ACTIVE)
			sctp_assoc_rm_peer(asoc, transport);
	पूर्ण

nomem:
	वापस 0;
पूर्ण


/* Update asoc with the option described in param.
 *
 * RFC2960 3.3.2.1 Optional/Variable Length Parameters in INIT
 *
 * asoc is the association to update.
 * param is the variable length parameter to use क्रम update.
 * cid tells us अगर this is an INIT, INIT ACK or COOKIE ECHO.
 * If the current packet is an INIT we want to minimize the amount of
 * work we करो.  In particular, we should not build transport
 * काष्ठाures क्रम the addresses.
 */
अटल पूर्णांक sctp_process_param(काष्ठा sctp_association *asoc,
			      जोड़ sctp_params param,
			      स्थिर जोड़ sctp_addr *peer_addr,
			      gfp_t gfp)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep = asoc->ep;
	जोड़ sctp_addr_param *addr_param;
	काष्ठा net *net = asoc->base.net;
	काष्ठा sctp_transport *t;
	क्रमागत sctp_scope scope;
	जोड़ sctp_addr addr;
	काष्ठा sctp_af *af;
	पूर्णांक retval = 1, i;
	u32 stale;
	__u16 sat;

	/* We मुख्यtain all INIT parameters in network byte order all the
	 * समय.  This allows us to not worry about whether the parameters
	 * came from a fresh INIT, and INIT ACK, or were stored in a cookie.
	 */
	चयन (param.p->type) अणु
	हाल SCTP_PARAM_IPV6_ADDRESS:
		अगर (PF_INET6 != asoc->base.sk->sk_family)
			अवरोध;
		जाओ करो_addr_param;

	हाल SCTP_PARAM_IPV4_ADDRESS:
		/* v4 addresses are not allowed on v6-only socket */
		अगर (ipv6_only_sock(asoc->base.sk))
			अवरोध;
करो_addr_param:
		af = sctp_get_af_specअगरic(param_type2af(param.p->type));
		af->from_addr_param(&addr, param.addr, htons(asoc->peer.port), 0);
		scope = sctp_scope(peer_addr);
		अगर (sctp_in_scope(net, &addr, scope))
			अगर (!sctp_assoc_add_peer(asoc, &addr, gfp, SCTP_UNCONFIRMED))
				वापस 0;
		अवरोध;

	हाल SCTP_PARAM_COOKIE_PRESERVATIVE:
		अगर (!net->sctp.cookie_preserve_enable)
			अवरोध;

		stale = ntohl(param.lअगरe->lअगरespan_increment);

		/* Suggested Cookie Lअगरe span increment's unit is msec,
		 * (1/1000sec).
		 */
		asoc->cookie_lअगरe = kसमय_add_ms(asoc->cookie_lअगरe, stale);
		अवरोध;

	हाल SCTP_PARAM_HOST_NAME_ADDRESS:
		pr_debug("%s: unimplemented SCTP_HOST_NAME_ADDRESS\n", __func__);
		अवरोध;

	हाल SCTP_PARAM_SUPPORTED_ADDRESS_TYPES:
		/* Turn off the शेष values first so we'll know which
		 * ones are really set by the peer.
		 */
		asoc->peer.ipv4_address = 0;
		asoc->peer.ipv6_address = 0;

		/* Assume that peer supports the address family
		 * by which it sends a packet.
		 */
		अगर (peer_addr->sa.sa_family == AF_INET6)
			asoc->peer.ipv6_address = 1;
		अन्यथा अगर (peer_addr->sa.sa_family == AF_INET)
			asoc->peer.ipv4_address = 1;

		/* Cycle through address types; aव्योम भागide by 0. */
		sat = ntohs(param.p->length) - माप(काष्ठा sctp_paramhdr);
		अगर (sat)
			sat /= माप(__u16);

		क्रम (i = 0; i < sat; ++i) अणु
			चयन (param.sat->types[i]) अणु
			हाल SCTP_PARAM_IPV4_ADDRESS:
				asoc->peer.ipv4_address = 1;
				अवरोध;

			हाल SCTP_PARAM_IPV6_ADDRESS:
				अगर (PF_INET6 == asoc->base.sk->sk_family)
					asoc->peer.ipv6_address = 1;
				अवरोध;

			हाल SCTP_PARAM_HOST_NAME_ADDRESS:
				asoc->peer.hostname_address = 1;
				अवरोध;

			शेष: /* Just ignore anything अन्यथा.  */
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल SCTP_PARAM_STATE_COOKIE:
		asoc->peer.cookie_len =
			ntohs(param.p->length) - माप(काष्ठा sctp_paramhdr);
		kमुक्त(asoc->peer.cookie);
		asoc->peer.cookie = kmemdup(param.cookie->body, asoc->peer.cookie_len, gfp);
		अगर (!asoc->peer.cookie)
			retval = 0;
		अवरोध;

	हाल SCTP_PARAM_HEARTBEAT_INFO:
		/* Would be odd to receive, but it causes no problems. */
		अवरोध;

	हाल SCTP_PARAM_UNRECOGNIZED_PARAMETERS:
		/* Rejected during verअगरy stage. */
		अवरोध;

	हाल SCTP_PARAM_ECN_CAPABLE:
		अगर (asoc->ep->ecn_enable) अणु
			asoc->peer.ecn_capable = 1;
			अवरोध;
		पूर्ण
		/* Fall Through */
		जाओ fall_through;


	हाल SCTP_PARAM_ADAPTATION_LAYER_IND:
		asoc->peer.adaptation_ind = ntohl(param.aind->adaptation_ind);
		अवरोध;

	हाल SCTP_PARAM_SET_PRIMARY:
		अगर (!ep->asconf_enable)
			जाओ fall_through;

		addr_param = param.v + माप(काष्ठा sctp_addip_param);

		af = sctp_get_af_specअगरic(param_type2af(addr_param->p.type));
		अगर (af == शून्य)
			अवरोध;

		af->from_addr_param(&addr, addr_param,
				    htons(asoc->peer.port), 0);

		/* अगर the address is invalid, we can't process it.
		 * XXX: see spec क्रम what to करो.
		 */
		अगर (!af->addr_valid(&addr, शून्य, शून्य))
			अवरोध;

		t = sctp_assoc_lookup_paddr(asoc, &addr);
		अगर (!t)
			अवरोध;

		sctp_assoc_set_primary(asoc, t);
		अवरोध;

	हाल SCTP_PARAM_SUPPORTED_EXT:
		sctp_process_ext_param(asoc, param);
		अवरोध;

	हाल SCTP_PARAM_FWD_TSN_SUPPORT:
		अगर (asoc->ep->prsctp_enable) अणु
			asoc->peer.prsctp_capable = 1;
			अवरोध;
		पूर्ण
		/* Fall Through */
		जाओ fall_through;

	हाल SCTP_PARAM_RANDOM:
		अगर (!ep->auth_enable)
			जाओ fall_through;

		/* Save peer's अक्रमom parameter */
		kमुक्त(asoc->peer.peer_अक्रमom);
		asoc->peer.peer_अक्रमom = kmemdup(param.p,
					    ntohs(param.p->length), gfp);
		अगर (!asoc->peer.peer_अक्रमom) अणु
			retval = 0;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SCTP_PARAM_HMAC_ALGO:
		अगर (!ep->auth_enable)
			जाओ fall_through;

		/* Save peer's HMAC list */
		kमुक्त(asoc->peer.peer_hmacs);
		asoc->peer.peer_hmacs = kmemdup(param.p,
					    ntohs(param.p->length), gfp);
		अगर (!asoc->peer.peer_hmacs) अणु
			retval = 0;
			अवरोध;
		पूर्ण

		/* Set the शेष HMAC the peer requested*/
		sctp_auth_asoc_set_शेष_hmac(asoc, param.hmac_algo);
		अवरोध;

	हाल SCTP_PARAM_CHUNKS:
		अगर (!ep->auth_enable)
			जाओ fall_through;

		kमुक्त(asoc->peer.peer_chunks);
		asoc->peer.peer_chunks = kmemdup(param.p,
					    ntohs(param.p->length), gfp);
		अगर (!asoc->peer.peer_chunks)
			retval = 0;
		अवरोध;
fall_through:
	शेष:
		/* Any unrecognized parameters should have been caught
		 * and handled by sctp_verअगरy_param() which should be
		 * called prior to this routine.  Simply log the error
		 * here.
		 */
		pr_debug("%s: ignoring param:%d for association:%p.\n",
			 __func__, ntohs(param.p->type), asoc);
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

/* Select a new verअगरication tag.  */
__u32 sctp_generate_tag(स्थिर काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	/* I believe that this अक्रमom number generator complies with RFC1750.
	 * A tag of 0 is reserved क्रम special हालs (e.g. INIT).
	 */
	__u32 x;

	करो अणु
		get_अक्रमom_bytes(&x, माप(__u32));
	पूर्ण जबतक (x == 0);

	वापस x;
पूर्ण

/* Select an initial TSN to send during startup.  */
__u32 sctp_generate_tsn(स्थिर काष्ठा sctp_endpoपूर्णांक *ep)
अणु
	__u32 retval;

	get_अक्रमom_bytes(&retval, माप(__u32));
	वापस retval;
पूर्ण

/*
 * ADDIP 3.1.1 Address Configuration Change Chunk (ASCONF)
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     | Type = 0xC1   |  Chunk Flags  |      Chunk Length             |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                       Serial Number                           |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                    Address Parameter                          |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                     ASCONF Parameter #1                       |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     \                                                               \
 *     /                             ....                              /
 *     \                                                               \
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                     ASCONF Parameter #N                       |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Address Parameter and other parameter will not be wrapped in this function
 */
अटल काष्ठा sctp_chunk *sctp_make_asconf(काष्ठा sctp_association *asoc,
					   जोड़ sctp_addr *addr,
					   पूर्णांक vparam_len)
अणु
	काष्ठा sctp_addiphdr asconf;
	काष्ठा sctp_chunk *retval;
	पूर्णांक length = माप(asconf) + vparam_len;
	जोड़ sctp_addr_param addrparam;
	पूर्णांक addrlen;
	काष्ठा sctp_af *af = sctp_get_af_specअगरic(addr->v4.sin_family);

	addrlen = af->to_addr_param(addr, &addrparam);
	अगर (!addrlen)
		वापस शून्य;
	length += addrlen;

	/* Create the chunk.  */
	retval = sctp_make_control(asoc, SCTP_CID_ASCONF, 0, length,
				   GFP_ATOMIC);
	अगर (!retval)
		वापस शून्य;

	asconf.serial = htonl(asoc->addip_serial++);

	retval->subh.addip_hdr =
		sctp_addto_chunk(retval, माप(asconf), &asconf);
	retval->param_hdr.v =
		sctp_addto_chunk(retval, addrlen, &addrparam);

	वापस retval;
पूर्ण

/* ADDIP
 * 3.2.1 Add IP Address
 * 	0                   1                   2                   3
 * 	0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |        Type = 0xC001          |    Length = Variable          |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |               ASCONF-Request Correlation ID                   |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                       Address Parameter                       |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * 3.2.2 Delete IP Address
 * 	0                   1                   2                   3
 * 	0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |        Type = 0xC002          |    Length = Variable          |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |               ASCONF-Request Correlation ID                   |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                       Address Parameter                       |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */
काष्ठा sctp_chunk *sctp_make_asconf_update_ip(काष्ठा sctp_association *asoc,
					      जोड़ sctp_addr *laddr,
					      काष्ठा sockaddr *addrs,
					      पूर्णांक addrcnt, __be16 flags)
अणु
	जोड़ sctp_addr_param addr_param;
	काष्ठा sctp_addip_param	param;
	पूर्णांक paramlen = माप(param);
	काष्ठा sctp_chunk *retval;
	पूर्णांक addr_param_len = 0;
	जोड़ sctp_addr *addr;
	पूर्णांक totallen = 0, i;
	पूर्णांक del_pickup = 0;
	काष्ठा sctp_af *af;
	व्योम *addr_buf;

	/* Get total length of all the address parameters. */
	addr_buf = addrs;
	क्रम (i = 0; i < addrcnt; i++) अणु
		addr = addr_buf;
		af = sctp_get_af_specअगरic(addr->v4.sin_family);
		addr_param_len = af->to_addr_param(addr, &addr_param);

		totallen += paramlen;
		totallen += addr_param_len;

		addr_buf += af->sockaddr_len;
		अगर (asoc->asconf_addr_del_pending && !del_pickup) अणु
			/* reuse the parameter length from the same scope one */
			totallen += paramlen;
			totallen += addr_param_len;
			del_pickup = 1;

			pr_debug("%s: picked same-scope del_pending addr, "
				 "totallen for all addresses is %d\n",
				 __func__, totallen);
		पूर्ण
	पूर्ण

	/* Create an asconf chunk with the required length. */
	retval = sctp_make_asconf(asoc, laddr, totallen);
	अगर (!retval)
		वापस शून्य;

	/* Add the address parameters to the asconf chunk. */
	addr_buf = addrs;
	क्रम (i = 0; i < addrcnt; i++) अणु
		addr = addr_buf;
		af = sctp_get_af_specअगरic(addr->v4.sin_family);
		addr_param_len = af->to_addr_param(addr, &addr_param);
		param.param_hdr.type = flags;
		param.param_hdr.length = htons(paramlen + addr_param_len);
		param.crr_id = htonl(i);

		sctp_addto_chunk(retval, paramlen, &param);
		sctp_addto_chunk(retval, addr_param_len, &addr_param);

		addr_buf += af->sockaddr_len;
	पूर्ण
	अगर (flags == SCTP_PARAM_ADD_IP && del_pickup) अणु
		addr = asoc->asconf_addr_del_pending;
		af = sctp_get_af_specअगरic(addr->v4.sin_family);
		addr_param_len = af->to_addr_param(addr, &addr_param);
		param.param_hdr.type = SCTP_PARAM_DEL_IP;
		param.param_hdr.length = htons(paramlen + addr_param_len);
		param.crr_id = htonl(i);

		sctp_addto_chunk(retval, paramlen, &param);
		sctp_addto_chunk(retval, addr_param_len, &addr_param);
	पूर्ण
	वापस retval;
पूर्ण

/* ADDIP
 * 3.2.4 Set Primary IP Address
 *	0                   1                   2                   3
 *	0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |        Type =0xC004           |    Length = Variable          |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |               ASCONF-Request Correlation ID                   |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                       Address Parameter                       |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Create an ASCONF chunk with Set Primary IP address parameter.
 */
काष्ठा sctp_chunk *sctp_make_asconf_set_prim(काष्ठा sctp_association *asoc,
					     जोड़ sctp_addr *addr)
अणु
	काष्ठा sctp_af *af = sctp_get_af_specअगरic(addr->v4.sin_family);
	जोड़ sctp_addr_param addrparam;
	काष्ठा sctp_addip_param	param;
	काष्ठा sctp_chunk *retval;
	पूर्णांक len = माप(param);
	पूर्णांक addrlen;

	addrlen = af->to_addr_param(addr, &addrparam);
	अगर (!addrlen)
		वापस शून्य;
	len += addrlen;

	/* Create the chunk and make asconf header. */
	retval = sctp_make_asconf(asoc, addr, len);
	अगर (!retval)
		वापस शून्य;

	param.param_hdr.type = SCTP_PARAM_SET_PRIMARY;
	param.param_hdr.length = htons(len);
	param.crr_id = 0;

	sctp_addto_chunk(retval, माप(param), &param);
	sctp_addto_chunk(retval, addrlen, &addrparam);

	वापस retval;
पूर्ण

/* ADDIP 3.1.2 Address Configuration Acknowledgement Chunk (ASCONF-ACK)
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     | Type = 0x80   |  Chunk Flags  |      Chunk Length             |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                       Serial Number                           |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                 ASCONF Parameter Response#1                   |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     \                                                               \
 *     /                             ....                              /
 *     \                                                               \
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                 ASCONF Parameter Response#N                   |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Create an ASCONF_ACK chunk with enough space क्रम the parameter responses.
 */
अटल काष्ठा sctp_chunk *sctp_make_asconf_ack(स्थिर काष्ठा sctp_association *asoc,
					       __u32 serial, पूर्णांक vparam_len)
अणु
	काष्ठा sctp_addiphdr asconf;
	काष्ठा sctp_chunk *retval;
	पूर्णांक length = माप(asconf) + vparam_len;

	/* Create the chunk.  */
	retval = sctp_make_control(asoc, SCTP_CID_ASCONF_ACK, 0, length,
				   GFP_ATOMIC);
	अगर (!retval)
		वापस शून्य;

	asconf.serial = htonl(serial);

	retval->subh.addip_hdr =
		sctp_addto_chunk(retval, माप(asconf), &asconf);

	वापस retval;
पूर्ण

/* Add response parameters to an ASCONF_ACK chunk. */
अटल व्योम sctp_add_asconf_response(काष्ठा sctp_chunk *chunk, __be32 crr_id,
				     __be16 err_code,
				     काष्ठा sctp_addip_param *asconf_param)
अणु
	काष्ठा sctp_addip_param ack_param;
	काष्ठा sctp_errhdr err_param;
	पूर्णांक asconf_param_len = 0;
	पूर्णांक err_param_len = 0;
	__be16 response_type;

	अगर (SCTP_ERROR_NO_ERROR == err_code) अणु
		response_type = SCTP_PARAM_SUCCESS_REPORT;
	पूर्ण अन्यथा अणु
		response_type = SCTP_PARAM_ERR_CAUSE;
		err_param_len = माप(err_param);
		अगर (asconf_param)
			asconf_param_len =
				 ntohs(asconf_param->param_hdr.length);
	पूर्ण

	/* Add Success Indication or Error Cause Indication parameter. */
	ack_param.param_hdr.type = response_type;
	ack_param.param_hdr.length = htons(माप(ack_param) +
					   err_param_len +
					   asconf_param_len);
	ack_param.crr_id = crr_id;
	sctp_addto_chunk(chunk, माप(ack_param), &ack_param);

	अगर (SCTP_ERROR_NO_ERROR == err_code)
		वापस;

	/* Add Error Cause parameter. */
	err_param.cause = err_code;
	err_param.length = htons(err_param_len + asconf_param_len);
	sctp_addto_chunk(chunk, err_param_len, &err_param);

	/* Add the failed TLV copied from ASCONF chunk. */
	अगर (asconf_param)
		sctp_addto_chunk(chunk, asconf_param_len, asconf_param);
पूर्ण

/* Process a asconf parameter. */
अटल __be16 sctp_process_asconf_param(काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *asconf,
					काष्ठा sctp_addip_param *asconf_param)
अणु
	जोड़ sctp_addr_param *addr_param;
	काष्ठा sctp_transport *peer;
	जोड़ sctp_addr	addr;
	काष्ठा sctp_af *af;

	addr_param = (व्योम *)asconf_param + माप(*asconf_param);

	अगर (asconf_param->param_hdr.type != SCTP_PARAM_ADD_IP &&
	    asconf_param->param_hdr.type != SCTP_PARAM_DEL_IP &&
	    asconf_param->param_hdr.type != SCTP_PARAM_SET_PRIMARY)
		वापस SCTP_ERROR_UNKNOWN_PARAM;

	चयन (addr_param->p.type) अणु
	हाल SCTP_PARAM_IPV6_ADDRESS:
		अगर (!asoc->peer.ipv6_address)
			वापस SCTP_ERROR_DNS_FAILED;
		अवरोध;
	हाल SCTP_PARAM_IPV4_ADDRESS:
		अगर (!asoc->peer.ipv4_address)
			वापस SCTP_ERROR_DNS_FAILED;
		अवरोध;
	शेष:
		वापस SCTP_ERROR_DNS_FAILED;
	पूर्ण

	af = sctp_get_af_specअगरic(param_type2af(addr_param->p.type));
	अगर (unlikely(!af))
		वापस SCTP_ERROR_DNS_FAILED;

	af->from_addr_param(&addr, addr_param, htons(asoc->peer.port), 0);

	/* ADDIP 4.2.1  This parameter MUST NOT contain a broadcast
	 * or multicast address.
	 * (note: wildcard is permitted and requires special handling so
	 *  make sure we check क्रम that)
	 */
	अगर (!af->is_any(&addr) && !af->addr_valid(&addr, शून्य, asconf->skb))
		वापस SCTP_ERROR_DNS_FAILED;

	चयन (asconf_param->param_hdr.type) अणु
	हाल SCTP_PARAM_ADD_IP:
		/* Section 4.2.1:
		 * If the address 0.0.0.0 or ::0 is provided, the source
		 * address of the packet MUST be added.
		 */
		अगर (af->is_any(&addr))
			स_नकल(&addr, &asconf->source, माप(addr));

		अगर (security_sctp_bind_connect(asoc->ep->base.sk,
					       SCTP_PARAM_ADD_IP,
					       (काष्ठा sockaddr *)&addr,
					       af->sockaddr_len))
			वापस SCTP_ERROR_REQ_REFUSED;

		/* ADDIP 4.3 D9) If an endpoपूर्णांक receives an ADD IP address
		 * request and करोes not have the local resources to add this
		 * new address to the association, it MUST वापस an Error
		 * Cause TLV set to the new error code 'Operation Refused
		 * Due to Resource Shortage'.
		 */

		peer = sctp_assoc_add_peer(asoc, &addr, GFP_ATOMIC, SCTP_UNCONFIRMED);
		अगर (!peer)
			वापस SCTP_ERROR_RSRC_LOW;

		/* Start the heartbeat समयr. */
		sctp_transport_reset_hb_समयr(peer);
		asoc->new_transport = peer;
		अवरोध;
	हाल SCTP_PARAM_DEL_IP:
		/* ADDIP 4.3 D7) If a request is received to delete the
		 * last reमुख्यing IP address of a peer endpoपूर्णांक, the receiver
		 * MUST send an Error Cause TLV with the error cause set to the
		 * new error code 'Request to Delete Last Remaining IP Address'.
		 */
		अगर (asoc->peer.transport_count == 1)
			वापस SCTP_ERROR_DEL_LAST_IP;

		/* ADDIP 4.3 D8) If a request is received to delete an IP
		 * address which is also the source address of the IP packet
		 * which contained the ASCONF chunk, the receiver MUST reject
		 * this request. To reject the request the receiver MUST send
		 * an Error Cause TLV set to the new error code 'Request to
		 * Delete Source IP Address'
		 */
		अगर (sctp_cmp_addr_exact(&asconf->source, &addr))
			वापस SCTP_ERROR_DEL_SRC_IP;

		/* Section 4.2.2
		 * If the address 0.0.0.0 or ::0 is provided, all
		 * addresses of the peer except	the source address of the
		 * packet MUST be deleted.
		 */
		अगर (af->is_any(&addr)) अणु
			sctp_assoc_set_primary(asoc, asconf->transport);
			sctp_assoc_del_nonprimary_peers(asoc,
							asconf->transport);
			वापस SCTP_ERROR_NO_ERROR;
		पूर्ण

		/* If the address is not part of the association, the
		 * ASCONF-ACK with Error Cause Indication Parameter
		 * which including cause of Unresolvable Address should
		 * be sent.
		 */
		peer = sctp_assoc_lookup_paddr(asoc, &addr);
		अगर (!peer)
			वापस SCTP_ERROR_DNS_FAILED;

		sctp_assoc_rm_peer(asoc, peer);
		अवरोध;
	हाल SCTP_PARAM_SET_PRIMARY:
		/* ADDIP Section 4.2.4
		 * If the address 0.0.0.0 or ::0 is provided, the receiver
		 * MAY mark the source address of the packet as its
		 * primary.
		 */
		अगर (af->is_any(&addr))
			स_नकल(&addr, sctp_source(asconf), माप(addr));

		अगर (security_sctp_bind_connect(asoc->ep->base.sk,
					       SCTP_PARAM_SET_PRIMARY,
					       (काष्ठा sockaddr *)&addr,
					       af->sockaddr_len))
			वापस SCTP_ERROR_REQ_REFUSED;

		peer = sctp_assoc_lookup_paddr(asoc, &addr);
		अगर (!peer)
			वापस SCTP_ERROR_DNS_FAILED;

		sctp_assoc_set_primary(asoc, peer);
		अवरोध;
	पूर्ण

	वापस SCTP_ERROR_NO_ERROR;
पूर्ण

/* Verअगरy the ASCONF packet beक्रमe we process it. */
bool sctp_verअगरy_asconf(स्थिर काष्ठा sctp_association *asoc,
			काष्ठा sctp_chunk *chunk, bool addr_param_needed,
			काष्ठा sctp_paramhdr **errp)
अणु
	काष्ठा sctp_addip_chunk *addip;
	bool addr_param_seen = false;
	जोड़ sctp_params param;

	addip = (काष्ठा sctp_addip_chunk *)chunk->chunk_hdr;
	sctp_walk_params(param, addip, addip_hdr.params) अणु
		माप_प्रकार length = ntohs(param.p->length);

		*errp = param.p;
		चयन (param.p->type) अणु
		हाल SCTP_PARAM_ERR_CAUSE:
			अवरोध;
		हाल SCTP_PARAM_IPV4_ADDRESS:
			अगर (length != माप(काष्ठा sctp_ipv4addr_param))
				वापस false;
			/* ensure there is only one addr param and it's in the
			 * beginning of addip_hdr params, or we reject it.
			 */
			अगर (param.v != addip->addip_hdr.params)
				वापस false;
			addr_param_seen = true;
			अवरोध;
		हाल SCTP_PARAM_IPV6_ADDRESS:
			अगर (length != माप(काष्ठा sctp_ipv6addr_param))
				वापस false;
			अगर (param.v != addip->addip_hdr.params)
				वापस false;
			addr_param_seen = true;
			अवरोध;
		हाल SCTP_PARAM_ADD_IP:
		हाल SCTP_PARAM_DEL_IP:
		हाल SCTP_PARAM_SET_PRIMARY:
			/* In ASCONF chunks, these need to be first. */
			अगर (addr_param_needed && !addr_param_seen)
				वापस false;
			length = ntohs(param.addip->param_hdr.length);
			अगर (length < माप(काष्ठा sctp_addip_param) +
				     माप(**errp))
				वापस false;
			अवरोध;
		हाल SCTP_PARAM_SUCCESS_REPORT:
		हाल SCTP_PARAM_ADAPTATION_LAYER_IND:
			अगर (length != माप(काष्ठा sctp_addip_param))
				वापस false;
			अवरोध;
		शेष:
			/* This is unknown to us, reject! */
			वापस false;
		पूर्ण
	पूर्ण

	/* Reमुख्यing sanity checks. */
	अगर (addr_param_needed && !addr_param_seen)
		वापस false;
	अगर (!addr_param_needed && addr_param_seen)
		वापस false;
	अगर (param.v != chunk->chunk_end)
		वापस false;

	वापस true;
पूर्ण

/* Process an incoming ASCONF chunk with the next expected serial no. and
 * वापस an ASCONF_ACK chunk to be sent in response.
 */
काष्ठा sctp_chunk *sctp_process_asconf(काष्ठा sctp_association *asoc,
				       काष्ठा sctp_chunk *asconf)
अणु
	जोड़ sctp_addr_param *addr_param;
	काष्ठा sctp_addip_chunk *addip;
	काष्ठा sctp_chunk *asconf_ack;
	bool all_param_pass = true;
	काष्ठा sctp_addiphdr *hdr;
	पूर्णांक length = 0, chunk_len;
	जोड़ sctp_params param;
	__be16 err_code;
	__u32 serial;

	addip = (काष्ठा sctp_addip_chunk *)asconf->chunk_hdr;
	chunk_len = ntohs(asconf->chunk_hdr->length) -
		    माप(काष्ठा sctp_chunkhdr);
	hdr = (काष्ठा sctp_addiphdr *)asconf->skb->data;
	serial = ntohl(hdr->serial);

	/* Skip the addiphdr and store a poपूर्णांकer to address parameter.  */
	length = माप(*hdr);
	addr_param = (जोड़ sctp_addr_param *)(asconf->skb->data + length);
	chunk_len -= length;

	/* Skip the address parameter and store a poपूर्णांकer to the first
	 * asconf parameter.
	 */
	length = ntohs(addr_param->p.length);
	chunk_len -= length;

	/* create an ASCONF_ACK chunk.
	 * Based on the definitions of parameters, we know that the size of
	 * ASCONF_ACK parameters are less than or equal to the fourfold of ASCONF
	 * parameters.
	 */
	asconf_ack = sctp_make_asconf_ack(asoc, serial, chunk_len * 4);
	अगर (!asconf_ack)
		जाओ करोne;

	/* Process the TLVs contained within the ASCONF chunk. */
	sctp_walk_params(param, addip, addip_hdr.params) अणु
		/* Skip preceeding address parameters. */
		अगर (param.p->type == SCTP_PARAM_IPV4_ADDRESS ||
		    param.p->type == SCTP_PARAM_IPV6_ADDRESS)
			जारी;

		err_code = sctp_process_asconf_param(asoc, asconf,
						     param.addip);
		/* ADDIP 4.1 A7)
		 * If an error response is received क्रम a TLV parameter,
		 * all TLVs with no response beक्रमe the failed TLV are
		 * considered successful अगर not reported.  All TLVs after
		 * the failed response are considered unsuccessful unless
		 * a specअगरic success indication is present क्रम the parameter.
		 */
		अगर (err_code != SCTP_ERROR_NO_ERROR)
			all_param_pass = false;
		अगर (!all_param_pass)
			sctp_add_asconf_response(asconf_ack, param.addip->crr_id,
						 err_code, param.addip);

		/* ADDIP 4.3 D11) When an endpoपूर्णांक receiving an ASCONF to add
		 * an IP address sends an 'Out of Resource' in its response, it
		 * MUST also fail any subsequent add or delete requests bundled
		 * in the ASCONF.
		 */
		अगर (err_code == SCTP_ERROR_RSRC_LOW)
			जाओ करोne;
	पूर्ण
करोne:
	asoc->peer.addip_serial++;

	/* If we are sending a new ASCONF_ACK hold a reference to it in assoc
	 * after मुक्तing the reference to old asconf ack अगर any.
	 */
	अगर (asconf_ack) अणु
		sctp_chunk_hold(asconf_ack);
		list_add_tail(&asconf_ack->transmitted_list,
			      &asoc->asconf_ack_list);
	पूर्ण

	वापस asconf_ack;
पूर्ण

/* Process a asconf parameter that is successfully acked. */
अटल व्योम sctp_asconf_param_success(काष्ठा sctp_association *asoc,
				      काष्ठा sctp_addip_param *asconf_param)
अणु
	काष्ठा sctp_bind_addr *bp = &asoc->base.bind_addr;
	जोड़ sctp_addr_param *addr_param;
	काष्ठा sctp_sockaddr_entry *saddr;
	काष्ठा sctp_transport *transport;
	जोड़ sctp_addr	addr;
	काष्ठा sctp_af *af;

	addr_param = (व्योम *)asconf_param + माप(*asconf_param);

	/* We have checked the packet beक्रमe, so we करो not check again.	*/
	af = sctp_get_af_specअगरic(param_type2af(addr_param->p.type));
	af->from_addr_param(&addr, addr_param, htons(bp->port), 0);

	चयन (asconf_param->param_hdr.type) अणु
	हाल SCTP_PARAM_ADD_IP:
		/* This is always करोne in BH context with a socket lock
		 * held, so the list can not change.
		 */
		local_bh_disable();
		list_क्रम_each_entry(saddr, &bp->address_list, list) अणु
			अगर (sctp_cmp_addr_exact(&saddr->a, &addr))
				saddr->state = SCTP_ADDR_SRC;
		पूर्ण
		local_bh_enable();
		list_क्रम_each_entry(transport, &asoc->peer.transport_addr_list,
				transports) अणु
			sctp_transport_dst_release(transport);
		पूर्ण
		अवरोध;
	हाल SCTP_PARAM_DEL_IP:
		local_bh_disable();
		sctp_del_bind_addr(bp, &addr);
		अगर (asoc->asconf_addr_del_pending != शून्य &&
		    sctp_cmp_addr_exact(asoc->asconf_addr_del_pending, &addr)) अणु
			kमुक्त(asoc->asconf_addr_del_pending);
			asoc->asconf_addr_del_pending = शून्य;
		पूर्ण
		local_bh_enable();
		list_क्रम_each_entry(transport, &asoc->peer.transport_addr_list,
				transports) अणु
			sctp_transport_dst_release(transport);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* Get the corresponding ASCONF response error code from the ASCONF_ACK chunk
 * क्रम the given asconf parameter.  If there is no response क्रम this parameter,
 * वापस the error code based on the third argument 'no_err'.
 * ADDIP 4.1
 * A7) If an error response is received क्रम a TLV parameter, all TLVs with no
 * response beक्रमe the failed TLV are considered successful अगर not reported.
 * All TLVs after the failed response are considered unsuccessful unless a
 * specअगरic success indication is present क्रम the parameter.
 */
अटल __be16 sctp_get_asconf_response(काष्ठा sctp_chunk *asconf_ack,
				       काष्ठा sctp_addip_param *asconf_param,
				       पूर्णांक no_err)
अणु
	काष्ठा sctp_addip_param	*asconf_ack_param;
	काष्ठा sctp_errhdr *err_param;
	पूर्णांक asconf_ack_len;
	__be16 err_code;
	पूर्णांक length;

	अगर (no_err)
		err_code = SCTP_ERROR_NO_ERROR;
	अन्यथा
		err_code = SCTP_ERROR_REQ_REFUSED;

	asconf_ack_len = ntohs(asconf_ack->chunk_hdr->length) -
			 माप(काष्ठा sctp_chunkhdr);

	/* Skip the addiphdr from the asconf_ack chunk and store a poपूर्णांकer to
	 * the first asconf_ack parameter.
	 */
	length = माप(काष्ठा sctp_addiphdr);
	asconf_ack_param = (काष्ठा sctp_addip_param *)(asconf_ack->skb->data +
						       length);
	asconf_ack_len -= length;

	जबतक (asconf_ack_len > 0) अणु
		अगर (asconf_ack_param->crr_id == asconf_param->crr_id) अणु
			चयन (asconf_ack_param->param_hdr.type) अणु
			हाल SCTP_PARAM_SUCCESS_REPORT:
				वापस SCTP_ERROR_NO_ERROR;
			हाल SCTP_PARAM_ERR_CAUSE:
				length = माप(*asconf_ack_param);
				err_param = (व्योम *)asconf_ack_param + length;
				asconf_ack_len -= length;
				अगर (asconf_ack_len > 0)
					वापस err_param->cause;
				अन्यथा
					वापस SCTP_ERROR_INV_PARAM;
				अवरोध;
			शेष:
				वापस SCTP_ERROR_INV_PARAM;
			पूर्ण
		पूर्ण

		length = ntohs(asconf_ack_param->param_hdr.length);
		asconf_ack_param = (व्योम *)asconf_ack_param + length;
		asconf_ack_len -= length;
	पूर्ण

	वापस err_code;
पूर्ण

/* Process an incoming ASCONF_ACK chunk against the cached last ASCONF chunk. */
पूर्णांक sctp_process_asconf_ack(काष्ठा sctp_association *asoc,
			    काष्ठा sctp_chunk *asconf_ack)
अणु
	काष्ठा sctp_chunk *asconf = asoc->addip_last_asconf;
	काष्ठा sctp_addip_param *asconf_param;
	__be16 err_code = SCTP_ERROR_NO_ERROR;
	जोड़ sctp_addr_param *addr_param;
	पूर्णांक asconf_len = asconf->skb->len;
	पूर्णांक all_param_pass = 0;
	पूर्णांक length = 0;
	पूर्णांक no_err = 1;
	पूर्णांक retval = 0;

	/* Skip the chunkhdr and addiphdr from the last asconf sent and store
	 * a poपूर्णांकer to address parameter.
	 */
	length = माप(काष्ठा sctp_addip_chunk);
	addr_param = (जोड़ sctp_addr_param *)(asconf->skb->data + length);
	asconf_len -= length;

	/* Skip the address parameter in the last asconf sent and store a
	 * poपूर्णांकer to the first asconf parameter.
	 */
	length = ntohs(addr_param->p.length);
	asconf_param = (व्योम *)addr_param + length;
	asconf_len -= length;

	/* ADDIP 4.1
	 * A8) If there is no response(s) to specअगरic TLV parameter(s), and no
	 * failures are indicated, then all request(s) are considered
	 * successful.
	 */
	अगर (asconf_ack->skb->len == माप(काष्ठा sctp_addiphdr))
		all_param_pass = 1;

	/* Process the TLVs contained in the last sent ASCONF chunk. */
	जबतक (asconf_len > 0) अणु
		अगर (all_param_pass)
			err_code = SCTP_ERROR_NO_ERROR;
		अन्यथा अणु
			err_code = sctp_get_asconf_response(asconf_ack,
							    asconf_param,
							    no_err);
			अगर (no_err && (SCTP_ERROR_NO_ERROR != err_code))
				no_err = 0;
		पूर्ण

		चयन (err_code) अणु
		हाल SCTP_ERROR_NO_ERROR:
			sctp_asconf_param_success(asoc, asconf_param);
			अवरोध;

		हाल SCTP_ERROR_RSRC_LOW:
			retval = 1;
			अवरोध;

		हाल SCTP_ERROR_UNKNOWN_PARAM:
			/* Disable sending this type of asconf parameter in
			 * future.
			 */
			asoc->peer.addip_disabled_mask |=
				asconf_param->param_hdr.type;
			अवरोध;

		हाल SCTP_ERROR_REQ_REFUSED:
		हाल SCTP_ERROR_DEL_LAST_IP:
		हाल SCTP_ERROR_DEL_SRC_IP:
		शेष:
			 अवरोध;
		पूर्ण

		/* Skip the processed asconf parameter and move to the next
		 * one.
		 */
		length = ntohs(asconf_param->param_hdr.length);
		asconf_param = (व्योम *)asconf_param + length;
		asconf_len -= length;
	पूर्ण

	अगर (no_err && asoc->src_out_of_asoc_ok) अणु
		asoc->src_out_of_asoc_ok = 0;
		sctp_transport_immediate_rtx(asoc->peer.primary_path);
	पूर्ण

	/* Free the cached last sent asconf chunk. */
	list_del_init(&asconf->transmitted_list);
	sctp_chunk_मुक्त(asconf);
	asoc->addip_last_asconf = शून्य;

	वापस retval;
पूर्ण

/* Make a FWD TSN chunk. */
काष्ठा sctp_chunk *sctp_make_fwdtsn(स्थिर काष्ठा sctp_association *asoc,
				    __u32 new_cum_tsn, माप_प्रकार nstreams,
				    काष्ठा sctp_fwdtsn_skip *skiplist)
अणु
	काष्ठा sctp_chunk *retval = शून्य;
	काष्ठा sctp_fwdtsn_hdr ftsn_hdr;
	काष्ठा sctp_fwdtsn_skip skip;
	माप_प्रकार hपूर्णांक;
	पूर्णांक i;

	hपूर्णांक = (nstreams + 1) * माप(__u32);

	retval = sctp_make_control(asoc, SCTP_CID_FWD_TSN, 0, hपूर्णांक, GFP_ATOMIC);

	अगर (!retval)
		वापस शून्य;

	ftsn_hdr.new_cum_tsn = htonl(new_cum_tsn);
	retval->subh.fwdtsn_hdr =
		sctp_addto_chunk(retval, माप(ftsn_hdr), &ftsn_hdr);

	क्रम (i = 0; i < nstreams; i++) अणु
		skip.stream = skiplist[i].stream;
		skip.ssn = skiplist[i].ssn;
		sctp_addto_chunk(retval, माप(skip), &skip);
	पूर्ण

	वापस retval;
पूर्ण

काष्ठा sctp_chunk *sctp_make_अगरwdtsn(स्थिर काष्ठा sctp_association *asoc,
				     __u32 new_cum_tsn, माप_प्रकार nstreams,
				     काष्ठा sctp_अगरwdtsn_skip *skiplist)
अणु
	काष्ठा sctp_chunk *retval = शून्य;
	काष्ठा sctp_अगरwdtsn_hdr ftsn_hdr;
	माप_प्रकार hपूर्णांक;

	hपूर्णांक = (nstreams + 1) * माप(__u32);

	retval = sctp_make_control(asoc, SCTP_CID_I_FWD_TSN, 0, hपूर्णांक,
				   GFP_ATOMIC);
	अगर (!retval)
		वापस शून्य;

	ftsn_hdr.new_cum_tsn = htonl(new_cum_tsn);
	retval->subh.अगरwdtsn_hdr =
		sctp_addto_chunk(retval, माप(ftsn_hdr), &ftsn_hdr);

	sctp_addto_chunk(retval, nstreams * माप(skiplist[0]), skiplist);

	वापस retval;
पूर्ण

/* RE-CONFIG 3.1 (RE-CONFIG chunk)
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  | Type = 130    |  Chunk Flags  |      Chunk Length             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  \                                                               \
 *  /                  Re-configuration Parameter                   /
 *  \                                                               \
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  \                                                               \
 *  /             Re-configuration Parameter (optional)             /
 *  \                                                               \
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
अटल काष्ठा sctp_chunk *sctp_make_reconf(स्थिर काष्ठा sctp_association *asoc,
					   पूर्णांक length)
अणु
	काष्ठा sctp_reconf_chunk *reconf;
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_control(asoc, SCTP_CID_RECONF, 0, length,
				   GFP_ATOMIC);
	अगर (!retval)
		वापस शून्य;

	reconf = (काष्ठा sctp_reconf_chunk *)retval->chunk_hdr;
	retval->param_hdr.v = reconf->params;

	वापस retval;
पूर्ण

/* RE-CONFIG 4.1 (STREAM OUT RESET)
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Parameter Type = 13       | Parameter Length = 16 + 2 * N |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |           Re-configuration Request Sequence Number            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |           Re-configuration Response Sequence Number           |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                Sender's Last Asचिन्हित TSN                     |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |  Stream Number 1 (optional)   |    Stream Number 2 (optional) |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  /                            ......                             /
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |  Stream Number N-1 (optional) |    Stream Number N (optional) |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * RE-CONFIG 4.2 (STREAM IN RESET)
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Parameter Type = 14       |  Parameter Length = 8 + 2 * N |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |          Re-configuration Request Sequence Number             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |  Stream Number 1 (optional)   |    Stream Number 2 (optional) |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  /                            ......                             /
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |  Stream Number N-1 (optional) |    Stream Number N (optional) |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा sctp_chunk *sctp_make_strreset_req(
					स्थिर काष्ठा sctp_association *asoc,
					__u16 stream_num, __be16 *stream_list,
					bool out, bool in)
अणु
	__u16 stream_len = stream_num * माप(__u16);
	काष्ठा sctp_strreset_outreq outreq;
	काष्ठा sctp_strreset_inreq inreq;
	काष्ठा sctp_chunk *retval;
	__u16 outlen, inlen;

	outlen = (माप(outreq) + stream_len) * out;
	inlen = (माप(inreq) + stream_len) * in;

	retval = sctp_make_reconf(asoc, outlen + inlen);
	अगर (!retval)
		वापस शून्य;

	अगर (outlen) अणु
		outreq.param_hdr.type = SCTP_PARAM_RESET_OUT_REQUEST;
		outreq.param_hdr.length = htons(outlen);
		outreq.request_seq = htonl(asoc->strreset_outseq);
		outreq.response_seq = htonl(asoc->strreset_inseq - 1);
		outreq.send_reset_at_tsn = htonl(asoc->next_tsn - 1);

		sctp_addto_chunk(retval, माप(outreq), &outreq);

		अगर (stream_len)
			sctp_addto_chunk(retval, stream_len, stream_list);
	पूर्ण

	अगर (inlen) अणु
		inreq.param_hdr.type = SCTP_PARAM_RESET_IN_REQUEST;
		inreq.param_hdr.length = htons(inlen);
		inreq.request_seq = htonl(asoc->strreset_outseq + out);

		sctp_addto_chunk(retval, माप(inreq), &inreq);

		अगर (stream_len)
			sctp_addto_chunk(retval, stream_len, stream_list);
	पूर्ण

	वापस retval;
पूर्ण

/* RE-CONFIG 4.3 (SSN/TSN RESET ALL)
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Parameter Type = 15       |      Parameter Length = 8     |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |         Re-configuration Request Sequence Number              |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा sctp_chunk *sctp_make_strreset_tsnreq(
					स्थिर काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_strreset_tsnreq tsnreq;
	__u16 length = माप(tsnreq);
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_reconf(asoc, length);
	अगर (!retval)
		वापस शून्य;

	tsnreq.param_hdr.type = SCTP_PARAM_RESET_TSN_REQUEST;
	tsnreq.param_hdr.length = htons(length);
	tsnreq.request_seq = htonl(asoc->strreset_outseq);

	sctp_addto_chunk(retval, माप(tsnreq), &tsnreq);

	वापस retval;
पूर्ण

/* RE-CONFIG 4.5/4.6 (ADD STREAM)
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Parameter Type = 17       |      Parameter Length = 12    |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |          Re-configuration Request Sequence Number             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |      Number of new streams    |         Reserved              |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा sctp_chunk *sctp_make_strreset_addstrm(
					स्थिर काष्ठा sctp_association *asoc,
					__u16 out, __u16 in)
अणु
	काष्ठा sctp_strreset_addstrm addstrm;
	__u16 size = माप(addstrm);
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_reconf(asoc, (!!out + !!in) * size);
	अगर (!retval)
		वापस शून्य;

	अगर (out) अणु
		addstrm.param_hdr.type = SCTP_PARAM_RESET_ADD_OUT_STREAMS;
		addstrm.param_hdr.length = htons(size);
		addstrm.number_of_streams = htons(out);
		addstrm.request_seq = htonl(asoc->strreset_outseq);
		addstrm.reserved = 0;

		sctp_addto_chunk(retval, size, &addstrm);
	पूर्ण

	अगर (in) अणु
		addstrm.param_hdr.type = SCTP_PARAM_RESET_ADD_IN_STREAMS;
		addstrm.param_hdr.length = htons(size);
		addstrm.number_of_streams = htons(in);
		addstrm.request_seq = htonl(asoc->strreset_outseq + !!out);
		addstrm.reserved = 0;

		sctp_addto_chunk(retval, size, &addstrm);
	पूर्ण

	वापस retval;
पूर्ण

/* RE-CONFIG 4.4 (RESP)
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Parameter Type = 16       |      Parameter Length         |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |         Re-configuration Response Sequence Number             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                            Result                             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा sctp_chunk *sctp_make_strreset_resp(स्थिर काष्ठा sctp_association *asoc,
					   __u32 result, __u32 sn)
अणु
	काष्ठा sctp_strreset_resp resp;
	__u16 length = माप(resp);
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_reconf(asoc, length);
	अगर (!retval)
		वापस शून्य;

	resp.param_hdr.type = SCTP_PARAM_RESET_RESPONSE;
	resp.param_hdr.length = htons(length);
	resp.response_seq = htonl(sn);
	resp.result = htonl(result);

	sctp_addto_chunk(retval, माप(resp), &resp);

	वापस retval;
पूर्ण

/* RE-CONFIG 4.4 OPTIONAL (TSNRESP)
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |     Parameter Type = 16       |      Parameter Length         |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |         Re-configuration Response Sequence Number             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                            Result                             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                   Sender's Next TSN (optional)                |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                  Receiver's Next TSN (optional)               |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा sctp_chunk *sctp_make_strreset_tsnresp(काष्ठा sctp_association *asoc,
					      __u32 result, __u32 sn,
					      __u32 sender_tsn,
					      __u32 receiver_tsn)
अणु
	काष्ठा sctp_strreset_resptsn tsnresp;
	__u16 length = माप(tsnresp);
	काष्ठा sctp_chunk *retval;

	retval = sctp_make_reconf(asoc, length);
	अगर (!retval)
		वापस शून्य;

	tsnresp.param_hdr.type = SCTP_PARAM_RESET_RESPONSE;
	tsnresp.param_hdr.length = htons(length);

	tsnresp.response_seq = htonl(sn);
	tsnresp.result = htonl(result);
	tsnresp.senders_next_tsn = htonl(sender_tsn);
	tsnresp.receivers_next_tsn = htonl(receiver_tsn);

	sctp_addto_chunk(retval, माप(tsnresp), &tsnresp);

	वापस retval;
पूर्ण

bool sctp_verअगरy_reconf(स्थिर काष्ठा sctp_association *asoc,
			काष्ठा sctp_chunk *chunk,
			काष्ठा sctp_paramhdr **errp)
अणु
	काष्ठा sctp_reconf_chunk *hdr;
	जोड़ sctp_params param;
	__be16 last = 0;
	__u16 cnt = 0;

	hdr = (काष्ठा sctp_reconf_chunk *)chunk->chunk_hdr;
	sctp_walk_params(param, hdr, params) अणु
		__u16 length = ntohs(param.p->length);

		*errp = param.p;
		अगर (cnt++ > 2)
			वापस false;
		चयन (param.p->type) अणु
		हाल SCTP_PARAM_RESET_OUT_REQUEST:
			अगर (length < माप(काष्ठा sctp_strreset_outreq) ||
			    (last && last != SCTP_PARAM_RESET_RESPONSE &&
			     last != SCTP_PARAM_RESET_IN_REQUEST))
				वापस false;
			अवरोध;
		हाल SCTP_PARAM_RESET_IN_REQUEST:
			अगर (length < माप(काष्ठा sctp_strreset_inreq) ||
			    (last && last != SCTP_PARAM_RESET_OUT_REQUEST))
				वापस false;
			अवरोध;
		हाल SCTP_PARAM_RESET_RESPONSE:
			अगर ((length != माप(काष्ठा sctp_strreset_resp) &&
			     length != माप(काष्ठा sctp_strreset_resptsn)) ||
			    (last && last != SCTP_PARAM_RESET_RESPONSE &&
			     last != SCTP_PARAM_RESET_OUT_REQUEST))
				वापस false;
			अवरोध;
		हाल SCTP_PARAM_RESET_TSN_REQUEST:
			अगर (length !=
			    माप(काष्ठा sctp_strreset_tsnreq) || last)
				वापस false;
			अवरोध;
		हाल SCTP_PARAM_RESET_ADD_IN_STREAMS:
			अगर (length != माप(काष्ठा sctp_strreset_addstrm) ||
			    (last && last != SCTP_PARAM_RESET_ADD_OUT_STREAMS))
				वापस false;
			अवरोध;
		हाल SCTP_PARAM_RESET_ADD_OUT_STREAMS:
			अगर (length != माप(काष्ठा sctp_strreset_addstrm) ||
			    (last && last != SCTP_PARAM_RESET_ADD_IN_STREAMS))
				वापस false;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण

		last = param.p->type;
	पूर्ण

	वापस true;
पूर्ण
