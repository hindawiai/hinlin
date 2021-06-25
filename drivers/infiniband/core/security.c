<शैली गुरु>
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/security.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_cache.h>
#समावेश "core_priv.h"
#समावेश "mad_priv.h"

अटल LIST_HEAD(mad_agent_list);
/* Lock to protect mad_agent_list */
अटल DEFINE_SPINLOCK(mad_agent_list_lock);

अटल काष्ठा pkey_index_qp_list *get_pkey_idx_qp_list(काष्ठा ib_port_pkey *pp)
अणु
	काष्ठा pkey_index_qp_list *pkey = शून्य;
	काष्ठा pkey_index_qp_list *पंचांगp_pkey;
	काष्ठा ib_device *dev = pp->sec->dev;

	spin_lock(&dev->port_data[pp->port_num].pkey_list_lock);
	list_क्रम_each_entry (पंचांगp_pkey, &dev->port_data[pp->port_num].pkey_list,
			     pkey_index_list) अणु
		अगर (पंचांगp_pkey->pkey_index == pp->pkey_index) अणु
			pkey = पंचांगp_pkey;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&dev->port_data[pp->port_num].pkey_list_lock);
	वापस pkey;
पूर्ण

अटल पूर्णांक get_pkey_and_subnet_prefix(काष्ठा ib_port_pkey *pp,
				      u16 *pkey,
				      u64 *subnet_prefix)
अणु
	काष्ठा ib_device *dev = pp->sec->dev;
	पूर्णांक ret;

	ret = ib_get_cached_pkey(dev, pp->port_num, pp->pkey_index, pkey);
	अगर (ret)
		वापस ret;

	ret = ib_get_cached_subnet_prefix(dev, pp->port_num, subnet_prefix);

	वापस ret;
पूर्ण

अटल पूर्णांक enक्रमce_qp_pkey_security(u16 pkey,
				    u64 subnet_prefix,
				    काष्ठा ib_qp_security *qp_sec)
अणु
	काष्ठा ib_qp_security *shared_qp_sec;
	पूर्णांक ret;

	ret = security_ib_pkey_access(qp_sec->security, subnet_prefix, pkey);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(shared_qp_sec,
			    &qp_sec->shared_qp_list,
			    shared_qp_list) अणु
		ret = security_ib_pkey_access(shared_qp_sec->security,
					      subnet_prefix,
					      pkey);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* The caller of this function must hold the QP security
 * mutex of the QP of the security काष्ठाure in *pps.
 *
 * It takes separate ports_pkeys and security काष्ठाure
 * because in some हालs the pps will be क्रम a new settings
 * or the pps will be क्रम the real QP and security काष्ठाure
 * will be क्रम a shared QP.
 */
अटल पूर्णांक check_qp_port_pkey_settings(काष्ठा ib_ports_pkeys *pps,
				       काष्ठा ib_qp_security *sec)
अणु
	u64 subnet_prefix;
	u16 pkey;
	पूर्णांक ret = 0;

	अगर (!pps)
		वापस 0;

	अगर (pps->मुख्य.state != IB_PORT_PKEY_NOT_VALID) अणु
		ret = get_pkey_and_subnet_prefix(&pps->मुख्य,
						 &pkey,
						 &subnet_prefix);
		अगर (ret)
			वापस ret;

		ret = enक्रमce_qp_pkey_security(pkey,
					       subnet_prefix,
					       sec);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (pps->alt.state != IB_PORT_PKEY_NOT_VALID) अणु
		ret = get_pkey_and_subnet_prefix(&pps->alt,
						 &pkey,
						 &subnet_prefix);
		अगर (ret)
			वापस ret;

		ret = enक्रमce_qp_pkey_security(pkey,
					       subnet_prefix,
					       sec);
	पूर्ण

	वापस ret;
पूर्ण

/* The caller of this function must hold the QP security
 * mutex.
 */
