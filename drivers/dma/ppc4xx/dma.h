<शैली गुरु>
/*
 * 440SPe's DMA engines support header file
 *
 * 2006-2009 (C) DENX Software Engineering.
 *
 * Author: Yuri Tikhonov <yur@emcraft.com>
 *
 * This file is licensed under the term of  the GNU General Public License
 * version 2. The program licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित	_PPC440SPE_DMA_H
#घोषणा _PPC440SPE_DMA_H

#समावेश <linux/types.h>

/* Number of elements in the array with अटलal CDBs */
#घोषणा	MAX_STAT_DMA_CDBS	16
/* Number of DMA engines available on the contoller */
#घोषणा DMA_ENGINES_NUM		2

/* Maximum h/w supported number of destinations */
#घोषणा DMA_DEST_MAX_NUM	2

/* FIFO's params */
#घोषणा DMA0_FIFO_SIZE		0x1000
#घोषणा DMA1_FIFO_SIZE		0x1000
#घोषणा DMA_FIFO_ENABLE		(1<<12)

/* DMA Configuration Register. Data Transfer Engine PLB Priority: */
#घोषणा DMA_CFG_DXEPR_LP	(0<<26)
#घोषणा DMA_CFG_DXEPR_HP	(3<<26)
#घोषणा DMA_CFG_DXEPR_HHP	(2<<26)
#घोषणा DMA_CFG_DXEPR_HHHP	(1<<26)

/* DMA Configuration Register. DMA FIFO Manager PLB Priority: */
#घोषणा DMA_CFG_DFMPP_LP	(0<<23)
#घोषणा DMA_CFG_DFMPP_HP	(3<<23)
#घोषणा DMA_CFG_DFMPP_HHP	(2<<23)
#घोषणा DMA_CFG_DFMPP_HHHP	(1<<23)

/* DMA Configuration Register. Force 64-byte Alignment */
#घोषणा DMA_CFG_FALGN		(1 << 19)

/*UIC0:*/
#घोषणा D0CPF_INT		(1<<12)
#घोषणा D0CSF_INT		(1<<11)
#घोषणा D1CPF_INT		(1<<10)
#घोषणा D1CSF_INT		(1<<9)
/*UIC1:*/
#घोषणा DMAE_INT		(1<<9)

/* I2O IOP Interrupt Mask Register */
#घोषणा I2O_IOPIM_P0SNE		(1<<3)
#घोषणा I2O_IOPIM_P0EM		(1<<5)
#घोषणा I2O_IOPIM_P1SNE		(1<<6)
#घोषणा I2O_IOPIM_P1EM		(1<<8)

/* DMA CDB fields */
#घोषणा DMA_CDB_MSK		(0xF)
#घोषणा DMA_CDB_64B_ADDR	(1<<2)
#घोषणा DMA_CDB_NO_INT		(1<<3)
#घोषणा DMA_CDB_STATUS_MSK	(0x3)
#घोषणा DMA_CDB_ADDR_MSK	(0xFFFFFFF0)

/* DMA CDB OpCodes */
#घोषणा DMA_CDB_OPC_NO_OP	(0x00)
#घोषणा DMA_CDB_OPC_MV_SG1_SG2	(0x01)
#घोषणा DMA_CDB_OPC_MULTICAST	(0x05)
#घोषणा DMA_CDB_OPC_DFILL128	(0x24)
#घोषणा DMA_CDB_OPC_DCHECK128	(0x23)

#घोषणा DMA_CUED_XOR_BASE	(0x10000000)
#घोषणा DMA_CUED_XOR_HB		(0x00000008)

#अगर_घोषित CONFIG_440SP
#घोषणा DMA_CUED_MULT1_OFF	0
#घोषणा DMA_CUED_MULT2_OFF	8
#घोषणा DMA_CUED_MULT3_OFF	16
#घोषणा DMA_CUED_REGION_OFF	24
#घोषणा DMA_CUED_XOR_WIN_MSK	(0xFC000000)
#अन्यथा
#घोषणा DMA_CUED_MULT1_OFF	2
#घोषणा DMA_CUED_MULT2_OFF	10
#घोषणा DMA_CUED_MULT3_OFF	18
#घोषणा DMA_CUED_REGION_OFF	26
#घोषणा DMA_CUED_XOR_WIN_MSK	(0xF0000000)
#पूर्ण_अगर

