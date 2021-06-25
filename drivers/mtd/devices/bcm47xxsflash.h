<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BCM47XXSFLASH_H
#घोषणा __BCM47XXSFLASH_H

#समावेश <linux/mtd/mtd.h>

#घोषणा BCM47XXSFLASH_WINDOW_SZ			SZ_16M

/* Used क्रम ST flashes only. */
#घोषणा OPCODE_ST_WREN		0x0006		/* Write Enable */
#घोषणा OPCODE_ST_WRDIS		0x0004		/* Write Disable */
#घोषणा OPCODE_ST_RDSR		0x0105		/* Read Status Register */
#घोषणा OPCODE_ST_WRSR		0x0101		/* Write Status Register */
#घोषणा OPCODE_ST_READ		0x0303		/* Read Data Bytes */
#घोषणा OPCODE_ST_PP		0x0302		/* Page Program */
#घोषणा OPCODE_ST_SE		0x02d8		/* Sector Erase */
#घोषणा OPCODE_ST_BE		0x00c7		/* Bulk Erase */
#घोषणा OPCODE_ST_DP		0x00b9		/* Deep Power-करोwn */
#घोषणा OPCODE_ST_RES		0x03ab		/* Read Electronic Signature */
#घोषणा OPCODE_ST_CSA		0x1000		/* Keep chip select निश्चितed */
#घोषणा OPCODE_ST_SSE		0x0220		/* Sub-sector Erase */
#घोषणा OPCODE_ST_READ4B	0x6313		/* Read Data Bytes in 4Byte addressing mode */

/* Used क्रम Aपंचांगel flashes only. */
#घोषणा OPCODE_AT_READ				0x07e8
#घोषणा OPCODE_AT_PAGE_READ			0x07d2
#घोषणा OPCODE_AT_STATUS			0x01d7
#घोषणा OPCODE_AT_BUF1_WRITE			0x0384
#घोषणा OPCODE_AT_BUF2_WRITE			0x0387
#घोषणा OPCODE_AT_BUF1_ERASE_PROGRAM		0x0283
#घोषणा OPCODE_AT_BUF2_ERASE_PROGRAM		0x0286
#घोषणा OPCODE_AT_BUF1_PROGRAM			0x0288
#घोषणा OPCODE_AT_BUF2_PROGRAM			0x0289
#घोषणा OPCODE_AT_PAGE_ERASE			0x0281
#घोषणा OPCODE_AT_BLOCK_ERASE			0x0250
#घोषणा OPCODE_AT_BUF1_WRITE_ERASE_PROGRAM	0x0382
#घोषणा OPCODE_AT_BUF2_WRITE_ERASE_PROGRAM	0x0385
#घोषणा OPCODE_AT_BUF1_LOAD			0x0253
#घोषणा OPCODE_AT_BUF2_LOAD			0x0255
#घोषणा OPCODE_AT_BUF1_COMPARE			0x0260
#घोषणा OPCODE_AT_BUF2_COMPARE			0x0261
#घोषणा OPCODE_AT_BUF1_REPROGRAM		0x0258
#घोषणा OPCODE_AT_BUF2_REPROGRAM		0x0259

/* Status रेजिस्टर bits क्रम ST flashes */
#घोषणा SR_ST_WIP		0x01		/* Write In Progress */
#घोषणा SR_ST_WEL		0x02		/* Write Enable Latch */
#घोषणा SR_ST_BP_MASK		0x1c		/* Block Protect */
#घोषणा SR_ST_BP_SHIFT		2
#घोषणा SR_ST_SRWD		0x80		/* Status Register Write Disable */

/* Status रेजिस्टर bits क्रम Aपंचांगel flashes */
#घोषणा SR_AT_READY		0x80
#घोषणा SR_AT_MISMATCH		0x40
#घोषणा SR_AT_ID_MASK		0x38
#घोषणा SR_AT_ID_SHIFT		3

काष्ठा bcma_drv_cc;

क्रमागत bcm47xxsflash_type अणु
	BCM47XXSFLASH_TYPE_ATMEL,
	BCM47XXSFLASH_TYPE_ST,
पूर्ण;

काष्ठा bcm47xxsflash अणु
	काष्ठा bcma_drv_cc *bcma_cc;
	पूर्णांक (*cc_पढ़ो)(काष्ठा bcm47xxsflash *b47s, u16 offset);
	व्योम (*cc_ग_लिखो)(काष्ठा bcm47xxsflash *b47s, u16 offset, u32 value);

	क्रमागत bcm47xxsflash_type type;

	व्योम __iomem *winकरोw;

	u32 blocksize;
	u16 numblocks;
	u32 size;

	काष्ठा mtd_info mtd;
पूर्ण;

#पूर्ण_अगर /* BCM47XXSFLASH */
