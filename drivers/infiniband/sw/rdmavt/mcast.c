<शैली गुरु>
/*
 * Copyright(c) 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/rculist.h>
#समावेश <rdma/rdma_vt.h>
#समावेश <rdma/rdmavt_qp.h>

#समावेश "mcast.h"

/**
 * rvt_driver_mcast_init - init resources क्रम multicast
 * @rdi: rvt dev काष्ठा
 *
 * This is per device that रेजिस्टरs with rdmavt
 */
व्योम rvt_driver_mcast_init(काष्ठा rvt_dev_info *rdi)
अणु
	/*
	 * Anything that needs setup क्रम multicast on a per driver or per rdi
	 * basis should be करोne in here.
	 */
	spin_lock_init(&rdi->n_mcast_grps_lock);
पूर्ण

/**
 * rvt_mcast_qp_alloc - alloc a काष्ठा to link a QP to mcast GID काष्ठा
 * @qp: the QP to link
 */
अटल काष्ठा rvt_mcast_qp *rvt_mcast_qp_alloc(काष्ठा rvt_qp *qp)
अणु
	काष्ठा rvt_mcast_qp *mqp;

	mqp = kदो_स्मृति(माप(*mqp), GFP_KERNEL);
	अगर (!mqp)
		जाओ bail;

	mqp->qp = qp;
	rvt_get_qp(qp);

bail:
	वापस mqp;
पूर्ण

अटल व्योम rvt_mcast_qp_मुक्त(काष्ठा rvt_mcast_qp *mqp)
अणु
	काष्ठा rvt_qp *qp = mqp->qp;

	/* Notअगरy hfi1_destroy_qp() अगर it is रुकोing. */
	rvt_put_qp(qp);

	kमुक्त(mqp);
पूर्ण

/**
 * rvt_mcast_alloc - allocate the multicast GID काष्ठाure
 * @mgid: the multicast GID
 * @lid: the muilticast LID (host order)
 *
 * A list of QPs will be attached to this काष्ठाure.
 */
अटल काष्ठा rvt_mcast *rvt_mcast_alloc(जोड़ ib_gid *mgid, u16 lid)
अणु
	काष्ठा rvt_mcast *mcast;

	mcast = kzalloc(माप(*mcast), GFP_KERNEL);
	अगर (!mcast)
		जाओ bail;

	mcast->mcast_addr.mgid = *mgid;
	mcast->mcast_addr.lid = lid;

	INIT_LIST_HEAD(&mcast->qp_list);
	init_रुकोqueue_head(&mcast->रुको);
	atomic_set(&mcast->refcount, 0);

bail:
	वापस mcast;
पूर्ण

अटल व्योम rvt_mcast_मुक्त(काष्ठा rvt_mcast *mcast)
अणु
	काष्ठा rvt_mcast_qp *p, *पंचांगp;

	list_क्रम_each_entry_safe(p, पंचांगp, &mcast->qp_list, list)
		rvt_mcast_qp_मुक्त(p);

	kमुक्त(mcast);
पूर्ण

/**
 * rvt_mcast_find - search the global table क्रम the given multicast GID/LID
 * NOTE: It is valid to have 1 MLID with multiple MGIDs.  It is not valid
 * to have 1 MGID with multiple MLIDs.
 * @ibp: the IB port काष्ठाure
 * @mgid: the multicast GID to search क्रम
 * @lid: the multicast LID portion of the multicast address (host order)
 *
 * The caller is responsible क्रम decrementing the reference count अगर found.
 *
 * Return: शून्य अगर not found.
 */
काष्ठा rvt_mcast *rvt_mcast_find(काष्ठा rvt_ibport *ibp, जोड़ ib_gid *mgid,
				 u16 lid)
अणु
	काष्ठा rb_node *n;
	अचिन्हित दीर्घ flags;
	काष्ठा rvt_mcast *found = शून्य;

	spin_lock_irqsave(&ibp->lock, flags);
	n = ibp->mcast_tree.rb_node;
	जबतक (n) अणु
		पूर्णांक ret;
		काष्ठा rvt_mcast *mcast;

		mcast = rb_entry(n, काष्ठा rvt_mcast, rb_node);

		ret = स_भेद(mgid->raw, mcast->mcast_addr.mgid.raw,
			     माप(*mgid));
		अगर (ret < 0) अणु
			n = n->rb_left;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			n = n->rb_right;
		पूर्ण अन्यथा अणु
			/* MGID/MLID must match */
			अगर (mcast->mcast_addr.lid == lid) अणु
				atomic_inc(&mcast->refcount);
				found = mcast;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ibp->lock, flags);
	वापस found;
