<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/pci.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_nic.h"
#समावेश "octeon_main.h"
#समावेश "octeon_network.h"
#समावेश "cn66xx_regs.h"
#समावेश "cn66xx_device.h"
#समावेश "cn23xx_pf_device.h"
#समावेश "cn23xx_vf_device.h"

अटल पूर्णांक lio_reset_queues(काष्ठा net_device *netdev, uपूर्णांक32_t num_qs);

काष्ठा oct_पूर्णांकrmod_resp अणु
	u64     rh;
	काष्ठा oct_पूर्णांकrmod_cfg पूर्णांकrmod;
	u64     status;
पूर्ण;

काष्ठा oct_mdio_cmd_resp अणु
	u64 rh;
	काष्ठा oct_mdio_cmd resp;
	u64 status;
पूर्ण;

#घोषणा OCT_MDIO45_RESP_SIZE   (माप(काष्ठा oct_mdio_cmd_resp))

/* Octeon's पूर्णांकerface mode of operation */
क्रमागत अणु
	INTERFACE_MODE_DISABLED,
	INTERFACE_MODE_RGMII,
	INTERFACE_MODE_GMII,
	INTERFACE_MODE_SPI,
	INTERFACE_MODE_PCIE,
	INTERFACE_MODE_XAUI,
	INTERFACE_MODE_SGMII,
	INTERFACE_MODE_PICMG,
	INTERFACE_MODE_NPI,
	INTERFACE_MODE_LOOP,
	INTERFACE_MODE_SRIO,
	INTERFACE_MODE_ILK,
	INTERFACE_MODE_RXAUI,
	INTERFACE_MODE_QSGMII,
	INTERFACE_MODE_AGL,
	INTERFACE_MODE_XLAUI,
	INTERFACE_MODE_XFI,
	INTERFACE_MODE_10G_KR,
	INTERFACE_MODE_40G_KR4,
	INTERFACE_MODE_MIXED,
पूर्ण;

#घोषणा OCT_ETHTOOL_REGDUMP_LEN  4096
#घोषणा OCT_ETHTOOL_REGDUMP_LEN_23XX  (4096 * 11)
#घोषणा OCT_ETHTOOL_REGDUMP_LEN_23XX_VF  (4096 * 2)
#घोषणा OCT_ETHTOOL_REGSVER  1

/* statistics of PF */
अटल स्थिर अक्षर oct_stats_strings[][ETH_GSTRING_LEN] = अणु
	"rx_packets",
	"tx_packets",
	"rx_bytes",
	"tx_bytes",
	"rx_errors",
	"tx_errors",
	"rx_dropped",
	"tx_dropped",

	"tx_total_sent",
	"tx_total_fwd",
	"tx_err_pko",
	"tx_err_pki",
	"tx_err_link",
	"tx_err_drop",

	"tx_tso",
	"tx_tso_packets",
	"tx_tso_err",
	"tx_vxlan",

	"tx_mcast",
	"tx_bcast",

	"mac_tx_total_pkts",
	"mac_tx_total_bytes",
	"mac_tx_mcast_pkts",
	"mac_tx_bcast_pkts",
	"mac_tx_ctl_packets",
	"mac_tx_total_collisions",
	"mac_tx_one_collision",
	"mac_tx_multi_collision",
	"mac_tx_max_collision_fail",
	"mac_tx_max_deferral_fail",
	"mac_tx_fifo_err",
	"mac_tx_runts",

	"rx_total_rcvd",
	"rx_total_fwd",
	"rx_mcast",
	"rx_bcast",
	"rx_jabber_err",
	"rx_l2_err",
	"rx_frame_err",
	"rx_err_pko",
	"rx_err_link",
	"rx_err_drop",

	"rx_vxlan",
	"rx_vxlan_err",

	"rx_lro_pkts",
	"rx_lro_bytes",
	"rx_total_lro",

	"rx_lro_aborts",
	"rx_lro_aborts_port",
	"rx_lro_aborts_seq",
	"rx_lro_aborts_tsval",
	"rx_lro_aborts_timer",
	"rx_fwd_rate",

	"mac_rx_total_rcvd",
	"mac_rx_bytes",
	"mac_rx_total_bcst",
	"mac_rx_total_mcst",
	"mac_rx_runts",
	"mac_rx_ctl_packets",
	"mac_rx_fifo_err",
	"mac_rx_dma_drop",
	"mac_rx_fcs_err",

	"link_state_changes",
पूर्ण;

/* statistics of VF */
अटल स्थिर अक्षर oct_vf_stats_strings[][ETH_GSTRING_LEN] = अणु
	"rx_packets",
	"tx_packets",
	"rx_bytes",
	"tx_bytes",
	"rx_errors",
	"tx_errors",
	"rx_dropped",
	"tx_dropped",
	"rx_mcast",
	"tx_mcast",
	"rx_bcast",
	"tx_bcast",
	"link_state_changes",
पूर्ण;

/* statistics of host tx queue */
अटल स्थिर अक्षर oct_iq_stats_strings[][ETH_GSTRING_LEN] = अणु
	"packets",
	"bytes",
	"dropped",
	"iq_busy",
	"sgentry_sent",

	"fw_instr_posted",
	"fw_instr_processed",
	"fw_instr_dropped",
	"fw_bytes_sent",

	"tso",
	"vxlan",
	"txq_restart",
पूर्ण;

/* statistics of host rx queue */
अटल स्थिर अक्षर oct_droq_stats_strings[][ETH_GSTRING_LEN] = अणु
	"packets",
	"bytes",
	"dropped",
	"dropped_nomem",
	"dropped_toomany",
	"fw_dropped",
	"fw_pkts_received",
	"fw_bytes_received",
	"fw_dropped_nodispatch",

	"vxlan",
	"buffer_alloc_failure",
पूर्ण;

/* LiquidIO driver निजी flags */
अटल स्थिर अक्षर oct_priv_flags_strings[][ETH_GSTRING_LEN] = अणु
पूर्ण;

#घोषणा OCTNIC_NCMD_AUTONEG_ON  0x1
#घोषणा OCTNIC_NCMD_PHY_ON      0x2

अटल पूर्णांक lio_get_link_ksettings(काष्ठा net_device *netdev,
				  काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा oct_link_info *linfo;

	linfo = &lio->linfo;

	ethtool_link_ksettings_zero_link_mode(ecmd, supported);
	ethtool_link_ksettings_zero_link_mode(ecmd, advertising);

	चयन (linfo->link.s.phy_type) अणु
	हाल LIO_PHY_PORT_TP:
		ecmd->base.port = PORT_TP;
		ecmd->base.स्वतःneg = AUTONEG_DISABLE;
		ethtool_link_ksettings_add_link_mode(ecmd, supported, TP);
		ethtool_link_ksettings_add_link_mode(ecmd, supported, Pause);
		ethtool_link_ksettings_add_link_mode(ecmd, supported,
						     10000baseT_Full);

		ethtool_link_ksettings_add_link_mode(ecmd, advertising, Pause);
		ethtool_link_ksettings_add_link_mode(ecmd, advertising,
						     10000baseT_Full);

		अवरोध;

	हाल LIO_PHY_PORT_FIBRE:
		अगर (linfo->link.s.अगर_mode == INTERFACE_MODE_XAUI ||
		    linfo->link.s.अगर_mode == INTERFACE_MODE_RXAUI ||
		    linfo->link.s.अगर_mode == INTERFACE_MODE_XLAUI ||
		    linfo->link.s.अगर_mode == INTERFACE_MODE_XFI) अणु
			dev_dbg(&oct->pci_dev->dev, "ecmd->base.transceiver is XCVR_EXTERNAL\n");
			ecmd->base.transceiver = XCVR_EXTERNAL;
		पूर्ण अन्यथा अणु
			dev_err(&oct->pci_dev->dev, "Unknown link interface mode: %d\n",
				linfo->link.s.अगर_mode);
		पूर्ण

		ecmd->base.port = PORT_FIBRE;
		ecmd->base.स्वतःneg = AUTONEG_DISABLE;
		ethtool_link_ksettings_add_link_mode(ecmd, supported, FIBRE);

		ethtool_link_ksettings_add_link_mode(ecmd, supported, Pause);
		ethtool_link_ksettings_add_link_mode(ecmd, advertising, Pause);
		अगर (oct->subप्रणाली_id == OCTEON_CN2350_25GB_SUBSYS_ID ||
		    oct->subप्रणाली_id == OCTEON_CN2360_25GB_SUBSYS_ID) अणु
			अगर (OCTEON_CN23XX_PF(oct)) अणु
				ethtool_link_ksettings_add_link_mode
					(ecmd, supported, 25000baseSR_Full);
				ethtool_link_ksettings_add_link_mode
					(ecmd, supported, 25000baseKR_Full);
				ethtool_link_ksettings_add_link_mode
					(ecmd, supported, 25000baseCR_Full);

				अगर (oct->no_speed_setting == 0)  अणु
					ethtool_link_ksettings_add_link_mode
						(ecmd, supported,
						 10000baseSR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, supported,
						 10000baseKR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, supported,
						 10000baseCR_Full);
				पूर्ण

				अगर (oct->no_speed_setting == 0) अणु
					liquidio_get_speed(lio);
					liquidio_get_fec(lio);
				पूर्ण अन्यथा अणु
					oct->speed_setting = 25;
				पूर्ण

				अगर (oct->speed_setting == 10) अणु
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 10000baseSR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 10000baseKR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 10000baseCR_Full);
				पूर्ण
				अगर (oct->speed_setting == 25) अणु
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 25000baseSR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 25000baseKR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 25000baseCR_Full);
				पूर्ण

				अगर (oct->no_speed_setting)
					अवरोध;

				ethtool_link_ksettings_add_link_mode
					(ecmd, supported, FEC_RS);
				ethtool_link_ksettings_add_link_mode
					(ecmd, supported, FEC_NONE);
					/*FEC_OFF*/
				अगर (oct->props[lio->अगरidx].fec == 1) अणु
					/* ETHTOOL_FEC_RS */
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising, FEC_RS);
				पूर्ण अन्यथा अणु
					/* ETHTOOL_FEC_OFF */
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising, FEC_NONE);
				पूर्ण
			पूर्ण अन्यथा अणु /* VF */
				अगर (linfo->link.s.speed == 10000) अणु
					ethtool_link_ksettings_add_link_mode
						(ecmd, supported,
						 10000baseSR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, supported,
						 10000baseKR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, supported,
						 10000baseCR_Full);

					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 10000baseSR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 10000baseKR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 10000baseCR_Full);
				पूर्ण

				अगर (linfo->link.s.speed == 25000) अणु
					ethtool_link_ksettings_add_link_mode
						(ecmd, supported,
						 25000baseSR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, supported,
						 25000baseKR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, supported,
						 25000baseCR_Full);

					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 25000baseSR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 25000baseKR_Full);
					ethtool_link_ksettings_add_link_mode
						(ecmd, advertising,
						 25000baseCR_Full);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			ethtool_link_ksettings_add_link_mode(ecmd, supported,
							     10000baseT_Full);
			ethtool_link_ksettings_add_link_mode(ecmd, advertising,
							     10000baseT_Full);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (linfo->link.s.link_up) अणु
		ecmd->base.speed = linfo->link.s.speed;
		ecmd->base.duplex = linfo->link.s.duplex;
	पूर्ण अन्यथा अणु
		ecmd->base.speed = SPEED_UNKNOWN;
		ecmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lio_set_link_ksettings(काष्ठा net_device *netdev,
				  स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	स्थिर पूर्णांक speed = ecmd->base.speed;
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा oct_link_info *linfo;
	काष्ठा octeon_device *oct;

	oct = lio->oct_dev;

	linfo = &lio->linfo;

	अगर (!(oct->subप्रणाली_id == OCTEON_CN2350_25GB_SUBSYS_ID ||
	      oct->subप्रणाली_id == OCTEON_CN2360_25GB_SUBSYS_ID))
		वापस -EOPNOTSUPP;

	अगर (oct->no_speed_setting) अणु
		dev_err(&oct->pci_dev->dev, "%s: Changing speed is not supported\n",
			__func__);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((ecmd->base.duplex != DUPLEX_UNKNOWN &&
	     ecmd->base.duplex != linfo->link.s.duplex) ||
	     ecmd->base.स्वतःneg != AUTONEG_DISABLE ||
	    (ecmd->base.speed != 10000 && ecmd->base.speed != 25000 &&
	     ecmd->base.speed != SPEED_UNKNOWN))
		वापस -EOPNOTSUPP;

	अगर ((oct->speed_boot == speed / 1000) &&
	    oct->speed_boot == oct->speed_setting)
		वापस 0;

	liquidio_set_speed(lio, speed / 1000);

	dev_dbg(&oct->pci_dev->dev, "Port speed is set to %dG\n",
		oct->speed_setting);

	वापस 0;
पूर्ण

अटल व्योम
lio_get_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा lio *lio;
	काष्ठा octeon_device *oct;

	lio = GET_LIO(netdev);
	oct = lio->oct_dev;

	स_रखो(drvinfo, 0, माप(काष्ठा ethtool_drvinfo));
	म_नकल(drvinfo->driver, "liquidio");
	म_नकलन(drvinfo->fw_version, oct->fw_info.liquidio_firmware_version,
		ETHTOOL_FWVERS_LEN);
	म_नकलन(drvinfo->bus_info, pci_name(oct->pci_dev), 32);
पूर्ण

अटल व्योम
lio_get_vf_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा octeon_device *oct;
	काष्ठा lio *lio;

	lio = GET_LIO(netdev);
	oct = lio->oct_dev;

	स_रखो(drvinfo, 0, माप(काष्ठा ethtool_drvinfo));
	म_नकल(drvinfo->driver, "liquidio_vf");
	म_नकलन(drvinfo->fw_version, oct->fw_info.liquidio_firmware_version,
		ETHTOOL_FWVERS_LEN);
	म_नकलन(drvinfo->bus_info, pci_name(oct->pci_dev), 32);
पूर्ण

अटल पूर्णांक
lio_send_queue_count_update(काष्ठा net_device *netdev, uपूर्णांक32_t num_queues)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_QUEUE_COUNT_CTL;
	nctrl.ncmd.s.param1 = num_queues;
	nctrl.ncmd.s.param2 = num_queues;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "Failed to send Queue reset command (ret: 0x%x)\n",
			ret);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
lio_ethtool_get_channels(काष्ठा net_device *dev,
			 काष्ठा ethtool_channels *channel)
