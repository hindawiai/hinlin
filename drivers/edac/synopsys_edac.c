<शैली गुरु>
/*
 * Synopsys DDR ECC Driver
 * This driver is based on ppc4xx_edac.c drivers
 *
 * Copyright (C) 2012 - 2014 Xilinx, Inc.
 *
 * This program is मुक्त software: you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details
 */

#समावेश <linux/edac.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश "edac_module.h"

/* Number of cs_rows needed per memory controller */
#घोषणा SYNPS_EDAC_NR_CSROWS		1

/* Number of channels per memory controller */
#घोषणा SYNPS_EDAC_NR_CHANS		1

/* Granularity of reported error in bytes */
#घोषणा SYNPS_EDAC_ERR_GRAIN		1

#घोषणा SYNPS_EDAC_MSG_SIZE		256

#घोषणा SYNPS_EDAC_MOD_STRING		"synps_edac"
#घोषणा SYNPS_EDAC_MOD_VER		"1"

/* Synopsys DDR memory controller रेजिस्टरs that are relevant to ECC */
#घोषणा CTRL_OFST			0x0
#घोषणा T_ZQ_OFST			0xA4

/* ECC control रेजिस्टर */
#घोषणा ECC_CTRL_OFST			0xC4
/* ECC log रेजिस्टर */
#घोषणा CE_LOG_OFST			0xC8
/* ECC address रेजिस्टर */
#घोषणा CE_ADDR_OFST			0xCC
/* ECC data[31:0] रेजिस्टर */
#घोषणा CE_DATA_31_0_OFST		0xD0

/* Uncorrectable error info रेजिस्टरs */
#घोषणा UE_LOG_OFST			0xDC
#घोषणा UE_ADDR_OFST			0xE0
#घोषणा UE_DATA_31_0_OFST		0xE4

#घोषणा STAT_OFST			0xF0
#घोषणा SCRUB_OFST			0xF4

/* Control रेजिस्टर bit field definitions */
#घोषणा CTRL_BW_MASK			0xC
#घोषणा CTRL_BW_SHIFT			2

#घोषणा DDRCTL_WDTH_16			1
#घोषणा DDRCTL_WDTH_32			0

/* ZQ रेजिस्टर bit field definitions */
#घोषणा T_ZQ_DDRMODE_MASK		0x2

/* ECC control रेजिस्टर bit field definitions */
#घोषणा ECC_CTRL_CLR_CE_ERR		0x2
#घोषणा ECC_CTRL_CLR_UE_ERR		0x1

/* ECC correctable/uncorrectable error log रेजिस्टर definitions */
#घोषणा LOG_VALID			0x1
#घोषणा CE_LOG_BITPOS_MASK		0xFE
#घोषणा CE_LOG_BITPOS_SHIFT		1

/* ECC correctable/uncorrectable error address रेजिस्टर definitions */
#घोषणा ADDR_COL_MASK			0xFFF
#घोषणा ADDR_ROW_MASK			0xFFFF000
#घोषणा ADDR_ROW_SHIFT			12
#घोषणा ADDR_BANK_MASK			0x70000000
#घोषणा ADDR_BANK_SHIFT			28

/* ECC statistic रेजिस्टर definitions */
#घोषणा STAT_UECNT_MASK			0xFF
#घोषणा STAT_CECNT_MASK			0xFF00
#घोषणा STAT_CECNT_SHIFT		8

/* ECC scrub रेजिस्टर definitions */
#घोषणा SCRUB_MODE_MASK			0x7
#घोषणा SCRUB_MODE_SECDED		0x4

/* DDR ECC Quirks */
#घोषणा DDR_ECC_INTR_SUPPORT		BIT(0)
#घोषणा DDR_ECC_DATA_POISON_SUPPORT	BIT(1)

/* ZynqMP Enhanced DDR memory controller रेजिस्टरs that are relevant to ECC */
/* ECC Configuration Registers */
#घोषणा ECC_CFG0_OFST			0x70
#घोषणा ECC_CFG1_OFST			0x74

/* ECC Status Register */
#घोषणा ECC_STAT_OFST			0x78

/* ECC Clear Register */
#घोषणा ECC_CLR_OFST			0x7C

/* ECC Error count Register */
#घोषणा ECC_ERRCNT_OFST			0x80

/* ECC Corrected Error Address Register */
#घोषणा ECC_CEADDR0_OFST		0x84
#घोषणा ECC_CEADDR1_OFST		0x88

/* ECC Syndrome Registers */
#घोषणा ECC_CSYND0_OFST			0x8C
#घोषणा ECC_CSYND1_OFST			0x90
#घोषणा ECC_CSYND2_OFST			0x94

/* ECC Bit Mask0 Address Register */
#घोषणा ECC_BITMASK0_OFST		0x98
#घोषणा ECC_BITMASK1_OFST		0x9C
#घोषणा ECC_BITMASK2_OFST		0xA0

/* ECC UnCorrected Error Address Register */
#घोषणा ECC_UEADDR0_OFST		0xA4
#घोषणा ECC_UEADDR1_OFST		0xA8

/* ECC Syndrome Registers */
#घोषणा ECC_UESYND0_OFST		0xAC
#घोषणा ECC_UESYND1_OFST		0xB0
#घोषणा ECC_UESYND2_OFST		0xB4

/* ECC Poison Address Reg */
#घोषणा ECC_POISON0_OFST		0xB8
#घोषणा ECC_POISON1_OFST		0xBC

#घोषणा ECC_ADDRMAP0_OFFSET		0x200

/* Control रेजिस्टर bitfield definitions */
#घोषणा ECC_CTRL_BUSWIDTH_MASK		0x3000
#घोषणा ECC_CTRL_BUSWIDTH_SHIFT		12
#घोषणा ECC_CTRL_CLR_CE_ERRCNT		BIT(2)
#घोषणा ECC_CTRL_CLR_UE_ERRCNT		BIT(3)

/* DDR Control Register width definitions  */
#घोषणा DDRCTL_EWDTH_16			2
#घोषणा DDRCTL_EWDTH_32			1
#घोषणा DDRCTL_EWDTH_64			0

/* ECC status रेजिस्टर definitions */
#घोषणा ECC_STAT_UECNT_MASK		0xF0000
#घोषणा ECC_STAT_UECNT_SHIFT		16
#घोषणा ECC_STAT_CECNT_MASK		0xF00
#घोषणा ECC_STAT_CECNT_SHIFT		8
#घोषणा ECC_STAT_BITNUM_MASK		0x7F

/* DDR QOS Interrupt रेजिस्टर definitions */
#घोषणा DDR_QOS_IRQ_STAT_OFST		0x20200
#घोषणा DDR_QOSUE_MASK			0x4
#घोषणा	DDR_QOSCE_MASK			0x2
#घोषणा	ECC_CE_UE_INTR_MASK		0x6
#घोषणा DDR_QOS_IRQ_EN_OFST		0x20208
#घोषणा DDR_QOS_IRQ_DB_OFST		0x2020C

/* ECC Corrected Error Register Mask and Shअगरts*/
#घोषणा ECC_CEADDR0_RW_MASK		0x3FFFF
#घोषणा ECC_CEADDR0_RNK_MASK		BIT(24)
#घोषणा ECC_CEADDR1_BNKGRP_MASK		0x3000000
#घोषणा ECC_CEADDR1_BNKNR_MASK		0x70000
#घोषणा ECC_CEADDR1_BLKNR_MASK		0xFFF
#घोषणा ECC_CEADDR1_BNKGRP_SHIFT	24
#घोषणा ECC_CEADDR1_BNKNR_SHIFT		16

