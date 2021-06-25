<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Xilinx Zynq MPSoC Firmware layer
 *
 *  Copyright (C) 2014-2019 Xilinx
 *
 *  Michal Simek <michal.simek@xilinx.com>
 *  Davorin Mista <davorin.mista@aggios.com>
 *  Jolly Shah <jollys@xilinx.com>
 *  Rajan Vaja <rajanv@xilinx.com>
 */

#अगर_अघोषित __FIRMWARE_ZYNQMP_H__
#घोषणा __FIRMWARE_ZYNQMP_H__

#समावेश <linux/err.h>

#घोषणा ZYNQMP_PM_VERSION_MAJOR	1
#घोषणा ZYNQMP_PM_VERSION_MINOR	0

#घोषणा ZYNQMP_PM_VERSION	((ZYNQMP_PM_VERSION_MAJOR << 16) | \
					ZYNQMP_PM_VERSION_MINOR)

#घोषणा ZYNQMP_TZ_VERSION_MAJOR	1
#घोषणा ZYNQMP_TZ_VERSION_MINOR	0

#घोषणा ZYNQMP_TZ_VERSION	((ZYNQMP_TZ_VERSION_MAJOR << 16) | \
					ZYNQMP_TZ_VERSION_MINOR)

/* SMC SIP service Call Function Identअगरier Prefix */
#घोषणा PM_SIP_SVC			0xC2000000
#घोषणा PM_GET_TRUSTZONE_VERSION	0xa03
#घोषणा PM_SET_SUSPEND_MODE		0xa02
#घोषणा GET_CALLBACK_DATA		0xa01

/* Number of 32bits values in payload */
#घोषणा PAYLOAD_ARG_CNT	4U

/* Number of arguments क्रम a callback */
#घोषणा CB_ARG_CNT     4

/* Payload size (consists of callback API ID + arguments) */
#घोषणा CB_PAYLOAD_SIZE (CB_ARG_CNT + 1)

#घोषणा ZYNQMP_PM_MAX_QOS		100U

#घोषणा GSS_NUM_REGS	(4)

/* Node capabilities */
#घोषणा	ZYNQMP_PM_CAPABILITY_ACCESS	0x1U
#घोषणा	ZYNQMP_PM_CAPABILITY_CONTEXT	0x2U
#घोषणा	ZYNQMP_PM_CAPABILITY_WAKEUP	0x4U
#घोषणा	ZYNQMP_PM_CAPABILITY_UNUSABLE	0x8U

/*
 * Firmware FPGA Manager flags
 * XILINX_ZYNQMP_PM_FPGA_FULL:	FPGA full reconfiguration
 * XILINX_ZYNQMP_PM_FPGA_PARTIAL: FPGA partial reconfiguration
 */
#घोषणा XILINX_ZYNQMP_PM_FPGA_FULL	0x0U
#घोषणा XILINX_ZYNQMP_PM_FPGA_PARTIAL	BIT(0)

क्रमागत pm_api_id अणु
	PM_GET_API_VERSION = 1,
	PM_SYSTEM_SHUTDOWN = 12,
	PM_REQUEST_NODE = 13,
	PM_RELEASE_NODE = 14,
	PM_SET_REQUIREMENT = 15,
	PM_RESET_ASSERT = 17,
	PM_RESET_GET_STATUS = 18,
	PM_PM_INIT_FINALIZE = 21,
	PM_FPGA_LOAD = 22,
	PM_FPGA_GET_STATUS = 23,
	PM_GET_CHIPID = 24,
	PM_PINCTRL_REQUEST = 28,
	PM_PINCTRL_RELEASE = 29,
	PM_PINCTRL_GET_FUNCTION = 30,
	PM_PINCTRL_SET_FUNCTION = 31,
	PM_PINCTRL_CONFIG_PARAM_GET = 32,
	PM_PINCTRL_CONFIG_PARAM_SET = 33,
	PM_IOCTL = 34,
	PM_QUERY_DATA = 35,
	PM_CLOCK_ENABLE = 36,
	PM_CLOCK_DISABLE = 37,
	PM_CLOCK_GETSTATE = 38,
	PM_CLOCK_SETDIVIDER = 39,
	PM_CLOCK_GETDIVIDER = 40,
	PM_CLOCK_SETRATE = 41,
	PM_CLOCK_GETRATE = 42,
	PM_CLOCK_SETPARENT = 43,
	PM_CLOCK_GETPARENT = 44,
	PM_SECURE_AES = 47,
	PM_FEATURE_CHECK = 63,
