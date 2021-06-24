<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2018, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/idr.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/sort.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <uapi/misc/fastrpc.h>

#घोषणा ADSP_DOMAIN_ID (0)
#घोषणा MDSP_DOMAIN_ID (1)
#घोषणा SDSP_DOMAIN_ID (2)
#घोषणा CDSP_DOMAIN_ID (3)
#घोषणा FASTRPC_DEV_MAX		4 /* adsp, mdsp, slpi, cdsp*/
#घोषणा FASTRPC_MAX_SESSIONS	9 /*8 compute, 1 cpz*/
#घोषणा FASTRPC_ALIGN		128
#घोषणा FASTRPC_MAX_FDLIST	16
#घोषणा FASTRPC_MAX_CRCLIST	64
#घोषणा FASTRPC_PHYS(p)	((p) & 0xffffffff)
#घोषणा FASTRPC_CTX_MAX (256)
#घोषणा FASTRPC_INIT_HANDLE	1
#घोषणा FASTRPC_CTXID_MASK (0xFF0)
#घोषणा INIT_खाताLEN_MAX (2 * 1024 * 1024)
#घोषणा FASTRPC_DEVICE_NAME	"fastrpc"
#घोषणा ADSP_MMAP_ADD_PAGES 0x1000

/* Retrives number of input buffers from the scalars parameter */
#घोषणा REMOTE_SCALARS_INBUFS(sc)	(((sc) >> 16) & 0x0ff)

/* Retrives number of output buffers from the scalars parameter */
#घोषणा REMOTE_SCALARS_OUTBUFS(sc)	(((sc) >> 8) & 0x0ff)

/* Retrives number of input handles from the scalars parameter */
#घोषणा REMOTE_SCALARS_INHANDLES(sc)	(((sc) >> 4) & 0x0f)

/* Retrives number of output handles from the scalars parameter */
#घोषणा REMOTE_SCALARS_OUTHANDLES(sc)	((sc) & 0x0f)

#घोषणा REMOTE_SCALARS_LENGTH(sc)	(REMOTE_SCALARS_INBUFS(sc) +   \
					 REMOTE_SCALARS_OUTBUFS(sc) +  \
					 REMOTE_SCALARS_INHANDLES(sc)+ \
					 REMOTE_SCALARS_OUTHANDLES(sc))
#घोषणा FASTRPC_BUILD_SCALARS(attr, method, in, out, oin, oout)  \
				(((attr & 0x07) << 29) |		\
				((method & 0x1f) << 24) |	\
				((in & 0xff) << 16) |		\
				((out & 0xff) <<  8) |		\
				((oin & 0x0f) <<  4) |		\
				(oout & 0x0f))

#घोषणा FASTRPC_SCALARS(method, in, out) \
		FASTRPC_BUILD_SCALARS(0, method, in, out, 0, 0)

#घोषणा FASTRPC_CREATE_PROCESS_NARGS	6
/* Remote Method id table */
#घोषणा FASTRPC_RMID_INIT_ATTACH	0
#घोषणा FASTRPC_RMID_INIT_RELEASE	1
#घोषणा FASTRPC_RMID_INIT_MMAP		4
#घोषणा FASTRPC_RMID_INIT_MUNMAP	5
#घोषणा FASTRPC_RMID_INIT_CREATE	6
#घोषणा FASTRPC_RMID_INIT_CREATE_ATTR	7
#घोषणा FASTRPC_RMID_INIT_CREATE_STATIC	8

/* Protection Doमुख्य(PD) ids */
#घोषणा AUDIO_PD	(0) /* also GUEST_OS PD? */
#घोषणा USER_PD		(1)
#घोषणा SENSORS_PD	(2)

#घोषणा miscdev_to_cctx(d) container_of(d, काष्ठा fastrpc_channel_ctx, miscdev)

अटल स्थिर अक्षर *करोमुख्यs[FASTRPC_DEV_MAX] = अणु "adsp", "mdsp",
						"sdsp", "cdsp"पूर्ण;
काष्ठा fastrpc_phy_page अणु
	u64 addr;		/* physical address */
	u64 size;		/* size of contiguous region */
पूर्ण;

काष्ठा fastrpc_invoke_buf अणु
	u32 num;		/* number of contiguous regions */
	u32 pgidx;		/* index to start of contiguous region */
पूर्ण;

काष्ठा fastrpc_remote_arg अणु
	u64 pv;
	u64 len;
पूर्ण;

काष्ठा fastrpc_mmap_rsp_msg अणु
	u64 vaddr;
पूर्ण;

काष्ठा fastrpc_mmap_req_msg अणु
	s32 pgid;
	u32 flags;
	u64 vaddr;
	s32 num;
पूर्ण;

काष्ठा fastrpc_munmap_req_msg अणु
	s32 pgid;
	u64 vaddr;
	u64 size;
पूर्ण;

काष्ठा fastrpc_msg अणु
	पूर्णांक pid;		/* process group id */
	पूर्णांक tid;		/* thपढ़ो id */
	u64 ctx;		/* invoke caller context */
	u32 handle;	/* handle to invoke */
	u32 sc;		/* scalars काष्ठाure describing the data */
	u64 addr;		/* physical address */
	u64 size;		/* size of contiguous region */
पूर्ण;

काष्ठा fastrpc_invoke_rsp अणु
	u64 ctx;		/* invoke caller context */
	पूर्णांक retval;		/* invoke वापस value */
पूर्ण;

काष्ठा fastrpc_buf_overlap अणु
	u64 start;
	u64 end;
	पूर्णांक raix;
	u64 mstart;
	u64 mend;
	u64 offset;
पूर्ण;

काष्ठा fastrpc_buf अणु
	काष्ठा fastrpc_user *fl;
	काष्ठा dma_buf *dmabuf;
	काष्ठा device *dev;
	व्योम *virt;
	u64 phys;
	u64 size;
	/* Lock क्रम dma buf attachments */
	काष्ठा mutex lock;
	काष्ठा list_head attachments;
	/* mmap support */
	काष्ठा list_head node; /* list of user requested mmaps */
	uपूर्णांकptr_t raddr;
पूर्ण;

काष्ठा fastrpc_dma_buf_attachment अणु
	काष्ठा device *dev;
	काष्ठा sg_table sgt;
	काष्ठा list_head node;
पूर्ण;

काष्ठा fastrpc_map अणु
	काष्ठा list_head node;
	काष्ठा fastrpc_user *fl;
	पूर्णांक fd;
	काष्ठा dma_buf *buf;
	काष्ठा sg_table *table;
	काष्ठा dma_buf_attachment *attach;
	u64 phys;
	u64 size;
	व्योम *va;
	u64 len;
	काष्ठा kref refcount;
पूर्ण;

काष्ठा fastrpc_invoke_ctx अणु
	पूर्णांक nscalars;
	पूर्णांक nbufs;
	पूर्णांक retval;
	पूर्णांक pid;
	पूर्णांक tgid;
	u32 sc;
	u32 *crc;
	u64 ctxid;
	u64 msg_sz;
	काष्ठा kref refcount;
	काष्ठा list_head node; /* list of ctxs */
	काष्ठा completion work;
	काष्ठा work_काष्ठा put_work;
	काष्ठा fastrpc_msg msg;
	काष्ठा fastrpc_user *fl;
	काष्ठा fastrpc_remote_arg *rpra;
	काष्ठा fastrpc_map **maps;
	काष्ठा fastrpc_buf *buf;
	काष्ठा fastrpc_invoke_args *args;
	काष्ठा fastrpc_buf_overlap *olaps;
	काष्ठा fastrpc_channel_ctx *cctx;
पूर्ण;

काष्ठा fastrpc_session_ctx अणु
	काष्ठा device *dev;
	पूर्णांक sid;
	bool used;
	bool valid;
