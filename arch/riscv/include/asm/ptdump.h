<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 SiFive
 */

#अगर_अघोषित _ASM_RISCV_PTDUMP_H
#घोषणा _ASM_RISCV_PTDUMP_H

व्योम ptdump_check_wx(व्योम);

#अगर_घोषित CONFIG_DEBUG_WX
अटल अंतरभूत व्योम debug_checkwx(व्योम)
अणु
	ptdump_check_wx();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम debug_checkwx(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_PTDUMP_H */
