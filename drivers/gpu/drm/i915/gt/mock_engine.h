<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __MOCK_ENGINE_H__
#घोषणा __MOCK_ENGINE_H__

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>

#समावेश "gt/intel_engine.h"

काष्ठा mock_engine अणु
	काष्ठा पूर्णांकel_engine_cs base;

	spinlock_t hw_lock;
	काष्ठा list_head hw_queue;
	काष्ठा समयr_list hw_delay;
पूर्ण;

काष्ठा पूर्णांकel_engine_cs *mock_engine(काष्ठा drm_i915_निजी *i915,
				    स्थिर अक्षर *name,
				    पूर्णांक id);
पूर्णांक mock_engine_init(काष्ठा पूर्णांकel_engine_cs *engine);

व्योम mock_engine_flush(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम mock_engine_reset(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम mock_engine_मुक्त(काष्ठा पूर्णांकel_engine_cs *engine);

#पूर्ण_अगर /* !__MOCK_ENGINE_H__ */
