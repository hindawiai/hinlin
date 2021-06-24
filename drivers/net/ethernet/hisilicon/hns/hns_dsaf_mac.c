<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "hns_dsaf_main.h"
#समावेश "hns_dsaf_misc.h"
#समावेश "hns_dsaf_rcb.h"

#घोषणा MAC_EN_FLAG_V		0xada0328

अटल स्थिर u16 mac_phy_to_speed[] = अणु
	[PHY_INTERFACE_MODE_MII] = MAC_SPEED_100,
	[PHY_INTERFACE_MODE_GMII] = MAC_SPEED_1000,
	[PHY_INTERFACE_MODE_SGMII] = MAC_SPEED_1000,
	[PHY_INTERFACE_MODE_TBI] = MAC_SPEED_1000,
	[PHY_INTERFACE_MODE_RMII] = MAC_SPEED_100,
	[PHY_INTERFACE_MODE_RGMII] = MAC_SPEED_1000,
	[PHY_INTERFACE_MODE_RGMII_ID] = MAC_SPEED_1000,
	[PHY_INTERFACE_MODE_RGMII_RXID]	= MAC_SPEED_1000,
	[PHY_INTERFACE_MODE_RGMII_TXID]	= MAC_SPEED_1000,
	[PHY_INTERFACE_MODE_RTBI] = MAC_SPEED_1000,
	[PHY_INTERFACE_MODE_XGMII] = MAC_SPEED_10000
पूर्ण;

अटल स्थिर क्रमागत mac_mode g_mac_mode_100[] = अणु
	[PHY_INTERFACE_MODE_MII]	= MAC_MODE_MII_100,
	[PHY_INTERFACE_MODE_RMII]   = MAC_MODE_RMII_100
पूर्ण;

अटल स्थिर क्रमागत mac_mode g_mac_mode_1000[] = अणु
	[PHY_INTERFACE_MODE_GMII]   = MAC_MODE_GMII_1000,
	[PHY_INTERFACE_MODE_SGMII]  = MAC_MODE_SGMII_1000,
	[PHY_INTERFACE_MODE_TBI]	= MAC_MODE_TBI_1000,
	[PHY_INTERFACE_MODE_RGMII]  = MAC_MODE_RGMII_1000,
	[PHY_INTERFACE_MODE_RGMII_ID]   = MAC_MODE_RGMII_1000,
	[PHY_INTERFACE_MODE_RGMII_RXID] = MAC_MODE_RGMII_1000,
	[PHY_INTERFACE_MODE_RGMII_TXID] = MAC_MODE_RGMII_1000,
	[PHY_INTERFACE_MODE_RTBI]   = MAC_MODE_RTBI_1000
पूर्ण;

अटल क्रमागत mac_mode hns_get_enet_पूर्णांकerface(स्थिर काष्ठा hns_mac_cb *mac_cb)
अणु
	चयन (mac_cb->max_speed) अणु
	हाल MAC_SPEED_100:
		वापस g_mac_mode_100[mac_cb->phy_अगर];
	हाल MAC_SPEED_1000:
		वापस g_mac_mode_1000[mac_cb->phy_अगर];
	हाल MAC_SPEED_10000:
		वापस MAC_MODE_XGMII_10000;
	शेष:
		वापस MAC_MODE_MII_100;
	पूर्ण
पूर्ण

व्योम hns_mac_get_link_status(काष्ठा hns_mac_cb *mac_cb, u32 *link_status)
अणु
	काष्ठा mac_driver *mac_ctrl_drv;
	पूर्णांक ret, sfp_prsnt;

	mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	अगर (mac_ctrl_drv->get_link_status)
		mac_ctrl_drv->get_link_status(mac_ctrl_drv, link_status);
	अन्यथा
		*link_status = 0;

	अगर (mac_cb->media_type == HNAE_MEDIA_TYPE_FIBER) अणु
		ret = mac_cb->dsaf_dev->misc_op->get_sfp_prsnt(mac_cb,
							       &sfp_prsnt);
		अगर (!ret)
			*link_status = *link_status && sfp_prsnt;
	पूर्ण

	mac_cb->link = *link_status;
पूर्ण

पूर्णांक hns_mac_get_port_info(काष्ठा hns_mac_cb *mac_cb,
			  u8 *स्वतः_neg, u16 *speed, u8 *duplex)
अणु
	काष्ठा mac_driver *mac_ctrl_drv;
	काष्ठा mac_info    info;

	mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	अगर (!mac_ctrl_drv->get_info)
		वापस -ENODEV;

	mac_ctrl_drv->get_info(mac_ctrl_drv, &info);
	अगर (स्वतः_neg)
		*स्वतः_neg = info.स्वतः_neg;
	अगर (speed)
		*speed = info.speed;
	अगर (duplex)
		*duplex = info.duplex;

	वापस 0;
पूर्ण

/**
 *hns_mac_is_adjust_link - check is need change mac speed and duplex रेजिस्टर
 *@mac_cb: mac device
 *@speed: phy device speed
 *@duplex:phy device duplex
 *
 */
bool hns_mac_need_adjust_link(काष्ठा hns_mac_cb *mac_cb, पूर्णांक speed, पूर्णांक duplex)
अणु
	काष्ठा mac_driver *mac_ctrl_drv;

	mac_ctrl_drv = (काष्ठा mac_driver *)(mac_cb->priv.mac);

	अगर (mac_ctrl_drv->need_adjust_link)
		वापस mac_ctrl_drv->need_adjust_link(mac_ctrl_drv,
			(क्रमागत mac_speed)speed, duplex);
	अन्यथा
		वापस true;
पूर्ण

