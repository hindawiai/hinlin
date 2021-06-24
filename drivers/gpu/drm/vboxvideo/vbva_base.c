<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/* Copyright (C) 2006-2017 Oracle Corporation */

#समावेश <linux/vbox_err.h>
#समावेश "vbox_drv.h"
#समावेश "vboxvideo_guest.h"
#समावेश "hgsmi_channels.h"

/*
 * There is a hardware ring buffer in the graphics device video RAM, क्रमmerly
 * in the VBox VMMDev PCI memory space.
 * All graphics commands go there serialized by vbva_buffer_begin_update.
 * and vbva_buffer_end_update.
 *
 * मुक्त_offset is writing position. data_offset is पढ़ोing position.
 * मुक्त_offset == data_offset means buffer is empty.
 * There must be always gap between data_offset and मुक्त_offset when data
 * are in the buffer.
 * Guest only changes मुक्त_offset, host changes data_offset.
 */

अटल u32 vbva_buffer_available(स्थिर काष्ठा vbva_buffer *vbva)
अणु
	s32 dअगरf = vbva->data_offset - vbva->मुक्त_offset;

	वापस dअगरf > 0 ? dअगरf : vbva->data_len + dअगरf;
पूर्ण

अटल व्योम vbva_buffer_place_data_at(काष्ठा vbva_buf_ctx *vbva_ctx,
				      स्थिर व्योम *p, u32 len, u32 offset)
अणु
	काष्ठा vbva_buffer *vbva = vbva_ctx->vbva;
	u32 bytes_till_boundary = vbva->data_len - offset;
	u8 *dst = &vbva->data[offset];
	s32 dअगरf = len - bytes_till_boundary;

	अगर (dअगरf <= 0) अणु
		/* Chunk will not cross buffer boundary. */
		स_नकल(dst, p, len);
	पूर्ण अन्यथा अणु
		/* Chunk crosses buffer boundary. */
		स_नकल(dst, p, bytes_till_boundary);
		स_नकल(&vbva->data[0], (u8 *)p + bytes_till_boundary, dअगरf);
	पूर्ण
पूर्ण

अटल व्योम vbva_buffer_flush(काष्ठा gen_pool *ctx)
अणु
	काष्ठा vbva_flush *p;

	p = hgsmi_buffer_alloc(ctx, माप(*p), HGSMI_CH_VBVA, VBVA_FLUSH);
	अगर (!p)
		वापस;

	p->reserved = 0;

	hgsmi_buffer_submit(ctx, p);
	hgsmi_buffer_मुक्त(ctx, p);
पूर्ण

bool vbva_ग_लिखो(काष्ठा vbva_buf_ctx *vbva_ctx, काष्ठा gen_pool *ctx,
		स्थिर व्योम *p, u32 len)
अणु
	काष्ठा vbva_record *record;
	काष्ठा vbva_buffer *vbva;
	u32 available;

	vbva = vbva_ctx->vbva;
	record = vbva_ctx->record;

	अगर (!vbva || vbva_ctx->buffer_overflow ||
	    !record || !(record->len_and_flags & VBVA_F_RECORD_PARTIAL))
		वापस false;

	available = vbva_buffer_available(vbva);

	जबतक (len > 0) अणु
		u32 chunk = len;

		अगर (chunk >= available) अणु
			vbva_buffer_flush(ctx);
			available = vbva_buffer_available(vbva);
		पूर्ण

		अगर (chunk >= available) अणु
			अगर (WARN_ON(available <= vbva->partial_ग_लिखो_tresh)) अणु
				vbva_ctx->buffer_overflow = true;
				वापस false;
			पूर्ण
			chunk = available - vbva->partial_ग_लिखो_tresh;
		पूर्ण

		vbva_buffer_place_data_at(vbva_ctx, p, chunk,
					  vbva->मुक्त_offset);

		vbva->मुक्त_offset = (vbva->मुक्त_offset + chunk) %
				    vbva->data_len;
		record->len_and_flags += chunk;
		available -= chunk;
		len -= chunk;
		p += chunk;
	पूर्ण

	वापस true;
पूर्ण

अटल bool vbva_inक्रमm_host(काष्ठा vbva_buf_ctx *vbva_ctx,
			     काष्ठा gen_pool *ctx, s32 screen, bool enable)
