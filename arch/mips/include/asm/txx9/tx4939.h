<शैली गुरु>
/*
 * Definitions क्रम TX4939
 *
 * Copyright (C) 2000-2001,2005-2006 Toshiba Corporation
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_अघोषित __ASM_TXX9_TX4939_H
#घोषणा __ASM_TXX9_TX4939_H

/* some controllers are compatible with 4927/4938 */
#समावेश <यंत्र/txx9/tx4938.h>

#अगर_घोषित CONFIG_64BIT
#घोषणा TX4939_REG_BASE 0xffffffffff1f0000UL /* == TX4938_REG_BASE */
#अन्यथा
#घोषणा TX4939_REG_BASE 0xff1f0000UL /* == TX4938_REG_BASE */
#पूर्ण_अगर
#घोषणा TX4939_REG_SIZE 0x00010000 /* == TX4938_REG_SIZE */

#घोषणा TX4939_ATA_REG(ch)	(TX4939_REG_BASE + 0x3000 + (ch) * 0x1000)
#घोषणा TX4939_NDFMC_REG	(TX4939_REG_BASE + 0x5000)
#घोषणा TX4939_SRAMC_REG	(TX4939_REG_BASE + 0x6000)
#घोषणा TX4939_CRYPTO_REG	(TX4939_REG_BASE + 0x6800)
#घोषणा TX4939_PCIC1_REG	(TX4939_REG_BASE + 0x7000)
#घोषणा TX4939_DDRC_REG		(TX4939_REG_BASE + 0x8000)
#घोषणा TX4939_EBUSC_REG	(TX4939_REG_BASE + 0x9000)
#घोषणा TX4939_VPC_REG		(TX4939_REG_BASE + 0xa000)
#घोषणा TX4939_DMA_REG(ch)	(TX4939_REG_BASE + 0xb000 + (ch) * 0x800)
#घोषणा TX4939_PCIC_REG		(TX4939_REG_BASE + 0xd000)
#घोषणा TX4939_CCFG_REG		(TX4939_REG_BASE + 0xe000)
#घोषणा TX4939_IRC_REG		(TX4939_REG_BASE + 0xe800)
#घोषणा TX4939_NR_TMR	6	/* 0xf000,0xf100,0xf200,0xfd00,0xfe00,0xff00 */
#घोषणा TX4939_TMR_REG(ch)	\
	(TX4939_REG_BASE + 0xf000 + ((ch) + ((ch) >= 3) * 10) * 0x100)
#घोषणा TX4939_NR_SIO	4	/* 0xf300, 0xf400, 0xf380, 0xf480 */
#घोषणा TX4939_SIO_REG(ch)	\
	(TX4939_REG_BASE + 0xf300 + (((ch) & 1) << 8) + (((ch) & 2) << 6))
#घोषणा TX4939_ACLC_REG		(TX4939_REG_BASE + 0xf700)
#घोषणा TX4939_SPI_REG		(TX4939_REG_BASE + 0xf800)
#घोषणा TX4939_I2C_REG		(TX4939_REG_BASE + 0xf900)
#घोषणा TX4939_I2S_REG		(TX4939_REG_BASE + 0xfa00)
#घोषणा TX4939_RTC_REG		(TX4939_REG_BASE + 0xfb00)
#घोषणा TX4939_CIR_REG		(TX4939_REG_BASE + 0xfc00)

#घोषणा TX4939_RNG_REG		(TX4939_CRYPTO_REG + 0xb0)

काष्ठा tx4939_le_reg अणु
	__u32 r;
	__u32 unused;
पूर्ण;

काष्ठा tx4939_ddrc_reg अणु
	काष्ठा tx4939_le_reg ctl[47];
	__u64 unused0[17];
	__u64 winen;
	__u64 win[4];
पूर्ण;

काष्ठा tx4939_ccfg_reg अणु
	__u64 ccfg;
	__u64 crir;
	__u64 pcfg;
	__u64 toea;
	__u64 clkctr;
	__u64 unused0;
	__u64 garbc;
	__u64 unused1[2];
	__u64 ramp;
	__u64 unused2[2];
	__u64 dskwctrl;
	__u64 mclkosc;
	__u64 mclkctl;
	__u64 unused3[17];
	काष्ठा अणु
		__u64 mr;
		__u64 dr;
	पूर्ण gpio[2];