व्योम hns_mac_adjust_link(काष्ठा hns_mac_cb *mac_cb, पूर्णांक speed, पूर्णांक duplex)
अणु
	पूर्णांक ret;
	काष्ठा mac_driver *mac_ctrl_drv;

	mac_ctrl_drv = (काष्ठा mac_driver *)(mac_cb->priv.mac);

	mac_cb->speed = speed;
	mac_cb->half_duplex = !duplex;

	अगर (mac_ctrl_drv->adjust_link) अणु
		ret = mac_ctrl_drv->adjust_link(mac_ctrl_drv,
			(क्रमागत mac_speed)speed, duplex);
		अगर (ret) अणु
			dev_err(mac_cb->dev,
				"adjust_link failed, %s mac%d ret = %#x!\n",
				mac_cb->dsaf_dev->ae_dev.name,
				mac_cb->mac_id, ret);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/**
 *hns_mac_get_inner_port_num - get mac table inner port number
 *@mac_cb: mac device
 *@vmid: vm id
 *@port_num:port number
 *
 */
पूर्णांक hns_mac_get_inner_port_num(काष्ठा hns_mac_cb *mac_cb, u8 vmid, u8 *port_num)
अणु
	पूर्णांक q_num_per_vf, vf_num_per_port;
	पूर्णांक vm_queue_id;
	u8 पंचांगp_port;

	अगर (mac_cb->dsaf_dev->dsaf_mode <= DSAF_MODE_ENABLE) अणु
		अगर (mac_cb->mac_id != DSAF_MAX_PORT_NUM) अणु
			dev_err(mac_cb->dev,
				"input invalid, %s mac%d vmid%d !\n",
				mac_cb->dsaf_dev->ae_dev.name,
				mac_cb->mac_id, vmid);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (mac_cb->dsaf_dev->dsaf_mode < DSAF_MODE_MAX) अणु
		अगर (mac_cb->mac_id >= DSAF_MAX_PORT_NUM) अणु
			dev_err(mac_cb->dev,
				"input invalid, %s mac%d vmid%d!\n",
				mac_cb->dsaf_dev->ae_dev.name,
				mac_cb->mac_id, vmid);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(mac_cb->dev, "dsaf mode invalid, %s mac%d!\n",
			mac_cb->dsaf_dev->ae_dev.name, mac_cb->mac_id);
		वापस -EINVAL;
	पूर्ण

	अगर (vmid >= mac_cb->dsaf_dev->rcb_common[0]->max_vfn) अणु
		dev_err(mac_cb->dev, "input invalid, %s mac%d vmid%d !\n",
			mac_cb->dsaf_dev->ae_dev.name, mac_cb->mac_id, vmid);
		वापस -EINVAL;
	पूर्ण

	q_num_per_vf = mac_cb->dsaf_dev->rcb_common[0]->max_q_per_vf;
	vf_num_per_port = mac_cb->dsaf_dev->rcb_common[0]->max_vfn;

	vm_queue_id = vmid * q_num_per_vf +
			vf_num_per_port * q_num_per_vf * mac_cb->mac_id;

	चयन (mac_cb->dsaf_dev->dsaf_mode) अणु
	हाल DSAF_MODE_ENABLE_FIX:
		पंचांगp_port = 0;
		अवरोध;
	हाल DSAF_MODE_DISABLE_FIX:
		पंचांगp_port = 0;
		अवरोध;
	हाल DSAF_MODE_ENABLE_0VM:
	हाल DSAF_MODE_ENABLE_8VM:
	हाल DSAF_MODE_ENABLE_16VM:
	हाल DSAF_MODE_ENABLE_32VM:
	हाल DSAF_MODE_ENABLE_128VM:
	हाल DSAF_MODE_DISABLE_2PORT_8VM:
	हाल DSAF_MODE_DISABLE_2PORT_16VM:
	हाल DSAF_MODE_DISABLE_2PORT_64VM:
	हाल DSAF_MODE_DISABLE_6PORT_0VM:
	हाल DSAF_MODE_DISABLE_6PORT_2VM:
	हाल DSAF_MODE_DISABLE_6PORT_4VM:
	हाल DSAF_MODE_DISABLE_6PORT_16VM:
		पंचांगp_port = vm_queue_id;
		अवरोध;
	शेष:
		dev_err(mac_cb->dev, "dsaf mode invalid, %s mac%d!\n",
			mac_cb->dsaf_dev->ae_dev.name, mac_cb->mac_id);
		वापस -EINVAL;
	पूर्ण
	पंचांगp_port += DSAF_BASE_INNER_PORT_NUM;

	*port_num = पंचांगp_port;

	वापस 0;
पूर्ण

/**
 *hns_mac_change_vf_addr - change vf mac address
 *@mac_cb: mac device
 *@vmid: vmid
 *@addr:mac address
 */
पूर्णांक hns_mac_change_vf_addr(काष्ठा hns_mac_cb *mac_cb,
			   u32 vmid, अक्षर *addr)
अणु
	पूर्णांक ret;
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	काष्ठा dsaf_drv_mac_single_dest_entry mac_entry;
	काष्ठा mac_entry_idx *old_entry;

	old_entry = &mac_cb->addr_entry_idx[vmid];
	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev)) अणु
		स_नकल(mac_entry.addr, addr, माप(mac_entry.addr));
		mac_entry.in_vlan_id = old_entry->vlan_id;
		mac_entry.in_port_num = mac_cb->mac_id;
		ret = hns_mac_get_inner_port_num(mac_cb, (u8)vmid,
						 &mac_entry.port_num);
		अगर (ret)
			वापस ret;

		अगर ((old_entry->valid != 0) &&
		    (स_भेद(old_entry->addr,
		    addr, माप(mac_entry.addr)) != 0)) अणु
			ret = hns_dsaf_del_mac_entry(dsaf_dev,
						     old_entry->vlan_id,
						     mac_cb->mac_id,
						     old_entry->addr);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = hns_dsaf_set_mac_uc_entry(dsaf_dev, &mac_entry);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर ((mac_ctrl_drv->set_mac_addr) && (vmid == 0))
		mac_ctrl_drv->set_mac_addr(mac_cb->priv.mac, addr);

	स_नकल(old_entry->addr, addr, माप(old_entry->addr));
	old_entry->valid = 1;
	वापस 0;
