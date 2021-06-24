<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Authors: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_file.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_g2d.h"
#समावेश "exynos_drm_gem.h"

#घोषणा G2D_HW_MAJOR_VER		4
#घोषणा G2D_HW_MINOR_VER		1

/* vaild रेजिस्टर range set from user: 0x0104 ~ 0x0880 */
#घोषणा G2D_VALID_START			0x0104
#घोषणा G2D_VALID_END			0x0880

/* general रेजिस्टरs */
#घोषणा G2D_SOFT_RESET			0x0000
#घोषणा G2D_INTEN			0x0004
#घोषणा G2D_INTC_PEND			0x000C
#घोषणा G2D_DMA_SFR_BASE_ADDR		0x0080
#घोषणा G2D_DMA_COMMAND			0x0084
#घोषणा G2D_DMA_STATUS			0x008C
#घोषणा G2D_DMA_HOLD_CMD		0x0090

/* command रेजिस्टरs */
#घोषणा G2D_BITBLT_START		0x0100

/* रेजिस्टरs क्रम base address */
#घोषणा G2D_SRC_BASE_ADDR		0x0304
#घोषणा G2D_SRC_STRIDE			0x0308
#घोषणा G2D_SRC_COLOR_MODE		0x030C
#घोषणा G2D_SRC_LEFT_TOP		0x0310
#घोषणा G2D_SRC_RIGHT_BOTTOM		0x0314
#घोषणा G2D_SRC_PLANE2_BASE_ADDR	0x0318
#घोषणा G2D_DST_BASE_ADDR		0x0404
#घोषणा G2D_DST_STRIDE			0x0408
#घोषणा G2D_DST_COLOR_MODE		0x040C
#घोषणा G2D_DST_LEFT_TOP		0x0410
#घोषणा G2D_DST_RIGHT_BOTTOM		0x0414
#घोषणा G2D_DST_PLANE2_BASE_ADDR	0x0418
#घोषणा G2D_PAT_BASE_ADDR		0x0500
#घोषणा G2D_MSK_BASE_ADDR		0x0520

/* G2D_SOFT_RESET */
#घोषणा G2D_SFRCLEAR			(1 << 1)
#घोषणा G2D_R				(1 << 0)

/* G2D_INTEN */
#घोषणा G2D_INTEN_ACF			(1 << 3)
#घोषणा G2D_INTEN_UCF			(1 << 2)
#घोषणा G2D_INTEN_GCF			(1 << 1)
#घोषणा G2D_INTEN_SCF			(1 << 0)

/* G2D_INTC_PEND */
#घोषणा G2D_INTP_ACMD_FIN		(1 << 3)
#घोषणा G2D_INTP_UCMD_FIN		(1 << 2)
#घोषणा G2D_INTP_GCMD_FIN		(1 << 1)
#घोषणा G2D_INTP_SCMD_FIN		(1 << 0)

/* G2D_DMA_COMMAND */
#घोषणा G2D_DMA_HALT			(1 << 2)
#घोषणा G2D_DMA_CONTINUE		(1 << 1)
#घोषणा G2D_DMA_START			(1 << 0)

/* G2D_DMA_STATUS */
#घोषणा G2D_DMA_LIST_DONE_COUNT		(0xFF << 17)
#घोषणा G2D_DMA_BITBLT_DONE_COUNT	(0xFFFF << 1)
#घोषणा G2D_DMA_DONE			(1 << 0)
#घोषणा G2D_DMA_LIST_DONE_COUNT_OFFSET	17

/* G2D_DMA_HOLD_CMD */
#घोषणा G2D_USER_HOLD			(1 << 2)
#घोषणा G2D_LIST_HOLD			(1 << 1)
#घोषणा G2D_BITBLT_HOLD			(1 << 0)

/* G2D_BITBLT_START */
#घोषणा G2D_START_CASESEL		(1 << 2)
#घोषणा G2D_START_NHOLT			(1 << 1)
#घोषणा G2D_START_BITBLT		(1 << 0)

/* buffer color क्रमmat */
#घोषणा G2D_FMT_XRGB8888		0
#घोषणा G2D_FMT_ARGB8888		1
#घोषणा G2D_FMT_RGB565			2
#घोषणा G2D_FMT_XRGB1555		3
#घोषणा G2D_FMT_ARGB1555		4
#घोषणा G2D_FMT_XRGB4444		5
#घोषणा G2D_FMT_ARGB4444		6
#घोषणा G2D_FMT_PACKED_RGB888		7
#घोषणा G2D_FMT_A8			11
#घोषणा G2D_FMT_L8			12

/* buffer valid length */
#घोषणा G2D_LEN_MIN			1
#घोषणा G2D_LEN_MAX			8000

#घोषणा G2D_CMDLIST_SIZE		(PAGE_SIZE / 4)
#घोषणा G2D_CMDLIST_NUM			64
#घोषणा G2D_CMDLIST_POOL_SIZE		(G2D_CMDLIST_SIZE * G2D_CMDLIST_NUM)
#घोषणा G2D_CMDLIST_DATA_NUM		(G2D_CMDLIST_SIZE / माप(u32) - 2)

/* maximum buffer pool size of userptr is 64MB as शेष */
#घोषणा MAX_POOL		(64 * 1024 * 1024)

क्रमागत अणु
	BUF_TYPE_GEM = 1,
	BUF_TYPE_USERPTR,
पूर्ण;

क्रमागत g2d_reg_type अणु
	REG_TYPE_NONE = -1,
	REG_TYPE_SRC,
	REG_TYPE_SRC_PLANE2,
	REG_TYPE_DST,
	REG_TYPE_DST_PLANE2,
	REG_TYPE_PAT,
	REG_TYPE_MSK,
	MAX_REG_TYPE_NR
पूर्ण;

क्रमागत g2d_flag_bits अणु
	/*
	 * If set, suspends the runqueue worker after the currently
	 * processed node is finished.
	 */
	G2D_BIT_SUSPEND_RUNQUEUE,
	/*
	 * If set, indicates that the engine is currently busy.
	 */
	G2D_BIT_ENGINE_BUSY,
पूर्ण;

/* cmdlist data काष्ठाure */
काष्ठा g2d_cmdlist अणु
	u32		head;
	अचिन्हित दीर्घ	data[G2D_CMDLIST_DATA_NUM];
	u32		last;	/* last data offset */
पूर्ण;

/*
 * A काष्ठाure of buffer description
 *
 * @क्रमmat: color क्रमmat
 * @stride: buffer stride/pitch in bytes
 * @left_x: the x coordinates of left top corner
 * @top_y: the y coordinates of left top corner
 * @right_x: the x coordinates of right bottom corner
 * @bottom_y: the y coordinates of right bottom corner
 *
 */
काष्ठा g2d_buf_desc अणु
	अचिन्हित पूर्णांक	क्रमmat;
	अचिन्हित पूर्णांक	stride;
	अचिन्हित पूर्णांक	left_x;
	अचिन्हित पूर्णांक	top_y;
	अचिन्हित पूर्णांक	right_x;
	अचिन्हित पूर्णांक	bottom_y;
पूर्ण;

/*
 * A काष्ठाure of buffer inक्रमmation
 *
 * @map_nr: manages the number of mapped buffers
 * @reg_types: stores regitster type in the order of requested command
 * @handles: stores buffer handle in its reg_type position
 * @types: stores buffer type in its reg_type position
 * @descs: stores buffer description in its reg_type position
 *
 */
