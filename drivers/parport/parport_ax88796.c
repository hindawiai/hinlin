<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/parport/parport_ax88796.c
 *
 * (c) 2005,2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/parport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#घोषणा AX_SPR_BUSY		(1<<7)
#घोषणा AX_SPR_ACK		(1<<6)
#घोषणा AX_SPR_PE		(1<<5)
#घोषणा AX_SPR_SLCT		(1<<4)
#घोषणा AX_SPR_ERR		(1<<3)

#घोषणा AX_CPR_nDOE		(1<<5)
#घोषणा AX_CPR_SLCTIN		(1<<3)
#घोषणा AX_CPR_nINIT		(1<<2)
#घोषणा AX_CPR_ATFD		(1<<1)
#घोषणा AX_CPR_STRB		(1<<0)

काष्ठा ax_drvdata अणु
	काष्ठा parport		*parport;
	काष्ठा parport_state	 suspend;

	काष्ठा device		*dev;
	काष्ठा resource		*io;

	अचिन्हित अक्षर		 irq_enabled;

	व्योम __iomem		*base;
	व्योम __iomem		*spp_data;
	व्योम __iomem		*spp_spr;
	व्योम __iomem		*spp_cpr;
पूर्ण;

अटल अंतरभूत काष्ठा ax_drvdata *pp_to_drv(काष्ठा parport *p)
अणु
	वापस p->निजी_data;
पूर्ण

अटल अचिन्हित अक्षर
parport_ax88796_पढ़ो_data(काष्ठा parport *p)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);

	वापस पढ़ोb(dd->spp_data);
पूर्ण

अटल व्योम
parport_ax88796_ग_लिखो_data(काष्ठा parport *p, अचिन्हित अक्षर data)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);

	ग_लिखोb(data, dd->spp_data);
पूर्ण

अटल अचिन्हित अक्षर
parport_ax88796_पढ़ो_control(काष्ठा parport *p)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);
	अचिन्हित पूर्णांक cpr = पढ़ोb(dd->spp_cpr);
	अचिन्हित पूर्णांक ret = 0;

	अगर (!(cpr & AX_CPR_STRB))
		ret |= PARPORT_CONTROL_STROBE;

	अगर (!(cpr & AX_CPR_ATFD))
		ret |= PARPORT_CONTROL_AUTOFD;

	अगर (cpr & AX_CPR_nINIT)
		ret |= PARPORT_CONTROL_INIT;

	अगर (!(cpr & AX_CPR_SLCTIN))
		ret |= PARPORT_CONTROL_SELECT;

	वापस ret;
पूर्ण

अटल व्योम
parport_ax88796_ग_लिखो_control(काष्ठा parport *p, अचिन्हित अक्षर control)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);
	अचिन्हित पूर्णांक cpr = पढ़ोb(dd->spp_cpr);

	cpr &= AX_CPR_nDOE;

	अगर (!(control & PARPORT_CONTROL_STROBE))
		cpr |= AX_CPR_STRB;

	अगर (!(control & PARPORT_CONTROL_AUTOFD))
		cpr |= AX_CPR_ATFD;

	अगर (control & PARPORT_CONTROL_INIT)
		cpr |= AX_CPR_nINIT;

	अगर (!(control & PARPORT_CONTROL_SELECT))
		cpr |= AX_CPR_SLCTIN;

	dev_dbg(dd->dev, "write_control: ctrl=%02x, cpr=%02x\n", control, cpr);
	ग_लिखोb(cpr, dd->spp_cpr);

	अगर (parport_ax88796_पढ़ो_control(p) != control) अणु
		dev_err(dd->dev, "write_control: read != set (%02x, %02x)\n",
			parport_ax88796_पढ़ो_control(p), control);
	पूर्ण
पूर्ण

अटल अचिन्हित अक्षर
parport_ax88796_पढ़ो_status(काष्ठा parport *p)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);
	अचिन्हित पूर्णांक status = पढ़ोb(dd->spp_spr);
	अचिन्हित पूर्णांक ret = 0;

	अगर (status & AX_SPR_BUSY)
		ret |= PARPORT_STATUS_BUSY;

	अगर (status & AX_SPR_ACK)
		ret |= PARPORT_STATUS_ACK;

	अगर (status & AX_SPR_ERR)
		ret |= PARPORT_STATUS_ERROR;

	अगर (status & AX_SPR_SLCT)
		ret |= PARPORT_STATUS_SELECT;

	अगर (status & AX_SPR_PE)
		ret |= PARPORT_STATUS_PAPEROUT;

	वापस ret;
