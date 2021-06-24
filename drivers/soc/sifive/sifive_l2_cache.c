<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SiFive L2 cache controller Driver
 *
 * Copyright (C) 2018-2019 SiFive, Inc.
 *
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/cacheinfo.h>
#समावेश <soc/sअगरive/sअगरive_l2_cache.h>

#घोषणा SIFIVE_L2_सूचीECCFIX_LOW 0x100
#घोषणा SIFIVE_L2_सूचीECCFIX_HIGH 0x104
#घोषणा SIFIVE_L2_सूचीECCFIX_COUNT 0x108

#घोषणा SIFIVE_L2_सूचीECCFAIL_LOW 0x120
#घोषणा SIFIVE_L2_सूचीECCFAIL_HIGH 0x124
#घोषणा SIFIVE_L2_सूचीECCFAIL_COUNT 0x128

#घोषणा SIFIVE_L2_DATECCFIX_LOW 0x140
#घोषणा SIFIVE_L2_DATECCFIX_HIGH 0x144
#घोषणा SIFIVE_L2_DATECCFIX_COUNT 0x148

#घोषणा SIFIVE_L2_DATECCFAIL_LOW 0x160
#घोषणा SIFIVE_L2_DATECCFAIL_HIGH 0x164
#घोषणा SIFIVE_L2_DATECCFAIL_COUNT 0x168

#घोषणा SIFIVE_L2_CONFIG 0x00
#घोषणा SIFIVE_L2_WAYENABLE 0x08
#घोषणा SIFIVE_L2_ECCINJECTERR 0x40

#घोषणा SIFIVE_L2_MAX_ECCINTR 4

अटल व्योम __iomem *l2_base;
अटल पूर्णांक g_irq[SIFIVE_L2_MAX_ECCINTR];
अटल काष्ठा riscv_cacheinfo_ops l2_cache_ops;

क्रमागत अणु
	सूची_CORR = 0,
	DATA_CORR,
	DATA_UNCORR,
	सूची_UNCORR,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल काष्ठा dentry *sअगरive_test;

अटल sमाप_प्रकार l2_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
			माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक val;

	अगर (kstrtouपूर्णांक_from_user(data, count, 0, &val))
		वापस -EINVAL;
	अगर ((val < 0xFF) || (val >= 0x10000 && val < 0x100FF))
		ग_लिखोl(val, l2_base + SIFIVE_L2_ECCINJECTERR);
	अन्यथा
		वापस -EINVAL;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations l2_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.ग_लिखो = l2_ग_लिखो
पूर्ण;

अटल व्योम setup_sअगरive_debug(व्योम)
अणु
	sअगरive_test = debugfs_create_dir("sifive_l2_cache", शून्य);

	debugfs_create_file("sifive_debug_inject_error", 0200,
			    sअगरive_test, शून्य, &l2_fops);
पूर्ण
#पूर्ण_अगर

अटल व्योम l2_config_पढ़ो(व्योम)
अणु
	u32 regval, val;

	regval = पढ़ोl(l2_base + SIFIVE_L2_CONFIG);
	val = regval & 0xFF;
	pr_info("L2CACHE: No. of Banks in the cache: %d\n", val);
	val = (regval & 0xFF00) >> 8;
	pr_info("L2CACHE: No. of ways per bank: %d\n", val);
	val = (regval & 0xFF0000) >> 16;
	pr_info("L2CACHE: Sets per bank: %llu\n", (uपूर्णांक64_t)1 << val);
	val = (regval & 0xFF000000) >> 24;
	pr_info("L2CACHE: Bytes per cache block: %llu\n", (uपूर्णांक64_t)1 << val);

	regval = पढ़ोl(l2_base + SIFIVE_L2_WAYENABLE);
	pr_info("L2CACHE: Index of the largest way enabled: %d\n", regval);
पूर्ण

अटल स्थिर काष्ठा of_device_id sअगरive_l2_ids[] = अणु
	अणु .compatible = "sifive,fu540-c000-ccache" पूर्ण,
	अणु .compatible = "sifive,fu740-c000-ccache" पूर्ण,
	अणु /* end of table */ पूर्ण,
पूर्ण;

अटल ATOMIC_NOTIFIER_HEAD(l2_err_chain);

पूर्णांक रेजिस्टर_sअगरive_l2_error_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&l2_err_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_sअगरive_l2_error_notअगरier);

पूर्णांक unरेजिस्टर_sअगरive_l2_error_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&l2_err_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_sअगरive_l2_error_notअगरier);

अटल पूर्णांक l2_largest_wayenabled(व्योम)
अणु
	वापस पढ़ोl(l2_base + SIFIVE_L2_WAYENABLE) & 0xFF;
पूर्ण

अटल sमाप_प्रकार number_of_ways_enabled_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", l2_largest_wayenabled());
पूर्ण

अटल DEVICE_ATTR_RO(number_of_ways_enabled);

