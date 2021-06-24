<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Connection tracking protocol helper module क्रम SCTP.
 *
 * Copyright (c) 2004 Kiran Kumar Immidi <immidi_kiran@yahoo.com>
 * Copyright (c) 2004-2012 Patrick McHardy <kaber@trash.net>
 *
 * SCTP is defined in RFC 2960. References to various sections in this code
 * are to this RFC.
 */

#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/sctp.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/sctp/checksum.h>

#समावेश <net/netfilter/nf_log.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>

/* FIXME: Examine ipfilter's समयouts and conntrack transitions more
   बंदly.  They're more complex. --RR

   And so क्रम me क्रम SCTP :D -Kiran */

अटल स्थिर अक्षर *स्थिर sctp_conntrack_names[] = अणु
	"NONE",
	"CLOSED",
	"COOKIE_WAIT",
	"COOKIE_ECHOED",
	"ESTABLISHED",
	"SHUTDOWN_SENT",
	"SHUTDOWN_RECD",
	"SHUTDOWN_ACK_SENT",
	"HEARTBEAT_SENT",
	"HEARTBEAT_ACKED",
पूर्ण;

#घोषणा SECS  * HZ
#घोषणा MINS  * 60 SECS
#घोषणा HOURS * 60 MINS
#घोषणा DAYS  * 24 HOURS

अटल स्थिर अचिन्हित पूर्णांक sctp_समयouts[SCTP_CONNTRACK_MAX] = अणु
	[SCTP_CONNTRACK_CLOSED]			= 10 SECS,
	[SCTP_CONNTRACK_COOKIE_WAIT]		= 3 SECS,
	[SCTP_CONNTRACK_COOKIE_ECHOED]		= 3 SECS,
	[SCTP_CONNTRACK_ESTABLISHED]		= 5 DAYS,
	[SCTP_CONNTRACK_SHUTDOWN_SENT]		= 300 SECS / 1000,
	[SCTP_CONNTRACK_SHUTDOWN_RECD]		= 300 SECS / 1000,
	[SCTP_CONNTRACK_SHUTDOWN_ACK_SENT]	= 3 SECS,
	[SCTP_CONNTRACK_HEARTBEAT_SENT]		= 30 SECS,
	[SCTP_CONNTRACK_HEARTBEAT_ACKED]	= 210 SECS,
पूर्ण;

#घोषणा	SCTP_FLAG_HEARTBEAT_VTAG_FAILED	1

#घोषणा sNO SCTP_CONNTRACK_NONE
#घोषणा	sCL SCTP_CONNTRACK_CLOSED
#घोषणा	sCW SCTP_CONNTRACK_COOKIE_WAIT
#घोषणा	sCE SCTP_CONNTRACK_COOKIE_ECHOED
#घोषणा	sES SCTP_CONNTRACK_ESTABLISHED
#घोषणा	sSS SCTP_CONNTRACK_SHUTDOWN_SENT
#घोषणा	sSR SCTP_CONNTRACK_SHUTDOWN_RECD
#घोषणा	sSA SCTP_CONNTRACK_SHUTDOWN_ACK_SENT
#घोषणा	sHS SCTP_CONNTRACK_HEARTBEAT_SENT
#घोषणा	sHA SCTP_CONNTRACK_HEARTBEAT_ACKED
#घोषणा	sIV SCTP_CONNTRACK_MAX

/*
	These are the descriptions of the states:

NOTE: These state names are tantalizingly similar to the states of an
SCTP endpoपूर्णांक. But the पूर्णांकerpretation of the states is a little dअगरferent,
considering that these are the states of the connection and not of an end
poपूर्णांक. Please note the subtleties. -Kiran

NONE              - Nothing so far.
COOKIE WAIT       - We have seen an INIT chunk in the original direction, or also
		    an INIT_ACK chunk in the reply direction.
COOKIE ECHOED     - We have seen a COOKIE_ECHO chunk in the original direction.
ESTABLISHED       - We have seen a COOKIE_ACK in the reply direction.
SHUTDOWN_SENT     - We have seen a SHUTDOWN chunk in the original direction.
SHUTDOWN_RECD     - We have seen a SHUTDOWN chunk in the reply directoin.
SHUTDOWN_ACK_SENT - We have seen a SHUTDOWN_ACK chunk in the direction opposite
		    to that of the SHUTDOWN chunk.
CLOSED            - We have seen a SHUTDOWN_COMPLETE chunk in the direction of
		    the SHUTDOWN chunk. Connection is बंदd.
HEARTBEAT_SENT    - We have seen a HEARTBEAT in a new flow.
HEARTBEAT_ACKED   - We have seen a HEARTBEAT-ACK in the direction opposite to
		    that of the HEARTBEAT chunk. Secondary connection is
		    established.
*/

