<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2020 STMicroelectronics - All Rights Reserved
 *
 * Author: Lee Jones <lee.jones@linaro.org>
 */

#अगर_अघोषित __LINUX_CLK_SPEAR_H
#घोषणा __LINUX_CLK_SPEAR_H

#अगर_घोषित CONFIG_MACH_SPEAR1310
व्योम __init spear1310_clk_init(व्योम __iomem *misc_base, व्योम __iomem *ras_base);
#अन्यथा
अटल अंतरभूत व्योम spear1310_clk_init(व्योम __iomem *misc_base, व्योम __iomem *ras_base) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_SPEAR1340
व्योम __init spear1340_clk_init(व्योम __iomem *misc_base);
#अन्यथा
अटल अंतरभूत व्योम spear1340_clk_init(व्योम __iomem *misc_base) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
