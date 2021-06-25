<शैली गुरु>
/*
 * 440SPe's XOR engines support header file
 *
 * 2006-2009 (C) DENX Software Engineering.
 *
 * Author: Yuri Tikhonov <yur@emcraft.com>
 *
 * This file is licensed under the term of  the GNU General Public License
 * version 2. The program licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित _PPC440SPE_XOR_H
#घोषणा _PPC440SPE_XOR_H

#समावेश <linux/types.h>

/* Number of XOR engines available on the contoller */
#घोषणा XOR_ENGINES_NUM		1

/* Number of opeअक्रमs supported in the h/w */
#घोषणा XOR_MAX_OPS		16

/*
 * XOR Command Block Control Register bits
 */
#घोषणा XOR_CBCR_LNK_BIT        (1<<31) /* link present */
#घोषणा XOR_CBCR_TGT_BIT        (1<<30) /* target present */
#घोषणा XOR_CBCR_CBCE_BIT       (1<<29) /* command block compete enable */
#घोषणा XOR_CBCR_RNZE_BIT       (1<<28) /* result not zero enable */
#घोषणा XOR_CBCR_XNOR_BIT       (1<<15) /* XOR/XNOR */
#घोषणा XOR_CDCR_OAC_MSK        (0x7F)  /* opeअक्रम address count */

/*
 * XORCore Status Register bits
 */
#घोषणा XOR_SR_XCP_BIT		(1<<31)	/* core processing */
#घोषणा XOR_SR_ICB_BIT		(1<<17)	/* invalid CB */
#घोषणा XOR_SR_IC_BIT		(1<<16)	/* invalid command */
#घोषणा XOR_SR_IPE_BIT		(1<<15)	/* पूर्णांकernal parity error */
#घोषणा XOR_SR_RNZ_BIT		(1<<2)	/* result not Zero */
#घोषणा XOR_SR_CBC_BIT		(1<<1)	/* CB complete */
#घोषणा XOR_SR_CBLC_BIT		(1<<0)	/* CB list complete */

/*
 * XORCore Control Set and Reset Register bits
 */
#घोषणा XOR_CRSR_XASR_BIT	(1<<31)	/* soft reset */
#घोषणा XOR_CRSR_XAE_BIT	(1<<30)	/* enable */
#घोषणा XOR_CRSR_RCBE_BIT	(1<<29)	/* refetch CB enable */
#घोषणा XOR_CRSR_PAUS_BIT	(1<<28)	/* छोड़ो */
#घोषणा XOR_CRSR_64BA_BIT	(1<<27) /* 64/32 CB क्रमmat */
#घोषणा XOR_CRSR_CLP_BIT	(1<<25)	/* जारी list processing */

/*
 * XORCore Interrupt Enable Register
 */
#घोषणा XOR_IE_ICBIE_BIT	(1<<17)	/* Invalid Command Block IRQ Enable */
#घोषणा XOR_IE_ICIE_BIT		(1<<16)	/* Invalid Command IRQ Enable */
#घोषणा XOR_IE_RPTIE_BIT	(1<<14)	/* Read PLB Timeout Error IRQ Enable */
#घोषणा XOR_IE_CBCIE_BIT	(1<<1)	/* CB complete पूर्णांकerrupt enable */
#घोषणा XOR_IE_CBLCI_BIT	(1<<0)	/* CB list complete पूर्णांकerrupt enable */

/*
 * XOR Accelerator engine Command Block Type
 */
काष्ठा xor_cb अणु
	/*
	 * Basic 64-bit क्रमmat XOR CB (Table 19-1, p.463, 440spe_um_1_22.pdf)
	 */
	u32	cbc;		/* control */
	u32	cbbc;		/* byte count */
	u32	cbs;		/* status */
	u8	pad0[4];	/* reserved */
	u32	cbtah;		/* target address high */
	u32	cbtal;		/* target address low */
	u32	cblah;		/* link address high */
	u32	cblal;		/* link address low */
	काष्ठा अणु
		u32 h;
		u32 l;
	पूर्ण __attribute__ ((packed)) ops[16];
पूर्ण __attribute__ ((packed));

/*
 * XOR hardware रेजिस्टरs Table 19-3, UM 1.22
 */
काष्ठा xor_regs अणु
	u32	op_ar[16][2];	/* opeअक्रम address[0]-high,[1]-low रेजिस्टरs */
	u8	pad0[352];	/* reserved */
	u32	cbcr;		/* CB control रेजिस्टर */
	u32	cbbcr;		/* CB byte count रेजिस्टर */
	u32	cbsr;		/* CB status रेजिस्टर */
	u8	pad1[4];	/* reserved */
	u32	cbtahr;		/* opeअक्रम target address high रेजिस्टर */
	u32	cbtalr;		/* opeअक्रम target address low रेजिस्टर */
	u32	cblahr;		/* CB link address high रेजिस्टर */
	u32	cblalr;		/* CB link address low रेजिस्टर */
	u32	crsr;		/* control set रेजिस्टर */
	u32	crrr;		/* control reset रेजिस्टर */
	u32	ccbahr;		/* current CB address high रेजिस्टर */
	u32	ccbalr;		/* current CB address low रेजिस्टर */
	u32	plbr;		/* PLB configuration रेजिस्टर */
	u32	ier;		/* पूर्णांकerrupt enable रेजिस्टर */
	u32	pecr;		/* parity error count रेजिस्टर */
	u32	sr;		/* status रेजिस्टर */
	u32	revidr;		/* revision ID रेजिस्टर */
पूर्ण;

#पूर्ण_अगर /* _PPC440SPE_XOR_H */
