<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_LCA__H__
#घोषणा __ALPHA_LCA__H__

#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/mce.h>

/*
 * Low Cost Alpha (LCA) definitions (these apply to 21066 and 21068,
 * क्रम example).
 *
 * This file is based on:
 *
 *	DECchip 21066 and DECchip 21068 Alpha AXP Microprocessors
 *	Hardware Reference Manual; Digital Equipment Corp.; May 1994;
 *	Maynard, MA; Order Number: EC-N2681-71.
 */

/*
 * NOTE: The LCA uses a Host Address Extension (HAE) रेजिस्टर to access
 *	 PCI addresses that are beyond the first 27 bits of address
 *	 space.  Updating the HAE requires an बाह्यal cycle (and
 *	 a memory barrier), which tends to be slow.  Instead of updating
 *	 it on each sparse memory access, we keep the current HAE value
 *	 cached in variable cache_hae.  Only अगर the cached HAE dअगरfers
 *	 from the desired HAE value करो we actually updated HAE रेजिस्टर.
 *	 The HAE रेजिस्टर is preserved by the पूर्णांकerrupt handler entry/निकास
 *	 code, so this scheme works even in the presence of पूर्णांकerrupts.
 *
 * Dense memory space करोesn't require the HAE, but is restricted to
 * aligned 32 and 64 bit accesses.  Special Cycle and Interrupt
 * Acknowledge cycles may also require the use of the HAE.  The LCA
 * limits I/O address space to the bottom 24 bits of address space,
 * but this easily covers the 16 bit ISA I/O address space.
 */

/*
 * NOTE 2! The memory operations करो not set any memory barriers, as
 * it's not needed क्रम हालs like a frame buffer that is essentially
 * memory-like.  You need to करो them by hand अगर the operations depend
 * on ordering.
 *
 * Similarly, the port I/O operations करो a "mb" only after a ग_लिखो
 * operation: अगर an mb is needed beक्रमe (as in the हाल of करोing
 * memory mapped I/O first, and then a port I/O operation to the same
 * device), it needs to be करोne by hand.
 *
 * After the above has bitten me 100 बार, I'll give up and just करो
 * the mb all the समय, but right now I'm hoping this will work out.
 * Aव्योमing mb's may potentially be a noticeable speed improvement,
 * but I can't honestly say I've tested it.
 *
 * Handling पूर्णांकerrupts that need to करो mb's to synchronize to
 * non-पूर्णांकerrupts is another fun race area.  Don't करो it (because अगर
 * you करो, I'll have to करो *everything* with पूर्णांकerrupts disabled,
 * ugh).
 */

/*
 * Memory Controller रेजिस्टरs:
 */
#घोषणा LCA_MEM_BCR0		(IDENT_ADDR + 0x120000000UL)
#घोषणा LCA_MEM_BCR1		(IDENT_ADDR + 0x120000008UL)
#घोषणा LCA_MEM_BCR2		(IDENT_ADDR + 0x120000010UL)
#घोषणा LCA_MEM_BCR3		(IDENT_ADDR + 0x120000018UL)
#घोषणा LCA_MEM_BMR0		(IDENT_ADDR + 0x120000020UL)
#घोषणा LCA_MEM_BMR1		(IDENT_ADDR + 0x120000028UL)
#घोषणा LCA_MEM_BMR2		(IDENT_ADDR + 0x120000030UL)
#घोषणा LCA_MEM_BMR3		(IDENT_ADDR + 0x120000038UL)
#घोषणा LCA_MEM_BTR0		(IDENT_ADDR + 0x120000040UL)
#घोषणा LCA_MEM_BTR1		(IDENT_ADDR + 0x120000048UL)
#घोषणा LCA_MEM_BTR2		(IDENT_ADDR + 0x120000050UL)
#घोषणा LCA_MEM_BTR3		(IDENT_ADDR + 0x120000058UL)
#घोषणा LCA_MEM_GTR		(IDENT_ADDR + 0x120000060UL)
#घोषणा LCA_MEM_ESR		(IDENT_ADDR + 0x120000068UL)
#घोषणा LCA_MEM_EAR		(IDENT_ADDR + 0x120000070UL)
#घोषणा LCA_MEM_CAR		(IDENT_ADDR + 0x120000078UL)
#घोषणा LCA_MEM_VGR		(IDENT_ADDR + 0x120000080UL)
#घोषणा LCA_MEM_PLM		(IDENT_ADDR + 0x120000088UL)
#घोषणा LCA_MEM_FOR		(IDENT_ADDR + 0x120000090UL)

