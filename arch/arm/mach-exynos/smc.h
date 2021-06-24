<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (c) 2012 Samsung Electronics.
 *
 * Exynos - SMC Call
 */

#अगर_अघोषित __ASM_ARCH_EXYNOS_SMC_H
#घोषणा __ASM_ARCH_EXYNOS_SMC_H

#घोषणा SMC_CMD_INIT		(-1)
#घोषणा SMC_CMD_INFO		(-2)
/* For Power Management */
#घोषणा SMC_CMD_SLEEP		(-3)
#घोषणा SMC_CMD_CPU1BOOT	(-4)
#घोषणा SMC_CMD_CPU0AFTR	(-5)
#घोषणा SMC_CMD_SAVE		(-6)
#घोषणा SMC_CMD_SHUTDOWN	(-7)
/* For CP15 Access */
#घोषणा SMC_CMD_C15RESUME	(-11)
/* For L2 Cache Access */
#घोषणा SMC_CMD_L2X0CTRL	(-21)
#घोषणा SMC_CMD_L2X0SETUP1	(-22)
#घोषणा SMC_CMD_L2X0SETUP2	(-23)
#घोषणा SMC_CMD_L2X0INVALL	(-24)
#घोषणा SMC_CMD_L2X0DEBUG	(-25)

/* For Accessing CP15/SFR (General) */
#घोषणा SMC_CMD_REG		(-101)

/* defines क्रम SMC_CMD_REG */
#घोषणा SMC_REG_CLASS_SFR_W	(0x1 << 30)
#घोषणा SMC_REG_ID_SFR_W(addr)	(SMC_REG_CLASS_SFR_W | ((addr) >> 2))

#अगर_अघोषित __ASSEMBLY__

बाह्य व्योम exynos_smc(u32 cmd, u32 arg1, u32 arg2, u32 arg3);

#पूर्ण_अगर /* __ASSEMBLY__ */

/* op type क्रम SMC_CMD_SAVE and SMC_CMD_SHUTDOWN */
#घोषणा OP_TYPE_CORE		0x0
#घोषणा OP_TYPE_CLUSTER		0x1

/* Power State required क्रम SMC_CMD_SAVE and SMC_CMD_SHUTDOWN */
#घोषणा SMC_POWERSTATE_IDLE	0x1

#पूर्ण_अगर
