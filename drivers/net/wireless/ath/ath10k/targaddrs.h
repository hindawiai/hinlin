<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2016 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित __TARGADDRS_H__
#घोषणा __TARGADDRS_H__

#समावेश "hw.h"

/*
 * xxx_HOST_INTEREST_ADDRESS is the address in Target RAM of the
 * host_पूर्णांकerest काष्ठाure.  It must match the address of the _host_पूर्णांकerest
 * symbol (see linker script).
 *
 * Host Interest is shared between Host and Target in order to coordinate
 * between the two, and is पूर्णांकended to reमुख्य स्थिरant (with additions only
 * at the end) across software releases.
 *
 * All addresses are available here so that it's possible to
 * ग_लिखो a single binary that works with all Target Types.
 * May be used in assembler code as well as C.
 */
#घोषणा QCA988X_HOST_INTEREST_ADDRESS    0x00400800
#घोषणा HOST_INTEREST_MAX_SIZE          0x200

/*
 * These are items that the Host may need to access via BMI or via the
 * Diagnostic Winकरोw. The position of items in this काष्ठाure must reमुख्य
 * स्थिरant across firmware revisions! Types क्रम each item must be fixed
 * size across target and host platक्रमms. More items may be added at the end.
 */
काष्ठा host_पूर्णांकerest अणु
	/*
	 * Poपूर्णांकer to application-defined area, अगर any.
	 * Set by Target application during startup.
	 */
	u32 hi_app_host_पूर्णांकerest;			/* 0x00 */

	/* Poपूर्णांकer to रेजिस्टर dump area, valid after Target crash. */
	u32 hi_failure_state;				/* 0x04 */

	/* Poपूर्णांकer to debug logging header */
	u32 hi_dbglog_hdr;				/* 0x08 */

	u32 hi_unused0c;				/* 0x0c */

	/*
	 * General-purpose flag bits, similar to SOC_OPTION_* flags.
	 * Can be used by application rather than by OS.
	 */
	u32 hi_option_flag;				/* 0x10 */

	/*
	 * Boolean that determines whether or not to
	 * display messages on the serial port.
	 */
	u32 hi_serial_enable;				/* 0x14 */

	/* Start address of DataSet index, अगर any */
	u32 hi_dset_list_head;				/* 0x18 */

	/* Override Target application start address */
	u32 hi_app_start;				/* 0x1c */

	/* Clock and voltage tuning */
	u32 hi_skip_घड़ी_init;				/* 0x20 */
	u32 hi_core_घड़ी_setting;			/* 0x24 */
	u32 hi_cpu_घड़ी_setting;			/* 0x28 */
	u32 hi_प्रणाली_sleep_setting;			/* 0x2c */
	u32 hi_xtal_control_setting;			/* 0x30 */
	u32 hi_pll_ctrl_setting_24ghz;			/* 0x34 */
	u32 hi_pll_ctrl_setting_5ghz;			/* 0x38 */
	u32 hi_ref_voltage_trim_setting;		/* 0x3c */
	u32 hi_घड़ी_info;				/* 0x40 */

	/* Host uses BE CPU or not */
	u32 hi_be;					/* 0x44 */

	u32 hi_stack;	/* normal stack */			/* 0x48 */
	u32 hi_err_stack; /* error stack */		/* 0x4c */
	u32 hi_desired_cpu_speed_hz;			/* 0x50 */

	/* Poपूर्णांकer to Board Data  */
	u32 hi_board_data;				/* 0x54 */

	/*
	 * Indication of Board Data state:
	 *    0: board data is not yet initialized.
	 *    1: board data is initialized; unknown size
	 *   >1: number of bytes of initialized board data
	 */
	u32 hi_board_data_initialized;			/* 0x58 */

	u32 hi_dset_ram_index_table;			/* 0x5c */

	u32 hi_desired_baud_rate;			/* 0x60 */
	u32 hi_dbglog_config;				/* 0x64 */
	u32 hi_end_ram_reserve_sz;			/* 0x68 */
	u32 hi_mbox_io_block_sz;			/* 0x6c */

	u32 hi_num_bpatch_streams;			/* 0x70 -- unused */
	u32 hi_mbox_isr_yield_limit;			/* 0x74 */

	u32 hi_refclk_hz;				/* 0x78 */
	u32 hi_ext_clk_detected;			/* 0x7c */
	u32 hi_dbg_uart_txpin;				/* 0x80 */
	u32 hi_dbg_uart_rxpin;				/* 0x84 */
	u32 hi_hci_uart_baud;				/* 0x88 */
	u32 hi_hci_uart_pin_assignments;		/* 0x8C */

	u32 hi_hci_uart_baud_scale_val;			/* 0x90 */
	u32 hi_hci_uart_baud_step_val;			/* 0x94 */

	u32 hi_allocram_start;				/* 0x98 */
	u32 hi_allocram_sz;				/* 0x9c */
	u32 hi_hci_bridge_flags;			/* 0xa0 */
	u32 hi_hci_uart_support_pins;			/* 0xa4 */

	u32 hi_hci_uart_pwr_mgmt_params;		/* 0xa8 */

	/*
	 * 0xa8 - [1]: 0 = UART FC active low, 1 = UART FC active high
	 *        [31:16]: wakeup समयout in ms
	 */
	/* Poपूर्णांकer to extended board Data  */
	u32 hi_board_ext_data;				/* 0xac */
	u32 hi_board_ext_data_config;			/* 0xb0 */
	/*
	 * Bit [0]  :   valid
	 * Bit[31:16:   size
	 */
	/*
	 * hi_reset_flag is used to करो some stuff when target reset.
	 * such as restore app_start after warm reset or
	 * preserve host Interest area, or preserve ROM data, literals etc.
	 */
	u32  hi_reset_flag;				/* 0xb4 */
	/* indicate hi_reset_flag is valid */
	u32  hi_reset_flag_valid;			/* 0xb8 */
	u32 hi_hci_uart_pwr_mgmt_params_ext;		/* 0xbc */
	/* 0xbc - [31:0]: idle समयout in ms */
	/* ACS flags */
	u32 hi_acs_flags;				/* 0xc0 */
	u32 hi_console_flags;				/* 0xc4 */
	u32 hi_nvram_state;				/* 0xc8 */
	u32 hi_option_flag2;				/* 0xcc */

	/* If non-zero, override values sent to Host in WMI_READY event. */
	u32 hi_sw_version_override;			/* 0xd0 */
	u32 hi_abi_version_override;			/* 0xd4 */

	/*
	 * Percentage of high priority RX traffic to total expected RX traffic
	 * applicable only to ar6004
	 */
	u32 hi_hp_rx_traffic_ratio;			/* 0xd8 */

	/* test applications flags */
	u32 hi_test_apps_related;			/* 0xdc */
	/* location of test script */
	u32 hi_ota_testscript;				/* 0xe0 */
	/* location of CAL data */
	u32 hi_cal_data;				/* 0xe4 */

	/* Number of packet log buffers */
	u32 hi_pktlog_num_buffers;			/* 0xe8 */

	/* wow extension configuration */
	u32 hi_wow_ext_config;				/* 0xec */
	u32 hi_pwr_save_flags;				/* 0xf0 */

	/* Spatial Multiplexing Power Save (SMPS) options */
	u32 hi_smps_options;				/* 0xf4 */

	/* Interconnect-specअगरic state */
	u32 hi_पूर्णांकerconnect_state;			/* 0xf8 */

	/* Coex configuration flags */
	u32 hi_coex_config;				/* 0xfc */

	/* Early allocation support */
	u32 hi_early_alloc;				/* 0x100 */
	/* FW swap field */
	/*
	 * Bits of this 32bit word will be used to pass specअगरic swap
	 * inकाष्ठाion to FW
	 */
	/*
	 * Bit 0 -- AP Nart descriptor no swap. When this bit is set
	 * FW will not swap TX descriptor. Meaning packets are क्रमmed
	 * on the target processor.
	 */
	/* Bit 1 - unused */
	u32 hi_fw_swap;					/* 0x104 */

	/* global arenas poपूर्णांकer address, used by host driver debug */
	u32 hi_dynamic_mem_arenas_addr;			/* 0x108 */

	/* allocated bytes of DRAM use by allocated */
	u32 hi_dynamic_mem_allocated;			/* 0x10C */

	/* reमुख्यing bytes of DRAM */
	u32 hi_dynamic_mem_reमुख्यing;			/* 0x110 */

	/* memory track count, configured by host */
	u32 hi_dynamic_mem_track_max;			/* 0x114 */

	/* minidump buffer */
	u32 hi_minidump;				/* 0x118 */

	/* bdata's sig and key addr */
	u32 hi_bd_sig_key;				/* 0x11c */
