<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2017 Broadcom
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/notअगरier.h>

#अगर_घोषित CONFIG_MIPS
#समावेश <यंत्र/traps.h>
#पूर्ण_अगर

#घोषणा  ARB_ERR_CAP_CLEAR		(1 << 0)
#घोषणा  ARB_ERR_CAP_STATUS_TIMEOUT	(1 << 12)
#घोषणा  ARB_ERR_CAP_STATUS_TEA		(1 << 11)
#घोषणा  ARB_ERR_CAP_STATUS_WRITE	(1 << 1)
#घोषणा  ARB_ERR_CAP_STATUS_VALID	(1 << 0)

#घोषणा  ARB_BP_CAP_CLEAR		(1 << 0)
#घोषणा  ARB_BP_CAP_STATUS_PROT_SHIFT	14
#घोषणा  ARB_BP_CAP_STATUS_TYPE		(1 << 13)
#घोषणा  ARB_BP_CAP_STATUS_RSP_SHIFT	10
#घोषणा  ARB_BP_CAP_STATUS_MASK		GENMASK(1, 0)
#घोषणा  ARB_BP_CAP_STATUS_BS_SHIFT	2
#घोषणा  ARB_BP_CAP_STATUS_WRITE	(1 << 1)
#घोषणा  ARB_BP_CAP_STATUS_VALID	(1 << 0)

क्रमागत अणु
	ARB_TIMER,
	ARB_BP_CAP_CLR,
	ARB_BP_CAP_HI_ADDR,
	ARB_BP_CAP_ADDR,
	ARB_BP_CAP_STATUS,
	ARB_BP_CAP_MASTER,
	ARB_ERR_CAP_CLR,
	ARB_ERR_CAP_HI_ADDR,
	ARB_ERR_CAP_ADDR,
	ARB_ERR_CAP_STATUS,
	ARB_ERR_CAP_MASTER,
पूर्ण;

अटल स्थिर पूर्णांक gisb_offsets_bcm7038[] = अणु
	[ARB_TIMER]		= 0x00c,
	[ARB_BP_CAP_CLR]	= 0x014,
	[ARB_BP_CAP_HI_ADDR]	= -1,
	[ARB_BP_CAP_ADDR]	= 0x0b8,
	[ARB_BP_CAP_STATUS]	= 0x0c0,
	[ARB_BP_CAP_MASTER]	= -1,
	[ARB_ERR_CAP_CLR]	= 0x0c4,
	[ARB_ERR_CAP_HI_ADDR]	= -1,
	[ARB_ERR_CAP_ADDR]	= 0x0c8,
	[ARB_ERR_CAP_STATUS]	= 0x0d0,
	[ARB_ERR_CAP_MASTER]	= -1,
पूर्ण;

अटल स्थिर पूर्णांक gisb_offsets_bcm7278[] = अणु
	[ARB_TIMER]		= 0x008,
	[ARB_BP_CAP_CLR]	= 0x01c,
	[ARB_BP_CAP_HI_ADDR]	= -1,
	[ARB_BP_CAP_ADDR]	= 0x220,
	[ARB_BP_CAP_STATUS]	= 0x230,
	[ARB_BP_CAP_MASTER]	= 0x234,
	[ARB_ERR_CAP_CLR]	= 0x7f8,
	[ARB_ERR_CAP_HI_ADDR]	= -1,
	[ARB_ERR_CAP_ADDR]	= 0x7e0,
	[ARB_ERR_CAP_STATUS]	= 0x7f0,
	[ARB_ERR_CAP_MASTER]	= 0x7f4,
पूर्ण;

अटल स्थिर पूर्णांक gisb_offsets_bcm7400[] = अणु
	[ARB_TIMER]		= 0x00c,
	[ARB_BP_CAP_CLR]	= 0x014,
	[ARB_BP_CAP_HI_ADDR]	= -1,
	[ARB_BP_CAP_ADDR]	= 0x0b8,
	[ARB_BP_CAP_STATUS]	= 0x0c0,
	[ARB_BP_CAP_MASTER]	= 0x0c4,
	[ARB_ERR_CAP_CLR]	= 0x0c8,
	[ARB_ERR_CAP_HI_ADDR]	= -1,
	[ARB_ERR_CAP_ADDR]	= 0x0cc,
	[ARB_ERR_CAP_STATUS]	= 0x0d4,
	[ARB_ERR_CAP_MASTER]	= 0x0d8,
