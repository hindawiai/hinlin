<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019  Arm Limited
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */

#अगर_अघोषित BTITEST_H
#घोषणा BTITEST_H

/* Trampolines क्रम calling the test stubs: */
व्योम call_using_br_x0(व्योम (*)(व्योम));
व्योम call_using_br_x16(व्योम (*)(व्योम));
व्योम call_using_blr(व्योम (*)(व्योम));

/* Test stubs: */
व्योम nohपूर्णांक_func(व्योम);
व्योम bti_none_func(व्योम);
व्योम bti_c_func(व्योम);
व्योम bti_j_func(व्योम);
व्योम bti_jc_func(व्योम);
व्योम paciasp_func(व्योम);

#पूर्ण_अगर /* !BTITEST_H */
