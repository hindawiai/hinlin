<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rculist.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/socket.h>
#समावेश <net/inet_sock.h>
#समावेश <net/kcm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/tcp.h>

#अगर_घोषित CONFIG_PROC_FS
अटल काष्ठा kcm_mux *kcm_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा kcm_net *knet = net_generic(net, kcm_net_id);

	वापस list_first_or_null_rcu(&knet->mux_list,
				      काष्ठा kcm_mux, kcm_mux_list);
पूर्ण

अटल काष्ठा kcm_mux *kcm_get_next(काष्ठा kcm_mux *mux)
अणु
	काष्ठा kcm_net *knet = mux->knet;

	वापस list_next_or_null_rcu(&knet->mux_list, &mux->kcm_mux_list,
				     काष्ठा kcm_mux, kcm_mux_list);
पूर्ण

अटल काष्ठा kcm_mux *kcm_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा kcm_net *knet = net_generic(net, kcm_net_id);
	काष्ठा kcm_mux *m;

	list_क्रम_each_entry_rcu(m, &knet->mux_list, kcm_mux_list) अणु
		अगर (!pos)
			वापस m;
		--pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *kcm_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	व्योम *p;

	अगर (v == SEQ_START_TOKEN)
		p = kcm_get_first(seq);
	अन्यथा
		p = kcm_get_next(v);
	++*pos;
	वापस p;
पूर्ण

अटल व्योम *kcm_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rcu)
अणु
	rcu_पढ़ो_lock();

	अगर (!*pos)
		वापस SEQ_START_TOKEN;
	अन्यथा
		वापस kcm_get_idx(seq, *pos - 1);
पूर्ण

अटल व्योम kcm_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rcu)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

काष्ठा kcm_proc_mux_state अणु
	काष्ठा seq_net_निजी p;
	पूर्णांक idx;
पूर्ण;

अटल व्योम kcm_क्रमmat_mux_header(काष्ठा seq_file *seq)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा kcm_net *knet = net_generic(net, kcm_net_id);

	seq_म_लिखो(seq,
		   "*** KCM statistics (%d MUX) ****\n",
		   knet->count);

	seq_म_लिखो(seq,
		   "%-14s %-10s %-16s %-10s %-16s %-8s %-8s %-8s %-8s %s",
		   "Object",
		   "RX-Msgs",
		   "RX-Bytes",
		   "TX-Msgs",
		   "TX-Bytes",
		   "Recv-Q",
		   "Rmem",
		   "Send-Q",
		   "Smem",
		   "Status");

	/* XXX: pdsts header stuff here */
	seq_माला_दो(seq, "\n");
पूर्ण

अटल व्योम kcm_क्रमmat_sock(काष्ठा kcm_sock *kcm, काष्ठा seq_file *seq,
			    पूर्णांक i, पूर्णांक *len)
अणु
	seq_म_लिखो(seq,
		   "   kcm-%-7u %-10llu %-16llu %-10llu %-16llu %-8d %-8d %-8d %-8s ",
		   kcm->index,
		   kcm->stats.rx_msgs,
		   kcm->stats.rx_bytes,
		   kcm->stats.tx_msgs,
		   kcm->stats.tx_bytes,
		   kcm->sk.sk_receive_queue.qlen,
		   sk_rmem_alloc_get(&kcm->sk),
		   kcm->sk.sk_ग_लिखो_queue.qlen,
		   "-");

	अगर (kcm->tx_psock)
		seq_म_लिखो(seq, "Psck-%u ", kcm->tx_psock->index);

	अगर (kcm->tx_रुको)
		seq_माला_दो(seq, "TxWait ");

	अगर (kcm->tx_रुको_more)
		seq_माला_दो(seq, "WMore ");

	अगर (kcm->rx_रुको)
		seq_माला_दो(seq, "RxWait ");

	seq_माला_दो(seq, "\n");
पूर्ण

अटल व्योम kcm_क्रमmat_psock(काष्ठा kcm_psock *psock, काष्ठा seq_file *seq,
			     पूर्णांक i, पूर्णांक *len)
