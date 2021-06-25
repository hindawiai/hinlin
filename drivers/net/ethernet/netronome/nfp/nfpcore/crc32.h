<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2017 Netronome Systems, Inc. */

#अगर_अघोषित NFP_CRC32_H
#घोषणा NFP_CRC32_H

#समावेश <linux/kernel.h>
#समावेश <linux/crc32.h>

/**
 * crc32_posix_end() - Finalize POSIX CRC32 working state
 * @crc:	Current CRC32 working state
 * @total_len:	Total length of data that was CRC32'd
 *
 * Return: Final POSIX CRC32 value
 */
अटल अंतरभूत u32 crc32_posix_end(u32 crc, माप_प्रकार total_len)
अणु
	/* Extend with the length of the string. */
	जबतक (total_len != 0) अणु
		u8 c = total_len & 0xff;

		crc = crc32_be(crc, &c, 1);
		total_len >>= 8;
	पूर्ण

	वापस ~crc;
पूर्ण

अटल अंतरभूत u32 crc32_posix(स्थिर व्योम *buff, माप_प्रकार len)
अणु
	वापस crc32_posix_end(crc32_be(0, buff, len), len);
पूर्ण

#पूर्ण_अगर /* NFP_CRC32_H */
