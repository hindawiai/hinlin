<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale PowerQUICC Ethernet Driver -- MIIM bus implementation
 * Provides Bus पूर्णांकerface क्रम MIIM regs
 *
 * Author: Andy Fleming <afleming@मुक्तscale.com>
 * Modअगरier: Sandeep Gopalpet <sandeep.kumar@मुक्तscale.com>
 *
 * Copyright 2002-2004, 2008-2009 Freescale Semiconductor, Inc.
 *
 * Based on gianfar_mii.c and ucc_geth_mii.c (Li Yang, Kim Phillips)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#अगर IS_ENABLED(CONFIG_UCC_GETH)
#समावेश <soc/fsl/qe/ucc.h>
#पूर्ण_अगर

#समावेश "gianfar.h"

#घोषणा MIIMIND_BUSY		0x00000001
#घोषणा MIIMIND_NOTVALID	0x00000004
#घोषणा MIIMCFG_INIT_VALUE	0x00000007
#घोषणा MIIMCFG_RESET		0x80000000

#घोषणा MII_READ_COMMAND	0x00000001

काष्ठा fsl_pq_mii अणु
	u32 miimcfg;	/* MII management configuration reg */
	u32 miimcom;	/* MII management command reg */
	u32 miimadd;	/* MII management address reg */
	u32 miimcon;	/* MII management control reg */
	u32 miimstat;	/* MII management status reg */
	u32 miimind;	/* MII management indication reg */
पूर्ण;

काष्ठा fsl_pq_mdio अणु
	u8 res1[16];
	u32 ievenपंचांग;	/* MDIO Interrupt event रेजिस्टर (क्रम etsec2)*/
	u32 imaskm;	/* MDIO Interrupt mask रेजिस्टर (क्रम etsec2)*/
	u8 res2[4];
	u32 emapm;	/* MDIO Event mapping रेजिस्टर (क्रम etsec2)*/
	u8 res3[1280];
	काष्ठा fsl_pq_mii mii;
	u8 res4[28];
	u32 utbipar;	/* TBI phy address reg (only on UCC) */
	u8 res5[2728];
पूर्ण __packed;

/* Number of microseconds to रुको क्रम an MII रेजिस्टर to respond */
#घोषणा MII_TIMEOUT	1000

काष्ठा fsl_pq_mdio_priv अणु
	व्योम __iomem *map;
	काष्ठा fsl_pq_mii __iomem *regs;
पूर्ण;

/*
 * Per-device-type data.  Each type of device tree node that we support माला_लो
 * one of these.
 *
 * @mii_offset: the offset of the MII रेजिस्टरs within the memory map of the
 * node.  Some nodes define only the MII रेजिस्टरs, and some define the whole
 * MAC (which includes the MII रेजिस्टरs).
 *
 * @get_tbipa: determines the address of the TBIPA रेजिस्टर
 *
 * @ucc_configure: a special function क्रम extra QE configuration
 */
काष्ठा fsl_pq_mdio_data अणु
	अचिन्हित पूर्णांक mii_offset;	/* offset of the MII रेजिस्टरs */
	uपूर्णांक32_t __iomem * (*get_tbipa)(व्योम __iomem *p);
	व्योम (*ucc_configure)(phys_addr_t start, phys_addr_t end);
पूर्ण;

/*
 * Write value to the PHY at mii_id at रेजिस्टर regnum, on the bus attached
 * to the local पूर्णांकerface, which may be dअगरferent from the generic mdio bus
 * (tied to a single पूर्णांकerface), रुकोing until the ग_लिखो is करोne beक्रमe
 * वापसing. This is helpful in programming पूर्णांकerfaces like the TBI which
 * control पूर्णांकerfaces like onchip SERDES and are always tied to the local
 * mdio pins, which may not be the same as प्रणाली mdio bus, used क्रम
 * controlling the बाह्यal PHYs, क्रम example.
 */
