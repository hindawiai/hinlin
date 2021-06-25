<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम generic MPU-401 boards (UART mode only)
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Copyright (c) 2004 by Castet Matthieu <castet.matthieu@मुक्त.fr>
 */

#समावेश <linux/init.h>
#समावेश <linux/pnp.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("MPU-401 UART");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = -2पूर्ण; /* exclude the first card */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
#अगर_घोषित CONFIG_PNP
अटल bool pnp[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
#पूर्ण_अगर
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* MPU-401 port number */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* MPU-401 IRQ */
अटल bool uart_enter[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for MPU-401 device.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for MPU-401 device.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable MPU-401 device.");
#अगर_घोषित CONFIG_PNP
module_param_array(pnp, bool, शून्य, 0444);
MODULE_PARM_DESC(pnp, "PnP detection for MPU-401 device.");
#पूर्ण_अगर
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for MPU-401 device.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for MPU-401 device.");
module_param_array(uart_enter, bool, शून्य, 0444);
MODULE_PARM_DESC(uart_enter, "Issue UART_ENTER command at open.");

अटल काष्ठा platक्रमm_device *platक्रमm_devices[SNDRV_CARDS];
अटल पूर्णांक pnp_रेजिस्टरed;
अटल अचिन्हित पूर्णांक snd_mpu401_devices;

अटल पूर्णांक snd_mpu401_create(काष्ठा device *devptr, पूर्णांक dev,
			     काष्ठा snd_card **rcard)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (!uart_enter[dev])
		snd_prपूर्णांकk(KERN_ERR "the uart_enter option is obsolete; remove it\n");

	*rcard = शून्य;
	err = snd_card_new(devptr, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;
	म_नकल(card->driver, "MPU-401 UART");
	म_नकल(card->लघुname, card->driver);
	प्र_लिखो(card->दीर्घname, "%s at %#lx, ", card->लघुname, port[dev]);
	अगर (irq[dev] >= 0) अणु
		प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname), "irq %d", irq[dev]);
	पूर्ण अन्यथा अणु
		म_जोड़ो(card->दीर्घname, "polled");
	पूर्ण

	err = snd_mpu401_uart_new(card, 0, MPU401_HW_MPU401, port[dev], 0,
				  irq[dev], शून्य);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "MPU401 not detected at 0x%lx\n", port[dev]);
		जाओ _err;
	पूर्ण

	*rcard = card;
	वापस 0;

 _err:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_mpu401_probe(काष्ठा platक्रमm_device *devptr)
