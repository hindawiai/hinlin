<शैली गुरु>
/*
 * Copyright(c) 2015-2018 Intel Corporation.
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

#समावेश <linux/net.h>
#समावेश <rdma/opa_addr.h>
#घोषणा OPA_NUM_PKEY_BLOCKS_PER_SMP (OPA_SMP_DR_DATA_SIZE \
			/ (OPA_PARTITION_TABLE_BLK_SIZE * माप(u16)))

#समावेश "hfi.h"
#समावेश "mad.h"
#समावेश "trace.h"
#समावेश "qp.h"
#समावेश "vnic.h"

/* the reset value from the FM is supposed to be 0xffff, handle both */
#घोषणा OPA_LINK_WIDTH_RESET_OLD 0x0fff
#घोषणा OPA_LINK_WIDTH_RESET 0xffff

काष्ठा trap_node अणु
	काष्ठा list_head list;
	काष्ठा opa_mad_notice_attr data;
	__be64 tid;
	पूर्णांक len;
	u32 retry;
	u8 in_use;
	u8 repress;
पूर्ण;

अटल पूर्णांक smp_length_check(u32 data_size, u32 request_len)
अणु
	अगर (unlikely(request_len < data_size))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक reply(काष्ठा ib_mad_hdr *smp)
अणु
	/*
	 * The verbs framework will handle the directed/LID route
	 * packet changes.
	 */
	smp->method = IB_MGMT_METHOD_GET_RESP;
	अगर (smp->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		smp->status |= IB_SMP_सूचीECTION;
	वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
पूर्ण

अटल अंतरभूत व्योम clear_opa_smp_data(काष्ठा opa_smp *smp)
अणु
	व्योम *data = opa_get_smp_data(smp);
	माप_प्रकार size = opa_get_smp_data_size(smp);

	स_रखो(data, 0, size);
पूर्ण

अटल u16 hfi1_lookup_pkey_value(काष्ठा hfi1_ibport *ibp, पूर्णांक pkey_idx)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	अगर (pkey_idx < ARRAY_SIZE(ppd->pkeys))
		वापस ppd->pkeys[pkey_idx];

	वापस 0;
पूर्ण

व्योम hfi1_event_pkey_change(काष्ठा hfi1_devdata *dd, u32 port)
अणु
	काष्ठा ib_event event;

	event.event = IB_EVENT_PKEY_CHANGE;
	event.device = &dd->verbs_dev.rdi.ibdev;
	event.element.port_num = port;
	ib_dispatch_event(&event);
पूर्ण

/*
 * If the port is करोwn, clean up all pending traps.  We need to be careful
 * with the given trap, because it may be queued.
 */
अटल व्योम cleanup_traps(काष्ठा hfi1_ibport *ibp, काष्ठा trap_node *trap)
अणु
	काष्ठा trap_node *node, *q;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head trap_list;
	पूर्णांक i;

	क्रम (i = 0; i < RVT_MAX_TRAP_LISTS; i++) अणु
		spin_lock_irqsave(&ibp->rvp.lock, flags);
		list_replace_init(&ibp->rvp.trap_lists[i].list, &trap_list);
		ibp->rvp.trap_lists[i].list_len = 0;
		spin_unlock_irqrestore(&ibp->rvp.lock, flags);

		/*
		 * Remove all items from the list, मुक्तing all the non-given
		 * traps.
		 */
		list_क्रम_each_entry_safe(node, q, &trap_list, list) अणु
			list_del(&node->list);
			अगर (node != trap)
				kमुक्त(node);
		पूर्ण
	पूर्ण

	/*
	 * If this wasn't on one of the lists it would not be मुक्तd.  If it
	 * was on the list, it is now safe to मुक्त.
	 */
	kमुक्त(trap);
पूर्ण

अटल काष्ठा trap_node *check_and_add_trap(काष्ठा hfi1_ibport *ibp,
					    काष्ठा trap_node *trap)
अणु
	काष्ठा trap_node *node;
	काष्ठा trap_list *trap_list;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समयout;
	पूर्णांक found = 0;
	अचिन्हित पूर्णांक queue_id;
	अटल पूर्णांक trap_count;

	queue_id = trap->data.generic_type & 0x0F;
	अगर (queue_id >= RVT_MAX_TRAP_LISTS) अणु
		trap_count++;
		pr_err_ratelimited("hfi1: Invalid trap 0x%0x dropped. Total dropped: %d\n",
				   trap->data.generic_type, trap_count);
		kमुक्त(trap);
		वापस शून्य;
	पूर्ण

	/*
	 * Since the retry (handle समयout) करोes not हटाओ a trap request
	 * from the list, all we have to करो is compare the node.
	 */
	spin_lock_irqsave(&ibp->rvp.lock, flags);
	trap_list = &ibp->rvp.trap_lists[queue_id];

	list_क्रम_each_entry(node, &trap_list->list, list) अणु
		अगर (node == trap) अणु
			node->retry++;
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If it is not on the list, add it, limited to RVT-MAX_TRAP_LEN. */
	अगर (!found) अणु
		अगर (trap_list->list_len < RVT_MAX_TRAP_LEN) अणु
			trap_list->list_len++;
			list_add_tail(&trap->list, &trap_list->list);
		पूर्ण अन्यथा अणु
			pr_warn_ratelimited("hfi1: Maximum trap limit reached for 0x%0x traps\n",
					    trap->data.generic_type);
			kमुक्त(trap);
		पूर्ण
	पूर्ण

	/*
	 * Next check to see अगर there is a समयr pending.  If not, set it up
	 * and get the first trap from the list.
	 */
	node = शून्य;
	अगर (!समयr_pending(&ibp->rvp.trap_समयr)) अणु
		/*
		 * o14-2
		 * If the समय out is set we have to रुको until it expires
		 * beक्रमe the trap can be sent.
		 * This should be > RVT_TRAP_TIMEOUT
		 */
		समयout = (RVT_TRAP_TIMEOUT *
			   (1UL << ibp->rvp.subnet_समयout)) / 1000;
		mod_समयr(&ibp->rvp.trap_समयr,
			  jअगरfies + usecs_to_jअगरfies(समयout));
		node = list_first_entry(&trap_list->list, काष्ठा trap_node,
					list);
		node->in_use = 1;
	पूर्ण
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

	वापस node;
पूर्ण

अटल व्योम subn_handle_opa_trap_repress(काष्ठा hfi1_ibport *ibp,
					 काष्ठा opa_smp *smp)
अणु
	काष्ठा trap_list *trap_list;
	काष्ठा trap_node *trap;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (smp->attr_id != IB_SMP_ATTR_NOTICE)
		वापस;

	spin_lock_irqsave(&ibp->rvp.lock, flags);
	क्रम (i = 0; i < RVT_MAX_TRAP_LISTS; i++) अणु
		trap_list = &ibp->rvp.trap_lists[i];
		trap = list_first_entry_or_null(&trap_list->list,
						काष्ठा trap_node, list);
		अगर (trap && trap->tid == smp->tid) अणु
			अगर (trap->in_use) अणु
				trap->repress = 1;
			पूर्ण अन्यथा अणु
				trap_list->list_len--;
				list_del(&trap->list);
				kमुक्त(trap);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);
पूर्ण

अटल व्योम hfi1_update_sm_ah_attr(काष्ठा hfi1_ibport *ibp,
				   काष्ठा rdma_ah_attr *attr, u32 dlid)
अणु
	rdma_ah_set_dlid(attr, dlid);
	rdma_ah_set_port_num(attr, ppd_from_ibp(ibp)->port);
	अगर (dlid >= be16_to_cpu(IB_MULTICAST_LID_BASE)) अणु
		काष्ठा ib_global_route *grh = rdma_ah_retrieve_grh(attr);

		rdma_ah_set_ah_flags(attr, IB_AH_GRH);
		grh->sgid_index = 0;
		grh->hop_limit = 1;
		grh->dgid.global.subnet_prefix =
			ibp->rvp.gid_prefix;
		grh->dgid.global.पूर्णांकerface_id = OPA_MAKE_ID(dlid);
	पूर्ण
पूर्ण

अटल पूर्णांक hfi1_modअगरy_qp0_ah(काष्ठा hfi1_ibport *ibp,
			      काष्ठा rvt_ah *ah, u32 dlid)
अणु
	काष्ठा rdma_ah_attr attr;
	काष्ठा rvt_qp *qp0;
	पूर्णांक ret = -EINVAL;

	स_रखो(&attr, 0, माप(attr));
	attr.type = ah->ibah.type;
	hfi1_update_sm_ah_attr(ibp, &attr, dlid);
	rcu_पढ़ो_lock();
	qp0 = rcu_dereference(ibp->rvp.qp[0]);
	अगर (qp0)
		ret = rdma_modअगरy_ah(&ah->ibah, &attr);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल काष्ठा ib_ah *hfi1_create_qp0_ah(काष्ठा hfi1_ibport *ibp, u32 dlid)
अणु
	काष्ठा rdma_ah_attr attr;
	काष्ठा ib_ah *ah = ERR_PTR(-EINVAL);
	काष्ठा rvt_qp *qp0;
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा hfi1_devdata *dd = dd_from_ppd(ppd);
	u32 port_num = ppd->port;

	स_रखो(&attr, 0, माप(attr));
	attr.type = rdma_ah_find_type(&dd->verbs_dev.rdi.ibdev, port_num);
	hfi1_update_sm_ah_attr(ibp, &attr, dlid);
	rcu_पढ़ो_lock();
	qp0 = rcu_dereference(ibp->rvp.qp[0]);
	अगर (qp0)
		ah = rdma_create_ah(qp0->ibqp.pd, &attr, 0);
	rcu_पढ़ो_unlock();
	वापस ah;
पूर्ण

अटल व्योम send_trap(काष्ठा hfi1_ibport *ibp, काष्ठा trap_node *trap)
अणु
	काष्ठा ib_mad_send_buf *send_buf;
	काष्ठा ib_mad_agent *agent;
	काष्ठा opa_smp *smp;
	अचिन्हित दीर्घ flags;
	पूर्णांक pkey_idx;
	u32 qpn = ppd_from_ibp(ibp)->sm_trap_qp;

	agent = ibp->rvp.send_agent;
	अगर (!agent) अणु
		cleanup_traps(ibp, trap);
		वापस;
	पूर्ण

	/* o14-3.2.1 */
	अगर (driver_lstate(ppd_from_ibp(ibp)) != IB_PORT_ACTIVE) अणु
		cleanup_traps(ibp, trap);
		वापस;
	पूर्ण

	/* Add the trap to the list अगर necessary and see अगर we can send it */
	trap = check_and_add_trap(ibp, trap);
	अगर (!trap)
		वापस;

	pkey_idx = hfi1_lookup_pkey_idx(ibp, LIM_MGMT_P_KEY);
	अगर (pkey_idx < 0) अणु
		pr_warn("%s: failed to find limited mgmt pkey, defaulting 0x%x\n",
			__func__, hfi1_get_pkey(ibp, 1));
		pkey_idx = 1;
	पूर्ण

	send_buf = ib_create_send_mad(agent, qpn, pkey_idx, 0,
				      IB_MGMT_MAD_HDR, IB_MGMT_MAD_DATA,
				      GFP_ATOMIC, IB_MGMT_BASE_VERSION);
	अगर (IS_ERR(send_buf))
		वापस;

	smp = send_buf->mad;
	smp->base_version = OPA_MGMT_BASE_VERSION;
	smp->mgmt_class = IB_MGMT_CLASS_SUBN_LID_ROUTED;
	smp->class_version = OPA_SM_CLASS_VERSION;
	smp->method = IB_MGMT_METHOD_TRAP;

	/* Only update the transaction ID क्रम new traps (o13-5). */
	अगर (trap->tid == 0) अणु
		ibp->rvp.tid++;
		/* make sure that tid != 0 */
		अगर (ibp->rvp.tid == 0)
			ibp->rvp.tid++;
		trap->tid = cpu_to_be64(ibp->rvp.tid);
	पूर्ण
	smp->tid = trap->tid;

	smp->attr_id = IB_SMP_ATTR_NOTICE;
	/* o14-1: smp->mkey = 0; */

	स_नकल(smp->route.lid.data, &trap->data, trap->len);

	spin_lock_irqsave(&ibp->rvp.lock, flags);
	अगर (!ibp->rvp.sm_ah) अणु
		अगर (ibp->rvp.sm_lid != be16_to_cpu(IB_LID_PERMISSIVE)) अणु
			काष्ठा ib_ah *ah;

			ah = hfi1_create_qp0_ah(ibp, ibp->rvp.sm_lid);
			अगर (IS_ERR(ah)) अणु
				spin_unlock_irqrestore(&ibp->rvp.lock, flags);
				वापस;
			पूर्ण
			send_buf->ah = ah;
			ibp->rvp.sm_ah = ibah_to_rvtah(ah);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&ibp->rvp.lock, flags);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		send_buf->ah = &ibp->rvp.sm_ah->ibah;
	पूर्ण

	/*
	 * If the trap was repressed जबतक things were getting set up, करोn't
	 * bother sending it. This could happen क्रम a retry.
	 */
	अगर (trap->repress) अणु
		list_del(&trap->list);
		spin_unlock_irqrestore(&ibp->rvp.lock, flags);
		kमुक्त(trap);
		ib_मुक्त_send_mad(send_buf);
		वापस;
	पूर्ण

	trap->in_use = 0;
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

	अगर (ib_post_send_mad(send_buf, शून्य))
		ib_मुक्त_send_mad(send_buf);
पूर्ण

व्योम hfi1_handle_trap_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hfi1_ibport *ibp = from_समयr(ibp, t, rvp.trap_समयr);
	काष्ठा trap_node *trap = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* Find the trap with the highest priority */
	spin_lock_irqsave(&ibp->rvp.lock, flags);
	क्रम (i = 0; !trap && i < RVT_MAX_TRAP_LISTS; i++) अणु
		trap = list_first_entry_or_null(&ibp->rvp.trap_lists[i].list,
						काष्ठा trap_node, list);
	पूर्ण
	spin_unlock_irqrestore(&ibp->rvp.lock, flags);

	अगर (trap)
		send_trap(ibp, trap);
पूर्ण

अटल काष्ठा trap_node *create_trap_node(u8 type, __be16 trap_num, u32 lid)
अणु
	काष्ठा trap_node *trap;

	trap = kzalloc(माप(*trap), GFP_ATOMIC);
	अगर (!trap)
		वापस शून्य;

	INIT_LIST_HEAD(&trap->list);
	trap->data.generic_type = type;
	trap->data.prod_type_lsb = IB_NOTICE_PROD_CA;
	trap->data.trap_num = trap_num;
	trap->data.issuer_lid = cpu_to_be32(lid);

	वापस trap;
पूर्ण

/*
 * Send a bad P_Key trap (ch. 14.3.8).
 */
व्योम hfi1_bad_pkey(काष्ठा hfi1_ibport *ibp, u32 key, u32 sl,
		   u32 qp1, u32 qp2, u32 lid1, u32 lid2)
अणु
	काष्ठा trap_node *trap;
	u32 lid = ppd_from_ibp(ibp)->lid;

	ibp->rvp.n_pkt_drops++;
	ibp->rvp.pkey_violations++;

	trap = create_trap_node(IB_NOTICE_TYPE_SECURITY, OPA_TRAP_BAD_P_KEY,
				lid);
	अगर (!trap)
		वापस;

	/* Send violation trap */
	trap->data.ntc_257_258.lid1 = cpu_to_be32(lid1);
	trap->data.ntc_257_258.lid2 = cpu_to_be32(lid2);
	trap->data.ntc_257_258.key = cpu_to_be32(key);
	trap->data.ntc_257_258.sl = sl << 3;
	trap->data.ntc_257_258.qp1 = cpu_to_be32(qp1);
	trap->data.ntc_257_258.qp2 = cpu_to_be32(qp2);

	trap->len = माप(trap->data);
	send_trap(ibp, trap);
पूर्ण

/*
 * Send a bad M_Key trap (ch. 14.3.9).
 */
अटल व्योम bad_mkey(काष्ठा hfi1_ibport *ibp, काष्ठा ib_mad_hdr *mad,
		     __be64 mkey, __be32 dr_slid, u8 वापस_path[], u8 hop_cnt)
अणु
	काष्ठा trap_node *trap;
	u32 lid = ppd_from_ibp(ibp)->lid;

	trap = create_trap_node(IB_NOTICE_TYPE_SECURITY, OPA_TRAP_BAD_M_KEY,
				lid);
	अगर (!trap)
		वापस;

	/* Send violation trap */
	trap->data.ntc_256.lid = trap->data.issuer_lid;
	trap->data.ntc_256.method = mad->method;
	trap->data.ntc_256.attr_id = mad->attr_id;
	trap->data.ntc_256.attr_mod = mad->attr_mod;
	trap->data.ntc_256.mkey = mkey;
	अगर (mad->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) अणु
		trap->data.ntc_256.dr_slid = dr_slid;
		trap->data.ntc_256.dr_trunc_hop = IB_NOTICE_TRAP_DR_NOTICE;
		अगर (hop_cnt > ARRAY_SIZE(trap->data.ntc_256.dr_rtn_path)) अणु
			trap->data.ntc_256.dr_trunc_hop |=
				IB_NOTICE_TRAP_DR_TRUNC;
			hop_cnt = ARRAY_SIZE(trap->data.ntc_256.dr_rtn_path);
		पूर्ण
		trap->data.ntc_256.dr_trunc_hop |= hop_cnt;
		स_नकल(trap->data.ntc_256.dr_rtn_path, वापस_path,
		       hop_cnt);
	पूर्ण

	trap->len = माप(trap->data);

	send_trap(ibp, trap);
पूर्ण

/*
 * Send a Port Capability Mask Changed trap (ch. 14.3.11).
 */
व्योम hfi1_cap_mask_chg(काष्ठा rvt_dev_info *rdi, u32 port_num)
अणु
	काष्ठा trap_node *trap;
	काष्ठा hfi1_ibdev *verbs_dev = dev_from_rdi(rdi);
	काष्ठा hfi1_devdata *dd = dd_from_dev(verbs_dev);
	काष्ठा hfi1_ibport *ibp = &dd->pport[port_num - 1].ibport_data;
	u32 lid = ppd_from_ibp(ibp)->lid;

	trap = create_trap_node(IB_NOTICE_TYPE_INFO,
				OPA_TRAP_CHANGE_CAPABILITY,
				lid);
	अगर (!trap)
		वापस;

	trap->data.ntc_144.lid = trap->data.issuer_lid;
	trap->data.ntc_144.new_cap_mask = cpu_to_be32(ibp->rvp.port_cap_flags);
	trap->data.ntc_144.cap_mask3 = cpu_to_be16(ibp->rvp.port_cap3_flags);

	trap->len = माप(trap->data);
	send_trap(ibp, trap);
पूर्ण

/*
 * Send a System Image GUID Changed trap (ch. 14.3.12).
 */
व्योम hfi1_sys_guid_chg(काष्ठा hfi1_ibport *ibp)
अणु
	काष्ठा trap_node *trap;
	u32 lid = ppd_from_ibp(ibp)->lid;

	trap = create_trap_node(IB_NOTICE_TYPE_INFO, OPA_TRAP_CHANGE_SYSGUID,
				lid);
	अगर (!trap)
		वापस;

	trap->data.ntc_145.new_sys_guid = ib_hfi1_sys_image_guid;
	trap->data.ntc_145.lid = trap->data.issuer_lid;

	trap->len = माप(trap->data);
	send_trap(ibp, trap);
पूर्ण

/*
 * Send a Node Description Changed trap (ch. 14.3.13).
 */
व्योम hfi1_node_desc_chg(काष्ठा hfi1_ibport *ibp)
अणु
	काष्ठा trap_node *trap;
	u32 lid = ppd_from_ibp(ibp)->lid;

	trap = create_trap_node(IB_NOTICE_TYPE_INFO,
				OPA_TRAP_CHANGE_CAPABILITY,
				lid);
	अगर (!trap)
		वापस;

	trap->data.ntc_144.lid = trap->data.issuer_lid;
	trap->data.ntc_144.change_flags =
		cpu_to_be16(OPA_NOTICE_TRAP_NODE_DESC_CHG);

	trap->len = माप(trap->data);
	send_trap(ibp, trap);
पूर्ण

अटल पूर्णांक __subn_get_opa_nodedesc(काष्ठा opa_smp *smp, u32 am,
				   u8 *data, काष्ठा ib_device *ibdev,
				   u32 port, u32 *resp_len, u32 max_len)
अणु
	काष्ठा opa_node_description *nd;

	अगर (am || smp_length_check(माप(*nd), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	nd = (काष्ठा opa_node_description *)data;

	स_नकल(nd->data, ibdev->node_desc, माप(nd->data));

	अगर (resp_len)
		*resp_len += माप(*nd);

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_get_opa_nodeinfo(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	काष्ठा opa_node_info *ni;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 pidx = port - 1; /* IB number port from 1, hw from 0 */

	ni = (काष्ठा opa_node_info *)data;

	/* GUID 0 is illegal */
	अगर (am || pidx >= dd->num_pports || ibdev->node_guid == 0 ||
	    smp_length_check(माप(*ni), max_len) ||
	    get_sguid(to_iport(ibdev, port), HFI1_PORT_GUID_INDEX) == 0) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	ni->port_guid = get_sguid(to_iport(ibdev, port), HFI1_PORT_GUID_INDEX);
	ni->base_version = OPA_MGMT_BASE_VERSION;
	ni->class_version = OPA_SM_CLASS_VERSION;
	ni->node_type = 1;     /* channel adapter */
	ni->num_ports = ibdev->phys_port_cnt;
	/* This is alपढ़ोy in network order */
	ni->प्रणाली_image_guid = ib_hfi1_sys_image_guid;
	ni->node_guid = ibdev->node_guid;
	ni->partition_cap = cpu_to_be16(hfi1_get_npkeys(dd));
	ni->device_id = cpu_to_be16(dd->pcidev->device);
	ni->revision = cpu_to_be32(dd->minrev);
	ni->local_port_num = port;
	ni->venकरोr_id[0] = dd->oui1;
	ni->venकरोr_id[1] = dd->oui2;
	ni->venकरोr_id[2] = dd->oui3;

	अगर (resp_len)
		*resp_len += माप(*ni);

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक subn_get_nodeinfo(काष्ठा ib_smp *smp, काष्ठा ib_device *ibdev,
			     u32 port)
अणु
	काष्ठा ib_node_info *nip = (काष्ठा ib_node_info *)&smp->data;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 pidx = port - 1; /* IB number port from 1, hw from 0 */

	/* GUID 0 is illegal */
	अगर (smp->attr_mod || pidx >= dd->num_pports ||
	    ibdev->node_guid == 0 ||
	    get_sguid(to_iport(ibdev, port), HFI1_PORT_GUID_INDEX) == 0) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	nip->port_guid = get_sguid(to_iport(ibdev, port), HFI1_PORT_GUID_INDEX);
	nip->base_version = OPA_MGMT_BASE_VERSION;
	nip->class_version = OPA_SM_CLASS_VERSION;
	nip->node_type = 1;     /* channel adapter */
	nip->num_ports = ibdev->phys_port_cnt;
	/* This is alपढ़ोy in network order */
	nip->sys_guid = ib_hfi1_sys_image_guid;
	nip->node_guid = ibdev->node_guid;
	nip->partition_cap = cpu_to_be16(hfi1_get_npkeys(dd));
	nip->device_id = cpu_to_be16(dd->pcidev->device);
	nip->revision = cpu_to_be32(dd->minrev);
	nip->local_port_num = port;
	nip->venकरोr_id[0] = dd->oui1;
	nip->venकरोr_id[1] = dd->oui2;
	nip->venकरोr_id[2] = dd->oui3;

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल व्योम set_link_width_enabled(काष्ठा hfi1_pportdata *ppd, u32 w)
अणु
	(व्योम)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_LWID_ENB, w);
पूर्ण

अटल व्योम set_link_width_करोwngrade_enabled(काष्ठा hfi1_pportdata *ppd, u32 w)
अणु
	(व्योम)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_LWID_DG_ENB, w);
पूर्ण

अटल व्योम set_link_speed_enabled(काष्ठा hfi1_pportdata *ppd, u32 s)
अणु
	(व्योम)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_SPD_ENB, s);