अटल पूर्णांक fsl_pq_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum,
		u16 value)
अणु
	काष्ठा fsl_pq_mdio_priv *priv = bus->priv;
	काष्ठा fsl_pq_mii __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक समयout;

	/* Set the PHY address and the रेजिस्टर address we want to ग_लिखो */
	ioग_लिखो32be((mii_id << 8) | regnum, &regs->miimadd);

	/* Write out the value we want */
	ioग_लिखो32be(value, &regs->miimcon);

	/* Wait क्रम the transaction to finish */
	समयout = MII_TIMEOUT;
	जबतक ((ioपढ़ो32be(&regs->miimind) & MIIMIND_BUSY) && समयout) अणु
		cpu_relax();
		समयout--;
	पूर्ण

	वापस समयout ? 0 : -ETIMEDOUT;
पूर्ण

/*
 * Read the bus क्रम PHY at addr mii_id, रेजिस्टर regnum, and वापस the value.
 * Clears miimcom first.
 *
 * All PHY operation करोne on the bus attached to the local पूर्णांकerface, which
 * may be dअगरferent from the generic mdio bus.  This is helpful in programming
 * पूर्णांकerfaces like the TBI which, in turn, control पूर्णांकerfaces like on-chip
 * SERDES and are always tied to the local mdio pins, which may not be the
 * same as प्रणाली mdio bus, used क्रम controlling the बाह्यal PHYs, क्रम eg.
 */
अटल पूर्णांक fsl_pq_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा fsl_pq_mdio_priv *priv = bus->priv;
	काष्ठा fsl_pq_mii __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक समयout;
	u16 value;

	/* Set the PHY address and the रेजिस्टर address we want to पढ़ो */
	ioग_लिखो32be((mii_id << 8) | regnum, &regs->miimadd);

	/* Clear miimcom, and then initiate a पढ़ो */
	ioग_लिखो32be(0, &regs->miimcom);
	ioग_लिखो32be(MII_READ_COMMAND, &regs->miimcom);

	/* Wait क्रम the transaction to finish, normally less than 100us */
	समयout = MII_TIMEOUT;
	जबतक ((ioपढ़ो32be(&regs->miimind) &
	       (MIIMIND_NOTVALID | MIIMIND_BUSY)) && समयout) अणु
		cpu_relax();
		समयout--;
	पूर्ण

	अगर (!समयout)
		वापस -ETIMEDOUT;

	/* Grab the value of the रेजिस्टर from miimstat */
	value = ioपढ़ो32be(&regs->miimstat);

	dev_dbg(&bus->dev, "read %04x from address %x/%x\n", value, mii_id, regnum);
	वापस value;
पूर्ण

/* Reset the MIIM रेजिस्टरs, and रुको क्रम the bus to मुक्त */
अटल पूर्णांक fsl_pq_mdio_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा fsl_pq_mdio_priv *priv = bus->priv;
	काष्ठा fsl_pq_mii __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक समयout;

	mutex_lock(&bus->mdio_lock);

	/* Reset the management पूर्णांकerface */
	ioग_लिखो32be(MIIMCFG_RESET, &regs->miimcfg);

	/* Setup the MII Mgmt घड़ी speed */
	ioग_लिखो32be(MIIMCFG_INIT_VALUE, &regs->miimcfg);

	/* Wait until the bus is मुक्त */
	समयout = MII_TIMEOUT;
	जबतक ((ioपढ़ो32be(&regs->miimind) & MIIMIND_BUSY) && समयout) अणु
		cpu_relax();
		समयout--;
	पूर्ण

	mutex_unlock(&bus->mdio_lock);

	अगर (!समयout) अणु
		dev_err(&bus->dev, "timeout waiting for MII bus\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_GIANFAR)
/*
 * Return the TBIPA address, starting from the address
 * of the mapped GFAR MDIO रेजिस्टरs (काष्ठा gfar)
 * This is mildly evil, but so is our hardware क्रम करोing this.
 * Also, we have to cast back to काष्ठा gfar because of
 * definition weirdness करोne in gianfar.h.
 */
अटल uपूर्णांक32_t __iomem *get_gfar_tbipa_from_mdio(व्योम __iomem *p)
अणु
	काष्ठा gfar __iomem *enet_regs = p;

	वापस &enet_regs->tbipa;
पूर्ण

/*
 * Return the TBIPA address, starting from the address
 * of the mapped GFAR MII रेजिस्टरs (gfar_mii_regs[] within काष्ठा gfar)
 */
अटल uपूर्णांक32_t __iomem *get_gfar_tbipa_from_mii(व्योम __iomem *p)
अणु
	वापस get_gfar_tbipa_from_mdio(container_of(p, काष्ठा gfar, gfar_mii_regs));
पूर्ण

/*
 * Return the TBIPAR address क्रम an eTSEC2 node
 */
अटल uपूर्णांक32_t __iomem *get_etsec_tbipa(व्योम __iomem *p)
अणु
	वापस p;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_UCC_GETH)
