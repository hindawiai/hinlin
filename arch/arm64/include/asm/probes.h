<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm64/include/यंत्र/probes.h
 *
 * Copyright (C) 2013 Linaro Limited
 */
#अगर_अघोषित _ARM_PROBES_H
#घोषणा _ARM_PROBES_H

#समावेश <यंत्र/insn.h>

प्रकार u32 probe_opcode_t;
प्रकार व्योम (probes_handler_t) (u32 opcode, दीर्घ addr, काष्ठा pt_regs *);

/* architecture specअगरic copy of original inकाष्ठाion */
काष्ठा arch_probe_insn अणु
	probe_opcode_t *insn;
	pstate_check_t *pstate_cc;
	probes_handler_t *handler;
	/* restore address after step xol */
	अचिन्हित दीर्घ restore;
पूर्ण;
#अगर_घोषित CONFIG_KPROBES
प्रकार u32 kprobe_opcode_t;
काष्ठा arch_specअगरic_insn अणु
	काष्ठा arch_probe_insn api;
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर
