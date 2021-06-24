<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Xen dma-buf functionality क्रम gntdev.
 *
 * DMA buffer implementation is based on drivers/gpu/drm/drm_prime.c.
 *
 * Copyright (c) 2018 Oleksandr Andrushchenko, EPAM Systems Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/dma-buf.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#समावेश <xen/xen.h>
#समावेश <xen/grant_table.h>

#समावेश "gntdev-common.h"
#समावेश "gntdev-dmabuf.h"

#अगर_अघोषित GRANT_INVALID_REF
/*
 * Note on usage of grant reference 0 as invalid grant reference:
 * grant reference 0 is valid, but never exposed to a driver,
 * because of the fact it is alपढ़ोy in use/reserved by the PV console.
 */
#घोषणा GRANT_INVALID_REF	0
#पूर्ण_अगर

काष्ठा gntdev_dmabuf अणु
	काष्ठा gntdev_dmabuf_priv *priv;
	काष्ठा dma_buf *dmabuf;
	काष्ठा list_head next;
	पूर्णांक fd;

	जोड़ अणु
		काष्ठा अणु
			/* Exported buffers are reference counted. */
			काष्ठा kref refcount;

			काष्ठा gntdev_priv *priv;
			काष्ठा gntdev_grant_map *map;
		पूर्ण exp;
		काष्ठा अणु
			/* Granted references of the imported buffer. */
			grant_ref_t *refs;
			/* Scatter-gather table of the imported buffer. */
			काष्ठा sg_table *sgt;
			/* dma-buf attachment of the imported buffer. */
			काष्ठा dma_buf_attachment *attach;
		पूर्ण imp;
	पूर्ण u;

	/* Number of pages this buffer has. */
	पूर्णांक nr_pages;
	/* Pages of this buffer. */
	काष्ठा page **pages;
पूर्ण;

काष्ठा gntdev_dmabuf_रुको_obj अणु
	काष्ठा list_head next;
	काष्ठा gntdev_dmabuf *gntdev_dmabuf;
	काष्ठा completion completion;
पूर्ण;

काष्ठा gntdev_dmabuf_attachment अणु
	काष्ठा sg_table *sgt;
	क्रमागत dma_data_direction dir;
पूर्ण;

काष्ठा gntdev_dmabuf_priv अणु
	/* List of exported DMA buffers. */
	काष्ठा list_head exp_list;
	/* List of रुको objects. */
	काष्ठा list_head exp_रुको_list;
	/* List of imported DMA buffers. */
	काष्ठा list_head imp_list;
	/* This is the lock which protects dma_buf_xxx lists. */
	काष्ठा mutex lock;
	/*
	 * We reference this file जबतक exporting dma-bufs, so
	 * the grant device context is not destroyed जबतक there are
	 * बाह्यal users alive.
	 */
	काष्ठा file *filp;
पूर्ण;

/* DMA buffer export support. */

/* Implementation of रुको क्रम exported DMA buffer to be released. */

अटल व्योम dmabuf_exp_release(काष्ठा kref *kref);

अटल काष्ठा gntdev_dmabuf_रुको_obj *
dmabuf_exp_रुको_obj_new(काष्ठा gntdev_dmabuf_priv *priv,
			काष्ठा gntdev_dmabuf *gntdev_dmabuf)
