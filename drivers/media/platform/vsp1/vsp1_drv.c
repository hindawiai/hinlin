<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_drv.c  --  R-Car VSP1 Driver
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/videodev2.h>

#समावेश <media/rcar-fcp.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_brx.h"
#समावेश "vsp1_clu.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_drm.h"
#समावेश "vsp1_hgo.h"
#समावेश "vsp1_hgt.h"
#समावेश "vsp1_hsit.h"
#समावेश "vsp1_lif.h"
#समावेश "vsp1_lut.h"
#समावेश "vsp1_pipe.h"
#समावेश "vsp1_rwpf.h"
#समावेश "vsp1_sru.h"
#समावेश "vsp1_uds.h"
#समावेश "vsp1_uif.h"
#समावेश "vsp1_video.h"

/* -----------------------------------------------------------------------------
 * Interrupt Handling
 */

अटल irqवापस_t vsp1_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	u32 mask = VI6_WFP_IRQ_STA_DFE | VI6_WFP_IRQ_STA_FRE;
	काष्ठा vsp1_device *vsp1 = data;
	irqवापस_t ret = IRQ_NONE;
	अचिन्हित पूर्णांक i;
	u32 status;

	क्रम (i = 0; i < vsp1->info->wpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *wpf = vsp1->wpf[i];

		अगर (wpf == शून्य)
			जारी;

		status = vsp1_पढ़ो(vsp1, VI6_WPF_IRQ_STA(i));
		vsp1_ग_लिखो(vsp1, VI6_WPF_IRQ_STA(i), ~status & mask);

		अगर (status & VI6_WFP_IRQ_STA_DFE) अणु
			vsp1_pipeline_frame_end(wpf->entity.pipe);
			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Entities
 */

/*
 * vsp1_create_sink_links - Create links from all sources to the given sink
 *
 * This function creates media links from all valid sources to the given sink
 * pad. Links that would be invalid according to the VSP1 hardware capabilities
 * are skipped. Those include all links
 *
 * - from a UDS to a UDS (UDS entities can't be chained)
 * - from an entity to itself (no loops are allowed)
 *
 * Furthermore, the BRS can't be connected to histogram generators, but no
 * special check is currently needed as all VSP instances that include a BRS
 * have no histogram generator.
 */
अटल पूर्णांक vsp1_create_sink_links(काष्ठा vsp1_device *vsp1,
				  काष्ठा vsp1_entity *sink)
अणु
	काष्ठा media_entity *entity = &sink->subdev.entity;
	काष्ठा vsp1_entity *source;
	अचिन्हित पूर्णांक pad;
	पूर्णांक ret;

	list_क्रम_each_entry(source, &vsp1->entities, list_dev) अणु
		u32 flags;

		अगर (source->type == sink->type)
			जारी;

		अगर (source->type == VSP1_ENTITY_HGO ||
		    source->type == VSP1_ENTITY_HGT ||
		    source->type == VSP1_ENTITY_LIF ||
		    source->type == VSP1_ENTITY_WPF)
			जारी;

		flags = source->type == VSP1_ENTITY_RPF &&
			sink->type == VSP1_ENTITY_WPF &&
			source->index == sink->index
		      ? MEDIA_LNK_FL_ENABLED : 0;

		क्रम (pad = 0; pad < entity->num_pads; ++pad) अणु
			अगर (!(entity->pads[pad].flags & MEDIA_PAD_FL_SINK))
				जारी;

			ret = media_create_pad_link(&source->subdev.entity,
						       source->source_pad,
						       entity, pad, flags);
			अगर (ret < 0)
				वापस ret;

			अगर (flags & MEDIA_LNK_FL_ENABLED)
				source->sink = sink;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsp1_uapi_create_links(काष्ठा vsp1_device *vsp1)
अणु
	काष्ठा vsp1_entity *entity;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	list_क्रम_each_entry(entity, &vsp1->entities, list_dev) अणु
		अगर (entity->type == VSP1_ENTITY_LIF ||
		    entity->type == VSP1_ENTITY_RPF)
			जारी;

		ret = vsp1_create_sink_links(vsp1, entity);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (vsp1->hgo) अणु
		ret = media_create_pad_link(&vsp1->hgo->histo.entity.subdev.entity,
					    HISTO_PAD_SOURCE,
					    &vsp1->hgo->histo.video.entity, 0,
					    MEDIA_LNK_FL_ENABLED |
					    MEDIA_LNK_FL_IMMUTABLE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (vsp1->hgt) अणु
		ret = media_create_pad_link(&vsp1->hgt->histo.entity.subdev.entity,
					    HISTO_PAD_SOURCE,
					    &vsp1->hgt->histo.video.entity, 0,
					    MEDIA_LNK_FL_ENABLED |
					    MEDIA_LNK_FL_IMMUTABLE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < vsp1->info->lअगर_count; ++i) अणु
		अगर (!vsp1->lअगर[i])
			जारी;

		ret = media_create_pad_link(&vsp1->wpf[i]->entity.subdev.entity,
					    RWPF_PAD_SOURCE,
					    &vsp1->lअगर[i]->entity.subdev.entity,
					    LIF_PAD_SINK, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < vsp1->info->rpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *rpf = vsp1->rpf[i];

		ret = media_create_pad_link(&rpf->video->video.entity, 0,
					    &rpf->entity.subdev.entity,
					    RWPF_PAD_SINK,
					    MEDIA_LNK_FL_ENABLED |
					    MEDIA_LNK_FL_IMMUTABLE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < vsp1->info->wpf_count; ++i) अणु
		/*
		 * Connect the video device to the WPF. All connections are
		 * immutable.
		 */
		काष्ठा vsp1_rwpf *wpf = vsp1->wpf[i];

		ret = media_create_pad_link(&wpf->entity.subdev.entity,
					    RWPF_PAD_SOURCE,
					    &wpf->video->video.entity, 0,
					    MEDIA_LNK_FL_IMMUTABLE |
					    MEDIA_LNK_FL_ENABLED);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vsp1_destroy_entities(काष्ठा vsp1_device *vsp1)
अणु
	काष्ठा vsp1_entity *entity, *_entity;
	काष्ठा vsp1_video *video, *_video;

	list_क्रम_each_entry_safe(entity, _entity, &vsp1->entities, list_dev) अणु
		list_del(&entity->list_dev);
		vsp1_entity_destroy(entity);
	पूर्ण

	list_क्रम_each_entry_safe(video, _video, &vsp1->videos, list) अणु
		list_del(&video->list);
		vsp1_video_cleanup(video);
	पूर्ण

	v4l2_device_unरेजिस्टर(&vsp1->v4l2_dev);
	अगर (vsp1->info->uapi)
		media_device_unरेजिस्टर(&vsp1->media_dev);
	media_device_cleanup(&vsp1->media_dev);

	अगर (!vsp1->info->uapi)
		vsp1_drm_cleanup(vsp1);
पूर्ण

अटल पूर्णांक vsp1_create_entities(काष्ठा vsp1_device *vsp1)
अणु
	काष्ठा media_device *mdev = &vsp1->media_dev;
	काष्ठा v4l2_device *vdev = &vsp1->v4l2_dev;
	काष्ठा vsp1_entity *entity;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	mdev->dev = vsp1->dev;
	mdev->hw_revision = vsp1->version;
	strscpy(mdev->model, vsp1->info->model, माप(mdev->model));
	snम_लिखो(mdev->bus_info, माप(mdev->bus_info), "platform:%s",
		 dev_name(mdev->dev));
	media_device_init(mdev);

	vsp1->media_ops.link_setup = vsp1_entity_link_setup;
	/*
	 * Don't perक्रमm link validation when the userspace API is disabled as
	 * the pipeline is configured पूर्णांकernally by the driver in that हाल, and
	 * its configuration can thus be trusted.
	 */
	अगर (vsp1->info->uapi)
		vsp1->media_ops.link_validate = v4l2_subdev_link_validate;

	vdev->mdev = mdev;
	ret = v4l2_device_रेजिस्टर(vsp1->dev, vdev);
	अगर (ret < 0) अणु
		dev_err(vsp1->dev, "V4L2 device registration failed (%d)\n",
			ret);
		जाओ करोne;
	पूर्ण

	/* Instantiate all the entities. */
	अगर (vsp1_feature(vsp1, VSP1_HAS_BRS)) अणु
		vsp1->brs = vsp1_brx_create(vsp1, VSP1_ENTITY_BRS);
		अगर (IS_ERR(vsp1->brs)) अणु
			ret = PTR_ERR(vsp1->brs);
			जाओ करोne;
		पूर्ण

		list_add_tail(&vsp1->brs->entity.list_dev, &vsp1->entities);
	पूर्ण

	अगर (vsp1_feature(vsp1, VSP1_HAS_BRU)) अणु
		vsp1->bru = vsp1_brx_create(vsp1, VSP1_ENTITY_BRU);
		अगर (IS_ERR(vsp1->bru)) अणु
			ret = PTR_ERR(vsp1->bru);
			जाओ करोne;
		पूर्ण

		list_add_tail(&vsp1->bru->entity.list_dev, &vsp1->entities);
	पूर्ण

	अगर (vsp1_feature(vsp1, VSP1_HAS_CLU)) अणु
		vsp1->clu = vsp1_clu_create(vsp1);
		अगर (IS_ERR(vsp1->clu)) अणु
			ret = PTR_ERR(vsp1->clu);
			जाओ करोne;
		पूर्ण

		list_add_tail(&vsp1->clu->entity.list_dev, &vsp1->entities);
	पूर्ण

	vsp1->hsi = vsp1_hsit_create(vsp1, true);
	अगर (IS_ERR(vsp1->hsi)) अणु
		ret = PTR_ERR(vsp1->hsi);
		जाओ करोne;
	पूर्ण

	list_add_tail(&vsp1->hsi->entity.list_dev, &vsp1->entities);

	vsp1->hst = vsp1_hsit_create(vsp1, false);
	अगर (IS_ERR(vsp1->hst)) अणु
		ret = PTR_ERR(vsp1->hst);
		जाओ करोne;
	पूर्ण

	list_add_tail(&vsp1->hst->entity.list_dev, &vsp1->entities);

	अगर (vsp1_feature(vsp1, VSP1_HAS_HGO) && vsp1->info->uapi) अणु
		vsp1->hgo = vsp1_hgo_create(vsp1);
		अगर (IS_ERR(vsp1->hgo)) अणु
			ret = PTR_ERR(vsp1->hgo);
			जाओ करोne;
		पूर्ण

		list_add_tail(&vsp1->hgo->histo.entity.list_dev,
			      &vsp1->entities);
	पूर्ण

	अगर (vsp1_feature(vsp1, VSP1_HAS_HGT) && vsp1->info->uapi) अणु
		vsp1->hgt = vsp1_hgt_create(vsp1);
		अगर (IS_ERR(vsp1->hgt)) अणु
			ret = PTR_ERR(vsp1->hgt);
			जाओ करोne;
		पूर्ण

		list_add_tail(&vsp1->hgt->histo.entity.list_dev,
			      &vsp1->entities);
	पूर्ण

	/*
	 * The LIFs are only supported when used in conjunction with the DU, in
	 * which हाल the userspace API is disabled. If the userspace API is
	 * enabled skip the LIFs, even when present.
	 */
	अगर (!vsp1->info->uapi) अणु
		क्रम (i = 0; i < vsp1->info->lअगर_count; ++i) अणु
			काष्ठा vsp1_lअगर *lअगर;

			lअगर = vsp1_lअगर_create(vsp1, i);
			अगर (IS_ERR(lअगर)) अणु
				ret = PTR_ERR(lअगर);
				जाओ करोne;
			पूर्ण

			vsp1->lअगर[i] = lअगर;
			list_add_tail(&lअगर->entity.list_dev, &vsp1->entities);
		पूर्ण
	पूर्ण

	अगर (vsp1_feature(vsp1, VSP1_HAS_LUT)) अणु
		vsp1->lut = vsp1_lut_create(vsp1);
		अगर (IS_ERR(vsp1->lut)) अणु
			ret = PTR_ERR(vsp1->lut);
			जाओ करोne;
		पूर्ण

		list_add_tail(&vsp1->lut->entity.list_dev, &vsp1->entities);
	पूर्ण

	क्रम (i = 0; i < vsp1->info->rpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *rpf;

		rpf = vsp1_rpf_create(vsp1, i);
		अगर (IS_ERR(rpf)) अणु
			ret = PTR_ERR(rpf);
			जाओ करोne;
		पूर्ण

		vsp1->rpf[i] = rpf;
		list_add_tail(&rpf->entity.list_dev, &vsp1->entities);

		अगर (vsp1->info->uapi) अणु
			काष्ठा vsp1_video *video = vsp1_video_create(vsp1, rpf);

			अगर (IS_ERR(video)) अणु
				ret = PTR_ERR(video);
				जाओ करोne;
			पूर्ण

			list_add_tail(&video->list, &vsp1->videos);
		पूर्ण
	पूर्ण

	अगर (vsp1_feature(vsp1, VSP1_HAS_SRU)) अणु
		vsp1->sru = vsp1_sru_create(vsp1);
		अगर (IS_ERR(vsp1->sru)) अणु
			ret = PTR_ERR(vsp1->sru);
			जाओ करोne;
		पूर्ण

		list_add_tail(&vsp1->sru->entity.list_dev, &vsp1->entities);
	पूर्ण

	क्रम (i = 0; i < vsp1->info->uds_count; ++i) अणु
		काष्ठा vsp1_uds *uds;

		uds = vsp1_uds_create(vsp1, i);
		अगर (IS_ERR(uds)) अणु
			ret = PTR_ERR(uds);
			जाओ करोne;
		पूर्ण

		vsp1->uds[i] = uds;
		list_add_tail(&uds->entity.list_dev, &vsp1->entities);
	पूर्ण

	क्रम (i = 0; i < vsp1->info->uअगर_count; ++i) अणु
		काष्ठा vsp1_uअगर *uअगर;

		uअगर = vsp1_uअगर_create(vsp1, i);
		अगर (IS_ERR(uअगर)) अणु
			ret = PTR_ERR(uअगर);
			जाओ करोne;
		पूर्ण

		vsp1->uअगर[i] = uअगर;
		list_add_tail(&uअगर->entity.list_dev, &vsp1->entities);
	पूर्ण

	क्रम (i = 0; i < vsp1->info->wpf_count; ++i) अणु
		काष्ठा vsp1_rwpf *wpf;

		wpf = vsp1_wpf_create(vsp1, i);
		अगर (IS_ERR(wpf)) अणु
			ret = PTR_ERR(wpf);
			जाओ करोne;
		पूर्ण

		vsp1->wpf[i] = wpf;
		list_add_tail(&wpf->entity.list_dev, &vsp1->entities);

		अगर (vsp1->info->uapi) अणु
			काष्ठा vsp1_video *video = vsp1_video_create(vsp1, wpf);

			अगर (IS_ERR(video)) अणु
				ret = PTR_ERR(video);
				जाओ करोne;
			पूर्ण

			list_add_tail(&video->list, &vsp1->videos);
		पूर्ण
	पूर्ण

	/* Register all subdevs. */
	list_क्रम_each_entry(entity, &vsp1->entities, list_dev) अणु
		ret = v4l2_device_रेजिस्टर_subdev(&vsp1->v4l2_dev,
						  &entity->subdev);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	/*
	 * Create links and रेजिस्टर subdev nodes अगर the userspace API is
	 * enabled or initialize the DRM pipeline otherwise.
	 */
	अगर (vsp1->info->uapi) अणु
		ret = vsp1_uapi_create_links(vsp1);
		अगर (ret < 0)
			जाओ करोne;

		ret = v4l2_device_रेजिस्टर_subdev_nodes(&vsp1->v4l2_dev);
		अगर (ret < 0)
			जाओ करोne;

		ret = media_device_रेजिस्टर(mdev);
	पूर्ण अन्यथा अणु
		ret = vsp1_drm_init(vsp1);
	पूर्ण

करोne:
	अगर (ret < 0)
		vsp1_destroy_entities(vsp1);

	वापस ret;
पूर्ण

पूर्णांक vsp1_reset_wpf(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक समयout;
	u32 status;

	status = vsp1_पढ़ो(vsp1, VI6_STATUS);
	अगर (!(status & VI6_STATUS_SYS_ACT(index)))
		वापस 0;

	vsp1_ग_लिखो(vsp1, VI6_SRESET, VI6_SRESET_SRTS(index));
	क्रम (समयout = 10; समयout > 0; --समयout) अणु
		status = vsp1_पढ़ो(vsp1, VI6_STATUS);
		अगर (!(status & VI6_STATUS_SYS_ACT(index)))
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण

	अगर (!समयout) अणु
		dev_err(vsp1->dev, "failed to reset wpf.%u\n", index);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsp1_device_init(काष्ठा vsp1_device *vsp1)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Reset any channel that might be running. */
	क्रम (i = 0; i < vsp1->info->wpf_count; ++i) अणु
		ret = vsp1_reset_wpf(vsp1, i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	vsp1_ग_लिखो(vsp1, VI6_CLK_DCSWT, (8 << VI6_CLK_DCSWT_CSTPW_SHIFT) |
		   (8 << VI6_CLK_DCSWT_CSTRW_SHIFT));

	क्रम (i = 0; i < vsp1->info->rpf_count; ++i)
		vsp1_ग_लिखो(vsp1, VI6_DPR_RPF_ROUTE(i), VI6_DPR_NODE_UNUSED);

	क्रम (i = 0; i < vsp1->info->uds_count; ++i)
		vsp1_ग_लिखो(vsp1, VI6_DPR_UDS_ROUTE(i), VI6_DPR_NODE_UNUSED);

	क्रम (i = 0; i < vsp1->info->uअगर_count; ++i)
		vsp1_ग_लिखो(vsp1, VI6_DPR_UIF_ROUTE(i), VI6_DPR_NODE_UNUSED);

	vsp1_ग_लिखो(vsp1, VI6_DPR_SRU_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_ग_लिखो(vsp1, VI6_DPR_LUT_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_ग_लिखो(vsp1, VI6_DPR_CLU_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_ग_लिखो(vsp1, VI6_DPR_HST_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_ग_लिखो(vsp1, VI6_DPR_HSI_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_ग_लिखो(vsp1, VI6_DPR_BRU_ROUTE, VI6_DPR_NODE_UNUSED);

	अगर (vsp1_feature(vsp1, VSP1_HAS_BRS))
		vsp1_ग_लिखो(vsp1, VI6_DPR_ILV_BRS_ROUTE, VI6_DPR_NODE_UNUSED);

	vsp1_ग_लिखो(vsp1, VI6_DPR_HGO_SMPPT, (7 << VI6_DPR_SMPPT_TGW_SHIFT) |
		   (VI6_DPR_NODE_UNUSED << VI6_DPR_SMPPT_PT_SHIFT));
	vsp1_ग_लिखो(vsp1, VI6_DPR_HGT_SMPPT, (7 << VI6_DPR_SMPPT_TGW_SHIFT) |
		   (VI6_DPR_NODE_UNUSED << VI6_DPR_SMPPT_PT_SHIFT));

	vsp1_dlm_setup(vsp1);

	वापस 0;
पूर्ण

/*
 * vsp1_device_get - Acquire the VSP1 device
 *
 * Make sure the device is not suspended and initialize it अगर needed.
 *
 * Return 0 on success or a negative error code otherwise.
 */
पूर्णांक vsp1_device_get(काष्ठा vsp1_device *vsp1)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(vsp1->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(vsp1->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vsp1_device_put - Release the VSP1 device
 *
 * Decrement the VSP1 reference count and cleanup the device अगर the last
 * reference is released.
 */
व्योम vsp1_device_put(काष्ठा vsp1_device *vsp1)
अणु
	pm_runसमय_put_sync(vsp1->dev);
पूर्ण

/* -----------------------------------------------------------------------------
 * Power Management
 */

अटल पूर्णांक __maybe_unused vsp1_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);

	/*
	 * When used as part of a display pipeline, the VSP is stopped and
	 * restarted explicitly by the DU.
	 */
	अगर (!vsp1->drm)
		vsp1_video_suspend(vsp1);

	pm_runसमय_क्रमce_suspend(vsp1->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused vsp1_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);

	pm_runसमय_क्रमce_resume(vsp1->dev);

	/*
	 * When used as part of a display pipeline, the VSP is stopped and
	 * restarted explicitly by the DU.
	 */
	अगर (!vsp1->drm)
		vsp1_video_resume(vsp1);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused vsp1_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);

	rcar_fcp_disable(vsp1->fcp);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused vsp1_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा vsp1_device *vsp1 = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (vsp1->info) अणु
		ret = vsp1_device_init(vsp1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस rcar_fcp_enable(vsp1->fcp);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vsp1_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(vsp1_pm_suspend, vsp1_pm_resume)
	SET_RUNTIME_PM_OPS(vsp1_pm_runसमय_suspend, vsp1_pm_runसमय_resume, शून्य)
पूर्ण;

/* -----------------------------------------------------------------------------
 * Platक्रमm Driver
 */

अटल स्थिर काष्ठा vsp1_device_info vsp1_device_infos[] = अणु
	अणु
		.version = VI6_IP_VERSION_MODEL_VSPS_H2,
		.model = "VSP1-S",
		.gen = 2,
		.features = VSP1_HAS_BRU | VSP1_HAS_CLU | VSP1_HAS_HGO
			  | VSP1_HAS_HGT | VSP1_HAS_LUT | VSP1_HAS_SRU
			  | VSP1_HAS_WPF_VFLIP,
		.rpf_count = 5,
		.uds_count = 3,
		.wpf_count = 4,
		.num_bru_inमाला_दो = 4,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPR_H2,
		.model = "VSP1-R",
		.gen = 2,
		.features = VSP1_HAS_BRU | VSP1_HAS_SRU | VSP1_HAS_WPF_VFLIP,
		.rpf_count = 5,
		.uds_count = 3,
		.wpf_count = 4,
		.num_bru_inमाला_दो = 4,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPD_GEN2,
		.model = "VSP1-D",
		.gen = 2,
		.features = VSP1_HAS_BRU | VSP1_HAS_HGO | VSP1_HAS_LUT,
		.lअगर_count = 1,
		.rpf_count = 4,
		.uds_count = 1,
		.wpf_count = 1,
		.num_bru_inमाला_दो = 4,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPS_M2,
		.model = "VSP1-S",
		.gen = 2,
		.features = VSP1_HAS_BRU | VSP1_HAS_CLU | VSP1_HAS_HGO
			  | VSP1_HAS_HGT | VSP1_HAS_LUT | VSP1_HAS_SRU
			  | VSP1_HAS_WPF_VFLIP,
		.rpf_count = 5,
		.uds_count = 1,
		.wpf_count = 4,
		.num_bru_inमाला_दो = 4,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPS_V2H,
		.model = "VSP1V-S",
		.gen = 2,
		.features = VSP1_HAS_BRU | VSP1_HAS_CLU | VSP1_HAS_LUT
			  | VSP1_HAS_SRU | VSP1_HAS_WPF_VFLIP,
		.rpf_count = 4,
		.uds_count = 1,
		.wpf_count = 4,
		.num_bru_inमाला_दो = 4,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPD_V2H,
		.model = "VSP1V-D",
		.gen = 2,
		.features = VSP1_HAS_BRU | VSP1_HAS_CLU | VSP1_HAS_LUT,
		.lअगर_count = 1,
		.rpf_count = 4,
		.uds_count = 1,
		.wpf_count = 1,
		.num_bru_inमाला_दो = 4,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPI_GEN3,
		.model = "VSP2-I",
		.gen = 3,
		.features = VSP1_HAS_CLU | VSP1_HAS_HGO | VSP1_HAS_HGT
			  | VSP1_HAS_LUT | VSP1_HAS_SRU | VSP1_HAS_WPF_HFLIP
			  | VSP1_HAS_WPF_VFLIP,
		.rpf_count = 1,
		.uds_count = 1,
		.wpf_count = 1,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPBD_GEN3,
		.model = "VSP2-BD",
		.gen = 3,
		.features = VSP1_HAS_BRU | VSP1_HAS_WPF_VFLIP,
		.rpf_count = 5,
		.wpf_count = 1,
		.num_bru_inमाला_दो = 5,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPBC_GEN3,
		.model = "VSP2-BC",
		.gen = 3,
		.features = VSP1_HAS_BRU | VSP1_HAS_CLU | VSP1_HAS_HGO
			  | VSP1_HAS_LUT | VSP1_HAS_WPF_VFLIP,
		.rpf_count = 5,
		.wpf_count = 1,
		.num_bru_inमाला_दो = 5,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPBS_GEN3,
		.model = "VSP2-BS",
		.gen = 3,
		.features = VSP1_HAS_BRS | VSP1_HAS_WPF_VFLIP,
		.rpf_count = 2,
		.wpf_count = 1,
		.uapi = true,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPD_GEN3,
		.model = "VSP2-D",
		.gen = 3,
		.features = VSP1_HAS_BRU | VSP1_HAS_WPF_VFLIP | VSP1_HAS_EXT_DL,
		.lअगर_count = 1,
		.rpf_count = 5,
		.uअगर_count = 1,
		.wpf_count = 2,
		.num_bru_inमाला_दो = 5,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPD_V3,
		.model = "VSP2-D",
		.gen = 3,
		.features = VSP1_HAS_BRS | VSP1_HAS_BRU,
		.lअगर_count = 1,
		.rpf_count = 5,
		.uअगर_count = 1,
		.wpf_count = 1,
		.num_bru_inमाला_दो = 5,
	पूर्ण, अणु
		.version = VI6_IP_VERSION_MODEL_VSPDL_GEN3,
		.model = "VSP2-DL",
		.gen = 3,
		.features = VSP1_HAS_BRS | VSP1_HAS_BRU | VSP1_HAS_EXT_DL,
		.lअगर_count = 2,
		.rpf_count = 5,
		.uअगर_count = 2,
		.wpf_count = 2,
		.num_bru_inमाला_दो = 5,
	पूर्ण,
पूर्ण;

अटल पूर्णांक vsp1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vsp1_device *vsp1;
	काष्ठा device_node *fcp_node;
	काष्ठा resource *irq;
	काष्ठा resource *io;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	vsp1 = devm_kzalloc(&pdev->dev, माप(*vsp1), GFP_KERNEL);
	अगर (vsp1 == शून्य)
		वापस -ENOMEM;

	vsp1->dev = &pdev->dev;
	INIT_LIST_HEAD(&vsp1->entities);
	INIT_LIST_HEAD(&vsp1->videos);

	platक्रमm_set_drvdata(pdev, vsp1);

	/* I/O and IRQ resources (घड़ी managed by the घड़ी PM करोमुख्य). */
	io = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	vsp1->mmio = devm_ioremap_resource(&pdev->dev, io);
	अगर (IS_ERR(vsp1->mmio))
		वापस PTR_ERR(vsp1->mmio);

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq) अणु
		dev_err(&pdev->dev, "missing IRQ\n");
		वापस -EINVAL;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq->start, vsp1_irq_handler,
			      IRQF_SHARED, dev_name(&pdev->dev), vsp1);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		वापस ret;
	पूर्ण

	/* FCP (optional). */
	fcp_node = of_parse_phandle(pdev->dev.of_node, "renesas,fcp", 0);
	अगर (fcp_node) अणु
		vsp1->fcp = rcar_fcp_get(fcp_node);
		of_node_put(fcp_node);
		अगर (IS_ERR(vsp1->fcp)) अणु
			dev_dbg(&pdev->dev, "FCP not found (%ld)\n",
				PTR_ERR(vsp1->fcp));
			वापस PTR_ERR(vsp1->fcp);
		पूर्ण

		/*
		 * When the FCP is present, it handles all bus master accesses
		 * क्रम the VSP and must thus be used in place of the VSP device
		 * to map DMA buffers.
		 */
		vsp1->bus_master = rcar_fcp_get_device(vsp1->fcp);
	पूर्ण अन्यथा अणु
		vsp1->bus_master = vsp1->dev;
	पूर्ण

	/* Configure device parameters based on the version रेजिस्टर. */
	pm_runसमय_enable(&pdev->dev);

	ret = vsp1_device_get(vsp1);
	अगर (ret < 0)
		जाओ करोne;

	vsp1->version = vsp1_पढ़ो(vsp1, VI6_IP_VERSION);
	vsp1_device_put(vsp1);

	क्रम (i = 0; i < ARRAY_SIZE(vsp1_device_infos); ++i) अणु
		अगर ((vsp1->version & VI6_IP_VERSION_MODEL_MASK) ==
		    vsp1_device_infos[i].version) अणु
			vsp1->info = &vsp1_device_infos[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!vsp1->info) अणु
		dev_err(&pdev->dev, "unsupported IP version 0x%08x\n",
			vsp1->version);
		ret = -ENXIO;
		जाओ करोne;
	पूर्ण

	dev_dbg(&pdev->dev, "IP version 0x%08x\n", vsp1->version);

	/* Instantiate entities. */
	ret = vsp1_create_entities(vsp1);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to create entities\n");
		जाओ करोne;
	पूर्ण

करोne:
	अगर (ret) अणु
		pm_runसमय_disable(&pdev->dev);
		rcar_fcp_put(vsp1->fcp);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vsp1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vsp1_device *vsp1 = platक्रमm_get_drvdata(pdev);

	vsp1_destroy_entities(vsp1);
	rcar_fcp_put(vsp1->fcp);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vsp1_of_match[] = अणु
	अणु .compatible = "renesas,vsp1" पूर्ण,
	अणु .compatible = "renesas,vsp2" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vsp1_of_match);

अटल काष्ठा platक्रमm_driver vsp1_platक्रमm_driver = अणु
	.probe		= vsp1_probe,
	.हटाओ		= vsp1_हटाओ,
	.driver		= अणु
		.name	= "vsp1",
		.pm	= &vsp1_pm_ops,
		.of_match_table = vsp1_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vsp1_platक्रमm_driver);

MODULE_ALIAS("vsp1");
MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Renesas VSP1 Driver");
MODULE_LICENSE("GPL");
