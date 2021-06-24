<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
 * Copyright (c) 2016-2018 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/etherdevice.h>
#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"
#समावेश "bnxt_ulp.h"
#समावेश "bnxt_sriov.h"
#समावेश "bnxt_vfr.h"
#समावेश "bnxt_ethtool.h"

#अगर_घोषित CONFIG_BNXT_SRIOV
अटल पूर्णांक bnxt_hwrm_fwd_async_event_cmpl(काष्ठा bnxt *bp,
					  काष्ठा bnxt_vf_info *vf, u16 event_id)
अणु
	काष्ठा hwrm_fwd_async_event_cmpl_input req = अणु0पूर्ण;
	काष्ठा hwrm_async_event_cmpl *async_cmpl;
	पूर्णांक rc = 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FWD_ASYNC_EVENT_CMPL, -1, -1);
	अगर (vf)
		req.encap_async_event_target_id = cpu_to_le16(vf->fw_fid);
	अन्यथा
		/* broadcast this async event to all VFs */
		req.encap_async_event_target_id = cpu_to_le16(0xffff);
	async_cmpl = (काष्ठा hwrm_async_event_cmpl *)req.encap_async_event_cmpl;
	async_cmpl->type = cpu_to_le16(ASYNC_EVENT_CMPL_TYPE_HWRM_ASYNC_EVENT);
	async_cmpl->event_id = cpu_to_le16(event_id);

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		netdev_err(bp->dev, "hwrm_fwd_async_event_cmpl failed. rc:%d\n",
			   rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_vf_nकरो_prep(काष्ठा bnxt *bp, पूर्णांक vf_id)
अणु
	अगर (!bp->pf.active_vfs) अणु
		netdev_err(bp->dev, "vf ndo called though sriov is disabled\n");
		वापस -EINVAL;
	पूर्ण
	अगर (vf_id >= bp->pf.active_vfs) अणु
		netdev_err(bp->dev, "Invalid VF id %d\n", vf_id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bnxt_set_vf_spoofchk(काष्ठा net_device *dev, पूर्णांक vf_id, bool setting)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_vf_info *vf;
	bool old_setting = false;
	u32 func_flags;
	पूर्णांक rc;

	अगर (bp->hwrm_spec_code < 0x10701)
		वापस -ENOTSUPP;

	rc = bnxt_vf_nकरो_prep(bp, vf_id);
	अगर (rc)
		वापस rc;

	vf = &bp->pf.vf[vf_id];
	अगर (vf->flags & BNXT_VF_SPOOFCHK)
		old_setting = true;
	अगर (old_setting == setting)
		वापस 0;

	अगर (setting)
		func_flags = FUNC_CFG_REQ_FLAGS_SRC_MAC_ADDR_CHECK_ENABLE;
	अन्यथा
		func_flags = FUNC_CFG_REQ_FLAGS_SRC_MAC_ADDR_CHECK_DISABLE;
	/*TODO: अगर the driver supports VLAN filter on guest VLAN,
	 * the spoof check should also include vlan anti-spoofing
	 */
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(vf->fw_fid);
	req.flags = cpu_to_le32(func_flags);
	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		अगर (setting)
			vf->flags |= BNXT_VF_SPOOFCHK;
		अन्यथा
			vf->flags &= ~BNXT_VF_SPOOFCHK;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_func_qcfg_flags(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf)
अणु
	काष्ठा hwrm_func_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_func_qcfg_input req = अणु0पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCFG, -1, -1);
	req.fid = cpu_to_le16(BNXT_PF(bp) ? vf->fw_fid : 0xffff);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc) अणु
		mutex_unlock(&bp->hwrm_cmd_lock);
		वापस rc;
	पूर्ण
	vf->func_qcfg_flags = le16_to_cpu(resp->flags);
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस 0;
पूर्ण

bool bnxt_is_trusted_vf(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf)
अणु
	अगर (BNXT_PF(bp) && !(bp->fw_cap & BNXT_FW_CAP_TRUSTED_VF))
		वापस !!(vf->flags & BNXT_VF_TRUST);

	bnxt_hwrm_func_qcfg_flags(bp, vf);
	वापस !!(vf->func_qcfg_flags & FUNC_QCFG_RESP_FLAGS_TRUSTED_VF);
पूर्ण

