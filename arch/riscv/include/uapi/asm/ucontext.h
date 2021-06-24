<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2017 SiFive, Inc.
 *
 * This file was copied from arch/arm64/include/uapi/यंत्र/ucontext.h
 */
#अगर_अघोषित _UAPI_ASM_RISCV_UCONTEXT_H
#घोषणा _UAPI_ASM_RISCV_UCONTEXT_H

#समावेश <linux/types.h>

काष्ठा ucontext अणु
	अचिन्हित दीर्घ	  uc_flags;
	काष्ठा ucontext	 *uc_link;
	stack_t		  uc_stack;
	sigset_t	  uc_sigmask;
	/* There's some padding here to allow sigset_t to be expanded in the
	 * future.  Though this is unlikely, other architectures put uc_sigmask
	 * at the end of this काष्ठाure and explicitly state it can be
	 * expanded, so we didn't want to box ourselves in here. */
	__u8		  __unused[1024 / 8 - माप(sigset_t)];
	/* We can't put uc_sigmask at the end of this काष्ठाure because we need
	 * to be able to expand sigcontext in the future.  For example, the
	 * vector ISA extension will almost certainly add ISA state.  We want
	 * to ensure all user-visible ISA state can be saved and restored via a
	 * ucontext, so we're putting this at the end in order to allow क्रम
	 * infinite extensibility.  Since we know this will be extended and we
	 * assume sigset_t won't be extended an extreme amount, we're
	 * prioritizing this. */
	काष्ठा sigcontext uc_mcontext;
पूर्ण;

#पूर्ण_अगर /* _UAPI_ASM_RISCV_UCONTEXT_H */
