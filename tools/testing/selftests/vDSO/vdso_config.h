<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * vdso_config.h: Configuration options क्रम vDSO tests.
 * Copyright (c) 2019 Arm Ltd.
 */
#अगर_अघोषित __VDSO_CONFIG_H__
#घोषणा __VDSO_CONFIG_H__

/*
 * Each architecture exports its vDSO implementation with dअगरferent names
 * and a dअगरferent version from the others, so we need to handle it as a
 * special हाल.
 */
#अगर defined(__arm__)
#घोषणा VDSO_VERSION		0
#घोषणा VDSO_NAMES		1
#घोषणा VDSO_32BIT		1
#या_अगर defined(__aarch64__)
#घोषणा VDSO_VERSION		3
#घोषणा VDSO_NAMES		0
#या_अगर defined(__घातerpc__)
#घोषणा VDSO_VERSION		1
#घोषणा VDSO_NAMES		0
#घोषणा VDSO_32BIT		1
#या_अगर defined(__घातerpc64__)
#घोषणा VDSO_VERSION		1
#घोषणा VDSO_NAMES		0
#या_अगर defined (__s390__)
#घोषणा VDSO_VERSION		2
#घोषणा VDSO_NAMES		0
#घोषणा VDSO_32BIT		1
#या_अगर defined (__s390X__)
#घोषणा VDSO_VERSION		2
#घोषणा VDSO_NAMES		0
#या_अगर defined(__mips__)
#घोषणा VDSO_VERSION		0
#घोषणा VDSO_NAMES		1
#घोषणा VDSO_32BIT		1
#या_अगर defined(__sparc__)
#घोषणा VDSO_VERSION		0
#घोषणा VDSO_NAMES		1
#घोषणा VDSO_32BIT		1
#या_अगर defined(__i386__)
#घोषणा VDSO_VERSION		0
#घोषणा VDSO_NAMES		1
#घोषणा VDSO_32BIT		1
#या_अगर defined(__x86_64__)
#घोषणा VDSO_VERSION		0
#घोषणा VDSO_NAMES		1
#या_अगर defined(__riscv__) || defined(__riscv)
#घोषणा VDSO_VERSION		5
#घोषणा VDSO_NAMES		1
#अगर __riscv_xlen == 32
#घोषणा VDSO_32BIT		1
#पूर्ण_अगर
#अन्यथा /* nds32 */
#घोषणा VDSO_VERSION		4
#घोषणा VDSO_NAMES		1
#घोषणा VDSO_32BIT		1
#पूर्ण_अगर

अटल स्थिर अक्षर *versions[6] = अणु
	"LINUX_2.6",
	"LINUX_2.6.15",
	"LINUX_2.6.29",
	"LINUX_2.6.39",
	"LINUX_4",
	"LINUX_4.15",
पूर्ण;

अटल स्थिर अक्षर *names[2][6] = अणु
	अणु
		"__kernel_gettimeofday",
		"__kernel_clock_gettime",
		"__kernel_time",
		"__kernel_clock_getres",
		"__kernel_getcpu",
#अगर defined(VDSO_32BIT)
		"__kernel_clock_gettime64",
#पूर्ण_अगर
	पूर्ण,
	अणु
		"__vdso_gettimeofday",
		"__vdso_clock_gettime",
		"__vdso_time",
		"__vdso_clock_getres",
		"__vdso_getcpu",
#अगर defined(VDSO_32BIT)
		"__vdso_clock_gettime64",
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

#पूर्ण_अगर /* __VDSO_CONFIG_H__ */
