<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rational fractions
 *
 * Copyright (C) 2009 emlix GmbH, Oskar Schirmer <oskar@scara.com>
 *
 * helper functions when coping with rational numbers,
 * e.g. when calculating optimum numerator/denominator pairs क्रम
 * pll configuration taking पूर्णांकo account restricted रेजिस्टर size
 */

#अगर_अघोषित _LINUX_RATIONAL_H
#घोषणा _LINUX_RATIONAL_H

व्योम rational_best_approximation(
	अचिन्हित दीर्घ given_numerator, अचिन्हित दीर्घ given_denominator,
	अचिन्हित दीर्घ max_numerator, अचिन्हित दीर्घ max_denominator,
	अचिन्हित दीर्घ *best_numerator, अचिन्हित दीर्घ *best_denominator);

#पूर्ण_अगर /* _LINUX_RATIONAL_H */
