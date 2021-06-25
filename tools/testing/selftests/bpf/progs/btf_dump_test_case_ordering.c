<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * BTF-to-C dumper test क्रम topological sorting of dependent काष्ठाs.
 *
 * Copyright (c) 2019 Facebook
 */
/* ----- START-EXPECTED-OUTPUT ----- */
काष्ठा s1 अणुपूर्ण;

काष्ठा s3;

काष्ठा s4;

काष्ठा s2 अणु
	काष्ठा s2 *s2;
	काष्ठा s3 *s3;
	काष्ठा s4 *s4;
पूर्ण;

काष्ठा s3 अणु
	काष्ठा s1 s1;
	काष्ठा s2 s2;
पूर्ण;

काष्ठा s4 अणु
	काष्ठा s1 s1;
	काष्ठा s3 s3;
पूर्ण;

काष्ठा list_head अणु
	काष्ठा list_head *next;
	काष्ठा list_head *prev;
पूर्ण;

काष्ठा hlist_node अणु
	काष्ठा hlist_node *next;
	काष्ठा hlist_node **pprev;
पूर्ण;

काष्ठा hlist_head अणु
	काष्ठा hlist_node *first;
पूर्ण;

काष्ठा callback_head अणु
	काष्ठा callback_head *next;
	व्योम (*func)(काष्ठा callback_head *);
पूर्ण;

काष्ठा root_काष्ठा अणु
	काष्ठा s4 s4;
	काष्ठा list_head l;
	काष्ठा hlist_node n;
	काष्ठा hlist_head h;
	काष्ठा callback_head cb;
पूर्ण;

/*------ END-EXPECTED-OUTPUT ------ */

पूर्णांक f(काष्ठा root_काष्ठा *root)
अणु
	वापस 0;
पूर्ण
