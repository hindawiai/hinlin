<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Aeroflex Gaisler GRGPIO General Purpose I/O cores.
 *
 * 2013 (c) Aeroflex Gaisler AB
 *
 * This driver supports the GRGPIO GPIO core available in the GRLIB VHDL
 * IP core library.
 *
 * Full करोcumentation of the GRGPIO core can be found here:
 * http://www.gaisler.com/products/grlib/grip.pdf
 *
 * See "Documentation/devicetree/bindings/gpio/gpio-grgpio.txt" क्रम
 * inक्रमmation on खोलो firmware properties.
 *
 * Contributors: Andreas Larsson <andreas@gaisler.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/bitops.h>

#घोषणा GRGPIO_MAX_NGPIO 32

#घोषणा GRGPIO_DATA		0x00
#घोषणा GRGPIO_OUTPUT		0x04
#घोषणा GRGPIO_सूची		0x08
#घोषणा GRGPIO_IMASK		0x0c
#घोषणा GRGPIO_IPOL		0x10
#घोषणा GRGPIO_IEDGE		0x14
#घोषणा GRGPIO_BYPASS		0x18
#घोषणा GRGPIO_IMAP_BASE	0x20

/* Structure क्रम an irq of the core - called an underlying irq */
काष्ठा grgpio_uirq अणु
	u8 refcnt; /* Reference counter to manage requesting/मुक्तing of uirq */
	u8 uirq; /* Underlying irq of the gpio driver */
पूर्ण;

/*
 * Structure क्रम an irq of a gpio line handed out by this driver. The index is
 * used to map to the corresponding underlying irq.
 */
काष्ठा grgpio_lirq अणु
	s8 index; /* Index पूर्णांकo काष्ठा grgpio_priv's uirqs, or -1 */
	u8 irq; /* irq क्रम the gpio line */
पूर्ण;

काष्ठा grgpio_priv अणु
	काष्ठा gpio_chip gc;
	व्योम __iomem *regs;
	काष्ठा device *dev;

	u32 imask; /* irq mask shaकरोw रेजिस्टर */

	/*
	 * The grgpio core can have multiple "underlying" irqs. The gpio lines
	 * can be mapped to any one or none of these underlying irqs
	 * independently of each other. This driver sets up an irq करोमुख्य and
	 * hands out separate irqs to each gpio line
	 */
	काष्ठा irq_करोमुख्य *करोमुख्य;

	/*
	 * This array contains inक्रमmation on each underlying irq, each
	 * irq of the grgpio core itself.
	 */
	काष्ठा grgpio_uirq uirqs[GRGPIO_MAX_NGPIO];

	/*
	 * This array contains inक्रमmation क्रम each gpio line on the irqs
	 * obtains from this driver. An index value of -1 क्रम a certain gpio
	 * line indicates that the line has no irq. Otherwise the index connects
	 * the irq to the underlying irq by poपूर्णांकing पूर्णांकo the uirqs array.
	 */
	काष्ठा grgpio_lirq lirqs[GRGPIO_MAX_NGPIO];
पूर्ण;

अटल व्योम grgpio_set_imask(काष्ठा grgpio_priv *priv, अचिन्हित पूर्णांक offset,
			     पूर्णांक val)
अणु
	काष्ठा gpio_chip *gc = &priv->gc;

	अगर (val)
		priv->imask |= BIT(offset);
	अन्यथा
		priv->imask &= ~BIT(offset);
	gc->ग_लिखो_reg(priv->regs + GRGPIO_IMASK, priv->imask);
पूर्ण

अटल पूर्णांक grgpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा grgpio_priv *priv = gpiochip_get_data(gc);

	अगर (offset >= gc->ngpio)
		वापस -ENXIO;

	अगर (priv->lirqs[offset].index < 0)
		वापस -ENXIO;

	वापस irq_create_mapping(priv->करोमुख्य, offset);
पूर्ण

/* -------------------- IRQ chip functions -------------------- */

अटल पूर्णांक grgpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा grgpio_priv *priv = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;
	u32 mask = BIT(d->hwirq);
	u32 ipol;
	u32 iedge;
	u32 pol;
	u32 edge;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_LOW:
		pol = 0;
		edge = 0;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		pol = mask;
		edge = 0;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		pol = 0;
		edge = mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		pol = mask;
		edge = mask;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	ipol = priv->gc.पढ़ो_reg(priv->regs + GRGPIO_IPOL) & ~mask;
	iedge = priv->gc.पढ़ो_reg(priv->regs + GRGPIO_IEDGE) & ~mask;

	priv->gc.ग_लिखो_reg(priv->regs + GRGPIO_IPOL, ipol | pol);
	priv->gc.ग_लिखो_reg(priv->regs + GRGPIO_IEDGE, iedge | edge);

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम grgpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा grgpio_priv *priv = irq_data_get_irq_chip_data(d);
	पूर्णांक offset = d->hwirq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	grgpio_set_imask(priv, offset, 0);

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);
पूर्ण