पूर्ण
EXPORT_SYMBOL(rvt_mcast_find);

/*
 * rvt_mcast_add - insert mcast GID पूर्णांकo table and attach QP काष्ठा
 * @mcast: the mcast GID table
 * @mqp: the QP to attach
 *
 * Return: zero अगर both were added.  Return EEXIST अगर the GID was alपढ़ोy in
 * the table but the QP was added.  Return ESRCH अगर the QP was alपढ़ोy
 * attached and neither काष्ठाure was added. Return EINVAL अगर the MGID was
 * found, but the MLID did NOT match.
 */
अटल पूर्णांक rvt_mcast_add(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_ibport *ibp,
			 काष्ठा rvt_mcast *mcast, काष्ठा rvt_mcast_qp *mqp)
अणु
	काष्ठा rb_node **n = &ibp->mcast_tree.rb_node;
	काष्ठा rb_node *pn = शून्य;
	पूर्णांक ret;

	spin_lock_irq(&ibp->lock);

	जबतक (*n) अणु
		काष्ठा rvt_mcast *पंचांगcast;
		काष्ठा rvt_mcast_qp *p;

		pn = *n;
		पंचांगcast = rb_entry(pn, काष्ठा rvt_mcast, rb_node);

		ret = स_भेद(mcast->mcast_addr.mgid.raw,
			     पंचांगcast->mcast_addr.mgid.raw,
			     माप(mcast->mcast_addr.mgid));
		अगर (ret < 0) अणु
			n = &pn->rb_left;
			जारी;
		पूर्ण
		अगर (ret > 0) अणु
			n = &pn->rb_right;
			जारी;
		पूर्ण

		अगर (पंचांगcast->mcast_addr.lid != mcast->mcast_addr.lid) अणु
			ret = EINVAL;
			जाओ bail;
		पूर्ण

		/* Search the QP list to see अगर this is alपढ़ोy there. */
		list_क्रम_each_entry_rcu(p, &पंचांगcast->qp_list, list) अणु
			अगर (p->qp == mqp->qp) अणु
				ret = ESRCH;
				जाओ bail;
			पूर्ण
		पूर्ण
		अगर (पंचांगcast->n_attached ==
		    rdi->dparms.props.max_mcast_qp_attach) अणु
			ret = ENOMEM;
			जाओ bail;
		पूर्ण

		पंचांगcast->n_attached++;

		list_add_tail_rcu(&mqp->list, &पंचांगcast->qp_list);
		ret = EEXIST;
		जाओ bail;
	पूर्ण

	spin_lock(&rdi->n_mcast_grps_lock);
	अगर (rdi->n_mcast_grps_allocated == rdi->dparms.props.max_mcast_grp) अणु
		spin_unlock(&rdi->n_mcast_grps_lock);
		ret = ENOMEM;
		जाओ bail;
	पूर्ण

	rdi->n_mcast_grps_allocated++;
	spin_unlock(&rdi->n_mcast_grps_lock);

	mcast->n_attached++;

	list_add_tail_rcu(&mqp->list, &mcast->qp_list);

	atomic_inc(&mcast->refcount);
	rb_link_node(&mcast->rb_node, pn, n);
	rb_insert_color(&mcast->rb_node, &ibp->mcast_tree);

	ret = 0;

bail:
	spin_unlock_irq(&ibp->lock);

	वापस ret;
पूर्ण

/**
 * rvt_attach_mcast - attach a qp to a multicast group
 * @ibqp: Infiniband qp
 * @gid: multicast guid
 * @lid: multicast lid
 *
 * Return: 0 on success
 */
पूर्णांक rvt_attach_mcast(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid)
अणु
	काष्ठा rvt_qp *qp = ibqp_to_rvtqp(ibqp);
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);
	काष्ठा rvt_ibport *ibp = rdi->ports[qp->port_num - 1];
	काष्ठा rvt_mcast *mcast;
	काष्ठा rvt_mcast_qp *mqp;
	पूर्णांक ret = -ENOMEM;

	अगर (ibqp->qp_num <= 1 || qp->state == IB_QPS_RESET)
		वापस -EINVAL;

	/*
	 * Allocate data काष्ठाures since its better to करो this outside of
	 * spin locks and it will most likely be needed.
	 */
	mcast = rvt_mcast_alloc(gid, lid);
	अगर (!mcast)
		वापस -ENOMEM;

	mqp = rvt_mcast_qp_alloc(qp);
	अगर (!mqp)
		जाओ bail_mcast;

	चयन (rvt_mcast_add(rdi, ibp, mcast, mqp)) अणु
	हाल ESRCH:
		/* Neither was used: OK to attach the same QP twice. */
		ret = 0;
		जाओ bail_mqp;
	हाल EEXIST: /* The mcast wasn't used */
		ret = 0;
		जाओ bail_mcast;
	हाल ENOMEM:
		/* Exceeded the maximum number of mcast groups. */
		ret = -ENOMEM;
		जाओ bail_mqp;
	हाल EINVAL:
		/* Invalid MGID/MLID pair */
		ret = -EINVAL;
		जाओ bail_mqp;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;

