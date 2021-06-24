<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    card-opti92x-ad1848.c - driver क्रम OPTi 82c92x based soundcards.
    Copyright (C) 1998-2000 by Massimo Piccioni <dafastidio@libero.it>

    Part of this code was developed at the Italian Ministry of Air Defence,
    Sixth Division (oh, che pace ...), Rome.

    Thanks to Maria Grazia Pollarini, Salvatore Vassallo.

*/


#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/delay.h>
#समावेश <linux/pnp.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <sound/core.h>
#समावेश <sound/tlv.h>
#समावेश <sound/wss.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#अगर_अघोषित OPTi93X
#समावेश <sound/opl4.h>
#पूर्ण_अगर
#घोषणा SNDRV_LEGACY_FIND_FREE_IOPORT
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

MODULE_AUTHOR("Massimo Piccioni <dafastidio@libero.it>");
MODULE_LICENSE("GPL");
#अगर_घोषित OPTi93X
MODULE_DESCRIPTION("OPTi93X");
#अन्यथा	/* OPTi93X */
#अगर_घोषित CS4231
MODULE_DESCRIPTION("OPTi92X - CS4231");
#अन्यथा	/* CS4231 */
MODULE_DESCRIPTION("OPTi92X - AD1848");
#पूर्ण_अगर	/* CS4231 */
#पूर्ण_अगर	/* OPTi93X */

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;	/* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;		/* ID क्रम this card */
//अटल bool enable = SNDRV_DEFAULT_ENABLE1;	/* Enable this card */
#अगर_घोषित CONFIG_PNP
अटल bool isapnp = true;			/* Enable ISA PnP detection */
#पूर्ण_अगर
अटल दीर्घ port = SNDRV_DEFAULT_PORT1; 	/* 0x530,0xe80,0xf40,0x604 */
अटल दीर्घ mpu_port = SNDRV_DEFAULT_PORT1;	/* 0x300,0x310,0x320,0x330 */
अटल दीर्घ fm_port = SNDRV_DEFAULT_PORT1;	/* 0x388 */
अटल पूर्णांक irq = SNDRV_DEFAULT_IRQ1;		/* 5,7,9,10,11 */
अटल पूर्णांक mpu_irq = SNDRV_DEFAULT_IRQ1;	/* 5,7,9,10 */
अटल पूर्णांक dma1 = SNDRV_DEFAULT_DMA1;		/* 0,1,3 */
#अगर defined(CS4231) || defined(OPTi93X)
अटल पूर्णांक dma2 = SNDRV_DEFAULT_DMA1;		/* 0,1,3 */
#पूर्ण_अगर	/* CS4231 || OPTi93X */

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for opti9xx based soundcard.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for opti9xx based soundcard.");
//module_param(enable, bool, 0444);
//MODULE_PARM_DESC(enable, "Enable opti9xx soundcard.");
#अगर_घोषित CONFIG_PNP
module_param(isapnp, bool, 0444);
MODULE_PARM_DESC(isapnp, "Enable ISA PnP detection for specified soundcard.");
#पूर्ण_अगर
module_param_hw(port, दीर्घ, ioport, 0444);
MODULE_PARM_DESC(port, "WSS port # for opti9xx driver.");
module_param_hw(mpu_port, दीर्घ, ioport, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for opti9xx driver.");
module_param_hw(fm_port, दीर्घ, ioport, 0444);
MODULE_PARM_DESC(fm_port, "FM port # for opti9xx driver.");
module_param_hw(irq, पूर्णांक, irq, 0444);
MODULE_PARM_DESC(irq, "WSS irq # for opti9xx driver.");
module_param_hw(mpu_irq, पूर्णांक, irq, 0444);
MODULE_PARM_DESC(mpu_irq, "MPU-401 irq # for opti9xx driver.");
module_param_hw(dma1, पूर्णांक, dma, 0444);
MODULE_PARM_DESC(dma1, "1st dma # for opti9xx driver.");
#अगर defined(CS4231) || defined(OPTi93X)
module_param_hw(dma2, पूर्णांक, dma, 0444);
MODULE_PARM_DESC(dma2, "2nd dma # for opti9xx driver.");
#पूर्ण_अगर	/* CS4231 || OPTi93X */

#घोषणा OPTi9XX_HW_82C928	1
#घोषणा OPTi9XX_HW_82C929	2
#घोषणा OPTi9XX_HW_82C924	3
#घोषणा OPTi9XX_HW_82C925	4
#घोषणा OPTi9XX_HW_82C930	5
#घोषणा OPTi9XX_HW_82C931	6
#घोषणा OPTi9XX_HW_82C933	7
#घोषणा OPTi9XX_HW_LAST		OPTi9XX_HW_82C933

#घोषणा OPTi9XX_MC_REG(n)	n

#अगर_घोषित OPTi93X

#घोषणा OPTi93X_STATUS			0x02
#घोषणा OPTi93X_PORT(chip, r)		((chip)->port + OPTi93X_##r)

#घोषणा OPTi93X_IRQ_PLAYBACK		0x04
#घोषणा OPTi93X_IRQ_CAPTURE		0x08

#पूर्ण_अगर /* OPTi93X */

काष्ठा snd_opti9xx अणु
	अचिन्हित लघु hardware;
	अचिन्हित अक्षर password;
	अक्षर name[7];

	अचिन्हित दीर्घ mc_base;
	काष्ठा resource *res_mc_base;
	अचिन्हित दीर्घ mc_base_size;
#अगर_घोषित OPTi93X
	अचिन्हित दीर्घ mc_indir_index;
	काष्ठा resource *res_mc_indir;
#पूर्ण_अगर	/* OPTi93X */
	काष्ठा snd_wss *codec;
	अचिन्हित दीर्घ pwd_reg;

	spinlock_t lock;

	दीर्घ wss_base;
	पूर्णांक irq;
पूर्ण;

अटल पूर्णांक snd_opti9xx_pnp_is_probed;

#अगर_घोषित CONFIG_PNP

अटल स्थिर काष्ठा pnp_card_device_id snd_opti9xx_pnpids[] = अणु
#अगर_अघोषित OPTi93X
	/* OPTi 82C924 */
	अणु .id = "OPT0924",
	  .devs = अणु अणु "OPT0000" पूर्ण, अणु "OPT0002" पूर्ण, अणु "OPT0005" पूर्ण पूर्ण,
	  .driver_data = 0x0924 पूर्ण,
	/* OPTi 82C925 */
	अणु .id = "OPT0925",
	  .devs = अणु अणु "OPT9250" पूर्ण, अणु "OPT0002" पूर्ण, अणु "OPT0005" पूर्ण पूर्ण,
	  .driver_data = 0x0925 पूर्ण,
#अन्यथा
	/* OPTi 82C931/3 */
	अणु .id = "OPT0931", .devs = अणु अणु "OPT9310" पूर्ण, अणु "OPT0002" पूर्ण पूर्ण,
	  .driver_data = 0x0931 पूर्ण,
#पूर्ण_अगर	/* OPTi93X */
	अणु .id = "" पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_opti9xx_pnpids);

