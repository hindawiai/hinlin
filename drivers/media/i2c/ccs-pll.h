<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/media/i2c/ccs-pll.h
 *
 * Generic MIPI CCS/SMIA/SMIA++ PLL calculator
 *
 * Copyright (C) 2020 Intel Corporation
 * Copyright (C) 2012 Nokia Corporation
 * Contact: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 */

#अगर_अघोषित CCS_PLL_H
#घोषणा CCS_PLL_H

#समावेश <linux/bits.h>

/* CSI-2 or CCP-2 */
#घोषणा CCS_PLL_BUS_TYPE_CSI2_DPHY				0x00
#घोषणा CCS_PLL_BUS_TYPE_CSI2_CPHY				0x01

/* Old SMIA and implementation specअगरic flags */
/* op pix घड़ी is क्रम all lanes in total normally */
#घोषणा CCS_PLL_FLAG_OP_PIX_CLOCK_PER_LANE			BIT(0)
#घोषणा CCS_PLL_FLAG_NO_OP_CLOCKS				BIT(1)
/* CCS PLL flags */
#घोषणा CCS_PLL_FLAG_LANE_SPEED_MODEL				BIT(2)
#घोषणा CCS_PLL_FLAG_LINK_DECOUPLED				BIT(3)
#घोषणा CCS_PLL_FLAG_EXT_IP_PLL_DIVIDER				BIT(4)
#घोषणा CCS_PLL_FLAG_FLEXIBLE_OP_PIX_CLK_DIV			BIT(5)
#घोषणा CCS_PLL_FLAG_FIFO_DERATING				BIT(6)
#घोषणा CCS_PLL_FLAG_FIFO_OVERRATING				BIT(7)
#घोषणा CCS_PLL_FLAG_DUAL_PLL					BIT(8)
#घोषणा CCS_PLL_FLAG_OP_SYS_DDR					BIT(9)
#घोषणा CCS_PLL_FLAG_OP_PIX_DDR					BIT(10)

/**
 * काष्ठा ccs_pll_branch_fr - CCS PLL configuration (front)
 *
 * A single branch front-end of the CCS PLL tree.
 *
 * @pre_pll_clk_भाग: Pre-PLL घड़ी भागisor
 * @pll_multiplier: PLL multiplier
 * @pll_ip_clk_freq_hz: PLL input घड़ी frequency
 * @pll_op_clk_freq_hz: PLL output घड़ी frequency
 */
काष्ठा ccs_pll_branch_fr अणु
	u16 pre_pll_clk_भाग;
	u16 pll_multiplier;
	u32 pll_ip_clk_freq_hz;
	u32 pll_op_clk_freq_hz;
पूर्ण;

/**
 * काष्ठा ccs_pll_branch_bk - CCS PLL configuration (back)
 *
 * A single branch back-end of the CCS PLL tree.
 *
 * @sys_clk_भाग: System घड़ी भागider
 * @pix_clk_भाग: Pixel घड़ी भागider
 * @sys_clk_freq_hz: System घड़ी frequency
 * @pix_clk_freq_hz: Pixel घड़ी frequency
 */
काष्ठा ccs_pll_branch_bk अणु
	u16 sys_clk_भाग;
	u16 pix_clk_भाग;
	u32 sys_clk_freq_hz;
	u32 pix_clk_freq_hz;
पूर्ण;

/**
 * काष्ठा ccs_pll - Full CCS PLL configuration
 *
 * All inक्रमmation required to calculate CCS PLL configuration.
 *
 * @bus_type: Type of the data bus, CCS_PLL_BUS_TYPE_* (input)
 * @op_lanes: Number of operational lanes (input)
 * @vt_lanes: Number of video timing lanes (input)
 * @csi2: CSI-2 related parameters
 * @csi2.lanes: The number of the CSI-2 data lanes (input)
 * @binning_vertical: Vertical binning factor (input)
 * @binning_horizontal: Horizontal binning factor (input)
 * @scale_m: Downscaling factor, M component, [16, max] (input)
 * @scale_n: Downscaling factor, N component, typically 16 (input)
 * @bits_per_pixel: Bits per pixel on the output data bus (input)
 * @op_bits_per_lane: Number of bits per OP lane (input)
 * @flags: CCS_PLL_FLAG_* (input)
 * @link_freq: Chosen link frequency (input)
 * @ext_clk_freq_hz: External घड़ी frequency, i.e. the sensor's input घड़ी
 *		     (input)
 * @vt_fr: Video timing front-end configuration (output)
 * @vt_bk: Video timing back-end configuration (output)
 * @op_fr: Operational timing front-end configuration (output)
 * @op_bk: Operational timing back-end configuration (output)
 * @pixel_rate_csi: Pixel rate on the output data bus (output)
 * @pixel_rate_pixel_array: Nominal pixel rate in the sensor's pixel array
 *			    (output)
 */
