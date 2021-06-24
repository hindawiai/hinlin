<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DC_LINK_ENCODER__DCN20_H__
#घोषणा __DC_LINK_ENCODER__DCN20_H__

#समावेश "dcn10/dcn10_link_encoder.h"

#घोषणा DCN2_AUX_REG_LIST(id)\
	AUX_REG_LIST(id), \
	SRI(AUX_DPHY_TX_CONTROL, DP_AUX, id)

#घोषणा UNIPHY_MASK_SH_LIST(mask_sh)\
	LE_SF(SYMCLKA_CLOCK_ENABLE, SYMCLKA_CLOCK_ENABLE, mask_sh),\
	LE_SF(UNIPHYA_CHANNEL_XBAR_CNTL, UNIPHY_LINK_ENABLE, mask_sh),\
	LE_SF(UNIPHYA_CHANNEL_XBAR_CNTL, UNIPHY_CHANNEL0_XBAR_SOURCE, mask_sh),\
	LE_SF(UNIPHYA_CHANNEL_XBAR_CNTL, UNIPHY_CHANNEL1_XBAR_SOURCE, mask_sh),\
	LE_SF(UNIPHYA_CHANNEL_XBAR_CNTL, UNIPHY_CHANNEL2_XBAR_SOURCE, mask_sh),\
	LE_SF(UNIPHYA_CHANNEL_XBAR_CNTL, UNIPHY_CHANNEL3_XBAR_SOURCE, mask_sh)

