<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_MMU_H
#घोषणा __ASM_GENERIC_MMU_H

/*
 * This is the mmu.h header क्रम nommu implementations.
 * Architectures with an MMU need something more complex.
 */
#अगर_अघोषित __ASSEMBLY__
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ		end_brk;

#अगर_घोषित CONFIG_BINFMT_ELF_FDPIC
	अचिन्हित दीर्घ		exec_fdpic_loadmap;
	अचिन्हित दीर्घ		पूर्णांकerp_fdpic_loadmap;
#पूर्ण_अगर
पूर्ण mm_context_t;
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_MMU_H */
