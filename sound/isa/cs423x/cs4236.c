<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम generic CS4232/CS4235/CS4236/CS4236B/CS4237B/CS4238B/CS4239 chips
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cirrus Logic CS4232-9");
MODULE_ALIAS("snd_cs4232");

#घोषणा IDENT "CS4232+"
#घोषणा DEV_NAME "cs4232+"

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP; /* Enable this card */
#अगर_घोषित CONFIG_PNP
अटल bool isapnp[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
#पूर्ण_अगर
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ cport[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;/* PnP setup */
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल दीर्घ sb_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5,7,9,11,12,15 */
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 9,11,12,15 */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3,5,6,7 */
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3,5,6,7 */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " IDENT " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " IDENT " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " IDENT " soundcard.");
#अगर_घोषित CONFIG_PNP
module_param_array(isapnp, bool, शून्य, 0444);
MODULE_PARM_DESC(isapnp, "ISA PnP detection for specified soundcard.");
#पूर्ण_अगर
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for " IDENT " driver.");
module_param_hw_array(cport, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(cport, "Control port # for " IDENT " driver.");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for " IDENT " driver.");
module_param_hw_array(fm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fm_port, "FM port # for " IDENT " driver.");
module_param_hw_array(sb_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(sb_port, "SB port # for " IDENT " driver (optional).");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for " IDENT " driver.");
module_param_hw_array(mpu_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(mpu_irq, "MPU-401 IRQ # for " IDENT " driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "DMA1 # for " IDENT " driver.");
module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "DMA2 # for " IDENT " driver.");

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक isa_रेजिस्टरed;
अटल पूर्णांक pnpc_रेजिस्टरed;
अटल पूर्णांक pnp_रेजिस्टरed;
#पूर्ण_अगर /* CONFIG_PNP */

काष्ठा snd_card_cs4236 अणु
	काष्ठा snd_wss *chip;
	काष्ठा resource *res_sb_port;
#अगर_घोषित CONFIG_PNP
	काष्ठा pnp_dev *wss;
	काष्ठा pnp_dev *ctrl;
	काष्ठा pnp_dev *mpu;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PNP

/*
 * PNP BIOS
 */
अटल स्थिर काष्ठा pnp_device_id snd_cs423x_pnpbiosids[] = अणु
	अणु .id = "CSC0100" पूर्ण,
	अणु .id = "CSC0000" पूर्ण,
	/* Guillemot Turtlebeach something appears to be cs4232 compatible
	 * (untested) */
	अणु .id = "GIM0100" पूर्ण,
	अणु .id = "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pnp, snd_cs423x_pnpbiosids);

#घोषणा CS423X_ISAPNP_DRIVER	"cs4232_isapnp"
अटल स्थिर काष्ठा pnp_card_device_id snd_cs423x_pnpids[] = अणु
	/* Philips PCA70PS */
	अणु .id = "CSC0d32", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "PNPb006" पूर्ण पूर्ण पूर्ण,
	/* TerraTec Maestro 32/96 (CS4232) */
	अणु .id = "CSC1a32", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* HP Omnibook 5500 onboard */
	अणु .id = "CSC4232", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0002" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Unnamed CS4236 card (Made in Taiwan) */
	अणु .id = "CSC4236", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Turtle Beach TBS-2000 (CS4232) */
	अणु .id = "CSC7532", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSCb006" पूर्ण पूर्ण पूर्ण,
	/* Turtle Beach Tropez Plus (CS4232) */
	अणु .id = "CSC7632", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "PNPb006" पूर्ण पूर्ण पूर्ण,
	/* SIC CrystalWave 32 (CS4232) */
	अणु .id = "CSCf032", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Netfinity 3000 on-board soundcard */
	अणु .id = "CSCe825", .devs = अणु अणु "CSC0100" पूर्ण, अणु "CSC0110" पूर्ण, अणु "CSC010f" पूर्ण पूर्ण पूर्ण,
	/* Intel Marlin Spike Motherboard - CS4235 */
	अणु .id = "CSC0225", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Intel Marlin Spike Motherboard (#2) - CS4235 */
	अणु .id = "CSC0225", .devs = अणु अणु "CSC0100" पूर्ण, अणु "CSC0110" पूर्ण, अणु "CSC0103" पूर्ण पूर्ण पूर्ण,
	/* Unknown Intel मुख्यboard - CS4235 */
	अणु .id = "CSC0225", .devs = अणु अणु "CSC0100" पूर्ण, अणु "CSC0110" पूर्ण पूर्ण पूर्ण,
	/* Genius Sound Maker 3DJ - CS4237B */
	अणु .id = "CSC0437", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Digital PC 5000 Onboard - CS4236B */
	अणु .id = "CSC0735", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण पूर्ण पूर्ण,
	/* some unknown CS4236B */
	अणु .id = "CSC0b35", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Intel PR440FX Onboard sound */
	अणु .id = "CSC0b36", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* CS4235 on मुख्यboard without MPU */
	अणु .id = "CSC1425", .devs = अणु अणु "CSC0100" पूर्ण, अणु "CSC0110" पूर्ण पूर्ण पूर्ण,
	/* Gateway E1000 Onboard CS4236B */
	अणु .id = "CSC1335", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* HP 6330 Onboard sound */
	अणु .id = "CSC1525", .devs = अणु अणु "CSC0100" पूर्ण, अणु "CSC0110" पूर्ण, अणु "CSC0103" पूर्ण पूर्ण पूर्ण,
	/* Crystal Computer TidalWave128 */
	अणु .id = "CSC1e37", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* ACER AW37 - CS4235 */
	अणु .id = "CSC4236", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* build-in soundcard in EliteGroup P5TX-LA motherboard - CS4237B */
	अणु .id = "CSC4237", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Crystal 3D - CS4237B */
	अणु .id = "CSC4336", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Typhoon Soundप्रणाली PnP - CS4236B */
	अणु .id = "CSC4536", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Crystal CX4235-XQ3 EP - CS4235 */
	अणु .id = "CSC4625", .devs = अणु अणु "CSC0100" पूर्ण, अणु "CSC0110" पूर्ण, अणु "CSC0103" पूर्ण पूर्ण पूर्ण,
	/* Crystal Semiconductors CS4237B */
	अणु .id = "CSC4637", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* NewClear 3D - CX4237B-XQ3 */
	अणु .id = "CSC4837", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Dell Optiplex GX1 - CS4236B */
	अणु .id = "CSC6835", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Dell P410 motherboard - CS4236B */
	अणु .id = "CSC6835", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण पूर्ण पूर्ण,
	/* Dell Workstation 400 Onboard - CS4236B */
	अणु .id = "CSC6836", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Turtle Beach Malibu - CS4237B */
	अणु .id = "CSC7537", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* CS4235 - onboard */
	अणु .id = "CSC8025", .devs = अणु अणु "CSC0100" पूर्ण, अणु "CSC0110" पूर्ण, अणु "CSC0103" पूर्ण पूर्ण पूर्ण,
	/* IBM Aptiva 2137 E24 Onboard - CS4237B */
	अणु .id = "CSC8037", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* IBM IntelliStation M Pro motherboard */
	अणु .id = "CSCc835", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण पूर्ण पूर्ण,
	/* Guillemot MaxiSound 16 PnP - CS4236B */
	अणु .id = "CSC9836", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Gallant SC-70P */
	अणु .id = "CSC9837", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* Techmakers MF-4236PW */
	अणु .id = "CSCa736", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* TerraTec AudioSystem EWS64XL - CS4236B */
	अणु .id = "CSCa836", .devs = अणु अणु "CSCa800" पूर्ण, अणु "CSCa810" पूर्ण, अणु "CSCa803" पूर्ण पूर्ण पूर्ण,
	/* TerraTec AudioSystem EWS64XL - CS4236B */
	अणु .id = "CSCa836", .devs = अणु अणु "CSCa800" पूर्ण, अणु "CSCa810" पूर्ण पूर्ण पूर्ण,
	/* ACER AW37/Pro - CS4235 */
	अणु .id = "CSCd925", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* ACER AW35/Pro - CS4237B */
	अणु .id = "CSCd937", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* CS4235 without MPU401 */
	अणु .id = "CSCe825", .devs = अणु अणु "CSC0100" पूर्ण, अणु "CSC0110" पूर्ण पूर्ण पूर्ण,
	/* Unknown SiS530 - CS4235 */
	अणु .id = "CSC4825", .devs = अणु अणु "CSC0100" पूर्ण, अणु "CSC0110" पूर्ण पूर्ण पूर्ण,
	/* IBM IntelliStation M Pro 6898 11U - CS4236B */
	अणु .id = "CSCe835", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण पूर्ण पूर्ण,
	/* IBM PC 300PL Onboard - CS4236B */
	अणु .id = "CSCe836", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण पूर्ण पूर्ण,
	/* Some noname CS4236 based card */
	अणु .id = "CSCe936", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* CS4236B */
	अणु .id = "CSCf235", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* CS4236B */
	अणु .id = "CSCf238", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "CSC0003" पूर्ण पूर्ण पूर्ण,
	/* --- */
	अणु .id = "" पूर्ण	/* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_cs423x_pnpids);

/* WSS initialization */
अटल पूर्णांक snd_cs423x_pnp_init_wss(पूर्णांक dev, काष्ठा pnp_dev *pdev)
अणु
	अगर (pnp_activate_dev(pdev) < 0) अणु
		prपूर्णांकk(KERN_ERR IDENT " WSS PnP configure failed for WSS (out of resources?)\n");
		वापस -EBUSY;
	पूर्ण
	port[dev] = pnp_port_start(pdev, 0);
	अगर (fm_port[dev] > 0)
		fm_port[dev] = pnp_port_start(pdev, 1);
	sb_port[dev] = pnp_port_start(pdev, 2);
	irq[dev] = pnp_irq(pdev, 0);
	dma1[dev] = pnp_dma(pdev, 0);
	dma2[dev] = pnp_dma(pdev, 1) == 4 ? -1 : (पूर्णांक)pnp_dma(pdev, 1);
	snd_prपूर्णांकdd("isapnp WSS: wss port=0x%lx, fm port=0x%lx, sb port=0x%lx\n",
			port[dev], fm_port[dev], sb_port[dev]);
	snd_prपूर्णांकdd("isapnp WSS: irq=%i, dma1=%i, dma2=%i\n",
			irq[dev], dma1[dev], dma2[dev]);
	वापस 0;
पूर्ण

/* CTRL initialization */
अटल पूर्णांक snd_cs423x_pnp_init_ctrl(पूर्णांक dev, काष्ठा pnp_dev *pdev)
अणु
	अगर (pnp_activate_dev(pdev) < 0) अणु
		prपूर्णांकk(KERN_ERR IDENT " CTRL PnP configure failed for WSS (out of resources?)\n");
		वापस -EBUSY;
	पूर्ण
	cport[dev] = pnp_port_start(pdev, 0);
	snd_prपूर्णांकdd("isapnp CTRL: control port=0x%lx\n", cport[dev]);
	वापस 0;
पूर्ण

/* MPU initialization */
अटल पूर्णांक snd_cs423x_pnp_init_mpu(पूर्णांक dev, काष्ठा pnp_dev *pdev)
अणु
	अगर (pnp_activate_dev(pdev) < 0) अणु
		prपूर्णांकk(KERN_ERR IDENT " MPU401 PnP configure failed for WSS (out of resources?)\n");
		mpu_port[dev] = SNDRV_AUTO_PORT;
		mpu_irq[dev] = SNDRV_AUTO_IRQ;
	पूर्ण अन्यथा अणु
		mpu_port[dev] = pnp_port_start(pdev, 0);
		अगर (mpu_irq[dev] >= 0 &&
		    pnp_irq_valid(pdev, 0) &&
		    pnp_irq(pdev, 0) != (resource_माप_प्रकार)-1) अणु
			mpu_irq[dev] = pnp_irq(pdev, 0);
		पूर्ण अन्यथा अणु
			mpu_irq[dev] = -1;	/* disable पूर्णांकerrupt */
		पूर्ण
	पूर्ण
	snd_prपूर्णांकdd("isapnp MPU: port=0x%lx, irq=%i\n", mpu_port[dev], mpu_irq[dev]);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_card_cs423x_pnp(पूर्णांक dev, काष्ठा snd_card_cs4236 *acard,
			       काष्ठा pnp_dev *pdev,
			       काष्ठा pnp_dev *cdev)
अणु
	acard->wss = pdev;
	अगर (snd_cs423x_pnp_init_wss(dev, acard->wss) < 0)
		वापस -EBUSY;
	अगर (cdev)
		cport[dev] = pnp_port_start(cdev, 0);
	अन्यथा
		cport[dev] = -1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_card_cs423x_pnpc(पूर्णांक dev, काष्ठा snd_card_cs4236 *acard,
				काष्ठा pnp_card_link *card,
				स्थिर काष्ठा pnp_card_device_id *id)
अणु
	acard->wss = pnp_request_card_device(card, id->devs[0].id, शून्य);
	अगर (acard->wss == शून्य)
		वापस -EBUSY;
	acard->ctrl = pnp_request_card_device(card, id->devs[1].id, शून्य);
	अगर (acard->ctrl == शून्य)
		वापस -EBUSY;
	अगर (id->devs[2].id[0]) अणु
		acard->mpu = pnp_request_card_device(card, id->devs[2].id, शून्य);
		अगर (acard->mpu == शून्य)
			वापस -EBUSY;
	पूर्ण

	/* WSS initialization */
	अगर (snd_cs423x_pnp_init_wss(dev, acard->wss) < 0)
		वापस -EBUSY;

	/* CTRL initialization */
	अगर (acard->ctrl && cport[dev] > 0) अणु
		अगर (snd_cs423x_pnp_init_ctrl(dev, acard->ctrl) < 0)
			वापस -EBUSY;
	पूर्ण
	/* MPU initialization */
	अगर (acard->mpu && mpu_port[dev] > 0) अणु
		अगर (snd_cs423x_pnp_init_mpu(dev, acard->mpu) < 0)
			वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PNP */

#अगर_घोषित CONFIG_PNP
#घोषणा is_isapnp_selected(dev)		isapnp[dev]
#अन्यथा
#घोषणा is_isapnp_selected(dev)		0
#पूर्ण_अगर

अटल व्योम snd_card_cs4236_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_card_cs4236 *acard = card->निजी_data;

	release_and_मुक्त_resource(acard->res_sb_port);
पूर्ण

अटल पूर्णांक snd_cs423x_card_new(काष्ठा device *pdev, पूर्णांक dev,
			       काष्ठा snd_card **cardp)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_card_new(pdev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_card_cs4236), &card);
	अगर (err < 0)
		वापस err;
	card->निजी_मुक्त = snd_card_cs4236_मुक्त;
	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs423x_probe(काष्ठा snd_card *card, पूर्णांक dev)
अणु
	काष्ठा snd_card_cs4236 *acard;
	काष्ठा snd_wss *chip;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;

	acard = card->निजी_data;
	अगर (sb_port[dev] > 0 && sb_port[dev] != SNDRV_AUTO_PORT)
		अगर ((acard->res_sb_port = request_region(sb_port[dev], 16, IDENT " SB")) == शून्य) अणु
			prपूर्णांकk(KERN_ERR IDENT ": unable to register SB port at 0x%lx\n", sb_port[dev]);
			वापस -EBUSY;
		पूर्ण

	err = snd_cs4236_create(card, port[dev], cport[dev],
			     irq[dev],
			     dma1[dev], dma2[dev],
			     WSS_HW_DETECT3, 0, &chip);
	अगर (err < 0)
		वापस err;

	acard->chip = chip;
	अगर (chip->hardware & WSS_HW_CS4236B_MASK) अणु

		err = snd_cs4236_pcm(chip, 0);
		अगर (err < 0)
			वापस err;

		err = snd_cs4236_mixer(chip);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		err = snd_wss_pcm(chip, 0);
		अगर (err < 0)
			वापस err;

		err = snd_wss_mixer(chip);
		अगर (err < 0)
			वापस err;
	पूर्ण
	strscpy(card->driver, chip->pcm->name, माप(card->driver));
	strscpy(card->लघुname, chip->pcm->name, माप(card->लघुname));
	अगर (dma2[dev] < 0)
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			 "%s at 0x%lx, irq %i, dma %i",
			 chip->pcm->name, chip->port, irq[dev], dma1[dev]);
	अन्यथा
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			 "%s at 0x%lx, irq %i, dma %i&%d",
			 chip->pcm->name, chip->port, irq[dev], dma1[dev],
			 dma2[dev]);

	err = snd_wss_समयr(chip, 0);
	अगर (err < 0)
		वापस err;

	अगर (fm_port[dev] > 0 && fm_port[dev] != SNDRV_AUTO_PORT) अणु
		अगर (snd_opl3_create(card,
				    fm_port[dev], fm_port[dev] + 2,
				    OPL3_HW_OPL3_CS, 0, &opl3) < 0) अणु
			prपूर्णांकk(KERN_WARNING IDENT ": OPL3 not detected\n");
		पूर्ण अन्यथा अणु
			अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (mpu_port[dev] > 0 && mpu_port[dev] != SNDRV_AUTO_PORT) अणु
		अगर (mpu_irq[dev] == SNDRV_AUTO_IRQ)
			mpu_irq[dev] = -1;
		अगर (snd_mpu401_uart_new(card, 0, MPU401_HW_CS4232,
					mpu_port[dev], 0,
					mpu_irq[dev], शून्य) < 0)
			prपूर्णांकk(KERN_WARNING IDENT ": MPU401 not detected\n");
	पूर्ण

	वापस snd_card_रेजिस्टर(card);
पूर्ण

अटल पूर्णांक snd_cs423x_isa_match(काष्ठा device *pdev,
				अचिन्हित पूर्णांक dev)
अणु
	अगर (!enable[dev] || is_isapnp_selected(dev))
		वापस 0;

	अगर (port[dev] == SNDRV_AUTO_PORT) अणु
		dev_err(pdev, "please specify port\n");
		वापस 0;
	पूर्ण
	अगर (cport[dev] == SNDRV_AUTO_PORT) अणु
		dev_err(pdev, "please specify cport\n");
		वापस 0;
	पूर्ण
	अगर (irq[dev] == SNDRV_AUTO_IRQ) अणु
		dev_err(pdev, "please specify irq\n");
		वापस 0;
	पूर्ण
	अगर (dma1[dev] == SNDRV_AUTO_DMA) अणु
		dev_err(pdev, "please specify dma1\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक snd_cs423x_isa_probe(काष्ठा device *pdev,
				अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_cs423x_card_new(pdev, dev, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_cs423x_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	dev_set_drvdata(pdev, card);
	वापस 0;
पूर्ण

अटल व्योम snd_cs423x_isa_हटाओ(काष्ठा device *pdev,
				 अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(pdev));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_cs423x_suspend(काष्ठा snd_card *card)
अणु
	काष्ठा snd_card_cs4236 *acard = card->निजी_data;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	acard->chip->suspend(acard->chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs423x_resume(काष्ठा snd_card *card)
अणु
	काष्ठा snd_card_cs4236 *acard = card->निजी_data;
	acard->chip->resume(acard->chip);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs423x_isa_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n,
				  pm_message_t state)
अणु
	वापस snd_cs423x_suspend(dev_get_drvdata(dev));
पूर्ण

अटल पूर्णांक snd_cs423x_isa_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	वापस snd_cs423x_resume(dev_get_drvdata(dev));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा isa_driver cs423x_isa_driver = अणु
	.match		= snd_cs423x_isa_match,
	.probe		= snd_cs423x_isa_probe,
	.हटाओ		= snd_cs423x_isa_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_cs423x_isa_suspend,
	.resume		= snd_cs423x_isa_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;


#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_cs423x_pnpbios_detect(काष्ठा pnp_dev *pdev,
				     स्थिर काष्ठा pnp_device_id *id)
अणु
	अटल पूर्णांक dev;
	पूर्णांक err;
	काष्ठा snd_card *card;
	काष्ठा pnp_dev *cdev;
	अक्षर cid[PNP_ID_LEN];

	अगर (pnp_device_is_isapnp(pdev))
		वापस -ENOENT;	/* we have another procedure - card */
	क्रम (; dev < SNDRV_CARDS; dev++) अणु
		अगर (enable[dev] && isapnp[dev])
			अवरोध;
	पूर्ण
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	/* prepare second id */
	म_नकल(cid, pdev->id[0].id);
	cid[5] = '1';
	cdev = शून्य;
	list_क्रम_each_entry(cdev, &(pdev->protocol->devices), protocol_list) अणु
		अगर (!म_भेद(cdev->id[0].id, cid))
			अवरोध;
	पूर्ण
	err = snd_cs423x_card_new(&pdev->dev, dev, &card);
	अगर (err < 0)
		वापस err;
	err = snd_card_cs423x_pnp(dev, card->निजी_data, pdev, cdev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "PnP BIOS detection failed for " IDENT "\n");
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_cs423x_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pnp_set_drvdata(pdev, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_cs423x_pnp_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	snd_card_मुक्त(pnp_get_drvdata(pdev));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_cs423x_pnp_suspend(काष्ठा pnp_dev *pdev, pm_message_t state)
अणु
	वापस snd_cs423x_suspend(pnp_get_drvdata(pdev));
पूर्ण

अटल पूर्णांक snd_cs423x_pnp_resume(काष्ठा pnp_dev *pdev)
अणु
	वापस snd_cs423x_resume(pnp_get_drvdata(pdev));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_driver cs423x_pnp_driver = अणु
	.name = "cs423x-pnpbios",
	.id_table = snd_cs423x_pnpbiosids,
	.probe = snd_cs423x_pnpbios_detect,
	.हटाओ = snd_cs423x_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_cs423x_pnp_suspend,
	.resume		= snd_cs423x_pnp_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक snd_cs423x_pnpc_detect(काष्ठा pnp_card_link *pcard,
				  स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	पूर्णांक res;

	क्रम ( ; dev < SNDRV_CARDS; dev++) अणु
		अगर (enable[dev] && isapnp[dev])
			अवरोध;
	पूर्ण
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	res = snd_cs423x_card_new(&pcard->card->dev, dev, &card);
	अगर (res < 0)
		वापस res;
	अगर ((res = snd_card_cs423x_pnpc(dev, card->निजी_data, pcard, pid)) < 0) अणु
		prपूर्णांकk(KERN_ERR "isapnp detection failed and probing for " IDENT
		       " is not supported\n");
		snd_card_मुक्त(card);
		वापस res;
	पूर्ण
	अगर ((res = snd_cs423x_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस res;
	पूर्ण
	pnp_set_card_drvdata(pcard, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_cs423x_pnpc_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_cs423x_pnpc_suspend(काष्ठा pnp_card_link *pcard, pm_message_t state)
अणु
	वापस snd_cs423x_suspend(pnp_get_card_drvdata(pcard));
पूर्ण

अटल पूर्णांक snd_cs423x_pnpc_resume(काष्ठा pnp_card_link *pcard)
अणु
	वापस snd_cs423x_resume(pnp_get_card_drvdata(pcard));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_card_driver cs423x_pnpc_driver = अणु
	.flags = PNP_DRIVER_RES_DISABLE,
	.name = CS423X_ISAPNP_DRIVER,
	.id_table = snd_cs423x_pnpids,
	.probe = snd_cs423x_pnpc_detect,
	.हटाओ = snd_cs423x_pnpc_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_cs423x_pnpc_suspend,
	.resume		= snd_cs423x_pnpc_resume,
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init alsa_card_cs423x_init(व्योम)
अणु
	पूर्णांक err;

	err = isa_रेजिस्टर_driver(&cs423x_isa_driver, SNDRV_CARDS);
#अगर_घोषित CONFIG_PNP
	अगर (!err)
		isa_रेजिस्टरed = 1;
	err = pnp_रेजिस्टर_driver(&cs423x_pnp_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;
	err = pnp_रेजिस्टर_card_driver(&cs423x_pnpc_driver);
	अगर (!err)
		pnpc_रेजिस्टरed = 1;
	अगर (pnp_रेजिस्टरed)
		err = 0;
	अगर (isa_रेजिस्टरed)
		err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_card_cs423x_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnpc_रेजिस्टरed)
		pnp_unरेजिस्टर_card_driver(&cs423x_pnpc_driver);
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&cs423x_pnp_driver);
	अगर (isa_रेजिस्टरed)
#पूर्ण_अगर
		isa_unरेजिस्टर_driver(&cs423x_isa_driver);
पूर्ण

module_init(alsa_card_cs423x_init)
module_निकास(alsa_card_cs423x_निकास)
