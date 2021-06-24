<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_UNALIGNED_H
#घोषणा __ASM_GENERIC_UNALIGNED_H

/*
 * This is the most generic implementation of unaligned accesses
 * and should work almost anywhere.
 */
#समावेश <यंत्र/byteorder.h>

/* Set by the arch अगर it can handle unaligned accesses in hardware. */
#अगर_घोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
# include <linux/unaligned/access_ok.h>
#पूर्ण_अगर

#अगर defined(__LITTLE_ENDIAN)
# अगरndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
#  include <linux/unaligned/le_काष्ठा.h>
#  include <linux/unaligned/be_byteshअगरt.h>
# endअगर
# include <linux/unaligned/generic.h>
# define get_unaligned	__get_unaligned_le
# define put_unaligned	__put_unaligned_le
#या_अगर defined(__BIG_ENDIAN)
# अगरndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
#  include <linux/unaligned/be_काष्ठा.h>
#  include <linux/unaligned/le_byteshअगरt.h>
# endअगर
# include <linux/unaligned/generic.h>
# define get_unaligned	__get_unaligned_be
# define put_unaligned	__put_unaligned_be
#अन्यथा
# error need to define endianess
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_UNALIGNED_H */
