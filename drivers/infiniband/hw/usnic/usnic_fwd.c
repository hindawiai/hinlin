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
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>

#समावेश "enic_api.h"
#समावेश "usnic_common_pkt_hdr.h"
#समावेश "usnic_fwd.h"
#समावेश "usnic_log.h"

अटल पूर्णांक usnic_fwd_devcmd_locked(काष्ठा usnic_fwd_dev *ufdev, पूर्णांक vnic_idx,
					क्रमागत vnic_devcmd_cmd cmd, u64 *a0,
					u64 *a1)
अणु
	पूर्णांक status;
	काष्ठा net_device *netdev = ufdev->netdev;

	lockdep_निश्चित_held(&ufdev->lock);

	status = enic_api_devcmd_proxy_by_index(netdev,
			vnic_idx,
			cmd,
			a0, a1,
			1000);
	अगर (status) अणु
		अगर (status == ERR_EINVAL && cmd == CMD_DEL_FILTER) अणु
			usnic_dbg("Dev %s vnic idx %u cmd %u already deleted",
					ufdev->name, vnic_idx, cmd);
		पूर्ण अन्यथा अणु
			usnic_err("Dev %s vnic idx %u cmd %u failed with status %d\n",
					ufdev->name, vnic_idx, cmd,
					status);
		पूर्ण
	पूर्ण अन्यथा अणु
		usnic_dbg("Dev %s vnic idx %u cmd %u success",
				ufdev->name, vnic_idx, cmd);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक usnic_fwd_devcmd(काष्ठा usnic_fwd_dev *ufdev, पूर्णांक vnic_idx,
				क्रमागत vnic_devcmd_cmd cmd, u64 *a0, u64 *a1)
अणु
	पूर्णांक status;

	spin_lock(&ufdev->lock);
	status = usnic_fwd_devcmd_locked(ufdev, vnic_idx, cmd, a0, a1);
	spin_unlock(&ufdev->lock);

	वापस status;
पूर्ण

काष्ठा usnic_fwd_dev *usnic_fwd_dev_alloc(काष्ठा pci_dev *pdev)
अणु
	काष्ठा usnic_fwd_dev *ufdev;

	ufdev = kzalloc(माप(*ufdev), GFP_KERNEL);
	अगर (!ufdev)
		वापस शून्य;

	ufdev->pdev = pdev;
	ufdev->netdev = pci_get_drvdata(pdev);
	spin_lock_init(&ufdev->lock);
	BUILD_BUG_ON(माप(ufdev->name) != माप(ufdev->netdev->name));
	म_नकल(ufdev->name, ufdev->netdev->name);

	वापस ufdev;
पूर्ण

व्योम usnic_fwd_dev_मुक्त(काष्ठा usnic_fwd_dev *ufdev)
अणु
	kमुक्त(ufdev);
पूर्ण

व्योम usnic_fwd_set_mac(काष्ठा usnic_fwd_dev *ufdev, अक्षर mac[ETH_ALEN])
अणु
	spin_lock(&ufdev->lock);
	स_नकल(&ufdev->mac, mac, माप(ufdev->mac));
	spin_unlock(&ufdev->lock);
पूर्ण

व्योम usnic_fwd_add_ipaddr(काष्ठा usnic_fwd_dev *ufdev, __be32 inaddr)
अणु
	spin_lock(&ufdev->lock);
	अगर (!ufdev->inaddr)
		ufdev->inaddr = inaddr;
	spin_unlock(&ufdev->lock);
पूर्ण

व्योम usnic_fwd_del_ipaddr(काष्ठा usnic_fwd_dev *ufdev)
अणु
	spin_lock(&ufdev->lock);
	ufdev->inaddr = 0;
	spin_unlock(&ufdev->lock);
पूर्ण

व्योम usnic_fwd_carrier_up(काष्ठा usnic_fwd_dev *ufdev)
अणु
	spin_lock(&ufdev->lock);
	ufdev->link_up = 1;
	spin_unlock(&ufdev->lock);
पूर्ण

व्योम usnic_fwd_carrier_करोwn(काष्ठा usnic_fwd_dev *ufdev)
अणु
	spin_lock(&ufdev->lock);
	ufdev->link_up = 0;
	spin_unlock(&ufdev->lock);
