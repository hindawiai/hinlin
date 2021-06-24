<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ICS backend क्रम OPAL managed पूर्णांकerrupts.
 *
 * Copyright 2011 IBM Corp.
 */

#अघोषित DEBUG

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/msi.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/firmware.h>

अटल पूर्णांक ics_opal_mangle_server(पूर्णांक server)
अणु
	/* No link क्रम now */
	वापस server << 2;
पूर्ण

अटल पूर्णांक ics_opal_unmangle_server(पूर्णांक server)
अणु
	/* No link क्रम now */
	वापस server >> 2;
पूर्ण

अटल व्योम ics_opal_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	पूर्णांक64_t rc;
	पूर्णांक server;

	pr_devel("ics-hal: unmask virq %d [hw 0x%x]\n", d->irq, hw_irq);

	अगर (hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS)
		वापस;

	server = xics_get_irq_server(d->irq, irq_data_get_affinity_mask(d), 0);
	server = ics_opal_mangle_server(server);

	rc = opal_set_xive(hw_irq, server, DEFAULT_PRIORITY);
	अगर (rc != OPAL_SUCCESS)
		pr_err("%s: opal_set_xive(irq=%d [hw 0x%x] server=%x)"
		       " error %lld\n",
		       __func__, d->irq, hw_irq, server, rc);
पूर्ण

अटल अचिन्हित पूर्णांक ics_opal_startup(काष्ठा irq_data *d)
अणु
#अगर_घोषित CONFIG_PCI_MSI
	/*
	 * The generic MSI code वापसs with the पूर्णांकerrupt disabled on the
	 * card, using the MSI mask bits. Firmware करोesn't appear to unmask
	 * at that level, so we करो it here by hand.
	 */
	अगर (irq_data_get_msi_desc(d))
		pci_msi_unmask_irq(d);
#पूर्ण_अगर

	/* unmask it */
	ics_opal_unmask_irq(d);
	वापस 0;
पूर्ण

अटल व्योम ics_opal_mask_real_irq(अचिन्हित पूर्णांक hw_irq)
अणु
	पूर्णांक server = ics_opal_mangle_server(xics_शेष_server);
	पूर्णांक64_t rc;

	अगर (hw_irq == XICS_IPI)
		वापस;

	/* Have to set XIVE to 0xff to be able to हटाओ a slot */
	rc = opal_set_xive(hw_irq, server, 0xff);
	अगर (rc != OPAL_SUCCESS)
		pr_err("%s: opal_set_xive(0xff) irq=%u returned %lld\n",
		       __func__, hw_irq, rc);
पूर्ण

अटल व्योम ics_opal_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);

	pr_devel("ics-hal: mask virq %d [hw 0x%x]\n", d->irq, hw_irq);

	अगर (hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS)
		वापस;
	ics_opal_mask_real_irq(hw_irq);
पूर्ण

अटल पूर्णांक ics_opal_set_affinity(काष्ठा irq_data *d,
				 स्थिर काष्ठा cpumask *cpumask,
				 bool क्रमce)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	__be16 oserver;
	पूर्णांक16_t server;
	पूर्णांक8_t priority;
	पूर्णांक64_t rc;
	पूर्णांक wanted_server;

	अगर (hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS)
		वापस -1;

	rc = opal_get_xive(hw_irq, &oserver, &priority);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_err("%s: opal_get_xive(irq=%d [hw 0x%x]) error %lld\n",
		       __func__, d->irq, hw_irq, rc);
		वापस -1;
	पूर्ण
	server = be16_to_cpu(oserver);

	wanted_server = xics_get_irq_server(d->irq, cpumask, 1);
	अगर (wanted_server < 0) अणु
		pr_warn("%s: No online cpus in the mask %*pb for irq %d\n",
			__func__, cpumask_pr_args(cpumask), d->irq);
		वापस -1;
	पूर्ण
	server = ics_opal_mangle_server(wanted_server);

	pr_devel("ics-hal: set-affinity irq %d [hw 0x%x] server: 0x%x/0x%x\n",
		 d->irq, hw_irq, wanted_server, server);

	rc = opal_set_xive(hw_irq, server, priority);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_err("%s: opal_set_xive(irq=%d [hw 0x%x] server=%x)"
		       " error %lld\n",
		       __func__, d->irq, hw_irq, server, rc);
		वापस -1;
	पूर्ण
	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल काष्ठा irq_chip ics_opal_irq_chip = अणु
	.name = "OPAL ICS",
	.irq_startup = ics_opal_startup,
	.irq_mask = ics_opal_mask_irq,
	.irq_unmask = ics_opal_unmask_irq,
	.irq_eoi = शून्य, /* Patched at init समय */
	.irq_set_affinity = ics_opal_set_affinity,
	.irq_set_type = xics_set_irq_type,
	.irq_retrigger = xics_retrigger,
