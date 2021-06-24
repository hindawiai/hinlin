<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cadence Torrent SD0801 PHY driver.
 *
 * Copyright 2018 Cadence Design Systems, Inc.
 *
 */

#समावेश <dt-bindings/phy/phy.h>
#समावेश <dt-bindings/phy/phy-cadence.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/regmap.h>

#घोषणा REF_CLK_19_2MHz		19200000
#घोषणा REF_CLK_25MHz		25000000

#घोषणा MAX_NUM_LANES		4
#घोषणा DEFAULT_MAX_BIT_RATE	8100 /* in Mbps */

#घोषणा NUM_SSC_MODE		3
#घोषणा NUM_PHY_TYPE		6

#घोषणा POLL_TIMEOUT_US		5000
#घोषणा PLL_LOCK_TIMEOUT	100000

#घोषणा TORRENT_COMMON_CDB_OFFSET	0x0

#घोषणा TORRENT_TX_LANE_CDB_OFFSET(ln, block_offset, reg_offset)	\
				((0x4000 << (block_offset)) +		\
				(((ln) << 9) << (reg_offset)))

#घोषणा TORRENT_RX_LANE_CDB_OFFSET(ln, block_offset, reg_offset)	\
				((0x8000 << (block_offset)) +		\
				(((ln) << 9) << (reg_offset)))

#घोषणा TORRENT_PHY_PCS_COMMON_OFFSET(block_offset)	\
				(0xC000 << (block_offset))

#घोषणा TORRENT_PHY_PMA_COMMON_OFFSET(block_offset)	\
				(0xE000 << (block_offset))

#घोषणा TORRENT_DPTX_PHY_OFFSET		0x0

/*
 * रेजिस्टर offsets from DPTX PHY रेजिस्टर block base (i.e MHDP
 * रेजिस्टर base + 0x30a00)
 */
#घोषणा PHY_AUX_CTRL			0x04
#घोषणा PHY_RESET			0x20
#घोषणा PMA_TX_ELEC_IDLE_MASK		0xF0U
#घोषणा PMA_TX_ELEC_IDLE_SHIFT		4
#घोषणा PHY_L00_RESET_N_MASK		0x01U
#घोषणा PHY_PMA_XCVR_PLLCLK_EN		0x24
#घोषणा PHY_PMA_XCVR_PLLCLK_EN_ACK	0x28
#घोषणा PHY_PMA_XCVR_POWER_STATE_REQ	0x2c
#घोषणा PHY_POWER_STATE_LN_0	0x0000
#घोषणा PHY_POWER_STATE_LN_1	0x0008
#घोषणा PHY_POWER_STATE_LN_2	0x0010
#घोषणा PHY_POWER_STATE_LN_3	0x0018
#घोषणा PMA_XCVR_POWER_STATE_REQ_LN_MASK	0x3FU
#घोषणा PHY_PMA_XCVR_POWER_STATE_ACK	0x30
#घोषणा PHY_PMA_CMN_READY		0x34

/*
 * रेजिस्टर offsets from SD0801 PHY रेजिस्टर block base (i.e MHDP
 * रेजिस्टर base + 0x500000)
 */
#घोषणा CMN_SSM_BANDGAP_TMR		0x0021U
#घोषणा CMN_SSM_BIAS_TMR		0x0022U
#घोषणा CMN_PLLSM0_PLLPRE_TMR		0x002AU
#घोषणा CMN_PLLSM0_PLLLOCK_TMR		0x002CU
#घोषणा CMN_PLLSM1_PLLPRE_TMR		0x0032U
#घोषणा CMN_PLLSM1_PLLLOCK_TMR		0x0034U
#घोषणा CMN_CDIAG_CDB_PWRI_OVRD		0x0041U
#घोषणा CMN_CDIAG_XCVRC_PWRI_OVRD	0x0047U
#घोषणा CMN_CDIAG_REFCLK_OVRD		0x004CU
#घोषणा CMN_CDIAG_REFCLK_DRV0_CTRL	0x0050U
#घोषणा CMN_BGCAL_INIT_TMR		0x0064U
#घोषणा CMN_BGCAL_ITER_TMR		0x0065U
#घोषणा CMN_IBCAL_INIT_TMR		0x0074U
#घोषणा CMN_PLL0_VCOCAL_TCTRL		0x0082U
#घोषणा CMN_PLL0_VCOCAL_INIT_TMR	0x0084U
#घोषणा CMN_PLL0_VCOCAL_ITER_TMR	0x0085U
#घोषणा CMN_PLL0_VCOCAL_REFTIM_START	0x0086U
#घोषणा CMN_PLL0_VCOCAL_PLLCNT_START	0x0088U
#घोषणा CMN_PLL0_INTDIV_M0		0x0090U
#घोषणा CMN_PLL0_FRACDIVL_M0		0x0091U
#घोषणा CMN_PLL0_FRACDIVH_M0		0x0092U
#घोषणा CMN_PLL0_HIGH_THR_M0		0x0093U
#घोषणा CMN_PLL0_DSM_DIAG_M0		0x0094U
#घोषणा CMN_PLL0_SS_CTRL1_M0		0x0098U
#घोषणा CMN_PLL0_SS_CTRL2_M0            0x0099U
#घोषणा CMN_PLL0_SS_CTRL3_M0            0x009AU
#घोषणा CMN_PLL0_SS_CTRL4_M0            0x009BU
#घोषणा CMN_PLL0_LOCK_REFCNT_START      0x009CU
#घोषणा CMN_PLL0_LOCK_PLLCNT_START	0x009EU
#घोषणा CMN_PLL0_LOCK_PLLCNT_THR        0x009FU
#घोषणा CMN_PLL0_INTDIV_M1		0x00A0U
#घोषणा CMN_PLL0_FRACDIVH_M1		0x00A2U
#घोषणा CMN_PLL0_HIGH_THR_M1		0x00A3U
#घोषणा CMN_PLL0_DSM_DIAG_M1		0x00A4U
#घोषणा CMN_PLL0_SS_CTRL1_M1		0x00A8U
#घोषणा CMN_PLL0_SS_CTRL2_M1		0x00A9U
#घोषणा CMN_PLL0_SS_CTRL3_M1		0x00AAU
#घोषणा CMN_PLL0_SS_CTRL4_M1		0x00ABU
#घोषणा CMN_PLL1_VCOCAL_TCTRL		0x00C2U
#घोषणा CMN_PLL1_VCOCAL_INIT_TMR	0x00C4U
#घोषणा CMN_PLL1_VCOCAL_ITER_TMR	0x00C5U
#घोषणा CMN_PLL1_VCOCAL_REFTIM_START	0x00C6U
#घोषणा CMN_PLL1_VCOCAL_PLLCNT_START	0x00C8U
#घोषणा CMN_PLL1_INTDIV_M0		0x00D0U
#घोषणा CMN_PLL1_FRACDIVL_M0		0x00D1U
#घोषणा CMN_PLL1_FRACDIVH_M0		0x00D2U
#घोषणा CMN_PLL1_HIGH_THR_M0		0x00D3U
#घोषणा CMN_PLL1_DSM_DIAG_M0		0x00D4U
#घोषणा CMN_PLL1_DSM_FBH_OVRD_M0	0x00D5U
#घोषणा CMN_PLL1_DSM_FBL_OVRD_M0	0x00D6U
#घोषणा CMN_PLL1_SS_CTRL1_M0		0x00D8U
#घोषणा CMN_PLL1_SS_CTRL2_M0            0x00D9U
#घोषणा CMN_PLL1_SS_CTRL3_M0            0x00DAU
#घोषणा CMN_PLL1_SS_CTRL4_M0            0x00DBU
#घोषणा CMN_PLL1_LOCK_REFCNT_START      0x00DCU
#घोषणा CMN_PLL1_LOCK_PLLCNT_START	0x00DEU
#घोषणा CMN_PLL1_LOCK_PLLCNT_THR        0x00DFU
#घोषणा CMN_TXPUCAL_TUNE		0x0103U
#घोषणा CMN_TXPUCAL_INIT_TMR		0x0104U
#घोषणा CMN_TXPUCAL_ITER_TMR		0x0105U
#घोषणा CMN_TXPDCAL_TUNE		0x010BU
#घोषणा CMN_TXPDCAL_INIT_TMR		0x010CU
#घोषणा CMN_TXPDCAL_ITER_TMR		0x010DU
#घोषणा CMN_RXCAL_INIT_TMR		0x0114U
#घोषणा CMN_RXCAL_ITER_TMR		0x0115U
#घोषणा CMN_SD_CAL_INIT_TMR		0x0124U
#घोषणा CMN_SD_CAL_ITER_TMR		0x0125U
#घोषणा CMN_SD_CAL_REFTIM_START		0x0126U
#घोषणा CMN_SD_CAL_PLLCNT_START		0x0128U
#घोषणा CMN_PDIAG_PLL0_CTRL_M0		0x01A0U
#घोषणा CMN_PDIAG_PLL0_CLK_SEL_M0	0x01A1U
#घोषणा CMN_PDIAG_PLL0_CP_PADJ_M0	0x01A4U
#घोषणा CMN_PDIAG_PLL0_CP_IADJ_M0	0x01A5U
#घोषणा CMN_PDIAG_PLL0_FILT_PADJ_M0	0x01A6U
#घोषणा CMN_PDIAG_PLL0_CTRL_M1		0x01B0U
#घोषणा CMN_PDIAG_PLL0_CLK_SEL_M1	0x01B1U
#घोषणा CMN_PDIAG_PLL0_CP_PADJ_M1	0x01B4U
#घोषणा CMN_PDIAG_PLL0_CP_IADJ_M1	0x01B5U
#घोषणा CMN_PDIAG_PLL0_FILT_PADJ_M1	0x01B6U
#घोषणा CMN_PDIAG_PLL1_CTRL_M0		0x01C0U
#घोषणा CMN_PDIAG_PLL1_CLK_SEL_M0	0x01C1U
#घोषणा CMN_PDIAG_PLL1_CP_PADJ_M0	0x01C4U
#घोषणा CMN_PDIAG_PLL1_CP_IADJ_M0	0x01C5U
#घोषणा CMN_PDIAG_PLL1_FILT_PADJ_M0	0x01C6U
#घोषणा CMN_DIAG_BIAS_OVRD1		0x01E1U

/* PMA TX Lane रेजिस्टरs */
#घोषणा TX_TXCC_CTRL			0x0040U
#घोषणा TX_TXCC_CPOST_MULT_00		0x004CU
#घोषणा TX_TXCC_CPOST_MULT_01		0x004DU
#घोषणा TX_TXCC_MGNFS_MULT_000		0x0050U
#घोषणा TX_TXCC_MGNFS_MULT_100		0x0054U
#घोषणा DRV_DIAG_TX_DRV			0x00C6U
#घोषणा XCVR_DIAG_PLLDRC_CTRL		0x00E5U
#घोषणा XCVR_DIAG_HSCLK_SEL		0x00E6U
#घोषणा XCVR_DIAG_HSCLK_DIV		0x00E7U
#घोषणा XCVR_DIAG_RXCLK_CTRL		0x00E9U
#घोषणा XCVR_DIAG_BIDI_CTRL		0x00EAU
#घोषणा XCVR_DIAG_PSC_OVRD		0x00EBU
#घोषणा TX_PSC_A0			0x0100U
#घोषणा TX_PSC_A1			0x0101U
#घोषणा TX_PSC_A2			0x0102U
#घोषणा TX_PSC_A3			0x0103U
#घोषणा TX_RCVDET_ST_TMR		0x0123U
#घोषणा TX_DIAG_ACYA			0x01E7U
#घोषणा TX_DIAG_ACYA_HBDC_MASK		0x0001U

/* PMA RX Lane रेजिस्टरs */
#घोषणा RX_PSC_A0			0x0000U
#घोषणा RX_PSC_A1			0x0001U
#घोषणा RX_PSC_A2			0x0002U
#घोषणा RX_PSC_A3			0x0003U
#घोषणा RX_PSC_CAL			0x0006U
#घोषणा RX_CDRLF_CNFG			0x0080U
#घोषणा RX_CDRLF_CNFG3			0x0082U
#घोषणा RX_SIGDET_HL_FILT_TMR		0x0090U
#घोषणा RX_REE_GCSM1_CTRL		0x0108U
#घोषणा RX_REE_GCSM1_EQENM_PH1		0x0109U
#घोषणा RX_REE_GCSM1_EQENM_PH2		0x010AU
#घोषणा RX_REE_GCSM2_CTRL		0x0110U
#घोषणा RX_REE_PERGCSM_CTRL		0x0118U
#घोषणा RX_REE_ATTEN_THR		0x0149U
#घोषणा RX_REE_TAP1_CLIP		0x0171U
#घोषणा RX_REE_TAP2TON_CLIP		0x0172U
#घोषणा RX_REE_SMGM_CTRL1		0x0177U
#घोषणा RX_REE_SMGM_CTRL2		0x0178U
#घोषणा RX_DIAG_DFE_CTRL		0x01E0U
#घोषणा RX_DIAG_DFE_AMP_TUNE_2		0x01E2U
#घोषणा RX_DIAG_DFE_AMP_TUNE_3		0x01E3U
#घोषणा RX_DIAG_NQST_CTRL		0x01E5U
#घोषणा RX_DIAG_SIGDET_TUNE		0x01E8U
#घोषणा RX_DIAG_PI_RATE			0x01F4U
#घोषणा RX_DIAG_PI_CAP			0x01F5U
#घोषणा RX_DIAG_ACYA			0x01FFU

/* PHY PCS common रेजिस्टरs */
#घोषणा PHY_PIPE_CMN_CTRL1		0x0000U
#घोषणा PHY_PLL_CFG			0x000EU
#घोषणा PHY_PIPE_USB3_GEN2_PRE_CFG0	0x0020U
#घोषणा PHY_PIPE_USB3_GEN2_POST_CFG0	0x0022U
#घोषणा PHY_PIPE_USB3_GEN2_POST_CFG1	0x0023U

/* PHY PMA common रेजिस्टरs */
#घोषणा PHY_PMA_CMN_CTRL1		0x0000U
#घोषणा PHY_PMA_CMN_CTRL2		0x0001U
#घोषणा PHY_PMA_PLL_RAW_CTRL		0x0003U

अटल स्थिर अक्षर * स्थिर clk_names[] = अणु
	[CDNS_TORRENT_REFCLK_DRIVER] = "refclk-driver",
पूर्ण;

अटल स्थिर काष्ठा reg_field phy_pll_cfg =
				REG_FIELD(PHY_PLL_CFG, 0, 1);

अटल स्थिर काष्ठा reg_field phy_pma_cmn_ctrl_1 =
				REG_FIELD(PHY_PMA_CMN_CTRL1, 0, 0);

अटल स्थिर काष्ठा reg_field phy_pma_cmn_ctrl_2 =
				REG_FIELD(PHY_PMA_CMN_CTRL2, 0, 7);

अटल स्थिर काष्ठा reg_field phy_pma_pll_raw_ctrl =
				REG_FIELD(PHY_PMA_PLL_RAW_CTRL, 0, 1);

अटल स्थिर काष्ठा reg_field phy_reset_ctrl =
				REG_FIELD(PHY_RESET, 8, 8);

अटल स्थिर काष्ठा reg_field phy_pipe_cmn_ctrl1_0 = REG_FIELD(PHY_PIPE_CMN_CTRL1, 0, 0);

#घोषणा REFCLK_OUT_NUM_CMN_CONFIG	5

क्रमागत cdns_torrent_refclk_out_cmn अणु
	CMN_CDIAG_REFCLK_OVRD_4,
	CMN_CDIAG_REFCLK_DRV0_CTRL_1,
	CMN_CDIAG_REFCLK_DRV0_CTRL_4,
	CMN_CDIAG_REFCLK_DRV0_CTRL_5,
	CMN_CDIAG_REFCLK_DRV0_CTRL_6,
पूर्ण;

अटल स्थिर काष्ठा reg_field refclk_out_cmn_cfg[] = अणु
	[CMN_CDIAG_REFCLK_OVRD_4]	= REG_FIELD(CMN_CDIAG_REFCLK_OVRD, 4, 4),
	[CMN_CDIAG_REFCLK_DRV0_CTRL_1]	= REG_FIELD(CMN_CDIAG_REFCLK_DRV0_CTRL, 1, 1),
	[CMN_CDIAG_REFCLK_DRV0_CTRL_4]	= REG_FIELD(CMN_CDIAG_REFCLK_DRV0_CTRL, 4, 4),
	[CMN_CDIAG_REFCLK_DRV0_CTRL_5]  = REG_FIELD(CMN_CDIAG_REFCLK_DRV0_CTRL, 5, 5),
	[CMN_CDIAG_REFCLK_DRV0_CTRL_6]	= REG_FIELD(CMN_CDIAG_REFCLK_DRV0_CTRL, 6, 6),
पूर्ण;

क्रमागत cdns_torrent_phy_type अणु
	TYPE_NONE,
	TYPE_DP,
	TYPE_PCIE,
	TYPE_SGMII,
	TYPE_QSGMII,
	TYPE_USB,
पूर्ण;

क्रमागत cdns_torrent_ssc_mode अणु
	NO_SSC,
	EXTERNAL_SSC,
	INTERNAL_SSC
पूर्ण;

काष्ठा cdns_torrent_inst अणु
	काष्ठा phy *phy;
	u32 mlane;
	क्रमागत cdns_torrent_phy_type phy_type;
	u32 num_lanes;
	काष्ठा reset_control *lnk_rst;
	क्रमागत cdns_torrent_ssc_mode ssc_mode;
पूर्ण;

काष्ठा cdns_torrent_phy अणु
	व्योम __iomem *base;	/* DPTX रेजिस्टरs base */
	व्योम __iomem *sd_base; /* SD0801 रेजिस्टरs base */
	u32 max_bit_rate; /* Maximum link bit rate to use (in Mbps) */
	काष्ठा reset_control *phy_rst;
	काष्ठा reset_control *apb_rst;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ ref_clk_rate;
	काष्ठा cdns_torrent_inst phys[MAX_NUM_LANES];
	पूर्णांक nsubnodes;
	स्थिर काष्ठा cdns_torrent_data *init_data;
	काष्ठा regmap *regmap;
	काष्ठा regmap *regmap_common_cdb;
	काष्ठा regmap *regmap_phy_pcs_common_cdb;
	काष्ठा regmap *regmap_phy_pma_common_cdb;
	काष्ठा regmap *regmap_tx_lane_cdb[MAX_NUM_LANES];
	काष्ठा regmap *regmap_rx_lane_cdb[MAX_NUM_LANES];
	काष्ठा regmap *regmap_dptx_phy_reg;
	काष्ठा regmap_field *phy_pll_cfg;
	काष्ठा regmap_field *phy_pma_cmn_ctrl_1;
	काष्ठा regmap_field *phy_pma_cmn_ctrl_2;
	काष्ठा regmap_field *phy_pma_pll_raw_ctrl;
	काष्ठा regmap_field *phy_reset_ctrl;
	काष्ठा clk *clks[CDNS_TORRENT_REFCLK_DRIVER + 1];
	काष्ठा clk_onecell_data clk_data;
