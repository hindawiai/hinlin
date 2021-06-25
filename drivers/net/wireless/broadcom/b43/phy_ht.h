<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_PHY_HT_H_
#घोषणा B43_PHY_HT_H_

#समावेश "phy_common.h"


#घोषणा B43_PHY_HT_BBCFG			0x001 /* BB config */
#घोषणा  B43_PHY_HT_BBCFG_RSTCCA		0x4000 /* Reset CCA */
#घोषणा  B43_PHY_HT_BBCFG_RSTRX			0x8000 /* Reset RX */
#घोषणा B43_PHY_HT_BANDCTL			0x009 /* Band control */
#घोषणा  B43_PHY_HT_BANDCTL_5GHZ		0x0001 /* Use the 5GHz band */
#घोषणा B43_PHY_HT_TABLE_ADDR			0x072 /* Table address */
#घोषणा B43_PHY_HT_TABLE_DATALO			0x073 /* Table data low */
#घोषणा B43_PHY_HT_TABLE_DATAHI			0x074 /* Table data high */
#घोषणा B43_PHY_HT_CLASS_CTL			0x0B0 /* Classअगरier control */
#घोषणा  B43_PHY_HT_CLASS_CTL_CCK_EN		0x0001 /* CCK enable */
#घोषणा  B43_PHY_HT_CLASS_CTL_OFDM_EN		0x0002 /* OFDM enable */
#घोषणा  B43_PHY_HT_CLASS_CTL_WAITED_EN		0x0004 /* Waited enable */
#घोषणा B43_PHY_HT_IQLOCAL_CMDGCTL		0x0C2	/* I/Q LO cal command G control */
#घोषणा B43_PHY_HT_SAMP_CMD			0x0C3	/* Sample command */
#घोषणा  B43_PHY_HT_SAMP_CMD_STOP		0x0002	/* Stop */
#घोषणा B43_PHY_HT_SAMP_LOOP_CNT		0x0C4	/* Sample loop count */
#घोषणा B43_PHY_HT_SAMP_WAIT_CNT		0x0C5	/* Sample रुको count */
#घोषणा B43_PHY_HT_SAMP_DEP_CNT			0x0C6	/* Sample depth count */
#घोषणा B43_PHY_HT_SAMP_STAT			0x0C7	/* Sample status */
#घोषणा B43_PHY_HT_EST_PWR_C1			0x118
#घोषणा B43_PHY_HT_EST_PWR_C2			0x119
#घोषणा B43_PHY_HT_EST_PWR_C3			0x11A
#घोषणा B43_PHY_HT_TSSIMODE			0x122	/* TSSI mode */
#घोषणा  B43_PHY_HT_TSSIMODE_EN			0x0001	/* TSSI enable */
#घोषणा  B43_PHY_HT_TSSIMODE_PDEN		0x0002	/* Power det enable */
#घोषणा B43_PHY_HT_BW1				0x1CE
#घोषणा B43_PHY_HT_BW2				0x1CF
#घोषणा B43_PHY_HT_BW3				0x1D0
#घोषणा B43_PHY_HT_BW4				0x1D1
#घोषणा B43_PHY_HT_BW5				0x1D2
#घोषणा B43_PHY_HT_BW6				0x1D3
#घोषणा B43_PHY_HT_TXPCTL_CMD_C1		0x1E7	/* TX घातer control command */
#घोषणा  B43_PHY_HT_TXPCTL_CMD_C1_INIT		0x007F	/* Init */
#घोषणा  B43_PHY_HT_TXPCTL_CMD_C1_COEFF		0x2000	/* Power control coefficients */
#घोषणा  B43_PHY_HT_TXPCTL_CMD_C1_HWPCTLEN	0x4000	/* Hardware TX घातer control enable */
#घोषणा  B43_PHY_HT_TXPCTL_CMD_C1_PCTLEN	0x8000	/* TX घातer control enable */
#घोषणा B43_PHY_HT_TXPCTL_N			0x1E8	/* TX घातer control N num */
#घोषणा  B43_PHY_HT_TXPCTL_N_TSSID		0x00FF	/* N TSSI delay */
#घोषणा  B43_PHY_HT_TXPCTL_N_TSSID_SHIFT	0
#घोषणा  B43_PHY_HT_TXPCTL_N_NPTIL2		0x0700	/* N PT पूर्णांकeger log2 */
#घोषणा  B43_PHY_HT_TXPCTL_N_NPTIL2_SHIFT	8
#घोषणा B43_PHY_HT_TXPCTL_IDLE_TSSI		0x1E9	/* TX घातer control idle TSSI */
#घोषणा  B43_PHY_HT_TXPCTL_IDLE_TSSI_C1		0x003F
#घोषणा  B43_PHY_HT_TXPCTL_IDLE_TSSI_C1_SHIFT	0
#घोषणा  B43_PHY_HT_TXPCTL_IDLE_TSSI_C2		0x3F00
#घोषणा  B43_PHY_HT_TXPCTL_IDLE_TSSI_C2_SHIFT	8
#घोषणा  B43_PHY_HT_TXPCTL_IDLE_TSSI_BINF	0x8000	/* Raw TSSI offset bin क्रमmat */
#घोषणा B43_PHY_HT_TXPCTL_TARG_PWR		0x1EA	/* TX घातer control target घातer */
#घोषणा  B43_PHY_HT_TXPCTL_TARG_PWR_C1		0x00FF	/* Power 0 */
#घोषणा  B43_PHY_HT_TXPCTL_TARG_PWR_C1_SHIFT	0
#घोषणा  B43_PHY_HT_TXPCTL_TARG_PWR_C2		0xFF00	/* Power 1 */
#घोषणा  B43_PHY_HT_TXPCTL_TARG_PWR_C2_SHIFT	8
#घोषणा B43_PHY_HT_TX_PCTL_STATUS_C1		0x1ED
#घोषणा B43_PHY_HT_TX_PCTL_STATUS_C2		0x1EE
#घोषणा B43_PHY_HT_TXPCTL_CMD_C2		0x222
#घोषणा  B43_PHY_HT_TXPCTL_CMD_C2_INIT		0x007F
#घोषणा B43_PHY_HT_RSSI_C1			0x219
#घोषणा B43_PHY_HT_RSSI_C2			0x21A
#घोषणा B43_PHY_HT_RSSI_C3			0x21B

