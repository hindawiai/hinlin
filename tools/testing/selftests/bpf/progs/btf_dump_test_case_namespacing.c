<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * BTF-to-C dumper test validating no name versioning happens between
 * independent C namespaces (काष्ठा/जोड़/क्रमागत vs प्रकार/क्रमागत values).
 *
 * Copyright (c) 2019 Facebook
 */
/* ----- START-EXPECTED-OUTPUT ----- */
काष्ठा S अणु
	पूर्णांक S;
	पूर्णांक U;
पूर्ण;

प्रकार काष्ठा S S;

जोड़ U अणु
	पूर्णांक S;
	पूर्णांक U;
पूर्ण;

प्रकार जोड़ U U;

क्रमागत E अणु
	V = 0,
पूर्ण;

प्रकार क्रमागत E E;

काष्ठा A अणुपूर्ण;

जोड़ B अणुपूर्ण;

क्रमागत C अणु
	A = 1,
	B = 2,
	C = 3,
पूर्ण;

काष्ठा X अणुपूर्ण;

जोड़ Y अणुपूर्ण;

क्रमागत Z;

प्रकार पूर्णांक X;

प्रकार पूर्णांक Y;

प्रकार पूर्णांक Z;

/*------ END-EXPECTED-OUTPUT ------ */

पूर्णांक f(काष्ठा अणु
	काष्ठा S _1;
	S _2;
	जोड़ U _3;
	U _4;
	क्रमागत E _5;
	E _6;
	काष्ठा A a;
	जोड़ B b;
	क्रमागत C c;
	काष्ठा X x;
	जोड़ Y y;
	क्रमागत Z *z;
	X xx;
	Y yy;
	Z zz;
पूर्ण *_)
अणु
	वापस 0;
पूर्ण
