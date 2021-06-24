<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.0+ OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#अगर_अघोषित __TOOLS_LIBC_COMPAT_H
#घोषणा __TOOLS_LIBC_COMPAT_H

#समावेश <मानककोष.स>
#समावेश <linux/overflow.h>

#अगर_घोषित COMPAT_NEED_REALLOCARRAY
अटल अंतरभूत व्योम *पुनः_स्मृतिarray(व्योम *ptr, माप_प्रकार nmemb, माप_प्रकार size)
अणु
	माप_प्रकार bytes;

	अगर (unlikely(check_mul_overflow(nmemb, size, &bytes)))
		वापस शून्य;
	वापस पुनः_स्मृति(ptr, bytes);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
