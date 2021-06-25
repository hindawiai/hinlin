<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018-2019 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare eDMA v0 core
 *
 * Author: Gustavo Pimentel <gustavo.pimentel@synopsys.com>
 */

#अगर_अघोषित _DW_EDMA_V0_REGS_H
#घोषणा _DW_EDMA_V0_REGS_H

#समावेश <linux/dmaengine.h>

#घोषणा EDMA_V0_MAX_NR_CH				8
#घोषणा EDMA_V0_VIEWPORT_MASK				GENMASK(2, 0)
#घोषणा EDMA_V0_DONE_INT_MASK				GENMASK(7, 0)
#घोषणा EDMA_V0_ABORT_INT_MASK				GENMASK(23, 16)
#घोषणा EDMA_V0_WRITE_CH_COUNT_MASK			GENMASK(3, 0)
#घोषणा EDMA_V0_READ_CH_COUNT_MASK			GENMASK(19, 16)
#घोषणा EDMA_V0_CH_STATUS_MASK				GENMASK(6, 5)
#घोषणा EDMA_V0_DOORBELL_CH_MASK			GENMASK(2, 0)
#घोषणा EDMA_V0_LINKED_LIST_ERR_MASK			GENMASK(7, 0)

#घोषणा EDMA_V0_CH_ODD_MSI_DATA_MASK			GENMASK(31, 16)
#घोषणा EDMA_V0_CH_EVEN_MSI_DATA_MASK			GENMASK(15, 0)

काष्ठा dw_edma_v0_ch_regs अणु
	u32 ch_control1;				/* 0x0000 */
	u32 ch_control2;				/* 0x0004 */
	u32 transfer_size;				/* 0x0008 */
	जोड़ अणु
		u64 reg;				/* 0x000c..0x0010 */
		काष्ठा अणु
			u32 lsb;			/* 0x000c */
			u32 msb;			/* 0x0010 */
		पूर्ण;
	पूर्ण sar;
	जोड़ अणु
		u64 reg;				/* 0x0014..0x0018 */
		काष्ठा अणु
			u32 lsb;			/* 0x0014 */
			u32 msb;			/* 0x0018 */
		पूर्ण;
	पूर्ण dar;
	जोड़ अणु
		u64 reg;				/* 0x001c..0x0020 */
		काष्ठा अणु
			u32 lsb;			/* 0x001c */
			u32 msb;			/* 0x0020 */
		पूर्ण;
	पूर्ण llp;
पूर्ण __packed;

काष्ठा dw_edma_v0_ch अणु
	काष्ठा dw_edma_v0_ch_regs wr;			/* 0x0200 */
	u32 padding_1[55];				/* 0x0224..0x02fc */
	काष्ठा dw_edma_v0_ch_regs rd;			/* 0x0300 */
	u32 padding_2[55];				/* 0x0324..0x03fc */
पूर्ण __packed;

काष्ठा dw_edma_v0_unroll अणु
	u32 padding_1;					/* 0x00f8 */
	u32 wr_engine_chgroup;				/* 0x0100 */
	u32 rd_engine_chgroup;				/* 0x0104 */
	जोड़ अणु
		u64 reg;				/* 0x0108..0x010c */
		काष्ठा अणु
			u32 lsb;			/* 0x0108 */
			u32 msb;			/* 0x010c */
		पूर्ण;
	पूर्ण wr_engine_hshake_cnt;
	u32 padding_2[2];				/* 0x0110..0x0114 */
	जोड़ अणु
		u64 reg;				/* 0x0120..0x0124 */
		काष्ठा अणु
			u32 lsb;			/* 0x0120 */
			u32 msb;			/* 0x0124 */
		पूर्ण;
	पूर्ण rd_engine_hshake_cnt;
	u32 padding_3[2];				/* 0x0120..0x0124 */
	u32 wr_ch0_pwr_en;				/* 0x0128 */
	u32 wr_ch1_pwr_en;				/* 0x012c */
	u32 wr_ch2_pwr_en;				/* 0x0130 */
	u32 wr_ch3_pwr_en;				/* 0x0134 */
	u32 wr_ch4_pwr_en;				/* 0x0138 */
	u32 wr_ch5_pwr_en;				/* 0x013c */
	u32 wr_ch6_pwr_en;				/* 0x0140 */
	u32 wr_ch7_pwr_en;				/* 0x0144 */
	u32 padding_4[8];				/* 0x0148..0x0164 */
	u32 rd_ch0_pwr_en;				/* 0x0168 */
	u32 rd_ch1_pwr_en;				/* 0x016c */
	u32 rd_ch2_pwr_en;				/* 0x0170 */
	u32 rd_ch3_pwr_en;				/* 0x0174 */
	u32 rd_ch4_pwr_en;				/* 0x0178 */
	u32 rd_ch5_pwr_en;				/* 0x018c */
	u32 rd_ch6_pwr_en;				/* 0x0180 */
	u32 rd_ch7_pwr_en;				/* 0x0184 */
	u32 padding_5[30];				/* 0x0188..0x01fc */
	काष्ठा dw_edma_v0_ch ch[EDMA_V0_MAX_NR_CH];	/* 0x0200..0x1120 */
पूर्ण __packed;

काष्ठा dw_edma_v0_legacy अणु
	u32 viewport_sel;				/* 0x00f8 */
	काष्ठा dw_edma_v0_ch_regs ch;			/* 0x0100..0x0120 */
पूर्ण __packed;