पूर्ण;

काष्ठा tx4939_irc_reg अणु
	काष्ठा tx4939_le_reg den;
	काष्ठा tx4939_le_reg scipb;
	काष्ठा tx4939_le_reg dm[2];
	काष्ठा tx4939_le_reg lvl[16];
	काष्ठा tx4939_le_reg msk;
	काष्ठा tx4939_le_reg edc;
	काष्ठा tx4939_le_reg pnd0;
	काष्ठा tx4939_le_reg cs;
	काष्ठा tx4939_le_reg pnd1;
	काष्ठा tx4939_le_reg dm2[2];
	काष्ठा tx4939_le_reg dbr[2];
	काष्ठा tx4939_le_reg dben;
	काष्ठा tx4939_le_reg unused0[2];
	काष्ठा tx4939_le_reg flag[2];
	काष्ठा tx4939_le_reg pol;
	काष्ठा tx4939_le_reg cnt;
	काष्ठा tx4939_le_reg maskपूर्णांक;
	काष्ठा tx4939_le_reg maskext;
पूर्ण;

काष्ठा tx4939_crypto_reg अणु
	काष्ठा tx4939_le_reg csr;
	काष्ठा tx4939_le_reg idesptr;
	काष्ठा tx4939_le_reg cdesptr;
	काष्ठा tx4939_le_reg buserr;
	काष्ठा tx4939_le_reg cip_tout;
	काष्ठा tx4939_le_reg cir;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा tx4939_le_reg data[8];
			काष्ठा tx4939_le_reg ctrl;
		पूर्ण gen;
		काष्ठा अणु
			काष्ठा अणु
				काष्ठा tx4939_le_reg l;
				काष्ठा tx4939_le_reg u;
			पूर्ण key[3], ini;
			काष्ठा tx4939_le_reg ctrl;
		पूर्ण des;
		काष्ठा अणु
			काष्ठा tx4939_le_reg key[4];
			काष्ठा tx4939_le_reg ini[4];
			काष्ठा tx4939_le_reg ctrl;
		पूर्ण aes;
		काष्ठा अणु
			काष्ठा अणु
				काष्ठा tx4939_le_reg l;
				काष्ठा tx4939_le_reg u;
			पूर्ण cnt;
			काष्ठा tx4939_le_reg ini[5];
			काष्ठा tx4939_le_reg unused;
			काष्ठा tx4939_le_reg ctrl;
		पूर्ण hash;
	पूर्ण cdr;
	काष्ठा tx4939_le_reg unused0[7];
	काष्ठा tx4939_le_reg rcsr;
	काष्ठा tx4939_le_reg rpr;
	__u64 rdr;
	__u64 ror[3];
	काष्ठा tx4939_le_reg unused1[2];
	काष्ठा tx4939_le_reg xorslr;
	काष्ठा tx4939_le_reg xorsur;
पूर्ण;

काष्ठा tx4939_crypto_desc अणु
	__u32 src;
	__u32 dst;
	__u32 next;
	__u32 ctrl;
	__u32 index;
	__u32 xor;
पूर्ण;

काष्ठा tx4939_vpc_reg अणु
	काष्ठा tx4939_le_reg csr;
	काष्ठा अणु
		काष्ठा tx4939_le_reg ctrlA;
		काष्ठा tx4939_le_reg ctrlB;
		काष्ठा tx4939_le_reg idesptr;
		काष्ठा tx4939_le_reg cdesptr;
	पूर्ण port[3];
	काष्ठा tx4939_le_reg buserr;
पूर्ण;

काष्ठा tx4939_vpc_desc अणु
	__u32 src;
	__u32 next;
	__u32 ctrl1;
	__u32 ctrl2;
पूर्ण;

/*
 * IRC
 */
