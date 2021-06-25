<शैली गुरु>
/*
 * arch/xtensa/kernel/platक्रमm.c
 *
 * Default platक्रमm functions.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 Tensilica Inc.
 *
 * Chris Zankel <chris@zankel.net>
 */

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/platक्रमm.h>
#समावेश <यंत्र/समयx.h>

#घोषणा _F(r,f,a,b)							\
	r __platक्रमm_##f a b;                                   	\
	r platक्रमm_##f a __attribute__((weak, alias("__platform_"#f)))

/*
 * Default functions that are used अगर no platक्रमm specअगरic function is defined.
 * (Please, refer to include/यंत्र-xtensa/platक्रमm.h क्रम more inक्रमmation)
 */

_F(व्योम, init, (bp_tag_t *first), अणु पूर्ण);
_F(व्योम, setup, (अक्षर** cmd), अणु पूर्ण);
_F(व्योम, restart, (व्योम), अणु जबतक(1); पूर्ण);
_F(व्योम, halt, (व्योम), अणु जबतक(1); पूर्ण);
_F(व्योम, घातer_off, (व्योम), अणु जबतक(1); पूर्ण);
_F(व्योम, idle, (व्योम), अणु __यंत्र__ __अस्थिर__ ("waiti 0" ::: "memory"); पूर्ण);
_F(व्योम, heartbeat, (व्योम), अणु पूर्ण);

#अगर_घोषित CONFIG_XTENSA_CALIBRATE_CCOUNT
_F(व्योम, calibrate_ccount, (व्योम),
अणु
	pr_err("ERROR: Cannot calibrate cpu frequency! Assuming 10MHz.\n");
	ccount_freq = 10 * 1000000UL;
पूर्ण);
#पूर्ण_अगर
