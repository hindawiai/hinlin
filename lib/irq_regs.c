<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* saved per-CPU IRQ रेजिस्टर poपूर्णांकer
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#समावेश <linux/export.h>
#समावेश <linux/percpu.h>
#समावेश <यंत्र/irq_regs.h>

#अगर_अघोषित ARCH_HAS_OWN_IRQ_REGS
DEFINE_PER_CPU(काष्ठा pt_regs *, __irq_regs);
EXPORT_PER_CPU_SYMBOL(__irq_regs);
#पूर्ण_अगर
