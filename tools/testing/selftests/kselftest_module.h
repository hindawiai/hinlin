<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित __KSELFTEST_MODULE_H
#घोषणा __KSELFTEST_MODULE_H

#समावेश <linux/module.h>

/*
 * Test framework क्रम writing test modules to be loaded by kselftest.
 * See Documentation/dev-tools/kselftest.rst क्रम an example test module.
 */

#घोषणा KSTM_MODULE_GLOBALS()			\
अटल अचिन्हित पूर्णांक total_tests __initdata;	\
अटल अचिन्हित पूर्णांक failed_tests __initdata;	\
अटल अचिन्हित पूर्णांक skipped_tests __initdata

#घोषणा KSTM_CHECK_ZERO(x) करो अणु						\
	total_tests++;							\
	अगर (x) अणु							\
		pr_warn("TC failed at %s:%d\n", __func__, __LINE__);	\
		failed_tests++;						\
	पूर्ण								\
पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक ksपंचांग_report(अचिन्हित पूर्णांक total_tests, अचिन्हित पूर्णांक failed_tests,
			      अचिन्हित पूर्णांक skipped_tests)
अणु
	अगर (failed_tests == 0) अणु
		अगर (skipped_tests) अणु
			pr_info("skipped %u tests\n", skipped_tests);
			pr_info("remaining %u tests passed\n", total_tests);
		पूर्ण अन्यथा
			pr_info("all %u tests passed\n", total_tests);
	पूर्ण अन्यथा
		pr_warn("failed %u out of %u tests\n", failed_tests, total_tests);

	वापस failed_tests ? -EINVAL : 0;
पूर्ण

#घोषणा KSTM_MODULE_LOADERS(__module)			\
अटल पूर्णांक __init __module##_init(व्योम)			\
अणु							\
	pr_info("loaded.\n");				\
	selftest();					\
	वापस ksपंचांग_report(total_tests, failed_tests, skipped_tests);	\
पूर्ण							\
अटल व्योम __निकास __module##_निकास(व्योम)		\
अणु							\
	pr_info("unloaded.\n");				\
पूर्ण							\
module_init(__module##_init);				\
module_निकास(__module##_निकास)

#पूर्ण_अगर	/* __KSELFTEST_MODULE_H */
