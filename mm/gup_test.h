<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __GUP_TEST_H
#घोषणा __GUP_TEST_H

#समावेश <linux/types.h>

#घोषणा GUP_FAST_BENCHMARK	_IOWR('g', 1, काष्ठा gup_test)
#घोषणा PIN_FAST_BENCHMARK	_IOWR('g', 2, काष्ठा gup_test)
#घोषणा PIN_LONGTERM_BENCHMARK	_IOWR('g', 3, काष्ठा gup_test)
#घोषणा GUP_BASIC_TEST		_IOWR('g', 4, काष्ठा gup_test)
#घोषणा PIN_BASIC_TEST		_IOWR('g', 5, काष्ठा gup_test)
#घोषणा DUMP_USER_PAGES_TEST	_IOWR('g', 6, काष्ठा gup_test)

#घोषणा GUP_TEST_MAX_PAGES_TO_DUMP		8

#घोषणा GUP_TEST_FLAG_DUMP_PAGES_USE_PIN	0x1

काष्ठा gup_test अणु
	__u64 get_delta_usec;
	__u64 put_delta_usec;
	__u64 addr;
	__u64 size;
	__u32 nr_pages_per_call;
	__u32 gup_flags;
	__u32 test_flags;
	/*
	 * Each non-zero entry is the number of the page (1-based: first page is
	 * page 1, so that zero entries mean "do nothing") from the .addr base.
	 */
	__u32 which_pages[GUP_TEST_MAX_PAGES_TO_DUMP];
पूर्ण;

#पूर्ण_अगर	/* __GUP_TEST_H */