पूर्ण;

/* PMU-FW वापस status codes */
क्रमागत pm_ret_status अणु
	XST_PM_SUCCESS = 0,
	XST_PM_NO_FEATURE = 19,
	XST_PM_INTERNAL = 2000,
	XST_PM_CONFLICT = 2001,
	XST_PM_NO_ACCESS = 2002,
	XST_PM_INVALID_NODE = 2003,
	XST_PM_DOUBLE_REQ = 2004,
	XST_PM_ABORT_SUSPEND = 2005,
	XST_PM_MULT_USER = 2008,
पूर्ण;

क्रमागत pm_ioctl_id अणु
	IOCTL_SD_DLL_RESET = 6,
	IOCTL_SET_SD_TAPDELAY = 7,
	IOCTL_SET_PLL_FRAC_MODE = 8,
	IOCTL_GET_PLL_FRAC_MODE = 9,
	IOCTL_SET_PLL_FRAC_DATA = 10,
	IOCTL_GET_PLL_FRAC_DATA = 11,
	IOCTL_WRITE_GGS = 12,
	IOCTL_READ_GGS = 13,
	IOCTL_WRITE_PGGS = 14,
	IOCTL_READ_PGGS = 15,
	/* Set healthy bit value */
	IOCTL_SET_BOOT_HEALTH_STATUS = 17,
पूर्ण;

क्रमागत pm_query_id अणु
	PM_QID_INVALID = 0,
	PM_QID_CLOCK_GET_NAME = 1,
	PM_QID_CLOCK_GET_TOPOLOGY = 2,
	PM_QID_CLOCK_GET_FIXEDFACTOR_PARAMS = 3,
	PM_QID_CLOCK_GET_PARENTS = 4,
	PM_QID_CLOCK_GET_ATTRIBUTES = 5,
	PM_QID_PINCTRL_GET_NUM_PINS = 6,
	PM_QID_PINCTRL_GET_NUM_FUNCTIONS = 7,
	PM_QID_PINCTRL_GET_NUM_FUNCTION_GROUPS = 8,
	PM_QID_PINCTRL_GET_FUNCTION_NAME = 9,
	PM_QID_PINCTRL_GET_FUNCTION_GROUPS = 10,
	PM_QID_PINCTRL_GET_PIN_GROUPS = 11,
	PM_QID_CLOCK_GET_NUM_CLOCKS = 12,
	PM_QID_CLOCK_GET_MAX_DIVISOR = 13,
पूर्ण;

क्रमागत zynqmp_pm_reset_action अणु
	PM_RESET_ACTION_RELEASE = 0,
	PM_RESET_ACTION_ASSERT = 1,
	PM_RESET_ACTION_PULSE = 2,
पूर्ण;