अटल पूर्णांक bnxt_hwrm_set_trusted_vf(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;

	अगर (!(bp->fw_cap & BNXT_FW_CAP_TRUSTED_VF))
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(vf->fw_fid);
	अगर (vf->flags & BNXT_VF_TRUST)
		req.flags = cpu_to_le32(FUNC_CFG_REQ_FLAGS_TRUSTED_VF_ENABLE);
	अन्यथा
		req.flags = cpu_to_le32(FUNC_CFG_REQ_FLAGS_TRUSTED_VF_DISABLE);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

पूर्णांक bnxt_set_vf_trust(काष्ठा net_device *dev, पूर्णांक vf_id, bool trusted)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_vf_info *vf;

	अगर (bnxt_vf_nकरो_prep(bp, vf_id))
		वापस -EINVAL;

	vf = &bp->pf.vf[vf_id];
	अगर (trusted)
		vf->flags |= BNXT_VF_TRUST;
	अन्यथा
		vf->flags &= ~BNXT_VF_TRUST;

	bnxt_hwrm_set_trusted_vf(bp, vf);
	वापस 0;
पूर्ण

पूर्णांक bnxt_get_vf_config(काष्ठा net_device *dev, पूर्णांक vf_id,
		       काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_vf_info *vf;
	पूर्णांक rc;

	rc = bnxt_vf_nकरो_prep(bp, vf_id);
	अगर (rc)
		वापस rc;

	ivi->vf = vf_id;
	vf = &bp->pf.vf[vf_id];

	अगर (is_valid_ether_addr(vf->mac_addr))
		स_नकल(&ivi->mac, vf->mac_addr, ETH_ALEN);
	अन्यथा
		स_नकल(&ivi->mac, vf->vf_mac_addr, ETH_ALEN);
	ivi->max_tx_rate = vf->max_tx_rate;
	ivi->min_tx_rate = vf->min_tx_rate;
	ivi->vlan = vf->vlan;
	अगर (vf->flags & BNXT_VF_QOS)
		ivi->qos = vf->vlan >> VLAN_PRIO_SHIFT;
	अन्यथा
		ivi->qos = 0;
	ivi->spoofchk = !!(vf->flags & BNXT_VF_SPOOFCHK);
	ivi->trusted = bnxt_is_trusted_vf(bp, vf);
	अगर (!(vf->flags & BNXT_VF_LINK_FORCED))
		ivi->linkstate = IFLA_VF_LINK_STATE_AUTO;
	अन्यथा अगर (vf->flags & BNXT_VF_LINK_UP)
		ivi->linkstate = IFLA_VF_LINK_STATE_ENABLE;
	अन्यथा
		ivi->linkstate = IFLA_VF_LINK_STATE_DISABLE;

	वापस 0;
पूर्ण

पूर्णांक bnxt_set_vf_mac(काष्ठा net_device *dev, पूर्णांक vf_id, u8 *mac)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_vf_info *vf;
	पूर्णांक rc;

	rc = bnxt_vf_nकरो_prep(bp, vf_id);
	अगर (rc)
		वापस rc;
	/* reject bc or mc mac addr, zero mac addr means allow
	 * VF to use its own mac addr
	 */
	अगर (is_multicast_ether_addr(mac)) अणु
		netdev_err(dev, "Invalid VF ethernet address\n");
		वापस -EINVAL;
	पूर्ण
	vf = &bp->pf.vf[vf_id];

	स_नकल(vf->mac_addr, mac, ETH_ALEN);
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(vf->fw_fid);
	req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_DFLT_MAC_ADDR);
	स_नकल(req.dflt_mac_addr, mac, ETH_ALEN);
	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

पूर्णांक bnxt_set_vf_vlan(काष्ठा net_device *dev, पूर्णांक vf_id, u16 vlan_id, u8 qos,
		     __be16 vlan_proto)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_vf_info *vf;
	u16 vlan_tag;
	पूर्णांक rc;

	अगर (bp->hwrm_spec_code < 0x10201)
		वापस -ENOTSUPP;

	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	rc = bnxt_vf_nकरो_prep(bp, vf_id);
	अगर (rc)
		वापस rc;

	/* TODO: needed to implement proper handling of user priority,
	 * currently fail the command अगर there is valid priority
	 */
	अगर (vlan_id > 4095 || qos)
		वापस -EINVAL;

	vf = &bp->pf.vf[vf_id];
	vlan_tag = vlan_id;
	अगर (vlan_tag == vf->vlan)
		वापस 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(vf->fw_fid);
	req.dflt_vlan = cpu_to_le16(vlan_tag);
	req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_DFLT_VLAN);
	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc)
		vf->vlan = vlan_tag;
	वापस rc;
पूर्ण