#पूर्ण_अगर	/* CONFIG_PNP */

#घोषणा DEV_NAME KBUILD_MODNAME

अटल स्थिर अक्षर * स्थिर snd_opti9xx_names[] = अणु
	"unknown",
	"82C928",	"82C929",
	"82C924",	"82C925",
	"82C930",	"82C931",	"82C933"
पूर्ण;

अटल पूर्णांक snd_opti9xx_init(काष्ठा snd_opti9xx *chip,
			    अचिन्हित लघु hardware)
अणु
	अटल स्थिर पूर्णांक opti9xx_mc_size[] = अणु7, 7, 10, 10, 2, 2, 2पूर्ण;

	chip->hardware = hardware;
	म_नकल(chip->name, snd_opti9xx_names[hardware]);

	spin_lock_init(&chip->lock);

	chip->irq = -1;

#अगर_अघोषित OPTi93X
#अगर_घोषित CONFIG_PNP
	अगर (isapnp && chip->mc_base)
		/* PnP resource gives the least 10 bits */
		chip->mc_base |= 0xc00;
	अन्यथा
#पूर्ण_अगर	/* CONFIG_PNP */
	अणु
		chip->mc_base = 0xf8c;
		chip->mc_base_size = opti9xx_mc_size[hardware];
	पूर्ण
#अन्यथा
		chip->mc_base_size = opti9xx_mc_size[hardware];
#पूर्ण_अगर

	चयन (hardware) अणु
#अगर_अघोषित OPTi93X
	हाल OPTi9XX_HW_82C928:
	हाल OPTi9XX_HW_82C929:
		chip->password = (hardware == OPTi9XX_HW_82C928) ? 0xe2 : 0xe3;
		chip->pwd_reg = 3;
		अवरोध;

	हाल OPTi9XX_HW_82C924:
	हाल OPTi9XX_HW_82C925:
		chip->password = 0xe5;
		chip->pwd_reg = 3;
		अवरोध;
#अन्यथा	/* OPTi93X */

	हाल OPTi9XX_HW_82C930:
	हाल OPTi9XX_HW_82C931:
	हाल OPTi9XX_HW_82C933:
		chip->mc_base = (hardware == OPTi9XX_HW_82C930) ? 0xf8f : 0xf8d;
		अगर (!chip->mc_indir_index)
			chip->mc_indir_index = 0xe0e;
		chip->password = 0xe4;
		chip->pwd_reg = 0;
		अवरोध;