काष्ठा g2d_buf_info अणु
	अचिन्हित पूर्णांक		map_nr;
	क्रमागत g2d_reg_type	reg_types[MAX_REG_TYPE_NR];
	व्योम			*obj[MAX_REG_TYPE_NR];
	अचिन्हित पूर्णांक		types[MAX_REG_TYPE_NR];
	काष्ठा g2d_buf_desc	descs[MAX_REG_TYPE_NR];
पूर्ण;

काष्ठा drm_exynos_pending_g2d_event अणु
	काष्ठा drm_pending_event	base;
	काष्ठा drm_exynos_g2d_event	event;
पूर्ण;

काष्ठा g2d_cmdlist_userptr अणु
	काष्ठा list_head	list;
	dma_addr_t		dma_addr;
	अचिन्हित दीर्घ		userptr;
	अचिन्हित दीर्घ		size;
	काष्ठा page		**pages;
	अचिन्हित पूर्णांक		npages;
	काष्ठा sg_table		*sgt;
	atomic_t		refcount;
	bool			in_pool;
	bool			out_of_list;
पूर्ण;
काष्ठा g2d_cmdlist_node अणु
	काष्ठा list_head	list;
	काष्ठा g2d_cmdlist	*cmdlist;
	dma_addr_t		dma_addr;
	काष्ठा g2d_buf_info	buf_info;

	काष्ठा drm_exynos_pending_g2d_event	*event;
पूर्ण;

काष्ठा g2d_runqueue_node अणु
	काष्ठा list_head	list;
	काष्ठा list_head	run_cmdlist;
	काष्ठा list_head	event_list;
	काष्ठा drm_file		*filp;
	pid_t			pid;
	काष्ठा completion	complete;
	पूर्णांक			async;
पूर्ण;

काष्ठा g2d_data अणु
	काष्ठा device			*dev;
	व्योम				*dma_priv;
	काष्ठा clk			*gate_clk;
	व्योम __iomem			*regs;
	पूर्णांक				irq;
	काष्ठा workqueue_काष्ठा		*g2d_workq;
	काष्ठा work_काष्ठा		runqueue_work;
	काष्ठा drm_device		*drm_dev;
	अचिन्हित दीर्घ			flags;

	/* cmdlist */
	काष्ठा g2d_cmdlist_node		*cmdlist_node;
	काष्ठा list_head		मुक्त_cmdlist;
	काष्ठा mutex			cmdlist_mutex;
	dma_addr_t			cmdlist_pool;
	व्योम				*cmdlist_pool_virt;
	अचिन्हित दीर्घ			cmdlist_dma_attrs;

	/* runqueue*/
	काष्ठा g2d_runqueue_node	*runqueue_node;
	काष्ठा list_head		runqueue;
	काष्ठा mutex			runqueue_mutex;
	काष्ठा kmem_cache		*runqueue_slab;

	अचिन्हित दीर्घ			current_pool;
	अचिन्हित दीर्घ			max_pool;
पूर्ण;

अटल अंतरभूत व्योम g2d_hw_reset(काष्ठा g2d_data *g2d)
अणु
	ग_लिखोl(G2D_R | G2D_SFRCLEAR, g2d->regs + G2D_SOFT_RESET);
	clear_bit(G2D_BIT_ENGINE_BUSY, &g2d->flags);
पूर्ण

अटल पूर्णांक g2d_init_cmdlist(काष्ठा g2d_data *g2d)
अणु
	काष्ठा device *dev = g2d->dev;
	काष्ठा g2d_cmdlist_node *node;
	पूर्णांक nr;
	पूर्णांक ret;
	काष्ठा g2d_buf_info *buf_info;

	g2d->cmdlist_dma_attrs = DMA_ATTR_WRITE_COMBINE;

	g2d->cmdlist_pool_virt = dma_alloc_attrs(to_dma_dev(g2d->drm_dev),
						G2D_CMDLIST_POOL_SIZE,
						&g2d->cmdlist_pool, GFP_KERNEL,
						g2d->cmdlist_dma_attrs);
	अगर (!g2d->cmdlist_pool_virt) अणु
		dev_err(dev, "failed to allocate dma memory\n");
		वापस -ENOMEM;
	पूर्ण

	node = kसुस्मृति(G2D_CMDLIST_NUM, माप(*node), GFP_KERNEL);
	अगर (!node) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (nr = 0; nr < G2D_CMDLIST_NUM; nr++) अणु
		अचिन्हित पूर्णांक i;

		node[nr].cmdlist =
			g2d->cmdlist_pool_virt + nr * G2D_CMDLIST_SIZE;
		node[nr].dma_addr =
			g2d->cmdlist_pool + nr * G2D_CMDLIST_SIZE;

		buf_info = &node[nr].buf_info;
		क्रम (i = 0; i < MAX_REG_TYPE_NR; i++)
			buf_info->reg_types[i] = REG_TYPE_NONE;

		list_add_tail(&node[nr].list, &g2d->मुक्त_cmdlist);
	पूर्ण

	वापस 0;

err:
	dma_मुक्त_attrs(to_dma_dev(g2d->drm_dev), G2D_CMDLIST_POOL_SIZE,
			g2d->cmdlist_pool_virt,
			g2d->cmdlist_pool, g2d->cmdlist_dma_attrs);
	वापस ret;
पूर्ण

अटल व्योम g2d_fini_cmdlist(काष्ठा g2d_data *g2d)
अणु
	kमुक्त(g2d->cmdlist_node);

	अगर (g2d->cmdlist_pool_virt && g2d->cmdlist_pool) अणु
		dma_मुक्त_attrs(to_dma_dev(g2d->drm_dev),
				G2D_CMDLIST_POOL_SIZE,
				g2d->cmdlist_pool_virt,
				g2d->cmdlist_pool, g2d->cmdlist_dma_attrs);
	पूर्ण
पूर्ण

अटल काष्ठा g2d_cmdlist_node *g2d_get_cmdlist(काष्ठा g2d_data *g2d)
अणु
	काष्ठा device *dev = g2d->dev;
	काष्ठा g2d_cmdlist_node *node;

	mutex_lock(&g2d->cmdlist_mutex);
	अगर (list_empty(&g2d->मुक्त_cmdlist)) अणु
		dev_err(dev, "there is no free cmdlist\n");
		mutex_unlock(&g2d->cmdlist_mutex);
		वापस शून्य;
	पूर्ण

	node = list_first_entry(&g2d->मुक्त_cmdlist, काष्ठा g2d_cmdlist_node,
				list);
	list_del_init(&node->list);
	mutex_unlock(&g2d->cmdlist_mutex);

	वापस node;
पूर्ण

अटल व्योम g2d_put_cmdlist(काष्ठा g2d_data *g2d, काष्ठा g2d_cmdlist_node *node)
अणु
	mutex_lock(&g2d->cmdlist_mutex);
	list_move_tail(&node->list, &g2d->मुक्त_cmdlist);
	mutex_unlock(&g2d->cmdlist_mutex);
पूर्ण

अटल व्योम g2d_add_cmdlist_to_inuse(काष्ठा drm_exynos_file_निजी *file_priv,
				     काष्ठा g2d_cmdlist_node *node)
अणु
	काष्ठा g2d_cmdlist_node *lnode;

	अगर (list_empty(&file_priv->inuse_cmdlist))
		जाओ add_to_list;

	/* this links to base address of new cmdlist */
	lnode = list_entry(file_priv->inuse_cmdlist.prev,
				काष्ठा g2d_cmdlist_node, list);
	lnode->cmdlist->data[lnode->cmdlist->last] = node->dma_addr;

add_to_list:
	list_add_tail(&node->list, &file_priv->inuse_cmdlist);

	अगर (node->event)
		list_add_tail(&node->event->base.link, &file_priv->event_list);
