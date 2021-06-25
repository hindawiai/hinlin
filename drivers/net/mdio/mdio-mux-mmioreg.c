<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple memory-mapped device MDIO MUX driver
 *
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/mdio-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा mdio_mux_mmioreg_state अणु
	व्योम *mux_handle;
	phys_addr_t phys;
	अचिन्हित पूर्णांक iosize;
	अचिन्हित पूर्णांक mask;
पूर्ण;

/*
 * MDIO multiplexing चयन function
 *
 * This function is called by the mdio-mux layer when it thinks the mdio bus
 * multiplexer needs to चयन.
 *
 * 'current_child' is the current value of the mux रेजिस्टर (masked via
 * s->mask).
 *
 * 'desired_child' is the value of the 'reg' property of the target child MDIO
 * node.
 *
 * The first समय this function is called, current_child == -1.
 *
 * If current_child == desired_child, then the mux is alपढ़ोy set to the
 * correct bus.
 */
अटल पूर्णांक mdio_mux_mmioreg_चयन_fn(पूर्णांक current_child, पूर्णांक desired_child,
				      व्योम *data)
अणु
	काष्ठा mdio_mux_mmioreg_state *s = data;

	अगर (current_child ^ desired_child) अणु
		व्योम __iomem *p = ioremap(s->phys, s->iosize);
		अगर (!p)
			वापस -ENOMEM;

		चयन (s->iosize) अणु
		हाल माप(uपूर्णांक8_t): अणु
			uपूर्णांक8_t x, y;

			x = ioपढ़ो8(p);
			y = (x & ~s->mask) | desired_child;
			अगर (x != y) अणु
				ioग_लिखो8((x & ~s->mask) | desired_child, p);
				pr_debug("%s: %02x -> %02x\n", __func__, x, y);
			पूर्ण

			अवरोध;
		पूर्ण
		हाल माप(uपूर्णांक16_t): अणु
			uपूर्णांक16_t x, y;

			x = ioपढ़ो16(p);
			y = (x & ~s->mask) | desired_child;
			अगर (x != y) अणु
				ioग_लिखो16((x & ~s->mask) | desired_child, p);
				pr_debug("%s: %04x -> %04x\n", __func__, x, y);
			पूर्ण

			अवरोध;
		पूर्ण
		हाल माप(uपूर्णांक32_t): अणु
			uपूर्णांक32_t x, y;

			x = ioपढ़ो32(p);
			y = (x & ~s->mask) | desired_child;
			अगर (x != y) अणु
				ioग_लिखो32((x & ~s->mask) | desired_child, p);
				pr_debug("%s: %08x -> %08x\n", __func__, x, y);
			पूर्ण

			अवरोध;
		पूर्ण
		पूर्ण

		iounmap(p);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mdio_mux_mmioreg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np2, *np = pdev->dev.of_node;
	काष्ठा mdio_mux_mmioreg_state *s;
	काष्ठा resource res;
	स्थिर __be32 *iprop;
	पूर्णांक len, ret;

	dev_dbg(&pdev->dev, "probing node %pOF\n", np);

	s = devm_kzalloc(&pdev->dev, माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	ret = of_address_to_resource(np, 0, &res);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not obtain memory map for node %pOF\n",
			np);
		वापस ret;
	पूर्ण
	s->phys = res.start;

	s->iosize = resource_size(&res);
	अगर (s->iosize != माप(uपूर्णांक8_t) &&
	    s->iosize != माप(uपूर्णांक16_t) &&
	    s->iosize != माप(uपूर्णांक32_t)) अणु
		dev_err(&pdev->dev, "only 8/16/32-bit registers are supported\n");
		वापस -EINVAL;
	पूर्ण

	iprop = of_get_property(np, "mux-mask", &len);
	अगर (!iprop || len != माप(uपूर्णांक32_t)) अणु
		dev_err(&pdev->dev, "missing or invalid mux-mask property\n");
		वापस -ENODEV;
	पूर्ण
	अगर (be32_to_cpup(iprop) >= BIT(s->iosize * 8)) अणु
		dev_err(&pdev->dev, "only 8/16/32-bit registers are supported\n");
		वापस -EINVAL;
	पूर्ण
	s->mask = be32_to_cpup(iprop);

	/*
	 * Verअगरy that the 'reg' property of each child MDIO bus करोes not
	 * set any bits outside of the 'mask'.
	 */
	क्रम_each_available_child_of_node(np, np2) अणु
		iprop = of_get_property(np2, "reg", &len);
		अगर (!iprop || len != माप(uपूर्णांक32_t)) अणु
			dev_err(&pdev->dev, "mdio-mux child node %pOF is "
				"missing a 'reg' property\n", np2);
			of_node_put(np2);
			वापस -ENODEV;
		पूर्ण
		अगर (be32_to_cpup(iprop) & ~s->mask) अणु
			dev_err(&pdev->dev, "mdio-mux child node %pOF has "
				"a 'reg' value with unmasked bits\n",
				np2);
			of_node_put(np2);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	ret = mdio_mux_init(&pdev->dev, pdev->dev.of_node,
			    mdio_mux_mmioreg_चयन_fn,
			    &s->mux_handle, s, शून्य);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"failed to register mdio-mux bus %pOF\n", np);
		वापस ret;
	पूर्ण

	pdev->dev.platक्रमm_data = s;

	वापस 0;
पूर्ण

अटल पूर्णांक mdio_mux_mmioreg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mdio_mux_mmioreg_state *s = dev_get_platdata(&pdev->dev);

	mdio_mux_uninit(s->mux_handle);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mdio_mux_mmioreg_match[] = अणु
	अणु
		.compatible = "mdio-mux-mmioreg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mdio_mux_mmioreg_match);

अटल काष्ठा platक्रमm_driver mdio_mux_mmioreg_driver = अणु
	.driver = अणु
		.name		= "mdio-mux-mmioreg",
		.of_match_table = mdio_mux_mmioreg_match,
	पूर्ण,
	.probe		= mdio_mux_mmioreg_probe,
	.हटाओ		= mdio_mux_mmioreg_हटाओ,
पूर्ण;

module_platक्रमm_driver(mdio_mux_mmioreg_driver);

MODULE_AUTHOR("Timur Tabi <timur@freescale.com>");
MODULE_DESCRIPTION("Memory-mapped device MDIO MUX driver");
MODULE_LICENSE("GPL v2");
