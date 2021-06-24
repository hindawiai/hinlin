<शैली गुरु>
/*
 * Cache control क्रम MicroBlaze cache memories
 *
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007-2009 John Williams <john.williams@petalogix.com>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/cache.h>
#समावेश <यंत्र/cpuinfo.h>
#समावेश <यंत्र/pvr.h>

अटल अंतरभूत व्योम __enable_icache_msr(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("	 msrset	r0, %0;"	\
				"nop;"			\
			: : "i" (MSR_ICE) : "memory");
पूर्ण

अटल अंतरभूत व्योम __disable_icache_msr(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("	 msrclr	r0, %0;"	\
				"nop;"			\
			: : "i" (MSR_ICE) : "memory");
पूर्ण

अटल अंतरभूत व्योम __enable_dcache_msr(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("	 msrset	r0, %0;"	\
				"nop;"			\
			: : "i" (MSR_DCE) : "memory");
पूर्ण

अटल अंतरभूत व्योम __disable_dcache_msr(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("	 msrclr	r0, %0;"	\
				"nop; "			\
			: : "i" (MSR_DCE) : "memory");
पूर्ण

अटल अंतरभूत व्योम __enable_icache_nomsr(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("	 mfs	r12, rmsr;"	\
				"nop;"			\
				"ori	r12, r12, %0;"	\
				"mts	rmsr, r12;"	\
				"nop;"			\
			: : "i" (MSR_ICE) : "memory", "r12");
पूर्ण

अटल अंतरभूत व्योम __disable_icache_nomsr(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("	 mfs	r12, rmsr;"	\
				"nop;"			\
				"andi	r12, r12, ~%0;"	\
				"mts	rmsr, r12;"	\
				"nop;"			\
			: : "i" (MSR_ICE) : "memory", "r12");
पूर्ण

अटल अंतरभूत व्योम __enable_dcache_nomsr(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("	 mfs	r12, rmsr;"	\
				"nop;"			\
				"ori	r12, r12, %0;"	\
				"mts	rmsr, r12;"	\
				"nop;"			\
			: : "i" (MSR_DCE) : "memory", "r12");
पूर्ण

अटल अंतरभूत व्योम __disable_dcache_nomsr(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("	 mfs	r12, rmsr;"	\
				"nop;"			\
				"andi	r12, r12, ~%0;"	\
				"mts	rmsr, r12;"	\
				"nop;"			\
			: : "i" (MSR_DCE) : "memory", "r12");
पूर्ण


/* Helper macro क्रम computing the limits of cache range loops
 *
 * End address can be unaligned which is OK क्रम C implementation.
 * ASM implementation align it in ASM macros
 */
#घोषणा CACHE_LOOP_LIMITS(start, end, cache_line_length, cache_size)	\
करो अणु									\
	पूर्णांक align = ~(cache_line_length - 1);				\
	अगर (start <  अच_पूर्णांक_उच्च - cache_size)				\
		end = min(start + cache_size, end);			\
	start &= align;							\
पूर्ण जबतक (0)

/*
 * Helper macro to loop over the specअगरied cache_size/line_length and
 * execute 'op' on that cacheline
 */
#घोषणा CACHE_ALL_LOOP(cache_size, line_length, op)			\
करो अणु									\
	अचिन्हित पूर्णांक len = cache_size - line_length;			\
	पूर्णांक step = -line_length;					\
	WARN_ON(step >= 0);						\
									\
	__यंत्र__ __अस्थिर__ (" 1:      " #op " %0, r0;"		\
					"bgtid   %0, 1b;"		\
					"addk    %0, %0, %1;"		\
					: : "r" (len), "r" (step)	\
					: "memory");			\
पूर्ण जबतक (0)

/* Used क्रम wdc.flush/clear which can use rB क्रम offset which is not possible
 * to use क्रम simple wdc or wic.
 *
 * start address is cache aligned
 * end address is not aligned, अगर end is aligned then I have to subtract
 * cacheline length because I can't flush/invalidate the next cacheline.
 * If is not, I align it because I will flush/invalidate whole line.
 */
