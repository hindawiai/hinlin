<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2012-2016 Mentor Graphics Inc.
 *
 * i.MX Queued image conversion support, with tiling and rotation.
 */
#अगर_अघोषित __IMX_IPU_IMAGE_CONVERT_H__
#घोषणा __IMX_IPU_IMAGE_CONVERT_H__

#समावेश <video/imx-ipu-v3.h>

काष्ठा ipu_image_convert_ctx;

/**
 * काष्ठा ipu_image_convert_run - image conversion run request काष्ठा
 *
 * @ctx:	the conversion context
 * @in_phys:	dma addr of input image buffer क्रम this run
 * @out_phys:	dma addr of output image buffer क्रम this run
 * @status:	completion status of this run
 */
काष्ठा ipu_image_convert_run अणु
	काष्ठा ipu_image_convert_ctx *ctx;

	dma_addr_t in_phys;
	dma_addr_t out_phys;

	पूर्णांक status;

	/* पूर्णांकernal to image converter, callers करोn't touch */
	काष्ठा list_head list;
पूर्ण;

/**
 * ipu_image_convert_cb_t - conversion callback function prototype
 *
 * @run:	the completed conversion run poपूर्णांकer
 * @ctx:	a निजी context poपूर्णांकer क्रम the callback
 */
प्रकार व्योम (*ipu_image_convert_cb_t)(काष्ठा ipu_image_convert_run *run,
				       व्योम *ctx);

/**
 * ipu_image_convert_क्रमागत_क्रमmat() - क्रमागतerate the image converter's
 *	supported input and output pixel क्रमmats.
 *
 * @index:	pixel क्रमmat index
 * @fourcc:	v4l2 fourcc क्रम this index
 *
 * Returns 0 with a valid index and fills in v4l2 fourcc, -EINVAL otherwise.
 *
 * In V4L2, drivers can call ipu_image_क्रमागत_क्रमmat() in .क्रमागत_fmt.
 */
पूर्णांक ipu_image_convert_क्रमागत_क्रमmat(पूर्णांक index, u32 *fourcc);

/**
 * ipu_image_convert_adjust() - adjust input/output images to IPU restrictions.
 *
 * @in:		input image क्रमmat, adjusted on वापस
 * @out:	output image क्रमmat, adjusted on वापस
 * @rot_mode:	rotation mode
 *
 * In V4L2, drivers can call ipu_image_convert_adjust() in .try_fmt.
 */
व्योम ipu_image_convert_adjust(काष्ठा ipu_image *in, काष्ठा ipu_image *out,
			      क्रमागत ipu_rotate_mode rot_mode);

/**
 * ipu_image_convert_verअगरy() - verअगरy that input/output image क्रमmats
 *         and rotation mode meet IPU restrictions.
 *
 * @in:		input image क्रमmat
 * @out:	output image क्रमmat
 * @rot_mode:	rotation mode
 *
 * Returns 0 अगर the क्रमmats and rotation mode meet IPU restrictions,
 * -EINVAL otherwise.
 */
पूर्णांक ipu_image_convert_verअगरy(काष्ठा ipu_image *in, काष्ठा ipu_image *out,
			     क्रमागत ipu_rotate_mode rot_mode);

/**
 * ipu_image_convert_prepare() - prepare a conversion context.
 *
 * @ipu:	the IPU handle to use क्रम the conversions
 * @ic_task:	the IC task to use क्रम the conversions
 * @in:		input image क्रमmat
 * @out:	output image क्रमmat
 * @rot_mode:	rotation mode
 * @complete:	run completion callback
 * @complete_context:	a context poपूर्णांकer क्रम the completion callback
 *
 * Returns an opaque conversion context poपूर्णांकer on success, error poपूर्णांकer
 * on failure. The input/output क्रमmats and rotation mode must alपढ़ोy meet
 * IPU retrictions.
 *
 * In V4L2, drivers should call ipu_image_convert_prepare() at streamon.
 */
काष्ठा ipu_image_convert_ctx *
ipu_image_convert_prepare(काष्ठा ipu_soc *ipu, क्रमागत ipu_ic_task ic_task,
			  काष्ठा ipu_image *in, काष्ठा ipu_image *out,
			  क्रमागत ipu_rotate_mode rot_mode,
			  ipu_image_convert_cb_t complete,
			  व्योम *complete_context);

