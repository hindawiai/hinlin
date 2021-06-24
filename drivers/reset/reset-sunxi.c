<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Allwinner SoCs Reset Controller driver
 *
 * Copyright 2013 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/reset/reset-simple.h>
#समावेश <linux/reset/sunxi.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

अटल पूर्णांक sunxi_reset_init(काष्ठा device_node *np)
अणु
	काष्ठा reset_simple_data *data;
	काष्ठा resource res;
	resource_माप_प्रकार size;
	पूर्णांक ret;

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
		जाओ err_alloc;
	पूर्ण

	spin_lock_init(&data->lock);

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = size * 8;
	data->rcdev.ops = &reset_simple_ops;
	data->rcdev.of_node = np;
	data->active_low = true;

	वापस reset_controller_रेजिस्टर(&data->rcdev);

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
अटल स्थिर काष्ठा of_device_id sunxi_early_reset_dt_ids[] __initस्थिर = अणु
	अणु .compatible = "allwinner,sun6i-a31-ahb1-reset", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

व्योम __init sun6i_reset_init(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम_each_matching_node(np, sunxi_early_reset_dt_ids)
		sunxi_reset_init(np);
पूर्ण