#पूर्ण_अगर	/* OPTi93X */

	शेष:
		snd_prपूर्णांकk(KERN_ERR "chip %d not supported\n", hardware);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर snd_opti9xx_पढ़ो(काष्ठा snd_opti9xx *chip,
				      अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर retval = 0xff;

	spin_lock_irqsave(&chip->lock, flags);
	outb(chip->password, chip->mc_base + chip->pwd_reg);

	चयन (chip->hardware) अणु
#अगर_अघोषित OPTi93X
	हाल OPTi9XX_HW_82C924:
	हाल OPTi9XX_HW_82C925:
		अगर (reg > 7) अणु
			outb(reg, chip->mc_base + 8);
			outb(chip->password, chip->mc_base + chip->pwd_reg);
			retval = inb(chip->mc_base + 9);
			अवरोध;
		पूर्ण
		fallthrough;

	हाल OPTi9XX_HW_82C928:
	हाल OPTi9XX_HW_82C929:
		retval = inb(chip->mc_base + reg);
		अवरोध;
#अन्यथा	/* OPTi93X */

	हाल OPTi9XX_HW_82C930:
	हाल OPTi9XX_HW_82C931:
	हाल OPTi9XX_HW_82C933:
		outb(reg, chip->mc_indir_index);
		outb(chip->password, chip->mc_base + chip->pwd_reg);
		retval = inb(chip->mc_indir_index + 1);
		अवरोध;
#पूर्ण_अगर	/* OPTi93X */

	शेष:
		snd_prपूर्णांकk(KERN_ERR "chip %d not supported\n", chip->hardware);
	पूर्ण

	spin_unlock_irqrestore(&chip->lock, flags);
	वापस retval;
पूर्ण

अटल व्योम snd_opti9xx_ग_लिखो(काष्ठा snd_opti9xx *chip, अचिन्हित अक्षर reg,
			      अचिन्हित अक्षर value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	outb(chip->password, chip->mc_base + chip->pwd_reg);

	चयन (chip->hardware) अणु
#अगर_अघोषित OPTi93X
	हाल OPTi9XX_HW_82C924:
	हाल OPTi9XX_HW_82C925:
		अगर (reg > 7) अणु
			outb(reg, chip->mc_base + 8);
			outb(chip->password, chip->mc_base + chip->pwd_reg);
			outb(value, chip->mc_base + 9);
			अवरोध;
		पूर्ण
		fallthrough;

	हाल OPTi9XX_HW_82C928:
	हाल OPTi9XX_HW_82C929:
		outb(value, chip->mc_base + reg);
		अवरोध;
#अन्यथा	/* OPTi93X */

	हाल OPTi9XX_HW_82C930:
	हाल OPTi9XX_HW_82C931:
	हाल OPTi9XX_HW_82C933:
		outb(reg, chip->mc_indir_index);
		outb(chip->password, chip->mc_base + chip->pwd_reg);
		outb(value, chip->mc_indir_index + 1);
		अवरोध;
#पूर्ण_अगर	/* OPTi93X */

	शेष:
		snd_prपूर्णांकk(KERN_ERR "chip %d not supported\n", chip->hardware);
	पूर्ण

	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण


अटल अंतरभूत व्योम snd_opti9xx_ग_लिखो_mask(काष्ठा snd_opti9xx *chip,
		अचिन्हित अक्षर reg, अचिन्हित अक्षर value, अचिन्हित अक्षर mask)
अणु
	अचिन्हित अक्षर oldval = snd_opti9xx_पढ़ो(chip, reg);

	snd_opti9xx_ग_लिखो(chip, reg, (oldval & ~mask) | (value & mask));
पूर्ण

अटल पूर्णांक snd_opti9xx_configure(काष्ठा snd_opti9xx *chip,
					   दीर्घ port,
					   पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2,
					   दीर्घ mpu_port, पूर्णांक mpu_irq)
अणु
	अचिन्हित अक्षर wss_base_bits;
	अचिन्हित अक्षर irq_bits;
	अचिन्हित अक्षर dma_bits;
	अचिन्हित अक्षर mpu_port_bits = 0;
	अचिन्हित अक्षर mpu_irq_bits;

	चयन (chip->hardware) अणु
#अगर_अघोषित OPTi93X
	हाल OPTi9XX_HW_82C924:
		/* opti 929 mode (?), OPL3 घड़ी output, audio enable */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(4), 0xf0, 0xfc);
		/* enable wave audio */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(6), 0x02, 0x02);
		fallthrough;

	हाल OPTi9XX_HW_82C925:
		/* enable WSS mode */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(1), 0x80, 0x80);
		/* OPL3 FM synthesis */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(2), 0x00, 0x20);
		/* disable Sound Blaster IRQ and DMA */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(3), 0xf0, 0xff);
#अगर_घोषित CS4231
		/* cs4231/4248 fix enabled */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(5), 0x02, 0x02);
#अन्यथा
		/* cs4231/4248 fix disabled */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(5), 0x00, 0x02);
#पूर्ण_अगर	/* CS4231 */
		अवरोध;

	हाल OPTi9XX_HW_82C928:
	हाल OPTi9XX_HW_82C929:
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(1), 0x80, 0x80);
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(2), 0x00, 0x20);
		/*
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(3), 0xa2, 0xae);
		*/
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(4), 0x00, 0x0c);
#अगर_घोषित CS4231
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(5), 0x02, 0x02);
#अन्यथा
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(5), 0x00, 0x02);
#पूर्ण_अगर	/* CS4231 */
		अवरोध;

#अन्यथा	/* OPTi93X */
	हाल OPTi9XX_HW_82C931:
		/* disable 3D sound (set GPIO1 as output, low) */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(20), 0x04, 0x0c);
		fallthrough;

	हाल OPTi9XX_HW_82C933:
		/*
		 * The BTC 1817DW has QS1000 wavetable which is connected
		 * to the serial digital input of the OPTI931.
		 */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(21), 0x82, 0xff);
		/* 
		 * This bit sets OPTI931 to स्वतःmaticaly select FM
		 * or digital input संकेत.
		 */
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(26), 0x01, 0x01);
		fallthrough;

	हाल OPTi9XX_HW_82C930:
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(6), 0x02, 0x03);
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(3), 0x00, 0xff);
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(4), 0x10 |
			(chip->hardware == OPTi9XX_HW_82C930 ? 0x00 : 0x04),
			0x34);
		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(5), 0x20, 0xbf);
		अवरोध;