पूर्ण

अटल व्योम g2d_userptr_put_dma_addr(काष्ठा g2d_data *g2d,
					व्योम *obj,
					bool क्रमce)
अणु
	काष्ठा g2d_cmdlist_userptr *g2d_userptr = obj;

	अगर (!obj)
		वापस;

	अगर (क्रमce)
		जाओ out;

	atomic_dec(&g2d_userptr->refcount);

	अगर (atomic_पढ़ो(&g2d_userptr->refcount) > 0)
		वापस;

	अगर (g2d_userptr->in_pool)
		वापस;

out:
	dma_unmap_sgtable(to_dma_dev(g2d->drm_dev), g2d_userptr->sgt,
			  DMA_BIसूचीECTIONAL, 0);

	unpin_user_pages_dirty_lock(g2d_userptr->pages, g2d_userptr->npages,
				    true);
	kvमुक्त(g2d_userptr->pages);

	अगर (!g2d_userptr->out_of_list)
		list_del_init(&g2d_userptr->list);

	sg_मुक्त_table(g2d_userptr->sgt);
	kमुक्त(g2d_userptr->sgt);
	kमुक्त(g2d_userptr);
पूर्ण

अटल dma_addr_t *g2d_userptr_get_dma_addr(काष्ठा g2d_data *g2d,
					अचिन्हित दीर्घ userptr,
					अचिन्हित दीर्घ size,
					काष्ठा drm_file *filp,
					व्योम **obj)
