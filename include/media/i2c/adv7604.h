<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * adv7604 - Analog Devices ADV7604 video decoder driver
 *
 * Copyright 2012 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _ADV7604_
#घोषणा _ADV7604_

#समावेश <linux/types.h>

/* Analog input muxing modes (AFE रेजिस्टर 0x02, [2:0]) */
क्रमागत adv7604_ain_sel अणु
	ADV7604_AIN1_2_3_NC_SYNC_1_2 = 0,
	ADV7604_AIN4_5_6_NC_SYNC_2_1 = 1,
	ADV7604_AIN7_8_9_NC_SYNC_3_1 = 2,
	ADV7604_AIN10_11_12_NC_SYNC_4_1 = 3,
	ADV7604_AIN9_4_5_6_SYNC_2_1 = 4,
पूर्ण;

/*
 * Bus rotation and reordering. This is used to specअगरy component reordering on
 * the board and describes the components order on the bus when the ADV7604
 * outमाला_दो RGB.
 */
क्रमागत adv7604_bus_order अणु
	ADV7604_BUS_ORDER_RGB,		/* No operation	*/
	ADV7604_BUS_ORDER_GRB,		/* Swap 1-2	*/
	ADV7604_BUS_ORDER_RBG,		/* Swap 2-3	*/
	ADV7604_BUS_ORDER_BGR,		/* Swap 1-3	*/
	ADV7604_BUS_ORDER_BRG,		/* Rotate right	*/
	ADV7604_BUS_ORDER_GBR,		/* Rotate left	*/
पूर्ण;

/* Input Color Space (IO रेजिस्टर 0x02, [7:4]) */
क्रमागत adv76xx_inp_color_space अणु
	ADV76XX_INP_COLOR_SPACE_LIM_RGB = 0,
	ADV76XX_INP_COLOR_SPACE_FULL_RGB = 1,
	ADV76XX_INP_COLOR_SPACE_LIM_YCbCr_601 = 2,
	ADV76XX_INP_COLOR_SPACE_LIM_YCbCr_709 = 3,
	ADV76XX_INP_COLOR_SPACE_XVYCC_601 = 4,
	ADV76XX_INP_COLOR_SPACE_XVYCC_709 = 5,
	ADV76XX_INP_COLOR_SPACE_FULL_YCbCr_601 = 6,
	ADV76XX_INP_COLOR_SPACE_FULL_YCbCr_709 = 7,
	ADV76XX_INP_COLOR_SPACE_AUTO = 0xf,
पूर्ण;

/* Select output क्रमmat (IO रेजिस्टर 0x03, [4:2]) */
क्रमागत adv7604_op_क्रमmat_mode_sel अणु
	ADV7604_OP_FORMAT_MODE0 = 0x00,
	ADV7604_OP_FORMAT_MODE1 = 0x04,
	ADV7604_OP_FORMAT_MODE2 = 0x08,
पूर्ण;

क्रमागत adv76xx_drive_strength अणु
	ADV76XX_DR_STR_MEDIUM_LOW = 1,
	ADV76XX_DR_STR_MEDIUM_HIGH = 2,
	ADV76XX_DR_STR_HIGH = 3,
पूर्ण;

/* INT1 Configuration (IO रेजिस्टर 0x40, [1:0]) */
क्रमागत adv76xx_पूर्णांक1_config अणु
	ADV76XX_INT1_CONFIG_OPEN_DRAIN,
	ADV76XX_INT1_CONFIG_ACTIVE_LOW,
	ADV76XX_INT1_CONFIG_ACTIVE_HIGH,
	ADV76XX_INT1_CONFIG_DISABLED,
पूर्ण;

क्रमागत adv76xx_page अणु
	ADV76XX_PAGE_IO,
	ADV7604_PAGE_AVLINK,
	ADV76XX_PAGE_CEC,
	ADV76XX_PAGE_INFOFRAME,
	ADV7604_PAGE_ESDP,
	ADV7604_PAGE_DPP,
	ADV76XX_PAGE_AFE,
	ADV76XX_PAGE_REP,
	ADV76XX_PAGE_EDID,
	ADV76XX_PAGE_HDMI,
	ADV76XX_PAGE_TEST,
	ADV76XX_PAGE_CP,
	ADV7604_PAGE_VDP,
	ADV76XX_PAGE_MAX,
पूर्ण;

/* Platक्रमm dependent definition */
काष्ठा adv76xx_platक्रमm_data अणु
	/* DIS_PWRDNB: 1 अगर the PWRDNB pin is unused and unconnected */
	अचिन्हित disable_pwrdnb:1;

	/* DIS_CABLE_DET_RST: 1 अगर the 5V pins are unused and unconnected */
	अचिन्हित disable_cable_det_rst:1;

	पूर्णांक शेष_input;

	/* Analog input muxing mode */
	क्रमागत adv7604_ain_sel ain_sel;

	/* Bus rotation and reordering */
	क्रमागत adv7604_bus_order bus_order;

	/* Select output क्रमmat mode */
	क्रमागत adv7604_op_क्रमmat_mode_sel op_क्रमmat_mode_sel;

	/* Configuration of the INT1 pin */
	क्रमागत adv76xx_पूर्णांक1_config पूर्णांक1_config;

	/* IO रेजिस्टर 0x02 */
	अचिन्हित alt_gamma:1;

	/* IO रेजिस्टर 0x05 */
	अचिन्हित blank_data:1;
	अचिन्हित insert_av_codes:1;
	अचिन्हित replicate_av_codes:1;

	/* IO रेजिस्टर 0x06 */
	अचिन्हित inv_vs_pol:1;
	अचिन्हित inv_hs_pol:1;
	अचिन्हित inv_llc_pol:1;

	/* IO रेजिस्टर 0x14 */
	क्रमागत adv76xx_drive_strength dr_str_data;
	क्रमागत adv76xx_drive_strength dr_str_clk;
	क्रमागत adv76xx_drive_strength dr_str_sync;

	/* IO रेजिस्टर 0x30 */
	अचिन्हित output_bus_lsb_to_msb:1;

	/* Free run */
	अचिन्हित hdmi_मुक्त_run_mode;

	/* i2c addresses: 0 == use शेष */
	u8 i2c_addresses[ADV76XX_PAGE_MAX];
पूर्ण;

क्रमागत adv76xx_pad अणु
	ADV76XX_PAD_HDMI_PORT_A = 0,
	ADV7604_PAD_HDMI_PORT_B = 1,
	ADV7604_PAD_HDMI_PORT_C = 2,
	ADV7604_PAD_HDMI_PORT_D = 3,
	ADV7604_PAD_VGA_RGB = 4,
	ADV7604_PAD_VGA_COMP = 5,
	/* The source pad is either 1 (ADV7611) or 6 (ADV7604) */
	ADV7604_PAD_SOURCE = 6,
	ADV7611_PAD_SOURCE = 1,
	ADV76XX_PAD_MAX = 7,
पूर्ण;

#घोषणा V4L2_CID_ADV_RX_ANALOG_SAMPLING_PHASE	(V4L2_CID_DV_CLASS_BASE + 0x1000)
#घोषणा V4L2_CID_ADV_RX_FREE_RUN_COLOR_MANUAL	(V4L2_CID_DV_CLASS_BASE + 0x1001)
#घोषणा V4L2_CID_ADV_RX_FREE_RUN_COLOR		(V4L2_CID_DV_CLASS_BASE + 0x1002)

/* notअगरy events */
#घोषणा ADV76XX_HOTPLUG		1

#पूर्ण_अगर