अटल काष्ठा attribute *priv_attrs[] = अणु
	&dev_attr_number_of_ways_enabled.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group priv_attr_group = अणु
	.attrs = priv_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *l2_get_priv_group(काष्ठा cacheinfo *this_leaf)
अणु
	/* We want to use निजी group क्रम L2 cache only */
	अगर (this_leaf->level == 2)
		वापस &priv_attr_group;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल irqवापस_t l2_पूर्णांक_handler(पूर्णांक irq, व्योम *device)
अणु
	अचिन्हित पूर्णांक add_h, add_l;

	अगर (irq == g_irq[सूची_CORR]) अणु
		add_h = पढ़ोl(l2_base + SIFIVE_L2_सूचीECCFIX_HIGH);
		add_l = पढ़ोl(l2_base + SIFIVE_L2_सूचीECCFIX_LOW);
		pr_err("L2CACHE: DirError @ 0x%08X.%08X\n", add_h, add_l);
		/* Reading this रेजिस्टर clears the DirError पूर्णांकerrupt sig */
		पढ़ोl(l2_base + SIFIVE_L2_सूचीECCFIX_COUNT);
		atomic_notअगरier_call_chain(&l2_err_chain, SIFIVE_L2_ERR_TYPE_CE,
					   "DirECCFix");
	पूर्ण
	अगर (irq == g_irq[सूची_UNCORR]) अणु
		add_h = पढ़ोl(l2_base + SIFIVE_L2_सूचीECCFAIL_HIGH);
		add_l = पढ़ोl(l2_base + SIFIVE_L2_सूचीECCFAIL_LOW);
		/* Reading this रेजिस्टर clears the DirFail पूर्णांकerrupt sig */
		पढ़ोl(l2_base + SIFIVE_L2_सूचीECCFAIL_COUNT);
		atomic_notअगरier_call_chain(&l2_err_chain, SIFIVE_L2_ERR_TYPE_UE,
					   "DirECCFail");
		panic("L2CACHE: DirFail @ 0x%08X.%08X\n", add_h, add_l);
	पूर्ण
	अगर (irq == g_irq[DATA_CORR]) अणु
		add_h = पढ़ोl(l2_base + SIFIVE_L2_DATECCFIX_HIGH);
		add_l = पढ़ोl(l2_base + SIFIVE_L2_DATECCFIX_LOW);
		pr_err("L2CACHE: DataError @ 0x%08X.%08X\n", add_h, add_l);
		/* Reading this रेजिस्टर clears the DataError पूर्णांकerrupt sig */
		पढ़ोl(l2_base + SIFIVE_L2_DATECCFIX_COUNT);
		atomic_notअगरier_call_chain(&l2_err_chain, SIFIVE_L2_ERR_TYPE_CE,
					   "DatECCFix");
	पूर्ण
	अगर (irq == g_irq[DATA_UNCORR]) अणु
		add_h = पढ़ोl(l2_base + SIFIVE_L2_DATECCFAIL_HIGH);
		add_l = पढ़ोl(l2_base + SIFIVE_L2_DATECCFAIL_LOW);
		pr_err("L2CACHE: DataFail @ 0x%08X.%08X\n", add_h, add_l);
		/* Reading this रेजिस्टर clears the DataFail पूर्णांकerrupt sig */
		पढ़ोl(l2_base + SIFIVE_L2_DATECCFAIL_COUNT);
		atomic_notअगरier_call_chain(&l2_err_chain, SIFIVE_L2_ERR_TYPE_UE,
					   "DatECCFail");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init sअगरive_l2_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource res;
	पूर्णांक i, rc, पूर्णांकr_num;

	np = of_find_matching_node(शून्य, sअगरive_l2_ids);
	अगर (!np)
		वापस -ENODEV;

	अगर (of_address_to_resource(np, 0, &res))
		वापस -ENODEV;

	l2_base = ioremap(res.start, resource_size(&res));
	अगर (!l2_base)
		वापस -ENOMEM;

	पूर्णांकr_num = of_property_count_u32_elems(np, "interrupts");
	अगर (!पूर्णांकr_num) अणु
		pr_err("L2CACHE: no interrupts property\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < पूर्णांकr_num; i++) अणु
		g_irq[i] = irq_of_parse_and_map(np, i);
		rc = request_irq(g_irq[i], l2_पूर्णांक_handler, 0, "l2_ecc", शून्य);
		अगर (rc) अणु
			pr_err("L2CACHE: Could not request IRQ %d\n", g_irq[i]);
			वापस rc;
		पूर्ण
	पूर्ण

	l2_config_पढ़ो();

	l2_cache_ops.get_priv_group = l2_get_priv_group;
	riscv_set_cacheinfo_ops(&l2_cache_ops);

#अगर_घोषित CONFIG_DEBUG_FS
	setup_sअगरive_debug();
#पूर्ण_अगर
	वापस 0;
पूर्ण
device_initcall(sअगरive_l2_init);
