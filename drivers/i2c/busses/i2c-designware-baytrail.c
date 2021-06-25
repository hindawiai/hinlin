<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel BayTrail PMIC I2C bus semaphore implementation
 * Copyright (c) 2014, Intel Corporation.
 */
#समावेश <linux/device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/iosf_mbi.h>

#समावेश "i2c-designware-core.h"

पूर्णांक i2c_dw_probe_lock_support(काष्ठा dw_i2c_dev *dev)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ shared_host = 0;
	acpi_handle handle;

	अगर (!dev || !dev->dev)
		वापस 0;

	handle = ACPI_HANDLE(dev->dev);
	अगर (!handle)
		वापस 0;

	status = acpi_evaluate_पूर्णांकeger(handle, "_SEM", शून्य, &shared_host);
	अगर (ACPI_FAILURE(status))
		वापस 0;

	अगर (!shared_host)
		वापस 0;

	अगर (!iosf_mbi_available())
		वापस -EPROBE_DEFER;

	dev_info(dev->dev, "I2C bus managed by PUNIT\n");
	dev->acquire_lock = iosf_mbi_block_punit_i2c_access;
	dev->release_lock = iosf_mbi_unblock_punit_i2c_access;
	dev->shared_with_punit = true;

	वापस 0;
पूर्ण