#घोषणा DPCS_MASK_SH_LIST(mask_sh)\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX0_CLK_RDY, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX0_DATA_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX1_CLK_RDY, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX1_DATA_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX2_CLK_RDY, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX2_DATA_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX3_CLK_RDY, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX3_DATA_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL4, RDPCS_PHY_DP_TX0_TERM_CTRL, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL4, RDPCS_PHY_DP_TX1_TERM_CTRL, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL4, RDPCS_PHY_DP_TX2_TERM_CTRL, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL4, RDPCS_PHY_DP_TX3_TERM_CTRL, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL11, RDPCS_PHY_DP_MPLLB_MULTIPLIER, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL5, RDPCS_PHY_DP_TX0_WIDTH, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL5, RDPCS_PHY_DP_TX0_RATE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL5, RDPCS_PHY_DP_TX1_WIDTH, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL5, RDPCS_PHY_DP_TX1_RATE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_TX2_PSTATE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_TX3_PSTATE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_TX2_MPLL_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_TX3_MPLL_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL7, RDPCS_PHY_DP_MPLLB_FRACN_QUOT, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL7, RDPCS_PHY_DP_MPLLB_FRACN_DEN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL8, RDPCS_PHY_DP_MPLLB_SSC_PEAK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL9, RDPCS_PHY_DP_MPLLB_SSC_UP_SPREAD, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL9, RDPCS_PHY_DP_MPLLB_SSC_STEPSIZE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL10, RDPCS_PHY_DP_MPLLB_FRACN_REM, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL11, RDPCS_PHY_DP_REF_CLK_MPLLB_DIV, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL11, RDPCS_PHY_HDMI_MPLLB_HDMI_DIV, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL12, RDPCS_PHY_DP_MPLLB_SSC_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL12, RDPCS_PHY_DP_MPLLB_DIV5_CLK_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL12, RDPCS_PHY_DP_MPLLB_TX_CLK_DIV, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL12, RDPCS_PHY_DP_MPLLB_WORD_DIV2_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL12, RDPCS_PHY_DP_MPLLB_STATE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL13, RDPCS_PHY_DP_MPLLB_DIV_CLK_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL13, RDPCS_PHY_DP_MPLLB_DIV_MULTIPLIER, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL14, RDPCS_PHY_DP_MPLLB_FRACN_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL14, RDPCS_PHY_DP_MPLLB_PMIX_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CNTL, RDPCS_TX_FIFO_LANE0_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CNTL, RDPCS_TX_FIFO_LANE1_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CNTL, RDPCS_TX_FIFO_LANE2_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CNTL, RDPCS_TX_FIFO_LANE3_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CNTL, RDPCS_TX_FIFO_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CNTL, RDPCS_TX_FIFO_RD_START_DELAY, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CLOCK_CNTL, RDPCS_EXT_REFCLK_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CLOCK_CNTL, RDPCS_SRAMCLK_BYPASS, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CLOCK_CNTL, RDPCS_SRAMCLK_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CLOCK_CNTL, RDPCS_SRAMCLK_CLOCK_ON, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CLOCK_CNTL, RDPCS_SYMCLK_DIV2_CLOCK_ON, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CLOCK_CNTL, RDPCS_SYMCLK_DIV2_GATE_DIS, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_CLOCK_CNTL, RDPCS_SYMCLK_DIV2_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX0_DISABLE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX1_DISABLE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX2_DISABLE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX3_DISABLE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX0_REQ, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX1_REQ, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX2_REQ, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX3_REQ, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX0_ACK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX1_ACK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX2_ACK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX3_ACK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX0_RESET, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX1_RESET, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX2_RESET, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL3, RDPCS_PHY_DP_TX3_RESET, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL0, RDPCS_PHY_RESET, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL0, RDPCS_PHY_CR_MUX_SEL, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL0, RDPCS_PHY_REF_RANGE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL0, RDPCS_SRAM_BYPASS, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL0, RDPCS_SRAM_EXT_LD_DONE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL0, RDPCS_PHY_HDMIMODE_ENABLE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL0, RDPCS_SRAM_INIT_DONE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL2, RDPCS_PHY_DP4_POR, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PLL_UPDATE_DATA, RDPCS_PLL_UPDATE_DATA, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_INTERRUPT_CONTROL, RDPCS_REG_FIFO_ERROR_MASK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_INTERRUPT_CONTROL, RDPCS_TX_FIFO_ERROR_MASK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_INTERRUPT_CONTROL, RDPCS_DPALT_DISABLE_TOGGLE_MASK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_INTERRUPT_CONTROL, RDPCS_DPALT_4LANE_TOGGLE_MASK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCS_TX_CR_ADDR, RDPCS_TX_CR_ADDR, mask_sh),\
	LE_SF(RDPCSTX0_RDPCS_TX_CR_DATA, RDPCS_TX_CR_DATA, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_DP_MPLLB_V2I, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_DP_TX0_EQ_MAIN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_DP_TX0_EQ_PRE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_DP_TX0_EQ_POST, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_DP_MPLLB_FREQ_VCO, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE1, RDPCS_PHY_DP_MPLLB_CP_INT, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE1, RDPCS_PHY_DP_MPLLB_CP_PROP, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE1, RDPCS_PHY_DP_TX1_EQ_MAIN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE1, RDPCS_PHY_DP_TX1_EQ_PRE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE1, RDPCS_PHY_DP_TX1_EQ_POST, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE2, RDPCS_PHY_DP_TX2_EQ_MAIN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE2, RDPCS_PHY_DP_TX2_EQ_PRE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE2, RDPCS_PHY_DP_TX2_EQ_POST, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DP_TX3_EQ_MAIN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DCO_FINETUNE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DCO_RANGE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DP_TX3_EQ_PRE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DP_TX3_EQ_POST, mask_sh),\
	LE_SF(DPCSTX0_DPCSTX_TX_CLOCK_CNTL, DPCS_SYMCLK_CLOCK_ON, mask_sh),\
	LE_SF(DPCSTX0_DPCSTX_TX_CLOCK_CNTL, DPCS_SYMCLK_GATE_DIS, mask_sh),\
	LE_SF(DPCSTX0_DPCSTX_TX_CLOCK_CNTL, DPCS_SYMCLK_EN, mask_sh),\
	LE_SF(DPCSTX0_DPCSTX_TX_CNTL, DPCS_TX_DATA_SWAP, mask_sh),\
	LE_SF(DPCSTX0_DPCSTX_TX_CNTL, DPCS_TX_DATA_ORDER_INVERT, mask_sh),\
	LE_SF(DPCSTX0_DPCSTX_TX_CNTL, DPCS_TX_FIFO_EN, mask_sh),\
	LE_SF(DPCSTX0_DPCSTX_TX_CNTL, DPCS_TX_FIFO_RD_START_DELAY, mask_sh)

