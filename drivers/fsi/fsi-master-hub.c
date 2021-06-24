<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * FSI hub master driver
 *
 * Copyright (C) IBM Corporation 2016
 */

#समावेश <linux/delay.h>
#समावेश <linux/fsi.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश "fsi-master.h"

#घोषणा FSI_ENGID_HUB_MASTER		0x1c

#घोषणा FSI_LINK_ENABLE_SETUP_TIME	10	/* in mS */

/*
 * FSI hub master support
 *
 * A hub master increases the number of potential target devices that the
 * primary FSI master can access. For each link a primary master supports,
 * each of those links can in turn be chained to a hub master with multiple
 * links of its own.
 *
 * The hub is controlled by a set of control रेजिस्टरs exposed as a regular fsi
 * device (the hub->upstream device), and provides access to the करोwnstream FSI
 * bus as through an address range on the slave itself (->addr and ->size).
 *
 * [This dअगरfers from "cascaded" masters, which expose the entire करोwnstream
 * bus entirely through the fsi device address range, and so have a smaller
 * accessible address space.]
 */
काष्ठा fsi_master_hub अणु
	काष्ठा fsi_master	master;
	काष्ठा fsi_device	*upstream;
	uपूर्णांक32_t		addr, size;	/* slave-relative addr of */
						/* master address space */
पूर्ण;

#घोषणा to_fsi_master_hub(m) container_of(m, काष्ठा fsi_master_hub, master)

अटल पूर्णांक hub_master_पढ़ो(काष्ठा fsi_master *master, पूर्णांक link,
			uपूर्णांक8_t id, uपूर्णांक32_t addr, व्योम *val, माप_प्रकार size)
अणु
	काष्ठा fsi_master_hub *hub = to_fsi_master_hub(master);

	अगर (id != 0)
		वापस -EINVAL;

	addr += hub->addr + (link * FSI_HUB_LINK_SIZE);
	वापस fsi_slave_पढ़ो(hub->upstream->slave, addr, val, size);
पूर्ण

अटल पूर्णांक hub_master_ग_लिखो(काष्ठा fsi_master *master, पूर्णांक link,
			uपूर्णांक8_t id, uपूर्णांक32_t addr, स्थिर व्योम *val, माप_प्रकार size)
अणु
	काष्ठा fsi_master_hub *hub = to_fsi_master_hub(master);

	अगर (id != 0)
		वापस -EINVAL;

	addr += hub->addr + (link * FSI_HUB_LINK_SIZE);
	वापस fsi_slave_ग_लिखो(hub->upstream->slave, addr, val, size);
पूर्ण

अटल पूर्णांक hub_master_अवरोध(काष्ठा fsi_master *master, पूर्णांक link)
अणु
	uपूर्णांक32_t addr;
	__be32 cmd;

	addr = 0x4;
	cmd = cpu_to_be32(0xc0de0000);

	वापस hub_master_ग_लिखो(master, link, 0, addr, &cmd, माप(cmd));
पूर्ण

अटल पूर्णांक hub_master_link_enable(काष्ठा fsi_master *master, पूर्णांक link,
				  bool enable)
अणु
	काष्ठा fsi_master_hub *hub = to_fsi_master_hub(master);
	पूर्णांक idx, bit;
	__be32 reg;
	पूर्णांक rc;

	idx = link / 32;
	bit = link % 32;

	reg = cpu_to_be32(0x80000000 >> bit);

	अगर (!enable)
		वापस fsi_device_ग_लिखो(hub->upstream, FSI_MCENP0 + (4 * idx),
					&reg, 4);

	rc = fsi_device_ग_लिखो(hub->upstream, FSI_MSENP0 + (4 * idx), &reg, 4);
	अगर (rc)
		वापस rc;

	mdelay(FSI_LINK_ENABLE_SETUP_TIME);

	वापस 0;
पूर्ण

अटल व्योम hub_master_release(काष्ठा device *dev)
अणु
	काष्ठा fsi_master_hub *hub = to_fsi_master_hub(dev_to_fsi_master(dev));

	kमुक्त(hub);
पूर्ण

/* mmode encoders */
अटल अंतरभूत u32 fsi_mmode_crs0(u32 x)
अणु
	वापस (x & FSI_MMODE_CRS0MASK) << FSI_MMODE_CRS0SHFT;
पूर्ण

अटल अंतरभूत u32 fsi_mmode_crs1(u32 x)
अणु
	वापस (x & FSI_MMODE_CRS1MASK) << FSI_MMODE_CRS1SHFT;
पूर्ण