अटल व्योम grgpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा grgpio_priv *priv = irq_data_get_irq_chip_data(d);
	पूर्णांक offset = d->hwirq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	grgpio_set_imask(priv, offset, 1);

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);
पूर्ण

अटल काष्ठा irq_chip grgpio_irq_chip = अणु
	.name			= "grgpio",
	.irq_mask		= grgpio_irq_mask,
	.irq_unmask		= grgpio_irq_unmask,
	.irq_set_type		= grgpio_irq_set_type,
पूर्ण;

अटल irqवापस_t grgpio_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा grgpio_priv *priv = dev;
	पूर्णांक ngpio = priv->gc.ngpio;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक match = 0;

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	/*
	 * For each gpio line, call its पूर्णांकerrupt handler अगर it its underlying
	 * irq matches the current irq that is handled.
	 */
	क्रम (i = 0; i < ngpio; i++) अणु
		काष्ठा grgpio_lirq *lirq = &priv->lirqs[i];

		अगर (priv->imask & BIT(i) && lirq->index >= 0 &&
		    priv->uirqs[lirq->index].uirq == irq) अणु
			generic_handle_irq(lirq->irq);
			match = 1;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);

	अगर (!match)
		dev_warn(priv->dev, "No gpio line matched irq %d\n", irq);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * This function will be called as a consequence of the call to
 * irq_create_mapping in grgpio_to_irq
 */
अटल पूर्णांक grgpio_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			  irq_hw_number_t hwirq)
अणु
	काष्ठा grgpio_priv *priv = d->host_data;
	काष्ठा grgpio_lirq *lirq;
	काष्ठा grgpio_uirq *uirq;
	अचिन्हित दीर्घ flags;
	पूर्णांक offset = hwirq;
	पूर्णांक ret = 0;

	अगर (!priv)
		वापस -EINVAL;

	lirq = &priv->lirqs[offset];
	अगर (lirq->index < 0)
		वापस -EINVAL;

	dev_dbg(priv->dev, "Mapping irq %d for gpio line %d\n",
		irq, offset);

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	/* Request underlying irq अगर not alपढ़ोy requested */
	lirq->irq = irq;
	uirq = &priv->uirqs[lirq->index];
	अगर (uirq->refcnt == 0) अणु
		spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);
		ret = request_irq(uirq->uirq, grgpio_irq_handler, 0,
				  dev_name(priv->dev), priv);
		अगर (ret) अणु
			dev_err(priv->dev,
				"Could not request underlying irq %d\n",
				uirq->uirq);
			वापस ret;
		पूर्ण
		spin_lock_irqsave(&priv->gc.bgpio_lock, flags);
	पूर्ण
	uirq->refcnt++;

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);

	/* Setup irq  */
	irq_set_chip_data(irq, priv);
	irq_set_chip_and_handler(irq, &grgpio_irq_chip,
				 handle_simple_irq);
	irq_set_noprobe(irq);

	वापस ret;
पूर्ण

अटल व्योम grgpio_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	काष्ठा grgpio_priv *priv = d->host_data;
	पूर्णांक index;
	काष्ठा grgpio_lirq *lirq;
	काष्ठा grgpio_uirq *uirq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ngpio = priv->gc.ngpio;
	पूर्णांक i;

	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	/* Free underlying irq अगर last user unmapped */
	index = -1;
	क्रम (i = 0; i < ngpio; i++) अणु
		lirq = &priv->lirqs[i];
		अगर (lirq->irq == irq) अणु
			grgpio_set_imask(priv, i, 0);
			lirq->irq = 0;
			index = lirq->index;
			अवरोध;
		पूर्ण
	पूर्ण
	WARN_ON(index < 0);

	अगर (index >= 0) अणु
		uirq = &priv->uirqs[lirq->index];
		uirq->refcnt--;
		अगर (uirq->refcnt == 0) अणु
			spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);
			मुक्त_irq(uirq->uirq, priv);
			वापस;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops grgpio_irq_करोमुख्य_ops = अणु
	.map	= grgpio_irq_map,
	.unmap	= grgpio_irq_unmap,
पूर्ण;

/* ------------------------------------------------------------ */