पूर्ण

अटल पूर्णांक check_mkey(काष्ठा hfi1_ibport *ibp, काष्ठा ib_mad_hdr *mad,
		      पूर्णांक mad_flags, __be64 mkey, __be32 dr_slid,
		      u8 वापस_path[], u8 hop_cnt)
अणु
	पूर्णांक valid_mkey = 0;
	पूर्णांक ret = 0;

	/* Is the mkey in the process of expiring? */
	अगर (ibp->rvp.mkey_lease_समयout &&
	    समय_after_eq(jअगरfies, ibp->rvp.mkey_lease_समयout)) अणु
		/* Clear समयout and mkey protection field. */
		ibp->rvp.mkey_lease_समयout = 0;
		ibp->rvp.mkeyprot = 0;
	पूर्ण

	अगर ((mad_flags & IB_MAD_IGNORE_MKEY) ||  ibp->rvp.mkey == 0 ||
	    ibp->rvp.mkey == mkey)
		valid_mkey = 1;

	/* Unset lease समयout on any valid Get/Set/TrapRepress */
	अगर (valid_mkey && ibp->rvp.mkey_lease_समयout &&
	    (mad->method == IB_MGMT_METHOD_GET ||
	     mad->method == IB_MGMT_METHOD_SET ||
	     mad->method == IB_MGMT_METHOD_TRAP_REPRESS))
		ibp->rvp.mkey_lease_समयout = 0;

	अगर (!valid_mkey) अणु
		चयन (mad->method) अणु
		हाल IB_MGMT_METHOD_GET:
			/* Bad mkey not a violation below level 2 */
			अगर (ibp->rvp.mkeyprot < 2)
				अवरोध;
			fallthrough;
		हाल IB_MGMT_METHOD_SET:
		हाल IB_MGMT_METHOD_TRAP_REPRESS:
			अगर (ibp->rvp.mkey_violations != 0xFFFF)
				++ibp->rvp.mkey_violations;
			अगर (!ibp->rvp.mkey_lease_समयout &&
			    ibp->rvp.mkey_lease_period)
				ibp->rvp.mkey_lease_समयout = jअगरfies +
					ibp->rvp.mkey_lease_period * HZ;
			/* Generate a trap notice. */
			bad_mkey(ibp, mad, mkey, dr_slid, वापस_path,
				 hop_cnt);
			ret = 1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The SMA caches पढ़ोs from LCB रेजिस्टरs in हाल the LCB is unavailable.
 * (The LCB is unavailable in certain link states, क्रम example.)
 */
काष्ठा lcb_datum अणु
	u32 off;
	u64 val;
पूर्ण;

अटल काष्ठा lcb_datum lcb_cache[] = अणु
	अणु DC_LCB_STS_ROUND_TRIP_LTP_CNT, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक ग_लिखो_lcb_cache(u32 off, u64 val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lcb_cache); i++) अणु
		अगर (lcb_cache[i].off == off) अणु
			lcb_cache[i].val = val;
			वापस 0;
		पूर्ण
	पूर्ण

	pr_warn("%s bad offset 0x%x\n", __func__, off);
	वापस -1;
पूर्ण

अटल पूर्णांक पढ़ो_lcb_cache(u32 off, u64 *val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lcb_cache); i++) अणु
		अगर (lcb_cache[i].off == off) अणु
			*val = lcb_cache[i].val;
			वापस 0;
		पूर्ण
	पूर्ण

	pr_warn("%s bad offset 0x%x\n", __func__, off);
	वापस -1;
पूर्ण

व्योम पढ़ो_ltp_rtt(काष्ठा hfi1_devdata *dd)
अणु
	u64 reg;

	अगर (पढ़ो_lcb_csr(dd, DC_LCB_STS_ROUND_TRIP_LTP_CNT, &reg))
		dd_dev_err(dd, "%s: unable to read LTP RTT\n", __func__);
	अन्यथा
		ग_लिखो_lcb_cache(DC_LCB_STS_ROUND_TRIP_LTP_CNT, reg);
पूर्ण