/* ECC Poison रेजिस्टर shअगरts */
#घोषणा ECC_POISON0_RANK_SHIFT		24
#घोषणा ECC_POISON0_RANK_MASK		BIT(24)
#घोषणा ECC_POISON0_COLUMN_SHIFT	0
#घोषणा ECC_POISON0_COLUMN_MASK		0xFFF
#घोषणा ECC_POISON1_BG_SHIFT		28
#घोषणा ECC_POISON1_BG_MASK		0x30000000
#घोषणा ECC_POISON1_BANKNR_SHIFT	24
#घोषणा ECC_POISON1_BANKNR_MASK		0x7000000
#घोषणा ECC_POISON1_ROW_SHIFT		0
#घोषणा ECC_POISON1_ROW_MASK		0x3FFFF

/* DDR Memory type defines */
#घोषणा MEM_TYPE_DDR3			0x1
#घोषणा MEM_TYPE_LPDDR3			0x8
#घोषणा MEM_TYPE_DDR2			0x4
#घोषणा MEM_TYPE_DDR4			0x10
#घोषणा MEM_TYPE_LPDDR4			0x20

/* DDRC Software control रेजिस्टर */
#घोषणा DDRC_SWCTL			0x320

/* DDRC ECC CE & UE poison mask */
#घोषणा ECC_CEPOISON_MASK		0x3
#घोषणा ECC_UEPOISON_MASK		0x1

/* DDRC Device config masks */
#घोषणा DDRC_MSTR_CFG_MASK		0xC0000000
#घोषणा DDRC_MSTR_CFG_SHIFT		30
#घोषणा DDRC_MSTR_CFG_X4_MASK		0x0
#घोषणा DDRC_MSTR_CFG_X8_MASK		0x1
#घोषणा DDRC_MSTR_CFG_X16_MASK		0x2
#घोषणा DDRC_MSTR_CFG_X32_MASK		0x3

#घोषणा DDR_MAX_ROW_SHIFT		18
#घोषणा DDR_MAX_COL_SHIFT		14
#घोषणा DDR_MAX_BANK_SHIFT		3
#घोषणा DDR_MAX_BANKGRP_SHIFT		2

#घोषणा ROW_MAX_VAL_MASK		0xF
#घोषणा COL_MAX_VAL_MASK		0xF
#घोषणा BANK_MAX_VAL_MASK		0x1F
#घोषणा BANKGRP_MAX_VAL_MASK		0x1F
#घोषणा RANK_MAX_VAL_MASK		0x1F

#घोषणा ROW_B0_BASE			6
#घोषणा ROW_B1_BASE			7
#घोषणा ROW_B2_BASE			8
#घोषणा ROW_B3_BASE			9
#घोषणा ROW_B4_BASE			10
#घोषणा ROW_B5_BASE			11
#घोषणा ROW_B6_BASE			12
#घोषणा ROW_B7_BASE			13
#घोषणा ROW_B8_BASE			14
#घोषणा ROW_B9_BASE			15
#घोषणा ROW_B10_BASE			16
#घोषणा ROW_B11_BASE			17
#घोषणा ROW_B12_BASE			18
#घोषणा ROW_B13_BASE			19
#घोषणा ROW_B14_BASE			20
#घोषणा ROW_B15_BASE			21
#घोषणा ROW_B16_BASE			22
#घोषणा ROW_B17_BASE			23

#घोषणा COL_B2_BASE			2
#घोषणा COL_B3_BASE			3
#घोषणा COL_B4_BASE			4
#घोषणा COL_B5_BASE			5
#घोषणा COL_B6_BASE			6
#घोषणा COL_B7_BASE			7
#घोषणा COL_B8_BASE			8
#घोषणा COL_B9_BASE			9
#घोषणा COL_B10_BASE			10
#घोषणा COL_B11_BASE			11
#घोषणा COL_B12_BASE			12
#घोषणा COL_B13_BASE			13

#घोषणा BANK_B0_BASE			2
#घोषणा BANK_B1_BASE			3
#घोषणा BANK_B2_BASE			4

#घोषणा BANKGRP_B0_BASE			2
#घोषणा BANKGRP_B1_BASE			3

#घोषणा RANK_B0_BASE			6

/**
 * काष्ठा ecc_error_info - ECC error log inक्रमmation.
 * @row:	Row number.
 * @col:	Column number.
 * @bank:	Bank number.
 * @bitpos:	Bit position.
 * @data:	Data causing the error.
 * @bankgrpnr:	Bank group number.
 * @blknr:	Block number.
 */
काष्ठा ecc_error_info अणु
	u32 row;
	u32 col;
	u32 bank;
	u32 bitpos;
	u32 data;
	u32 bankgrpnr;
	u32 blknr;
पूर्ण;

/**
 * काष्ठा synps_ecc_status - ECC status inक्रमmation to report.
 * @ce_cnt:	Correctable error count.
 * @ue_cnt:	Uncorrectable error count.
 * @ceinfo:	Correctable error log inक्रमmation.
 * @ueinfo:	Uncorrectable error log inक्रमmation.
 */
काष्ठा synps_ecc_status अणु
	u32 ce_cnt;
	u32 ue_cnt;
	काष्ठा ecc_error_info ceinfo;
	काष्ठा ecc_error_info ueinfo;
पूर्ण;

/**
 * काष्ठा synps_edac_priv - DDR memory controller निजी instance data.
 * @baseaddr:		Base address of the DDR controller.
 * @message:		Buffer क्रम framing the event specअगरic info.
 * @stat:		ECC status inक्रमmation.
 * @p_data:		Platक्रमm data.
 * @ce_cnt:		Correctable Error count.
 * @ue_cnt:		Uncorrectable Error count.
 * @poison_addr:	Data poison address.
 * @row_shअगरt:		Bit shअगरts क्रम row bit.
 * @col_shअगरt:		Bit shअगरts क्रम column bit.
 * @bank_shअगरt:		Bit shअगरts क्रम bank bit.
 * @bankgrp_shअगरt:	Bit shअगरts क्रम bank group bit.
 * @rank_shअगरt:		Bit shअगरts क्रम rank bit.
 */
काष्ठा synps_edac_priv अणु
	व्योम __iomem *baseaddr;
	अक्षर message[SYNPS_EDAC_MSG_SIZE];
	काष्ठा synps_ecc_status stat;
	स्थिर काष्ठा synps_platक्रमm_data *p_data;
	u32 ce_cnt;
	u32 ue_cnt;
#अगर_घोषित CONFIG_EDAC_DEBUG
	uदीर्घ poison_addr;
	u32 row_shअगरt[18];
	u32 col_shअगरt[14];
	u32 bank_shअगरt[3];
	u32 bankgrp_shअगरt[2];
	u32 rank_shअगरt[1];
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा synps_platक्रमm_data -  synps platक्रमm data काष्ठाure.
 * @get_error_info:	Get EDAC error info.
 * @get_mtype:		Get mtype.
 * @get_dtype:		Get dtype.
 * @get_ecc_state:	Get ECC state.
 * @quirks:		To dअगरferentiate IPs.
 */