/*
 * Return the TBIPAR address क्रम a QE MDIO node, starting from the address
 * of the mapped MII रेजिस्टरs (काष्ठा fsl_pq_mii)
 */
अटल uपूर्णांक32_t __iomem *get_ucc_tbipa(व्योम __iomem *p)
अणु
	काष्ठा fsl_pq_mdio __iomem *mdio = container_of(p, काष्ठा fsl_pq_mdio, mii);

	वापस &mdio->utbipar;
पूर्ण

/*
 * Find the UCC node that controls the given MDIO node
 *
 * For some reason, the QE MDIO nodes are not children of the UCC devices
 * that control them.  Thereक्रमe, we need to scan all UCC nodes looking क्रम
 * the one that encompases the given MDIO node.  We करो this by comparing
 * physical addresses.  The 'start' and 'end' addresses of the MDIO node are
 * passed, and the correct UCC node will cover the entire address range.
 *
 * This assumes that there is only one QE MDIO node in the entire device tree.
 */
अटल व्योम ucc_configure(phys_addr_t start, phys_addr_t end)
अणु
	अटल bool found_mii_master;
	काष्ठा device_node *np = शून्य;

	अगर (found_mii_master)
		वापस;

	क्रम_each_compatible_node(np, शून्य, "ucc_geth") अणु
		काष्ठा resource res;
		स्थिर uपूर्णांक32_t *iprop;
		uपूर्णांक32_t id;
		पूर्णांक ret;

		ret = of_address_to_resource(np, 0, &res);
		अगर (ret < 0) अणु
			pr_debug("fsl-pq-mdio: no address range in node %pOF\n",
				 np);
			जारी;
		पूर्ण

		/* अगर our mdio regs fall within this UCC regs range */
		अगर ((start < res.start) || (end > res.end))
			जारी;

		iprop = of_get_property(np, "cell-index", शून्य);
		अगर (!iprop) अणु
			iprop = of_get_property(np, "device-id", शून्य);
			अगर (!iprop) अणु
				pr_debug("fsl-pq-mdio: no UCC ID in node %pOF\n",
					 np);
				जारी;
			पूर्ण
		पूर्ण

		id = be32_to_cpup(iprop);

		/*
		 * cell-index and device-id क्रम QE nodes are
		 * numbered from 1, not 0.
		 */
		अगर (ucc_set_qe_mux_mii_mng(id - 1) < 0) अणु
			pr_debug("fsl-pq-mdio: invalid UCC ID in node %pOF\n",
				 np);
			जारी;
		पूर्ण

		pr_debug("fsl-pq-mdio: setting node UCC%u to MII master\n", id);
		found_mii_master = true;
	पूर्ण
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id fsl_pq_mdio_match[] = अणु
#अगर IS_ENABLED(CONFIG_GIANFAR)
	अणु
		.compatible = "fsl,gianfar-tbi",
		.data = &(काष्ठा fsl_pq_mdio_data) अणु
			.mii_offset = 0,
			.get_tbipa = get_gfar_tbipa_from_mii,
		पूर्ण,
	पूर्ण,
	अणु
		.compatible = "fsl,gianfar-mdio",
		.data = &(काष्ठा fsl_pq_mdio_data) अणु
			.mii_offset = 0,
			.get_tbipa = get_gfar_tbipa_from_mii,
		पूर्ण,
	पूर्ण,
	अणु
		.type = "mdio",
		.compatible = "gianfar",
		.data = &(काष्ठा fsl_pq_mdio_data) अणु
			.mii_offset = दुरत्व(काष्ठा fsl_pq_mdio, mii),
			.get_tbipa = get_gfar_tbipa_from_mdio,
		पूर्ण,
	पूर्ण,
	अणु
		.compatible = "fsl,etsec2-tbi",
		.data = &(काष्ठा fsl_pq_mdio_data) अणु
			.mii_offset = दुरत्व(काष्ठा fsl_pq_mdio, mii),
			.get_tbipa = get_etsec_tbipa,
		पूर्ण,
	पूर्ण,
	अणु
		.compatible = "fsl,etsec2-mdio",
		.data = &(काष्ठा fsl_pq_mdio_data) अणु
			.mii_offset = दुरत्व(काष्ठा fsl_pq_mdio, mii),
			.get_tbipa = get_etsec_tbipa,
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_UCC_GETH)
	अणु
		.compatible = "fsl,ucc-mdio",
		.data = &(काष्ठा fsl_pq_mdio_data) अणु
			.mii_offset = 0,
			.get_tbipa = get_ucc_tbipa,
			.ucc_configure = ucc_configure,
		पूर्ण,
	पूर्ण,
	अणु
		/* Legacy UCC MDIO node */
		.type = "mdio",
		.compatible = "ucc_geth_phy",
		.data = &(काष्ठा fsl_pq_mdio_data) अणु
			.mii_offset = 0,
			.get_tbipa = get_ucc_tbipa,
			.ucc_configure = ucc_configure,
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	/* No Kconfig option क्रम Fman support yet */
	अणु
		.compatible = "fsl,fman-mdio",
		.data = &(काष्ठा fsl_pq_mdio_data) अणु
			.mii_offset = 0,
			/* Fman TBI operations are handled अन्यथाwhere */
		पूर्ण,
	पूर्ण,

	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_pq_mdio_match);

