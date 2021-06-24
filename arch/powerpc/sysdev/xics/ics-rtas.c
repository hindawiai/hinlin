<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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
#समावेश <यंत्र/rtas.h>

/* RTAS service tokens */
अटल पूर्णांक ibm_get_xive;
अटल पूर्णांक ibm_set_xive;
अटल पूर्णांक ibm_पूर्णांक_on;
अटल पूर्णांक ibm_पूर्णांक_off;

अटल पूर्णांक ics_rtas_map(काष्ठा ics *ics, अचिन्हित पूर्णांक virq);
अटल व्योम ics_rtas_mask_unknown(काष्ठा ics *ics, अचिन्हित दीर्घ vec);
अटल दीर्घ ics_rtas_get_server(काष्ठा ics *ics, अचिन्हित दीर्घ vec);
अटल पूर्णांक ics_rtas_host_match(काष्ठा ics *ics, काष्ठा device_node *node);

/* Only one global & state काष्ठा ics */
अटल काष्ठा ics ics_rtas = अणु
	.map		= ics_rtas_map,
	.mask_unknown	= ics_rtas_mask_unknown,
	.get_server	= ics_rtas_get_server,
	.host_match	= ics_rtas_host_match,
पूर्ण;

अटल व्योम ics_rtas_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	पूर्णांक call_status;
	पूर्णांक server;

	pr_devel("xics: unmask virq %d [hw 0x%x]\n", d->irq, hw_irq);

	अगर (hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS)
		वापस;

	server = xics_get_irq_server(d->irq, irq_data_get_affinity_mask(d), 0);

	call_status = rtas_call_reentrant(ibm_set_xive, 3, 1, शून्य, hw_irq,
					  server, DEFAULT_PRIORITY);
	अगर (call_status != 0) अणु
		prपूर्णांकk(KERN_ERR
			"%s: ibm_set_xive irq %u server %x returned %d\n",
			__func__, hw_irq, server, call_status);
		वापस;
	पूर्ण

	/* Now unmask the पूर्णांकerrupt (often a no-op) */
	call_status = rtas_call_reentrant(ibm_पूर्णांक_on, 1, 1, शून्य, hw_irq);
	अगर (call_status != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: ibm_int_on irq=%u returned %d\n",
			__func__, hw_irq, call_status);
		वापस;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ics_rtas_startup(काष्ठा irq_data *d)
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
	ics_rtas_unmask_irq(d);
	वापस 0;
पूर्ण

अटल व्योम ics_rtas_mask_real_irq(अचिन्हित पूर्णांक hw_irq)
अणु
	पूर्णांक call_status;

	अगर (hw_irq == XICS_IPI)
		वापस;

	call_status = rtas_call_reentrant(ibm_पूर्णांक_off, 1, 1, शून्य, hw_irq);
	अगर (call_status != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: ibm_int_off irq=%u returned %d\n",
			__func__, hw_irq, call_status);
		वापस;
	पूर्ण

	/* Have to set XIVE to 0xff to be able to हटाओ a slot */
	call_status = rtas_call_reentrant(ibm_set_xive, 3, 1, शून्य, hw_irq,
					  xics_शेष_server, 0xff);
	अगर (call_status != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: ibm_set_xive(0xff) irq=%u returned %d\n",
			__func__, hw_irq, call_status);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम ics_rtas_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);

	pr_devel("xics: mask virq %d [hw 0x%x]\n", d->irq, hw_irq);

	अगर (hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS)
		वापस;
	ics_rtas_mask_real_irq(hw_irq);
पूर्ण

