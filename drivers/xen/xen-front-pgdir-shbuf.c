<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 * Xen frontend/backend page directory based shared buffer
 * helper module.
 *
 * Copyright (C) 2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/balloon.h>
#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/पूर्णांकerface/io/ring.h>

#समावेश <xen/xen-front-pgdir-shbuf.h>

#अगर_अघोषित GRANT_INVALID_REF
/*
 * FIXME: usage of grant reference 0 as invalid grant reference:
 * grant reference 0 is valid, but never exposed to a PV driver,
 * because of the fact it is alपढ़ोy in use/reserved by the PV console.
 */
#घोषणा GRANT_INVALID_REF	0
#पूर्ण_अगर

/**
 * This काष्ठाure represents the काष्ठाure of a shared page
 * that contains grant references to the pages of the shared
 * buffer. This काष्ठाure is common to many Xen para-भवized
 * protocols at include/xen/पूर्णांकerface/io/
 */
काष्ठा xen_page_directory अणु
	grant_ref_t gref_dir_next_page;
	grant_ref_t gref[1]; /* Variable length */
पूर्ण;

/**
 * Shared buffer ops which are dअगरferently implemented
 * depending on the allocation mode, e.g. अगर the buffer
 * is allocated by the corresponding backend or frontend.
 * Some of the operations.
 */
काष्ठा xen_front_pgdir_shbuf_ops अणु
	/*
	 * Calculate number of grefs required to handle this buffer,
	 * e.g. अगर grefs are required क्रम page directory only or the buffer
	 * pages as well.
	 */
	व्योम (*calc_num_grefs)(काष्ठा xen_front_pgdir_shbuf *buf);

	/* Fill page directory according to para-भव display protocol. */
	व्योम (*fill_page_dir)(काष्ठा xen_front_pgdir_shbuf *buf);

	/* Claim grant references क्रम the pages of the buffer. */
	पूर्णांक (*grant_refs_क्रम_buffer)(काष्ठा xen_front_pgdir_shbuf *buf,
				     grant_ref_t *priv_gref_head, पूर्णांक gref_idx);

	/* Map grant references of the buffer. */
	पूर्णांक (*map)(काष्ठा xen_front_pgdir_shbuf *buf);

	/* Unmap grant references of the buffer. */
	पूर्णांक (*unmap)(काष्ठा xen_front_pgdir_shbuf *buf);
पूर्ण;

/**
 * Get granted reference to the very first page of the
 * page directory. Usually this is passed to the backend,
 * so it can find/fill the grant references to the buffer's
 * pages.
 *
 * \param buf shared buffer which page directory is of पूर्णांकerest.
 * \लeturn granted reference to the very first page of the
 * page directory.
 */
grant_ref_t
xen_front_pgdir_shbuf_get_dir_start(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	अगर (!buf->grefs)
		वापस GRANT_INVALID_REF;

	वापस buf->grefs[0];
पूर्ण
EXPORT_SYMBOL_GPL(xen_front_pgdir_shbuf_get_dir_start);

/**
 * Map granted references of the shared buffer.
 *
 * Depending on the shared buffer mode of allocation
 * (be_alloc flag) this can either करो nothing (क्रम buffers
 * shared by the frontend itself) or map the provided granted
 * references onto the backing storage (buf->pages).
 *
 * \param buf shared buffer which grants to be maped.
 * \लeturn zero on success or a negative number on failure.
 */
पूर्णांक xen_front_pgdir_shbuf_map(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	अगर (buf->ops && buf->ops->map)
		वापस buf->ops->map(buf);

	/* No need to map own grant references. */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xen_front_pgdir_shbuf_map);

/**
 * Unmap granted references of the shared buffer.
 *
 * Depending on the shared buffer mode of allocation
 * (be_alloc flag) this can either करो nothing (क्रम buffers
 * shared by the frontend itself) or unmap the provided granted
 * references.
 *
 * \param buf shared buffer which grants to be unmaped.
 * \लeturn zero on success or a negative number on failure.
 */
पूर्णांक xen_front_pgdir_shbuf_unmap(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	अगर (buf->ops && buf->ops->unmap)
		वापस buf->ops->unmap(buf);

	/* No need to unmap own grant references. */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xen_front_pgdir_shbuf_unmap);

/**
 * Free all the resources of the shared buffer.
 *
 * \param buf shared buffer which resources to be मुक्तd.
 */
व्योम xen_front_pgdir_shbuf_मुक्त(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	अगर (buf->grefs) अणु
		पूर्णांक i;

		क्रम (i = 0; i < buf->num_grefs; i++)
			अगर (buf->grefs[i] != GRANT_INVALID_REF)
				gnttab_end_क्रमeign_access(buf->grefs[i],
							  0, 0UL);
	पूर्ण
	kमुक्त(buf->grefs);
	kमुक्त(buf->directory);
पूर्ण
EXPORT_SYMBOL_GPL(xen_front_pgdir_shbuf_मुक्त);

/*
 * Number of grefs a page can hold with respect to the
 * काष्ठा xen_page_directory header.
 */
#घोषणा XEN_NUM_GREFS_PER_PAGE ((PAGE_SIZE - \
				 दुरत्व(काष्ठा xen_page_directory, \
					  gref)) / माप(grant_ref_t))

