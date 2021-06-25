<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_RPS_H
#घोषणा INTEL_RPS_H

#समावेश "intel_rps_types.h"

काष्ठा i915_request;

व्योम पूर्णांकel_rps_init_early(काष्ठा पूर्णांकel_rps *rps);
व्योम पूर्णांकel_rps_init(काष्ठा पूर्णांकel_rps *rps);
व्योम पूर्णांकel_rps_sanitize(काष्ठा पूर्णांकel_rps *rps);

व्योम पूर्णांकel_rps_driver_रेजिस्टर(काष्ठा पूर्णांकel_rps *rps);
व्योम पूर्णांकel_rps_driver_unरेजिस्टर(काष्ठा पूर्णांकel_rps *rps);

व्योम पूर्णांकel_rps_enable(काष्ठा पूर्णांकel_rps *rps);
व्योम पूर्णांकel_rps_disable(काष्ठा पूर्णांकel_rps *rps);

व्योम पूर्णांकel_rps_park(काष्ठा पूर्णांकel_rps *rps);
व्योम पूर्णांकel_rps_unpark(काष्ठा पूर्णांकel_rps *rps);
व्योम पूर्णांकel_rps_boost(काष्ठा i915_request *rq);

पूर्णांक पूर्णांकel_rps_set(काष्ठा पूर्णांकel_rps *rps, u8 val);
व्योम पूर्णांकel_rps_mark_पूर्णांकeractive(काष्ठा पूर्णांकel_rps *rps, bool पूर्णांकeractive);

पूर्णांक पूर्णांकel_gpu_freq(काष्ठा पूर्णांकel_rps *rps, पूर्णांक val);
पूर्णांक पूर्णांकel_freq_opcode(काष्ठा पूर्णांकel_rps *rps, पूर्णांक val);
u32 पूर्णांकel_rps_get_cagf(काष्ठा पूर्णांकel_rps *rps, u32 rpstat1);
u32 पूर्णांकel_rps_पढ़ो_actual_frequency(काष्ठा पूर्णांकel_rps *rps);

व्योम gen5_rps_irq_handler(काष्ठा पूर्णांकel_rps *rps);
व्योम gen6_rps_irq_handler(काष्ठा पूर्णांकel_rps *rps, u32 pm_iir);
व्योम gen11_rps_irq_handler(काष्ठा पूर्णांकel_rps *rps, u32 pm_iir);

अटल अंतरभूत bool पूर्णांकel_rps_is_enabled(स्थिर काष्ठा पूर्णांकel_rps *rps)
अणु
	वापस test_bit(INTEL_RPS_ENABLED, &rps->flags);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_rps_set_enabled(काष्ठा पूर्णांकel_rps *rps)
अणु
	set_bit(INTEL_RPS_ENABLED, &rps->flags);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_rps_clear_enabled(काष्ठा पूर्णांकel_rps *rps)
अणु
	clear_bit(INTEL_RPS_ENABLED, &rps->flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_rps_is_active(स्थिर काष्ठा पूर्णांकel_rps *rps)
अणु
	वापस test_bit(INTEL_RPS_ACTIVE, &rps->flags);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_rps_set_active(काष्ठा पूर्णांकel_rps *rps)
अणु
	set_bit(INTEL_RPS_ACTIVE, &rps->flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_rps_clear_active(काष्ठा पूर्णांकel_rps *rps)
अणु
	वापस test_and_clear_bit(INTEL_RPS_ACTIVE, &rps->flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_rps_has_पूर्णांकerrupts(स्थिर काष्ठा पूर्णांकel_rps *rps)
अणु
	वापस test_bit(INTEL_RPS_INTERRUPTS, &rps->flags);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_rps_set_पूर्णांकerrupts(काष्ठा पूर्णांकel_rps *rps)
अणु
	set_bit(INTEL_RPS_INTERRUPTS, &rps->flags);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_rps_clear_पूर्णांकerrupts(काष्ठा पूर्णांकel_rps *rps)
अणु
	clear_bit(INTEL_RPS_INTERRUPTS, &rps->flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_rps_uses_समयr(स्थिर काष्ठा पूर्णांकel_rps *rps)
अणु
	वापस test_bit(INTEL_RPS_TIMER, &rps->flags);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_rps_set_समयr(काष्ठा पूर्णांकel_rps *rps)
अणु
	set_bit(INTEL_RPS_TIMER, &rps->flags);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_rps_clear_समयr(काष्ठा पूर्णांकel_rps *rps)
अणु
	clear_bit(INTEL_RPS_TIMER, &rps->flags);
पूर्ण

#पूर्ण_अगर /* INTEL_RPS_H */