पूर्ण;

क्रमागत phy_घातerstate अणु
	POWERSTATE_A0 = 0,
	/* Powerstate A1 is unused */
	POWERSTATE_A2 = 2,
	POWERSTATE_A3 = 3,
पूर्ण;

काष्ठा cdns_torrent_derived_refclk अणु
	काष्ठा clk_hw		hw;
	काष्ठा regmap_field	*phy_pipe_cmn_ctrl1_0;
	काष्ठा regmap_field	*cmn_fields[REFCLK_OUT_NUM_CMN_CONFIG];
	काष्ठा clk_init_data	clk_data;
पूर्ण;

#घोषणा to_cdns_torrent_derived_refclk(_hw)	\
			container_of(_hw, काष्ठा cdns_torrent_derived_refclk, hw)

अटल पूर्णांक cdns_torrent_phy_init(काष्ठा phy *phy);
अटल पूर्णांक cdns_torrent_dp_init(काष्ठा phy *phy);
अटल पूर्णांक cdns_torrent_dp_run(काष्ठा cdns_torrent_phy *cdns_phy,
			       u32 num_lanes);
अटल
पूर्णांक cdns_torrent_dp_रुको_pma_cmn_पढ़ोy(काष्ठा cdns_torrent_phy *cdns_phy);
अटल व्योम cdns_torrent_dp_pma_cfg(काष्ठा cdns_torrent_phy *cdns_phy,
				    काष्ठा cdns_torrent_inst *inst);
अटल
व्योम cdns_torrent_dp_pma_cmn_cfg_19_2mhz(काष्ठा cdns_torrent_phy *cdns_phy);
अटल
व्योम cdns_torrent_dp_pma_cmn_vco_cfg_19_2mhz(काष्ठा cdns_torrent_phy *cdns_phy,
					     u32 rate, bool ssc);
अटल
व्योम cdns_torrent_dp_pma_cmn_cfg_25mhz(काष्ठा cdns_torrent_phy *cdns_phy);
अटल
व्योम cdns_torrent_dp_pma_cmn_vco_cfg_25mhz(काष्ठा cdns_torrent_phy *cdns_phy,
					   u32 rate, bool ssc);
अटल व्योम cdns_torrent_dp_pma_lane_cfg(काष्ठा cdns_torrent_phy *cdns_phy,
					 अचिन्हित पूर्णांक lane);
अटल व्योम cdns_torrent_dp_pma_cmn_rate(काष्ठा cdns_torrent_phy *cdns_phy,
					 u32 rate, u32 num_lanes);
अटल पूर्णांक cdns_torrent_dp_configure(काष्ठा phy *phy,
				     जोड़ phy_configure_opts *opts);
अटल पूर्णांक cdns_torrent_dp_set_घातer_state(काष्ठा cdns_torrent_phy *cdns_phy,
					   u32 num_lanes,
					   क्रमागत phy_घातerstate घातerstate);
अटल पूर्णांक cdns_torrent_phy_on(काष्ठा phy *phy);
अटल पूर्णांक cdns_torrent_phy_off(काष्ठा phy *phy);

अटल स्थिर काष्ठा phy_ops cdns_torrent_phy_ops = अणु
	.init		= cdns_torrent_phy_init,
	.configure	= cdns_torrent_dp_configure,
	.घातer_on	= cdns_torrent_phy_on,
	.घातer_off	= cdns_torrent_phy_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक cdns_torrent_noop_phy_on(काष्ठा phy *phy)
अणु
	/* Give 5ms to 10ms delay क्रम the PIPE घड़ी to be stable */
	usleep_range(5000, 10000);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops noop_ops = अणु
	.घातer_on	= cdns_torrent_noop_phy_on,
	.owner		= THIS_MODULE,
पूर्ण;

काष्ठा cdns_reg_pairs अणु
	u32 val;
	u32 off;
पूर्ण;

काष्ठा cdns_torrent_vals अणु
	काष्ठा cdns_reg_pairs *reg_pairs;
	u32 num_regs;
पूर्ण;

काष्ठा cdns_torrent_data अणु
	u8 block_offset_shअगरt;
	u8 reg_offset_shअगरt;
	काष्ठा cdns_torrent_vals *link_cmn_vals[NUM_PHY_TYPE][NUM_PHY_TYPE]
					       [NUM_SSC_MODE];
	काष्ठा cdns_torrent_vals *xcvr_diag_vals[NUM_PHY_TYPE][NUM_PHY_TYPE]
						[NUM_SSC_MODE];
	काष्ठा cdns_torrent_vals *pcs_cmn_vals[NUM_PHY_TYPE][NUM_PHY_TYPE]
					      [NUM_SSC_MODE];
	काष्ठा cdns_torrent_vals *cmn_vals[NUM_PHY_TYPE][NUM_PHY_TYPE]
					  [NUM_SSC_MODE];
	काष्ठा cdns_torrent_vals *tx_ln_vals[NUM_PHY_TYPE][NUM_PHY_TYPE]
					    [NUM_SSC_MODE];
	काष्ठा cdns_torrent_vals *rx_ln_vals[NUM_PHY_TYPE][NUM_PHY_TYPE]
					    [NUM_SSC_MODE];
पूर्ण;

काष्ठा cdns_regmap_cdb_context अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	u8 reg_offset_shअगरt;
पूर्ण;

अटल पूर्णांक cdns_regmap_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा cdns_regmap_cdb_context *ctx = context;
	u32 offset = reg << ctx->reg_offset_shअगरt;

	ग_लिखोw(val, ctx->base + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_regmap_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा cdns_regmap_cdb_context *ctx = context;
	u32 offset = reg << ctx->reg_offset_shअगरt;

	*val = पढ़ोw(ctx->base + offset);
	वापस 0;
पूर्ण

अटल पूर्णांक cdns_regmap_dptx_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	काष्ठा cdns_regmap_cdb_context *ctx = context;
	u32 offset = reg;

	ग_लिखोl(val, ctx->base + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_regmap_dptx_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक *val)
अणु
	काष्ठा cdns_regmap_cdb_context *ctx = context;
	u32 offset = reg;

	*val = पढ़ोl(ctx->base + offset);
	वापस 0;
पूर्ण

#घोषणा TORRENT_TX_LANE_CDB_REGMAP_CONF(n) \
अणु \
	.name = "torrent_tx_lane" n "_cdb", \
	.reg_stride = 1, \
	.fast_io = true, \
	.reg_ग_लिखो = cdns_regmap_ग_लिखो, \
	.reg_पढ़ो = cdns_regmap_पढ़ो, \
पूर्ण

#घोषणा TORRENT_RX_LANE_CDB_REGMAP_CONF(n) \
अणु \
	.name = "torrent_rx_lane" n "_cdb", \
	.reg_stride = 1, \
	.fast_io = true, \
	.reg_ग_लिखो = cdns_regmap_ग_लिखो, \
	.reg_पढ़ो = cdns_regmap_पढ़ो, \
पूर्ण

अटल स्थिर काष्ठा regmap_config cdns_torrent_tx_lane_cdb_config[] = अणु
	TORRENT_TX_LANE_CDB_REGMAP_CONF("0"),
	TORRENT_TX_LANE_CDB_REGMAP_CONF("1"),
	TORRENT_TX_LANE_CDB_REGMAP_CONF("2"),
	TORRENT_TX_LANE_CDB_REGMAP_CONF("3"),
पूर्ण;

अटल स्थिर काष्ठा regmap_config cdns_torrent_rx_lane_cdb_config[] = अणु
	TORRENT_RX_LANE_CDB_REGMAP_CONF("0"),
	TORRENT_RX_LANE_CDB_REGMAP_CONF("1"),
	TORRENT_RX_LANE_CDB_REGMAP_CONF("2"),
	TORRENT_RX_LANE_CDB_REGMAP_CONF("3"),
पूर्ण;

अटल स्थिर काष्ठा regmap_config cdns_torrent_common_cdb_config = अणु
	.name = "torrent_common_cdb",
	.reg_stride = 1,
	.fast_io = true,
	.reg_ग_लिखो = cdns_regmap_ग_लिखो,
	.reg_पढ़ो = cdns_regmap_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cdns_torrent_phy_pcs_cmn_cdb_config = अणु
	.name = "torrent_phy_pcs_cmn_cdb",
	.reg_stride = 1,
	.fast_io = true,
	.reg_ग_लिखो = cdns_regmap_ग_लिखो,
	.reg_पढ़ो = cdns_regmap_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cdns_torrent_phy_pma_cmn_cdb_config = अणु
	.name = "torrent_phy_pma_cmn_cdb",
	.reg_stride = 1,
	.fast_io = true,
	.reg_ग_लिखो = cdns_regmap_ग_लिखो,
	.reg_पढ़ो = cdns_regmap_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cdns_torrent_dptx_phy_config = अणु
	.name = "torrent_dptx_phy",
	.reg_stride = 1,
	.fast_io = true,
	.reg_ग_लिखो = cdns_regmap_dptx_ग_लिखो,
	.reg_पढ़ो = cdns_regmap_dptx_पढ़ो,
पूर्ण;

/* PHY mmr access functions */

अटल व्योम cdns_torrent_phy_ग_लिखो(काष्ठा regmap *regmap, u32 offset, u32 val)
अणु
	regmap_ग_लिखो(regmap, offset, val);
पूर्ण

अटल u32 cdns_torrent_phy_पढ़ो(काष्ठा regmap *regmap, u32 offset)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(regmap, offset, &val);
	वापस val;
पूर्ण

/* DPTX mmr access functions */

अटल व्योम cdns_torrent_dp_ग_लिखो(काष्ठा regmap *regmap, u32 offset, u32 val)
अणु
	regmap_ग_लिखो(regmap, offset, val);
पूर्ण

अटल u32 cdns_torrent_dp_पढ़ो(काष्ठा regmap *regmap, u32 offset)
अणु
	u32 val;

	regmap_पढ़ो(regmap, offset, &val);
	वापस val;
पूर्ण

/*
 * Structure used to store values of PHY रेजिस्टरs क्रम voltage-related
 * coefficients, क्रम particular voltage swing and pre-emphasis level. Values
 * are shared across all physical lanes.
 */
काष्ठा coefficients अणु
	/* Value of DRV_DIAG_TX_DRV रेजिस्टर to use */
	u16 diag_tx_drv;
	/* Value of TX_TXCC_MGNFS_MULT_000 रेजिस्टर to use */
	u16 mgnfs_mult;
	/* Value of TX_TXCC_CPOST_MULT_00 रेजिस्टर to use */
	u16 cpost_mult;
पूर्ण;

/*
 * Array consists of values of voltage-related रेजिस्टरs क्रम sd0801 PHY. A value
 * of 0xFFFF is a placeholder क्रम invalid combination, and will never be used.
 */
अटल स्थिर काष्ठा coefficients vltg_coeff[4][4] = अणु
	/* voltage swing 0, pre-emphasis 0->3 */
	अणु	अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x002A,
		 .cpost_mult = 0x0000पूर्ण,
		अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x001F,
		 .cpost_mult = 0x0014पूर्ण,
		अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x0012,
		 .cpost_mult = 0x0020पूर्ण,
		अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x0000,
		 .cpost_mult = 0x002Aपूर्ण
	पूर्ण,

	/* voltage swing 1, pre-emphasis 0->3 */
	अणु	अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x001F,
		 .cpost_mult = 0x0000पूर्ण,
		अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x0013,
		 .cpost_mult = 0x0012पूर्ण,
		अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x0000,
		 .cpost_mult = 0x001Fपूर्ण,
		अणु.diag_tx_drv = 0xFFFF, .mgnfs_mult = 0xFFFF,
		 .cpost_mult = 0xFFFFपूर्ण
	पूर्ण,

	/* voltage swing 2, pre-emphasis 0->3 */
	अणु	अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x0013,
		 .cpost_mult = 0x0000पूर्ण,
		अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x0000,
		 .cpost_mult = 0x0013पूर्ण,
		अणु.diag_tx_drv = 0xFFFF, .mgnfs_mult = 0xFFFF,
		 .cpost_mult = 0xFFFFपूर्ण,
		अणु.diag_tx_drv = 0xFFFF, .mgnfs_mult = 0xFFFF,
		 .cpost_mult = 0xFFFFपूर्ण
	पूर्ण,

	/* voltage swing 3, pre-emphasis 0->3 */
	अणु	अणु.diag_tx_drv = 0x0003, .mgnfs_mult = 0x0000,
		 .cpost_mult = 0x0000पूर्ण,
		अणु.diag_tx_drv = 0xFFFF, .mgnfs_mult = 0xFFFF,
		 .cpost_mult = 0xFFFFपूर्ण,
		अणु.diag_tx_drv = 0xFFFF, .mgnfs_mult = 0xFFFF,
		 .cpost_mult = 0xFFFFपूर्ण,
		अणु.diag_tx_drv = 0xFFFF, .mgnfs_mult = 0xFFFF,
		 .cpost_mult = 0xFFFFपूर्ण
	पूर्ण
पूर्ण;

/*
 * Enable or disable PLL क्रम selected lanes.
 */
अटल पूर्णांक cdns_torrent_dp_set_pll_en(काष्ठा cdns_torrent_phy *cdns_phy,
				      काष्ठा phy_configure_opts_dp *dp,
				      bool enable)
अणु
	u32 rd_val;
	u32 ret;
	काष्ठा regmap *regmap = cdns_phy->regmap_dptx_phy_reg;

	/*
	 * Used to determine, which bits to check क्रम or enable in
	 * PHY_PMA_XCVR_PLLCLK_EN रेजिस्टर.
	 */
	u32 pll_bits;
	/* Used to enable or disable lanes. */
	u32 pll_val;

	/* Select values of रेजिस्टरs and mask, depending on enabled lane
	 * count.
	 */
	चयन (dp->lanes) अणु
	/* lane 0 */
	हाल (1):
		pll_bits = 0x00000001;
		अवरोध;
	/* lanes 0-1 */
	हाल (2):
		pll_bits = 0x00000003;
		अवरोध;
	/* lanes 0-3, all */
	शेष:
		pll_bits = 0x0000000F;
		अवरोध;
	पूर्ण

	अगर (enable)
		pll_val = pll_bits;
	अन्यथा
		pll_val = 0x00000000;

	cdns_torrent_dp_ग_लिखो(regmap, PHY_PMA_XCVR_PLLCLK_EN, pll_val);

	/* Wait क्रम acknowledgment from PHY. */
	ret = regmap_पढ़ो_poll_समयout(regmap,
				       PHY_PMA_XCVR_PLLCLK_EN_ACK,
				       rd_val,
				       (rd_val & pll_bits) == pll_val,
				       0, POLL_TIMEOUT_US);
	ndelay(100);
	वापस ret;
पूर्ण

/*
 * Perक्रमm रेजिस्टर operations related to setting link rate, once घातerstate is
 * set and PLL disable request was processed.
 */
अटल पूर्णांक cdns_torrent_dp_configure_rate(काष्ठा cdns_torrent_phy *cdns_phy,
					  काष्ठा phy_configure_opts_dp *dp)
अणु
	u32 ret;
	u32 पढ़ो_val;

	/* Disable the cmn_pll0_en beक्रमe re-programming the new data rate. */
	regmap_field_ग_लिखो(cdns_phy->phy_pma_pll_raw_ctrl, 0x0);

	/*
	 * Wait क्रम PLL पढ़ोy de-निश्चितion.
	 * For PLL0 - PHY_PMA_CMN_CTRL2[2] == 1
	 */
	ret = regmap_field_पढ़ो_poll_समयout(cdns_phy->phy_pma_cmn_ctrl_2,
					     पढ़ो_val,
					     ((पढ़ो_val >> 2) & 0x01) != 0,
					     0, POLL_TIMEOUT_US);
	अगर (ret)
		वापस ret;
	ndelay(200);

	/* DP Rate Change - VCO Output settings. */
	अगर (cdns_phy->ref_clk_rate == REF_CLK_19_2MHz) अणु
		/* PMA common configuration 19.2MHz */
		cdns_torrent_dp_pma_cmn_vco_cfg_19_2mhz(cdns_phy, dp->link_rate,
							dp->ssc);
		cdns_torrent_dp_pma_cmn_cfg_19_2mhz(cdns_phy);
	पूर्ण अन्यथा अगर (cdns_phy->ref_clk_rate == REF_CLK_25MHz) अणु
		/* PMA common configuration 25MHz */
		cdns_torrent_dp_pma_cmn_vco_cfg_25mhz(cdns_phy, dp->link_rate,
						      dp->ssc);
		cdns_torrent_dp_pma_cmn_cfg_25mhz(cdns_phy);
	पूर्ण
	cdns_torrent_dp_pma_cmn_rate(cdns_phy, dp->link_rate, dp->lanes);

	/* Enable the cmn_pll0_en. */
	regmap_field_ग_लिखो(cdns_phy->phy_pma_pll_raw_ctrl, 0x3);

	/*
	 * Wait क्रम PLL पढ़ोy निश्चितion.
	 * For PLL0 - PHY_PMA_CMN_CTRL2[0] == 1
	 */
	ret = regmap_field_पढ़ो_poll_समयout(cdns_phy->phy_pma_cmn_ctrl_2,
					     पढ़ो_val,
					     (पढ़ो_val & 0x01) != 0,
					     0, POLL_TIMEOUT_US);
	वापस ret;
पूर्ण

/*
 * Verअगरy, that parameters to configure PHY with are correct.
 */
अटल पूर्णांक cdns_torrent_dp_verअगरy_config(काष्ठा cdns_torrent_inst *inst,
					 काष्ठा phy_configure_opts_dp *dp)
अणु
	u8 i;

	/* If changing link rate was required, verअगरy it's supported. */
	अगर (dp->set_rate) अणु
		चयन (dp->link_rate) अणु
		हाल 1620:
		हाल 2160:
		हाल 2430:
		हाल 2700:
		हाल 3240:
		हाल 4320:
		हाल 5400:
		हाल 8100:
			/* valid bit rate */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Verअगरy lane count. */
	चयन (dp->lanes) अणु
	हाल 1:
	हाल 2:
	हाल 4:
		/* valid lane count. */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Check against actual number of PHY's lanes. */
	अगर (dp->lanes > inst->num_lanes)
		वापस -EINVAL;

	/*
	 * If changing voltages is required, check swing and pre-emphasis
	 * levels, per-lane.
	 */
	अगर (dp->set_voltages) अणु
		/* Lane count verअगरied previously. */
		क्रम (i = 0; i < dp->lanes; i++) अणु
			अगर (dp->voltage[i] > 3 || dp->pre[i] > 3)
				वापस -EINVAL;

			/* Sum of voltage swing and pre-emphasis levels cannot
			 * exceed 3.
			 */
			अगर (dp->voltage[i] + dp->pre[i] > 3)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Set घातer state A0 and PLL घड़ी enable to 0 on enabled lanes. */
अटल व्योम cdns_torrent_dp_set_a0_pll(काष्ठा cdns_torrent_phy *cdns_phy,
				       u32 num_lanes)
अणु
	काष्ठा regmap *regmap = cdns_phy->regmap_dptx_phy_reg;
	u32 pwr_state = cdns_torrent_dp_पढ़ो(regmap,
					     PHY_PMA_XCVR_POWER_STATE_REQ);
	u32 pll_clk_en = cdns_torrent_dp_पढ़ो(regmap,
					      PHY_PMA_XCVR_PLLCLK_EN);

	/* Lane 0 is always enabled. */
	pwr_state &= ~(PMA_XCVR_POWER_STATE_REQ_LN_MASK <<
		       PHY_POWER_STATE_LN_0);
	pll_clk_en &= ~0x01U;

	अगर (num_lanes > 1) अणु
		/* lane 1 */
		pwr_state &= ~(PMA_XCVR_POWER_STATE_REQ_LN_MASK <<
			       PHY_POWER_STATE_LN_1);
		pll_clk_en &= ~(0x01U << 1);
	पूर्ण

	अगर (num_lanes > 2) अणु
		/* lanes 2 and 3 */
		pwr_state &= ~(PMA_XCVR_POWER_STATE_REQ_LN_MASK <<
			       PHY_POWER_STATE_LN_2);
		pwr_state &= ~(PMA_XCVR_POWER_STATE_REQ_LN_MASK <<
			       PHY_POWER_STATE_LN_3);
		pll_clk_en &= ~(0x01U << 2);
		pll_clk_en &= ~(0x01U << 3);
	पूर्ण

	cdns_torrent_dp_ग_लिखो(regmap, PHY_PMA_XCVR_POWER_STATE_REQ, pwr_state);
	cdns_torrent_dp_ग_लिखो(regmap, PHY_PMA_XCVR_PLLCLK_EN, pll_clk_en);
पूर्ण

/* Configure lane count as required. */
अटल पूर्णांक cdns_torrent_dp_set_lanes(काष्ठा cdns_torrent_phy *cdns_phy,
				     काष्ठा phy_configure_opts_dp *dp)
अणु
	u32 value;
	u32 ret;
	काष्ठा regmap *regmap = cdns_phy->regmap_dptx_phy_reg;
	u8 lane_mask = (1 << dp->lanes) - 1;

	value = cdns_torrent_dp_पढ़ो(regmap, PHY_RESET);
	/* clear pma_tx_elec_idle_ln_* bits. */
	value &= ~PMA_TX_ELEC_IDLE_MASK;
	/* Assert pma_tx_elec_idle_ln_* क्रम disabled lanes. */
	value |= ((~lane_mask) << PMA_TX_ELEC_IDLE_SHIFT) &
		 PMA_TX_ELEC_IDLE_MASK;
	cdns_torrent_dp_ग_लिखो(regmap, PHY_RESET, value);

	/* reset the link by निश्चितing phy_l00_reset_n low */
	cdns_torrent_dp_ग_लिखो(regmap, PHY_RESET,
			      value & (~PHY_L00_RESET_N_MASK));

	/*
	 * Assert lane reset on unused lanes and lane 0 so they reमुख्य in reset
	 * and घातered करोwn when re-enabling the link
	 */
	value = (value & 0x0000FFF0) | (0x0000000E & lane_mask);
	cdns_torrent_dp_ग_लिखो(regmap, PHY_RESET, value);

	cdns_torrent_dp_set_a0_pll(cdns_phy, dp->lanes);

	/* release phy_l0*_reset_n based on used laneCount */
	value = (value & 0x0000FFF0) | (0x0000000F & lane_mask);
	cdns_torrent_dp_ग_लिखो(regmap, PHY_RESET, value);

	/* Wait, until PHY माला_लो पढ़ोy after releasing PHY reset संकेत. */
	ret = cdns_torrent_dp_रुको_pma_cmn_पढ़ोy(cdns_phy);
	अगर (ret)
		वापस ret;

	ndelay(100);

	/* release pma_xcvr_pllclk_en_ln_*, only क्रम the master lane */
	cdns_torrent_dp_ग_लिखो(regmap, PHY_PMA_XCVR_PLLCLK_EN, 0x0001);

	ret = cdns_torrent_dp_run(cdns_phy, dp->lanes);

	वापस ret;
पूर्ण

/* Configure link rate as required. */
अटल पूर्णांक cdns_torrent_dp_set_rate(काष्ठा cdns_torrent_phy *cdns_phy,
				    काष्ठा phy_configure_opts_dp *dp)
अणु
	u32 ret;

	ret = cdns_torrent_dp_set_घातer_state(cdns_phy, dp->lanes,
					      POWERSTATE_A3);
	अगर (ret)
		वापस ret;
	ret = cdns_torrent_dp_set_pll_en(cdns_phy, dp, false);
	अगर (ret)
		वापस ret;
	ndelay(200);

	ret = cdns_torrent_dp_configure_rate(cdns_phy, dp);
	अगर (ret)
		वापस ret;
	ndelay(200);

	ret = cdns_torrent_dp_set_pll_en(cdns_phy, dp, true);
	अगर (ret)
		वापस ret;
	ret = cdns_torrent_dp_set_घातer_state(cdns_phy, dp->lanes,
					      POWERSTATE_A2);
	अगर (ret)
		वापस ret;
	ret = cdns_torrent_dp_set_घातer_state(cdns_phy, dp->lanes,
					      POWERSTATE_A0);
	अगर (ret)
		वापस ret;
	ndelay(900);

	वापस ret;
पूर्ण

/* Configure voltage swing and pre-emphasis क्रम all enabled lanes. */
अटल व्योम cdns_torrent_dp_set_voltages(काष्ठा cdns_torrent_phy *cdns_phy,
					 काष्ठा phy_configure_opts_dp *dp)
अणु
	u8 lane;
	u16 val;

	क्रम (lane = 0; lane < dp->lanes; lane++) अणु
		val = cdns_torrent_phy_पढ़ो(cdns_phy->regmap_tx_lane_cdb[lane],
					    TX_DIAG_ACYA);
		/*
		 * Write 1 to रेजिस्टर bit TX_DIAG_ACYA[0] to मुक्तze the
		 * current state of the analog TX driver.
		 */
		val |= TX_DIAG_ACYA_HBDC_MASK;
		cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
				       TX_DIAG_ACYA, val);

		cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
				       TX_TXCC_CTRL, 0x08A4);
		val = vltg_coeff[dp->voltage[lane]][dp->pre[lane]].diag_tx_drv;
		cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
				       DRV_DIAG_TX_DRV, val);
		val = vltg_coeff[dp->voltage[lane]][dp->pre[lane]].mgnfs_mult;
		cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
				       TX_TXCC_MGNFS_MULT_000,
				       val);
		val = vltg_coeff[dp->voltage[lane]][dp->pre[lane]].cpost_mult;
		cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
				       TX_TXCC_CPOST_MULT_00,
				       val);

		val = cdns_torrent_phy_पढ़ो(cdns_phy->regmap_tx_lane_cdb[lane],
					    TX_DIAG_ACYA);
		/*
		 * Write 0 to रेजिस्टर bit TX_DIAG_ACYA[0] to allow the state of
		 * analog TX driver to reflect the new programmed one.
		 */
		val &= ~TX_DIAG_ACYA_HBDC_MASK;
		cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
				       TX_DIAG_ACYA, val);
	पूर्ण
