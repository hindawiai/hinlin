<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __M68K_FPU_H
#घोषणा __M68K_FPU_H


/*
 * MAX भग्नing poपूर्णांक unit state size (FSAVE/FRESTORE)
 */

#अगर defined(CONFIG_M68020) || defined(CONFIG_M68030)
#घोषणा FPSTATESIZE (216)
#या_अगर defined(CONFIG_M68040)
#घोषणा FPSTATESIZE (96)
#या_अगर defined(CONFIG_M68KFPU_EMU)
#घोषणा FPSTATESIZE (28)
#या_अगर defined(CONFIG_COLDFIRE) && defined(CONFIG_MMU)
#घोषणा FPSTATESIZE (16)
#या_अगर defined(CONFIG_M68060)
#घोषणा FPSTATESIZE (12)
#अन्यथा
#घोषणा FPSTATESIZE (0)
#पूर्ण_अगर

#पूर्ण_अगर /* __M68K_FPU_H */
