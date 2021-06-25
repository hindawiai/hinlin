<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies. */

#समावेश <linux/refcount.h>
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/netevent.h>
#समावेश <net/arp.h>
#समावेश "neigh.h"
#समावेश "tc.h"
#समावेश "en_rep.h"
#समावेश "fs_core.h"
#समावेश "diag/en_rep_tracepoint.h"

अटल अचिन्हित दीर्घ mlx5e_rep_ipv6_पूर्णांकerval(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_IPV6) && ipv6_stub->nd_tbl)
		वापस NEIGH_VAR(&ipv6_stub->nd_tbl->parms, DELAY_PROBE_TIME);

	वापस ~0UL;
पूर्ण

अटल व्योम mlx5e_rep_neigh_update_init_पूर्णांकerval(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	अचिन्हित दीर्घ ipv4_पूर्णांकerval = NEIGH_VAR(&arp_tbl.parms, DELAY_PROBE_TIME);
	अचिन्हित दीर्घ ipv6_पूर्णांकerval = mlx5e_rep_ipv6_पूर्णांकerval();
	काष्ठा net_device *netdev = rpriv->netdev;
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	rpriv->neigh_update.min_पूर्णांकerval = min_t(अचिन्हित दीर्घ, ipv6_पूर्णांकerval, ipv4_पूर्णांकerval);
	mlx5_fc_update_sampling_पूर्णांकerval(priv->mdev, rpriv->neigh_update.min_पूर्णांकerval);
पूर्ण

व्योम mlx5e_rep_queue_neigh_stats_work(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5e_neigh_update_table *neigh_update = &rpriv->neigh_update;

	mlx5_fc_queue_stats_work(priv->mdev,
				 &neigh_update->neigh_stats_work,
				 neigh_update->min_पूर्णांकerval);
पूर्ण

अटल bool mlx5e_rep_neigh_entry_hold(काष्ठा mlx5e_neigh_hash_entry *nhe)
अणु
	वापस refcount_inc_not_zero(&nhe->refcnt);
पूर्ण

अटल व्योम mlx5e_rep_neigh_entry_हटाओ(काष्ठा mlx5e_neigh_hash_entry *nhe);

व्योम mlx5e_rep_neigh_entry_release(काष्ठा mlx5e_neigh_hash_entry *nhe)
अणु
	अगर (refcount_dec_and_test(&nhe->refcnt)) अणु
		mlx5e_rep_neigh_entry_हटाओ(nhe);
		kमुक्त_rcu(nhe, rcu);
	पूर्ण
पूर्ण

अटल काष्ठा mlx5e_neigh_hash_entry *
mlx5e_get_next_nhe(काष्ठा mlx5e_rep_priv *rpriv,
		   काष्ठा mlx5e_neigh_hash_entry *nhe)
अणु
	काष्ठा mlx5e_neigh_hash_entry *next = शून्य;

	rcu_पढ़ो_lock();

	क्रम (next = nhe ?
		     list_next_or_null_rcu(&rpriv->neigh_update.neigh_list,
					   &nhe->neigh_list,
					   काष्ठा mlx5e_neigh_hash_entry,
					   neigh_list) :
		     list_first_or_null_rcu(&rpriv->neigh_update.neigh_list,
					    काष्ठा mlx5e_neigh_hash_entry,
					    neigh_list);
	     next;
	     next = list_next_or_null_rcu(&rpriv->neigh_update.neigh_list,
					  &next->neigh_list,
					  काष्ठा mlx5e_neigh_hash_entry,
					  neigh_list))
		अगर (mlx5e_rep_neigh_entry_hold(next))
			अवरोध;

	rcu_पढ़ो_unlock();

	अगर (nhe)
		mlx5e_rep_neigh_entry_release(nhe);

	वापस next;
पूर्ण

अटल व्योम mlx5e_rep_neigh_stats_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = container_of(work, काष्ठा mlx5e_rep_priv,
						    neigh_update.neigh_stats_work.work);
	काष्ठा net_device *netdev = rpriv->netdev;
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_neigh_hash_entry *nhe = शून्य;

	rtnl_lock();
	अगर (!list_empty(&rpriv->neigh_update.neigh_list))
		mlx5e_rep_queue_neigh_stats_work(priv);

	जबतक ((nhe = mlx5e_get_next_nhe(rpriv, nhe)) != शून्य)
		mlx5e_tc_update_neigh_used_value(nhe);

	rtnl_unlock();
पूर्ण

काष्ठा neigh_update_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा neighbour *n;
	काष्ठा mlx5e_neigh_hash_entry *nhe;
पूर्ण;

अटल व्योम mlx5e_release_neigh_update_work(काष्ठा neigh_update_work *update_work)
अणु
	neigh_release(update_work->n);
	mlx5e_rep_neigh_entry_release(update_work->nhe);
	kमुक्त(update_work);
पूर्ण

अटल व्योम mlx5e_rep_neigh_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा neigh_update_work *update_work = container_of(work, काष्ठा neigh_update_work,
							     work);
	काष्ठा mlx5e_neigh_hash_entry *nhe = update_work->nhe;
	काष्ठा neighbour *n = update_work->n;
	काष्ठा mlx5e_encap_entry *e = शून्य;
	bool neigh_connected, same_dev;
	अचिन्हित अक्षर ha[ETH_ALEN];
	u8 nud_state, dead;

	rtnl_lock();

	/* If these parameters are changed after we release the lock,
	 * we'll receive another event letting us know about it.
	 * We use this lock to aव्योम inconsistency between the neigh validity
	 * and it's hw address.
	 */
	पढ़ो_lock_bh(&n->lock);
	स_नकल(ha, n->ha, ETH_ALEN);
	nud_state = n->nud_state;
	dead = n->dead;
	same_dev = READ_ONCE(nhe->neigh_dev) == n->dev;
	पढ़ो_unlock_bh(&n->lock);

	neigh_connected = (nud_state & NUD_VALID) && !dead;

	trace_mlx5e_rep_neigh_update(nhe, ha, neigh_connected);

	अगर (!same_dev)
		जाओ out;

	/* mlx5e_get_next_init_encap() releases previous encap beक्रमe वापसing
	 * the next one.
	 */
	जबतक ((e = mlx5e_get_next_init_encap(nhe, e)) != शून्य)
		mlx5e_rep_update_flows(netdev_priv(e->out_dev), e, neigh_connected, ha);

out:
	rtnl_unlock();
	mlx5e_release_neigh_update_work(update_work);
पूर्ण

अटल काष्ठा neigh_update_work *mlx5e_alloc_neigh_update_work(काष्ठा mlx5e_priv *priv,
							       काष्ठा neighbour *n)
अणु
	काष्ठा neigh_update_work *update_work;
	काष्ठा mlx5e_neigh_hash_entry *nhe;
	काष्ठा mlx5e_neigh m_neigh = अणुपूर्ण;

	update_work = kzalloc(माप(*update_work), GFP_ATOMIC);
	अगर (WARN_ON(!update_work))
		वापस शून्य;

	m_neigh.family = n->ops->family;
	स_नकल(&m_neigh.dst_ip, n->primary_key, n->tbl->key_len);

	/* Obtain reference to nhe as last step in order not to release it in
	 * atomic context.
	 */
	rcu_पढ़ो_lock();
	nhe = mlx5e_rep_neigh_entry_lookup(priv, &m_neigh);
	rcu_पढ़ो_unlock();
	अगर (!nhe) अणु
		kमुक्त(update_work);
		वापस शून्य;
	पूर्ण

	INIT_WORK(&update_work->work, mlx5e_rep_neigh_update);
	neigh_hold(n);
	update_work->n = n;
	update_work->nhe = nhe;

	वापस update_work;
पूर्ण

अटल पूर्णांक mlx5e_rep_netevent_event(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = container_of(nb, काष्ठा mlx5e_rep_priv,
						    neigh_update.netevent_nb);
	काष्ठा mlx5e_neigh_update_table *neigh_update = &rpriv->neigh_update;
	काष्ठा net_device *netdev = rpriv->netdev;
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_neigh_hash_entry *nhe = शून्य;
	काष्ठा neigh_update_work *update_work;
	काष्ठा neigh_parms *p;
	काष्ठा neighbour *n;
	bool found = false;

	चयन (event) अणु
	हाल NETEVENT_NEIGH_UPDATE:
		n = ptr;
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (n->tbl != ipv6_stub->nd_tbl && n->tbl != &arp_tbl)
#अन्यथा
		अगर (n->tbl != &arp_tbl)
#पूर्ण_अगर
			वापस NOTIFY_DONE;

		update_work = mlx5e_alloc_neigh_update_work(priv, n);
		अगर (!update_work)
			वापस NOTIFY_DONE;

		queue_work(priv->wq, &update_work->work);
		अवरोध;

	हाल NETEVENT_DELAY_PROBE_TIME_UPDATE:
		p = ptr;

		/* We check the device is present since we करोn't care about
		 * changes in the शेष table, we only care about changes
		 * करोne per device delay prob समय parameter.
		 */
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (!p->dev || (p->tbl != ipv6_stub->nd_tbl && p->tbl != &arp_tbl))
#अन्यथा
		अगर (!p->dev || p->tbl != &arp_tbl)
#पूर्ण_अगर
			वापस NOTIFY_DONE;

		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(nhe, &neigh_update->neigh_list,
					neigh_list) अणु
			अगर (p->dev == READ_ONCE(nhe->neigh_dev)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
		अगर (!found)
			वापस NOTIFY_DONE;

		neigh_update->min_पूर्णांकerval = min_t(अचिन्हित दीर्घ,
						   NEIGH_VAR(p, DELAY_PROBE_TIME),
						   neigh_update->min_पूर्णांकerval);
		mlx5_fc_update_sampling_पूर्णांकerval(priv->mdev,
						 neigh_update->min_पूर्णांकerval);
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params mlx5e_neigh_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा mlx5e_neigh_hash_entry, rhash_node),
	.key_offset = दुरत्व(काष्ठा mlx5e_neigh_hash_entry, m_neigh),
	.key_len = माप(काष्ठा mlx5e_neigh),
	.स्वतःmatic_shrinking = true,
पूर्ण;

पूर्णांक mlx5e_rep_neigh_init(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	काष्ठा mlx5e_neigh_update_table *neigh_update = &rpriv->neigh_update;
	पूर्णांक err;

	err = rhashtable_init(&neigh_update->neigh_ht, &mlx5e_neigh_ht_params);
	अगर (err)
		जाओ out_err;

	INIT_LIST_HEAD(&neigh_update->neigh_list);
	mutex_init(&neigh_update->encap_lock);
	INIT_DELAYED_WORK(&neigh_update->neigh_stats_work,
			  mlx5e_rep_neigh_stats_work);
	mlx5e_rep_neigh_update_init_पूर्णांकerval(rpriv);

	neigh_update->netevent_nb.notअगरier_call = mlx5e_rep_netevent_event;
	err = रेजिस्टर_netevent_notअगरier(&neigh_update->netevent_nb);
	अगर (err)
		जाओ out_notअगरier;
	वापस 0;

out_notअगरier:
	neigh_update->netevent_nb.notअगरier_call = शून्य;
	rhashtable_destroy(&neigh_update->neigh_ht);
out_err:
	netdev_warn(rpriv->netdev,
		    "Failed to initialize neighbours handling for vport %d\n",
		    rpriv->rep->vport);
	वापस err;
पूर्ण

व्योम mlx5e_rep_neigh_cleanup(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	काष्ठा mlx5e_neigh_update_table *neigh_update = &rpriv->neigh_update;
	काष्ठा mlx5e_priv *priv = netdev_priv(rpriv->netdev);

	अगर (!rpriv->neigh_update.netevent_nb.notअगरier_call)
		वापस;

	unरेजिस्टर_netevent_notअगरier(&neigh_update->netevent_nb);

	flush_workqueue(priv->wq); /* flush neigh update works */

	cancel_delayed_work_sync(&rpriv->neigh_update.neigh_stats_work);

	mutex_destroy(&neigh_update->encap_lock);
	rhashtable_destroy(&neigh_update->neigh_ht);
पूर्ण

अटल पूर्णांक mlx5e_rep_neigh_entry_insert(काष्ठा mlx5e_priv *priv,
					काष्ठा mlx5e_neigh_hash_entry *nhe)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	पूर्णांक err;

	err = rhashtable_insert_fast(&rpriv->neigh_update.neigh_ht,
				     &nhe->rhash_node,
				     mlx5e_neigh_ht_params);
	अगर (err)
		वापस err;

	list_add_rcu(&nhe->neigh_list, &rpriv->neigh_update.neigh_list);

	वापस err;
पूर्ण

अटल व्योम mlx5e_rep_neigh_entry_हटाओ(काष्ठा mlx5e_neigh_hash_entry *nhe)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = nhe->priv->ppriv;

	mutex_lock(&rpriv->neigh_update.encap_lock);

	list_del_rcu(&nhe->neigh_list);

	rhashtable_हटाओ_fast(&rpriv->neigh_update.neigh_ht,
			       &nhe->rhash_node,
			       mlx5e_neigh_ht_params);
	mutex_unlock(&rpriv->neigh_update.encap_lock);
पूर्ण

/* This function must only be called under the representor's encap_lock or
 * inside rcu पढ़ो lock section.
 */
काष्ठा mlx5e_neigh_hash_entry *
mlx5e_rep_neigh_entry_lookup(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_neigh *m_neigh)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5e_neigh_update_table *neigh_update = &rpriv->neigh_update;
	काष्ठा mlx5e_neigh_hash_entry *nhe;

	nhe = rhashtable_lookup_fast(&neigh_update->neigh_ht, m_neigh,
				     mlx5e_neigh_ht_params);
	वापस nhe && mlx5e_rep_neigh_entry_hold(nhe) ? nhe : शून्य;
पूर्ण

पूर्णांक mlx5e_rep_neigh_entry_create(काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5e_neigh *m_neigh,
				 काष्ठा net_device *neigh_dev,
				 काष्ठा mlx5e_neigh_hash_entry **nhe)
अणु
	पूर्णांक err;

	*nhe = kzalloc(माप(**nhe), GFP_KERNEL);
	अगर (!*nhe)
		वापस -ENOMEM;

	(*nhe)->priv = priv;
	स_नकल(&(*nhe)->m_neigh, m_neigh, माप(*m_neigh));
	spin_lock_init(&(*nhe)->encap_list_lock);
	INIT_LIST_HEAD(&(*nhe)->encap_list);
	refcount_set(&(*nhe)->refcnt, 1);
	WRITE_ONCE((*nhe)->neigh_dev, neigh_dev);

	err = mlx5e_rep_neigh_entry_insert(priv, *nhe);
	अगर (err)
		जाओ out_मुक्त;
	वापस 0;

out_मुक्त:
	kमुक्त(*nhe);
	वापस err;
पूर्ण
