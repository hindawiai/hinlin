<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * BTF-to-C dumper tests क्रम bitfield.
 *
 * Copyright (c) 2019 Facebook
 */
#समावेश <stdbool.h>

/* ----- START-EXPECTED-OUTPUT ----- */
/*
 *काष्ठा bitfields_only_mixed_types अणु
 *	पूर्णांक a: 3;
 *	दीर्घ पूर्णांक b: 2;
 *	_Bool c: 1;
 *	क्रमागत अणु
 *		A = 0,
 *		B = 1,
 *	पूर्ण d: 1;
 *	लघु e: 5;
 *	पूर्णांक: 20;
 *	अचिन्हित पूर्णांक f: 30;
 *पूर्ण;
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

काष्ठा bitfields_only_mixed_types अणु
	पूर्णांक a: 3;
	दीर्घ पूर्णांक b: 2;
	bool c: 1; /* it's really a _Bool type */
	क्रमागत अणु
		A, /* A = 0, dumper is very explicit */
		B, /* B = 1, same */
	पूर्ण d: 1;
	लघु e: 5;
	/* 20-bit padding here */
	अचिन्हित f: 30; /* this माला_लो aligned on 4-byte boundary */
पूर्ण;

/* ----- START-EXPECTED-OUTPUT ----- */
/*
 *काष्ठा bitfield_mixed_with_others अणु
 *	अक्षर: 4;
 *	पूर्णांक a: 4;
 *	लघु b;
 *	दीर्घ पूर्णांक c;
 *	दीर्घ पूर्णांक d: 8;
 *	पूर्णांक e;
 *	पूर्णांक f;
 *पूर्ण;
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */
काष्ठा bitfield_mixed_with_others अणु
	दीर्घ: 4; /* अक्षर is enough as a backing field */
	पूर्णांक a: 4;
	/* 8-bit implicit padding */
	लघु b; /* combined with previous bitfield */
	/* 4 more bytes of implicit padding */
	दीर्घ c;
	दीर्घ d: 8;
	/* 24 bits implicit padding */
	पूर्णांक e; /* combined with previous bitfield */
	पूर्णांक f;
	/* 4 bytes of padding */
पूर्ण;

/* ----- START-EXPECTED-OUTPUT ----- */
/*
 *काष्ठा bitfield_flushed अणु
 *	पूर्णांक a: 4;
 *	दीर्घ: 60;
 *	दीर्घ पूर्णांक b: 16;
 *पूर्ण;
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */
काष्ठा bitfield_flushed अणु
	पूर्णांक a: 4;
	दीर्घ: 0; /* flush until next natural alignment boundary */
	दीर्घ b: 16;
पूर्ण;

पूर्णांक f(काष्ठा अणु
	काष्ठा bitfields_only_mixed_types _1;
	काष्ठा bitfield_mixed_with_others _2;
	काष्ठा bitfield_flushed _3;
पूर्ण *_)
अणु
	वापस 0;
पूर्ण
