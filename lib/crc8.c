<शैली गुरु>
/*
 * Copyright (c) 2011 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/crc8.h>
#समावेश <linux/prपूर्णांकk.h>

/**
 * crc8_populate_msb - fill crc table क्रम given polynomial in reverse bit order.
 *
 * @table:	table to be filled.
 * @polynomial:	polynomial क्रम which table is to be filled.
 */
व्योम crc8_populate_msb(u8 table[CRC8_TABLE_SIZE], u8 polynomial)
अणु
	पूर्णांक i, j;
	स्थिर u8 msbit = 0x80;
	u8 t = msbit;

	table[0] = 0;

	क्रम (i = 1; i < CRC8_TABLE_SIZE; i *= 2) अणु
		t = (t << 1) ^ (t & msbit ? polynomial : 0);
		क्रम (j = 0; j < i; j++)
			table[i+j] = table[j] ^ t;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(crc8_populate_msb);

/**
 * crc8_populate_lsb - fill crc table क्रम given polynomial in regular bit order.
 *
 * @table:	table to be filled.
 * @polynomial:	polynomial क्रम which table is to be filled.
 */
व्योम crc8_populate_lsb(u8 table[CRC8_TABLE_SIZE], u8 polynomial)
अणु
	पूर्णांक i, j;
	u8 t = 1;

	table[0] = 0;

	क्रम (i = (CRC8_TABLE_SIZE >> 1); i; i >>= 1) अणु
		t = (t >> 1) ^ (t & 1 ? polynomial : 0);
		क्रम (j = 0; j < CRC8_TABLE_SIZE; j += 2*i)
			table[i+j] = table[j] ^ t;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(crc8_populate_lsb);

/**
 * crc8 - calculate a crc8 over the given input data.
 *
 * @table: crc table used क्रम calculation.
 * @pdata: poपूर्णांकer to data buffer.
 * @nbytes: number of bytes in data buffer.
 * @crc: previous वापसed crc8 value.
 */
u8 crc8(स्थिर u8 table[CRC8_TABLE_SIZE], स्थिर u8 *pdata, माप_प्रकार nbytes, u8 crc)
अणु
	/* loop over the buffer data */
	जबतक (nbytes-- > 0)
		crc = table[(crc ^ *pdata++) & 0xff];

	वापस crc;
पूर्ण
EXPORT_SYMBOL(crc8);

MODULE_DESCRIPTION("CRC8 (by Williams, Ross N.) function");
MODULE_AUTHOR("Broadcom Corporation");
MODULE_LICENSE("Dual BSD/GPL");