काष्ठा synps_platक्रमm_data अणु
	पूर्णांक (*get_error_info)(काष्ठा synps_edac_priv *priv);
	क्रमागत mem_type (*get_mtype)(स्थिर व्योम __iomem *base);
	क्रमागत dev_type (*get_dtype)(स्थिर व्योम __iomem *base);
	bool (*get_ecc_state)(व्योम __iomem *base);
	पूर्णांक quirks;
पूर्ण;

/**
 * zynq_get_error_info - Get the current ECC error info.
 * @priv:	DDR memory controller निजी instance data.
 *
 * Return: one अगर there is no error, otherwise zero.
 */
अटल पूर्णांक zynq_get_error_info(काष्ठा synps_edac_priv *priv)
अणु
	काष्ठा synps_ecc_status *p;
	u32 regval, clearval = 0;
	व्योम __iomem *base;

	base = priv->baseaddr;
	p = &priv->stat;

	regval = पढ़ोl(base + STAT_OFST);
	अगर (!regval)
		वापस 1;

	p->ce_cnt = (regval & STAT_CECNT_MASK) >> STAT_CECNT_SHIFT;
	p->ue_cnt = regval & STAT_UECNT_MASK;

	regval = पढ़ोl(base + CE_LOG_OFST);
	अगर (!(p->ce_cnt && (regval & LOG_VALID)))
		जाओ ue_err;

	p->ceinfo.bitpos = (regval & CE_LOG_BITPOS_MASK) >> CE_LOG_BITPOS_SHIFT;
	regval = पढ़ोl(base + CE_ADDR_OFST);
	p->ceinfo.row = (regval & ADDR_ROW_MASK) >> ADDR_ROW_SHIFT;
	p->ceinfo.col = regval & ADDR_COL_MASK;
	p->ceinfo.bank = (regval & ADDR_BANK_MASK) >> ADDR_BANK_SHIFT;
	p->ceinfo.data = पढ़ोl(base + CE_DATA_31_0_OFST);
	edac_dbg(3, "CE bit position: %d data: %d\n", p->ceinfo.bitpos,
		 p->ceinfo.data);
	clearval = ECC_CTRL_CLR_CE_ERR;

ue_err:
	regval = पढ़ोl(base + UE_LOG_OFST);
	अगर (!(p->ue_cnt && (regval & LOG_VALID)))
		जाओ out;

	regval = पढ़ोl(base + UE_ADDR_OFST);
	p->ueinfo.row = (regval & ADDR_ROW_MASK) >> ADDR_ROW_SHIFT;
	p->ueinfo.col = regval & ADDR_COL_MASK;
	p->ueinfo.bank = (regval & ADDR_BANK_MASK) >> ADDR_BANK_SHIFT;
	p->ueinfo.data = पढ़ोl(base + UE_DATA_31_0_OFST);
	clearval |= ECC_CTRL_CLR_UE_ERR;

out:
	ग_लिखोl(clearval, base + ECC_CTRL_OFST);
	ग_लिखोl(0x0, base + ECC_CTRL_OFST);

	वापस 0;
पूर्ण

/**
 * zynqmp_get_error_info - Get the current ECC error info.
 * @priv:	DDR memory controller निजी instance data.
 *
 * Return: one अगर there is no error otherwise वापसs zero.
 */
अटल पूर्णांक zynqmp_get_error_info(काष्ठा synps_edac_priv *priv)
अणु
	काष्ठा synps_ecc_status *p;
	u32 regval, clearval = 0;
	व्योम __iomem *base;

	base = priv->baseaddr;
	p = &priv->stat;

	regval = पढ़ोl(base + ECC_STAT_OFST);
	अगर (!regval)
		वापस 1;

	p->ce_cnt = (regval & ECC_STAT_CECNT_MASK) >> ECC_STAT_CECNT_SHIFT;
	p->ue_cnt = (regval & ECC_STAT_UECNT_MASK) >> ECC_STAT_UECNT_SHIFT;
	अगर (!p->ce_cnt)
		जाओ ue_err;

	p->ceinfo.bitpos = (regval & ECC_STAT_BITNUM_MASK);

	regval = पढ़ोl(base + ECC_CEADDR0_OFST);
	p->ceinfo.row = (regval & ECC_CEADDR0_RW_MASK);
	regval = पढ़ोl(base + ECC_CEADDR1_OFST);
	p->ceinfo.bank = (regval & ECC_CEADDR1_BNKNR_MASK) >>
					ECC_CEADDR1_BNKNR_SHIFT;
	p->ceinfo.bankgrpnr = (regval &	ECC_CEADDR1_BNKGRP_MASK) >>
					ECC_CEADDR1_BNKGRP_SHIFT;
	p->ceinfo.blknr = (regval & ECC_CEADDR1_BLKNR_MASK);
	p->ceinfo.data = पढ़ोl(base + ECC_CSYND0_OFST);
	edac_dbg(2, "ECCCSYN0: 0x%08X ECCCSYN1: 0x%08X ECCCSYN2: 0x%08X\n",
		 पढ़ोl(base + ECC_CSYND0_OFST), पढ़ोl(base + ECC_CSYND1_OFST),
		 पढ़ोl(base + ECC_CSYND2_OFST));
ue_err:
	अगर (!p->ue_cnt)
		जाओ out;

	regval = पढ़ोl(base + ECC_UEADDR0_OFST);
	p->ueinfo.row = (regval & ECC_CEADDR0_RW_MASK);
	regval = पढ़ोl(base + ECC_UEADDR1_OFST);
	p->ueinfo.bankgrpnr = (regval & ECC_CEADDR1_BNKGRP_MASK) >>
					ECC_CEADDR1_BNKGRP_SHIFT;
	p->ueinfo.bank = (regval & ECC_CEADDR1_BNKNR_MASK) >>
					ECC_CEADDR1_BNKNR_SHIFT;
	p->ueinfo.blknr = (regval & ECC_CEADDR1_BLKNR_MASK);
	p->ueinfo.data = पढ़ोl(base + ECC_UESYND0_OFST);
out:
	clearval = ECC_CTRL_CLR_CE_ERR | ECC_CTRL_CLR_CE_ERRCNT;
	clearval |= ECC_CTRL_CLR_UE_ERR | ECC_CTRL_CLR_UE_ERRCNT;
	ग_लिखोl(clearval, base + ECC_CLR_OFST);
	ग_लिखोl(0x0, base + ECC_CLR_OFST);

	वापस 0;
पूर्ण

/**
 * handle_error - Handle Correctable and Uncorrectable errors.
 * @mci:	EDAC memory controller instance.
 * @p:		Synopsys ECC status काष्ठाure.
 *
 * Handles ECC correctable and uncorrectable errors.
 */
