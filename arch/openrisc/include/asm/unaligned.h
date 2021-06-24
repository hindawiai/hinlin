<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_UNALIGNED_H
#घोषणा __ASM_OPENRISC_UNALIGNED_H

/*
 * This is copied from the generic implementation and the C-काष्ठा
 * variant replaced with the स_हटाओ variant.  The GCC compiler
 * क्रम the OR32 arch optimizes too aggressively क्रम the C-काष्ठा
 * variant to work, so use the स_हटाओ variant instead.
 *
 * It may be worth considering implementing the unaligned access
 * exception handler and allowing unaligned accesses (access_ok.h)...
 * not sure अगर it would be much of a perक्रमmance win without further
 * investigation.
 */
#समावेश <यंत्र/byteorder.h>

#अगर defined(__LITTLE_ENDIAN)
# include <linux/unaligned/le_स_हटाओ.h>
# include <linux/unaligned/be_byteshअगरt.h>
# include <linux/unaligned/generic.h>
# define get_unaligned	__get_unaligned_le
# define put_unaligned	__put_unaligned_le
#या_अगर defined(__BIG_ENDIAN)
# include <linux/unaligned/be_स_हटाओ.h>
# include <linux/unaligned/le_byteshअगरt.h>
# include <linux/unaligned/generic.h>
# define get_unaligned	__get_unaligned_be
# define put_unaligned	__put_unaligned_be
#अन्यथा
# error need to define endianess
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_OPENRISC_UNALIGNED_H */