अणु
	काष्ठा drm_exynos_file_निजी *file_priv = filp->driver_priv;
	काष्ठा g2d_cmdlist_userptr *g2d_userptr;
	काष्ठा sg_table	*sgt;
	अचिन्हित दीर्घ start, end;
	अचिन्हित पूर्णांक npages, offset;
	पूर्णांक ret;

	अगर (!size) अणु
		DRM_DEV_ERROR(g2d->dev, "invalid userptr size.\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* check अगर userptr alपढ़ोy exists in userptr_list. */
	list_क्रम_each_entry(g2d_userptr, &file_priv->userptr_list, list) अणु
		अगर (g2d_userptr->userptr == userptr) अणु
			/*
			 * also check size because there could be same address
			 * and dअगरferent size.
			 */
			अगर (g2d_userptr->size == size) अणु
				atomic_inc(&g2d_userptr->refcount);
				*obj = g2d_userptr;

				वापस &g2d_userptr->dma_addr;
			पूर्ण

			/*
			 * at this moment, maybe g2d dma is accessing this
			 * g2d_userptr memory region so just हटाओ this
			 * g2d_userptr object from userptr_list not to be
			 * referred again and also except it the userptr
			 * pool to be released after the dma access completion.
			 */
			g2d_userptr->out_of_list = true;
			g2d_userptr->in_pool = false;
			list_del_init(&g2d_userptr->list);

			अवरोध;
		पूर्ण
	पूर्ण

	g2d_userptr = kzalloc(माप(*g2d_userptr), GFP_KERNEL);
	अगर (!g2d_userptr)
		वापस ERR_PTR(-ENOMEM);

	atomic_set(&g2d_userptr->refcount, 1);
	g2d_userptr->size = size;

	start = userptr & PAGE_MASK;
	offset = userptr & ~PAGE_MASK;
	end = PAGE_ALIGN(userptr + size);
	npages = (end - start) >> PAGE_SHIFT;
	g2d_userptr->pages = kvदो_स्मृति_array(npages, माप(*g2d_userptr->pages),
					    GFP_KERNEL);
	अगर (!g2d_userptr->pages) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	ret = pin_user_pages_fast(start, npages,
				  FOLL_FORCE | FOLL_WRITE | FOLL_LONGTERM,
				  g2d_userptr->pages);
	अगर (ret != npages) अणु
		DRM_DEV_ERROR(g2d->dev,
			      "failed to get user pages from userptr.\n");
		अगर (ret < 0)
			जाओ err_destroy_pages;
		npages = ret;
		ret = -EFAULT;
		जाओ err_unpin_pages;
	पूर्ण
	g2d_userptr->npages = npages;

	sgt = kzalloc(माप(*sgt), GFP_KERNEL);
	अगर (!sgt) अणु
		ret = -ENOMEM;
		जाओ err_unpin_pages;
	पूर्ण

	ret = sg_alloc_table_from_pages(sgt,
					g2d_userptr->pages,
					npages, offset, size, GFP_KERNEL);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(g2d->dev, "failed to get sgt from pages.\n");
		जाओ err_मुक्त_sgt;
	पूर्ण

	g2d_userptr->sgt = sgt;

	ret = dma_map_sgtable(to_dma_dev(g2d->drm_dev), sgt,
			      DMA_BIसूचीECTIONAL, 0);
	अगर (ret) अणु
		DRM_DEV_ERROR(g2d->dev, "failed to map sgt with dma region.\n");
		जाओ err_sg_मुक्त_table;
	पूर्ण

	g2d_userptr->dma_addr = sgt->sgl[0].dma_address;
	g2d_userptr->userptr = userptr;

	list_add_tail(&g2d_userptr->list, &file_priv->userptr_list);

	अगर (g2d->current_pool + (npages << PAGE_SHIFT) < g2d->max_pool) अणु
		g2d->current_pool += npages << PAGE_SHIFT;
		g2d_userptr->in_pool = true;
	पूर्ण

	*obj = g2d_userptr;

	वापस &g2d_userptr->dma_addr;

err_sg_मुक्त_table:
	sg_मुक्त_table(sgt);

err_मुक्त_sgt:
	kमुक्त(sgt);

err_unpin_pages:
	unpin_user_pages(g2d_userptr->pages, npages);

err_destroy_pages:
	kvमुक्त(g2d_userptr->pages);

err_मुक्त:
	kमुक्त(g2d_userptr);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम g2d_userptr_मुक्त_all(काष्ठा g2d_data *g2d, काष्ठा drm_file *filp)
अणु
	काष्ठा drm_exynos_file_निजी *file_priv = filp->driver_priv;
	काष्ठा g2d_cmdlist_userptr *g2d_userptr, *n;

	list_क्रम_each_entry_safe(g2d_userptr, n, &file_priv->userptr_list, list)
		अगर (g2d_userptr->in_pool)
			g2d_userptr_put_dma_addr(g2d, g2d_userptr, true);

	g2d->current_pool = 0;
पूर्ण

अटल क्रमागत g2d_reg_type g2d_get_reg_type(काष्ठा g2d_data *g2d, पूर्णांक reg_offset)
अणु
	क्रमागत g2d_reg_type reg_type;

	चयन (reg_offset) अणु
	हाल G2D_SRC_BASE_ADDR:
	हाल G2D_SRC_STRIDE:
	हाल G2D_SRC_COLOR_MODE:
	हाल G2D_SRC_LEFT_TOP:
	हाल G2D_SRC_RIGHT_BOTTOM:
		reg_type = REG_TYPE_SRC;
		अवरोध;
	हाल G2D_SRC_PLANE2_BASE_ADDR:
		reg_type = REG_TYPE_SRC_PLANE2;
		अवरोध;
	हाल G2D_DST_BASE_ADDR:
	हाल G2D_DST_STRIDE:
	हाल G2D_DST_COLOR_MODE:
	हाल G2D_DST_LEFT_TOP:
	हाल G2D_DST_RIGHT_BOTTOM:
		reg_type = REG_TYPE_DST;
		अवरोध;
	हाल G2D_DST_PLANE2_BASE_ADDR:
		reg_type = REG_TYPE_DST_PLANE2;
		अवरोध;
	हाल G2D_PAT_BASE_ADDR:
		reg_type = REG_TYPE_PAT;
		अवरोध;
	हाल G2D_MSK_BASE_ADDR:
		reg_type = REG_TYPE_MSK;
		अवरोध;
	शेष:
		reg_type = REG_TYPE_NONE;
		DRM_DEV_ERROR(g2d->dev, "Unknown register offset![%d]\n",
			      reg_offset);
		अवरोध;
	पूर्ण

	वापस reg_type;
पूर्ण

अटल अचिन्हित दीर्घ g2d_get_buf_bpp(अचिन्हित पूर्णांक क्रमmat)
अणु
	अचिन्हित दीर्घ bpp;

	चयन (क्रमmat) अणु
	हाल G2D_FMT_XRGB8888:
	हाल G2D_FMT_ARGB8888:
		bpp = 4;
		अवरोध;
	हाल G2D_FMT_RGB565:
	हाल G2D_FMT_XRGB1555:
	हाल G2D_FMT_ARGB1555:
	हाल G2D_FMT_XRGB4444:
	हाल G2D_FMT_ARGB4444:
		bpp = 2;
		अवरोध;
	हाल G2D_FMT_PACKED_RGB888:
		bpp = 3;
		अवरोध;
	शेष:
		bpp = 1;
		अवरोध;
	पूर्ण

	वापस bpp;
पूर्ण

अटल bool g2d_check_buf_desc_is_valid(काष्ठा g2d_data *g2d,
					काष्ठा g2d_buf_desc *buf_desc,
					क्रमागत g2d_reg_type reg_type,
					अचिन्हित दीर्घ size)
अणु
	पूर्णांक width, height;
	अचिन्हित दीर्घ bpp, last_pos;

	/*
	 * check source and destination buffers only.
	 * so the others are always valid.
	 */
	अगर (reg_type != REG_TYPE_SRC && reg_type != REG_TYPE_DST)
		वापस true;

	/* This check also makes sure that right_x > left_x. */
	width = (पूर्णांक)buf_desc->right_x - (पूर्णांक)buf_desc->left_x;
	अगर (width < G2D_LEN_MIN || width > G2D_LEN_MAX) अणु
		DRM_DEV_ERROR(g2d->dev, "width[%d] is out of range!\n", width);
		वापस false;
	पूर्ण

	/* This check also makes sure that bottom_y > top_y. */
	height = (पूर्णांक)buf_desc->bottom_y - (पूर्णांक)buf_desc->top_y;
	अगर (height < G2D_LEN_MIN || height > G2D_LEN_MAX) अणु
		DRM_DEV_ERROR(g2d->dev,
			      "height[%d] is out of range!\n", height);
		वापस false;
	पूर्ण

	bpp = g2d_get_buf_bpp(buf_desc->क्रमmat);

	/* Compute the position of the last byte that the engine accesses. */
	last_pos = ((अचिन्हित दीर्घ)buf_desc->bottom_y - 1) *
		(अचिन्हित दीर्घ)buf_desc->stride +
		(अचिन्हित दीर्घ)buf_desc->right_x * bpp - 1;

	/*
	 * Since right_x > left_x and bottom_y > top_y we alपढ़ोy know
	 * that the first_pos < last_pos (first_pos being the position
	 * of the first byte the engine accesses), it just reमुख्यs to
	 * check अगर last_pos is smaller then the buffer size.
	 */

	अगर (last_pos >= size) अणु
		DRM_DEV_ERROR(g2d->dev, "last engine access position [%lu] "
			      "is out of range [%lu]!\n", last_pos, size);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक g2d_map_cmdlist_gem(काष्ठा g2d_data *g2d,
				काष्ठा g2d_cmdlist_node *node,
				काष्ठा drm_device *drm_dev,
				काष्ठा drm_file *file)
अणु
	काष्ठा g2d_cmdlist *cmdlist = node->cmdlist;
	काष्ठा g2d_buf_info *buf_info = &node->buf_info;
	पूर्णांक offset;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < buf_info->map_nr; i++) अणु
		काष्ठा g2d_buf_desc *buf_desc;
		क्रमागत g2d_reg_type reg_type;
		पूर्णांक reg_pos;
		अचिन्हित दीर्घ handle;
		dma_addr_t *addr;

		reg_pos = cmdlist->last - 2 * (i + 1);

		offset = cmdlist->data[reg_pos];
		handle = cmdlist->data[reg_pos + 1];

		reg_type = g2d_get_reg_type(g2d, offset);
		अगर (reg_type == REG_TYPE_NONE) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		buf_desc = &buf_info->descs[reg_type];

		अगर (buf_info->types[reg_type] == BUF_TYPE_GEM) अणु
			काष्ठा exynos_drm_gem *exynos_gem;

			exynos_gem = exynos_drm_gem_get(file, handle);
			अगर (!exynos_gem) अणु
				ret = -EFAULT;
				जाओ err;
			पूर्ण

			अगर (!g2d_check_buf_desc_is_valid(g2d, buf_desc,
							 reg_type, exynos_gem->size)) अणु
				exynos_drm_gem_put(exynos_gem);
				ret = -EFAULT;
				जाओ err;
			पूर्ण

			addr = &exynos_gem->dma_addr;
			buf_info->obj[reg_type] = exynos_gem;
		पूर्ण अन्यथा अणु
			काष्ठा drm_exynos_g2d_userptr g2d_userptr;

			अगर (copy_from_user(&g2d_userptr, (व्योम __user *)handle,
				माप(काष्ठा drm_exynos_g2d_userptr))) अणु
				ret = -EFAULT;
				जाओ err;
			पूर्ण

			अगर (!g2d_check_buf_desc_is_valid(g2d, buf_desc,
							 reg_type,
							 g2d_userptr.size)) अणु
				ret = -EFAULT;
				जाओ err;
			पूर्ण

			addr = g2d_userptr_get_dma_addr(g2d,
							g2d_userptr.userptr,
							g2d_userptr.size,
							file,
							&buf_info->obj[reg_type]);
			अगर (IS_ERR(addr)) अणु
				ret = -EFAULT;
				जाओ err;
			पूर्ण
		पूर्ण

		cmdlist->data[reg_pos + 1] = *addr;
		buf_info->reg_types[i] = reg_type;
	पूर्ण

	वापस 0;

err:
	buf_info->map_nr = i;
	वापस ret;
पूर्ण

अटल व्योम g2d_unmap_cmdlist_gem(काष्ठा g2d_data *g2d,
				  काष्ठा g2d_cmdlist_node *node,
				  काष्ठा drm_file *filp)
अणु
	काष्ठा g2d_buf_info *buf_info = &node->buf_info;
	पूर्णांक i;

	क्रम (i = 0; i < buf_info->map_nr; i++) अणु
		काष्ठा g2d_buf_desc *buf_desc;
		क्रमागत g2d_reg_type reg_type;
		व्योम *obj;

		reg_type = buf_info->reg_types[i];

		buf_desc = &buf_info->descs[reg_type];
		obj = buf_info->obj[reg_type];

		अगर (buf_info->types[reg_type] == BUF_TYPE_GEM)
			exynos_drm_gem_put(obj);
		अन्यथा
			g2d_userptr_put_dma_addr(g2d, obj, false);

		buf_info->reg_types[i] = REG_TYPE_NONE;
		buf_info->obj[reg_type] = शून्य;
		buf_info->types[reg_type] = 0;
		स_रखो(buf_desc, 0x00, माप(*buf_desc));
	पूर्ण

	buf_info->map_nr = 0;
