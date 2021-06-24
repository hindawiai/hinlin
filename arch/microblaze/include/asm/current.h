<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_CURRENT_H
#घोषणा _ASM_MICROBLAZE_CURRENT_H

/*
 * Register used to hold the current task poपूर्णांकer जबतक in the kernel.
 * Any `call clobbered' रेजिस्टर without a special meaning should be OK,
 * but check यंत्र/microblaze/kernel/entry.S to be sure.
 */
#घोषणा CURRENT_TASK	r31
# अगरndef __ASSEMBLY__
/*
 * Dedicate r31 to keeping the current task poपूर्णांकer
 */
रेजिस्टर काष्ठा task_काष्ठा *current यंत्र("r31");

# define get_current()	current
# endअगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_MICROBLAZE_CURRENT_H */