क्रमागत zynqmp_pm_reset अणु
	ZYNQMP_PM_RESET_START = 1000,
	ZYNQMP_PM_RESET_PCIE_CFG = ZYNQMP_PM_RESET_START,
	ZYNQMP_PM_RESET_PCIE_BRIDGE = 1001,
	ZYNQMP_PM_RESET_PCIE_CTRL = 1002,
	ZYNQMP_PM_RESET_DP = 1003,
	ZYNQMP_PM_RESET_SWDT_CRF = 1004,
	ZYNQMP_PM_RESET_AFI_FM5 = 1005,
	ZYNQMP_PM_RESET_AFI_FM4 = 1006,
	ZYNQMP_PM_RESET_AFI_FM3 = 1007,
	ZYNQMP_PM_RESET_AFI_FM2 = 1008,
	ZYNQMP_PM_RESET_AFI_FM1 = 1009,
	ZYNQMP_PM_RESET_AFI_FM0 = 1010,
	ZYNQMP_PM_RESET_GDMA = 1011,
	ZYNQMP_PM_RESET_GPU_PP1 = 1012,
	ZYNQMP_PM_RESET_GPU_PP0 = 1013,
	ZYNQMP_PM_RESET_GPU = 1014,
	ZYNQMP_PM_RESET_GT = 1015,
	ZYNQMP_PM_RESET_SATA = 1016,
	ZYNQMP_PM_RESET_ACPU3_PWRON = 1017,
	ZYNQMP_PM_RESET_ACPU2_PWRON = 1018,
	ZYNQMP_PM_RESET_ACPU1_PWRON = 1019,
	ZYNQMP_PM_RESET_ACPU0_PWRON = 1020,
	ZYNQMP_PM_RESET_APU_L2 = 1021,
	ZYNQMP_PM_RESET_ACPU3 = 1022,
	ZYNQMP_PM_RESET_ACPU2 = 1023,
	ZYNQMP_PM_RESET_ACPU1 = 1024,
	ZYNQMP_PM_RESET_ACPU0 = 1025,
	ZYNQMP_PM_RESET_DDR = 1026,
	ZYNQMP_PM_RESET_APM_FPD = 1027,
	ZYNQMP_PM_RESET_SOFT = 1028,
	ZYNQMP_PM_RESET_GEM0 = 1029,
	ZYNQMP_PM_RESET_GEM1 = 1030,
	ZYNQMP_PM_RESET_GEM2 = 1031,
	ZYNQMP_PM_RESET_GEM3 = 1032,
	ZYNQMP_PM_RESET_QSPI = 1033,
	ZYNQMP_PM_RESET_UART0 = 1034,
	ZYNQMP_PM_RESET_UART1 = 1035,
	ZYNQMP_PM_RESET_SPI0 = 1036,
	ZYNQMP_PM_RESET_SPI1 = 1037,
	ZYNQMP_PM_RESET_SDIO0 = 1038,
	ZYNQMP_PM_RESET_SDIO1 = 1039,
	ZYNQMP_PM_RESET_CAN0 = 1040,
	ZYNQMP_PM_RESET_CAN1 = 1041,
	ZYNQMP_PM_RESET_I2C0 = 1042,
	ZYNQMP_PM_RESET_I2C1 = 1043,
	ZYNQMP_PM_RESET_TTC0 = 1044,
	ZYNQMP_PM_RESET_TTC1 = 1045,
	ZYNQMP_PM_RESET_TTC2 = 1046,
	ZYNQMP_PM_RESET_TTC3 = 1047,
	ZYNQMP_PM_RESET_SWDT_CRL = 1048,
	ZYNQMP_PM_RESET_न_अंकD = 1049,
	ZYNQMP_PM_RESET_ADMA = 1050,
	ZYNQMP_PM_RESET_GPIO = 1051,
	ZYNQMP_PM_RESET_IOU_CC = 1052,
	ZYNQMP_PM_RESET_TIMESTAMP = 1053,
	ZYNQMP_PM_RESET_RPU_R50 = 1054,
	ZYNQMP_PM_RESET_RPU_R51 = 1055,
	ZYNQMP_PM_RESET_RPU_AMBA = 1056,
	ZYNQMP_PM_RESET_OCM = 1057,
	ZYNQMP_PM_RESET_RPU_PGE = 1058,
	ZYNQMP_PM_RESET_USB0_CORERESET = 1059,
	ZYNQMP_PM_RESET_USB1_CORERESET = 1060,
	ZYNQMP_PM_RESET_USB0_HIBERRESET = 1061,
	ZYNQMP_PM_RESET_USB1_HIBERRESET = 1062,
	ZYNQMP_PM_RESET_USB0_APB = 1063,
	ZYNQMP_PM_RESET_USB1_APB = 1064,
	ZYNQMP_PM_RESET_IPI = 1065,
	ZYNQMP_PM_RESET_APM_LPD = 1066,
	ZYNQMP_PM_RESET_RTC = 1067,
	ZYNQMP_PM_RESET_SYSMON = 1068,
	ZYNQMP_PM_RESET_AFI_FM6 = 1069,
	ZYNQMP_PM_RESET_LPD_SWDT = 1070,
	ZYNQMP_PM_RESET_FPD = 1071,
	ZYNQMP_PM_RESET_RPU_DBG1 = 1072,
	ZYNQMP_PM_RESET_RPU_DBG0 = 1073,
	ZYNQMP_PM_RESET_DBG_LPD = 1074,
	ZYNQMP_PM_RESET_DBG_FPD = 1075,
	ZYNQMP_PM_RESET_APLL = 1076,
	ZYNQMP_PM_RESET_DPLL = 1077,
	ZYNQMP_PM_RESET_VPLL = 1078,
	ZYNQMP_PM_RESET_IOPLL = 1079,
	ZYNQMP_PM_RESET_RPLL = 1080,
	ZYNQMP_PM_RESET_GPO3_PL_0 = 1081,
	ZYNQMP_PM_RESET_GPO3_PL_1 = 1082,
	ZYNQMP_PM_RESET_GPO3_PL_2 = 1083,
	ZYNQMP_PM_RESET_GPO3_PL_3 = 1084,
	ZYNQMP_PM_RESET_GPO3_PL_4 = 1085,
	ZYNQMP_PM_RESET_GPO3_PL_5 = 1086,
	ZYNQMP_PM_RESET_GPO3_PL_6 = 1087,
	ZYNQMP_PM_RESET_GPO3_PL_7 = 1088,
	ZYNQMP_PM_RESET_GPO3_PL_8 = 1089,
	ZYNQMP_PM_RESET_GPO3_PL_9 = 1090,
	ZYNQMP_PM_RESET_GPO3_PL_10 = 1091,
	ZYNQMP_PM_RESET_GPO3_PL_11 = 1092,
	ZYNQMP_PM_RESET_GPO3_PL_12 = 1093,
	ZYNQMP_PM_RESET_GPO3_PL_13 = 1094,
	ZYNQMP_PM_RESET_GPO3_PL_14 = 1095,
	ZYNQMP_PM_RESET_GPO3_PL_15 = 1096,
	ZYNQMP_PM_RESET_GPO3_PL_16 = 1097,
	ZYNQMP_PM_RESET_GPO3_PL_17 = 1098,
	ZYNQMP_PM_RESET_GPO3_PL_18 = 1099,
	ZYNQMP_PM_RESET_GPO3_PL_19 = 1100,
	ZYNQMP_PM_RESET_GPO3_PL_20 = 1101,
	ZYNQMP_PM_RESET_GPO3_PL_21 = 1102,
	ZYNQMP_PM_RESET_GPO3_PL_22 = 1103,
	ZYNQMP_PM_RESET_GPO3_PL_23 = 1104,
	ZYNQMP_PM_RESET_GPO3_PL_24 = 1105,
	ZYNQMP_PM_RESET_GPO3_PL_25 = 1106,
	ZYNQMP_PM_RESET_GPO3_PL_26 = 1107,
	ZYNQMP_PM_RESET_GPO3_PL_27 = 1108,
	ZYNQMP_PM_RESET_GPO3_PL_28 = 1109,
	ZYNQMP_PM_RESET_GPO3_PL_29 = 1110,
	ZYNQMP_PM_RESET_GPO3_PL_30 = 1111,
	ZYNQMP_PM_RESET_GPO3_PL_31 = 1112,
	ZYNQMP_PM_RESET_RPU_LS = 1113,
	ZYNQMP_PM_RESET_PS_ONLY = 1114,
	ZYNQMP_PM_RESET_PL = 1115,
	ZYNQMP_PM_RESET_PS_PL0 = 1116,
	ZYNQMP_PM_RESET_PS_PL1 = 1117,
	ZYNQMP_PM_RESET_PS_PL2 = 1118,
	ZYNQMP_PM_RESET_PS_PL3 = 1119,
	ZYNQMP_PM_RESET_END = ZYNQMP_PM_RESET_PS_PL3