पूर्ण

पूर्णांक hns_mac_add_uc_addr(काष्ठा hns_mac_cb *mac_cb, u8 vf_id,
			स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	काष्ठा dsaf_drv_mac_single_dest_entry mac_entry;
	पूर्णांक ret;

	अगर (HNS_DSAF_IS_DEBUG(dsaf_dev))
		वापस -ENOSPC;

	स_रखो(&mac_entry, 0, माप(mac_entry));
	स_नकल(mac_entry.addr, addr, माप(mac_entry.addr));
	mac_entry.in_port_num = mac_cb->mac_id;
	ret = hns_mac_get_inner_port_num(mac_cb, vf_id, &mac_entry.port_num);
	अगर (ret)
		वापस ret;

	वापस hns_dsaf_set_mac_uc_entry(dsaf_dev, &mac_entry);
पूर्ण

पूर्णांक hns_mac_rm_uc_addr(काष्ठा hns_mac_cb *mac_cb, u8 vf_id,
		       स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	काष्ठा dsaf_drv_mac_single_dest_entry mac_entry;
	पूर्णांक ret;

	अगर (HNS_DSAF_IS_DEBUG(dsaf_dev))
		वापस -ENOSPC;

	स_रखो(&mac_entry, 0, माप(mac_entry));
	स_नकल(mac_entry.addr, addr, माप(mac_entry.addr));
	mac_entry.in_port_num = mac_cb->mac_id;
	ret = hns_mac_get_inner_port_num(mac_cb, vf_id, &mac_entry.port_num);
	अगर (ret)
		वापस ret;

	वापस hns_dsaf_rm_mac_addr(dsaf_dev, &mac_entry);
पूर्ण

पूर्णांक hns_mac_set_multi(काष्ठा hns_mac_cb *mac_cb,
		      u32 port_num, अक्षर *addr, bool enable)
अणु
	पूर्णांक ret;
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	काष्ठा dsaf_drv_mac_single_dest_entry mac_entry;

	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev) && addr) अणु
		स_नकल(mac_entry.addr, addr, माप(mac_entry.addr));
		mac_entry.in_vlan_id = 0;/*vlan_id;*/
		mac_entry.in_port_num = mac_cb->mac_id;
		mac_entry.port_num = port_num;

		अगर (!enable)
			ret = hns_dsaf_del_mac_mc_port(dsaf_dev, &mac_entry);
		अन्यथा
			ret = hns_dsaf_add_mac_mc_port(dsaf_dev, &mac_entry);
		अगर (ret) अणु
			dev_err(dsaf_dev->dev,
				"set mac mc port failed, %s mac%d ret = %#x!\n",
				mac_cb->dsaf_dev->ae_dev.name,
				mac_cb->mac_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hns_mac_clr_multicast(काष्ठा hns_mac_cb *mac_cb, पूर्णांक vfn)
अणु
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	u8 port_num;
	पूर्णांक ret = hns_mac_get_inner_port_num(mac_cb, vfn, &port_num);

	अगर (ret)
		वापस ret;

	वापस hns_dsaf_clr_mac_mc_port(dsaf_dev, mac_cb->mac_id, port_num);
पूर्ण

अटल व्योम hns_mac_param_get(काष्ठा mac_params *param,
			      काष्ठा hns_mac_cb *mac_cb)
अणु
	param->vaddr = mac_cb->vaddr;
	param->mac_mode = hns_get_enet_पूर्णांकerface(mac_cb);
	ether_addr_copy(param->addr, mac_cb->addr_entry_idx[0].addr);
	param->mac_id = mac_cb->mac_id;
	param->dev = mac_cb->dev;
पूर्ण

/**
 * hns_mac_queue_config_bc_en - set broadcast rx&tx enable
 * @mac_cb: mac device
 * @port_num: queue number
 * @vlan_id: vlan id`
 * @enable: enable
 * वापस 0 - success , negative --fail
 */
अटल पूर्णांक hns_mac_port_config_bc_en(काष्ठा hns_mac_cb *mac_cb,
				     u32 port_num, u16 vlan_id, bool enable)
अणु
	पूर्णांक ret;
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	काष्ठा dsaf_drv_mac_single_dest_entry mac_entry;

	/* directy वापस ok in debug network mode */
	अगर (mac_cb->mac_type == HNAE_PORT_DEBUG)
		वापस 0;

	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev)) अणु
		eth_broadcast_addr(mac_entry.addr);
		mac_entry.in_vlan_id = vlan_id;
		mac_entry.in_port_num = mac_cb->mac_id;
		mac_entry.port_num = port_num;

		अगर (!enable)
			ret = hns_dsaf_del_mac_mc_port(dsaf_dev, &mac_entry);
		अन्यथा
			ret = hns_dsaf_add_mac_mc_port(dsaf_dev, &mac_entry);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hns_mac_vm_config_bc_en - set broadcast rx&tx enable
 * @mac_cb: mac device
 * @vmid: vm id
 * @enable: enable
 * वापस 0 - success , negative --fail
 */
पूर्णांक hns_mac_vm_config_bc_en(काष्ठा hns_mac_cb *mac_cb, u32 vmid, bool enable)
अणु
	पूर्णांक ret;
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	u8 port_num;
	काष्ठा mac_entry_idx *uc_mac_entry;
	काष्ठा dsaf_drv_mac_single_dest_entry mac_entry;

	अगर (mac_cb->mac_type == HNAE_PORT_DEBUG)
		वापस 0;

	uc_mac_entry = &mac_cb->addr_entry_idx[vmid];

	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev))  अणु
		eth_broadcast_addr(mac_entry.addr);
		mac_entry.in_vlan_id = uc_mac_entry->vlan_id;
		mac_entry.in_port_num = mac_cb->mac_id;
		ret = hns_mac_get_inner_port_num(mac_cb, vmid, &port_num);
		अगर (ret)
			वापस ret;
		mac_entry.port_num = port_num;

		अगर (!enable)
			ret = hns_dsaf_del_mac_mc_port(dsaf_dev, &mac_entry);
		अन्यथा
			ret = hns_dsaf_add_mac_mc_port(dsaf_dev, &mac_entry);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hns_mac_रुको_fअगरo_clean(काष्ठा hns_mac_cb *mac_cb)