पूर्ण

अटल व्योम g2d_dma_start(काष्ठा g2d_data *g2d,
			  काष्ठा g2d_runqueue_node *runqueue_node)
अणु
	काष्ठा g2d_cmdlist_node *node =
				list_first_entry(&runqueue_node->run_cmdlist,
						काष्ठा g2d_cmdlist_node, list);

	set_bit(G2D_BIT_ENGINE_BUSY, &g2d->flags);
	ग_लिखोl_relaxed(node->dma_addr, g2d->regs + G2D_DMA_SFR_BASE_ADDR);
	ग_लिखोl_relaxed(G2D_DMA_START, g2d->regs + G2D_DMA_COMMAND);
पूर्ण

अटल काष्ठा g2d_runqueue_node *g2d_get_runqueue_node(काष्ठा g2d_data *g2d)
अणु
	काष्ठा g2d_runqueue_node *runqueue_node;

	अगर (list_empty(&g2d->runqueue))
		वापस शून्य;

	runqueue_node = list_first_entry(&g2d->runqueue,
					 काष्ठा g2d_runqueue_node, list);
	list_del_init(&runqueue_node->list);
	वापस runqueue_node;
पूर्ण

अटल व्योम g2d_मुक्त_runqueue_node(काष्ठा g2d_data *g2d,
				   काष्ठा g2d_runqueue_node *runqueue_node)
अणु
	काष्ठा g2d_cmdlist_node *node;

	mutex_lock(&g2d->cmdlist_mutex);
	/*
	 * commands in run_cmdlist have been completed so unmap all gem
	 * objects in each command node so that they are unreferenced.
	 */
	list_क्रम_each_entry(node, &runqueue_node->run_cmdlist, list)
		g2d_unmap_cmdlist_gem(g2d, node, runqueue_node->filp);
	list_splice_tail_init(&runqueue_node->run_cmdlist, &g2d->मुक्त_cmdlist);
	mutex_unlock(&g2d->cmdlist_mutex);

	kmem_cache_मुक्त(g2d->runqueue_slab, runqueue_node);
पूर्ण

/**
 * g2d_हटाओ_runqueue_nodes - हटाओ items from the list of runqueue nodes
 * @g2d: G2D state object
 * @file: अगर not zero, only हटाओ items with this DRM file
 *
 * Has to be called under runqueue lock.
 */
अटल व्योम g2d_हटाओ_runqueue_nodes(काष्ठा g2d_data *g2d, काष्ठा drm_file *file)
अणु
	काष्ठा g2d_runqueue_node *node, *n;

	अगर (list_empty(&g2d->runqueue))
		वापस;

	list_क्रम_each_entry_safe(node, n, &g2d->runqueue, list) अणु
		अगर (file && node->filp != file)
			जारी;

		list_del_init(&node->list);
		g2d_मुक्त_runqueue_node(g2d, node);
	पूर्ण
पूर्ण

अटल व्योम g2d_runqueue_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा g2d_data *g2d = container_of(work, काष्ठा g2d_data,
					    runqueue_work);
	काष्ठा g2d_runqueue_node *runqueue_node;

	/*
	 * The engine is busy and the completion of the current node is going
	 * to poke the runqueue worker, so nothing to करो here.
	 */
	अगर (test_bit(G2D_BIT_ENGINE_BUSY, &g2d->flags))
		वापस;

	mutex_lock(&g2d->runqueue_mutex);

	runqueue_node = g2d->runqueue_node;
	g2d->runqueue_node = शून्य;

	अगर (runqueue_node) अणु
		pm_runसमय_mark_last_busy(g2d->dev);
		pm_runसमय_put_स्वतःsuspend(g2d->dev);

		complete(&runqueue_node->complete);
		अगर (runqueue_node->async)
			g2d_मुक्त_runqueue_node(g2d, runqueue_node);
	पूर्ण

	अगर (!test_bit(G2D_BIT_SUSPEND_RUNQUEUE, &g2d->flags)) अणु
		g2d->runqueue_node = g2d_get_runqueue_node(g2d);

		अगर (g2d->runqueue_node) अणु
			pm_runसमय_get_sync(g2d->dev);
			g2d_dma_start(g2d, g2d->runqueue_node);
		पूर्ण
	पूर्ण

	mutex_unlock(&g2d->runqueue_mutex);
पूर्ण

अटल व्योम g2d_finish_event(काष्ठा g2d_data *g2d, u32 cmdlist_no)
अणु
	काष्ठा drm_device *drm_dev = g2d->drm_dev;
	काष्ठा g2d_runqueue_node *runqueue_node = g2d->runqueue_node;
	काष्ठा drm_exynos_pending_g2d_event *e;
	काष्ठा बारpec64 now;

	अगर (list_empty(&runqueue_node->event_list))
		वापस;

	e = list_first_entry(&runqueue_node->event_list,
			     काष्ठा drm_exynos_pending_g2d_event, base.link);

	kसमय_get_ts64(&now);
	e->event.tv_sec = now.tv_sec;
	e->event.tv_usec = now.tv_nsec / NSEC_PER_USEC;
	e->event.cmdlist_no = cmdlist_no;

	drm_send_event(drm_dev, &e->base);
पूर्ण

अटल irqवापस_t g2d_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा g2d_data *g2d = dev_id;
	u32 pending;

	pending = पढ़ोl_relaxed(g2d->regs + G2D_INTC_PEND);
	अगर (pending)
		ग_लिखोl_relaxed(pending, g2d->regs + G2D_INTC_PEND);

	अगर (pending & G2D_INTP_GCMD_FIN) अणु
		u32 cmdlist_no = पढ़ोl_relaxed(g2d->regs + G2D_DMA_STATUS);

		cmdlist_no = (cmdlist_no & G2D_DMA_LIST_DONE_COUNT) >>
						G2D_DMA_LIST_DONE_COUNT_OFFSET;

		g2d_finish_event(g2d, cmdlist_no);

		ग_लिखोl_relaxed(0, g2d->regs + G2D_DMA_HOLD_CMD);
		अगर (!(pending & G2D_INTP_ACMD_FIN)) अणु
			ग_लिखोl_relaxed(G2D_DMA_CONTINUE,
					g2d->regs + G2D_DMA_COMMAND);
		पूर्ण
	पूर्ण

	अगर (pending & G2D_INTP_ACMD_FIN) अणु
		clear_bit(G2D_BIT_ENGINE_BUSY, &g2d->flags);
		queue_work(g2d->g2d_workq, &g2d->runqueue_work);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * g2d_रुको_finish - रुको क्रम the G2D engine to finish the current runqueue node
 * @g2d: G2D state object
 * @file: अगर not zero, only रुको अगर the current runqueue node beदीर्घs
 *        to the DRM file
 *
 * Should the engine not become idle after a 100ms समयout, a hardware
 * reset is issued.
 */
