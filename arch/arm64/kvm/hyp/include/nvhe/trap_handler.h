<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Trap handler helpers.
 *
 * Copyright (C) 2020 - Google LLC
 * Author: Marc Zyngier <maz@kernel.org>
 */

#अगर_अघोषित __ARM64_KVM_NVHE_TRAP_HANDLER_H__
#घोषणा __ARM64_KVM_NVHE_TRAP_HANDLER_H__

#समावेश <यंत्र/kvm_host.h>

#घोषणा cpu_reg(ctxt, r)	(ctxt)->regs.regs[r]
#घोषणा DECLARE_REG(type, name, ctxt, reg)	\
				type name = (type)cpu_reg(ctxt, (reg))

#पूर्ण_अगर /* __ARM64_KVM_NVHE_TRAP_HANDLER_H__ */