पूर्ण;

अटल स्थिर पूर्णांक gisb_offsets_bcm7435[] = अणु
	[ARB_TIMER]		= 0x00c,
	[ARB_BP_CAP_CLR]	= 0x014,
	[ARB_BP_CAP_HI_ADDR]	= -1,
	[ARB_BP_CAP_ADDR]	= 0x158,
	[ARB_BP_CAP_STATUS]	= 0x160,
	[ARB_BP_CAP_MASTER]	= 0x164,
	[ARB_ERR_CAP_CLR]	= 0x168,
	[ARB_ERR_CAP_HI_ADDR]	= -1,
	[ARB_ERR_CAP_ADDR]	= 0x16c,
	[ARB_ERR_CAP_STATUS]	= 0x174,
	[ARB_ERR_CAP_MASTER]	= 0x178,
पूर्ण;

अटल स्थिर पूर्णांक gisb_offsets_bcm7445[] = अणु
	[ARB_TIMER]		= 0x008,
	[ARB_BP_CAP_CLR]	= 0x010,
	[ARB_BP_CAP_HI_ADDR]	= -1,
	[ARB_BP_CAP_ADDR]	= 0x1d8,
	[ARB_BP_CAP_STATUS]	= 0x1e0,
	[ARB_BP_CAP_MASTER]	= 0x1e4,
	[ARB_ERR_CAP_CLR]	= 0x7e4,
	[ARB_ERR_CAP_HI_ADDR]	= 0x7e8,
	[ARB_ERR_CAP_ADDR]	= 0x7ec,
	[ARB_ERR_CAP_STATUS]	= 0x7f4,
	[ARB_ERR_CAP_MASTER]	= 0x7f8,
पूर्ण;

काष्ठा brcmstb_gisb_arb_device अणु
	व्योम __iomem	*base;
	स्थिर पूर्णांक	*gisb_offsets;
	bool		big_endian;
	काष्ठा mutex	lock;
	काष्ठा list_head next;
	u32 valid_mask;
	स्थिर अक्षर *master_names[माप(u32) * BITS_PER_BYTE];
	u32 saved_समयout;
पूर्ण;

अटल LIST_HEAD(brcmstb_gisb_arb_device_list);

अटल u32 gisb_पढ़ो(काष्ठा brcmstb_gisb_arb_device *gdev, पूर्णांक reg)
अणु
	पूर्णांक offset = gdev->gisb_offsets[reg];

	अगर (offset < 0) अणु
		/* वापस 1 अगर the hardware करोesn't have ARB_ERR_CAP_MASTER */
		अगर (reg == ARB_ERR_CAP_MASTER)
			वापस 1;
		अन्यथा
			वापस 0;
	पूर्ण

	अगर (gdev->big_endian)
		वापस ioपढ़ो32be(gdev->base + offset);
	अन्यथा
		वापस ioपढ़ो32(gdev->base + offset);
पूर्ण

अटल u64 gisb_पढ़ो_address(काष्ठा brcmstb_gisb_arb_device *gdev)
अणु
	u64 value;

	value = gisb_पढ़ो(gdev, ARB_ERR_CAP_ADDR);
	value |= (u64)gisb_पढ़ो(gdev, ARB_ERR_CAP_HI_ADDR) << 32;

	वापस value;
पूर्ण

अटल u64 gisb_पढ़ो_bp_address(काष्ठा brcmstb_gisb_arb_device *gdev)
अणु
	u64 value;

	value = gisb_पढ़ो(gdev, ARB_BP_CAP_ADDR);
	value |= (u64)gisb_पढ़ो(gdev, ARB_BP_CAP_HI_ADDR) << 32;

	वापस value;
पूर्ण

अटल व्योम gisb_ग_लिखो(काष्ठा brcmstb_gisb_arb_device *gdev, u32 val, पूर्णांक reg)
अणु
	पूर्णांक offset = gdev->gisb_offsets[reg];

	अगर (offset == -1)
		वापस;

	अगर (gdev->big_endian)
		ioग_लिखो32be(val, gdev->base + offset);
	अन्यथा
		ioग_लिखो32(val, gdev->base + offset);