#घोषणा CACHE_RANGE_LOOP_2(start, end, line_length, op)			\
करो अणु									\
	पूर्णांक step = -line_length;					\
	पूर्णांक align = ~(line_length - 1);					\
	पूर्णांक count;							\
	end = ((end & align) == end) ? end - line_length : end & align;	\
	count = end - start;						\
	WARN_ON(count < 0);						\
									\
	__यंत्र__ __अस्थिर__ (" 1:	" #op "	%0, %1;"		\
					"bgtid	%1, 1b;"		\
					"addk	%1, %1, %2;"		\
					: : "r" (start), "r" (count),	\
					"r" (step) : "memory");		\
पूर्ण जबतक (0)

/* It is used only first parameter क्रम OP - क्रम wic, wdc */
#घोषणा CACHE_RANGE_LOOP_1(start, end, line_length, op)			\
करो अणु									\
	अचिन्हित पूर्णांक अस्थिर temp = 0;						\
	अचिन्हित पूर्णांक align = ~(line_length - 1);					\
	end = ((end & align) == end) ? end - line_length : end & align;	\
	WARN_ON(end < start);					\
									\
	__यंत्र__ __अस्थिर__ (" 1:	" #op "	%1, r0;"		\
					"cmpu	%0, %1, %2;"		\
					"bgtid	%0, 1b;"		\
					"addk	%1, %1, %3;"		\
				: : "r" (temp), "r" (start), "r" (end),	\
					"r" (line_length) : "memory");	\
पूर्ण जबतक (0)

#घोषणा ASM_LOOP

अटल व्योम __flush_icache_range_msr_irq(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ flags;
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s: start 0x%x, end 0x%x\n", __func__,
				(अचिन्हित पूर्णांक)start, (अचिन्हित पूर्णांक) end);

	CACHE_LOOP_LIMITS(start, end,
			cpuinfo.icache_line_length, cpuinfo.icache_size);

	local_irq_save(flags);
	__disable_icache_msr();

#अगर_घोषित ASM_LOOP
	CACHE_RANGE_LOOP_1(start, end, cpuinfo.icache_line_length, wic);
#अन्यथा
	क्रम (i = start; i < end; i += cpuinfo.icache_line_length)
		__यंत्र__ __अस्थिर__ ("wic	%0, r0;"	\
				: : "r" (i));
#पूर्ण_अगर
	__enable_icache_msr();
	local_irq_restore(flags);
पूर्ण

अटल व्योम __flush_icache_range_nomsr_irq(अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ flags;
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s: start 0x%x, end 0x%x\n", __func__,
				(अचिन्हित पूर्णांक)start, (अचिन्हित पूर्णांक) end);

	CACHE_LOOP_LIMITS(start, end,
			cpuinfo.icache_line_length, cpuinfo.icache_size);

	local_irq_save(flags);
	__disable_icache_nomsr();

#अगर_घोषित ASM_LOOP
	CACHE_RANGE_LOOP_1(start, end, cpuinfo.icache_line_length, wic);
#अन्यथा
	क्रम (i = start; i < end; i += cpuinfo.icache_line_length)
		__यंत्र__ __अस्थिर__ ("wic	%0, r0;"	\
				: : "r" (i));
#पूर्ण_अगर

	__enable_icache_nomsr();
	local_irq_restore(flags);
पूर्ण

अटल व्योम __flush_icache_range_noirq(अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ end)
अणु
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s: start 0x%x, end 0x%x\n", __func__,
				(अचिन्हित पूर्णांक)start, (अचिन्हित पूर्णांक) end);

	CACHE_LOOP_LIMITS(start, end,
			cpuinfo.icache_line_length, cpuinfo.icache_size);
#अगर_घोषित ASM_LOOP
	CACHE_RANGE_LOOP_1(start, end, cpuinfo.icache_line_length, wic);
#अन्यथा
	क्रम (i = start; i < end; i += cpuinfo.icache_line_length)
		__यंत्र__ __अस्थिर__ ("wic	%0, r0;"	\
				: : "r" (i));
#पूर्ण_अगर
पूर्ण

