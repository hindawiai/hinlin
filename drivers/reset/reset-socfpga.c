<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018, Intel Corporation
 * Copied from reset-sunxi.c
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/reset/reset-simple.h>
#समावेश <linux/reset/socfpga.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#घोषणा SOCFPGA_NR_BANKS	8

अटल पूर्णांक a10_reset_init(काष्ठा device_node *np)
अणु
	काष्ठा reset_simple_data *data;
	काष्ठा resource res;
	resource_माप_प्रकार size;
	पूर्णांक ret;
	u32 reg_offset = 0x10;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = of_address_to_resource(np, 0, &res);
	अगर (ret)
		जाओ err_alloc;

	size = resource_size(&res);
	अगर (!request_mem_region(res.start, size, np->name)) अणु
		ret = -EBUSY;
		जाओ err_alloc;
	पूर्ण

	data->membase = ioremap(res.start, size);
	अगर (!data->membase) अणु
		ret = -ENOMEM;
		जाओ release_region;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "altr,modrst-offset", &reg_offset))
		pr_warn("missing altr,modrst-offset property, assuming 0x10\n");
	data->membase += reg_offset;

	spin_lock_init(&data->lock);

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = SOCFPGA_NR_BANKS * 32;
	data->rcdev.ops = &reset_simple_ops;
	data->rcdev.of_node = np;
	data->status_active_low = true;

	ret = reset_controller_रेजिस्टर(&data->rcdev);
	अगर (ret)
		pr_err("unable to register device\n");

	वापस ret;

release_region:
	release_mem_region(res.start, size);

err_alloc:
	kमुक्त(data);
	वापस ret;
पूर्ण;

/*
 * These are the reset controller we need to initialize early on in
 * our प्रणाली, beक्रमe we can even think of using a regular device
 * driver क्रम it.
 * The controllers that we can रेजिस्टर through the regular device
 * model are handled by the simple reset driver directly.
 */
अटल स्थिर काष्ठा of_device_id socfpga_early_reset_dt_ids[] __initस्थिर = अणु
	अणु .compatible = "altr,rst-mgr", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

व्योम __init socfpga_reset_init(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम_each_matching_node(np, socfpga_early_reset_dt_ids)
		a10_reset_init(np);
पूर्ण
