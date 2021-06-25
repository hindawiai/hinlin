<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2017-2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित GAUDI_PACKETS_H
#घोषणा GAUDI_PACKETS_H

#समावेश <linux/types.h>

#घोषणा PACKET_HEADER_PACKET_ID_SHIFT		56
#घोषणा PACKET_HEADER_PACKET_ID_MASK		0x1F00000000000000ull

क्रमागत packet_id अणु
	PACKET_WREG_32 = 0x1,
	PACKET_WREG_BULK = 0x2,
	PACKET_MSG_LONG = 0x3,
	PACKET_MSG_SHORT = 0x4,
	PACKET_CP_DMA = 0x5,
	PACKET_REPEAT = 0x6,
	PACKET_MSG_PROT = 0x7,
	PACKET_FENCE = 0x8,
	PACKET_LIN_DMA = 0x9,
	PACKET_NOP = 0xA,
	PACKET_STOP = 0xB,
	PACKET_ARB_POINT = 0xC,
	PACKET_WAIT = 0xD,
	PACKET_LOAD_AND_EXE = 0xF,
	MAX_PACKET_ID = (PACKET_HEADER_PACKET_ID_MASK >>
				PACKET_HEADER_PACKET_ID_SHIFT) + 1
पूर्ण;

#घोषणा GAUDI_PKT_CTL_OPCODE_SHIFT	24
#घोषणा GAUDI_PKT_CTL_OPCODE_MASK	0x1F000000

#घोषणा GAUDI_PKT_CTL_EB_SHIFT		29
#घोषणा GAUDI_PKT_CTL_EB_MASK		0x20000000

#घोषणा GAUDI_PKT_CTL_RB_SHIFT		30
#घोषणा GAUDI_PKT_CTL_RB_MASK		0x40000000

#घोषणा GAUDI_PKT_CTL_MB_SHIFT		31
#घोषणा GAUDI_PKT_CTL_MB_MASK		0x80000000

/* All packets have, at least, an 8-byte header, which contains
 * the packet type. The kernel driver uses the packet header क्रम packet
 * validation and to perक्रमm any necessary required preparation beक्रमe
 * sending them off to the hardware.
 */
काष्ठा gaudi_packet अणु
	__le64 header;
	/* The rest of the packet data follows. Use the corresponding
	 * packet_XXX काष्ठा to deference the data, based on packet type
	 */
	u8 contents[0];
पूर्ण;

काष्ठा packet_nop अणु
	__le32 reserved;
	__le32 ctl;
पूर्ण;

काष्ठा packet_stop अणु
	__le32 reserved;
	__le32 ctl;
पूर्ण;

काष्ठा packet_wreg32 अणु
	__le32 value;
	__le32 ctl;
पूर्ण;

काष्ठा packet_wreg_bulk अणु
	__le32 size64;
	__le32 ctl;
	__le64 values[0]; /* data starts here */
पूर्ण;

#घोषणा GAUDI_PKT_LONG_CTL_OP_SHIFT		20
#घोषणा GAUDI_PKT_LONG_CTL_OP_MASK		0x00300000

काष्ठा packet_msg_दीर्घ अणु
	__le32 value;
	__le32 ctl;
	__le64 addr;
पूर्ण;

#घोषणा GAUDI_PKT_SHORT_VAL_SOB_SYNC_VAL_SHIFT	0
#घोषणा GAUDI_PKT_SHORT_VAL_SOB_SYNC_VAL_MASK	0x00007FFF

#घोषणा GAUDI_PKT_SHORT_VAL_SOB_MOD_SHIFT	31
#घोषणा GAUDI_PKT_SHORT_VAL_SOB_MOD_MASK	0x80000000

#घोषणा GAUDI_PKT_SHORT_VAL_MON_SYNC_GID_SHIFT	0
#घोषणा GAUDI_PKT_SHORT_VAL_MON_SYNC_GID_MASK	0x000000FF

#घोषणा GAUDI_PKT_SHORT_VAL_MON_MASK_SHIFT	8
#घोषणा GAUDI_PKT_SHORT_VAL_MON_MASK_MASK	0x0000FF00

