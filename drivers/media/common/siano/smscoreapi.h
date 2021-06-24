<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/****************************************************************

Siano Mobile Silicon, Inc.
MDTV receiver kernel modules.
Copyright (C) 2006-2008, Uri Shkolnik, Anम_से_दy Greenblat


****************************************************************/

#अगर_अघोषित __SMS_CORE_API_H__
#घोषणा __SMS_CORE_API_H__

#घोषणा pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>
#समावेश <linux/समयr.h>

#समावेश <media/media-device.h>

#समावेश <यंत्र/page.h>

#समावेश "smsir.h"

/*
 * Define the firmware names used by the driver.
 * Those should match what's used at smscoreapi.c and sms-cards.c
 * including the MODULE_FIRMWARE() macros at the end of smscoreapi.c
 */
#घोषणा SMS_FW_ATSC_DENVER         "atsc_denver.inp"
#घोषणा SMS_FW_CMMB_MING_APP       "cmmb_ming_app.inp"
#घोषणा SMS_FW_CMMB_VEGA_12MHZ     "cmmb_vega_12mhz.inp"
#घोषणा SMS_FW_CMMB_VENICE_12MHZ   "cmmb_venice_12mhz.inp"
#घोषणा SMS_FW_DVBH_RIO            "dvbh_rio.inp"
#घोषणा SMS_FW_DVB_NOVA_12MHZ_B0   "dvb_nova_12mhz_b0.inp"
#घोषणा SMS_FW_DVB_NOVA_12MHZ      "dvb_nova_12mhz.inp"
#घोषणा SMS_FW_DVB_RIO             "dvb_rio.inp"
#घोषणा SMS_FW_FM_RADIO            "fm_radio.inp"
#घोषणा SMS_FW_FM_RADIO_RIO        "fm_radio_rio.inp"
#घोषणा SMS_FW_DVBT_HCW_55XXX      "sms1xxx-hcw-55xxx-dvbt-02.fw"
#घोषणा SMS_FW_ISDBT_HCW_55XXX     "sms1xxx-hcw-55xxx-isdbt-02.fw"
#घोषणा SMS_FW_ISDBT_NOVA_12MHZ_B0 "isdbt_nova_12mhz_b0.inp"
#घोषणा SMS_FW_ISDBT_NOVA_12MHZ    "isdbt_nova_12mhz.inp"
#घोषणा SMS_FW_ISDBT_PELE          "isdbt_pele.inp"
#घोषणा SMS_FW_ISDBT_RIO           "isdbt_rio.inp"
#घोषणा SMS_FW_DVBT_NOVA_A         "sms1xxx-nova-a-dvbt-01.fw"
#घोषणा SMS_FW_DVBT_NOVA_B         "sms1xxx-nova-b-dvbt-01.fw"
#घोषणा SMS_FW_DVBT_STELLAR        "sms1xxx-stellar-dvbt-01.fw"
#घोषणा SMS_FW_TDMB_DENVER         "tdmb_denver.inp"
#घोषणा SMS_FW_TDMB_NOVA_12MHZ_B0  "tdmb_nova_12mhz_b0.inp"
#घोषणा SMS_FW_TDMB_NOVA_12MHZ     "tdmb_nova_12mhz.inp"

#घोषणा SMS_PROTOCOL_MAX_RAOUNDTRIP_MS			(10000)
#घोषणा SMS_ALLOC_ALIGNMENT				128
#घोषणा SMS_DMA_ALIGNMENT				16
#घोषणा SMS_ALIGN_ADDRESS(addr) \
	((((uपूर्णांकptr_t)(addr)) + (SMS_DMA_ALIGNMENT-1)) & ~(SMS_DMA_ALIGNMENT-1))

#घोषणा SMS_DEVICE_FAMILY1				0
#घोषणा SMS_DEVICE_FAMILY2				1
#घोषणा SMS_ROM_NO_RESPONSE				2
#घोषणा SMS_DEVICE_NOT_READY				0x8000000

क्रमागत sms_device_type_st अणु
	SMS_UNKNOWN_TYPE = -1,
	SMS_STELLAR = 0,
	SMS_NOVA_A0,
	SMS_NOVA_B0,
	SMS_VEGA,
	SMS_VENICE,
	SMS_MING,
	SMS_PELE,
	SMS_RIO,
	SMS_DENVER_1530,
	SMS_DENVER_2160,
	SMS_NUM_OF_DEVICE_TYPES
पूर्ण;

क्रमागत sms_घातer_mode_st अणु
	SMS_POWER_MODE_ACTIVE,
	SMS_POWER_MODE_SUSPENDED
पूर्ण;

काष्ठा smscore_device_t;
काष्ठा smscore_client_t;
काष्ठा smscore_buffer_t;

प्रकार पूर्णांक (*hotplug_t)(काष्ठा smscore_device_t *coredev,
			 काष्ठा device *device, पूर्णांक arrival);

प्रकार पूर्णांक (*seपंचांगode_t)(व्योम *context, पूर्णांक mode);
प्रकार व्योम (*detecपंचांगode_t)(व्योम *context, पूर्णांक *mode);
प्रकार पूर्णांक (*sendrequest_t)(व्योम *context, व्योम *buffer, माप_प्रकार size);
प्रकार पूर्णांक (*loadfirmware_t)(व्योम *context, व्योम *buffer, माप_प्रकार size);
प्रकार पूर्णांक (*preload_t)(व्योम *context);
प्रकार पूर्णांक (*postload_t)(व्योम *context);

प्रकार पूर्णांक (*onresponse_t)(व्योम *context, काष्ठा smscore_buffer_t *cb);
प्रकार व्योम (*onहटाओ_t)(व्योम *context);

काष्ठा smscore_buffer_t अणु
	/* खुला members, once passed to clients can be changed मुक्तly */
	काष्ठा list_head entry;
	पूर्णांक size;
	पूर्णांक offset;

	/* निजी members, पढ़ो-only क्रम clients */
	व्योम *p;
	dma_addr_t phys;
	अचिन्हित दीर्घ offset_in_common;
पूर्ण;

काष्ठा smsdevice_params_t अणु
	काष्ठा device	*device;
	काष्ठा usb_device	*usb_device;

	पूर्णांक				buffer_size;
	पूर्णांक				num_buffers;

	अक्षर			devpath[32];
	अचिन्हित दीर्घ	flags;

	seपंचांगode_t		seपंचांगode_handler;
	detecपंचांगode_t	detecपंचांगode_handler;
	sendrequest_t	sendrequest_handler;
	preload_t		preload_handler;
	postload_t		postload_handler;

	व्योम			*context;
	क्रमागत sms_device_type_st device_type;
पूर्ण;

काष्ठा smsclient_params_t अणु
	पूर्णांक				initial_id;
	पूर्णांक				data_type;
	onresponse_t	onresponse_handler;
	onहटाओ_t		onहटाओ_handler;
	व्योम			*context;
पूर्ण;

काष्ठा smscore_device_t अणु
	काष्ठा list_head entry;

	काष्ठा list_head clients;
	काष्ठा list_head subclients;
	spinlock_t clientslock;

	काष्ठा list_head buffers;
	spinlock_t bufferslock;
	पूर्णांक num_buffers;

	व्योम *common_buffer;
	पूर्णांक common_buffer_size;
	dma_addr_t common_buffer_phys;

	व्योम *context;
	काष्ठा device *device;
	काष्ठा usb_device *usb_device;

	अक्षर devpath[32];
	अचिन्हित दीर्घ device_flags;

	seपंचांगode_t seपंचांगode_handler;
	detecपंचांगode_t detecपंचांगode_handler;
	sendrequest_t sendrequest_handler;
	preload_t preload_handler;
	postload_t postload_handler;

	पूर्णांक mode, modes_supported;

	gfp_t gfp_buf_flags;

	/* host <--> device messages */
	काष्ठा completion version_ex_करोne, data_करोwnload_करोne, trigger_करोne;
	काष्ठा completion data_validity_करोne, device_पढ़ोy_करोne;
	काष्ठा completion init_device_करोne, reload_start_करोne, resume_करोne;
	काष्ठा completion gpio_configuration_करोne, gpio_set_level_करोne;
	काष्ठा completion gpio_get_level_करोne, ir_init_करोne;

	/* Buffer management */
	रुको_queue_head_t buffer_mng_रुकोq;

	/* GPIO */
	पूर्णांक gpio_get_res;

	/* Target hardware board */
	पूर्णांक board_id;

	/* Firmware */
	u8 *fw_buf;
	u32 fw_buf_size;
	u16 fw_version;

	/* Infrared (IR) */
	काष्ठा ir_t ir;

	/*
	 * Identअगरy अगर device is USB or not.
	 * Used by smsdvb-sysfs to know the root node क्रम debugfs
	 */
	bool is_usb_device;

	पूर्णांक led_state;

