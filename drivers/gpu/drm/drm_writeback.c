<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2016 ARM Limited. All rights reserved.
 * Author: Brian Starkey <brian.starkey@arm.com>
 *
 * This program is मुक्त software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 */

#समावेश <linux/dma-fence.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_property.h>
#समावेश <drm/drm_ग_लिखोback.h>

/**
 * DOC: overview
 *
 * Writeback connectors are used to expose hardware which can ग_लिखो the output
 * from a CRTC to a memory buffer. They are used and act similarly to other
 * types of connectors, with some important dअगरferences:
 *
 * * Writeback connectors करोn't provide a way to output visually to the user.
 *
 * * Writeback connectors are visible to userspace only when the client sets
 *   DRM_CLIENT_CAP_WRITEBACK_CONNECTORS.
 *
 * * Writeback connectors करोn't have EDID.
 *
 * A framebuffer may only be attached to a ग_लिखोback connector when the
 * connector is attached to a CRTC. The WRITEBACK_FB_ID property which sets the
 * framebuffer applies only to a single commit (see below). A framebuffer may
 * not be attached जबतक the CRTC is off.
 *
 * Unlike with planes, when a ग_लिखोback framebuffer is हटाओd by userspace DRM
 * makes no attempt to हटाओ it from active use by the connector. This is
 * because no method is provided to पात a ग_लिखोback operation, and in any
 * हाल making a new commit whilst a ग_लिखोback is ongoing is undefined (see
 * WRITEBACK_OUT_FENCE_PTR below). As soon as the current ग_लिखोback is finished,
 * the framebuffer will स्वतःmatically no दीर्घer be in active use. As it will
 * also have alपढ़ोy been हटाओd from the framebuffer list, there will be no
 * way क्रम any userspace application to retrieve a reference to it in the
 * पूर्णांकervening period.
 *
 * Writeback connectors have some additional properties, which userspace
 * can use to query and control them:
 *
 *  "WRITEBACK_FB_ID":
 *	Write-only object property storing a DRM_MODE_OBJECT_FB: it stores the
 *	framebuffer to be written by the ग_लिखोback connector. This property is
 *	similar to the FB_ID property on planes, but will always पढ़ो as zero
 *	and is not preserved across commits.
 *	Userspace must set this property to an output buffer every समय it
 *	wishes the buffer to get filled.
 *
 *  "WRITEBACK_PIXEL_FORMATS":
 *	Immutable blob property to store the supported pixel क्रमmats table. The
 *	data is an array of u32 DRM_FORMAT_* fourcc values.
 *	Userspace can use this blob to find out what pixel क्रमmats are supported
 *	by the connector's ग_लिखोback engine.
 *
 *  "WRITEBACK_OUT_FENCE_PTR":
 *	Userspace can use this property to provide a poपूर्णांकer क्रम the kernel to
 *	fill with a sync_file file descriptor, which will संकेत once the
 *	ग_लिखोback is finished. The value should be the address of a 32-bit
 *	चिन्हित पूर्णांकeger, cast to a u64.
 *	Userspace should रुको क्रम this fence to संकेत beक्रमe making another
 *	commit affecting any of the same CRTCs, Planes or Connectors.
 *	**Failure to करो so will result in undefined behaviour.**
 *	For this reason it is strongly recommended that all userspace
 *	applications making use of ग_लिखोback connectors *always* retrieve an
 *	out-fence क्रम the commit and use it appropriately.
 *	From userspace, this property will always पढ़ो as zero.
 */

#घोषणा fence_to_wb_connector(x) container_of(x->lock, \
					      काष्ठा drm_ग_लिखोback_connector, \
					      fence_lock)

अटल स्थिर अक्षर *drm_ग_लिखोback_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा drm_ग_लिखोback_connector *wb_connector =
		fence_to_wb_connector(fence);

	वापस wb_connector->base.dev->driver->name;
पूर्ण

अटल स्थिर अक्षर *
drm_ग_लिखोback_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा drm_ग_लिखोback_connector *wb_connector =
		fence_to_wb_connector(fence);

	वापस wb_connector->समयline_name;
पूर्ण