अणु
	काष्ठा lio *lio = GET_LIO(dev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	u32 max_rx = 0, max_tx = 0, tx_count = 0, rx_count = 0;
	u32 combined_count = 0, max_combined = 0;

	अगर (OCTEON_CN6XXX(oct)) अणु
		काष्ठा octeon_config *conf6x = CHIP_CONF(oct, cn6xxx);

		max_rx = CFG_GET_OQ_MAX_Q(conf6x);
		max_tx = CFG_GET_IQ_MAX_Q(conf6x);
		rx_count = CFG_GET_NUM_RXQS_NIC_IF(conf6x, lio->अगरidx);
		tx_count = CFG_GET_NUM_TXQS_NIC_IF(conf6x, lio->अगरidx);
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_PF(oct)) अणु
		अगर (oct->sriov_info.sriov_enabled) अणु
			max_combined = lio->linfo.num_txpciq;
		पूर्ण अन्यथा अणु
			काष्ठा octeon_config *conf23_pf =
				CHIP_CONF(oct, cn23xx_pf);

			max_combined = CFG_GET_IQ_MAX_Q(conf23_pf);
		पूर्ण
		combined_count = oct->num_iqs;
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_VF(oct)) अणु
		u64 reg_val = 0ULL;
		u64 ctrl = CN23XX_VF_SLI_IQ_PKT_CONTROL64(0);

		reg_val = octeon_पढ़ो_csr64(oct, ctrl);
		reg_val = reg_val >> CN23XX_PKT_INPUT_CTL_RPVF_POS;
		max_combined = reg_val & CN23XX_PKT_INPUT_CTL_RPVF_MASK;
		combined_count = oct->num_iqs;
	पूर्ण

	channel->max_rx = max_rx;
	channel->max_tx = max_tx;
	channel->max_combined = max_combined;
	channel->rx_count = rx_count;
	channel->tx_count = tx_count;
	channel->combined_count = combined_count;
पूर्ण

अटल पूर्णांक
lio_irq_पुनः_स्मृतिate_irqs(काष्ठा octeon_device *oct, uपूर्णांक32_t num_ioqs)
अणु
	काष्ठा msix_entry *msix_entries;
	पूर्णांक num_msix_irqs = 0;
	पूर्णांक i;

	अगर (!oct->msix_on)
		वापस 0;

	/* Disable the input and output queues now. No more packets will
	 * arrive from Octeon.
	 */
	oct->fn_list.disable_पूर्णांकerrupt(oct, OCTEON_ALL_INTR);

	अगर (oct->msix_on) अणु
		अगर (OCTEON_CN23XX_PF(oct))
			num_msix_irqs = oct->num_msix_irqs - 1;
		अन्यथा अगर (OCTEON_CN23XX_VF(oct))
			num_msix_irqs = oct->num_msix_irqs;

		msix_entries = (काष्ठा msix_entry *)oct->msix_entries;
		क्रम (i = 0; i < num_msix_irqs; i++) अणु
			अगर (oct->ioq_vector[i].vector) अणु
				/* clear the affinity_cpumask */
				irq_set_affinity_hपूर्णांक(msix_entries[i].vector,
						      शून्य);
				मुक्त_irq(msix_entries[i].vector,
					 &oct->ioq_vector[i]);
				oct->ioq_vector[i].vector = 0;
			पूर्ण
		पूर्ण

		/* non-iov vector's argument is oct काष्ठा */
		अगर (OCTEON_CN23XX_PF(oct))
			मुक्त_irq(msix_entries[i].vector, oct);

		pci_disable_msix(oct->pci_dev);
		kमुक्त(oct->msix_entries);
		oct->msix_entries = शून्य;
	पूर्ण

	kमुक्त(oct->irq_name_storage);
	oct->irq_name_storage = शून्य;

	अगर (octeon_allocate_ioq_vector(oct, num_ioqs)) अणु
		dev_err(&oct->pci_dev->dev, "OCTEON: ioq vector allocation failed\n");
		वापस -1;
	पूर्ण

	अगर (octeon_setup_पूर्णांकerrupt(oct, num_ioqs)) अणु
		dev_info(&oct->pci_dev->dev, "Setup interrupt failed\n");
		वापस -1;
	पूर्ण

	/* Enable Octeon device पूर्णांकerrupts */
	oct->fn_list.enable_पूर्णांकerrupt(oct, OCTEON_ALL_INTR);

	वापस 0;
पूर्ण

अटल पूर्णांक
lio_ethtool_set_channels(काष्ठा net_device *dev,
			 काष्ठा ethtool_channels *channel)
अणु
	u32 combined_count, max_combined;
	काष्ठा lio *lio = GET_LIO(dev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	पूर्णांक stopped = 0;

	अगर (म_भेद(oct->fw_info.liquidio_firmware_version, "1.6.1") < 0) अणु
		dev_err(&oct->pci_dev->dev, "Minimum firmware version required is 1.6.1\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!channel->combined_count || channel->other_count ||
	    channel->rx_count || channel->tx_count)
		वापस -EINVAL;

	combined_count = channel->combined_count;

	अगर (OCTEON_CN23XX_PF(oct)) अणु
		अगर (oct->sriov_info.sriov_enabled) अणु
			max_combined = lio->linfo.num_txpciq;
		पूर्ण अन्यथा अणु
			काष्ठा octeon_config *conf23_pf =
				CHIP_CONF(oct,
					  cn23xx_pf);

			max_combined =
				CFG_GET_IQ_MAX_Q(conf23_pf);
		पूर्ण
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_VF(oct)) अणु
		u64 reg_val = 0ULL;
		u64 ctrl = CN23XX_VF_SLI_IQ_PKT_CONTROL64(0);

		reg_val = octeon_पढ़ो_csr64(oct, ctrl);
		reg_val = reg_val >> CN23XX_PKT_INPUT_CTL_RPVF_POS;
		max_combined = reg_val & CN23XX_PKT_INPUT_CTL_RPVF_MASK;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (combined_count > max_combined || combined_count < 1)
		वापस -EINVAL;

	अगर (combined_count == oct->num_iqs)
		वापस 0;

	अगरstate_set(lio, LIO_IFSTATE_RESETTING);

	अगर (netअगर_running(dev)) अणु
		dev->netdev_ops->nकरो_stop(dev);
		stopped = 1;
	पूर्ण

	अगर (lio_reset_queues(dev, combined_count))
		वापस -EINVAL;

	अगर (stopped)
		dev->netdev_ops->nकरो_खोलो(dev);

	अगरstate_reset(lio, LIO_IFSTATE_RESETTING);

	वापस 0;
पूर्ण

अटल पूर्णांक lio_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	u8 buf[192];
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	काष्ठा octeon_board_info *board_info;
	पूर्णांक len;

	board_info = (काष्ठा octeon_board_info *)(&oct_dev->boardinfo);
	len = प्र_लिखो(buf, "boardname:%s serialnum:%s maj:%lld min:%lld\n",
		      board_info->name, board_info->serial_number,
		      board_info->major, board_info->minor);

	वापस len;
पूर्ण

अटल पूर्णांक
lio_get_eeprom(काष्ठा net_device *netdev, काष्ठा ethtool_eeprom *eeprom,
	       u8 *bytes)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	काष्ठा octeon_board_info *board_info;

	अगर (eeprom->offset)
		वापस -EINVAL;

	eeprom->magic = oct_dev->pci_dev->venकरोr;
	board_info = (काष्ठा octeon_board_info *)(&oct_dev->boardinfo);
	प्र_लिखो((अक्षर *)bytes,
		"boardname:%s serialnum:%s maj:%lld min:%lld\n",
		board_info->name, board_info->serial_number,
		board_info->major, board_info->minor);

	वापस 0;
पूर्ण

अटल पूर्णांक octnet_gpio_access(काष्ठा net_device *netdev, पूर्णांक addr, पूर्णांक val)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_GPIO_ACCESS;
	nctrl.ncmd.s.param1 = addr;
	nctrl.ncmd.s.param2 = val;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev,
			"Failed to configure gpio value, ret=%d\n", ret);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक octnet_id_active(काष्ठा net_device *netdev, पूर्णांक val)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_ID_ACTIVE;
	nctrl.ncmd.s.param1 = val;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev,
			"Failed to configure gpio value, ret=%d\n", ret);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* This routine provides PHY access routines क्रम
 * mdio  clause45 .
 */