#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	काष्ठा media_device *media_dev;
#पूर्ण_अगर
पूर्ण;

/* GPIO definitions क्रम antenna frequency करोमुख्य control (SMS8021) */
#घोषणा SMS_ANTENNA_GPIO_0					1
#घोषणा SMS_ANTENNA_GPIO_1					0

क्रमागत sms_bandwidth_mode अणु
	BW_8_MHZ = 0,
	BW_7_MHZ = 1,
	BW_6_MHZ = 2,
	BW_5_MHZ = 3,
	BW_ISDBT_1SEG = 4,
	BW_ISDBT_3SEG = 5,
	BW_2_MHZ = 6,
	BW_FM_RADIO = 7,
	BW_ISDBT_13SEG = 8,
	BW_1_5_MHZ = 15,
	BW_UNKNOWN = 0xffff
पूर्ण;


#घोषणा MSG_HDR_FLAG_SPLIT_MSG				4

#घोषणा MAX_GPIO_PIN_NUMBER					31

#घोषणा HIF_TASK							11
#घोषणा HIF_TASK_SLAVE					22
#घोषणा HIF_TASK_SLAVE2					33
#घोषणा HIF_TASK_SLAVE3					44
#घोषणा SMS_HOST_LIB						150
#घोषणा DVBT_BDA_CONTROL_MSG_ID				201

#घोषणा SMS_MAX_PAYLOAD_SIZE				240
#घोषणा SMS_TUNE_TIMEOUT					500