पूर्ण __packed;

#घोषणा HI_ITEM(item)  दुरत्व(काष्ठा host_पूर्णांकerest, item)

/* Bits defined in hi_option_flag */

/* Enable समयr workaround */
#घोषणा HI_OPTION_TIMER_WAR         0x01
/* Limit BMI command credits */
#घोषणा HI_OPTION_BMI_CRED_LIMIT    0x02
/* Relay Dot11 hdr to/from host */
#घोषणा HI_OPTION_RELAY_DOT11_HDR   0x04
/* MAC addr method 0-locally administred 1-globally unique addrs */
#घोषणा HI_OPTION_MAC_ADDR_METHOD   0x08
/* Firmware Bridging */
#घोषणा HI_OPTION_FW_BRIDGE         0x10
/* Enable CPU profiling */
#घोषणा HI_OPTION_ENABLE_PROखाता    0x20
/* Disable debug logging */
#घोषणा HI_OPTION_DISABLE_DBGLOG    0x40
/* Skip Era Tracking */
#घोषणा HI_OPTION_SKIP_ERA_TRACKING 0x80
/* Disable PAPRD (debug) */
#घोषणा HI_OPTION_PAPRD_DISABLE     0x100
#घोषणा HI_OPTION_NUM_DEV_LSB       0x200
#घोषणा HI_OPTION_NUM_DEV_MSB       0x800
#घोषणा HI_OPTION_DEV_MODE_LSB      0x1000
#घोषणा HI_OPTION_DEV_MODE_MSB      0x8000000
/* Disable LowFreq Timer Stabilization */
#घोषणा HI_OPTION_NO_LFT_STBL       0x10000000
/* Skip regulatory scan */
#घोषणा HI_OPTION_SKIP_REG_SCAN     0x20000000
/*
 * Do regulatory scan during init beक्रमe
 * sending WMI पढ़ोy event to host
 */