पूर्ण

अटल sमाप_प्रकार gisb_arb_get_समयout(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा brcmstb_gisb_arb_device *gdev = dev_get_drvdata(dev);
	u32 समयout;

	mutex_lock(&gdev->lock);
	समयout = gisb_पढ़ो(gdev, ARB_TIMER);
	mutex_unlock(&gdev->lock);

	वापस प्र_लिखो(buf, "%d", समयout);
पूर्ण

अटल sमाप_प्रकार gisb_arb_set_समयout(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा brcmstb_gisb_arb_device *gdev = dev_get_drvdata(dev);
	पूर्णांक val, ret;

	ret = kstrtoपूर्णांक(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val == 0 || val >= 0xffffffff)
		वापस -EINVAL;

	mutex_lock(&gdev->lock);
	gisb_ग_लिखो(gdev, val, ARB_TIMER);
	mutex_unlock(&gdev->lock);

	वापस count;
पूर्ण

अटल स्थिर अक्षर *
brcmstb_gisb_master_to_str(काष्ठा brcmstb_gisb_arb_device *gdev,
						u32 masters)
अणु
	u32 mask = gdev->valid_mask & masters;

	अगर (hweight_दीर्घ(mask) != 1)
		वापस शून्य;

	वापस gdev->master_names[ffs(mask) - 1];
पूर्ण

अटल पूर्णांक brcmstb_gisb_arb_decode_addr(काष्ठा brcmstb_gisb_arb_device *gdev,
					स्थिर अक्षर *reason)
अणु
	u32 cap_status;
	u64 arb_addr;
	u32 master;
	स्थिर अक्षर *m_name;
	अक्षर m_fmt[11];

	cap_status = gisb_पढ़ो(gdev, ARB_ERR_CAP_STATUS);

	/* Invalid captured address, bail out */
	अगर (!(cap_status & ARB_ERR_CAP_STATUS_VALID))
		वापस 1;

	/* Read the address and master */
	arb_addr = gisb_पढ़ो_address(gdev);
	master = gisb_पढ़ो(gdev, ARB_ERR_CAP_MASTER);

	m_name = brcmstb_gisb_master_to_str(gdev, master);
	अगर (!m_name) अणु
		snम_लिखो(m_fmt, माप(m_fmt), "0x%08x", master);
		m_name = m_fmt;
	पूर्ण

	pr_crit("GISB: %s at 0x%llx [%c %s], core: %s\n",
		reason, arb_addr,
		cap_status & ARB_ERR_CAP_STATUS_WRITE ? 'W' : 'R',
		cap_status & ARB_ERR_CAP_STATUS_TIMEOUT ? "timeout" : "",
		m_name);

	/* clear the GISB error */
	gisb_ग_लिखो(gdev, ARB_ERR_CAP_CLEAR, ARB_ERR_CAP_CLR);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MIPS
अटल पूर्णांक brcmstb_bus_error_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	पूर्णांक ret = 0;
	काष्ठा brcmstb_gisb_arb_device *gdev;
	u32 cap_status;

	list_क्रम_each_entry(gdev, &brcmstb_gisb_arb_device_list, next) अणु
		cap_status = gisb_पढ़ो(gdev, ARB_ERR_CAP_STATUS);

		/* Invalid captured address, bail out */
		अगर (!(cap_status & ARB_ERR_CAP_STATUS_VALID)) अणु
			is_fixup = 1;
			जाओ out;
		पूर्ण

		ret |= brcmstb_gisb_arb_decode_addr(gdev, "bus error");
	पूर्ण
out:
	वापस is_fixup ? MIPS_BE_FIXUP : MIPS_BE_FATAL;
पूर्ण
#पूर्ण_अगर

अटल irqवापस_t brcmstb_gisb_समयout_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	brcmstb_gisb_arb_decode_addr(dev_id, "timeout");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t brcmstb_gisb_tea_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	brcmstb_gisb_arb_decode_addr(dev_id, "target abort");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t brcmstb_gisb_bp_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा brcmstb_gisb_arb_device *gdev = dev_id;
	स्थिर अक्षर *m_name;
	u32 bp_status;
	u64 arb_addr;
	u32 master;
	अक्षर m_fmt[11];

	bp_status = gisb_पढ़ो(gdev, ARB_BP_CAP_STATUS);

	/* Invalid captured address, bail out */
	अगर (!(bp_status & ARB_BP_CAP_STATUS_VALID))
		वापस IRQ_HANDLED;

	/* Read the address and master */
	arb_addr = gisb_पढ़ो_bp_address(gdev);
	master = gisb_पढ़ो(gdev, ARB_BP_CAP_MASTER);

	m_name = brcmstb_gisb_master_to_str(gdev, master);
	अगर (!m_name) अणु
		snम_लिखो(m_fmt, माप(m_fmt), "0x%08x", master);
		m_name = m_fmt;
	पूर्ण

	pr_crit("GISB: breakpoint at 0x%llx [%c], core: %s\n",
		arb_addr, bp_status & ARB_BP_CAP_STATUS_WRITE ? 'W' : 'R',
		m_name);

	/* clear the GISB error */
	gisb_ग_लिखो(gdev, ARB_ERR_CAP_CLEAR, ARB_ERR_CAP_CLR);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Dump out gisb errors on die or panic.
 */
अटल पूर्णांक dump_gisb_error(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ v,
			   व्योम *p);

अटल काष्ठा notअगरier_block gisb_die_notअगरier = अणु
	.notअगरier_call = dump_gisb_error,
पूर्ण;

अटल काष्ठा notअगरier_block gisb_panic_notअगरier = अणु
	.notअगरier_call = dump_gisb_error,
पूर्ण;

अटल पूर्णांक dump_gisb_error(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ v,
			   व्योम *p)
अणु
	काष्ठा brcmstb_gisb_arb_device *gdev;
	स्थिर अक्षर *reason = "panic";

	अगर (self == &gisb_die_notअगरier)
		reason = "die";

	/* iterate over each GISB arb रेजिस्टरed handlers */
	list_क्रम_each_entry(gdev, &brcmstb_gisb_arb_device_list, next)
		brcmstb_gisb_arb_decode_addr(gdev, reason);

	वापस NOTIFY_DONE;
पूर्ण

अटल DEVICE_ATTR(gisb_arb_समयout, S_IWUSR | S_IRUGO,
		gisb_arb_get_समयout, gisb_arb_set_समयout);

अटल काष्ठा attribute *gisb_arb_sysfs_attrs[] = अणु
	&dev_attr_gisb_arb_समयout.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group gisb_arb_sysfs_attr_group = अणु
	.attrs = gisb_arb_sysfs_attrs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id brcmstb_gisb_arb_of_match[] = अणु
	अणु .compatible = "brcm,gisb-arb",         .data = gisb_offsets_bcm7445 पूर्ण,
	अणु .compatible = "brcm,bcm7445-gisb-arb", .data = gisb_offsets_bcm7445 पूर्ण,
	अणु .compatible = "brcm,bcm7435-gisb-arb", .data = gisb_offsets_bcm7435 पूर्ण,
	अणु .compatible = "brcm,bcm7400-gisb-arb", .data = gisb_offsets_bcm7400 पूर्ण,
	अणु .compatible = "brcm,bcm7278-gisb-arb", .data = gisb_offsets_bcm7278 पूर्ण,
	अणु .compatible = "brcm,bcm7038-gisb-arb", .data = gisb_offsets_bcm7038 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __init brcmstb_gisb_arb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *dn = pdev->dev.of_node;
	काष्ठा brcmstb_gisb_arb_device *gdev;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा resource *r;
	पूर्णांक err, समयout_irq, tea_irq, bp_irq;
	अचिन्हित पूर्णांक num_masters, j = 0;
	पूर्णांक i, first, last;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	समयout_irq = platक्रमm_get_irq(pdev, 0);
	tea_irq = platक्रमm_get_irq(pdev, 1);
	bp_irq = platक्रमm_get_irq(pdev, 2);

	gdev = devm_kzalloc(&pdev->dev, माप(*gdev), GFP_KERNEL);
	अगर (!gdev)
		वापस -ENOMEM;

	mutex_init(&gdev->lock);
	INIT_LIST_HEAD(&gdev->next);

	gdev->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(gdev->base))
		वापस PTR_ERR(gdev->base);

	of_id = of_match_node(brcmstb_gisb_arb_of_match, dn);
	अगर (!of_id) अणु
		pr_err("failed to look up compatible string\n");
		वापस -EINVAL;
	पूर्ण
	gdev->gisb_offsets = of_id->data;
	gdev->big_endian = of_device_is_big_endian(dn);

	err = devm_request_irq(&pdev->dev, समयout_irq,
				brcmstb_gisb_समयout_handler, 0, pdev->name,
				gdev);
	अगर (err < 0)
		वापस err;

	err = devm_request_irq(&pdev->dev, tea_irq,
				brcmstb_gisb_tea_handler, 0, pdev->name,
				gdev);
	अगर (err < 0)
		वापस err;

	/* Interrupt is optional */
	अगर (bp_irq > 0) अणु
		err = devm_request_irq(&pdev->dev, bp_irq,
				       brcmstb_gisb_bp_handler, 0, pdev->name,
				       gdev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* If we करो not have a valid mask, assume all masters are enabled */
	अगर (of_property_पढ़ो_u32(dn, "brcm,gisb-arb-master-mask",
				&gdev->valid_mask))
		gdev->valid_mask = 0xffffffff;

	/* Proceed with पढ़ोing the litteral names अगर we agree on the
	 * number of masters
	 */
	num_masters = of_property_count_strings(dn,
			"brcm,gisb-arb-master-names");
	अगर (hweight_दीर्घ(gdev->valid_mask) == num_masters) अणु
		first = ffs(gdev->valid_mask) - 1;
		last = fls(gdev->valid_mask) - 1;

		क्रम (i = first; i < last; i++) अणु
			अगर (!(gdev->valid_mask & BIT(i)))
				जारी;

			of_property_पढ़ो_string_index(dn,
					"brcm,gisb-arb-master-names", j,
					&gdev->master_names[i]);
			j++;
		पूर्ण
	पूर्ण

	err = sysfs_create_group(&pdev->dev.kobj, &gisb_arb_sysfs_attr_group);
	अगर (err)
		वापस err;

	platक्रमm_set_drvdata(pdev, gdev);

	list_add_tail(&gdev->next, &brcmstb_gisb_arb_device_list);

#अगर_घोषित CONFIG_MIPS
	board_be_handler = brcmstb_bus_error_handler;
#पूर्ण_अगर

	अगर (list_is_singular(&brcmstb_gisb_arb_device_list)) अणु
		रेजिस्टर_die_notअगरier(&gisb_die_notअगरier);
		atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					       &gisb_panic_notअगरier);
	पूर्ण

	dev_info(&pdev->dev, "registered irqs: %d, %d\n",
		 समयout_irq, tea_irq);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक brcmstb_gisb_arb_suspend(काष्ठा device *dev)
अणु
	काष्ठा brcmstb_gisb_arb_device *gdev = dev_get_drvdata(dev);

	gdev->saved_समयout = gisb_पढ़ो(gdev, ARB_TIMER);

	वापस 0;
पूर्ण

/* Make sure we provide the same समयout value that was configured beक्रमe, and
 * करो this beक्रमe the GISB समयout पूर्णांकerrupt handler has any chance to run.
 */
अटल पूर्णांक brcmstb_gisb_arb_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा brcmstb_gisb_arb_device *gdev = dev_get_drvdata(dev);

	gisb_ग_लिखो(gdev, gdev->saved_समयout, ARB_TIMER);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा brcmstb_gisb_arb_suspend       शून्य
#घोषणा brcmstb_gisb_arb_resume_noirq  शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops brcmstb_gisb_arb_pm_ops = अणु
	.suspend	= brcmstb_gisb_arb_suspend,
	.resume_noirq	= brcmstb_gisb_arb_resume_noirq,
पूर्ण;

अटल काष्ठा platक्रमm_driver brcmstb_gisb_arb_driver = अणु
	.driver = अणु
		.name	= "brcm-gisb-arb",
		.of_match_table = brcmstb_gisb_arb_of_match,
		.pm	= &brcmstb_gisb_arb_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init brcm_gisb_driver_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&brcmstb_gisb_arb_driver,
				     brcmstb_gisb_arb_probe);
पूर्ण

module_init(brcm_gisb_driver_init);
