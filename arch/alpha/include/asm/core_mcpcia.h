<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_MCPCIA__H__
#घोषणा __ALPHA_MCPCIA__H__

/* Define to experiment with fitting everything पूर्णांकo one 128MB HAE winकरोw.
   One winकरोw per bus, that is.  */
#घोषणा MCPCIA_ONE_HAE_WINDOW 1

#समावेश <linux/types.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/mce.h>

/*
 * MCPCIA is the पूर्णांकernal name क्रम a core logic chipset which provides
 * PCI access क्रम the RAWHIDE family of प्रणालीs.
 *
 * This file is based on:
 *
 * RAWHIDE System Programmer's Manual
 * 16-May-96
 * Rev. 1.4
 *
 */

/*------------------------------------------------------------------------**
**                                                                        **
**  I/O procedures                                                        **
**                                                                        **
**      inport[b|w|t|l], outport[b|w|t|l] 8:16:24:32 IO xfers             **
**	inportbxt: 8 bits only                                            **
**      inport:    alias of inportw                                       **
**      outport:   alias of outportw                                      **
**                                                                        **
**      inmem[b|w|t|l], ouपंचांगem[b|w|t|l] 8:16:24:32 ISA memory xfers       **
**	inmembxt: 8 bits only                                             **
**      inmem:    alias of inmemw                                         **
**      ouपंचांगem:   alias of ouपंचांगemw                                        **
**                                                                        **
**------------------------------------------------------------------------*/


/* MCPCIA ADDRESS BIT DEFINITIONS
 *
 *  3333 3333 3322 2222 2222 1111 1111 11
 *  9876 5432 1098 7654 3210 9876 5432 1098 7654 3210
 *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 *  1                                             000
 *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 *  |                                             |\|
 *  |                               Byte Enable --+ |
 *  |                             Transfer Length --+
 *  +-- IO space, not cached
 *
 *   Byte      Transfer
 *   Enable    Length    Transfer  Byte    Address
 *   adr<6:5>  adr<4:3>  Length    Enable  Adder
 *   ---------------------------------------------
 *      00        00      Byte      1110   0x000
 *      01        00      Byte      1101   0x020
 *      10        00      Byte      1011   0x040
 *      11        00      Byte      0111   0x060
 *
 *      00        01      Word      1100   0x008
 *      01        01      Word      1001   0x028 <= Not supported in this code.
 *      10        01      Word      0011   0x048
 *
 *      00        10      Tribyte   1000   0x010
 *      01        10      Tribyte   0001   0x030
 *
 *      10        11      Longword  0000   0x058
 *
 *      Note that byte enables are निश्चितed low.
 *
 */

#घोषणा MCPCIA_MAX_HOSES 4

#घोषणा MCPCIA_MID(m)		((अचिन्हित दीर्घ)(m) << 33)

/* Dodge has PCI0 and PCI1 at MID 4 and 5 respectively. 
   Durango adds PCI2 and PCI3 at MID 6 and 7 respectively.  */
#घोषणा MCPCIA_HOSE2MID(h)	((h) + 4)

#घोषणा MCPCIA_MEM_MASK 0x07ffffff /* SPARSE Mem region mask is 27 bits */

/*
 * Memory spaces:
 */
#घोषणा MCPCIA_SPARSE(m)	(IDENT_ADDR + 0xf000000000UL + MCPCIA_MID(m))
#घोषणा MCPCIA_DENSE(m)		(IDENT_ADDR + 0xf100000000UL + MCPCIA_MID(m))
#घोषणा MCPCIA_IO(m)		(IDENT_ADDR + 0xf180000000UL + MCPCIA_MID(m))
#घोषणा MCPCIA_CONF(m)		(IDENT_ADDR + 0xf1c0000000UL + MCPCIA_MID(m))
#घोषणा MCPCIA_CSR(m)		(IDENT_ADDR + 0xf1e0000000UL + MCPCIA_MID(m))
#घोषणा MCPCIA_IO_IACK(m)	(IDENT_ADDR + 0xf1f0000000UL + MCPCIA_MID(m))
#घोषणा MCPCIA_DENSE_IO(m)	(IDENT_ADDR + 0xe1fc000000UL + MCPCIA_MID(m))
#घोषणा MCPCIA_DENSE_CONF(m)	(IDENT_ADDR + 0xe1fe000000UL + MCPCIA_MID(m))

