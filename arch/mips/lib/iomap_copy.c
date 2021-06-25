<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/export.h>
#समावेश <linux/पन.स>

/**
 * __ioपढ़ो64_copy - copy data from MMIO space, in 64-bit units
 * @to: destination (must be 64-bit aligned)
 * @from: source, in MMIO space (must be 64-bit aligned)
 * @count: number of 64-bit quantities to copy
 *
 * Copy data from MMIO space to kernel space, in units of 32 or 64 bits at a
 * समय.  Order of access is not guaranteed, nor is a memory barrier
 * perक्रमmed afterwards.
 */
व्योम __ioपढ़ो64_copy(व्योम *to, स्थिर व्योम __iomem *from, माप_प्रकार count)
अणु
#अगर_घोषित CONFIG_64BIT
	u64 *dst = to;
	स्थिर u64 __iomem *src = from;
	स्थिर u64 __iomem *end = src + count;

	जबतक (src < end)
		*dst++ = __raw_पढ़ोq(src++);
#अन्यथा
	__ioपढ़ो32_copy(to, from, count * 2);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(__ioपढ़ो64_copy);