पूर्ण

व्योम usnic_fwd_set_mtu(काष्ठा usnic_fwd_dev *ufdev, अचिन्हित पूर्णांक mtu)
अणु
	spin_lock(&ufdev->lock);
	ufdev->mtu = mtu;
	spin_unlock(&ufdev->lock);
पूर्ण

अटल पूर्णांक usnic_fwd_dev_पढ़ोy_locked(काष्ठा usnic_fwd_dev *ufdev)
अणु
	lockdep_निश्चित_held(&ufdev->lock);

	अगर (!ufdev->link_up)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक validate_filter_locked(काष्ठा usnic_fwd_dev *ufdev,
					काष्ठा filter *filter)
अणु

	lockdep_निश्चित_held(&ufdev->lock);

	अगर (filter->type == FILTER_IPV4_5TUPLE) अणु
		अगर (!(filter->u.ipv4.flags & FILTER_FIELD_5TUP_DST_AD))
			वापस -EACCES;
		अगर (!(filter->u.ipv4.flags & FILTER_FIELD_5TUP_DST_PT))
			वापस -EBUSY;
		अन्यथा अगर (ufdev->inaddr == 0)
			वापस -EINVAL;
		अन्यथा अगर (filter->u.ipv4.dst_port == 0)
			वापस -दुस्फल;
		अन्यथा अगर (ntohl(ufdev->inaddr) != filter->u.ipv4.dst_addr)
			वापस -EFAULT;
		अन्यथा
			वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fill_tlv(काष्ठा filter_tlv *tlv, काष्ठा filter *filter,
		काष्ठा filter_action *action)
अणु
	tlv->type = CLSF_TLV_FILTER;
	tlv->length = माप(काष्ठा filter);
	*((काष्ठा filter *)&tlv->val) = *filter;

	tlv = (काष्ठा filter_tlv *)((अक्षर *)tlv + माप(काष्ठा filter_tlv) +
			माप(काष्ठा filter));
	tlv->type = CLSF_TLV_ACTION;
	tlv->length = माप(काष्ठा filter_action);
	*((काष्ठा filter_action *)&tlv->val) = *action;
पूर्ण

काष्ठा usnic_fwd_flow*
usnic_fwd_alloc_flow(काष्ठा usnic_fwd_dev *ufdev, काष्ठा filter *filter,
				काष्ठा usnic_filter_action *uaction)
अणु
	काष्ठा filter_tlv *tlv;
	काष्ठा pci_dev *pdev;
	काष्ठा usnic_fwd_flow *flow;
	uपूर्णांक64_t a0, a1;
	uपूर्णांक64_t tlv_size;
	dma_addr_t tlv_pa;
	पूर्णांक status;

	pdev = ufdev->pdev;
	tlv_size = (2*माप(काष्ठा filter_tlv) + माप(काष्ठा filter) +
			माप(काष्ठा filter_action));

	flow = kzalloc(माप(*flow), GFP_ATOMIC);
	अगर (!flow)
		वापस ERR_PTR(-ENOMEM);

	tlv = dma_alloc_coherent(&pdev->dev, tlv_size, &tlv_pa, GFP_ATOMIC);
	अगर (!tlv) अणु
		usnic_err("Failed to allocate memory\n");
		status = -ENOMEM;
		जाओ out_मुक्त_flow;
	पूर्ण

	fill_tlv(tlv, filter, &uaction->action);

	spin_lock(&ufdev->lock);
	status = usnic_fwd_dev_पढ़ोy_locked(ufdev);
	अगर (status) अणु
		usnic_err("Forwarding dev %s not ready with status %d\n",
				ufdev->name, status);
		जाओ out_मुक्त_tlv;
	पूर्ण

	status = validate_filter_locked(ufdev, filter);
	अगर (status) अणु
		usnic_err("Failed to validate filter with status %d\n",
				status);
		जाओ out_मुक्त_tlv;
	पूर्ण

	/* Issue Devcmd */
	a0 = tlv_pa;
	a1 = tlv_size;
	status = usnic_fwd_devcmd_locked(ufdev, uaction->vnic_idx,
						CMD_ADD_FILTER, &a0, &a1);
	अगर (status) अणु
		usnic_err("VF %s Filter add failed with status:%d",
				ufdev->name, status);
		status = -EFAULT;
		जाओ out_मुक्त_tlv;
	पूर्ण अन्यथा अणु
		usnic_dbg("VF %s FILTER ID:%llu", ufdev->name, a0);
	पूर्ण

	flow->flow_id = (uपूर्णांक32_t) a0;
	flow->vnic_idx = uaction->vnic_idx;
	flow->ufdev = ufdev;

