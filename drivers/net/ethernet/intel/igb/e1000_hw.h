<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000_IGB_HW_H_
#घोषणा _E1000_IGB_HW_H_

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>

#समावेश "e1000_regs.h"
#समावेश "e1000_defines.h"

काष्ठा e1000_hw;

#घोषणा E1000_DEV_ID_82576			0x10C9
#घोषणा E1000_DEV_ID_82576_FIBER		0x10E6
#घोषणा E1000_DEV_ID_82576_SERDES		0x10E7
#घोषणा E1000_DEV_ID_82576_QUAD_COPPER		0x10E8
#घोषणा E1000_DEV_ID_82576_QUAD_COPPER_ET2	0x1526
#घोषणा E1000_DEV_ID_82576_NS			0x150A
#घोषणा E1000_DEV_ID_82576_NS_SERDES		0x1518
#घोषणा E1000_DEV_ID_82576_SERDES_QUAD		0x150D
#घोषणा E1000_DEV_ID_82575EB_COPPER		0x10A7
#घोषणा E1000_DEV_ID_82575EB_FIBER_SERDES	0x10A9
#घोषणा E1000_DEV_ID_82575GB_QUAD_COPPER	0x10D6
#घोषणा E1000_DEV_ID_82580_COPPER		0x150E
#घोषणा E1000_DEV_ID_82580_FIBER		0x150F
#घोषणा E1000_DEV_ID_82580_SERDES		0x1510
#घोषणा E1000_DEV_ID_82580_SGMII		0x1511
#घोषणा E1000_DEV_ID_82580_COPPER_DUAL		0x1516
#घोषणा E1000_DEV_ID_82580_QUAD_FIBER		0x1527
#घोषणा E1000_DEV_ID_DH89XXCC_SGMII		0x0438
#घोषणा E1000_DEV_ID_DH89XXCC_SERDES		0x043A
#घोषणा E1000_DEV_ID_DH89XXCC_BACKPLANE		0x043C
#घोषणा E1000_DEV_ID_DH89XXCC_SFP		0x0440
#घोषणा E1000_DEV_ID_I350_COPPER		0x1521
#घोषणा E1000_DEV_ID_I350_FIBER			0x1522
#घोषणा E1000_DEV_ID_I350_SERDES		0x1523
#घोषणा E1000_DEV_ID_I350_SGMII			0x1524
#घोषणा E1000_DEV_ID_I210_COPPER		0x1533
#घोषणा E1000_DEV_ID_I210_FIBER			0x1536
#घोषणा E1000_DEV_ID_I210_SERDES		0x1537
#घोषणा E1000_DEV_ID_I210_SGMII			0x1538
#घोषणा E1000_DEV_ID_I210_COPPER_FLASHLESS	0x157B
#घोषणा E1000_DEV_ID_I210_SERDES_FLASHLESS	0x157C
#घोषणा E1000_DEV_ID_I211_COPPER		0x1539
#घोषणा E1000_DEV_ID_I354_BACKPLANE_1GBPS	0x1F40
#घोषणा E1000_DEV_ID_I354_SGMII			0x1F41
#घोषणा E1000_DEV_ID_I354_BACKPLANE_2_5GBPS	0x1F45

#घोषणा E1000_REVISION_2 2
#घोषणा E1000_REVISION_4 4

#घोषणा E1000_FUNC_0     0
#घोषणा E1000_FUNC_1     1
#घोषणा E1000_FUNC_2     2
#घोषणा E1000_FUNC_3     3

#घोषणा E1000_ALT_MAC_ADDRESS_OFFSET_LAN0   0
#घोषणा E1000_ALT_MAC_ADDRESS_OFFSET_LAN1   3
#घोषणा E1000_ALT_MAC_ADDRESS_OFFSET_LAN2   6
#घोषणा E1000_ALT_MAC_ADDRESS_OFFSET_LAN3   9

क्रमागत e1000_mac_type अणु
	e1000_undefined = 0,
	e1000_82575,
	e1000_82576,
	e1000_82580,
	e1000_i350,
	e1000_i354,
	e1000_i210,
	e1000_i211,
	e1000_num_macs  /* List is 1-based, so subtract 1 क्रम true count. */
पूर्ण;

क्रमागत e1000_media_type अणु
	e1000_media_type_unknown = 0,
	e1000_media_type_copper = 1,
	e1000_media_type_fiber = 2,
	e1000_media_type_पूर्णांकernal_serdes = 3,
	e1000_num_media_types
