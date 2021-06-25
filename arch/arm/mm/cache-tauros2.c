<शैली गुरु>
/*
 * arch/arm/mm/cache-tauros2.c - Tauros2 L2 cache controller support
 *
 * Copyright (C) 2008 Marvell Semiconductor
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * References:
 * - PJ1 CPU Core Datasheet,
 *   Document ID MV-S104837-01, Rev 0.7, January 24 2008.
 * - PJ4 CPU Core Datasheet,
 *   Document ID MV-S105190-00, Rev 0.7, March 14 2008.
 */

#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/hardware/cache-tauros2.h>

/* CP15 PJ4 Control configuration रेजिस्टर */
#घोषणा CCR_L2C_PREFETCH_DISABLE	BIT(24)
#घोषणा CCR_L2C_ECC_ENABLE		BIT(23)
#घोषणा CCR_L2C_WAY7_4_DISABLE		BIT(21)
#घोषणा CCR_L2C_BURST8_ENABLE		BIT(20)

/*
 * When Tauros2 is used on a CPU that supports the v7 hierarchical
 * cache operations, the cache handling code in proc-v7.S takes care
 * of everything, including handling DMA coherency.
 *
 * So, we only need to रेजिस्टर outer cache operations here अगर we're
 * being used on a pre-v7 CPU, and we only need to build support क्रम
 * outer cache operations पूर्णांकo the kernel image अगर the kernel has been
 * configured to support a pre-v7 CPU.
 */
#अगर_घोषित CONFIG_CPU_32v5
/*
 * Low-level cache मुख्यtenance operations.
 */
