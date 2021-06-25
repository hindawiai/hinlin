<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author: YT SHEN <yt.shen@mediatek.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-mapping.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "mtk_drm_crtc.h"
#समावेश "mtk_drm_ddp_comp.h"
#समावेश "mtk_drm_drv.h"
#समावेश "mtk_drm_gem.h"

#घोषणा DRIVER_NAME "mediatek"
#घोषणा DRIVER_DESC "Mediatek SoC DRM"
#घोषणा DRIVER_DATE "20150513"
#घोषणा DRIVER_MAJOR 1
#घोषणा DRIVER_MINOR 0

अटल स्थिर काष्ठा drm_mode_config_helper_funcs mtk_drm_mode_config_helpers = अणु
	.atomic_commit_tail = drm_atomic_helper_commit_tail_rpm,
पूर्ण;

अटल काष्ठा drm_framebuffer *
mtk_drm_mode_fb_create(काष्ठा drm_device *dev,
		       काष्ठा drm_file *file,
		       स्थिर काष्ठा drm_mode_fb_cmd2 *cmd)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_get_क्रमmat_info(dev, cmd);

	अगर (info->num_planes != 1)
		वापस ERR_PTR(-EINVAL);

	वापस drm_gem_fb_create(dev, file, cmd);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs mtk_drm_mode_config_funcs = अणु
	.fb_create = mtk_drm_mode_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt2701_mtk_ddp_मुख्य[] = अणु
	DDP_COMPONENT_OVL0,
	DDP_COMPONENT_RDMA0,
	DDP_COMPONENT_COLOR0,
	DDP_COMPONENT_BLS,
	DDP_COMPONENT_DSI0,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt2701_mtk_ddp_ext[] = अणु
	DDP_COMPONENT_RDMA1,
	DDP_COMPONENT_DPI0,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt7623_mtk_ddp_मुख्य[] = अणु
	DDP_COMPONENT_OVL0,
	DDP_COMPONENT_RDMA0,
	DDP_COMPONENT_COLOR0,
	DDP_COMPONENT_BLS,
	DDP_COMPONENT_DPI0,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt7623_mtk_ddp_ext[] = अणु
	DDP_COMPONENT_RDMA1,
	DDP_COMPONENT_DSI0,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt2712_mtk_ddp_मुख्य[] = अणु
	DDP_COMPONENT_OVL0,
	DDP_COMPONENT_COLOR0,
	DDP_COMPONENT_AAL0,
	DDP_COMPONENT_OD0,
	DDP_COMPONENT_RDMA0,
	DDP_COMPONENT_DPI0,
	DDP_COMPONENT_PWM0,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt2712_mtk_ddp_ext[] = अणु
	DDP_COMPONENT_OVL1,
	DDP_COMPONENT_COLOR1,
	DDP_COMPONENT_AAL1,
	DDP_COMPONENT_OD1,
	DDP_COMPONENT_RDMA1,
	DDP_COMPONENT_DPI1,
	DDP_COMPONENT_PWM1,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt2712_mtk_ddp_third[] = अणु
	DDP_COMPONENT_RDMA2,
	DDP_COMPONENT_DSI3,
	DDP_COMPONENT_PWM2,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt8173_mtk_ddp_मुख्य[] = अणु
	DDP_COMPONENT_OVL0,
	DDP_COMPONENT_COLOR0,
	DDP_COMPONENT_AAL0,
	DDP_COMPONENT_OD0,
	DDP_COMPONENT_RDMA0,
	DDP_COMPONENT_UFOE,
	DDP_COMPONENT_DSI0,
	DDP_COMPONENT_PWM0,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt8173_mtk_ddp_ext[] = अणु
	DDP_COMPONENT_OVL1,
	DDP_COMPONENT_COLOR1,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_RDMA1,
	DDP_COMPONENT_DPI0,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt8183_mtk_ddp_मुख्य[] = अणु
	DDP_COMPONENT_OVL0,
	DDP_COMPONENT_OVL_2L0,
	DDP_COMPONENT_RDMA0,
	DDP_COMPONENT_COLOR0,
	DDP_COMPONENT_CCORR,
	DDP_COMPONENT_AAL0,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_DITHER,
	DDP_COMPONENT_DSI0,
पूर्ण;

