<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * altera-comp.c
 *
 * altera FPGA driver
 *
 * Copyright (C) Altera Corporation 1998-2001
 * Copyright (C) 2010 NetUP Inc.
 * Copyright (C) 2010 Igor M. Liplianin <liplianin@netup.ru>
 */

#समावेश <linux/kernel.h>
#समावेश "altera-exprt.h"

#घोषणा	SHORT_BITS		16
#घोषणा	अक्षर_बिटS		8
#घोषणा	DATA_BLOB_LENGTH	3
#घोषणा	MATCH_DATA_LENGTH	8192
#घोषणा ALTERA_REQUEST_SIZE	1024
#घोषणा ALTERA_BUFFER_SIZE	(MATCH_DATA_LENGTH + ALTERA_REQUEST_SIZE)

अटल u32 altera_bits_req(u32 n)
अणु
	u32 result = SHORT_BITS;

	अगर (n == 0)
		result = 1;
	अन्यथा अणु
		/* Look क्रम the highest non-zero bit position */
		जबतक ((n & (1 << (SHORT_BITS - 1))) == 0) अणु
			n <<= 1;
			--result;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल u32 altera_पढ़ो_packed(u8 *buffer, u32 bits, u32 *bits_avail,
							u32 *in_index)
अणु
	u32 result = 0;
	u32 shअगरt = 0;
	u32 databyte = 0;

	जबतक (bits > 0) अणु
		databyte = buffer[*in_index];
		result |= (((databyte >> (अक्षर_बिटS - *bits_avail))
			& (0xff >> (अक्षर_बिटS - *bits_avail))) << shअगरt);

		अगर (bits <= *bits_avail) अणु
			result &= (0xffff >> (SHORT_BITS - (bits + shअगरt)));
			*bits_avail -= bits;
			bits = 0;
		पूर्ण अन्यथा अणु
			++(*in_index);
			shअगरt += *bits_avail;
			bits -= *bits_avail;
			*bits_avail = अक्षर_बिटS;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

u32 altera_shrink(u8 *in, u32 in_length, u8 *out, u32 out_length, s32 version)
अणु
	u32 i, j, data_length = 0L;
	u32 offset, length;
	u32 match_data_length = MATCH_DATA_LENGTH;
	u32 bits_avail = अक्षर_बिटS;
	u32 in_index = 0L;

	अगर (version > 0)
		--match_data_length;

	क्रम (i = 0; i < out_length; ++i)
		out[i] = 0;

	/* Read number of bytes in data. */
	क्रम (i = 0; i < माप(in_length); ++i) अणु
		data_length = data_length | (
			altera_पढ़ो_packed(in,
					अक्षर_बिटS,
					&bits_avail,
					&in_index) << (i * अक्षर_बिटS));
	पूर्ण

	अगर (data_length > out_length) अणु
		data_length = 0L;
		वापस data_length;
	पूर्ण

	i = 0;
	जबतक (i < data_length) अणु
		/* A 0 bit indicates literal data. */
		अगर (altera_पढ़ो_packed(in, 1, &bits_avail,
						&in_index) == 0) अणु
			क्रम (j = 0; j < DATA_BLOB_LENGTH; ++j) अणु
				अगर (i < data_length) अणु
					out[i] = (u8)altera_पढ़ो_packed(in,
							अक्षर_बिटS,
							&bits_avail,
							&in_index);
					i++;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* A 1 bit indicates offset/length to follow. */
			offset = altera_पढ़ो_packed(in, altera_bits_req((s16)
					(i > match_data_length ?
						match_data_length : i)),
					&bits_avail,
					&in_index);
			length = altera_पढ़ो_packed(in, अक्षर_बिटS,
					&bits_avail,
					&in_index);
			क्रम (j = 0; j < length; ++j) अणु
				अगर (i < data_length) अणु
					out[i] = out[i - offset];
					i++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस data_length;
पूर्ण