अटल व्योम set_tbipa(स्थिर u32 tbipa_val, काष्ठा platक्रमm_device *pdev,
		      uपूर्णांक32_t __iomem * (*get_tbipa)(व्योम __iomem *),
		      व्योम __iomem *reg_map, काष्ठा resource *reg_res)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	uपूर्णांक32_t __iomem *tbipa;
	bool tbipa_mapped;

	tbipa = of_iomap(np, 1);
	अगर (tbipa) अणु
		tbipa_mapped = true;
	पूर्ण अन्यथा अणु
		tbipa_mapped = false;
		tbipa = (*get_tbipa)(reg_map);

		/*
		 * Add consistency check to make sure TBI is contained within
		 * the mapped range (not because we would get a segfault,
		 * rather to catch bugs in computing TBI address). Prपूर्णांक error
		 * message but जारी anyway.
		 */
		अगर ((व्योम *)tbipa > reg_map + resource_size(reg_res) - 4)
			dev_err(&pdev->dev, "invalid register map (should be at least 0x%04zx to contain TBI address)\n",
				((व्योम *)tbipa - reg_map) + 4);
	पूर्ण

	ioग_लिखो32be(be32_to_cpu(tbipa_val), tbipa);

	अगर (tbipa_mapped)
		iounmap(tbipa);
पूर्ण

