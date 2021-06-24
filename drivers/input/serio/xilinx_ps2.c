<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Xilinx XPS PS/2 device driver
 *
 * (c) 2005 MontaVista Software, Inc.
 * (c) 2008 Xilinx, Inc.
 */


#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा DRIVER_NAME		"xilinx_ps2"

/* Register offsets क्रम the xps2 device */
#घोषणा XPS2_SRST_OFFSET	0x00000000 /* Software Reset रेजिस्टर */
#घोषणा XPS2_STATUS_OFFSET	0x00000004 /* Status रेजिस्टर */
#घोषणा XPS2_RX_DATA_OFFSET	0x00000008 /* Receive Data रेजिस्टर */
#घोषणा XPS2_TX_DATA_OFFSET	0x0000000C /* Transmit Data रेजिस्टर */
#घोषणा XPS2_GIER_OFFSET	0x0000002C /* Global Interrupt Enable reg */
#घोषणा XPS2_IPISR_OFFSET	0x00000030 /* Interrupt Status रेजिस्टर */
#घोषणा XPS2_IPIER_OFFSET	0x00000038 /* Interrupt Enable रेजिस्टर */

/* Reset Register Bit Definitions */
#घोषणा XPS2_SRST_RESET		0x0000000A /* Software Reset  */

/* Status Register Bit Positions */
#घोषणा XPS2_STATUS_RX_FULL	0x00000001 /* Receive Full  */
#घोषणा XPS2_STATUS_TX_FULL	0x00000002 /* Transmit Full  */

/*
 * Bit definitions क्रम ISR/IER रेजिस्टरs. Both the रेजिस्टरs have the same bit
 * definitions and are only defined once.
 */
#घोषणा XPS2_IPIXR_WDT_TOUT	0x00000001 /* Watchकरोg Timeout Interrupt */
#घोषणा XPS2_IPIXR_TX_NOACK	0x00000002 /* Transmit No ACK Interrupt */
#घोषणा XPS2_IPIXR_TX_ACK	0x00000004 /* Transmit ACK (Data) Interrupt */
#घोषणा XPS2_IPIXR_RX_OVF	0x00000008 /* Receive Overflow Interrupt */
#घोषणा XPS2_IPIXR_RX_ERR	0x00000010 /* Receive Error Interrupt */
#घोषणा XPS2_IPIXR_RX_FULL	0x00000020 /* Receive Data Interrupt */

/* Mask क्रम all the Transmit Interrupts */
#घोषणा XPS2_IPIXR_TX_ALL	(XPS2_IPIXR_TX_NOACK | XPS2_IPIXR_TX_ACK)

/* Mask क्रम all the Receive Interrupts */
#घोषणा XPS2_IPIXR_RX_ALL	(XPS2_IPIXR_RX_OVF | XPS2_IPIXR_RX_ERR |  \
				 XPS2_IPIXR_RX_FULL)

/* Mask क्रम all the Interrupts */
#घोषणा XPS2_IPIXR_ALL		(XPS2_IPIXR_TX_ALL | XPS2_IPIXR_RX_ALL |  \
				 XPS2_IPIXR_WDT_TOUT)

/* Global Interrupt Enable mask */
#घोषणा XPS2_GIER_GIE_MASK	0x80000000

काष्ठा xps2data अणु
	पूर्णांक irq;
	spinlock_t lock;
	व्योम __iomem *base_address;	/* virt. address of control रेजिस्टरs */
	अचिन्हित पूर्णांक flags;
	काष्ठा serio *serio;		/* serio */
	काष्ठा device *dev;
पूर्ण;

/************************************/
/* XPS PS/2 data transmission calls */
/************************************/

/**
 * xps2_recv() - attempts to receive a byte from the PS/2 port.
 * @drvdata:	poपूर्णांकer to ps2 device निजी data काष्ठाure
 * @byte:	address where the पढ़ो data will be copied
 *
 * If there is any data available in the PS/2 receiver, this functions पढ़ोs
 * the data, otherwise it वापसs error.
 */
अटल पूर्णांक xps2_recv(काष्ठा xps2data *drvdata, u8 *byte)
अणु
	u32 sr;
	पूर्णांक status = -1;

	/* If there is data available in the PS/2 receiver, पढ़ो it */
	sr = in_be32(drvdata->base_address + XPS2_STATUS_OFFSET);
	अगर (sr & XPS2_STATUS_RX_FULL) अणु
		*byte = in_be32(drvdata->base_address + XPS2_RX_DATA_OFFSET);
		status = 0;
	पूर्ण

	वापस status;
पूर्ण

