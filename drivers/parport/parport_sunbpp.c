<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* parport_sunbpp.c: Parallel-port routines क्रम SBUS
 * 
 * Author: Derrick J. Brashear <shaकरोw@dementia.org>
 *
 * based on work by:
 *          Phil Blundell <philb@gnu.org>
 *          Tim Waugh <tim@cyberelk.demon.co.uk>
 *	    Jose Renau <renau@acm.org>
 *          David Campbell <campbell@tirian.che.curtin.edu.au>
 *          Grant Guenther <grant@torque.net>
 *          Eddie C. Dost <ecd@skynet.be>
 *          Stephen Williams (steve@icarus.com)
 *          Gus Baldauf (gbaldauf@ix.netcom.com)
 *          Peter Zaitcev
 *          Tom Dyas
 *
 * Updated to new SBUS device framework: David S. Miller <davem@davemloft.net>
 * 
 */

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/parport.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/oplib.h>           /* OpenProm Library */
#समावेश <यंत्र/dma.h>             /* BPP uses LSI 64854 क्रम DMA */
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sunbpp.h>

#अघोषित __SUNBPP_DEBUG
#अगर_घोषित __SUNBPP_DEBUG
#घोषणा dprपूर्णांकk(x) prपूर्णांकk x
#अन्यथा
#घोषणा dprपूर्णांकk(x)
#पूर्ण_अगर

अटल व्योम parport_sunbpp_disable_irq(काष्ठा parport *p)
अणु
	काष्ठा bpp_regs __iomem *regs = (काष्ठा bpp_regs __iomem *)p->base;
	u32 पंचांगp;

	पंचांगp = sbus_पढ़ोl(&regs->p_csr);
	पंचांगp &= ~DMA_INT_ENAB;
	sbus_ग_लिखोl(पंचांगp, &regs->p_csr);
पूर्ण

अटल व्योम parport_sunbpp_enable_irq(काष्ठा parport *p)
अणु
	काष्ठा bpp_regs __iomem *regs = (काष्ठा bpp_regs __iomem *)p->base;
	u32 पंचांगp;

	पंचांगp = sbus_पढ़ोl(&regs->p_csr);
	पंचांगp |= DMA_INT_ENAB;
	sbus_ग_लिखोl(पंचांगp, &regs->p_csr);
पूर्ण

अटल व्योम parport_sunbpp_ग_लिखो_data(काष्ठा parport *p, अचिन्हित अक्षर d)
अणु
	काष्ठा bpp_regs __iomem *regs = (काष्ठा bpp_regs __iomem *)p->base;

	sbus_ग_लिखोb(d, &regs->p_dr);
	dprपूर्णांकk((KERN_DEBUG "wrote 0x%x\n", d));
पूर्ण

अटल अचिन्हित अक्षर parport_sunbpp_पढ़ो_data(काष्ठा parport *p)
अणु
	काष्ठा bpp_regs __iomem *regs = (काष्ठा bpp_regs __iomem *)p->base;

	वापस sbus_पढ़ोb(&regs->p_dr);
पूर्ण

अटल अचिन्हित अक्षर status_sunbpp_to_pc(काष्ठा parport *p)
अणु
	काष्ठा bpp_regs __iomem *regs = (काष्ठा bpp_regs __iomem *)p->base;
	अचिन्हित अक्षर bits = 0;
	अचिन्हित अक्षर value_tcr = sbus_पढ़ोb(&regs->p_tcr);
	अचिन्हित अक्षर value_ir = sbus_पढ़ोb(&regs->p_ir);

	अगर (!(value_ir & P_IR_ERR))
		bits |= PARPORT_STATUS_ERROR;
	अगर (!(value_ir & P_IR_SLCT))
		bits |= PARPORT_STATUS_SELECT;
	अगर (!(value_ir & P_IR_PE))
		bits |= PARPORT_STATUS_PAPEROUT;
	अगर (value_tcr & P_TCR_ACK)
		bits |= PARPORT_STATUS_ACK;
	अगर (!(value_tcr & P_TCR_BUSY))
		bits |= PARPORT_STATUS_BUSY;

	dprपूर्णांकk((KERN_DEBUG "tcr 0x%x ir 0x%x\n", value_tcr, value_ir));
	dprपूर्णांकk((KERN_DEBUG "read status 0x%x\n", bits));
	वापस bits;
पूर्ण

