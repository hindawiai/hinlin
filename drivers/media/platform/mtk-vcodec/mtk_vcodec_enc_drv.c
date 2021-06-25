<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: PC Chen <pc.chen@mediatek.com>
*	Tअगरfany Lin <tअगरfany.lin@mediatek.com>
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
#समावेश <linux/pm_runसमय.स>

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_enc.h"
#समावेश "mtk_vcodec_enc_pm.h"
#समावेश "mtk_vcodec_intr.h"
#समावेश "mtk_vcodec_util.h"
#समावेश "mtk_vcodec_fw.h"

module_param(mtk_v4l2_dbg_level, पूर्णांक, S_IRUGO | S_IWUSR);
module_param(mtk_vcodec_dbg, bool, S_IRUGO | S_IWUSR);

अटल स्थिर काष्ठा mtk_video_fmt mtk_video_क्रमmats_output_mt8173[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_NV12M,
		.type = MTK_FMT_FRAME,
		.num_planes = 2,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_NV21M,
		.type = MTK_FMT_FRAME,
		.num_planes = 2,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_YUV420M,
		.type = MTK_FMT_FRAME,
		.num_planes = 3,
	पूर्ण,
	अणु
		.fourcc = V4L2_PIX_FMT_YVU420M,
		.type = MTK_FMT_FRAME,
		.num_planes = 3,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_video_fmt mtk_video_क्रमmats_capture_mt8173_avc[] =  अणु
	अणु
		.fourcc = V4L2_PIX_FMT_H264,
		.type = MTK_FMT_ENC,
		.num_planes = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_video_fmt mtk_video_क्रमmats_capture_mt8173_vp8[] =  अणु
	अणु
		.fourcc = V4L2_PIX_FMT_VP8,
		.type = MTK_FMT_ENC,
		.num_planes = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mtk_video_fmt mtk_video_क्रमmats_capture_mt8183[] =  अणु
	अणु
		.fourcc = V4L2_PIX_FMT_H264,
		.type = MTK_FMT_ENC,
		.num_planes = 1,
	पूर्ण,
पूर्ण;

/* Wake up context रुको_queue */
अटल व्योम wake_up_ctx(काष्ठा mtk_vcodec_ctx *ctx, अचिन्हित पूर्णांक reason)
अणु
	ctx->पूर्णांक_cond = 1;
	ctx->पूर्णांक_type = reason;
	wake_up_पूर्णांकerruptible(&ctx->queue);
पूर्ण

अटल व्योम clean_irq_status(अचिन्हित पूर्णांक irq_status, व्योम __iomem *addr)
अणु
	अगर (irq_status & MTK_VENC_IRQ_STATUS_PAUSE)
		ग_लिखोl(MTK_VENC_IRQ_STATUS_PAUSE, addr);

	अगर (irq_status & MTK_VENC_IRQ_STATUS_SWITCH)
		ग_लिखोl(MTK_VENC_IRQ_STATUS_SWITCH, addr);

	अगर (irq_status & MTK_VENC_IRQ_STATUS_DRAM)
		ग_लिखोl(MTK_VENC_IRQ_STATUS_DRAM, addr);

	अगर (irq_status & MTK_VENC_IRQ_STATUS_SPS)
		ग_लिखोl(MTK_VENC_IRQ_STATUS_SPS, addr);

	अगर (irq_status & MTK_VENC_IRQ_STATUS_PPS)
		ग_लिखोl(MTK_VENC_IRQ_STATUS_PPS, addr);

	अगर (irq_status & MTK_VENC_IRQ_STATUS_FRM)
		ग_लिखोl(MTK_VENC_IRQ_STATUS_FRM, addr);

पूर्ण
अटल irqवापस_t mtk_vcodec_enc_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा mtk_vcodec_dev *dev = priv;
	काष्ठा mtk_vcodec_ctx *ctx;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr;

	spin_lock_irqsave(&dev->irqlock, flags);
	ctx = dev->curr_ctx;
	spin_unlock_irqrestore(&dev->irqlock, flags);

	mtk_v4l2_debug(1, "id=%d coreid:%d", ctx->id, dev->venc_pdata->core_id);
	addr = dev->reg_base[dev->venc_pdata->core_id] +
				MTK_VENC_IRQ_ACK_OFFSET;

	ctx->irq_status = पढ़ोl(dev->reg_base[dev->venc_pdata->core_id] +
				(MTK_VENC_IRQ_STATUS_OFFSET));

	clean_irq_status(ctx->irq_status, addr);

	wake_up_ctx(ctx, MTK_INST_IRQ_RECEIVED);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fops_vcodec_खोलो(काष्ठा file *file)
अणु
	काष्ठा mtk_vcodec_dev *dev = video_drvdata(file);
	काष्ठा mtk_vcodec_ctx *ctx = शून्य;
	पूर्णांक ret = 0;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mutex_lock(&dev->dev_mutex);
	/*
	 * Use simple counter to uniquely identअगरy this context. Only
	 * used क्रम logging.
	 */
	ctx->id = dev->id_counter++;
	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);
	INIT_LIST_HEAD(&ctx->list);
	ctx->dev = dev;
	init_रुकोqueue_head(&ctx->queue);

	ctx->type = MTK_INST_ENCODER;
	ret = mtk_vcodec_enc_ctrls_setup(ctx);
	अगर (ret) अणु
		mtk_v4l2_err("Failed to setup controls() (%d)",
				ret);
		जाओ err_ctrls_setup;
	पूर्ण
	ctx->m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev_enc, ctx,
				&mtk_vcodec_enc_queue_init);
	अगर (IS_ERR((__क्रमce व्योम *)ctx->m2m_ctx)) अणु
		ret = PTR_ERR((__क्रमce व्योम *)ctx->m2m_ctx);
		mtk_v4l2_err("Failed to v4l2_m2m_ctx_init() (%d)",
				ret);
		जाओ err_m2m_ctx_init;
	पूर्ण
	mtk_vcodec_enc_set_शेष_params(ctx);

	अगर (v4l2_fh_is_singular(&ctx->fh)) अणु
		/*
		 * load fireware to checks अगर it was loaded alपढ़ोy and
		 * करोes nothing in that हाल
		 */
		ret = mtk_vcodec_fw_load_firmware(dev->fw_handler);
		अगर (ret < 0) अणु
			/*
			 * Return 0 अगर करोwnloading firmware successfully,
			 * otherwise it is failed
			 */
			mtk_v4l2_err("vpu_load_firmware failed!");
			जाओ err_load_fw;
		पूर्ण

		dev->enc_capability =
			mtk_vcodec_fw_get_venc_capa(dev->fw_handler);
		mtk_v4l2_debug(0, "encoder capability %x", dev->enc_capability);
	पूर्ण

	mtk_v4l2_debug(2, "Create instance [%d]@%p m2m_ctx=%p ",
			ctx->id, ctx, ctx->m2m_ctx);

	list_add(&ctx->list, &dev->ctx_list);

	mutex_unlock(&dev->dev_mutex);
	mtk_v4l2_debug(0, "%s encoder [%d]", dev_name(&dev->plat_dev->dev),
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
	kमुक्त(ctx);
	mutex_unlock(&dev->dev_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक fops_vcodec_release(काष्ठा file *file)
अणु
	काष्ठा mtk_vcodec_dev *dev = video_drvdata(file);
	काष्ठा mtk_vcodec_ctx *ctx = fh_to_ctx(file->निजी_data);

	mtk_v4l2_debug(1, "[%d] encoder", ctx->id);
	mutex_lock(&dev->dev_mutex);

	mtk_vcodec_enc_release(ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_hdl);
	v4l2_m2m_ctx_release(ctx->m2m_ctx);

	list_del_init(&ctx->list);
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
	काष्ठा video_device *vfd_enc;
	काष्ठा resource *res;
	phandle rproc_phandle;
	क्रमागत mtk_vcodec_fw_type fw_type;
	पूर्णांक ret;

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
		mtk_v4l2_err("Could not get venc IPI device");
		वापस -ENODEV;
	पूर्ण
	dma_set_max_seg_size(&pdev->dev, अच_पूर्णांक_उच्च);

	dev->fw_handler = mtk_vcodec_fw_select(dev, fw_type, ENCODER);
	अगर (IS_ERR(dev->fw_handler))
		वापस PTR_ERR(dev->fw_handler);

	dev->venc_pdata = of_device_get_match_data(&pdev->dev);
	ret = mtk_vcodec_init_enc_pm(dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get mtk vcodec clock source!");
		जाओ err_enc_pm;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	dev->reg_base[dev->venc_pdata->core_id] =
		devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dev->reg_base[dev->venc_pdata->core_id])) अणु
		ret = PTR_ERR(dev->reg_base[dev->venc_pdata->core_id]);
		जाओ err_res;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "failed to get irq resource");
		ret = -ENOENT;
		जाओ err_res;
	पूर्ण

	dev->enc_irq = platक्रमm_get_irq(pdev, 0);
	irq_set_status_flags(dev->enc_irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(&pdev->dev, dev->enc_irq,
			       mtk_vcodec_enc_irq_handler,
			       0, pdev->name, dev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to install dev->enc_irq %d (%d) core_id (%d)",
			dev->enc_irq, ret, dev->venc_pdata->core_id);
		ret = -EINVAL;
		जाओ err_res;
	पूर्ण

	mutex_init(&dev->enc_mutex);
	mutex_init(&dev->dev_mutex);
	spin_lock_init(&dev->irqlock);

	snम_लिखो(dev->v4l2_dev.name, माप(dev->v4l2_dev.name), "%s",
		 "[MTK_V4L2_VENC]");

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret) अणु
		mtk_v4l2_err("v4l2_device_register err=%d", ret);
		जाओ err_res;
	पूर्ण

	init_रुकोqueue_head(&dev->queue);

	/* allocate video device क्रम encoder and रेजिस्टर it */
	vfd_enc = video_device_alloc();
	अगर (!vfd_enc) अणु
		mtk_v4l2_err("Failed to allocate video device");
		ret = -ENOMEM;
		जाओ err_enc_alloc;
	पूर्ण
	vfd_enc->fops           = &mtk_vcodec_fops;
	vfd_enc->ioctl_ops      = &mtk_venc_ioctl_ops;
	vfd_enc->release        = video_device_release;
	vfd_enc->lock           = &dev->dev_mutex;
	vfd_enc->v4l2_dev       = &dev->v4l2_dev;
	vfd_enc->vfl_dir        = VFL_सूची_M2M;
	vfd_enc->device_caps	= V4L2_CAP_VIDEO_M2M_MPLANE |
					V4L2_CAP_STREAMING;

	snम_लिखो(vfd_enc->name, माप(vfd_enc->name), "%s",
		 MTK_VCODEC_ENC_NAME);
	video_set_drvdata(vfd_enc, dev);
	dev->vfd_enc = vfd_enc;
	platक्रमm_set_drvdata(pdev, dev);

	dev->m2m_dev_enc = v4l2_m2m_init(&mtk_venc_m2m_ops);
	अगर (IS_ERR((__क्रमce व्योम *)dev->m2m_dev_enc)) अणु
		mtk_v4l2_err("Failed to init mem2mem enc device");
		ret = PTR_ERR((__क्रमce व्योम *)dev->m2m_dev_enc);
		जाओ err_enc_mem_init;
	पूर्ण

	dev->encode_workqueue =
			alloc_ordered_workqueue(MTK_VCODEC_ENC_NAME,
						WQ_MEM_RECLAIM |
						WQ_FREEZABLE);
	अगर (!dev->encode_workqueue) अणु
		mtk_v4l2_err("Failed to create encode workqueue");
		ret = -EINVAL;
		जाओ err_event_workq;
	पूर्ण

	ret = video_रेजिस्टर_device(vfd_enc, VFL_TYPE_VIDEO, 1);
	अगर (ret) अणु
		mtk_v4l2_err("Failed to register video device");
		जाओ err_enc_reg;
	पूर्ण

	mtk_v4l2_debug(0, "encoder %d registered as /dev/video%d",
		       dev->venc_pdata->core_id, vfd_enc->num);

	वापस 0;

