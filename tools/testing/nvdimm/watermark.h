<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright(c) 2018 Intel Corporation. All rights reserved.
#अगर_अघोषित _TEST_NVDIMM_WATERMARK_H_
#घोषणा _TEST_NVDIMM_WATERMARK_H_
पूर्णांक pmem_test(व्योम);
पूर्णांक libnvdimm_test(व्योम);
पूर्णांक acpi_nfit_test(व्योम);
पूर्णांक device_dax_test(व्योम);
पूर्णांक dax_pmem_test(व्योम);
पूर्णांक dax_pmem_core_test(व्योम);
पूर्णांक dax_pmem_compat_test(व्योम);

/*
 * dummy routine क्रम nfit_test to validate it is linking to the properly
 * mocked module and not the standard one from the base tree.
 */
#घोषणा nfit_test_watermark(x)				\
पूर्णांक x##_test(व्योम)					\
अणु							\
	pr_debug("%s for nfit_test\n", KBUILD_MODNAME);	\
	वापस 0;					\
पूर्ण							\
EXPORT_SYMBOL(x##_test)
#पूर्ण_अगर /* _TEST_NVDIMM_WATERMARK_H_ */
