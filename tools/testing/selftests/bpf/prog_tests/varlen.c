<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <test_progs.h>
#समावेश <समय.स>
#समावेश "test_varlen.skel.h"

#घोषणा CHECK_VAL(got, exp) \
	CHECK((got) != (exp), "check", "got %ld != exp %ld\n", \
	      (दीर्घ)(got), (दीर्घ)(exp))

व्योम test_varlen(व्योम)
अणु
	पूर्णांक duration = 0, err;
	काष्ठा test_varlen* skel;
	काष्ठा test_varlen__bss *bss;
	काष्ठा test_varlen__data *data;
	स्थिर अक्षर str1[] = "Hello, ";
	स्थिर अक्षर str2[] = "World!";
	स्थिर अक्षर exp_str[] = "Hello, \0World!\0";
	स्थिर पूर्णांक size1 = माप(str1);
	स्थिर पूर्णांक size2 = माप(str2);

	skel = test_varlen__खोलो_and_load();
	अगर (CHECK(!skel, "skel_open", "failed to open skeleton\n"))
		वापस;
	bss = skel->bss;
	data = skel->data;

	err = test_varlen__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		जाओ cleanup;

	bss->test_pid = getpid();

	/* trigger everything */
	स_नकल(bss->buf_in1, str1, size1);
	स_नकल(bss->buf_in2, str2, size2);
	bss->capture = true;
	usleep(1);
	bss->capture = false;

	CHECK_VAL(bss->payload1_len1, size1);
	CHECK_VAL(bss->payload1_len2, size2);
	CHECK_VAL(bss->total1, size1 + size2);
	CHECK(स_भेद(bss->payload1, exp_str, size1 + size2), "content_check",
	      "doesn't match!\n");

	CHECK_VAL(data->payload2_len1, size1);
	CHECK_VAL(data->payload2_len2, size2);
	CHECK_VAL(data->total2, size1 + size2);
	CHECK(स_भेद(data->payload2, exp_str, size1 + size2), "content_check",
	      "doesn't match!\n");

	CHECK_VAL(data->payload3_len1, size1);
	CHECK_VAL(data->payload3_len2, size2);
	CHECK_VAL(data->total3, size1 + size2);
	CHECK(स_भेद(data->payload3, exp_str, size1 + size2), "content_check",
	      "doesn't match!\n");

	CHECK_VAL(data->payload4_len1, size1);
	CHECK_VAL(data->payload4_len2, size2);
	CHECK_VAL(data->total4, size1 + size2);
	CHECK(स_भेद(data->payload4, exp_str, size1 + size2), "content_check",
	      "doesn't match!\n");
cleanup:
	test_varlen__destroy(skel);
पूर्ण