अटल bool drm_ग_लिखोback_fence_enable_संकेतing(काष्ठा dma_fence *fence)
अणु
	वापस true;
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops drm_ग_लिखोback_fence_ops = अणु
	.get_driver_name = drm_ग_लिखोback_fence_get_driver_name,
	.get_समयline_name = drm_ग_लिखोback_fence_get_समयline_name,
	.enable_संकेतing = drm_ग_लिखोback_fence_enable_संकेतing,
पूर्ण;

अटल पूर्णांक create_ग_लिखोback_properties(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_property *prop;

	अगर (!dev->mode_config.ग_लिखोback_fb_id_property) अणु
		prop = drm_property_create_object(dev, DRM_MODE_PROP_ATOMIC,
						  "WRITEBACK_FB_ID",
						  DRM_MODE_OBJECT_FB);
		अगर (!prop)
			वापस -ENOMEM;
		dev->mode_config.ग_लिखोback_fb_id_property = prop;
	पूर्ण

	अगर (!dev->mode_config.ग_लिखोback_pixel_क्रमmats_property) अणु
		prop = drm_property_create(dev, DRM_MODE_PROP_BLOB |
					   DRM_MODE_PROP_ATOMIC |
					   DRM_MODE_PROP_IMMUTABLE,
					   "WRITEBACK_PIXEL_FORMATS", 0);
		अगर (!prop)
			वापस -ENOMEM;
		dev->mode_config.ग_लिखोback_pixel_क्रमmats_property = prop;
	पूर्ण

	अगर (!dev->mode_config.ग_लिखोback_out_fence_ptr_property) अणु
		prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
						 "WRITEBACK_OUT_FENCE_PTR", 0,
						 U64_MAX);
		अगर (!prop)
			वापस -ENOMEM;
		dev->mode_config.ग_लिखोback_out_fence_ptr_property = prop;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs drm_ग_लिखोback_encoder_funcs = अणु
	.destroy = drm_encoder_cleanup,
पूर्ण;

/**
 * drm_ग_लिखोback_connector_init - Initialize a ग_लिखोback connector and its properties
 * @dev: DRM device
 * @wb_connector: Writeback connector to initialize
 * @con_funcs: Connector funcs vtable
 * @enc_helper_funcs: Encoder helper funcs vtable to be used by the पूर्णांकernal encoder
 * @क्रमmats: Array of supported pixel क्रमmats क्रम the ग_लिखोback engine
 * @n_क्रमmats: Length of the क्रमmats array
 *
 * This function creates the ग_लिखोback-connector-specअगरic properties अगर they
 * have not been alपढ़ोy created, initializes the connector as
 * type DRM_MODE_CONNECTOR_WRITEBACK, and correctly initializes the property
 * values. It will also create an पूर्णांकernal encoder associated with the
 * drm_ग_लिखोback_connector and set it to use the @enc_helper_funcs vtable क्रम
 * the encoder helper.
 *
 * Drivers should always use this function instead of drm_connector_init() to
 * set up ग_लिखोback connectors.
 *
 * Returns: 0 on success, or a negative error code
 */
पूर्णांक drm_ग_लिखोback_connector_init(काष्ठा drm_device *dev,
				 काष्ठा drm_ग_लिखोback_connector *wb_connector,
				 स्थिर काष्ठा drm_connector_funcs *con_funcs,
				 स्थिर काष्ठा drm_encoder_helper_funcs *enc_helper_funcs,
				 स्थिर u32 *क्रमmats, पूर्णांक n_क्रमmats)
