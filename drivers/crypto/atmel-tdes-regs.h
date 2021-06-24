<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ATMEL_TDES_REGS_H__
#घोषणा __ATMEL_TDES_REGS_H__

#घोषणा TDES_CR			0x00
#घोषणा TDES_CR_START			(1 << 0)
#घोषणा TDES_CR_SWRST			(1 << 8)
#घोषणा TDES_CR_LOADSEED		(1 << 16)

#घोषणा	TDES_MR			0x04
#घोषणा TDES_MR_CYPHER_DEC		(0 << 0)
#घोषणा TDES_MR_CYPHER_ENC		(1 << 0)
#घोषणा TDES_MR_TDESMOD_MASK	(0x3 << 1)
#घोषणा TDES_MR_TDESMOD_DES		(0x0 << 1)
#घोषणा TDES_MR_TDESMOD_TDES	(0x1 << 1)
#घोषणा TDES_MR_TDESMOD_XTEA	(0x2 << 1)
#घोषणा TDES_MR_KEYMOD_3KEY		(0 << 4)
#घोषणा TDES_MR_KEYMOD_2KEY		(1 << 4)
#घोषणा TDES_MR_SMOD_MASK		(0x3 << 8)
#घोषणा TDES_MR_SMOD_MANUAL		(0x0 << 8)
#घोषणा TDES_MR_SMOD_AUTO		(0x1 << 8)
#घोषणा TDES_MR_SMOD_PDC		(0x2 << 8)
#घोषणा TDES_MR_OPMOD_MASK		(0x3 << 12)
#घोषणा TDES_MR_OPMOD_ECB		(0x0 << 12)
#घोषणा TDES_MR_OPMOD_CBC		(0x1 << 12)
#घोषणा TDES_MR_OPMOD_OFB		(0x2 << 12)
#घोषणा TDES_MR_OPMOD_CFB		(0x3 << 12)
#घोषणा TDES_MR_LOD				(0x1 << 15)
#घोषणा TDES_MR_CFBS_MASK		(0x3 << 16)
#घोषणा TDES_MR_CFBS_64b		(0x0 << 16)
#घोषणा TDES_MR_CFBS_32b		(0x1 << 16)
#घोषणा TDES_MR_CFBS_16b		(0x2 << 16)
#घोषणा TDES_MR_CFBS_8b			(0x3 << 16)
#घोषणा TDES_MR_CKEY_MASK		(0xF << 20)
#घोषणा TDES_MR_CKEY_OFFSET		20
#घोषणा TDES_MR_CTYPE_MASK		(0x3F << 24)
#घोषणा TDES_MR_CTYPE_OFFSET	24

#घोषणा	TDES_IER		0x10
#घोषणा	TDES_IDR		0x14
#घोषणा	TDES_IMR		0x18
#घोषणा	TDES_ISR		0x1C
#घोषणा TDES_INT_DATARDY		(1 << 0)
#घोषणा TDES_INT_ENDRX			(1 << 1)
#घोषणा TDES_INT_ENDTX			(1 << 2)
#घोषणा TDES_INT_RXBUFF			(1 << 3)
#घोषणा TDES_INT_TXBUFE			(1 << 4)
#घोषणा TDES_INT_URAD			(1 << 8)
#घोषणा TDES_ISR_URAT_MASK		(0x3 << 12)
#घोषणा TDES_ISR_URAT_IDR		(0x0 << 12)
#घोषणा TDES_ISR_URAT_ODR		(0x1 << 12)
#घोषणा TDES_ISR_URAT_MR		(0x2 << 12)
#घोषणा TDES_ISR_URAT_WO		(0x3 << 12)


#घोषणा	TDES_KEY1W1R	0x20
#घोषणा	TDES_KEY1W2R	0x24
#घोषणा	TDES_KEY2W1R	0x28
#घोषणा	TDES_KEY2W2R	0x2C
#घोषणा	TDES_KEY3W1R	0x30
#घोषणा	TDES_KEY3W2R	0x34
#घोषणा	TDES_IDATA1R	0x40
#घोषणा	TDES_IDATA2R	0x44
#घोषणा	TDES_ODATA1R	0x50
#घोषणा	TDES_ODATA2R	0x54
#घोषणा	TDES_IV1R		0x60
#घोषणा	TDES_IV2R		0x64

#घोषणा	TDES_XTEARNDR	0x70
#घोषणा	TDES_XTEARNDR_XTEA_RNDS_MASK	(0x3F << 0)
#घोषणा	TDES_XTEARNDR_XTEA_RNDS_OFFSET	0

#घोषणा	TDES_HW_VERSION	0xFC

#घोषणा TDES_RPR		0x100
#घोषणा TDES_RCR		0x104
#घोषणा TDES_TPR		0x108
#घोषणा TDES_TCR		0x10C
#घोषणा TDES_RNPR		0x118
#घोषणा TDES_RNCR		0x11C
#घोषणा TDES_TNPR		0x118
#घोषणा TDES_TNCR		0x11C
#घोषणा TDES_PTCR		0x120
#घोषणा TDES_PTCR_RXTEN			(1 << 0)
#घोषणा TDES_PTCR_RXTDIS		(1 << 1)
#घोषणा TDES_PTCR_TXTEN			(1 << 8)
#घोषणा TDES_PTCR_TXTDIS		(1 << 9)
#घोषणा TDES_PTSR		0x124
#घोषणा TDES_PTSR_RXTEN			(1 << 0)
#घोषणा TDES_PTSR_TXTEN			(1 << 8)

#पूर्ण_अगर /* __ATMEL_TDES_REGS_H__ */