#घोषणा DPCS_DCN2_MASK_SH_LIST(mask_sh)\
	DPCS_MASK_SH_LIST(mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_RX_LD_VAL, RDPCS_PHY_RX_REF_LD_VAL, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_RX_LD_VAL, RDPCS_PHY_RX_VCO_LD_VAL, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DPALT_DISABLE_ACK, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_TX0_PSTATE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_TX1_PSTATE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_TX0_MPLL_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_TX1_MPLL_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_REF_CLK_EN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL5, RDPCS_PHY_DP_TX2_WIDTH, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL5, RDPCS_PHY_DP_TX2_RATE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL5, RDPCS_PHY_DP_TX3_WIDTH, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL5, RDPCS_PHY_DP_TX3_RATE, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYA_SOFT_RESET, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYB_SOFT_RESET, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYC_SOFT_RESET, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYD_SOFT_RESET, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYE_SOFT_RESET, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DPALT_DP4, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DPALT_DISABLE, mask_sh)

#घोषणा LINK_ENCODER_MASK_SH_LIST_DCN20(mask_sh)\
	LINK_ENCODER_MASK_SH_LIST_DCN10(mask_sh),\
	LE_SF(DP0_DP_DPHY_CNTL, DPHY_FEC_EN, mask_sh),\
	LE_SF(DP0_DP_DPHY_CNTL, DPHY_FEC_READY_SHADOW, mask_sh),\
	LE_SF(DP0_DP_DPHY_CNTL, DPHY_FEC_ACTIVE_STATUS, mask_sh),\
	LE_SF(DIG0_DIG_LANE_ENABLE, DIG_LANE0EN, mask_sh),\
	LE_SF(DIG0_DIG_LANE_ENABLE, DIG_LANE1EN, mask_sh),\
	LE_SF(DIG0_DIG_LANE_ENABLE, DIG_LANE2EN, mask_sh),\
	LE_SF(DIG0_DIG_LANE_ENABLE, DIG_LANE3EN, mask_sh),\
	LE_SF(DIG0_DIG_LANE_ENABLE, DIG_CLK_EN, mask_sh),\
	LE_SF(DIG0_TMDS_CTL_BITS, TMDS_CTL0, mask_sh), \
	UNIPHY_MASK_SH_LIST(mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL0, AUX_RX_START_WINDOW, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL0, AUX_RX_HALF_SYM_DETECT_LEN, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL0, AUX_RX_TRANSITION_FILTER_EN, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL0, AUX_RX_ALLOW_BELOW_THRESHOLD_PHASE_DETECT, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL0, AUX_RX_ALLOW_BELOW_THRESHOLD_START, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL0, AUX_RX_ALLOW_BELOW_THRESHOLD_STOP, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL0, AUX_RX_PHASE_DETECT_LEN, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL0, AUX_RX_DETECTION_THRESHOLD, mask_sh), \
	LE_SF(DP_AUX0_AUX_DPHY_TX_CONTROL, AUX_TX_PRECHARGE_LEN, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_TX_CONTROL, AUX_TX_PRECHARGE_SYMBOLS, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_TX_CONTROL, AUX_MODE_DET_CHECK_DELAY, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL1, AUX_RX_PRECHARGE_SKIP, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL1, AUX_RX_TIMEOUT_LEN, mask_sh),\
	LE_SF(DP_AUX0_AUX_DPHY_RX_CONTROL1, AUX_RX_TIMEOUT_LEN_MUL, mask_sh)

#घोषणा UNIPHY_DCN2_REG_LIST(id) \
	SRI(CLOCK_ENABLE, SYMCLK, id), \
	SRI(CHANNEL_XBAR_CNTL, UNIPHY, id)