अटल पूर्णांक hub_master_init(काष्ठा fsi_master_hub *hub)
अणु
	काष्ठा fsi_device *dev = hub->upstream;
	__be32 reg;
	पूर्णांक rc;

	reg = cpu_to_be32(FSI_MRESP_RST_ALL_MASTER | FSI_MRESP_RST_ALL_LINK
			| FSI_MRESP_RST_MCR | FSI_MRESP_RST_PYE);
	rc = fsi_device_ग_लिखो(dev, FSI_MRESP0, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	/* Initialize the MFSI (hub master) engine */
	reg = cpu_to_be32(FSI_MRESP_RST_ALL_MASTER | FSI_MRESP_RST_ALL_LINK
			| FSI_MRESP_RST_MCR | FSI_MRESP_RST_PYE);
	rc = fsi_device_ग_लिखो(dev, FSI_MRESP0, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	reg = cpu_to_be32(FSI_MECTRL_EOAE | FSI_MECTRL_P8_AUTO_TERM);
	rc = fsi_device_ग_लिखो(dev, FSI_MECTRL, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	reg = cpu_to_be32(FSI_MMODE_EIP | FSI_MMODE_ECRC | FSI_MMODE_EPC
			| fsi_mmode_crs0(1) | fsi_mmode_crs1(1)
			| FSI_MMODE_P8_TO_LSB);
	rc = fsi_device_ग_लिखो(dev, FSI_MMODE, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	reg = cpu_to_be32(0xffff0000);
	rc = fsi_device_ग_लिखो(dev, FSI_MDLYR, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	reg = cpu_to_be32(~0);
	rc = fsi_device_ग_लिखो(dev, FSI_MSENP0, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	/* Leave enabled दीर्घ enough क्रम master logic to set up */
	mdelay(FSI_LINK_ENABLE_SETUP_TIME);

	rc = fsi_device_ग_लिखो(dev, FSI_MCENP0, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	rc = fsi_device_पढ़ो(dev, FSI_MAEB, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	reg = cpu_to_be32(FSI_MRESP_RST_ALL_MASTER | FSI_MRESP_RST_ALL_LINK);
	rc = fsi_device_ग_लिखो(dev, FSI_MRESP0, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	rc = fsi_device_पढ़ो(dev, FSI_MLEVP0, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	/* Reset the master bridge */
	reg = cpu_to_be32(FSI_MRESB_RST_GEN);
	rc = fsi_device_ग_लिखो(dev, FSI_MRESB0, &reg, माप(reg));
	अगर (rc)
		वापस rc;

	reg = cpu_to_be32(FSI_MRESB_RST_ERR);
	वापस fsi_device_ग_लिखो(dev, FSI_MRESB0, &reg, माप(reg));
पूर्ण

अटल पूर्णांक hub_master_probe(काष्ठा device *dev)
अणु
	काष्ठा fsi_device *fsi_dev = to_fsi_dev(dev);
	काष्ठा fsi_master_hub *hub;
	uपूर्णांक32_t reg, links;
	__be32 __reg;
	पूर्णांक rc;

	rc = fsi_device_पढ़ो(fsi_dev, FSI_MVER, &__reg, माप(__reg));
	अगर (rc)
		वापस rc;

	reg = be32_to_cpu(__reg);
	links = (reg >> 8) & 0xff;
	dev_dbg(dev, "hub version %08x (%d links)\n", reg, links);

	rc = fsi_slave_claim_range(fsi_dev->slave, FSI_HUB_LINK_OFFSET,
			FSI_HUB_LINK_SIZE * links);
	अगर (rc) अणु
		dev_err(dev, "can't claim slave address range for links");
		वापस rc;
	पूर्ण

	hub = kzalloc(माप(*hub), GFP_KERNEL);
	अगर (!hub) अणु
		rc = -ENOMEM;
		जाओ err_release;
	पूर्ण

	hub->addr = FSI_HUB_LINK_OFFSET;
	hub->size = FSI_HUB_LINK_SIZE * links;
	hub->upstream = fsi_dev;

	hub->master.dev.parent = dev;
	hub->master.dev.release = hub_master_release;
	hub->master.dev.of_node = of_node_get(dev_of_node(dev));

	hub->master.n_links = links;
	hub->master.पढ़ो = hub_master_पढ़ो;
	hub->master.ग_लिखो = hub_master_ग_लिखो;
	hub->master.send_अवरोध = hub_master_अवरोध;
	hub->master.link_enable = hub_master_link_enable;

	dev_set_drvdata(dev, hub);

	hub_master_init(hub);

	rc = fsi_master_रेजिस्टर(&hub->master);
	अगर (rc)
		जाओ err_release;

	/* At this poपूर्णांक, fsi_master_रेजिस्टर perक्रमms the device_initialize(),
	 * and holds the sole reference on master.dev. This means the device
	 * will be मुक्तd (via ->release) during any subsequent call to
	 * fsi_master_unरेजिस्टर.  We add our own reference to it here, so we
	 * can perक्रमm cleanup (in _हटाओ()) without it being मुक्तd beक्रमe
	 * we're पढ़ोy.
	 */
	get_device(&hub->master.dev);
	वापस 0;

err_release:
	fsi_slave_release_range(fsi_dev->slave, FSI_HUB_LINK_OFFSET,
			FSI_HUB_LINK_SIZE * links);
	वापस rc;
पूर्ण

अटल पूर्णांक hub_master_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा fsi_master_hub *hub = dev_get_drvdata(dev);

	fsi_master_unरेजिस्टर(&hub->master);
	fsi_slave_release_range(hub->upstream->slave, hub->addr, hub->size);
	of_node_put(hub->master.dev.of_node);

	/*
	 * master.dev will likely be ->release()ed after this, which मुक्त()s
	 * the hub
	 */
	put_device(&hub->master.dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsi_device_id hub_master_ids[] = अणु
	अणु
		.engine_type = FSI_ENGID_HUB_MASTER,
		.version = FSI_VERSION_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा fsi_driver hub_master_driver = अणु
	.id_table = hub_master_ids,
	.drv = अणु
		.name = "fsi-master-hub",
		.bus = &fsi_bus_type,
		.probe = hub_master_probe,
		.हटाओ = hub_master_हटाओ,
	पूर्ण
पूर्ण;

module_fsi_driver(hub_master_driver);
MODULE_LICENSE("GPL");
