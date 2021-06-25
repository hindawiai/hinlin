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

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mlx5/driver.h>

#समावेश "mlx5_core.h"

काष्ठा mlx5_db_pgdir अणु
	काष्ठा list_head	list;
	अचिन्हित दीर्घ	       *biपंचांगap;
	__be32		       *db_page;
	dma_addr_t		db_dma;
पूर्ण;

/* Handling क्रम queue buffers -- we allocate a bunch of memory and
 * रेजिस्टर it in a memory region at HCA भव address 0.
 */

अटल व्योम *mlx5_dma_zalloc_coherent_node(काष्ठा mlx5_core_dev *dev,
					   माप_प्रकार size, dma_addr_t *dma_handle,
					   पूर्णांक node)
अणु
	काष्ठा device *device = mlx5_core_dma_dev(dev);
	काष्ठा mlx5_priv *priv = &dev->priv;
	पूर्णांक original_node;
	व्योम *cpu_handle;

	mutex_lock(&priv->alloc_mutex);
	original_node = dev_to_node(device);
	set_dev_node(device, node);
	cpu_handle = dma_alloc_coherent(device, size, dma_handle,
					GFP_KERNEL);
	set_dev_node(device, original_node);
	mutex_unlock(&priv->alloc_mutex);
	वापस cpu_handle;
पूर्ण

अटल पूर्णांक mlx5_buf_alloc_node(काष्ठा mlx5_core_dev *dev, पूर्णांक size,
			       काष्ठा mlx5_frag_buf *buf, पूर्णांक node)
अणु
	dma_addr_t t;

	buf->size = size;
	buf->npages       = 1;
	buf->page_shअगरt   = (u8)get_order(size) + PAGE_SHIFT;

	buf->frags = kzalloc(माप(*buf->frags), GFP_KERNEL);
	अगर (!buf->frags)
		वापस -ENOMEM;

	buf->frags->buf   = mlx5_dma_zalloc_coherent_node(dev, size,
							  &t, node);
	अगर (!buf->frags->buf)
		जाओ err_out;

	buf->frags->map = t;

	जबतक (t & ((1 << buf->page_shअगरt) - 1)) अणु
		--buf->page_shअगरt;
		buf->npages *= 2;
	पूर्ण

	वापस 0;
err_out:
	kमुक्त(buf->frags);
	वापस -ENOMEM;
पूर्ण

पूर्णांक mlx5_buf_alloc(काष्ठा mlx5_core_dev *dev,
		   पूर्णांक size, काष्ठा mlx5_frag_buf *buf)
अणु
	वापस mlx5_buf_alloc_node(dev, size, buf, dev->priv.numa_node);
पूर्ण
EXPORT_SYMBOL(mlx5_buf_alloc);

व्योम mlx5_buf_मुक्त(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_frag_buf *buf)
अणु
	dma_मुक्त_coherent(mlx5_core_dma_dev(dev), buf->size, buf->frags->buf,
			  buf->frags->map);

	kमुक्त(buf->frags);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_buf_मुक्त);

पूर्णांक mlx5_frag_buf_alloc_node(काष्ठा mlx5_core_dev *dev, पूर्णांक size,
			     काष्ठा mlx5_frag_buf *buf, पूर्णांक node)
अणु
	पूर्णांक i;

	buf->size = size;
	buf->npages = DIV_ROUND_UP(size, PAGE_SIZE);
	buf->page_shअगरt = PAGE_SHIFT;
	buf->frags = kसुस्मृति(buf->npages, माप(काष्ठा mlx5_buf_list),
			     GFP_KERNEL);
	अगर (!buf->frags)
		जाओ err_out;

	क्रम (i = 0; i < buf->npages; i++) अणु
		काष्ठा mlx5_buf_list *frag = &buf->frags[i];
		पूर्णांक frag_sz = min_t(पूर्णांक, size, PAGE_SIZE);

		frag->buf = mlx5_dma_zalloc_coherent_node(dev, frag_sz,
							  &frag->map, node);
		अगर (!frag->buf)
			जाओ err_मुक्त_buf;
		अगर (frag->map & ((1 << buf->page_shअगरt) - 1)) अणु
			dma_मुक्त_coherent(mlx5_core_dma_dev(dev), frag_sz,
					  buf->frags[i].buf, buf->frags[i].map);
			mlx5_core_warn(dev, "unexpected map alignment: %pad, page_shift=%d\n",
				       &frag->map, buf->page_shअगरt);
			जाओ err_मुक्त_buf;
		पूर्ण
		size -= frag_sz;
	पूर्ण

	वापस 0;

err_मुक्त_buf:
	जबतक (i--)
		dma_मुक्त_coherent(mlx5_core_dma_dev(dev), PAGE_SIZE, buf->frags[i].buf,
				  buf->frags[i].map);
	kमुक्त(buf->frags);
err_out:
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_frag_buf_alloc_node);

व्योम mlx5_frag_buf_मुक्त(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_frag_buf *buf)
अणु
	पूर्णांक size = buf->size;
	पूर्णांक i;

	क्रम (i = 0; i < buf->npages; i++) अणु
		पूर्णांक frag_sz = min_t(पूर्णांक, size, PAGE_SIZE);

		dma_मुक्त_coherent(mlx5_core_dma_dev(dev), frag_sz, buf->frags[i].buf,
				  buf->frags[i].map);
		size -= frag_sz;
	पूर्ण
	kमुक्त(buf->frags);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_frag_buf_मुक्त);

