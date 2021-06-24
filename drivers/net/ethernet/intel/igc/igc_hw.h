<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2018 Intel Corporation */

#अगर_अघोषित _IGC_HW_H_
#घोषणा _IGC_HW_H_

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>

#समावेश "igc_regs.h"
#समावेश "igc_defines.h"
#समावेश "igc_mac.h"
#समावेश "igc_phy.h"
#समावेश "igc_nvm.h"
#समावेश "igc_i225.h"
#समावेश "igc_base.h"

#घोषणा IGC_DEV_ID_I225_LM			0x15F2
#घोषणा IGC_DEV_ID_I225_V			0x15F3
#घोषणा IGC_DEV_ID_I225_I			0x15F8
#घोषणा IGC_DEV_ID_I220_V			0x15F7
#घोषणा IGC_DEV_ID_I225_K			0x3100
#घोषणा IGC_DEV_ID_I225_K2			0x3101
#घोषणा IGC_DEV_ID_I225_LMVP			0x5502
#घोषणा IGC_DEV_ID_I226_K			0x5504
#घोषणा IGC_DEV_ID_I225_IT			0x0D9F
#घोषणा IGC_DEV_ID_I226_LM			0x125B
#घोषणा IGC_DEV_ID_I226_V			0x125C
#घोषणा IGC_DEV_ID_I226_IT			0x125D
#घोषणा IGC_DEV_ID_I221_V			0x125E
#घोषणा IGC_DEV_ID_I226_BLANK_NVM		0x125F
#घोषणा IGC_DEV_ID_I225_BLANK_NVM		0x15FD

/* Function poपूर्णांकers क्रम the MAC. */
काष्ठा igc_mac_operations अणु
	s32 (*check_क्रम_link)(काष्ठा igc_hw *hw);
	s32 (*reset_hw)(काष्ठा igc_hw *hw);
	s32 (*init_hw)(काष्ठा igc_hw *hw);
	s32 (*setup_physical_पूर्णांकerface)(काष्ठा igc_hw *hw);
	व्योम (*rar_set)(काष्ठा igc_hw *hw, u8 *address, u32 index);
	s32 (*पढ़ो_mac_addr)(काष्ठा igc_hw *hw);
	s32 (*get_speed_and_duplex)(काष्ठा igc_hw *hw, u16 *speed,
				    u16 *duplex);
	s32 (*acquire_swfw_sync)(काष्ठा igc_hw *hw, u16 mask);
	व्योम (*release_swfw_sync)(काष्ठा igc_hw *hw, u16 mask);
पूर्ण;

क्रमागत igc_mac_type अणु
	igc_undefined = 0,
	igc_i225,
	igc_num_macs  /* List is 1-based, so subtract 1 क्रम true count. */
पूर्ण;

क्रमागत igc_phy_type अणु
	igc_phy_unknown = 0,
	igc_phy_none,
	igc_phy_i225,
पूर्ण;

क्रमागत igc_media_type अणु
	igc_media_type_unknown = 0,
	igc_media_type_copper = 1,
	igc_num_media_types
पूर्ण;

क्रमागत igc_nvm_type अणु
	igc_nvm_unknown = 0,
	igc_nvm_eeprom_spi,
	igc_nvm_flash_hw,
	igc_nvm_invm,
पूर्ण;

काष्ठा igc_info अणु
	s32 (*get_invariants)(काष्ठा igc_hw *hw);
	काष्ठा igc_mac_operations *mac_ops;
	स्थिर काष्ठा igc_phy_operations *phy_ops;
	काष्ठा igc_nvm_operations *nvm_ops;
पूर्ण;

बाह्य स्थिर काष्ठा igc_info igc_base_info;

काष्ठा igc_mac_info अणु
	काष्ठा igc_mac_operations ops;

	u8 addr[ETH_ALEN];
	u8 perm_addr[ETH_ALEN];

	क्रमागत igc_mac_type type;

	u32 mc_filter_type;

	u16 mta_reg_count;
	u16 uta_reg_count;

	u32 mta_shaकरोw[MAX_MTA_REG];
	u16 rar_entry_count;

	u8 क्रमced_speed_duplex;

	bool asf_firmware_present;
	bool arc_subप्रणाली_valid;

	bool स्वतःneg;
	bool स्वतःneg_failed;
	bool get_link_status;
पूर्ण;

