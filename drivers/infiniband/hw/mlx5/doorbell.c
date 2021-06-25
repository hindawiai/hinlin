<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/kref.h>
#समावेश <linux/slab.h>
#समावेश <rdma/ib_uस्मृति.स>

#समावेश "mlx5_ib.h"

काष्ठा mlx5_ib_user_db_page अणु
	काष्ठा list_head	list;
	काष्ठा ib_umem	       *umem;
	अचिन्हित दीर्घ		user_virt;
	पूर्णांक			refcnt;
	काष्ठा mm_काष्ठा	*mm;
पूर्ण;

पूर्णांक mlx5_ib_db_map_user(काष्ठा mlx5_ib_ucontext *context,
			काष्ठा ib_udata *udata, अचिन्हित दीर्घ virt,
			काष्ठा mlx5_db *db)
अणु
	काष्ठा mlx5_ib_user_db_page *page;
	पूर्णांक err = 0;

	mutex_lock(&context->db_page_mutex);

	list_क्रम_each_entry(page, &context->db_page_list, list)
		अगर ((current->mm == page->mm) &&
		    (page->user_virt == (virt & PAGE_MASK)))
			जाओ found;

	page = kदो_स्मृति(माप(*page), GFP_KERNEL);
	अगर (!page) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	page->user_virt = (virt & PAGE_MASK);
	page->refcnt    = 0;
	page->umem = ib_umem_get(context->ibucontext.device, virt & PAGE_MASK,
				 PAGE_SIZE, 0);
	अगर (IS_ERR(page->umem)) अणु
		err = PTR_ERR(page->umem);
		kमुक्त(page);
		जाओ out;
	पूर्ण
	mmgrab(current->mm);
	page->mm = current->mm;

	list_add(&page->list, &context->db_page_list);

found:
	db->dma = sg_dma_address(page->umem->sg_head.sgl) + (virt & ~PAGE_MASK);
	db->u.user_page = page;
	++page->refcnt;

out:
	mutex_unlock(&context->db_page_mutex);

	वापस err;
पूर्ण

व्योम mlx5_ib_db_unmap_user(काष्ठा mlx5_ib_ucontext *context, काष्ठा mlx5_db *db)
अणु
	mutex_lock(&context->db_page_mutex);

	अगर (!--db->u.user_page->refcnt) अणु
		list_del(&db->u.user_page->list);
		mmdrop(db->u.user_page->mm);
		ib_umem_release(db->u.user_page->umem);
		kमुक्त(db->u.user_page);
	पूर्ण

	mutex_unlock(&context->db_page_mutex);
पूर्ण
