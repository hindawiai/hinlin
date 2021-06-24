<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mpc8610-pcm.h - ALSA PCM पूर्णांकerface क्रम the Freescale MPC8610 SoC
 */

#अगर_अघोषित _MPC8610_PCM_H
#घोषणा _MPC8610_PCM_H

काष्ठा ccsr_dma अणु
	u8 res0[0x100];
	काष्ठा ccsr_dma_channel अणु
		__be32 mr;      /* Mode रेजिस्टर */
		__be32 sr;      /* Status रेजिस्टर */
		__be32 eclndar; /* Current link descriptor extended addr reg */
		__be32 clndar;  /* Current link descriptor address रेजिस्टर */
		__be32 satr;    /* Source attributes रेजिस्टर */
		__be32 sar;     /* Source address रेजिस्टर */
		__be32 datr;    /* Destination attributes रेजिस्टर */
		__be32 dar;     /* Destination address रेजिस्टर */
		__be32 bcr;     /* Byte count रेजिस्टर */
		__be32 enlndar; /* Next link descriptor extended address reg */
		__be32 nlndar;  /* Next link descriptor address रेजिस्टर */
		u8 res1[4];
		__be32 eclsdar; /* Current list descriptor extended addr reg */
		__be32 clsdar;  /* Current list descriptor address रेजिस्टर */
		__be32 enlsdar; /* Next list descriptor extended address reg */
		__be32 nlsdar;  /* Next list descriptor address रेजिस्टर */
		__be32 ssr;     /* Source stride रेजिस्टर */
		__be32 dsr;     /* Destination stride रेजिस्टर */
		u8 res2[0x38];
	पूर्ण channel[4];
	__be32 dgsr;
पूर्ण;

#घोषणा CCSR_DMA_MR_BWC_DISABLED	0x0F000000
#घोषणा CCSR_DMA_MR_BWC_SHIFT   	24
#घोषणा CCSR_DMA_MR_BWC_MASK    	0x0F000000
#घोषणा CCSR_DMA_MR_BWC(x) \
	((ilog2(x) << CCSR_DMA_MR_BWC_SHIFT) & CCSR_DMA_MR_BWC_MASK)
#घोषणा CCSR_DMA_MR_EMP_EN      	0x00200000
#घोषणा CCSR_DMA_MR_EMS_EN      	0x00040000
#घोषणा CCSR_DMA_MR_DAHTS_MASK  	0x00030000
#घोषणा CCSR_DMA_MR_DAHTS_1     	0x00000000
#घोषणा CCSR_DMA_MR_DAHTS_2     	0x00010000
#घोषणा CCSR_DMA_MR_DAHTS_4     	0x00020000
#घोषणा CCSR_DMA_MR_DAHTS_8     	0x00030000
#घोषणा CCSR_DMA_MR_SAHTS_MASK  	0x0000C000
#घोषणा CCSR_DMA_MR_SAHTS_1     	0x00000000
#घोषणा CCSR_DMA_MR_SAHTS_2     	0x00004000
#घोषणा CCSR_DMA_MR_SAHTS_4     	0x00008000
#घोषणा CCSR_DMA_MR_SAHTS_8     	0x0000C000
#घोषणा CCSR_DMA_MR_DAHE		0x00002000
#घोषणा CCSR_DMA_MR_SAHE		0x00001000
#घोषणा CCSR_DMA_MR_SRW 		0x00000400
#घोषणा CCSR_DMA_MR_EOSIE       	0x00000200
#घोषणा CCSR_DMA_MR_EOLNIE      	0x00000100
#घोषणा CCSR_DMA_MR_EOLSIE      	0x00000080
#घोषणा CCSR_DMA_MR_EIE 		0x00000040
#घोषणा CCSR_DMA_MR_XFE 		0x00000020
#घोषणा CCSR_DMA_MR_CDSM_SWSM   	0x00000010
#घोषणा CCSR_DMA_MR_CA  		0x00000008
#घोषणा CCSR_DMA_MR_CTM 		0x00000004
#घोषणा CCSR_DMA_MR_CC  		0x00000002
#घोषणा CCSR_DMA_MR_CS  		0x00000001

#घोषणा CCSR_DMA_SR_TE  		0x00000080
#घोषणा CCSR_DMA_SR_CH  		0x00000020
#घोषणा CCSR_DMA_SR_PE  		0x00000010
#घोषणा CCSR_DMA_SR_EOLNI       	0x00000008
#घोषणा CCSR_DMA_SR_CB  		0x00000004
#घोषणा CCSR_DMA_SR_EOSI		0x00000002
#घोषणा CCSR_DMA_SR_EOLSI       	0x00000001

/* ECLNDAR takes bits 32-36 of the CLNDAR रेजिस्टर */
अटल अंतरभूत u32 CCSR_DMA_ECLNDAR_ADDR(u64 x)
अणु
	वापस (x >> 32) & 0xf;
पूर्ण

#घोषणा CCSR_DMA_CLNDAR_ADDR(x) ((x) & 0xFFFFFFFE)
#घोषणा CCSR_DMA_CLNDAR_EOSIE   	0x00000008

/* SATR and DATR, combined */
#घोषणा CCSR_DMA_ATR_PBATMU     	0x20000000
#घोषणा CCSR_DMA_ATR_TFLOWLVL_0 	0x00000000
#घोषणा CCSR_DMA_ATR_TFLOWLVL_1 	0x06000000
#घोषणा CCSR_DMA_ATR_TFLOWLVL_2 	0x08000000
#घोषणा CCSR_DMA_ATR_TFLOWLVL_3 	0x0C000000
#घोषणा CCSR_DMA_ATR_PCIORDER   	0x02000000
#घोषणा CCSR_DMA_ATR_SME		0x01000000
#घोषणा CCSR_DMA_ATR_NOSNOOP    	0x00040000
#घोषणा CCSR_DMA_ATR_SNOOP      	0x00050000
#घोषणा CCSR_DMA_ATR_ESAD_MASK  	0x0000000F

/**
 *  List Descriptor क्रम extended chaining mode DMA operations.
 *
 *  The CLSDAR रेजिस्टर poपूर्णांकs to the first (in a linked-list) List
 *  Descriptor.  Each object must be aligned on a 32-byte boundary. Each
 *  list descriptor poपूर्णांकs to a linked-list of link Descriptors.
 */
काष्ठा fsl_dma_list_descriptor अणु
	__be64 next;    	/* Address of next list descriptor */
	__be64 first_link;      /* Address of first link descriptor */
	__be32 source;  	/* Source stride */
	__be32 dest;    	/* Destination stride */
	u8 res[8];      	/* Reserved */
पूर्ण __attribute__ ((aligned(32), packed));

/**
 *  Link Descriptor क्रम basic and extended chaining mode DMA operations.
 *
 *  A Link Descriptor poपूर्णांकs to a single DMA buffer.  Each link descriptor
 *  must be aligned on a 32-byte boundary.
 */
काष्ठा fsl_dma_link_descriptor अणु
	__be32 source_attr;     /* Programmed पूर्णांकo SATR रेजिस्टर */
	__be32 source_addr;     /* Programmed पूर्णांकo SAR रेजिस्टर */
	__be32 dest_attr;       /* Programmed पूर्णांकo DATR रेजिस्टर */
	__be32 dest_addr;       /* Programmed पूर्णांकo DAR रेजिस्टर */
	__be64 next;    /* Address of next link descriptor */
	__be32 count;   /* Byte count */
	u8 res[4];      /* Reserved */
पूर्ण __attribute__ ((aligned(32), packed));

#पूर्ण_अगर