bail_mqp:
	rvt_mcast_qp_मुक्त(mqp);

bail_mcast:
	rvt_mcast_मुक्त(mcast);

	वापस ret;
पूर्ण

/**
 * rvt_detach_mcast - हटाओ a qp from a multicast group
 * @ibqp: Infiniband qp
 * @gid: multicast guid
 * @lid: multicast lid
 *
 * Return: 0 on success
 */
पूर्णांक rvt_detach_mcast(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid)
अणु
	काष्ठा rvt_qp *qp = ibqp_to_rvtqp(ibqp);
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);
	काष्ठा rvt_ibport *ibp = rdi->ports[qp->port_num - 1];
	काष्ठा rvt_mcast *mcast = शून्य;
	काष्ठा rvt_mcast_qp *p, *पंचांगp, *delp = शून्य;
	काष्ठा rb_node *n;
	पूर्णांक last = 0;
	पूर्णांक ret = 0;

	अगर (ibqp->qp_num <= 1)
		वापस -EINVAL;

	spin_lock_irq(&ibp->lock);

	/* Find the GID in the mcast table. */
	n = ibp->mcast_tree.rb_node;
	जबतक (1) अणु
		अगर (!n) अणु
			spin_unlock_irq(&ibp->lock);
			वापस -EINVAL;
		पूर्ण

		mcast = rb_entry(n, काष्ठा rvt_mcast, rb_node);
		ret = स_भेद(gid->raw, mcast->mcast_addr.mgid.raw,
			     माप(*gid));
		अगर (ret < 0) अणु
			n = n->rb_left;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			n = n->rb_right;
		पूर्ण अन्यथा अणु
			/* MGID/MLID must match */
			अगर (mcast->mcast_addr.lid != lid) अणु
				spin_unlock_irq(&ibp->lock);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* Search the QP list. */
	list_क्रम_each_entry_safe(p, पंचांगp, &mcast->qp_list, list) अणु
		अगर (p->qp != qp)
			जारी;
		/*
		 * We found it, so हटाओ it, but करोn't poison the क्रमward
		 * link until we are sure there are no list walkers.
		 */
		list_del_rcu(&p->list);
		mcast->n_attached--;
		delp = p;

		/* If this was the last attached QP, हटाओ the GID too. */
		अगर (list_empty(&mcast->qp_list)) अणु
			rb_erase(&mcast->rb_node, &ibp->mcast_tree);
			last = 1;
		पूर्ण
		अवरोध;
	पूर्ण

	spin_unlock_irq(&ibp->lock);
	/* QP not attached */
	अगर (!delp)
		वापस -EINVAL;

	/*
	 * Wait क्रम any list walkers to finish beक्रमe मुक्तing the
	 * list element.
	 */
	रुको_event(mcast->रुको, atomic_पढ़ो(&mcast->refcount) <= 1);
	rvt_mcast_qp_मुक्त(delp);

	अगर (last) अणु
		atomic_dec(&mcast->refcount);
		रुको_event(mcast->रुको, !atomic_पढ़ो(&mcast->refcount));
		rvt_mcast_मुक्त(mcast);
		spin_lock_irq(&rdi->n_mcast_grps_lock);
		rdi->n_mcast_grps_allocated--;
		spin_unlock_irq(&rdi->n_mcast_grps_lock);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rvt_mcast_tree_empty - determine अगर any qps are attached to any mcast group
 * @rdi: rvt dev काष्ठा
 *
 * Return: in use count
 */
पूर्णांक rvt_mcast_tree_empty(काष्ठा rvt_dev_info *rdi)
अणु
	पूर्णांक i;
	पूर्णांक in_use = 0;

	क्रम (i = 0; i < rdi->dparms.nports; i++)
		अगर (rdi->ports[i]->mcast_tree.rb_node)
			in_use++;
	वापस in_use;
पूर्ण