अटल व्योम g2d_रुको_finish(काष्ठा g2d_data *g2d, काष्ठा drm_file *file)
अणु
	काष्ठा device *dev = g2d->dev;

	काष्ठा g2d_runqueue_node *runqueue_node = शून्य;
	अचिन्हित पूर्णांक tries = 10;

	mutex_lock(&g2d->runqueue_mutex);

	/* If no node is currently processed, we have nothing to करो. */
	अगर (!g2d->runqueue_node)
		जाओ out;

	runqueue_node = g2d->runqueue_node;

	/* Check अगर the currently processed item beदीर्घs to us. */
	अगर (file && runqueue_node->filp != file)
		जाओ out;

	mutex_unlock(&g2d->runqueue_mutex);

	/* Wait क्रम the G2D engine to finish. */
	जबतक (tries-- && (g2d->runqueue_node == runqueue_node))
		mdelay(10);

	mutex_lock(&g2d->runqueue_mutex);

	अगर (g2d->runqueue_node != runqueue_node)
		जाओ out;

	dev_err(dev, "wait timed out, resetting engine...\n");
	g2d_hw_reset(g2d);

	/*
	 * After the hardware reset of the engine we are going to loose
	 * the IRQ which triggers the PM runसमय put().
	 * So करो this manually here.
	 */
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	complete(&runqueue_node->complete);
	अगर (runqueue_node->async)
		g2d_मुक्त_runqueue_node(g2d, runqueue_node);

out:
	mutex_unlock(&g2d->runqueue_mutex);
पूर्ण

अटल पूर्णांक g2d_check_reg_offset(काष्ठा g2d_data *g2d,
				काष्ठा g2d_cmdlist_node *node,
				पूर्णांक nr, bool क्रम_addr)
अणु
	काष्ठा g2d_cmdlist *cmdlist = node->cmdlist;
	पूर्णांक reg_offset;
	पूर्णांक index;
	पूर्णांक i;

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा g2d_buf_info *buf_info = &node->buf_info;
		काष्ठा g2d_buf_desc *buf_desc;
		क्रमागत g2d_reg_type reg_type;
		अचिन्हित दीर्घ value;

		index = cmdlist->last - 2 * (i + 1);

		reg_offset = cmdlist->data[index] & ~0xfffff000;
		अगर (reg_offset < G2D_VALID_START || reg_offset > G2D_VALID_END)
			जाओ err;
		अगर (reg_offset % 4)
			जाओ err;

		चयन (reg_offset) अणु
		हाल G2D_SRC_BASE_ADDR:
		हाल G2D_SRC_PLANE2_BASE_ADDR:
		हाल G2D_DST_BASE_ADDR:
		हाल G2D_DST_PLANE2_BASE_ADDR:
		हाल G2D_PAT_BASE_ADDR:
		हाल G2D_MSK_BASE_ADDR:
			अगर (!क्रम_addr)
				जाओ err;

			reg_type = g2d_get_reg_type(g2d, reg_offset);

			/* check userptr buffer type. */
			अगर ((cmdlist->data[index] & ~0x7fffffff) >> 31) अणु
				buf_info->types[reg_type] = BUF_TYPE_USERPTR;
				cmdlist->data[index] &= ~G2D_BUF_USERPTR;
			पूर्ण अन्यथा
				buf_info->types[reg_type] = BUF_TYPE_GEM;
			अवरोध;
		हाल G2D_SRC_STRIDE:
		हाल G2D_DST_STRIDE:
			अगर (क्रम_addr)
				जाओ err;

			reg_type = g2d_get_reg_type(g2d, reg_offset);

			buf_desc = &buf_info->descs[reg_type];
			buf_desc->stride = cmdlist->data[index + 1];
			अवरोध;
		हाल G2D_SRC_COLOR_MODE:
		हाल G2D_DST_COLOR_MODE:
			अगर (क्रम_addr)
				जाओ err;

			reg_type = g2d_get_reg_type(g2d, reg_offset);

			buf_desc = &buf_info->descs[reg_type];
			value = cmdlist->data[index + 1];

			buf_desc->क्रमmat = value & 0xf;
			अवरोध;
		हाल G2D_SRC_LEFT_TOP:
		हाल G2D_DST_LEFT_TOP:
			अगर (क्रम_addr)
				जाओ err;

			reg_type = g2d_get_reg_type(g2d, reg_offset);

			buf_desc = &buf_info->descs[reg_type];
			value = cmdlist->data[index + 1];

			buf_desc->left_x = value & 0x1fff;
			buf_desc->top_y = (value & 0x1fff0000) >> 16;
			अवरोध;
		हाल G2D_SRC_RIGHT_BOTTOM:
		हाल G2D_DST_RIGHT_BOTTOM:
			अगर (क्रम_addr)
				जाओ err;

			reg_type = g2d_get_reg_type(g2d, reg_offset);

			buf_desc = &buf_info->descs[reg_type];
			value = cmdlist->data[index + 1];

			buf_desc->right_x = value & 0x1fff;
			buf_desc->bottom_y = (value & 0x1fff0000) >> 16;
			अवरोध;
		शेष:
			अगर (क्रम_addr)
				जाओ err;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	dev_err(g2d->dev, "Bad register offset: 0x%lx\n", cmdlist->data[index]);
	वापस -EINVAL;
पूर्ण

/* ioctl functions */
पूर्णांक exynos_g2d_get_ver_ioctl(काष्ठा drm_device *drm_dev, व्योम *data,
			     काष्ठा drm_file *file)
अणु
	काष्ठा drm_exynos_g2d_get_ver *ver = data;

	ver->major = G2D_HW_MAJOR_VER;
	ver->minor = G2D_HW_MINOR_VER;

	वापस 0;
पूर्ण

पूर्णांक exynos_g2d_set_cmdlist_ioctl(काष्ठा drm_device *drm_dev, व्योम *data,
				 काष्ठा drm_file *file)