अटल व्योम __flush_icache_all_msr_irq(व्योम)
अणु
	अचिन्हित दीर्घ flags;
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s\n", __func__);

	local_irq_save(flags);
	__disable_icache_msr();
#अगर_घोषित ASM_LOOP
	CACHE_ALL_LOOP(cpuinfo.icache_size, cpuinfo.icache_line_length, wic);
#अन्यथा
	क्रम (i = 0; i < cpuinfo.icache_size;
		 i += cpuinfo.icache_line_length)
			__यंत्र__ __अस्थिर__ ("wic	%0, r0;" \
					: : "r" (i));
#पूर्ण_अगर
	__enable_icache_msr();
	local_irq_restore(flags);
पूर्ण

अटल व्योम __flush_icache_all_nomsr_irq(व्योम)
अणु
	अचिन्हित दीर्घ flags;
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s\n", __func__);

	local_irq_save(flags);
	__disable_icache_nomsr();
#अगर_घोषित ASM_LOOP
	CACHE_ALL_LOOP(cpuinfo.icache_size, cpuinfo.icache_line_length, wic);
#अन्यथा
	क्रम (i = 0; i < cpuinfo.icache_size;
		 i += cpuinfo.icache_line_length)
			__यंत्र__ __अस्थिर__ ("wic	%0, r0;" \
					: : "r" (i));
#पूर्ण_अगर
	__enable_icache_nomsr();
	local_irq_restore(flags);
पूर्ण

अटल व्योम __flush_icache_all_noirq(व्योम)
अणु
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s\n", __func__);
#अगर_घोषित ASM_LOOP
	CACHE_ALL_LOOP(cpuinfo.icache_size, cpuinfo.icache_line_length, wic);
#अन्यथा
	क्रम (i = 0; i < cpuinfo.icache_size;
		 i += cpuinfo.icache_line_length)
			__यंत्र__ __अस्थिर__ ("wic	%0, r0;" \
					: : "r" (i));
#पूर्ण_अगर
पूर्ण

अटल व्योम __invalidate_dcache_all_msr_irq(व्योम)
अणु
	अचिन्हित दीर्घ flags;
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s\n", __func__);

	local_irq_save(flags);
	__disable_dcache_msr();
#अगर_घोषित ASM_LOOP
	CACHE_ALL_LOOP(cpuinfo.dcache_size, cpuinfo.dcache_line_length, wdc);
#अन्यथा
	क्रम (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_line_length)
			__यंत्र__ __अस्थिर__ ("wdc	%0, r0;" \
					: : "r" (i));
#पूर्ण_अगर
	__enable_dcache_msr();
	local_irq_restore(flags);
पूर्ण

अटल व्योम __invalidate_dcache_all_nomsr_irq(व्योम)
अणु
	अचिन्हित दीर्घ flags;
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s\n", __func__);

	local_irq_save(flags);
	__disable_dcache_nomsr();
#अगर_घोषित ASM_LOOP
	CACHE_ALL_LOOP(cpuinfo.dcache_size, cpuinfo.dcache_line_length, wdc);
#अन्यथा
	क्रम (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_line_length)
			__यंत्र__ __अस्थिर__ ("wdc	%0, r0;" \
					: : "r" (i));
#पूर्ण_अगर
	__enable_dcache_nomsr();
	local_irq_restore(flags);
पूर्ण

अटल व्योम __invalidate_dcache_all_noirq_wt(व्योम)
अणु
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s\n", __func__);
#अगर_घोषित ASM_LOOP
	CACHE_ALL_LOOP(cpuinfo.dcache_size, cpuinfo.dcache_line_length, wdc);
#अन्यथा
	क्रम (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_line_length)
			__यंत्र__ __अस्थिर__ ("wdc	%0, r0;" \
					: : "r" (i));
#पूर्ण_अगर
पूर्ण

/*
 * FIXME It is blindly invalidation as is expected
 * but can't be called on noMMU in microblaze_cache_init below
 *
 * MS: noMMU kernel won't boot अगर simple wdc is used
 * The reason should be that there are discared data which kernel needs
 */