अटल व्योम handle_error(काष्ठा mem_ctl_info *mci, काष्ठा synps_ecc_status *p)
अणु
	काष्ठा synps_edac_priv *priv = mci->pvt_info;
	काष्ठा ecc_error_info *pinf;

	अगर (p->ce_cnt) अणु
		pinf = &p->ceinfo;
		अगर (priv->p_data->quirks & DDR_ECC_INTR_SUPPORT) अणु
			snम_लिखो(priv->message, SYNPS_EDAC_MSG_SIZE,
				 "DDR ECC error type:%s Row %d Bank %d BankGroup Number %d Block Number %d Bit Position: %d Data: 0x%08x",
				 "CE", pinf->row, pinf->bank,
				 pinf->bankgrpnr, pinf->blknr,
				 pinf->bitpos, pinf->data);
		पूर्ण अन्यथा अणु
			snम_लिखो(priv->message, SYNPS_EDAC_MSG_SIZE,
				 "DDR ECC error type:%s Row %d Bank %d Col %d Bit Position: %d Data: 0x%08x",
				 "CE", pinf->row, pinf->bank, pinf->col,
				 pinf->bitpos, pinf->data);
		पूर्ण

		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci,
				     p->ce_cnt, 0, 0, 0, 0, 0, -1,
				     priv->message, "");
	पूर्ण

	अगर (p->ue_cnt) अणु
		pinf = &p->ueinfo;
		अगर (priv->p_data->quirks & DDR_ECC_INTR_SUPPORT) अणु
			snम_लिखो(priv->message, SYNPS_EDAC_MSG_SIZE,
				 "DDR ECC error type :%s Row %d Bank %d BankGroup Number %d Block Number %d",
				 "UE", pinf->row, pinf->bank,
				 pinf->bankgrpnr, pinf->blknr);
		पूर्ण अन्यथा अणु
			snम_लिखो(priv->message, SYNPS_EDAC_MSG_SIZE,
				 "DDR ECC error type :%s Row %d Bank %d Col %d ",
				 "UE", pinf->row, pinf->bank, pinf->col);
		पूर्ण

		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci,
				     p->ue_cnt, 0, 0, 0, 0, 0, -1,
				     priv->message, "");
	पूर्ण

	स_रखो(p, 0, माप(*p));
पूर्ण

/**
 * पूर्णांकr_handler - Interrupt Handler क्रम ECC पूर्णांकerrupts.
 * @irq:        IRQ number.
 * @dev_id:     Device ID.
 *
 * Return: IRQ_NONE, अगर पूर्णांकerrupt not set or IRQ_HANDLED otherwise.
 */
अटल irqवापस_t पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	स्थिर काष्ठा synps_platक्रमm_data *p_data;
	काष्ठा mem_ctl_info *mci = dev_id;
	काष्ठा synps_edac_priv *priv;
	पूर्णांक status, regval;

	priv = mci->pvt_info;
	p_data = priv->p_data;

	regval = पढ़ोl(priv->baseaddr + DDR_QOS_IRQ_STAT_OFST);
	regval &= (DDR_QOSCE_MASK | DDR_QOSUE_MASK);
	अगर (!(regval & ECC_CE_UE_INTR_MASK))
		वापस IRQ_NONE;

	status = p_data->get_error_info(priv);
	अगर (status)
		वापस IRQ_NONE;

	priv->ce_cnt += priv->stat.ce_cnt;
	priv->ue_cnt += priv->stat.ue_cnt;
	handle_error(mci, &priv->stat);

	edac_dbg(3, "Total error count CE %d UE %d\n",
		 priv->ce_cnt, priv->ue_cnt);
	ग_लिखोl(regval, priv->baseaddr + DDR_QOS_IRQ_STAT_OFST);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * check_errors - Check controller क्रम ECC errors.
 * @mci:	EDAC memory controller instance.
 *
 * Check and post ECC errors. Called by the polling thपढ़ो.
 */
अटल व्योम check_errors(काष्ठा mem_ctl_info *mci)
अणु
	स्थिर काष्ठा synps_platक्रमm_data *p_data;
	काष्ठा synps_edac_priv *priv;
	पूर्णांक status;

	priv = mci->pvt_info;
	p_data = priv->p_data;

	status = p_data->get_error_info(priv);
	अगर (status)
		वापस;

	priv->ce_cnt += priv->stat.ce_cnt;
	priv->ue_cnt += priv->stat.ue_cnt;
	handle_error(mci, &priv->stat);

	edac_dbg(3, "Total error count CE %d UE %d\n",
		 priv->ce_cnt, priv->ue_cnt);
पूर्ण

/**
 * zynq_get_dtype - Return the controller memory width.
 * @base:	DDR memory controller base address.
 *
 * Get the EDAC device type width appropriate क्रम the current controller
 * configuration.
 *
 * Return: a device type width क्रमागतeration.
 */
अटल क्रमागत dev_type zynq_get_dtype(स्थिर व्योम __iomem *base)
अणु
	क्रमागत dev_type dt;
	u32 width;

	width = पढ़ोl(base + CTRL_OFST);
	width = (width & CTRL_BW_MASK) >> CTRL_BW_SHIFT;

	चयन (width) अणु
	हाल DDRCTL_WDTH_16:
		dt = DEV_X2;
		अवरोध;
	हाल DDRCTL_WDTH_32:
		dt = DEV_X4;
		अवरोध;
	शेष:
		dt = DEV_UNKNOWN;
	पूर्ण

	वापस dt;
पूर्ण

/**
 * zynqmp_get_dtype - Return the controller memory width.
 * @base:	DDR memory controller base address.
 *
 * Get the EDAC device type width appropriate क्रम the current controller
 * configuration.
 *
 * Return: a device type width क्रमागतeration.
 */
अटल क्रमागत dev_type zynqmp_get_dtype(स्थिर व्योम __iomem *base)
अणु
	क्रमागत dev_type dt;
	u32 width;

	width = पढ़ोl(base + CTRL_OFST);
	width = (width & ECC_CTRL_BUSWIDTH_MASK) >> ECC_CTRL_BUSWIDTH_SHIFT;
	चयन (width) अणु
	हाल DDRCTL_EWDTH_16:
		dt = DEV_X2;
		अवरोध;
	हाल DDRCTL_EWDTH_32:
		dt = DEV_X4;
		अवरोध;
	हाल DDRCTL_EWDTH_64:
		dt = DEV_X8;
		अवरोध;
	शेष:
		dt = DEV_UNKNOWN;
	पूर्ण

	वापस dt;
पूर्ण

/**
 * zynq_get_ecc_state - Return the controller ECC enable/disable status.
 * @base:	DDR memory controller base address.
 *
 * Get the ECC enable/disable status of the controller.
 *
 * Return: true अगर enabled, otherwise false.
 */
अटल bool zynq_get_ecc_state(व्योम __iomem *base)
अणु
	क्रमागत dev_type dt;
	u32 ecctype;

	dt = zynq_get_dtype(base);
	अगर (dt == DEV_UNKNOWN)
		वापस false;

	ecctype = पढ़ोl(base + SCRUB_OFST) & SCRUB_MODE_MASK;
	अगर ((ecctype == SCRUB_MODE_SECDED) && (dt == DEV_X2))
		वापस true;

	वापस false;
पूर्ण

/**
 * zynqmp_get_ecc_state - Return the controller ECC enable/disable status.
 * @base:	DDR memory controller base address.
 *
 * Get the ECC enable/disable status क्रम the controller.
 *
 * Return: a ECC status boolean i.e true/false - enabled/disabled.
 */
अटल bool zynqmp_get_ecc_state(व्योम __iomem *base)
अणु
	क्रमागत dev_type dt;
	u32 ecctype;

	dt = zynqmp_get_dtype(base);
	अगर (dt == DEV_UNKNOWN)
		वापस false;

	ecctype = पढ़ोl(base + ECC_CFG0_OFST) & SCRUB_MODE_MASK;
	अगर ((ecctype == SCRUB_MODE_SECDED) &&
	    ((dt == DEV_X2) || (dt == DEV_X4) || (dt == DEV_X8)))
		वापस true;

	वापस false;
पूर्ण

/**
 * get_memsize - Read the size of the attached memory device.
 *
 * Return: the memory size in bytes.
 */
