<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause) */
/*
 * Copyright (c) 2017 Hisilicon Limited.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश "hns_roce_device.h"

पूर्णांक hns_roce_db_map_user(काष्ठा hns_roce_ucontext *context,
			 काष्ठा ib_udata *udata, अचिन्हित दीर्घ virt,
			 काष्ठा hns_roce_db *db)
अणु
	अचिन्हित दीर्घ page_addr = virt & PAGE_MASK;
	काष्ठा hns_roce_user_db_page *page;
	अचिन्हित पूर्णांक offset;
	पूर्णांक ret = 0;

	mutex_lock(&context->page_mutex);

	list_क्रम_each_entry(page, &context->page_list, list)
		अगर (page->user_virt == page_addr)
			जाओ found;

	page = kदो_स्मृति(माप(*page), GFP_KERNEL);
	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	refcount_set(&page->refcount, 1);
	page->user_virt = page_addr;
	page->umem = ib_umem_get(context->ibucontext.device, page_addr,
				 PAGE_SIZE, 0);
	अगर (IS_ERR(page->umem)) अणु
		ret = PTR_ERR(page->umem);
		kमुक्त(page);
		जाओ out;
	पूर्ण

	list_add(&page->list, &context->page_list);

found:
	offset = virt - page_addr;
	db->dma = sg_dma_address(page->umem->sg_head.sgl) + offset;
	db->virt_addr = sg_virt(page->umem->sg_head.sgl) + offset;
	db->u.user_page = page;
	refcount_inc(&page->refcount);

out:
	mutex_unlock(&context->page_mutex);

	वापस ret;
पूर्ण

व्योम hns_roce_db_unmap_user(काष्ठा hns_roce_ucontext *context,
			    काष्ठा hns_roce_db *db)
अणु
	mutex_lock(&context->page_mutex);

	refcount_dec(&db->u.user_page->refcount);
	अगर (refcount_dec_अगर_one(&db->u.user_page->refcount)) अणु
		list_del(&db->u.user_page->list);
		ib_umem_release(db->u.user_page->umem);
		kमुक्त(db->u.user_page);
	पूर्ण

	mutex_unlock(&context->page_mutex);
पूर्ण

अटल काष्ठा hns_roce_db_pgdir *hns_roce_alloc_db_pgdir(
					काष्ठा device *dma_device)
अणु
	काष्ठा hns_roce_db_pgdir *pgdir;

	pgdir = kzalloc(माप(*pgdir), GFP_KERNEL);
	अगर (!pgdir)
		वापस शून्य;

	biपंचांगap_fill(pgdir->order1,
		    HNS_ROCE_DB_PER_PAGE / HNS_ROCE_DB_TYPE_COUNT);
	pgdir->bits[0] = pgdir->order0;
	pgdir->bits[1] = pgdir->order1;
	pgdir->page = dma_alloc_coherent(dma_device, PAGE_SIZE,
					 &pgdir->db_dma, GFP_KERNEL);
	अगर (!pgdir->page) अणु
		kमुक्त(pgdir);
		वापस शून्य;
	पूर्ण

	वापस pgdir;
पूर्ण

अटल पूर्णांक hns_roce_alloc_db_from_pgdir(काष्ठा hns_roce_db_pgdir *pgdir,
					काष्ठा hns_roce_db *db, पूर्णांक order)
अणु
	अचिन्हित दीर्घ o;
	अचिन्हित दीर्घ i;

	क्रम (o = order; o <= 1; ++o) अणु
		i = find_first_bit(pgdir->bits[o], HNS_ROCE_DB_PER_PAGE >> o);
		अगर (i < HNS_ROCE_DB_PER_PAGE >> o)
			जाओ found;
	पूर्ण

	वापस -ENOMEM;

found:
	clear_bit(i, pgdir->bits[o]);

	i <<= o;

	अगर (o > order)
		set_bit(i ^ 1, pgdir->bits[order]);

	db->u.pgdir	= pgdir;
	db->index	= i;
	db->db_record	= pgdir->page + db->index;
	db->dma		= pgdir->db_dma  + db->index * HNS_ROCE_DB_UNIT_SIZE;
	db->order	= order;

	वापस 0;
पूर्ण

पूर्णांक hns_roce_alloc_db(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_db *db,
		      पूर्णांक order)
अणु
	काष्ठा hns_roce_db_pgdir *pgdir;
	पूर्णांक ret = 0;

	mutex_lock(&hr_dev->pgdir_mutex);

	list_क्रम_each_entry(pgdir, &hr_dev->pgdir_list, list)
		अगर (!hns_roce_alloc_db_from_pgdir(pgdir, db, order))
			जाओ out;

	pgdir = hns_roce_alloc_db_pgdir(hr_dev->dev);
	अगर (!pgdir) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	list_add(&pgdir->list, &hr_dev->pgdir_list);

	/* This should never fail -- we just allocated an empty page: */
	WARN_ON(hns_roce_alloc_db_from_pgdir(pgdir, db, order));

out:
	mutex_unlock(&hr_dev->pgdir_mutex);

	वापस ret;
पूर्ण

व्योम hns_roce_मुक्त_db(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_db *db)
अणु
	अचिन्हित दीर्घ o;
	अचिन्हित दीर्घ i;

	mutex_lock(&hr_dev->pgdir_mutex);

	o = db->order;
	i = db->index;

	अगर (db->order == 0 && test_bit(i ^ 1, db->u.pgdir->order0)) अणु
		clear_bit(i ^ 1, db->u.pgdir->order0);
		++o;
	पूर्ण

	i >>= o;
	set_bit(i, db->u.pgdir->bits[o]);

	अगर (biपंचांगap_full(db->u.pgdir->order1,
			HNS_ROCE_DB_PER_PAGE / HNS_ROCE_DB_TYPE_COUNT)) अणु
		dma_मुक्त_coherent(hr_dev->dev, PAGE_SIZE, db->u.pgdir->page,
				  db->u.pgdir->db_dma);
		list_del(&db->u.pgdir->list);
		kमुक्त(db->u.pgdir);
	पूर्ण

	mutex_unlock(&hr_dev->pgdir_mutex);
पूर्ण