काष्ठा ccs_pll अणु
	/* input values */
	u8 bus_type;
	u8 op_lanes;
	u8 vt_lanes;
	काष्ठा अणु
		u8 lanes;
	पूर्ण csi2;
	u8 binning_horizontal;
	u8 binning_vertical;
	u8 scale_m;
	u8 scale_n;
	u8 bits_per_pixel;
	u8 op_bits_per_lane;
	u16 flags;
	u32 link_freq;
	u32 ext_clk_freq_hz;

	/* output values */
	काष्ठा ccs_pll_branch_fr vt_fr;
	काष्ठा ccs_pll_branch_bk vt_bk;
	काष्ठा ccs_pll_branch_fr op_fr;
	काष्ठा ccs_pll_branch_bk op_bk;

	u32 pixel_rate_csi;
	u32 pixel_rate_pixel_array;
पूर्ण;

/**
 * काष्ठा ccs_pll_branch_limits_fr - CCS PLL front-end limits
 *
 * @min_pre_pll_clk_भाग: Minimum pre-PLL घड़ी भागider
 * @max_pre_pll_clk_भाग: Maximum pre-PLL घड़ी भागider
 * @min_pll_ip_clk_freq_hz: Minimum PLL input घड़ी frequency
 * @max_pll_ip_clk_freq_hz: Maximum PLL input घड़ी frequency
 * @min_pll_multiplier: Minimum PLL multiplier
 * @max_pll_multiplier: Maximum PLL multiplier
 * @min_pll_op_clk_freq_hz: Minimum PLL output घड़ी frequency
 * @max_pll_op_clk_freq_hz: Maximum PLL output घड़ी frequency
 */
काष्ठा ccs_pll_branch_limits_fr अणु
	u16 min_pre_pll_clk_भाग;
	u16 max_pre_pll_clk_भाग;
	u32 min_pll_ip_clk_freq_hz;
	u32 max_pll_ip_clk_freq_hz;
	u16 min_pll_multiplier;
	u16 max_pll_multiplier;
	u32 min_pll_op_clk_freq_hz;
	u32 max_pll_op_clk_freq_hz;
पूर्ण;

/**
 * काष्ठा ccs_pll_branch_limits_bk - CCS PLL back-end limits
 *
 * @min_sys_clk_भाग: Minimum प्रणाली घड़ी भागider
 * @max_sys_clk_भाग: Maximum प्रणाली घड़ी भागider
 * @min_sys_clk_freq_hz: Minimum प्रणाली घड़ी frequency
 * @max_sys_clk_freq_hz: Maximum प्रणाली घड़ी frequency
 * @min_pix_clk_भाग: Minimum pixel घड़ी भागider
 * @max_pix_clk_भाग: Maximum pixel घड़ी भागider
 * @min_pix_clk_freq_hz: Minimum pixel घड़ी frequency
 * @max_pix_clk_freq_hz: Maximum pixel घड़ी frequency
 */
काष्ठा ccs_pll_branch_limits_bk अणु
	u16 min_sys_clk_भाग;
	u16 max_sys_clk_भाग;
	u32 min_sys_clk_freq_hz;
	u32 max_sys_clk_freq_hz;
	u16 min_pix_clk_भाग;
	u16 max_pix_clk_भाग;
	u32 min_pix_clk_freq_hz;
	u32 max_pix_clk_freq_hz;
पूर्ण;

/**
 * काष्ठा ccs_pll_limits - CCS PLL limits
 *
 * @min_ext_clk_freq_hz: Minimum बाह्यal घड़ी frequency
 * @max_ext_clk_freq_hz: Maximum बाह्यal घड़ी frequency
 * @vt_fr: Video timing front-end limits
 * @vt_bk: Video timing back-end limits
 * @op_fr: Operational timing front-end limits
 * @op_bk: Operational timing back-end limits
 * @min_line_length_pck_bin: Minimum line length in pixels, with binning
 * @min_line_length_pck: Minimum line length in pixels without binning
 */
काष्ठा ccs_pll_limits अणु
	/* Strict PLL limits */
	u32 min_ext_clk_freq_hz;
	u32 max_ext_clk_freq_hz;

	काष्ठा ccs_pll_branch_limits_fr vt_fr;
	काष्ठा ccs_pll_branch_limits_bk vt_bk;
	काष्ठा ccs_pll_branch_limits_fr op_fr;
	काष्ठा ccs_pll_branch_limits_bk op_bk;

	/* Other relevant limits */
	u32 min_line_length_pck_bin;
	u32 min_line_length_pck;
पूर्ण;

काष्ठा device;

/**
 * ccs_pll_calculate - Calculate CCS PLL configuration based on input parameters
 *
 * @dev: Device poपूर्णांकer, used क्रम prपूर्णांकing messages
 * @limits: Limits specअगरic to the sensor
 * @pll: Given PLL configuration
 *
 * Calculate the CCS PLL configuration based on the limits as well as given
 * device specअगरic, प्रणाली specअगरic or user configured input data.
 */
पूर्णांक ccs_pll_calculate(काष्ठा device *dev, स्थिर काष्ठा ccs_pll_limits *limits,
		      काष्ठा ccs_pll *pll);

#पूर्ण_अगर /* CCS_PLL_H */
