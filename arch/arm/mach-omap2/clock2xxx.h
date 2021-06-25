<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OMAP2 घड़ी function prototypes and macros
 *
 * Copyright (C) 2005-2010 Texas Instruments, Inc.
 * Copyright (C) 2004-2010 Nokia Corporation
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_CLOCK2XXX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_CLOCK2XXX_H

#समावेश <linux/clk-provider.h>
#समावेश "clock.h"

अचिन्हित दीर्घ omap2_table_mpu_recalc(काष्ठा clk_hw *clk,
				     अचिन्हित दीर्घ parent_rate);
पूर्णांक omap2_select_table_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate);
दीर्घ omap2_round_to_table_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate);
अचिन्हित दीर्घ omap2xxx_sys_clk_recalc(काष्ठा clk_hw *clk,
				      अचिन्हित दीर्घ parent_rate);
अचिन्हित दीर्घ omap2_osc_clk_recalc(काष्ठा clk_hw *clk,
				   अचिन्हित दीर्घ parent_rate);
व्योम omap2xxx_clkt_dpllcore_init(काष्ठा clk_hw *hw);
अचिन्हित दीर्घ omap2xxx_clk_get_core_rate(व्योम);
u32 omap2xxx_get_sysclkभाग(व्योम);
व्योम omap2xxx_clk_prepare_क्रम_reboot(व्योम);
व्योम omap2xxx_clkt_vps_check_bootloader_rates(व्योम);
व्योम omap2xxx_clkt_vps_late_init(व्योम);

#अगर_घोषित CONFIG_SOC_OMAP2420
पूर्णांक omap2420_clk_init(व्योम);
#अन्यथा
#घोषणा omap2420_clk_init()	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2430
पूर्णांक omap2430_clk_init(व्योम);
#अन्यथा
#घोषणा omap2430_clk_init()	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

बाह्य काष्ठा clk_hw *dclk_hw;

#पूर्ण_अगर
