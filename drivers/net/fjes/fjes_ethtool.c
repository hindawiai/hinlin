<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  FUJITSU Extended Socket Network Device driver
 *  Copyright (c) 2015 FUJITSU LIMITED
 */

/* ethtool support क्रम fjes */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "fjes.h"

काष्ठा fjes_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा FJES_STAT(name, stat) अणु \
	.stat_string = name, \
	.माप_stat = माप_field(काष्ठा fjes_adapter, stat), \
	.stat_offset = दुरत्व(काष्ठा fjes_adapter, stat) \
पूर्ण

अटल स्थिर काष्ठा fjes_stats fjes_gstrings_stats[] = अणु
	FJES_STAT("rx_packets", stats64.rx_packets),
	FJES_STAT("tx_packets", stats64.tx_packets),
	FJES_STAT("rx_bytes", stats64.rx_bytes),
	FJES_STAT("tx_bytes", stats64.rx_bytes),
	FJES_STAT("rx_dropped", stats64.rx_dropped),
	FJES_STAT("tx_dropped", stats64.tx_dropped),
पूर्ण;

#घोषणा FJES_EP_STATS_LEN 14
#घोषणा FJES_STATS_LEN \
	(ARRAY_SIZE(fjes_gstrings_stats) + \
	 ((&((काष्ठा fjes_adapter *)netdev_priv(netdev))->hw)->max_epid - 1) * \
	 FJES_EP_STATS_LEN)

अटल व्योम fjes_get_ethtool_stats(काष्ठा net_device *netdev,
				   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;
	पूर्णांक epidx;
	अक्षर *p;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fjes_gstrings_stats); i++) अणु
		p = (अक्षर *)adapter + fjes_gstrings_stats[i].stat_offset;
		data[i] = (fjes_gstrings_stats[i].माप_stat == माप(u64))
			? *(u64 *)p : *(u32 *)p;
	पूर्ण
	क्रम (epidx = 0; epidx < hw->max_epid; epidx++) अणु
		अगर (epidx == hw->my_epid)
			जारी;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.com_regist_buf_exec;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.com_unregist_buf_exec;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.send_पूर्णांकr_rx;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.send_पूर्णांकr_unshare;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.send_पूर्णांकr_zoneupdate;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.recv_पूर्णांकr_rx;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.recv_पूर्णांकr_unshare;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.recv_पूर्णांकr_stop;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.recv_पूर्णांकr_zoneupdate;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.tx_buffer_full;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dropped_not_shared;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dropped_ver_mismatch;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dropped_buf_size_mismatch;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dropped_vlanid_mismatch;
	पूर्ण
पूर्ण

अटल व्योम fjes_get_strings(काष्ठा net_device *netdev,
			     u32 stringset, u8 *data)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(fjes_gstrings_stats); i++) अणु
			स_नकल(p, fjes_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < hw->max_epid; i++) अणु
			अगर (i == hw->my_epid)
				जारी;
			प्र_लिखो(p, "ep%u_com_regist_buf_exec", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_com_unregist_buf_exec", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_send_intr_rx", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_send_intr_unshare", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_send_intr_zoneupdate", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_recv_intr_rx", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_recv_intr_unshare", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_recv_intr_stop", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_recv_intr_zoneupdate", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_tx_buffer_full", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_tx_dropped_not_shared", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_tx_dropped_ver_mismatch", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_tx_dropped_buf_size_mismatch", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "ep%u_tx_dropped_vlanid_mismatch", i);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक fjes_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस FJES_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम fjes_get_drvinfo(काष्ठा net_device *netdev,
			     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा platक्रमm_device *plat_dev;

	plat_dev = adapter->plat_dev;

	strlcpy(drvinfo->driver, fjes_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->version, fjes_driver_version,
		माप(drvinfo->version));

	strlcpy(drvinfo->fw_version, "none", माप(drvinfo->fw_version));
	snम_लिखो(drvinfo->bus_info, माप(drvinfo->bus_info),
		 "platform:%s", plat_dev->name);
पूर्ण

अटल पूर्णांक fjes_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *ecmd)
अणु
	ethtool_link_ksettings_zero_link_mode(ecmd, supported);
	ethtool_link_ksettings_zero_link_mode(ecmd, advertising);
	ecmd->base.duplex = DUPLEX_FULL;
	ecmd->base.स्वतःneg = AUTONEG_DISABLE;
	ecmd->base.port = PORT_NONE;
	ecmd->base.speed = 20000;	/* 20Gb/s */

	वापस 0;
