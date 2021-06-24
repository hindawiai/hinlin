<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tools/testing/selftests/kvm/include/test_util.h
 *
 * Copyright (C) 2018, Google LLC.
 */

#अगर_अघोषित SELFTEST_KVM_TEST_UTIL_H
#घोषणा SELFTEST_KVM_TEST_UTIL_H

#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <sys/mman.h>
#समावेश "kselftest.h"

अटल अंतरभूत पूर्णांक _no_म_लिखो(स्थिर अक्षर *क्रमmat, ...) अणु वापस 0; पूर्ण

#अगर_घोषित DEBUG
#घोषणा pr_debug(...) म_लिखो(__VA_ARGS__)
#अन्यथा
#घोषणा pr_debug(...) _no_म_लिखो(__VA_ARGS__)
#पूर्ण_अगर
#अगर_अघोषित QUIET
#घोषणा pr_info(...) म_लिखो(__VA_ARGS__)
#अन्यथा
#घोषणा pr_info(...) _no_म_लिखो(__VA_ARGS__)
#पूर्ण_अगर

व्योम prपूर्णांक_skip(स्थिर अक्षर *fmt, ...) __attribute__((क्रमmat(म_लिखो, 1, 2)));

sमाप_प्रकार test_ग_लिखो(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार count);
sमाप_प्रकार test_पढ़ो(पूर्णांक fd, व्योम *buf, माप_प्रकार count);
पूर्णांक test_seq_पढ़ो(स्थिर अक्षर *path, अक्षर **bufp, माप_प्रकार *sizep);

व्योम test_निश्चित(bool exp, स्थिर अक्षर *exp_str,
		 स्थिर अक्षर *file, अचिन्हित पूर्णांक line, स्थिर अक्षर *fmt, ...)
		__attribute__((क्रमmat(म_लिखो, 5, 6)));

#घोषणा TEST_ASSERT(e, fmt, ...) \
	test_निश्चित((e), #e, __खाता__, __LINE__, fmt, ##__VA_ARGS__)

#घोषणा ASSERT_EQ(a, b) करो अणु \
	typeof(a) __a = (a); \
	typeof(b) __b = (b); \
	TEST_ASSERT(__a == __b, \
		    "ASSERT_EQ(%s, %s) failed.\n" \
		    "\t%s is %#lx\n" \
		    "\t%s is %#lx", \
		    #a, #b, #a, (अचिन्हित दीर्घ) __a, #b, (अचिन्हित दीर्घ) __b); \
पूर्ण जबतक (0)

#घोषणा TEST_FAIL(fmt, ...) \
	TEST_ASSERT(false, fmt, ##__VA_ARGS__)

माप_प्रकार parse_size(स्थिर अक्षर *size);

पूर्णांक64_t बारpec_to_ns(काष्ठा बारpec ts);
काष्ठा बारpec बारpec_add_ns(काष्ठा बारpec ts, पूर्णांक64_t ns);
काष्ठा बारpec बारpec_add(काष्ठा बारpec ts1, काष्ठा बारpec ts2);
काष्ठा बारpec बारpec_sub(काष्ठा बारpec ts1, काष्ठा बारpec ts2);
काष्ठा बारpec बारpec_elapsed(काष्ठा बारpec start);
काष्ठा बारpec बारpec_भाग(काष्ठा बारpec ts, पूर्णांक भागisor);

क्रमागत vm_mem_backing_src_type अणु
	VM_MEM_SRC_ANONYMOUS,
	VM_MEM_SRC_ANONYMOUS_THP,
	VM_MEM_SRC_ANONYMOUS_HUGETLB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_16KB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_64KB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_512KB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_1MB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_2MB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_8MB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_16MB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_32MB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_256MB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_512MB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_1GB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_2GB,
	VM_MEM_SRC_ANONYMOUS_HUGETLB_16GB,
	VM_MEM_SRC_SHMEM,
	VM_MEM_SRC_SHARED_HUGETLB,
	NUM_SRC_TYPES,
पूर्ण;

काष्ठा vm_mem_backing_src_alias अणु
	स्थिर अक्षर *name;
	uपूर्णांक32_t flag;
पूर्ण;

bool thp_configured(व्योम);
माप_प्रकार get_trans_hugepagesz(व्योम);
माप_प्रकार get_def_hugetlb_pagesz(व्योम);
स्थिर काष्ठा vm_mem_backing_src_alias *vm_mem_backing_src_alias(uपूर्णांक32_t i);
माप_प्रकार get_backing_src_pagesz(uपूर्णांक32_t i);
व्योम backing_src_help(व्योम);
क्रमागत vm_mem_backing_src_type parse_backing_src_type(स्थिर अक्षर *type_name);

/*
 * Whether or not the given source type is shared memory (as opposed to
 * anonymous).
 */
अटल अंतरभूत bool backing_src_is_shared(क्रमागत vm_mem_backing_src_type t)
अणु
	वापस vm_mem_backing_src_alias(t)->flag & MAP_SHARED;
पूर्ण

#पूर्ण_अगर /* SELFTEST_KVM_TEST_UTIL_H */