अटल पूर्णांक
octnet_mdio45_access(काष्ठा lio *lio, पूर्णांक op, पूर्णांक loc, पूर्णांक *value)
अणु
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	काष्ठा octeon_soft_command *sc;
	काष्ठा oct_mdio_cmd_resp *mdio_cmd_rsp;
	काष्ठा oct_mdio_cmd *mdio_cmd;
	पूर्णांक retval = 0;

	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct_dev,
					  माप(काष्ठा oct_mdio_cmd),
					  माप(काष्ठा oct_mdio_cmd_resp), 0);

	अगर (!sc)
		वापस -ENOMEM;

	mdio_cmd_rsp = (काष्ठा oct_mdio_cmd_resp *)sc->virtrptr;
	mdio_cmd = (काष्ठा oct_mdio_cmd *)sc->virtdptr;

	mdio_cmd->op = op;
	mdio_cmd->mdio_addr = loc;
	अगर (op)
		mdio_cmd->value1 = *value;
	octeon_swap_8B_data((u64 *)mdio_cmd, माप(काष्ठा oct_mdio_cmd) / 8);

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct_dev, sc, OPCODE_NIC, OPCODE_NIC_MDIO45,
				    0, 0, 0);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	retval = octeon_send_soft_command(oct_dev, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		dev_err(&oct_dev->pci_dev->dev,
			"octnet_mdio45_access instruction failed status: %x\n",
			retval);
		octeon_मुक्त_soft_command(oct_dev, sc);
		वापस -EBUSY;
	पूर्ण अन्यथा अणु
		/* Sleep on a रुको queue till the cond flag indicates that the
		 * response arrived
		 */
		retval = रुको_क्रम_sc_completion_समयout(oct_dev, sc, 0);
		अगर (retval)
			वापस retval;

		retval = mdio_cmd_rsp->status;
		अगर (retval) अणु
			dev_err(&oct_dev->pci_dev->dev,
				"octnet mdio45 access failed: %x\n", retval);
			WRITE_ONCE(sc->caller_is_करोne, true);
			वापस -EBUSY;
		पूर्ण

		octeon_swap_8B_data((u64 *)(&mdio_cmd_rsp->resp),
				    माप(काष्ठा oct_mdio_cmd) / 8);

		अगर (!op)
			*value = mdio_cmd_rsp->resp.value1;

		WRITE_ONCE(sc->caller_is_करोne, true);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक lio_set_phys_id(काष्ठा net_device *netdev,
			   क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा oct_link_info *linfo;
	पूर्णांक value, ret;
	u32 cur_ver;

	linfo = &lio->linfo;
	cur_ver = OCT_FW_VER(oct->fw_info.ver.maj,
			     oct->fw_info.ver.min,
			     oct->fw_info.ver.rev);

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		अगर (oct->chip_id == OCTEON_CN66XX) अणु
			octnet_gpio_access(netdev, VITESSE_PHY_GPIO_CFG,
					   VITESSE_PHY_GPIO_DRIVEON);
			वापस 2;

		पूर्ण अन्यथा अगर (oct->chip_id == OCTEON_CN68XX) अणु
			/* Save the current LED settings */
			ret = octnet_mdio45_access(lio, 0,
						   LIO68XX_LED_BEACON_ADDR,
						   &lio->phy_beacon_val);
			अगर (ret)
				वापस ret;

			ret = octnet_mdio45_access(lio, 0,
						   LIO68XX_LED_CTRL_ADDR,
						   &lio->led_ctrl_val);
			अगर (ret)
				वापस ret;

			/* Configure Beacon values */
			value = LIO68XX_LED_BEACON_CFGON;
			ret = octnet_mdio45_access(lio, 1,
						   LIO68XX_LED_BEACON_ADDR,
						   &value);
			अगर (ret)
				वापस ret;

			value = LIO68XX_LED_CTRL_CFGON;
			ret = octnet_mdio45_access(lio, 1,
						   LIO68XX_LED_CTRL_ADDR,
						   &value);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर (oct->chip_id == OCTEON_CN23XX_PF_VID) अणु
			octnet_id_active(netdev, LED_IDENTIFICATION_ON);
			अगर (linfo->link.s.phy_type == LIO_PHY_PORT_TP &&
			    cur_ver > OCT_FW_VER(1, 7, 2))
				वापस 2;
			अन्यथा
				वापस 0;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल ETHTOOL_ID_ON:
		अगर (oct->chip_id == OCTEON_CN23XX_PF_VID &&
		    linfo->link.s.phy_type == LIO_PHY_PORT_TP &&
		    cur_ver > OCT_FW_VER(1, 7, 2))
			octnet_id_active(netdev, LED_IDENTIFICATION_ON);
		अन्यथा अगर (oct->chip_id == OCTEON_CN66XX)
			octnet_gpio_access(netdev, VITESSE_PHY_GPIO_CFG,
					   VITESSE_PHY_GPIO_HIGH);
		अन्यथा
			वापस -EINVAL;

		अवरोध;

	हाल ETHTOOL_ID_OFF:
		अगर (oct->chip_id == OCTEON_CN23XX_PF_VID &&
		    linfo->link.s.phy_type == LIO_PHY_PORT_TP &&
		    cur_ver > OCT_FW_VER(1, 7, 2))
			octnet_id_active(netdev, LED_IDENTIFICATION_OFF);
		अन्यथा अगर (oct->chip_id == OCTEON_CN66XX)
			octnet_gpio_access(netdev, VITESSE_PHY_GPIO_CFG,
					   VITESSE_PHY_GPIO_LOW);
		अन्यथा
			वापस -EINVAL;

		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		अगर (oct->chip_id == OCTEON_CN66XX) अणु
			octnet_gpio_access(netdev, VITESSE_PHY_GPIO_CFG,
					   VITESSE_PHY_GPIO_DRIVखातापूर्णF);
		पूर्ण अन्यथा अगर (oct->chip_id == OCTEON_CN68XX) अणु
			/* Restore LED settings */
			ret = octnet_mdio45_access(lio, 1,
						   LIO68XX_LED_CTRL_ADDR,
						   &lio->led_ctrl_val);
			अगर (ret)
				वापस ret;

			ret = octnet_mdio45_access(lio, 1,
						   LIO68XX_LED_BEACON_ADDR,
						   &lio->phy_beacon_val);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर (oct->chip_id == OCTEON_CN23XX_PF_VID) अणु
			octnet_id_active(netdev, LED_IDENTIFICATION_OFF);

			वापस 0;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
lio_ethtool_get_ringparam(काष्ठा net_device *netdev,
			  काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	u32 tx_max_pending = 0, rx_max_pending = 0, tx_pending = 0,
	    rx_pending = 0;

	अगर (अगरstate_check(lio, LIO_IFSTATE_RESETTING))
		वापस;

	अगर (OCTEON_CN6XXX(oct)) अणु
		काष्ठा octeon_config *conf6x = CHIP_CONF(oct, cn6xxx);

		tx_max_pending = CN6XXX_MAX_IQ_DESCRIPTORS;
		rx_max_pending = CN6XXX_MAX_OQ_DESCRIPTORS;
		rx_pending = CFG_GET_NUM_RX_DESCS_NIC_IF(conf6x, lio->अगरidx);
		tx_pending = CFG_GET_NUM_TX_DESCS_NIC_IF(conf6x, lio->अगरidx);
	पूर्ण अन्यथा अगर (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct)) अणु
		tx_max_pending = CN23XX_MAX_IQ_DESCRIPTORS;
		rx_max_pending = CN23XX_MAX_OQ_DESCRIPTORS;
		rx_pending = oct->droq[0]->max_count;
		tx_pending = oct->instr_queue[0]->max_count;
	पूर्ण

	ering->tx_pending = tx_pending;
	ering->tx_max_pending = tx_max_pending;
	ering->rx_pending = rx_pending;
	ering->rx_max_pending = rx_max_pending;
	ering->rx_mini_pending = 0;
	ering->rx_jumbo_pending = 0;
	ering->rx_mini_max_pending = 0;
	ering->rx_jumbo_max_pending = 0;
पूर्ण

अटल पूर्णांक lio_23xx_reconfigure_queue_count(काष्ठा lio *lio)
अणु
	काष्ठा octeon_device *oct = lio->oct_dev;
	u32 resp_size, data_size;
	काष्ठा liquidio_अगर_cfg_resp *resp;
	काष्ठा octeon_soft_command *sc;
	जोड़ oct_nic_अगर_cfg अगर_cfg;
	काष्ठा lio_version *vdata;
	u32 अगरidx_or_pfnum;
	पूर्णांक retval;
	पूर्णांक j;

	resp_size = माप(काष्ठा liquidio_अगर_cfg_resp);
	data_size = माप(काष्ठा lio_version);
	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct, data_size,
					  resp_size, 0);
	अगर (!sc) अणु
		dev_err(&oct->pci_dev->dev, "%s: Failed to allocate soft command\n",
			__func__);
		वापस -1;
	पूर्ण

	resp = (काष्ठा liquidio_अगर_cfg_resp *)sc->virtrptr;
	vdata = (काष्ठा lio_version *)sc->virtdptr;

	vdata->major = (__क्रमce u16)cpu_to_be16(LIQUIDIO_BASE_MAJOR_VERSION);
	vdata->minor = (__क्रमce u16)cpu_to_be16(LIQUIDIO_BASE_MINOR_VERSION);
	vdata->micro = (__क्रमce u16)cpu_to_be16(LIQUIDIO_BASE_MICRO_VERSION);

	अगरidx_or_pfnum = oct->pf_num;

	अगर_cfg.u64 = 0;
	अगर_cfg.s.num_iqueues = oct->sriov_info.num_pf_rings;
	अगर_cfg.s.num_oqueues = oct->sriov_info.num_pf_rings;
	अगर_cfg.s.base_queue = oct->sriov_info.pf_srn;
	अगर_cfg.s.gmx_port_id = oct->pf_num;

	sc->iq_no = 0;
	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_QCOUNT_UPDATE, 0,
				    अगर_cfg.u64, 0);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	retval = octeon_send_soft_command(oct, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		dev_err(&oct->pci_dev->dev,
			"Sending iq/oq config failed status: %x\n",
			retval);
		octeon_मुक्त_soft_command(oct, sc);
		वापस -EIO;
	पूर्ण

	retval = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
	अगर (retval)
		वापस retval;

	retval = resp->status;
	अगर (retval) अणु
		dev_err(&oct->pci_dev->dev,
			"iq/oq config failed: %x\n", retval);
		WRITE_ONCE(sc->caller_is_करोne, true);
		वापस -1;
	पूर्ण

	octeon_swap_8B_data((u64 *)(&resp->cfg_info),
			    (माप(काष्ठा liquidio_अगर_cfg_info)) >> 3);

	lio->अगरidx = अगरidx_or_pfnum;
	lio->linfo.num_rxpciq = hweight64(resp->cfg_info.iqmask);
	lio->linfo.num_txpciq = hweight64(resp->cfg_info.iqmask);
	क्रम (j = 0; j < lio->linfo.num_rxpciq; j++) अणु
		lio->linfo.rxpciq[j].u64 =
			resp->cfg_info.linfo.rxpciq[j].u64;
	पूर्ण

	क्रम (j = 0; j < lio->linfo.num_txpciq; j++) अणु
		lio->linfo.txpciq[j].u64 =
			resp->cfg_info.linfo.txpciq[j].u64;
	पूर्ण

	lio->linfo.hw_addr = resp->cfg_info.linfo.hw_addr;
	lio->linfo.gmxport = resp->cfg_info.linfo.gmxport;
	lio->linfo.link.u64 = resp->cfg_info.linfo.link.u64;
	lio->txq = lio->linfo.txpciq[0].s.q_no;
	lio->rxq = lio->linfo.rxpciq[0].s.q_no;

	dev_info(&oct->pci_dev->dev, "Queue count updated to %d\n",
		 lio->linfo.num_rxpciq);

	WRITE_ONCE(sc->caller_is_करोne, true);

	वापस 0;
पूर्ण

अटल पूर्णांक lio_reset_queues(काष्ठा net_device *netdev, uपूर्णांक32_t num_qs)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	पूर्णांक i, queue_count_update = 0;
	काष्ठा napi_काष्ठा *napi, *n;
	पूर्णांक ret;

	schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(100));

	अगर (रुको_क्रम_pending_requests(oct))
		dev_err(&oct->pci_dev->dev, "There were pending requests\n");

	अगर (lio_रुको_क्रम_instr_fetch(oct))
		dev_err(&oct->pci_dev->dev, "IQ had pending instructions\n");

	अगर (octeon_set_io_queues_off(oct)) अणु
		dev_err(&oct->pci_dev->dev, "Setting io queues off failed\n");
		वापस -1;
	पूर्ण

	/* Disable the input and output queues now. No more packets will
	 * arrive from Octeon.
	 */
	oct->fn_list.disable_io_queues(oct);
	/* Delete NAPI */
	list_क्रम_each_entry_safe(napi, n, &netdev->napi_list, dev_list)
		netअगर_napi_del(napi);

	अगर (num_qs != oct->num_iqs) अणु
		ret = netअगर_set_real_num_rx_queues(netdev, num_qs);
		अगर (ret) अणु
			dev_err(&oct->pci_dev->dev,
				"Setting real number rx failed\n");
			वापस ret;
		पूर्ण

		ret = netअगर_set_real_num_tx_queues(netdev, num_qs);
		अगर (ret) अणु
			dev_err(&oct->pci_dev->dev,
				"Setting real number tx failed\n");
			वापस ret;
		पूर्ण

		/* The value of queue_count_update decides whether it is the
		 * queue count or the descriptor count that is being
		 * re-configured.
		 */
		queue_count_update = 1;
	पूर्ण

	/* Re-configuration of queues can happen in two scenarios, SRIOV enabled
	 * and SRIOV disabled. Few things like recreating queue zero, resetting
	 * glists and IRQs are required क्रम both. For the latter, some more
	 * steps like updating sriov_info क्रम the octeon device need to be करोne.
	 */
	अगर (queue_count_update) अणु
		cleanup_rx_oom_poll_fn(netdev);

		lio_delete_glists(lio);

		/* Delete mbox क्रम PF which is SRIOV disabled because sriov_info
		 * will be now changed.
		 */
		अगर ((OCTEON_CN23XX_PF(oct)) && !oct->sriov_info.sriov_enabled)
			oct->fn_list.मुक्त_mbox(oct);
	पूर्ण

	क्रम (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct); i++) अणु
		अगर (!(oct->io_qmask.oq & BIT_ULL(i)))
			जारी;
		octeon_delete_droq(oct, i);
	पूर्ण

	क्रम (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) अणु
		अगर (!(oct->io_qmask.iq & BIT_ULL(i)))
			जारी;
		octeon_delete_instr_queue(oct, i);
	पूर्ण

	अगर (queue_count_update) अणु
		/* For PF re-configure sriov related inक्रमmation */
		अगर ((OCTEON_CN23XX_PF(oct)) &&
		    !oct->sriov_info.sriov_enabled) अणु
			oct->sriov_info.num_pf_rings = num_qs;
			अगर (cn23xx_sriov_config(oct)) अणु
				dev_err(&oct->pci_dev->dev,
					"Queue reset aborted: SRIOV config failed\n");
				वापस -1;
			पूर्ण

			num_qs = oct->sriov_info.num_pf_rings;
		पूर्ण
	पूर्ण

	अगर (oct->fn_list.setup_device_regs(oct)) अणु
		dev_err(&oct->pci_dev->dev, "Failed to configure device registers\n");
		वापस -1;
	पूर्ण

	/* The following are needed in हाल of queue count re-configuration and
	 * not क्रम descriptor count re-configuration.
	 */
	अगर (queue_count_update) अणु
		अगर (octeon_setup_instr_queues(oct))
			वापस -1;

		अगर (octeon_setup_output_queues(oct))
			वापस -1;

		/* Recreating mbox क्रम PF that is SRIOV disabled */
		अगर (OCTEON_CN23XX_PF(oct) && !oct->sriov_info.sriov_enabled) अणु
			अगर (oct->fn_list.setup_mbox(oct)) अणु
				dev_err(&oct->pci_dev->dev, "Mailbox setup failed\n");
				वापस -1;
			पूर्ण
		पूर्ण

		/* Deleting and recreating IRQs whether the पूर्णांकerface is SRIOV
		 * enabled or disabled.
		 */
		अगर (lio_irq_पुनः_स्मृतिate_irqs(oct, num_qs)) अणु
			dev_err(&oct->pci_dev->dev, "IRQs could not be allocated\n");
			वापस -1;
		पूर्ण

		/* Enable the input and output queues क्रम this Octeon device */
		अगर (oct->fn_list.enable_io_queues(oct)) अणु
			dev_err(&oct->pci_dev->dev, "Failed to enable input/output queues\n");
			वापस -1;
		पूर्ण

		क्रम (i = 0; i < oct->num_oqs; i++)
			ग_लिखोl(oct->droq[i]->max_count,
			       oct->droq[i]->pkts_credit_reg);

		/* Inक्रमming firmware about the new queue count. It is required
		 * क्रम firmware to allocate more number of queues than those at
		 * load समय.
		 */
		अगर (OCTEON_CN23XX_PF(oct) && !oct->sriov_info.sriov_enabled) अणु
			अगर (lio_23xx_reconfigure_queue_count(lio))
				वापस -1;
		पूर्ण
	पूर्ण

	/* Once firmware is aware of the new value, queues can be recreated */
	अगर (liquidio_setup_io_queues(oct, 0, num_qs, num_qs)) अणु
		dev_err(&oct->pci_dev->dev, "I/O queues creation failed\n");
		वापस -1;
	पूर्ण

	अगर (queue_count_update) अणु
		अगर (lio_setup_glists(oct, lio, num_qs)) अणु
			dev_err(&oct->pci_dev->dev, "Gather list allocation failed\n");
			वापस -1;
		पूर्ण

		अगर (setup_rx_oom_poll_fn(netdev)) अणु
			dev_err(&oct->pci_dev->dev, "lio_setup_rx_oom_poll_fn failed\n");
			वापस 1;
		पूर्ण

		/* Send firmware the inक्रमmation about new number of queues
		 * अगर the पूर्णांकerface is a VF or a PF that is SRIOV enabled.
		 */
		अगर (oct->sriov_info.sriov_enabled || OCTEON_CN23XX_VF(oct))
			अगर (lio_send_queue_count_update(netdev, num_qs))
				वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lio_ethtool_set_ringparam(काष्ठा net_device *netdev,
				     काष्ठा ethtool_ringparam *ering)
अणु
	u32 rx_count, tx_count, rx_count_old, tx_count_old;
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	पूर्णांक stopped = 0;

	अगर (!OCTEON_CN23XX_PF(oct) && !OCTEON_CN23XX_VF(oct))
		वापस -EINVAL;

	अगर (ering->rx_mini_pending || ering->rx_jumbo_pending)
		वापस -EINVAL;

	rx_count = clamp_t(u32, ering->rx_pending, CN23XX_MIN_OQ_DESCRIPTORS,
			   CN23XX_MAX_OQ_DESCRIPTORS);
	tx_count = clamp_t(u32, ering->tx_pending, CN23XX_MIN_IQ_DESCRIPTORS,
			   CN23XX_MAX_IQ_DESCRIPTORS);

	rx_count_old = oct->droq[0]->max_count;
	tx_count_old = oct->instr_queue[0]->max_count;

	अगर (rx_count == rx_count_old && tx_count == tx_count_old)
		वापस 0;

	अगरstate_set(lio, LIO_IFSTATE_RESETTING);

	अगर (netअगर_running(netdev)) अणु
		netdev->netdev_ops->nकरो_stop(netdev);
		stopped = 1;
	पूर्ण

	/* Change RX/TX DESCS  count */
	अगर (tx_count != tx_count_old)
		CFG_SET_NUM_TX_DESCS_NIC_IF(octeon_get_conf(oct), lio->अगरidx,
					    tx_count);
	अगर (rx_count != rx_count_old)
		CFG_SET_NUM_RX_DESCS_NIC_IF(octeon_get_conf(oct), lio->अगरidx,
					    rx_count);

	अगर (lio_reset_queues(netdev, oct->num_iqs))
		जाओ err_lio_reset_queues;

	अगर (stopped)
		netdev->netdev_ops->nकरो_खोलो(netdev);

	अगरstate_reset(lio, LIO_IFSTATE_RESETTING);

	वापस 0;

err_lio_reset_queues:
	अगर (tx_count != tx_count_old)
		CFG_SET_NUM_TX_DESCS_NIC_IF(octeon_get_conf(oct), lio->अगरidx,
					    tx_count_old);
	अगर (rx_count != rx_count_old)
		CFG_SET_NUM_RX_DESCS_NIC_IF(octeon_get_conf(oct), lio->अगरidx,
					    rx_count_old);
	वापस -EINVAL;
