<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "usnic_abi.h"
#समावेश "usnic_ib.h"
#समावेश "usnic_common_util.h"
#समावेश "usnic_ib_qp_grp.h"
#समावेश "usnic_ib_verbs.h"
#समावेश "usnic_fwd.h"
#समावेश "usnic_log.h"
#समावेश "usnic_uiom.h"
#समावेश "usnic_transport.h"

#घोषणा USNIC_DEFAULT_TRANSPORT USNIC_TRANSPORT_ROCE_CUSTOM

स्थिर काष्ठा usnic_vnic_res_spec min_transport_spec[USNIC_TRANSPORT_MAX] = अणु
	अणु /*USNIC_TRANSPORT_UNKNOWN*/
		.resources = अणु
			अणु.type = USNIC_VNIC_RES_TYPE_EOL,	.cnt = 0,पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु /*USNIC_TRANSPORT_ROCE_CUSTOM*/
		.resources = अणु
			अणु.type = USNIC_VNIC_RES_TYPE_WQ,	.cnt = 1,पूर्ण,
			अणु.type = USNIC_VNIC_RES_TYPE_RQ,	.cnt = 1,पूर्ण,
			अणु.type = USNIC_VNIC_RES_TYPE_CQ,	.cnt = 1,पूर्ण,
			अणु.type = USNIC_VNIC_RES_TYPE_EOL,	.cnt = 0,पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु /*USNIC_TRANSPORT_IPV4_UDP*/
		.resources = अणु
			अणु.type = USNIC_VNIC_RES_TYPE_WQ,	.cnt = 1,पूर्ण,
			अणु.type = USNIC_VNIC_RES_TYPE_RQ,	.cnt = 1,पूर्ण,
			अणु.type = USNIC_VNIC_RES_TYPE_CQ,	.cnt = 1,पूर्ण,
			अणु.type = USNIC_VNIC_RES_TYPE_EOL,	.cnt = 0,पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम usnic_ib_fw_string_to_u64(अक्षर *fw_ver_str, u64 *fw_ver)
अणु
	*fw_ver = *((u64 *)fw_ver_str);
पूर्ण

अटल पूर्णांक usnic_ib_fill_create_qp_resp(काष्ठा usnic_ib_qp_grp *qp_grp,
					काष्ठा ib_udata *udata)
