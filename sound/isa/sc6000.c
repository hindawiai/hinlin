<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Gallant SC-6000 soundcard. This card is also known as
 *  Audio Excel DSP 16 or Zoltrix AV302.
 *  These cards use CompuMedia ASC-9308 chip + AD1848 codec.
 *  SC-6600 and SC-7000 cards are also supported. They are based on
 *  CompuMedia ASC-9408 chip and CS4231 codec.
 *
 *  Copyright (C) 2007 Krzysztof Helt <krzysztof.h1@wp.pl>
 *
 *  I करोn't have करोcumentation क्रम this card. I used the driver
 *  क्रम OSS/Free included in the kernel source as reference.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/isa.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/opl3.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/control.h>
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

MODULE_AUTHOR("Krzysztof Helt");
MODULE_DESCRIPTION("Gallant SC-6000");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x220, 0x240 */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5, 7, 9, 10, 11 */
अटल दीर्घ mss_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x530, 0xe80 */
अटल दीर्घ mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
						/* 0x300, 0x310, 0x320, 0x330 */
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5, 7, 9, 10, 0 */
अटल पूर्णांक dma[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0, 1, 3 */
अटल bool joystick[SNDRV_CARDS] = अणु [0 ... (SNDRV_CARDS-1)] = false पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for sc-6000 based soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for sc-6000 based soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable sc-6000 based soundcard.");
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for sc-6000 driver.");
module_param_hw_array(mss_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mss_port, "MSS Port # for sc-6000 driver.");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for sc-6000 driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for sc-6000 driver.");
module_param_hw_array(mpu_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(mpu_irq, "MPU-401 IRQ # for sc-6000 driver.");
module_param_hw_array(dma, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma, "DMA # for sc-6000 driver.");
module_param_array(joystick, bool, शून्य, 0444);
MODULE_PARM_DESC(joystick, "Enable gameport.");

/*
 * Commands of SC6000's DSP (SBPRO+special).
 * Some of them are COMMAND_xx, in the future they may change.
 */
#घोषणा WRITE_MसूचीQ_CFG	0x50	/* Set M&I&DRQ mask (the real config)	*/
#घोषणा COMMAND_52	0x52	/*					*/
#घोषणा READ_HARD_CFG	0x58	/* Read Hardware Config (I/O base etc)	*/
#घोषणा COMMAND_5C	0x5c	/*					*/
#घोषणा COMMAND_60	0x60	/*					*/
#घोषणा COMMAND_66	0x66	/*					*/
#घोषणा COMMAND_6C	0x6c	/*					*/
#घोषणा COMMAND_6E	0x6e	/*					*/
#घोषणा COMMAND_88	0x88	/* Unknown command 			*/
#घोषणा DSP_INIT_MSS	0x8c	/* Enable Microsoft Sound System mode	*/
#घोषणा COMMAND_C5	0xc5	/*					*/
#घोषणा GET_DSP_VERSION	0xe1	/* Get DSP Version			*/
#घोषणा GET_DSP_COPYRIGHT 0xe3	/* Get DSP Copyright			*/

/*
 * Offsets of SC6000 DSP I/O ports. The offset is added to base I/O port
 * to have the actual I/O port.
 * Register permissions are:
 * (wo) == Write Only
 * (ro) == Read  Only
 * (w-) == Write
 * (r-) == Read
 */
#घोषणा DSP_RESET	0x06	/* offset of DSP RESET		(wo) */
#घोषणा DSP_READ	0x0a	/* offset of DSP READ		(ro) */
#घोषणा DSP_WRITE	0x0c	/* offset of DSP WRITE		(w-) */
#घोषणा DSP_COMMAND	0x0c	/* offset of DSP COMMAND	(w-) */
#घोषणा DSP_STATUS	0x0c	/* offset of DSP STATUS		(r-) */
#घोषणा DSP_DATAVAIL	0x0e	/* offset of DSP DATA AVAILABLE	(ro) */

#घोषणा PFX "sc6000: "
#घोषणा DRV_NAME "SC-6000"

/* hardware dependent functions */

/*
 * sc6000_irq_to_softcfg - Decode irq number पूर्णांकo cfg code.
 */
अटल अचिन्हित अक्षर sc6000_irq_to_softcfg(पूर्णांक irq)
अणु
	अचिन्हित अक्षर val = 0;

	चयन (irq) अणु
	हाल 5:
		val = 0x28;
		अवरोध;
	हाल 7:
		val = 0x8;
		अवरोध;
	हाल 9:
		val = 0x10;
		अवरोध;
	हाल 10:
		val = 0x18;
		अवरोध;
	हाल 11:
		val = 0x20;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण

/*
 * sc6000_dma_to_softcfg - Decode dma number पूर्णांकo cfg code.
 */
अटल अचिन्हित अक्षर sc6000_dma_to_softcfg(पूर्णांक dma)
अणु
	अचिन्हित अक्षर val = 0;

	चयन (dma) अणु
	हाल 0:
		val = 1;
		अवरोध;
	हाल 1:
		val = 2;
		अवरोध;
	हाल 3:
		val = 3;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण

/*
 * sc6000_mpu_irq_to_softcfg - Decode MPU-401 irq number पूर्णांकo cfg code.
 */
अटल अचिन्हित अक्षर sc6000_mpu_irq_to_softcfg(पूर्णांक mpu_irq)
अणु
	अचिन्हित अक्षर val = 0;

	चयन (mpu_irq) अणु
	हाल 5:
		val = 4;
		अवरोध;
	हाल 7:
		val = 0x44;
		अवरोध;
	हाल 9:
		val = 0x84;
		अवरोध;
	हाल 10:
		val = 0xc4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण

अटल पूर्णांक sc6000_रुको_data(अक्षर __iomem *vport)
अणु
	पूर्णांक loop = 1000;
	अचिन्हित अक्षर val = 0;

	करो अणु
		val = ioपढ़ो8(vport + DSP_DATAVAIL);
		अगर (val & 0x80)
			वापस 0;
		cpu_relax();
	पूर्ण जबतक (loop--);

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक sc6000_पढ़ो(अक्षर __iomem *vport)
अणु
	अगर (sc6000_रुको_data(vport))
		वापस -EBUSY;

	वापस ioपढ़ो8(vport + DSP_READ);

पूर्ण

अटल पूर्णांक sc6000_ग_लिखो(अक्षर __iomem *vport, पूर्णांक cmd)
अणु
	अचिन्हित अक्षर val;
	पूर्णांक loop = 500000;

	करो अणु
		val = ioपढ़ो8(vport + DSP_STATUS);
		/*
		 * DSP पढ़ोy to receive data अगर bit 7 of val == 0
		 */
		अगर (!(val & 0x80)) अणु
			ioग_लिखो8(cmd, vport + DSP_COMMAND);
			वापस 0;
		पूर्ण
		cpu_relax();
	पूर्ण जबतक (loop--);

	snd_prपूर्णांकk(KERN_ERR "DSP Command (0x%x) timeout.\n", cmd);

	वापस -EIO;
पूर्ण

अटल पूर्णांक sc6000_dsp_get_answer(अक्षर __iomem *vport, पूर्णांक command,
				 अक्षर *data, पूर्णांक data_len)
अणु
	पूर्णांक len = 0;

	अगर (sc6000_ग_लिखो(vport, command)) अणु
		snd_prपूर्णांकk(KERN_ERR "CMD 0x%x: failed!\n", command);
		वापस -EIO;
	पूर्ण

	करो अणु
		पूर्णांक val = sc6000_पढ़ो(vport);

		अगर (val < 0)
			अवरोध;

		data[len++] = val;

	पूर्ण जबतक (len < data_len);

	/*
	 * If no more data available, वापस to the caller, no error अगर len>0.
	 * We have no other way to know when the string is finished.
	 */
	वापस len ? len : -EIO;
पूर्ण

अटल पूर्णांक sc6000_dsp_reset(अक्षर __iomem *vport)
अणु
	ioग_लिखो8(1, vport + DSP_RESET);
	udelay(10);
	ioग_लिखो8(0, vport + DSP_RESET);
	udelay(20);
	अगर (sc6000_पढ़ो(vport) == 0xaa)
		वापस 0;
	वापस -ENODEV;
पूर्ण

/* detection and initialization */
अटल पूर्णांक sc6000_hw_cfg_ग_लिखो(अक्षर __iomem *vport, स्थिर पूर्णांक *cfg)
अणु
	अगर (sc6000_ग_लिखो(vport, COMMAND_6C) < 0) अणु
		snd_prपूर्णांकk(KERN_WARNING "CMD 0x%x: failed!\n", COMMAND_6C);
		वापस -EIO;
	पूर्ण
	अगर (sc6000_ग_लिखो(vport, COMMAND_5C) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "CMD 0x%x: failed!\n", COMMAND_5C);
		वापस -EIO;
	पूर्ण
	अगर (sc6000_ग_लिखो(vport, cfg[0]) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "DATA 0x%x: failed!\n", cfg[0]);
		वापस -EIO;
	पूर्ण
	अगर (sc6000_ग_लिखो(vport, cfg[1]) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "DATA 0x%x: failed!\n", cfg[1]);
		वापस -EIO;
	पूर्ण
	अगर (sc6000_ग_लिखो(vport, COMMAND_C5) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "CMD 0x%x: failed!\n", COMMAND_C5);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sc6000_cfg_ग_लिखो(अक्षर __iomem *vport, अचिन्हित अक्षर softcfg)
अणु

	अगर (sc6000_ग_लिखो(vport, WRITE_MसूचीQ_CFG)) अणु
		snd_prपूर्णांकk(KERN_ERR "CMD 0x%x: failed!\n", WRITE_MसूचीQ_CFG);
		वापस -EIO;
	पूर्ण
	अगर (sc6000_ग_लिखो(vport, softcfg)) अणु
		snd_prपूर्णांकk(KERN_ERR "sc6000_cfg_write: failed!\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sc6000_setup_board(अक्षर __iomem *vport, पूर्णांक config)
अणु
	पूर्णांक loop = 10;

	करो अणु
		अगर (sc6000_ग_लिखो(vport, COMMAND_88)) अणु
			snd_prपूर्णांकk(KERN_ERR "CMD 0x%x: failed!\n",
				   COMMAND_88);
			वापस -EIO;
		पूर्ण
	पूर्ण जबतक ((sc6000_रुको_data(vport) < 0) && loop--);

	अगर (sc6000_पढ़ो(vport) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sc6000_read after CMD 0x%x: failed\n",
			   COMMAND_88);
		वापस -EIO;
	पूर्ण

	अगर (sc6000_cfg_ग_लिखो(vport, config))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक sc6000_init_mss(अक्षर __iomem *vport, पूर्णांक config,
			   अक्षर __iomem *vmss_port, पूर्णांक mss_config)
अणु
	अगर (sc6000_ग_लिखो(vport, DSP_INIT_MSS)) अणु
		snd_prपूर्णांकk(KERN_ERR "sc6000_init_mss [0x%x]: failed!\n",
			   DSP_INIT_MSS);
		वापस -EIO;
	पूर्ण

	msleep(10);

	अगर (sc6000_cfg_ग_लिखो(vport, config))
		वापस -EIO;

	ioग_लिखो8(mss_config, vmss_port);

	वापस 0;
पूर्ण

अटल व्योम sc6000_hw_cfg_encode(अक्षर __iomem *vport, पूर्णांक *cfg,
				 दीर्घ xport, दीर्घ xmpu,
				 दीर्घ xmss_port, पूर्णांक joystick)
अणु
	cfg[0] = 0;
	cfg[1] = 0;
	अगर (xport == 0x240)
		cfg[0] |= 1;
	अगर (xmpu != SNDRV_AUTO_PORT) अणु
		cfg[0] |= (xmpu & 0x30) >> 2;
		cfg[1] |= 0x20;
	पूर्ण
	अगर (xmss_port == 0xe80)
		cfg[0] |= 0x10;
	cfg[0] |= 0x40;		/* always set */
	अगर (!joystick)
		cfg[0] |= 0x02;
	cfg[1] |= 0x80;		/* enable WSS प्रणाली */
	cfg[1] &= ~0x40;	/* disable IDE */
	snd_prपूर्णांकd("hw cfg %x, %x\n", cfg[0], cfg[1]);
पूर्ण

अटल पूर्णांक sc6000_init_board(अक्षर __iomem *vport,
			     अक्षर __iomem *vmss_port, पूर्णांक dev)
अणु
	अक्षर answer[15];
	अक्षर version[2];
	पूर्णांक mss_config = sc6000_irq_to_softcfg(irq[dev]) |
			 sc6000_dma_to_softcfg(dma[dev]);
	पूर्णांक config = mss_config |
		     sc6000_mpu_irq_to_softcfg(mpu_irq[dev]);
	पूर्णांक err;
	पूर्णांक old = 0;

	err = sc6000_dsp_reset(vport);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sc6000_dsp_reset: failed!\n");
		वापस err;
	पूर्ण

	स_रखो(answer, 0, माप(answer));
	err = sc6000_dsp_get_answer(vport, GET_DSP_COPYRIGHT, answer, 15);
	अगर (err <= 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sc6000_dsp_copyright: failed!\n");
		वापस -ENODEV;
	पूर्ण
	/*
	 * My SC-6000 card वापस "SC-6000" in DSPCopyright, so
	 * अगर we have something dअगरferent, we have to be warned.
	 */
	अगर (म_भेदन("SC-6000", answer, 7))
		snd_prपूर्णांकk(KERN_WARNING "Warning: non SC-6000 audio card!\n");

	अगर (sc6000_dsp_get_answer(vport, GET_DSP_VERSION, version, 2) < 2) अणु
		snd_prपूर्णांकk(KERN_ERR "sc6000_dsp_version: failed!\n");
		वापस -ENODEV;
	पूर्ण
	prपूर्णांकk(KERN_INFO PFX "Detected model: %s, DSP version %d.%d\n",
		answer, version[0], version[1]);

	/* set configuration */
	sc6000_ग_लिखो(vport, COMMAND_5C);
	अगर (sc6000_पढ़ो(vport) < 0)
		old = 1;

	अगर (!old) अणु
		पूर्णांक cfg[2];
		sc6000_hw_cfg_encode(vport, &cfg[0], port[dev], mpu_port[dev],
				     mss_port[dev], joystick[dev]);
		अगर (sc6000_hw_cfg_ग_लिखो(vport, cfg) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "sc6000_hw_cfg_write: failed!\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	err = sc6000_setup_board(vport, config);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sc6000_setup_board: failed!\n");
		वापस -ENODEV;
	पूर्ण

	sc6000_dsp_reset(vport);

	अगर (!old) अणु
		sc6000_ग_लिखो(vport, COMMAND_60);
		sc6000_ग_लिखो(vport, 0x02);
		sc6000_dsp_reset(vport);
	पूर्ण

	err = sc6000_setup_board(vport, config);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sc6000_setup_board: failed!\n");
		वापस -ENODEV;
	पूर्ण
	err = sc6000_init_mss(vport, config, vmss_port, mss_config);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Cannot initialize "
			   "Microsoft Sound System mode.\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sc6000_mixer(काष्ठा snd_wss *chip)
अणु
	काष्ठा snd_card *card = chip->card;
	काष्ठा snd_ctl_elem_id id1, id2;
	पूर्णांक err;

	स_रखो(&id1, 0, माप(id1));
	स_रखो(&id2, 0, माप(id2));
	id1.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	id2.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	/* reassign AUX0 to FM */
	म_नकल(id1.name, "Aux Playback Switch");
	म_नकल(id2.name, "FM Playback Switch");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0)
		वापस err;
	म_नकल(id1.name, "Aux Playback Volume");
	म_नकल(id2.name, "FM Playback Volume");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0)
		वापस err;
	/* reassign AUX1 to CD */
	म_नकल(id1.name, "Aux Playback Switch"); id1.index = 1;
	म_नकल(id2.name, "CD Playback Switch");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0)
		वापस err;
	म_नकल(id1.name, "Aux Playback Volume");
	म_नकल(id2.name, "CD Playback Volume");
	err = snd_ctl_नाम_id(card, &id1, &id2);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sc6000_match(काष्ठा device *devptr, अचिन्हित पूर्णांक dev)
अणु
	अगर (!enable[dev])
		वापस 0;
	अगर (port[dev] == SNDRV_AUTO_PORT) अणु
		prपूर्णांकk(KERN_ERR PFX "specify IO port\n");
		वापस 0;
	पूर्ण
	अगर (mss_port[dev] == SNDRV_AUTO_PORT) अणु
		prपूर्णांकk(KERN_ERR PFX "specify MSS port\n");
		वापस 0;
	पूर्ण
	अगर (port[dev] != 0x220 && port[dev] != 0x240) अणु
		prपूर्णांकk(KERN_ERR PFX "Port must be 0x220 or 0x240\n");
		वापस 0;
	पूर्ण
	अगर (mss_port[dev] != 0x530 && mss_port[dev] != 0xe80) अणु
		prपूर्णांकk(KERN_ERR PFX "MSS port must be 0x530 or 0xe80\n");
		वापस 0;
	पूर्ण
	अगर (irq[dev] != SNDRV_AUTO_IRQ && !sc6000_irq_to_softcfg(irq[dev])) अणु
		prपूर्णांकk(KERN_ERR PFX "invalid IRQ %d\n", irq[dev]);
		वापस 0;
	पूर्ण
	अगर (dma[dev] != SNDRV_AUTO_DMA && !sc6000_dma_to_softcfg(dma[dev])) अणु
		prपूर्णांकk(KERN_ERR PFX "invalid DMA %d\n", dma[dev]);
		वापस 0;
	पूर्ण
	अगर (mpu_port[dev] != SNDRV_AUTO_PORT &&
	    (mpu_port[dev] & ~0x30L) != 0x300) अणु
		prपूर्णांकk(KERN_ERR PFX "invalid MPU-401 port %lx\n",
			mpu_port[dev]);
		वापस 0;
	पूर्ण
	अगर (mpu_port[dev] != SNDRV_AUTO_PORT &&
	    mpu_irq[dev] != SNDRV_AUTO_IRQ && mpu_irq[dev] != 0 &&
	    !sc6000_mpu_irq_to_softcfg(mpu_irq[dev])) अणु
		prपूर्णांकk(KERN_ERR PFX "invalid MPU-401 IRQ %d\n", mpu_irq[dev]);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक snd_sc6000_probe(काष्ठा device *devptr, अचिन्हित पूर्णांक dev)
अणु
	अटल स्थिर पूर्णांक possible_irqs[] = अणु 5, 7, 9, 10, 11, -1 पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas[] = अणु 1, 3, 0, -1 पूर्ण;
	पूर्णांक err;
	पूर्णांक xirq = irq[dev];
	पूर्णांक xdma = dma[dev];
	काष्ठा snd_card *card;
	काष्ठा snd_wss *chip;
	काष्ठा snd_opl3 *opl3;
	अक्षर __iomem **vport;
	अक्षर __iomem *vmss_port;


	err = snd_card_new(devptr, index[dev], id[dev], THIS_MODULE,
			   माप(vport), &card);
	अगर (err < 0)
		वापस err;

	vport = card->निजी_data;
	अगर (xirq == SNDRV_AUTO_IRQ) अणु
		xirq = snd_legacy_find_मुक्त_irq(possible_irqs);
		अगर (xirq < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free IRQ\n");
			err = -EBUSY;
			जाओ err_निकास;
		पूर्ण
	पूर्ण

	अगर (xdma == SNDRV_AUTO_DMA) अणु
		xdma = snd_legacy_find_मुक्त_dma(possible_dmas);
		अगर (xdma < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free DMA\n");
			err = -EBUSY;
			जाओ err_निकास;
		पूर्ण
	पूर्ण

	अगर (!request_region(port[dev], 0x10, DRV_NAME)) अणु
		snd_prपूर्णांकk(KERN_ERR PFX
			   "I/O port region is already in use.\n");
		err = -EBUSY;
		जाओ err_निकास;
	पूर्ण
	*vport = devm_ioport_map(devptr, port[dev], 0x10);
	अगर (*vport == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR PFX
			   "I/O port cannot be iomapped.\n");
		err = -EBUSY;
		जाओ err_unmap1;
	पूर्ण

	/* to make it marked as used */
	अगर (!request_region(mss_port[dev], 4, DRV_NAME)) अणु
		snd_prपूर्णांकk(KERN_ERR PFX
			   "SC-6000 port I/O port region is already in use.\n");
		err = -EBUSY;
		जाओ err_unmap1;
	पूर्ण
	vmss_port = devm_ioport_map(devptr, mss_port[dev], 4);
	अगर (!vmss_port) अणु
		snd_prपूर्णांकk(KERN_ERR PFX
			   "MSS port I/O cannot be iomapped.\n");
		err = -EBUSY;
		जाओ err_unmap2;
	पूर्ण

	snd_prपूर्णांकd("Initializing BASE[0x%lx] IRQ[%d] DMA[%d] MIRQ[%d]\n",
		   port[dev], xirq, xdma,
		   mpu_irq[dev] == SNDRV_AUTO_IRQ ? 0 : mpu_irq[dev]);

	err = sc6000_init_board(*vport, vmss_port, dev);
	अगर (err < 0)
		जाओ err_unmap2;

	err = snd_wss_create(card, mss_port[dev] + 4,  -1, xirq, xdma, -1,
			     WSS_HW_DETECT, 0, &chip);
	अगर (err < 0)
		जाओ err_unmap2;

	err = snd_wss_pcm(chip, 0);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX
			   "error creating new WSS PCM device\n");
		जाओ err_unmap2;
	पूर्ण
	err = snd_wss_mixer(chip);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "error creating new WSS mixer\n");
		जाओ err_unmap2;
	पूर्ण
	err = snd_sc6000_mixer(chip);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "the mixer rewrite failed\n");
		जाओ err_unmap2;
	पूर्ण
	अगर (snd_opl3_create(card,
			    0x388, 0x388 + 2,
			    OPL3_HW_AUTO, 0, &opl3) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "no OPL device at 0x%x-0x%x ?\n",
			   0x388, 0x388 + 2);
	पूर्ण अन्यथा अणु
		err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य);
		अगर (err < 0)
			जाओ err_unmap2;
	पूर्ण

	अगर (mpu_port[dev] != SNDRV_AUTO_PORT) अणु
		अगर (mpu_irq[dev] == SNDRV_AUTO_IRQ)
			mpu_irq[dev] = -1;
		अगर (snd_mpu401_uart_new(card, 0,
					MPU401_HW_MPU401,
					mpu_port[dev], 0,
					mpu_irq[dev], शून्य) < 0)
			snd_prपूर्णांकk(KERN_ERR "no MPU-401 device at 0x%lx ?\n",
					mpu_port[dev]);
	पूर्ण

	म_नकल(card->driver, DRV_NAME);
	म_नकल(card->लघुname, "SC-6000");
	प्र_लिखो(card->दीर्घname, "Gallant SC-6000 at 0x%lx, irq %d, dma %d",
		mss_port[dev], xirq, xdma);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ err_unmap2;

	dev_set_drvdata(devptr, card);
	वापस 0;

err_unmap2:
	sc6000_setup_board(*vport, 0);
	release_region(mss_port[dev], 4);
err_unmap1:
	release_region(port[dev], 0x10);
err_निकास:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_sc6000_हटाओ(काष्ठा device *devptr, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(devptr);
	अक्षर __iomem **vport = card->निजी_data;

	अगर (sc6000_setup_board(*vport, 0) < 0)
		snd_prपूर्णांकk(KERN_WARNING "sc6000_setup_board failed on exit!\n");

	release_region(port[dev], 0x10);
	release_region(mss_port[dev], 4);

	snd_card_मुक्त(card);
पूर्ण

अटल काष्ठा isa_driver snd_sc6000_driver = अणु
	.match		= snd_sc6000_match,
	.probe		= snd_sc6000_probe,
	.हटाओ		= snd_sc6000_हटाओ,
	/* FIXME: suspend/resume */
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;


module_isa_driver(snd_sc6000_driver, SNDRV_CARDS);