क्रमागत msg_types अणु
	MSG_TYPE_BASE_VAL = 500,
	MSG_SMS_GET_VERSION_REQ = 503,
	MSG_SMS_GET_VERSION_RES = 504,
	MSG_SMS_MULTI_BRIDGE_CFG = 505,
	MSG_SMS_GPIO_CONFIG_REQ = 507,
	MSG_SMS_GPIO_CONFIG_RES = 508,
	MSG_SMS_GPIO_SET_LEVEL_REQ = 509,
	MSG_SMS_GPIO_SET_LEVEL_RES = 510,
	MSG_SMS_GPIO_GET_LEVEL_REQ = 511,
	MSG_SMS_GPIO_GET_LEVEL_RES = 512,
	MSG_SMS_EEPROM_BURN_IND = 513,
	MSG_SMS_LOG_ENABLE_CHANGE_REQ = 514,
	MSG_SMS_LOG_ENABLE_CHANGE_RES = 515,
	MSG_SMS_SET_MAX_TX_MSG_LEN_REQ = 516,
	MSG_SMS_SET_MAX_TX_MSG_LEN_RES = 517,
	MSG_SMS_SPI_HALFDUPLEX_TOKEN_HOST_TO_DEVICE = 518,
	MSG_SMS_SPI_HALFDUPLEX_TOKEN_DEVICE_TO_HOST = 519,
	MSG_SMS_BACKGROUND_SCAN_FLAG_CHANGE_REQ = 520,
	MSG_SMS_BACKGROUND_SCAN_FLAG_CHANGE_RES = 521,
	MSG_SMS_BACKGROUND_SCAN_SIGNAL_DETECTED_IND = 522,
	MSG_SMS_BACKGROUND_SCAN_NO_SIGNAL_IND = 523,
	MSG_SMS_CONFIGURE_RF_SWITCH_REQ = 524,
	MSG_SMS_CONFIGURE_RF_SWITCH_RES = 525,
	MSG_SMS_MRC_PATH_DISCONNECT_REQ = 526,
	MSG_SMS_MRC_PATH_DISCONNECT_RES = 527,
	MSG_SMS_RECEIVE_1SEG_THROUGH_FULLSEG_REQ = 528,
	MSG_SMS_RECEIVE_1SEG_THROUGH_FULLSEG_RES = 529,
	MSG_SMS_RECEIVE_VHF_VIA_VHF_INPUT_REQ = 530,
	MSG_SMS_RECEIVE_VHF_VIA_VHF_INPUT_RES = 531,
	MSG_WR_REG_RFT_REQ = 533,
	MSG_WR_REG_RFT_RES = 534,
	MSG_RD_REG_RFT_REQ = 535,
	MSG_RD_REG_RFT_RES = 536,
	MSG_RD_REG_ALL_RFT_REQ = 537,
	MSG_RD_REG_ALL_RFT_RES = 538,
	MSG_HELP_INT = 539,
	MSG_RUN_SCRIPT_INT = 540,
	MSG_SMS_EWS_INBAND_REQ = 541,
	MSG_SMS_EWS_INBAND_RES = 542,
	MSG_SMS_RFS_SELECT_REQ = 543,
	MSG_SMS_RFS_SELECT_RES = 544,
	MSG_SMS_MB_GET_VER_REQ = 545,
	MSG_SMS_MB_GET_VER_RES = 546,
	MSG_SMS_MB_WRITE_CFGखाता_REQ = 547,
	MSG_SMS_MB_WRITE_CFGखाता_RES = 548,
	MSG_SMS_MB_READ_CFGखाता_REQ = 549,
	MSG_SMS_MB_READ_CFGखाता_RES = 550,
	MSG_SMS_RD_MEM_REQ = 552,
	MSG_SMS_RD_MEM_RES = 553,
	MSG_SMS_WR_MEM_REQ = 554,
	MSG_SMS_WR_MEM_RES = 555,
	MSG_SMS_UPDATE_MEM_REQ = 556,
	MSG_SMS_UPDATE_MEM_RES = 557,
	MSG_SMS_ISDBT_ENABLE_FULL_PARAMS_SET_REQ = 558,
	MSG_SMS_ISDBT_ENABLE_FULL_PARAMS_SET_RES = 559,
	MSG_SMS_RF_TUNE_REQ = 561,
	MSG_SMS_RF_TUNE_RES = 562,
	MSG_SMS_ISDBT_ENABLE_HIGH_MOBILITY_REQ = 563,
	MSG_SMS_ISDBT_ENABLE_HIGH_MOBILITY_RES = 564,
	MSG_SMS_ISDBT_SB_RECEPTION_REQ = 565,
	MSG_SMS_ISDBT_SB_RECEPTION_RES = 566,
	MSG_SMS_GENERIC_EPROM_WRITE_REQ = 567,
	MSG_SMS_GENERIC_EPROM_WRITE_RES = 568,
	MSG_SMS_GENERIC_EPROM_READ_REQ = 569,
	MSG_SMS_GENERIC_EPROM_READ_RES = 570,
	MSG_SMS_EEPROM_WRITE_REQ = 571,
	MSG_SMS_EEPROM_WRITE_RES = 572,
	MSG_SMS_CUSTOM_READ_REQ = 574,
	MSG_SMS_CUSTOM_READ_RES = 575,
	MSG_SMS_CUSTOM_WRITE_REQ = 576,
	MSG_SMS_CUSTOM_WRITE_RES = 577,
	MSG_SMS_INIT_DEVICE_REQ = 578,
	MSG_SMS_INIT_DEVICE_RES = 579,
	MSG_SMS_ATSC_SET_ALL_IP_REQ = 580,
	MSG_SMS_ATSC_SET_ALL_IP_RES = 581,
	MSG_SMS_ATSC_START_ENSEMBLE_REQ = 582,
	MSG_SMS_ATSC_START_ENSEMBLE_RES = 583,
	MSG_SMS_SET_OUTPUT_MODE_REQ = 584,
	MSG_SMS_SET_OUTPUT_MODE_RES = 585,
	MSG_SMS_ATSC_IP_FILTER_GET_LIST_REQ = 586,
	MSG_SMS_ATSC_IP_FILTER_GET_LIST_RES = 587,
	MSG_SMS_SUB_CHANNEL_START_REQ = 589,
	MSG_SMS_SUB_CHANNEL_START_RES = 590,
	MSG_SMS_SUB_CHANNEL_STOP_REQ = 591,
	MSG_SMS_SUB_CHANNEL_STOP_RES = 592,
	MSG_SMS_ATSC_IP_FILTER_ADD_REQ = 593,
	MSG_SMS_ATSC_IP_FILTER_ADD_RES = 594,
	MSG_SMS_ATSC_IP_FILTER_REMOVE_REQ = 595,
	MSG_SMS_ATSC_IP_FILTER_REMOVE_RES = 596,
	MSG_SMS_ATSC_IP_FILTER_REMOVE_ALL_REQ = 597,
	MSG_SMS_ATSC_IP_FILTER_REMOVE_ALL_RES = 598,
	MSG_SMS_WAIT_CMD = 599,
	MSG_SMS_ADD_PID_FILTER_REQ = 601,
	MSG_SMS_ADD_PID_FILTER_RES = 602,
	MSG_SMS_REMOVE_PID_FILTER_REQ = 603,
	MSG_SMS_REMOVE_PID_FILTER_RES = 604,
	MSG_SMS_FAST_INFORMATION_CHANNEL_REQ = 605,
	MSG_SMS_FAST_INFORMATION_CHANNEL_RES = 606,
	MSG_SMS_DAB_CHANNEL = 607,
	MSG_SMS_GET_PID_FILTER_LIST_REQ = 608,
	MSG_SMS_GET_PID_FILTER_LIST_RES = 609,
	MSG_SMS_POWER_DOWN_REQ = 610,
	MSG_SMS_POWER_DOWN_RES = 611,
	MSG_SMS_ATSC_SLT_EXIST_IND = 612,
	MSG_SMS_ATSC_NO_SLT_IND = 613,
	MSG_SMS_GET_STATISTICS_REQ = 615,
	MSG_SMS_GET_STATISTICS_RES = 616,
	MSG_SMS_SEND_DUMP = 617,
	MSG_SMS_SCAN_START_REQ = 618,
	MSG_SMS_SCAN_START_RES = 619,
	MSG_SMS_SCAN_STOP_REQ = 620,
	MSG_SMS_SCAN_STOP_RES = 621,
	MSG_SMS_SCAN_PROGRESS_IND = 622,
	MSG_SMS_SCAN_COMPLETE_IND = 623,
	MSG_SMS_LOG_ITEM = 624,
	MSG_SMS_DAB_SUBCHANNEL_RECONFIG_REQ = 628,
	MSG_SMS_DAB_SUBCHANNEL_RECONFIG_RES = 629,
	MSG_SMS_HO_PER_SLICES_IND = 630,
	MSG_SMS_HO_INBAND_POWER_IND = 631,
	MSG_SMS_MANUAL_DEMOD_REQ = 632,
	MSG_SMS_HO_TUNE_ON_REQ = 636,
	MSG_SMS_HO_TUNE_ON_RES = 637,
	MSG_SMS_HO_TUNE_OFF_REQ = 638,
	MSG_SMS_HO_TUNE_OFF_RES = 639,
	MSG_SMS_HO_PEEK_FREQ_REQ = 640,
	MSG_SMS_HO_PEEK_FREQ_RES = 641,
	MSG_SMS_HO_PEEK_FREQ_IND = 642,
	MSG_SMS_MB_ATTEN_SET_REQ = 643,
	MSG_SMS_MB_ATTEN_SET_RES = 644,
	MSG_SMS_ENABLE_STAT_IN_I2C_REQ = 649,
	MSG_SMS_ENABLE_STAT_IN_I2C_RES = 650,
	MSG_SMS_SET_ANTENNA_CONFIG_REQ = 651,
	MSG_SMS_SET_ANTENNA_CONFIG_RES = 652,
	MSG_SMS_GET_STATISTICS_EX_REQ = 653,
	MSG_SMS_GET_STATISTICS_EX_RES = 654,
	MSG_SMS_SLEEP_RESUME_COMP_IND = 655,
	MSG_SMS_SWITCH_HOST_INTERFACE_REQ = 656,
	MSG_SMS_SWITCH_HOST_INTERFACE_RES = 657,
	MSG_SMS_DATA_DOWNLOAD_REQ = 660,
	MSG_SMS_DATA_DOWNLOAD_RES = 661,
	MSG_SMS_DATA_VALIDITY_REQ = 662,
	MSG_SMS_DATA_VALIDITY_RES = 663,
	MSG_SMS_SWDOWNLOAD_TRIGGER_REQ = 664,
	MSG_SMS_SWDOWNLOAD_TRIGGER_RES = 665,
	MSG_SMS_SWDOWNLOAD_BACKDOOR_REQ = 666,
	MSG_SMS_SWDOWNLOAD_BACKDOOR_RES = 667,
	MSG_SMS_GET_VERSION_EX_REQ = 668,
	MSG_SMS_GET_VERSION_EX_RES = 669,
	MSG_SMS_CLOCK_OUTPUT_CONFIG_REQ = 670,
	MSG_SMS_CLOCK_OUTPUT_CONFIG_RES = 671,
	MSG_SMS_I2C_SET_FREQ_REQ = 685,
	MSG_SMS_I2C_SET_FREQ_RES = 686,
	MSG_SMS_GENERIC_I2C_REQ = 687,
	MSG_SMS_GENERIC_I2C_RES = 688,
	MSG_SMS_DVBT_BDA_DATA = 693,
	MSG_SW_RELOAD_REQ = 697,
	MSG_SMS_DATA_MSG = 699,
	MSG_TABLE_UPLOAD_REQ = 700,
	MSG_TABLE_UPLOAD_RES = 701,
	MSG_SW_RELOAD_START_REQ = 702,
	MSG_SW_RELOAD_START_RES = 703,
	MSG_SW_RELOAD_EXEC_REQ = 704,
	MSG_SW_RELOAD_EXEC_RES = 705,
	MSG_SMS_SPI_INT_LINE_SET_REQ = 710,
	MSG_SMS_SPI_INT_LINE_SET_RES = 711,
	MSG_SMS_GPIO_CONFIG_EX_REQ = 712,
	MSG_SMS_GPIO_CONFIG_EX_RES = 713,
	MSG_SMS_WATCHDOG_ACT_REQ = 716,
	MSG_SMS_WATCHDOG_ACT_RES = 717,
	MSG_SMS_LOOPBACK_REQ = 718,
	MSG_SMS_LOOPBACK_RES = 719,
	MSG_SMS_RAW_CAPTURE_START_REQ = 720,
	MSG_SMS_RAW_CAPTURE_START_RES = 721,
	MSG_SMS_RAW_CAPTURE_ABORT_REQ = 722,
	MSG_SMS_RAW_CAPTURE_ABORT_RES = 723,
	MSG_SMS_RAW_CAPTURE_COMPLETE_IND = 728,
	MSG_SMS_DATA_PUMP_IND = 729,
	MSG_SMS_DATA_PUMP_REQ = 730,
	MSG_SMS_DATA_PUMP_RES = 731,
	MSG_SMS_FLASH_DL_REQ = 732,
	MSG_SMS_EXEC_TEST_1_REQ = 734,
	MSG_SMS_EXEC_TEST_1_RES = 735,
	MSG_SMS_ENABLE_TS_INTERFACE_REQ = 736,
	MSG_SMS_ENABLE_TS_INTERFACE_RES = 737,
	MSG_SMS_SPI_SET_BUS_WIDTH_REQ = 738,
	MSG_SMS_SPI_SET_BUS_WIDTH_RES = 739,
	MSG_SMS_SEND_EMM_REQ = 740,
	MSG_SMS_SEND_EMM_RES = 741,
	MSG_SMS_DISABLE_TS_INTERFACE_REQ = 742,
	MSG_SMS_DISABLE_TS_INTERFACE_RES = 743,
	MSG_SMS_IS_BUF_FREE_REQ = 744,
	MSG_SMS_IS_BUF_FREE_RES = 745,
	MSG_SMS_EXT_ANTENNA_REQ = 746,
	MSG_SMS_EXT_ANTENNA_RES = 747,
	MSG_SMS_CMMB_GET_NET_OF_FREQ_REQ_OBSOLETE = 748,
	MSG_SMS_CMMB_GET_NET_OF_FREQ_RES_OBSOLETE = 749,
	MSG_SMS_BATTERY_LEVEL_REQ = 750,
	MSG_SMS_BATTERY_LEVEL_RES = 751,
	MSG_SMS_CMMB_INJECT_TABLE_REQ_OBSOLETE = 752,
	MSG_SMS_CMMB_INJECT_TABLE_RES_OBSOLETE = 753,
	MSG_SMS_FM_RADIO_BLOCK_IND = 754,
	MSG_SMS_HOST_NOTIFICATION_IND = 755,
	MSG_SMS_CMMB_GET_CONTROL_TABLE_REQ_OBSOLETE = 756,
	MSG_SMS_CMMB_GET_CONTROL_TABLE_RES_OBSOLETE = 757,
	MSG_SMS_CMMB_GET_NETWORKS_REQ = 760,
	MSG_SMS_CMMB_GET_NETWORKS_RES = 761,
	MSG_SMS_CMMB_START_SERVICE_REQ = 762,
	MSG_SMS_CMMB_START_SERVICE_RES = 763,
	MSG_SMS_CMMB_STOP_SERVICE_REQ = 764,
	MSG_SMS_CMMB_STOP_SERVICE_RES = 765,
	MSG_SMS_CMMB_ADD_CHANNEL_FILTER_REQ = 768,
	MSG_SMS_CMMB_ADD_CHANNEL_FILTER_RES = 769,
	MSG_SMS_CMMB_REMOVE_CHANNEL_FILTER_REQ = 770,
	MSG_SMS_CMMB_REMOVE_CHANNEL_FILTER_RES = 771,
	MSG_SMS_CMMB_START_CONTROL_INFO_REQ = 772,
	MSG_SMS_CMMB_START_CONTROL_INFO_RES = 773,
	MSG_SMS_CMMB_STOP_CONTROL_INFO_REQ = 774,
	MSG_SMS_CMMB_STOP_CONTROL_INFO_RES = 775,
	MSG_SMS_ISDBT_TUNE_REQ = 776,
	MSG_SMS_ISDBT_TUNE_RES = 777,
	MSG_SMS_TRANSMISSION_IND = 782,
	MSG_SMS_PID_STATISTICS_IND = 783,
	MSG_SMS_POWER_DOWN_IND = 784,
	MSG_SMS_POWER_DOWN_CONF = 785,
	MSG_SMS_POWER_UP_IND = 786,
	MSG_SMS_POWER_UP_CONF = 787,
	MSG_SMS_POWER_MODE_SET_REQ = 790,
	MSG_SMS_POWER_MODE_SET_RES = 791,
	MSG_SMS_DEBUG_HOST_EVENT_REQ = 792,
	MSG_SMS_DEBUG_HOST_EVENT_RES = 793,
	MSG_SMS_NEW_CRYSTAL_REQ = 794,
	MSG_SMS_NEW_CRYSTAL_RES = 795,
	MSG_SMS_CONFIG_SPI_REQ = 796,
	MSG_SMS_CONFIG_SPI_RES = 797,
	MSG_SMS_I2C_SHORT_STAT_IND = 798,
	MSG_SMS_START_IR_REQ = 800,
	MSG_SMS_START_IR_RES = 801,
	MSG_SMS_IR_SAMPLES_IND = 802,
	MSG_SMS_CMMB_CA_SERVICE_IND = 803,
	MSG_SMS_SLAVE_DEVICE_DETECTED = 804,
	MSG_SMS_INTERFACE_LOCK_IND = 805,
	MSG_SMS_INTERFACE_UNLOCK_IND = 806,
	MSG_SMS_SEND_ROSUM_BUFF_REQ = 810,
	MSG_SMS_SEND_ROSUM_BUFF_RES = 811,
	MSG_SMS_ROSUM_BUFF = 812,
	MSG_SMS_SET_AES128_KEY_REQ = 815,
	MSG_SMS_SET_AES128_KEY_RES = 816,
	MSG_SMS_MBBMS_WRITE_REQ = 817,
	MSG_SMS_MBBMS_WRITE_RES = 818,
	MSG_SMS_MBBMS_READ_IND = 819,
	MSG_SMS_IQ_STREAM_START_REQ = 820,
	MSG_SMS_IQ_STREAM_START_RES = 821,
	MSG_SMS_IQ_STREAM_STOP_REQ = 822,
	MSG_SMS_IQ_STREAM_STOP_RES = 823,
	MSG_SMS_IQ_STREAM_DATA_BLOCK = 824,
	MSG_SMS_GET_EEPROM_VERSION_REQ = 825,
	MSG_SMS_GET_EEPROM_VERSION_RES = 826,
	MSG_SMS_SIGNAL_DETECTED_IND = 827,
	MSG_SMS_NO_SIGNAL_IND = 828,
	MSG_SMS_MRC_SHUTDOWN_SLAVE_REQ = 830,
	MSG_SMS_MRC_SHUTDOWN_SLAVE_RES = 831,
	MSG_SMS_MRC_BRINGUP_SLAVE_REQ = 832,
	MSG_SMS_MRC_BRINGUP_SLAVE_RES = 833,
	MSG_SMS_EXTERNAL_LNA_CTRL_REQ = 834,
	MSG_SMS_EXTERNAL_LNA_CTRL_RES = 835,
	MSG_SMS_SET_PERIODIC_STATISTICS_REQ = 836,
	MSG_SMS_SET_PERIODIC_STATISTICS_RES = 837,
	MSG_SMS_CMMB_SET_AUTO_OUTPUT_TS0_REQ = 838,
	MSG_SMS_CMMB_SET_AUTO_OUTPUT_TS0_RES = 839,
	LOCAL_TUNE = 850,
	LOCAL_IFFT_H_ICI = 851,
	MSG_RESYNC_REQ = 852,
	MSG_SMS_CMMB_GET_MRC_STATISTICS_REQ = 853,
	MSG_SMS_CMMB_GET_MRC_STATISTICS_RES = 854,
	MSG_SMS_LOG_EX_ITEM = 855,
	MSG_SMS_DEVICE_DATA_LOSS_IND = 856,
	MSG_SMS_MRC_WATCHDOG_TRIGGERED_IND = 857,
	MSG_SMS_USER_MSG_REQ = 858,
	MSG_SMS_USER_MSG_RES = 859,
	MSG_SMS_SMART_CARD_INIT_REQ = 860,
	MSG_SMS_SMART_CARD_INIT_RES = 861,
	MSG_SMS_SMART_CARD_WRITE_REQ = 862,
	MSG_SMS_SMART_CARD_WRITE_RES = 863,
	MSG_SMS_SMART_CARD_READ_IND = 864,
	MSG_SMS_TSE_ENABLE_REQ = 866,
	MSG_SMS_TSE_ENABLE_RES = 867,
	MSG_SMS_CMMB_GET_SHORT_STATISTICS_REQ = 868,
	MSG_SMS_CMMB_GET_SHORT_STATISTICS_RES = 869,
	MSG_SMS_LED_CONFIG_REQ = 870,
	MSG_SMS_LED_CONFIG_RES = 871,
	MSG_PWM_ANTENNA_REQ = 872,
	MSG_PWM_ANTENNA_RES = 873,
	MSG_SMS_CMMB_SMD_SN_REQ = 874,
	MSG_SMS_CMMB_SMD_SN_RES = 875,
	MSG_SMS_CMMB_SET_CA_CW_REQ = 876,
	MSG_SMS_CMMB_SET_CA_CW_RES = 877,
	MSG_SMS_CMMB_SET_CA_SALT_REQ = 878,
	MSG_SMS_CMMB_SET_CA_SALT_RES = 879,
	MSG_SMS_NSCD_INIT_REQ = 880,
	MSG_SMS_NSCD_INIT_RES = 881,
	MSG_SMS_NSCD_PROCESS_SECTION_REQ = 882,
	MSG_SMS_NSCD_PROCESS_SECTION_RES = 883,
	MSG_SMS_DBD_CREATE_OBJECT_REQ = 884,
	MSG_SMS_DBD_CREATE_OBJECT_RES = 885,
	MSG_SMS_DBD_CONFIGURE_REQ = 886,
	MSG_SMS_DBD_CONFIGURE_RES = 887,
	MSG_SMS_DBD_SET_KEYS_REQ = 888,
	MSG_SMS_DBD_SET_KEYS_RES = 889,
	MSG_SMS_DBD_PROCESS_HEADER_REQ = 890,
	MSG_SMS_DBD_PROCESS_HEADER_RES = 891,
	MSG_SMS_DBD_PROCESS_DATA_REQ = 892,
	MSG_SMS_DBD_PROCESS_DATA_RES = 893,
	MSG_SMS_DBD_PROCESS_GET_DATA_REQ = 894,
	MSG_SMS_DBD_PROCESS_GET_DATA_RES = 895,
	MSG_SMS_NSCD_OPEN_SESSION_REQ = 896,
	MSG_SMS_NSCD_OPEN_SESSION_RES = 897,
	MSG_SMS_SEND_HOST_DATA_TO_DEMUX_REQ = 898,
	MSG_SMS_SEND_HOST_DATA_TO_DEMUX_RES = 899,
	MSG_LAST_MSG_TYPE = 900,