#घोषणा TX4939_IR_NONE	0
#घोषणा TX4939_IR_DDR	1
#घोषणा TX4939_IR_WTOERR	2
#घोषणा TX4939_NUM_IR_INT	3
#घोषणा TX4939_IR_INT(n)	(3 + (n))
#घोषणा TX4939_NUM_IR_ETH	2
#घोषणा TX4939_IR_ETH(n)	((n) ? 43 : 6)
#घोषणा TX4939_IR_VIDEO 7
#घोषणा TX4939_IR_CIR	8
#घोषणा TX4939_NUM_IR_SIO	4
#घोषणा TX4939_IR_SIO(n)	((n) ? 43 + (n) : 9)	/* 9,44-46 */
#घोषणा TX4939_NUM_IR_DMA	4
#घोषणा TX4939_IR_DMA(ch, n)	(((ch) ? 22 : 10) + (n)) /* 10-13,22-25 */
#घोषणा TX4939_IR_IRC	14
#घोषणा TX4939_IR_PDMAC 15
#घोषणा TX4939_NUM_IR_TMR	6
#घोषणा TX4939_IR_TMR(n)	(((n) >= 3 ? 45 : 16) + (n)) /* 16-18,48-50 */
#घोषणा TX4939_NUM_IR_ATA	2
#घोषणा TX4939_IR_ATA(n)	(19 + (n))
#घोषणा TX4939_IR_ACLC	21
#घोषणा TX4939_IR_CIPHER	26
#घोषणा TX4939_IR_INTA	27
#घोषणा TX4939_IR_INTB	28
#घोषणा TX4939_IR_INTC	29
#घोषणा TX4939_IR_INTD	30
#घोषणा TX4939_IR_I2C	33
#घोषणा TX4939_IR_SPI	34
#घोषणा TX4939_IR_PCIC	35
#घोषणा TX4939_IR_PCIC1 36
#घोषणा TX4939_IR_PCIERR	37
#घोषणा TX4939_IR_PCIPME	38
#घोषणा TX4939_IR_NDFMC 39
#घोषणा TX4939_IR_ACLCPME	40
#घोषणा TX4939_IR_RTC	41
#घोषणा TX4939_IR_RND	42
#घोषणा TX4939_IR_I2S	47
#घोषणा TX4939_NUM_IR	64

#घोषणा TX4939_IRC_INT	2	/* IP[2] in Status रेजिस्टर */

/*
 * CCFG
 */
/* CCFG : Chip Configuration */
#घोषणा TX4939_CCFG_PCIBOOT	0x0000040000000000ULL
#घोषणा TX4939_CCFG_WDRST	0x0000020000000000ULL
#घोषणा TX4939_CCFG_WDREXEN	0x0000010000000000ULL
#घोषणा TX4939_CCFG_BCFG_MASK	0x000000ff00000000ULL
#घोषणा TX4939_CCFG_GTOT_MASK	0x06000000
#घोषणा TX4939_CCFG_GTOT_4096	0x06000000
#घोषणा TX4939_CCFG_GTOT_2048	0x04000000
#घोषणा TX4939_CCFG_GTOT_1024	0x02000000
#घोषणा TX4939_CCFG_GTOT_512	0x00000000
#घोषणा TX4939_CCFG_TINTDIS	0x01000000
#घोषणा TX4939_CCFG_PCI66	0x00800000
#घोषणा TX4939_CCFG_PCIMODE	0x00400000
#घोषणा TX4939_CCFG_SSCG	0x00100000
#घोषणा TX4939_CCFG_MULCLK_MASK 0x000e0000
#घोषणा TX4939_CCFG_MULCLK_8	(0x7 << 17)
#घोषणा TX4939_CCFG_MULCLK_9	(0x0 << 17)
#घोषणा TX4939_CCFG_MULCLK_10	(0x1 << 17)
#घोषणा TX4939_CCFG_MULCLK_11	(0x2 << 17)
#घोषणा TX4939_CCFG_MULCLK_12	(0x3 << 17)
#घोषणा TX4939_CCFG_MULCLK_13	(0x4 << 17)
#घोषणा TX4939_CCFG_MULCLK_14	(0x5 << 17)
#घोषणा TX4939_CCFG_MULCLK_15	(0x6 << 17)
#घोषणा TX4939_CCFG_BEOW	0x00010000
#घोषणा TX4939_CCFG_WR	0x00008000
#घोषणा TX4939_CCFG_TOE 0x00004000
#घोषणा TX4939_CCFG_PCIARB	0x00002000
#घोषणा TX4939_CCFG_YDIVMODE_MASK	0x00001c00
#घोषणा TX4939_CCFG_YDIVMODE_2	(0x0 << 10)
#घोषणा TX4939_CCFG_YDIVMODE_3	(0x1 << 10)
#घोषणा TX4939_CCFG_YDIVMODE_5	(0x6 << 10)
#घोषणा TX4939_CCFG_YDIVMODE_6	(0x7 << 10)
#घोषणा TX4939_CCFG_PTSEL	0x00000200
#घोषणा TX4939_CCFG_BESEL	0x00000100
#घोषणा TX4939_CCFG_SYSSP_MASK	0x000000c0
#घोषणा TX4939_CCFG_ACKSEL	0x00000020
#घोषणा TX4939_CCFG_ROMW	0x00000010
#घोषणा TX4939_CCFG_ENDIAN	0x00000004
#घोषणा TX4939_CCFG_ARMODE	0x00000002
#घोषणा TX4939_CCFG_ACEHOLD	0x00000001