अटल व्योम qp_to_error(काष्ठा ib_qp_security *sec)
अणु
	काष्ठा ib_qp_security *shared_qp_sec;
	काष्ठा ib_qp_attr attr = अणु
		.qp_state = IB_QPS_ERR
	पूर्ण;
	काष्ठा ib_event event = अणु
		.event = IB_EVENT_QP_FATAL
	पूर्ण;

	/* If the QP is in the process of being destroyed
	 * the qp poपूर्णांकer in the security काष्ठाure is
	 * undefined.  It cannot be modअगरied now.
	 */
	अगर (sec->destroying)
		वापस;

	ib_modअगरy_qp(sec->qp,
		     &attr,
		     IB_QP_STATE);

	अगर (sec->qp->event_handler && sec->qp->qp_context) अणु
		event.element.qp = sec->qp;
		sec->qp->event_handler(&event,
				       sec->qp->qp_context);
	पूर्ण

	list_क्रम_each_entry(shared_qp_sec,
			    &sec->shared_qp_list,
			    shared_qp_list) अणु
		काष्ठा ib_qp *qp = shared_qp_sec->qp;

		अगर (qp->event_handler && qp->qp_context) अणु
			event.element.qp = qp;
			event.device = qp->device;
			qp->event_handler(&event,
					  qp->qp_context);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम check_pkey_qps(काष्ठा pkey_index_qp_list *pkey,
				  काष्ठा ib_device *device,
				  u32 port_num,
				  u64 subnet_prefix)
अणु
	काष्ठा ib_port_pkey *pp, *पंचांगp_pp;
	bool comp;
	LIST_HEAD(to_error_list);
	u16 pkey_val;

	अगर (!ib_get_cached_pkey(device,
				port_num,
				pkey->pkey_index,
				&pkey_val)) अणु
		spin_lock(&pkey->qp_list_lock);
		list_क्रम_each_entry(pp, &pkey->qp_list, qp_list) अणु
			अगर (atomic_पढ़ो(&pp->sec->error_list_count))
				जारी;

			अगर (enक्रमce_qp_pkey_security(pkey_val,
						     subnet_prefix,
						     pp->sec)) अणु
				atomic_inc(&pp->sec->error_list_count);
				list_add(&pp->to_error_list,
					 &to_error_list);
			पूर्ण
		पूर्ण
		spin_unlock(&pkey->qp_list_lock);
	पूर्ण

	list_क्रम_each_entry_safe(pp,
				 पंचांगp_pp,
				 &to_error_list,
				 to_error_list) अणु
		mutex_lock(&pp->sec->mutex);
		qp_to_error(pp->sec);
		list_del(&pp->to_error_list);
		atomic_dec(&pp->sec->error_list_count);
		comp = pp->sec->destroying;
		mutex_unlock(&pp->sec->mutex);

		अगर (comp)
			complete(&pp->sec->error_complete);
	पूर्ण
पूर्ण

/* The caller of this function must hold the QP security
 * mutex.
 */
अटल पूर्णांक port_pkey_list_insert(काष्ठा ib_port_pkey *pp)
अणु
	काष्ठा pkey_index_qp_list *पंचांगp_pkey;
	काष्ठा pkey_index_qp_list *pkey;
	काष्ठा ib_device *dev;
	u32 port_num = pp->port_num;
	पूर्णांक ret = 0;

	अगर (pp->state != IB_PORT_PKEY_VALID)
		वापस 0;

	dev = pp->sec->dev;

	pkey = get_pkey_idx_qp_list(pp);

	अगर (!pkey) अणु
		bool found = false;

		pkey = kzalloc(माप(*pkey), GFP_KERNEL);
		अगर (!pkey)
			वापस -ENOMEM;

		spin_lock(&dev->port_data[port_num].pkey_list_lock);
		/* Check क्रम the PKey again.  A racing process may
		 * have created it.
		 */
		list_क्रम_each_entry(पंचांगp_pkey,
				    &dev->port_data[port_num].pkey_list,
				    pkey_index_list) अणु
			अगर (पंचांगp_pkey->pkey_index == pp->pkey_index) अणु
				kमुक्त(pkey);
				pkey = पंचांगp_pkey;
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			pkey->pkey_index = pp->pkey_index;
			spin_lock_init(&pkey->qp_list_lock);
			INIT_LIST_HEAD(&pkey->qp_list);
			list_add(&pkey->pkey_index_list,
				 &dev->port_data[port_num].pkey_list);
		पूर्ण
		spin_unlock(&dev->port_data[port_num].pkey_list_lock);
	पूर्ण

	spin_lock(&pkey->qp_list_lock);
	list_add(&pp->qp_list, &pkey->qp_list);
	spin_unlock(&pkey->qp_list_lock);

	pp->state = IB_PORT_PKEY_LISTED;

	वापस ret;