अटल अचिन्हित अक्षर control_sunbpp_to_pc(काष्ठा parport *p)
अणु
	काष्ठा bpp_regs __iomem *regs = (काष्ठा bpp_regs __iomem *)p->base;
	अचिन्हित अक्षर bits = 0;
	अचिन्हित अक्षर value_tcr = sbus_पढ़ोb(&regs->p_tcr);
	अचिन्हित अक्षर value_or = sbus_पढ़ोb(&regs->p_or);

	अगर (!(value_tcr & P_TCR_DS))
		bits |= PARPORT_CONTROL_STROBE;
	अगर (!(value_or & P_OR_AFXN))
		bits |= PARPORT_CONTROL_AUTOFD;
	अगर (!(value_or & P_OR_INIT))
		bits |= PARPORT_CONTROL_INIT;
	अगर (value_or & P_OR_SLCT_IN)
		bits |= PARPORT_CONTROL_SELECT;

	dprपूर्णांकk((KERN_DEBUG "tcr 0x%x or 0x%x\n", value_tcr, value_or));
	dprपूर्णांकk((KERN_DEBUG "read control 0x%x\n", bits));
	वापस bits;
पूर्ण

अटल अचिन्हित अक्षर parport_sunbpp_पढ़ो_control(काष्ठा parport *p)
अणु
	वापस control_sunbpp_to_pc(p);
पूर्ण

अटल अचिन्हित अक्षर parport_sunbpp_frob_control(काष्ठा parport *p,
						 अचिन्हित अक्षर mask,
						 अचिन्हित अक्षर val)
अणु
	काष्ठा bpp_regs __iomem *regs = (काष्ठा bpp_regs __iomem *)p->base;
	अचिन्हित अक्षर value_tcr = sbus_पढ़ोb(&regs->p_tcr);
	अचिन्हित अक्षर value_or = sbus_पढ़ोb(&regs->p_or);

	dprपूर्णांकk((KERN_DEBUG "frob1: tcr 0x%x or 0x%x\n",
		 value_tcr, value_or));
	अगर (mask & PARPORT_CONTROL_STROBE) अणु
		अगर (val & PARPORT_CONTROL_STROBE) अणु
			value_tcr &= ~P_TCR_DS;
		पूर्ण अन्यथा अणु
			value_tcr |= P_TCR_DS;
		पूर्ण
	पूर्ण
	अगर (mask & PARPORT_CONTROL_AUTOFD) अणु
		अगर (val & PARPORT_CONTROL_AUTOFD) अणु
			value_or &= ~P_OR_AFXN;
		पूर्ण अन्यथा अणु
			value_or |= P_OR_AFXN;
		पूर्ण
	पूर्ण
	अगर (mask & PARPORT_CONTROL_INIT) अणु
		अगर (val & PARPORT_CONTROL_INIT) अणु
			value_or &= ~P_OR_INIT;
		पूर्ण अन्यथा अणु
			value_or |= P_OR_INIT;
		पूर्ण
	पूर्ण
	अगर (mask & PARPORT_CONTROL_SELECT) अणु
		अगर (val & PARPORT_CONTROL_SELECT) अणु
			value_or |= P_OR_SLCT_IN;
		पूर्ण अन्यथा अणु
			value_or &= ~P_OR_SLCT_IN;
		पूर्ण
	पूर्ण

	sbus_ग_लिखोb(value_or, &regs->p_or);
	sbus_ग_लिखोb(value_tcr, &regs->p_tcr);
	dprपूर्णांकk((KERN_DEBUG "frob2: tcr 0x%x or 0x%x\n",
		 value_tcr, value_or));
	वापस parport_sunbpp_पढ़ो_control(p);
पूर्ण

अटल व्योम parport_sunbpp_ग_लिखो_control(काष्ठा parport *p, अचिन्हित अक्षर d)
अणु
	स्थिर अचिन्हित अक्षर wm = (PARPORT_CONTROL_STROBE |
				  PARPORT_CONTROL_AUTOFD |
				  PARPORT_CONTROL_INIT |
				  PARPORT_CONTROL_SELECT);

	parport_sunbpp_frob_control (p, wm, d & wm);
पूर्ण

अटल अचिन्हित अक्षर parport_sunbpp_पढ़ो_status(काष्ठा parport *p)
अणु
	वापस status_sunbpp_to_pc(p);
पूर्ण

अटल व्योम parport_sunbpp_data_क्रमward (काष्ठा parport *p)
अणु
	काष्ठा bpp_regs __iomem *regs = (काष्ठा bpp_regs __iomem *)p->base;
	अचिन्हित अक्षर value_tcr = sbus_पढ़ोb(&regs->p_tcr);

	dprपूर्णांकk((KERN_DEBUG "forward\n"));
	value_tcr &= ~P_TCR_सूची;
	sbus_ग_लिखोb(value_tcr, &regs->p_tcr);
पूर्ण

अटल व्योम parport_sunbpp_data_reverse (काष्ठा parport *p)
अणु
	काष्ठा bpp_regs __iomem *regs = (काष्ठा bpp_regs __iomem *)p->base;
	u8 val = sbus_पढ़ोb(&regs->p_tcr);

	dprपूर्णांकk((KERN_DEBUG "reverse\n"));
	val |= P_TCR_सूची;
	sbus_ग_लिखोb(val, &regs->p_tcr);
