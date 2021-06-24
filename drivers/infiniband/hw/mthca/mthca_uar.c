<शैली गुरु>
/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
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

#समावेश <यंत्र/page.h>		/* PAGE_SHIFT */

#समावेश "mthca_dev.h"
#समावेश "mthca_memfree.h"

पूर्णांक mthca_uar_alloc(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar)
अणु
	uar->index = mthca_alloc(&dev->uar_table.alloc);
	अगर (uar->index == -1)
		वापस -ENOMEM;

	uar->pfn = (pci_resource_start(dev->pdev, 2) >> PAGE_SHIFT) + uar->index;

	वापस 0;
पूर्ण

व्योम mthca_uar_मुक्त(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar)
अणु
	mthca_मुक्त(&dev->uar_table.alloc, uar->index);
पूर्ण

पूर्णांक mthca_init_uar_table(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक ret;

	ret = mthca_alloc_init(&dev->uar_table.alloc,
			       dev->limits.num_uars,
			       dev->limits.num_uars - 1,
			       dev->limits.reserved_uars + 1);
	अगर (ret)
		वापस ret;

	ret = mthca_init_db_tab(dev);
	अगर (ret)
		mthca_alloc_cleanup(&dev->uar_table.alloc);

	वापस ret;
पूर्ण

व्योम mthca_cleanup_uar_table(काष्ठा mthca_dev *dev)
अणु
	mthca_cleanup_db_tab(dev);

	/* XXX check अगर any UARs are still allocated? */
	mthca_alloc_cleanup(&dev->uar_table.alloc);
पूर्ण