पूर्णांक bnxt_set_vf_bw(काष्ठा net_device *dev, पूर्णांक vf_id, पूर्णांक min_tx_rate,
		   पूर्णांक max_tx_rate)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_vf_info *vf;
	u32 pf_link_speed;
	पूर्णांक rc;

	rc = bnxt_vf_nकरो_prep(bp, vf_id);
	अगर (rc)
		वापस rc;

	vf = &bp->pf.vf[vf_id];
	pf_link_speed = bnxt_fw_to_ethtool_speed(bp->link_info.link_speed);
	अगर (max_tx_rate > pf_link_speed) अणु
		netdev_info(bp->dev, "max tx rate %d exceed PF link speed for VF %d\n",
			    max_tx_rate, vf_id);
		वापस -EINVAL;
	पूर्ण

	अगर (min_tx_rate > pf_link_speed || min_tx_rate > max_tx_rate) अणु
		netdev_info(bp->dev, "min tx rate %d is invalid for VF %d\n",
			    min_tx_rate, vf_id);
		वापस -EINVAL;
	पूर्ण
	अगर (min_tx_rate == vf->min_tx_rate && max_tx_rate == vf->max_tx_rate)
		वापस 0;
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(vf->fw_fid);
	req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_MAX_BW);
	req.max_bw = cpu_to_le32(max_tx_rate);
	req.enables |= cpu_to_le32(FUNC_CFG_REQ_ENABLES_MIN_BW);
	req.min_bw = cpu_to_le32(min_tx_rate);
	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		vf->min_tx_rate = min_tx_rate;
		vf->max_tx_rate = max_tx_rate;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक bnxt_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक vf_id, पूर्णांक link)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_vf_info *vf;
	पूर्णांक rc;

	rc = bnxt_vf_nकरो_prep(bp, vf_id);
	अगर (rc)
		वापस rc;

	vf = &bp->pf.vf[vf_id];

	vf->flags &= ~(BNXT_VF_LINK_UP | BNXT_VF_LINK_FORCED);
	चयन (link) अणु
	हाल IFLA_VF_LINK_STATE_AUTO:
		vf->flags |= BNXT_VF_LINK_UP;
		अवरोध;
	हाल IFLA_VF_LINK_STATE_DISABLE:
		vf->flags |= BNXT_VF_LINK_FORCED;
		अवरोध;
	हाल IFLA_VF_LINK_STATE_ENABLE:
		vf->flags |= BNXT_VF_LINK_UP | BNXT_VF_LINK_FORCED;
		अवरोध;
	शेष:
		netdev_err(bp->dev, "Invalid link option\n");
		rc = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (vf->flags & (BNXT_VF_LINK_UP | BNXT_VF_LINK_FORCED))
		rc = bnxt_hwrm_fwd_async_event_cmpl(bp, vf,
			ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_set_vf_attr(काष्ठा bnxt *bp, पूर्णांक num_vfs)
अणु
	पूर्णांक i;
	काष्ठा bnxt_vf_info *vf;

	क्रम (i = 0; i < num_vfs; i++) अणु
		vf = &bp->pf.vf[i];
		स_रखो(vf, 0, माप(*vf));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_func_vf_resource_मुक्त(काष्ठा bnxt *bp, पूर्णांक num_vfs)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा bnxt_pf_info *pf = &bp->pf;
	काष्ठा hwrm_func_vf_resc_मुक्त_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_VF_RESC_FREE, -1, -1);

	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = pf->first_vf_id; i < pf->first_vf_id + num_vfs; i++) अणु
		req.vf_id = cpu_to_le16(i);
		rc = _hwrm_send_message(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
		अगर (rc)
			अवरोध;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_मुक्त_vf_resources(काष्ठा bnxt *bp)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;
	पूर्णांक i;

	kमुक्त(bp->pf.vf_event_bmap);
	bp->pf.vf_event_bmap = शून्य;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (bp->pf.hwrm_cmd_req_addr[i]) अणु
			dma_मुक्त_coherent(&pdev->dev, BNXT_PAGE_SIZE,
					  bp->pf.hwrm_cmd_req_addr[i],
					  bp->pf.hwrm_cmd_req_dma_addr[i]);
			bp->pf.hwrm_cmd_req_addr[i] = शून्य;
		पूर्ण
	पूर्ण

	bp->pf.active_vfs = 0;
	kमुक्त(bp->pf.vf);
	bp->pf.vf = शून्य;
पूर्ण

अटल पूर्णांक bnxt_alloc_vf_resources(काष्ठा bnxt *bp, पूर्णांक num_vfs)
अणु
	काष्ठा pci_dev *pdev = bp->pdev;
	u32 nr_pages, size, i, j, k = 0;

	bp->pf.vf = kसुस्मृति(num_vfs, माप(काष्ठा bnxt_vf_info), GFP_KERNEL);
	अगर (!bp->pf.vf)
		वापस -ENOMEM;

	bnxt_set_vf_attr(bp, num_vfs);

	size = num_vfs * BNXT_HWRM_REQ_MAX_SIZE;
	nr_pages = size / BNXT_PAGE_SIZE;
	अगर (size & (BNXT_PAGE_SIZE - 1))
		nr_pages++;

	क्रम (i = 0; i < nr_pages; i++) अणु
		bp->pf.hwrm_cmd_req_addr[i] =
			dma_alloc_coherent(&pdev->dev, BNXT_PAGE_SIZE,
					   &bp->pf.hwrm_cmd_req_dma_addr[i],
					   GFP_KERNEL);

		अगर (!bp->pf.hwrm_cmd_req_addr[i])
			वापस -ENOMEM;

		क्रम (j = 0; j < BNXT_HWRM_REQS_PER_PAGE && k < num_vfs; j++) अणु
			काष्ठा bnxt_vf_info *vf = &bp->pf.vf[k];

			vf->hwrm_cmd_req_addr = bp->pf.hwrm_cmd_req_addr[i] +
						j * BNXT_HWRM_REQ_MAX_SIZE;
			vf->hwrm_cmd_req_dma_addr =
				bp->pf.hwrm_cmd_req_dma_addr[i] + j *
				BNXT_HWRM_REQ_MAX_SIZE;
			k++;
		पूर्ण
	पूर्ण

	/* Max 128 VF's */
	bp->pf.vf_event_bmap = kzalloc(16, GFP_KERNEL);
	अगर (!bp->pf.vf_event_bmap)
		वापस -ENOMEM;

	bp->pf.hwrm_cmd_req_pages = nr_pages;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_hwrm_func_buf_rgtr(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_func_buf_rgtr_input req = अणु0पूर्ण;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_BUF_RGTR, -1, -1);

	req.req_buf_num_pages = cpu_to_le16(bp->pf.hwrm_cmd_req_pages);
	req.req_buf_page_size = cpu_to_le16(BNXT_PAGE_SHIFT);
	req.req_buf_len = cpu_to_le16(BNXT_HWRM_REQ_MAX_SIZE);
	req.req_buf_page_addr0 = cpu_to_le64(bp->pf.hwrm_cmd_req_dma_addr[0]);
	req.req_buf_page_addr1 = cpu_to_le64(bp->pf.hwrm_cmd_req_dma_addr[1]);
	req.req_buf_page_addr2 = cpu_to_le64(bp->pf.hwrm_cmd_req_dma_addr[2]);
	req.req_buf_page_addr3 = cpu_to_le64(bp->pf.hwrm_cmd_req_dma_addr[3]);

	वापस hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

/* Caller holds bp->hwrm_cmd_lock mutex lock */
अटल व्योम __bnxt_set_vf_params(काष्ठा bnxt *bp, पूर्णांक vf_id)
अणु
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt_vf_info *vf;

	vf = &bp->pf.vf[vf_id];
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(vf->fw_fid);

	अगर (is_valid_ether_addr(vf->mac_addr)) अणु
		req.enables |= cpu_to_le32(FUNC_CFG_REQ_ENABLES_DFLT_MAC_ADDR);
		स_नकल(req.dflt_mac_addr, vf->mac_addr, ETH_ALEN);
	पूर्ण
	अगर (vf->vlan) अणु
		req.enables |= cpu_to_le32(FUNC_CFG_REQ_ENABLES_DFLT_VLAN);
		req.dflt_vlan = cpu_to_le16(vf->vlan);
	पूर्ण
	अगर (vf->max_tx_rate) अणु
		req.enables |= cpu_to_le32(FUNC_CFG_REQ_ENABLES_MAX_BW);
		req.max_bw = cpu_to_le32(vf->max_tx_rate);
#अगर_घोषित HAVE_IFLA_TX_RATE
		req.enables |= cpu_to_le32(FUNC_CFG_REQ_ENABLES_MIN_BW);
		req.min_bw = cpu_to_le32(vf->min_tx_rate);
#पूर्ण_अगर
	पूर्ण
	अगर (vf->flags & BNXT_VF_TRUST)
		req.flags |= cpu_to_le32(FUNC_CFG_REQ_FLAGS_TRUSTED_VF_ENABLE);

	_hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
पूर्ण

/* Only called by PF to reserve resources क्रम VFs, वापसs actual number of
 * VFs configured, or < 0 on error.
 */
अटल पूर्णांक bnxt_hwrm_func_vf_resc_cfg(काष्ठा bnxt *bp, पूर्णांक num_vfs, bool reset)
अणु
	काष्ठा hwrm_func_vf_resource_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	u16 vf_tx_rings, vf_rx_rings, vf_cp_rings;
	u16 vf_stat_ctx, vf_vnics, vf_ring_grps;
	काष्ठा bnxt_pf_info *pf = &bp->pf;
	पूर्णांक i, rc = 0, min = 1;
	u16 vf_msix = 0;
	u16 vf_rss;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_VF_RESOURCE_CFG, -1, -1);

	अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
		vf_msix = hw_resc->max_nqs - bnxt_nq_rings_in_use(bp);
		vf_ring_grps = 0;
	पूर्ण अन्यथा अणु
		vf_ring_grps = hw_resc->max_hw_ring_grps - bp->rx_nr_rings;
	पूर्ण
	vf_cp_rings = bnxt_get_avail_cp_rings_क्रम_en(bp);
	vf_stat_ctx = bnxt_get_avail_stat_ctxs_क्रम_en(bp);
	अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
		vf_rx_rings = hw_resc->max_rx_rings - bp->rx_nr_rings * 2;
	अन्यथा
		vf_rx_rings = hw_resc->max_rx_rings - bp->rx_nr_rings;
	vf_tx_rings = hw_resc->max_tx_rings - bp->tx_nr_rings;
	vf_vnics = hw_resc->max_vnics - bp->nr_vnics;
	vf_vnics = min_t(u16, vf_vnics, vf_rx_rings);
	vf_rss = hw_resc->max_rsscos_ctxs - bp->rsscos_nr_ctxs;

	req.min_rsscos_ctx = cpu_to_le16(BNXT_VF_MIN_RSS_CTX);
	अगर (pf->vf_resv_strategy == BNXT_VF_RESV_STRATEGY_MINIMAL_STATIC) अणु
		min = 0;
		req.min_rsscos_ctx = cpu_to_le16(min);
	पूर्ण
	अगर (pf->vf_resv_strategy == BNXT_VF_RESV_STRATEGY_MINIMAL ||
	    pf->vf_resv_strategy == BNXT_VF_RESV_STRATEGY_MINIMAL_STATIC) अणु
		req.min_cmpl_rings = cpu_to_le16(min);
		req.min_tx_rings = cpu_to_le16(min);
		req.min_rx_rings = cpu_to_le16(min);
		req.min_l2_ctxs = cpu_to_le16(min);
		req.min_vnics = cpu_to_le16(min);
		req.min_stat_ctx = cpu_to_le16(min);
		अगर (!(bp->flags & BNXT_FLAG_CHIP_P5))
			req.min_hw_ring_grps = cpu_to_le16(min);
	पूर्ण अन्यथा अणु
		vf_cp_rings /= num_vfs;
		vf_tx_rings /= num_vfs;
		vf_rx_rings /= num_vfs;
		vf_vnics /= num_vfs;
		vf_stat_ctx /= num_vfs;
		vf_ring_grps /= num_vfs;
		vf_rss /= num_vfs;

		req.min_cmpl_rings = cpu_to_le16(vf_cp_rings);
		req.min_tx_rings = cpu_to_le16(vf_tx_rings);
		req.min_rx_rings = cpu_to_le16(vf_rx_rings);
		req.min_l2_ctxs = cpu_to_le16(BNXT_VF_MAX_L2_CTX);
		req.min_vnics = cpu_to_le16(vf_vnics);
		req.min_stat_ctx = cpu_to_le16(vf_stat_ctx);
		req.min_hw_ring_grps = cpu_to_le16(vf_ring_grps);
		req.min_rsscos_ctx = cpu_to_le16(vf_rss);
	पूर्ण
	req.max_cmpl_rings = cpu_to_le16(vf_cp_rings);
	req.max_tx_rings = cpu_to_le16(vf_tx_rings);
	req.max_rx_rings = cpu_to_le16(vf_rx_rings);
	req.max_l2_ctxs = cpu_to_le16(BNXT_VF_MAX_L2_CTX);
	req.max_vnics = cpu_to_le16(vf_vnics);
	req.max_stat_ctx = cpu_to_le16(vf_stat_ctx);
	req.max_hw_ring_grps = cpu_to_le16(vf_ring_grps);
	req.max_rsscos_ctx = cpu_to_le16(vf_rss);
	अगर (bp->flags & BNXT_FLAG_CHIP_P5)
		req.max_msix = cpu_to_le16(vf_msix / num_vfs);

	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = 0; i < num_vfs; i++) अणु
		अगर (reset)
			__bnxt_set_vf_params(bp, i);

		req.vf_id = cpu_to_le16(pf->first_vf_id + i);
		rc = _hwrm_send_message(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
		अगर (rc)
			अवरोध;
		pf->active_vfs = i + 1;
		pf->vf[i].fw_fid = pf->first_vf_id + i;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	अगर (pf->active_vfs) अणु
		u16 n = pf->active_vfs;

		hw_resc->max_tx_rings -= le16_to_cpu(req.min_tx_rings) * n;
		hw_resc->max_rx_rings -= le16_to_cpu(req.min_rx_rings) * n;
		hw_resc->max_hw_ring_grps -= le16_to_cpu(req.min_hw_ring_grps) *
					     n;
		hw_resc->max_cp_rings -= le16_to_cpu(req.min_cmpl_rings) * n;
		hw_resc->max_rsscos_ctxs -= le16_to_cpu(req.min_rsscos_ctx) * n;
		hw_resc->max_stat_ctxs -= le16_to_cpu(req.min_stat_ctx) * n;
		hw_resc->max_vnics -= le16_to_cpu(req.min_vnics) * n;
		अगर (bp->flags & BNXT_FLAG_CHIP_P5)
			hw_resc->max_irqs -= vf_msix * n;

		rc = pf->active_vfs;
	पूर्ण
	वापस rc;
पूर्ण

/* Only called by PF to reserve resources क्रम VFs, वापसs actual number of
 * VFs configured, or < 0 on error.
 */
अटल पूर्णांक bnxt_hwrm_func_cfg(काष्ठा bnxt *bp, पूर्णांक num_vfs)
अणु
	u32 rc = 0, mtu, i;
	u16 vf_tx_rings, vf_rx_rings, vf_cp_rings, vf_stat_ctx, vf_vnics;
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	काष्ठा hwrm_func_cfg_input req = अणु0पूर्ण;
	काष्ठा bnxt_pf_info *pf = &bp->pf;
	पूर्णांक total_vf_tx_rings = 0;
	u16 vf_ring_grps;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);

	/* Reमुख्यing rings are distributed equally amongs VF's क्रम now */
	vf_cp_rings = bnxt_get_avail_cp_rings_क्रम_en(bp) / num_vfs;
	vf_stat_ctx = bnxt_get_avail_stat_ctxs_क्रम_en(bp) / num_vfs;
	अगर (bp->flags & BNXT_FLAG_AGG_RINGS)
		vf_rx_rings = (hw_resc->max_rx_rings - bp->rx_nr_rings * 2) /
			      num_vfs;
	अन्यथा
		vf_rx_rings = (hw_resc->max_rx_rings - bp->rx_nr_rings) /
			      num_vfs;
	vf_ring_grps = (hw_resc->max_hw_ring_grps - bp->rx_nr_rings) / num_vfs;
	vf_tx_rings = (hw_resc->max_tx_rings - bp->tx_nr_rings) / num_vfs;
	vf_vnics = (hw_resc->max_vnics - bp->nr_vnics) / num_vfs;
	vf_vnics = min_t(u16, vf_vnics, vf_rx_rings);

	req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_MTU |
				  FUNC_CFG_REQ_ENABLES_MRU |
				  FUNC_CFG_REQ_ENABLES_NUM_RSSCOS_CTXS |
				  FUNC_CFG_REQ_ENABLES_NUM_STAT_CTXS |
				  FUNC_CFG_REQ_ENABLES_NUM_CMPL_RINGS |
				  FUNC_CFG_REQ_ENABLES_NUM_TX_RINGS |
				  FUNC_CFG_REQ_ENABLES_NUM_RX_RINGS |
				  FUNC_CFG_REQ_ENABLES_NUM_L2_CTXS |
				  FUNC_CFG_REQ_ENABLES_NUM_VNICS |
				  FUNC_CFG_REQ_ENABLES_NUM_HW_RING_GRPS);

	mtu = bp->dev->mtu + ETH_HLEN + VLAN_HLEN;
	req.mru = cpu_to_le16(mtu);
	req.mtu = cpu_to_le16(mtu);

	req.num_rsscos_ctxs = cpu_to_le16(1);
	req.num_cmpl_rings = cpu_to_le16(vf_cp_rings);
	req.num_tx_rings = cpu_to_le16(vf_tx_rings);
	req.num_rx_rings = cpu_to_le16(vf_rx_rings);
	req.num_hw_ring_grps = cpu_to_le16(vf_ring_grps);
	req.num_l2_ctxs = cpu_to_le16(4);

	req.num_vnics = cpu_to_le16(vf_vnics);
	/* FIXME spec currently uses 1 bit क्रम stats ctx */
	req.num_stat_ctxs = cpu_to_le16(vf_stat_ctx);

	mutex_lock(&bp->hwrm_cmd_lock);
	क्रम (i = 0; i < num_vfs; i++) अणु
		पूर्णांक vf_tx_rsvd = vf_tx_rings;

		req.fid = cpu_to_le16(pf->first_vf_id + i);
		rc = _hwrm_send_message(bp, &req, माप(req),
					HWRM_CMD_TIMEOUT);
		अगर (rc)
			अवरोध;
		pf->active_vfs = i + 1;
		pf->vf[i].fw_fid = le16_to_cpu(req.fid);
		rc = __bnxt_hwrm_get_tx_rings(bp, pf->vf[i].fw_fid,
					      &vf_tx_rsvd);
		अगर (rc)
			अवरोध;
		total_vf_tx_rings += vf_tx_rsvd;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	अगर (pf->active_vfs) अणु
		hw_resc->max_tx_rings -= total_vf_tx_rings;
		hw_resc->max_rx_rings -= vf_rx_rings * num_vfs;
		hw_resc->max_hw_ring_grps -= vf_ring_grps * num_vfs;
		hw_resc->max_cp_rings -= vf_cp_rings * num_vfs;
		hw_resc->max_rsscos_ctxs -= num_vfs;
		hw_resc->max_stat_ctxs -= vf_stat_ctx * num_vfs;
		hw_resc->max_vnics -= vf_vnics * num_vfs;
		rc = pf->active_vfs;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_func_cfg(काष्ठा bnxt *bp, पूर्णांक num_vfs, bool reset)