अटल u32 get_memsize(व्योम)
अणु
	काष्ठा sysinfo inf;

	si_meminfo(&inf);

	वापस inf.totalram * inf.mem_unit;
पूर्ण

/**
 * zynq_get_mtype - Return the controller memory type.
 * @base:	Synopsys ECC status काष्ठाure.
 *
 * Get the EDAC memory type appropriate क्रम the current controller
 * configuration.
 *
 * Return: a memory type क्रमागतeration.
 */
अटल क्रमागत mem_type zynq_get_mtype(स्थिर व्योम __iomem *base)
अणु
	क्रमागत mem_type mt;
	u32 memtype;

	memtype = पढ़ोl(base + T_ZQ_OFST);

	अगर (memtype & T_ZQ_DDRMODE_MASK)
		mt = MEM_DDR3;
	अन्यथा
		mt = MEM_DDR2;

	वापस mt;
पूर्ण

/**
 * zynqmp_get_mtype - Returns controller memory type.
 * @base:	Synopsys ECC status काष्ठाure.
 *
 * Get the EDAC memory type appropriate क्रम the current controller
 * configuration.
 *
 * Return: a memory type क्रमागतeration.
 */
अटल क्रमागत mem_type zynqmp_get_mtype(स्थिर व्योम __iomem *base)
अणु
	क्रमागत mem_type mt;
	u32 memtype;

	memtype = पढ़ोl(base + CTRL_OFST);

	अगर ((memtype & MEM_TYPE_DDR3) || (memtype & MEM_TYPE_LPDDR3))
		mt = MEM_DDR3;
	अन्यथा अगर (memtype & MEM_TYPE_DDR2)
		mt = MEM_RDDR2;
	अन्यथा अगर ((memtype & MEM_TYPE_LPDDR4) || (memtype & MEM_TYPE_DDR4))
		mt = MEM_DDR4;
	अन्यथा
		mt = MEM_EMPTY;

	वापस mt;
पूर्ण

/**
 * init_csrows - Initialize the csrow data.
 * @mci:	EDAC memory controller instance.
 *
 * Initialize the chip select rows associated with the EDAC memory
 * controller instance.
 */
अटल व्योम init_csrows(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा synps_edac_priv *priv = mci->pvt_info;
	स्थिर काष्ठा synps_platक्रमm_data *p_data;
	काष्ठा csrow_info *csi;
	काष्ठा dimm_info *dimm;
	u32 size, row;
	पूर्णांक j;

	p_data = priv->p_data;

	क्रम (row = 0; row < mci->nr_csrows; row++) अणु
		csi = mci->csrows[row];
		size = get_memsize();

		क्रम (j = 0; j < csi->nr_channels; j++) अणु
			dimm		= csi->channels[j]->dimm;
			dimm->edac_mode	= EDAC_FLAG_SECDED;
			dimm->mtype	= p_data->get_mtype(priv->baseaddr);
			dimm->nr_pages	= (size >> PAGE_SHIFT) / csi->nr_channels;
			dimm->grain	= SYNPS_EDAC_ERR_GRAIN;
			dimm->dtype	= p_data->get_dtype(priv->baseaddr);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mc_init - Initialize one driver instance.
 * @mci:	EDAC memory controller instance.
 * @pdev:	platक्रमm device.
 *
 * Perक्रमm initialization of the EDAC memory controller instance and
 * related driver-निजी data associated with the memory controller the
 * instance is bound to.
 */
अटल व्योम mc_init(काष्ठा mem_ctl_info *mci, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा synps_edac_priv *priv;

	mci->pdev = &pdev->dev;
	priv = mci->pvt_info;
	platक्रमm_set_drvdata(pdev, mci);

	/* Initialize controller capabilities and configuration */
	mci->mtype_cap = MEM_FLAG_DDR3 | MEM_FLAG_DDR2;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->scrub_cap = SCRUB_HW_SRC;
	mci->scrub_mode = SCRUB_NONE;

	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->ctl_name = "synps_ddr_controller";
	mci->dev_name = SYNPS_EDAC_MOD_STRING;
	mci->mod_name = SYNPS_EDAC_MOD_VER;

	अगर (priv->p_data->quirks & DDR_ECC_INTR_SUPPORT) अणु
		edac_op_state = EDAC_OPSTATE_INT;
	पूर्ण अन्यथा अणु
		edac_op_state = EDAC_OPSTATE_POLL;
		mci->edac_check = check_errors;
	पूर्ण

	mci->ctl_page_to_phys = शून्य;

	init_csrows(mci);
पूर्ण

अटल व्योम enable_पूर्णांकr(काष्ठा synps_edac_priv *priv)
अणु
	/* Enable UE/CE Interrupts */
	ग_लिखोl(DDR_QOSUE_MASK | DDR_QOSCE_MASK,
			priv->baseaddr + DDR_QOS_IRQ_EN_OFST);
पूर्ण

अटल व्योम disable_पूर्णांकr(काष्ठा synps_edac_priv *priv)
अणु
	/* Disable UE/CE Interrupts */
	ग_लिखोl(DDR_QOSUE_MASK | DDR_QOSCE_MASK,
			priv->baseaddr + DDR_QOS_IRQ_DB_OFST);
पूर्ण

अटल पूर्णांक setup_irq(काष्ठा mem_ctl_info *mci,
		     काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा synps_edac_priv *priv = mci->pvt_info;
	पूर्णांक ret, irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "No IRQ %d in DT\n", irq);
		वापस irq;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, पूर्णांकr_handler,
			       0, dev_name(&pdev->dev), mci);
	अगर (ret < 0) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC, "Failed to request IRQ\n");
		वापस ret;
	पूर्ण

	enable_पूर्णांकr(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा synps_platक्रमm_data zynq_edac_def = अणु
	.get_error_info	= zynq_get_error_info,
	.get_mtype	= zynq_get_mtype,
	.get_dtype	= zynq_get_dtype,
	.get_ecc_state	= zynq_get_ecc_state,
	.quirks		= 0,
पूर्ण;

अटल स्थिर काष्ठा synps_platक्रमm_data zynqmp_edac_def = अणु
	.get_error_info	= zynqmp_get_error_info,
	.get_mtype	= zynqmp_get_mtype,
	.get_dtype	= zynqmp_get_dtype,
	.get_ecc_state	= zynqmp_get_ecc_state,
	.quirks         = (DDR_ECC_INTR_SUPPORT
#अगर_घोषित CONFIG_EDAC_DEBUG
			  | DDR_ECC_DATA_POISON_SUPPORT
#पूर्ण_अगर
			  ),
पूर्ण;

अटल स्थिर काष्ठा of_device_id synps_edac_match[] = अणु
	अणु
		.compatible = "xlnx,zynq-ddrc-a05",
		.data = (व्योम *)&zynq_edac_def
	पूर्ण,
	अणु
		.compatible = "xlnx,zynqmp-ddrc-2.40a",
		.data = (व्योम *)&zynqmp_edac_def
	पूर्ण,
	अणु
		/* end of table */
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, synps_edac_match);

#अगर_घोषित CONFIG_EDAC_DEBUG
#घोषणा to_mci(k) container_of(k, काष्ठा mem_ctl_info, dev)

/**
 * ddr_poison_setup -	Update poison रेजिस्टरs.
 * @priv:		DDR memory controller निजी instance data.
 *
 * Update poison रेजिस्टरs as per DDR mapping.
 * Return: none.
 */