पूर्ण

अटल u32 lio_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);

	वापस lio->msg_enable;
पूर्ण

अटल व्योम lio_set_msglevel(काष्ठा net_device *netdev, u32 msglvl)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);

	अगर ((msglvl ^ lio->msg_enable) & NETIF_MSG_HW) अणु
		अगर (msglvl & NETIF_MSG_HW)
			liquidio_set_feature(netdev,
					     OCTNET_CMD_VERBOSE_ENABLE, 0);
		अन्यथा
			liquidio_set_feature(netdev,
					     OCTNET_CMD_VERBOSE_DISABLE, 0);
	पूर्ण

	lio->msg_enable = msglvl;
पूर्ण

अटल व्योम lio_vf_set_msglevel(काष्ठा net_device *netdev, u32 msglvl)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);

	lio->msg_enable = msglvl;
पूर्ण

अटल व्योम
lio_get_छोड़ोparam(काष्ठा net_device *netdev, काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	/* Notes: Not supporting any स्वतः negotiation in these
	 * drivers. Just report छोड़ो frame support.
	 */
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	छोड़ो->स्वतःneg = 0;

	छोड़ो->tx_छोड़ो = oct->tx_छोड़ो;
	छोड़ो->rx_छोड़ो = oct->rx_छोड़ो;
पूर्ण

अटल पूर्णांक
lio_set_छोड़ोparam(काष्ठा net_device *netdev, काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	/* Notes: Not supporting any स्वतः negotiation in these
	 * drivers.
	 */
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	काष्ठा oct_link_info *linfo = &lio->linfo;

	पूर्णांक ret = 0;

	अगर (oct->chip_id != OCTEON_CN23XX_PF_VID)
		वापस -EINVAL;

	अगर (linfo->link.s.duplex == 0) अणु
		/*no flow control क्रम half duplex*/
		अगर (छोड़ो->rx_छोड़ो || छोड़ो->tx_छोड़ो)
			वापस -EINVAL;
	पूर्ण

	/*करो not support स्वतःneg of link flow control*/
	अगर (छोड़ो->स्वतःneg == AUTONEG_ENABLE)
		वापस -EINVAL;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = OCTNET_CMD_SET_FLOW_CTL;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	अगर (छोड़ो->rx_छोड़ो) अणु
		/*enable rx छोड़ो*/
		nctrl.ncmd.s.param1 = 1;
	पूर्ण अन्यथा अणु
		/*disable rx छोड़ो*/
		nctrl.ncmd.s.param1 = 0;
	पूर्ण

	अगर (छोड़ो->tx_छोड़ो) अणु
		/*enable tx छोड़ो*/
		nctrl.ncmd.s.param2 = 1;
	पूर्ण अन्यथा अणु
		/*disable tx छोड़ो*/
		nctrl.ncmd.s.param2 = 0;
	पूर्ण

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev,
			"Failed to set pause parameter, ret=%d\n", ret);
		वापस -EINVAL;
	पूर्ण

	oct->rx_छोड़ो = छोड़ो->rx_छोड़ो;
	oct->tx_छोड़ो = छोड़ो->tx_छोड़ो;

	वापस 0;
पूर्ण

अटल व्योम
lio_get_ethtool_stats(काष्ठा net_device *netdev,
		      काष्ठा ethtool_stats *stats  __attribute__((unused)),
		      u64 *data)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	काष्ठा rtnl_link_stats64 lstats;
	पूर्णांक i = 0, j;

	अगर (अगरstate_check(lio, LIO_IFSTATE_RESETTING))
		वापस;

	netdev->netdev_ops->nकरो_get_stats64(netdev, &lstats);
	/*sum of oct->droq[oq_no]->stats->rx_pkts_received */
	data[i++] = lstats.rx_packets;
	/*sum of oct->instr_queue[iq_no]->stats.tx_करोne */
	data[i++] = lstats.tx_packets;
	/*sum of oct->droq[oq_no]->stats->rx_bytes_received */
	data[i++] = lstats.rx_bytes;
	/*sum of oct->instr_queue[iq_no]->stats.tx_tot_bytes */
	data[i++] = lstats.tx_bytes;
	data[i++] = lstats.rx_errors +
			oct_dev->link_stats.fromwire.fcs_err +
			oct_dev->link_stats.fromwire.jabber_err +
			oct_dev->link_stats.fromwire.l2_err +
			oct_dev->link_stats.fromwire.frame_err;
	data[i++] = lstats.tx_errors;
	/*sum of oct->droq[oq_no]->stats->rx_dropped +
	 *oct->droq[oq_no]->stats->dropped_nodispatch +
	 *oct->droq[oq_no]->stats->dropped_toomany +
	 *oct->droq[oq_no]->stats->dropped_nomem
	 */
	data[i++] = lstats.rx_dropped +
			oct_dev->link_stats.fromwire.fअगरo_err +
			oct_dev->link_stats.fromwire.dmac_drop +
			oct_dev->link_stats.fromwire.red_drops +
			oct_dev->link_stats.fromwire.fw_err_pko +
			oct_dev->link_stats.fromwire.fw_err_link +
			oct_dev->link_stats.fromwire.fw_err_drop;
	/*sum of oct->instr_queue[iq_no]->stats.tx_dropped */
	data[i++] = lstats.tx_dropped +
			oct_dev->link_stats.fromhost.max_collision_fail +
			oct_dev->link_stats.fromhost.max_deferral_fail +
			oct_dev->link_stats.fromhost.total_collisions +
			oct_dev->link_stats.fromhost.fw_err_pko +
			oct_dev->link_stats.fromhost.fw_err_link +
			oct_dev->link_stats.fromhost.fw_err_drop +
			oct_dev->link_stats.fromhost.fw_err_pki;

	/* firmware tx stats */
	/*per_core_stats[cvmx_get_core_num()].link_stats[mdata->from_अगरidx].
	 *fromhost.fw_total_sent
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_total_sent);
	/*per_core_stats[i].link_stats[port].fromwire.fw_total_fwd */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_total_fwd);
	/*per_core_stats[j].link_stats[i].fromhost.fw_err_pko */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_pko);
	/*per_core_stats[j].link_stats[i].fromhost.fw_err_pki */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_pki);
	/*per_core_stats[j].link_stats[i].fromhost.fw_err_link */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_link);
	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.
	 *fw_err_drop
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_drop);

	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.fw_tso */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_tso);
	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.
	 *fw_tso_fwd
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_tso_fwd);
	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.
	 *fw_err_tso
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_err_tso);
	/*per_core_stats[cvmx_get_core_num()].link_stats[idx].fromhost.
	 *fw_tx_vxlan
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fw_tx_vxlan);

	/* Multicast packets sent by this port */
	data[i++] = oct_dev->link_stats.fromhost.fw_total_mcast_sent;
	data[i++] = oct_dev->link_stats.fromhost.fw_total_bcast_sent;

	/* mac tx statistics */
	/*CVMX_BGXX_CMRX_TX_STAT5 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.total_pkts_sent);
	/*CVMX_BGXX_CMRX_TX_STAT4 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.total_bytes_sent);
	/*CVMX_BGXX_CMRX_TX_STAT15 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.mcast_pkts_sent);
	/*CVMX_BGXX_CMRX_TX_STAT14 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.bcast_pkts_sent);
	/*CVMX_BGXX_CMRX_TX_STAT17 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.ctl_sent);
	/*CVMX_BGXX_CMRX_TX_STAT0 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.total_collisions);
	/*CVMX_BGXX_CMRX_TX_STAT3 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.one_collision_sent);
	/*CVMX_BGXX_CMRX_TX_STAT2 */
	data[i++] =
		CVM_CAST64(oct_dev->link_stats.fromhost.multi_collision_sent);
	/*CVMX_BGXX_CMRX_TX_STAT0 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.max_collision_fail);
	/*CVMX_BGXX_CMRX_TX_STAT1 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.max_deferral_fail);
	/*CVMX_BGXX_CMRX_TX_STAT16 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.fअगरo_err);
	/*CVMX_BGXX_CMRX_TX_STAT6 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromhost.runts);

	/* RX firmware stats */
	/*per_core_stats[cvmx_get_core_num()].link_stats[अगरidx].fromwire.
	 *fw_total_rcvd
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_total_rcvd);
	/*per_core_stats[cvmx_get_core_num()].link_stats[अगरidx].fromwire.
	 *fw_total_fwd
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_total_fwd);
	/* Multicast packets received on this port */
	data[i++] = oct_dev->link_stats.fromwire.fw_total_mcast;
	data[i++] = oct_dev->link_stats.fromwire.fw_total_bcast;
	/*per_core_stats[core_id].link_stats[अगरidx].fromwire.jabber_err */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.jabber_err);
	/*per_core_stats[core_id].link_stats[अगरidx].fromwire.l2_err */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.l2_err);
	/*per_core_stats[core_id].link_stats[अगरidx].fromwire.frame_err */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.frame_err);
	/*per_core_stats[cvmx_get_core_num()].link_stats[अगरidx].fromwire.
	 *fw_err_pko
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_err_pko);
	/*per_core_stats[j].link_stats[i].fromwire.fw_err_link */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_err_link);
	/*per_core_stats[cvmx_get_core_num()].link_stats[lro_ctx->अगरidx].
	 *fromwire.fw_err_drop
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_err_drop);

	/*per_core_stats[cvmx_get_core_num()].link_stats[lro_ctx->अगरidx].
	 *fromwire.fw_rx_vxlan
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_rx_vxlan);
	/*per_core_stats[cvmx_get_core_num()].link_stats[lro_ctx->अगरidx].
	 *fromwire.fw_rx_vxlan_err
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_rx_vxlan_err);

	/* LRO */
	/*per_core_stats[cvmx_get_core_num()].link_stats[अगरidx].fromwire.
	 *fw_lro_pkts
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_pkts);
	/*per_core_stats[cvmx_get_core_num()].link_stats[अगरidx].fromwire.
	 *fw_lro_octs
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_octs);
	/*per_core_stats[j].link_stats[i].fromwire.fw_total_lro */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_total_lro);
	/*per_core_stats[j].link_stats[i].fromwire.fw_lro_पातs */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_पातs);
	/*per_core_stats[cvmx_get_core_num()].link_stats[अगरidx].fromwire.
	 *fw_lro_पातs_port
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_पातs_port);
	/*per_core_stats[cvmx_get_core_num()].link_stats[अगरidx].fromwire.
	 *fw_lro_पातs_seq
	 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_पातs_seq);
	/*per_core_stats[cvmx_get_core_num()].link_stats[अगरidx].fromwire.
	 *fw_lro_पातs_tsval
	 */
	data[i++] =
		CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_पातs_tsval);
	/*per_core_stats[cvmx_get_core_num()].link_stats[अगरidx].fromwire.
	 *fw_lro_पातs_समयr
	 */
	/* पूर्णांकrmod: packet क्रमward rate */
	data[i++] =
		CVM_CAST64(oct_dev->link_stats.fromwire.fw_lro_पातs_समयr);
	/*per_core_stats[j].link_stats[i].fromwire.fw_lro_पातs */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fwd_rate);

	/* mac: link-level stats */
	/*CVMX_BGXX_CMRX_RX_STAT0 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.total_rcvd);
	/*CVMX_BGXX_CMRX_RX_STAT1 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.bytes_rcvd);
	/*CVMX_PKI_STATX_STAT5 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.total_bcst);
	/*CVMX_PKI_STATX_STAT5 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.total_mcst);
	/*wqe->word2.err_code or wqe->word2.err_level */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.runts);
	/*CVMX_BGXX_CMRX_RX_STAT2 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.ctl_rcvd);
	/*CVMX_BGXX_CMRX_RX_STAT6 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fअगरo_err);
	/*CVMX_BGXX_CMRX_RX_STAT4 */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.dmac_drop);
	/*wqe->word2.err_code or wqe->word2.err_level */
	data[i++] = CVM_CAST64(oct_dev->link_stats.fromwire.fcs_err);
	/*lio->link_changes*/
	data[i++] = CVM_CAST64(lio->link_changes);

	क्रम (j = 0; j < MAX_OCTEON_INSTR_QUEUES(oct_dev); j++) अणु
		अगर (!(oct_dev->io_qmask.iq & BIT_ULL(j)))
			जारी;
		/*packets to network port*/
		/*# of packets tx to network */
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_करोne);
		/*# of bytes tx to network */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_tot_bytes);
		/*# of packets dropped */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_dropped);
		/*# of tx fails due to queue full */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_iq_busy);
		/*XXX gather entries sent */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.sgentry_sent);

		/*inकाष्ठाion to firmware: data and control */
		/*# of inकाष्ठाions to the queue */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.instr_posted);
		/*# of inकाष्ठाions processed */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.instr_processed);
		/*# of inकाष्ठाions could not be processed */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.instr_dropped);
		/*bytes sent through the queue */
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.bytes_sent);

		/*tso request*/
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_gso);
		/*vxlan request*/
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_vxlan);
		/*txq restart*/
		data[i++] =
			CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_restart);
	पूर्ण

	/* RX */
	क्रम (j = 0; j < MAX_OCTEON_OUTPUT_QUEUES(oct_dev); j++) अणु
		अगर (!(oct_dev->io_qmask.oq & BIT_ULL(j)))
			जारी;

		/*packets send to TCP/IP network stack */
		/*# of packets to network stack */
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_pkts_received);
		/*# of bytes to network stack */
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_bytes_received);
		/*# of packets dropped */
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.dropped_nomem +
				       oct_dev->droq[j]->stats.dropped_toomany +
				       oct_dev->droq[j]->stats.rx_dropped);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.dropped_nomem);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.dropped_toomany);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_dropped);

		/*control and data path*/
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.pkts_received);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.bytes_received);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.dropped_nodispatch);

		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_vxlan);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.rx_alloc_failure);
	पूर्ण
पूर्ण

अटल व्योम lio_vf_get_ethtool_stats(काष्ठा net_device *netdev,
				     काष्ठा ethtool_stats *stats
				     __attribute__((unused)),
				     u64 *data)