अणु
	काष्ठा drm_property_blob *blob;
	काष्ठा drm_connector *connector = &wb_connector->base;
	काष्ठा drm_mode_config *config = &dev->mode_config;
	पूर्णांक ret = create_ग_लिखोback_properties(dev);

	अगर (ret != 0)
		वापस ret;

	blob = drm_property_create_blob(dev, n_क्रमmats * माप(*क्रमmats),
					क्रमmats);
	अगर (IS_ERR(blob))
		वापस PTR_ERR(blob);

	drm_encoder_helper_add(&wb_connector->encoder, enc_helper_funcs);
	ret = drm_encoder_init(dev, &wb_connector->encoder,
			       &drm_ग_लिखोback_encoder_funcs,
			       DRM_MODE_ENCODER_VIRTUAL, शून्य);
	अगर (ret)
		जाओ fail;

	connector->पूर्णांकerlace_allowed = 0;

	ret = drm_connector_init(dev, connector, con_funcs,
				 DRM_MODE_CONNECTOR_WRITEBACK);
	अगर (ret)
		जाओ connector_fail;

	ret = drm_connector_attach_encoder(connector,
						&wb_connector->encoder);
	अगर (ret)
		जाओ attach_fail;

	INIT_LIST_HEAD(&wb_connector->job_queue);
	spin_lock_init(&wb_connector->job_lock);

	wb_connector->fence_context = dma_fence_context_alloc(1);
	spin_lock_init(&wb_connector->fence_lock);
	snम_लिखो(wb_connector->समयline_name,
		 माप(wb_connector->समयline_name),
		 "CONNECTOR:%d-%s", connector->base.id, connector->name);

	drm_object_attach_property(&connector->base,
				   config->ग_लिखोback_out_fence_ptr_property, 0);

	drm_object_attach_property(&connector->base,
				   config->ग_लिखोback_fb_id_property, 0);

	drm_object_attach_property(&connector->base,
				   config->ग_लिखोback_pixel_क्रमmats_property,
				   blob->base.id);
	wb_connector->pixel_क्रमmats_blob_ptr = blob;

	वापस 0;

attach_fail:
	drm_connector_cleanup(connector);
connector_fail:
	drm_encoder_cleanup(&wb_connector->encoder);
fail:
	drm_property_blob_put(blob);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_ग_लिखोback_connector_init);

पूर्णांक drm_ग_लिखोback_set_fb(काष्ठा drm_connector_state *conn_state,
			 काष्ठा drm_framebuffer *fb)
अणु
	WARN_ON(conn_state->connector->connector_type != DRM_MODE_CONNECTOR_WRITEBACK);

	अगर (!conn_state->ग_लिखोback_job) अणु
		conn_state->ग_लिखोback_job =
			kzalloc(माप(*conn_state->ग_लिखोback_job), GFP_KERNEL);
		अगर (!conn_state->ग_लिखोback_job)
			वापस -ENOMEM;

		conn_state->ग_लिखोback_job->connector =
			drm_connector_to_ग_लिखोback(conn_state->connector);
	पूर्ण

	drm_framebuffer_assign(&conn_state->ग_लिखोback_job->fb, fb);
	वापस 0;
पूर्ण

पूर्णांक drm_ग_लिखोback_prepare_job(काष्ठा drm_ग_लिखोback_job *job)
अणु
	काष्ठा drm_ग_लिखोback_connector *connector = job->connector;
	स्थिर काष्ठा drm_connector_helper_funcs *funcs =
		connector->base.helper_निजी;
	पूर्णांक ret;

	अगर (funcs->prepare_ग_लिखोback_job) अणु
		ret = funcs->prepare_ग_लिखोback_job(connector, job);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	job->prepared = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_ग_लिखोback_prepare_job);

/**
 * drm_ग_लिखोback_queue_job - Queue a ग_लिखोback job क्रम later संकेतling
 * @wb_connector: The ग_लिखोback connector to queue a job on
 * @conn_state: The connector state containing the job to queue
 *
 * This function adds the job contained in @conn_state to the job_queue क्रम a
 * ग_लिखोback connector. It takes ownership of the ग_लिखोback job and sets the
 * @conn_state->ग_लिखोback_job to शून्य, and so no access to the job may be
 * perक्रमmed by the caller after this function वापसs.
 *
 * Drivers must ensure that क्रम a given ग_लिखोback connector, jobs are queued in
 * exactly the same order as they will be completed by the hardware (and
 * संकेतed via drm_ग_लिखोback_संकेत_completion).
 *
 * For every call to drm_ग_लिखोback_queue_job() there must be exactly one call to
 * drm_ग_लिखोback_संकेत_completion()
 *
 * See also: drm_ग_लिखोback_संकेत_completion()
 */
