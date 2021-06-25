<शैली गुरु>
/*
 * Copyright(c) 2016 - 2018 Intel Corporation.
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

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dma-mapping.h>
#समावेश "vt.h"
#समावेश "cq.h"
#समावेश "trace.h"

#घोषणा RVT_UVERBS_ABI_VERSION 2

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("RDMA Verbs Transport Library");

अटल पूर्णांक rvt_init(व्योम)
अणु
	पूर्णांक ret = rvt_driver_cq_init();

	अगर (ret)
		pr_err("Error in driver CQ init.\n");

	वापस ret;
पूर्ण
module_init(rvt_init);

अटल व्योम rvt_cleanup(व्योम)
अणु
	rvt_cq_निकास();
पूर्ण
module_निकास(rvt_cleanup);

/**
 * rvt_alloc_device - allocate rdi
 * @size: how big of a काष्ठाure to allocate
 * @nports: number of ports to allocate array slots क्रम
 *
 * Use IB core device alloc to allocate space क्रम the rdi which is assumed to be
 * inside of the ib_device. Any extra space that drivers require should be
 * included in size.
 *
 * We also allocate a port array based on the number of ports.
 *
 * Return: poपूर्णांकer to allocated rdi
 */
काष्ठा rvt_dev_info *rvt_alloc_device(माप_प्रकार size, पूर्णांक nports)
अणु
	काष्ठा rvt_dev_info *rdi;

	rdi = container_of(_ib_alloc_device(size), काष्ठा rvt_dev_info, ibdev);
	अगर (!rdi)
		वापस rdi;

	rdi->ports = kसुस्मृति(nports, माप(*rdi->ports), GFP_KERNEL);
	अगर (!rdi->ports)
		ib_dealloc_device(&rdi->ibdev);

	वापस rdi;
पूर्ण
EXPORT_SYMBOL(rvt_alloc_device);

/**
 * rvt_dealloc_device - deallocate rdi
 * @rdi: काष्ठाure to मुक्त
 *
 * Free a काष्ठाure allocated with rvt_alloc_device()
 */
व्योम rvt_dealloc_device(काष्ठा rvt_dev_info *rdi)
अणु
	kमुक्त(rdi->ports);
	ib_dealloc_device(&rdi->ibdev);
पूर्ण
EXPORT_SYMBOL(rvt_dealloc_device);

अटल पूर्णांक rvt_query_device(काष्ठा ib_device *ibdev,
			    काष्ठा ib_device_attr *props,
			    काष्ठा ib_udata *uhw)
अणु
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibdev);

	अगर (uhw->inlen || uhw->outlen)
		वापस -EINVAL;
	/*
	 * Return rvt_dev_info.dparms.props contents
	 */
	*props = rdi->dparms.props;
	वापस 0;
पूर्ण

अटल पूर्णांक rvt_modअगरy_device(काष्ठा ib_device *device,
			     पूर्णांक device_modअगरy_mask,
			     काष्ठा ib_device_modअगरy *device_modअगरy)
अणु
	/*
	 * There is currently no need to supply this based on qib and hfi1.
	 * Future drivers may need to implement this though.
	 */

	वापस -EOPNOTSUPP;
पूर्ण

/**
 * rvt_query_port: Passes the query port call to the driver
 * @ibdev: Verbs IB dev
 * @port_num: port number, 1 based from ib core
 * @props: काष्ठाure to hold वापसed properties
 *
 * Return: 0 on success
 */
अटल पूर्णांक rvt_query_port(काष्ठा ib_device *ibdev, u32 port_num,
			  काष्ठा ib_port_attr *props)
अणु
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibdev);
	काष्ठा rvt_ibport *rvp;
	u32 port_index = ibport_num_to_idx(ibdev, port_num);

	rvp = rdi->ports[port_index];
	/* props being zeroed by the caller, aव्योम zeroing it here */
	props->sm_lid = rvp->sm_lid;
	props->sm_sl = rvp->sm_sl;
	props->port_cap_flags = rvp->port_cap_flags;
	props->max_msg_sz = 0x80000000;
	props->pkey_tbl_len = rvt_get_npkeys(rdi);
	props->bad_pkey_cntr = rvp->pkey_violations;
	props->qkey_viol_cntr = rvp->qkey_violations;
	props->subnet_समयout = rvp->subnet_समयout;
	props->init_type_reply = 0;

	/* Populate the reमुख्यing ib_port_attr elements */
	वापस rdi->driver_f.query_port_state(rdi, port_num, props);
