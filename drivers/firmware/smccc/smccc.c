<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Arm Limited
 */

#घोषणा pr_fmt(fmt) "smccc: " fmt

#समावेश <linux/cache.h>
#समावेश <linux/init.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/archअक्रमom.h>

अटल u32 smccc_version = ARM_SMCCC_VERSION_1_0;
अटल क्रमागत arm_smccc_conduit smccc_conduit = SMCCC_CONDUIT_NONE;

bool __ro_after_init smccc_trng_available = false;

व्योम __init arm_smccc_version_init(u32 version, क्रमागत arm_smccc_conduit conduit)
अणु
	smccc_version = version;
	smccc_conduit = conduit;

	smccc_trng_available = smccc_probe_trng();
पूर्ण

क्रमागत arm_smccc_conduit arm_smccc_1_1_get_conduit(व्योम)
अणु
	अगर (smccc_version < ARM_SMCCC_VERSION_1_1)
		वापस SMCCC_CONDUIT_NONE;

	वापस smccc_conduit;
पूर्ण
EXPORT_SYMBOL_GPL(arm_smccc_1_1_get_conduit);

u32 arm_smccc_get_version(व्योम)
अणु
	वापस smccc_version;
पूर्ण
EXPORT_SYMBOL_GPL(arm_smccc_get_version);