/* PCFG : Pin Configuration */
#घोषणा TX4939_PCFG_SIO2MODE_MASK	0xc000000000000000ULL
#घोषणा TX4939_PCFG_SIO2MODE_GPIO	0x8000000000000000ULL
#घोषणा TX4939_PCFG_SIO2MODE_SIO2	0x4000000000000000ULL
#घोषणा TX4939_PCFG_SIO2MODE_SIO0	0x0000000000000000ULL
#घोषणा TX4939_PCFG_SPIMODE	0x2000000000000000ULL
#घोषणा TX4939_PCFG_I2CMODE	0x1000000000000000ULL
#घोषणा TX4939_PCFG_I2SMODE_MASK	0x0c00000000000000ULL
#घोषणा TX4939_PCFG_I2SMODE_GPIO	0x0c00000000000000ULL
#घोषणा TX4939_PCFG_I2SMODE_I2S 0x0800000000000000ULL
#घोषणा TX4939_PCFG_I2SMODE_I2S_ALT	0x0400000000000000ULL
#घोषणा TX4939_PCFG_I2SMODE_ACLC	0x0000000000000000ULL
#घोषणा TX4939_PCFG_SIO3MODE	0x0200000000000000ULL
#घोषणा TX4939_PCFG_DMASEL3	0x0004000000000000ULL
#घोषणा TX4939_PCFG_DMASEL3_SIO0	0x0004000000000000ULL
#घोषणा TX4939_PCFG_DMASEL3_NDFC	0x0000000000000000ULL
#घोषणा TX4939_PCFG_VSSMODE	0x0000200000000000ULL
#घोषणा TX4939_PCFG_VPSMODE	0x0000100000000000ULL
#घोषणा TX4939_PCFG_ET1MODE	0x0000080000000000ULL
#घोषणा TX4939_PCFG_ET0MODE	0x0000040000000000ULL
#घोषणा TX4939_PCFG_ATA1MODE	0x0000020000000000ULL
#घोषणा TX4939_PCFG_ATA0MODE	0x0000010000000000ULL
#घोषणा TX4939_PCFG_BP_PLL	0x0000000100000000ULL

#घोषणा TX4939_PCFG_SYSCLKEN	0x08000000
#घोषणा TX4939_PCFG_PCICLKEN_ALL	0x000f0000
#घोषणा TX4939_PCFG_PCICLKEN(ch)	(0x00010000<<(ch))
#घोषणा TX4939_PCFG_SPEED1	0x00002000
#घोषणा TX4939_PCFG_SPEED0	0x00001000
#घोषणा TX4939_PCFG_ITMODE	0x00000300
#घोषणा TX4939_PCFG_DMASEL_ALL	(0x00000007 | TX4939_PCFG_DMASEL3)
#घोषणा TX4939_PCFG_DMASEL2	0x00000004
#घोषणा TX4939_PCFG_DMASEL2_DRQ2	0x00000000
#घोषणा TX4939_PCFG_DMASEL2_SIO0	0x00000004
#घोषणा TX4939_PCFG_DMASEL1	0x00000002
#घोषणा TX4939_PCFG_DMASEL1_DRQ1	0x00000000
#घोषणा TX4939_PCFG_DMASEL0	0x00000001
#घोषणा TX4939_PCFG_DMASEL0_DRQ0	0x00000000