अणु
	काष्ठा rtnl_link_stats64 lstats;
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	पूर्णांक i = 0, j, vj;

	अगर (अगरstate_check(lio, LIO_IFSTATE_RESETTING))
		वापस;

	netdev->netdev_ops->nकरो_get_stats64(netdev, &lstats);
	/* sum of oct->droq[oq_no]->stats->rx_pkts_received */
	data[i++] = lstats.rx_packets;
	/* sum of oct->instr_queue[iq_no]->stats.tx_करोne */
	data[i++] = lstats.tx_packets;
	/* sum of oct->droq[oq_no]->stats->rx_bytes_received */
	data[i++] = lstats.rx_bytes;
	/* sum of oct->instr_queue[iq_no]->stats.tx_tot_bytes */
	data[i++] = lstats.tx_bytes;
	data[i++] = lstats.rx_errors;
	data[i++] = lstats.tx_errors;
	 /* sum of oct->droq[oq_no]->stats->rx_dropped +
	  * oct->droq[oq_no]->stats->dropped_nodispatch +
	  * oct->droq[oq_no]->stats->dropped_toomany +
	  * oct->droq[oq_no]->stats->dropped_nomem
	  */
	data[i++] = lstats.rx_dropped;
	/* sum of oct->instr_queue[iq_no]->stats.tx_dropped */
	data[i++] = lstats.tx_dropped +
		oct_dev->link_stats.fromhost.fw_err_drop;

	data[i++] = oct_dev->link_stats.fromwire.fw_total_mcast;
	data[i++] = oct_dev->link_stats.fromhost.fw_total_mcast_sent;
	data[i++] = oct_dev->link_stats.fromwire.fw_total_bcast;
	data[i++] = oct_dev->link_stats.fromhost.fw_total_bcast_sent;

	/* lio->link_changes */
	data[i++] = CVM_CAST64(lio->link_changes);

	क्रम (vj = 0; vj < oct_dev->num_iqs; vj++) अणु
		j = lio->linfo.txpciq[vj].s.q_no;

		/* packets to network port */
		/* # of packets tx to network */
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_करोne);
		 /* # of bytes tx to network */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.tx_tot_bytes);
		/* # of packets dropped */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.tx_dropped);
		/* # of tx fails due to queue full */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.tx_iq_busy);
		/* XXX gather entries sent */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.sgentry_sent);

		/* inकाष्ठाion to firmware: data and control */
		/* # of inकाष्ठाions to the queue */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.instr_posted);
		/* # of inकाष्ठाions processed */
		data[i++] =
		    CVM_CAST64(oct_dev->instr_queue[j]->stats.instr_processed);
		/* # of inकाष्ठाions could not be processed */
		data[i++] =
		    CVM_CAST64(oct_dev->instr_queue[j]->stats.instr_dropped);
		/* bytes sent through the queue */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.bytes_sent);
		/* tso request */
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_gso);
		/* vxlan request */
		data[i++] = CVM_CAST64(oct_dev->instr_queue[j]->stats.tx_vxlan);
		/* txq restart */
		data[i++] = CVM_CAST64(
				oct_dev->instr_queue[j]->stats.tx_restart);
	पूर्ण

	/* RX */
	क्रम (vj = 0; vj < oct_dev->num_oqs; vj++) अणु
		j = lio->linfo.rxpciq[vj].s.q_no;

		/* packets send to TCP/IP network stack */
		/* # of packets to network stack */
		data[i++] = CVM_CAST64(
				oct_dev->droq[j]->stats.rx_pkts_received);
		/* # of bytes to network stack */
		data[i++] = CVM_CAST64(
				oct_dev->droq[j]->stats.rx_bytes_received);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.dropped_nomem +
				       oct_dev->droq[j]->stats.dropped_toomany +
				       oct_dev->droq[j]->stats.rx_dropped);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.dropped_nomem);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.dropped_toomany);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.rx_dropped);

		/* control and data path */
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.pkts_received);
		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.bytes_received);
		data[i++] =
			CVM_CAST64(oct_dev->droq[j]->stats.dropped_nodispatch);

		data[i++] = CVM_CAST64(oct_dev->droq[j]->stats.rx_vxlan);
		data[i++] =
		    CVM_CAST64(oct_dev->droq[j]->stats.rx_alloc_failure);
	पूर्ण
पूर्ण

अटल व्योम lio_get_priv_flags_strings(काष्ठा lio *lio, u8 *data)
अणु
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	पूर्णांक i;

	चयन (oct_dev->chip_id) अणु
	हाल OCTEON_CN23XX_PF_VID:
	हाल OCTEON_CN23XX_VF_VID:
		क्रम (i = 0; i < ARRAY_SIZE(oct_priv_flags_strings); i++) अणु
			प्र_लिखो(data, "%s", oct_priv_flags_strings[i]);
			data += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	हाल OCTEON_CN68XX:
	हाल OCTEON_CN66XX:
		अवरोध;
	शेष:
		netअगर_info(lio, drv, lio->netdev, "Unknown Chip !!\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम lio_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	पूर्णांक num_iq_stats, num_oq_stats, i, j;
	पूर्णांक num_stats;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		num_stats = ARRAY_SIZE(oct_stats_strings);
		क्रम (j = 0; j < num_stats; j++) अणु
			प्र_लिखो(data, "%s", oct_stats_strings[j]);
			data += ETH_GSTRING_LEN;
		पूर्ण

		num_iq_stats = ARRAY_SIZE(oct_iq_stats_strings);
		क्रम (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct_dev); i++) अणु
			अगर (!(oct_dev->io_qmask.iq & BIT_ULL(i)))
				जारी;
			क्रम (j = 0; j < num_iq_stats; j++) अणु
				प्र_लिखो(data, "tx-%d-%s", i,
					oct_iq_stats_strings[j]);
				data += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण

		num_oq_stats = ARRAY_SIZE(oct_droq_stats_strings);
		क्रम (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct_dev); i++) अणु
			अगर (!(oct_dev->io_qmask.oq & BIT_ULL(i)))
				जारी;
			क्रम (j = 0; j < num_oq_stats; j++) अणु
				प्र_लिखो(data, "rx-%d-%s", i,
					oct_droq_stats_strings[j]);
				data += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ETH_SS_PRIV_FLAGS:
		lio_get_priv_flags_strings(lio, data);
		अवरोध;
	शेष:
		netअगर_info(lio, drv, lio->netdev, "Unknown Stringset !!\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम lio_vf_get_strings(काष्ठा net_device *netdev, u32 stringset,
			       u8 *data)
अणु
	पूर्णांक num_iq_stats, num_oq_stats, i, j;
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	पूर्णांक num_stats;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		num_stats = ARRAY_SIZE(oct_vf_stats_strings);
		क्रम (j = 0; j < num_stats; j++) अणु
			प्र_लिखो(data, "%s", oct_vf_stats_strings[j]);
			data += ETH_GSTRING_LEN;
		पूर्ण

		num_iq_stats = ARRAY_SIZE(oct_iq_stats_strings);
		क्रम (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct_dev); i++) अणु
			अगर (!(oct_dev->io_qmask.iq & BIT_ULL(i)))
				जारी;
			क्रम (j = 0; j < num_iq_stats; j++) अणु
				प्र_लिखो(data, "tx-%d-%s", i,
					oct_iq_stats_strings[j]);
				data += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण

		num_oq_stats = ARRAY_SIZE(oct_droq_stats_strings);
		क्रम (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct_dev); i++) अणु
			अगर (!(oct_dev->io_qmask.oq & BIT_ULL(i)))
				जारी;
			क्रम (j = 0; j < num_oq_stats; j++) अणु
				प्र_लिखो(data, "rx-%d-%s", i,
					oct_droq_stats_strings[j]);
				data += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ETH_SS_PRIV_FLAGS:
		lio_get_priv_flags_strings(lio, data);
		अवरोध;
	शेष:
		netअगर_info(lio, drv, lio->netdev, "Unknown Stringset !!\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक lio_get_priv_flags_ss_count(काष्ठा lio *lio)
अणु
	काष्ठा octeon_device *oct_dev = lio->oct_dev;

	चयन (oct_dev->chip_id) अणु
	हाल OCTEON_CN23XX_PF_VID:
	हाल OCTEON_CN23XX_VF_VID:
		वापस ARRAY_SIZE(oct_priv_flags_strings);
	हाल OCTEON_CN68XX:
	हाल OCTEON_CN66XX:
		वापस -EOPNOTSUPP;
	शेष:
		netअगर_info(lio, drv, lio->netdev, "Unknown Chip !!\n");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lio_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct_dev = lio->oct_dev;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस (ARRAY_SIZE(oct_stats_strings) +
			ARRAY_SIZE(oct_iq_stats_strings) * oct_dev->num_iqs +
			ARRAY_SIZE(oct_droq_stats_strings) * oct_dev->num_oqs);
	हाल ETH_SS_PRIV_FLAGS:
		वापस lio_get_priv_flags_ss_count(lio);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lio_vf_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct_dev = lio->oct_dev;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस (ARRAY_SIZE(oct_vf_stats_strings) +
			ARRAY_SIZE(oct_iq_stats_strings) * oct_dev->num_iqs +
			ARRAY_SIZE(oct_droq_stats_strings) * oct_dev->num_oqs);
	हाल ETH_SS_PRIV_FLAGS:
		वापस lio_get_priv_flags_ss_count(lio);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/*  get पूर्णांकerrupt moderation parameters */
अटल पूर्णांक octnet_get_पूर्णांकrmod_cfg(काष्ठा lio *lio,
				  काष्ठा oct_पूर्णांकrmod_cfg *पूर्णांकr_cfg)
अणु
	काष्ठा octeon_soft_command *sc;
	काष्ठा oct_पूर्णांकrmod_resp *resp;
	पूर्णांक retval;
	काष्ठा octeon_device *oct_dev = lio->oct_dev;

	/* Alloc soft command */
	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct_dev,
					  0,
					  माप(काष्ठा oct_पूर्णांकrmod_resp), 0);

	अगर (!sc)
		वापस -ENOMEM;

	resp = (काष्ठा oct_पूर्णांकrmod_resp *)sc->virtrptr;
	स_रखो(resp, 0, माप(काष्ठा oct_पूर्णांकrmod_resp));

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_INTRMOD_PARAMS, 0, 0, 0);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	retval = octeon_send_soft_command(oct_dev, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		octeon_मुक्त_soft_command(oct_dev, sc);
		वापस -EINVAL;
	पूर्ण

	/* Sleep on a रुको queue till the cond flag indicates that the
	 * response arrived or समयd-out.
	 */
	retval = रुको_क्रम_sc_completion_समयout(oct_dev, sc, 0);
	अगर (retval)
		वापस -ENODEV;

	अगर (resp->status) अणु
		dev_err(&oct_dev->pci_dev->dev,
			"Get interrupt moderation parameters failed\n");
		WRITE_ONCE(sc->caller_is_करोne, true);
		वापस -ENODEV;
	पूर्ण

	octeon_swap_8B_data((u64 *)&resp->पूर्णांकrmod,
			    (माप(काष्ठा oct_पूर्णांकrmod_cfg)) / 8);
	स_नकल(पूर्णांकr_cfg, &resp->पूर्णांकrmod, माप(काष्ठा oct_पूर्णांकrmod_cfg));
	WRITE_ONCE(sc->caller_is_करोne, true);

	वापस 0;
पूर्ण

/*  Configure पूर्णांकerrupt moderation parameters */
अटल पूर्णांक octnet_set_पूर्णांकrmod_cfg(काष्ठा lio *lio,
				  काष्ठा oct_पूर्णांकrmod_cfg *पूर्णांकr_cfg)
अणु
	काष्ठा octeon_soft_command *sc;
	काष्ठा oct_पूर्णांकrmod_cfg *cfg;
	पूर्णांक retval;
	काष्ठा octeon_device *oct_dev = lio->oct_dev;

	/* Alloc soft command */
	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct_dev,
					  माप(काष्ठा oct_पूर्णांकrmod_cfg),
					  16, 0);

	अगर (!sc)
		वापस -ENOMEM;

	cfg = (काष्ठा oct_पूर्णांकrmod_cfg *)sc->virtdptr;

	स_नकल(cfg, पूर्णांकr_cfg, माप(काष्ठा oct_पूर्णांकrmod_cfg));
	octeon_swap_8B_data((u64 *)cfg, (माप(काष्ठा oct_पूर्णांकrmod_cfg)) / 8);

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_INTRMOD_CFG, 0, 0, 0);

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	retval = octeon_send_soft_command(oct_dev, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		octeon_मुक्त_soft_command(oct_dev, sc);
		वापस -EINVAL;
	पूर्ण

	/* Sleep on a रुको queue till the cond flag indicates that the
	 * response arrived or समयd-out.
	 */
	retval = रुको_क्रम_sc_completion_समयout(oct_dev, sc, 0);
	अगर (retval)
		वापस retval;

	retval = sc->sc_status;
	अगर (retval == 0) अणु
		dev_info(&oct_dev->pci_dev->dev,
			 "Rx-Adaptive Interrupt moderation %s\n",
			 (पूर्णांकr_cfg->rx_enable) ?
			 "enabled" : "disabled");
		WRITE_ONCE(sc->caller_is_करोne, true);
		वापस 0;
	पूर्ण

	dev_err(&oct_dev->pci_dev->dev,
		"intrmod config failed. Status: %x\n", retval);
	WRITE_ONCE(sc->caller_is_करोne, true);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक lio_get_पूर्णांकr_coalesce(काष्ठा net_device *netdev,
				 काष्ठा ethtool_coalesce *पूर्णांकr_coal)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octeon_instr_queue *iq;
	काष्ठा oct_पूर्णांकrmod_cfg पूर्णांकrmod_cfg;

	अगर (octnet_get_पूर्णांकrmod_cfg(lio, &पूर्णांकrmod_cfg))
		वापस -ENODEV;

	चयन (oct->chip_id) अणु
	हाल OCTEON_CN23XX_PF_VID:
	हाल OCTEON_CN23XX_VF_VID: अणु
		अगर (!पूर्णांकrmod_cfg.rx_enable) अणु
			पूर्णांकr_coal->rx_coalesce_usecs = oct->rx_coalesce_usecs;
			पूर्णांकr_coal->rx_max_coalesced_frames =
				oct->rx_max_coalesced_frames;
		पूर्ण
		अगर (!पूर्णांकrmod_cfg.tx_enable)
			पूर्णांकr_coal->tx_max_coalesced_frames =
				oct->tx_max_coalesced_frames;
		अवरोध;
	पूर्ण
	हाल OCTEON_CN68XX:
	हाल OCTEON_CN66XX: अणु
		काष्ठा octeon_cn6xxx *cn6xxx =
			(काष्ठा octeon_cn6xxx *)oct->chip;

		अगर (!पूर्णांकrmod_cfg.rx_enable) अणु
			पूर्णांकr_coal->rx_coalesce_usecs =
				CFG_GET_OQ_INTR_TIME(cn6xxx->conf);
			पूर्णांकr_coal->rx_max_coalesced_frames =
				CFG_GET_OQ_INTR_PKT(cn6xxx->conf);
		पूर्ण
		iq = oct->instr_queue[lio->linfo.txpciq[0].s.q_no];
		पूर्णांकr_coal->tx_max_coalesced_frames = iq->fill_threshold;
		अवरोध;
	पूर्ण
	शेष:
		netअगर_info(lio, drv, lio->netdev, "Unknown Chip !!\n");
		वापस -EINVAL;
	पूर्ण
	अगर (पूर्णांकrmod_cfg.rx_enable) अणु
		पूर्णांकr_coal->use_adaptive_rx_coalesce =
			पूर्णांकrmod_cfg.rx_enable;
		पूर्णांकr_coal->rate_sample_पूर्णांकerval =
			पूर्णांकrmod_cfg.check_पूर्णांकrvl;
		पूर्णांकr_coal->pkt_rate_high =
			पूर्णांकrmod_cfg.maxpkt_ratethr;
		पूर्णांकr_coal->pkt_rate_low =
			पूर्णांकrmod_cfg.minpkt_ratethr;
		पूर्णांकr_coal->rx_max_coalesced_frames_high =
			पूर्णांकrmod_cfg.rx_maxcnt_trigger;
		पूर्णांकr_coal->rx_coalesce_usecs_high =
			पूर्णांकrmod_cfg.rx_maxपंचांगr_trigger;
		पूर्णांकr_coal->rx_coalesce_usecs_low =
			पूर्णांकrmod_cfg.rx_mपूर्णांकmr_trigger;
		पूर्णांकr_coal->rx_max_coalesced_frames_low =
			पूर्णांकrmod_cfg.rx_mincnt_trigger;
	पूर्ण
	अगर ((OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct)) &&
	    (पूर्णांकrmod_cfg.tx_enable)) अणु
		पूर्णांकr_coal->use_adaptive_tx_coalesce =
			पूर्णांकrmod_cfg.tx_enable;
		पूर्णांकr_coal->tx_max_coalesced_frames_high =
			पूर्णांकrmod_cfg.tx_maxcnt_trigger;
		पूर्णांकr_coal->tx_max_coalesced_frames_low =
			पूर्णांकrmod_cfg.tx_mincnt_trigger;
	पूर्ण
	वापस 0;