अणु
	अगर (BNXT_NEW_RM(bp))
		वापस bnxt_hwrm_func_vf_resc_cfg(bp, num_vfs, reset);
	अन्यथा
		वापस bnxt_hwrm_func_cfg(bp, num_vfs);
पूर्ण

पूर्णांक bnxt_cfg_hw_sriov(काष्ठा bnxt *bp, पूर्णांक *num_vfs, bool reset)
अणु
	पूर्णांक rc;

	/* Register buffers क्रम VFs */
	rc = bnxt_hwrm_func_buf_rgtr(bp);
	अगर (rc)
		वापस rc;

	/* Reserve resources क्रम VFs */
	rc = bnxt_func_cfg(bp, *num_vfs, reset);
	अगर (rc != *num_vfs) अणु
		अगर (rc <= 0) अणु
			netdev_warn(bp->dev, "Unable to reserve resources for SRIOV.\n");
			*num_vfs = 0;
			वापस rc;
		पूर्ण
		netdev_warn(bp->dev, "Only able to reserve resources for %d VFs.\n",
			    rc);
		*num_vfs = rc;
	पूर्ण

	bnxt_ulp_sriov_cfg(bp, *num_vfs);
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_sriov_enable(काष्ठा bnxt *bp, पूर्णांक *num_vfs)
अणु
	पूर्णांक rc = 0, vfs_supported;
	पूर्णांक min_rx_rings, min_tx_rings, min_rss_ctxs;
	काष्ठा bnxt_hw_resc *hw_resc = &bp->hw_resc;
	पूर्णांक tx_ok = 0, rx_ok = 0, rss_ok = 0;
	पूर्णांक avail_cp, avail_stat;

	/* Check अगर we can enable requested num of vf's. At a mininum
	 * we require 1 RX 1 TX rings क्रम each VF. In this minimum conf
	 * features like TPA will not be available.
	 */
	vfs_supported = *num_vfs;

	avail_cp = bnxt_get_avail_cp_rings_क्रम_en(bp);
	avail_stat = bnxt_get_avail_stat_ctxs_क्रम_en(bp);
	avail_cp = min_t(पूर्णांक, avail_cp, avail_stat);

	जबतक (vfs_supported) अणु
		min_rx_rings = vfs_supported;
		min_tx_rings = vfs_supported;
		min_rss_ctxs = vfs_supported;

		अगर (bp->flags & BNXT_FLAG_AGG_RINGS) अणु
			अगर (hw_resc->max_rx_rings - bp->rx_nr_rings * 2 >=
			    min_rx_rings)
				rx_ok = 1;
		पूर्ण अन्यथा अणु
			अगर (hw_resc->max_rx_rings - bp->rx_nr_rings >=
			    min_rx_rings)
				rx_ok = 1;
		पूर्ण
		अगर (hw_resc->max_vnics - bp->nr_vnics < min_rx_rings ||
		    avail_cp < min_rx_rings)
			rx_ok = 0;

		अगर (hw_resc->max_tx_rings - bp->tx_nr_rings >= min_tx_rings &&
		    avail_cp >= min_tx_rings)
			tx_ok = 1;

		अगर (hw_resc->max_rsscos_ctxs - bp->rsscos_nr_ctxs >=
		    min_rss_ctxs)
			rss_ok = 1;

		अगर (tx_ok && rx_ok && rss_ok)
			अवरोध;

		vfs_supported--;
	पूर्ण

	अगर (!vfs_supported) अणु
		netdev_err(bp->dev, "Cannot enable VF's as all resources are used by PF\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vfs_supported != *num_vfs) अणु
		netdev_info(bp->dev, "Requested VFs %d, can enable %d\n",
			    *num_vfs, vfs_supported);
		*num_vfs = vfs_supported;
	पूर्ण

	rc = bnxt_alloc_vf_resources(bp, *num_vfs);
	अगर (rc)
		जाओ err_out1;

	rc = bnxt_cfg_hw_sriov(bp, num_vfs, false);
	अगर (rc)
		जाओ err_out2;

	rc = pci_enable_sriov(bp->pdev, *num_vfs);
	अगर (rc)
		जाओ err_out2;

	वापस 0;

err_out2:
	/* Free the resources reserved क्रम various VF's */
	bnxt_hwrm_func_vf_resource_मुक्त(bp, *num_vfs);

err_out1:
	bnxt_मुक्त_vf_resources(bp);

	वापस rc;
पूर्ण

व्योम bnxt_sriov_disable(काष्ठा bnxt *bp)
अणु
	u16 num_vfs = pci_num_vf(bp->pdev);

	अगर (!num_vfs)
		वापस;

	/* synchronize VF and VF-rep create and destroy */
	mutex_lock(&bp->sriov_lock);
	bnxt_vf_reps_destroy(bp);

	अगर (pci_vfs_asचिन्हित(bp->pdev)) अणु
		bnxt_hwrm_fwd_async_event_cmpl(
			bp, शून्य, ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD);
		netdev_warn(bp->dev, "Unable to free %d VFs because some are assigned to VMs.\n",
			    num_vfs);
	पूर्ण अन्यथा अणु
		pci_disable_sriov(bp->pdev);
		/* Free the HW resources reserved क्रम various VF's */
		bnxt_hwrm_func_vf_resource_मुक्त(bp, num_vfs);
	पूर्ण
	mutex_unlock(&bp->sriov_lock);

	bnxt_मुक्त_vf_resources(bp);

	/* Reclaim all resources क्रम the PF. */
	rtnl_lock();
	bnxt_restore_pf_fw_resources(bp);
	rtnl_unlock();

	bnxt_ulp_sriov_cfg(bp, 0);
पूर्ण

पूर्णांक bnxt_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnxt *bp = netdev_priv(dev);

	अगर (!(bp->flags & BNXT_FLAG_USING_MSIX)) अणु
		netdev_warn(dev, "Not allow SRIOV if the irq mode is not MSIX\n");
		वापस 0;
	पूर्ण

	rtnl_lock();
	अगर (!netअगर_running(dev)) अणु
		netdev_warn(dev, "Reject SRIOV config request since if is down!\n");
		rtnl_unlock();
		वापस 0;
	पूर्ण
	अगर (test_bit(BNXT_STATE_IN_FW_RESET, &bp->state)) अणु
		netdev_warn(dev, "Reject SRIOV config request when FW reset is in progress\n");
		rtnl_unlock();
		वापस 0;
	पूर्ण
	bp->sriov_cfg = true;
	rtnl_unlock();

	अगर (pci_vfs_asचिन्हित(bp->pdev)) अणु
		netdev_warn(dev, "Unable to configure SRIOV since some VFs are assigned to VMs.\n");
		num_vfs = 0;
		जाओ sriov_cfg_निकास;
	पूर्ण

	/* Check अगर enabled VFs is same as requested */
	अगर (num_vfs && num_vfs == bp->pf.active_vfs)
		जाओ sriov_cfg_निकास;

	/* अगर there are previous existing VFs, clean them up */
	bnxt_sriov_disable(bp);
	अगर (!num_vfs)
		जाओ sriov_cfg_निकास;

	bnxt_sriov_enable(bp, &num_vfs);

sriov_cfg_निकास:
	bp->sriov_cfg = false;
	wake_up(&bp->sriov_cfg_रुको);

	वापस num_vfs;
पूर्ण

अटल पूर्णांक bnxt_hwrm_fwd_resp(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf,
			      व्योम *encap_resp, __le64 encap_resp_addr,
			      __le16 encap_resp_cpr, u32 msg_size)
अणु
	पूर्णांक rc = 0;
	काष्ठा hwrm_fwd_resp_input req = अणु0पूर्ण;

	अगर (BNXT_FWD_RESP_SIZE_ERR(msg_size))
		वापस -EINVAL;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FWD_RESP, -1, -1);

	/* Set the new target id */
	req.target_id = cpu_to_le16(vf->fw_fid);
	req.encap_resp_target_id = cpu_to_le16(vf->fw_fid);
	req.encap_resp_len = cpu_to_le16(msg_size);
	req.encap_resp_addr = encap_resp_addr;
	req.encap_resp_cmpl_ring = encap_resp_cpr;
	स_नकल(req.encap_resp, encap_resp, msg_size);

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		netdev_err(bp->dev, "hwrm_fwd_resp failed. rc:%d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_fwd_err_resp(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf,
				  u32 msg_size)
