<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>

#समावेश "cxgb4.h"
#समावेश "sched.h"

अटल पूर्णांक t4_sched_class_fw_cmd(काष्ठा port_info *pi,
				 काष्ठा ch_sched_params *p,
				 क्रमागत sched_fw_ops op)
अणु
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sched_table *s = pi->sched_tbl;
	काष्ठा sched_class *e;
	पूर्णांक err = 0;

	e = &s->tab[p->u.params.class];
	चयन (op) अणु
	हाल SCHED_FW_OP_ADD:
	हाल SCHED_FW_OP_DEL:
		err = t4_sched_params(adap, p->type,
				      p->u.params.level, p->u.params.mode,
				      p->u.params.rateunit,
				      p->u.params.ratemode,
				      p->u.params.channel, e->idx,
				      p->u.params.minrate, p->u.params.maxrate,
				      p->u.params.weight, p->u.params.pktsize,
				      p->u.params.burstsize);
		अवरोध;
	शेष:
		err = -ENOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक t4_sched_bind_unbind_op(काष्ठा port_info *pi, व्योम *arg,
				   क्रमागत sched_bind_type type, bool bind)
अणु
	काष्ठा adapter *adap = pi->adapter;
	u32 fw_mnem, fw_class, fw_param;
	अचिन्हित पूर्णांक pf = adap->pf;
	अचिन्हित पूर्णांक vf = 0;
	पूर्णांक err = 0;

	चयन (type) अणु
	हाल SCHED_QUEUE: अणु
		काष्ठा sched_queue_entry *qe;

		qe = (काष्ठा sched_queue_entry *)arg;

		/* Create a ढाँचा क्रम the FW_PARAMS_CMD mnemonic and
		 * value (TX Scheduling Class in this हाल).
		 */
		fw_mnem = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
			   FW_PARAMS_PARAM_X_V(
				   FW_PARAMS_PARAM_DMAQ_EQ_SCHEDCLASS_ETH));
		fw_class = bind ? qe->param.class : FW_SCHED_CLS_NONE;
		fw_param = (fw_mnem | FW_PARAMS_PARAM_YZ_V(qe->cntxt_id));

		pf = adap->pf;
		vf = 0;

		err = t4_set_params(adap, adap->mbox, pf, vf, 1,
				    &fw_param, &fw_class);
		अवरोध;
	पूर्ण
	हाल SCHED_FLOWC: अणु
		काष्ठा sched_flowc_entry *fe;

		fe = (काष्ठा sched_flowc_entry *)arg;

		fw_class = bind ? fe->param.class : FW_SCHED_CLS_NONE;
		err = cxgb4_ethofld_send_flowc(adap->port[pi->port_id],
					       fe->param.tid, fw_class);
		अवरोध;
	पूर्ण
	शेष:
		err = -ENOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम *t4_sched_entry_lookup(काष्ठा port_info *pi,
				   क्रमागत sched_bind_type type,
				   स्थिर u32 val)
अणु
	काष्ठा sched_table *s = pi->sched_tbl;
	काष्ठा sched_class *e, *end;
	व्योम *found = शून्य;

	/* Look क्रम an entry with matching @val */
	end = &s->tab[s->sched_size];
	क्रम (e = &s->tab[0]; e != end; ++e) अणु
		अगर (e->state == SCHED_STATE_UNUSED ||
		    e->bind_type != type)
			जारी;

		चयन (type) अणु
		हाल SCHED_QUEUE: अणु
			काष्ठा sched_queue_entry *qe;

			list_क्रम_each_entry(qe, &e->entry_list, list) अणु
				अगर (qe->cntxt_id == val) अणु
					found = qe;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
		हाल SCHED_FLOWC: अणु
			काष्ठा sched_flowc_entry *fe;

			list_क्रम_each_entry(fe, &e->entry_list, list) अणु
				अगर (fe->param.tid == val) अणु
					found = fe;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
		शेष:
			वापस शून्य;
		पूर्ण

		अगर (found)
			अवरोध;
	पूर्ण

	वापस found;
पूर्ण