/*
 * I/O Controller रेजिस्टरs:
 */
#घोषणा LCA_IOC_HAE		(IDENT_ADDR + 0x180000000UL)
#घोषणा LCA_IOC_CONF		(IDENT_ADDR + 0x180000020UL)
#घोषणा LCA_IOC_STAT0		(IDENT_ADDR + 0x180000040UL)
#घोषणा LCA_IOC_STAT1		(IDENT_ADDR + 0x180000060UL)
#घोषणा LCA_IOC_TBIA		(IDENT_ADDR + 0x180000080UL)
#घोषणा LCA_IOC_TB_ENA		(IDENT_ADDR + 0x1800000a0UL)
#घोषणा LCA_IOC_SFT_RST		(IDENT_ADDR + 0x1800000c0UL)
#घोषणा LCA_IOC_PAR_DIS		(IDENT_ADDR + 0x1800000e0UL)
#घोषणा LCA_IOC_W_BASE0		(IDENT_ADDR + 0x180000100UL)
#घोषणा LCA_IOC_W_BASE1		(IDENT_ADDR + 0x180000120UL)
#घोषणा LCA_IOC_W_MASK0		(IDENT_ADDR + 0x180000140UL)
#घोषणा LCA_IOC_W_MASK1		(IDENT_ADDR + 0x180000160UL)
#घोषणा LCA_IOC_T_BASE0		(IDENT_ADDR + 0x180000180UL)
#घोषणा LCA_IOC_T_BASE1		(IDENT_ADDR + 0x1800001a0UL)
#घोषणा LCA_IOC_TB_TAG0		(IDENT_ADDR + 0x188000000UL)
#घोषणा LCA_IOC_TB_TAG1		(IDENT_ADDR + 0x188000020UL)
#घोषणा LCA_IOC_TB_TAG2		(IDENT_ADDR + 0x188000040UL)
#घोषणा LCA_IOC_TB_TAG3		(IDENT_ADDR + 0x188000060UL)
#घोषणा LCA_IOC_TB_TAG4		(IDENT_ADDR + 0x188000070UL)
#घोषणा LCA_IOC_TB_TAG5		(IDENT_ADDR + 0x1880000a0UL)
#घोषणा LCA_IOC_TB_TAG6		(IDENT_ADDR + 0x1880000c0UL)
#घोषणा LCA_IOC_TB_TAG7		(IDENT_ADDR + 0x1880000e0UL)

/*
 * Memory spaces:
 */
#घोषणा LCA_IACK_SC		(IDENT_ADDR + 0x1a0000000UL)
#घोषणा LCA_CONF		(IDENT_ADDR + 0x1e0000000UL)
#घोषणा LCA_IO			(IDENT_ADDR + 0x1c0000000UL)
#घोषणा LCA_SPARSE_MEM		(IDENT_ADDR + 0x200000000UL)
#घोषणा LCA_DENSE_MEM		(IDENT_ADDR + 0x300000000UL)

/*
 * Bit definitions क्रम I/O Controller status रेजिस्टर 0:
 */
#घोषणा LCA_IOC_STAT0_CMD		0xf
#घोषणा LCA_IOC_STAT0_ERR		(1<<4)
#घोषणा LCA_IOC_STAT0_LOST		(1<<5)
#घोषणा LCA_IOC_STAT0_THIT		(1<<6)
#घोषणा LCA_IOC_STAT0_TREF		(1<<7)
#घोषणा LCA_IOC_STAT0_CODE_SHIFT	8
#घोषणा LCA_IOC_STAT0_CODE_MASK		0x7
#घोषणा LCA_IOC_STAT0_P_NBR_SHIFT	13
#घोषणा LCA_IOC_STAT0_P_NBR_MASK	0x7ffff

#घोषणा LCA_HAE_ADDRESS		LCA_IOC_HAE

/* LCA PMR Power Management रेजिस्टर defines */
#घोषणा LCA_PMR_ADDR	(IDENT_ADDR + 0x120000098UL)
#घोषणा LCA_PMR_PDIV    0x7                     /* Primary घड़ी भागisor */
#घोषणा LCA_PMR_ODIV    0x38                    /* Override घड़ी भागisor */
#घोषणा LCA_PMR_INTO    0x40                    /* Interrupt override */
#घोषणा LCA_PMR_DMAO    0x80                    /* DMA override */
#घोषणा LCA_PMR_OCCEB   0xffff0000L             /* Override cycle counter - even bits */
#घोषणा LCA_PMR_OCCOB   0xffff000000000000L     /* Override cycle counter - even bits */
#घोषणा LCA_PMR_PRIMARY_MASK    0xfffffffffffffff8L

