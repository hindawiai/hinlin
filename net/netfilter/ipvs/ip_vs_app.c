<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ip_vs_app.c: Application module support क्रम IPVS
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *
 * Most code here is taken from ip_masq_app.c in kernel 2.2. The dअगरference
 * is that ip_vs_app module handles the reverse direction (incoming requests
 * and outgoing responses).
 *
 *		IP_MASQ_APP application masquerading module
 *
 * Author:	Juan Jose Ciarlante, <jjciarla@raiz.uncu.edu.ar>
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>
#समावेश <net/protocol.h>
#समावेश <net/tcp.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mutex.h>

#समावेश <net/ip_vs.h>

EXPORT_SYMBOL(रेजिस्टर_ip_vs_app);
EXPORT_SYMBOL(unरेजिस्टर_ip_vs_app);
EXPORT_SYMBOL(रेजिस्टर_ip_vs_app_inc);

अटल DEFINE_MUTEX(__ip_vs_app_mutex);

/*
 *	Get an ip_vs_app object
 */
अटल अंतरभूत पूर्णांक ip_vs_app_get(काष्ठा ip_vs_app *app)
अणु
	वापस try_module_get(app->module);
पूर्ण


अटल अंतरभूत व्योम ip_vs_app_put(काष्ठा ip_vs_app *app)
अणु
	module_put(app->module);
पूर्ण

अटल व्योम ip_vs_app_inc_destroy(काष्ठा ip_vs_app *inc)
अणु
	kमुक्त(inc->समयout_table);
	kमुक्त(inc);
पूर्ण

अटल व्योम ip_vs_app_inc_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा ip_vs_app *inc = container_of(head, काष्ठा ip_vs_app, rcu_head);

	ip_vs_app_inc_destroy(inc);
पूर्ण

/*
 *	Allocate/initialize app incarnation and रेजिस्टर it in proto apps.
 */
अटल पूर्णांक
ip_vs_app_inc_new(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *app, __u16 proto,
		  __u16 port)
अणु
	काष्ठा ip_vs_protocol *pp;
	काष्ठा ip_vs_app *inc;
	पूर्णांक ret;

	अगर (!(pp = ip_vs_proto_get(proto)))
		वापस -EPROTONOSUPPORT;

	अगर (!pp->unरेजिस्टर_app)
		वापस -EOPNOTSUPP;

	inc = kmemdup(app, माप(*inc), GFP_KERNEL);
	अगर (!inc)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&inc->p_list);
	INIT_LIST_HEAD(&inc->incs_list);
	inc->app = app;
	inc->port = htons(port);
	atomic_set(&inc->usecnt, 0);

	अगर (app->समयouts) अणु
		inc->समयout_table =
			ip_vs_create_समयout_table(app->समयouts,
						   app->समयouts_size);
		अगर (!inc->समयout_table) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = pp->रेजिस्टर_app(ipvs, inc);
	अगर (ret)
		जाओ out;

	list_add(&inc->a_list, &app->incs_list);
	IP_VS_DBG(9, "%s App %s:%u registered\n",
		  pp->name, inc->name, ntohs(inc->port));

	वापस 0;

  out:
	ip_vs_app_inc_destroy(inc);
	वापस ret;
पूर्ण


/*
 *	Release app incarnation
 */
अटल व्योम
ip_vs_app_inc_release(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *inc)
अणु
	काष्ठा ip_vs_protocol *pp;

	अगर (!(pp = ip_vs_proto_get(inc->protocol)))
		वापस;

	अगर (pp->unरेजिस्टर_app)
		pp->unरेजिस्टर_app(ipvs, inc);

	IP_VS_DBG(9, "%s App %s:%u unregistered\n",
		  pp->name, inc->name, ntohs(inc->port));

	list_del(&inc->a_list);

	call_rcu(&inc->rcu_head, ip_vs_app_inc_rcu_मुक्त);
पूर्ण


