<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2016 ARM Limited. All rights reserved.
 * Author: Brian Starkey <brian.starkey@arm.com>
 *
 * This program is मुक्त software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 */

#अगर_अघोषित __DRM_WRITEBACK_H__
#घोषणा __DRM_WRITEBACK_H__
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_encoder.h>
#समावेश <linux/workqueue.h>

/**
 * काष्ठा drm_ग_लिखोback_connector - DRM ग_लिखोback connector
 */
काष्ठा drm_ग_लिखोback_connector अणु
	/**
	 * @base: base drm_connector object
	 */
	काष्ठा drm_connector base;

	/**
	 * @encoder: Internal encoder used by the connector to fulfill
	 * the DRM framework requirements. The users of the
	 * @drm_ग_लिखोback_connector control the behaviour of the @encoder
	 * by passing the @enc_funcs parameter to drm_ग_लिखोback_connector_init()
	 * function.
	 */
	काष्ठा drm_encoder encoder;

	/**
	 * @pixel_क्रमmats_blob_ptr:
	 *
	 * DRM blob property data क्रम the pixel क्रमmats list on ग_लिखोback
	 * connectors
	 * See also drm_ग_लिखोback_connector_init()
	 */
	काष्ठा drm_property_blob *pixel_क्रमmats_blob_ptr;

	/** @job_lock: Protects job_queue */
	spinlock_t job_lock;

	/**
	 * @job_queue:
	 *
	 * Holds a list of a connector's ग_लिखोback jobs; the last item is the
	 * most recent. The first item may be either रुकोing क्रम the hardware
	 * to begin writing, or currently being written.
	 *
	 * See also: drm_ग_लिखोback_queue_job() and
	 * drm_ग_लिखोback_संकेत_completion()
	 */
	काष्ठा list_head job_queue;

	/**
	 * @fence_context:
	 *
	 * समयline context used क्रम fence operations.
	 */
	अचिन्हित पूर्णांक fence_context;
	/**
	 * @fence_lock:
	 *
	 * spinlock to protect the fences in the fence_context.
	 */
	spinlock_t fence_lock;
	/**
	 * @fence_seqno:
	 *
	 * Seqno variable used as monotonic counter क्रम the fences
	 * created on the connector's समयline.
	 */
	अचिन्हित दीर्घ fence_seqno;
	/**
	 * @समयline_name:
	 *
	 * The name of the connector's fence समयline.
	 */
	अक्षर समयline_name[32];
पूर्ण;

/**
 * काष्ठा drm_ग_लिखोback_job - DRM ग_लिखोback job
 */
काष्ठा drm_ग_लिखोback_job अणु
	/**
	 * @connector:
	 *
	 * Back-poपूर्णांकer to the ग_लिखोback connector associated with the job
	 */
	काष्ठा drm_ग_लिखोback_connector *connector;

	/**
	 * @prepared:
	 *
	 * Set when the job has been prepared with drm_ग_लिखोback_prepare_job()
	 */
	bool prepared;

	/**
	 * @cleanup_work:
	 *
	 * Used to allow drm_ग_लिखोback_संकेत_completion to defer dropping the
	 * framebuffer reference to a workqueue
	 */
	काष्ठा work_काष्ठा cleanup_work;

	/**
	 * @list_entry:
	 *
	 * List item क्रम the ग_लिखोback connector's @job_queue
	 */
	काष्ठा list_head list_entry;

	/**
	 * @fb:
	 *
	 * Framebuffer to be written to by the ग_लिखोback connector. Do not set
	 * directly, use drm_ग_लिखोback_set_fb()
	 */
	काष्ठा drm_framebuffer *fb;

	/**
	 * @out_fence:
	 *
	 * Fence which will संकेत once the ग_लिखोback has completed
	 */
	काष्ठा dma_fence *out_fence;

	/**
	 * @priv:
	 *
	 * Driver-निजी data
	 */
	व्योम *priv;
पूर्ण;

अटल अंतरभूत काष्ठा drm_ग_लिखोback_connector *
drm_connector_to_ग_लिखोback(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा drm_ग_लिखोback_connector, base);
पूर्ण

पूर्णांक drm_ग_लिखोback_connector_init(काष्ठा drm_device *dev,
				 काष्ठा drm_ग_लिखोback_connector *wb_connector,
				 स्थिर काष्ठा drm_connector_funcs *con_funcs,
				 स्थिर काष्ठा drm_encoder_helper_funcs *enc_helper_funcs,
				 स्थिर u32 *क्रमmats, पूर्णांक n_क्रमmats);

पूर्णांक drm_ग_लिखोback_set_fb(काष्ठा drm_connector_state *conn_state,
			 काष्ठा drm_framebuffer *fb);

पूर्णांक drm_ग_लिखोback_prepare_job(काष्ठा drm_ग_लिखोback_job *job);

व्योम drm_ग_लिखोback_queue_job(काष्ठा drm_ग_लिखोback_connector *wb_connector,
			     काष्ठा drm_connector_state *conn_state);

व्योम drm_ग_लिखोback_cleanup_job(काष्ठा drm_ग_लिखोback_job *job);

व्योम
drm_ग_लिखोback_संकेत_completion(काष्ठा drm_ग_लिखोback_connector *wb_connector,
				पूर्णांक status);

काष्ठा dma_fence *
drm_ग_लिखोback_get_out_fence(काष्ठा drm_ग_लिखोback_connector *wb_connector);
#पूर्ण_अगर