/*********************/
/* Interrupt handler */
/*********************/
अटल irqवापस_t xps2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xps2data *drvdata = dev_id;
	u32 पूर्णांकr_sr;
	u8 c;
	पूर्णांक status;

	/* Get the PS/2 पूर्णांकerrupts and clear them */
	पूर्णांकr_sr = in_be32(drvdata->base_address + XPS2_IPISR_OFFSET);
	out_be32(drvdata->base_address + XPS2_IPISR_OFFSET, पूर्णांकr_sr);

	/* Check which पूर्णांकerrupt is active */
	अगर (पूर्णांकr_sr & XPS2_IPIXR_RX_OVF)
		dev_warn(drvdata->dev, "receive overrun error\n");

	अगर (पूर्णांकr_sr & XPS2_IPIXR_RX_ERR)
		drvdata->flags |= SERIO_PARITY;

	अगर (पूर्णांकr_sr & (XPS2_IPIXR_TX_NOACK | XPS2_IPIXR_WDT_TOUT))
		drvdata->flags |= SERIO_TIMEOUT;

	अगर (पूर्णांकr_sr & XPS2_IPIXR_RX_FULL) अणु
		status = xps2_recv(drvdata, &c);

		/* Error, अगर a byte is not received */
		अगर (status) अणु
			dev_err(drvdata->dev,
				"wrong rcvd byte count (%d)\n", status);
		पूर्ण अन्यथा अणु
			serio_पूर्णांकerrupt(drvdata->serio, c, drvdata->flags);
			drvdata->flags = 0;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*******************/
/* serio callbacks */
/*******************/

/**
 * sxps2_ग_लिखो() - sends a byte out through the PS/2 port.
 * @pserio:	poपूर्णांकer to the serio काष्ठाure of the PS/2 port
 * @c:		data that needs to be written to the PS/2 port
 *
 * This function checks अगर the PS/2 transmitter is empty and sends a byte.
 * Otherwise it वापसs error. Transmission fails only when nothing is connected
 * to the PS/2 port. Thats why, we करो not try to resend the data in हाल of a
 * failure.
 */
अटल पूर्णांक sxps2_ग_लिखो(काष्ठा serio *pserio, अचिन्हित अक्षर c)
अणु
	काष्ठा xps2data *drvdata = pserio->port_data;
	अचिन्हित दीर्घ flags;
	u32 sr;
	पूर्णांक status = -1;

	spin_lock_irqsave(&drvdata->lock, flags);

	/* If the PS/2 transmitter is empty send a byte of data */
	sr = in_be32(drvdata->base_address + XPS2_STATUS_OFFSET);
	अगर (!(sr & XPS2_STATUS_TX_FULL)) अणु
		out_be32(drvdata->base_address + XPS2_TX_DATA_OFFSET, c);
		status = 0;
	पूर्ण

	spin_unlock_irqrestore(&drvdata->lock, flags);

	वापस status;
पूर्ण

/**
 * sxps2_खोलो() - called when a port is खोलोed by the higher layer.
 * @pserio:	poपूर्णांकer to the serio काष्ठाure of the PS/2 device
 *
 * This function requests irq and enables पूर्णांकerrupts क्रम the PS/2 device.
 */
अटल पूर्णांक sxps2_खोलो(काष्ठा serio *pserio)
अणु
	काष्ठा xps2data *drvdata = pserio->port_data;
	पूर्णांक error;
	u8 c;

	error = request_irq(drvdata->irq, &xps2_पूर्णांकerrupt, 0,
				DRIVER_NAME, drvdata);
	अगर (error) अणु
		dev_err(drvdata->dev,
			"Couldn't allocate interrupt %d\n", drvdata->irq);
		वापस error;
	पूर्ण

	/* start reception by enabling the पूर्णांकerrupts */
	out_be32(drvdata->base_address + XPS2_GIER_OFFSET, XPS2_GIER_GIE_MASK);
	out_be32(drvdata->base_address + XPS2_IPIER_OFFSET, XPS2_IPIXR_RX_ALL);
	(व्योम)xps2_recv(drvdata, &c);

	वापस 0;		/* success */
पूर्ण

/**
 * sxps2_बंद() - मुक्तs the पूर्णांकerrupt.
 * @pserio:	poपूर्णांकer to the serio काष्ठाure of the PS/2 device
 *
 * This function मुक्तs the irq and disables पूर्णांकerrupts क्रम the PS/2 device.
 */
अटल व्योम sxps2_बंद(काष्ठा serio *pserio)
अणु
	काष्ठा xps2data *drvdata = pserio->port_data;

	/* Disable the PS2 पूर्णांकerrupts */
	out_be32(drvdata->base_address + XPS2_GIER_OFFSET, 0x00);
	out_be32(drvdata->base_address + XPS2_IPIER_OFFSET, 0x00);
	मुक्त_irq(drvdata->irq, drvdata);
पूर्ण

/**
 * xps2_of_probe - probe method क्रम the PS/2 device.
 * @of_dev:	poपूर्णांकer to OF device काष्ठाure
 * @match:	poपूर्णांकer to the काष्ठाure used क्रम matching a device
 *
 * This function probes the PS/2 device in the device tree.
 * It initializes the driver data काष्ठाure and the hardware.
 * It वापसs 0, अगर the driver is bound to the PS/2 device, or a negative
 * value अगर there is an error.
 */