पूर्ण

/* Enable/Disable स्वतः पूर्णांकerrupt Moderation */
अटल पूर्णांक oct_cfg_adaptive_पूर्णांकr(काष्ठा lio *lio,
				 काष्ठा oct_पूर्णांकrmod_cfg *पूर्णांकrmod_cfg,
				 काष्ठा ethtool_coalesce *पूर्णांकr_coal)
अणु
	पूर्णांक ret = 0;

	अगर (पूर्णांकrmod_cfg->rx_enable || पूर्णांकrmod_cfg->tx_enable) अणु
		पूर्णांकrmod_cfg->check_पूर्णांकrvl = पूर्णांकr_coal->rate_sample_पूर्णांकerval;
		पूर्णांकrmod_cfg->maxpkt_ratethr = पूर्णांकr_coal->pkt_rate_high;
		पूर्णांकrmod_cfg->minpkt_ratethr = पूर्णांकr_coal->pkt_rate_low;
	पूर्ण
	अगर (पूर्णांकrmod_cfg->rx_enable) अणु
		पूर्णांकrmod_cfg->rx_maxcnt_trigger =
			पूर्णांकr_coal->rx_max_coalesced_frames_high;
		पूर्णांकrmod_cfg->rx_maxपंचांगr_trigger =
			पूर्णांकr_coal->rx_coalesce_usecs_high;
		पूर्णांकrmod_cfg->rx_mपूर्णांकmr_trigger =
			पूर्णांकr_coal->rx_coalesce_usecs_low;
		पूर्णांकrmod_cfg->rx_mincnt_trigger =
			पूर्णांकr_coal->rx_max_coalesced_frames_low;
	पूर्ण
	अगर (पूर्णांकrmod_cfg->tx_enable) अणु
		पूर्णांकrmod_cfg->tx_maxcnt_trigger =
			पूर्णांकr_coal->tx_max_coalesced_frames_high;
		पूर्णांकrmod_cfg->tx_mincnt_trigger =
			पूर्णांकr_coal->tx_max_coalesced_frames_low;
	पूर्ण

	ret = octnet_set_पूर्णांकrmod_cfg(lio, पूर्णांकrmod_cfg);

	वापस ret;
पूर्ण

अटल पूर्णांक
oct_cfg_rx_पूर्णांकrcnt(काष्ठा lio *lio,
		   काष्ठा oct_पूर्णांकrmod_cfg *पूर्णांकrmod,
		   काष्ठा ethtool_coalesce *पूर्णांकr_coal)
अणु
	काष्ठा octeon_device *oct = lio->oct_dev;
	u32 rx_max_coalesced_frames;

	/* Config Cnt based पूर्णांकerrupt values */
	चयन (oct->chip_id) अणु
	हाल OCTEON_CN68XX:
	हाल OCTEON_CN66XX: अणु
		काष्ठा octeon_cn6xxx *cn6xxx =
			(काष्ठा octeon_cn6xxx *)oct->chip;

		अगर (!पूर्णांकr_coal->rx_max_coalesced_frames)
			rx_max_coalesced_frames = CN6XXX_OQ_INTR_PKT;
		अन्यथा
			rx_max_coalesced_frames =
				पूर्णांकr_coal->rx_max_coalesced_frames;
		octeon_ग_लिखो_csr(oct, CN6XXX_SLI_OQ_INT_LEVEL_PKTS,
				 rx_max_coalesced_frames);
		CFG_SET_OQ_INTR_PKT(cn6xxx->conf, rx_max_coalesced_frames);
		अवरोध;
	पूर्ण
	हाल OCTEON_CN23XX_PF_VID: अणु
		पूर्णांक q_no;

		अगर (!पूर्णांकr_coal->rx_max_coalesced_frames)
			rx_max_coalesced_frames = पूर्णांकrmod->rx_frames;
		अन्यथा
			rx_max_coalesced_frames =
			    पूर्णांकr_coal->rx_max_coalesced_frames;
		क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
			q_no += oct->sriov_info.pf_srn;
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_SLI_OQ_PKT_INT_LEVELS(q_no),
			    (octeon_पढ़ो_csr64(
				 oct, CN23XX_SLI_OQ_PKT_INT_LEVELS(q_no)) &
			     (0x3fffff00000000UL)) |
				(rx_max_coalesced_frames - 1));
			/*consider setting resend bit*/
		पूर्ण
		पूर्णांकrmod->rx_frames = rx_max_coalesced_frames;
		oct->rx_max_coalesced_frames = rx_max_coalesced_frames;
		अवरोध;
	पूर्ण
	हाल OCTEON_CN23XX_VF_VID: अणु
		पूर्णांक q_no;

		अगर (!पूर्णांकr_coal->rx_max_coalesced_frames)
			rx_max_coalesced_frames = पूर्णांकrmod->rx_frames;
		अन्यथा
			rx_max_coalesced_frames =
			    पूर्णांकr_coal->rx_max_coalesced_frames;
		क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_VF_SLI_OQ_PKT_INT_LEVELS(q_no),
			    (octeon_पढ़ो_csr64(
				 oct, CN23XX_VF_SLI_OQ_PKT_INT_LEVELS(q_no)) &
			     (0x3fffff00000000UL)) |
				(rx_max_coalesced_frames - 1));
			/*consider writing to resend bit here*/
		पूर्ण
		पूर्णांकrmod->rx_frames = rx_max_coalesced_frames;
		oct->rx_max_coalesced_frames = rx_max_coalesced_frames;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक oct_cfg_rx_पूर्णांकrसमय(काष्ठा lio *lio,
			       काष्ठा oct_पूर्णांकrmod_cfg *पूर्णांकrmod,
			       काष्ठा ethtool_coalesce *पूर्णांकr_coal)
अणु
	काष्ठा octeon_device *oct = lio->oct_dev;
	u32 समय_प्रकारhreshold, rx_coalesce_usecs;

	/* Config Time based पूर्णांकerrupt values */
	चयन (oct->chip_id) अणु
	हाल OCTEON_CN68XX:
	हाल OCTEON_CN66XX: अणु
		काष्ठा octeon_cn6xxx *cn6xxx =
			(काष्ठा octeon_cn6xxx *)oct->chip;
		अगर (!पूर्णांकr_coal->rx_coalesce_usecs)
			rx_coalesce_usecs = CN6XXX_OQ_INTR_TIME;
		अन्यथा
			rx_coalesce_usecs = पूर्णांकr_coal->rx_coalesce_usecs;

		समय_प्रकारhreshold = lio_cn6xxx_get_oq_ticks(oct,
							 rx_coalesce_usecs);
		octeon_ग_लिखो_csr(oct,
				 CN6XXX_SLI_OQ_INT_LEVEL_TIME,
				 समय_प्रकारhreshold);

		CFG_SET_OQ_INTR_TIME(cn6xxx->conf, rx_coalesce_usecs);
		अवरोध;
	पूर्ण
	हाल OCTEON_CN23XX_PF_VID: अणु
		u64 समय_प्रकारhreshold;
		पूर्णांक q_no;

		अगर (!पूर्णांकr_coal->rx_coalesce_usecs)
			rx_coalesce_usecs = पूर्णांकrmod->rx_usecs;
		अन्यथा
			rx_coalesce_usecs = पूर्णांकr_coal->rx_coalesce_usecs;
		समय_प्रकारhreshold =
		    cn23xx_pf_get_oq_ticks(oct, (u32)rx_coalesce_usecs);
		क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
			q_no += oct->sriov_info.pf_srn;
			octeon_ग_लिखो_csr64(oct,
					   CN23XX_SLI_OQ_PKT_INT_LEVELS(q_no),
					   (पूर्णांकrmod->rx_frames |
					    ((u64)समय_प्रकारhreshold << 32)));
			/*consider writing to resend bit here*/
		पूर्ण
		पूर्णांकrmod->rx_usecs = rx_coalesce_usecs;
		oct->rx_coalesce_usecs = rx_coalesce_usecs;
		अवरोध;
	पूर्ण
	हाल OCTEON_CN23XX_VF_VID: अणु
		u64 समय_प्रकारhreshold;
		पूर्णांक q_no;

		अगर (!पूर्णांकr_coal->rx_coalesce_usecs)
			rx_coalesce_usecs = पूर्णांकrmod->rx_usecs;
		अन्यथा
			rx_coalesce_usecs = पूर्णांकr_coal->rx_coalesce_usecs;

		समय_प्रकारhreshold =
		    cn23xx_vf_get_oq_ticks(oct, (u32)rx_coalesce_usecs);
		क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
			octeon_ग_लिखो_csr64(
				oct, CN23XX_VF_SLI_OQ_PKT_INT_LEVELS(q_no),
				(पूर्णांकrmod->rx_frames |
				 ((u64)समय_प्रकारhreshold << 32)));
			/*consider setting resend bit*/
		पूर्ण
		पूर्णांकrmod->rx_usecs = rx_coalesce_usecs;
		oct->rx_coalesce_usecs = rx_coalesce_usecs;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
oct_cfg_tx_पूर्णांकrcnt(काष्ठा lio *lio,
		   काष्ठा oct_पूर्णांकrmod_cfg *पूर्णांकrmod,
		   काष्ठा ethtool_coalesce *पूर्णांकr_coal)
अणु
	काष्ठा octeon_device *oct = lio->oct_dev;
	u32 iq_पूर्णांकr_pkt;
	व्योम __iomem *inst_cnt_reg;
	u64 val;

	/* Config Cnt based पूर्णांकerrupt values */
	चयन (oct->chip_id) अणु
	हाल OCTEON_CN68XX:
	हाल OCTEON_CN66XX:
		अवरोध;
	हाल OCTEON_CN23XX_VF_VID:
	हाल OCTEON_CN23XX_PF_VID: अणु
		पूर्णांक q_no;

		अगर (!पूर्णांकr_coal->tx_max_coalesced_frames)
			iq_पूर्णांकr_pkt = CN23XX_DEF_IQ_INTR_THRESHOLD &
				      CN23XX_PKT_IN_DONE_WMARK_MASK;
		अन्यथा
			iq_पूर्णांकr_pkt = पूर्णांकr_coal->tx_max_coalesced_frames &
				      CN23XX_PKT_IN_DONE_WMARK_MASK;
		क्रम (q_no = 0; q_no < oct->num_iqs; q_no++) अणु
			inst_cnt_reg = (oct->instr_queue[q_no])->inst_cnt_reg;
			val = पढ़ोq(inst_cnt_reg);
			/*clear wmark and count.करोnt want to ग_लिखो count back*/
			val = (val & 0xFFFF000000000000ULL) |
			      ((u64)(iq_पूर्णांकr_pkt - 1)
			       << CN23XX_PKT_IN_DONE_WMARK_BIT_POS);
			ग_लिखोq(val, inst_cnt_reg);
			/*consider setting resend bit*/
		पूर्ण
		पूर्णांकrmod->tx_frames = iq_पूर्णांकr_pkt;
		oct->tx_max_coalesced_frames = iq_पूर्णांकr_pkt;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lio_set_पूर्णांकr_coalesce(काष्ठा net_device *netdev,
				 काष्ठा ethtool_coalesce *पूर्णांकr_coal)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	पूर्णांक ret;
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा oct_पूर्णांकrmod_cfg पूर्णांकrmod = अणु0पूर्ण;
	u32 j, q_no;
	पूर्णांक db_max, db_min;

	चयन (oct->chip_id) अणु
	हाल OCTEON_CN68XX:
	हाल OCTEON_CN66XX:
		db_min = CN6XXX_DB_MIN;
		db_max = CN6XXX_DB_MAX;
		अगर ((पूर्णांकr_coal->tx_max_coalesced_frames >= db_min) &&
		    (पूर्णांकr_coal->tx_max_coalesced_frames <= db_max)) अणु
			क्रम (j = 0; j < lio->linfo.num_txpciq; j++) अणु
				q_no = lio->linfo.txpciq[j].s.q_no;
				oct->instr_queue[q_no]->fill_threshold =
					पूर्णांकr_coal->tx_max_coalesced_frames;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(&oct->pci_dev->dev,
				"LIQUIDIO: Invalid tx-frames:%d. Range is min:%d max:%d\n",
				पूर्णांकr_coal->tx_max_coalesced_frames,
				db_min, db_max);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल OCTEON_CN23XX_PF_VID:
	हाल OCTEON_CN23XX_VF_VID:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	पूर्णांकrmod.rx_enable = पूर्णांकr_coal->use_adaptive_rx_coalesce ? 1 : 0;
	पूर्णांकrmod.tx_enable = पूर्णांकr_coal->use_adaptive_tx_coalesce ? 1 : 0;
	पूर्णांकrmod.rx_frames = CFG_GET_OQ_INTR_PKT(octeon_get_conf(oct));
	पूर्णांकrmod.rx_usecs = CFG_GET_OQ_INTR_TIME(octeon_get_conf(oct));
	पूर्णांकrmod.tx_frames = CFG_GET_IQ_INTR_PKT(octeon_get_conf(oct));

	ret = oct_cfg_adaptive_पूर्णांकr(lio, &पूर्णांकrmod, पूर्णांकr_coal);

	अगर (!पूर्णांकr_coal->use_adaptive_rx_coalesce) अणु
		ret = oct_cfg_rx_पूर्णांकrसमय(lio, &पूर्णांकrmod, पूर्णांकr_coal);
		अगर (ret)
			जाओ ret_पूर्णांकrmod;

		ret = oct_cfg_rx_पूर्णांकrcnt(lio, &पूर्णांकrmod, पूर्णांकr_coal);
		अगर (ret)
			जाओ ret_पूर्णांकrmod;
	पूर्ण अन्यथा अणु
		oct->rx_coalesce_usecs =
			CFG_GET_OQ_INTR_TIME(octeon_get_conf(oct));
		oct->rx_max_coalesced_frames =
			CFG_GET_OQ_INTR_PKT(octeon_get_conf(oct));
	पूर्ण

	अगर (!पूर्णांकr_coal->use_adaptive_tx_coalesce) अणु
		ret = oct_cfg_tx_पूर्णांकrcnt(lio, &पूर्णांकrmod, पूर्णांकr_coal);
		अगर (ret)
			जाओ ret_पूर्णांकrmod;
	पूर्ण अन्यथा अणु
		oct->tx_max_coalesced_frames =
			CFG_GET_IQ_INTR_PKT(octeon_get_conf(oct));
	पूर्ण

	वापस 0;