/* CLKCTR : Clock Control */
#घोषणा TX4939_CLKCTR_IOSCKD	0x8000000000000000ULL
#घोषणा TX4939_CLKCTR_SYSCKD	0x4000000000000000ULL
#घोषणा TX4939_CLKCTR_TM5CKD	0x2000000000000000ULL
#घोषणा TX4939_CLKCTR_TM4CKD	0x1000000000000000ULL
#घोषणा TX4939_CLKCTR_TM3CKD	0x0800000000000000ULL
#घोषणा TX4939_CLKCTR_CIRCKD	0x0400000000000000ULL
#घोषणा TX4939_CLKCTR_SIO3CKD	0x0200000000000000ULL
#घोषणा TX4939_CLKCTR_SIO2CKD	0x0100000000000000ULL
#घोषणा TX4939_CLKCTR_SIO1CKD	0x0080000000000000ULL
#घोषणा TX4939_CLKCTR_VPCCKD	0x0040000000000000ULL
#घोषणा TX4939_CLKCTR_EPCICKD	0x0020000000000000ULL
#घोषणा TX4939_CLKCTR_ETH1CKD	0x0008000000000000ULL
#घोषणा TX4939_CLKCTR_ATA1CKD	0x0004000000000000ULL
#घोषणा TX4939_CLKCTR_BROMCKD	0x0002000000000000ULL
#घोषणा TX4939_CLKCTR_NDCCKD	0x0001000000000000ULL
#घोषणा TX4939_CLKCTR_I2CCKD	0x0000800000000000ULL
#घोषणा TX4939_CLKCTR_ETH0CKD	0x0000400000000000ULL
#घोषणा TX4939_CLKCTR_SPICKD	0x0000200000000000ULL
#घोषणा TX4939_CLKCTR_SRAMCKD	0x0000100000000000ULL
#घोषणा TX4939_CLKCTR_PCI1CKD	0x0000080000000000ULL
#घोषणा TX4939_CLKCTR_DMA1CKD	0x0000040000000000ULL
#घोषणा TX4939_CLKCTR_ACLCKD	0x0000020000000000ULL
#घोषणा TX4939_CLKCTR_ATA0CKD	0x0000010000000000ULL
#घोषणा TX4939_CLKCTR_DMA0CKD	0x0000008000000000ULL
#घोषणा TX4939_CLKCTR_PCICCKD	0x0000004000000000ULL
#घोषणा TX4939_CLKCTR_I2SCKD	0x0000002000000000ULL
#घोषणा TX4939_CLKCTR_TM0CKD	0x0000001000000000ULL
#घोषणा TX4939_CLKCTR_TM1CKD	0x0000000800000000ULL
#घोषणा TX4939_CLKCTR_TM2CKD	0x0000000400000000ULL
#घोषणा TX4939_CLKCTR_SIO0CKD	0x0000000200000000ULL
#घोषणा TX4939_CLKCTR_CYPCKD	0x0000000100000000ULL
#घोषणा TX4939_CLKCTR_IOSRST	0x80000000
#घोषणा TX4939_CLKCTR_SYSRST	0x40000000
#घोषणा TX4939_CLKCTR_TM5RST	0x20000000
#घोषणा TX4939_CLKCTR_TM4RST	0x10000000
#घोषणा TX4939_CLKCTR_TM3RST	0x08000000
#घोषणा TX4939_CLKCTR_CIRRST	0x04000000
#घोषणा TX4939_CLKCTR_SIO3RST	0x02000000
#घोषणा TX4939_CLKCTR_SIO2RST	0x01000000
#घोषणा TX4939_CLKCTR_SIO1RST	0x00800000
#घोषणा TX4939_CLKCTR_VPCRST	0x00400000
#घोषणा TX4939_CLKCTR_EPCIRST	0x00200000
#घोषणा TX4939_CLKCTR_ETH1RST	0x00080000
#घोषणा TX4939_CLKCTR_ATA1RST	0x00040000
#घोषणा TX4939_CLKCTR_BROMRST	0x00020000
#घोषणा TX4939_CLKCTR_NDCRST	0x00010000
#घोषणा TX4939_CLKCTR_I2CRST	0x00008000
#घोषणा TX4939_CLKCTR_ETH0RST	0x00004000
#घोषणा TX4939_CLKCTR_SPIRST	0x00002000
#घोषणा TX4939_CLKCTR_SRAMRST	0x00001000
#घोषणा TX4939_CLKCTR_PCI1RST	0x00000800
#घोषणा TX4939_CLKCTR_DMA1RST	0x00000400
#घोषणा TX4939_CLKCTR_ACLRST	0x00000200
#घोषणा TX4939_CLKCTR_ATA0RST	0x00000100
#घोषणा TX4939_CLKCTR_DMA0RST	0x00000080
#घोषणा TX4939_CLKCTR_PCICRST	0x00000040
#घोषणा TX4939_CLKCTR_I2SRST	0x00000020
#घोषणा TX4939_CLKCTR_TM0RST	0x00000010
#घोषणा TX4939_CLKCTR_TM1RST	0x00000008
#घोषणा TX4939_CLKCTR_TM2RST	0x00000004
#घोषणा TX4939_CLKCTR_SIO0RST	0x00000002
#घोषणा TX4939_CLKCTR_CYPRST	0x00000001