अणु
	काष्ठा usnic_ib_dev *us_ibdev;
	काष्ठा usnic_ib_create_qp_resp resp;
	काष्ठा pci_dev *pdev;
	काष्ठा vnic_dev_bar *bar;
	काष्ठा usnic_vnic_res_chunk *chunk;
	काष्ठा usnic_ib_qp_grp_flow *शेष_flow;
	पूर्णांक i, err;

	स_रखो(&resp, 0, माप(resp));

	us_ibdev = qp_grp->vf->pf;
	pdev = usnic_vnic_get_pdev(qp_grp->vf->vnic);
	अगर (!pdev) अणु
		usnic_err("Failed to get pdev of qp_grp %d\n",
				qp_grp->grp_id);
		वापस -EFAULT;
	पूर्ण

	bar = usnic_vnic_get_bar(qp_grp->vf->vnic, 0);
	अगर (!bar) अणु
		usnic_err("Failed to get bar0 of qp_grp %d vf %s",
				qp_grp->grp_id, pci_name(pdev));
		वापस -EFAULT;
	पूर्ण

	resp.vfid = usnic_vnic_get_index(qp_grp->vf->vnic);
	resp.bar_bus_addr = bar->bus_addr;
	resp.bar_len = bar->len;

	chunk = usnic_ib_qp_grp_get_chunk(qp_grp, USNIC_VNIC_RES_TYPE_RQ);
	अगर (IS_ERR(chunk)) अणु
		usnic_err("Failed to get chunk %s for qp_grp %d with err %ld\n",
			usnic_vnic_res_type_to_str(USNIC_VNIC_RES_TYPE_RQ),
			qp_grp->grp_id,
			PTR_ERR(chunk));
		वापस PTR_ERR(chunk);
	पूर्ण

	WARN_ON(chunk->type != USNIC_VNIC_RES_TYPE_RQ);
	resp.rq_cnt = chunk->cnt;
	क्रम (i = 0; i < chunk->cnt; i++)
		resp.rq_idx[i] = chunk->res[i]->vnic_idx;

	chunk = usnic_ib_qp_grp_get_chunk(qp_grp, USNIC_VNIC_RES_TYPE_WQ);
	अगर (IS_ERR(chunk)) अणु
		usnic_err("Failed to get chunk %s for qp_grp %d with err %ld\n",
			usnic_vnic_res_type_to_str(USNIC_VNIC_RES_TYPE_WQ),
			qp_grp->grp_id,
			PTR_ERR(chunk));
		वापस PTR_ERR(chunk);
	पूर्ण

	WARN_ON(chunk->type != USNIC_VNIC_RES_TYPE_WQ);
	resp.wq_cnt = chunk->cnt;
	क्रम (i = 0; i < chunk->cnt; i++)
		resp.wq_idx[i] = chunk->res[i]->vnic_idx;

	chunk = usnic_ib_qp_grp_get_chunk(qp_grp, USNIC_VNIC_RES_TYPE_CQ);
	अगर (IS_ERR(chunk)) अणु
		usnic_err("Failed to get chunk %s for qp_grp %d with err %ld\n",
			usnic_vnic_res_type_to_str(USNIC_VNIC_RES_TYPE_CQ),
			qp_grp->grp_id,
			PTR_ERR(chunk));
		वापस PTR_ERR(chunk);
	पूर्ण

	WARN_ON(chunk->type != USNIC_VNIC_RES_TYPE_CQ);
	resp.cq_cnt = chunk->cnt;
	क्रम (i = 0; i < chunk->cnt; i++)
		resp.cq_idx[i] = chunk->res[i]->vnic_idx;

	शेष_flow = list_first_entry(&qp_grp->flows_lst,
					काष्ठा usnic_ib_qp_grp_flow, link);
	resp.transport = शेष_flow->trans_type;

	err = ib_copy_to_udata(udata, &resp, माप(resp));
	अगर (err) अणु
		usnic_err("Failed to copy udata for %s",
			  dev_name(&us_ibdev->ib_dev.dev));
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा usnic_ib_qp_grp*
find_मुक्त_vf_and_create_qp_grp(काष्ठा usnic_ib_dev *us_ibdev,
				काष्ठा usnic_ib_pd *pd,
				काष्ठा usnic_transport_spec *trans_spec,
				काष्ठा usnic_vnic_res_spec *res_spec)