अणु
	seq_म_लिखो(seq,
		   "   psock-%-5u %-10llu %-16llu %-10llu %-16llu %-8d %-8d %-8d %-8d ",
		   psock->index,
		   psock->strp.stats.msgs,
		   psock->strp.stats.bytes,
		   psock->stats.tx_msgs,
		   psock->stats.tx_bytes,
		   psock->sk->sk_receive_queue.qlen,
		   atomic_पढ़ो(&psock->sk->sk_rmem_alloc),
		   psock->sk->sk_ग_लिखो_queue.qlen,
		   refcount_पढ़ो(&psock->sk->sk_wmem_alloc));

	अगर (psock->करोne)
		seq_माला_दो(seq, "Done ");

	अगर (psock->tx_stopped)
		seq_माला_दो(seq, "TxStop ");

	अगर (psock->strp.stopped)
		seq_माला_दो(seq, "RxStop ");

	अगर (psock->tx_kcm)
		seq_म_लिखो(seq, "Rsvd-%d ", psock->tx_kcm->index);

	अगर (!psock->strp.छोड़ोd && !psock->पढ़ोy_rx_msg) अणु
		अगर (psock->sk->sk_receive_queue.qlen) अणु
			अगर (psock->strp.need_bytes)
				seq_म_लिखो(seq, "RxWait=%u ",
					   psock->strp.need_bytes);
			अन्यथा
				seq_म_लिखो(seq, "RxWait ");
		पूर्ण
	पूर्ण अन्यथा  अणु
		अगर (psock->strp.छोड़ोd)
			seq_माला_दो(seq, "RxPause ");

		अगर (psock->पढ़ोy_rx_msg)
			seq_माला_दो(seq, "RdyRx ");
	पूर्ण

	seq_माला_दो(seq, "\n");
पूर्ण

अटल व्योम
kcm_क्रमmat_mux(काष्ठा kcm_mux *mux, loff_t idx, काष्ठा seq_file *seq)
अणु
	पूर्णांक i, len;
	काष्ठा kcm_sock *kcm;
	काष्ठा kcm_psock *psock;

	/* mux inक्रमmation */
	seq_म_लिखो(seq,
		   "%-6s%-8s %-10llu %-16llu %-10llu %-16llu %-8s %-8s %-8s %-8s ",
		   "mux", "",
		   mux->stats.rx_msgs,
		   mux->stats.rx_bytes,
		   mux->stats.tx_msgs,
		   mux->stats.tx_bytes,
		   "-", "-", "-", "-");

	seq_म_लिखो(seq, "KCMs: %d, Psocks %d\n",
		   mux->kcm_socks_cnt, mux->psocks_cnt);

	/* kcm sock inक्रमmation */
	i = 0;
	spin_lock_bh(&mux->lock);
	list_क्रम_each_entry(kcm, &mux->kcm_socks, kcm_sock_list) अणु
		kcm_क्रमmat_sock(kcm, seq, i, &len);
		i++;
	पूर्ण
	i = 0;
	list_क्रम_each_entry(psock, &mux->psocks, psock_list) अणु
		kcm_क्रमmat_psock(psock, seq, i, &len);
		i++;
	पूर्ण
	spin_unlock_bh(&mux->lock);
पूर्ण

अटल पूर्णांक kcm_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा kcm_proc_mux_state *mux_state;

	mux_state = seq->निजी;
	अगर (v == SEQ_START_TOKEN) अणु
		mux_state->idx = 0;
		kcm_क्रमmat_mux_header(seq);
	पूर्ण अन्यथा अणु
		kcm_क्रमmat_mux(v, mux_state->idx, seq);
		mux_state->idx++;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations kcm_seq_ops = अणु
	.show	= kcm_seq_show,
	.start	= kcm_seq_start,
	.next	= kcm_seq_next,
	.stop	= kcm_seq_stop,
पूर्ण;

