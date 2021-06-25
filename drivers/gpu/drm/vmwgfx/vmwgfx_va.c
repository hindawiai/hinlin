<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2012-2016 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_resource_priv.h"

/**
 * काष्ठा vmw_stream - Overlay stream simple resource.
 * @sres: The simple resource we derive from.
 * @stream_id: The overlay stream id.
 */
काष्ठा vmw_stream अणु
	काष्ठा vmw_simple_resource sres;
	u32 stream_id;
पूर्ण;

/**
 * vmw_stream - Typecast a काष्ठा vmw_resource to a काष्ठा vmw_stream.
 * @res: Poपूर्णांकer to the काष्ठा vmw_resource.
 *
 * Returns: Returns a poपूर्णांकer to the काष्ठा vmw_stream.
 */
अटल काष्ठा vmw_stream *
vmw_stream(काष्ठा vmw_resource *res)
अणु
	वापस container_of(res, काष्ठा vmw_stream, sres.res);
पूर्ण

/***************************************************************************
 * Simple resource callbacks क्रम काष्ठा vmw_stream
 **************************************************************************/
अटल व्योम vmw_stream_hw_destroy(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा vmw_stream *stream = vmw_stream(res);
	पूर्णांक ret;

	ret = vmw_overlay_unref(dev_priv, stream->stream_id);
	WARN_ON_ONCE(ret != 0);
पूर्ण

अटल पूर्णांक vmw_stream_init(काष्ठा vmw_resource *res, व्योम *data)
अणु
	काष्ठा vmw_stream *stream = vmw_stream(res);

	वापस vmw_overlay_claim(res->dev_priv, &stream->stream_id);
पूर्ण

अटल व्योम vmw_stream_set_arg_handle(व्योम *data, u32 handle)
अणु
	काष्ठा drm_vmw_stream_arg *arg = (काष्ठा drm_vmw_stream_arg *)data;

	arg->stream_id = handle;
पूर्ण

अटल स्थिर काष्ठा vmw_simple_resource_func va_stream_func = अणु
	.res_func = अणु
		.res_type = vmw_res_stream,
		.needs_backup = false,
		.may_evict = false,
		.type_name = "overlay stream",
		.backup_placement = शून्य,
		.create = शून्य,
		.destroy = शून्य,
		.bind = शून्य,
		.unbind = शून्य
	पूर्ण,
	.tपंचांग_res_type = VMW_RES_STREAM,
	.size = माप(काष्ठा vmw_stream),
	.init = vmw_stream_init,
	.hw_destroy = vmw_stream_hw_destroy,
	.set_arg_handle = vmw_stream_set_arg_handle,
पूर्ण;

/***************************************************************************
 * End simple resource callbacks क्रम काष्ठा vmw_stream
 **************************************************************************/

/**
 * vmw_stream_unref_ioctl - Ioctl to unreference a user-space handle to
 * a काष्ठा vmw_stream.
 * @dev: Poपूर्णांकer to the drm device.
 * @data: The ioctl argument
 * @file_priv: Poपूर्णांकer to a काष्ठा drm_file identअगरying the caller.
 *
 * Return:
 *   0 अगर successful.
 *   Negative error value on failure.
 */
पूर्णांक vmw_stream_unref_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_stream_arg *arg = (काष्ठा drm_vmw_stream_arg *)data;

	वापस tपंचांग_ref_object_base_unref(vmw_fpriv(file_priv)->tfile,
					 arg->stream_id, TTM_REF_USAGE);
पूर्ण

/**
 * vmw_stream_claim_ioctl - Ioctl to claim a काष्ठा vmw_stream overlay.
 * @dev: Poपूर्णांकer to the drm device.
 * @data: The ioctl argument
 * @file_priv: Poपूर्णांकer to a काष्ठा drm_file identअगरying the caller.
 *
 * Return:
 *   0 अगर successful.
 *   Negative error value on failure.
 */
पूर्णांक vmw_stream_claim_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	वापस vmw_simple_resource_create_ioctl(dev, data, file_priv,
						&va_stream_func);
पूर्ण

/**
 * vmw_user_stream_lookup - Look up a काष्ठा vmw_user_stream from a handle.
 * @dev_priv: Poपूर्णांकer to a काष्ठा vmw_निजी.
 * @tfile: काष्ठा tपंचांग_object_file identअगरying the caller.
 * @inout_id: In: The user-space handle. Out: The stream id.
 * @out: On output contains a refcounted poपूर्णांकer to the embedded
 * काष्ठा vmw_resource.
 *
 * Return:
 *   0 अगर successful.
 *   Negative error value on failure.
 */
पूर्णांक vmw_user_stream_lookup(काष्ठा vmw_निजी *dev_priv,
			   काष्ठा tपंचांग_object_file *tfile,
			   uपूर्णांक32_t *inout_id, काष्ठा vmw_resource **out)
अणु
	काष्ठा vmw_stream *stream;
	काष्ठा vmw_resource *res =
		vmw_simple_resource_lookup(tfile, *inout_id, &va_stream_func);

	अगर (IS_ERR(res))
		वापस PTR_ERR(res);

	stream = vmw_stream(res);
	*inout_id = stream->stream_id;
	*out = res;

	वापस 0;
पूर्ण