अणु
	पूर्णांक dev = devptr->id;
	पूर्णांक err;
	काष्ठा snd_card *card;

	अगर (port[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR "specify port\n");
		वापस -EINVAL;
	पूर्ण
	अगर (irq[dev] == SNDRV_AUTO_IRQ) अणु
		snd_prपूर्णांकk(KERN_ERR "specify or disable IRQ\n");
		वापस -EINVAL;
	पूर्ण
	err = snd_mpu401_create(&devptr->dev, dev, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	platक्रमm_set_drvdata(devptr, card);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mpu401_हटाओ(काष्ठा platक्रमm_device *devptr)
अणु
	snd_card_मुक्त(platक्रमm_get_drvdata(devptr));
	वापस 0;
पूर्ण

#घोषणा SND_MPU401_DRIVER	"snd_mpu401"

अटल काष्ठा platक्रमm_driver snd_mpu401_driver = अणु
	.probe		= snd_mpu401_probe,
	.हटाओ		= snd_mpu401_हटाओ,
	.driver		= अणु
		.name	= SND_MPU401_DRIVER,
	पूर्ण,
पूर्ण;


#अगर_घोषित CONFIG_PNP

#घोषणा IO_EXTENT 2

अटल स्थिर काष्ठा pnp_device_id snd_mpu401_pnpids[] = अणु
	अणु .id = "PNPb006" पूर्ण,
	अणु .id = "" पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp, snd_mpu401_pnpids);

अटल पूर्णांक snd_mpu401_pnp(पूर्णांक dev, काष्ठा pnp_dev *device,
			  स्थिर काष्ठा pnp_device_id *id)
अणु
	अगर (!pnp_port_valid(device, 0) ||
	    pnp_port_flags(device, 0) & IORESOURCE_DISABLED) अणु
		snd_prपूर्णांकk(KERN_ERR "no PnP port\n");
		वापस -ENODEV;
	पूर्ण
	अगर (pnp_port_len(device, 0) < IO_EXTENT) अणु
		snd_prपूर्णांकk(KERN_ERR "PnP port length is %llu, expected %d\n",
			   (अचिन्हित दीर्घ दीर्घ)pnp_port_len(device, 0),
			   IO_EXTENT);
		वापस -ENODEV;
	पूर्ण
	port[dev] = pnp_port_start(device, 0);

	अगर (!pnp_irq_valid(device, 0) ||
	    pnp_irq_flags(device, 0) & IORESOURCE_DISABLED) अणु
		snd_prपूर्णांकk(KERN_WARNING "no PnP irq, using polling\n");
		irq[dev] = -1;
	पूर्ण अन्यथा अणु
		irq[dev] = pnp_irq(device, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mpu401_pnp_probe(काष्ठा pnp_dev *pnp_dev,
				स्थिर काष्ठा pnp_device_id *id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	पूर्णांक err;

	क्रम ( ; dev < SNDRV_CARDS; ++dev) अणु
		अगर (!enable[dev] || !pnp[dev])
			जारी;
		err = snd_mpu401_pnp(dev, pnp_dev, id);
		अगर (err < 0)
			वापस err;
		err = snd_mpu401_create(&pnp_dev->dev, dev, &card);
		अगर (err < 0)
			वापस err;
		अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
		pnp_set_drvdata(pnp_dev, card);
		snd_mpu401_devices++;
		++dev;
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम snd_mpu401_pnp_हटाओ(काष्ठा pnp_dev *dev)
अणु
	काष्ठा snd_card *card = (काष्ठा snd_card *) pnp_get_drvdata(dev);

	snd_card_disconnect(card);
	snd_card_मुक्त_when_बंदd(card);
पूर्ण

अटल काष्ठा pnp_driver snd_mpu401_pnp_driver = अणु
	.name = "mpu401",
	.id_table = snd_mpu401_pnpids,
	.probe = snd_mpu401_pnp_probe,
	.हटाओ = snd_mpu401_pnp_हटाओ,
पूर्ण;
#अन्यथा
अटल काष्ठा pnp_driver snd_mpu401_pnp_driver;
#पूर्ण_अगर

अटल व्योम snd_mpu401_unरेजिस्टर_all(व्योम)
अणु
	पूर्णांक i;

	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&snd_mpu401_pnp_driver);
	क्रम (i = 0; i < ARRAY_SIZE(platक्रमm_devices); ++i)
		platक्रमm_device_unरेजिस्टर(platक्रमm_devices[i]);
	platक्रमm_driver_unरेजिस्टर(&snd_mpu401_driver);
पूर्ण

अटल पूर्णांक __init alsa_card_mpu401_init(व्योम)
अणु
	पूर्णांक i, err;

	अगर ((err = platक्रमm_driver_रेजिस्टर(&snd_mpu401_driver)) < 0)
		वापस err;

	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		काष्ठा platक्रमm_device *device;
		अगर (! enable[i])
			जारी;
#अगर_घोषित CONFIG_PNP
		अगर (pnp[i])
			जारी;
#पूर्ण_अगर
		device = platक्रमm_device_रेजिस्टर_simple(SND_MPU401_DRIVER,
							 i, शून्य, 0);
		अगर (IS_ERR(device))
			जारी;
		अगर (!platक्रमm_get_drvdata(device)) अणु
			platक्रमm_device_unरेजिस्टर(device);
			जारी;
		पूर्ण
		platक्रमm_devices[i] = device;
		snd_mpu401_devices++;
	पूर्ण
	err = pnp_रेजिस्टर_driver(&snd_mpu401_pnp_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;

	अगर (!snd_mpu401_devices) अणु
#अगर_घोषित MODULE
		prपूर्णांकk(KERN_ERR "MPU-401 device not found or device busy\n");
#पूर्ण_अगर
		snd_mpu401_unरेजिस्टर_all();
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_card_mpu401_निकास(व्योम)
अणु
	snd_mpu401_unरेजिस्टर_all();
पूर्ण

module_init(alsa_card_mpu401_init)
module_निकास(alsa_card_mpu401_निकास)
