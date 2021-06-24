<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Driver is originally developed by Pavel Sokolov <psokolov@synopsys.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#घोषणा ARC_PS2_PORTS                   2

#घोषणा ARC_ARC_PS2_ID                  0x0001f609

#घोषणा STAT_TIMEOUT                    128

#घोषणा PS2_STAT_RX_FRM_ERR             (1)
#घोषणा PS2_STAT_RX_BUF_OVER            (1 << 1)
#घोषणा PS2_STAT_RX_INT_EN              (1 << 2)
#घोषणा PS2_STAT_RX_VAL                 (1 << 3)
#घोषणा PS2_STAT_TX_ISNOT_FUL           (1 << 4)
#घोषणा PS2_STAT_TX_INT_EN              (1 << 5)

काष्ठा arc_ps2_port अणु
	व्योम __iomem *data_addr;
	व्योम __iomem *status_addr;
	काष्ठा serio *io;
पूर्ण;

काष्ठा arc_ps2_data अणु
	काष्ठा arc_ps2_port port[ARC_PS2_PORTS];
	व्योम __iomem *addr;
	अचिन्हित पूर्णांक frame_error;
	अचिन्हित पूर्णांक buf_overflow;
	अचिन्हित पूर्णांक total_पूर्णांक;
पूर्ण;

अटल व्योम arc_ps2_check_rx(काष्ठा arc_ps2_data *arc_ps2,
			     काष्ठा arc_ps2_port *port)
अणु
	अचिन्हित पूर्णांक समयout = 1000;
	अचिन्हित पूर्णांक flag, status;
	अचिन्हित अक्षर data;

	करो अणु
		status = ioपढ़ो32(port->status_addr);
		अगर (!(status & PS2_STAT_RX_VAL))
			वापस;

		data = ioपढ़ो32(port->data_addr) & 0xff;

		flag = 0;
		arc_ps2->total_पूर्णांक++;
		अगर (status & PS2_STAT_RX_FRM_ERR) अणु
			arc_ps2->frame_error++;
			flag |= SERIO_PARITY;
		पूर्ण अन्यथा अगर (status & PS2_STAT_RX_BUF_OVER) अणु
			arc_ps2->buf_overflow++;
			flag |= SERIO_FRAME;
		पूर्ण

		serio_पूर्णांकerrupt(port->io, data, flag);
	पूर्ण जबतक (--समयout);

	dev_err(&port->io->dev, "PS/2 hardware stuck\n");
पूर्ण

अटल irqवापस_t arc_ps2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा arc_ps2_data *arc_ps2 = dev;
	पूर्णांक i;

	क्रम (i = 0; i < ARC_PS2_PORTS; i++)
		arc_ps2_check_rx(arc_ps2, &arc_ps2->port[i]);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक arc_ps2_ग_लिखो(काष्ठा serio *io, अचिन्हित अक्षर val)
अणु
	अचिन्हित status;
	काष्ठा arc_ps2_port *port = io->port_data;
	पूर्णांक समयout = STAT_TIMEOUT;

	करो अणु
		status = ioपढ़ो32(port->status_addr);
		cpu_relax();

		अगर (status & PS2_STAT_TX_ISNOT_FUL) अणु
			ioग_लिखो32(val & 0xff, port->data_addr);
			वापस 0;
		पूर्ण

	पूर्ण जबतक (--समयout);

	dev_err(&io->dev, "write timeout\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक arc_ps2_खोलो(काष्ठा serio *io)
अणु
	काष्ठा arc_ps2_port *port = io->port_data;

	ioग_लिखो32(PS2_STAT_RX_INT_EN, port->status_addr);

	वापस 0;
पूर्ण

अटल व्योम arc_ps2_बंद(काष्ठा serio *io)
अणु
	काष्ठा arc_ps2_port *port = io->port_data;

	ioग_लिखो32(ioपढ़ो32(port->status_addr) & ~PS2_STAT_RX_INT_EN,
		  port->status_addr);
पूर्ण

अटल व्योम __iomem *arc_ps2_calc_addr(काष्ठा arc_ps2_data *arc_ps2,
						  पूर्णांक index, bool status)
अणु
	व्योम __iomem *addr;

	addr = arc_ps2->addr + 4 + 4 * index;
	अगर (status)
		addr += ARC_PS2_PORTS * 4;

	वापस addr;
पूर्ण

अटल व्योम arc_ps2_inhibit_ports(काष्ठा arc_ps2_data *arc_ps2)
अणु
	व्योम __iomem *addr;
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARC_PS2_PORTS; i++) अणु
		addr = arc_ps2_calc_addr(arc_ps2, i, true);
		val = ioपढ़ो32(addr);
		val &= ~(PS2_STAT_RX_INT_EN | PS2_STAT_TX_INT_EN);
		ioग_लिखो32(val, addr);
	पूर्ण