पूर्ण;

काष्ठा fastrpc_channel_ctx अणु
	पूर्णांक करोमुख्य_id;
	पूर्णांक sesscount;
	काष्ठा rpmsg_device *rpdev;
	काष्ठा fastrpc_session_ctx session[FASTRPC_MAX_SESSIONS];
	spinlock_t lock;
	काष्ठा idr ctx_idr;
	काष्ठा list_head users;
	काष्ठा miscdevice miscdev;
	काष्ठा kref refcount;
पूर्ण;

काष्ठा fastrpc_user अणु
	काष्ठा list_head user;
	काष्ठा list_head maps;
	काष्ठा list_head pending;
	काष्ठा list_head mmaps;

	काष्ठा fastrpc_channel_ctx *cctx;
	काष्ठा fastrpc_session_ctx *sctx;
	काष्ठा fastrpc_buf *init_mem;

	पूर्णांक tgid;
	पूर्णांक pd;
	/* Lock क्रम lists */
	spinlock_t lock;
	/* lock क्रम allocations */
	काष्ठा mutex mutex;
पूर्ण;

अटल व्योम fastrpc_मुक्त_map(काष्ठा kref *ref)
अणु
	काष्ठा fastrpc_map *map;

	map = container_of(ref, काष्ठा fastrpc_map, refcount);

	अगर (map->table) अणु
		dma_buf_unmap_attachment(map->attach, map->table,
					 DMA_BIसूचीECTIONAL);
		dma_buf_detach(map->buf, map->attach);
		dma_buf_put(map->buf);
	पूर्ण

	kमुक्त(map);
पूर्ण

अटल व्योम fastrpc_map_put(काष्ठा fastrpc_map *map)
अणु
	अगर (map)
		kref_put(&map->refcount, fastrpc_मुक्त_map);
पूर्ण

अटल व्योम fastrpc_map_get(काष्ठा fastrpc_map *map)
अणु
	अगर (map)
		kref_get(&map->refcount);
पूर्ण

अटल पूर्णांक fastrpc_map_find(काष्ठा fastrpc_user *fl, पूर्णांक fd,
			    काष्ठा fastrpc_map **ppmap)
अणु
	काष्ठा fastrpc_map *map = शून्य;

	mutex_lock(&fl->mutex);
	list_क्रम_each_entry(map, &fl->maps, node) अणु
		अगर (map->fd == fd) अणु
			fastrpc_map_get(map);
			*ppmap = map;
			mutex_unlock(&fl->mutex);
			वापस 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&fl->mutex);

	वापस -ENOENT;
पूर्ण

अटल व्योम fastrpc_buf_मुक्त(काष्ठा fastrpc_buf *buf)
अणु
	dma_मुक्त_coherent(buf->dev, buf->size, buf->virt,
			  FASTRPC_PHYS(buf->phys));
	kमुक्त(buf);
पूर्ण

अटल पूर्णांक fastrpc_buf_alloc(काष्ठा fastrpc_user *fl, काष्ठा device *dev,
			     u64 size, काष्ठा fastrpc_buf **obuf)
अणु
	काष्ठा fastrpc_buf *buf;

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&buf->attachments);
	INIT_LIST_HEAD(&buf->node);
	mutex_init(&buf->lock);

	buf->fl = fl;
	buf->virt = शून्य;
	buf->phys = 0;
	buf->size = size;
	buf->dev = dev;
	buf->raddr = 0;

	buf->virt = dma_alloc_coherent(dev, buf->size, (dma_addr_t *)&buf->phys,
				       GFP_KERNEL);
	अगर (!buf->virt) अणु
		mutex_destroy(&buf->lock);
		kमुक्त(buf);
		वापस -ENOMEM;
	पूर्ण

	अगर (fl->sctx && fl->sctx->sid)
		buf->phys += ((u64)fl->sctx->sid << 32);

	*obuf = buf;

	वापस 0;
पूर्ण

अटल व्योम fastrpc_channel_ctx_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा fastrpc_channel_ctx *cctx;

	cctx = container_of(ref, काष्ठा fastrpc_channel_ctx, refcount);

	kमुक्त(cctx);
पूर्ण

अटल व्योम fastrpc_channel_ctx_get(काष्ठा fastrpc_channel_ctx *cctx)
अणु
	kref_get(&cctx->refcount);
पूर्ण

अटल व्योम fastrpc_channel_ctx_put(काष्ठा fastrpc_channel_ctx *cctx)
अणु
	kref_put(&cctx->refcount, fastrpc_channel_ctx_मुक्त);
पूर्ण

अटल व्योम fastrpc_context_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा fastrpc_invoke_ctx *ctx;
	काष्ठा fastrpc_channel_ctx *cctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	ctx = container_of(ref, काष्ठा fastrpc_invoke_ctx, refcount);
	cctx = ctx->cctx;

	क्रम (i = 0; i < ctx->nscalars; i++)
		fastrpc_map_put(ctx->maps[i]);

	अगर (ctx->buf)
		fastrpc_buf_मुक्त(ctx->buf);

	spin_lock_irqsave(&cctx->lock, flags);
	idr_हटाओ(&cctx->ctx_idr, ctx->ctxid >> 4);
	spin_unlock_irqrestore(&cctx->lock, flags);

	kमुक्त(ctx->maps);
	kमुक्त(ctx->olaps);
	kमुक्त(ctx);

	fastrpc_channel_ctx_put(cctx);
पूर्ण

अटल व्योम fastrpc_context_get(काष्ठा fastrpc_invoke_ctx *ctx)
अणु
	kref_get(&ctx->refcount);
पूर्ण

अटल व्योम fastrpc_context_put(काष्ठा fastrpc_invoke_ctx *ctx)
अणु
	kref_put(&ctx->refcount, fastrpc_context_मुक्त);
पूर्ण

अटल व्योम fastrpc_context_put_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fastrpc_invoke_ctx *ctx =
			container_of(work, काष्ठा fastrpc_invoke_ctx, put_work);

	fastrpc_context_put(ctx);
पूर्ण

#घोषणा CMP(aa, bb) ((aa) == (bb) ? 0 : (aa) < (bb) ? -1 : 1)
अटल पूर्णांक olaps_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	काष्ठा fastrpc_buf_overlap *pa = (काष्ठा fastrpc_buf_overlap *)a;
	काष्ठा fastrpc_buf_overlap *pb = (काष्ठा fastrpc_buf_overlap *)b;
	/* sort with lowest starting buffer first */
	पूर्णांक st = CMP(pa->start, pb->start);
	/* sort with highest ending buffer first */
	पूर्णांक ed = CMP(pb->end, pa->end);

	वापस st == 0 ? ed : st;
पूर्ण

अटल व्योम fastrpc_get_buff_overlaps(काष्ठा fastrpc_invoke_ctx *ctx)
अणु
	u64 max_end = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ctx->nbufs; ++i) अणु
		ctx->olaps[i].start = ctx->args[i].ptr;
		ctx->olaps[i].end = ctx->olaps[i].start + ctx->args[i].length;
		ctx->olaps[i].raix = i;
	पूर्ण

	sort(ctx->olaps, ctx->nbufs, माप(*ctx->olaps), olaps_cmp, शून्य);

	क्रम (i = 0; i < ctx->nbufs; ++i) अणु
		/* Falling inside previous range */
		अगर (ctx->olaps[i].start < max_end) अणु
			ctx->olaps[i].mstart = max_end;
			ctx->olaps[i].mend = ctx->olaps[i].end;
			ctx->olaps[i].offset = max_end - ctx->olaps[i].start;

			अगर (ctx->olaps[i].end > max_end) अणु
				max_end = ctx->olaps[i].end;
			पूर्ण अन्यथा अणु
				ctx->olaps[i].mend = 0;
				ctx->olaps[i].mstart = 0;
			पूर्ण

		पूर्ण अन्यथा  अणु
			ctx->olaps[i].mend = ctx->olaps[i].end;
			ctx->olaps[i].mstart = ctx->olaps[i].start;
			ctx->olaps[i].offset = 0;
			max_end = ctx->olaps[i].end;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा fastrpc_invoke_ctx *fastrpc_context_alloc(
			काष्ठा fastrpc_user *user, u32 kernel, u32 sc,
			काष्ठा fastrpc_invoke_args *args)