पूर्ण

/* The caller of this function must hold the QP security
 * mutex.
 */
अटल व्योम port_pkey_list_हटाओ(काष्ठा ib_port_pkey *pp)
अणु
	काष्ठा pkey_index_qp_list *pkey;

	अगर (pp->state != IB_PORT_PKEY_LISTED)
		वापस;

	pkey = get_pkey_idx_qp_list(pp);

	spin_lock(&pkey->qp_list_lock);
	list_del(&pp->qp_list);
	spin_unlock(&pkey->qp_list_lock);

	/* The setting may still be valid, i.e. after
	 * a destroy has failed क्रम example.
	 */
	pp->state = IB_PORT_PKEY_VALID;
पूर्ण

अटल व्योम destroy_qp_security(काष्ठा ib_qp_security *sec)
अणु
	security_ib_मुक्त_security(sec->security);
	kमुक्त(sec->ports_pkeys);
	kमुक्त(sec);
पूर्ण

/* The caller of this function must hold the QP security
 * mutex.
 */
अटल काष्ठा ib_ports_pkeys *get_new_pps(स्थिर काष्ठा ib_qp *qp,
					  स्थिर काष्ठा ib_qp_attr *qp_attr,
					  पूर्णांक qp_attr_mask)
अणु
	काष्ठा ib_ports_pkeys *new_pps;
	काष्ठा ib_ports_pkeys *qp_pps = qp->qp_sec->ports_pkeys;

	new_pps = kzalloc(माप(*new_pps), GFP_KERNEL);
	अगर (!new_pps)
		वापस शून्य;

	अगर (qp_attr_mask & IB_QP_PORT)
		new_pps->मुख्य.port_num = qp_attr->port_num;
	अन्यथा अगर (qp_pps)
		new_pps->मुख्य.port_num = qp_pps->मुख्य.port_num;

	अगर (qp_attr_mask & IB_QP_PKEY_INDEX)
		new_pps->मुख्य.pkey_index = qp_attr->pkey_index;
	अन्यथा अगर (qp_pps)
		new_pps->मुख्य.pkey_index = qp_pps->मुख्य.pkey_index;

	अगर (((qp_attr_mask & IB_QP_PKEY_INDEX) &&
	     (qp_attr_mask & IB_QP_PORT)) ||
	    (qp_pps && qp_pps->मुख्य.state != IB_PORT_PKEY_NOT_VALID))
		new_pps->मुख्य.state = IB_PORT_PKEY_VALID;

	अगर (qp_attr_mask & IB_QP_ALT_PATH) अणु
		new_pps->alt.port_num = qp_attr->alt_port_num;
		new_pps->alt.pkey_index = qp_attr->alt_pkey_index;
		new_pps->alt.state = IB_PORT_PKEY_VALID;
	पूर्ण अन्यथा अगर (qp_pps) अणु
		new_pps->alt.port_num = qp_pps->alt.port_num;
		new_pps->alt.pkey_index = qp_pps->alt.pkey_index;
		अगर (qp_pps->alt.state != IB_PORT_PKEY_NOT_VALID)
			new_pps->alt.state = IB_PORT_PKEY_VALID;
	पूर्ण

	new_pps->मुख्य.sec = qp->qp_sec;
	new_pps->alt.sec = qp->qp_sec;
	वापस new_pps;
पूर्ण

पूर्णांक ib_खोलो_shared_qp_security(काष्ठा ib_qp *qp, काष्ठा ib_device *dev)
अणु
	काष्ठा ib_qp *real_qp = qp->real_qp;
	पूर्णांक ret;

	ret = ib_create_qp_security(qp, dev);

	अगर (ret)
		वापस ret;

	अगर (!qp->qp_sec)
		वापस 0;

	mutex_lock(&real_qp->qp_sec->mutex);
	ret = check_qp_port_pkey_settings(real_qp->qp_sec->ports_pkeys,
					  qp->qp_sec);

	अगर (ret)
		जाओ ret;

	अगर (qp != real_qp)
		list_add(&qp->qp_sec->shared_qp_list,
			 &real_qp->qp_sec->shared_qp_list);