अटल व्योम __invalidate_dcache_all_wb(व्योम)
अणु
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s\n", __func__);
#अगर_घोषित ASM_LOOP
	CACHE_ALL_LOOP(cpuinfo.dcache_size, cpuinfo.dcache_line_length,
					wdc);
#अन्यथा
	क्रम (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_line_length)
			__यंत्र__ __अस्थिर__ ("wdc	%0, r0;" \
					: : "r" (i));
#पूर्ण_अगर
पूर्ण

अटल व्योम __invalidate_dcache_range_wb(अचिन्हित दीर्घ start,
						अचिन्हित दीर्घ end)
अणु
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s: start 0x%x, end 0x%x\n", __func__,
				(अचिन्हित पूर्णांक)start, (अचिन्हित पूर्णांक) end);

	CACHE_LOOP_LIMITS(start, end,
			cpuinfo.dcache_line_length, cpuinfo.dcache_size);
#अगर_घोषित ASM_LOOP
	CACHE_RANGE_LOOP_2(start, end, cpuinfo.dcache_line_length, wdc.clear);
#अन्यथा
	क्रम (i = start; i < end; i += cpuinfo.dcache_line_length)
		__यंत्र__ __अस्थिर__ ("wdc.clear	%0, r0;"	\
				: : "r" (i));
#पूर्ण_अगर
पूर्ण

अटल व्योम __invalidate_dcache_range_nomsr_wt(अचिन्हित दीर्घ start,
							अचिन्हित दीर्घ end)
अणु
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s: start 0x%x, end 0x%x\n", __func__,
				(अचिन्हित पूर्णांक)start, (अचिन्हित पूर्णांक) end);
	CACHE_LOOP_LIMITS(start, end,
			cpuinfo.dcache_line_length, cpuinfo.dcache_size);

#अगर_घोषित ASM_LOOP
	CACHE_RANGE_LOOP_1(start, end, cpuinfo.dcache_line_length, wdc);
#अन्यथा
	क्रम (i = start; i < end; i += cpuinfo.dcache_line_length)
		__यंत्र__ __अस्थिर__ ("wdc	%0, r0;"	\
				: : "r" (i));
#पूर्ण_अगर
पूर्ण

अटल व्योम __invalidate_dcache_range_msr_irq_wt(अचिन्हित दीर्घ start,
							अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ flags;
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s: start 0x%x, end 0x%x\n", __func__,
				(अचिन्हित पूर्णांक)start, (अचिन्हित पूर्णांक) end);
	CACHE_LOOP_LIMITS(start, end,
			cpuinfo.dcache_line_length, cpuinfo.dcache_size);

	local_irq_save(flags);
	__disable_dcache_msr();

#अगर_घोषित ASM_LOOP
	CACHE_RANGE_LOOP_1(start, end, cpuinfo.dcache_line_length, wdc);
#अन्यथा
	क्रम (i = start; i < end; i += cpuinfo.dcache_line_length)
		__यंत्र__ __अस्थिर__ ("wdc	%0, r0;"	\
				: : "r" (i));
#पूर्ण_अगर

	__enable_dcache_msr();
	local_irq_restore(flags);
पूर्ण

अटल व्योम __invalidate_dcache_range_nomsr_irq(अचिन्हित दीर्घ start,
							अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ flags;
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s: start 0x%x, end 0x%x\n", __func__,
				(अचिन्हित पूर्णांक)start, (अचिन्हित पूर्णांक) end);

	CACHE_LOOP_LIMITS(start, end,
			cpuinfo.dcache_line_length, cpuinfo.dcache_size);

	local_irq_save(flags);
	__disable_dcache_nomsr();

#अगर_घोषित ASM_LOOP
	CACHE_RANGE_LOOP_1(start, end, cpuinfo.dcache_line_length, wdc);
#अन्यथा
	क्रम (i = start; i < end; i += cpuinfo.dcache_line_length)
		__यंत्र__ __अस्थिर__ ("wdc	%0, r0;"	\
				: : "r" (i));
#पूर्ण_अगर

	__enable_dcache_nomsr();
	local_irq_restore(flags);
