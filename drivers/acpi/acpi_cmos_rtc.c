<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI support क्रम CMOS RTC Address Space access
 *
 * Copyright (C) 2013, Intel Corporation
 * Authors: Lan Tianyu <tianyu.lan@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mc146818rtc.h>

#समावेश "internal.h"

अटल स्थिर काष्ठा acpi_device_id acpi_cmos_rtc_ids[] = अणु
	अणु "PNP0B00" पूर्ण,
	अणु "PNP0B01" पूर्ण,
	अणु "PNP0B02" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल acpi_status
acpi_cmos_rtc_space_handler(u32 function, acpi_physical_address address,
		      u32 bits, u64 *value64,
		      व्योम *handler_context, व्योम *region_context)
अणु
	पूर्णांक i;
	u8 *value = (u8 *)value64;

	अगर (address > 0xff || !value64)
		वापस AE_BAD_PARAMETER;

	अगर (function != ACPI_WRITE && function != ACPI_READ)
		वापस AE_BAD_PARAMETER;

	spin_lock_irq(&rtc_lock);

	क्रम (i = 0; i < DIV_ROUND_UP(bits, 8); ++i, ++address, ++value)
		अगर (function == ACPI_READ)
			*value = CMOS_READ(address);
		अन्यथा
			CMOS_WRITE(*value, address);

	spin_unlock_irq(&rtc_lock);

	वापस AE_OK;
पूर्ण

अटल पूर्णांक acpi_install_cmos_rtc_space_handler(काष्ठा acpi_device *adev,
		स्थिर काष्ठा acpi_device_id *id)
अणु
	acpi_status status;

	status = acpi_install_address_space_handler(adev->handle,
			ACPI_ADR_SPACE_CMOS,
			&acpi_cmos_rtc_space_handler,
			शून्य, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err(PREFIX "Error installing CMOS-RTC region handler\n");
		वापस -ENODEV;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम acpi_हटाओ_cmos_rtc_space_handler(काष्ठा acpi_device *adev)
अणु
	अगर (ACPI_FAILURE(acpi_हटाओ_address_space_handler(adev->handle,
			ACPI_ADR_SPACE_CMOS, &acpi_cmos_rtc_space_handler)))
		pr_err(PREFIX "Error removing CMOS-RTC region handler\n");
पूर्ण

अटल काष्ठा acpi_scan_handler cmos_rtc_handler = अणु
	.ids = acpi_cmos_rtc_ids,
	.attach = acpi_install_cmos_rtc_space_handler,
	.detach = acpi_हटाओ_cmos_rtc_space_handler,
पूर्ण;

व्योम __init acpi_cmos_rtc_init(व्योम)
अणु
	acpi_scan_add_handler(&cmos_rtc_handler);
पूर्ण
