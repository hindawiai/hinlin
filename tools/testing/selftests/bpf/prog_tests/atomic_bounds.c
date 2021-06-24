<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <test_progs.h>

#समावेश "atomic_bounds.skel.h"

व्योम test_atomic_bounds(व्योम)
अणु
	काष्ठा atomic_bounds *skel;
	__u32 duration = 0;

	skel = atomic_bounds__खोलो_and_load();
	अगर (CHECK(!skel, "skel_load", "couldn't load program\n"))
		वापस;

	atomic_bounds__destroy(skel);
पूर्ण
