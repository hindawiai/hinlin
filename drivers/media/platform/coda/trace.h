<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM coda

#अगर !defined(__CODA_TRACE_H__) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __CODA_TRACE_H__

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "coda.h"

TRACE_EVENT(coda_bit_run,
	TP_PROTO(काष्ठा coda_ctx *ctx, पूर्णांक cmd),

	TP_ARGS(ctx, cmd),

	TP_STRUCT__entry(
		__field(पूर्णांक, minor)
		__field(पूर्णांक, ctx)
		__field(पूर्णांक, cmd)
	),

	TP_fast_assign(
		__entry->minor = ctx->fh.vdev->minor;
		__entry->ctx = ctx->idx;
		__entry->cmd = cmd;
	),

	TP_prपूर्णांकk("minor = %d, ctx = %d, cmd = %d",
		  __entry->minor, __entry->ctx, __entry->cmd)
);

TRACE_EVENT(coda_bit_करोne,
	TP_PROTO(काष्ठा coda_ctx *ctx),

	TP_ARGS(ctx),

	TP_STRUCT__entry(
		__field(पूर्णांक, minor)
		__field(पूर्णांक, ctx)
	),

	TP_fast_assign(
		__entry->minor = ctx->fh.vdev->minor;
		__entry->ctx = ctx->idx;
	),

	TP_prपूर्णांकk("minor = %d, ctx = %d", __entry->minor, __entry->ctx)
);

DECLARE_EVENT_CLASS(coda_buf_class,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf),

	TP_ARGS(ctx, buf),

	TP_STRUCT__entry(
		__field(पूर्णांक, minor)
		__field(पूर्णांक, index)
		__field(पूर्णांक, ctx)
	),

	TP_fast_assign(
		__entry->minor = ctx->fh.vdev->minor;
		__entry->index = buf->vb2_buf.index;
		__entry->ctx = ctx->idx;
	),

	TP_prपूर्णांकk("minor = %d, index = %d, ctx = %d",
		  __entry->minor, __entry->index, __entry->ctx)
);

DEFINE_EVENT(coda_buf_class, coda_enc_pic_run,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf),
	TP_ARGS(ctx, buf)
);

DEFINE_EVENT(coda_buf_class, coda_enc_pic_करोne,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf),
	TP_ARGS(ctx, buf)
);

DECLARE_EVENT_CLASS(coda_buf_meta_class,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf,
		 काष्ठा coda_buffer_meta *meta),

	TP_ARGS(ctx, buf, meta),

	TP_STRUCT__entry(
		__field(पूर्णांक, minor)
		__field(पूर्णांक, index)
		__field(पूर्णांक, start)
		__field(पूर्णांक, end)
		__field(पूर्णांक, ctx)
	),

	TP_fast_assign(
		__entry->minor = ctx->fh.vdev->minor;
		__entry->index = buf->vb2_buf.index;
		__entry->start = meta->start & ctx->bitstream_fअगरo.kfअगरo.mask;
		__entry->end = meta->end & ctx->bitstream_fअगरo.kfअगरo.mask;
		__entry->ctx = ctx->idx;
	),

	TP_prपूर्णांकk("minor = %d, index = %d, start = 0x%x, end = 0x%x, ctx = %d",
		  __entry->minor, __entry->index, __entry->start, __entry->end,
		  __entry->ctx)
);

DEFINE_EVENT(coda_buf_meta_class, coda_bit_queue,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf,
		 काष्ठा coda_buffer_meta *meta),
	TP_ARGS(ctx, buf, meta)
);

DECLARE_EVENT_CLASS(coda_meta_class,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा coda_buffer_meta *meta),

	TP_ARGS(ctx, meta),

	TP_STRUCT__entry(
		__field(पूर्णांक, minor)
		__field(पूर्णांक, start)
		__field(पूर्णांक, end)
		__field(पूर्णांक, ctx)
	),

	TP_fast_assign(
		__entry->minor = ctx->fh.vdev->minor;
		__entry->start = meta ? (meta->start &
					 ctx->bitstream_fअगरo.kfअगरo.mask) : 0;
		__entry->end = meta ? (meta->end &
				       ctx->bitstream_fअगरo.kfअगरo.mask) : 0;
		__entry->ctx = ctx->idx;
	),

	TP_prपूर्णांकk("minor = %d, start = 0x%x, end = 0x%x, ctx = %d",
		  __entry->minor, __entry->start, __entry->end, __entry->ctx)
);

DEFINE_EVENT(coda_meta_class, coda_dec_pic_run,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा coda_buffer_meta *meta),
	TP_ARGS(ctx, meta)
);

DEFINE_EVENT(coda_meta_class, coda_dec_pic_करोne,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा coda_buffer_meta *meta),
	TP_ARGS(ctx, meta)
);

DEFINE_EVENT(coda_buf_meta_class, coda_dec_rot_करोne,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf,
		 काष्ठा coda_buffer_meta *meta),
	TP_ARGS(ctx, buf, meta)
);

DEFINE_EVENT(coda_buf_class, coda_jpeg_run,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf),
	TP_ARGS(ctx, buf)
);

DEFINE_EVENT(coda_buf_class, coda_jpeg_करोne,
	TP_PROTO(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf),
	TP_ARGS(ctx, buf)
);

#पूर्ण_अगर /* __CODA_TRACE_H__ */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/media/platक्रमm/coda
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