अणु
	काष्ठा gntdev_dmabuf_रुको_obj *obj;

	obj = kzalloc(माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस ERR_PTR(-ENOMEM);

	init_completion(&obj->completion);
	obj->gntdev_dmabuf = gntdev_dmabuf;

	mutex_lock(&priv->lock);
	list_add(&obj->next, &priv->exp_रुको_list);
	/* Put our reference and रुको क्रम gntdev_dmabuf's release to fire. */
	kref_put(&gntdev_dmabuf->u.exp.refcount, dmabuf_exp_release);
	mutex_unlock(&priv->lock);
	वापस obj;
पूर्ण

अटल व्योम dmabuf_exp_रुको_obj_मुक्त(काष्ठा gntdev_dmabuf_priv *priv,
				     काष्ठा gntdev_dmabuf_रुको_obj *obj)
अणु
	mutex_lock(&priv->lock);
	list_del(&obj->next);
	mutex_unlock(&priv->lock);
	kमुक्त(obj);
पूर्ण

अटल पूर्णांक dmabuf_exp_रुको_obj_रुको(काष्ठा gntdev_dmabuf_रुको_obj *obj,
				    u32 रुको_to_ms)
अणु
	अगर (रुको_क्रम_completion_समयout(&obj->completion,
			msecs_to_jअगरfies(रुको_to_ms)) <= 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम dmabuf_exp_रुको_obj_संकेत(काष्ठा gntdev_dmabuf_priv *priv,
				       काष्ठा gntdev_dmabuf *gntdev_dmabuf)
अणु
	काष्ठा gntdev_dmabuf_रुको_obj *obj;

	list_क्रम_each_entry(obj, &priv->exp_रुको_list, next)
		अगर (obj->gntdev_dmabuf == gntdev_dmabuf) अणु
			pr_debug("Found gntdev_dmabuf in the wait list, wake\n");
			complete_all(&obj->completion);
			अवरोध;
		पूर्ण
पूर्ण

अटल काष्ठा gntdev_dmabuf *
dmabuf_exp_रुको_obj_get_dmabuf(काष्ठा gntdev_dmabuf_priv *priv, पूर्णांक fd)
अणु
	काष्ठा gntdev_dmabuf *gntdev_dmabuf, *ret = ERR_PTR(-ENOENT);

	mutex_lock(&priv->lock);
	list_क्रम_each_entry(gntdev_dmabuf, &priv->exp_list, next)
		अगर (gntdev_dmabuf->fd == fd) अणु
			pr_debug("Found gntdev_dmabuf in the wait list\n");
			kref_get(&gntdev_dmabuf->u.exp.refcount);
			ret = gntdev_dmabuf;
			अवरोध;
		पूर्ण
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dmabuf_exp_रुको_released(काष्ठा gntdev_dmabuf_priv *priv, पूर्णांक fd,
				    पूर्णांक रुको_to_ms)
अणु
	काष्ठा gntdev_dmabuf *gntdev_dmabuf;
	काष्ठा gntdev_dmabuf_रुको_obj *obj;
	पूर्णांक ret;

	pr_debug("Will wait for dma-buf with fd %d\n", fd);
	/*
	 * Try to find the DMA buffer: अगर not found means that
	 * either the buffer has alपढ़ोy been released or file descriptor
	 * provided is wrong.
	 */
	gntdev_dmabuf = dmabuf_exp_रुको_obj_get_dmabuf(priv, fd);
	अगर (IS_ERR(gntdev_dmabuf))
		वापस PTR_ERR(gntdev_dmabuf);

	/*
	 * gntdev_dmabuf still exists and is reference count locked by us now,
	 * so prepare to रुको: allocate रुको object and add it to the रुको list,
	 * so we can find it on release.
	 */
	obj = dmabuf_exp_रुको_obj_new(priv, gntdev_dmabuf);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	ret = dmabuf_exp_रुको_obj_रुको(obj, रुको_to_ms);
	dmabuf_exp_रुको_obj_मुक्त(priv, obj);
	वापस ret;
पूर्ण

/* DMA buffer export support. */

अटल काष्ठा sg_table *
dmabuf_pages_to_sgt(काष्ठा page **pages, अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा sg_table *sgt;
	पूर्णांक ret;

	sgt = kदो_स्मृति(माप(*sgt), GFP_KERNEL);
	अगर (!sgt) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = sg_alloc_table_from_pages(sgt, pages, nr_pages, 0,
					nr_pages << PAGE_SHIFT,
					GFP_KERNEL);
	अगर (ret)
		जाओ out;

	वापस sgt;

out:
	kमुक्त(sgt);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक dmabuf_exp_ops_attach(काष्ठा dma_buf *dma_buf,
				 काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा gntdev_dmabuf_attachment *gntdev_dmabuf_attach;

	gntdev_dmabuf_attach = kzalloc(माप(*gntdev_dmabuf_attach),
				       GFP_KERNEL);
	अगर (!gntdev_dmabuf_attach)
		वापस -ENOMEM;

	gntdev_dmabuf_attach->dir = DMA_NONE;
	attach->priv = gntdev_dmabuf_attach;
	वापस 0;
पूर्ण

अटल व्योम dmabuf_exp_ops_detach(काष्ठा dma_buf *dma_buf,
				  काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा gntdev_dmabuf_attachment *gntdev_dmabuf_attach = attach->priv;

	अगर (gntdev_dmabuf_attach) अणु
		काष्ठा sg_table *sgt = gntdev_dmabuf_attach->sgt;

		अगर (sgt) अणु
			अगर (gntdev_dmabuf_attach->dir != DMA_NONE)
				dma_unmap_sgtable(attach->dev, sgt,
						  gntdev_dmabuf_attach->dir,
						  DMA_ATTR_SKIP_CPU_SYNC);
			sg_मुक्त_table(sgt);
		पूर्ण

		kमुक्त(sgt);
		kमुक्त(gntdev_dmabuf_attach);
		attach->priv = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा sg_table *
dmabuf_exp_ops_map_dma_buf(काष्ठा dma_buf_attachment *attach,
			   क्रमागत dma_data_direction dir)
अणु
	काष्ठा gntdev_dmabuf_attachment *gntdev_dmabuf_attach = attach->priv;
	काष्ठा gntdev_dmabuf *gntdev_dmabuf = attach->dmabuf->priv;
	काष्ठा sg_table *sgt;

	pr_debug("Mapping %d pages for dev %p\n", gntdev_dmabuf->nr_pages,
		 attach->dev);

	अगर (dir == DMA_NONE || !gntdev_dmabuf_attach)
		वापस ERR_PTR(-EINVAL);

	/* Return the cached mapping when possible. */
	अगर (gntdev_dmabuf_attach->dir == dir)
		वापस gntdev_dmabuf_attach->sgt;

	/*
	 * Two mappings with dअगरferent directions क्रम the same attachment are
	 * not allowed.
	 */
	अगर (gntdev_dmabuf_attach->dir != DMA_NONE)
		वापस ERR_PTR(-EBUSY);

	sgt = dmabuf_pages_to_sgt(gntdev_dmabuf->pages,
				  gntdev_dmabuf->nr_pages);
	अगर (!IS_ERR(sgt)) अणु
		अगर (dma_map_sgtable(attach->dev, sgt, dir,
				    DMA_ATTR_SKIP_CPU_SYNC)) अणु
			sg_मुक्त_table(sgt);
			kमुक्त(sgt);
			sgt = ERR_PTR(-ENOMEM);
		पूर्ण अन्यथा अणु
			gntdev_dmabuf_attach->sgt = sgt;
			gntdev_dmabuf_attach->dir = dir;
		पूर्ण
	पूर्ण
	अगर (IS_ERR(sgt))
		pr_debug("Failed to map sg table for dev %p\n", attach->dev);
	वापस sgt;
पूर्ण

अटल व्योम dmabuf_exp_ops_unmap_dma_buf(काष्ठा dma_buf_attachment *attach,
					 काष्ठा sg_table *sgt,
					 क्रमागत dma_data_direction dir)
अणु
	/* Not implemented. The unmap is करोne at dmabuf_exp_ops_detach(). */
पूर्ण

अटल व्योम dmabuf_exp_release(काष्ठा kref *kref)
अणु
	काष्ठा gntdev_dmabuf *gntdev_dmabuf =
		container_of(kref, काष्ठा gntdev_dmabuf, u.exp.refcount);

	dmabuf_exp_रुको_obj_संकेत(gntdev_dmabuf->priv, gntdev_dmabuf);
	list_del(&gntdev_dmabuf->next);
	fput(gntdev_dmabuf->priv->filp);
	kमुक्त(gntdev_dmabuf);
पूर्ण

अटल व्योम dmabuf_exp_हटाओ_map(काष्ठा gntdev_priv *priv,
				  काष्ठा gntdev_grant_map *map)
अणु
	mutex_lock(&priv->lock);
	list_del(&map->next);
	gntdev_put_map(शून्य /* alपढ़ोy हटाओd */, map);
	mutex_unlock(&priv->lock);
पूर्ण

अटल व्योम dmabuf_exp_ops_release(काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा gntdev_dmabuf *gntdev_dmabuf = dma_buf->priv;
	काष्ठा gntdev_dmabuf_priv *priv = gntdev_dmabuf->priv;

	dmabuf_exp_हटाओ_map(gntdev_dmabuf->u.exp.priv,
			      gntdev_dmabuf->u.exp.map);
	mutex_lock(&priv->lock);
	kref_put(&gntdev_dmabuf->u.exp.refcount, dmabuf_exp_release);
	mutex_unlock(&priv->lock);
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops dmabuf_exp_ops =  अणु
	.attach = dmabuf_exp_ops_attach,
	.detach = dmabuf_exp_ops_detach,
	.map_dma_buf = dmabuf_exp_ops_map_dma_buf,
	.unmap_dma_buf = dmabuf_exp_ops_unmap_dma_buf,
	.release = dmabuf_exp_ops_release,
पूर्ण;

काष्ठा gntdev_dmabuf_export_args अणु
	काष्ठा gntdev_priv *priv;
	काष्ठा gntdev_grant_map *map;
	काष्ठा gntdev_dmabuf_priv *dmabuf_priv;
	काष्ठा device *dev;
	पूर्णांक count;
	काष्ठा page **pages;
	u32 fd;
पूर्ण;

अटल पूर्णांक dmabuf_exp_from_pages(काष्ठा gntdev_dmabuf_export_args *args)
अणु
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	काष्ठा gntdev_dmabuf *gntdev_dmabuf;
	पूर्णांक ret;

	gntdev_dmabuf = kzalloc(माप(*gntdev_dmabuf), GFP_KERNEL);
	अगर (!gntdev_dmabuf)
		वापस -ENOMEM;

	kref_init(&gntdev_dmabuf->u.exp.refcount);

	gntdev_dmabuf->priv = args->dmabuf_priv;
	gntdev_dmabuf->nr_pages = args->count;
	gntdev_dmabuf->pages = args->pages;
	gntdev_dmabuf->u.exp.priv = args->priv;
	gntdev_dmabuf->u.exp.map = args->map;

	exp_info.exp_name = KBUILD_MODNAME;
	अगर (args->dev->driver && args->dev->driver->owner)
		exp_info.owner = args->dev->driver->owner;
	अन्यथा
		exp_info.owner = THIS_MODULE;
	exp_info.ops = &dmabuf_exp_ops;
	exp_info.size = args->count << PAGE_SHIFT;
	exp_info.flags = O_RDWR;
	exp_info.priv = gntdev_dmabuf;

	gntdev_dmabuf->dmabuf = dma_buf_export(&exp_info);
	अगर (IS_ERR(gntdev_dmabuf->dmabuf)) अणु
		ret = PTR_ERR(gntdev_dmabuf->dmabuf);
		gntdev_dmabuf->dmabuf = शून्य;
		जाओ fail;
	पूर्ण

	ret = dma_buf_fd(gntdev_dmabuf->dmabuf, O_CLOEXEC);
	अगर (ret < 0)
		जाओ fail;

	gntdev_dmabuf->fd = ret;
	args->fd = ret;

	pr_debug("Exporting DMA buffer with fd %d\n", ret);

	mutex_lock(&args->dmabuf_priv->lock);
	list_add(&gntdev_dmabuf->next, &args->dmabuf_priv->exp_list);
	mutex_unlock(&args->dmabuf_priv->lock);
	get_file(gntdev_dmabuf->priv->filp);
	वापस 0;

fail:
	अगर (gntdev_dmabuf->dmabuf)
		dma_buf_put(gntdev_dmabuf->dmabuf);
	kमुक्त(gntdev_dmabuf);
	वापस ret;
पूर्ण

अटल काष्ठा gntdev_grant_map *
dmabuf_exp_alloc_backing_storage(काष्ठा gntdev_priv *priv, पूर्णांक dmabuf_flags,
				 पूर्णांक count)
अणु
	काष्ठा gntdev_grant_map *map;

	अगर (unlikely(gntdev_test_page_count(count)))
		वापस ERR_PTR(-EINVAL);

	अगर ((dmabuf_flags & GNTDEV_DMA_FLAG_WC) &&
	    (dmabuf_flags & GNTDEV_DMA_FLAG_COHERENT)) अणु
		pr_debug("Wrong dma-buf flags: 0x%x\n", dmabuf_flags);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	map = gntdev_alloc_map(priv, count, dmabuf_flags);
	अगर (!map)
		वापस ERR_PTR(-ENOMEM);

	वापस map;
पूर्ण

अटल पूर्णांक dmabuf_exp_from_refs(काष्ठा gntdev_priv *priv, पूर्णांक flags,
				पूर्णांक count, u32 करोmid, u32 *refs, u32 *fd)
अणु
	काष्ठा gntdev_grant_map *map;
	काष्ठा gntdev_dmabuf_export_args args;
	पूर्णांक i, ret;

	map = dmabuf_exp_alloc_backing_storage(priv, flags, count);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	क्रम (i = 0; i < count; i++) अणु
		map->grants[i].करोmid = करोmid;
		map->grants[i].ref = refs[i];
	पूर्ण

	mutex_lock(&priv->lock);
	gntdev_add_map(priv, map);
	mutex_unlock(&priv->lock);

	map->flags |= GNTMAP_host_map;
#अगर defined(CONFIG_X86)
	map->flags |= GNTMAP_device_map;
#पूर्ण_अगर

	ret = gntdev_map_grant_pages(map);
	अगर (ret < 0)
		जाओ out;

	args.priv = priv;
	args.map = map;
	args.dev = priv->dma_dev;
	args.dmabuf_priv = priv->dmabuf_priv;
	args.count = map->count;
	args.pages = map->pages;
	args.fd = -1; /* Shut up unnecessary gcc warning क्रम i386 */

	ret = dmabuf_exp_from_pages(&args);
	अगर (ret < 0)
		जाओ out;

	*fd = args.fd;
	वापस 0;

out:
	dmabuf_exp_हटाओ_map(priv, map);
	वापस ret;
पूर्ण

/* DMA buffer import support. */

अटल पूर्णांक
dmabuf_imp_grant_क्रमeign_access(काष्ठा page **pages, u32 *refs,
				पूर्णांक count, पूर्णांक करोmid)
अणु
	grant_ref_t priv_gref_head;
	पूर्णांक i, ret;

	ret = gnttab_alloc_grant_references(count, &priv_gref_head);
	अगर (ret < 0) अणु
		pr_debug("Cannot allocate grant references, ret %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक cur_ref;

		cur_ref = gnttab_claim_grant_reference(&priv_gref_head);
		अगर (cur_ref < 0) अणु
			ret = cur_ref;
			pr_debug("Cannot claim grant reference, ret %d\n", ret);
			जाओ out;
		पूर्ण

		gnttab_grant_क्रमeign_access_ref(cur_ref, करोmid,
						xen_page_to_gfn(pages[i]), 0);
		refs[i] = cur_ref;
	पूर्ण

	वापस 0;

out:
	gnttab_मुक्त_grant_references(priv_gref_head);
	वापस ret;
पूर्ण

अटल व्योम dmabuf_imp_end_क्रमeign_access(u32 *refs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		अगर (refs[i] != GRANT_INVALID_REF)
			gnttab_end_क्रमeign_access(refs[i], 0, 0UL);
पूर्ण

अटल व्योम dmabuf_imp_मुक्त_storage(काष्ठा gntdev_dmabuf *gntdev_dmabuf)
अणु
	kमुक्त(gntdev_dmabuf->pages);
	kमुक्त(gntdev_dmabuf->u.imp.refs);
	kमुक्त(gntdev_dmabuf);
पूर्ण

अटल काष्ठा gntdev_dmabuf *dmabuf_imp_alloc_storage(पूर्णांक count)
अणु
	काष्ठा gntdev_dmabuf *gntdev_dmabuf;
	पूर्णांक i;

	gntdev_dmabuf = kzalloc(माप(*gntdev_dmabuf), GFP_KERNEL);
	अगर (!gntdev_dmabuf)
		जाओ fail_no_मुक्त;

	gntdev_dmabuf->u.imp.refs = kसुस्मृति(count,
					    माप(gntdev_dmabuf->u.imp.refs[0]),
					    GFP_KERNEL);
	अगर (!gntdev_dmabuf->u.imp.refs)
		जाओ fail;

	gntdev_dmabuf->pages = kसुस्मृति(count,
				       माप(gntdev_dmabuf->pages[0]),
				       GFP_KERNEL);
	अगर (!gntdev_dmabuf->pages)
		जाओ fail;

	gntdev_dmabuf->nr_pages = count;

	क्रम (i = 0; i < count; i++)
		gntdev_dmabuf->u.imp.refs[i] = GRANT_INVALID_REF;

	वापस gntdev_dmabuf;

fail:
	dmabuf_imp_मुक्त_storage(gntdev_dmabuf);
fail_no_मुक्त:
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल काष्ठा gntdev_dmabuf *
dmabuf_imp_to_refs(काष्ठा gntdev_dmabuf_priv *priv, काष्ठा device *dev,
		   पूर्णांक fd, पूर्णांक count, पूर्णांक करोmid)
अणु
	काष्ठा gntdev_dmabuf *gntdev_dmabuf, *ret;
	काष्ठा dma_buf *dma_buf;
	काष्ठा dma_buf_attachment *attach;
	काष्ठा sg_table *sgt;
	काष्ठा sg_page_iter sg_iter;
	पूर्णांक i;

	dma_buf = dma_buf_get(fd);
	अगर (IS_ERR(dma_buf))
		वापस ERR_CAST(dma_buf);

	gntdev_dmabuf = dmabuf_imp_alloc_storage(count);
	अगर (IS_ERR(gntdev_dmabuf)) अणु
		ret = gntdev_dmabuf;
		जाओ fail_put;
	पूर्ण

	gntdev_dmabuf->priv = priv;
	gntdev_dmabuf->fd = fd;

	attach = dma_buf_attach(dma_buf, dev);
	अगर (IS_ERR(attach)) अणु
		ret = ERR_CAST(attach);
		जाओ fail_मुक्त_obj;
	पूर्ण

	gntdev_dmabuf->u.imp.attach = attach;

	sgt = dma_buf_map_attachment(attach, DMA_BIसूचीECTIONAL);
	अगर (IS_ERR(sgt)) अणु
		ret = ERR_CAST(sgt);
		जाओ fail_detach;
	पूर्ण

	/* Check that we have zero offset. */
	अगर (sgt->sgl->offset) अणु
		ret = ERR_PTR(-EINVAL);
		pr_debug("DMA buffer has %d bytes offset, user-space expects 0\n",
			 sgt->sgl->offset);
		जाओ fail_unmap;
	पूर्ण

	/* Check number of pages that imported buffer has. */
	अगर (attach->dmabuf->size != gntdev_dmabuf->nr_pages << PAGE_SHIFT) अणु
		ret = ERR_PTR(-EINVAL);
		pr_debug("DMA buffer has %zu pages, user-space expects %d\n",
			 attach->dmabuf->size, gntdev_dmabuf->nr_pages);
		जाओ fail_unmap;
	पूर्ण

	gntdev_dmabuf->u.imp.sgt = sgt;

	/* Now convert sgt to array of pages and check क्रम page validity. */
	i = 0;
	क्रम_each_sgtable_page(sgt, &sg_iter, 0) अणु
		काष्ठा page *page = sg_page_iter_page(&sg_iter);
		/*
		 * Check अगर page is valid: this can happen अगर we are given
		 * a page from VRAM or other resources which are not backed
		 * by a काष्ठा page.
		 */
		अगर (!pfn_valid(page_to_pfn(page))) अणु
			ret = ERR_PTR(-EINVAL);
			जाओ fail_unmap;
		पूर्ण

		gntdev_dmabuf->pages[i++] = page;
	पूर्ण

	ret = ERR_PTR(dmabuf_imp_grant_क्रमeign_access(gntdev_dmabuf->pages,
						      gntdev_dmabuf->u.imp.refs,
						      count, करोmid));
	अगर (IS_ERR(ret))
		जाओ fail_end_access;

	pr_debug("Imported DMA buffer with fd %d\n", fd);

	mutex_lock(&priv->lock);
	list_add(&gntdev_dmabuf->next, &priv->imp_list);
	mutex_unlock(&priv->lock);

	वापस gntdev_dmabuf;

fail_end_access:
	dmabuf_imp_end_क्रमeign_access(gntdev_dmabuf->u.imp.refs, count);
fail_unmap:
	dma_buf_unmap_attachment(attach, sgt, DMA_BIसूचीECTIONAL);
fail_detach:
	dma_buf_detach(dma_buf, attach);
fail_मुक्त_obj:
	dmabuf_imp_मुक्त_storage(gntdev_dmabuf);
fail_put:
	dma_buf_put(dma_buf);
	वापस ret;
पूर्ण

/*
 * Find the hyper dma-buf by its file descriptor and हटाओ
 * it from the buffer's list.
 */
अटल काष्ठा gntdev_dmabuf *
dmabuf_imp_find_unlink(काष्ठा gntdev_dmabuf_priv *priv, पूर्णांक fd)
अणु
	काष्ठा gntdev_dmabuf *q, *gntdev_dmabuf, *ret = ERR_PTR(-ENOENT);

	mutex_lock(&priv->lock);
	list_क्रम_each_entry_safe(gntdev_dmabuf, q, &priv->imp_list, next) अणु
		अगर (gntdev_dmabuf->fd == fd) अणु
			pr_debug("Found gntdev_dmabuf in the import list\n");
			ret = gntdev_dmabuf;
			list_del(&gntdev_dmabuf->next);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dmabuf_imp_release(काष्ठा gntdev_dmabuf_priv *priv, u32 fd)
अणु
	काष्ठा gntdev_dmabuf *gntdev_dmabuf;
	काष्ठा dma_buf_attachment *attach;
	काष्ठा dma_buf *dma_buf;

	gntdev_dmabuf = dmabuf_imp_find_unlink(priv, fd);
	अगर (IS_ERR(gntdev_dmabuf))
		वापस PTR_ERR(gntdev_dmabuf);

	pr_debug("Releasing DMA buffer with fd %d\n", fd);

	dmabuf_imp_end_क्रमeign_access(gntdev_dmabuf->u.imp.refs,
				      gntdev_dmabuf->nr_pages);

	attach = gntdev_dmabuf->u.imp.attach;

	अगर (gntdev_dmabuf->u.imp.sgt)
		dma_buf_unmap_attachment(attach, gntdev_dmabuf->u.imp.sgt,
					 DMA_BIसूचीECTIONAL);
	dma_buf = attach->dmabuf;
	dma_buf_detach(attach->dmabuf, attach);
	dma_buf_put(dma_buf);

	dmabuf_imp_मुक्त_storage(gntdev_dmabuf);
	वापस 0;
पूर्ण

अटल व्योम dmabuf_imp_release_all(काष्ठा gntdev_dmabuf_priv *priv)
अणु
	काष्ठा gntdev_dmabuf *q, *gntdev_dmabuf;

	list_क्रम_each_entry_safe(gntdev_dmabuf, q, &priv->imp_list, next)
		dmabuf_imp_release(priv, gntdev_dmabuf->fd);
पूर्ण

/* DMA buffer IOCTL support. */

दीर्घ gntdev_ioctl_dmabuf_exp_from_refs(काष्ठा gntdev_priv *priv, पूर्णांक use_ptemod,
				       काष्ठा ioctl_gntdev_dmabuf_exp_from_refs __user *u)
अणु
	काष्ठा ioctl_gntdev_dmabuf_exp_from_refs op;
	u32 *refs;
	दीर्घ ret;

	अगर (use_ptemod) अणु
		pr_debug("Cannot provide dma-buf: use_ptemode %d\n",
			 use_ptemod);
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&op, u, माप(op)) != 0)
		वापस -EFAULT;

	अगर (unlikely(gntdev_test_page_count(op.count)))
		वापस -EINVAL;

	refs = kसुस्मृति(op.count, माप(*refs), GFP_KERNEL);
	अगर (!refs)
		वापस -ENOMEM;

	अगर (copy_from_user(refs, u->refs, माप(*refs) * op.count) != 0) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	ret = dmabuf_exp_from_refs(priv, op.flags, op.count,
				   op.करोmid, refs, &op.fd);
	अगर (ret)
		जाओ out;

	अगर (copy_to_user(u, &op, माप(op)) != 0)
		ret = -EFAULT;

out:
	kमुक्त(refs);
	वापस ret;
पूर्ण

दीर्घ gntdev_ioctl_dmabuf_exp_रुको_released(काष्ठा gntdev_priv *priv,
					   काष्ठा ioctl_gntdev_dmabuf_exp_रुको_released __user *u)
अणु
	काष्ठा ioctl_gntdev_dmabuf_exp_रुको_released op;

	अगर (copy_from_user(&op, u, माप(op)) != 0)
		वापस -EFAULT;

	वापस dmabuf_exp_रुको_released(priv->dmabuf_priv, op.fd,
					op.रुको_to_ms);
पूर्ण

दीर्घ gntdev_ioctl_dmabuf_imp_to_refs(काष्ठा gntdev_priv *priv,
				     काष्ठा ioctl_gntdev_dmabuf_imp_to_refs __user *u)
अणु
	काष्ठा ioctl_gntdev_dmabuf_imp_to_refs op;
	काष्ठा gntdev_dmabuf *gntdev_dmabuf;
	दीर्घ ret;

	अगर (copy_from_user(&op, u, माप(op)) != 0)
		वापस -EFAULT;

	अगर (unlikely(gntdev_test_page_count(op.count)))
		वापस -EINVAL;

	gntdev_dmabuf = dmabuf_imp_to_refs(priv->dmabuf_priv,
					   priv->dma_dev, op.fd,
					   op.count, op.करोmid);
	अगर (IS_ERR(gntdev_dmabuf))
		वापस PTR_ERR(gntdev_dmabuf);

	अगर (copy_to_user(u->refs, gntdev_dmabuf->u.imp.refs,
			 माप(*u->refs) * op.count) != 0) अणु
		ret = -EFAULT;
		जाओ out_release;
	पूर्ण
	वापस 0;

out_release:
	dmabuf_imp_release(priv->dmabuf_priv, op.fd);
	वापस ret;
पूर्ण

दीर्घ gntdev_ioctl_dmabuf_imp_release(काष्ठा gntdev_priv *priv,
				     काष्ठा ioctl_gntdev_dmabuf_imp_release __user *u)
अणु
	काष्ठा ioctl_gntdev_dmabuf_imp_release op;

	अगर (copy_from_user(&op, u, माप(op)) != 0)
		वापस -EFAULT;

	वापस dmabuf_imp_release(priv->dmabuf_priv, op.fd);
पूर्ण

काष्ठा gntdev_dmabuf_priv *gntdev_dmabuf_init(काष्ठा file *filp)
अणु
	काष्ठा gntdev_dmabuf_priv *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&priv->lock);
	INIT_LIST_HEAD(&priv->exp_list);
	INIT_LIST_HEAD(&priv->exp_रुको_list);
	INIT_LIST_HEAD(&priv->imp_list);

	priv->filp = filp;

	वापस priv;
पूर्ण

व्योम gntdev_dmabuf_fini(काष्ठा gntdev_dmabuf_priv *priv)
अणु
	dmabuf_imp_release_all(priv);
	kमुक्त(priv);
पूर्ण