पूर्ण;

अटल पूर्णांक ics_opal_map(काष्ठा ics *ics, अचिन्हित पूर्णांक virq);
अटल व्योम ics_opal_mask_unknown(काष्ठा ics *ics, अचिन्हित दीर्घ vec);
अटल दीर्घ ics_opal_get_server(काष्ठा ics *ics, अचिन्हित दीर्घ vec);

अटल पूर्णांक ics_opal_host_match(काष्ठा ics *ics, काष्ठा device_node *node)
अणु
	वापस 1;
पूर्ण

/* Only one global & state काष्ठा ics */
अटल काष्ठा ics ics_hal = अणु
	.map		= ics_opal_map,
	.mask_unknown	= ics_opal_mask_unknown,
	.get_server	= ics_opal_get_server,
	.host_match	= ics_opal_host_match,
पूर्ण;

अटल पूर्णांक ics_opal_map(काष्ठा ics *ics, अचिन्हित पूर्णांक virq)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)virq_to_hw(virq);
	पूर्णांक64_t rc;
	__be16 server;
	पूर्णांक8_t priority;

	अगर (WARN_ON(hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS))
		वापस -EINVAL;

	/* Check अगर HAL knows about this पूर्णांकerrupt */
	rc = opal_get_xive(hw_irq, &server, &priority);
	अगर (rc != OPAL_SUCCESS)
		वापस -ENXIO;

	irq_set_chip_and_handler(virq, &ics_opal_irq_chip, handle_fasteoi_irq);
	irq_set_chip_data(virq, &ics_hal);

	वापस 0;
पूर्ण

अटल व्योम ics_opal_mask_unknown(काष्ठा ics *ics, अचिन्हित दीर्घ vec)
अणु
	पूर्णांक64_t rc;
	__be16 server;
	पूर्णांक8_t priority;

	/* Check अगर HAL knows about this पूर्णांकerrupt */
	rc = opal_get_xive(vec, &server, &priority);
	अगर (rc != OPAL_SUCCESS)
		वापस;

	ics_opal_mask_real_irq(vec);
पूर्ण

अटल दीर्घ ics_opal_get_server(काष्ठा ics *ics, अचिन्हित दीर्घ vec)
अणु
	पूर्णांक64_t rc;
	__be16 server;
	पूर्णांक8_t priority;

	/* Check अगर HAL knows about this पूर्णांकerrupt */
	rc = opal_get_xive(vec, &server, &priority);
	अगर (rc != OPAL_SUCCESS)
		वापस -1;
	वापस ics_opal_unmangle_server(be16_to_cpu(server));
पूर्ण

पूर्णांक __init ics_opal_init(व्योम)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_OPAL))
		वापस -ENODEV;

	/* We need to patch our irq chip's EOI to poपूर्णांक to the
	 * right ICP
	 */
	ics_opal_irq_chip.irq_eoi = icp_ops->eoi;

	/* Register ourselves */
	xics_रेजिस्टर_ics(&ics_hal);

	pr_info("ICS OPAL backend registered\n");

	वापस 0;
पूर्ण