अटल अंतरभूत व्योम tauros2_clean_pa(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__("mcr p15, 1, %0, c7, c11, 3" : : "r" (addr));
पूर्ण

अटल अंतरभूत व्योम tauros2_clean_inv_pa(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__("mcr p15, 1, %0, c7, c15, 3" : : "r" (addr));
पूर्ण

अटल अंतरभूत व्योम tauros2_inv_pa(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__("mcr p15, 1, %0, c7, c7, 3" : : "r" (addr));
पूर्ण


/*
 * Linux primitives.
 *
 * Note that the end addresses passed to Linux primitives are
 * noninclusive.
 */
#घोषणा CACHE_LINE_SIZE		32

अटल व्योम tauros2_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * Clean and invalidate partial first cache line.
	 */
	अगर (start & (CACHE_LINE_SIZE - 1)) अणु
		tauros2_clean_inv_pa(start & ~(CACHE_LINE_SIZE - 1));
		start = (start | (CACHE_LINE_SIZE - 1)) + 1;
	पूर्ण

	/*
	 * Clean and invalidate partial last cache line.
	 */
	अगर (end & (CACHE_LINE_SIZE - 1)) अणु
		tauros2_clean_inv_pa(end & ~(CACHE_LINE_SIZE - 1));
		end &= ~(CACHE_LINE_SIZE - 1);
	पूर्ण

	/*
	 * Invalidate all full cache lines between 'start' and 'end'.
	 */
	जबतक (start < end) अणु
		tauros2_inv_pa(start);
		start += CACHE_LINE_SIZE;
	पूर्ण

	dsb();
पूर्ण

अटल व्योम tauros2_clean_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	start &= ~(CACHE_LINE_SIZE - 1);
	जबतक (start < end) अणु
		tauros2_clean_pa(start);
		start += CACHE_LINE_SIZE;
	पूर्ण

	dsb();
पूर्ण

अटल व्योम tauros2_flush_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	start &= ~(CACHE_LINE_SIZE - 1);
	जबतक (start < end) अणु
		tauros2_clean_inv_pa(start);
		start += CACHE_LINE_SIZE;
	पूर्ण

	dsb();
पूर्ण

अटल व्योम tauros2_disable(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
	"mcr	p15, 1, %0, c7, c11, 0 @L2 Cache Clean All\n\t"
	"mrc	p15, 0, %0, c1, c0, 0\n\t"
	"bic	%0, %0, #(1 << 26)\n\t"
	"mcr	p15, 0, %0, c1, c0, 0  @Disable L2 Cache\n\t"
	: : "r" (0x0));
पूर्ण

अटल व्योम tauros2_resume(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
	"mcr	p15, 1, %0, c7, c7, 0 @L2 Cache Invalidate All\n\t"
	"mrc	p15, 0, %0, c1, c0, 0\n\t"
	"orr	%0, %0, #(1 << 26)\n\t"
	"mcr	p15, 0, %0, c1, c0, 0 @Enable L2 Cache\n\t"
	: : "r" (0x0));
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u32 __init पढ़ो_extra_features(व्योम)
अणु
	u32 u;

	__यंत्र__("mrc p15, 1, %0, c15, c1, 0" : "=r" (u));

	वापस u;
पूर्ण

अटल अंतरभूत व्योम __init ग_लिखो_extra_features(u32 u)
अणु
	__यंत्र__("mcr p15, 1, %0, c15, c1, 0" : : "r" (u));
पूर्ण

अटल अंतरभूत पूर्णांक __init cpuid_scheme(व्योम)
अणु
	वापस !!((processor_id & 0x000f0000) == 0x000f0000);
पूर्ण

अटल अंतरभूत u32 __init पढ़ो_mmfr3(व्योम)
अणु
	u32 mmfr3;

	__यंत्र__("mrc p15, 0, %0, c0, c1, 7\n" : "=r" (mmfr3));

	वापस mmfr3;
पूर्ण

अटल अंतरभूत u32 __init पढ़ो_actlr(व्योम)
अणु
	u32 actlr;

	__यंत्र__("mrc p15, 0, %0, c1, c0, 1\n" : "=r" (actlr));

	वापस actlr;
पूर्ण

अटल अंतरभूत व्योम __init ग_लिखो_actlr(u32 actlr)
अणु
	__यंत्र__("mcr p15, 0, %0, c1, c0, 1\n" : : "r" (actlr));
पूर्ण

अटल व्योम enable_extra_feature(अचिन्हित पूर्णांक features)
अणु
	u32 u;

	u = पढ़ो_extra_features();

	अगर (features & CACHE_TAUROS2_PREFETCH_ON)
		u &= ~CCR_L2C_PREFETCH_DISABLE;
	अन्यथा
		u |= CCR_L2C_PREFETCH_DISABLE;
	pr_info("Tauros2: %s L2 prefetch.\n",
			(features & CACHE_TAUROS2_PREFETCH_ON)
			? "Enabling" : "Disabling");

	अगर (features & CACHE_TAUROS2_LINEFILL_BURST8)
		u |= CCR_L2C_BURST8_ENABLE;
	अन्यथा
		u &= ~CCR_L2C_BURST8_ENABLE;
	pr_info("Tauros2: %s burst8 line fill.\n",
			(features & CACHE_TAUROS2_LINEFILL_BURST8)
			? "Enabling" : "Disabling");

	ग_लिखो_extra_features(u);
पूर्ण

अटल व्योम __init tauros2_पूर्णांकernal_init(अचिन्हित पूर्णांक features)
अणु
	अक्षर *mode = शून्य;

	enable_extra_feature(features);

#अगर_घोषित CONFIG_CPU_32v5
	अगर ((processor_id & 0xff0f0000) == 0x56050000) अणु
		u32 feat;

		/*
		 * v5 CPUs with Tauros2 have the L2 cache enable bit
		 * located in the CPU Extra Features रेजिस्टर.
		 */
		feat = पढ़ो_extra_features();
		अगर (!(feat & 0x00400000)) अणु
			pr_info("Tauros2: Enabling L2 cache.\n");
			ग_लिखो_extra_features(feat | 0x00400000);
		पूर्ण

		mode = "ARMv5";
		outer_cache.inv_range = tauros2_inv_range;
		outer_cache.clean_range = tauros2_clean_range;
		outer_cache.flush_range = tauros2_flush_range;
		outer_cache.disable = tauros2_disable;
		outer_cache.resume = tauros2_resume;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_32v7
	/*
	 * Check whether this CPU has support क्रम the v7 hierarchical
	 * cache ops.  (PJ4 is in its v7 personality mode अगर the MMFR3
	 * रेजिस्टर indicates support क्रम the v7 hierarchical cache
	 * ops.)
	 *
	 * (Although strictly speaking there may exist CPUs that
	 * implement the v7 cache ops but are only ARMv6 CPUs (due to
	 * not complying with all of the other ARMv7 requirements),
	 * there are no real-lअगरe examples of Tauros2 being used on
	 * such CPUs as of yet.)
	 */
	अगर (cpuid_scheme() && (पढ़ो_mmfr3() & 0xf) == 1) अणु
		u32 actlr;

		/*
		 * When Tauros2 is used in an ARMv7 प्रणाली, the L2
		 * enable bit is located in the Auxiliary System Control
		 * Register (which is the only रेजिस्टर allowed by the
		 * ARMv7 spec to contain fine-grained cache control bits).
		 */
		actlr = पढ़ो_actlr();
		अगर (!(actlr & 0x00000002)) अणु
			pr_info("Tauros2: Enabling L2 cache.\n");
			ग_लिखो_actlr(actlr | 0x00000002);
		पूर्ण

		mode = "ARMv7";
	पूर्ण
#पूर्ण_अगर

	अगर (mode == शून्य) अणु
		pr_crit("Tauros2: Unable to detect CPU mode.\n");
		वापस;
	पूर्ण

	pr_info("Tauros2: L2 cache support initialised "
			 "in %s mode.\n", mode);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tauros2_ids[] __initस्थिर = अणु
	अणु .compatible = "marvell,tauros2-cache"पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

व्योम __init tauros2_init(अचिन्हित पूर्णांक features)
अणु
#अगर_घोषित CONFIG_OF
	काष्ठा device_node *node;
	पूर्णांक ret;
	अचिन्हित पूर्णांक f;

	node = of_find_matching_node(शून्य, tauros2_ids);
	अगर (!node) अणु
		pr_info("Not found marvell,tauros2-cache, disable it\n");
	पूर्ण अन्यथा अणु
		ret = of_property_पढ़ो_u32(node, "marvell,tauros2-cache-features", &f);
		अगर (ret) अणु
			pr_info("Not found marvell,tauros-cache-features property, "
				"disable extra features\n");
			features = 0;
		पूर्ण अन्यथा
			features = f;
	पूर्ण
#पूर्ण_अगर
	tauros2_पूर्णांकernal_init(features);
पूर्ण