व्योम drm_ग_लिखोback_queue_job(काष्ठा drm_ग_लिखोback_connector *wb_connector,
			     काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_ग_लिखोback_job *job;
	अचिन्हित दीर्घ flags;

	job = conn_state->ग_लिखोback_job;
	conn_state->ग_लिखोback_job = शून्य;

	spin_lock_irqsave(&wb_connector->job_lock, flags);
	list_add_tail(&job->list_entry, &wb_connector->job_queue);
	spin_unlock_irqrestore(&wb_connector->job_lock, flags);
पूर्ण
EXPORT_SYMBOL(drm_ग_लिखोback_queue_job);

व्योम drm_ग_लिखोback_cleanup_job(काष्ठा drm_ग_लिखोback_job *job)
अणु
	काष्ठा drm_ग_लिखोback_connector *connector = job->connector;
	स्थिर काष्ठा drm_connector_helper_funcs *funcs =
		connector->base.helper_निजी;

	अगर (job->prepared && funcs->cleanup_ग_लिखोback_job)
		funcs->cleanup_ग_लिखोback_job(connector, job);

	अगर (job->fb)
		drm_framebuffer_put(job->fb);

	अगर (job->out_fence)
		dma_fence_put(job->out_fence);

	kमुक्त(job);
पूर्ण
EXPORT_SYMBOL(drm_ग_लिखोback_cleanup_job);

/*
 * @cleanup_work: deferred cleanup of a ग_लिखोback job
 *
 * The job cannot be cleaned up directly in drm_ग_लिखोback_संकेत_completion,
 * because it may be called in पूर्णांकerrupt context. Dropping the framebuffer
 * reference can sleep, and so the cleanup is deferred to a workqueue.
 */
अटल व्योम cleanup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_ग_लिखोback_job *job = container_of(work,
						     काष्ठा drm_ग_लिखोback_job,
						     cleanup_work);

	drm_ग_लिखोback_cleanup_job(job);
पूर्ण

/**
 * drm_ग_लिखोback_संकेत_completion - Signal the completion of a ग_लिखोback job
 * @wb_connector: The ग_लिखोback connector whose job is complete
 * @status: Status code to set in the ग_लिखोback out_fence (0 क्रम success)
 *
 * Drivers should call this to संकेत the completion of a previously queued
 * ग_लिखोback job. It should be called as soon as possible after the hardware
 * has finished writing, and may be called from पूर्णांकerrupt context.
 * It is the driver's responsibility to ensure that क्रम a given connector, the
 * hardware completes ग_लिखोback jobs in the same order as they are queued.
 *
 * Unless the driver is holding its own reference to the framebuffer, it must
 * not be accessed after calling this function.
 *
 * See also: drm_ग_लिखोback_queue_job()
 */
व्योम
drm_ग_लिखोback_संकेत_completion(काष्ठा drm_ग_लिखोback_connector *wb_connector,
				पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा drm_ग_लिखोback_job *job;
	काष्ठा dma_fence *out_fence;

	spin_lock_irqsave(&wb_connector->job_lock, flags);
	job = list_first_entry_or_null(&wb_connector->job_queue,
				       काष्ठा drm_ग_लिखोback_job,
				       list_entry);
	अगर (job)
		list_del(&job->list_entry);

	spin_unlock_irqrestore(&wb_connector->job_lock, flags);

	अगर (WARN_ON(!job))
		वापस;

	out_fence = job->out_fence;
	अगर (out_fence) अणु
		अगर (status)
			dma_fence_set_error(out_fence, status);
		dma_fence_संकेत(out_fence);
		dma_fence_put(out_fence);
		job->out_fence = शून्य;
	पूर्ण

	INIT_WORK(&job->cleanup_work, cleanup_work);
	queue_work(प्रणाली_दीर्घ_wq, &job->cleanup_work);
पूर्ण
EXPORT_SYMBOL(drm_ग_लिखोback_संकेत_completion);

काष्ठा dma_fence *
drm_ग_लिखोback_get_out_fence(काष्ठा drm_ग_लिखोback_connector *wb_connector)
अणु
	काष्ठा dma_fence *fence;

	अगर (WARN_ON(wb_connector->base.connector_type !=
		    DRM_MODE_CONNECTOR_WRITEBACK))
		वापस शून्य;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (!fence)
		वापस शून्य;

	dma_fence_init(fence, &drm_ग_लिखोback_fence_ops,
		       &wb_connector->fence_lock, wb_connector->fence_context,
		       ++wb_connector->fence_seqno);

	वापस fence;
पूर्ण
EXPORT_SYMBOL(drm_ग_लिखोback_get_out_fence);
