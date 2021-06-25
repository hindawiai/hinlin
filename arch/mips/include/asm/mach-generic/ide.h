<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994-1996  Linus Torvalds & authors
 *
 * Copied from i386; many of the especially older MIPS or ISA-based platक्रमms
 * are basically identical.  Using this file probably implies i8259 PIC
 * support in a प्रणाली but the very least पूर्णांकerrupt numbers 0 - 15 need to
 * be put aside क्रम legacy devices.
 */
#अगर_अघोषित __ASM_MACH_GENERIC_IDE_H
#घोषणा __ASM_MACH_GENERIC_IDE_H

#अगर_घोषित __KERNEL__

#समावेश <linux/pci.h>
#समावेश <linux/मानकघोष.स>
#समावेश <यंत्र/processor.h>

/* MIPS port and memory-mapped I/O string operations.  */
अटल अंतरभूत व्योम __ide_flush_prologue(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (cpu_has_dc_aliases || !cpu_has_ic_fills_f_dc)
		preempt_disable();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम __ide_flush_epilogue(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (cpu_has_dc_aliases || !cpu_has_ic_fills_f_dc)
		preempt_enable();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम __ide_flush_dcache_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अगर (cpu_has_dc_aliases || !cpu_has_ic_fills_f_dc) अणु
		अचिन्हित दीर्घ end = addr + size;

		जबतक (addr < end) अणु
			local_flush_data_cache_page((व्योम *)addr);
			addr += PAGE_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * insw() and gang might be called with पूर्णांकerrupts disabled, so we can't
 * send IPIs क्रम flushing due to the potencial of deadlocks, see the comment
 * above smp_call_function() in arch/mips/kernel/smp.c.	 We work around the
 * problem by disabling preemption so we know we actually perक्रमm the flush
 * on the processor that actually has the lines to be flushed which hopefully
 * is even better क्रम perक्रमmance anyway.
 */
अटल अंतरभूत व्योम __ide_insw(अचिन्हित दीर्घ port, व्योम *addr,
	अचिन्हित पूर्णांक count)
अणु
	__ide_flush_prologue();
	insw(port, addr, count);
	__ide_flush_dcache_range((अचिन्हित दीर्घ)addr, count * 2);
	__ide_flush_epilogue();
पूर्ण

अटल अंतरभूत व्योम __ide_insl(अचिन्हित दीर्घ port, व्योम *addr, अचिन्हित पूर्णांक count)
अणु
	__ide_flush_prologue();
	insl(port, addr, count);
	__ide_flush_dcache_range((अचिन्हित दीर्घ)addr, count * 4);
	__ide_flush_epilogue();
पूर्ण

अटल अंतरभूत व्योम __ide_outsw(अचिन्हित दीर्घ port, स्थिर व्योम *addr,
	अचिन्हित दीर्घ count)
अणु
	__ide_flush_prologue();
	outsw(port, addr, count);
	__ide_flush_dcache_range((अचिन्हित दीर्घ)addr, count * 2);
	__ide_flush_epilogue();
पूर्ण

अटल अंतरभूत व्योम __ide_outsl(अचिन्हित दीर्घ port, स्थिर व्योम *addr,
	अचिन्हित दीर्घ count)
अणु
	__ide_flush_prologue();
	outsl(port, addr, count);
	__ide_flush_dcache_range((अचिन्हित दीर्घ)addr, count * 4);
	__ide_flush_epilogue();
पूर्ण

अटल अंतरभूत व्योम __ide_mm_insw(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	__ide_flush_prologue();
	पढ़ोsw(port, addr, count);
	__ide_flush_dcache_range((अचिन्हित दीर्घ)addr, count * 2);
	__ide_flush_epilogue();
पूर्ण

अटल अंतरभूत व्योम __ide_mm_insl(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	__ide_flush_prologue();
	पढ़ोsl(port, addr, count);
	__ide_flush_dcache_range((अचिन्हित दीर्घ)addr, count * 4);
	__ide_flush_epilogue();
पूर्ण

अटल अंतरभूत व्योम __ide_mm_outsw(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	__ide_flush_prologue();
	ग_लिखोsw(port, addr, count);
	__ide_flush_dcache_range((अचिन्हित दीर्घ)addr, count * 2);
	__ide_flush_epilogue();
पूर्ण

अटल अंतरभूत व्योम __ide_mm_outsl(व्योम __iomem * port, व्योम *addr, u32 count)
अणु
	__ide_flush_prologue();
	ग_लिखोsl(port, addr, count);
	__ide_flush_dcache_range((अचिन्हित दीर्घ)addr, count * 4);
	__ide_flush_epilogue();
पूर्ण

/* ide_insw calls insw, not __ide_insw.	 Why? */
#अघोषित insw
#अघोषित insl
#अघोषित outsw
#अघोषित outsl
#घोषणा insw(port, addr, count) __ide_insw(port, addr, count)
#घोषणा insl(port, addr, count) __ide_insl(port, addr, count)
#घोषणा outsw(port, addr, count) __ide_outsw(port, addr, count)
#घोषणा outsl(port, addr, count) __ide_outsl(port, addr, count)

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASM_MACH_GENERIC_IDE_H */
