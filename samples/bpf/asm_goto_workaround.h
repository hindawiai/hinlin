<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 Facebook */
#अगर_अघोषित __ASM_GOTO_WORKAROUND_H
#घोषणा __ASM_GOTO_WORKAROUND_H

/*
 * This will bring in यंत्र_अस्थिर_जाओ and यंत्र_अंतरभूत macro definitions
 * अगर enabled by compiler and config options.
 */
#समावेश <linux/types.h>

#अगर_घोषित यंत्र_अस्थिर_जाओ
#अघोषित यंत्र_अस्थिर_जाओ
#घोषणा यंत्र_अस्थिर_जाओ(x...) यंत्र अस्थिर("invalid use of asm_volatile_goto")
#पूर्ण_अगर

/*
 * यंत्र_अंतरभूत is defined as यंत्र __अंतरभूत in "include/linux/compiler_types.h"
 * अगर supported by the kernel's CC (i.e CONFIG_CC_HAS_ASM_INLINE) which is not
 * supported by CLANG.
 */
#अगर_घोषित यंत्र_अंतरभूत
#अघोषित यंत्र_अंतरभूत
#घोषणा यंत्र_अंतरभूत यंत्र
#पूर्ण_अगर

#घोषणा अस्थिर(x...) अस्थिर("")
#पूर्ण_अगर