#घोषणा GAUDI_PKT_SHORT_VAL_MON_MODE_SHIFT	16
#घोषणा GAUDI_PKT_SHORT_VAL_MON_MODE_MASK	0x00010000

#घोषणा GAUDI_PKT_SHORT_VAL_MON_SYNC_VAL_SHIFT	17
#घोषणा GAUDI_PKT_SHORT_VAL_MON_SYNC_VAL_MASK	0xFFFE0000

#घोषणा GAUDI_PKT_SHORT_CTL_ADDR_SHIFT		0
#घोषणा GAUDI_PKT_SHORT_CTL_ADDR_MASK		0x0000FFFF

#घोषणा GAUDI_PKT_SHORT_CTL_OP_SHIFT		20
#घोषणा GAUDI_PKT_SHORT_CTL_OP_MASK		0x00300000

#घोषणा GAUDI_PKT_SHORT_CTL_BASE_SHIFT		22
#घोषणा GAUDI_PKT_SHORT_CTL_BASE_MASK		0x00C00000

काष्ठा packet_msg_लघु अणु
	__le32 value;
	__le32 ctl;
पूर्ण;

काष्ठा packet_msg_prot अणु
	__le32 value;
	__le32 ctl;
	__le64 addr;
पूर्ण;

#घोषणा GAUDI_PKT_FENCE_CFG_DEC_VAL_SHIFT	0
#घोषणा GAUDI_PKT_FENCE_CFG_DEC_VAL_MASK	0x0000000F

#घोषणा GAUDI_PKT_FENCE_CFG_TARGET_VAL_SHIFT	16
#घोषणा GAUDI_PKT_FENCE_CFG_TARGET_VAL_MASK	0x00FF0000

#घोषणा GAUDI_PKT_FENCE_CFG_ID_SHIFT		30
#घोषणा GAUDI_PKT_FENCE_CFG_ID_MASK		0xC0000000

#घोषणा GAUDI_PKT_FENCE_CTL_PRED_SHIFT		0
#घोषणा GAUDI_PKT_FENCE_CTL_PRED_MASK		0x0000001F

काष्ठा packet_fence अणु
	__le32 cfg;
	__le32 ctl;
पूर्ण;

#घोषणा GAUDI_PKT_LIN_DMA_CTL_WRCOMP_EN_SHIFT	0
#घोषणा GAUDI_PKT_LIN_DMA_CTL_WRCOMP_EN_MASK	0x00000001

#घोषणा GAUDI_PKT_LIN_DMA_CTL_LIN_SHIFT		3
#घोषणा GAUDI_PKT_LIN_DMA_CTL_LIN_MASK		0x00000008

#घोषणा GAUDI_PKT_LIN_DMA_CTL_MEMSET_SHIFT	4
#घोषणा GAUDI_PKT_LIN_DMA_CTL_MEMSET_MASK	0x00000010

#घोषणा GAUDI_PKT_LIN_DMA_DST_ADDR_SHIFT	0
#घोषणा GAUDI_PKT_LIN_DMA_DST_ADDR_MASK		0x00FFFFFFFFFFFFFFull

काष्ठा packet_lin_dma अणु
	__le32 tsize;
	__le32 ctl;
	__le64 src_addr;
	__le64 dst_addr;
पूर्ण;

काष्ठा packet_arb_poपूर्णांक अणु
	__le32 cfg;
	__le32 ctl;
पूर्ण;

काष्ठा packet_repeat अणु
	__le32 cfg;
	__le32 ctl;
पूर्ण;

काष्ठा packet_रुको अणु
	__le32 cfg;
	__le32 ctl;
पूर्ण;

#घोषणा GAUDI_PKT_LOAD_AND_EXE_CFG_DST_SHIFT	0
#घोषणा GAUDI_PKT_LOAD_AND_EXE_CFG_DST_MASK	0x00000001

काष्ठा packet_load_and_exe अणु
	__le32 cfg;
	__le32 ctl;
	__le64 src_addr;
पूर्ण;

काष्ठा packet_cp_dma अणु
	__le32 tsize;
	__le32 ctl;
	__le64 src_addr;
पूर्ण;

#पूर्ण_अगर /* GAUDI_PACKETS_H */
