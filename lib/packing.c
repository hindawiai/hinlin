<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2016-2018, NXP Semiconductors
 * Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 */
#समावेश <linux/packing.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

अटल पूर्णांक get_le_offset(पूर्णांक offset)
अणु
	पूर्णांक बंदst_multiple_of_4;

	बंदst_multiple_of_4 = (offset / 4) * 4;
	offset -= बंदst_multiple_of_4;
	वापस बंदst_multiple_of_4 + (3 - offset);
पूर्ण

अटल पूर्णांक get_reverse_lsw32_offset(पूर्णांक offset, माप_प्रकार len)
अणु
	पूर्णांक बंदst_multiple_of_4;
	पूर्णांक word_index;

	word_index = offset / 4;
	बंदst_multiple_of_4 = word_index * 4;
	offset -= बंदst_multiple_of_4;
	word_index = (len / 4) - word_index - 1;
	वापस word_index * 4 + offset;
पूर्ण

अटल u64 bit_reverse(u64 val, अचिन्हित पूर्णांक width)
अणु
	u64 new_val = 0;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < width; i++) अणु
		bit = (val & (1 << i)) != 0;
		new_val |= (bit << (width - i - 1));
	पूर्ण
	वापस new_val;
पूर्ण

अटल व्योम adjust_क्रम_msb_right_quirk(u64 *to_ग_लिखो, पूर्णांक *box_start_bit,
				       पूर्णांक *box_end_bit, u8 *box_mask)
अणु
	पूर्णांक box_bit_width = *box_start_bit - *box_end_bit + 1;
	पूर्णांक new_box_start_bit, new_box_end_bit;

	*to_ग_लिखो >>= *box_end_bit;
	*to_ग_लिखो = bit_reverse(*to_ग_लिखो, box_bit_width);
	*to_ग_लिखो <<= *box_end_bit;

	new_box_end_bit   = box_bit_width - *box_start_bit - 1;
	new_box_start_bit = box_bit_width - *box_end_bit - 1;
	*box_mask = GENMASK_ULL(new_box_start_bit, new_box_end_bit);
	*box_start_bit = new_box_start_bit;
	*box_end_bit   = new_box_end_bit;
पूर्ण

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
 * @pbuflen: The length in bytes of the packed buffer poपूर्णांकed to by @pbuf.
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
	    क्रमागत packing_op op, u8 quirks)
अणु
	/* Number of bits क्रम storing "uval"
	 * also width of the field to access in the pbuf
	 */
	u64 value_width;
	/* Logical byte indices corresponding to the
	 * start and end of the field.
	 */
	पूर्णांक plogical_first_u8, plogical_last_u8, box;

	/* startbit is expected to be larger than endbit */
	अगर (startbit < endbit)
		/* Invalid function call */
		वापस -EINVAL;

	value_width = startbit - endbit + 1;
	अगर (value_width > 64)
		वापस -दुस्फल;

	/* Check अगर "uval" fits in "value_width" bits.
	 * If value_width is 64, the check will fail, but any
	 * 64-bit uval will surely fit.
	 */
	अगर (op == PACK && value_width < 64 && (*uval >= (1ull << value_width)))
		/* Cannot store "uval" inside "value_width" bits.
		 * Truncating "uval" is most certainly not desirable,
		 * so simply erroring out is appropriate.
		 */
		वापस -दुस्फल;

	/* Initialize parameter */
	अगर (op == UNPACK)
		*uval = 0;

	/* Iterate through an idealistic view of the pbuf as an u64 with
	 * no quirks, u8 by u8 (aligned at u8 boundaries), from high to low
	 * logical bit signअगरicance. "box" denotes the current logical u8.
	 */
	plogical_first_u8 = startbit / 8;
	plogical_last_u8  = endbit / 8;

	क्रम (box = plogical_first_u8; box >= plogical_last_u8; box--) अणु
		/* Bit indices पूर्णांकo the currently accessed 8-bit box */
		पूर्णांक box_start_bit, box_end_bit, box_addr;
		u8  box_mask;
		/* Corresponding bits from the unpacked u64 parameter */
		पूर्णांक proj_start_bit, proj_end_bit;
		u64 proj_mask;

		/* This u8 may need to be accessed in its entirety
		 * (from bit 7 to bit 0), or not, depending on the
		 * input arguments startbit and endbit.
		 */
		अगर (box == plogical_first_u8)
			box_start_bit = startbit % 8;
		अन्यथा
			box_start_bit = 7;
		अगर (box == plogical_last_u8)
			box_end_bit = endbit % 8;
		अन्यथा
			box_end_bit = 0;

		/* We have determined the box bit start and end.
		 * Now we calculate where this (masked) u8 box would fit
		 * in the unpacked (CPU-पढ़ोable) u64 - the u8 box's
		 * projection onto the unpacked u64. Though the
		 * box is u8, the projection is u64 because it may fall
		 * anywhere within the unpacked u64.
		 */
		proj_start_bit = ((box * 8) + box_start_bit) - endbit;
		proj_end_bit   = ((box * 8) + box_end_bit) - endbit;
		proj_mask = GENMASK_ULL(proj_start_bit, proj_end_bit);
		box_mask  = GENMASK_ULL(box_start_bit, box_end_bit);

		/* Determine the offset of the u8 box inside the pbuf,
		 * adjusted क्रम quirks. The adjusted box_addr will be used क्रम
		 * effective addressing inside the pbuf (so it's not
		 * logical any दीर्घer).
		 */
		box_addr = pbuflen - box - 1;
		अगर (quirks & QUIRK_LITTLE_ENDIAN)
			box_addr = get_le_offset(box_addr);
		अगर (quirks & QUIRK_LSW32_IS_FIRST)
			box_addr = get_reverse_lsw32_offset(box_addr,
							    pbuflen);

		अगर (op == UNPACK) अणु
			u64 pval;

			/* Read from pbuf, ग_लिखो to uval */
			pval = ((u8 *)pbuf)[box_addr] & box_mask;
			अगर (quirks & QUIRK_MSB_ON_THE_RIGHT)
				adjust_क्रम_msb_right_quirk(&pval,
							   &box_start_bit,
							   &box_end_bit,
							   &box_mask);

			pval >>= box_end_bit;
			pval <<= proj_end_bit;
			*uval &= ~proj_mask;
			*uval |= pval;
		पूर्ण अन्यथा अणु
			u64 pval;

			/* Write to pbuf, पढ़ो from uval */
			pval = (*uval) & proj_mask;
			pval >>= proj_end_bit;
			अगर (quirks & QUIRK_MSB_ON_THE_RIGHT)
				adjust_क्रम_msb_right_quirk(&pval,
							   &box_start_bit,
							   &box_end_bit,
							   &box_mask);

			pval <<= box_end_bit;
			((u8 *)pbuf)[box_addr] &= ~box_mask;
			((u8 *)pbuf)[box_addr] |= pval;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(packing);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Generic bitfield packing and unpacking");