अटल पूर्णांक __subn_get_opa_portinfo(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	पूर्णांक i;
	काष्ठा hfi1_devdata *dd;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा opa_port_info *pi = (काष्ठा opa_port_info *)data;
	u8 mtu;
	u8 credit_rate;
	u8 is_beaconing_active;
	u32 state;
	u32 num_ports = OPA_AM_NPORT(am);
	u32 start_of_sm_config = OPA_AM_START_SM_CFG(am);
	u32 buffer_units;
	u64 पंचांगp = 0;

	अगर (num_ports != 1 || smp_length_check(माप(*pi), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	dd = dd_from_ibdev(ibdev);
	/* IB numbers ports from 1, hw from 0 */
	ppd = dd->pport + (port - 1);
	ibp = &ppd->ibport_data;

	अगर (ppd->vls_supported / 2 > ARRAY_SIZE(pi->neigh_mtu.pvlx_to_mtu) ||
	    ppd->vls_supported > ARRAY_SIZE(dd->vld)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	pi->lid = cpu_to_be32(ppd->lid);

	/* Only वापस the mkey अगर the protection field allows it. */
	अगर (!(smp->method == IB_MGMT_METHOD_GET &&
	      ibp->rvp.mkey != smp->mkey &&
	      ibp->rvp.mkeyprot == 1))
		pi->mkey = ibp->rvp.mkey;

	pi->subnet_prefix = ibp->rvp.gid_prefix;
	pi->sm_lid = cpu_to_be32(ibp->rvp.sm_lid);
	pi->ib_cap_mask = cpu_to_be32(ibp->rvp.port_cap_flags);
	pi->mkey_lease_period = cpu_to_be16(ibp->rvp.mkey_lease_period);
	pi->sm_trap_qp = cpu_to_be32(ppd->sm_trap_qp);
	pi->sa_qp = cpu_to_be32(ppd->sa_qp);

	pi->link_width.enabled = cpu_to_be16(ppd->link_width_enabled);
	pi->link_width.supported = cpu_to_be16(ppd->link_width_supported);
	pi->link_width.active = cpu_to_be16(ppd->link_width_active);

	pi->link_width_करोwngrade.supported =
			cpu_to_be16(ppd->link_width_करोwngrade_supported);
	pi->link_width_करोwngrade.enabled =
			cpu_to_be16(ppd->link_width_करोwngrade_enabled);
	pi->link_width_करोwngrade.tx_active =
			cpu_to_be16(ppd->link_width_करोwngrade_tx_active);
	pi->link_width_करोwngrade.rx_active =
			cpu_to_be16(ppd->link_width_करोwngrade_rx_active);

	pi->link_speed.supported = cpu_to_be16(ppd->link_speed_supported);
	pi->link_speed.active = cpu_to_be16(ppd->link_speed_active);
	pi->link_speed.enabled = cpu_to_be16(ppd->link_speed_enabled);

	state = driver_lstate(ppd);

	अगर (start_of_sm_config && (state == IB_PORT_INIT))
		ppd->is_sm_config_started = 1;

	pi->port_phys_conf = (ppd->port_type & 0xf);

	pi->port_states.ledenable_offlinereason = ppd->neighbor_normal << 4;
	pi->port_states.ledenable_offlinereason |=
		ppd->is_sm_config_started << 5;
	/*
	 * This pairs with the memory barrier in hfi1_start_led_override to
	 * ensure that we पढ़ो the correct state of LED beaconing represented
	 * by led_override_समयr_active
	 */
	smp_rmb();
	is_beaconing_active = !!atomic_पढ़ो(&ppd->led_override_समयr_active);
	pi->port_states.ledenable_offlinereason |= is_beaconing_active << 6;
	pi->port_states.ledenable_offlinereason |=
		ppd->offline_disabled_reason;

	pi->port_states.portphysstate_portstate =
		(driver_pstate(ppd) << 4) | state;

	pi->mkeyprotect_lmc = (ibp->rvp.mkeyprot << 6) | ppd->lmc;

	स_रखो(pi->neigh_mtu.pvlx_to_mtu, 0, माप(pi->neigh_mtu.pvlx_to_mtu));
	क्रम (i = 0; i < ppd->vls_supported; i++) अणु
		mtu = mtu_to_क्रमागत(dd->vld[i].mtu, HFI1_DEFAULT_ACTIVE_MTU);
		अगर ((i % 2) == 0)
			pi->neigh_mtu.pvlx_to_mtu[i / 2] |= (mtu << 4);
		अन्यथा
			pi->neigh_mtu.pvlx_to_mtu[i / 2] |= mtu;
	पूर्ण
	/* करोn't क्रमget VL 15 */
	mtu = mtu_to_क्रमागत(dd->vld[15].mtu, 2048);
	pi->neigh_mtu.pvlx_to_mtu[15 / 2] |= mtu;
	pi->smsl = ibp->rvp.sm_sl & OPA_PI_MASK_SMSL;
	pi->operational_vls = hfi1_get_ib_cfg(ppd, HFI1_IB_CFG_OP_VLS);
	pi->partenक्रमce_filterraw |=
		(ppd->linkinit_reason & OPA_PI_MASK_LINKINIT_REASON);
	अगर (ppd->part_enक्रमce & HFI1_PART_ENFORCE_IN)
		pi->partenक्रमce_filterraw |= OPA_PI_MASK_PARTITION_ENFORCE_IN;
	अगर (ppd->part_enक्रमce & HFI1_PART_ENFORCE_OUT)
		pi->partenक्रमce_filterraw |= OPA_PI_MASK_PARTITION_ENFORCE_OUT;
	pi->mkey_violations = cpu_to_be16(ibp->rvp.mkey_violations);
	/* P_KeyViolations are counted by hardware. */
	pi->pkey_violations = cpu_to_be16(ibp->rvp.pkey_violations);
	pi->qkey_violations = cpu_to_be16(ibp->rvp.qkey_violations);

	pi->vl.cap = ppd->vls_supported;
	pi->vl.high_limit = cpu_to_be16(ibp->rvp.vl_high_limit);
	pi->vl.arb_high_cap = (u8)hfi1_get_ib_cfg(ppd, HFI1_IB_CFG_VL_HIGH_CAP);
	pi->vl.arb_low_cap = (u8)hfi1_get_ib_cfg(ppd, HFI1_IB_CFG_VL_LOW_CAP);

	pi->clientrereg_subnetसमयout = ibp->rvp.subnet_समयout;

	pi->port_link_mode  = cpu_to_be16(OPA_PORT_LINK_MODE_OPA << 10 |
					  OPA_PORT_LINK_MODE_OPA << 5 |
					  OPA_PORT_LINK_MODE_OPA);

	pi->port_ltp_crc_mode = cpu_to_be16(ppd->port_ltp_crc_mode);

	pi->port_mode = cpu_to_be16(
				ppd->is_active_optimize_enabled ?
					OPA_PI_MASK_PORT_ACTIVE_OPTOMIZE : 0);

	pi->port_packet_क्रमmat.supported =
		cpu_to_be16(OPA_PORT_PACKET_FORMAT_9B |
			    OPA_PORT_PACKET_FORMAT_16B);
	pi->port_packet_क्रमmat.enabled =
		cpu_to_be16(OPA_PORT_PACKET_FORMAT_9B |
			    OPA_PORT_PACKET_FORMAT_16B);

	/* flit_control.पूर्णांकerleave is (OPA V1, version .76):
	 * bits		use
	 * ----		---
	 * 2		res
	 * 2		DistanceSupported
	 * 2		DistanceEnabled
	 * 5		MaxNextLevelTxEnabled
	 * 5		MaxNestLevelRxSupported
	 *
	 * HFI supports only "distance mode 1" (see OPA V1, version .76,
	 * section 9.6.2), so set DistanceSupported, DistanceEnabled
	 * to 0x1.
	 */
	pi->flit_control.पूर्णांकerleave = cpu_to_be16(0x1400);

	pi->link_करोwn_reason = ppd->local_link_करोwn_reason.sma;
	pi->neigh_link_करोwn_reason = ppd->neigh_link_करोwn_reason.sma;
	pi->port_error_action = cpu_to_be32(ppd->port_error_action);
	pi->mtucap = mtu_to_क्रमागत(hfi1_max_mtu, IB_MTU_4096);

	/* 32.768 usec. response समय (guessing) */
	pi->respसमयvalue = 3;

	pi->local_port_num = port;

	/* buffer info क्रम FM */
	pi->overall_buffer_space = cpu_to_be16(dd->link_credits);

	pi->neigh_node_guid = cpu_to_be64(ppd->neighbor_guid);
	pi->neigh_port_num = ppd->neighbor_port_number;
	pi->port_neigh_mode =
		(ppd->neighbor_type & OPA_PI_MASK_NEIGH_NODE_TYPE) |
		(ppd->mgmt_allowed ? OPA_PI_MASK_NEIGH_MGMT_ALLOWED : 0) |
		(ppd->neighbor_fm_security ?
			OPA_PI_MASK_NEIGH_FW_AUTH_BYPASS : 0);

	/* HFIs shall always वापस VL15 credits to their
	 * neighbor in a समयly manner, without any credit वापस pacing.
	 */
	credit_rate = 0;
	buffer_units  = (dd->vau) & OPA_PI_MASK_BUF_UNIT_BUF_ALLOC;
	buffer_units |= (dd->vcu << 3) & OPA_PI_MASK_BUF_UNIT_CREDIT_ACK;
	buffer_units |= (credit_rate << 6) &
				OPA_PI_MASK_BUF_UNIT_VL15_CREDIT_RATE;
	buffer_units |= (dd->vl15_init << 11) & OPA_PI_MASK_BUF_UNIT_VL15_INIT;
	pi->buffer_units = cpu_to_be32(buffer_units);

	pi->opa_cap_mask = cpu_to_be16(ibp->rvp.port_cap3_flags);
	pi->collectivemask_multicasपंचांगask = ((OPA_COLLECTIVE_NR & 0x7)
					    << 3 | (OPA_MCAST_NR & 0x7));

	/* HFI supports a replay buffer 128 LTPs in size */
	pi->replay_depth.buffer = 0x80;
	/* पढ़ो the cached value of DC_LCB_STS_ROUND_TRIP_LTP_CNT */
	पढ़ो_lcb_cache(DC_LCB_STS_ROUND_TRIP_LTP_CNT, &पंचांगp);

	/*
	 * this counter is 16 bits wide, but the replay_depth.wire
	 * variable is only 8 bits
	 */
	अगर (पंचांगp > 0xff)
		पंचांगp = 0xff;
	pi->replay_depth.wire = पंचांगp;

	अगर (resp_len)
		*resp_len += माप(काष्ठा opa_port_info);

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

/**
 * get_pkeys - वापस the PKEY table
 * @dd: the hfi1_ib device
 * @port: the IB port number
 * @pkeys: the pkey table is placed here
 */
अटल पूर्णांक get_pkeys(काष्ठा hfi1_devdata *dd, u32 port, u16 *pkeys)
अणु
	काष्ठा hfi1_pportdata *ppd = dd->pport + port - 1;

	स_नकल(pkeys, ppd->pkeys, माप(ppd->pkeys));

	वापस 0;
पूर्ण

अटल पूर्णांक __subn_get_opa_pkeytable(काष्ठा opa_smp *smp, u32 am, u8 *data,
				    काष्ठा ib_device *ibdev, u32 port,
				    u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 n_blocks_req = OPA_AM_NBLK(am);
	u32 start_block = am & 0x7ff;
	__be16 *p;
	u16 *q;
	पूर्णांक i;
	u16 n_blocks_avail;
	अचिन्हित npkeys = hfi1_get_npkeys(dd);
	माप_प्रकार size;

	अगर (n_blocks_req == 0) अणु
		pr_warn("OPA Get PKey AM Invalid : P = %d; B = 0x%x; N = 0x%x\n",
			port, start_block, n_blocks_req);
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	n_blocks_avail = (u16)(npkeys / OPA_PARTITION_TABLE_BLK_SIZE) + 1;

	size = (n_blocks_req * OPA_PARTITION_TABLE_BLK_SIZE) * माप(u16);

	अगर (smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	अगर (start_block + n_blocks_req > n_blocks_avail ||
	    n_blocks_req > OPA_NUM_PKEY_BLOCKS_PER_SMP) अणु
		pr_warn("OPA Get PKey AM Invalid : s 0x%x; req 0x%x; "
			"avail 0x%x; blk/smp 0x%lx\n",
			start_block, n_blocks_req, n_blocks_avail,
			OPA_NUM_PKEY_BLOCKS_PER_SMP);
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	p = (__be16 *)data;
	q = (u16 *)data;
	/* get the real pkeys अगर we are requesting the first block */
	अगर (start_block == 0) अणु
		get_pkeys(dd, port, q);
		क्रम (i = 0; i < npkeys; i++)
			p[i] = cpu_to_be16(q[i]);
		अगर (resp_len)
			*resp_len += size;
	पूर्ण अन्यथा अणु
		smp->status |= IB_SMP_INVALID_FIELD;
	पूर्ण
	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

क्रमागत अणु
	HFI_TRANSITION_DISALLOWED,
	HFI_TRANSITION_IGNORED,
	HFI_TRANSITION_ALLOWED,
	HFI_TRANSITION_UNDEFINED,
पूर्ण;

/*
 * Use लघुened names to improve पढ़ोability of
 * अणुlogical,physicalपूर्ण_state_transitions
 */
क्रमागत अणु
	__D = HFI_TRANSITION_DISALLOWED,
	__I = HFI_TRANSITION_IGNORED,
	__A = HFI_TRANSITION_ALLOWED,
	__U = HFI_TRANSITION_UNDEFINED,
पूर्ण;

/*
 * IB_PORTPHYSSTATE_POLLING (2) through OPA_PORTPHYSSTATE_MAX (11) are
 * represented in physical_state_transitions.
 */
#घोषणा __N_PHYSTATES (OPA_PORTPHYSSTATE_MAX - IB_PORTPHYSSTATE_POLLING + 1)

/*
 * Within physical_state_transitions, rows represent "old" states,
 * columns "new" states, and physical_state_transitions.allowed[old][new]
 * indicates अगर the transition from old state to new state is legal (see
 * OPAg1v1, Table 6-4).
 */
अटल स्थिर काष्ठा अणु
	u8 allowed[__N_PHYSTATES][__N_PHYSTATES];
पूर्ण physical_state_transitions = अणु
	अणु
		/* 2    3    4    5    6    7    8    9   10   11 */
	/* 2 */	अणु __A, __A, __D, __D, __D, __D, __D, __D, __D, __D पूर्ण,
	/* 3 */	अणु __A, __I, __D, __D, __D, __D, __D, __D, __D, __A पूर्ण,
	/* 4 */	अणु __U, __U, __U, __U, __U, __U, __U, __U, __U, __U पूर्ण,
	/* 5 */	अणु __A, __A, __D, __I, __D, __D, __D, __D, __D, __D पूर्ण,
	/* 6 */	अणु __U, __U, __U, __U, __U, __U, __U, __U, __U, __U पूर्ण,
	/* 7 */	अणु __D, __A, __D, __D, __D, __I, __D, __D, __D, __D पूर्ण,
	/* 8 */	अणु __U, __U, __U, __U, __U, __U, __U, __U, __U, __U पूर्ण,
	/* 9 */	अणु __I, __A, __D, __D, __D, __D, __D, __I, __D, __D पूर्ण,
	/*10 */	अणु __U, __U, __U, __U, __U, __U, __U, __U, __U, __U पूर्ण,
	/*11 */	अणु __D, __A, __D, __D, __D, __D, __D, __D, __D, __I पूर्ण,
	पूर्ण
पूर्ण;

/*
 * IB_PORT_DOWN (1) through IB_PORT_ACTIVE_DEFER (5) are represented
 * logical_state_transitions
 */

#घोषणा __N_LOGICAL_STATES (IB_PORT_ACTIVE_DEFER - IB_PORT_DOWN + 1)

/*
 * Within logical_state_transitions rows represent "old" states,
 * columns "new" states, and logical_state_transitions.allowed[old][new]
 * indicates अगर the transition from old state to new state is legal (see
 * OPAg1v1, Table 9-12).
 */
अटल स्थिर काष्ठा अणु
	u8 allowed[__N_LOGICAL_STATES][__N_LOGICAL_STATES];
पूर्ण logical_state_transitions = अणु
	अणु
		/* 1    2    3    4    5 */
	/* 1 */	अणु __I, __D, __D, __D, __Uपूर्ण,
	/* 2 */	अणु __D, __I, __A, __D, __Uपूर्ण,
	/* 3 */	अणु __D, __D, __I, __A, __Uपूर्ण,
	/* 4 */	अणु __D, __D, __I, __I, __Uपूर्ण,
	/* 5 */	अणु __U, __U, __U, __U, __Uपूर्ण,
	पूर्ण
पूर्ण;

अटल पूर्णांक logical_transition_allowed(पूर्णांक old, पूर्णांक new)
अणु
	अगर (old < IB_PORT_NOP || old > IB_PORT_ACTIVE_DEFER ||
	    new < IB_PORT_NOP || new > IB_PORT_ACTIVE_DEFER) अणु
		pr_warn("invalid logical state(s) (old %d new %d)\n",
			old, new);
		वापस HFI_TRANSITION_UNDEFINED;
	पूर्ण

	अगर (new == IB_PORT_NOP)
		वापस HFI_TRANSITION_ALLOWED; /* always allowed */

	/* adjust states क्रम indexing पूर्णांकo logical_state_transitions */
	old -= IB_PORT_DOWN;
	new -= IB_PORT_DOWN;

	अगर (old < 0 || new < 0)
		वापस HFI_TRANSITION_UNDEFINED;
	वापस logical_state_transitions.allowed[old][new];
पूर्ण

अटल पूर्णांक physical_transition_allowed(पूर्णांक old, पूर्णांक new)
अणु
	अगर (old < IB_PORTPHYSSTATE_NOP || old > OPA_PORTPHYSSTATE_MAX ||
	    new < IB_PORTPHYSSTATE_NOP || new > OPA_PORTPHYSSTATE_MAX) अणु
		pr_warn("invalid physical state(s) (old %d new %d)\n",
			old, new);
		वापस HFI_TRANSITION_UNDEFINED;
	पूर्ण

	अगर (new == IB_PORTPHYSSTATE_NOP)
		वापस HFI_TRANSITION_ALLOWED; /* always allowed */

	/* adjust states क्रम indexing पूर्णांकo physical_state_transitions */
	old -= IB_PORTPHYSSTATE_POLLING;
	new -= IB_PORTPHYSSTATE_POLLING;

	अगर (old < 0 || new < 0)
		वापस HFI_TRANSITION_UNDEFINED;
	वापस physical_state_transitions.allowed[old][new];
पूर्ण

अटल पूर्णांक port_states_transition_allowed(काष्ठा hfi1_pportdata *ppd,
					  u32 logical_new, u32 physical_new)
अणु
	u32 physical_old = driver_pstate(ppd);
	u32 logical_old = driver_lstate(ppd);
	पूर्णांक ret, logical_allowed, physical_allowed;

	ret = logical_transition_allowed(logical_old, logical_new);
	logical_allowed = ret;

	अगर (ret == HFI_TRANSITION_DISALLOWED ||
	    ret == HFI_TRANSITION_UNDEFINED) अणु
		pr_warn("invalid logical state transition %s -> %s\n",
			opa_lstate_name(logical_old),
			opa_lstate_name(logical_new));
		वापस ret;
	पूर्ण

	ret = physical_transition_allowed(physical_old, physical_new);
	physical_allowed = ret;

	अगर (ret == HFI_TRANSITION_DISALLOWED ||
	    ret == HFI_TRANSITION_UNDEFINED) अणु
		pr_warn("invalid physical state transition %s -> %s\n",
			opa_pstate_name(physical_old),
			opa_pstate_name(physical_new));
		वापस ret;
	पूर्ण

	अगर (logical_allowed == HFI_TRANSITION_IGNORED &&
	    physical_allowed == HFI_TRANSITION_IGNORED)
		वापस HFI_TRANSITION_IGNORED;

	/*
	 * A change request of Physical Port State from
	 * 'Offline' to 'Polling' should be ignored.
	 */
	अगर ((physical_old == OPA_PORTPHYSSTATE_OFFLINE) &&
	    (physical_new == IB_PORTPHYSSTATE_POLLING))
		वापस HFI_TRANSITION_IGNORED;

	/*
	 * Either physical_allowed or logical_allowed is
	 * HFI_TRANSITION_ALLOWED.
	 */
	वापस HFI_TRANSITION_ALLOWED;
पूर्ण

अटल पूर्णांक set_port_states(काष्ठा hfi1_pportdata *ppd, काष्ठा opa_smp *smp,
			   u32 logical_state, u32 phys_state, पूर्णांक local_mad)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u32 link_state;
	पूर्णांक ret;

	ret = port_states_transition_allowed(ppd, logical_state, phys_state);
	अगर (ret == HFI_TRANSITION_DISALLOWED ||
	    ret == HFI_TRANSITION_UNDEFINED) अणु
		/* error message emitted above */
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस 0;
	पूर्ण

	अगर (ret == HFI_TRANSITION_IGNORED)
		वापस 0;

	अगर ((phys_state != IB_PORTPHYSSTATE_NOP) &&
	    !(logical_state == IB_PORT_DOWN ||
	      logical_state == IB_PORT_NOP))अणु
		pr_warn("SubnSet(OPA_PortInfo) port state invalid: logical_state 0x%x physical_state 0x%x\n",
			logical_state, phys_state);
		smp->status |= IB_SMP_INVALID_FIELD;
	पूर्ण

	/*
	 * Logical state changes are summarized in OPAv1g1 spec.,
	 * Table 9-12; physical state changes are summarized in
	 * OPAv1g1 spec., Table 6.4.
	 */
	चयन (logical_state) अणु
	हाल IB_PORT_NOP:
		अगर (phys_state == IB_PORTPHYSSTATE_NOP)
			अवरोध;
		fallthrough;
	हाल IB_PORT_DOWN:
		अगर (phys_state == IB_PORTPHYSSTATE_NOP) अणु
			link_state = HLS_DN_DOWNDEF;
		पूर्ण अन्यथा अगर (phys_state == IB_PORTPHYSSTATE_POLLING) अणु
			link_state = HLS_DN_POLL;
			set_link_करोwn_reason(ppd, OPA_LINKDOWN_REASON_FM_BOUNCE,
					     0, OPA_LINKDOWN_REASON_FM_BOUNCE);
		पूर्ण अन्यथा अगर (phys_state == IB_PORTPHYSSTATE_DISABLED) अणु
			link_state = HLS_DN_DISABLE;
		पूर्ण अन्यथा अणु
			pr_warn("SubnSet(OPA_PortInfo) invalid physical state 0x%x\n",
				phys_state);
			smp->status |= IB_SMP_INVALID_FIELD;
			अवरोध;
		पूर्ण

		अगर ((link_state == HLS_DN_POLL ||
		     link_state == HLS_DN_DOWNDEF)) अणु
			/*
			 * Going to poll.  No matter what the current state,
			 * always move offline first, then tune and start the
			 * link.  This correctly handles a FM link bounce and
			 * a link enable.  Going offline is a no-op अगर alपढ़ोy
			 * offline.
			 */
			set_link_state(ppd, HLS_DN_OFFLINE);
			start_link(ppd);
		पूर्ण अन्यथा अणु
			set_link_state(ppd, link_state);
		पूर्ण
		अगर (link_state == HLS_DN_DISABLE &&
		    (ppd->offline_disabled_reason >
		     HFI1_ODR_MASK(OPA_LINKDOWN_REASON_SMA_DISABLED) ||
		     ppd->offline_disabled_reason ==
		     HFI1_ODR_MASK(OPA_LINKDOWN_REASON_NONE)))
			ppd->offline_disabled_reason =
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_SMA_DISABLED);
		/*
		 * Don't send a reply अगर the response would be sent
		 * through the disabled port.
		 */
		अगर (link_state == HLS_DN_DISABLE && !local_mad)
			वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
		अवरोध;
	हाल IB_PORT_ARMED:
		ret = set_link_state(ppd, HLS_UP_ARMED);
		अगर (!ret)
			send_idle_sma(dd, SMA_IDLE_ARM);
		अवरोध;
	हाल IB_PORT_ACTIVE:
		अगर (ppd->neighbor_normal) अणु
			ret = set_link_state(ppd, HLS_UP_ACTIVE);
			अगर (ret == 0)
				send_idle_sma(dd, SMA_IDLE_ACTIVE);
		पूर्ण अन्यथा अणु
			pr_warn("SubnSet(OPA_PortInfo) Cannot move to Active with NeighborNormal 0\n");
			smp->status |= IB_SMP_INVALID_FIELD;
		पूर्ण
		अवरोध;
	शेष:
		pr_warn("SubnSet(OPA_PortInfo) invalid logical state 0x%x\n",
			logical_state);
		smp->status |= IB_SMP_INVALID_FIELD;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * subn_set_opa_portinfo - set port inक्रमmation
 * @smp: the incoming SM packet
 * @ibdev: the infiniband device
 * @port: the port on the device
 *
 */
अटल पूर्णांक __subn_set_opa_portinfo(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len, पूर्णांक local_mad)
अणु
	काष्ठा opa_port_info *pi = (काष्ठा opa_port_info *)data;
	काष्ठा ib_event event;
	काष्ठा hfi1_devdata *dd;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_ibport *ibp;
	u8 clientrereg;
	अचिन्हित दीर्घ flags;
	u32 smlid;
	u32 lid;
	u8 ls_old, ls_new, ps_new;
	u8 vls;
	u8 msl;
	u8 crc_enabled;
	u16 lse, lwe, mtu;
	u32 num_ports = OPA_AM_NPORT(am);
	u32 start_of_sm_config = OPA_AM_START_SM_CFG(am);
	पूर्णांक ret, i, invalid = 0, call_set_mtu = 0;
	पूर्णांक call_link_करोwngrade_policy = 0;

	अगर (num_ports != 1 ||
	    smp_length_check(माप(*pi), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	lid = be32_to_cpu(pi->lid);
	अगर (lid & 0xFF000000) अणु
		pr_warn("OPA_PortInfo lid out of range: %X\n", lid);
		smp->status |= IB_SMP_INVALID_FIELD;
		जाओ get_only;
	पूर्ण


	smlid = be32_to_cpu(pi->sm_lid);
	अगर (smlid & 0xFF000000) अणु
		pr_warn("OPA_PortInfo SM lid out of range: %X\n", smlid);
		smp->status |= IB_SMP_INVALID_FIELD;
		जाओ get_only;
	पूर्ण

	clientrereg = (pi->clientrereg_subnetसमयout &
			OPA_PI_MASK_CLIENT_REREGISTER);

	dd = dd_from_ibdev(ibdev);
	/* IB numbers ports from 1, hw from 0 */
	ppd = dd->pport + (port - 1);
	ibp = &ppd->ibport_data;
	event.device = ibdev;
	event.element.port_num = port;

	ls_old = driver_lstate(ppd);

	ibp->rvp.mkey = pi->mkey;
	अगर (ibp->rvp.gid_prefix != pi->subnet_prefix) अणु
		ibp->rvp.gid_prefix = pi->subnet_prefix;
		event.event = IB_EVENT_GID_CHANGE;
		ib_dispatch_event(&event);
	पूर्ण
	ibp->rvp.mkey_lease_period = be16_to_cpu(pi->mkey_lease_period);

	/* Must be a valid unicast LID address. */
	अगर ((lid == 0 && ls_old > IB_PORT_INIT) ||
	     (hfi1_is_16B_mcast(lid))) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		pr_warn("SubnSet(OPA_PortInfo) lid invalid 0x%x\n",
			lid);
	पूर्ण अन्यथा अगर (ppd->lid != lid ||
		 ppd->lmc != (pi->mkeyprotect_lmc & OPA_PI_MASK_LMC)) अणु
		अगर (ppd->lid != lid)
			hfi1_set_uevent_bits(ppd, _HFI1_EVENT_LID_CHANGE_BIT);
		अगर (ppd->lmc != (pi->mkeyprotect_lmc & OPA_PI_MASK_LMC))
			hfi1_set_uevent_bits(ppd, _HFI1_EVENT_LMC_CHANGE_BIT);
		hfi1_set_lid(ppd, lid, pi->mkeyprotect_lmc & OPA_PI_MASK_LMC);
		event.event = IB_EVENT_LID_CHANGE;
		ib_dispatch_event(&event);

		अगर (HFI1_PORT_GUID_INDEX + 1 < HFI1_GUIDS_PER_PORT) अणु
			/* Manufacture GID from LID to support extended
			 * addresses
			 */
			ppd->guids[HFI1_PORT_GUID_INDEX + 1] =
				be64_to_cpu(OPA_MAKE_ID(lid));
			event.event = IB_EVENT_GID_CHANGE;
			ib_dispatch_event(&event);
		पूर्ण
	पूर्ण

	msl = pi->smsl & OPA_PI_MASK_SMSL;
	अगर (pi->partenक्रमce_filterraw & OPA_PI_MASK_LINKINIT_REASON)
		ppd->linkinit_reason =
			(pi->partenक्रमce_filterraw &
			 OPA_PI_MASK_LINKINIT_REASON);

	/* Must be a valid unicast LID address. */
	अगर ((smlid == 0 && ls_old > IB_PORT_INIT) ||
	     (hfi1_is_16B_mcast(smlid))) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		pr_warn("SubnSet(OPA_PortInfo) smlid invalid 0x%x\n", smlid);
	पूर्ण अन्यथा अगर (smlid != ibp->rvp.sm_lid || msl != ibp->rvp.sm_sl) अणु
		pr_warn("SubnSet(OPA_PortInfo) smlid 0x%x\n", smlid);
		spin_lock_irqsave(&ibp->rvp.lock, flags);
		अगर (ibp->rvp.sm_ah) अणु
			अगर (smlid != ibp->rvp.sm_lid)
				hfi1_modअगरy_qp0_ah(ibp, ibp->rvp.sm_ah, smlid);
			अगर (msl != ibp->rvp.sm_sl)
				rdma_ah_set_sl(&ibp->rvp.sm_ah->attr, msl);
		पूर्ण
		spin_unlock_irqrestore(&ibp->rvp.lock, flags);
		अगर (smlid != ibp->rvp.sm_lid)
			ibp->rvp.sm_lid = smlid;
		अगर (msl != ibp->rvp.sm_sl)
			ibp->rvp.sm_sl = msl;
		event.event = IB_EVENT_SM_CHANGE;
		ib_dispatch_event(&event);
	पूर्ण

	अगर (pi->link_करोwn_reason == 0) अणु
		ppd->local_link_करोwn_reason.sma = 0;
		ppd->local_link_करोwn_reason.latest = 0;
	पूर्ण

	अगर (pi->neigh_link_करोwn_reason == 0) अणु
		ppd->neigh_link_करोwn_reason.sma = 0;
		ppd->neigh_link_करोwn_reason.latest = 0;
	पूर्ण

	ppd->sm_trap_qp = be32_to_cpu(pi->sm_trap_qp);
	ppd->sa_qp = be32_to_cpu(pi->sa_qp);

	ppd->port_error_action = be32_to_cpu(pi->port_error_action);
	lwe = be16_to_cpu(pi->link_width.enabled);
	अगर (lwe) अणु
		अगर (lwe == OPA_LINK_WIDTH_RESET ||
		    lwe == OPA_LINK_WIDTH_RESET_OLD)
			set_link_width_enabled(ppd, ppd->link_width_supported);
		अन्यथा अगर ((lwe & ~ppd->link_width_supported) == 0)
			set_link_width_enabled(ppd, lwe);
		अन्यथा
			smp->status |= IB_SMP_INVALID_FIELD;
	पूर्ण
	lwe = be16_to_cpu(pi->link_width_करोwngrade.enabled);
	/* LWD.E is always applied - 0 means "disabled" */
	अगर (lwe == OPA_LINK_WIDTH_RESET ||
	    lwe == OPA_LINK_WIDTH_RESET_OLD) अणु
		set_link_width_करोwngrade_enabled(ppd,
						 ppd->
						 link_width_करोwngrade_supported
						 );
	पूर्ण अन्यथा अगर ((lwe & ~ppd->link_width_करोwngrade_supported) == 0) अणु
		/* only set and apply अगर something changed */
		अगर (lwe != ppd->link_width_करोwngrade_enabled) अणु
			set_link_width_करोwngrade_enabled(ppd, lwe);
			call_link_करोwngrade_policy = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		smp->status |= IB_SMP_INVALID_FIELD;
	पूर्ण
	lse = be16_to_cpu(pi->link_speed.enabled);
	अगर (lse) अणु
		अगर (lse & be16_to_cpu(pi->link_speed.supported))
			set_link_speed_enabled(ppd, lse);
		अन्यथा
			smp->status |= IB_SMP_INVALID_FIELD;
	पूर्ण

	ibp->rvp.mkeyprot =
		(pi->mkeyprotect_lmc & OPA_PI_MASK_MKEY_PROT_BIT) >> 6;
	ibp->rvp.vl_high_limit = be16_to_cpu(pi->vl.high_limit) & 0xFF;
	(व्योम)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_VL_HIGH_LIMIT,
				    ibp->rvp.vl_high_limit);

	अगर (ppd->vls_supported / 2 > ARRAY_SIZE(pi->neigh_mtu.pvlx_to_mtu) ||
	    ppd->vls_supported > ARRAY_SIZE(dd->vld)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण
	क्रम (i = 0; i < ppd->vls_supported; i++) अणु
		अगर ((i % 2) == 0)
			mtu = क्रमागत_to_mtu((pi->neigh_mtu.pvlx_to_mtu[i / 2] >>
					   4) & 0xF);
		अन्यथा
			mtu = क्रमागत_to_mtu(pi->neigh_mtu.pvlx_to_mtu[i / 2] &
					  0xF);
		अगर (mtu == 0xffff) अणु
			pr_warn("SubnSet(OPA_PortInfo) mtu invalid %d (0x%x)\n",
				mtu,
				(pi->neigh_mtu.pvlx_to_mtu[0] >> 4) & 0xF);
			smp->status |= IB_SMP_INVALID_FIELD;
			mtu = hfi1_max_mtu; /* use a valid MTU */
		पूर्ण
		अगर (dd->vld[i].mtu != mtu) अणु
			dd_dev_info(dd,
				    "MTU change on vl %d from %d to %d\n",
				    i, dd->vld[i].mtu, mtu);
			dd->vld[i].mtu = mtu;
			call_set_mtu++;
		पूर्ण
	पूर्ण
	/* As per OPAV1 spec: VL15 must support and be configured
	 * क्रम operation with a 2048 or larger MTU.
	 */
	mtu = क्रमागत_to_mtu(pi->neigh_mtu.pvlx_to_mtu[15 / 2] & 0xF);
	अगर (mtu < 2048 || mtu == 0xffff)
		mtu = 2048;
	अगर (dd->vld[15].mtu != mtu) अणु
		dd_dev_info(dd,
			    "MTU change on vl 15 from %d to %d\n",
			    dd->vld[15].mtu, mtu);
		dd->vld[15].mtu = mtu;
		call_set_mtu++;
	पूर्ण
	अगर (call_set_mtu)
		set_mtu(ppd);

	/* Set operational VLs */
	vls = pi->operational_vls & OPA_PI_MASK_OPERATIONAL_VL;
	अगर (vls) अणु
		अगर (vls > ppd->vls_supported) अणु
			pr_warn("SubnSet(OPA_PortInfo) VL's supported invalid %d\n",
				pi->operational_vls);
			smp->status |= IB_SMP_INVALID_FIELD;
		पूर्ण अन्यथा अणु
			अगर (hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_OP_VLS,
					    vls) == -EINVAL)
				smp->status |= IB_SMP_INVALID_FIELD;
		पूर्ण
	पूर्ण

	अगर (pi->mkey_violations == 0)
		ibp->rvp.mkey_violations = 0;

	अगर (pi->pkey_violations == 0)
		ibp->rvp.pkey_violations = 0;

	अगर (pi->qkey_violations == 0)
		ibp->rvp.qkey_violations = 0;

	ibp->rvp.subnet_समयout =
		pi->clientrereg_subnetसमयout & OPA_PI_MASK_SUBNET_TIMEOUT;

	crc_enabled = be16_to_cpu(pi->port_ltp_crc_mode);
	crc_enabled >>= 4;
	crc_enabled &= 0xf;

	अगर (crc_enabled != 0)
		ppd->port_crc_mode_enabled = port_ltp_to_cap(crc_enabled);

	ppd->is_active_optimize_enabled =
			!!(be16_to_cpu(pi->port_mode)
					& OPA_PI_MASK_PORT_ACTIVE_OPTOMIZE);

	ls_new = pi->port_states.portphysstate_portstate &
			OPA_PI_MASK_PORT_STATE;
	ps_new = (pi->port_states.portphysstate_portstate &
			OPA_PI_MASK_PORT_PHYSICAL_STATE) >> 4;

	अगर (ls_old == IB_PORT_INIT) अणु
		अगर (start_of_sm_config) अणु
			अगर (ls_new == ls_old || (ls_new == IB_PORT_ARMED))
				ppd->is_sm_config_started = 1;
		पूर्ण अन्यथा अगर (ls_new == IB_PORT_ARMED) अणु
			अगर (ppd->is_sm_config_started == 0) अणु
				invalid = 1;
				smp->status |= IB_SMP_INVALID_FIELD;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Handle CLIENT_REREGISTER event b/c SM asked us क्रम it */
	अगर (clientrereg) अणु
		event.event = IB_EVENT_CLIENT_REREGISTER;
		ib_dispatch_event(&event);
	पूर्ण

	/*
	 * Do the port state change now that the other link parameters
	 * have been set.
	 * Changing the port physical state only makes sense अगर the link
	 * is करोwn or is being set to करोwn.
	 */

	अगर (!invalid) अणु
		ret = set_port_states(ppd, smp, ls_new, ps_new, local_mad);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = __subn_get_opa_portinfo(smp, am, data, ibdev, port, resp_len,
				      max_len);

	/* restore re-reg bit per o14-12.2.1 */
	pi->clientrereg_subnetसमयout |= clientrereg;

	/*
	 * Apply the new link करोwngrade policy.  This may result in a link
	 * bounce.  Do this after everything अन्यथा so things are settled.
	 * Possible problem: अगर setting the port state above fails, then
	 * the policy change is not applied.
	 */
	अगर (call_link_करोwngrade_policy)
		apply_link_करोwngrade_policy(ppd, 0);

	वापस ret;

get_only:
	वापस __subn_get_opa_portinfo(smp, am, data, ibdev, port, resp_len,
				       max_len);
पूर्ण

/**
 * set_pkeys - set the PKEY table क्रम ctxt 0
 * @dd: the hfi1_ib device
 * @port: the IB port number
 * @pkeys: the PKEY table
 */
अटल पूर्णांक set_pkeys(काष्ठा hfi1_devdata *dd, u32 port, u16 *pkeys)
अणु
	काष्ठा hfi1_pportdata *ppd;
	पूर्णांक i;
	पूर्णांक changed = 0;
	पूर्णांक update_includes_mgmt_partition = 0;

	/*
	 * IB port one/two always maps to context zero/one,
	 * always a kernel context, no locking needed
	 * If we get here with ppd setup, no need to check
	 * that rcd is valid.
	 */
	ppd = dd->pport + (port - 1);
	/*
	 * If the update करोes not include the management pkey, करोn't करो it.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) अणु
		अगर (pkeys[i] == LIM_MGMT_P_KEY) अणु
			update_includes_mgmt_partition = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!update_includes_mgmt_partition)
		वापस 1;

	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) अणु
		u16 key = pkeys[i];
		u16 okey = ppd->pkeys[i];

		अगर (key == okey)
			जारी;
		/*
		 * The SM gives us the complete PKey table. We have
		 * to ensure that we put the PKeys in the matching
		 * slots.
		 */
		ppd->pkeys[i] = key;
		changed = 1;
	पूर्ण

	अगर (changed) अणु
		(व्योम)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_PKEYS, 0);
		hfi1_event_pkey_change(dd, port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __subn_set_opa_pkeytable(काष्ठा opa_smp *smp, u32 am, u8 *data,
				    काष्ठा ib_device *ibdev, u32 port,
				    u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 n_blocks_sent = OPA_AM_NBLK(am);
	u32 start_block = am & 0x7ff;
	u16 *p = (u16 *)data;
	__be16 *q = (__be16 *)data;
	पूर्णांक i;
	u16 n_blocks_avail;
	अचिन्हित npkeys = hfi1_get_npkeys(dd);
	u32 size = 0;

	अगर (n_blocks_sent == 0) अणु
		pr_warn("OPA Get PKey AM Invalid : P = %u; B = 0x%x; N = 0x%x\n",
			port, start_block, n_blocks_sent);
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	n_blocks_avail = (u16)(npkeys / OPA_PARTITION_TABLE_BLK_SIZE) + 1;

	size = माप(u16) * (n_blocks_sent * OPA_PARTITION_TABLE_BLK_SIZE);

	अगर (smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	अगर (start_block + n_blocks_sent > n_blocks_avail ||
	    n_blocks_sent > OPA_NUM_PKEY_BLOCKS_PER_SMP) अणु
		pr_warn("OPA Set PKey AM Invalid : s 0x%x; req 0x%x; avail 0x%x; blk/smp 0x%lx\n",
			start_block, n_blocks_sent, n_blocks_avail,
			OPA_NUM_PKEY_BLOCKS_PER_SMP);
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	क्रम (i = 0; i < n_blocks_sent * OPA_PARTITION_TABLE_BLK_SIZE; i++)
		p[i] = be16_to_cpu(q[i]);

	अगर (start_block == 0 && set_pkeys(dd, port, p) != 0) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	वापस __subn_get_opa_pkeytable(smp, am, data, ibdev, port, resp_len,
					max_len);
पूर्ण

#घोषणा ILLEGAL_VL 12
/*
 * filter_sc2vlt changes mappings to VL15 to ILLEGAL_VL (except
 * क्रम SC15, which must map to VL15). If we करोn't remap things this
 * way it is possible क्रम VL15 counters to increment when we try to
 * send on a SC which is mapped to an invalid VL.
 * When getting the table convert ILLEGAL_VL back to VL15.
 */
अटल व्योम filter_sc2vlt(व्योम *data, bool set)
अणु
	पूर्णांक i;
	u8 *pd = data;

	क्रम (i = 0; i < OPA_MAX_SCS; i++) अणु
		अगर (i == 15)
			जारी;

		अगर (set) अणु
			अगर ((pd[i] & 0x1f) == 0xf)
				pd[i] = ILLEGAL_VL;
		पूर्ण अन्यथा अणु
			अगर ((pd[i] & 0x1f) == ILLEGAL_VL)
				pd[i] = 0xf;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक set_sc2vlt_tables(काष्ठा hfi1_devdata *dd, व्योम *data)
अणु
	u64 *val = data;

	filter_sc2vlt(data, true);

	ग_लिखो_csr(dd, SEND_SC2VLT0, *val++);
	ग_लिखो_csr(dd, SEND_SC2VLT1, *val++);
	ग_लिखो_csr(dd, SEND_SC2VLT2, *val++);
	ग_लिखो_csr(dd, SEND_SC2VLT3, *val++);
	ग_लिखो_seqlock_irq(&dd->sc2vl_lock);
	स_नकल(dd->sc2vl, data, माप(dd->sc2vl));
	ग_लिखो_sequnlock_irq(&dd->sc2vl_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक get_sc2vlt_tables(काष्ठा hfi1_devdata *dd, व्योम *data)
अणु
	u64 *val = (u64 *)data;

	*val++ = पढ़ो_csr(dd, SEND_SC2VLT0);
	*val++ = पढ़ो_csr(dd, SEND_SC2VLT1);
	*val++ = पढ़ो_csr(dd, SEND_SC2VLT2);
	*val++ = पढ़ो_csr(dd, SEND_SC2VLT3);

	filter_sc2vlt((u64 *)data, false);
	वापस 0;
पूर्ण

अटल पूर्णांक __subn_get_opa_sl_to_sc(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	u8 *p = data;
	माप_प्रकार size = ARRAY_SIZE(ibp->sl_to_sc); /* == 32 */
	अचिन्हित i;

	अगर (am || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ibp->sl_to_sc); i++)
		*p++ = ibp->sl_to_sc[i];

	अगर (resp_len)
		*resp_len += size;

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_set_opa_sl_to_sc(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	u8 *p = data;
	माप_प्रकार size = ARRAY_SIZE(ibp->sl_to_sc);
	पूर्णांक i;
	u8 sc;

	अगर (am || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	क्रम (i = 0; i <  ARRAY_SIZE(ibp->sl_to_sc); i++) अणु
		sc = *p++;
		अगर (ibp->sl_to_sc[i] != sc) अणु
			ibp->sl_to_sc[i] = sc;

			/* Put all stale qps पूर्णांकo error state */
			hfi1_error_port_qps(ibp, i);
		पूर्ण
	पूर्ण

	वापस __subn_get_opa_sl_to_sc(smp, am, data, ibdev, port, resp_len,
				       max_len);
पूर्ण

अटल पूर्णांक __subn_get_opa_sc_to_sl(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	u8 *p = data;
	माप_प्रकार size = ARRAY_SIZE(ibp->sc_to_sl); /* == 32 */
	अचिन्हित i;

	अगर (am || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ibp->sc_to_sl); i++)
		*p++ = ibp->sc_to_sl[i];

	अगर (resp_len)
		*resp_len += size;

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_set_opa_sc_to_sl(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	माप_प्रकार size = ARRAY_SIZE(ibp->sc_to_sl);
	u8 *p = data;
	पूर्णांक i;

	अगर (am || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ibp->sc_to_sl); i++)
		ibp->sc_to_sl[i] = *p++;

	वापस __subn_get_opa_sc_to_sl(smp, am, data, ibdev, port, resp_len,
				       max_len);
पूर्ण

अटल पूर्णांक __subn_get_opa_sc_to_vlt(काष्ठा opa_smp *smp, u32 am, u8 *data,
				    काष्ठा ib_device *ibdev, u32 port,
				    u32 *resp_len, u32 max_len)
अणु
	u32 n_blocks = OPA_AM_NBLK(am);
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	व्योम *vp = (व्योम *)data;
	माप_प्रकार size = 4 * माप(u64);

	अगर (n_blocks != 1 || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	get_sc2vlt_tables(dd, vp);

	अगर (resp_len)
		*resp_len += size;

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_set_opa_sc_to_vlt(काष्ठा opa_smp *smp, u32 am, u8 *data,
				    काष्ठा ib_device *ibdev, u32 port,
				    u32 *resp_len, u32 max_len)
अणु
	u32 n_blocks = OPA_AM_NBLK(am);
	पूर्णांक async_update = OPA_AM_ASYNC(am);
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	व्योम *vp = (व्योम *)data;
	काष्ठा hfi1_pportdata *ppd;
	पूर्णांक lstate;
	/*
	 * set_sc2vlt_tables ग_लिखोs the inक्रमmation contained in *data
	 * to four 64-bit रेजिस्टरs SendSC2VLt[0-3]. We need to make
	 * sure *max_len is not greater than the total size of the four
	 * SendSC2VLt[0-3] रेजिस्टरs.
	 */
	माप_प्रकार size = 4 * माप(u64);

	अगर (n_blocks != 1 || async_update || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	/* IB numbers ports from 1, hw from 0 */
	ppd = dd->pport + (port - 1);
	lstate = driver_lstate(ppd);
	/*
	 * it's known that async_update is 0 by this poपूर्णांक, but include
	 * the explicit check क्रम clarity
	 */
	अगर (!async_update &&
	    (lstate == IB_PORT_ARMED || lstate == IB_PORT_ACTIVE)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	set_sc2vlt_tables(dd, vp);

	वापस __subn_get_opa_sc_to_vlt(smp, am, data, ibdev, port, resp_len,
					max_len);
पूर्ण

अटल पूर्णांक __subn_get_opa_sc_to_vlnt(काष्ठा opa_smp *smp, u32 am, u8 *data,
				     काष्ठा ib_device *ibdev, u32 port,
				     u32 *resp_len, u32 max_len)
अणु
	u32 n_blocks = OPA_AM_NPORT(am);
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा hfi1_pportdata *ppd;
	व्योम *vp = (व्योम *)data;
	पूर्णांक size = माप(काष्ठा sc2vlnt);

	अगर (n_blocks != 1 || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	ppd = dd->pport + (port - 1);

	fm_get_table(ppd, FM_TBL_SC2VLNT, vp);

	अगर (resp_len)
		*resp_len += size;

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_set_opa_sc_to_vlnt(काष्ठा opa_smp *smp, u32 am, u8 *data,
				     काष्ठा ib_device *ibdev, u32 port,
				     u32 *resp_len, u32 max_len)
अणु
	u32 n_blocks = OPA_AM_NPORT(am);
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा hfi1_pportdata *ppd;
	व्योम *vp = (व्योम *)data;
	पूर्णांक lstate;
	पूर्णांक size = माप(काष्ठा sc2vlnt);

	अगर (n_blocks != 1 || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	/* IB numbers ports from 1, hw from 0 */
	ppd = dd->pport + (port - 1);
	lstate = driver_lstate(ppd);
	अगर (lstate == IB_PORT_ARMED || lstate == IB_PORT_ACTIVE) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	ppd = dd->pport + (port - 1);

	fm_set_table(ppd, FM_TBL_SC2VLNT, vp);

	वापस __subn_get_opa_sc_to_vlnt(smp, am, data, ibdev, port,
					 resp_len, max_len);
पूर्ण

अटल पूर्णांक __subn_get_opa_psi(काष्ठा opa_smp *smp, u32 am, u8 *data,
			      काष्ठा ib_device *ibdev, u32 port,
			      u32 *resp_len, u32 max_len)
अणु
	u32 nports = OPA_AM_NPORT(am);
	u32 start_of_sm_config = OPA_AM_START_SM_CFG(am);
	u32 lstate;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा opa_port_state_info *psi = (काष्ठा opa_port_state_info *)data;

	अगर (nports != 1 || smp_length_check(माप(*psi), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	ibp = to_iport(ibdev, port);
	ppd = ppd_from_ibp(ibp);

	lstate = driver_lstate(ppd);

	अगर (start_of_sm_config && (lstate == IB_PORT_INIT))
		ppd->is_sm_config_started = 1;

	psi->port_states.ledenable_offlinereason = ppd->neighbor_normal << 4;
	psi->port_states.ledenable_offlinereason |=
		ppd->is_sm_config_started << 5;
	psi->port_states.ledenable_offlinereason |=
		ppd->offline_disabled_reason;

	psi->port_states.portphysstate_portstate =
		(driver_pstate(ppd) << 4) | (lstate & 0xf);
	psi->link_width_करोwngrade_tx_active =
		cpu_to_be16(ppd->link_width_करोwngrade_tx_active);
	psi->link_width_करोwngrade_rx_active =
		cpu_to_be16(ppd->link_width_करोwngrade_rx_active);
	अगर (resp_len)
		*resp_len += माप(काष्ठा opa_port_state_info);

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_set_opa_psi(काष्ठा opa_smp *smp, u32 am, u8 *data,
			      काष्ठा ib_device *ibdev, u32 port,
			      u32 *resp_len, u32 max_len, पूर्णांक local_mad)
अणु
	u32 nports = OPA_AM_NPORT(am);
	u32 start_of_sm_config = OPA_AM_START_SM_CFG(am);
	u32 ls_old;
	u8 ls_new, ps_new;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा opa_port_state_info *psi = (काष्ठा opa_port_state_info *)data;
	पूर्णांक ret, invalid = 0;

	अगर (nports != 1 || smp_length_check(माप(*psi), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	ibp = to_iport(ibdev, port);
	ppd = ppd_from_ibp(ibp);

	ls_old = driver_lstate(ppd);

	ls_new = port_states_to_logical_state(&psi->port_states);
	ps_new = port_states_to_phys_state(&psi->port_states);

	अगर (ls_old == IB_PORT_INIT) अणु
		अगर (start_of_sm_config) अणु
			अगर (ls_new == ls_old || (ls_new == IB_PORT_ARMED))
				ppd->is_sm_config_started = 1;
		पूर्ण अन्यथा अगर (ls_new == IB_PORT_ARMED) अणु
			अगर (ppd->is_sm_config_started == 0) अणु
				invalid = 1;
				smp->status |= IB_SMP_INVALID_FIELD;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!invalid) अणु
		ret = set_port_states(ppd, smp, ls_new, ps_new, local_mad);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस __subn_get_opa_psi(smp, am, data, ibdev, port, resp_len,
				  max_len);
पूर्ण

अटल पूर्णांक __subn_get_opa_cable_info(काष्ठा opa_smp *smp, u32 am, u8 *data,
				     काष्ठा ib_device *ibdev, u32 port,
				     u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 addr = OPA_AM_CI_ADDR(am);
	u32 len = OPA_AM_CI_LEN(am) + 1;
	पूर्णांक ret;

	अगर (dd->pport->port_type != PORT_TYPE_QSFP ||
	    smp_length_check(len, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

#घोषणा __CI_PAGE_SIZE BIT(7) /* 128 bytes */
#घोषणा __CI_PAGE_MASK ~(__CI_PAGE_SIZE - 1)
#घोषणा __CI_PAGE_NUM(a) ((a) & __CI_PAGE_MASK)

	/*
	 * check that addr is within spec, and
	 * addr and (addr + len - 1) are on the same "page"
	 */
	अगर (addr >= 4096 ||
	    (__CI_PAGE_NUM(addr) != __CI_PAGE_NUM(addr + len - 1))) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	ret = get_cable_info(dd, port, addr, len, data);

	अगर (ret == -ENODEV) अणु
		smp->status |= IB_SMP_UNSUP_METH_ATTR;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	/* The address range क्रम the CableInfo SMA query is wider than the
	 * memory available on the QSFP cable. We want to वापस a valid
	 * response, albeit zeroed out, क्रम address ranges beyond available
	 * memory but that are within the CableInfo query spec
	 */
	अगर (ret < 0 && ret != -दुस्फल) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	अगर (resp_len)
		*resp_len += len;

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_get_opa_bct(काष्ठा opa_smp *smp, u32 am, u8 *data,
			      काष्ठा ib_device *ibdev, u32 port, u32 *resp_len,
			      u32 max_len)
अणु
	u32 num_ports = OPA_AM_NPORT(am);
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा buffer_control *p = (काष्ठा buffer_control *)data;
	पूर्णांक size = माप(काष्ठा buffer_control);

	अगर (num_ports != 1 || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	ppd = dd->pport + (port - 1);
	fm_get_table(ppd, FM_TBL_BUFFER_CONTROL, p);
	trace_bct_get(dd, p);
	अगर (resp_len)
		*resp_len += size;

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_set_opa_bct(काष्ठा opa_smp *smp, u32 am, u8 *data,
			      काष्ठा ib_device *ibdev, u32 port, u32 *resp_len,
			      u32 max_len)
अणु
	u32 num_ports = OPA_AM_NPORT(am);
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा buffer_control *p = (काष्ठा buffer_control *)data;

	अगर (num_ports != 1 || smp_length_check(माप(*p), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण
	ppd = dd->pport + (port - 1);
	trace_bct_set(dd, p);
	अगर (fm_set_table(ppd, FM_TBL_BUFFER_CONTROL, p) < 0) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	वापस __subn_get_opa_bct(smp, am, data, ibdev, port, resp_len,
				  max_len);
पूर्ण

अटल पूर्णांक __subn_get_opa_vl_arb(काष्ठा opa_smp *smp, u32 am, u8 *data,
				 काष्ठा ib_device *ibdev, u32 port,
				 u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(to_iport(ibdev, port));
	u32 num_ports = OPA_AM_NPORT(am);
	u8 section = (am & 0x00ff0000) >> 16;
	u8 *p = data;
	पूर्णांक size = 256;

	अगर (num_ports != 1 || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	चयन (section) अणु
	हाल OPA_VLARB_LOW_ELEMENTS:
		fm_get_table(ppd, FM_TBL_VL_LOW_ARB, p);
		अवरोध;
	हाल OPA_VLARB_HIGH_ELEMENTS:
		fm_get_table(ppd, FM_TBL_VL_HIGH_ARB, p);
		अवरोध;
	हाल OPA_VLARB_PREEMPT_ELEMENTS:
		fm_get_table(ppd, FM_TBL_VL_PREEMPT_ELEMS, p);
		अवरोध;
	हाल OPA_VLARB_PREEMPT_MATRIX:
		fm_get_table(ppd, FM_TBL_VL_PREEMPT_MATRIX, p);
		अवरोध;
	शेष:
		pr_warn("OPA SubnGet(VL Arb) AM Invalid : 0x%x\n",
			be32_to_cpu(smp->attr_mod));
		smp->status |= IB_SMP_INVALID_FIELD;
		size = 0;
		अवरोध;
	पूर्ण

	अगर (size > 0 && resp_len)
		*resp_len += size;

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_set_opa_vl_arb(काष्ठा opa_smp *smp, u32 am, u8 *data,
				 काष्ठा ib_device *ibdev, u32 port,
				 u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(to_iport(ibdev, port));
	u32 num_ports = OPA_AM_NPORT(am);
	u8 section = (am & 0x00ff0000) >> 16;
	u8 *p = data;
	पूर्णांक size = 256;

	अगर (num_ports != 1 || smp_length_check(size, max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	चयन (section) अणु
	हाल OPA_VLARB_LOW_ELEMENTS:
		(व्योम)fm_set_table(ppd, FM_TBL_VL_LOW_ARB, p);
		अवरोध;
	हाल OPA_VLARB_HIGH_ELEMENTS:
		(व्योम)fm_set_table(ppd, FM_TBL_VL_HIGH_ARB, p);
		अवरोध;
	/*
	 * neither OPA_VLARB_PREEMPT_ELEMENTS, or OPA_VLARB_PREEMPT_MATRIX
	 * can be changed from the शेष values
	 */
	हाल OPA_VLARB_PREEMPT_ELEMENTS:
	हाल OPA_VLARB_PREEMPT_MATRIX:
		smp->status |= IB_SMP_UNSUP_METH_ATTR;
		अवरोध;
	शेष:
		pr_warn("OPA SubnSet(VL Arb) AM Invalid : 0x%x\n",
			be32_to_cpu(smp->attr_mod));
		smp->status |= IB_SMP_INVALID_FIELD;
		अवरोध;
	पूर्ण

	वापस __subn_get_opa_vl_arb(smp, am, data, ibdev, port, resp_len,
				     max_len);
पूर्ण

काष्ठा opa_pma_mad अणु
	काष्ठा ib_mad_hdr mad_hdr;
	u8 data[2024];
पूर्ण __packed;

काष्ठा opa_port_status_req अणु
	__u8 port_num;
	__u8 reserved[3];
	__be32 vl_select_mask;
पूर्ण;

#घोषणा VL_MASK_ALL		0x00000000000080ffUL

काष्ठा opa_port_status_rsp अणु
	__u8 port_num;
	__u8 reserved[3];
	__be32  vl_select_mask;

	/* Data counters */
	__be64 port_xmit_data;
	__be64 port_rcv_data;
	__be64 port_xmit_pkts;
	__be64 port_rcv_pkts;
	__be64 port_multicast_xmit_pkts;
	__be64 port_multicast_rcv_pkts;
	__be64 port_xmit_रुको;
	__be64 sw_port_congestion;
	__be64 port_rcv_fecn;
	__be64 port_rcv_becn;
	__be64 port_xmit_समय_cong;
	__be64 port_xmit_wasted_bw;
	__be64 port_xmit_रुको_data;
	__be64 port_rcv_bubble;
	__be64 port_mark_fecn;
	/* Error counters */
	__be64 port_rcv_स्थिरraपूर्णांक_errors;
	__be64 port_rcv_चयन_relay_errors;
	__be64 port_xmit_discards;
	__be64 port_xmit_स्थिरraपूर्णांक_errors;
	__be64 port_rcv_remote_physical_errors;
	__be64 local_link_पूर्णांकegrity_errors;
	__be64 port_rcv_errors;
	__be64 excessive_buffer_overruns;
	__be64 fm_config_errors;
	__be32 link_error_recovery;
	__be32 link_करोwned;
	u8 uncorrectable_errors;

	u8 link_quality_indicator; /* 5res, 3bit */
	u8 res2[6];
	काष्ठा _vls_pctrs अणु
		/* per-VL Data counters */
		__be64 port_vl_xmit_data;
		__be64 port_vl_rcv_data;
		__be64 port_vl_xmit_pkts;
		__be64 port_vl_rcv_pkts;
		__be64 port_vl_xmit_रुको;
		__be64 sw_port_vl_congestion;
		__be64 port_vl_rcv_fecn;
		__be64 port_vl_rcv_becn;
		__be64 port_xmit_समय_cong;
		__be64 port_vl_xmit_wasted_bw;
		__be64 port_vl_xmit_रुको_data;
		__be64 port_vl_rcv_bubble;
		__be64 port_vl_mark_fecn;
		__be64 port_vl_xmit_discards;
	पूर्ण vls[]; /* real array size defined by # bits set in vl_select_mask */
पूर्ण;

क्रमागत counter_selects अणु
	CS_PORT_XMIT_DATA			= (1 << 31),
	CS_PORT_RCV_DATA			= (1 << 30),
	CS_PORT_XMIT_PKTS			= (1 << 29),
	CS_PORT_RCV_PKTS			= (1 << 28),
	CS_PORT_MCAST_XMIT_PKTS			= (1 << 27),
	CS_PORT_MCAST_RCV_PKTS			= (1 << 26),
	CS_PORT_XMIT_WAIT			= (1 << 25),
	CS_SW_PORT_CONGESTION			= (1 << 24),
	CS_PORT_RCV_FECN			= (1 << 23),
	CS_PORT_RCV_BECN			= (1 << 22),
	CS_PORT_XMIT_TIME_CONG			= (1 << 21),
	CS_PORT_XMIT_WASTED_BW			= (1 << 20),
	CS_PORT_XMIT_WAIT_DATA			= (1 << 19),
	CS_PORT_RCV_BUBBLE			= (1 << 18),
	CS_PORT_MARK_FECN			= (1 << 17),
	CS_PORT_RCV_CONSTRAINT_ERRORS		= (1 << 16),
	CS_PORT_RCV_SWITCH_RELAY_ERRORS		= (1 << 15),
	CS_PORT_XMIT_DISCARDS			= (1 << 14),
	CS_PORT_XMIT_CONSTRAINT_ERRORS		= (1 << 13),
	CS_PORT_RCV_REMOTE_PHYSICAL_ERRORS	= (1 << 12),
	CS_LOCAL_LINK_INTEGRITY_ERRORS		= (1 << 11),
	CS_PORT_RCV_ERRORS			= (1 << 10),
	CS_EXCESSIVE_BUFFER_OVERRUNS		= (1 << 9),
	CS_FM_CONFIG_ERRORS			= (1 << 8),
	CS_LINK_ERROR_RECOVERY			= (1 << 7),
	CS_LINK_DOWNED				= (1 << 6),
	CS_UNCORRECTABLE_ERRORS			= (1 << 5),
पूर्ण;

काष्ठा opa_clear_port_status अणु
	__be64 port_select_mask[4];
	__be32 counter_select_mask;
पूर्ण;

काष्ठा opa_aggregate अणु
	__be16 attr_id;
	__be16 err_reqlength;	/* 1 bit, 8 res, 7 bit */
	__be32 attr_mod;
	u8 data[];
पूर्ण;

#घोषणा MSK_LLI 0x000000f0
#घोषणा MSK_LLI_SFT 4
#घोषणा MSK_LER 0x0000000f
#घोषणा MSK_LER_SFT 0
#घोषणा ADD_LLI 8
#घोषणा ADD_LER 2

/* Request contains first three fields, response contains those plus the rest */
काष्ठा opa_port_data_counters_msg अणु
	__be64 port_select_mask[4];
	__be32 vl_select_mask;
	__be32 resolution;

	/* Response fields follow */
	काष्ठा _port_dctrs अणु
		u8 port_number;
		u8 reserved2[3];
		__be32 link_quality_indicator; /* 29res, 3bit */

		/* Data counters */
		__be64 port_xmit_data;
		__be64 port_rcv_data;
		__be64 port_xmit_pkts;
		__be64 port_rcv_pkts;
		__be64 port_multicast_xmit_pkts;
		__be64 port_multicast_rcv_pkts;
		__be64 port_xmit_रुको;
		__be64 sw_port_congestion;
		__be64 port_rcv_fecn;
		__be64 port_rcv_becn;
		__be64 port_xmit_समय_cong;
		__be64 port_xmit_wasted_bw;
		__be64 port_xmit_रुको_data;
		__be64 port_rcv_bubble;
		__be64 port_mark_fecn;

		__be64 port_error_counter_summary;
		/* Sum of error counts/port */

		काष्ठा _vls_dctrs अणु
			/* per-VL Data counters */
			__be64 port_vl_xmit_data;
			__be64 port_vl_rcv_data;
			__be64 port_vl_xmit_pkts;
			__be64 port_vl_rcv_pkts;
			__be64 port_vl_xmit_रुको;
			__be64 sw_port_vl_congestion;
			__be64 port_vl_rcv_fecn;
			__be64 port_vl_rcv_becn;
			__be64 port_xmit_समय_cong;
			__be64 port_vl_xmit_wasted_bw;
			__be64 port_vl_xmit_रुको_data;
			__be64 port_vl_rcv_bubble;
			__be64 port_vl_mark_fecn;
		पूर्ण vls[0];
		/* array size defined by #bits set in vl_select_mask*/
	पूर्ण port[1]; /* array size defined by  #ports in attribute modअगरier */
पूर्ण;

काष्ठा opa_port_error_counters64_msg अणु
	/*
	 * Request contains first two fields, response contains the
	 * whole magilla
	 */
	__be64 port_select_mask[4];
	__be32 vl_select_mask;

	/* Response-only fields follow */
	__be32 reserved1;
	काष्ठा _port_ectrs अणु
		u8 port_number;
		u8 reserved2[7];
		__be64 port_rcv_स्थिरraपूर्णांक_errors;
		__be64 port_rcv_चयन_relay_errors;
		__be64 port_xmit_discards;
		__be64 port_xmit_स्थिरraपूर्णांक_errors;
		__be64 port_rcv_remote_physical_errors;
		__be64 local_link_पूर्णांकegrity_errors;
		__be64 port_rcv_errors;
		__be64 excessive_buffer_overruns;
		__be64 fm_config_errors;
		__be32 link_error_recovery;
		__be32 link_करोwned;
		u8 uncorrectable_errors;
		u8 reserved3[7];
		काष्ठा _vls_ectrs अणु
			__be64 port_vl_xmit_discards;
		पूर्ण vls[0];
		/* array size defined by #bits set in vl_select_mask */
	पूर्ण port[1]; /* array size defined by #ports in attribute modअगरier */
पूर्ण;

काष्ठा opa_port_error_info_msg अणु
	__be64 port_select_mask[4];
	__be32 error_info_select_mask;
	__be32 reserved1;
	काष्ठा _port_ei अणु
		u8 port_number;
		u8 reserved2[7];

		/* PortRcvErrorInfo */
		काष्ठा अणु
			u8 status_and_code;
			जोड़ अणु
				u8 raw[17];
				काष्ठा अणु
					/* EI1to12 क्रमmat */
					u8 packet_flit1[8];
					u8 packet_flit2[8];
					u8 reमुख्यing_flit_bits12;
				पूर्ण ei1to12;
				काष्ठा अणु
					u8 packet_bytes[8];
					u8 reमुख्यing_flit_bits;
				पूर्ण ei13;
			पूर्ण ei;
			u8 reserved3[6];
		पूर्ण __packed port_rcv_ei;

		/* ExcessiveBufferOverrunInfo */
		काष्ठा अणु
			u8 status_and_sc;
			u8 reserved4[7];
		पूर्ण __packed excessive_buffer_overrun_ei;

		/* PortXmitConstraपूर्णांकErrorInfo */
		काष्ठा अणु
			u8 status;
			u8 reserved5;
			__be16 pkey;
			__be32 slid;
		पूर्ण __packed port_xmit_स्थिरraपूर्णांक_ei;

		/* PortRcvConstraपूर्णांकErrorInfo */
		काष्ठा अणु
			u8 status;
			u8 reserved6;
			__be16 pkey;
			__be32 slid;
		पूर्ण __packed port_rcv_स्थिरraपूर्णांक_ei;

		/* PortRcvSwitchRelayErrorInfo */
		काष्ठा अणु
			u8 status_and_code;
			u8 reserved7[3];
			__u32 error_info;
		पूर्ण __packed port_rcv_चयन_relay_ei;

		/* UncorrectableErrorInfo */
		काष्ठा अणु
			u8 status_and_code;
			u8 reserved8;
		पूर्ण __packed uncorrectable_ei;

		/* FMConfigErrorInfo */
		काष्ठा अणु
			u8 status_and_code;
			u8 error_info;
		पूर्ण __packed fm_config_ei;
		__u32 reserved9;
	पूर्ण port[1]; /* actual array size defined by #ports in attr modअगरier */
पूर्ण;

/* opa_port_error_info_msg error_info_select_mask bit definitions */
क्रमागत error_info_selects अणु
	ES_PORT_RCV_ERROR_INFO			= (1 << 31),
	ES_EXCESSIVE_BUFFER_OVERRUN_INFO	= (1 << 30),
	ES_PORT_XMIT_CONSTRAINT_ERROR_INFO	= (1 << 29),
	ES_PORT_RCV_CONSTRAINT_ERROR_INFO	= (1 << 28),
	ES_PORT_RCV_SWITCH_RELAY_ERROR_INFO	= (1 << 27),
	ES_UNCORRECTABLE_ERROR_INFO		= (1 << 26),
	ES_FM_CONFIG_ERROR_INFO			= (1 << 25)
पूर्ण;

अटल पूर्णांक pma_get_opa_classportinfo(काष्ठा opa_pma_mad *pmp,
				     काष्ठा ib_device *ibdev, u32 *resp_len)
अणु
	काष्ठा opa_class_port_info *p =
		(काष्ठा opa_class_port_info *)pmp->data;

	स_रखो(pmp->data, 0, माप(pmp->data));

	अगर (pmp->mad_hdr.attr_mod != 0)
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;

	p->base_version = OPA_MGMT_BASE_VERSION;
	p->class_version = OPA_SM_CLASS_VERSION;
	/*
	 * Expected response समय is 4.096 usec. * 2^18 == 1.073741824 sec.
	 */
	p->cap_mask2_resp_समय = cpu_to_be32(18);

	अगर (resp_len)
		*resp_len += माप(*p);

	वापस reply((काष्ठा ib_mad_hdr *)pmp);
पूर्ण

अटल व्योम a0_portstatus(काष्ठा hfi1_pportdata *ppd,
			  काष्ठा opa_port_status_rsp *rsp)
अणु
	अगर (!is_bx(ppd->dd)) अणु
		अचिन्हित दीर्घ vl;
		u64 sum_vl_xmit_रुको = 0;
		अचिन्हित दीर्घ vl_all_mask = VL_MASK_ALL;

		क्रम_each_set_bit(vl, &vl_all_mask, BITS_PER_LONG) अणु
			u64 पंचांगp = sum_vl_xmit_रुको +
				  पढ़ो_port_cntr(ppd, C_TX_WAIT_VL,
						 idx_from_vl(vl));
			अगर (पंचांगp < sum_vl_xmit_रुको) अणु
				/* we wrapped */
				sum_vl_xmit_रुको = (u64)~0;
				अवरोध;
			पूर्ण
			sum_vl_xmit_रुको = पंचांगp;
		पूर्ण
		अगर (be64_to_cpu(rsp->port_xmit_रुको) > sum_vl_xmit_रुको)
			rsp->port_xmit_रुको = cpu_to_be64(sum_vl_xmit_रुको);
	पूर्ण
पूर्ण

/**
 * tx_link_width - convert link width biपंचांगask to पूर्णांकeger
 * value representing actual link width.
 * @link_width: width of active link
 * @वापस: वापस index of the bit set in link_width var
 *
 * The function convert and वापस the index of bit set
 * that indicate the current link width.
 */
u16 tx_link_width(u16 link_width)
अणु
	पूर्णांक n = LINK_WIDTH_DEFAULT;
	u16 tx_width = n;

	जबतक (link_width && n) अणु
		अगर (link_width & (1 << (n - 1))) अणु
			tx_width = n;
			अवरोध;
		पूर्ण
		n--;
	पूर्ण

	वापस tx_width;
पूर्ण

/**
 * get_xmit_रुको_counters - Convert HFI 's SendWaitCnt/SendWaitVlCnt
 * counter in unit of TXE cycle बार to flit बार.
 * @ppd: info of physical Hfi port
 * @link_width: width of active link
 * @link_speed: speed of active link
 * @vl: represent VL0-VL7, VL15 क्रम PortVLXmitWait counters request
 * and अगर vl value is C_VL_COUNT, it represent SendWaitCnt
 * counter request
 * @वापस: वापस SendWaitCnt/SendWaitVlCnt counter value per vl.
 *
 * Convert SendWaitCnt/SendWaitVlCnt counter from TXE cycle बार to
 * flit बार. Call this function to samples these counters. This
 * function will calculate क्रम previous state transition and update
 * current state at end of function using ppd->prev_link_width and
 * ppd->port_vl_xmit_रुको_last to port_vl_xmit_रुको_curr and link_width.
 */
u64 get_xmit_रुको_counters(काष्ठा hfi1_pportdata *ppd,
			   u16 link_width, u16 link_speed, पूर्णांक vl)
अणु
	u64 port_vl_xmit_रुको_curr;
	u64 delta_vl_xmit_रुको;
	u64 xmit_रुको_val;

	अगर (vl > C_VL_COUNT)
		वापस  0;
	अगर (vl < C_VL_COUNT)
		port_vl_xmit_रुको_curr =
			पढ़ो_port_cntr(ppd, C_TX_WAIT_VL, vl);
	अन्यथा
		port_vl_xmit_रुको_curr =
			पढ़ो_port_cntr(ppd, C_TX_WAIT, CNTR_INVALID_VL);

	xmit_रुको_val =
		port_vl_xmit_रुको_curr -
		ppd->port_vl_xmit_रुको_last[vl];
	delta_vl_xmit_रुको =
		convert_xmit_counter(xmit_रुको_val,
				     ppd->prev_link_width,
				     link_speed);

	ppd->vl_xmit_flit_cnt[vl] += delta_vl_xmit_रुको;
	ppd->port_vl_xmit_रुको_last[vl] = port_vl_xmit_रुको_curr;
	ppd->prev_link_width = link_width;

	वापस ppd->vl_xmit_flit_cnt[vl];
पूर्ण

अटल पूर्णांक pma_get_opa_portstatus(काष्ठा opa_pma_mad *pmp,
				  काष्ठा ib_device *ibdev,
				  u32 port, u32 *resp_len)
अणु
	काष्ठा opa_port_status_req *req =
		(काष्ठा opa_port_status_req *)pmp->data;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा opa_port_status_rsp *rsp;
	अचिन्हित दीर्घ vl_select_mask = be32_to_cpu(req->vl_select_mask);
	अचिन्हित दीर्घ vl;
	माप_प्रकार response_data_size;
	u32 nports = be32_to_cpu(pmp->mad_hdr.attr_mod) >> 24;
	u32 port_num = req->port_num;
	u8 num_vls = hweight64(vl_select_mask);
	काष्ठा _vls_pctrs *vlinfo;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	पूर्णांक vfi;
	u64 पंचांगp, पंचांगp2;
	u16 link_width;
	u16 link_speed;

	response_data_size = काष्ठा_size(rsp, vls, num_vls);
	अगर (response_data_size > माप(pmp->data)) अणु
		pmp->mad_hdr.status |= OPA_PM_STATUS_REQUEST_TOO_LARGE;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	अगर (nports != 1 || (port_num && port_num != port) ||
	    num_vls > OPA_MAX_VLS || (vl_select_mask & ~VL_MASK_ALL)) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	स_रखो(pmp->data, 0, माप(pmp->data));

	rsp = (काष्ठा opa_port_status_rsp *)pmp->data;
	अगर (port_num)
		rsp->port_num = port_num;
	अन्यथा
		rsp->port_num = port;

	rsp->port_rcv_स्थिरraपूर्णांक_errors =
		cpu_to_be64(पढ़ो_port_cntr(ppd, C_SW_RCV_CSTR_ERR,
					   CNTR_INVALID_VL));

	hfi1_पढ़ो_link_quality(dd, &rsp->link_quality_indicator);

	rsp->vl_select_mask = cpu_to_be32((u32)vl_select_mask);
	rsp->port_xmit_data = cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_XMIT_FLITS,
					  CNTR_INVALID_VL));
	rsp->port_rcv_data = cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_FLITS,
					 CNTR_INVALID_VL));
	rsp->port_xmit_pkts = cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_XMIT_PKTS,
					  CNTR_INVALID_VL));
	rsp->port_rcv_pkts = cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_PKTS,
					 CNTR_INVALID_VL));
	rsp->port_multicast_xmit_pkts =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_MC_XMIT_PKTS,
					  CNTR_INVALID_VL));
	rsp->port_multicast_rcv_pkts =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_MC_RCV_PKTS,
					  CNTR_INVALID_VL));
	/*
	 * Convert PortXmitWait counter from TXE cycle बार
	 * to flit बार.
	 */
	link_width =
		tx_link_width(ppd->link_width_करोwngrade_tx_active);
	link_speed = get_link_speed(ppd->link_speed_active);
	rsp->port_xmit_रुको =
		cpu_to_be64(get_xmit_रुको_counters(ppd, link_width,
						   link_speed, C_VL_COUNT));
	rsp->port_rcv_fecn =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_FCN, CNTR_INVALID_VL));
	rsp->port_rcv_becn =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_BCN, CNTR_INVALID_VL));
	rsp->port_xmit_discards =
		cpu_to_be64(पढ़ो_port_cntr(ppd, C_SW_XMIT_DSCD,
					   CNTR_INVALID_VL));
	rsp->port_xmit_स्थिरraपूर्णांक_errors =
		cpu_to_be64(पढ़ो_port_cntr(ppd, C_SW_XMIT_CSTR_ERR,
					   CNTR_INVALID_VL));
	rsp->port_rcv_remote_physical_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RMT_PHY_ERR,
					  CNTR_INVALID_VL));
	rsp->local_link_पूर्णांकegrity_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RX_REPLAY,
					  CNTR_INVALID_VL));
	पंचांगp = पढ़ो_dev_cntr(dd, C_DC_SEQ_CRC_CNT, CNTR_INVALID_VL);
	पंचांगp2 = पंचांगp + पढ़ो_dev_cntr(dd, C_DC_REINIT_FROM_PEER_CNT,
				   CNTR_INVALID_VL);
	अगर (पंचांगp2 > (u32)अच_पूर्णांक_उच्च || पंचांगp2 < पंचांगp) अणु
		/* overflow/wrapped */
		rsp->link_error_recovery = cpu_to_be32(~0);
	पूर्ण अन्यथा अणु
		rsp->link_error_recovery = cpu_to_be32(पंचांगp2);
	पूर्ण
	rsp->port_rcv_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_ERR, CNTR_INVALID_VL));
	rsp->excessive_buffer_overruns =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_RCV_OVF, CNTR_INVALID_VL));
	rsp->fm_config_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_FM_CFG_ERR,
					  CNTR_INVALID_VL));
	rsp->link_करोwned = cpu_to_be32(पढ़ो_port_cntr(ppd, C_SW_LINK_DOWN,
						      CNTR_INVALID_VL));

	/* rsp->uncorrectable_errors is 8 bits wide, and it pegs at 0xff */
	पंचांगp = पढ़ो_dev_cntr(dd, C_DC_UNC_ERR, CNTR_INVALID_VL);
	rsp->uncorrectable_errors = पंचांगp < 0x100 ? (पंचांगp & 0xff) : 0xff;

	vlinfo = &rsp->vls[0];
	vfi = 0;
	/* The vl_select_mask has been checked above, and we know
	 * that it contains only entries which represent valid VLs.
	 * So in the क्रम_each_set_bit() loop below, we करोn't need
	 * any additional checks क्रम vl.
	 */
	क्रम_each_set_bit(vl, &vl_select_mask, BITS_PER_LONG) अणु
		स_रखो(vlinfo, 0, माप(*vlinfo));

		पंचांगp = पढ़ो_dev_cntr(dd, C_DC_RX_FLIT_VL, idx_from_vl(vl));
		rsp->vls[vfi].port_vl_rcv_data = cpu_to_be64(पंचांगp);

		rsp->vls[vfi].port_vl_rcv_pkts =
			cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RX_PKT_VL,
						  idx_from_vl(vl)));

		rsp->vls[vfi].port_vl_xmit_data =
			cpu_to_be64(पढ़ो_port_cntr(ppd, C_TX_FLIT_VL,
						   idx_from_vl(vl)));

		rsp->vls[vfi].port_vl_xmit_pkts =
			cpu_to_be64(पढ़ो_port_cntr(ppd, C_TX_PKT_VL,
						   idx_from_vl(vl)));
		/*
		 * Convert PortVlXmitWait counter from TXE cycle
		 * बार to flit बार.
		 */
		rsp->vls[vfi].port_vl_xmit_रुको =
			cpu_to_be64(get_xmit_रुको_counters(ppd, link_width,
							   link_speed,
							   idx_from_vl(vl)));

		rsp->vls[vfi].port_vl_rcv_fecn =
			cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_FCN_VL,
						  idx_from_vl(vl)));

		rsp->vls[vfi].port_vl_rcv_becn =
			cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_BCN_VL,
						  idx_from_vl(vl)));

		rsp->vls[vfi].port_vl_xmit_discards =
			cpu_to_be64(पढ़ो_port_cntr(ppd, C_SW_XMIT_DSCD_VL,
						   idx_from_vl(vl)));
		vlinfo++;
		vfi++;
	पूर्ण

	a0_portstatus(ppd, rsp);

	अगर (resp_len)
		*resp_len += response_data_size;

	वापस reply((काष्ठा ib_mad_hdr *)pmp);