पूर्ण

अटल अचिन्हित अक्षर
parport_ax88796_frob_control(काष्ठा parport *p, अचिन्हित अक्षर mask,
			     अचिन्हित अक्षर val)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);
	अचिन्हित अक्षर old = parport_ax88796_पढ़ो_control(p);

	dev_dbg(dd->dev, "frob: mask=%02x, val=%02x, old=%02x\n",
		mask, val, old);

	parport_ax88796_ग_लिखो_control(p, (old & ~mask) | val);
	वापस old;
पूर्ण

अटल व्योम
parport_ax88796_enable_irq(काष्ठा parport *p)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (!dd->irq_enabled) अणु
		enable_irq(p->irq);
		dd->irq_enabled = 1;
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल व्योम
parport_ax88796_disable_irq(काष्ठा parport *p)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (dd->irq_enabled) अणु
		disable_irq(p->irq);
		dd->irq_enabled = 0;
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल व्योम
parport_ax88796_data_क्रमward(काष्ठा parport *p)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);
	व्योम __iomem *cpr = dd->spp_cpr;

	ग_लिखोb((पढ़ोb(cpr) & ~AX_CPR_nDOE), cpr);
पूर्ण

अटल व्योम
parport_ax88796_data_reverse(काष्ठा parport *p)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);
	व्योम __iomem *cpr = dd->spp_cpr;

	ग_लिखोb(पढ़ोb(cpr) | AX_CPR_nDOE, cpr);
पूर्ण

अटल व्योम
parport_ax88796_init_state(काष्ठा pardevice *d, काष्ठा parport_state *s)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(d->port);

	स_रखो(s, 0, माप(काष्ठा parport_state));

	dev_dbg(dd->dev, "init_state: %p: state=%p\n", d, s);
	s->u.ax88796.cpr = पढ़ोb(dd->spp_cpr);
पूर्ण

अटल व्योम
parport_ax88796_save_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);

	dev_dbg(dd->dev, "save_state: %p: state=%p\n", p, s);
	s->u.ax88796.cpr = पढ़ोb(dd->spp_cpr);
पूर्ण

अटल व्योम
parport_ax88796_restore_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	काष्ठा ax_drvdata *dd = pp_to_drv(p);

	dev_dbg(dd->dev, "restore_state: %p: state=%p\n", p, s);
	ग_लिखोb(s->u.ax88796.cpr, dd->spp_cpr);
पूर्ण