काष्ठा dw_edma_v0_regs अणु
	/* eDMA global रेजिस्टरs */
	u32 ctrl_data_arb_prior;			/* 0x0000 */
	u32 padding_1;					/* 0x0004 */
	u32 ctrl;					/* 0x0008 */
	u32 wr_engine_en;				/* 0x000c */
	u32 wr_करोorbell;				/* 0x0010 */
	u32 padding_2;					/* 0x0014 */
	जोड़ अणु
		u64 reg;				/* 0x0018..0x001c */
		काष्ठा अणु
			u32 lsb;			/* 0x0018 */
			u32 msb;			/* 0x001c */
		पूर्ण;
	पूर्ण wr_ch_arb_weight;
	u32 padding_3[3];				/* 0x0020..0x0028 */
	u32 rd_engine_en;				/* 0x002c */
	u32 rd_करोorbell;				/* 0x0030 */
	u32 padding_4;					/* 0x0034 */
	जोड़ अणु
		u64 reg;				/* 0x0038..0x003c */
		काष्ठा अणु
			u32 lsb;			/* 0x0038 */
			u32 msb;			/* 0x003c */
		पूर्ण;
	पूर्ण rd_ch_arb_weight;
	u32 padding_5[3];				/* 0x0040..0x0048 */
	/* eDMA पूर्णांकerrupts रेजिस्टरs */
	u32 wr_पूर्णांक_status;				/* 0x004c */
	u32 padding_6;					/* 0x0050 */
	u32 wr_पूर्णांक_mask;				/* 0x0054 */
	u32 wr_पूर्णांक_clear;				/* 0x0058 */
	u32 wr_err_status;				/* 0x005c */
	जोड़ अणु
		u64 reg;				/* 0x0060..0x0064 */
		काष्ठा अणु
			u32 lsb;			/* 0x0060 */
			u32 msb;			/* 0x0064 */
		पूर्ण;
	पूर्ण wr_करोne_imwr;
	जोड़ अणु
		u64 reg;				/* 0x0068..0x006c */
		काष्ठा अणु
			u32 lsb;			/* 0x0068 */
			u32 msb;			/* 0x006c */
		पूर्ण;
	पूर्ण wr_पात_imwr;
	u32 wr_ch01_imwr_data;				/* 0x0070 */
	u32 wr_ch23_imwr_data;				/* 0x0074 */
	u32 wr_ch45_imwr_data;				/* 0x0078 */
	u32 wr_ch67_imwr_data;				/* 0x007c */
	u32 padding_7[4];				/* 0x0080..0x008c */
	u32 wr_linked_list_err_en;			/* 0x0090 */
	u32 padding_8[3];				/* 0x0094..0x009c */
	u32 rd_पूर्णांक_status;				/* 0x00a0 */
	u32 padding_9;					/* 0x00a4 */
	u32 rd_पूर्णांक_mask;				/* 0x00a8 */
	u32 rd_पूर्णांक_clear;				/* 0x00ac */
	u32 padding_10;					/* 0x00b0 */
	जोड़ अणु
		u64 reg;				/* 0x00b4..0x00b8 */
		काष्ठा अणु
			u32 lsb;			/* 0x00b4 */
			u32 msb;			/* 0x00b8 */
		पूर्ण;
	पूर्ण rd_err_status;
	u32 padding_11[2];				/* 0x00bc..0x00c0 */
	u32 rd_linked_list_err_en;			/* 0x00c4 */
	u32 padding_12;					/* 0x00c8 */
	जोड़ अणु
		u64 reg;				/* 0x00cc..0x00d0 */
		काष्ठा अणु
			u32 lsb;			/* 0x00cc */
			u32 msb;			/* 0x00d0 */
		पूर्ण;
	पूर्ण rd_करोne_imwr;
	जोड़ अणु
		u64 reg;				/* 0x00d4..0x00d8 */
		काष्ठा अणु
			u32 lsb;			/* 0x00d4 */
			u32 msb;			/* 0x00d8 */
		पूर्ण;
	पूर्ण rd_पात_imwr;
	u32 rd_ch01_imwr_data;				/* 0x00dc */
	u32 rd_ch23_imwr_data;				/* 0x00e0 */
	u32 rd_ch45_imwr_data;				/* 0x00e4 */
	u32 rd_ch67_imwr_data;				/* 0x00e8 */
	u32 padding_13[4];				/* 0x00ec..0x00f8 */
	/* eDMA channel context grouping */
	जोड़ dw_edma_v0_type अणु
		काष्ठा dw_edma_v0_legacy legacy;	/* 0x00f8..0x0120 */
		काष्ठा dw_edma_v0_unroll unroll;	/* 0x00f8..0x1120 */
	पूर्ण type;
पूर्ण __packed;

काष्ठा dw_edma_v0_lli अणु
	u32 control;
	u32 transfer_size;
	जोड़ अणु
		u64 reg;
		काष्ठा अणु
			u32 lsb;
			u32 msb;
		पूर्ण;
	पूर्ण sar;
	जोड़ अणु
		u64 reg;
		काष्ठा अणु
			u32 lsb;
			u32 msb;
		पूर्ण;
	पूर्ण dar;
पूर्ण __packed;

काष्ठा dw_edma_v0_llp अणु
	u32 control;
	u32 reserved;
	जोड़ अणु
		u64 reg;
		काष्ठा अणु
			u32 lsb;
			u32 msb;
		पूर्ण;
	पूर्ण llp;
पूर्ण __packed;

#पूर्ण_अगर /* _DW_EDMA_V0_REGS_H */
