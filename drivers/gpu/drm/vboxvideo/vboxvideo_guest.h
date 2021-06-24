<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/* Copyright (C) 2006-2016 Oracle Corporation */

#अगर_अघोषित __VBOXVIDEO_GUEST_H__
#घोषणा __VBOXVIDEO_GUEST_H__

#समावेश <linux/genभाग.स>
#समावेश "vboxvideo.h"

/*
 * Structure grouping the context needed क्रम sending graphics acceleration
 * inक्रमmation to the host via VBVA.  Each screen has its own VBVA buffer.
 */
काष्ठा vbva_buf_ctx अणु
	/* Offset of the buffer in the VRAM section क्रम the screen */
	u32 buffer_offset;
	/* Length of the buffer in bytes */
	u32 buffer_length;
	/* Set अगर we wrote to the buffer faster than the host could पढ़ो it */
	bool buffer_overflow;
	/* VBVA record that we are currently preparing क्रम the host, or शून्य */
	काष्ठा vbva_record *record;
	/*
	 * Poपूर्णांकer to the VBVA buffer mapped पूर्णांकo the current address space.
	 * Will be शून्य अगर VBVA is not enabled.
	 */
	काष्ठा vbva_buffer *vbva;
पूर्ण;

पूर्णांक hgsmi_report_flags_location(काष्ठा gen_pool *ctx, u32 location);
पूर्णांक hgsmi_send_caps_info(काष्ठा gen_pool *ctx, u32 caps);
पूर्णांक hgsmi_test_query_conf(काष्ठा gen_pool *ctx);
पूर्णांक hgsmi_query_conf(काष्ठा gen_pool *ctx, u32 index, u32 *value_ret);
पूर्णांक hgsmi_update_poपूर्णांकer_shape(काष्ठा gen_pool *ctx, u32 flags,
			       u32 hot_x, u32 hot_y, u32 width, u32 height,
			       u8 *pixels, u32 len);
पूर्णांक hgsmi_cursor_position(काष्ठा gen_pool *ctx, bool report_position,
			  u32 x, u32 y, u32 *x_host, u32 *y_host);

bool vbva_enable(काष्ठा vbva_buf_ctx *vbva_ctx, काष्ठा gen_pool *ctx,
		 काष्ठा vbva_buffer *vbva, s32 screen);
व्योम vbva_disable(काष्ठा vbva_buf_ctx *vbva_ctx, काष्ठा gen_pool *ctx,
		  s32 screen);
bool vbva_buffer_begin_update(काष्ठा vbva_buf_ctx *vbva_ctx,
			      काष्ठा gen_pool *ctx);
व्योम vbva_buffer_end_update(काष्ठा vbva_buf_ctx *vbva_ctx);
bool vbva_ग_लिखो(काष्ठा vbva_buf_ctx *vbva_ctx, काष्ठा gen_pool *ctx,
		स्थिर व्योम *p, u32 len);
व्योम vbva_setup_buffer_context(काष्ठा vbva_buf_ctx *vbva_ctx,
			       u32 buffer_offset, u32 buffer_length);

व्योम hgsmi_process_display_info(काष्ठा gen_pool *ctx, u32 display,
				s32 origin_x, s32 origin_y, u32 start_offset,
				u32 pitch, u32 width, u32 height,
				u16 bpp, u16 flags);
पूर्णांक hgsmi_update_input_mapping(काष्ठा gen_pool *ctx, s32 origin_x, s32 origin_y,
			       u32 width, u32 height);
पूर्णांक hgsmi_get_mode_hपूर्णांकs(काष्ठा gen_pool *ctx, अचिन्हित पूर्णांक screens,
			 काष्ठा vbva_modehपूर्णांक *hपूर्णांकs);

#पूर्ण_अगर