/**
 * Get the number of pages the page directory consumes itself.
 *
 * \param buf shared buffer.
 */
अटल पूर्णांक get_num_pages_dir(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	वापस DIV_ROUND_UP(buf->num_pages, XEN_NUM_GREFS_PER_PAGE);
पूर्ण

/**
 * Calculate the number of grant references needed to share the buffer
 * and its pages when backend allocates the buffer.
 *
 * \param buf shared buffer.
 */
अटल व्योम backend_calc_num_grefs(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	/* Only क्रम pages the page directory consumes itself. */
	buf->num_grefs = get_num_pages_dir(buf);
पूर्ण

/**
 * Calculate the number of grant references needed to share the buffer
 * and its pages when frontend allocates the buffer.
 *
 * \param buf shared buffer.
 */
अटल व्योम guest_calc_num_grefs(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	/*
	 * Number of pages the page directory consumes itself
	 * plus grefs क्रम the buffer pages.
	 */
	buf->num_grefs = get_num_pages_dir(buf) + buf->num_pages;
पूर्ण

#घोषणा xen_page_to_vaddr(page) \
	((uपूर्णांकptr_t)pfn_to_kaddr(page_to_xen_pfn(page)))

/**
 * Unmap the buffer previously mapped with grant references
 * provided by the backend.
 *
 * \param buf shared buffer.
 * \लeturn zero on success or a negative number on failure.
 */
अटल पूर्णांक backend_unmap(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	काष्ठा gnttab_unmap_grant_ref *unmap_ops;
	पूर्णांक i, ret;

	अगर (!buf->pages || !buf->backend_map_handles || !buf->grefs)
		वापस 0;

	unmap_ops = kसुस्मृति(buf->num_pages, माप(*unmap_ops),
			    GFP_KERNEL);
	अगर (!unmap_ops)
		वापस -ENOMEM;

	क्रम (i = 0; i < buf->num_pages; i++) अणु
		phys_addr_t addr;

		addr = xen_page_to_vaddr(buf->pages[i]);
		gnttab_set_unmap_op(&unmap_ops[i], addr, GNTMAP_host_map,
				    buf->backend_map_handles[i]);
	पूर्ण

	ret = gnttab_unmap_refs(unmap_ops, शून्य, buf->pages,
				buf->num_pages);

	क्रम (i = 0; i < buf->num_pages; i++) अणु
		अगर (unlikely(unmap_ops[i].status != GNTST_okay))
			dev_err(&buf->xb_dev->dev,
				"Failed to unmap page %d: %d\n",
				i, unmap_ops[i].status);
	पूर्ण

	अगर (ret)
		dev_err(&buf->xb_dev->dev,
			"Failed to unmap grant references, ret %d", ret);

	kमुक्त(unmap_ops);
	kमुक्त(buf->backend_map_handles);
	buf->backend_map_handles = शून्य;
	वापस ret;
पूर्ण

/**
 * Map the buffer with grant references provided by the backend.
 *
 * \param buf shared buffer.
 * \लeturn zero on success or a negative number on failure.
 */
अटल पूर्णांक backend_map(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	काष्ठा gnttab_map_grant_ref *map_ops = शून्य;
	अचिन्हित अक्षर *ptr;
	पूर्णांक ret, cur_gref, cur_dir_page, cur_page, grefs_left;

	map_ops = kसुस्मृति(buf->num_pages, माप(*map_ops), GFP_KERNEL);
	अगर (!map_ops)
		वापस -ENOMEM;

	buf->backend_map_handles = kसुस्मृति(buf->num_pages,
					   माप(*buf->backend_map_handles),
					   GFP_KERNEL);
	अगर (!buf->backend_map_handles) अणु
		kमुक्त(map_ops);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Read page directory to get grefs from the backend: क्रम बाह्यal
	 * buffer we only allocate buf->grefs क्रम the page directory,
	 * so buf->num_grefs has number of pages in the page directory itself.
	 */
	ptr = buf->directory;
	grefs_left = buf->num_pages;
	cur_page = 0;
	क्रम (cur_dir_page = 0; cur_dir_page < buf->num_grefs; cur_dir_page++) अणु
		काष्ठा xen_page_directory *page_dir =
			(काष्ठा xen_page_directory *)ptr;
		पूर्णांक to_copy = XEN_NUM_GREFS_PER_PAGE;

		अगर (to_copy > grefs_left)
			to_copy = grefs_left;

		क्रम (cur_gref = 0; cur_gref < to_copy; cur_gref++) अणु
			phys_addr_t addr;

			addr = xen_page_to_vaddr(buf->pages[cur_page]);
			gnttab_set_map_op(&map_ops[cur_page], addr,
					  GNTMAP_host_map,
					  page_dir->gref[cur_gref],
					  buf->xb_dev->otherend_id);
			cur_page++;
		पूर्ण

		grefs_left -= to_copy;
		ptr += PAGE_SIZE;
	पूर्ण
	ret = gnttab_map_refs(map_ops, शून्य, buf->pages, buf->num_pages);

	/* Save handles even अगर error, so we can unmap. */
	क्रम (cur_page = 0; cur_page < buf->num_pages; cur_page++) अणु
		अगर (likely(map_ops[cur_page].status == GNTST_okay)) अणु
			buf->backend_map_handles[cur_page] =
				map_ops[cur_page].handle;
		पूर्ण अन्यथा अणु
			buf->backend_map_handles[cur_page] =
				INVALID_GRANT_HANDLE;
			अगर (!ret)
				ret = -ENXIO;
			dev_err(&buf->xb_dev->dev,
				"Failed to map page %d: %d\n",
				cur_page, map_ops[cur_page].status);
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		dev_err(&buf->xb_dev->dev,
			"Failed to map grant references, ret %d", ret);
		backend_unmap(buf);
	पूर्ण

	kमुक्त(map_ops);
	वापस ret;
पूर्ण

/**
 * Fill page directory with grant references to the pages of the
 * page directory itself.
 *
 * The grant references to the buffer pages are provided by the
 * backend in this हाल.
 *
 * \param buf shared buffer.
 */
अटल व्योम backend_fill_page_dir(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	काष्ठा xen_page_directory *page_dir;
	अचिन्हित अक्षर *ptr;
	पूर्णांक i, num_pages_dir;

	ptr = buf->directory;
	num_pages_dir = get_num_pages_dir(buf);

	/* Fill only grefs क्रम the page directory itself. */
	क्रम (i = 0; i < num_pages_dir - 1; i++) अणु
		page_dir = (काष्ठा xen_page_directory *)ptr;

		page_dir->gref_dir_next_page = buf->grefs[i + 1];
		ptr += PAGE_SIZE;
	पूर्ण
	/* Last page must say there is no more pages. */
	page_dir = (काष्ठा xen_page_directory *)ptr;
	page_dir->gref_dir_next_page = GRANT_INVALID_REF;
पूर्ण

/**
 * Fill page directory with grant references to the pages of the
 * page directory and the buffer we share with the backend.
 *
 * \param buf shared buffer.
 */
अटल व्योम guest_fill_page_dir(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	अचिन्हित अक्षर *ptr;
	पूर्णांक cur_gref, grefs_left, to_copy, i, num_pages_dir;

	ptr = buf->directory;
	num_pages_dir = get_num_pages_dir(buf);

	/*
	 * While copying, skip grefs at start, they are क्रम pages
	 * granted क्रम the page directory itself.
	 */
	cur_gref = num_pages_dir;
	grefs_left = buf->num_pages;
	क्रम (i = 0; i < num_pages_dir; i++) अणु
		काष्ठा xen_page_directory *page_dir =
			(काष्ठा xen_page_directory *)ptr;

		अगर (grefs_left <= XEN_NUM_GREFS_PER_PAGE) अणु
			to_copy = grefs_left;
			page_dir->gref_dir_next_page = GRANT_INVALID_REF;
		पूर्ण अन्यथा अणु
			to_copy = XEN_NUM_GREFS_PER_PAGE;
			page_dir->gref_dir_next_page = buf->grefs[i + 1];
		पूर्ण
		स_नकल(&page_dir->gref, &buf->grefs[cur_gref],
		       to_copy * माप(grant_ref_t));
		ptr += PAGE_SIZE;
		grefs_left -= to_copy;
		cur_gref += to_copy;
	पूर्ण
पूर्ण

/**
 * Grant references to the frontend's buffer pages.
 *
 * These will be shared with the backend, so it can
 * access the buffer's data.
 *
 * \param buf shared buffer.
 * \लeturn zero on success or a negative number on failure.
 */
अटल पूर्णांक guest_grant_refs_क्रम_buffer(काष्ठा xen_front_pgdir_shbuf *buf,
				       grant_ref_t *priv_gref_head,
				       पूर्णांक gref_idx)
अणु
	पूर्णांक i, cur_ref, otherend_id;

	otherend_id = buf->xb_dev->otherend_id;
	क्रम (i = 0; i < buf->num_pages; i++) अणु
		cur_ref = gnttab_claim_grant_reference(priv_gref_head);
		अगर (cur_ref < 0)
			वापस cur_ref;

		gnttab_grant_क्रमeign_access_ref(cur_ref, otherend_id,
						xen_page_to_gfn(buf->pages[i]),
						0);
		buf->grefs[gref_idx++] = cur_ref;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Grant all the references needed to share the buffer.
 *
 * Grant references to the page directory pages and, अगर
 * needed, also to the pages of the shared buffer data.
 *
 * \param buf shared buffer.
 * \लeturn zero on success or a negative number on failure.
 */
अटल पूर्णांक grant_references(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	grant_ref_t priv_gref_head;
	पूर्णांक ret, i, j, cur_ref;
	पूर्णांक otherend_id, num_pages_dir;

	ret = gnttab_alloc_grant_references(buf->num_grefs, &priv_gref_head);
	अगर (ret < 0) अणु
		dev_err(&buf->xb_dev->dev,
			"Cannot allocate grant references\n");
		वापस ret;
	पूर्ण

	otherend_id = buf->xb_dev->otherend_id;
	j = 0;
	num_pages_dir = get_num_pages_dir(buf);
	क्रम (i = 0; i < num_pages_dir; i++) अणु
		अचिन्हित दीर्घ frame;

		cur_ref = gnttab_claim_grant_reference(&priv_gref_head);
		अगर (cur_ref < 0)
			वापस cur_ref;

		frame = xen_page_to_gfn(virt_to_page(buf->directory +
						     PAGE_SIZE * i));
		gnttab_grant_क्रमeign_access_ref(cur_ref, otherend_id, frame, 0);
		buf->grefs[j++] = cur_ref;
	पूर्ण

	अगर (buf->ops->grant_refs_क्रम_buffer) अणु
		ret = buf->ops->grant_refs_क्रम_buffer(buf, &priv_gref_head, j);
		अगर (ret)
			वापस ret;
	पूर्ण

	gnttab_मुक्त_grant_references(priv_gref_head);
	वापस 0;
पूर्ण

/**
 * Allocate all required काष्ठाures to mange shared buffer.
 *
 * \param buf shared buffer.
 * \लeturn zero on success or a negative number on failure.
 */
अटल पूर्णांक alloc_storage(काष्ठा xen_front_pgdir_shbuf *buf)
अणु
	buf->grefs = kसुस्मृति(buf->num_grefs, माप(*buf->grefs), GFP_KERNEL);
	अगर (!buf->grefs)
		वापस -ENOMEM;

	buf->directory = kसुस्मृति(get_num_pages_dir(buf), PAGE_SIZE, GFP_KERNEL);
	अगर (!buf->directory)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/*
 * For backend allocated buffers we करोn't need grant_refs_क्रम_buffer
 * as those grant references are allocated at backend side.
 */
अटल स्थिर काष्ठा xen_front_pgdir_shbuf_ops backend_ops = अणु
	.calc_num_grefs = backend_calc_num_grefs,
	.fill_page_dir = backend_fill_page_dir,
	.map = backend_map,
	.unmap = backend_unmap
पूर्ण;

/*
 * For locally granted references we करो not need to map/unmap
 * the references.
 */
अटल स्थिर काष्ठा xen_front_pgdir_shbuf_ops local_ops = अणु
	.calc_num_grefs = guest_calc_num_grefs,
	.fill_page_dir = guest_fill_page_dir,
	.grant_refs_क्रम_buffer = guest_grant_refs_क्रम_buffer,
पूर्ण;

/**
 * Allocate a new instance of a shared buffer.
 *
 * \param cfg configuration to be used जबतक allocating a new shared buffer.
 * \लeturn zero on success or a negative number on failure.
 */
पूर्णांक xen_front_pgdir_shbuf_alloc(काष्ठा xen_front_pgdir_shbuf_cfg *cfg)
अणु
	काष्ठा xen_front_pgdir_shbuf *buf = cfg->pgdir;
	पूर्णांक ret;

	अगर (cfg->be_alloc)
		buf->ops = &backend_ops;
	अन्यथा
		buf->ops = &local_ops;
	buf->xb_dev = cfg->xb_dev;
	buf->num_pages = cfg->num_pages;
	buf->pages = cfg->pages;

	buf->ops->calc_num_grefs(buf);

	ret = alloc_storage(buf);
	अगर (ret)
		जाओ fail;

	ret = grant_references(buf);
	अगर (ret)
		जाओ fail;

	buf->ops->fill_page_dir(buf);

	वापस 0;

fail:
	xen_front_pgdir_shbuf_मुक्त(buf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xen_front_pgdir_shbuf_alloc);

MODULE_DESCRIPTION("Xen frontend/backend page directory based "
		   "shared buffer handling");
MODULE_AUTHOR("Oleksandr Andrushchenko");
MODULE_LICENSE("GPL");
