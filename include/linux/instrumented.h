<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * This header provides generic wrappers क्रम memory access instrumentation that
 * the compiler cannot emit क्रम: KASAN, KCSAN.
 */
#अगर_अघोषित _LINUX_INSTRUMENTED_H
#घोषणा _LINUX_INSTRUMENTED_H

#समावेश <linux/compiler.h>
#समावेश <linux/kasan-checks.h>
#समावेश <linux/kcsan-checks.h>
#समावेश <linux/types.h>

/**
 * instrument_पढ़ो - instrument regular पढ़ो access
 *
 * Instrument a regular पढ़ो access. The instrumentation should be inserted
 * beक्रमe the actual पढ़ो happens.
 *
 * @ptr address of access
 * @size size of access
 */
अटल __always_अंतरभूत व्योम instrument_पढ़ो(स्थिर अस्थिर व्योम *v, माप_प्रकार size)
अणु
	kasan_check_पढ़ो(v, size);
	kcsan_check_पढ़ो(v, size);
पूर्ण

/**
 * instrument_ग_लिखो - instrument regular ग_लिखो access
 *
 * Instrument a regular ग_लिखो access. The instrumentation should be inserted
 * beक्रमe the actual ग_लिखो happens.
 *
 * @ptr address of access
 * @size size of access
 */
अटल __always_अंतरभूत व्योम instrument_ग_लिखो(स्थिर अस्थिर व्योम *v, माप_प्रकार size)
अणु
	kasan_check_ग_लिखो(v, size);
	kcsan_check_ग_लिखो(v, size);
पूर्ण

/**
 * instrument_पढ़ो_ग_लिखो - instrument regular पढ़ो-ग_लिखो access
 *
 * Instrument a regular ग_लिखो access. The instrumentation should be inserted
 * beक्रमe the actual ग_लिखो happens.
 *
 * @ptr address of access
 * @size size of access
 */
अटल __always_अंतरभूत व्योम instrument_पढ़ो_ग_लिखो(स्थिर अस्थिर व्योम *v, माप_प्रकार size)
अणु
	kasan_check_ग_लिखो(v, size);
	kcsan_check_पढ़ो_ग_लिखो(v, size);
पूर्ण

/**
 * instrument_atomic_पढ़ो - instrument atomic पढ़ो access
 *
 * Instrument an atomic पढ़ो access. The instrumentation should be inserted
 * beक्रमe the actual पढ़ो happens.
 *
 * @ptr address of access
 * @size size of access
 */
अटल __always_अंतरभूत व्योम instrument_atomic_पढ़ो(स्थिर अस्थिर व्योम *v, माप_प्रकार size)
अणु
	kasan_check_पढ़ो(v, size);
	kcsan_check_atomic_पढ़ो(v, size);
पूर्ण

/**
 * instrument_atomic_ग_लिखो - instrument atomic ग_लिखो access
 *
 * Instrument an atomic ग_लिखो access. The instrumentation should be inserted
 * beक्रमe the actual ग_लिखो happens.
 *
 * @ptr address of access
 * @size size of access
 */
अटल __always_अंतरभूत व्योम instrument_atomic_ग_लिखो(स्थिर अस्थिर व्योम *v, माप_प्रकार size)
अणु
	kasan_check_ग_लिखो(v, size);
	kcsan_check_atomic_ग_लिखो(v, size);
पूर्ण

/**
 * instrument_atomic_पढ़ो_ग_लिखो - instrument atomic पढ़ो-ग_लिखो access
 *
 * Instrument an atomic पढ़ो-ग_लिखो access. The instrumentation should be
 * inserted beक्रमe the actual ग_लिखो happens.
 *
 * @ptr address of access
 * @size size of access
 */
अटल __always_अंतरभूत व्योम instrument_atomic_पढ़ो_ग_लिखो(स्थिर अस्थिर व्योम *v, माप_प्रकार size)
अणु
	kasan_check_ग_लिखो(v, size);
	kcsan_check_atomic_पढ़ो_ग_लिखो(v, size);
पूर्ण

/**
 * instrument_copy_to_user - instrument पढ़ोs of copy_to_user
 *
 * Instrument पढ़ोs from kernel memory, that are due to copy_to_user (and
 * variants). The instrumentation must be inserted beक्रमe the accesses.
 *
 * @to destination address
 * @from source address
 * @n number of bytes to copy
 */
अटल __always_अंतरभूत व्योम
instrument_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	kasan_check_पढ़ो(from, n);
	kcsan_check_पढ़ो(from, n);
पूर्ण

/**
 * instrument_copy_from_user - instrument ग_लिखोs of copy_from_user
 *
 * Instrument ग_लिखोs to kernel memory, that are due to copy_from_user (and
 * variants). The instrumentation should be inserted beक्रमe the accesses.
 *
 * @to destination address
 * @from source address
 * @n number of bytes to copy
 */
अटल __always_अंतरभूत व्योम
instrument_copy_from_user(स्थिर व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	kasan_check_ग_लिखो(to, n);
	kcsan_check_ग_लिखो(to, n);
पूर्ण

#पूर्ण_अगर /* _LINUX_INSTRUMENTED_H */
