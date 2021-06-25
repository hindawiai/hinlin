<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2018 Intel Corporation
 */

#अगर_अघोषित _INTEL_WORKAROUNDS_H_
#घोषणा _INTEL_WORKAROUNDS_H_

#समावेश <linux/slab.h>

#समावेश "intel_workarounds_types.h"

काष्ठा drm_i915_निजी;
काष्ठा i915_request;
काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_gt;

अटल अंतरभूत व्योम पूर्णांकel_wa_list_मुक्त(काष्ठा i915_wa_list *wal)
अणु
	kमुक्त(wal->list);
	स_रखो(wal, 0, माप(*wal));
पूर्ण

व्योम पूर्णांकel_engine_init_ctx_wa(काष्ठा पूर्णांकel_engine_cs *engine);
पूर्णांक पूर्णांकel_engine_emit_ctx_wa(काष्ठा i915_request *rq);

व्योम पूर्णांकel_gt_init_workarounds(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_gt_apply_workarounds(काष्ठा पूर्णांकel_gt *gt);
bool पूर्णांकel_gt_verअगरy_workarounds(काष्ठा पूर्णांकel_gt *gt, स्थिर अक्षर *from);

व्योम पूर्णांकel_engine_init_whitelist(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम पूर्णांकel_engine_apply_whitelist(काष्ठा पूर्णांकel_engine_cs *engine);

व्योम पूर्णांकel_engine_init_workarounds(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम पूर्णांकel_engine_apply_workarounds(काष्ठा पूर्णांकel_engine_cs *engine);
पूर्णांक पूर्णांकel_engine_verअगरy_workarounds(काष्ठा पूर्णांकel_engine_cs *engine,
				    स्थिर अक्षर *from);

#पूर्ण_अगर