पूर्ण

अटल u64 get_error_counter_summary(काष्ठा ib_device *ibdev, u32 port,
				     u8 res_lli, u8 res_ler)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u64 error_counter_summary = 0, पंचांगp;

	error_counter_summary += पढ़ो_port_cntr(ppd, C_SW_RCV_CSTR_ERR,
						CNTR_INVALID_VL);
	/* port_rcv_चयन_relay_errors is 0 क्रम HFIs */
	error_counter_summary += पढ़ो_port_cntr(ppd, C_SW_XMIT_DSCD,
						CNTR_INVALID_VL);
	error_counter_summary += पढ़ो_port_cntr(ppd, C_SW_XMIT_CSTR_ERR,
						CNTR_INVALID_VL);
	error_counter_summary += पढ़ो_dev_cntr(dd, C_DC_RMT_PHY_ERR,
					       CNTR_INVALID_VL);
	/* local link पूर्णांकegrity must be right-shअगरted by the lli resolution */
	error_counter_summary += (पढ़ो_dev_cntr(dd, C_DC_RX_REPLAY,
						CNTR_INVALID_VL) >> res_lli);
	/* link error recovery must b right-shअगरted by the ler resolution */
	पंचांगp = पढ़ो_dev_cntr(dd, C_DC_SEQ_CRC_CNT, CNTR_INVALID_VL);
	पंचांगp += पढ़ो_dev_cntr(dd, C_DC_REINIT_FROM_PEER_CNT, CNTR_INVALID_VL);
	error_counter_summary += (पंचांगp >> res_ler);
	error_counter_summary += पढ़ो_dev_cntr(dd, C_DC_RCV_ERR,
					       CNTR_INVALID_VL);
	error_counter_summary += पढ़ो_dev_cntr(dd, C_RCV_OVF, CNTR_INVALID_VL);
	error_counter_summary += पढ़ो_dev_cntr(dd, C_DC_FM_CFG_ERR,
					       CNTR_INVALID_VL);
	/* ppd->link_करोwned is a 32-bit value */
	error_counter_summary += पढ़ो_port_cntr(ppd, C_SW_LINK_DOWN,
						CNTR_INVALID_VL);
	पंचांगp = पढ़ो_dev_cntr(dd, C_DC_UNC_ERR, CNTR_INVALID_VL);
	/* this is an 8-bit quantity */
	error_counter_summary += पंचांगp < 0x100 ? (पंचांगp & 0xff) : 0xff;

	वापस error_counter_summary;
