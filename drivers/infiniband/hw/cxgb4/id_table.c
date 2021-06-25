<शैली गुरु>
/*
 * Copyright (c) 2011 Chelsio Communications.  All rights reserved.
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
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश "iw_cxgb4.h"

#घोषणा RANDOM_SKIP 16

/*
 * Trivial biपंचांगap-based allocator. If the अक्रमom flag is set, the
 * allocator is deचिन्हित to:
 * - pseuकरो-अक्रमomize the id वापसed such that it is not trivially predictable.
 * - aव्योम reuse of recently used id (at the expense of predictability)
 */
u32 c4iw_id_alloc(काष्ठा c4iw_id_table *alloc)
अणु
	अचिन्हित दीर्घ flags;
	u32 obj;

	spin_lock_irqsave(&alloc->lock, flags);

	obj = find_next_zero_bit(alloc->table, alloc->max, alloc->last);
	अगर (obj >= alloc->max)
		obj = find_first_zero_bit(alloc->table, alloc->max);

	अगर (obj < alloc->max) अणु
		अगर (alloc->flags & C4IW_ID_TABLE_F_RANDOM)
			alloc->last += pअक्रमom_u32() % RANDOM_SKIP;
		अन्यथा
			alloc->last = obj + 1;
		अगर (alloc->last >= alloc->max)
			alloc->last = 0;
		set_bit(obj, alloc->table);
		obj += alloc->start;
	पूर्ण अन्यथा
		obj = -1;

	spin_unlock_irqrestore(&alloc->lock, flags);
	वापस obj;
पूर्ण

व्योम c4iw_id_मुक्त(काष्ठा c4iw_id_table *alloc, u32 obj)
अणु
	अचिन्हित दीर्घ flags;

	obj -= alloc->start;

	spin_lock_irqsave(&alloc->lock, flags);
	clear_bit(obj, alloc->table);
	spin_unlock_irqrestore(&alloc->lock, flags);
पूर्ण

पूर्णांक c4iw_id_table_alloc(काष्ठा c4iw_id_table *alloc, u32 start, u32 num,
			u32 reserved, u32 flags)
अणु
	पूर्णांक i;

	alloc->start = start;
	alloc->flags = flags;
	अगर (flags & C4IW_ID_TABLE_F_RANDOM)
		alloc->last = pअक्रमom_u32() % RANDOM_SKIP;
	अन्यथा
		alloc->last = 0;
	alloc->max  = num;
	spin_lock_init(&alloc->lock);
	alloc->table = kदो_स्मृति_array(BITS_TO_LONGS(num), माप(दीर्घ),
				     GFP_KERNEL);
	अगर (!alloc->table)
		वापस -ENOMEM;

	biपंचांगap_zero(alloc->table, num);
	अगर (!(alloc->flags & C4IW_ID_TABLE_F_EMPTY))
		क्रम (i = 0; i < reserved; ++i)
			set_bit(i, alloc->table);

	वापस 0;
पूर्ण

व्योम c4iw_id_table_मुक्त(काष्ठा c4iw_id_table *alloc)
अणु
	kमुक्त(alloc->table);
पूर्ण
