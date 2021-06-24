<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* uio_fsl_elbc_gpcm: UIO driver क्रम eLBC/GPCM peripherals

   Copyright (C) 2014 Linutronix GmbH
     Author: John Ogness <john.ogness@linutronix.de>

   This driver provides UIO access to memory of a peripheral connected
   to the Freescale enhanced local bus controller (eLBC) पूर्णांकerface
   using the general purpose chip-select mode (GPCM).

   Here is an example of the device tree entries:

	localbus@ffe05000 अणु
		ranges = <0x2 0x0 0x0 0xff810000 0x10000>;

		dpm@2,0 अणु
			compatible = "fsl,elbc-gpcm-uio";
			reg = <0x2 0x0 0x10000>;
			elbc-gpcm-br = <0xff810800>;
			elbc-gpcm-or = <0xffff09f7>;
			पूर्णांकerrupt-parent = <&mpic>;
			पूर्णांकerrupts = <4 1>;
			device_type = "netx5152";
			uio_name = "netx_custom";
			netx5152,init-win0-offset = <0x0>;
		पूर्ण;
	पूर्ण;

   Only the entries reg (to identअगरy bank) and elbc-gpcm-* (initial BR/OR
   values) are required. The entries पूर्णांकerrupt*, device_type, and uio_name
   are optional (as well as any type-specअगरic options such as
   netx5152,init-win0-offset). As दीर्घ as no पूर्णांकerrupt handler is needed,
   this driver can be used without any type-specअगरic implementation.

   The netx5152 type has been tested to work with the netX 51/52 hardware
   from Hilscher using the Hilscher userspace netX stack.

   The netx5152 type should serve as a model to add new type-specअगरic
   devices as needed.
*/

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/fsl_lbc.h>

#घोषणा MAX_BANKS 8

काष्ठा fsl_elbc_gpcm अणु
	काष्ठा device *dev;
	काष्ठा fsl_lbc_regs __iomem *lbc;
	u32 bank;
	स्थिर अक्षर *name;

	व्योम (*init)(काष्ठा uio_info *info);
	व्योम (*shutकरोwn)(काष्ठा uio_info *info, bool init_err);
	irqवापस_t (*irq_handler)(पूर्णांक irq, काष्ठा uio_info *info);
पूर्ण;

अटल sमाप_प्रकार reg_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf);
अटल sमाप_प्रकार reg_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count);

अटल DEVICE_ATTR(reg_br, 0664, reg_show, reg_store);
अटल DEVICE_ATTR(reg_or, 0664, reg_show, reg_store);

अटल काष्ठा attribute *uio_fsl_elbc_gpcm_attrs[] = अणु
	&dev_attr_reg_br.attr,
	&dev_attr_reg_or.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(uio_fsl_elbc_gpcm);

अटल sमाप_प्रकार reg_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा uio_info *info = dev_get_drvdata(dev);
	काष्ठा fsl_elbc_gpcm *priv = info->priv;
	काष्ठा fsl_lbc_bank *bank = &priv->lbc->bank[priv->bank];

	अगर (attr == &dev_attr_reg_br) अणु
		वापस scnम_लिखो(buf, PAGE_SIZE, "0x%08x\n",
				 in_be32(&bank->br));

	पूर्ण अन्यथा अगर (attr == &dev_attr_reg_or) अणु
		वापस scnम_लिखो(buf, PAGE_SIZE, "0x%08x\n",
				 in_be32(&bank->or));
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार reg_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा uio_info *info = dev_get_drvdata(dev);
	काष्ठा fsl_elbc_gpcm *priv = info->priv;
	काष्ठा fsl_lbc_bank *bank = &priv->lbc->bank[priv->bank];
	अचिन्हित दीर्घ val;
	u32 reg_br_cur;
	u32 reg_or_cur;
	u32 reg_new;

	/* parse use input */
	अगर (kम_से_अदीर्घ(buf, 0, &val) != 0)
		वापस -EINVAL;
	reg_new = (u32)val;

	/* पढ़ो current values */
	reg_br_cur = in_be32(&bank->br);
	reg_or_cur = in_be32(&bank->or);

	अगर (attr == &dev_attr_reg_br) अणु
		/* not allowed to change effective base address */
		अगर ((reg_br_cur & reg_or_cur & BR_BA) !=
		    (reg_new & reg_or_cur & BR_BA)) अणु
			वापस -EINVAL;
		पूर्ण

		/* not allowed to change mode */
		अगर ((reg_new & BR_MSEL) != BR_MS_GPCM)
			वापस -EINVAL;

		/* ग_लिखो new value (क्रमce valid) */
		out_be32(&bank->br, reg_new | BR_V);

	पूर्ण अन्यथा अगर (attr == &dev_attr_reg_or) अणु
		/* not allowed to change access mask */
		अगर ((reg_or_cur & OR_GPCM_AM) != (reg_new & OR_GPCM_AM))
			वापस -EINVAL;

		/* ग_लिखो new value */
		out_be32(&bank->or, reg_new);

	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