पूर्ण;

#घोषणा SMS_INIT_MSG_EX(ptr, type, src, dst, len) करो अणु \
	(ptr)->msg_type = type; \
	(ptr)->msg_src_id = src; \
	(ptr)->msg_dst_id = dst; \
	(ptr)->msg_length = len; \
	(ptr)->msg_flags = 0; \
पूर्ण जबतक (0)

#घोषणा SMS_INIT_MSG(ptr, type, len) \
	SMS_INIT_MSG_EX(ptr, type, 0, HIF_TASK, len)

क्रमागत SMS_DVB3_EVENTS अणु
	DVB3_EVENT_INIT = 0,
	DVB3_EVENT_SLEEP,
	DVB3_EVENT_HOTPLUG,
	DVB3_EVENT_FE_LOCK,
	DVB3_EVENT_FE_UNLOCK,
	DVB3_EVENT_UNC_OK,
	DVB3_EVENT_UNC_ERR
पूर्ण;

क्रमागत SMS_DEVICE_MODE अणु
	DEVICE_MODE_NONE = -1,
	DEVICE_MODE_DVBT = 0,
	DEVICE_MODE_DVBH,
	DEVICE_MODE_DAB_TDMB,
	DEVICE_MODE_DAB_TDMB_DABIP,
	DEVICE_MODE_DVBT_BDA,
	DEVICE_MODE_ISDBT,
	DEVICE_MODE_ISDBT_BDA,
	DEVICE_MODE_CMMB,
	DEVICE_MODE_RAW_TUNER,
	DEVICE_MODE_FM_RADIO,
	DEVICE_MODE_FM_RADIO_BDA,
	DEVICE_MODE_ATSC,
	DEVICE_MODE_MAX,
