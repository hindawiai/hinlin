<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tsi108/109 device setup code
 *
 * Maपूर्णांकained by Roy Zang < tie-fei.zang@मुक्तscale.com >
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/major.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/export.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_net.h>
#समावेश <यंत्र/tsi108.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <mm/mmu_decl.h>

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) करो अणु prपूर्णांकk(fmt); पूर्ण जबतक(0)
#अन्यथा
#घोषणा DBG(fmt...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल phys_addr_t tsi108_csr_base = -1;

phys_addr_t get_csrbase(व्योम)
अणु
	काष्ठा device_node *tsi;

	अगर (tsi108_csr_base != -1)
		वापस tsi108_csr_base;

	tsi = of_find_node_by_type(शून्य, "tsi-bridge");
	अगर (tsi) अणु
		अचिन्हित पूर्णांक size;
		स्थिर व्योम *prop = of_get_property(tsi, "reg", &size);
		tsi108_csr_base = of_translate_address(tsi, prop);
		of_node_put(tsi);
	पूर्ण
	वापस tsi108_csr_base;
पूर्ण

u32 get_vir_csrbase(व्योम)
अणु
	वापस (u32) (ioremap(get_csrbase(), 0x10000));
पूर्ण

EXPORT_SYMBOL(get_csrbase);
EXPORT_SYMBOL(get_vir_csrbase);

अटल पूर्णांक __init tsi108_eth_of_init(व्योम)
अणु
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा platक्रमm_device *tsi_eth_dev;
	काष्ठा resource res;
	पूर्णांक ret;

	क्रम_each_compatible_node(np, "network", "tsi108-ethernet") अणु
		काष्ठा resource r[2];
		काष्ठा device_node *phy, *mdio;
		hw_info tsi_eth_data;
		स्थिर अचिन्हित पूर्णांक *phy_id;
		स्थिर phandle *ph;

		स_रखो(r, 0, माप(r));
		स_रखो(&tsi_eth_data, 0, माप(tsi_eth_data));

		ret = of_address_to_resource(np, 0, &r[0]);
		DBG("%s: name:start->end = %s:%pR\n",
		    __func__, r[0].name, &r[0]);
		अगर (ret)
			जाओ err;

		r[1].name = "tx";
		r[1].start = irq_of_parse_and_map(np, 0);
		r[1].end = irq_of_parse_and_map(np, 0);
		r[1].flags = IORESOURCE_IRQ;
		DBG("%s: name:start->end = %s:%pR\n",
			__func__, r[1].name, &r[1]);

		tsi_eth_dev =
		    platक्रमm_device_रेजिस्टर_simple("tsi-ethernet", i++, &r[0],
						    1);

		अगर (IS_ERR(tsi_eth_dev)) अणु
			ret = PTR_ERR(tsi_eth_dev);
			जाओ err;
		पूर्ण

		of_get_mac_address(np, tsi_eth_data.mac_addr);

		ph = of_get_property(np, "mdio-handle", शून्य);
		mdio = of_find_node_by_phandle(*ph);
		ret = of_address_to_resource(mdio, 0, &res);
		of_node_put(mdio);
		अगर (ret)
			जाओ unreg;

		ph = of_get_property(np, "phy-handle", शून्य);
		phy = of_find_node_by_phandle(*ph);

		अगर (phy == शून्य) अणु
			ret = -ENODEV;
			जाओ unreg;
		पूर्ण

		phy_id = of_get_property(phy, "reg", शून्य);

		tsi_eth_data.regs = r[0].start;
		tsi_eth_data.phyregs = res.start;
		tsi_eth_data.phy = *phy_id;
		tsi_eth_data.irq_num = irq_of_parse_and_map(np, 0);

		/* Some boards with the TSI108 bridge (e.g. Holly)
		 * have a miswiring of the ethernet PHYs which
		 * requires a workaround.  The special
		 * "txc-rxc-delay-disable" property enables this
		 * workaround.  FIXME: Need to port the tsi108_eth
		 * driver itself to phylib and use a non-misleading
		 * name क्रम the workaround flag - it's not actually to
		 * करो with the model of PHY in use */
		अगर (of_get_property(phy, "txc-rxc-delay-disable", शून्य))
			tsi_eth_data.phy_type = TSI108_PHY_BCM54XX;
		of_node_put(phy);

		ret =
		    platक्रमm_device_add_data(tsi_eth_dev, &tsi_eth_data,
					     माप(hw_info));
		अगर (ret)
			जाओ unreg;
	पूर्ण
	वापस 0;
unreg:
	platक्रमm_device_unरेजिस्टर(tsi_eth_dev);
err:
	of_node_put(np);
	वापस ret;
पूर्ण

arch_initcall(tsi108_eth_of_init);