काष्ठा sched_class *cxgb4_sched_queue_lookup(काष्ठा net_device *dev,
					     काष्ठा ch_sched_queue *p)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा sched_queue_entry *qe = शून्य;
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge_eth_txq *txq;

	अगर (p->queue < 0 || p->queue >= pi->nqsets)
		वापस शून्य;

	txq = &adap->sge.ethtxq[pi->first_qset + p->queue];
	qe = t4_sched_entry_lookup(pi, SCHED_QUEUE, txq->q.cntxt_id);
	वापस qe ? &pi->sched_tbl->tab[qe->param.class] : शून्य;
पूर्ण

अटल पूर्णांक t4_sched_queue_unbind(काष्ठा port_info *pi, काष्ठा ch_sched_queue *p)
अणु
	काष्ठा sched_queue_entry *qe = शून्य;
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge_eth_txq *txq;
	काष्ठा sched_class *e;
	पूर्णांक err = 0;

	अगर (p->queue < 0 || p->queue >= pi->nqsets)
		वापस -दुस्फल;

	txq = &adap->sge.ethtxq[pi->first_qset + p->queue];

	/* Find the existing entry that the queue is bound to */
	qe = t4_sched_entry_lookup(pi, SCHED_QUEUE, txq->q.cntxt_id);
	अगर (qe) अणु
		err = t4_sched_bind_unbind_op(pi, (व्योम *)qe, SCHED_QUEUE,
					      false);
		अगर (err)
			वापस err;

		e = &pi->sched_tbl->tab[qe->param.class];
		list_del(&qe->list);
		kvमुक्त(qe);
		अगर (atomic_dec_and_test(&e->refcnt))
			cxgb4_sched_class_मुक्त(adap->port[pi->port_id], e->idx);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक t4_sched_queue_bind(काष्ठा port_info *pi, काष्ठा ch_sched_queue *p)
अणु
	काष्ठा sched_table *s = pi->sched_tbl;
	काष्ठा sched_queue_entry *qe = शून्य;
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge_eth_txq *txq;
	काष्ठा sched_class *e;
	अचिन्हित पूर्णांक qid;
	पूर्णांक err = 0;

	अगर (p->queue < 0 || p->queue >= pi->nqsets)
		वापस -दुस्फल;

	qe = kvzalloc(माप(काष्ठा sched_queue_entry), GFP_KERNEL);
	अगर (!qe)
		वापस -ENOMEM;

	txq = &adap->sge.ethtxq[pi->first_qset + p->queue];
	qid = txq->q.cntxt_id;

	/* Unbind queue from any existing class */
	err = t4_sched_queue_unbind(pi, p);
	अगर (err)
		जाओ out_err;

	/* Bind queue to specअगरied class */
	qe->cntxt_id = qid;
	स_नकल(&qe->param, p, माप(qe->param));

	e = &s->tab[qe->param.class];
	err = t4_sched_bind_unbind_op(pi, (व्योम *)qe, SCHED_QUEUE, true);
	अगर (err)
		जाओ out_err;

	list_add_tail(&qe->list, &e->entry_list);
	e->bind_type = SCHED_QUEUE;
	atomic_inc(&e->refcnt);
	वापस err;

out_err:
	kvमुक्त(qe);
	वापस err;
पूर्ण

अटल पूर्णांक t4_sched_flowc_unbind(काष्ठा port_info *pi, काष्ठा ch_sched_flowc *p)
अणु
	काष्ठा sched_flowc_entry *fe = शून्य;
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sched_class *e;
	पूर्णांक err = 0;

	अगर (p->tid < 0 || p->tid >= adap->tids.neotids)
		वापस -दुस्फल;

	/* Find the existing entry that the flowc is bound to */
	fe = t4_sched_entry_lookup(pi, SCHED_FLOWC, p->tid);
	अगर (fe) अणु
		err = t4_sched_bind_unbind_op(pi, (व्योम *)fe, SCHED_FLOWC,
					      false);
		अगर (err)
			वापस err;

		e = &pi->sched_tbl->tab[fe->param.class];
		list_del(&fe->list);
		kvमुक्त(fe);
		अगर (atomic_dec_and_test(&e->refcnt))
			cxgb4_sched_class_मुक्त(adap->port[pi->port_id], e->idx);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक t4_sched_flowc_bind(काष्ठा port_info *pi, काष्ठा ch_sched_flowc *p)
