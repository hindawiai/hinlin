<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "ixgbe.h"
#समावेश <linux/dcbnl.h>
#समावेश "ixgbe_dcb_82598.h"
#समावेश "ixgbe_dcb_82599.h"
#समावेश "ixgbe_sriov.h"

/* Callbacks क्रम DCB netlink in the kernel */
#घोषणा BIT_DCB_MODE	0x01
#घोषणा BIT_PFC		0x02
#घोषणा BIT_PG_RX	0x04
#घोषणा BIT_PG_TX	0x08
#घोषणा BIT_APP_UPCHG	0x10
#घोषणा BIT_LINKSPEED   0x80

/* Responses क्रम the DCB_C_SET_ALL command */
#घोषणा DCB_HW_CHG_RST  0  /* DCB configuration changed with reset */
#घोषणा DCB_NO_HW_CHG   1  /* DCB configuration did not change */
#घोषणा DCB_HW_CHG      2  /* DCB configuration changed, no reset */

अटल पूर्णांक ixgbe_copy_dcb_cfg(काष्ठा ixgbe_adapter *adapter, पूर्णांक tc_max)
अणु
	काष्ठा ixgbe_dcb_config *scfg = &adapter->temp_dcb_cfg;
	काष्ठा ixgbe_dcb_config *dcfg = &adapter->dcb_cfg;
	काष्ठा tc_configuration *src = शून्य;
	काष्ठा tc_configuration *dst = शून्य;
	पूर्णांक i, j;
	पूर्णांक tx = DCB_TX_CONFIG;
	पूर्णांक rx = DCB_RX_CONFIG;
	पूर्णांक changes = 0;
#अगर_घोषित IXGBE_FCOE
	काष्ठा dcb_app app = अणु
			      .selector = DCB_APP_IDTYPE_ETHTYPE,
			      .protocol = ETH_P_FCOE,
			     पूर्ण;
	u8 up = dcb_getapp(adapter->netdev, &app);

	अगर (up && !(up & BIT(adapter->fcoe.up)))
		changes |= BIT_APP_UPCHG;