अटल पूर्णांक fsl_pq_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id =
		of_match_device(fsl_pq_mdio_match, &pdev->dev);
	स्थिर काष्ठा fsl_pq_mdio_data *data;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource res;
	काष्ठा device_node *tbi;
	काष्ठा fsl_pq_mdio_priv *priv;
	काष्ठा mii_bus *new_bus;
	पूर्णांक err;

	अगर (!id) अणु
		dev_err(&pdev->dev, "Failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	data = id->data;

	dev_dbg(&pdev->dev, "found %s compatible node\n", id->compatible);

	new_bus = mdiobus_alloc_size(माप(*priv));
	अगर (!new_bus)
		वापस -ENOMEM;

	priv = new_bus->priv;
	new_bus->name = "Freescale PowerQUICC MII Bus";
	new_bus->पढ़ो = &fsl_pq_mdio_पढ़ो;
	new_bus->ग_लिखो = &fsl_pq_mdio_ग_लिखो;
	new_bus->reset = &fsl_pq_mdio_reset;

	err = of_address_to_resource(np, 0, &res);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "could not obtain address information\n");
		जाओ error;
	पूर्ण

	snम_लिखो(new_bus->id, MII_BUS_ID_SIZE, "%pOFn@%llx", np,
		 (अचिन्हित दीर्घ दीर्घ)res.start);

	priv->map = of_iomap(np, 0);
	अगर (!priv->map) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	/*
	 * Some device tree nodes represent only the MII रेजिस्टरs, and
	 * others represent the MAC and MII रेजिस्टरs.  The 'mii_offset' field
	 * contains the offset of the MII रेजिस्टरs inside the mapped रेजिस्टर
	 * space.
	 */
	अगर (data->mii_offset > resource_size(&res)) अणु
		dev_err(&pdev->dev, "invalid register map\n");
		err = -EINVAL;
		जाओ error;
	पूर्ण
	priv->regs = priv->map + data->mii_offset;

	new_bus->parent = &pdev->dev;
	platक्रमm_set_drvdata(pdev, new_bus);

	अगर (data->get_tbipa) अणु
		क्रम_each_child_of_node(np, tbi) अणु
			अगर (of_node_is_type(tbi, "tbi-phy")) अणु
				dev_dbg(&pdev->dev, "found TBI PHY node %pOFP\n",
					tbi);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (tbi) अणु
			स्थिर u32 *prop = of_get_property(tbi, "reg", शून्य);
			अगर (!prop) अणु
				dev_err(&pdev->dev,
					"missing 'reg' property in node %pOF\n",
					tbi);
				err = -EBUSY;
				जाओ error;
			पूर्ण
			set_tbipa(*prop, pdev,
				  data->get_tbipa, priv->map, &res);
		पूर्ण
	पूर्ण

	अगर (data->ucc_configure)
		data->ucc_configure(res.start, res.end);

	err = of_mdiobus_रेजिस्टर(new_bus, np);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot register %s as MDIO bus\n",
			new_bus->name);
		जाओ error;
	पूर्ण

	वापस 0;

error:
	अगर (priv->map)
		iounmap(priv->map);

	kमुक्त(new_bus);

	वापस err;
पूर्ण


अटल पूर्णांक fsl_pq_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *device = &pdev->dev;
	काष्ठा mii_bus *bus = dev_get_drvdata(device);
	काष्ठा fsl_pq_mdio_priv *priv = bus->priv;

	mdiobus_unरेजिस्टर(bus);

	iounmap(priv->map);
	mdiobus_मुक्त(bus);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver fsl_pq_mdio_driver = अणु
	.driver = अणु
		.name = "fsl-pq_mdio",
		.of_match_table = fsl_pq_mdio_match,
	पूर्ण,
	.probe = fsl_pq_mdio_probe,
	.हटाओ = fsl_pq_mdio_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsl_pq_mdio_driver);

MODULE_LICENSE("GPL");
