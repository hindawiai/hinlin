<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap-secure.h: OMAP Secure infraकाष्ठाure header.
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 * Copyright (C) 2012 Ivaylo Dimitrov <मुक्तmangorकरोn@abv.bg>
 * Copyright (C) 2013 Pali Rohथँr <pali@kernel.org>
 */
#अगर_अघोषित OMAP_ARCH_OMAP_SECURE_H
#घोषणा OMAP_ARCH_OMAP_SECURE_H

#समावेश <linux/types.h>

/* Monitor error code */
#घोषणा  API_HAL_RET_VALUE_NS2S_CONVERSION_ERROR	0xFFFFFFFE
#घोषणा  API_HAL_RET_VALUE_SERVICE_UNKNWON		0xFFFFFFFF

/* HAL API error codes */
#घोषणा  API_HAL_RET_VALUE_OK		0x00
#घोषणा  API_HAL_RET_VALUE_FAIL		0x01

/* Secure HAL API flags */
#घोषणा FLAG_START_CRITICAL		0x4
#घोषणा FLAG_IRQFIQ_MASK		0x3
#घोषणा FLAG_IRQ_ENABLE			0x2
#घोषणा FLAG_FIQ_ENABLE			0x1
#घोषणा NO_FLAG				0x0

/* Maximum Secure memory storage size */
#घोषणा OMAP_SECURE_RAM_STORAGE	(88 * SZ_1K)

#घोषणा OMAP3_SAVE_SECURE_RAM_SZ	0x803F

/* Secure low घातer HAL API index */
#घोषणा OMAP4_HAL_SAVESECURERAM_INDEX	0x1a
#घोषणा OMAP4_HAL_SAVEHW_INDEX		0x1b
#घोषणा OMAP4_HAL_SAVEALL_INDEX		0x1c
#घोषणा OMAP4_HAL_SAVEGIC_INDEX		0x1d

/* Secure Monitor mode APIs */
#घोषणा OMAP4_MON_SCU_PWR_INDEX		0x108
#घोषणा OMAP4_MON_L2X0_DBG_CTRL_INDEX	0x100
#घोषणा OMAP4_MON_L2X0_CTRL_INDEX	0x102
#घोषणा OMAP4_MON_L2X0_AUXCTRL_INDEX	0x109
#घोषणा OMAP4_MON_L2X0_PREFETCH_INDEX	0x113

#घोषणा OMAP5_DRA7_MON_SET_CNTFRQ_INDEX	0x109
#घोषणा OMAP5_MON_AMBA_IF_INDEX		0x108
#घोषणा OMAP5_DRA7_MON_SET_ACR_INDEX	0x107

/* Secure PPA(Primary Protected Application) APIs */
#घोषणा OMAP4_PPA_SERVICE_0		0x21
#घोषणा OMAP4_PPA_L2_POR_INDEX		0x23
#घोषणा OMAP4_PPA_CPU_ACTRL_SMP_INDEX	0x25

#घोषणा AM43xx_PPA_SVC_PM_SUSPEND	0x71
#घोषणा AM43xx_PPA_SVC_PM_RESUME	0x72

/* Secure RX-51 PPA (Primary Protected Application) APIs */
#घोषणा RX51_PPA_HWRNG			29
#घोषणा RX51_PPA_L2_INVAL		40
#घोषणा RX51_PPA_WRITE_ACR		42

#अगर_अघोषित __ASSEMBLER__

बाह्य u32 omap_secure_dispatcher(u32 idx, u32 flag, u32 nargs,
				u32 arg1, u32 arg2, u32 arg3, u32 arg4);
बाह्य व्योम omap_smccc_smc(u32 fn, u32 arg);
बाह्य व्योम omap_smc1(u32 fn, u32 arg);
बाह्य u32 omap_smc2(u32 id, u32 falg, u32 pargs);
बाह्य u32 omap_smc3(u32 id, u32 process, u32 flag, u32 pargs);
बाह्य phys_addr_t omap_secure_ram_mempool_base(व्योम);
बाह्य पूर्णांक omap_secure_ram_reserve_memblock(व्योम);
बाह्य u32 save_secure_ram_context(u32 args_pa);
बाह्य u32 omap3_save_secure_ram(व्योम __iomem *save_regs, पूर्णांक size);

बाह्य u32 rx51_secure_dispatcher(u32 idx, u32 process, u32 flag, u32 nargs,
				  u32 arg1, u32 arg2, u32 arg3, u32 arg4);
बाह्य u32 rx51_secure_update_aux_cr(u32 set_bits, u32 clear_bits);
बाह्य u32 rx51_secure_rng_call(u32 ptr, u32 count, u32 flag);

बाह्य bool optee_available;
व्योम omap_secure_init(व्योम);

#अगर_घोषित CONFIG_SOC_HAS_REALTIME_COUNTER
व्योम set_cntfreq(व्योम);
#अन्यथा
अटल अंतरभूत व्योम set_cntfreq(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLER__ */
#पूर्ण_अगर /* OMAP_ARCH_OMAP_SECURE_H */
