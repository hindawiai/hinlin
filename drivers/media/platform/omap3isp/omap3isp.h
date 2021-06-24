<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap3isp.h
 *
 * TI OMAP3 ISP - Bus Configuration
 *
 * Copyright (C) 2011 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित __OMAP3ISP_H__
#घोषणा __OMAP3ISP_H__

क्रमागत isp_पूर्णांकerface_type अणु
	ISP_INTERFACE_PARALLEL,
	ISP_INTERFACE_CSI2A_PHY2,
	ISP_INTERFACE_CCP2B_PHY1,
	ISP_INTERFACE_CCP2B_PHY2,
	ISP_INTERFACE_CSI2C_PHY1,
पूर्ण;

/**
 * काष्ठा isp_parallel_cfg - Parallel पूर्णांकerface configuration
 * @data_lane_shअगरt: Data lane shअगरter
 *		0 - CAMEXT[13:0] -> CAM[13:0]
 *		2 - CAMEXT[13:2] -> CAM[11:0]
 *		4 - CAMEXT[13:4] -> CAM[9:0]
 *		6 - CAMEXT[13:6] -> CAM[7:0]
 * @clk_pol: Pixel घड़ी polarity
 *		0 - Sample on rising edge, 1 - Sample on falling edge
 * @hs_pol: Horizontal synchronization polarity
 *		0 - Active high, 1 - Active low
 * @vs_pol: Vertical synchronization polarity
 *		0 - Active high, 1 - Active low
 * @fld_pol: Field संकेत polarity
 *		0 - Positive, 1 - Negative
 * @data_pol: Data polarity
 *		0 - Normal, 1 - One's complement
 * @bt656: Data contain BT.656 embedded synchronization
 */
काष्ठा isp_parallel_cfg अणु
	अचिन्हित पूर्णांक data_lane_shअगरt:3;
	अचिन्हित पूर्णांक clk_pol:1;
	अचिन्हित पूर्णांक hs_pol:1;
	अचिन्हित पूर्णांक vs_pol:1;
	अचिन्हित पूर्णांक fld_pol:1;
	अचिन्हित पूर्णांक data_pol:1;
	अचिन्हित पूर्णांक bt656:1;
पूर्ण;

क्रमागत अणु
	ISP_CCP2_PHY_DATA_CLOCK = 0,
	ISP_CCP2_PHY_DATA_STROBE = 1,
पूर्ण;

क्रमागत अणु
	ISP_CCP2_MODE_MIPI = 0,
	ISP_CCP2_MODE_CCP2 = 1,
पूर्ण;

/**
 * काष्ठा isp_csiphy_lane: CCP2/CSI2 lane position and polarity
 * @pos: position of the lane
 * @pol: polarity of the lane
 */
काष्ठा isp_csiphy_lane अणु
	u8 pos;
	u8 pol;
पूर्ण;

#घोषणा ISP_CSIPHY1_NUM_DATA_LANES	1
#घोषणा ISP_CSIPHY2_NUM_DATA_LANES	2

/**
 * काष्ठा isp_csiphy_lanes_cfg - CCP2/CSI2 lane configuration
 * @data: Configuration of one or two data lanes
 * @clk: Clock lane configuration
 */
काष्ठा isp_csiphy_lanes_cfg अणु
	काष्ठा isp_csiphy_lane data[ISP_CSIPHY2_NUM_DATA_LANES];
	काष्ठा isp_csiphy_lane clk;
पूर्ण;

/**
 * काष्ठा isp_ccp2_cfg - CCP2 पूर्णांकerface configuration
 * @strobe_clk_pol: Strobe/घड़ी polarity
 *		0 - Non Inverted, 1 - Inverted
 * @crc: Enable the cyclic redundancy check
 * @ccp2_mode: Enable CCP2 compatibility mode
 *		ISP_CCP2_MODE_MIPI - MIPI-CSI1 mode
 *		ISP_CCP2_MODE_CCP2 - CCP2 mode
 * @phy_layer: Physical layer selection
 *		ISP_CCP2_PHY_DATA_CLOCK - Data/घड़ी physical layer
 *		ISP_CCP2_PHY_DATA_STROBE - Data/strobe physical layer
 * @vpclk_भाग: Video port output घड़ी control
 */
काष्ठा isp_ccp2_cfg अणु
	अचिन्हित पूर्णांक strobe_clk_pol:1;
	अचिन्हित पूर्णांक crc:1;
	अचिन्हित पूर्णांक ccp2_mode:1;
	अचिन्हित पूर्णांक phy_layer:1;
	अचिन्हित पूर्णांक vpclk_भाग:2;
	अचिन्हित पूर्णांक vp_clk_pol:1;
	काष्ठा isp_csiphy_lanes_cfg lanecfg;
पूर्ण;

/**
 * काष्ठा isp_csi2_cfg - CSI2 पूर्णांकerface configuration
 * @crc: Enable the cyclic redundancy check
 * @lanecfg: CSI-2 lane configuration
 * @num_data_lanes: The number of data lanes in use
 */
काष्ठा isp_csi2_cfg अणु
	अचिन्हित crc:1;
	काष्ठा isp_csiphy_lanes_cfg lanecfg;
	u8 num_data_lanes;
पूर्ण;

काष्ठा isp_bus_cfg अणु
	क्रमागत isp_पूर्णांकerface_type पूर्णांकerface;
	जोड़ अणु
		काष्ठा isp_parallel_cfg parallel;
		काष्ठा isp_ccp2_cfg ccp2;
		काष्ठा isp_csi2_cfg csi2;
	पूर्ण bus; /* gcc < 4.6.0 chokes on anonymous जोड़ initializers */
पूर्ण;

#पूर्ण_अगर	/* __OMAP3ISP_H__ */
