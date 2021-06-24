<शैली गुरु>
/*
 * proc_llc.c - proc पूर्णांकerface क्रम LLC
 *
 * Copyright (c) 2001 by Jay Schulist <jschlst@samba.org>
 *		 2002-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/llc.h>
#समावेश <net/llc_c_ac.h>
#समावेश <net/llc_c_ev.h>
#समावेश <net/llc_c_st.h>
#समावेश <net/llc_conn.h>

अटल व्योम llc_ui_क्रमmat_mac(काष्ठा seq_file *seq, u8 *addr)
अणु
	seq_म_लिखो(seq, "%pM", addr);
पूर्ण

अटल काष्ठा sock *llc_get_sk_idx(loff_t pos)
अणु
	काष्ठा llc_sap *sap;
	काष्ठा sock *sk = शून्य;
	पूर्णांक i;

	list_क्रम_each_entry_rcu(sap, &llc_sap_list, node) अणु
		spin_lock_bh(&sap->sk_lock);
		क्रम (i = 0; i < LLC_SK_LADDR_HASH_ENTRIES; i++) अणु
			काष्ठा hlist_nulls_head *head = &sap->sk_laddr_hash[i];
			काष्ठा hlist_nulls_node *node;

			sk_nulls_क्रम_each(sk, node, head) अणु
				अगर (!pos)
					जाओ found; /* keep the lock */
				--pos;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&sap->sk_lock);
	पूर्ण
	sk = शून्य;
found:
	वापस sk;
पूर्ण

अटल व्योम *llc_seq_start(काष्ठा seq_file *seq, loff_t *pos) __acquires(RCU)
अणु
	loff_t l = *pos;

	rcu_पढ़ो_lock_bh();
	वापस l ? llc_get_sk_idx(--l) : SEQ_START_TOKEN;
पूर्ण

अटल काष्ठा sock *laddr_hash_next(काष्ठा llc_sap *sap, पूर्णांक bucket)
अणु
	काष्ठा hlist_nulls_node *node;
	काष्ठा sock *sk = शून्य;

	जबतक (++bucket < LLC_SK_LADDR_HASH_ENTRIES)
		sk_nulls_क्रम_each(sk, node, &sap->sk_laddr_hash[bucket])
			जाओ out;

out:
	वापस sk;
पूर्ण

अटल व्योम *llc_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा sock* sk, *next;
	काष्ठा llc_sock *llc;
	काष्ठा llc_sap *sap;

	++*pos;
	अगर (v == SEQ_START_TOKEN) अणु
		sk = llc_get_sk_idx(0);
		जाओ out;
	पूर्ण
	sk = v;
	next = sk_nulls_next(sk);
	अगर (next) अणु
		sk = next;
		जाओ out;
	पूर्ण
	llc = llc_sk(sk);
	sap = llc->sap;
	sk = laddr_hash_next(sap, llc_sk_laddr_hashfn(sap, &llc->laddr));
	अगर (sk)
		जाओ out;
	spin_unlock_bh(&sap->sk_lock);
	list_क्रम_each_entry_जारी_rcu(sap, &llc_sap_list, node) अणु
		spin_lock_bh(&sap->sk_lock);
		sk = laddr_hash_next(sap, -1);
		अगर (sk)
			अवरोध; /* keep the lock */
		spin_unlock_bh(&sap->sk_lock);
	पूर्ण
out:
	वापस sk;
पूर्ण

अटल व्योम llc_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v && v != SEQ_START_TOKEN) अणु
		काष्ठा sock *sk = v;
		काष्ठा llc_sock *llc = llc_sk(sk);
		काष्ठा llc_sap *sap = llc->sap;

		spin_unlock_bh(&sap->sk_lock);
	पूर्ण
	rcu_पढ़ो_unlock_bh();
पूर्ण

