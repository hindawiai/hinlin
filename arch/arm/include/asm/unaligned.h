<शैली गुरु>
#अगर_अघोषित __ASM_ARM_UNALIGNED_H
#घोषणा __ASM_ARM_UNALIGNED_H

/*
 * We generally want to set CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS on ARMv6+,
 * but we करोn't want to use linux/unaligned/access_ok.h since that can lead
 * to traps on unaligned sपंचांग/ldm or strd/ldrd.
 */
#समावेश <यंत्र/byteorder.h>

#अगर defined(__LITTLE_ENDIAN)
# include <linux/unaligned/le_काष्ठा.h>
# include <linux/unaligned/be_byteshअगरt.h>
# include <linux/unaligned/generic.h>
# define get_unaligned	__get_unaligned_le
# define put_unaligned	__put_unaligned_le
#या_अगर defined(__BIG_ENDIAN)
# include <linux/unaligned/be_काष्ठा.h>
# include <linux/unaligned/le_byteshअगरt.h>
# include <linux/unaligned/generic.h>
# define get_unaligned	__get_unaligned_be
# define put_unaligned	__put_unaligned_be
#अन्यथा
# error need to define endianess
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ARM_UNALIGNED_H */