अणु
	काष्ठा usnic_ib_vf *vf;
	काष्ठा usnic_vnic *vnic;
	काष्ठा usnic_ib_qp_grp *qp_grp;
	काष्ठा device *dev, **dev_list;
	पूर्णांक i;

	BUG_ON(!mutex_is_locked(&us_ibdev->usdev_lock));

	अगर (list_empty(&us_ibdev->vf_dev_list)) अणु
		usnic_info("No vfs to allocate\n");
		वापस शून्य;
	पूर्ण

	अगर (usnic_ib_share_vf) अणु
		/* Try to find resouces on a used vf which is in pd */
		dev_list = usnic_uiom_get_dev_list(pd->umem_pd);
		अगर (IS_ERR(dev_list))
			वापस ERR_CAST(dev_list);
		क्रम (i = 0; dev_list[i]; i++) अणु
			dev = dev_list[i];
			vf = dev_get_drvdata(dev);
			spin_lock(&vf->lock);
			vnic = vf->vnic;
			अगर (!usnic_vnic_check_room(vnic, res_spec)) अणु
				usnic_dbg("Found used vnic %s from %s\n",
						dev_name(&us_ibdev->ib_dev.dev),
						pci_name(usnic_vnic_get_pdev(
									vnic)));
				qp_grp = usnic_ib_qp_grp_create(us_ibdev->ufdev,
								vf, pd,
								res_spec,
								trans_spec);

				spin_unlock(&vf->lock);
				जाओ qp_grp_check;
			पूर्ण
			spin_unlock(&vf->lock);

		पूर्ण
		usnic_uiom_मुक्त_dev_list(dev_list);
		dev_list = शून्य;
	पूर्ण

	/* Try to find resources on an unused vf */
	list_क्रम_each_entry(vf, &us_ibdev->vf_dev_list, link) अणु
		spin_lock(&vf->lock);
		vnic = vf->vnic;
		अगर (vf->qp_grp_ref_cnt == 0 &&
		    usnic_vnic_check_room(vnic, res_spec) == 0) अणु
			qp_grp = usnic_ib_qp_grp_create(us_ibdev->ufdev, vf,
							pd, res_spec,
							trans_spec);

			spin_unlock(&vf->lock);
			जाओ qp_grp_check;
		पूर्ण
		spin_unlock(&vf->lock);
	पूर्ण

	usnic_info("No free qp grp found on %s\n",
		   dev_name(&us_ibdev->ib_dev.dev));
	वापस ERR_PTR(-ENOMEM);

qp_grp_check:
	अगर (IS_ERR_OR_शून्य(qp_grp)) अणु
		usnic_err("Failed to allocate qp_grp\n");
		अगर (usnic_ib_share_vf)
			usnic_uiom_मुक्त_dev_list(dev_list);
		वापस ERR_PTR(qp_grp ? PTR_ERR(qp_grp) : -ENOMEM);
	पूर्ण
	वापस qp_grp;
पूर्ण

अटल व्योम qp_grp_destroy(काष्ठा usnic_ib_qp_grp *qp_grp)
अणु
	काष्ठा usnic_ib_vf *vf = qp_grp->vf;

	WARN_ON(qp_grp->state != IB_QPS_RESET);

	spin_lock(&vf->lock);
	usnic_ib_qp_grp_destroy(qp_grp);
	spin_unlock(&vf->lock);
पूर्ण

अटल पूर्णांक create_qp_validate_user_data(काष्ठा usnic_ib_create_qp_cmd cmd)
अणु
	अगर (cmd.spec.trans_type <= USNIC_TRANSPORT_UNKNOWN ||
			cmd.spec.trans_type >= USNIC_TRANSPORT_MAX)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Start of ib callback functions */

क्रमागत rdma_link_layer usnic_ib_port_link_layer(काष्ठा ib_device *device,
					      u32 port_num)
अणु
	वापस IB_LINK_LAYER_ETHERNET;
पूर्ण

पूर्णांक usnic_ib_query_device(काष्ठा ib_device *ibdev,
			  काष्ठा ib_device_attr *props,
			  काष्ठा ib_udata *uhw)