अणु
	काष्ठा mac_driver *drv = hns_mac_get_drv(mac_cb);

	अगर (drv->रुको_fअगरo_clean)
		वापस drv->रुको_fअगरo_clean(drv);

	वापस 0;
पूर्ण

व्योम hns_mac_reset(काष्ठा hns_mac_cb *mac_cb)
अणु
	काष्ठा mac_driver *drv = hns_mac_get_drv(mac_cb);
	bool is_ver1 = AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver);

	drv->mac_init(drv);

	अगर (drv->config_max_frame_length)
		drv->config_max_frame_length(drv, mac_cb->max_frm);

	अगर (drv->set_tx_स्वतः_छोड़ो_frames)
		drv->set_tx_स्वतः_छोड़ो_frames(drv, mac_cb->tx_छोड़ो_frm_समय);

	अगर (drv->set_an_mode)
		drv->set_an_mode(drv, 1);

	अगर (drv->mac_छोड़ोfrm_cfg) अणु
		अगर (mac_cb->mac_type == HNAE_PORT_DEBUG)
			drv->mac_छोड़ोfrm_cfg(drv, !is_ver1, !is_ver1);
		अन्यथा /* mac rx must disable, dsaf pfc बंद instead of it*/
			drv->mac_छोड़ोfrm_cfg(drv, 0, 1);
	पूर्ण
पूर्ण

पूर्णांक hns_mac_set_mtu(काष्ठा hns_mac_cb *mac_cb, u32 new_mtu, u32 buf_size)
अणु
	काष्ठा mac_driver *drv = hns_mac_get_drv(mac_cb);
	u32 new_frm = new_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;

	अगर (new_frm > HNS_RCB_RING_MAX_BD_PER_PKT * buf_size)
		वापस -EINVAL;

	अगर (!drv->config_max_frame_length)
		वापस -ECHILD;

	/* adjust max frame to be at least the size of a standard frame */
	अगर (new_frm < (ETH_FRAME_LEN + ETH_FCS_LEN + VLAN_HLEN))
		new_frm = (ETH_FRAME_LEN + ETH_FCS_LEN + VLAN_HLEN);

	drv->config_max_frame_length(drv, new_frm);

	mac_cb->max_frm = new_frm;

	वापस 0;
पूर्ण

व्योम hns_mac_start(काष्ठा hns_mac_cb *mac_cb)
अणु
	काष्ठा mac_driver *mac_drv = hns_mac_get_drv(mac_cb);

	/* क्रम virt */
	अगर (mac_drv->mac_en_flg == MAC_EN_FLAG_V) अणु
		/*plus 1 when the भव mac has been enabled */
		mac_drv->virt_dev_num += 1;
		वापस;
	पूर्ण

	अगर (mac_drv->mac_enable) अणु
		mac_drv->mac_enable(mac_cb->priv.mac, MAC_COMM_MODE_RX_AND_TX);
		mac_drv->mac_en_flg = MAC_EN_FLAG_V;
	पूर्ण
पूर्ण

व्योम hns_mac_stop(काष्ठा hns_mac_cb *mac_cb)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	/*modअगरied क्रम भवization */
	अगर (mac_ctrl_drv->virt_dev_num > 0) अणु
		mac_ctrl_drv->virt_dev_num -= 1;
		अगर (mac_ctrl_drv->virt_dev_num > 0)
			वापस;
	पूर्ण

	अगर (mac_ctrl_drv->mac_disable)
		mac_ctrl_drv->mac_disable(mac_cb->priv.mac,
			MAC_COMM_MODE_RX_AND_TX);

	mac_ctrl_drv->mac_en_flg = 0;
	mac_cb->link = 0;
	mac_cb->dsaf_dev->misc_op->cpld_reset_led(mac_cb);
पूर्ण

/**
 * hns_mac_get_स्वतःneg - get स्वतः स्वतःnegotiation
 * @mac_cb: mac control block
 * @स्वतः_neg: output poपूर्णांकer to स्वतःneg result
 * वापस 0 - success , negative --fail
 */
व्योम hns_mac_get_स्वतःneg(काष्ठा hns_mac_cb *mac_cb, u32 *स्वतः_neg)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	अगर (mac_ctrl_drv->स्वतःneg_stat)
		mac_ctrl_drv->स्वतःneg_stat(mac_ctrl_drv, स्वतः_neg);
	अन्यथा
		*स्वतः_neg = 0;
पूर्ण

/**
 * hns_mac_get_छोड़ोparam - set rx & tx छोड़ो parameter
 * @mac_cb: mac control block
 * @rx_en: rx enable status
 * @tx_en: tx enable status
 * वापस 0 - success , negative --fail
 */
व्योम hns_mac_get_छोड़ोparam(काष्ठा hns_mac_cb *mac_cb, u32 *rx_en, u32 *tx_en)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	अगर (mac_ctrl_drv->get_छोड़ो_enable) अणु
		mac_ctrl_drv->get_छोड़ो_enable(mac_ctrl_drv, rx_en, tx_en);
	पूर्ण अन्यथा अणु
		*rx_en = 0;
		*tx_en = 0;
	पूर्ण
पूर्ण

/**
 * hns_mac_set_स्वतःneg - set स्वतः स्वतःnegotiation
 * @mac_cb: mac control block
 * @enable: enable or not
 * वापस 0 - success , negative --fail
 */