पूर्ण;

क्रमागत zynqmp_pm_suspend_reason अणु
	SUSPEND_POWER_REQUEST = 201,
	SUSPEND_ALERT = 202,
	SUSPEND_SYSTEM_SHUTDOWN = 203,
पूर्ण;

क्रमागत zynqmp_pm_request_ack अणु
	ZYNQMP_PM_REQUEST_ACK_NO = 1,
	ZYNQMP_PM_REQUEST_ACK_BLOCKING = 2,
	ZYNQMP_PM_REQUEST_ACK_NON_BLOCKING = 3,
पूर्ण;

क्रमागत pm_node_id अणु
	NODE_SD_0 = 39,
	NODE_SD_1 = 40,
पूर्ण;

क्रमागत tap_delay_type अणु
	PM_TAPDELAY_INPUT = 0,
	PM_TAPDELAY_OUTPUT = 1,
पूर्ण;

क्रमागत dll_reset_type अणु
	PM_DLL_RESET_ASSERT = 0,
	PM_DLL_RESET_RELEASE = 1,
	PM_DLL_RESET_PULSE = 2,
पूर्ण;

क्रमागत pm_pinctrl_config_param अणु
	PM_PINCTRL_CONFIG_SLEW_RATE = 0,
	PM_PINCTRL_CONFIG_BIAS_STATUS = 1,
	PM_PINCTRL_CONFIG_PULL_CTRL = 2,
	PM_PINCTRL_CONFIG_SCHMITT_CMOS = 3,
	PM_PINCTRL_CONFIG_DRIVE_STRENGTH = 4,
	PM_PINCTRL_CONFIG_VOLTAGE_STATUS = 5,
	PM_PINCTRL_CONFIG_TRI_STATE = 6,
	PM_PINCTRL_CONFIG_MAX = 7,
