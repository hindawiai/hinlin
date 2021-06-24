<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_RC6_H
#घोषणा INTEL_RC6_H

#समावेश "i915_reg.h"

काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_rc6;

व्योम पूर्णांकel_rc6_init(काष्ठा पूर्णांकel_rc6 *rc6);
व्योम पूर्णांकel_rc6_fini(काष्ठा पूर्णांकel_rc6 *rc6);

व्योम पूर्णांकel_rc6_unpark(काष्ठा पूर्णांकel_rc6 *rc6);
व्योम पूर्णांकel_rc6_park(काष्ठा पूर्णांकel_rc6 *rc6);

व्योम पूर्णांकel_rc6_sanitize(काष्ठा पूर्णांकel_rc6 *rc6);
व्योम पूर्णांकel_rc6_enable(काष्ठा पूर्णांकel_rc6 *rc6);
व्योम पूर्णांकel_rc6_disable(काष्ठा पूर्णांकel_rc6 *rc6);

u64 पूर्णांकel_rc6_residency_ns(काष्ठा पूर्णांकel_rc6 *rc6, i915_reg_t reg);
u64 पूर्णांकel_rc6_residency_us(काष्ठा पूर्णांकel_rc6 *rc6, i915_reg_t reg);

#पूर्ण_अगर /* INTEL_RC6_H */
