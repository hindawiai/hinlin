<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर !defined(_GPU_SCHED_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _GPU_SCHED_TRACE_H_

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM gpu_scheduler
#घोषणा TRACE_INCLUDE_खाता gpu_scheduler_trace

TRACE_EVENT(drm_sched_job,
	    TP_PROTO(काष्ठा drm_sched_job *sched_job, काष्ठा drm_sched_entity *entity),
	    TP_ARGS(sched_job, entity),
	    TP_STRUCT__entry(
			     __field(काष्ठा drm_sched_entity *, entity)
			     __field(काष्ठा dma_fence *, fence)
			     __field(स्थिर अक्षर *, name)
			     __field(uपूर्णांक64_t, id)
			     __field(u32, job_count)
			     __field(पूर्णांक, hw_job_count)
			     ),

	    TP_fast_assign(
			   __entry->entity = entity;
			   __entry->id = sched_job->id;
			   __entry->fence = &sched_job->s_fence->finished;
			   __entry->name = sched_job->sched->name;
			   __entry->job_count = spsc_queue_count(&entity->job_queue);
			   __entry->hw_job_count = atomic_पढ़ो(
				   &sched_job->sched->hw_rq_count);
			   ),
	    TP_prपूर्णांकk("entity=%p, id=%llu, fence=%p, ring=%s, job count:%u, hw job count:%d",
		      __entry->entity, __entry->id,
		      __entry->fence, __entry->name,
		      __entry->job_count, __entry->hw_job_count)
);

TRACE_EVENT(drm_run_job,
	    TP_PROTO(काष्ठा drm_sched_job *sched_job, काष्ठा drm_sched_entity *entity),
	    TP_ARGS(sched_job, entity),
	    TP_STRUCT__entry(
			     __field(काष्ठा drm_sched_entity *, entity)
			     __field(काष्ठा dma_fence *, fence)
			     __field(स्थिर अक्षर *, name)
			     __field(uपूर्णांक64_t, id)
			     __field(u32, job_count)
			     __field(पूर्णांक, hw_job_count)
			     ),

	    TP_fast_assign(
			   __entry->entity = entity;
			   __entry->id = sched_job->id;
			   __entry->fence = &sched_job->s_fence->finished;
			   __entry->name = sched_job->sched->name;
			   __entry->job_count = spsc_queue_count(&entity->job_queue);
			   __entry->hw_job_count = atomic_पढ़ो(
				   &sched_job->sched->hw_rq_count);
			   ),
	    TP_prपूर्णांकk("entity=%p, id=%llu, fence=%p, ring=%s, job count:%u, hw job count:%d",
		      __entry->entity, __entry->id,
		      __entry->fence, __entry->name,
		      __entry->job_count, __entry->hw_job_count)
);

TRACE_EVENT(drm_sched_process_job,
	    TP_PROTO(काष्ठा drm_sched_fence *fence),
	    TP_ARGS(fence),
	    TP_STRUCT__entry(
		    __field(काष्ठा dma_fence *, fence)
		    ),

	    TP_fast_assign(
		    __entry->fence = &fence->finished;
		    ),
	    TP_prपूर्णांकk("fence=%p signaled", __entry->fence)
);

TRACE_EVENT(drm_sched_job_रुको_dep,
	    TP_PROTO(काष्ठा drm_sched_job *sched_job, काष्ठा dma_fence *fence),
	    TP_ARGS(sched_job, fence),
	    TP_STRUCT__entry(
			     __field(स्थिर अक्षर *,name)
			     __field(uपूर्णांक64_t, id)
			     __field(काष्ठा dma_fence *, fence)
			     __field(uपूर्णांक64_t, ctx)
			     __field(अचिन्हित, seqno)
			     ),

	    TP_fast_assign(
			   __entry->name = sched_job->sched->name;
			   __entry->id = sched_job->id;
			   __entry->fence = fence;
			   __entry->ctx = fence->context;
			   __entry->seqno = fence->seqno;
			   ),
	    TP_prपूर्णांकk("job ring=%s, id=%llu, depends fence=%p, context=%llu, seq=%u",
		      __entry->name, __entry->id,
		      __entry->fence, __entry->ctx,
		      __entry->seqno)
);

#पूर्ण_अगर

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm/scheduler
#समावेश <trace/define_trace.h>