/* TODO
 - I have assumed that the first INIT is in the original direction.
 This messes things when an INIT comes in the reply direction in CLOSED
 state.
 - Check the error type in the reply dir beक्रमe transitioning from
cookie echoed to बंदd.
 - Sec 5.2.4 of RFC 2960
 - Full Multi Homing support.
*/

/* SCTP conntrack state transitions */
अटल स्थिर u8 sctp_conntracks[2][11][SCTP_CONNTRACK_MAX] = अणु
	अणु
/*	ORIGINAL	*/
/*                  sNO, sCL, sCW, sCE, sES, sSS, sSR, sSA, sHS, sHA */
/* init         */ अणुsCL, sCL, sCW, sCE, sES, sSS, sSR, sSA, sCW, sHAपूर्ण,
/* init_ack     */ अणुsCL, sCL, sCW, sCE, sES, sSS, sSR, sSA, sCL, sHAपूर्ण,
/* पात        */ अणुsCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCLपूर्ण,
/* shutकरोwn     */ अणुsCL, sCL, sCW, sCE, sSS, sSS, sSR, sSA, sCL, sSSपूर्ण,
/* shutकरोwn_ack */ अणुsSA, sCL, sCW, sCE, sES, sSA, sSA, sSA, sSA, sHAपूर्ण,
/* error        */ अणुsCL, sCL, sCW, sCE, sES, sSS, sSR, sSA, sCL, sHAपूर्ण,/* Can't have Stale cookie*/
/* cookie_echo  */ अणुsCL, sCL, sCE, sCE, sES, sSS, sSR, sSA, sCL, sHAपूर्ण,/* 5.2.4 - Big TODO */
/* cookie_ack   */ अणुsCL, sCL, sCW, sCE, sES, sSS, sSR, sSA, sCL, sHAपूर्ण,/* Can't come in orig dir */
/* shutकरोwn_comp*/ अणुsCL, sCL, sCW, sCE, sES, sSS, sSR, sCL, sCL, sHAपूर्ण,
/* heartbeat    */ अणुsHS, sCL, sCW, sCE, sES, sSS, sSR, sSA, sHS, sHAपूर्ण,
/* heartbeat_ack*/ अणुsCL, sCL, sCW, sCE, sES, sSS, sSR, sSA, sHS, sHAपूर्ण
	पूर्ण,
	अणु
/*	REPLY	*/
/*                  sNO, sCL, sCW, sCE, sES, sSS, sSR, sSA, sHS, sHA */
/* init         */ अणुsIV, sCL, sCW, sCE, sES, sSS, sSR, sSA, sIV, sHAपूर्ण,/* INIT in sCL Big TODO */
/* init_ack     */ अणुsIV, sCW, sCW, sCE, sES, sSS, sSR, sSA, sIV, sHAपूर्ण,
/* पात        */ अणुsIV, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sIV, sCLपूर्ण,
/* shutकरोwn     */ अणुsIV, sCL, sCW, sCE, sSR, sSS, sSR, sSA, sIV, sSRपूर्ण,
/* shutकरोwn_ack */ अणुsIV, sCL, sCW, sCE, sES, sSA, sSA, sSA, sIV, sHAपूर्ण,
/* error        */ अणुsIV, sCL, sCW, sCL, sES, sSS, sSR, sSA, sIV, sHAपूर्ण,
/* cookie_echo  */ अणुsIV, sCL, sCW, sCE, sES, sSS, sSR, sSA, sIV, sHAपूर्ण,/* Can't come in reply dir */
/* cookie_ack   */ अणुsIV, sCL, sCW, sES, sES, sSS, sSR, sSA, sIV, sHAपूर्ण,
/* shutकरोwn_comp*/ अणुsIV, sCL, sCW, sCE, sES, sSS, sSR, sCL, sIV, sHAपूर्ण,
/* heartbeat    */ अणुsIV, sCL, sCW, sCE, sES, sSS, sSR, sSA, sHS, sHAपूर्ण,
/* heartbeat_ack*/ अणुsIV, sCL, sCW, sCE, sES, sSS, sSR, sSA, sHA, sHAपूर्ण
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
/* Prपूर्णांक out the निजी part of the conntrack. */
अटल व्योम sctp_prपूर्णांक_conntrack(काष्ठा seq_file *s, काष्ठा nf_conn *ct)
अणु
	seq_म_लिखो(s, "%s ", sctp_conntrack_names[ct->proto.sctp.state]);