#घोषणा B43_PHY_HT_C1_CLIP1THRES		B43_PHY_OFDM(0x00E)
#घोषणा B43_PHY_HT_C2_CLIP1THRES		B43_PHY_OFDM(0x04E)
#घोषणा B43_PHY_HT_C3_CLIP1THRES		B43_PHY_OFDM(0x08E)

#घोषणा B43_PHY_HT_RF_SEQ_MODE			B43_PHY_EXTG(0x000)
#घोषणा  B43_PHY_HT_RF_SEQ_MODE_CA_OVER		0x0001	/* Core active override */
#घोषणा  B43_PHY_HT_RF_SEQ_MODE_TR_OVER		0x0002	/* Trigger override */
#घोषणा B43_PHY_HT_RF_SEQ_TRIG			B43_PHY_EXTG(0x003)
#घोषणा  B43_PHY_HT_RF_SEQ_TRIG_RX2TX		0x0001 /* RX2TX */
#घोषणा  B43_PHY_HT_RF_SEQ_TRIG_TX2RX		0x0002 /* TX2RX */
#घोषणा  B43_PHY_HT_RF_SEQ_TRIG_UPGH		0x0004 /* Update gain H */
#घोषणा  B43_PHY_HT_RF_SEQ_TRIG_UPGL		0x0008 /* Update gain L */
#घोषणा  B43_PHY_HT_RF_SEQ_TRIG_UPGU		0x0010 /* Update gain U */
#घोषणा  B43_PHY_HT_RF_SEQ_TRIG_RST2RX		0x0020 /* Reset to RX */
#घोषणा B43_PHY_HT_RF_SEQ_STATUS		B43_PHY_EXTG(0x004)
/* Values क्रम the status are the same as क्रम the trigger */

