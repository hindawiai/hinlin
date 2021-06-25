<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Lucas Stach, Pengutronix
 */

#समावेश <drm/drm_fourcc.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <video/imx-ipu-v3.h>

#समावेश "ipu-prv.h"

#घोषणा IPU_PRE_MAX_WIDTH	2048
#घोषणा IPU_PRE_NUM_SCANLINES	8

#घोषणा IPU_PRE_CTRL					0x000
#घोषणा IPU_PRE_CTRL_SET				0x004
#घोषणा  IPU_PRE_CTRL_ENABLE				(1 << 0)
#घोषणा  IPU_PRE_CTRL_BLOCK_EN				(1 << 1)
#घोषणा  IPU_PRE_CTRL_BLOCK_16				(1 << 2)
#घोषणा  IPU_PRE_CTRL_SDW_UPDATE			(1 << 4)
#घोषणा  IPU_PRE_CTRL_VFLIP				(1 << 5)
#घोषणा  IPU_PRE_CTRL_SO				(1 << 6)
#घोषणा  IPU_PRE_CTRL_INTERLACED_FIELD			(1 << 7)
#घोषणा  IPU_PRE_CTRL_HANDSHAKE_EN			(1 << 8)
#घोषणा  IPU_PRE_CTRL_HANDSHAKE_LINE_NUM(v)		((v & 0x3) << 9)
#घोषणा  IPU_PRE_CTRL_HANDSHAKE_ABORT_SKIP_EN		(1 << 11)
#घोषणा  IPU_PRE_CTRL_EN_REPEAT				(1 << 28)
#घोषणा  IPU_PRE_CTRL_TPR_REST_SEL			(1 << 29)
#घोषणा  IPU_PRE_CTRL_CLKGATE				(1 << 30)
#घोषणा  IPU_PRE_CTRL_SFTRST				(1 << 31)

#घोषणा IPU_PRE_CUR_BUF					0x030

#घोषणा IPU_PRE_NEXT_BUF				0x040

#घोषणा IPU_PRE_TPR_CTRL				0x070
#घोषणा  IPU_PRE_TPR_CTRL_TILE_FORMAT(v)		((v & 0xff) << 0)
#घोषणा  IPU_PRE_TPR_CTRL_TILE_FORMAT_MASK		0xff
#घोषणा  IPU_PRE_TPR_CTRL_TILE_FORMAT_16_BIT		(1 << 0)
#घोषणा  IPU_PRE_TPR_CTRL_TILE_FORMAT_SPLIT_BUF		(1 << 4)
#घोषणा  IPU_PRE_TPR_CTRL_TILE_FORMAT_SINGLE_BUF	(1 << 5)
#घोषणा  IPU_PRE_TPR_CTRL_TILE_FORMAT_SUPER_TILED	(1 << 6)

#घोषणा IPU_PRE_PREFETCH_ENG_CTRL			0x080
#घोषणा  IPU_PRE_PREF_ENG_CTRL_PREFETCH_EN		(1 << 0)
#घोषणा  IPU_PRE_PREF_ENG_CTRL_RD_NUM_BYTES(v)		((v & 0x7) << 1)
#घोषणा  IPU_PRE_PREF_ENG_CTRL_INPUT_ACTIVE_BPP(v)	((v & 0x3) << 4)
#घोषणा  IPU_PRE_PREF_ENG_CTRL_INPUT_PIXEL_FORMAT(v)	((v & 0x7) << 8)
#घोषणा  IPU_PRE_PREF_ENG_CTRL_SHIFT_BYPASS		(1 << 11)
#घोषणा  IPU_PRE_PREF_ENG_CTRL_FIELD_INVERSE		(1 << 12)
#घोषणा  IPU_PRE_PREF_ENG_CTRL_PARTIAL_UV_SWAP		(1 << 14)
#घोषणा  IPU_PRE_PREF_ENG_CTRL_TPR_COOR_OFFSET_EN	(1 << 15)

#घोषणा IPU_PRE_PREFETCH_ENG_INPUT_SIZE			0x0a0
#घोषणा  IPU_PRE_PREFETCH_ENG_INPUT_SIZE_WIDTH(v)	((v & 0xffff) << 0)
#घोषणा  IPU_PRE_PREFETCH_ENG_INPUT_SIZE_HEIGHT(v)	((v & 0xffff) << 16)