पूर्ण

अटल व्योम a0_datacounters(काष्ठा hfi1_pportdata *ppd, काष्ठा _port_dctrs *rsp)
अणु
	अगर (!is_bx(ppd->dd)) अणु
		अचिन्हित दीर्घ vl;
		u64 sum_vl_xmit_रुको = 0;
		अचिन्हित दीर्घ vl_all_mask = VL_MASK_ALL;

		क्रम_each_set_bit(vl, &vl_all_mask, BITS_PER_LONG) अणु
			u64 पंचांगp = sum_vl_xmit_रुको +
				  पढ़ो_port_cntr(ppd, C_TX_WAIT_VL,
						 idx_from_vl(vl));
			अगर (पंचांगp < sum_vl_xmit_रुको) अणु
				/* we wrapped */
				sum_vl_xmit_रुको = (u64)~0;
				अवरोध;
			पूर्ण
			sum_vl_xmit_रुको = पंचांगp;
		पूर्ण
		अगर (be64_to_cpu(rsp->port_xmit_रुको) > sum_vl_xmit_रुको)
			rsp->port_xmit_रुको = cpu_to_be64(sum_vl_xmit_रुको);
	पूर्ण
पूर्ण

अटल व्योम pma_get_opa_port_dctrs(काष्ठा ib_device *ibdev,
				   काष्ठा _port_dctrs *rsp)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);

	rsp->port_xmit_data = cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_XMIT_FLITS,
						CNTR_INVALID_VL));
	rsp->port_rcv_data = cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_FLITS,
						CNTR_INVALID_VL));
	rsp->port_xmit_pkts = cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_XMIT_PKTS,
						CNTR_INVALID_VL));
	rsp->port_rcv_pkts = cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_PKTS,
						CNTR_INVALID_VL));
	rsp->port_multicast_xmit_pkts =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_MC_XMIT_PKTS,
					  CNTR_INVALID_VL));
	rsp->port_multicast_rcv_pkts =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_MC_RCV_PKTS,
					  CNTR_INVALID_VL));
पूर्ण

अटल पूर्णांक pma_get_opa_datacounters(काष्ठा opa_pma_mad *pmp,
				    काष्ठा ib_device *ibdev,
				    u32 port, u32 *resp_len)
अणु
	काष्ठा opa_port_data_counters_msg *req =
		(काष्ठा opa_port_data_counters_msg *)pmp->data;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा _port_dctrs *rsp;
	काष्ठा _vls_dctrs *vlinfo;
	माप_प्रकार response_data_size;
	u32 num_ports;
	u8 lq, num_vls;
	u8 res_lli, res_ler;
	u64 port_mask;
	u32 port_num;
	अचिन्हित दीर्घ vl;
	अचिन्हित दीर्घ vl_select_mask;
	पूर्णांक vfi;
	u16 link_width;
	u16 link_speed;

	num_ports = be32_to_cpu(pmp->mad_hdr.attr_mod) >> 24;
	num_vls = hweight32(be32_to_cpu(req->vl_select_mask));
	vl_select_mask = be32_to_cpu(req->vl_select_mask);
	res_lli = (u8)(be32_to_cpu(req->resolution) & MSK_LLI) >> MSK_LLI_SFT;
	res_lli = res_lli ? res_lli + ADD_LLI : 0;
	res_ler = (u8)(be32_to_cpu(req->resolution) & MSK_LER) >> MSK_LER_SFT;
	res_ler = res_ler ? res_ler + ADD_LER : 0;

	अगर (num_ports != 1 || (vl_select_mask & ~VL_MASK_ALL)) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	/* Sanity check */
	response_data_size = काष्ठा_size(req, port[0].vls, num_vls);

	अगर (response_data_size > माप(pmp->data)) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	/*
	 * The bit set in the mask needs to be consistent with the
	 * port the request came in on.
	 */
	port_mask = be64_to_cpu(req->port_select_mask[3]);
	port_num = find_first_bit((अचिन्हित दीर्घ *)&port_mask,
				  माप(port_mask) * 8);

	अगर (port_num != port) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	rsp = &req->port[0];
	स_रखो(rsp, 0, माप(*rsp));

	rsp->port_number = port;
	/*
	 * Note that link_quality_indicator is a 32 bit quantity in
	 * 'datacounters' queries (as opposed to 'portinfo' queries,
	 * where it's a byte).
	 */
	hfi1_पढ़ो_link_quality(dd, &lq);
	rsp->link_quality_indicator = cpu_to_be32((u32)lq);
	pma_get_opa_port_dctrs(ibdev, rsp);

	/*
	 * Convert PortXmitWait counter from TXE
	 * cycle बार to flit बार.
	 */
	link_width =
		tx_link_width(ppd->link_width_करोwngrade_tx_active);
	link_speed = get_link_speed(ppd->link_speed_active);
	rsp->port_xmit_रुको =
		cpu_to_be64(get_xmit_रुको_counters(ppd, link_width,
						   link_speed, C_VL_COUNT));
	rsp->port_rcv_fecn =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_FCN, CNTR_INVALID_VL));
	rsp->port_rcv_becn =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_BCN, CNTR_INVALID_VL));
	rsp->port_error_counter_summary =
		cpu_to_be64(get_error_counter_summary(ibdev, port,
						      res_lli, res_ler));

	vlinfo = &rsp->vls[0];
	vfi = 0;
	/* The vl_select_mask has been checked above, and we know
	 * that it contains only entries which represent valid VLs.
	 * So in the क्रम_each_set_bit() loop below, we करोn't need
	 * any additional checks क्रम vl.
	 */
	क्रम_each_set_bit(vl, &vl_select_mask, BITS_PER_LONG) अणु
		स_रखो(vlinfo, 0, माप(*vlinfo));

		rsp->vls[vfi].port_vl_xmit_data =
			cpu_to_be64(पढ़ो_port_cntr(ppd, C_TX_FLIT_VL,
						   idx_from_vl(vl)));

		rsp->vls[vfi].port_vl_rcv_data =
			cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RX_FLIT_VL,
						  idx_from_vl(vl)));

		rsp->vls[vfi].port_vl_xmit_pkts =
			cpu_to_be64(पढ़ो_port_cntr(ppd, C_TX_PKT_VL,
						   idx_from_vl(vl)));

		rsp->vls[vfi].port_vl_rcv_pkts =
			cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RX_PKT_VL,
						  idx_from_vl(vl)));

		/*
		 * Convert PortVlXmitWait counter from TXE
		 * cycle बार to flit बार.
		 */
		rsp->vls[vfi].port_vl_xmit_रुको =
			cpu_to_be64(get_xmit_रुको_counters(ppd, link_width,
							   link_speed,
							   idx_from_vl(vl)));

		rsp->vls[vfi].port_vl_rcv_fecn =
			cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_FCN_VL,
						  idx_from_vl(vl)));
		rsp->vls[vfi].port_vl_rcv_becn =
			cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_BCN_VL,
						  idx_from_vl(vl)));

		/* rsp->port_vl_xmit_समय_cong is 0 क्रम HFIs */
		/* rsp->port_vl_xmit_wasted_bw ??? */
		/* port_vl_xmit_रुको_data - TXE (table 13-9 HFI spec) ???
		 * करोes this dअगरfer from rsp->vls[vfi].port_vl_xmit_रुको
		 */
		/*rsp->vls[vfi].port_vl_mark_fecn =
		 *	cpu_to_be64(पढ़ो_csr(dd, DCC_PRF_PORT_VL_MARK_FECN_CNT
		 *		+ offset));
		 */
		vlinfo++;
		vfi++;
	पूर्ण

	a0_datacounters(ppd, rsp);

	अगर (resp_len)
		*resp_len += response_data_size;

	वापस reply((काष्ठा ib_mad_hdr *)pmp);
