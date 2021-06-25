<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __IWL_CONFIG_H__
#घोषणा __IWL_CONFIG_H__

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/nl80211.h>
#समावेश "iwl-csr.h"

क्रमागत iwl_device_family अणु
	IWL_DEVICE_FAMILY_UNDEFINED,
	IWL_DEVICE_FAMILY_1000,
	IWL_DEVICE_FAMILY_100,
	IWL_DEVICE_FAMILY_2000,
	IWL_DEVICE_FAMILY_2030,
	IWL_DEVICE_FAMILY_105,
	IWL_DEVICE_FAMILY_135,
	IWL_DEVICE_FAMILY_5000,
	IWL_DEVICE_FAMILY_5150,
	IWL_DEVICE_FAMILY_6000,
	IWL_DEVICE_FAMILY_6000i,
	IWL_DEVICE_FAMILY_6005,
	IWL_DEVICE_FAMILY_6030,
	IWL_DEVICE_FAMILY_6050,
	IWL_DEVICE_FAMILY_6150,
	IWL_DEVICE_FAMILY_7000,
	IWL_DEVICE_FAMILY_8000,
	IWL_DEVICE_FAMILY_9000,
	IWL_DEVICE_FAMILY_22000,
	IWL_DEVICE_FAMILY_AX210,
पूर्ण;

/*
 * LED mode
 *    IWL_LED_DEFAULT:  use device शेष
 *    IWL_LED_RF_STATE: turn LED on/off based on RF state
 *			LED ON  = RF ON
 *			LED OFF = RF OFF
 *    IWL_LED_BLINK:    adjust led blink rate based on blink table
 *    IWL_LED_DISABLE:	led disabled
 */
क्रमागत iwl_led_mode अणु
	IWL_LED_DEFAULT,
	IWL_LED_RF_STATE,
	IWL_LED_BLINK,
	IWL_LED_DISABLE,
पूर्ण;

/**
 * क्रमागत iwl_nvm_type - nvm क्रमmats
 * @IWL_NVM: the regular क्रमmat
 * @IWL_NVM_EXT: extended NVM क्रमmat
 * @IWL_NVM_SDP: NVM क्रमmat used by 3168 series
 */
क्रमागत iwl_nvm_type अणु
	IWL_NVM,
	IWL_NVM_EXT,
	IWL_NVM_SDP,
पूर्ण;

/*
 * This is the threshold value of plcp error rate per 100mSecs.  It is
 * used to set and check क्रम the validity of plcp_delta.
 */
#घोषणा IWL_MAX_PLCP_ERR_THRESHOLD_MIN		1
#घोषणा IWL_MAX_PLCP_ERR_THRESHOLD_DEF		50
#घोषणा IWL_MAX_PLCP_ERR_LONG_THRESHOLD_DEF	100
#घोषणा IWL_MAX_PLCP_ERR_EXT_LONG_THRESHOLD_DEF	200
#घोषणा IWL_MAX_PLCP_ERR_THRESHOLD_MAX		255
#घोषणा IWL_MAX_PLCP_ERR_THRESHOLD_DISABLE	0

/* TX queue watchकरोg समयouts in mSecs */
#घोषणा IWL_WATCHDOG_DISABLED	0
#घोषणा IWL_DEF_WD_TIMEOUT	2500
#घोषणा IWL_LONG_WD_TIMEOUT	10000
#घोषणा IWL_MAX_WD_TIMEOUT	120000

#घोषणा IWL_DEFAULT_MAX_TX_POWER 22
#घोषणा IWL_TX_CSUM_NETIF_FLAGS (NETIF_F_IPV6_CSUM | NETIF_F_IP_CSUM |\
				 NETIF_F_TSO | NETIF_F_TSO6)

/* Antenna presence definitions */
#घोषणा	ANT_NONE	0x0
#घोषणा	ANT_INVALID	0xff
#घोषणा	ANT_A		BIT(0)
#घोषणा	ANT_B		BIT(1)
#घोषणा ANT_C		BIT(2)
#घोषणा	ANT_AB		(ANT_A | ANT_B)
#घोषणा	ANT_AC		(ANT_A | ANT_C)
#घोषणा ANT_BC		(ANT_B | ANT_C)
#घोषणा ANT_ABC		(ANT_A | ANT_B | ANT_C)
#घोषणा MAX_ANT_NUM 3