/*
 * CRYPTO
 */
#घोषणा TX4939_CRYPTO_CSR_SAESO 0x08000000
#घोषणा TX4939_CRYPTO_CSR_SAESI 0x04000000
#घोषणा TX4939_CRYPTO_CSR_SDESO 0x02000000
#घोषणा TX4939_CRYPTO_CSR_SDESI 0x01000000
#घोषणा TX4939_CRYPTO_CSR_INDXBST_MASK	0x00700000
#घोषणा TX4939_CRYPTO_CSR_INDXBST(n)	((n) << 20)
#घोषणा TX4939_CRYPTO_CSR_TOINT 0x00080000
#घोषणा TX4939_CRYPTO_CSR_DCINT 0x00040000
#घोषणा TX4939_CRYPTO_CSR_GBINT 0x00010000
#घोषणा TX4939_CRYPTO_CSR_INDXAST_MASK	0x0000e000
#घोषणा TX4939_CRYPTO_CSR_INDXAST(n)	((n) << 13)
#घोषणा TX4939_CRYPTO_CSR_CSWAP_MASK	0x00001800
#घोषणा TX4939_CRYPTO_CSR_CSWAP_NONE	0x00000000
#घोषणा TX4939_CRYPTO_CSR_CSWAP_IN	0x00000800
#घोषणा TX4939_CRYPTO_CSR_CSWAP_OUT	0x00001000
#घोषणा TX4939_CRYPTO_CSR_CSWAP_BOTH	0x00001800
#घोषणा TX4939_CRYPTO_CSR_CDIV_MASK	0x00000600
#घोषणा TX4939_CRYPTO_CSR_CDIV_DIV2	0x00000000
#घोषणा TX4939_CRYPTO_CSR_CDIV_DIV1	0x00000200
#घोषणा TX4939_CRYPTO_CSR_CDIV_DIV2ALT	0x00000400
#घोषणा TX4939_CRYPTO_CSR_CDIV_DIV1ALT	0x00000600
#घोषणा TX4939_CRYPTO_CSR_PDINT_MASK	0x000000c0
#घोषणा TX4939_CRYPTO_CSR_PDINT_ALL	0x00000000
#घोषणा TX4939_CRYPTO_CSR_PDINT_END	0x00000040
#घोषणा TX4939_CRYPTO_CSR_PDINT_NEXT	0x00000080
#घोषणा TX4939_CRYPTO_CSR_PDINT_NONE	0x000000c0
#घोषणा TX4939_CRYPTO_CSR_GINTE 0x00000008
#घोषणा TX4939_CRYPTO_CSR_RSTD	0x00000004
#घोषणा TX4939_CRYPTO_CSR_RSTC	0x00000002
#घोषणा TX4939_CRYPTO_CSR_ENCR	0x00000001

/* bits क्रम tx4939_crypto_reg.cdr.gen.ctrl */
#घोषणा TX4939_CRYPTO_CTX_ENGINE_MASK	0x00000003
#घोषणा TX4939_CRYPTO_CTX_ENGINE_DES	0x00000000
#घोषणा TX4939_CRYPTO_CTX_ENGINE_AES	0x00000001
#घोषणा TX4939_CRYPTO_CTX_ENGINE_MD5	0x00000002
#घोषणा TX4939_CRYPTO_CTX_ENGINE_SHA1	0x00000003
#घोषणा TX4939_CRYPTO_CTX_TDMS	0x00000010
#घोषणा TX4939_CRYPTO_CTX_CMS	0x00000020
#घोषणा TX4939_CRYPTO_CTX_DMS	0x00000040
#घोषणा TX4939_CRYPTO_CTX_UPDATE	0x00000080