#घोषणा HI_OPTION_INIT_REG_SCAN     0x40000000

/* REV6: Do not adjust memory map */
#घोषणा HI_OPTION_SKIP_MEMMAP       0x80000000

#घोषणा HI_OPTION_MAC_ADDR_METHOD_SHIFT 3

/* 2 bits of hi_option_flag are used to represent 3 modes */
#घोषणा HI_OPTION_FW_MODE_IBSS    0x0 /* IBSS Mode */
#घोषणा HI_OPTION_FW_MODE_BSS_STA 0x1 /* STA Mode */
#घोषणा HI_OPTION_FW_MODE_AP      0x2 /* AP Mode */
#घोषणा HI_OPTION_FW_MODE_BT30AMP 0x3 /* BT30 AMP Mode */

/* 2 bits of hi_option flag are usedto represent 4 submodes */
#घोषणा HI_OPTION_FW_SUBMODE_NONE    0x0  /* Normal mode */
#घोषणा HI_OPTION_FW_SUBMODE_P2PDEV  0x1  /* p2p device mode */
#घोषणा HI_OPTION_FW_SUBMODE_P2PCLIENT 0x2 /* p2p client mode */
#घोषणा HI_OPTION_FW_SUBMODE_P2PGO   0x3 /* p2p go mode */

/* Num dev Mask */
#घोषणा HI_OPTION_NUM_DEV_MASK    0x7
#घोषणा HI_OPTION_NUM_DEV_SHIFT   0x9

/* firmware bridging */
#घोषणा HI_OPTION_FW_BRIDGE_SHIFT 0x04

/*
 * Fw Mode/SubMode Mask
 *-----------------------------------------------------------------------------
 *  SUB   |   SUB   |   SUB   |  SUB    |         |         |         |
 *MODE[3] | MODE[2] | MODE[1] | MODE[0] | MODE[3] | MODE[2] | MODE[1] | MODE[0]
 *  (2)   |   (2)   |   (2)   |   (2)   |   (2)   |   (2)   |   (2)   |   (2)
 *-----------------------------------------------------------------------------
 */
