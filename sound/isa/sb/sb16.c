<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम SoundBlaster 16/AWE32/AWE64 soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <यंत्र/dma.h>
#समावेश <linux/init.h>
#समावेश <linux/pnp.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/sb.h>
#समावेश <sound/sb16_csp.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/emu8000.h>
#समावेश <sound/seq_device.h>
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

#अगर_घोषित SNDRV_SBAWE
#घोषणा PFX "sbawe: "
#अन्यथा
#घोषणा PFX "sb16: "
#पूर्ण_अगर

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_LICENSE("GPL");
#अगर_अघोषित SNDRV_SBAWE
MODULE_DESCRIPTION("Sound Blaster 16");
#अन्यथा
MODULE_DESCRIPTION("Sound Blaster AWE");
#पूर्ण_अगर

#अगर 0
#घोषणा SNDRV_DEBUG_IRQ
#पूर्ण_अगर

#अगर defined(SNDRV_SBAWE) && IS_ENABLED(CONFIG_SND_SEQUENCER)
#घोषणा SNDRV_SBAWE_EMU8000
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP; /* Enable this card */
#अगर_घोषित CONFIG_PNP
अटल bool isapnp[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
#पूर्ण_अगर
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x220,0x240,0x260,0x280 */
अटल दीर्घ mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x330,0x300 */
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
#अगर_घोषित SNDRV_SBAWE_EMU8000
अटल दीर्घ awe_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
#पूर्ण_अगर
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5,7,9,10 */
अटल पूर्णांक dma8[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3 */
अटल पूर्णांक dma16[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 5,6,7 */
अटल पूर्णांक mic_agc[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
#अगर_घोषित CONFIG_SND_SB16_CSP
अटल पूर्णांक csp[SNDRV_CARDS];
#पूर्ण_अगर
#अगर_घोषित SNDRV_SBAWE_EMU8000
अटल पूर्णांक seq_ports[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 4पूर्ण;
#पूर्ण_अगर

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for SoundBlaster 16 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for SoundBlaster 16 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable SoundBlaster 16 soundcard.");
#अगर_घोषित CONFIG_PNP
module_param_array(isapnp, bool, शून्य, 0444);
MODULE_PARM_DESC(isapnp, "PnP detection for specified soundcard.");
#पूर्ण_अगर
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for SB16 driver.");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for SB16 driver.");
module_param_hw_array(fm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fm_port, "FM port # for SB16 PnP driver.");
#अगर_घोषित SNDRV_SBAWE_EMU8000
module_param_hw_array(awe_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(awe_port, "AWE port # for SB16 PnP driver.");
#पूर्ण_अगर
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for SB16 driver.");
module_param_hw_array(dma8, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma8, "8-bit DMA # for SB16 driver.");
module_param_hw_array(dma16, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma16, "16-bit DMA # for SB16 driver.");
module_param_array(mic_agc, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(mic_agc, "Mic Auto-Gain-Control switch.");
#अगर_घोषित CONFIG_SND_SB16_CSP
module_param_array(csp, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(csp, "ASP/CSP chip support.");
#पूर्ण_अगर
#अगर_घोषित SNDRV_SBAWE_EMU8000
module_param_array(seq_ports, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(seq_ports, "Number of sequencer ports for WaveTable synth.");
#पूर्ण_अगर

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक isa_रेजिस्टरed;
अटल पूर्णांक pnp_रेजिस्टरed;
#पूर्ण_अगर

काष्ठा snd_card_sb16 अणु
	काष्ठा resource *fm_res;	/* used to block FM i/o region क्रम legacy cards */
	काष्ठा snd_sb *chip;
#अगर_घोषित CONFIG_PNP
	पूर्णांक dev_no;
	काष्ठा pnp_dev *dev;
#अगर_घोषित SNDRV_SBAWE_EMU8000
	काष्ठा pnp_dev *devwt;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PNP

अटल स्थिर काष्ठा pnp_card_device_id snd_sb16_pnpids[] = अणु
#अगर_अघोषित SNDRV_SBAWE
	/* Sound Blaster 16 PnP */
	अणु .id = "CTL0024", .devs = अणु अणु "CTL0031" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 PnP */
	अणु .id = "CTL0025", .devs = अणु अणु "CTL0031" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 PnP */
	अणु .id = "CTL0026", .devs = अणु अणु "CTL0031" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 PnP */
	अणु .id = "CTL0027", .devs = अणु अणु "CTL0031" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 PnP */
	अणु .id = "CTL0028", .devs = अणु अणु "CTL0031" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 PnP */
	अणु .id = "CTL0029", .devs = अणु अणु "CTL0031" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 PnP */
	अणु .id = "CTL002a", .devs = अणु अणु "CTL0031" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 PnP */
	/* Note: This card has also a CTL0051:StereoEnhance device!!! */
	अणु .id = "CTL002b", .devs = अणु अणु "CTL0031" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 PnP */
	अणु .id = "CTL002c", .devs = अणु अणु "CTL0031" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster Vibra16S */
	अणु .id = "CTL0051", .devs = अणु अणु "CTL0001" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster Vibra16C */
	अणु .id = "CTL0070", .devs = अणु अणु "CTL0001" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster Vibra16CL - added by cपंचांग@ardi.com */
	अणु .id = "CTL0080", .devs = अणु अणु "CTL0041" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 'value' PnP. It says model ct4130 on the pcb, */
	/* but ct4131 on a sticker on the board.. */
	अणु .id = "CTL0086", .devs = अणु अणु "CTL0041" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster Vibra16X */
	अणु .id = "CTL00f0", .devs = अणु अणु "CTL0043" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 (Virtual PC 2004) */
	अणु .id = "tBA03b0", .devs = अणु अणु.id="PNPb003" पूर्ण पूर्ण पूर्ण,
#अन्यथा  /* SNDRV_SBAWE defined */
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL0035", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL0039", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL0042", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL0043", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	/* Note: This card has also a CTL0051:StereoEnhance device!!! */
	अणु .id = "CTL0044", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	/* Note: This card has also a CTL0051:StereoEnhance device!!! */
	अणु .id = "CTL0045", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL0046", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL0047", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL0048", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL0054", .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL009a", .devs = अणु अणु "CTL0041" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 32 PnP */
	अणु .id = "CTL009c", .devs = अणु अणु "CTL0041" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 32 PnP */
	अणु .id = "CTL009f", .devs = अणु अणु "CTL0041" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 64 PnP */
	अणु .id = "CTL009d", .devs = अणु अणु "CTL0042" पूर्ण, अणु "CTL0022" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 64 PnP Gold */
	अणु .id = "CTL009e", .devs = अणु अणु "CTL0044" पूर्ण, अणु "CTL0023" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 64 PnP Gold */
	अणु .id = "CTL00b2", .devs = अणु अणु "CTL0044" पूर्ण, अणु "CTL0023" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 64 PnP */
	अणु .id = "CTL00c1", .devs = अणु अणु "CTL0042" पूर्ण, अणु "CTL0022" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 64 PnP */
	अणु .id = "CTL00c3", .devs = अणु अणु "CTL0045" पूर्ण, अणु "CTL0022" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 64 PnP */
	अणु .id = "CTL00c5", .devs = अणु अणु "CTL0045" पूर्ण, अणु "CTL0022" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 64 PnP */
	अणु .id = "CTL00c7", .devs = अणु अणु "CTL0045" पूर्ण, अणु "CTL0022" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 64 PnP */
	अणु .id = "CTL00e4", .devs = अणु अणु "CTL0045" पूर्ण, अणु "CTL0022" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster AWE 64 PnP */
	अणु .id = "CTL00e9", .devs = अणु अणु "CTL0045" पूर्ण, अणु "CTL0022" पूर्ण पूर्ण पूर्ण,
	/* Sound Blaster 16 PnP (AWE) */
	अणु .id = "CTL00ed", .devs = अणु अणु "CTL0041" पूर्ण, अणु "CTL0070" पूर्ण पूर्ण पूर्ण,
	/* Generic entries */
	अणु .id = "CTLXXXX" , .devs = अणु अणु "CTL0031" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	अणु .id = "CTLXXXX" , .devs = अणु अणु "CTL0041" पूर्ण, अणु "CTL0021" पूर्ण पूर्ण पूर्ण,
	अणु .id = "CTLXXXX" , .devs = अणु अणु "CTL0042" पूर्ण, अणु "CTL0022" पूर्ण पूर्ण पूर्ण,
	अणु .id = "CTLXXXX" , .devs = अणु अणु "CTL0044" पूर्ण, अणु "CTL0023" पूर्ण पूर्ण पूर्ण,
	अणु .id = "CTLXXXX" , .devs = अणु अणु "CTL0045" पूर्ण, अणु "CTL0022" पूर्ण पूर्ण पूर्ण,
#पूर्ण_अगर /* SNDRV_SBAWE */
	अणु .id = "", पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_sb16_pnpids);

#पूर्ण_अगर /* CONFIG_PNP */

#अगर_घोषित SNDRV_SBAWE_EMU8000
#घोषणा DRIVER_NAME	"snd-card-sbawe"
#अन्यथा
#घोषणा DRIVER_NAME	"snd-card-sb16"
#पूर्ण_अगर

#अगर_घोषित CONFIG_PNP

अटल पूर्णांक snd_card_sb16_pnp(पूर्णांक dev, काष्ठा snd_card_sb16 *acard,
			     काष्ठा pnp_card_link *card,
			     स्थिर काष्ठा pnp_card_device_id *id)
अणु
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;

	acard->dev = pnp_request_card_device(card, id->devs[0].id, शून्य);
	अगर (acard->dev == शून्य)
		वापस -ENODEV; 

#अगर_घोषित SNDRV_SBAWE_EMU8000
	acard->devwt = pnp_request_card_device(card, id->devs[1].id, acard->dev);
#पूर्ण_अगर
	/* Audio initialization */
	pdev = acard->dev;

	err = pnp_activate_dev(pdev); 
	अगर (err < 0) अणु 
		snd_prपूर्णांकk(KERN_ERR PFX "AUDIO pnp configure failure\n"); 
		वापस err; 
	पूर्ण 
	port[dev] = pnp_port_start(pdev, 0);
	mpu_port[dev] = pnp_port_start(pdev, 1);
	fm_port[dev] = pnp_port_start(pdev, 2);
	dma8[dev] = pnp_dma(pdev, 0);
	dma16[dev] = pnp_dma(pdev, 1);
	irq[dev] = pnp_irq(pdev, 0);
	snd_prपूर्णांकdd("pnp SB16: port=0x%lx, mpu port=0x%lx, fm port=0x%lx\n",
			port[dev], mpu_port[dev], fm_port[dev]);
	snd_prपूर्णांकdd("pnp SB16: dma1=%i, dma2=%i, irq=%i\n",
			dma8[dev], dma16[dev], irq[dev]);
#अगर_घोषित SNDRV_SBAWE_EMU8000
	/* WaveTable initialization */
	pdev = acard->devwt;
	अगर (pdev != शून्य) अणु
		err = pnp_activate_dev(pdev); 
		अगर (err < 0) अणु 
			जाओ __wt_error; 
		पूर्ण 
		awe_port[dev] = pnp_port_start(pdev, 0);
		snd_prपूर्णांकdd("pnp SB16: wavetable port=0x%llx\n",
				(अचिन्हित दीर्घ दीर्घ)pnp_port_start(pdev, 0));
	पूर्ण अन्यथा अणु
__wt_error:
		अगर (pdev) अणु
			pnp_release_card_device(pdev);
			snd_prपूर्णांकk(KERN_ERR PFX "WaveTable pnp configure failure\n");
		पूर्ण
		acard->devwt = शून्य;
		awe_port[dev] = -1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PNP */

अटल व्योम snd_sb16_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_card_sb16 *acard = card->निजी_data;
        
	अगर (acard == शून्य)
		वापस;
	release_and_मुक्त_resource(acard->fm_res);
पूर्ण

#अगर_घोषित CONFIG_PNP
#घोषणा is_isapnp_selected(dev)		isapnp[dev]
#अन्यथा
#घोषणा is_isapnp_selected(dev)		0
#पूर्ण_अगर

अटल पूर्णांक snd_sb16_card_new(काष्ठा device *devptr, पूर्णांक dev,
			     काष्ठा snd_card **cardp)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_card_new(devptr, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_card_sb16), &card);
	अगर (err < 0)
		वापस err;
	card->निजी_मुक्त = snd_sb16_मुक्त;
	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16_probe(काष्ठा snd_card *card, पूर्णांक dev)
अणु
	पूर्णांक xirq, xdma8, xdma16;
	काष्ठा snd_sb *chip;
	काष्ठा snd_card_sb16 *acard = card->निजी_data;
	काष्ठा snd_opl3 *opl3;
	काष्ठा snd_hwdep *synth = शून्य;
#अगर_घोषित CONFIG_SND_SB16_CSP
	काष्ठा snd_hwdep *xcsp = शून्य;
#पूर्ण_अगर
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	xirq = irq[dev];
	xdma8 = dma8[dev];
	xdma16 = dma16[dev];

	अगर ((err = snd_sbdsp_create(card,
				    port[dev],
				    xirq,
				    snd_sb16dsp_पूर्णांकerrupt,
				    xdma8,
				    xdma16,
				    SB_HW_AUTO,
				    &chip)) < 0)
		वापस err;

	acard->chip = chip;
	अगर (chip->hardware != SB_HW_16) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "SB 16 chip was not detected at 0x%lx\n", port[dev]);
		वापस -ENODEV;
	पूर्ण
	chip->mpu_port = mpu_port[dev];
	अगर (! is_isapnp_selected(dev) && (err = snd_sb16dsp_configure(chip)) < 0)
		वापस err;

	अगर ((err = snd_sb16dsp_pcm(chip, 0)) < 0)
		वापस err;

	म_नकल(card->driver,
#अगर_घोषित SNDRV_SBAWE_EMU8000
			awe_port[dev] > 0 ? "SB AWE" :
#पूर्ण_अगर
			"SB16");
	म_नकल(card->लघुname, chip->name);
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i, dma ",
		chip->name,
		chip->port,
		xirq);
	अगर (xdma8 >= 0)
		प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname), "%d", xdma8);
	अगर (xdma16 >= 0)
		प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname), "%s%d",
			xdma8 >= 0 ? "&" : "", xdma16);

	अगर (chip->mpu_port > 0 && chip->mpu_port != SNDRV_AUTO_PORT) अणु
		अगर ((err = snd_mpu401_uart_new(card, 0, MPU401_HW_SB,
					       chip->mpu_port,
					       MPU401_INFO_IRQ_HOOK, -1,
					       &chip->rmidi)) < 0)
			वापस err;
		chip->rmidi_callback = snd_mpu401_uart_पूर्णांकerrupt;
	पूर्ण

