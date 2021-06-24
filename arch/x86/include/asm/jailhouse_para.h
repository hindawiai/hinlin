<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Jailhouse paravirt detection
 *
 * Copyright (c) Siemens AG, 2015-2017
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 */

#अगर_अघोषित _ASM_X86_JAILHOUSE_PARA_H
#घोषणा _ASM_X86_JAILHOUSE_PARA_H

#समावेश <linux/types.h>

#अगर_घोषित CONFIG_JAILHOUSE_GUEST
bool jailhouse_paravirt(व्योम);
#अन्यथा
अटल अंतरभूत bool jailhouse_paravirt(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_JAILHOUSE_PARA_H */