#पूर्ण_अगर	/* OPTi93X */

	शेष:
		snd_prपूर्णांकk(KERN_ERR "chip %d not supported\n", chip->hardware);
		वापस -EINVAL;
	पूर्ण

	/* PnP resource says it decodes only 10 bits of address */
	चयन (port & 0x3ff) अणु
	हाल 0x130:
		chip->wss_base = 0x530;
		wss_base_bits = 0x00;
		अवरोध;
	हाल 0x204:
		chip->wss_base = 0x604;
		wss_base_bits = 0x03;
		अवरोध;
	हाल 0x280:
		chip->wss_base = 0xe80;
		wss_base_bits = 0x01;
		अवरोध;
	हाल 0x340:
		chip->wss_base = 0xf40;
		wss_base_bits = 0x02;
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_WARNING "WSS port 0x%lx not valid\n", port);
		जाओ __skip_base;
	पूर्ण
	snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(1), wss_base_bits << 4, 0x30);

__skip_base:
	चयन (irq) अणु
//#अगर_घोषित OPTi93X
	हाल 5:
		irq_bits = 0x05;
		अवरोध;
//#पूर्ण_अगर	/* OPTi93X */
	हाल 7:
		irq_bits = 0x01;
		अवरोध;
	हाल 9:
		irq_bits = 0x02;
		अवरोध;
	हाल 10:
		irq_bits = 0x03;
		अवरोध;
	हाल 11:
		irq_bits = 0x04;
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_WARNING "WSS irq # %d not valid\n", irq);
		जाओ __skip_resources;
	पूर्ण

	चयन (dma1) अणु
	हाल 0:
		dma_bits = 0x01;
		अवरोध;
	हाल 1:
		dma_bits = 0x02;
		अवरोध;
	हाल 3:
		dma_bits = 0x03;
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_WARNING "WSS dma1 # %d not valid\n", dma1);
		जाओ __skip_resources;
	पूर्ण

#अगर defined(CS4231) || defined(OPTi93X)
	अगर (dma1 == dma2) अणु
		snd_prपूर्णांकk(KERN_ERR "don't want to share dmas\n");
		वापस -EBUSY;
	पूर्ण

	चयन (dma2) अणु
	हाल 0:
	हाल 1:
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_WARNING "WSS dma2 # %d not valid\n", dma2);
		जाओ __skip_resources;
	पूर्ण
	dma_bits |= 0x04;
#पूर्ण_अगर	/* CS4231 || OPTi93X */

#अगर_अघोषित OPTi93X
	 outb(irq_bits << 3 | dma_bits, chip->wss_base);
#अन्यथा /* OPTi93X */
	snd_opti9xx_ग_लिखो(chip, OPTi9XX_MC_REG(3), (irq_bits << 3 | dma_bits));
#पूर्ण_अगर /* OPTi93X */

__skip_resources:
	अगर (chip->hardware > OPTi9XX_HW_82C928) अणु
		चयन (mpu_port) अणु
		हाल 0:
		हाल -1:
			अवरोध;
		हाल 0x300:
			mpu_port_bits = 0x03;
			अवरोध;
		हाल 0x310:
			mpu_port_bits = 0x02;
			अवरोध;
		हाल 0x320:
			mpu_port_bits = 0x01;
			अवरोध;
		हाल 0x330:
			mpu_port_bits = 0x00;
			अवरोध;
		शेष:
			snd_prपूर्णांकk(KERN_WARNING
				   "MPU-401 port 0x%lx not valid\n", mpu_port);
			जाओ __skip_mpu;
		पूर्ण

		चयन (mpu_irq) अणु
		हाल 5:
			mpu_irq_bits = 0x02;
			अवरोध;
		हाल 7:
			mpu_irq_bits = 0x03;
			अवरोध;
		हाल 9:
			mpu_irq_bits = 0x00;
			अवरोध;
		हाल 10:
			mpu_irq_bits = 0x01;
			अवरोध;
		शेष:
			snd_prपूर्णांकk(KERN_WARNING "MPU-401 irq # %d not valid\n",
				mpu_irq);
			जाओ __skip_mpu;
		पूर्ण

		snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(6),
			(mpu_port <= 0) ? 0x00 :
				0x80 | mpu_port_bits << 5 | mpu_irq_bits << 3,
			0xf8);
	पूर्ण
__skip_mpu:

	वापस 0;
पूर्ण

#अगर_घोषित OPTi93X

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit_3db_step, -9300, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_4bit_12db_max, -3300, 300, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_opti93x_controls[] = अणु
WSS_DOUBLE("Master Playback Switch", 0,
		OPTi93X_OUT_LEFT, OPTi93X_OUT_RIGHT, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Master Playback Volume", 0,
		OPTi93X_OUT_LEFT, OPTi93X_OUT_RIGHT, 1, 1, 31, 1,
		db_scale_5bit_3db_step),
WSS_DOUBLE_TLV("PCM Playback Volume", 0,
		CS4231_LEFT_OUTPUT, CS4231_RIGHT_OUTPUT, 0, 0, 31, 1,
		db_scale_5bit),
WSS_DOUBLE_TLV("FM Playback Volume", 0,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 1, 1, 15, 1,
		db_scale_4bit_12db_max),
WSS_DOUBLE("Line Playback Switch", 0,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Line Playback Volume", 0,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 0, 0, 15, 1,
		db_scale_4bit_12db_max),
WSS_DOUBLE("Mic Playback Switch", 0,
		OPTi93X_MIC_LEFT_INPUT, OPTi93X_MIC_RIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Mic Playback Volume", 0,
		OPTi93X_MIC_LEFT_INPUT, OPTi93X_MIC_RIGHT_INPUT, 1, 1, 15, 1,
		db_scale_4bit_12db_max),
WSS_DOUBLE_TLV("CD Playback Volume", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 1, 1, 15, 1,
		db_scale_4bit_12db_max),