अणु
	काष्ठा fastrpc_channel_ctx *cctx = user->cctx;
	काष्ठा fastrpc_invoke_ctx *ctx = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&ctx->node);
	ctx->fl = user;
	ctx->nscalars = REMOTE_SCALARS_LENGTH(sc);
	ctx->nbufs = REMOTE_SCALARS_INBUFS(sc) +
		     REMOTE_SCALARS_OUTBUFS(sc);

	अगर (ctx->nscalars) अणु
		ctx->maps = kसुस्मृति(ctx->nscalars,
				    माप(*ctx->maps), GFP_KERNEL);
		अगर (!ctx->maps) अणु
			kमुक्त(ctx);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		ctx->olaps = kसुस्मृति(ctx->nscalars,
				    माप(*ctx->olaps), GFP_KERNEL);
		अगर (!ctx->olaps) अणु
			kमुक्त(ctx->maps);
			kमुक्त(ctx);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		ctx->args = args;
		fastrpc_get_buff_overlaps(ctx);
	पूर्ण

	/* Released in fastrpc_context_put() */
	fastrpc_channel_ctx_get(cctx);

	ctx->sc = sc;
	ctx->retval = -1;
	ctx->pid = current->pid;
	ctx->tgid = user->tgid;
	ctx->cctx = cctx;
	init_completion(&ctx->work);
	INIT_WORK(&ctx->put_work, fastrpc_context_put_wq);

	spin_lock(&user->lock);
	list_add_tail(&ctx->node, &user->pending);
	spin_unlock(&user->lock);

	spin_lock_irqsave(&cctx->lock, flags);
	ret = idr_alloc_cyclic(&cctx->ctx_idr, ctx, 1,
			       FASTRPC_CTX_MAX, GFP_ATOMIC);
	अगर (ret < 0) अणु
		spin_unlock_irqrestore(&cctx->lock, flags);
		जाओ err_idr;
	पूर्ण
	ctx->ctxid = ret << 4;
	spin_unlock_irqrestore(&cctx->lock, flags);

	kref_init(&ctx->refcount);

	वापस ctx;
err_idr:
	spin_lock(&user->lock);
	list_del(&ctx->node);
	spin_unlock(&user->lock);
	fastrpc_channel_ctx_put(cctx);
	kमुक्त(ctx->maps);
	kमुक्त(ctx->olaps);
	kमुक्त(ctx);

	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा sg_table *
fastrpc_map_dma_buf(काष्ठा dma_buf_attachment *attachment,
		    क्रमागत dma_data_direction dir)
अणु
	काष्ठा fastrpc_dma_buf_attachment *a = attachment->priv;
	काष्ठा sg_table *table;
	पूर्णांक ret;

	table = &a->sgt;

	ret = dma_map_sgtable(attachment->dev, table, dir, 0);
	अगर (ret)
		table = ERR_PTR(ret);
	वापस table;
पूर्ण

अटल व्योम fastrpc_unmap_dma_buf(काष्ठा dma_buf_attachment *attach,
				  काष्ठा sg_table *table,
				  क्रमागत dma_data_direction dir)
अणु
	dma_unmap_sgtable(attach->dev, table, dir, 0);
पूर्ण

अटल व्योम fastrpc_release(काष्ठा dma_buf *dmabuf)
अणु
	काष्ठा fastrpc_buf *buffer = dmabuf->priv;

	fastrpc_buf_मुक्त(buffer);
पूर्ण

अटल पूर्णांक fastrpc_dma_buf_attach(काष्ठा dma_buf *dmabuf,
				  काष्ठा dma_buf_attachment *attachment)
अणु
	काष्ठा fastrpc_dma_buf_attachment *a;
	काष्ठा fastrpc_buf *buffer = dmabuf->priv;
	पूर्णांक ret;

	a = kzalloc(माप(*a), GFP_KERNEL);
	अगर (!a)
		वापस -ENOMEM;

	ret = dma_get_sgtable(buffer->dev, &a->sgt, buffer->virt,
			      FASTRPC_PHYS(buffer->phys), buffer->size);
	अगर (ret < 0) अणु
		dev_err(buffer->dev, "failed to get scatterlist from DMA API\n");
		kमुक्त(a);
		वापस -EINVAL;
	पूर्ण

	a->dev = attachment->dev;
	INIT_LIST_HEAD(&a->node);
	attachment->priv = a;

	mutex_lock(&buffer->lock);
	list_add(&a->node, &buffer->attachments);
	mutex_unlock(&buffer->lock);

	वापस 0;
पूर्ण

अटल व्योम fastrpc_dma_buf_detatch(काष्ठा dma_buf *dmabuf,
				    काष्ठा dma_buf_attachment *attachment)
अणु
	काष्ठा fastrpc_dma_buf_attachment *a = attachment->priv;
	काष्ठा fastrpc_buf *buffer = dmabuf->priv;

	mutex_lock(&buffer->lock);
	list_del(&a->node);
	mutex_unlock(&buffer->lock);
	sg_मुक्त_table(&a->sgt);
	kमुक्त(a);
पूर्ण