अणु
	काष्ठा drm_exynos_file_निजी *file_priv = file->driver_priv;
	काष्ठा exynos_drm_निजी *priv = drm_dev->dev_निजी;
	काष्ठा g2d_data *g2d = dev_get_drvdata(priv->g2d_dev);
	काष्ठा drm_exynos_g2d_set_cmdlist *req = data;
	काष्ठा drm_exynos_g2d_cmd *cmd;
	काष्ठा drm_exynos_pending_g2d_event *e;
	काष्ठा g2d_cmdlist_node *node;
	काष्ठा g2d_cmdlist *cmdlist;
	पूर्णांक size;
	पूर्णांक ret;

	node = g2d_get_cmdlist(g2d);
	अगर (!node)
		वापस -ENOMEM;

	/*
	 * To aव्योम an पूर्णांकeger overflow क्रम the later size computations, we
	 * enक्रमce a maximum number of submitted commands here. This limit is
	 * sufficient क्रम all conceivable usage हालs of the G2D.
	 */
	अगर (req->cmd_nr > G2D_CMDLIST_DATA_NUM ||
	    req->cmd_buf_nr > G2D_CMDLIST_DATA_NUM) अणु
		dev_err(g2d->dev, "number of submitted G2D commands exceeds limit\n");
		वापस -EINVAL;
	पूर्ण

	node->event = शून्य;

	अगर (req->event_type != G2D_EVENT_NOT) अणु
		e = kzalloc(माप(*node->event), GFP_KERNEL);
		अगर (!e) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		e->event.base.type = DRM_EXYNOS_G2D_EVENT;
		e->event.base.length = माप(e->event);
		e->event.user_data = req->user_data;

		ret = drm_event_reserve_init(drm_dev, file, &e->base, &e->event.base);
		अगर (ret) अणु
			kमुक्त(e);
			जाओ err;
		पूर्ण

		node->event = e;
	पूर्ण

	cmdlist = node->cmdlist;

	cmdlist->last = 0;

	/*
	 * If करोn't clear SFR रेजिस्टरs, the cmdlist is affected by रेजिस्टर
	 * values of previous cmdlist. G2D hw executes SFR clear command and
	 * a next command at the same समय then the next command is ignored and
	 * is executed rightly from next next command, so needs a dummy command
	 * to next command of SFR clear command.
	 */
	cmdlist->data[cmdlist->last++] = G2D_SOFT_RESET;
	cmdlist->data[cmdlist->last++] = G2D_SFRCLEAR;
	cmdlist->data[cmdlist->last++] = G2D_SRC_BASE_ADDR;
	cmdlist->data[cmdlist->last++] = 0;

	/*
	 * 'LIST_HOLD' command should be set to the DMA_HOLD_CMD_REG
	 * and GCF bit should be set to INTEN रेजिस्टर अगर user wants
	 * G2D पूर्णांकerrupt event once current command list execution is
	 * finished.
	 * Otherwise only ACF bit should be set to INTEN रेजिस्टर so
	 * that one पूर्णांकerrupt is occurred after all command lists
	 * have been completed.
	 */
	अगर (node->event) अणु
		cmdlist->data[cmdlist->last++] = G2D_INTEN;
		cmdlist->data[cmdlist->last++] = G2D_INTEN_ACF | G2D_INTEN_GCF;
		cmdlist->data[cmdlist->last++] = G2D_DMA_HOLD_CMD;
		cmdlist->data[cmdlist->last++] = G2D_LIST_HOLD;
	पूर्ण अन्यथा अणु
		cmdlist->data[cmdlist->last++] = G2D_INTEN;
		cmdlist->data[cmdlist->last++] = G2D_INTEN_ACF;
	पूर्ण

	/*
	 * Check the size of cmdlist. The 2 that is added last comes from
	 * the implicit G2D_BITBLT_START that is appended once we have
	 * checked all the submitted commands.
	 */
	size = cmdlist->last + req->cmd_nr * 2 + req->cmd_buf_nr * 2 + 2;
	अगर (size > G2D_CMDLIST_DATA_NUM) अणु
		dev_err(g2d->dev, "cmdlist size is too big\n");
		ret = -EINVAL;
		जाओ err_मुक्त_event;
	पूर्ण

	cmd = (काष्ठा drm_exynos_g2d_cmd *)(अचिन्हित दीर्घ)req->cmd;

	अगर (copy_from_user(cmdlist->data + cmdlist->last,
				(व्योम __user *)cmd,
				माप(*cmd) * req->cmd_nr)) अणु
		ret = -EFAULT;
		जाओ err_मुक्त_event;
	पूर्ण
	cmdlist->last += req->cmd_nr * 2;

	ret = g2d_check_reg_offset(g2d, node, req->cmd_nr, false);
	अगर (ret < 0)
		जाओ err_मुक्त_event;

	node->buf_info.map_nr = req->cmd_buf_nr;
	अगर (req->cmd_buf_nr) अणु
		काष्ठा drm_exynos_g2d_cmd *cmd_buf;

		cmd_buf = (काष्ठा drm_exynos_g2d_cmd *)
				(अचिन्हित दीर्घ)req->cmd_buf;

		अगर (copy_from_user(cmdlist->data + cmdlist->last,
					(व्योम __user *)cmd_buf,
					माप(*cmd_buf) * req->cmd_buf_nr)) अणु
			ret = -EFAULT;
			जाओ err_मुक्त_event;
		पूर्ण
		cmdlist->last += req->cmd_buf_nr * 2;

		ret = g2d_check_reg_offset(g2d, node, req->cmd_buf_nr, true);
		अगर (ret < 0)
			जाओ err_मुक्त_event;

		ret = g2d_map_cmdlist_gem(g2d, node, drm_dev, file);
		अगर (ret < 0)
			जाओ err_unmap;
	पूर्ण

	cmdlist->data[cmdlist->last++] = G2D_BITBLT_START;
	cmdlist->data[cmdlist->last++] = G2D_START_BITBLT;

	/* head */
	cmdlist->head = cmdlist->last / 2;

	/* tail */
	cmdlist->data[cmdlist->last] = 0;

	g2d_add_cmdlist_to_inuse(file_priv, node);

	वापस 0;

err_unmap:
	g2d_unmap_cmdlist_gem(g2d, node, file);
err_मुक्त_event:
	अगर (node->event)
		drm_event_cancel_मुक्त(drm_dev, &node->event->base);
err:
	g2d_put_cmdlist(g2d, node);
	वापस ret;
पूर्ण

पूर्णांक exynos_g2d_exec_ioctl(काष्ठा drm_device *drm_dev, व्योम *data,
			  काष्ठा drm_file *file)
अणु
	काष्ठा drm_exynos_file_निजी *file_priv = file->driver_priv;
	काष्ठा exynos_drm_निजी *priv = drm_dev->dev_निजी;
	काष्ठा g2d_data *g2d = dev_get_drvdata(priv->g2d_dev);
	काष्ठा drm_exynos_g2d_exec *req = data;
	काष्ठा g2d_runqueue_node *runqueue_node;
	काष्ठा list_head *run_cmdlist;
	काष्ठा list_head *event_list;

	runqueue_node = kmem_cache_alloc(g2d->runqueue_slab, GFP_KERNEL);
	अगर (!runqueue_node)
		वापस -ENOMEM;

	run_cmdlist = &runqueue_node->run_cmdlist;
	event_list = &runqueue_node->event_list;
	INIT_LIST_HEAD(run_cmdlist);
	INIT_LIST_HEAD(event_list);
	init_completion(&runqueue_node->complete);
	runqueue_node->async = req->async;

	list_splice_init(&file_priv->inuse_cmdlist, run_cmdlist);
	list_splice_init(&file_priv->event_list, event_list);

	अगर (list_empty(run_cmdlist)) अणु
		dev_err(g2d->dev, "there is no inuse cmdlist\n");
		kmem_cache_मुक्त(g2d->runqueue_slab, runqueue_node);
		वापस -EPERM;
	पूर्ण

	mutex_lock(&g2d->runqueue_mutex);
	runqueue_node->pid = current->pid;
	runqueue_node->filp = file;
	list_add_tail(&runqueue_node->list, &g2d->runqueue);
	mutex_unlock(&g2d->runqueue_mutex);

	/* Let the runqueue know that there is work to करो. */
	queue_work(g2d->g2d_workq, &g2d->runqueue_work);

	अगर (runqueue_node->async)
		जाओ out;

	रुको_क्रम_completion(&runqueue_node->complete);
	g2d_मुक्त_runqueue_node(g2d, runqueue_node);

out:
	वापस 0;
पूर्ण

पूर्णांक g2d_खोलो(काष्ठा drm_device *drm_dev, काष्ठा drm_file *file)
अणु
	काष्ठा drm_exynos_file_निजी *file_priv = file->driver_priv;

	INIT_LIST_HEAD(&file_priv->inuse_cmdlist);
	INIT_LIST_HEAD(&file_priv->event_list);
	INIT_LIST_HEAD(&file_priv->userptr_list);

	वापस 0;
पूर्ण

व्योम g2d_बंद(काष्ठा drm_device *drm_dev, काष्ठा drm_file *file)
अणु
	काष्ठा drm_exynos_file_निजी *file_priv = file->driver_priv;
	काष्ठा exynos_drm_निजी *priv = drm_dev->dev_निजी;
	काष्ठा g2d_data *g2d;
	काष्ठा g2d_cmdlist_node *node, *n;

	अगर (!priv->g2d_dev)
		वापस;

	g2d = dev_get_drvdata(priv->g2d_dev);

	/* Remove the runqueue nodes that beदीर्घ to us. */
	mutex_lock(&g2d->runqueue_mutex);
	g2d_हटाओ_runqueue_nodes(g2d, file);
	mutex_unlock(&g2d->runqueue_mutex);

	/*
	 * Wait क्रम the runqueue worker to finish its current node.
	 * After this the engine should no दीर्घer be accessing any
	 * memory beदीर्घing to us.
	 */
	g2d_रुको_finish(g2d, file);

	/*
	 * Even after the engine is idle, there might still be stale cmdlists
	 * (i.e. cmdlisst which we submitted but never executed) around, with
	 * their corresponding GEM/userptr buffers.
	 * Properly unmap these buffers here.
	 */
	mutex_lock(&g2d->cmdlist_mutex);
	list_क्रम_each_entry_safe(node, n, &file_priv->inuse_cmdlist, list) अणु
		g2d_unmap_cmdlist_gem(g2d, node, file);
		list_move_tail(&node->list, &g2d->मुक्त_cmdlist);
	पूर्ण
	mutex_unlock(&g2d->cmdlist_mutex);

	/* release all g2d_userptr in pool. */
	g2d_userptr_मुक्त_all(g2d, file);