ret_पूर्णांकrmod:
	वापस ret;
पूर्ण

अटल पूर्णांक lio_get_ts_info(काष्ठा net_device *netdev,
			   काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);

	info->so_बारtamping =
#अगर_घोषित PTP_HARDWARE_TIMESTAMPING
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE |
		SOF_TIMESTAMPING_TX_SOFTWARE |
#पूर्ण_अगर
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE;

	अगर (lio->ptp_घड़ी)
		info->phc_index = ptp_घड़ी_index(lio->ptp_घड़ी);
	अन्यथा
		info->phc_index = -1;

#अगर_घोषित PTP_HARDWARE_TIMESTAMPING
	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);

	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
			   (1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
			   (1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Return रेजिस्टर dump len. */
अटल पूर्णांक lio_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा lio *lio = GET_LIO(dev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	चयन (oct->chip_id) अणु
	हाल OCTEON_CN23XX_PF_VID:
		वापस OCT_ETHTOOL_REGDUMP_LEN_23XX;
	हाल OCTEON_CN23XX_VF_VID:
		वापस OCT_ETHTOOL_REGDUMP_LEN_23XX_VF;
	शेष:
		वापस OCT_ETHTOOL_REGDUMP_LEN;
	पूर्ण
पूर्ण

अटल पूर्णांक cn23xx_पढ़ो_csr_reg(अक्षर *s, काष्ठा octeon_device *oct)
अणु
	u32 reg;
	u8 pf_num = oct->pf_num;
	पूर्णांक len = 0;
	पूर्णांक i;

	/* PCI  Winकरोw Registers */

	len += प्र_लिखो(s + len, "\n\t Octeon CSR Registers\n\n");

	/*0x29030 or 0x29040*/
	reg = CN23XX_SLI_PKT_MAC_RINFO64(oct->pcie_port, oct->pf_num);
	len += प्र_लिखो(s + len,
		       "\n[%08x] (SLI_PKT_MAC%d_PF%d_RINFO): %016llx\n",
		       reg, oct->pcie_port, oct->pf_num,
		       (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x27080 or 0x27090*/
	reg = CN23XX_SLI_MAC_PF_INT_ENB64(oct->pcie_port, oct->pf_num);
	len +=
	    प्र_लिखो(s + len, "\n[%08x] (SLI_MAC%d_PF%d_INT_ENB): %016llx\n",
		    reg, oct->pcie_port, oct->pf_num,
		    (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x27000 or 0x27010*/
	reg = CN23XX_SLI_MAC_PF_INT_SUM64(oct->pcie_port, oct->pf_num);
	len +=
	    प्र_लिखो(s + len, "\n[%08x] (SLI_MAC%d_PF%d_INT_SUM): %016llx\n",
		    reg, oct->pcie_port, oct->pf_num,
		    (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x29120*/
	reg = 0x29120;
	len += प्र_लिखो(s + len, "\n[%08x] (SLI_PKT_MEM_CTL): %016llx\n", reg,
		       (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x27300*/
	reg = 0x27300 + oct->pcie_port * CN23XX_MAC_INT_OFFSET +
	      (oct->pf_num) * CN23XX_PF_INT_OFFSET;
	len += प्र_लिखो(
	    s + len, "\n[%08x] (SLI_MAC%d_PF%d_PKT_VF_INT): %016llx\n", reg,
	    oct->pcie_port, oct->pf_num, (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x27200*/
	reg = 0x27200 + oct->pcie_port * CN23XX_MAC_INT_OFFSET +
	      (oct->pf_num) * CN23XX_PF_INT_OFFSET;
	len += प्र_लिखो(s + len,
		       "\n[%08x] (SLI_MAC%d_PF%d_PP_VF_INT): %016llx\n",
		       reg, oct->pcie_port, oct->pf_num,
		       (u64)octeon_पढ़ो_csr64(oct, reg));

	/*29130*/
	reg = CN23XX_SLI_PKT_CNT_INT;
	len += प्र_लिखो(s + len, "\n[%08x] (SLI_PKT_CNT_INT): %016llx\n", reg,
		       (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x29140*/
	reg = CN23XX_SLI_PKT_TIME_INT;
	len += प्र_लिखो(s + len, "\n[%08x] (SLI_PKT_TIME_INT): %016llx\n", reg,
		       (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x29160*/
	reg = 0x29160;
	len += प्र_लिखो(s + len, "\n[%08x] (SLI_PKT_INT): %016llx\n", reg,
		       (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x29180*/
	reg = CN23XX_SLI_OQ_WMARK;
	len += प्र_लिखो(s + len, "\n[%08x] (SLI_PKT_OUTPUT_WMARK): %016llx\n",
		       reg, (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x291E0*/
	reg = CN23XX_SLI_PKT_IOQ_RING_RST;
	len += प्र_लिखो(s + len, "\n[%08x] (SLI_PKT_RING_RST): %016llx\n", reg,
		       (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x29210*/
	reg = CN23XX_SLI_GBL_CONTROL;
	len += प्र_लिखो(s + len,
		       "\n[%08x] (SLI_PKT_GBL_CONTROL): %016llx\n", reg,
		       (u64)octeon_पढ़ो_csr64(oct, reg));

	/*0x29220*/
	reg = 0x29220;
	len += प्र_लिखो(s + len, "\n[%08x] (SLI_PKT_BIST_STATUS): %016llx\n",
		       reg, (u64)octeon_पढ़ो_csr64(oct, reg));

	/*PF only*/
	अगर (pf_num == 0) अणु
		/*0x29260*/
		reg = CN23XX_SLI_OUT_BP_EN_W1S;
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT_OUT_BP_EN_W1S):  %016llx\n",
			       reg, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण अन्यथा अगर (pf_num == 1) अणु
		/*0x29270*/
		reg = CN23XX_SLI_OUT_BP_EN2_W1S;
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT_OUT_BP_EN2_W1S): %016llx\n",
			       reg, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		reg = CN23XX_SLI_OQ_BUFF_INFO_SIZE(i);
		len +=
		    प्र_लिखो(s + len, "\n[%08x] (SLI_PKT%d_OUT_SIZE): %016llx\n",
			    reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	/*0x10040*/
	क्रम (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) अणु
		reg = CN23XX_SLI_IQ_INSTR_COUNT64(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT_IN_DONE%d_CNTS): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	/*0x10080*/
	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		reg = CN23XX_SLI_OQ_PKTS_CREDIT(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_SLIST_BAOFF_DBELL): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	/*0x10090*/
	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		reg = CN23XX_SLI_OQ_SIZE(i);
		len += प्र_लिखो(
		    s + len, "\n[%08x] (SLI_PKT%d_SLIST_FIFO_RSIZE): %016llx\n",
		    reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	/*0x10050*/
	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		reg = CN23XX_SLI_OQ_PKT_CONTROL(i);
		len += प्र_लिखो(
			s + len,
			"\n[%08x] (SLI_PKT%d__OUTPUT_CONTROL): %016llx\n",
			reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	/*0x10070*/
	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		reg = CN23XX_SLI_OQ_BASE_ADDR64(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_SLIST_BADDR): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	/*0x100a0*/
	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		reg = CN23XX_SLI_OQ_PKT_INT_LEVELS(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_INT_LEVELS): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	/*0x100b0*/
	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		reg = CN23XX_SLI_OQ_PKTS_SENT(i);
		len += प्र_लिखो(s + len, "\n[%08x] (SLI_PKT%d_CNTS): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	/*0x100c0*/
	क्रम (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) अणु
		reg = 0x100c0 + i * CN23XX_OQ_OFFSET;
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_ERROR_INFO): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));

		/*0x10000*/
		क्रम (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) अणु
			reg = CN23XX_SLI_IQ_PKT_CONTROL64(i);
			len += प्र_लिखो(
				s + len,
				"\n[%08x] (SLI_PKT%d_INPUT_CONTROL): %016llx\n",
				reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
		पूर्ण

		/*0x10010*/
		क्रम (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) अणु
			reg = CN23XX_SLI_IQ_BASE_ADDR64(i);
			len += प्र_लिखो(
			    s + len,
			    "\n[%08x] (SLI_PKT%d_INSTR_BADDR): %016llx\n", reg,
			    i, (u64)octeon_पढ़ो_csr64(oct, reg));
		पूर्ण

		/*0x10020*/
		क्रम (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) अणु
			reg = CN23XX_SLI_IQ_DOORBELL(i);
			len += प्र_लिखो(
			    s + len,
			    "\n[%08x] (SLI_PKT%d_INSTR_BAOFF_DBELL): %016llx\n",
			    reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
		पूर्ण

		/*0x10030*/
		क्रम (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) अणु
			reg = CN23XX_SLI_IQ_SIZE(i);
			len += प्र_लिखो(
			    s + len,
			    "\n[%08x] (SLI_PKT%d_INSTR_FIFO_RSIZE): %016llx\n",
			    reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
		पूर्ण

		/*0x10040*/
		क्रम (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++)
			reg = CN23XX_SLI_IQ_INSTR_COUNT64(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT_IN_DONE%d_CNTS): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक cn23xx_vf_पढ़ो_csr_reg(अक्षर *s, काष्ठा octeon_device *oct)
अणु
	पूर्णांक len = 0;
	u32 reg;
	पूर्णांक i;

	/* PCI  Winकरोw Registers */

	len += प्र_लिखो(s + len, "\n\t Octeon CSR Registers\n\n");

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_OQ_BUFF_INFO_SIZE(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_OUT_SIZE): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_IQ_INSTR_COUNT64(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT_IN_DONE%d_CNTS): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_OQ_PKTS_CREDIT(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_SLIST_BAOFF_DBELL): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_OQ_SIZE(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_SLIST_FIFO_RSIZE): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_OQ_PKT_CONTROL(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d__OUTPUT_CONTROL): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_OQ_BASE_ADDR64(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_SLIST_BADDR): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_OQ_PKT_INT_LEVELS(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_INT_LEVELS): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_OQ_PKTS_SENT(i);
		len += प्र_लिखो(s + len, "\n[%08x] (SLI_PKT%d_CNTS): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = 0x100c0 + i * CN23XX_VF_OQ_OFFSET;
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_ERROR_INFO): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = 0x100d0 + i * CN23XX_VF_IQ_OFFSET;
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_VF_INT_SUM): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_IQ_PKT_CONTROL64(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_INPUT_CONTROL): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_IQ_BASE_ADDR64(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_INSTR_BADDR): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_IQ_DOORBELL(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_INSTR_BAOFF_DBELL): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_IQ_SIZE(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT%d_INSTR_FIFO_RSIZE): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	क्रम (i = 0; i < (oct->sriov_info.rings_per_vf); i++) अणु
		reg = CN23XX_VF_SLI_IQ_INSTR_COUNT64(i);
		len += प्र_लिखो(s + len,
			       "\n[%08x] (SLI_PKT_IN_DONE%d_CNTS): %016llx\n",
			       reg, i, (u64)octeon_पढ़ो_csr64(oct, reg));
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक cn6xxx_पढ़ो_csr_reg(अक्षर *s, काष्ठा octeon_device *oct)
अणु
	u32 reg;
	पूर्णांक i, len = 0;

	/* PCI  Winकरोw Registers */

	len += प्र_लिखो(s + len, "\n\t Octeon CSR Registers\n\n");
	reg = CN6XXX_WIN_WR_ADDR_LO;
	len += प्र_लिखो(s + len, "\n[%02x] (WIN_WR_ADDR_LO): %08x\n",
		       CN6XXX_WIN_WR_ADDR_LO, octeon_पढ़ो_csr(oct, reg));
	reg = CN6XXX_WIN_WR_ADDR_HI;
	len += प्र_लिखो(s + len, "[%02x] (WIN_WR_ADDR_HI): %08x\n",
		       CN6XXX_WIN_WR_ADDR_HI, octeon_पढ़ो_csr(oct, reg));
	reg = CN6XXX_WIN_RD_ADDR_LO;
	len += प्र_लिखो(s + len, "[%02x] (WIN_RD_ADDR_LO): %08x\n",
		       CN6XXX_WIN_RD_ADDR_LO, octeon_पढ़ो_csr(oct, reg));
	reg = CN6XXX_WIN_RD_ADDR_HI;
	len += प्र_लिखो(s + len, "[%02x] (WIN_RD_ADDR_HI): %08x\n",
		       CN6XXX_WIN_RD_ADDR_HI, octeon_पढ़ो_csr(oct, reg));
	reg = CN6XXX_WIN_WR_DATA_LO;
	len += प्र_लिखो(s + len, "[%02x] (WIN_WR_DATA_LO): %08x\n",
		       CN6XXX_WIN_WR_DATA_LO, octeon_पढ़ो_csr(oct, reg));
	reg = CN6XXX_WIN_WR_DATA_HI;
	len += प्र_लिखो(s + len, "[%02x] (WIN_WR_DATA_HI): %08x\n",
		       CN6XXX_WIN_WR_DATA_HI, octeon_पढ़ो_csr(oct, reg));
	len += प्र_लिखो(s + len, "[%02x] (WIN_WR_MASK_REG): %08x\n",
		       CN6XXX_WIN_WR_MASK_REG,
		       octeon_पढ़ो_csr(oct, CN6XXX_WIN_WR_MASK_REG));

	/* PCI  Interrupt Register */
	len += प्र_लिखो(s + len, "\n[%x] (INT_ENABLE PORT 0): %08x\n",
		       CN6XXX_SLI_INT_ENB64_PORT0, octeon_पढ़ो_csr(oct,
						CN6XXX_SLI_INT_ENB64_PORT0));
	len += प्र_लिखो(s + len, "\n[%x] (INT_ENABLE PORT 1): %08x\n",
		       CN6XXX_SLI_INT_ENB64_PORT1,
		       octeon_पढ़ो_csr(oct, CN6XXX_SLI_INT_ENB64_PORT1));
	len += प्र_लिखो(s + len, "[%x] (INT_SUM): %08x\n", CN6XXX_SLI_INT_SUM64,
		       octeon_पढ़ो_csr(oct, CN6XXX_SLI_INT_SUM64));

	/* PCI  Output queue रेजिस्टरs */
	क्रम (i = 0; i < oct->num_oqs; i++) अणु
		reg = CN6XXX_SLI_OQ_PKTS_SENT(i);
		len += प्र_लिखो(s + len, "\n[%x] (PKTS_SENT_%d): %08x\n",
			       reg, i, octeon_पढ़ो_csr(oct, reg));
		reg = CN6XXX_SLI_OQ_PKTS_CREDIT(i);
		len += प्र_लिखो(s + len, "[%x] (PKT_CREDITS_%d): %08x\n",
			       reg, i, octeon_पढ़ो_csr(oct, reg));
	पूर्ण
	reg = CN6XXX_SLI_OQ_INT_LEVEL_PKTS;
	len += प्र_लिखो(s + len, "\n[%x] (PKTS_SENT_INT_LEVEL): %08x\n",
		       reg, octeon_पढ़ो_csr(oct, reg));
	reg = CN6XXX_SLI_OQ_INT_LEVEL_TIME;
	len += प्र_लिखो(s + len, "[%x] (PKTS_SENT_TIME): %08x\n",
		       reg, octeon_पढ़ो_csr(oct, reg));

	/* PCI  Input queue रेजिस्टरs */
	क्रम (i = 0; i <= 3; i++) अणु
		u32 reg;

		reg = CN6XXX_SLI_IQ_DOORBELL(i);
		len += प्र_लिखो(s + len, "\n[%x] (INSTR_DOORBELL_%d): %08x\n",
			       reg, i, octeon_पढ़ो_csr(oct, reg));
		reg = CN6XXX_SLI_IQ_INSTR_COUNT(i);
		len += प्र_लिखो(s + len, "[%x] (INSTR_COUNT_%d): %08x\n",
			       reg, i, octeon_पढ़ो_csr(oct, reg));
	पूर्ण

	/* PCI  DMA रेजिस्टरs */

	len += प्र_लिखो(s + len, "\n[%x] (DMA_CNT_0): %08x\n",
		       CN6XXX_DMA_CNT(0),
		       octeon_पढ़ो_csr(oct, CN6XXX_DMA_CNT(0)));
	reg = CN6XXX_DMA_PKT_INT_LEVEL(0);
	len += प्र_लिखो(s + len, "[%x] (DMA_INT_LEV_0): %08x\n",
		       CN6XXX_DMA_PKT_INT_LEVEL(0), octeon_पढ़ो_csr(oct, reg));
	reg = CN6XXX_DMA_TIME_INT_LEVEL(0);
	len += प्र_लिखो(s + len, "[%x] (DMA_TIME_0): %08x\n",
		       CN6XXX_DMA_TIME_INT_LEVEL(0),
		       octeon_पढ़ो_csr(oct, reg));

	len += प्र_लिखो(s + len, "\n[%x] (DMA_CNT_1): %08x\n",
		       CN6XXX_DMA_CNT(1),
		       octeon_पढ़ो_csr(oct, CN6XXX_DMA_CNT(1)));
	reg = CN6XXX_DMA_PKT_INT_LEVEL(1);
	len += प्र_लिखो(s + len, "[%x] (DMA_INT_LEV_1): %08x\n",
		       CN6XXX_DMA_PKT_INT_LEVEL(1),
		       octeon_पढ़ो_csr(oct, reg));
	reg = CN6XXX_DMA_PKT_INT_LEVEL(1);
	len += प्र_लिखो(s + len, "[%x] (DMA_TIME_1): %08x\n",
		       CN6XXX_DMA_TIME_INT_LEVEL(1),
		       octeon_पढ़ो_csr(oct, reg));

	/* PCI  Index रेजिस्टरs */

	len += प्र_लिखो(s + len, "\n");

	क्रम (i = 0; i < 16; i++) अणु
		reg = lio_pci_पढ़ोq(oct, CN6XXX_BAR1_REG(i, oct->pcie_port));
		len += प्र_लिखो(s + len, "[%llx] (BAR1_INDEX_%02d): %08x\n",
			       CN6XXX_BAR1_REG(i, oct->pcie_port), i, reg);
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक cn6xxx_पढ़ो_config_reg(अक्षर *s, काष्ठा octeon_device *oct)
अणु
	u32 val;
	पूर्णांक i, len = 0;

	/* PCI CONFIG Registers */

	len += प्र_लिखो(s + len,
		       "\n\t Octeon Config space Registers\n\n");

	क्रम (i = 0; i <= 13; i++) अणु
		pci_पढ़ो_config_dword(oct->pci_dev, (i * 4), &val);
		len += प्र_लिखो(s + len, "[0x%x] (Config[%d]): 0x%08x\n",
			       (i * 4), i, val);
	पूर्ण

	क्रम (i = 30; i <= 34; i++) अणु
		pci_पढ़ो_config_dword(oct->pci_dev, (i * 4), &val);
		len += प्र_लिखो(s + len, "[0x%x] (Config[%d]): 0x%08x\n",
			       (i * 4), i, val);
	पूर्ण

	वापस len;
पूर्ण

/*  Return रेजिस्टर dump user app.  */
अटल व्योम lio_get_regs(काष्ठा net_device *dev,
			 काष्ठा ethtool_regs *regs, व्योम *regbuf)
अणु
	काष्ठा lio *lio = GET_LIO(dev);
	पूर्णांक len = 0;
	काष्ठा octeon_device *oct = lio->oct_dev;

	regs->version = OCT_ETHTOOL_REGSVER;

	चयन (oct->chip_id) अणु
	हाल OCTEON_CN23XX_PF_VID:
		स_रखो(regbuf, 0, OCT_ETHTOOL_REGDUMP_LEN_23XX);
		len += cn23xx_पढ़ो_csr_reg(regbuf + len, oct);
		अवरोध;
	हाल OCTEON_CN23XX_VF_VID:
		स_रखो(regbuf, 0, OCT_ETHTOOL_REGDUMP_LEN_23XX_VF);
		len += cn23xx_vf_पढ़ो_csr_reg(regbuf + len, oct);
		अवरोध;
	हाल OCTEON_CN68XX:
	हाल OCTEON_CN66XX:
		स_रखो(regbuf, 0, OCT_ETHTOOL_REGDUMP_LEN);
		len += cn6xxx_पढ़ो_csr_reg(regbuf + len, oct);
		len += cn6xxx_पढ़ो_config_reg(regbuf + len, oct);
		अवरोध;
	शेष:
		dev_err(&oct->pci_dev->dev, "%s Unknown chipid: %d\n",
			__func__, oct->chip_id);
	पूर्ण
पूर्ण

अटल u32 lio_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);

	वापस lio->oct_dev->priv_flags;
पूर्ण

अटल पूर्णांक lio_set_priv_flags(काष्ठा net_device *netdev, u32 flags)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	bool पूर्णांकr_by_tx_bytes = !!(flags & (0x1 << OCT_PRIV_FLAG_TX_BYTES));

	lio_set_priv_flag(lio->oct_dev, OCT_PRIV_FLAG_TX_BYTES,
			  पूर्णांकr_by_tx_bytes);
	वापस 0;
पूर्ण

अटल पूर्णांक lio_get_fecparam(काष्ठा net_device *netdev,
			    काष्ठा ethtool_fecparam *fec)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	fec->active_fec = ETHTOOL_FEC_NONE;
	fec->fec = ETHTOOL_FEC_NONE;

	अगर (oct->subप्रणाली_id == OCTEON_CN2350_25GB_SUBSYS_ID ||
	    oct->subप्रणाली_id == OCTEON_CN2360_25GB_SUBSYS_ID) अणु
		अगर (oct->no_speed_setting == 1)
			वापस 0;

		liquidio_get_fec(lio);
		fec->fec = (ETHTOOL_FEC_RS | ETHTOOL_FEC_OFF);
		अगर (oct->props[lio->अगरidx].fec == 1)
			fec->active_fec = ETHTOOL_FEC_RS;
		अन्यथा
			fec->active_fec = ETHTOOL_FEC_OFF;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lio_set_fecparam(काष्ठा net_device *netdev,
			    काष्ठा ethtool_fecparam *fec)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	अगर (oct->subप्रणाली_id == OCTEON_CN2350_25GB_SUBSYS_ID ||
	    oct->subप्रणाली_id == OCTEON_CN2360_25GB_SUBSYS_ID) अणु
		अगर (oct->no_speed_setting == 1)
			वापस -EOPNOTSUPP;

		अगर (fec->fec & ETHTOOL_FEC_OFF)
			liquidio_set_fec(lio, 0);
		अन्यथा अगर (fec->fec & ETHTOOL_FEC_RS)
			liquidio_set_fec(lio, 1);
		अन्यथा
			वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा LIO_ETHTOOL_COALESCE	(ETHTOOL_COALESCE_RX_USECS |		\
				 ETHTOOL_COALESCE_MAX_FRAMES |		\
				 ETHTOOL_COALESCE_USE_ADAPTIVE |	\
				 ETHTOOL_COALESCE_RX_MAX_FRAMES_LOW |	\
				 ETHTOOL_COALESCE_TX_MAX_FRAMES_LOW |	\
				 ETHTOOL_COALESCE_RX_MAX_FRAMES_HIGH |	\
				 ETHTOOL_COALESCE_TX_MAX_FRAMES_HIGH |	\
				 ETHTOOL_COALESCE_PKT_RATE_RX_USECS)

अटल स्थिर काष्ठा ethtool_ops lio_ethtool_ops = अणु
	.supported_coalesce_params = LIO_ETHTOOL_COALESCE,
	.get_link_ksettings	= lio_get_link_ksettings,
	.set_link_ksettings	= lio_set_link_ksettings,
	.get_fecparam		= lio_get_fecparam,
	.set_fecparam		= lio_set_fecparam,
	.get_link		= ethtool_op_get_link,
	.get_drvinfo		= lio_get_drvinfo,
	.get_ringparam		= lio_ethtool_get_ringparam,
	.set_ringparam		= lio_ethtool_set_ringparam,
	.get_channels		= lio_ethtool_get_channels,
	.set_channels		= lio_ethtool_set_channels,
	.set_phys_id		= lio_set_phys_id,
	.get_eeprom_len		= lio_get_eeprom_len,
	.get_eeprom		= lio_get_eeprom,
	.get_strings		= lio_get_strings,
	.get_ethtool_stats	= lio_get_ethtool_stats,
	.get_छोड़ोparam		= lio_get_छोड़ोparam,
	.set_छोड़ोparam		= lio_set_छोड़ोparam,
	.get_regs_len		= lio_get_regs_len,
	.get_regs		= lio_get_regs,
	.get_msglevel		= lio_get_msglevel,
	.set_msglevel		= lio_set_msglevel,
	.get_sset_count		= lio_get_sset_count,
	.get_coalesce		= lio_get_पूर्णांकr_coalesce,
	.set_coalesce		= lio_set_पूर्णांकr_coalesce,
	.get_priv_flags		= lio_get_priv_flags,
	.set_priv_flags		= lio_set_priv_flags,
	.get_ts_info		= lio_get_ts_info,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops lio_vf_ethtool_ops = अणु
	.supported_coalesce_params = LIO_ETHTOOL_COALESCE,
	.get_link_ksettings	= lio_get_link_ksettings,
	.get_link		= ethtool_op_get_link,
	.get_drvinfo		= lio_get_vf_drvinfo,
	.get_ringparam		= lio_ethtool_get_ringparam,
	.set_ringparam          = lio_ethtool_set_ringparam,
	.get_channels		= lio_ethtool_get_channels,
	.set_channels		= lio_ethtool_set_channels,
	.get_strings		= lio_vf_get_strings,
	.get_ethtool_stats	= lio_vf_get_ethtool_stats,
	.get_regs_len		= lio_get_regs_len,
	.get_regs		= lio_get_regs,
	.get_msglevel		= lio_get_msglevel,
	.set_msglevel		= lio_vf_set_msglevel,
	.get_sset_count		= lio_vf_get_sset_count,
	.get_coalesce		= lio_get_पूर्णांकr_coalesce,
	.set_coalesce		= lio_set_पूर्णांकr_coalesce,
	.get_priv_flags		= lio_get_priv_flags,
	.set_priv_flags		= lio_set_priv_flags,
	.get_ts_info		= lio_get_ts_info,
पूर्ण;

व्योम liquidio_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;

	अगर (OCTEON_CN23XX_VF(oct))
		netdev->ethtool_ops = &lio_vf_ethtool_ops;
	अन्यथा
		netdev->ethtool_ops = &lio_ethtool_ops;
पूर्ण