पूर्ण

/**
 * rvt_modअगरy_port
 * @ibdev: Verbs IB dev
 * @port_num: Port number, 1 based from ib core
 * @port_modअगरy_mask: How to change the port
 * @props: Structure to fill in
 *
 * Return: 0 on success
 */
अटल पूर्णांक rvt_modअगरy_port(काष्ठा ib_device *ibdev, u32 port_num,
			   पूर्णांक port_modअगरy_mask, काष्ठा ib_port_modअगरy *props)
अणु
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibdev);
	काष्ठा rvt_ibport *rvp;
	पूर्णांक ret = 0;
	u32 port_index = ibport_num_to_idx(ibdev, port_num);

	rvp = rdi->ports[port_index];
	अगर (port_modअगरy_mask & IB_PORT_OPA_MASK_CHG) अणु
		rvp->port_cap3_flags |= props->set_port_cap_mask;
		rvp->port_cap3_flags &= ~props->clr_port_cap_mask;
	पूर्ण अन्यथा अणु
		rvp->port_cap_flags |= props->set_port_cap_mask;
		rvp->port_cap_flags &= ~props->clr_port_cap_mask;
	पूर्ण

	अगर (props->set_port_cap_mask || props->clr_port_cap_mask)
		rdi->driver_f.cap_mask_chg(rdi, port_num);
	अगर (port_modअगरy_mask & IB_PORT_SHUTDOWN)
		ret = rdi->driver_f.shut_करोwn_port(rdi, port_num);
	अगर (port_modअगरy_mask & IB_PORT_RESET_QKEY_CNTR)
		rvp->qkey_violations = 0;

	वापस ret;
पूर्ण

/**
 * rvt_query_pkey - Return a pkey from the table at a given index
 * @ibdev: Verbs IB dev
 * @port_num: Port number, 1 based from ib core
 * @index: Index पूर्णांकo pkey table
 * @pkey: वापसed pkey from the port pkey table
 *
 * Return: 0 on failure pkey otherwise
 */
अटल पूर्णांक rvt_query_pkey(काष्ठा ib_device *ibdev, u32 port_num, u16 index,
			  u16 *pkey)
अणु
	/*
	 * Driver will be responsible क्रम keeping rvt_dev_info.pkey_table up to
	 * date. This function will just वापस that value. There is no need to
	 * lock, अगर a stale value is पढ़ो and sent to the user so be it there is
	 * no way to protect against that anyway.
	 */
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibdev);
	u32 port_index;

	port_index = ibport_num_to_idx(ibdev, port_num);

	अगर (index >= rvt_get_npkeys(rdi))
		वापस -EINVAL;

	*pkey = rvt_get_pkey(rdi, port_index, index);
	वापस 0;
पूर्ण

/**
 * rvt_query_gid - Return a gid from the table
 * @ibdev: Verbs IB dev
 * @port_num: Port number, 1 based from ib core
 * @guid_index: Index in table
 * @gid: Gid to वापस
 *
 * Return: 0 on success
 */
अटल पूर्णांक rvt_query_gid(काष्ठा ib_device *ibdev, u32 port_num,
			 पूर्णांक guid_index, जोड़ ib_gid *gid)
अणु
	काष्ठा rvt_dev_info *rdi;
	काष्ठा rvt_ibport *rvp;
	u32 port_index;

	/*
	 * Driver is responsible क्रम updating the guid table. Which will be used
	 * to craft the वापस value. This will work similar to how query_pkey()
	 * is being करोne.
	 */
	port_index = ibport_num_to_idx(ibdev, port_num);

	rdi = ib_to_rvt(ibdev);
	rvp = rdi->ports[port_index];

	gid->global.subnet_prefix = rvp->gid_prefix;

	वापस rdi->driver_f.get_guid_be(rdi, rvp, guid_index,
					 &gid->global.पूर्णांकerface_id);
पूर्ण

/**
 * rvt_alloc_ucontext - Allocate a user context
 * @uctx: Verbs context
 * @udata: User data allocated
 */
अटल पूर्णांक rvt_alloc_ucontext(काष्ठा ib_ucontext *uctx, काष्ठा ib_udata *udata)
अणु
	वापस 0;
पूर्ण