#घोषणा DMA_CUED_REGION_MSK	0x3
#घोषणा DMA_RXOR123		0x0
#घोषणा DMA_RXOR124		0x1
#घोषणा DMA_RXOR125		0x2
#घोषणा DMA_RXOR12		0x3

/* S/G addresses */
#घोषणा DMA_CDB_SG_SRC		1
#घोषणा DMA_CDB_SG_DST1		2
#घोषणा DMA_CDB_SG_DST2		3

/*
 * DMAx engines Command Descriptor Block Type
 */
काष्ठा dma_cdb अणु
	/*
	 * Basic CDB काष्ठाure (Table 20-17, p.499, 440spe_um_1_22.pdf)
	 */
	u8	pad0[2];        /* reserved */
	u8	attr;		/* attributes */
	u8	opc;		/* opcode */
	u32	sg1u;		/* upper SG1 address */
	u32	sg1l;		/* lower SG1 address */
	u32	cnt;		/* SG count, 3B used */
	u32	sg2u;		/* upper SG2 address */
	u32	sg2l;		/* lower SG2 address */
	u32	sg3u;		/* upper SG3 address */
	u32	sg3l;		/* lower SG3 address */
पूर्ण;

/*
 * DMAx hardware रेजिस्टरs (p.515 in 440SPe UM 1.22)
 */
काष्ठा dma_regs अणु
	u32	cpfpl;
	u32	cpfph;
	u32	csfpl;
	u32	csfph;
	u32	dsts;
	u32	cfg;
	u8	pad0[0x8];
	u16	cpfhp;
	u16	cpftp;
	u16	csfhp;
	u16	csftp;
	u8	pad1[0x8];
	u32	acpl;
	u32	acph;
	u32	s1bpl;
	u32	s1bph;
	u32	s2bpl;
	u32	s2bph;
	u32	s3bpl;
	u32	s3bph;
	u8	pad2[0x10];
	u32	earl;
	u32	earh;
	u8	pad3[0x8];
	u32	seat;
	u32	sead;
	u32	op;
	u32	fsiz;
पूर्ण;

/*
 * I2O hardware रेजिस्टरs (p.528 in 440SPe UM 1.22)
 */
काष्ठा i2o_regs अणु
	u32	ists;
	u32	iseat;
	u32	isead;
	u8	pad0[0x14];
	u32	idbel;
	u8	pad1[0xc];
	u32	ihis;
	u32	ihim;
	u8	pad2[0x8];
	u32	ihiq;
	u32	ihoq;
	u8	pad3[0x8];
	u32	iopis;
	u32	iopim;
	u32	iopiq;
	u8	iopoq;
	u8	pad4[3];
	u16	iअगरlh;
	u16	iअगरlt;
	u16	iiplh;
	u16	iiplt;
	u16	ioflh;
	u16	ioflt;
	u16	ioplh;
	u16	ioplt;
	u32	iidc;
	u32	ictl;
	u32	अगरcpp;
	u8	pad5[0x4];
	u16	mfac0;
	u16	mfac1;
	u16	mfac2;
	u16	mfac3;
	u16	mfac4;
	u16	mfac5;
	u16	mfac6;
	u16	mfac7;
	u16	अगरcfh;
	u16	अगरcht;
	u8	pad6[0x4];
	u32	iअगरmc;
	u32	iodb;
	u32	iodbc;
	u32	अगरbal;
	u32	अगरbah;
	u32	अगरsiz;
	u32	ispd0;
	u32	ispd1;
	u32	ispd2;
	u32	ispd3;
	u32	ihipl;
	u32	ihiph;
	u32	ihopl;
	u32	ihoph;
	u32	iiipl;
	u32	iiiph;
	u32	iiopl;
	u32	iioph;
	u32	अगरcpl;
	u32	अगरcph;
	u8	pad7[0x8];
	u32	iopt;
पूर्ण;

#पूर्ण_अगर /* _PPC440SPE_DMA_H */