अटल स्थिर क्रमागत mtk_ddp_comp_id mt8183_mtk_ddp_ext[] = अणु
	DDP_COMPONENT_OVL_2L1,
	DDP_COMPONENT_RDMA1,
	DDP_COMPONENT_DPI0,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt2701_mmsys_driver_data = अणु
	.मुख्य_path = mt2701_mtk_ddp_मुख्य,
	.मुख्य_len = ARRAY_SIZE(mt2701_mtk_ddp_मुख्य),
	.ext_path = mt2701_mtk_ddp_ext,
	.ext_len = ARRAY_SIZE(mt2701_mtk_ddp_ext),
	.shaकरोw_रेजिस्टर = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt7623_mmsys_driver_data = अणु
	.मुख्य_path = mt7623_mtk_ddp_मुख्य,
	.मुख्य_len = ARRAY_SIZE(mt7623_mtk_ddp_मुख्य),
	.ext_path = mt7623_mtk_ddp_ext,
	.ext_len = ARRAY_SIZE(mt7623_mtk_ddp_ext),
	.shaकरोw_रेजिस्टर = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt2712_mmsys_driver_data = अणु
	.मुख्य_path = mt2712_mtk_ddp_मुख्य,
	.मुख्य_len = ARRAY_SIZE(mt2712_mtk_ddp_मुख्य),
	.ext_path = mt2712_mtk_ddp_ext,
	.ext_len = ARRAY_SIZE(mt2712_mtk_ddp_ext),
	.third_path = mt2712_mtk_ddp_third,
	.third_len = ARRAY_SIZE(mt2712_mtk_ddp_third),
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt8173_mmsys_driver_data = अणु
	.मुख्य_path = mt8173_mtk_ddp_मुख्य,
	.मुख्य_len = ARRAY_SIZE(mt8173_mtk_ddp_मुख्य),
	.ext_path = mt8173_mtk_ddp_ext,
	.ext_len = ARRAY_SIZE(mt8173_mtk_ddp_ext),
पूर्ण;

अटल स्थिर काष्ठा mtk_mmsys_driver_data mt8183_mmsys_driver_data = अणु
	.मुख्य_path = mt8183_mtk_ddp_मुख्य,
	.मुख्य_len = ARRAY_SIZE(mt8183_mtk_ddp_मुख्य),
	.ext_path = mt8183_mtk_ddp_ext,
	.ext_len = ARRAY_SIZE(mt8183_mtk_ddp_ext),
पूर्ण;

अटल पूर्णांक mtk_drm_kms_init(काष्ठा drm_device *drm)
अणु
	काष्ठा mtk_drm_निजी *निजी = drm->dev_निजी;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np;
	काष्ठा device *dma_dev;
	पूर्णांक ret;

	अगर (!iommu_present(&platक्रमm_bus_type))
		वापस -EPROBE_DEFER;

	pdev = of_find_device_by_node(निजी->mutex_node);
	अगर (!pdev) अणु
		dev_err(drm->dev, "Waiting for disp-mutex device %pOF\n",
			निजी->mutex_node);
		of_node_put(निजी->mutex_node);
		वापस -EPROBE_DEFER;
	पूर्ण
	निजी->mutex_dev = &pdev->dev;

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		जाओ put_mutex_dev;

	drm->mode_config.min_width = 64;
	drm->mode_config.min_height = 64;

	/*
	 * set max width and height as शेष value(4096x4096).
	 * this value would be used to check framebuffer size limitation
	 * at drm_mode_addfb().
	 */
	drm->mode_config.max_width = 4096;
	drm->mode_config.max_height = 4096;
	drm->mode_config.funcs = &mtk_drm_mode_config_funcs;
	drm->mode_config.helper_निजी = &mtk_drm_mode_config_helpers;

	ret = component_bind_all(drm->dev, drm);
	अगर (ret)
		जाओ put_mutex_dev;

	/*
	 * We currently support two fixed data streams, each optional,
	 * and each अटलally asचिन्हित to a crtc:
	 * OVL0 -> COLOR0 -> AAL -> OD -> RDMA0 -> UFOE -> DSI0 ...
	 */
	ret = mtk_drm_crtc_create(drm, निजी->data->मुख्य_path,
				  निजी->data->मुख्य_len);
	अगर (ret < 0)
		जाओ err_component_unbind;
	/* ... and OVL1 -> COLOR1 -> GAMMA -> RDMA1 -> DPI0. */
	ret = mtk_drm_crtc_create(drm, निजी->data->ext_path,
				  निजी->data->ext_len);
	अगर (ret < 0)
		जाओ err_component_unbind;

	ret = mtk_drm_crtc_create(drm, निजी->data->third_path,
				  निजी->data->third_len);
	अगर (ret < 0)
		जाओ err_component_unbind;

	/* Use OVL device क्रम all DMA memory allocations */
	np = निजी->comp_node[निजी->data->मुख्य_path[0]] ?:
	     निजी->comp_node[निजी->data->ext_path[0]];
	pdev = of_find_device_by_node(np);
	अगर (!pdev) अणु
		ret = -ENODEV;
		dev_err(drm->dev, "Need at least one OVL device\n");
		जाओ err_component_unbind;
	पूर्ण

	dma_dev = &pdev->dev;
	निजी->dma_dev = dma_dev;

	/*
	 * Configure the DMA segment size to make sure we get contiguous IOVA
	 * when importing PRIME buffers.
	 */
	ret = dma_set_max_seg_size(dma_dev, अच_पूर्णांक_उच्च);
	अगर (ret) अणु
		dev_err(dma_dev, "Failed to set DMA segment size\n");
		जाओ err_component_unbind;
	पूर्ण

	/*
	 * We करोn't use the drm_irq_install() helpers provided by the DRM
	 * core, so we need to set this manually in order to allow the
	 * DRM_IOCTL_WAIT_VBLANK to operate correctly.
	 */
	drm->irq_enabled = true;
	ret = drm_vblank_init(drm, MAX_CRTC);
	अगर (ret < 0)
		जाओ err_component_unbind;

	drm_kms_helper_poll_init(drm);
	drm_mode_config_reset(drm);

	वापस 0;