#पूर्ण_अगर

	क्रम (i = DCB_PG_ATTR_TC_0; i < tc_max + DCB_PG_ATTR_TC_0; i++) अणु
		src = &scfg->tc_config[i - DCB_PG_ATTR_TC_0];
		dst = &dcfg->tc_config[i - DCB_PG_ATTR_TC_0];

		अगर (dst->path[tx].prio_type != src->path[tx].prio_type) अणु
			dst->path[tx].prio_type = src->path[tx].prio_type;
			changes |= BIT_PG_TX;
		पूर्ण

		अगर (dst->path[tx].bwg_id != src->path[tx].bwg_id) अणु
			dst->path[tx].bwg_id = src->path[tx].bwg_id;
			changes |= BIT_PG_TX;
		पूर्ण

		अगर (dst->path[tx].bwg_percent != src->path[tx].bwg_percent) अणु
			dst->path[tx].bwg_percent = src->path[tx].bwg_percent;
			changes |= BIT_PG_TX;
		पूर्ण

		अगर (dst->path[tx].up_to_tc_biपंचांगap !=
				src->path[tx].up_to_tc_biपंचांगap) अणु
			dst->path[tx].up_to_tc_biपंचांगap =
				src->path[tx].up_to_tc_biपंचांगap;
			changes |= (BIT_PG_TX | BIT_PFC | BIT_APP_UPCHG);
		पूर्ण

		अगर (dst->path[rx].prio_type != src->path[rx].prio_type) अणु
			dst->path[rx].prio_type = src->path[rx].prio_type;
			changes |= BIT_PG_RX;
		पूर्ण

		अगर (dst->path[rx].bwg_id != src->path[rx].bwg_id) अणु
			dst->path[rx].bwg_id = src->path[rx].bwg_id;
			changes |= BIT_PG_RX;
		पूर्ण

		अगर (dst->path[rx].bwg_percent != src->path[rx].bwg_percent) अणु
			dst->path[rx].bwg_percent = src->path[rx].bwg_percent;
			changes |= BIT_PG_RX;
		पूर्ण

		अगर (dst->path[rx].up_to_tc_biपंचांगap !=
				src->path[rx].up_to_tc_biपंचांगap) अणु
			dst->path[rx].up_to_tc_biपंचांगap =
				src->path[rx].up_to_tc_biपंचांगap;
			changes |= (BIT_PG_RX | BIT_PFC | BIT_APP_UPCHG);
		पूर्ण
	पूर्ण

	क्रम (i = DCB_PG_ATTR_BW_ID_0; i < DCB_PG_ATTR_BW_ID_MAX; i++) अणु
		j = i - DCB_PG_ATTR_BW_ID_0;
		अगर (dcfg->bw_percentage[tx][j] != scfg->bw_percentage[tx][j]) अणु
			dcfg->bw_percentage[tx][j] = scfg->bw_percentage[tx][j];
			changes |= BIT_PG_TX;
		पूर्ण
		अगर (dcfg->bw_percentage[rx][j] != scfg->bw_percentage[rx][j]) अणु
			dcfg->bw_percentage[rx][j] = scfg->bw_percentage[rx][j];
			changes |= BIT_PG_RX;
		पूर्ण
	पूर्ण

	क्रम (i = DCB_PFC_UP_ATTR_0; i < DCB_PFC_UP_ATTR_MAX; i++) अणु
		j = i - DCB_PFC_UP_ATTR_0;
		अगर (dcfg->tc_config[j].dcb_pfc != scfg->tc_config[j].dcb_pfc) अणु
			dcfg->tc_config[j].dcb_pfc = scfg->tc_config[j].dcb_pfc;
			changes |= BIT_PFC;
		पूर्ण
	पूर्ण

	अगर (dcfg->pfc_mode_enable != scfg->pfc_mode_enable) अणु
		dcfg->pfc_mode_enable = scfg->pfc_mode_enable;
		changes |= BIT_PFC;
	पूर्ण

	वापस changes;
पूर्ण

