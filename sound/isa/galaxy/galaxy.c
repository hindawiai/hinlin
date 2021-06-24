<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Aztech AZT1605/AZT2316 Driver
 * Copyright (C) 2007,2010  Rene Herman
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/isa.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/wss.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>

MODULE_DESCRIPTION(CRD_NAME);
MODULE_AUTHOR("Rene Herman");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CRD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CRD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " CRD_NAME " soundcard.");

अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल दीर्घ wss_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल दीर्घ mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;

module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for " CRD_NAME " driver.");
module_param_hw_array(wss_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(wss_port, "WSS port # for " CRD_NAME " driver.");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for " CRD_NAME " driver.");
module_param_hw_array(fm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fm_port, "FM port # for " CRD_NAME " driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for " CRD_NAME " driver.");
module_param_hw_array(mpu_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(mpu_irq, "MPU-401 IRQ # for " CRD_NAME " driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "Playback DMA # for " CRD_NAME " driver.");
module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "Capture DMA # for " CRD_NAME " driver.");

/*
 * Generic SB DSP support routines
 */

#घोषणा DSP_PORT_RESET		0x6
#घोषणा DSP_PORT_READ		0xa
#घोषणा DSP_PORT_COMMAND	0xc
#घोषणा DSP_PORT_STATUS		0xc
#घोषणा DSP_PORT_DATA_AVAIL	0xe

#घोषणा DSP_SIGNATURE		0xaa

#घोषणा DSP_COMMAND_GET_VERSION	0xe1

अटल पूर्णांक dsp_get_byte(व्योम __iomem *port, u8 *val)
अणु
	पूर्णांक loops = 1000;

	जबतक (!(ioपढ़ो8(port + DSP_PORT_DATA_AVAIL) & 0x80)) अणु
		अगर (!loops--)
			वापस -EIO;
		cpu_relax();
	पूर्ण
	*val = ioपढ़ो8(port + DSP_PORT_READ);
	वापस 0;
पूर्ण

अटल पूर्णांक dsp_reset(व्योम __iomem *port)
अणु
	u8 val;

	ioग_लिखो8(1, port + DSP_PORT_RESET);
	udelay(10);
	ioग_लिखो8(0, port + DSP_PORT_RESET);

	अगर (dsp_get_byte(port, &val) < 0 || val != DSP_SIGNATURE)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक dsp_command(व्योम __iomem *port, u8 cmd)
अणु
	पूर्णांक loops = 1000;

	जबतक (ioपढ़ो8(port + DSP_PORT_STATUS) & 0x80) अणु
		अगर (!loops--)
			वापस -EIO;
		cpu_relax();
	पूर्ण
	ioग_लिखो8(cmd, port + DSP_PORT_COMMAND);
	वापस 0;
पूर्ण

अटल पूर्णांक dsp_get_version(व्योम __iomem *port, u8 *major, u8 *minor)
अणु
	पूर्णांक err;

	err = dsp_command(port, DSP_COMMAND_GET_VERSION);
	अगर (err < 0)
		वापस err;

	err = dsp_get_byte(port, major);
	अगर (err < 0)
		वापस err;

	err = dsp_get_byte(port, minor);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/*
 * Generic WSS support routines
 */

#घोषणा WSS_CONFIG_DMA_0	(1 << 0)
#घोषणा WSS_CONFIG_DMA_1	(2 << 0)
#घोषणा WSS_CONFIG_DMA_3	(3 << 0)
#घोषणा WSS_CONFIG_DUPLEX	(1 << 2)
#घोषणा WSS_CONFIG_IRQ_7	(1 << 3)
#घोषणा WSS_CONFIG_IRQ_9	(2 << 3)
#घोषणा WSS_CONFIG_IRQ_10	(3 << 3)
#घोषणा WSS_CONFIG_IRQ_11	(4 << 3)

#घोषणा WSS_PORT_CONFIG		0
#घोषणा WSS_PORT_SIGNATURE	3

#घोषणा WSS_SIGNATURE		4

अटल पूर्णांक wss_detect(व्योम __iomem *wss_port)
अणु
	अगर ((ioपढ़ो8(wss_port + WSS_PORT_SIGNATURE) & 0x3f) != WSS_SIGNATURE)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम wss_set_config(व्योम __iomem *wss_port, u8 wss_config)
अणु
	ioग_लिखो8(wss_config, wss_port + WSS_PORT_CONFIG);
पूर्ण

/*
 * Aztech Sound Galaxy specअगरics
 */

#घोषणा GALAXY_PORT_CONFIG	1024
#घोषणा CONFIG_PORT_SET		4

#घोषणा DSP_COMMAND_GALAXY_8	8
#घोषणा GALAXY_COMMAND_GET_TYPE	5

#घोषणा DSP_COMMAND_GALAXY_9	9
#घोषणा GALAXY_COMMAND_WSSMODE	0
#घोषणा GALAXY_COMMAND_SB8MODE	1

#घोषणा GALAXY_MODE_WSS		GALAXY_COMMAND_WSSMODE
#घोषणा GALAXY_MODE_SB8		GALAXY_COMMAND_SB8MODE

काष्ठा snd_galaxy अणु
	व्योम __iomem *port;
	व्योम __iomem *config_port;
	व्योम __iomem *wss_port;
	u32 config;
	काष्ठा resource *res_port;
	काष्ठा resource *res_config_port;
	काष्ठा resource *res_wss_port;
पूर्ण;

अटल u32 config[SNDRV_CARDS];
अटल u8 wss_config[SNDRV_CARDS];

अटल पूर्णांक snd_galaxy_match(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	अगर (!enable[n])
		वापस 0;

	चयन (port[n]) अणु
	हाल SNDRV_AUTO_PORT:
		dev_err(dev, "please specify port\n");
		वापस 0;
	हाल 0x220:
		config[n] |= GALAXY_CONFIG_SBA_220;
		अवरोध;
	हाल 0x240:
		config[n] |= GALAXY_CONFIG_SBA_240;
		अवरोध;
	हाल 0x260:
		config[n] |= GALAXY_CONFIG_SBA_260;
		अवरोध;
	हाल 0x280:
		config[n] |= GALAXY_CONFIG_SBA_280;
		अवरोध;
	शेष:
		dev_err(dev, "invalid port %#lx\n", port[n]);
		वापस 0;
	पूर्ण

	चयन (wss_port[n]) अणु
	हाल SNDRV_AUTO_PORT:
		dev_err(dev,  "please specify wss_port\n");
		वापस 0;
	हाल 0x530:
		config[n] |= GALAXY_CONFIG_WSS_ENABLE | GALAXY_CONFIG_WSSA_530;
		अवरोध;
	हाल 0x604:
		config[n] |= GALAXY_CONFIG_WSS_ENABLE | GALAXY_CONFIG_WSSA_604;
		अवरोध;
	हाल 0xe80:
		config[n] |= GALAXY_CONFIG_WSS_ENABLE | GALAXY_CONFIG_WSSA_E80;
		अवरोध;
	हाल 0xf40:
		config[n] |= GALAXY_CONFIG_WSS_ENABLE | GALAXY_CONFIG_WSSA_F40;
		अवरोध;
	शेष:
		dev_err(dev, "invalid WSS port %#lx\n", wss_port[n]);
		वापस 0;
	पूर्ण

	चयन (irq[n]) अणु
	हाल SNDRV_AUTO_IRQ:
		dev_err(dev,  "please specify irq\n");
		वापस 0;
	हाल 7:
		wss_config[n] |= WSS_CONFIG_IRQ_7;
		अवरोध;
	हाल 2:
		irq[n] = 9;
		fallthrough;
	हाल 9:
		wss_config[n] |= WSS_CONFIG_IRQ_9;
		अवरोध;
	हाल 10:
		wss_config[n] |= WSS_CONFIG_IRQ_10;
		अवरोध;
	हाल 11:
		wss_config[n] |= WSS_CONFIG_IRQ_11;
		अवरोध;
	शेष:
		dev_err(dev, "invalid IRQ %d\n", irq[n]);
		वापस 0;
	पूर्ण

	चयन (dma1[n]) अणु
	हाल SNDRV_AUTO_DMA:
		dev_err(dev,  "please specify dma1\n");
		वापस 0;
	हाल 0:
		wss_config[n] |= WSS_CONFIG_DMA_0;
		अवरोध;
	हाल 1:
		wss_config[n] |= WSS_CONFIG_DMA_1;
		अवरोध;
	हाल 3:
		wss_config[n] |= WSS_CONFIG_DMA_3;
		अवरोध;
	शेष:
		dev_err(dev, "invalid playback DMA %d\n", dma1[n]);
		वापस 0;
	पूर्ण

	अगर (dma2[n] == SNDRV_AUTO_DMA || dma2[n] == dma1[n]) अणु
		dma2[n] = -1;
		जाओ mpu;
	पूर्ण

	wss_config[n] |= WSS_CONFIG_DUPLEX;
	चयन (dma2[n]) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		अगर (dma1[n] == 0)
			अवरोध;
		fallthrough;
	शेष:
		dev_err(dev, "invalid capture DMA %d\n", dma2[n]);
		वापस 0;
	पूर्ण

mpu:
	चयन (mpu_port[n]) अणु
	हाल SNDRV_AUTO_PORT:
		dev_warn(dev, "mpu_port not specified; not using MPU-401\n");
		mpu_port[n] = -1;
		जाओ fm;
	हाल 0x300:
		config[n] |= GALAXY_CONFIG_MPU_ENABLE | GALAXY_CONFIG_MPUA_300;
		अवरोध;
	हाल 0x330:
		config[n] |= GALAXY_CONFIG_MPU_ENABLE | GALAXY_CONFIG_MPUA_330;
		अवरोध;
	शेष:
		dev_err(dev, "invalid MPU port %#lx\n", mpu_port[n]);
		वापस 0;
	पूर्ण

	चयन (mpu_irq[n]) अणु
	हाल SNDRV_AUTO_IRQ:
		dev_warn(dev, "mpu_irq not specified: using polling mode\n");
		mpu_irq[n] = -1;
		अवरोध;
	हाल 2:
		mpu_irq[n] = 9;
		fallthrough;
	हाल 9:
		config[n] |= GALAXY_CONFIG_MPUIRQ_2;
		अवरोध;
#अगर_घोषित AZT1605
	हाल 3:
		config[n] |= GALAXY_CONFIG_MPUIRQ_3;
		अवरोध;
#पूर्ण_अगर
	हाल 5:
		config[n] |= GALAXY_CONFIG_MPUIRQ_5;
		अवरोध;
	हाल 7:
		config[n] |= GALAXY_CONFIG_MPUIRQ_7;
		अवरोध;
#अगर_घोषित AZT2316
	हाल 10:
		config[n] |= GALAXY_CONFIG_MPUIRQ_10;
		अवरोध;
#पूर्ण_अगर
	शेष:
		dev_err(dev, "invalid MPU IRQ %d\n", mpu_irq[n]);
		वापस 0;
	पूर्ण

	अगर (mpu_irq[n] == irq[n]) अणु
		dev_err(dev, "cannot share IRQ between WSS and MPU-401\n");
		वापस 0;
	पूर्ण

fm:
	चयन (fm_port[n]) अणु
	हाल SNDRV_AUTO_PORT:
		dev_warn(dev, "fm_port not specified: not using OPL3\n");
		fm_port[n] = -1;
		अवरोध;
	हाल 0x388:
		अवरोध;
	शेष:
		dev_err(dev, "illegal FM port %#lx\n", fm_port[n]);
		वापस 0;
	पूर्ण

	config[n] |= GALAXY_CONFIG_GAME_ENABLE;
	वापस 1;
पूर्ण

अटल पूर्णांक galaxy_init(काष्ठा snd_galaxy *galaxy, u8 *type)
अणु
	u8 major;
	u8 minor;
	पूर्णांक err;

	err = dsp_reset(galaxy->port);
	अगर (err < 0)
		वापस err;

	err = dsp_get_version(galaxy->port, &major, &minor);
	अगर (err < 0)
		वापस err;

	अगर (major != GALAXY_DSP_MAJOR || minor != GALAXY_DSP_MINOR)
		वापस -ENODEV;

	err = dsp_command(galaxy->port, DSP_COMMAND_GALAXY_8);
	अगर (err < 0)
		वापस err;

	err = dsp_command(galaxy->port, GALAXY_COMMAND_GET_TYPE);
	अगर (err < 0)
		वापस err;

	err = dsp_get_byte(galaxy->port, type);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक galaxy_set_mode(काष्ठा snd_galaxy *galaxy, u8 mode)
अणु
	पूर्णांक err;

	err = dsp_command(galaxy->port, DSP_COMMAND_GALAXY_9);
	अगर (err < 0)
		वापस err;

	err = dsp_command(galaxy->port, mode);
	अगर (err < 0)
		वापस err;

#अगर_घोषित AZT1605
	/*
	 * Needed क्रम MPU IRQ on AZT1605, but AZT2316 loses WSS again
	 */
	err = dsp_reset(galaxy->port);
	अगर (err < 0)
		वापस err;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम galaxy_set_config(काष्ठा snd_galaxy *galaxy, u32 config)
अणु
	u8 पंचांगp = ioपढ़ो8(galaxy->config_port + CONFIG_PORT_SET);
	पूर्णांक i;

	ioग_लिखो8(पंचांगp | 0x80, galaxy->config_port + CONFIG_PORT_SET);
	क्रम (i = 0; i < GALAXY_CONFIG_SIZE; i++) अणु
		ioग_लिखो8(config, galaxy->config_port + i);
		config >>= 8;
	पूर्ण
	ioग_लिखो8(पंचांगp & 0x7f, galaxy->config_port + CONFIG_PORT_SET);
	msleep(10);
पूर्ण

अटल व्योम galaxy_config(काष्ठा snd_galaxy *galaxy, u32 config)
अणु
	पूर्णांक i;

	क्रम (i = GALAXY_CONFIG_SIZE; i; i--) अणु
		u8 पंचांगp = ioपढ़ो8(galaxy->config_port + i - 1);
		galaxy->config = (galaxy->config << 8) | पंचांगp;
	पूर्ण
	config |= galaxy->config & GALAXY_CONFIG_MASK;
	galaxy_set_config(galaxy, config);
पूर्ण

अटल पूर्णांक galaxy_wss_config(काष्ठा snd_galaxy *galaxy, u8 wss_config)
अणु
	पूर्णांक err;

	err = wss_detect(galaxy->wss_port);
	अगर (err < 0)
		वापस err;

	wss_set_config(galaxy->wss_port, wss_config);

	err = galaxy_set_mode(galaxy, GALAXY_MODE_WSS);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम snd_galaxy_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_galaxy *galaxy = card->निजी_data;

	अगर (galaxy->wss_port) अणु
		wss_set_config(galaxy->wss_port, 0);
		ioport_unmap(galaxy->wss_port);
		release_and_मुक्त_resource(galaxy->res_wss_port);
	पूर्ण
	अगर (galaxy->config_port) अणु
		galaxy_set_config(galaxy, galaxy->config);
		ioport_unmap(galaxy->config_port);
		release_and_मुक्त_resource(galaxy->res_config_port);
	पूर्ण
	अगर (galaxy->port) अणु
		ioport_unmap(galaxy->port);
		release_and_मुक्त_resource(galaxy->res_port);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_galaxy_probe(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_galaxy *galaxy;
	काष्ठा snd_wss *chip;
	काष्ठा snd_card *card;
	u8 type;
	पूर्णांक err;

	err = snd_card_new(dev, index[n], id[n], THIS_MODULE,
			   माप(*galaxy), &card);
	अगर (err < 0)
		वापस err;

	card->निजी_मुक्त = snd_galaxy_मुक्त;
	galaxy = card->निजी_data;

	galaxy->res_port = request_region(port[n], 16, DRV_NAME);
	अगर (!galaxy->res_port) अणु
		dev_err(dev, "could not grab ports %#lx-%#lx\n", port[n],
			port[n] + 15);
		err = -EBUSY;
		जाओ error;
	पूर्ण
	galaxy->port = ioport_map(port[n], 16);

	err = galaxy_init(galaxy, &type);
	अगर (err < 0) अणु
		dev_err(dev, "did not find a Sound Galaxy at %#lx\n", port[n]);
		जाओ error;
	पूर्ण
	dev_info(dev, "Sound Galaxy (type %d) found at %#lx\n", type, port[n]);

	galaxy->res_config_port = request_region(port[n] + GALAXY_PORT_CONFIG,
						 16, DRV_NAME);
	अगर (!galaxy->res_config_port) अणु
		dev_err(dev, "could not grab ports %#lx-%#lx\n",
			port[n] + GALAXY_PORT_CONFIG,
			port[n] + GALAXY_PORT_CONFIG + 15);
		err = -EBUSY;
		जाओ error;
	पूर्ण
	galaxy->config_port = ioport_map(port[n] + GALAXY_PORT_CONFIG, 16);

	galaxy_config(galaxy, config[n]);

	galaxy->res_wss_port = request_region(wss_port[n], 4, DRV_NAME);
	अगर (!galaxy->res_wss_port)  अणु
		dev_err(dev, "could not grab ports %#lx-%#lx\n", wss_port[n],
			wss_port[n] + 3);
		err = -EBUSY;
		जाओ error;
	पूर्ण
	galaxy->wss_port = ioport_map(wss_port[n], 4);

	err = galaxy_wss_config(galaxy, wss_config[n]);
	अगर (err < 0) अणु
		dev_err(dev, "could not configure WSS\n");
		जाओ error;
	पूर्ण

	म_नकल(card->driver, DRV_NAME);
	म_नकल(card->लघुname, DRV_NAME);
	प्र_लिखो(card->दीर्घname, "%s at %#lx/%#lx, irq %d, dma %d/%d",
		card->लघुname, port[n], wss_port[n], irq[n], dma1[n],
		dma2[n]);

	err = snd_wss_create(card, wss_port[n] + 4, -1, irq[n], dma1[n],
			     dma2[n], WSS_HW_DETECT, 0, &chip);
	अगर (err < 0)
		जाओ error;

	err = snd_wss_pcm(chip, 0);
	अगर (err < 0)
		जाओ error;

	err = snd_wss_mixer(chip);
	अगर (err < 0)
		जाओ error;

	err = snd_wss_समयr(chip, 0);
	अगर (err < 0)
		जाओ error;

	अगर (mpu_port[n] >= 0) अणु
		err = snd_mpu401_uart_new(card, 0, MPU401_HW_MPU401,
					  mpu_port[n], 0, mpu_irq[n], शून्य);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	अगर (fm_port[n] >= 0) अणु
		काष्ठा snd_opl3 *opl3;

		err = snd_opl3_create(card, fm_port[n], fm_port[n] + 2,
				      OPL3_HW_AUTO, 0, &opl3);
		अगर (err < 0) अणु
			dev_err(dev, "no OPL device at %#lx\n", fm_port[n]);
			जाओ error;
		पूर्ण
		err = snd_opl3_समयr_new(opl3, 1, 2);
		अगर (err < 0)
			जाओ error;

		err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ error;

	dev_set_drvdata(dev, card);
	वापस 0;

error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_galaxy_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	snd_card_मुक्त(dev_get_drvdata(dev));
पूर्ण

अटल काष्ठा isa_driver snd_galaxy_driver = अणु
	.match		= snd_galaxy_match,
	.probe		= snd_galaxy_probe,
	.हटाओ		= snd_galaxy_हटाओ,

	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण
पूर्ण;

module_isa_driver(snd_galaxy_driver, SNDRV_CARDS);
