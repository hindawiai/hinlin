<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 	atalk_proc.c - proc support क्रम Appletalk
 *
 * 	Copyright(c) Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <linux/atalk.h>
#समावेश <linux/export.h>


अटल __अंतरभूत__ काष्ठा atalk_अगरace *atalk_get_पूर्णांकerface_idx(loff_t pos)
अणु
	काष्ठा atalk_अगरace *i;

	क्रम (i = atalk_पूर्णांकerfaces; pos && i; i = i->next)
		--pos;

	वापस i;
पूर्ण

अटल व्योम *atalk_seq_पूर्णांकerface_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(atalk_पूर्णांकerfaces_lock)
अणु
	loff_t l = *pos;

	पढ़ो_lock_bh(&atalk_पूर्णांकerfaces_lock);
	वापस l ? atalk_get_पूर्णांकerface_idx(--l) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *atalk_seq_पूर्णांकerface_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा atalk_अगरace *i;

	++*pos;
	अगर (v == SEQ_START_TOKEN) अणु
		i = शून्य;
		अगर (atalk_पूर्णांकerfaces)
			i = atalk_पूर्णांकerfaces;
		जाओ out;
	पूर्ण
	i = v;
	i = i->next;
out:
	वापस i;
पूर्ण

अटल व्योम atalk_seq_पूर्णांकerface_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(atalk_पूर्णांकerfaces_lock)
अणु
	पढ़ो_unlock_bh(&atalk_पूर्णांकerfaces_lock);
पूर्ण

अटल पूर्णांक atalk_seq_पूर्णांकerface_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा atalk_अगरace *अगरace;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Interface        Address   Networks  "
			      "Status\n");
		जाओ out;
	पूर्ण

	अगरace = v;
	seq_म_लिखो(seq, "%-16s %04X:%02X  %04X-%04X  %d\n",
		   अगरace->dev->name, ntohs(अगरace->address.s_net),
		   अगरace->address.s_node, ntohs(अगरace->nets.nr_firstnet),
		   ntohs(अगरace->nets.nr_lastnet), अगरace->status);
out:
	वापस 0;
पूर्ण

अटल __अंतरभूत__ काष्ठा atalk_route *atalk_get_route_idx(loff_t pos)
अणु
	काष्ठा atalk_route *r;

	क्रम (r = atalk_routes; pos && r; r = r->next)
		--pos;

	वापस r;
पूर्ण

अटल व्योम *atalk_seq_route_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(atalk_routes_lock)
अणु
	loff_t l = *pos;

	पढ़ो_lock_bh(&atalk_routes_lock);
	वापस l ? atalk_get_route_idx(--l) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *atalk_seq_route_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा atalk_route *r;

	++*pos;
	अगर (v == SEQ_START_TOKEN) अणु
		r = शून्य;
		अगर (atalk_routes)
			r = atalk_routes;
		जाओ out;
	पूर्ण
	r = v;
	r = r->next;
out:
	वापस r;
पूर्ण

अटल व्योम atalk_seq_route_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(atalk_routes_lock)
अणु
	पढ़ो_unlock_bh(&atalk_routes_lock);
पूर्ण

अटल पूर्णांक atalk_seq_route_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा atalk_route *rt;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Target        Router  Flags Dev\n");
		जाओ out;
	पूर्ण

	अगर (atrtr_शेष.dev) अणु
		rt = &atrtr_शेष;
		seq_म_लिखो(seq, "Default     %04X:%02X  %-4d  %s\n",
			       ntohs(rt->gateway.s_net), rt->gateway.s_node,
			       rt->flags, rt->dev->name);
	पूर्ण

	rt = v;
	seq_म_लिखो(seq, "%04X:%02X     %04X:%02X  %-4d  %s\n",
		   ntohs(rt->target.s_net), rt->target.s_node,
		   ntohs(rt->gateway.s_net), rt->gateway.s_node,
		   rt->flags, rt->dev->name);
out:
	वापस 0;
पूर्ण

अटल व्योम *atalk_seq_socket_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(atalk_sockets_lock)
अणु
	पढ़ो_lock_bh(&atalk_sockets_lock);
	वापस seq_hlist_start_head(&atalk_sockets, *pos);
पूर्ण

अटल व्योम *atalk_seq_socket_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_hlist_next(v, &atalk_sockets, pos);
पूर्ण

अटल व्योम atalk_seq_socket_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(atalk_sockets_lock)
अणु
	पढ़ो_unlock_bh(&atalk_sockets_lock);
पूर्ण

अटल पूर्णांक atalk_seq_socket_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा sock *s;
	काष्ठा atalk_sock *at;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq, "Type Local_addr  Remote_addr Tx_queue "
				"Rx_queue St UID\n");
		जाओ out;
	पूर्ण

	s = sk_entry(v);
	at = at_sk(s);

	seq_म_लिखो(seq, "%02X   %04X:%02X:%02X  %04X:%02X:%02X  %08X:%08X "
			"%02X %u\n",
		   s->sk_type, ntohs(at->src_net), at->src_node, at->src_port,
		   ntohs(at->dest_net), at->dest_node, at->dest_port,
		   sk_wmem_alloc_get(s),
		   sk_rmem_alloc_get(s),
		   s->sk_state,
		   from_kuid_munged(seq_user_ns(seq), sock_i_uid(s)));
out:
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations atalk_seq_पूर्णांकerface_ops = अणु
	.start  = atalk_seq_पूर्णांकerface_start,
	.next   = atalk_seq_पूर्णांकerface_next,
	.stop   = atalk_seq_पूर्णांकerface_stop,
	.show   = atalk_seq_पूर्णांकerface_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations atalk_seq_route_ops = अणु
	.start  = atalk_seq_route_start,
	.next   = atalk_seq_route_next,
	.stop   = atalk_seq_route_stop,
	.show   = atalk_seq_route_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations atalk_seq_socket_ops = अणु
	.start  = atalk_seq_socket_start,
	.next   = atalk_seq_socket_next,
	.stop   = atalk_seq_socket_stop,
	.show   = atalk_seq_socket_show,
पूर्ण;

पूर्णांक __init atalk_proc_init(व्योम)
अणु
	अगर (!proc_सूची_गढ़ो("atalk", init_net.proc_net))
		वापस -ENOMEM;

	अगर (!proc_create_seq("atalk/interface", 0444, init_net.proc_net,
			    &atalk_seq_पूर्णांकerface_ops))
		जाओ out;

	अगर (!proc_create_seq("atalk/route", 0444, init_net.proc_net,
			    &atalk_seq_route_ops))
		जाओ out;

	अगर (!proc_create_seq("atalk/socket", 0444, init_net.proc_net,
			    &atalk_seq_socket_ops))
		जाओ out;

	अगर (!proc_create_seq_निजी("atalk/arp", 0444, init_net.proc_net,
				     &aarp_seq_ops,
				     माप(काष्ठा aarp_iter_state), शून्य))
		जाओ out;

	वापस 0;

out:
	हटाओ_proc_subtree("atalk", init_net.proc_net);
	वापस -ENOMEM;
पूर्ण

व्योम atalk_proc_निकास(व्योम)
अणु
	हटाओ_proc_subtree("atalk", init_net.proc_net);
पूर्ण