अणु
	पूर्णांक rc = 0;
	काष्ठा hwrm_reject_fwd_resp_input req = अणु0पूर्ण;

	अगर (BNXT_REJ_FWD_RESP_SIZE_ERR(msg_size))
		वापस -EINVAL;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_REJECT_FWD_RESP, -1, -1);
	/* Set the new target id */
	req.target_id = cpu_to_le16(vf->fw_fid);
	req.encap_resp_target_id = cpu_to_le16(vf->fw_fid);
	स_नकल(req.encap_request, vf->hwrm_cmd_req_addr, msg_size);

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		netdev_err(bp->dev, "hwrm_fwd_err_resp failed. rc:%d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_exec_fwd_resp(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf,
				   u32 msg_size)
अणु
	पूर्णांक rc = 0;
	काष्ठा hwrm_exec_fwd_resp_input req = अणु0पूर्ण;

	अगर (BNXT_EXEC_FWD_RESP_SIZE_ERR(msg_size))
		वापस -EINVAL;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_EXEC_FWD_RESP, -1, -1);
	/* Set the new target id */
	req.target_id = cpu_to_le16(vf->fw_fid);
	req.encap_resp_target_id = cpu_to_le16(vf->fw_fid);
	स_नकल(req.encap_request, vf->hwrm_cmd_req_addr, msg_size);

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		netdev_err(bp->dev, "hwrm_exec_fw_resp failed. rc:%d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_vf_configure_mac(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf)
अणु
	u32 msg_size = माप(काष्ठा hwrm_func_vf_cfg_input);
	काष्ठा hwrm_func_vf_cfg_input *req =
		(काष्ठा hwrm_func_vf_cfg_input *)vf->hwrm_cmd_req_addr;

	/* Allow VF to set a valid MAC address, अगर trust is set to on or
	 * अगर the PF asचिन्हित MAC address is zero
	 */
	अगर (req->enables & cpu_to_le32(FUNC_VF_CFG_REQ_ENABLES_DFLT_MAC_ADDR)) अणु
		bool trust = bnxt_is_trusted_vf(bp, vf);

		अगर (is_valid_ether_addr(req->dflt_mac_addr) &&
		    (trust || !is_valid_ether_addr(vf->mac_addr) ||
		     ether_addr_equal(req->dflt_mac_addr, vf->mac_addr))) अणु
			ether_addr_copy(vf->vf_mac_addr, req->dflt_mac_addr);
			वापस bnxt_hwrm_exec_fwd_resp(bp, vf, msg_size);
		पूर्ण
		वापस bnxt_hwrm_fwd_err_resp(bp, vf, msg_size);
	पूर्ण
	वापस bnxt_hwrm_exec_fwd_resp(bp, vf, msg_size);
पूर्ण

अटल पूर्णांक bnxt_vf_validate_set_mac(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf)
अणु
	u32 msg_size = माप(काष्ठा hwrm_cfa_l2_filter_alloc_input);
	काष्ठा hwrm_cfa_l2_filter_alloc_input *req =
		(काष्ठा hwrm_cfa_l2_filter_alloc_input *)vf->hwrm_cmd_req_addr;
	bool mac_ok = false;

	अगर (!is_valid_ether_addr((स्थिर u8 *)req->l2_addr))
		वापस bnxt_hwrm_fwd_err_resp(bp, vf, msg_size);

	/* Allow VF to set a valid MAC address, अगर trust is set to on.
	 * Or VF MAC address must first match MAC address in PF's context.
	 * Otherwise, it must match the VF MAC address अगर firmware spec >=
	 * 1.2.2
	 */
	अगर (bnxt_is_trusted_vf(bp, vf)) अणु
		mac_ok = true;
	पूर्ण अन्यथा अगर (is_valid_ether_addr(vf->mac_addr)) अणु
		अगर (ether_addr_equal((स्थिर u8 *)req->l2_addr, vf->mac_addr))
			mac_ok = true;
	पूर्ण अन्यथा अगर (is_valid_ether_addr(vf->vf_mac_addr)) अणु
		अगर (ether_addr_equal((स्थिर u8 *)req->l2_addr, vf->vf_mac_addr))
			mac_ok = true;
	पूर्ण अन्यथा अणु
		/* There are two हालs:
		 * 1.If firmware spec < 0x10202,VF MAC address is not क्रमwarded
		 *   to the PF and so it करोesn't have to match
		 * 2.Allow VF to modअगरy it's own MAC when PF has not asचिन्हित a
		 *   valid MAC address and firmware spec >= 0x10202
		 */
		mac_ok = true;
	पूर्ण
	अगर (mac_ok)
		वापस bnxt_hwrm_exec_fwd_resp(bp, vf, msg_size);
	वापस bnxt_hwrm_fwd_err_resp(bp, vf, msg_size);
पूर्ण

अटल पूर्णांक bnxt_vf_set_link(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf)
अणु
	पूर्णांक rc = 0;

	अगर (!(vf->flags & BNXT_VF_LINK_FORCED)) अणु
		/* real link */
		rc = bnxt_hwrm_exec_fwd_resp(
			bp, vf, माप(काष्ठा hwrm_port_phy_qcfg_input));
	पूर्ण अन्यथा अणु
		काष्ठा hwrm_port_phy_qcfg_output phy_qcfg_resp = अणु0पूर्ण;
		काष्ठा hwrm_port_phy_qcfg_input *phy_qcfg_req;

		phy_qcfg_req =
		(काष्ठा hwrm_port_phy_qcfg_input *)vf->hwrm_cmd_req_addr;
		mutex_lock(&bp->hwrm_cmd_lock);
		स_नकल(&phy_qcfg_resp, &bp->link_info.phy_qcfg_resp,
		       माप(phy_qcfg_resp));
		mutex_unlock(&bp->hwrm_cmd_lock);
		phy_qcfg_resp.resp_len = cpu_to_le16(माप(phy_qcfg_resp));
		phy_qcfg_resp.seq_id = phy_qcfg_req->seq_id;
		phy_qcfg_resp.valid = 1;

		अगर (vf->flags & BNXT_VF_LINK_UP) अणु
			/* अगर physical link is करोwn, क्रमce link up on VF */
			अगर (phy_qcfg_resp.link !=
			    PORT_PHY_QCFG_RESP_LINK_LINK) अणु
				phy_qcfg_resp.link =
					PORT_PHY_QCFG_RESP_LINK_LINK;
				phy_qcfg_resp.link_speed = cpu_to_le16(
					PORT_PHY_QCFG_RESP_LINK_SPEED_10GB);
				phy_qcfg_resp.duplex_cfg =
					PORT_PHY_QCFG_RESP_DUPLEX_CFG_FULL;
				phy_qcfg_resp.duplex_state =
					PORT_PHY_QCFG_RESP_DUPLEX_STATE_FULL;
				phy_qcfg_resp.छोड़ो =
					(PORT_PHY_QCFG_RESP_PAUSE_TX |
					 PORT_PHY_QCFG_RESP_PAUSE_RX);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* क्रमce link करोwn */
			phy_qcfg_resp.link = PORT_PHY_QCFG_RESP_LINK_NO_LINK;
			phy_qcfg_resp.link_speed = 0;
			phy_qcfg_resp.duplex_state =
				PORT_PHY_QCFG_RESP_DUPLEX_STATE_HALF;
			phy_qcfg_resp.छोड़ो = 0;
		पूर्ण
		rc = bnxt_hwrm_fwd_resp(bp, vf, &phy_qcfg_resp,
					phy_qcfg_req->resp_addr,
					phy_qcfg_req->cmpl_ring,
					माप(phy_qcfg_resp));
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_vf_req_validate_snd(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf)
अणु
	पूर्णांक rc = 0;
	काष्ठा input *encap_req = vf->hwrm_cmd_req_addr;
	u32 req_type = le16_to_cpu(encap_req->req_type);

	चयन (req_type) अणु
	हाल HWRM_FUNC_VF_CFG:
		rc = bnxt_vf_configure_mac(bp, vf);
		अवरोध;
	हाल HWRM_CFA_L2_FILTER_ALLOC:
		rc = bnxt_vf_validate_set_mac(bp, vf);
		अवरोध;
	हाल HWRM_FUNC_CFG:
		/* TODO Validate अगर VF is allowed to change mac address,
		 * mtu, num of rings etc
		 */
		rc = bnxt_hwrm_exec_fwd_resp(
			bp, vf, माप(काष्ठा hwrm_func_cfg_input));
		अवरोध;
	हाल HWRM_PORT_PHY_QCFG:
		rc = bnxt_vf_set_link(bp, vf);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

व्योम bnxt_hwrm_exec_fwd_req(काष्ठा bnxt *bp)
अणु
	u32 i = 0, active_vfs = bp->pf.active_vfs, vf_id;

	/* Scan through VF's and process commands */
	जबतक (1) अणु
		vf_id = find_next_bit(bp->pf.vf_event_bmap, active_vfs, i);
		अगर (vf_id >= active_vfs)
			अवरोध;

		clear_bit(vf_id, bp->pf.vf_event_bmap);
		bnxt_vf_req_validate_snd(bp, &bp->pf.vf[vf_id]);
		i = vf_id + 1;
	पूर्ण
पूर्ण

पूर्णांक bnxt_approve_mac(काष्ठा bnxt *bp, u8 *mac, bool strict)
अणु
	काष्ठा hwrm_func_vf_cfg_input req = अणु0पूर्ण;
	पूर्णांक rc = 0;

	अगर (!BNXT_VF(bp))
		वापस 0;

	अगर (bp->hwrm_spec_code < 0x10202) अणु
		अगर (is_valid_ether_addr(bp->vf.mac_addr))
			rc = -EADDRNOTAVAIL;
		जाओ mac_करोne;
	पूर्ण
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_VF_CFG, -1, -1);
	req.enables = cpu_to_le32(FUNC_VF_CFG_REQ_ENABLES_DFLT_MAC_ADDR);
	स_नकल(req.dflt_mac_addr, mac, ETH_ALEN);
	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