/*
 *	Get reference to app inc (only called from softirq)
 *
 */
पूर्णांक ip_vs_app_inc_get(काष्ठा ip_vs_app *inc)
अणु
	पूर्णांक result;

	result = ip_vs_app_get(inc->app);
	अगर (result)
		atomic_inc(&inc->usecnt);
	वापस result;
पूर्ण


/*
 *	Put the app inc (only called from समयr or net softirq)
 */
व्योम ip_vs_app_inc_put(काष्ठा ip_vs_app *inc)
अणु
	atomic_dec(&inc->usecnt);
	ip_vs_app_put(inc->app);
पूर्ण


/*
 *	Register an application incarnation in protocol applications
 */
पूर्णांक
रेजिस्टर_ip_vs_app_inc(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *app, __u16 proto,
		       __u16 port)
अणु
	पूर्णांक result;

	mutex_lock(&__ip_vs_app_mutex);

	result = ip_vs_app_inc_new(ipvs, app, proto, port);

	mutex_unlock(&__ip_vs_app_mutex);

	वापस result;
पूर्ण


/* Register application क्रम netns */
काष्ठा ip_vs_app *रेजिस्टर_ip_vs_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *app)
अणु
	काष्ठा ip_vs_app *a;
	पूर्णांक err = 0;

	mutex_lock(&__ip_vs_app_mutex);

	/* increase the module use count */
	अगर (!ip_vs_use_count_inc()) अणु
		err = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	list_क्रम_each_entry(a, &ipvs->app_list, a_list) अणु
		अगर (!म_भेद(app->name, a->name)) अणु
			err = -EEXIST;
			/* decrease the module use count */
			ip_vs_use_count_dec();
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	a = kmemdup(app, माप(*app), GFP_KERNEL);
	अगर (!a) अणु
		err = -ENOMEM;
		/* decrease the module use count */
		ip_vs_use_count_dec();
		जाओ out_unlock;
	पूर्ण
	INIT_LIST_HEAD(&a->incs_list);
	list_add(&a->a_list, &ipvs->app_list);

out_unlock:
	mutex_unlock(&__ip_vs_app_mutex);

	वापस err ? ERR_PTR(err) : a;
पूर्ण


/*
 *	ip_vs_app unregistration routine
 *	We are sure there are no app incarnations attached to services
 *	Caller should use synchronize_rcu() or rcu_barrier()
 */
व्योम unरेजिस्टर_ip_vs_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *app)
अणु
	काष्ठा ip_vs_app *a, *anxt, *inc, *nxt;

	mutex_lock(&__ip_vs_app_mutex);

	list_क्रम_each_entry_safe(a, anxt, &ipvs->app_list, a_list) अणु
		अगर (app && म_भेद(app->name, a->name))
			जारी;
		list_क्रम_each_entry_safe(inc, nxt, &a->incs_list, a_list) अणु
			ip_vs_app_inc_release(ipvs, inc);
		पूर्ण

		list_del(&a->a_list);
		kमुक्त(a);

		/* decrease the module use count */
		ip_vs_use_count_dec();
	पूर्ण

	mutex_unlock(&__ip_vs_app_mutex);
पूर्ण


/*
 *	Bind ip_vs_conn to its ip_vs_app (called by cp स्थिरructor)
 */
पूर्णांक ip_vs_bind_app(काष्ठा ip_vs_conn *cp,
		   काष्ठा ip_vs_protocol *pp)
अणु
	वापस pp->app_conn_bind(cp);
पूर्ण


/*
 *	Unbind cp from application incarnation (called by cp deकाष्ठाor)
 */
