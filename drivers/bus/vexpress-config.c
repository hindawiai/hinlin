<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2014 ARM Limited
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/vexpress.h>

#घोषणा SYS_MISC		0x0
#घोषणा SYS_MISC_MASTERSITE	(1 << 14)

#घोषणा SYS_PROCID0		0x24
#घोषणा SYS_PROCID1		0x28
#घोषणा SYS_HBI_MASK		0xfff
#घोषणा SYS_PROCIDx_HBI_SHIFT	0

#घोषणा SYS_CFGDATA		0x40

#घोषणा SYS_CFGCTRL		0x44
#घोषणा SYS_CFGCTRL_START	(1 << 31)
#घोषणा SYS_CFGCTRL_WRITE	(1 << 30)
#घोषणा SYS_CFGCTRL_DCC(n)	(((n) & 0xf) << 26)
#घोषणा SYS_CFGCTRL_FUNC(n)	(((n) & 0x3f) << 20)
#घोषणा SYS_CFGCTRL_SITE(n)	(((n) & 0x3) << 16)
#घोषणा SYS_CFGCTRL_POSITION(n)	(((n) & 0xf) << 12)
#घोषणा SYS_CFGCTRL_DEVICE(n)	(((n) & 0xfff) << 0)

#घोषणा SYS_CFGSTAT		0x48
#घोषणा SYS_CFGSTAT_ERR		(1 << 1)
#घोषणा SYS_CFGSTAT_COMPLETE	(1 << 0)

#घोषणा VEXPRESS_SITE_MB		0
#घोषणा VEXPRESS_SITE_DB1		1
#घोषणा VEXPRESS_SITE_DB2		2
#घोषणा VEXPRESS_SITE_MASTER		0xf

काष्ठा vexpress_syscfg अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा list_head funcs;
पूर्ण;

काष्ठा vexpress_syscfg_func अणु
	काष्ठा list_head list;
	काष्ठा vexpress_syscfg *syscfg;
	काष्ठा regmap *regmap;
	पूर्णांक num_ढाँचाs;
	u32 ढाँचा[]; /* Keep it last! */
पूर्ण;

काष्ठा vexpress_config_bridge_ops अणु
	काष्ठा regmap * (*regmap_init)(काष्ठा device *dev, व्योम *context);
	व्योम (*regmap_निकास)(काष्ठा regmap *regmap, व्योम *context);
पूर्ण;

काष्ठा vexpress_config_bridge अणु
	काष्ठा vexpress_config_bridge_ops *ops;
	व्योम *context;
पूर्ण;


अटल DEFINE_MUTEX(vexpress_config_mutex);
अटल u32 vexpress_config_site_master = VEXPRESS_SITE_MASTER;


अटल व्योम vexpress_config_set_master(u32 site)
अणु
	vexpress_config_site_master = site;
पूर्ण

अटल व्योम vexpress_config_lock(व्योम *arg)
अणु
	mutex_lock(&vexpress_config_mutex);
पूर्ण

अटल व्योम vexpress_config_unlock(व्योम *arg)
अणु
	mutex_unlock(&vexpress_config_mutex);
पूर्ण


अटल व्योम vexpress_config_find_prop(काष्ठा device_node *node,
		स्थिर अक्षर *name, u32 *val)
अणु
	/* Default value */
	*val = 0;

	of_node_get(node);
	जबतक (node) अणु
		अगर (of_property_पढ़ो_u32(node, name, val) == 0) अणु
			of_node_put(node);
			वापस;
		पूर्ण
		node = of_get_next_parent(node);
	पूर्ण
पूर्ण

अटल पूर्णांक vexpress_config_get_topo(काष्ठा device_node *node, u32 *site,
		u32 *position, u32 *dcc)
अणु
	vexpress_config_find_prop(node, "arm,vexpress,site", site);
	अगर (*site == VEXPRESS_SITE_MASTER)
		*site = vexpress_config_site_master;
	अगर (WARN_ON(vexpress_config_site_master == VEXPRESS_SITE_MASTER))
		वापस -EINVAL;
	vexpress_config_find_prop(node, "arm,vexpress,position", position);
	vexpress_config_find_prop(node, "arm,vexpress,dcc", dcc);

	वापस 0;
पूर्ण


अटल व्योम vexpress_config_devres_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा vexpress_config_bridge *bridge = dev_get_drvdata(dev->parent);
	काष्ठा regmap *regmap = res;

	bridge->ops->regmap_निकास(regmap, bridge->context);
पूर्ण

काष्ठा regmap *devm_regmap_init_vexpress_config(काष्ठा device *dev)
अणु
	काष्ठा vexpress_config_bridge *bridge;
	काष्ठा regmap *regmap;
	काष्ठा regmap **res;

	bridge = dev_get_drvdata(dev->parent);
	अगर (WARN_ON(!bridge))
		वापस ERR_PTR(-EINVAL);

	res = devres_alloc(vexpress_config_devres_release, माप(*res),
			GFP_KERNEL);
	अगर (!res)
		वापस ERR_PTR(-ENOMEM);

	regmap = (bridge->ops->regmap_init)(dev, bridge->context);
	अगर (IS_ERR(regmap)) अणु
		devres_मुक्त(res);
		वापस regmap;
	पूर्ण

	*res = regmap;
	devres_add(dev, res);

	वापस regmap;
पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_init_vexpress_config);

अटल पूर्णांक vexpress_syscfg_exec(काष्ठा vexpress_syscfg_func *func,
		पूर्णांक index, bool ग_लिखो, u32 *data)
अणु
	काष्ठा vexpress_syscfg *syscfg = func->syscfg;
	u32 command, status;
	पूर्णांक tries;
	दीर्घ समयout;

	अगर (WARN_ON(index >= func->num_ढाँचाs))
		वापस -EINVAL;

	command = पढ़ोl(syscfg->base + SYS_CFGCTRL);
	अगर (WARN_ON(command & SYS_CFGCTRL_START))
		वापस -EBUSY;

	command = func->ढाँचा[index];
	command |= SYS_CFGCTRL_START;
	command |= ग_लिखो ? SYS_CFGCTRL_WRITE : 0;

	/* Use a canary क्रम पढ़ोs */
	अगर (!ग_लिखो)
		*data = 0xdeadbeef;

	dev_dbg(syscfg->dev, "func %p, command %x, data %x\n",
			func, command, *data);
	ग_लिखोl(*data, syscfg->base + SYS_CFGDATA);
	ग_लिखोl(0, syscfg->base + SYS_CFGSTAT);
	ग_लिखोl(command, syscfg->base + SYS_CFGCTRL);
	mb();

	/* The operation can take ages... Go to sleep, 100us initially */
	tries = 100;
	समयout = 100;
	करो अणु
		अगर (!irqs_disabled()) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_समयout(usecs_to_jअगरfies(समयout));
			अगर (संकेत_pending(current))
				वापस -EINTR;
		पूर्ण अन्यथा अणु
			udelay(समयout);
		पूर्ण

		status = पढ़ोl(syscfg->base + SYS_CFGSTAT);
		अगर (status & SYS_CFGSTAT_ERR)
			वापस -EFAULT;

		अगर (समयout > 20)
			समयout -= 20;
	पूर्ण जबतक (--tries && !(status & SYS_CFGSTAT_COMPLETE));
	अगर (WARN_ON_ONCE(!tries))
		वापस -ETIMEDOUT;

	अगर (!ग_लिखो) अणु
		*data = पढ़ोl(syscfg->base + SYS_CFGDATA);
		dev_dbg(syscfg->dev, "func %p, read data %x\n", func, *data);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vexpress_syscfg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक index,
		अचिन्हित पूर्णांक *val)
अणु
	काष्ठा vexpress_syscfg_func *func = context;

	वापस vexpress_syscfg_exec(func, index, false, val);
पूर्ण

अटल पूर्णांक vexpress_syscfg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक index,
		अचिन्हित पूर्णांक val)
अणु
	काष्ठा vexpress_syscfg_func *func = context;

	वापस vexpress_syscfg_exec(func, index, true, &val);
पूर्ण

अटल काष्ठा regmap_config vexpress_syscfg_regmap_config = अणु
	.lock = vexpress_config_lock,
	.unlock = vexpress_config_unlock,
	.reg_bits = 32,
	.val_bits = 32,
	.reg_पढ़ो = vexpress_syscfg_पढ़ो,
	.reg_ग_लिखो = vexpress_syscfg_ग_लिखो,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
पूर्ण;


अटल काष्ठा regmap *vexpress_syscfg_regmap_init(काष्ठा device *dev,
		व्योम *context)
