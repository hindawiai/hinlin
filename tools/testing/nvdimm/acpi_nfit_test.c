<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright(c) 2018 Intel Corporation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश "watermark.h"
#समावेश <nfit.h>

nfit_test_watermark(acpi_nfit);

/* strong / override definition of nfit_पूर्णांकel_shutकरोwn_status */
व्योम nfit_पूर्णांकel_shutकरोwn_status(काष्ठा nfit_mem *nfit_mem)
अणु
	set_bit(NFIT_MEM_सूचीTY_COUNT, &nfit_mem->flags);
	nfit_mem->dirty_shutकरोwn = 42;
पूर्ण
