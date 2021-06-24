<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCMCIA driver क्रम SL811HS (as found in REX-CFU1U)
 * Filename: sl811_cs.c
 * Author:   Yukio Yamamoto
 *
 *  Port to sl811-hcd and 2.6.x by
 *    Botond Botyanszki <boti@rockeपंचांगail.com>
 *    Simon Pickering
 *
 *  Last update: 2005-05-12
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>

#समावेश <linux/usb/sl811.h>

MODULE_AUTHOR("Botond Botyanszki");
MODULE_DESCRIPTION("REX-CFU1U PCMCIA driver for 2.6");
MODULE_LICENSE("GPL");


/*====================================================================*/
/* MACROS                                                             */
/*====================================================================*/

#घोषणा INFO(args...) prपूर्णांकk(KERN_INFO "sl811_cs: " args)

/*====================================================================*/
/* VARIABLES                                                          */
/*====================================================================*/

प्रकार काष्ठा local_info_t अणु
	काष्ठा pcmcia_device	*p_dev;
पूर्ण local_info_t;

अटल व्योम sl811_cs_release(काष्ठा pcmcia_device * link);

/*====================================================================*/

अटल व्योम release_platक्रमm_dev(काष्ठा device * dev)
अणु
	dev_dbg(dev, "sl811_cs platform_dev release\n");
	dev->parent = शून्य;
पूर्ण

अटल काष्ठा sl811_platक्रमm_data platक्रमm_data = अणु
	.potpg		= 100,
	.घातer		= 50,		/* == 100mA */
	// .reset	= ... FIXME:  invoke CF reset on the card
पूर्ण;

अटल काष्ठा resource resources[] = अणु
	[0] = अणु
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[1] = अणु
		// .name   = "address",
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[2] = अणु
		// .name   = "data",
		.flags	= IORESOURCE_IO,
	पूर्ण,
पूर्ण;

बाह्य काष्ठा platक्रमm_driver sl811h_driver;

अटल काष्ठा platक्रमm_device platक्रमm_dev = अणु
	.id			= -1,
	.dev = अणु
		.platक्रमm_data = &platक्रमm_data,
		.release       = release_platक्रमm_dev,
	पूर्ण,
	.resource		= resources,
	.num_resources		= ARRAY_SIZE(resources),
पूर्ण;

अटल पूर्णांक sl811_hc_init(काष्ठा device *parent, resource_माप_प्रकार base_addr,
			 पूर्णांक irq)
अणु
	अगर (platक्रमm_dev.dev.parent)
		वापस -EBUSY;
	platक्रमm_dev.dev.parent = parent;

	/* finish setting up the platक्रमm device */
	resources[0].start = irq;

	resources[1].start = base_addr;
	resources[1].end = base_addr;

	resources[2].start = base_addr + 1;
	resources[2].end   = base_addr + 1;

	/* The driver core will probe क्रम us.  We know sl811-hcd has been
	 * initialized alपढ़ोy because of the link order dependency created
	 * by referencing "sl811h_driver".
	 */
	platक्रमm_dev.name = sl811h_driver.driver.name;
	वापस platक्रमm_device_रेजिस्टर(&platक्रमm_dev);
पूर्ण

/*====================================================================*/

अटल व्योम sl811_cs_detach(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "sl811_cs_detach\n");

	sl811_cs_release(link);

	/* This poपूर्णांकs to the parent local_info_t काष्ठा */
	kमुक्त(link->priv);
पूर्ण

अटल व्योम sl811_cs_release(काष्ठा pcmcia_device * link)
अणु
	dev_dbg(&link->dev, "sl811_cs_release\n");

	pcmcia_disable_device(link);
	platक्रमm_device_unरेजिस्टर(&platक्रमm_dev);
पूर्ण

अटल पूर्णांक sl811_cs_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	अगर (p_dev->config_index == 0)
		वापस -EINVAL;

	वापस pcmcia_request_io(p_dev);
पूर्ण


अटल पूर्णांक sl811_cs_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा device		*parent = &link->dev;
	पूर्णांक			ret;

	dev_dbg(&link->dev, "sl811_cs_config\n");

	link->config_flags |= CONF_ENABLE_IRQ |	CONF_AUTO_SET_VPP |
		CONF_AUTO_CHECK_VCC | CONF_AUTO_SET_IO;

	अगर (pcmcia_loop_config(link, sl811_cs_config_check, शून्य))
		जाओ failed;

	/* require an IRQ and two रेजिस्टरs */
	अगर (resource_size(link->resource[0]) < 2)
		जाओ failed;

	अगर (!link->irq)
		जाओ failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	अगर (sl811_hc_init(parent, link->resource[0]->start, link->irq)
			< 0) अणु
failed:
		prपूर्णांकk(KERN_WARNING "sl811_cs_config failed\n");
		sl811_cs_release(link);
		वापस  -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sl811_cs_probe(काष्ठा pcmcia_device *link)
अणु
	local_info_t *local;

	local = kzalloc(माप(local_info_t), GFP_KERNEL);
	अगर (!local)
		वापस -ENOMEM;
	local->p_dev = link;
	link->priv = local;

	वापस sl811_cs_config(link);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id sl811_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0xc015, 0x0001), /* RATOC USB HOST CF+ Card */
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, sl811_ids);

अटल काष्ठा pcmcia_driver sl811_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "sl811_cs",
	.probe		= sl811_cs_probe,
	.हटाओ		= sl811_cs_detach,
	.id_table	= sl811_ids,
पूर्ण;
module_pcmcia_driver(sl811_cs_driver);
