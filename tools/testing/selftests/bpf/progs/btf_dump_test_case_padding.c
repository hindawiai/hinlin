<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * BTF-to-C dumper tests क्रम implicit and explicit padding between fields and
 * at the end of a काष्ठा.
 *
 * Copyright (c) 2019 Facebook
 */
/* ----- START-EXPECTED-OUTPUT ----- */
काष्ठा padded_implicitly अणु
	पूर्णांक a;
	दीर्घ पूर्णांक b;
	अक्षर c;
पूर्ण;

/* ------ END-EXPECTED-OUTPUT ------ */

/* ----- START-EXPECTED-OUTPUT ----- */
/*
 *काष्ठा padded_explicitly अणु
 *	पूर्णांक a;
 *	पूर्णांक: 32;
 *	पूर्णांक b;
 *पूर्ण;
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

काष्ठा padded_explicitly अणु
	पूर्णांक a;
	पूर्णांक: 1; /* algo will explicitly pad with full 32 bits here */
	पूर्णांक b;
पूर्ण;

/* ----- START-EXPECTED-OUTPUT ----- */
/*
 *काष्ठा padded_a_lot अणु
 *	पूर्णांक a;
 *	दीर्घ: 32;
 *	दीर्घ: 64;
 *	दीर्घ: 64;
 *	पूर्णांक b;
 *पूर्ण;
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

काष्ठा padded_a_lot अणु
	पूर्णांक a;
	/* 32 bit of implicit padding here, which algo will make explicit */
	दीर्घ: 64;
	दीर्घ: 64;
	पूर्णांक b;
पूर्ण;

/* ----- START-EXPECTED-OUTPUT ----- */
/*
 *काष्ठा padded_cache_line अणु
 *	पूर्णांक a;
 *	दीर्घ: 32;
 *	दीर्घ: 64;
 *	दीर्घ: 64;
 *	दीर्घ: 64;
 *	पूर्णांक b;
 *	दीर्घ: 32;
 *	दीर्घ: 64;
 *	दीर्घ: 64;
 *	दीर्घ: 64;
 *पूर्ण;
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

काष्ठा padded_cache_line अणु
	पूर्णांक a;
	पूर्णांक b __attribute__((aligned(32)));
पूर्ण;

/* ----- START-EXPECTED-OUTPUT ----- */
/*
 *काष्ठा zone_padding अणु
 *	अक्षर x[0];
 *पूर्ण;
 *
 *काष्ठा zone अणु
 *	पूर्णांक a;
 *	लघु b;
 *	लघु: 16;
 *	काष्ठा zone_padding __pad__;
 *पूर्ण;
 *
 */
/* ------ END-EXPECTED-OUTPUT ------ */

काष्ठा zone_padding अणु
	अक्षर x[0];
पूर्ण __attribute__((__aligned__(8)));

काष्ठा zone अणु
	पूर्णांक a;
	लघु b;
	काष्ठा zone_padding __pad__;
पूर्ण;

पूर्णांक f(काष्ठा अणु
	काष्ठा padded_implicitly _1;
	काष्ठा padded_explicitly _2;
	काष्ठा padded_a_lot _3;
	काष्ठा padded_cache_line _4;
	काष्ठा zone _5;
पूर्ण *_)
अणु
	वापस 0;
पूर्ण