/*
 *  General Registers
 */
#घोषणा MCPCIA_REV(m)		(MCPCIA_CSR(m) + 0x000)
#घोषणा MCPCIA_WHOAMI(m)	(MCPCIA_CSR(m) + 0x040)
#घोषणा MCPCIA_PCI_LAT(m)	(MCPCIA_CSR(m) + 0x080)
#घोषणा MCPCIA_CAP_CTRL(m)	(MCPCIA_CSR(m) + 0x100)
#घोषणा MCPCIA_HAE_MEM(m)	(MCPCIA_CSR(m) + 0x400)
#घोषणा MCPCIA_HAE_IO(m)	(MCPCIA_CSR(m) + 0x440)
#घोषणा _MCPCIA_IACK_SC(m)	(MCPCIA_CSR(m) + 0x480)
#घोषणा MCPCIA_HAE_DENSE(m)	(MCPCIA_CSR(m) + 0x4C0)

/*
 * Interrupt Control रेजिस्टरs
 */
#घोषणा MCPCIA_INT_CTL(m)	(MCPCIA_CSR(m) + 0x500)
#घोषणा MCPCIA_INT_REQ(m)	(MCPCIA_CSR(m) + 0x540)
#घोषणा MCPCIA_INT_TARG(m)	(MCPCIA_CSR(m) + 0x580)
#घोषणा MCPCIA_INT_ADR(m)	(MCPCIA_CSR(m) + 0x5C0)
#घोषणा MCPCIA_INT_ADR_EXT(m)	(MCPCIA_CSR(m) + 0x600)
#घोषणा MCPCIA_INT_MASK0(m)	(MCPCIA_CSR(m) + 0x640)
#घोषणा MCPCIA_INT_MASK1(m)	(MCPCIA_CSR(m) + 0x680)
#घोषणा MCPCIA_INT_ACK0(m)	(MCPCIA_CSR(m) + 0x10003f00)
#घोषणा MCPCIA_INT_ACK1(m)	(MCPCIA_CSR(m) + 0x10003f40)

/*
 * Perक्रमmance Monitor रेजिस्टरs
 */
#घोषणा MCPCIA_PERF_MON(m)	(MCPCIA_CSR(m) + 0x300)
#घोषणा MCPCIA_PERF_CONT(m)	(MCPCIA_CSR(m) + 0x340)

/*
 * Diagnostic Registers
 */
#घोषणा MCPCIA_CAP_DIAG(m)	(MCPCIA_CSR(m) + 0x700)
#घोषणा MCPCIA_TOP_OF_MEM(m)	(MCPCIA_CSR(m) + 0x7C0)

/*
 * Error रेजिस्टरs
 */
#घोषणा MCPCIA_MC_ERR0(m)	(MCPCIA_CSR(m) + 0x800)
#घोषणा MCPCIA_MC_ERR1(m)	(MCPCIA_CSR(m) + 0x840)
#घोषणा MCPCIA_CAP_ERR(m)	(MCPCIA_CSR(m) + 0x880)
#घोषणा MCPCIA_PCI_ERR1(m)	(MCPCIA_CSR(m) + 0x1040)
#घोषणा MCPCIA_MDPA_STAT(m)	(MCPCIA_CSR(m) + 0x4000)
#घोषणा MCPCIA_MDPA_SYN(m)	(MCPCIA_CSR(m) + 0x4040)
#घोषणा MCPCIA_MDPA_DIAG(m)	(MCPCIA_CSR(m) + 0x4080)
#घोषणा MCPCIA_MDPB_STAT(m)	(MCPCIA_CSR(m) + 0x8000)
#घोषणा MCPCIA_MDPB_SYN(m)	(MCPCIA_CSR(m) + 0x8040)
#घोषणा MCPCIA_MDPB_DIAG(m)	(MCPCIA_CSR(m) + 0x8080)

/*
 * PCI Address Translation Registers.
 */
#घोषणा MCPCIA_SG_TBIA(m)	(MCPCIA_CSR(m) + 0x1300)
#घोषणा MCPCIA_HBASE(m)		(MCPCIA_CSR(m) + 0x1340)