/**
 * rvt_dealloc_ucontext - Free a user context
 * @context: Unused
 */
अटल व्योम rvt_dealloc_ucontext(काष्ठा ib_ucontext *context)
अणु
	वापस;
पूर्ण

अटल पूर्णांक rvt_get_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
				  काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibdev);
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	immutable->core_cap_flags = rdi->dparms.core_cap_flags;

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->max_mad_size = rdi->dparms.max_mad_size;

	वापस 0;
पूर्ण

क्रमागत अणु
	MISC,
	QUERY_DEVICE,
	MODIFY_DEVICE,
	QUERY_PORT,
	MODIFY_PORT,
	QUERY_PKEY,
	QUERY_GID,
	ALLOC_UCONTEXT,
	DEALLOC_UCONTEXT,
	GET_PORT_IMMUTABLE,
	CREATE_QP,
	MODIFY_QP,
	DESTROY_QP,
	QUERY_QP,
	POST_SEND,
	POST_RECV,
	POST_SRQ_RECV,
	CREATE_AH,
	DESTROY_AH,
	MODIFY_AH,
	QUERY_AH,
	CREATE_SRQ,
	MODIFY_SRQ,
	DESTROY_SRQ,
	QUERY_SRQ,
	ATTACH_MCAST,
	DETACH_MCAST,
	GET_DMA_MR,
	REG_USER_MR,
	DEREG_MR,
	ALLOC_MR,
	MAP_MR_SG,
	ALLOC_FMR,
	MAP_PHYS_FMR,
	UNMAP_FMR,
	DEALLOC_FMR,
	MMAP,
	CREATE_CQ,
	DESTROY_CQ,
	POLL_CQ,
	REQ_NOTFIY_CQ,
	RESIZE_CQ,
	ALLOC_PD,
	DEALLOC_PD,
	_VERB_IDX_MAX /* Must always be last! */
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops rvt_dev_ops = अणु
	.uverbs_abi_ver = RVT_UVERBS_ABI_VERSION,

	.alloc_mr = rvt_alloc_mr,
	.alloc_pd = rvt_alloc_pd,
	.alloc_ucontext = rvt_alloc_ucontext,
	.attach_mcast = rvt_attach_mcast,
	.create_ah = rvt_create_ah,
	.create_cq = rvt_create_cq,
	.create_qp = rvt_create_qp,
	.create_srq = rvt_create_srq,
	.create_user_ah = rvt_create_ah,
	.dealloc_pd = rvt_dealloc_pd,
	.dealloc_ucontext = rvt_dealloc_ucontext,
	.dereg_mr = rvt_dereg_mr,
	.destroy_ah = rvt_destroy_ah,
	.destroy_cq = rvt_destroy_cq,
	.destroy_qp = rvt_destroy_qp,
	.destroy_srq = rvt_destroy_srq,
	.detach_mcast = rvt_detach_mcast,
	.get_dma_mr = rvt_get_dma_mr,
	.get_port_immutable = rvt_get_port_immutable,
	.map_mr_sg = rvt_map_mr_sg,
	.mmap = rvt_mmap,
	.modअगरy_ah = rvt_modअगरy_ah,
	.modअगरy_device = rvt_modअगरy_device,
	.modअगरy_port = rvt_modअगरy_port,
	.modअगरy_qp = rvt_modअगरy_qp,
	.modअगरy_srq = rvt_modअगरy_srq,
	.poll_cq = rvt_poll_cq,
	.post_recv = rvt_post_recv,
	.post_send = rvt_post_send,
	.post_srq_recv = rvt_post_srq_recv,
	.query_ah = rvt_query_ah,
	.query_device = rvt_query_device,
	.query_gid = rvt_query_gid,
	.query_pkey = rvt_query_pkey,
	.query_port = rvt_query_port,
	.query_qp = rvt_query_qp,
	.query_srq = rvt_query_srq,
	.reg_user_mr = rvt_reg_user_mr,
	.req_notअगरy_cq = rvt_req_notअगरy_cq,
	.resize_cq = rvt_resize_cq,

	INIT_RDMA_OBJ_SIZE(ib_ah, rvt_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_cq, rvt_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_pd, rvt_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_srq, rvt_srq, ibsrq),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, rvt_ucontext, ibucontext),
पूर्ण;