पूर्ण

अटल पूर्णांक pma_get_ib_portcounters_ext(काष्ठा ib_pma_mad *pmp,
				       काष्ठा ib_device *ibdev, u32 port)
अणु
	काष्ठा ib_pma_portcounters_ext *p = (काष्ठा ib_pma_portcounters_ext *)
						pmp->data;
	काष्ठा _port_dctrs rsp;

	अगर (pmp->mad_hdr.attr_mod != 0 || p->port_select != port) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		जाओ bail;
	पूर्ण

	स_रखो(&rsp, 0, माप(rsp));
	pma_get_opa_port_dctrs(ibdev, &rsp);

	p->port_xmit_data = rsp.port_xmit_data;
	p->port_rcv_data = rsp.port_rcv_data;
	p->port_xmit_packets = rsp.port_xmit_pkts;
	p->port_rcv_packets = rsp.port_rcv_pkts;
	p->port_unicast_xmit_packets = 0;
	p->port_unicast_rcv_packets =  0;
	p->port_multicast_xmit_packets = rsp.port_multicast_xmit_pkts;
	p->port_multicast_rcv_packets = rsp.port_multicast_rcv_pkts;

bail:
	वापस reply((काष्ठा ib_mad_hdr *)pmp);
पूर्ण

अटल व्योम pma_get_opa_port_ectrs(काष्ठा ib_device *ibdev,
				   काष्ठा _port_ectrs *rsp, u32 port)
अणु
	u64 पंचांगp, पंचांगp2;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	पंचांगp = पढ़ो_dev_cntr(dd, C_DC_SEQ_CRC_CNT, CNTR_INVALID_VL);
	पंचांगp2 = पंचांगp + पढ़ो_dev_cntr(dd, C_DC_REINIT_FROM_PEER_CNT,
					CNTR_INVALID_VL);
	अगर (पंचांगp2 > (u32)अच_पूर्णांक_उच्च || पंचांगp2 < पंचांगp) अणु
		/* overflow/wrapped */
		rsp->link_error_recovery = cpu_to_be32(~0);
	पूर्ण अन्यथा अणु
		rsp->link_error_recovery = cpu_to_be32(पंचांगp2);
	पूर्ण

	rsp->link_करोwned = cpu_to_be32(पढ़ो_port_cntr(ppd, C_SW_LINK_DOWN,
						CNTR_INVALID_VL));
	rsp->port_rcv_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_ERR, CNTR_INVALID_VL));
	rsp->port_rcv_remote_physical_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RMT_PHY_ERR,
					  CNTR_INVALID_VL));
	rsp->port_rcv_चयन_relay_errors = 0;
	rsp->port_xmit_discards =
		cpu_to_be64(पढ़ो_port_cntr(ppd, C_SW_XMIT_DSCD,
					   CNTR_INVALID_VL));
	rsp->port_xmit_स्थिरraपूर्णांक_errors =
		cpu_to_be64(पढ़ो_port_cntr(ppd, C_SW_XMIT_CSTR_ERR,
					   CNTR_INVALID_VL));
	rsp->port_rcv_स्थिरraपूर्णांक_errors =
		cpu_to_be64(पढ़ो_port_cntr(ppd, C_SW_RCV_CSTR_ERR,
					   CNTR_INVALID_VL));
	rsp->local_link_पूर्णांकegrity_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RX_REPLAY,
					  CNTR_INVALID_VL));
	rsp->excessive_buffer_overruns =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_RCV_OVF, CNTR_INVALID_VL));
पूर्ण

अटल पूर्णांक pma_get_opa_porterrors(काष्ठा opa_pma_mad *pmp,
				  काष्ठा ib_device *ibdev,
				  u32 port, u32 *resp_len)
अणु
	माप_प्रकार response_data_size;
	काष्ठा _port_ectrs *rsp;
	u32 port_num;
	काष्ठा opa_port_error_counters64_msg *req;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 num_ports;
	u8 num_pslm;
	u8 num_vls;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा _vls_ectrs *vlinfo;
	अचिन्हित दीर्घ vl;
	u64 port_mask, पंचांगp;
	अचिन्हित दीर्घ vl_select_mask;
	पूर्णांक vfi;

	req = (काष्ठा opa_port_error_counters64_msg *)pmp->data;

	num_ports = be32_to_cpu(pmp->mad_hdr.attr_mod) >> 24;

	num_pslm = hweight64(be64_to_cpu(req->port_select_mask[3]));
	num_vls = hweight32(be32_to_cpu(req->vl_select_mask));

	अगर (num_ports != 1 || num_ports != num_pslm) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	response_data_size = काष्ठा_size(req, port[0].vls, num_vls);

	अगर (response_data_size > माप(pmp->data)) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण
	/*
	 * The bit set in the mask needs to be consistent with the
	 * port the request came in on.
	 */
	port_mask = be64_to_cpu(req->port_select_mask[3]);
	port_num = find_first_bit((अचिन्हित दीर्घ *)&port_mask,
				  माप(port_mask) * 8);

	अगर (port_num != port) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	rsp = &req->port[0];

	ibp = to_iport(ibdev, port_num);
	ppd = ppd_from_ibp(ibp);

	स_रखो(rsp, 0, माप(*rsp));
	rsp->port_number = port_num;

	pma_get_opa_port_ectrs(ibdev, rsp, port_num);

	rsp->port_rcv_remote_physical_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RMT_PHY_ERR,
					  CNTR_INVALID_VL));
	rsp->fm_config_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_FM_CFG_ERR,
					  CNTR_INVALID_VL));
	पंचांगp = पढ़ो_dev_cntr(dd, C_DC_UNC_ERR, CNTR_INVALID_VL);

	rsp->uncorrectable_errors = पंचांगp < 0x100 ? (पंचांगp & 0xff) : 0xff;
	rsp->port_rcv_errors =
		cpu_to_be64(पढ़ो_dev_cntr(dd, C_DC_RCV_ERR, CNTR_INVALID_VL));
	vlinfo = &rsp->vls[0];
	vfi = 0;
	vl_select_mask = be32_to_cpu(req->vl_select_mask);
	क्रम_each_set_bit(vl, &vl_select_mask, BITS_PER_LONG) अणु
		स_रखो(vlinfo, 0, माप(*vlinfo));
		rsp->vls[vfi].port_vl_xmit_discards =
			cpu_to_be64(पढ़ो_port_cntr(ppd, C_SW_XMIT_DSCD_VL,
						   idx_from_vl(vl)));
		vlinfo += 1;
		vfi++;
	पूर्ण

	अगर (resp_len)
		*resp_len += response_data_size;

	वापस reply((काष्ठा ib_mad_hdr *)pmp);
पूर्ण

अटल पूर्णांक pma_get_ib_portcounters(काष्ठा ib_pma_mad *pmp,
				   काष्ठा ib_device *ibdev, u32 port)
अणु
	काष्ठा ib_pma_portcounters *p = (काष्ठा ib_pma_portcounters *)
		pmp->data;
	काष्ठा _port_ectrs rsp;
	u64 temp_link_overrun_errors;
	u64 temp_64;
	u32 temp_32;

	स_रखो(&rsp, 0, माप(rsp));
	pma_get_opa_port_ectrs(ibdev, &rsp, port);

	अगर (pmp->mad_hdr.attr_mod != 0 || p->port_select != port) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		जाओ bail;
	पूर्ण

	p->symbol_error_counter = 0; /* N/A क्रम OPA */

	temp_32 = be32_to_cpu(rsp.link_error_recovery);
	अगर (temp_32 > 0xFFUL)
		p->link_error_recovery_counter = 0xFF;
	अन्यथा
		p->link_error_recovery_counter = (u8)temp_32;

	temp_32 = be32_to_cpu(rsp.link_करोwned);
	अगर (temp_32 > 0xFFUL)
		p->link_करोwned_counter = 0xFF;
	अन्यथा
		p->link_करोwned_counter = (u8)temp_32;

	temp_64 = be64_to_cpu(rsp.port_rcv_errors);
	अगर (temp_64 > 0xFFFFUL)
		p->port_rcv_errors = cpu_to_be16(0xFFFF);
	अन्यथा
		p->port_rcv_errors = cpu_to_be16((u16)temp_64);

	temp_64 = be64_to_cpu(rsp.port_rcv_remote_physical_errors);
	अगर (temp_64 > 0xFFFFUL)
		p->port_rcv_remphys_errors = cpu_to_be16(0xFFFF);
	अन्यथा
		p->port_rcv_remphys_errors = cpu_to_be16((u16)temp_64);

	temp_64 = be64_to_cpu(rsp.port_rcv_चयन_relay_errors);
	p->port_rcv_चयन_relay_errors = cpu_to_be16((u16)temp_64);

	temp_64 = be64_to_cpu(rsp.port_xmit_discards);
	अगर (temp_64 > 0xFFFFUL)
		p->port_xmit_discards = cpu_to_be16(0xFFFF);
	अन्यथा
		p->port_xmit_discards = cpu_to_be16((u16)temp_64);

	temp_64 = be64_to_cpu(rsp.port_xmit_स्थिरraपूर्णांक_errors);
	अगर (temp_64 > 0xFFUL)
		p->port_xmit_स्थिरraपूर्णांक_errors = 0xFF;
	अन्यथा
		p->port_xmit_स्थिरraपूर्णांक_errors = (u8)temp_64;

	temp_64 = be64_to_cpu(rsp.port_rcv_स्थिरraपूर्णांक_errors);
	अगर (temp_64 > 0xFFUL)
		p->port_rcv_स्थिरraपूर्णांक_errors = 0xFFUL;
	अन्यथा
		p->port_rcv_स्थिरraपूर्णांक_errors = (u8)temp_64;

	/* LocalLink: 7:4, BufferOverrun: 3:0 */
	temp_64 = be64_to_cpu(rsp.local_link_पूर्णांकegrity_errors);
	अगर (temp_64 > 0xFUL)
		temp_64 = 0xFUL;

	temp_link_overrun_errors = temp_64 << 4;

	temp_64 = be64_to_cpu(rsp.excessive_buffer_overruns);
	अगर (temp_64 > 0xFUL)
		temp_64 = 0xFUL;
	temp_link_overrun_errors |= temp_64;

	p->link_overrun_errors = (u8)temp_link_overrun_errors;

	p->vl15_dropped = 0; /* N/A क्रम OPA */

bail:
	वापस reply((काष्ठा ib_mad_hdr *)pmp);
पूर्ण

अटल पूर्णांक pma_get_opa_errorinfo(काष्ठा opa_pma_mad *pmp,
				 काष्ठा ib_device *ibdev,
				 u32 port, u32 *resp_len)
अणु
	माप_प्रकार response_data_size;
	काष्ठा _port_ei *rsp;
	काष्ठा opa_port_error_info_msg *req;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u64 port_mask;
	u32 num_ports;
	u32 port_num;
	u8 num_pslm;
	u64 reg;

	req = (काष्ठा opa_port_error_info_msg *)pmp->data;
	rsp = &req->port[0];

	num_ports = OPA_AM_NPORT(be32_to_cpu(pmp->mad_hdr.attr_mod));
	num_pslm = hweight64(be64_to_cpu(req->port_select_mask[3]));

	स_रखो(rsp, 0, माप(*rsp));

	अगर (num_ports != 1 || num_ports != num_pslm) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	/* Sanity check */
	response_data_size = माप(काष्ठा opa_port_error_info_msg);

	अगर (response_data_size > माप(pmp->data)) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	/*
	 * The bit set in the mask needs to be consistent with the port
	 * the request came in on.
	 */
	port_mask = be64_to_cpu(req->port_select_mask[3]);
	port_num = find_first_bit((अचिन्हित दीर्घ *)&port_mask,
				  माप(port_mask) * 8);

	अगर (port_num != port) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण
	rsp->port_number = port;

	/* PortRcvErrorInfo */
	rsp->port_rcv_ei.status_and_code =
		dd->err_info_rcvport.status_and_code;
	स_नकल(&rsp->port_rcv_ei.ei.ei1to12.packet_flit1,
	       &dd->err_info_rcvport.packet_flit1, माप(u64));
	स_नकल(&rsp->port_rcv_ei.ei.ei1to12.packet_flit2,
	       &dd->err_info_rcvport.packet_flit2, माप(u64));

	/* ExcessiverBufferOverrunInfo */
	reg = पढ़ो_csr(dd, RCV_ERR_INFO);
	अगर (reg & RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SMASK) अणु
		/*
		 * अगर the RcvExcessBufferOverrun bit is set, save SC of
		 * first pkt that encountered an excess buffer overrun
		 */
		u8 पंचांगp = (u8)reg;

		पंचांगp &=  RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SC_SMASK;
		पंचांगp <<= 2;
		rsp->excessive_buffer_overrun_ei.status_and_sc = पंचांगp;
		/* set the status bit */
		rsp->excessive_buffer_overrun_ei.status_and_sc |= 0x80;
	पूर्ण

	rsp->port_xmit_स्थिरraपूर्णांक_ei.status =
		dd->err_info_xmit_स्थिरraपूर्णांक.status;
	rsp->port_xmit_स्थिरraपूर्णांक_ei.pkey =
		cpu_to_be16(dd->err_info_xmit_स्थिरraपूर्णांक.pkey);
	rsp->port_xmit_स्थिरraपूर्णांक_ei.slid =
		cpu_to_be32(dd->err_info_xmit_स्थिरraपूर्णांक.slid);

	rsp->port_rcv_स्थिरraपूर्णांक_ei.status =
		dd->err_info_rcv_स्थिरraपूर्णांक.status;
	rsp->port_rcv_स्थिरraपूर्णांक_ei.pkey =
		cpu_to_be16(dd->err_info_rcv_स्थिरraपूर्णांक.pkey);
	rsp->port_rcv_स्थिरraपूर्णांक_ei.slid =
		cpu_to_be32(dd->err_info_rcv_स्थिरraपूर्णांक.slid);

	/* UncorrectableErrorInfo */
	rsp->uncorrectable_ei.status_and_code = dd->err_info_uncorrectable;

	/* FMConfigErrorInfo */
	rsp->fm_config_ei.status_and_code = dd->err_info_fmconfig;

	अगर (resp_len)
		*resp_len += response_data_size;

	वापस reply((काष्ठा ib_mad_hdr *)pmp);
पूर्ण

अटल पूर्णांक pma_set_opa_portstatus(काष्ठा opa_pma_mad *pmp,
				  काष्ठा ib_device *ibdev,
				  u32 port, u32 *resp_len)
अणु
	काष्ठा opa_clear_port_status *req =
		(काष्ठा opa_clear_port_status *)pmp->data;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 nports = be32_to_cpu(pmp->mad_hdr.attr_mod) >> 24;
	u64 portn = be64_to_cpu(req->port_select_mask[3]);
	u32 counter_select = be32_to_cpu(req->counter_select_mask);
	अचिन्हित दीर्घ vl_select_mask = VL_MASK_ALL; /* clear all per-vl cnts */
	अचिन्हित दीर्घ vl;

	अगर ((nports != 1) || (portn != 1 << port)) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण
	/*
	 * only counters वापसed by pma_get_opa_portstatus() are
	 * handled, so when pma_get_opa_portstatus() माला_लो a fix,
	 * the corresponding change should be made here as well.
	 */

	अगर (counter_select & CS_PORT_XMIT_DATA)
		ग_लिखो_dev_cntr(dd, C_DC_XMIT_FLITS, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_PORT_RCV_DATA)
		ग_लिखो_dev_cntr(dd, C_DC_RCV_FLITS, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_PORT_XMIT_PKTS)
		ग_लिखो_dev_cntr(dd, C_DC_XMIT_PKTS, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_PORT_RCV_PKTS)
		ग_लिखो_dev_cntr(dd, C_DC_RCV_PKTS, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_PORT_MCAST_XMIT_PKTS)
		ग_लिखो_dev_cntr(dd, C_DC_MC_XMIT_PKTS, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_PORT_MCAST_RCV_PKTS)
		ग_लिखो_dev_cntr(dd, C_DC_MC_RCV_PKTS, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_PORT_XMIT_WAIT) अणु
		ग_लिखो_port_cntr(ppd, C_TX_WAIT, CNTR_INVALID_VL, 0);
		ppd->port_vl_xmit_रुको_last[C_VL_COUNT] = 0;
		ppd->vl_xmit_flit_cnt[C_VL_COUNT] = 0;
	पूर्ण
	/* ignore cs_sw_portCongestion क्रम HFIs */

	अगर (counter_select & CS_PORT_RCV_FECN)
		ग_लिखो_dev_cntr(dd, C_DC_RCV_FCN, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_PORT_RCV_BECN)
		ग_लिखो_dev_cntr(dd, C_DC_RCV_BCN, CNTR_INVALID_VL, 0);

	/* ignore cs_port_xmit_समय_cong क्रम HFIs */
	/* ignore cs_port_xmit_wasted_bw क्रम now */
	/* ignore cs_port_xmit_रुको_data क्रम now */
	अगर (counter_select & CS_PORT_RCV_BUBBLE)
		ग_लिखो_dev_cntr(dd, C_DC_RCV_BBL, CNTR_INVALID_VL, 0);

	/* Only applicable क्रम चयन */
	/* अगर (counter_select & CS_PORT_MARK_FECN)
	 *	ग_लिखो_csr(dd, DCC_PRF_PORT_MARK_FECN_CNT, 0);
	 */

	अगर (counter_select & CS_PORT_RCV_CONSTRAINT_ERRORS)
		ग_लिखो_port_cntr(ppd, C_SW_RCV_CSTR_ERR, CNTR_INVALID_VL, 0);

	/* ignore cs_port_rcv_चयन_relay_errors क्रम HFIs */
	अगर (counter_select & CS_PORT_XMIT_DISCARDS)
		ग_लिखो_port_cntr(ppd, C_SW_XMIT_DSCD, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_PORT_XMIT_CONSTRAINT_ERRORS)
		ग_लिखो_port_cntr(ppd, C_SW_XMIT_CSTR_ERR, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_PORT_RCV_REMOTE_PHYSICAL_ERRORS)
		ग_लिखो_dev_cntr(dd, C_DC_RMT_PHY_ERR, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_LOCAL_LINK_INTEGRITY_ERRORS)
		ग_लिखो_dev_cntr(dd, C_DC_RX_REPLAY, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_LINK_ERROR_RECOVERY) अणु
		ग_लिखो_dev_cntr(dd, C_DC_SEQ_CRC_CNT, CNTR_INVALID_VL, 0);
		ग_लिखो_dev_cntr(dd, C_DC_REINIT_FROM_PEER_CNT,
			       CNTR_INVALID_VL, 0);
	पूर्ण

	अगर (counter_select & CS_PORT_RCV_ERRORS)
		ग_लिखो_dev_cntr(dd, C_DC_RCV_ERR, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_EXCESSIVE_BUFFER_OVERRUNS) अणु
		ग_लिखो_dev_cntr(dd, C_RCV_OVF, CNTR_INVALID_VL, 0);
		dd->rcv_ovfl_cnt = 0;
	पूर्ण

	अगर (counter_select & CS_FM_CONFIG_ERRORS)
		ग_लिखो_dev_cntr(dd, C_DC_FM_CFG_ERR, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_LINK_DOWNED)
		ग_लिखो_port_cntr(ppd, C_SW_LINK_DOWN, CNTR_INVALID_VL, 0);

	अगर (counter_select & CS_UNCORRECTABLE_ERRORS)
		ग_लिखो_dev_cntr(dd, C_DC_UNC_ERR, CNTR_INVALID_VL, 0);

	क्रम_each_set_bit(vl, &vl_select_mask, BITS_PER_LONG) अणु
		अगर (counter_select & CS_PORT_XMIT_DATA)
			ग_लिखो_port_cntr(ppd, C_TX_FLIT_VL, idx_from_vl(vl), 0);

		अगर (counter_select & CS_PORT_RCV_DATA)
			ग_लिखो_dev_cntr(dd, C_DC_RX_FLIT_VL, idx_from_vl(vl), 0);

		अगर (counter_select & CS_PORT_XMIT_PKTS)
			ग_लिखो_port_cntr(ppd, C_TX_PKT_VL, idx_from_vl(vl), 0);

		अगर (counter_select & CS_PORT_RCV_PKTS)
			ग_लिखो_dev_cntr(dd, C_DC_RX_PKT_VL, idx_from_vl(vl), 0);

		अगर (counter_select & CS_PORT_XMIT_WAIT) अणु
			ग_लिखो_port_cntr(ppd, C_TX_WAIT_VL, idx_from_vl(vl), 0);
			ppd->port_vl_xmit_रुको_last[idx_from_vl(vl)] = 0;
			ppd->vl_xmit_flit_cnt[idx_from_vl(vl)] = 0;
		पूर्ण

		/* sw_port_vl_congestion is 0 क्रम HFIs */
		अगर (counter_select & CS_PORT_RCV_FECN)
			ग_लिखो_dev_cntr(dd, C_DC_RCV_FCN_VL, idx_from_vl(vl), 0);

		अगर (counter_select & CS_PORT_RCV_BECN)
			ग_लिखो_dev_cntr(dd, C_DC_RCV_BCN_VL, idx_from_vl(vl), 0);

		/* port_vl_xmit_समय_cong is 0 क्रम HFIs */
		/* port_vl_xmit_wasted_bw ??? */
		/* port_vl_xmit_रुको_data - TXE (table 13-9 HFI spec) ??? */
		अगर (counter_select & CS_PORT_RCV_BUBBLE)
			ग_लिखो_dev_cntr(dd, C_DC_RCV_BBL_VL, idx_from_vl(vl), 0);

		/* अगर (counter_select & CS_PORT_MARK_FECN)
		 *     ग_लिखो_csr(dd, DCC_PRF_PORT_VL_MARK_FECN_CNT + offset, 0);
		 */
		अगर (counter_select & C_SW_XMIT_DSCD_VL)
			ग_लिखो_port_cntr(ppd, C_SW_XMIT_DSCD_VL,
					idx_from_vl(vl), 0);
	पूर्ण

	अगर (resp_len)
		*resp_len += माप(*req);

	वापस reply((काष्ठा ib_mad_hdr *)pmp);
पूर्ण

अटल पूर्णांक pma_set_opa_errorinfo(काष्ठा opa_pma_mad *pmp,
				 काष्ठा ib_device *ibdev,
				 u32 port, u32 *resp_len)
