<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * अणुपढ़ो,ग_लिखोपूर्णअणुb,w,l,qपूर्ण based on arch/arm64/include/यंत्र/पन.स
 *   which was based on arch/arm/include/पन.स
 *
 * Copyright (C) 1996-2000 Russell King
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2014 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_IO_H
#घोषणा _ASM_RISCV_IO_H

#समावेश <linux/types.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/mmiowb.h>
#समावेश <यंत्र/early_ioremap.h>

/*
 * MMIO access functions are separated out to अवरोध dependency cycles
 * when using अणुपढ़ो,ग_लिखोपूर्ण* fns in low-level headers
 */
#समावेश <यंत्र/mmपन.स>

/*
 *  I/O port access स्थिरants.
 */
#अगर_घोषित CONFIG_MMU
#घोषणा IO_SPACE_LIMIT		(PCI_IO_SIZE - 1)
#घोषणा PCI_IOBASE		((व्योम __iomem *)PCI_IO_START)
#पूर्ण_अगर /* CONFIG_MMU */

/*
 * Emulation routines क्रम the port-mapped IO space used by some PCI drivers.
 * These are defined as being "fully synchronous", but also "not guaranteed to
 * be fully ordered with respect to other memory and I/O operations".  We're
 * going to be on the safe side here and just make them:
 *  - Fully ordered WRT each other, by bracketing them with two fences.  The
 *    outer set contains both I/O so inX is ordered with outX, जबतक the inner just
 *    needs the type of the access (I क्रम inX and O क्रम outX).
 *  - Ordered in the same manner as पढ़ोX/ग_लिखोX WRT memory by subsuming their
 *    fences.
 *  - Ordered WRT समयr पढ़ोs, so udelay and मित्रs करोn't get elided by the
 *    implementation.
 * Note that there is no way to actually enक्रमce that outX is a non-posted
 * operation on RISC-V, but hopefully the समयr ordering स्थिरraपूर्णांक is
 * sufficient to ensure this works sanely on controllers that support I/O
 * ग_लिखोs.
 */
#घोषणा __io_pbr()	__यंत्र__ __अस्थिर__ ("fence io,i"  : : : "memory");
#घोषणा __io_par(v)	__यंत्र__ __अस्थिर__ ("fence i,ior" : : : "memory");
#घोषणा __io_pbw()	__यंत्र__ __अस्थिर__ ("fence iow,o" : : : "memory");
#घोषणा __io_paw()	__यंत्र__ __अस्थिर__ ("fence o,io"  : : : "memory");

#घोषणा inb(c)		(अणु u8  __v; __io_pbr(); __v = पढ़ोb_cpu((व्योम*)(PCI_IOBASE + (c))); __io_par(__v); __v; पूर्ण)
#घोषणा inw(c)		(अणु u16 __v; __io_pbr(); __v = पढ़ोw_cpu((व्योम*)(PCI_IOBASE + (c))); __io_par(__v); __v; पूर्ण)
#घोषणा inl(c)		(अणु u32 __v; __io_pbr(); __v = पढ़ोl_cpu((व्योम*)(PCI_IOBASE + (c))); __io_par(__v); __v; पूर्ण)

#घोषणा outb(v,c)	(अणु __io_pbw(); ग_लिखोb_cpu((v),(व्योम*)(PCI_IOBASE + (c))); __io_paw(); पूर्ण)
#घोषणा outw(v,c)	(अणु __io_pbw(); ग_लिखोw_cpu((v),(व्योम*)(PCI_IOBASE + (c))); __io_paw(); पूर्ण)
#घोषणा outl(v,c)	(अणु __io_pbw(); ग_लिखोl_cpu((v),(व्योम*)(PCI_IOBASE + (c))); __io_paw(); पूर्ण)

#अगर_घोषित CONFIG_64BIT
#घोषणा inq(c)		(अणु u64 __v; __io_pbr(); __v = पढ़ोq_cpu((व्योम*)(c)); __io_par(__v); __v; पूर्ण)
#घोषणा outq(v,c)	(अणु __io_pbw(); ग_लिखोq_cpu((v),(व्योम*)(c)); __io_paw(); पूर्ण)
#पूर्ण_अगर

/*
 * Accesses from a single hart to a single I/O address must be ordered.  This
 * allows us to use the raw पढ़ो macros, but we still need to fence beक्रमe and
 * after the block to ensure ordering WRT other macros.  These are defined to
 * perक्रमm host-endian accesses so we use __raw instead of __cpu.
 */