अणु
	काष्ठा usnic_ib_dev *us_ibdev = to_usdev(ibdev);
	जोड़ ib_gid gid;
	काष्ठा ethtool_drvinfo info;
	पूर्णांक qp_per_vf;

	usnic_dbg("\n");
	अगर (uhw->inlen || uhw->outlen)
		वापस -EINVAL;

	mutex_lock(&us_ibdev->usdev_lock);
	us_ibdev->netdev->ethtool_ops->get_drvinfo(us_ibdev->netdev, &info);
	स_रखो(props, 0, माप(*props));
	usnic_mac_ip_to_gid(us_ibdev->ufdev->mac, us_ibdev->ufdev->inaddr,
			&gid.raw[0]);
	स_नकल(&props->sys_image_guid, &gid.global.पूर्णांकerface_id,
		माप(gid.global.पूर्णांकerface_id));
	usnic_ib_fw_string_to_u64(&info.fw_version[0], &props->fw_ver);
	props->max_mr_size = USNIC_UIOM_MAX_MR_SIZE;
	props->page_size_cap = USNIC_UIOM_PAGE_SIZE;
	props->venकरोr_id = PCI_VENDOR_ID_CISCO;
	props->venकरोr_part_id = PCI_DEVICE_ID_CISCO_VIC_USPACE_NIC;
	props->hw_ver = us_ibdev->pdev->subप्रणाली_device;
	qp_per_vf = max(us_ibdev->vf_res_cnt[USNIC_VNIC_RES_TYPE_WQ],
			us_ibdev->vf_res_cnt[USNIC_VNIC_RES_TYPE_RQ]);
	props->max_qp = qp_per_vf *
		kref_पढ़ो(&us_ibdev->vf_cnt);
	props->device_cap_flags = IB_DEVICE_PORT_ACTIVE_EVENT |
		IB_DEVICE_SYS_IMAGE_GUID | IB_DEVICE_BLOCK_MULTICAST_LOOPBACK;
	props->max_cq = us_ibdev->vf_res_cnt[USNIC_VNIC_RES_TYPE_CQ] *
		kref_पढ़ो(&us_ibdev->vf_cnt);
	props->max_pd = USNIC_UIOM_MAX_PD_CNT;
	props->max_mr = USNIC_UIOM_MAX_MR_CNT;
	props->local_ca_ack_delay = 0;
	props->max_pkeys = 0;
	props->atomic_cap = IB_ATOMIC_NONE;
	props->masked_atomic_cap = props->atomic_cap;
	props->max_qp_rd_atom = 0;
	props->max_qp_init_rd_atom = 0;
	props->max_res_rd_atom = 0;
	props->max_srq = 0;
	props->max_srq_wr = 0;
	props->max_srq_sge = 0;
	props->max_fast_reg_page_list_len = 0;
	props->max_mcast_grp = 0;
	props->max_mcast_qp_attach = 0;
	props->max_total_mcast_qp_attach = 0;
	/* Owned by Userspace
	 * max_qp_wr, max_sge, max_sge_rd, max_cqe */
	mutex_unlock(&us_ibdev->usdev_lock);

	वापस 0;
पूर्ण

पूर्णांक usnic_ib_query_port(काष्ठा ib_device *ibdev, u32 port,
				काष्ठा ib_port_attr *props)
अणु
	काष्ठा usnic_ib_dev *us_ibdev = to_usdev(ibdev);

	usnic_dbg("\n");

	अगर (ib_get_eth_speed(ibdev, port, &props->active_speed,
			     &props->active_width))
		वापस -EINVAL;

	/*
	 * usdev_lock is acquired after (and not beक्रमe) ib_get_eth_speed call
	 * because acquiring rtnl_lock in ib_get_eth_speed, जबतक holding
	 * usdev_lock could lead to a deadlock.
	 */
	mutex_lock(&us_ibdev->usdev_lock);
	/* props being zeroed by the caller, aव्योम zeroing it here */

	props->lid = 0;
	props->lmc = 1;
	props->sm_lid = 0;
	props->sm_sl = 0;

	अगर (!us_ibdev->ufdev->link_up) अणु
		props->state = IB_PORT_DOWN;
		props->phys_state = IB_PORT_PHYS_STATE_DISABLED;
	पूर्ण अन्यथा अगर (!us_ibdev->ufdev->inaddr) अणु
		props->state = IB_PORT_INIT;
		props->phys_state =
			IB_PORT_PHYS_STATE_PORT_CONFIGURATION_TRAINING;
	पूर्ण अन्यथा अणु
		props->state = IB_PORT_ACTIVE;
		props->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	पूर्ण

	props->port_cap_flags = 0;
	props->gid_tbl_len = 1;
	props->bad_pkey_cntr = 0;
	props->qkey_viol_cntr = 0;
	props->max_mtu = IB_MTU_4096;
	props->active_mtu = iboe_get_mtu(us_ibdev->ufdev->mtu);
	/* Userspace will adjust क्रम hdrs */
	props->max_msg_sz = us_ibdev->ufdev->mtu;
	props->max_vl_num = 1;
	mutex_unlock(&us_ibdev->usdev_lock);

	वापस 0;
