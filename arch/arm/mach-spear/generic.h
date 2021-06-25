<शैली गुरु>
/*
 * spear machine family generic header file
 *
 * Copyright (C) 2009-2012 ST Microelectronics
 * Rajeev Kumar <rajeev-dlh.kumar@st.com>
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __MACH_GENERIC_H
#घोषणा __MACH_GENERIC_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/amba/pl08x.h>
#समावेश <linux/init.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/mach/समय.स>

बाह्य अस्थिर पूर्णांक spear_pen_release;

बाह्य व्योम spear13xx_समयr_init(व्योम);
बाह्य व्योम spear3xx_समयr_init(व्योम);
बाह्य काष्ठा pl022_ssp_controller pl022_plat_data;
बाह्य काष्ठा pl08x_platक्रमm_data pl080_plat_data;

व्योम __init spear_setup_of_समयr(व्योम);
व्योम __init spear3xx_clk_init(व्योम __iomem *misc_base,
			      व्योम __iomem *soc_config_base);
व्योम __init spear3xx_map_io(व्योम);
व्योम __init spear3xx_dt_init_irq(व्योम);
व्योम __init spear6xx_clk_init(व्योम __iomem *misc_base);
व्योम __init spear13xx_map_io(व्योम);
व्योम __init spear13xx_l2x0_init(व्योम);

व्योम spear_restart(क्रमागत reboot_mode, स्थिर अक्षर *);

व्योम spear13xx_secondary_startup(व्योम);
व्योम spear13xx_cpu_die(अचिन्हित पूर्णांक cpu);

बाह्य स्थिर काष्ठा smp_operations spear13xx_smp_ops;

#पूर्ण_अगर /* __MACH_GENERIC_H */