अणु
	काष्ठा sched_table *s = pi->sched_tbl;
	काष्ठा sched_flowc_entry *fe = शून्य;
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sched_class *e;
	पूर्णांक err = 0;

	अगर (p->tid < 0 || p->tid >= adap->tids.neotids)
		वापस -दुस्फल;

	fe = kvzalloc(माप(*fe), GFP_KERNEL);
	अगर (!fe)
		वापस -ENOMEM;

	/* Unbind flowc from any existing class */
	err = t4_sched_flowc_unbind(pi, p);
	अगर (err)
		जाओ out_err;

	/* Bind flowc to specअगरied class */
	स_नकल(&fe->param, p, माप(fe->param));

	e = &s->tab[fe->param.class];
	err = t4_sched_bind_unbind_op(pi, (व्योम *)fe, SCHED_FLOWC, true);
	अगर (err)
		जाओ out_err;

	list_add_tail(&fe->list, &e->entry_list);
	e->bind_type = SCHED_FLOWC;
	atomic_inc(&e->refcnt);
	वापस err;

out_err:
	kvमुक्त(fe);
	वापस err;
पूर्ण

अटल व्योम t4_sched_class_unbind_all(काष्ठा port_info *pi,
				      काष्ठा sched_class *e,
				      क्रमागत sched_bind_type type)
अणु
	अगर (!e)
		वापस;

	चयन (type) अणु
	हाल SCHED_QUEUE: अणु
		काष्ठा sched_queue_entry *qe;

		list_क्रम_each_entry(qe, &e->entry_list, list)
			t4_sched_queue_unbind(pi, &qe->param);
		अवरोध;
	पूर्ण
	हाल SCHED_FLOWC: अणु
		काष्ठा sched_flowc_entry *fe;

		list_क्रम_each_entry(fe, &e->entry_list, list)
			t4_sched_flowc_unbind(pi, &fe->param);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक t4_sched_class_bind_unbind_op(काष्ठा port_info *pi, व्योम *arg,
					 क्रमागत sched_bind_type type, bool bind)
अणु
	पूर्णांक err = 0;

	अगर (!arg)
		वापस -EINVAL;

	चयन (type) अणु
	हाल SCHED_QUEUE: अणु
		काष्ठा ch_sched_queue *qe = (काष्ठा ch_sched_queue *)arg;

		अगर (bind)
			err = t4_sched_queue_bind(pi, qe);
		अन्यथा
			err = t4_sched_queue_unbind(pi, qe);
		अवरोध;
	पूर्ण
	हाल SCHED_FLOWC: अणु
		काष्ठा ch_sched_flowc *fe = (काष्ठा ch_sched_flowc *)arg;

		अगर (bind)
			err = t4_sched_flowc_bind(pi, fe);
		अन्यथा
			err = t4_sched_flowc_unbind(pi, fe);
		अवरोध;
	पूर्ण
	शेष:
		err = -ENOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * cxgb4_sched_class_bind - Bind an entity to a scheduling class
 * @dev: net_device poपूर्णांकer
 * @arg: Entity opaque data
 * @type: Entity type (Queue)
 *
 * Binds an entity (queue) to a scheduling class.  If the entity
 * is bound to another class, it will be unbound from the other class
 * and bound to the class specअगरied in @arg.
 */
पूर्णांक cxgb4_sched_class_bind(काष्ठा net_device *dev, व्योम *arg,
			   क्रमागत sched_bind_type type)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	u8 class_id;

	अगर (!can_sched(dev))
		वापस -ENOTSUPP;

	अगर (!arg)
		वापस -EINVAL;

	चयन (type) अणु
	हाल SCHED_QUEUE: अणु
		काष्ठा ch_sched_queue *qe = (काष्ठा ch_sched_queue *)arg;

		class_id = qe->class;
		अवरोध;
	पूर्ण
	हाल SCHED_FLOWC: अणु
		काष्ठा ch_sched_flowc *fe = (काष्ठा ch_sched_flowc *)arg;

		class_id = fe->class;
		अवरोध;
	पूर्ण
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!valid_class_id(dev, class_id))
		वापस -EINVAL;

	अगर (class_id == SCHED_CLS_NONE)
		वापस -ENOTSUPP;

	वापस t4_sched_class_bind_unbind_op(pi, arg, type, true);

पूर्ण