पूर्ण

पूर्णांक usnic_ib_query_qp(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *qp_attr,
				पूर्णांक qp_attr_mask,
				काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा usnic_ib_qp_grp *qp_grp;
	काष्ठा usnic_ib_vf *vf;
	पूर्णांक err;

	usnic_dbg("\n");

	स_रखो(qp_attr, 0, माप(*qp_attr));
	स_रखो(qp_init_attr, 0, माप(*qp_init_attr));

	qp_grp = to_uqp_grp(qp);
	vf = qp_grp->vf;
	mutex_lock(&vf->pf->usdev_lock);
	usnic_dbg("\n");
	qp_attr->qp_state = qp_grp->state;
	qp_attr->cur_qp_state = qp_grp->state;

	चयन (qp_grp->ibqp.qp_type) अणु
	हाल IB_QPT_UD:
		qp_attr->qkey = 0;
		अवरोध;
	शेष:
		usnic_err("Unexpected qp_type %d\n", qp_grp->ibqp.qp_type);
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	mutex_unlock(&vf->pf->usdev_lock);
	वापस 0;

err_out:
	mutex_unlock(&vf->pf->usdev_lock);
	वापस err;
पूर्ण

पूर्णांक usnic_ib_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
				जोड़ ib_gid *gid)
अणु

	काष्ठा usnic_ib_dev *us_ibdev = to_usdev(ibdev);
	usnic_dbg("\n");

	अगर (index > 1)
		वापस -EINVAL;

	mutex_lock(&us_ibdev->usdev_lock);
	स_रखो(&(gid->raw[0]), 0, माप(gid->raw));
	usnic_mac_ip_to_gid(us_ibdev->ufdev->mac, us_ibdev->ufdev->inaddr,
			&gid->raw[0]);
	mutex_unlock(&us_ibdev->usdev_lock);

	वापस 0;
पूर्ण

पूर्णांक usnic_ib_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा usnic_ib_pd *pd = to_upd(ibpd);
	व्योम *umem_pd;

	umem_pd = pd->umem_pd = usnic_uiom_alloc_pd();
	अगर (IS_ERR_OR_शून्य(umem_pd)) अणु
		वापस umem_pd ? PTR_ERR(umem_pd) : -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक usnic_ib_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	usnic_uiom_dealloc_pd((to_upd(pd))->umem_pd);
	वापस 0;
पूर्ण