पूर्णांक hns_mac_set_स्वतःneg(काष्ठा hns_mac_cb *mac_cb, u8 enable)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	अगर (mac_cb->phy_अगर == PHY_INTERFACE_MODE_XGMII && enable) अणु
		dev_err(mac_cb->dev, "enabling autoneg is not allowed!\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (mac_ctrl_drv->set_an_mode)
		mac_ctrl_drv->set_an_mode(mac_ctrl_drv, enable);

	वापस 0;
पूर्ण

/**
 * hns_mac_set_स्वतःneg - set rx & tx छोड़ो parameter
 * @mac_cb: mac control block
 * @rx_en: rx enable or not
 * @tx_en: tx enable or not
 * वापस 0 - success , negative --fail
 */
पूर्णांक hns_mac_set_छोड़ोparam(काष्ठा hns_mac_cb *mac_cb, u32 rx_en, u32 tx_en)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);
	bool is_ver1 = AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver);

	अगर (mac_cb->mac_type == HNAE_PORT_DEBUG) अणु
		अगर (is_ver1 && (tx_en || rx_en)) अणु
			dev_err(mac_cb->dev, "macv1 can't enable tx/rx_pause!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (mac_ctrl_drv->mac_छोड़ोfrm_cfg)
		mac_ctrl_drv->mac_छोड़ोfrm_cfg(mac_ctrl_drv, rx_en, tx_en);

	वापस 0;
पूर्ण

/**
 * hns_mac_init_ex - mac init
 * @mac_cb: mac control block
 * वापस 0 - success , negative --fail
 */
अटल पूर्णांक hns_mac_init_ex(काष्ठा hns_mac_cb *mac_cb)
अणु
	पूर्णांक ret;
	काष्ठा mac_params param;
	काष्ठा mac_driver *drv;

	hns_dsaf_fix_mac_mode(mac_cb);

	स_रखो(&param, 0, माप(काष्ठा mac_params));
	hns_mac_param_get(&param, mac_cb);

	अगर (MAC_SPEED_FROM_MODE(param.mac_mode) < MAC_SPEED_10000)
		drv = (काष्ठा mac_driver *)hns_gmac_config(mac_cb, &param);
	अन्यथा
		drv = (काष्ठा mac_driver *)hns_xgmac_config(mac_cb, &param);

	अगर (!drv)
		वापस -ENOMEM;

	mac_cb->priv.mac = (व्योम *)drv;
	hns_mac_reset(mac_cb);

	hns_mac_adjust_link(mac_cb, mac_cb->speed, !mac_cb->half_duplex);

	ret = hns_mac_port_config_bc_en(mac_cb, mac_cb->mac_id, 0, true);
	अगर (ret)
		जाओ मुक्त_mac_drv;

	वापस 0;

मुक्त_mac_drv:
	drv->mac_मुक्त(mac_cb->priv.mac);
	mac_cb->priv.mac = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक
hns_mac_phy_parse_addr(काष्ठा device *dev, काष्ठा fwnode_handle *fwnode)
अणु
	u32 addr;
	पूर्णांक ret;

	ret = fwnode_property_पढ़ो_u32(fwnode, "phy-addr", &addr);
	अगर (ret) अणु
		dev_err(dev, "has invalid PHY address ret:%d\n", ret);
		वापस ret;
	पूर्ण

	अगर (addr >= PHY_MAX_ADDR) अणु
		dev_err(dev, "PHY address %i is too large\n", addr);
		वापस -EINVAL;
	पूर्ण

	वापस addr;
पूर्ण

अटल पूर्णांक
hns_mac_रेजिस्टर_phydev(काष्ठा mii_bus *mdio, काष्ठा hns_mac_cb *mac_cb,
			u32 addr)
अणु
	काष्ठा phy_device *phy;
	स्थिर अक्षर *phy_type;
	bool is_c45;
	पूर्णांक rc;

	rc = fwnode_property_पढ़ो_string(mac_cb->fw_port,
					 "phy-mode", &phy_type);
	अगर (rc < 0)
		वापस rc;

	अगर (!म_भेद(phy_type, phy_modes(PHY_INTERFACE_MODE_XGMII)))
		is_c45 = true;
	अन्यथा अगर (!म_भेद(phy_type, phy_modes(PHY_INTERFACE_MODE_SGMII)))
		is_c45 = false;
	अन्यथा
		वापस -ENODATA;

	phy = get_phy_device(mdio, addr, is_c45);
	अगर (!phy || IS_ERR(phy))
		वापस -EIO;

	phy->irq = mdio->irq[addr];

	/* All data is now stored in the phy काष्ठा;
	 * रेजिस्टर it
	 */
	rc = phy_device_रेजिस्टर(phy);
	अगर (rc) अणु
		phy_device_मुक्त(phy);
		dev_err(&mdio->dev, "registered phy fail at address %i\n",
			addr);
		वापस -ENODEV;
	पूर्ण

	mac_cb->phy_dev = phy;

	dev_dbg(&mdio->dev, "registered phy at address %i\n", addr);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_mac_रेजिस्टर_phy(काष्ठा hns_mac_cb *mac_cb)
अणु
	काष्ठा fwnode_reference_args args;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mii_bus *mii_bus;
	पूर्णांक rc;
	पूर्णांक addr;

	/* Loop over the child nodes and रेजिस्टर a phy_device क्रम each one */
	अगर (!to_acpi_device_node(mac_cb->fw_port))
		वापस -ENODEV;

	rc = acpi_node_get_property_reference(
			mac_cb->fw_port, "mdio-node", 0, &args);
	अगर (rc)
		वापस rc;
	अगर (!is_acpi_device_node(args.fwnode))
		वापस -EINVAL;

	addr = hns_mac_phy_parse_addr(mac_cb->dev, mac_cb->fw_port);
	अगर (addr < 0)
		वापस addr;

	/* dev address in adev */
	pdev = hns_dsaf_find_platक्रमm_device(args.fwnode);
	अगर (!pdev) अणु
		dev_err(mac_cb->dev, "mac%d mdio pdev is NULL\n",
			mac_cb->mac_id);
		वापस  -EINVAL;
	पूर्ण

	mii_bus = platक्रमm_get_drvdata(pdev);
	अगर (!mii_bus) अणु
		dev_err(mac_cb->dev,
			"mac%d mdio is NULL, dsaf will probe again later\n",
			mac_cb->mac_id);
		वापस -EPROBE_DEFER;
	पूर्ण

	rc = hns_mac_रेजिस्टर_phydev(mii_bus, mac_cb, addr);
	अगर (!rc)
		dev_dbg(mac_cb->dev, "mac%d register phy addr:%d\n",
			mac_cb->mac_id, addr);

	वापस rc;
पूर्ण

अटल व्योम hns_mac_हटाओ_phydev(काष्ठा hns_mac_cb *mac_cb)
अणु
	अगर (!to_acpi_device_node(mac_cb->fw_port) || !mac_cb->phy_dev)
		वापस;

	phy_device_हटाओ(mac_cb->phy_dev);
	phy_device_मुक्त(mac_cb->phy_dev);

	mac_cb->phy_dev = शून्य;
पूर्ण

#घोषणा MAC_MEDIA_TYPE_MAX_LEN		16

अटल स्थिर काष्ठा अणु
	क्रमागत hnae_media_type value;
	स्थिर अक्षर *name;
पूर्ण media_type_defs[] = अणु
	अणुHNAE_MEDIA_TYPE_UNKNOWN,	"unknown" पूर्ण,
	अणुHNAE_MEDIA_TYPE_FIBER,		"fiber" पूर्ण,
	अणुHNAE_MEDIA_TYPE_COPPER,	"copper" पूर्ण,
	अणुHNAE_MEDIA_TYPE_BACKPLANE,	"backplane" पूर्ण,
पूर्ण;

/**
 *hns_mac_get_info  - get mac inक्रमmation from device node
 *@mac_cb: mac device
 * वापस: 0 --success, negative --fail
 */
अटल पूर्णांक hns_mac_get_info(काष्ठा hns_mac_cb *mac_cb)
अणु
	काष्ठा device_node *np;
	काष्ठा regmap *syscon;
	काष्ठा of_phandle_args cpld_args;
	स्थिर अक्षर *media_type;
	u32 i;
	u32 ret;

	mac_cb->link = false;
	mac_cb->half_duplex = false;
	mac_cb->media_type = HNAE_MEDIA_TYPE_UNKNOWN;
	mac_cb->speed = mac_phy_to_speed[mac_cb->phy_अगर];
	mac_cb->max_speed = mac_cb->speed;

	अगर (mac_cb->phy_अगर == PHY_INTERFACE_MODE_SGMII) अणु
		mac_cb->अगर_support = MAC_GMAC_SUPPORTED;
		mac_cb->अगर_support |= SUPPORTED_1000baseT_Full;
	पूर्ण अन्यथा अगर (mac_cb->phy_अगर == PHY_INTERFACE_MODE_XGMII) अणु
		mac_cb->अगर_support = SUPPORTED_10000baseR_FEC;
		mac_cb->अगर_support |= SUPPORTED_10000baseKR_Full;
	पूर्ण

	mac_cb->max_frm = MAC_DEFAULT_MTU;
	mac_cb->tx_छोड़ो_frm_समय = MAC_DEFAULT_PAUSE_TIME;
	mac_cb->port_rst_off = mac_cb->mac_id;
	mac_cb->port_mode_off = 0;

	/* अगर the dsaf node करोesn't contain a port subnode, get phy-handle
	 * from dsaf node
	 */
	अगर (!mac_cb->fw_port) अणु
		np = of_parse_phandle(mac_cb->dev->of_node, "phy-handle",
				      mac_cb->mac_id);
		mac_cb->phy_dev = of_phy_find_device(np);
		अगर (mac_cb->phy_dev) अणु
			/* refcount is held by of_phy_find_device()
			 * अगर the phy_dev is found
			 */
			put_device(&mac_cb->phy_dev->mdio.dev);

			dev_dbg(mac_cb->dev, "mac%d phy_node: %pOFn\n",
				mac_cb->mac_id, np);
		पूर्ण
		of_node_put(np);

		वापस 0;
	पूर्ण

	अगर (is_of_node(mac_cb->fw_port)) अणु
		/* parse property from port subnode in dsaf */
		np = of_parse_phandle(to_of_node(mac_cb->fw_port),
				      "phy-handle", 0);
		mac_cb->phy_dev = of_phy_find_device(np);
		अगर (mac_cb->phy_dev) अणु
			/* refcount is held by of_phy_find_device()
			 * अगर the phy_dev is found
			 */
			put_device(&mac_cb->phy_dev->mdio.dev);
			dev_dbg(mac_cb->dev, "mac%d phy_node: %pOFn\n",
				mac_cb->mac_id, np);
		पूर्ण
		of_node_put(np);

		np = of_parse_phandle(to_of_node(mac_cb->fw_port),
				      "serdes-syscon", 0);
		syscon = syscon_node_to_regmap(np);
		of_node_put(np);
		अगर (IS_ERR_OR_शून्य(syscon)) अणु
			dev_err(mac_cb->dev, "serdes-syscon is needed!\n");
			वापस -EINVAL;
		पूर्ण
		mac_cb->serdes_ctrl = syscon;

		ret = fwnode_property_पढ़ो_u32(mac_cb->fw_port,
					       "port-rst-offset",
					       &mac_cb->port_rst_off);
		अगर (ret) अणु
			dev_dbg(mac_cb->dev,
				"mac%d port-rst-offset not found, use default value.\n",
				mac_cb->mac_id);
		पूर्ण

		ret = fwnode_property_पढ़ो_u32(mac_cb->fw_port,
					       "port-mode-offset",
					       &mac_cb->port_mode_off);
		अगर (ret) अणु
			dev_dbg(mac_cb->dev,
				"mac%d port-mode-offset not found, use default value.\n",
				mac_cb->mac_id);
		पूर्ण

		ret = of_parse_phandle_with_fixed_args(
			to_of_node(mac_cb->fw_port), "cpld-syscon", 1, 0,
			&cpld_args);
		अगर (ret) अणु
			dev_dbg(mac_cb->dev, "mac%d no cpld-syscon found.\n",
				mac_cb->mac_id);
			mac_cb->cpld_ctrl = शून्य;
		पूर्ण अन्यथा अणु
			syscon = syscon_node_to_regmap(cpld_args.np);
			अगर (IS_ERR_OR_शून्य(syscon)) अणु
				dev_dbg(mac_cb->dev, "no cpld-syscon found!\n");
				mac_cb->cpld_ctrl = शून्य;
			पूर्ण अन्यथा अणु
				mac_cb->cpld_ctrl = syscon;
				mac_cb->cpld_ctrl_reg = cpld_args.args[0];
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (is_acpi_node(mac_cb->fw_port)) अणु
		ret = hns_mac_रेजिस्टर_phy(mac_cb);
		/*
		 * Mac can work well अगर there is phy or not.If the port करोn't
		 * connect with phy, the वापस value will be ignored. Only
		 * when there is phy but can't find mdio bus, the वापस value
		 * will be handled.
		 */
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
	पूर्ण अन्यथा अणु
		dev_err(mac_cb->dev, "mac%d cannot find phy node\n",
			mac_cb->mac_id);
	पूर्ण

	अगर (!fwnode_property_पढ़ो_string(mac_cb->fw_port, "media-type",
					 &media_type)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(media_type_defs); i++) अणु
			अगर (!म_भेदन(media_type_defs[i].name, media_type,
				     MAC_MEDIA_TYPE_MAX_LEN)) अणु
				mac_cb->media_type = media_type_defs[i].value;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (fwnode_property_पढ़ो_u8_array(mac_cb->fw_port, "mc-mac-mask",
					  mac_cb->mc_mask, ETH_ALEN)) अणु
		dev_warn(mac_cb->dev,
			 "no mc-mac-mask property, set to default value.\n");
		eth_broadcast_addr(mac_cb->mc_mask);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hns_mac_get_mode - get mac mode
 * @phy_अगर: phy पूर्णांकerface
 * वापस 0 - gmac, 1 - xgmac , negative --fail
 */
अटल पूर्णांक hns_mac_get_mode(phy_पूर्णांकerface_t phy_अगर)
अणु
	चयन (phy_अगर) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
		वापस MAC_GMAC_IDX;
	हाल PHY_INTERFACE_MODE_XGMII:
		वापस MAC_XGMAC_IDX;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u8 __iomem *
hns_mac_get_vaddr(काष्ठा dsaf_device *dsaf_dev,
		  काष्ठा hns_mac_cb *mac_cb, u32 mac_mode_idx)
अणु
	u8 __iomem *base = dsaf_dev->io_base;
	पूर्णांक mac_id = mac_cb->mac_id;

	अगर (mac_cb->mac_type == HNAE_PORT_SERVICE)
		वापस base + 0x40000 + mac_id * 0x4000 -
				mac_mode_idx * 0x20000;
	अन्यथा
		वापस dsaf_dev->ppe_base + 0x1000;
पूर्ण

/**
 * hns_mac_get_cfg - get mac cfg from dtb or acpi table
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @mac_cb: mac control block
 * वापस 0 - success , negative --fail
 */
अटल पूर्णांक
hns_mac_get_cfg(काष्ठा dsaf_device *dsaf_dev, काष्ठा hns_mac_cb *mac_cb)
अणु
	पूर्णांक ret;
	u32 mac_mode_idx;

	mac_cb->dsaf_dev = dsaf_dev;
	mac_cb->dev = dsaf_dev->dev;

	mac_cb->sys_ctl_vaddr =	dsaf_dev->sc_base;
	mac_cb->serdes_vaddr = dsaf_dev->sds_base;

	mac_cb->sfp_prsnt = 0;
	mac_cb->txpkt_क्रम_led = 0;
	mac_cb->rxpkt_क्रम_led = 0;

	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev))
		mac_cb->mac_type = HNAE_PORT_SERVICE;
	अन्यथा
		mac_cb->mac_type = HNAE_PORT_DEBUG;

	mac_cb->phy_अगर = dsaf_dev->misc_op->get_phy_अगर(mac_cb);

	ret = hns_mac_get_mode(mac_cb->phy_अगर);
	अगर (ret < 0) अणु
		dev_err(dsaf_dev->dev,
			"hns_mac_get_mode failed, mac%d ret = %#x!\n",
			mac_cb->mac_id, ret);
		वापस ret;
	पूर्ण
	mac_mode_idx = (u32)ret;

	ret  = hns_mac_get_info(mac_cb);
	अगर (ret)
		वापस ret;

	mac_cb->dsaf_dev->misc_op->cpld_reset_led(mac_cb);
	mac_cb->vaddr = hns_mac_get_vaddr(dsaf_dev, mac_cb, mac_mode_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_mac_get_max_port_num(काष्ठा dsaf_device *dsaf_dev)
अणु
	अगर (HNS_DSAF_IS_DEBUG(dsaf_dev))
		वापस 1;
	अन्यथा
		वापस  DSAF_MAX_PORT_NUM;
पूर्ण

व्योम hns_mac_enable(काष्ठा hns_mac_cb *mac_cb, क्रमागत mac_commom_mode mode)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	mac_ctrl_drv->mac_enable(mac_cb->priv.mac, mode);
पूर्ण

व्योम hns_mac_disable(काष्ठा hns_mac_cb *mac_cb, क्रमागत mac_commom_mode mode)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	mac_ctrl_drv->mac_disable(mac_cb->priv.mac, mode);
पूर्ण

/**
 * hns_mac_init - init mac
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * वापस 0 - success , negative --fail
 */
पूर्णांक hns_mac_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	bool found = false;
	पूर्णांक ret;
	u32 port_id;
	पूर्णांक max_port_num = hns_mac_get_max_port_num(dsaf_dev);
	काष्ठा hns_mac_cb *mac_cb;
	काष्ठा fwnode_handle *child;

	device_क्रम_each_child_node(dsaf_dev->dev, child) अणु
		ret = fwnode_property_पढ़ो_u32(child, "reg", &port_id);
		अगर (ret) अणु
			dev_err(dsaf_dev->dev,
				"get reg fail, ret=%d!\n", ret);
			वापस ret;
		पूर्ण
		अगर (port_id >= max_port_num) अणु
			dev_err(dsaf_dev->dev,
				"reg(%u) out of range!\n", port_id);
			वापस -EINVAL;
		पूर्ण
		mac_cb = devm_kzalloc(dsaf_dev->dev, माप(*mac_cb),
				      GFP_KERNEL);
		अगर (!mac_cb)
			वापस -ENOMEM;
		mac_cb->fw_port = child;
		mac_cb->mac_id = (u8)port_id;
		dsaf_dev->mac_cb[port_id] = mac_cb;
		found = true;
	पूर्ण

	/* अगर करोn't get any port subnode from dsaf node
	 * will init all port then, this is compatible with the old dts
	 */
	अगर (!found) अणु
		क्रम (port_id = 0; port_id < max_port_num; port_id++) अणु
			mac_cb = devm_kzalloc(dsaf_dev->dev, माप(*mac_cb),
					      GFP_KERNEL);
			अगर (!mac_cb)
				वापस -ENOMEM;

			mac_cb->mac_id = port_id;
			dsaf_dev->mac_cb[port_id] = mac_cb;
		पूर्ण
	पूर्ण

	/* init mac_cb क्रम all port */
	क्रम (port_id = 0; port_id < max_port_num; port_id++) अणु
		mac_cb = dsaf_dev->mac_cb[port_id];
		अगर (!mac_cb)
			जारी;

		ret = hns_mac_get_cfg(dsaf_dev, mac_cb);
		अगर (ret)
			वापस ret;

		ret = hns_mac_init_ex(mac_cb);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम hns_mac_uninit(काष्ठा dsaf_device *dsaf_dev)
अणु
	पूर्णांक i;
	पूर्णांक max_port_num = hns_mac_get_max_port_num(dsaf_dev);

	क्रम (i = 0; i < max_port_num; i++) अणु
		अगर (!dsaf_dev->mac_cb[i])
			जारी;

		dsaf_dev->misc_op->cpld_reset_led(dsaf_dev->mac_cb[i]);
		hns_mac_हटाओ_phydev(dsaf_dev->mac_cb[i]);
		dsaf_dev->mac_cb[i] = शून्य;
	पूर्ण
पूर्ण

पूर्णांक hns_mac_config_mac_loopback(काष्ठा hns_mac_cb *mac_cb,
				क्रमागत hnae_loop loop, पूर्णांक en)
अणु
	पूर्णांक ret;
	काष्ठा mac_driver *drv = hns_mac_get_drv(mac_cb);

	अगर (drv->config_loopback)
		ret = drv->config_loopback(drv, loop, en);
	अन्यथा
		ret = -ENOTSUPP;

	वापस ret;
पूर्ण

व्योम hns_mac_update_stats(काष्ठा hns_mac_cb *mac_cb)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	mac_ctrl_drv->update_stats(mac_ctrl_drv);
पूर्ण

व्योम hns_mac_get_stats(काष्ठा hns_mac_cb *mac_cb, u64 *data)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	mac_ctrl_drv->get_ethtool_stats(mac_ctrl_drv, data);
पूर्ण

व्योम hns_mac_get_strings(काष्ठा hns_mac_cb *mac_cb,
			 पूर्णांक stringset, u8 *data)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	mac_ctrl_drv->get_strings(stringset, data);
पूर्ण

पूर्णांक hns_mac_get_sset_count(काष्ठा hns_mac_cb *mac_cb, पूर्णांक stringset)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	वापस mac_ctrl_drv->get_sset_count(stringset);
पूर्ण

व्योम hns_mac_set_promisc(काष्ठा hns_mac_cb *mac_cb, u8 en)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	hns_dsaf_set_promisc_tcam(mac_cb->dsaf_dev, mac_cb->mac_id, !!en);

	अगर (mac_ctrl_drv->set_promiscuous)
		mac_ctrl_drv->set_promiscuous(mac_ctrl_drv, en);
पूर्ण

पूर्णांक hns_mac_get_regs_count(काष्ठा hns_mac_cb *mac_cb)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	वापस mac_ctrl_drv->get_regs_count();
पूर्ण

व्योम hns_mac_get_regs(काष्ठा hns_mac_cb *mac_cb, व्योम *data)
अणु
	काष्ठा mac_driver *mac_ctrl_drv = hns_mac_get_drv(mac_cb);

	mac_ctrl_drv->get_regs(mac_ctrl_drv, data);
पूर्ण

व्योम hns_set_led_opt(काष्ठा hns_mac_cb *mac_cb)
अणु
	पूर्णांक nic_data;
	पूर्णांक txpkts, rxpkts;

	txpkts = mac_cb->txpkt_क्रम_led - mac_cb->hw_stats.tx_good_pkts;
	rxpkts = mac_cb->rxpkt_क्रम_led - mac_cb->hw_stats.rx_good_pkts;
	अगर (txpkts || rxpkts)
		nic_data = 1;
	अन्यथा
		nic_data = 0;
	mac_cb->txpkt_क्रम_led = mac_cb->hw_stats.tx_good_pkts;
	mac_cb->rxpkt_क्रम_led = mac_cb->hw_stats.rx_good_pkts;
	mac_cb->dsaf_dev->misc_op->cpld_set_led(mac_cb, (पूर्णांक)mac_cb->link,
			 mac_cb->speed, nic_data);
पूर्ण

पूर्णांक hns_cpld_led_set_id(काष्ठा hns_mac_cb *mac_cb,
			क्रमागत hnae_led_state status)
अणु
	अगर (!mac_cb)
		वापस 0;

	वापस mac_cb->dsaf_dev->misc_op->cpld_set_led_id(mac_cb, status);
पूर्ण