#घोषणा HI_OPTION_FW_MODE_BITS         0x2
#घोषणा HI_OPTION_FW_MODE_MASK         0x3
#घोषणा HI_OPTION_FW_MODE_SHIFT        0xC
#घोषणा HI_OPTION_ALL_FW_MODE_MASK     0xFF

#घोषणा HI_OPTION_FW_SUBMODE_BITS      0x2
#घोषणा HI_OPTION_FW_SUBMODE_MASK      0x3
#घोषणा HI_OPTION_FW_SUBMODE_SHIFT     0x14
#घोषणा HI_OPTION_ALL_FW_SUBMODE_MASK  0xFF00
#घोषणा HI_OPTION_ALL_FW_SUBMODE_SHIFT 0x8

/* hi_option_flag2 options */
#घोषणा HI_OPTION_OFFLOAD_AMSDU     0x01
#घोषणा HI_OPTION_DFS_SUPPORT       0x02 /* Enable DFS support */
#घोषणा HI_OPTION_ENABLE_RFKILL     0x04 /* RFKill Enable Feature*/
#घोषणा HI_OPTION_RADIO_RETENTION_DISABLE 0x08 /* Disable radio retention */
#घोषणा HI_OPTION_EARLY_CFG_DONE    0x10 /* Early configuration is complete */

#घोषणा HI_OPTION_RF_KILL_SHIFT     0x2
#घोषणा HI_OPTION_RF_KILL_MASK      0x1

/* hi_reset_flag */
/* preserve App Start address */
#घोषणा HI_RESET_FLAG_PRESERVE_APP_START         0x01
/* preserve host पूर्णांकerest */
#घोषणा HI_RESET_FLAG_PRESERVE_HOST_INTEREST     0x02
/* preserve ROM data */
#घोषणा HI_RESET_FLAG_PRESERVE_ROMDATA           0x04
#घोषणा HI_RESET_FLAG_PRESERVE_NVRAM_STATE       0x08
#घोषणा HI_RESET_FLAG_PRESERVE_BOOT_INFO         0x10
#घोषणा HI_RESET_FLAG_WARM_RESET	0x20

/* define hi_fw_swap bits */
#घोषणा HI_DESC_IN_FW_BIT	0x01

/* indicate the reset flag is valid */
#घोषणा HI_RESET_FLAG_IS_VALID  0x12345678

/* ACS is enabled */
#घोषणा HI_ACS_FLAGS_ENABLED        (1 << 0)
/* Use physical WWAN device */
#घोषणा HI_ACS_FLAGS_USE_WWAN       (1 << 1)
/* Use test VAP */
#घोषणा HI_ACS_FLAGS_TEST_VAP       (1 << 2)
/* SDIO/mailbox ACS flag definitions */
#घोषणा HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_SET       (1 << 0)
#घोषणा HI_ACS_FLAGS_SDIO_REDUCE_TX_COMPL_SET    (1 << 1)
#घोषणा HI_ACS_FLAGS_ALT_DATA_CREDIT_SIZE        (1 << 2)
#घोषणा HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_FW_ACK    (1 << 16)
#घोषणा HI_ACS_FLAGS_SDIO_REDUCE_TX_COMPL_FW_ACK (1 << 17)

/*
 * If both SDIO_CRASH_DUMP_ENHANCEMENT_HOST and SDIO_CRASH_DUMP_ENHANCEMENT_FW
 * flags are set, then crashdump upload will be करोne using the BMI host/target
 * communication channel.
 */
/* HOST to support using BMI dump FW memory when hit निश्चित */
#घोषणा HI_OPTION_SDIO_CRASH_DUMP_ENHANCEMENT_HOST 0x400

/* FW to support using BMI dump FW memory when hit निश्चित */
#घोषणा HI_OPTION_SDIO_CRASH_DUMP_ENHANCEMENT_FW   0x800

/*
 * CONSOLE FLAGS
 *
 * Bit Range  Meaning
 * ---------  --------------------------------
 *   2..0     UART ID (0 = Default)
 *    3       Baud Select (0 = 9600, 1 = 115200)
 *   30..4    Reserved
 *    31      Enable Console
 *
 */

