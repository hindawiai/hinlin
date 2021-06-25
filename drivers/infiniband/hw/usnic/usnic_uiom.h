<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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
 *
 */

#अगर_अघोषित USNIC_UIOM_H_
#घोषणा USNIC_UIOM_H_

#समावेश <linux/list.h>
#समावेश <linux/scatterlist.h>

#समावेश "usnic_uiom_interval_tree.h"

काष्ठा ib_ucontext;

#घोषणा USNIC_UIOM_READ			(1)
#घोषणा USNIC_UIOM_WRITE		(2)

#घोषणा USNIC_UIOM_MAX_PD_CNT		(1000)
#घोषणा USNIC_UIOM_MAX_MR_CNT		(1000000)
#घोषणा USNIC_UIOM_MAX_MR_SIZE		(~0UL)
#घोषणा USNIC_UIOM_PAGE_SIZE		(PAGE_SIZE)

काष्ठा usnic_uiom_dev अणु
	काष्ठा device			*dev;
	काष्ठा list_head		link;
पूर्ण;

काष्ठा usnic_uiom_pd अणु
	काष्ठा iommu_करोमुख्य		*करोमुख्य;
	spinlock_t			lock;
	काष्ठा rb_root_cached		root;
	काष्ठा list_head		devs;
	पूर्णांक				dev_cnt;
पूर्ण;

काष्ठा usnic_uiom_reg अणु
	काष्ठा usnic_uiom_pd		*pd;
	अचिन्हित दीर्घ			va;
	माप_प्रकार				length;
	पूर्णांक				offset;
	पूर्णांक				page_size;
	पूर्णांक				writable;
	काष्ठा list_head		chunk_list;
	काष्ठा work_काष्ठा		work;
	काष्ठा mm_काष्ठा		*owning_mm;
पूर्ण;

काष्ठा usnic_uiom_chunk अणु
	काष्ठा list_head		list;
	पूर्णांक				nents;
	काष्ठा scatterlist		page_list[];
पूर्ण;

काष्ठा usnic_uiom_pd *usnic_uiom_alloc_pd(व्योम);
व्योम usnic_uiom_dealloc_pd(काष्ठा usnic_uiom_pd *pd);
पूर्णांक usnic_uiom_attach_dev_to_pd(काष्ठा usnic_uiom_pd *pd, काष्ठा device *dev);
व्योम usnic_uiom_detach_dev_from_pd(काष्ठा usnic_uiom_pd *pd,
					काष्ठा device *dev);
काष्ठा device **usnic_uiom_get_dev_list(काष्ठा usnic_uiom_pd *pd);
व्योम usnic_uiom_मुक्त_dev_list(काष्ठा device **devs);
काष्ठा usnic_uiom_reg *usnic_uiom_reg_get(काष्ठा usnic_uiom_pd *pd,
						अचिन्हित दीर्घ addr, माप_प्रकार size,
						पूर्णांक access, पूर्णांक dmasync);
व्योम usnic_uiom_reg_release(काष्ठा usnic_uiom_reg *uiomr);
पूर्णांक usnic_uiom_init(अक्षर *drv_name);
#पूर्ण_अगर /* USNIC_UIOM_H_ */