#घोषणा __io_पढ़ोs_ins(port, ctype, len, bfence, afence)			\
	अटल अंतरभूत व्योम __ ## port ## len(स्थिर अस्थिर व्योम __iomem *addr,	\
					     व्योम *buffer,			\
					     अचिन्हित पूर्णांक count)		\
	अणु									\
		bfence;								\
		अगर (count) अणु							\
			ctype *buf = buffer;					\
										\
			करो अणु							\
				ctype x = __raw_पढ़ो ## len(addr);		\
				*buf++ = x;					\
			पूर्ण जबतक (--count);					\
		पूर्ण								\
		afence;								\
	पूर्ण

#घोषणा __io_ग_लिखोs_outs(port, ctype, len, bfence, afence)			\
	अटल अंतरभूत व्योम __ ## port ## len(अस्थिर व्योम __iomem *addr,	\
					     स्थिर व्योम *buffer,		\
					     अचिन्हित पूर्णांक count)		\
	अणु									\
		bfence;								\
		अगर (count) अणु							\
			स्थिर ctype *buf = buffer;				\
										\
			करो अणु							\
				__raw_ग_लिखो ## len(*buf++, addr);		\
			पूर्ण जबतक (--count);					\
		पूर्ण								\
		afence;								\
	पूर्ण

__io_पढ़ोs_ins(पढ़ोs,  u8, b, __io_br(), __io_ar(addr))
__io_पढ़ोs_ins(पढ़ोs, u16, w, __io_br(), __io_ar(addr))
__io_पढ़ोs_ins(पढ़ोs, u32, l, __io_br(), __io_ar(addr))
#घोषणा पढ़ोsb(addr, buffer, count) __पढ़ोsb(addr, buffer, count)
#घोषणा पढ़ोsw(addr, buffer, count) __पढ़ोsw(addr, buffer, count)
#घोषणा पढ़ोsl(addr, buffer, count) __पढ़ोsl(addr, buffer, count)

__io_पढ़ोs_ins(ins,  u8, b, __io_pbr(), __io_par(addr))
__io_पढ़ोs_ins(ins, u16, w, __io_pbr(), __io_par(addr))
__io_पढ़ोs_ins(ins, u32, l, __io_pbr(), __io_par(addr))
#घोषणा insb(addr, buffer, count) __insb((व्योम __iomem *)(दीर्घ)addr, buffer, count)
#घोषणा insw(addr, buffer, count) __insw((व्योम __iomem *)(दीर्घ)addr, buffer, count)
#घोषणा insl(addr, buffer, count) __insl((व्योम __iomem *)(दीर्घ)addr, buffer, count)

__io_ग_लिखोs_outs(ग_लिखोs,  u8, b, __io_bw(), __io_aw())
__io_ग_लिखोs_outs(ग_लिखोs, u16, w, __io_bw(), __io_aw())
__io_ग_लिखोs_outs(ग_लिखोs, u32, l, __io_bw(), __io_aw())
#घोषणा ग_लिखोsb(addr, buffer, count) __ग_लिखोsb(addr, buffer, count)
#घोषणा ग_लिखोsw(addr, buffer, count) __ग_लिखोsw(addr, buffer, count)
#घोषणा ग_लिखोsl(addr, buffer, count) __ग_लिखोsl(addr, buffer, count)

__io_ग_लिखोs_outs(outs,  u8, b, __io_pbw(), __io_paw())
__io_ग_लिखोs_outs(outs, u16, w, __io_pbw(), __io_paw())
__io_ग_लिखोs_outs(outs, u32, l, __io_pbw(), __io_paw())
#घोषणा outsb(addr, buffer, count) __outsb((व्योम __iomem *)(दीर्घ)addr, buffer, count)
#घोषणा outsw(addr, buffer, count) __outsw((व्योम __iomem *)(दीर्घ)addr, buffer, count)
#घोषणा outsl(addr, buffer, count) __outsl((व्योम __iomem *)(दीर्घ)addr, buffer, count)

#अगर_घोषित CONFIG_64BIT
__io_पढ़ोs_ins(पढ़ोs, u64, q, __io_br(), __io_ar(addr))
#घोषणा पढ़ोsq(addr, buffer, count) __पढ़ोsq(addr, buffer, count)

__io_पढ़ोs_ins(ins, u64, q, __io_pbr(), __io_par(addr))
#घोषणा insq(addr, buffer, count) __insq((व्योम __iomem *)addr, buffer, count)

__io_ग_लिखोs_outs(ग_लिखोs, u64, q, __io_bw(), __io_aw())
#घोषणा ग_लिखोsq(addr, buffer, count) __ग_लिखोsq(addr, buffer, count)

__io_ग_लिखोs_outs(outs, u64, q, __io_pbr(), __io_paw())
#घोषणा outsq(addr, buffer, count) __outsq((व्योम __iomem *)addr, buffer, count)
#पूर्ण_अगर

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर /* _ASM_RISCV_IO_H */