पूर्ण

अटल पूर्णांक fjes_get_regs_len(काष्ठा net_device *netdev)
अणु
#घोषणा FJES_REGS_LEN	37
	वापस FJES_REGS_LEN * माप(u32);
पूर्ण

अटल व्योम fjes_get_regs(काष्ठा net_device *netdev,
			  काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;
	u32 *regs_buff = p;

	स_रखो(p, 0, FJES_REGS_LEN * माप(u32));

	regs->version = 1;

	/* Inक्रमmation रेजिस्टरs */
	regs_buff[0] = rd32(XSCT_OWNER_EPID);
	regs_buff[1] = rd32(XSCT_MAX_EP);

	/* Device Control रेजिस्टरs */
	regs_buff[4] = rd32(XSCT_DCTL);

	/* Command Control रेजिस्टरs */
	regs_buff[8] = rd32(XSCT_CR);
	regs_buff[9] = rd32(XSCT_CS);
	regs_buff[10] = rd32(XSCT_SHSTSAL);
	regs_buff[11] = rd32(XSCT_SHSTSAH);

	regs_buff[13] = rd32(XSCT_REQBL);
	regs_buff[14] = rd32(XSCT_REQBAL);
	regs_buff[15] = rd32(XSCT_REQBAH);

	regs_buff[17] = rd32(XSCT_RESPBL);
	regs_buff[18] = rd32(XSCT_RESPBAL);
	regs_buff[19] = rd32(XSCT_RESPBAH);

	/* Interrupt Control रेजिस्टरs */
	regs_buff[32] = rd32(XSCT_IS);
	regs_buff[33] = rd32(XSCT_IMS);
	regs_buff[34] = rd32(XSCT_IMC);
	regs_buff[35] = rd32(XSCT_IG);
	regs_buff[36] = rd32(XSCT_ICTL);
पूर्ण

अटल पूर्णांक fjes_set_dump(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;
	पूर्णांक ret = 0;

	अगर (dump->flag) अणु
		अगर (hw->debug_mode)
			वापस -EPERM;

		hw->debug_mode = dump->flag;

		/* enable debug mode */
		mutex_lock(&hw->hw_info.lock);
		ret = fjes_hw_start_debug(hw);
		mutex_unlock(&hw->hw_info.lock);

		अगर (ret)
			hw->debug_mode = 0;
	पूर्ण अन्यथा अणु
		अगर (!hw->debug_mode)
			वापस -EPERM;

		/* disable debug mode */
		mutex_lock(&hw->hw_info.lock);
		ret = fjes_hw_stop_debug(hw);
		mutex_unlock(&hw->hw_info.lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fjes_get_dump_flag(काष्ठा net_device *netdev,
			      काष्ठा ethtool_dump *dump)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;

	dump->len = hw->hw_info.trace_size;
	dump->version = 1;
	dump->flag = hw->debug_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक fjes_get_dump_data(काष्ठा net_device *netdev,
			      काष्ठा ethtool_dump *dump, व्योम *buf)
अणु
	काष्ठा fjes_adapter *adapter = netdev_priv(netdev);
	काष्ठा fjes_hw *hw = &adapter->hw;
	पूर्णांक ret = 0;

	अगर (hw->hw_info.trace)
		स_नकल(buf, hw->hw_info.trace, hw->hw_info.trace_size);
	अन्यथा
		ret = -EPERM;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops fjes_ethtool_ops = अणु
		.get_drvinfo		= fjes_get_drvinfo,
		.get_ethtool_stats = fjes_get_ethtool_stats,
		.get_strings      = fjes_get_strings,
		.get_sset_count   = fjes_get_sset_count,
		.get_regs		= fjes_get_regs,
		.get_regs_len		= fjes_get_regs_len,
		.set_dump		= fjes_set_dump,
		.get_dump_flag		= fjes_get_dump_flag,
		.get_dump_data		= fjes_get_dump_data,
		.get_link_ksettings	= fjes_get_link_ksettings,
पूर्ण;

व्योम fjes_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &fjes_ethtool_ops;
पूर्ण