पूर्ण;

अटल पूर्णांक cdns_torrent_dp_configure(काष्ठा phy *phy,
				     जोड़ phy_configure_opts *opts)
अणु
	काष्ठा cdns_torrent_inst *inst = phy_get_drvdata(phy);
	काष्ठा cdns_torrent_phy *cdns_phy = dev_get_drvdata(phy->dev.parent);
	पूर्णांक ret;

	ret = cdns_torrent_dp_verअगरy_config(inst, &opts->dp);
	अगर (ret) अणु
		dev_err(&phy->dev, "invalid params for phy configure\n");
		वापस ret;
	पूर्ण

	अगर (opts->dp.set_lanes) अणु
		ret = cdns_torrent_dp_set_lanes(cdns_phy, &opts->dp);
		अगर (ret) अणु
			dev_err(&phy->dev, "cdns_torrent_dp_set_lanes failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (opts->dp.set_rate) अणु
		ret = cdns_torrent_dp_set_rate(cdns_phy, &opts->dp);
		अगर (ret) अणु
			dev_err(&phy->dev, "cdns_torrent_dp_set_rate failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (opts->dp.set_voltages)
		cdns_torrent_dp_set_voltages(cdns_phy, &opts->dp);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_torrent_dp_init(काष्ठा phy *phy)
अणु
	अचिन्हित अक्षर lane_bits;
	पूर्णांक ret;
	काष्ठा cdns_torrent_inst *inst = phy_get_drvdata(phy);
	काष्ठा cdns_torrent_phy *cdns_phy = dev_get_drvdata(phy->dev.parent);
	काष्ठा regmap *regmap = cdns_phy->regmap_dptx_phy_reg;

	चयन (cdns_phy->ref_clk_rate) अणु
	हाल REF_CLK_19_2MHz:
	हाल REF_CLK_25MHz:
		/* Valid Ref Clock Rate */
		अवरोध;
	शेष:
		dev_err(cdns_phy->dev, "Unsupported Ref Clock Rate\n");
		वापस -EINVAL;
	पूर्ण

	cdns_torrent_dp_ग_लिखो(regmap, PHY_AUX_CTRL, 0x0003); /* enable AUX */

	/* PHY PMA रेजिस्टरs configuration function */
	cdns_torrent_dp_pma_cfg(cdns_phy, inst);

	/*
	 * Set lines घातer state to A0
	 * Set lines pll clk enable to 0
	 */
	cdns_torrent_dp_set_a0_pll(cdns_phy, inst->num_lanes);

	/*
	 * release phy_l0*_reset_n and pma_tx_elec_idle_ln_* based on
	 * used lanes
	 */
	lane_bits = (1 << inst->num_lanes) - 1;
	cdns_torrent_dp_ग_लिखो(regmap, PHY_RESET,
			      ((0xF & ~lane_bits) << 4) | (0xF & lane_bits));

	/* release pma_xcvr_pllclk_en_ln_*, only क्रम the master lane */
	cdns_torrent_dp_ग_लिखो(regmap, PHY_PMA_XCVR_PLLCLK_EN, 0x0001);

	/* PHY PMA रेजिस्टरs configuration functions */
	/* Initialize PHY with max supported link rate, without SSC. */
	अगर (cdns_phy->ref_clk_rate == REF_CLK_19_2MHz)
		cdns_torrent_dp_pma_cmn_vco_cfg_19_2mhz(cdns_phy,
							cdns_phy->max_bit_rate,
							false);
	अन्यथा अगर (cdns_phy->ref_clk_rate == REF_CLK_25MHz)
		cdns_torrent_dp_pma_cmn_vco_cfg_25mhz(cdns_phy,
						      cdns_phy->max_bit_rate,
						      false);
	cdns_torrent_dp_pma_cmn_rate(cdns_phy, cdns_phy->max_bit_rate,
				     inst->num_lanes);

	/* take out of reset */
	regmap_field_ग_लिखो(cdns_phy->phy_reset_ctrl, 0x1);

	cdns_torrent_phy_on(phy);

	ret = cdns_torrent_dp_रुको_pma_cmn_पढ़ोy(cdns_phy);
	अगर (ret)
		वापस ret;

	ret = cdns_torrent_dp_run(cdns_phy, inst->num_lanes);

	वापस ret;
पूर्ण

अटल
पूर्णांक cdns_torrent_dp_रुको_pma_cmn_पढ़ोy(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	काष्ठा regmap *regmap = cdns_phy->regmap_dptx_phy_reg;

	ret = regmap_पढ़ो_poll_समयout(regmap, PHY_PMA_CMN_READY, reg,
				       reg & 1, 0, POLL_TIMEOUT_US);
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(cdns_phy->dev,
			"timeout waiting for PMA common ready\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cdns_torrent_dp_pma_cfg(काष्ठा cdns_torrent_phy *cdns_phy,
				    काष्ठा cdns_torrent_inst *inst)
अणु
	अचिन्हित पूर्णांक i;

	अगर (cdns_phy->ref_clk_rate == REF_CLK_19_2MHz)
		/* PMA common configuration 19.2MHz */
		cdns_torrent_dp_pma_cmn_cfg_19_2mhz(cdns_phy);
	अन्यथा अगर (cdns_phy->ref_clk_rate == REF_CLK_25MHz)
		/* PMA common configuration 25MHz */
		cdns_torrent_dp_pma_cmn_cfg_25mhz(cdns_phy);

	/* PMA lane configuration to deal with multi-link operation */
	क्रम (i = 0; i < inst->num_lanes; i++)
		cdns_torrent_dp_pma_lane_cfg(cdns_phy, i);
पूर्ण

अटल
व्योम cdns_torrent_dp_pma_cmn_cfg_19_2mhz(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	काष्ठा regmap *regmap = cdns_phy->regmap_common_cdb;

	/* refघड़ी रेजिस्टरs - assumes 19.2 MHz refघड़ी */
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SSM_BIAS_TMR, 0x0014);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLLSM0_PLLPRE_TMR, 0x0027);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLLSM0_PLLLOCK_TMR, 0x00A1);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLLSM1_PLLPRE_TMR, 0x0027);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLLSM1_PLLLOCK_TMR, 0x00A1);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_BGCAL_INIT_TMR, 0x0060);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_BGCAL_ITER_TMR, 0x0060);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_IBCAL_INIT_TMR, 0x0014);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_TXPUCAL_INIT_TMR, 0x0018);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_TXPUCAL_ITER_TMR, 0x0005);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_TXPDCAL_INIT_TMR, 0x0018);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_TXPDCAL_ITER_TMR, 0x0005);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_RXCAL_INIT_TMR, 0x0240);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_RXCAL_ITER_TMR, 0x0005);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SD_CAL_INIT_TMR, 0x0002);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SD_CAL_ITER_TMR, 0x0002);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SD_CAL_REFTIM_START, 0x000B);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SD_CAL_PLLCNT_START, 0x0137);

	/* PLL रेजिस्टरs */
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL0_CP_PADJ_M0, 0x0509);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL0_CP_IADJ_M0, 0x0F00);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL0_FILT_PADJ_M0, 0x0F08);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_DSM_DIAG_M0, 0x0004);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL1_CP_PADJ_M0, 0x0509);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL1_CP_IADJ_M0, 0x0F00);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL1_FILT_PADJ_M0, 0x0F08);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_DSM_DIAG_M0, 0x0004);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_VCOCAL_INIT_TMR, 0x00C0);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_VCOCAL_ITER_TMR, 0x0004);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_VCOCAL_INIT_TMR, 0x00C0);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_VCOCAL_ITER_TMR, 0x0004);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_VCOCAL_REFTIM_START, 0x0260);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_VCOCAL_TCTRL, 0x0003);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_VCOCAL_REFTIM_START, 0x0260);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_VCOCAL_TCTRL, 0x0003);
पूर्ण

/*
 * Set रेजिस्टरs responsible क्रम enabling and configuring SSC, with second and
 * third रेजिस्टर values provided by parameters.
 */
अटल
व्योम cdns_torrent_dp_enable_ssc_19_2mhz(काष्ठा cdns_torrent_phy *cdns_phy,
					u32 ctrl2_val, u32 ctrl3_val)
अणु
	काष्ठा regmap *regmap = cdns_phy->regmap_common_cdb;

	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL1_M0, 0x0001);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL1_M0, ctrl2_val);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL1_M0, ctrl3_val);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL4_M0, 0x0003);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL1_M0, 0x0001);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL1_M0, ctrl2_val);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL1_M0, ctrl3_val);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL4_M0, 0x0003);
पूर्ण

अटल
व्योम cdns_torrent_dp_pma_cmn_vco_cfg_19_2mhz(काष्ठा cdns_torrent_phy *cdns_phy,
					     u32 rate, bool ssc)
अणु
	काष्ठा regmap *regmap = cdns_phy->regmap_common_cdb;

	/* Assumes 19.2 MHz refघड़ी */
	चयन (rate) अणु
	/* Setting VCO क्रम 10.8GHz */
	हाल 2700:
	हाल 5400:
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_INTDIV_M0, 0x0119);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_FRACDIVL_M0, 0x4000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_HIGH_THR_M0, 0x00BC);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PDIAG_PLL0_CTRL_M0, 0x0012);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_INTDIV_M0, 0x0119);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_FRACDIVL_M0, 0x4000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_HIGH_THR_M0, 0x00BC);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PDIAG_PLL1_CTRL_M0, 0x0012);
		अगर (ssc)
			cdns_torrent_dp_enable_ssc_19_2mhz(cdns_phy, 0x033A,
							   0x006A);
		अवरोध;
	/* Setting VCO क्रम 9.72GHz */
	हाल 1620:
	हाल 2430:
	हाल 3240:
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_INTDIV_M0, 0x01FA);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_FRACDIVL_M0, 0x4000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_HIGH_THR_M0, 0x0152);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PDIAG_PLL0_CTRL_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_INTDIV_M0, 0x01FA);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_FRACDIVL_M0, 0x4000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_HIGH_THR_M0, 0x0152);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PDIAG_PLL1_CTRL_M0, 0x0002);
		अगर (ssc)
			cdns_torrent_dp_enable_ssc_19_2mhz(cdns_phy, 0x05DD,
							   0x0069);
		अवरोध;
	/* Setting VCO क्रम 8.64GHz */
	हाल 2160:
	हाल 4320:
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_INTDIV_M0, 0x01C2);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_FRACDIVL_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_HIGH_THR_M0, 0x012C);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PDIAG_PLL0_CTRL_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_INTDIV_M0, 0x01C2);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_FRACDIVL_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_HIGH_THR_M0, 0x012C);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PDIAG_PLL1_CTRL_M0, 0x0002);
		अगर (ssc)
			cdns_torrent_dp_enable_ssc_19_2mhz(cdns_phy, 0x0536,
							   0x0069);
		अवरोध;
	/* Setting VCO क्रम 8.1GHz */
	हाल 8100:
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_INTDIV_M0, 0x01A5);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_FRACDIVL_M0, 0xE000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_HIGH_THR_M0, 0x011A);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PDIAG_PLL0_CTRL_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_INTDIV_M0, 0x01A5);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_FRACDIVL_M0, 0xE000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_HIGH_THR_M0, 0x011A);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PDIAG_PLL1_CTRL_M0, 0x0002);
		अगर (ssc)
			cdns_torrent_dp_enable_ssc_19_2mhz(cdns_phy, 0x04D7,
							   0x006A);
		अवरोध;
	पूर्ण

	अगर (ssc) अणु
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_VCOCAL_PLLCNT_START, 0x025E);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_LOCK_PLLCNT_THR, 0x0005);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_VCOCAL_PLLCNT_START, 0x025E);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_LOCK_PLLCNT_THR, 0x0005);
	पूर्ण अन्यथा अणु
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_VCOCAL_PLLCNT_START, 0x0260);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_VCOCAL_PLLCNT_START, 0x0260);
		/* Set reset रेजिस्टर values to disable SSC */
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_SS_CTRL1_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_SS_CTRL2_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_SS_CTRL3_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_SS_CTRL4_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_LOCK_PLLCNT_THR, 0x0003);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_SS_CTRL1_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_SS_CTRL2_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_SS_CTRL3_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_SS_CTRL4_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_LOCK_PLLCNT_THR, 0x0003);
	पूर्ण

	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_LOCK_REFCNT_START, 0x0099);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_LOCK_PLLCNT_START, 0x0099);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_LOCK_REFCNT_START, 0x0099);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_LOCK_PLLCNT_START, 0x0099);
