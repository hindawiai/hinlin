<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCD_H
#घोषणा _BCD_H

#समावेश <linux/compiler.h>

#घोषणा bcd2bin(x)					\
		(__builtin_स्थिरant_p((u8 )(x)) ?	\
		स्थिर_bcd2bin(x) :			\
		_bcd2bin(x))

#घोषणा bin2bcd(x)					\
		(__builtin_स्थिरant_p((u8 )(x)) ?	\
		स्थिर_bin2bcd(x) :			\
		_bin2bcd(x))

#घोषणा स्थिर_bcd2bin(x)	(((x) & 0x0f) + ((x) >> 4) * 10)
#घोषणा स्थिर_bin2bcd(x)	((((x) / 10) << 4) + (x) % 10)

अचिन्हित _bcd2bin(अचिन्हित अक्षर val) __attribute_स्थिर__;
अचिन्हित अक्षर _bin2bcd(अचिन्हित val) __attribute_स्थिर__;

#पूर्ण_अगर /* _BCD_H */
