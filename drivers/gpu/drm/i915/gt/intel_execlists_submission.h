<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014 Intel Corporation
 */

#अगर_अघोषित __INTEL_EXECLISTS_SUBMISSION_H__
#घोषणा __INTEL_EXECLISTS_SUBMISSION_H__

#समावेश <linux/llist.h>
#समावेश <linux/types.h>

काष्ठा drm_prपूर्णांकer;

काष्ठा i915_request;
काष्ठा पूर्णांकel_context;
काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_gt;

क्रमागत अणु
	INTEL_CONTEXT_SCHEDULE_IN = 0,
	INTEL_CONTEXT_SCHEDULE_OUT,
	INTEL_CONTEXT_SCHEDULE_PREEMPTED,
पूर्ण;

पूर्णांक पूर्णांकel_execlists_submission_setup(काष्ठा पूर्णांकel_engine_cs *engine);

व्योम पूर्णांकel_execlists_show_requests(काष्ठा पूर्णांकel_engine_cs *engine,
				   काष्ठा drm_prपूर्णांकer *m,
				   व्योम (*show_request)(काष्ठा drm_prपूर्णांकer *m,
							स्थिर काष्ठा i915_request *rq,
							स्थिर अक्षर *prefix,
							पूर्णांक indent),
				   अचिन्हित पूर्णांक max);

काष्ठा पूर्णांकel_context *
पूर्णांकel_execlists_create_भव(काष्ठा पूर्णांकel_engine_cs **siblings,
			       अचिन्हित पूर्णांक count);

काष्ठा पूर्णांकel_context *
पूर्णांकel_execlists_clone_भव(काष्ठा पूर्णांकel_engine_cs *src);

पूर्णांक पूर्णांकel_भव_engine_attach_bond(काष्ठा पूर्णांकel_engine_cs *engine,
				     स्थिर काष्ठा पूर्णांकel_engine_cs *master,
				     स्थिर काष्ठा पूर्णांकel_engine_cs *sibling);

bool
पूर्णांकel_engine_in_execlists_submission_mode(स्थिर काष्ठा पूर्णांकel_engine_cs *engine);

#पूर्ण_अगर /* __INTEL_EXECLISTS_SUBMISSION_H__ */