काष्ठा ib_qp *usnic_ib_create_qp(काष्ठा ib_pd *pd,
					काष्ठा ib_qp_init_attr *init_attr,
					काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा usnic_ib_dev *us_ibdev;
	काष्ठा usnic_ib_qp_grp *qp_grp;
	काष्ठा usnic_ib_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा usnic_ib_ucontext, ibucontext);
	पूर्णांक cq_cnt;
	काष्ठा usnic_vnic_res_spec res_spec;
	काष्ठा usnic_ib_create_qp_cmd cmd;
	काष्ठा usnic_transport_spec trans_spec;

	usnic_dbg("\n");

	us_ibdev = to_usdev(pd->device);

	अगर (init_attr->create_flags)
		वापस ERR_PTR(-EOPNOTSUPP);

	err = ib_copy_from_udata(&cmd, udata, माप(cmd));
	अगर (err) अणु
		usnic_err("%s: cannot copy udata for create_qp\n",
			  dev_name(&us_ibdev->ib_dev.dev));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	err = create_qp_validate_user_data(cmd);
	अगर (err) अणु
		usnic_err("%s: Failed to validate user data\n",
			  dev_name(&us_ibdev->ib_dev.dev));
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (init_attr->qp_type != IB_QPT_UD) अणु
		usnic_err("%s asked to make a non-UD QP: %d\n",
			  dev_name(&us_ibdev->ib_dev.dev), init_attr->qp_type);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	trans_spec = cmd.spec;
	mutex_lock(&us_ibdev->usdev_lock);
	cq_cnt = (init_attr->send_cq == init_attr->recv_cq) ? 1 : 2;
	res_spec = min_transport_spec[trans_spec.trans_type];
	usnic_vnic_res_spec_update(&res_spec, USNIC_VNIC_RES_TYPE_CQ, cq_cnt);
	qp_grp = find_मुक्त_vf_and_create_qp_grp(us_ibdev, to_upd(pd),
						&trans_spec,
						&res_spec);
	अगर (IS_ERR_OR_शून्य(qp_grp)) अणु
		err = qp_grp ? PTR_ERR(qp_grp) : -ENOMEM;
		जाओ out_release_mutex;
	पूर्ण

	err = usnic_ib_fill_create_qp_resp(qp_grp, udata);
	अगर (err) अणु
		err = -EBUSY;
		जाओ out_release_qp_grp;
	पूर्ण

	qp_grp->ctx = ucontext;
	list_add_tail(&qp_grp->link, &ucontext->qp_grp_list);
	usnic_ib_log_vf(qp_grp->vf);
	mutex_unlock(&us_ibdev->usdev_lock);
	वापस &qp_grp->ibqp;

out_release_qp_grp:
	qp_grp_destroy(qp_grp);
out_release_mutex:
	mutex_unlock(&us_ibdev->usdev_lock);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक usnic_ib_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata)
अणु
	काष्ठा usnic_ib_qp_grp *qp_grp;
	काष्ठा usnic_ib_vf *vf;

	usnic_dbg("\n");

	qp_grp = to_uqp_grp(qp);
	vf = qp_grp->vf;
	mutex_lock(&vf->pf->usdev_lock);
	अगर (usnic_ib_qp_grp_modअगरy(qp_grp, IB_QPS_RESET, शून्य)) अणु
		usnic_err("Failed to move qp grp %u to reset\n",
				qp_grp->grp_id);
	पूर्ण

	list_del(&qp_grp->link);
	qp_grp_destroy(qp_grp);
	mutex_unlock(&vf->pf->usdev_lock);

	वापस 0;
पूर्ण

पूर्णांक usnic_ib_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
				पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा usnic_ib_qp_grp *qp_grp;
	पूर्णांक status;
	usnic_dbg("\n");

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	qp_grp = to_uqp_grp(ibqp);

	mutex_lock(&qp_grp->vf->pf->usdev_lock);
	अगर ((attr_mask & IB_QP_PORT) && attr->port_num != 1) अणु
		/* usnic devices only have one port */
		status = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (attr_mask & IB_QP_STATE) अणु
		status = usnic_ib_qp_grp_modअगरy(qp_grp, attr->qp_state, शून्य);
	पूर्ण अन्यथा अणु
		usnic_err("Unhandled request, attr_mask=0x%x\n", attr_mask);
		status = -EINVAL;
	पूर्ण

out_unlock:
	mutex_unlock(&qp_grp->vf->pf->usdev_lock);
	वापस status;
पूर्ण

पूर्णांक usnic_ib_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		       काष्ठा ib_udata *udata)
अणु
	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

पूर्णांक usnic_ib_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata)
अणु
	वापस 0;
पूर्ण

काष्ठा ib_mr *usnic_ib_reg_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
					u64 virt_addr, पूर्णांक access_flags,
					काष्ठा ib_udata *udata)
अणु
	काष्ठा usnic_ib_mr *mr;
	पूर्णांक err;

	usnic_dbg("start 0x%llx va 0x%llx length 0x%llx\n", start,
			virt_addr, length);

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->umem = usnic_uiom_reg_get(to_upd(pd)->umem_pd, start, length,
					access_flags, 0);
	अगर (IS_ERR_OR_शून्य(mr->umem)) अणु
		err = mr->umem ? PTR_ERR(mr->umem) : -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	mr->ibmr.lkey = mr->ibmr.rkey = 0;
	वापस &mr->ibmr;