काष्ठा igc_nvm_operations अणु
	s32 (*acquire)(काष्ठा igc_hw *hw);
	s32 (*पढ़ो)(काष्ठा igc_hw *hw, u16 offset, u16 i, u16 *data);
	व्योम (*release)(काष्ठा igc_hw *hw);
	s32 (*ग_लिखो)(काष्ठा igc_hw *hw, u16 offset, u16 i, u16 *data);
	s32 (*update)(काष्ठा igc_hw *hw);
	s32 (*validate)(काष्ठा igc_hw *hw);
पूर्ण;

काष्ठा igc_phy_operations अणु
	s32 (*acquire)(काष्ठा igc_hw *hw);
	s32 (*check_reset_block)(काष्ठा igc_hw *hw);
	s32 (*क्रमce_speed_duplex)(काष्ठा igc_hw *hw);
	s32 (*get_phy_info)(काष्ठा igc_hw *hw);
	s32 (*पढ़ो_reg)(काष्ठा igc_hw *hw, u32 address, u16 *data);
	व्योम (*release)(काष्ठा igc_hw *hw);
	s32 (*reset)(काष्ठा igc_hw *hw);
	s32 (*ग_लिखो_reg)(काष्ठा igc_hw *hw, u32 address, u16 data);
पूर्ण;

काष्ठा igc_nvm_info अणु
	काष्ठा igc_nvm_operations ops;
	क्रमागत igc_nvm_type type;

	u16 word_size;
	u16 delay_usec;
	u16 address_bits;
	u16 opcode_bits;
	u16 page_size;
पूर्ण;

काष्ठा igc_phy_info अणु
	काष्ठा igc_phy_operations ops;

	क्रमागत igc_phy_type type;

	u32 addr;
	u32 id;
	u32 reset_delay_us; /* in usec */
	u32 revision;

	क्रमागत igc_media_type media_type;

	u16 स्वतःneg_advertised;
	u16 स्वतःneg_mask;

	u8 mdix;

	bool is_mdix;
	bool speed_करोwngraded;
	bool स्वतःneg_रुको_to_complete;
पूर्ण;

काष्ठा igc_bus_info अणु
	u16 func;
	u16 pci_cmd_word;
पूर्ण;

क्रमागत igc_fc_mode अणु
	igc_fc_none = 0,
	igc_fc_rx_छोड़ो,
	igc_fc_tx_छोड़ो,
	igc_fc_full,
	igc_fc_शेष = 0xFF
पूर्ण;

काष्ठा igc_fc_info अणु
	u32 high_water;     /* Flow control high-water mark */
	u32 low_water;      /* Flow control low-water mark */
	u16 छोड़ो_समय;     /* Flow control छोड़ो समयr */
	bool send_xon;      /* Flow control send XON */
	bool strict_ieee;   /* Strict IEEE mode */
	क्रमागत igc_fc_mode current_mode; /* Type of flow control */
	क्रमागत igc_fc_mode requested_mode;
पूर्ण;

काष्ठा igc_dev_spec_base अणु
	bool clear_semaphore_once;
	bool eee_enable;
पूर्ण;

काष्ठा igc_hw अणु
	व्योम *back;

	u8 __iomem *hw_addr;
	अचिन्हित दीर्घ io_base;

	काष्ठा igc_mac_info  mac;
	काष्ठा igc_fc_info   fc;
	काष्ठा igc_nvm_info  nvm;
	काष्ठा igc_phy_info  phy;

	काष्ठा igc_bus_info bus;

	जोड़ अणु
		काष्ठा igc_dev_spec_base	_base;
	पूर्ण dev_spec;

	u16 device_id;
	u16 subप्रणाली_venकरोr_id;
	u16 subप्रणाली_device_id;
	u16 venकरोr_id;

	u8 revision_id;
पूर्ण;

/* Statistics counters collected by the MAC */
काष्ठा igc_hw_stats अणु
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
	u64 tlpic;
	u64 rlpic;
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
	u64 htdpmc;
	u64 rpthc;
	u64 hgptc;
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

काष्ठा net_device *igc_get_hw_dev(काष्ठा igc_hw *hw);
#घोषणा hw_dbg(क्रमmat, arg...) \
	netdev_dbg(igc_get_hw_dev(hw), क्रमmat, ##arg)

s32  igc_पढ़ो_pcie_cap_reg(काष्ठा igc_hw *hw, u32 reg, u16 *value);
s32  igc_ग_लिखो_pcie_cap_reg(काष्ठा igc_hw *hw, u32 reg, u16 *value);
व्योम igc_पढ़ो_pci_cfg(काष्ठा igc_hw *hw, u32 reg, u16 *value);
व्योम igc_ग_लिखो_pci_cfg(काष्ठा igc_hw *hw, u32 reg, u16 *value);

#पूर्ण_अगर /* _IGC_HW_H_ */