#घोषणा IPU_PRE_PREFETCH_ENG_PITCH			0x0d0
#घोषणा  IPU_PRE_PREFETCH_ENG_PITCH_Y(v)		((v & 0xffff) << 0)
#घोषणा  IPU_PRE_PREFETCH_ENG_PITCH_UV(v)		((v & 0xffff) << 16)

#घोषणा IPU_PRE_STORE_ENG_CTRL				0x110
#घोषणा  IPU_PRE_STORE_ENG_CTRL_STORE_EN		(1 << 0)
#घोषणा  IPU_PRE_STORE_ENG_CTRL_WR_NUM_BYTES(v)		((v & 0x7) << 1)
#घोषणा  IPU_PRE_STORE_ENG_CTRL_OUTPUT_ACTIVE_BPP(v)	((v & 0x3) << 4)

#घोषणा IPU_PRE_STORE_ENG_STATUS			0x120
#घोषणा  IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_X_MASK	0xffff
#घोषणा  IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_X_SHIFT	0
#घोषणा  IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_Y_MASK	0x3fff
#घोषणा  IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_Y_SHIFT	16
#घोषणा  IPU_PRE_STORE_ENG_STATUS_STORE_FIFO_FULL	(1 << 30)
#घोषणा  IPU_PRE_STORE_ENG_STATUS_STORE_FIELD		(1 << 31)

#घोषणा IPU_PRE_STORE_ENG_SIZE				0x130
#घोषणा  IPU_PRE_STORE_ENG_SIZE_INPUT_WIDTH(v)		((v & 0xffff) << 0)
#घोषणा  IPU_PRE_STORE_ENG_SIZE_INPUT_HEIGHT(v)		((v & 0xffff) << 16)

#घोषणा IPU_PRE_STORE_ENG_PITCH				0x140
#घोषणा  IPU_PRE_STORE_ENG_PITCH_OUT_PITCH(v)		((v & 0xffff) << 0)

#घोषणा IPU_PRE_STORE_ENG_ADDR				0x150

काष्ठा ipu_pre अणु
	काष्ठा list_head	list;
	काष्ठा device		*dev;

	व्योम __iomem		*regs;
	काष्ठा clk		*clk_axi;
	काष्ठा gen_pool		*iram;

	dma_addr_t		buffer_paddr;
	व्योम			*buffer_virt;
	bool			in_use;
	अचिन्हित पूर्णांक		safe_winकरोw_end;
	अचिन्हित पूर्णांक		last_bufaddr;
पूर्ण;

अटल DEFINE_MUTEX(ipu_pre_list_mutex);
अटल LIST_HEAD(ipu_pre_list);
अटल पूर्णांक available_pres;

पूर्णांक ipu_pre_get_available_count(व्योम)
अणु
	वापस available_pres;
पूर्ण

काष्ठा ipu_pre *
ipu_pre_lookup_by_phandle(काष्ठा device *dev, स्थिर अक्षर *name, पूर्णांक index)
अणु
	काष्ठा device_node *pre_node = of_parse_phandle(dev->of_node,
							name, index);
	काष्ठा ipu_pre *pre;

	mutex_lock(&ipu_pre_list_mutex);
	list_क्रम_each_entry(pre, &ipu_pre_list, list) अणु
		अगर (pre_node == pre->dev->of_node) अणु
			mutex_unlock(&ipu_pre_list_mutex);
			device_link_add(dev, pre->dev,
					DL_FLAG_AUTOREMOVE_CONSUMER);
			of_node_put(pre_node);
			वापस pre;
		पूर्ण
	पूर्ण
	mutex_unlock(&ipu_pre_list_mutex);

	of_node_put(pre_node);

	वापस शून्य;
पूर्ण

पूर्णांक ipu_pre_get(काष्ठा ipu_pre *pre)
अणु
	u32 val;

	अगर (pre->in_use)
		वापस -EBUSY;

	/* first get the engine out of reset and हटाओ घड़ी gating */
	ग_लिखोl(0, pre->regs + IPU_PRE_CTRL);

	/* init शेषs that should be applied to all streams */
	val = IPU_PRE_CTRL_HANDSHAKE_ABORT_SKIP_EN |
	      IPU_PRE_CTRL_HANDSHAKE_EN |
	      IPU_PRE_CTRL_TPR_REST_SEL |
	      IPU_PRE_CTRL_SDW_UPDATE;
	ग_लिखोl(val, pre->regs + IPU_PRE_CTRL);

	pre->in_use = true;
	वापस 0;