पूर्ण

अटल पूर्णांक g2d_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा g2d_data *g2d = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_निजी *priv = drm_dev->dev_निजी;
	पूर्णांक ret;

	g2d->drm_dev = drm_dev;

	/* allocate dma-aware cmdlist buffer. */
	ret = g2d_init_cmdlist(g2d);
	अगर (ret < 0) अणु
		dev_err(dev, "cmdlist init failed\n");
		वापस ret;
	पूर्ण

	ret = exynos_drm_रेजिस्टर_dma(drm_dev, dev, &g2d->dma_priv);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable iommu.\n");
		g2d_fini_cmdlist(g2d);
		वापस ret;
	पूर्ण
	priv->g2d_dev = dev;

	dev_info(dev, "The Exynos G2D (ver %d.%d) successfully registered.\n",
			G2D_HW_MAJOR_VER, G2D_HW_MINOR_VER);
	वापस 0;
पूर्ण

अटल व्योम g2d_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा g2d_data *g2d = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_निजी *priv = drm_dev->dev_निजी;

	/* Suspend operation and रुको क्रम engine idle. */
	set_bit(G2D_BIT_SUSPEND_RUNQUEUE, &g2d->flags);
	g2d_रुको_finish(g2d, शून्य);
	priv->g2d_dev = शून्य;

	cancel_work_sync(&g2d->runqueue_work);
	exynos_drm_unरेजिस्टर_dma(g2d->drm_dev, dev, &g2d->dma_priv);
पूर्ण

अटल स्थिर काष्ठा component_ops g2d_component_ops = अणु
	.bind	= g2d_bind,
	.unbind = g2d_unbind,
पूर्ण;

अटल पूर्णांक g2d_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा g2d_data *g2d;
	पूर्णांक ret;

	g2d = devm_kzalloc(dev, माप(*g2d), GFP_KERNEL);
	अगर (!g2d)
		वापस -ENOMEM;

	g2d->runqueue_slab = kmem_cache_create("g2d_runqueue_slab",
			माप(काष्ठा g2d_runqueue_node), 0, 0, शून्य);
	अगर (!g2d->runqueue_slab)
		वापस -ENOMEM;

	g2d->dev = dev;

	g2d->g2d_workq = create_singlethपढ़ो_workqueue("g2d");
	अगर (!g2d->g2d_workq) अणु
		dev_err(dev, "failed to create workqueue\n");
		ret = -EINVAL;
		जाओ err_destroy_slab;
	पूर्ण

	INIT_WORK(&g2d->runqueue_work, g2d_runqueue_worker);
	INIT_LIST_HEAD(&g2d->मुक्त_cmdlist);
	INIT_LIST_HEAD(&g2d->runqueue);

	mutex_init(&g2d->cmdlist_mutex);
	mutex_init(&g2d->runqueue_mutex);

	g2d->gate_clk = devm_clk_get(dev, "fimg2d");
	अगर (IS_ERR(g2d->gate_clk)) अणु
		dev_err(dev, "failed to get gate clock\n");
		ret = PTR_ERR(g2d->gate_clk);
		जाओ err_destroy_workqueue;
	पूर्ण

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 2000);
	pm_runसमय_enable(dev);
	clear_bit(G2D_BIT_SUSPEND_RUNQUEUE, &g2d->flags);
	clear_bit(G2D_BIT_ENGINE_BUSY, &g2d->flags);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	g2d->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(g2d->regs)) अणु
		ret = PTR_ERR(g2d->regs);
		जाओ err_put_clk;
	पूर्ण

	g2d->irq = platक्रमm_get_irq(pdev, 0);
	अगर (g2d->irq < 0) अणु
		ret = g2d->irq;
		जाओ err_put_clk;
	पूर्ण

	ret = devm_request_irq(dev, g2d->irq, g2d_irq_handler, 0,
								"drm_g2d", g2d);
	अगर (ret < 0) अणु
		dev_err(dev, "irq request failed\n");
		जाओ err_put_clk;
	पूर्ण

	g2d->max_pool = MAX_POOL;

	platक्रमm_set_drvdata(pdev, g2d);

	ret = component_add(dev, &g2d_component_ops);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register drm g2d device\n");
		जाओ err_put_clk;
	पूर्ण

	वापस 0;

err_put_clk:
	pm_runसमय_disable(dev);
err_destroy_workqueue:
	destroy_workqueue(g2d->g2d_workq);
err_destroy_slab:
	kmem_cache_destroy(g2d->runqueue_slab);
	वापस ret;
पूर्ण

अटल पूर्णांक g2d_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा g2d_data *g2d = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &g2d_component_ops);

	/* There should be no locking needed here. */
	g2d_हटाओ_runqueue_nodes(g2d, शून्य);

	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	g2d_fini_cmdlist(g2d);
	destroy_workqueue(g2d->g2d_workq);
	kmem_cache_destroy(g2d->runqueue_slab);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक g2d_suspend(काष्ठा device *dev)
अणु
	काष्ठा g2d_data *g2d = dev_get_drvdata(dev);

	/*
	 * Suspend the runqueue worker operation and रुको until the G2D
	 * engine is idle.
	 */
	set_bit(G2D_BIT_SUSPEND_RUNQUEUE, &g2d->flags);
	g2d_रुको_finish(g2d, शून्य);
	flush_work(&g2d->runqueue_work);

	वापस 0;
पूर्ण

अटल पूर्णांक g2d_resume(काष्ठा device *dev)
अणु
	काष्ठा g2d_data *g2d = dev_get_drvdata(dev);

	clear_bit(G2D_BIT_SUSPEND_RUNQUEUE, &g2d->flags);
	queue_work(g2d->g2d_workq, &g2d->runqueue_work);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक g2d_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा g2d_data *g2d = dev_get_drvdata(dev);

	clk_disable_unprepare(g2d->gate_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक g2d_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा g2d_data *g2d = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(g2d->gate_clk);
	अगर (ret < 0)
		dev_warn(dev, "failed to enable clock.\n");

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops g2d_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(g2d_suspend, g2d_resume)
	SET_RUNTIME_PM_OPS(g2d_runसमय_suspend, g2d_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_g2d_match[] = अणु
	अणु .compatible = "samsung,exynos5250-g2d" पूर्ण,
	अणु .compatible = "samsung,exynos4212-g2d" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_g2d_match);

काष्ठा platक्रमm_driver g2d_driver = अणु
	.probe		= g2d_probe,
	.हटाओ		= g2d_हटाओ,
	.driver		= अणु
		.name	= "exynos-drm-g2d",
		.owner	= THIS_MODULE,
		.pm	= &g2d_pm_ops,
		.of_match_table = exynos_g2d_match,
	पूर्ण,
पूर्ण;