err_मुक्त:
	kमुक्त(mr);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक usnic_ib_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata)
अणु
	काष्ठा usnic_ib_mr *mr = to_umr(ibmr);

	usnic_dbg("va 0x%lx length 0x%zx\n", mr->umem->va, mr->umem->length);

	usnic_uiom_reg_release(mr->umem);
	kमुक्त(mr);
	वापस 0;
पूर्ण

पूर्णांक usnic_ib_alloc_ucontext(काष्ठा ib_ucontext *uctx, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = uctx->device;
	काष्ठा usnic_ib_ucontext *context = to_ucontext(uctx);
	काष्ठा usnic_ib_dev *us_ibdev = to_usdev(ibdev);
	usnic_dbg("\n");

	INIT_LIST_HEAD(&context->qp_grp_list);
	mutex_lock(&us_ibdev->usdev_lock);
	list_add_tail(&context->link, &us_ibdev->ctx_list);
	mutex_unlock(&us_ibdev->usdev_lock);

	वापस 0;
पूर्ण

व्योम usnic_ib_dealloc_ucontext(काष्ठा ib_ucontext *ibcontext)
अणु
	काष्ठा usnic_ib_ucontext *context = to_uucontext(ibcontext);
	काष्ठा usnic_ib_dev *us_ibdev = to_usdev(ibcontext->device);
	usnic_dbg("\n");

	mutex_lock(&us_ibdev->usdev_lock);
	WARN_ON_ONCE(!list_empty(&context->qp_grp_list));
	list_del(&context->link);
	mutex_unlock(&us_ibdev->usdev_lock);
पूर्ण

पूर्णांक usnic_ib_mmap(काष्ठा ib_ucontext *context,
				काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा usnic_ib_ucontext *uctx = to_ucontext(context);
	काष्ठा usnic_ib_dev *us_ibdev;
	काष्ठा usnic_ib_qp_grp *qp_grp;
	काष्ठा usnic_ib_vf *vf;
	काष्ठा vnic_dev_bar *bar;
	dma_addr_t bus_addr;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक vfid;

	usnic_dbg("\n");

	us_ibdev = to_usdev(context->device);
	vma->vm_flags |= VM_IO;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vfid = vma->vm_pgoff;
	usnic_dbg("Page Offset %lu PAGE_SHIFT %u VFID %u\n",
			vma->vm_pgoff, PAGE_SHIFT, vfid);

	mutex_lock(&us_ibdev->usdev_lock);
	list_क्रम_each_entry(qp_grp, &uctx->qp_grp_list, link) अणु
		vf = qp_grp->vf;
		अगर (usnic_vnic_get_index(vf->vnic) == vfid) अणु
			bar = usnic_vnic_get_bar(vf->vnic, 0);
			अगर ((vma->vm_end - vma->vm_start) != bar->len) अणु
				usnic_err("Bar0 Len %lu - Request map %lu\n",
						bar->len,
						vma->vm_end - vma->vm_start);
				mutex_unlock(&us_ibdev->usdev_lock);
				वापस -EINVAL;
			पूर्ण
			bus_addr = bar->bus_addr;
			len = bar->len;
			usnic_dbg("bus: %pa vaddr: %p size: %ld\n",
					&bus_addr, bar->vaddr, bar->len);
			mutex_unlock(&us_ibdev->usdev_lock);

			वापस remap_pfn_range(vma,
						vma->vm_start,
						bus_addr >> PAGE_SHIFT,
						len, vma->vm_page_prot);
		पूर्ण
	पूर्ण

	mutex_unlock(&us_ibdev->usdev_lock);
	usnic_err("No VF %u found\n", vfid);
	वापस -EINVAL;
पूर्ण

