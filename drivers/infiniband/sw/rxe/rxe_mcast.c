<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश "rxe.h"
#समावेश "rxe_loc.h"

/* caller should hold mc_grp_pool->pool_lock */
अटल काष्ठा rxe_mc_grp *create_grp(काष्ठा rxe_dev *rxe,
				     काष्ठा rxe_pool *pool,
				     जोड़ ib_gid *mgid)
अणु
	पूर्णांक err;
	काष्ठा rxe_mc_grp *grp;

	grp = rxe_alloc_locked(&rxe->mc_grp_pool);
	अगर (!grp)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&grp->qp_list);
	spin_lock_init(&grp->mcg_lock);
	grp->rxe = rxe;
	rxe_add_key_locked(grp, mgid);

	err = rxe_mcast_add(rxe, mgid);
	अगर (unlikely(err)) अणु
		rxe_drop_key_locked(grp);
		rxe_drop_ref(grp);
		वापस ERR_PTR(err);
	पूर्ण

	वापस grp;
पूर्ण

पूर्णांक rxe_mcast_get_grp(काष्ठा rxe_dev *rxe, जोड़ ib_gid *mgid,
		      काष्ठा rxe_mc_grp **grp_p)
अणु
	पूर्णांक err;
	काष्ठा rxe_mc_grp *grp;
	काष्ठा rxe_pool *pool = &rxe->mc_grp_pool;
	अचिन्हित दीर्घ flags;

	अगर (rxe->attr.max_mcast_qp_attach == 0)
		वापस -EINVAL;

	ग_लिखो_lock_irqsave(&pool->pool_lock, flags);

	grp = rxe_pool_get_key_locked(pool, mgid);
	अगर (grp)
		जाओ करोne;

	grp = create_grp(rxe, pool, mgid);
	अगर (IS_ERR(grp)) अणु
		ग_लिखो_unlock_irqrestore(&pool->pool_lock, flags);
		err = PTR_ERR(grp);
		वापस err;
	पूर्ण

करोne:
	ग_लिखो_unlock_irqrestore(&pool->pool_lock, flags);
	*grp_p = grp;
	वापस 0;
पूर्ण

पूर्णांक rxe_mcast_add_grp_elem(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp,
			   काष्ठा rxe_mc_grp *grp)
अणु
	पूर्णांक err;
	काष्ठा rxe_mc_elem *elem;

	/* check to see of the qp is alपढ़ोy a member of the group */
	spin_lock_bh(&qp->grp_lock);
	spin_lock_bh(&grp->mcg_lock);
	list_क्रम_each_entry(elem, &grp->qp_list, qp_list) अणु
		अगर (elem->qp == qp) अणु
			err = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (grp->num_qp >= rxe->attr.max_mcast_qp_attach) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	elem = rxe_alloc(&rxe->mc_elem_pool);
	अगर (!elem) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* each qp holds a ref on the grp */
	rxe_add_ref(grp);

	grp->num_qp++;
	elem->qp = qp;
	elem->grp = grp;

	list_add(&elem->qp_list, &grp->qp_list);
	list_add(&elem->grp_list, &qp->grp_list);

	err = 0;
out:
	spin_unlock_bh(&grp->mcg_lock);
	spin_unlock_bh(&qp->grp_lock);
	वापस err;
पूर्ण

पूर्णांक rxe_mcast_drop_grp_elem(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp,
			    जोड़ ib_gid *mgid)
अणु
	काष्ठा rxe_mc_grp *grp;
	काष्ठा rxe_mc_elem *elem, *पंचांगp;

	grp = rxe_pool_get_key(&rxe->mc_grp_pool, mgid);
	अगर (!grp)
		जाओ err1;

	spin_lock_bh(&qp->grp_lock);
	spin_lock_bh(&grp->mcg_lock);

	list_क्रम_each_entry_safe(elem, पंचांगp, &grp->qp_list, qp_list) अणु
		अगर (elem->qp == qp) अणु
			list_del(&elem->qp_list);
			list_del(&elem->grp_list);
			grp->num_qp--;

			spin_unlock_bh(&grp->mcg_lock);
			spin_unlock_bh(&qp->grp_lock);
			rxe_drop_ref(elem);
			rxe_drop_ref(grp);	/* ref held by QP */
			rxe_drop_ref(grp);	/* ref from get_key */
			वापस 0;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&grp->mcg_lock);
	spin_unlock_bh(&qp->grp_lock);
	rxe_drop_ref(grp);			/* ref from get_key */
err1:
	वापस -EINVAL;
पूर्ण

व्योम rxe_drop_all_mcast_groups(काष्ठा rxe_qp *qp)
अणु
	काष्ठा rxe_mc_grp *grp;
	काष्ठा rxe_mc_elem *elem;

	जबतक (1) अणु
		spin_lock_bh(&qp->grp_lock);
		अगर (list_empty(&qp->grp_list)) अणु
			spin_unlock_bh(&qp->grp_lock);
			अवरोध;
		पूर्ण
		elem = list_first_entry(&qp->grp_list, काष्ठा rxe_mc_elem,
					grp_list);
		list_del(&elem->grp_list);
		spin_unlock_bh(&qp->grp_lock);

		grp = elem->grp;
		spin_lock_bh(&grp->mcg_lock);
		list_del(&elem->qp_list);
		grp->num_qp--;
		spin_unlock_bh(&grp->mcg_lock);
		rxe_drop_ref(grp);
		rxe_drop_ref(elem);
	पूर्ण
पूर्ण

व्योम rxe_mc_cleanup(काष्ठा rxe_pool_entry *arg)
अणु
	काष्ठा rxe_mc_grp *grp = container_of(arg, typeof(*grp), pelem);
	काष्ठा rxe_dev *rxe = grp->rxe;

	rxe_drop_key(grp);
	rxe_mcast_delete(rxe, &grp->mgid);
पूर्ण
