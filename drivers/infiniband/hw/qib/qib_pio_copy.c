<शैली गुरु>
/*
 * Copyright (c) 2009 QLogic Corporation. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "qib.h"

/**
 * qib_pio_copy - copy data to MMIO space, in multiples of 32-bits
 * @to: destination, in MMIO space (must be 64-bit aligned)
 * @from: source (must be 64-bit aligned)
 * @count: number of 32-bit quantities to copy
 *
 * Copy data from kernel space to MMIO space, in multiples of 32 bits at a
 * समय.  Order of access is not guaranteed, nor is a memory barrier
 * perक्रमmed afterwards.
 */
व्योम qib_pio_copy(व्योम __iomem *to, स्थिर व्योम *from, माप_प्रकार count)
अणु
#अगर_घोषित CONFIG_64BIT
	u64 __iomem *dst = to;
	स्थिर u64 *src = from;
	स्थिर u64 *end = src + (count >> 1);

	जबतक (src < end)
		__raw_ग_लिखोq(*src++, dst++);
	अगर (count & 1)
		__raw_ग_लिखोl(*(स्थिर u32 *)src, dst);
#अन्यथा
	u32 __iomem *dst = to;
	स्थिर u32 *src = from;
	स्थिर u32 *end = src + count;

	जबतक (src < end)
		__raw_ग_लिखोl(*src++, dst++);
#पूर्ण_अगर
पूर्ण