/* bits क्रम tx4939_crypto_desc.ctrl */
#घोषणा TX4939_CRYPTO_DESC_OB_CNT_MASK	0xffe00000
#घोषणा TX4939_CRYPTO_DESC_OB_CNT(cnt)	((cnt) << 21)
#घोषणा TX4939_CRYPTO_DESC_IB_CNT_MASK	0x001ffc00
#घोषणा TX4939_CRYPTO_DESC_IB_CNT(cnt)	((cnt) << 10)
#घोषणा TX4939_CRYPTO_DESC_START	0x00000200
#घोषणा TX4939_CRYPTO_DESC_END	0x00000100
#घोषणा TX4939_CRYPTO_DESC_XOR	0x00000010
#घोषणा TX4939_CRYPTO_DESC_LAST 0x00000008
#घोषणा TX4939_CRYPTO_DESC_ERR_MASK	0x00000006
#घोषणा TX4939_CRYPTO_DESC_ERR_NONE	0x00000000
#घोषणा TX4939_CRYPTO_DESC_ERR_TOUT	0x00000002
#घोषणा TX4939_CRYPTO_DESC_ERR_DIGEST	0x00000004
#घोषणा TX4939_CRYPTO_DESC_OWN	0x00000001

/* bits क्रम tx4939_crypto_desc.index */
#घोषणा TX4939_CRYPTO_DESC_HASH_IDX_MASK	0x00000070
#घोषणा TX4939_CRYPTO_DESC_HASH_IDX(idx)	((idx) << 4)
#घोषणा TX4939_CRYPTO_DESC_ENCRYPT_IDX_MASK	0x00000007
#घोषणा TX4939_CRYPTO_DESC_ENCRYPT_IDX(idx)	((idx) << 0)

#घोषणा TX4939_CRYPTO_NR_SET	6

#घोषणा TX4939_CRYPTO_RCSR_INTE 0x00000008
#घोषणा TX4939_CRYPTO_RCSR_RST	0x00000004
#घोषणा TX4939_CRYPTO_RCSR_FIN	0x00000002
#घोषणा TX4939_CRYPTO_RCSR_ST	0x00000001

/*
 * VPC
 */
#घोषणा TX4939_VPC_CSR_GBINT	0x00010000
#घोषणा TX4939_VPC_CSR_SWAPO	0x00000020
#घोषणा TX4939_VPC_CSR_SWAPI	0x00000010
#घोषणा TX4939_VPC_CSR_GINTE	0x00000008
#घोषणा TX4939_VPC_CSR_RSTD	0x00000004
#घोषणा TX4939_VPC_CSR_RSTVPC	0x00000002

#घोषणा TX4939_VPC_CTRLA_VDPSN	0x00000200
#घोषणा TX4939_VPC_CTRLA_PBUSY	0x00000100
#घोषणा TX4939_VPC_CTRLA_DCINT	0x00000080
#घोषणा TX4939_VPC_CTRLA_UOINT	0x00000040
#घोषणा TX4939_VPC_CTRLA_PDINT_MASK	0x00000030
#घोषणा TX4939_VPC_CTRLA_PDINT_ALL	0x00000000
#घोषणा TX4939_VPC_CTRLA_PDINT_NEXT	0x00000010
#घोषणा TX4939_VPC_CTRLA_PDINT_NONE	0x00000030
#घोषणा TX4939_VPC_CTRLA_VDVLDP 0x00000008
#घोषणा TX4939_VPC_CTRLA_VDMODE 0x00000004
#घोषणा TX4939_VPC_CTRLA_VDFOR	0x00000002
#घोषणा TX4939_VPC_CTRLA_ENVPC	0x00000001

/* bits क्रम tx4939_vpc_desc.ctrl1 */
#घोषणा TX4939_VPC_DESC_CTRL1_ERR_MASK	0x00000006
#घोषणा TX4939_VPC_DESC_CTRL1_OWN	0x00000001