WSS_DOUBLE("Aux Playback Switch", 0,
		OPTi931_AUX_LEFT_INPUT, OPTi931_AUX_RIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Aux Playback Volume", 0,
		OPTi931_AUX_LEFT_INPUT, OPTi931_AUX_RIGHT_INPUT, 1, 1, 15, 1,
		db_scale_4bit_12db_max),
पूर्ण;

अटल पूर्णांक snd_opti93x_mixer(काष्ठा snd_wss *chip)
अणु
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक idx;
	काष्ठा snd_ctl_elem_id id1, id2;
	पूर्णांक err;

	अगर (snd_BUG_ON(!chip || !chip->pcm))
		वापस -EINVAL;

	card = chip->card;

	म_नकल(card->mixername, chip->pcm->name);

	स_रखो(&id1, 0, माप(id1));
	स_रखो(&id2, 0, माप(id2));
	id1.अगरace = id2.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	/* reassign AUX0 चयन to CD */
	म_नकल(id1.name, "Aux Playback Switch");
	म_नकल(id2.name, "CD Playback Switch");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Cannot rename opti93x control\n");
		वापस err;
	पूर्ण
	/* reassign AUX1 चयन to FM */
	म_नकल(id1.name, "Aux Playback Switch"); id1.index = 1;
	म_नकल(id2.name, "FM Playback Switch");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Cannot rename opti93x control\n");
		वापस err;
	पूर्ण
	/* हटाओ AUX1 volume */
	म_नकल(id1.name, "Aux Playback Volume"); id1.index = 1;
	snd_ctl_हटाओ_id(card, &id1);

	/* Replace WSS volume controls with OPTi93x volume controls */
	id1.index = 0;
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_opti93x_controls); idx++) अणु
		म_नकल(id1.name, snd_opti93x_controls[idx].name);
		snd_ctl_हटाओ_id(card, &id1);

		err = snd_ctl_add(card,
				snd_ctl_new1(&snd_opti93x_controls[idx], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t snd_opti93x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_opti9xx *chip = dev_id;
	काष्ठा snd_wss *codec = chip->codec;
	अचिन्हित अक्षर status;

	अगर (!codec)
		वापस IRQ_HANDLED;

	status = snd_opti9xx_पढ़ो(chip, OPTi9XX_MC_REG(11));
	अगर ((status & OPTi93X_IRQ_PLAYBACK) && codec->playback_substream)
		snd_pcm_period_elapsed(codec->playback_substream);
	अगर ((status & OPTi93X_IRQ_CAPTURE) && codec->capture_substream) अणु
		snd_wss_overrange(codec);
		snd_pcm_period_elapsed(codec->capture_substream);
	पूर्ण
	outb(0x00, OPTi93X_PORT(codec, STATUS));
	वापस IRQ_HANDLED;
पूर्ण

#पूर्ण_अगर /* OPTi93X */

अटल पूर्णांक snd_opti9xx_पढ़ो_check(काष्ठा snd_opti9xx *chip)
अणु
	अचिन्हित अक्षर value;
#अगर_घोषित OPTi93X
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर

	chip->res_mc_base = request_region(chip->mc_base, chip->mc_base_size,
					   "OPTi9xx MC");
	अगर (chip->res_mc_base == शून्य)
		वापस -EBUSY;
#अगर_अघोषित OPTi93X
	value = snd_opti9xx_पढ़ो(chip, OPTi9XX_MC_REG(1));
	अगर (value != 0xff && value != inb(chip->mc_base + OPTi9XX_MC_REG(1)))
		अगर (value == snd_opti9xx_पढ़ो(chip, OPTi9XX_MC_REG(1)))
			वापस 0;
#अन्यथा	/* OPTi93X */
	chip->res_mc_indir = request_region(chip->mc_indir_index, 2,
					    "OPTi93x MC");
	अगर (chip->res_mc_indir == शून्य)
		वापस -EBUSY;

	spin_lock_irqsave(&chip->lock, flags);
	outb(chip->password, chip->mc_base + chip->pwd_reg);
	outb(((chip->mc_indir_index & 0x1f0) >> 4), chip->mc_base);
	spin_unlock_irqrestore(&chip->lock, flags);

	value = snd_opti9xx_पढ़ो(chip, OPTi9XX_MC_REG(7));
	snd_opti9xx_ग_लिखो(chip, OPTi9XX_MC_REG(7), 0xff - value);
	अगर (snd_opti9xx_पढ़ो(chip, OPTi9XX_MC_REG(7)) == 0xff - value)
		वापस 0;

	release_and_मुक्त_resource(chip->res_mc_indir);
	chip->res_mc_indir = शून्य;
#पूर्ण_अगर	/* OPTi93X */
	release_and_मुक्त_resource(chip->res_mc_base);
	chip->res_mc_base = शून्य;

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक snd_card_opti9xx_detect(काष्ठा snd_card *card,
				   काष्ठा snd_opti9xx *chip)
अणु
	पूर्णांक i, err;

#अगर_अघोषित OPTi93X
	क्रम (i = OPTi9XX_HW_82C928; i < OPTi9XX_HW_82C930; i++) अणु
#अन्यथा
	क्रम (i = OPTi9XX_HW_82C931; i >= OPTi9XX_HW_82C930; i--) अणु
#पूर्ण_अगर
		err = snd_opti9xx_init(chip, i);
		अगर (err < 0)
			वापस err;

		err = snd_opti9xx_पढ़ो_check(chip);
		अगर (err == 0)
			वापस 1;
#अगर_घोषित OPTi93X
		chip->mc_indir_index = 0;
#पूर्ण_अगर
	पूर्ण
	वापस -ENODEV;
पूर्ण

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_card_opti9xx_pnp(काष्ठा snd_opti9xx *chip,
				काष्ठा pnp_card_link *card,
				स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;
	काष्ठा pnp_dev *devmpu;
#अगर_अघोषित OPTi93X
	काष्ठा pnp_dev *devmc;
#पूर्ण_अगर

	pdev = pnp_request_card_device(card, pid->devs[0].id, शून्य);
	अगर (pdev == शून्य)
		वापस -EBUSY;

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "AUDIO pnp configure failure: %d\n", err);
		वापस err;
	पूर्ण

#अगर_घोषित OPTi93X
	port = pnp_port_start(pdev, 0) - 4;
	fm_port = pnp_port_start(pdev, 1) + 8;
	/* adjust mc_indir_index - some cards report it at 0xe?d,
	   other at 0xe?c but it really is always at 0xe?e */
	chip->mc_indir_index = (pnp_port_start(pdev, 3) & ~0xf) | 0xe;
#अन्यथा
	devmc = pnp_request_card_device(card, pid->devs[2].id, शून्य);
	अगर (devmc == शून्य)
		वापस -EBUSY;

	err = pnp_activate_dev(devmc);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "MC pnp configure failure: %d\n", err);
		वापस err;
	पूर्ण

	port = pnp_port_start(pdev, 1);
	fm_port = pnp_port_start(pdev, 2) + 8;
	/*
	 * The MC(0) is never accessed and card करोes not
	 * include it in the PnP resource range. OPTI93x include it.
	 */
	chip->mc_base = pnp_port_start(devmc, 0) - 1;
	chip->mc_base_size = pnp_port_len(devmc, 0) + 1;
#पूर्ण_अगर	/* OPTi93X */
	irq = pnp_irq(pdev, 0);
	dma1 = pnp_dma(pdev, 0);
#अगर defined(CS4231) || defined(OPTi93X)
	dma2 = pnp_dma(pdev, 1);
#पूर्ण_अगर	/* CS4231 || OPTi93X */

	devmpu = pnp_request_card_device(card, pid->devs[1].id, शून्य);

	अगर (devmpu && mpu_port > 0) अणु
		err = pnp_activate_dev(devmpu);
		अगर (err < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "MPU401 pnp configure failure\n");
			mpu_port = -1;
		पूर्ण अन्यथा अणु
			mpu_port = pnp_port_start(devmpu, 0);
			mpu_irq = pnp_irq(devmpu, 0);
		पूर्ण
	पूर्ण
	वापस pid->driver_data;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PNP */

अटल व्योम snd_card_opti9xx_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_opti9xx *chip = card->निजी_data;

	अगर (chip) अणु
#अगर_घोषित OPTi93X
		अगर (chip->irq > 0) अणु
			disable_irq(chip->irq);
			मुक्त_irq(chip->irq, chip);
		पूर्ण
		release_and_मुक्त_resource(chip->res_mc_indir);
#पूर्ण_अगर
		release_and_मुक्त_resource(chip->res_mc_base);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_opti9xx_probe(काष्ठा snd_card *card)
अणु
	अटल स्थिर दीर्घ possible_ports[] = अणु0x530, 0xe80, 0xf40, 0x604, -1पूर्ण;
	पूर्णांक error;
	पूर्णांक xdma2;
	काष्ठा snd_opti9xx *chip = card->निजी_data;
	काष्ठा snd_wss *codec;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_hwdep *synth;

#अगर defined(CS4231) || defined(OPTi93X)
	xdma2 = dma2;
#अन्यथा
	xdma2 = -1;
#पूर्ण_अगर

	अगर (port == SNDRV_AUTO_PORT) अणु
		port = snd_legacy_find_मुक्त_ioport(possible_ports, 4);
		अगर (port < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free WSS port\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	error = snd_opti9xx_configure(chip, port, irq, dma1, xdma2,
				      mpu_port, mpu_irq);
	अगर (error)
		वापस error;

	error = snd_wss_create(card, chip->wss_base + 4, -1, irq, dma1, xdma2,
#अगर_घोषित OPTi93X
			       WSS_HW_OPTI93X, WSS_HWSHARE_IRQ,
#अन्यथा
			       WSS_HW_DETECT, 0,
#पूर्ण_अगर
			       &codec);
	अगर (error < 0)
		वापस error;
	chip->codec = codec;
	error = snd_wss_pcm(codec, 0);
	अगर (error < 0)
		वापस error;
	error = snd_wss_mixer(codec);
	अगर (error < 0)
		वापस error;
#अगर_घोषित OPTi93X
	error = snd_opti93x_mixer(codec);
	अगर (error < 0)
		वापस error;
#पूर्ण_अगर
#अगर_घोषित CS4231
	error = snd_wss_समयr(codec, 0);
	अगर (error < 0)
		वापस error;
#पूर्ण_अगर
#अगर_घोषित OPTi93X
	error = request_irq(irq, snd_opti93x_पूर्णांकerrupt,
			    0, DEV_NAME" - WSS", chip);
	अगर (error < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "opti9xx: can't grab IRQ %d\n", irq);
		वापस error;
	पूर्ण
#पूर्ण_अगर
	chip->irq = irq;
	card->sync_irq = chip->irq;
	म_नकल(card->driver, chip->name);
	प्र_लिखो(card->लघुname, "OPTi %s", card->driver);
#अगर defined(CS4231) || defined(OPTi93X)
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s, %s at 0x%lx, irq %d, dma %d&%d",
		 card->लघुname, codec->pcm->name,
		 chip->wss_base + 4, irq, dma1, xdma2);
#अन्यथा
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s, %s at 0x%lx, irq %d, dma %d",
		 card->लघुname, codec->pcm->name, chip->wss_base + 4, irq,
		 dma1);