#घोषणा MCPCIA_W0_BASE(m)	(MCPCIA_CSR(m) + 0x1400)
#घोषणा MCPCIA_W0_MASK(m)	(MCPCIA_CSR(m) + 0x1440)
#घोषणा MCPCIA_T0_BASE(m)	(MCPCIA_CSR(m) + 0x1480)

#घोषणा MCPCIA_W1_BASE(m)	(MCPCIA_CSR(m) + 0x1500)
#घोषणा MCPCIA_W1_MASK(m)	(MCPCIA_CSR(m) + 0x1540)
#घोषणा MCPCIA_T1_BASE(m)	(MCPCIA_CSR(m) + 0x1580)

#घोषणा MCPCIA_W2_BASE(m)	(MCPCIA_CSR(m) + 0x1600)
#घोषणा MCPCIA_W2_MASK(m)	(MCPCIA_CSR(m) + 0x1640)
#घोषणा MCPCIA_T2_BASE(m)	(MCPCIA_CSR(m) + 0x1680)

#घोषणा MCPCIA_W3_BASE(m)	(MCPCIA_CSR(m) + 0x1700)
#घोषणा MCPCIA_W3_MASK(m)	(MCPCIA_CSR(m) + 0x1740)
#घोषणा MCPCIA_T3_BASE(m)	(MCPCIA_CSR(m) + 0x1780)

/* Hack!  Only words क्रम bus 0.  */

#अगर_अघोषित MCPCIA_ONE_HAE_WINDOW
#घोषणा MCPCIA_HAE_ADDRESS	MCPCIA_HAE_MEM(4)
#पूर्ण_अगर
#घोषणा MCPCIA_IACK_SC		_MCPCIA_IACK_SC(4)

/* 
 * The canonical non-remaped I/O and MEM addresses have these values
 * subtracted out.  This is arranged so that folks manipulating ISA
 * devices can use their familiar numbers and have them map to bus 0.
 */

#घोषणा MCPCIA_IO_BIAS		MCPCIA_IO(4)
#घोषणा MCPCIA_MEM_BIAS		MCPCIA_DENSE(4)

/* Offset between ram physical addresses and pci64 DAC bus addresses.  */
#घोषणा MCPCIA_DAC_OFFSET	(1UL << 40)

/*
 * Data काष्ठाure क्रम handling MCPCIA machine checks:
 */
काष्ठा el_MCPCIA_uncorrected_frame_mcheck अणु
	काष्ठा el_common header;
	काष्ठा el_common_EV5_uncorrectable_mcheck procdata;
पूर्ण;


#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions:
 *
 * MCPCIA, the RAWHIDE family PCI/memory support chipset क्रम the EV5 (21164)
 * and EV56 (21164a) processors, can use either a sparse address mapping
 * scheme, or the so-called byte-word PCI address space, to get at PCI memory
 * and I/O.
 *
 * Unक्रमtunately, we can't use BWIO with EV5, so क्रम now, we always use SPARSE.
 */

/*
 * Memory functions.  64-bit and 32-bit accesses are करोne through
 * dense memory space, everything अन्यथा through sparse space.
 *
 * For पढ़ोing and writing 8 and 16 bit quantities we need to
 * go through one of the three sparse address mapping regions
 * and use the HAE_MEM CSR to provide some bits of the address.
 * The following few routines use only sparse address region 1
 * which gives 1Gbyte of accessible space which relates exactly
 * to the amount of PCI memory mapping *पूर्णांकo* प्रणाली address space.
 * See p 6-17 of the specअगरication but it looks something like this:
 *
 * 21164 Address:
 *
 *          3         2         1
 * 9876543210987654321098765432109876543210
 * 1ZZZZ0.PCI.QW.Address............BBLL
 *
 * ZZ = SBZ
 * BB = Byte offset
 * LL = Transfer length
 *
 * PCI Address:
 *
 * 3         2         1
 * 10987654321098765432109876543210
 * HHH....PCI.QW.Address........ 00
 *
 * HHH = 31:29 HAE_MEM CSR
 *
 */

#घोषणा vip	अस्थिर पूर्णांक __क्रमce *
#घोषणा vuip	अस्थिर अचिन्हित पूर्णांक __क्रमce *