ret:
	mutex_unlock(&real_qp->qp_sec->mutex);
	अगर (ret)
		destroy_qp_security(qp->qp_sec);

	वापस ret;
पूर्ण

व्योम ib_बंद_shared_qp_security(काष्ठा ib_qp_security *sec)
अणु
	काष्ठा ib_qp *real_qp = sec->qp->real_qp;

	mutex_lock(&real_qp->qp_sec->mutex);
	list_del(&sec->shared_qp_list);
	mutex_unlock(&real_qp->qp_sec->mutex);

	destroy_qp_security(sec);
पूर्ण

पूर्णांक ib_create_qp_security(काष्ठा ib_qp *qp, काष्ठा ib_device *dev)
अणु
	अचिन्हित पूर्णांक i;
	bool is_ib = false;
	पूर्णांक ret;

	rdma_क्रम_each_port (dev, i) अणु
		is_ib = rdma_protocol_ib(dev, i);
		अगर (is_ib)
			अवरोध;
	पूर्ण

	/* If this isn't an IB device don't create the security context */
	अगर (!is_ib)
		वापस 0;

	qp->qp_sec = kzalloc(माप(*qp->qp_sec), GFP_KERNEL);
	अगर (!qp->qp_sec)
		वापस -ENOMEM;

	qp->qp_sec->qp = qp;
	qp->qp_sec->dev = dev;
	mutex_init(&qp->qp_sec->mutex);
	INIT_LIST_HEAD(&qp->qp_sec->shared_qp_list);
	atomic_set(&qp->qp_sec->error_list_count, 0);
	init_completion(&qp->qp_sec->error_complete);
	ret = security_ib_alloc_security(&qp->qp_sec->security);
	अगर (ret) अणु
		kमुक्त(qp->qp_sec);
		qp->qp_sec = शून्य;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_create_qp_security);

व्योम ib_destroy_qp_security_begin(काष्ठा ib_qp_security *sec)
अणु
	/* Return अगर not IB */
	अगर (!sec)
		वापस;

	mutex_lock(&sec->mutex);

	/* Remove the QP from the lists so it won't get added to
	 * a to_error_list during the destroy process.
	 */
	अगर (sec->ports_pkeys) अणु
		port_pkey_list_हटाओ(&sec->ports_pkeys->मुख्य);
		port_pkey_list_हटाओ(&sec->ports_pkeys->alt);
	पूर्ण

	/* If the QP is alपढ़ोy in one or more of those lists
	 * the destroying flag will ensure the to error flow
	 * करोesn't operate on an undefined QP.
	 */
	sec->destroying = true;

	/* Record the error list count to know how many completions
	 * to रुको क्रम.
	 */
	sec->error_comps_pending = atomic_पढ़ो(&sec->error_list_count);

	mutex_unlock(&sec->mutex);
पूर्ण

व्योम ib_destroy_qp_security_पात(काष्ठा ib_qp_security *sec)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	/* Return अगर not IB */
	अगर (!sec)
		वापस;

	/* If a concurrent cache update is in progress this
	 * QP security could be marked क्रम an error state
	 * transition.  Wait क्रम this to complete.
	 */
	क्रम (i = 0; i < sec->error_comps_pending; i++)
		रुको_क्रम_completion(&sec->error_complete);

	mutex_lock(&sec->mutex);
	sec->destroying = false;

	/* Restore the position in the lists and verअगरy
	 * access is still allowed in हाल a cache update
	 * occurred जबतक attempting to destroy.
	 *
	 * Because these setting were listed alपढ़ोy
	 * and हटाओd during ib_destroy_qp_security_begin
	 * we know the pkey_index_qp_list क्रम the PKey
	 * alपढ़ोy exists so port_pkey_list_insert won't fail.
	 */
	अगर (sec->ports_pkeys) अणु
		port_pkey_list_insert(&sec->ports_pkeys->मुख्य);
		port_pkey_list_insert(&sec->ports_pkeys->alt);
	पूर्ण

	ret = check_qp_port_pkey_settings(sec->ports_pkeys, sec);
	अगर (ret)
		qp_to_error(sec);

	mutex_unlock(&sec->mutex);
