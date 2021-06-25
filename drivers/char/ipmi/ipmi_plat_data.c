<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Add an IPMI platक्रमm device.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश "ipmi_plat_data.h"
#समावेश "ipmi_si.h"

काष्ठा platक्रमm_device *ipmi_platक्रमm_add(स्थिर अक्षर *name, अचिन्हित पूर्णांक inst,
					  काष्ठा ipmi_plat_data *p)
अणु
	काष्ठा platक्रमm_device *pdev;
	अचिन्हित पूर्णांक num_r = 1, size = 0, pidx = 0;
	काष्ठा resource r[4];
	काष्ठा property_entry pr[6];
	u32 flags;
	पूर्णांक rv;

	स_रखो(pr, 0, माप(pr));
	स_रखो(r, 0, माप(r));

	अगर (p->अगरtype == IPMI_PLAT_IF_SI) अणु
		अगर (p->type == SI_BT)
			size = 3;
		अन्यथा अगर (p->type != SI_TYPE_INVALID)
			size = 2;

		अगर (p->regsize == 0)
			p->regsize = DEFAULT_REGSIZE;
		अगर (p->regspacing == 0)
			p->regspacing = p->regsize;

		pr[pidx++] = PROPERTY_ENTRY_U8("ipmi-type", p->type);
	पूर्ण अन्यथा अगर (p->अगरtype == IPMI_PLAT_IF_SSIF) अणु
		pr[pidx++] = PROPERTY_ENTRY_U16("i2c-addr", p->addr);
	पूर्ण

	अगर (p->slave_addr)
		pr[pidx++] = PROPERTY_ENTRY_U8("slave-addr", p->slave_addr);
	pr[pidx++] = PROPERTY_ENTRY_U8("addr-source", p->addr_source);
	अगर (p->regshअगरt)
		pr[pidx++] = PROPERTY_ENTRY_U8("reg-shift", p->regshअगरt);
	pr[pidx++] = PROPERTY_ENTRY_U8("reg-size", p->regsize);
	/* Last entry must be left शून्य to terminate it. */

	pdev = platक्रमm_device_alloc(name, inst);
	अगर (!pdev) अणु
		pr_err("Error allocating IPMI platform device %s.%d\n",
		       name, inst);
		वापस शून्य;
	पूर्ण

	अगर (size == 0)
		/* An invalid or SSIF पूर्णांकerface, no resources. */
		जाओ add_properties;

	/*
	 * Register spacing is derived from the resources in
	 * the IPMI platक्रमm code.
	 */

	अगर (p->space == IPMI_IO_ADDR_SPACE)
		flags = IORESOURCE_IO;
	अन्यथा
		flags = IORESOURCE_MEM;

	r[0].start = p->addr;
	r[0].end = r[0].start + p->regsize - 1;
	r[0].name = "IPMI Address 1";
	r[0].flags = flags;

	अगर (size > 1) अणु
		r[1].start = r[0].start + p->regspacing;
		r[1].end = r[1].start + p->regsize - 1;
		r[1].name = "IPMI Address 2";
		r[1].flags = flags;
		num_r++;
	पूर्ण

	अगर (size > 2) अणु
		r[2].start = r[1].start + p->regspacing;
		r[2].end = r[2].start + p->regsize - 1;
		r[2].name = "IPMI Address 3";
		r[2].flags = flags;
		num_r++;
	पूर्ण

	अगर (p->irq) अणु
		r[num_r].start = p->irq;
		r[num_r].end = p->irq;
		r[num_r].name = "IPMI IRQ";
		r[num_r].flags = IORESOURCE_IRQ;
		num_r++;
	पूर्ण

	rv = platक्रमm_device_add_resources(pdev, r, num_r);
	अगर (rv) अणु
		dev_err(&pdev->dev,
			"Unable to add hard-code resources: %d\n", rv);
		जाओ err;
	पूर्ण
 add_properties:
	rv = device_create_managed_software_node(&pdev->dev, pr, शून्य);
	अगर (rv) अणु
		dev_err(&pdev->dev,
			"Unable to add hard-code properties: %d\n", rv);
		जाओ err;
	पूर्ण

	rv = platक्रमm_device_add(pdev);
	अगर (rv) अणु
		dev_err(&pdev->dev,
			"Unable to add hard-code device: %d\n", rv);
		जाओ err;
	पूर्ण
	वापस pdev;

err:
	platक्रमm_device_put(pdev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(ipmi_platक्रमm_add);