#अगर_अघोषित MCPCIA_ONE_HAE_WINDOW
#घोषणा MCPCIA_FROB_MMIO						\
	अगर (__mcpcia_is_mmio(hose)) अणु					\
		set_hae(hose & 0xffffffff);				\
		hose = hose - MCPCIA_DENSE(4) + MCPCIA_SPARSE(4);	\
	पूर्ण
#अन्यथा
#घोषणा MCPCIA_FROB_MMIO						\
	अगर (__mcpcia_is_mmio(hose)) अणु					\
		hose = hose - MCPCIA_DENSE(4) + MCPCIA_SPARSE(4);	\
	पूर्ण
#पूर्ण_अगर

बाह्य अंतरभूत पूर्णांक __mcpcia_is_mmio(अचिन्हित दीर्घ addr)
अणु
	वापस (addr & 0x80000000UL) == 0;
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक mcpcia_ioपढ़ो8(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)xaddr & MCPCIA_MEM_MASK;
	अचिन्हित दीर्घ hose = (अचिन्हित दीर्घ)xaddr & ~MCPCIA_MEM_MASK;
	अचिन्हित दीर्घ result;

	MCPCIA_FROB_MMIO;

	result = *(vip) ((addr << 5) + hose + 0x00);
	वापस __kernel_extbl(result, addr & 3);
पूर्ण

__EXTERN_INLINE व्योम mcpcia_ioग_लिखो8(u8 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)xaddr & MCPCIA_MEM_MASK;
	अचिन्हित दीर्घ hose = (अचिन्हित दीर्घ)xaddr & ~MCPCIA_MEM_MASK;
	अचिन्हित दीर्घ w;

	MCPCIA_FROB_MMIO;

	w = __kernel_insbl(b, addr & 3);
	*(vuip) ((addr << 5) + hose + 0x00) = w;
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक mcpcia_ioपढ़ो16(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)xaddr & MCPCIA_MEM_MASK;
	अचिन्हित दीर्घ hose = (अचिन्हित दीर्घ)xaddr & ~MCPCIA_MEM_MASK;
	अचिन्हित दीर्घ result;

	MCPCIA_FROB_MMIO;

	result = *(vip) ((addr << 5) + hose + 0x08);
	वापस __kernel_extwl(result, addr & 3);
पूर्ण

__EXTERN_INLINE व्योम mcpcia_ioग_लिखो16(u16 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)xaddr & MCPCIA_MEM_MASK;
	अचिन्हित दीर्घ hose = (अचिन्हित दीर्घ)xaddr & ~MCPCIA_MEM_MASK;
	अचिन्हित दीर्घ w;

	MCPCIA_FROB_MMIO;

	w = __kernel_inswl(b, addr & 3);
	*(vuip) ((addr << 5) + hose + 0x08) = w;
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक mcpcia_ioपढ़ो32(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)xaddr;

	अगर (!__mcpcia_is_mmio(addr))
		addr = ((addr & 0xffff) << 5) + (addr & ~0xfffful) + 0x18;

	वापस *(vuip)addr;
पूर्ण

__EXTERN_INLINE व्योम mcpcia_ioग_लिखो32(u32 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)xaddr;

	अगर (!__mcpcia_is_mmio(addr))
		addr = ((addr & 0xffff) << 5) + (addr & ~0xfffful) + 0x18;

	*(vuip)addr = b;
पूर्ण


__EXTERN_INLINE व्योम __iomem *mcpcia_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)(addr + MCPCIA_IO_BIAS);
पूर्ण

__EXTERN_INLINE व्योम __iomem *mcpcia_ioremap(अचिन्हित दीर्घ addr,
					     अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)(addr + MCPCIA_MEM_BIAS);
पूर्ण

__EXTERN_INLINE पूर्णांक mcpcia_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= MCPCIA_SPARSE(0);
पूर्ण

__EXTERN_INLINE पूर्णांक mcpcia_is_mmio(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	वापस __mcpcia_is_mmio(addr);
पूर्ण

#अघोषित MCPCIA_FROB_MMIO

#अघोषित vip
#अघोषित vuip

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		mcpcia
#घोषणा mcpcia_trivial_rw_bw	2
#घोषणा mcpcia_trivial_rw_lq	1
#घोषणा mcpcia_trivial_io_bw	0
#घोषणा mcpcia_trivial_io_lq	0
#घोषणा mcpcia_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_MCPCIA__H__ */