/**
 * cxgb4_sched_class_unbind - Unbind an entity from a scheduling class
 * @dev: net_device poपूर्णांकer
 * @arg: Entity opaque data
 * @type: Entity type (Queue)
 *
 * Unbinds an entity (queue) from a scheduling class.
 */
पूर्णांक cxgb4_sched_class_unbind(काष्ठा net_device *dev, व्योम *arg,
			     क्रमागत sched_bind_type type)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	u8 class_id;

	अगर (!can_sched(dev))
		वापस -ENOTSUPP;

	अगर (!arg)
		वापस -EINVAL;

	चयन (type) अणु
	हाल SCHED_QUEUE: अणु
		काष्ठा ch_sched_queue *qe = (काष्ठा ch_sched_queue *)arg;

		class_id = qe->class;
		अवरोध;
	पूर्ण
	हाल SCHED_FLOWC: अणु
		काष्ठा ch_sched_flowc *fe = (काष्ठा ch_sched_flowc *)arg;

		class_id = fe->class;
		अवरोध;
	पूर्ण
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!valid_class_id(dev, class_id))
		वापस -EINVAL;

	वापस t4_sched_class_bind_unbind_op(pi, arg, type, false);
पूर्ण

/* If @p is शून्य, fetch any available unused class */
अटल काष्ठा sched_class *t4_sched_class_lookup(काष्ठा port_info *pi,
						स्थिर काष्ठा ch_sched_params *p)
अणु
	काष्ठा sched_table *s = pi->sched_tbl;
	काष्ठा sched_class *found = शून्य;
	काष्ठा sched_class *e, *end;

	अगर (!p) अणु
		/* Get any available unused class */
		end = &s->tab[s->sched_size];
		क्रम (e = &s->tab[0]; e != end; ++e) अणु
			अगर (e->state == SCHED_STATE_UNUSED) अणु
				found = e;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Look क्रम a class with matching scheduling parameters */
		काष्ठा ch_sched_params info;
		काष्ठा ch_sched_params tp;

		स_नकल(&tp, p, माप(tp));
		/* Don't try to match class parameter */
		tp.u.params.class = SCHED_CLS_NONE;

		end = &s->tab[s->sched_size];
		क्रम (e = &s->tab[0]; e != end; ++e) अणु
			अगर (e->state == SCHED_STATE_UNUSED)
				जारी;

			स_नकल(&info, &e->info, माप(info));
			/* Don't try to match class parameter */
			info.u.params.class = SCHED_CLS_NONE;

			अगर ((info.type == tp.type) &&
			    (!स_भेद(&info.u.params, &tp.u.params,
				     माप(info.u.params)))) अणु
				found = e;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल काष्ठा sched_class *t4_sched_class_alloc(काष्ठा port_info *pi,
						काष्ठा ch_sched_params *p)
अणु
	काष्ठा sched_class *e = शून्य;
	u8 class_id;
	पूर्णांक err;

	अगर (!p)
		वापस शून्य;

	class_id = p->u.params.class;

	/* Only accept search क्रम existing class with matching params
	 * or allocation of new class with specअगरied params
	 */
	अगर (class_id != SCHED_CLS_NONE)
		वापस शून्य;

	/* See अगर there's an exisiting class with same requested sched
	 * params. Classes can only be shared among FLOWC types. For
	 * other types, always request a new class.
	 */
	अगर (p->u.params.mode == SCHED_CLASS_MODE_FLOW)
		e = t4_sched_class_lookup(pi, p);

	अगर (!e) अणु
		काष्ठा ch_sched_params np;

		/* Fetch any available unused class */
		e = t4_sched_class_lookup(pi, शून्य);
		अगर (!e)
			वापस शून्य;

		स_नकल(&np, p, माप(np));
		np.u.params.class = e->idx;
		/* New class */
		err = t4_sched_class_fw_cmd(pi, &np, SCHED_FW_OP_ADD);
		अगर (err)
			वापस शून्य;
		स_नकल(&e->info, &np, माप(e->info));
		atomic_set(&e->refcnt, 0);
		e->state = SCHED_STATE_ACTIVE;
	पूर्ण

	वापस e;
पूर्ण