पूर्ण
#पूर्ण_अगर

#घोषणा क्रम_each_sctp_chunk(skb, sch, _sch, offset, dataoff, count)	\
क्रम ((offset) = (dataoff) + माप(काष्ठा sctphdr), (count) = 0;	\
	(offset) < (skb)->len &&					\
	((sch) = skb_header_poपूर्णांकer((skb), (offset), माप(_sch), &(_sch)));	\
	(offset) += (ntohs((sch)->length) + 3) & ~3, (count)++)

/* Some validity checks to make sure the chunks are fine */
अटल पूर्णांक करो_basic_checks(काष्ठा nf_conn *ct,
			   स्थिर काष्ठा sk_buff *skb,
			   अचिन्हित पूर्णांक dataoff,
			   अचिन्हित दीर्घ *map)
अणु
	u_पूर्णांक32_t offset, count;
	काष्ठा sctp_chunkhdr _sch, *sch;
	पूर्णांक flag;

	flag = 0;

	क्रम_each_sctp_chunk (skb, sch, _sch, offset, dataoff, count) अणु
		pr_debug("Chunk Num: %d  Type: %d\n", count, sch->type);

		अगर (sch->type == SCTP_CID_INIT ||
		    sch->type == SCTP_CID_INIT_ACK ||
		    sch->type == SCTP_CID_SHUTDOWN_COMPLETE)
			flag = 1;

		/*
		 * Cookie Ack/Echo chunks not the first OR
		 * Init / Init Ack / Shutकरोwn compl chunks not the only chunks
		 * OR zero-length.
		 */
		अगर (((sch->type == SCTP_CID_COOKIE_ACK ||
		      sch->type == SCTP_CID_COOKIE_ECHO ||
		      flag) &&
		     count != 0) || !sch->length) अणु
			pr_debug("Basic checks failed\n");
			वापस 1;
		पूर्ण

		अगर (map)
			set_bit(sch->type, map);
	पूर्ण

	pr_debug("Basic checks passed\n");
	वापस count == 0;
पूर्ण

अटल पूर्णांक sctp_new_state(क्रमागत ip_conntrack_dir dir,
			  क्रमागत sctp_conntrack cur_state,
			  पूर्णांक chunk_type)
अणु
	पूर्णांक i;

	pr_debug("Chunk type: %d\n", chunk_type);

	चयन (chunk_type) अणु
	हाल SCTP_CID_INIT:
		pr_debug("SCTP_CID_INIT\n");
		i = 0;
		अवरोध;
	हाल SCTP_CID_INIT_ACK:
		pr_debug("SCTP_CID_INIT_ACK\n");
		i = 1;
		अवरोध;
	हाल SCTP_CID_ABORT:
		pr_debug("SCTP_CID_ABORT\n");
		i = 2;
		अवरोध;
	हाल SCTP_CID_SHUTDOWN:
		pr_debug("SCTP_CID_SHUTDOWN\n");
		i = 3;
		अवरोध;
	हाल SCTP_CID_SHUTDOWN_ACK:
		pr_debug("SCTP_CID_SHUTDOWN_ACK\n");
		i = 4;
		अवरोध;
	हाल SCTP_CID_ERROR:
		pr_debug("SCTP_CID_ERROR\n");
		i = 5;
		अवरोध;
	हाल SCTP_CID_COOKIE_ECHO:
		pr_debug("SCTP_CID_COOKIE_ECHO\n");
		i = 6;
		अवरोध;
	हाल SCTP_CID_COOKIE_ACK:
		pr_debug("SCTP_CID_COOKIE_ACK\n");
		i = 7;
		अवरोध;
	हाल SCTP_CID_SHUTDOWN_COMPLETE:
		pr_debug("SCTP_CID_SHUTDOWN_COMPLETE\n");
		i = 8;
		अवरोध;
	हाल SCTP_CID_HEARTBEAT:
		pr_debug("SCTP_CID_HEARTBEAT");
		i = 9;
		अवरोध;
	हाल SCTP_CID_HEARTBEAT_ACK:
		pr_debug("SCTP_CID_HEARTBEAT_ACK");
		i = 10;
		अवरोध;
	शेष:
		/* Other chunks like DATA or SACK करो not change the state */
		pr_debug("Unknown chunk type, Will stay in %s\n",
			 sctp_conntrack_names[cur_state]);
		वापस cur_state;
	पूर्ण

	pr_debug("dir: %d   cur_state: %s  chunk_type: %d  new_state: %s\n",
		 dir, sctp_conntrack_names[cur_state], chunk_type,
		 sctp_conntrack_names[sctp_conntracks[dir][i][cur_state]]);

	वापस sctp_conntracks[dir][i][cur_state];
