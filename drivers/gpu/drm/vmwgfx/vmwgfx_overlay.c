<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2014 VMware, Inc., Palo Alto, CA., USA
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

#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "device_include/svga_overlay.h"
#समावेश "device_include/svga_escape.h"

#समावेश "vmwgfx_drv.h"

#घोषणा VMW_MAX_NUM_STREAMS 1
#घोषणा VMW_OVERLAY_CAP_MASK (SVGA_FIFO_CAP_VIDEO | SVGA_FIFO_CAP_ESCAPE)

काष्ठा vmw_stream अणु
	काष्ठा vmw_buffer_object *buf;
	bool claimed;
	bool छोड़ोd;
	काष्ठा drm_vmw_control_stream_arg saved;
पूर्ण;

/*
 * Overlay control
 */
काष्ठा vmw_overlay अणु
	/*
	 * Each stream is a single overlay. In Xv these are called ports.
	 */
	काष्ठा mutex mutex;
	काष्ठा vmw_stream stream[VMW_MAX_NUM_STREAMS];
पूर्ण;

अटल अंतरभूत काष्ठा vmw_overlay *vmw_overlay(काष्ठा drm_device *dev)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	वापस dev_priv ? dev_priv->overlay_priv : शून्य;
पूर्ण

काष्ठा vmw_escape_header अणु
	uपूर्णांक32_t cmd;
	SVGAFअगरoCmdEscape body;
पूर्ण;

काष्ठा vmw_escape_video_flush अणु
	काष्ठा vmw_escape_header escape;
	SVGAEscapeVideoFlush flush;
पूर्ण;

अटल अंतरभूत व्योम fill_escape(काष्ठा vmw_escape_header *header,
			       uपूर्णांक32_t size)
अणु
	header->cmd = SVGA_CMD_ESCAPE;
	header->body.nsid = SVGA_ESCAPE_NSID_VMWARE;
	header->body.size = size;
पूर्ण

अटल अंतरभूत व्योम fill_flush(काष्ठा vmw_escape_video_flush *cmd,
			      uपूर्णांक32_t stream_id)
अणु
	fill_escape(&cmd->escape, माप(cmd->flush));
	cmd->flush.cmdType = SVGA_ESCAPE_VMWARE_VIDEO_FLUSH;
	cmd->flush.streamId = stream_id;
पूर्ण

/*
 * Send put command to hw.
 *
 * Returns
 * -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत.
 */
अटल पूर्णांक vmw_overlay_send_put(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_buffer_object *buf,
				काष्ठा drm_vmw_control_stream_arg *arg,
				bool पूर्णांकerruptible)