अटल अंतरभूत u8 num_of_ant(u8 mask)
अणु
	वापस  !!((mask) & ANT_A) +
		!!((mask) & ANT_B) +
		!!((mask) & ANT_C);
पूर्ण

/**
 * काष्ठा iwl_base_params - params not likely to change within a device family
 * @max_ll_items: max number of OTP blocks
 * @shaकरोw_ram_support: shaकरोw support क्रम OTP memory
 * @led_compensation: compensate on the led on/off समय per HW according
 *	to the deviation to achieve the desired led frequency.
 *	The detail algorithm is described in iwl-led.c
 * @wd_समयout: TX queues watchकरोg समयout
 * @max_event_log_size: size of event log buffer size क्रम ucode event logging
 * @shaकरोw_reg_enable: HW shaकरोw रेजिस्टर support
 * @apmg_wake_up_wa: should the MAC access REQ be निश्चितed when a command
 *	is in flight. This is due to a HW bug in 7260, 3160 and 7265.
 * @scd_chain_ext_wa: should the chain extension feature in SCD be disabled.
 * @max_tfd_queue_size: max number of entries in tfd queue.
 */
काष्ठा iwl_base_params अणु
	अचिन्हित पूर्णांक wd_समयout;

	u16 eeprom_size;
	u16 max_event_log_size;

	u8 pll_cfg:1, /* क्रम iwl_pcie_apm_init() */
	   shaकरोw_ram_support:1,
	   shaकरोw_reg_enable:1,
	   pcie_l1_allowed:1,
	   apmg_wake_up_wa:1,
	   scd_chain_ext_wa:1;

	u16 num_of_queues;	/* def: HW dependent */
	u32 max_tfd_queue_size;	/* def: HW dependent */

	u8 max_ll_items;
	u8 led_compensation;
पूर्ण;

/*
 * @stbc: support Tx STBC and 1*SS Rx STBC
 * @ldpc: support Tx/Rx with LDPC
 * @use_rts_क्रम_aggregation: use rts/cts protection क्रम HT traffic
 * @ht40_bands: biपंचांगap of bands (using %NL80211_BAND_*) that support HT40
 */
काष्ठा iwl_ht_params अणु
	u8 ht_greenfield_support:1,
	   stbc:1,
	   ldpc:1,
	   use_rts_क्रम_aggregation:1;
	u8 ht40_bands;
पूर्ण;

/*
 * Tx-backoff threshold
 * @temperature: The threshold in Celsius
 * @backoff: The tx-backoff in uSec
 */
काष्ठा iwl_tt_tx_backoff अणु
	s32 temperature;
	u32 backoff;
पूर्ण;

#घोषणा TT_TX_BACKOFF_SIZE 6

/**
 * काष्ठा iwl_tt_params - thermal throttling parameters
 * @ct_समाप्त_entry: CT Kill entry threshold
 * @ct_समाप्त_निकास: CT Kill निकास threshold
 * @ct_समाप्त_duration: The समय  पूर्णांकervals (in uSec) in which the driver needs
 *	to checks whether to निकास CT Kill.
 * @dynamic_smps_entry: Dynamic SMPS entry threshold
 * @dynamic_smps_निकास: Dynamic SMPS निकास threshold
 * @tx_protection_entry: TX protection entry threshold
 * @tx_protection_निकास: TX protection निकास threshold
 * @tx_backoff: Array of thresholds क्रम tx-backoff , in ascending order.
 * @support_ct_समाप्त: Support CT Kill?
 * @support_dynamic_smps: Support dynamic SMPS?
 * @support_tx_protection: Support tx protection?
 * @support_tx_backoff: Support tx-backoff?
 */
