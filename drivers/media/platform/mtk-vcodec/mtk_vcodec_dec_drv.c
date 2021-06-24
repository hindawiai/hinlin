<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 *         Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_dec.h"
#समावेश "mtk_vcodec_dec_pm.h"
#समावेश "mtk_vcodec_intr.h"
#समावेश "mtk_vcodec_util.h"
#समावेश "mtk_vcodec_fw.h"

#घोषणा VDEC_HW_ACTIVE	0x10
#घोषणा VDEC_IRQ_CFG	0x11
#घोषणा VDEC_IRQ_CLR	0x10
#घोषणा VDEC_IRQ_CFG_REG	0xa4

module_param(mtk_v4l2_dbg_level, पूर्णांक, 0644);
module_param(mtk_vcodec_dbg, bool, 0644);

/* Wake up context रुको_queue */
अटल व्योम wake_up_ctx(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	ctx->पूर्णांक_cond = 1;
	wake_up_पूर्णांकerruptible(&ctx->queue);
पूर्ण

अटल irqवापस_t mtk_vcodec_dec_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा mtk_vcodec_dev *dev = priv;
	काष्ठा mtk_vcodec_ctx *ctx;
	u32 cg_status = 0;
	अचिन्हित पूर्णांक dec_करोne_status = 0;
	व्योम __iomem *vdec_misc_addr = dev->reg_base[VDEC_MISC] +
					VDEC_IRQ_CFG_REG;

	ctx = mtk_vcodec_get_curr_ctx(dev);

	/* check अगर HW active or not */
	cg_status = पढ़ोl(dev->reg_base[0]);
	अगर ((cg_status & VDEC_HW_ACTIVE) != 0) अणु
		mtk_v4l2_err("DEC ISR, VDEC active is not 0x0 (0x%08x)",
			     cg_status);
		वापस IRQ_HANDLED;
	पूर्ण

	dec_करोne_status = पढ़ोl(vdec_misc_addr);
	ctx->irq_status = dec_करोne_status;
	अगर ((dec_करोne_status & MTK_VDEC_IRQ_STATUS_DEC_SUCCESS) !=
		MTK_VDEC_IRQ_STATUS_DEC_SUCCESS)
		वापस IRQ_HANDLED;

	/* clear पूर्णांकerrupt */
	ग_लिखोl((पढ़ोl(vdec_misc_addr) | VDEC_IRQ_CFG),
		dev->reg_base[VDEC_MISC] + VDEC_IRQ_CFG_REG);
	ग_लिखोl((पढ़ोl(vdec_misc_addr) & ~VDEC_IRQ_CLR),
		dev->reg_base[VDEC_MISC] + VDEC_IRQ_CFG_REG);

	wake_up_ctx(ctx);

	mtk_v4l2_debug(3,
			"mtk_vcodec_dec_irq_handler :wake up ctx %d, dec_done_status=%x",
			ctx->id, dec_करोne_status);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fops_vcodec_खोलो(काष्ठा file *file)
अणु
	काष्ठा mtk_vcodec_dev *dev = video_drvdata(file);
	काष्ठा mtk_vcodec_ctx *ctx = शून्य;
	काष्ठा mtk_video_dec_buf *mtk_buf = शून्य;
	पूर्णांक ret = 0;
	काष्ठा vb2_queue *src_vq;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	mtk_buf = kzalloc(माप(*mtk_buf), GFP_KERNEL);
	अगर (!mtk_buf) अणु
		kमुक्त(ctx);
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&dev->dev_mutex);
	ctx->empty_flush_buf = mtk_buf;
	ctx->id = dev->id_counter++;
	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);
	INIT_LIST_HEAD(&ctx->list);
	ctx->dev = dev;
	init_रुकोqueue_head(&ctx->queue);
	mutex_init(&ctx->lock);

	ctx->type = MTK_INST_DECODER;
	ret = mtk_vcodec_dec_ctrls_setup(ctx);
	अगर (ret) अणु
		mtk_v4l2_err("Failed to setup mt vcodec controls");
		जाओ err_ctrls_setup;
	पूर्ण
	ctx->m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev_dec, ctx,
		&mtk_vcodec_dec_queue_init);
	अगर (IS_ERR((__क्रमce व्योम *)ctx->m2m_ctx)) अणु
		ret = PTR_ERR((__क्रमce व्योम *)ctx->m2m_ctx);
		mtk_v4l2_err("Failed to v4l2_m2m_ctx_init() (%d)",
			ret);
		जाओ err_m2m_ctx_init;
	पूर्ण
	src_vq = v4l2_m2m_get_vq(ctx->m2m_ctx,
				V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	ctx->empty_flush_buf->m2m_buf.vb.vb2_buf.vb2_queue = src_vq;
	ctx->empty_flush_buf->lastframe = true;
	mtk_vcodec_dec_set_शेष_params(ctx);

	अगर (v4l2_fh_is_singular(&ctx->fh)) अणु
		mtk_vcodec_dec_pw_on(&dev->pm);
		/*
		 * Does nothing अगर firmware was alपढ़ोy loaded.
		 */
		ret = mtk_vcodec_fw_load_firmware(dev->fw_handler);
		अगर (ret < 0) अणु
			/*
			 * Return 0 अगर करोwnloading firmware successfully,
			 * otherwise it is failed
			 */
			mtk_v4l2_err("failed to load firmware!");
			जाओ err_load_fw;
		पूर्ण

		dev->dec_capability =
			mtk_vcodec_fw_get_vdec_capa(dev->fw_handler);
		mtk_v4l2_debug(0, "decoder capability %x", dev->dec_capability);
	पूर्ण

	list_add(&ctx->list, &dev->ctx_list);

	mutex_unlock(&dev->dev_mutex);
	mtk_v4l2_debug(0, "%s decoder [%d]", dev_name(&dev->plat_dev->dev),
			ctx->id);
	वापस ret;

	/* Deinit when failure occurred */
err_load_fw:
	v4l2_m2m_ctx_release(ctx->m2m_ctx);
err_m2m_ctx_init:
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);
err_ctrls_setup:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx->empty_flush_buf);
	kमुक्त(ctx);
	mutex_unlock(&dev->dev_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक fops_vcodec_release(काष्ठा file *file)
अणु
	काष्ठा mtk_vcodec_dev *dev = video_drvdata(file);
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(file->निजी_data);

	mtk_v4l2_debug(0, "[%d] decoder", ctx->id);
	mutex_lock(&dev->dev_mutex);

	/*
	 * Call v4l2_m2m_ctx_release beक्रमe mtk_vcodec_dec_release. First, it
	 * makes sure the worker thपढ़ो is not running after vdec_अगर_deinit.
	 * Second, the decoder will be flushed and all the buffers will be
	 * वापसed in stop_streaming.
	 */
	v4l2_m2m_ctx_release(ctx->m2m_ctx);
	mtk_vcodec_dec_release(ctx);

	अगर (v4l2_fh_is_singular(&ctx->fh))
		mtk_vcodec_dec_pw_off(&dev->pm);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);

	list_del_init(&ctx->list);
	kमुक्त(ctx->empty_flush_buf);
	kमुक्त(ctx);
	mutex_unlock(&dev->dev_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations mtk_vcodec_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fops_vcodec_खोलो,
	.release	= fops_vcodec_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

अटल पूर्णांक mtk_vcodec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_vcodec_dev *dev;
	काष्ठा video_device *vfd_dec;
	काष्ठा resource *res;
	phandle rproc_phandle;
	क्रमागत mtk_vcodec_fw_type fw_type;
	पूर्णांक i, ret;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&dev->ctx_list);
	dev->plat_dev = pdev;

	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "mediatek,vpu",
				  &rproc_phandle)) अणु
		fw_type = VPU;
	पूर्ण अन्यथा अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "mediatek,scp",
					 &rproc_phandle)) अणु
		fw_type = SCP;
	पूर्ण अन्यथा अणु
		mtk_v4l2_err("Could not get vdec IPI device");
		वापस -ENODEV;
	पूर्ण
	dma_set_max_seg_size(&pdev->dev, अच_पूर्णांक_उच्च);

	dev->fw_handler = mtk_vcodec_fw_select(dev, fw_type, DECODER);
	अगर (IS_ERR(dev->fw_handler))
		वापस PTR_ERR(dev->fw_handler);

	ret = mtk_vcodec_init_dec_pm(dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get mt vcodec clock source");
		जाओ err_dec_pm;
	पूर्ण

	क्रम (i = 0; i < NUM_MAX_VDEC_REG_BASE; i++) अणु
		dev->reg_base[i] = devm_platक्रमm_ioremap_resource(pdev, i);
		अगर (IS_ERR((__क्रमce व्योम *)dev->reg_base[i])) अणु
			ret = PTR_ERR((__क्रमce व्योम *)dev->reg_base[i]);
			जाओ err_res;
		पूर्ण
		mtk_v4l2_debug(2, "reg[%d] base=%p", i, dev->reg_base[i]);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "failed to get irq resource");
		ret = -ENOENT;
		जाओ err_res;
	पूर्ण

	dev->dec_irq = platक्रमm_get_irq(pdev, 0);
	irq_set_status_flags(dev->dec_irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(&pdev->dev, dev->dec_irq,
			mtk_vcodec_dec_irq_handler, 0, pdev->name, dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to install dev->dec_irq %d (%d)",
			dev->dec_irq,
			ret);
		जाओ err_res;
	पूर्ण

	mutex_init(&dev->dec_mutex);
	mutex_init(&dev->dev_mutex);
	spin_lock_init(&dev->irqlock);

	snम_लिखो(dev->v4l2_dev.name, माप(dev->v4l2_dev.name), "%s",
		"[/MTK_V4L2_VDEC]");

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret) अणु
		mtk_v4l2_err("v4l2_device_register err=%d", ret);
		जाओ err_res;
	पूर्ण

	init_रुकोqueue_head(&dev->queue);

	vfd_dec = video_device_alloc();
	अगर (!vfd_dec) अणु
		mtk_v4l2_err("Failed to allocate video device");
		ret = -ENOMEM;
		जाओ err_dec_alloc;
	पूर्ण
	vfd_dec->fops		= &mtk_vcodec_fops;
	vfd_dec->ioctl_ops	= &mtk_vdec_ioctl_ops;
	vfd_dec->release	= video_device_release;
	vfd_dec->lock		= &dev->dev_mutex;
	vfd_dec->v4l2_dev	= &dev->v4l2_dev;
	vfd_dec->vfl_dir	= VFL_सूची_M2M;
	vfd_dec->device_caps	= V4L2_CAP_VIDEO_M2M_MPLANE |
			V4L2_CAP_STREAMING;

	snम_लिखो(vfd_dec->name, माप(vfd_dec->name), "%s",
		MTK_VCODEC_DEC_NAME);
	video_set_drvdata(vfd_dec, dev);
	dev->vfd_dec = vfd_dec;
	platक्रमm_set_drvdata(pdev, dev);

	dev->m2m_dev_dec = v4l2_m2m_init(&mtk_vdec_m2m_ops);
	अगर (IS_ERR((__क्रमce व्योम *)dev->m2m_dev_dec)) अणु
		mtk_v4l2_err("Failed to init mem2mem dec device");
		ret = PTR_ERR((__क्रमce व्योम *)dev->m2m_dev_dec);
		जाओ err_dec_mem_init;
	पूर्ण

	dev->decode_workqueue =
		alloc_ordered_workqueue(MTK_VCODEC_DEC_NAME,
			WQ_MEM_RECLAIM | WQ_FREEZABLE);
	अगर (!dev->decode_workqueue) अणु
		mtk_v4l2_err("Failed to create decode workqueue");
		ret = -EINVAL;
		जाओ err_event_workq;
	पूर्ण

	ret = video_रेजिस्टर_device(vfd_dec, VFL_TYPE_VIDEO, 0);
	अगर (ret) अणु
		mtk_v4l2_err("Failed to register video device");
		जाओ err_dec_reg;
	पूर्ण

	mtk_v4l2_debug(0, "decoder registered as /dev/video%d",
		vfd_dec->num);

	वापस 0;