अणु
	काष्ठा vmw_escape_video_flush *flush;
	माप_प्रकार fअगरo_size;
	bool have_so = (dev_priv->active_display_unit == vmw_du_screen_object);
	पूर्णांक i, num_items;
	SVGAGuestPtr ptr;

	काष्ठा अणु
		काष्ठा vmw_escape_header escape;
		काष्ठा अणु
			uपूर्णांक32_t cmdType;
			uपूर्णांक32_t streamId;
		पूर्ण header;
	पूर्ण *cmds;
	काष्ठा अणु
		uपूर्णांक32_t रेजिस्टरId;
		uपूर्णांक32_t value;
	पूर्ण *items;

	/* defines are a index needs + 1 */
	अगर (have_so)
		num_items = SVGA_VIDEO_DST_SCREEN_ID + 1;
	अन्यथा
		num_items = SVGA_VIDEO_PITCH_3 + 1;

	fअगरo_size = माप(*cmds) + माप(*flush) + माप(*items) * num_items;

	cmds = VMW_CMD_RESERVE(dev_priv, fअगरo_size);
	/* hardware has hung, can't करो anything here */
	अगर (!cmds)
		वापस -ENOMEM;

	items = (typeof(items))&cmds[1];
	flush = (काष्ठा vmw_escape_video_flush *)&items[num_items];

	/* the size is header + number of items */
	fill_escape(&cmds->escape, माप(*items) * (num_items + 1));

	cmds->header.cmdType = SVGA_ESCAPE_VMWARE_VIDEO_SET_REGS;
	cmds->header.streamId = arg->stream_id;

	/* the IDs are neatly numbered */
	क्रम (i = 0; i < num_items; i++)
		items[i].रेजिस्टरId = i;

	vmw_bo_get_guest_ptr(&buf->base, &ptr);
	ptr.offset += arg->offset;

	items[SVGA_VIDEO_ENABLED].value     = true;
	items[SVGA_VIDEO_FLAGS].value       = arg->flags;
	items[SVGA_VIDEO_DATA_OFFSET].value = ptr.offset;
	items[SVGA_VIDEO_FORMAT].value      = arg->क्रमmat;
	items[SVGA_VIDEO_COLORKEY].value    = arg->color_key;
	items[SVGA_VIDEO_SIZE].value        = arg->size;
	items[SVGA_VIDEO_WIDTH].value       = arg->width;
	items[SVGA_VIDEO_HEIGHT].value      = arg->height;
	items[SVGA_VIDEO_SRC_X].value       = arg->src.x;
	items[SVGA_VIDEO_SRC_Y].value       = arg->src.y;
	items[SVGA_VIDEO_SRC_WIDTH].value   = arg->src.w;
	items[SVGA_VIDEO_SRC_HEIGHT].value  = arg->src.h;
	items[SVGA_VIDEO_DST_X].value       = arg->dst.x;
	items[SVGA_VIDEO_DST_Y].value       = arg->dst.y;
	items[SVGA_VIDEO_DST_WIDTH].value   = arg->dst.w;
	items[SVGA_VIDEO_DST_HEIGHT].value  = arg->dst.h;
	items[SVGA_VIDEO_PITCH_1].value     = arg->pitch[0];
	items[SVGA_VIDEO_PITCH_2].value     = arg->pitch[1];
	items[SVGA_VIDEO_PITCH_3].value     = arg->pitch[2];
	अगर (have_so) अणु
		items[SVGA_VIDEO_DATA_GMRID].value    = ptr.gmrId;
		items[SVGA_VIDEO_DST_SCREEN_ID].value = SVGA_ID_INVALID;
	पूर्ण

	fill_flush(flush, arg->stream_id);

	vmw_cmd_commit(dev_priv, fअगरo_size);

	वापस 0;
पूर्ण

/*
 * Send stop command to hw.
 *
 * Returns
 * -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत.
 */
अटल पूर्णांक vmw_overlay_send_stop(काष्ठा vmw_निजी *dev_priv,
				 uपूर्णांक32_t stream_id,
				 bool पूर्णांकerruptible)
अणु
	काष्ठा अणु
		काष्ठा vmw_escape_header escape;
		SVGAEscapeVideoSetRegs body;
		काष्ठा vmw_escape_video_flush flush;
	पूर्ण *cmds;
	पूर्णांक ret;

	क्रम (;;) अणु
		cmds = VMW_CMD_RESERVE(dev_priv, माप(*cmds));
		अगर (cmds)
			अवरोध;

		ret = vmw_fallback_रुको(dev_priv, false, true, 0,
					पूर्णांकerruptible, 3*HZ);
		अगर (पूर्णांकerruptible && ret == -ERESTARTSYS)
			वापस ret;
		अन्यथा
			BUG_ON(ret != 0);
	पूर्ण

	fill_escape(&cmds->escape, माप(cmds->body));
	cmds->body.header.cmdType = SVGA_ESCAPE_VMWARE_VIDEO_SET_REGS;
	cmds->body.header.streamId = stream_id;
	cmds->body.items[0].रेजिस्टरId = SVGA_VIDEO_ENABLED;
	cmds->body.items[0].value = false;
	fill_flush(&cmds->flush, stream_id);

	vmw_cmd_commit(dev_priv, माप(*cmds));

	वापस 0;
पूर्ण