पूर्ण;

क्रमागत e1000_nvm_type अणु
	e1000_nvm_unknown = 0,
	e1000_nvm_none,
	e1000_nvm_eeprom_spi,
	e1000_nvm_flash_hw,
	e1000_nvm_invm,
	e1000_nvm_flash_sw
पूर्ण;

क्रमागत e1000_nvm_override अणु
	e1000_nvm_override_none = 0,
	e1000_nvm_override_spi_small,
	e1000_nvm_override_spi_large,
पूर्ण;

क्रमागत e1000_phy_type अणु
	e1000_phy_unknown = 0,
	e1000_phy_none,
	e1000_phy_m88,
	e1000_phy_igp,
	e1000_phy_igp_2,
	e1000_phy_gg82563,
	e1000_phy_igp_3,
	e1000_phy_अगरe,
	e1000_phy_82580,
	e1000_phy_i210,
	e1000_phy_bcm54616,
पूर्ण;

क्रमागत e1000_bus_type अणु
	e1000_bus_type_unknown = 0,
	e1000_bus_type_pci,
	e1000_bus_type_pcix,
	e1000_bus_type_pci_express,
	e1000_bus_type_reserved
पूर्ण;

क्रमागत e1000_bus_speed अणु
	e1000_bus_speed_unknown = 0,
	e1000_bus_speed_33,
	e1000_bus_speed_66,
	e1000_bus_speed_100,
	e1000_bus_speed_120,
	e1000_bus_speed_133,
	e1000_bus_speed_2500,
	e1000_bus_speed_5000,
	e1000_bus_speed_reserved
पूर्ण;

क्रमागत e1000_bus_width अणु
	e1000_bus_width_unknown = 0,
	e1000_bus_width_pcie_x1,
	e1000_bus_width_pcie_x2,
	e1000_bus_width_pcie_x4 = 4,
	e1000_bus_width_pcie_x8 = 8,
	e1000_bus_width_32,
	e1000_bus_width_64,
	e1000_bus_width_reserved
पूर्ण;

क्रमागत e1000_1000t_rx_status अणु
	e1000_1000t_rx_status_not_ok = 0,
	e1000_1000t_rx_status_ok,
	e1000_1000t_rx_status_undefined = 0xFF
पूर्ण;

क्रमागत e1000_rev_polarity अणु
	e1000_rev_polarity_normal = 0,
	e1000_rev_polarity_reversed,
	e1000_rev_polarity_undefined = 0xFF
पूर्ण;

क्रमागत e1000_fc_mode अणु
	e1000_fc_none = 0,
	e1000_fc_rx_छोड़ो,
	e1000_fc_tx_छोड़ो,
	e1000_fc_full,
	e1000_fc_शेष = 0xFF
पूर्ण;

/* Statistics counters collected by the MAC */
काष्ठा e1000_hw_stats अणु
	u64 crcerrs;
	u64 algnerrc;
	u64 symerrs;
	u64 rxerrc;
	u64 mpc;
	u64 scc;
	u64 ecol;
	u64 mcc;
	u64 latecol;
	u64 colc;
	u64 dc;
	u64 tncrs;
	u64 sec;
	u64 cexterr;
	u64 rlec;
	u64 xonrxc;
	u64 xontxc;
	u64 xoffrxc;
	u64 xofftxc;
	u64 fcruc;
	u64 prc64;
	u64 prc127;
	u64 prc255;
	u64 prc511;
	u64 prc1023;
	u64 prc1522;
	u64 gprc;
	u64 bprc;
	u64 mprc;
	u64 gptc;
	u64 gorc;
	u64 gotc;
	u64 rnbc;
	u64 ruc;
	u64 rfc;
	u64 roc;
	u64 rjc;
	u64 mgprc;
	u64 mgpdc;
	u64 mgptc;
	u64 tor;
	u64 tot;
	u64 tpr;
	u64 tpt;
	u64 ptc64;
	u64 ptc127;
	u64 ptc255;
	u64 ptc511;
	u64 ptc1023;
	u64 ptc1522;
	u64 mptc;
	u64 bptc;
	u64 tsctc;
	u64 tsctfc;
	u64 iac;
	u64 icrxptc;
	u64 icrxatc;
	u64 ictxptc;
	u64 ictxatc;
	u64 ictxqec;
	u64 ictxqmtc;
	u64 icrxdmtc;
	u64 icrxoc;
	u64 cbपंचांगpc;
	u64 htdpmc;
	u64 cbrdpc;
	u64 cbrmpc;
	u64 rpthc;
	u64 hgptc;
	u64 htcbdpc;
	u64 hgorc;
	u64 hgotc;
	u64 lenerrs;
	u64 scvpc;
	u64 hrmpc;
	u64 करोosync;
	u64 o2bgptc;
	u64 o2bspc;
	u64 b2ospc;
	u64 b2ogprc;
