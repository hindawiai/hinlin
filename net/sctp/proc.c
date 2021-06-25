<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * Copyright (c) 2003 International Business Machines, Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Sridhar Samudrala <sri@us.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/ip.h> /* क्रम snmp_fold_field */

अटल स्थिर काष्ठा snmp_mib sctp_snmp_list[] = अणु
	SNMP_MIB_ITEM("SctpCurrEstab", SCTP_MIB_CURRESTAB),
	SNMP_MIB_ITEM("SctpActiveEstabs", SCTP_MIB_ACTIVEESTABS),
	SNMP_MIB_ITEM("SctpPassiveEstabs", SCTP_MIB_PASSIVEESTABS),
	SNMP_MIB_ITEM("SctpAborteds", SCTP_MIB_ABORTEDS),
	SNMP_MIB_ITEM("SctpShutdowns", SCTP_MIB_SHUTDOWNS),
	SNMP_MIB_ITEM("SctpOutOfBlues", SCTP_MIB_OUTOFBLUES),
	SNMP_MIB_ITEM("SctpChecksumErrors", SCTP_MIB_CHECKSUMERRORS),
	SNMP_MIB_ITEM("SctpOutCtrlChunks", SCTP_MIB_OUTCTRLCHUNKS),
	SNMP_MIB_ITEM("SctpOutOrderChunks", SCTP_MIB_OUTORDERCHUNKS),
	SNMP_MIB_ITEM("SctpOutUnorderChunks", SCTP_MIB_OUTUNORDERCHUNKS),
	SNMP_MIB_ITEM("SctpInCtrlChunks", SCTP_MIB_INCTRLCHUNKS),
	SNMP_MIB_ITEM("SctpInOrderChunks", SCTP_MIB_INORDERCHUNKS),
	SNMP_MIB_ITEM("SctpInUnorderChunks", SCTP_MIB_INUNORDERCHUNKS),
	SNMP_MIB_ITEM("SctpFragUsrMsgs", SCTP_MIB_FRAGUSRMSGS),
	SNMP_MIB_ITEM("SctpReasmUsrMsgs", SCTP_MIB_REASMUSRMSGS),
	SNMP_MIB_ITEM("SctpOutSCTPPacks", SCTP_MIB_OUTSCTPPACKS),
	SNMP_MIB_ITEM("SctpInSCTPPacks", SCTP_MIB_INSCTPPACKS),
	SNMP_MIB_ITEM("SctpT1InitExpireds", SCTP_MIB_T1_INIT_EXPIREDS),
	SNMP_MIB_ITEM("SctpT1CookieExpireds", SCTP_MIB_T1_COOKIE_EXPIREDS),
	SNMP_MIB_ITEM("SctpT2ShutdownExpireds", SCTP_MIB_T2_SHUTDOWN_EXPIREDS),
	SNMP_MIB_ITEM("SctpT3RtxExpireds", SCTP_MIB_T3_RTX_EXPIREDS),
	SNMP_MIB_ITEM("SctpT4RtoExpireds", SCTP_MIB_T4_RTO_EXPIREDS),
	SNMP_MIB_ITEM("SctpT5ShutdownGuardExpireds", SCTP_MIB_T5_SHUTDOWN_GUARD_EXPIREDS),
	SNMP_MIB_ITEM("SctpDelaySackExpireds", SCTP_MIB_DELAY_SACK_EXPIREDS),
	SNMP_MIB_ITEM("SctpAutocloseExpireds", SCTP_MIB_AUTOCLOSE_EXPIREDS),
	SNMP_MIB_ITEM("SctpT3Retransmits", SCTP_MIB_T3_RETRANSMITS),
	SNMP_MIB_ITEM("SctpPmtudRetransmits", SCTP_MIB_PMTUD_RETRANSMITS),
	SNMP_MIB_ITEM("SctpFastRetransmits", SCTP_MIB_FAST_RETRANSMITS),
	SNMP_MIB_ITEM("SctpInPktSoftirq", SCTP_MIB_IN_PKT_SOFTIRQ),
	SNMP_MIB_ITEM("SctpInPktBacklog", SCTP_MIB_IN_PKT_BACKLOG),
	SNMP_MIB_ITEM("SctpInPktDiscards", SCTP_MIB_IN_PKT_DISCARDS),
	SNMP_MIB_ITEM("SctpInDataChunkDiscards", SCTP_MIB_IN_DATA_CHUNK_DISCARDS),
	SNMP_MIB_SENTINEL