/*
 * Move a buffer to vram or gmr अगर @pin is set, अन्यथा unpin the buffer.
 *
 * With the पूर्णांकroduction of screen objects buffers could now be
 * used with GMRs instead of being locked to vram.
 */
अटल पूर्णांक vmw_overlay_move_buffer(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा vmw_buffer_object *buf,
				   bool pin, bool पूर्णांकer)
अणु
	अगर (!pin)
		वापस vmw_bo_unpin(dev_priv, buf, पूर्णांकer);

	अगर (dev_priv->active_display_unit == vmw_du_legacy)
		वापस vmw_bo_pin_in_vram(dev_priv, buf, पूर्णांकer);

	वापस vmw_bo_pin_in_vram_or_gmr(dev_priv, buf, पूर्णांकer);
पूर्ण

/*
 * Stop or छोड़ो a stream.
 *
 * If the stream is छोड़ोd the no evict flag is हटाओd from the buffer
 * but left in vram. This allows क्रम instance mode_set to evict it
 * should it need to.
 *
 * The caller must hold the overlay lock.
 *
 * @stream_id which stream to stop/छोड़ो.
 * @छोड़ो true to छोड़ो, false to stop completely.
 */
अटल पूर्णांक vmw_overlay_stop(काष्ठा vmw_निजी *dev_priv,
			    uपूर्णांक32_t stream_id, bool छोड़ो,
			    bool पूर्णांकerruptible)
अणु
	काष्ठा vmw_overlay *overlay = dev_priv->overlay_priv;
	काष्ठा vmw_stream *stream = &overlay->stream[stream_id];
	पूर्णांक ret;

	/* no buffer attached the stream is completely stopped */
	अगर (!stream->buf)
		वापस 0;

	/* If the stream is छोड़ोd this is alपढ़ोy करोne */
	अगर (!stream->छोड़ोd) अणु
		ret = vmw_overlay_send_stop(dev_priv, stream_id,
					    पूर्णांकerruptible);
		अगर (ret)
			वापस ret;

		/* We just हटाओ the NO_EVICT flag so no -ENOMEM */
		ret = vmw_overlay_move_buffer(dev_priv, stream->buf, false,
					      पूर्णांकerruptible);
		अगर (पूर्णांकerruptible && ret == -ERESTARTSYS)
			वापस ret;
		अन्यथा
			BUG_ON(ret != 0);
	पूर्ण

	अगर (!छोड़ो) अणु
		vmw_bo_unreference(&stream->buf);
		stream->छोड़ोd = false;
	पूर्ण अन्यथा अणु
		stream->छोड़ोd = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Update a stream and send any put or stop fअगरo commands needed.
 *
 * The caller must hold the overlay lock.
 *
 * Returns
 * -ENOMEM अगर buffer करोesn't fit in vram.
 * -ERESTARTSYS अगर पूर्णांकerrupted.
 */
अटल पूर्णांक vmw_overlay_update_stream(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_buffer_object *buf,
				     काष्ठा drm_vmw_control_stream_arg *arg,
				     bool पूर्णांकerruptible)
