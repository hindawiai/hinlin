<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI watchकरोg table parsing support.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: watchdog: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "internal.h"

#अगर_घोषित CONFIG_RTC_MC146818_LIB
#समावेश <linux/mc146818rtc.h>

/*
 * There are several प्रणालीs where the WDAT table is accessing RTC SRAM to
 * store persistent inक्रमmation. This करोes not work well with the Linux RTC
 * driver so on those प्रणालीs we skip WDAT driver and prefer iTCO_wdt
 * instead.
 *
 * See also https://bugzilla.kernel.org/show_bug.cgi?id=199033.
 */
अटल bool acpi_watchकरोg_uses_rtc(स्थिर काष्ठा acpi_table_wdat *wdat)
अणु
	स्थिर काष्ठा acpi_wdat_entry *entries;
	पूर्णांक i;

	entries = (काष्ठा acpi_wdat_entry *)(wdat + 1);
	क्रम (i = 0; i < wdat->entries; i++) अणु
		स्थिर काष्ठा acpi_generic_address *gas;

		gas = &entries[i].रेजिस्टर_region;
		अगर (gas->space_id == ACPI_ADR_SPACE_SYSTEM_IO) अणु
			चयन (gas->address) अणु
			हाल RTC_PORT(0):
			हाल RTC_PORT(1):
			हाल RTC_PORT(2):
			हाल RTC_PORT(3):
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
#अन्यथा
अटल bool acpi_watchकरोg_uses_rtc(स्थिर काष्ठा acpi_table_wdat *wdat)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल bool acpi_no_watchकरोg;

अटल स्थिर काष्ठा acpi_table_wdat *acpi_watchकरोg_get_wdat(व्योम)
अणु
	स्थिर काष्ठा acpi_table_wdat *wdat = शून्य;
	acpi_status status;

	अगर (acpi_disabled || acpi_no_watchकरोg)
		वापस शून्य;

	status = acpi_get_table(ACPI_SIG_WDAT, 0,
				(काष्ठा acpi_table_header **)&wdat);
	अगर (ACPI_FAILURE(status)) अणु
		/* It is fine अगर there is no WDAT */
		वापस शून्य;
	पूर्ण

	अगर (acpi_watchकरोg_uses_rtc(wdat)) अणु
		acpi_put_table((काष्ठा acpi_table_header *)wdat);
		pr_info("Skipping WDAT on this system because it uses RTC SRAM\n");
		वापस शून्य;
	पूर्ण

	वापस wdat;
पूर्ण

/**
 * Returns true अगर this प्रणाली should prefer ACPI based watchकरोg instead of
 * the native one (which are typically the same hardware).
 */
bool acpi_has_watchकरोg(व्योम)
अणु
	वापस !!acpi_watchकरोg_get_wdat();
पूर्ण
EXPORT_SYMBOL_GPL(acpi_has_watchकरोg);

/* ACPI watchकरोg can be disabled on boot command line */
अटल पूर्णांक __init disable_acpi_watchकरोg(अक्षर *str)
अणु
	acpi_no_watchकरोg = true;
	वापस 1;
पूर्ण
__setup("acpi_no_watchdog", disable_acpi_watchकरोg);

व्योम __init acpi_watchकरोg_init(व्योम)
अणु
	स्थिर काष्ठा acpi_wdat_entry *entries;
	स्थिर काष्ठा acpi_table_wdat *wdat;
	काष्ठा list_head resource_list;
	काष्ठा resource_entry *rentry;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource *resources;
	माप_प्रकार nresources = 0;
	पूर्णांक i;

	wdat = acpi_watchकरोg_get_wdat();
	अगर (!wdat) अणु
		/* It is fine अगर there is no WDAT */
		वापस;
	पूर्ण

	/* Watchकरोg disabled by BIOS */
	अगर (!(wdat->flags & ACPI_WDAT_ENABLED))
		जाओ fail_put_wdat;

	/* Skip legacy PCI WDT devices */
	अगर (wdat->pci_segment != 0xff || wdat->pci_bus != 0xff ||
	    wdat->pci_device != 0xff || wdat->pci_function != 0xff)
		जाओ fail_put_wdat;

	INIT_LIST_HEAD(&resource_list);

	entries = (काष्ठा acpi_wdat_entry *)(wdat + 1);
	क्रम (i = 0; i < wdat->entries; i++) अणु
		स्थिर काष्ठा acpi_generic_address *gas;
		काष्ठा resource_entry *rentry;
		काष्ठा resource res = अणुपूर्ण;
		bool found;

		gas = &entries[i].रेजिस्टर_region;

		res.start = gas->address;
		res.end = res.start + ACPI_ACCESS_BYTE_WIDTH(gas->access_width) - 1;
		अगर (gas->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
			res.flags = IORESOURCE_MEM;
		पूर्ण अन्यथा अगर (gas->space_id == ACPI_ADR_SPACE_SYSTEM_IO) अणु
			res.flags = IORESOURCE_IO;
		पूर्ण अन्यथा अणु
			pr_warn("Unsupported address space: %u\n",
				gas->space_id);
			जाओ fail_मुक्त_resource_list;
		पूर्ण

		found = false;
		resource_list_क्रम_each_entry(rentry, &resource_list) अणु
			अगर (rentry->res->flags == res.flags &&
			    resource_जोड़(rentry->res, &res, rentry->res)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			rentry = resource_list_create_entry(शून्य, 0);
			अगर (!rentry)
				जाओ fail_मुक्त_resource_list;

			*rentry->res = res;
			resource_list_add_tail(rentry, &resource_list);
			nresources++;
		पूर्ण
	पूर्ण

	resources = kसुस्मृति(nresources, माप(*resources), GFP_KERNEL);
	अगर (!resources)
		जाओ fail_मुक्त_resource_list;

	i = 0;
	resource_list_क्रम_each_entry(rentry, &resource_list)
		resources[i++] = *rentry->res;

	pdev = platक्रमm_device_रेजिस्टर_simple("wdat_wdt", PLATFORM_DEVID_NONE,
					       resources, nresources);
	अगर (IS_ERR(pdev))
		pr_err("Device creation failed: %ld\n", PTR_ERR(pdev));

	kमुक्त(resources);

fail_मुक्त_resource_list:
	resource_list_मुक्त(&resource_list);
fail_put_wdat:
	acpi_put_table((काष्ठा acpi_table_header *)wdat);
पूर्ण