/**
 * cxgb4_sched_class_alloc - allocate a scheduling class
 * @dev: net_device poपूर्णांकer
 * @p: new scheduling class to create.
 *
 * Returns poपूर्णांकer to the scheduling class created.  If @p is शून्य, then
 * it allocates and वापसs any available unused scheduling class. If a
 * scheduling class with matching @p is found, then the matching class is
 * वापसed.
 */
काष्ठा sched_class *cxgb4_sched_class_alloc(काष्ठा net_device *dev,
					    काष्ठा ch_sched_params *p)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	u8 class_id;

	अगर (!can_sched(dev))
		वापस शून्य;

	class_id = p->u.params.class;
	अगर (!valid_class_id(dev, class_id))
		वापस शून्य;

	वापस t4_sched_class_alloc(pi, p);
पूर्ण

/**
 * cxgb4_sched_class_मुक्त - मुक्त a scheduling class
 * @dev: net_device poपूर्णांकer
 * @classid: scheduling class id to मुक्त
 *
 * Frees a scheduling class अगर there are no users.
 */
व्योम cxgb4_sched_class_मुक्त(काष्ठा net_device *dev, u8 classid)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा sched_table *s = pi->sched_tbl;
	काष्ठा ch_sched_params p;
	काष्ठा sched_class *e;
	u32 speed;
	पूर्णांक ret;

	e = &s->tab[classid];
	अगर (!atomic_पढ़ो(&e->refcnt) && e->state != SCHED_STATE_UNUSED) अणु
		/* Port based rate limiting needs explicit reset back
		 * to max rate. But, we'll करो explicit reset क्रम all
		 * types, instead of just port based type, to be on
		 * the safer side.
		 */
		स_नकल(&p, &e->info, माप(p));
		/* Always reset mode to 0. Otherwise, FLOWC mode will
		 * still be enabled even after resetting the traffic
		 * class.
		 */
		p.u.params.mode = 0;
		p.u.params.minrate = 0;
		p.u.params.pktsize = 0;

		ret = t4_get_link_params(pi, शून्य, &speed, शून्य);
		अगर (!ret)
			p.u.params.maxrate = speed * 1000; /* Mbps to Kbps */
		अन्यथा
			p.u.params.maxrate = SCHED_MAX_RATE_KBPS;

		t4_sched_class_fw_cmd(pi, &p, SCHED_FW_OP_DEL);

		e->state = SCHED_STATE_UNUSED;
		स_रखो(&e->info, 0, माप(e->info));
	पूर्ण
पूर्ण

अटल व्योम t4_sched_class_मुक्त(काष्ठा net_device *dev, काष्ठा sched_class *e)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	t4_sched_class_unbind_all(pi, e, e->bind_type);
	cxgb4_sched_class_मुक्त(dev, e->idx);
पूर्ण

काष्ठा sched_table *t4_init_sched(अचिन्हित पूर्णांक sched_size)
अणु
	काष्ठा sched_table *s;
	अचिन्हित पूर्णांक i;

	s = kvzalloc(काष्ठा_size(s, tab, sched_size), GFP_KERNEL);
	अगर (!s)
		वापस शून्य;

	s->sched_size = sched_size;

	क्रम (i = 0; i < s->sched_size; i++) अणु
		स_रखो(&s->tab[i], 0, माप(काष्ठा sched_class));
		s->tab[i].idx = i;
		s->tab[i].state = SCHED_STATE_UNUSED;
		INIT_LIST_HEAD(&s->tab[i].entry_list);
		atomic_set(&s->tab[i].refcnt, 0);
	पूर्ण
	वापस s;
पूर्ण

व्योम t4_cleanup_sched(काष्ठा adapter *adap)
अणु
	काष्ठा sched_table *s;
	अचिन्हित पूर्णांक j, i;

	क्रम_each_port(adap, j) अणु
		काष्ठा port_info *pi = netdev2pinfo(adap->port[j]);

		s = pi->sched_tbl;
		अगर (!s)
			जारी;

		क्रम (i = 0; i < s->sched_size; i++) अणु
			काष्ठा sched_class *e;

			e = &s->tab[i];
			अगर (e->state == SCHED_STATE_ACTIVE)
				t4_sched_class_मुक्त(adap->port[j], e);
		पूर्ण
		kvमुक्त(s);
	पूर्ण
पूर्ण