पूर्ण

/* Don't need lock here: this conntrack not in circulation yet */
अटल noअंतरभूत bool
sctp_new(काष्ठा nf_conn *ct, स्थिर काष्ठा sk_buff *skb,
	 स्थिर काष्ठा sctphdr *sh, अचिन्हित पूर्णांक dataoff)
अणु
	क्रमागत sctp_conntrack new_state;
	स्थिर काष्ठा sctp_chunkhdr *sch;
	काष्ठा sctp_chunkhdr _sch;
	u32 offset, count;

	स_रखो(&ct->proto.sctp, 0, माप(ct->proto.sctp));
	new_state = SCTP_CONNTRACK_MAX;
	क्रम_each_sctp_chunk(skb, sch, _sch, offset, dataoff, count) अणु
		new_state = sctp_new_state(IP_CT_सूची_ORIGINAL,
					   SCTP_CONNTRACK_NONE, sch->type);

		/* Invalid: delete conntrack */
		अगर (new_state == SCTP_CONNTRACK_NONE ||
		    new_state == SCTP_CONNTRACK_MAX) अणु
			pr_debug("nf_conntrack_sctp: invalid new deleting.\n");
			वापस false;
		पूर्ण

		/* Copy the vtag पूर्णांकo the state info */
		अगर (sch->type == SCTP_CID_INIT) अणु
			काष्ठा sctp_inithdr _inithdr, *ih;
			/* Sec 8.5.1 (A) */
			अगर (sh->vtag)
				वापस false;

			ih = skb_header_poपूर्णांकer(skb, offset + माप(_sch),
						माप(_inithdr), &_inithdr);
			अगर (!ih)
				वापस false;

			pr_debug("Setting vtag %x for new conn\n",
				 ih->init_tag);

			ct->proto.sctp.vtag[IP_CT_सूची_REPLY] = ih->init_tag;
		पूर्ण अन्यथा अगर (sch->type == SCTP_CID_HEARTBEAT) अणु
			pr_debug("Setting vtag %x for secondary conntrack\n",
				 sh->vtag);
			ct->proto.sctp.vtag[IP_CT_सूची_ORIGINAL] = sh->vtag;
		पूर्ण अन्यथा अणु
		/* If it is a shutकरोwn ack OOTB packet, we expect a वापस
		   shutकरोwn complete, otherwise an ABORT Sec 8.4 (5) and (8) */
			pr_debug("Setting vtag %x for new conn OOTB\n",
				 sh->vtag);
			ct->proto.sctp.vtag[IP_CT_सूची_REPLY] = sh->vtag;
		पूर्ण

		ct->proto.sctp.state = SCTP_CONNTRACK_NONE;
	पूर्ण

	वापस true;
पूर्ण

अटल bool sctp_error(काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक dataoff,
		       स्थिर काष्ठा nf_hook_state *state)
अणु
	स्थिर काष्ठा sctphdr *sh;
	स्थिर अक्षर *logmsg;

	अगर (skb->len < dataoff + माप(काष्ठा sctphdr)) अणु
		logmsg = "nf_ct_sctp: short packet ";
		जाओ out_invalid;
	पूर्ण
	अगर (state->hook == NF_INET_PRE_ROUTING &&
	    state->net->ct.sysctl_checksum &&
	    skb->ip_summed == CHECKSUM_NONE) अणु
		अगर (skb_ensure_writable(skb, dataoff + माप(*sh))) अणु
			logmsg = "nf_ct_sctp: failed to read header ";
			जाओ out_invalid;
		पूर्ण
		sh = (स्थिर काष्ठा sctphdr *)(skb->data + dataoff);
		अगर (sh->checksum != sctp_compute_cksum(skb, dataoff)) अणु
			logmsg = "nf_ct_sctp: bad CRC ";
			जाओ out_invalid;
		पूर्ण
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण
	वापस false;
