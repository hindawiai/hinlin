<शैली गुरु>
/* airport.c
 *
 * A driver क्रम "Hermes" chipset based Apple Airport wireless
 * card.
 *
 * Copyright notice & release notes in file मुख्य.c
 *
 * Note specअगरic to airport stub:
 *
 *  0.05 : first version of the new split driver
 *  0.06 : fix possible hang on घातerup, add sleep support
 */

#घोषणा DRIVER_NAME "airport"
#घोषणा PFX DRIVER_NAME ": "

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/pmac_feature.h>

#समावेश "orinoco.h"

#घोषणा AIRPORT_IO_LEN	(0x1000)	/* one page */

काष्ठा airport अणु
	काष्ठा macio_dev *mdev;
	व्योम __iomem *vaddr;
	अचिन्हित पूर्णांक irq;
	पूर्णांक irq_requested;
	पूर्णांक ndev_रेजिस्टरed;
पूर्ण;

अटल पूर्णांक
airport_suspend(काष्ठा macio_dev *mdev, pm_message_t state)
अणु
	काष्ठा orinoco_निजी *priv = dev_get_drvdata(&mdev->ofdev.dev);
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा airport *card = priv->card;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	prपूर्णांकk(KERN_DEBUG "%s: Airport entering sleep mode\n", dev->name);

	err = orinoco_lock(priv, &flags);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: hw_unavailable on PBOOK_SLEEP_NOW\n",
		       dev->name);
		वापस 0;
	पूर्ण

	orinoco_करोwn(priv);
	orinoco_unlock(priv, &flags);

	disable_irq(card->irq);
	pmac_call_feature(PMAC_FTR_AIRPORT_ENABLE,
			  macio_get_of_node(mdev), 0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
airport_resume(काष्ठा macio_dev *mdev)
अणु
	काष्ठा orinoco_निजी *priv = dev_get_drvdata(&mdev->ofdev.dev);
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा airport *card = priv->card;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	prपूर्णांकk(KERN_DEBUG "%s: Airport waking up\n", dev->name);

	pmac_call_feature(PMAC_FTR_AIRPORT_ENABLE,
			  macio_get_of_node(mdev), 0, 1);
	msleep(200);

	enable_irq(card->irq);

	priv->hw.ops->lock_irqsave(&priv->lock, &flags);
	err = orinoco_up(priv);
	priv->hw.ops->unlock_irqrestore(&priv->lock, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक
airport_detach(काष्ठा macio_dev *mdev)
अणु
	काष्ठा orinoco_निजी *priv = dev_get_drvdata(&mdev->ofdev.dev);
	काष्ठा airport *card = priv->card;

	अगर (card->ndev_रेजिस्टरed)
		orinoco_अगर_del(priv);
	card->ndev_रेजिस्टरed = 0;

	अगर (card->irq_requested)
		मुक्त_irq(card->irq, priv);
	card->irq_requested = 0;

	अगर (card->vaddr)
		iounmap(card->vaddr);
	card->vaddr = शून्य;

	macio_release_resource(mdev, 0);

	pmac_call_feature(PMAC_FTR_AIRPORT_ENABLE,
			  macio_get_of_node(mdev), 0, 0);
	ssleep(1);

	macio_set_drvdata(mdev, शून्य);
	मुक्त_orinocodev(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक airport_hard_reset(काष्ठा orinoco_निजी *priv)
अणु
	/* It would be nice to घातer cycle the Airport क्रम a real hard
	 * reset, but क्रम some reason although it appears to
	 * re-initialize properly, it falls in a screaming heap
	 * लघुly afterwards. */
#अगर 0
	काष्ठा airport *card = priv->card;

	/* Vitally important.  If we करोn't करो this it seems we get an
	 * पूर्णांकerrupt somewhere during the घातer cycle, since
	 * hw_unavailable is alपढ़ोy set it करोesn't get ACKed, we get
	 * पूर्णांकo an पूर्णांकerrupt loop and the PMU decides to turn us
	 * off. */
	disable_irq(card->irq);

	pmac_call_feature(PMAC_FTR_AIRPORT_ENABLE,
			  macio_get_of_node(card->mdev), 0, 0);
	ssleep(1);
	pmac_call_feature(PMAC_FTR_AIRPORT_ENABLE,
			  macio_get_of_node(card->mdev), 0, 1);
	ssleep(1);

	enable_irq(card->irq);
	ssleep(1);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक
airport_attach(काष्ठा macio_dev *mdev, स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा orinoco_निजी *priv;
	काष्ठा airport *card;
	अचिन्हित दीर्घ phys_addr;
	काष्ठा hermes *hw;

	अगर (macio_resource_count(mdev) < 1 || macio_irq_count(mdev) < 1) अणु
		prपूर्णांकk(KERN_ERR PFX "Wrong interrupt/addresses in OF tree\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate space क्रम निजी device-specअगरic data */
	priv = alloc_orinocodev(माप(*card), &mdev->ofdev.dev,
				airport_hard_reset, शून्य);
	अगर (!priv) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate network device\n");
		वापस -ENODEV;
	पूर्ण
	card = priv->card;

	hw = &priv->hw;
	card->mdev = mdev;

	अगर (macio_request_resource(mdev, 0, DRIVER_NAME)) अणु
		prपूर्णांकk(KERN_ERR PFX "can't request IO resource !\n");
		मुक्त_orinocodev(priv);
		वापस -EBUSY;
	पूर्ण

	macio_set_drvdata(mdev, priv);

	/* Setup पूर्णांकerrupts & base address */
	card->irq = macio_irq(mdev, 0);
	phys_addr = macio_resource_start(mdev, 0);  /* Physical address */
	prपूर्णांकk(KERN_DEBUG PFX "Physical address %lx\n", phys_addr);
	card->vaddr = ioremap(phys_addr, AIRPORT_IO_LEN);
	अगर (!card->vaddr) अणु
		prपूर्णांकk(KERN_ERR PFX "ioremap() failed\n");
		जाओ failed;
	पूर्ण

	hermes_काष्ठा_init(hw, card->vaddr, HERMES_16BIT_REGSPACING);

	/* Power up card */
	pmac_call_feature(PMAC_FTR_AIRPORT_ENABLE,
			  macio_get_of_node(mdev), 0, 1);
	ssleep(1);

	/* Reset it beक्रमe we get the पूर्णांकerrupt */
	hw->ops->init(hw);

	अगर (request_irq(card->irq, orinoco_पूर्णांकerrupt, 0, DRIVER_NAME, priv)) अणु
		prपूर्णांकk(KERN_ERR PFX "Couldn't get IRQ %d\n", card->irq);
		जाओ failed;
	पूर्ण
	card->irq_requested = 1;

	/* Initialise the मुख्य driver */
	अगर (orinoco_init(priv) != 0) अणु
		prपूर्णांकk(KERN_ERR PFX "orinoco_init() failed\n");
		जाओ failed;
	पूर्ण

	/* Register an पूर्णांकerface with the stack */
	अगर (orinoco_अगर_add(priv, phys_addr, card->irq, शून्य) != 0) अणु
		prपूर्णांकk(KERN_ERR PFX "orinoco_if_add() failed\n");
		जाओ failed;
	पूर्ण
	card->ndev_रेजिस्टरed = 1;
	वापस 0;
 failed:
	airport_detach(mdev);
	वापस -ENODEV;
पूर्ण				/* airport_attach */


अटल अक्षर version[] __initdata = DRIVER_NAME " " DRIVER_VERSION
	" (Benjamin Herrenschmidt <benh@kernel.crashing.org>)";
MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("Driver for the Apple Airport wireless card.");
MODULE_LICENSE("Dual MPL/GPL");

अटल स्थिर काष्ठा of_device_id airport_match[] = अणु
	अणु
	.name		= "radio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, airport_match);

अटल काष्ठा macio_driver airport_driver = अणु
	.driver = अणु
		.name		= DRIVER_NAME,
		.owner		= THIS_MODULE,
		.of_match_table	= airport_match,
	पूर्ण,
	.probe		= airport_attach,
	.हटाओ		= airport_detach,
	.suspend	= airport_suspend,
	.resume		= airport_resume,
पूर्ण;

अटल पूर्णांक __init
init_airport(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "%s\n", version);

	वापस macio_रेजिस्टर_driver(&airport_driver);
पूर्ण

अटल व्योम __निकास
निकास_airport(व्योम)
अणु
	macio_unरेजिस्टर_driver(&airport_driver);
पूर्ण

module_init(init_airport);
module_निकास(निकास_airport);
