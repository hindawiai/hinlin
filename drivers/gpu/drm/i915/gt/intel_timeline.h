<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित I915_TIMELINE_H
#घोषणा I915_TIMELINE_H

#समावेश <linux/lockdep.h>

#समावेश "i915_active.h"
#समावेश "i915_syncmap.h"
#समावेश "intel_timeline_types.h"

काष्ठा drm_prपूर्णांकer;

काष्ठा पूर्णांकel_समयline *
__पूर्णांकel_समयline_create(काष्ठा पूर्णांकel_gt *gt,
			काष्ठा i915_vma *global_hwsp,
			अचिन्हित पूर्णांक offset);

अटल अंतरभूत काष्ठा पूर्णांकel_समयline *
पूर्णांकel_समयline_create(काष्ठा पूर्णांकel_gt *gt)
अणु
	वापस __पूर्णांकel_समयline_create(gt, शून्य, 0);
पूर्ण

काष्ठा पूर्णांकel_समयline *
पूर्णांकel_समयline_create_from_engine(काष्ठा पूर्णांकel_engine_cs *engine,
				  अचिन्हित पूर्णांक offset);

अटल अंतरभूत काष्ठा पूर्णांकel_समयline *
पूर्णांकel_समयline_get(काष्ठा पूर्णांकel_समयline *समयline)
अणु
	kref_get(&समयline->kref);
	वापस समयline;
पूर्ण

व्योम __पूर्णांकel_समयline_मुक्त(काष्ठा kref *kref);
अटल अंतरभूत व्योम पूर्णांकel_समयline_put(काष्ठा पूर्णांकel_समयline *समयline)
अणु
	kref_put(&समयline->kref, __पूर्णांकel_समयline_मुक्त);
पूर्ण

अटल अंतरभूत पूर्णांक __पूर्णांकel_समयline_sync_set(काष्ठा पूर्णांकel_समयline *tl,
					    u64 context, u32 seqno)
अणु
	वापस i915_syncmap_set(&tl->sync, context, seqno);
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_समयline_sync_set(काष्ठा पूर्णांकel_समयline *tl,
					  स्थिर काष्ठा dma_fence *fence)
अणु
	वापस __पूर्णांकel_समयline_sync_set(tl, fence->context, fence->seqno);
पूर्ण

अटल अंतरभूत bool __पूर्णांकel_समयline_sync_is_later(काष्ठा पूर्णांकel_समयline *tl,
						  u64 context, u32 seqno)
अणु
	वापस i915_syncmap_is_later(&tl->sync, context, seqno);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_समयline_sync_is_later(काष्ठा पूर्णांकel_समयline *tl,
						स्थिर काष्ठा dma_fence *fence)
अणु
	वापस __पूर्णांकel_समयline_sync_is_later(tl, fence->context, fence->seqno);
पूर्ण

व्योम __पूर्णांकel_समयline_pin(काष्ठा पूर्णांकel_समयline *tl);
पूर्णांक पूर्णांकel_समयline_pin(काष्ठा पूर्णांकel_समयline *tl, काष्ठा i915_gem_ww_ctx *ww);
व्योम पूर्णांकel_समयline_enter(काष्ठा पूर्णांकel_समयline *tl);
पूर्णांक पूर्णांकel_समयline_get_seqno(काष्ठा पूर्णांकel_समयline *tl,
			     काष्ठा i915_request *rq,
			     u32 *seqno);
व्योम पूर्णांकel_समयline_निकास(काष्ठा पूर्णांकel_समयline *tl);
व्योम पूर्णांकel_समयline_unpin(काष्ठा पूर्णांकel_समयline *tl);

व्योम पूर्णांकel_समयline_reset_seqno(स्थिर काष्ठा पूर्णांकel_समयline *tl);

पूर्णांक पूर्णांकel_समयline_पढ़ो_hwsp(काष्ठा i915_request *from,
			     काष्ठा i915_request *until,
			     u32 *hwsp_offset);

व्योम पूर्णांकel_gt_init_समयlines(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_fini_समयlines(काष्ठा पूर्णांकel_gt *gt);

व्योम पूर्णांकel_gt_show_समयlines(काष्ठा पूर्णांकel_gt *gt,
			     काष्ठा drm_prपूर्णांकer *m,
			     व्योम (*show_request)(काष्ठा drm_prपूर्णांकer *m,
						  स्थिर काष्ठा i915_request *rq,
						  स्थिर अक्षर *prefix,
						  पूर्णांक indent));

अटल अंतरभूत bool
पूर्णांकel_समयline_is_last(स्थिर काष्ठा पूर्णांकel_समयline *tl,
		       स्थिर काष्ठा i915_request *rq)
अणु
	वापस list_is_last_rcu(&rq->link, &tl->requests);
पूर्ण

I915_SELFTEST_DECLARE(पूर्णांक पूर्णांकel_समयline_pin_map(काष्ठा पूर्णांकel_समयline *tl));

#पूर्ण_अगर