काष्ठा iwl_tt_params अणु
	u32 ct_समाप्त_entry;
	u32 ct_समाप्त_निकास;
	u32 ct_समाप्त_duration;
	u32 dynamic_smps_entry;
	u32 dynamic_smps_निकास;
	u32 tx_protection_entry;
	u32 tx_protection_निकास;
	काष्ठा iwl_tt_tx_backoff tx_backoff[TT_TX_BACKOFF_SIZE];
	u8 support_ct_समाप्त:1,
	   support_dynamic_smps:1,
	   support_tx_protection:1,
	   support_tx_backoff:1;
पूर्ण;

/*
 * inक्रमmation on how to parse the EEPROM
 */
#घोषणा EEPROM_REG_BAND_1_CHANNELS		0x08
#घोषणा EEPROM_REG_BAND_2_CHANNELS		0x26
#घोषणा EEPROM_REG_BAND_3_CHANNELS		0x42
#घोषणा EEPROM_REG_BAND_4_CHANNELS		0x5C
#घोषणा EEPROM_REG_BAND_5_CHANNELS		0x74
#घोषणा EEPROM_REG_BAND_24_HT40_CHANNELS	0x82
#घोषणा EEPROM_REG_BAND_52_HT40_CHANNELS	0x92
#घोषणा EEPROM_6000_REG_BAND_24_HT40_CHANNELS	0x80
#घोषणा EEPROM_REGULATORY_BAND_NO_HT40		0

/* lower blocks contain EEPROM image and calibration data */
#घोषणा OTP_LOW_IMAGE_SIZE_2K		(2 * 512 * माप(u16))  /*  2 KB */
#घोषणा OTP_LOW_IMAGE_SIZE_16K		(16 * 512 * माप(u16)) /* 16 KB */
#घोषणा OTP_LOW_IMAGE_SIZE_32K		(32 * 512 * माप(u16)) /* 32 KB */

काष्ठा iwl_eeprom_params अणु
	स्थिर u8 regulatory_bands[7];
	bool enhanced_txघातer;
पूर्ण;

/* Tx-backoff घातer threshold
 * @pwr: The घातer limit in mw
 * @backoff: The tx-backoff in uSec
 */
काष्ठा iwl_pwr_tx_backoff अणु
	u32 pwr;
	u32 backoff;
पूर्ण;

क्रमागत iwl_cfg_trans_ltr_delay अणु
	IWL_CFG_TRANS_LTR_DELAY_NONE	= 0,
	IWL_CFG_TRANS_LTR_DELAY_200US	= 1,
	IWL_CFG_TRANS_LTR_DELAY_2500US	= 2,
	IWL_CFG_TRANS_LTR_DELAY_1820US	= 3,
पूर्ण;

/**
 * काष्ठा iwl_cfg_trans - inक्रमmation needed to start the trans
 *
 * These values are specअगरic to the device ID and करो not change when
 * multiple configs are used क्रम a single device ID.  They values are
 * used, among other things, to boot the NIC so that the HW REV or
 * RFID can be पढ़ो beक्रमe deciding the reमुख्यing parameters to use.
 *
 * @base_params: poपूर्णांकer to basic parameters
 * @csr: csr flags and addresses that are dअगरferent across devices
 * @device_family: the device family
 * @umac_prph_offset: offset to add to UMAC periphery address
 * @xtal_latency: घातer up latency to get the xtal stabilized
 * @extra_phy_cfg_flags: extra configuration flags to pass to the PHY
 * @rf_id: need to पढ़ो rf_id to determine the firmware image
 * @use_tfh: use TFH
 * @gen2: 22000 and on transport operation
 * @mq_rx_supported: multi-queue rx support
 * @पूर्णांकegrated: discrete or पूर्णांकegrated
 * @low_latency_xtal: use the low latency xtal अगर supported
 * @ltr_delay: LTR delay parameter, &क्रमागत iwl_cfg_trans_ltr_delay.
 */
काष्ठा iwl_cfg_trans_params अणु
	स्थिर काष्ठा iwl_base_params *base_params;
	क्रमागत iwl_device_family device_family;
	u32 umac_prph_offset;
	u32 xtal_latency;
	u32 extra_phy_cfg_flags;
	u32 rf_id:1,
	    use_tfh:1,
	    gen2:1,
	    mq_rx_supported:1,
	    पूर्णांकegrated:1,
	    low_latency_xtal:1,
	    bisr_workaround:1,
	    ltr_delay:2;