err_component_unbind:
	component_unbind_all(drm->dev, drm);
put_mutex_dev:
	put_device(निजी->mutex_dev);
	वापस ret;
पूर्ण

अटल व्योम mtk_drm_kms_deinit(काष्ठा drm_device *drm)
अणु
	drm_kms_helper_poll_fini(drm);
	drm_atomic_helper_shutकरोwn(drm);

	component_unbind_all(drm->dev, drm);
पूर्ण

अटल स्थिर काष्ठा file_operations mtk_drm_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = drm_ioctl,
	.mmap = mtk_drm_gem_mmap,
	.poll = drm_poll,
	.पढ़ो = drm_पढ़ो,
	.compat_ioctl = drm_compat_ioctl,
पूर्ण;

/*
 * We need to override this because the device used to import the memory is
 * not dev->dev, as drm_gem_prime_import() expects.
 */
अटल काष्ठा drm_gem_object *mtk_drm_gem_prime_import(काष्ठा drm_device *dev,
						       काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा mtk_drm_निजी *निजी = dev->dev_निजी;

	वापस drm_gem_prime_import_dev(dev, dma_buf, निजी->dma_dev);
पूर्ण

अटल स्थिर काष्ठा drm_driver mtk_drm_driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,

	.dumb_create = mtk_drm_gem_dumb_create,

	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import = mtk_drm_gem_prime_import,
	.gem_prime_import_sg_table = mtk_gem_prime_import_sg_table,
	.gem_prime_mmap = mtk_drm_gem_mmap_buf,
	.fops = &mtk_drm_fops,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
पूर्ण;

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

अटल पूर्णांक mtk_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा mtk_drm_निजी *निजी = dev_get_drvdata(dev);
	काष्ठा drm_device *drm;
	पूर्णांक ret;

	drm = drm_dev_alloc(&mtk_drm_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	drm->dev_निजी = निजी;
	निजी->drm = drm;

	ret = mtk_drm_kms_init(drm);
	अगर (ret < 0)
		जाओ err_मुक्त;

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret < 0)
		जाओ err_deinit;

	drm_fbdev_generic_setup(drm, 32);

	वापस 0;

err_deinit:
	mtk_drm_kms_deinit(drm);
err_मुक्त:
	drm_dev_put(drm);
	वापस ret;
पूर्ण

अटल व्योम mtk_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा mtk_drm_निजी *निजी = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(निजी->drm);
	mtk_drm_kms_deinit(निजी->drm);
	drm_dev_put(निजी->drm);
	निजी->num_pipes = 0;
	निजी->drm = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_master_ops mtk_drm_ops = अणु
	.bind		= mtk_drm_bind,
	.unbind		= mtk_drm_unbind,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_ddp_comp_dt_ids[] = अणु
	अणु .compatible = "mediatek,mt2701-disp-ovl",
	  .data = (व्योम *)MTK_DISP_OVL पूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-ovl",
	  .data = (व्योम *)MTK_DISP_OVL पूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-ovl",
	  .data = (व्योम *)MTK_DISP_OVL पूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-ovl-2l",
	  .data = (व्योम *)MTK_DISP_OVL_2L पूर्ण,
	अणु .compatible = "mediatek,mt2701-disp-rdma",
	  .data = (व्योम *)MTK_DISP_RDMA पूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-rdma",
	  .data = (व्योम *)MTK_DISP_RDMA पूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-rdma",
	  .data = (व्योम *)MTK_DISP_RDMA पूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-wdma",
	  .data = (व्योम *)MTK_DISP_WDMA पूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-ccorr",
	  .data = (व्योम *)MTK_DISP_CCORR पूर्ण,
	अणु .compatible = "mediatek,mt2701-disp-color",
	  .data = (व्योम *)MTK_DISP_COLOR पूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-color",
	  .data = (व्योम *)MTK_DISP_COLOR पूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-aal",
	  .data = (व्योम *)MTK_DISP_AALपूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-gamma",
	  .data = (व्योम *)MTK_DISP_GAMMA, पूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-gamma",
	  .data = (व्योम *)MTK_DISP_GAMMA, पूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-dither",
	  .data = (व्योम *)MTK_DISP_DITHER पूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-ufoe",
	  .data = (व्योम *)MTK_DISP_UFOE पूर्ण,
	अणु .compatible = "mediatek,mt2701-dsi",
	  .data = (व्योम *)MTK_DSI पूर्ण,
	अणु .compatible = "mediatek,mt8173-dsi",
	  .data = (व्योम *)MTK_DSI पूर्ण,
	अणु .compatible = "mediatek,mt8183-dsi",
	  .data = (व्योम *)MTK_DSI पूर्ण,
	अणु .compatible = "mediatek,mt2701-dpi",
	  .data = (व्योम *)MTK_DPI पूर्ण,
	अणु .compatible = "mediatek,mt8173-dpi",
	  .data = (व्योम *)MTK_DPI पूर्ण,
	अणु .compatible = "mediatek,mt8183-dpi",
	  .data = (व्योम *)MTK_DPI पूर्ण,
	अणु .compatible = "mediatek,mt2701-disp-mutex",
	  .data = (व्योम *)MTK_DISP_MUTEX पूर्ण,
	अणु .compatible = "mediatek,mt2712-disp-mutex",
	  .data = (व्योम *)MTK_DISP_MUTEX पूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-mutex",
	  .data = (व्योम *)MTK_DISP_MUTEX पूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-mutex",
	  .data = (व्योम *)MTK_DISP_MUTEX पूर्ण,
	अणु .compatible = "mediatek,mt2701-disp-pwm",
	  .data = (व्योम *)MTK_DISP_BLS पूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-pwm",
	  .data = (व्योम *)MTK_DISP_PWM पूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-od",
	  .data = (व्योम *)MTK_DISP_OD पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_drm_of_ids[] = अणु
	अणु .compatible = "mediatek,mt2701-mmsys",
	  .data = &mt2701_mmsys_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt7623-mmsys",
	  .data = &mt7623_mmsys_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt2712-mmsys",
	  .data = &mt2712_mmsys_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8173-mmsys",
	  .data = &mt8173_mmsys_driver_dataपूर्ण,
	अणु .compatible = "mediatek,mt8183-mmsys",
	  .data = &mt8183_mmsys_driver_dataपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_drm_of_ids);