#घोषणा HI_CONSOLE_FLAGS_ENABLE       (1 << 31)
#घोषणा HI_CONSOLE_FLAGS_UART_MASK    (0x7)
#घोषणा HI_CONSOLE_FLAGS_UART_SHIFT   0
#घोषणा HI_CONSOLE_FLAGS_BAUD_SELECT  (1 << 3)

/* SM घातer save options */
#घोषणा HI_SMPS_ALLOW_MASK            (0x00000001)
#घोषणा HI_SMPS_MODE_MASK             (0x00000002)
#घोषणा HI_SMPS_MODE_STATIC           (0x00000000)
#घोषणा HI_SMPS_MODE_DYNAMIC          (0x00000002)
#घोषणा HI_SMPS_DISABLE_AUTO_MODE     (0x00000004)
#घोषणा HI_SMPS_DATA_THRESH_MASK      (0x000007f8)
#घोषणा HI_SMPS_DATA_THRESH_SHIFT     (3)
#घोषणा HI_SMPS_RSSI_THRESH_MASK      (0x0007f800)
#घोषणा HI_SMPS_RSSI_THRESH_SHIFT     (11)
#घोषणा HI_SMPS_LOWPWR_CM_MASK        (0x00380000)
#घोषणा HI_SMPS_LOWPWR_CM_SHIFT       (15)
#घोषणा HI_SMPS_HIPWR_CM_MASK         (0x03c00000)
#घोषणा HI_SMPS_HIPWR_CM_SHIFT        (19)

/*
 * WOW Extension configuration
 *
 * Bit Range  Meaning
 * ---------  --------------------------------
 *   8..0     Size of each WOW pattern (max 511)
 *   15..9    Number of patterns per list (max 127)
 *   17..16   Number of lists (max 4)
 *   30..18   Reserved
 *   31       Enabled
 *
 *  set values (except enable) to zeros क्रम शेष settings
 */

#घोषणा HI_WOW_EXT_ENABLED_MASK        (1 << 31)
#घोषणा HI_WOW_EXT_NUM_LIST_SHIFT      16
#घोषणा HI_WOW_EXT_NUM_LIST_MASK       (0x3 << HI_WOW_EXT_NUM_LIST_SHIFT)
#घोषणा HI_WOW_EXT_NUM_PATTERNS_SHIFT  9
#घोषणा HI_WOW_EXT_NUM_PATTERNS_MASK   (0x7F << HI_WOW_EXT_NUM_PATTERNS_SHIFT)
#घोषणा HI_WOW_EXT_PATTERN_SIZE_SHIFT  0
#घोषणा HI_WOW_EXT_PATTERN_SIZE_MASK   (0x1FF << HI_WOW_EXT_PATTERN_SIZE_SHIFT)

#घोषणा HI_WOW_EXT_MAKE_CONFIG(num_lists, count, size) \
	((((num_lists) << HI_WOW_EXT_NUM_LIST_SHIFT) & \
		HI_WOW_EXT_NUM_LIST_MASK) | \
	(((count) << HI_WOW_EXT_NUM_PATTERNS_SHIFT) & \
		HI_WOW_EXT_NUM_PATTERNS_MASK) | \
	(((size) << HI_WOW_EXT_PATTERN_SIZE_SHIFT) & \
		HI_WOW_EXT_PATTERN_SIZE_MASK))

#घोषणा HI_WOW_EXT_GET_NUM_LISTS(config) \
	(((config) & HI_WOW_EXT_NUM_LIST_MASK) >> HI_WOW_EXT_NUM_LIST_SHIFT)
#घोषणा HI_WOW_EXT_GET_NUM_PATTERNS(config) \
	(((config) & HI_WOW_EXT_NUM_PATTERNS_MASK) >> \
		HI_WOW_EXT_NUM_PATTERNS_SHIFT)
#घोषणा HI_WOW_EXT_GET_PATTERN_SIZE(config) \
	(((config) & HI_WOW_EXT_PATTERN_SIZE_MASK) >> \
		HI_WOW_EXT_PATTERN_SIZE_SHIFT)