पूर्ण;

क्रमागत pm_pinctrl_slew_rate अणु
	PM_PINCTRL_SLEW_RATE_FAST = 0,
	PM_PINCTRL_SLEW_RATE_SLOW = 1,
पूर्ण;

क्रमागत pm_pinctrl_bias_status अणु
	PM_PINCTRL_BIAS_DISABLE = 0,
	PM_PINCTRL_BIAS_ENABLE = 1,
पूर्ण;

क्रमागत pm_pinctrl_pull_ctrl अणु
	PM_PINCTRL_BIAS_PULL_DOWN = 0,
	PM_PINCTRL_BIAS_PULL_UP = 1,
पूर्ण;

क्रमागत pm_pinctrl_schmitt_cmos अणु
	PM_PINCTRL_INPUT_TYPE_CMOS = 0,
	PM_PINCTRL_INPUT_TYPE_SCHMITT = 1,
पूर्ण;

क्रमागत pm_pinctrl_drive_strength अणु
	PM_PINCTRL_DRIVE_STRENGTH_2MA = 0,
	PM_PINCTRL_DRIVE_STRENGTH_4MA = 1,
	PM_PINCTRL_DRIVE_STRENGTH_8MA = 2,
	PM_PINCTRL_DRIVE_STRENGTH_12MA = 3,
पूर्ण;

क्रमागत zynqmp_pm_shutकरोwn_type अणु
	ZYNQMP_PM_SHUTDOWN_TYPE_SHUTDOWN = 0,
	ZYNQMP_PM_SHUTDOWN_TYPE_RESET = 1,
	ZYNQMP_PM_SHUTDOWN_TYPE_SETSCOPE_ONLY = 2,
पूर्ण;

क्रमागत zynqmp_pm_shutकरोwn_subtype अणु
	ZYNQMP_PM_SHUTDOWN_SUBTYPE_SUBSYSTEM = 0,
	ZYNQMP_PM_SHUTDOWN_SUBTYPE_PS_ONLY = 1,
	ZYNQMP_PM_SHUTDOWN_SUBTYPE_SYSTEM = 2,
पूर्ण;

/**
 * काष्ठा zynqmp_pm_query_data - PM query data
 * @qid:	query ID
 * @arg1:	Argument 1 of query data
 * @arg2:	Argument 2 of query data
 * @arg3:	Argument 3 of query data
 */