#पूर्ण_अगर	/* CS4231 || OPTi93X */

	अगर (mpu_port <= 0 || mpu_port == SNDRV_AUTO_PORT)
		rmidi = शून्य;
	अन्यथा अणु
		error = snd_mpu401_uart_new(card, 0, MPU401_HW_MPU401,
				mpu_port, 0, mpu_irq, &rmidi);
		अगर (error)
			snd_prपूर्णांकk(KERN_WARNING "no MPU-401 device at 0x%lx?\n",
				   mpu_port);
	पूर्ण

	अगर (fm_port > 0 && fm_port != SNDRV_AUTO_PORT) अणु
		काष्ठा snd_opl3 *opl3 = शून्य;
#अगर_अघोषित OPTi93X
		अगर (chip->hardware == OPTi9XX_HW_82C928 ||
		    chip->hardware == OPTi9XX_HW_82C929 ||
		    chip->hardware == OPTi9XX_HW_82C924) अणु
			काष्ठा snd_opl4 *opl4;
			/* assume we have an OPL4 */
			snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(2),
					       0x20, 0x20);
			अगर (snd_opl4_create(card, fm_port, fm_port - 8,
					    2, &opl3, &opl4) < 0) अणु
				/* no luck, use OPL3 instead */
				snd_opti9xx_ग_लिखो_mask(chip, OPTi9XX_MC_REG(2),
						       0x00, 0x20);
			पूर्ण
		पूर्ण