#अगर_घोषित CONFIG_UIO_FSL_ELBC_GPCM_NETX5152
#घोषणा DPM_HOST_WIN0_OFFSET	0xff00
#घोषणा DPM_HOST_INT_STAT0	0xe0
#घोषणा DPM_HOST_INT_EN0	0xf0
#घोषणा DPM_HOST_INT_MASK	0xe600ffff
#घोषणा DPM_HOST_INT_GLOBAL_EN	0x80000000

अटल irqवापस_t netx5152_irq_handler(पूर्णांक irq, काष्ठा uio_info *info)
अणु
	व्योम __iomem *reg_पूर्णांक_en = info->mem[0].पूर्णांकernal_addr +
					DPM_HOST_WIN0_OFFSET +
					DPM_HOST_INT_EN0;
	व्योम __iomem *reg_पूर्णांक_stat = info->mem[0].पूर्णांकernal_addr +
					DPM_HOST_WIN0_OFFSET +
					DPM_HOST_INT_STAT0;

	/* check अगर an पूर्णांकerrupt is enabled and active */
	अगर ((ioपढ़ो32(reg_पूर्णांक_en) & ioपढ़ो32(reg_पूर्णांक_stat) &
	     DPM_HOST_INT_MASK) == 0) अणु
		वापस IRQ_NONE;
	पूर्ण

	/* disable पूर्णांकerrupts */
	ioग_लिखो32(ioपढ़ो32(reg_पूर्णांक_en) & ~DPM_HOST_INT_GLOBAL_EN, reg_पूर्णांक_en);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम netx5152_init(काष्ठा uio_info *info)
अणु
	अचिन्हित दीर्घ win0_offset = DPM_HOST_WIN0_OFFSET;
	काष्ठा fsl_elbc_gpcm *priv = info->priv;
	स्थिर व्योम *prop;

	/* get an optional initial win0 offset */
	prop = of_get_property(priv->dev->of_node,
			       "netx5152,init-win0-offset", शून्य);
	अगर (prop)
		win0_offset = of_पढ़ो_uदीर्घ(prop, 1);

	/* disable पूर्णांकerrupts */
	ioग_लिखो32(0, info->mem[0].पूर्णांकernal_addr + win0_offset +
		     DPM_HOST_INT_EN0);
पूर्ण

अटल व्योम netx5152_shutकरोwn(काष्ठा uio_info *info, bool init_err)
अणु
	अगर (init_err)
		वापस;

	/* disable पूर्णांकerrupts */
	ioग_लिखो32(0, info->mem[0].पूर्णांकernal_addr + DPM_HOST_WIN0_OFFSET +
		     DPM_HOST_INT_EN0);
पूर्ण
#पूर्ण_अगर

अटल व्योम setup_periph(काष्ठा fsl_elbc_gpcm *priv,
				   स्थिर अक्षर *type)
अणु
#अगर_घोषित CONFIG_UIO_FSL_ELBC_GPCM_NETX5152
	अगर (म_भेद(type, "netx5152") == 0) अणु
		priv->irq_handler = netx5152_irq_handler;
		priv->init = netx5152_init;
		priv->shutकरोwn = netx5152_shutकरोwn;
		priv->name = "netX 51/52";
		वापस;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक check_of_data(काष्ठा fsl_elbc_gpcm *priv,
				   काष्ठा resource *res,
				   u32 reg_br, u32 reg_or)