अटल पूर्णांक llc_seq_socket_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sock* sk;
	काष्ठा llc_sock *llc;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "SKt Mc local_mac_sap        remote_mac_sap   "
			      "    tx_queue rx_queue st uid link\n");
		जाओ out;
	पूर्ण
	sk = v;
	llc = llc_sk(sk);

	/* FIXME: check अगर the address is multicast */
	seq_म_लिखो(seq, "%2X  %2X ", sk->sk_type, 0);

	अगर (llc->dev)
		llc_ui_क्रमmat_mac(seq, llc->dev->dev_addr);
	अन्यथा अणु
		u8 addr[6] = अणु0,0,0,0,0,0पूर्ण;
		llc_ui_क्रमmat_mac(seq, addr);
	पूर्ण
	seq_म_लिखो(seq, "@%02X ", llc->sap->laddr.lsap);
	llc_ui_क्रमmat_mac(seq, llc->daddr.mac);
	seq_म_लिखो(seq, "@%02X %8d %8d %2d %3u %4d\n", llc->daddr.lsap,
		   sk_wmem_alloc_get(sk),
		   sk_rmem_alloc_get(sk) - llc->copied_seq,
		   sk->sk_state,
		   from_kuid_munged(seq_user_ns(seq), sock_i_uid(sk)),
		   llc->link);
out:
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *स्थिर llc_conn_state_names[] = अणु
	[LLC_CONN_STATE_ADM] =        "adm",
	[LLC_CONN_STATE_SETUP] =      "setup",
	[LLC_CONN_STATE_NORMAL] =     "normal",
	[LLC_CONN_STATE_BUSY] =       "busy",
	[LLC_CONN_STATE_REJ] =        "rej",
	[LLC_CONN_STATE_AWAIT] =      "await",
	[LLC_CONN_STATE_AWAIT_BUSY] = "await_busy",
	[LLC_CONN_STATE_AWAIT_REJ] =  "await_rej",
	[LLC_CONN_STATE_D_CONN]	=     "d_conn",
	[LLC_CONN_STATE_RESET] =      "reset",
	[LLC_CONN_STATE_ERROR] =      "error",
	[LLC_CONN_STATE_TEMP] =       "temp",
पूर्ण;

अटल पूर्णांक llc_seq_core_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sock* sk;
	काष्ठा llc_sock *llc;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Connection list:\n"
			      "dsap state      retr txw rxw pf ff sf df rs cs "
			      "tack tpfc trs tbs blog busr\n");
		जाओ out;
	पूर्ण
	sk = v;
	llc = llc_sk(sk);

	seq_म_लिखो(seq, " %02X  %-10s %3d  %3d %3d %2d %2d %2d %2d %2d %2d "
			"%4d %4d %3d %3d %4d %4d\n",
		   llc->daddr.lsap, llc_conn_state_names[llc->state],
		   llc->retry_count, llc->k, llc->rw, llc->p_flag, llc->f_flag,
		   llc->s_flag, llc->data_flag, llc->remote_busy_flag,
		   llc->cause_flag, समयr_pending(&llc->ack_समयr.समयr),
		   समयr_pending(&llc->pf_cycle_समयr.समयr),
		   समयr_pending(&llc->rej_sent_समयr.समयr),
		   समयr_pending(&llc->busy_state_समयr.समयr),
		   !!sk->sk_backlog.tail, !!sk->sk_lock.owned);
out:
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations llc_seq_socket_ops = अणु
	.start  = llc_seq_start,
	.next   = llc_seq_next,
	.stop   = llc_seq_stop,
	.show   = llc_seq_socket_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations llc_seq_core_ops = अणु
	.start  = llc_seq_start,
	.next   = llc_seq_next,
	.stop   = llc_seq_stop,
	.show   = llc_seq_core_show,
पूर्ण;

अटल काष्ठा proc_dir_entry *llc_proc_dir;

पूर्णांक __init llc_proc_init(व्योम)
अणु
	पूर्णांक rc = -ENOMEM;
	काष्ठा proc_dir_entry *p;

	llc_proc_dir = proc_सूची_गढ़ो("llc", init_net.proc_net);
	अगर (!llc_proc_dir)
		जाओ out;

	p = proc_create_seq("socket", 0444, llc_proc_dir, &llc_seq_socket_ops);
	अगर (!p)
		जाओ out_socket;

	p = proc_create_seq("core", 0444, llc_proc_dir, &llc_seq_core_ops);
	अगर (!p)
		जाओ out_core;

	rc = 0;
out:
	वापस rc;
out_core:
	हटाओ_proc_entry("socket", llc_proc_dir);
out_socket:
	हटाओ_proc_entry("llc", init_net.proc_net);
	जाओ out;
पूर्ण

व्योम llc_proc_निकास(व्योम)
अणु
	हटाओ_proc_entry("socket", llc_proc_dir);
	हटाओ_proc_entry("core", llc_proc_dir);
	हटाओ_proc_entry("llc", init_net.proc_net);
पूर्ण