/*
 * Early allocation configuration
 * Support RAM bank configuration beक्रमe BMI करोne and this eases the memory
 * allocation at very early stage
 * Bit Range  Meaning
 * ---------  ----------------------------------
 * [0:3]      number of bank asचिन्हित to be IRAM
 * [4:15]     reserved
 * [16:31]    magic number
 *
 * Note:
 * 1. target firmware would check magic number and अगर it's a match, firmware
 *    would consider the bits[0:15] are valid and base on that to calculate
 *    the end of DRAM. Early allocation would be located at that area and
 *    may be reclaimed when necessary
 * 2. अगर no magic number is found, early allocation would happen at "_end"
 *    symbol of ROM which is located beक्रमe the app-data and might NOT be
 *    re-claimable. If this is aकरोpted, link script should keep this in
 *    mind to aव्योम data corruption.
 */
#घोषणा HI_EARLY_ALLOC_MAGIC		0x6d8a
#घोषणा HI_EARLY_ALLOC_MAGIC_MASK	0xffff0000
#घोषणा HI_EARLY_ALLOC_MAGIC_SHIFT	16
#घोषणा HI_EARLY_ALLOC_IRAM_BANKS_MASK	0x0000000f
#घोषणा HI_EARLY_ALLOC_IRAM_BANKS_SHIFT	0

#घोषणा HI_EARLY_ALLOC_VALID() \
	((((HOST_INTEREST->hi_early_alloc) & HI_EARLY_ALLOC_MAGIC_MASK) >> \
	HI_EARLY_ALLOC_MAGIC_SHIFT) == (HI_EARLY_ALLOC_MAGIC))
#घोषणा HI_EARLY_ALLOC_GET_IRAM_BANKS() \
	(((HOST_INTEREST->hi_early_alloc) & HI_EARLY_ALLOC_IRAM_BANKS_MASK) \
	>> HI_EARLY_ALLOC_IRAM_BANKS_SHIFT)

/*घातer save flag bit definitions*/
#घोषणा HI_PWR_SAVE_LPL_ENABLED   0x1
/*b1-b3 reserved*/
/*b4-b5 : dev0 LPL type : 0 - none
 *			  1- Reduce Pwr Search
 *			  2- Reduce Pwr Listen
 */
/*b6-b7 : dev1 LPL type and so on क्रम Max 8 devices*/
#घोषणा HI_PWR_SAVE_LPL_DEV0_LSB   4
#घोषणा HI_PWR_SAVE_LPL_DEV_MASK   0x3
/*घातer save related utility macros*/
#घोषणा HI_LPL_ENABLED() \
	((HOST_INTEREST->hi_pwr_save_flags & HI_PWR_SAVE_LPL_ENABLED))
#घोषणा HI_DEV_LPL_TYPE_GET(_devix) \
	(HOST_INTEREST->hi_pwr_save_flags & ((HI_PWR_SAVE_LPL_DEV_MASK) << \
	 (HI_PWR_SAVE_LPL_DEV0_LSB + (_devix) * 2)))

#घोषणा HOST_INTEREST_SMPS_IS_ALLOWED() \
	((HOST_INTEREST->hi_smps_options & HI_SMPS_ALLOW_MASK))

/* Reserve 1024 bytes क्रम extended board data */
#घोषणा QCA988X_BOARD_DATA_SZ     7168
#घोषणा QCA988X_BOARD_EXT_DATA_SZ 0

#घोषणा QCA9887_BOARD_DATA_SZ     7168
#घोषणा QCA9887_BOARD_EXT_DATA_SZ 0

#घोषणा QCA6174_BOARD_DATA_SZ     8192
#घोषणा QCA6174_BOARD_EXT_DATA_SZ 0

#घोषणा QCA9377_BOARD_DATA_SZ     QCA6174_BOARD_DATA_SZ
#घोषणा QCA9377_BOARD_EXT_DATA_SZ 0

#घोषणा QCA99X0_BOARD_DATA_SZ	  12288
#घोषणा QCA99X0_BOARD_EXT_DATA_SZ 0

/* Dual band extended board data */
#घोषणा QCA99X0_EXT_BOARD_DATA_SZ 2048
#घोषणा EXT_BOARD_ADDRESS_OFFSET 0x3000

#घोषणा QCA4019_BOARD_DATA_SZ	  12064
#घोषणा QCA4019_BOARD_EXT_DATA_SZ 0

#पूर्ण_अगर /* __TARGADDRS_H__ */