अटल u8 ixgbe_dcbnl_get_state(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	वापस !!(adapter->flags & IXGBE_FLAG_DCB_ENABLED);
पूर्ण

अटल u8 ixgbe_dcbnl_set_state(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	/* Fail command अगर not in CEE mode */
	अगर (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस 1;

	/* verअगरy there is something to करो, अगर not then निकास */
	अगर (!state == !(adapter->flags & IXGBE_FLAG_DCB_ENABLED))
		वापस 0;

	वापस !!ixgbe_setup_tc(netdev,
				state ? adapter->dcb_cfg.num_tcs.pg_tcs : 0);
पूर्ण

अटल व्योम ixgbe_dcbnl_get_perm_hw_addr(काष्ठा net_device *netdev,
					 u8 *perm_addr)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i, j;

	स_रखो(perm_addr, 0xff, MAX_ADDR_LEN);

	क्रम (i = 0; i < netdev->addr_len; i++)
		perm_addr[i] = adapter->hw.mac.perm_addr[i];

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
		क्रम (j = 0; j < netdev->addr_len; j++, i++)
			perm_addr[i] = adapter->hw.mac.san_addr[j];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_dcbnl_set_pg_tc_cfg_tx(काष्ठा net_device *netdev, पूर्णांक tc,
					 u8 prio, u8 bwg_id, u8 bw_pct,
					 u8 up_map)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (prio != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[0].prio_type = prio;
	अगर (bwg_id != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[0].bwg_id = bwg_id;
	अगर (bw_pct != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[0].bwg_percent =
			bw_pct;
	अगर (up_map != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[0].up_to_tc_biपंचांगap =
			up_map;
पूर्ण

अटल व्योम ixgbe_dcbnl_set_pg_bwg_cfg_tx(काष्ठा net_device *netdev, पूर्णांक bwg_id,
					  u8 bw_pct)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	adapter->temp_dcb_cfg.bw_percentage[0][bwg_id] = bw_pct;
पूर्ण

अटल व्योम ixgbe_dcbnl_set_pg_tc_cfg_rx(काष्ठा net_device *netdev, पूर्णांक tc,
					 u8 prio, u8 bwg_id, u8 bw_pct,
					 u8 up_map)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (prio != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[1].prio_type = prio;
	अगर (bwg_id != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[1].bwg_id = bwg_id;
	अगर (bw_pct != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[1].bwg_percent =
			bw_pct;
	अगर (up_map != DCB_ATTR_VALUE_UNDEFINED)
		adapter->temp_dcb_cfg.tc_config[tc].path[1].up_to_tc_biपंचांगap =
			up_map;
पूर्ण

अटल व्योम ixgbe_dcbnl_set_pg_bwg_cfg_rx(काष्ठा net_device *netdev, पूर्णांक bwg_id,
					  u8 bw_pct)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	adapter->temp_dcb_cfg.bw_percentage[1][bwg_id] = bw_pct;
पूर्ण

अटल व्योम ixgbe_dcbnl_get_pg_tc_cfg_tx(काष्ठा net_device *netdev, पूर्णांक tc,
					 u8 *prio, u8 *bwg_id, u8 *bw_pct,
					 u8 *up_map)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	*prio = adapter->dcb_cfg.tc_config[tc].path[0].prio_type;
	*bwg_id = adapter->dcb_cfg.tc_config[tc].path[0].bwg_id;
	*bw_pct = adapter->dcb_cfg.tc_config[tc].path[0].bwg_percent;
	*up_map = adapter->dcb_cfg.tc_config[tc].path[0].up_to_tc_biपंचांगap;
पूर्ण

अटल व्योम ixgbe_dcbnl_get_pg_bwg_cfg_tx(काष्ठा net_device *netdev, पूर्णांक bwg_id,
					  u8 *bw_pct)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	*bw_pct = adapter->dcb_cfg.bw_percentage[0][bwg_id];
पूर्ण

अटल व्योम ixgbe_dcbnl_get_pg_tc_cfg_rx(काष्ठा net_device *netdev, पूर्णांक tc,
					 u8 *prio, u8 *bwg_id, u8 *bw_pct,
					 u8 *up_map)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	*prio = adapter->dcb_cfg.tc_config[tc].path[1].prio_type;
	*bwg_id = adapter->dcb_cfg.tc_config[tc].path[1].bwg_id;
	*bw_pct = adapter->dcb_cfg.tc_config[tc].path[1].bwg_percent;
	*up_map = adapter->dcb_cfg.tc_config[tc].path[1].up_to_tc_biपंचांगap;
पूर्ण

अटल व्योम ixgbe_dcbnl_get_pg_bwg_cfg_rx(काष्ठा net_device *netdev, पूर्णांक bwg_id,
					  u8 *bw_pct)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	*bw_pct = adapter->dcb_cfg.bw_percentage[1][bwg_id];
पूर्ण

अटल व्योम ixgbe_dcbnl_set_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक priority,
				    u8 setting)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	adapter->temp_dcb_cfg.tc_config[priority].dcb_pfc = setting;
	अगर (adapter->temp_dcb_cfg.tc_config[priority].dcb_pfc !=
	    adapter->dcb_cfg.tc_config[priority].dcb_pfc)
		adapter->temp_dcb_cfg.pfc_mode_enable = true;
पूर्ण

अटल व्योम ixgbe_dcbnl_get_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक priority,
				    u8 *setting)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	*setting = adapter->dcb_cfg.tc_config[priority].dcb_pfc;
पूर्ण

अटल व्योम ixgbe_dcbnl_devreset(काष्ठा net_device *dev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);

	जबतक (test_and_set_bit(__IXGBE_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (netअगर_running(dev))
		dev->netdev_ops->nकरो_stop(dev);

	ixgbe_clear_पूर्णांकerrupt_scheme(adapter);
	ixgbe_init_पूर्णांकerrupt_scheme(adapter);

	अगर (netअगर_running(dev))
		dev->netdev_ops->nकरो_खोलो(dev);

	clear_bit(__IXGBE_RESETTING, &adapter->state);
पूर्ण

अटल u8 ixgbe_dcbnl_set_all(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_dcb_config *dcb_cfg = &adapter->dcb_cfg;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक ret = DCB_NO_HW_CHG;
	पूर्णांक i;

	/* Fail command अगर not in CEE mode */
	अगर (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस DCB_NO_HW_CHG;

	adapter->dcb_set_biपंचांगap |= ixgbe_copy_dcb_cfg(adapter,
						      MAX_TRAFFIC_CLASS);
	अगर (!adapter->dcb_set_biपंचांगap)
		वापस DCB_NO_HW_CHG;

	अगर (adapter->dcb_set_biपंचांगap & (BIT_PG_TX|BIT_PG_RX)) अणु
		u16 refill[MAX_TRAFFIC_CLASS], max[MAX_TRAFFIC_CLASS];
		u8 bwg_id[MAX_TRAFFIC_CLASS], prio_type[MAX_TRAFFIC_CLASS];
		/* Priority to TC mapping in CEE हाल शेष to 1:1 */
		u8 prio_tc[MAX_USER_PRIORITY];
		पूर्णांक max_frame = adapter->netdev->mtu + ETH_HLEN + ETH_FCS_LEN;

#अगर_घोषित IXGBE_FCOE
		अगर (adapter->netdev->features & NETIF_F_FCOE_MTU)
			max_frame = max(max_frame, IXGBE_FCOE_JUMBO_FRAME_SIZE);
#पूर्ण_अगर

		ixgbe_dcb_calculate_tc_credits(hw, dcb_cfg, max_frame,
					       DCB_TX_CONFIG);
		ixgbe_dcb_calculate_tc_credits(hw, dcb_cfg, max_frame,
					       DCB_RX_CONFIG);

		ixgbe_dcb_unpack_refill(dcb_cfg, DCB_TX_CONFIG, refill);
		ixgbe_dcb_unpack_max(dcb_cfg, max);
		ixgbe_dcb_unpack_bwgid(dcb_cfg, DCB_TX_CONFIG, bwg_id);
		ixgbe_dcb_unpack_prio(dcb_cfg, DCB_TX_CONFIG, prio_type);
		ixgbe_dcb_unpack_map(dcb_cfg, DCB_TX_CONFIG, prio_tc);

		ixgbe_dcb_hw_ets_config(hw, refill, max, bwg_id,
					prio_type, prio_tc);

		क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			netdev_set_prio_tc_map(netdev, i, prio_tc[i]);

		ret = DCB_HW_CHG_RST;
	पूर्ण

	अगर (adapter->dcb_set_biपंचांगap & BIT_PFC) अणु
		अगर (dcb_cfg->pfc_mode_enable) अणु
			u8 pfc_en;
			u8 prio_tc[MAX_USER_PRIORITY];

			ixgbe_dcb_unpack_map(dcb_cfg, DCB_TX_CONFIG, prio_tc);
			ixgbe_dcb_unpack_pfc(dcb_cfg, &pfc_en);
			ixgbe_dcb_hw_pfc_config(hw, pfc_en, prio_tc);
		पूर्ण अन्यथा अणु
			hw->mac.ops.fc_enable(hw);
		पूर्ण

		ixgbe_set_rx_drop_en(adapter);

		ret = DCB_HW_CHG;
	पूर्ण

#अगर_घोषित IXGBE_FCOE
	/* Reprogram FCoE hardware offloads when the traffic class
	 * FCoE is using changes. This happens अगर the APP info
	 * changes or the up2tc mapping is updated.
	 */
	अगर (adapter->dcb_set_biपंचांगap & BIT_APP_UPCHG) अणु
		काष्ठा dcb_app app = अणु
				      .selector = DCB_APP_IDTYPE_ETHTYPE,
				      .protocol = ETH_P_FCOE,
				     पूर्ण;
		u8 up = dcb_getapp(netdev, &app);

		adapter->fcoe.up = ffs(up) - 1;
		ixgbe_dcbnl_devreset(netdev);
		ret = DCB_HW_CHG_RST;
	पूर्ण
#पूर्ण_अगर

	adapter->dcb_set_biपंचांगap = 0x00;
	वापस ret;
पूर्ण

अटल u8 ixgbe_dcbnl_अ_लोap(काष्ठा net_device *netdev, पूर्णांक capid, u8 *cap)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	चयन (capid) अणु
	हाल DCB_CAP_ATTR_PG:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_PFC:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_UP2TC:
		*cap = false;
		अवरोध;
	हाल DCB_CAP_ATTR_PG_TCS:
		*cap = 0x80;
		अवरोध;
	हाल DCB_CAP_ATTR_PFC_TCS:
		*cap = 0x80;
		अवरोध;
	हाल DCB_CAP_ATTR_GSP:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_BCN:
		*cap = false;
		अवरोध;
	हाल DCB_CAP_ATTR_DCBX:
		*cap = adapter->dcbx_cap;
		अवरोध;
	शेष:
		*cap = false;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_dcbnl_getnumtcs(काष्ठा net_device *netdev, पूर्णांक tcid, u8 *num)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->flags & IXGBE_FLAG_DCB_ENABLED) अणु
		चयन (tcid) अणु
		हाल DCB_NUMTCS_ATTR_PG:
			*num = adapter->dcb_cfg.num_tcs.pg_tcs;
			अवरोध;
		हाल DCB_NUMTCS_ATTR_PFC:
			*num = adapter->dcb_cfg.num_tcs.pfc_tcs;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_dcbnl_setnumtcs(काष्ठा net_device *netdev, पूर्णांक tcid, u8 num)
अणु
	वापस -EINVAL;
पूर्ण

अटल u8 ixgbe_dcbnl_getpfcstate(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	वापस adapter->dcb_cfg.pfc_mode_enable;
पूर्ण

अटल व्योम ixgbe_dcbnl_setpfcstate(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	adapter->temp_dcb_cfg.pfc_mode_enable = state;
पूर्ण

/**
 * ixgbe_dcbnl_getapp - retrieve the DCBX application user priority
 * @netdev : the corresponding netdev
 * @idtype : identअगरies the id as ether type or TCP/UDP port number
 * @id: id is either ether type or TCP/UDP port number
 *
 * Returns : on success, वापसs a non-zero 802.1p user priority biपंचांगap
 * otherwise वापसs -EINVAL as the invalid user priority biपंचांगap to indicate an
 * error.
 */
अटल पूर्णांक ixgbe_dcbnl_getapp(काष्ठा net_device *netdev, u8 idtype, u16 id)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा dcb_app app = अणु
				.selector = idtype,
				.protocol = id,
			     पूर्ण;

	अगर (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस -EINVAL;

	वापस dcb_getapp(netdev, &app);
पूर्ण

अटल पूर्णांक ixgbe_dcbnl_ieee_getets(काष्ठा net_device *dev,
				   काष्ठा ieee_ets *ets)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ieee_ets *my_ets = adapter->ixgbe_ieee_ets;

	ets->ets_cap = adapter->dcb_cfg.num_tcs.pg_tcs;

	/* No IEEE PFC settings available */
	अगर (!my_ets)
		वापस 0;

	ets->cbs = my_ets->cbs;
	स_नकल(ets->tc_tx_bw, my_ets->tc_tx_bw, माप(ets->tc_tx_bw));
	स_नकल(ets->tc_rx_bw, my_ets->tc_rx_bw, माप(ets->tc_rx_bw));
	स_नकल(ets->tc_tsa, my_ets->tc_tsa, माप(ets->tc_tsa));
	स_नकल(ets->prio_tc, my_ets->prio_tc, माप(ets->prio_tc));
	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_dcbnl_ieee_setets(काष्ठा net_device *dev,
				   काष्ठा ieee_ets *ets)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	पूर्णांक max_frame = dev->mtu + ETH_HLEN + ETH_FCS_LEN;
	पूर्णांक i, err;
	__u8 max_tc = 0;
	__u8 map_chg = 0;

	अगर (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		वापस -EINVAL;

	अगर (!adapter->ixgbe_ieee_ets) अणु
		adapter->ixgbe_ieee_ets = kदो_स्मृति(माप(काष्ठा ieee_ets),
						  GFP_KERNEL);
		अगर (!adapter->ixgbe_ieee_ets)
			वापस -ENOMEM;

		/* initialize UP2TC mappings to invalid value */
		क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			adapter->ixgbe_ieee_ets->prio_tc[i] =
				IEEE_8021QAZ_MAX_TCS;
		/* अगर possible update UP2TC mappings from HW */
		ixgbe_dcb_पढ़ो_rtrup2tc(&adapter->hw,
					adapter->ixgbe_ieee_ets->prio_tc);
	पूर्ण

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		अगर (ets->prio_tc[i] > max_tc)
			max_tc = ets->prio_tc[i];
		अगर (ets->prio_tc[i] != adapter->ixgbe_ieee_ets->prio_tc[i])
			map_chg = 1;
	पूर्ण

	स_नकल(adapter->ixgbe_ieee_ets, ets, माप(*adapter->ixgbe_ieee_ets));

	अगर (max_tc)
		max_tc++;

	अगर (max_tc > adapter->dcb_cfg.num_tcs.pg_tcs)
		वापस -EINVAL;

	अगर (max_tc != adapter->hw_tcs) अणु
		err = ixgbe_setup_tc(dev, max_tc);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (map_chg) अणु
		ixgbe_dcbnl_devreset(dev);
	पूर्ण

	वापस ixgbe_dcb_hw_ets(&adapter->hw, ets, max_frame);
पूर्ण

अटल पूर्णांक ixgbe_dcbnl_ieee_getpfc(काष्ठा net_device *dev,
				   काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ieee_pfc *my_pfc = adapter->ixgbe_ieee_pfc;
	पूर्णांक i;

	pfc->pfc_cap = adapter->dcb_cfg.num_tcs.pfc_tcs;

	/* No IEEE PFC settings available */
	अगर (!my_pfc)
		वापस 0;

	pfc->pfc_en = my_pfc->pfc_en;
	pfc->mbc = my_pfc->mbc;
	pfc->delay = my_pfc->delay;

	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		pfc->requests[i] = adapter->stats.pxoffrxc[i];
		pfc->indications[i] = adapter->stats.pxofftxc[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_dcbnl_ieee_setpfc(काष्ठा net_device *dev,
				   काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u8 *prio_tc;
	पूर्णांक err;

	अगर (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		वापस -EINVAL;

	अगर (!adapter->ixgbe_ieee_pfc) अणु
		adapter->ixgbe_ieee_pfc = kदो_स्मृति(माप(काष्ठा ieee_pfc),
						  GFP_KERNEL);
		अगर (!adapter->ixgbe_ieee_pfc)
			वापस -ENOMEM;
	पूर्ण

	prio_tc = adapter->ixgbe_ieee_ets->prio_tc;
	स_नकल(adapter->ixgbe_ieee_pfc, pfc, माप(*adapter->ixgbe_ieee_pfc));

	/* Enable link flow control parameters अगर PFC is disabled */
	अगर (pfc->pfc_en)
		err = ixgbe_dcb_hw_pfc_config(hw, pfc->pfc_en, prio_tc);
	अन्यथा
		err = hw->mac.ops.fc_enable(hw);

	ixgbe_set_rx_drop_en(adapter);

	वापस err;
पूर्ण

अटल पूर्णांक ixgbe_dcbnl_ieee_setapp(काष्ठा net_device *dev,
				   काष्ठा dcb_app *app)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	पूर्णांक err;

	अगर (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		वापस -EINVAL;

	err = dcb_ieee_setapp(dev, app);
	अगर (err)
		वापस err;

#अगर_घोषित IXGBE_FCOE
	अगर (app->selector == IEEE_8021QAZ_APP_SEL_ETHERTYPE &&
	    app->protocol == ETH_P_FCOE) अणु
		u8 app_mask = dcb_ieee_getapp_mask(dev, app);

		अगर (app_mask & BIT(adapter->fcoe.up))
			वापस 0;

		adapter->fcoe.up = app->priority;
		ixgbe_dcbnl_devreset(dev);
	पूर्ण
#पूर्ण_अगर

	/* VF devices should use शेष UP when available */
	अगर (app->selector == IEEE_8021QAZ_APP_SEL_ETHERTYPE &&
	    app->protocol == 0) अणु
		पूर्णांक vf;

		adapter->शेष_up = app->priority;

		क्रम (vf = 0; vf < adapter->num_vfs; vf++) अणु
			काष्ठा vf_data_storage *vfinfo = &adapter->vfinfo[vf];

			अगर (!vfinfo->pf_qos)
				ixgbe_set_vmvir(adapter, vfinfo->pf_vlan,
						app->priority, vf);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_dcbnl_ieee_delapp(काष्ठा net_device *dev,
				   काष्ठा dcb_app *app)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	पूर्णांक err;

	अगर (!(adapter->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		वापस -EINVAL;

	err = dcb_ieee_delapp(dev, app);

#अगर_घोषित IXGBE_FCOE
	अगर (!err && app->selector == IEEE_8021QAZ_APP_SEL_ETHERTYPE &&
	    app->protocol == ETH_P_FCOE) अणु
		u8 app_mask = dcb_ieee_getapp_mask(dev, app);

		अगर (app_mask & BIT(adapter->fcoe.up))
			वापस 0;

		adapter->fcoe.up = app_mask ?
				   ffs(app_mask) - 1 : IXGBE_FCOE_DEFTC;
		ixgbe_dcbnl_devreset(dev);
	पूर्ण
#पूर्ण_अगर
	/* IF शेष priority is being हटाओd clear VF शेष UP */
	अगर (app->selector == IEEE_8021QAZ_APP_SEL_ETHERTYPE &&
	    app->protocol == 0 && adapter->शेष_up == app->priority) अणु
		पूर्णांक vf;
		दीर्घ अचिन्हित पूर्णांक app_mask = dcb_ieee_getapp_mask(dev, app);
		पूर्णांक qos = app_mask ? find_first_bit(&app_mask, 8) : 0;

		adapter->शेष_up = qos;

		क्रम (vf = 0; vf < adapter->num_vfs; vf++) अणु
			काष्ठा vf_data_storage *vfinfo = &adapter->vfinfo[vf];

			अगर (!vfinfo->pf_qos)
				ixgbe_set_vmvir(adapter, vfinfo->pf_vlan,
						qos, vf);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल u8 ixgbe_dcbnl_getdcbx(काष्ठा net_device *dev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	वापस adapter->dcbx_cap;
पूर्ण

अटल u8 ixgbe_dcbnl_setdcbx(काष्ठा net_device *dev, u8 mode)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ieee_ets ets = अणु0पूर्ण;
	काष्ठा ieee_pfc pfc = अणु0पूर्ण;
	पूर्णांक err = 0;

	/* no support क्रम LLD_MANAGED modes or CEE+IEEE */
	अगर ((mode & DCB_CAP_DCBX_LLD_MANAGED) ||
	    ((mode & DCB_CAP_DCBX_VER_IEEE) && (mode & DCB_CAP_DCBX_VER_CEE)) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		वापस 1;

	अगर (mode == adapter->dcbx_cap)
		वापस 0;

	adapter->dcbx_cap = mode;

	/* ETS and PFC शेषs */
	ets.ets_cap = 8;
	pfc.pfc_cap = 8;

	अगर (mode & DCB_CAP_DCBX_VER_IEEE) अणु
		ixgbe_dcbnl_ieee_setets(dev, &ets);
		ixgbe_dcbnl_ieee_setpfc(dev, &pfc);
	पूर्ण अन्यथा अगर (mode & DCB_CAP_DCBX_VER_CEE) अणु
		u8 mask = BIT_PFC | BIT_PG_TX | BIT_PG_RX | BIT_APP_UPCHG;

		adapter->dcb_set_biपंचांगap |= mask;
		ixgbe_dcbnl_set_all(dev);
	पूर्ण अन्यथा अणु
		/* Drop पूर्णांकo single TC mode strict priority as this
		 * indicates CEE and IEEE versions are disabled
		 */
		ixgbe_dcbnl_ieee_setets(dev, &ets);
		ixgbe_dcbnl_ieee_setpfc(dev, &pfc);
		err = ixgbe_setup_tc(dev, 0);
	पूर्ण

	वापस err ? 1 : 0;
पूर्ण

स्थिर काष्ठा dcbnl_rtnl_ops ixgbe_dcbnl_ops = अणु
	.ieee_getets	= ixgbe_dcbnl_ieee_getets,
	.ieee_setets	= ixgbe_dcbnl_ieee_setets,
	.ieee_getpfc	= ixgbe_dcbnl_ieee_getpfc,
	.ieee_setpfc	= ixgbe_dcbnl_ieee_setpfc,
	.ieee_setapp	= ixgbe_dcbnl_ieee_setapp,
	.ieee_delapp	= ixgbe_dcbnl_ieee_delapp,
	.माला_लोtate	= ixgbe_dcbnl_get_state,
	.setstate	= ixgbe_dcbnl_set_state,
	.getpermhwaddr	= ixgbe_dcbnl_get_perm_hw_addr,
	.setpgtccfgtx	= ixgbe_dcbnl_set_pg_tc_cfg_tx,
	.setpgbwgcfgtx	= ixgbe_dcbnl_set_pg_bwg_cfg_tx,
	.setpgtccfgrx	= ixgbe_dcbnl_set_pg_tc_cfg_rx,
	.setpgbwgcfgrx	= ixgbe_dcbnl_set_pg_bwg_cfg_rx,
	.getpgtccfgtx	= ixgbe_dcbnl_get_pg_tc_cfg_tx,
	.getpgbwgcfgtx	= ixgbe_dcbnl_get_pg_bwg_cfg_tx,
	.getpgtccfgrx	= ixgbe_dcbnl_get_pg_tc_cfg_rx,
	.getpgbwgcfgrx	= ixgbe_dcbnl_get_pg_bwg_cfg_rx,
	.setpfccfg	= ixgbe_dcbnl_set_pfc_cfg,
	.getpfccfg	= ixgbe_dcbnl_get_pfc_cfg,
	.setall		= ixgbe_dcbnl_set_all,
	.अ_लोap		= ixgbe_dcbnl_अ_लोap,
	.getnumtcs	= ixgbe_dcbnl_getnumtcs,
	.setnumtcs	= ixgbe_dcbnl_setnumtcs,
	.getpfcstate	= ixgbe_dcbnl_getpfcstate,
	.setpfcstate	= ixgbe_dcbnl_setpfcstate,
	.getapp		= ixgbe_dcbnl_getapp,
	.getdcbx	= ixgbe_dcbnl_getdcbx,
	.setdcbx	= ixgbe_dcbnl_setdcbx,
पूर्ण;