err_enc_reg:
	destroy_workqueue(dev->encode_workqueue);
err_event_workq:
	v4l2_m2m_release(dev->m2m_dev_enc);
err_enc_mem_init:
	video_unरेजिस्टर_device(vfd_enc);
err_enc_alloc:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
err_res:
	mtk_vcodec_release_enc_pm(dev);
err_enc_pm:
	mtk_vcodec_fw_release(dev->fw_handler);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mtk_vcodec_enc_pdata mt8173_avc_pdata = अणु
	.chip = MTK_MT8173,
	.capture_क्रमmats = mtk_video_क्रमmats_capture_mt8173_avc,
	.num_capture_क्रमmats = ARRAY_SIZE(mtk_video_क्रमmats_capture_mt8173_avc),
	.output_क्रमmats = mtk_video_क्रमmats_output_mt8173,
	.num_output_क्रमmats = ARRAY_SIZE(mtk_video_क्रमmats_output_mt8173),
	.min_bitrate = 1,
	.max_bitrate = 4000000,
	.core_id = VENC_SYS,
पूर्ण;

अटल स्थिर काष्ठा mtk_vcodec_enc_pdata mt8173_vp8_pdata = अणु
	.chip = MTK_MT8173,
	.capture_क्रमmats = mtk_video_क्रमmats_capture_mt8173_vp8,
	.num_capture_क्रमmats = ARRAY_SIZE(mtk_video_क्रमmats_capture_mt8173_vp8),
	.output_क्रमmats = mtk_video_क्रमmats_output_mt8173,
	.num_output_क्रमmats = ARRAY_SIZE(mtk_video_क्रमmats_output_mt8173),
	.min_bitrate = 64,
	.max_bitrate = 4000000,
	.core_id = VENC_LT_SYS,
