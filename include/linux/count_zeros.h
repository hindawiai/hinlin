<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Count leading and trailing zeros functions
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_BITOPS_COUNT_ZEROS_H_
#घोषणा _LINUX_BITOPS_COUNT_ZEROS_H_

#समावेश <यंत्र/bitops.h>

/**
 * count_leading_zeros - Count the number of zeros from the MSB back
 * @x: The value
 *
 * Count the number of leading zeros from the MSB going towards the LSB in @x.
 *
 * If the MSB of @x is set, the result is 0.
 * If only the LSB of @x is set, then the result is BITS_PER_LONG-1.
 * If @x is 0 then the result is COUNT_LEADING_ZEROS_0.
 */
अटल अंतरभूत पूर्णांक count_leading_zeros(अचिन्हित दीर्घ x)
अणु
	अगर (माप(x) == 4)
		वापस BITS_PER_LONG - fls(x);
	अन्यथा
		वापस BITS_PER_LONG - fls64(x);
पूर्ण

#घोषणा COUNT_LEADING_ZEROS_0 BITS_PER_LONG

/**
 * count_trailing_zeros - Count the number of zeros from the LSB क्रमwards
 * @x: The value
 *
 * Count the number of trailing zeros from the LSB going towards the MSB in @x.
 *
 * If the LSB of @x is set, the result is 0.
 * If only the MSB of @x is set, then the result is BITS_PER_LONG-1.
 * If @x is 0 then the result is COUNT_TRAILING_ZEROS_0.
 */
अटल अंतरभूत पूर्णांक count_trailing_zeros(अचिन्हित दीर्घ x)
अणु
#घोषणा COUNT_TRAILING_ZEROS_0 (-1)

	अगर (माप(x) == 4)
		वापस ffs(x);
	अन्यथा
		वापस (x != 0) ? __ffs(x) : COUNT_TRAILING_ZEROS_0;
पूर्ण

#पूर्ण_अगर /* _LINUX_BITOPS_COUNT_ZEROS_H_ */