अणु
	/* check specअगरied bank */
	अगर (priv->bank >= MAX_BANKS) अणु
		dev_err(priv->dev, "invalid bank\n");
		वापस -ENODEV;
	पूर्ण

	/* check specअगरied mode (BR_MS_GPCM is 0) */
	अगर ((reg_br & BR_MSEL) != BR_MS_GPCM) अणु
		dev_err(priv->dev, "unsupported mode\n");
		वापस -ENODEV;
	पूर्ण

	/* check specअगरied mask vs. resource size */
	अगर ((~(reg_or & OR_GPCM_AM) + 1) != resource_size(res)) अणु
		dev_err(priv->dev, "address mask / size mismatch\n");
		वापस -ENODEV;
	पूर्ण

	/* check specअगरied address */
	अगर ((reg_br & reg_or & BR_BA) != fsl_lbc_addr(res->start)) अणु
		dev_err(priv->dev, "base address mismatch\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_of_data(काष्ठा fsl_elbc_gpcm *priv, काष्ठा device_node *node,
		       काष्ठा resource *res, u32 *reg_br,
		       u32 *reg_or, अचिन्हित पूर्णांक *irq, अक्षर **name)
अणु
	स्थिर अक्षर *dt_name;
	स्थिर अक्षर *type;
	पूर्णांक ret;

	/* get the memory resource */
	ret = of_address_to_resource(node, 0, res);
	अगर (ret) अणु
		dev_err(priv->dev, "failed to get resource\n");
		वापस ret;
	पूर्ण

	/* get the bank number */
	ret = of_property_पढ़ो_u32(node, "reg", &priv->bank);
	अगर (ret) अणु
		dev_err(priv->dev, "failed to get bank number\n");
		वापस ret;
	पूर्ण

	/* get BR value to set */
	ret = of_property_पढ़ो_u32(node, "elbc-gpcm-br", reg_br);
	अगर (ret) अणु
		dev_err(priv->dev, "missing elbc-gpcm-br value\n");
		वापस ret;
	पूर्ण

	/* get OR value to set */
	ret = of_property_पढ़ो_u32(node, "elbc-gpcm-or", reg_or);
	अगर (ret) अणु
		dev_err(priv->dev, "missing elbc-gpcm-or value\n");
		वापस ret;
	पूर्ण

	/* get optional peripheral type */
	priv->name = "generic";
	अगर (of_property_पढ़ो_string(node, "device_type", &type) == 0)
		setup_periph(priv, type);

	/* get optional irq value */
	*irq = irq_of_parse_and_map(node, 0);

	/* sanity check device tree data */
	ret = check_of_data(priv, res, *reg_br, *reg_or);
	अगर (ret)
		वापस ret;

	/* get optional uio name */
	अगर (of_property_पढ़ो_string(node, "uio_name", &dt_name) != 0)
		dt_name = "eLBC_GPCM";
	*name = devm_kstrdup(priv->dev, dt_name, GFP_KERNEL);
	अगर (!*name)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक uio_fsl_elbc_gpcm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा fsl_elbc_gpcm *priv;
	काष्ठा uio_info *info;
	अक्षर *uio_name = शून्य;
	काष्ठा resource res;
	अचिन्हित पूर्णांक irq;
	u32 reg_br_cur;
	u32 reg_or_cur;
	u32 reg_br_new;
	u32 reg_or_new;
	पूर्णांक ret;

	अगर (!fsl_lbc_ctrl_dev || !fsl_lbc_ctrl_dev->regs)
		वापस -ENODEV;

	/* allocate निजी data */
	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->dev = &pdev->dev;
	priv->lbc = fsl_lbc_ctrl_dev->regs;

	/* get device tree data */
	ret = get_of_data(priv, node, &res, &reg_br_new, &reg_or_new,
			  &irq, &uio_name);
	अगर (ret)
		वापस ret;

	/* allocate UIO काष्ठाure */
	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	/* get current BR/OR values */
	reg_br_cur = in_be32(&priv->lbc->bank[priv->bank].br);
	reg_or_cur = in_be32(&priv->lbc->bank[priv->bank].or);

	/* अगर bank alपढ़ोy configured, make sure it matches */
	अगर ((reg_br_cur & BR_V)) अणु
		अगर ((reg_br_cur & BR_MSEL) != BR_MS_GPCM ||
		    (reg_br_cur & reg_or_cur & BR_BA)
		     != fsl_lbc_addr(res.start)) अणु
			dev_err(priv->dev,
				"bank in use by another peripheral\n");
			वापस -ENODEV;
		पूर्ण

		/* warn अगर behavior settings changing */
		अगर ((reg_br_cur & ~(BR_BA | BR_V)) !=
		    (reg_br_new & ~(BR_BA | BR_V))) अणु
			dev_warn(priv->dev,
				 "modifying BR settings: 0x%08x -> 0x%08x",
				 reg_br_cur, reg_br_new);
		पूर्ण
		अगर ((reg_or_cur & ~OR_GPCM_AM) != (reg_or_new & ~OR_GPCM_AM)) अणु
			dev_warn(priv->dev,
				 "modifying OR settings: 0x%08x -> 0x%08x",
				 reg_or_cur, reg_or_new);
		पूर्ण
	पूर्ण

	/* configure the bank (क्रमce base address and GPCM) */
	reg_br_new &= ~(BR_BA | BR_MSEL);
	reg_br_new |= fsl_lbc_addr(res.start) | BR_MS_GPCM | BR_V;
	out_be32(&priv->lbc->bank[priv->bank].or, reg_or_new);
	out_be32(&priv->lbc->bank[priv->bank].br, reg_br_new);

	/* map the memory resource */
	info->mem[0].पूर्णांकernal_addr = ioremap(res.start, resource_size(&res));
	अगर (!info->mem[0].पूर्णांकernal_addr) अणु
		dev_err(priv->dev, "failed to map chip region\n");
		वापस -ENODEV;
	पूर्ण

	/* set all UIO data */
	info->mem[0].name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%pOFn", node);
	info->mem[0].addr = res.start;
	info->mem[0].size = resource_size(&res);
	info->mem[0].memtype = UIO_MEM_PHYS;
	info->priv = priv;
	info->name = uio_name;
	info->version = "0.0.1";
	अगर (irq != NO_IRQ) अणु
		अगर (priv->irq_handler) अणु
			info->irq = irq;
			info->irq_flags = IRQF_SHARED;
			info->handler = priv->irq_handler;
		पूर्ण अन्यथा अणु
			irq = NO_IRQ;
			dev_warn(priv->dev, "ignoring irq, no handler\n");
		पूर्ण
	पूर्ण

	अगर (priv->init)
		priv->init(info);

	/* रेजिस्टर UIO device */
	अगर (uio_रेजिस्टर_device(priv->dev, info) != 0) अणु
		dev_err(priv->dev, "UIO registration failed\n");
		ret = -ENODEV;
		जाओ out_err2;
	पूर्ण

	/* store निजी data */
	platक्रमm_set_drvdata(pdev, info);

	dev_info(priv->dev,
		 "eLBC/GPCM device (%s) at 0x%llx, bank %d, irq=%d\n",
		 priv->name, (अचिन्हित दीर्घ दीर्घ)res.start, priv->bank,
		 irq != NO_IRQ ? irq : -1);

	वापस 0;