अटल पूर्णांक xps2_of_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा resource r_mem; /* IO mem resources */
	काष्ठा xps2data *drvdata;
	काष्ठा serio *serio;
	काष्ठा device *dev = &ofdev->dev;
	resource_माप_प्रकार remap_size, phys_addr;
	अचिन्हित पूर्णांक irq;
	पूर्णांक error;

	dev_info(dev, "Device Tree Probing \'%pOFn\'\n", dev->of_node);

	/* Get iospace क्रम the device */
	error = of_address_to_resource(dev->of_node, 0, &r_mem);
	अगर (error) अणु
		dev_err(dev, "invalid address\n");
		वापस error;
	पूर्ण

	/* Get IRQ क्रम the device */
	irq = irq_of_parse_and_map(dev->of_node, 0);
	अगर (!irq) अणु
		dev_err(dev, "no IRQ found\n");
		वापस -ENODEV;
	पूर्ण

	drvdata = kzalloc(माप(काष्ठा xps2data), GFP_KERNEL);
	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!drvdata || !serio) अणु
		error = -ENOMEM;
		जाओ failed1;
	पूर्ण

	spin_lock_init(&drvdata->lock);
	drvdata->irq = irq;
	drvdata->serio = serio;
	drvdata->dev = dev;

	phys_addr = r_mem.start;
	remap_size = resource_size(&r_mem);
	अगर (!request_mem_region(phys_addr, remap_size, DRIVER_NAME)) अणु
		dev_err(dev, "Couldn't lock memory region at 0x%08llX\n",
			(अचिन्हित दीर्घ दीर्घ)phys_addr);
		error = -EBUSY;
		जाओ failed1;
	पूर्ण

	/* Fill in configuration data and add them to the list */
	drvdata->base_address = ioremap(phys_addr, remap_size);
	अगर (drvdata->base_address == शून्य) अणु
		dev_err(dev, "Couldn't ioremap memory at 0x%08llX\n",
			(अचिन्हित दीर्घ दीर्घ)phys_addr);
		error = -EFAULT;
		जाओ failed2;
	पूर्ण

	/* Disable all the पूर्णांकerrupts, just in हाल */
	out_be32(drvdata->base_address + XPS2_IPIER_OFFSET, 0);

	/*
	 * Reset the PS2 device and पात any current transaction,
	 * to make sure we have the PS2 in a good state.
	 */
	out_be32(drvdata->base_address + XPS2_SRST_OFFSET, XPS2_SRST_RESET);

	dev_info(dev, "Xilinx PS2 at 0x%08llX mapped to 0x%p, irq=%d\n",
		 (अचिन्हित दीर्घ दीर्घ)phys_addr, drvdata->base_address,
		 drvdata->irq);

	serio->id.type = SERIO_8042;
	serio->ग_लिखो = sxps2_ग_लिखो;
	serio->खोलो = sxps2_खोलो;
	serio->बंद = sxps2_बंद;
	serio->port_data = drvdata;
	serio->dev.parent = dev;
	snम_लिखो(serio->name, माप(serio->name),
		 "Xilinx XPS PS/2 at %08llX", (अचिन्हित दीर्घ दीर्घ)phys_addr);
	snम_लिखो(serio->phys, माप(serio->phys),
		 "xilinxps2/serio at %08llX", (अचिन्हित दीर्घ दीर्घ)phys_addr);

	serio_रेजिस्टर_port(serio);

	platक्रमm_set_drvdata(ofdev, drvdata);
	वापस 0;		/* success */

failed2:
	release_mem_region(phys_addr, remap_size);
failed1:
	kमुक्त(serio);
	kमुक्त(drvdata);

	वापस error;
पूर्ण

/**
 * xps2_of_हटाओ - unbinds the driver from the PS/2 device.
 * @of_dev:	poपूर्णांकer to OF device काष्ठाure
 *
 * This function is called अगर a device is physically हटाओd from the प्रणाली or
 * अगर the driver module is being unloaded. It मुक्तs any resources allocated to
 * the device.
 */
अटल पूर्णांक xps2_of_हटाओ(काष्ठा platक्रमm_device *of_dev)
अणु
	काष्ठा xps2data *drvdata = platक्रमm_get_drvdata(of_dev);
	काष्ठा resource r_mem; /* IO mem resources */

	serio_unरेजिस्टर_port(drvdata->serio);
	iounmap(drvdata->base_address);

	/* Get iospace of the device */
	अगर (of_address_to_resource(of_dev->dev.of_node, 0, &r_mem))
		dev_err(drvdata->dev, "invalid address\n");
	अन्यथा
		release_mem_region(r_mem.start, resource_size(&r_mem));

	kमुक्त(drvdata);

	वापस 0;
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id xps2_of_match[] = अणु
	अणु .compatible = "xlnx,xps-ps2-1.00.a", पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xps2_of_match);

अटल काष्ठा platक्रमm_driver xps2_of_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = xps2_of_match,
	पूर्ण,
	.probe		= xps2_of_probe,
	.हटाओ		= xps2_of_हटाओ,
पूर्ण;
module_platक्रमm_driver(xps2_of_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Xilinx XPS PS/2 driver");
MODULE_LICENSE("GPL");

