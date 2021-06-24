<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2006 PathScale, Inc.  All Rights Reserved.
 */

#समावेश <linux/export.h>
#समावेश <linux/पन.स>

/**
 * __ioग_लिखो32_copy - copy data to MMIO space, in 32-bit units
 * @to: destination, in MMIO space (must be 32-bit aligned)
 * @from: source (must be 32-bit aligned)
 * @count: number of 32-bit quantities to copy
 *
 * Copy data from kernel space to MMIO space, in units of 32 bits at a
 * समय.  Order of access is not guaranteed, nor is a memory barrier
 * perक्रमmed afterwards.
 */
व्योम __attribute__((weak)) __ioग_लिखो32_copy(व्योम __iomem *to,
					    स्थिर व्योम *from,
					    माप_प्रकार count)
अणु
	u32 __iomem *dst = to;
	स्थिर u32 *src = from;
	स्थिर u32 *end = src + count;

	जबतक (src < end)
		__raw_ग_लिखोl(*src++, dst++);
पूर्ण
EXPORT_SYMBOL_GPL(__ioग_लिखो32_copy);

/**
 * __ioपढ़ो32_copy - copy data from MMIO space, in 32-bit units
 * @to: destination (must be 32-bit aligned)
 * @from: source, in MMIO space (must be 32-bit aligned)
 * @count: number of 32-bit quantities to copy
 *
 * Copy data from MMIO space to kernel space, in units of 32 bits at a
 * समय.  Order of access is not guaranteed, nor is a memory barrier
 * perक्रमmed afterwards.
 */
व्योम __ioपढ़ो32_copy(व्योम *to, स्थिर व्योम __iomem *from, माप_प्रकार count)
अणु
	u32 *dst = to;
	स्थिर u32 __iomem *src = from;
	स्थिर u32 __iomem *end = src + count;

	जबतक (src < end)
		*dst++ = __raw_पढ़ोl(src++);
पूर्ण
EXPORT_SYMBOL_GPL(__ioपढ़ो32_copy);

/**
 * __ioग_लिखो64_copy - copy data to MMIO space, in 64-bit or 32-bit units
 * @to: destination, in MMIO space (must be 64-bit aligned)
 * @from: source (must be 64-bit aligned)
 * @count: number of 64-bit quantities to copy
 *
 * Copy data from kernel space to MMIO space, in units of 32 or 64 bits at a
 * समय.  Order of access is not guaranteed, nor is a memory barrier
 * perक्रमmed afterwards.
 */
व्योम __attribute__((weak)) __ioग_लिखो64_copy(व्योम __iomem *to,
					    स्थिर व्योम *from,
					    माप_प्रकार count)
अणु
#अगर_घोषित CONFIG_64BIT
	u64 __iomem *dst = to;
	स्थिर u64 *src = from;
	स्थिर u64 *end = src + count;

	जबतक (src < end)
		__raw_ग_लिखोq(*src++, dst++);
#अन्यथा
	__ioग_लिखो32_copy(to, from, count * 2);
#पूर्ण_अगर
पूर्ण

EXPORT_SYMBOL_GPL(__ioग_लिखो64_copy);