पूर्ण;

/* Display sctp snmp mib statistics(/proc/net/sctp/snmp). */
अटल पूर्णांक sctp_snmp_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अचिन्हित दीर्घ buff[SCTP_MIB_MAX];
	काष्ठा net *net = seq->निजी;
	पूर्णांक i;

	स_रखो(buff, 0, माप(अचिन्हित दीर्घ) * SCTP_MIB_MAX);

	snmp_get_cpu_field_batch(buff, sctp_snmp_list,
				 net->sctp.sctp_statistics);
	क्रम (i = 0; sctp_snmp_list[i].name; i++)
		seq_म_लिखो(seq, "%-32s\t%ld\n", sctp_snmp_list[i].name,
						buff[i]);

	वापस 0;
पूर्ण

/* Dump local addresses of an association/endpoपूर्णांक. */
अटल व्योम sctp_seq_dump_local_addrs(काष्ठा seq_file *seq, काष्ठा sctp_ep_common *epb)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_sockaddr_entry *laddr;
	काष्ठा sctp_transport *peer;
	जोड़ sctp_addr *addr, *primary = शून्य;
	काष्ठा sctp_af *af;

	अगर (epb->type == SCTP_EP_TYPE_ASSOCIATION) अणु
		asoc = sctp_assoc(epb);

		peer = asoc->peer.primary_path;
		अगर (unlikely(peer == शून्य)) अणु
			WARN(1, "Association %p with NULL primary path!\n", asoc);
			वापस;
		पूर्ण

		primary = &peer->saddr;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(laddr, &epb->bind_addr.address_list, list) अणु
		अगर (!laddr->valid)
			जारी;

		addr = &laddr->a;
		af = sctp_get_af_specअगरic(addr->sa.sa_family);
		अगर (primary && af->cmp_addr(addr, primary)) अणु
			seq_म_लिखो(seq, "*");
		पूर्ण
		af->seq_dump_addr(seq, addr);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Dump remote addresses of an association. */
अटल व्योम sctp_seq_dump_remote_addrs(काष्ठा seq_file *seq, काष्ठा sctp_association *assoc)
अणु
	काष्ठा sctp_transport *transport;
	जोड़ sctp_addr *addr, *primary;
	काष्ठा sctp_af *af;

	primary = &assoc->peer.primary_addr;
	list_क्रम_each_entry_rcu(transport, &assoc->peer.transport_addr_list,
			transports) अणु
		addr = &transport->ipaddr;

		af = sctp_get_af_specअगरic(addr->sa.sa_family);
		अगर (af->cmp_addr(addr, primary)) अणु
			seq_म_लिखो(seq, "*");
		पूर्ण
		af->seq_dump_addr(seq, addr);
	पूर्ण
पूर्ण

अटल व्योम *sctp_eps_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	अगर (*pos >= sctp_ep_hashsize)
		वापस शून्य;

	अगर (*pos < 0)
		*pos = 0;

	अगर (*pos == 0)
		seq_म_लिखो(seq, " ENDPT     SOCK   STY SST HBKT LPORT   UID INODE LADDRS\n");

	वापस (व्योम *)pos;
पूर्ण

अटल व्योम sctp_eps_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण


अटल व्योम *sctp_eps_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	अगर (++*pos >= sctp_ep_hashsize)
		वापस शून्य;

	वापस pos;
पूर्ण


