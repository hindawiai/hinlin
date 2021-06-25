<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#समावेश "helper.h"

माप_प्रकार keyia_sign(माप_प्रकार ptr)
अणु
	यंत्र अस्थिर("paciza %0" : "+r" (ptr));
	वापस ptr;
पूर्ण

माप_प्रकार keyib_sign(माप_प्रकार ptr)
अणु
	यंत्र अस्थिर("pacizb %0" : "+r" (ptr));
	वापस ptr;
पूर्ण

माप_प्रकार keyda_sign(माप_प्रकार ptr)
अणु
	यंत्र अस्थिर("pacdza %0" : "+r" (ptr));
	वापस ptr;
पूर्ण

माप_प्रकार keydb_sign(माप_प्रकार ptr)
अणु
	यंत्र अस्थिर("pacdzb %0" : "+r" (ptr));
	वापस ptr;
पूर्ण

माप_प्रकार keyg_sign(माप_प्रकार ptr)
अणु
	/* output is encoded in the upper 32 bits */
	माप_प्रकार dest = 0;
	माप_प्रकार modअगरier = 0;

	यंत्र अस्थिर("pacga %0, %1, %2" : "=r" (dest) : "r" (ptr), "r" (modअगरier));

	वापस dest;
पूर्ण
