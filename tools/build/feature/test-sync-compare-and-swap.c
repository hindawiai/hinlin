<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानक_निवेशt.h>

अस्थिर uपूर्णांक64_t x;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	uपूर्णांक64_t old, new = argc;

	(व्योम)argv;
	करो अणु
		old = __sync_val_compare_and_swap(&x, 0, 0);
	पूर्ण जबतक (!__sync_bool_compare_and_swap(&x, old, new));
	वापस old == new;
पूर्ण