व्योम ip_vs_unbind_app(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा ip_vs_app *inc = cp->app;

	अगर (!inc)
		वापस;

	अगर (inc->unbind_conn)
		inc->unbind_conn(inc, cp);
	अगर (inc->करोne_conn)
		inc->करोne_conn(inc, cp);
	ip_vs_app_inc_put(inc);
	cp->app = शून्य;
पूर्ण


/*
 *	Fixes th->seq based on ip_vs_seq info.
 */
अटल अंतरभूत व्योम vs_fix_seq(स्थिर काष्ठा ip_vs_seq *vseq, काष्ठा tcphdr *th)
अणु
	__u32 seq = ntohl(th->seq);

	/*
	 *	Adjust seq with delta-offset क्रम all packets after
	 *	the most recent resized pkt seq and with previous_delta offset
	 *	क्रम all packets	beक्रमe most recent resized pkt seq.
	 */
	अगर (vseq->delta || vseq->previous_delta) अणु
		अगर(after(seq, vseq->init_seq)) अणु
			th->seq = htonl(seq + vseq->delta);
			IP_VS_DBG(9, "%s(): added delta (%d) to seq\n",
				  __func__, vseq->delta);
		पूर्ण अन्यथा अणु
			th->seq = htonl(seq + vseq->previous_delta);
			IP_VS_DBG(9, "%s(): added previous_delta (%d) to seq\n",
				  __func__, vseq->previous_delta);
		पूर्ण
	पूर्ण
पूर्ण


/*
 *	Fixes th->ack_seq based on ip_vs_seq info.
 */
अटल अंतरभूत व्योम
vs_fix_ack_seq(स्थिर काष्ठा ip_vs_seq *vseq, काष्ठा tcphdr *th)
अणु
	__u32 ack_seq = ntohl(th->ack_seq);

	/*
	 * Adjust ack_seq with delta-offset क्रम
	 * the packets AFTER most recent resized pkt has caused a shअगरt
	 * क्रम packets beक्रमe most recent resized pkt, use previous_delta
	 */
	अगर (vseq->delta || vseq->previous_delta) अणु
		/* since ack_seq is the number of octet that is expected
		   to receive next, so compare it with init_seq+delta */
		अगर(after(ack_seq, vseq->init_seq+vseq->delta)) अणु
			th->ack_seq = htonl(ack_seq - vseq->delta);
			IP_VS_DBG(9, "%s(): subtracted delta "
				  "(%d) from ack_seq\n", __func__, vseq->delta);

		पूर्ण अन्यथा अणु
			th->ack_seq = htonl(ack_seq - vseq->previous_delta);
			IP_VS_DBG(9, "%s(): subtracted "
				  "previous_delta (%d) from ack_seq\n",
				  __func__, vseq->previous_delta);
		पूर्ण
	पूर्ण
पूर्ण


/*
 *	Updates ip_vs_seq अगर pkt has been resized
 *	Assumes alपढ़ोy checked proto==IPPROTO_TCP and dअगरf!=0.
 */
अटल अंतरभूत व्योम vs_seq_update(काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_seq *vseq,
				 अचिन्हित पूर्णांक flag, __u32 seq, पूर्णांक dअगरf)
अणु
	/* spinlock is to keep updating cp->flags atomic */
	spin_lock_bh(&cp->lock);
	अगर (!(cp->flags & flag) || after(seq, vseq->init_seq)) अणु
		vseq->previous_delta = vseq->delta;
		vseq->delta += dअगरf;
		vseq->init_seq = seq;
		cp->flags |= flag;
	पूर्ण
	spin_unlock_bh(&cp->lock);
पूर्ण

अटल अंतरभूत पूर्णांक app_tcp_pkt_out(काष्ठा ip_vs_conn *cp, काष्ठा sk_buff *skb,
				  काष्ठा ip_vs_app *app,
				  काष्ठा ip_vs_iphdr *ipvsh)
अणु
	पूर्णांक dअगरf;
	स्थिर अचिन्हित पूर्णांक tcp_offset = ip_hdrlen(skb);
	काष्ठा tcphdr *th;
	__u32 seq;

	अगर (skb_ensure_writable(skb, tcp_offset + माप(*th)))
		वापस 0;

	th = (काष्ठा tcphdr *)(skb_network_header(skb) + tcp_offset);

	/*
	 *	Remember seq number in हाल this pkt माला_लो resized
	 */
	seq = ntohl(th->seq);

	/*
	 *	Fix seq stuff अगर flagged as so.
	 */
	अगर (cp->flags & IP_VS_CONN_F_OUT_SEQ)
		vs_fix_seq(&cp->out_seq, th);
	अगर (cp->flags & IP_VS_CONN_F_IN_SEQ)
		vs_fix_ack_seq(&cp->in_seq, th);

	/*
	 *	Call निजी output hook function
	 */
	अगर (app->pkt_out == शून्य)
		वापस 1;

	अगर (!app->pkt_out(app, cp, skb, &dअगरf, ipvsh))
		वापस 0;

	/*
	 *	Update ip_vs seq stuff अगर len has changed.
	 */
	अगर (dअगरf != 0)
		vs_seq_update(cp, &cp->out_seq,
			      IP_VS_CONN_F_OUT_SEQ, seq, dअगरf);

	वापस 1;
पूर्ण

/*
 *	Output pkt hook. Will call bound ip_vs_app specअगरic function
 *	called by ipvs packet handler, assumes previously checked cp!=शून्य
 *	वापसs false अगर it can't handle packet (oom)
 */
पूर्णांक ip_vs_app_pkt_out(काष्ठा ip_vs_conn *cp, काष्ठा sk_buff *skb,
		      काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा ip_vs_app *app;

	/*
	 *	check अगर application module is bound to
	 *	this ip_vs_conn.
	 */
	अगर ((app = cp->app) == शून्य)
		वापस 1;

	/* TCP is complicated */
	अगर (cp->protocol == IPPROTO_TCP)
		वापस app_tcp_pkt_out(cp, skb, app, ipvsh);

	/*
	 *	Call निजी output hook function
	 */
	अगर (app->pkt_out == शून्य)
		वापस 1;

	वापस app->pkt_out(app, cp, skb, शून्य, ipvsh);
पूर्ण


अटल अंतरभूत पूर्णांक app_tcp_pkt_in(काष्ठा ip_vs_conn *cp, काष्ठा sk_buff *skb,
				 काष्ठा ip_vs_app *app,
				 काष्ठा ip_vs_iphdr *ipvsh)
अणु
	पूर्णांक dअगरf;
	स्थिर अचिन्हित पूर्णांक tcp_offset = ip_hdrlen(skb);
	काष्ठा tcphdr *th;
	__u32 seq;

	अगर (skb_ensure_writable(skb, tcp_offset + माप(*th)))
		वापस 0;

	th = (काष्ठा tcphdr *)(skb_network_header(skb) + tcp_offset);

	/*
	 *	Remember seq number in हाल this pkt माला_लो resized
	 */
	seq = ntohl(th->seq);

	/*
	 *	Fix seq stuff अगर flagged as so.
	 */
	अगर (cp->flags & IP_VS_CONN_F_IN_SEQ)
		vs_fix_seq(&cp->in_seq, th);
	अगर (cp->flags & IP_VS_CONN_F_OUT_SEQ)
		vs_fix_ack_seq(&cp->out_seq, th);

	/*
	 *	Call निजी input hook function
	 */
	अगर (app->pkt_in == शून्य)
		वापस 1;

	अगर (!app->pkt_in(app, cp, skb, &dअगरf, ipvsh))
		वापस 0;

	/*
	 *	Update ip_vs seq stuff अगर len has changed.
	 */
	अगर (dअगरf != 0)
		vs_seq_update(cp, &cp->in_seq,
			      IP_VS_CONN_F_IN_SEQ, seq, dअगरf);

	वापस 1;
पूर्ण

/*
 *	Input pkt hook. Will call bound ip_vs_app specअगरic function
 *	called by ipvs packet handler, assumes previously checked cp!=शून्य.
 *	वापसs false अगर can't handle packet (oom).
 */
पूर्णांक ip_vs_app_pkt_in(काष्ठा ip_vs_conn *cp, काष्ठा sk_buff *skb,
		     काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा ip_vs_app *app;

	/*
	 *	check अगर application module is bound to
	 *	this ip_vs_conn.
	 */
	अगर ((app = cp->app) == शून्य)
		वापस 1;

	/* TCP is complicated */
	अगर (cp->protocol == IPPROTO_TCP)
		वापस app_tcp_pkt_in(cp, skb, app, ipvsh);

	/*
	 *	Call निजी input hook function
	 */
	अगर (app->pkt_in == शून्य)
		वापस 1;

	वापस app->pkt_in(app, cp, skb, शून्य, ipvsh);
पूर्ण


#अगर_घोषित CONFIG_PROC_FS
/*
 *	/proc/net/ip_vs_app entry function
 */

अटल काष्ठा ip_vs_app *ip_vs_app_idx(काष्ठा netns_ipvs *ipvs, loff_t pos)
अणु
	काष्ठा ip_vs_app *app, *inc;

	list_क्रम_each_entry(app, &ipvs->app_list, a_list) अणु
		list_क्रम_each_entry(inc, &app->incs_list, a_list) अणु
			अगर (pos-- == 0)
				वापस inc;
		पूर्ण
	पूर्ण
	वापस शून्य;

पूर्ण

अटल व्योम *ip_vs_app_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	mutex_lock(&__ip_vs_app_mutex);

	वापस *pos ? ip_vs_app_idx(ipvs, *pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *ip_vs_app_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा ip_vs_app *inc, *app;
	काष्ठा list_head *e;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	++*pos;
	अगर (v == SEQ_START_TOKEN)
		वापस ip_vs_app_idx(ipvs, 0);

	inc = v;
	app = inc->app;

	अगर ((e = inc->a_list.next) != &app->incs_list)
		वापस list_entry(e, काष्ठा ip_vs_app, a_list);

	/* go on to next application */
	क्रम (e = app->a_list.next; e != &ipvs->app_list; e = e->next) अणु
		app = list_entry(e, काष्ठा ip_vs_app, a_list);
		list_क्रम_each_entry(inc, &app->incs_list, a_list) अणु
			वापस inc;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम ip_vs_app_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	mutex_unlock(&__ip_vs_app_mutex);
पूर्ण

अटल पूर्णांक ip_vs_app_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "prot port    usecnt name\n");
	अन्यथा अणु
		स्थिर काष्ठा ip_vs_app *inc = v;

		seq_म_लिखो(seq, "%-3s  %-7u %-6d %-17s\n",
			   ip_vs_proto_name(inc->protocol),
			   ntohs(inc->port),
			   atomic_पढ़ो(&inc->usecnt),
			   inc->name);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ip_vs_app_seq_ops = अणु
	.start = ip_vs_app_seq_start,
	.next  = ip_vs_app_seq_next,
	.stop  = ip_vs_app_seq_stop,
	.show  = ip_vs_app_seq_show,
पूर्ण;
#पूर्ण_अगर

पूर्णांक __net_init ip_vs_app_net_init(काष्ठा netns_ipvs *ipvs)
अणु
	INIT_LIST_HEAD(&ipvs->app_list);
	proc_create_net("ip_vs_app", 0, ipvs->net->proc_net, &ip_vs_app_seq_ops,
			माप(काष्ठा seq_net_निजी));
	वापस 0;
पूर्ण

व्योम __net_निकास ip_vs_app_net_cleanup(काष्ठा netns_ipvs *ipvs)
अणु
	unरेजिस्टर_ip_vs_app(ipvs, शून्य /* all */);
	हटाओ_proc_entry("ip_vs_app", ipvs->net->proc_net);
पूर्ण
