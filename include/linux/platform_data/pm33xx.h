<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * TI pm33xx platक्रमm data
 *
 * Copyright (C) 2016-2018 Texas Instruments, Inc.
 *	Dave Gerlach <d-gerlach@ti.com>
 */

#अगर_अघोषित _LINUX_PLATFORM_DATA_PM33XX_H
#घोषणा _LINUX_PLATFORM_DATA_PM33XX_H

#समावेश <linux/kbuild.h>
#समावेश <linux/types.h>

/*
 * WFI Flags क्रम sleep code control
 *
 * These flags allow PM code to exclude certain operations from happening
 * in the low level ASM code found in sleep33xx.S and sleep43xx.S
 *
 * WFI_FLAG_FLUSH_CACHE: Flush the ARM caches and disable caching. Only
 *			 needed when MPU will lose context.
 * WFI_FLAG_SELF_REFRESH: Let EMIF place DDR memory पूर्णांकo self-refresh and
 *			  disable EMIF.
 * WFI_FLAG_SAVE_EMIF: Save context of all EMIF रेजिस्टरs and restore in
 *		       resume path. Only needed अगर PER करोमुख्य loses context
 *		       and must also have WFI_FLAG_SELF_REFRESH set.
 * WFI_FLAG_WAKE_M3: Disable MPU घड़ी or घड़ीकरोमुख्य to cause wkup_m3 to
 *		     execute when WFI inकाष्ठाion executes.
 * WFI_FLAG_RTC_ONLY: Configure the RTC to enter RTC+DDR mode.
 */
#घोषणा WFI_FLAG_FLUSH_CACHE		BIT(0)
#घोषणा WFI_FLAG_SELF_REFRESH		BIT(1)
#घोषणा WFI_FLAG_SAVE_EMIF		BIT(2)
#घोषणा WFI_FLAG_WAKE_M3		BIT(3)
#घोषणा WFI_FLAG_RTC_ONLY		BIT(4)

#अगर_अघोषित __ASSEMBLER__
काष्ठा am33xx_pm_sram_addr अणु
	व्योम (*करो_wfi)(व्योम);
	अचिन्हित दीर्घ *करो_wfi_sz;
	अचिन्हित दीर्घ *resume_offset;
	अचिन्हित दीर्घ *emअगर_sram_table;
	अचिन्हित दीर्घ *ro_sram_data;
	अचिन्हित दीर्घ resume_address;
पूर्ण;

काष्ठा am33xx_pm_platक्रमm_data अणु
	पूर्णांक     (*init)(पूर्णांक (*idle)(u32 wfi_flags));
	पूर्णांक     (*deinit)(व्योम);
	पूर्णांक	(*soc_suspend)(अचिन्हित पूर्णांक state, पूर्णांक (*fn)(अचिन्हित दीर्घ),
			       अचिन्हित दीर्घ args);
	पूर्णांक	(*cpu_suspend)(पूर्णांक (*fn)(अचिन्हित दीर्घ), अचिन्हित दीर्घ args);
	व्योम    (*begin_suspend)(व्योम);
	व्योम    (*finish_suspend)(व्योम);
	काष्ठा  am33xx_pm_sram_addr *(*get_sram_addrs)(व्योम);
	व्योम (*save_context)(व्योम);
	व्योम (*restore_context)(व्योम);
	पूर्णांक (*check_off_mode_enable)(व्योम);
पूर्ण;

काष्ठा am33xx_pm_sram_data अणु
	u32 wfi_flags;
	u32 l2_aux_ctrl_val;
	u32 l2_prefetch_ctrl_val;
पूर्ण __packed __aligned(8);

काष्ठा am33xx_pm_ro_sram_data अणु
	u32 amx3_pm_sram_data_virt;
	u32 amx3_pm_sram_data_phys;
	व्योम __iomem *rtc_base_virt;
पूर्ण __packed __aligned(8);

#पूर्ण_अगर /* __ASSEMBLER__ */
#पूर्ण_अगर /* _LINUX_PLATFORM_DATA_PM33XX_H */
