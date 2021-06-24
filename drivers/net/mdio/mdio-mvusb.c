<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/usb.h>

#घोषणा USB_MARVELL_VID	0x1286

अटल स्थिर काष्ठा usb_device_id mvusb_mdio_table[] = अणु
	अणु USB_DEVICE(USB_MARVELL_VID, 0x1fa4) पूर्ण,

	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, mvusb_mdio_table);

क्रमागत अणु
	MVUSB_CMD_PREAMBLE0,
	MVUSB_CMD_PREAMBLE1,
	MVUSB_CMD_ADDR,
	MVUSB_CMD_VAL,
पूर्ण;

काष्ठा mvusb_mdio अणु
	काष्ठा usb_device *udev;
	काष्ठा mii_bus *mdio;

	__le16 buf[4];
पूर्ण;

अटल पूर्णांक mvusb_mdio_पढ़ो(काष्ठा mii_bus *mdio, पूर्णांक dev, पूर्णांक reg)
अणु
	काष्ठा mvusb_mdio *mvusb = mdio->priv;
	पूर्णांक err, alen;

	अगर (dev & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	mvusb->buf[MVUSB_CMD_ADDR] = cpu_to_le16(0xa400 | (dev << 5) | reg);

	err = usb_bulk_msg(mvusb->udev, usb_sndbulkpipe(mvusb->udev, 2),
			   mvusb->buf, 6, &alen, 100);
	अगर (err)
		वापस err;

	err = usb_bulk_msg(mvusb->udev, usb_rcvbulkpipe(mvusb->udev, 6),
			   &mvusb->buf[MVUSB_CMD_VAL], 2, &alen, 100);
	अगर (err)
		वापस err;

	वापस le16_to_cpu(mvusb->buf[MVUSB_CMD_VAL]);
पूर्ण

अटल पूर्णांक mvusb_mdio_ग_लिखो(काष्ठा mii_bus *mdio, पूर्णांक dev, पूर्णांक reg, u16 val)
अणु
	काष्ठा mvusb_mdio *mvusb = mdio->priv;
	पूर्णांक alen;

	अगर (dev & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	mvusb->buf[MVUSB_CMD_ADDR] = cpu_to_le16(0x8000 | (dev << 5) | reg);
	mvusb->buf[MVUSB_CMD_VAL]  = cpu_to_le16(val);

	वापस usb_bulk_msg(mvusb->udev, usb_sndbulkpipe(mvusb->udev, 2),
			    mvusb->buf, 8, &alen, 100);
पूर्ण

अटल पूर्णांक mvusb_mdio_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा device *dev = &पूर्णांकerface->dev;
	काष्ठा mvusb_mdio *mvusb;
	काष्ठा mii_bus *mdio;

	mdio = devm_mdiobus_alloc_size(dev, माप(*mvusb));
	अगर (!mdio)
		वापस -ENOMEM;

	mvusb = mdio->priv;
	mvusb->mdio = mdio;
	mvusb->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));

	/* Reversed from USB PCAPs, no idea what these mean. */
	mvusb->buf[MVUSB_CMD_PREAMBLE0] = cpu_to_le16(0xe800);
	mvusb->buf[MVUSB_CMD_PREAMBLE1] = cpu_to_le16(0x0001);

	snम_लिखो(mdio->id, MII_BUS_ID_SIZE, "mvusb-%s", dev_name(dev));
	mdio->name = mdio->id;
	mdio->parent = dev;
	mdio->पढ़ो = mvusb_mdio_पढ़ो;
	mdio->ग_लिखो = mvusb_mdio_ग_लिखो;

	usb_set_पूर्णांकfdata(पूर्णांकerface, mvusb);
	वापस of_mdiobus_रेजिस्टर(mdio, dev->of_node);
पूर्ण

अटल व्योम mvusb_mdio_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा mvusb_mdio *mvusb = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा usb_device *udev = mvusb->udev;

	mdiobus_unरेजिस्टर(mvusb->mdio);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	usb_put_dev(udev);
पूर्ण

अटल काष्ठा usb_driver mvusb_mdio_driver = अणु
	.name       = "mvusb_mdio",
	.id_table   = mvusb_mdio_table,
	.probe      = mvusb_mdio_probe,
	.disconnect = mvusb_mdio_disconnect,
पूर्ण;

module_usb_driver(mvusb_mdio_driver);

MODULE_AUTHOR("Tobias Waldekranz <tobias@waldekranz.com>");
MODULE_DESCRIPTION("Marvell USB MDIO Adapter");
MODULE_LICENSE("GPL");
