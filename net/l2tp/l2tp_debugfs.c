<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* L2TP subप्रणाली debugfs
 *
 * Copyright (c) 2010 Katalix Systems Ltd
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/hash.h>
#समावेश <linux/l2tp.h>
#समावेश <linux/in.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/debugfs.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/udp.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/tcp_states.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश "l2tp_core.h"

अटल काष्ठा dentry *rootdir;

काष्ठा l2tp_dfs_seq_data अणु
	काष्ठा net *net;
	पूर्णांक tunnel_idx;			/* current tunnel */
	पूर्णांक session_idx;		/* index of session within current tunnel */
	काष्ठा l2tp_tunnel *tunnel;
	काष्ठा l2tp_session *session;	/* शून्य means get next tunnel */
पूर्ण;

अटल व्योम l2tp_dfs_next_tunnel(काष्ठा l2tp_dfs_seq_data *pd)
अणु
	/* Drop reference taken during previous invocation */
	अगर (pd->tunnel)
		l2tp_tunnel_dec_refcount(pd->tunnel);

	pd->tunnel = l2tp_tunnel_get_nth(pd->net, pd->tunnel_idx);
	pd->tunnel_idx++;
पूर्ण

अटल व्योम l2tp_dfs_next_session(काष्ठा l2tp_dfs_seq_data *pd)
अणु
	/* Drop reference taken during previous invocation */
	अगर (pd->session)
		l2tp_session_dec_refcount(pd->session);

	pd->session = l2tp_session_get_nth(pd->tunnel, pd->session_idx);
	pd->session_idx++;

	अगर (!pd->session) अणु
		pd->session_idx = 0;
		l2tp_dfs_next_tunnel(pd);
	पूर्ण
पूर्ण

अटल व्योम *l2tp_dfs_seq_start(काष्ठा seq_file *m, loff_t *offs)
अणु
	काष्ठा l2tp_dfs_seq_data *pd = SEQ_START_TOKEN;
	loff_t pos = *offs;

	अगर (!pos)
		जाओ out;

	अगर (WARN_ON(!m->निजी)) अणु
		pd = शून्य;
		जाओ out;
	पूर्ण
	pd = m->निजी;

	अगर (!pd->tunnel)
		l2tp_dfs_next_tunnel(pd);
	अन्यथा
		l2tp_dfs_next_session(pd);

	/* शून्य tunnel and session indicates end of list */
	अगर (!pd->tunnel && !pd->session)
		pd = शून्य;

out:
	वापस pd;
पूर्ण

अटल व्योम *l2tp_dfs_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस शून्य;
पूर्ण

अटल व्योम l2tp_dfs_seq_stop(काष्ठा seq_file *p, व्योम *v)
अणु
	काष्ठा l2tp_dfs_seq_data *pd = v;

	अगर (!pd || pd == SEQ_START_TOKEN)
		वापस;

	/* Drop reference taken by last invocation of l2tp_dfs_next_session()
	 * or l2tp_dfs_next_tunnel().
	 */
	अगर (pd->session) अणु
		l2tp_session_dec_refcount(pd->session);
		pd->session = शून्य;
	पूर्ण
	अगर (pd->tunnel) अणु
		l2tp_tunnel_dec_refcount(pd->tunnel);
		pd->tunnel = शून्य;
	पूर्ण
पूर्ण

अटल व्योम l2tp_dfs_seq_tunnel_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा l2tp_tunnel *tunnel = v;
	पूर्णांक session_count = 0;
	पूर्णांक hash;
	काष्ठा hlist_node *walk;
	काष्ठा hlist_node *पंचांगp;

	पढ़ो_lock_bh(&tunnel->hlist_lock);
	क्रम (hash = 0; hash < L2TP_HASH_SIZE; hash++) अणु
		hlist_क्रम_each_safe(walk, पंचांगp, &tunnel->session_hlist[hash]) अणु
			काष्ठा l2tp_session *session;

			session = hlist_entry(walk, काष्ठा l2tp_session, hlist);
			अगर (session->session_id == 0)
				जारी;

			session_count++;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&tunnel->hlist_lock);

	seq_म_लिखो(m, "\nTUNNEL %u peer %u", tunnel->tunnel_id, tunnel->peer_tunnel_id);
	अगर (tunnel->sock) अणु
		काष्ठा inet_sock *inet = inet_sk(tunnel->sock);

