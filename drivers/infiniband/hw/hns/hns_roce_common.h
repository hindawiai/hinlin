<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _HNS_ROCE_COMMON_H
#घोषणा _HNS_ROCE_COMMON_H
#समावेश <linux/bitfield.h>

#घोषणा roce_ग_लिखो(dev, reg, val)	ग_लिखोl((val), (dev)->reg_base + (reg))
#घोषणा roce_पढ़ो(dev, reg)		पढ़ोl((dev)->reg_base + (reg))
#घोषणा roce_raw_ग_लिखो(value, addr) \
	__raw_ग_लिखोl((__क्रमce u32)cpu_to_le32(value), (addr))

#घोषणा roce_get_field(origin, mask, shअगरt)                                    \
	((le32_to_cpu(origin) & (mask)) >> (u32)(shअगरt))

#घोषणा roce_get_bit(origin, shअगरt) \
	roce_get_field((origin), (1ul << (shअगरt)), (shअगरt))

#घोषणा roce_set_field(origin, mask, shअगरt, val)                               \
	करो अणु                                                                   \
		(origin) &= ~cpu_to_le32(mask);                                \
		(origin) |=                                                    \
			cpu_to_le32(((u32)(val) << (u32)(shअगरt)) & (mask));    \
	पूर्ण जबतक (0)

#घोषणा roce_set_bit(origin, shअगरt, val)                                       \
	roce_set_field((origin), (1ul << (shअगरt)), (shअगरt), (val))

#घोषणा FIELD_LOC(field_type, field_h, field_l) field_type, field_h, field_l

#घोषणा _hr_reg_enable(ptr, field_type, field_h, field_l)                      \
	(अणु                                                                     \
		स्थिर field_type *_ptr = ptr;                                  \
		*((__le32 *)_ptr + (field_h) / 32) |= cpu_to_le32(             \
			BIT((field_l) % 32) +                                  \
			BUILD_BUG_ON_ZERO((field_h) != (field_l)));            \
	पूर्ण)

#घोषणा hr_reg_enable(ptr, field) _hr_reg_enable(ptr, field)

#घोषणा _hr_reg_clear(ptr, field_type, field_h, field_l)                       \
	(अणु                                                                     \
		स्थिर field_type *_ptr = ptr;                                  \
		BUILD_BUG_ON(((field_h) / 32) != ((field_l) / 32));            \
		*((__le32 *)_ptr + (field_h) / 32) &=                          \
			~cpu_to_le32(GENMASK((field_h) % 32, (field_l) % 32)); \
	पूर्ण)

#घोषणा hr_reg_clear(ptr, field) _hr_reg_clear(ptr, field)

#घोषणा _hr_reg_ग_लिखो(ptr, field_type, field_h, field_l, val)                  \
	(अणु                                                                     \
		_hr_reg_clear(ptr, field_type, field_h, field_l);              \
		*((__le32 *)ptr + (field_h) / 32) |= cpu_to_le32(FIELD_PREP(   \
			GENMASK((field_h) % 32, (field_l) % 32), val));        \
	पूर्ण)

#घोषणा hr_reg_ग_लिखो(ptr, field, val) _hr_reg_ग_लिखो(ptr, field, val)

#घोषणा _hr_reg_पढ़ो(ptr, field_type, field_h, field_l)                        \
	(अणु                                                                     \
		स्थिर field_type *_ptr = ptr;                                  \
		BUILD_BUG_ON(((field_h) / 32) != ((field_l) / 32));            \
		FIELD_GET(GENMASK((field_h) % 32, (field_l) % 32),             \
			  le32_to_cpu(*((__le32 *)_ptr + (field_h) / 32)));    \
	पूर्ण)

#घोषणा hr_reg_पढ़ो(ptr, field) _hr_reg_पढ़ो(ptr, field)

#घोषणा ROCEE_GLB_CFG_ROCEE_DB_SQ_MODE_S 3
#घोषणा ROCEE_GLB_CFG_ROCEE_DB_OTH_MODE_S 4

#घोषणा ROCEE_GLB_CFG_SQ_EXT_DB_MODE_S 5

#घोषणा ROCEE_GLB_CFG_OTH_EXT_DB_MODE_S 6

#घोषणा ROCEE_GLB_CFG_ROCEE_PORT_ST_S 10
#घोषणा ROCEE_GLB_CFG_ROCEE_PORT_ST_M  \
	(((1UL << 6) - 1) << ROCEE_GLB_CFG_ROCEE_PORT_ST_S)