पूर्ण

अटल पूर्णांक arc_ps2_create_port(काष्ठा platक्रमm_device *pdev,
					 काष्ठा arc_ps2_data *arc_ps2,
					 पूर्णांक index)
अणु
	काष्ठा arc_ps2_port *port = &arc_ps2->port[index];
	काष्ठा serio *io;

	io = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!io)
		वापस -ENOMEM;

	io->id.type = SERIO_8042;
	io->ग_लिखो = arc_ps2_ग_लिखो;
	io->खोलो = arc_ps2_खोलो;
	io->बंद = arc_ps2_बंद;
	snम_लिखो(io->name, माप(io->name), "ARC PS/2 port%d", index);
	snम_लिखो(io->phys, माप(io->phys), "arc/serio%d", index);
	io->port_data = port;

	port->io = io;

	port->data_addr = arc_ps2_calc_addr(arc_ps2, index, false);
	port->status_addr = arc_ps2_calc_addr(arc_ps2, index, true);

	dev_dbg(&pdev->dev, "port%d is allocated (data = 0x%p, status = 0x%p)\n",
		index, port->data_addr, port->status_addr);

	serio_रेजिस्टर_port(port->io);
	वापस 0;
पूर्ण

अटल पूर्णांक arc_ps2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arc_ps2_data *arc_ps2;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक error, id, i;

	irq = platक्रमm_get_irq_byname(pdev, "arc_ps2_irq");
	अगर (irq < 0)
		वापस -EINVAL;

	arc_ps2 = devm_kzalloc(&pdev->dev, माप(काष्ठा arc_ps2_data),
				GFP_KERNEL);
	अगर (!arc_ps2) अणु
		dev_err(&pdev->dev, "out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	arc_ps2->addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(arc_ps2->addr))
		वापस PTR_ERR(arc_ps2->addr);

	dev_info(&pdev->dev, "irq = %d, address = 0x%p, ports = %i\n",
		 irq, arc_ps2->addr, ARC_PS2_PORTS);

	id = ioपढ़ो32(arc_ps2->addr);
	अगर (id != ARC_ARC_PS2_ID) अणु
		dev_err(&pdev->dev, "device id does not match\n");
		वापस -ENXIO;
	पूर्ण

	arc_ps2_inhibit_ports(arc_ps2);

	error = devm_request_irq(&pdev->dev, irq, arc_ps2_पूर्णांकerrupt,
				 0, "arc_ps2", arc_ps2);
	अगर (error) अणु
		dev_err(&pdev->dev, "Could not allocate IRQ\n");
		वापस error;
	पूर्ण

	क्रम (i = 0; i < ARC_PS2_PORTS; i++) अणु
		error = arc_ps2_create_port(pdev, arc_ps2, i);
		अगर (error) अणु
			जबतक (--i >= 0)
				serio_unरेजिस्टर_port(arc_ps2->port[i].io);
			वापस error;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, arc_ps2);

	वापस 0;
पूर्ण

अटल पूर्णांक arc_ps2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arc_ps2_data *arc_ps2 = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < ARC_PS2_PORTS; i++)
		serio_unरेजिस्टर_port(arc_ps2->port[i].io);

	dev_dbg(&pdev->dev, "interrupt count = %i\n", arc_ps2->total_पूर्णांक);
	dev_dbg(&pdev->dev, "frame error count = %i\n", arc_ps2->frame_error);
	dev_dbg(&pdev->dev, "buffer overflow count = %i\n",
		arc_ps2->buf_overflow);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id arc_ps2_match[] = अणु
	अणु .compatible = "snps,arc_ps2" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arc_ps2_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver arc_ps2_driver = अणु
	.driver	= अणु
		.name		= "arc_ps2",
		.of_match_table	= of_match_ptr(arc_ps2_match),
	पूर्ण,
	.probe	= arc_ps2_probe,
	.हटाओ	= arc_ps2_हटाओ,
पूर्ण;

module_platक्रमm_driver(arc_ps2_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pavel Sokolov <psokolov@synopsys.com>");
MODULE_DESCRIPTION("ARC PS/2 Driver");
