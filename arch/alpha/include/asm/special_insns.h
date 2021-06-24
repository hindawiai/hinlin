<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_SPECIAL_INSNS_H
#घोषणा __ALPHA_SPECIAL_INSNS_H

क्रमागत implver_क्रमागत अणु
	IMPLVER_EV4,
	IMPLVER_EV5,
	IMPLVER_EV6
पूर्ण;

#अगर_घोषित CONFIG_ALPHA_GENERIC
#घोषणा implver()				\
(अणु अचिन्हित दीर्घ __implver;			\
   __यंत्र__ ("implver %0" : "=r"(__implver));	\
   (क्रमागत implver_क्रमागत) __implver; पूर्ण)
#अन्यथा
/* Try to eliminate some dead code.  */
#अगर_घोषित CONFIG_ALPHA_EV4
#घोषणा implver() IMPLVER_EV4
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALPHA_EV5
#घोषणा implver() IMPLVER_EV5
#पूर्ण_अगर
#अगर defined(CONFIG_ALPHA_EV6)
#घोषणा implver() IMPLVER_EV6
#पूर्ण_अगर
#पूर्ण_अगर

क्रमागत amask_क्रमागत अणु
	AMASK_BWX = (1UL << 0),
	AMASK_FIX = (1UL << 1),
	AMASK_CIX = (1UL << 2),
	AMASK_MAX = (1UL << 8),
	AMASK_PRECISE_TRAP = (1UL << 9),
पूर्ण;

#घोषणा amask(mask)						\
(अणु अचिन्हित दीर्घ __amask, __input = (mask);			\
   __यंत्र__ ("amask %1,%0" : "=r"(__amask) : "rI"(__input));	\
   __amask; पूर्ण)

#पूर्ण_अगर /* __ALPHA_SPECIAL_INSNS_H */