#घोषणा ROCEE_GLB_CFG_TRP_RAQ_DROP_EN_S 16

#घोषणा ROCEE_DMAE_USER_CFG1_ROCEE_STREAM_ID_TB_CFG_S 0
#घोषणा ROCEE_DMAE_USER_CFG1_ROCEE_STREAM_ID_TB_CFG_M  \
	(((1UL << 24) - 1) << ROCEE_DMAE_USER_CFG1_ROCEE_STREAM_ID_TB_CFG_S)

#घोषणा ROCEE_DMAE_USER_CFG1_ROCEE_CACHE_TB_CFG_S 24
#घोषणा ROCEE_DMAE_USER_CFG1_ROCEE_CACHE_TB_CFG_M  \
	(((1UL << 4) - 1) << ROCEE_DMAE_USER_CFG1_ROCEE_CACHE_TB_CFG_S)

#घोषणा ROCEE_DMAE_USER_CFG2_ROCEE_STREAM_ID_PKT_CFG_S 0
#घोषणा ROCEE_DMAE_USER_CFG2_ROCEE_STREAM_ID_PKT_CFG_M   \
	(((1UL << 24) - 1) << ROCEE_DMAE_USER_CFG2_ROCEE_STREAM_ID_PKT_CFG_S)

#घोषणा ROCEE_DMAE_USER_CFG2_ROCEE_CACHE_PKT_CFG_S 24
#घोषणा ROCEE_DMAE_USER_CFG2_ROCEE_CACHE_PKT_CFG_M   \
	(((1UL << 4) - 1) << ROCEE_DMAE_USER_CFG2_ROCEE_CACHE_PKT_CFG_S)

#घोषणा ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_S 0
#घोषणा ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_M   \
	(((1UL << 16) - 1) << ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_S)

#घोषणा ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_EMPTY_S 16
#घोषणा ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_EMPTY_M   \
	(((1UL << 16) - 1) << ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_EMPTY_S)

#घोषणा ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_S 0
#घोषणा ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_M   \
	(((1UL << 16) - 1) << ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_S)

#घोषणा ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_EMPTY_S 16
#घोषणा ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_EMPTY_M   \
	(((1UL << 16) - 1) << ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_EMPTY_S)

#घोषणा ROCEE_RAQ_WL_ROCEE_RAQ_WL_S 0
#घोषणा ROCEE_RAQ_WL_ROCEE_RAQ_WL_M   \
	(((1UL << 8) - 1) << ROCEE_RAQ_WL_ROCEE_RAQ_WL_S)

#घोषणा ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_POL_TIME_INTERVAL_S 0
#घोषणा ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_POL_TIME_INTERVAL_M   \
	(((1UL << 15) - 1) << \
	ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_POL_TIME_INTERVAL_S)

#घोषणा ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_CFG_S 16
#घोषणा ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_CFG_M   \
	(((1UL << 4) - 1) << \
	ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_CFG_S)

#घोषणा ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_EN_S 20

#घोषणा ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_EXT_RAQ_MODE 21

#घोषणा ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_SHIFT_S 0
#घोषणा ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_SHIFT_M   \
	(((1UL << 5) - 1) << ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_SHIFT_S)

#घोषणा ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_BA_H_S 5
#घोषणा ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_BA_H_M   \
	(((1UL << 5) - 1) << ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_BA_H_S)

#घोषणा ROCEE_EXT_DB_OTH_H_EXT_DB_OTH_SHIFT_S 0
#घोषणा ROCEE_EXT_DB_OTH_H_EXT_DB_OTH_SHIFT_M   \
	(((1UL << 5) - 1) << ROCEE_EXT_DB_OTH_H_EXT_DB_OTH_SHIFT_S)

#घोषणा ROCEE_EXT_DB_SQ_H_EXT_DB_OTH_BA_H_S 5
#घोषणा ROCEE_EXT_DB_SQ_H_EXT_DB_OTH_BA_H_M   \
	(((1UL << 5) - 1) << ROCEE_EXT_DB_SQ_H_EXT_DB_OTH_BA_H_S)

#घोषणा ROCEE_EXT_RAQ_H_EXT_RAQ_SHIFT_S 0
#घोषणा ROCEE_EXT_RAQ_H_EXT_RAQ_SHIFT_M   \
	(((1UL << 5) - 1) << ROCEE_EXT_RAQ_H_EXT_RAQ_SHIFT_S)

