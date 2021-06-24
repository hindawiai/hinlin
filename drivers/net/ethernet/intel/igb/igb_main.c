<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/slab.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/aer.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/etherdevice.h>
#अगर_घोषित CONFIG_IGB_DCA
#समावेश <linux/dca.h>
#पूर्ण_अगर
#समावेश <linux/i2c.h>
#समावेश "igb.h"

क्रमागत queue_mode अणु
	QUEUE_MODE_STRICT_PRIORITY,
	QUEUE_MODE_STREAM_RESERVATION,
पूर्ण;

क्रमागत tx_queue_prio अणु
	TX_QUEUE_PRIO_HIGH,
	TX_QUEUE_PRIO_LOW,
पूर्ण;

अक्षर igb_driver_name[] = "igb";
अटल स्थिर अक्षर igb_driver_string[] =
				"Intel(R) Gigabit Ethernet Network Driver";
अटल स्थिर अक्षर igb_copyright[] =
				"Copyright (c) 2007-2014 Intel Corporation.";

अटल स्थिर काष्ठा e1000_info *igb_info_tbl[] = अणु
	[board_82575] = &e1000_82575_info,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id igb_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I354_BACKPLANE_1GBPS) पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I354_SGMII) पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I354_BACKPLANE_2_5GBPS) पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I211_COPPER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_COPPER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_FIBER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_SERDES), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_SGMII), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_COPPER_FLASHLESS), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I210_SERDES_FLASHLESS), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I350_COPPER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I350_FIBER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I350_SERDES), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I350_SGMII), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_COPPER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_FIBER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_QUAD_FIBER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_SERDES), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_SGMII), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82580_COPPER_DUAL), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_DH89XXCC_SGMII), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_DH89XXCC_SERDES), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_DH89XXCC_BACKPLANE), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_DH89XXCC_SFP), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82576), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_NS), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_NS_SERDES), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_FIBER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_SERDES), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_SERDES_QUAD), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_QUAD_COPPER_ET2), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_QUAD_COPPER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82575EB_COPPER), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82575EB_FIBER_SERDES), board_82575 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82575GB_QUAD_COPPER), board_82575 पूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, igb_pci_tbl);

अटल पूर्णांक igb_setup_all_tx_resources(काष्ठा igb_adapter *);
अटल पूर्णांक igb_setup_all_rx_resources(काष्ठा igb_adapter *);
अटल व्योम igb_मुक्त_all_tx_resources(काष्ठा igb_adapter *);
अटल व्योम igb_मुक्त_all_rx_resources(काष्ठा igb_adapter *);
अटल व्योम igb_setup_mrqc(काष्ठा igb_adapter *);
अटल पूर्णांक igb_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम igb_हटाओ(काष्ठा pci_dev *pdev);
अटल पूर्णांक igb_sw_init(काष्ठा igb_adapter *);
पूर्णांक igb_खोलो(काष्ठा net_device *);
पूर्णांक igb_बंद(काष्ठा net_device *);
अटल व्योम igb_configure(काष्ठा igb_adapter *);
अटल व्योम igb_configure_tx(काष्ठा igb_adapter *);
अटल व्योम igb_configure_rx(काष्ठा igb_adapter *);
अटल व्योम igb_clean_all_tx_rings(काष्ठा igb_adapter *);
अटल व्योम igb_clean_all_rx_rings(काष्ठा igb_adapter *);
अटल व्योम igb_clean_tx_ring(काष्ठा igb_ring *);
अटल व्योम igb_clean_rx_ring(काष्ठा igb_ring *);
अटल व्योम igb_set_rx_mode(काष्ठा net_device *);
अटल व्योम igb_update_phy_info(काष्ठा समयr_list *);
अटल व्योम igb_watchकरोg(काष्ठा समयr_list *);
अटल व्योम igb_watchकरोg_task(काष्ठा work_काष्ठा *);
अटल netdev_tx_t igb_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *);
अटल व्योम igb_get_stats64(काष्ठा net_device *dev,
			    काष्ठा rtnl_link_stats64 *stats);
अटल पूर्णांक igb_change_mtu(काष्ठा net_device *, पूर्णांक);
अटल पूर्णांक igb_set_mac(काष्ठा net_device *, व्योम *);
अटल व्योम igb_set_uta(काष्ठा igb_adapter *adapter, bool set);
अटल irqवापस_t igb_पूर्णांकr(पूर्णांक irq, व्योम *);
अटल irqवापस_t igb_पूर्णांकr_msi(पूर्णांक irq, व्योम *);
अटल irqवापस_t igb_msix_other(पूर्णांक irq, व्योम *);
अटल irqवापस_t igb_msix_ring(पूर्णांक irq, व्योम *);
#अगर_घोषित CONFIG_IGB_DCA
अटल व्योम igb_update_dca(काष्ठा igb_q_vector *);
अटल व्योम igb_setup_dca(काष्ठा igb_adapter *);
#पूर्ण_अगर /* CONFIG_IGB_DCA */
अटल पूर्णांक igb_poll(काष्ठा napi_काष्ठा *, पूर्णांक);
अटल bool igb_clean_tx_irq(काष्ठा igb_q_vector *, पूर्णांक);
अटल पूर्णांक igb_clean_rx_irq(काष्ठा igb_q_vector *, पूर्णांक);
अटल पूर्णांक igb_ioctl(काष्ठा net_device *, काष्ठा अगरreq *, पूर्णांक cmd);
अटल व्योम igb_tx_समयout(काष्ठा net_device *, अचिन्हित पूर्णांक txqueue);
अटल व्योम igb_reset_task(काष्ठा work_काष्ठा *);
अटल व्योम igb_vlan_mode(काष्ठा net_device *netdev,
			  netdev_features_t features);
अटल पूर्णांक igb_vlan_rx_add_vid(काष्ठा net_device *, __be16, u16);
अटल पूर्णांक igb_vlan_rx_समाप्त_vid(काष्ठा net_device *, __be16, u16);
अटल व्योम igb_restore_vlan(काष्ठा igb_adapter *);
अटल व्योम igb_rar_set_index(काष्ठा igb_adapter *, u32);
अटल व्योम igb_ping_all_vfs(काष्ठा igb_adapter *);
अटल व्योम igb_msg_task(काष्ठा igb_adapter *);
अटल व्योम igb_vmm_control(काष्ठा igb_adapter *);
अटल पूर्णांक igb_set_vf_mac(काष्ठा igb_adapter *, पूर्णांक, अचिन्हित अक्षर *);
अटल व्योम igb_flush_mac_table(काष्ठा igb_adapter *);
अटल पूर्णांक igb_available_rars(काष्ठा igb_adapter *, u8);
अटल व्योम igb_set_शेष_mac_filter(काष्ठा igb_adapter *);
अटल पूर्णांक igb_uc_sync(काष्ठा net_device *, स्थिर अचिन्हित अक्षर *);
अटल पूर्णांक igb_uc_unsync(काष्ठा net_device *, स्थिर अचिन्हित अक्षर *);
अटल व्योम igb_restore_vf_multicasts(काष्ठा igb_adapter *adapter);
अटल पूर्णांक igb_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac);
अटल पूर्णांक igb_nकरो_set_vf_vlan(काष्ठा net_device *netdev,
			       पूर्णांक vf, u16 vlan, u8 qos, __be16 vlan_proto);
अटल पूर्णांक igb_nकरो_set_vf_bw(काष्ठा net_device *, पूर्णांक, पूर्णांक, पूर्णांक);
अटल पूर्णांक igb_nकरो_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf,
				   bool setting);
अटल पूर्णांक igb_nकरो_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf,
				bool setting);
अटल पूर्णांक igb_nकरो_get_vf_config(काष्ठा net_device *netdev, पूर्णांक vf,
				 काष्ठा अगरla_vf_info *ivi);
अटल व्योम igb_check_vf_rate_limit(काष्ठा igb_adapter *);
अटल व्योम igb_nfc_filter_निकास(काष्ठा igb_adapter *adapter);
अटल व्योम igb_nfc_filter_restore(काष्ठा igb_adapter *adapter);

#अगर_घोषित CONFIG_PCI_IOV
अटल पूर्णांक igb_vf_configure(काष्ठा igb_adapter *adapter, पूर्णांक vf);
अटल पूर्णांक igb_pci_enable_sriov(काष्ठा pci_dev *dev, पूर्णांक num_vfs);
अटल पूर्णांक igb_disable_sriov(काष्ठा pci_dev *dev);
अटल पूर्णांक igb_pci_disable_sriov(काष्ठा pci_dev *dev);
#पूर्ण_अगर

अटल पूर्णांक igb_suspend(काष्ठा device *);
अटल पूर्णांक igb_resume(काष्ठा device *);
अटल पूर्णांक igb_runसमय_suspend(काष्ठा device *dev);
अटल पूर्णांक igb_runसमय_resume(काष्ठा device *dev);
अटल पूर्णांक igb_runसमय_idle(काष्ठा device *dev);
अटल स्थिर काष्ठा dev_pm_ops igb_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(igb_suspend, igb_resume)
	SET_RUNTIME_PM_OPS(igb_runसमय_suspend, igb_runसमय_resume,
			igb_runसमय_idle)
पूर्ण;
अटल व्योम igb_shutकरोwn(काष्ठा pci_dev *);
अटल पूर्णांक igb_pci_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs);
#अगर_घोषित CONFIG_IGB_DCA
अटल पूर्णांक igb_notअगरy_dca(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल काष्ठा notअगरier_block dca_notअगरier = अणु
	.notअगरier_call	= igb_notअगरy_dca,
	.next		= शून्य,
	.priority	= 0
पूर्ण;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_IOV
अटल अचिन्हित पूर्णांक max_vfs;
module_param(max_vfs, uपूर्णांक, 0);
MODULE_PARM_DESC(max_vfs, "Maximum number of virtual functions to allocate per physical function");
#पूर्ण_अगर /* CONFIG_PCI_IOV */

अटल pci_ers_result_t igb_io_error_detected(काष्ठा pci_dev *,
		     pci_channel_state_t);
अटल pci_ers_result_t igb_io_slot_reset(काष्ठा pci_dev *);
अटल व्योम igb_io_resume(काष्ठा pci_dev *);

अटल स्थिर काष्ठा pci_error_handlers igb_err_handler = अणु
	.error_detected = igb_io_error_detected,
	.slot_reset = igb_io_slot_reset,
	.resume = igb_io_resume,
पूर्ण;

अटल व्योम igb_init_dmac(काष्ठा igb_adapter *adapter, u32 pba);

अटल काष्ठा pci_driver igb_driver = अणु
	.name     = igb_driver_name,
	.id_table = igb_pci_tbl,
	.probe    = igb_probe,
	.हटाओ   = igb_हटाओ,
#अगर_घोषित CONFIG_PM
	.driver.pm = &igb_pm_ops,
#पूर्ण_अगर
	.shutकरोwn = igb_shutकरोwn,
	.sriov_configure = igb_pci_sriov_configure,
	.err_handler = &igb_err_handler
पूर्ण;

MODULE_AUTHOR("Intel Corporation, <e1000-devel@lists.sourceforge.net>");
MODULE_DESCRIPTION("Intel(R) Gigabit Ethernet Network Driver");
MODULE_LICENSE("GPL v2");

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV|NETIF_MSG_PROBE|NETIF_MSG_LINK)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

काष्ठा igb_reg_info अणु
	u32 ofs;
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा igb_reg_info igb_reg_info_tbl[] = अणु

	/* General Registers */
	अणुE1000_CTRL, "CTRL"पूर्ण,
	अणुE1000_STATUS, "STATUS"पूर्ण,
	अणुE1000_CTRL_EXT, "CTRL_EXT"पूर्ण,

	/* Interrupt Registers */
	अणुE1000_ICR, "ICR"पूर्ण,

	/* RX Registers */
	अणुE1000_RCTL, "RCTL"पूर्ण,
	अणुE1000_RDLEN(0), "RDLEN"पूर्ण,
	अणुE1000_RDH(0), "RDH"पूर्ण,
	अणुE1000_RDT(0), "RDT"पूर्ण,
	अणुE1000_RXDCTL(0), "RXDCTL"पूर्ण,
	अणुE1000_RDBAL(0), "RDBAL"पूर्ण,
	अणुE1000_RDBAH(0), "RDBAH"पूर्ण,

	/* TX Registers */
	अणुE1000_TCTL, "TCTL"पूर्ण,
	अणुE1000_TDBAL(0), "TDBAL"पूर्ण,
	अणुE1000_TDBAH(0), "TDBAH"पूर्ण,
	अणुE1000_TDLEN(0), "TDLEN"पूर्ण,
	अणुE1000_TDH(0), "TDH"पूर्ण,
	अणुE1000_TDT(0), "TDT"पूर्ण,
	अणुE1000_TXDCTL(0), "TXDCTL"पूर्ण,
	अणुE1000_TDFH, "TDFH"पूर्ण,
	अणुE1000_TDFT, "TDFT"पूर्ण,
	अणुE1000_TDFHS, "TDFHS"पूर्ण,
	अणुE1000_TDFPC, "TDFPC"पूर्ण,

	/* List Terminator */
	अणुपूर्ण
पूर्ण;

/* igb_regdump - रेजिस्टर prपूर्णांकout routine */
अटल व्योम igb_regdump(काष्ठा e1000_hw *hw, काष्ठा igb_reg_info *reginfo)
अणु
	पूर्णांक n = 0;
	अक्षर rname[16];
	u32 regs[8];

	चयन (reginfo->ofs) अणु
	हाल E1000_RDLEN(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_RDLEN(n));
		अवरोध;
	हाल E1000_RDH(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_RDH(n));
		अवरोध;
	हाल E1000_RDT(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_RDT(n));
		अवरोध;
	हाल E1000_RXDCTL(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_RXDCTL(n));
		अवरोध;
	हाल E1000_RDBAL(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_RDBAL(n));
		अवरोध;
	हाल E1000_RDBAH(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_RDBAH(n));
		अवरोध;
	हाल E1000_TDBAL(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_TDBAL(n));
		अवरोध;
	हाल E1000_TDBAH(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_TDBAH(n));
		अवरोध;
	हाल E1000_TDLEN(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_TDLEN(n));
		अवरोध;
	हाल E1000_TDH(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_TDH(n));
		अवरोध;
	हाल E1000_TDT(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_TDT(n));
		अवरोध;
	हाल E1000_TXDCTL(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(E1000_TXDCTL(n));
		अवरोध;
	शेष:
		pr_info("%-15s %08x\n", reginfo->name, rd32(reginfo->ofs));
		वापस;
	पूर्ण

	snम_लिखो(rname, 16, "%s%s", reginfo->name, "[0-3]");
	pr_info("%-15s %08x %08x %08x %08x\n", rname, regs[0], regs[1],
		regs[2], regs[3]);
पूर्ण

/* igb_dump - Prपूर्णांक रेजिस्टरs, Tx-rings and Rx-rings */
अटल व्योम igb_dump(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा igb_reg_info *reginfo;
	काष्ठा igb_ring *tx_ring;
	जोड़ e1000_adv_tx_desc *tx_desc;
	काष्ठा my_u0 अणु u64 a; u64 b; पूर्ण *u0;
	काष्ठा igb_ring *rx_ring;
	जोड़ e1000_adv_rx_desc *rx_desc;
	u32 staterr;
	u16 i, n;

	अगर (!netअगर_msg_hw(adapter))
		वापस;

	/* Prपूर्णांक netdevice Info */
	अगर (netdev) अणु
		dev_info(&adapter->pdev->dev, "Net device Info\n");
		pr_info("Device Name     state            trans_start\n");
		pr_info("%-15s %016lX %016lX\n", netdev->name,
			netdev->state, dev_trans_start(netdev));
	पूर्ण

	/* Prपूर्णांक Registers */
	dev_info(&adapter->pdev->dev, "Register Dump\n");
	pr_info(" Register Name   Value\n");
	क्रम (reginfo = (काष्ठा igb_reg_info *)igb_reg_info_tbl;
	     reginfo->name; reginfo++) अणु
		igb_regdump(hw, reginfo);
	पूर्ण

	/* Prपूर्णांक TX Ring Summary */
	अगर (!netdev || !netअगर_running(netdev))
		जाओ निकास;

	dev_info(&adapter->pdev->dev, "TX Rings Summary\n");
	pr_info("Queue [NTU] [NTC] [bi(ntc)->dma  ] leng ntw timestamp\n");
	क्रम (n = 0; n < adapter->num_tx_queues; n++) अणु
		काष्ठा igb_tx_buffer *buffer_info;
		tx_ring = adapter->tx_ring[n];
		buffer_info = &tx_ring->tx_buffer_info[tx_ring->next_to_clean];
		pr_info(" %5d %5X %5X %016llX %04X %p %016llX\n",
			n, tx_ring->next_to_use, tx_ring->next_to_clean,
			(u64)dma_unmap_addr(buffer_info, dma),
			dma_unmap_len(buffer_info, len),
			buffer_info->next_to_watch,
			(u64)buffer_info->समय_stamp);
	पूर्ण

	/* Prपूर्णांक TX Rings */
	अगर (!netअगर_msg_tx_करोne(adapter))
		जाओ rx_ring_summary;

	dev_info(&adapter->pdev->dev, "TX Rings Dump\n");

	/* Transmit Descriptor Formats
	 *
	 * Advanced Transmit Descriptor
	 *   +--------------------------------------------------------------+
	 * 0 |         Buffer Address [63:0]                                |
	 *   +--------------------------------------------------------------+
	 * 8 | PAYLEN  | PORTS  |CC|IDX | STA | DCMD  |DTYP|MAC|RSV| DTALEN |
	 *   +--------------------------------------------------------------+
	 *   63      46 45    40 39 38 36 35 32 31   24             15       0
	 */

	क्रम (n = 0; n < adapter->num_tx_queues; n++) अणु
		tx_ring = adapter->tx_ring[n];
		pr_info("------------------------------------\n");
		pr_info("TX QUEUE INDEX = %d\n", tx_ring->queue_index);
		pr_info("------------------------------------\n");
		pr_info("T [desc]     [address 63:0  ] [PlPOCIStDDM Ln] [bi->dma       ] leng  ntw timestamp        bi->skb\n");

		क्रम (i = 0; tx_ring->desc && (i < tx_ring->count); i++) अणु
			स्थिर अक्षर *next_desc;
			काष्ठा igb_tx_buffer *buffer_info;
			tx_desc = IGB_TX_DESC(tx_ring, i);
			buffer_info = &tx_ring->tx_buffer_info[i];
			u0 = (काष्ठा my_u0 *)tx_desc;
			अगर (i == tx_ring->next_to_use &&
			    i == tx_ring->next_to_clean)
				next_desc = " NTC/U";
			अन्यथा अगर (i == tx_ring->next_to_use)
				next_desc = " NTU";
			अन्यथा अगर (i == tx_ring->next_to_clean)
				next_desc = " NTC";
			अन्यथा
				next_desc = "";

			pr_info("T [0x%03X]    %016llX %016llX %016llX %04X  %p %016llX %p%s\n",
				i, le64_to_cpu(u0->a),
				le64_to_cpu(u0->b),
				(u64)dma_unmap_addr(buffer_info, dma),
				dma_unmap_len(buffer_info, len),
				buffer_info->next_to_watch,
				(u64)buffer_info->समय_stamp,
				buffer_info->skb, next_desc);

			अगर (netअगर_msg_pktdata(adapter) && buffer_info->skb)
				prपूर्णांक_hex_dump(KERN_INFO, "",
					DUMP_PREFIX_ADDRESS,
					16, 1, buffer_info->skb->data,
					dma_unmap_len(buffer_info, len),
					true);
		पूर्ण
	पूर्ण

	/* Prपूर्णांक RX Rings Summary */
rx_ring_summary:
	dev_info(&adapter->pdev->dev, "RX Rings Summary\n");
	pr_info("Queue [NTU] [NTC]\n");
	क्रम (n = 0; n < adapter->num_rx_queues; n++) अणु
		rx_ring = adapter->rx_ring[n];
		pr_info(" %5d %5X %5X\n",
			n, rx_ring->next_to_use, rx_ring->next_to_clean);
	पूर्ण

	/* Prपूर्णांक RX Rings */
	अगर (!netअगर_msg_rx_status(adapter))
		जाओ निकास;

	dev_info(&adapter->pdev->dev, "RX Rings Dump\n");

	/* Advanced Receive Descriptor (Read) Format
	 *    63                                           1        0
	 *    +-----------------------------------------------------+
	 *  0 |       Packet Buffer Address [63:1]           |A0/NSE|
	 *    +----------------------------------------------+------+
	 *  8 |       Header Buffer Address [63:1]           |  DD  |
	 *    +-----------------------------------------------------+
	 *
	 *
	 * Advanced Receive Descriptor (Write-Back) Format
	 *
	 *   63       48 47    32 31  30      21 20 17 16   4 3     0
	 *   +------------------------------------------------------+
	 * 0 | Packet     IP     |SPH| HDR_LEN   | RSV|Packet|  RSS |
	 *   | Checksum   Ident  |   |           |    | Type | Type |
	 *   +------------------------------------------------------+
	 * 8 | VLAN Tag | Length | Extended Error | Extended Status |
	 *   +------------------------------------------------------+
	 *   63       48 47    32 31            20 19               0
	 */

	क्रम (n = 0; n < adapter->num_rx_queues; n++) अणु
		rx_ring = adapter->rx_ring[n];
		pr_info("------------------------------------\n");
		pr_info("RX QUEUE INDEX = %d\n", rx_ring->queue_index);
		pr_info("------------------------------------\n");
		pr_info("R  [desc]      [ PktBuf     A0] [  HeadBuf   DD] [bi->dma       ] [bi->skb] <-- Adv Rx Read format\n");
		pr_info("RWB[desc]      [PcsmIpSHl PtRs] [vl er S cks ln] ---------------- [bi->skb] <-- Adv Rx Write-Back format\n");

		क्रम (i = 0; i < rx_ring->count; i++) अणु
			स्थिर अक्षर *next_desc;
			काष्ठा igb_rx_buffer *buffer_info;
			buffer_info = &rx_ring->rx_buffer_info[i];
			rx_desc = IGB_RX_DESC(rx_ring, i);
			u0 = (काष्ठा my_u0 *)rx_desc;
			staterr = le32_to_cpu(rx_desc->wb.upper.status_error);

			अगर (i == rx_ring->next_to_use)
				next_desc = " NTU";
			अन्यथा अगर (i == rx_ring->next_to_clean)
				next_desc = " NTC";
			अन्यथा
				next_desc = "";

			अगर (staterr & E1000_RXD_STAT_DD) अणु
				/* Descriptor Done */
				pr_info("%s[0x%03X]     %016llX %016llX ---------------- %s\n",
					"RWB", i,
					le64_to_cpu(u0->a),
					le64_to_cpu(u0->b),
					next_desc);
			पूर्ण अन्यथा अणु
				pr_info("%s[0x%03X]     %016llX %016llX %016llX %s\n",
					"R  ", i,
					le64_to_cpu(u0->a),
					le64_to_cpu(u0->b),
					(u64)buffer_info->dma,
					next_desc);

				अगर (netअगर_msg_pktdata(adapter) &&
				    buffer_info->dma && buffer_info->page) अणु
					prपूर्णांक_hex_dump(KERN_INFO, "",
					  DUMP_PREFIX_ADDRESS,
					  16, 1,
					  page_address(buffer_info->page) +
						      buffer_info->page_offset,
					  igb_rx_bufsz(rx_ring), true);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

निकास:
	वापस;
पूर्ण

/**
 *  igb_get_i2c_data - Reads the I2C SDA data bit
 *  @data: opaque poपूर्णांकer to adapter काष्ठा
 *
 *  Returns the I2C data bit value
 **/
अटल पूर्णांक igb_get_i2c_data(व्योम *data)
अणु
	काष्ठा igb_adapter *adapter = (काष्ठा igb_adapter *)data;
	काष्ठा e1000_hw *hw = &adapter->hw;
	s32 i2cctl = rd32(E1000_I2CPARAMS);

	वापस !!(i2cctl & E1000_I2C_DATA_IN);
पूर्ण

/**
 *  igb_set_i2c_data - Sets the I2C data bit
 *  @data: poपूर्णांकer to hardware काष्ठाure
 *  @state: I2C data value (0 or 1) to set
 *
 *  Sets the I2C data bit
 **/
अटल व्योम igb_set_i2c_data(व्योम *data, पूर्णांक state)
अणु
	काष्ठा igb_adapter *adapter = (काष्ठा igb_adapter *)data;
	काष्ठा e1000_hw *hw = &adapter->hw;
	s32 i2cctl = rd32(E1000_I2CPARAMS);

	अगर (state)
		i2cctl |= E1000_I2C_DATA_OUT;
	अन्यथा
		i2cctl &= ~E1000_I2C_DATA_OUT;

	i2cctl &= ~E1000_I2C_DATA_OE_N;
	i2cctl |= E1000_I2C_CLK_OE_N;
	wr32(E1000_I2CPARAMS, i2cctl);
	wrfl();

पूर्ण

/**
 *  igb_set_i2c_clk - Sets the I2C SCL घड़ी
 *  @data: poपूर्णांकer to hardware काष्ठाure
 *  @state: state to set घड़ी
 *
 *  Sets the I2C घड़ी line to state
 **/
अटल व्योम igb_set_i2c_clk(व्योम *data, पूर्णांक state)
अणु
	काष्ठा igb_adapter *adapter = (काष्ठा igb_adapter *)data;
	काष्ठा e1000_hw *hw = &adapter->hw;
	s32 i2cctl = rd32(E1000_I2CPARAMS);

	अगर (state) अणु
		i2cctl |= E1000_I2C_CLK_OUT;
		i2cctl &= ~E1000_I2C_CLK_OE_N;
	पूर्ण अन्यथा अणु
		i2cctl &= ~E1000_I2C_CLK_OUT;
		i2cctl &= ~E1000_I2C_CLK_OE_N;
	पूर्ण
	wr32(E1000_I2CPARAMS, i2cctl);
	wrfl();
पूर्ण

/**
 *  igb_get_i2c_clk - Gets the I2C SCL घड़ी state
 *  @data: poपूर्णांकer to hardware काष्ठाure
 *
 *  Gets the I2C घड़ी state
 **/
अटल पूर्णांक igb_get_i2c_clk(व्योम *data)
अणु
	काष्ठा igb_adapter *adapter = (काष्ठा igb_adapter *)data;
	काष्ठा e1000_hw *hw = &adapter->hw;
	s32 i2cctl = rd32(E1000_I2CPARAMS);

	वापस !!(i2cctl & E1000_I2C_CLK_IN);
पूर्ण

अटल स्थिर काष्ठा i2c_algo_bit_data igb_i2c_algo = अणु
	.setsda		= igb_set_i2c_data,
	.setscl		= igb_set_i2c_clk,
	.माला_लोda		= igb_get_i2c_data,
	.माला_लोcl		= igb_get_i2c_clk,
	.udelay		= 5,
	.समयout	= 20,
पूर्ण;

/**
 *  igb_get_hw_dev - वापस device
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  used by hardware layer to prपूर्णांक debugging inक्रमmation
 **/
काष्ठा net_device *igb_get_hw_dev(काष्ठा e1000_hw *hw)
अणु
	काष्ठा igb_adapter *adapter = hw->back;
	वापस adapter->netdev;
पूर्ण

/**
 *  igb_init_module - Driver Registration Routine
 *
 *  igb_init_module is the first routine called when the driver is
 *  loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/
अटल पूर्णांक __init igb_init_module(व्योम)
अणु
	पूर्णांक ret;

	pr_info("%s\n", igb_driver_string);
	pr_info("%s\n", igb_copyright);

#अगर_घोषित CONFIG_IGB_DCA
	dca_रेजिस्टर_notअगरy(&dca_notअगरier);
#पूर्ण_अगर
	ret = pci_रेजिस्टर_driver(&igb_driver);
	वापस ret;
पूर्ण

module_init(igb_init_module);

/**
 *  igb_निकास_module - Driver Exit Cleanup Routine
 *
 *  igb_निकास_module is called just beक्रमe the driver is हटाओd
 *  from memory.
 **/
अटल व्योम __निकास igb_निकास_module(व्योम)
अणु
#अगर_घोषित CONFIG_IGB_DCA
	dca_unरेजिस्टर_notअगरy(&dca_notअगरier);
#पूर्ण_अगर
	pci_unरेजिस्टर_driver(&igb_driver);
पूर्ण

module_निकास(igb_निकास_module);

#घोषणा Q_IDX_82576(i) (((i & 0x1) << 3) + (i >> 1))
/**
 *  igb_cache_ring_रेजिस्टर - Descriptor ring to रेजिस्टर mapping
 *  @adapter: board निजी काष्ठाure to initialize
 *
 *  Once we know the feature-set enabled क्रम the device, we'll cache
 *  the रेजिस्टर offset the descriptor ring is asचिन्हित to.
 **/
अटल व्योम igb_cache_ring_रेजिस्टर(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक i = 0, j = 0;
	u32 rbase_offset = adapter->vfs_allocated_count;

	चयन (adapter->hw.mac.type) अणु
	हाल e1000_82576:
		/* The queues are allocated क्रम भवization such that VF 0
		 * is allocated queues 0 and 8, VF 1 queues 1 and 9, etc.
		 * In order to aव्योम collision we start at the first मुक्त queue
		 * and जारी consuming queues in the same sequence
		 */
		अगर (adapter->vfs_allocated_count) अणु
			क्रम (; i < adapter->rss_queues; i++)
				adapter->rx_ring[i]->reg_idx = rbase_offset +
							       Q_IDX_82576(i);
		पूर्ण
		fallthrough;
	हाल e1000_82575:
	हाल e1000_82580:
	हाल e1000_i350:
	हाल e1000_i354:
	हाल e1000_i210:
	हाल e1000_i211:
	शेष:
		क्रम (; i < adapter->num_rx_queues; i++)
			adapter->rx_ring[i]->reg_idx = rbase_offset + i;
		क्रम (; j < adapter->num_tx_queues; j++)
			adapter->tx_ring[j]->reg_idx = rbase_offset + j;
		अवरोध;
	पूर्ण
पूर्ण

u32 igb_rd32(काष्ठा e1000_hw *hw, u32 reg)
अणु
	काष्ठा igb_adapter *igb = container_of(hw, काष्ठा igb_adapter, hw);
	u8 __iomem *hw_addr = READ_ONCE(hw->hw_addr);
	u32 value = 0;

	अगर (E1000_REMOVED(hw_addr))
		वापस ~value;

	value = पढ़ोl(&hw_addr[reg]);

	/* पढ़ोs should not वापस all F's */
	अगर (!(~value) && (!reg || !(~पढ़ोl(hw_addr)))) अणु
		काष्ठा net_device *netdev = igb->netdev;
		hw->hw_addr = शून्य;
		netdev_err(netdev, "PCIe link lost\n");
		WARN(pci_device_is_present(igb->pdev),
		     "igb: Failed to read reg 0x%x!\n", reg);
	पूर्ण

	वापस value;
पूर्ण

/**
 *  igb_ग_लिखो_ivar - configure ivar क्रम given MSI-X vector
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msix_vector: vector number we are allocating to a given ring
 *  @index: row index of IVAR रेजिस्टर to ग_लिखो within IVAR table
 *  @offset: column offset of in IVAR, should be multiple of 8
 *
 *  This function is पूर्णांकended to handle the writing of the IVAR रेजिस्टर
 *  क्रम adapters 82576 and newer.  The IVAR table consists of 2 columns,
 *  each containing an cause allocation क्रम an Rx and Tx ring, and a
 *  variable number of rows depending on the number of queues supported.
 **/
अटल व्योम igb_ग_लिखो_ivar(काष्ठा e1000_hw *hw, पूर्णांक msix_vector,
			   पूर्णांक index, पूर्णांक offset)
अणु
	u32 ivar = array_rd32(E1000_IVAR0, index);

	/* clear any bits that are currently set */
	ivar &= ~((u32)0xFF << offset);

	/* ग_लिखो vector and valid bit */
	ivar |= (msix_vector | E1000_IVAR_VALID) << offset;

	array_wr32(E1000_IVAR0, index, ivar);
पूर्ण

#घोषणा IGB_N0_QUEUE -1
अटल व्योम igb_assign_vector(काष्ठा igb_q_vector *q_vector, पूर्णांक msix_vector)
अणु
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक rx_queue = IGB_N0_QUEUE;
	पूर्णांक tx_queue = IGB_N0_QUEUE;
	u32 msixbm = 0;

	अगर (q_vector->rx.ring)
		rx_queue = q_vector->rx.ring->reg_idx;
	अगर (q_vector->tx.ring)
		tx_queue = q_vector->tx.ring->reg_idx;

	चयन (hw->mac.type) अणु
	हाल e1000_82575:
		/* The 82575 assigns vectors using a biपंचांगask, which matches the
		 * biपंचांगask क्रम the EICR/EIMS/EIMC रेजिस्टरs.  To assign one
		 * or more queues to a vector, we ग_लिखो the appropriate bits
		 * पूर्णांकo the MSIXBM रेजिस्टर क्रम that vector.
		 */
		अगर (rx_queue > IGB_N0_QUEUE)
			msixbm = E1000_EICR_RX_QUEUE0 << rx_queue;
		अगर (tx_queue > IGB_N0_QUEUE)
			msixbm |= E1000_EICR_TX_QUEUE0 << tx_queue;
		अगर (!(adapter->flags & IGB_FLAG_HAS_MSIX) && msix_vector == 0)
			msixbm |= E1000_EIMS_OTHER;
		array_wr32(E1000_MSIXBM(0), msix_vector, msixbm);
		q_vector->eims_value = msixbm;
		अवरोध;
	हाल e1000_82576:
		/* 82576 uses a table that essentially consists of 2 columns
		 * with 8 rows.  The ordering is column-major so we use the
		 * lower 3 bits as the row index, and the 4th bit as the
		 * column offset.
		 */
		अगर (rx_queue > IGB_N0_QUEUE)
			igb_ग_लिखो_ivar(hw, msix_vector,
				       rx_queue & 0x7,
				       (rx_queue & 0x8) << 1);
		अगर (tx_queue > IGB_N0_QUEUE)
			igb_ग_लिखो_ivar(hw, msix_vector,
				       tx_queue & 0x7,
				       ((tx_queue & 0x8) << 1) + 8);
		q_vector->eims_value = BIT(msix_vector);
		अवरोध;
	हाल e1000_82580:
	हाल e1000_i350:
	हाल e1000_i354:
	हाल e1000_i210:
	हाल e1000_i211:
		/* On 82580 and newer adapters the scheme is similar to 82576
		 * however instead of ordering column-major we have things
		 * ordered row-major.  So we traverse the table by using
		 * bit 0 as the column offset, and the reमुख्यing bits as the
		 * row index.
		 */
		अगर (rx_queue > IGB_N0_QUEUE)
			igb_ग_लिखो_ivar(hw, msix_vector,
				       rx_queue >> 1,
				       (rx_queue & 0x1) << 4);
		अगर (tx_queue > IGB_N0_QUEUE)
			igb_ग_लिखो_ivar(hw, msix_vector,
				       tx_queue >> 1,
				       ((tx_queue & 0x1) << 4) + 8);
		q_vector->eims_value = BIT(msix_vector);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	/* add q_vector eims value to global eims_enable_mask */
	adapter->eims_enable_mask |= q_vector->eims_value;

	/* configure q_vector to set itr on first पूर्णांकerrupt */
	q_vector->set_itr = 1;
पूर्ण

/**
 *  igb_configure_msix - Configure MSI-X hardware
 *  @adapter: board निजी काष्ठाure to initialize
 *
 *  igb_configure_msix sets up the hardware to properly
 *  generate MSI-X पूर्णांकerrupts.
 **/
अटल व्योम igb_configure_msix(काष्ठा igb_adapter *adapter)
अणु
	u32 पंचांगp;
	पूर्णांक i, vector = 0;
	काष्ठा e1000_hw *hw = &adapter->hw;

	adapter->eims_enable_mask = 0;

	/* set vector क्रम other causes, i.e. link changes */
	चयन (hw->mac.type) अणु
	हाल e1000_82575:
		पंचांगp = rd32(E1000_CTRL_EXT);
		/* enable MSI-X PBA support*/
		पंचांगp |= E1000_CTRL_EXT_PBA_CLR;

		/* Auto-Mask पूर्णांकerrupts upon ICR पढ़ो. */
		पंचांगp |= E1000_CTRL_EXT_EIAME;
		पंचांगp |= E1000_CTRL_EXT_IRCA;

		wr32(E1000_CTRL_EXT, पंचांगp);

		/* enable msix_other पूर्णांकerrupt */
		array_wr32(E1000_MSIXBM(0), vector++, E1000_EIMS_OTHER);
		adapter->eims_other = E1000_EIMS_OTHER;

		अवरोध;

	हाल e1000_82576:
	हाल e1000_82580:
	हाल e1000_i350:
	हाल e1000_i354:
	हाल e1000_i210:
	हाल e1000_i211:
		/* Turn on MSI-X capability first, or our settings
		 * won't stick.  And it will take days to debug.
		 */
		wr32(E1000_GPIE, E1000_GPIE_MSIX_MODE |
		     E1000_GPIE_PBA | E1000_GPIE_EIAME |
		     E1000_GPIE_NSICR);

		/* enable msix_other पूर्णांकerrupt */
		adapter->eims_other = BIT(vector);
		पंचांगp = (vector++ | E1000_IVAR_VALID) << 8;

		wr32(E1000_IVAR_MISC, पंचांगp);
		अवरोध;
	शेष:
		/* करो nothing, since nothing अन्यथा supports MSI-X */
		अवरोध;
	पूर्ण /* चयन (hw->mac.type) */

	adapter->eims_enable_mask |= adapter->eims_other;

	क्रम (i = 0; i < adapter->num_q_vectors; i++)
		igb_assign_vector(adapter->q_vector[i], vector++);

	wrfl();
पूर्ण

/**
 *  igb_request_msix - Initialize MSI-X पूर्णांकerrupts
 *  @adapter: board निजी काष्ठाure to initialize
 *
 *  igb_request_msix allocates MSI-X vectors and requests पूर्णांकerrupts from the
 *  kernel.
 **/
अटल पूर्णांक igb_request_msix(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i, err = 0, vector = 0, मुक्त_vector = 0;

	err = request_irq(adapter->msix_entries[vector].vector,
			  igb_msix_other, 0, netdev->name, adapter);
	अगर (err)
		जाओ err_out;

	क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
		काष्ठा igb_q_vector *q_vector = adapter->q_vector[i];

		vector++;

		q_vector->itr_रेजिस्टर = adapter->io_addr + E1000_EITR(vector);

		अगर (q_vector->rx.ring && q_vector->tx.ring)
			प्र_लिखो(q_vector->name, "%s-TxRx-%u", netdev->name,
				q_vector->rx.ring->queue_index);
		अन्यथा अगर (q_vector->tx.ring)
			प्र_लिखो(q_vector->name, "%s-tx-%u", netdev->name,
				q_vector->tx.ring->queue_index);
		अन्यथा अगर (q_vector->rx.ring)
			प्र_लिखो(q_vector->name, "%s-rx-%u", netdev->name,
				q_vector->rx.ring->queue_index);
		अन्यथा
			प्र_लिखो(q_vector->name, "%s-unused", netdev->name);

		err = request_irq(adapter->msix_entries[vector].vector,
				  igb_msix_ring, 0, q_vector->name,
				  q_vector);
		अगर (err)
			जाओ err_मुक्त;
	पूर्ण

	igb_configure_msix(adapter);
	वापस 0;

err_मुक्त:
	/* मुक्त alपढ़ोy asचिन्हित IRQs */
	मुक्त_irq(adapter->msix_entries[मुक्त_vector++].vector, adapter);

	vector--;
	क्रम (i = 0; i < vector; i++) अणु
		मुक्त_irq(adapter->msix_entries[मुक्त_vector++].vector,
			 adapter->q_vector[i]);
	पूर्ण
err_out:
	वापस err;
पूर्ण

/**
 *  igb_मुक्त_q_vector - Free memory allocated क्रम specअगरic पूर्णांकerrupt vector
 *  @adapter: board निजी काष्ठाure to initialize
 *  @v_idx: Index of vector to be मुक्तd
 *
 *  This function मुक्तs the memory allocated to the q_vector.
 **/
अटल व्योम igb_मुक्त_q_vector(काष्ठा igb_adapter *adapter, पूर्णांक v_idx)
अणु
	काष्ठा igb_q_vector *q_vector = adapter->q_vector[v_idx];

	adapter->q_vector[v_idx] = शून्य;

	/* igb_get_stats64() might access the rings on this vector,
	 * we must रुको a grace period beक्रमe मुक्तing it.
	 */
	अगर (q_vector)
		kमुक्त_rcu(q_vector, rcu);
पूर्ण

/**
 *  igb_reset_q_vector - Reset config क्रम पूर्णांकerrupt vector
 *  @adapter: board निजी काष्ठाure to initialize
 *  @v_idx: Index of vector to be reset
 *
 *  If NAPI is enabled it will delete any references to the
 *  NAPI काष्ठा. This is preparation क्रम igb_मुक्त_q_vector.
 **/
अटल व्योम igb_reset_q_vector(काष्ठा igb_adapter *adapter, पूर्णांक v_idx)
अणु
	काष्ठा igb_q_vector *q_vector = adapter->q_vector[v_idx];

	/* Coming from igb_set_पूर्णांकerrupt_capability, the vectors are not yet
	 * allocated. So, q_vector is शून्य so we should stop here.
	 */
	अगर (!q_vector)
		वापस;

	अगर (q_vector->tx.ring)
		adapter->tx_ring[q_vector->tx.ring->queue_index] = शून्य;

	अगर (q_vector->rx.ring)
		adapter->rx_ring[q_vector->rx.ring->queue_index] = शून्य;

	netअगर_napi_del(&q_vector->napi);

पूर्ण

अटल व्योम igb_reset_पूर्णांकerrupt_capability(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक v_idx = adapter->num_q_vectors;

	अगर (adapter->flags & IGB_FLAG_HAS_MSIX)
		pci_disable_msix(adapter->pdev);
	अन्यथा अगर (adapter->flags & IGB_FLAG_HAS_MSI)
		pci_disable_msi(adapter->pdev);

	जबतक (v_idx--)
		igb_reset_q_vector(adapter, v_idx);
पूर्ण

/**
 *  igb_मुक्त_q_vectors - Free memory allocated क्रम पूर्णांकerrupt vectors
 *  @adapter: board निजी काष्ठाure to initialize
 *
 *  This function मुक्तs the memory allocated to the q_vectors.  In addition अगर
 *  NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 *  to मुक्तing the q_vector.
 **/
अटल व्योम igb_मुक्त_q_vectors(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक v_idx = adapter->num_q_vectors;

	adapter->num_tx_queues = 0;
	adapter->num_rx_queues = 0;
	adapter->num_q_vectors = 0;

	जबतक (v_idx--) अणु
		igb_reset_q_vector(adapter, v_idx);
		igb_मुक्त_q_vector(adapter, v_idx);
	पूर्ण
पूर्ण

/**
 *  igb_clear_पूर्णांकerrupt_scheme - reset the device to a state of no पूर्णांकerrupts
 *  @adapter: board निजी काष्ठाure to initialize
 *
 *  This function resets the device so that it has 0 Rx queues, Tx queues, and
 *  MSI-X पूर्णांकerrupts allocated.
 */
अटल व्योम igb_clear_पूर्णांकerrupt_scheme(काष्ठा igb_adapter *adapter)
अणु
	igb_मुक्त_q_vectors(adapter);
	igb_reset_पूर्णांकerrupt_capability(adapter);
पूर्ण

/**
 *  igb_set_पूर्णांकerrupt_capability - set MSI or MSI-X अगर supported
 *  @adapter: board निजी काष्ठाure to initialize
 *  @msix: boolean value of MSIX capability
 *
 *  Attempt to configure पूर्णांकerrupts using the best available
 *  capabilities of the hardware and kernel.
 **/
अटल व्योम igb_set_पूर्णांकerrupt_capability(काष्ठा igb_adapter *adapter, bool msix)
अणु
	पूर्णांक err;
	पूर्णांक numvecs, i;

	अगर (!msix)
		जाओ msi_only;
	adapter->flags |= IGB_FLAG_HAS_MSIX;

	/* Number of supported queues. */
	adapter->num_rx_queues = adapter->rss_queues;
	अगर (adapter->vfs_allocated_count)
		adapter->num_tx_queues = 1;
	अन्यथा
		adapter->num_tx_queues = adapter->rss_queues;

	/* start with one vector क्रम every Rx queue */
	numvecs = adapter->num_rx_queues;

	/* अगर Tx handler is separate add 1 क्रम every Tx queue */
	अगर (!(adapter->flags & IGB_FLAG_QUEUE_PAIRS))
		numvecs += adapter->num_tx_queues;

	/* store the number of vectors reserved क्रम queues */
	adapter->num_q_vectors = numvecs;

	/* add 1 vector क्रम link status पूर्णांकerrupts */
	numvecs++;
	क्रम (i = 0; i < numvecs; i++)
		adapter->msix_entries[i].entry = i;

	err = pci_enable_msix_range(adapter->pdev,
				    adapter->msix_entries,
				    numvecs,
				    numvecs);
	अगर (err > 0)
		वापस;

	igb_reset_पूर्णांकerrupt_capability(adapter);

	/* If we can't करो MSI-X, try MSI */
msi_only:
	adapter->flags &= ~IGB_FLAG_HAS_MSIX;
#अगर_घोषित CONFIG_PCI_IOV
	/* disable SR-IOV क्रम non MSI-X configurations */
	अगर (adapter->vf_data) अणु
		काष्ठा e1000_hw *hw = &adapter->hw;
		/* disable iov and allow समय क्रम transactions to clear */
		pci_disable_sriov(adapter->pdev);
		msleep(500);

		kमुक्त(adapter->vf_mac_list);
		adapter->vf_mac_list = शून्य;
		kमुक्त(adapter->vf_data);
		adapter->vf_data = शून्य;
		wr32(E1000_IOVCTL, E1000_IOVCTL_REUSE_VFQ);
		wrfl();
		msleep(100);
		dev_info(&adapter->pdev->dev, "IOV Disabled\n");
	पूर्ण
#पूर्ण_अगर
	adapter->vfs_allocated_count = 0;
	adapter->rss_queues = 1;
	adapter->flags |= IGB_FLAG_QUEUE_PAIRS;
	adapter->num_rx_queues = 1;
	adapter->num_tx_queues = 1;
	adapter->num_q_vectors = 1;
	अगर (!pci_enable_msi(adapter->pdev))
		adapter->flags |= IGB_FLAG_HAS_MSI;
पूर्ण

अटल व्योम igb_add_ring(काष्ठा igb_ring *ring,
			 काष्ठा igb_ring_container *head)
अणु
	head->ring = ring;
	head->count++;
पूर्ण

/**
 *  igb_alloc_q_vector - Allocate memory क्रम a single पूर्णांकerrupt vector
 *  @adapter: board निजी काष्ठाure to initialize
 *  @v_count: q_vectors allocated on adapter, used क्रम ring पूर्णांकerleaving
 *  @v_idx: index of vector in adapter काष्ठा
 *  @txr_count: total number of Tx rings to allocate
 *  @txr_idx: index of first Tx ring to allocate
 *  @rxr_count: total number of Rx rings to allocate
 *  @rxr_idx: index of first Rx ring to allocate
 *
 *  We allocate one q_vector.  If allocation fails we वापस -ENOMEM.
 **/
अटल पूर्णांक igb_alloc_q_vector(काष्ठा igb_adapter *adapter,
			      पूर्णांक v_count, पूर्णांक v_idx,
			      पूर्णांक txr_count, पूर्णांक txr_idx,
			      पूर्णांक rxr_count, पूर्णांक rxr_idx)
अणु
	काष्ठा igb_q_vector *q_vector;
	काष्ठा igb_ring *ring;
	पूर्णांक ring_count;
	माप_प्रकार size;

	/* igb only supports 1 Tx and/or 1 Rx queue per vector */
	अगर (txr_count > 1 || rxr_count > 1)
		वापस -ENOMEM;

	ring_count = txr_count + rxr_count;
	size = काष्ठा_size(q_vector, ring, ring_count);

	/* allocate q_vector and rings */
	q_vector = adapter->q_vector[v_idx];
	अगर (!q_vector) अणु
		q_vector = kzalloc(size, GFP_KERNEL);
	पूर्ण अन्यथा अगर (size > ksize(q_vector)) अणु
		kमुक्त_rcu(q_vector, rcu);
		q_vector = kzalloc(size, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		स_रखो(q_vector, 0, size);
	पूर्ण
	अगर (!q_vector)
		वापस -ENOMEM;

	/* initialize NAPI */
	netअगर_napi_add(adapter->netdev, &q_vector->napi,
		       igb_poll, 64);

	/* tie q_vector and adapter together */
	adapter->q_vector[v_idx] = q_vector;
	q_vector->adapter = adapter;

	/* initialize work limits */
	q_vector->tx.work_limit = adapter->tx_work_limit;

	/* initialize ITR configuration */
	q_vector->itr_रेजिस्टर = adapter->io_addr + E1000_EITR(0);
	q_vector->itr_val = IGB_START_ITR;

	/* initialize poपूर्णांकer to rings */
	ring = q_vector->ring;

	/* पूर्णांकialize ITR */
	अगर (rxr_count) अणु
		/* rx or rx/tx vector */
		अगर (!adapter->rx_itr_setting || adapter->rx_itr_setting > 3)
			q_vector->itr_val = adapter->rx_itr_setting;
	पूर्ण अन्यथा अणु
		/* tx only vector */
		अगर (!adapter->tx_itr_setting || adapter->tx_itr_setting > 3)
			q_vector->itr_val = adapter->tx_itr_setting;
	पूर्ण

	अगर (txr_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Tx values */
		igb_add_ring(ring, &q_vector->tx);

		/* For 82575, context index must be unique per ring. */
		अगर (adapter->hw.mac.type == e1000_82575)
			set_bit(IGB_RING_FLAG_TX_CTX_IDX, &ring->flags);

		/* apply Tx specअगरic ring traits */
		ring->count = adapter->tx_ring_count;
		ring->queue_index = txr_idx;

		ring->cbs_enable = false;
		ring->idleslope = 0;
		ring->sendslope = 0;
		ring->hicredit = 0;
		ring->locredit = 0;

		u64_stats_init(&ring->tx_syncp);
		u64_stats_init(&ring->tx_syncp2);

		/* assign ring to adapter */
		adapter->tx_ring[txr_idx] = ring;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	अगर (rxr_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Rx values */
		igb_add_ring(ring, &q_vector->rx);

		/* set flag indicating ring supports SCTP checksum offload */
		अगर (adapter->hw.mac.type >= e1000_82576)
			set_bit(IGB_RING_FLAG_RX_SCTP_CSUM, &ring->flags);

		/* On i350, i354, i210, and i211, loopback VLAN packets
		 * have the tag byte-swapped.
		 */
		अगर (adapter->hw.mac.type >= e1000_i350)
			set_bit(IGB_RING_FLAG_RX_LB_VLAN_BSWAP, &ring->flags);

		/* apply Rx specअगरic ring traits */
		ring->count = adapter->rx_ring_count;
		ring->queue_index = rxr_idx;

		u64_stats_init(&ring->rx_syncp);

		/* assign ring to adapter */
		adapter->rx_ring[rxr_idx] = ring;
	पूर्ण

	वापस 0;
पूर्ण


/**
 *  igb_alloc_q_vectors - Allocate memory क्रम पूर्णांकerrupt vectors
 *  @adapter: board निजी काष्ठाure to initialize
 *
 *  We allocate one q_vector per queue पूर्णांकerrupt.  If allocation fails we
 *  वापस -ENOMEM.
 **/
अटल पूर्णांक igb_alloc_q_vectors(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक q_vectors = adapter->num_q_vectors;
	पूर्णांक rxr_reमुख्यing = adapter->num_rx_queues;
	पूर्णांक txr_reमुख्यing = adapter->num_tx_queues;
	पूर्णांक rxr_idx = 0, txr_idx = 0, v_idx = 0;
	पूर्णांक err;

	अगर (q_vectors >= (rxr_reमुख्यing + txr_reमुख्यing)) अणु
		क्रम (; rxr_reमुख्यing; v_idx++) अणु
			err = igb_alloc_q_vector(adapter, q_vectors, v_idx,
						 0, 0, 1, rxr_idx);

			अगर (err)
				जाओ err_out;

			/* update counts and index */
			rxr_reमुख्यing--;
			rxr_idx++;
		पूर्ण
	पूर्ण

	क्रम (; v_idx < q_vectors; v_idx++) अणु
		पूर्णांक rqpv = DIV_ROUND_UP(rxr_reमुख्यing, q_vectors - v_idx);
		पूर्णांक tqpv = DIV_ROUND_UP(txr_reमुख्यing, q_vectors - v_idx);

		err = igb_alloc_q_vector(adapter, q_vectors, v_idx,
					 tqpv, txr_idx, rqpv, rxr_idx);

		अगर (err)
			जाओ err_out;

		/* update counts and index */
		rxr_reमुख्यing -= rqpv;
		txr_reमुख्यing -= tqpv;
		rxr_idx++;
		txr_idx++;
	पूर्ण

	वापस 0;

err_out:
	adapter->num_tx_queues = 0;
	adapter->num_rx_queues = 0;
	adapter->num_q_vectors = 0;

	जबतक (v_idx--)
		igb_मुक्त_q_vector(adapter, v_idx);

	वापस -ENOMEM;
पूर्ण

/**
 *  igb_init_पूर्णांकerrupt_scheme - initialize पूर्णांकerrupts, allocate queues/vectors
 *  @adapter: board निजी काष्ठाure to initialize
 *  @msix: boolean value of MSIX capability
 *
 *  This function initializes the पूर्णांकerrupts and allocates all of the queues.
 **/
अटल पूर्णांक igb_init_पूर्णांकerrupt_scheme(काष्ठा igb_adapter *adapter, bool msix)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err;

	igb_set_पूर्णांकerrupt_capability(adapter, msix);

	err = igb_alloc_q_vectors(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to allocate memory for vectors\n");
		जाओ err_alloc_q_vectors;
	पूर्ण

	igb_cache_ring_रेजिस्टर(adapter);

	वापस 0;

err_alloc_q_vectors:
	igb_reset_पूर्णांकerrupt_capability(adapter);
	वापस err;
पूर्ण

/**
 *  igb_request_irq - initialize पूर्णांकerrupts
 *  @adapter: board निजी काष्ठाure to initialize
 *
 *  Attempts to configure पूर्णांकerrupts using the best available
 *  capabilities of the hardware and kernel.
 **/
अटल पूर्णांक igb_request_irq(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err = 0;

	अगर (adapter->flags & IGB_FLAG_HAS_MSIX) अणु
		err = igb_request_msix(adapter);
		अगर (!err)
			जाओ request_करोne;
		/* fall back to MSI */
		igb_मुक्त_all_tx_resources(adapter);
		igb_मुक्त_all_rx_resources(adapter);

		igb_clear_पूर्णांकerrupt_scheme(adapter);
		err = igb_init_पूर्णांकerrupt_scheme(adapter, false);
		अगर (err)
			जाओ request_करोne;

		igb_setup_all_tx_resources(adapter);
		igb_setup_all_rx_resources(adapter);
		igb_configure(adapter);
	पूर्ण

	igb_assign_vector(adapter->q_vector[0], 0);

	अगर (adapter->flags & IGB_FLAG_HAS_MSI) अणु
		err = request_irq(pdev->irq, igb_पूर्णांकr_msi, 0,
				  netdev->name, adapter);
		अगर (!err)
			जाओ request_करोne;

		/* fall back to legacy पूर्णांकerrupts */
		igb_reset_पूर्णांकerrupt_capability(adapter);
		adapter->flags &= ~IGB_FLAG_HAS_MSI;
	पूर्ण

	err = request_irq(pdev->irq, igb_पूर्णांकr, IRQF_SHARED,
			  netdev->name, adapter);

	अगर (err)
		dev_err(&pdev->dev, "Error %d getting interrupt\n",
			err);

request_करोne:
	वापस err;
पूर्ण

अटल व्योम igb_मुक्त_irq(काष्ठा igb_adapter *adapter)
अणु
	अगर (adapter->flags & IGB_FLAG_HAS_MSIX) अणु
		पूर्णांक vector = 0, i;

		मुक्त_irq(adapter->msix_entries[vector++].vector, adapter);

		क्रम (i = 0; i < adapter->num_q_vectors; i++)
			मुक्त_irq(adapter->msix_entries[vector++].vector,
				 adapter->q_vector[i]);
	पूर्ण अन्यथा अणु
		मुक्त_irq(adapter->pdev->irq, adapter);
	पूर्ण
पूर्ण

/**
 *  igb_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 *  @adapter: board निजी काष्ठाure
 **/
अटल व्योम igb_irq_disable(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* we need to be careful when disabling पूर्णांकerrupts.  The VFs are also
	 * mapped पूर्णांकo these रेजिस्टरs and so clearing the bits can cause
	 * issues on the VF drivers so we only need to clear what we set
	 */
	अगर (adapter->flags & IGB_FLAG_HAS_MSIX) अणु
		u32 regval = rd32(E1000_EIAM);

		wr32(E1000_EIAM, regval & ~adapter->eims_enable_mask);
		wr32(E1000_EIMC, adapter->eims_enable_mask);
		regval = rd32(E1000_EIAC);
		wr32(E1000_EIAC, regval & ~adapter->eims_enable_mask);
	पूर्ण

	wr32(E1000_IAM, 0);
	wr32(E1000_IMC, ~0);
	wrfl();
	अगर (adapter->flags & IGB_FLAG_HAS_MSIX) अणु
		पूर्णांक i;

		क्रम (i = 0; i < adapter->num_q_vectors; i++)
			synchronize_irq(adapter->msix_entries[i].vector);
	पूर्ण अन्यथा अणु
		synchronize_irq(adapter->pdev->irq);
	पूर्ण
पूर्ण

/**
 *  igb_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 *  @adapter: board निजी काष्ठाure
 **/
अटल व्योम igb_irq_enable(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (adapter->flags & IGB_FLAG_HAS_MSIX) अणु
		u32 ims = E1000_IMS_LSC | E1000_IMS_DOUTSYNC | E1000_IMS_DRSTA;
		u32 regval = rd32(E1000_EIAC);

		wr32(E1000_EIAC, regval | adapter->eims_enable_mask);
		regval = rd32(E1000_EIAM);
		wr32(E1000_EIAM, regval | adapter->eims_enable_mask);
		wr32(E1000_EIMS, adapter->eims_enable_mask);
		अगर (adapter->vfs_allocated_count) अणु
			wr32(E1000_MBVFIMR, 0xFF);
			ims |= E1000_IMS_VMMB;
		पूर्ण
		wr32(E1000_IMS, ims);
	पूर्ण अन्यथा अणु
		wr32(E1000_IMS, IMS_ENABLE_MASK |
				E1000_IMS_DRSTA);
		wr32(E1000_IAM, IMS_ENABLE_MASK |
				E1000_IMS_DRSTA);
	पूर्ण
पूर्ण

अटल व्योम igb_update_mng_vlan(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 pf_id = adapter->vfs_allocated_count;
	u16 vid = adapter->hw.mng_cookie.vlan_id;
	u16 old_vid = adapter->mng_vlan_id;

	अगर (hw->mng_cookie.status & E1000_MNG_DHCP_COOKIE_STATUS_VLAN) अणु
		/* add VID to filter table */
		igb_vfta_set(hw, vid, pf_id, true, true);
		adapter->mng_vlan_id = vid;
	पूर्ण अन्यथा अणु
		adapter->mng_vlan_id = IGB_MNG_VLAN_NONE;
	पूर्ण

	अगर ((old_vid != (u16)IGB_MNG_VLAN_NONE) &&
	    (vid != old_vid) &&
	    !test_bit(old_vid, adapter->active_vlans)) अणु
		/* हटाओ VID from filter table */
		igb_vfta_set(hw, vid, pf_id, false, true);
	पूर्ण
पूर्ण

/**
 *  igb_release_hw_control - release control of the h/w to f/w
 *  @adapter: address of board निजी काष्ठाure
 *
 *  igb_release_hw_control resets CTRL_EXT:DRV_LOAD bit.
 *  For ASF and Pass Through versions of f/w this means that the
 *  driver is no दीर्घer loaded.
 **/
अटल व्योम igb_release_hw_control(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl_ext;

	/* Let firmware take over control of h/w */
	ctrl_ext = rd32(E1000_CTRL_EXT);
	wr32(E1000_CTRL_EXT,
			ctrl_ext & ~E1000_CTRL_EXT_DRV_LOAD);
पूर्ण

/**
 *  igb_get_hw_control - get control of the h/w from f/w
 *  @adapter: address of board निजी काष्ठाure
 *
 *  igb_get_hw_control sets CTRL_EXT:DRV_LOAD bit.
 *  For ASF and Pass Through versions of f/w this means that
 *  the driver is loaded.
 **/
अटल व्योम igb_get_hw_control(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl_ext;

	/* Let firmware know the driver has taken over */
	ctrl_ext = rd32(E1000_CTRL_EXT);
	wr32(E1000_CTRL_EXT,
			ctrl_ext | E1000_CTRL_EXT_DRV_LOAD);
पूर्ण

अटल व्योम enable_fqtss(काष्ठा igb_adapter *adapter, bool enable)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;

	WARN_ON(hw->mac.type != e1000_i210);

	अगर (enable)
		adapter->flags |= IGB_FLAG_FQTSS;
	अन्यथा
		adapter->flags &= ~IGB_FLAG_FQTSS;

	अगर (netअगर_running(netdev))
		schedule_work(&adapter->reset_task);
पूर्ण

अटल bool is_fqtss_enabled(काष्ठा igb_adapter *adapter)
अणु
	वापस (adapter->flags & IGB_FLAG_FQTSS) ? true : false;
पूर्ण

अटल व्योम set_tx_desc_fetch_prio(काष्ठा e1000_hw *hw, पूर्णांक queue,
				   क्रमागत tx_queue_prio prio)
अणु
	u32 val;

	WARN_ON(hw->mac.type != e1000_i210);
	WARN_ON(queue < 0 || queue > 4);

	val = rd32(E1000_I210_TXDCTL(queue));

	अगर (prio == TX_QUEUE_PRIO_HIGH)
		val |= E1000_TXDCTL_PRIORITY;
	अन्यथा
		val &= ~E1000_TXDCTL_PRIORITY;

	wr32(E1000_I210_TXDCTL(queue), val);
पूर्ण

अटल व्योम set_queue_mode(काष्ठा e1000_hw *hw, पूर्णांक queue, क्रमागत queue_mode mode)
अणु
	u32 val;

	WARN_ON(hw->mac.type != e1000_i210);
	WARN_ON(queue < 0 || queue > 1);

	val = rd32(E1000_I210_TQAVCC(queue));

	अगर (mode == QUEUE_MODE_STREAM_RESERVATION)
		val |= E1000_TQAVCC_QUEUEMODE;
	अन्यथा
		val &= ~E1000_TQAVCC_QUEUEMODE;

	wr32(E1000_I210_TQAVCC(queue), val);
पूर्ण

अटल bool is_any_cbs_enabled(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		अगर (adapter->tx_ring[i]->cbs_enable)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool is_any_txसमय_enabled(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		अगर (adapter->tx_ring[i]->launchसमय_enable)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 *  igb_config_tx_modes - Configure "Qav Tx mode" features on igb
 *  @adapter: poपूर्णांकer to adapter काष्ठा
 *  @queue: queue number
 *
 *  Configure CBS and Launchसमय क्रम a given hardware queue.
 *  Parameters are retrieved from the correct Tx ring, so
 *  igb_save_cbs_params() and igb_save_txसमय_params() should be used
 *  क्रम setting those correctly prior to this function being called.
 **/
अटल व्योम igb_config_tx_modes(काष्ठा igb_adapter *adapter, पूर्णांक queue)
अणु
	काष्ठा igb_ring *ring = adapter->tx_ring[queue];
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tqavcc, tqavctrl;
	u16 value;

	WARN_ON(hw->mac.type != e1000_i210);
	WARN_ON(queue < 0 || queue > 1);

	/* If any of the Qav features is enabled, configure queues as SR and
	 * with HIGH PRIO. If none is, then configure them with LOW PRIO and
	 * as SP.
	 */
	अगर (ring->cbs_enable || ring->launchसमय_enable) अणु
		set_tx_desc_fetch_prio(hw, queue, TX_QUEUE_PRIO_HIGH);
		set_queue_mode(hw, queue, QUEUE_MODE_STREAM_RESERVATION);
	पूर्ण अन्यथा अणु
		set_tx_desc_fetch_prio(hw, queue, TX_QUEUE_PRIO_LOW);
		set_queue_mode(hw, queue, QUEUE_MODE_STRICT_PRIORITY);
	पूर्ण

	/* If CBS is enabled, set DataTranARB and config its parameters. */
	अगर (ring->cbs_enable || queue == 0) अणु
		/* i210 करोes not allow the queue 0 to be in the Strict
		 * Priority mode जबतक the Qav mode is enabled, so,
		 * instead of disabling strict priority mode, we give
		 * queue 0 the maximum of credits possible.
		 *
		 * See section 8.12.19 of the i210 datasheet, "Note:
		 * Queue0 QueueMode must be set to 1b when
		 * TransmitMode is set to Qav."
		 */
		अगर (queue == 0 && !ring->cbs_enable) अणु
			/* max "linkspeed" idleslope in kbps */
			ring->idleslope = 1000000;
			ring->hicredit = ETH_FRAME_LEN;
		पूर्ण

		/* Always set data transfer arbitration to credit-based
		 * shaper algorithm on TQAVCTRL अगर CBS is enabled क्रम any of
		 * the queues.
		 */
		tqavctrl = rd32(E1000_I210_TQAVCTRL);
		tqavctrl |= E1000_TQAVCTRL_DATATRANARB;
		wr32(E1000_I210_TQAVCTRL, tqavctrl);

		/* According to i210 datasheet section 7.2.7.7, we should set
		 * the 'idleSlope' field from TQAVCC रेजिस्टर following the
		 * equation:
		 *
		 * For 100 Mbps link speed:
		 *
		 *     value = BW * 0x7735 * 0.2                          (E1)
		 *
		 * For 1000Mbps link speed:
		 *
		 *     value = BW * 0x7735 * 2                            (E2)
		 *
		 * E1 and E2 can be merged पूर्णांकo one equation as shown below.
		 * Note that 'link-speed' is in Mbps.
		 *
		 *     value = BW * 0x7735 * 2 * link-speed
		 *                           --------------               (E3)
		 *                                1000
		 *
		 * 'BW' is the percentage bandwidth out of full link speed
		 * which can be found with the following equation. Note that
		 * idleSlope here is the parameter from this function which
		 * is in kbps.
		 *
		 *     BW =     idleSlope
		 *          -----------------                             (E4)
		 *          link-speed * 1000
		 *
		 * That said, we can come up with a generic equation to
		 * calculate the value we should set it TQAVCC रेजिस्टर by
		 * replacing 'BW' in E3 by E4. The resulting equation is:
		 *
		 * value =     idleSlope     * 0x7735 * 2 * link-speed
		 *         -----------------            --------------    (E5)
		 *         link-speed * 1000                 1000
		 *
		 * 'link-speed' is present in both sides of the fraction so
		 * it is canceled out. The final equation is the following:
		 *
		 *     value = idleSlope * 61034
		 *             -----------------                          (E6)
		 *                  1000000
		 *
		 * NOTE: For i210, given the above, we can see that idleslope
		 *       is represented in 16.38431 kbps units by the value at
		 *       the TQAVCC रेजिस्टर (1Gbps / 61034), which reduces
		 *       the granularity क्रम idleslope increments.
		 *       For instance, अगर you want to configure a 2576kbps
		 *       idleslope, the value to be written on the रेजिस्टर
		 *       would have to be 157.23. If rounded करोwn, you end
		 *       up with less bandwidth available than originally
		 *       required (~2572 kbps). If rounded up, you end up
		 *       with a higher bandwidth (~2589 kbps). Below the
		 *       approach we take is to always round up the
		 *       calculated value, so the resulting bandwidth might
		 *       be slightly higher क्रम some configurations.
		 */
		value = DIV_ROUND_UP_ULL(ring->idleslope * 61034ULL, 1000000);

		tqavcc = rd32(E1000_I210_TQAVCC(queue));
		tqavcc &= ~E1000_TQAVCC_IDLESLOPE_MASK;
		tqavcc |= value;
		wr32(E1000_I210_TQAVCC(queue), tqavcc);

		wr32(E1000_I210_TQAVHC(queue),
		     0x80000000 + ring->hicredit * 0x7735);
	पूर्ण अन्यथा अणु

		/* Set idleSlope to zero. */
		tqavcc = rd32(E1000_I210_TQAVCC(queue));
		tqavcc &= ~E1000_TQAVCC_IDLESLOPE_MASK;
		wr32(E1000_I210_TQAVCC(queue), tqavcc);

		/* Set hiCredit to zero. */
		wr32(E1000_I210_TQAVHC(queue), 0);

		/* If CBS is not enabled क्रम any queues anymore, then वापस to
		 * the शेष state of Data Transmission Arbitration on
		 * TQAVCTRL.
		 */
		अगर (!is_any_cbs_enabled(adapter)) अणु
			tqavctrl = rd32(E1000_I210_TQAVCTRL);
			tqavctrl &= ~E1000_TQAVCTRL_DATATRANARB;
			wr32(E1000_I210_TQAVCTRL, tqavctrl);
		पूर्ण
	पूर्ण

	/* If LaunchTime is enabled, set DataTranTIM. */
	अगर (ring->launchसमय_enable) अणु
		/* Always set DataTranTIM on TQAVCTRL अगर LaunchTime is enabled
		 * क्रम any of the SR queues, and configure fetchसमय delta.
		 * XXX NOTE:
		 *     - LaunchTime will be enabled क्रम all SR queues.
		 *     - A fixed offset can be added relative to the launch
		 *       समय of all packets अगर configured at reg LAUNCH_OS0.
		 *       We are keeping it as 0 क्रम now (शेष value).
		 */
		tqavctrl = rd32(E1000_I210_TQAVCTRL);
		tqavctrl |= E1000_TQAVCTRL_DATATRANTIM |
		       E1000_TQAVCTRL_FETCHTIME_DELTA;
		wr32(E1000_I210_TQAVCTRL, tqavctrl);
	पूर्ण अन्यथा अणु
		/* If Launchसमय is not enabled क्रम any SR queues anymore,
		 * then clear DataTranTIM on TQAVCTRL and clear fetchसमय delta,
		 * effectively disabling Launchसमय.
		 */
		अगर (!is_any_txसमय_enabled(adapter)) अणु
			tqavctrl = rd32(E1000_I210_TQAVCTRL);
			tqavctrl &= ~E1000_TQAVCTRL_DATATRANTIM;
			tqavctrl &= ~E1000_TQAVCTRL_FETCHTIME_DELTA;
			wr32(E1000_I210_TQAVCTRL, tqavctrl);
		पूर्ण
	पूर्ण

	/* XXX: In i210 controller the sendSlope and loCredit parameters from
	 * CBS are not configurable by software so we करोn't do any 'controller
	 * configuration' in respect to these parameters.
	 */

	netdev_dbg(netdev, "Qav Tx mode: cbs %s, launchtime %s, queue %d idleslope %d sendslope %d hiCredit %d locredit %d\n",
		   ring->cbs_enable ? "enabled" : "disabled",
		   ring->launchसमय_enable ? "enabled" : "disabled",
		   queue,
		   ring->idleslope, ring->sendslope,
		   ring->hicredit, ring->locredit);
पूर्ण

अटल पूर्णांक igb_save_txसमय_params(काष्ठा igb_adapter *adapter, पूर्णांक queue,
				  bool enable)
अणु
	काष्ठा igb_ring *ring;

	अगर (queue < 0 || queue > adapter->num_tx_queues)
		वापस -EINVAL;

	ring = adapter->tx_ring[queue];
	ring->launchसमय_enable = enable;

	वापस 0;
पूर्ण

अटल पूर्णांक igb_save_cbs_params(काष्ठा igb_adapter *adapter, पूर्णांक queue,
			       bool enable, पूर्णांक idleslope, पूर्णांक sendslope,
			       पूर्णांक hicredit, पूर्णांक locredit)
अणु
	काष्ठा igb_ring *ring;

	अगर (queue < 0 || queue > adapter->num_tx_queues)
		वापस -EINVAL;

	ring = adapter->tx_ring[queue];

	ring->cbs_enable = enable;
	ring->idleslope = idleslope;
	ring->sendslope = sendslope;
	ring->hicredit = hicredit;
	ring->locredit = locredit;

	वापस 0;
पूर्ण

/**
 *  igb_setup_tx_mode - Switch to/from Qav Tx mode when applicable
 *  @adapter: poपूर्णांकer to adapter काष्ठा
 *
 *  Configure TQAVCTRL रेजिस्टर चयनing the controller's Tx mode
 *  अगर FQTSS mode is enabled or disabled. Additionally, will issue
 *  a call to igb_config_tx_modes() per queue so any previously saved
 *  Tx parameters are applied.
 **/
अटल व्योम igb_setup_tx_mode(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 val;

	/* Only i210 controller supports changing the transmission mode. */
	अगर (hw->mac.type != e1000_i210)
		वापस;

	अगर (is_fqtss_enabled(adapter)) अणु
		पूर्णांक i, max_queue;

		/* Configure TQAVCTRL रेजिस्टर: set transmit mode to 'Qav',
		 * set data fetch arbitration to 'round robin', set SP_WAIT_SR
		 * so SP queues रुको क्रम SR ones.
		 */
		val = rd32(E1000_I210_TQAVCTRL);
		val |= E1000_TQAVCTRL_XMIT_MODE | E1000_TQAVCTRL_SP_WAIT_SR;
		val &= ~E1000_TQAVCTRL_DATAFETCHARB;
		wr32(E1000_I210_TQAVCTRL, val);

		/* Configure Tx and Rx packet buffers sizes as described in
		 * i210 datasheet section 7.2.7.7.
		 */
		val = rd32(E1000_TXPBS);
		val &= ~I210_TXPBSIZE_MASK;
		val |= I210_TXPBSIZE_PB0_6KB | I210_TXPBSIZE_PB1_6KB |
			I210_TXPBSIZE_PB2_6KB | I210_TXPBSIZE_PB3_6KB;
		wr32(E1000_TXPBS, val);

		val = rd32(E1000_RXPBS);
		val &= ~I210_RXPBSIZE_MASK;
		val |= I210_RXPBSIZE_PB_30KB;
		wr32(E1000_RXPBS, val);

		/* Section 8.12.9 states that MAX_TPKT_SIZE from DTXMXPKTSZ
		 * रेजिस्टर should not exceed the buffer size programmed in
		 * TXPBS. The smallest buffer size programmed in TXPBS is 4kB
		 * so according to the datasheet we should set MAX_TPKT_SIZE to
		 * 4kB / 64.
		 *
		 * However, when we करो so, no frame from queue 2 and 3 are
		 * transmitted.  It seems the MAX_TPKT_SIZE should not be great
		 * or _equal_ to the buffer size programmed in TXPBS. For this
		 * reason, we set set MAX_ TPKT_SIZE to (4kB - 1) / 64.
		 */
		val = (4096 - 1) / 64;
		wr32(E1000_I210_DTXMXPKTSZ, val);

		/* Since FQTSS mode is enabled, apply any CBS configuration
		 * previously set. If no previous CBS configuration has been
		 * करोne, then the initial configuration is applied, which means
		 * CBS is disabled.
		 */
		max_queue = (adapter->num_tx_queues < I210_SR_QUEUES_NUM) ?
			    adapter->num_tx_queues : I210_SR_QUEUES_NUM;

		क्रम (i = 0; i < max_queue; i++) अणु
			igb_config_tx_modes(adapter, i);
		पूर्ण
	पूर्ण अन्यथा अणु
		wr32(E1000_RXPBS, I210_RXPBSIZE_DEFAULT);
		wr32(E1000_TXPBS, I210_TXPBSIZE_DEFAULT);
		wr32(E1000_I210_DTXMXPKTSZ, I210_DTXMXPKTSZ_DEFAULT);

		val = rd32(E1000_I210_TQAVCTRL);
		/* According to Section 8.12.21, the other flags we've set when
		 * enabling FQTSS are not relevant when disabling FQTSS so we
		 * करोn't set they here.
		 */
		val &= ~E1000_TQAVCTRL_XMIT_MODE;
		wr32(E1000_I210_TQAVCTRL, val);
	पूर्ण

	netdev_dbg(netdev, "FQTSS %s\n", (is_fqtss_enabled(adapter)) ?
		   "enabled" : "disabled");
पूर्ण

/**
 *  igb_configure - configure the hardware क्रम RX and TX
 *  @adapter: निजी board काष्ठाure
 **/
अटल व्योम igb_configure(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i;

	igb_get_hw_control(adapter);
	igb_set_rx_mode(netdev);
	igb_setup_tx_mode(adapter);

	igb_restore_vlan(adapter);

	igb_setup_tctl(adapter);
	igb_setup_mrqc(adapter);
	igb_setup_rctl(adapter);

	igb_nfc_filter_restore(adapter);
	igb_configure_tx(adapter);
	igb_configure_rx(adapter);

	igb_rx_fअगरo_flush_82575(&adapter->hw);

	/* call igb_desc_unused which always leaves
	 * at least 1 descriptor unused to make sure
	 * next_to_use != next_to_clean
	 */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा igb_ring *ring = adapter->rx_ring[i];
		igb_alloc_rx_buffers(ring, igb_desc_unused(ring));
	पूर्ण
पूर्ण

/**
 *  igb_घातer_up_link - Power up the phy/serdes link
 *  @adapter: address of board निजी काष्ठाure
 **/
व्योम igb_घातer_up_link(काष्ठा igb_adapter *adapter)
अणु
	igb_reset_phy(&adapter->hw);

	अगर (adapter->hw.phy.media_type == e1000_media_type_copper)
		igb_घातer_up_phy_copper(&adapter->hw);
	अन्यथा
		igb_घातer_up_serdes_link_82575(&adapter->hw);

	igb_setup_link(&adapter->hw);
पूर्ण

/**
 *  igb_घातer_करोwn_link - Power करोwn the phy/serdes link
 *  @adapter: address of board निजी काष्ठाure
 */
अटल व्योम igb_घातer_करोwn_link(काष्ठा igb_adapter *adapter)
अणु
	अगर (adapter->hw.phy.media_type == e1000_media_type_copper)
		igb_घातer_करोwn_phy_copper_82575(&adapter->hw);
	अन्यथा
		igb_shutकरोwn_serdes_link_82575(&adapter->hw);
पूर्ण

/**
 * igb_check_swap_media -  Detect and चयन function क्रम Media Auto Sense
 * @adapter: address of the board निजी काष्ठाure
 **/
अटल व्योम igb_check_swap_media(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl_ext, connsw;
	bool swap_now = false;

	ctrl_ext = rd32(E1000_CTRL_EXT);
	connsw = rd32(E1000_CONNSW);

	/* need to live swap अगर current media is copper and we have fiber/serdes
	 * to go to.
	 */

	अगर ((hw->phy.media_type == e1000_media_type_copper) &&
	    (!(connsw & E1000_CONNSW_AUTOSENSE_EN))) अणु
		swap_now = true;
	पूर्ण अन्यथा अगर ((hw->phy.media_type != e1000_media_type_copper) &&
		   !(connsw & E1000_CONNSW_SERDESD)) अणु
		/* copper संकेत takes समय to appear */
		अगर (adapter->copper_tries < 4) अणु
			adapter->copper_tries++;
			connsw |= E1000_CONNSW_AUTOSENSE_CONF;
			wr32(E1000_CONNSW, connsw);
			वापस;
		पूर्ण अन्यथा अणु
			adapter->copper_tries = 0;
			अगर ((connsw & E1000_CONNSW_PHYSD) &&
			    (!(connsw & E1000_CONNSW_PHY_PDN))) अणु
				swap_now = true;
				connsw &= ~E1000_CONNSW_AUTOSENSE_CONF;
				wr32(E1000_CONNSW, connsw);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!swap_now)
		वापस;

	चयन (hw->phy.media_type) अणु
	हाल e1000_media_type_copper:
		netdev_info(adapter->netdev,
			"MAS: changing media to fiber/serdes\n");
		ctrl_ext |=
			E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES;
		adapter->flags |= IGB_FLAG_MEDIA_RESET;
		adapter->copper_tries = 0;
		अवरोध;
	हाल e1000_media_type_पूर्णांकernal_serdes:
	हाल e1000_media_type_fiber:
		netdev_info(adapter->netdev,
			"MAS: changing media to copper\n");
		ctrl_ext &=
			~E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES;
		adapter->flags |= IGB_FLAG_MEDIA_RESET;
		अवरोध;
	शेष:
		/* shouldn't get here during regular operation */
		netdev_err(adapter->netdev,
			"AMS: Invalid media type found, returning\n");
		अवरोध;
	पूर्ण
	wr32(E1000_CTRL_EXT, ctrl_ext);
पूर्ण

/**
 *  igb_up - Open the पूर्णांकerface and prepare it to handle traffic
 *  @adapter: board निजी काष्ठाure
 **/
पूर्णांक igb_up(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक i;

	/* hardware has been reset, we need to reload some things */
	igb_configure(adapter);

	clear_bit(__IGB_DOWN, &adapter->state);

	क्रम (i = 0; i < adapter->num_q_vectors; i++)
		napi_enable(&(adapter->q_vector[i]->napi));

	अगर (adapter->flags & IGB_FLAG_HAS_MSIX)
		igb_configure_msix(adapter);
	अन्यथा
		igb_assign_vector(adapter->q_vector[0], 0);

	/* Clear any pending पूर्णांकerrupts. */
	rd32(E1000_TSICR);
	rd32(E1000_ICR);
	igb_irq_enable(adapter);

	/* notअगरy VFs that reset has been completed */
	अगर (adapter->vfs_allocated_count) अणु
		u32 reg_data = rd32(E1000_CTRL_EXT);

		reg_data |= E1000_CTRL_EXT_PFRSTD;
		wr32(E1000_CTRL_EXT, reg_data);
	पूर्ण

	netअगर_tx_start_all_queues(adapter->netdev);

	/* start the watchकरोg. */
	hw->mac.get_link_status = 1;
	schedule_work(&adapter->watchकरोg_task);

	अगर ((adapter->flags & IGB_FLAG_EEE) &&
	    (!hw->dev_spec._82575.eee_disable))
		adapter->eee_advert = MDIO_EEE_100TX | MDIO_EEE_1000T;

	वापस 0;
पूर्ण

व्योम igb_करोwn(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tctl, rctl;
	पूर्णांक i;

	/* संकेत that we're करोwn so the पूर्णांकerrupt handler करोes not
	 * reschedule our watchकरोg समयr
	 */
	set_bit(__IGB_DOWN, &adapter->state);

	/* disable receives in the hardware */
	rctl = rd32(E1000_RCTL);
	wr32(E1000_RCTL, rctl & ~E1000_RCTL_EN);
	/* flush and sleep below */

	igb_nfc_filter_निकास(adapter);

	netअगर_carrier_off(netdev);
	netअगर_tx_stop_all_queues(netdev);

	/* disable transmits in the hardware */
	tctl = rd32(E1000_TCTL);
	tctl &= ~E1000_TCTL_EN;
	wr32(E1000_TCTL, tctl);
	/* flush both disables and रुको क्रम them to finish */
	wrfl();
	usleep_range(10000, 11000);

	igb_irq_disable(adapter);

	adapter->flags &= ~IGB_FLAG_NEED_LINK_UPDATE;

	क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
		अगर (adapter->q_vector[i]) अणु
			napi_synchronize(&adapter->q_vector[i]->napi);
			napi_disable(&adapter->q_vector[i]->napi);
		पूर्ण
	पूर्ण

	del_समयr_sync(&adapter->watchकरोg_समयr);
	del_समयr_sync(&adapter->phy_info_समयr);

	/* record the stats beक्रमe reset*/
	spin_lock(&adapter->stats64_lock);
	igb_update_stats(adapter);
	spin_unlock(&adapter->stats64_lock);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	अगर (!pci_channel_offline(adapter->pdev))
		igb_reset(adapter);

	/* clear VLAN promisc flag so VFTA will be updated अगर necessary */
	adapter->flags &= ~IGB_FLAG_VLAN_PROMISC;

	igb_clean_all_tx_rings(adapter);
	igb_clean_all_rx_rings(adapter);
#अगर_घोषित CONFIG_IGB_DCA

	/* since we reset the hardware DCA settings were cleared */
	igb_setup_dca(adapter);
#पूर्ण_अगर
पूर्ण

व्योम igb_reinit_locked(काष्ठा igb_adapter *adapter)
अणु
	जबतक (test_and_set_bit(__IGB_RESETTING, &adapter->state))
		usleep_range(1000, 2000);
	igb_करोwn(adapter);
	igb_up(adapter);
	clear_bit(__IGB_RESETTING, &adapter->state);
पूर्ण

/** igb_enable_mas - Media Autosense re-enable after swap
 *
 * @adapter: adapter काष्ठा
 **/
अटल व्योम igb_enable_mas(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 connsw = rd32(E1000_CONNSW);

	/* configure क्रम SerDes media detect */
	अगर ((hw->phy.media_type == e1000_media_type_copper) &&
	    (!(connsw & E1000_CONNSW_SERDESD))) अणु
		connsw |= E1000_CONNSW_ENRGSRC;
		connsw |= E1000_CONNSW_AUTOSENSE_EN;
		wr32(E1000_CONNSW, connsw);
		wrfl();
	पूर्ण
पूर्ण

व्योम igb_reset(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_mac_info *mac = &hw->mac;
	काष्ठा e1000_fc_info *fc = &hw->fc;
	u32 pba, hwm;

	/* Repartition Pba क्रम greater than 9k mtu
	 * To take effect CTRL.RST is required.
	 */
	चयन (mac->type) अणु
	हाल e1000_i350:
	हाल e1000_i354:
	हाल e1000_82580:
		pba = rd32(E1000_RXPBS);
		pba = igb_rxpbs_adjust_82580(pba);
		अवरोध;
	हाल e1000_82576:
		pba = rd32(E1000_RXPBS);
		pba &= E1000_RXPBS_SIZE_MASK_82576;
		अवरोध;
	हाल e1000_82575:
	हाल e1000_i210:
	हाल e1000_i211:
	शेष:
		pba = E1000_PBA_34K;
		अवरोध;
	पूर्ण

	अगर (mac->type == e1000_82575) अणु
		u32 min_rx_space, min_tx_space, needed_tx_space;

		/* ग_लिखो Rx PBA so that hardware can report correct Tx PBA */
		wr32(E1000_PBA, pba);

		/* To मुख्यtain wire speed transmits, the Tx FIFO should be
		 * large enough to accommodate two full transmit packets,
		 * rounded up to the next 1KB and expressed in KB.  Likewise,
		 * the Rx FIFO should be large enough to accommodate at least
		 * one full receive packet and is similarly rounded up and
		 * expressed in KB.
		 */
		min_rx_space = DIV_ROUND_UP(MAX_JUMBO_FRAME_SIZE, 1024);

		/* The Tx FIFO also stores 16 bytes of inक्रमmation about the Tx
		 * but करोn't include Ethernet FCS because hardware appends it.
		 * We only need to round करोwn to the nearest 512 byte block
		 * count since the value we care about is 2 frames, not 1.
		 */
		min_tx_space = adapter->max_frame_size;
		min_tx_space += माप(जोड़ e1000_adv_tx_desc) - ETH_FCS_LEN;
		min_tx_space = DIV_ROUND_UP(min_tx_space, 512);

		/* upper 16 bits has Tx packet buffer allocation size in KB */
		needed_tx_space = min_tx_space - (rd32(E1000_PBA) >> 16);

		/* If current Tx allocation is less than the min Tx FIFO size,
		 * and the min Tx FIFO size is less than the current Rx FIFO
		 * allocation, take space away from current Rx allocation.
		 */
		अगर (needed_tx_space < pba) अणु
			pba -= needed_tx_space;

			/* अगर लघु on Rx space, Rx wins and must trump Tx
			 * adjusपंचांगent
			 */
			अगर (pba < min_rx_space)
				pba = min_rx_space;
		पूर्ण

		/* adjust PBA क्रम jumbo frames */
		wr32(E1000_PBA, pba);
	पूर्ण

	/* flow control settings
	 * The high water mark must be low enough to fit one full frame
	 * after transmitting the छोड़ो frame.  As such we must have enough
	 * space to allow क्रम us to complete our current transmit and then
	 * receive the frame that is in progress from the link partner.
	 * Set it to:
	 * - the full Rx FIFO size minus one full Tx plus one full Rx frame
	 */
	hwm = (pba << 10) - (adapter->max_frame_size + MAX_JUMBO_FRAME_SIZE);

	fc->high_water = hwm & 0xFFFFFFF0;	/* 16-byte granularity */
	fc->low_water = fc->high_water - 16;
	fc->छोड़ो_समय = 0xFFFF;
	fc->send_xon = 1;
	fc->current_mode = fc->requested_mode;

	/* disable receive क्रम all VFs and रुको one second */
	अगर (adapter->vfs_allocated_count) अणु
		पूर्णांक i;

		क्रम (i = 0 ; i < adapter->vfs_allocated_count; i++)
			adapter->vf_data[i].flags &= IGB_VF_FLAG_PF_SET_MAC;

		/* ping all the active vfs to let them know we are going करोwn */
		igb_ping_all_vfs(adapter);

		/* disable transmits and receives */
		wr32(E1000_VFRE, 0);
		wr32(E1000_VFTE, 0);
	पूर्ण

	/* Allow समय क्रम pending master requests to run */
	hw->mac.ops.reset_hw(hw);
	wr32(E1000_WUC, 0);

	अगर (adapter->flags & IGB_FLAG_MEDIA_RESET) अणु
		/* need to resetup here after media swap */
		adapter->ei.get_invariants(hw);
		adapter->flags &= ~IGB_FLAG_MEDIA_RESET;
	पूर्ण
	अगर ((mac->type == e1000_82575 || mac->type == e1000_i350) &&
	    (adapter->flags & IGB_FLAG_MAS_ENABLE)) अणु
		igb_enable_mas(adapter);
	पूर्ण
	अगर (hw->mac.ops.init_hw(hw))
		dev_err(&pdev->dev, "Hardware Error\n");

	/* RAR रेजिस्टरs were cleared during init_hw, clear mac table */
	igb_flush_mac_table(adapter);
	__dev_uc_unsync(adapter->netdev, शून्य);

	/* Recover शेष RAR entry */
	igb_set_शेष_mac_filter(adapter);

	/* Flow control settings reset on hardware reset, so guarantee flow
	 * control is off when क्रमcing speed.
	 */
	अगर (!hw->mac.स्वतःneg)
		igb_क्रमce_mac_fc(hw);

	igb_init_dmac(adapter, pba);
#अगर_घोषित CONFIG_IGB_HWMON
	/* Re-initialize the thermal sensor on i350 devices. */
	अगर (!test_bit(__IGB_DOWN, &adapter->state)) अणु
		अगर (mac->type == e1000_i350 && hw->bus.func == 0) अणु
			/* If present, re-initialize the बाह्यal thermal sensor
			 * पूर्णांकerface.
			 */
			अगर (adapter->ets)
				mac->ops.init_thermal_sensor_thresh(hw);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* Re-establish EEE setting */
	अगर (hw->phy.media_type == e1000_media_type_copper) अणु
		चयन (mac->type) अणु
		हाल e1000_i350:
		हाल e1000_i210:
		हाल e1000_i211:
			igb_set_eee_i350(hw, true, true);
			अवरोध;
		हाल e1000_i354:
			igb_set_eee_i354(hw, true, true);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!netअगर_running(adapter->netdev))
		igb_घातer_करोwn_link(adapter);

	igb_update_mng_vlan(adapter);

	/* Enable h/w to recognize an 802.1Q VLAN Ethernet packet */
	wr32(E1000_VET, ETHERNET_IEEE_VLAN_TYPE);

	/* Re-enable PTP, where applicable. */
	अगर (adapter->ptp_flags & IGB_PTP_ENABLED)
		igb_ptp_reset(adapter);

	igb_get_phy_info(hw);
पूर्ण

अटल netdev_features_t igb_fix_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	/* Since there is no support क्रम separate Rx/Tx vlan accel
	 * enable/disable make sure Tx flag is always in same state as Rx.
	 */
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		features |= NETIF_F_HW_VLAN_CTAG_TX;
	अन्यथा
		features &= ~NETIF_F_HW_VLAN_CTAG_TX;

	वापस features;
पूर्ण

अटल पूर्णांक igb_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	netdev_features_t changed = netdev->features ^ features;
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		igb_vlan_mode(netdev, features);

	अगर (!(changed & (NETIF_F_RXALL | NETIF_F_NTUPLE)))
		वापस 0;

	अगर (!(features & NETIF_F_NTUPLE)) अणु
		काष्ठा hlist_node *node2;
		काष्ठा igb_nfc_filter *rule;

		spin_lock(&adapter->nfc_lock);
		hlist_क्रम_each_entry_safe(rule, node2,
					  &adapter->nfc_filter_list, nfc_node) अणु
			igb_erase_filter(adapter, rule);
			hlist_del(&rule->nfc_node);
			kमुक्त(rule);
		पूर्ण
		spin_unlock(&adapter->nfc_lock);
		adapter->nfc_filter_count = 0;
	पूर्ण

	netdev->features = features;

	अगर (netअगर_running(netdev))
		igb_reinit_locked(adapter);
	अन्यथा
		igb_reset(adapter);

	वापस 1;
पूर्ण

अटल पूर्णांक igb_nकरो_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			   काष्ठा net_device *dev,
			   स्थिर अचिन्हित अक्षर *addr, u16 vid,
			   u16 flags,
			   काष्ठा netlink_ext_ack *extack)
अणु
	/* guarantee we can provide a unique filter क्रम the unicast address */
	अगर (is_unicast_ether_addr(addr) || is_link_local_ether_addr(addr)) अणु
		काष्ठा igb_adapter *adapter = netdev_priv(dev);
		पूर्णांक vfn = adapter->vfs_allocated_count;

		अगर (netdev_uc_count(dev) >= igb_available_rars(adapter, vfn))
			वापस -ENOMEM;
	पूर्ण

	वापस nकरो_dflt_fdb_add(ndm, tb, dev, addr, vid, flags);
पूर्ण

#घोषणा IGB_MAX_MAC_HDR_LEN	127
#घोषणा IGB_MAX_NETWORK_HDR_LEN	511

अटल netdev_features_t
igb_features_check(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		   netdev_features_t features)
अणु
	अचिन्हित पूर्णांक network_hdr_len, mac_hdr_len;

	/* Make certain the headers can be described by a context descriptor */
	mac_hdr_len = skb_network_header(skb) - skb->data;
	अगर (unlikely(mac_hdr_len > IGB_MAX_MAC_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_GSO_UDP_L4 |
				    NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	network_hdr_len = skb_checksum_start(skb) - skb_network_header(skb);
	अगर (unlikely(network_hdr_len >  IGB_MAX_NETWORK_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_GSO_UDP_L4 |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	/* We can only support IPV4 TSO in tunnels अगर we can mangle the
	 * inner IP ID field, so strip TSO अगर MANGLEID is not supported.
	 */
	अगर (skb->encapsulation && !(features & NETIF_F_TSO_MANGLEID))
		features &= ~NETIF_F_TSO;

	वापस features;
पूर्ण

अटल व्योम igb_offload_apply(काष्ठा igb_adapter *adapter, s32 queue)
अणु
	अगर (!is_fqtss_enabled(adapter)) अणु
		enable_fqtss(adapter, true);
		वापस;
	पूर्ण

	igb_config_tx_modes(adapter, queue);

	अगर (!is_any_cbs_enabled(adapter) && !is_any_txसमय_enabled(adapter))
		enable_fqtss(adapter, false);
पूर्ण

अटल पूर्णांक igb_offload_cbs(काष्ठा igb_adapter *adapter,
			   काष्ठा tc_cbs_qopt_offload *qopt)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक err;

	/* CBS offloading is only supported by i210 controller. */
	अगर (hw->mac.type != e1000_i210)
		वापस -EOPNOTSUPP;

	/* CBS offloading is only supported by queue 0 and queue 1. */
	अगर (qopt->queue < 0 || qopt->queue > 1)
		वापस -EINVAL;

	err = igb_save_cbs_params(adapter, qopt->queue, qopt->enable,
				  qopt->idleslope, qopt->sendslope,
				  qopt->hicredit, qopt->locredit);
	अगर (err)
		वापस err;

	igb_offload_apply(adapter, qopt->queue);

	वापस 0;
पूर्ण

#घोषणा ETHER_TYPE_FULL_MASK ((__क्रमce __be16)~0)
#घोषणा VLAN_PRIO_FULL_MASK (0x07)

अटल पूर्णांक igb_parse_cls_flower(काष्ठा igb_adapter *adapter,
				काष्ठा flow_cls_offload *f,
				पूर्णांक traffic_class,
				काष्ठा igb_nfc_filter *input)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	काष्ठा netlink_ext_ack *extack = f->common.extack;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Unsupported key used, only BASIC, CONTROL, ETH_ADDRS and VLAN are supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		अगर (!is_zero_ether_addr(match.mask->dst)) अणु
			अगर (!is_broadcast_ether_addr(match.mask->dst)) अणु
				NL_SET_ERR_MSG_MOD(extack, "Only full masks are supported for destination MAC address");
				वापस -EINVAL;
			पूर्ण

			input->filter.match_flags |=
				IGB_FILTER_FLAG_DST_MAC_ADDR;
			ether_addr_copy(input->filter.dst_addr, match.key->dst);
		पूर्ण

		अगर (!is_zero_ether_addr(match.mask->src)) अणु
			अगर (!is_broadcast_ether_addr(match.mask->src)) अणु
				NL_SET_ERR_MSG_MOD(extack, "Only full masks are supported for source MAC address");
				वापस -EINVAL;
			पूर्ण

			input->filter.match_flags |=
				IGB_FILTER_FLAG_SRC_MAC_ADDR;
			ether_addr_copy(input->filter.src_addr, match.key->src);
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		अगर (match.mask->n_proto) अणु
			अगर (match.mask->n_proto != ETHER_TYPE_FULL_MASK) अणु
				NL_SET_ERR_MSG_MOD(extack, "Only full mask is supported for EtherType filter");
				वापस -EINVAL;
			पूर्ण

			input->filter.match_flags |= IGB_FILTER_FLAG_ETHER_TYPE;
			input->filter.etype = match.key->n_proto;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		अगर (match.mask->vlan_priority) अणु
			अगर (match.mask->vlan_priority != VLAN_PRIO_FULL_MASK) अणु
				NL_SET_ERR_MSG_MOD(extack, "Only full mask is supported for VLAN priority");
				वापस -EINVAL;
			पूर्ण

			input->filter.match_flags |= IGB_FILTER_FLAG_VLAN_TCI;
			input->filter.vlan_tci = match.key->vlan_priority;
		पूर्ण
	पूर्ण

	input->action = traffic_class;
	input->cookie = f->cookie;

	वापस 0;
पूर्ण

अटल पूर्णांक igb_configure_clsflower(काष्ठा igb_adapter *adapter,
				   काष्ठा flow_cls_offload *cls_flower)
अणु
	काष्ठा netlink_ext_ack *extack = cls_flower->common.extack;
	काष्ठा igb_nfc_filter *filter, *f;
	पूर्णांक err, tc;

	tc = tc_classid_to_hwtc(adapter->netdev, cls_flower->classid);
	अगर (tc < 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid traffic class");
		वापस -EINVAL;
	पूर्ण

	filter = kzalloc(माप(*filter), GFP_KERNEL);
	अगर (!filter)
		वापस -ENOMEM;

	err = igb_parse_cls_flower(adapter, cls_flower, tc, filter);
	अगर (err < 0)
		जाओ err_parse;

	spin_lock(&adapter->nfc_lock);

	hlist_क्रम_each_entry(f, &adapter->nfc_filter_list, nfc_node) अणु
		अगर (!स_भेद(&f->filter, &filter->filter, माप(f->filter))) अणु
			err = -EEXIST;
			NL_SET_ERR_MSG_MOD(extack,
					   "This filter is already set in ethtool");
			जाओ err_locked;
		पूर्ण
	पूर्ण

	hlist_क्रम_each_entry(f, &adapter->cls_flower_list, nfc_node) अणु
		अगर (!स_भेद(&f->filter, &filter->filter, माप(f->filter))) अणु
			err = -EEXIST;
			NL_SET_ERR_MSG_MOD(extack,
					   "This filter is already set in cls_flower");
			जाओ err_locked;
		पूर्ण
	पूर्ण

	err = igb_add_filter(adapter, filter);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Could not add filter to the adapter");
		जाओ err_locked;
	पूर्ण

	hlist_add_head(&filter->nfc_node, &adapter->cls_flower_list);

	spin_unlock(&adapter->nfc_lock);

	वापस 0;

err_locked:
	spin_unlock(&adapter->nfc_lock);

err_parse:
	kमुक्त(filter);

	वापस err;
पूर्ण

अटल पूर्णांक igb_delete_clsflower(काष्ठा igb_adapter *adapter,
				काष्ठा flow_cls_offload *cls_flower)
अणु
	काष्ठा igb_nfc_filter *filter;
	पूर्णांक err;

	spin_lock(&adapter->nfc_lock);

	hlist_क्रम_each_entry(filter, &adapter->cls_flower_list, nfc_node)
		अगर (filter->cookie == cls_flower->cookie)
			अवरोध;

	अगर (!filter) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	err = igb_erase_filter(adapter, filter);
	अगर (err < 0)
		जाओ out;

	hlist_del(&filter->nfc_node);
	kमुक्त(filter);

out:
	spin_unlock(&adapter->nfc_lock);

	वापस err;
पूर्ण

अटल पूर्णांक igb_setup_tc_cls_flower(काष्ठा igb_adapter *adapter,
				   काष्ठा flow_cls_offload *cls_flower)
अणु
	चयन (cls_flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस igb_configure_clsflower(adapter, cls_flower);
	हाल FLOW_CLS_DESTROY:
		वापस igb_delete_clsflower(adapter, cls_flower);
	हाल FLOW_CLS_STATS:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक igb_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				 व्योम *cb_priv)
अणु
	काष्ठा igb_adapter *adapter = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(adapter->netdev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस igb_setup_tc_cls_flower(adapter, type_data);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक igb_offload_txसमय(काष्ठा igb_adapter *adapter,
			      काष्ठा tc_etf_qopt_offload *qopt)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक err;

	/* Launchसमय offloading is only supported by i210 controller. */
	अगर (hw->mac.type != e1000_i210)
		वापस -EOPNOTSUPP;

	/* Launchसमय offloading is only supported by queues 0 and 1. */
	अगर (qopt->queue < 0 || qopt->queue > 1)
		वापस -EINVAL;

	err = igb_save_txसमय_params(adapter, qopt->queue, qopt->enable);
	अगर (err)
		वापस err;

	igb_offload_apply(adapter, qopt->queue);

	वापस 0;
पूर्ण

अटल LIST_HEAD(igb_block_cb_list);

अटल पूर्णांक igb_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			व्योम *type_data)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(dev);

	चयन (type) अणु
	हाल TC_SETUP_QDISC_CBS:
		वापस igb_offload_cbs(adapter, type_data);
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &igb_block_cb_list,
						  igb_setup_tc_block_cb,
						  adapter, adapter, true);

	हाल TC_SETUP_QDISC_ETF:
		वापस igb_offload_txसमय(adapter, type_data);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक igb_xdp_setup(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf)
अणु
	पूर्णांक i, frame_size = dev->mtu + IGB_ETH_PKT_HDR_PAD;
	काष्ठा igb_adapter *adapter = netdev_priv(dev);
	काष्ठा bpf_prog *prog = bpf->prog, *old_prog;
	bool running = netअगर_running(dev);
	bool need_reset;

	/* verअगरy igb ring attributes are sufficient क्रम XDP */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा igb_ring *ring = adapter->rx_ring[i];

		अगर (frame_size > igb_rx_bufsz(ring)) अणु
			NL_SET_ERR_MSG_MOD(bpf->extack,
					   "The RX buffer size is too small for the frame size");
			netdev_warn(dev, "XDP RX buffer size %d is too small for the frame size %d\n",
				    igb_rx_bufsz(ring), frame_size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	old_prog = xchg(&adapter->xdp_prog, prog);
	need_reset = (!!prog != !!old_prog);

	/* device is up and bpf is added/हटाओd, must setup the RX queues */
	अगर (need_reset && running) अणु
		igb_बंद(dev);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			(व्योम)xchg(&adapter->rx_ring[i]->xdp_prog,
			    adapter->xdp_prog);
	पूर्ण

	अगर (old_prog)
		bpf_prog_put(old_prog);

	/* bpf is just replaced, RXQ and MTU are alपढ़ोy setup */
	अगर (!need_reset)
		वापस 0;

	अगर (running)
		igb_खोलो(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस igb_xdp_setup(dev, xdp);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम igb_xdp_ring_update_tail(काष्ठा igb_ring *ring)
अणु
	/* Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.
	 */
	wmb();
	ग_लिखोl(ring->next_to_use, ring->tail);
पूर्ण

अटल काष्ठा igb_ring *igb_xdp_tx_queue_mapping(काष्ठा igb_adapter *adapter)
अणु
	अचिन्हित पूर्णांक r_idx = smp_processor_id();

	अगर (r_idx >= adapter->num_tx_queues)
		r_idx = r_idx % adapter->num_tx_queues;

	वापस adapter->tx_ring[r_idx];
पूर्ण

अटल पूर्णांक igb_xdp_xmit_back(काष्ठा igb_adapter *adapter, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_frame *xdpf = xdp_convert_buff_to_frame(xdp);
	पूर्णांक cpu = smp_processor_id();
	काष्ठा igb_ring *tx_ring;
	काष्ठा netdev_queue *nq;
	u32 ret;

	अगर (unlikely(!xdpf))
		वापस IGB_XDP_CONSUMED;

	/* During program transitions its possible adapter->xdp_prog is asचिन्हित
	 * but ring has not been configured yet. In this हाल simply पात xmit.
	 */
	tx_ring = adapter->xdp_prog ? igb_xdp_tx_queue_mapping(adapter) : शून्य;
	अगर (unlikely(!tx_ring))
		वापस IGB_XDP_CONSUMED;

	nq = txring_txq(tx_ring);
	__netअगर_tx_lock(nq, cpu);
	/* Aव्योम transmit queue समयout since we share it with the slow path */
	nq->trans_start = jअगरfies;
	ret = igb_xmit_xdp_ring(adapter, tx_ring, xdpf);
	__netअगर_tx_unlock(nq);

	वापस ret;
पूर्ण

अटल पूर्णांक igb_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n,
			काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(dev);
	पूर्णांक cpu = smp_processor_id();
	काष्ठा igb_ring *tx_ring;
	काष्ठा netdev_queue *nq;
	पूर्णांक nxmit = 0;
	पूर्णांक i;

	अगर (unlikely(test_bit(__IGB_DOWN, &adapter->state)))
		वापस -ENETDOWN;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	/* During program transitions its possible adapter->xdp_prog is asचिन्हित
	 * but ring has not been configured yet. In this हाल simply पात xmit.
	 */
	tx_ring = adapter->xdp_prog ? igb_xdp_tx_queue_mapping(adapter) : शून्य;
	अगर (unlikely(!tx_ring))
		वापस -ENXIO;

	nq = txring_txq(tx_ring);
	__netअगर_tx_lock(nq, cpu);

	/* Aव्योम transmit queue समयout since we share it with the slow path */
	nq->trans_start = jअगरfies;

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdpf = frames[i];
		पूर्णांक err;

		err = igb_xmit_xdp_ring(adapter, tx_ring, xdpf);
		अगर (err != IGB_XDP_TX)
			अवरोध;
		nxmit++;
	पूर्ण

	__netअगर_tx_unlock(nq);

	अगर (unlikely(flags & XDP_XMIT_FLUSH))
		igb_xdp_ring_update_tail(tx_ring);

	वापस nxmit;
पूर्ण

अटल स्थिर काष्ठा net_device_ops igb_netdev_ops = अणु
	.nकरो_खोलो		= igb_खोलो,
	.nकरो_stop		= igb_बंद,
	.nकरो_start_xmit		= igb_xmit_frame,
	.nकरो_get_stats64	= igb_get_stats64,
	.nकरो_set_rx_mode	= igb_set_rx_mode,
	.nकरो_set_mac_address	= igb_set_mac,
	.nकरो_change_mtu		= igb_change_mtu,
	.nकरो_करो_ioctl		= igb_ioctl,
	.nकरो_tx_समयout		= igb_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_vlan_rx_add_vid	= igb_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= igb_vlan_rx_समाप्त_vid,
	.nकरो_set_vf_mac		= igb_nकरो_set_vf_mac,
	.nकरो_set_vf_vlan	= igb_nकरो_set_vf_vlan,
	.nकरो_set_vf_rate	= igb_nकरो_set_vf_bw,
	.nकरो_set_vf_spoofchk	= igb_nकरो_set_vf_spoofchk,
	.nकरो_set_vf_trust	= igb_nकरो_set_vf_trust,
	.nकरो_get_vf_config	= igb_nकरो_get_vf_config,
	.nकरो_fix_features	= igb_fix_features,
	.nकरो_set_features	= igb_set_features,
	.nकरो_fdb_add		= igb_nकरो_fdb_add,
	.nकरो_features_check	= igb_features_check,
	.nकरो_setup_tc		= igb_setup_tc,
	.nकरो_bpf		= igb_xdp,
	.nकरो_xdp_xmit		= igb_xdp_xmit,
पूर्ण;

/**
 * igb_set_fw_version - Configure version string क्रम ethtool
 * @adapter: adapter काष्ठा
 **/
व्योम igb_set_fw_version(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_fw_version fw;

	igb_get_fw_version(hw, &fw);

	चयन (hw->mac.type) अणु
	हाल e1000_i210:
	हाल e1000_i211:
		अगर (!(igb_get_flash_presence_i210(hw))) अणु
			snम_लिखो(adapter->fw_version,
				 माप(adapter->fw_version),
				 "%2d.%2d-%d",
				 fw.invm_major, fw.invm_minor,
				 fw.invm_img_type);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		/* अगर option is rom valid, display its version too */
		अगर (fw.or_valid) अणु
			snम_लिखो(adapter->fw_version,
				 माप(adapter->fw_version),
				 "%d.%d, 0x%08x, %d.%d.%d",
				 fw.eep_major, fw.eep_minor, fw.etrack_id,
				 fw.or_major, fw.or_build, fw.or_patch);
		/* no option rom */
		पूर्ण अन्यथा अगर (fw.etrack_id != 0X0000) अणु
			snम_लिखो(adapter->fw_version,
			    माप(adapter->fw_version),
			    "%d.%d, 0x%08x",
			    fw.eep_major, fw.eep_minor, fw.etrack_id);
		पूर्ण अन्यथा अणु
		snम_लिखो(adapter->fw_version,
		    माप(adapter->fw_version),
		    "%d.%d.%d",
		    fw.eep_major, fw.eep_minor, fw.eep_build);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/**
 * igb_init_mas - init Media Autosense feature अगर enabled in the NVM
 *
 * @adapter: adapter काष्ठा
 **/
अटल व्योम igb_init_mas(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 eeprom_data;

	hw->nvm.ops.पढ़ो(hw, NVM_COMPAT, 1, &eeprom_data);
	चयन (hw->bus.func) अणु
	हाल E1000_FUNC_0:
		अगर (eeprom_data & IGB_MAS_ENABLE_0) अणु
			adapter->flags |= IGB_FLAG_MAS_ENABLE;
			netdev_info(adapter->netdev,
				"MAS: Enabling Media Autosense for port %d\n",
				hw->bus.func);
		पूर्ण
		अवरोध;
	हाल E1000_FUNC_1:
		अगर (eeprom_data & IGB_MAS_ENABLE_1) अणु
			adapter->flags |= IGB_FLAG_MAS_ENABLE;
			netdev_info(adapter->netdev,
				"MAS: Enabling Media Autosense for port %d\n",
				hw->bus.func);
		पूर्ण
		अवरोध;
	हाल E1000_FUNC_2:
		अगर (eeprom_data & IGB_MAS_ENABLE_2) अणु
			adapter->flags |= IGB_FLAG_MAS_ENABLE;
			netdev_info(adapter->netdev,
				"MAS: Enabling Media Autosense for port %d\n",
				hw->bus.func);
		पूर्ण
		अवरोध;
	हाल E1000_FUNC_3:
		अगर (eeprom_data & IGB_MAS_ENABLE_3) अणु
			adapter->flags |= IGB_FLAG_MAS_ENABLE;
			netdev_info(adapter->netdev,
				"MAS: Enabling Media Autosense for port %d\n",
				hw->bus.func);
		पूर्ण
		अवरोध;
	शेष:
		/* Shouldn't get here */
		netdev_err(adapter->netdev,
			"MAS: Invalid port configuration, returning\n");
		अवरोध;
	पूर्ण
पूर्ण

/**
 *  igb_init_i2c - Init I2C पूर्णांकerface
 *  @adapter: poपूर्णांकer to adapter काष्ठाure
 **/
अटल s32 igb_init_i2c(काष्ठा igb_adapter *adapter)
अणु
	s32 status = 0;

	/* I2C पूर्णांकerface supported on i350 devices */
	अगर (adapter->hw.mac.type != e1000_i350)
		वापस 0;

	/* Initialize the i2c bus which is controlled by the रेजिस्टरs.
	 * This bus will use the i2c_algo_bit काष्ठाure that implements
	 * the protocol through toggling of the 4 bits in the रेजिस्टर.
	 */
	adapter->i2c_adap.owner = THIS_MODULE;
	adapter->i2c_algo = igb_i2c_algo;
	adapter->i2c_algo.data = adapter;
	adapter->i2c_adap.algo_data = &adapter->i2c_algo;
	adapter->i2c_adap.dev.parent = &adapter->pdev->dev;
	strlcpy(adapter->i2c_adap.name, "igb BB",
		माप(adapter->i2c_adap.name));
	status = i2c_bit_add_bus(&adapter->i2c_adap);
	वापस status;
पूर्ण

/**
 *  igb_probe - Device Initialization Routine
 *  @pdev: PCI device inक्रमmation काष्ठा
 *  @ent: entry in igb_pci_tbl
 *
 *  Returns 0 on success, negative on failure
 *
 *  igb_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 *  The OS initialization, configuring of the adapter निजी काष्ठाure,
 *  and a hardware reset occur.
 **/
अटल पूर्णांक igb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा igb_adapter *adapter;
	काष्ठा e1000_hw *hw;
	u16 eeprom_data = 0;
	s32 ret_val;
	अटल पूर्णांक global_quad_port_a; /* global quad port a indication */
	स्थिर काष्ठा e1000_info *ei = igb_info_tbl[ent->driver_data];
	पूर्णांक err, pci_using_dac;
	u8 part_str[E1000_PBANUM_LENGTH];

	/* Catch broken hardware that put the wrong VF device ID in
	 * the PCIe SR-IOV capability.
	 */
	अगर (pdev->is_virtfn) अणु
		WARN(1, KERN_ERR "%s (%x:%x) should not be a VF!\n",
			pci_name(pdev), pdev->venकरोr, pdev->device);
		वापस -EINVAL;
	पूर्ण

	err = pci_enable_device_mem(pdev);
	अगर (err)
		वापस err;

	pci_using_dac = 0;
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (!err) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"No usable DMA configuration, aborting\n");
			जाओ err_dma;
		पूर्ण
	पूर्ण

	err = pci_request_mem_regions(pdev, igb_driver_name);
	अगर (err)
		जाओ err_pci_reg;

	pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);
	pci_save_state(pdev);

	err = -ENOMEM;
	netdev = alloc_etherdev_mq(माप(काष्ठा igb_adapter),
				   IGB_MAX_TX_QUEUES);
	अगर (!netdev)
		जाओ err_alloc_etherdev;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	hw = &adapter->hw;
	hw->back = adapter;
	adapter->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	err = -EIO;
	adapter->io_addr = pci_iomap(pdev, 0, 0);
	अगर (!adapter->io_addr)
		जाओ err_ioremap;
	/* hw->hw_addr can be altered, we'll use adapter->io_addr क्रम unmap */
	hw->hw_addr = adapter->io_addr;

	netdev->netdev_ops = &igb_netdev_ops;
	igb_set_ethtool_ops(netdev);
	netdev->watchकरोg_समयo = 5 * HZ;

	म_नकलन(netdev->name, pci_name(pdev), माप(netdev->name) - 1);

	netdev->mem_start = pci_resource_start(pdev, 0);
	netdev->mem_end = pci_resource_end(pdev, 0);

	/* PCI config space info */
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->revision_id = pdev->revision;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_device_id = pdev->subप्रणाली_device;

	/* Copy the शेष MAC, PHY and NVM function poपूर्णांकers */
	स_नकल(&hw->mac.ops, ei->mac_ops, माप(hw->mac.ops));
	स_नकल(&hw->phy.ops, ei->phy_ops, माप(hw->phy.ops));
	स_नकल(&hw->nvm.ops, ei->nvm_ops, माप(hw->nvm.ops));
	/* Initialize skew-specअगरic स्थिरants */
	err = ei->get_invariants(hw);
	अगर (err)
		जाओ err_sw_init;

	/* setup the निजी काष्ठाure */
	err = igb_sw_init(adapter);
	अगर (err)
		जाओ err_sw_init;

	igb_get_bus_info_pcie(hw);

	hw->phy.स्वतःneg_रुको_to_complete = false;

	/* Copper options */
	अगर (hw->phy.media_type == e1000_media_type_copper) अणु
		hw->phy.mdix = AUTO_ALL_MODES;
		hw->phy.disable_polarity_correction = false;
		hw->phy.ms_type = e1000_ms_hw_शेष;
	पूर्ण

	अगर (igb_check_reset_block(hw))
		dev_info(&pdev->dev,
			"PHY reset is blocked due to SOL/IDER session.\n");

	/* features is initialized to 0 in allocation, it might have bits
	 * set by igb_sw_init so we should use an or instead of an
	 * assignment.
	 */
	netdev->features |= NETIF_F_SG |
			    NETIF_F_TSO |
			    NETIF_F_TSO6 |
			    NETIF_F_RXHASH |
			    NETIF_F_RXCSUM |
			    NETIF_F_HW_CSUM;

	अगर (hw->mac.type >= e1000_82576)
		netdev->features |= NETIF_F_SCTP_CRC | NETIF_F_GSO_UDP_L4;

	अगर (hw->mac.type >= e1000_i350)
		netdev->features |= NETIF_F_HW_TC;

#घोषणा IGB_GSO_PARTIAL_FEATURES (NETIF_F_GSO_GRE | \
				  NETIF_F_GSO_GRE_CSUM | \
				  NETIF_F_GSO_IPXIP4 | \
				  NETIF_F_GSO_IPXIP6 | \
				  NETIF_F_GSO_UDP_TUNNEL | \
				  NETIF_F_GSO_UDP_TUNNEL_CSUM)

	netdev->gso_partial_features = IGB_GSO_PARTIAL_FEATURES;
	netdev->features |= NETIF_F_GSO_PARTIAL | IGB_GSO_PARTIAL_FEATURES;

	/* copy netdev features पूर्णांकo list of user selectable features */
	netdev->hw_features |= netdev->features |
			       NETIF_F_HW_VLAN_CTAG_RX |
			       NETIF_F_HW_VLAN_CTAG_TX |
			       NETIF_F_RXALL;

	अगर (hw->mac.type >= e1000_i350)
		netdev->hw_features |= NETIF_F_NTUPLE;

	अगर (pci_using_dac)
		netdev->features |= NETIF_F_HIGHDMA;

	netdev->vlan_features |= netdev->features | NETIF_F_TSO_MANGLEID;
	netdev->mpls_features |= NETIF_F_HW_CSUM;
	netdev->hw_enc_features |= netdev->vlan_features;

	/* set this bit last since it cannot be part of vlan_features */
	netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER |
			    NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_TX;

	netdev->priv_flags |= IFF_SUPP_NOFCS;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	/* MTU range: 68 - 9216 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = MAX_STD_JUMBO_FRAME_SIZE;

	adapter->en_mng_pt = igb_enable_mng_pass_thru(hw);

	/* beक्रमe पढ़ोing the NVM, reset the controller to put the device in a
	 * known good starting state
	 */
	hw->mac.ops.reset_hw(hw);

	/* make sure the NVM is good , i211/i210 parts can have special NVM
	 * that करोesn't contain a checksum
	 */
	चयन (hw->mac.type) अणु
	हाल e1000_i210:
	हाल e1000_i211:
		अगर (igb_get_flash_presence_i210(hw)) अणु
			अगर (hw->nvm.ops.validate(hw) < 0) अणु
				dev_err(&pdev->dev,
					"The NVM Checksum Is Not Valid\n");
				err = -EIO;
				जाओ err_eeprom;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अगर (hw->nvm.ops.validate(hw) < 0) अणु
			dev_err(&pdev->dev, "The NVM Checksum Is Not Valid\n");
			err = -EIO;
			जाओ err_eeprom;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (eth_platक्रमm_get_mac_address(&pdev->dev, hw->mac.addr)) अणु
		/* copy the MAC address out of the NVM */
		अगर (hw->mac.ops.पढ़ो_mac_addr(hw))
			dev_err(&pdev->dev, "NVM Read Error\n");
	पूर्ण

	स_नकल(netdev->dev_addr, hw->mac.addr, netdev->addr_len);

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		dev_err(&pdev->dev, "Invalid MAC Address\n");
		err = -EIO;
		जाओ err_eeprom;
	पूर्ण

	igb_set_शेष_mac_filter(adapter);

	/* get firmware version क्रम ethtool -i */
	igb_set_fw_version(adapter);

	/* configure RXPBSIZE and TXPBSIZE */
	अगर (hw->mac.type == e1000_i210) अणु
		wr32(E1000_RXPBS, I210_RXPBSIZE_DEFAULT);
		wr32(E1000_TXPBS, I210_TXPBSIZE_DEFAULT);
	पूर्ण

	समयr_setup(&adapter->watchकरोg_समयr, igb_watchकरोg, 0);
	समयr_setup(&adapter->phy_info_समयr, igb_update_phy_info, 0);

	INIT_WORK(&adapter->reset_task, igb_reset_task);
	INIT_WORK(&adapter->watchकरोg_task, igb_watchकरोg_task);

	/* Initialize link properties that are user-changeable */
	adapter->fc_स्वतःneg = true;
	hw->mac.स्वतःneg = true;
	hw->phy.स्वतःneg_advertised = 0x2f;

	hw->fc.requested_mode = e1000_fc_शेष;
	hw->fc.current_mode = e1000_fc_शेष;

	igb_validate_mdi_setting(hw);

	/* By शेष, support wake on port A */
	अगर (hw->bus.func == 0)
		adapter->flags |= IGB_FLAG_WOL_SUPPORTED;

	/* Check the NVM क्रम wake support on non-port A ports */
	अगर (hw->mac.type >= e1000_82580)
		hw->nvm.ops.पढ़ो(hw, NVM_INIT_CONTROL3_PORT_A +
				 NVM_82580_LAN_FUNC_OFFSET(hw->bus.func), 1,
				 &eeprom_data);
	अन्यथा अगर (hw->bus.func == 1)
		hw->nvm.ops.पढ़ो(hw, NVM_INIT_CONTROL3_PORT_B, 1, &eeprom_data);

	अगर (eeprom_data & IGB_EEPROM_APME)
		adapter->flags |= IGB_FLAG_WOL_SUPPORTED;

	/* now that we have the eeprom settings, apply the special हालs where
	 * the eeprom may be wrong or the board simply won't support wake on
	 * lan on a particular port
	 */
	चयन (pdev->device) अणु
	हाल E1000_DEV_ID_82575GB_QUAD_COPPER:
		adapter->flags &= ~IGB_FLAG_WOL_SUPPORTED;
		अवरोध;
	हाल E1000_DEV_ID_82575EB_FIBER_SERDES:
	हाल E1000_DEV_ID_82576_FIBER:
	हाल E1000_DEV_ID_82576_SERDES:
		/* Wake events only supported on port A क्रम dual fiber
		 * regardless of eeprom setting
		 */
		अगर (rd32(E1000_STATUS) & E1000_STATUS_FUNC_1)
			adapter->flags &= ~IGB_FLAG_WOL_SUPPORTED;
		अवरोध;
	हाल E1000_DEV_ID_82576_QUAD_COPPER:
	हाल E1000_DEV_ID_82576_QUAD_COPPER_ET2:
		/* अगर quad port adapter, disable WoL on all but port A */
		अगर (global_quad_port_a != 0)
			adapter->flags &= ~IGB_FLAG_WOL_SUPPORTED;
		अन्यथा
			adapter->flags |= IGB_FLAG_QUAD_PORT_A;
		/* Reset क्रम multiple quad port adapters */
		अगर (++global_quad_port_a == 4)
			global_quad_port_a = 0;
		अवरोध;
	शेष:
		/* If the device can't wake, don't set software support */
		अगर (!device_can_wakeup(&adapter->pdev->dev))
			adapter->flags &= ~IGB_FLAG_WOL_SUPPORTED;
	पूर्ण

	/* initialize the wol settings based on the eeprom settings */
	अगर (adapter->flags & IGB_FLAG_WOL_SUPPORTED)
		adapter->wol |= E1000_WUFC_MAG;

	/* Some venकरोrs want WoL disabled by शेष, but still supported */
	अगर ((hw->mac.type == e1000_i350) &&
	    (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_HP)) अणु
		adapter->flags |= IGB_FLAG_WOL_SUPPORTED;
		adapter->wol = 0;
	पूर्ण

	/* Some venकरोrs want the ability to Use the EEPROM setting as
	 * enable/disable only, and not क्रम capability
	 */
	अगर (((hw->mac.type == e1000_i350) ||
	     (hw->mac.type == e1000_i354)) &&
	    (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_DELL)) अणु
		adapter->flags |= IGB_FLAG_WOL_SUPPORTED;
		adapter->wol = 0;
	पूर्ण
	अगर (hw->mac.type == e1000_i350) अणु
		अगर (((pdev->subप्रणाली_device == 0x5001) ||
		     (pdev->subप्रणाली_device == 0x5002)) &&
				(hw->bus.func == 0)) अणु
			adapter->flags |= IGB_FLAG_WOL_SUPPORTED;
			adapter->wol = 0;
		पूर्ण
		अगर (pdev->subप्रणाली_device == 0x1F52)
			adapter->flags |= IGB_FLAG_WOL_SUPPORTED;
	पूर्ण

	device_set_wakeup_enable(&adapter->pdev->dev,
				 adapter->flags & IGB_FLAG_WOL_SUPPORTED);

	/* reset the hardware with the new settings */
	igb_reset(adapter);

	/* Init the I2C पूर्णांकerface */
	err = igb_init_i2c(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to init i2c interface\n");
		जाओ err_eeprom;
	पूर्ण

	/* let the f/w know that the h/w is now under the control of the
	 * driver.
	 */
	igb_get_hw_control(adapter);

	म_नकल(netdev->name, "eth%d");
	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;

	/* carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

#अगर_घोषित CONFIG_IGB_DCA
	अगर (dca_add_requester(&pdev->dev) == 0) अणु
		adapter->flags |= IGB_FLAG_DCA_ENABLED;
		dev_info(&pdev->dev, "DCA enabled\n");
		igb_setup_dca(adapter);
	पूर्ण

#पूर्ण_अगर
#अगर_घोषित CONFIG_IGB_HWMON
	/* Initialize the thermal sensor on i350 devices. */
	अगर (hw->mac.type == e1000_i350 && hw->bus.func == 0) अणु
		u16 ets_word;

		/* Read the NVM to determine अगर this i350 device supports an
		 * बाह्यal thermal sensor.
		 */
		hw->nvm.ops.पढ़ो(hw, NVM_ETS_CFG, 1, &ets_word);
		अगर (ets_word != 0x0000 && ets_word != 0xFFFF)
			adapter->ets = true;
		अन्यथा
			adapter->ets = false;
		अगर (igb_sysfs_init(adapter))
			dev_err(&pdev->dev,
				"failed to allocate sysfs resources\n");
	पूर्ण अन्यथा अणु
		adapter->ets = false;
	पूर्ण
#पूर्ण_अगर
	/* Check अगर Media Autosense is enabled */
	adapter->ei = *ei;
	अगर (hw->dev_spec._82575.mas_capable)
		igb_init_mas(adapter);

	/* करो hw tstamp init after resetting */
	igb_ptp_init(adapter);

	dev_info(&pdev->dev, "Intel(R) Gigabit Ethernet Network Connection\n");
	/* prपूर्णांक bus type/speed/width info, not applicable to i354 */
	अगर (hw->mac.type != e1000_i354) अणु
		dev_info(&pdev->dev, "%s: (PCIe:%s:%s) %pM\n",
			 netdev->name,
			 ((hw->bus.speed == e1000_bus_speed_2500) ? "2.5Gb/s" :
			  (hw->bus.speed == e1000_bus_speed_5000) ? "5.0Gb/s" :
			   "unknown"),
			 ((hw->bus.width == e1000_bus_width_pcie_x4) ?
			  "Width x4" :
			  (hw->bus.width == e1000_bus_width_pcie_x2) ?
			  "Width x2" :
			  (hw->bus.width == e1000_bus_width_pcie_x1) ?
			  "Width x1" : "unknown"), netdev->dev_addr);
	पूर्ण

	अगर ((hw->mac.type == e1000_82576 &&
	     rd32(E1000_EECD) & E1000_EECD_PRES) ||
	    (hw->mac.type >= e1000_i210 ||
	     igb_get_flash_presence_i210(hw))) अणु
		ret_val = igb_पढ़ो_part_string(hw, part_str,
					       E1000_PBANUM_LENGTH);
	पूर्ण अन्यथा अणु
		ret_val = -E1000_ERR_INVM_VALUE_NOT_FOUND;
	पूर्ण

	अगर (ret_val)
		म_नकल(part_str, "Unknown");
	dev_info(&pdev->dev, "%s: PBA No: %s\n", netdev->name, part_str);
	dev_info(&pdev->dev,
		"Using %s interrupts. %d rx queue(s), %d tx queue(s)\n",
		(adapter->flags & IGB_FLAG_HAS_MSIX) ? "MSI-X" :
		(adapter->flags & IGB_FLAG_HAS_MSI) ? "MSI" : "legacy",
		adapter->num_rx_queues, adapter->num_tx_queues);
	अगर (hw->phy.media_type == e1000_media_type_copper) अणु
		चयन (hw->mac.type) अणु
		हाल e1000_i350:
		हाल e1000_i210:
		हाल e1000_i211:
			/* Enable EEE क्रम पूर्णांकernal copper PHY devices */
			err = igb_set_eee_i350(hw, true, true);
			अगर ((!err) &&
			    (!hw->dev_spec._82575.eee_disable)) अणु
				adapter->eee_advert =
					MDIO_EEE_100TX | MDIO_EEE_1000T;
				adapter->flags |= IGB_FLAG_EEE;
			पूर्ण
			अवरोध;
		हाल e1000_i354:
			अगर ((rd32(E1000_CTRL_EXT) &
			    E1000_CTRL_EXT_LINK_MODE_SGMII)) अणु
				err = igb_set_eee_i354(hw, true, true);
				अगर ((!err) &&
					(!hw->dev_spec._82575.eee_disable)) अणु
					adapter->eee_advert =
					   MDIO_EEE_100TX | MDIO_EEE_1000T;
					adapter->flags |= IGB_FLAG_EEE;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	dev_pm_set_driver_flags(&pdev->dev, DPM_FLAG_NO_सूचीECT_COMPLETE);

	pm_runसमय_put_noidle(&pdev->dev);
	वापस 0;

err_रेजिस्टर:
	igb_release_hw_control(adapter);
	स_रखो(&adapter->i2c_adap, 0, माप(adapter->i2c_adap));
err_eeprom:
	अगर (!igb_check_reset_block(hw))
		igb_reset_phy(hw);

	अगर (hw->flash_address)
		iounmap(hw->flash_address);
err_sw_init:
	kमुक्त(adapter->mac_table);
	kमुक्त(adapter->shaकरोw_vfta);
	igb_clear_पूर्णांकerrupt_scheme(adapter);
#अगर_घोषित CONFIG_PCI_IOV
	igb_disable_sriov(pdev);
#पूर्ण_अगर
	pci_iounmap(pdev, adapter->io_addr);
err_ioremap:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_mem_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
अटल पूर्णांक igb_disable_sriov(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* reclaim resources allocated to VFs */
	अगर (adapter->vf_data) अणु
		/* disable iov and allow समय क्रम transactions to clear */
		अगर (pci_vfs_asचिन्हित(pdev)) अणु
			dev_warn(&pdev->dev,
				 "Cannot deallocate SR-IOV virtual functions while they are assigned - VFs will not be deallocated\n");
			वापस -EPERM;
		पूर्ण अन्यथा अणु
			pci_disable_sriov(pdev);
			msleep(500);
		पूर्ण

		kमुक्त(adapter->vf_mac_list);
		adapter->vf_mac_list = शून्य;
		kमुक्त(adapter->vf_data);
		adapter->vf_data = शून्य;
		adapter->vfs_allocated_count = 0;
		wr32(E1000_IOVCTL, E1000_IOVCTL_REUSE_VFQ);
		wrfl();
		msleep(100);
		dev_info(&pdev->dev, "IOV Disabled\n");

		/* Re-enable DMA Coalescing flag since IOV is turned off */
		adapter->flags |= IGB_FLAG_DMAC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igb_enable_sriov(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	पूर्णांक old_vfs = pci_num_vf(pdev);
	काष्ठा vf_mac_filter *mac_list;
	पूर्णांक err = 0;
	पूर्णांक num_vf_mac_filters, i;

	अगर (!(adapter->flags & IGB_FLAG_HAS_MSIX) || num_vfs > 7) अणु
		err = -EPERM;
		जाओ out;
	पूर्ण
	अगर (!num_vfs)
		जाओ out;

	अगर (old_vfs) अणु
		dev_info(&pdev->dev, "%d pre-allocated VFs found - override max_vfs setting of %d\n",
			 old_vfs, max_vfs);
		adapter->vfs_allocated_count = old_vfs;
	पूर्ण अन्यथा
		adapter->vfs_allocated_count = num_vfs;

	adapter->vf_data = kसुस्मृति(adapter->vfs_allocated_count,
				माप(काष्ठा vf_data_storage), GFP_KERNEL);

	/* अगर allocation failed then we करो not support SR-IOV */
	अगर (!adapter->vf_data) अणु
		adapter->vfs_allocated_count = 0;
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Due to the limited number of RAR entries calculate potential
	 * number of MAC filters available क्रम the VFs. Reserve entries
	 * क्रम PF शेष MAC, PF MAC filters and at least one RAR entry
	 * क्रम each VF क्रम VF MAC.
	 */
	num_vf_mac_filters = adapter->hw.mac.rar_entry_count -
			     (1 + IGB_PF_MAC_FILTERS_RESERVED +
			      adapter->vfs_allocated_count);

	adapter->vf_mac_list = kसुस्मृति(num_vf_mac_filters,
				       माप(काष्ठा vf_mac_filter),
				       GFP_KERNEL);

	mac_list = adapter->vf_mac_list;
	INIT_LIST_HEAD(&adapter->vf_macs.l);

	अगर (adapter->vf_mac_list) अणु
		/* Initialize list of VF MAC filters */
		क्रम (i = 0; i < num_vf_mac_filters; i++) अणु
			mac_list->vf = -1;
			mac_list->मुक्त = true;
			list_add(&mac_list->l, &adapter->vf_macs.l);
			mac_list++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If we could not allocate memory क्रम the VF MAC filters
		 * we can जारी without this feature but warn user.
		 */
		dev_err(&pdev->dev,
			"Unable to allocate memory for VF MAC filter list\n");
	पूर्ण

	/* only call pci_enable_sriov() अगर no VFs are allocated alपढ़ोy */
	अगर (!old_vfs) अणु
		err = pci_enable_sriov(pdev, adapter->vfs_allocated_count);
		अगर (err)
			जाओ err_out;
	पूर्ण
	dev_info(&pdev->dev, "%d VFs allocated\n",
		 adapter->vfs_allocated_count);
	क्रम (i = 0; i < adapter->vfs_allocated_count; i++)
		igb_vf_configure(adapter, i);

	/* DMA Coalescing is not supported in IOV mode. */
	adapter->flags &= ~IGB_FLAG_DMAC;
	जाओ out;

err_out:
	kमुक्त(adapter->vf_mac_list);
	adapter->vf_mac_list = शून्य;
	kमुक्त(adapter->vf_data);
	adapter->vf_data = शून्य;
	adapter->vfs_allocated_count = 0;
out:
	वापस err;
पूर्ण

#पूर्ण_अगर
/**
 *  igb_हटाओ_i2c - Cleanup  I2C पूर्णांकerface
 *  @adapter: poपूर्णांकer to adapter काष्ठाure
 **/
अटल व्योम igb_हटाओ_i2c(काष्ठा igb_adapter *adapter)
अणु
	/* मुक्त the adapter bus काष्ठाure */
	i2c_del_adapter(&adapter->i2c_adap);
पूर्ण

/**
 *  igb_हटाओ - Device Removal Routine
 *  @pdev: PCI device inक्रमmation काष्ठा
 *
 *  igb_हटाओ is called by the PCI subप्रणाली to alert the driver
 *  that it should release a PCI device.  The could be caused by a
 *  Hot-Plug event, or because the driver is going to be हटाओd from
 *  memory.
 **/
अटल व्योम igb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	pm_runसमय_get_noresume(&pdev->dev);
#अगर_घोषित CONFIG_IGB_HWMON
	igb_sysfs_निकास(adapter);
#पूर्ण_अगर
	igb_हटाओ_i2c(adapter);
	igb_ptp_stop(adapter);
	/* The watchकरोg समयr may be rescheduled, so explicitly
	 * disable watchकरोg from being rescheduled.
	 */
	set_bit(__IGB_DOWN, &adapter->state);
	del_समयr_sync(&adapter->watchकरोg_समयr);
	del_समयr_sync(&adapter->phy_info_समयr);

	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->watchकरोg_task);

#अगर_घोषित CONFIG_IGB_DCA
	अगर (adapter->flags & IGB_FLAG_DCA_ENABLED) अणु
		dev_info(&pdev->dev, "DCA disabled\n");
		dca_हटाओ_requester(&pdev->dev);
		adapter->flags &= ~IGB_FLAG_DCA_ENABLED;
		wr32(E1000_DCA_CTRL, E1000_DCA_CTRL_DCA_MODE_DISABLE);
	पूर्ण
#पूर्ण_अगर

	/* Release control of h/w to f/w.  If f/w is AMT enabled, this
	 * would have alपढ़ोy happened in बंद and is redundant.
	 */
	igb_release_hw_control(adapter);

#अगर_घोषित CONFIG_PCI_IOV
	igb_disable_sriov(pdev);
#पूर्ण_अगर

	unरेजिस्टर_netdev(netdev);

	igb_clear_पूर्णांकerrupt_scheme(adapter);

	pci_iounmap(pdev, adapter->io_addr);
	अगर (hw->flash_address)
		iounmap(hw->flash_address);
	pci_release_mem_regions(pdev);

	kमुक्त(adapter->mac_table);
	kमुक्त(adapter->shaकरोw_vfta);
	मुक्त_netdev(netdev);

	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
पूर्ण

/**
 *  igb_probe_vfs - Initialize vf data storage and add VFs to pci config space
 *  @adapter: board निजी काष्ठाure to initialize
 *
 *  This function initializes the vf specअगरic data storage and then attempts to
 *  allocate the VFs.  The reason क्रम ordering it this way is because it is much
 *  mor expensive समय wise to disable SR-IOV than it is to allocate and मुक्त
 *  the memory क्रम the VFs.
 **/
अटल व्योम igb_probe_vfs(काष्ठा igb_adapter *adapter)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* Virtualization features not supported on i210 family. */
	अगर ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211))
		वापस;

	/* Of the below we really only want the effect of getting
	 * IGB_FLAG_HAS_MSIX set (अगर available), without which
	 * igb_enable_sriov() has no effect.
	 */
	igb_set_पूर्णांकerrupt_capability(adapter, true);
	igb_reset_पूर्णांकerrupt_capability(adapter);

	pci_sriov_set_totalvfs(pdev, 7);
	igb_enable_sriov(pdev, max_vfs);

#पूर्ण_अगर /* CONFIG_PCI_IOV */
पूर्ण

अचिन्हित पूर्णांक igb_get_max_rss_queues(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	अचिन्हित पूर्णांक max_rss_queues;

	/* Determine the maximum number of RSS queues supported. */
	चयन (hw->mac.type) अणु
	हाल e1000_i211:
		max_rss_queues = IGB_MAX_RX_QUEUES_I211;
		अवरोध;
	हाल e1000_82575:
	हाल e1000_i210:
		max_rss_queues = IGB_MAX_RX_QUEUES_82575;
		अवरोध;
	हाल e1000_i350:
		/* I350 cannot करो RSS and SR-IOV at the same समय */
		अगर (!!adapter->vfs_allocated_count) अणु
			max_rss_queues = 1;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल e1000_82576:
		अगर (!!adapter->vfs_allocated_count) अणु
			max_rss_queues = 2;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल e1000_82580:
	हाल e1000_i354:
	शेष:
		max_rss_queues = IGB_MAX_RX_QUEUES;
		अवरोध;
	पूर्ण

	वापस max_rss_queues;
पूर्ण

अटल व्योम igb_init_queue_configuration(काष्ठा igb_adapter *adapter)
अणु
	u32 max_rss_queues;

	max_rss_queues = igb_get_max_rss_queues(adapter);
	adapter->rss_queues = min_t(u32, max_rss_queues, num_online_cpus());

	igb_set_flag_queue_pairs(adapter, max_rss_queues);
पूर्ण

व्योम igb_set_flag_queue_pairs(काष्ठा igb_adapter *adapter,
			      स्थिर u32 max_rss_queues)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* Determine अगर we need to pair queues. */
	चयन (hw->mac.type) अणु
	हाल e1000_82575:
	हाल e1000_i211:
		/* Device supports enough पूर्णांकerrupts without queue pairing. */
		अवरोध;
	हाल e1000_82576:
	हाल e1000_82580:
	हाल e1000_i350:
	हाल e1000_i354:
	हाल e1000_i210:
	शेष:
		/* If rss_queues > half of max_rss_queues, pair the queues in
		 * order to conserve पूर्णांकerrupts due to limited supply.
		 */
		अगर (adapter->rss_queues > (max_rss_queues / 2))
			adapter->flags |= IGB_FLAG_QUEUE_PAIRS;
		अन्यथा
			adapter->flags &= ~IGB_FLAG_QUEUE_PAIRS;
		अवरोध;
	पूर्ण
पूर्ण

/**
 *  igb_sw_init - Initialize general software काष्ठाures (काष्ठा igb_adapter)
 *  @adapter: board निजी काष्ठाure to initialize
 *
 *  igb_sw_init initializes the Adapter निजी data काष्ठाure.
 *  Fields are initialized based on PCI device inक्रमmation and
 *  OS network device settings (MTU size).
 **/
अटल पूर्णांक igb_sw_init(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &hw->bus.pci_cmd_word);

	/* set शेष ring sizes */
	adapter->tx_ring_count = IGB_DEFAULT_TXD;
	adapter->rx_ring_count = IGB_DEFAULT_RXD;

	/* set शेष ITR values */
	adapter->rx_itr_setting = IGB_DEFAULT_ITR;
	adapter->tx_itr_setting = IGB_DEFAULT_ITR;

	/* set शेष work limits */
	adapter->tx_work_limit = IGB_DEFAULT_TX_WORK;

	adapter->max_frame_size = netdev->mtu + IGB_ETH_PKT_HDR_PAD;
	adapter->min_frame_size = ETH_ZLEN + ETH_FCS_LEN;

	spin_lock_init(&adapter->nfc_lock);
	spin_lock_init(&adapter->stats64_lock);
#अगर_घोषित CONFIG_PCI_IOV
	चयन (hw->mac.type) अणु
	हाल e1000_82576:
	हाल e1000_i350:
		अगर (max_vfs > 7) अणु
			dev_warn(&pdev->dev,
				 "Maximum of 7 VFs per PF, using max\n");
			max_vfs = adapter->vfs_allocated_count = 7;
		पूर्ण अन्यथा
			adapter->vfs_allocated_count = max_vfs;
		अगर (adapter->vfs_allocated_count)
			dev_warn(&pdev->dev,
				 "Enabling SR-IOV VFs using the module parameter is deprecated - please use the pci sysfs interface.\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

	/* Assume MSI-X पूर्णांकerrupts, will be checked during IRQ allocation */
	adapter->flags |= IGB_FLAG_HAS_MSIX;

	adapter->mac_table = kसुस्मृति(hw->mac.rar_entry_count,
				     माप(काष्ठा igb_mac_addr),
				     GFP_KERNEL);
	अगर (!adapter->mac_table)
		वापस -ENOMEM;

	igb_probe_vfs(adapter);

	igb_init_queue_configuration(adapter);

	/* Setup and initialize a copy of the hw vlan table array */
	adapter->shaकरोw_vfta = kसुस्मृति(E1000_VLAN_FILTER_TBL_SIZE, माप(u32),
				       GFP_KERNEL);
	अगर (!adapter->shaकरोw_vfta)
		वापस -ENOMEM;

	/* This call may decrease the number of queues */
	अगर (igb_init_पूर्णांकerrupt_scheme(adapter, true)) अणु
		dev_err(&pdev->dev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण

	/* Explicitly disable IRQ since the NIC can be in any state. */
	igb_irq_disable(adapter);

	अगर (hw->mac.type >= e1000_i350)
		adapter->flags &= ~IGB_FLAG_DMAC;

	set_bit(__IGB_DOWN, &adapter->state);
	वापस 0;
पूर्ण

/**
 *  __igb_खोलो - Called when a network पूर्णांकerface is made active
 *  @netdev: network पूर्णांकerface device काष्ठाure
 *  @resuming: indicates whether we are in a resume call
 *
 *  Returns 0 on success, negative value on failure
 *
 *  The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 *  active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 *  क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 *  handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 *  and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 **/
अटल पूर्णांक __igb_खोलो(काष्ठा net_device *netdev, bool resuming)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err;
	पूर्णांक i;

	/* disallow खोलो during test */
	अगर (test_bit(__IGB_TESTING, &adapter->state)) अणु
		WARN_ON(resuming);
		वापस -EBUSY;
	पूर्ण

	अगर (!resuming)
		pm_runसमय_get_sync(&pdev->dev);

	netअगर_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = igb_setup_all_tx_resources(adapter);
	अगर (err)
		जाओ err_setup_tx;

	/* allocate receive descriptors */
	err = igb_setup_all_rx_resources(adapter);
	अगर (err)
		जाओ err_setup_rx;

	igb_घातer_up_link(adapter);

	/* beक्रमe we allocate an पूर्णांकerrupt, we must be पढ़ोy to handle it.
	 * Setting DEBUG_SHIRQ in the kernel makes it fire an पूर्णांकerrupt
	 * as soon as we call pci_request_irq, so we have to setup our
	 * clean_rx handler beक्रमe we करो so.
	 */
	igb_configure(adapter);

	err = igb_request_irq(adapter);
	अगर (err)
		जाओ err_req_irq;

	/* Notअगरy the stack of the actual queue counts. */
	err = netअगर_set_real_num_tx_queues(adapter->netdev,
					   adapter->num_tx_queues);
	अगर (err)
		जाओ err_set_queues;

	err = netअगर_set_real_num_rx_queues(adapter->netdev,
					   adapter->num_rx_queues);
	अगर (err)
		जाओ err_set_queues;

	/* From here on the code is the same as igb_up() */
	clear_bit(__IGB_DOWN, &adapter->state);

	क्रम (i = 0; i < adapter->num_q_vectors; i++)
		napi_enable(&(adapter->q_vector[i]->napi));

	/* Clear any pending पूर्णांकerrupts. */
	rd32(E1000_TSICR);
	rd32(E1000_ICR);

	igb_irq_enable(adapter);

	/* notअगरy VFs that reset has been completed */
	अगर (adapter->vfs_allocated_count) अणु
		u32 reg_data = rd32(E1000_CTRL_EXT);

		reg_data |= E1000_CTRL_EXT_PFRSTD;
		wr32(E1000_CTRL_EXT, reg_data);
	पूर्ण

	netअगर_tx_start_all_queues(netdev);

	अगर (!resuming)
		pm_runसमय_put(&pdev->dev);

	/* start the watchकरोg. */
	hw->mac.get_link_status = 1;
	schedule_work(&adapter->watchकरोg_task);

	वापस 0;

err_set_queues:
	igb_मुक्त_irq(adapter);
err_req_irq:
	igb_release_hw_control(adapter);
	igb_घातer_करोwn_link(adapter);
	igb_मुक्त_all_rx_resources(adapter);
err_setup_rx:
	igb_मुक्त_all_tx_resources(adapter);
err_setup_tx:
	igb_reset(adapter);
	अगर (!resuming)
		pm_runसमय_put(&pdev->dev);

	वापस err;
पूर्ण

पूर्णांक igb_खोलो(काष्ठा net_device *netdev)
अणु
	वापस __igb_खोलो(netdev, false);
पूर्ण

/**
 *  __igb_बंद - Disables a network पूर्णांकerface
 *  @netdev: network पूर्णांकerface device काष्ठाure
 *  @suspending: indicates we are in a suspend call
 *
 *  Returns 0, this is not allowed to fail
 *
 *  The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 *  by the OS.  The hardware is still under the driver's control, but
 *  needs to be disabled.  A global MAC reset is issued to stop the
 *  hardware, and all transmit and receive resources are मुक्तd.
 **/
अटल पूर्णांक __igb_बंद(काष्ठा net_device *netdev, bool suspending)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;

	WARN_ON(test_bit(__IGB_RESETTING, &adapter->state));

	अगर (!suspending)
		pm_runसमय_get_sync(&pdev->dev);

	igb_करोwn(adapter);
	igb_मुक्त_irq(adapter);

	igb_मुक्त_all_tx_resources(adapter);
	igb_मुक्त_all_rx_resources(adapter);

	अगर (!suspending)
		pm_runसमय_put_sync(&pdev->dev);
	वापस 0;
पूर्ण

पूर्णांक igb_बंद(काष्ठा net_device *netdev)
अणु
	अगर (netअगर_device_present(netdev) || netdev->dismantle)
		वापस __igb_बंद(netdev, false);
	वापस 0;
पूर्ण

/**
 *  igb_setup_tx_resources - allocate Tx resources (Descriptors)
 *  @tx_ring: tx descriptor ring (क्रम a specअगरic queue) to setup
 *
 *  Return 0 on success, negative on failure
 **/
पूर्णांक igb_setup_tx_resources(काष्ठा igb_ring *tx_ring)
अणु
	काष्ठा device *dev = tx_ring->dev;
	पूर्णांक size;

	size = माप(काष्ठा igb_tx_buffer) * tx_ring->count;

	tx_ring->tx_buffer_info = vदो_स्मृति(size);
	अगर (!tx_ring->tx_buffer_info)
		जाओ err;

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * माप(जोड़ e1000_adv_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);

	tx_ring->desc = dma_alloc_coherent(dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	अगर (!tx_ring->desc)
		जाओ err;

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	वापस 0;

err:
	vमुक्त(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = शून्य;
	dev_err(dev, "Unable to allocate memory for the Tx descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 *  igb_setup_all_tx_resources - wrapper to allocate Tx resources
 *				 (Descriptors) क्रम all queues
 *  @adapter: board निजी काष्ठाure
 *
 *  Return 0 on success, negative on failure
 **/
अटल पूर्णांक igb_setup_all_tx_resources(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		err = igb_setup_tx_resources(adapter->tx_ring[i]);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Allocation for Tx Queue %u failed\n", i);
			क्रम (i--; i >= 0; i--)
				igb_मुक्त_tx_resources(adapter->tx_ring[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 *  igb_setup_tctl - configure the transmit control रेजिस्टरs
 *  @adapter: Board निजी काष्ठाure
 **/
व्योम igb_setup_tctl(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tctl;

	/* disable queue 0 which is enabled by शेष on 82575 and 82576 */
	wr32(E1000_TXDCTL(0), 0);

	/* Program the Transmit Control Register */
	tctl = rd32(E1000_TCTL);
	tctl &= ~E1000_TCTL_CT;
	tctl |= E1000_TCTL_PSP | E1000_TCTL_RTLC |
		(E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT);

	igb_config_collision_dist(hw);

	/* Enable transmits */
	tctl |= E1000_TCTL_EN;

	wr32(E1000_TCTL, tctl);
पूर्ण

/**
 *  igb_configure_tx_ring - Configure transmit ring after Reset
 *  @adapter: board निजी काष्ठाure
 *  @ring: tx ring to configure
 *
 *  Configure a transmit ring after a reset.
 **/
व्योम igb_configure_tx_ring(काष्ठा igb_adapter *adapter,
			   काष्ठा igb_ring *ring)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 txdctl = 0;
	u64 tdba = ring->dma;
	पूर्णांक reg_idx = ring->reg_idx;

	wr32(E1000_TDLEN(reg_idx),
	     ring->count * माप(जोड़ e1000_adv_tx_desc));
	wr32(E1000_TDBAL(reg_idx),
	     tdba & 0x00000000ffffffffULL);
	wr32(E1000_TDBAH(reg_idx), tdba >> 32);

	ring->tail = adapter->io_addr + E1000_TDT(reg_idx);
	wr32(E1000_TDH(reg_idx), 0);
	ग_लिखोl(0, ring->tail);

	txdctl |= IGB_TX_PTHRESH;
	txdctl |= IGB_TX_HTHRESH << 8;
	txdctl |= IGB_TX_WTHRESH << 16;

	/* reinitialize tx_buffer_info */
	स_रखो(ring->tx_buffer_info, 0,
	       माप(काष्ठा igb_tx_buffer) * ring->count);

	txdctl |= E1000_TXDCTL_QUEUE_ENABLE;
	wr32(E1000_TXDCTL(reg_idx), txdctl);
पूर्ण

/**
 *  igb_configure_tx - Configure transmit Unit after Reset
 *  @adapter: board निजी काष्ठाure
 *
 *  Configure the Tx unit of the MAC after a reset.
 **/
अटल व्योम igb_configure_tx(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक i;

	/* disable the queues */
	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		wr32(E1000_TXDCTL(adapter->tx_ring[i]->reg_idx), 0);

	wrfl();
	usleep_range(10000, 20000);

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		igb_configure_tx_ring(adapter, adapter->tx_ring[i]);
पूर्ण

/**
 *  igb_setup_rx_resources - allocate Rx resources (Descriptors)
 *  @rx_ring: Rx descriptor ring (क्रम a specअगरic queue) to setup
 *
 *  Returns 0 on success, negative on failure
 **/
पूर्णांक igb_setup_rx_resources(काष्ठा igb_ring *rx_ring)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(rx_ring->netdev);
	काष्ठा device *dev = rx_ring->dev;
	पूर्णांक size;

	size = माप(काष्ठा igb_rx_buffer) * rx_ring->count;

	rx_ring->rx_buffer_info = vदो_स्मृति(size);
	अगर (!rx_ring->rx_buffer_info)
		जाओ err;

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * माप(जोड़ e1000_adv_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	rx_ring->desc = dma_alloc_coherent(dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);
	अगर (!rx_ring->desc)
		जाओ err;

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	rx_ring->xdp_prog = adapter->xdp_prog;

	/* XDP RX-queue info */
	अगर (xdp_rxq_info_reg(&rx_ring->xdp_rxq, rx_ring->netdev,
			     rx_ring->queue_index, 0) < 0)
		जाओ err;

	वापस 0;

err:
	vमुक्त(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = शून्य;
	dev_err(dev, "Unable to allocate memory for the Rx descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 *  igb_setup_all_rx_resources - wrapper to allocate Rx resources
 *				 (Descriptors) क्रम all queues
 *  @adapter: board निजी काष्ठाure
 *
 *  Return 0 on success, negative on failure
 **/
अटल पूर्णांक igb_setup_all_rx_resources(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		err = igb_setup_rx_resources(adapter->rx_ring[i]);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Allocation for Rx Queue %u failed\n", i);
			क्रम (i--; i >= 0; i--)
				igb_मुक्त_rx_resources(adapter->rx_ring[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 *  igb_setup_mrqc - configure the multiple receive queue control रेजिस्टरs
 *  @adapter: Board निजी काष्ठाure
 **/
अटल व्योम igb_setup_mrqc(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 mrqc, rxcsum;
	u32 j, num_rx_queues;
	u32 rss_key[10];

	netdev_rss_key_fill(rss_key, माप(rss_key));
	क्रम (j = 0; j < 10; j++)
		wr32(E1000_RSSRK(j), rss_key[j]);

	num_rx_queues = adapter->rss_queues;

	चयन (hw->mac.type) अणु
	हाल e1000_82576:
		/* 82576 supports 2 RSS queues क्रम SR-IOV */
		अगर (adapter->vfs_allocated_count)
			num_rx_queues = 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (adapter->rss_indir_tbl_init != num_rx_queues) अणु
		क्रम (j = 0; j < IGB_RETA_SIZE; j++)
			adapter->rss_indir_tbl[j] =
			(j * num_rx_queues) / IGB_RETA_SIZE;
		adapter->rss_indir_tbl_init = num_rx_queues;
	पूर्ण
	igb_ग_लिखो_rss_indir_tbl(adapter);

	/* Disable raw packet checksumming so that RSS hash is placed in
	 * descriptor on ग_लिखोback.  No need to enable TCP/UDP/IP checksum
	 * offloads as they are enabled by शेष
	 */
	rxcsum = rd32(E1000_RXCSUM);
	rxcsum |= E1000_RXCSUM_PCSD;

	अगर (adapter->hw.mac.type >= e1000_82576)
		/* Enable Receive Checksum Offload क्रम SCTP */
		rxcsum |= E1000_RXCSUM_CRCOFL;

	/* Don't need to set TUOFL or IPOFL, they शेष to 1 */
	wr32(E1000_RXCSUM, rxcsum);

	/* Generate RSS hash based on packet types, TCP/UDP
	 * port numbers and/or IPv4/v6 src and dst addresses
	 */
	mrqc = E1000_MRQC_RSS_FIELD_IPV4 |
	       E1000_MRQC_RSS_FIELD_IPV4_TCP |
	       E1000_MRQC_RSS_FIELD_IPV6 |
	       E1000_MRQC_RSS_FIELD_IPV6_TCP |
	       E1000_MRQC_RSS_FIELD_IPV6_TCP_EX;

	अगर (adapter->flags & IGB_FLAG_RSS_FIELD_IPV4_UDP)
		mrqc |= E1000_MRQC_RSS_FIELD_IPV4_UDP;
	अगर (adapter->flags & IGB_FLAG_RSS_FIELD_IPV6_UDP)
		mrqc |= E1000_MRQC_RSS_FIELD_IPV6_UDP;

	/* If VMDq is enabled then we set the appropriate mode क्रम that, अन्यथा
	 * we शेष to RSS so that an RSS hash is calculated per packet even
	 * अगर we are only using one queue
	 */
	अगर (adapter->vfs_allocated_count) अणु
		अगर (hw->mac.type > e1000_82575) अणु
			/* Set the शेष pool क्रम the PF's first queue */
			u32 vtctl = rd32(E1000_VT_CTL);

			vtctl &= ~(E1000_VT_CTL_DEFAULT_POOL_MASK |
				   E1000_VT_CTL_DISABLE_DEF_POOL);
			vtctl |= adapter->vfs_allocated_count <<
				E1000_VT_CTL_DEFAULT_POOL_SHIFT;
			wr32(E1000_VT_CTL, vtctl);
		पूर्ण
		अगर (adapter->rss_queues > 1)
			mrqc |= E1000_MRQC_ENABLE_VMDQ_RSS_MQ;
		अन्यथा
			mrqc |= E1000_MRQC_ENABLE_VMDQ;
	पूर्ण अन्यथा अणु
		mrqc |= E1000_MRQC_ENABLE_RSS_MQ;
	पूर्ण
	igb_vmm_control(adapter);

	wr32(E1000_MRQC, mrqc);
पूर्ण

/**
 *  igb_setup_rctl - configure the receive control रेजिस्टरs
 *  @adapter: Board निजी काष्ठाure
 **/
व्योम igb_setup_rctl(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;

	rctl = rd32(E1000_RCTL);

	rctl &= ~(3 << E1000_RCTL_MO_SHIFT);
	rctl &= ~(E1000_RCTL_LBM_TCVR | E1000_RCTL_LBM_MAC);

	rctl |= E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_RDMTS_HALF |
		(hw->mac.mc_filter_type << E1000_RCTL_MO_SHIFT);

	/* enable stripping of CRC. It's unlikely this will अवरोध BMC
	 * redirection as it did with e1000. Newer features require
	 * that the HW strips the CRC.
	 */
	rctl |= E1000_RCTL_SECRC;

	/* disable store bad packets and clear size bits. */
	rctl &= ~(E1000_RCTL_SBP | E1000_RCTL_SZ_256);

	/* enable LPE to allow क्रम reception of jumbo frames */
	rctl |= E1000_RCTL_LPE;

	/* disable queue 0 to prevent tail ग_लिखो w/o re-config */
	wr32(E1000_RXDCTL(0), 0);

	/* Attention!!!  For SR-IOV PF driver operations you must enable
	 * queue drop क्रम all VF and PF queues to prevent head of line blocking
	 * अगर an un-trusted VF करोes not provide descriptors to hardware.
	 */
	अगर (adapter->vfs_allocated_count) अणु
		/* set all queue drop enable bits */
		wr32(E1000_QDE, ALL_QUEUES);
	पूर्ण

	/* This is useful क्रम snअगरfing bad packets. */
	अगर (adapter->netdev->features & NETIF_F_RXALL) अणु
		/* UPE and MPE will be handled by normal PROMISC logic
		 * in e1000e_set_rx_mode
		 */
		rctl |= (E1000_RCTL_SBP | /* Receive bad packets */
			 E1000_RCTL_BAM | /* RX All Bcast Pkts */
			 E1000_RCTL_PMCF); /* RX All MAC Ctrl Pkts */

		rctl &= ~(E1000_RCTL_DPF | /* Allow filtered छोड़ो */
			  E1000_RCTL_CFIEN); /* Dis VLAN CFIEN Filter */
		/* Do not mess with E1000_CTRL_VME, it affects transmit as well,
		 * and that अवरोधs VLANs.
		 */
	पूर्ण

	wr32(E1000_RCTL, rctl);
पूर्ण

अटल अंतरभूत पूर्णांक igb_set_vf_rlpml(काष्ठा igb_adapter *adapter, पूर्णांक size,
				   पूर्णांक vfn)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 vmolr;

	अगर (size > MAX_JUMBO_FRAME_SIZE)
		size = MAX_JUMBO_FRAME_SIZE;

	vmolr = rd32(E1000_VMOLR(vfn));
	vmolr &= ~E1000_VMOLR_RLPML_MASK;
	vmolr |= size | E1000_VMOLR_LPE;
	wr32(E1000_VMOLR(vfn), vmolr);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम igb_set_vf_vlan_strip(काष्ठा igb_adapter *adapter,
					 पूर्णांक vfn, bool enable)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 val, reg;

	अगर (hw->mac.type < e1000_82576)
		वापस;

	अगर (hw->mac.type == e1000_i350)
		reg = E1000_DVMOLR(vfn);
	अन्यथा
		reg = E1000_VMOLR(vfn);

	val = rd32(reg);
	अगर (enable)
		val |= E1000_VMOLR_STRVLAN;
	अन्यथा
		val &= ~(E1000_VMOLR_STRVLAN);
	wr32(reg, val);
पूर्ण

अटल अंतरभूत व्योम igb_set_vmolr(काष्ठा igb_adapter *adapter,
				 पूर्णांक vfn, bool aupe)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 vmolr;

	/* This रेजिस्टर exists only on 82576 and newer so अगर we are older then
	 * we should निकास and करो nothing
	 */
	अगर (hw->mac.type < e1000_82576)
		वापस;

	vmolr = rd32(E1000_VMOLR(vfn));
	अगर (aupe)
		vmolr |= E1000_VMOLR_AUPE; /* Accept untagged packets */
	अन्यथा
		vmolr &= ~(E1000_VMOLR_AUPE); /* Tagged packets ONLY */

	/* clear all bits that might not be set */
	vmolr &= ~(E1000_VMOLR_BAM | E1000_VMOLR_RSSE);

	अगर (adapter->rss_queues > 1 && vfn == adapter->vfs_allocated_count)
		vmolr |= E1000_VMOLR_RSSE; /* enable RSS */
	/* क्रम VMDq only allow the VFs and pool 0 to accept broadcast and
	 * multicast packets
	 */
	अगर (vfn <= adapter->vfs_allocated_count)
		vmolr |= E1000_VMOLR_BAM; /* Accept broadcast */

	wr32(E1000_VMOLR(vfn), vmolr);
पूर्ण

/**
 *  igb_setup_srrctl - configure the split and replication receive control
 *                     रेजिस्टरs
 *  @adapter: Board निजी काष्ठाure
 *  @ring: receive ring to be configured
 **/
व्योम igb_setup_srrctl(काष्ठा igb_adapter *adapter, काष्ठा igb_ring *ring)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक reg_idx = ring->reg_idx;
	u32 srrctl = 0;

	srrctl = IGB_RX_HDR_LEN << E1000_SRRCTL_BSIZEHDRSIZE_SHIFT;
	अगर (ring_uses_large_buffer(ring))
		srrctl |= IGB_RXBUFFER_3072 >> E1000_SRRCTL_BSIZEPKT_SHIFT;
	अन्यथा
		srrctl |= IGB_RXBUFFER_2048 >> E1000_SRRCTL_BSIZEPKT_SHIFT;
	srrctl |= E1000_SRRCTL_DESCTYPE_ADV_ONEBUF;
	अगर (hw->mac.type >= e1000_82580)
		srrctl |= E1000_SRRCTL_TIMESTAMP;
	/* Only set Drop Enable अगर VFs allocated, or we are supporting multiple
	 * queues and rx flow control is disabled
	 */
	अगर (adapter->vfs_allocated_count ||
	    (!(hw->fc.current_mode & e1000_fc_rx_छोड़ो) &&
	     adapter->num_rx_queues > 1))
		srrctl |= E1000_SRRCTL_DROP_EN;

	wr32(E1000_SRRCTL(reg_idx), srrctl);
पूर्ण

/**
 *  igb_configure_rx_ring - Configure a receive ring after Reset
 *  @adapter: board निजी काष्ठाure
 *  @ring: receive ring to be configured
 *
 *  Configure the Rx unit of the MAC after a reset.
 **/
व्योम igb_configure_rx_ring(काष्ठा igb_adapter *adapter,
			   काष्ठा igb_ring *ring)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	जोड़ e1000_adv_rx_desc *rx_desc;
	u64 rdba = ring->dma;
	पूर्णांक reg_idx = ring->reg_idx;
	u32 rxdctl = 0;

	xdp_rxq_info_unreg_mem_model(&ring->xdp_rxq);
	WARN_ON(xdp_rxq_info_reg_mem_model(&ring->xdp_rxq,
					   MEM_TYPE_PAGE_SHARED, शून्य));

	/* disable the queue */
	wr32(E1000_RXDCTL(reg_idx), 0);

	/* Set DMA base address रेजिस्टरs */
	wr32(E1000_RDBAL(reg_idx),
	     rdba & 0x00000000ffffffffULL);
	wr32(E1000_RDBAH(reg_idx), rdba >> 32);
	wr32(E1000_RDLEN(reg_idx),
	     ring->count * माप(जोड़ e1000_adv_rx_desc));

	/* initialize head and tail */
	ring->tail = adapter->io_addr + E1000_RDT(reg_idx);
	wr32(E1000_RDH(reg_idx), 0);
	ग_लिखोl(0, ring->tail);

	/* set descriptor configuration */
	igb_setup_srrctl(adapter, ring);

	/* set filtering क्रम VMDQ pools */
	igb_set_vmolr(adapter, reg_idx & 0x7, true);

	rxdctl |= IGB_RX_PTHRESH;
	rxdctl |= IGB_RX_HTHRESH << 8;
	rxdctl |= IGB_RX_WTHRESH << 16;

	/* initialize rx_buffer_info */
	स_रखो(ring->rx_buffer_info, 0,
	       माप(काष्ठा igb_rx_buffer) * ring->count);

	/* initialize Rx descriptor 0 */
	rx_desc = IGB_RX_DESC(ring, 0);
	rx_desc->wb.upper.length = 0;

	/* enable receive descriptor fetching */
	rxdctl |= E1000_RXDCTL_QUEUE_ENABLE;
	wr32(E1000_RXDCTL(reg_idx), rxdctl);
पूर्ण

अटल व्योम igb_set_rx_buffer_len(काष्ठा igb_adapter *adapter,
				  काष्ठा igb_ring *rx_ring)
अणु
	/* set build_skb and buffer size flags */
	clear_ring_build_skb_enabled(rx_ring);
	clear_ring_uses_large_buffer(rx_ring);

	अगर (adapter->flags & IGB_FLAG_RX_LEGACY)
		वापस;

	set_ring_build_skb_enabled(rx_ring);

#अगर (PAGE_SIZE < 8192)
	अगर (adapter->max_frame_size <= IGB_MAX_FRAME_BUILD_SKB)
		वापस;

	set_ring_uses_large_buffer(rx_ring);
#पूर्ण_अगर
पूर्ण

/**
 *  igb_configure_rx - Configure receive Unit after Reset
 *  @adapter: board निजी काष्ठाure
 *
 *  Configure the Rx unit of the MAC after a reset.
 **/
अटल व्योम igb_configure_rx(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक i;

	/* set the correct pool क्रम the PF शेष MAC address in entry 0 */
	igb_set_शेष_mac_filter(adapter);

	/* Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा igb_ring *rx_ring = adapter->rx_ring[i];

		igb_set_rx_buffer_len(adapter, rx_ring);
		igb_configure_rx_ring(adapter, rx_ring);
	पूर्ण
पूर्ण

/**
 *  igb_मुक्त_tx_resources - Free Tx Resources per Queue
 *  @tx_ring: Tx descriptor ring क्रम a specअगरic queue
 *
 *  Free all transmit software resources
 **/
व्योम igb_मुक्त_tx_resources(काष्ठा igb_ring *tx_ring)
अणु
	igb_clean_tx_ring(tx_ring);

	vमुक्त(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = शून्य;

	/* अगर not set, then करोn't मुक्त */
	अगर (!tx_ring->desc)
		वापस;

	dma_मुक्त_coherent(tx_ring->dev, tx_ring->size,
			  tx_ring->desc, tx_ring->dma);

	tx_ring->desc = शून्य;
पूर्ण

/**
 *  igb_मुक्त_all_tx_resources - Free Tx Resources क्रम All Queues
 *  @adapter: board निजी काष्ठाure
 *
 *  Free all transmit software resources
 **/
अटल व्योम igb_मुक्त_all_tx_resources(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		अगर (adapter->tx_ring[i])
			igb_मुक्त_tx_resources(adapter->tx_ring[i]);
पूर्ण

/**
 *  igb_clean_tx_ring - Free Tx Buffers
 *  @tx_ring: ring to be cleaned
 **/
अटल व्योम igb_clean_tx_ring(काष्ठा igb_ring *tx_ring)
अणु
	u16 i = tx_ring->next_to_clean;
	काष्ठा igb_tx_buffer *tx_buffer = &tx_ring->tx_buffer_info[i];

	जबतक (i != tx_ring->next_to_use) अणु
		जोड़ e1000_adv_tx_desc *eop_desc, *tx_desc;

		/* Free all the Tx ring sk_buffs */
		dev_kमुक्त_skb_any(tx_buffer->skb);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* check क्रम eop_desc to determine the end of the packet */
		eop_desc = tx_buffer->next_to_watch;
		tx_desc = IGB_TX_DESC(tx_ring, i);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buffer++;
			tx_desc++;
			i++;
			अगर (unlikely(i == tx_ring->count)) अणु
				i = 0;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IGB_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buffer, len))
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buffer++;
		i++;
		अगर (unlikely(i == tx_ring->count)) अणु
			i = 0;
			tx_buffer = tx_ring->tx_buffer_info;
		पूर्ण
	पूर्ण

	/* reset BQL क्रम queue */
	netdev_tx_reset_queue(txring_txq(tx_ring));

	/* reset next_to_use and next_to_clean */
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
पूर्ण

/**
 *  igb_clean_all_tx_rings - Free Tx Buffers क्रम all queues
 *  @adapter: board निजी काष्ठाure
 **/
अटल व्योम igb_clean_all_tx_rings(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		अगर (adapter->tx_ring[i])
			igb_clean_tx_ring(adapter->tx_ring[i]);
पूर्ण

/**
 *  igb_मुक्त_rx_resources - Free Rx Resources
 *  @rx_ring: ring to clean the resources from
 *
 *  Free all receive software resources
 **/
व्योम igb_मुक्त_rx_resources(काष्ठा igb_ring *rx_ring)
अणु
	igb_clean_rx_ring(rx_ring);

	rx_ring->xdp_prog = शून्य;
	xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	vमुक्त(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = शून्य;

	/* अगर not set, then करोn't मुक्त */
	अगर (!rx_ring->desc)
		वापस;

	dma_मुक्त_coherent(rx_ring->dev, rx_ring->size,
			  rx_ring->desc, rx_ring->dma);

	rx_ring->desc = शून्य;
पूर्ण

/**
 *  igb_मुक्त_all_rx_resources - Free Rx Resources क्रम All Queues
 *  @adapter: board निजी काष्ठाure
 *
 *  Free all receive software resources
 **/
अटल व्योम igb_मुक्त_all_rx_resources(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		अगर (adapter->rx_ring[i])
			igb_मुक्त_rx_resources(adapter->rx_ring[i]);
पूर्ण

/**
 *  igb_clean_rx_ring - Free Rx Buffers per Queue
 *  @rx_ring: ring to मुक्त buffers from
 **/
अटल व्योम igb_clean_rx_ring(काष्ठा igb_ring *rx_ring)
अणु
	u16 i = rx_ring->next_to_clean;

	dev_kमुक्त_skb(rx_ring->skb);
	rx_ring->skb = शून्य;

	/* Free all the Rx ring sk_buffs */
	जबतक (i != rx_ring->next_to_alloc) अणु
		काष्ठा igb_rx_buffer *buffer_info = &rx_ring->rx_buffer_info[i];

		/* Invalidate cache lines that may have been written to by
		 * device so that we aव्योम corrupting memory.
		 */
		dma_sync_single_range_क्रम_cpu(rx_ring->dev,
					      buffer_info->dma,
					      buffer_info->page_offset,
					      igb_rx_bufsz(rx_ring),
					      DMA_FROM_DEVICE);

		/* मुक्त resources associated with mapping */
		dma_unmap_page_attrs(rx_ring->dev,
				     buffer_info->dma,
				     igb_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE,
				     IGB_RX_DMA_ATTR);
		__page_frag_cache_drain(buffer_info->page,
					buffer_info->pagecnt_bias);

		i++;
		अगर (i == rx_ring->count)
			i = 0;
	पूर्ण

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
पूर्ण

/**
 *  igb_clean_all_rx_rings - Free Rx Buffers क्रम all queues
 *  @adapter: board निजी काष्ठाure
 **/
अटल व्योम igb_clean_all_rx_rings(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		अगर (adapter->rx_ring[i])
			igb_clean_rx_ring(adapter->rx_ring[i]);
पूर्ण

/**
 *  igb_set_mac - Change the Ethernet Address of the NIC
 *  @netdev: network पूर्णांकerface device काष्ठाure
 *  @p: poपूर्णांकer to an address काष्ठाure
 *
 *  Returns 0 on success, negative on failure
 **/
अटल पूर्णांक igb_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(hw->mac.addr, addr->sa_data, netdev->addr_len);

	/* set the correct pool क्रम the new PF MAC address in entry 0 */
	igb_set_शेष_mac_filter(adapter);

	वापस 0;
पूर्ण

/**
 *  igb_ग_लिखो_mc_addr_list - ग_लिखो multicast addresses to MTA
 *  @netdev: network पूर्णांकerface device काष्ठाure
 *
 *  Writes multicast address list to the MTA hash table.
 *  Returns: -ENOMEM on failure
 *           0 on no addresses written
 *           X on writing X addresses to MTA
 **/
अटल पूर्णांक igb_ग_लिखो_mc_addr_list(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u8  *mta_list;
	पूर्णांक i;

	अगर (netdev_mc_empty(netdev)) अणु
		/* nothing to program, so clear mc list */
		igb_update_mc_addr_list(hw, शून्य, 0);
		igb_restore_vf_multicasts(adapter);
		वापस 0;
	पूर्ण

	mta_list = kसुस्मृति(netdev_mc_count(netdev), 6, GFP_ATOMIC);
	अगर (!mta_list)
		वापस -ENOMEM;

	/* The shared function expects a packed array of only addresses. */
	i = 0;
	netdev_क्रम_each_mc_addr(ha, netdev)
		स_नकल(mta_list + (i++ * ETH_ALEN), ha->addr, ETH_ALEN);

	igb_update_mc_addr_list(hw, mta_list, i);
	kमुक्त(mta_list);

	वापस netdev_mc_count(netdev);
पूर्ण

अटल पूर्णांक igb_vlan_promisc_enable(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 i, pf_id;

	चयन (hw->mac.type) अणु
	हाल e1000_i210:
	हाल e1000_i211:
	हाल e1000_i350:
		/* VLAN filtering needed क्रम VLAN prio filter */
		अगर (adapter->netdev->features & NETIF_F_NTUPLE)
			अवरोध;
		fallthrough;
	हाल e1000_82576:
	हाल e1000_82580:
	हाल e1000_i354:
		/* VLAN filtering needed क्रम pool filtering */
		अगर (adapter->vfs_allocated_count)
			अवरोध;
		fallthrough;
	शेष:
		वापस 1;
	पूर्ण

	/* We are alपढ़ोy in VLAN promisc, nothing to करो */
	अगर (adapter->flags & IGB_FLAG_VLAN_PROMISC)
		वापस 0;

	अगर (!adapter->vfs_allocated_count)
		जाओ set_vfta;

	/* Add PF to all active pools */
	pf_id = adapter->vfs_allocated_count + E1000_VLVF_POOLSEL_SHIFT;

	क्रम (i = E1000_VLVF_ARRAY_SIZE; --i;) अणु
		u32 vlvf = rd32(E1000_VLVF(i));

		vlvf |= BIT(pf_id);
		wr32(E1000_VLVF(i), vlvf);
	पूर्ण

set_vfta:
	/* Set all bits in the VLAN filter table array */
	क्रम (i = E1000_VLAN_FILTER_TBL_SIZE; i--;)
		hw->mac.ops.ग_लिखो_vfta(hw, i, ~0U);

	/* Set flag so we करोn't reकरो unnecessary work */
	adapter->flags |= IGB_FLAG_VLAN_PROMISC;

	वापस 0;
पूर्ण

#घोषणा VFTA_BLOCK_SIZE 8
अटल व्योम igb_scrub_vfta(काष्ठा igb_adapter *adapter, u32 vfta_offset)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 vfta[VFTA_BLOCK_SIZE] = अणु 0 पूर्ण;
	u32 vid_start = vfta_offset * 32;
	u32 vid_end = vid_start + (VFTA_BLOCK_SIZE * 32);
	u32 i, vid, word, bits, pf_id;

	/* guarantee that we करोn't scrub out management VLAN */
	vid = adapter->mng_vlan_id;
	अगर (vid >= vid_start && vid < vid_end)
		vfta[(vid - vid_start) / 32] |= BIT(vid % 32);

	अगर (!adapter->vfs_allocated_count)
		जाओ set_vfta;

	pf_id = adapter->vfs_allocated_count + E1000_VLVF_POOLSEL_SHIFT;

	क्रम (i = E1000_VLVF_ARRAY_SIZE; --i;) अणु
		u32 vlvf = rd32(E1000_VLVF(i));

		/* pull VLAN ID from VLVF */
		vid = vlvf & VLAN_VID_MASK;

		/* only concern ourselves with a certain range */
		अगर (vid < vid_start || vid >= vid_end)
			जारी;

		अगर (vlvf & E1000_VLVF_VLANID_ENABLE) अणु
			/* record VLAN ID in VFTA */
			vfta[(vid - vid_start) / 32] |= BIT(vid % 32);

			/* अगर PF is part of this then जारी */
			अगर (test_bit(vid, adapter->active_vlans))
				जारी;
		पूर्ण

		/* हटाओ PF from the pool */
		bits = ~BIT(pf_id);
		bits &= rd32(E1000_VLVF(i));
		wr32(E1000_VLVF(i), bits);
	पूर्ण

set_vfta:
	/* extract values from active_vlans and ग_लिखो back to VFTA */
	क्रम (i = VFTA_BLOCK_SIZE; i--;) अणु
		vid = (vfta_offset + i) * 32;
		word = vid / BITS_PER_LONG;
		bits = vid % BITS_PER_LONG;

		vfta[i] |= adapter->active_vlans[word] >> bits;

		hw->mac.ops.ग_लिखो_vfta(hw, vfta_offset + i, vfta[i]);
	पूर्ण
पूर्ण

अटल व्योम igb_vlan_promisc_disable(काष्ठा igb_adapter *adapter)
अणु
	u32 i;

	/* We are not in VLAN promisc, nothing to करो */
	अगर (!(adapter->flags & IGB_FLAG_VLAN_PROMISC))
		वापस;

	/* Set flag so we करोn't reकरो unnecessary work */
	adapter->flags &= ~IGB_FLAG_VLAN_PROMISC;

	क्रम (i = 0; i < E1000_VLAN_FILTER_TBL_SIZE; i += VFTA_BLOCK_SIZE)
		igb_scrub_vfta(adapter, i);
पूर्ण

/**
 *  igb_set_rx_mode - Secondary Unicast, Multicast and Promiscuous mode set
 *  @netdev: network पूर्णांकerface device काष्ठाure
 *
 *  The set_rx_mode entry poपूर्णांक is called whenever the unicast or multicast
 *  address lists or the network पूर्णांकerface flags are updated.  This routine is
 *  responsible क्रम configuring the hardware क्रम proper unicast, multicast,
 *  promiscuous mode, and all-multi behavior.
 **/
अटल व्योम igb_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	अचिन्हित पूर्णांक vfn = adapter->vfs_allocated_count;
	u32 rctl = 0, vmolr = 0, rlpml = MAX_JUMBO_FRAME_SIZE;
	पूर्णांक count;

	/* Check क्रम Promiscuous and All Multicast modes */
	अगर (netdev->flags & IFF_PROMISC) अणु
		rctl |= E1000_RCTL_UPE | E1000_RCTL_MPE;
		vmolr |= E1000_VMOLR_MPME;

		/* enable use of UTA filter to क्रमce packets to शेष pool */
		अगर (hw->mac.type == e1000_82576)
			vmolr |= E1000_VMOLR_ROPE;
	पूर्ण अन्यथा अणु
		अगर (netdev->flags & IFF_ALLMULTI) अणु
			rctl |= E1000_RCTL_MPE;
			vmolr |= E1000_VMOLR_MPME;
		पूर्ण अन्यथा अणु
			/* Write addresses to the MTA, अगर the attempt fails
			 * then we should just turn on promiscuous mode so
			 * that we can at least receive multicast traffic
			 */
			count = igb_ग_लिखो_mc_addr_list(netdev);
			अगर (count < 0) अणु
				rctl |= E1000_RCTL_MPE;
				vmolr |= E1000_VMOLR_MPME;
			पूर्ण अन्यथा अगर (count) अणु
				vmolr |= E1000_VMOLR_ROMPE;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Write addresses to available RAR रेजिस्टरs, अगर there is not
	 * sufficient space to store all the addresses then enable
	 * unicast promiscuous mode
	 */
	अगर (__dev_uc_sync(netdev, igb_uc_sync, igb_uc_unsync)) अणु
		rctl |= E1000_RCTL_UPE;
		vmolr |= E1000_VMOLR_ROPE;
	पूर्ण

	/* enable VLAN filtering by शेष */
	rctl |= E1000_RCTL_VFE;

	/* disable VLAN filtering क्रम modes that require it */
	अगर ((netdev->flags & IFF_PROMISC) ||
	    (netdev->features & NETIF_F_RXALL)) अणु
		/* अगर we fail to set all rules then just clear VFE */
		अगर (igb_vlan_promisc_enable(adapter))
			rctl &= ~E1000_RCTL_VFE;
	पूर्ण अन्यथा अणु
		igb_vlan_promisc_disable(adapter);
	पूर्ण

	/* update state of unicast, multicast, and VLAN filtering modes */
	rctl |= rd32(E1000_RCTL) & ~(E1000_RCTL_UPE | E1000_RCTL_MPE |
				     E1000_RCTL_VFE);
	wr32(E1000_RCTL, rctl);

#अगर (PAGE_SIZE < 8192)
	अगर (!adapter->vfs_allocated_count) अणु
		अगर (adapter->max_frame_size <= IGB_MAX_FRAME_BUILD_SKB)
			rlpml = IGB_MAX_FRAME_BUILD_SKB;
	पूर्ण
#पूर्ण_अगर
	wr32(E1000_RLPML, rlpml);

	/* In order to support SR-IOV and eventually VMDq it is necessary to set
	 * the VMOLR to enable the appropriate modes.  Without this workaround
	 * we will have issues with VLAN tag stripping not being करोne क्रम frames
	 * that are only arriving because we are the शेष pool
	 */
	अगर ((hw->mac.type < e1000_82576) || (hw->mac.type > e1000_i350))
		वापस;

	/* set UTA to appropriate mode */
	igb_set_uta(adapter, !!(vmolr & E1000_VMOLR_ROPE));

	vmolr |= rd32(E1000_VMOLR(vfn)) &
		 ~(E1000_VMOLR_ROPE | E1000_VMOLR_MPME | E1000_VMOLR_ROMPE);

	/* enable Rx jumbo frames, restrict as needed to support build_skb */
	vmolr &= ~E1000_VMOLR_RLPML_MASK;
#अगर (PAGE_SIZE < 8192)
	अगर (adapter->max_frame_size <= IGB_MAX_FRAME_BUILD_SKB)
		vmolr |= IGB_MAX_FRAME_BUILD_SKB;
	अन्यथा
#पूर्ण_अगर
		vmolr |= MAX_JUMBO_FRAME_SIZE;
	vmolr |= E1000_VMOLR_LPE;

	wr32(E1000_VMOLR(vfn), vmolr);

	igb_restore_vf_multicasts(adapter);
पूर्ण

अटल व्योम igb_check_wvbr(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 wvbr = 0;

	चयन (hw->mac.type) अणु
	हाल e1000_82576:
	हाल e1000_i350:
		wvbr = rd32(E1000_WVBR);
		अगर (!wvbr)
			वापस;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	adapter->wvbr |= wvbr;
पूर्ण

#घोषणा IGB_STAGGERED_QUEUE_OFFSET 8

अटल व्योम igb_spoof_check(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक j;

	अगर (!adapter->wvbr)
		वापस;

	क्रम (j = 0; j < adapter->vfs_allocated_count; j++) अणु
		अगर (adapter->wvbr & BIT(j) ||
		    adapter->wvbr & BIT(j + IGB_STAGGERED_QUEUE_OFFSET)) अणु
			dev_warn(&adapter->pdev->dev,
				"Spoof event(s) detected on VF %d\n", j);
			adapter->wvbr &=
				~(BIT(j) |
				  BIT(j + IGB_STAGGERED_QUEUE_OFFSET));
		पूर्ण
	पूर्ण
पूर्ण

/* Need to रुको a few seconds after link up to get diagnostic inक्रमmation from
 * the phy
 */
अटल व्योम igb_update_phy_info(काष्ठा समयr_list *t)
अणु
	काष्ठा igb_adapter *adapter = from_समयr(adapter, t, phy_info_समयr);
	igb_get_phy_info(&adapter->hw);
पूर्ण

/**
 *  igb_has_link - check shared code क्रम link and determine up/करोwn
 *  @adapter: poपूर्णांकer to driver निजी info
 **/
bool igb_has_link(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	bool link_active = false;

	/* get_link_status is set on LSC (link status) पूर्णांकerrupt or
	 * rx sequence error पूर्णांकerrupt.  get_link_status will stay
	 * false until the e1000_check_क्रम_link establishes link
	 * क्रम copper adapters ONLY
	 */
	चयन (hw->phy.media_type) अणु
	हाल e1000_media_type_copper:
		अगर (!hw->mac.get_link_status)
			वापस true;
		fallthrough;
	हाल e1000_media_type_पूर्णांकernal_serdes:
		hw->mac.ops.check_क्रम_link(hw);
		link_active = !hw->mac.get_link_status;
		अवरोध;
	शेष:
	हाल e1000_media_type_unknown:
		अवरोध;
	पूर्ण

	अगर (((hw->mac.type == e1000_i210) ||
	     (hw->mac.type == e1000_i211)) &&
	     (hw->phy.id == I210_I_PHY_ID)) अणु
		अगर (!netअगर_carrier_ok(adapter->netdev)) अणु
			adapter->flags &= ~IGB_FLAG_NEED_LINK_UPDATE;
		पूर्ण अन्यथा अगर (!(adapter->flags & IGB_FLAG_NEED_LINK_UPDATE)) अणु
			adapter->flags |= IGB_FLAG_NEED_LINK_UPDATE;
			adapter->link_check_समयout = jअगरfies;
		पूर्ण
	पूर्ण

	वापस link_active;
पूर्ण

अटल bool igb_thermal_sensor_event(काष्ठा e1000_hw *hw, u32 event)
अणु
	bool ret = false;
	u32 ctrl_ext, thstat;

	/* check क्रम thermal sensor event on i350 copper only */
	अगर (hw->mac.type == e1000_i350) अणु
		thstat = rd32(E1000_THSTAT);
		ctrl_ext = rd32(E1000_CTRL_EXT);

		अगर ((hw->phy.media_type == e1000_media_type_copper) &&
		    !(ctrl_ext & E1000_CTRL_EXT_LINK_MODE_SGMII))
			ret = !!(thstat & event);
	पूर्ण

	वापस ret;
पूर्ण

/**
 *  igb_check_lvmmc - check क्रम malक्रमmed packets received
 *  and indicated in LVMMC रेजिस्टर
 *  @adapter: poपूर्णांकer to adapter
 **/
अटल व्योम igb_check_lvmmc(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 lvmmc;

	lvmmc = rd32(E1000_LVMMC);
	अगर (lvmmc) अणु
		अगर (unlikely(net_ratelimit())) अणु
			netdev_warn(adapter->netdev,
				    "malformed Tx packet detected and dropped, LVMMC:0x%08x\n",
				    lvmmc);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *  igb_watchकरोg - Timer Call-back
 *  @t: poपूर्णांकer to समयr_list containing our निजी info poपूर्णांकer
 **/
अटल व्योम igb_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा igb_adapter *adapter = from_समयr(adapter, t, watchकरोg_समयr);
	/* Do the rest outside of पूर्णांकerrupt context */
	schedule_work(&adapter->watchकरोg_task);
पूर्ण

अटल व्योम igb_watchकरोg_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा igb_adapter *adapter = container_of(work,
						   काष्ठा igb_adapter,
						   watchकरोg_task);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_phy_info *phy = &hw->phy;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 link;
	पूर्णांक i;
	u32 connsw;
	u16 phy_data, retry_count = 20;

	link = igb_has_link(adapter);

	अगर (adapter->flags & IGB_FLAG_NEED_LINK_UPDATE) अणु
		अगर (समय_after(jअगरfies, (adapter->link_check_समयout + HZ)))
			adapter->flags &= ~IGB_FLAG_NEED_LINK_UPDATE;
		अन्यथा
			link = false;
	पूर्ण

	/* Force link करोwn अगर we have fiber to swap to */
	अगर (adapter->flags & IGB_FLAG_MAS_ENABLE) अणु
		अगर (hw->phy.media_type == e1000_media_type_copper) अणु
			connsw = rd32(E1000_CONNSW);
			अगर (!(connsw & E1000_CONNSW_AUTOSENSE_EN))
				link = 0;
		पूर्ण
	पूर्ण
	अगर (link) अणु
		/* Perक्रमm a reset अगर the media type changed. */
		अगर (hw->dev_spec._82575.media_changed) अणु
			hw->dev_spec._82575.media_changed = false;
			adapter->flags |= IGB_FLAG_MEDIA_RESET;
			igb_reset(adapter);
		पूर्ण
		/* Cancel scheduled suspend requests. */
		pm_runसमय_resume(netdev->dev.parent);

		अगर (!netअगर_carrier_ok(netdev)) अणु
			u32 ctrl;

			hw->mac.ops.get_speed_and_duplex(hw,
							 &adapter->link_speed,
							 &adapter->link_duplex);

			ctrl = rd32(E1000_CTRL);
			/* Links status message must follow this क्रमmat */
			netdev_info(netdev,
			       "igb: %s NIC Link is Up %d Mbps %s Duplex, Flow Control: %s\n",
			       netdev->name,
			       adapter->link_speed,
			       adapter->link_duplex == FULL_DUPLEX ?
			       "Full" : "Half",
			       (ctrl & E1000_CTRL_TFCE) &&
			       (ctrl & E1000_CTRL_RFCE) ? "RX/TX" :
			       (ctrl & E1000_CTRL_RFCE) ?  "RX" :
			       (ctrl & E1000_CTRL_TFCE) ?  "TX" : "None");

			/* disable EEE अगर enabled */
			अगर ((adapter->flags & IGB_FLAG_EEE) &&
				(adapter->link_duplex == HALF_DUPLEX)) अणु
				dev_info(&adapter->pdev->dev,
				"EEE Disabled: unsupported at half duplex. Re-enable using ethtool when at full duplex.\n");
				adapter->hw.dev_spec._82575.eee_disable = true;
				adapter->flags &= ~IGB_FLAG_EEE;
			पूर्ण

			/* check अगर SmartSpeed worked */
			igb_check_करोwnshअगरt(hw);
			अगर (phy->speed_करोwngraded)
				netdev_warn(netdev, "Link Speed was downgraded by SmartSpeed\n");

			/* check क्रम thermal sensor event */
			अगर (igb_thermal_sensor_event(hw,
			    E1000_THSTAT_LINK_THROTTLE))
				netdev_info(netdev, "The network adapter link speed was downshifted because it overheated\n");

			/* adjust समयout factor according to speed/duplex */
			adapter->tx_समयout_factor = 1;
			चयन (adapter->link_speed) अणु
			हाल SPEED_10:
				adapter->tx_समयout_factor = 14;
				अवरोध;
			हाल SPEED_100:
				/* maybe add some समयout factor ? */
				अवरोध;
			पूर्ण

			अगर (adapter->link_speed != SPEED_1000)
				जाओ no_रुको;

			/* रुको क्रम Remote receiver status OK */
retry_पढ़ो_status:
			अगर (!igb_पढ़ो_phy_reg(hw, PHY_1000T_STATUS,
					      &phy_data)) अणु
				अगर (!(phy_data & SR_1000T_REMOTE_RX_STATUS) &&
				    retry_count) अणु
					msleep(100);
					retry_count--;
					जाओ retry_पढ़ो_status;
				पूर्ण अन्यथा अगर (!retry_count) अणु
					dev_err(&adapter->pdev->dev, "exceed max 2 second\n");
				पूर्ण
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev, "read 1000Base-T Status Reg\n");
			पूर्ण
no_रुको:
			netअगर_carrier_on(netdev);

			igb_ping_all_vfs(adapter);
			igb_check_vf_rate_limit(adapter);

			/* link state has changed, schedule phy info update */
			अगर (!test_bit(__IGB_DOWN, &adapter->state))
				mod_समयr(&adapter->phy_info_समयr,
					  round_jअगरfies(jअगरfies + 2 * HZ));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			adapter->link_speed = 0;
			adapter->link_duplex = 0;

			/* check क्रम thermal sensor event */
			अगर (igb_thermal_sensor_event(hw,
			    E1000_THSTAT_PWR_DOWN)) अणु
				netdev_err(netdev, "The network adapter was stopped because it overheated\n");
			पूर्ण

			/* Links status message must follow this क्रमmat */
			netdev_info(netdev, "igb: %s NIC Link is Down\n",
			       netdev->name);
			netअगर_carrier_off(netdev);

			igb_ping_all_vfs(adapter);

			/* link state has changed, schedule phy info update */
			अगर (!test_bit(__IGB_DOWN, &adapter->state))
				mod_समयr(&adapter->phy_info_समयr,
					  round_jअगरfies(jअगरfies + 2 * HZ));

			/* link is करोwn, समय to check क्रम alternate media */
			अगर (adapter->flags & IGB_FLAG_MAS_ENABLE) अणु
				igb_check_swap_media(adapter);
				अगर (adapter->flags & IGB_FLAG_MEDIA_RESET) अणु
					schedule_work(&adapter->reset_task);
					/* वापस immediately */
					वापस;
				पूर्ण
			पूर्ण
			pm_schedule_suspend(netdev->dev.parent,
					    MSEC_PER_SEC * 5);

		/* also check क्रम alternate media here */
		पूर्ण अन्यथा अगर (!netअगर_carrier_ok(netdev) &&
			   (adapter->flags & IGB_FLAG_MAS_ENABLE)) अणु
			igb_check_swap_media(adapter);
			अगर (adapter->flags & IGB_FLAG_MEDIA_RESET) अणु
				schedule_work(&adapter->reset_task);
				/* वापस immediately */
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock(&adapter->stats64_lock);
	igb_update_stats(adapter);
	spin_unlock(&adapter->stats64_lock);

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा igb_ring *tx_ring = adapter->tx_ring[i];
		अगर (!netअगर_carrier_ok(netdev)) अणु
			/* We've lost link, so the controller stops DMA,
			 * but we've got queued Tx work that's never going
			 * to get करोne, so reset controller to flush Tx.
			 * (Do the reset outside of पूर्णांकerrupt context).
			 */
			अगर (igb_desc_unused(tx_ring) + 1 < tx_ring->count) अणु
				adapter->tx_समयout_count++;
				schedule_work(&adapter->reset_task);
				/* वापस immediately since reset is imminent */
				वापस;
			पूर्ण
		पूर्ण

		/* Force detection of hung controller every watchकरोg period */
		set_bit(IGB_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags);
	पूर्ण

	/* Cause software पूर्णांकerrupt to ensure Rx ring is cleaned */
	अगर (adapter->flags & IGB_FLAG_HAS_MSIX) अणु
		u32 eics = 0;

		क्रम (i = 0; i < adapter->num_q_vectors; i++)
			eics |= adapter->q_vector[i]->eims_value;
		wr32(E1000_EICS, eics);
	पूर्ण अन्यथा अणु
		wr32(E1000_ICS, E1000_ICS_RXDMT0);
	पूर्ण

	igb_spoof_check(adapter);
	igb_ptp_rx_hang(adapter);
	igb_ptp_tx_hang(adapter);

	/* Check LVMMC रेजिस्टर on i350/i354 only */
	अगर ((adapter->hw.mac.type == e1000_i350) ||
	    (adapter->hw.mac.type == e1000_i354))
		igb_check_lvmmc(adapter);

	/* Reset the समयr */
	अगर (!test_bit(__IGB_DOWN, &adapter->state)) अणु
		अगर (adapter->flags & IGB_FLAG_NEED_LINK_UPDATE)
			mod_समयr(&adapter->watchकरोg_समयr,
				  round_jअगरfies(jअगरfies +  HZ));
		अन्यथा
			mod_समयr(&adapter->watchकरोg_समयr,
				  round_jअगरfies(jअगरfies + 2 * HZ));
	पूर्ण
पूर्ण

क्रमागत latency_range अणु
	lowest_latency = 0,
	low_latency = 1,
	bulk_latency = 2,
	latency_invalid = 255
पूर्ण;

/**
 *  igb_update_ring_itr - update the dynamic ITR value based on packet size
 *  @q_vector: poपूर्णांकer to q_vector
 *
 *  Stores a new ITR value based on strictly on packet size.  This
 *  algorithm is less sophisticated than that used in igb_update_itr,
 *  due to the dअगरficulty of synchronizing statistics across multiple
 *  receive rings.  The भागisors and thresholds used by this function
 *  were determined based on theoretical maximum wire speed and testing
 *  data, in order to minimize response समय जबतक increasing bulk
 *  throughput.
 *  This functionality is controlled by ethtool's coalescing settings.
 *  NOTE:  This function is called only when operating in a multiqueue
 *         receive environment.
 **/
अटल व्योम igb_update_ring_itr(काष्ठा igb_q_vector *q_vector)
अणु
	पूर्णांक new_val = q_vector->itr_val;
	पूर्णांक avg_wire_size = 0;
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	अचिन्हित पूर्णांक packets;

	/* For non-gigabit speeds, just fix the पूर्णांकerrupt rate at 4000
	 * पूर्णांकs/sec - ITR समयr value of 120 ticks.
	 */
	अगर (adapter->link_speed != SPEED_1000) अणु
		new_val = IGB_4K_ITR;
		जाओ set_itr_val;
	पूर्ण

	packets = q_vector->rx.total_packets;
	अगर (packets)
		avg_wire_size = q_vector->rx.total_bytes / packets;

	packets = q_vector->tx.total_packets;
	अगर (packets)
		avg_wire_size = max_t(u32, avg_wire_size,
				      q_vector->tx.total_bytes / packets);

	/* अगर avg_wire_size isn't set no work was करोne */
	अगर (!avg_wire_size)
		जाओ clear_counts;

	/* Add 24 bytes to size to account क्रम CRC, preamble, and gap */
	avg_wire_size += 24;

	/* Don't starve jumbo frames */
	avg_wire_size = min(avg_wire_size, 3000);

	/* Give a little boost to mid-size frames */
	अगर ((avg_wire_size > 300) && (avg_wire_size < 1200))
		new_val = avg_wire_size / 3;
	अन्यथा
		new_val = avg_wire_size / 2;

	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	अगर (new_val < IGB_20K_ITR &&
	    ((q_vector->rx.ring && adapter->rx_itr_setting == 3) ||
	     (!q_vector->rx.ring && adapter->tx_itr_setting == 3)))
		new_val = IGB_20K_ITR;

set_itr_val:
	अगर (new_val != q_vector->itr_val) अणु
		q_vector->itr_val = new_val;
		q_vector->set_itr = 1;
	पूर्ण
clear_counts:
	q_vector->rx.total_bytes = 0;
	q_vector->rx.total_packets = 0;
	q_vector->tx.total_bytes = 0;
	q_vector->tx.total_packets = 0;
पूर्ण

/**
 *  igb_update_itr - update the dynamic ITR value based on statistics
 *  @q_vector: poपूर्णांकer to q_vector
 *  @ring_container: ring info to update the itr क्रम
 *
 *  Stores a new ITR value based on packets and byte
 *  counts during the last पूर्णांकerrupt.  The advantage of per पूर्णांकerrupt
 *  computation is faster updates and more accurate ITR क्रम the current
 *  traffic pattern.  Constants in this function were computed
 *  based on theoretical maximum wire speed and thresholds were set based
 *  on testing data as well as attempting to minimize response समय
 *  जबतक increasing bulk throughput.
 *  This functionality is controlled by ethtool's coalescing settings.
 *  NOTE:  These calculations are only valid when operating in a single-
 *         queue environment.
 **/
अटल व्योम igb_update_itr(काष्ठा igb_q_vector *q_vector,
			   काष्ठा igb_ring_container *ring_container)
अणु
	अचिन्हित पूर्णांक packets = ring_container->total_packets;
	अचिन्हित पूर्णांक bytes = ring_container->total_bytes;
	u8 itrval = ring_container->itr;

	/* no packets, निकास with status unchanged */
	अगर (packets == 0)
		वापस;

	चयन (itrval) अणु
	हाल lowest_latency:
		/* handle TSO and jumbo frames */
		अगर (bytes/packets > 8000)
			itrval = bulk_latency;
		अन्यथा अगर ((packets < 5) && (bytes > 512))
			itrval = low_latency;
		अवरोध;
	हाल low_latency:  /* 50 usec aka 20000 पूर्णांकs/s */
		अगर (bytes > 10000) अणु
			/* this अगर handles the TSO accounting */
			अगर (bytes/packets > 8000)
				itrval = bulk_latency;
			अन्यथा अगर ((packets < 10) || ((bytes/packets) > 1200))
				itrval = bulk_latency;
			अन्यथा अगर ((packets > 35))
				itrval = lowest_latency;
		पूर्ण अन्यथा अगर (bytes/packets > 2000) अणु
			itrval = bulk_latency;
		पूर्ण अन्यथा अगर (packets <= 2 && bytes < 512) अणु
			itrval = lowest_latency;
		पूर्ण
		अवरोध;
	हाल bulk_latency: /* 250 usec aka 4000 पूर्णांकs/s */
		अगर (bytes > 25000) अणु
			अगर (packets > 35)
				itrval = low_latency;
		पूर्ण अन्यथा अगर (bytes < 1500) अणु
			itrval = low_latency;
		पूर्ण
		अवरोध;
	पूर्ण

	/* clear work counters since we have the values we need */
	ring_container->total_bytes = 0;
	ring_container->total_packets = 0;

	/* ग_लिखो updated itr to ring container */
	ring_container->itr = itrval;
पूर्ण

अटल व्योम igb_set_itr(काष्ठा igb_q_vector *q_vector)
अणु
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	u32 new_itr = q_vector->itr_val;
	u8 current_itr = 0;

	/* क्रम non-gigabit speeds, just fix the पूर्णांकerrupt rate at 4000 */
	अगर (adapter->link_speed != SPEED_1000) अणु
		current_itr = 0;
		new_itr = IGB_4K_ITR;
		जाओ set_itr_now;
	पूर्ण

	igb_update_itr(q_vector, &q_vector->tx);
	igb_update_itr(q_vector, &q_vector->rx);

	current_itr = max(q_vector->rx.itr, q_vector->tx.itr);

	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	अगर (current_itr == lowest_latency &&
	    ((q_vector->rx.ring && adapter->rx_itr_setting == 3) ||
	     (!q_vector->rx.ring && adapter->tx_itr_setting == 3)))
		current_itr = low_latency;

	चयन (current_itr) अणु
	/* counts and packets in update_itr are dependent on these numbers */
	हाल lowest_latency:
		new_itr = IGB_70K_ITR; /* 70,000 पूर्णांकs/sec */
		अवरोध;
	हाल low_latency:
		new_itr = IGB_20K_ITR; /* 20,000 पूर्णांकs/sec */
		अवरोध;
	हाल bulk_latency:
		new_itr = IGB_4K_ITR;  /* 4,000 पूर्णांकs/sec */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

set_itr_now:
	अगर (new_itr != q_vector->itr_val) अणु
		/* this attempts to bias the पूर्णांकerrupt rate towards Bulk
		 * by adding पूर्णांकermediate steps when पूर्णांकerrupt rate is
		 * increasing
		 */
		new_itr = new_itr > q_vector->itr_val ?
			  max((new_itr * q_vector->itr_val) /
			  (new_itr + (q_vector->itr_val >> 2)),
			  new_itr) : new_itr;
		/* Don't write the value here; it resets the adapter's
		 * पूर्णांकernal समयr, and causes us to delay far दीर्घer than
		 * we should between पूर्णांकerrupts.  Instead, we ग_लिखो the ITR
		 * value at the beginning of the next पूर्णांकerrupt so the timing
		 * ends up being correct.
		 */
		q_vector->itr_val = new_itr;
		q_vector->set_itr = 1;
	पूर्ण
पूर्ण

अटल व्योम igb_tx_ctxtdesc(काष्ठा igb_ring *tx_ring,
			    काष्ठा igb_tx_buffer *first,
			    u32 vlan_macip_lens, u32 type_tucmd,
			    u32 mss_l4len_idx)
अणु
	काष्ठा e1000_adv_tx_context_desc *context_desc;
	u16 i = tx_ring->next_to_use;
	काष्ठा बारpec64 ts;

	context_desc = IGB_TX_CTXTDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* set bits to identअगरy this as an advanced context descriptor */
	type_tucmd |= E1000_TXD_CMD_DEXT | E1000_ADVTXD_DTYP_CTXT;

	/* For 82575, context index must be unique per ring. */
	अगर (test_bit(IGB_RING_FLAG_TX_CTX_IDX, &tx_ring->flags))
		mss_l4len_idx |= tx_ring->reg_idx << 4;

	context_desc->vlan_macip_lens	= cpu_to_le32(vlan_macip_lens);
	context_desc->type_tucmd_mlhl	= cpu_to_le32(type_tucmd);
	context_desc->mss_l4len_idx	= cpu_to_le32(mss_l4len_idx);

	/* We assume there is always a valid tx समय available. Invalid बार
	 * should have been handled by the upper layers.
	 */
	अगर (tx_ring->launchसमय_enable) अणु
		ts = kसमय_प्रकारo_बारpec64(first->skb->tstamp);
		skb_txसमय_consumed(first->skb);
		context_desc->seqnum_seed = cpu_to_le32(ts.tv_nsec / 32);
	पूर्ण अन्यथा अणु
		context_desc->seqnum_seed = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक igb_tso(काष्ठा igb_ring *tx_ring,
		   काष्ठा igb_tx_buffer *first,
		   u8 *hdr_len)
अणु
	u32 vlan_macip_lens, type_tucmd, mss_l4len_idx;
	काष्ठा sk_buff *skb = first->skb;
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
		काष्ठा udphdr *udp;
		अचिन्हित अक्षर *hdr;
	पूर्ण l4;
	u32 paylen, l4_offset;
	पूर्णांक err;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	err = skb_cow_head(skb, 0);
	अगर (err < 0)
		वापस err;

	ip.hdr = skb_network_header(skb);
	l4.hdr = skb_checksum_start(skb);

	/* ADV DTYP TUCMD MKRLOC/ISCSIHEDLEN */
	type_tucmd = (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) ?
		      E1000_ADVTXD_TUCMD_L4T_UDP : E1000_ADVTXD_TUCMD_L4T_TCP;

	/* initialize outer IP header fields */
	अगर (ip.v4->version == 4) अणु
		अचिन्हित अक्षर *csum_start = skb_checksum_start(skb);
		अचिन्हित अक्षर *trans_start = ip.hdr + (ip.v4->ihl * 4);

		/* IP header will have to cancel out any data that
		 * is not a part of the outer IP header
		 */
		ip.v4->check = csum_fold(csum_partial(trans_start,
						      csum_start - trans_start,
						      0));
		type_tucmd |= E1000_ADVTXD_TUCMD_IPV4;

		ip.v4->tot_len = 0;
		first->tx_flags |= IGB_TX_FLAGS_TSO |
				   IGB_TX_FLAGS_CSUM |
				   IGB_TX_FLAGS_IPV4;
	पूर्ण अन्यथा अणु
		ip.v6->payload_len = 0;
		first->tx_flags |= IGB_TX_FLAGS_TSO |
				   IGB_TX_FLAGS_CSUM;
	पूर्ण

	/* determine offset of inner transport header */
	l4_offset = l4.hdr - skb->data;

	/* हटाओ payload length from inner checksum */
	paylen = skb->len - l4_offset;
	अगर (type_tucmd & E1000_ADVTXD_TUCMD_L4T_TCP) अणु
		/* compute length of segmentation header */
		*hdr_len = (l4.tcp->करोff * 4) + l4_offset;
		csum_replace_by_dअगरf(&l4.tcp->check,
			(__क्रमce __wsum)htonl(paylen));
	पूर्ण अन्यथा अणु
		/* compute length of segmentation header */
		*hdr_len = माप(*l4.udp) + l4_offset;
		csum_replace_by_dअगरf(&l4.udp->check,
				     (__क्रमce __wsum)htonl(paylen));
	पूर्ण

	/* update gso size and bytecount with header size */
	first->gso_segs = skb_shinfo(skb)->gso_segs;
	first->bytecount += (first->gso_segs - 1) * *hdr_len;

	/* MSS L4LEN IDX */
	mss_l4len_idx = (*hdr_len - l4_offset) << E1000_ADVTXD_L4LEN_SHIFT;
	mss_l4len_idx |= skb_shinfo(skb)->gso_size << E1000_ADVTXD_MSS_SHIFT;

	/* VLAN MACLEN IPLEN */
	vlan_macip_lens = l4.hdr - ip.hdr;
	vlan_macip_lens |= (ip.hdr - skb->data) << E1000_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IGB_TX_FLAGS_VLAN_MASK;

	igb_tx_ctxtdesc(tx_ring, first, vlan_macip_lens,
			type_tucmd, mss_l4len_idx);

	वापस 1;
पूर्ण

अटल व्योम igb_tx_csum(काष्ठा igb_ring *tx_ring, काष्ठा igb_tx_buffer *first)
अणु
	काष्ठा sk_buff *skb = first->skb;
	u32 vlan_macip_lens = 0;
	u32 type_tucmd = 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
csum_failed:
		अगर (!(first->tx_flags & IGB_TX_FLAGS_VLAN) &&
		    !tx_ring->launchसमय_enable)
			वापस;
		जाओ no_csum;
	पूर्ण

	चयन (skb->csum_offset) अणु
	हाल दुरत्व(काष्ठा tcphdr, check):
		type_tucmd = E1000_ADVTXD_TUCMD_L4T_TCP;
		fallthrough;
	हाल दुरत्व(काष्ठा udphdr, check):
		अवरोध;
	हाल दुरत्व(काष्ठा sctphdr, checksum):
		/* validate that this is actually an SCTP request */
		अगर (skb_csum_is_sctp(skb)) अणु
			type_tucmd = E1000_ADVTXD_TUCMD_L4T_SCTP;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		skb_checksum_help(skb);
		जाओ csum_failed;
	पूर्ण

	/* update TX checksum flag */
	first->tx_flags |= IGB_TX_FLAGS_CSUM;
	vlan_macip_lens = skb_checksum_start_offset(skb) -
			  skb_network_offset(skb);
no_csum:
	vlan_macip_lens |= skb_network_offset(skb) << E1000_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IGB_TX_FLAGS_VLAN_MASK;

	igb_tx_ctxtdesc(tx_ring, first, vlan_macip_lens, type_tucmd, 0);
पूर्ण

#घोषणा IGB_SET_FLAG(_input, _flag, _result) \
	((_flag <= _result) ? \
	 ((u32)(_input & _flag) * (_result / _flag)) : \
	 ((u32)(_input & _flag) / (_flag / _result)))

अटल u32 igb_tx_cmd_type(काष्ठा sk_buff *skb, u32 tx_flags)
अणु
	/* set type क्रम advanced descriptor with frame checksum insertion */
	u32 cmd_type = E1000_ADVTXD_DTYP_DATA |
		       E1000_ADVTXD_DCMD_DEXT |
		       E1000_ADVTXD_DCMD_IFCS;

	/* set HW vlan bit अगर vlan is present */
	cmd_type |= IGB_SET_FLAG(tx_flags, IGB_TX_FLAGS_VLAN,
				 (E1000_ADVTXD_DCMD_VLE));

	/* set segmentation bits क्रम TSO */
	cmd_type |= IGB_SET_FLAG(tx_flags, IGB_TX_FLAGS_TSO,
				 (E1000_ADVTXD_DCMD_TSE));

	/* set बारtamp bit अगर present */
	cmd_type |= IGB_SET_FLAG(tx_flags, IGB_TX_FLAGS_TSTAMP,
				 (E1000_ADVTXD_MAC_TSTAMP));

	/* insert frame checksum */
	cmd_type ^= IGB_SET_FLAG(skb->no_fcs, 1, E1000_ADVTXD_DCMD_IFCS);

	वापस cmd_type;
पूर्ण

अटल व्योम igb_tx_olinfo_status(काष्ठा igb_ring *tx_ring,
				 जोड़ e1000_adv_tx_desc *tx_desc,
				 u32 tx_flags, अचिन्हित पूर्णांक paylen)
अणु
	u32 olinfo_status = paylen << E1000_ADVTXD_PAYLEN_SHIFT;

	/* 82575 requires a unique index per ring */
	अगर (test_bit(IGB_RING_FLAG_TX_CTX_IDX, &tx_ring->flags))
		olinfo_status |= tx_ring->reg_idx << 4;

	/* insert L4 checksum */
	olinfo_status |= IGB_SET_FLAG(tx_flags,
				      IGB_TX_FLAGS_CSUM,
				      (E1000_TXD_POPTS_TXSM << 8));

	/* insert IPv4 checksum */
	olinfo_status |= IGB_SET_FLAG(tx_flags,
				      IGB_TX_FLAGS_IPV4,
				      (E1000_TXD_POPTS_IXSM << 8));

	tx_desc->पढ़ो.olinfo_status = cpu_to_le32(olinfo_status);
पूर्ण

अटल पूर्णांक __igb_maybe_stop_tx(काष्ठा igb_ring *tx_ring, स्थिर u16 size)
अणु
	काष्ठा net_device *netdev = tx_ring->netdev;

	netअगर_stop_subqueue(netdev, tx_ring->queue_index);

	/* Herbert's original patch had:
	 *  smp_mb__after_netअगर_stop_queue();
	 * but since that करोesn't exist yet, just खोलो code it.
	 */
	smp_mb();

	/* We need to check again in a हाल another CPU has just
	 * made room available.
	 */
	अगर (igb_desc_unused(tx_ring) < size)
		वापस -EBUSY;

	/* A reprieve! */
	netअगर_wake_subqueue(netdev, tx_ring->queue_index);

	u64_stats_update_begin(&tx_ring->tx_syncp2);
	tx_ring->tx_stats.restart_queue2++;
	u64_stats_update_end(&tx_ring->tx_syncp2);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक igb_maybe_stop_tx(काष्ठा igb_ring *tx_ring, स्थिर u16 size)
अणु
	अगर (igb_desc_unused(tx_ring) >= size)
		वापस 0;
	वापस __igb_maybe_stop_tx(tx_ring, size);
पूर्ण

अटल पूर्णांक igb_tx_map(काष्ठा igb_ring *tx_ring,
		      काष्ठा igb_tx_buffer *first,
		      स्थिर u8 hdr_len)
अणु
	काष्ठा sk_buff *skb = first->skb;
	काष्ठा igb_tx_buffer *tx_buffer;
	जोड़ e1000_adv_tx_desc *tx_desc;
	skb_frag_t *frag;
	dma_addr_t dma;
	अचिन्हित पूर्णांक data_len, size;
	u32 tx_flags = first->tx_flags;
	u32 cmd_type = igb_tx_cmd_type(skb, tx_flags);
	u16 i = tx_ring->next_to_use;

	tx_desc = IGB_TX_DESC(tx_ring, i);

	igb_tx_olinfo_status(tx_ring, tx_desc, tx_flags, skb->len - hdr_len);

	size = skb_headlen(skb);
	data_len = skb->data_len;

	dma = dma_map_single(tx_ring->dev, skb->data, size, DMA_TO_DEVICE);

	tx_buffer = first;

	क्रम (frag = &skb_shinfo(skb)->frags[0];; frag++) अणु
		अगर (dma_mapping_error(tx_ring->dev, dma))
			जाओ dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_buffer, len, size);
		dma_unmap_addr_set(tx_buffer, dma, dma);

		tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);

		जबतक (unlikely(size > IGB_MAX_DATA_PER_TXD)) अणु
			tx_desc->पढ़ो.cmd_type_len =
				cpu_to_le32(cmd_type ^ IGB_MAX_DATA_PER_TXD);

			i++;
			tx_desc++;
			अगर (i == tx_ring->count) अणु
				tx_desc = IGB_TX_DESC(tx_ring, 0);
				i = 0;
			पूर्ण
			tx_desc->पढ़ो.olinfo_status = 0;

			dma += IGB_MAX_DATA_PER_TXD;
			size -= IGB_MAX_DATA_PER_TXD;

			tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);
		पूर्ण

		अगर (likely(!data_len))
			अवरोध;

		tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type ^ size);

		i++;
		tx_desc++;
		अगर (i == tx_ring->count) अणु
			tx_desc = IGB_TX_DESC(tx_ring, 0);
			i = 0;
		पूर्ण
		tx_desc->पढ़ो.olinfo_status = 0;

		size = skb_frag_size(frag);
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0,
				       size, DMA_TO_DEVICE);

		tx_buffer = &tx_ring->tx_buffer_info[i];
	पूर्ण

	/* ग_लिखो last descriptor with RS and EOP bits */
	cmd_type |= size | IGB_TXD_DCMD;
	tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type);

	netdev_tx_sent_queue(txring_txq(tx_ring), first->bytecount);

	/* set the बारtamp */
	first->समय_stamp = jअगरfies;

	skb_tx_बारtamp(skb);

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.  (Only applicable क्रम weak-ordered
	 * memory model archs, such as IA-64).
	 *
	 * We also need this memory barrier to make certain all of the
	 * status bits have been updated beक्रमe next_to_watch is written.
	 */
	dma_wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	i++;
	अगर (i == tx_ring->count)
		i = 0;

	tx_ring->next_to_use = i;

	/* Make sure there is space in the ring क्रम the next send. */
	igb_maybe_stop_tx(tx_ring, DESC_NEEDED);

	अगर (netअगर_xmit_stopped(txring_txq(tx_ring)) || !netdev_xmit_more()) अणु
		ग_लिखोl(i, tx_ring->tail);
	पूर्ण
	वापस 0;

dma_error:
	dev_err(tx_ring->dev, "TX DMA map failed\n");
	tx_buffer = &tx_ring->tx_buffer_info[i];

	/* clear dma mappings क्रम failed tx_buffer_info map */
	जबतक (tx_buffer != first) अणु
		अगर (dma_unmap_len(tx_buffer, len))
			dma_unmap_page(tx_ring->dev,
				       dma_unmap_addr(tx_buffer, dma),
				       dma_unmap_len(tx_buffer, len),
				       DMA_TO_DEVICE);
		dma_unmap_len_set(tx_buffer, len, 0);

		अगर (i-- == 0)
			i += tx_ring->count;
		tx_buffer = &tx_ring->tx_buffer_info[i];
	पूर्ण

	अगर (dma_unmap_len(tx_buffer, len))
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);
	dma_unmap_len_set(tx_buffer, len, 0);

	dev_kमुक्त_skb_any(tx_buffer->skb);
	tx_buffer->skb = शून्य;

	tx_ring->next_to_use = i;

	वापस -1;
पूर्ण

पूर्णांक igb_xmit_xdp_ring(काष्ठा igb_adapter *adapter,
		      काष्ठा igb_ring *tx_ring,
		      काष्ठा xdp_frame *xdpf)
अणु
	जोड़ e1000_adv_tx_desc *tx_desc;
	u32 len, cmd_type, olinfo_status;
	काष्ठा igb_tx_buffer *tx_buffer;
	dma_addr_t dma;
	u16 i;

	len = xdpf->len;

	अगर (unlikely(!igb_desc_unused(tx_ring)))
		वापस IGB_XDP_CONSUMED;

	dma = dma_map_single(tx_ring->dev, xdpf->data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(tx_ring->dev, dma))
		वापस IGB_XDP_CONSUMED;

	/* record the location of the first descriptor क्रम this packet */
	tx_buffer = &tx_ring->tx_buffer_info[tx_ring->next_to_use];
	tx_buffer->bytecount = len;
	tx_buffer->gso_segs = 1;
	tx_buffer->protocol = 0;

	i = tx_ring->next_to_use;
	tx_desc = IGB_TX_DESC(tx_ring, i);

	dma_unmap_len_set(tx_buffer, len, len);
	dma_unmap_addr_set(tx_buffer, dma, dma);
	tx_buffer->type = IGB_TYPE_XDP;
	tx_buffer->xdpf = xdpf;

	tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);

	/* put descriptor type bits */
	cmd_type = E1000_ADVTXD_DTYP_DATA |
		   E1000_ADVTXD_DCMD_DEXT |
		   E1000_ADVTXD_DCMD_IFCS;
	cmd_type |= len | IGB_TXD_DCMD;
	tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type);

	olinfo_status = cpu_to_le32(len << E1000_ADVTXD_PAYLEN_SHIFT);
	/* 82575 requires a unique index per ring */
	अगर (test_bit(IGB_RING_FLAG_TX_CTX_IDX, &tx_ring->flags))
		olinfo_status |= tx_ring->reg_idx << 4;

	tx_desc->पढ़ो.olinfo_status = olinfo_status;

	netdev_tx_sent_queue(txring_txq(tx_ring), tx_buffer->bytecount);

	/* set the बारtamp */
	tx_buffer->समय_stamp = jअगरfies;

	/* Aव्योम any potential race with xdp_xmit and cleanup */
	smp_wmb();

	/* set next_to_watch value indicating a packet is present */
	i++;
	अगर (i == tx_ring->count)
		i = 0;

	tx_buffer->next_to_watch = tx_desc;
	tx_ring->next_to_use = i;

	/* Make sure there is space in the ring क्रम the next send. */
	igb_maybe_stop_tx(tx_ring, DESC_NEEDED);

	अगर (netअगर_xmit_stopped(txring_txq(tx_ring)) || !netdev_xmit_more())
		ग_लिखोl(i, tx_ring->tail);

	वापस IGB_XDP_TX;
पूर्ण

netdev_tx_t igb_xmit_frame_ring(काष्ठा sk_buff *skb,
				काष्ठा igb_ring *tx_ring)
अणु
	काष्ठा igb_tx_buffer *first;
	पूर्णांक tso;
	u32 tx_flags = 0;
	अचिन्हित लघु f;
	u16 count = TXD_USE_COUNT(skb_headlen(skb));
	__be16 protocol = vlan_get_protocol(skb);
	u8 hdr_len = 0;

	/* need: 1 descriptor per page * PAGE_SIZE/IGB_MAX_DATA_PER_TXD,
	 *       + 1 desc क्रम skb_headlen/IGB_MAX_DATA_PER_TXD,
	 *       + 2 desc gap to keep tail from touching head,
	 *       + 1 desc क्रम context descriptor,
	 * otherwise try next समय
	 */
	क्रम (f = 0; f < skb_shinfo(skb)->nr_frags; f++)
		count += TXD_USE_COUNT(skb_frag_size(
						&skb_shinfo(skb)->frags[f]));

	अगर (igb_maybe_stop_tx(tx_ring, count + 3)) अणु
		/* this is a hard error */
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* record the location of the first descriptor क्रम this packet */
	first = &tx_ring->tx_buffer_info[tx_ring->next_to_use];
	first->type = IGB_TYPE_SKB;
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) अणु
		काष्ठा igb_adapter *adapter = netdev_priv(tx_ring->netdev);

		अगर (adapter->tstamp_config.tx_type == HWTSTAMP_TX_ON &&
		    !test_and_set_bit_lock(__IGB_PTP_TX_IN_PROGRESS,
					   &adapter->state)) अणु
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
			tx_flags |= IGB_TX_FLAGS_TSTAMP;

			adapter->ptp_tx_skb = skb_get(skb);
			adapter->ptp_tx_start = jअगरfies;
			अगर (adapter->hw.mac.type == e1000_82576)
				schedule_work(&adapter->ptp_tx_work);
		पूर्ण अन्यथा अणु
			adapter->tx_hwtstamp_skipped++;
		पूर्ण
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		tx_flags |= IGB_TX_FLAGS_VLAN;
		tx_flags |= (skb_vlan_tag_get(skb) << IGB_TX_FLAGS_VLAN_SHIFT);
	पूर्ण

	/* record initial flags and protocol */
	first->tx_flags = tx_flags;
	first->protocol = protocol;

	tso = igb_tso(tx_ring, first, &hdr_len);
	अगर (tso < 0)
		जाओ out_drop;
	अन्यथा अगर (!tso)
		igb_tx_csum(tx_ring, first);

	अगर (igb_tx_map(tx_ring, first, hdr_len))
		जाओ cleanup_tx_tstamp;

	वापस NETDEV_TX_OK;

out_drop:
	dev_kमुक्त_skb_any(first->skb);
	first->skb = शून्य;
cleanup_tx_tstamp:
	अगर (unlikely(tx_flags & IGB_TX_FLAGS_TSTAMP)) अणु
		काष्ठा igb_adapter *adapter = netdev_priv(tx_ring->netdev);

		dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = शून्य;
		अगर (adapter->hw.mac.type == e1000_82576)
			cancel_work_sync(&adapter->ptp_tx_work);
		clear_bit_unlock(__IGB_PTP_TX_IN_PROGRESS, &adapter->state);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल अंतरभूत काष्ठा igb_ring *igb_tx_queue_mapping(काष्ठा igb_adapter *adapter,
						    काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक r_idx = skb->queue_mapping;

	अगर (r_idx >= adapter->num_tx_queues)
		r_idx = r_idx % adapter->num_tx_queues;

	वापस adapter->tx_ring[r_idx];
पूर्ण

अटल netdev_tx_t igb_xmit_frame(काष्ठा sk_buff *skb,
				  काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	/* The minimum packet size with TCTL.PSP set is 17 so pad the skb
	 * in order to meet this minimum size requirement.
	 */
	अगर (skb_put_padto(skb, 17))
		वापस NETDEV_TX_OK;

	वापस igb_xmit_frame_ring(skb, igb_tx_queue_mapping(adapter, skb));
पूर्ण

/**
 *  igb_tx_समयout - Respond to a Tx Hang
 *  @netdev: network पूर्णांकerface device काष्ठाure
 *  @txqueue: number of the Tx queue that hung (unused)
 **/
अटल व्योम igb_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक __always_unused txqueue)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* Do the reset outside of पूर्णांकerrupt context */
	adapter->tx_समयout_count++;

	अगर (hw->mac.type >= e1000_82580)
		hw->dev_spec._82575.global_device_reset = true;

	schedule_work(&adapter->reset_task);
	wr32(E1000_EICS,
	     (adapter->eims_enable_mask & ~adapter->eims_other));
पूर्ण

अटल व्योम igb_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा igb_adapter *adapter;
	adapter = container_of(work, काष्ठा igb_adapter, reset_task);

	rtnl_lock();
	/* If we're alपढ़ोy करोwn or resetting, just bail */
	अगर (test_bit(__IGB_DOWN, &adapter->state) ||
	    test_bit(__IGB_RESETTING, &adapter->state)) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	igb_dump(adapter);
	netdev_err(adapter->netdev, "Reset adapter\n");
	igb_reinit_locked(adapter);
	rtnl_unlock();
पूर्ण

/**
 *  igb_get_stats64 - Get System Network Statistics
 *  @netdev: network पूर्णांकerface device काष्ठाure
 *  @stats: rtnl_link_stats64 poपूर्णांकer
 **/
अटल व्योम igb_get_stats64(काष्ठा net_device *netdev,
			    काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	spin_lock(&adapter->stats64_lock);
	igb_update_stats(adapter);
	स_नकल(stats, &adapter->stats64, माप(*stats));
	spin_unlock(&adapter->stats64_lock);
पूर्ण

/**
 *  igb_change_mtu - Change the Maximum Transfer Unit
 *  @netdev: network पूर्णांकerface device काष्ठाure
 *  @new_mtu: new value क्रम maximum frame size
 *
 *  Returns 0 on success, negative on failure
 **/
अटल पूर्णांक igb_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	पूर्णांक max_frame = new_mtu + IGB_ETH_PKT_HDR_PAD;

	अगर (adapter->xdp_prog) अणु
		पूर्णांक i;

		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			काष्ठा igb_ring *ring = adapter->rx_ring[i];

			अगर (max_frame > igb_rx_bufsz(ring)) अणु
				netdev_warn(adapter->netdev,
					    "Requested MTU size is not supported with XDP. Max frame size is %d\n",
					    max_frame);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/* adjust max frame to be at least the size of a standard frame */
	अगर (max_frame < (ETH_FRAME_LEN + ETH_FCS_LEN))
		max_frame = ETH_FRAME_LEN + ETH_FCS_LEN;

	जबतक (test_and_set_bit(__IGB_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	/* igb_करोwn has a dependency on max_frame_size */
	adapter->max_frame_size = max_frame;

	अगर (netअगर_running(netdev))
		igb_करोwn(adapter);

	netdev_dbg(netdev, "changing MTU from %d to %d\n",
		   netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	अगर (netअगर_running(netdev))
		igb_up(adapter);
	अन्यथा
		igb_reset(adapter);

	clear_bit(__IGB_RESETTING, &adapter->state);

	वापस 0;
पूर्ण

/**
 *  igb_update_stats - Update the board statistics counters
 *  @adapter: board निजी काष्ठाure
 **/
व्योम igb_update_stats(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा rtnl_link_stats64 *net_stats = &adapter->stats64;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u32 reg, mpc;
	पूर्णांक i;
	u64 bytes, packets;
	अचिन्हित पूर्णांक start;
	u64 _bytes, _packets;

	/* Prevent stats update जबतक adapter is being reset, or अगर the pci
	 * connection is करोwn.
	 */
	अगर (adapter->link_speed == 0)
		वापस;
	अगर (pci_channel_offline(pdev))
		वापस;

	bytes = 0;
	packets = 0;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा igb_ring *ring = adapter->rx_ring[i];
		u32 rqdpc = rd32(E1000_RQDPC(i));
		अगर (hw->mac.type >= e1000_i210)
			wr32(E1000_RQDPC(i), 0);

		अगर (rqdpc) अणु
			ring->rx_stats.drops += rqdpc;
			net_stats->rx_fअगरo_errors += rqdpc;
		पूर्ण

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->rx_syncp);
			_bytes = ring->rx_stats.bytes;
			_packets = ring->rx_stats.packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->rx_syncp, start));
		bytes += _bytes;
		packets += _packets;
	पूर्ण

	net_stats->rx_bytes = bytes;
	net_stats->rx_packets = packets;

	bytes = 0;
	packets = 0;
	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा igb_ring *ring = adapter->tx_ring[i];
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->tx_syncp);
			_bytes = ring->tx_stats.bytes;
			_packets = ring->tx_stats.packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->tx_syncp, start));
		bytes += _bytes;
		packets += _packets;
	पूर्ण
	net_stats->tx_bytes = bytes;
	net_stats->tx_packets = packets;
	rcu_पढ़ो_unlock();

	/* पढ़ो stats रेजिस्टरs */
	adapter->stats.crcerrs += rd32(E1000_CRCERRS);
	adapter->stats.gprc += rd32(E1000_GPRC);
	adapter->stats.gorc += rd32(E1000_GORCL);
	rd32(E1000_GORCH); /* clear GORCL */
	adapter->stats.bprc += rd32(E1000_BPRC);
	adapter->stats.mprc += rd32(E1000_MPRC);
	adapter->stats.roc += rd32(E1000_ROC);

	adapter->stats.prc64 += rd32(E1000_PRC64);
	adapter->stats.prc127 += rd32(E1000_PRC127);
	adapter->stats.prc255 += rd32(E1000_PRC255);
	adapter->stats.prc511 += rd32(E1000_PRC511);
	adapter->stats.prc1023 += rd32(E1000_PRC1023);
	adapter->stats.prc1522 += rd32(E1000_PRC1522);
	adapter->stats.symerrs += rd32(E1000_SYMERRS);
	adapter->stats.sec += rd32(E1000_SEC);

	mpc = rd32(E1000_MPC);
	adapter->stats.mpc += mpc;
	net_stats->rx_fअगरo_errors += mpc;
	adapter->stats.scc += rd32(E1000_SCC);
	adapter->stats.ecol += rd32(E1000_ECOL);
	adapter->stats.mcc += rd32(E1000_MCC);
	adapter->stats.latecol += rd32(E1000_LATECOL);
	adapter->stats.dc += rd32(E1000_DC);
	adapter->stats.rlec += rd32(E1000_RLEC);
	adapter->stats.xonrxc += rd32(E1000_XONRXC);
	adapter->stats.xontxc += rd32(E1000_XONTXC);
	adapter->stats.xoffrxc += rd32(E1000_XOFFRXC);
	adapter->stats.xofftxc += rd32(E1000_XOFFTXC);
	adapter->stats.fcruc += rd32(E1000_FCRUC);
	adapter->stats.gptc += rd32(E1000_GPTC);
	adapter->stats.gotc += rd32(E1000_GOTCL);
	rd32(E1000_GOTCH); /* clear GOTCL */
	adapter->stats.rnbc += rd32(E1000_RNBC);
	adapter->stats.ruc += rd32(E1000_RUC);
	adapter->stats.rfc += rd32(E1000_RFC);
	adapter->stats.rjc += rd32(E1000_RJC);
	adapter->stats.tor += rd32(E1000_TORH);
	adapter->stats.tot += rd32(E1000_TOTH);
	adapter->stats.tpr += rd32(E1000_TPR);

	adapter->stats.ptc64 += rd32(E1000_PTC64);
	adapter->stats.ptc127 += rd32(E1000_PTC127);
	adapter->stats.ptc255 += rd32(E1000_PTC255);
	adapter->stats.ptc511 += rd32(E1000_PTC511);
	adapter->stats.ptc1023 += rd32(E1000_PTC1023);
	adapter->stats.ptc1522 += rd32(E1000_PTC1522);

	adapter->stats.mptc += rd32(E1000_MPTC);
	adapter->stats.bptc += rd32(E1000_BPTC);

	adapter->stats.tpt += rd32(E1000_TPT);
	adapter->stats.colc += rd32(E1000_COLC);

	adapter->stats.algnerrc += rd32(E1000_ALGNERRC);
	/* पढ़ो पूर्णांकernal phy specअगरic stats */
	reg = rd32(E1000_CTRL_EXT);
	अगर (!(reg & E1000_CTRL_EXT_LINK_MODE_MASK)) अणु
		adapter->stats.rxerrc += rd32(E1000_RXERRC);

		/* this stat has invalid values on i210/i211 */
		अगर ((hw->mac.type != e1000_i210) &&
		    (hw->mac.type != e1000_i211))
			adapter->stats.tncrs += rd32(E1000_TNCRS);
	पूर्ण

	adapter->stats.tsctc += rd32(E1000_TSCTC);
	adapter->stats.tsctfc += rd32(E1000_TSCTFC);

	adapter->stats.iac += rd32(E1000_IAC);
	adapter->stats.icrxoc += rd32(E1000_ICRXOC);
	adapter->stats.icrxptc += rd32(E1000_ICRXPTC);
	adapter->stats.icrxatc += rd32(E1000_ICRXATC);
	adapter->stats.ictxptc += rd32(E1000_ICTXPTC);
	adapter->stats.ictxatc += rd32(E1000_ICTXATC);
	adapter->stats.ictxqec += rd32(E1000_ICTXQEC);
	adapter->stats.ictxqmtc += rd32(E1000_ICTXQMTC);
	adapter->stats.icrxdmtc += rd32(E1000_ICRXDMTC);

	/* Fill out the OS statistics काष्ठाure */
	net_stats->multicast = adapter->stats.mprc;
	net_stats->collisions = adapter->stats.colc;

	/* Rx Errors */

	/* RLEC on some newer hardware can be incorrect so build
	 * our own version based on RUC and ROC
	 */
	net_stats->rx_errors = adapter->stats.rxerrc +
		adapter->stats.crcerrs + adapter->stats.algnerrc +
		adapter->stats.ruc + adapter->stats.roc +
		adapter->stats.cexterr;
	net_stats->rx_length_errors = adapter->stats.ruc +
				      adapter->stats.roc;
	net_stats->rx_crc_errors = adapter->stats.crcerrs;
	net_stats->rx_frame_errors = adapter->stats.algnerrc;
	net_stats->rx_missed_errors = adapter->stats.mpc;

	/* Tx Errors */
	net_stats->tx_errors = adapter->stats.ecol +
			       adapter->stats.latecol;
	net_stats->tx_पातed_errors = adapter->stats.ecol;
	net_stats->tx_winकरोw_errors = adapter->stats.latecol;
	net_stats->tx_carrier_errors = adapter->stats.tncrs;

	/* Tx Dropped needs to be मुख्यtained अन्यथाwhere */

	/* Management Stats */
	adapter->stats.mgptc += rd32(E1000_MGTPTC);
	adapter->stats.mgprc += rd32(E1000_MGTPRC);
	adapter->stats.mgpdc += rd32(E1000_MGTPDC);

	/* OS2BMC Stats */
	reg = rd32(E1000_MANC);
	अगर (reg & E1000_MANC_EN_BMC2OS) अणु
		adapter->stats.o2bgptc += rd32(E1000_O2BGPTC);
		adapter->stats.o2bspc += rd32(E1000_O2BSPC);
		adapter->stats.b2ospc += rd32(E1000_B2OSPC);
		adapter->stats.b2ogprc += rd32(E1000_B2OGPRC);
	पूर्ण
पूर्ण

अटल व्योम igb_tsync_पूर्णांकerrupt(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा ptp_घड़ी_event event;
	काष्ठा बारpec64 ts;
	u32 ack = 0, tsauxc, sec, nsec, tsicr = rd32(E1000_TSICR);

	अगर (tsicr & TSINTR_SYS_WRAP) अणु
		event.type = PTP_CLOCK_PPS;
		अगर (adapter->ptp_caps.pps)
			ptp_घड़ी_event(adapter->ptp_घड़ी, &event);
		ack |= TSINTR_SYS_WRAP;
	पूर्ण

	अगर (tsicr & E1000_TSICR_TXTS) अणु
		/* retrieve hardware बारtamp */
		schedule_work(&adapter->ptp_tx_work);
		ack |= E1000_TSICR_TXTS;
	पूर्ण

	अगर (tsicr & TSINTR_TT0) अणु
		spin_lock(&adapter->पंचांगreg_lock);
		ts = बारpec64_add(adapter->perout[0].start,
				    adapter->perout[0].period);
		/* u32 conversion of tv_sec is safe until y2106 */
		wr32(E1000_TRGTTIML0, ts.tv_nsec);
		wr32(E1000_TRGTTIMH0, (u32)ts.tv_sec);
		tsauxc = rd32(E1000_TSAUXC);
		tsauxc |= TSAUXC_EN_TT0;
		wr32(E1000_TSAUXC, tsauxc);
		adapter->perout[0].start = ts;
		spin_unlock(&adapter->पंचांगreg_lock);
		ack |= TSINTR_TT0;
	पूर्ण

	अगर (tsicr & TSINTR_TT1) अणु
		spin_lock(&adapter->पंचांगreg_lock);
		ts = बारpec64_add(adapter->perout[1].start,
				    adapter->perout[1].period);
		wr32(E1000_TRGTTIML1, ts.tv_nsec);
		wr32(E1000_TRGTTIMH1, (u32)ts.tv_sec);
		tsauxc = rd32(E1000_TSAUXC);
		tsauxc |= TSAUXC_EN_TT1;
		wr32(E1000_TSAUXC, tsauxc);
		adapter->perout[1].start = ts;
		spin_unlock(&adapter->पंचांगreg_lock);
		ack |= TSINTR_TT1;
	पूर्ण

	अगर (tsicr & TSINTR_AUTT0) अणु
		nsec = rd32(E1000_AUXSTMPL0);
		sec  = rd32(E1000_AUXSTMPH0);
		event.type = PTP_CLOCK_EXTTS;
		event.index = 0;
		event.बारtamp = sec * 1000000000ULL + nsec;
		ptp_घड़ी_event(adapter->ptp_घड़ी, &event);
		ack |= TSINTR_AUTT0;
	पूर्ण

	अगर (tsicr & TSINTR_AUTT1) अणु
		nsec = rd32(E1000_AUXSTMPL1);
		sec  = rd32(E1000_AUXSTMPH1);
		event.type = PTP_CLOCK_EXTTS;
		event.index = 1;
		event.बारtamp = sec * 1000000000ULL + nsec;
		ptp_घड़ी_event(adapter->ptp_घड़ी, &event);
		ack |= TSINTR_AUTT1;
	पूर्ण

	/* acknowledge the पूर्णांकerrupts */
	wr32(E1000_TSICR, ack);
पूर्ण

अटल irqवापस_t igb_msix_other(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा igb_adapter *adapter = data;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 icr = rd32(E1000_ICR);
	/* पढ़ोing ICR causes bit 31 of EICR to be cleared */

	अगर (icr & E1000_ICR_DRSTA)
		schedule_work(&adapter->reset_task);

	अगर (icr & E1000_ICR_DOUTSYNC) अणु
		/* HW is reporting DMA is out of sync */
		adapter->stats.करोosync++;
		/* The DMA Out of Sync is also indication of a spoof event
		 * in IOV mode. Check the Wrong VM Behavior रेजिस्टर to
		 * see अगर it is really a spoof event.
		 */
		igb_check_wvbr(adapter);
	पूर्ण

	/* Check क्रम a mailbox event */
	अगर (icr & E1000_ICR_VMMB)
		igb_msg_task(adapter);

	अगर (icr & E1000_ICR_LSC) अणु
		hw->mac.get_link_status = 1;
		/* guard against पूर्णांकerrupt when we're going करोwn */
		अगर (!test_bit(__IGB_DOWN, &adapter->state))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);
	पूर्ण

	अगर (icr & E1000_ICR_TS)
		igb_tsync_पूर्णांकerrupt(adapter);

	wr32(E1000_EIMS, adapter->eims_other);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम igb_ग_लिखो_itr(काष्ठा igb_q_vector *q_vector)
अणु
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	u32 itr_val = q_vector->itr_val & 0x7FFC;

	अगर (!q_vector->set_itr)
		वापस;

	अगर (!itr_val)
		itr_val = 0x4;

	अगर (adapter->hw.mac.type == e1000_82575)
		itr_val |= itr_val << 16;
	अन्यथा
		itr_val |= E1000_EITR_CNT_IGNR;

	ग_लिखोl(itr_val, q_vector->itr_रेजिस्टर);
	q_vector->set_itr = 0;
पूर्ण

अटल irqवापस_t igb_msix_ring(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा igb_q_vector *q_vector = data;

	/* Write the ITR value calculated from the previous पूर्णांकerrupt. */
	igb_ग_लिखो_itr(q_vector);

	napi_schedule(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_IGB_DCA
अटल व्योम igb_update_tx_dca(काष्ठा igb_adapter *adapter,
			      काष्ठा igb_ring *tx_ring,
			      पूर्णांक cpu)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 txctrl = dca3_get_tag(tx_ring->dev, cpu);

	अगर (hw->mac.type != e1000_82575)
		txctrl <<= E1000_DCA_TXCTRL_CPUID_SHIFT;

	/* We can enable relaxed ordering क्रम पढ़ोs, but not ग_लिखोs when
	 * DCA is enabled.  This is due to a known issue in some chipsets
	 * which will cause the DCA tag to be cleared.
	 */
	txctrl |= E1000_DCA_TXCTRL_DESC_RRO_EN |
		  E1000_DCA_TXCTRL_DATA_RRO_EN |
		  E1000_DCA_TXCTRL_DESC_DCA_EN;

	wr32(E1000_DCA_TXCTRL(tx_ring->reg_idx), txctrl);
पूर्ण

अटल व्योम igb_update_rx_dca(काष्ठा igb_adapter *adapter,
			      काष्ठा igb_ring *rx_ring,
			      पूर्णांक cpu)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rxctrl = dca3_get_tag(&adapter->pdev->dev, cpu);

	अगर (hw->mac.type != e1000_82575)
		rxctrl <<= E1000_DCA_RXCTRL_CPUID_SHIFT;

	/* We can enable relaxed ordering क्रम पढ़ोs, but not ग_लिखोs when
	 * DCA is enabled.  This is due to a known issue in some chipsets
	 * which will cause the DCA tag to be cleared.
	 */
	rxctrl |= E1000_DCA_RXCTRL_DESC_RRO_EN |
		  E1000_DCA_RXCTRL_DESC_DCA_EN;

	wr32(E1000_DCA_RXCTRL(rx_ring->reg_idx), rxctrl);
पूर्ण

अटल व्योम igb_update_dca(काष्ठा igb_q_vector *q_vector)
अणु
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	पूर्णांक cpu = get_cpu();

	अगर (q_vector->cpu == cpu)
		जाओ out_no_update;

	अगर (q_vector->tx.ring)
		igb_update_tx_dca(adapter, q_vector->tx.ring, cpu);

	अगर (q_vector->rx.ring)
		igb_update_rx_dca(adapter, q_vector->rx.ring, cpu);

	q_vector->cpu = cpu;
out_no_update:
	put_cpu();
पूर्ण

अटल व्योम igb_setup_dca(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक i;

	अगर (!(adapter->flags & IGB_FLAG_DCA_ENABLED))
		वापस;

	/* Always use CB2 mode, dअगरference is masked in the CB driver. */
	wr32(E1000_DCA_CTRL, E1000_DCA_CTRL_DCA_MODE_CB2);

	क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
		adapter->q_vector[i]->cpu = -1;
		igb_update_dca(adapter->q_vector[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक __igb_notअगरy_dca(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ event = *(अचिन्हित दीर्घ *)data;

	चयन (event) अणु
	हाल DCA_PROVIDER_ADD:
		/* अगर alपढ़ोy enabled, करोn't करो it again */
		अगर (adapter->flags & IGB_FLAG_DCA_ENABLED)
			अवरोध;
		अगर (dca_add_requester(dev) == 0) अणु
			adapter->flags |= IGB_FLAG_DCA_ENABLED;
			dev_info(&pdev->dev, "DCA enabled\n");
			igb_setup_dca(adapter);
			अवरोध;
		पूर्ण
		fallthrough; /* since DCA is disabled. */
	हाल DCA_PROVIDER_REMOVE:
		अगर (adapter->flags & IGB_FLAG_DCA_ENABLED) अणु
			/* without this a class_device is left
			 * hanging around in the sysfs model
			 */
			dca_हटाओ_requester(dev);
			dev_info(&pdev->dev, "DCA disabled\n");
			adapter->flags &= ~IGB_FLAG_DCA_ENABLED;
			wr32(E1000_DCA_CTRL, E1000_DCA_CTRL_DCA_MODE_DISABLE);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igb_notअगरy_dca(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			  व्योम *p)
अणु
	पूर्णांक ret_val;

	ret_val = driver_क्रम_each_device(&igb_driver.driver, शून्य, &event,
					 __igb_notअगरy_dca);

	वापस ret_val ? NOTIFY_BAD : NOTIFY_DONE;
पूर्ण
#पूर्ण_अगर /* CONFIG_IGB_DCA */

#अगर_घोषित CONFIG_PCI_IOV
अटल पूर्णांक igb_vf_configure(काष्ठा igb_adapter *adapter, पूर्णांक vf)
अणु
	अचिन्हित अक्षर mac_addr[ETH_ALEN];

	eth_zero_addr(mac_addr);
	igb_set_vf_mac(adapter, vf, mac_addr);

	/* By शेष spoof check is enabled क्रम all VFs */
	adapter->vf_data[vf].spoofchk_enabled = true;

	/* By शेष VFs are not trusted */
	adapter->vf_data[vf].trusted = false;

	वापस 0;
पूर्ण

#पूर्ण_अगर
अटल व्योम igb_ping_all_vfs(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ping;
	पूर्णांक i;

	क्रम (i = 0 ; i < adapter->vfs_allocated_count; i++) अणु
		ping = E1000_PF_CONTROL_MSG;
		अगर (adapter->vf_data[i].flags & IGB_VF_FLAG_CTS)
			ping |= E1000_VT_MSGTYPE_CTS;
		igb_ग_लिखो_mbx(hw, &ping, 1, i);
	पूर्ण
पूर्ण

अटल पूर्णांक igb_set_vf_promisc(काष्ठा igb_adapter *adapter, u32 *msgbuf, u32 vf)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 vmolr = rd32(E1000_VMOLR(vf));
	काष्ठा vf_data_storage *vf_data = &adapter->vf_data[vf];

	vf_data->flags &= ~(IGB_VF_FLAG_UNI_PROMISC |
			    IGB_VF_FLAG_MULTI_PROMISC);
	vmolr &= ~(E1000_VMOLR_ROPE | E1000_VMOLR_ROMPE | E1000_VMOLR_MPME);

	अगर (*msgbuf & E1000_VF_SET_PROMISC_MULTICAST) अणु
		vmolr |= E1000_VMOLR_MPME;
		vf_data->flags |= IGB_VF_FLAG_MULTI_PROMISC;
		*msgbuf &= ~E1000_VF_SET_PROMISC_MULTICAST;
	पूर्ण अन्यथा अणु
		/* अगर we have hashes and we are clearing a multicast promisc
		 * flag we need to ग_लिखो the hashes to the MTA as this step
		 * was previously skipped
		 */
		अगर (vf_data->num_vf_mc_hashes > 30) अणु
			vmolr |= E1000_VMOLR_MPME;
		पूर्ण अन्यथा अगर (vf_data->num_vf_mc_hashes) अणु
			पूर्णांक j;

			vmolr |= E1000_VMOLR_ROMPE;
			क्रम (j = 0; j < vf_data->num_vf_mc_hashes; j++)
				igb_mta_set(hw, vf_data->vf_mc_hashes[j]);
		पूर्ण
	पूर्ण

	wr32(E1000_VMOLR(vf), vmolr);

	/* there are flags left unprocessed, likely not supported */
	अगर (*msgbuf & E1000_VT_MSGINFO_MASK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक igb_set_vf_multicasts(काष्ठा igb_adapter *adapter,
				  u32 *msgbuf, u32 vf)
अणु
	पूर्णांक n = (msgbuf[0] & E1000_VT_MSGINFO_MASK) >> E1000_VT_MSGINFO_SHIFT;
	u16 *hash_list = (u16 *)&msgbuf[1];
	काष्ठा vf_data_storage *vf_data = &adapter->vf_data[vf];
	पूर्णांक i;

	/* salt away the number of multicast addresses asचिन्हित
	 * to this VF क्रम later use to restore when the PF multi cast
	 * list changes
	 */
	vf_data->num_vf_mc_hashes = n;

	/* only up to 30 hash values supported */
	अगर (n > 30)
		n = 30;

	/* store the hashes क्रम later use */
	क्रम (i = 0; i < n; i++)
		vf_data->vf_mc_hashes[i] = hash_list[i];

	/* Flush and reset the mta with the new values */
	igb_set_rx_mode(adapter->netdev);

	वापस 0;
पूर्ण

अटल व्योम igb_restore_vf_multicasts(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा vf_data_storage *vf_data;
	पूर्णांक i, j;

	क्रम (i = 0; i < adapter->vfs_allocated_count; i++) अणु
		u32 vmolr = rd32(E1000_VMOLR(i));

		vmolr &= ~(E1000_VMOLR_ROMPE | E1000_VMOLR_MPME);

		vf_data = &adapter->vf_data[i];

		अगर ((vf_data->num_vf_mc_hashes > 30) ||
		    (vf_data->flags & IGB_VF_FLAG_MULTI_PROMISC)) अणु
			vmolr |= E1000_VMOLR_MPME;
		पूर्ण अन्यथा अगर (vf_data->num_vf_mc_hashes) अणु
			vmolr |= E1000_VMOLR_ROMPE;
			क्रम (j = 0; j < vf_data->num_vf_mc_hashes; j++)
				igb_mta_set(hw, vf_data->vf_mc_hashes[j]);
		पूर्ण
		wr32(E1000_VMOLR(i), vmolr);
	पूर्ण
पूर्ण

अटल व्योम igb_clear_vf_vfta(काष्ठा igb_adapter *adapter, u32 vf)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 pool_mask, vlvf_mask, i;

	/* create mask क्रम VF and other pools */
	pool_mask = E1000_VLVF_POOLSEL_MASK;
	vlvf_mask = BIT(E1000_VLVF_POOLSEL_SHIFT + vf);

	/* drop PF from pool bits */
	pool_mask &= ~BIT(E1000_VLVF_POOLSEL_SHIFT +
			     adapter->vfs_allocated_count);

	/* Find the vlan filter क्रम this id */
	क्रम (i = E1000_VLVF_ARRAY_SIZE; i--;) अणु
		u32 vlvf = rd32(E1000_VLVF(i));
		u32 vfta_mask, vid, vfta;

		/* हटाओ the vf from the pool */
		अगर (!(vlvf & vlvf_mask))
			जारी;

		/* clear out bit from VLVF */
		vlvf ^= vlvf_mask;

		/* अगर other pools are present, just हटाओ ourselves */
		अगर (vlvf & pool_mask)
			जाओ update_vlvfb;

		/* अगर PF is present, leave VFTA */
		अगर (vlvf & E1000_VLVF_POOLSEL_MASK)
			जाओ update_vlvf;

		vid = vlvf & E1000_VLVF_VLANID_MASK;
		vfta_mask = BIT(vid % 32);

		/* clear bit from VFTA */
		vfta = adapter->shaकरोw_vfta[vid / 32];
		अगर (vfta & vfta_mask)
			hw->mac.ops.ग_लिखो_vfta(hw, vid / 32, vfta ^ vfta_mask);
update_vlvf:
		/* clear pool selection enable */
		अगर (adapter->flags & IGB_FLAG_VLAN_PROMISC)
			vlvf &= E1000_VLVF_POOLSEL_MASK;
		अन्यथा
			vlvf = 0;
update_vlvfb:
		/* clear pool bits */
		wr32(E1000_VLVF(i), vlvf);
	पूर्ण
पूर्ण

अटल पूर्णांक igb_find_vlvf_entry(काष्ठा e1000_hw *hw, u32 vlan)
अणु
	u32 vlvf;
	पूर्णांक idx;

	/* लघु cut the special हाल */
	अगर (vlan == 0)
		वापस 0;

	/* Search क्रम the VLAN id in the VLVF entries */
	क्रम (idx = E1000_VLVF_ARRAY_SIZE; --idx;) अणु
		vlvf = rd32(E1000_VLVF(idx));
		अगर ((vlvf & VLAN_VID_MASK) == vlan)
			अवरोध;
	पूर्ण

	वापस idx;
पूर्ण

अटल व्योम igb_update_pf_vlvf(काष्ठा igb_adapter *adapter, u32 vid)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 bits, pf_id;
	पूर्णांक idx;

	idx = igb_find_vlvf_entry(hw, vid);
	अगर (!idx)
		वापस;

	/* See अगर any other pools are set क्रम this VLAN filter
	 * entry other than the PF.
	 */
	pf_id = adapter->vfs_allocated_count + E1000_VLVF_POOLSEL_SHIFT;
	bits = ~BIT(pf_id) & E1000_VLVF_POOLSEL_MASK;
	bits &= rd32(E1000_VLVF(idx));

	/* Disable the filter so this falls पूर्णांकo the शेष pool. */
	अगर (!bits) अणु
		अगर (adapter->flags & IGB_FLAG_VLAN_PROMISC)
			wr32(E1000_VLVF(idx), BIT(pf_id));
		अन्यथा
			wr32(E1000_VLVF(idx), 0);
	पूर्ण
पूर्ण

अटल s32 igb_set_vf_vlan(काष्ठा igb_adapter *adapter, u32 vid,
			   bool add, u32 vf)
अणु
	पूर्णांक pf_id = adapter->vfs_allocated_count;
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक err;

	/* If VLAN overlaps with one the PF is currently monitoring make
	 * sure that we are able to allocate a VLVF entry.  This may be
	 * redundant but it guarantees PF will मुख्यtain visibility to
	 * the VLAN.
	 */
	अगर (add && test_bit(vid, adapter->active_vlans)) अणु
		err = igb_vfta_set(hw, vid, pf_id, true, false);
		अगर (err)
			वापस err;
	पूर्ण

	err = igb_vfta_set(hw, vid, vf, add, false);

	अगर (add && !err)
		वापस err;

	/* If we failed to add the VF VLAN or we are removing the VF VLAN
	 * we may need to drop the PF pool bit in order to allow us to मुक्त
	 * up the VLVF resources.
	 */
	अगर (test_bit(vid, adapter->active_vlans) ||
	    (adapter->flags & IGB_FLAG_VLAN_PROMISC))
		igb_update_pf_vlvf(adapter, vid);

	वापस err;
पूर्ण

अटल व्योम igb_set_vmvir(काष्ठा igb_adapter *adapter, u32 vid, u32 vf)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (vid)
		wr32(E1000_VMVIR(vf), (vid | E1000_VMVIR_VLANA_DEFAULT));
	अन्यथा
		wr32(E1000_VMVIR(vf), 0);
पूर्ण

अटल पूर्णांक igb_enable_port_vlan(काष्ठा igb_adapter *adapter, पूर्णांक vf,
				u16 vlan, u8 qos)
अणु
	पूर्णांक err;

	err = igb_set_vf_vlan(adapter, vlan, true, vf);
	अगर (err)
		वापस err;

	igb_set_vmvir(adapter, vlan | (qos << VLAN_PRIO_SHIFT), vf);
	igb_set_vmolr(adapter, vf, !vlan);

	/* revoke access to previous VLAN */
	अगर (vlan != adapter->vf_data[vf].pf_vlan)
		igb_set_vf_vlan(adapter, adapter->vf_data[vf].pf_vlan,
				false, vf);

	adapter->vf_data[vf].pf_vlan = vlan;
	adapter->vf_data[vf].pf_qos = qos;
	igb_set_vf_vlan_strip(adapter, vf, true);
	dev_info(&adapter->pdev->dev,
		 "Setting VLAN %d, QOS 0x%x on VF %d\n", vlan, qos, vf);
	अगर (test_bit(__IGB_DOWN, &adapter->state)) अणु
		dev_warn(&adapter->pdev->dev,
			 "The VF VLAN has been set, but the PF device is not up.\n");
		dev_warn(&adapter->pdev->dev,
			 "Bring the PF device up before attempting to use the VF device.\n");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक igb_disable_port_vlan(काष्ठा igb_adapter *adapter, पूर्णांक vf)
अणु
	/* Restore tagless access via VLAN 0 */
	igb_set_vf_vlan(adapter, 0, true, vf);

	igb_set_vmvir(adapter, 0, vf);
	igb_set_vmolr(adapter, vf, true);

	/* Remove any PF asचिन्हित VLAN */
	अगर (adapter->vf_data[vf].pf_vlan)
		igb_set_vf_vlan(adapter, adapter->vf_data[vf].pf_vlan,
				false, vf);

	adapter->vf_data[vf].pf_vlan = 0;
	adapter->vf_data[vf].pf_qos = 0;
	igb_set_vf_vlan_strip(adapter, vf, false);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_nकरो_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf,
			       u16 vlan, u8 qos, __be16 vlan_proto)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	अगर ((vf >= adapter->vfs_allocated_count) || (vlan > 4095) || (qos > 7))
		वापस -EINVAL;

	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	वापस (vlan || qos) ? igb_enable_port_vlan(adapter, vf, vlan, qos) :
			       igb_disable_port_vlan(adapter, vf);
पूर्ण

अटल पूर्णांक igb_set_vf_vlan_msg(काष्ठा igb_adapter *adapter, u32 *msgbuf, u32 vf)
अणु
	पूर्णांक add = (msgbuf[0] & E1000_VT_MSGINFO_MASK) >> E1000_VT_MSGINFO_SHIFT;
	पूर्णांक vid = (msgbuf[1] & E1000_VLVF_VLANID_MASK);
	पूर्णांक ret;

	अगर (adapter->vf_data[vf].pf_vlan)
		वापस -1;

	/* VLAN 0 is a special हाल, करोn't allow it to be हटाओd */
	अगर (!vid && !add)
		वापस 0;

	ret = igb_set_vf_vlan(adapter, vid, !!add, vf);
	अगर (!ret)
		igb_set_vf_vlan_strip(adapter, vf, !!vid);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम igb_vf_reset(काष्ठा igb_adapter *adapter, u32 vf)
अणु
	काष्ठा vf_data_storage *vf_data = &adapter->vf_data[vf];

	/* clear flags - except flag that indicates PF has set the MAC */
	vf_data->flags &= IGB_VF_FLAG_PF_SET_MAC;
	vf_data->last_nack = jअगरfies;

	/* reset vlans क्रम device */
	igb_clear_vf_vfta(adapter, vf);
	igb_set_vf_vlan(adapter, vf_data->pf_vlan, true, vf);
	igb_set_vmvir(adapter, vf_data->pf_vlan |
			       (vf_data->pf_qos << VLAN_PRIO_SHIFT), vf);
	igb_set_vmolr(adapter, vf, !vf_data->pf_vlan);
	igb_set_vf_vlan_strip(adapter, vf, !!(vf_data->pf_vlan));

	/* reset multicast table array क्रम vf */
	adapter->vf_data[vf].num_vf_mc_hashes = 0;

	/* Flush and reset the mta with the new values */
	igb_set_rx_mode(adapter->netdev);
पूर्ण

अटल व्योम igb_vf_reset_event(काष्ठा igb_adapter *adapter, u32 vf)
अणु
	अचिन्हित अक्षर *vf_mac = adapter->vf_data[vf].vf_mac_addresses;

	/* clear mac address as we were hotplug हटाओd/added */
	अगर (!(adapter->vf_data[vf].flags & IGB_VF_FLAG_PF_SET_MAC))
		eth_zero_addr(vf_mac);

	/* process reमुख्यing reset events */
	igb_vf_reset(adapter, vf);
पूर्ण

अटल व्योम igb_vf_reset_msg(काष्ठा igb_adapter *adapter, u32 vf)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	अचिन्हित अक्षर *vf_mac = adapter->vf_data[vf].vf_mac_addresses;
	u32 reg, msgbuf[3];
	u8 *addr = (u8 *)(&msgbuf[1]);

	/* process all the same items cleared in a function level reset */
	igb_vf_reset(adapter, vf);

	/* set vf mac address */
	igb_set_vf_mac(adapter, vf, vf_mac);

	/* enable transmit and receive क्रम vf */
	reg = rd32(E1000_VFTE);
	wr32(E1000_VFTE, reg | BIT(vf));
	reg = rd32(E1000_VFRE);
	wr32(E1000_VFRE, reg | BIT(vf));

	adapter->vf_data[vf].flags |= IGB_VF_FLAG_CTS;

	/* reply to reset with ack and vf mac address */
	अगर (!is_zero_ether_addr(vf_mac)) अणु
		msgbuf[0] = E1000_VF_RESET | E1000_VT_MSGTYPE_ACK;
		स_नकल(addr, vf_mac, ETH_ALEN);
	पूर्ण अन्यथा अणु
		msgbuf[0] = E1000_VF_RESET | E1000_VT_MSGTYPE_NACK;
	पूर्ण
	igb_ग_लिखो_mbx(hw, msgbuf, 3, vf);
पूर्ण

अटल व्योम igb_flush_mac_table(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक i;

	क्रम (i = 0; i < hw->mac.rar_entry_count; i++) अणु
		adapter->mac_table[i].state &= ~IGB_MAC_STATE_IN_USE;
		eth_zero_addr(adapter->mac_table[i].addr);
		adapter->mac_table[i].queue = 0;
		igb_rar_set_index(adapter, i);
	पूर्ण
पूर्ण

अटल पूर्णांक igb_available_rars(काष्ठा igb_adapter *adapter, u8 queue)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	/* करो not count rar entries reserved क्रम VFs MAC addresses */
	पूर्णांक rar_entries = hw->mac.rar_entry_count -
			  adapter->vfs_allocated_count;
	पूर्णांक i, count = 0;

	क्रम (i = 0; i < rar_entries; i++) अणु
		/* करो not count शेष entries */
		अगर (adapter->mac_table[i].state & IGB_MAC_STATE_DEFAULT)
			जारी;

		/* करो not count "in use" entries क्रम dअगरferent queues */
		अगर ((adapter->mac_table[i].state & IGB_MAC_STATE_IN_USE) &&
		    (adapter->mac_table[i].queue != queue))
			जारी;

		count++;
	पूर्ण

	वापस count;
पूर्ण

/* Set शेष MAC address क्रम the PF in the first RAR entry */
अटल व्योम igb_set_शेष_mac_filter(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा igb_mac_addr *mac_table = &adapter->mac_table[0];

	ether_addr_copy(mac_table->addr, adapter->hw.mac.addr);
	mac_table->queue = adapter->vfs_allocated_count;
	mac_table->state = IGB_MAC_STATE_DEFAULT | IGB_MAC_STATE_IN_USE;

	igb_rar_set_index(adapter, 0);
पूर्ण

/* If the filter to be added and an alपढ़ोy existing filter express
 * the same address and address type, it should be possible to only
 * override the other configurations, क्रम example the queue to steer
 * traffic.
 */
अटल bool igb_mac_entry_can_be_used(स्थिर काष्ठा igb_mac_addr *entry,
				      स्थिर u8 *addr, स्थिर u8 flags)
अणु
	अगर (!(entry->state & IGB_MAC_STATE_IN_USE))
		वापस true;

	अगर ((entry->state & IGB_MAC_STATE_SRC_ADDR) !=
	    (flags & IGB_MAC_STATE_SRC_ADDR))
		वापस false;

	अगर (!ether_addr_equal(addr, entry->addr))
		वापस false;

	वापस true;
पूर्ण

/* Add a MAC filter क्रम 'addr' directing matching traffic to 'queue',
 * 'flags' is used to indicate what kind of match is made, match is by
 * शेष क्रम the destination address, अगर matching by source address
 * is desired the flag IGB_MAC_STATE_SRC_ADDR can be used.
 */
अटल पूर्णांक igb_add_mac_filter_flags(काष्ठा igb_adapter *adapter,
				    स्थिर u8 *addr, स्थिर u8 queue,
				    स्थिर u8 flags)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक rar_entries = hw->mac.rar_entry_count -
			  adapter->vfs_allocated_count;
	पूर्णांक i;

	अगर (is_zero_ether_addr(addr))
		वापस -EINVAL;

	/* Search क्रम the first empty entry in the MAC table.
	 * Do not touch entries at the end of the table reserved क्रम the VF MAC
	 * addresses.
	 */
	क्रम (i = 0; i < rar_entries; i++) अणु
		अगर (!igb_mac_entry_can_be_used(&adapter->mac_table[i],
					       addr, flags))
			जारी;

		ether_addr_copy(adapter->mac_table[i].addr, addr);
		adapter->mac_table[i].queue = queue;
		adapter->mac_table[i].state |= IGB_MAC_STATE_IN_USE | flags;

		igb_rar_set_index(adapter, i);
		वापस i;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक igb_add_mac_filter(काष्ठा igb_adapter *adapter, स्थिर u8 *addr,
			      स्थिर u8 queue)
अणु
	वापस igb_add_mac_filter_flags(adapter, addr, queue, 0);
पूर्ण

/* Remove a MAC filter क्रम 'addr' directing matching traffic to
 * 'queue', 'flags' is used to indicate what kind of match need to be
 * हटाओd, match is by शेष क्रम the destination address, अगर
 * matching by source address is to be हटाओd the flag
 * IGB_MAC_STATE_SRC_ADDR can be used.
 */
अटल पूर्णांक igb_del_mac_filter_flags(काष्ठा igb_adapter *adapter,
				    स्थिर u8 *addr, स्थिर u8 queue,
				    स्थिर u8 flags)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक rar_entries = hw->mac.rar_entry_count -
			  adapter->vfs_allocated_count;
	पूर्णांक i;

	अगर (is_zero_ether_addr(addr))
		वापस -EINVAL;

	/* Search क्रम matching entry in the MAC table based on given address
	 * and queue. Do not touch entries at the end of the table reserved
	 * क्रम the VF MAC addresses.
	 */
	क्रम (i = 0; i < rar_entries; i++) अणु
		अगर (!(adapter->mac_table[i].state & IGB_MAC_STATE_IN_USE))
			जारी;
		अगर ((adapter->mac_table[i].state & flags) != flags)
			जारी;
		अगर (adapter->mac_table[i].queue != queue)
			जारी;
		अगर (!ether_addr_equal(adapter->mac_table[i].addr, addr))
			जारी;

		/* When a filter क्रम the शेष address is "deleted",
		 * we वापस it to its initial configuration
		 */
		अगर (adapter->mac_table[i].state & IGB_MAC_STATE_DEFAULT) अणु
			adapter->mac_table[i].state =
				IGB_MAC_STATE_DEFAULT | IGB_MAC_STATE_IN_USE;
			adapter->mac_table[i].queue =
				adapter->vfs_allocated_count;
		पूर्ण अन्यथा अणु
			adapter->mac_table[i].state = 0;
			adapter->mac_table[i].queue = 0;
			eth_zero_addr(adapter->mac_table[i].addr);
		पूर्ण

		igb_rar_set_index(adapter, i);
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक igb_del_mac_filter(काष्ठा igb_adapter *adapter, स्थिर u8 *addr,
			      स्थिर u8 queue)
अणु
	वापस igb_del_mac_filter_flags(adapter, addr, queue, 0);
पूर्ण

पूर्णांक igb_add_mac_steering_filter(काष्ठा igb_adapter *adapter,
				स्थिर u8 *addr, u8 queue, u8 flags)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* In theory, this should be supported on 82575 as well, but
	 * that part wasn't easily accessible during development.
	 */
	अगर (hw->mac.type != e1000_i210)
		वापस -EOPNOTSUPP;

	वापस igb_add_mac_filter_flags(adapter, addr, queue,
					IGB_MAC_STATE_QUEUE_STEERING | flags);
पूर्ण

पूर्णांक igb_del_mac_steering_filter(काष्ठा igb_adapter *adapter,
				स्थिर u8 *addr, u8 queue, u8 flags)
अणु
	वापस igb_del_mac_filter_flags(adapter, addr, queue,
					IGB_MAC_STATE_QUEUE_STEERING | flags);
पूर्ण

अटल पूर्णांक igb_uc_sync(काष्ठा net_device *netdev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret;

	ret = igb_add_mac_filter(adapter, addr, adapter->vfs_allocated_count);

	वापस min_t(पूर्णांक, ret, 0);
पूर्ण

अटल पूर्णांक igb_uc_unsync(काष्ठा net_device *netdev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	igb_del_mac_filter(adapter, addr, adapter->vfs_allocated_count);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_set_vf_mac_filter(काष्ठा igb_adapter *adapter, स्थिर पूर्णांक vf,
				 स्थिर u32 info, स्थिर u8 *addr)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा vf_data_storage *vf_data = &adapter->vf_data[vf];
	काष्ठा list_head *pos;
	काष्ठा vf_mac_filter *entry = शून्य;
	पूर्णांक ret = 0;

	चयन (info) अणु
	हाल E1000_VF_MAC_FILTER_CLR:
		/* हटाओ all unicast MAC filters related to the current VF */
		list_क्रम_each(pos, &adapter->vf_macs.l) अणु
			entry = list_entry(pos, काष्ठा vf_mac_filter, l);
			अगर (entry->vf == vf) अणु
				entry->vf = -1;
				entry->मुक्त = true;
				igb_del_mac_filter(adapter, entry->vf_mac, vf);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल E1000_VF_MAC_FILTER_ADD:
		अगर ((vf_data->flags & IGB_VF_FLAG_PF_SET_MAC) &&
		    !vf_data->trusted) अणु
			dev_warn(&pdev->dev,
				 "VF %d requested MAC filter but is administratively denied\n",
				 vf);
			वापस -EINVAL;
		पूर्ण
		अगर (!is_valid_ether_addr(addr)) अणु
			dev_warn(&pdev->dev,
				 "VF %d attempted to set invalid MAC filter\n",
				 vf);
			वापस -EINVAL;
		पूर्ण

		/* try to find empty slot in the list */
		list_क्रम_each(pos, &adapter->vf_macs.l) अणु
			entry = list_entry(pos, काष्ठा vf_mac_filter, l);
			अगर (entry->मुक्त)
				अवरोध;
		पूर्ण

		अगर (entry && entry->मुक्त) अणु
			entry->मुक्त = false;
			entry->vf = vf;
			ether_addr_copy(entry->vf_mac, addr);

			ret = igb_add_mac_filter(adapter, addr, vf);
			ret = min_t(पूर्णांक, ret, 0);
		पूर्ण अन्यथा अणु
			ret = -ENOSPC;
		पूर्ण

		अगर (ret == -ENOSPC)
			dev_warn(&pdev->dev,
				 "VF %d has requested MAC filter but there is no space for it\n",
				 vf);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक igb_set_vf_mac_addr(काष्ठा igb_adapter *adapter, u32 *msg, पूर्णांक vf)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा vf_data_storage *vf_data = &adapter->vf_data[vf];
	u32 info = msg[0] & E1000_VT_MSGINFO_MASK;

	/* The VF MAC Address is stored in a packed array of bytes
	 * starting at the second 32 bit word of the msg array
	 */
	अचिन्हित अक्षर *addr = (अचिन्हित अक्षर *)&msg[1];
	पूर्णांक ret = 0;

	अगर (!info) अणु
		अगर ((vf_data->flags & IGB_VF_FLAG_PF_SET_MAC) &&
		    !vf_data->trusted) अणु
			dev_warn(&pdev->dev,
				 "VF %d attempted to override administratively set MAC address\nReload the VF driver to resume operations\n",
				 vf);
			वापस -EINVAL;
		पूर्ण

		अगर (!is_valid_ether_addr(addr)) अणु
			dev_warn(&pdev->dev,
				 "VF %d attempted to set invalid MAC\n",
				 vf);
			वापस -EINVAL;
		पूर्ण

		ret = igb_set_vf_mac(adapter, vf, addr);
	पूर्ण अन्यथा अणु
		ret = igb_set_vf_mac_filter(adapter, vf, info, addr);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम igb_rcv_ack_from_vf(काष्ठा igb_adapter *adapter, u32 vf)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा vf_data_storage *vf_data = &adapter->vf_data[vf];
	u32 msg = E1000_VT_MSGTYPE_NACK;

	/* अगर device isn't clear to send it shouldn't be पढ़ोing either */
	अगर (!(vf_data->flags & IGB_VF_FLAG_CTS) &&
	    समय_after(jअगरfies, vf_data->last_nack + (2 * HZ))) अणु
		igb_ग_लिखो_mbx(hw, &msg, 1, vf);
		vf_data->last_nack = jअगरfies;
	पूर्ण
पूर्ण

अटल व्योम igb_rcv_msg_from_vf(काष्ठा igb_adapter *adapter, u32 vf)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	u32 msgbuf[E1000_VFMAILBOX_SIZE];
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा vf_data_storage *vf_data = &adapter->vf_data[vf];
	s32 retval;

	retval = igb_पढ़ो_mbx(hw, msgbuf, E1000_VFMAILBOX_SIZE, vf, false);

	अगर (retval) अणु
		/* अगर receive failed revoke VF CTS stats and restart init */
		dev_err(&pdev->dev, "Error receiving message from VF\n");
		vf_data->flags &= ~IGB_VF_FLAG_CTS;
		अगर (!समय_after(jअगरfies, vf_data->last_nack + (2 * HZ)))
			जाओ unlock;
		जाओ out;
	पूर्ण

	/* this is a message we alपढ़ोy processed, करो nothing */
	अगर (msgbuf[0] & (E1000_VT_MSGTYPE_ACK | E1000_VT_MSGTYPE_NACK))
		जाओ unlock;

	/* until the vf completes a reset it should not be
	 * allowed to start any configuration.
	 */
	अगर (msgbuf[0] == E1000_VF_RESET) अणु
		/* unlocks mailbox */
		igb_vf_reset_msg(adapter, vf);
		वापस;
	पूर्ण

	अगर (!(vf_data->flags & IGB_VF_FLAG_CTS)) अणु
		अगर (!समय_after(jअगरfies, vf_data->last_nack + (2 * HZ)))
			जाओ unlock;
		retval = -1;
		जाओ out;
	पूर्ण

	चयन ((msgbuf[0] & 0xFFFF)) अणु
	हाल E1000_VF_SET_MAC_ADDR:
		retval = igb_set_vf_mac_addr(adapter, msgbuf, vf);
		अवरोध;
	हाल E1000_VF_SET_PROMISC:
		retval = igb_set_vf_promisc(adapter, msgbuf, vf);
		अवरोध;
	हाल E1000_VF_SET_MULTICAST:
		retval = igb_set_vf_multicasts(adapter, msgbuf, vf);
		अवरोध;
	हाल E1000_VF_SET_LPE:
		retval = igb_set_vf_rlpml(adapter, msgbuf[1], vf);
		अवरोध;
	हाल E1000_VF_SET_VLAN:
		retval = -1;
		अगर (vf_data->pf_vlan)
			dev_warn(&pdev->dev,
				 "VF %d attempted to override administratively set VLAN tag\nReload the VF driver to resume operations\n",
				 vf);
		अन्यथा
			retval = igb_set_vf_vlan_msg(adapter, msgbuf, vf);
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unhandled Msg %08x\n", msgbuf[0]);
		retval = -1;
		अवरोध;
	पूर्ण

	msgbuf[0] |= E1000_VT_MSGTYPE_CTS;
out:
	/* notअगरy the VF of the results of what it sent us */
	अगर (retval)
		msgbuf[0] |= E1000_VT_MSGTYPE_NACK;
	अन्यथा
		msgbuf[0] |= E1000_VT_MSGTYPE_ACK;

	/* unlocks mailbox */
	igb_ग_लिखो_mbx(hw, msgbuf, 1, vf);
	वापस;

unlock:
	igb_unlock_mbx(hw, vf);
पूर्ण

अटल व्योम igb_msg_task(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 vf;

	क्रम (vf = 0; vf < adapter->vfs_allocated_count; vf++) अणु
		/* process any reset requests */
		अगर (!igb_check_क्रम_rst(hw, vf))
			igb_vf_reset_event(adapter, vf);

		/* process any messages pending */
		अगर (!igb_check_क्रम_msg(hw, vf))
			igb_rcv_msg_from_vf(adapter, vf);

		/* process any acks */
		अगर (!igb_check_क्रम_ack(hw, vf))
			igb_rcv_ack_from_vf(adapter, vf);
	पूर्ण
पूर्ण

/**
 *  igb_set_uta - Set unicast filter table address
 *  @adapter: board निजी काष्ठाure
 *  @set: boolean indicating अगर we are setting or clearing bits
 *
 *  The unicast table address is a रेजिस्टर array of 32-bit रेजिस्टरs.
 *  The table is meant to be used in a way similar to how the MTA is used
 *  however due to certain limitations in the hardware it is necessary to
 *  set all the hash bits to 1 and use the VMOLR ROPE bit as a promiscuous
 *  enable bit to allow vlan tag stripping when promiscuous mode is enabled
 **/
अटल व्योम igb_set_uta(काष्ठा igb_adapter *adapter, bool set)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 uta = set ? ~0 : 0;
	पूर्णांक i;

	/* we only need to करो this अगर VMDq is enabled */
	अगर (!adapter->vfs_allocated_count)
		वापस;

	क्रम (i = hw->mac.uta_reg_count; i--;)
		array_wr32(E1000_UTA, i, uta);
पूर्ण

/**
 *  igb_पूर्णांकr_msi - Interrupt Handler
 *  @irq: पूर्णांकerrupt number
 *  @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 **/
अटल irqवापस_t igb_पूर्णांकr_msi(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा igb_adapter *adapter = data;
	काष्ठा igb_q_vector *q_vector = adapter->q_vector[0];
	काष्ठा e1000_hw *hw = &adapter->hw;
	/* पढ़ो ICR disables पूर्णांकerrupts using IAM */
	u32 icr = rd32(E1000_ICR);

	igb_ग_लिखो_itr(q_vector);

	अगर (icr & E1000_ICR_DRSTA)
		schedule_work(&adapter->reset_task);

	अगर (icr & E1000_ICR_DOUTSYNC) अणु
		/* HW is reporting DMA is out of sync */
		adapter->stats.करोosync++;
	पूर्ण

	अगर (icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC)) अणु
		hw->mac.get_link_status = 1;
		अगर (!test_bit(__IGB_DOWN, &adapter->state))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);
	पूर्ण

	अगर (icr & E1000_ICR_TS)
		igb_tsync_पूर्णांकerrupt(adapter);

	napi_schedule(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 *  igb_पूर्णांकr - Legacy Interrupt Handler
 *  @irq: पूर्णांकerrupt number
 *  @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 **/
अटल irqवापस_t igb_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा igb_adapter *adapter = data;
	काष्ठा igb_q_vector *q_vector = adapter->q_vector[0];
	काष्ठा e1000_hw *hw = &adapter->hw;
	/* Interrupt Auto-Mask...upon पढ़ोing ICR, पूर्णांकerrupts are masked.  No
	 * need क्रम the IMC ग_लिखो
	 */
	u32 icr = rd32(E1000_ICR);

	/* IMS will not स्वतः-mask अगर INT_ASSERTED is not set, and अगर it is
	 * not set, then the adapter didn't send an पूर्णांकerrupt
	 */
	अगर (!(icr & E1000_ICR_INT_ASSERTED))
		वापस IRQ_NONE;

	igb_ग_लिखो_itr(q_vector);

	अगर (icr & E1000_ICR_DRSTA)
		schedule_work(&adapter->reset_task);

	अगर (icr & E1000_ICR_DOUTSYNC) अणु
		/* HW is reporting DMA is out of sync */
		adapter->stats.करोosync++;
	पूर्ण

	अगर (icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC)) अणु
		hw->mac.get_link_status = 1;
		/* guard against पूर्णांकerrupt when we're going करोwn */
		अगर (!test_bit(__IGB_DOWN, &adapter->state))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);
	पूर्ण

	अगर (icr & E1000_ICR_TS)
		igb_tsync_पूर्णांकerrupt(adapter);

	napi_schedule(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम igb_ring_irq_enable(काष्ठा igb_q_vector *q_vector)
अणु
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर ((q_vector->rx.ring && (adapter->rx_itr_setting & 3)) ||
	    (!q_vector->rx.ring && (adapter->tx_itr_setting & 3))) अणु
		अगर ((adapter->num_q_vectors == 1) && !adapter->vf_data)
			igb_set_itr(q_vector);
		अन्यथा
			igb_update_ring_itr(q_vector);
	पूर्ण

	अगर (!test_bit(__IGB_DOWN, &adapter->state)) अणु
		अगर (adapter->flags & IGB_FLAG_HAS_MSIX)
			wr32(E1000_EIMS, q_vector->eims_value);
		अन्यथा
			igb_irq_enable(adapter);
	पूर्ण
पूर्ण

/**
 *  igb_poll - NAPI Rx polling callback
 *  @napi: napi polling काष्ठाure
 *  @budget: count of how many packets we should handle
 **/
अटल पूर्णांक igb_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा igb_q_vector *q_vector = container_of(napi,
						     काष्ठा igb_q_vector,
						     napi);
	bool clean_complete = true;
	पूर्णांक work_करोne = 0;

#अगर_घोषित CONFIG_IGB_DCA
	अगर (q_vector->adapter->flags & IGB_FLAG_DCA_ENABLED)
		igb_update_dca(q_vector);
#पूर्ण_अगर
	अगर (q_vector->tx.ring)
		clean_complete = igb_clean_tx_irq(q_vector, budget);

	अगर (q_vector->rx.ring) अणु
		पूर्णांक cleaned = igb_clean_rx_irq(q_vector, budget);

		work_करोne += cleaned;
		अगर (cleaned >= budget)
			clean_complete = false;
	पूर्ण

	/* If all work not completed, वापस budget and keep polling */
	अगर (!clean_complete)
		वापस budget;

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne)))
		igb_ring_irq_enable(q_vector);

	वापस min(work_करोne, budget - 1);
पूर्ण

/**
 *  igb_clean_tx_irq - Reclaim resources after transmit completes
 *  @q_vector: poपूर्णांकer to q_vector containing needed info
 *  @napi_budget: Used to determine अगर we are in netpoll
 *
 *  वापसs true अगर ring is completely cleaned
 **/
अटल bool igb_clean_tx_irq(काष्ठा igb_q_vector *q_vector, पूर्णांक napi_budget)
अणु
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	काष्ठा igb_ring *tx_ring = q_vector->tx.ring;
	काष्ठा igb_tx_buffer *tx_buffer;
	जोड़ e1000_adv_tx_desc *tx_desc;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	अचिन्हित पूर्णांक budget = q_vector->tx.work_limit;
	अचिन्हित पूर्णांक i = tx_ring->next_to_clean;

	अगर (test_bit(__IGB_DOWN, &adapter->state))
		वापस true;

	tx_buffer = &tx_ring->tx_buffer_info[i];
	tx_desc = IGB_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	करो अणु
		जोड़ e1000_adv_tx_desc *eop_desc = tx_buffer->next_to_watch;

		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		/* अगर DD is not set pending work has not been completed */
		अगर (!(eop_desc->wb.status & cpu_to_le32(E1000_TXD_STAT_DD)))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buffer->next_to_watch = शून्य;

		/* update the statistics क्रम this packet */
		total_bytes += tx_buffer->bytecount;
		total_packets += tx_buffer->gso_segs;

		/* मुक्त the skb */
		अगर (tx_buffer->type == IGB_TYPE_SKB)
			napi_consume_skb(tx_buffer->skb, napi_budget);
		अन्यथा
			xdp_वापस_frame(tx_buffer->xdpf);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		dma_unmap_len_set(tx_buffer, len, 0);

		/* clear last DMA location and unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buffer++;
			tx_desc++;
			i++;
			अगर (unlikely(!i)) अणु
				i -= tx_ring->count;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IGB_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buffer, len)) अणु
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
				dma_unmap_len_set(tx_buffer, len, 0);
			पूर्ण
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buffer++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buffer = tx_ring->tx_buffer_info;
			tx_desc = IGB_TX_DESC(tx_ring, 0);
		पूर्ण

		/* issue prefetch क्रम next Tx descriptor */
		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	पूर्ण जबतक (likely(budget));

	netdev_tx_completed_queue(txring_txq(tx_ring),
				  total_packets, total_bytes);
	i += tx_ring->count;
	tx_ring->next_to_clean = i;
	u64_stats_update_begin(&tx_ring->tx_syncp);
	tx_ring->tx_stats.bytes += total_bytes;
	tx_ring->tx_stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->tx_syncp);
	q_vector->tx.total_bytes += total_bytes;
	q_vector->tx.total_packets += total_packets;

	अगर (test_bit(IGB_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags)) अणु
		काष्ठा e1000_hw *hw = &adapter->hw;

		/* Detect a transmit hang in hardware, this serializes the
		 * check with the clearing of समय_stamp and movement of i
		 */
		clear_bit(IGB_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags);
		अगर (tx_buffer->next_to_watch &&
		    समय_after(jअगरfies, tx_buffer->समय_stamp +
			       (adapter->tx_समयout_factor * HZ)) &&
		    !(rd32(E1000_STATUS) & E1000_STATUS_TXOFF)) अणु

			/* detected Tx unit hang */
			dev_err(tx_ring->dev,
				"Detected Tx Unit Hang\n"
				"  Tx Queue             <%d>\n"
				"  TDH                  <%x>\n"
				"  TDT                  <%x>\n"
				"  next_to_use          <%x>\n"
				"  next_to_clean        <%x>\n"
				"buffer_info[next_to_clean]\n"
				"  time_stamp           <%lx>\n"
				"  next_to_watch        <%p>\n"
				"  jiffies              <%lx>\n"
				"  desc.status          <%x>\n",
				tx_ring->queue_index,
				rd32(E1000_TDH(tx_ring->reg_idx)),
				पढ़ोl(tx_ring->tail),
				tx_ring->next_to_use,
				tx_ring->next_to_clean,
				tx_buffer->समय_stamp,
				tx_buffer->next_to_watch,
				jअगरfies,
				tx_buffer->next_to_watch->wb.status);
			netअगर_stop_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);

			/* we are about to reset, no poपूर्णांक in enabling stuff */
			वापस true;
		पूर्ण
	पूर्ण

#घोषणा TX_WAKE_THRESHOLD (DESC_NEEDED * 2)
	अगर (unlikely(total_packets &&
	    netअगर_carrier_ok(tx_ring->netdev) &&
	    igb_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD)) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (__netअगर_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		    !(test_bit(__IGB_DOWN, &adapter->state))) अणु
			netअगर_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);

			u64_stats_update_begin(&tx_ring->tx_syncp);
			tx_ring->tx_stats.restart_queue++;
			u64_stats_update_end(&tx_ring->tx_syncp);
		पूर्ण
	पूर्ण

	वापस !!budget;
पूर्ण

/**
 *  igb_reuse_rx_page - page flip buffer and store it back on the ring
 *  @rx_ring: rx descriptor ring to store buffers on
 *  @old_buff: करोnor buffer to have page reused
 *
 *  Synchronizes page क्रम reuse by the adapter
 **/
अटल व्योम igb_reuse_rx_page(काष्ठा igb_ring *rx_ring,
			      काष्ठा igb_rx_buffer *old_buff)
अणु
	काष्ठा igb_rx_buffer *new_buff;
	u16 nta = rx_ring->next_to_alloc;

	new_buff = &rx_ring->rx_buffer_info[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* Transfer page from old buffer to new buffer.
	 * Move each member inभागidually to aव्योम possible store
	 * क्रमwarding stalls.
	 */
	new_buff->dma		= old_buff->dma;
	new_buff->page		= old_buff->page;
	new_buff->page_offset	= old_buff->page_offset;
	new_buff->pagecnt_bias	= old_buff->pagecnt_bias;
पूर्ण

अटल bool igb_can_reuse_rx_page(काष्ठा igb_rx_buffer *rx_buffer,
				  पूर्णांक rx_buf_pgcnt)
अणु
	अचिन्हित पूर्णांक pagecnt_bias = rx_buffer->pagecnt_bias;
	काष्ठा page *page = rx_buffer->page;

	/* aव्योम re-using remote and pfmeदो_स्मृति pages */
	अगर (!dev_page_is_reusable(page))
		वापस false;

#अगर (PAGE_SIZE < 8192)
	/* अगर we are only owner of page we can reuse it */
	अगर (unlikely((rx_buf_pgcnt - pagecnt_bias) > 1))
		वापस false;
#अन्यथा
#घोषणा IGB_LAST_OFFSET \
	(SKB_WITH_OVERHEAD(PAGE_SIZE) - IGB_RXBUFFER_2048)

	अगर (rx_buffer->page_offset > IGB_LAST_OFFSET)
		वापस false;
#पूर्ण_अगर

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	अगर (unlikely(pagecnt_bias == 1)) अणु
		page_ref_add(page, अच_लघु_उच्च - 1);
		rx_buffer->pagecnt_bias = अच_लघु_उच्च;
	पूर्ण

	वापस true;
पूर्ण

/**
 *  igb_add_rx_frag - Add contents of Rx buffer to sk_buff
 *  @rx_ring: rx descriptor ring to transact packets on
 *  @rx_buffer: buffer containing page to add
 *  @skb: sk_buff to place the data पूर्णांकo
 *  @size: size of buffer to be added
 *
 *  This function will add the data contained in rx_buffer->page to the skb.
 **/
अटल व्योम igb_add_rx_frag(काष्ठा igb_ring *rx_ring,
			    काष्ठा igb_rx_buffer *rx_buffer,
			    काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक size)
अणु
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = igb_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = ring_uses_build_skb(rx_ring) ?
				SKB_DATA_ALIGN(IGB_SKB_PAD + size) :
				SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_buffer->page,
			rx_buffer->page_offset, size, truesize);
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा sk_buff *igb_स्थिरruct_skb(काष्ठा igb_ring *rx_ring,
					 काष्ठा igb_rx_buffer *rx_buffer,
					 काष्ठा xdp_buff *xdp,
					 kसमय_प्रकार बारtamp)
अणु
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = igb_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(xdp->data_end -
					       xdp->data_hard_start);
#पूर्ण_अगर
	अचिन्हित पूर्णांक size = xdp->data_end - xdp->data;
	अचिन्हित पूर्णांक headlen;
	काष्ठा sk_buff *skb;

	/* prefetch first cache line of first page */
	net_prefetch(xdp->data);

	/* allocate a skb to store the frags */
	skb = napi_alloc_skb(&rx_ring->q_vector->napi, IGB_RX_HDR_LEN);
	अगर (unlikely(!skb))
		वापस शून्य;

	अगर (बारtamp)
		skb_hwtstamps(skb)->hwtstamp = बारtamp;

	/* Determine available headroom क्रम copy */
	headlen = size;
	अगर (headlen > IGB_RX_HDR_LEN)
		headlen = eth_get_headlen(skb->dev, xdp->data, IGB_RX_HDR_LEN);

	/* align pull length to size of दीर्घ to optimize स_नकल perक्रमmance */
	स_नकल(__skb_put(skb, headlen), xdp->data, ALIGN(headlen, माप(दीर्घ)));

	/* update all of the poपूर्णांकers */
	size -= headlen;
	अगर (size) अणु
		skb_add_rx_frag(skb, 0, rx_buffer->page,
				(xdp->data + headlen) - page_address(rx_buffer->page),
				size, truesize);
#अगर (PAGE_SIZE < 8192)
		rx_buffer->page_offset ^= truesize;
#अन्यथा
		rx_buffer->page_offset += truesize;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		rx_buffer->pagecnt_bias++;
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *igb_build_skb(काष्ठा igb_ring *rx_ring,
				     काष्ठा igb_rx_buffer *rx_buffer,
				     काष्ठा xdp_buff *xdp,
				     kसमय_प्रकार बारtamp)
अणु
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = igb_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) +
				SKB_DATA_ALIGN(xdp->data_end -
					       xdp->data_hard_start);
#पूर्ण_अगर
	अचिन्हित पूर्णांक metasize = xdp->data - xdp->data_meta;
	काष्ठा sk_buff *skb;

	/* prefetch first cache line of first page */
	net_prefetch(xdp->data_meta);

	/* build an skb around the page buffer */
	skb = build_skb(xdp->data_hard_start, truesize);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* update poपूर्णांकers within the skb to store the data */
	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	__skb_put(skb, xdp->data_end - xdp->data);

	अगर (metasize)
		skb_metadata_set(skb, metasize);

	अगर (बारtamp)
		skb_hwtstamps(skb)->hwtstamp = बारtamp;

	/* update buffer offset */
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *igb_run_xdp(काष्ठा igb_adapter *adapter,
				   काष्ठा igb_ring *rx_ring,
				   काष्ठा xdp_buff *xdp)
अणु
	पूर्णांक err, result = IGB_XDP_PASS;
	काष्ठा bpf_prog *xdp_prog;
	u32 act;

	rcu_पढ़ो_lock();
	xdp_prog = READ_ONCE(rx_ring->xdp_prog);

	अगर (!xdp_prog)
		जाओ xdp_out;

	prefetchw(xdp->data_hard_start); /* xdp_frame ग_लिखो */

	act = bpf_prog_run_xdp(xdp_prog, xdp);
	चयन (act) अणु
	हाल XDP_PASS:
		अवरोध;
	हाल XDP_TX:
		result = igb_xdp_xmit_back(adapter, xdp);
		अगर (result == IGB_XDP_CONSUMED)
			जाओ out_failure;
		अवरोध;
	हाल XDP_REसूचीECT:
		err = xdp_करो_redirect(adapter->netdev, xdp, xdp_prog);
		अगर (err)
			जाओ out_failure;
		result = IGB_XDP_REसूची;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
out_failure:
		trace_xdp_exception(rx_ring->netdev, xdp_prog, act);
		fallthrough;
	हाल XDP_DROP:
		result = IGB_XDP_CONSUMED;
		अवरोध;
	पूर्ण
xdp_out:
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-result);
पूर्ण

अटल अचिन्हित पूर्णांक igb_rx_frame_truesize(काष्ठा igb_ring *rx_ring,
					  अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize;

#अगर (PAGE_SIZE < 8192)
	truesize = igb_rx_pg_size(rx_ring) / 2; /* Must be घातer-of-2 */
#अन्यथा
	truesize = ring_uses_build_skb(rx_ring) ?
		SKB_DATA_ALIGN(IGB_SKB_PAD + size) +
		SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) :
		SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	वापस truesize;
पूर्ण

अटल व्योम igb_rx_buffer_flip(काष्ठा igb_ring *rx_ring,
			       काष्ठा igb_rx_buffer *rx_buffer,
			       अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize = igb_rx_frame_truesize(rx_ring, size);
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम igb_rx_checksum(काष्ठा igb_ring *ring,
				   जोड़ e1000_adv_rx_desc *rx_desc,
				   काष्ठा sk_buff *skb)
अणु
	skb_checksum_none_निश्चित(skb);

	/* Ignore Checksum bit is set */
	अगर (igb_test_staterr(rx_desc, E1000_RXD_STAT_IXSM))
		वापस;

	/* Rx checksum disabled via ethtool */
	अगर (!(ring->netdev->features & NETIF_F_RXCSUM))
		वापस;

	/* TCP/UDP checksum error bit is set */
	अगर (igb_test_staterr(rx_desc,
			     E1000_RXDEXT_STATERR_TCPE |
			     E1000_RXDEXT_STATERR_IPE)) अणु
		/* work around errata with sctp packets where the TCPE aka
		 * L4E bit is set incorrectly on 64 byte (60 byte w/o crc)
		 * packets, (aka let the stack check the crc32c)
		 */
		अगर (!((skb->len == 60) &&
		      test_bit(IGB_RING_FLAG_RX_SCTP_CSUM, &ring->flags))) अणु
			u64_stats_update_begin(&ring->rx_syncp);
			ring->rx_stats.csum_err++;
			u64_stats_update_end(&ring->rx_syncp);
		पूर्ण
		/* let the stack verअगरy checksum errors */
		वापस;
	पूर्ण
	/* It must be a TCP or UDP packet with a valid checksum */
	अगर (igb_test_staterr(rx_desc, E1000_RXD_STAT_TCPCS |
				      E1000_RXD_STAT_UDPCS))
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	dev_dbg(ring->dev, "cksum success: bits %08X\n",
		le32_to_cpu(rx_desc->wb.upper.status_error));
पूर्ण

अटल अंतरभूत व्योम igb_rx_hash(काष्ठा igb_ring *ring,
			       जोड़ e1000_adv_rx_desc *rx_desc,
			       काष्ठा sk_buff *skb)
अणु
	अगर (ring->netdev->features & NETIF_F_RXHASH)
		skb_set_hash(skb,
			     le32_to_cpu(rx_desc->wb.lower.hi_dword.rss),
			     PKT_HASH_TYPE_L3);
पूर्ण

/**
 *  igb_is_non_eop - process handling of non-EOP buffers
 *  @rx_ring: Rx ring being processed
 *  @rx_desc: Rx descriptor क्रम current buffer
 *
 *  This function updates next to clean.  If the buffer is an EOP buffer
 *  this function निकासs वापसing false, otherwise it will place the
 *  sk_buff in the next buffer to be chained and वापस true indicating
 *  that this is in fact a non-EOP buffer.
 **/
अटल bool igb_is_non_eop(काष्ठा igb_ring *rx_ring,
			   जोड़ e1000_adv_rx_desc *rx_desc)
अणु
	u32 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(IGB_RX_DESC(rx_ring, ntc));

	अगर (likely(igb_test_staterr(rx_desc, E1000_RXD_STAT_EOP)))
		वापस false;

	वापस true;
पूर्ण

/**
 *  igb_cleanup_headers - Correct corrupted or empty headers
 *  @rx_ring: rx descriptor ring packet is being transacted on
 *  @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 *  @skb: poपूर्णांकer to current skb being fixed
 *
 *  Address the हाल where we are pulling data in on pages only
 *  and as such no data is present in the skb header.
 *
 *  In addition अगर skb is not at least 60 bytes we need to pad it so that
 *  it is large enough to qualअगरy as a valid Ethernet frame.
 *
 *  Returns true अगर an error was encountered and skb was मुक्तd.
 **/
अटल bool igb_cleanup_headers(काष्ठा igb_ring *rx_ring,
				जोड़ e1000_adv_rx_desc *rx_desc,
				काष्ठा sk_buff *skb)
अणु
	/* XDP packets use error poपूर्णांकer so पात at this poपूर्णांक */
	अगर (IS_ERR(skb))
		वापस true;

	अगर (unlikely((igb_test_staterr(rx_desc,
				       E1000_RXDEXT_ERR_FRAME_ERR_MASK)))) अणु
		काष्ठा net_device *netdev = rx_ring->netdev;
		अगर (!(netdev->features & NETIF_F_RXALL)) अणु
			dev_kमुक्त_skb_any(skb);
			वापस true;
		पूर्ण
	पूर्ण

	/* अगर eth_skb_pad वापसs an error the skb was मुक्तd */
	अगर (eth_skb_pad(skb))
		वापस true;

	वापस false;
पूर्ण

/**
 *  igb_process_skb_fields - Populate skb header fields from Rx descriptor
 *  @rx_ring: rx descriptor ring packet is being transacted on
 *  @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 *  @skb: poपूर्णांकer to current skb being populated
 *
 *  This function checks the ring, descriptor, and packet inक्रमmation in
 *  order to populate the hash, checksum, VLAN, बारtamp, protocol, and
 *  other fields within the skb.
 **/
अटल व्योम igb_process_skb_fields(काष्ठा igb_ring *rx_ring,
				   जोड़ e1000_adv_rx_desc *rx_desc,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = rx_ring->netdev;

	igb_rx_hash(rx_ring, rx_desc, skb);

	igb_rx_checksum(rx_ring, rx_desc, skb);

	अगर (igb_test_staterr(rx_desc, E1000_RXDADV_STAT_TS) &&
	    !igb_test_staterr(rx_desc, E1000_RXDADV_STAT_TSIP))
		igb_ptp_rx_rgtstamp(rx_ring->q_vector, skb);

	अगर ((dev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    igb_test_staterr(rx_desc, E1000_RXD_STAT_VP)) अणु
		u16 vid;

		अगर (igb_test_staterr(rx_desc, E1000_RXDEXT_STATERR_LB) &&
		    test_bit(IGB_RING_FLAG_RX_LB_VLAN_BSWAP, &rx_ring->flags))
			vid = be16_to_cpu(rx_desc->wb.upper.vlan);
		अन्यथा
			vid = le16_to_cpu(rx_desc->wb.upper.vlan);

		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	पूर्ण

	skb_record_rx_queue(skb, rx_ring->queue_index);

	skb->protocol = eth_type_trans(skb, rx_ring->netdev);
पूर्ण

अटल अचिन्हित पूर्णांक igb_rx_offset(काष्ठा igb_ring *rx_ring)
अणु
	वापस ring_uses_build_skb(rx_ring) ? IGB_SKB_PAD : 0;
पूर्ण

अटल काष्ठा igb_rx_buffer *igb_get_rx_buffer(काष्ठा igb_ring *rx_ring,
					       स्थिर अचिन्हित पूर्णांक size, पूर्णांक *rx_buf_pgcnt)
अणु
	काष्ठा igb_rx_buffer *rx_buffer;

	rx_buffer = &rx_ring->rx_buffer_info[rx_ring->next_to_clean];
	*rx_buf_pgcnt =
#अगर (PAGE_SIZE < 8192)
		page_count(rx_buffer->page);
#अन्यथा
		0;
#पूर्ण_अगर
	prefetchw(rx_buffer->page);

	/* we are reusing so sync this buffer क्रम CPU use */
	dma_sync_single_range_क्रम_cpu(rx_ring->dev,
				      rx_buffer->dma,
				      rx_buffer->page_offset,
				      size,
				      DMA_FROM_DEVICE);

	rx_buffer->pagecnt_bias--;

	वापस rx_buffer;
पूर्ण

अटल व्योम igb_put_rx_buffer(काष्ठा igb_ring *rx_ring,
			      काष्ठा igb_rx_buffer *rx_buffer, पूर्णांक rx_buf_pgcnt)
अणु
	अगर (igb_can_reuse_rx_page(rx_buffer, rx_buf_pgcnt)) अणु
		/* hand second half of page back to the ring */
		igb_reuse_rx_page(rx_ring, rx_buffer);
	पूर्ण अन्यथा अणु
		/* We are not reusing the buffer so unmap it and मुक्त
		 * any references we are holding to it
		 */
		dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
				     igb_rx_pg_size(rx_ring), DMA_FROM_DEVICE,
				     IGB_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
	पूर्ण

	/* clear contents of rx_buffer */
	rx_buffer->page = शून्य;
पूर्ण

अटल पूर्णांक igb_clean_rx_irq(काष्ठा igb_q_vector *q_vector, स्थिर पूर्णांक budget)
अणु
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	काष्ठा igb_ring *rx_ring = q_vector->rx.ring;
	काष्ठा sk_buff *skb = rx_ring->skb;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	u16 cleaned_count = igb_desc_unused(rx_ring);
	अचिन्हित पूर्णांक xdp_xmit = 0;
	काष्ठा xdp_buff xdp;
	u32 frame_sz = 0;
	पूर्णांक rx_buf_pgcnt;

	/* Frame size depend on rx_ring setup when PAGE_SIZE=4K */
#अगर (PAGE_SIZE < 8192)
	frame_sz = igb_rx_frame_truesize(rx_ring, 0);
#पूर्ण_अगर
	xdp_init_buff(&xdp, frame_sz, &rx_ring->xdp_rxq);

	जबतक (likely(total_packets < budget)) अणु
		जोड़ e1000_adv_rx_desc *rx_desc;
		काष्ठा igb_rx_buffer *rx_buffer;
		kसमय_प्रकार बारtamp = 0;
		पूर्णांक pkt_offset = 0;
		अचिन्हित पूर्णांक size;
		व्योम *pktbuf;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= IGB_RX_BUFFER_WRITE) अणु
			igb_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		rx_desc = IGB_RX_DESC(rx_ring, rx_ring->next_to_clean);
		size = le16_to_cpu(rx_desc->wb.upper.length);
		अगर (!size)
			अवरोध;

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we know the
		 * descriptor has been written back
		 */
		dma_rmb();

		rx_buffer = igb_get_rx_buffer(rx_ring, size, &rx_buf_pgcnt);
		pktbuf = page_address(rx_buffer->page) + rx_buffer->page_offset;

		/* pull rx packet बारtamp अगर available and valid */
		अगर (igb_test_staterr(rx_desc, E1000_RXDADV_STAT_TSIP)) अणु
			पूर्णांक ts_hdr_len;

			ts_hdr_len = igb_ptp_rx_pktstamp(rx_ring->q_vector,
							 pktbuf, &बारtamp);

			pkt_offset += ts_hdr_len;
			size -= ts_hdr_len;
		पूर्ण

		/* retrieve a buffer from the ring */
		अगर (!skb) अणु
			अचिन्हित अक्षर *hard_start = pktbuf - igb_rx_offset(rx_ring);
			अचिन्हित पूर्णांक offset = pkt_offset + igb_rx_offset(rx_ring);

			xdp_prepare_buff(&xdp, hard_start, offset, size, true);
#अगर (PAGE_SIZE > 4096)
			/* At larger PAGE_SIZE, frame_sz depend on len size */
			xdp.frame_sz = igb_rx_frame_truesize(rx_ring, size);
#पूर्ण_अगर
			skb = igb_run_xdp(adapter, rx_ring, &xdp);
		पूर्ण

		अगर (IS_ERR(skb)) अणु
			अचिन्हित पूर्णांक xdp_res = -PTR_ERR(skb);

			अगर (xdp_res & (IGB_XDP_TX | IGB_XDP_REसूची)) अणु
				xdp_xmit |= xdp_res;
				igb_rx_buffer_flip(rx_ring, rx_buffer, size);
			पूर्ण अन्यथा अणु
				rx_buffer->pagecnt_bias++;
			पूर्ण
			total_packets++;
			total_bytes += size;
		पूर्ण अन्यथा अगर (skb)
			igb_add_rx_frag(rx_ring, rx_buffer, skb, size);
		अन्यथा अगर (ring_uses_build_skb(rx_ring))
			skb = igb_build_skb(rx_ring, rx_buffer, &xdp,
					    बारtamp);
		अन्यथा
			skb = igb_स्थिरruct_skb(rx_ring, rx_buffer,
						&xdp, बारtamp);

		/* निकास अगर we failed to retrieve a buffer */
		अगर (!skb) अणु
			rx_ring->rx_stats.alloc_failed++;
			rx_buffer->pagecnt_bias++;
			अवरोध;
		पूर्ण

		igb_put_rx_buffer(rx_ring, rx_buffer, rx_buf_pgcnt);
		cleaned_count++;

		/* fetch next buffer in frame अगर non-eop */
		अगर (igb_is_non_eop(rx_ring, rx_desc))
			जारी;

		/* verअगरy the packet layout is correct */
		अगर (igb_cleanup_headers(rx_ring, rx_desc, skb)) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		/* probably a little skewed due to removing CRC */
		total_bytes += skb->len;

		/* populate checksum, बारtamp, VLAN, and protocol */
		igb_process_skb_fields(rx_ring, rx_desc, skb);

		napi_gro_receive(&q_vector->napi, skb);

		/* reset skb poपूर्णांकer */
		skb = शून्य;

		/* update budget accounting */
		total_packets++;
	पूर्ण

	/* place incomplete frames back on ring क्रम completion */
	rx_ring->skb = skb;

	अगर (xdp_xmit & IGB_XDP_REसूची)
		xdp_करो_flush();

	अगर (xdp_xmit & IGB_XDP_TX) अणु
		काष्ठा igb_ring *tx_ring = igb_xdp_tx_queue_mapping(adapter);

		igb_xdp_ring_update_tail(tx_ring);
	पूर्ण

	u64_stats_update_begin(&rx_ring->rx_syncp);
	rx_ring->rx_stats.packets += total_packets;
	rx_ring->rx_stats.bytes += total_bytes;
	u64_stats_update_end(&rx_ring->rx_syncp);
	q_vector->rx.total_packets += total_packets;
	q_vector->rx.total_bytes += total_bytes;

	अगर (cleaned_count)
		igb_alloc_rx_buffers(rx_ring, cleaned_count);

	वापस total_packets;
पूर्ण

अटल bool igb_alloc_mapped_page(काष्ठा igb_ring *rx_ring,
				  काष्ठा igb_rx_buffer *bi)
अणु
	काष्ठा page *page = bi->page;
	dma_addr_t dma;

	/* since we are recycling buffers we should selकरोm need to alloc */
	अगर (likely(page))
		वापस true;

	/* alloc new page क्रम storage */
	page = dev_alloc_pages(igb_rx_pg_order(rx_ring));
	अगर (unlikely(!page)) अणु
		rx_ring->rx_stats.alloc_failed++;
		वापस false;
	पूर्ण

	/* map page क्रम use */
	dma = dma_map_page_attrs(rx_ring->dev, page, 0,
				 igb_rx_pg_size(rx_ring),
				 DMA_FROM_DEVICE,
				 IGB_RX_DMA_ATTR);

	/* अगर mapping failed मुक्त memory back to प्रणाली since
	 * there isn't much point in holding memory we can't use
	 */
	अगर (dma_mapping_error(rx_ring->dev, dma)) अणु
		__मुक्त_pages(page, igb_rx_pg_order(rx_ring));

		rx_ring->rx_stats.alloc_failed++;
		वापस false;
	पूर्ण

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = igb_rx_offset(rx_ring);
	page_ref_add(page, अच_लघु_उच्च - 1);
	bi->pagecnt_bias = अच_लघु_उच्च;

	वापस true;
पूर्ण

/**
 *  igb_alloc_rx_buffers - Replace used receive buffers
 *  @rx_ring: rx descriptor ring to allocate new receive buffers
 *  @cleaned_count: count of buffers to allocate
 **/
व्योम igb_alloc_rx_buffers(काष्ठा igb_ring *rx_ring, u16 cleaned_count)
अणु
	जोड़ e1000_adv_rx_desc *rx_desc;
	काष्ठा igb_rx_buffer *bi;
	u16 i = rx_ring->next_to_use;
	u16 bufsz;

	/* nothing to करो */
	अगर (!cleaned_count)
		वापस;

	rx_desc = IGB_RX_DESC(rx_ring, i);
	bi = &rx_ring->rx_buffer_info[i];
	i -= rx_ring->count;

	bufsz = igb_rx_bufsz(rx_ring);

	करो अणु
		अगर (!igb_alloc_mapped_page(rx_ring, bi))
			अवरोध;

		/* sync the buffer क्रम use by the device */
		dma_sync_single_range_क्रम_device(rx_ring->dev, bi->dma,
						 bi->page_offset, bufsz,
						 DMA_FROM_DEVICE);

		/* Refresh the desc even अगर buffer_addrs didn't change
		 * because each ग_लिखो-back erases this info.
		 */
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		i++;
		अगर (unlikely(!i)) अणु
			rx_desc = IGB_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_buffer_info;
			i -= rx_ring->count;
		पूर्ण

		/* clear the length क्रम the next_to_use descriptor */
		rx_desc->wb.upper.length = 0;

		cleaned_count--;
	पूर्ण जबतक (cleaned_count);

	i += rx_ring->count;

	अगर (rx_ring->next_to_use != i) अणु
		/* record the next descriptor to use */
		rx_ring->next_to_use = i;

		/* update next to alloc since we have filled the ring */
		rx_ring->next_to_alloc = i;

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		dma_wmb();
		ग_लिखोl(i, rx_ring->tail);
	पूर्ण
पूर्ण

/**
 * igb_mii_ioctl -
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @अगरr: पूर्णांकerface काष्ठाure
 * @cmd: ioctl command to execute
 **/
अटल पूर्णांक igb_mii_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);

	अगर (adapter->hw.phy.media_type != e1000_media_type_copper)
		वापस -EOPNOTSUPP;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = adapter->hw.phy.addr;
		अवरोध;
	हाल SIOCGMIIREG:
		अगर (igb_पढ़ो_phy_reg(&adapter->hw, data->reg_num & 0x1F,
				     &data->val_out))
			वापस -EIO;
		अवरोध;
	हाल SIOCSMIIREG:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * igb_ioctl -
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @अगरr: पूर्णांकerface काष्ठाure
 * @cmd: ioctl command to execute
 **/
अटल पूर्णांक igb_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		वापस igb_mii_ioctl(netdev, अगरr, cmd);
	हाल SIOCGHWTSTAMP:
		वापस igb_ptp_get_ts_config(netdev, अगरr);
	हाल SIOCSHWTSTAMP:
		वापस igb_ptp_set_ts_config(netdev, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

व्योम igb_पढ़ो_pci_cfg(काष्ठा e1000_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा igb_adapter *adapter = hw->back;

	pci_पढ़ो_config_word(adapter->pdev, reg, value);
पूर्ण

व्योम igb_ग_लिखो_pci_cfg(काष्ठा e1000_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा igb_adapter *adapter = hw->back;

	pci_ग_लिखो_config_word(adapter->pdev, reg, *value);
पूर्ण

s32 igb_पढ़ो_pcie_cap_reg(काष्ठा e1000_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा igb_adapter *adapter = hw->back;

	अगर (pcie_capability_पढ़ो_word(adapter->pdev, reg, value))
		वापस -E1000_ERR_CONFIG;

	वापस 0;
पूर्ण

s32 igb_ग_लिखो_pcie_cap_reg(काष्ठा e1000_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा igb_adapter *adapter = hw->back;

	अगर (pcie_capability_ग_लिखो_word(adapter->pdev, reg, *value))
		वापस -E1000_ERR_CONFIG;

	वापस 0;
पूर्ण

अटल व्योम igb_vlan_mode(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl, rctl;
	bool enable = !!(features & NETIF_F_HW_VLAN_CTAG_RX);

	अगर (enable) अणु
		/* enable VLAN tag insert/strip */
		ctrl = rd32(E1000_CTRL);
		ctrl |= E1000_CTRL_VME;
		wr32(E1000_CTRL, ctrl);

		/* Disable CFI check */
		rctl = rd32(E1000_RCTL);
		rctl &= ~E1000_RCTL_CFIEN;
		wr32(E1000_RCTL, rctl);
	पूर्ण अन्यथा अणु
		/* disable VLAN tag insert/strip */
		ctrl = rd32(E1000_CTRL);
		ctrl &= ~E1000_CTRL_VME;
		wr32(E1000_CTRL, ctrl);
	पूर्ण

	igb_set_vf_vlan_strip(adapter, adapter->vfs_allocated_count, enable);
पूर्ण

अटल पूर्णांक igb_vlan_rx_add_vid(काष्ठा net_device *netdev,
			       __be16 proto, u16 vid)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक pf_id = adapter->vfs_allocated_count;

	/* add the filter since PF can receive vlans w/o entry in vlvf */
	अगर (!vid || !(adapter->flags & IGB_FLAG_VLAN_PROMISC))
		igb_vfta_set(hw, vid, pf_id, true, !!vid);

	set_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				__be16 proto, u16 vid)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	पूर्णांक pf_id = adapter->vfs_allocated_count;
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* हटाओ VID from filter table */
	अगर (vid && !(adapter->flags & IGB_FLAG_VLAN_PROMISC))
		igb_vfta_set(hw, vid, pf_id, false, true);

	clear_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण

अटल व्योम igb_restore_vlan(काष्ठा igb_adapter *adapter)
अणु
	u16 vid = 1;

	igb_vlan_mode(adapter->netdev, adapter->netdev->features);
	igb_vlan_rx_add_vid(adapter->netdev, htons(ETH_P_8021Q), 0);

	क्रम_each_set_bit_from(vid, adapter->active_vlans, VLAN_N_VID)
		igb_vlan_rx_add_vid(adapter->netdev, htons(ETH_P_8021Q), vid);
पूर्ण

पूर्णांक igb_set_spd_dplx(काष्ठा igb_adapter *adapter, u32 spd, u8 dplx)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_mac_info *mac = &adapter->hw.mac;

	mac->स्वतःneg = 0;

	/* Make sure dplx is at most 1 bit and lsb of speed is not set
	 * क्रम the चयन() below to work
	 */
	अगर ((spd & 1) || (dplx & ~1))
		जाओ err_inval;

	/* Fiber NIC's only allow 1000 gbps Full duplex
	 * and 100Mbps Full duplex क्रम 100baseFx sfp
	 */
	अगर (adapter->hw.phy.media_type == e1000_media_type_पूर्णांकernal_serdes) अणु
		चयन (spd + dplx) अणु
		हाल SPEED_10 + DUPLEX_HALF:
		हाल SPEED_10 + DUPLEX_FULL:
		हाल SPEED_100 + DUPLEX_HALF:
			जाओ err_inval;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (spd + dplx) अणु
	हाल SPEED_10 + DUPLEX_HALF:
		mac->क्रमced_speed_duplex = ADVERTISE_10_HALF;
		अवरोध;
	हाल SPEED_10 + DUPLEX_FULL:
		mac->क्रमced_speed_duplex = ADVERTISE_10_FULL;
		अवरोध;
	हाल SPEED_100 + DUPLEX_HALF:
		mac->क्रमced_speed_duplex = ADVERTISE_100_HALF;
		अवरोध;
	हाल SPEED_100 + DUPLEX_FULL:
		mac->क्रमced_speed_duplex = ADVERTISE_100_FULL;
		अवरोध;
	हाल SPEED_1000 + DUPLEX_FULL:
		mac->स्वतःneg = 1;
		adapter->hw.phy.स्वतःneg_advertised = ADVERTISE_1000_FULL;
		अवरोध;
	हाल SPEED_1000 + DUPLEX_HALF: /* not supported */
	शेष:
		जाओ err_inval;
	पूर्ण

	/* clear MDI, MDI(-X) override is only allowed when स्वतःneg enabled */
	adapter->hw.phy.mdix = AUTO_ALL_MODES;

	वापस 0;

err_inval:
	dev_err(&pdev->dev, "Unsupported Speed/Duplex configuration\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __igb_shutकरोwn(काष्ठा pci_dev *pdev, bool *enable_wake,
			  bool runसमय)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl, rctl, status;
	u32 wufc = runसमय ? E1000_WUFC_LNKC : adapter->wol;
	bool wake;

	rtnl_lock();
	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev))
		__igb_बंद(netdev, true);

	igb_ptp_suspend(adapter);

	igb_clear_पूर्णांकerrupt_scheme(adapter);
	rtnl_unlock();

	status = rd32(E1000_STATUS);
	अगर (status & E1000_STATUS_LU)
		wufc &= ~E1000_WUFC_LNKC;

	अगर (wufc) अणु
		igb_setup_rctl(adapter);
		igb_set_rx_mode(netdev);

		/* turn on all-multi mode अगर wake on multicast is enabled */
		अगर (wufc & E1000_WUFC_MC) अणु
			rctl = rd32(E1000_RCTL);
			rctl |= E1000_RCTL_MPE;
			wr32(E1000_RCTL, rctl);
		पूर्ण

		ctrl = rd32(E1000_CTRL);
		ctrl |= E1000_CTRL_ADVD3WUC;
		wr32(E1000_CTRL, ctrl);

		/* Allow समय क्रम pending master requests to run */
		igb_disable_pcie_master(hw);

		wr32(E1000_WUC, E1000_WUC_PME_EN);
		wr32(E1000_WUFC, wufc);
	पूर्ण अन्यथा अणु
		wr32(E1000_WUC, 0);
		wr32(E1000_WUFC, 0);
	पूर्ण

	wake = wufc || adapter->en_mng_pt;
	अगर (!wake)
		igb_घातer_करोwn_link(adapter);
	अन्यथा
		igb_घातer_up_link(adapter);

	अगर (enable_wake)
		*enable_wake = wake;

	/* Release control of h/w to f/w.  If f/w is AMT enabled, this
	 * would have alपढ़ोy happened in बंद and is redundant.
	 */
	igb_release_hw_control(adapter);

	pci_disable_device(pdev);

	वापस 0;
पूर्ण

अटल व्योम igb_deliver_wake_packet(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा sk_buff *skb;
	u32 wupl;

	wupl = rd32(E1000_WUPL) & E1000_WUPL_MASK;

	/* WUPM stores only the first 128 bytes of the wake packet.
	 * Read the packet only अगर we have the whole thing.
	 */
	अगर ((wupl == 0) || (wupl > E1000_WUPM_BYTES))
		वापस;

	skb = netdev_alloc_skb_ip_align(netdev, E1000_WUPM_BYTES);
	अगर (!skb)
		वापस;

	skb_put(skb, wupl);

	/* Ensure पढ़ोs are 32-bit aligned */
	wupl = roundup(wupl, 4);

	स_नकल_fromio(skb->data, hw->hw_addr + E1000_WUPM_REG(0), wupl);

	skb->protocol = eth_type_trans(skb, netdev);
	netअगर_rx(skb);
पूर्ण

अटल पूर्णांक __maybe_unused igb_suspend(काष्ठा device *dev)
अणु
	वापस __igb_shutकरोwn(to_pci_dev(dev), शून्य, 0);
पूर्ण

अटल पूर्णांक __maybe_unused igb_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 err, val;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	अगर (!pci_device_is_present(pdev))
		वापस -ENODEV;
	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"igb: Cannot enable PCI device from suspend\n");
		वापस err;
	पूर्ण
	pci_set_master(pdev);

	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_enable_wake(pdev, PCI_D3cold, 0);

	अगर (igb_init_पूर्णांकerrupt_scheme(adapter, true)) अणु
		dev_err(&pdev->dev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण

	igb_reset(adapter);

	/* let the f/w know that the h/w is now under the control of the
	 * driver.
	 */
	igb_get_hw_control(adapter);

	val = rd32(E1000_WUS);
	अगर (val & WAKE_PKT_WUS)
		igb_deliver_wake_packet(netdev);

	wr32(E1000_WUS, ~0);

	rtnl_lock();
	अगर (!err && netअगर_running(netdev))
		err = __igb_खोलो(netdev, true);

	अगर (!err)
		netअगर_device_attach(netdev);
	rtnl_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused igb_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	अगर (!igb_has_link(adapter))
		pm_schedule_suspend(dev, MSEC_PER_SEC * 5);

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक __maybe_unused igb_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस __igb_shutकरोwn(to_pci_dev(dev), शून्य, 1);
पूर्ण

अटल पूर्णांक __maybe_unused igb_runसमय_resume(काष्ठा device *dev)
अणु
	वापस igb_resume(dev);
पूर्ण

अटल व्योम igb_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	bool wake;

	__igb_shutकरोwn(pdev, &wake, 0);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, wake);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
अटल पूर्णांक igb_sriov_reinit(काष्ठा pci_dev *dev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(dev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;

	rtnl_lock();

	अगर (netअगर_running(netdev))
		igb_बंद(netdev);
	अन्यथा
		igb_reset(adapter);

	igb_clear_पूर्णांकerrupt_scheme(adapter);

	igb_init_queue_configuration(adapter);

	अगर (igb_init_पूर्णांकerrupt_scheme(adapter, true)) अणु
		rtnl_unlock();
		dev_err(&pdev->dev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (netअगर_running(netdev))
		igb_खोलो(netdev);

	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक igb_pci_disable_sriov(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err = igb_disable_sriov(dev);

	अगर (!err)
		err = igb_sriov_reinit(dev);

	वापस err;
पूर्ण

अटल पूर्णांक igb_pci_enable_sriov(काष्ठा pci_dev *dev, पूर्णांक num_vfs)
अणु
	पूर्णांक err = igb_enable_sriov(dev, num_vfs);

	अगर (err)
		जाओ out;

	err = igb_sriov_reinit(dev);
	अगर (!err)
		वापस num_vfs;

out:
	वापस err;
पूर्ण

#पूर्ण_अगर
अटल पूर्णांक igb_pci_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	अगर (num_vfs == 0)
		वापस igb_pci_disable_sriov(dev);
	अन्यथा
		वापस igb_pci_enable_sriov(dev, num_vfs);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 *  igb_io_error_detected - called when PCI error is detected
 *  @pdev: Poपूर्णांकer to PCI device
 *  @state: The current pci connection state
 *
 *  This function is called after a PCI bus error affecting
 *  this device has been detected.
 **/
अटल pci_ers_result_t igb_io_error_detected(काष्ठा pci_dev *pdev,
					      pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev))
		igb_करोwn(adapter);
	pci_disable_device(pdev);

	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 *  igb_io_slot_reset - called after the pci bus has been reset.
 *  @pdev: Poपूर्णांकer to PCI device
 *
 *  Restart the card from scratch, as अगर from a cold-boot. Implementation
 *  resembles the first-half of the igb_resume routine.
 **/
अटल pci_ers_result_t igb_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	pci_ers_result_t result;

	अगर (pci_enable_device_mem(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
		result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		pci_set_master(pdev);
		pci_restore_state(pdev);
		pci_save_state(pdev);

		pci_enable_wake(pdev, PCI_D3hot, 0);
		pci_enable_wake(pdev, PCI_D3cold, 0);

		/* In हाल of PCI error, adapter lose its HW address
		 * so we should re-assign it here.
		 */
		hw->hw_addr = adapter->io_addr;

		igb_reset(adapter);
		wr32(E1000_WUS, ~0);
		result = PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	वापस result;
पूर्ण

/**
 *  igb_io_resume - called when traffic can start flowing again.
 *  @pdev: Poपूर्णांकer to PCI device
 *
 *  This callback is called when the error recovery driver tells us that
 *  its OK to resume normal operation. Implementation resembles the
 *  second-half of the igb_resume routine.
 */
अटल व्योम igb_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev)) अणु
		अगर (igb_up(adapter)) अणु
			dev_err(&pdev->dev, "igb_up failed after reset\n");
			वापस;
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);

	/* let the f/w know that the h/w is now under the control of the
	 * driver.
	 */
	igb_get_hw_control(adapter);
पूर्ण

/**
 *  igb_rar_set_index - Sync RAL[index] and RAH[index] रेजिस्टरs with MAC table
 *  @adapter: Poपूर्णांकer to adapter काष्ठाure
 *  @index: Index of the RAR entry which need to be synced with MAC table
 **/
अटल व्योम igb_rar_set_index(काष्ठा igb_adapter *adapter, u32 index)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rar_low, rar_high;
	u8 *addr = adapter->mac_table[index].addr;

	/* HW expects these to be in network order when they are plugged
	 * पूर्णांकo the रेजिस्टरs which are little endian.  In order to guarantee
	 * that ordering we need to करो an leXX_to_cpup here in order to be
	 * पढ़ोy क्रम the byteswap that occurs with ग_लिखोl
	 */
	rar_low = le32_to_cpup((__le32 *)(addr));
	rar_high = le16_to_cpup((__le16 *)(addr + 4));

	/* Indicate to hardware the Address is Valid. */
	अगर (adapter->mac_table[index].state & IGB_MAC_STATE_IN_USE) अणु
		अगर (is_valid_ether_addr(addr))
			rar_high |= E1000_RAH_AV;

		अगर (adapter->mac_table[index].state & IGB_MAC_STATE_SRC_ADDR)
			rar_high |= E1000_RAH_ASEL_SRC_ADDR;

		चयन (hw->mac.type) अणु
		हाल e1000_82575:
		हाल e1000_i210:
			अगर (adapter->mac_table[index].state &
			    IGB_MAC_STATE_QUEUE_STEERING)
				rar_high |= E1000_RAH_QSEL_ENABLE;

			rar_high |= E1000_RAH_POOL_1 *
				    adapter->mac_table[index].queue;
			अवरोध;
		शेष:
			rar_high |= E1000_RAH_POOL_1 <<
				    adapter->mac_table[index].queue;
			अवरोध;
		पूर्ण
	पूर्ण

	wr32(E1000_RAL(index), rar_low);
	wrfl();
	wr32(E1000_RAH(index), rar_high);
	wrfl();
पूर्ण

अटल पूर्णांक igb_set_vf_mac(काष्ठा igb_adapter *adapter,
			  पूर्णांक vf, अचिन्हित अक्षर *mac_addr)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	/* VF MAC addresses start at end of receive addresses and moves
	 * towards the first, as a result a collision should not be possible
	 */
	पूर्णांक rar_entry = hw->mac.rar_entry_count - (vf + 1);
	अचिन्हित अक्षर *vf_mac_addr = adapter->vf_data[vf].vf_mac_addresses;

	ether_addr_copy(vf_mac_addr, mac_addr);
	ether_addr_copy(adapter->mac_table[rar_entry].addr, mac_addr);
	adapter->mac_table[rar_entry].queue = vf;
	adapter->mac_table[rar_entry].state |= IGB_MAC_STATE_IN_USE;
	igb_rar_set_index(adapter, rar_entry);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	अगर (vf >= adapter->vfs_allocated_count)
		वापस -EINVAL;

	/* Setting the VF MAC to 0 reverts the IGB_VF_FLAG_PF_SET_MAC
	 * flag and allows to overग_लिखो the MAC via VF netdev.  This
	 * is necessary to allow libvirt a way to restore the original
	 * MAC after unbinding vfio-pci and reloading igbvf after shutting
	 * करोwn a VM.
	 */
	अगर (is_zero_ether_addr(mac)) अणु
		adapter->vf_data[vf].flags &= ~IGB_VF_FLAG_PF_SET_MAC;
		dev_info(&adapter->pdev->dev,
			 "remove administratively set MAC on VF %d\n",
			 vf);
	पूर्ण अन्यथा अगर (is_valid_ether_addr(mac)) अणु
		adapter->vf_data[vf].flags |= IGB_VF_FLAG_PF_SET_MAC;
		dev_info(&adapter->pdev->dev, "setting MAC %pM on VF %d\n",
			 mac, vf);
		dev_info(&adapter->pdev->dev,
			 "Reload the VF driver to make this change effective.");
		/* Generate additional warning अगर PF is करोwn */
		अगर (test_bit(__IGB_DOWN, &adapter->state)) अणु
			dev_warn(&adapter->pdev->dev,
				 "The VF MAC address has been set, but the PF device is not up.\n");
			dev_warn(&adapter->pdev->dev,
				 "Bring the PF device up before attempting to use the VF device.\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस igb_set_vf_mac(adapter, vf, mac);
पूर्ण

अटल पूर्णांक igb_link_mbps(पूर्णांक पूर्णांकernal_link_speed)
अणु
	चयन (पूर्णांकernal_link_speed) अणु
	हाल SPEED_100:
		वापस 100;
	हाल SPEED_1000:
		वापस 1000;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम igb_set_vf_rate_limit(काष्ठा e1000_hw *hw, पूर्णांक vf, पूर्णांक tx_rate,
				  पूर्णांक link_speed)
अणु
	पूर्णांक rf_dec, rf_पूर्णांक;
	u32 bcnrc_val;

	अगर (tx_rate != 0) अणु
		/* Calculate the rate factor values to set */
		rf_पूर्णांक = link_speed / tx_rate;
		rf_dec = (link_speed - (rf_पूर्णांक * tx_rate));
		rf_dec = (rf_dec * BIT(E1000_RTTBCNRC_RF_INT_SHIFT)) /
			 tx_rate;

		bcnrc_val = E1000_RTTBCNRC_RS_ENA;
		bcnrc_val |= ((rf_पूर्णांक << E1000_RTTBCNRC_RF_INT_SHIFT) &
			      E1000_RTTBCNRC_RF_INT_MASK);
		bcnrc_val |= (rf_dec & E1000_RTTBCNRC_RF_DEC_MASK);
	पूर्ण अन्यथा अणु
		bcnrc_val = 0;
	पूर्ण

	wr32(E1000_RTTDQSEL, vf); /* vf X uses queue X */
	/* Set global transmit compensation समय to the MMW_SIZE in RTTBCNRM
	 * रेजिस्टर. MMW_SIZE=0x014 अगर 9728-byte jumbo is supported.
	 */
	wr32(E1000_RTTBCNRM, 0x14);
	wr32(E1000_RTTBCNRC, bcnrc_val);
पूर्ण

अटल व्योम igb_check_vf_rate_limit(काष्ठा igb_adapter *adapter)
अणु
	पूर्णांक actual_link_speed, i;
	bool reset_rate = false;

	/* VF TX rate limit was not set or not supported */
	अगर ((adapter->vf_rate_link_speed == 0) ||
	    (adapter->hw.mac.type != e1000_82576))
		वापस;

	actual_link_speed = igb_link_mbps(adapter->link_speed);
	अगर (actual_link_speed != adapter->vf_rate_link_speed) अणु
		reset_rate = true;
		adapter->vf_rate_link_speed = 0;
		dev_info(&adapter->pdev->dev,
			 "Link speed has been changed. VF Transmit rate is disabled\n");
	पूर्ण

	क्रम (i = 0; i < adapter->vfs_allocated_count; i++) अणु
		अगर (reset_rate)
			adapter->vf_data[i].tx_rate = 0;

		igb_set_vf_rate_limit(&adapter->hw, i,
				      adapter->vf_data[i].tx_rate,
				      actual_link_speed);
	पूर्ण
पूर्ण

अटल पूर्णांक igb_nकरो_set_vf_bw(काष्ठा net_device *netdev, पूर्णांक vf,
			     पूर्णांक min_tx_rate, पूर्णांक max_tx_rate)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक actual_link_speed;

	अगर (hw->mac.type != e1000_82576)
		वापस -EOPNOTSUPP;

	अगर (min_tx_rate)
		वापस -EINVAL;

	actual_link_speed = igb_link_mbps(adapter->link_speed);
	अगर ((vf >= adapter->vfs_allocated_count) ||
	    (!(rd32(E1000_STATUS) & E1000_STATUS_LU)) ||
	    (max_tx_rate < 0) ||
	    (max_tx_rate > actual_link_speed))
		वापस -EINVAL;

	adapter->vf_rate_link_speed = actual_link_speed;
	adapter->vf_data[vf].tx_rate = (u16)max_tx_rate;
	igb_set_vf_rate_limit(hw, vf, max_tx_rate, actual_link_speed);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_nकरो_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf,
				   bool setting)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 reg_val, reg_offset;

	अगर (!adapter->vfs_allocated_count)
		वापस -EOPNOTSUPP;

	अगर (vf >= adapter->vfs_allocated_count)
		वापस -EINVAL;

	reg_offset = (hw->mac.type == e1000_82576) ? E1000_DTXSWC : E1000_TXSWC;
	reg_val = rd32(reg_offset);
	अगर (setting)
		reg_val |= (BIT(vf) |
			    BIT(vf + E1000_DTXSWC_VLAN_SPOOF_SHIFT));
	अन्यथा
		reg_val &= ~(BIT(vf) |
			     BIT(vf + E1000_DTXSWC_VLAN_SPOOF_SHIFT));
	wr32(reg_offset, reg_val);

	adapter->vf_data[vf].spoofchk_enabled = setting;
	वापस 0;
पूर्ण

अटल पूर्णांक igb_nकरो_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf, bool setting)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	अगर (vf >= adapter->vfs_allocated_count)
		वापस -EINVAL;
	अगर (adapter->vf_data[vf].trusted == setting)
		वापस 0;

	adapter->vf_data[vf].trusted = setting;

	dev_info(&adapter->pdev->dev, "VF %u is %strusted\n",
		 vf, setting ? "" : "not ");
	वापस 0;
पूर्ण

अटल पूर्णांक igb_nकरो_get_vf_config(काष्ठा net_device *netdev,
				 पूर्णांक vf, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	अगर (vf >= adapter->vfs_allocated_count)
		वापस -EINVAL;
	ivi->vf = vf;
	स_नकल(&ivi->mac, adapter->vf_data[vf].vf_mac_addresses, ETH_ALEN);
	ivi->max_tx_rate = adapter->vf_data[vf].tx_rate;
	ivi->min_tx_rate = 0;
	ivi->vlan = adapter->vf_data[vf].pf_vlan;
	ivi->qos = adapter->vf_data[vf].pf_qos;
	ivi->spoofchk = adapter->vf_data[vf].spoofchk_enabled;
	ivi->trusted = adapter->vf_data[vf].trusted;
	वापस 0;
पूर्ण

अटल व्योम igb_vmm_control(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 reg;

	चयन (hw->mac.type) अणु
	हाल e1000_82575:
	हाल e1000_i210:
	हाल e1000_i211:
	हाल e1000_i354:
	शेष:
		/* replication is not supported क्रम 82575 */
		वापस;
	हाल e1000_82576:
		/* notअगरy HW that the MAC is adding vlan tags */
		reg = rd32(E1000_DTXCTL);
		reg |= E1000_DTXCTL_VLAN_ADDED;
		wr32(E1000_DTXCTL, reg);
		fallthrough;
	हाल e1000_82580:
		/* enable replication vlan tag stripping */
		reg = rd32(E1000_RPLOLR);
		reg |= E1000_RPLOLR_STRVLAN;
		wr32(E1000_RPLOLR, reg);
		fallthrough;
	हाल e1000_i350:
		/* none of the above रेजिस्टरs are supported by i350 */
		अवरोध;
	पूर्ण

	अगर (adapter->vfs_allocated_count) अणु
		igb_vmdq_set_loopback_pf(hw, true);
		igb_vmdq_set_replication_pf(hw, true);
		igb_vmdq_set_anti_spoofing_pf(hw, true,
					      adapter->vfs_allocated_count);
	पूर्ण अन्यथा अणु
		igb_vmdq_set_loopback_pf(hw, false);
		igb_vmdq_set_replication_pf(hw, false);
	पूर्ण
पूर्ण

अटल व्योम igb_init_dmac(काष्ठा igb_adapter *adapter, u32 pba)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 dmac_thr;
	u16 hwm;

	अगर (hw->mac.type > e1000_82580) अणु
		अगर (adapter->flags & IGB_FLAG_DMAC) अणु
			u32 reg;

			/* क्रमce threshold to 0. */
			wr32(E1000_DMCTXTH, 0);

			/* DMA Coalescing high water mark needs to be greater
			 * than the Rx threshold. Set hwm to PBA - max frame
			 * size in 16B units, capping it at PBA - 6KB.
			 */
			hwm = 64 * (pba - 6);
			reg = rd32(E1000_FCRTC);
			reg &= ~E1000_FCRTC_RTH_COAL_MASK;
			reg |= ((hwm << E1000_FCRTC_RTH_COAL_SHIFT)
				& E1000_FCRTC_RTH_COAL_MASK);
			wr32(E1000_FCRTC, reg);

			/* Set the DMA Coalescing Rx threshold to PBA - 2 * max
			 * frame size, capping it at PBA - 10KB.
			 */
			dmac_thr = pba - 10;
			reg = rd32(E1000_DMACR);
			reg &= ~E1000_DMACR_DMACTHR_MASK;
			reg |= ((dmac_thr << E1000_DMACR_DMACTHR_SHIFT)
				& E1000_DMACR_DMACTHR_MASK);

			/* transition to L0x or L1 अगर available..*/
			reg |= (E1000_DMACR_DMAC_EN | E1000_DMACR_DMAC_LX_MASK);

			/* watchकरोg समयr= +-1000 usec in 32usec पूर्णांकervals */
			reg |= (1000 >> 5);

			/* Disable BMC-to-OS Watchकरोg Enable */
			अगर (hw->mac.type != e1000_i354)
				reg &= ~E1000_DMACR_DC_BMC2OSW_EN;

			wr32(E1000_DMACR, reg);

			/* no lower threshold to disable
			 * coalescing(smart fअगरb)-UTRESH=0
			 */
			wr32(E1000_DMCRTRH, 0);

			reg = (IGB_DMCTLX_DCFLUSH_DIS | 0x4);

			wr32(E1000_DMCTLX, reg);

			/* मुक्त space in tx packet buffer to wake from
			 * DMA coal
			 */
			wr32(E1000_DMCTXTH, (IGB_MIN_TXPBSIZE -
			     (IGB_TX_BUF_4096 + adapter->max_frame_size)) >> 6);

			/* make low घातer state decision controlled
			 * by DMA coal
			 */
			reg = rd32(E1000_PCIEMISC);
			reg &= ~E1000_PCIEMISC_LX_DECISION;
			wr32(E1000_PCIEMISC, reg);
		पूर्ण /* endअगर adapter->dmac is not disabled */
	पूर्ण अन्यथा अगर (hw->mac.type == e1000_82580) अणु
		u32 reg = rd32(E1000_PCIEMISC);

		wr32(E1000_PCIEMISC, reg & ~E1000_PCIEMISC_LX_DECISION);
		wr32(E1000_DMACR, 0);
	पूर्ण
पूर्ण

/**
 *  igb_पढ़ो_i2c_byte - Reads 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to पढ़ो
 *  @dev_addr: device address
 *  @data: value पढ़ो
 *
 *  Perक्रमms byte पढ़ो operation over I2C पूर्णांकerface at
 *  a specअगरied device address.
 **/
s32 igb_पढ़ो_i2c_byte(काष्ठा e1000_hw *hw, u8 byte_offset,
		      u8 dev_addr, u8 *data)
अणु
	काष्ठा igb_adapter *adapter = container_of(hw, काष्ठा igb_adapter, hw);
	काष्ठा i2c_client *this_client = adapter->i2c_client;
	s32 status;
	u16 swfw_mask = 0;

	अगर (!this_client)
		वापस E1000_ERR_I2C;

	swfw_mask = E1000_SWFW_PHY0_SM;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, swfw_mask))
		वापस E1000_ERR_SWFW_SYNC;

	status = i2c_smbus_पढ़ो_byte_data(this_client, byte_offset);
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);

	अगर (status < 0)
		वापस E1000_ERR_I2C;
	अन्यथा अणु
		*data = status;
		वापस 0;
	पूर्ण
पूर्ण

/**
 *  igb_ग_लिखो_i2c_byte - Writes 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to ग_लिखो
 *  @dev_addr: device address
 *  @data: value to ग_लिखो
 *
 *  Perक्रमms byte ग_लिखो operation over I2C पूर्णांकerface at
 *  a specअगरied device address.
 **/
s32 igb_ग_लिखो_i2c_byte(काष्ठा e1000_hw *hw, u8 byte_offset,
		       u8 dev_addr, u8 data)
अणु
	काष्ठा igb_adapter *adapter = container_of(hw, काष्ठा igb_adapter, hw);
	काष्ठा i2c_client *this_client = adapter->i2c_client;
	s32 status;
	u16 swfw_mask = E1000_SWFW_PHY0_SM;

	अगर (!this_client)
		वापस E1000_ERR_I2C;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, swfw_mask))
		वापस E1000_ERR_SWFW_SYNC;
	status = i2c_smbus_ग_लिखो_byte_data(this_client, byte_offset, data);
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);

	अगर (status)
		वापस E1000_ERR_I2C;
	अन्यथा
		वापस 0;

पूर्ण

पूर्णांक igb_reinit_queues(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err = 0;

	अगर (netअगर_running(netdev))
		igb_बंद(netdev);

	igb_reset_पूर्णांकerrupt_capability(adapter);

	अगर (igb_init_पूर्णांकerrupt_scheme(adapter, true)) अणु
		dev_err(&pdev->dev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (netअगर_running(netdev))
		err = igb_खोलो(netdev);

	वापस err;
पूर्ण

अटल व्योम igb_nfc_filter_निकास(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा igb_nfc_filter *rule;

	spin_lock(&adapter->nfc_lock);

	hlist_क्रम_each_entry(rule, &adapter->nfc_filter_list, nfc_node)
		igb_erase_filter(adapter, rule);

	hlist_क्रम_each_entry(rule, &adapter->cls_flower_list, nfc_node)
		igb_erase_filter(adapter, rule);

	spin_unlock(&adapter->nfc_lock);
पूर्ण

अटल व्योम igb_nfc_filter_restore(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा igb_nfc_filter *rule;

	spin_lock(&adapter->nfc_lock);

	hlist_क्रम_each_entry(rule, &adapter->nfc_filter_list, nfc_node)
		igb_add_filter(adapter, rule);

	spin_unlock(&adapter->nfc_lock);
पूर्ण
/* igb_मुख्य.c */
