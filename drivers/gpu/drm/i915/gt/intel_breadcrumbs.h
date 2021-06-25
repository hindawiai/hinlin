<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_BREADCRUMBS__
#घोषणा __INTEL_BREADCRUMBS__

#समावेश <linux/atomic.h>
#समावेश <linux/irq_work.h>

#समावेश "intel_engine_types.h"

काष्ठा drm_prपूर्णांकer;
काष्ठा i915_request;
काष्ठा पूर्णांकel_bपढ़ोcrumbs;

काष्ठा पूर्णांकel_bपढ़ोcrumbs *
पूर्णांकel_bपढ़ोcrumbs_create(काष्ठा पूर्णांकel_engine_cs *irq_engine);
व्योम पूर्णांकel_bपढ़ोcrumbs_मुक्त(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b);

व्योम पूर्णांकel_bपढ़ोcrumbs_reset(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b);
व्योम __पूर्णांकel_bपढ़ोcrumbs_park(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b);

अटल अंतरभूत व्योम पूर्णांकel_bपढ़ोcrumbs_unpark(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	atomic_inc(&b->active);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_bपढ़ोcrumbs_park(काष्ठा पूर्णांकel_bपढ़ोcrumbs *b)
अणु
	अगर (atomic_dec_and_test(&b->active))
		__पूर्णांकel_bपढ़ोcrumbs_park(b);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	irq_work_queue(&engine->bपढ़ोcrumbs->irq_work);
पूर्ण

व्योम पूर्णांकel_engine_prपूर्णांक_bपढ़ोcrumbs(काष्ठा पूर्णांकel_engine_cs *engine,
				    काष्ठा drm_prपूर्णांकer *p);

bool i915_request_enable_bपढ़ोcrumb(काष्ठा i915_request *request);
व्योम i915_request_cancel_bपढ़ोcrumb(काष्ठा i915_request *request);

व्योम पूर्णांकel_context_हटाओ_bपढ़ोcrumbs(काष्ठा पूर्णांकel_context *ce,
				      काष्ठा पूर्णांकel_bपढ़ोcrumbs *b);

#पूर्ण_अगर /* __INTEL_BREADCRUMBS__ */