काष्ठा zynqmp_pm_query_data अणु
	u32 qid;
	u32 arg1;
	u32 arg2;
	u32 arg3;
पूर्ण;

पूर्णांक zynqmp_pm_invoke_fn(u32 pm_api_id, u32 arg0, u32 arg1,
			u32 arg2, u32 arg3, u32 *ret_payload);

#अगर IS_REACHABLE(CONFIG_ZYNQMP_FIRMWARE)
पूर्णांक zynqmp_pm_get_api_version(u32 *version);
पूर्णांक zynqmp_pm_get_chipid(u32 *idcode, u32 *version);
पूर्णांक zynqmp_pm_query_data(काष्ठा zynqmp_pm_query_data qdata, u32 *out);
पूर्णांक zynqmp_pm_घड़ी_enable(u32 घड़ी_id);
पूर्णांक zynqmp_pm_घड़ी_disable(u32 घड़ी_id);
पूर्णांक zynqmp_pm_घड़ी_माला_लोtate(u32 घड़ी_id, u32 *state);
पूर्णांक zynqmp_pm_घड़ी_setभागider(u32 घड़ी_id, u32 भागider);
पूर्णांक zynqmp_pm_घड़ी_getभागider(u32 घड़ी_id, u32 *भागider);
पूर्णांक zynqmp_pm_घड़ी_setrate(u32 घड़ी_id, u64 rate);
पूर्णांक zynqmp_pm_घड़ी_getrate(u32 घड़ी_id, u64 *rate);
पूर्णांक zynqmp_pm_घड़ी_setparent(u32 घड़ी_id, u32 parent_id);
पूर्णांक zynqmp_pm_घड़ी_getparent(u32 घड़ी_id, u32 *parent_id);
पूर्णांक zynqmp_pm_set_pll_frac_mode(u32 clk_id, u32 mode);
पूर्णांक zynqmp_pm_get_pll_frac_mode(u32 clk_id, u32 *mode);
पूर्णांक zynqmp_pm_set_pll_frac_data(u32 clk_id, u32 data);
पूर्णांक zynqmp_pm_get_pll_frac_data(u32 clk_id, u32 *data);
पूर्णांक zynqmp_pm_set_sd_tapdelay(u32 node_id, u32 type, u32 value);
पूर्णांक zynqmp_pm_sd_dll_reset(u32 node_id, u32 type);
पूर्णांक zynqmp_pm_reset_निश्चित(स्थिर क्रमागत zynqmp_pm_reset reset,
			   स्थिर क्रमागत zynqmp_pm_reset_action निश्चित_flag);
पूर्णांक zynqmp_pm_reset_get_status(स्थिर क्रमागत zynqmp_pm_reset reset, u32 *status);
पूर्णांक zynqmp_pm_init_finalize(व्योम);
पूर्णांक zynqmp_pm_set_suspend_mode(u32 mode);
पूर्णांक zynqmp_pm_request_node(स्थिर u32 node, स्थिर u32 capabilities,
			   स्थिर u32 qos, स्थिर क्रमागत zynqmp_pm_request_ack ack);
पूर्णांक zynqmp_pm_release_node(स्थिर u32 node);
पूर्णांक zynqmp_pm_set_requirement(स्थिर u32 node, स्थिर u32 capabilities,
			      स्थिर u32 qos,
			      स्थिर क्रमागत zynqmp_pm_request_ack ack);
पूर्णांक zynqmp_pm_aes_engine(स्थिर u64 address, u32 *out);
पूर्णांक zynqmp_pm_fpga_load(स्थिर u64 address, स्थिर u32 size, स्थिर u32 flags);
पूर्णांक zynqmp_pm_fpga_get_status(u32 *value);
पूर्णांक zynqmp_pm_ग_लिखो_ggs(u32 index, u32 value);
पूर्णांक zynqmp_pm_पढ़ो_ggs(u32 index, u32 *value);
पूर्णांक zynqmp_pm_ग_लिखो_pggs(u32 index, u32 value);
पूर्णांक zynqmp_pm_पढ़ो_pggs(u32 index, u32 *value);
पूर्णांक zynqmp_pm_प्रणाली_shutकरोwn(स्थिर u32 type, स्थिर u32 subtype);
पूर्णांक zynqmp_pm_set_boot_health_status(u32 value);
पूर्णांक zynqmp_pm_pinctrl_request(स्थिर u32 pin);
पूर्णांक zynqmp_pm_pinctrl_release(स्थिर u32 pin);
पूर्णांक zynqmp_pm_pinctrl_get_function(स्थिर u32 pin, u32 *id);
पूर्णांक zynqmp_pm_pinctrl_set_function(स्थिर u32 pin, स्थिर u32 id);
पूर्णांक zynqmp_pm_pinctrl_get_config(स्थिर u32 pin, स्थिर u32 param,
				 u32 *value);