पूर्ण

अटल
व्योम cdns_torrent_dp_pma_cmn_cfg_25mhz(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	काष्ठा regmap *regmap = cdns_phy->regmap_common_cdb;

	/* refघड़ी रेजिस्टरs - assumes 25 MHz refघड़ी */
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SSM_BIAS_TMR, 0x0019);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLLSM0_PLLPRE_TMR, 0x0032);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLLSM0_PLLLOCK_TMR, 0x00D1);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLLSM1_PLLPRE_TMR, 0x0032);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLLSM1_PLLLOCK_TMR, 0x00D1);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_BGCAL_INIT_TMR, 0x007D);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_BGCAL_ITER_TMR, 0x007D);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_IBCAL_INIT_TMR, 0x0019);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_TXPUCAL_INIT_TMR, 0x001E);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_TXPUCAL_ITER_TMR, 0x0006);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_TXPDCAL_INIT_TMR, 0x001E);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_TXPDCAL_ITER_TMR, 0x0006);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_RXCAL_INIT_TMR, 0x02EE);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_RXCAL_ITER_TMR, 0x0006);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SD_CAL_INIT_TMR, 0x0002);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SD_CAL_ITER_TMR, 0x0002);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SD_CAL_REFTIM_START, 0x000E);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_SD_CAL_PLLCNT_START, 0x012B);

	/* PLL रेजिस्टरs */
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL0_CP_PADJ_M0, 0x0509);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL0_CP_IADJ_M0, 0x0F00);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL0_FILT_PADJ_M0, 0x0F08);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_DSM_DIAG_M0, 0x0004);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL1_CP_PADJ_M0, 0x0509);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL1_CP_IADJ_M0, 0x0F00);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL1_FILT_PADJ_M0, 0x0F08);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_DSM_DIAG_M0, 0x0004);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_VCOCAL_INIT_TMR, 0x00FA);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_VCOCAL_ITER_TMR, 0x0004);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_VCOCAL_INIT_TMR, 0x00FA);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_VCOCAL_ITER_TMR, 0x0004);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_VCOCAL_REFTIM_START, 0x0317);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_VCOCAL_TCTRL, 0x0003);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_VCOCAL_REFTIM_START, 0x0317);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_VCOCAL_TCTRL, 0x0003);
पूर्ण

/*
 * Set रेजिस्टरs responsible क्रम enabling and configuring SSC, with second
 * रेजिस्टर value provided by a parameter.
 */
अटल व्योम cdns_torrent_dp_enable_ssc_25mhz(काष्ठा cdns_torrent_phy *cdns_phy,
					     u32 ctrl2_val)
अणु
	काष्ठा regmap *regmap = cdns_phy->regmap_common_cdb;

	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL1_M0, 0x0001);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL1_M0, ctrl2_val);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL1_M0, 0x007F);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL4_M0, 0x0003);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL1_M0, 0x0001);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL1_M0, ctrl2_val);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL1_M0, 0x007F);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL4_M0, 0x0003);
पूर्ण

अटल
व्योम cdns_torrent_dp_pma_cmn_vco_cfg_25mhz(काष्ठा cdns_torrent_phy *cdns_phy,
					   u32 rate, bool ssc)
अणु
	काष्ठा regmap *regmap = cdns_phy->regmap_common_cdb;

	/* Assumes 25 MHz refघड़ी */
	चयन (rate) अणु
	/* Setting VCO क्रम 10.8GHz */
	हाल 2700:
	हाल 5400:
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_INTDIV_M0, 0x01B0);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_FRACDIVL_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_HIGH_THR_M0, 0x0120);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_INTDIV_M0, 0x01B0);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_FRACDIVL_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_HIGH_THR_M0, 0x0120);
		अगर (ssc)
			cdns_torrent_dp_enable_ssc_25mhz(cdns_phy, 0x0423);
		अवरोध;
	/* Setting VCO क्रम 9.72GHz */
	हाल 1620:
	हाल 2430:
	हाल 3240:
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_INTDIV_M0, 0x0184);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_FRACDIVL_M0, 0xCCCD);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_HIGH_THR_M0, 0x0104);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_INTDIV_M0, 0x0184);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_FRACDIVL_M0, 0xCCCD);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_HIGH_THR_M0, 0x0104);
		अगर (ssc)
			cdns_torrent_dp_enable_ssc_25mhz(cdns_phy, 0x03B9);
		अवरोध;
	/* Setting VCO क्रम 8.64GHz */
	हाल 2160:
	हाल 4320:
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_INTDIV_M0, 0x0159);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_FRACDIVL_M0, 0x999A);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_HIGH_THR_M0, 0x00E7);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_INTDIV_M0, 0x0159);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_FRACDIVL_M0, 0x999A);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_HIGH_THR_M0, 0x00E7);
		अगर (ssc)
			cdns_torrent_dp_enable_ssc_25mhz(cdns_phy, 0x034F);
		अवरोध;
	/* Setting VCO क्रम 8.1GHz */
	हाल 8100:
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_INTDIV_M0, 0x0144);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_FRACDIVL_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_HIGH_THR_M0, 0x00D8);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_INTDIV_M0, 0x0144);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_FRACDIVL_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_FRACDIVH_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_HIGH_THR_M0, 0x00D8);
		अगर (ssc)
			cdns_torrent_dp_enable_ssc_25mhz(cdns_phy, 0x031A);
		अवरोध;
	पूर्ण

	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL0_CTRL_M0, 0x0002);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PDIAG_PLL1_CTRL_M0, 0x0002);

	अगर (ssc) अणु
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_VCOCAL_PLLCNT_START, 0x0315);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_LOCK_PLLCNT_THR, 0x0005);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_VCOCAL_PLLCNT_START, 0x0315);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_LOCK_PLLCNT_THR, 0x0005);
	पूर्ण अन्यथा अणु
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_VCOCAL_PLLCNT_START, 0x0317);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_VCOCAL_PLLCNT_START, 0x0317);
		/* Set reset रेजिस्टर values to disable SSC */
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL1_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL2_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL3_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_SS_CTRL4_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL0_LOCK_PLLCNT_THR, 0x0003);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL1_M0, 0x0002);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL2_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL3_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_SS_CTRL4_M0, 0x0000);
		cdns_torrent_phy_ग_लिखो(regmap,
				       CMN_PLL1_LOCK_PLLCNT_THR, 0x0003);
	पूर्ण

	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_LOCK_REFCNT_START, 0x00C7);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL0_LOCK_PLLCNT_START, 0x00C7);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_LOCK_REFCNT_START, 0x00C7);
	cdns_torrent_phy_ग_लिखो(regmap, CMN_PLL1_LOCK_PLLCNT_START, 0x00C7);
पूर्ण

अटल व्योम cdns_torrent_dp_pma_cmn_rate(काष्ठा cdns_torrent_phy *cdns_phy,
					 u32 rate, u32 num_lanes)
अणु
	अचिन्हित पूर्णांक clk_sel_val = 0;
	अचिन्हित पूर्णांक hsclk_भाग_val = 0;
	अचिन्हित पूर्णांक i;

	/* 16'h0000 क्रम single DP link configuration */
	regmap_field_ग_लिखो(cdns_phy->phy_pll_cfg, 0x0);

	चयन (rate) अणु
	हाल 1620:
		clk_sel_val = 0x0f01;
		hsclk_भाग_val = 2;
		अवरोध;
	हाल 2160:
	हाल 2430:
	हाल 2700:
		clk_sel_val = 0x0701;
		hsclk_भाग_val = 1;
		अवरोध;
	हाल 3240:
		clk_sel_val = 0x0b00;
		hsclk_भाग_val = 2;
		अवरोध;
	हाल 4320:
	हाल 5400:
		clk_sel_val = 0x0301;
		hsclk_भाग_val = 0;
		अवरोध;
	हाल 8100:
		clk_sel_val = 0x0200;
		hsclk_भाग_val = 0;
		अवरोध;
	पूर्ण

	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_common_cdb,
			       CMN_PDIAG_PLL0_CLK_SEL_M0, clk_sel_val);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_common_cdb,
			       CMN_PDIAG_PLL1_CLK_SEL_M0, clk_sel_val);

	/* PMA lane configuration to deal with multi-link operation */
	क्रम (i = 0; i < num_lanes; i++)
		cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[i],
				       XCVR_DIAG_HSCLK_DIV, hsclk_भाग_val);
पूर्ण

अटल व्योम cdns_torrent_dp_pma_lane_cfg(काष्ठा cdns_torrent_phy *cdns_phy,
					 अचिन्हित पूर्णांक lane)
अणु
	/* Per lane, refघड़ी-dependent receiver detection setting */
	अगर (cdns_phy->ref_clk_rate == REF_CLK_19_2MHz)
		cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
				       TX_RCVDET_ST_TMR, 0x0780);
	अन्यथा अगर (cdns_phy->ref_clk_rate == REF_CLK_25MHz)
		cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
				       TX_RCVDET_ST_TMR, 0x09C4);

	/* Writing Tx/Rx Power State Controllers रेजिस्टरs */
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
			       TX_PSC_A0, 0x00FB);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
			       TX_PSC_A2, 0x04AA);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
			       TX_PSC_A3, 0x04AA);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_rx_lane_cdb[lane],
			       RX_PSC_A0, 0x0000);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_rx_lane_cdb[lane],
			       RX_PSC_A2, 0x0000);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_rx_lane_cdb[lane],
			       RX_PSC_A3, 0x0000);

	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_rx_lane_cdb[lane],
			       RX_PSC_CAL, 0x0000);

	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_rx_lane_cdb[lane],
			       RX_REE_GCSM1_CTRL, 0x0000);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_rx_lane_cdb[lane],
			       RX_REE_GCSM2_CTRL, 0x0000);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_rx_lane_cdb[lane],
			       RX_REE_PERGCSM_CTRL, 0x0000);

	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
			       XCVR_DIAG_BIDI_CTRL, 0x000F);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
			       XCVR_DIAG_PLLDRC_CTRL, 0x0001);
	cdns_torrent_phy_ग_लिखो(cdns_phy->regmap_tx_lane_cdb[lane],
			       XCVR_DIAG_HSCLK_SEL, 0x0000);
पूर्ण

अटल पूर्णांक cdns_torrent_dp_set_घातer_state(काष्ठा cdns_torrent_phy *cdns_phy,
					   u32 num_lanes,
					   क्रमागत phy_घातerstate घातerstate)
अणु
	/* Register value क्रम घातer state क्रम a single byte. */
	u32 value_part;
	u32 value;
	u32 mask;
	u32 पढ़ो_val;
	u32 ret;
	काष्ठा regmap *regmap = cdns_phy->regmap_dptx_phy_reg;

	चयन (घातerstate) अणु
	हाल (POWERSTATE_A0):
		value_part = 0x01U;
		अवरोध;
	हाल (POWERSTATE_A2):
		value_part = 0x04U;
		अवरोध;
	शेष:
		/* Powerstate A3 */
		value_part = 0x08U;
		अवरोध;
	पूर्ण

	/* Select values of रेजिस्टरs and mask, depending on enabled
	 * lane count.
	 */
	चयन (num_lanes) अणु
	/* lane 0 */
	हाल (1):
		value = value_part;
		mask = 0x0000003FU;
		अवरोध;
	/* lanes 0-1 */
	हाल (2):
		value = (value_part
			 | (value_part << 8));
		mask = 0x00003F3FU;
		अवरोध;
	/* lanes 0-3, all */
	शेष:
		value = (value_part
			 | (value_part << 8)
			 | (value_part << 16)
			 | (value_part << 24));
		mask = 0x3F3F3F3FU;
		अवरोध;
	पूर्ण

	/* Set घातer state A<n>. */
	cdns_torrent_dp_ग_लिखो(regmap, PHY_PMA_XCVR_POWER_STATE_REQ, value);
	/* Wait, until PHY acknowledges घातer state completion. */
	ret = regmap_पढ़ो_poll_समयout(regmap, PHY_PMA_XCVR_POWER_STATE_ACK,
				       पढ़ो_val, (पढ़ो_val & mask) == value, 0,
				       POLL_TIMEOUT_US);
	cdns_torrent_dp_ग_लिखो(regmap, PHY_PMA_XCVR_POWER_STATE_REQ, 0x00000000);
	ndelay(100);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_torrent_dp_run(काष्ठा cdns_torrent_phy *cdns_phy, u32 num_lanes)
अणु
	अचिन्हित पूर्णांक पढ़ो_val;
	पूर्णांक ret;
	काष्ठा regmap *regmap = cdns_phy->regmap_dptx_phy_reg;

	/*
	 * रुकोing क्रम ACK of pma_xcvr_pllclk_en_ln_*, only क्रम the
	 * master lane
	 */
	ret = regmap_पढ़ो_poll_समयout(regmap, PHY_PMA_XCVR_PLLCLK_EN_ACK,
				       पढ़ो_val, पढ़ो_val & 1,
				       0, POLL_TIMEOUT_US);
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(cdns_phy->dev,
			"timeout waiting for link PLL clock enable ack\n");
		वापस ret;
	पूर्ण

	ndelay(100);

	ret = cdns_torrent_dp_set_घातer_state(cdns_phy, num_lanes,
					      POWERSTATE_A2);
	अगर (ret)
		वापस ret;

	ret = cdns_torrent_dp_set_घातer_state(cdns_phy, num_lanes,
					      POWERSTATE_A0);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_torrent_derived_refclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा cdns_torrent_derived_refclk *derived_refclk = to_cdns_torrent_derived_refclk(hw);

	regmap_field_ग_लिखो(derived_refclk->cmn_fields[CMN_CDIAG_REFCLK_DRV0_CTRL_6], 0);
	regmap_field_ग_लिखो(derived_refclk->cmn_fields[CMN_CDIAG_REFCLK_DRV0_CTRL_4], 1);
	regmap_field_ग_लिखो(derived_refclk->cmn_fields[CMN_CDIAG_REFCLK_DRV0_CTRL_5], 1);
	regmap_field_ग_लिखो(derived_refclk->cmn_fields[CMN_CDIAG_REFCLK_DRV0_CTRL_1], 0);
	regmap_field_ग_लिखो(derived_refclk->cmn_fields[CMN_CDIAG_REFCLK_OVRD_4], 1);
	regmap_field_ग_लिखो(derived_refclk->phy_pipe_cmn_ctrl1_0, 1);

	वापस 0;
पूर्ण

अटल व्योम cdns_torrent_derived_refclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा cdns_torrent_derived_refclk *derived_refclk = to_cdns_torrent_derived_refclk(hw);

	regmap_field_ग_लिखो(derived_refclk->phy_pipe_cmn_ctrl1_0, 0);
पूर्ण

अटल पूर्णांक cdns_torrent_derived_refclk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा cdns_torrent_derived_refclk *derived_refclk = to_cdns_torrent_derived_refclk(hw);
	पूर्णांक val;

	regmap_field_पढ़ो(derived_refclk->phy_pipe_cmn_ctrl1_0, &val);

	वापस !!val;
पूर्ण

अटल स्थिर काष्ठा clk_ops cdns_torrent_derived_refclk_ops = अणु
	.enable = cdns_torrent_derived_refclk_enable,
	.disable = cdns_torrent_derived_refclk_disable,
	.is_enabled = cdns_torrent_derived_refclk_is_enabled,
पूर्ण;

अटल पूर्णांक cdns_torrent_derived_refclk_रेजिस्टर(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	काष्ठा cdns_torrent_derived_refclk *derived_refclk;
	काष्ठा device *dev = cdns_phy->dev;
	काष्ठा regmap_field *field;
	काष्ठा clk_init_data *init;
	स्थिर अक्षर *parent_name;
	काष्ठा regmap *regmap;
	अक्षर clk_name[100];
	काष्ठा clk *clk;
	पूर्णांक i;

	derived_refclk = devm_kzalloc(dev, माप(*derived_refclk), GFP_KERNEL);
	अगर (!derived_refclk)
		वापस -ENOMEM;

	snम_लिखो(clk_name, माप(clk_name), "%s_%s", dev_name(dev),
		 clk_names[CDNS_TORRENT_REFCLK_DRIVER]);

	clk = devm_clk_get_optional(dev, "phy_en_refclk");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "No parent clock for derived_refclk\n");
		वापस PTR_ERR(clk);
	पूर्ण

	init = &derived_refclk->clk_data;

	अगर (clk) अणु
		parent_name = __clk_get_name(clk);
		init->parent_names = &parent_name;
		init->num_parents = 1;
	पूर्ण
	init->ops = &cdns_torrent_derived_refclk_ops;
	init->flags = 0;
	init->name = clk_name;

	regmap = cdns_phy->regmap_phy_pcs_common_cdb;
	field = devm_regmap_field_alloc(dev, regmap, phy_pipe_cmn_ctrl1_0);
	अगर (IS_ERR(field)) अणु
		dev_err(dev, "phy_pipe_cmn_ctrl1_0 reg field init failed\n");
		वापस PTR_ERR(field);
	पूर्ण
	derived_refclk->phy_pipe_cmn_ctrl1_0 = field;

	regmap = cdns_phy->regmap_common_cdb;
	क्रम (i = 0; i < REFCLK_OUT_NUM_CMN_CONFIG; i++) अणु
		field = devm_regmap_field_alloc(dev, regmap, refclk_out_cmn_cfg[i]);
		अगर (IS_ERR(field)) अणु
			dev_err(dev, "CMN reg field init failed\n");
			वापस PTR_ERR(field);
		पूर्ण
		derived_refclk->cmn_fields[i] = field;
	पूर्ण

	derived_refclk->hw.init = init;

	clk = devm_clk_रेजिस्टर(dev, &derived_refclk->hw);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	cdns_phy->clks[CDNS_TORRENT_REFCLK_DRIVER] = clk;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_torrent_phy_on(काष्ठा phy *phy)
