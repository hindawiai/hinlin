<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2008-2018 Intel Corporation
 */

#अगर_अघोषित I915_RESET_H
#घोषणा I915_RESET_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/srcu.h>

#समावेश "intel_engine_types.h"
#समावेश "intel_reset_types.h"

काष्ठा i915_request;
काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_gt;
काष्ठा पूर्णांकel_guc;

व्योम पूर्णांकel_gt_init_reset(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_fini_reset(काष्ठा पूर्णांकel_gt *gt);

__म_लिखो(4, 5)
व्योम पूर्णांकel_gt_handle_error(काष्ठा पूर्णांकel_gt *gt,
			   पूर्णांकel_engine_mask_t engine_mask,
			   अचिन्हित दीर्घ flags,
			   स्थिर अक्षर *fmt, ...);
#घोषणा I915_ERROR_CAPTURE BIT(0)

व्योम पूर्णांकel_gt_reset(काष्ठा पूर्णांकel_gt *gt,
		    पूर्णांकel_engine_mask_t stalled_mask,
		    स्थिर अक्षर *reason);
पूर्णांक पूर्णांकel_engine_reset(काष्ठा पूर्णांकel_engine_cs *engine,
		       स्थिर अक्षर *reason);
पूर्णांक __पूर्णांकel_engine_reset_bh(काष्ठा पूर्णांकel_engine_cs *engine,
			    स्थिर अक्षर *reason);

व्योम __i915_request_reset(काष्ठा i915_request *rq, bool guilty);

पूर्णांक __must_check पूर्णांकel_gt_reset_trylock(काष्ठा पूर्णांकel_gt *gt, पूर्णांक *srcu);
व्योम पूर्णांकel_gt_reset_unlock(काष्ठा पूर्णांकel_gt *gt, पूर्णांक tag);

व्योम पूर्णांकel_gt_set_wedged(काष्ठा पूर्णांकel_gt *gt);
bool पूर्णांकel_gt_unset_wedged(काष्ठा पूर्णांकel_gt *gt);
पूर्णांक पूर्णांकel_gt_terminally_wedged(काष्ठा पूर्णांकel_gt *gt);

/*
 * There's no unset_wedged_on_init paired with this one.
 * Once we're wedged on init, there's no going back.
 * Same thing क्रम unset_wedged_on_fini.
 */
व्योम पूर्णांकel_gt_set_wedged_on_init(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_set_wedged_on_fini(काष्ठा पूर्णांकel_gt *gt);

पूर्णांक __पूर्णांकel_gt_reset(काष्ठा पूर्णांकel_gt *gt, पूर्णांकel_engine_mask_t engine_mask);

पूर्णांक पूर्णांकel_reset_guc(काष्ठा पूर्णांकel_gt *gt);

काष्ठा पूर्णांकel_wedge_me अणु
	काष्ठा delayed_work work;
	काष्ठा पूर्णांकel_gt *gt;
	स्थिर अक्षर *name;
पूर्ण;

व्योम __पूर्णांकel_init_wedge(काष्ठा पूर्णांकel_wedge_me *w,
			काष्ठा पूर्णांकel_gt *gt,
			दीर्घ समयout,
			स्थिर अक्षर *name);
व्योम __पूर्णांकel_fini_wedge(काष्ठा पूर्णांकel_wedge_me *w);

#घोषणा पूर्णांकel_wedge_on_समयout(W, GT, TIMEOUT)				\
	क्रम (__पूर्णांकel_init_wedge((W), (GT), (TIMEOUT), __func__);	\
	     (W)->gt;							\
	     __पूर्णांकel_fini_wedge((W)))

bool पूर्णांकel_has_gpu_reset(स्थिर काष्ठा पूर्णांकel_gt *gt);
bool पूर्णांकel_has_reset_engine(स्थिर काष्ठा पूर्णांकel_gt *gt);

#पूर्ण_अगर /* I915_RESET_H */