#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (tunnel->sock->sk_family == AF_INET6) अणु
			स्थिर काष्ठा ipv6_pinfo *np = inet6_sk(tunnel->sock);

			seq_म_लिखो(m, " from %pI6c to %pI6c\n",
				   &np->saddr, &tunnel->sock->sk_v6_daddr);
		पूर्ण
#पूर्ण_अगर
		अगर (tunnel->sock->sk_family == AF_INET)
			seq_म_लिखो(m, " from %pI4 to %pI4\n",
				   &inet->inet_saddr, &inet->inet_daddr);

		अगर (tunnel->encap == L2TP_ENCAPTYPE_UDP)
			seq_म_लिखो(m, " source port %hu, dest port %hu\n",
				   ntohs(inet->inet_sport), ntohs(inet->inet_dport));
	पूर्ण
	seq_म_लिखो(m, " L2TPv%d, %s\n", tunnel->version,
		   tunnel->encap == L2TP_ENCAPTYPE_UDP ? "UDP" :
		   tunnel->encap == L2TP_ENCAPTYPE_IP ? "IP" :
		   "");
	seq_म_लिखो(m, " %d sessions, refcnt %d/%d\n", session_count,
		   tunnel->sock ? refcount_पढ़ो(&tunnel->sock->sk_refcnt) : 0,
		   refcount_पढ़ो(&tunnel->ref_count));
	seq_म_लिखो(m, " %08x rx %ld/%ld/%ld rx %ld/%ld/%ld\n",
		   0,
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.tx_packets),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.tx_bytes),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.tx_errors),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_packets),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_bytes),
		   atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_errors));
पूर्ण

अटल व्योम l2tp_dfs_seq_session_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा l2tp_session *session = v;

	seq_म_लिखो(m, "  SESSION %u, peer %u, %s\n", session->session_id,
		   session->peer_session_id,
		   session->pwtype == L2TP_PWTYPE_ETH ? "ETH" :
		   session->pwtype == L2TP_PWTYPE_PPP ? "PPP" :
		   "");
	अगर (session->send_seq || session->recv_seq)
		seq_म_लिखो(m, "   nr %hu, ns %hu\n", session->nr, session->ns);
	seq_म_लिखो(m, "   refcnt %d\n", refcount_पढ़ो(&session->ref_count));
	seq_म_लिखो(m, "   config 0/0/%c/%c/-/%s %08x %u\n",
		   session->recv_seq ? 'R' : '-',
		   session->send_seq ? 'S' : '-',
		   session->lns_mode ? "LNS" : "LAC",
		   0,
		   jअगरfies_to_msecs(session->reorder_समयout));
	seq_म_लिखो(m, "   offset 0 l2specific %hu/%hu\n",
		   session->l2specअगरic_type, l2tp_get_l2specअगरic_len(session));
	अगर (session->cookie_len) अणु
		seq_म_लिखो(m, "   cookie %02x%02x%02x%02x",
			   session->cookie[0], session->cookie[1],
			   session->cookie[2], session->cookie[3]);
		अगर (session->cookie_len == 8)
			seq_म_लिखो(m, "%02x%02x%02x%02x",
				   session->cookie[4], session->cookie[5],
				   session->cookie[6], session->cookie[7]);
		seq_माला_दो(m, "\n");
	पूर्ण
	अगर (session->peer_cookie_len) अणु
		seq_म_लिखो(m, "   peer cookie %02x%02x%02x%02x",
			   session->peer_cookie[0], session->peer_cookie[1],
			   session->peer_cookie[2], session->peer_cookie[3]);
		अगर (session->peer_cookie_len == 8)
			seq_म_लिखो(m, "%02x%02x%02x%02x",
				   session->peer_cookie[4], session->peer_cookie[5],
				   session->peer_cookie[6], session->peer_cookie[7]);
		seq_माला_दो(m, "\n");
	पूर्ण

	seq_म_लिखो(m, "   %hu/%hu tx %ld/%ld/%ld rx %ld/%ld/%ld\n",
		   session->nr, session->ns,
		   atomic_दीर्घ_पढ़ो(&session->stats.tx_packets),
		   atomic_दीर्घ_पढ़ो(&session->stats.tx_bytes),
		   atomic_दीर्घ_पढ़ो(&session->stats.tx_errors),
		   atomic_दीर्घ_पढ़ो(&session->stats.rx_packets),
		   atomic_दीर्घ_पढ़ो(&session->stats.rx_bytes),
		   atomic_दीर्घ_पढ़ो(&session->stats.rx_errors));

	अगर (session->show)
		session->show(m, session);
