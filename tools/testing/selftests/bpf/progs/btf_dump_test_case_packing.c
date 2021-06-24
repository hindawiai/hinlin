<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * BTF-to-C dumper tests क्रम काष्ठा packing determination.
 *
 * Copyright (c) 2019 Facebook
 */
/* ----- START-EXPECTED-OUTPUT ----- */
काष्ठा packed_trailing_space अणु
	पूर्णांक a;
	लघु b;
पूर्ण __attribute__((packed));

काष्ठा non_packed_trailing_space अणु
	पूर्णांक a;
	लघु b;
पूर्ण;

काष्ठा packed_fields अणु
	लघु a;
	पूर्णांक b;
पूर्ण __attribute__((packed));

काष्ठा non_packed_fields अणु
	लघु a;
	पूर्णांक b;
पूर्ण;

काष्ठा nested_packed अणु
	अक्षर: 4;
	पूर्णांक a: 4;
	दीर्घ पूर्णांक b;
	काष्ठा अणु
		अक्षर c;
		पूर्णांक d;
	पूर्ण __attribute__((packed)) e;
पूर्ण __attribute__((packed));

जोड़ जोड़_is_never_packed अणु
	पूर्णांक a: 4;
	अक्षर b;
	अक्षर c: 1;
पूर्ण;

जोड़ जोड़_करोes_not_need_packing अणु
	काष्ठा अणु
		दीर्घ पूर्णांक a;
		पूर्णांक b;
	पूर्ण __attribute__((packed));
	पूर्णांक c;
पूर्ण;

जोड़ jump_code_जोड़ अणु
	अक्षर code[5];
	काष्ठा अणु
		अक्षर jump;
		पूर्णांक offset;
	पूर्ण __attribute__((packed));
पूर्ण;

/*------ END-EXPECTED-OUTPUT ------ */

पूर्णांक f(काष्ठा अणु
	काष्ठा packed_trailing_space _1;
	काष्ठा non_packed_trailing_space _2;
	काष्ठा packed_fields _3;
	काष्ठा non_packed_fields _4;
	काष्ठा nested_packed _5;
	जोड़ जोड़_is_never_packed _6;
	जोड़ जोड़_करोes_not_need_packing _7;
	जोड़ jump_code_जोड़ _8;
पूर्ण *_)
अणु
	वापस 0;
पूर्ण