पूर्ण;

काष्ठा sms_msg_hdr अणु
	u16	msg_type;
	u8	msg_src_id;
	u8	msg_dst_id;
	u16	msg_length; /* length of entire message, including header */
	u16	msg_flags;
पूर्ण;

काष्ठा sms_msg_data अणु
	काष्ठा sms_msg_hdr x_msg_header;
	u32 msg_data[1];
पूर्ण;

काष्ठा sms_msg_data2 अणु
	काष्ठा sms_msg_hdr x_msg_header;
	u32 msg_data[2];
पूर्ण;

काष्ठा sms_msg_data4 अणु
	काष्ठा sms_msg_hdr x_msg_header;
	u32 msg_data[4];
पूर्ण;

काष्ठा sms_data_करोwnload अणु
	काष्ठा sms_msg_hdr	x_msg_header;
	u32			mem_addr;
	u8			payload[SMS_MAX_PAYLOAD_SIZE];
पूर्ण;

काष्ठा sms_version_res अणु
	काष्ठा sms_msg_hdr	x_msg_header;

	u16		chip_model; /* e.g. 0x1102 क्रम SMS-1102 "Nova" */
	u8		step; /* 0 - step A */
	u8		metal_fix; /* 0 - Metal 0 */

	/* firmware_id 0xFF अगर ROM, otherwise the
	 * value indicated by SMSHOSTLIB_DEVICE_MODES_E */
	u8 firmware_id;
	/* supported_protocols Bitwise OR combination of
					     * supported protocols */
	u8 supported_protocols;

	u8		version_major;
	u8		version_minor;
	u8		version_patch;
	u8		version_field_patch;

	u8		rom_ver_major;
	u8		rom_ver_minor;
	u8		rom_ver_patch;
	u8		rom_ver_field_patch;

	u8		TextLabel[34];
पूर्ण;

काष्ठा sms_firmware अणु
	u32			check_sum;
	u32			length;
	u32			start_address;
	u8			payload[1];
पूर्ण;

/* statistics inक्रमmation वापसed as response क्रम
 * SmsHostApiGetstatistics_Req */
