<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <test_progs.h>
#समावेश "test_endian.skel.h"

अटल पूर्णांक duration;

#घोषणा IN16 0x1234
#घोषणा IN32 0x12345678U
#घोषणा IN64 0x123456789abcdef0ULL

#घोषणा OUT16 0x3412
#घोषणा OUT32 0x78563412U
#घोषणा OUT64 0xf0debc9a78563412ULL

व्योम test_endian(व्योम)
अणु
	काष्ठा test_endian* skel;
	काष्ठा test_endian__bss *bss;
	पूर्णांक err;

	skel = test_endian__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;
	bss = skel->bss;

	bss->in16 = IN16;
	bss->in32 = IN32;
	bss->in64 = IN64;

	err = test_endian__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	usleep(1);

	CHECK(bss->out16 != OUT16, "out16", "got 0x%llx != exp 0x%llx\n",
	      (__u64)bss->out16, (__u64)OUT16);
	CHECK(bss->out32 != OUT32, "out32", "got 0x%llx != exp 0x%llx\n",
	      (__u64)bss->out32, (__u64)OUT32);
	CHECK(bss->out64 != OUT64, "out16", "got 0x%llx != exp 0x%llx\n",
	      (__u64)bss->out64, (__u64)OUT64);

	CHECK(bss->स्थिर16 != OUT16, "const16", "got 0x%llx != exp 0x%llx\n",
	      (__u64)bss->स्थिर16, (__u64)OUT16);
	CHECK(bss->स्थिर32 != OUT32, "const32", "got 0x%llx != exp 0x%llx\n",
	      (__u64)bss->स्थिर32, (__u64)OUT32);
	CHECK(bss->स्थिर64 != OUT64, "const64", "got 0x%llx != exp 0x%llx\n",
	      (__u64)bss->स्थिर64, (__u64)OUT64);
cleanup:
	test_endian__destroy(skel);
पूर्ण