अणु
	पूर्णांक err;
	काष्ठा vexpress_syscfg *syscfg = context;
	काष्ठा vexpress_syscfg_func *func;
	काष्ठा property *prop;
	स्थिर __be32 *val = शून्य;
	__be32 energy_quirk[4];
	पूर्णांक num;
	u32 site, position, dcc;
	पूर्णांक i;

	err = vexpress_config_get_topo(dev->of_node, &site,
				&position, &dcc);
	अगर (err)
		वापस ERR_PTR(err);

	prop = of_find_property(dev->of_node,
			"arm,vexpress-sysreg,func", शून्य);
	अगर (!prop)
		वापस ERR_PTR(-EINVAL);

	num = prop->length / माप(u32) / 2;
	val = prop->value;

	/*
	 * "arm,vexpress-energy" function used to be described
	 * by its first device only, now it requires both
	 */
	अगर (num == 1 && of_device_is_compatible(dev->of_node,
			"arm,vexpress-energy")) अणु
		num = 2;
		energy_quirk[0] = *val;
		energy_quirk[2] = *val++;
		energy_quirk[1] = *val;
		energy_quirk[3] = cpu_to_be32(be32_to_cpup(val) + 1);
		val = energy_quirk;
	पूर्ण

	func = kzalloc(काष्ठा_size(func, ढाँचा, num), GFP_KERNEL);
	अगर (!func)
		वापस ERR_PTR(-ENOMEM);

	func->syscfg = syscfg;
	func->num_ढाँचाs = num;

	क्रम (i = 0; i < num; i++) अणु
		u32 function, device;

		function = be32_to_cpup(val++);
		device = be32_to_cpup(val++);

		dev_dbg(dev, "func %p: %u/%u/%u/%u/%u\n",
				func, site, position, dcc,
				function, device);

		func->ढाँचा[i] = SYS_CFGCTRL_DCC(dcc);
		func->ढाँचा[i] |= SYS_CFGCTRL_SITE(site);
		func->ढाँचा[i] |= SYS_CFGCTRL_POSITION(position);
		func->ढाँचा[i] |= SYS_CFGCTRL_FUNC(function);
		func->ढाँचा[i] |= SYS_CFGCTRL_DEVICE(device);
	पूर्ण

	vexpress_syscfg_regmap_config.max_रेजिस्टर = num - 1;

	func->regmap = regmap_init(dev, शून्य, func,
			&vexpress_syscfg_regmap_config);

	अगर (IS_ERR(func->regmap)) अणु
		व्योम *err = func->regmap;

		kमुक्त(func);
		वापस err;
	पूर्ण

	list_add(&func->list, &syscfg->funcs);

	वापस func->regmap;
पूर्ण

अटल व्योम vexpress_syscfg_regmap_निकास(काष्ठा regmap *regmap, व्योम *context)
अणु
	काष्ठा vexpress_syscfg *syscfg = context;
	काष्ठा vexpress_syscfg_func *func, *पंचांगp;

	regmap_निकास(regmap);

	list_क्रम_each_entry_safe(func, पंचांगp, &syscfg->funcs, list) अणु
		अगर (func->regmap == regmap) अणु
			list_del(&syscfg->funcs);
			kमुक्त(func);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा vexpress_config_bridge_ops vexpress_syscfg_bridge_ops = अणु
	.regmap_init = vexpress_syscfg_regmap_init,
	.regmap_निकास = vexpress_syscfg_regmap_निकास,
पूर्ण;


अटल पूर्णांक vexpress_syscfg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vexpress_syscfg *syscfg;
	काष्ठा resource *res;
	काष्ठा vexpress_config_bridge *bridge;
	काष्ठा device_node *node;
	पूर्णांक master;
	u32 dt_hbi;

	syscfg = devm_kzalloc(&pdev->dev, माप(*syscfg), GFP_KERNEL);
	अगर (!syscfg)
		वापस -ENOMEM;
	syscfg->dev = &pdev->dev;
	INIT_LIST_HEAD(&syscfg->funcs);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	syscfg->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(syscfg->base))
		वापस PTR_ERR(syscfg->base);

	bridge = devm_kदो_स्मृति(&pdev->dev, माप(*bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->ops = &vexpress_syscfg_bridge_ops;
	bridge->context = syscfg;

	dev_set_drvdata(&pdev->dev, bridge);

	master = पढ़ोl(syscfg->base + SYS_MISC) & SYS_MISC_MASTERSITE ?
			VEXPRESS_SITE_DB2 : VEXPRESS_SITE_DB1;
	vexpress_config_set_master(master);

	/* Confirm board type against DT property, अगर available */
	अगर (of_property_पढ़ो_u32(of_root, "arm,hbi", &dt_hbi) == 0) अणु
		u32 id = पढ़ोl(syscfg->base + (master == VEXPRESS_SITE_DB1 ?
				 SYS_PROCID0 : SYS_PROCID1));
		u32 hbi = (id >> SYS_PROCIDx_HBI_SHIFT) & SYS_HBI_MASK;

		अगर (WARN_ON(dt_hbi != hbi))
			dev_warn(&pdev->dev, "DT HBI (%x) is not matching hardware (%x)!\n",
					dt_hbi, hbi);
	पूर्ण

	क्रम_each_compatible_node(node, शून्य, "arm,vexpress,config-bus") अणु
		काष्ठा device_node *bridge_np;

		bridge_np = of_parse_phandle(node, "arm,vexpress,config-bridge", 0);
		अगर (bridge_np != pdev->dev.parent->of_node)
			जारी;

		of_platक्रमm_populate(node, शून्य, शून्य, &pdev->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id vexpress_syscfg_id_table[] = अणु
	अणु "vexpress-syscfg", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, vexpress_syscfg_id_table);

अटल काष्ठा platक्रमm_driver vexpress_syscfg_driver = अणु
	.driver.name = "vexpress-syscfg",
	.id_table = vexpress_syscfg_id_table,
	.probe = vexpress_syscfg_probe,
पूर्ण;
module_platक्रमm_driver(vexpress_syscfg_driver);
MODULE_LICENSE("GPL v2");
