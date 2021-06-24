<शैली गुरु>
/******************************************************************************
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice.  This file is not
 * a complete program and may only be used when the entire operating
 * प्रणाली is licensed under the GPL.
 * See the file COPYING in this distribution क्रम more inक्रमmation.
 *
 * vxge-ethtool.c: Driver क्रम Exar Corp's X3100 Series 10GbE PCIe I/O
 *                 Virtualized Server Adapter.
 * Copyright(c) 2002-2010 Exar Corp.
 ******************************************************************************/
#समावेश <linux/ethtool.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>

#समावेश "vxge-ethtool.h"

अटल स्थिर अक्षर ethtool_driver_stats_keys[][ETH_GSTRING_LEN] = अणु
	अणु"\n DRIVER STATISTICS"पूर्ण,
	अणु"vpaths_opened"पूर्ण,
	अणु"vpath_open_fail_cnt"पूर्ण,
	अणु"link_up_cnt"पूर्ण,
	अणु"link_down_cnt"पूर्ण,
	अणु"tx_frms"पूर्ण,
	अणु"tx_errors"पूर्ण,
	अणु"tx_bytes"पूर्ण,
	अणु"txd_not_free"पूर्ण,
	अणु"txd_out_of_desc"पूर्ण,
	अणु"rx_frms"पूर्ण,
	अणु"rx_errors"पूर्ण,
	अणु"rx_bytes"पूर्ण,
	अणु"rx_mcast"पूर्ण,
	अणु"pci_map_fail_cnt"पूर्ण,
	अणु"skb_alloc_fail_cnt"पूर्ण
पूर्ण;

/**
 * vxge_ethtool_set_link_ksettings - Sets dअगरferent link parameters.
 * @dev: device poपूर्णांकer.
 * @cmd: poपूर्णांकer to the काष्ठाure with parameters given by ethtool to set
 * link inक्रमmation.
 *
 * The function sets dअगरferent link parameters provided by the user onto
 * the NIC.
 * Return value:
 * 0 on success.
 */
अटल पूर्णांक
vxge_ethtool_set_link_ksettings(काष्ठा net_device *dev,
				स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	/* We currently only support 10Gb/FULL */
	अगर ((cmd->base.स्वतःneg == AUTONEG_ENABLE) ||
	    (cmd->base.speed != SPEED_10000) ||
	    (cmd->base.duplex != DUPLEX_FULL))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * vxge_ethtool_get_link_ksettings - Return link specअगरic inक्रमmation.
 * @dev: device poपूर्णांकer.
 * @cmd: poपूर्णांकer to the काष्ठाure with parameters given by ethtool
 * to वापस link inक्रमmation.
 *
 * Returns link specअगरic inक्रमmation like speed, duplex etc.. to ethtool.
 * Return value :
 * वापस 0 on success.
 */
अटल पूर्णांक vxge_ethtool_get_link_ksettings(काष्ठा net_device *dev,
					   काष्ठा ethtool_link_ksettings *cmd)
अणु
	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);

	ethtool_link_ksettings_zero_link_mode(cmd, advertising);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, 10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, FIBRE);

	cmd->base.port = PORT_FIBRE;

	अगर (netअगर_carrier_ok(dev)) अणु
		cmd->base.speed = SPEED_10000;
		cmd->base.duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	cmd->base.स्वतःneg = AUTONEG_DISABLE;
	वापस 0;
पूर्ण

/**
 * vxge_ethtool_gdrvinfo - Returns driver specअगरic inक्रमmation.
 * @dev: device poपूर्णांकer.
 * @info: poपूर्णांकer to the काष्ठाure with parameters given by ethtool to
 * वापस driver inक्रमmation.
 *
 * Returns driver specefic inक्रमmation like name, version etc.. to ethtool.
 */