out_मुक्त_tlv:
	spin_unlock(&ufdev->lock);
	dma_मुक्त_coherent(&pdev->dev, tlv_size, tlv, tlv_pa);
	अगर (!status)
		वापस flow;
out_मुक्त_flow:
	kमुक्त(flow);
	वापस ERR_PTR(status);
पूर्ण

पूर्णांक usnic_fwd_dealloc_flow(काष्ठा usnic_fwd_flow *flow)
अणु
	पूर्णांक status;
	u64 a0, a1;

	a0 = flow->flow_id;

	status = usnic_fwd_devcmd(flow->ufdev, flow->vnic_idx,
					CMD_DEL_FILTER, &a0, &a1);
	अगर (status) अणु
		अगर (status == ERR_EINVAL) अणु
			usnic_dbg("Filter %u already deleted for VF Idx %u pf: %s status: %d",
					flow->flow_id, flow->vnic_idx,
					flow->ufdev->name, status);
		पूर्ण अन्यथा अणु
			usnic_err("PF %s VF Idx %u Filter: %u FILTER DELETE failed with status %d",
					flow->ufdev->name, flow->vnic_idx,
					flow->flow_id, status);
		पूर्ण
		status = 0;
		/*
		 * Log the error and fake success to the caller because अगर
		 * a flow fails to be deleted in the firmware, it is an
		 * unrecoverable error.
		 */
	पूर्ण अन्यथा अणु
		usnic_dbg("PF %s VF Idx %u Filter: %u FILTER DELETED",
				flow->ufdev->name, flow->vnic_idx,
				flow->flow_id);
	पूर्ण

	kमुक्त(flow);
	वापस status;
पूर्ण

पूर्णांक usnic_fwd_enable_qp(काष्ठा usnic_fwd_dev *ufdev, पूर्णांक vnic_idx, पूर्णांक qp_idx)
अणु
	पूर्णांक status;
	काष्ठा net_device *pf_netdev;
	u64 a0, a1;

	pf_netdev = ufdev->netdev;
	a0 = qp_idx;
	a1 = CMD_QP_RQWQ;

	status = usnic_fwd_devcmd(ufdev, vnic_idx, CMD_QP_ENABLE,
						&a0, &a1);
	अगर (status) अणु
		usnic_err("PF %s VNIC Index %u RQ Index: %u ENABLE Failed with status %d",
				netdev_name(pf_netdev),
				vnic_idx,
				qp_idx,
				status);
	पूर्ण अन्यथा अणु
		usnic_dbg("PF %s VNIC Index %u RQ Index: %u ENABLED",
				netdev_name(pf_netdev),
				vnic_idx, qp_idx);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक usnic_fwd_disable_qp(काष्ठा usnic_fwd_dev *ufdev, पूर्णांक vnic_idx, पूर्णांक qp_idx)
अणु
	पूर्णांक status;
	u64 a0, a1;
	काष्ठा net_device *pf_netdev;

	pf_netdev = ufdev->netdev;
	a0 = qp_idx;
	a1 = CMD_QP_RQWQ;

	status = usnic_fwd_devcmd(ufdev, vnic_idx, CMD_QP_DISABLE,
			&a0, &a1);
	अगर (status) अणु
		usnic_err("PF %s VNIC Index %u RQ Index: %u DISABLE Failed with status %d",
				netdev_name(pf_netdev),
				vnic_idx,
				qp_idx,
				status);
	पूर्ण अन्यथा अणु
		usnic_dbg("PF %s VNIC Index %u RQ Index: %u DISABLED",
				netdev_name(pf_netdev),
				vnic_idx,
				qp_idx);
	पूर्ण

	वापस status;
पूर्ण