पूर्ण

अटल व्योम parport_sunbpp_init_state(काष्ठा pardevice *dev, काष्ठा parport_state *s)
अणु
	s->u.pc.ctr = 0xc;
	s->u.pc.ecr = 0x0;
पूर्ण

अटल व्योम parport_sunbpp_save_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	s->u.pc.ctr = parport_sunbpp_पढ़ो_control(p);
पूर्ण

अटल व्योम parport_sunbpp_restore_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	parport_sunbpp_ग_लिखो_control(p, s->u.pc.ctr);
पूर्ण

अटल काष्ठा parport_operations parport_sunbpp_ops = 
अणु
	.ग_लिखो_data	= parport_sunbpp_ग_लिखो_data,
	.पढ़ो_data	= parport_sunbpp_पढ़ो_data,

	.ग_लिखो_control	= parport_sunbpp_ग_लिखो_control,
	.पढ़ो_control	= parport_sunbpp_पढ़ो_control,
	.frob_control	= parport_sunbpp_frob_control,

	.पढ़ो_status	= parport_sunbpp_पढ़ो_status,

	.enable_irq	= parport_sunbpp_enable_irq,
	.disable_irq	= parport_sunbpp_disable_irq,

	.data_क्रमward	= parport_sunbpp_data_क्रमward,
	.data_reverse	= parport_sunbpp_data_reverse,

	.init_state	= parport_sunbpp_init_state,
	.save_state	= parport_sunbpp_save_state,
	.restore_state	= parport_sunbpp_restore_state,

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

अटल पूर्णांक bpp_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा parport_operations *ops;
	काष्ठा bpp_regs __iomem *regs;
	पूर्णांक irq, dma, err = 0, size;
	अचिन्हित अक्षर value_tcr;
	व्योम __iomem *base;
	काष्ठा parport *p;

	irq = op->archdata.irqs[0];
	base = of_ioremap(&op->resource[0], 0,
			  resource_size(&op->resource[0]),
			  "sunbpp");
	अगर (!base)
		वापस -ENODEV;

	size = resource_size(&op->resource[0]);
	dma = PARPORT_DMA_NONE;

	ops = kmemdup(&parport_sunbpp_ops, माप(काष्ठा parport_operations),
		      GFP_KERNEL);
	अगर (!ops) अणु
		err = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	dprपूर्णांकk(("register_port\n"));
	अगर (!(p = parport_रेजिस्टर_port((अचिन्हित दीर्घ)base, irq, dma, ops))) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_ops;
	पूर्ण

	p->size = size;
	p->dev = &op->dev;

	अगर ((err = request_irq(p->irq, parport_irq_handler,
			       IRQF_SHARED, p->name, p)) != 0) अणु
		जाओ out_put_port;
	पूर्ण

	parport_sunbpp_enable_irq(p);

	regs = (काष्ठा bpp_regs __iomem *)p->base;

	value_tcr = sbus_पढ़ोb(&regs->p_tcr);
	value_tcr &= ~P_TCR_सूची;
	sbus_ग_लिखोb(value_tcr, &regs->p_tcr);

	pr_info("%s: sunbpp at 0x%lx\n", p->name, p->base);

	dev_set_drvdata(&op->dev, p);

	parport_announce_port(p);

	वापस 0;

out_put_port:
	parport_put_port(p);

out_मुक्त_ops:
	kमुक्त(ops);

out_unmap:
	of_iounmap(&op->resource[0], base, size);

	वापस err;
पूर्ण

अटल पूर्णांक bpp_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा parport *p = dev_get_drvdata(&op->dev);
	काष्ठा parport_operations *ops = p->ops;

	parport_हटाओ_port(p);

	अगर (p->irq != PARPORT_IRQ_NONE) अणु
		parport_sunbpp_disable_irq(p);
		मुक्त_irq(p->irq, p);
	पूर्ण

	of_iounmap(&op->resource[0], (व्योम __iomem *) p->base, p->size);
	parport_put_port(p);
	kमुक्त(ops);

	dev_set_drvdata(&op->dev, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bpp_match[] = अणु
	अणु
		.name = "SUNW,bpp",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, bpp_match);

अटल काष्ठा platक्रमm_driver bpp_sbus_driver = अणु
	.driver = अणु
		.name = "bpp",
		.of_match_table = bpp_match,
	पूर्ण,
	.probe		= bpp_probe,
	.हटाओ		= bpp_हटाओ,
पूर्ण;

module_platक्रमm_driver(bpp_sbus_driver);

MODULE_AUTHOR("Derrick J Brashear");
MODULE_DESCRIPTION("Parport Driver for Sparc bidirectional Port");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