अणु
	काष्ठा vbva_enable_ex *p;
	bool ret;

	p = hgsmi_buffer_alloc(ctx, माप(*p), HGSMI_CH_VBVA, VBVA_ENABLE);
	अगर (!p)
		वापस false;

	p->base.flags = enable ? VBVA_F_ENABLE : VBVA_F_DISABLE;
	p->base.offset = vbva_ctx->buffer_offset;
	p->base.result = VERR_NOT_SUPPORTED;
	अगर (screen >= 0) अणु
		p->base.flags |= VBVA_F_EXTENDED | VBVA_F_ABSOFFSET;
		p->screen_id = screen;
	पूर्ण

	hgsmi_buffer_submit(ctx, p);

	अगर (enable)
		ret = p->base.result >= 0;
	अन्यथा
		ret = true;

	hgsmi_buffer_मुक्त(ctx, p);

	वापस ret;
पूर्ण

bool vbva_enable(काष्ठा vbva_buf_ctx *vbva_ctx, काष्ठा gen_pool *ctx,
		 काष्ठा vbva_buffer *vbva, s32 screen)
अणु
	bool ret = false;

	स_रखो(vbva, 0, माप(*vbva));
	vbva->partial_ग_लिखो_tresh = 256;
	vbva->data_len = vbva_ctx->buffer_length - माप(काष्ठा vbva_buffer);
	vbva_ctx->vbva = vbva;

	ret = vbva_inक्रमm_host(vbva_ctx, ctx, screen, true);
	अगर (!ret)
		vbva_disable(vbva_ctx, ctx, screen);

	वापस ret;
पूर्ण

व्योम vbva_disable(काष्ठा vbva_buf_ctx *vbva_ctx, काष्ठा gen_pool *ctx,
		  s32 screen)
अणु
	vbva_ctx->buffer_overflow = false;
	vbva_ctx->record = शून्य;
	vbva_ctx->vbva = शून्य;

	vbva_inक्रमm_host(vbva_ctx, ctx, screen, false);
पूर्ण

bool vbva_buffer_begin_update(काष्ठा vbva_buf_ctx *vbva_ctx,
			      काष्ठा gen_pool *ctx)
अणु
	काष्ठा vbva_record *record;
	u32 next;

	अगर (!vbva_ctx->vbva ||
	    !(vbva_ctx->vbva->host_flags.host_events & VBVA_F_MODE_ENABLED))
		वापस false;

	WARN_ON(vbva_ctx->buffer_overflow || vbva_ctx->record);

	next = (vbva_ctx->vbva->record_मुक्त_index + 1) % VBVA_MAX_RECORDS;

	/* Flush अगर all slots in the records queue are used */
	अगर (next == vbva_ctx->vbva->record_first_index)
		vbva_buffer_flush(ctx);

	/* If even after flush there is no place then fail the request */
	अगर (next == vbva_ctx->vbva->record_first_index)
		वापस false;

	record = &vbva_ctx->vbva->records[vbva_ctx->vbva->record_मुक्त_index];
	record->len_and_flags = VBVA_F_RECORD_PARTIAL;
	vbva_ctx->vbva->record_मुक्त_index = next;
	/* Remember which record we are using. */
	vbva_ctx->record = record;

	वापस true;
पूर्ण

व्योम vbva_buffer_end_update(काष्ठा vbva_buf_ctx *vbva_ctx)
अणु
	काष्ठा vbva_record *record = vbva_ctx->record;

	WARN_ON(!vbva_ctx->vbva || !record ||
		!(record->len_and_flags & VBVA_F_RECORD_PARTIAL));

	/* Mark the record completed. */
	record->len_and_flags &= ~VBVA_F_RECORD_PARTIAL;

	vbva_ctx->buffer_overflow = false;
	vbva_ctx->record = शून्य;
पूर्ण

व्योम vbva_setup_buffer_context(काष्ठा vbva_buf_ctx *vbva_ctx,
			       u32 buffer_offset, u32 buffer_length)
अणु
	vbva_ctx->buffer_offset = buffer_offset;
	vbva_ctx->buffer_length = buffer_length;
पूर्ण