अटल noअंतरभूत पूर्णांक check_support(काष्ठा rvt_dev_info *rdi, पूर्णांक verb)
अणु
	चयन (verb) अणु
	हाल MISC:
		/*
		 * These functions are not part of verbs specअगरically but are
		 * required क्रम rdmavt to function.
		 */
		अगर ((!rdi->ibdev.ops.init_port) ||
		    (!rdi->driver_f.get_pci_dev))
			वापस -EINVAL;
		अवरोध;

	हाल MODIFY_DEVICE:
		/*
		 * rdmavt करोes not support modअगरy device currently drivers must
		 * provide.
		 */
		अगर (!rdi->ibdev.ops.modअगरy_device)
			वापस -EOPNOTSUPP;
		अवरोध;

	हाल QUERY_PORT:
		अगर (!rdi->ibdev.ops.query_port)
			अगर (!rdi->driver_f.query_port_state)
				वापस -EINVAL;
		अवरोध;

	हाल MODIFY_PORT:
		अगर (!rdi->ibdev.ops.modअगरy_port)
			अगर (!rdi->driver_f.cap_mask_chg ||
			    !rdi->driver_f.shut_करोwn_port)
				वापस -EINVAL;
		अवरोध;

	हाल QUERY_GID:
		अगर (!rdi->ibdev.ops.query_gid)
			अगर (!rdi->driver_f.get_guid_be)
				वापस -EINVAL;
		अवरोध;

	हाल CREATE_QP:
		अगर (!rdi->ibdev.ops.create_qp)
			अगर (!rdi->driver_f.qp_priv_alloc ||
			    !rdi->driver_f.qp_priv_मुक्त ||
			    !rdi->driver_f.notअगरy_qp_reset ||
			    !rdi->driver_f.flush_qp_रुकोers ||
			    !rdi->driver_f.stop_send_queue ||
			    !rdi->driver_f.quiesce_qp)
				वापस -EINVAL;
		अवरोध;

	हाल MODIFY_QP:
		अगर (!rdi->ibdev.ops.modअगरy_qp)
			अगर (!rdi->driver_f.notअगरy_qp_reset ||
			    !rdi->driver_f.schedule_send ||
			    !rdi->driver_f.get_pmtu_from_attr ||
			    !rdi->driver_f.flush_qp_रुकोers ||
			    !rdi->driver_f.stop_send_queue ||
			    !rdi->driver_f.quiesce_qp ||
			    !rdi->driver_f.notअगरy_error_qp ||
			    !rdi->driver_f.mtu_from_qp ||
			    !rdi->driver_f.mtu_to_path_mtu)
				वापस -EINVAL;
		अवरोध;

	हाल DESTROY_QP:
		अगर (!rdi->ibdev.ops.destroy_qp)
			अगर (!rdi->driver_f.qp_priv_मुक्त ||
			    !rdi->driver_f.notअगरy_qp_reset ||
			    !rdi->driver_f.flush_qp_रुकोers ||
			    !rdi->driver_f.stop_send_queue ||
			    !rdi->driver_f.quiesce_qp)
				वापस -EINVAL;
		अवरोध;

	हाल POST_SEND:
		अगर (!rdi->ibdev.ops.post_send)
			अगर (!rdi->driver_f.schedule_send ||
			    !rdi->driver_f.करो_send ||
			    !rdi->post_parms)
				वापस -EINVAL;
		अवरोध;

	पूर्ण

	वापस 0;
पूर्ण

/**
 * rvt_रेजिस्टर_device - रेजिस्टर a driver
 * @rdi: मुख्य dev काष्ठाure क्रम all of rdmavt operations
 *
 * It is up to drivers to allocate the rdi and fill in the appropriate
 * inक्रमmation.
 *
 * Return: 0 on success otherwise an त्रुटि_सं.
 */