काष्ठा sms_stats अणु
	u32 reserved;		/* reserved */

	/* Common parameters */
	u32 is_rf_locked;		/* 0 - not locked, 1 - locked */
	u32 is_demod_locked;	/* 0 - not locked, 1 - locked */
	u32 is_बाह्यal_lna_on;	/* 0 - बाह्यal LNA off, 1 - बाह्यal LNA on */

	/* Reception quality */
	s32 SNR;		/* dB */
	u32 ber;		/* Post Viterbi ber [1E-5] */
	u32 FIB_CRC;		/* CRC errors percentage, valid only क्रम DAB */
	u32 ts_per;		/* Transport stream PER,
	0xFFFFFFFF indicate N/A, valid only क्रम DVB-T/H */
	u32 MFER;		/* DVB-H frame error rate in percentage,
	0xFFFFFFFF indicate N/A, valid only क्रम DVB-H */
	s32 RSSI;		/* dBm */
	s32 in_band_pwr;		/* In band घातer in dBM */
	s32 carrier_offset;	/* Carrier Offset in bin/1024 */

	/* Transmission parameters */
	u32 frequency;		/* frequency in Hz */
	u32 bandwidth;		/* bandwidth in MHz, valid only क्रम DVB-T/H */
	u32 transmission_mode;	/* Transmission Mode, क्रम DAB modes 1-4,
	क्रम DVB-T/H FFT mode carriers in Kilos */
	u32 modem_state;		/* from SMSHOSTLIB_DVB_MODEM_STATE_ET,
	valid only क्रम DVB-T/H */
	u32 guard_पूर्णांकerval;	/* Guard Interval from
	SMSHOSTLIB_GUARD_INTERVALS_ET,	valid only क्रम DVB-T/H */
	u32 code_rate;		/* Code Rate from SMSHOSTLIB_CODE_RATE_ET,
	valid only क्रम DVB-T/H */
	u32 lp_code_rate;		/* Low Priority Code Rate from
	SMSHOSTLIB_CODE_RATE_ET, valid only क्रम DVB-T/H */
	u32 hierarchy;		/* hierarchy from SMSHOSTLIB_HIERARCHY_ET,
	valid only क्रम DVB-T/H */
	u32 स्थिरellation;	/* स्थिरellation from
	SMSHOSTLIB_CONSTELLATION_ET, valid only क्रम DVB-T/H */

	/* Burst parameters, valid only क्रम DVB-H */
	u32 burst_size;		/* Current burst size in bytes,
	valid only क्रम DVB-H */
	u32 burst_duration;	/* Current burst duration in mSec,
	valid only क्रम DVB-H */
	u32 burst_cycle_समय;	/* Current burst cycle समय in mSec,
	valid only क्रम DVB-H */
	u32 calc_burst_cycle_समय;/* Current burst cycle समय in mSec,
	as calculated by demodulator, valid only क्रम DVB-H */
	u32 num_of_rows;		/* Number of rows in MPE table,
	valid only क्रम DVB-H */
	u32 num_of_padd_cols;	/* Number of padding columns in MPE table,
	valid only क्रम DVB-H */
	u32 num_of_punct_cols;	/* Number of puncturing columns in MPE table,
	valid only क्रम DVB-H */
	u32 error_ts_packets;	/* Number of erroneous
	transport-stream packets */
	u32 total_ts_packets;	/* Total number of transport-stream packets */
	u32 num_of_valid_mpe_tlbs;	/* Number of MPE tables which करो not include
	errors after MPE RS decoding */
	u32 num_of_invalid_mpe_tlbs;/* Number of MPE tables which include errors
	after MPE RS decoding */
	u32 num_of_corrected_mpe_tlbs;/* Number of MPE tables which were
	corrected by MPE RS decoding */
	/* Common params */
	u32 ber_error_count;	/* Number of erroneous SYNC bits. */
	u32 ber_bit_count;	/* Total number of SYNC bits. */

	/* Interface inक्रमmation */
	u32 sms_to_host_tx_errors;	/* Total number of transmission errors. */

	/* DAB/T-DMB */
	u32 pre_ber;		/* DAB/T-DMB only: Pre Viterbi ber [1E-5] */

	/* DVB-H TPS parameters */
	u32 cell_id;		/* TPS Cell ID in bits 15..0, bits 31..16 zero;
	 अगर set to 0xFFFFFFFF cell_id not yet recovered */
	u32 dvbh_srv_ind_hp;	/* DVB-H service indication info, bit 1 -
	Time Slicing indicator, bit 0 - MPE-FEC indicator */
	u32 dvbh_srv_ind_lp;	/* DVB-H service indication info, bit 1 -
	Time Slicing indicator, bit 0 - MPE-FEC indicator */

	u32 num_mpe_received;	/* DVB-H, Num MPE section received */

	u32 reservedFields[10];	/* reserved */
पूर्ण;

काष्ठा sms_msg_statistics_info अणु
	u32 request_result;

	काष्ठा sms_stats stat;

	/* Split the calc of the SNR in DAB */
	u32 संकेत; /* dB */
	u32 noise; /* dB */

पूर्ण;

काष्ठा sms_isdbt_layer_stats अणु
	/* Per-layer inक्रमmation */
	u32 code_rate; /* Code Rate from SMSHOSTLIB_CODE_RATE_ET,
		       * 255 means layer करोes not exist */
	u32 स्थिरellation; /* स्थिरellation from SMSHOSTLIB_CONSTELLATION_ET,
			    * 255 means layer करोes not exist */
	u32 ber; /* Post Viterbi ber [1E-5], 0xFFFFFFFF indicate N/A */
	u32 ber_error_count; /* Post Viterbi Error Bits Count */
	u32 ber_bit_count; /* Post Viterbi Total Bits Count */
	u32 pre_ber; /* Pre Viterbi ber [1E-5], 0xFFFFFFFF indicate N/A */
	u32 ts_per; /* Transport stream PER [%], 0xFFFFFFFF indicate N/A */
	u32 error_ts_packets; /* Number of erroneous transport-stream packets */
	u32 total_ts_packets; /* Total number of transport-stream packets */
	u32 ti_ldepth_i; /* Time पूर्णांकerleaver depth I parameter,
			* 255 means layer करोes not exist */
	u32 number_of_segments; /* Number of segments in layer A,
			       * 255 means layer करोes not exist */
	u32 पंचांगcc_errors; /* TMCC errors */
पूर्ण;

काष्ठा sms_isdbt_stats अणु
	u32 statistics_type; /* Enumerator identअगरying the type of the
				* काष्ठाure.  Values are the same as
				* SMSHOSTLIB_DEVICE_MODES_E
				*
				* This field MUST always be first in any
				* statistics काष्ठाure */

	u32 full_size; /* Total size of the काष्ठाure वापसed by the modem.
		       * If the size requested by the host is smaller than
		       * full_size, the काष्ठा will be truncated */

	/* Common parameters */
	u32 is_rf_locked; /* 0 - not locked, 1 - locked */
	u32 is_demod_locked; /* 0 - not locked, 1 - locked */
	u32 is_बाह्यal_lna_on; /* 0 - बाह्यal LNA off, 1 - बाह्यal LNA on */

	/* Reception quality */
	s32  SNR; /* dB */
	s32  RSSI; /* dBm */
	s32  in_band_pwr; /* In band घातer in dBM */
	s32  carrier_offset; /* Carrier Offset in Hz */

	/* Transmission parameters */
	u32 frequency; /* frequency in Hz */
	u32 bandwidth; /* bandwidth in MHz */
	u32 transmission_mode; /* ISDB-T transmission mode */
	u32 modem_state; /* 0 - Acquisition, 1 - Locked */
	u32 guard_पूर्णांकerval; /* Guard Interval, 1 भागided by value */
	u32 प्रणाली_type; /* ISDB-T प्रणाली type (ISDB-T / ISDB-Tsb) */
	u32 partial_reception; /* TRUE - partial reception, FALSE otherwise */
	u32 num_of_layers; /* Number of ISDB-T layers in the network */

	/* Per-layer inक्रमmation */
	/* Layers A, B and C */
	काष्ठा sms_isdbt_layer_stats	layer_info[3];
	/* Per-layer statistics, see sms_isdbt_layer_stats */

	/* Interface inक्रमmation */
	u32 sms_to_host_tx_errors; /* Total number of transmission errors. */
पूर्ण;

