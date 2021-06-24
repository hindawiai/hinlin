<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2017-2018 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित GOYA_PACKETS_H
#घोषणा GOYA_PACKETS_H

#समावेश <linux/types.h>

#घोषणा PACKET_HEADER_PACKET_ID_SHIFT		56
#घोषणा PACKET_HEADER_PACKET_ID_MASK		0x1F00000000000000ull

क्रमागत packet_id अणु
	PACKET_WREG_32 = 0x1,
	PACKET_WREG_BULK = 0x2,
	PACKET_MSG_LONG = 0x3,
	PACKET_MSG_SHORT = 0x4,
	PACKET_CP_DMA = 0x5,
	PACKET_MSG_PROT = 0x7,
	PACKET_FENCE = 0x8,
	PACKET_LIN_DMA = 0x9,
	PACKET_NOP = 0xA,
	PACKET_STOP = 0xB,
	MAX_PACKET_ID = (PACKET_HEADER_PACKET_ID_MASK >>
				PACKET_HEADER_PACKET_ID_SHIFT) + 1
पूर्ण;

क्रमागत goya_dma_direction अणु
	DMA_HOST_TO_DRAM,
	DMA_HOST_TO_SRAM,
	DMA_DRAM_TO_SRAM,
	DMA_SRAM_TO_DRAM,
	DMA_SRAM_TO_HOST,
	DMA_DRAM_TO_HOST,
	DMA_DRAM_TO_DRAM,
	DMA_SRAM_TO_SRAM,
	DMA_ENUM_MAX
पूर्ण;

#घोषणा GOYA_PKT_CTL_OPCODE_SHIFT	24
#घोषणा GOYA_PKT_CTL_OPCODE_MASK	0x1F000000

#घोषणा GOYA_PKT_CTL_EB_SHIFT		29
#घोषणा GOYA_PKT_CTL_EB_MASK		0x20000000

#घोषणा GOYA_PKT_CTL_RB_SHIFT		30
#घोषणा GOYA_PKT_CTL_RB_MASK		0x40000000

#घोषणा GOYA_PKT_CTL_MB_SHIFT		31
#घोषणा GOYA_PKT_CTL_MB_MASK		0x80000000

/* All packets have, at least, an 8-byte header, which contains
 * the packet type. The kernel driver uses the packet header क्रम packet
 * validation and to perक्रमm any necessary required preparation beक्रमe
 * sending them off to the hardware.
 */
काष्ठा goya_packet अणु
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

#घोषणा GOYA_PKT_WREG32_CTL_REG_OFFSET_SHIFT	0
#घोषणा GOYA_PKT_WREG32_CTL_REG_OFFSET_MASK	0x0000FFFF

काष्ठा packet_wreg32 अणु
	__le32 value;
	__le32 ctl;
पूर्ण;

काष्ठा packet_wreg_bulk अणु
	__le32 size64;
	__le32 ctl;
	__le64 values[0]; /* data starts here */
पूर्ण;

काष्ठा packet_msg_दीर्घ अणु
	__le32 value;
	__le32 ctl;
	__le64 addr;
पूर्ण;

काष्ठा packet_msg_लघु अणु
	__le32 value;
	__le32 ctl;
पूर्ण;

काष्ठा packet_msg_prot अणु
	__le32 value;
	__le32 ctl;
	__le64 addr;
पूर्ण;

काष्ठा packet_fence अणु
	__le32 cfg;
	__le32 ctl;
पूर्ण;

#घोषणा GOYA_PKT_LIN_DMA_CTL_WO_SHIFT		0
#घोषणा GOYA_PKT_LIN_DMA_CTL_WO_MASK		0x00000001

#घोषणा GOYA_PKT_LIN_DMA_CTL_RDCOMP_SHIFT	1
#घोषणा GOYA_PKT_LIN_DMA_CTL_RDCOMP_MASK	0x00000002

#घोषणा GOYA_PKT_LIN_DMA_CTL_WRCOMP_SHIFT	2
#घोषणा GOYA_PKT_LIN_DMA_CTL_WRCOMP_MASK	0x00000004

#घोषणा GOYA_PKT_LIN_DMA_CTL_MEMSET_SHIFT	6
#घोषणा GOYA_PKT_LIN_DMA_CTL_MEMSET_MASK	0x00000040

#घोषणा GOYA_PKT_LIN_DMA_CTL_DMA_सूची_SHIFT	20
#घोषणा GOYA_PKT_LIN_DMA_CTL_DMA_सूची_MASK	0x00700000

काष्ठा packet_lin_dma अणु
	__le32 tsize;
	__le32 ctl;
	__le64 src_addr;
	__le64 dst_addr;
पूर्ण;

काष्ठा packet_cp_dma अणु
	__le32 tsize;
	__le32 ctl;
	__le64 src_addr;
पूर्ण;

#पूर्ण_अगर /* GOYA_PACKETS_H */