#घोषणा ROCEE_EXT_RAQ_H_EXT_RAQ_BA_H_S 8
#घोषणा ROCEE_EXT_RAQ_H_EXT_RAQ_BA_H_M   \
	(((1UL << 5) - 1) << ROCEE_EXT_RAQ_H_EXT_RAQ_BA_H_S)

#घोषणा ROCEE_BT_CMD_H_ROCEE_BT_CMD_IN_MDF_S 0
#घोषणा ROCEE_BT_CMD_H_ROCEE_BT_CMD_IN_MDF_M   \
	(((1UL << 19) - 1) << ROCEE_BT_CMD_H_ROCEE_BT_CMD_IN_MDF_S)

#घोषणा ROCEE_BT_CMD_H_ROCEE_BT_CMD_S 19

#घोषणा ROCEE_BT_CMD_H_ROCEE_BT_CMD_MDF_S 20
#घोषणा ROCEE_BT_CMD_H_ROCEE_BT_CMD_MDF_M   \
	(((1UL << 2) - 1) << ROCEE_BT_CMD_H_ROCEE_BT_CMD_MDF_S)

#घोषणा ROCEE_BT_CMD_H_ROCEE_BT_CMD_BA_H_S 22
#घोषणा ROCEE_BT_CMD_H_ROCEE_BT_CMD_BA_H_M   \
	(((1UL << 5) - 1) << ROCEE_BT_CMD_H_ROCEE_BT_CMD_BA_H_S)

#घोषणा ROCEE_BT_CMD_H_ROCEE_BT_CMD_HW_SYNS_S 31

#घोषणा ROCEE_QP1C_CFG0_0_ROCEE_QP1C_QP_ST_S 0
#घोषणा ROCEE_QP1C_CFG0_0_ROCEE_QP1C_QP_ST_M   \
	(((1UL << 3) - 1) << ROCEE_QP1C_CFG0_0_ROCEE_QP1C_QP_ST_S)

#घोषणा ROCEE_QP1C_CFG3_0_ROCEE_QP1C_RQ_HEAD_S 0
#घोषणा ROCEE_QP1C_CFG3_0_ROCEE_QP1C_RQ_HEAD_M   \
	(((1UL << 15) - 1) << ROCEE_QP1C_CFG3_0_ROCEE_QP1C_RQ_HEAD_S)

#घोषणा ROCEE_MB6_ROCEE_MB_CMD_S 0
#घोषणा ROCEE_MB6_ROCEE_MB_CMD_M   \
	(((1UL << 8) - 1) << ROCEE_MB6_ROCEE_MB_CMD_S)

#घोषणा ROCEE_MB6_ROCEE_MB_CMD_MDF_S 8
#घोषणा ROCEE_MB6_ROCEE_MB_CMD_MDF_M   \
	(((1UL << 4) - 1) << ROCEE_MB6_ROCEE_MB_CMD_MDF_S)

#घोषणा ROCEE_MB6_ROCEE_MB_EVENT_S 14

#घोषणा ROCEE_MB6_ROCEE_MB_HW_RUN_S 15

#घोषणा ROCEE_MB6_ROCEE_MB_TOKEN_S 16
#घोषणा ROCEE_MB6_ROCEE_MB_TOKEN_M   \
	(((1UL << 16) - 1) << ROCEE_MB6_ROCEE_MB_TOKEN_S)

#घोषणा ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_S 0
#घोषणा ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_M   \
	(((1UL << 24) - 1) << ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_S)

#घोषणा ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_S 24
#घोषणा ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_M   \
	(((1UL << 4) - 1) << ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_S)

#घोषणा ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_S 28
#घोषणा ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_M   \
	(((1UL << 3) - 1) << ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_S)

#घोषणा ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_HW_SYNS_S 31

#घोषणा ROCEE_SMAC_H_ROCEE_SMAC_H_S 0
#घोषणा ROCEE_SMAC_H_ROCEE_SMAC_H_M   \
	(((1UL << 16) - 1) << ROCEE_SMAC_H_ROCEE_SMAC_H_S)

#घोषणा ROCEE_SMAC_H_ROCEE_PORT_MTU_S 16
#घोषणा ROCEE_SMAC_H_ROCEE_PORT_MTU_M   \
	(((1UL << 4) - 1) << ROCEE_SMAC_H_ROCEE_PORT_MTU_S)

#घोषणा ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_STATE_S 0
#घोषणा ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_STATE_M   \
	(((1UL << 2) - 1) << ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_STATE_S)

