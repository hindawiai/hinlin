<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Copyright(c) 2016-20 Intel Corporation. */

#समावेश <मानकघोष.स>
#समावेश "defines.h"

अटल व्योम *स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < n; i++)
		((अक्षर *)dest)[i] = ((अक्षर *)src)[i];

	वापस dest;
पूर्ण

व्योम encl_body(व्योम *rdi, व्योम *rsi)
अणु
	स_नकल(rsi, rdi, 8);
पूर्ण