अटल पूर्णांक ics_rtas_set_affinity(काष्ठा irq_data *d,
				 स्थिर काष्ठा cpumask *cpumask,
				 bool क्रमce)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	पूर्णांक status;
	पूर्णांक xics_status[2];
	पूर्णांक irq_server;

	अगर (hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS)
		वापस -1;

	status = rtas_call_reentrant(ibm_get_xive, 1, 3, xics_status, hw_irq);

	अगर (status) अणु
		prपूर्णांकk(KERN_ERR "%s: ibm,get-xive irq=%u returns %d\n",
			__func__, hw_irq, status);
		वापस -1;
	पूर्ण

	irq_server = xics_get_irq_server(d->irq, cpumask, 1);
	अगर (irq_server == -1) अणु
		pr_warn("%s: No online cpus in the mask %*pb for irq %d\n",
			__func__, cpumask_pr_args(cpumask), d->irq);
		वापस -1;
	पूर्ण

	status = rtas_call_reentrant(ibm_set_xive, 3, 1, शून्य,
				     hw_irq, irq_server, xics_status[1]);

	अगर (status) अणु
		prपूर्णांकk(KERN_ERR "%s: ibm,set-xive irq=%u returns %d\n",
			__func__, hw_irq, status);
		वापस -1;
	पूर्ण

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल काष्ठा irq_chip ics_rtas_irq_chip = अणु
	.name = "XICS",
	.irq_startup = ics_rtas_startup,
	.irq_mask = ics_rtas_mask_irq,
	.irq_unmask = ics_rtas_unmask_irq,
	.irq_eoi = शून्य, /* Patched at init समय */
	.irq_set_affinity = ics_rtas_set_affinity,
	.irq_set_type = xics_set_irq_type,
	.irq_retrigger = xics_retrigger,
पूर्ण;

अटल पूर्णांक ics_rtas_map(काष्ठा ics *ics, अचिन्हित पूर्णांक virq)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)virq_to_hw(virq);
	पूर्णांक status[2];
	पूर्णांक rc;

	अगर (WARN_ON(hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS))
		वापस -EINVAL;

	/* Check अगर RTAS knows about this पूर्णांकerrupt */
	rc = rtas_call_reentrant(ibm_get_xive, 1, 3, status, hw_irq);
	अगर (rc)
		वापस -ENXIO;

	irq_set_chip_and_handler(virq, &ics_rtas_irq_chip, handle_fasteoi_irq);
	irq_set_chip_data(virq, &ics_rtas);

	वापस 0;
पूर्ण

अटल व्योम ics_rtas_mask_unknown(काष्ठा ics *ics, अचिन्हित दीर्घ vec)
अणु
	ics_rtas_mask_real_irq(vec);
पूर्ण

अटल दीर्घ ics_rtas_get_server(काष्ठा ics *ics, अचिन्हित दीर्घ vec)
अणु
	पूर्णांक rc, status[2];

	rc = rtas_call_reentrant(ibm_get_xive, 1, 3, status, vec);
	अगर (rc)
		वापस -1;
	वापस status[0];
पूर्ण

अटल पूर्णांक ics_rtas_host_match(काष्ठा ics *ics, काष्ठा device_node *node)
अणु
	/* IBM machines have पूर्णांकerrupt parents of various funky types क्रम things
	 * like vdevices, events, etc... The trick we use here is to match
	 * everything here except the legacy 8259 which is compatible "chrp,iic"
	 */
	वापस !of_device_is_compatible(node, "chrp,iic");
पूर्ण

__init पूर्णांक ics_rtas_init(व्योम)
अणु
	ibm_get_xive = rtas_token("ibm,get-xive");
	ibm_set_xive = rtas_token("ibm,set-xive");
	ibm_पूर्णांक_on  = rtas_token("ibm,int-on");
	ibm_पूर्णांक_off = rtas_token("ibm,int-off");

	/* We enable the RTAS "ICS" अगर RTAS is present with the
	 * appropriate tokens
	 */
	अगर (ibm_get_xive == RTAS_UNKNOWN_SERVICE ||
	    ibm_set_xive == RTAS_UNKNOWN_SERVICE)
		वापस -ENODEV;

	/* We need to patch our irq chip's EOI to poपूर्णांक to the
	 * right ICP
	 */
	ics_rtas_irq_chip.irq_eoi = icp_ops->eoi;

	/* Register ourselves */
	xics_रेजिस्टर_ics(&ics_rtas);

	वापस 0;
पूर्ण