अटल व्योम vxge_ethtool_gdrvinfo(काष्ठा net_device *dev,
				  काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	strlcpy(info->driver, VXGE_DRIVER_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->fw_version, vdev->fw_version, माप(info->fw_version));
	strlcpy(info->bus_info, pci_name(vdev->pdev), माप(info->bus_info));
पूर्ण

/**
 * vxge_ethtool_gregs - dumps the entire space of Titan पूर्णांकo the buffer.
 * @dev: device poपूर्णांकer.
 * @regs: poपूर्णांकer to the काष्ठाure with parameters given by ethtool क्रम
 * dumping the रेजिस्टरs.
 * @space: The input argument पूर्णांकo which all the रेजिस्टरs are dumped.
 *
 * Dumps the vpath रेजिस्टर space of Titan NIC पूर्णांकo the user given
 * buffer area.
 */
अटल व्योम vxge_ethtool_gregs(काष्ठा net_device *dev,
			       काष्ठा ethtool_regs *regs, व्योम *space)
अणु
	पूर्णांक index, offset;
	क्रमागत vxge_hw_status status;
	u64 reg;
	u64 *reg_space = (u64 *)space;
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	काष्ठा __vxge_hw_device *hldev = vdev->devh;

	regs->len = माप(काष्ठा vxge_hw_vpath_reg) * vdev->no_of_vpath;
	regs->version = vdev->pdev->subप्रणाली_device;
	क्रम (index = 0; index < vdev->no_of_vpath; index++) अणु
		क्रम (offset = 0; offset < माप(काष्ठा vxge_hw_vpath_reg);
				offset += 8) अणु
			status = vxge_hw_mgmt_reg_पढ़ो(hldev,
					vxge_hw_mgmt_reg_type_vpath,
					vdev->vpaths[index].device_id,
					offset, &reg);
			अगर (status != VXGE_HW_OK) अणु
				vxge_debug_init(VXGE_ERR,
					"%s:%d Getting reg dump Failed",
						__func__, __LINE__);
				वापस;
			पूर्ण
			*reg_space++ = reg;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vxge_ethtool_idnic - To physically identअगरy the nic on the प्रणाली.
 * @dev : device poपूर्णांकer.
 * @state : requested LED state
 *
 * Used to physically identअगरy the NIC on the प्रणाली.
 * 0 on success
 */
अटल पूर्णांक vxge_ethtool_idnic(काष्ठा net_device *dev,
			      क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	काष्ठा __vxge_hw_device *hldev = vdev->devh;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		vxge_hw_device_flick_link_led(hldev, VXGE_FLICKER_ON);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		vxge_hw_device_flick_link_led(hldev, VXGE_FLICKER_OFF);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vxge_ethtool_getछोड़ो_data - Pause frame frame generation and reception.
 * @dev : device poपूर्णांकer.
 * @ep : poपूर्णांकer to the काष्ठाure with छोड़ो parameters given by ethtool.
 * Description:
 * Returns the Pause frame generation and reception capability of the NIC.
 * Return value:
 *  व्योम
 */
अटल व्योम vxge_ethtool_getछोड़ो_data(काष्ठा net_device *dev,
				       काष्ठा ethtool_छोड़ोparam *ep)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	काष्ठा __vxge_hw_device *hldev = vdev->devh;

	vxge_hw_device_getछोड़ो_data(hldev, 0, &ep->tx_छोड़ो, &ep->rx_छोड़ो);
पूर्ण

/**
 * vxge_ethtool_setछोड़ो_data -  set/reset छोड़ो frame generation.
 * @dev : device poपूर्णांकer.
 * @ep : poपूर्णांकer to the काष्ठाure with छोड़ो parameters given by ethtool.
 * Description:
 * It can be used to set or reset Pause frame generation or reception
 * support of the NIC.
 * Return value:
 * पूर्णांक, वापसs 0 on Success
 */
अटल पूर्णांक vxge_ethtool_setछोड़ो_data(काष्ठा net_device *dev,
				      काष्ठा ethtool_छोड़ोparam *ep)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	काष्ठा __vxge_hw_device *hldev = vdev->devh;

	vxge_hw_device_setछोड़ो_data(hldev, 0, ep->tx_छोड़ो, ep->rx_छोड़ो);

	vdev->config.tx_छोड़ो_enable = ep->tx_छोड़ो;
	vdev->config.rx_छोड़ो_enable = ep->rx_छोड़ो;

	वापस 0;
पूर्ण

अटल व्योम vxge_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *estats, u64 *पंचांगp_stats)
अणु
	पूर्णांक j, k;
	क्रमागत vxge_hw_status status;
	क्रमागत vxge_hw_status swstatus;
	काष्ठा vxge_vpath *vpath = शून्य;
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	काष्ठा __vxge_hw_device *hldev = vdev->devh;
	काष्ठा vxge_hw_xmac_stats *xmac_stats;
	काष्ठा vxge_hw_device_stats_sw_info *sw_stats;
	काष्ठा vxge_hw_device_stats_hw_info *hw_stats;

	u64 *ptr = पंचांगp_stats;

	स_रखो(पंचांगp_stats, 0,
		vxge_ethtool_get_sset_count(dev, ETH_SS_STATS) * माप(u64));

	xmac_stats = kzalloc(माप(काष्ठा vxge_hw_xmac_stats), GFP_KERNEL);
	अगर (xmac_stats == शून्य) अणु
		vxge_debug_init(VXGE_ERR,
			"%s : %d Memory Allocation failed for xmac_stats",
				 __func__, __LINE__);
		वापस;
	पूर्ण

	sw_stats = kzalloc(माप(काष्ठा vxge_hw_device_stats_sw_info),
				GFP_KERNEL);
	अगर (sw_stats == शून्य) अणु
		kमुक्त(xmac_stats);
		vxge_debug_init(VXGE_ERR,
			"%s : %d Memory Allocation failed for sw_stats",
			__func__, __LINE__);
		वापस;
	पूर्ण

	hw_stats = kzalloc(माप(काष्ठा vxge_hw_device_stats_hw_info),
				GFP_KERNEL);
	अगर (hw_stats == शून्य) अणु
		kमुक्त(xmac_stats);
		kमुक्त(sw_stats);
		vxge_debug_init(VXGE_ERR,
			"%s : %d Memory Allocation failed for hw_stats",
			__func__, __LINE__);
		वापस;
	पूर्ण

	*ptr++ = 0;
	status = vxge_hw_device_xmac_stats_get(hldev, xmac_stats);
	अगर (status != VXGE_HW_OK) अणु
		अगर (status != VXGE_HW_ERR_PRIVILEGED_OPERATION) अणु
			vxge_debug_init(VXGE_ERR,
				"%s : %d Failure in getting xmac stats",
				__func__, __LINE__);
		पूर्ण
	पूर्ण
	swstatus = vxge_hw_driver_stats_get(hldev, sw_stats);
	अगर (swstatus != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"%s : %d Failure in getting sw stats",
			__func__, __LINE__);
	पूर्ण

	status = vxge_hw_device_stats_get(hldev, hw_stats);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR,
			"%s : %d hw_stats_get error", __func__, __LINE__);
	पूर्ण

	क्रम (k = 0; k < vdev->no_of_vpath; k++) अणु
		काष्ठा vxge_hw_vpath_stats_hw_info *vpath_info;

		vpath = &vdev->vpaths[k];
		j = vpath->device_id;
		vpath_info = hw_stats->vpath_info[j];
		अगर (!vpath_info) अणु
			स_रखो(ptr, 0, (VXGE_HW_VPATH_TX_STATS_LEN +
				VXGE_HW_VPATH_RX_STATS_LEN) * माप(u64));
			ptr += (VXGE_HW_VPATH_TX_STATS_LEN +
				VXGE_HW_VPATH_RX_STATS_LEN);
			जारी;
		पूर्ण

		*ptr++ = vpath_info->tx_stats.tx_ttl_eth_frms;
		*ptr++ = vpath_info->tx_stats.tx_ttl_eth_octets;
		*ptr++ = vpath_info->tx_stats.tx_data_octets;
		*ptr++ = vpath_info->tx_stats.tx_mcast_frms;
		*ptr++ = vpath_info->tx_stats.tx_bcast_frms;
		*ptr++ = vpath_info->tx_stats.tx_ucast_frms;
		*ptr++ = vpath_info->tx_stats.tx_tagged_frms;
		*ptr++ = vpath_info->tx_stats.tx_vld_ip;
		*ptr++ = vpath_info->tx_stats.tx_vld_ip_octets;
		*ptr++ = vpath_info->tx_stats.tx_icmp;
		*ptr++ = vpath_info->tx_stats.tx_tcp;
		*ptr++ = vpath_info->tx_stats.tx_rst_tcp;
		*ptr++ = vpath_info->tx_stats.tx_udp;
		*ptr++ = vpath_info->tx_stats.tx_unknown_protocol;
		*ptr++ = vpath_info->tx_stats.tx_lost_ip;
		*ptr++ = vpath_info->tx_stats.tx_parse_error;
		*ptr++ = vpath_info->tx_stats.tx_tcp_offload;
		*ptr++ = vpath_info->tx_stats.tx_retx_tcp_offload;
		*ptr++ = vpath_info->tx_stats.tx_lost_ip_offload;
		*ptr++ = vpath_info->rx_stats.rx_ttl_eth_frms;
		*ptr++ = vpath_info->rx_stats.rx_vld_frms;
		*ptr++ = vpath_info->rx_stats.rx_offload_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_eth_octets;
		*ptr++ = vpath_info->rx_stats.rx_data_octets;
		*ptr++ = vpath_info->rx_stats.rx_offload_octets;
		*ptr++ = vpath_info->rx_stats.rx_vld_mcast_frms;
		*ptr++ = vpath_info->rx_stats.rx_vld_bcast_frms;
		*ptr++ = vpath_info->rx_stats.rx_accepted_ucast_frms;
		*ptr++ = vpath_info->rx_stats.rx_accepted_nucast_frms;
		*ptr++ = vpath_info->rx_stats.rx_tagged_frms;
		*ptr++ = vpath_info->rx_stats.rx_दीर्घ_frms;
		*ptr++ = vpath_info->rx_stats.rx_usized_frms;
		*ptr++ = vpath_info->rx_stats.rx_osized_frms;
		*ptr++ = vpath_info->rx_stats.rx_frag_frms;
		*ptr++ = vpath_info->rx_stats.rx_jabber_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_64_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_65_127_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_128_255_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_256_511_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_512_1023_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_1024_1518_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_1519_4095_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_4096_8191_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_8192_max_frms;
		*ptr++ = vpath_info->rx_stats.rx_ttl_gt_max_frms;
		*ptr++ = vpath_info->rx_stats.rx_ip;
		*ptr++ = vpath_info->rx_stats.rx_accepted_ip;
		*ptr++ = vpath_info->rx_stats.rx_ip_octets;
		*ptr++ = vpath_info->rx_stats.rx_err_ip;
		*ptr++ = vpath_info->rx_stats.rx_icmp;
		*ptr++ = vpath_info->rx_stats.rx_tcp;
		*ptr++ = vpath_info->rx_stats.rx_udp;
		*ptr++ = vpath_info->rx_stats.rx_err_tcp;
		*ptr++ = vpath_info->rx_stats.rx_lost_frms;
		*ptr++ = vpath_info->rx_stats.rx_lost_ip;
		*ptr++ = vpath_info->rx_stats.rx_lost_ip_offload;
		*ptr++ = vpath_info->rx_stats.rx_various_discard;
		*ptr++ = vpath_info->rx_stats.rx_sleep_discard;
		*ptr++ = vpath_info->rx_stats.rx_red_discard;
		*ptr++ = vpath_info->rx_stats.rx_queue_full_discard;
		*ptr++ = vpath_info->rx_stats.rx_mpa_ok_frms;
	पूर्ण
	*ptr++ = 0;
	क्रम (k = 0; k < vdev->max_config_port; k++) अणु
		*ptr++ = xmac_stats->aggr_stats[k].tx_frms;
		*ptr++ = xmac_stats->aggr_stats[k].tx_data_octets;
		*ptr++ = xmac_stats->aggr_stats[k].tx_mcast_frms;
		*ptr++ = xmac_stats->aggr_stats[k].tx_bcast_frms;
		*ptr++ = xmac_stats->aggr_stats[k].tx_discarded_frms;
		*ptr++ = xmac_stats->aggr_stats[k].tx_errored_frms;
		*ptr++ = xmac_stats->aggr_stats[k].rx_frms;
		*ptr++ = xmac_stats->aggr_stats[k].rx_data_octets;
		*ptr++ = xmac_stats->aggr_stats[k].rx_mcast_frms;
		*ptr++ = xmac_stats->aggr_stats[k].rx_bcast_frms;
		*ptr++ = xmac_stats->aggr_stats[k].rx_discarded_frms;
		*ptr++ = xmac_stats->aggr_stats[k].rx_errored_frms;
		*ptr++ = xmac_stats->aggr_stats[k].rx_unknown_slow_proto_frms;
	पूर्ण
	*ptr++ = 0;
	क्रम (k = 0; k < vdev->max_config_port; k++) अणु
		*ptr++ = xmac_stats->port_stats[k].tx_ttl_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_ttl_octets;
		*ptr++ = xmac_stats->port_stats[k].tx_data_octets;
		*ptr++ = xmac_stats->port_stats[k].tx_mcast_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_bcast_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_ucast_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_tagged_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_vld_ip;
		*ptr++ = xmac_stats->port_stats[k].tx_vld_ip_octets;
		*ptr++ = xmac_stats->port_stats[k].tx_icmp;
		*ptr++ = xmac_stats->port_stats[k].tx_tcp;
		*ptr++ = xmac_stats->port_stats[k].tx_rst_tcp;
		*ptr++ = xmac_stats->port_stats[k].tx_udp;
		*ptr++ = xmac_stats->port_stats[k].tx_parse_error;
		*ptr++ = xmac_stats->port_stats[k].tx_unknown_protocol;
		*ptr++ = xmac_stats->port_stats[k].tx_छोड़ो_ctrl_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_marker_pdu_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_lacpdu_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_drop_ip;
		*ptr++ = xmac_stats->port_stats[k].tx_marker_resp_pdu_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_xgmii_अक्षर2_match;
		*ptr++ = xmac_stats->port_stats[k].tx_xgmii_अक्षर1_match;
		*ptr++ = xmac_stats->port_stats[k].tx_xgmii_column2_match;
		*ptr++ = xmac_stats->port_stats[k].tx_xgmii_column1_match;
		*ptr++ = xmac_stats->port_stats[k].tx_any_err_frms;
		*ptr++ = xmac_stats->port_stats[k].tx_drop_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_vld_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_offload_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_octets;
		*ptr++ = xmac_stats->port_stats[k].rx_data_octets;
		*ptr++ = xmac_stats->port_stats[k].rx_offload_octets;
		*ptr++ = xmac_stats->port_stats[k].rx_vld_mcast_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_vld_bcast_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_accepted_ucast_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_accepted_nucast_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_tagged_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_दीर्घ_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_usized_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_osized_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_frag_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_jabber_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_64_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_65_127_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_128_255_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_256_511_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_512_1023_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_1024_1518_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_1519_4095_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_4096_8191_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_8192_max_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ttl_gt_max_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_ip;
		*ptr++ = xmac_stats->port_stats[k].rx_accepted_ip;
		*ptr++ = xmac_stats->port_stats[k].rx_ip_octets;
		*ptr++ = xmac_stats->port_stats[k].rx_err_ip;
		*ptr++ = xmac_stats->port_stats[k].rx_icmp;
		*ptr++ = xmac_stats->port_stats[k].rx_tcp;
		*ptr++ = xmac_stats->port_stats[k].rx_udp;
		*ptr++ = xmac_stats->port_stats[k].rx_err_tcp;
		*ptr++ = xmac_stats->port_stats[k].rx_छोड़ो_count;
		*ptr++ = xmac_stats->port_stats[k].rx_छोड़ो_ctrl_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_unsup_ctrl_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_fcs_err_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_in_rng_len_err_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_out_rng_len_err_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_drop_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_discarded_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_drop_ip;
		*ptr++ = xmac_stats->port_stats[k].rx_drop_udp;
		*ptr++ = xmac_stats->port_stats[k].rx_marker_pdu_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_lacpdu_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_unknown_pdu_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_marker_resp_pdu_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_fcs_discard;
		*ptr++ = xmac_stats->port_stats[k].rx_illegal_pdu_frms;
		*ptr++ = xmac_stats->port_stats[k].rx_चयन_discard;
		*ptr++ = xmac_stats->port_stats[k].rx_len_discard;
		*ptr++ = xmac_stats->port_stats[k].rx_rpa_discard;
		*ptr++ = xmac_stats->port_stats[k].rx_l2_mgmt_discard;
		*ptr++ = xmac_stats->port_stats[k].rx_rts_discard;
		*ptr++ = xmac_stats->port_stats[k].rx_trash_discard;
		*ptr++ = xmac_stats->port_stats[k].rx_buff_full_discard;
		*ptr++ = xmac_stats->port_stats[k].rx_red_discard;
		*ptr++ = xmac_stats->port_stats[k].rx_xgmii_ctrl_err_cnt;
		*ptr++ = xmac_stats->port_stats[k].rx_xgmii_data_err_cnt;
		*ptr++ = xmac_stats->port_stats[k].rx_xgmii_अक्षर1_match;
		*ptr++ = xmac_stats->port_stats[k].rx_xgmii_err_sym;
		*ptr++ = xmac_stats->port_stats[k].rx_xgmii_column1_match;
		*ptr++ = xmac_stats->port_stats[k].rx_xgmii_अक्षर2_match;
		*ptr++ = xmac_stats->port_stats[k].rx_local_fault;
		*ptr++ = xmac_stats->port_stats[k].rx_xgmii_column2_match;
		*ptr++ = xmac_stats->port_stats[k].rx_jettison;
		*ptr++ = xmac_stats->port_stats[k].rx_remote_fault;
	पूर्ण

	*ptr++ = 0;
	क्रम (k = 0; k < vdev->no_of_vpath; k++) अणु
		काष्ठा vxge_hw_vpath_stats_sw_info *vpath_info;

		vpath = &vdev->vpaths[k];
		j = vpath->device_id;
		vpath_info = (काष्ठा vxge_hw_vpath_stats_sw_info *)
				&sw_stats->vpath_info[j];
		*ptr++ = vpath_info->soft_reset_cnt;
		*ptr++ = vpath_info->error_stats.unknown_alarms;
		*ptr++ = vpath_info->error_stats.network_sustained_fault;
		*ptr++ = vpath_info->error_stats.network_sustained_ok;
		*ptr++ = vpath_info->error_stats.kdfcctl_fअगरo0_overग_लिखो;
		*ptr++ = vpath_info->error_stats.kdfcctl_fअगरo0_poison;
		*ptr++ = vpath_info->error_stats.kdfcctl_fअगरo0_dma_error;
		*ptr++ = vpath_info->error_stats.dblgen_fअगरo0_overflow;
		*ptr++ = vpath_info->error_stats.statsb_pअगर_chain_error;
		*ptr++ = vpath_info->error_stats.statsb_drop_समयout;
		*ptr++ = vpath_info->error_stats.target_illegal_access;
		*ptr++ = vpath_info->error_stats.ini_serr_det;
		*ptr++ = vpath_info->error_stats.prc_ring_bumps;
		*ptr++ = vpath_info->error_stats.prc_rxdcm_sc_err;
		*ptr++ = vpath_info->error_stats.prc_rxdcm_sc_पात;
		*ptr++ = vpath_info->error_stats.prc_quanta_size_err;
		*ptr++ = vpath_info->ring_stats.common_stats.full_cnt;
		*ptr++ = vpath_info->ring_stats.common_stats.usage_cnt;
		*ptr++ = vpath_info->ring_stats.common_stats.usage_max;
		*ptr++ = vpath_info->ring_stats.common_stats.
					reserve_मुक्त_swaps_cnt;
		*ptr++ = vpath_info->ring_stats.common_stats.total_compl_cnt;
		क्रम (j = 0; j < VXGE_HW_DTR_MAX_T_CODE; j++)
			*ptr++ = vpath_info->ring_stats.rxd_t_code_err_cnt[j];
		*ptr++ = vpath_info->fअगरo_stats.common_stats.full_cnt;
		*ptr++ = vpath_info->fअगरo_stats.common_stats.usage_cnt;
		*ptr++ = vpath_info->fअगरo_stats.common_stats.usage_max;
		*ptr++ = vpath_info->fअगरo_stats.common_stats.
						reserve_मुक्त_swaps_cnt;
		*ptr++ = vpath_info->fअगरo_stats.common_stats.total_compl_cnt;
		*ptr++ = vpath_info->fअगरo_stats.total_posts;
		*ptr++ = vpath_info->fअगरo_stats.total_buffers;
		क्रम (j = 0; j < VXGE_HW_DTR_MAX_T_CODE; j++)
			*ptr++ = vpath_info->fअगरo_stats.txd_t_code_err_cnt[j];
	पूर्ण

	*ptr++ = 0;
	क्रम (k = 0; k < vdev->no_of_vpath; k++) अणु
		काष्ठा vxge_hw_vpath_stats_hw_info *vpath_info;
		vpath = &vdev->vpaths[k];
		j = vpath->device_id;
		vpath_info = hw_stats->vpath_info[j];
		अगर (!vpath_info) अणु
			स_रखो(ptr, 0, VXGE_HW_VPATH_STATS_LEN * माप(u64));
			ptr += VXGE_HW_VPATH_STATS_LEN;
			जारी;
		पूर्ण
		*ptr++ = vpath_info->ini_num_mwr_sent;
		*ptr++ = vpath_info->ini_num_mrd_sent;
		*ptr++ = vpath_info->ini_num_cpl_rcvd;
		*ptr++ = vpath_info->ini_num_mwr_byte_sent;
		*ptr++ = vpath_info->ini_num_cpl_byte_rcvd;
		*ptr++ = vpath_info->wrcrdtarb_xoff;
		*ptr++ = vpath_info->rdcrdtarb_xoff;
		*ptr++ = vpath_info->vpath_genstats_count0;
		*ptr++ = vpath_info->vpath_genstats_count1;
		*ptr++ = vpath_info->vpath_genstats_count2;
		*ptr++ = vpath_info->vpath_genstats_count3;
		*ptr++ = vpath_info->vpath_genstats_count4;
		*ptr++ = vpath_info->vpath_genstats_count5;
		*ptr++ = vpath_info->prog_event_vnum0;
		*ptr++ = vpath_info->prog_event_vnum1;
		*ptr++ = vpath_info->prog_event_vnum2;
		*ptr++ = vpath_info->prog_event_vnum3;
		*ptr++ = vpath_info->rx_multi_cast_frame_discard;
		*ptr++ = vpath_info->rx_frm_transferred;
		*ptr++ = vpath_info->rxd_वापसed;
		*ptr++ = vpath_info->rx_mpa_len_fail_frms;
		*ptr++ = vpath_info->rx_mpa_mrk_fail_frms;
		*ptr++ = vpath_info->rx_mpa_crc_fail_frms;
		*ptr++ = vpath_info->rx_permitted_frms;
		*ptr++ = vpath_info->rx_vp_reset_discarded_frms;
		*ptr++ = vpath_info->rx_wol_frms;
		*ptr++ = vpath_info->tx_vp_reset_discarded_frms;
	पूर्ण

	*ptr++ = 0;
	*ptr++ = vdev->stats.vpaths_खोलो;
	*ptr++ = vdev->stats.vpath_खोलो_fail;
	*ptr++ = vdev->stats.link_up;
	*ptr++ = vdev->stats.link_करोwn;

	क्रम (k = 0; k < vdev->no_of_vpath; k++) अणु
		*ptr += vdev->vpaths[k].fअगरo.stats.tx_frms;
		*(ptr + 1) += vdev->vpaths[k].fअगरo.stats.tx_errors;
		*(ptr + 2) += vdev->vpaths[k].fअगरo.stats.tx_bytes;
		*(ptr + 3) += vdev->vpaths[k].fअगरo.stats.txd_not_मुक्त;
		*(ptr + 4) += vdev->vpaths[k].fअगरo.stats.txd_out_of_desc;
		*(ptr + 5) += vdev->vpaths[k].ring.stats.rx_frms;
		*(ptr + 6) += vdev->vpaths[k].ring.stats.rx_errors;
		*(ptr + 7) += vdev->vpaths[k].ring.stats.rx_bytes;
		*(ptr + 8) += vdev->vpaths[k].ring.stats.rx_mcast;
		*(ptr + 9) += vdev->vpaths[k].fअगरo.stats.pci_map_fail +
				vdev->vpaths[k].ring.stats.pci_map_fail;
		*(ptr + 10) += vdev->vpaths[k].ring.stats.skb_alloc_fail;
	पूर्ण

	ptr += 12;

	kमुक्त(xmac_stats);
	kमुक्त(sw_stats);
	kमुक्त(hw_stats);