out_invalid:
	nf_l4proto_log_invalid(skb, state->net, state->pf, IPPROTO_SCTP, "%s", logmsg);
	वापस true;
पूर्ण

/* Returns verdict क्रम packet, or -NF_ACCEPT क्रम invalid. */
पूर्णांक nf_conntrack_sctp_packet(काष्ठा nf_conn *ct,
			     काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक dataoff,
			     क्रमागत ip_conntrack_info ctinfo,
			     स्थिर काष्ठा nf_hook_state *state)
अणु
	क्रमागत sctp_conntrack new_state, old_state;
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	स्थिर काष्ठा sctphdr *sh;
	काष्ठा sctphdr _sctph;
	स्थिर काष्ठा sctp_chunkhdr *sch;
	काष्ठा sctp_chunkhdr _sch;
	u_पूर्णांक32_t offset, count;
	अचिन्हित पूर्णांक *समयouts;
	अचिन्हित दीर्घ map[256 / माप(अचिन्हित दीर्घ)] = अणु 0 पूर्ण;
	bool ignore = false;

	अगर (sctp_error(skb, dataoff, state))
		वापस -NF_ACCEPT;

	sh = skb_header_poपूर्णांकer(skb, dataoff, माप(_sctph), &_sctph);
	अगर (sh == शून्य)
		जाओ out;

	अगर (करो_basic_checks(ct, skb, dataoff, map) != 0)
		जाओ out;

	अगर (!nf_ct_is_confirmed(ct)) अणु
		/* If an OOTB packet has any of these chunks discard (Sec 8.4) */
		अगर (test_bit(SCTP_CID_ABORT, map) ||
		    test_bit(SCTP_CID_SHUTDOWN_COMPLETE, map) ||
		    test_bit(SCTP_CID_COOKIE_ACK, map))
			वापस -NF_ACCEPT;

		अगर (!sctp_new(ct, skb, sh, dataoff))
			वापस -NF_ACCEPT;
	पूर्ण

	/* Check the verअगरication tag (Sec 8.5) */
	अगर (!test_bit(SCTP_CID_INIT, map) &&
	    !test_bit(SCTP_CID_SHUTDOWN_COMPLETE, map) &&
	    !test_bit(SCTP_CID_COOKIE_ECHO, map) &&
	    !test_bit(SCTP_CID_ABORT, map) &&
	    !test_bit(SCTP_CID_SHUTDOWN_ACK, map) &&
	    !test_bit(SCTP_CID_HEARTBEAT, map) &&
	    !test_bit(SCTP_CID_HEARTBEAT_ACK, map) &&
	    sh->vtag != ct->proto.sctp.vtag[dir]) अणु
		pr_debug("Verification tag check failed\n");
		जाओ out;
	पूर्ण

	old_state = new_state = SCTP_CONNTRACK_NONE;
	spin_lock_bh(&ct->lock);
	क्रम_each_sctp_chunk (skb, sch, _sch, offset, dataoff, count) अणु
		/* Special हालs of Verअगरication tag check (Sec 8.5.1) */
		अगर (sch->type == SCTP_CID_INIT) अणु
			/* Sec 8.5.1 (A) */
			अगर (sh->vtag != 0)
				जाओ out_unlock;
		पूर्ण अन्यथा अगर (sch->type == SCTP_CID_ABORT) अणु
			/* Sec 8.5.1 (B) */
			अगर (sh->vtag != ct->proto.sctp.vtag[dir] &&
			    sh->vtag != ct->proto.sctp.vtag[!dir])
				जाओ out_unlock;
		पूर्ण अन्यथा अगर (sch->type == SCTP_CID_SHUTDOWN_COMPLETE) अणु
			/* Sec 8.5.1 (C) */
			अगर (sh->vtag != ct->proto.sctp.vtag[dir] &&
			    sh->vtag != ct->proto.sctp.vtag[!dir] &&
			    sch->flags & SCTP_CHUNK_FLAG_T)
				जाओ out_unlock;
		पूर्ण अन्यथा अगर (sch->type == SCTP_CID_COOKIE_ECHO) अणु
			/* Sec 8.5.1 (D) */
			अगर (sh->vtag != ct->proto.sctp.vtag[dir])
				जाओ out_unlock;
		पूर्ण अन्यथा अगर (sch->type == SCTP_CID_HEARTBEAT) अणु
			अगर (ct->proto.sctp.vtag[dir] == 0) अणु
				pr_debug("Setting %d vtag %x for dir %d\n", sch->type, sh->vtag, dir);
				ct->proto.sctp.vtag[dir] = sh->vtag;
			पूर्ण अन्यथा अगर (sh->vtag != ct->proto.sctp.vtag[dir]) अणु
				अगर (test_bit(SCTP_CID_DATA, map) || ignore)
					जाओ out_unlock;

				ct->proto.sctp.flags |= SCTP_FLAG_HEARTBEAT_VTAG_FAILED;
				ct->proto.sctp.last_dir = dir;
				ignore = true;
				जारी;
			पूर्ण अन्यथा अगर (ct->proto.sctp.flags & SCTP_FLAG_HEARTBEAT_VTAG_FAILED) अणु
				ct->proto.sctp.flags &= ~SCTP_FLAG_HEARTBEAT_VTAG_FAILED;
			पूर्ण
		पूर्ण अन्यथा अगर (sch->type == SCTP_CID_HEARTBEAT_ACK) अणु
			अगर (ct->proto.sctp.vtag[dir] == 0) अणु
				pr_debug("Setting vtag %x for dir %d\n",
					 sh->vtag, dir);
				ct->proto.sctp.vtag[dir] = sh->vtag;
			पूर्ण अन्यथा अगर (sh->vtag != ct->proto.sctp.vtag[dir]) अणु
				अगर (test_bit(SCTP_CID_DATA, map) || ignore)
					जाओ out_unlock;

				अगर ((ct->proto.sctp.flags & SCTP_FLAG_HEARTBEAT_VTAG_FAILED) == 0 ||
				    ct->proto.sctp.last_dir == dir)
					जाओ out_unlock;

				ct->proto.sctp.flags &= ~SCTP_FLAG_HEARTBEAT_VTAG_FAILED;
				ct->proto.sctp.vtag[dir] = sh->vtag;
				ct->proto.sctp.vtag[!dir] = 0;
			पूर्ण अन्यथा अगर (ct->proto.sctp.flags & SCTP_FLAG_HEARTBEAT_VTAG_FAILED) अणु
				ct->proto.sctp.flags &= ~SCTP_FLAG_HEARTBEAT_VTAG_FAILED;
			पूर्ण
		पूर्ण

		old_state = ct->proto.sctp.state;
		new_state = sctp_new_state(dir, old_state, sch->type);

		/* Invalid */
		अगर (new_state == SCTP_CONNTRACK_MAX) अणु
			pr_debug("nf_conntrack_sctp: Invalid dir=%i ctype=%u "
				 "conntrack=%u\n",
				 dir, sch->type, old_state);
			जाओ out_unlock;
		पूर्ण

		/* If it is an INIT or an INIT ACK note करोwn the vtag */
		अगर (sch->type == SCTP_CID_INIT ||
		    sch->type == SCTP_CID_INIT_ACK) अणु
			काष्ठा sctp_inithdr _inithdr, *ih;

			ih = skb_header_poपूर्णांकer(skb, offset + माप(_sch),
						माप(_inithdr), &_inithdr);
			अगर (ih == शून्य)
				जाओ out_unlock;
			pr_debug("Setting vtag %x for dir %d\n",
				 ih->init_tag, !dir);
			ct->proto.sctp.vtag[!dir] = ih->init_tag;
		पूर्ण

		ct->proto.sctp.state = new_state;
		अगर (old_state != new_state)
			nf_conntrack_event_cache(IPCT_PROTOINFO, ct);
	पूर्ण
	spin_unlock_bh(&ct->lock);

	/* allow but करो not refresh समयout */
	अगर (ignore)
		वापस NF_ACCEPT;

	समयouts = nf_ct_समयout_lookup(ct);
	अगर (!समयouts)
		समयouts = nf_sctp_pernet(nf_ct_net(ct))->समयouts;

	nf_ct_refresh_acct(ct, ctinfo, skb, समयouts[new_state]);

	अगर (old_state == SCTP_CONNTRACK_COOKIE_ECHOED &&
	    dir == IP_CT_सूची_REPLY &&
	    new_state == SCTP_CONNTRACK_ESTABLISHED) अणु
		pr_debug("Setting assured bit\n");
		set_bit(IPS_ASSURED_BIT, &ct->status);
		nf_conntrack_event_cache(IPCT_ASSURED, ct);
	पूर्ण

	वापस NF_ACCEPT;