अणु
	काष्ठा cdns_torrent_inst *inst = phy_get_drvdata(phy);
	काष्ठा cdns_torrent_phy *cdns_phy = dev_get_drvdata(phy->dev.parent);
	u32 पढ़ो_val;
	पूर्णांक ret;

	अगर (cdns_phy->nsubnodes == 1) अणु
		/* Take the PHY lane group out of reset */
		reset_control_deनिश्चित(inst->lnk_rst);

		/* Take the PHY out of reset */
		ret = reset_control_deनिश्चित(cdns_phy->phy_rst);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Wait क्रम cmn_पढ़ोy निश्चितion
	 * PHY_PMA_CMN_CTRL1[0] == 1
	 */
	ret = regmap_field_पढ़ो_poll_समयout(cdns_phy->phy_pma_cmn_ctrl_1,
					     पढ़ो_val, पढ़ो_val, 1000,
					     PLL_LOCK_TIMEOUT);
	अगर (ret) अणु
		dev_err(cdns_phy->dev, "Timeout waiting for CMN ready\n");
		वापस ret;
	पूर्ण

	mdelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_torrent_phy_off(काष्ठा phy *phy)
अणु
	काष्ठा cdns_torrent_inst *inst = phy_get_drvdata(phy);
	काष्ठा cdns_torrent_phy *cdns_phy = dev_get_drvdata(phy->dev.parent);
	पूर्णांक ret;

	अगर (cdns_phy->nsubnodes != 1)
		वापस 0;

	ret = reset_control_निश्चित(cdns_phy->phy_rst);
	अगर (ret)
		वापस ret;

	वापस reset_control_निश्चित(inst->lnk_rst);
पूर्ण

अटल काष्ठा regmap *cdns_regmap_init(काष्ठा device *dev, व्योम __iomem *base,
				       u32 block_offset,
				       u8 reg_offset_shअगरt,
				       स्थिर काष्ठा regmap_config *config)
अणु
	काष्ठा cdns_regmap_cdb_context *ctx;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ctx->dev = dev;
	ctx->base = base + block_offset;
	ctx->reg_offset_shअगरt = reg_offset_shअगरt;

	वापस devm_regmap_init(dev, शून्य, ctx, config);
पूर्ण

