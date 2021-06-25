<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_ENGINE_PM_H
#घोषणा INTEL_ENGINE_PM_H

#समावेश "i915_request.h"
#समावेश "intel_engine_types.h"
#समावेश "intel_wakeref.h"

अटल अंतरभूत bool
पूर्णांकel_engine_pm_is_awake(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस पूर्णांकel_wakeref_is_active(&engine->wakeref);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_engine_pm_get(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_wakeref_get(&engine->wakeref);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_engine_pm_get_अगर_awake(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस पूर्णांकel_wakeref_get_अगर_active(&engine->wakeref);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_engine_pm_put(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_wakeref_put(&engine->wakeref);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_engine_pm_put_async(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_wakeref_put_async(&engine->wakeref);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_engine_pm_put_delay(काष्ठा पूर्णांकel_engine_cs *engine,
					     अचिन्हित दीर्घ delay)
अणु
	पूर्णांकel_wakeref_put_delay(&engine->wakeref, delay);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_engine_pm_flush(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_wakeref_unlock_रुको(&engine->wakeref);
पूर्ण

अटल अंतरभूत काष्ठा i915_request *
पूर्णांकel_engine_create_kernel_request(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_request *rq;

	/*
	 * The engine->kernel_context is special as it is used inside
	 * the engine-pm barrier (see __engine_park()), circumventing
	 * the usual mutexes and relying on the engine-pm barrier
	 * instead. So whenever we use the engine->kernel_context
	 * outside of the barrier, we must manually handle the
	 * engine wakeref to serialise with the use inside.
	 */
	पूर्णांकel_engine_pm_get(engine);
	rq = i915_request_create(engine->kernel_context);
	पूर्णांकel_engine_pm_put(engine);

	वापस rq;
पूर्ण

व्योम पूर्णांकel_engine_init__pm(काष्ठा पूर्णांकel_engine_cs *engine);

#पूर्ण_अगर /* INTEL_ENGINE_PM_H */
