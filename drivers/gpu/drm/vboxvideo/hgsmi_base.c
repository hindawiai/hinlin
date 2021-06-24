<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/* Copyright (C) 2006-2017 Oracle Corporation */

#समावेश <linux/vbox_err.h>
#समावेश "vbox_drv.h"
#समावेश "vboxvideo_guest.h"
#समावेश "vboxvideo_vbe.h"
#समावेश "hgsmi_channels.h"
#समावेश "hgsmi_ch_setup.h"

/**
 * Inक्रमm the host of the location of the host flags in VRAM via an HGSMI cmd.
 * Return: 0 or negative त्रुटि_सं value.
 * @ctx:        The context of the guest heap to use.
 * @location:   The offset chosen क्रम the flags within guest VRAM.
 */
पूर्णांक hgsmi_report_flags_location(काष्ठा gen_pool *ctx, u32 location)
अणु
	काष्ठा hgsmi_buffer_location *p;

	p = hgsmi_buffer_alloc(ctx, माप(*p), HGSMI_CH_HGSMI,
			       HGSMI_CC_HOST_FLAGS_LOCATION);
	अगर (!p)
		वापस -ENOMEM;

	p->buf_location = location;
	p->buf_len = माप(काष्ठा hgsmi_host_flags);

	hgsmi_buffer_submit(ctx, p);
	hgsmi_buffer_मुक्त(ctx, p);

	वापस 0;
पूर्ण

/**
 * Notअगरy the host of HGSMI-related guest capabilities via an HGSMI command.
 * Return: 0 or negative त्रुटि_सं value.
 * @ctx:        The context of the guest heap to use.
 * @caps:       The capabilities to report, see vbva_caps.
 */
पूर्णांक hgsmi_send_caps_info(काष्ठा gen_pool *ctx, u32 caps)
अणु
	काष्ठा vbva_caps *p;

	p = hgsmi_buffer_alloc(ctx, माप(*p), HGSMI_CH_VBVA, VBVA_INFO_CAPS);
	अगर (!p)
		वापस -ENOMEM;

	p->rc = VERR_NOT_IMPLEMENTED;
	p->caps = caps;

	hgsmi_buffer_submit(ctx, p);

	WARN_ON_ONCE(p->rc < 0);

	hgsmi_buffer_मुक्त(ctx, p);

	वापस 0;
पूर्ण

पूर्णांक hgsmi_test_query_conf(काष्ठा gen_pool *ctx)
अणु
	u32 value = 0;
	पूर्णांक ret;

	ret = hgsmi_query_conf(ctx, U32_MAX, &value);
	अगर (ret)
		वापस ret;

	वापस value == U32_MAX ? 0 : -EIO;
पूर्ण

/**
 * Query the host क्रम an HGSMI configuration parameter via an HGSMI command.
 * Return: 0 or negative त्रुटि_सं value.
 * @ctx:        The context containing the heap used.
 * @index:      The index of the parameter to query.
 * @value_ret:  Where to store the value of the parameter on success.
 */
पूर्णांक hgsmi_query_conf(काष्ठा gen_pool *ctx, u32 index, u32 *value_ret)
अणु
	काष्ठा vbva_conf32 *p;

	p = hgsmi_buffer_alloc(ctx, माप(*p), HGSMI_CH_VBVA,
			       VBVA_QUERY_CONF32);
	अगर (!p)
		वापस -ENOMEM;

	p->index = index;
	p->value = U32_MAX;

	hgsmi_buffer_submit(ctx, p);

	*value_ret = p->value;

	hgsmi_buffer_मुक्त(ctx, p);

	वापस 0;
पूर्ण

/**
 * Pass the host a new mouse poपूर्णांकer shape via an HGSMI command.
 * Return: 0 or negative त्रुटि_सं value.
 * @ctx:        The context containing the heap to be used.
 * @flags:      Cursor flags.
 * @hot_x:      Horizontal position of the hot spot.
 * @hot_y:      Vertical position of the hot spot.
 * @width:      Width in pixels of the cursor.
 * @height:     Height in pixels of the cursor.
 * @pixels:     Pixel data, @see VMMDevReqMousePoपूर्णांकer क्रम the क्रमmat.
 * @len:        Size in bytes of the pixel data.
 */
पूर्णांक hgsmi_update_poपूर्णांकer_shape(काष्ठा gen_pool *ctx, u32 flags,
			       u32 hot_x, u32 hot_y, u32 width, u32 height,
			       u8 *pixels, u32 len)
अणु
	काष्ठा vbva_mouse_poपूर्णांकer_shape *p;
	u32 pixel_len = 0;
	पूर्णांक rc;

	अगर (flags & VBOX_MOUSE_POINTER_SHAPE) अणु
		/*
		 * Size of the poपूर्णांकer data:
		 * माप (AND mask) + माप (XOR_MASK)
		 */
		pixel_len = ((((width + 7) / 8) * height + 3) & ~3) +
			 width * 4 * height;
		अगर (pixel_len > len)
			वापस -EINVAL;

		/*
		 * If shape is supplied, then always create the poपूर्णांकer visible.
		 * See comments in 'vboxUpdatePointerShape'
		 */
		flags |= VBOX_MOUSE_POINTER_VISIBLE;
	पूर्ण

	p = hgsmi_buffer_alloc(ctx, माप(*p) + pixel_len, HGSMI_CH_VBVA,
			       VBVA_MOUSE_POINTER_SHAPE);
	अगर (!p)
		वापस -ENOMEM;

	p->result = VINF_SUCCESS;
	p->flags = flags;
	p->hot_X = hot_x;
	p->hot_y = hot_y;
	p->width = width;
	p->height = height;
	अगर (pixel_len)
		स_नकल(p->data, pixels, pixel_len);

	hgsmi_buffer_submit(ctx, p);

	चयन (p->result) अणु
	हाल VINF_SUCCESS:
		rc = 0;
		अवरोध;
	हाल VERR_NO_MEMORY:
		rc = -ENOMEM;
		अवरोध;
	हाल VERR_NOT_SUPPORTED:
		rc = -EBUSY;
		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण

	hgsmi_buffer_मुक्त(ctx, p);

	वापस rc;
पूर्ण

/**
 * Report the guest cursor position.  The host may wish to use this inक्रमmation
 * to re-position its own cursor (though this is currently unlikely).  The
 * current host cursor position is वापसed.
 * Return: 0 or negative त्रुटि_सं value.
 * @ctx:              The context containing the heap used.
 * @report_position:  Are we reporting a position?
 * @x:                Guest cursor X position.
 * @y:                Guest cursor Y position.
 * @x_host:           Host cursor X position is stored here.  Optional.
 * @y_host:           Host cursor Y position is stored here.  Optional.
 */
पूर्णांक hgsmi_cursor_position(काष्ठा gen_pool *ctx, bool report_position,
			  u32 x, u32 y, u32 *x_host, u32 *y_host)
अणु
	काष्ठा vbva_cursor_position *p;

	p = hgsmi_buffer_alloc(ctx, माप(*p), HGSMI_CH_VBVA,
			       VBVA_CURSOR_POSITION);
	अगर (!p)
		वापस -ENOMEM;

	p->report_position = report_position;
	p->x = x;
	p->y = y;

	hgsmi_buffer_submit(ctx, p);

	*x_host = p->x;
	*y_host = p->y;

	hgsmi_buffer_मुक्त(ctx, p);

	वापस 0;
पूर्ण