अटल पूर्णांक fastrpc_vmap(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा fastrpc_buf *buf = dmabuf->priv;

	dma_buf_map_set_vaddr(map, buf->virt);

	वापस 0;
पूर्ण

अटल पूर्णांक fastrpc_mmap(काष्ठा dma_buf *dmabuf,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा fastrpc_buf *buf = dmabuf->priv;
	माप_प्रकार size = vma->vm_end - vma->vm_start;

	वापस dma_mmap_coherent(buf->dev, vma, buf->virt,
				 FASTRPC_PHYS(buf->phys), size);
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops fastrpc_dma_buf_ops = अणु
	.attach = fastrpc_dma_buf_attach,
	.detach = fastrpc_dma_buf_detatch,
	.map_dma_buf = fastrpc_map_dma_buf,
	.unmap_dma_buf = fastrpc_unmap_dma_buf,
	.mmap = fastrpc_mmap,
	.vmap = fastrpc_vmap,
	.release = fastrpc_release,
पूर्ण;

अटल पूर्णांक fastrpc_map_create(काष्ठा fastrpc_user *fl, पूर्णांक fd,
			      u64 len, काष्ठा fastrpc_map **ppmap)
अणु
	काष्ठा fastrpc_session_ctx *sess = fl->sctx;
	काष्ठा fastrpc_map *map = शून्य;
	पूर्णांक err = 0;

	अगर (!fastrpc_map_find(fl, fd, ppmap))
		वापस 0;

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&map->node);
	map->fl = fl;
	map->fd = fd;
	map->buf = dma_buf_get(fd);
	अगर (IS_ERR(map->buf)) अणु
		err = PTR_ERR(map->buf);
		जाओ get_err;
	पूर्ण

	map->attach = dma_buf_attach(map->buf, sess->dev);
	अगर (IS_ERR(map->attach)) अणु
		dev_err(sess->dev, "Failed to attach dmabuf\n");
		err = PTR_ERR(map->attach);
		जाओ attach_err;
	पूर्ण

	map->table = dma_buf_map_attachment(map->attach, DMA_BIसूचीECTIONAL);
	अगर (IS_ERR(map->table)) अणु
		err = PTR_ERR(map->table);
		जाओ map_err;
	पूर्ण

	map->phys = sg_dma_address(map->table->sgl);
	map->phys += ((u64)fl->sctx->sid << 32);
	map->size = len;
	map->va = sg_virt(map->table->sgl);
	map->len = len;
	kref_init(&map->refcount);

	spin_lock(&fl->lock);
	list_add_tail(&map->node, &fl->maps);
	spin_unlock(&fl->lock);
	*ppmap = map;

	वापस 0;

map_err:
	dma_buf_detach(map->buf, map->attach);
attach_err:
	dma_buf_put(map->buf);
get_err:
	kमुक्त(map);

	वापस err;
पूर्ण

/*
 * Fastrpc payload buffer with metadata looks like:
 *
 * >>>>>>  START of METADATA <<<<<<<<<
 * +---------------------------------+
 * |           Arguments             |
 * | type:(काष्ठा fastrpc_remote_arg)|
 * |             (0 - N)             |
 * +---------------------------------+
 * |         Invoke Buffer list      |
 * | type:(काष्ठा fastrpc_invoke_buf)|
 * |           (0 - N)               |
 * +---------------------------------+
 * |         Page info list          |
 * | type:(काष्ठा fastrpc_phy_page)  |
 * |             (0 - N)             |
 * +---------------------------------+
 * |         Optional info           |
 * |(can be specअगरic to SoC/Firmware)|
 * +---------------------------------+
 * >>>>>>>>  END of METADATA <<<<<<<<<
 * +---------------------------------+
 * |         Inline ARGS             |
 * |            (0-N)                |
 * +---------------------------------+
 */

अटल पूर्णांक fastrpc_get_meta_size(काष्ठा fastrpc_invoke_ctx *ctx)
अणु
	पूर्णांक size = 0;

	size = (माप(काष्ठा fastrpc_remote_arg) +
		माप(काष्ठा fastrpc_invoke_buf) +
		माप(काष्ठा fastrpc_phy_page)) * ctx->nscalars +
		माप(u64) * FASTRPC_MAX_FDLIST +
		माप(u32) * FASTRPC_MAX_CRCLIST;

	वापस size;
पूर्ण

अटल u64 fastrpc_get_payload_size(काष्ठा fastrpc_invoke_ctx *ctx, पूर्णांक metalen)
अणु
	u64 size = 0;
	पूर्णांक i;

	size = ALIGN(metalen, FASTRPC_ALIGN);
	क्रम (i = 0; i < ctx->nscalars; i++) अणु
		अगर (ctx->args[i].fd == 0 || ctx->args[i].fd == -1) अणु

			अगर (ctx->olaps[i].offset == 0)
				size = ALIGN(size, FASTRPC_ALIGN);

			size += (ctx->olaps[i].mend - ctx->olaps[i].mstart);
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक fastrpc_create_maps(काष्ठा fastrpc_invoke_ctx *ctx)
अणु
	काष्ठा device *dev = ctx->fl->sctx->dev;
	पूर्णांक i, err;

	क्रम (i = 0; i < ctx->nscalars; ++i) अणु
		/* Make sure reserved field is set to 0 */
		अगर (ctx->args[i].reserved)
			वापस -EINVAL;

		अगर (ctx->args[i].fd == 0 || ctx->args[i].fd == -1 ||
		    ctx->args[i].length == 0)
			जारी;

		err = fastrpc_map_create(ctx->fl, ctx->args[i].fd,
					 ctx->args[i].length, &ctx->maps[i]);
		अगर (err) अणु
			dev_err(dev, "Error Creating map %d\n", err);
			वापस -EINVAL;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fastrpc_get_args(u32 kernel, काष्ठा fastrpc_invoke_ctx *ctx)
अणु
	काष्ठा device *dev = ctx->fl->sctx->dev;
	काष्ठा fastrpc_remote_arg *rpra;
	काष्ठा fastrpc_invoke_buf *list;
	काष्ठा fastrpc_phy_page *pages;
	पूर्णांक inbufs, i, oix, err = 0;
	u64 len, rlen, pkt_size;
	u64 pg_start, pg_end;
	uपूर्णांकptr_t args;
	पूर्णांक metalen;

	inbufs = REMOTE_SCALARS_INBUFS(ctx->sc);
	metalen = fastrpc_get_meta_size(ctx);
	pkt_size = fastrpc_get_payload_size(ctx, metalen);

	err = fastrpc_create_maps(ctx);
	अगर (err)
		वापस err;

	ctx->msg_sz = pkt_size;

	err = fastrpc_buf_alloc(ctx->fl, dev, pkt_size, &ctx->buf);
	अगर (err)
		वापस err;

	rpra = ctx->buf->virt;
	list = ctx->buf->virt + ctx->nscalars * माप(*rpra);
	pages = ctx->buf->virt + ctx->nscalars * (माप(*list) +
		माप(*rpra));
	args = (uपूर्णांकptr_t)ctx->buf->virt + metalen;
	rlen = pkt_size - metalen;
	ctx->rpra = rpra;

	क्रम (oix = 0; oix < ctx->nbufs; ++oix) अणु
		पूर्णांक mlen;

		i = ctx->olaps[oix].raix;
		len = ctx->args[i].length;

		rpra[i].pv = 0;
		rpra[i].len = len;
		list[i].num = len ? 1 : 0;
		list[i].pgidx = i;

		अगर (!len)
			जारी;

		अगर (ctx->maps[i]) अणु
			काष्ठा vm_area_काष्ठा *vma = शून्य;

			rpra[i].pv = (u64) ctx->args[i].ptr;
			pages[i].addr = ctx->maps[i]->phys;

			vma = find_vma(current->mm, ctx->args[i].ptr);
			अगर (vma)
				pages[i].addr += ctx->args[i].ptr -
						 vma->vm_start;

			pg_start = (ctx->args[i].ptr & PAGE_MASK) >> PAGE_SHIFT;
			pg_end = ((ctx->args[i].ptr + len - 1) & PAGE_MASK) >>
				  PAGE_SHIFT;
			pages[i].size = (pg_end - pg_start + 1) * PAGE_SIZE;

		पूर्ण अन्यथा अणु

			अगर (ctx->olaps[oix].offset == 0) अणु
				rlen -= ALIGN(args, FASTRPC_ALIGN) - args;
				args = ALIGN(args, FASTRPC_ALIGN);
			पूर्ण

			mlen = ctx->olaps[oix].mend - ctx->olaps[oix].mstart;

			अगर (rlen < mlen)
				जाओ bail;

			rpra[i].pv = args - ctx->olaps[oix].offset;
			pages[i].addr = ctx->buf->phys -
					ctx->olaps[oix].offset +
					(pkt_size - rlen);
			pages[i].addr = pages[i].addr &	PAGE_MASK;

			pg_start = (args & PAGE_MASK) >> PAGE_SHIFT;
			pg_end = ((args + len - 1) & PAGE_MASK) >> PAGE_SHIFT;
			pages[i].size = (pg_end - pg_start + 1) * PAGE_SIZE;
			args = args + mlen;
			rlen -= mlen;
		पूर्ण

		अगर (i < inbufs && !ctx->maps[i]) अणु
			व्योम *dst = (व्योम *)(uपूर्णांकptr_t)rpra[i].pv;
			व्योम *src = (व्योम *)(uपूर्णांकptr_t)ctx->args[i].ptr;

			अगर (!kernel) अणु
				अगर (copy_from_user(dst, (व्योम __user *)src,
						   len)) अणु
					err = -EFAULT;
					जाओ bail;
				पूर्ण
			पूर्ण अन्यथा अणु
				स_नकल(dst, src, len);
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = ctx->nbufs; i < ctx->nscalars; ++i) अणु
		rpra[i].pv = (u64) ctx->args[i].ptr;
		rpra[i].len = ctx->args[i].length;
		list[i].num = ctx->args[i].length ? 1 : 0;
		list[i].pgidx = i;
		pages[i].addr = ctx->maps[i]->phys;
		pages[i].size = ctx->maps[i]->size;
	पूर्ण

