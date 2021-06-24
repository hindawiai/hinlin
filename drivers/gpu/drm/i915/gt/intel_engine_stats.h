<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __INTEL_ENGINE_STATS_H__
#घोषणा __INTEL_ENGINE_STATS_H__

#समावेश <linux/atomic.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/seqlock.h>

#समावेश "i915_gem.h" /* GEM_BUG_ON */
#समावेश "intel_engine.h"

अटल अंतरभूत व्योम पूर्णांकel_engine_context_in(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अचिन्हित दीर्घ flags;

	अगर (engine->stats.active) अणु
		engine->stats.active++;
		वापस;
	पूर्ण

	/* The ग_लिखोr is serialised; but the pmu पढ़ोer may be from hardirq */
	local_irq_save(flags);
	ग_लिखो_seqcount_begin(&engine->stats.lock);

	engine->stats.start = kसमय_get();
	engine->stats.active++;

	ग_लिखो_seqcount_end(&engine->stats.lock);
	local_irq_restore(flags);

	GEM_BUG_ON(!engine->stats.active);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_engine_context_out(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अचिन्हित दीर्घ flags;

	GEM_BUG_ON(!engine->stats.active);
	अगर (engine->stats.active > 1) अणु
		engine->stats.active--;
		वापस;
	पूर्ण

	local_irq_save(flags);
	ग_लिखो_seqcount_begin(&engine->stats.lock);

	engine->stats.active--;
	engine->stats.total =
		kसमय_add(engine->stats.total,
			  kसमय_sub(kसमय_get(), engine->stats.start));

	ग_लिखो_seqcount_end(&engine->stats.lock);
	local_irq_restore(flags);
पूर्ण

#पूर्ण_अगर /* __INTEL_ENGINE_STATS_H__ */