#पूर्ण_अगर	/* !OPTi93X */
		अगर (!opl3 && snd_opl3_create(card, fm_port, fm_port + 2,
					     OPL3_HW_AUTO, 0, &opl3) < 0) अणु
			snd_prपूर्णांकk(KERN_WARNING "no OPL device at 0x%lx-0x%lx\n",
				   fm_port, fm_port + 4 - 1);
		पूर्ण
		अगर (opl3) अणु
			error = snd_opl3_hwdep_new(opl3, 0, 1, &synth);
			अगर (error < 0)
				वापस error;
		पूर्ण
	पूर्ण

	वापस snd_card_रेजिस्टर(card);
पूर्ण

अटल पूर्णांक snd_opti9xx_card_new(काष्ठा device *pdev, काष्ठा snd_card **cardp)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_card_new(pdev, index, id, THIS_MODULE,
			   माप(काष्ठा snd_opti9xx), &card);
	अगर (err < 0)
		वापस err;
	card->निजी_मुक्त = snd_card_opti9xx_मुक्त;
	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opti9xx_isa_match(काष्ठा device *devptr,
				 अचिन्हित पूर्णांक dev)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (snd_opti9xx_pnp_is_probed)
		वापस 0;
	अगर (isapnp)
		वापस 0;
#पूर्ण_अगर
	वापस 1;
पूर्ण