पूर्ण

अटल व्योम vxge_ethtool_get_strings(काष्ठा net_device *dev, u32 stringset,
				     u8 *data)
अणु
	पूर्णांक stat_size = 0;
	पूर्णांक i, j;
	काष्ठा vxgedev *vdev = netdev_priv(dev);
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		vxge_add_string("VPATH STATISTICS%s\t\t\t",
			&stat_size, data, "");
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vxge_add_string("tx_ttl_eth_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_ttl_eth_octects_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_data_octects_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_mcast_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_bcast_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_ucast_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_tagged_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_vld_ip_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_vld_ip_octects_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_icmp_%d\t\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_tcp_%d\t\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_rst_tcp_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_udp_%d\t\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_unknown_proto_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_lost_ip_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_parse_error_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_tcp_offload_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_retx_tcp_offload_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_lost_ip_offload_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_eth_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_vld_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_offload_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_eth_octects_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_data_octects_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_offload_octects_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_vld_mcast_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_vld_bcast_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_accepted_ucast_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_accepted_nucast_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_tagged_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_long_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_usized_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_osized_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_frag_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_jabber_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_64_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_65_127_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_128_255_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_256_511_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_512_1023_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_1024_1518_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_1519_4095_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_4096_8191_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_8192_max_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ttl_gt_max_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ip%d\t\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_accepted_ip_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_ip_octects_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_err_ip_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_icmp_%d\t\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_tcp_%d\t\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_udp_%d\t\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_err_tcp_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_lost_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_lost_ip_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_lost_ip_offload_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_various_discard_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_sleep_discard_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_red_discard_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_queue_full_discard_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_mpa_ok_frms_%d\t\t\t",
					&stat_size, data, i);
		पूर्ण

		vxge_add_string("\nAGGR STATISTICS%s\t\t\t\t",
			&stat_size, data, "");
		क्रम (i = 0; i < vdev->max_config_port; i++) अणु
			vxge_add_string("tx_frms_%d\t\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_data_octects_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_mcast_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_bcast_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_discarded_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_errored_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_frms_%d\t\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_data_octects_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_mcast_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_bcast_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_discarded_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_errored_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_unknown_slow_proto_frms_%d\t",
				&stat_size, data, i);
		पूर्ण

		vxge_add_string("\nPORT STATISTICS%s\t\t\t\t",
			&stat_size, data, "");
		क्रम (i = 0; i < vdev->max_config_port; i++) अणु
			vxge_add_string("tx_ttl_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_ttl_octects_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_data_octects_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_mcast_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_bcast_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_ucast_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_tagged_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_vld_ip_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_vld_ip_octects_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_icmp_%d\t\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_tcp_%d\t\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_rst_tcp_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_udp_%d\t\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_parse_error_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_unknown_protocol_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_pause_ctrl_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_marker_pdu_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_lacpdu_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_drop_ip_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_marker_resp_pdu_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_xgmii_char2_match_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_xgmii_char1_match_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_xgmii_column2_match_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_xgmii_column1_match_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_any_err_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("tx_drop_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_vld_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_offload_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_octects_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_data_octects_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_offload_octects_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_vld_mcast_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_vld_bcast_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_accepted_ucast_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_accepted_nucast_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_tagged_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_long_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_usized_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_osized_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_frag_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_jabber_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_64_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_65_127_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_128_255_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_256_511_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_512_1023_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_1024_1518_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_1519_4095_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_4096_8191_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_8192_max_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ttl_gt_max_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ip_%d\t\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_accepted_ip_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_ip_octets_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_err_ip_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_icmp_%d\t\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_tcp_%d\t\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_udp_%d\t\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_err_tcp_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_pause_count_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_pause_ctrl_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_unsup_ctrl_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_fcs_err_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_in_rng_len_err_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_out_rng_len_err_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_drop_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_discard_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_drop_ip_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_drop_udp_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_marker_pdu_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_lacpdu_frms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_unknown_pdu_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_marker_resp_pdu_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_fcs_discard_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_illegal_pdu_frms_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_switch_discard_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_len_discard_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_rpa_discard_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_l2_mgmt_discard_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_rts_discard_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_trash_discard_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_buff_full_discard_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_red_discard_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_xgmii_ctrl_err_cnt_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_xgmii_data_err_cnt_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_xgmii_char1_match_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_xgmii_err_sym_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_xgmii_column1_match_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_xgmii_char2_match_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_local_fault_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_xgmii_column2_match_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_jettison_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("rx_remote_fault_%d\t\t\t",
				&stat_size, data, i);
		पूर्ण

		vxge_add_string("\n SOFTWARE STATISTICS%s\t\t\t",
			&stat_size, data, "");
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vxge_add_string("soft_reset_cnt_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("unknown_alarms_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("network_sustained_fault_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("network_sustained_ok_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("kdfcctl_fifo0_overwrite_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("kdfcctl_fifo0_poison_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("kdfcctl_fifo0_dma_error_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("dblgen_fifo0_overflow_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("statsb_pif_chain_error_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("statsb_drop_timeout_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("target_illegal_access_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("ini_serr_det_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("prc_ring_bumps_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("prc_rxdcm_sc_err_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("prc_rxdcm_sc_abort_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("prc_quanta_size_err_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("ring_full_cnt_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("ring_usage_cnt_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("ring_usage_max_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("ring_reserve_free_swaps_cnt_%d\t",
				&stat_size, data, i);
			vxge_add_string("ring_total_compl_cnt_%d\t\t",
				&stat_size, data, i);
			क्रम (j = 0; j < VXGE_HW_DTR_MAX_T_CODE; j++)
				vxge_add_string("rxd_t_code_err_cnt%d_%d\t\t",
					&stat_size, data, j, i);
			vxge_add_string("fifo_full_cnt_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("fifo_usage_cnt_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("fifo_usage_max_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("fifo_reserve_free_swaps_cnt_%d\t",
				&stat_size, data, i);
			vxge_add_string("fifo_total_compl_cnt_%d\t\t",
				&stat_size, data, i);
			vxge_add_string("fifo_total_posts_%d\t\t\t",
				&stat_size, data, i);
			vxge_add_string("fifo_total_buffers_%d\t\t",
				&stat_size, data, i);
			क्रम (j = 0; j < VXGE_HW_DTR_MAX_T_CODE; j++)
				vxge_add_string("txd_t_code_err_cnt%d_%d\t\t",
					&stat_size, data, j, i);
		पूर्ण

		vxge_add_string("\n HARDWARE STATISTICS%s\t\t\t",
				&stat_size, data, "");
		क्रम (i = 0; i < vdev->no_of_vpath; i++) अणु
			vxge_add_string("ini_num_mwr_sent_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("ini_num_mrd_sent_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("ini_num_cpl_rcvd_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("ini_num_mwr_byte_sent_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("ini_num_cpl_byte_rcvd_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("wrcrdtarb_xoff_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rdcrdtarb_xoff_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("vpath_genstats_count0_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("vpath_genstats_count1_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("vpath_genstats_count2_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("vpath_genstats_count3_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("vpath_genstats_count4_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("vpath_genstats_count5_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("prog_event_vnum0_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("prog_event_vnum1_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("prog_event_vnum2_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("prog_event_vnum3_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_multi_cast_frame_discard_%d\t",
					&stat_size, data, i);
			vxge_add_string("rx_frm_transferred_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rxd_returned_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_mpa_len_fail_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_mpa_mrk_fail_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_mpa_crc_fail_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_permitted_frms_%d\t\t",
					&stat_size, data, i);
			vxge_add_string("rx_vp_reset_discarded_frms_%d\t",
					&stat_size, data, i);
			vxge_add_string("rx_wol_frms_%d\t\t\t",
					&stat_size, data, i);
			vxge_add_string("tx_vp_reset_discarded_frms_%d\t",
					&stat_size, data, i);
		पूर्ण

		स_नकल(data + stat_size, &ethtool_driver_stats_keys,
			माप(ethtool_driver_stats_keys));
	पूर्ण
पूर्ण

अटल पूर्णांक vxge_ethtool_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);

	वापस माप(काष्ठा vxge_hw_vpath_reg) * vdev->no_of_vpath;
पूर्ण

अटल पूर्णांक vxge_ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस VXGE_TITLE_LEN +
			(vdev->no_of_vpath * VXGE_HW_VPATH_STATS_LEN) +
			(vdev->max_config_port * VXGE_HW_AGGR_STATS_LEN) +
			(vdev->max_config_port * VXGE_HW_PORT_STATS_LEN) +
			(vdev->no_of_vpath * VXGE_HW_VPATH_TX_STATS_LEN) +
			(vdev->no_of_vpath * VXGE_HW_VPATH_RX_STATS_LEN) +
			(vdev->no_of_vpath * VXGE_SW_STATS_LEN) +
			DRIVER_STAT_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक vxge_fw_flash(काष्ठा net_device *dev, काष्ठा ethtool_flash *parms)
अणु
	काष्ठा vxgedev *vdev = netdev_priv(dev);

	अगर (vdev->max_vpath_supported != VXGE_HW_MAX_VIRTUAL_PATHS) अणु
		prपूर्णांकk(KERN_INFO "Single Function Mode is required to flash the"
		       " firmware\n");
		वापस -EINVAL;
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		prपूर्णांकk(KERN_INFO "Interface %s must be down to flash the "
		       "firmware\n", dev->name);
		वापस -EBUSY;
	पूर्ण

	वापस vxge_fw_upgrade(vdev, parms->data, 1);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vxge_ethtool_ops = अणु
	.get_drvinfo		= vxge_ethtool_gdrvinfo,
	.get_regs_len		= vxge_ethtool_get_regs_len,
	.get_regs		= vxge_ethtool_gregs,
	.get_link		= ethtool_op_get_link,
	.get_छोड़ोparam		= vxge_ethtool_getछोड़ो_data,
	.set_छोड़ोparam		= vxge_ethtool_setछोड़ो_data,
	.get_strings		= vxge_ethtool_get_strings,
	.set_phys_id		= vxge_ethtool_idnic,
	.get_sset_count		= vxge_ethtool_get_sset_count,
	.get_ethtool_stats	= vxge_get_ethtool_stats,
	.flash_device		= vxge_fw_flash,
	.get_link_ksettings	= vxge_ethtool_get_link_ksettings,
	.set_link_ksettings	= vxge_ethtool_set_link_ksettings,
पूर्ण;

व्योम vxge_initialize_ethtool_ops(काष्ठा net_device *ndev)
अणु
	ndev->ethtool_ops = &vxge_ethtool_ops;
पूर्ण