bail:
	अगर (err)
		dev_err(dev, "Error: get invoke args failed:%d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक fastrpc_put_args(काष्ठा fastrpc_invoke_ctx *ctx,
			    u32 kernel)
अणु
	काष्ठा fastrpc_remote_arg *rpra = ctx->rpra;
	पूर्णांक i, inbufs;

	inbufs = REMOTE_SCALARS_INBUFS(ctx->sc);

	क्रम (i = inbufs; i < ctx->nbufs; ++i) अणु
		व्योम *src = (व्योम *)(uपूर्णांकptr_t)rpra[i].pv;
		व्योम *dst = (व्योम *)(uपूर्णांकptr_t)ctx->args[i].ptr;
		u64 len = rpra[i].len;

		अगर (!kernel) अणु
			अगर (copy_to_user((व्योम __user *)dst, src, len))
				वापस -EFAULT;
		पूर्ण अन्यथा अणु
			स_नकल(dst, src, len);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fastrpc_invoke_send(काष्ठा fastrpc_session_ctx *sctx,
			       काष्ठा fastrpc_invoke_ctx *ctx,
			       u32 kernel, uपूर्णांक32_t handle)
अणु
	काष्ठा fastrpc_channel_ctx *cctx;
	काष्ठा fastrpc_user *fl = ctx->fl;
	काष्ठा fastrpc_msg *msg = &ctx->msg;
	पूर्णांक ret;

	cctx = fl->cctx;
	msg->pid = fl->tgid;
	msg->tid = current->pid;

	अगर (kernel)
		msg->pid = 0;

	msg->ctx = ctx->ctxid | fl->pd;
	msg->handle = handle;
	msg->sc = ctx->sc;
	msg->addr = ctx->buf ? ctx->buf->phys : 0;
	msg->size = roundup(ctx->msg_sz, PAGE_SIZE);
	fastrpc_context_get(ctx);

	ret = rpmsg_send(cctx->rpdev->ept, (व्योम *)msg, माप(*msg));

	अगर (ret)
		fastrpc_context_put(ctx);

	वापस ret;

पूर्ण

अटल पूर्णांक fastrpc_पूर्णांकernal_invoke(काष्ठा fastrpc_user *fl,  u32 kernel,
				   u32 handle, u32 sc,
				   काष्ठा fastrpc_invoke_args *args)
अणु
	काष्ठा fastrpc_invoke_ctx *ctx = शून्य;
	पूर्णांक err = 0;

	अगर (!fl->sctx)
		वापस -EINVAL;

	अगर (!fl->cctx->rpdev)
		वापस -EPIPE;

	अगर (handle == FASTRPC_INIT_HANDLE && !kernel) अणु
		dev_warn_ratelimited(fl->sctx->dev, "user app trying to send a kernel RPC message (%d)\n",  handle);
		वापस -EPERM;
	पूर्ण

	ctx = fastrpc_context_alloc(fl, kernel, sc, args);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	अगर (ctx->nscalars) अणु
		err = fastrpc_get_args(kernel, ctx);
		अगर (err)
			जाओ bail;
	पूर्ण

	/* make sure that all CPU memory ग_लिखोs are seen by DSP */
	dma_wmb();
	/* Send invoke buffer to remote dsp */
	err = fastrpc_invoke_send(fl->sctx, ctx, kernel, handle);
	अगर (err)
		जाओ bail;

	अगर (kernel) अणु
		अगर (!रुको_क्रम_completion_समयout(&ctx->work, 10 * HZ))
			err = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		err = रुको_क्रम_completion_पूर्णांकerruptible(&ctx->work);
	पूर्ण

	अगर (err)
		जाओ bail;

	/* Check the response from remote dsp */
	err = ctx->retval;
	अगर (err)
		जाओ bail;

	अगर (ctx->nscalars) अणु
		/* make sure that all memory ग_लिखोs by DSP are seen by CPU */
		dma_rmb();
		/* populate all the output buffers with results */
		err = fastrpc_put_args(ctx, kernel);
		अगर (err)
			जाओ bail;
	पूर्ण

bail:
	अगर (err != -ERESTARTSYS && err != -ETIMEDOUT) अणु
		/* We are करोne with this compute context */
		spin_lock(&fl->lock);
		list_del(&ctx->node);
		spin_unlock(&fl->lock);
		fastrpc_context_put(ctx);
	पूर्ण
	अगर (err)
		dev_dbg(fl->sctx->dev, "Error: Invoke Failed %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक fastrpc_init_create_process(काष्ठा fastrpc_user *fl,
					अक्षर __user *argp)
अणु
	काष्ठा fastrpc_init_create init;
	काष्ठा fastrpc_invoke_args *args;
	काष्ठा fastrpc_phy_page pages[1];
	काष्ठा fastrpc_map *map = शून्य;
	काष्ठा fastrpc_buf *imem = शून्य;
	पूर्णांक memlen;
	पूर्णांक err;
	काष्ठा अणु
		पूर्णांक pgid;
		u32 namelen;
		u32 filelen;
		u32 pageslen;
		u32 attrs;
		u32 siglen;
	पूर्ण inbuf;
	u32 sc;

	args = kसुस्मृति(FASTRPC_CREATE_PROCESS_NARGS, माप(*args), GFP_KERNEL);
	अगर (!args)
		वापस -ENOMEM;

	अगर (copy_from_user(&init, argp, माप(init))) अणु
		err = -EFAULT;
		जाओ err;
	पूर्ण

	अगर (init.filelen > INIT_खाताLEN_MAX) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	inbuf.pgid = fl->tgid;
	inbuf.namelen = म_माप(current->comm) + 1;
	inbuf.filelen = init.filelen;
	inbuf.pageslen = 1;
	inbuf.attrs = init.attrs;
	inbuf.siglen = init.siglen;
	fl->pd = USER_PD;

	अगर (init.filelen && init.filefd) अणु
		err = fastrpc_map_create(fl, init.filefd, init.filelen, &map);
		अगर (err)
			जाओ err;
	पूर्ण

	memlen = ALIGN(max(INIT_खाताLEN_MAX, (पूर्णांक)init.filelen * 4),
		       1024 * 1024);
	err = fastrpc_buf_alloc(fl, fl->sctx->dev, memlen,
				&imem);
	अगर (err)
		जाओ err_alloc;

	fl->init_mem = imem;
	args[0].ptr = (u64)(uपूर्णांकptr_t)&inbuf;
	args[0].length = माप(inbuf);
	args[0].fd = -1;

	args[1].ptr = (u64)(uपूर्णांकptr_t)current->comm;
	args[1].length = inbuf.namelen;
	args[1].fd = -1;

	args[2].ptr = (u64) init.file;
	args[2].length = inbuf.filelen;
	args[2].fd = init.filefd;

	pages[0].addr = imem->phys;
	pages[0].size = imem->size;

	args[3].ptr = (u64)(uपूर्णांकptr_t) pages;
	args[3].length = 1 * माप(*pages);
	args[3].fd = -1;

	args[4].ptr = (u64)(uपूर्णांकptr_t)&inbuf.attrs;
	args[4].length = माप(inbuf.attrs);
	args[4].fd = -1;

	args[5].ptr = (u64)(uपूर्णांकptr_t) &inbuf.siglen;
	args[5].length = माप(inbuf.siglen);
	args[5].fd = -1;

	sc = FASTRPC_SCALARS(FASTRPC_RMID_INIT_CREATE, 4, 0);
	अगर (init.attrs)
		sc = FASTRPC_SCALARS(FASTRPC_RMID_INIT_CREATE_ATTR, 6, 0);

	err = fastrpc_पूर्णांकernal_invoke(fl, true, FASTRPC_INIT_HANDLE,
				      sc, args);
	अगर (err)
		जाओ err_invoke;

	kमुक्त(args);

	वापस 0;