/**
 * ipu_image_convert_unprepare() - unprepare a conversion context.
 *
 * @ctx: the conversion context poपूर्णांकer to unprepare
 *
 * Aborts any active or pending conversions क्रम this context and
 * मुक्तs the context. Any currently active or pending runs beदीर्घing
 * to this context are वापसed via the completion callback with an
 * error run status.
 *
 * In V4L2, drivers should call ipu_image_convert_unprepare() at
 * streamoff.
 */
व्योम ipu_image_convert_unprepare(काष्ठा ipu_image_convert_ctx *ctx);

/**
 * ipu_image_convert_queue() - queue a conversion run
 *
 * @run: the run request poपूर्णांकer
 *
 * ipu_image_convert_run must be dynamically allocated (_not_ as a local
 * var) by callers and filled in with a previously prepared conversion
 * context handle and the dma addr's of the input and output image buffers
 * क्रम this conversion run.
 *
 * When this conversion completes, the run poपूर्णांकer is वापसed via the
 * completion callback. The caller is responsible क्रम मुक्तing the run
 * object after it completes.
 *
 * In V4L2, drivers should call ipu_image_convert_queue() जबतक
 * streaming to queue the conversion of a received input buffer.
 * For example mem2mem devices this would be called in .device_run.
 */
पूर्णांक ipu_image_convert_queue(काष्ठा ipu_image_convert_run *run);

/**
 * ipu_image_convert_पात() - पात conversions
 *
 * @ctx: the conversion context poपूर्णांकer
 *
 * This will पात any active or pending conversions क्रम this context.
 * Any currently active or pending runs beदीर्घing to this context are
 * वापसed via the completion callback with an error run status.
 */
व्योम ipu_image_convert_पात(काष्ठा ipu_image_convert_ctx *ctx);

/**
 * ipu_image_convert() - asynchronous image conversion request
 *
 * @ipu:	the IPU handle to use क्रम the conversion
 * @ic_task:	the IC task to use क्रम the conversion
 * @in:		input image क्रमmat
 * @out:	output image क्रमmat
 * @rot_mode:	rotation mode
 * @complete:	run completion callback
 * @complete_context:	a context poपूर्णांकer क्रम the completion callback
 *
 * Request a single image conversion. Returns the run that has been queued.
 * A conversion context is स्वतःmatically created and is available in run->ctx.
 * As with ipu_image_convert_prepare(), the input/output क्रमmats and rotation
 * mode must alपढ़ोy meet IPU retrictions.
 *
 * On successful वापस the caller can queue more run requests अगर needed, using
 * the prepared context in run->ctx. The caller is responsible क्रम unpreparing
 * the context when no more conversion requests are needed.
 */
काष्ठा ipu_image_convert_run *
ipu_image_convert(काष्ठा ipu_soc *ipu, क्रमागत ipu_ic_task ic_task,
		  काष्ठा ipu_image *in, काष्ठा ipu_image *out,
		  क्रमागत ipu_rotate_mode rot_mode,
		  ipu_image_convert_cb_t complete,
		  व्योम *complete_context);

/**
 * ipu_image_convert_sync() - synchronous single image conversion request
 *
 * @ipu:	the IPU handle to use क्रम the conversion
 * @ic_task:	the IC task to use क्रम the conversion
 * @in:		input image क्रमmat
 * @out:	output image क्रमmat
 * @rot_mode:	rotation mode
 *
 * Carry out a single image conversion. Returns when the conversion
 * completes. The input/output क्रमmats and rotation mode must alपढ़ोy
 * meet IPU retrictions. The created context is स्वतःmatically unprepared
 * and the run मुक्तd on वापस.
 */
पूर्णांक ipu_image_convert_sync(काष्ठा ipu_soc *ipu, क्रमागत ipu_ic_task ic_task,
			   काष्ठा ipu_image *in, काष्ठा ipu_image *out,
			   क्रमागत ipu_rotate_mode rot_mode);


#पूर्ण_अगर /* __IMX_IPU_IMAGE_CONVERT_H__ */