#घोषणा ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_AEQE_SHIFT_S 8
#घोषणा ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_AEQE_SHIFT_M   \
	(((1UL << 4) - 1) << ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_AEQE_SHIFT_S)

#घोषणा ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQ_ALM_OVF_INT_ST_S 17

#घोषणा ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQ_BT_H_S 0
#घोषणा ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQ_BT_H_M   \
	(((1UL << 5) - 1) << ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQ_BT_H_S)

#घोषणा ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQE_CUR_IDX_S 16
#घोषणा ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQE_CUR_IDX_M   \
	(((1UL << 16) - 1) << ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQE_CUR_IDX_S)

#घोषणा ROCEE_CAEP_AEQE_CONS_IDX_CAEP_AEQE_CONS_IDX_S 0
#घोषणा ROCEE_CAEP_AEQE_CONS_IDX_CAEP_AEQE_CONS_IDX_M   \
	(((1UL << 16) - 1) << ROCEE_CAEP_AEQE_CONS_IDX_CAEP_AEQE_CONS_IDX_S)

#घोषणा ROCEE_CAEP_CEQC_SHIFT_CAEP_CEQ_ALM_OVF_INT_ST_S 16
#घोषणा ROCEE_CAEP_CE_IRQ_MASK_CAEP_CEQ_ALM_OVF_MASK_S 1
#घोषणा ROCEE_CAEP_CEQ_ALM_OVF_CAEP_CEQ_ALM_OVF_S 0

#घोषणा ROCEE_CAEP_AE_MASK_CAEP_AEQ_ALM_OVF_MASK_S 0
#घोषणा ROCEE_CAEP_AE_MASK_CAEP_AE_IRQ_MASK_S 1

#घोषणा ROCEE_CAEP_AE_ST_CAEP_AEQ_ALM_OVF_S 0

#घोषणा ROCEE_SDB_ISSUE_PTR_SDB_ISSUE_PTR_S 0
#घोषणा ROCEE_SDB_ISSUE_PTR_SDB_ISSUE_PTR_M   \
	(((1UL << 28) - 1) << ROCEE_SDB_ISSUE_PTR_SDB_ISSUE_PTR_S)

#घोषणा ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S 0
#घोषणा ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_M   \
	(((1UL << 28) - 1) << ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S)

#घोषणा ROCEE_SDB_INV_CNT_SDB_INV_CNT_S 0
#घोषणा ROCEE_SDB_INV_CNT_SDB_INV_CNT_M   \
	(((1UL << 16) - 1) << ROCEE_SDB_INV_CNT_SDB_INV_CNT_S)

#घोषणा ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_S	0
#घोषणा ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_M	\
	(((1UL << 16) - 1) << ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_S)

#घोषणा ROCEE_SDB_CNT_CMP_BITS 16

#घोषणा ROCEE_TSP_BP_ST_QH_FIFO_ENTRY_S	20

#घोषणा ROCEE_CNT_CLR_CE_CNT_CLR_CE_S 0

/*************ROCEE_REG DEFINITION****************/
#घोषणा ROCEE_VENDOR_ID_REG			0x0
#घोषणा ROCEE_VENDOR_PART_ID_REG		0x4

#घोषणा ROCEE_SYS_IMAGE_GUID_L_REG		0xC
#घोषणा ROCEE_SYS_IMAGE_GUID_H_REG		0x10

#घोषणा ROCEE_PORT_GID_L_0_REG			0x50
#घोषणा ROCEE_PORT_GID_ML_0_REG			0x54
#घोषणा ROCEE_PORT_GID_MH_0_REG			0x58
#घोषणा ROCEE_PORT_GID_H_0_REG			0x5C

#घोषणा ROCEE_BT_CMD_H_REG			0x204

#घोषणा ROCEE_SMAC_L_0_REG			0x240
#घोषणा ROCEE_SMAC_H_0_REG			0x244

#घोषणा ROCEE_QP1C_CFG3_0_REG			0x27C

#घोषणा ROCEE_CAEP_AEQE_CONS_IDX_REG		0x3AC
#घोषणा ROCEE_CAEP_CEQC_CONS_IDX_0_REG		0x3BC

#घोषणा ROCEE_ECC_UCERR_ALM1_REG		0xB38
#घोषणा ROCEE_ECC_UCERR_ALM2_REG		0xB3C
#घोषणा ROCEE_ECC_CERR_ALM1_REG			0xB44
#घोषणा ROCEE_ECC_CERR_ALM2_REG			0xB48