err_invoke:
	fl->init_mem = शून्य;
	fastrpc_buf_मुक्त(imem);
err_alloc:
	अगर (map) अणु
		spin_lock(&fl->lock);
		list_del(&map->node);
		spin_unlock(&fl->lock);
		fastrpc_map_put(map);
	पूर्ण
err:
	kमुक्त(args);

	वापस err;
पूर्ण

अटल काष्ठा fastrpc_session_ctx *fastrpc_session_alloc(
					काष्ठा fastrpc_channel_ctx *cctx)
अणु
	काष्ठा fastrpc_session_ctx *session = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&cctx->lock, flags);
	क्रम (i = 0; i < cctx->sesscount; i++) अणु
		अगर (!cctx->session[i].used && cctx->session[i].valid) अणु
			cctx->session[i].used = true;
			session = &cctx->session[i];
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cctx->lock, flags);

	वापस session;
पूर्ण

अटल व्योम fastrpc_session_मुक्त(काष्ठा fastrpc_channel_ctx *cctx,
				 काष्ठा fastrpc_session_ctx *session)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cctx->lock, flags);
	session->used = false;
	spin_unlock_irqrestore(&cctx->lock, flags);
पूर्ण

अटल पूर्णांक fastrpc_release_current_dsp_process(काष्ठा fastrpc_user *fl)
अणु
	काष्ठा fastrpc_invoke_args args[1];
	पूर्णांक tgid = 0;
	u32 sc;

	tgid = fl->tgid;
	args[0].ptr = (u64)(uपूर्णांकptr_t) &tgid;
	args[0].length = माप(tgid);
	args[0].fd = -1;
	args[0].reserved = 0;
	sc = FASTRPC_SCALARS(FASTRPC_RMID_INIT_RELEASE, 1, 0);

	वापस fastrpc_पूर्णांकernal_invoke(fl, true, FASTRPC_INIT_HANDLE,
				       sc, &args[0]);
पूर्ण

