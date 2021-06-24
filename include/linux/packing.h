<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause
 * Copyright (c) 2016-2018, NXP Semiconductors
 * Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 */
#अगर_अघोषित _LINUX_PACKING_H
#घोषणा _LINUX_PACKING_H

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>

#घोषणा QUIRK_MSB_ON_THE_RIGHT	BIT(0)
#घोषणा QUIRK_LITTLE_ENDIAN	BIT(1)
#घोषणा QUIRK_LSW32_IS_FIRST	BIT(2)

क्रमागत packing_op अणु
	PACK,
	UNPACK,
पूर्ण;

/**
 * packing - Convert numbers (currently u64) between a packed and an unpacked
 *	     क्रमmat. Unpacked means laid out in memory in the CPU's native
 *	     understanding of पूर्णांकegers, जबतक packed means anything अन्यथा that
 *	     requires translation.
 *
 * @pbuf: Poपूर्णांकer to a buffer holding the packed value.
 * @uval: Poपूर्णांकer to an u64 holding the unpacked value.
 * @startbit: The index (in logical notation, compensated क्रम quirks) where
 *	      the packed value starts within pbuf. Must be larger than, or
 *	      equal to, endbit.
 * @endbit: The index (in logical notation, compensated क्रम quirks) where
 *	    the packed value ends within pbuf. Must be smaller than, or equal
 *	    to, startbit.
 * @op: If PACK, then uval will be treated as स्थिर poपूर्णांकer and copied (packed)
 *	पूर्णांकo pbuf, between startbit and endbit.
 *	If UNPACK, then pbuf will be treated as स्थिर poपूर्णांकer and the logical
 *	value between startbit and endbit will be copied (unpacked) to uval.
 * @quirks: A bit mask of QUIRK_LITTLE_ENDIAN, QUIRK_LSW32_IS_FIRST and
 *	    QUIRK_MSB_ON_THE_RIGHT.
 *
 * Return: 0 on success, EINVAL or दुस्फल अगर called incorrectly. Assuming
 *	   correct usage, वापस code may be discarded.
 *	   If op is PACK, pbuf is modअगरied.
 *	   If op is UNPACK, uval is modअगरied.
 */
पूर्णांक packing(व्योम *pbuf, u64 *uval, पूर्णांक startbit, पूर्णांक endbit, माप_प्रकार pbuflen,
	    क्रमागत packing_op op, u8 quirks);

#पूर्ण_अगर