out_unlock:
	spin_unlock_bh(&ct->lock);
out:
	वापस -NF_ACCEPT;
पूर्ण

अटल bool sctp_can_early_drop(स्थिर काष्ठा nf_conn *ct)
अणु
	चयन (ct->proto.sctp.state) अणु
	हाल SCTP_CONNTRACK_SHUTDOWN_SENT:
	हाल SCTP_CONNTRACK_SHUTDOWN_RECD:
	हाल SCTP_CONNTRACK_SHUTDOWN_ACK_SENT:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_conntrack.h>

अटल पूर्णांक sctp_to_nlattr(काष्ठा sk_buff *skb, काष्ठा nlattr *nla,
			  काष्ठा nf_conn *ct, bool destroy)
अणु
	काष्ठा nlattr *nest_parms;

	spin_lock_bh(&ct->lock);
	nest_parms = nla_nest_start(skb, CTA_PROTOINFO_SCTP);
	अगर (!nest_parms)
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, CTA_PROTOINFO_SCTP_STATE, ct->proto.sctp.state))
		जाओ nla_put_failure;

	अगर (destroy)
		जाओ skip_state;

	अगर (nla_put_be32(skb, CTA_PROTOINFO_SCTP_VTAG_ORIGINAL,
			 ct->proto.sctp.vtag[IP_CT_सूची_ORIGINAL]) ||
	    nla_put_be32(skb, CTA_PROTOINFO_SCTP_VTAG_REPLY,
			 ct->proto.sctp.vtag[IP_CT_सूची_REPLY]))
		जाओ nla_put_failure;

