<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/mcb.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_8250.h>
#समावेश <uapi/linux/serial_core.h>

#घोषणा MEN_UART_ID_Z025 0x19
#घोषणा MEN_UART_ID_Z057 0x39
#घोषणा MEN_UART_ID_Z125 0x7d

#घोषणा MEN_UART_MEM_SIZE 0x10

काष्ठा serial_8250_men_mcb_data अणु
	काष्ठा uart_8250_port uart;
	पूर्णांक line;
पूर्ण;

/*
 * The Z125 16550-compatible UART has no fixed base घड़ी asचिन्हित
 * So, depending on the board we're on, we need to adjust the
 * parameter in order to really set the correct baudrate, and
 * करो so अगर possible without user पूर्णांकeraction
 */
अटल u32 men_lookup_uartclk(काष्ठा mcb_device *mdev)
अणु
	/* use शेष value अगर board is not available below */
	u32 clkval = 1041666;

	dev_info(&mdev->dev, "%s on board %s\n",
		dev_name(&mdev->dev),
		mdev->bus->name);
	अगर  (म_भेदन(mdev->bus->name, "F075", 4) == 0)
		clkval = 1041666;
	अन्यथा अगर (म_भेदन(mdev->bus->name, "F216", 4) == 0)
		clkval = 1843200;
	अन्यथा अगर (म_भेदन(mdev->bus->name, "G215", 4) == 0)
		clkval = 1843200;
	अन्यथा अगर (म_भेदन(mdev->bus->name, "F210", 4) == 0)
		clkval = 115200;
	अन्यथा
		dev_info(&mdev->dev,
			 "board not detected, using default uartclk\n");

	clkval = clkval  << 4;

	वापस clkval;
पूर्ण

अटल पूर्णांक get_num_ports(काष्ठा mcb_device *mdev,
				  व्योम __iomem *membase)
अणु
	चयन (mdev->id) अणु
	हाल MEN_UART_ID_Z125:
		वापस 1U;
	हाल MEN_UART_ID_Z025:
		वापस पढ़ोb(membase) >> 4;
	हाल MEN_UART_ID_Z057:
		वापस 4U;
	शेष:
		dev_err(&mdev->dev, "no supported device!\n");
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल पूर्णांक serial_8250_men_mcb_probe(काष्ठा mcb_device *mdev,
				     स्थिर काष्ठा mcb_device_id *id)
अणु
	काष्ठा serial_8250_men_mcb_data *data;
	काष्ठा resource *mem;
	पूर्णांक num_ports;
	पूर्णांक i;
	व्योम __iomem *membase;

	mem = mcb_get_resource(mdev, IORESOURCE_MEM);
	अगर (mem == शून्य)
		वापस -ENXIO;
	membase = devm_ioremap_resource(&mdev->dev, mem);
	अगर (IS_ERR(membase))
		वापस PTR_ERR_OR_ZERO(membase);

	num_ports = get_num_ports(mdev, membase);

	dev_dbg(&mdev->dev, "found a 16z%03u with %u ports\n",
		mdev->id, num_ports);

	अगर (num_ports <= 0 || num_ports > 4) अणु
		dev_err(&mdev->dev, "unexpected number of ports: %u\n",
			num_ports);
		वापस -ENODEV;
	पूर्ण

	data = devm_kसुस्मृति(&mdev->dev, num_ports,
			    माप(काष्ठा serial_8250_men_mcb_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mcb_set_drvdata(mdev, data);

	क्रम (i = 0; i < num_ports; i++) अणु
		data[i].uart.port.dev = mdev->dma_dev;
		spin_lock_init(&data[i].uart.port.lock);

		data[i].uart.port.type = PORT_16550;
		data[i].uart.port.flags = UPF_SKIP_TEST | UPF_SHARE_IRQ
					  | UPF_FIXED_TYPE;
		data[i].uart.port.iotype = UPIO_MEM;
		data[i].uart.port.uartclk = men_lookup_uartclk(mdev);
		data[i].uart.port.regshअगरt = 0;
		data[i].uart.port.irq = mcb_get_irq(mdev);
		data[i].uart.port.membase = membase;
		data[i].uart.port.fअगरosize = 60;
		data[i].uart.port.mapbase = (अचिन्हित दीर्घ) mem->start
					    + i * MEN_UART_MEM_SIZE;
		data[i].uart.port.iobase = data[i].uart.port.mapbase;

		/* ok, रेजिस्टर the port */
		data[i].line = serial8250_रेजिस्टर_8250_port(&data[i].uart);
		अगर (data[i].line < 0) अणु
			dev_err(&mdev->dev, "unable to register UART port\n");
			वापस data[i].line;
		पूर्ण
		dev_info(&mdev->dev, "found MCB UART: ttyS%d\n", data[i].line);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम serial_8250_men_mcb_हटाओ(काष्ठा mcb_device *mdev)
अणु
	पूर्णांक num_ports, i;
	काष्ठा serial_8250_men_mcb_data *data = mcb_get_drvdata(mdev);

	अगर (!data)
		वापस;

	num_ports = get_num_ports(mdev, data[0].uart.port.membase);
	अगर (num_ports <= 0 || num_ports > 4) अणु
		dev_err(&mdev->dev, "error retrieving number of ports!\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < num_ports; i++)
		serial8250_unरेजिस्टर_port(data[i].line);
पूर्ण

अटल स्थिर काष्ठा mcb_device_id serial_8250_men_mcb_ids[] = अणु
	अणु .device = MEN_UART_ID_Z025 पूर्ण,
	अणु .device = MEN_UART_ID_Z057 पूर्ण,
	अणु .device = MEN_UART_ID_Z125 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mcb, serial_8250_men_mcb_ids);

अटल काष्ठा mcb_driver mcb_driver = अणु
	.driver = अणु
		.name = "8250_men_mcb",
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = serial_8250_men_mcb_probe,
	.हटाओ = serial_8250_men_mcb_हटाओ,
	.id_table = serial_8250_men_mcb_ids,
पूर्ण;
module_mcb_driver(mcb_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MEN 8250 UART driver");
MODULE_AUTHOR("Michael Moese <michael.moese@men.de");
MODULE_ALIAS("mcb:16z125");
MODULE_ALIAS("mcb:16z025");
MODULE_ALIAS("mcb:16z057");
MODULE_IMPORT_NS(MCB);