अणु
	काष्ठा _port_ei *rsp;
	काष्ठा opa_port_error_info_msg *req;
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u64 port_mask;
	u32 num_ports;
	u32 port_num;
	u8 num_pslm;
	u32 error_info_select;

	req = (काष्ठा opa_port_error_info_msg *)pmp->data;
	rsp = &req->port[0];

	num_ports = OPA_AM_NPORT(be32_to_cpu(pmp->mad_hdr.attr_mod));
	num_pslm = hweight64(be64_to_cpu(req->port_select_mask[3]));

	स_रखो(rsp, 0, माप(*rsp));

	अगर (num_ports != 1 || num_ports != num_pslm) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	/*
	 * The bit set in the mask needs to be consistent with the port
	 * the request came in on.
	 */
	port_mask = be64_to_cpu(req->port_select_mask[3]);
	port_num = find_first_bit((अचिन्हित दीर्घ *)&port_mask,
				  माप(port_mask) * 8);

	अगर (port_num != port) अणु
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	error_info_select = be32_to_cpu(req->error_info_select_mask);

	/* PortRcvErrorInfo */
	अगर (error_info_select & ES_PORT_RCV_ERROR_INFO)
		/* turn off status bit */
		dd->err_info_rcvport.status_and_code &= ~OPA_EI_STATUS_SMASK;

	/* ExcessiverBufferOverrunInfo */
	अगर (error_info_select & ES_EXCESSIVE_BUFFER_OVERRUN_INFO)
		/*
		 * status bit is essentially kept in the h/w - bit 5 of
		 * RCV_ERR_INFO
		 */
		ग_लिखो_csr(dd, RCV_ERR_INFO,
			  RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SMASK);

	अगर (error_info_select & ES_PORT_XMIT_CONSTRAINT_ERROR_INFO)
		dd->err_info_xmit_स्थिरraपूर्णांक.status &= ~OPA_EI_STATUS_SMASK;

	अगर (error_info_select & ES_PORT_RCV_CONSTRAINT_ERROR_INFO)
		dd->err_info_rcv_स्थिरraपूर्णांक.status &= ~OPA_EI_STATUS_SMASK;

	/* UncorrectableErrorInfo */
	अगर (error_info_select & ES_UNCORRECTABLE_ERROR_INFO)
		/* turn off status bit */
		dd->err_info_uncorrectable &= ~OPA_EI_STATUS_SMASK;

	/* FMConfigErrorInfo */
	अगर (error_info_select & ES_FM_CONFIG_ERROR_INFO)
		/* turn off status bit */
		dd->err_info_fmconfig &= ~OPA_EI_STATUS_SMASK;

	अगर (resp_len)
		*resp_len += माप(*req);

	वापस reply((काष्ठा ib_mad_hdr *)pmp);
पूर्ण

काष्ठा opa_congestion_info_attr अणु
	__be16 congestion_info;
	u8 control_table_cap;	/* Multiple of 64 entry unit CCTs */
	u8 congestion_log_length;
पूर्ण __packed;

अटल पूर्णांक __subn_get_opa_cong_info(काष्ठा opa_smp *smp, u32 am, u8 *data,
				    काष्ठा ib_device *ibdev, u32 port,
				    u32 *resp_len, u32 max_len)
