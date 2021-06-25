<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */
#अगर_अघोषित _ASM_MICROBLAZE_SETUP_H
#घोषणा _ASM_MICROBLAZE_SETUP_H

#समावेश <uapi/यंत्र/setup.h>

# अगरndef __ASSEMBLY__
बाह्य अक्षर cmd_line[COMMAND_LINE_SIZE];

बाह्य अक्षर *klimit;

बाह्य व्योम mmu_reset(व्योम);

व्योम समय_init(व्योम);
व्योम init_IRQ(व्योम);
व्योम machine_early_init(स्थिर अक्षर *cmdline, अचिन्हित पूर्णांक ram,
		अचिन्हित पूर्णांक fdt, अचिन्हित पूर्णांक msr, अचिन्हित पूर्णांक tlb0,
		अचिन्हित पूर्णांक tlb1);

व्योम machine_restart(अक्षर *cmd);
व्योम machine_shutकरोwn(व्योम);
व्योम machine_halt(व्योम);
व्योम machine_घातer_off(व्योम);

बाह्य व्योम *zalloc_maybe_booपंचांगem(माप_प्रकार size, gfp_t mask);

# endअगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_MICROBLAZE_SETUP_H */