अटल पूर्णांक fastrpc_device_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fastrpc_user *fl = (काष्ठा fastrpc_user *)file->निजी_data;
	काष्ठा fastrpc_channel_ctx *cctx = fl->cctx;
	काष्ठा fastrpc_invoke_ctx *ctx, *n;
	काष्ठा fastrpc_map *map, *m;
	काष्ठा fastrpc_buf *buf, *b;
	अचिन्हित दीर्घ flags;

	fastrpc_release_current_dsp_process(fl);

	spin_lock_irqsave(&cctx->lock, flags);
	list_del(&fl->user);
	spin_unlock_irqrestore(&cctx->lock, flags);

	अगर (fl->init_mem)
		fastrpc_buf_मुक्त(fl->init_mem);

	list_क्रम_each_entry_safe(ctx, n, &fl->pending, node) अणु
		list_del(&ctx->node);
		fastrpc_context_put(ctx);
	पूर्ण

	list_क्रम_each_entry_safe(map, m, &fl->maps, node) अणु
		list_del(&map->node);
		fastrpc_map_put(map);
	पूर्ण

	list_क्रम_each_entry_safe(buf, b, &fl->mmaps, node) अणु
		list_del(&buf->node);
		fastrpc_buf_मुक्त(buf);
	पूर्ण

	fastrpc_session_मुक्त(cctx, fl->sctx);
	fastrpc_channel_ctx_put(cctx);

	mutex_destroy(&fl->mutex);
	kमुक्त(fl);
	file->निजी_data = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक fastrpc_device_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा fastrpc_channel_ctx *cctx = miscdev_to_cctx(filp->निजी_data);
	काष्ठा fastrpc_user *fl = शून्य;
	अचिन्हित दीर्घ flags;

	fl = kzalloc(माप(*fl), GFP_KERNEL);
	अगर (!fl)
		वापस -ENOMEM;

	/* Released in fastrpc_device_release() */
	fastrpc_channel_ctx_get(cctx);

	filp->निजी_data = fl;
	spin_lock_init(&fl->lock);
	mutex_init(&fl->mutex);
	INIT_LIST_HEAD(&fl->pending);
	INIT_LIST_HEAD(&fl->maps);
	INIT_LIST_HEAD(&fl->mmaps);
	INIT_LIST_HEAD(&fl->user);
	fl->tgid = current->tgid;
	fl->cctx = cctx;

	fl->sctx = fastrpc_session_alloc(cctx);
	अगर (!fl->sctx) अणु
		dev_err(&cctx->rpdev->dev, "No session available\n");
		mutex_destroy(&fl->mutex);
		kमुक्त(fl);

		वापस -EBUSY;
	पूर्ण

	spin_lock_irqsave(&cctx->lock, flags);
	list_add_tail(&fl->user, &cctx->users);
	spin_unlock_irqrestore(&cctx->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक fastrpc_dmabuf_alloc(काष्ठा fastrpc_user *fl, अक्षर __user *argp)
अणु
	काष्ठा fastrpc_alloc_dma_buf bp;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	काष्ठा fastrpc_buf *buf = शून्य;
	पूर्णांक err;

	अगर (copy_from_user(&bp, argp, माप(bp)))
		वापस -EFAULT;

	err = fastrpc_buf_alloc(fl, fl->sctx->dev, bp.size, &buf);
	अगर (err)
		वापस err;
	exp_info.ops = &fastrpc_dma_buf_ops;
	exp_info.size = bp.size;
	exp_info.flags = O_RDWR;
	exp_info.priv = buf;
	buf->dmabuf = dma_buf_export(&exp_info);
	अगर (IS_ERR(buf->dmabuf)) अणु
		err = PTR_ERR(buf->dmabuf);
		fastrpc_buf_मुक्त(buf);
		वापस err;
	पूर्ण

	bp.fd = dma_buf_fd(buf->dmabuf, O_ACCMODE);
	अगर (bp.fd < 0) अणु
		dma_buf_put(buf->dmabuf);
		वापस -EINVAL;
	पूर्ण

	अगर (copy_to_user(argp, &bp, माप(bp))) अणु
		dma_buf_put(buf->dmabuf);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fastrpc_init_attach(काष्ठा fastrpc_user *fl, पूर्णांक pd)
अणु
	काष्ठा fastrpc_invoke_args args[1];
	पूर्णांक tgid = fl->tgid;
	u32 sc;

	args[0].ptr = (u64)(uपूर्णांकptr_t) &tgid;
	args[0].length = माप(tgid);
	args[0].fd = -1;
	args[0].reserved = 0;
	sc = FASTRPC_SCALARS(FASTRPC_RMID_INIT_ATTACH, 1, 0);
	fl->pd = pd;

	वापस fastrpc_पूर्णांकernal_invoke(fl, true, FASTRPC_INIT_HANDLE,
				       sc, &args[0]);
पूर्ण

अटल पूर्णांक fastrpc_invoke(काष्ठा fastrpc_user *fl, अक्षर __user *argp)
अणु
	काष्ठा fastrpc_invoke_args *args = शून्य;
	काष्ठा fastrpc_invoke inv;
	u32 nscalars;
	पूर्णांक err;

	अगर (copy_from_user(&inv, argp, माप(inv)))
		वापस -EFAULT;

	/* nscalars is truncated here to max supported value */
	nscalars = REMOTE_SCALARS_LENGTH(inv.sc);
	अगर (nscalars) अणु
		args = kसुस्मृति(nscalars, माप(*args), GFP_KERNEL);
		अगर (!args)
			वापस -ENOMEM;

		अगर (copy_from_user(args, (व्योम __user *)(uपूर्णांकptr_t)inv.args,
				   nscalars * माप(*args))) अणु
			kमुक्त(args);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	err = fastrpc_पूर्णांकernal_invoke(fl, false, inv.handle, inv.sc, args);
	kमुक्त(args);

	वापस err;
पूर्ण

अटल पूर्णांक fastrpc_req_munmap_impl(काष्ठा fastrpc_user *fl,
				   काष्ठा fastrpc_req_munmap *req)
अणु
	काष्ठा fastrpc_invoke_args args[1] = अणु [0] = अणु 0 पूर्ण पूर्ण;
	काष्ठा fastrpc_buf *buf, *b;
	काष्ठा fastrpc_munmap_req_msg req_msg;
	काष्ठा device *dev = fl->sctx->dev;
	पूर्णांक err;
	u32 sc;

	spin_lock(&fl->lock);
	list_क्रम_each_entry_safe(buf, b, &fl->mmaps, node) अणु
		अगर ((buf->raddr == req->vaddrout) && (buf->size == req->size))
			अवरोध;
		buf = शून्य;
	पूर्ण
	spin_unlock(&fl->lock);

	अगर (!buf) अणु
		dev_err(dev, "mmap not in list\n");
		वापस -EINVAL;
	पूर्ण

	req_msg.pgid = fl->tgid;
	req_msg.size = buf->size;
	req_msg.vaddr = buf->raddr;

	args[0].ptr = (u64) (uपूर्णांकptr_t) &req_msg;
	args[0].length = माप(req_msg);

	sc = FASTRPC_SCALARS(FASTRPC_RMID_INIT_MUNMAP, 1, 0);
	err = fastrpc_पूर्णांकernal_invoke(fl, true, FASTRPC_INIT_HANDLE, sc,
				      &args[0]);
	अगर (!err) अणु
		dev_dbg(dev, "unmmap\tpt 0x%09lx OK\n", buf->raddr);
		spin_lock(&fl->lock);
		list_del(&buf->node);
		spin_unlock(&fl->lock);
		fastrpc_buf_मुक्त(buf);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unmmap\tpt 0x%09lx ERROR\n", buf->raddr);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक fastrpc_req_munmap(काष्ठा fastrpc_user *fl, अक्षर __user *argp)
अणु
	काष्ठा fastrpc_req_munmap req;

	अगर (copy_from_user(&req, argp, माप(req)))
		वापस -EFAULT;

	वापस fastrpc_req_munmap_impl(fl, &req);
पूर्ण

अटल पूर्णांक fastrpc_req_mmap(काष्ठा fastrpc_user *fl, अक्षर __user *argp)
अणु
	काष्ठा fastrpc_invoke_args args[3] = अणु [0 ... 2] = अणु 0 पूर्ण पूर्ण;
	काष्ठा fastrpc_buf *buf = शून्य;
	काष्ठा fastrpc_mmap_req_msg req_msg;
	काष्ठा fastrpc_mmap_rsp_msg rsp_msg;
	काष्ठा fastrpc_req_munmap req_unmap;
	काष्ठा fastrpc_phy_page pages;
	काष्ठा fastrpc_req_mmap req;
	काष्ठा device *dev = fl->sctx->dev;
	पूर्णांक err;
	u32 sc;

	अगर (copy_from_user(&req, argp, माप(req)))
		वापस -EFAULT;

	अगर (req.flags != ADSP_MMAP_ADD_PAGES) अणु
		dev_err(dev, "flag not supported 0x%x\n", req.flags);
		वापस -EINVAL;
	पूर्ण

	अगर (req.vaddrin) अणु
		dev_err(dev, "adding user allocated pages is not supported\n");
		वापस -EINVAL;
	पूर्ण

	err = fastrpc_buf_alloc(fl, fl->sctx->dev, req.size, &buf);
	अगर (err) अणु
		dev_err(dev, "failed to allocate buffer\n");
		वापस err;
	पूर्ण

	req_msg.pgid = fl->tgid;
	req_msg.flags = req.flags;
	req_msg.vaddr = req.vaddrin;
	req_msg.num = माप(pages);

	args[0].ptr = (u64) (uपूर्णांकptr_t) &req_msg;
	args[0].length = माप(req_msg);

	pages.addr = buf->phys;
	pages.size = buf->size;

	args[1].ptr = (u64) (uपूर्णांकptr_t) &pages;
	args[1].length = माप(pages);

	args[2].ptr = (u64) (uपूर्णांकptr_t) &rsp_msg;
	args[2].length = माप(rsp_msg);

	sc = FASTRPC_SCALARS(FASTRPC_RMID_INIT_MMAP, 2, 1);
	err = fastrpc_पूर्णांकernal_invoke(fl, true, FASTRPC_INIT_HANDLE, sc,
				      &args[0]);
	अगर (err) अणु
		dev_err(dev, "mmap error (len 0x%08llx)\n", buf->size);
		जाओ err_invoke;
	पूर्ण

	/* update the buffer to be able to deallocate the memory on the DSP */
	buf->raddr = (uपूर्णांकptr_t) rsp_msg.vaddr;

	/* let the client know the address to use */
	req.vaddrout = rsp_msg.vaddr;

	spin_lock(&fl->lock);
	list_add_tail(&buf->node, &fl->mmaps);
	spin_unlock(&fl->lock);

	अगर (copy_to_user((व्योम __user *)argp, &req, माप(req))) अणु
		/* unmap the memory and release the buffer */
		req_unmap.vaddrout = buf->raddr;
		req_unmap.size = buf->size;
		fastrpc_req_munmap_impl(fl, &req_unmap);
		वापस -EFAULT;
	पूर्ण

	dev_dbg(dev, "mmap\t\tpt 0x%09lx OK [len 0x%08llx]\n",
		buf->raddr, buf->size);

	वापस 0;

err_invoke:
	fastrpc_buf_मुक्त(buf);

	वापस err;
पूर्ण

अटल दीर्घ fastrpc_device_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा fastrpc_user *fl = (काष्ठा fastrpc_user *)file->निजी_data;
	अक्षर __user *argp = (अक्षर __user *)arg;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल FASTRPC_IOCTL_INVOKE:
		err = fastrpc_invoke(fl, argp);
		अवरोध;
	हाल FASTRPC_IOCTL_INIT_ATTACH:
		err = fastrpc_init_attach(fl, AUDIO_PD);
		अवरोध;
	हाल FASTRPC_IOCTL_INIT_ATTACH_SNS:
		err = fastrpc_init_attach(fl, SENSORS_PD);
		अवरोध;
	हाल FASTRPC_IOCTL_INIT_CREATE:
		err = fastrpc_init_create_process(fl, argp);
		अवरोध;
	हाल FASTRPC_IOCTL_ALLOC_DMA_BUFF:
		err = fastrpc_dmabuf_alloc(fl, argp);
		अवरोध;
	हाल FASTRPC_IOCTL_MMAP:
		err = fastrpc_req_mmap(fl, argp);
		अवरोध;
	हाल FASTRPC_IOCTL_MUNMAP:
		err = fastrpc_req_munmap(fl, argp);
		अवरोध;
	शेष:
		err = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations fastrpc_fops = अणु
	.खोलो = fastrpc_device_खोलो,
	.release = fastrpc_device_release,
	.unlocked_ioctl = fastrpc_device_ioctl,
	.compat_ioctl = fastrpc_device_ioctl,
पूर्ण;

अटल पूर्णांक fastrpc_cb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fastrpc_channel_ctx *cctx;
	काष्ठा fastrpc_session_ctx *sess;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i, sessions = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	cctx = dev_get_drvdata(dev->parent);
	अगर (!cctx)
		वापस -EINVAL;

	of_property_पढ़ो_u32(dev->of_node, "qcom,nsessions", &sessions);

	spin_lock_irqsave(&cctx->lock, flags);
	sess = &cctx->session[cctx->sesscount];
	sess->used = false;
	sess->valid = true;
	sess->dev = dev;
	dev_set_drvdata(dev, sess);

	अगर (of_property_पढ़ो_u32(dev->of_node, "reg", &sess->sid))
		dev_info(dev, "FastRPC Session ID not specified in DT\n");

	अगर (sessions > 0) अणु
		काष्ठा fastrpc_session_ctx *dup_sess;

		क्रम (i = 1; i < sessions; i++) अणु
			अगर (cctx->sesscount++ >= FASTRPC_MAX_SESSIONS)
				अवरोध;
			dup_sess = &cctx->session[cctx->sesscount];
			स_नकल(dup_sess, sess, माप(*dup_sess));
		पूर्ण
	पूर्ण
	cctx->sesscount++;
	spin_unlock_irqrestore(&cctx->lock, flags);
	rc = dma_set_mask(dev, DMA_BIT_MASK(32));
	अगर (rc) अणु
		dev_err(dev, "32-bit DMA enable failed\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fastrpc_cb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fastrpc_channel_ctx *cctx = dev_get_drvdata(pdev->dev.parent);
	काष्ठा fastrpc_session_ctx *sess = dev_get_drvdata(&pdev->dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&cctx->lock, flags);
	क्रम (i = 1; i < FASTRPC_MAX_SESSIONS; i++) अणु
		अगर (cctx->session[i].sid == sess->sid) अणु
			cctx->session[i].valid = false;
			cctx->sesscount--;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cctx->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fastrpc_match_table[] = अणु
	अणु .compatible = "qcom,fastrpc-compute-cb", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver fastrpc_cb_driver = अणु
	.probe = fastrpc_cb_probe,
	.हटाओ = fastrpc_cb_हटाओ,
	.driver = अणु
		.name = "qcom,fastrpc-cb",
		.of_match_table = fastrpc_match_table,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक fastrpc_rpmsg_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा device *rdev = &rpdev->dev;
	काष्ठा fastrpc_channel_ctx *data;
	पूर्णांक i, err, करोमुख्य_id = -1;
	स्थिर अक्षर *करोमुख्य;

	err = of_property_पढ़ो_string(rdev->of_node, "label", &करोमुख्य);
	अगर (err) अणु
		dev_info(rdev, "FastRPC Domain not specified in DT\n");
		वापस err;
	पूर्ण

	क्रम (i = 0; i <= CDSP_DOMAIN_ID; i++) अणु
		अगर (!म_भेद(करोमुख्यs[i], करोमुख्य)) अणु
			करोमुख्य_id = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (करोमुख्य_id < 0) अणु
		dev_info(rdev, "FastRPC Invalid Domain ID %d\n", करोमुख्य_id);
		वापस -EINVAL;
	पूर्ण

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->miscdev.minor = MISC_DYNAMIC_MINOR;
	data->miscdev.name = devm_kaप्र_लिखो(rdev, GFP_KERNEL, "fastrpc-%s",
					    करोमुख्यs[करोमुख्य_id]);
	data->miscdev.fops = &fastrpc_fops;
	err = misc_रेजिस्टर(&data->miscdev);
	अगर (err) अणु
		kमुक्त(data);
		वापस err;
	पूर्ण

	kref_init(&data->refcount);

	dev_set_drvdata(&rpdev->dev, data);
	dma_set_mask_and_coherent(rdev, DMA_BIT_MASK(32));
	INIT_LIST_HEAD(&data->users);
	spin_lock_init(&data->lock);
	idr_init(&data->ctx_idr);
	data->करोमुख्य_id = करोमुख्य_id;
	data->rpdev = rpdev;

	वापस of_platक्रमm_populate(rdev->of_node, शून्य, शून्य, rdev);
पूर्ण

अटल व्योम fastrpc_notअगरy_users(काष्ठा fastrpc_user *user)
अणु
	काष्ठा fastrpc_invoke_ctx *ctx;

	spin_lock(&user->lock);
	list_क्रम_each_entry(ctx, &user->pending, node)
		complete(&ctx->work);
	spin_unlock(&user->lock);
पूर्ण

अटल व्योम fastrpc_rpmsg_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा fastrpc_channel_ctx *cctx = dev_get_drvdata(&rpdev->dev);
	काष्ठा fastrpc_user *user;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cctx->lock, flags);
	list_क्रम_each_entry(user, &cctx->users, user)
		fastrpc_notअगरy_users(user);
	spin_unlock_irqrestore(&cctx->lock, flags);

	misc_deरेजिस्टर(&cctx->miscdev);
	of_platक्रमm_depopulate(&rpdev->dev);

	cctx->rpdev = शून्य;
	fastrpc_channel_ctx_put(cctx);
पूर्ण

अटल पूर्णांक fastrpc_rpmsg_callback(काष्ठा rpmsg_device *rpdev, व्योम *data,
				  पूर्णांक len, व्योम *priv, u32 addr)
अणु
	काष्ठा fastrpc_channel_ctx *cctx = dev_get_drvdata(&rpdev->dev);
	काष्ठा fastrpc_invoke_rsp *rsp = data;
	काष्ठा fastrpc_invoke_ctx *ctx;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ ctxid;

	अगर (len < माप(*rsp))
		वापस -EINVAL;

	ctxid = ((rsp->ctx & FASTRPC_CTXID_MASK) >> 4);

	spin_lock_irqsave(&cctx->lock, flags);
	ctx = idr_find(&cctx->ctx_idr, ctxid);
	spin_unlock_irqrestore(&cctx->lock, flags);

	अगर (!ctx) अणु
		dev_err(&rpdev->dev, "No context ID matches response\n");
		वापस -ENOENT;
	पूर्ण

	ctx->retval = rsp->retval;
	complete(&ctx->work);

	/*
	 * The DMA buffer associated with the context cannot be मुक्तd in
	 * पूर्णांकerrupt context so schedule it through a worker thपढ़ो to
	 * aव्योम a kernel BUG.
	 */
	schedule_work(&ctx->put_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fastrpc_rpmsg_of_match[] = अणु
	अणु .compatible = "qcom,fastrpc" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fastrpc_rpmsg_of_match);

अटल काष्ठा rpmsg_driver fastrpc_driver = अणु
	.probe = fastrpc_rpmsg_probe,
	.हटाओ = fastrpc_rpmsg_हटाओ,
	.callback = fastrpc_rpmsg_callback,
	.drv = अणु
		.name = "qcom,fastrpc",
		.of_match_table = fastrpc_rpmsg_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक fastrpc_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&fastrpc_cb_driver);
	अगर (ret < 0) अणु
		pr_err("fastrpc: failed to register cb driver\n");
		वापस ret;
	पूर्ण

	ret = रेजिस्टर_rpmsg_driver(&fastrpc_driver);
	अगर (ret < 0) अणु
		pr_err("fastrpc: failed to register rpmsg driver\n");
		platक्रमm_driver_unरेजिस्टर(&fastrpc_cb_driver);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(fastrpc_init);

अटल व्योम fastrpc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fastrpc_cb_driver);
	unरेजिस्टर_rpmsg_driver(&fastrpc_driver);
पूर्ण
module_निकास(fastrpc_निकास);

MODULE_LICENSE("GPL v2");