पूर्ण;

/**
 * काष्ठा iwl_fw_mon_reg - FW monitor रेजिस्टर info
 * @addr: रेजिस्टर address
 * @mask: रेजिस्टर mask
 */
काष्ठा iwl_fw_mon_reg अणु
	u32 addr;
	u32 mask;
पूर्ण;

/**
 * काष्ठा iwl_fw_mon_regs - FW monitor रेजिस्टरs
 * @ग_लिखो_ptr: ग_लिखो poपूर्णांकer रेजिस्टर
 * @cycle_cnt: cycle count रेजिस्टर
 * @cur_frag: current fragment in use
 */
काष्ठा iwl_fw_mon_regs अणु
	काष्ठा iwl_fw_mon_reg ग_लिखो_ptr;
	काष्ठा iwl_fw_mon_reg cycle_cnt;
	काष्ठा iwl_fw_mon_reg cur_frag;
पूर्ण;

/**
 * काष्ठा iwl_cfg
 * @trans: the trans-specअगरic configuration part
 * @name: Official name of the device
 * @fw_name_pre: Firmware filename prefix. The api version and extension
 *	(.ucode) will be added to filename beक्रमe loading from disk. The
 *	filename is स्थिरructed as fw_name_pre<api>.ucode.
 * @ucode_api_max: Highest version of uCode API supported by driver.
 * @ucode_api_min: Lowest version of uCode API supported by driver.
 * @max_inst_size: The maximal length of the fw inst section (only DVM)
 * @max_data_size: The maximal length of the fw data section (only DVM)
 * @valid_tx_ant: valid transmit antenna
 * @valid_rx_ant: valid receive antenna
 * @non_shared_ant: the antenna that is क्रम WiFi only
 * @nvm_ver: NVM version
 * @nvm_calib_ver: NVM calibration version
 * @lib: poपूर्णांकer to the lib ops
 * @ht_params: poपूर्णांक to ht parameters
 * @led_mode: 0=blinking, 1=On(RF On)/Off(RF Off)
 * @rx_with_siso_भागersity: 1x1 device with rx antenna भागersity
 * @tx_with_siso_भागersity: 1x1 device with tx antenna भागersity
 * @पूर्णांकernal_wimax_coex: पूर्णांकernal wअगरi/wimax combo device
 * @high_temp: Is this NIC is designated to be in high temperature.
 * @host_पूर्णांकerrupt_operation_mode: device needs host पूर्णांकerrupt operation
 *	mode set
 * @nvm_hw_section_num: the ID of the HW NVM section
 * @mac_addr_from_csr: पढ़ो HW address from CSR रेजिस्टरs
 * @features: hw features, any combination of feature_passlist
 * @pwr_tx_backoffs: translation table between घातer limits and backoffs
 * @max_tx_agg_size: max TX aggregation size of the ADDBA request/response
 * @dccm_offset: offset from which DCCM begins
 * @dccm_len: length of DCCM (including runसमय stack CCM)
 * @dccm2_offset: offset from which the second DCCM begins
 * @dccm2_len: length of the second DCCM
 * @smem_offset: offset from which the SMEM begins
 * @smem_len: the length of SMEM
 * @vht_mu_mimo_supported: VHT MU-MIMO support
 * @cdb: CDB support
 * @nvm_type: see &क्रमागत iwl_nvm_type
 * @d3_debug_data_base_addr: base address where D3 debug data is stored
 * @d3_debug_data_length: length of the D3 debug data
 * @bisr_workaround: BISR hardware workaround (क्रम 22260 series devices)
 * @min_txq_size: minimum number of slots required in a TX queue
 * @uhb_supported: ultra high band channels supported
 * @min_256_ba_txq_size: minimum number of slots required in a TX queue which
 *	supports 256 BA aggregation
 * @num_rbds: number of receive buffer descriptors to use
 *	(only used क्रम multi-queue capable devices)
 *
 * We enable the driver to be backward compatible wrt. hardware features.
 * API dअगरferences in uCode shouldn't be handled here but through TLVs
 * and/or the uCode API version instead.
 */
