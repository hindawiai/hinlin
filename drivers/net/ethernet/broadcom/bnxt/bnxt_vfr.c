<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2016-2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/jhash.h>
#समावेश <net/pkt_cls.h>

#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"
#समावेश "bnxt_vfr.h"
#समावेश "bnxt_devlink.h"
#समावेश "bnxt_tc.h"

#अगर_घोषित CONFIG_BNXT_SRIOV

#घोषणा CFA_HANDLE_INVALID		0xffff
#घोषणा VF_IDX_INVALID			0xffff

अटल पूर्णांक hwrm_cfa_vfr_alloc(काष्ठा bnxt *bp, u16 vf_idx,
			      u16 *tx_cfa_action, u16 *rx_cfa_code)
अणु
	काष्ठा hwrm_cfa_vfr_alloc_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_cfa_vfr_alloc_input req = अणु 0 पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_VFR_ALLOC, -1, -1);
	req.vf_id = cpu_to_le16(vf_idx);
	प्र_लिखो(req.vfr_name, "vfr%d", vf_idx);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		*tx_cfa_action = le16_to_cpu(resp->tx_cfa_action);
		*rx_cfa_code = le16_to_cpu(resp->rx_cfa_code);
		netdev_dbg(bp->dev, "tx_cfa_action=0x%x, rx_cfa_code=0x%x",
			   *tx_cfa_action, *rx_cfa_code);
	पूर्ण अन्यथा अणु
		netdev_info(bp->dev, "%s error rc=%d\n", __func__, rc);
	पूर्ण

	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक hwrm_cfa_vfr_मुक्त(काष्ठा bnxt *bp, u16 vf_idx)
अणु
	काष्ठा hwrm_cfa_vfr_मुक्त_input req = अणु 0 पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_VFR_FREE, -1, -1);
	प्र_लिखो(req.vfr_name, "vfr%d", vf_idx);

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		netdev_info(bp->dev, "%s error rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_hwrm_vfr_qcfg(काष्ठा bnxt *bp, काष्ठा bnxt_vf_rep *vf_rep,
			      u16 *max_mtu)
