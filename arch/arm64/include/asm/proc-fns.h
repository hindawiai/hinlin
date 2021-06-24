<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/proc-fns.h
 *
 * Copyright (C) 1997-1999 Russell King
 * Copyright (C) 2000 Deep Blue Solutions Ltd
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_PROCFNS_H
#घोषणा __ASM_PROCFNS_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/page.h>

काष्ठा cpu_suspend_ctx;

बाह्य व्योम cpu_करो_idle(व्योम);
बाह्य व्योम cpu_करो_suspend(काष्ठा cpu_suspend_ctx *ptr);
बाह्य u64 cpu_करो_resume(phys_addr_t ptr, u64 idmap_ttbr);

#समावेश <यंत्र/memory.h>

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_PROCFNS_H */
