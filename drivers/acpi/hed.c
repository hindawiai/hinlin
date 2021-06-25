<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI Hardware Error Device (PNP0C33) Driver
 *
 * Copyright (C) 2010, Intel Corp.
 *	Author: Huang Ying <ying.huang@पूर्णांकel.com>
 *
 * ACPI Hardware Error Device is used to report some hardware errors
 * notअगरied via SCI, मुख्यly the corrected errors.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/hed.h>

अटल स्थिर काष्ठा acpi_device_id acpi_hed_ids[] = अणु
	अणु"PNP0C33", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acpi_hed_ids);

अटल acpi_handle hed_handle;

अटल BLOCKING_NOTIFIER_HEAD(acpi_hed_notअगरy_list);

पूर्णांक रेजिस्टर_acpi_hed_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&acpi_hed_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_acpi_hed_notअगरier);

व्योम unरेजिस्टर_acpi_hed_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&acpi_hed_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_acpi_hed_notअगरier);

/*
 * SCI to report hardware error is क्रमwarded to the listeners of HED,
 * it is used by HEST Generic Hardware Error Source with notअगरy type
 * SCI.
 */
अटल व्योम acpi_hed_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	blocking_notअगरier_call_chain(&acpi_hed_notअगरy_list, 0, शून्य);
पूर्ण

अटल पूर्णांक acpi_hed_add(काष्ठा acpi_device *device)
अणु
	/* Only one hardware error device */
	अगर (hed_handle)
		वापस -EINVAL;
	hed_handle = device->handle;
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_hed_हटाओ(काष्ठा acpi_device *device)
अणु
	hed_handle = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा acpi_driver acpi_hed_driver = अणु
	.name = "hardware_error_device",
	.class = "hardware_error",
	.ids = acpi_hed_ids,
	.ops = अणु
		.add = acpi_hed_add,
		.हटाओ = acpi_hed_हटाओ,
		.notअगरy = acpi_hed_notअगरy,
	पूर्ण,
पूर्ण;
module_acpi_driver(acpi_hed_driver);

MODULE_AUTHOR("Huang Ying");
MODULE_DESCRIPTION("ACPI Hardware Error Device Driver");
MODULE_LICENSE("GPL");