#घोषणा DPCS_DCN2_CMN_REG_LIST(id) \
	SRI(DIG_LANE_ENABLE, DIG, id), \
	SRI(TMDS_CTL_BITS, DIG, id), \
	SRI(RDPCSTX_PHY_CNTL3, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL4, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL5, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL6, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL7, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL8, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL9, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL10, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL11, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL12, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL13, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL14, RDPCSTX, id), \
	SRI(RDPCSTX_CNTL, RDPCSTX, id), \
	SRI(RDPCSTX_CLOCK_CNTL, RDPCSTX, id), \
	SRI(RDPCSTX_INTERRUPT_CONTROL, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL0, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_CNTL2, RDPCSTX, id), \
	SRI(RDPCSTX_PLL_UPDATE_DATA, RDPCSTX, id), \
	SRI(RDPCS_TX_CR_ADDR, RDPCSTX, id), \
	SRI(RDPCS_TX_CR_DATA, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_FUSE0, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_FUSE1, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_FUSE2, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_FUSE3, RDPCSTX, id), \
	SRI(DPCSTX_TX_CLOCK_CNTL, DPCSTX, id), \
	SRI(DPCSTX_TX_CNTL, DPCSTX, id), \
	SR(RDPCSTX0_RDPCSTX_SCRATCH)


#घोषणा DPCS_DCN2_REG_LIST(id) \
	DPCS_DCN2_CMN_REG_LIST(id), \
	SRI(RDPCSTX_PHY_RX_LD_VAL, RDPCSTX, id),\
	SRI(RDPCSTX_DMCU_DPALT_DIS_BLOCK_REG, RDPCSTX, id)

#घोषणा LE_DCN2_REG_LIST(id) \
		LE_DCN10_REG_LIST(id), \
		SR(DCIO_SOFT_RESET)

काष्ठा mpll_cfg अणु
	uपूर्णांक32_t mpllb_ana_v2i;
	uपूर्णांक32_t mpllb_ana_freq_vco;
	uपूर्णांक32_t mpllb_ana_cp_पूर्णांक;
	uपूर्णांक32_t mpllb_ana_cp_prop;
	uपूर्णांक32_t mpllb_multiplier;
	uपूर्णांक32_t ref_clk_mpllb_भाग;
	bool mpllb_word_भाग2_en;
	bool mpllb_ssc_en;
	bool mpllb_भाग5_clk_en;
	bool mpllb_भाग_clk_en;
	bool mpllb_fracn_en;
	bool mpllb_pmix_en;
	uपूर्णांक32_t mpllb_भाग_multiplier;
	uपूर्णांक32_t mpllb_tx_clk_भाग;
	uपूर्णांक32_t mpllb_fracn_quot;
	uपूर्णांक32_t mpllb_fracn_den;
	uपूर्णांक32_t mpllb_ssc_peak;
	uपूर्णांक32_t mpllb_ssc_stepsize;
	uपूर्णांक32_t mpllb_ssc_up_spपढ़ो;
	uपूर्णांक32_t mpllb_fracn_rem;
	uपूर्णांक32_t mpllb_hdmi_भाग;
	// TODO: May not mpll params, need to figure out.
	uपूर्णांक32_t tx_vboost_lvl;
	uपूर्णांक32_t hdmi_pixel_clk_भाग;
	uपूर्णांक32_t ref_range;
	uपूर्णांक32_t ref_clk;
	bool hdmimode_enable;
	bool sup_pre_hp;
	bool dp_tx0_vergdrv_byp;
	bool dp_tx1_vergdrv_byp;
	bool dp_tx2_vergdrv_byp;
	bool dp_tx3_vergdrv_byp;
	uपूर्णांक32_t tx_peaking_lvl;
	uपूर्णांक32_t ctr_reqs_pll;


पूर्ण;

काष्ठा dpcssys_phy_seq_cfg अणु
	bool program_fuse;
	bool bypass_sram;
	bool lane_en[4];
	bool use_calibration_setting;
	काष्ठा mpll_cfg mpll_cfg;
	bool load_sram_fw;