अटल पूर्णांक cdns_torrent_dp_regfield_init(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	काष्ठा device *dev = cdns_phy->dev;
	काष्ठा regmap_field *field;
	काष्ठा regmap *regmap;

	regmap = cdns_phy->regmap_dptx_phy_reg;
	field = devm_regmap_field_alloc(dev, regmap, phy_reset_ctrl);
	अगर (IS_ERR(field)) अणु
		dev_err(dev, "PHY_RESET reg field init failed\n");
		वापस PTR_ERR(field);
	पूर्ण
	cdns_phy->phy_reset_ctrl = field;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_torrent_regfield_init(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	काष्ठा device *dev = cdns_phy->dev;
	काष्ठा regmap_field *field;
	काष्ठा regmap *regmap;

	regmap = cdns_phy->regmap_phy_pcs_common_cdb;
	field = devm_regmap_field_alloc(dev, regmap, phy_pll_cfg);
	अगर (IS_ERR(field)) अणु
		dev_err(dev, "PHY_PLL_CFG reg field init failed\n");
		वापस PTR_ERR(field);
	पूर्ण
	cdns_phy->phy_pll_cfg = field;

	regmap = cdns_phy->regmap_phy_pma_common_cdb;
	field = devm_regmap_field_alloc(dev, regmap, phy_pma_cmn_ctrl_1);
	अगर (IS_ERR(field)) अणु
		dev_err(dev, "PHY_PMA_CMN_CTRL1 reg field init failed\n");
		वापस PTR_ERR(field);
	पूर्ण
	cdns_phy->phy_pma_cmn_ctrl_1 = field;

	regmap = cdns_phy->regmap_phy_pma_common_cdb;
	field = devm_regmap_field_alloc(dev, regmap, phy_pma_cmn_ctrl_2);
	अगर (IS_ERR(field)) अणु
		dev_err(dev, "PHY_PMA_CMN_CTRL2 reg field init failed\n");
		वापस PTR_ERR(field);
	पूर्ण
	cdns_phy->phy_pma_cmn_ctrl_2 = field;

	regmap = cdns_phy->regmap_phy_pma_common_cdb;
	field = devm_regmap_field_alloc(dev, regmap, phy_pma_pll_raw_ctrl);
	अगर (IS_ERR(field)) अणु
		dev_err(dev, "PHY_PMA_PLL_RAW_CTRL reg field init failed\n");
		वापस PTR_ERR(field);
	पूर्ण
	cdns_phy->phy_pma_pll_raw_ctrl = field;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_torrent_dp_regmap_init(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	व्योम __iomem *base = cdns_phy->base;
	काष्ठा device *dev = cdns_phy->dev;
	काष्ठा regmap *regmap;
	u8 reg_offset_shअगरt;
	u32 block_offset;

	reg_offset_shअगरt = cdns_phy->init_data->reg_offset_shअगरt;

	block_offset = TORRENT_DPTX_PHY_OFFSET;
	regmap = cdns_regmap_init(dev, base, block_offset,
				  reg_offset_shअगरt,
				  &cdns_torrent_dptx_phy_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to init DPTX PHY regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	cdns_phy->regmap_dptx_phy_reg = regmap;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_torrent_regmap_init(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	व्योम __iomem *sd_base = cdns_phy->sd_base;
	u8 block_offset_shअगरt, reg_offset_shअगरt;
	काष्ठा device *dev = cdns_phy->dev;
	काष्ठा regmap *regmap;
	u32 block_offset;
	पूर्णांक i;

	block_offset_shअगरt = cdns_phy->init_data->block_offset_shअगरt;
	reg_offset_shअगरt = cdns_phy->init_data->reg_offset_shअगरt;

	क्रम (i = 0; i < MAX_NUM_LANES; i++) अणु
		block_offset = TORRENT_TX_LANE_CDB_OFFSET(i, block_offset_shअगरt,
							  reg_offset_shअगरt);
		regmap = cdns_regmap_init(dev, sd_base, block_offset,
					  reg_offset_shअगरt,
					  &cdns_torrent_tx_lane_cdb_config[i]);
		अगर (IS_ERR(regmap)) अणु
			dev_err(dev, "Failed to init tx lane CDB regmap\n");
			वापस PTR_ERR(regmap);
		पूर्ण
		cdns_phy->regmap_tx_lane_cdb[i] = regmap;

		block_offset = TORRENT_RX_LANE_CDB_OFFSET(i, block_offset_shअगरt,
							  reg_offset_shअगरt);
		regmap = cdns_regmap_init(dev, sd_base, block_offset,
					  reg_offset_shअगरt,
					  &cdns_torrent_rx_lane_cdb_config[i]);
		अगर (IS_ERR(regmap)) अणु
			dev_err(dev, "Failed to init rx lane CDB regmap\n");
			वापस PTR_ERR(regmap);
		पूर्ण
		cdns_phy->regmap_rx_lane_cdb[i] = regmap;
	पूर्ण

	block_offset = TORRENT_COMMON_CDB_OFFSET;
	regmap = cdns_regmap_init(dev, sd_base, block_offset,
				  reg_offset_shअगरt,
				  &cdns_torrent_common_cdb_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to init common CDB regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	cdns_phy->regmap_common_cdb = regmap;

	block_offset = TORRENT_PHY_PCS_COMMON_OFFSET(block_offset_shअगरt);
	regmap = cdns_regmap_init(dev, sd_base, block_offset,
				  reg_offset_shअगरt,
				  &cdns_torrent_phy_pcs_cmn_cdb_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to init PHY PCS common CDB regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	cdns_phy->regmap_phy_pcs_common_cdb = regmap;

	block_offset = TORRENT_PHY_PMA_COMMON_OFFSET(block_offset_shअगरt);
	regmap = cdns_regmap_init(dev, sd_base, block_offset,
				  reg_offset_shअगरt,
				  &cdns_torrent_phy_pma_cmn_cdb_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to init PHY PMA common CDB regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	cdns_phy->regmap_phy_pma_common_cdb = regmap;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_torrent_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा cdns_torrent_phy *cdns_phy = dev_get_drvdata(phy->dev.parent);
	स्थिर काष्ठा cdns_torrent_data *init_data = cdns_phy->init_data;
	काष्ठा cdns_torrent_vals *cmn_vals, *tx_ln_vals, *rx_ln_vals;
	काष्ठा cdns_torrent_vals *link_cmn_vals, *xcvr_diag_vals;
	काष्ठा cdns_torrent_inst *inst = phy_get_drvdata(phy);
	क्रमागत cdns_torrent_phy_type phy_type = inst->phy_type;
	क्रमागत cdns_torrent_ssc_mode ssc = inst->ssc_mode;
	काष्ठा cdns_torrent_vals *pcs_cmn_vals;
	काष्ठा cdns_reg_pairs *reg_pairs;
	काष्ठा regmap *regmap;
	u32 num_regs;
	पूर्णांक i, j;

	अगर (cdns_phy->nsubnodes > 1)
		वापस 0;

	अगर (phy_type == TYPE_DP)
		वापस cdns_torrent_dp_init(phy);

	/**
	 * Spपढ़ो spectrum generation is not required or supported
	 * क्रम SGMII/QSGMII
	 */
	अगर (phy_type == TYPE_SGMII || phy_type == TYPE_QSGMII)
		ssc = NO_SSC;

	/* PHY configuration specअगरic रेजिस्टरs क्रम single link */
	link_cmn_vals = init_data->link_cmn_vals[phy_type][TYPE_NONE][ssc];
	अगर (link_cmn_vals) अणु
		reg_pairs = link_cmn_vals->reg_pairs;
		num_regs = link_cmn_vals->num_regs;
		regmap = cdns_phy->regmap_common_cdb;

		/**
		 * First array value in link_cmn_vals must be of
		 * PHY_PLL_CFG रेजिस्टर
		 */
		regmap_field_ग_लिखो(cdns_phy->phy_pll_cfg, reg_pairs[0].val);

		क्रम (i = 1; i < num_regs; i++)
			regmap_ग_लिखो(regmap, reg_pairs[i].off,
				     reg_pairs[i].val);
	पूर्ण

	xcvr_diag_vals = init_data->xcvr_diag_vals[phy_type][TYPE_NONE][ssc];
	अगर (xcvr_diag_vals) अणु
		reg_pairs = xcvr_diag_vals->reg_pairs;
		num_regs = xcvr_diag_vals->num_regs;
		क्रम (i = 0; i < inst->num_lanes; i++) अणु
			regmap = cdns_phy->regmap_tx_lane_cdb[i + inst->mlane];
			क्रम (j = 0; j < num_regs; j++)
				regmap_ग_लिखो(regmap, reg_pairs[j].off,
					     reg_pairs[j].val);
		पूर्ण
	पूर्ण

	/* PHY PCS common रेजिस्टरs configurations */
	pcs_cmn_vals = init_data->pcs_cmn_vals[phy_type][TYPE_NONE][ssc];
	अगर (pcs_cmn_vals) अणु
		reg_pairs = pcs_cmn_vals->reg_pairs;
		num_regs = pcs_cmn_vals->num_regs;
		regmap = cdns_phy->regmap_phy_pcs_common_cdb;
		क्रम (i = 0; i < num_regs; i++)
			regmap_ग_लिखो(regmap, reg_pairs[i].off,
				     reg_pairs[i].val);
	पूर्ण

	/* PMA common रेजिस्टरs configurations */
	cmn_vals = init_data->cmn_vals[phy_type][TYPE_NONE][ssc];
	अगर (cmn_vals) अणु
		reg_pairs = cmn_vals->reg_pairs;
		num_regs = cmn_vals->num_regs;
		regmap = cdns_phy->regmap_common_cdb;
		क्रम (i = 0; i < num_regs; i++)
			regmap_ग_लिखो(regmap, reg_pairs[i].off,
				     reg_pairs[i].val);
	पूर्ण

	/* PMA TX lane रेजिस्टरs configurations */
	tx_ln_vals = init_data->tx_ln_vals[phy_type][TYPE_NONE][ssc];
	अगर (tx_ln_vals) अणु
		reg_pairs = tx_ln_vals->reg_pairs;
		num_regs = tx_ln_vals->num_regs;
		क्रम (i = 0; i < inst->num_lanes; i++) अणु
			regmap = cdns_phy->regmap_tx_lane_cdb[i + inst->mlane];
			क्रम (j = 0; j < num_regs; j++)
				regmap_ग_लिखो(regmap, reg_pairs[j].off,
					     reg_pairs[j].val);
		पूर्ण
	पूर्ण

	/* PMA RX lane रेजिस्टरs configurations */
	rx_ln_vals = init_data->rx_ln_vals[phy_type][TYPE_NONE][ssc];
	अगर (rx_ln_vals) अणु
		reg_pairs = rx_ln_vals->reg_pairs;
		num_regs = rx_ln_vals->num_regs;
		क्रम (i = 0; i < inst->num_lanes; i++) अणु
			regmap = cdns_phy->regmap_rx_lane_cdb[i + inst->mlane];
			क्रम (j = 0; j < num_regs; j++)
				regmap_ग_लिखो(regmap, reg_pairs[j].off,
					     reg_pairs[j].val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक cdns_torrent_phy_configure_multilink(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	स्थिर काष्ठा cdns_torrent_data *init_data = cdns_phy->init_data;
	काष्ठा cdns_torrent_vals *cmn_vals, *tx_ln_vals, *rx_ln_vals;
	काष्ठा cdns_torrent_vals *link_cmn_vals, *xcvr_diag_vals;
	क्रमागत cdns_torrent_phy_type phy_t1, phy_t2, पंचांगp_phy_type;
	काष्ठा cdns_torrent_vals *pcs_cmn_vals;
	पूर्णांक i, j, node, mlane, num_lanes, ret;
	काष्ठा cdns_reg_pairs *reg_pairs;
	क्रमागत cdns_torrent_ssc_mode ssc;
	काष्ठा regmap *regmap;
	u32 num_regs;

	/* Maximum 2 links (subnodes) are supported */
	अगर (cdns_phy->nsubnodes != 2)
		वापस -EINVAL;

	phy_t1 = cdns_phy->phys[0].phy_type;
	phy_t2 = cdns_phy->phys[1].phy_type;

	/**
	 * First configure the PHY क्रम first link with phy_t1. Get the array
	 * values as [phy_t1][phy_t2][ssc].
	 */
	क्रम (node = 0; node < cdns_phy->nsubnodes; node++) अणु
		अगर (node == 1) अणु
			/**
			 * If first link with phy_t1 is configured, then
			 * configure the PHY क्रम second link with phy_t2.
			 * Get the array values as [phy_t2][phy_t1][ssc].
			 */
			पंचांगp_phy_type = phy_t1;
			phy_t1 = phy_t2;
			phy_t2 = पंचांगp_phy_type;
		पूर्ण

		mlane = cdns_phy->phys[node].mlane;
		ssc = cdns_phy->phys[node].ssc_mode;
		num_lanes = cdns_phy->phys[node].num_lanes;

		/**
		 * PHY configuration specअगरic रेजिस्टरs:
		 * link_cmn_vals depend on combination of PHY types being
		 * configured and are common क्रम both PHY types, so array
		 * values should be same क्रम [phy_t1][phy_t2][ssc] and
		 * [phy_t2][phy_t1][ssc].
		 * xcvr_diag_vals also depend on combination of PHY types
		 * being configured, but these can be dअगरferent क्रम particular
		 * PHY type and are per lane.
		 */
		link_cmn_vals = init_data->link_cmn_vals[phy_t1][phy_t2][ssc];
		अगर (link_cmn_vals) अणु
			reg_pairs = link_cmn_vals->reg_pairs;
			num_regs = link_cmn_vals->num_regs;
			regmap = cdns_phy->regmap_common_cdb;

			/**
			 * First array value in link_cmn_vals must be of
			 * PHY_PLL_CFG रेजिस्टर
			 */
			regmap_field_ग_लिखो(cdns_phy->phy_pll_cfg,
					   reg_pairs[0].val);

			क्रम (i = 1; i < num_regs; i++)
				regmap_ग_लिखो(regmap, reg_pairs[i].off,
					     reg_pairs[i].val);
		पूर्ण

		xcvr_diag_vals = init_data->xcvr_diag_vals[phy_t1][phy_t2][ssc];
		अगर (xcvr_diag_vals) अणु
			reg_pairs = xcvr_diag_vals->reg_pairs;
			num_regs = xcvr_diag_vals->num_regs;
			क्रम (i = 0; i < num_lanes; i++) अणु
				regmap = cdns_phy->regmap_tx_lane_cdb[i + mlane];
				क्रम (j = 0; j < num_regs; j++)
					regmap_ग_लिखो(regmap, reg_pairs[j].off,
						     reg_pairs[j].val);
			पूर्ण
		पूर्ण

		/* PHY PCS common रेजिस्टरs configurations */
		pcs_cmn_vals = init_data->pcs_cmn_vals[phy_t1][phy_t2][ssc];
		अगर (pcs_cmn_vals) अणु
			reg_pairs = pcs_cmn_vals->reg_pairs;
			num_regs = pcs_cmn_vals->num_regs;
			regmap = cdns_phy->regmap_phy_pcs_common_cdb;
			क्रम (i = 0; i < num_regs; i++)
				regmap_ग_लिखो(regmap, reg_pairs[i].off,
					     reg_pairs[i].val);
		पूर्ण

		/* PMA common रेजिस्टरs configurations */
		cmn_vals = init_data->cmn_vals[phy_t1][phy_t2][ssc];
		अगर (cmn_vals) अणु
			reg_pairs = cmn_vals->reg_pairs;
			num_regs = cmn_vals->num_regs;
			regmap = cdns_phy->regmap_common_cdb;
			क्रम (i = 0; i < num_regs; i++)
				regmap_ग_लिखो(regmap, reg_pairs[i].off,
					     reg_pairs[i].val);
		पूर्ण

		/* PMA TX lane रेजिस्टरs configurations */
		tx_ln_vals = init_data->tx_ln_vals[phy_t1][phy_t2][ssc];
		अगर (tx_ln_vals) अणु
			reg_pairs = tx_ln_vals->reg_pairs;
			num_regs = tx_ln_vals->num_regs;
			क्रम (i = 0; i < num_lanes; i++) अणु
				regmap = cdns_phy->regmap_tx_lane_cdb[i + mlane];
				क्रम (j = 0; j < num_regs; j++)
					regmap_ग_लिखो(regmap, reg_pairs[j].off,
						     reg_pairs[j].val);
			पूर्ण
		पूर्ण

		/* PMA RX lane रेजिस्टरs configurations */
		rx_ln_vals = init_data->rx_ln_vals[phy_t1][phy_t2][ssc];
		अगर (rx_ln_vals) अणु
			reg_pairs = rx_ln_vals->reg_pairs;
			num_regs = rx_ln_vals->num_regs;
			क्रम (i = 0; i < num_lanes; i++) अणु
				regmap = cdns_phy->regmap_rx_lane_cdb[i + mlane];
				क्रम (j = 0; j < num_regs; j++)
					regmap_ग_लिखो(regmap, reg_pairs[j].off,
						     reg_pairs[j].val);
			पूर्ण
		पूर्ण

		reset_control_deनिश्चित(cdns_phy->phys[node].lnk_rst);
	पूर्ण

	/* Take the PHY out of reset */
	ret = reset_control_deनिश्चित(cdns_phy->phy_rst);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम cdns_torrent_clk_cleanup(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	काष्ठा device *dev = cdns_phy->dev;

	of_clk_del_provider(dev->of_node);
पूर्ण

अटल पूर्णांक cdns_torrent_clk_रेजिस्टर(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	काष्ठा device *dev = cdns_phy->dev;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक ret;

	ret = cdns_torrent_derived_refclk_रेजिस्टर(cdns_phy);
	अगर (ret) अणु
		dev_err(dev, "failed to register derived refclk\n");
		वापस ret;
	पूर्ण

	cdns_phy->clk_data.clks = cdns_phy->clks;
	cdns_phy->clk_data.clk_num = CDNS_TORRENT_REFCLK_DRIVER + 1;

	ret = of_clk_add_provider(node, of_clk_src_onecell_get, &cdns_phy->clk_data);
	अगर (ret) अणु
		dev_err(dev, "Failed to add clock provider: %s\n", node->name);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_torrent_reset(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	काष्ठा device *dev = cdns_phy->dev;

	cdns_phy->phy_rst = devm_reset_control_get_exclusive_by_index(dev, 0);
	अगर (IS_ERR(cdns_phy->phy_rst)) अणु
		dev_err(dev, "%s: failed to get reset\n",
			dev->of_node->full_name);
		वापस PTR_ERR(cdns_phy->phy_rst);
	पूर्ण

	cdns_phy->apb_rst = devm_reset_control_get_optional_exclusive(dev, "torrent_apb");
	अगर (IS_ERR(cdns_phy->apb_rst)) अणु
		dev_err(dev, "%s: failed to get apb reset\n",
			dev->of_node->full_name);
		वापस PTR_ERR(cdns_phy->apb_rst);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_torrent_clk(काष्ठा cdns_torrent_phy *cdns_phy)
अणु
	काष्ठा device *dev = cdns_phy->dev;
	पूर्णांक ret;

	cdns_phy->clk = devm_clk_get(dev, "refclk");
	अगर (IS_ERR(cdns_phy->clk)) अणु
		dev_err(dev, "phy ref clock not found\n");
		वापस PTR_ERR(cdns_phy->clk);
	पूर्ण

	ret = clk_prepare_enable(cdns_phy->clk);
	अगर (ret) अणु
		dev_err(cdns_phy->dev, "Failed to prepare ref clock\n");
		वापस ret;
	पूर्ण

	cdns_phy->ref_clk_rate = clk_get_rate(cdns_phy->clk);
	अगर (!(cdns_phy->ref_clk_rate)) अणु
		dev_err(cdns_phy->dev, "Failed to get ref clock rate\n");
		clk_disable_unprepare(cdns_phy->clk);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_torrent_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_torrent_phy *cdns_phy;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	स्थिर काष्ठा cdns_torrent_data *data;
	काष्ठा device_node *child;
	पूर्णांक ret, subnodes, node = 0, i;
	u32 total_num_lanes = 0;
	पूर्णांक alपढ़ोy_configured;
	u8 init_dp_regmap = 0;
	u32 phy_type;

	/* Get init data क्रम this PHY */
	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -EINVAL;

	cdns_phy = devm_kzalloc(dev, माप(*cdns_phy), GFP_KERNEL);
	अगर (!cdns_phy)
		वापस -ENOMEM;

	dev_set_drvdata(dev, cdns_phy);
	cdns_phy->dev = dev;
	cdns_phy->init_data = data;

	cdns_phy->sd_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(cdns_phy->sd_base))
		वापस PTR_ERR(cdns_phy->sd_base);

	subnodes = of_get_available_child_count(dev->of_node);
	अगर (subnodes == 0) अणु
		dev_err(dev, "No available link subnodes found\n");
		वापस -EINVAL;
	पूर्ण

	ret = cdns_torrent_regmap_init(cdns_phy);
	अगर (ret)
		वापस ret;

	ret = cdns_torrent_regfield_init(cdns_phy);
	अगर (ret)
		वापस ret;

	ret = cdns_torrent_clk_रेजिस्टर(cdns_phy);
	अगर (ret)
		वापस ret;

	regmap_field_पढ़ो(cdns_phy->phy_pma_cmn_ctrl_1, &alपढ़ोy_configured);

	अगर (!alपढ़ोy_configured) अणु
		ret = cdns_torrent_reset(cdns_phy);
		अगर (ret)
			जाओ clk_cleanup;

		ret = cdns_torrent_clk(cdns_phy);
		अगर (ret)
			जाओ clk_cleanup;

		/* Enable APB */
		reset_control_deनिश्चित(cdns_phy->apb_rst);
	पूर्ण

	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		काष्ठा phy *gphy;

		/* PHY subnode name must be 'phy'. */
		अगर (!(of_node_name_eq(child, "phy")))
			जारी;

		cdns_phy->phys[node].lnk_rst =
				of_reset_control_array_get_exclusive(child);
		अगर (IS_ERR(cdns_phy->phys[node].lnk_rst)) अणु
			dev_err(dev, "%s: failed to get reset\n",
				child->full_name);
			ret = PTR_ERR(cdns_phy->phys[node].lnk_rst);
			जाओ put_lnk_rst;
		पूर्ण

		अगर (of_property_पढ़ो_u32(child, "reg",
					 &cdns_phy->phys[node].mlane)) अणु
			dev_err(dev, "%s: No \"reg\"-property.\n",
				child->full_name);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		अगर (of_property_पढ़ो_u32(child, "cdns,phy-type", &phy_type)) अणु
			dev_err(dev, "%s: No \"cdns,phy-type\"-property.\n",
				child->full_name);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		चयन (phy_type) अणु
		हाल PHY_TYPE_PCIE:
			cdns_phy->phys[node].phy_type = TYPE_PCIE;
			अवरोध;
		हाल PHY_TYPE_DP:
			cdns_phy->phys[node].phy_type = TYPE_DP;
			अवरोध;
		हाल PHY_TYPE_SGMII:
			cdns_phy->phys[node].phy_type = TYPE_SGMII;
			अवरोध;
		हाल PHY_TYPE_QSGMII:
			cdns_phy->phys[node].phy_type = TYPE_QSGMII;
			अवरोध;
		हाल PHY_TYPE_USB3:
			cdns_phy->phys[node].phy_type = TYPE_USB;
			अवरोध;
		शेष:
			dev_err(dev, "Unsupported protocol\n");
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		अगर (of_property_पढ़ो_u32(child, "cdns,num-lanes",
					 &cdns_phy->phys[node].num_lanes)) अणु
			dev_err(dev, "%s: No \"cdns,num-lanes\"-property.\n",
				child->full_name);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		total_num_lanes += cdns_phy->phys[node].num_lanes;

		/* Get SSC mode */
		cdns_phy->phys[node].ssc_mode = NO_SSC;
		of_property_पढ़ो_u32(child, "cdns,ssc-mode",
				     &cdns_phy->phys[node].ssc_mode);

		अगर (!alपढ़ोy_configured)
			gphy = devm_phy_create(dev, child, &cdns_torrent_phy_ops);
		अन्यथा
			gphy = devm_phy_create(dev, child, &noop_ops);
		अगर (IS_ERR(gphy)) अणु
			ret = PTR_ERR(gphy);
			जाओ put_child;
		पूर्ण

		अगर (cdns_phy->phys[node].phy_type == TYPE_DP) अणु
			चयन (cdns_phy->phys[node].num_lanes) अणु
			हाल 1:
			हाल 2:
			हाल 4:
			/* valid number of lanes */
				अवरोध;
			शेष:
				dev_err(dev, "unsupported number of lanes: %d\n",
					cdns_phy->phys[node].num_lanes);
				ret = -EINVAL;
				जाओ put_child;
			पूर्ण

			cdns_phy->max_bit_rate = DEFAULT_MAX_BIT_RATE;
			of_property_पढ़ो_u32(child, "cdns,max-bit-rate",
					     &cdns_phy->max_bit_rate);

			चयन (cdns_phy->max_bit_rate) अणु
			हाल 1620:
			हाल 2160:
			हाल 2430:
			हाल 2700:
			हाल 3240:
			हाल 4320:
			हाल 5400:
			हाल 8100:
			/* valid bit rate */
				अवरोध;
			शेष:
				dev_err(dev, "unsupported max bit rate: %dMbps\n",
					cdns_phy->max_bit_rate);
				ret = -EINVAL;
				जाओ put_child;
			पूर्ण

			/* DPTX रेजिस्टरs */
			cdns_phy->base = devm_platक्रमm_ioremap_resource(pdev, 1);
			अगर (IS_ERR(cdns_phy->base)) अणु
				ret = PTR_ERR(cdns_phy->base);
				जाओ put_child;
			पूर्ण

			अगर (!init_dp_regmap) अणु
				ret = cdns_torrent_dp_regmap_init(cdns_phy);
				अगर (ret)
					जाओ put_child;

				ret = cdns_torrent_dp_regfield_init(cdns_phy);
				अगर (ret)
					जाओ put_child;

				init_dp_regmap++;
			पूर्ण

			dev_info(dev, "%d lanes, max bit rate %d.%03d Gbps\n",
				 cdns_phy->phys[node].num_lanes,
				 cdns_phy->max_bit_rate / 1000,
				 cdns_phy->max_bit_rate % 1000);

			gphy->attrs.bus_width = cdns_phy->phys[node].num_lanes;
			gphy->attrs.max_link_rate = cdns_phy->max_bit_rate;
			gphy->attrs.mode = PHY_MODE_DP;
		पूर्ण

		cdns_phy->phys[node].phy = gphy;
		phy_set_drvdata(gphy, &cdns_phy->phys[node]);

		node++;
	पूर्ण
	cdns_phy->nsubnodes = node;

	अगर (total_num_lanes > MAX_NUM_LANES) अणु
		dev_err(dev, "Invalid lane configuration\n");
		ret = -EINVAL;
		जाओ put_lnk_rst;
	पूर्ण

	अगर (cdns_phy->nsubnodes > 1 && !alपढ़ोy_configured) अणु
		ret = cdns_torrent_phy_configure_multilink(cdns_phy);
		अगर (ret)
			जाओ put_lnk_rst;
	पूर्ण

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		ret = PTR_ERR(phy_provider);
		जाओ put_lnk_rst;
	पूर्ण

	वापस 0;

put_child:
	node++;
put_lnk_rst:
	क्रम (i = 0; i < node; i++)
		reset_control_put(cdns_phy->phys[i].lnk_rst);
	of_node_put(child);
	reset_control_निश्चित(cdns_phy->apb_rst);
	clk_disable_unprepare(cdns_phy->clk);
clk_cleanup:
	cdns_torrent_clk_cleanup(cdns_phy);
	वापस ret;
पूर्ण

अटल पूर्णांक cdns_torrent_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_torrent_phy *cdns_phy = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	reset_control_निश्चित(cdns_phy->phy_rst);
	reset_control_निश्चित(cdns_phy->apb_rst);
	क्रम (i = 0; i < cdns_phy->nsubnodes; i++) अणु
		reset_control_निश्चित(cdns_phy->phys[i].lnk_rst);
		reset_control_put(cdns_phy->phys[i].lnk_rst);
	पूर्ण

	clk_disable_unprepare(cdns_phy->clk);
	cdns_torrent_clk_cleanup(cdns_phy);

	वापस 0;
पूर्ण

/* USB and SGMII/QSGMII link configuration */
अटल काष्ठा cdns_reg_pairs usb_sgmii_link_cmn_regs[] = अणु
	अणु0x0002, PHY_PLL_CFGपूर्ण,
	अणु0x8600, CMN_PDIAG_PLL0_CLK_SEL_M0पूर्ण,
	अणु0x0601, CMN_PDIAG_PLL1_CLK_SEL_M0पूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs usb_sgmii_xcvr_diag_ln_regs[] = अणु
	अणु0x0000, XCVR_DIAG_HSCLK_SELपूर्ण,
	अणु0x0001, XCVR_DIAG_HSCLK_DIVपूर्ण,
	अणु0x0041, XCVR_DIAG_PLLDRC_CTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs sgmii_usb_xcvr_diag_ln_regs[] = अणु
	अणु0x0011, XCVR_DIAG_HSCLK_SELपूर्ण,
	अणु0x0003, XCVR_DIAG_HSCLK_DIVपूर्ण,
	अणु0x009B, XCVR_DIAG_PLLDRC_CTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals usb_sgmii_link_cmn_vals = अणु
	.reg_pairs = usb_sgmii_link_cmn_regs,
	.num_regs = ARRAY_SIZE(usb_sgmii_link_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals usb_sgmii_xcvr_diag_ln_vals = अणु
	.reg_pairs = usb_sgmii_xcvr_diag_ln_regs,
	.num_regs = ARRAY_SIZE(usb_sgmii_xcvr_diag_ln_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals sgmii_usb_xcvr_diag_ln_vals = अणु
	.reg_pairs = sgmii_usb_xcvr_diag_ln_regs,
	.num_regs = ARRAY_SIZE(sgmii_usb_xcvr_diag_ln_regs),
पूर्ण;

/* PCIe and USB Unique SSC link configuration */
अटल काष्ठा cdns_reg_pairs pcie_usb_link_cmn_regs[] = अणु
	अणु0x0003, PHY_PLL_CFGपूर्ण,
	अणु0x0601, CMN_PDIAG_PLL0_CLK_SEL_M0पूर्ण,
	अणु0x0400, CMN_PDIAG_PLL0_CLK_SEL_M1पूर्ण,
	अणु0x8600, CMN_PDIAG_PLL1_CLK_SEL_M0पूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs pcie_usb_xcvr_diag_ln_regs[] = अणु
	अणु0x0000, XCVR_DIAG_HSCLK_SELपूर्ण,
	अणु0x0001, XCVR_DIAG_HSCLK_DIVपूर्ण,
	अणु0x0012, XCVR_DIAG_PLLDRC_CTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs usb_pcie_xcvr_diag_ln_regs[] = अणु
	अणु0x0011, XCVR_DIAG_HSCLK_SELपूर्ण,
	अणु0x0001, XCVR_DIAG_HSCLK_DIVपूर्ण,
	अणु0x00C9, XCVR_DIAG_PLLDRC_CTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals pcie_usb_link_cmn_vals = अणु
	.reg_pairs = pcie_usb_link_cmn_regs,
	.num_regs = ARRAY_SIZE(pcie_usb_link_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals pcie_usb_xcvr_diag_ln_vals = अणु
	.reg_pairs = pcie_usb_xcvr_diag_ln_regs,
	.num_regs = ARRAY_SIZE(pcie_usb_xcvr_diag_ln_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals usb_pcie_xcvr_diag_ln_vals = अणु
	.reg_pairs = usb_pcie_xcvr_diag_ln_regs,
	.num_regs = ARRAY_SIZE(usb_pcie_xcvr_diag_ln_regs),
पूर्ण;

/* USB 100 MHz Ref clk, पूर्णांकernal SSC */
अटल काष्ठा cdns_reg_pairs usb_100_पूर्णांक_ssc_cmn_regs[] = अणु
	अणु0x0004, CMN_PLL0_DSM_DIAG_M0पूर्ण,
	अणु0x0004, CMN_PLL0_DSM_DIAG_M1पूर्ण,
	अणु0x0004, CMN_PLL1_DSM_DIAG_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M1पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M1पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL1_CP_IADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M1पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL1_FILT_PADJ_M0पूर्ण,
	अणु0x0064, CMN_PLL0_INTDIV_M0पूर्ण,
	अणु0x0050, CMN_PLL0_INTDIV_M1पूर्ण,
	अणु0x0064, CMN_PLL1_INTDIV_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M1पूर्ण,
	अणु0x0002, CMN_PLL1_FRACDIVH_M0पूर्ण,
	अणु0x0044, CMN_PLL0_HIGH_THR_M0पूर्ण,
	अणु0x0036, CMN_PLL0_HIGH_THR_M1पूर्ण,
	अणु0x0044, CMN_PLL1_HIGH_THR_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M1पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL1_CTRL_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M1पूर्ण,
	अणु0x0001, CMN_PLL1_SS_CTRL1_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M1पूर्ण,
	अणु0x011B, CMN_PLL1_SS_CTRL2_M0पूर्ण,
	अणु0x006E, CMN_PLL0_SS_CTRL3_M0पूर्ण,
	अणु0x0058, CMN_PLL0_SS_CTRL3_M1पूर्ण,
	अणु0x006E, CMN_PLL1_SS_CTRL3_M0पूर्ण,
	अणु0x000E, CMN_PLL0_SS_CTRL4_M0पूर्ण,
	अणु0x0012, CMN_PLL0_SS_CTRL4_M1पूर्ण,
	अणु0x000E, CMN_PLL1_SS_CTRL4_M0पूर्ण,
	अणु0x0C5E, CMN_PLL0_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C5E, CMN_PLL1_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C56, CMN_PLL0_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x0C56, CMN_PLL1_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x0005, CMN_PLL0_LOCK_PLLCNT_THRपूर्ण,
	अणु0x0005, CMN_PLL1_LOCK_PLLCNT_THRपूर्ण,
	अणु0x8200, CMN_CDIAG_CDB_PWRI_OVRDपूर्ण,
	अणु0x8200, CMN_CDIAG_XCVRC_PWRI_OVRDपूर्ण,
	अणु0x007F, CMN_TXPUCAL_TUNEपूर्ण,
	अणु0x007F, CMN_TXPDCAL_TUNEपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals usb_100_पूर्णांक_ssc_cmn_vals = अणु
	.reg_pairs = usb_100_पूर्णांक_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(usb_100_पूर्णांक_ssc_cmn_regs),
पूर्ण;

/* Single USB link configuration */
अटल काष्ठा cdns_reg_pairs sl_usb_link_cmn_regs[] = अणु
	अणु0x0000, PHY_PLL_CFGपूर्ण,
	अणु0x8600, CMN_PDIAG_PLL0_CLK_SEL_M0पूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs sl_usb_xcvr_diag_ln_regs[] = अणु
	अणु0x0000, XCVR_DIAG_HSCLK_SELपूर्ण,
	अणु0x0001, XCVR_DIAG_HSCLK_DIVपूर्ण,
	अणु0x0041, XCVR_DIAG_PLLDRC_CTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals sl_usb_link_cmn_vals = अणु
	.reg_pairs = sl_usb_link_cmn_regs,
	.num_regs = ARRAY_SIZE(sl_usb_link_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals sl_usb_xcvr_diag_ln_vals = अणु
	.reg_pairs = sl_usb_xcvr_diag_ln_regs,
	.num_regs = ARRAY_SIZE(sl_usb_xcvr_diag_ln_regs),
पूर्ण;

/* USB PHY PCS common configuration */
अटल काष्ठा cdns_reg_pairs usb_phy_pcs_cmn_regs[] = अणु
	अणु0x0A0A, PHY_PIPE_USB3_GEN2_PRE_CFG0पूर्ण,
	अणु0x1000, PHY_PIPE_USB3_GEN2_POST_CFG0पूर्ण,
	अणु0x0010, PHY_PIPE_USB3_GEN2_POST_CFG1पूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals usb_phy_pcs_cmn_vals = अणु
	.reg_pairs = usb_phy_pcs_cmn_regs,
	.num_regs = ARRAY_SIZE(usb_phy_pcs_cmn_regs),
पूर्ण;

/* USB 100 MHz Ref clk, no SSC */
अटल काष्ठा cdns_reg_pairs sl_usb_100_no_ssc_cmn_regs[] = अणु
	अणु0x0028, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x001E, CMN_PLL1_DSM_FBH_OVRD_M0पूर्ण,
	अणु0x000C, CMN_PLL1_DSM_FBL_OVRD_M0पूर्ण,
	अणु0x0003, CMN_PLL0_VCOCAL_TCTRLपूर्ण,
	अणु0x0003, CMN_PLL1_VCOCAL_TCTRLपूर्ण,
	अणु0x8200, CMN_CDIAG_CDB_PWRI_OVRDपूर्ण,
	अणु0x8200, CMN_CDIAG_XCVRC_PWRI_OVRDपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals sl_usb_100_no_ssc_cmn_vals = अणु
	.reg_pairs = sl_usb_100_no_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(sl_usb_100_no_ssc_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_reg_pairs usb_100_no_ssc_cmn_regs[] = अणु
	अणु0x8200, CMN_CDIAG_CDB_PWRI_OVRDपूर्ण,
	अणु0x8200, CMN_CDIAG_XCVRC_PWRI_OVRDपूर्ण,
	अणु0x007F, CMN_TXPUCAL_TUNEपूर्ण,
	अणु0x007F, CMN_TXPDCAL_TUNEपूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs usb_100_no_ssc_tx_ln_regs[] = अणु
	अणु0x02FF, TX_PSC_A0पूर्ण,
	अणु0x06AF, TX_PSC_A1पूर्ण,
	अणु0x06AE, TX_PSC_A2पूर्ण,
	अणु0x06AE, TX_PSC_A3पूर्ण,
	अणु0x2A82, TX_TXCC_CTRLपूर्ण,
	अणु0x0014, TX_TXCC_CPOST_MULT_01पूर्ण,
	अणु0x0003, XCVR_DIAG_PSC_OVRDपूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs usb_100_no_ssc_rx_ln_regs[] = अणु
	अणु0x0D1D, RX_PSC_A0पूर्ण,
	अणु0x0D1D, RX_PSC_A1पूर्ण,
	अणु0x0D00, RX_PSC_A2पूर्ण,
	अणु0x0500, RX_PSC_A3पूर्ण,
	अणु0x0013, RX_SIGDET_HL_FILT_TMRपूर्ण,
	अणु0x0000, RX_REE_GCSM1_CTRLपूर्ण,
	अणु0x0C02, RX_REE_ATTEN_THRपूर्ण,
	अणु0x0330, RX_REE_SMGM_CTRL1पूर्ण,
	अणु0x0300, RX_REE_SMGM_CTRL2पूर्ण,
	अणु0x0019, RX_REE_TAP1_CLIPपूर्ण,
	अणु0x0019, RX_REE_TAP2TON_CLIPपूर्ण,
	अणु0x1004, RX_DIAG_SIGDET_TUNEपूर्ण,
	अणु0x00F9, RX_DIAG_NQST_CTRLपूर्ण,
	अणु0x0C01, RX_DIAG_DFE_AMP_TUNE_2पूर्ण,
	अणु0x0002, RX_DIAG_DFE_AMP_TUNE_3पूर्ण,
	अणु0x0000, RX_DIAG_PI_CAPपूर्ण,
	अणु0x0031, RX_DIAG_PI_RATEपूर्ण,
	अणु0x0001, RX_DIAG_ACYAपूर्ण,
	अणु0x018C, RX_CDRLF_CNFGपूर्ण,
	अणु0x0003, RX_CDRLF_CNFG3पूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals usb_100_no_ssc_cmn_vals = अणु
	.reg_pairs = usb_100_no_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(usb_100_no_ssc_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals usb_100_no_ssc_tx_ln_vals = अणु
	.reg_pairs = usb_100_no_ssc_tx_ln_regs,
	.num_regs = ARRAY_SIZE(usb_100_no_ssc_tx_ln_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals usb_100_no_ssc_rx_ln_vals = अणु
	.reg_pairs = usb_100_no_ssc_rx_ln_regs,
	.num_regs = ARRAY_SIZE(usb_100_no_ssc_rx_ln_regs),
पूर्ण;

/* Single link USB, 100 MHz Ref clk, पूर्णांकernal SSC */
अटल काष्ठा cdns_reg_pairs sl_usb_100_पूर्णांक_ssc_cmn_regs[] = अणु
	अणु0x0004, CMN_PLL0_DSM_DIAG_M0पूर्ण,
	अणु0x0004, CMN_PLL1_DSM_DIAG_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL1_CP_IADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL1_FILT_PADJ_M0पूर्ण,
	अणु0x0064, CMN_PLL0_INTDIV_M0पूर्ण,
	अणु0x0064, CMN_PLL1_INTDIV_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M0पूर्ण,
	अणु0x0002, CMN_PLL1_FRACDIVH_M0पूर्ण,
	अणु0x0044, CMN_PLL0_HIGH_THR_M0पूर्ण,
	अणु0x0044, CMN_PLL1_HIGH_THR_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL1_CTRL_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M0पूर्ण,
	अणु0x0001, CMN_PLL1_SS_CTRL1_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M0पूर्ण,
	अणु0x011B, CMN_PLL1_SS_CTRL2_M0पूर्ण,
	अणु0x006E, CMN_PLL0_SS_CTRL3_M0पूर्ण,
	अणु0x006E, CMN_PLL1_SS_CTRL3_M0पूर्ण,
	अणु0x000E, CMN_PLL0_SS_CTRL4_M0पूर्ण,
	अणु0x000E, CMN_PLL1_SS_CTRL4_M0पूर्ण,
	अणु0x0C5E, CMN_PLL0_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C5E, CMN_PLL1_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C56, CMN_PLL0_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x0C56, CMN_PLL1_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x0003, CMN_PLL0_VCOCAL_TCTRLपूर्ण,
	अणु0x0003, CMN_PLL1_VCOCAL_TCTRLपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x0005, CMN_PLL0_LOCK_PLLCNT_THRपूर्ण,
	अणु0x0005, CMN_PLL1_LOCK_PLLCNT_THRपूर्ण,
	अणु0x8200, CMN_CDIAG_CDB_PWRI_OVRDपूर्ण,
	अणु0x8200, CMN_CDIAG_XCVRC_PWRI_OVRDपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals sl_usb_100_पूर्णांक_ssc_cmn_vals = अणु
	.reg_pairs = sl_usb_100_पूर्णांक_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(sl_usb_100_पूर्णांक_ssc_cmn_regs),
पूर्ण;

/* PCIe and SGMII/QSGMII Unique SSC link configuration */
अटल काष्ठा cdns_reg_pairs pcie_sgmii_link_cmn_regs[] = अणु
	अणु0x0003, PHY_PLL_CFGपूर्ण,
	अणु0x0601, CMN_PDIAG_PLL0_CLK_SEL_M0पूर्ण,
	अणु0x0400, CMN_PDIAG_PLL0_CLK_SEL_M1पूर्ण,
	अणु0x0601, CMN_PDIAG_PLL1_CLK_SEL_M0पूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs pcie_sgmii_xcvr_diag_ln_regs[] = अणु
	अणु0x0000, XCVR_DIAG_HSCLK_SELपूर्ण,
	अणु0x0001, XCVR_DIAG_HSCLK_DIVपूर्ण,
	अणु0x0012, XCVR_DIAG_PLLDRC_CTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs sgmii_pcie_xcvr_diag_ln_regs[] = अणु
	अणु0x0011, XCVR_DIAG_HSCLK_SELपूर्ण,
	अणु0x0003, XCVR_DIAG_HSCLK_DIVपूर्ण,
	अणु0x009B, XCVR_DIAG_PLLDRC_CTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals pcie_sgmii_link_cmn_vals = अणु
	.reg_pairs = pcie_sgmii_link_cmn_regs,
	.num_regs = ARRAY_SIZE(pcie_sgmii_link_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals pcie_sgmii_xcvr_diag_ln_vals = अणु
	.reg_pairs = pcie_sgmii_xcvr_diag_ln_regs,
	.num_regs = ARRAY_SIZE(pcie_sgmii_xcvr_diag_ln_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals sgmii_pcie_xcvr_diag_ln_vals = अणु
	.reg_pairs = sgmii_pcie_xcvr_diag_ln_regs,
	.num_regs = ARRAY_SIZE(sgmii_pcie_xcvr_diag_ln_regs),
पूर्ण;

/* SGMII 100 MHz Ref clk, no SSC */
अटल काष्ठा cdns_reg_pairs sl_sgmii_100_no_ssc_cmn_regs[] = अणु
	अणु0x0028, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x001E, CMN_PLL1_DSM_FBH_OVRD_M0पूर्ण,
	अणु0x000C, CMN_PLL1_DSM_FBL_OVRD_M0पूर्ण,
	अणु0x0003, CMN_PLL0_VCOCAL_TCTRLपूर्ण,
	अणु0x0003, CMN_PLL1_VCOCAL_TCTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals sl_sgmii_100_no_ssc_cmn_vals = अणु
	.reg_pairs = sl_sgmii_100_no_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(sl_sgmii_100_no_ssc_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_reg_pairs sgmii_100_no_ssc_cmn_regs[] = अणु
	अणु0x007F, CMN_TXPUCAL_TUNEपूर्ण,
	अणु0x007F, CMN_TXPDCAL_TUNEपूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs sgmii_100_no_ssc_tx_ln_regs[] = अणु
	अणु0x00F3, TX_PSC_A0पूर्ण,
	अणु0x04A2, TX_PSC_A2पूर्ण,
	अणु0x04A2, TX_PSC_A3पूर्ण,
	अणु0x0000, TX_TXCC_CPOST_MULT_00पूर्ण,
	अणु0x00B3, DRV_DIAG_TX_DRVपूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs ti_sgmii_100_no_ssc_tx_ln_regs[] = अणु
	अणु0x00F3, TX_PSC_A0पूर्ण,
	अणु0x04A2, TX_PSC_A2पूर्ण,
	अणु0x04A2, TX_PSC_A3पूर्ण,
	अणु0x0000, TX_TXCC_CPOST_MULT_00पूर्ण,
	अणु0x00B3, DRV_DIAG_TX_DRVपूर्ण,
	अणु0x4000, XCVR_DIAG_RXCLK_CTRLपूर्ण,
पूर्ण;

अटल काष्ठा cdns_reg_pairs sgmii_100_no_ssc_rx_ln_regs[] = अणु
	अणु0x091D, RX_PSC_A0पूर्ण,
	अणु0x0900, RX_PSC_A2पूर्ण,
	अणु0x0100, RX_PSC_A3पूर्ण,
	अणु0x03C7, RX_REE_GCSM1_EQENM_PH1पूर्ण,
	अणु0x01C7, RX_REE_GCSM1_EQENM_PH2पूर्ण,
	अणु0x0000, RX_DIAG_DFE_CTRLपूर्ण,
	अणु0x0019, RX_REE_TAP1_CLIPपूर्ण,
	अणु0x0019, RX_REE_TAP2TON_CLIPपूर्ण,
	अणु0x0098, RX_DIAG_NQST_CTRLपूर्ण,
	अणु0x0C01, RX_DIAG_DFE_AMP_TUNE_2पूर्ण,
	अणु0x0000, RX_DIAG_DFE_AMP_TUNE_3पूर्ण,
	अणु0x0000, RX_DIAG_PI_CAPपूर्ण,
	अणु0x0010, RX_DIAG_PI_RATEपूर्ण,
	अणु0x0001, RX_DIAG_ACYAपूर्ण,
	अणु0x018C, RX_CDRLF_CNFGपूर्ण,
पूर्ण;

अटल काष्ठा cdns_torrent_vals sgmii_100_no_ssc_cmn_vals = अणु
	.reg_pairs = sgmii_100_no_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(sgmii_100_no_ssc_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals sgmii_100_no_ssc_tx_ln_vals = अणु
	.reg_pairs = sgmii_100_no_ssc_tx_ln_regs,
	.num_regs = ARRAY_SIZE(sgmii_100_no_ssc_tx_ln_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals ti_sgmii_100_no_ssc_tx_ln_vals = अणु
	.reg_pairs = ti_sgmii_100_no_ssc_tx_ln_regs,
	.num_regs = ARRAY_SIZE(ti_sgmii_100_no_ssc_tx_ln_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals sgmii_100_no_ssc_rx_ln_vals = अणु
	.reg_pairs = sgmii_100_no_ssc_rx_ln_regs,
	.num_regs = ARRAY_SIZE(sgmii_100_no_ssc_rx_ln_regs),
पूर्ण;

/* SGMII 100 MHz Ref clk, पूर्णांकernal SSC */
अटल काष्ठा cdns_reg_pairs sgmii_100_पूर्णांक_ssc_cmn_regs[] = अणु
	अणु0x0004, CMN_PLL0_DSM_DIAG_M0पूर्ण,
	अणु0x0004, CMN_PLL0_DSM_DIAG_M1पूर्ण,
	अणु0x0004, CMN_PLL1_DSM_DIAG_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M1पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M1पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL1_CP_IADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M1पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL1_FILT_PADJ_M0पूर्ण,
	अणु0x0064, CMN_PLL0_INTDIV_M0पूर्ण,
	अणु0x0050, CMN_PLL0_INTDIV_M1पूर्ण,
	अणु0x0064, CMN_PLL1_INTDIV_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M1पूर्ण,
	अणु0x0002, CMN_PLL1_FRACDIVH_M0पूर्ण,
	अणु0x0044, CMN_PLL0_HIGH_THR_M0पूर्ण,
	अणु0x0036, CMN_PLL0_HIGH_THR_M1पूर्ण,
	अणु0x0044, CMN_PLL1_HIGH_THR_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M1पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL1_CTRL_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M1पूर्ण,
	अणु0x0001, CMN_PLL1_SS_CTRL1_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M1पूर्ण,
	अणु0x011B, CMN_PLL1_SS_CTRL2_M0पूर्ण,
	अणु0x006E, CMN_PLL0_SS_CTRL3_M0पूर्ण,
	अणु0x0058, CMN_PLL0_SS_CTRL3_M1पूर्ण,
	अणु0x006E, CMN_PLL1_SS_CTRL3_M0पूर्ण,
	अणु0x000E, CMN_PLL0_SS_CTRL4_M0पूर्ण,
	अणु0x0012, CMN_PLL0_SS_CTRL4_M1पूर्ण,
	अणु0x000E, CMN_PLL1_SS_CTRL4_M0पूर्ण,
	अणु0x0C5E, CMN_PLL0_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C5E, CMN_PLL1_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C56, CMN_PLL0_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x0C56, CMN_PLL1_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x0005, CMN_PLL0_LOCK_PLLCNT_THRपूर्ण,
	अणु0x0005, CMN_PLL1_LOCK_PLLCNT_THRपूर्ण,
	अणु0x007F, CMN_TXPUCAL_TUNEपूर्ण,
	अणु0x007F, CMN_TXPDCAL_TUNEपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals sgmii_100_पूर्णांक_ssc_cmn_vals = अणु
	.reg_pairs = sgmii_100_पूर्णांक_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(sgmii_100_पूर्णांक_ssc_cmn_regs),
पूर्ण;

/* QSGMII 100 MHz Ref clk, no SSC */
अटल काष्ठा cdns_reg_pairs sl_qsgmii_100_no_ssc_cmn_regs[] = अणु
	अणु0x0028, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x001E, CMN_PLL1_DSM_FBH_OVRD_M0पूर्ण,
	अणु0x000C, CMN_PLL1_DSM_FBL_OVRD_M0पूर्ण,
	अणु0x0003, CMN_PLL0_VCOCAL_TCTRLपूर्ण,
	अणु0x0003, CMN_PLL1_VCOCAL_TCTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals sl_qsgmii_100_no_ssc_cmn_vals = अणु
	.reg_pairs = sl_qsgmii_100_no_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(sl_qsgmii_100_no_ssc_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_reg_pairs qsgmii_100_no_ssc_cmn_regs[] = अणु
	अणु0x007F, CMN_TXPUCAL_TUNEपूर्ण,
	अणु0x007F, CMN_TXPDCAL_TUNEपूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs qsgmii_100_no_ssc_tx_ln_regs[] = अणु
	अणु0x00F3, TX_PSC_A0पूर्ण,
	अणु0x04A2, TX_PSC_A2पूर्ण,
	अणु0x04A2, TX_PSC_A3पूर्ण,
	अणु0x0000, TX_TXCC_CPOST_MULT_00पूर्ण,
	अणु0x0011, TX_TXCC_MGNFS_MULT_100पूर्ण,
	अणु0x0003, DRV_DIAG_TX_DRVपूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs ti_qsgmii_100_no_ssc_tx_ln_regs[] = अणु
	अणु0x00F3, TX_PSC_A0पूर्ण,
	अणु0x04A2, TX_PSC_A2पूर्ण,
	अणु0x04A2, TX_PSC_A3पूर्ण,
	अणु0x0000, TX_TXCC_CPOST_MULT_00पूर्ण,
	अणु0x0011, TX_TXCC_MGNFS_MULT_100पूर्ण,
	अणु0x0003, DRV_DIAG_TX_DRVपूर्ण,
	अणु0x4000, XCVR_DIAG_RXCLK_CTRLपूर्ण,
पूर्ण;

अटल काष्ठा cdns_reg_pairs qsgmii_100_no_ssc_rx_ln_regs[] = अणु
	अणु0x091D, RX_PSC_A0पूर्ण,
	अणु0x0900, RX_PSC_A2पूर्ण,
	अणु0x0100, RX_PSC_A3पूर्ण,
	अणु0x03C7, RX_REE_GCSM1_EQENM_PH1पूर्ण,
	अणु0x01C7, RX_REE_GCSM1_EQENM_PH2पूर्ण,
	अणु0x0000, RX_DIAG_DFE_CTRLपूर्ण,
	अणु0x0019, RX_REE_TAP1_CLIPपूर्ण,
	अणु0x0019, RX_REE_TAP2TON_CLIPपूर्ण,
	अणु0x0098, RX_DIAG_NQST_CTRLपूर्ण,
	अणु0x0C01, RX_DIAG_DFE_AMP_TUNE_2पूर्ण,
	अणु0x0000, RX_DIAG_DFE_AMP_TUNE_3पूर्ण,
	अणु0x0000, RX_DIAG_PI_CAPपूर्ण,
	अणु0x0010, RX_DIAG_PI_RATEपूर्ण,
	अणु0x0001, RX_DIAG_ACYAपूर्ण,
	अणु0x018C, RX_CDRLF_CNFGपूर्ण,
पूर्ण;

अटल काष्ठा cdns_torrent_vals qsgmii_100_no_ssc_cmn_vals = अणु
	.reg_pairs = qsgmii_100_no_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(qsgmii_100_no_ssc_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals qsgmii_100_no_ssc_tx_ln_vals = अणु
	.reg_pairs = qsgmii_100_no_ssc_tx_ln_regs,
	.num_regs = ARRAY_SIZE(qsgmii_100_no_ssc_tx_ln_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals ti_qsgmii_100_no_ssc_tx_ln_vals = अणु
	.reg_pairs = ti_qsgmii_100_no_ssc_tx_ln_regs,
	.num_regs = ARRAY_SIZE(ti_qsgmii_100_no_ssc_tx_ln_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals qsgmii_100_no_ssc_rx_ln_vals = अणु
	.reg_pairs = qsgmii_100_no_ssc_rx_ln_regs,
	.num_regs = ARRAY_SIZE(qsgmii_100_no_ssc_rx_ln_regs),
पूर्ण;

/* QSGMII 100 MHz Ref clk, पूर्णांकernal SSC */
अटल काष्ठा cdns_reg_pairs qsgmii_100_पूर्णांक_ssc_cmn_regs[] = अणु
	अणु0x0004, CMN_PLL0_DSM_DIAG_M0पूर्ण,
	अणु0x0004, CMN_PLL0_DSM_DIAG_M1पूर्ण,
	अणु0x0004, CMN_PLL1_DSM_DIAG_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M1पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M1पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL1_CP_IADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M1पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL1_FILT_PADJ_M0पूर्ण,
	अणु0x0064, CMN_PLL0_INTDIV_M0पूर्ण,
	अणु0x0050, CMN_PLL0_INTDIV_M1पूर्ण,
	अणु0x0064, CMN_PLL1_INTDIV_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M1पूर्ण,
	अणु0x0002, CMN_PLL1_FRACDIVH_M0पूर्ण,
	अणु0x0044, CMN_PLL0_HIGH_THR_M0पूर्ण,
	अणु0x0036, CMN_PLL0_HIGH_THR_M1पूर्ण,
	अणु0x0044, CMN_PLL1_HIGH_THR_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M1पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL1_CTRL_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M1पूर्ण,
	अणु0x0001, CMN_PLL1_SS_CTRL1_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M1पूर्ण,
	अणु0x011B, CMN_PLL1_SS_CTRL2_M0पूर्ण,
	अणु0x006E, CMN_PLL0_SS_CTRL3_M0पूर्ण,
	अणु0x0058, CMN_PLL0_SS_CTRL3_M1पूर्ण,
	अणु0x006E, CMN_PLL1_SS_CTRL3_M0पूर्ण,
	अणु0x000E, CMN_PLL0_SS_CTRL4_M0पूर्ण,
	अणु0x0012, CMN_PLL0_SS_CTRL4_M1पूर्ण,
	अणु0x000E, CMN_PLL1_SS_CTRL4_M0पूर्ण,
	अणु0x0C5E, CMN_PLL0_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C5E, CMN_PLL1_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C56, CMN_PLL0_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x0C56, CMN_PLL1_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x0005, CMN_PLL0_LOCK_PLLCNT_THRपूर्ण,
	अणु0x0005, CMN_PLL1_LOCK_PLLCNT_THRपूर्ण,
	अणु0x007F, CMN_TXPUCAL_TUNEपूर्ण,
	अणु0x007F, CMN_TXPDCAL_TUNEपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals qsgmii_100_पूर्णांक_ssc_cmn_vals = अणु
	.reg_pairs = qsgmii_100_पूर्णांक_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(qsgmii_100_पूर्णांक_ssc_cmn_regs),
पूर्ण;

/* Single SGMII/QSGMII link configuration */
अटल काष्ठा cdns_reg_pairs sl_sgmii_link_cmn_regs[] = अणु
	अणु0x0000, PHY_PLL_CFGपूर्ण,
	अणु0x0601, CMN_PDIAG_PLL0_CLK_SEL_M0पूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs sl_sgmii_xcvr_diag_ln_regs[] = अणु
	अणु0x0000, XCVR_DIAG_HSCLK_SELपूर्ण,
	अणु0x0003, XCVR_DIAG_HSCLK_DIVपूर्ण,
	अणु0x0013, XCVR_DIAG_PLLDRC_CTRLपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals sl_sgmii_link_cmn_vals = अणु
	.reg_pairs = sl_sgmii_link_cmn_regs,
	.num_regs = ARRAY_SIZE(sl_sgmii_link_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals sl_sgmii_xcvr_diag_ln_vals = अणु
	.reg_pairs = sl_sgmii_xcvr_diag_ln_regs,
	.num_regs = ARRAY_SIZE(sl_sgmii_xcvr_diag_ln_regs),
पूर्ण;

/* Multi link PCIe, 100 MHz Ref clk, पूर्णांकernal SSC */
अटल काष्ठा cdns_reg_pairs pcie_100_पूर्णांक_ssc_cmn_regs[] = अणु
	अणु0x0004, CMN_PLL0_DSM_DIAG_M0पूर्ण,
	अणु0x0004, CMN_PLL0_DSM_DIAG_M1पूर्ण,
	अणु0x0004, CMN_PLL1_DSM_DIAG_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M1पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M1पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL1_CP_IADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M1पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL1_FILT_PADJ_M0पूर्ण,
	अणु0x0064, CMN_PLL0_INTDIV_M0पूर्ण,
	अणु0x0050, CMN_PLL0_INTDIV_M1पूर्ण,
	अणु0x0064, CMN_PLL1_INTDIV_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M1पूर्ण,
	अणु0x0002, CMN_PLL1_FRACDIVH_M0पूर्ण,
	अणु0x0044, CMN_PLL0_HIGH_THR_M0पूर्ण,
	अणु0x0036, CMN_PLL0_HIGH_THR_M1पूर्ण,
	अणु0x0044, CMN_PLL1_HIGH_THR_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M1पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL1_CTRL_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M1पूर्ण,
	अणु0x0001, CMN_PLL1_SS_CTRL1_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M1पूर्ण,
	अणु0x011B, CMN_PLL1_SS_CTRL2_M0पूर्ण,
	अणु0x006E, CMN_PLL0_SS_CTRL3_M0पूर्ण,
	अणु0x0058, CMN_PLL0_SS_CTRL3_M1पूर्ण,
	अणु0x006E, CMN_PLL1_SS_CTRL3_M0पूर्ण,
	अणु0x000E, CMN_PLL0_SS_CTRL4_M0पूर्ण,
	अणु0x0012, CMN_PLL0_SS_CTRL4_M1पूर्ण,
	अणु0x000E, CMN_PLL1_SS_CTRL4_M0पूर्ण,
	अणु0x0C5E, CMN_PLL0_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C5E, CMN_PLL1_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C56, CMN_PLL0_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x0C56, CMN_PLL1_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x0005, CMN_PLL0_LOCK_PLLCNT_THRपूर्ण,
	अणु0x0005, CMN_PLL1_LOCK_PLLCNT_THRपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals pcie_100_पूर्णांक_ssc_cmn_vals = अणु
	.reg_pairs = pcie_100_पूर्णांक_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(pcie_100_पूर्णांक_ssc_cmn_regs),
पूर्ण;

/* Single link PCIe, 100 MHz Ref clk, पूर्णांकernal SSC */
अटल काष्ठा cdns_reg_pairs sl_pcie_100_पूर्णांक_ssc_cmn_regs[] = अणु
	अणु0x0004, CMN_PLL0_DSM_DIAG_M0पूर्ण,
	अणु0x0004, CMN_PLL0_DSM_DIAG_M1पूर्ण,
	अणु0x0004, CMN_PLL1_DSM_DIAG_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M0पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL0_CP_PADJ_M1पूर्ण,
	अणु0x0509, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M0पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL0_CP_IADJ_M1पूर्ण,
	अणु0x0F00, CMN_PDIAG_PLL1_CP_IADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M0पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL0_FILT_PADJ_M1पूर्ण,
	अणु0x0F08, CMN_PDIAG_PLL1_FILT_PADJ_M0पूर्ण,
	अणु0x0064, CMN_PLL0_INTDIV_M0पूर्ण,
	अणु0x0050, CMN_PLL0_INTDIV_M1पूर्ण,
	अणु0x0050, CMN_PLL1_INTDIV_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M0पूर्ण,
	अणु0x0002, CMN_PLL0_FRACDIVH_M1पूर्ण,
	अणु0x0002, CMN_PLL1_FRACDIVH_M0पूर्ण,
	अणु0x0044, CMN_PLL0_HIGH_THR_M0पूर्ण,
	अणु0x0036, CMN_PLL0_HIGH_THR_M1पूर्ण,
	अणु0x0036, CMN_PLL1_HIGH_THR_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M0पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL0_CTRL_M1पूर्ण,
	अणु0x0002, CMN_PDIAG_PLL1_CTRL_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M0पूर्ण,
	अणु0x0001, CMN_PLL0_SS_CTRL1_M1पूर्ण,
	अणु0x0001, CMN_PLL1_SS_CTRL1_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M0पूर्ण,
	अणु0x011B, CMN_PLL0_SS_CTRL2_M1पूर्ण,
	अणु0x011B, CMN_PLL1_SS_CTRL2_M0पूर्ण,
	अणु0x006E, CMN_PLL0_SS_CTRL3_M0पूर्ण,
	अणु0x0058, CMN_PLL0_SS_CTRL3_M1पूर्ण,
	अणु0x0058, CMN_PLL1_SS_CTRL3_M0पूर्ण,
	अणु0x000E, CMN_PLL0_SS_CTRL4_M0पूर्ण,
	अणु0x0012, CMN_PLL0_SS_CTRL4_M1पूर्ण,
	अणु0x0012, CMN_PLL1_SS_CTRL4_M0पूर्ण,
	अणु0x0C5E, CMN_PLL0_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C5E, CMN_PLL1_VCOCAL_REFTIM_STARTपूर्ण,
	अणु0x0C56, CMN_PLL0_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x0C56, CMN_PLL1_VCOCAL_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_REFCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL0_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x00C7, CMN_PLL1_LOCK_PLLCNT_STARTपूर्ण,
	अणु0x0005, CMN_PLL0_LOCK_PLLCNT_THRपूर्ण,
	अणु0x0005, CMN_PLL1_LOCK_PLLCNT_THRपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals sl_pcie_100_पूर्णांक_ssc_cmn_vals = अणु
	.reg_pairs = sl_pcie_100_पूर्णांक_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(sl_pcie_100_पूर्णांक_ssc_cmn_regs),
पूर्ण;

/* PCIe, 100 MHz Ref clk, no SSC & बाह्यal SSC */
अटल काष्ठा cdns_reg_pairs pcie_100_ext_no_ssc_cmn_regs[] = अणु
	अणु0x0028, CMN_PDIAG_PLL1_CP_PADJ_M0पूर्ण,
	अणु0x001E, CMN_PLL1_DSM_FBH_OVRD_M0पूर्ण,
	अणु0x000C, CMN_PLL1_DSM_FBL_OVRD_M0पूर्ण
पूर्ण;

अटल काष्ठा cdns_reg_pairs pcie_100_ext_no_ssc_rx_ln_regs[] = अणु
	अणु0x0019, RX_REE_TAP1_CLIPपूर्ण,
	अणु0x0019, RX_REE_TAP2TON_CLIPपूर्ण,
	अणु0x0001, RX_DIAG_ACYAपूर्ण
पूर्ण;

अटल काष्ठा cdns_torrent_vals pcie_100_no_ssc_cmn_vals = अणु
	.reg_pairs = pcie_100_ext_no_ssc_cmn_regs,
	.num_regs = ARRAY_SIZE(pcie_100_ext_no_ssc_cmn_regs),
पूर्ण;

अटल काष्ठा cdns_torrent_vals pcie_100_no_ssc_rx_ln_vals = अणु
	.reg_pairs = pcie_100_ext_no_ssc_rx_ln_regs,
	.num_regs = ARRAY_SIZE(pcie_100_ext_no_ssc_rx_ln_regs),
पूर्ण;

अटल स्थिर काष्ठा cdns_torrent_data cdns_map_torrent = अणु
	.block_offset_shअगरt = 0x2,
	.reg_offset_shअगरt = 0x2,
	.link_cmn_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &pcie_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &pcie_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &pcie_usb_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_usb_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_usb_link_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &pcie_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &usb_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &pcie_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &usb_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_usb_link_cmn_vals,
				[EXTERNAL_SSC] = &sl_usb_link_cmn_vals,
				[INTERNAL_SSC] = &sl_usb_link_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &pcie_usb_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_usb_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_usb_link_cmn_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.xcvr_diag_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &pcie_usb_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &pcie_usb_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &pcie_usb_xcvr_diag_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_usb_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sl_usb_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sl_usb_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_pcie_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &usb_pcie_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &usb_pcie_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.pcs_cmn_vals = अणु
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &usb_phy_pcs_cmn_vals,
				[EXTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
				[INTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_phy_pcs_cmn_vals,
				[EXTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
				[INTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_phy_pcs_cmn_vals,
				[EXTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
				[INTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_phy_pcs_cmn_vals,
				[EXTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
				[INTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.cmn_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = &sl_pcie_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &pcie_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &pcie_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &pcie_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &pcie_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &pcie_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &pcie_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_100_no_ssc_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sgmii_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sgmii_100_no_ssc_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_qsgmii_100_no_ssc_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &qsgmii_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &qsgmii_100_no_ssc_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sl_usb_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &usb_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sl_usb_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sl_usb_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.tx_ln_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &sgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &sgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &qsgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &qsgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.rx_ln_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cdns_torrent_data ti_j721e_map_torrent = अणु
	.block_offset_shअगरt = 0x0,
	.reg_offset_shअगरt = 0x1,
	.link_cmn_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &pcie_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &pcie_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &pcie_usb_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_usb_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_usb_link_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &pcie_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &usb_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &pcie_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &usb_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_usb_link_cmn_vals,
				[EXTERNAL_SSC] = &sl_usb_link_cmn_vals,
				[INTERNAL_SSC] = &sl_usb_link_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &pcie_usb_link_cmn_vals,
				[EXTERNAL_SSC] = &pcie_usb_link_cmn_vals,
				[INTERNAL_SSC] = &pcie_usb_link_cmn_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_sgmii_link_cmn_vals,
				[EXTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
				[INTERNAL_SSC] = &usb_sgmii_link_cmn_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.xcvr_diag_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &pcie_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &pcie_usb_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &pcie_usb_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &pcie_usb_xcvr_diag_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sgmii_pcie_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sgmii_usb_xcvr_diag_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_usb_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &sl_usb_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &sl_usb_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_pcie_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &usb_pcie_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &usb_pcie_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
				[EXTERNAL_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
				[INTERNAL_SSC] = &usb_sgmii_xcvr_diag_ln_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.pcs_cmn_vals = अणु
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &usb_phy_pcs_cmn_vals,
				[EXTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
				[INTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_phy_pcs_cmn_vals,
				[EXTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
				[INTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_phy_pcs_cmn_vals,
				[EXTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
				[INTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_phy_pcs_cmn_vals,
				[EXTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
				[INTERNAL_SSC] = &usb_phy_pcs_cmn_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.cmn_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = &sl_pcie_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &pcie_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &pcie_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &pcie_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &pcie_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &pcie_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &pcie_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_sgmii_100_no_ssc_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sgmii_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sgmii_100_no_ssc_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_qsgmii_100_no_ssc_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &qsgmii_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &qsgmii_100_no_ssc_cmn_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sl_usb_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &usb_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sl_usb_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[EXTERNAL_SSC] = &sl_usb_100_no_ssc_cmn_vals,
				[INTERNAL_SSC] = &sl_usb_100_पूर्णांक_ssc_cmn_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.tx_ln_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = शून्य,
				[EXTERNAL_SSC] = शून्य,
				[INTERNAL_SSC] = शून्य,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &ti_sgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &ti_sgmii_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &ti_sgmii_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &ti_sgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &ti_sgmii_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &ti_sgmii_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &ti_sgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &ti_qsgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &ti_qsgmii_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &ti_qsgmii_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &ti_qsgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &ti_qsgmii_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &ti_qsgmii_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &ti_qsgmii_100_no_ssc_tx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_tx_ln_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	.rx_ln_vals = अणु
		[TYPE_PCIE] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &pcie_100_no_ssc_rx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_SGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &sgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_QSGMII] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_USB] = अणु
				[NO_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &qsgmii_100_no_ssc_rx_ln_vals,
			पूर्ण,
		पूर्ण,
		[TYPE_USB] = अणु
			[TYPE_NONE] = अणु
				[NO_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_PCIE] = अणु
				[NO_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_SGMII] = अणु
				[NO_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
			पूर्ण,
			[TYPE_QSGMII] = अणु
				[NO_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[EXTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
				[INTERNAL_SSC] = &usb_100_no_ssc_rx_ln_vals,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_torrent_phy_of_match[] = अणु
	अणु
		.compatible = "cdns,torrent-phy",
		.data = &cdns_map_torrent,
	पूर्ण,
	अणु
		.compatible = "ti,j721e-serdes-10g",
		.data = &ti_j721e_map_torrent,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_torrent_phy_of_match);

अटल काष्ठा platक्रमm_driver cdns_torrent_phy_driver = अणु
	.probe	= cdns_torrent_phy_probe,
	.हटाओ = cdns_torrent_phy_हटाओ,
	.driver = अणु
		.name	= "cdns-torrent-phy",
		.of_match_table	= cdns_torrent_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(cdns_torrent_phy_driver);

MODULE_AUTHOR("Cadence Design Systems, Inc.");
MODULE_DESCRIPTION("Cadence Torrent PHY driver");
MODULE_LICENSE("GPL v2");