पूर्णांक zynqmp_pm_pinctrl_set_config(स्थिर u32 pin, स्थिर u32 param,
				 u32 value);
#अन्यथा
अटल अंतरभूत पूर्णांक zynqmp_pm_get_api_version(u32 *version)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_get_chipid(u32 *idcode, u32 *version)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_query_data(काष्ठा zynqmp_pm_query_data qdata,
				       u32 *out)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_घड़ी_enable(u32 घड़ी_id)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_घड़ी_disable(u32 घड़ी_id)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_घड़ी_माला_लोtate(u32 घड़ी_id, u32 *state)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_घड़ी_setभागider(u32 घड़ी_id, u32 भागider)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_घड़ी_getभागider(u32 घड़ी_id, u32 *भागider)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_घड़ी_setrate(u32 घड़ी_id, u64 rate)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_घड़ी_getrate(u32 घड़ी_id, u64 *rate)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_घड़ी_setparent(u32 घड़ी_id, u32 parent_id)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_घड़ी_getparent(u32 घड़ी_id, u32 *parent_id)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_set_pll_frac_mode(u32 clk_id, u32 mode)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_get_pll_frac_mode(u32 clk_id, u32 *mode)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_set_pll_frac_data(u32 clk_id, u32 data)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_get_pll_frac_data(u32 clk_id, u32 *data)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_set_sd_tapdelay(u32 node_id, u32 type, u32 value)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_sd_dll_reset(u32 node_id, u32 type)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_reset_निश्चित(स्थिर क्रमागत zynqmp_pm_reset reset,
					 स्थिर क्रमागत zynqmp_pm_reset_action निश्चित_flag)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_reset_get_status(स्थिर क्रमागत zynqmp_pm_reset reset,
					     u32 *status)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_init_finalize(व्योम)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_set_suspend_mode(u32 mode)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_request_node(स्थिर u32 node, स्थिर u32 capabilities,
					 स्थिर u32 qos,
					 स्थिर क्रमागत zynqmp_pm_request_ack ack)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_release_node(स्थिर u32 node)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_set_requirement(स्थिर u32 node,
					    स्थिर u32 capabilities,
					    स्थिर u32 qos,
					    स्थिर क्रमागत zynqmp_pm_request_ack ack)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_aes_engine(स्थिर u64 address, u32 *out)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_fpga_load(स्थिर u64 address, स्थिर u32 size,
				      स्थिर u32 flags)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_fpga_get_status(u32 *value)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_ग_लिखो_ggs(u32 index, u32 value)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_पढ़ो_ggs(u32 index, u32 *value)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_ग_लिखो_pggs(u32 index, u32 value)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_पढ़ो_pggs(u32 index, u32 *value)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_प्रणाली_shutकरोwn(स्थिर u32 type, स्थिर u32 subtype)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_set_boot_health_status(u32 value)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_pinctrl_request(स्थिर u32 pin)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_pinctrl_release(स्थिर u32 pin)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_pinctrl_get_function(स्थिर u32 pin, u32 *id)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_pinctrl_set_function(स्थिर u32 pin, स्थिर u32 id)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_pinctrl_get_config(स्थिर u32 pin, स्थिर u32 param,
					       u32 *value)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक zynqmp_pm_pinctrl_set_config(स्थिर u32 pin, स्थिर u32 param,
					       u32 value)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __FIRMWARE_ZYNQMP_H__ */