skip_state:
	spin_unlock_bh(&ct->lock);
	nla_nest_end(skb, nest_parms);

	वापस 0;

nla_put_failure:
	spin_unlock_bh(&ct->lock);
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nla_policy sctp_nla_policy[CTA_PROTOINFO_SCTP_MAX+1] = अणु
	[CTA_PROTOINFO_SCTP_STATE]	    = अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTOINFO_SCTP_VTAG_ORIGINAL]  = अणु .type = NLA_U32 पूर्ण,
	[CTA_PROTOINFO_SCTP_VTAG_REPLY]     = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

#घोषणा SCTP_NLATTR_SIZE ( \
		NLA_ALIGN(NLA_HDRLEN + 1) + \
		NLA_ALIGN(NLA_HDRLEN + 4) + \
		NLA_ALIGN(NLA_HDRLEN + 4))

अटल पूर्णांक nlattr_to_sctp(काष्ठा nlattr *cda[], काष्ठा nf_conn *ct)
अणु
	काष्ठा nlattr *attr = cda[CTA_PROTOINFO_SCTP];
	काष्ठा nlattr *tb[CTA_PROTOINFO_SCTP_MAX+1];
	पूर्णांक err;

	/* updates may not contain the पूर्णांकernal protocol info, skip parsing */
	अगर (!attr)
		वापस 0;

	err = nla_parse_nested_deprecated(tb, CTA_PROTOINFO_SCTP_MAX, attr,
					  sctp_nla_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[CTA_PROTOINFO_SCTP_STATE] ||
	    !tb[CTA_PROTOINFO_SCTP_VTAG_ORIGINAL] ||
	    !tb[CTA_PROTOINFO_SCTP_VTAG_REPLY])
		वापस -EINVAL;

	spin_lock_bh(&ct->lock);
	ct->proto.sctp.state = nla_get_u8(tb[CTA_PROTOINFO_SCTP_STATE]);
	ct->proto.sctp.vtag[IP_CT_सूची_ORIGINAL] =
		nla_get_be32(tb[CTA_PROTOINFO_SCTP_VTAG_ORIGINAL]);
	ct->proto.sctp.vtag[IP_CT_सूची_REPLY] =
		nla_get_be32(tb[CTA_PROTOINFO_SCTP_VTAG_REPLY]);
	spin_unlock_bh(&ct->lock);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_ctसमयout.h>

