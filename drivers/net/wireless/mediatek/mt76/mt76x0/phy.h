<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */
#अगर_अघोषित _MT76X0_PHY_H_
#घोषणा _MT76X0_PHY_H_

#घोषणा RF_G_BAND	0x0100
#घोषणा RF_A_BAND	0x0200
#घोषणा RF_A_BAND_LB	0x0400
#घोषणा RF_A_BAND_MB	0x0800
#घोषणा RF_A_BAND_HB	0x1000
#घोषणा RF_A_BAND_11J	0x2000

#घोषणा RF_BW_20        1
#घोषणा RF_BW_40        2
#घोषणा RF_BW_10        4
#घोषणा RF_BW_80        8

#घोषणा MT_RF(bank, reg)		((bank) << 16 | (reg))
#घोषणा MT_RF_BANK(offset)		((offset) >> 16)
#घोषणा MT_RF_REG(offset)		((offset) & 0xff)

#घोषणा MT_RF_VCO_BP_CLOSE_LOOP		BIT(3)
#घोषणा MT_RF_VCO_BP_CLOSE_LOOP_MASK	GENMASK(3, 0)
#घोषणा MT_RF_VCO_CAL_MASK		GENMASK(2, 0)
#घोषणा MT_RF_START_TIME		0x3
#घोषणा MT_RF_START_TIME_MASK		GENMASK(2, 0)
#घोषणा MT_RF_SETTLE_TIME_MASK		GENMASK(6, 4)

#घोषणा MT_RF_PLL_DEN_MASK		GENMASK(4, 0)
#घोषणा MT_RF_PLL_K_MASK		GENMASK(4, 0)
#घोषणा MT_RF_SDM_RESET_MASK		BIT(7)
#घोषणा MT_RF_SDM_MASH_PRBS_MASK	GENMASK(6, 2)
#घोषणा MT_RF_SDM_BP_MASK		BIT(1)
#घोषणा MT_RF_ISI_ISO_MASK		GENMASK(7, 6)
#घोषणा MT_RF_PFD_DLY_MASK		GENMASK(5, 4)
#घोषणा MT_RF_CLK_SEL_MASK		GENMASK(3, 2)
#घोषणा MT_RF_XO_DIV_MASK		GENMASK(1, 0)

काष्ठा mt76x0_bbp_चयन_item अणु
	u16 bw_band;
	काष्ठा mt76_reg_pair reg_pair;
पूर्ण;

काष्ठा mt76x0_rf_चयन_item अणु
	u32 rf_bank_reg;
	u16 bw_band;
	u8 value;
पूर्ण;

काष्ठा mt76x0_freq_item अणु
	u8 channel;
	u32 band;
	u8 pllR37;
	u8 pllR36;
	u8 pllR35;
	u8 pllR34;
	u8 pllR33;
	u8 pllR32_b7b5;
	u8 pllR32_b4b0; /* PLL_DEN (Denomina - 8) */
	u8 pllR31_b7b5;
	u8 pllR31_b4b0; /* PLL_K (Nominator *)*/
	u8 pllR30_b7;	/* sdm_reset_n */
	u8 pllR30_b6b2; /* sdmmash_prbs,sin */
	u8 pllR30_b1;	/* sdm_bp */
	u16 pll_n;	/* R30<0>, R29<7:0> (hex) */
	u8 pllR28_b7b6; /* isi,iso */
	u8 pllR28_b5b4;	/* pfd_dly */
	u8 pllR28_b3b2;	/* clksel option */
	u32 pll_sdm_k;	/* R28<1:0>, R27<7:0>, R26<7:0> (hex) SDM_k */
	u8 pllR24_b1b0;	/* xo_भाग */
पूर्ण;

काष्ठा mt76x0_rate_pwr_item अणु
	s8 mcs_घातer;
	u8 rf_pa_mode;
पूर्ण;

काष्ठा mt76x0_rate_pwr_tab अणु
	काष्ठा mt76x0_rate_pwr_item cck[4];
	काष्ठा mt76x0_rate_pwr_item ofdm[8];
	काष्ठा mt76x0_rate_pwr_item ht[8];
	काष्ठा mt76x0_rate_pwr_item vht[10];
	काष्ठा mt76x0_rate_pwr_item stbc[8];
	काष्ठा mt76x0_rate_pwr_item mcs32;
पूर्ण;

#पूर्ण_अगर /* _MT76X0_PHY_H_ */
