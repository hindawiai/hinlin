<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश "pvrdma.h"

पूर्णांक pvrdma_uar_table_init(काष्ठा pvrdma_dev *dev)
अणु
	u32 num = dev->dsr->caps.max_uar;
	u32 mask = num - 1;
	काष्ठा pvrdma_id_table *tbl = &dev->uar_table.tbl;

	अगर (!is_घातer_of_2(num))
		वापस -EINVAL;

	tbl->last = 0;
	tbl->top = 0;
	tbl->max = num;
	tbl->mask = mask;
	spin_lock_init(&tbl->lock);
	tbl->table = kसुस्मृति(BITS_TO_LONGS(num), माप(दीर्घ), GFP_KERNEL);
	अगर (!tbl->table)
		वापस -ENOMEM;

	/* 0th UAR is taken by the device. */
	set_bit(0, tbl->table);

	वापस 0;
पूर्ण

व्योम pvrdma_uar_table_cleanup(काष्ठा pvrdma_dev *dev)
अणु
	काष्ठा pvrdma_id_table *tbl = &dev->uar_table.tbl;

	kमुक्त(tbl->table);
पूर्ण

पूर्णांक pvrdma_uar_alloc(काष्ठा pvrdma_dev *dev, काष्ठा pvrdma_uar_map *uar)
अणु
	काष्ठा pvrdma_id_table *tbl;
	अचिन्हित दीर्घ flags;
	u32 obj;

	tbl = &dev->uar_table.tbl;

	spin_lock_irqsave(&tbl->lock, flags);
	obj = find_next_zero_bit(tbl->table, tbl->max, tbl->last);
	अगर (obj >= tbl->max) अणु
		tbl->top = (tbl->top + tbl->max) & tbl->mask;
		obj = find_first_zero_bit(tbl->table, tbl->max);
	पूर्ण

	अगर (obj >= tbl->max) अणु
		spin_unlock_irqrestore(&tbl->lock, flags);
		वापस -ENOMEM;
	पूर्ण

	set_bit(obj, tbl->table);
	obj |= tbl->top;

	spin_unlock_irqrestore(&tbl->lock, flags);

	uar->index = obj;
	uar->pfn = (pci_resource_start(dev->pdev, PVRDMA_PCI_RESOURCE_UAR) >>
		    PAGE_SHIFT) + uar->index;

	वापस 0;
पूर्ण

व्योम pvrdma_uar_मुक्त(काष्ठा pvrdma_dev *dev, काष्ठा pvrdma_uar_map *uar)
अणु
	काष्ठा pvrdma_id_table *tbl = &dev->uar_table.tbl;
	अचिन्हित दीर्घ flags;
	u32 obj;

	obj = uar->index & (tbl->max - 1);
	spin_lock_irqsave(&tbl->lock, flags);
	clear_bit(obj, tbl->table);
	tbl->last = min(tbl->last, obj);
	tbl->top = (tbl->top + tbl->max) & tbl->mask;
	spin_unlock_irqrestore(&tbl->lock, flags);
पूर्ण