/* LCA PMR Macros */

#घोषणा LCA_READ_PMR        (*(अस्थिर अचिन्हित दीर्घ *)LCA_PMR_ADDR)
#घोषणा LCA_WRITE_PMR(d)    (*((अस्थिर अचिन्हित दीर्घ *)LCA_PMR_ADDR) = (d))

#घोषणा LCA_GET_PRIMARY(r)  ((r) & LCA_PMR_PDIV)
#घोषणा LCA_GET_OVERRIDE(r) (((r) >> 3) & LCA_PMR_PDIV)
#घोषणा LCA_SET_PRIMARY_CLOCK(r, c) ((r) = (((r) & LCA_PMR_PRIMARY_MASK)|(c)))

/* LCA PMR Divisor values */
#घोषणा LCA_PMR_DIV_1   0x0
#घोषणा LCA_PMR_DIV_1_5 0x1
#घोषणा LCA_PMR_DIV_2   0x2
#घोषणा LCA_PMR_DIV_4   0x3
#घोषणा LCA_PMR_DIV_8   0x4
#घोषणा LCA_PMR_DIV_16  0x5
#घोषणा LCA_PMR_DIV_MIN DIV_1
#घोषणा LCA_PMR_DIV_MAX DIV_16


/*
 * Data काष्ठाure क्रम handling LCA machine checks.  Correctable errors
 * result in a लघु logout frame, uncorrectable ones in a दीर्घ one.
 */
काष्ठा el_lca_mcheck_लघु अणु
	काष्ठा el_common	h;		/* common logout header */
	अचिन्हित दीर्घ		esr;		/* error-status रेजिस्टर */
	अचिन्हित दीर्घ		ear;		/* error-address रेजिस्टर */
	अचिन्हित दीर्घ		dc_stat;	/* dcache status रेजिस्टर */
	अचिन्हित दीर्घ		ioc_stat0;	/* I/O controller status रेजिस्टर 0 */
	अचिन्हित दीर्घ		ioc_stat1;	/* I/O controller status रेजिस्टर 1 */
पूर्ण;

काष्ठा el_lca_mcheck_दीर्घ अणु
	काष्ठा el_common	h;		/* common logout header */
	अचिन्हित दीर्घ		pt[31];		/* PAL temps */
	अचिन्हित दीर्घ		exc_addr;	/* exception address */
	अचिन्हित दीर्घ		pad1[3];
	अचिन्हित दीर्घ		pal_base;	/* PALcode base address */
	अचिन्हित दीर्घ		hier;		/* hw पूर्णांकerrupt enable */
	अचिन्हित दीर्घ		hirr;		/* hw पूर्णांकerrupt request */
	अचिन्हित दीर्घ		mm_csr;		/* MMU control & status */
	अचिन्हित दीर्घ		dc_stat;	/* data cache status */
	अचिन्हित दीर्घ		dc_addr;	/* data cache addr रेजिस्टर */
	अचिन्हित दीर्घ		abox_ctl;	/* address box control रेजिस्टर */
	अचिन्हित दीर्घ		esr;		/* error status रेजिस्टर */
	अचिन्हित दीर्घ		ear;		/* error address रेजिस्टर */
	अचिन्हित दीर्घ		car;		/* cache control रेजिस्टर */
	अचिन्हित दीर्घ		ioc_stat0;	/* I/O controller status रेजिस्टर 0 */
	अचिन्हित दीर्घ		ioc_stat1;	/* I/O controller status रेजिस्टर 1 */
	अचिन्हित दीर्घ		va;		/* भव address रेजिस्टर */
पूर्ण;

जोड़ el_lca अणु
	काष्ठा el_common *		c;
	काष्ठा el_lca_mcheck_दीर्घ *	l;
	काष्ठा el_lca_mcheck_लघु *	s;
पूर्ण;

#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions:
 *
 * Unlike Jensen, the Noname machines have no concept of local
 * I/O---everything goes over the PCI bus.
 *
 * There is plenty room क्रम optimization here.  In particular,
 * the Alpha's insb/insw/extb/extw should be useful in moving
 * data to/from the right byte-lanes.
 */

