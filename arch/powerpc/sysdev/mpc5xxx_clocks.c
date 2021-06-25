<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * 	mpc5xxx_get_bus_frequency - Find the bus frequency क्रम a device
 * 	@node:	device node
 *
 * 	Returns bus frequency (IPS on MPC512x, IPB on MPC52xx),
 * 	or 0 अगर the bus frequency cannot be found.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/mpc5xxx.h>

अचिन्हित दीर्घ mpc5xxx_get_bus_frequency(काष्ठा device_node *node)
अणु
	स्थिर अचिन्हित पूर्णांक *p_bus_freq = शून्य;

	of_node_get(node);
	जबतक (node) अणु
		p_bus_freq = of_get_property(node, "bus-frequency", शून्य);
		अगर (p_bus_freq)
			अवरोध;

		node = of_get_next_parent(node);
	पूर्ण
	of_node_put(node);

	वापस p_bus_freq ? *p_bus_freq : 0;
पूर्ण
EXPORT_SYMBOL(mpc5xxx_get_bus_frequency);
