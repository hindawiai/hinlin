<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 */

#अगर_अघोषित _ASM_MIPS_BOARDS_LAUNCH_H
#घोषणा _ASM_MIPS_BOARDS_LAUNCH_H

#अगर_अघोषित _ASSEMBLER_

काष्ठा cpulaunch अणु
    अचिन्हित दीर्घ	pc;
    अचिन्हित दीर्घ	gp;
    अचिन्हित दीर्घ	sp;
    अचिन्हित दीर्घ	a0;
    अचिन्हित दीर्घ	_pad[3]; /* pad to cache line size to aव्योम thrashing */
    अचिन्हित दीर्घ	flags;
पूर्ण;

#अन्यथा

#घोषणा LOG2CPULAUNCH	5
#घोषणा LAUNCH_PC	0
#घोषणा LAUNCH_GP	4
#घोषणा LAUNCH_SP	8
#घोषणा LAUNCH_A0	12
#घोषणा LAUNCH_FLAGS	28

#पूर्ण_अगर

#घोषणा LAUNCH_FREADY	1
#घोषणा LAUNCH_FGO	2
#घोषणा LAUNCH_FGONE	4

#घोषणा CPULAUNCH	0x00000f00
#घोषणा NCPULAUNCH	8

/* Polling period in count cycles क्रम secondary CPU's */
#घोषणा LAUNCHPERIOD	10000

#पूर्ण_अगर /* _ASM_MIPS_BOARDS_LAUNCH_H */
