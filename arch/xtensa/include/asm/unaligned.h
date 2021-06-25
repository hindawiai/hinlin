<शैली गुरु>
/*
 * Xtensa करोesn't handle unaligned accesses efficiently.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */
#अगर_अघोषित _ASM_XTENSA_UNALIGNED_H
#घोषणा _ASM_XTENSA_UNALIGNED_H

#समावेश <यंत्र/byteorder.h>

#अगर_घोषित __LITTLE_ENDIAN
# include <linux/unaligned/le_काष्ठा.h>
# include <linux/unaligned/be_byteshअगरt.h>
# include <linux/unaligned/generic.h>
# define get_unaligned	__get_unaligned_le
# define put_unaligned	__put_unaligned_le
#अन्यथा
# include <linux/unaligned/be_काष्ठा.h>
# include <linux/unaligned/le_byteshअगरt.h>
# include <linux/unaligned/generic.h>
# define get_unaligned	__get_unaligned_be
# define put_unaligned	__put_unaligned_be
#पूर्ण_अगर

#पूर्ण_अगर	/* _ASM_XTENSA_UNALIGNED_H */
