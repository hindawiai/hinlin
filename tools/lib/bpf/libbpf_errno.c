<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * Copyright (C) 2013-2015 Alexei Starovoitov <ast@kernel.org>
 * Copyright (C) 2015 Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2015 Huawei Inc.
 * Copyright (C) 2017 Nicira, Inc.
 */

#अघोषित _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <माला.स>

#समावेश "libbpf.h"

/* make sure libbpf करोesn't use kernel-only पूर्णांकeger प्रकारs */
#आशय GCC poison u8 u16 u32 u64 s8 s16 s32 s64

#घोषणा ERRNO_OFFSET(e)		((e) - __LIBBPF_ERRNO__START)
#घोषणा ERRCODE_OFFSET(c)	ERRNO_OFFSET(LIBBPF_ERRNO__##c)
#घोषणा NR_ERRNO	(__LIBBPF_ERRNO__END - __LIBBPF_ERRNO__START)

अटल स्थिर अक्षर *libbpf_म_त्रुटि_table[NR_ERRNO] = अणु
	[ERRCODE_OFFSET(LIBELF)]	= "Something wrong in libelf",
	[ERRCODE_OFFSET(FORMAT)]	= "BPF object format invalid",
	[ERRCODE_OFFSET(KVERSION)]	= "'version' section incorrect or lost",
	[ERRCODE_OFFSET(ENDIAN)]	= "Endian mismatch",
	[ERRCODE_OFFSET(INTERNAL)]	= "Internal error in libbpf",
	[ERRCODE_OFFSET(RELOC)]		= "Relocation failed",
	[ERRCODE_OFFSET(VERIFY)]	= "Kernel verifier blocks program loading",
	[ERRCODE_OFFSET(PROG2BIG)]	= "Program too big",
	[ERRCODE_OFFSET(KVER)]		= "Incorrect kernel version",
	[ERRCODE_OFFSET(PROGTYPE)]	= "Kernel doesn't support this program type",
	[ERRCODE_OFFSET(WRNGPID)]	= "Wrong pid in netlink message",
	[ERRCODE_OFFSET(INVSEQ)]	= "Invalid netlink sequence",
	[ERRCODE_OFFSET(NLPARSE)]	= "Incorrect netlink message parsing",
पूर्ण;

पूर्णांक libbpf_म_त्रुटि(पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	अगर (!buf || !size)
		वापस -1;

	err = err > 0 ? err : -err;

	अगर (err < __LIBBPF_ERRNO__START) अणु
		पूर्णांक ret;

		ret = म_त्रुटि_r(err, buf, size);
		buf[size - 1] = '\0';
		वापस ret;
	पूर्ण

	अगर (err < __LIBBPF_ERRNO__END) अणु
		स्थिर अक्षर *msg;

		msg = libbpf_म_त्रुटि_table[ERRNO_OFFSET(err)];
		snम_लिखो(buf, size, "%s", msg);
		buf[size - 1] = '\0';
		वापस 0;
	पूर्ण

	snम_लिखो(buf, size, "Unknown libbpf error %d", err);
	buf[size - 1] = '\0';
	वापस -1;
पूर्ण