पूर्ण;

अटल स्थिर काष्ठा mtk_vcodec_enc_pdata mt8183_pdata = अणु
	.chip = MTK_MT8183,
	.uses_ext = true,
	.capture_क्रमmats = mtk_video_क्रमmats_capture_mt8183,
	.num_capture_क्रमmats = ARRAY_SIZE(mtk_video_क्रमmats_capture_mt8183),
	/* MT8183 supports the same output क्रमmats as MT8173 */
	.output_क्रमmats = mtk_video_क्रमmats_output_mt8173,
	.num_output_क्रमmats = ARRAY_SIZE(mtk_video_क्रमmats_output_mt8173),
	.min_bitrate = 64,
	.max_bitrate = 40000000,
	.core_id = VENC_SYS,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_vcodec_enc_match[] = अणु
	अणु.compatible = "mediatek,mt8173-vcodec-enc",
			.data = &mt8173_avc_pdataपूर्ण,
	अणु.compatible = "mediatek,mt8173-vcodec-enc-vp8",
			.data = &mt8173_vp8_pdataपूर्ण,
	अणु.compatible = "mediatek,mt8183-vcodec-enc", .data = &mt8183_pdataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_vcodec_enc_match);

अटल पूर्णांक mtk_vcodec_enc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_vcodec_dev *dev = platक्रमm_get_drvdata(pdev);

	mtk_v4l2_debug_enter();
	flush_workqueue(dev->encode_workqueue);
	destroy_workqueue(dev->encode_workqueue);
	अगर (dev->m2m_dev_enc)
		v4l2_m2m_release(dev->m2m_dev_enc);

	अगर (dev->vfd_enc)
		video_unरेजिस्टर_device(dev->vfd_enc);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	mtk_vcodec_release_enc_pm(dev);
	mtk_vcodec_fw_release(dev->fw_handler);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_vcodec_enc_driver = अणु
	.probe	= mtk_vcodec_probe,
	.हटाओ	= mtk_vcodec_enc_हटाओ,
	.driver	= अणु
		.name	= MTK_VCODEC_ENC_NAME,
		.of_match_table = mtk_vcodec_enc_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_vcodec_enc_driver);


MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Mediatek video codec V4L2 encoder driver");
