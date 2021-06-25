<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Intel PMC Core platक्रमm init
 * Copyright (c) 2019, Google Inc.
 * Author - Rajat Jain
 *
 * This code instantiates platक्रमm devices क्रम पूर्णांकel_pmc_core driver, only
 * on supported platक्रमms that may not have the ACPI devices in the ACPI tables.
 * No new platक्रमms should be added here, because we expect that new platक्रमms
 * should all have the ACPI device, which is the preferred way of क्रमागतeration.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

अटल व्योम पूर्णांकel_pmc_core_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल काष्ठा platक्रमm_device *pmc_core_device;

/*
 * पूर्णांकel_pmc_core_platक्रमm_ids is the list of platक्रमms where we want to
 * instantiate the platक्रमm_device अगर not alपढ़ोy instantiated. This is
 * dअगरferent than पूर्णांकel_pmc_core_ids in पूर्णांकel_pmc_core.c which is the
 * list of platक्रमms that the driver supports क्रम pmc_core device. The
 * other list may grow, but this list should not.
 */
अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_pmc_core_platक्रमm_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_L,		&pmc_core_device),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE,		&pmc_core_device),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE_L,		&pmc_core_device),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE,		&pmc_core_device),
	X86_MATCH_INTEL_FAM6_MODEL(CANNONLAKE_L,	&pmc_core_device),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_L,		&pmc_core_device),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE,		&pmc_core_device),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE_L,		&pmc_core_device),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, पूर्णांकel_pmc_core_platक्रमm_ids);

अटल पूर्णांक __init pmc_core_platक्रमm_init(व्योम)
अणु
	पूर्णांक retval;

	/* Skip creating the platक्रमm device अगर ACPI alपढ़ोy has a device */
	अगर (acpi_dev_present("INT33A1", शून्य, -1))
		वापस -ENODEV;

	अगर (!x86_match_cpu(पूर्णांकel_pmc_core_platक्रमm_ids))
		वापस -ENODEV;

	pmc_core_device = kzalloc(माप(*pmc_core_device), GFP_KERNEL);
	अगर (!pmc_core_device)
		वापस -ENOMEM;

	pmc_core_device->name = "intel_pmc_core";
	pmc_core_device->dev.release = पूर्णांकel_pmc_core_release;

	retval = platक्रमm_device_रेजिस्टर(pmc_core_device);
	अगर (retval)
		kमुक्त(pmc_core_device);

	वापस retval;
पूर्ण

अटल व्योम __निकास pmc_core_platक्रमm_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pmc_core_device);
पूर्ण

module_init(pmc_core_platक्रमm_init);
module_निकास(pmc_core_platक्रमm_निकास);
MODULE_LICENSE("GPL v2");