काष्ठा iwl_cfg अणु
	काष्ठा iwl_cfg_trans_params trans;
	/* params specअगरic to an inभागidual device within a device family */
	स्थिर अक्षर *name;
	स्थिर अक्षर *fw_name_pre;
	/* params likely to change within a device family */
	स्थिर काष्ठा iwl_ht_params *ht_params;
	स्थिर काष्ठा iwl_eeprom_params *eeprom_params;
	स्थिर काष्ठा iwl_pwr_tx_backoff *pwr_tx_backoffs;
	स्थिर अक्षर *शेष_nvm_file_C_step;
	स्थिर काष्ठा iwl_tt_params *thermal_params;
	क्रमागत iwl_led_mode led_mode;
	क्रमागत iwl_nvm_type nvm_type;
	u32 max_data_size;
	u32 max_inst_size;
	netdev_features_t features;
	u32 dccm_offset;
	u32 dccm_len;
	u32 dccm2_offset;
	u32 dccm2_len;
	u32 smem_offset;
	u32 smem_len;
	u16 nvm_ver;
	u16 nvm_calib_ver;
	u32 rx_with_siso_भागersity:1,
	    tx_with_siso_भागersity:1,
	    bt_shared_single_ant:1,
	    पूर्णांकernal_wimax_coex:1,
	    host_पूर्णांकerrupt_operation_mode:1,
	    high_temp:1,
	    mac_addr_from_csr:1,
	    lp_xtal_workaround:1,
	    disable_dummy_notअगरication:1,
	    apmg_not_supported:1,
	    vht_mu_mimo_supported:1,
	    cdb:1,
	    dbgc_supported:1,
	    uhb_supported:1;
	u8 valid_tx_ant;
	u8 valid_rx_ant;
	u8 non_shared_ant;
	u8 nvm_hw_section_num;
	u8 max_tx_agg_size;
	u8 ucode_api_max;
	u8 ucode_api_min;
	u16 num_rbds;
	u32 min_umac_error_event_table;
	u32 d3_debug_data_base_addr;
	u32 d3_debug_data_length;
	u32 min_txq_size;
	u32 gp2_reg_addr;
	u32 min_256_ba_txq_size;
	स्थिर काष्ठा iwl_fw_mon_regs mon_dram_regs;
	स्थिर काष्ठा iwl_fw_mon_regs mon_smem_regs;
पूर्ण;

#घोषणा IWL_CFG_ANY (~0)

#घोषणा IWL_CFG_MAC_TYPE_PU		0x31
#घोषणा IWL_CFG_MAC_TYPE_PNJ		0x32
#घोषणा IWL_CFG_MAC_TYPE_TH		0x32
#घोषणा IWL_CFG_MAC_TYPE_QU		0x33
#घोषणा IWL_CFG_MAC_TYPE_QUZ		0x35
#घोषणा IWL_CFG_MAC_TYPE_QNJ		0x36
#घोषणा IWL_CFG_MAC_TYPE_SO		0x37
#घोषणा IWL_CFG_MAC_TYPE_SNJ		0x42
#घोषणा IWL_CFG_MAC_TYPE_SOF		0x43
#घोषणा IWL_CFG_MAC_TYPE_MA		0x44
#घोषणा IWL_CFG_MAC_TYPE_BZ		0x46

#घोषणा IWL_CFG_RF_TYPE_TH		0x105
#घोषणा IWL_CFG_RF_TYPE_TH1		0x108
#घोषणा IWL_CFG_RF_TYPE_JF2		0x105
#घोषणा IWL_CFG_RF_TYPE_JF1		0x108
#घोषणा IWL_CFG_RF_TYPE_HR2		0x10A
#घोषणा IWL_CFG_RF_TYPE_HR1		0x10C
#घोषणा IWL_CFG_RF_TYPE_GF		0x10D
#घोषणा IWL_CFG_RF_TYPE_MR		0x110

#घोषणा IWL_CFG_RF_ID_TH		0x1
#घोषणा IWL_CFG_RF_ID_TH1		0x1
#घोषणा IWL_CFG_RF_ID_JF		0x3
#घोषणा IWL_CFG_RF_ID_JF1		0x6
#घोषणा IWL_CFG_RF_ID_JF1_DIV		0xA
#घोषणा IWL_CFG_RF_ID_HR		0x7
#घोषणा IWL_CFG_RF_ID_HR1		0x4

