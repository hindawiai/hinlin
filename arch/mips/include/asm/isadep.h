<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Various ISA level dependent स्थिरants.
 * Most of the following स्थिरants reflect the dअगरferent layout
 * of Coprocessor 0 रेजिस्टरs.
 *
 * Copyright (c) 1998 Harald Koerfgen
 */

#अगर_अघोषित __ASM_ISADEP_H
#घोषणा __ASM_ISADEP_H

#अगर defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_TX39XX)
/*
 * R2000 or R3000
 */

/*
 * kernel or user mode? (CP0_STATUS)
 */
#घोषणा KU_MASK 0x08
#घोषणा KU_USER 0x08
#घोषणा KU_KERN 0x00

#अन्यथा
/*
 * kernel or user mode?
 */
#घोषणा KU_MASK 0x18
#घोषणा KU_USER 0x10
#घोषणा KU_KERN 0x00

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ISADEP_H */
