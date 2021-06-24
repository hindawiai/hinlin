<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __PRINT_SUPPORT_H_INCLUDED__
#घोषणा __PRINT_SUPPORT_H_INCLUDED__

#समावेश <मानकतर्क.स>

बाह्य पूर्णांक (*sh_css_म_लिखो)(स्थिर अक्षर *fmt, बहु_सूची args);
/* depends on host supplied prपूर्णांक function in ia_css_init() */
अटल अंतरभूत  __म_लिखो(1, 2) व्योम ia_css_prपूर्णांक(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	अगर (sh_css_म_लिखो) अणु
		बहु_शुरू(ap, fmt);
		sh_css_म_लिखो(fmt, ap);
		बहु_पूर्ण(ap);
	पूर्ण
पूर्ण

/* Start adding support क्रम bxt tracing functions क्रम poc. From
 * bxt_sandbox/support/prपूर्णांक_support.h. */
/* TODO: support these macros in userspace. */
#घोषणा PWARN(क्रमmat, ...) ia_css_prपूर्णांक("warning: ", ##__VA_ARGS__)
#घोषणा PRINT(क्रमmat, ...) ia_css_prपूर्णांक(क्रमmat, ##__VA_ARGS__)
#घोषणा PERROR(क्रमmat, ...) ia_css_prपूर्णांक("error: " क्रमmat, ##__VA_ARGS__)
#घोषणा PDEBUG(क्रमmat, ...) ia_css_prपूर्णांक("debug: " क्रमmat, ##__VA_ARGS__)

#पूर्ण_अगर /* __PRINT_SUPPORT_H_INCLUDED__ */