अटल काष्ठा parport_operations parport_ax88796_ops = अणु
	.ग_लिखो_data	= parport_ax88796_ग_लिखो_data,
	.पढ़ो_data	= parport_ax88796_पढ़ो_data,

	.ग_लिखो_control	= parport_ax88796_ग_लिखो_control,
	.पढ़ो_control	= parport_ax88796_पढ़ो_control,
	.frob_control	= parport_ax88796_frob_control,

	.पढ़ो_status	= parport_ax88796_पढ़ो_status,

	.enable_irq	= parport_ax88796_enable_irq,
	.disable_irq	= parport_ax88796_disable_irq,

	.data_क्रमward	= parport_ax88796_data_क्रमward,
	.data_reverse	= parport_ax88796_data_reverse,

	.init_state	= parport_ax88796_init_state,
	.save_state	= parport_ax88796_save_state,
	.restore_state	= parport_ax88796_restore_state,

	.epp_ग_लिखो_data	= parport_ieee1284_epp_ग_लिखो_data,
	.epp_पढ़ो_data	= parport_ieee1284_epp_पढ़ो_data,
	.epp_ग_लिखो_addr	= parport_ieee1284_epp_ग_लिखो_addr,
	.epp_पढ़ो_addr	= parport_ieee1284_epp_पढ़ो_addr,

	.ecp_ग_लिखो_data	= parport_ieee1284_ecp_ग_लिखो_data,
	.ecp_पढ़ो_data	= parport_ieee1284_ecp_पढ़ो_data,
	.ecp_ग_लिखो_addr	= parport_ieee1284_ecp_ग_लिखो_addr,

	.compat_ग_लिखो_data	= parport_ieee1284_ग_लिखो_compat,
	.nibble_पढ़ो_data	= parport_ieee1284_पढ़ो_nibble,
	.byte_पढ़ो_data		= parport_ieee1284_पढ़ो_byte,

	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक parport_ax88796_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *_dev = &pdev->dev;
	काष्ठा ax_drvdata *dd;
	काष्ठा parport *pp;
	काष्ठा resource *res;
	अचिन्हित दीर्घ size;
	पूर्णांक spacing;
	पूर्णांक irq;
	पूर्णांक ret;

	dd = kzalloc(माप(*dd), GFP_KERNEL);
	अगर (!dd)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(_dev, "no MEM specified\n");
		ret = -ENXIO;
		जाओ निकास_mem;
	पूर्ण

	size = resource_size(res);
	spacing = size / 3;

	dd->io = request_mem_region(res->start, size, pdev->name);
	अगर (dd->io == शून्य) अणु
		dev_err(_dev, "cannot reserve memory\n");
		ret = -ENXIO;
		जाओ निकास_mem;
	पूर्ण

	dd->base = ioremap(res->start, size);
	अगर (dd->base == शून्य) अणु
		dev_err(_dev, "cannot ioremap region\n");
		ret = -ENXIO;
		जाओ निकास_res;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		irq = PARPORT_IRQ_NONE;

	pp = parport_रेजिस्टर_port((अचिन्हित दीर्घ)dd->base, irq,
				   PARPORT_DMA_NONE,
				   &parport_ax88796_ops);

	अगर (pp == शून्य) अणु
		dev_err(_dev, "failed to register parallel port\n");
		ret = -ENOMEM;
		जाओ निकास_unmap;
	पूर्ण

	pp->निजी_data = dd;
	dd->parport = pp;
	dd->dev = _dev;

	dd->spp_data = dd->base;
	dd->spp_spr  = dd->base + (spacing * 1);
	dd->spp_cpr  = dd->base + (spacing * 2);

	/* initialise the port controls */
	ग_लिखोb(AX_CPR_STRB, dd->spp_cpr);

	अगर (irq >= 0) अणु
		/* request irq */
		ret = request_irq(irq, parport_irq_handler,
				  IRQF_TRIGGER_FALLING, pdev->name, pp);

		अगर (ret < 0)
			जाओ निकास_port;

		dd->irq_enabled = 1;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pp);

	dev_info(_dev, "attached parallel port driver\n");
	parport_announce_port(pp);

	वापस 0;

 निकास_port:
	parport_हटाओ_port(pp);
 निकास_unmap:
	iounmap(dd->base);
 निकास_res:
	release_mem_region(dd->io->start, size);
 निकास_mem:
	kमुक्त(dd);
	वापस ret;
पूर्ण

अटल पूर्णांक parport_ax88796_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा parport *p = platक्रमm_get_drvdata(pdev);
	काष्ठा ax_drvdata *dd = pp_to_drv(p);

	मुक्त_irq(p->irq, p);
	parport_हटाओ_port(p);
	iounmap(dd->base);
	release_mem_region(dd->io->start, resource_size(dd->io));
	kमुक्त(dd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक parport_ax88796_suspend(काष्ठा platक्रमm_device *dev,
				   pm_message_t state)
अणु
	काष्ठा parport *p = platक्रमm_get_drvdata(dev);
	काष्ठा ax_drvdata *dd = pp_to_drv(p);

	parport_ax88796_save_state(p, &dd->suspend);
	ग_लिखोb(AX_CPR_nDOE | AX_CPR_STRB, dd->spp_cpr);
	वापस 0;
पूर्ण

अटल पूर्णांक parport_ax88796_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा parport *p = platक्रमm_get_drvdata(dev);
	काष्ठा ax_drvdata *dd = pp_to_drv(p);

	parport_ax88796_restore_state(p, &dd->suspend);
	वापस 0;
पूर्ण

#अन्यथा
#घोषणा parport_ax88796_suspend शून्य
#घोषणा parport_ax88796_resume  शून्य
#पूर्ण_अगर

MODULE_ALIAS("platform:ax88796-pp");

अटल काष्ठा platक्रमm_driver axdrv = अणु
	.driver		= अणु
		.name	= "ax88796-pp",
	पूर्ण,
	.probe		= parport_ax88796_probe,
	.हटाओ		= parport_ax88796_हटाओ,
	.suspend	= parport_ax88796_suspend,
	.resume		= parport_ax88796_resume,
पूर्ण;

module_platक्रमm_driver(axdrv);

MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("AX88796 Parport parallel port driver");
MODULE_LICENSE("GPL");