अटल व्योम ddr_poison_setup(काष्ठा synps_edac_priv *priv)
अणु
	पूर्णांक col = 0, row = 0, bank = 0, bankgrp = 0, rank = 0, regval;
	पूर्णांक index;
	uदीर्घ hअगर_addr = 0;

	hअगर_addr = priv->poison_addr >> 3;

	क्रम (index = 0; index < DDR_MAX_ROW_SHIFT; index++) अणु
		अगर (priv->row_shअगरt[index])
			row |= (((hअगर_addr >> priv->row_shअगरt[index]) &
						BIT(0)) << index);
		अन्यथा
			अवरोध;
	पूर्ण

	क्रम (index = 0; index < DDR_MAX_COL_SHIFT; index++) अणु
		अगर (priv->col_shअगरt[index] || index < 3)
			col |= (((hअगर_addr >> priv->col_shअगरt[index]) &
						BIT(0)) << index);
		अन्यथा
			अवरोध;
	पूर्ण

	क्रम (index = 0; index < DDR_MAX_BANK_SHIFT; index++) अणु
		अगर (priv->bank_shअगरt[index])
			bank |= (((hअगर_addr >> priv->bank_shअगरt[index]) &
						BIT(0)) << index);
		अन्यथा
			अवरोध;
	पूर्ण

	क्रम (index = 0; index < DDR_MAX_BANKGRP_SHIFT; index++) अणु
		अगर (priv->bankgrp_shअगरt[index])
			bankgrp |= (((hअगर_addr >> priv->bankgrp_shअगरt[index])
						& BIT(0)) << index);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (priv->rank_shअगरt[0])
		rank = (hअगर_addr >> priv->rank_shअगरt[0]) & BIT(0);

	regval = (rank << ECC_POISON0_RANK_SHIFT) & ECC_POISON0_RANK_MASK;
	regval |= (col << ECC_POISON0_COLUMN_SHIFT) & ECC_POISON0_COLUMN_MASK;
	ग_लिखोl(regval, priv->baseaddr + ECC_POISON0_OFST);

	regval = (bankgrp << ECC_POISON1_BG_SHIFT) & ECC_POISON1_BG_MASK;
	regval |= (bank << ECC_POISON1_BANKNR_SHIFT) & ECC_POISON1_BANKNR_MASK;
	regval |= (row << ECC_POISON1_ROW_SHIFT) & ECC_POISON1_ROW_MASK;
	ग_लिखोl(regval, priv->baseaddr + ECC_POISON1_OFST);
पूर्ण

