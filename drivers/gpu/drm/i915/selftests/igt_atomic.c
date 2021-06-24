<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/preempt.h>
#समावेश <linux/bottom_half.h>
#समावेश <linux/irqflags.h>

#समावेश "igt_atomic.h"

अटल व्योम __preempt_begin(व्योम)
अणु
	preempt_disable();
पूर्ण

अटल व्योम __preempt_end(व्योम)
अणु
	preempt_enable();
पूर्ण

अटल व्योम __softirq_begin(व्योम)
अणु
	local_bh_disable();
पूर्ण

अटल व्योम __softirq_end(व्योम)
अणु
	local_bh_enable();
पूर्ण

अटल व्योम __hardirq_begin(व्योम)
अणु
	local_irq_disable();
पूर्ण

अटल व्योम __hardirq_end(व्योम)
अणु
	local_irq_enable();
पूर्ण

स्थिर काष्ठा igt_atomic_section igt_atomic_phases[] = अणु
	अणु "preempt", __preempt_begin, __preempt_end पूर्ण,
	अणु "softirq", __softirq_begin, __softirq_end पूर्ण,
	अणु "hardirq", __hardirq_begin, __hardirq_end पूर्ण,
	अणु पूर्ण
पूर्ण;
