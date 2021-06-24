<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */

/*
 * Common user-facing libbpf helpers.
 *
 * Copyright (c) 2019 Facebook
 */

#अगर_अघोषित __LIBBPF_LIBBPF_COMMON_H
#घोषणा __LIBBPF_LIBBPF_COMMON_H

#समावेश <माला.स>

#अगर_अघोषित LIBBPF_API
#घोषणा LIBBPF_API __attribute__((visibility("default")))
#पूर्ण_अगर

#घोषणा LIBBPF_DEPRECATED(msg) __attribute__((deprecated(msg)))

/* Helper macro to declare and initialize libbpf options काष्ठा
 *
 * This dance with uninitialized declaration, followed by स_रखो to zero,
 * followed by assignment using compound literal syntax is करोne to preserve
 * ability to use a nice काष्ठा field initialization syntax and **hopefully**
 * have all the padding bytes initialized to zero. It's not guaranteed though,
 * when copying literal, that compiler won't copy garbage in literal's padding
 * bytes, but that's the best way I've found and it seems to work in practice.
 *
 * Macro declares opts काष्ठा of given type and name, zero-initializes,
 * including any extra padding, it with स_रखो() and then assigns initial
 * values provided by users in काष्ठा initializer-syntax as varargs.
 */
#घोषणा DECLARE_LIBBPF_OPTS(TYPE, NAME, ...)				    \
	काष्ठा TYPE NAME = (अणु 						    \
		स_रखो(&NAME, 0, माप(काष्ठा TYPE));			    \
		(काष्ठा TYPE) अणु						    \
			.sz = माप(काष्ठा TYPE),			    \
			__VA_ARGS__					    \
		पूर्ण;							    \
	पूर्ण)

#पूर्ण_अगर /* __LIBBPF_LIBBPF_COMMON_H */
