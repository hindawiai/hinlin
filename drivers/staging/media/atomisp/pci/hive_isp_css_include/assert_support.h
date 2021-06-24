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

#अगर_अघोषित __ASSERT_SUPPORT_H_INCLUDED__
#घोषणा __ASSERT_SUPPORT_H_INCLUDED__

/**
 * The following macro can help to test the size of a काष्ठा at compile
 * समय rather than at run-समय. It करोes not work क्रम all compilers; see
 * below.
 *
 * Depending on the value of 'condition', the following macro is expanded to:
 * - condition==true:
 *     an expression containing an array declaration with negative size,
 *     usually resulting in a compilation error
 * - condition==false:
 *     (व्योम) 1; // C statement with no effect
 *
 * example:
 *  COMPILATION_ERROR_IF( माप(काष्ठा host_sp_queues) != SIZE_OF_HOST_SP_QUEUES_STRUCT);
 *
 * verअगरy that the macro indeed triggers a compilation error with your compiler:
 *  COMPILATION_ERROR_IF( माप(काष्ठा host_sp_queues) != (माप(काष्ठा host_sp_queues)+1) );
 *
 * Not all compilers will trigger an error with this macro; use a search engine to search क्रम
 * BUILD_BUG_ON to find other methods.
 */
#घोषणा COMPILATION_ERROR_IF(condition) ((व्योम)माप(अक्षर[1 - 2 * !!(condition)]))

/* Compile समय निश्चितion */
#अगर_अघोषित CT_ASSERT
#घोषणा CT_ASSERT(cnd) ((व्योम)माप(अक्षर[(cnd) ? 1 :  -1]))
#पूर्ण_अगर /* CT_ASSERT */

#समावेश <linux/bug.h>

/* TODO: it would be cleaner to use this:
 * #घोषणा निश्चित(cnd) BUG_ON(cnd)
 * but that causes many compiler warnings (==errors) under Android
 * because it seems that the BUG_ON() macro is not seen as a check by
 * gcc like the BUG() macro is. */
#घोषणा निश्चित(cnd) \
	करो अणु \
		अगर (!(cnd)) \
			BUG(); \
	पूर्ण जबतक (0)

#अगर_अघोषित PIPE_GENERATION
/* Deprecated OP___निश्चित, this is still used in ~1000 places
 * in the code. This will be हटाओd over समय.
 * The implementation क्रम the pipe generation tool is in see support.isp.h */
#घोषणा OP___निश्चित(cnd) निश्चित(cnd)

अटल अंतरभूत व्योम compile_समय_निश्चित(अचिन्हित पूर्णांक cond)
अणु
	/* Call undefined function अगर cond is false */
	व्योम _compile_समय_निश्चित(व्योम);
	अगर (!cond) _compile_समय_निश्चित();
पूर्ण
#पूर्ण_अगर /* PIPE_GENERATION */

#पूर्ण_अगर /* __ASSERT_SUPPORT_H_INCLUDED__ */