पूर्ण;

काष्ठा e1000_host_mng_dhcp_cookie अणु
	u32 signature;
	u8  status;
	u8  reserved0;
	u16 vlan_id;
	u32 reserved1;
	u16 reserved2;
	u8  reserved3;
	u8  checksum;
पूर्ण;

/* Host Interface "Rev 1" */
काष्ठा e1000_host_command_header अणु
	u8 command_id;
	u8 command_length;
	u8 command_options;
	u8 checksum;
पूर्ण;

#घोषणा E1000_HI_MAX_DATA_LENGTH     252
काष्ठा e1000_host_command_info अणु
	काष्ठा e1000_host_command_header command_header;
	u8 command_data[E1000_HI_MAX_DATA_LENGTH];
पूर्ण;

/* Host Interface "Rev 2" */
काष्ठा e1000_host_mng_command_header अणु
	u8  command_id;
	u8  checksum;
	u16 reserved1;
	u16 reserved2;
	u16 command_length;
पूर्ण;

#घोषणा E1000_HI_MAX_MNG_DATA_LENGTH 0x6F8
काष्ठा e1000_host_mng_command_info अणु
	काष्ठा e1000_host_mng_command_header command_header;
	u8 command_data[E1000_HI_MAX_MNG_DATA_LENGTH];
पूर्ण;

#समावेश "e1000_mac.h"
#समावेश "e1000_phy.h"
#समावेश "e1000_nvm.h"
#समावेश "e1000_mbx.h"

काष्ठा e1000_mac_operations अणु
	s32 (*check_क्रम_link)(काष्ठा e1000_hw *);
	s32 (*reset_hw)(काष्ठा e1000_hw *);
	s32 (*init_hw)(काष्ठा e1000_hw *);
	bool (*check_mng_mode)(काष्ठा e1000_hw *);
	s32 (*setup_physical_पूर्णांकerface)(काष्ठा e1000_hw *);
	व्योम (*rar_set)(काष्ठा e1000_hw *, u8 *, u32);
	s32 (*पढ़ो_mac_addr)(काष्ठा e1000_hw *);
	s32 (*get_speed_and_duplex)(काष्ठा e1000_hw *, u16 *, u16 *);
	s32 (*acquire_swfw_sync)(काष्ठा e1000_hw *, u16);
	व्योम (*release_swfw_sync)(काष्ठा e1000_hw *, u16);
#अगर_घोषित CONFIG_IGB_HWMON
	s32 (*get_thermal_sensor_data)(काष्ठा e1000_hw *);
	s32 (*init_thermal_sensor_thresh)(काष्ठा e1000_hw *);
#पूर्ण_अगर
	व्योम (*ग_लिखो_vfta)(काष्ठा e1000_hw *, u32, u32);
पूर्ण;

काष्ठा e1000_phy_operations अणु
	s32 (*acquire)(काष्ठा e1000_hw *);
	s32 (*check_polarity)(काष्ठा e1000_hw *);
	s32 (*check_reset_block)(काष्ठा e1000_hw *);
	s32 (*क्रमce_speed_duplex)(काष्ठा e1000_hw *);
	s32 (*get_cfg_करोne)(काष्ठा e1000_hw *hw);
	s32 (*get_cable_length)(काष्ठा e1000_hw *);
	s32 (*get_phy_info)(काष्ठा e1000_hw *);
	s32 (*पढ़ो_reg)(काष्ठा e1000_hw *, u32, u16 *);
	व्योम (*release)(काष्ठा e1000_hw *);
	s32 (*reset)(काष्ठा e1000_hw *);
	s32 (*set_d0_lplu_state)(काष्ठा e1000_hw *, bool);
	s32 (*set_d3_lplu_state)(काष्ठा e1000_hw *, bool);
	s32 (*ग_लिखो_reg)(काष्ठा e1000_hw *, u32, u16);
	s32 (*पढ़ो_i2c_byte)(काष्ठा e1000_hw *, u8, u8, u8 *);
	s32 (*ग_लिखो_i2c_byte)(काष्ठा e1000_hw *, u8, u8, u8);
