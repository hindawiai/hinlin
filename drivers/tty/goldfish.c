<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Google, Inc.
 * Copyright (C) 2012 Intel, Inc.
 * Copyright (C) 2017 Imagination Technologies Ltd.
 */

#समावेश <linux/console.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/goldfish.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/serial_core.h>

/* Goldfish tty रेजिस्टर's offsets */
#घोषणा	GOLDFISH_TTY_REG_BYTES_READY	0x04
#घोषणा	GOLDFISH_TTY_REG_CMD		0x08
#घोषणा	GOLDFISH_TTY_REG_DATA_PTR	0x10
#घोषणा	GOLDFISH_TTY_REG_DATA_LEN	0x14
#घोषणा	GOLDFISH_TTY_REG_DATA_PTR_HIGH	0x18
#घोषणा	GOLDFISH_TTY_REG_VERSION	0x20

/* Goldfish tty commands */
#घोषणा	GOLDFISH_TTY_CMD_INT_DISABLE	0
#घोषणा	GOLDFISH_TTY_CMD_INT_ENABLE	1
#घोषणा	GOLDFISH_TTY_CMD_WRITE_BUFFER	2
#घोषणा	GOLDFISH_TTY_CMD_READ_BUFFER	3

काष्ठा goldfish_tty अणु
	काष्ठा tty_port port;
	spinlock_t lock;
	व्योम __iomem *base;
	u32 irq;
	पूर्णांक खोलोcount;
	काष्ठा console console;
	u32 version;
	काष्ठा device *dev;
पूर्ण;

अटल DEFINE_MUTEX(goldfish_tty_lock);
अटल काष्ठा tty_driver *goldfish_tty_driver;
अटल u32 goldfish_tty_line_count = 8;
अटल u32 goldfish_tty_current_line_count;
अटल काष्ठा goldfish_tty *goldfish_ttys;

अटल व्योम करो_rw_io(काष्ठा goldfish_tty *qtty,
		     अचिन्हित दीर्घ address,
		     अचिन्हित पूर्णांक count,
		     पूर्णांक is_ग_लिखो)
अणु
	अचिन्हित दीर्घ irq_flags;
	व्योम __iomem *base = qtty->base;

	spin_lock_irqsave(&qtty->lock, irq_flags);
	gf_ग_लिखो_ptr((व्योम *)address, base + GOLDFISH_TTY_REG_DATA_PTR,
		     base + GOLDFISH_TTY_REG_DATA_PTR_HIGH);
	__raw_ग_लिखोl(count, base + GOLDFISH_TTY_REG_DATA_LEN);

	अगर (is_ग_लिखो)
		__raw_ग_लिखोl(GOLDFISH_TTY_CMD_WRITE_BUFFER,
		       base + GOLDFISH_TTY_REG_CMD);
	अन्यथा
		__raw_ग_लिखोl(GOLDFISH_TTY_CMD_READ_BUFFER,
		       base + GOLDFISH_TTY_REG_CMD);

	spin_unlock_irqrestore(&qtty->lock, irq_flags);
पूर्ण

अटल व्योम goldfish_tty_rw(काष्ठा goldfish_tty *qtty,
			    अचिन्हित दीर्घ addr,
			    अचिन्हित पूर्णांक count,
			    पूर्णांक is_ग_लिखो)