#घोषणा ROCEE_ACK_DELAY_REG			0x14
#घोषणा ROCEE_GLB_CFG_REG			0x18

#घोषणा ROCEE_DMAE_USER_CFG1_REG		0x40
#घोषणा ROCEE_DMAE_USER_CFG2_REG		0x44

#घोषणा ROCEE_DB_SQ_WL_REG			0x154
#घोषणा ROCEE_DB_OTHERS_WL_REG			0x158
#घोषणा ROCEE_RAQ_WL_REG			0x15C
#घोषणा ROCEE_WRMS_POL_TIME_INTERVAL_REG	0x160
#घोषणा ROCEE_EXT_DB_SQ_REG			0x164
#घोषणा ROCEE_EXT_DB_SQ_H_REG			0x168
#घोषणा ROCEE_EXT_DB_OTH_REG			0x16C

#घोषणा ROCEE_EXT_DB_OTH_H_REG			0x170
#घोषणा ROCEE_EXT_DB_SQ_WL_EMPTY_REG		0x174
#घोषणा ROCEE_EXT_DB_SQ_WL_REG			0x178
#घोषणा ROCEE_EXT_DB_OTHERS_WL_EMPTY_REG	0x17C
#घोषणा ROCEE_EXT_DB_OTHERS_WL_REG		0x180
#घोषणा ROCEE_EXT_RAQ_REG			0x184
#घोषणा ROCEE_EXT_RAQ_H_REG			0x188

#घोषणा ROCEE_CAEP_CE_INTERVAL_CFG_REG		0x190
#घोषणा ROCEE_CAEP_CE_BURST_NUM_CFG_REG		0x194
#घोषणा ROCEE_BT_CMD_L_REG			0x200

#घोषणा ROCEE_MB1_REG				0x210
#घोषणा ROCEE_MB6_REG				0x224
#घोषणा ROCEE_DB_SQ_L_0_REG			0x230
#घोषणा ROCEE_DB_OTHERS_L_0_REG			0x238
#घोषणा ROCEE_QP1C_CFG0_0_REG			0x270

#घोषणा ROCEE_CAEP_AEQC_AEQE_SHIFT_REG		0x3A0
#घोषणा ROCEE_CAEP_CEQC_SHIFT_0_REG		0x3B0
#घोषणा ROCEE_CAEP_CE_IRQ_MASK_0_REG		0x3C0
#घोषणा ROCEE_CAEP_CEQ_ALM_OVF_0_REG		0x3C4
#घोषणा ROCEE_CAEP_AE_MASK_REG			0x6C8
#घोषणा ROCEE_CAEP_AE_ST_REG			0x6CC

#घोषणा ROCEE_CAEP_CQE_WCMD_EMPTY		0x850
#घोषणा ROCEE_SCAEP_WR_CQE_CNT			0x8D0
#घोषणा ROCEE_ECC_UCERR_ALM0_REG		0xB34
#घोषणा ROCEE_ECC_CERR_ALM0_REG			0xB40

/* V2 ROCEE REG */
#घोषणा ROCEE_TX_CMQ_BASEADDR_L_REG		0x07000
#घोषणा ROCEE_TX_CMQ_BASEADDR_H_REG		0x07004
#घोषणा ROCEE_TX_CMQ_DEPTH_REG			0x07008
#घोषणा ROCEE_TX_CMQ_HEAD_REG			0x07010
#घोषणा ROCEE_TX_CMQ_TAIL_REG			0x07014

#घोषणा ROCEE_RX_CMQ_BASEADDR_L_REG		0x07018
#घोषणा ROCEE_RX_CMQ_BASEADDR_H_REG		0x0701c
#घोषणा ROCEE_RX_CMQ_DEPTH_REG			0x07020
#घोषणा ROCEE_RX_CMQ_TAIL_REG			0x07024
#घोषणा ROCEE_RX_CMQ_HEAD_REG			0x07028

#घोषणा ROCEE_VF_EQ_DB_CFG0_REG			0x238
#घोषणा ROCEE_VF_EQ_DB_CFG1_REG			0x23C

#घोषणा ROCEE_VF_ABN_INT_CFG_REG		0x13000
#घोषणा ROCEE_VF_ABN_INT_ST_REG			0x13004
#घोषणा ROCEE_VF_ABN_INT_EN_REG			0x13008
#घोषणा ROCEE_VF_EVENT_INT_EN_REG		0x1300c

#पूर्ण_अगर /* _HNS_ROCE_COMMON_H */