#अगर 0

	bool hdmimode_enable;
	bool silver2;
	bool ext_refclk_en;
	uपूर्णांक32_t dp_tx0_term_ctrl;
	uपूर्णांक32_t dp_tx1_term_ctrl;
	uपूर्णांक32_t dp_tx2_term_ctrl;
	uपूर्णांक32_t dp_tx3_term_ctrl;
	uपूर्णांक32_t fw_data[0x1000];
	uपूर्णांक32_t dp_tx0_width;
	uपूर्णांक32_t dp_tx1_width;
	uपूर्णांक32_t dp_tx2_width;
	uपूर्णांक32_t dp_tx3_width;
	uपूर्णांक32_t dp_tx0_rate;
	uपूर्णांक32_t dp_tx1_rate;
	uपूर्णांक32_t dp_tx2_rate;
	uपूर्णांक32_t dp_tx3_rate;
	uपूर्णांक32_t dp_tx0_eq_मुख्य;
	uपूर्णांक32_t dp_tx0_eq_pre;
	uपूर्णांक32_t dp_tx0_eq_post;
	uपूर्णांक32_t dp_tx1_eq_मुख्य;
	uपूर्णांक32_t dp_tx1_eq_pre;
	uपूर्णांक32_t dp_tx1_eq_post;
	uपूर्णांक32_t dp_tx2_eq_मुख्य;
	uपूर्णांक32_t dp_tx2_eq_pre;
	uपूर्णांक32_t dp_tx2_eq_post;
	uपूर्णांक32_t dp_tx3_eq_मुख्य;
	uपूर्णांक32_t dp_tx3_eq_pre;
	uपूर्णांक32_t dp_tx3_eq_post;
	bool data_swap_en;
	bool data_order_invert_en;
	uपूर्णांक32_t ldpcs_fअगरo_start_delay;
	uपूर्णांक32_t rdpcs_fअगरo_start_delay;
	bool rdpcs_reg_fअगरo_error_mask;
	bool rdpcs_tx_fअगरo_error_mask;
	bool rdpcs_dpalt_disable_mask;
	bool rdpcs_dpalt_4lane_mask;
#पूर्ण_अगर
पूर्ण;

काष्ठा dcn20_link_encoder अणु
	काष्ठा dcn10_link_encoder enc10;
	काष्ठा dpcssys_phy_seq_cfg phy_seq_cfg;
पूर्ण;

व्योम enc2_fec_set_enable(काष्ठा link_encoder *enc, bool enable);
व्योम enc2_fec_set_पढ़ोy(काष्ठा link_encoder *enc, bool पढ़ोy);
bool enc2_fec_is_active(काष्ठा link_encoder *enc);
व्योम enc2_hw_init(काष्ठा link_encoder *enc);

व्योम link_enc2_पढ़ो_state(काष्ठा link_encoder *enc, काष्ठा link_enc_state *s);

व्योम dcn20_link_encoder_enable_dp_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source);

bool dcn20_link_encoder_is_in_alt_mode(काष्ठा link_encoder *enc);
व्योम dcn20_link_encoder_get_max_link_cap(काष्ठा link_encoder *enc,
	काष्ठा dc_link_settings *link_settings);

व्योम dcn20_link_encoder_स्थिरruct(
	काष्ठा dcn20_link_encoder *enc20,
	स्थिर काष्ठा encoder_init_data *init_data,
	स्थिर काष्ठा encoder_feature_support *enc_features,
	स्थिर काष्ठा dcn10_link_enc_रेजिस्टरs *link_regs,
	स्थिर काष्ठा dcn10_link_enc_aux_रेजिस्टरs *aux_regs,
	स्थिर काष्ठा dcn10_link_enc_hpd_रेजिस्टरs *hpd_regs,
	स्थिर काष्ठा dcn10_link_enc_shअगरt *link_shअगरt,
	स्थिर काष्ठा dcn10_link_enc_mask *link_mask);

#पूर्ण_अगर /* __DC_LINK_ENCODER__DCN20_H__ */
