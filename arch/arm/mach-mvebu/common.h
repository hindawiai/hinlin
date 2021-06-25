<शैली गुरु>
/*
 * Core functions क्रम Marvell System On Chip
 *
 * Copyright (C) 2012 Marvell
 *
 * Lior Amsalem <alior@marvell.com>
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ARCH_MVEBU_COMMON_H
#घोषणा __ARCH_MVEBU_COMMON_H

#समावेश <linux/reboot.h>

व्योम mvebu_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd);
पूर्णांक mvebu_cpu_reset_deनिश्चित(पूर्णांक cpu);
व्योम mvebu_pmsu_set_cpu_boot_addr(पूर्णांक hw_cpu, व्योम *boot_addr);
व्योम mvebu_प्रणाली_controller_set_cpu_boot_addr(व्योम *boot_addr);
पूर्णांक mvebu_प्रणाली_controller_get_soc_id(u32 *dev, u32 *rev);

व्योम __iomem *mvebu_get_scu_base(व्योम);

पूर्णांक mvebu_pm_suspend_init(व्योम (*board_pm_enter)(व्योम __iomem *sdram_reg,
							u32 srcmd));
#पूर्ण_अगर
