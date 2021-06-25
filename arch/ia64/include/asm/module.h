<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_MODULE_H
#घोषणा _ASM_IA64_MODULE_H

#समावेश <यंत्र-generic/module.h>

/*
 * IA-64-specअगरic support क्रम kernel module loader.
 *
 * Copyright (C) 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

काष्ठा elf64_shdr;			/* क्रमward declration */

काष्ठा mod_arch_specअगरic अणु
	/* Used only at module load समय. */
	काष्ठा elf64_shdr *core_plt;	/* core PLT section */
	काष्ठा elf64_shdr *init_plt;	/* init PLT section */
	काष्ठा elf64_shdr *got;		/* global offset table */
	काष्ठा elf64_shdr *opd;		/* official procedure descriptors */
	काष्ठा elf64_shdr *unwind;	/* unwind-table section */
	अचिन्हित दीर्घ gp;		/* global-poपूर्णांकer क्रम module */
	अचिन्हित पूर्णांक next_got_entry;	/* index of next available got entry */

	/* Used at module run and cleanup समय. */
	व्योम *core_unw_table;		/* core unwind-table cookie वापसed by unwinder */
	व्योम *init_unw_table;		/* init unwind-table cookie वापसed by unwinder */
	व्योम *opd_addr;			/* symbolize uses .opd to get to actual function */
	अचिन्हित दीर्घ opd_size;
पूर्ण;

#घोषणा ARCH_SHF_SMALL	SHF_IA_64_SHORT

#पूर्ण_अगर /* _ASM_IA64_MODULE_H */
