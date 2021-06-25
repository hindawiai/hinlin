<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * connection tracking event cache.
 */

#अगर_अघोषित _NF_CONNTRACK_ECACHE_H
#घोषणा _NF_CONNTRACK_ECACHE_H
#समावेश <net/netfilter/nf_conntrack.h>

#समावेश <net/net_namespace.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>

क्रमागत nf_ct_ecache_state अणु
	NFCT_ECACHE_UNKNOWN,		/* destroy event not sent */
	NFCT_ECACHE_DESTROY_FAIL,	/* tried but failed to send destroy event */
	NFCT_ECACHE_DESTROY_SENT,	/* sent destroy event after failure */
पूर्ण;

काष्ठा nf_conntrack_ecache अणु
	अचिन्हित दीर्घ cache;		/* bitops want दीर्घ */
	u16 missed;			/* missed events */
	u16 cपंचांगask;			/* biपंचांगask of ct events to be delivered */
	u16 expmask;			/* biपंचांगask of expect events to be delivered */
	क्रमागत nf_ct_ecache_state state:8;/* ecache state */
	u32 portid;			/* netlink portid of destroyer */
पूर्ण;

अटल अंतरभूत काष्ठा nf_conntrack_ecache *
nf_ct_ecache_find(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	वापस nf_ct_ext_find(ct, NF_CT_EXT_ECACHE);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा nf_conntrack_ecache *
nf_ct_ecache_ext_add(काष्ठा nf_conn *ct, u16 cपंचांगask, u16 expmask, gfp_t gfp)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_conntrack_ecache *e;

	अगर (!cपंचांगask && !expmask && net->ct.sysctl_events) अणु
		cपंचांगask = ~0;
		expmask = ~0;
	पूर्ण
	अगर (!cपंचांगask && !expmask)
		वापस शून्य;

	e = nf_ct_ext_add(ct, NF_CT_EXT_ECACHE, gfp);
	अगर (e) अणु
		e->cपंचांगask  = cपंचांगask;
		e->expmask = expmask;
	पूर्ण
	वापस e;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS

/* This काष्ठाure is passed to event handler */
काष्ठा nf_ct_event अणु
	काष्ठा nf_conn *ct;
	u32 portid;
	पूर्णांक report;
पूर्ण;

काष्ठा nf_ct_event_notअगरier अणु
	पूर्णांक (*fcn)(अचिन्हित पूर्णांक events, काष्ठा nf_ct_event *item);
पूर्ण;

पूर्णांक nf_conntrack_रेजिस्टर_notअगरier(काष्ठा net *net,
				   काष्ठा nf_ct_event_notअगरier *nb);
व्योम nf_conntrack_unरेजिस्टर_notअगरier(काष्ठा net *net,
				      काष्ठा nf_ct_event_notअगरier *nb);

व्योम nf_ct_deliver_cached_events(काष्ठा nf_conn *ct);
पूर्णांक nf_conntrack_evenपंचांगask_report(अचिन्हित पूर्णांक evenपंचांगask, काष्ठा nf_conn *ct,
				  u32 portid, पूर्णांक report);

#अन्यथा

अटल अंतरभूत व्योम nf_ct_deliver_cached_events(स्थिर काष्ठा nf_conn *ct)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक nf_conntrack_evenपंचांगask_report(अचिन्हित पूर्णांक evenपंचांगask,
						काष्ठा nf_conn *ct,
						u32 portid,
						पूर्णांक report)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत व्योम
nf_conntrack_event_cache(क्रमागत ip_conntrack_events event, काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_conntrack_ecache *e;

	अगर (!rcu_access_poपूर्णांकer(net->ct.nf_conntrack_event_cb))
		वापस;

	e = nf_ct_ecache_find(ct);
	अगर (e == शून्य)
		वापस;

	set_bit(event, &e->cache);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक
nf_conntrack_event_report(क्रमागत ip_conntrack_events event, काष्ठा nf_conn *ct,
			  u32 portid, पूर्णांक report)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	स्थिर काष्ठा net *net = nf_ct_net(ct);

	अगर (!rcu_access_poपूर्णांकer(net->ct.nf_conntrack_event_cb))
		वापस 0;

	वापस nf_conntrack_evenपंचांगask_report(1 << event, ct, portid, report);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक
nf_conntrack_event(क्रमागत ip_conntrack_events event, काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	स्थिर काष्ठा net *net = nf_ct_net(ct);

	अगर (!rcu_access_poपूर्णांकer(net->ct.nf_conntrack_event_cb))
		वापस 0;

	वापस nf_conntrack_evenपंचांगask_report(1 << event, ct, 0, 0);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS

काष्ठा nf_exp_event अणु
	काष्ठा nf_conntrack_expect *exp;
	u32 portid;
	पूर्णांक report;
पूर्ण;

काष्ठा nf_exp_event_notअगरier अणु
	पूर्णांक (*fcn)(अचिन्हित पूर्णांक events, काष्ठा nf_exp_event *item);
पूर्ण;

पूर्णांक nf_ct_expect_रेजिस्टर_notअगरier(काष्ठा net *net,
				   काष्ठा nf_exp_event_notअगरier *nb);
व्योम nf_ct_expect_unरेजिस्टर_notअगरier(काष्ठा net *net,
				      काष्ठा nf_exp_event_notअगरier *nb);

व्योम nf_ct_expect_event_report(क्रमागत ip_conntrack_expect_events event,
			       काष्ठा nf_conntrack_expect *exp,
			       u32 portid, पूर्णांक report);

व्योम nf_conntrack_ecache_work(काष्ठा net *net, क्रमागत nf_ct_ecache_state state);

व्योम nf_conntrack_ecache_pernet_init(काष्ठा net *net);
व्योम nf_conntrack_ecache_pernet_fini(काष्ठा net *net);

पूर्णांक nf_conntrack_ecache_init(व्योम);
व्योम nf_conntrack_ecache_fini(व्योम);

अटल अंतरभूत bool nf_conntrack_ecache_dwork_pending(स्थिर काष्ठा net *net)
अणु
	वापस net->ct.ecache_dwork_pending;
पूर्ण
#अन्यथा /* CONFIG_NF_CONNTRACK_EVENTS */

अटल अंतरभूत व्योम nf_ct_expect_event_report(क्रमागत ip_conntrack_expect_events e,
					     काष्ठा nf_conntrack_expect *exp,
					     u32 portid,
					     पूर्णांक report)
अणु
पूर्ण

अटल अंतरभूत व्योम nf_conntrack_ecache_work(काष्ठा net *net,
					    क्रमागत nf_ct_ecache_state s)
अणु
पूर्ण

अटल अंतरभूत व्योम nf_conntrack_ecache_pernet_init(काष्ठा net *net)
अणु
पूर्ण

अटल अंतरभूत व्योम nf_conntrack_ecache_pernet_fini(काष्ठा net *net)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक nf_conntrack_ecache_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nf_conntrack_ecache_fini(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool nf_conntrack_ecache_dwork_pending(स्थिर काष्ठा net *net) अणु वापस false; पूर्ण
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_EVENTS */
#पूर्ण_अगर /*_NF_CONNTRACK_ECACHE_H*/