पूर्ण

अटल व्योम __flush_dcache_all_wb(व्योम)
अणु
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s\n", __func__);
#अगर_घोषित ASM_LOOP
	CACHE_ALL_LOOP(cpuinfo.dcache_size, cpuinfo.dcache_line_length,
				wdc.flush);
#अन्यथा
	क्रम (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_line_length)
			__यंत्र__ __अस्थिर__ ("wdc.flush	%0, r0;" \
					: : "r" (i));
#पूर्ण_अगर
पूर्ण

अटल व्योम __flush_dcache_range_wb(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
#अगर_अघोषित ASM_LOOP
	पूर्णांक i;
#पूर्ण_अगर
	pr_debug("%s: start 0x%x, end 0x%x\n", __func__,
				(अचिन्हित पूर्णांक)start, (अचिन्हित पूर्णांक) end);

	CACHE_LOOP_LIMITS(start, end,
			cpuinfo.dcache_line_length, cpuinfo.dcache_size);
#अगर_घोषित ASM_LOOP
	CACHE_RANGE_LOOP_2(start, end, cpuinfo.dcache_line_length, wdc.flush);
#अन्यथा
	क्रम (i = start; i < end; i += cpuinfo.dcache_line_length)
		__यंत्र__ __अस्थिर__ ("wdc.flush	%0, r0;"	\
				: : "r" (i));
#पूर्ण_अगर
पूर्ण

/* काष्ठा क्रम wb caches and क्रम wt caches */
काष्ठा scache *mbc;

/* new wb cache model */
अटल स्थिर काष्ठा scache wb_msr = अणु
	.ie = __enable_icache_msr,
	.id = __disable_icache_msr,
	.अगरl = __flush_icache_all_noirq,
	.अगरlr = __flush_icache_range_noirq,
	.iin = __flush_icache_all_noirq,
	.iinr = __flush_icache_range_noirq,
	.de = __enable_dcache_msr,
	.dd = __disable_dcache_msr,
	.dfl = __flush_dcache_all_wb,
	.dflr = __flush_dcache_range_wb,
	.din = __invalidate_dcache_all_wb,
	.dinr = __invalidate_dcache_range_wb,
पूर्ण;

/* There is only dअगरference in ie, id, de, dd functions */
अटल स्थिर काष्ठा scache wb_nomsr = अणु
	.ie = __enable_icache_nomsr,
	.id = __disable_icache_nomsr,
	.अगरl = __flush_icache_all_noirq,
	.अगरlr = __flush_icache_range_noirq,
	.iin = __flush_icache_all_noirq,
	.iinr = __flush_icache_range_noirq,
	.de = __enable_dcache_nomsr,
	.dd = __disable_dcache_nomsr,
	.dfl = __flush_dcache_all_wb,
	.dflr = __flush_dcache_range_wb,
	.din = __invalidate_dcache_all_wb,
	.dinr = __invalidate_dcache_range_wb,
पूर्ण;

/* Old wt cache model with disabling irq and turn off cache */
अटल स्थिर काष्ठा scache wt_msr = अणु
	.ie = __enable_icache_msr,
	.id = __disable_icache_msr,
	.अगरl = __flush_icache_all_msr_irq,
	.अगरlr = __flush_icache_range_msr_irq,
	.iin = __flush_icache_all_msr_irq,
	.iinr = __flush_icache_range_msr_irq,
	.de = __enable_dcache_msr,
	.dd = __disable_dcache_msr,
	.dfl = __invalidate_dcache_all_msr_irq,
	.dflr = __invalidate_dcache_range_msr_irq_wt,
	.din = __invalidate_dcache_all_msr_irq,
	.dinr = __invalidate_dcache_range_msr_irq_wt,
पूर्ण;

अटल स्थिर काष्ठा scache wt_nomsr = अणु
	.ie = __enable_icache_nomsr,
	.id = __disable_icache_nomsr,
	.अगरl = __flush_icache_all_nomsr_irq,
	.अगरlr = __flush_icache_range_nomsr_irq,
	.iin = __flush_icache_all_nomsr_irq,
	.iinr = __flush_icache_range_nomsr_irq,
	.de = __enable_dcache_nomsr,
	.dd = __disable_dcache_nomsr,
	.dfl = __invalidate_dcache_all_nomsr_irq,
	.dflr = __invalidate_dcache_range_nomsr_irq,
	.din = __invalidate_dcache_all_nomsr_irq,
	.dinr = __invalidate_dcache_range_nomsr_irq,
पूर्ण;

/* New wt cache model क्रम newer Microblaze versions */
अटल स्थिर काष्ठा scache wt_msr_noirq = अणु
	.ie = __enable_icache_msr,
	.id = __disable_icache_msr,
	.अगरl = __flush_icache_all_noirq,
	.अगरlr = __flush_icache_range_noirq,
	.iin = __flush_icache_all_noirq,
	.iinr = __flush_icache_range_noirq,
	.de = __enable_dcache_msr,
	.dd = __disable_dcache_msr,
	.dfl = __invalidate_dcache_all_noirq_wt,
	.dflr = __invalidate_dcache_range_nomsr_wt,
	.din = __invalidate_dcache_all_noirq_wt,
	.dinr = __invalidate_dcache_range_nomsr_wt,
पूर्ण;

अटल स्थिर काष्ठा scache wt_nomsr_noirq = अणु
	.ie = __enable_icache_nomsr,
	.id = __disable_icache_nomsr,
	.अगरl = __flush_icache_all_noirq,
	.अगरlr = __flush_icache_range_noirq,
	.iin = __flush_icache_all_noirq,
	.iinr = __flush_icache_range_noirq,
	.de = __enable_dcache_nomsr,
	.dd = __disable_dcache_nomsr,
	.dfl = __invalidate_dcache_all_noirq_wt,
	.dflr = __invalidate_dcache_range_nomsr_wt,
	.din = __invalidate_dcache_all_noirq_wt,
	.dinr = __invalidate_dcache_range_nomsr_wt,
पूर्ण;

/* CPU version code क्रम 7.20.c - see arch/microblaze/kernel/cpu/cpuinfo.c */
#घोषणा CPUVER_7_20_A	0x0c
#घोषणा CPUVER_7_20_D	0x0f

व्योम microblaze_cache_init(व्योम)
अणु
	अगर (cpuinfo.use_instr & PVR2_USE_MSR_INSTR) अणु
		अगर (cpuinfo.dcache_wb) अणु
			pr_info("wb_msr\n");
			mbc = (काष्ठा scache *)&wb_msr;
			अगर (cpuinfo.ver_code <= CPUVER_7_20_D) अणु
				/* MS: problem with संकेत handling - hw bug */
				pr_info("WB won't work properly\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (cpuinfo.ver_code >= CPUVER_7_20_A) अणु
				pr_info("wt_msr_noirq\n");
				mbc = (काष्ठा scache *)&wt_msr_noirq;
			पूर्ण अन्यथा अणु
				pr_info("wt_msr\n");
				mbc = (काष्ठा scache *)&wt_msr;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cpuinfo.dcache_wb) अणु
			pr_info("wb_nomsr\n");
			mbc = (काष्ठा scache *)&wb_nomsr;
			अगर (cpuinfo.ver_code <= CPUVER_7_20_D) अणु
				/* MS: problem with संकेत handling - hw bug */
				pr_info("WB won't work properly\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (cpuinfo.ver_code >= CPUVER_7_20_A) अणु
				pr_info("wt_nomsr_noirq\n");
				mbc = (काष्ठा scache *)&wt_nomsr_noirq;
			पूर्ण अन्यथा अणु
				pr_info("wt_nomsr\n");
				mbc = (काष्ठा scache *)&wt_nomsr;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * FIXME Invalidation is करोne in U-BOOT
	 * WT cache: Data is alपढ़ोy written to मुख्य memory
	 * WB cache: Discard data on noMMU which caused that kernel करोesn't boot
	 */
	/* invalidate_dcache(); */
	enable_dcache();

	invalidate_icache();
	enable_icache();
पूर्ण