#घोषणा IWL_CFG_NO_160			0x1
#घोषणा IWL_CFG_160			0x0

#घोषणा IWL_CFG_CORES_BT		0x0
#घोषणा IWL_CFG_CORES_BT_GNSS		0x5

#घोषणा IWL_CFG_NO_CDB			0x0
#घोषणा IWL_CFG_CDB			0x1

#घोषणा IWL_SUBDEVICE_RF_ID(subdevice)	((u16)((subdevice) & 0x00F0) >> 4)
#घोषणा IWL_SUBDEVICE_NO_160(subdevice)	((u16)((subdevice) & 0x0200) >> 9)
#घोषणा IWL_SUBDEVICE_CORES(subdevice)	((u16)((subdevice) & 0x1C00) >> 10)

काष्ठा iwl_dev_info अणु
	u16 device;
	u16 subdevice;
	u16 mac_type;
	u16 rf_type;
	u8 mac_step;
	u8 rf_id;
	u8 no_160;
	u8 cores;
	u8 cdb;
	स्थिर काष्ठा iwl_cfg *cfg;
	स्थिर अक्षर *name;
पूर्ण;

/*
 * This list declares the config काष्ठाures क्रम all devices.
 */
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl9000_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl9560_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl9560_दीर्घ_latency_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl9560_shared_clk_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_qnj_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_qu_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_qu_medium_latency_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_qu_दीर्घ_latency_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_ax200_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_snj_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_so_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_so_दीर्घ_latency_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_ma_trans_cfg;
बाह्य स्थिर काष्ठा iwl_cfg_trans_params iwl_bz_trans_cfg;
बाह्य स्थिर अक्षर iwl9162_name[];
बाह्य स्थिर अक्षर iwl9260_name[];
बाह्य स्थिर अक्षर iwl9260_1_name[];
बाह्य स्थिर अक्षर iwl9270_name[];
बाह्य स्थिर अक्षर iwl9461_name[];
बाह्य स्थिर अक्षर iwl9462_name[];
बाह्य स्थिर अक्षर iwl9560_name[];
बाह्य स्थिर अक्षर iwl9162_160_name[];
बाह्य स्थिर अक्षर iwl9260_160_name[];
बाह्य स्थिर अक्षर iwl9270_160_name[];
बाह्य स्थिर अक्षर iwl9461_160_name[];
बाह्य स्थिर अक्षर iwl9462_160_name[];
बाह्य स्थिर अक्षर iwl9560_160_name[];
बाह्य स्थिर अक्षर iwl9260_समाप्तer_1550_name[];
बाह्य स्थिर अक्षर iwl9560_समाप्तer_1550i_name[];
बाह्य स्थिर अक्षर iwl9560_समाप्तer_1550s_name[];
बाह्य स्थिर अक्षर iwl_ax200_name[];
बाह्य स्थिर अक्षर iwl_ax203_name[];
बाह्य स्थिर अक्षर iwl_ax201_name[];
बाह्य स्थिर अक्षर iwl_ax101_name[];
बाह्य स्थिर अक्षर iwl_ax200_समाप्तer_1650w_name[];
बाह्य स्थिर अक्षर iwl_ax200_समाप्तer_1650x_name[];
बाह्य स्थिर अक्षर iwl_ax201_समाप्तer_1650s_name[];
बाह्य स्थिर अक्षर iwl_ax201_समाप्तer_1650i_name[];
बाह्य स्थिर अक्षर iwl_ax210_समाप्तer_1675w_name[];
बाह्य स्थिर अक्षर iwl_ax210_समाप्तer_1675x_name[];
बाह्य स्थिर अक्षर iwl_ax211_name[];
बाह्य स्थिर अक्षर iwl_ax221_name[];
बाह्य स्थिर अक्षर iwl_ax411_name[];
#अगर IS_ENABLED(CONFIG_IWLDVM)
बाह्य स्थिर काष्ठा iwl_cfg iwl5300_agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl5100_agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl5350_agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl5100_bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl5100_abg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl5150_agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl5150_abg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6005_2agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6005_2abg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6005_2bg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6005_2agn_sff_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6005_2agn_d_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6005_2agn_mow1_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6005_2agn_mow2_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl1030_bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl1030_bg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6030_2agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6030_2abg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6030_2bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6030_2bg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6000i_2agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6000i_2abg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6000i_2bg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6000_3agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6050_2agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6050_2abg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6150_bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6150_bg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl1000_bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl1000_bg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl100_bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl100_bg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl130_bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl130_bg_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl2000_2bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl2000_2bgn_d_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl2030_2bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6035_2agn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl6035_2agn_sff_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl105_bgn_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl105_bgn_d_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl135_bgn_cfg;
#पूर्ण_अगर /* CONFIG_IWLDVM */
#अगर IS_ENABLED(CONFIG_IWLMVM)
बाह्य स्थिर काष्ठा iwl_cfg iwl7260_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl7260_2ac_cfg_high_temp;
बाह्य स्थिर काष्ठा iwl_cfg iwl7260_2n_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl7260_n_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl3160_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl3160_2n_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl3160_n_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl3165_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl3168_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl7265_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl7265_2n_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl7265_n_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl7265d_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl7265d_2n_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl7265d_n_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl8260_2n_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl8260_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl8265_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl8275_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl4165_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl9260_2ac_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl9560_qu_b0_jf_b0_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl9560_qu_c0_jf_b0_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl9560_quz_a0_jf_b0_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl9560_qnj_b0_jf_b0_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl9560_2ac_cfg_soc;
बाह्य स्थिर काष्ठा iwl_cfg iwl_qu_b0_hr1_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_qu_c0_hr1_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_quz_a0_hr1_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_qu_b0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_qu_c0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_ax200_cfg_cc;
बाह्य स्थिर काष्ठा iwl_cfg iwl_ax201_cfg_qu_hr;
बाह्य स्थिर काष्ठा iwl_cfg iwl_ax201_cfg_qu_hr;
बाह्य स्थिर काष्ठा iwl_cfg iwl_ax201_cfg_qu_c0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_ax201_cfg_quz_hr;
बाह्य स्थिर काष्ठा iwl_cfg iwl_ax1650i_cfg_quz_hr;
बाह्य स्थिर काष्ठा iwl_cfg iwl_ax1650s_cfg_quz_hr;
बाह्य स्थिर काष्ठा iwl_cfg समाप्तer1650s_2ax_cfg_qu_b0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg समाप्तer1650i_2ax_cfg_qu_b0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg समाप्तer1650s_2ax_cfg_qu_c0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg समाप्तer1650i_2ax_cfg_qu_c0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg समाप्तer1650x_2ax_cfg;
बाह्य स्थिर काष्ठा iwl_cfg समाप्तer1650w_2ax_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwl_qnj_b0_hr_b0_cfg;
बाह्य स्थिर काष्ठा iwl_cfg iwlax210_2ax_cfg_so_jf_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwlax210_2ax_cfg_so_hr_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwlax211_2ax_cfg_so_gf_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwlax211_2ax_cfg_so_gf_a0_दीर्घ;
बाह्य स्थिर काष्ठा iwl_cfg iwlax210_2ax_cfg_ty_gf_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwlax411_2ax_cfg_so_gf4_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwlax411_2ax_cfg_so_gf4_a0_दीर्घ;
बाह्य स्थिर काष्ठा iwl_cfg iwlax411_2ax_cfg_sosnj_gf4_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwlax211_cfg_snj_gf_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_snj_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_snj_a0_jf_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_ma_a0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_ma_a0_gf_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_ma_a0_gf4_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_ma_a0_mr_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_snj_a0_mr_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_so_a0_hr_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_quz_a0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_bz_a0_hr_b0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_bz_a0_gf_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_bz_a0_gf4_a0;
बाह्य स्थिर काष्ठा iwl_cfg iwl_cfg_bz_a0_mr_a0;
#पूर्ण_अगर /* CONFIG_IWLMVM */

#पूर्ण_अगर /* __IWL_CONFIG_H__ */
