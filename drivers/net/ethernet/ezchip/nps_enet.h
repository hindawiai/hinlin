<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2015 EZchip Technologies.
 */

#अगर_अघोषित _NPS_ENET_H
#घोषणा _NPS_ENET_H

/* शेष values */
#घोषणा NPS_ENET_NAPI_POLL_WEIGHT		0x2
#घोषणा NPS_ENET_MAX_FRAME_LENGTH		0x3FFF
#घोषणा NPS_ENET_GE_MAC_CFG_0_TX_FC_RETR	0x7
#घोषणा NPS_ENET_GE_MAC_CFG_0_RX_IFG		0x5
#घोषणा NPS_ENET_GE_MAC_CFG_0_TX_IFG		0xC
#घोषणा NPS_ENET_GE_MAC_CFG_0_TX_PR_LEN		0x7
#घोषणा NPS_ENET_GE_MAC_CFG_2_STAT_EN		0x3
#घोषणा NPS_ENET_GE_MAC_CFG_3_RX_IFG_TH		0x14
#घोषणा NPS_ENET_GE_MAC_CFG_3_MAX_LEN		0x3FFC
#घोषणा NPS_ENET_ENABLE				1
#घोषणा NPS_ENET_DISABLE			0

/* रेजिस्टर definitions  */
#घोषणा NPS_ENET_REG_TX_CTL		0x800
#घोषणा NPS_ENET_REG_TX_BUF		0x808
#घोषणा NPS_ENET_REG_RX_CTL		0x810
#घोषणा NPS_ENET_REG_RX_BUF		0x818
#घोषणा NPS_ENET_REG_BUF_INT_ENABLE	0x8C0
#घोषणा NPS_ENET_REG_GE_MAC_CFG_0	0x1000
#घोषणा NPS_ENET_REG_GE_MAC_CFG_1	0x1004
#घोषणा NPS_ENET_REG_GE_MAC_CFG_2	0x1008
#घोषणा NPS_ENET_REG_GE_MAC_CFG_3	0x100C
#घोषणा NPS_ENET_REG_GE_RST		0x1400
#घोषणा NPS_ENET_REG_PHASE_FIFO_CTL	0x1404

/* Tx control रेजिस्टर masks and shअगरts */
#घोषणा TX_CTL_NT_MASK 0x7FF
#घोषणा TX_CTL_NT_SHIFT 0
#घोषणा TX_CTL_ET_MASK 0x4000
#घोषणा TX_CTL_ET_SHIFT 14
#घोषणा TX_CTL_CT_MASK 0x8000
#घोषणा TX_CTL_CT_SHIFT 15

/* Rx control रेजिस्टर masks and shअगरts */
#घोषणा RX_CTL_NR_MASK 0x7FF
#घोषणा RX_CTL_NR_SHIFT 0
#घोषणा RX_CTL_CRC_MASK 0x2000
#घोषणा RX_CTL_CRC_SHIFT 13
#घोषणा RX_CTL_ER_MASK 0x4000
#घोषणा RX_CTL_ER_SHIFT 14
#घोषणा RX_CTL_CR_MASK 0x8000
#घोषणा RX_CTL_CR_SHIFT 15

/* Interrupt enable क्रम data buffer events रेजिस्टर masks and shअगरts */
#घोषणा RX_RDY_MASK 0x1
#घोषणा RX_RDY_SHIFT 0
#घोषणा TX_DONE_MASK 0x2
#घोषणा TX_DONE_SHIFT 1