अणु
	काष्ठा vmw_overlay *overlay = dev_priv->overlay_priv;
	काष्ठा vmw_stream *stream = &overlay->stream[arg->stream_id];
	पूर्णांक ret = 0;

	अगर (!buf)
		वापस -EINVAL;

	DRM_DEBUG("   %s: old %p, new %p, %spaused\n", __func__,
		  stream->buf, buf, stream->छोड़ोd ? "" : "not ");

	अगर (stream->buf != buf) अणु
		ret = vmw_overlay_stop(dev_priv, arg->stream_id,
				       false, पूर्णांकerruptible);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (!stream->छोड़ोd) अणु
		/* If the buffers match and not छोड़ोd then just send
		 * the put command, no need to करो anything अन्यथा.
		 */
		ret = vmw_overlay_send_put(dev_priv, buf, arg, पूर्णांकerruptible);
		अगर (ret == 0)
			stream->saved = *arg;
		अन्यथा
			BUG_ON(!पूर्णांकerruptible);

		वापस ret;
	पूर्ण

	/* We करोn't start the old stream अगर we are पूर्णांकerrupted.
	 * Might वापस -ENOMEM अगर it can't fit the buffer in vram.
	 */
	ret = vmw_overlay_move_buffer(dev_priv, buf, true, पूर्णांकerruptible);
	अगर (ret)
		वापस ret;

	ret = vmw_overlay_send_put(dev_priv, buf, arg, पूर्णांकerruptible);
	अगर (ret) अणु
		/* This one needs to happen no matter what. We only हटाओ
		 * the NO_EVICT flag so this is safe from -ENOMEM.
		 */
		BUG_ON(vmw_overlay_move_buffer(dev_priv, buf, false, false)
		       != 0);
		वापस ret;
	पूर्ण

	अगर (stream->buf != buf)
		stream->buf = vmw_bo_reference(buf);
	stream->saved = *arg;
	/* stream is no दीर्घer stopped/छोड़ोd */
	stream->छोड़ोd = false;

	वापस 0;
पूर्ण

/*
 * Try to resume all छोड़ोd streams.
 *
 * Used by the kms code after moving a new scanout buffer to vram.
 *
 * Takes the overlay lock.
 */