अटल पूर्णांक mtk_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *phandle = dev->parent->of_node;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा mtk_drm_निजी *निजी;
	काष्ठा device_node *node;
	काष्ठा component_match *match = शून्य;
	पूर्णांक ret;
	पूर्णांक i;

	निजी = devm_kzalloc(dev, माप(*निजी), GFP_KERNEL);
	अगर (!निजी)
		वापस -ENOMEM;

	निजी->mmsys_dev = dev->parent;
	अगर (!निजी->mmsys_dev) अणु
		dev_err(dev, "Failed to get MMSYS device\n");
		वापस -ENODEV;
	पूर्ण

	of_id = of_match_node(mtk_drm_of_ids, phandle);
	अगर (!of_id)
		वापस -ENODEV;

	निजी->data = of_id->data;

	/* Iterate over sibling DISP function blocks */
	क्रम_each_child_of_node(phandle->parent, node) अणु
		स्थिर काष्ठा of_device_id *of_id;
		क्रमागत mtk_ddp_comp_type comp_type;
		पूर्णांक comp_id;

		of_id = of_match_node(mtk_ddp_comp_dt_ids, node);
		अगर (!of_id)
			जारी;

		अगर (!of_device_is_available(node)) अणु
			dev_dbg(dev, "Skipping disabled component %pOF\n",
				node);
			जारी;
		पूर्ण

		comp_type = (क्रमागत mtk_ddp_comp_type)of_id->data;

		अगर (comp_type == MTK_DISP_MUTEX) अणु
			निजी->mutex_node = of_node_get(node);
			जारी;
		पूर्ण

		comp_id = mtk_ddp_comp_get_id(node, comp_type);
		अगर (comp_id < 0) अणु
			dev_warn(dev, "Skipping unknown component %pOF\n",
				 node);
			जारी;
		पूर्ण

		निजी->comp_node[comp_id] = of_node_get(node);

		/*
		 * Currently only the CCORR, COLOR, GAMMA, OVL, RDMA, DSI, and DPI
		 * blocks have separate component platक्रमm drivers and initialize their own
		 * DDP component काष्ठाure. The others are initialized here.
		 */
		अगर (comp_type == MTK_DISP_CCORR ||
		    comp_type == MTK_DISP_COLOR ||
		    comp_type == MTK_DISP_GAMMA ||
		    comp_type == MTK_DISP_OVL ||
		    comp_type == MTK_DISP_OVL_2L ||
		    comp_type == MTK_DISP_RDMA ||
		    comp_type == MTK_DSI ||
		    comp_type == MTK_DPI) अणु
			dev_info(dev, "Adding component match for %pOF\n",
				 node);
			drm_of_component_match_add(dev, &match, compare_of,
						   node);
		पूर्ण

		ret = mtk_ddp_comp_init(node, &निजी->ddp_comp[comp_id], comp_id);
		अगर (ret) अणु
			of_node_put(node);
			जाओ err_node;
		पूर्ण
	पूर्ण

	अगर (!निजी->mutex_node) अणु
		dev_err(dev, "Failed to find disp-mutex node\n");
		ret = -ENODEV;
		जाओ err_node;
	पूर्ण

	pm_runसमय_enable(dev);

	platक्रमm_set_drvdata(pdev, निजी);

	ret = component_master_add_with_match(dev, &mtk_drm_ops, match);
	अगर (ret)
		जाओ err_pm;

	वापस 0;