/* Gbps Eth MAC Configuration 0 रेजिस्टर masks and shअगरts */
#घोषणा CFG_0_RX_EN_MASK 0x1
#घोषणा CFG_0_RX_EN_SHIFT 0
#घोषणा CFG_0_TX_EN_MASK 0x2
#घोषणा CFG_0_TX_EN_SHIFT 1
#घोषणा CFG_0_TX_FC_EN_MASK 0x4
#घोषणा CFG_0_TX_FC_EN_SHIFT 2
#घोषणा CFG_0_TX_PAD_EN_MASK 0x8
#घोषणा CFG_0_TX_PAD_EN_SHIFT 3
#घोषणा CFG_0_TX_CRC_EN_MASK 0x10
#घोषणा CFG_0_TX_CRC_EN_SHIFT 4
#घोषणा CFG_0_RX_FC_EN_MASK 0x20
#घोषणा CFG_0_RX_FC_EN_SHIFT 5
#घोषणा CFG_0_RX_CRC_STRIP_MASK 0x40
#घोषणा CFG_0_RX_CRC_STRIP_SHIFT 6
#घोषणा CFG_0_RX_CRC_IGNORE_MASK 0x80
#घोषणा CFG_0_RX_CRC_IGNORE_SHIFT 7
#घोषणा CFG_0_RX_LENGTH_CHECK_EN_MASK 0x100
#घोषणा CFG_0_RX_LENGTH_CHECK_EN_SHIFT 8
#घोषणा CFG_0_TX_FC_RETR_MASK 0xE00
#घोषणा CFG_0_TX_FC_RETR_SHIFT 9
#घोषणा CFG_0_RX_IFG_MASK 0xF000
#घोषणा CFG_0_RX_IFG_SHIFT 12
#घोषणा CFG_0_TX_IFG_MASK 0x3F0000
#घोषणा CFG_0_TX_IFG_SHIFT 16
#घोषणा CFG_0_RX_PR_CHECK_EN_MASK 0x400000
#घोषणा CFG_0_RX_PR_CHECK_EN_SHIFT 22
#घोषणा CFG_0_NIB_MODE_MASK 0x800000
#घोषणा CFG_0_NIB_MODE_SHIFT 23
#घोषणा CFG_0_TX_IFG_NIB_MASK 0xF000000
#घोषणा CFG_0_TX_IFG_NIB_SHIFT 24
#घोषणा CFG_0_TX_PR_LEN_MASK 0xF0000000
#घोषणा CFG_0_TX_PR_LEN_SHIFT 28

/* Gbps Eth MAC Configuration 1 रेजिस्टर masks and shअगरts */
#घोषणा CFG_1_OCTET_0_MASK 0x000000FF
#घोषणा CFG_1_OCTET_0_SHIFT 0
#घोषणा CFG_1_OCTET_1_MASK 0x0000FF00
#घोषणा CFG_1_OCTET_1_SHIFT 8
#घोषणा CFG_1_OCTET_2_MASK 0x00FF0000
#घोषणा CFG_1_OCTET_2_SHIFT 16
#घोषणा CFG_1_OCTET_3_MASK 0xFF000000
#घोषणा CFG_1_OCTET_3_SHIFT 24

/* Gbps Eth MAC Configuration 2 रेजिस्टर masks and shअगरts */
#घोषणा CFG_2_OCTET_4_MASK 0x000000FF
#घोषणा CFG_2_OCTET_4_SHIFT 0
#घोषणा CFG_2_OCTET_5_MASK 0x0000FF00
#घोषणा CFG_2_OCTET_5_SHIFT 8
#घोषणा CFG_2_DISK_MC_MASK 0x00100000
#घोषणा CFG_2_DISK_MC_SHIFT 20
#घोषणा CFG_2_DISK_BC_MASK 0x00200000
#घोषणा CFG_2_DISK_BC_SHIFT 21
#घोषणा CFG_2_DISK_DA_MASK 0x00400000
#घोषणा CFG_2_DISK_DA_SHIFT 22
#घोषणा CFG_2_STAT_EN_MASK 0x3000000
#घोषणा CFG_2_STAT_EN_SHIFT 24
#घोषणा CFG_2_TRANSMIT_FLUSH_EN_MASK 0x80000000
#घोषणा CFG_2_TRANSMIT_FLUSH_EN_SHIFT 31