पूर्ण

व्योम ib_destroy_qp_security_end(काष्ठा ib_qp_security *sec)
अणु
	पूर्णांक i;

	/* Return अगर not IB */
	अगर (!sec)
		वापस;

	/* If a concurrent cache update is occurring we must
	 * रुको until this QP security काष्ठाure is processed
	 * in the QP to error flow beक्रमe destroying it because
	 * the to_error_list is in use.
	 */
	क्रम (i = 0; i < sec->error_comps_pending; i++)
		रुको_क्रम_completion(&sec->error_complete);

	destroy_qp_security(sec);
पूर्ण

व्योम ib_security_cache_change(काष्ठा ib_device *device,
			      u32 port_num,
			      u64 subnet_prefix)
अणु
	काष्ठा pkey_index_qp_list *pkey;

	list_क्रम_each_entry (pkey, &device->port_data[port_num].pkey_list,
			     pkey_index_list) अणु
		check_pkey_qps(pkey,
			       device,
			       port_num,
			       subnet_prefix);
	पूर्ण
पूर्ण

व्योम ib_security_release_port_pkey_list(काष्ठा ib_device *device)
अणु
	काष्ठा pkey_index_qp_list *pkey, *पंचांगp_pkey;
	अचिन्हित पूर्णांक i;

	rdma_क्रम_each_port (device, i) अणु
		list_क्रम_each_entry_safe(pkey,
					 पंचांगp_pkey,
					 &device->port_data[i].pkey_list,
					 pkey_index_list) अणु
			list_del(&pkey->pkey_index_list);
			kमुक्त(pkey);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ib_security_modअगरy_qp(काष्ठा ib_qp *qp,
			  काष्ठा ib_qp_attr *qp_attr,
			  पूर्णांक qp_attr_mask,
			  काष्ठा ib_udata *udata)
अणु
	पूर्णांक ret = 0;
	काष्ठा ib_ports_pkeys *पंचांगp_pps;
	काष्ठा ib_ports_pkeys *new_pps = शून्य;
	काष्ठा ib_qp *real_qp = qp->real_qp;
	bool special_qp = (real_qp->qp_type == IB_QPT_SMI ||
			   real_qp->qp_type == IB_QPT_GSI ||
			   real_qp->qp_type >= IB_QPT_RESERVED1);
	bool pps_change = ((qp_attr_mask & (IB_QP_PKEY_INDEX | IB_QP_PORT)) ||
			   (qp_attr_mask & IB_QP_ALT_PATH));

	WARN_ONCE((qp_attr_mask & IB_QP_PORT &&
		   rdma_protocol_ib(real_qp->device, qp_attr->port_num) &&
		   !real_qp->qp_sec),
		   "%s: QP security is not initialized for IB QP: %d\n",
		   __func__, real_qp->qp_num);

	/* The port/pkey settings are मुख्यtained only क्रम the real QP. Open
	 * handles on the real QP will be in the shared_qp_list. When
	 * enक्रमcing security on the real QP all the shared QPs will be
	 * checked as well.
	 */

	अगर (pps_change && !special_qp && real_qp->qp_sec) अणु
		mutex_lock(&real_qp->qp_sec->mutex);
		new_pps = get_new_pps(real_qp,
				      qp_attr,
				      qp_attr_mask);
		अगर (!new_pps) अणु
			mutex_unlock(&real_qp->qp_sec->mutex);
			वापस -ENOMEM;
		पूर्ण
		/* Add this QP to the lists क्रम the new port
		 * and pkey settings beक्रमe checking क्रम permission
		 * in हाल there is a concurrent cache update
		 * occurring.  Walking the list क्रम a cache change
		 * करोesn't acquire the security mutex unless it's
		 * sending the QP to error.
		 */
		ret = port_pkey_list_insert(&new_pps->मुख्य);

		अगर (!ret)
			ret = port_pkey_list_insert(&new_pps->alt);

		अगर (!ret)
			ret = check_qp_port_pkey_settings(new_pps,
							  real_qp->qp_sec);
	पूर्ण

	अगर (!ret)
		ret = real_qp->device->ops.modअगरy_qp(real_qp,
						     qp_attr,
						     qp_attr_mask,
						     udata);

	अगर (new_pps) अणु
		/* Clean up the lists and मुक्त the appropriate
		 * ports_pkeys काष्ठाure.
		 */
		अगर (ret) अणु
			पंचांगp_pps = new_pps;
		पूर्ण अन्यथा अणु
			पंचांगp_pps = real_qp->qp_sec->ports_pkeys;
			real_qp->qp_sec->ports_pkeys = new_pps;
		पूर्ण

		अगर (पंचांगp_pps) अणु
			port_pkey_list_हटाओ(&पंचांगp_pps->मुख्य);
			port_pkey_list_हटाओ(&पंचांगp_pps->alt);
		पूर्ण
		kमुक्त(पंचांगp_pps);
		mutex_unlock(&real_qp->qp_sec->mutex);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ib_security_pkey_access(काष्ठा ib_device *dev,
				   u32 port_num,
				   u16 pkey_index,
				   व्योम *sec)