err_pm:
	pm_runसमय_disable(dev);
err_node:
	of_node_put(निजी->mutex_node);
	क्रम (i = 0; i < DDP_COMPONENT_ID_MAX; i++) अणु
		of_node_put(निजी->comp_node[i]);
		अगर (निजी->ddp_comp[i].larb_dev)
			put_device(निजी->ddp_comp[i].larb_dev);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_drm_निजी *निजी = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	component_master_del(&pdev->dev, &mtk_drm_ops);
	pm_runसमय_disable(&pdev->dev);
	of_node_put(निजी->mutex_node);
	क्रम (i = 0; i < DDP_COMPONENT_ID_MAX; i++)
		of_node_put(निजी->comp_node[i]);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_drm_sys_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_drm_निजी *निजी = dev_get_drvdata(dev);
	काष्ठा drm_device *drm = निजी->drm;
	पूर्णांक ret;

	ret = drm_mode_config_helper_suspend(drm);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_drm_sys_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_drm_निजी *निजी = dev_get_drvdata(dev);
	काष्ठा drm_device *drm = निजी->drm;
	पूर्णांक ret;

	ret = drm_mode_config_helper_resume(drm);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mtk_drm_pm_ops, mtk_drm_sys_suspend,
			 mtk_drm_sys_resume);

अटल काष्ठा platक्रमm_driver mtk_drm_platक्रमm_driver = अणु
	.probe	= mtk_drm_probe,
	.हटाओ	= mtk_drm_हटाओ,
	.driver	= अणु
		.name	= "mediatek-drm",
		.pm     = &mtk_drm_pm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर mtk_drm_drivers[] = अणु
	&mtk_disp_ccorr_driver,
	&mtk_disp_color_driver,
	&mtk_disp_gamma_driver,
	&mtk_disp_ovl_driver,
	&mtk_disp_rdma_driver,
	&mtk_dpi_driver,
	&mtk_drm_platक्रमm_driver,
	&mtk_dsi_driver,
पूर्ण;

अटल पूर्णांक __init mtk_drm_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(mtk_drm_drivers,
					 ARRAY_SIZE(mtk_drm_drivers));
पूर्ण

अटल व्योम __निकास mtk_drm_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(mtk_drm_drivers,
				    ARRAY_SIZE(mtk_drm_drivers));
पूर्ण

module_init(mtk_drm_init);
module_निकास(mtk_drm_निकास);

MODULE_AUTHOR("YT SHEN <yt.shen@mediatek.com>");
MODULE_DESCRIPTION("Mediatek SoC DRM driver");
MODULE_LICENSE("GPL v2");
