<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2000 Deep Blue Solutions Ltd
 * Copyright 2004 ARM Limited
 * Copyright 2008 Cavium Networks
 */

#अगर_अघोषित __CNS3XXX_CORE_H
#घोषणा __CNS3XXX_CORE_H

#समावेश <linux/reboot.h>

बाह्य व्योम cns3xxx_समयr_init(व्योम);

#अगर_घोषित CONFIG_CACHE_L2X0
व्योम __init cns3xxx_l2x0_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम cns3xxx_l2x0_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_CACHE_L2X0 */

#अगर_घोषित CONFIG_PCI
बाह्य व्योम __init cns3xxx_pcie_init_late(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __init cns3xxx_pcie_init_late(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम __init cns3xxx_map_io(व्योम);
व्योम __init cns3xxx_init_irq(व्योम);
व्योम cns3xxx_घातer_off(व्योम);
व्योम cns3xxx_restart(क्रमागत reboot_mode, स्थिर अक्षर *);

#पूर्ण_अगर /* __CNS3XXX_CORE_H */
