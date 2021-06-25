<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * ACPI support क्रम platक्रमm bus type.
 *
 * Copyright (C) 2015, Linaro Ltd
 * Author: Graeme Gregory <graeme.gregory@linaro.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "internal.h"

अटल स्थिर काष्ठा acpi_device_id amba_id_list[] = अणु
	अणु"ARMH0061", 0पूर्ण, /* PL061 GPIO Device */
	अणु"ARMHC500", 0पूर्ण, /* ARM CoreSight ETM4x */
	अणु"ARMHC501", 0पूर्ण, /* ARM CoreSight ETR */
	अणु"ARMHC502", 0पूर्ण, /* ARM CoreSight STM */
	अणु"ARMHC503", 0पूर्ण, /* ARM CoreSight Debug */
	अणु"ARMHC979", 0पूर्ण, /* ARM CoreSight TPIU */
	अणु"ARMHC97C", 0पूर्ण, /* ARM CoreSight SoC-400 TMC, SoC-600 ETF/ETB */
	अणु"ARMHC98D", 0पूर्ण, /* ARM CoreSight Dynamic Replicator */
	अणु"ARMHC9CA", 0पूर्ण, /* ARM CoreSight CATU */
	अणु"ARMHC9FF", 0पूर्ण, /* ARM CoreSight Dynamic Funnel */
	अणु"", 0पूर्ण,
पूर्ण;

अटल व्योम amba_रेजिस्टर_dummy_clk(व्योम)
अणु
	अटल काष्ठा clk *amba_dummy_clk;

	/* If घड़ी alपढ़ोy रेजिस्टरed */
	अगर (amba_dummy_clk)
		वापस;

	amba_dummy_clk = clk_रेजिस्टर_fixed_rate(शून्य, "apb_pclk", शून्य, 0, 0);
	clk_रेजिस्टर_clkdev(amba_dummy_clk, "apb_pclk", शून्य);
पूर्ण

अटल पूर्णांक amba_handler_attach(काष्ठा acpi_device *adev,
				स्थिर काष्ठा acpi_device_id *id)
अणु
	काष्ठा amba_device *dev;
	काष्ठा resource_entry *rentry;
	काष्ठा list_head resource_list;
	bool address_found = false;
	पूर्णांक irq_no = 0;
	पूर्णांक ret;

	/* If the ACPI node alपढ़ोy has a physical device attached, skip it. */
	अगर (adev->physical_node_count)
		वापस 0;

	dev = amba_device_alloc(dev_name(&adev->dev), 0, 0);
	अगर (!dev) अणु
		dev_err(&adev->dev, "%s(): amba_device_alloc() failed\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list, शून्य, शून्य);
	अगर (ret < 0)
		जाओ err_मुक्त;

	list_क्रम_each_entry(rentry, &resource_list, node) अणु
		चयन (resource_type(rentry->res)) अणु
		हाल IORESOURCE_MEM:
			अगर (!address_found) अणु
				dev->res = *rentry->res;
				address_found = true;
			पूर्ण
			अवरोध;
		हाल IORESOURCE_IRQ:
			अगर (irq_no < AMBA_NR_IRQS)
				dev->irq[irq_no++] = rentry->res->start;
			अवरोध;
		शेष:
			dev_warn(&adev->dev, "Invalid resource\n");
			अवरोध;
		पूर्ण
	पूर्ण

	acpi_dev_मुक्त_resource_list(&resource_list);

	/*
	 * If the ACPI node has a parent and that parent has a physical device
	 * attached to it, that physical device should be the parent of
	 * the amba device we are about to create.
	 */
	अगर (adev->parent)
		dev->dev.parent = acpi_get_first_physical_node(adev->parent);

	ACPI_COMPANION_SET(&dev->dev, adev);

	ret = amba_device_add(dev, &iomem_resource);
	अगर (ret) अणु
		dev_err(&adev->dev, "%s(): amba_device_add() failed (%d)\n",
		       __func__, ret);
		जाओ err_मुक्त;
	पूर्ण

	वापस 1;

err_मुक्त:
	amba_device_put(dev);
	वापस ret;
पूर्ण

अटल काष्ठा acpi_scan_handler amba_handler = अणु
	.ids = amba_id_list,
	.attach = amba_handler_attach,
पूर्ण;

व्योम __init acpi_amba_init(व्योम)
अणु
	amba_रेजिस्टर_dummy_clk();
	acpi_scan_add_handler(&amba_handler);
पूर्ण