पूर्णांक rvt_रेजिस्टर_device(काष्ठा rvt_dev_info *rdi)
अणु
	पूर्णांक ret = 0, i;

	अगर (!rdi)
		वापस -EINVAL;

	/*
	 * Check to ensure drivers have setup the required helpers क्रम the verbs
	 * they want rdmavt to handle
	 */
	क्रम (i = 0; i < _VERB_IDX_MAX; i++)
		अगर (check_support(rdi, i)) अणु
			pr_err("Driver support req not met at %d\n", i);
			वापस -EINVAL;
		पूर्ण

	ib_set_device_ops(&rdi->ibdev, &rvt_dev_ops);

	/* Once we get past here we can use rvt_pr macros and tracepoपूर्णांकs */
	trace_rvt_dbg(rdi, "Driver attempting registration");
	rvt_mmap_init(rdi);

	/* Queue Pairs */
	ret = rvt_driver_qp_init(rdi);
	अगर (ret) अणु
		pr_err("Error in driver QP init.\n");
		वापस -EINVAL;
	पूर्ण

	/* Address Handle */
	spin_lock_init(&rdi->n_ahs_lock);
	rdi->n_ahs_allocated = 0;

	/* Shared Receive Queue */
	rvt_driver_srq_init(rdi);

	/* Multicast */
	rvt_driver_mcast_init(rdi);

	/* Mem Region */
	ret = rvt_driver_mr_init(rdi);
	अगर (ret) अणु
		pr_err("Error in driver MR init.\n");
		जाओ bail_no_mr;
	पूर्ण

	/* Memory Working Set Size */
	ret = rvt_wss_init(rdi);
	अगर (ret) अणु
		rvt_pr_err(rdi, "Error in WSS init.\n");
		जाओ bail_mr;
	पूर्ण

	/* Completion queues */
	spin_lock_init(&rdi->n_cqs_lock);

	/* Protection Doमुख्य */
	spin_lock_init(&rdi->n_pds_lock);
	rdi->n_pds_allocated = 0;

	/*
	 * There are some things which could be set by underlying drivers but
	 * really should be up to rdmavt to set. For instance drivers can't know
	 * exactly which functions rdmavt supports, nor करो they know the ABI
	 * version, so we करो all of this sort of stuff here.
	 */
	rdi->ibdev.uverbs_cmd_mask |=
		(1ull << IB_USER_VERBS_CMD_POLL_CQ)             |
		(1ull << IB_USER_VERBS_CMD_REQ_NOTIFY_CQ)       |
		(1ull << IB_USER_VERBS_CMD_POST_SEND)           |
		(1ull << IB_USER_VERBS_CMD_POST_RECV)           |
		(1ull << IB_USER_VERBS_CMD_POST_SRQ_RECV);
	rdi->ibdev.node_type = RDMA_NODE_IB_CA;
	अगर (!rdi->ibdev.num_comp_vectors)
		rdi->ibdev.num_comp_vectors = 1;

	/* We are now good to announce we exist */
	ret = ib_रेजिस्टर_device(&rdi->ibdev, dev_name(&rdi->ibdev.dev), शून्य);
	अगर (ret) अणु
		rvt_pr_err(rdi, "Failed to register driver with ib core.\n");
		जाओ bail_wss;
	पूर्ण

	rvt_create_mad_agents(rdi);

	rvt_pr_info(rdi, "Registration with rdmavt done.\n");
	वापस ret;

bail_wss:
	rvt_wss_निकास(rdi);
bail_mr:
	rvt_mr_निकास(rdi);

bail_no_mr:
	rvt_qp_निकास(rdi);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(rvt_रेजिस्टर_device);

/**
 * rvt_unरेजिस्टर_device - हटाओ a driver
 * @rdi: rvt dev काष्ठा
 */
व्योम rvt_unरेजिस्टर_device(काष्ठा rvt_dev_info *rdi)
अणु
	trace_rvt_dbg(rdi, "Driver is unregistering.");
	अगर (!rdi)
		वापस;

	rvt_मुक्त_mad_agents(rdi);

	ib_unरेजिस्टर_device(&rdi->ibdev);
	rvt_wss_निकास(rdi);
	rvt_mr_निकास(rdi);
	rvt_qp_निकास(rdi);
पूर्ण
EXPORT_SYMBOL(rvt_unरेजिस्टर_device);

/**
 * rvt_init_port - init पूर्णांकernal data क्रम driver port
 * @rdi: rvt_dev_info काष्ठा
 * @port: rvt port
 * @port_index: 0 based index of ports, dअगरferent from IB core port num
 * @pkey_table: pkey_table क्रम @port
 *
 * Keep track of a list of ports. No need to have a detach port.
 * They persist until the driver goes away.
 *
 * Return: always 0
 */
पूर्णांक rvt_init_port(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_ibport *port,
		  पूर्णांक port_index, u16 *pkey_table)
अणु

	rdi->ports[port_index] = port;
	rdi->ports[port_index]->pkey_table = pkey_table;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rvt_init_port);