अटल पूर्णांक snd_opti9xx_isa_probe(काष्ठा device *devptr,
				 अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card;
	पूर्णांक error;
	अटल स्थिर दीर्घ possible_mpu_ports[] = अणु0x300, 0x310, 0x320, 0x330, -1पूर्ण;
#अगर_घोषित OPTi93X
	अटल स्थिर पूर्णांक possible_irqs[] = अणु5, 9, 10, 11, 7, -1पूर्ण;
#अन्यथा
	अटल स्थिर पूर्णांक possible_irqs[] = अणु9, 10, 11, 7, -1पूर्ण;
#पूर्ण_अगर	/* OPTi93X */
	अटल स्थिर पूर्णांक possible_mpu_irqs[] = अणु5, 9, 10, 7, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dma1s[] = अणु3, 1, 0, -1पूर्ण;
#अगर defined(CS4231) || defined(OPTi93X)
	अटल स्थिर पूर्णांक possible_dma2s[][2] = अणुअणु1,-1पूर्ण, अणु0,-1पूर्ण, अणु-1,-1पूर्ण, अणु0,-1पूर्णपूर्ण;
#पूर्ण_अगर	/* CS4231 || OPTi93X */

	अगर (mpu_port == SNDRV_AUTO_PORT) अणु
		अगर ((mpu_port = snd_legacy_find_मुक्त_ioport(possible_mpu_ports, 2)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free MPU401 port\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (irq == SNDRV_AUTO_IRQ) अणु
		अगर ((irq = snd_legacy_find_मुक्त_irq(possible_irqs)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (mpu_irq == SNDRV_AUTO_IRQ) अणु
		अगर ((mpu_irq = snd_legacy_find_मुक्त_irq(possible_mpu_irqs)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free MPU401 IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma1 == SNDRV_AUTO_DMA) अणु
		अगर ((dma1 = snd_legacy_find_मुक्त_dma(possible_dma1s)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free DMA1\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
#अगर defined(CS4231) || defined(OPTi93X)
	अगर (dma2 == SNDRV_AUTO_DMA) अणु
		अगर ((dma2 = snd_legacy_find_मुक्त_dma(possible_dma2s[dma1 % 4])) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "unable to find a free DMA2\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	error = snd_opti9xx_card_new(devptr, &card);
	अगर (error < 0)
		वापस error;

	अगर ((error = snd_card_opti9xx_detect(card, card->निजी_data)) < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	अगर ((error = snd_opti9xx_probe(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	dev_set_drvdata(devptr, card);
	वापस 0;
पूर्ण

अटल व्योम snd_opti9xx_isa_हटाओ(काष्ठा device *devptr,
				   अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(devptr));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_opti9xx_suspend(काष्ठा snd_card *card)
अणु
	काष्ठा snd_opti9xx *chip = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	chip->codec->suspend(chip->codec);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opti9xx_resume(काष्ठा snd_card *card)
अणु
	काष्ठा snd_opti9xx *chip = card->निजी_data;
	पूर्णांक error, xdma2;
#अगर defined(CS4231) || defined(OPTi93X)
	xdma2 = dma2;
#अन्यथा
	xdma2 = -1;
#पूर्ण_अगर

	error = snd_opti9xx_configure(chip, port, irq, dma1, xdma2,
				      mpu_port, mpu_irq);
	अगर (error)
		वापस error;
	chip->codec->resume(chip->codec);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opti9xx_isa_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n,
				   pm_message_t state)
अणु
	वापस snd_opti9xx_suspend(dev_get_drvdata(dev));
पूर्ण

अटल पूर्णांक snd_opti9xx_isa_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	वापस snd_opti9xx_resume(dev_get_drvdata(dev));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा isa_driver snd_opti9xx_driver = अणु
	.match		= snd_opti9xx_isa_match,
	.probe		= snd_opti9xx_isa_probe,
	.हटाओ		= snd_opti9xx_isa_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_opti9xx_isa_suspend,
	.resume		= snd_opti9xx_isa_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_opti9xx_pnp_probe(काष्ठा pnp_card_link *pcard,
				 स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	काष्ठा snd_card *card;
	पूर्णांक error, hw;
	काष्ठा snd_opti9xx *chip;

	अगर (snd_opti9xx_pnp_is_probed)
		वापस -EBUSY;
	अगर (! isapnp)
		वापस -ENODEV;
	error = snd_opti9xx_card_new(&pcard->card->dev, &card);
	अगर (error < 0)
		वापस error;
	chip = card->निजी_data;

	hw = snd_card_opti9xx_pnp(chip, pcard, pid);
	चयन (hw) अणु
	हाल 0x0924:
		hw = OPTi9XX_HW_82C924;
		अवरोध;
	हाल 0x0925:
		hw = OPTi9XX_HW_82C925;
		अवरोध;
	हाल 0x0931:
		hw = OPTi9XX_HW_82C931;
		अवरोध;
	शेष:
		snd_card_मुक्त(card);
		वापस -ENODEV;
	पूर्ण

	अगर ((error = snd_opti9xx_init(chip, hw))) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	error = snd_opti9xx_पढ़ो_check(chip);
	अगर (error) अणु
		snd_prपूर्णांकk(KERN_ERR "OPTI chip not found\n");
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	अगर ((error = snd_opti9xx_probe(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	pnp_set_card_drvdata(pcard, card);
	snd_opti9xx_pnp_is_probed = 1;
	वापस 0;
पूर्ण

अटल व्योम snd_opti9xx_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
	snd_opti9xx_pnp_is_probed = 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_opti9xx_pnp_suspend(काष्ठा pnp_card_link *pcard,
				   pm_message_t state)
अणु
	वापस snd_opti9xx_suspend(pnp_get_card_drvdata(pcard));
पूर्ण

अटल पूर्णांक snd_opti9xx_pnp_resume(काष्ठा pnp_card_link *pcard)
अणु
	वापस snd_opti9xx_resume(pnp_get_card_drvdata(pcard));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_card_driver opti9xx_pnpc_driver = अणु
	.flags		= PNP_DRIVER_RES_DISABLE,
	.name		= DEV_NAME,
	.id_table	= snd_opti9xx_pnpids,
	.probe		= snd_opti9xx_pnp_probe,
	.हटाओ		= snd_opti9xx_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_opti9xx_pnp_suspend,
	.resume		= snd_opti9xx_pnp_resume,
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित OPTi93X
#घोषणा CHIP_NAME	"82C93x"
#अन्यथा
#घोषणा CHIP_NAME	"82C92x"
#पूर्ण_अगर

अटल पूर्णांक __init alsa_card_opti9xx_init(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	pnp_रेजिस्टर_card_driver(&opti9xx_pnpc_driver);
	अगर (snd_opti9xx_pnp_is_probed)
		वापस 0;
	pnp_unरेजिस्टर_card_driver(&opti9xx_pnpc_driver);
#पूर्ण_अगर
	वापस isa_रेजिस्टर_driver(&snd_opti9xx_driver, 1);
पूर्ण

अटल व्योम __निकास alsa_card_opti9xx_निकास(व्योम)
अणु
	अगर (!snd_opti9xx_pnp_is_probed) अणु
		isa_unरेजिस्टर_driver(&snd_opti9xx_driver);
		वापस;
	पूर्ण
#अगर_घोषित CONFIG_PNP
	pnp_unरेजिस्टर_card_driver(&opti9xx_pnpc_driver);
#पूर्ण_अगर
पूर्ण

module_init(alsa_card_opti9xx_init)
module_निकास(alsa_card_opti9xx_निकास)