अणु
	dma_addr_t dma_handle;
	क्रमागत dma_data_direction dma_dir;

	dma_dir = (is_ग_लिखो ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
	अगर (qtty->version > 0) अणु
		/*
		 * Goldfish TTY क्रम Ranchu platक्रमm uses
		 * physical addresses and DMA क्रम पढ़ो/ग_लिखो operations
		 */
		अचिन्हित दीर्घ addr_end = addr + count;

		जबतक (addr < addr_end) अणु
			अचिन्हित दीर्घ pg_end = (addr & PAGE_MASK) + PAGE_SIZE;
			अचिन्हित दीर्घ next =
					pg_end < addr_end ? pg_end : addr_end;
			अचिन्हित दीर्घ avail = next - addr;

			/*
			 * Map the buffer's भव address to the DMA address
			 * so the buffer can be accessed by the device.
			 */
			dma_handle = dma_map_single(qtty->dev, (व्योम *)addr,
						    avail, dma_dir);

			अगर (dma_mapping_error(qtty->dev, dma_handle)) अणु
				dev_err(qtty->dev, "tty: DMA mapping error.\n");
				वापस;
			पूर्ण
			करो_rw_io(qtty, dma_handle, avail, is_ग_लिखो);

			/*
			 * Unmap the previously mapped region after
			 * the completion of the पढ़ो/ग_लिखो operation.
			 */
			dma_unmap_single(qtty->dev, dma_handle, avail, dma_dir);

			addr += avail;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Old style Goldfish TTY used on the Goldfish platक्रमm
		 * uses भव addresses.
		 */
		करो_rw_io(qtty, addr, count, is_ग_लिखो);
	पूर्ण
पूर्ण

अटल व्योम goldfish_tty_करो_ग_लिखो(पूर्णांक line, स्थिर अक्षर *buf,
				  अचिन्हित पूर्णांक count)
अणु
	काष्ठा goldfish_tty *qtty = &goldfish_ttys[line];
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)(व्योम *)buf;

	goldfish_tty_rw(qtty, address, count, 1);
पूर्ण

अटल irqवापस_t goldfish_tty_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा goldfish_tty *qtty = dev_id;
	व्योम __iomem *base = qtty->base;
	अचिन्हित दीर्घ address;
	अचिन्हित अक्षर *buf;
	u32 count;

	count = __raw_पढ़ोl(base + GOLDFISH_TTY_REG_BYTES_READY);
	अगर (count == 0)
		वापस IRQ_NONE;

	count = tty_prepare_flip_string(&qtty->port, &buf, count);

	address = (अचिन्हित दीर्घ)(व्योम *)buf;
	goldfish_tty_rw(qtty, address, count, 0);

	tty_schedule_flip(&qtty->port);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक goldfish_tty_activate(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा goldfish_tty *qtty = container_of(port, काष्ठा goldfish_tty,
									port);
	__raw_ग_लिखोl(GOLDFISH_TTY_CMD_INT_ENABLE, qtty->base + GOLDFISH_TTY_REG_CMD);
	वापस 0;
पूर्ण

अटल व्योम goldfish_tty_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा goldfish_tty *qtty = container_of(port, काष्ठा goldfish_tty,
									port);
	__raw_ग_लिखोl(GOLDFISH_TTY_CMD_INT_DISABLE, qtty->base + GOLDFISH_TTY_REG_CMD);
पूर्ण

अटल पूर्णांक goldfish_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा goldfish_tty *qtty = &goldfish_ttys[tty->index];
	वापस tty_port_खोलो(&qtty->port, tty, filp);
पूर्ण

अटल व्योम goldfish_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	tty_port_बंद(tty->port, tty, filp);
पूर्ण

अटल व्योम goldfish_tty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	tty_port_hangup(tty->port);
पूर्ण

अटल पूर्णांक goldfish_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
								पूर्णांक count)
अणु
	goldfish_tty_करो_ग_लिखो(tty->index, buf, count);
	वापस count;
पूर्ण

अटल पूर्णांक goldfish_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	वापस 0x10000;
पूर्ण

अटल पूर्णांक goldfish_tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा goldfish_tty *qtty = &goldfish_ttys[tty->index];
	व्योम __iomem *base = qtty->base;
	वापस __raw_पढ़ोl(base + GOLDFISH_TTY_REG_BYTES_READY);
पूर्ण

अटल व्योम goldfish_tty_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *b,
								अचिन्हित count)
अणु
	goldfish_tty_करो_ग_लिखो(co->index, b, count);
पूर्ण

अटल काष्ठा tty_driver *goldfish_tty_console_device(काष्ठा console *c,
								पूर्णांक *index)
अणु
	*index = c->index;
	वापस goldfish_tty_driver;
पूर्ण

अटल पूर्णांक goldfish_tty_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	अगर ((अचिन्हित)co->index >= goldfish_tty_line_count)
		वापस -ENODEV;
	अगर (!goldfish_ttys[co->index].base)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tty_port_operations goldfish_port_ops = अणु
	.activate = goldfish_tty_activate,
	.shutकरोwn = goldfish_tty_shutकरोwn
