<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Merrअगरield watchकरोg platक्रमm device library file
 *
 * (C) Copyright 2014 Intel Corporation
 * Author: David Cohen <david.a.cohen@linux.पूर्णांकel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/पूर्णांकel-mid_wdt.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/पूर्णांकel-mid.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/hw_irq.h>

#घोषणा TANGIER_EXT_TIMER0_MSI 12

अटल काष्ठा platक्रमm_device wdt_dev = अणु
	.name = "intel_mid_wdt",
	.id = -1,
पूर्ण;

अटल पूर्णांक tangier_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा irq_alloc_info info;
	काष्ठा पूर्णांकel_mid_wdt_pdata *pdata = pdev->dev.platक्रमm_data;
	पूर्णांक gsi = TANGIER_EXT_TIMER0_MSI;
	पूर्णांक irq;

	अगर (!pdata)
		वापस -EINVAL;

	/* IOAPIC builds identity mapping between GSI and IRQ on MID */
	ioapic_set_alloc_attr(&info, cpu_to_node(0), 1, 0);
	irq = mp_map_gsi_to_irq(gsi, IOAPIC_MAP_ALLOC, &info);
	अगर (irq < 0) अणु
		dev_warn(&pdev->dev, "cannot find interrupt %d in ioapic\n", gsi);
		वापस irq;
	पूर्ण

	pdata->irq = irq;
	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_mid_wdt_pdata tangier_pdata = अणु
	.probe = tangier_probe,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_mid_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT_MID, &tangier_pdata),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_mid_wdt(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;

	id = x86_match_cpu(पूर्णांकel_mid_cpu_ids);
	अगर (!id)
		वापस -ENODEV;

	wdt_dev.dev.platक्रमm_data = (काष्ठा पूर्णांकel_mid_wdt_pdata *)id->driver_data;
	वापस platक्रमm_device_रेजिस्टर(&wdt_dev);
पूर्ण
arch_initcall(रेजिस्टर_mid_wdt);

अटल व्योम __निकास unरेजिस्टर_mid_wdt(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(&wdt_dev);
पूर्ण
__निकासcall(unरेजिस्टर_mid_wdt);