काष्ठा sms_isdbt_stats_ex अणु
	u32 statistics_type; /* Enumerator identअगरying the type of the
				* काष्ठाure.  Values are the same as
				* SMSHOSTLIB_DEVICE_MODES_E
				*
				* This field MUST always be first in any
				* statistics काष्ठाure */

	u32 full_size; /* Total size of the काष्ठाure वापसed by the modem.
		       * If the size requested by the host is smaller than
		       * full_size, the काष्ठा will be truncated */

	/* Common parameters */
	u32 is_rf_locked; /* 0 - not locked, 1 - locked */
	u32 is_demod_locked; /* 0 - not locked, 1 - locked */
	u32 is_बाह्यal_lna_on; /* 0 - बाह्यal LNA off, 1 - बाह्यal LNA on */

	/* Reception quality */
	s32  SNR; /* dB */
	s32  RSSI; /* dBm */
	s32  in_band_pwr; /* In band घातer in dBM */
	s32  carrier_offset; /* Carrier Offset in Hz */

	/* Transmission parameters */
	u32 frequency; /* frequency in Hz */
	u32 bandwidth; /* bandwidth in MHz */
	u32 transmission_mode; /* ISDB-T transmission mode */
	u32 modem_state; /* 0 - Acquisition, 1 - Locked */
	u32 guard_पूर्णांकerval; /* Guard Interval, 1 भागided by value */
	u32 प्रणाली_type; /* ISDB-T प्रणाली type (ISDB-T / ISDB-Tsb) */
	u32 partial_reception; /* TRUE - partial reception, FALSE otherwise */
	u32 num_of_layers; /* Number of ISDB-T layers in the network */

	u32 segment_number; /* Segment number क्रम ISDB-Tsb */
	u32 tune_bw;	   /* Tuned bandwidth - BW_ISDBT_1SEG / BW_ISDBT_3SEG */

	/* Per-layer inक्रमmation */
	/* Layers A, B and C */
	काष्ठा sms_isdbt_layer_stats	layer_info[3];
	/* Per-layer statistics, see sms_isdbt_layer_stats */

	/* Interface inक्रमmation */
	u32 reserved1;    /* Was sms_to_host_tx_errors - obsolete . */
 /* Proprietary inक्रमmation */
	u32 ext_antenna;    /* Obsolete field. */
	u32 reception_quality;
	u32 ews_alert_active;   /* संकेतs अगर EWS alert is currently on */
	u32 lna_on_off;	/* Internal LNA state: 0: OFF, 1: ON */

	u32 rf_agc_level;	 /* RF AGC Level [linear units], full gain = 65535 (20dB) */
	u32 bb_agc_level;    /* Baseband AGC level [linear units], full gain = 65535 (71.5dB) */
	u32 fw_errors_counter;   /* Application errors - should be always zero */
	u8 FwErrorsHistoryArr[8]; /* Last FW errors IDs - first is most recent, last is oldest */

	s32  MRC_SNR;     /* dB */
	u32 snr_full_res;    /* dB x 65536 */
	u32 reserved4[4];
पूर्ण;


काष्ठा sms_pid_stats_data अणु
	काष्ठा PID_BURST_S अणु
		u32 size;
		u32 padding_cols;
		u32 punct_cols;
		u32 duration;
		u32 cycle;
		u32 calc_cycle;
	पूर्ण burst;

	u32 tot_tbl_cnt;
	u32 invalid_tbl_cnt;
	u32 tot_cor_tbl;
पूर्ण;

काष्ठा sms_pid_data अणु
	u32 pid;
	u32 num_rows;
	काष्ठा sms_pid_stats_data pid_statistics;
पूर्ण;

#घोषणा CORRECT_STAT_RSSI(_stat) ((_stat).RSSI *= -1)
#घोषणा CORRECT_STAT_BANDWIDTH(_stat) (_stat.bandwidth = 8 - _stat.bandwidth)
#घोषणा CORRECT_STAT_TRANSMISSON_MODE(_stat) \
	अगर (_stat.transmission_mode == 0) \
		_stat.transmission_mode = 2; \
	अन्यथा अगर (_stat.transmission_mode == 1) \
		_stat.transmission_mode = 8; \
		अन्यथा \
			_stat.transmission_mode = 4;

काष्ठा sms_tx_stats अणु
	u32 frequency;		/* frequency in Hz */
	u32 bandwidth;		/* bandwidth in MHz */
	u32 transmission_mode;	/* FFT mode carriers in Kilos */
	u32 guard_पूर्णांकerval;	/* Guard Interval from
	SMSHOSTLIB_GUARD_INTERVALS_ET */
	u32 code_rate;		/* Code Rate from SMSHOSTLIB_CODE_RATE_ET */
	u32 lp_code_rate;		/* Low Priority Code Rate from
	SMSHOSTLIB_CODE_RATE_ET */
	u32 hierarchy;		/* hierarchy from SMSHOSTLIB_HIERARCHY_ET */
	u32 स्थिरellation;	/* स्थिरellation from
	SMSHOSTLIB_CONSTELLATION_ET */

	/* DVB-H TPS parameters */
	u32 cell_id;		/* TPS Cell ID in bits 15..0, bits 31..16 zero;
	 अगर set to 0xFFFFFFFF cell_id not yet recovered */
	u32 dvbh_srv_ind_hp;	/* DVB-H service indication info, bit 1 -
	 Time Slicing indicator, bit 0 - MPE-FEC indicator */
	u32 dvbh_srv_ind_lp;	/* DVB-H service indication info, bit 1 -
	 Time Slicing indicator, bit 0 - MPE-FEC indicator */
	u32 is_demod_locked;	/* 0 - not locked, 1 - locked */
पूर्ण;

काष्ठा sms_rx_stats अणु
	u32 is_rf_locked;		/* 0 - not locked, 1 - locked */
	u32 is_demod_locked;	/* 0 - not locked, 1 - locked */
	u32 is_बाह्यal_lna_on;	/* 0 - बाह्यal LNA off, 1 - बाह्यal LNA on */

	u32 modem_state;		/* from SMSHOSTLIB_DVB_MODEM_STATE_ET */
	s32 SNR;		/* dB */
	u32 ber;		/* Post Viterbi ber [1E-5] */
	u32 ber_error_count;	/* Number of erroneous SYNC bits. */
	u32 ber_bit_count;	/* Total number of SYNC bits. */
	u32 ts_per;		/* Transport stream PER,
	0xFFFFFFFF indicate N/A */
	u32 MFER;		/* DVB-H frame error rate in percentage,
	0xFFFFFFFF indicate N/A, valid only क्रम DVB-H */
	s32 RSSI;		/* dBm */
	s32 in_band_pwr;		/* In band घातer in dBM */
	s32 carrier_offset;	/* Carrier Offset in bin/1024 */
	u32 error_ts_packets;	/* Number of erroneous
	transport-stream packets */
	u32 total_ts_packets;	/* Total number of transport-stream packets */

	s32 MRC_SNR;		/* dB */
	s32 MRC_RSSI;		/* dBm */
	s32 mrc_in_band_pwr;	/* In band घातer in dBM */
पूर्ण;

काष्ठा sms_rx_stats_ex अणु
	u32 is_rf_locked;		/* 0 - not locked, 1 - locked */
	u32 is_demod_locked;	/* 0 - not locked, 1 - locked */
	u32 is_बाह्यal_lna_on;	/* 0 - बाह्यal LNA off, 1 - बाह्यal LNA on */

	u32 modem_state;		/* from SMSHOSTLIB_DVB_MODEM_STATE_ET */
	s32 SNR;		/* dB */
	u32 ber;		/* Post Viterbi ber [1E-5] */
	u32 ber_error_count;	/* Number of erroneous SYNC bits. */
	u32 ber_bit_count;	/* Total number of SYNC bits. */
	u32 ts_per;		/* Transport stream PER,
	0xFFFFFFFF indicate N/A */
	u32 MFER;		/* DVB-H frame error rate in percentage,
	0xFFFFFFFF indicate N/A, valid only क्रम DVB-H */
	s32 RSSI;		/* dBm */
	s32 in_band_pwr;		/* In band घातer in dBM */
	s32 carrier_offset;	/* Carrier Offset in bin/1024 */
	u32 error_ts_packets;	/* Number of erroneous
	transport-stream packets */
	u32 total_ts_packets;	/* Total number of transport-stream packets */

	s32  ref_dev_ppm;
	s32  freq_dev_hz;

	s32 MRC_SNR;		/* dB */
	s32 MRC_RSSI;		/* dBm */
	s32 mrc_in_band_pwr;	/* In band घातer in dBM */
पूर्ण;

#घोषणा	SRVM_MAX_PID_FILTERS 8

/* statistics inक्रमmation वापसed as response क्रम
 * SmsHostApiGetstatisticsEx_Req क्रम DVB applications, SMS1100 and up */
काष्ठा sms_stats_dvb अणु
	/* Reception */
	काष्ठा sms_rx_stats reception_data;

	/* Transmission parameters */
	काष्ठा sms_tx_stats transmission_data;

	/* Burst parameters, valid only क्रम DVB-H */
	काष्ठा sms_pid_data pid_data[SRVM_MAX_PID_FILTERS];