/* Display sctp endpoपूर्णांकs (/proc/net/sctp/eps). */
अटल पूर्णांक sctp_eps_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sctp_hashbucket *head;
	काष्ठा sctp_ep_common *epb;
	काष्ठा sctp_endpoपूर्णांक *ep;
	काष्ठा sock *sk;
	पूर्णांक    hash = *(loff_t *)v;

	अगर (hash >= sctp_ep_hashsize)
		वापस -ENOMEM;

	head = &sctp_ep_hashtable[hash];
	पढ़ो_lock_bh(&head->lock);
	sctp_क्रम_each_hentry(epb, &head->chain) अणु
		ep = sctp_ep(epb);
		sk = epb->sk;
		अगर (!net_eq(sock_net(sk), seq_file_net(seq)))
			जारी;
		seq_म_लिखो(seq, "%8pK %8pK %-3d %-3d %-4d %-5d %5u %5lu ", ep, sk,
			   sctp_sk(sk)->type, sk->sk_state, hash,
			   epb->bind_addr.port,
			   from_kuid_munged(seq_user_ns(seq), sock_i_uid(sk)),
			   sock_i_ino(sk));

		sctp_seq_dump_local_addrs(seq, epb);
		seq_म_लिखो(seq, "\n");
	पूर्ण
	पढ़ो_unlock_bh(&head->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations sctp_eps_ops = अणु
	.start = sctp_eps_seq_start,
	.next  = sctp_eps_seq_next,
	.stop  = sctp_eps_seq_stop,
	.show  = sctp_eps_seq_show,
पूर्ण;

काष्ठा sctp_ht_iter अणु
	काष्ठा seq_net_निजी p;
	काष्ठा rhashtable_iter hti;
पूर्ण;

अटल व्योम *sctp_transport_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा sctp_ht_iter *iter = seq->निजी;

	sctp_transport_walk_start(&iter->hti);

	वापस sctp_transport_get_idx(seq_file_net(seq), &iter->hti, *pos);
पूर्ण

अटल व्योम sctp_transport_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sctp_ht_iter *iter = seq->निजी;

	अगर (v && v != SEQ_START_TOKEN) अणु
		काष्ठा sctp_transport *transport = v;

		sctp_transport_put(transport);
	पूर्ण

	sctp_transport_walk_stop(&iter->hti);
पूर्ण

अटल व्योम *sctp_transport_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा sctp_ht_iter *iter = seq->निजी;

	अगर (v && v != SEQ_START_TOKEN) अणु
		काष्ठा sctp_transport *transport = v;

		sctp_transport_put(transport);
	पूर्ण

	++*pos;

	वापस sctp_transport_get_next(seq_file_net(seq), &iter->hti);
पूर्ण

/* Display sctp associations (/proc/net/sctp/assocs). */
अटल पूर्णांक sctp_assocs_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sctp_transport *transport;
	काष्ठा sctp_association *assoc;
	काष्ठा sctp_ep_common *epb;
	काष्ठा sock *sk;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq, " ASSOC     SOCK   STY SST ST HBKT "
				"ASSOC-ID TX_QUEUE RX_QUEUE UID INODE LPORT "
				"RPORT LADDRS <-> RADDRS "
				"HBINT INS OUTS MAXRT T1X T2X RTXC "
				"wmema wmemq sndbuf rcvbuf\n");
		वापस 0;
	पूर्ण

	transport = (काष्ठा sctp_transport *)v;
	assoc = transport->asoc;
	epb = &assoc->base;
	sk = epb->sk;

	seq_म_लिखो(seq,
		   "%8pK %8pK %-3d %-3d %-2d %-4d "
		   "%4d %8d %8d %7u %5lu %-5d %5d ",
		   assoc, sk, sctp_sk(sk)->type, sk->sk_state,
		   assoc->state, 0,
		   assoc->assoc_id,
		   assoc->sndbuf_used,
		   atomic_पढ़ो(&assoc->rmem_alloc),
		   from_kuid_munged(seq_user_ns(seq), sock_i_uid(sk)),
		   sock_i_ino(sk),
		   epb->bind_addr.port,
		   assoc->peer.port);
	seq_म_लिखो(seq, " ");
	sctp_seq_dump_local_addrs(seq, epb);
	seq_म_लिखो(seq, "<-> ");
	sctp_seq_dump_remote_addrs(seq, assoc);
	seq_म_लिखो(seq, "\t%8lu %5d %5d %4d %4d %4d %8d "
		   "%8d %8d %8d %8d",
		assoc->hbपूर्णांकerval, assoc->stream.incnt,
		assoc->stream.outcnt, assoc->max_retrans,
		assoc->init_retries, assoc->shutकरोwn_retries,
		assoc->rtx_data_chunks,
		refcount_पढ़ो(&sk->sk_wmem_alloc),
		sk->sk_wmem_queued,
		sk->sk_sndbuf,
		sk->sk_rcvbuf);
	seq_म_लिखो(seq, "\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations sctp_assoc_ops = अणु
	.start = sctp_transport_seq_start,
	.next  = sctp_transport_seq_next,
	.stop  = sctp_transport_seq_stop,
	.show  = sctp_assocs_seq_show,
पूर्ण;

अटल पूर्णांक sctp_remaddr_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sctp_association *assoc;
	काष्ठा sctp_transport *transport, *tsp;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq, "ADDR ASSOC_ID HB_ACT RTO MAX_PATH_RTX "
				"REM_ADDR_RTX START STATE\n");
		वापस 0;
	पूर्ण

	transport = (काष्ठा sctp_transport *)v;
	assoc = transport->asoc;

	list_क्रम_each_entry_rcu(tsp, &assoc->peer.transport_addr_list,
				transports) अणु
		/*
		 * The remote address (ADDR)
		 */
		tsp->af_specअगरic->seq_dump_addr(seq, &tsp->ipaddr);
		seq_म_लिखो(seq, " ");
		/*
		 * The association ID (ASSOC_ID)
		 */
		seq_म_लिखो(seq, "%d ", tsp->asoc->assoc_id);

		/*
		 * If the Heartbeat is active (HB_ACT)
		 * Note: 1 = Active, 0 = Inactive
		 */
		seq_म_लिखो(seq, "%d ", समयr_pending(&tsp->hb_समयr));

		/*
		 * Retransmit समय out (RTO)
		 */
		seq_म_लिखो(seq, "%lu ", tsp->rto);

		/*
		 * Maximum path retransmit count (PATH_MAX_RTX)
		 */
		seq_म_लिखो(seq, "%d ", tsp->pathmaxrxt);

		/*
		 * remote address retransmit count (REM_ADDR_RTX)
		 * Note: We करोn't have a way to tally this at the moment
		 * so lets just leave it as zero क्रम the moment
		 */
		seq_माला_दो(seq, "0 ");

		/*
		 * remote address start समय (START).  This is also not
		 * currently implemented, but we can record it with a
		 * jअगरfies marker in a subsequent patch
		 */
		seq_माला_दो(seq, "0 ");

		/*
		 * The current state of this destination. I.e.
		 * SCTP_ACTIVE, SCTP_INACTIVE, ...
		 */
		seq_म_लिखो(seq, "%d", tsp->state);

		seq_म_लिखो(seq, "\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations sctp_remaddr_ops = अणु
	.start = sctp_transport_seq_start,
	.next  = sctp_transport_seq_next,
	.stop  = sctp_transport_seq_stop,
	.show  = sctp_remaddr_seq_show,
पूर्ण;

/* Set up the proc fs entry क्रम the SCTP protocol. */
पूर्णांक __net_init sctp_proc_init(काष्ठा net *net)
अणु
	net->sctp.proc_net_sctp = proc_net_सूची_गढ़ो(net, "sctp", net->proc_net);
	अगर (!net->sctp.proc_net_sctp)
		वापस -ENOMEM;
	अगर (!proc_create_net_single("snmp", 0444, net->sctp.proc_net_sctp,
			 sctp_snmp_seq_show, शून्य))
		जाओ cleanup;
	अगर (!proc_create_net("eps", 0444, net->sctp.proc_net_sctp,
			&sctp_eps_ops, माप(काष्ठा seq_net_निजी)))
		जाओ cleanup;
	अगर (!proc_create_net("assocs", 0444, net->sctp.proc_net_sctp,
			&sctp_assoc_ops, माप(काष्ठा sctp_ht_iter)))
		जाओ cleanup;
	अगर (!proc_create_net("remaddr", 0444, net->sctp.proc_net_sctp,
			&sctp_remaddr_ops, माप(काष्ठा sctp_ht_iter)))
		जाओ cleanup;
	वापस 0;

cleanup:
	हटाओ_proc_subtree("sctp", net->proc_net);
	net->sctp.proc_net_sctp = शून्य;
	वापस -ENOMEM;
पूर्ण