#अगर_घोषित SNDRV_SBAWE_EMU8000
	अगर (awe_port[dev] == SNDRV_AUTO_PORT)
		awe_port[dev] = 0; /* disable */
#पूर्ण_अगर

	अगर (fm_port[dev] > 0 && fm_port[dev] != SNDRV_AUTO_PORT) अणु
		अगर (snd_opl3_create(card, fm_port[dev], fm_port[dev] + 2,
				    OPL3_HW_OPL3,
				    acard->fm_res != शून्य || fm_port[dev] == port[dev],
				    &opl3) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "no OPL device at 0x%lx-0x%lx\n",
				   fm_port[dev], fm_port[dev] + 2);
		पूर्ण अन्यथा अणु
#अगर_घोषित SNDRV_SBAWE_EMU8000
			पूर्णांक seqdev = awe_port[dev] > 0 ? 2 : 1;
#अन्यथा
			पूर्णांक seqdev = 1;
#पूर्ण_अगर
			अगर ((err = snd_opl3_hwdep_new(opl3, 0, seqdev, &synth)) < 0)
				वापस err;
		पूर्ण
	पूर्ण

	अगर ((err = snd_sbmixer_new(chip)) < 0)
		वापस err;

#अगर_घोषित CONFIG_SND_SB16_CSP
	/* CSP chip on SB16ASP/AWE32 */
	अगर ((chip->hardware == SB_HW_16) && csp[dev]) अणु
		snd_sb_csp_new(chip, synth != शून्य ? 1 : 0, &xcsp);
		अगर (xcsp) अणु
			chip->csp = xcsp->निजी_data;
			chip->hardware = SB_HW_16CSP;
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकk(KERN_INFO PFX "warning - CSP chip not detected on soundcard #%i\n", dev + 1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित SNDRV_SBAWE_EMU8000
	अगर (awe_port[dev] > 0) अणु
		अगर ((err = snd_emu8000_new(card, 1, awe_port[dev],
					   seq_ports[dev], शून्य)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "fatal error - EMU-8000 synthesizer not detected at 0x%lx\n", awe_port[dev]);

			वापस err;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* setup Mic AGC */
	spin_lock_irqsave(&chip->mixer_lock, flags);
	snd_sbmixer_ग_लिखो(chip, SB_DSP4_MIC_AGC,
		(snd_sbmixer_पढ़ो(chip, SB_DSP4_MIC_AGC) & 0x01) |
		(mic_agc[dev] ? 0x00 : 0x01));
	spin_unlock_irqrestore(&chip->mixer_lock, flags);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0)
		वापस err;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_sb16_suspend(काष्ठा snd_card *card, pm_message_t state)
अणु
	काष्ठा snd_card_sb16 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_sbmixer_suspend(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16_resume(काष्ठा snd_card *card)
अणु
	काष्ठा snd_card_sb16 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_sbdsp_reset(chip);
	snd_sbmixer_resume(chip);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_sb16_isa_probe1(पूर्णांक dev, काष्ठा device *pdev)
अणु
	काष्ठा snd_card_sb16 *acard;
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_sb16_card_new(pdev, dev, &card);
	अगर (err < 0)
		वापस err;

	acard = card->निजी_data;
	/* non-PnP FM port address is hardwired with base port address */
	fm_port[dev] = port[dev];
	/* block the 0x388 port to aव्योम PnP conflicts */
	acard->fm_res = request_region(0x388, 4, "SoundBlaster FM");
#अगर_घोषित SNDRV_SBAWE_EMU8000
	/* non-PnP AWE port address is hardwired with base port address */
	awe_port[dev] = port[dev] + 0x400;
#पूर्ण_अगर

	अगर ((err = snd_sb16_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	dev_set_drvdata(pdev, card);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_sb16_isa_match(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	वापस enable[dev] && !is_isapnp_selected(dev);
पूर्ण

अटल पूर्णांक snd_sb16_isa_probe(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	पूर्णांक err;
	अटल स्थिर पूर्णांक possible_irqs[] = अणु5, 9, 10, 7, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas8[] = अणु1, 3, 0, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas16[] = अणु5, 6, 7, -1पूर्ण;

	अगर (irq[dev] == SNDRV_AUTO_IRQ) अणु
		अगर ((irq[dev] = snd_legacy_find_मुक्त_irq(possible_irqs)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma8[dev] == SNDRV_AUTO_DMA) अणु
		अगर ((dma8[dev] = snd_legacy_find_मुक्त_dma(possible_dmas8)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free 8-bit DMA\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma16[dev] == SNDRV_AUTO_DMA) अणु
		अगर ((dma16[dev] = snd_legacy_find_मुक्त_dma(possible_dmas16)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free 16-bit DMA\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (port[dev] != SNDRV_AUTO_PORT)
		वापस snd_sb16_isa_probe1(dev, pdev);
	अन्यथा अणु
		अटल स्थिर पूर्णांक possible_ports[] = अणु0x220, 0x240, 0x260, 0x280पूर्ण;
		पूर्णांक i;
		क्रम (i = 0; i < ARRAY_SIZE(possible_ports); i++) अणु
			port[dev] = possible_ports[i];
			err = snd_sb16_isa_probe1(dev, pdev);
			अगर (! err)
				वापस 0;
		पूर्ण
		वापस err;
	पूर्ण
पूर्ण

अटल व्योम snd_sb16_isa_हटाओ(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(pdev));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_sb16_isa_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n,
				pm_message_t state)
अणु
	वापस snd_sb16_suspend(dev_get_drvdata(dev), state);
पूर्ण

अटल पूर्णांक snd_sb16_isa_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	वापस snd_sb16_resume(dev_get_drvdata(dev));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित SNDRV_SBAWE
#घोषणा DEV_NAME "sbawe"
#अन्यथा
#घोषणा DEV_NAME "sb16"
#पूर्ण_अगर

अटल काष्ठा isa_driver snd_sb16_isa_driver = अणु
	.match		= snd_sb16_isa_match,
	.probe		= snd_sb16_isa_probe,
	.हटाओ		= snd_sb16_isa_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_sb16_isa_suspend,
	.resume		= snd_sb16_isa_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;


#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_sb16_pnp_detect(काष्ठा pnp_card_link *pcard,
			       स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	पूर्णांक res;

	क्रम ( ; dev < SNDRV_CARDS; dev++) अणु
		अगर (!enable[dev] || !isapnp[dev])
			जारी;
		res = snd_sb16_card_new(&pcard->card->dev, dev, &card);
		अगर (res < 0)
			वापस res;
		अगर ((res = snd_card_sb16_pnp(dev, card->निजी_data, pcard, pid)) < 0 ||
		    (res = snd_sb16_probe(card, dev)) < 0) अणु
			snd_card_मुक्त(card);
			वापस res;
		पूर्ण
		pnp_set_card_drvdata(pcard, card);
		dev++;
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम snd_sb16_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_sb16_pnp_suspend(काष्ठा pnp_card_link *pcard, pm_message_t state)
अणु
	वापस snd_sb16_suspend(pnp_get_card_drvdata(pcard), state);
पूर्ण
अटल पूर्णांक snd_sb16_pnp_resume(काष्ठा pnp_card_link *pcard)
अणु
	वापस snd_sb16_resume(pnp_get_card_drvdata(pcard));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_card_driver sb16_pnpc_driver = अणु
	.flags = PNP_DRIVER_RES_DISABLE,
#अगर_घोषित SNDRV_SBAWE
	.name = "sbawe",
#अन्यथा
	.name = "sb16",
#पूर्ण_अगर
	.id_table = snd_sb16_pnpids,
	.probe = snd_sb16_pnp_detect,
	.हटाओ = snd_sb16_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = snd_sb16_pnp_suspend,
	.resume = snd_sb16_pnp_resume,
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init alsa_card_sb16_init(व्योम)
अणु
	पूर्णांक err;

	err = isa_रेजिस्टर_driver(&snd_sb16_isa_driver, SNDRV_CARDS);
#अगर_घोषित CONFIG_PNP
	अगर (!err)
		isa_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_card_driver(&sb16_pnpc_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;

	अगर (isa_रेजिस्टरed)
		err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_card_sb16_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_card_driver(&sb16_pnpc_driver);
	अगर (isa_रेजिस्टरed)
#पूर्ण_अगर
		isa_unरेजिस्टर_driver(&snd_sb16_isa_driver);
पूर्ण

module_init(alsa_card_sb16_init)
module_निकास(alsa_card_sb16_निकास)