पूर्ण;

/* statistics inक्रमmation वापसed as response क्रम
 * SmsHostApiGetstatisticsEx_Req क्रम DVB applications, SMS1100 and up */
काष्ठा sms_stats_dvb_ex अणु
	/* Reception */
	काष्ठा sms_rx_stats_ex reception_data;

	/* Transmission parameters */
	काष्ठा sms_tx_stats transmission_data;

	/* Burst parameters, valid only क्रम DVB-H */
	काष्ठा sms_pid_data pid_data[SRVM_MAX_PID_FILTERS];
पूर्ण;

काष्ठा sms_srvm_संकेत_status अणु
	u32 result;
	u32 snr;
	u32 ts_packets;
	u32 ets_packets;
	u32 स्थिरellation;
	u32 hp_code;
	u32 tps_srv_ind_lp;
	u32 tps_srv_ind_hp;
	u32 cell_id;
	u32 reason;

	s32 in_band_घातer;
	u32 request_id;
पूर्ण;

काष्ठा sms_i2c_req अणु
	u32	device_address; /* I2c device address */
	u32	ग_लिखो_count; /* number of bytes to ग_लिखो */
	u32	पढ़ो_count; /* number of bytes to पढ़ो */
	u8	Data[1];
पूर्ण;

काष्ठा sms_i2c_res अणु
	u32	status; /* non-zero value in हाल of failure */
	u32	पढ़ो_count; /* number of bytes पढ़ो */
	u8	Data[1];
पूर्ण;


काष्ठा smscore_config_gpio अणु
#घोषणा SMS_GPIO_सूचीECTION_INPUT  0
#घोषणा SMS_GPIO_सूचीECTION_OUTPUT 1
	u8 direction;

#घोषणा SMS_GPIO_PULLUPDOWN_NONE     0
#घोषणा SMS_GPIO_PULLUPDOWN_PULLDOWN 1
#घोषणा SMS_GPIO_PULLUPDOWN_PULLUP   2
#घोषणा SMS_GPIO_PULLUPDOWN_KEEPER   3
	u8 pullupकरोwn;

#घोषणा SMS_GPIO_INPUTCHARACTERISTICS_NORMAL  0
#घोषणा SMS_GPIO_INPUTCHARACTERISTICS_SCHMITT 1
	u8 inअक्षर_दोacteristics;

	/* 10xx */
#घोषणा SMS_GPIO_OUTPUT_SLEW_RATE_FAST 0
#घोषणा SMS_GPIO_OUTPUT_SLEW_WRATE_SLOW 1

	/* 11xx */
#घोषणा SMS_GPIO_OUTPUT_SLEW_RATE_0_45_V_NS	0
#घोषणा SMS_GPIO_OUTPUT_SLEW_RATE_0_9_V_NS	1
#घोषणा SMS_GPIO_OUTPUT_SLEW_RATE_1_7_V_NS	2
#घोषणा SMS_GPIO_OUTPUT_SLEW_RATE_3_3_V_NS	3

	u8 outमाला_दोlewrate;

	/* 10xx */
#घोषणा SMS_GPIO_OUTPUTDRIVING_S_4mA  0
#घोषणा SMS_GPIO_OUTPUTDRIVING_S_8mA  1
#घोषणा SMS_GPIO_OUTPUTDRIVING_S_12mA 2
#घोषणा SMS_GPIO_OUTPUTDRIVING_S_16mA 3

	/* 11xx*/
#घोषणा SMS_GPIO_OUTPUTDRIVING_1_5mA	0
#घोषणा SMS_GPIO_OUTPUTDRIVING_2_8mA	1
#घोषणा SMS_GPIO_OUTPUTDRIVING_4mA	2
#घोषणा SMS_GPIO_OUTPUTDRIVING_7mA	3
#घोषणा SMS_GPIO_OUTPUTDRIVING_10mA	4
#घोषणा SMS_GPIO_OUTPUTDRIVING_11mA	5
#घोषणा SMS_GPIO_OUTPUTDRIVING_14mA	6
#घोषणा SMS_GPIO_OUTPUTDRIVING_16mA	7

	u8 outputdriving;
पूर्ण;

अक्षर *smscore_translate_msg(क्रमागत msg_types msgtype);

बाह्य पूर्णांक smscore_registry_geपंचांगode(अक्षर *devpath);

बाह्य पूर्णांक smscore_रेजिस्टर_hotplug(hotplug_t hotplug);
बाह्य व्योम smscore_unरेजिस्टर_hotplug(hotplug_t hotplug);

बाह्य पूर्णांक smscore_रेजिस्टर_device(काष्ठा smsdevice_params_t *params,
				   काष्ठा smscore_device_t **coredev,
				   gfp_t gfp_buf_flags,
				   व्योम *mdev);
बाह्य व्योम smscore_unरेजिस्टर_device(काष्ठा smscore_device_t *coredev);

बाह्य पूर्णांक smscore_start_device(काष्ठा smscore_device_t *coredev);
बाह्य पूर्णांक smscore_load_firmware(काष्ठा smscore_device_t *coredev,
				 अक्षर *filename,
				 loadfirmware_t loadfirmware_handler);

बाह्य पूर्णांक smscore_set_device_mode(काष्ठा smscore_device_t *coredev, पूर्णांक mode);
बाह्य पूर्णांक smscore_get_device_mode(काष्ठा smscore_device_t *coredev);

बाह्य पूर्णांक smscore_रेजिस्टर_client(काष्ठा smscore_device_t *coredev,
				    काष्ठा smsclient_params_t *params,
				    काष्ठा smscore_client_t **client);
बाह्य व्योम smscore_unरेजिस्टर_client(काष्ठा smscore_client_t *client);

बाह्य पूर्णांक smsclient_sendrequest(काष्ठा smscore_client_t *client,
				 व्योम *buffer, माप_प्रकार size);
बाह्य व्योम smscore_onresponse(काष्ठा smscore_device_t *coredev,
			       काष्ठा smscore_buffer_t *cb);

बाह्य पूर्णांक smscore_get_common_buffer_size(काष्ठा smscore_device_t *coredev);
बाह्य पूर्णांक smscore_map_common_buffer(काष्ठा smscore_device_t *coredev,
				      काष्ठा vm_area_काष्ठा *vma);
बाह्य पूर्णांक smscore_send_fw_file(काष्ठा smscore_device_t *coredev,
				u8 *ufwbuf, पूर्णांक size);

बाह्य
काष्ठा smscore_buffer_t *smscore_getbuffer(काष्ठा smscore_device_t *coredev);
बाह्य व्योम smscore_putbuffer(काष्ठा smscore_device_t *coredev,
			      काष्ठा smscore_buffer_t *cb);

/* old GPIO management */
पूर्णांक smscore_configure_gpio(काष्ठा smscore_device_t *coredev, u32 pin,
			   काष्ठा smscore_config_gpio *pinconfig);
पूर्णांक smscore_set_gpio(काष्ठा smscore_device_t *coredev, u32 pin, पूर्णांक level);

/* new GPIO management */
बाह्य पूर्णांक smscore_gpio_configure(काष्ठा smscore_device_t *coredev, u8 pin_num,
		काष्ठा smscore_config_gpio *p_gpio_config);
बाह्य पूर्णांक smscore_gpio_set_level(काष्ठा smscore_device_t *coredev, u8 pin_num,
		u8 new_level);
बाह्य पूर्णांक smscore_gpio_get_level(काष्ठा smscore_device_t *coredev, u8 pin_num,
		u8 *level);

व्योम smscore_set_board_id(काष्ठा smscore_device_t *core, पूर्णांक id);
पूर्णांक smscore_get_board_id(काष्ठा smscore_device_t *core);

पूर्णांक smscore_led_state(काष्ठा smscore_device_t *core, पूर्णांक led);


/* ------------------------------------------------------------------------ */

#पूर्ण_अगर /* __SMS_CORE_API_H__ */
