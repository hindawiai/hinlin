<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम घातer management features of the OLPC XO-1 laptop
 *
 * Copyright (C) 2010 Andres Salomon <dilinger@queued.net>
 * Copyright (C) 2010 One Laptop per Child
 * Copyright (C) 2006 Red Hat, Inc.
 * Copyright (C) 2006 Advanced Micro Devices, Inc.
 */

#समावेश <linux/cs5535.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/export.h>
#समावेश <linux/pm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/olpc-ec.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/olpc.h>

#घोषणा DRV_NAME "olpc-xo1-pm"

अटल अचिन्हित दीर्घ acpi_base;
अटल अचिन्हित दीर्घ pms_base;

अटल u16 wakeup_mask = CS5536_PM_PWRBTN;

अटल काष्ठा अणु
	अचिन्हित दीर्घ address;
	अचिन्हित लघु segment;
पूर्ण ofw_bios_entry = अणु 0xF0000 + PAGE_OFFSET, __KERNEL_CS पूर्ण;

/* Set bits in the wakeup mask */
व्योम olpc_xo1_pm_wakeup_set(u16 value)
अणु
	wakeup_mask |= value;
पूर्ण
EXPORT_SYMBOL_GPL(olpc_xo1_pm_wakeup_set);

/* Clear bits in the wakeup mask */
व्योम olpc_xo1_pm_wakeup_clear(u16 value)
अणु
	wakeup_mask &= ~value;
पूर्ण
EXPORT_SYMBOL_GPL(olpc_xo1_pm_wakeup_clear);

अटल पूर्णांक xo1_घातer_state_enter(suspend_state_t pm_state)
अणु
	अचिन्हित दीर्घ saved_sci_mask;

	/* Only STR is supported */
	अगर (pm_state != PM_SUSPEND_MEM)
		वापस -EINVAL;

	/*
	 * Save SCI mask (this माला_लो lost since PM1_EN is used as a mask क्रम
	 * wakeup events, which is not necessarily the same event set)
	 */
	saved_sci_mask = inl(acpi_base + CS5536_PM1_STS);
	saved_sci_mask &= 0xffff0000;

	/* Save CPU state */
	करो_olpc_suspend_lowlevel();

	/* Resume path starts here */

	/* Restore SCI mask (using dword access to CS5536_PM1_EN) */
	outl(saved_sci_mask, acpi_base + CS5536_PM1_STS);

	वापस 0;
पूर्ण

यंत्रlinkage __visible पूर्णांक xo1_करो_sleep(u8 sleep_state)
अणु
	व्योम *pgd_addr = __va(पढ़ो_cr3_pa());

	/* Program wakeup mask (using dword access to CS5536_PM1_EN) */
	outl(wakeup_mask << 16, acpi_base + CS5536_PM1_STS);

	__यंत्र__("movl %0,%%eax" : : "r" (pgd_addr));
	__यंत्र__("call *(%%edi); cld"
		: : "D" (&ofw_bios_entry));
	__यंत्र__("movb $0x34, %al\n\t"
		"outb %al, $0x70\n\t"
		"movb $0x30, %al\n\t"
		"outb %al, $0x71\n\t");
	वापस 0;
पूर्ण

अटल व्योम xo1_घातer_off(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "OLPC XO-1 power off sequence...\n");

	/* Enable all of these controls with 0 delay */
	outl(0x40000000, pms_base + CS5536_PM_SCLK);
	outl(0x40000000, pms_base + CS5536_PM_IN_SLPCTL);
	outl(0x40000000, pms_base + CS5536_PM_WKXD);
	outl(0x40000000, pms_base + CS5536_PM_WKD);

	/* Clear status bits (possibly unnecessary) */
	outl(0x0002ffff, pms_base  + CS5536_PM_SSC);
	outl(0xffffffff, acpi_base + CS5536_PM_GPE0_STS);

	/* Write SLP_EN bit to start the machinery */
	outl(0x00002000, acpi_base + CS5536_PM1_CNT);
पूर्ण

अटल पूर्णांक xo1_घातer_state_valid(suspend_state_t pm_state)
अणु
	/* suspend-to-RAM only */
	वापस pm_state == PM_SUSPEND_MEM;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops xo1_suspend_ops = अणु
	.valid = xo1_घातer_state_valid,
	.enter = xo1_घातer_state_enter,
पूर्ण;

अटल पूर्णांक xo1_pm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;

	/* करोn't run on non-XOs */
	अगर (!machine_is_olpc())
		वापस -ENODEV;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		वापस -EIO;
	पूर्ण
	अगर (म_भेद(pdev->name, "cs5535-pms") == 0)
		pms_base = res->start;
	अन्यथा अगर (म_भेद(pdev->name, "olpc-xo1-pm-acpi") == 0)
		acpi_base = res->start;

	/* If we have both addresses, we can override the घातeroff hook */
	अगर (pms_base && acpi_base) अणु
		suspend_set_ops(&xo1_suspend_ops);
		pm_घातer_off = xo1_घातer_off;
		prपूर्णांकk(KERN_INFO "OLPC XO-1 support registered\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xo1_pm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (म_भेद(pdev->name, "cs5535-pms") == 0)
		pms_base = 0;
	अन्यथा अगर (म_भेद(pdev->name, "olpc-xo1-pm-acpi") == 0)
		acpi_base = 0;

	pm_घातer_off = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cs5535_pms_driver = अणु
	.driver = अणु
		.name = "cs5535-pms",
	पूर्ण,
	.probe = xo1_pm_probe,
	.हटाओ = xo1_pm_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_driver cs5535_acpi_driver = अणु
	.driver = अणु
		.name = "olpc-xo1-pm-acpi",
	पूर्ण,
	.probe = xo1_pm_probe,
	.हटाओ = xo1_pm_हटाओ,
पूर्ण;

अटल पूर्णांक __init xo1_pm_init(व्योम)
अणु
	पूर्णांक r;

	r = platक्रमm_driver_रेजिस्टर(&cs5535_pms_driver);
	अगर (r)
		वापस r;

	r = platक्रमm_driver_रेजिस्टर(&cs5535_acpi_driver);
	अगर (r)
		platक्रमm_driver_unरेजिस्टर(&cs5535_pms_driver);

	वापस r;
पूर्ण
arch_initcall(xo1_pm_init);