#घोषणा vip	अस्थिर पूर्णांक __क्रमce *
#घोषणा vuip	अस्थिर अचिन्हित पूर्णांक __क्रमce *
#घोषणा vulp	अस्थिर अचिन्हित दीर्घ __क्रमce *

#घोषणा LCA_SET_HAE						\
	करो अणु							\
		अगर (addr >= (1UL << 24)) अणु			\
			अचिन्हित दीर्घ msb = addr & 0xf8000000;	\
			addr -= msb;				\
			set_hae(msb);				\
		पूर्ण						\
	पूर्ण जबतक (0)


__EXTERN_INLINE अचिन्हित पूर्णांक lca_ioपढ़ो8(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ result, base_and_type;

	अगर (addr >= LCA_DENSE_MEM) अणु
		addr -= LCA_DENSE_MEM;
		LCA_SET_HAE;
		base_and_type = LCA_SPARSE_MEM + 0x00;
	पूर्ण अन्यथा अणु
		addr -= LCA_IO;
		base_and_type = LCA_IO + 0x00;
	पूर्ण

	result = *(vip) ((addr << 5) + base_and_type);
	वापस __kernel_extbl(result, addr & 3);
पूर्ण

__EXTERN_INLINE व्योम lca_ioग_लिखो8(u8 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ w, base_and_type;

	अगर (addr >= LCA_DENSE_MEM) अणु
		addr -= LCA_DENSE_MEM;
		LCA_SET_HAE;
		base_and_type = LCA_SPARSE_MEM + 0x00;
	पूर्ण अन्यथा अणु
		addr -= LCA_IO;
		base_and_type = LCA_IO + 0x00;
	पूर्ण

	w = __kernel_insbl(b, addr & 3);
	*(vuip) ((addr << 5) + base_and_type) = w;
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक lca_ioपढ़ो16(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ result, base_and_type;

	अगर (addr >= LCA_DENSE_MEM) अणु
		addr -= LCA_DENSE_MEM;
		LCA_SET_HAE;
		base_and_type = LCA_SPARSE_MEM + 0x08;
	पूर्ण अन्यथा अणु
		addr -= LCA_IO;
		base_and_type = LCA_IO + 0x08;
	पूर्ण

	result = *(vip) ((addr << 5) + base_and_type);
	वापस __kernel_extwl(result, addr & 3);
पूर्ण

__EXTERN_INLINE व्योम lca_ioग_लिखो16(u16 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ w, base_and_type;

	अगर (addr >= LCA_DENSE_MEM) अणु
		addr -= LCA_DENSE_MEM;
		LCA_SET_HAE;
		base_and_type = LCA_SPARSE_MEM + 0x08;
	पूर्ण अन्यथा अणु
		addr -= LCA_IO;
		base_and_type = LCA_IO + 0x08;
	पूर्ण

	w = __kernel_inswl(b, addr & 3);
	*(vuip) ((addr << 5) + base_and_type) = w;
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक lca_ioपढ़ो32(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (addr < LCA_DENSE_MEM)
		addr = ((addr - LCA_IO) << 5) + LCA_IO + 0x18;
	वापस *(vuip)addr;
पूर्ण

__EXTERN_INLINE व्योम lca_ioग_लिखो32(u32 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (addr < LCA_DENSE_MEM)
		addr = ((addr - LCA_IO) << 5) + LCA_IO + 0x18;
	*(vuip)addr = b;
पूर्ण

__EXTERN_INLINE व्योम __iomem *lca_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)(addr + LCA_IO);
पूर्ण

__EXTERN_INLINE व्योम __iomem *lca_ioremap(अचिन्हित दीर्घ addr,
					  अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)(addr + LCA_DENSE_MEM);
पूर्ण

__EXTERN_INLINE पूर्णांक lca_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= IDENT_ADDR + 0x120000000UL;
पूर्ण

__EXTERN_INLINE पूर्णांक lca_is_mmio(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस (अचिन्हित दीर्घ)addr >= LCA_DENSE_MEM;
पूर्ण

#अघोषित vip
#अघोषित vuip
#अघोषित vulp

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		lca
#घोषणा lca_trivial_rw_bw	2
#घोषणा lca_trivial_rw_lq	1
#घोषणा lca_trivial_io_bw	0
#घोषणा lca_trivial_io_lq	0
#घोषणा lca_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_LCA__H__ */