पूर्ण

व्योम ipu_pre_put(काष्ठा ipu_pre *pre)
अणु
	ग_लिखोl(IPU_PRE_CTRL_SFTRST, pre->regs + IPU_PRE_CTRL);

	pre->in_use = false;
पूर्ण

व्योम ipu_pre_configure(काष्ठा ipu_pre *pre, अचिन्हित पूर्णांक width,
		       अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक stride, u32 क्रमmat,
		       uपूर्णांक64_t modअगरier, अचिन्हित पूर्णांक bufaddr)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(क्रमmat);
	u32 active_bpp = info->cpp[0] >> 1;
	u32 val;

	/* calculate safe winकरोw क्रम ctrl रेजिस्टर updates */
	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR)
		pre->safe_winकरोw_end = height - 2;
	अन्यथा
		pre->safe_winकरोw_end = DIV_ROUND_UP(height, 4) - 1;

	ग_लिखोl(bufaddr, pre->regs + IPU_PRE_CUR_BUF);
	ग_लिखोl(bufaddr, pre->regs + IPU_PRE_NEXT_BUF);
	pre->last_bufaddr = bufaddr;

	val = IPU_PRE_PREF_ENG_CTRL_INPUT_PIXEL_FORMAT(0) |
	      IPU_PRE_PREF_ENG_CTRL_INPUT_ACTIVE_BPP(active_bpp) |
	      IPU_PRE_PREF_ENG_CTRL_RD_NUM_BYTES(4) |
	      IPU_PRE_PREF_ENG_CTRL_SHIFT_BYPASS |
	      IPU_PRE_PREF_ENG_CTRL_PREFETCH_EN;
	ग_लिखोl(val, pre->regs + IPU_PRE_PREFETCH_ENG_CTRL);

	val = IPU_PRE_PREFETCH_ENG_INPUT_SIZE_WIDTH(width) |
	      IPU_PRE_PREFETCH_ENG_INPUT_SIZE_HEIGHT(height);
	ग_लिखोl(val, pre->regs + IPU_PRE_PREFETCH_ENG_INPUT_SIZE);

	val = IPU_PRE_PREFETCH_ENG_PITCH_Y(stride);
	ग_लिखोl(val, pre->regs + IPU_PRE_PREFETCH_ENG_PITCH);

	val = IPU_PRE_STORE_ENG_CTRL_OUTPUT_ACTIVE_BPP(active_bpp) |
	      IPU_PRE_STORE_ENG_CTRL_WR_NUM_BYTES(4) |
	      IPU_PRE_STORE_ENG_CTRL_STORE_EN;
	ग_लिखोl(val, pre->regs + IPU_PRE_STORE_ENG_CTRL);

	val = IPU_PRE_STORE_ENG_SIZE_INPUT_WIDTH(width) |
	      IPU_PRE_STORE_ENG_SIZE_INPUT_HEIGHT(height);
	ग_लिखोl(val, pre->regs + IPU_PRE_STORE_ENG_SIZE);

	val = IPU_PRE_STORE_ENG_PITCH_OUT_PITCH(stride);
	ग_लिखोl(val, pre->regs + IPU_PRE_STORE_ENG_PITCH);

	ग_लिखोl(pre->buffer_paddr, pre->regs + IPU_PRE_STORE_ENG_ADDR);

	val = पढ़ोl(pre->regs + IPU_PRE_TPR_CTRL);
	val &= ~IPU_PRE_TPR_CTRL_TILE_FORMAT_MASK;
	अगर (modअगरier != DRM_FORMAT_MOD_LINEAR) अणु
		/* only support single buffer क्रमmats क्रम now */
		val |= IPU_PRE_TPR_CTRL_TILE_FORMAT_SINGLE_BUF;
		अगर (modअगरier == DRM_FORMAT_MOD_VIVANTE_SUPER_TILED)
			val |= IPU_PRE_TPR_CTRL_TILE_FORMAT_SUPER_TILED;
		अगर (info->cpp[0] == 2)
			val |= IPU_PRE_TPR_CTRL_TILE_FORMAT_16_BIT;
	पूर्ण
	ग_लिखोl(val, pre->regs + IPU_PRE_TPR_CTRL);

	val = पढ़ोl(pre->regs + IPU_PRE_CTRL);
	val |= IPU_PRE_CTRL_EN_REPEAT | IPU_PRE_CTRL_ENABLE |
	       IPU_PRE_CTRL_SDW_UPDATE;
	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR)
		val &= ~IPU_PRE_CTRL_BLOCK_EN;
	अन्यथा
		val |= IPU_PRE_CTRL_BLOCK_EN;
	ग_लिखोl(val, pre->regs + IPU_PRE_CTRL);