अणु
	काष्ठा opa_congestion_info_attr *p =
		(काष्ठा opa_congestion_info_attr *)data;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	अगर (smp_length_check(माप(*p), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	p->congestion_info = 0;
	p->control_table_cap = ppd->cc_max_table_entries;
	p->congestion_log_length = OPA_CONG_LOG_ELEMS;

	अगर (resp_len)
		*resp_len += माप(*p);

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_get_opa_cong_setting(काष्ठा opa_smp *smp, u32 am,
				       u8 *data, काष्ठा ib_device *ibdev,
				       u32 port, u32 *resp_len, u32 max_len)
अणु
	पूर्णांक i;
	काष्ठा opa_congestion_setting_attr *p =
		(काष्ठा opa_congestion_setting_attr *)data;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा opa_congestion_setting_entry_shaकरोw *entries;
	काष्ठा cc_state *cc_state;

	अगर (smp_length_check(माप(*p), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	rcu_पढ़ो_lock();

	cc_state = get_cc_state(ppd);

	अगर (!cc_state) अणु
		rcu_पढ़ो_unlock();
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	entries = cc_state->cong_setting.entries;
	p->port_control = cpu_to_be16(cc_state->cong_setting.port_control);
	p->control_map = cpu_to_be32(cc_state->cong_setting.control_map);
	क्रम (i = 0; i < OPA_MAX_SLS; i++) अणु
		p->entries[i].ccti_increase = entries[i].ccti_increase;
		p->entries[i].ccti_समयr = cpu_to_be16(entries[i].ccti_समयr);
		p->entries[i].trigger_threshold =
			entries[i].trigger_threshold;
		p->entries[i].ccti_min = entries[i].ccti_min;
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (resp_len)
		*resp_len += माप(*p);

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

/*
 * Apply congestion control inक्रमmation stored in the ppd to the
 * active काष्ठाure.
 */
अटल व्योम apply_cc_state(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा cc_state *old_cc_state, *new_cc_state;

	new_cc_state = kzalloc(माप(*new_cc_state), GFP_KERNEL);
	अगर (!new_cc_state)
		वापस;

	/*
	 * Hold the lock क्रम updating *and* to prevent ppd inक्रमmation
	 * from changing during the update.
	 */
	spin_lock(&ppd->cc_state_lock);

	old_cc_state = get_cc_state_रक्षित(ppd);
	अगर (!old_cc_state) अणु
		/* never active, or shutting करोwn */
		spin_unlock(&ppd->cc_state_lock);
		kमुक्त(new_cc_state);
		वापस;
	पूर्ण

	*new_cc_state = *old_cc_state;

	अगर (ppd->total_cct_entry)
		new_cc_state->cct.ccti_limit = ppd->total_cct_entry - 1;
	अन्यथा
		new_cc_state->cct.ccti_limit = 0;

	स_नकल(new_cc_state->cct.entries, ppd->ccti_entries,
	       ppd->total_cct_entry * माप(काष्ठा ib_cc_table_entry));

	new_cc_state->cong_setting.port_control = IB_CC_CCS_PC_SL_BASED;
	new_cc_state->cong_setting.control_map = ppd->cc_sl_control_map;
	स_नकल(new_cc_state->cong_setting.entries, ppd->congestion_entries,
	       OPA_MAX_SLS * माप(काष्ठा opa_congestion_setting_entry));

	rcu_assign_poपूर्णांकer(ppd->cc_state, new_cc_state);

	spin_unlock(&ppd->cc_state_lock);

	kमुक्त_rcu(old_cc_state, rcu);
पूर्ण

अटल पूर्णांक __subn_set_opa_cong_setting(काष्ठा opa_smp *smp, u32 am, u8 *data,
				       काष्ठा ib_device *ibdev, u32 port,
				       u32 *resp_len, u32 max_len)
अणु
	काष्ठा opa_congestion_setting_attr *p =
		(काष्ठा opa_congestion_setting_attr *)data;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा opa_congestion_setting_entry_shaकरोw *entries;
	पूर्णांक i;

	अगर (smp_length_check(माप(*p), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	/*
	 * Save details from packet पूर्णांकo the ppd.  Hold the cc_state_lock so
	 * our inक्रमmation is consistent with anyone trying to apply the state.
	 */
	spin_lock(&ppd->cc_state_lock);
	ppd->cc_sl_control_map = be32_to_cpu(p->control_map);

	entries = ppd->congestion_entries;
	क्रम (i = 0; i < OPA_MAX_SLS; i++) अणु
		entries[i].ccti_increase = p->entries[i].ccti_increase;
		entries[i].ccti_समयr = be16_to_cpu(p->entries[i].ccti_समयr);
		entries[i].trigger_threshold =
			p->entries[i].trigger_threshold;
		entries[i].ccti_min = p->entries[i].ccti_min;
	पूर्ण
	spin_unlock(&ppd->cc_state_lock);

	/* now apply the inक्रमmation */
	apply_cc_state(ppd);

	वापस __subn_get_opa_cong_setting(smp, am, data, ibdev, port,
					   resp_len, max_len);
पूर्ण

अटल पूर्णांक __subn_get_opa_hfi1_cong_log(काष्ठा opa_smp *smp, u32 am,
					u8 *data, काष्ठा ib_device *ibdev,
					u32 port, u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा opa_hfi1_cong_log *cong_log = (काष्ठा opa_hfi1_cong_log *)data;
	u64 ts;
	पूर्णांक i;

	अगर (am || smp_length_check(माप(*cong_log), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	spin_lock_irq(&ppd->cc_log_lock);

	cong_log->log_type = OPA_CC_LOG_TYPE_HFI;
	cong_log->congestion_flags = 0;
	cong_log->threshold_event_counter =
		cpu_to_be16(ppd->threshold_event_counter);
	स_नकल(cong_log->threshold_cong_event_map,
	       ppd->threshold_cong_event_map,
	       माप(cong_log->threshold_cong_event_map));
	/* keep बारtamp in units of 1.024 usec */
	ts = kसमय_get_ns() / 1024;
	cong_log->current_समय_stamp = cpu_to_be32(ts);
	क्रम (i = 0; i < OPA_CONG_LOG_ELEMS; i++) अणु
		काष्ठा opa_hfi1_cong_log_event_पूर्णांकernal *cce =
			&ppd->cc_events[ppd->cc_mad_idx++];
		अगर (ppd->cc_mad_idx == OPA_CONG_LOG_ELEMS)
			ppd->cc_mad_idx = 0;
		/*
		 * Entries which are older than twice the समय
		 * required to wrap the counter are supposed to
		 * be zeroed (CA10-49 IBTA, release 1.2.1, V1).
		 */
		अगर ((ts - cce->बारtamp) / 2 > U32_MAX)
			जारी;
		स_नकल(cong_log->events[i].local_qp_cn_entry, &cce->lqpn, 3);
		स_नकल(cong_log->events[i].remote_qp_number_cn_entry,
		       &cce->rqpn, 3);
		cong_log->events[i].sl_svc_type_cn_entry =
			((cce->sl & 0x1f) << 3) | (cce->svc_type & 0x7);
		cong_log->events[i].remote_lid_cn_entry =
			cpu_to_be32(cce->rlid);
		cong_log->events[i].बारtamp_cn_entry =
			cpu_to_be32(cce->बारtamp);
	पूर्ण

	/*
	 * Reset threshold_cong_event_map, and threshold_event_counter
	 * to 0 when log is पढ़ो.
	 */
	स_रखो(ppd->threshold_cong_event_map, 0x0,
	       माप(ppd->threshold_cong_event_map));
	ppd->threshold_event_counter = 0;

	spin_unlock_irq(&ppd->cc_log_lock);

	अगर (resp_len)
		*resp_len += माप(काष्ठा opa_hfi1_cong_log);

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_get_opa_cc_table(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	काष्ठा ib_cc_table_attr *cc_table_attr =
		(काष्ठा ib_cc_table_attr *)data;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 start_block = OPA_AM_START_BLK(am);
	u32 n_blocks = OPA_AM_NBLK(am);
	काष्ठा ib_cc_table_entry_shaकरोw *entries;
	पूर्णांक i, j;
	u32 sentry, eentry;
	काष्ठा cc_state *cc_state;
	u32 size = माप(u16) * (IB_CCT_ENTRIES * n_blocks + 1);

	/* sanity check n_blocks, start_block */
	अगर (n_blocks == 0 || smp_length_check(size, max_len) ||
	    start_block + n_blocks > ppd->cc_max_table_entries) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	rcu_पढ़ो_lock();

	cc_state = get_cc_state(ppd);

	अगर (!cc_state) अणु
		rcu_पढ़ो_unlock();
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	sentry = start_block * IB_CCT_ENTRIES;
	eentry = sentry + (IB_CCT_ENTRIES * n_blocks);

	cc_table_attr->ccti_limit = cpu_to_be16(cc_state->cct.ccti_limit);

	entries = cc_state->cct.entries;

	/* वापस n_blocks, though the last block may not be full */
	क्रम (j = 0, i = sentry; i < eentry; j++, i++)
		cc_table_attr->ccti_entries[j].entry =
			cpu_to_be16(entries[i].entry);

	rcu_पढ़ो_unlock();

	अगर (resp_len)
		*resp_len += size;

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_set_opa_cc_table(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	काष्ठा ib_cc_table_attr *p = (काष्ठा ib_cc_table_attr *)data;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 start_block = OPA_AM_START_BLK(am);
	u32 n_blocks = OPA_AM_NBLK(am);
	काष्ठा ib_cc_table_entry_shaकरोw *entries;
	पूर्णांक i, j;
	u32 sentry, eentry;
	u16 ccti_limit;
	u32 size = माप(u16) * (IB_CCT_ENTRIES * n_blocks + 1);

	/* sanity check n_blocks, start_block */
	अगर (n_blocks == 0 || smp_length_check(size, max_len) ||
	    start_block + n_blocks > ppd->cc_max_table_entries) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	sentry = start_block * IB_CCT_ENTRIES;
	eentry = sentry + ((n_blocks - 1) * IB_CCT_ENTRIES) +
		 (be16_to_cpu(p->ccti_limit)) % IB_CCT_ENTRIES + 1;

	/* sanity check ccti_limit */
	ccti_limit = be16_to_cpu(p->ccti_limit);
	अगर (ccti_limit + 1 > eentry) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	/*
	 * Save details from packet पूर्णांकo the ppd.  Hold the cc_state_lock so
	 * our inक्रमmation is consistent with anyone trying to apply the state.
	 */
	spin_lock(&ppd->cc_state_lock);
	ppd->total_cct_entry = ccti_limit + 1;
	entries = ppd->ccti_entries;
	क्रम (j = 0, i = sentry; i < eentry; j++, i++)
		entries[i].entry = be16_to_cpu(p->ccti_entries[j].entry);
	spin_unlock(&ppd->cc_state_lock);

	/* now apply the inक्रमmation */
	apply_cc_state(ppd);

	वापस __subn_get_opa_cc_table(smp, am, data, ibdev, port, resp_len,
				       max_len);
पूर्ण

काष्ठा opa_led_info अणु
	__be32 rsvd_led_mask;
	__be32 rsvd;
पूर्ण;

#घोषणा OPA_LED_SHIFT	31
#घोषणा OPA_LED_MASK	BIT(OPA_LED_SHIFT)

अटल पूर्णांक __subn_get_opa_led_info(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	काष्ठा opa_led_info *p = (काष्ठा opa_led_info *)data;
	u32 nport = OPA_AM_NPORT(am);
	u32 is_beaconing_active;

	अगर (nport != 1 || smp_length_check(माप(*p), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	/*
	 * This pairs with the memory barrier in hfi1_start_led_override to
	 * ensure that we पढ़ो the correct state of LED beaconing represented
	 * by led_override_समयr_active
	 */
	smp_rmb();
	is_beaconing_active = !!atomic_पढ़ो(&ppd->led_override_समयr_active);
	p->rsvd_led_mask = cpu_to_be32(is_beaconing_active << OPA_LED_SHIFT);

	अगर (resp_len)
		*resp_len += माप(काष्ठा opa_led_info);

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक __subn_set_opa_led_info(काष्ठा opa_smp *smp, u32 am, u8 *data,
				   काष्ठा ib_device *ibdev, u32 port,
				   u32 *resp_len, u32 max_len)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(ibdev);
	काष्ठा opa_led_info *p = (काष्ठा opa_led_info *)data;
	u32 nport = OPA_AM_NPORT(am);
	पूर्णांक on = !!(be32_to_cpu(p->rsvd_led_mask) & OPA_LED_MASK);

	अगर (nport != 1 || smp_length_check(माप(*p), max_len)) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	अगर (on)
		hfi1_start_led_override(dd->pport, 2000, 1500);
	अन्यथा
		shutकरोwn_led_override(dd->pport);

	वापस __subn_get_opa_led_info(smp, am, data, ibdev, port, resp_len,
				       max_len);
पूर्ण

अटल पूर्णांक subn_get_opa_sma(__be16 attr_id, काष्ठा opa_smp *smp, u32 am,
			    u8 *data, काष्ठा ib_device *ibdev, u32 port,
			    u32 *resp_len, u32 max_len)
अणु
	पूर्णांक ret;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);

	चयन (attr_id) अणु
	हाल IB_SMP_ATTR_NODE_DESC:
		ret = __subn_get_opa_nodedesc(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल IB_SMP_ATTR_NODE_INFO:
		ret = __subn_get_opa_nodeinfo(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल IB_SMP_ATTR_PORT_INFO:
		ret = __subn_get_opa_portinfo(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल IB_SMP_ATTR_PKEY_TABLE:
		ret = __subn_get_opa_pkeytable(smp, am, data, ibdev, port,
					       resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_SL_TO_SC_MAP:
		ret = __subn_get_opa_sl_to_sc(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_SC_TO_SL_MAP:
		ret = __subn_get_opa_sc_to_sl(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_SC_TO_VLT_MAP:
		ret = __subn_get_opa_sc_to_vlt(smp, am, data, ibdev, port,
					       resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_SC_TO_VLNT_MAP:
		ret = __subn_get_opa_sc_to_vlnt(smp, am, data, ibdev, port,
						resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_PORT_STATE_INFO:
		ret = __subn_get_opa_psi(smp, am, data, ibdev, port,
					 resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_BUFFER_CONTROL_TABLE:
		ret = __subn_get_opa_bct(smp, am, data, ibdev, port,
					 resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_CABLE_INFO:
		ret = __subn_get_opa_cable_info(smp, am, data, ibdev, port,
						resp_len, max_len);
		अवरोध;
	हाल IB_SMP_ATTR_VL_ARB_TABLE:
		ret = __subn_get_opa_vl_arb(smp, am, data, ibdev, port,
					    resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_CONGESTION_INFO:
		ret = __subn_get_opa_cong_info(smp, am, data, ibdev, port,
					       resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_HFI_CONGESTION_SETTING:
		ret = __subn_get_opa_cong_setting(smp, am, data, ibdev,
						  port, resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_HFI_CONGESTION_LOG:
		ret = __subn_get_opa_hfi1_cong_log(smp, am, data, ibdev,
						   port, resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_CONGESTION_CONTROL_TABLE:
		ret = __subn_get_opa_cc_table(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल IB_SMP_ATTR_LED_INFO:
		ret = __subn_get_opa_led_info(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल IB_SMP_ATTR_SM_INFO:
		अगर (ibp->rvp.port_cap_flags & IB_PORT_SM_DISABLED)
			वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
		अगर (ibp->rvp.port_cap_flags & IB_PORT_SM)
			वापस IB_MAD_RESULT_SUCCESS;
		fallthrough;
	शेष:
		smp->status |= IB_SMP_UNSUP_METH_ATTR;
		ret = reply((काष्ठा ib_mad_hdr *)smp);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक subn_set_opa_sma(__be16 attr_id, काष्ठा opa_smp *smp, u32 am,
			    u8 *data, काष्ठा ib_device *ibdev, u32 port,
			    u32 *resp_len, u32 max_len, पूर्णांक local_mad)
अणु
	पूर्णांक ret;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);

	चयन (attr_id) अणु
	हाल IB_SMP_ATTR_PORT_INFO:
		ret = __subn_set_opa_portinfo(smp, am, data, ibdev, port,
					      resp_len, max_len, local_mad);
		अवरोध;
	हाल IB_SMP_ATTR_PKEY_TABLE:
		ret = __subn_set_opa_pkeytable(smp, am, data, ibdev, port,
					       resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_SL_TO_SC_MAP:
		ret = __subn_set_opa_sl_to_sc(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_SC_TO_SL_MAP:
		ret = __subn_set_opa_sc_to_sl(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_SC_TO_VLT_MAP:
		ret = __subn_set_opa_sc_to_vlt(smp, am, data, ibdev, port,
					       resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_SC_TO_VLNT_MAP:
		ret = __subn_set_opa_sc_to_vlnt(smp, am, data, ibdev, port,
						resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_PORT_STATE_INFO:
		ret = __subn_set_opa_psi(smp, am, data, ibdev, port,
					 resp_len, max_len, local_mad);
		अवरोध;
	हाल OPA_ATTRIB_ID_BUFFER_CONTROL_TABLE:
		ret = __subn_set_opa_bct(smp, am, data, ibdev, port,
					 resp_len, max_len);
		अवरोध;
	हाल IB_SMP_ATTR_VL_ARB_TABLE:
		ret = __subn_set_opa_vl_arb(smp, am, data, ibdev, port,
					    resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_HFI_CONGESTION_SETTING:
		ret = __subn_set_opa_cong_setting(smp, am, data, ibdev,
						  port, resp_len, max_len);
		अवरोध;
	हाल OPA_ATTRIB_ID_CONGESTION_CONTROL_TABLE:
		ret = __subn_set_opa_cc_table(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल IB_SMP_ATTR_LED_INFO:
		ret = __subn_set_opa_led_info(smp, am, data, ibdev, port,
					      resp_len, max_len);
		अवरोध;
	हाल IB_SMP_ATTR_SM_INFO:
		अगर (ibp->rvp.port_cap_flags & IB_PORT_SM_DISABLED)
			वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
		अगर (ibp->rvp.port_cap_flags & IB_PORT_SM)
			वापस IB_MAD_RESULT_SUCCESS;
		fallthrough;
	शेष:
		smp->status |= IB_SMP_UNSUP_METH_ATTR;
		ret = reply((काष्ठा ib_mad_hdr *)smp);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम set_aggr_error(काष्ठा opa_aggregate *ag)
अणु
	ag->err_reqlength |= cpu_to_be16(0x8000);
पूर्ण

अटल पूर्णांक subn_get_opa_aggregate(काष्ठा opa_smp *smp,
				  काष्ठा ib_device *ibdev, u32 port,
				  u32 *resp_len)
अणु
	पूर्णांक i;
	u32 num_attr = be32_to_cpu(smp->attr_mod) & 0x000000ff;
	u8 *next_smp = opa_get_smp_data(smp);

	अगर (num_attr < 1 || num_attr > 117) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	क्रम (i = 0; i < num_attr; i++) अणु
		काष्ठा opa_aggregate *agg;
		माप_प्रकार agg_data_len;
		माप_प्रकार agg_size;
		u32 am;

		agg = (काष्ठा opa_aggregate *)next_smp;
		agg_data_len = (be16_to_cpu(agg->err_reqlength) & 0x007f) * 8;
		agg_size = माप(*agg) + agg_data_len;
		am = be32_to_cpu(agg->attr_mod);

		*resp_len += agg_size;

		अगर (next_smp + agg_size > ((u8 *)smp) + माप(*smp)) अणु
			smp->status |= IB_SMP_INVALID_FIELD;
			वापस reply((काष्ठा ib_mad_hdr *)smp);
		पूर्ण

		/* zero the payload क्रम this segment */
		स_रखो(next_smp + माप(*agg), 0, agg_data_len);

		(व्योम)subn_get_opa_sma(agg->attr_id, smp, am, agg->data,
				       ibdev, port, शून्य, (u32)agg_data_len);

		अगर (smp->status & IB_SMP_INVALID_FIELD)
			अवरोध;
		अगर (smp->status & ~IB_SMP_सूचीECTION) अणु
			set_aggr_error(agg);
			वापस reply((काष्ठा ib_mad_hdr *)smp);
		पूर्ण
		next_smp += agg_size;
	पूर्ण

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

अटल पूर्णांक subn_set_opa_aggregate(काष्ठा opa_smp *smp,
				  काष्ठा ib_device *ibdev, u32 port,
				  u32 *resp_len, पूर्णांक local_mad)
अणु
	पूर्णांक i;
	u32 num_attr = be32_to_cpu(smp->attr_mod) & 0x000000ff;
	u8 *next_smp = opa_get_smp_data(smp);

	अगर (num_attr < 1 || num_attr > 117) अणु
		smp->status |= IB_SMP_INVALID_FIELD;
		वापस reply((काष्ठा ib_mad_hdr *)smp);
	पूर्ण

	क्रम (i = 0; i < num_attr; i++) अणु
		काष्ठा opa_aggregate *agg;
		माप_प्रकार agg_data_len;
		माप_प्रकार agg_size;
		u32 am;

		agg = (काष्ठा opa_aggregate *)next_smp;
		agg_data_len = (be16_to_cpu(agg->err_reqlength) & 0x007f) * 8;
		agg_size = माप(*agg) + agg_data_len;
		am = be32_to_cpu(agg->attr_mod);

		*resp_len += agg_size;

		अगर (next_smp + agg_size > ((u8 *)smp) + माप(*smp)) अणु
			smp->status |= IB_SMP_INVALID_FIELD;
			वापस reply((काष्ठा ib_mad_hdr *)smp);
		पूर्ण

		(व्योम)subn_set_opa_sma(agg->attr_id, smp, am, agg->data,
				       ibdev, port, शून्य, (u32)agg_data_len,
				       local_mad);

		अगर (smp->status & IB_SMP_INVALID_FIELD)
			अवरोध;
		अगर (smp->status & ~IB_SMP_सूचीECTION) अणु
			set_aggr_error(agg);
			वापस reply((काष्ठा ib_mad_hdr *)smp);
		पूर्ण
		next_smp += agg_size;
	पूर्ण

	वापस reply((काष्ठा ib_mad_hdr *)smp);
पूर्ण

/*
 * OPAv1 specअगरies that, on the transition to link up, these counters
 * are cleared:
 *   PortRcvErrors [*]
 *   LinkErrorRecovery
 *   LocalLinkIntegrityErrors
 *   ExcessiveBufferOverruns [*]
 *
 * [*] Error info associated with these counters is retained, but the
 * error info status is reset to 0.
 */
व्योम clear_linkup_counters(काष्ठा hfi1_devdata *dd)
अणु
	/* PortRcvErrors */
	ग_लिखो_dev_cntr(dd, C_DC_RCV_ERR, CNTR_INVALID_VL, 0);
	dd->err_info_rcvport.status_and_code &= ~OPA_EI_STATUS_SMASK;
	/* LinkErrorRecovery */
	ग_लिखो_dev_cntr(dd, C_DC_SEQ_CRC_CNT, CNTR_INVALID_VL, 0);
	ग_लिखो_dev_cntr(dd, C_DC_REINIT_FROM_PEER_CNT, CNTR_INVALID_VL, 0);
	/* LocalLinkIntegrityErrors */
	ग_लिखो_dev_cntr(dd, C_DC_RX_REPLAY, CNTR_INVALID_VL, 0);
	/* ExcessiveBufferOverruns */
	ग_लिखो_dev_cntr(dd, C_RCV_OVF, CNTR_INVALID_VL, 0);
	dd->rcv_ovfl_cnt = 0;
	dd->err_info_xmit_स्थिरraपूर्णांक.status &= ~OPA_EI_STATUS_SMASK;
पूर्ण

अटल पूर्णांक is_full_mgmt_pkey_in_table(काष्ठा hfi1_ibport *ibp)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); ++i)
		अगर (ppd->pkeys[i] == FULL_MGMT_P_KEY)
			वापस 1;

	वापस 0;
पूर्ण

/*
 * is_local_mad() वापसs 1 अगर 'mad' is sent from, and destined to the
 * local node, 0 otherwise.
 */
अटल पूर्णांक is_local_mad(काष्ठा hfi1_ibport *ibp, स्थिर काष्ठा opa_mad *mad,
			स्थिर काष्ठा ib_wc *in_wc)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	स्थिर काष्ठा opa_smp *smp = (स्थिर काष्ठा opa_smp *)mad;

	अगर (smp->mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) अणु
		वापस (smp->hop_cnt == 0 &&
			smp->route.dr.dr_slid == OPA_LID_PERMISSIVE &&
			smp->route.dr.dr_dlid == OPA_LID_PERMISSIVE);
	पूर्ण

	वापस (in_wc->slid == ppd->lid);
पूर्ण

/*
 * opa_local_smp_check() should only be called on MADs क्रम which
 * is_local_mad() वापसs true. It applies the SMP checks that are
 * specअगरic to SMPs which are sent from, and destined to this node.
 * opa_local_smp_check() वापसs 0 अगर the SMP passes its checks, 1
 * otherwise.
 *
 * SMPs which arrive from other nodes are instead checked by
 * opa_smp_check().
 */
अटल पूर्णांक opa_local_smp_check(काष्ठा hfi1_ibport *ibp,
			       स्थिर काष्ठा ib_wc *in_wc)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u16 pkey;

	अगर (in_wc->pkey_index >= ARRAY_SIZE(ppd->pkeys))
		वापस 1;

	pkey = ppd->pkeys[in_wc->pkey_index];
	/*
	 * We need to करो the "node-local" checks specअगरied in OPAv1,
	 * rev 0.90, section 9.10.26, which are:
	 *   - pkey is 0x7fff, or 0xffff
	 *   - Source QPN == 0 || Destination QPN == 0
	 *   - the MAD header's management class is either
	 *     IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE or
	 *     IB_MGMT_CLASS_SUBN_LID_ROUTED
	 *   - SLID != 0
	 *
	 * However, we know (and so करोn't need to check again) that,
	 * क्रम local SMPs, the MAD stack passes MADs with:
	 *   - Source QPN of 0
	 *   - MAD mgmt_class is IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE
	 *   - SLID is either: OPA_LID_PERMISSIVE (0xFFFFFFFF), or
	 *     our own port's lid
	 *
	 */
	अगर (pkey == LIM_MGMT_P_KEY || pkey == FULL_MGMT_P_KEY)
		वापस 0;
	ingress_pkey_table_fail(ppd, pkey, in_wc->slid);
	वापस 1;
पूर्ण

/**
 * hfi1_pkey_validation_pma - It validates PKEYs क्रम incoming PMA MAD packets.
 * @ibp: IB port data
 * @in_mad: MAD packet with header and data
 * @in_wc: Work completion data such as source LID, port number, etc.
 *
 * These are all the possible logic rules क्रम validating a pkey:
 *
 * a) If pkey neither FULL_MGMT_P_KEY nor LIM_MGMT_P_KEY,
 *    and NOT self-originated packet:
 *     Drop MAD packet as it should always be part of the
 *     management partition unless it's a self-originated packet.
 *
 * b) If pkey_index -> FULL_MGMT_P_KEY, and LIM_MGMT_P_KEY in pkey table:
 *     The packet is coming from a management node and the receiving node
 *     is also a management node, so it is safe क्रम the packet to go through.
 *
 * c) If pkey_index -> FULL_MGMT_P_KEY, and LIM_MGMT_P_KEY is NOT in pkey table:
 *     Drop the packet as LIM_MGMT_P_KEY should always be in the pkey table.
 *     It could be an FM misconfiguration.
 *
 * d) If pkey_index -> LIM_MGMT_P_KEY and FULL_MGMT_P_KEY is NOT in pkey table:
 *     It is safe क्रम the packet to go through since a non-management node is
 *     talking to another non-management node.
 *
 * e) If pkey_index -> LIM_MGMT_P_KEY and FULL_MGMT_P_KEY in pkey table:
 *     Drop the packet because a non-management node is talking to a
 *     management node, and it could be an attack.
 *
 * For the implementation, these rules can be simplied to only checking
 * क्रम (a) and (e). There's no need to check क्रम rule (b) as
 * the packet करोesn't need to be dropped. Rule (c) is not possible in
 * the driver as LIM_MGMT_P_KEY is always in the pkey table.
 *
 * Return:
 * 0 - pkey is okay, -EINVAL it's a bad pkey
 */
अटल पूर्णांक hfi1_pkey_validation_pma(काष्ठा hfi1_ibport *ibp,
				    स्थिर काष्ठा opa_mad *in_mad,
				    स्थिर काष्ठा ib_wc *in_wc)
अणु
	u16 pkey_value = hfi1_lookup_pkey_value(ibp, in_wc->pkey_index);

	/* Rule (a) from above */
	अगर (!is_local_mad(ibp, in_mad, in_wc) &&
	    pkey_value != LIM_MGMT_P_KEY &&
	    pkey_value != FULL_MGMT_P_KEY)
		वापस -EINVAL;

	/* Rule (e) from above */
	अगर (pkey_value == LIM_MGMT_P_KEY &&
	    is_full_mgmt_pkey_in_table(ibp))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक process_subn_opa(काष्ठा ib_device *ibdev, पूर्णांक mad_flags,
			    u32 port, स्थिर काष्ठा opa_mad *in_mad,
			    काष्ठा opa_mad *out_mad,
			    u32 *resp_len, पूर्णांक local_mad)
अणु
	काष्ठा opa_smp *smp = (काष्ठा opa_smp *)out_mad;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	u8 *data;
	u32 am, data_size;
	__be16 attr_id;
	पूर्णांक ret;

	*out_mad = *in_mad;
	data = opa_get_smp_data(smp);
	data_size = (u32)opa_get_smp_data_size(smp);

	am = be32_to_cpu(smp->attr_mod);
	attr_id = smp->attr_id;
	अगर (smp->class_version != OPA_SM_CLASS_VERSION) अणु
		smp->status |= IB_SMP_UNSUP_VERSION;
		ret = reply((काष्ठा ib_mad_hdr *)smp);
		वापस ret;
	पूर्ण
	ret = check_mkey(ibp, (काष्ठा ib_mad_hdr *)smp, mad_flags, smp->mkey,
			 smp->route.dr.dr_slid, smp->route.dr.वापस_path,
			 smp->hop_cnt);
	अगर (ret) अणु
		u32 port_num = be32_to_cpu(smp->attr_mod);

		/*
		 * If this is a get/set portinfo, we alपढ़ोy check the
		 * M_Key अगर the MAD is क्रम another port and the M_Key
		 * is OK on the receiving port. This check is needed
		 * to increment the error counters when the M_Key
		 * fails to match on *both* ports.
		 */
		अगर (attr_id == IB_SMP_ATTR_PORT_INFO &&
		    (smp->method == IB_MGMT_METHOD_GET ||
		     smp->method == IB_MGMT_METHOD_SET) &&
		    port_num && port_num <= ibdev->phys_port_cnt &&
		    port != port_num)
			(व्योम)check_mkey(to_iport(ibdev, port_num),
					  (काष्ठा ib_mad_hdr *)smp, 0,
					  smp->mkey, smp->route.dr.dr_slid,
					  smp->route.dr.वापस_path,
					  smp->hop_cnt);
		ret = IB_MAD_RESULT_FAILURE;
		वापस ret;
	पूर्ण

	*resp_len = opa_get_smp_header_size(smp);

	चयन (smp->method) अणु
	हाल IB_MGMT_METHOD_GET:
		चयन (attr_id) अणु
		शेष:
			clear_opa_smp_data(smp);
			ret = subn_get_opa_sma(attr_id, smp, am, data,
					       ibdev, port, resp_len,
					       data_size);
			अवरोध;
		हाल OPA_ATTRIB_ID_AGGREGATE:
			ret = subn_get_opa_aggregate(smp, ibdev, port,
						     resp_len);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IB_MGMT_METHOD_SET:
		चयन (attr_id) अणु
		शेष:
			ret = subn_set_opa_sma(attr_id, smp, am, data,
					       ibdev, port, resp_len,
					       data_size, local_mad);
			अवरोध;
		हाल OPA_ATTRIB_ID_AGGREGATE:
			ret = subn_set_opa_aggregate(smp, ibdev, port,
						     resp_len, local_mad);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IB_MGMT_METHOD_TRAP:
	हाल IB_MGMT_METHOD_REPORT:
	हाल IB_MGMT_METHOD_REPORT_RESP:
	हाल IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * beक्रमe checking क्रम other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		अवरोध;
	हाल IB_MGMT_METHOD_TRAP_REPRESS:
		subn_handle_opa_trap_repress(ibp, smp);
		/* Always successful */
		ret = IB_MAD_RESULT_SUCCESS;
		अवरोध;
	शेष:
		smp->status |= IB_SMP_UNSUP_METHOD;
		ret = reply((काष्ठा ib_mad_hdr *)smp);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक process_subn(काष्ठा ib_device *ibdev, पूर्णांक mad_flags,
			u32 port, स्थिर काष्ठा ib_mad *in_mad,
			काष्ठा ib_mad *out_mad)
अणु
	काष्ठा ib_smp *smp = (काष्ठा ib_smp *)out_mad;
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);
	पूर्णांक ret;

	*out_mad = *in_mad;
	अगर (smp->class_version != 1) अणु
		smp->status |= IB_SMP_UNSUP_VERSION;
		ret = reply((काष्ठा ib_mad_hdr *)smp);
		वापस ret;
	पूर्ण

	ret = check_mkey(ibp, (काष्ठा ib_mad_hdr *)smp, mad_flags,
			 smp->mkey, (__क्रमce __be32)smp->dr_slid,
			 smp->वापस_path, smp->hop_cnt);
	अगर (ret) अणु
		u32 port_num = be32_to_cpu(smp->attr_mod);

		/*
		 * If this is a get/set portinfo, we alपढ़ोy check the
		 * M_Key अगर the MAD is क्रम another port and the M_Key
		 * is OK on the receiving port. This check is needed
		 * to increment the error counters when the M_Key
		 * fails to match on *both* ports.
		 */
		अगर (in_mad->mad_hdr.attr_id == IB_SMP_ATTR_PORT_INFO &&
		    (smp->method == IB_MGMT_METHOD_GET ||
		     smp->method == IB_MGMT_METHOD_SET) &&
		    port_num && port_num <= ibdev->phys_port_cnt &&
		    port != port_num)
			(व्योम)check_mkey(to_iport(ibdev, port_num),
					 (काष्ठा ib_mad_hdr *)smp, 0,
					 smp->mkey,
					 (__क्रमce __be32)smp->dr_slid,
					 smp->वापस_path, smp->hop_cnt);
		ret = IB_MAD_RESULT_FAILURE;
		वापस ret;
	पूर्ण

	चयन (smp->method) अणु
	हाल IB_MGMT_METHOD_GET:
		चयन (smp->attr_id) अणु
		हाल IB_SMP_ATTR_NODE_INFO:
			ret = subn_get_nodeinfo(smp, ibdev, port);
			अवरोध;
		शेष:
			smp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((काष्ठा ib_mad_hdr *)smp);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक process_perf(काष्ठा ib_device *ibdev, u32 port,
			स्थिर काष्ठा ib_mad *in_mad,
			काष्ठा ib_mad *out_mad)
अणु
	काष्ठा ib_pma_mad *pmp = (काष्ठा ib_pma_mad *)out_mad;
	काष्ठा ib_class_port_info *cpi = (काष्ठा ib_class_port_info *)
						&pmp->data;
	पूर्णांक ret = IB_MAD_RESULT_FAILURE;

	*out_mad = *in_mad;
	अगर (pmp->mad_hdr.class_version != 1) अणु
		pmp->mad_hdr.status |= IB_SMP_UNSUP_VERSION;
		ret = reply((काष्ठा ib_mad_hdr *)pmp);
		वापस ret;
	पूर्ण

	चयन (pmp->mad_hdr.method) अणु
	हाल IB_MGMT_METHOD_GET:
		चयन (pmp->mad_hdr.attr_id) अणु
		हाल IB_PMA_PORT_COUNTERS:
			ret = pma_get_ib_portcounters(pmp, ibdev, port);
			अवरोध;
		हाल IB_PMA_PORT_COUNTERS_EXT:
			ret = pma_get_ib_portcounters_ext(pmp, ibdev, port);
			अवरोध;
		हाल IB_PMA_CLASS_PORT_INFO:
			cpi->capability_mask = IB_PMA_CLASS_CAP_EXT_WIDTH;
			ret = reply((काष्ठा ib_mad_hdr *)pmp);
			अवरोध;
		शेष:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((काष्ठा ib_mad_hdr *)pmp);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IB_MGMT_METHOD_SET:
		अगर (pmp->mad_hdr.attr_id) अणु
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((काष्ठा ib_mad_hdr *)pmp);
		पूर्ण
		अवरोध;

	हाल IB_MGMT_METHOD_TRAP:
	हाल IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * beक्रमe checking क्रम other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		अवरोध;

	शेष:
		pmp->mad_hdr.status |= IB_SMP_UNSUP_METHOD;
		ret = reply((काष्ठा ib_mad_hdr *)pmp);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक process_perf_opa(काष्ठा ib_device *ibdev, u32 port,
			    स्थिर काष्ठा opa_mad *in_mad,
			    काष्ठा opa_mad *out_mad, u32 *resp_len)
अणु
	काष्ठा opa_pma_mad *pmp = (काष्ठा opa_pma_mad *)out_mad;
	पूर्णांक ret;

	*out_mad = *in_mad;

	अगर (pmp->mad_hdr.class_version != OPA_SM_CLASS_VERSION) अणु
		pmp->mad_hdr.status |= IB_SMP_UNSUP_VERSION;
		वापस reply((काष्ठा ib_mad_hdr *)pmp);
	पूर्ण

	*resp_len = माप(pmp->mad_hdr);

	चयन (pmp->mad_hdr.method) अणु
	हाल IB_MGMT_METHOD_GET:
		चयन (pmp->mad_hdr.attr_id) अणु
		हाल IB_PMA_CLASS_PORT_INFO:
			ret = pma_get_opa_classportinfo(pmp, ibdev, resp_len);
			अवरोध;
		हाल OPA_PM_ATTRIB_ID_PORT_STATUS:
			ret = pma_get_opa_portstatus(pmp, ibdev, port,
						     resp_len);
			अवरोध;
		हाल OPA_PM_ATTRIB_ID_DATA_PORT_COUNTERS:
			ret = pma_get_opa_datacounters(pmp, ibdev, port,
						       resp_len);
			अवरोध;
		हाल OPA_PM_ATTRIB_ID_ERROR_PORT_COUNTERS:
			ret = pma_get_opa_porterrors(pmp, ibdev, port,
						     resp_len);
			अवरोध;
		हाल OPA_PM_ATTRIB_ID_ERROR_INFO:
			ret = pma_get_opa_errorinfo(pmp, ibdev, port,
						    resp_len);
			अवरोध;
		शेष:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((काष्ठा ib_mad_hdr *)pmp);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IB_MGMT_METHOD_SET:
		चयन (pmp->mad_hdr.attr_id) अणु
		हाल OPA_PM_ATTRIB_ID_CLEAR_PORT_STATUS:
			ret = pma_set_opa_portstatus(pmp, ibdev, port,
						     resp_len);
			अवरोध;
		हाल OPA_PM_ATTRIB_ID_ERROR_INFO:
			ret = pma_set_opa_errorinfo(pmp, ibdev, port,
						    resp_len);
			अवरोध;
		शेष:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((काष्ठा ib_mad_hdr *)pmp);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IB_MGMT_METHOD_TRAP:
	हाल IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * beक्रमe checking क्रम other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		अवरोध;

	शेष:
		pmp->mad_hdr.status |= IB_SMP_UNSUP_METHOD;
		ret = reply((काष्ठा ib_mad_hdr *)pmp);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_process_opa_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags,
				u32 port, स्थिर काष्ठा ib_wc *in_wc,
				स्थिर काष्ठा ib_grh *in_grh,
				स्थिर काष्ठा opa_mad *in_mad,
				काष्ठा opa_mad *out_mad, माप_प्रकार *out_mad_size,
				u16 *out_mad_pkey_index)
अणु
	पूर्णांक ret;
	पूर्णांक pkey_idx;
	पूर्णांक local_mad = 0;
	u32 resp_len = in_wc->byte_len - माप(*in_grh);
	काष्ठा hfi1_ibport *ibp = to_iport(ibdev, port);

	pkey_idx = hfi1_lookup_pkey_idx(ibp, LIM_MGMT_P_KEY);
	अगर (pkey_idx < 0) अणु
		pr_warn("failed to find limited mgmt pkey, defaulting 0x%x\n",
			hfi1_get_pkey(ibp, 1));
		pkey_idx = 1;
	पूर्ण
	*out_mad_pkey_index = (u16)pkey_idx;

	चयन (in_mad->mad_hdr.mgmt_class) अणु
	हाल IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE:
	हाल IB_MGMT_CLASS_SUBN_LID_ROUTED:
		local_mad = is_local_mad(ibp, in_mad, in_wc);
		अगर (local_mad) अणु
			ret = opa_local_smp_check(ibp, in_wc);
			अगर (ret)
				वापस IB_MAD_RESULT_FAILURE;
		पूर्ण
		ret = process_subn_opa(ibdev, mad_flags, port, in_mad,
				       out_mad, &resp_len, local_mad);
		जाओ bail;
	हाल IB_MGMT_CLASS_PERF_MGMT:
		ret = hfi1_pkey_validation_pma(ibp, in_mad, in_wc);
		अगर (ret)
			वापस IB_MAD_RESULT_FAILURE;

		ret = process_perf_opa(ibdev, port, in_mad, out_mad, &resp_len);
		जाओ bail;

	शेष:
		ret = IB_MAD_RESULT_SUCCESS;
	पूर्ण

bail:
	अगर (ret & IB_MAD_RESULT_REPLY)
		*out_mad_size = round_up(resp_len, 8);
	अन्यथा अगर (ret & IB_MAD_RESULT_SUCCESS)
		*out_mad_size = in_wc->byte_len - माप(काष्ठा ib_grh);

	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_process_ib_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port,
			       स्थिर काष्ठा ib_wc *in_wc,
			       स्थिर काष्ठा ib_grh *in_grh,
			       स्थिर काष्ठा ib_mad *in_mad,
			       काष्ठा ib_mad *out_mad)
अणु
	पूर्णांक ret;

	चयन (in_mad->mad_hdr.mgmt_class) अणु
	हाल IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE:
	हाल IB_MGMT_CLASS_SUBN_LID_ROUTED:
		ret = process_subn(ibdev, mad_flags, port, in_mad, out_mad);
		अवरोध;
	हाल IB_MGMT_CLASS_PERF_MGMT:
		ret = process_perf(ibdev, port, in_mad, out_mad);
		अवरोध;
	शेष:
		ret = IB_MAD_RESULT_SUCCESS;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * hfi1_process_mad - process an incoming MAD packet
 * @ibdev: the infiniband device this packet came in on
 * @mad_flags: MAD flags
 * @port: the port number this packet came in on
 * @in_wc: the work completion entry क्रम this packet
 * @in_grh: the global route header क्रम this packet
 * @in_mad: the incoming MAD
 * @out_mad: any outgoing MAD reply
 * @out_mad_size: size of the outgoing MAD reply
 * @out_mad_pkey_index: used to apss back the packet key index
 *
 * Returns IB_MAD_RESULT_SUCCESS अगर this is a MAD that we are not
 * पूर्णांकerested in processing.
 *
 * Note that the verbs framework has alपढ़ोy करोne the MAD sanity checks,
 * and hop count/poपूर्णांकer updating क्रम IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE
 * MADs.
 *
 * This is called by the ib_mad module.
 */
पूर्णांक hfi1_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port,
		     स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		     स्थिर काष्ठा ib_mad *in_mad, काष्ठा ib_mad *out_mad,
		     माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index)
अणु
	चयन (in_mad->mad_hdr.base_version) अणु
	हाल OPA_MGMT_BASE_VERSION:
		वापस hfi1_process_opa_mad(ibdev, mad_flags, port,
					    in_wc, in_grh,
					    (काष्ठा opa_mad *)in_mad,
					    (काष्ठा opa_mad *)out_mad,
					    out_mad_size,
					    out_mad_pkey_index);
	हाल IB_MGMT_BASE_VERSION:
		वापस hfi1_process_ib_mad(ibdev, mad_flags, port, in_wc,
					   in_grh, in_mad, out_mad);
	शेष:
		अवरोध;
	पूर्ण

	वापस IB_MAD_RESULT_FAILURE;
पूर्ण