पूर्ण;

काष्ठा e1000_nvm_operations अणु
	s32 (*acquire)(काष्ठा e1000_hw *);
	s32 (*पढ़ो)(काष्ठा e1000_hw *, u16, u16, u16 *);
	व्योम (*release)(काष्ठा e1000_hw *);
	s32 (*ग_लिखो)(काष्ठा e1000_hw *, u16, u16, u16 *);
	s32 (*update)(काष्ठा e1000_hw *);
	s32 (*validate)(काष्ठा e1000_hw *);
	s32 (*valid_led_शेष)(काष्ठा e1000_hw *, u16 *);
पूर्ण;

#घोषणा E1000_MAX_SENSORS		3

काष्ठा e1000_thermal_diode_data अणु
	u8 location;
	u8 temp;
	u8 caution_thresh;
	u8 max_op_thresh;
पूर्ण;

काष्ठा e1000_thermal_sensor_data अणु
	काष्ठा e1000_thermal_diode_data sensor[E1000_MAX_SENSORS];
पूर्ण;

काष्ठा e1000_info अणु
	s32 (*get_invariants)(काष्ठा e1000_hw *);
	काष्ठा e1000_mac_operations *mac_ops;
	स्थिर काष्ठा e1000_phy_operations *phy_ops;
	काष्ठा e1000_nvm_operations *nvm_ops;
पूर्ण;

बाह्य स्थिर काष्ठा e1000_info e1000_82575_info;

काष्ठा e1000_mac_info अणु
	काष्ठा e1000_mac_operations ops;

	u8 addr[6];
	u8 perm_addr[6];

	क्रमागत e1000_mac_type type;

	u32 ledctl_शेष;
	u32 ledctl_mode1;
	u32 ledctl_mode2;
	u32 mc_filter_type;
	u32 txcw;

	u16 mta_reg_count;
	u16 uta_reg_count;

	/* Maximum size of the MTA रेजिस्टर table in all supported adapters */
	#घोषणा MAX_MTA_REG 128
	u32 mta_shaकरोw[MAX_MTA_REG];
	u16 rar_entry_count;

	u8  क्रमced_speed_duplex;

	bool adaptive_अगरs;
	bool arc_subप्रणाली_valid;
	bool asf_firmware_present;
	bool स्वतःneg;
	bool स्वतःneg_failed;
	bool disable_hw_init_bits;
	bool get_link_status;
	bool अगरs_params_क्रमced;
	bool in_अगरs_mode;
	bool report_tx_early;
	bool serdes_has_link;
	bool tx_pkt_filtering;
	काष्ठा e1000_thermal_sensor_data thermal_sensor_data;
पूर्ण;

काष्ठा e1000_phy_info अणु
	काष्ठा e1000_phy_operations ops;

	क्रमागत e1000_phy_type type;

	क्रमागत e1000_1000t_rx_status local_rx;
	क्रमागत e1000_1000t_rx_status remote_rx;
	क्रमागत e1000_ms_type ms_type;
	क्रमागत e1000_ms_type original_ms_type;
	क्रमागत e1000_rev_polarity cable_polarity;
	क्रमागत e1000_smart_speed smart_speed;

	u32 addr;
	u32 id;
	u32 reset_delay_us; /* in usec */
	u32 revision;

	क्रमागत e1000_media_type media_type;

	u16 स्वतःneg_advertised;
	u16 स्वतःneg_mask;
	u16 cable_length;
	u16 max_cable_length;
	u16 min_cable_length;
	u16 pair_length[4];

	u8 mdix;

	bool disable_polarity_correction;
	bool is_mdix;
	bool polarity_correction;
	bool reset_disable;
	bool speed_करोwngraded;
	bool स्वतःneg_रुको_to_complete;
पूर्ण;

काष्ठा e1000_nvm_info अणु
	काष्ठा e1000_nvm_operations ops;
	क्रमागत e1000_nvm_type type;
	क्रमागत e1000_nvm_override override;

	u32 flash_bank_size;
	u32 flash_base_addr;

	u16 word_size;
	u16 delay_usec;
	u16 address_bits;
	u16 opcode_bits;
	u16 page_size;