पूर्ण

व्योम ipu_pre_update(काष्ठा ipu_pre *pre, अचिन्हित पूर्णांक bufaddr)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(5);
	अचिन्हित लघु current_yblock;
	u32 val;

	अगर (bufaddr == pre->last_bufaddr)
		वापस;

	ग_लिखोl(bufaddr, pre->regs + IPU_PRE_NEXT_BUF);
	pre->last_bufaddr = bufaddr;

	करो अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(pre->dev, "timeout waiting for PRE safe window\n");
			वापस;
		पूर्ण

		val = पढ़ोl(pre->regs + IPU_PRE_STORE_ENG_STATUS);
		current_yblock =
			(val >> IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_Y_SHIFT) &
			IPU_PRE_STORE_ENG_STATUS_STORE_BLOCK_Y_MASK;
	पूर्ण जबतक (current_yblock == 0 || current_yblock >= pre->safe_winकरोw_end);

	ग_लिखोl(IPU_PRE_CTRL_SDW_UPDATE, pre->regs + IPU_PRE_CTRL_SET);
पूर्ण

bool ipu_pre_update_pending(काष्ठा ipu_pre *pre)
अणु
	वापस !!(पढ़ोl_relaxed(pre->regs + IPU_PRE_CTRL) &
		  IPU_PRE_CTRL_SDW_UPDATE);
पूर्ण

u32 ipu_pre_get_baddr(काष्ठा ipu_pre *pre)
अणु
	वापस (u32)pre->buffer_paddr;
पूर्ण

अटल पूर्णांक ipu_pre_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा ipu_pre *pre;

	pre = devm_kzalloc(dev, माप(*pre), GFP_KERNEL);
	अगर (!pre)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pre->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(pre->regs))
		वापस PTR_ERR(pre->regs);

	pre->clk_axi = devm_clk_get(dev, "axi");
	अगर (IS_ERR(pre->clk_axi))
		वापस PTR_ERR(pre->clk_axi);

	pre->iram = of_gen_pool_get(dev->of_node, "fsl,iram", 0);
	अगर (!pre->iram)
		वापस -EPROBE_DEFER;

	/*
	 * Allocate IRAM buffer with maximum size. This could be made dynamic,
	 * but as there is no other user of this IRAM region and we can fit all
	 * max sized buffers पूर्णांकo it, there is no need yet.
	 */
	pre->buffer_virt = gen_pool_dma_alloc(pre->iram, IPU_PRE_MAX_WIDTH *
					      IPU_PRE_NUM_SCANLINES * 4,
					      &pre->buffer_paddr);
	अगर (!pre->buffer_virt)
		वापस -ENOMEM;

	clk_prepare_enable(pre->clk_axi);

	pre->dev = dev;
	platक्रमm_set_drvdata(pdev, pre);
	mutex_lock(&ipu_pre_list_mutex);
	list_add(&pre->list, &ipu_pre_list);
	available_pres++;
	mutex_unlock(&ipu_pre_list_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ipu_pre_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipu_pre *pre = platक्रमm_get_drvdata(pdev);

	mutex_lock(&ipu_pre_list_mutex);
	list_del(&pre->list);
	available_pres--;
	mutex_unlock(&ipu_pre_list_mutex);

	clk_disable_unprepare(pre->clk_axi);

	अगर (pre->buffer_virt)
		gen_pool_मुक्त(pre->iram, (अचिन्हित दीर्घ)pre->buffer_virt,
			      IPU_PRE_MAX_WIDTH * IPU_PRE_NUM_SCANLINES * 4);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ipu_pre_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6qp-pre", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

काष्ठा platक्रमm_driver ipu_pre_drv = अणु
	.probe		= ipu_pre_probe,
	.हटाओ		= ipu_pre_हटाओ,
	.driver		= अणु
		.name	= "imx-ipu-pre",
		.of_match_table = ipu_pre_dt_ids,
	पूर्ण,
पूर्ण;