अटल काष्ठा mlx5_db_pgdir *mlx5_alloc_db_pgdir(काष्ठा mlx5_core_dev *dev,
						 पूर्णांक node)
अणु
	u32 db_per_page = PAGE_SIZE / cache_line_size();
	काष्ठा mlx5_db_pgdir *pgdir;

	pgdir = kzalloc(माप(*pgdir), GFP_KERNEL);
	अगर (!pgdir)
		वापस शून्य;

	pgdir->biपंचांगap = biपंचांगap_zalloc(db_per_page, GFP_KERNEL);
	अगर (!pgdir->biपंचांगap) अणु
		kमुक्त(pgdir);
		वापस शून्य;
	पूर्ण

	biपंचांगap_fill(pgdir->biपंचांगap, db_per_page);

	pgdir->db_page = mlx5_dma_zalloc_coherent_node(dev, PAGE_SIZE,
						       &pgdir->db_dma, node);
	अगर (!pgdir->db_page) अणु
		biपंचांगap_मुक्त(pgdir->biपंचांगap);
		kमुक्त(pgdir);
		वापस शून्य;
	पूर्ण

	वापस pgdir;
पूर्ण

अटल पूर्णांक mlx5_alloc_db_from_pgdir(काष्ठा mlx5_db_pgdir *pgdir,
				    काष्ठा mlx5_db *db)
अणु
	u32 db_per_page = PAGE_SIZE / cache_line_size();
	पूर्णांक offset;
	पूर्णांक i;

	i = find_first_bit(pgdir->biपंचांगap, db_per_page);
	अगर (i >= db_per_page)
		वापस -ENOMEM;

	__clear_bit(i, pgdir->biपंचांगap);

	db->u.pgdir = pgdir;
	db->index   = i;
	offset = db->index * cache_line_size();
	db->db      = pgdir->db_page + offset / माप(*pgdir->db_page);
	db->dma     = pgdir->db_dma  + offset;

	db->db[0] = 0;
	db->db[1] = 0;

	वापस 0;
पूर्ण

पूर्णांक mlx5_db_alloc_node(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_db *db, पूर्णांक node)
अणु
	काष्ठा mlx5_db_pgdir *pgdir;
	पूर्णांक ret = 0;

	mutex_lock(&dev->priv.pgdir_mutex);

	list_क्रम_each_entry(pgdir, &dev->priv.pgdir_list, list)
		अगर (!mlx5_alloc_db_from_pgdir(pgdir, db))
			जाओ out;

	pgdir = mlx5_alloc_db_pgdir(dev, node);
	अगर (!pgdir) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	list_add(&pgdir->list, &dev->priv.pgdir_list);

	/* This should never fail -- we just allocated an empty page: */
	WARN_ON(mlx5_alloc_db_from_pgdir(pgdir, db));

out:
	mutex_unlock(&dev->priv.pgdir_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_db_alloc_node);

पूर्णांक mlx5_db_alloc(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_db *db)
अणु
	वापस mlx5_db_alloc_node(dev, db, dev->priv.numa_node);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_db_alloc);

व्योम mlx5_db_मुक्त(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_db *db)
अणु
	u32 db_per_page = PAGE_SIZE / cache_line_size();

	mutex_lock(&dev->priv.pgdir_mutex);

	__set_bit(db->index, db->u.pgdir->biपंचांगap);

	अगर (biपंचांगap_full(db->u.pgdir->biपंचांगap, db_per_page)) अणु
		dma_मुक्त_coherent(mlx5_core_dma_dev(dev), PAGE_SIZE,
				  db->u.pgdir->db_page, db->u.pgdir->db_dma);
		list_del(&db->u.pgdir->list);
		biपंचांगap_मुक्त(db->u.pgdir->biपंचांगap);
		kमुक्त(db->u.pgdir);
	पूर्ण

	mutex_unlock(&dev->priv.pgdir_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_db_मुक्त);

व्योम mlx5_fill_page_array(काष्ठा mlx5_frag_buf *buf, __be64 *pas)
अणु
	u64 addr;
	पूर्णांक i;

	क्रम (i = 0; i < buf->npages; i++) अणु
		addr = buf->frags->map + (i << buf->page_shअगरt);

		pas[i] = cpu_to_be64(addr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_fill_page_array);

व्योम mlx5_fill_page_frag_array_perm(काष्ठा mlx5_frag_buf *buf, __be64 *pas, u8 perm)
अणु
	पूर्णांक i;

	WARN_ON(perm & 0xfc);
	क्रम (i = 0; i < buf->npages; i++)
		pas[i] = cpu_to_be64(buf->frags[i].map | perm);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_fill_page_frag_array_perm);

व्योम mlx5_fill_page_frag_array(काष्ठा mlx5_frag_buf *buf, __be64 *pas)
अणु
	mlx5_fill_page_frag_array_perm(buf, pas, 0);
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_fill_page_frag_array);