अटल पूर्णांक kcm_stats_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा kcm_psock_stats psock_stats;
	काष्ठा kcm_mux_stats mux_stats;
	काष्ठा strp_aggr_stats strp_stats;
	काष्ठा kcm_mux *mux;
	काष्ठा kcm_psock *psock;
	काष्ठा net *net = seq->निजी;
	काष्ठा kcm_net *knet = net_generic(net, kcm_net_id);

	स_रखो(&mux_stats, 0, माप(mux_stats));
	स_रखो(&psock_stats, 0, माप(psock_stats));
	स_रखो(&strp_stats, 0, माप(strp_stats));

	mutex_lock(&knet->mutex);

	aggregate_mux_stats(&knet->aggregate_mux_stats, &mux_stats);
	aggregate_psock_stats(&knet->aggregate_psock_stats,
			      &psock_stats);
	aggregate_strp_stats(&knet->aggregate_strp_stats,
			     &strp_stats);

	list_क्रम_each_entry(mux, &knet->mux_list, kcm_mux_list) अणु
		spin_lock_bh(&mux->lock);
		aggregate_mux_stats(&mux->stats, &mux_stats);
		aggregate_psock_stats(&mux->aggregate_psock_stats,
				      &psock_stats);
		aggregate_strp_stats(&mux->aggregate_strp_stats,
				     &strp_stats);
		list_क्रम_each_entry(psock, &mux->psocks, psock_list) अणु
			aggregate_psock_stats(&psock->stats, &psock_stats);
			save_strp_stats(&psock->strp, &strp_stats);
		पूर्ण

		spin_unlock_bh(&mux->lock);
	पूर्ण

	mutex_unlock(&knet->mutex);

	seq_म_लिखो(seq,
		   "%-8s %-10s %-16s %-10s %-16s %-10s %-10s %-10s %-10s %-10s\n",
		   "MUX",
		   "RX-Msgs",
		   "RX-Bytes",
		   "TX-Msgs",
		   "TX-Bytes",
		   "TX-Retries",
		   "Attach",
		   "Unattach",
		   "UnattchRsvd",
		   "RX-RdyDrops");

	seq_म_लिखो(seq,
		   "%-8s %-10llu %-16llu %-10llu %-16llu %-10u %-10u %-10u %-10u %-10u\n",
		   "",
		   mux_stats.rx_msgs,
		   mux_stats.rx_bytes,
		   mux_stats.tx_msgs,
		   mux_stats.tx_bytes,
		   mux_stats.tx_retries,
		   mux_stats.psock_attach,
		   mux_stats.psock_unattach_rsvd,
		   mux_stats.psock_unattach,
		   mux_stats.rx_पढ़ोy_drops);

	seq_म_लिखो(seq,
		   "%-8s %-10s %-16s %-10s %-16s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n",
		   "Psock",
		   "RX-Msgs",
		   "RX-Bytes",
		   "TX-Msgs",
		   "TX-Bytes",
		   "Reserved",
		   "Unreserved",
		   "RX-Aborts",
		   "RX-Intr",
		   "RX-Unrecov",
		   "RX-MemFail",
		   "RX-NeedMor",
		   "RX-BadLen",
		   "RX-TooBig",
		   "RX-Timeout",
		   "TX-Aborts");

	seq_म_लिखो(seq,
		   "%-8s %-10llu %-16llu %-10llu %-16llu %-10llu %-10llu %-10u %-10u %-10u %-10u %-10u %-10u %-10u %-10u %-10u\n",
		   "",
		   strp_stats.msgs,
		   strp_stats.bytes,
		   psock_stats.tx_msgs,
		   psock_stats.tx_bytes,
		   psock_stats.reserved,
		   psock_stats.unreserved,
		   strp_stats.पातs,
		   strp_stats.पूर्णांकerrupted,
		   strp_stats.unrecov_पूर्णांकr,
		   strp_stats.mem_fail,
		   strp_stats.need_more_hdr,
		   strp_stats.bad_hdr_len,
		   strp_stats.msg_too_big,
		   strp_stats.msg_समयouts,
		   psock_stats.tx_पातs);

	वापस 0;
पूर्ण

अटल पूर्णांक kcm_proc_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net_single("kcm_stats", 0444, net->proc_net,
			 kcm_stats_seq_show, शून्य))
		जाओ out_kcm_stats;

	अगर (!proc_create_net("kcm", 0444, net->proc_net, &kcm_seq_ops,
			माप(काष्ठा kcm_proc_mux_state)))
		जाओ out_kcm;

	वापस 0;

out_kcm:
	हटाओ_proc_entry("kcm_stats", net->proc_net);
out_kcm_stats:
	वापस -ENOMEM;
पूर्ण

अटल व्योम kcm_proc_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("kcm", net->proc_net);
	हटाओ_proc_entry("kcm_stats", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations kcm_net_ops = अणु
	.init = kcm_proc_init_net,
	.निकास = kcm_proc_निकास_net,
पूर्ण;

पूर्णांक __init kcm_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&kcm_net_ops);
पूर्ण

व्योम __निकास kcm_proc_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&kcm_net_ops);
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */
