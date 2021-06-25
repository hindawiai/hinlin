<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Marvel प्रणालीs use the IO7 I/O chip provides PCI/PCIX/AGP access
 *
 * This file is based on:
 *
 * Marvel / EV7 System Programmer's Manual
 * Revision 1.00
 * 14 May 2001
 */

#अगर_अघोषित __ALPHA_MARVEL__H__
#घोषणा __ALPHA_MARVEL__H__

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/compiler.h>

#घोषणा MARVEL_MAX_PIDS		 32 /* as दीर्घ as we rely on 43-bit superpage */
#घोषणा MARVEL_IRQ_VEC_PE_SHIFT	(10)
#घोषणा MARVEL_IRQ_VEC_IRQ_MASK	((1 << MARVEL_IRQ_VEC_PE_SHIFT) - 1)
#घोषणा MARVEL_NR_IRQS		\
	(16 + (MARVEL_MAX_PIDS * (1 << MARVEL_IRQ_VEC_PE_SHIFT)))

/*
 * EV7 RBOX Registers
 */
प्रकार काष्ठा अणु
	अस्थिर अचिन्हित दीर्घ csr __attribute__((aligned(16)));
पूर्ण ev7_csr;

प्रकार काष्ठा अणु
	ev7_csr	RBOX_CFG;		/* 0x0000 */
	ev7_csr	RBOX_NSVC;
	ev7_csr	RBOX_EWVC;
	ev7_csr	RBOX_WHAMI;
	ev7_csr	RBOX_TCTL;		/* 0x0040 */
	ev7_csr	RBOX_INT;
	ev7_csr	RBOX_IMASK;
	ev7_csr	RBOX_IREQ;
	ev7_csr	RBOX_INTQ;		/* 0x0080 */
	ev7_csr	RBOX_INTA;
	ev7_csr	RBOX_IT;
	ev7_csr	RBOX_SCRATCH1;
	ev7_csr	RBOX_SCRATCH2;		/* 0x00c0 */
	ev7_csr	RBOX_L_ERR;
पूर्ण ev7_csrs;

/*
 * EV7 CSR addressing macros
 */
#घोषणा EV7_MASK40(addr)        ((addr) & ((1UL << 41) - 1))
#घोषणा EV7_KERN_ADDR(addr)	((व्योम *)(IDENT_ADDR | EV7_MASK40(addr)))

#घोषणा EV7_PE_MASK		0x1ffUL /* 9 bits ( 256 + mem/io ) */
#घोषणा EV7_IPE(pe)		((~((दीर्घ)(pe)) & EV7_PE_MASK) << 35)

#घोषणा EV7_CSR_PHYS(pe, off)	(EV7_IPE(pe) | (0x7FFCUL << 20) | (off))
#घोषणा EV7_CSRS_PHYS(pe)	(EV7_CSR_PHYS(pe, 0UL))

#घोषणा EV7_CSR_KERN(pe, off)	(EV7_KERN_ADDR(EV7_CSR_PHYS(pe, off)))
#घोषणा EV7_CSRS_KERN(pe)	(EV7_KERN_ADDR(EV7_CSRS_PHYS(pe)))

#घोषणा EV7_CSR_OFFSET(name)	((अचिन्हित दीर्घ)&((ev7_csrs *)शून्य)->name.csr)

/*
 * IO7 रेजिस्टरs
 */
प्रकार काष्ठा अणु
	अस्थिर अचिन्हित दीर्घ csr __attribute__((aligned(64)));
पूर्ण io7_csr;

प्रकार काष्ठा अणु
	/* I/O Port Control Registers */
	io7_csr	POx_CTRL;	       	/* 0x0000 */
	io7_csr	POx_CACHE_CTL;
	io7_csr POx_TIMER;
	io7_csr POx_IO_ADR_EXT;
	io7_csr	POx_MEM_ADR_EXT;	/* 0x0100 */
	io7_csr POx_XCAL_CTRL;
	io7_csr rsvd1[2];	/* ?? spec करोesn't show 0x180 */
	io7_csr POx_DM_SOURCE;		/* 0x0200 */
	io7_csr POx_DM_DEST;
	io7_csr POx_DM_SIZE;
	io7_csr POx_DM_CTRL;
	io7_csr rsvd2[4];		/* 0x0300 */

	/* AGP Control Registers -- port 3 only */
	io7_csr AGP_CAP_ID;		/* 0x0400 */
	io7_csr AGP_STAT;
	io7_csr	AGP_CMD;
	io7_csr	rsvd3;

	/* I/O Port Monitor Registers */
	io7_csr	POx_MONCTL;		/* 0x0500 */
	io7_csr POx_CTRA;
	io7_csr POx_CTRB;
	io7_csr POx_CTR56;
	io7_csr POx_SCRATCH;		/* 0x0600 */
	io7_csr POx_XTRA_A;
	io7_csr POx_XTRA_TS;
	io7_csr POx_XTRA_Z;
	io7_csr rsvd4;			/* 0x0700 */
	io7_csr POx_THRESHA;
	io7_csr POx_THRESHB;
	io7_csr rsvd5[33];

	/* System Address Space Winकरोw Control Registers */

	io7_csr POx_WBASE[4];		/* 0x1000 */
	io7_csr POx_WMASK[4];
	io7_csr POx_TBASE[4];
	io7_csr POx_SG_TBIA;
	io7_csr POx_MSI_WBASE;
	io7_csr rsvd6[50];

	/* I/O Port Error Registers */
	io7_csr POx_ERR_SUM;
	io7_csr POx_FIRST_ERR;
	io7_csr POx_MSK_HEI;
	io7_csr POx_TLB_ERR;
	io7_csr POx_SPL_COMPLT;
	io7_csr POx_TRANS_SUM;
	io7_csr POx_FRC_PCI_ERR;
	io7_csr POx_MULT_ERR;
	io7_csr rsvd7[8];

	/* I/O Port End of Interrupt Registers */
	io7_csr EOI_DAT;
	io7_csr rsvd8[7];
	io7_csr POx_IACK_SPECIAL;
	io7_csr rsvd9[103];
पूर्ण io7_ioport_csrs;

प्रकार काष्ठा अणु
	io7_csr IO_ASIC_REV;		/* 0x30.0000 */
	io7_csr IO_SYS_REV;
	io7_csr SER_CHAIN3;
	io7_csr PO7_RST1;
	io7_csr PO7_RST2;		/* 0x30.0100 */
	io7_csr POx_RST[4];
	io7_csr IO7_DWNH;
	io7_csr IO7_MAF;
	io7_csr IO7_MAF_TO;
	io7_csr IO7_ACC_CLUMP;		/* 0x30.0300 */
	io7_csr IO7_PMASK;
	io7_csr IO7_IOMASK;
	io7_csr IO7_UPH;
	io7_csr IO7_UPH_TO;		/* 0x30.0400 */
	io7_csr RBX_IREQ_OFF;
	io7_csr RBX_INTA_OFF;
	io7_csr INT_RTY;
	io7_csr PO7_MONCTL;		/* 0x30.0500 */
	io7_csr PO7_CTRA;
	io7_csr PO7_CTRB;
	io7_csr PO7_CTR56;
	io7_csr PO7_SCRATCH;		/* 0x30.0600 */
	io7_csr PO7_XTRA_A;
	io7_csr PO7_XTRA_TS;
	io7_csr PO7_XTRA_Z;
	io7_csr PO7_PMASK;		/* 0x30.0700 */
	io7_csr PO7_THRESHA;
	io7_csr PO7_THRESHB;
	io7_csr rsvd1[97];
	io7_csr PO7_ERROR_SUM;		/* 0x30.2000 */
	io7_csr PO7_BHOLE_MASK;
	io7_csr PO7_HEI_MSK;
	io7_csr PO7_CRD_MSK;
	io7_csr PO7_UNCRR_SYM;		/* 0x30.2100 */
	io7_csr PO7_CRRCT_SYM;
	io7_csr PO7_ERR_PKT[2];
	io7_csr PO7_UGBGE_SYM;		/* 0x30.2200 */
	io7_csr rsbv2[887];
	io7_csr PO7_LSI_CTL[128];	/* 0x31.0000 */
	io7_csr rsvd3[123];
	io7_csr HLT_CTL;		/* 0x31.3ec0 */
	io7_csr HPI_CTL;		/* 0x31.3f00 */
	io7_csr CRD_CTL;
	io7_csr STV_CTL;
	io7_csr HEI_CTL;
	io7_csr PO7_MSI_CTL[16];	/* 0x31.4000 */
	io7_csr rsvd4[240];

	/*
	 * Interrupt Diagnostic / Test
	 */
	काष्ठा अणु
		io7_csr INT_PND;
		io7_csr INT_CLR;
		io7_csr INT_EOI;
		io7_csr rsvd[29];
	पूर्ण INT_DIAG[4];
	io7_csr rsvd5[125];	    	/* 0x31.a000 */
	io7_csr MISC_PND;		/* 0x31.b800 */
	io7_csr rsvd6[31];
	io7_csr MSI_PND[16];		/* 0x31.c000 */
	io7_csr rsvd7[16];
	io7_csr MSI_CLR[16];		/* 0x31.c800 */
पूर्ण io7_port7_csrs;

/* 
 * IO7 DMA Winकरोw Base रेजिस्टर (POx_WBASEx)
 */
#घोषणा wbase_m_ena  0x1
#घोषणा wbase_m_sg   0x2
#घोषणा wbase_m_dac  0x4
#घोषणा wbase_m_addr 0xFFF00000
जोड़ IO7_POx_WBASE अणु
	काष्ठा अणु
		अचिन्हित ena : 1;	/* <0>			*/
		अचिन्हित sg : 1;	/* <1>			*/
		अचिन्हित dac : 1;	/* <2> -- winकरोw 3 only */
		अचिन्हित rsvd1 : 17; 
		अचिन्हित addr : 12;	/* <31:20>		*/
		अचिन्हित rsvd2 : 32;
	पूर्ण bits;
	अचिन्हित as_दीर्घ[2];
	अचिन्हित as_quad;
पूर्ण;

/*
 * IO7 IID (Interrupt IDentअगरier) क्रमmat
 *
 * For level-sensative पूर्णांकerrupts, पूर्णांक_num is encoded as:
 *
 *	bus/port	slot/device	INTx
 *	<7:5>		<4:2>		<1:0>
 */
जोड़ IO7_IID अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक_num : 9;		/* <8:0>    	*/
		अचिन्हित tpu_mask : 4;		/* <12:9> rsvd	*/
		अचिन्हित msi : 1;		/* 13		*/
		अचिन्हित ipe : 10;		/* <23:14>	*/
		अचिन्हित दीर्घ rsvd : 40;		
	पूर्ण bits;
	अचिन्हित पूर्णांक as_दीर्घ[2];
	अचिन्हित दीर्घ as_quad;
पूर्ण;

/*
 * IO7 addressing macros
 */
#घोषणा IO7_KERN_ADDR(addr)	(EV7_KERN_ADDR(addr))

#घोषणा IO7_PORT_MASK	   	0x07UL	/* 3 bits of port 	   */

#घोषणा IO7_IPE(pe)		(EV7_IPE(pe))
#घोषणा IO7_IPORT(port)		((~((दीर्घ)(port)) & IO7_PORT_MASK) << 32)

#घोषणा IO7_HOSE(pe, port)	(IO7_IPE(pe) | IO7_IPORT(port))

#घोषणा IO7_MEM_PHYS(pe, port)	(IO7_HOSE(pe, port) | 0x00000000UL)
#घोषणा IO7_CONF_PHYS(pe, port)	(IO7_HOSE(pe, port) | 0xFE000000UL)
#घोषणा IO7_IO_PHYS(pe, port)	(IO7_HOSE(pe, port) | 0xFF000000UL)
#घोषणा IO7_CSR_PHYS(pe, port, off) \
                                (IO7_HOSE(pe, port) | 0xFF800000UL | (off))
#घोषणा IO7_CSRS_PHYS(pe, port)	(IO7_CSR_PHYS(pe, port, 0UL))
#घोषणा IO7_PORT7_CSRS_PHYS(pe) (IO7_CSR_PHYS(pe, 7, 0x300000UL))

#घोषणा IO7_MEM_KERN(pe, port)      (IO7_KERN_ADDR(IO7_MEM_PHYS(pe, port)))
#घोषणा IO7_CONF_KERN(pe, port)     (IO7_KERN_ADDR(IO7_CONF_PHYS(pe, port)))
#घोषणा IO7_IO_KERN(pe, port)       (IO7_KERN_ADDR(IO7_IO_PHYS(pe, port)))
#घोषणा IO7_CSR_KERN(pe, port, off) (IO7_KERN_ADDR(IO7_CSR_PHYS(pe,port,off)))
#घोषणा IO7_CSRS_KERN(pe, port)     (IO7_KERN_ADDR(IO7_CSRS_PHYS(pe, port)))
#घोषणा IO7_PORT7_CSRS_KERN(pe)	    (IO7_KERN_ADDR(IO7_PORT7_CSRS_PHYS(pe)))

#घोषणा IO7_PLL_RNGA(pll)	(((pll) >> 3) & 0x7)
#घोषणा IO7_PLL_RNGB(pll)	(((pll) >> 6) & 0x7)

#घोषणा IO7_MEM_SPACE		(2UL * 1024 * 1024 * 1024)	/* 2GB MEM */
#घोषणा IO7_IO_SPACE		(8UL * 1024 * 1024)		/* 8MB I/O */

 
/* 
 * Offset between ram physical addresses and pci64 DAC addresses
 */
#घोषणा IO7_DAC_OFFSET		(1UL << 49)

/*
 * This is needed to satisअगरy the IO() macro used in initializing the machvec
 */
#घोषणा MARVEL_IACK_SC 							\
        ((अचिन्हित दीर्घ)						\
	 (&(((io7_ioport_csrs *)IO7_CSRS_KERN(0, 0))->POx_IACK_SPECIAL)))

#अगर_घोषित __KERNEL__

/*
 * IO7 काष्ठाs
 */
#घोषणा IO7_NUM_PORTS 4
#घोषणा IO7_AGP_PORT  3

काष्ठा io7_port अणु
	काष्ठा io7 *io7;
	काष्ठा pci_controller *hose;

	पूर्णांक enabled;
	अचिन्हित पूर्णांक port;
	io7_ioport_csrs *csrs;

	अचिन्हित दीर्घ saved_wbase[4];
	अचिन्हित दीर्घ saved_wmask[4];
	अचिन्हित दीर्घ saved_tbase[4];
पूर्ण;

काष्ठा io7 अणु
	काष्ठा io7 *next;

	अचिन्हित पूर्णांक pe;
	io7_port7_csrs *csrs;
	काष्ठा io7_port ports[IO7_NUM_PORTS];

	raw_spinlock_t irq_lock;
पूर्ण;

#अगर_अघोषित __EXTERN_INLINE
# define __EXTERN_INLINE बाह्य अंतरभूत
# define __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions. All access through linear space.
 */

/*
 * Memory functions.  All accesses through linear space.
 */

#घोषणा vucp	अस्थिर अचिन्हित अक्षर __क्रमce *
#घोषणा vusp	अस्थिर अचिन्हित लघु __क्रमce *

बाह्य अचिन्हित पूर्णांक marvel_ioपढ़ो8(स्थिर व्योम __iomem *);
बाह्य व्योम marvel_ioग_लिखो8(u8 b, व्योम __iomem *);

__EXTERN_INLINE अचिन्हित पूर्णांक marvel_ioपढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	वापस __kernel_ldwu(*(vusp)addr);
पूर्ण

__EXTERN_INLINE व्योम marvel_ioग_लिखो16(u16 b, व्योम __iomem *addr)
अणु
	__kernel_stw(b, *(vusp)addr);
पूर्ण

बाह्य व्योम __iomem *marvel_ioremap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size);
बाह्य व्योम marvel_iounmap(अस्थिर व्योम __iomem *addr);
बाह्य व्योम __iomem *marvel_ioporपंचांगap (अचिन्हित दीर्घ addr);

__EXTERN_INLINE पूर्णांक marvel_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस (addr >> 40) & 1;
पूर्ण

बाह्य पूर्णांक marvel_is_mmio(स्थिर अस्थिर व्योम __iomem *);

#अघोषित vucp
#अघोषित vusp

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		marvel
#घोषणा marvel_trivial_rw_bw	1
#घोषणा marvel_trivial_rw_lq	1
#घोषणा marvel_trivial_io_bw	0
#घोषणा marvel_trivial_io_lq	1
#घोषणा marvel_trivial_iounmap	0
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
# undef __EXTERN_INLINE
# undef __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_MARVEL__H__ */