पूर्णांक vmw_overlay_resume_all(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_overlay *overlay = dev_priv->overlay_priv;
	पूर्णांक i, ret;

	अगर (!overlay)
		वापस 0;

	mutex_lock(&overlay->mutex);

	क्रम (i = 0; i < VMW_MAX_NUM_STREAMS; i++) अणु
		काष्ठा vmw_stream *stream = &overlay->stream[i];
		अगर (!stream->छोड़ोd)
			जारी;

		ret = vmw_overlay_update_stream(dev_priv, stream->buf,
						&stream->saved, false);
		अगर (ret != 0)
			DRM_INFO("%s: *warning* failed to resume stream %i\n",
				 __func__, i);
	पूर्ण

	mutex_unlock(&overlay->mutex);

	वापस 0;
पूर्ण

/*
 * Pauses all active streams.
 *
 * Used by the kms code when moving a new scanout buffer to vram.
 *
 * Takes the overlay lock.
 */
पूर्णांक vmw_overlay_छोड़ो_all(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_overlay *overlay = dev_priv->overlay_priv;
	पूर्णांक i, ret;

	अगर (!overlay)
		वापस 0;

	mutex_lock(&overlay->mutex);

	क्रम (i = 0; i < VMW_MAX_NUM_STREAMS; i++) अणु
		अगर (overlay->stream[i].छोड़ोd)
			DRM_INFO("%s: *warning* stream %i already paused\n",
				 __func__, i);
		ret = vmw_overlay_stop(dev_priv, i, true, false);
		WARN_ON(ret != 0);
	पूर्ण

	mutex_unlock(&overlay->mutex);

	वापस 0;
पूर्ण


अटल bool vmw_overlay_available(स्थिर काष्ठा vmw_निजी *dev_priv)
अणु
	वापस (dev_priv->overlay_priv != शून्य &&
		((dev_priv->fअगरo.capabilities & VMW_OVERLAY_CAP_MASK) ==
		 VMW_OVERLAY_CAP_MASK));
पूर्ण

पूर्णांक vmw_overlay_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा vmw_overlay *overlay = dev_priv->overlay_priv;
	काष्ठा drm_vmw_control_stream_arg *arg =
	    (काष्ठा drm_vmw_control_stream_arg *)data;
	काष्ठा vmw_buffer_object *buf;
	काष्ठा vmw_resource *res;
	पूर्णांक ret;

	अगर (!vmw_overlay_available(dev_priv))
		वापस -ENOSYS;

	ret = vmw_user_stream_lookup(dev_priv, tfile, &arg->stream_id, &res);
	अगर (ret)
		वापस ret;

	mutex_lock(&overlay->mutex);

	अगर (!arg->enabled) अणु
		ret = vmw_overlay_stop(dev_priv, arg->stream_id, false, true);
		जाओ out_unlock;
	पूर्ण

	ret = vmw_user_bo_lookup(tfile, arg->handle, &buf, शून्य);
	अगर (ret)
		जाओ out_unlock;

	ret = vmw_overlay_update_stream(dev_priv, buf, arg, true);

	vmw_bo_unreference(&buf);

out_unlock:
	mutex_unlock(&overlay->mutex);
	vmw_resource_unreference(&res);

	वापस ret;
पूर्ण

पूर्णांक vmw_overlay_num_overlays(काष्ठा vmw_निजी *dev_priv)
अणु
	अगर (!vmw_overlay_available(dev_priv))
		वापस 0;

	वापस VMW_MAX_NUM_STREAMS;
पूर्ण

पूर्णांक vmw_overlay_num_मुक्त_overlays(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_overlay *overlay = dev_priv->overlay_priv;
	पूर्णांक i, k;

	अगर (!vmw_overlay_available(dev_priv))
		वापस 0;

	mutex_lock(&overlay->mutex);

	क्रम (i = 0, k = 0; i < VMW_MAX_NUM_STREAMS; i++)
		अगर (!overlay->stream[i].claimed)
			k++;

	mutex_unlock(&overlay->mutex);

	वापस k;
पूर्ण

पूर्णांक vmw_overlay_claim(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t *out)
अणु
	काष्ठा vmw_overlay *overlay = dev_priv->overlay_priv;
	पूर्णांक i;

	अगर (!overlay)
		वापस -ENOSYS;

	mutex_lock(&overlay->mutex);

	क्रम (i = 0; i < VMW_MAX_NUM_STREAMS; i++) अणु

		अगर (overlay->stream[i].claimed)
			जारी;

		overlay->stream[i].claimed = true;
		*out = i;
		mutex_unlock(&overlay->mutex);
		वापस 0;
	पूर्ण

	mutex_unlock(&overlay->mutex);
	वापस -ESRCH;
पूर्ण

पूर्णांक vmw_overlay_unref(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t stream_id)
अणु
	काष्ठा vmw_overlay *overlay = dev_priv->overlay_priv;

	BUG_ON(stream_id >= VMW_MAX_NUM_STREAMS);

	अगर (!overlay)
		वापस -ENOSYS;

	mutex_lock(&overlay->mutex);

	WARN_ON(!overlay->stream[stream_id].claimed);
	vmw_overlay_stop(dev_priv, stream_id, false, false);
	overlay->stream[stream_id].claimed = false;

	mutex_unlock(&overlay->mutex);
	वापस 0;
पूर्ण

पूर्णांक vmw_overlay_init(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_overlay *overlay;
	पूर्णांक i;

	अगर (dev_priv->overlay_priv)
		वापस -EINVAL;

	overlay = kzalloc(माप(*overlay), GFP_KERNEL);
	अगर (!overlay)
		वापस -ENOMEM;

	mutex_init(&overlay->mutex);
	क्रम (i = 0; i < VMW_MAX_NUM_STREAMS; i++) अणु
		overlay->stream[i].buf = शून्य;
		overlay->stream[i].छोड़ोd = false;
		overlay->stream[i].claimed = false;
	पूर्ण

	dev_priv->overlay_priv = overlay;

	वापस 0;
पूर्ण

पूर्णांक vmw_overlay_बंद(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_overlay *overlay = dev_priv->overlay_priv;
	bool क्रमgotten_buffer = false;
	पूर्णांक i;

	अगर (!overlay)
		वापस -ENOSYS;

	क्रम (i = 0; i < VMW_MAX_NUM_STREAMS; i++) अणु
		अगर (overlay->stream[i].buf) अणु
			क्रमgotten_buffer = true;
			vmw_overlay_stop(dev_priv, i, false, false);
		पूर्ण
	पूर्ण

	WARN_ON(क्रमgotten_buffer);

	dev_priv->overlay_priv = शून्य;
	kमुक्त(overlay);

	वापस 0;
पूर्ण
