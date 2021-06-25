<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ATMEL_AES_REGS_H__
#घोषणा __ATMEL_AES_REGS_H__

#घोषणा AES_CR			0x00
#घोषणा AES_CR_START		(1 << 0)
#घोषणा AES_CR_SWRST		(1 << 8)
#घोषणा AES_CR_LOADSEED		(1 << 16)

#घोषणा	AES_MR			0x04
#घोषणा AES_MR_CYPHER_DEC		(0 << 0)
#घोषणा AES_MR_CYPHER_ENC		(1 << 0)
#घोषणा AES_MR_GTAGEN			(1 << 1)
#घोषणा	AES_MR_DUALBUFF			(1 << 3)
#घोषणा AES_MR_PROCDLY_MASK		(0xF << 4)
#घोषणा AES_MR_PROCDLY_OFFSET	4
#घोषणा AES_MR_SMOD_MASK		(0x3 << 8)
#घोषणा AES_MR_SMOD_MANUAL		(0x0 << 8)
#घोषणा AES_MR_SMOD_AUTO		(0x1 << 8)
#घोषणा AES_MR_SMOD_IDATAR0		(0x2 << 8)
#घोषणा	AES_MR_KEYSIZE_MASK		(0x3 << 10)
#घोषणा	AES_MR_KEYSIZE_128		(0x0 << 10)
#घोषणा	AES_MR_KEYSIZE_192		(0x1 << 10)
#घोषणा	AES_MR_KEYSIZE_256		(0x2 << 10)
#घोषणा AES_MR_OPMOD_MASK		(0x7 << 12)
#घोषणा AES_MR_OPMOD_ECB		(0x0 << 12)
#घोषणा AES_MR_OPMOD_CBC		(0x1 << 12)
#घोषणा AES_MR_OPMOD_OFB		(0x2 << 12)
#घोषणा AES_MR_OPMOD_CFB		(0x3 << 12)
#घोषणा AES_MR_OPMOD_CTR		(0x4 << 12)
#घोषणा AES_MR_OPMOD_GCM		(0x5 << 12)
#घोषणा AES_MR_OPMOD_XTS		(0x6 << 12)
#घोषणा AES_MR_LOD				(0x1 << 15)
#घोषणा AES_MR_CFBS_MASK		(0x7 << 16)
#घोषणा AES_MR_CFBS_128b		(0x0 << 16)
#घोषणा AES_MR_CFBS_64b			(0x1 << 16)
#घोषणा AES_MR_CFBS_32b			(0x2 << 16)
#घोषणा AES_MR_CFBS_16b			(0x3 << 16)
#घोषणा AES_MR_CFBS_8b			(0x4 << 16)
#घोषणा AES_MR_CKEY_MASK		(0xF << 20)
#घोषणा AES_MR_CKEY_OFFSET		20
#घोषणा AES_MR_CMTYP_MASK		(0x1F << 24)
#घोषणा AES_MR_CMTYP_OFFSET		24

#घोषणा	AES_IER		0x10
#घोषणा	AES_IDR		0x14
#घोषणा	AES_IMR		0x18
#घोषणा	AES_ISR		0x1C
#घोषणा AES_INT_DATARDY		(1 << 0)
#घोषणा AES_INT_URAD		(1 << 8)
#घोषणा AES_INT_TAGRDY		(1 << 16)
#घोषणा AES_ISR_URAT_MASK	(0xF << 12)
#घोषणा AES_ISR_URAT_IDR_WR_PROC	(0x0 << 12)
#घोषणा AES_ISR_URAT_ODR_RD_PROC	(0x1 << 12)
#घोषणा AES_ISR_URAT_MR_WR_PROC		(0x2 << 12)
#घोषणा AES_ISR_URAT_ODR_RD_SUBK	(0x3 << 12)
#घोषणा AES_ISR_URAT_MR_WR_SUBK		(0x4 << 12)
#घोषणा AES_ISR_URAT_WOR_RD			(0x5 << 12)

#घोषणा AES_KEYWR(x)	(0x20 + ((x) * 0x04))
#घोषणा AES_IDATAR(x)	(0x40 + ((x) * 0x04))
#घोषणा AES_ODATAR(x)	(0x50 + ((x) * 0x04))
#घोषणा AES_IVR(x)		(0x60 + ((x) * 0x04))

#घोषणा AES_AADLENR	0x70
#घोषणा AES_CLENR	0x74
#घोषणा AES_GHASHR(x)	(0x78 + ((x) * 0x04))
#घोषणा AES_TAGR(x)	(0x88 + ((x) * 0x04))
#घोषणा AES_CTRR	0x98
#घोषणा AES_GCMHR(x)	(0x9c + ((x) * 0x04))

#घोषणा AES_EMR		0xb0
#घोषणा AES_EMR_APEN		BIT(0)	/* Auto Padding Enable */
#घोषणा AES_EMR_APM		BIT(1)	/* Auto Padding Mode */
#घोषणा AES_EMR_APM_IPSEC	0x0
#घोषणा AES_EMR_APM_SSL		BIT(1)
#घोषणा AES_EMR_PLIPEN		BIT(4)	/* PLIP Enable */
#घोषणा AES_EMR_PLIPD		BIT(5)	/* PLIP Decipher */
#घोषणा AES_EMR_PADLEN_MASK	(0xFu << 8)
#घोषणा AES_EMR_PADLEN_OFFSET	8
#घोषणा AES_EMR_PADLEN(padlen)	(((padlen) << AES_EMR_PADLEN_OFFSET) &\
				 AES_EMR_PADLEN_MASK)
#घोषणा AES_EMR_NHEAD_MASK	(0xFu << 16)
#घोषणा AES_EMR_NHEAD_OFFSET	16
#घोषणा AES_EMR_NHEAD(nhead)	(((nhead) << AES_EMR_NHEAD_OFFSET) &\
				 AES_EMR_NHEAD_MASK)

#घोषणा AES_TWR(x)	(0xc0 + ((x) * 0x04))
#घोषणा AES_ALPHAR(x)	(0xd0 + ((x) * 0x04))

#घोषणा AES_HW_VERSION	0xFC

#पूर्ण_अगर /* __ATMEL_AES_REGS_H__ */