mac_करोne:
	अगर (rc && strict) अणु
		rc = -EADDRNOTAVAIL;
		netdev_warn(bp->dev, "VF MAC address %pM not approved by the PF\n",
			    mac);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

व्योम bnxt_update_vf_mac(काष्ठा bnxt *bp)
अणु
	काष्ठा hwrm_func_qcaps_input req = अणु0पूर्ण;
	काष्ठा hwrm_func_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	bool inक्रमm_pf = false;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCAPS, -1, -1);
	req.fid = cpu_to_le16(0xffff);

	mutex_lock(&bp->hwrm_cmd_lock);
	अगर (_hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT))
		जाओ update_vf_mac_निकास;

	/* Store MAC address from the firmware.  There are 2 हालs:
	 * 1. MAC address is valid.  It is asचिन्हित from the PF and we
	 *    need to override the current VF MAC address with it.
	 * 2. MAC address is zero.  The VF will use a अक्रमom MAC address by
	 *    शेष but the stored zero MAC will allow the VF user to change
	 *    the अक्रमom MAC address using nकरो_set_mac_address() अगर he wants.
	 */
	अगर (!ether_addr_equal(resp->mac_address, bp->vf.mac_addr)) अणु
		स_नकल(bp->vf.mac_addr, resp->mac_address, ETH_ALEN);
		/* This means we are now using our own MAC address, let
		 * the PF know about this MAC address.
		 */
		अगर (!is_valid_ether_addr(bp->vf.mac_addr))
			inक्रमm_pf = true;
	पूर्ण

	/* overग_लिखो netdev dev_addr with admin VF MAC */
	अगर (is_valid_ether_addr(bp->vf.mac_addr))
		स_नकल(bp->dev->dev_addr, bp->vf.mac_addr, ETH_ALEN);
update_vf_mac_निकास:
	mutex_unlock(&bp->hwrm_cmd_lock);
	अगर (inक्रमm_pf)
		bnxt_approve_mac(bp, bp->dev->dev_addr, false);
पूर्ण

#अन्यथा

पूर्णांक bnxt_cfg_hw_sriov(काष्ठा bnxt *bp, पूर्णांक *num_vfs, bool reset)
अणु
	अगर (*num_vfs)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

व्योम bnxt_sriov_disable(काष्ठा bnxt *bp)
अणु
पूर्ण

व्योम bnxt_hwrm_exec_fwd_req(काष्ठा bnxt *bp)
अणु
	netdev_err(bp->dev, "Invalid VF message received when SRIOV is not enable\n");
पूर्ण

व्योम bnxt_update_vf_mac(काष्ठा bnxt *bp)
अणु
पूर्ण

पूर्णांक bnxt_approve_mac(काष्ठा bnxt *bp, u8 *mac, bool strict)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