अटल पूर्णांक grgpio_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	व्योम  __iomem *regs;
	काष्ठा gpio_chip *gc;
	काष्ठा grgpio_priv *priv;
	पूर्णांक err;
	u32 prop;
	s32 *irqmap;
	पूर्णांक size;
	पूर्णांक i;

	priv = devm_kzalloc(&ofdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	regs = devm_platक्रमm_ioremap_resource(ofdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	gc = &priv->gc;
	err = bgpio_init(gc, &ofdev->dev, 4, regs + GRGPIO_DATA,
			 regs + GRGPIO_OUTPUT, शून्य, regs + GRGPIO_सूची, शून्य,
			 BGPIOF_BIG_ENDIAN_BYTE_ORDER);
	अगर (err) अणु
		dev_err(&ofdev->dev, "bgpio_init() failed\n");
		वापस err;
	पूर्ण

	priv->regs = regs;
	priv->imask = gc->पढ़ो_reg(regs + GRGPIO_IMASK);
	priv->dev = &ofdev->dev;

	gc->of_node = np;
	gc->owner = THIS_MODULE;
	gc->to_irq = grgpio_to_irq;
	gc->label = devm_kaप्र_लिखो(&ofdev->dev, GFP_KERNEL, "%pOF", np);
	gc->base = -1;

	err = of_property_पढ़ो_u32(np, "nbits", &prop);
	अगर (err || prop <= 0 || prop > GRGPIO_MAX_NGPIO) अणु
		gc->ngpio = GRGPIO_MAX_NGPIO;
		dev_dbg(&ofdev->dev,
			"No or invalid nbits property: assume %d\n", gc->ngpio);
	पूर्ण अन्यथा अणु
		gc->ngpio = prop;
	पूर्ण

	/*
	 * The irqmap contains the index values indicating which underlying irq,
	 * अगर anyone, is connected to that line
	 */
	irqmap = (s32 *)of_get_property(np, "irqmap", &size);
	अगर (irqmap) अणु
		अगर (size < gc->ngpio) अणु
			dev_err(&ofdev->dev,
				"irqmap shorter than ngpio (%d < %d)\n",
				size, gc->ngpio);
			वापस -EINVAL;
		पूर्ण

		priv->करोमुख्य = irq_करोमुख्य_add_linear(np, gc->ngpio,
						     &grgpio_irq_करोमुख्य_ops,
						     priv);
		अगर (!priv->करोमुख्य) अणु
			dev_err(&ofdev->dev, "Could not add irq domain\n");
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < gc->ngpio; i++) अणु
			काष्ठा grgpio_lirq *lirq;
			पूर्णांक ret;

			lirq = &priv->lirqs[i];
			lirq->index = irqmap[i];

			अगर (lirq->index < 0)
				जारी;

			ret = platक्रमm_get_irq(ofdev, lirq->index);
			अगर (ret <= 0) अणु
				/*
				 * Continue without irq functionality क्रम that
				 * gpio line
				 */
				जारी;
			पूर्ण
			priv->uirqs[lirq->index].uirq = ret;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(ofdev, priv);

	err = gpiochip_add_data(gc, priv);
	अगर (err) अणु
		dev_err(&ofdev->dev, "Could not add gpiochip\n");
		अगर (priv->करोमुख्य)
			irq_करोमुख्य_हटाओ(priv->करोमुख्य);
		वापस err;
	पूर्ण

	dev_info(&ofdev->dev, "regs=0x%p, base=%d, ngpio=%d, irqs=%s\n",
		 priv->regs, gc->base, gc->ngpio, priv->करोमुख्य ? "on" : "off");

	वापस 0;
पूर्ण

अटल पूर्णांक grgpio_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा grgpio_priv *priv = platक्रमm_get_drvdata(ofdev);
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (priv->करोमुख्य) अणु
		क्रम (i = 0; i < GRGPIO_MAX_NGPIO; i++) अणु
			अगर (priv->uirqs[i].refcnt != 0) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	gpiochip_हटाओ(&priv->gc);

	अगर (priv->करोमुख्य)
		irq_करोमुख्य_हटाओ(priv->करोमुख्य);

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id grgpio_match[] = अणु
	अणु.name = "GAISLER_GPIO"पूर्ण,
	अणु.name = "01_01a"पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, grgpio_match);

अटल काष्ठा platक्रमm_driver grgpio_driver = अणु
	.driver = अणु
		.name = "grgpio",
		.of_match_table = grgpio_match,
	पूर्ण,
	.probe = grgpio_probe,
	.हटाओ = grgpio_हटाओ,
पूर्ण;
module_platक्रमm_driver(grgpio_driver);

MODULE_AUTHOR("Aeroflex Gaisler AB.");
MODULE_DESCRIPTION("Driver for Aeroflex Gaisler GRGPIO");
MODULE_LICENSE("GPL");