पूर्ण;

अटल स्थिर काष्ठा tty_operations goldfish_tty_ops = अणु
	.खोलो = goldfish_tty_खोलो,
	.बंद = goldfish_tty_बंद,
	.hangup = goldfish_tty_hangup,
	.ग_लिखो = goldfish_tty_ग_लिखो,
	.ग_लिखो_room = goldfish_tty_ग_लिखो_room,
	.अक्षरs_in_buffer = goldfish_tty_अक्षरs_in_buffer,
पूर्ण;

अटल पूर्णांक goldfish_tty_create_driver(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा tty_driver *tty;

	goldfish_ttys = kसुस्मृति(goldfish_tty_line_count,
				माप(*goldfish_ttys),
				GFP_KERNEL);
	अगर (goldfish_ttys == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_alloc_goldfish_ttys_failed;
	पूर्ण
	tty = alloc_tty_driver(goldfish_tty_line_count);
	अगर (tty == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_alloc_tty_driver_failed;
	पूर्ण
	tty->driver_name = "goldfish";
	tty->name = "ttyGF";
	tty->type = TTY_DRIVER_TYPE_SERIAL;
	tty->subtype = SERIAL_TYPE_NORMAL;
	tty->init_termios = tty_std_termios;
	tty->flags = TTY_DRIVER_RESET_TERMIOS | TTY_DRIVER_REAL_RAW |
						TTY_DRIVER_DYNAMIC_DEV;
	tty_set_operations(tty, &goldfish_tty_ops);
	ret = tty_रेजिस्टर_driver(tty);
	अगर (ret)
		जाओ err_tty_रेजिस्टर_driver_failed;

	goldfish_tty_driver = tty;
	वापस 0;

err_tty_रेजिस्टर_driver_failed:
	put_tty_driver(tty);
err_alloc_tty_driver_failed:
	kमुक्त(goldfish_ttys);
	goldfish_ttys = शून्य;
err_alloc_goldfish_ttys_failed:
	वापस ret;
पूर्ण

अटल व्योम goldfish_tty_delete_driver(व्योम)
अणु
	tty_unरेजिस्टर_driver(goldfish_tty_driver);
	put_tty_driver(goldfish_tty_driver);
	goldfish_tty_driver = शून्य;
	kमुक्त(goldfish_ttys);
	goldfish_ttys = शून्य;
पूर्ण

अटल पूर्णांक goldfish_tty_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा goldfish_tty *qtty;
	पूर्णांक ret = -ENODEV;
	काष्ठा resource *r;
	काष्ठा device *ttydev;
	व्योम __iomem *base;
	u32 irq;
	अचिन्हित पूर्णांक line;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		pr_err("goldfish_tty: No MEM resource available!\n");
		वापस -ENOMEM;
	पूर्ण

	base = ioremap(r->start, 0x1000);
	अगर (!base) अणु
		pr_err("goldfish_tty: Unable to ioremap base!\n");
		वापस -ENOMEM;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!r) अणु
		pr_err("goldfish_tty: No IRQ resource available!\n");
		जाओ err_unmap;
	पूर्ण

	irq = r->start;

	mutex_lock(&goldfish_tty_lock);

	अगर (pdev->id == PLATFORM_DEVID_NONE)
		line = goldfish_tty_current_line_count;
	अन्यथा
		line = pdev->id;

	अगर (line >= goldfish_tty_line_count) अणु
		pr_err("goldfish_tty: Reached maximum tty number of %d.\n",
		       goldfish_tty_current_line_count);
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	अगर (goldfish_tty_current_line_count == 0) अणु
		ret = goldfish_tty_create_driver();
		अगर (ret)
			जाओ err_unlock;
	पूर्ण
	goldfish_tty_current_line_count++;

	qtty = &goldfish_ttys[line];
	spin_lock_init(&qtty->lock);
	tty_port_init(&qtty->port);
	qtty->port.ops = &goldfish_port_ops;
	qtty->base = base;
	qtty->irq = irq;
	qtty->dev = &pdev->dev;

	/*
	 * Goldfish TTY device used by the Goldfish emulator
	 * should identअगरy itself with 0, क्रमcing the driver
	 * to use भव addresses. Goldfish TTY device
	 * on Ranchu emulator (qemu2) वापसs 1 here and
	 * driver will use physical addresses.
	 */
	qtty->version = __raw_पढ़ोl(base + GOLDFISH_TTY_REG_VERSION);

	/*
	 * Goldfish TTY device on Ranchu emulator (qemu2)
	 * will use DMA क्रम पढ़ो/ग_लिखो IO operations.
	 */
	अगर (qtty->version > 0) अणु
		/*
		 * Initialize dma_mask to 32-bits.
		 */
		अगर (!pdev->dev.dma_mask)
			pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
		ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			dev_err(&pdev->dev, "No suitable DMA available.\n");
			जाओ err_dec_line_count;
		पूर्ण
	पूर्ण

	__raw_ग_लिखोl(GOLDFISH_TTY_CMD_INT_DISABLE, base + GOLDFISH_TTY_REG_CMD);

	ret = request_irq(irq, goldfish_tty_पूर्णांकerrupt, IRQF_SHARED,
			  "goldfish_tty", qtty);
	अगर (ret) अणु
		pr_err("goldfish_tty: No IRQ available!\n");
		जाओ err_dec_line_count;
	पूर्ण

	ttydev = tty_port_रेजिस्टर_device(&qtty->port, goldfish_tty_driver,
					  line, &pdev->dev);
	अगर (IS_ERR(ttydev)) अणु
		ret = PTR_ERR(ttydev);
		जाओ err_tty_रेजिस्टर_device_failed;
	पूर्ण

	म_नकल(qtty->console.name, "ttyGF");
	qtty->console.ग_लिखो = goldfish_tty_console_ग_लिखो;
	qtty->console.device = goldfish_tty_console_device;
	qtty->console.setup = goldfish_tty_console_setup;
	qtty->console.flags = CON_PRINTBUFFER;
	qtty->console.index = line;
	रेजिस्टर_console(&qtty->console);
	platक्रमm_set_drvdata(pdev, qtty);

	mutex_unlock(&goldfish_tty_lock);
	वापस 0;

err_tty_रेजिस्टर_device_failed:
	मुक्त_irq(irq, qtty);
err_dec_line_count:
	goldfish_tty_current_line_count--;
	अगर (goldfish_tty_current_line_count == 0)
		goldfish_tty_delete_driver();
err_unlock:
	mutex_unlock(&goldfish_tty_lock);
err_unmap:
	iounmap(base);
	वापस ret;
पूर्ण

अटल पूर्णांक goldfish_tty_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा goldfish_tty *qtty = platक्रमm_get_drvdata(pdev);

	mutex_lock(&goldfish_tty_lock);

	unरेजिस्टर_console(&qtty->console);
	tty_unरेजिस्टर_device(goldfish_tty_driver, qtty->console.index);
	iounmap(qtty->base);
	qtty->base = शून्य;
	मुक्त_irq(qtty->irq, pdev);
	goldfish_tty_current_line_count--;
	अगर (goldfish_tty_current_line_count == 0)
		goldfish_tty_delete_driver();
	mutex_unlock(&goldfish_tty_lock);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_GOLDFISH_TTY_EARLY_CONSOLE
अटल व्योम gf_early_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	__raw_ग_लिखोl(ch, port->membase);
पूर्ण

अटल व्योम gf_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, gf_early_console_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init gf_earlycon_setup(काष्ठा earlycon_device *device,
				    स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = gf_early_ग_लिखो;
	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(early_gf_tty, "google,goldfish-tty", gf_earlycon_setup);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id goldfish_tty_of_match[] = अणु
	अणु .compatible = "google,goldfish-tty", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, goldfish_tty_of_match);

अटल काष्ठा platक्रमm_driver goldfish_tty_platक्रमm_driver = अणु
	.probe = goldfish_tty_probe,
	.हटाओ = goldfish_tty_हटाओ,
	.driver = अणु
		.name = "goldfish_tty",
		.of_match_table = goldfish_tty_of_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(goldfish_tty_platक्रमm_driver);

MODULE_LICENSE("GPL v2");