#घोषणा B43_PHY_HT_RF_CTL_CMD			0x810
#घोषणा  B43_PHY_HT_RF_CTL_CMD_FORCE		0x0001
#घोषणा  B43_PHY_HT_RF_CTL_CMD_CHIP0_PU		0x0002

#घोषणा B43_PHY_HT_RF_CTL_INT_C1		B43_PHY_EXTG(0x04c)
#घोषणा B43_PHY_HT_RF_CTL_INT_C2		B43_PHY_EXTG(0x06c)
#घोषणा B43_PHY_HT_RF_CTL_INT_C3		B43_PHY_EXTG(0x08c)

#घोषणा B43_PHY_HT_AFE_C1_OVER			B43_PHY_EXTG(0x110)
#घोषणा B43_PHY_HT_AFE_C1			B43_PHY_EXTG(0x111)
#घोषणा B43_PHY_HT_AFE_C2_OVER			B43_PHY_EXTG(0x114)
#घोषणा B43_PHY_HT_AFE_C2			B43_PHY_EXTG(0x115)
#घोषणा B43_PHY_HT_AFE_C3_OVER			B43_PHY_EXTG(0x118)
#घोषणा B43_PHY_HT_AFE_C3			B43_PHY_EXTG(0x119)

#घोषणा B43_PHY_HT_TXPCTL_CMD_C3		B43_PHY_EXTG(0x164)
#घोषणा  B43_PHY_HT_TXPCTL_CMD_C3_INIT		0x007F
#घोषणा B43_PHY_HT_TXPCTL_IDLE_TSSI2		B43_PHY_EXTG(0x165)	/* TX घातer control idle TSSI */
#घोषणा  B43_PHY_HT_TXPCTL_IDLE_TSSI2_C3	0x003F
#घोषणा  B43_PHY_HT_TXPCTL_IDLE_TSSI2_C3_SHIFT	0
#घोषणा B43_PHY_HT_TXPCTL_TARG_PWR2		B43_PHY_EXTG(0x166)	/* TX घातer control target घातer */
#घोषणा  B43_PHY_HT_TXPCTL_TARG_PWR2_C3		0x00FF
#घोषणा  B43_PHY_HT_TXPCTL_TARG_PWR2_C3_SHIFT	0
#घोषणा B43_PHY_HT_TX_PCTL_STATUS_C3		B43_PHY_EXTG(0x169)

#घोषणा B43_PHY_B_BBCFG				B43_PHY_N_BMODE(0x001)
#घोषणा  B43_PHY_B_BBCFG_RSTCCA			0x4000 /* Reset CCA */
#घोषणा  B43_PHY_B_BBCFG_RSTRX			0x8000 /* Reset RX */
#घोषणा B43_PHY_HT_TEST				B43_PHY_N_BMODE(0x00A)


/* Values क्रम PHY रेजिस्टरs used on channel चयनing */
काष्ठा b43_phy_ht_channeltab_e_phy अणु
	u16 bw1;
	u16 bw2;
	u16 bw3;
	u16 bw4;
	u16 bw5;
	u16 bw6;
पूर्ण;


काष्ठा b43_phy_ht अणु
	u16 rf_ctl_पूर्णांक_save[3];

	bool tx_pwr_ctl;
	u8 tx_pwr_idx[3];

	s32 bb_mult_save[3];

	u8 idle_tssi[3];
पूर्ण;


काष्ठा b43_phy_operations;
बाह्य स्थिर काष्ठा b43_phy_operations b43_phyops_ht;

#पूर्ण_अगर /* B43_PHY_HT_H_ */