पूर्ण;

काष्ठा e1000_bus_info अणु
	क्रमागत e1000_bus_type type;
	क्रमागत e1000_bus_speed speed;
	क्रमागत e1000_bus_width width;

	u32 snoop;

	u16 func;
	u16 pci_cmd_word;
पूर्ण;

काष्ठा e1000_fc_info अणु
	u32 high_water;     /* Flow control high-water mark */
	u32 low_water;      /* Flow control low-water mark */
	u16 छोड़ो_समय;     /* Flow control छोड़ो समयr */
	bool send_xon;      /* Flow control send XON */
	bool strict_ieee;   /* Strict IEEE mode */
	क्रमागत e1000_fc_mode current_mode; /* Type of flow control */
	क्रमागत e1000_fc_mode requested_mode;
पूर्ण;

काष्ठा e1000_mbx_operations अणु
	s32 (*init_params)(काष्ठा e1000_hw *hw);
	s32 (*पढ़ो)(काष्ठा e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id,
		    bool unlock);
	s32 (*ग_लिखो)(काष्ठा e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id);
	s32 (*पढ़ो_posted)(काष्ठा e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id);
	s32 (*ग_लिखो_posted)(काष्ठा e1000_hw *hw, u32 *msg, u16 size,
			    u16 mbx_id);
	s32 (*check_क्रम_msg)(काष्ठा e1000_hw *hw, u16 mbx_id);
	s32 (*check_क्रम_ack)(काष्ठा e1000_hw *hw, u16 mbx_id);
	s32 (*check_क्रम_rst)(काष्ठा e1000_hw *hw, u16 mbx_id);
	s32 (*unlock)(काष्ठा e1000_hw *hw, u16 mbx_id);
पूर्ण;

काष्ठा e1000_mbx_stats अणु
	u32 msgs_tx;
	u32 msgs_rx;

	u32 acks;
	u32 reqs;
	u32 rsts;
पूर्ण;

काष्ठा e1000_mbx_info अणु
	काष्ठा e1000_mbx_operations ops;
	काष्ठा e1000_mbx_stats stats;
	u32 समयout;
	u32 usec_delay;
	u16 size;
पूर्ण;

काष्ठा e1000_dev_spec_82575 अणु
	bool sgmii_active;
	bool global_device_reset;
	bool eee_disable;
	bool clear_semaphore_once;
	काष्ठा e1000_sfp_flags eth_flags;
	bool module_plugged;
	u8 media_port;
	bool media_changed;
	bool mas_capable;
पूर्ण;

काष्ठा e1000_hw अणु
	व्योम *back;

	u8 __iomem *hw_addr;
	u8 __iomem *flash_address;
	अचिन्हित दीर्घ io_base;

	काष्ठा e1000_mac_info  mac;
	काष्ठा e1000_fc_info   fc;
	काष्ठा e1000_phy_info  phy;
	काष्ठा e1000_nvm_info  nvm;
	काष्ठा e1000_bus_info  bus;
	काष्ठा e1000_mbx_info mbx;
	काष्ठा e1000_host_mng_dhcp_cookie mng_cookie;

	जोड़ अणु
		काष्ठा e1000_dev_spec_82575	_82575;
	पूर्ण dev_spec;

	u16 device_id;
	u16 subप्रणाली_venकरोr_id;
	u16 subप्रणाली_device_id;
	u16 venकरोr_id;

	u8  revision_id;
पूर्ण;

काष्ठा net_device *igb_get_hw_dev(काष्ठा e1000_hw *hw);
#घोषणा hw_dbg(क्रमmat, arg...) \
	netdev_dbg(igb_get_hw_dev(hw), क्रमmat, ##arg)

/* These functions must be implemented by drivers */
s32 igb_पढ़ो_pcie_cap_reg(काष्ठा e1000_hw *hw, u32 reg, u16 *value);
s32 igb_ग_लिखो_pcie_cap_reg(काष्ठा e1000_hw *hw, u32 reg, u16 *value);

व्योम igb_पढ़ो_pci_cfg(काष्ठा e1000_hw *hw, u32 reg, u16 *value);
व्योम igb_ग_लिखो_pci_cfg(काष्ठा e1000_hw *hw, u32 reg, u16 *value);
#पूर्ण_अगर /* _E1000_IGB_HW_H_ */