अणु
	काष्ठा hwrm_func_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	काष्ठा hwrm_func_qcfg_input req = अणु0पूर्ण;
	u16 mtu;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCFG, -1, -1);
	req.fid = cpu_to_le16(bp->pf.vf[vf_rep->vf_idx].fw_fid);

	mutex_lock(&bp->hwrm_cmd_lock);

	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		mtu = le16_to_cpu(resp->max_mtu_configured);
		अगर (!mtu)
			*max_mtu = BNXT_MAX_MTU;
		अन्यथा
			*max_mtu = mtu;
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_vf_rep_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt_vf_rep *vf_rep = netdev_priv(dev);
	काष्ठा bnxt *bp = vf_rep->bp;

	/* Enable link and TX only अगर the parent PF is खोलो. */
	अगर (netअगर_running(bp->dev)) अणु
		netअगर_carrier_on(dev);
		netअगर_tx_start_all_queues(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_vf_rep_बंद(काष्ठा net_device *dev)
अणु
	netअगर_carrier_off(dev);
	netअगर_tx_disable(dev);

	वापस 0;
पूर्ण

अटल netdev_tx_t bnxt_vf_rep_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा bnxt_vf_rep *vf_rep = netdev_priv(dev);
	पूर्णांक rc, len = skb->len;

	skb_dst_drop(skb);
	dst_hold((काष्ठा dst_entry *)vf_rep->dst);
	skb_dst_set(skb, (काष्ठा dst_entry *)vf_rep->dst);
	skb->dev = vf_rep->dst->u.port_info.lower_dev;

	rc = dev_queue_xmit(skb);
	अगर (!rc) अणु
		vf_rep->tx_stats.packets++;
		vf_rep->tx_stats.bytes += len;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम
bnxt_vf_rep_get_stats64(काष्ठा net_device *dev,
			काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा bnxt_vf_rep *vf_rep = netdev_priv(dev);

	stats->rx_packets = vf_rep->rx_stats.packets;
	stats->rx_bytes = vf_rep->rx_stats.bytes;
	stats->tx_packets = vf_rep->tx_stats.packets;
	stats->tx_bytes = vf_rep->tx_stats.bytes;
पूर्ण

अटल पूर्णांक bnxt_vf_rep_setup_tc_block_cb(क्रमागत tc_setup_type type,
					 व्योम *type_data,
					 व्योम *cb_priv)
अणु
	काष्ठा bnxt_vf_rep *vf_rep = cb_priv;
	काष्ठा bnxt *bp = vf_rep->bp;
	पूर्णांक vf_fid = bp->pf.vf[vf_rep->vf_idx].fw_fid;

	अगर (!bnxt_tc_flower_enabled(vf_rep->bp) ||
	    !tc_cls_can_offload_and_chain0(bp->dev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस bnxt_tc_setup_flower(bp, vf_fid, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(bnxt_vf_block_cb_list);

अटल पूर्णांक bnxt_vf_rep_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
				व्योम *type_data)
अणु
	काष्ठा bnxt_vf_rep *vf_rep = netdev_priv(dev);

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &bnxt_vf_block_cb_list,
						  bnxt_vf_rep_setup_tc_block_cb,
						  vf_rep, vf_rep, true);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

काष्ठा net_device *bnxt_get_vf_rep(काष्ठा bnxt *bp, u16 cfa_code)
अणु
	u16 vf_idx;

	अगर (cfa_code && bp->cfa_code_map && BNXT_PF(bp)) अणु
		vf_idx = bp->cfa_code_map[cfa_code];
		अगर (vf_idx != VF_IDX_INVALID)
			वापस bp->vf_reps[vf_idx]->dev;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम bnxt_vf_rep_rx(काष्ठा bnxt *bp, काष्ठा sk_buff *skb)
अणु
	काष्ठा bnxt_vf_rep *vf_rep = netdev_priv(skb->dev);

	vf_rep->rx_stats.bytes += skb->len;
	vf_rep->rx_stats.packets++;

	netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक bnxt_vf_rep_get_phys_port_name(काष्ठा net_device *dev, अक्षर *buf,
					  माप_प्रकार len)
अणु
	काष्ठा bnxt_vf_rep *vf_rep = netdev_priv(dev);
	काष्ठा pci_dev *pf_pdev = vf_rep->bp->pdev;
	पूर्णांक rc;

	rc = snम_लिखो(buf, len, "pf%dvf%d", PCI_FUNC(pf_pdev->devfn),
		      vf_rep->vf_idx);
	अगर (rc >= len)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल व्योम bnxt_vf_rep_get_drvinfo(काष्ठा net_device *dev,
				    काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
पूर्ण

अटल पूर्णांक bnxt_vf_rep_get_port_parent_id(काष्ठा net_device *dev,
					  काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा bnxt_vf_rep *vf_rep = netdev_priv(dev);

	/* as only PORT_PARENT_ID is supported currently use common code
	 * between PF and VF-rep क्रम now.
	 */
	वापस bnxt_get_port_parent_id(vf_rep->bp->dev, ppid);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bnxt_vf_rep_ethtool_ops = अणु
	.get_drvinfo		= bnxt_vf_rep_get_drvinfo
पूर्ण;

अटल स्थिर काष्ठा net_device_ops bnxt_vf_rep_netdev_ops = अणु
	.nकरो_खोलो		= bnxt_vf_rep_खोलो,
	.nकरो_stop		= bnxt_vf_rep_बंद,
	.nकरो_start_xmit		= bnxt_vf_rep_xmit,
	.nकरो_get_stats64	= bnxt_vf_rep_get_stats64,
	.nकरो_setup_tc		= bnxt_vf_rep_setup_tc,
	.nकरो_get_port_parent_id	= bnxt_vf_rep_get_port_parent_id,
	.nकरो_get_phys_port_name = bnxt_vf_rep_get_phys_port_name
पूर्ण;

bool bnxt_dev_is_vf_rep(काष्ठा net_device *dev)
अणु
	वापस dev->netdev_ops == &bnxt_vf_rep_netdev_ops;
पूर्ण

/* Called when the parent PF पूर्णांकerface is बंदd:
 * As the mode transition from SWITCHDEV to LEGACY
 * happens under the rtnl_lock() this routine is safe
 * under the rtnl_lock()
 */
व्योम bnxt_vf_reps_बंद(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_vf_rep *vf_rep;
	u16 num_vfs, i;

	अगर (bp->eचयन_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		वापस;

	num_vfs = pci_num_vf(bp->pdev);
	क्रम (i = 0; i < num_vfs; i++) अणु
		vf_rep = bp->vf_reps[i];
		अगर (netअगर_running(vf_rep->dev))
			bnxt_vf_rep_बंद(vf_rep->dev);
	पूर्ण
पूर्ण

/* Called when the parent PF पूर्णांकerface is खोलोed (re-खोलोed):
 * As the mode transition from SWITCHDEV to LEGACY
 * happen under the rtnl_lock() this routine is safe
 * under the rtnl_lock()
 */
व्योम bnxt_vf_reps_खोलो(काष्ठा bnxt *bp)
अणु
	पूर्णांक i;

	अगर (bp->eचयन_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		वापस;

	क्रम (i = 0; i < pci_num_vf(bp->pdev); i++) अणु
		/* Open the VF-Rep only अगर it is allocated in the FW */
		अगर (bp->vf_reps[i]->tx_cfa_action != CFA_HANDLE_INVALID)
			bnxt_vf_rep_खोलो(bp->vf_reps[i]->dev);
	पूर्ण
पूर्ण

अटल व्योम __bnxt_मुक्त_one_vf_rep(काष्ठा bnxt *bp, काष्ठा bnxt_vf_rep *vf_rep)
अणु
	अगर (!vf_rep)
		वापस;

	अगर (vf_rep->dst) अणु
		dst_release((काष्ठा dst_entry *)vf_rep->dst);
		vf_rep->dst = शून्य;
	पूर्ण
	अगर (vf_rep->tx_cfa_action != CFA_HANDLE_INVALID) अणु
		hwrm_cfa_vfr_मुक्त(bp, vf_rep->vf_idx);
		vf_rep->tx_cfa_action = CFA_HANDLE_INVALID;
	पूर्ण
पूर्ण

अटल व्योम __bnxt_vf_reps_destroy(काष्ठा bnxt *bp)
अणु
	u16 num_vfs = pci_num_vf(bp->pdev);
	काष्ठा bnxt_vf_rep *vf_rep;
	पूर्णांक i;

	क्रम (i = 0; i < num_vfs; i++) अणु
		vf_rep = bp->vf_reps[i];
		अगर (vf_rep) अणु
			__bnxt_मुक्त_one_vf_rep(bp, vf_rep);
			अगर (vf_rep->dev) अणु
				/* अगर रेजिस्टर_netdev failed, then netdev_ops
				 * would have been set to शून्य
				 */
				अगर (vf_rep->dev->netdev_ops)
					unरेजिस्टर_netdev(vf_rep->dev);
				मुक्त_netdev(vf_rep->dev);
			पूर्ण
		पूर्ण
	पूर्ण

	kमुक्त(bp->vf_reps);
	bp->vf_reps = शून्य;
पूर्ण

व्योम bnxt_vf_reps_destroy(काष्ठा bnxt *bp)
अणु
	bool बंदd = false;

	अगर (bp->eचयन_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		वापस;

	अगर (!bp->vf_reps)
		वापस;

	/* Ensure that parent PF's and VF-reps' RX/TX has been quiesced
	 * beक्रमe proceeding with VF-rep cleanup.
	 */
	rtnl_lock();
	अगर (netअगर_running(bp->dev)) अणु
		bnxt_बंद_nic(bp, false, false);
		बंदd = true;
	पूर्ण
	/* un-publish cfa_code_map so that RX path can't see it anymore */
	kमुक्त(bp->cfa_code_map);
	bp->cfa_code_map = शून्य;
	bp->eचयन_mode = DEVLINK_ESWITCH_MODE_LEGACY;

	अगर (बंदd)
		bnxt_खोलो_nic(bp, false, false);
	rtnl_unlock();

	/* Need to call vf_reps_destroy() outside of rntl_lock
	 * as unरेजिस्टर_netdev takes rtnl_lock
	 */
	__bnxt_vf_reps_destroy(bp);
पूर्ण

/* Free the VF-Reps in firmware, during firmware hot-reset processing.
 * Note that the VF-Rep netdevs are still active (not unरेजिस्टरed) during
 * this process. As the mode transition from SWITCHDEV to LEGACY happens
 * under the rtnl_lock() this routine is safe under the rtnl_lock().
 */
व्योम bnxt_vf_reps_मुक्त(काष्ठा bnxt *bp)
अणु
	u16 num_vfs = pci_num_vf(bp->pdev);
	पूर्णांक i;

	अगर (bp->eचयन_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		वापस;

	क्रम (i = 0; i < num_vfs; i++)
		__bnxt_मुक्त_one_vf_rep(bp, bp->vf_reps[i]);
पूर्ण

अटल पूर्णांक bnxt_alloc_vf_rep(काष्ठा bnxt *bp, काष्ठा bnxt_vf_rep *vf_rep,
			     u16 *cfa_code_map)
अणु
	/* get cfa handles from FW */
	अगर (hwrm_cfa_vfr_alloc(bp, vf_rep->vf_idx, &vf_rep->tx_cfa_action,
			       &vf_rep->rx_cfa_code))
		वापस -ENOLINK;

	cfa_code_map[vf_rep->rx_cfa_code] = vf_rep->vf_idx;
	vf_rep->dst = metadata_dst_alloc(0, METADATA_HW_PORT_MUX, GFP_KERNEL);
	अगर (!vf_rep->dst)
		वापस -ENOMEM;

	/* only cfa_action is needed to mux a packet जबतक TXing */
	vf_rep->dst->u.port_info.port_id = vf_rep->tx_cfa_action;
	vf_rep->dst->u.port_info.lower_dev = bp->dev;

	वापस 0;
पूर्ण

/* Allocate the VF-Reps in firmware, during firmware hot-reset processing.
 * Note that the VF-Rep netdevs are still active (not unरेजिस्टरed) during
 * this process. As the mode transition from SWITCHDEV to LEGACY happens
 * under the rtnl_lock() this routine is safe under the rtnl_lock().
 */
पूर्णांक bnxt_vf_reps_alloc(काष्ठा bnxt *bp)
अणु
	u16 *cfa_code_map = bp->cfa_code_map, num_vfs = pci_num_vf(bp->pdev);
	काष्ठा bnxt_vf_rep *vf_rep;
	पूर्णांक rc, i;

	अगर (bp->eचयन_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		वापस 0;

	अगर (!cfa_code_map)
		वापस -EINVAL;

	क्रम (i = 0; i < MAX_CFA_CODE; i++)
		cfa_code_map[i] = VF_IDX_INVALID;

	क्रम (i = 0; i < num_vfs; i++) अणु
		vf_rep = bp->vf_reps[i];
		vf_rep->vf_idx = i;

		rc = bnxt_alloc_vf_rep(bp, vf_rep, cfa_code_map);
		अगर (rc)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	netdev_info(bp->dev, "%s error=%d\n", __func__, rc);
	bnxt_vf_reps_मुक्त(bp);
	वापस rc;
पूर्ण

/* Use the OUI of the PF's perm addr and report the same mac addr
 * क्रम the same VF-rep each समय
 */
अटल व्योम bnxt_vf_rep_eth_addr_gen(u8 *src_mac, u16 vf_idx, u8 *mac)
अणु
	u32 addr;

	ether_addr_copy(mac, src_mac);

	addr = jhash(src_mac, ETH_ALEN, 0) + vf_idx;
	mac[3] = (u8)(addr & 0xFF);
	mac[4] = (u8)((addr >> 8) & 0xFF);
	mac[5] = (u8)((addr >> 16) & 0xFF);
पूर्ण

अटल व्योम bnxt_vf_rep_netdev_init(काष्ठा bnxt *bp, काष्ठा bnxt_vf_rep *vf_rep,
				    काष्ठा net_device *dev)
अणु
	काष्ठा net_device *pf_dev = bp->dev;
	u16 max_mtu;

	dev->netdev_ops = &bnxt_vf_rep_netdev_ops;
	dev->ethtool_ops = &bnxt_vf_rep_ethtool_ops;
	/* Just inherit all the featues of the parent PF as the VF-R
	 * uses the RX/TX rings of the parent PF
	 */
	dev->hw_features = pf_dev->hw_features;
	dev->gso_partial_features = pf_dev->gso_partial_features;
	dev->vlan_features = pf_dev->vlan_features;
	dev->hw_enc_features = pf_dev->hw_enc_features;
	dev->features |= pf_dev->features;
	bnxt_vf_rep_eth_addr_gen(bp->pf.mac_addr, vf_rep->vf_idx,
				 dev->perm_addr);
	ether_addr_copy(dev->dev_addr, dev->perm_addr);
	/* Set VF-Rep's max-mtu to the corresponding VF's max-mtu */
	अगर (!bnxt_hwrm_vfr_qcfg(bp, vf_rep, &max_mtu))
		dev->max_mtu = max_mtu;
	dev->min_mtu = ETH_ZLEN;
पूर्ण

अटल पूर्णांक bnxt_vf_reps_create(काष्ठा bnxt *bp)
अणु
	u16 *cfa_code_map = शून्य, num_vfs = pci_num_vf(bp->pdev);
	काष्ठा bnxt_vf_rep *vf_rep;
	काष्ठा net_device *dev;
	पूर्णांक rc, i;

	अगर (!(bp->flags & BNXT_FLAG_DSN_VALID))
		वापस -ENODEV;

	bp->vf_reps = kसुस्मृति(num_vfs, माप(vf_rep), GFP_KERNEL);
	अगर (!bp->vf_reps)
		वापस -ENOMEM;

	/* storage क्रम cfa_code to vf-idx mapping */
	cfa_code_map = kदो_स्मृति_array(MAX_CFA_CODE, माप(*bp->cfa_code_map),
				     GFP_KERNEL);
	अगर (!cfa_code_map) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण
	क्रम (i = 0; i < MAX_CFA_CODE; i++)
		cfa_code_map[i] = VF_IDX_INVALID;

	क्रम (i = 0; i < num_vfs; i++) अणु
		dev = alloc_etherdev(माप(*vf_rep));
		अगर (!dev) अणु
			rc = -ENOMEM;
			जाओ err;
		पूर्ण

		vf_rep = netdev_priv(dev);
		bp->vf_reps[i] = vf_rep;
		vf_rep->dev = dev;
		vf_rep->bp = bp;
		vf_rep->vf_idx = i;
		vf_rep->tx_cfa_action = CFA_HANDLE_INVALID;

		rc = bnxt_alloc_vf_rep(bp, vf_rep, cfa_code_map);
		अगर (rc)
			जाओ err;

		bnxt_vf_rep_netdev_init(bp, vf_rep, dev);
		rc = रेजिस्टर_netdev(dev);
		अगर (rc) अणु
			/* no need क्रम unरेजिस्टर_netdev in cleanup */
			dev->netdev_ops = शून्य;
			जाओ err;
		पूर्ण
	पूर्ण

	/* publish cfa_code_map only after all VF-reps have been initialized */
	bp->cfa_code_map = cfa_code_map;
	bp->eचयन_mode = DEVLINK_ESWITCH_MODE_SWITCHDEV;
	netअगर_keep_dst(bp->dev);
	वापस 0;

err:
	netdev_info(bp->dev, "%s error=%d\n", __func__, rc);
	kमुक्त(cfa_code_map);
	__bnxt_vf_reps_destroy(bp);
	वापस rc;
पूर्ण

/* Devlink related routines */
पूर्णांक bnxt_dl_eचयन_mode_get(काष्ठा devlink *devlink, u16 *mode)
अणु
	काष्ठा bnxt *bp = bnxt_get_bp_from_dl(devlink);

	*mode = bp->eचयन_mode;
	वापस 0;
पूर्ण

पूर्णांक bnxt_dl_eचयन_mode_set(काष्ठा devlink *devlink, u16 mode,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bnxt *bp = bnxt_get_bp_from_dl(devlink);
	पूर्णांक rc = 0;

	mutex_lock(&bp->sriov_lock);
	अगर (bp->eचयन_mode == mode) अणु
		netdev_info(bp->dev, "already in %s eswitch mode\n",
			    mode == DEVLINK_ESWITCH_MODE_LEGACY ?
			    "legacy" : "switchdev");
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण

	चयन (mode) अणु
	हाल DEVLINK_ESWITCH_MODE_LEGACY:
		bnxt_vf_reps_destroy(bp);
		अवरोध;

	हाल DEVLINK_ESWITCH_MODE_SWITCHDEV:
		अगर (bp->hwrm_spec_code < 0x10803) अणु
			netdev_warn(bp->dev, "FW does not support SRIOV E-Switch SWITCHDEV mode\n");
			rc = -ENOTSUPP;
			जाओ करोne;
		पूर्ण

		अगर (pci_num_vf(bp->pdev) == 0) अणु
			netdev_info(bp->dev, "Enable VFs before setting switchdev mode\n");
			rc = -EPERM;
			जाओ करोne;
		पूर्ण
		rc = bnxt_vf_reps_create(bp);
		अवरोध;

	शेष:
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण
करोne:
	mutex_unlock(&bp->sriov_lock);
	वापस rc;
पूर्ण

#पूर्ण_अगर