पूर्ण

अटल पूर्णांक l2tp_dfs_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा l2tp_dfs_seq_data *pd = v;

	/* display header on line 1 */
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(m, "TUNNEL ID, peer ID from IP to IP\n");
		seq_माला_दो(m, " L2TPv2/L2TPv3, UDP/IP\n");
		seq_माला_दो(m, " sessions session-count, refcnt refcnt/sk->refcnt\n");
		seq_माला_दो(m, " debug tx-pkts/bytes/errs rx-pkts/bytes/errs\n");
		seq_माला_दो(m, "  SESSION ID, peer ID, PWTYPE\n");
		seq_माला_दो(m, "   refcnt cnt\n");
		seq_माला_दो(m, "   offset OFFSET l2specific TYPE/LEN\n");
		seq_माला_दो(m, "   [ cookie ]\n");
		seq_माला_दो(m, "   [ peer cookie ]\n");
		seq_माला_दो(m, "   config mtu/mru/rcvseq/sendseq/dataseq/lns debug reorderto\n");
		seq_माला_दो(m, "   nr/ns tx-pkts/bytes/errs rx-pkts/bytes/errs\n");
		जाओ out;
	पूर्ण

	अगर (!pd->session)
		l2tp_dfs_seq_tunnel_show(m, pd->tunnel);
	अन्यथा
		l2tp_dfs_seq_session_show(m, pd->session);

out:
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations l2tp_dfs_seq_ops = अणु
	.start		= l2tp_dfs_seq_start,
	.next		= l2tp_dfs_seq_next,
	.stop		= l2tp_dfs_seq_stop,
	.show		= l2tp_dfs_seq_show,
पूर्ण;

अटल पूर्णांक l2tp_dfs_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा l2tp_dfs_seq_data *pd;
	काष्ठा seq_file *seq;
	पूर्णांक rc = -ENOMEM;

	pd = kzalloc(माप(*pd), GFP_KERNEL);
	अगर (!pd)
		जाओ out;

	/* Derive the network namespace from the pid खोलोing the
	 * file.
	 */
	pd->net = get_net_ns_by_pid(current->pid);
	अगर (IS_ERR(pd->net)) अणु
		rc = PTR_ERR(pd->net);
		जाओ err_मुक्त_pd;
	पूर्ण

	rc = seq_खोलो(file, &l2tp_dfs_seq_ops);
	अगर (rc)
		जाओ err_मुक्त_net;

	seq = file->निजी_data;
	seq->निजी = pd;

out:
	वापस rc;

err_मुक्त_net:
	put_net(pd->net);
err_मुक्त_pd:
	kमुक्त(pd);
	जाओ out;
पूर्ण

अटल पूर्णांक l2tp_dfs_seq_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा l2tp_dfs_seq_data *pd;
	काष्ठा seq_file *seq;

	seq = file->निजी_data;
	pd = seq->निजी;
	अगर (pd->net)
		put_net(pd->net);
	kमुक्त(pd);
	seq_release(inode, file);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations l2tp_dfs_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= l2tp_dfs_seq_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= l2tp_dfs_seq_release,
पूर्ण;

अटल पूर्णांक __init l2tp_debugfs_init(व्योम)
अणु
	rootdir = debugfs_create_dir("l2tp", शून्य);

	debugfs_create_file("tunnels", 0600, rootdir, शून्य, &l2tp_dfs_fops);

	pr_info("L2TP debugfs support\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास l2tp_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(rootdir);
पूर्ण

module_init(l2tp_debugfs_init);
module_निकास(l2tp_debugfs_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Chapman <jchapman@katalix.com>");
MODULE_DESCRIPTION("L2TP debugfs driver");
MODULE_VERSION("1.0");