अटल पूर्णांक sctp_समयout_nlattr_to_obj(काष्ठा nlattr *tb[],
				      काष्ठा net *net, व्योम *data)
अणु
	अचिन्हित पूर्णांक *समयouts = data;
	काष्ठा nf_sctp_net *sn = nf_sctp_pernet(net);
	पूर्णांक i;

	अगर (!समयouts)
		समयouts = sn->समयouts;

	/* set शेष SCTP समयouts. */
	क्रम (i=0; i<SCTP_CONNTRACK_MAX; i++)
		समयouts[i] = sn->समयouts[i];

	/* there's a 1:1 mapping between attributes and protocol states. */
	क्रम (i=CTA_TIMEOUT_SCTP_UNSPEC+1; i<CTA_TIMEOUT_SCTP_MAX+1; i++) अणु
		अगर (tb[i]) अणु
			समयouts[i] = ntohl(nla_get_be32(tb[i])) * HZ;
		पूर्ण
	पूर्ण

	समयouts[CTA_TIMEOUT_SCTP_UNSPEC] = समयouts[CTA_TIMEOUT_SCTP_CLOSED];
	वापस 0;
पूर्ण

अटल पूर्णांक
sctp_समयout_obj_to_nlattr(काष्ठा sk_buff *skb, स्थिर व्योम *data)
अणु
        स्थिर अचिन्हित पूर्णांक *समयouts = data;
	पूर्णांक i;

	क्रम (i=CTA_TIMEOUT_SCTP_UNSPEC+1; i<CTA_TIMEOUT_SCTP_MAX+1; i++) अणु
	        अगर (nla_put_be32(skb, i, htonl(समयouts[i] / HZ)))
			जाओ nla_put_failure;
	पूर्ण
        वापस 0;

nla_put_failure:
        वापस -ENOSPC;
पूर्ण

अटल स्थिर काष्ठा nla_policy
sctp_समयout_nla_policy[CTA_TIMEOUT_SCTP_MAX+1] = अणु
	[CTA_TIMEOUT_SCTP_CLOSED]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_SCTP_COOKIE_WAIT]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_SCTP_COOKIE_ECHOED]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_SCTP_ESTABLISHED]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_SCTP_SHUTDOWN_SENT]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_SCTP_SHUTDOWN_RECD]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_SCTP_SHUTDOWN_ACK_SENT]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_SCTP_HEARTBEAT_SENT]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_SCTP_HEARTBEAT_ACKED]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

व्योम nf_conntrack_sctp_init_net(काष्ठा net *net)
अणु
	काष्ठा nf_sctp_net *sn = nf_sctp_pernet(net);
	पूर्णांक i;

	क्रम (i = 0; i < SCTP_CONNTRACK_MAX; i++)
		sn->समयouts[i] = sctp_समयouts[i];

	/* समयouts[0] is unused, init it so ->समयouts[0] contains
	 * 'new' समयout, like udp or icmp.
	 */
	sn->समयouts[0] = sctp_समयouts[SCTP_CONNTRACK_CLOSED];
पूर्ण

स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_sctp = अणु
	.l4proto 		= IPPROTO_SCTP,
#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
	.prपूर्णांक_conntrack	= sctp_prपूर्णांक_conntrack,
#पूर्ण_अगर
	.can_early_drop		= sctp_can_early_drop,
#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)
	.nlattr_size		= SCTP_NLATTR_SIZE,
	.to_nlattr		= sctp_to_nlattr,
	.from_nlattr		= nlattr_to_sctp,
	.tuple_to_nlattr	= nf_ct_port_tuple_to_nlattr,
	.nlattr_tuple_size	= nf_ct_port_nlattr_tuple_size,
	.nlattr_to_tuple	= nf_ct_port_nlattr_to_tuple,
	.nla_policy		= nf_ct_port_nla_policy,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	.ctnl_समयout		= अणु
		.nlattr_to_obj	= sctp_समयout_nlattr_to_obj,
		.obj_to_nlattr	= sctp_समयout_obj_to_nlattr,
		.nlattr_max	= CTA_TIMEOUT_SCTP_MAX,
		.obj_size	= माप(अचिन्हित पूर्णांक) * SCTP_CONNTRACK_MAX,
		.nla_policy	= sctp_समयout_nla_policy,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */
पूर्ण;