अणु
	u64 subnet_prefix;
	u16 pkey;
	पूर्णांक ret;

	अगर (!rdma_protocol_ib(dev, port_num))
		वापस 0;

	ret = ib_get_cached_pkey(dev, port_num, pkey_index, &pkey);
	अगर (ret)
		वापस ret;

	ret = ib_get_cached_subnet_prefix(dev, port_num, &subnet_prefix);

	अगर (ret)
		वापस ret;

	वापस security_ib_pkey_access(sec, subnet_prefix, pkey);
पूर्ण

व्योम ib_mad_agent_security_change(व्योम)
अणु
	काष्ठा ib_mad_agent *ag;

	spin_lock(&mad_agent_list_lock);
	list_क्रम_each_entry(ag,
			    &mad_agent_list,
			    mad_agent_sec_list)
		WRITE_ONCE(ag->smp_allowed,
			   !security_ib_endport_manage_subnet(ag->security,
				dev_name(&ag->device->dev), ag->port_num));
	spin_unlock(&mad_agent_list_lock);
पूर्ण

पूर्णांक ib_mad_agent_security_setup(काष्ठा ib_mad_agent *agent,
				क्रमागत ib_qp_type qp_type)
अणु
	पूर्णांक ret;

	अगर (!rdma_protocol_ib(agent->device, agent->port_num))
		वापस 0;

	INIT_LIST_HEAD(&agent->mad_agent_sec_list);

	ret = security_ib_alloc_security(&agent->security);
	अगर (ret)
		वापस ret;

	अगर (qp_type != IB_QPT_SMI)
		वापस 0;

	spin_lock(&mad_agent_list_lock);
	ret = security_ib_endport_manage_subnet(agent->security,
						dev_name(&agent->device->dev),
						agent->port_num);
	अगर (ret)
		जाओ मुक्त_security;

	WRITE_ONCE(agent->smp_allowed, true);
	list_add(&agent->mad_agent_sec_list, &mad_agent_list);
	spin_unlock(&mad_agent_list_lock);
	वापस 0;

मुक्त_security:
	spin_unlock(&mad_agent_list_lock);
	security_ib_मुक्त_security(agent->security);
	वापस ret;
पूर्ण

व्योम ib_mad_agent_security_cleanup(काष्ठा ib_mad_agent *agent)
अणु
	अगर (!rdma_protocol_ib(agent->device, agent->port_num))
		वापस;

	अगर (agent->qp->qp_type == IB_QPT_SMI) अणु
		spin_lock(&mad_agent_list_lock);
		list_del(&agent->mad_agent_sec_list);
		spin_unlock(&mad_agent_list_lock);
	पूर्ण

	security_ib_मुक्त_security(agent->security);
पूर्ण

पूर्णांक ib_mad_enक्रमce_security(काष्ठा ib_mad_agent_निजी *map, u16 pkey_index)
अणु
	अगर (!rdma_protocol_ib(map->agent.device, map->agent.port_num))
		वापस 0;

	अगर (map->agent.qp->qp_type == IB_QPT_SMI) अणु
		अगर (!READ_ONCE(map->agent.smp_allowed))
			वापस -EACCES;
		वापस 0;
	पूर्ण

	वापस ib_security_pkey_access(map->agent.device,
				       map->agent.port_num,
				       pkey_index,
				       map->agent.security);
पूर्ण