अटल sमाप_प्रकार inject_data_error_show(काष्ठा device *dev,
				      काष्ठा device_attribute *mattr,
				      अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा synps_edac_priv *priv = mci->pvt_info;

	वापस प्र_लिखो(data, "Poison0 Addr: 0x%08x\n\rPoison1 Addr: 0x%08x\n\r"
			"Error injection Address: 0x%lx\n\r",
			पढ़ोl(priv->baseaddr + ECC_POISON0_OFST),
			पढ़ोl(priv->baseaddr + ECC_POISON1_OFST),
			priv->poison_addr);
पूर्ण

अटल sमाप_प्रकार inject_data_error_store(काष्ठा device *dev,
				       काष्ठा device_attribute *mattr,
				       स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा synps_edac_priv *priv = mci->pvt_info;

	अगर (kम_से_अदीर्घ(data, 0, &priv->poison_addr))
		वापस -EINVAL;

	ddr_poison_setup(priv);

	वापस count;
पूर्ण

अटल sमाप_प्रकार inject_data_poison_show(काष्ठा device *dev,
				       काष्ठा device_attribute *mattr,
				       अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा synps_edac_priv *priv = mci->pvt_info;

	वापस प्र_लिखो(data, "Data Poisoning: %s\n\r",
			(((पढ़ोl(priv->baseaddr + ECC_CFG1_OFST)) & 0x3) == 0x3)
			? ("Correctable Error") : ("UnCorrectable Error"));
पूर्ण

अटल sमाप_प्रकार inject_data_poison_store(काष्ठा device *dev,
					काष्ठा device_attribute *mattr,
					स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा synps_edac_priv *priv = mci->pvt_info;

	ग_लिखोl(0, priv->baseaddr + DDRC_SWCTL);
	अगर (म_भेदन(data, "CE", 2) == 0)
		ग_लिखोl(ECC_CEPOISON_MASK, priv->baseaddr + ECC_CFG1_OFST);
	अन्यथा
		ग_लिखोl(ECC_UEPOISON_MASK, priv->baseaddr + ECC_CFG1_OFST);
	ग_लिखोl(1, priv->baseaddr + DDRC_SWCTL);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(inject_data_error);
अटल DEVICE_ATTR_RW(inject_data_poison);

अटल पूर्णांक edac_create_sysfs_attributes(काष्ठा mem_ctl_info *mci)
अणु
	पूर्णांक rc;

	rc = device_create_file(&mci->dev, &dev_attr_inject_data_error);
	अगर (rc < 0)
		वापस rc;
	rc = device_create_file(&mci->dev, &dev_attr_inject_data_poison);
	अगर (rc < 0)
		वापस rc;
	वापस 0;
पूर्ण

अटल व्योम edac_हटाओ_sysfs_attributes(काष्ठा mem_ctl_info *mci)
अणु
	device_हटाओ_file(&mci->dev, &dev_attr_inject_data_error);
	device_हटाओ_file(&mci->dev, &dev_attr_inject_data_poison);
पूर्ण

अटल व्योम setup_row_address_map(काष्ठा synps_edac_priv *priv, u32 *addrmap)
अणु
	u32 addrmap_row_b2_10;
	पूर्णांक index;

	priv->row_shअगरt[0] = (addrmap[5] & ROW_MAX_VAL_MASK) + ROW_B0_BASE;
	priv->row_shअगरt[1] = ((addrmap[5] >> 8) &
			ROW_MAX_VAL_MASK) + ROW_B1_BASE;

	addrmap_row_b2_10 = (addrmap[5] >> 16) & ROW_MAX_VAL_MASK;
	अगर (addrmap_row_b2_10 != ROW_MAX_VAL_MASK) अणु
		क्रम (index = 2; index < 11; index++)
			priv->row_shअगरt[index] = addrmap_row_b2_10 +
				index + ROW_B0_BASE;

	पूर्ण अन्यथा अणु
		priv->row_shअगरt[2] = (addrmap[9] &
				ROW_MAX_VAL_MASK) + ROW_B2_BASE;
		priv->row_shअगरt[3] = ((addrmap[9] >> 8) &
				ROW_MAX_VAL_MASK) + ROW_B3_BASE;
		priv->row_shअगरt[4] = ((addrmap[9] >> 16) &
				ROW_MAX_VAL_MASK) + ROW_B4_BASE;
		priv->row_shअगरt[5] = ((addrmap[9] >> 24) &
				ROW_MAX_VAL_MASK) + ROW_B5_BASE;
		priv->row_shअगरt[6] = (addrmap[10] &
				ROW_MAX_VAL_MASK) + ROW_B6_BASE;
		priv->row_shअगरt[7] = ((addrmap[10] >> 8) &
				ROW_MAX_VAL_MASK) + ROW_B7_BASE;
		priv->row_shअगरt[8] = ((addrmap[10] >> 16) &
				ROW_MAX_VAL_MASK) + ROW_B8_BASE;
		priv->row_shअगरt[9] = ((addrmap[10] >> 24) &
				ROW_MAX_VAL_MASK) + ROW_B9_BASE;
		priv->row_shअगरt[10] = (addrmap[11] &
				ROW_MAX_VAL_MASK) + ROW_B10_BASE;
	पूर्ण

	priv->row_shअगरt[11] = (((addrmap[5] >> 24) & ROW_MAX_VAL_MASK) ==
				ROW_MAX_VAL_MASK) ? 0 : (((addrmap[5] >> 24) &
				ROW_MAX_VAL_MASK) + ROW_B11_BASE);
	priv->row_shअगरt[12] = ((addrmap[6] & ROW_MAX_VAL_MASK) ==
				ROW_MAX_VAL_MASK) ? 0 : ((addrmap[6] &
				ROW_MAX_VAL_MASK) + ROW_B12_BASE);
	priv->row_shअगरt[13] = (((addrmap[6] >> 8) & ROW_MAX_VAL_MASK) ==
				ROW_MAX_VAL_MASK) ? 0 : (((addrmap[6] >> 8) &
				ROW_MAX_VAL_MASK) + ROW_B13_BASE);
	priv->row_shअगरt[14] = (((addrmap[6] >> 16) & ROW_MAX_VAL_MASK) ==
				ROW_MAX_VAL_MASK) ? 0 : (((addrmap[6] >> 16) &
				ROW_MAX_VAL_MASK) + ROW_B14_BASE);
	priv->row_shअगरt[15] = (((addrmap[6] >> 24) & ROW_MAX_VAL_MASK) ==
				ROW_MAX_VAL_MASK) ? 0 : (((addrmap[6] >> 24) &
				ROW_MAX_VAL_MASK) + ROW_B15_BASE);
	priv->row_shअगरt[16] = ((addrmap[7] & ROW_MAX_VAL_MASK) ==
				ROW_MAX_VAL_MASK) ? 0 : ((addrmap[7] &
				ROW_MAX_VAL_MASK) + ROW_B16_BASE);
	priv->row_shअगरt[17] = (((addrmap[7] >> 8) & ROW_MAX_VAL_MASK) ==
				ROW_MAX_VAL_MASK) ? 0 : (((addrmap[7] >> 8) &
				ROW_MAX_VAL_MASK) + ROW_B17_BASE);
पूर्ण

अटल व्योम setup_column_address_map(काष्ठा synps_edac_priv *priv, u32 *addrmap)
अणु
	u32 width, memtype;
	पूर्णांक index;

	memtype = पढ़ोl(priv->baseaddr + CTRL_OFST);
	width = (memtype & ECC_CTRL_BUSWIDTH_MASK) >> ECC_CTRL_BUSWIDTH_SHIFT;

	priv->col_shअगरt[0] = 0;
	priv->col_shअगरt[1] = 1;
	priv->col_shअगरt[2] = (addrmap[2] & COL_MAX_VAL_MASK) + COL_B2_BASE;
	priv->col_shअगरt[3] = ((addrmap[2] >> 8) &
			COL_MAX_VAL_MASK) + COL_B3_BASE;
	priv->col_shअगरt[4] = (((addrmap[2] >> 16) & COL_MAX_VAL_MASK) ==
			COL_MAX_VAL_MASK) ? 0 : (((addrmap[2] >> 16) &
					COL_MAX_VAL_MASK) + COL_B4_BASE);
	priv->col_shअगरt[5] = (((addrmap[2] >> 24) & COL_MAX_VAL_MASK) ==
			COL_MAX_VAL_MASK) ? 0 : (((addrmap[2] >> 24) &
					COL_MAX_VAL_MASK) + COL_B5_BASE);
	priv->col_shअगरt[6] = ((addrmap[3] & COL_MAX_VAL_MASK) ==
			COL_MAX_VAL_MASK) ? 0 : ((addrmap[3] &
					COL_MAX_VAL_MASK) + COL_B6_BASE);
	priv->col_shअगरt[7] = (((addrmap[3] >> 8) & COL_MAX_VAL_MASK) ==
			COL_MAX_VAL_MASK) ? 0 : (((addrmap[3] >> 8) &
					COL_MAX_VAL_MASK) + COL_B7_BASE);
	priv->col_shअगरt[8] = (((addrmap[3] >> 16) & COL_MAX_VAL_MASK) ==
			COL_MAX_VAL_MASK) ? 0 : (((addrmap[3] >> 16) &
					COL_MAX_VAL_MASK) + COL_B8_BASE);
	priv->col_shअगरt[9] = (((addrmap[3] >> 24) & COL_MAX_VAL_MASK) ==
			COL_MAX_VAL_MASK) ? 0 : (((addrmap[3] >> 24) &
					COL_MAX_VAL_MASK) + COL_B9_BASE);
	अगर (width == DDRCTL_EWDTH_64) अणु
		अगर (memtype & MEM_TYPE_LPDDR3) अणु
			priv->col_shअगरt[10] = ((addrmap[4] &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				((addrmap[4] & COL_MAX_VAL_MASK) +
				 COL_B10_BASE);
			priv->col_shअगरt[11] = (((addrmap[4] >> 8) &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				(((addrmap[4] >> 8) & COL_MAX_VAL_MASK) +
				 COL_B11_BASE);
		पूर्ण अन्यथा अणु
			priv->col_shअगरt[11] = ((addrmap[4] &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				((addrmap[4] & COL_MAX_VAL_MASK) +
				 COL_B10_BASE);
			priv->col_shअगरt[13] = (((addrmap[4] >> 8) &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				(((addrmap[4] >> 8) & COL_MAX_VAL_MASK) +
				 COL_B11_BASE);
		पूर्ण
	पूर्ण अन्यथा अगर (width == DDRCTL_EWDTH_32) अणु
		अगर (memtype & MEM_TYPE_LPDDR3) अणु
			priv->col_shअगरt[10] = (((addrmap[3] >> 24) &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				(((addrmap[3] >> 24) & COL_MAX_VAL_MASK) +
				 COL_B9_BASE);
			priv->col_shअगरt[11] = ((addrmap[4] &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				((addrmap[4] & COL_MAX_VAL_MASK) +
				 COL_B10_BASE);
		पूर्ण अन्यथा अणु
			priv->col_shअगरt[11] = (((addrmap[3] >> 24) &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				(((addrmap[3] >> 24) & COL_MAX_VAL_MASK) +
				 COL_B9_BASE);
			priv->col_shअगरt[13] = ((addrmap[4] &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				((addrmap[4] & COL_MAX_VAL_MASK) +
				 COL_B10_BASE);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (memtype & MEM_TYPE_LPDDR3) अणु
			priv->col_shअगरt[10] = (((addrmap[3] >> 16) &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				(((addrmap[3] >> 16) & COL_MAX_VAL_MASK) +
				 COL_B8_BASE);
			priv->col_shअगरt[11] = (((addrmap[3] >> 24) &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				(((addrmap[3] >> 24) & COL_MAX_VAL_MASK) +
				 COL_B9_BASE);
			priv->col_shअगरt[13] = ((addrmap[4] &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				((addrmap[4] & COL_MAX_VAL_MASK) +
				 COL_B10_BASE);
		पूर्ण अन्यथा अणु
			priv->col_shअगरt[11] = (((addrmap[3] >> 16) &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				(((addrmap[3] >> 16) & COL_MAX_VAL_MASK) +
				 COL_B8_BASE);
			priv->col_shअगरt[13] = (((addrmap[3] >> 24) &
				COL_MAX_VAL_MASK) == COL_MAX_VAL_MASK) ? 0 :
				(((addrmap[3] >> 24) & COL_MAX_VAL_MASK) +
				 COL_B9_BASE);
		पूर्ण
	पूर्ण

	अगर (width) अणु
		क्रम (index = 9; index > width; index--) अणु
			priv->col_shअगरt[index] = priv->col_shअगरt[index - width];
			priv->col_shअगरt[index - width] = 0;
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम setup_bank_address_map(काष्ठा synps_edac_priv *priv, u32 *addrmap)
अणु
	priv->bank_shअगरt[0] = (addrmap[1] & BANK_MAX_VAL_MASK) + BANK_B0_BASE;
	priv->bank_shअगरt[1] = ((addrmap[1] >> 8) &
				BANK_MAX_VAL_MASK) + BANK_B1_BASE;
	priv->bank_shअगरt[2] = (((addrmap[1] >> 16) &
				BANK_MAX_VAL_MASK) == BANK_MAX_VAL_MASK) ? 0 :
				(((addrmap[1] >> 16) & BANK_MAX_VAL_MASK) +
				 BANK_B2_BASE);

पूर्ण

अटल व्योम setup_bg_address_map(काष्ठा synps_edac_priv *priv, u32 *addrmap)
अणु
	priv->bankgrp_shअगरt[0] = (addrmap[8] &
				BANKGRP_MAX_VAL_MASK) + BANKGRP_B0_BASE;
	priv->bankgrp_shअगरt[1] = (((addrmap[8] >> 8) & BANKGRP_MAX_VAL_MASK) ==
				BANKGRP_MAX_VAL_MASK) ? 0 : (((addrmap[8] >> 8)
				& BANKGRP_MAX_VAL_MASK) + BANKGRP_B1_BASE);

पूर्ण

अटल व्योम setup_rank_address_map(काष्ठा synps_edac_priv *priv, u32 *addrmap)
अणु
	priv->rank_shअगरt[0] = ((addrmap[0] & RANK_MAX_VAL_MASK) ==
				RANK_MAX_VAL_MASK) ? 0 : ((addrmap[0] &
				RANK_MAX_VAL_MASK) + RANK_B0_BASE);
पूर्ण

/**
 * setup_address_map -	Set Address Map by querying ADDRMAP रेजिस्टरs.
 * @priv:		DDR memory controller निजी instance data.
 *
 * Set Address Map by querying ADDRMAP रेजिस्टरs.
 *
 * Return: none.
 */
अटल व्योम setup_address_map(काष्ठा synps_edac_priv *priv)
अणु
	u32 addrmap[12];
	पूर्णांक index;

	क्रम (index = 0; index < 12; index++) अणु
		u32 addrmap_offset;

		addrmap_offset = ECC_ADDRMAP0_OFFSET + (index * 4);
		addrmap[index] = पढ़ोl(priv->baseaddr + addrmap_offset);
	पूर्ण

	setup_row_address_map(priv, addrmap);

	setup_column_address_map(priv, addrmap);

	setup_bank_address_map(priv, addrmap);

	setup_bg_address_map(priv, addrmap);

	setup_rank_address_map(priv, addrmap);
पूर्ण
#पूर्ण_अगर /* CONFIG_EDAC_DEBUG */

/**
 * mc_probe - Check controller and bind driver.
 * @pdev:	platक्रमm device.
 *
 * Probe a specअगरic controller instance क्रम binding with the driver.
 *
 * Return: 0 अगर the controller instance was successfully bound to the
 * driver; otherwise, < 0 on error.
 */
अटल पूर्णांक mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा synps_platक्रमm_data *p_data;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा synps_edac_priv *priv;
	काष्ठा mem_ctl_info *mci;
	व्योम __iomem *baseaddr;
	काष्ठा resource *res;
	पूर्णांक rc;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	baseaddr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(baseaddr))
		वापस PTR_ERR(baseaddr);

	p_data = of_device_get_match_data(&pdev->dev);
	अगर (!p_data)
		वापस -ENODEV;

	अगर (!p_data->get_ecc_state(baseaddr)) अणु
		edac_prपूर्णांकk(KERN_INFO, EDAC_MC, "ECC not enabled\n");
		वापस -ENXIO;
	पूर्ण

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = SYNPS_EDAC_NR_CSROWS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = SYNPS_EDAC_NR_CHANS;
	layers[1].is_virt_csrow = false;

	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers,
			    माप(काष्ठा synps_edac_priv));
	अगर (!mci) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Failed memory allocation for mc instance\n");
		वापस -ENOMEM;
	पूर्ण

	priv = mci->pvt_info;
	priv->baseaddr = baseaddr;
	priv->p_data = p_data;

	mc_init(mci, pdev);

	अगर (priv->p_data->quirks & DDR_ECC_INTR_SUPPORT) अणु
		rc = setup_irq(mci, pdev);
		अगर (rc)
			जाओ मुक्त_edac_mc;
	पूर्ण

	rc = edac_mc_add_mc(mci);
	अगर (rc) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Failed to register with EDAC core\n");
		जाओ मुक्त_edac_mc;
	पूर्ण

#अगर_घोषित CONFIG_EDAC_DEBUG
	अगर (priv->p_data->quirks & DDR_ECC_DATA_POISON_SUPPORT) अणु
		rc = edac_create_sysfs_attributes(mci);
		अगर (rc) अणु
			edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
					"Failed to create sysfs entries\n");
			जाओ मुक्त_edac_mc;
		पूर्ण
	पूर्ण

	अगर (of_device_is_compatible(pdev->dev.of_node,
				    "xlnx,zynqmp-ddrc-2.40a"))
		setup_address_map(priv);
#पूर्ण_अगर

	/*
	 * Start capturing the correctable and uncorrectable errors. A ग_लिखो of
	 * 0 starts the counters.
	 */
	अगर (!(priv->p_data->quirks & DDR_ECC_INTR_SUPPORT))
		ग_लिखोl(0x0, baseaddr + ECC_CTRL_OFST);

	वापस rc;

मुक्त_edac_mc:
	edac_mc_मुक्त(mci);

	वापस rc;
पूर्ण

/**
 * mc_हटाओ - Unbind driver from controller.
 * @pdev:	Platक्रमm device.
 *
 * Return: Unconditionally 0
 */
अटल पूर्णांक mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);
	काष्ठा synps_edac_priv *priv = mci->pvt_info;

	अगर (priv->p_data->quirks & DDR_ECC_INTR_SUPPORT)
		disable_पूर्णांकr(priv);

#अगर_घोषित CONFIG_EDAC_DEBUG
	अगर (priv->p_data->quirks & DDR_ECC_DATA_POISON_SUPPORT)
		edac_हटाओ_sysfs_attributes(mci);
#पूर्ण_अगर

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver synps_edac_mc_driver = अणु
	.driver = अणु
		   .name = "synopsys-edac",
		   .of_match_table = synps_edac_match,
		   पूर्ण,
	.probe = mc_probe,
	.हटाओ = mc_हटाओ,
पूर्ण;

module_platक्रमm_driver(synps_edac_mc_driver);

MODULE_AUTHOR("Xilinx Inc");
MODULE_DESCRIPTION("Synopsys DDR ECC driver");
MODULE_LICENSE("GPL v2");