/* Gbps Eth MAC Configuration 3 रेजिस्टर masks and shअगरts */
#घोषणा CFG_3_TM_HD_MODE_MASK 0x1
#घोषणा CFG_3_TM_HD_MODE_SHIFT 0
#घोषणा CFG_3_RX_CBFC_EN_MASK 0x2
#घोषणा CFG_3_RX_CBFC_EN_SHIFT 1
#घोषणा CFG_3_RX_CBFC_REसूची_EN_MASK 0x4
#घोषणा CFG_3_RX_CBFC_REसूची_EN_SHIFT 2
#घोषणा CFG_3_REसूचीECT_CBFC_SEL_MASK 0x18
#घोषणा CFG_3_REसूचीECT_CBFC_SEL_SHIFT 3
#घोषणा CFG_3_CF_DROP_MASK 0x20
#घोषणा CFG_3_CF_DROP_SHIFT 5
#घोषणा CFG_3_CF_TIMEOUT_MASK 0x3C0
#घोषणा CFG_3_CF_TIMEOUT_SHIFT 6
#घोषणा CFG_3_RX_IFG_TH_MASK 0x7C00
#घोषणा CFG_3_RX_IFG_TH_SHIFT 10
#घोषणा CFG_3_TX_CBFC_EN_MASK 0x8000
#घोषणा CFG_3_TX_CBFC_EN_SHIFT 15
#घोषणा CFG_3_MAX_LEN_MASK 0x3FFF0000
#घोषणा CFG_3_MAX_LEN_SHIFT 16
#घोषणा CFG_3_EXT_OOB_CBFC_SEL_MASK 0xC0000000
#घोषणा CFG_3_EXT_OOB_CBFC_SEL_SHIFT 30

/* GE MAC, PCS reset control रेजिस्टर masks and shअगरts */
#घोषणा RST_SPCS_MASK 0x1
#घोषणा RST_SPCS_SHIFT 0
#घोषणा RST_GMAC_0_MASK 0x100
#घोषणा RST_GMAC_0_SHIFT 8

/* Tx phase sync FIFO control रेजिस्टर masks and shअगरts */
#घोषणा PHASE_FIFO_CTL_RST_MASK 0x1
#घोषणा PHASE_FIFO_CTL_RST_SHIFT 0
#घोषणा PHASE_FIFO_CTL_INIT_MASK 0x2
#घोषणा PHASE_FIFO_CTL_INIT_SHIFT 1

/**
 * काष्ठा nps_enet_priv - Storage of ENET's निजी inक्रमmation.
 * @regs_base:      Base address of ENET memory-mapped control रेजिस्टरs.
 * @irq:            For RX/TX IRQ number.
 * @tx_skb:         socket buffer of sent frame.
 * @napi:           Structure क्रम NAPI.
 */
काष्ठा nps_enet_priv अणु
	व्योम __iomem *regs_base;
	s32 irq;
	काष्ठा sk_buff *tx_skb;
	काष्ठा napi_काष्ठा napi;
	u32 ge_mac_cfg_2_value;
	u32 ge_mac_cfg_3_value;
पूर्ण;

/**
 * nps_enet_reg_set - Sets ENET रेजिस्टर with provided value.
 * @priv:       Poपूर्णांकer to EZchip ENET निजी data काष्ठाure.
 * @reg:        Register offset from base address.
 * @value:      Value to set in रेजिस्टर.
 */
अटल अंतरभूत व्योम nps_enet_reg_set(काष्ठा nps_enet_priv *priv,
				    s32 reg, s32 value)
अणु
	ioग_लिखो32be(value, priv->regs_base + reg);
पूर्ण

/**
 * nps_enet_reg_get - Gets value of specअगरied ENET रेजिस्टर.
 * @priv:       Poपूर्णांकer to EZchip ENET निजी data काष्ठाure.
 * @reg:        Register offset from base address.
 *
 * वापसs:     Value of requested रेजिस्टर.
 */
अटल अंतरभूत u32 nps_enet_reg_get(काष्ठा nps_enet_priv *priv, s32 reg)
अणु
	वापस ioपढ़ो32be(priv->regs_base + reg);
पूर्ण

#पूर्ण_अगर /* _NPS_ENET_H */
