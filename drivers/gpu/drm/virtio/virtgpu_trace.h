<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_VIRTGPU_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _VIRTGPU_TRACE_H_

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM virtio_gpu
#घोषणा TRACE_INCLUDE_खाता virtgpu_trace

DECLARE_EVENT_CLASS(virtio_gpu_cmd,
	TP_PROTO(काष्ठा virtqueue *vq, काष्ठा virtio_gpu_ctrl_hdr *hdr),
	TP_ARGS(vq, hdr),
	TP_STRUCT__entry(
			 __field(पूर्णांक, dev)
			 __field(अचिन्हित पूर्णांक, vq)
			 __field(स्थिर अक्षर *, name)
			 __field(u32, type)
			 __field(u32, flags)
			 __field(u64, fence_id)
			 __field(u32, ctx_id)
			 ),
	TP_fast_assign(
		       __entry->dev = vq->vdev->index;
		       __entry->vq = vq->index;
		       __entry->name = vq->name;
		       __entry->type = le32_to_cpu(hdr->type);
		       __entry->flags = le32_to_cpu(hdr->flags);
		       __entry->fence_id = le64_to_cpu(hdr->fence_id);
		       __entry->ctx_id = le32_to_cpu(hdr->ctx_id);
		       ),
	TP_prपूर्णांकk("vdev=%d vq=%u name=%s type=0x%x flags=0x%x fence_id=%llu ctx_id=%u",
		  __entry->dev, __entry->vq, __entry->name,
		  __entry->type, __entry->flags, __entry->fence_id,
		  __entry->ctx_id)
);

DEFINE_EVENT(virtio_gpu_cmd, virtio_gpu_cmd_queue,
	TP_PROTO(काष्ठा virtqueue *vq, काष्ठा virtio_gpu_ctrl_hdr *hdr),
	TP_ARGS(vq, hdr)
);

DEFINE_EVENT(virtio_gpu_cmd, virtio_gpu_cmd_response,
	TP_PROTO(काष्ठा virtqueue *vq, काष्ठा virtio_gpu_ctrl_hdr *hdr),
	TP_ARGS(vq, hdr)
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm/virtio
#समावेश <trace/define_trace.h>
