<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2010, 2014 The Linux Foundation. All rights reserved.
 */

#समावेश <यंत्र/barrier.h>

अटल अंतरभूत u32 __dcc_माला_लोtatus(व्योम)
अणु
	u32 __ret;
	यंत्र अस्थिर("mrc p14, 0, %0, c0, c1, 0	@ read comms ctrl reg"
		: "=r" (__ret) : : "cc");

	वापस __ret;
पूर्ण

अटल अंतरभूत अक्षर __dcc_अक्षर_लो(व्योम)
अणु
	अक्षर __c;

	यंत्र अस्थिर("mrc p14, 0, %0, c0, c5, 0	@ read comms data reg"
		: "=r" (__c));
	isb();

	वापस __c;
पूर्ण

अटल अंतरभूत व्योम __dcc_अक्षर_दो(अक्षर c)
अणु
	यंत्र अस्थिर("mcr p14, 0, %0, c0, c5, 0	@ write a char"
		: /* no output रेजिस्टर */
		: "r" (c));
	isb();
पूर्ण