out_err2:
	अगर (priv->shutकरोwn)
		priv->shutकरोwn(info, true);
	iounmap(info->mem[0].पूर्णांकernal_addr);
	वापस ret;
पूर्ण

अटल पूर्णांक uio_fsl_elbc_gpcm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uio_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा fsl_elbc_gpcm *priv = info->priv;

	platक्रमm_set_drvdata(pdev, शून्य);
	uio_unरेजिस्टर_device(info);
	अगर (priv->shutकरोwn)
		priv->shutकरोwn(info, false);
	iounmap(info->mem[0].पूर्णांकernal_addr);

	वापस 0;

पूर्ण

अटल स्थिर काष्ठा of_device_id uio_fsl_elbc_gpcm_match[] = अणु
	अणु .compatible = "fsl,elbc-gpcm-uio", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uio_fsl_elbc_gpcm_match);

अटल काष्ठा platक्रमm_driver uio_fsl_elbc_gpcm_driver = अणु
	.driver = अणु
		.name = "fsl,elbc-gpcm-uio",
		.of_match_table = uio_fsl_elbc_gpcm_match,
		.dev_groups = uio_fsl_elbc_gpcm_groups,
	पूर्ण,
	.probe = uio_fsl_elbc_gpcm_probe,
	.हटाओ = uio_fsl_elbc_gpcm_हटाओ,
पूर्ण;
module_platक्रमm_driver(uio_fsl_elbc_gpcm_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Ogness <john.ogness@linutronix.de>");
MODULE_DESCRIPTION("Freescale Enhanced Local Bus Controller GPCM driver");