#घोषणा tx4939_ddrcptr	((काष्ठा tx4939_ddrc_reg __iomem *)TX4939_DDRC_REG)
#घोषणा tx4939_ebuscptr		tx4938_ebuscptr
#घोषणा tx4939_ircptr \
		((काष्ठा tx4939_irc_reg __iomem *)TX4939_IRC_REG)
#घोषणा tx4939_pcicptr		tx4938_pcicptr
#घोषणा tx4939_pcic1ptr		tx4938_pcic1ptr
#घोषणा tx4939_ccfgptr \
		((काष्ठा tx4939_ccfg_reg __iomem *)TX4939_CCFG_REG)
#घोषणा tx4939_sramcptr		tx4938_sramcptr
#घोषणा tx4939_cryptoptr \
		((काष्ठा tx4939_crypto_reg __iomem *)TX4939_CRYPTO_REG)
#घोषणा tx4939_vpcptr	((काष्ठा tx4939_vpc_reg __iomem *)TX4939_VPC_REG)

#घोषणा TX4939_REV_MAJ_MIN()	\
	((__u32)__raw_पढ़ोq(&tx4939_ccfgptr->crir) & 0x00ff)
#घोषणा TX4939_REV_PCODE()	\
	((__u32)__raw_पढ़ोq(&tx4939_ccfgptr->crir) >> 16)
#घोषणा TX4939_CCFG_BCFG()	\
	((__u32)((__raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_BCFG_MASK) \
		 >> 32))

#घोषणा tx4939_ccfg_clear(bits) tx4938_ccfg_clear(bits)
#घोषणा tx4939_ccfg_set(bits)	tx4938_ccfg_set(bits)
#घोषणा tx4939_ccfg_change(change, new) tx4938_ccfg_change(change, new)

#घोषणा TX4939_EBUSC_CR(ch)	TX4927_EBUSC_CR(ch)
#घोषणा TX4939_EBUSC_BA(ch)	TX4927_EBUSC_BA(ch)
#घोषणा TX4939_EBUSC_SIZE(ch)	TX4927_EBUSC_SIZE(ch)
#घोषणा TX4939_EBUSC_WIDTH(ch)	\
	(16 >> ((__u32)(TX4939_EBUSC_CR(ch) >> 20) & 0x1))

/* SCLK0 = MSTCLK * 429/19 * 16/245 / 2	 (14.745MHz क्रम MST 20MHz) */
#घोषणा TX4939_SCLK0(mst)	\
	((((mst) + 245/2) / 245UL * 429 * 16 + 19) / 19 / 2)

व्योम tx4939_wdt_init(व्योम);
व्योम tx4939_setup(व्योम);
व्योम tx4939_समय_init(अचिन्हित पूर्णांक पंचांगrnr);
व्योम tx4939_sio_init(अचिन्हित पूर्णांक sclk, अचिन्हित पूर्णांक cts_mask);
व्योम tx4939_spi_init(पूर्णांक busid);
व्योम tx4939_ethaddr_init(अचिन्हित अक्षर *addr0, अचिन्हित अक्षर *addr1);
पूर्णांक tx4939_report_pciclk(व्योम);
व्योम tx4939_report_pci1clk(व्योम);
काष्ठा pci_dev;
पूर्णांक tx4939_pcic1_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot);
पूर्णांक tx4939_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);
व्योम tx4939_setup_pcierr_irq(व्योम);
व्योम tx4939_irq_init(व्योम);
पूर्णांक tx4939_irq(व्योम);
व्योम tx4939_mtd_init(पूर्णांक ch);
व्योम tx4939_ata_init(व्योम);
व्योम tx4939_rtc_init(व्योम);
व्योम tx4939_ndfmc_init(अचिन्हित पूर्णांक hold, अचिन्हित पूर्णांक spw,
		       अचिन्हित अक्षर ch_mask, अचिन्हित अक्षर wide_mask);
व्योम tx4939_dmac_init(पूर्णांक स_नकल_chan0, पूर्णांक स_नकल_chan1);
व्योम tx4939_aclc_init(व्योम);
व्योम tx4939_sramc_init(व्योम);
व्योम tx4939_rng_init(व्योम);

#पूर्ण_अगर /* __ASM_TXX9_TX4939_H */