err_dec_reg:
	destroy_workqueue(dev->decode_workqueue);
err_event_workq:
	v4l2_m2m_release(dev->m2m_dev_dec);
err_dec_mem_init:
	video_unरेजिस्टर_device(vfd_dec);
err_dec_alloc:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
err_res:
	mtk_vcodec_release_dec_pm(dev);
err_dec_pm:
	mtk_vcodec_fw_release(dev->fw_handler);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_vcodec_match[] = अणु
	अणु.compatible = "mediatek,mt8173-vcodec-dec",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mtk_vcodec_match);

अटल पूर्णांक mtk_vcodec_dec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_vcodec_dev *dev = platक्रमm_get_drvdata(pdev);

	flush_workqueue(dev->decode_workqueue);
	destroy_workqueue(dev->decode_workqueue);
	अगर (dev->m2m_dev_dec)
		v4l2_m2m_release(dev->m2m_dev_dec);

	अगर (dev->vfd_dec)
		video_unरेजिस्टर_device(dev->vfd_dec);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	mtk_vcodec_release_dec_pm(dev);
	mtk_vcodec_fw_release(dev->fw_handler);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_vcodec_dec_driver = अणु
	.probe	= mtk_vcodec_probe,
	.हटाओ	= mtk_vcodec_dec_हटाओ,
	.driver	= अणु
		.name	= MTK_VCODEC_DEC_NAME,
		.of_match_table = mtk_vcodec_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_vcodec_dec_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Mediatek video codec V4L2 decoder driver");
