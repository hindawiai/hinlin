<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Low-level ALSA driver क्रम the ENSONIQ SoundScape
 *   Copyright (c) by Chris Rankin
 *
 *   This driver was written in part using inक्रमmation obtained from
 *   the OSS/Free SoundScape driver, written by Hannu Savolainen.
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/isa.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pnp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/dma.h>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/initval.h>


MODULE_AUTHOR("Chris Rankin");
MODULE_DESCRIPTION("ENSONIQ SoundScape driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("sndscape.co0");
MODULE_FIRMWARE("sndscape.co1");
MODULE_FIRMWARE("sndscape.co2");
MODULE_FIRMWARE("sndscape.co3");
MODULE_FIRMWARE("sndscape.co4");
MODULE_FIRMWARE("scope.cod");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर* id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल दीर्घ wss_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;
अटल पूर्णांक dma[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;
अटल bool joystick[SNDRV_CARDS];

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index number for SoundScape soundcard");

module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "Description for SoundScape card");

module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for SoundScape driver.");

module_param_hw_array(wss_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(wss_port, "WSS Port # for SoundScape driver.");

module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for SoundScape driver.");

module_param_hw_array(mpu_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(mpu_irq, "MPU401 IRQ # for SoundScape driver.");

module_param_hw_array(dma, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma, "DMA # for SoundScape driver.");

module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "DMA2 # for SoundScape driver.");

module_param_array(joystick, bool, शून्य, 0444);
MODULE_PARM_DESC(joystick, "Enable gameport.");

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक isa_रेजिस्टरed;
अटल पूर्णांक pnp_रेजिस्टरed;

अटल स्थिर काष्ठा pnp_card_device_id sscape_pnpids[] = अणु
	अणु .id = "ENS3081", .devs = अणु अणु "ENS0000" पूर्ण पूर्ण पूर्ण, /* Soundscape PnP */
	अणु .id = "ENS4081", .devs = अणु अणु "ENS1011" पूर्ण पूर्ण पूर्ण,	/* VIVO90 */
	अणु .id = "" पूर्ण	/* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, sscape_pnpids);
#पूर्ण_अगर


#घोषणा HOST_CTRL_IO(i)  ((i) + 2)
#घोषणा HOST_DATA_IO(i)  ((i) + 3)
#घोषणा ODIE_ADDR_IO(i)  ((i) + 4)
#घोषणा ODIE_DATA_IO(i)  ((i) + 5)
#घोषणा CODEC_IO(i)      ((i) + 8)

#घोषणा IC_ODIE  1
#घोषणा IC_OPUS  2

#घोषणा RX_READY 0x01
#घोषणा TX_READY 0x02

#घोषणा CMD_ACK			0x80
#घोषणा CMD_SET_MIDI_VOL	0x84
#घोषणा CMD_GET_MIDI_VOL	0x85
#घोषणा CMD_XXX_MIDI_VOL	0x86
#घोषणा CMD_SET_EXTMIDI		0x8a
#घोषणा CMD_GET_EXTMIDI		0x8b
#घोषणा CMD_SET_MT32		0x8c
#घोषणा CMD_GET_MT32		0x8d

क्रमागत GA_REG अणु
	GA_INTSTAT_REG = 0,
	GA_INTENA_REG,
	GA_DMAA_REG,
	GA_DMAB_REG,
	GA_INTCFG_REG,
	GA_DMACFG_REG,
	GA_CDCFG_REG,
	GA_SMCFGA_REG,
	GA_SMCFGB_REG,
	GA_HMCTL_REG
पूर्ण;

#घोषणा DMA_8BIT  0x80


क्रमागत card_type अणु
	MEDIA_FX,	/* Sequoia S-1000 */
	SSCAPE,		/* Sequoia S-2000 */
	SSCAPE_PNP,
	SSCAPE_VIVO,
पूर्ण;

काष्ठा soundscape अणु
	spinlock_t lock;
	अचिन्हित io_base;
	पूर्णांक ic_type;
	क्रमागत card_type type;
	काष्ठा resource *io_res;
	काष्ठा resource *wss_res;
	काष्ठा snd_wss *chip;

	अचिन्हित अक्षर midi_vol;
पूर्ण;

#घोषणा INVALID_IRQ  ((अचिन्हित)-1)


अटल अंतरभूत काष्ठा soundscape *get_card_soundscape(काष्ठा snd_card *c)
अणु
	वापस (काष्ठा soundscape *) (c->निजी_data);
पूर्ण

/*
 * Allocates some kernel memory that we can use क्रम DMA.
 * I think this means that the memory has to map to
 * contiguous pages of physical memory.
 */
अटल काष्ठा snd_dma_buffer *get_dmabuf(काष्ठा soundscape *s,
					 काष्ठा snd_dma_buffer *buf,
					 अचिन्हित दीर्घ size)
अणु
	अगर (buf) अणु
		अगर (snd_dma_alloc_pages_fallback(SNDRV_DMA_TYPE_DEV,
						 s->chip->card->dev,
						 size, buf) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "sscape: Failed to allocate "
					    "%lu bytes for DMA\n",
					    size);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस buf;
पूर्ण

/*
 * Release the DMA-able kernel memory ...
 */
अटल व्योम मुक्त_dmabuf(काष्ठा snd_dma_buffer *buf)
अणु
	अगर (buf && buf->area)
		snd_dma_मुक्त_pages(buf);
पूर्ण

/*
 * This function ग_लिखोs to the SoundScape's control रेजिस्टरs,
 * but करोesn't do any locking. It's up to the caller to करो that.
 * This is why this function is "unsafe" ...
 */
अटल अंतरभूत व्योम sscape_ग_लिखो_unsafe(अचिन्हित io_base, क्रमागत GA_REG reg,
				       अचिन्हित अक्षर val)
अणु
	outb(reg, ODIE_ADDR_IO(io_base));
	outb(val, ODIE_DATA_IO(io_base));
पूर्ण

/*
 * Write to the SoundScape's control रेजिस्टरs, and करो the
 * necessary locking ...
 */
अटल व्योम sscape_ग_लिखो(काष्ठा soundscape *s, क्रमागत GA_REG reg,
			 अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	sscape_ग_लिखो_unsafe(s->io_base, reg, val);
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

/*
 * Read from the SoundScape's control रेजिस्टरs, but leave any
 * locking to the caller. This is why the function is "unsafe" ...
 */
अटल अंतरभूत अचिन्हित अक्षर sscape_पढ़ो_unsafe(अचिन्हित io_base,
					       क्रमागत GA_REG reg)
अणु
	outb(reg, ODIE_ADDR_IO(io_base));
	वापस inb(ODIE_DATA_IO(io_base));
पूर्ण

/*
 * Puts the SoundScape पूर्णांकo "host" mode, as compared to "MIDI" mode
 */
अटल अंतरभूत व्योम set_host_mode_unsafe(अचिन्हित io_base)
अणु
	outb(0x0, HOST_CTRL_IO(io_base));
पूर्ण

/*
 * Puts the SoundScape पूर्णांकo "MIDI" mode, as compared to "host" mode
 */
अटल अंतरभूत व्योम set_midi_mode_unsafe(अचिन्हित io_base)
अणु
	outb(0x3, HOST_CTRL_IO(io_base));
पूर्ण

/*
 * Read the SoundScape's host-mode control रेजिस्टर, but leave
 * any locking issues to the caller ...
 */
अटल अंतरभूत पूर्णांक host_पढ़ो_unsafe(अचिन्हित io_base)
अणु
	पूर्णांक data = -1;
	अगर ((inb(HOST_CTRL_IO(io_base)) & RX_READY) != 0)
		data = inb(HOST_DATA_IO(io_base));

	वापस data;
पूर्ण

/*
 * Read the SoundScape's host-mode control रेजिस्टर, perक्रमming
 * a limited amount of busy-रुकोing अगर the रेजिस्टर isn't पढ़ोy.
 * Also leaves all locking-issues to the caller ...
 */
अटल पूर्णांक host_पढ़ो_ctrl_unsafe(अचिन्हित io_base, अचिन्हित समयout)
अणु
	पूर्णांक data;

	जबतक (((data = host_पढ़ो_unsafe(io_base)) < 0) && (समयout != 0)) अणु
		udelay(100);
		--समयout;
	पूर्ण /* जबतक */

	वापस data;
पूर्ण

/*
 * Write to the SoundScape's host-mode control रेजिस्टरs, but
 * leave any locking issues to the caller ...
 */
अटल अंतरभूत पूर्णांक host_ग_लिखो_unsafe(अचिन्हित io_base, अचिन्हित अक्षर data)
अणु
	अगर ((inb(HOST_CTRL_IO(io_base)) & TX_READY) != 0) अणु
		outb(data, HOST_DATA_IO(io_base));
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write to the SoundScape's host-mode control रेजिस्टरs, perक्रमming
 * a limited amount of busy-रुकोing अगर the रेजिस्टर isn't पढ़ोy.
 * Also leaves all locking-issues to the caller ...
 */
अटल पूर्णांक host_ग_लिखो_ctrl_unsafe(अचिन्हित io_base, अचिन्हित अक्षर data,
				  अचिन्हित समयout)
अणु
	पूर्णांक err;

	जबतक (!(err = host_ग_लिखो_unsafe(io_base, data)) && (समयout != 0)) अणु
		udelay(100);
		--समयout;
	पूर्ण /* जबतक */

	वापस err;
पूर्ण


/*
 * Check that the MIDI subप्रणाली is operational. If it isn't,
 * then we will hang the computer अगर we try to use it ...
 *
 * NOTE: This check is based upon observation, not करोcumentation.
 */
अटल अंतरभूत पूर्णांक verअगरy_mpu401(स्थिर काष्ठा snd_mpu401 *mpu)
अणु
	वापस ((inb(MPU401C(mpu)) & 0xc0) == 0x80);
पूर्ण

/*
 * This is apparently the standard way to initialise an MPU-401
 */
अटल अंतरभूत व्योम initialise_mpu401(स्थिर काष्ठा snd_mpu401 *mpu)
अणु
	outb(0, MPU401D(mpu));
पूर्ण

/*
 * Tell the SoundScape to activate the AD1845 chip (I think).
 * The AD1845 detection fails अगर we *करोn't* करो this, so I
 * think that this is a good idea ...
 */
अटल व्योम activate_ad1845_unsafe(अचिन्हित io_base)
अणु
	अचिन्हित अक्षर val = sscape_पढ़ो_unsafe(io_base, GA_HMCTL_REG);
	sscape_ग_लिखो_unsafe(io_base, GA_HMCTL_REG, (val & 0xcf) | 0x10);
	sscape_ग_लिखो_unsafe(io_base, GA_CDCFG_REG, 0x80);
पूर्ण

/*
 * Do the necessary ALSA-level cleanup to deallocate our driver ...
 */
अटल व्योम soundscape_मुक्त(काष्ठा snd_card *c)
अणु
	काष्ठा soundscape *sscape = get_card_soundscape(c);
	release_and_मुक्त_resource(sscape->io_res);
	release_and_मुक्त_resource(sscape->wss_res);
	मुक्त_dma(sscape->chip->dma1);
पूर्ण

/*
 * Tell the SoundScape to begin a DMA transfer using the given channel.
 * All locking issues are left to the caller.
 */
अटल व्योम sscape_start_dma_unsafe(अचिन्हित io_base, क्रमागत GA_REG reg)
अणु
	sscape_ग_लिखो_unsafe(io_base, reg,
			    sscape_पढ़ो_unsafe(io_base, reg) | 0x01);
	sscape_ग_लिखो_unsafe(io_base, reg,
			    sscape_पढ़ो_unsafe(io_base, reg) & 0xfe);
पूर्ण

/*
 * Wait क्रम a DMA transfer to complete. This is a "limited busy-wait",
 * and all locking issues are left to the caller.
 */
अटल पूर्णांक sscape_रुको_dma_unsafe(अचिन्हित io_base, क्रमागत GA_REG reg,
				  अचिन्हित समयout)
अणु
	जबतक (!(sscape_पढ़ो_unsafe(io_base, reg) & 0x01) && (समयout != 0)) अणु
		udelay(100);
		--समयout;
	पूर्ण /* जबतक */

	वापस sscape_पढ़ो_unsafe(io_base, reg) & 0x01;
पूर्ण

/*
 * Wait क्रम the On-Board Processor to वापस its start-up
 * acknowledgement sequence. This रुको is too दीर्घ क्रम
 * us to perक्रमm "busy-waiting", and so we must sleep.
 * This in turn means that we must not be holding any
 * spinlocks when we call this function.
 */
अटल पूर्णांक obp_startup_ack(काष्ठा soundscape *s, अचिन्हित समयout)
अणु
	अचिन्हित दीर्घ end_समय = jअगरfies + msecs_to_jअगरfies(समयout);

	करो अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक x;

		spin_lock_irqsave(&s->lock, flags);
		x = host_पढ़ो_unsafe(s->io_base);
		spin_unlock_irqrestore(&s->lock, flags);
		अगर (x == 0xfe || x == 0xff)
			वापस 1;

		msleep(10);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));

	वापस 0;
पूर्ण

/*
 * Wait क्रम the host to वापस its start-up acknowledgement
 * sequence. This रुको is too दीर्घ क्रम us to perक्रमm
 * "busy-waiting", and so we must sleep. This in turn means
 * that we must not be holding any spinlocks when we call
 * this function.
 */
अटल पूर्णांक host_startup_ack(काष्ठा soundscape *s, अचिन्हित समयout)
अणु
	अचिन्हित दीर्घ end_समय = jअगरfies + msecs_to_jअगरfies(समयout);

	करो अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक x;

		spin_lock_irqsave(&s->lock, flags);
		x = host_पढ़ो_unsafe(s->io_base);
		spin_unlock_irqrestore(&s->lock, flags);
		अगर (x == 0xfe)
			वापस 1;

		msleep(10);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));

	वापस 0;
पूर्ण

/*
 * Upload a byte-stream पूर्णांकo the SoundScape using DMA channel A.
 */
अटल पूर्णांक upload_dma_data(काष्ठा soundscape *s, स्थिर अचिन्हित अक्षर *data,
			   माप_प्रकार size)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_dma_buffer dma;
	पूर्णांक ret;
	अचिन्हित अक्षर val;

	अगर (!get_dmabuf(s, &dma, PAGE_ALIGN(32 * 1024)))
		वापस -ENOMEM;

	spin_lock_irqsave(&s->lock, flags);

	/*
	 * Reset the board ...
	 */
	val = sscape_पढ़ो_unsafe(s->io_base, GA_HMCTL_REG);
	sscape_ग_लिखो_unsafe(s->io_base, GA_HMCTL_REG, val & 0x3f);

	/*
	 * Enable the DMA channels and configure them ...
	 */
	val = (s->chip->dma1 << 4) | DMA_8BIT;
	sscape_ग_लिखो_unsafe(s->io_base, GA_DMAA_REG, val);
	sscape_ग_लिखो_unsafe(s->io_base, GA_DMAB_REG, 0x20);

	/*
	 * Take the board out of reset ...
	 */
	val = sscape_पढ़ो_unsafe(s->io_base, GA_HMCTL_REG);
	sscape_ग_लिखो_unsafe(s->io_base, GA_HMCTL_REG, val | 0x80);

	/*
	 * Upload the firmware to the SoundScape
	 * board through the DMA channel ...
	 */
	जबतक (size != 0) अणु
		अचिन्हित दीर्घ len;

		len = min(size, dma.bytes);
		स_नकल(dma.area, data, len);
		data += len;
		size -= len;

		snd_dma_program(s->chip->dma1, dma.addr, len, DMA_MODE_WRITE);
		sscape_start_dma_unsafe(s->io_base, GA_DMAA_REG);
		अगर (!sscape_रुको_dma_unsafe(s->io_base, GA_DMAA_REG, 5000)) अणु
			/*
			 * Don't forget to release this spinlock we're holding
			 */
			spin_unlock_irqrestore(&s->lock, flags);

			snd_prपूर्णांकk(KERN_ERR
					"sscape: DMA upload has timed out\n");
			ret = -EAGAIN;
			जाओ _release_dma;
		पूर्ण
	पूर्ण /* जबतक */

	set_host_mode_unsafe(s->io_base);
	outb(0x0, s->io_base);

	/*
	 * Boot the board ... (I think)
	 */
	val = sscape_पढ़ो_unsafe(s->io_base, GA_HMCTL_REG);
	sscape_ग_लिखो_unsafe(s->io_base, GA_HMCTL_REG, val | 0x40);
	spin_unlock_irqrestore(&s->lock, flags);

	/*
	 * If all has gone well, then the board should acknowledge
	 * the new upload and tell us that it has rebooted OK. We
	 * give it 5 seconds (max) ...
	 */
	ret = 0;
	अगर (!obp_startup_ack(s, 5000)) अणु
		snd_prपूर्णांकk(KERN_ERR "sscape: No response "
				    "from on-board processor after upload\n");
		ret = -EAGAIN;
	पूर्ण अन्यथा अगर (!host_startup_ack(s, 5000)) अणु
		snd_prपूर्णांकk(KERN_ERR
				"sscape: SoundScape failed to initialise\n");
		ret = -EAGAIN;
	पूर्ण

_release_dma:
	/*
	 * NOTE!!! We are NOT holding any spinlocks at this poपूर्णांक !!!
	 */
	sscape_ग_लिखो(s, GA_DMAA_REG, (s->ic_type == IC_OPUS ? 0x40 : 0x70));
	मुक्त_dmabuf(&dma);

	वापस ret;
पूर्ण

/*
 * Upload the bootblock(?) पूर्णांकo the SoundScape. The only
 * purpose of this block of code seems to be to tell
 * us which version of the microcode we should be using.
 */
अटल पूर्णांक sscape_upload_bootblock(काष्ठा snd_card *card)
अणु
	काष्ठा soundscape *sscape = get_card_soundscape(card);
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा firmware *init_fw = शून्य;
	पूर्णांक data = 0;
	पूर्णांक ret;

	ret = request_firmware(&init_fw, "scope.cod", card->dev);
	अगर (ret < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sscape: Error loading scope.cod");
		वापस ret;
	पूर्ण
	ret = upload_dma_data(sscape, init_fw->data, init_fw->size);

	release_firmware(init_fw);

	spin_lock_irqsave(&sscape->lock, flags);
	अगर (ret == 0)
		data = host_पढ़ो_ctrl_unsafe(sscape->io_base, 100);

	अगर (data & 0x10)
		sscape_ग_लिखो_unsafe(sscape->io_base, GA_SMCFGA_REG, 0x2f);

	spin_unlock_irqrestore(&sscape->lock, flags);

	data &= 0xf;
	अगर (ret == 0 && data > 7) अणु
		snd_prपूर्णांकk(KERN_ERR
				"sscape: timeout reading firmware version\n");
		ret = -EAGAIN;
	पूर्ण

	वापस (ret == 0) ? data : ret;
पूर्ण

/*
 * Upload the microcode पूर्णांकo the SoundScape.
 */
अटल पूर्णांक sscape_upload_microcode(काष्ठा snd_card *card, पूर्णांक version)
अणु
	काष्ठा soundscape *sscape = get_card_soundscape(card);
	स्थिर काष्ठा firmware *init_fw = शून्य;
	अक्षर name[14];
	पूर्णांक err;

	snम_लिखो(name, माप(name), "sndscape.co%d", version);

	err = request_firmware(&init_fw, name, card->dev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sscape: Error loading sndscape.co%d",
				version);
		वापस err;
	पूर्ण
	err = upload_dma_data(sscape, init_fw->data, init_fw->size);
	अगर (err == 0)
		snd_prपूर्णांकk(KERN_INFO "sscape: MIDI firmware loaded %zu KBs\n",
				init_fw->size >> 10);

	release_firmware(init_fw);

	वापस err;
पूर्ण

/*
 * Mixer control क्रम the SoundScape's MIDI device.
 */
अटल पूर्णांक sscape_midi_info(काष्ठा snd_kcontrol *ctl,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 127;
	वापस 0;
पूर्ण

अटल पूर्णांक sscape_midi_get(काष्ठा snd_kcontrol *kctl,
			   काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kctl);
	काष्ठा snd_card *card = chip->card;
	रेजिस्टर काष्ठा soundscape *s = get_card_soundscape(card);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	uctl->value.पूर्णांकeger.value[0] = s->midi_vol;
	spin_unlock_irqrestore(&s->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक sscape_midi_put(काष्ठा snd_kcontrol *kctl,
			   काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kctl);
	काष्ठा snd_card *card = chip->card;
	काष्ठा soundscape *s = get_card_soundscape(card);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित अक्षर new_val;

	spin_lock_irqsave(&s->lock, flags);

	new_val = uctl->value.पूर्णांकeger.value[0] & 127;
	/*
	 * We need to put the board पूर्णांकo HOST mode beक्रमe we
	 * can send any volume-changing HOST commands ...
	 */
	set_host_mode_unsafe(s->io_base);

	/*
	 * To successfully change the MIDI volume setting, you seem to
	 * have to ग_लिखो a volume command, ग_लिखो the new volume value,
	 * and then perक्रमm another volume-related command. Perhaps the
	 * first command is an "open" and the second command is a "close"?
	 */
	अगर (s->midi_vol == new_val) अणु
		change = 0;
		जाओ __skip_change;
	पूर्ण
	change = host_ग_लिखो_ctrl_unsafe(s->io_base, CMD_SET_MIDI_VOL, 100)
		 && host_ग_लिखो_ctrl_unsafe(s->io_base, new_val, 100)
		 && host_ग_लिखो_ctrl_unsafe(s->io_base, CMD_XXX_MIDI_VOL, 100)
		 && host_ग_लिखो_ctrl_unsafe(s->io_base, new_val, 100);
	s->midi_vol = new_val;
__skip_change:

	/*
	 * Take the board out of HOST mode and back पूर्णांकo MIDI mode ...
	 */
	set_midi_mode_unsafe(s->io_base);

	spin_unlock_irqrestore(&s->lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new midi_mixer_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "MIDI",
	.info = sscape_midi_info,
	.get = sscape_midi_get,
	.put = sscape_midi_put
पूर्ण;

/*
 * The SoundScape can use two IRQs from a possible set of four.
 * These IRQs are encoded as bit patterns so that they can be
 * written to the control रेजिस्टरs.
 */
अटल अचिन्हित get_irq_config(पूर्णांक sscape_type, पूर्णांक irq)
अणु
	अटल स्थिर पूर्णांक valid_irq[] = अणु 9, 5, 7, 10 पूर्ण;
	अटल स्थिर पूर्णांक old_irq[] = अणु 9, 7, 5, 15 पूर्ण;
	अचिन्हित cfg;

	अगर (sscape_type == MEDIA_FX) अणु
		क्रम (cfg = 0; cfg < ARRAY_SIZE(old_irq); ++cfg)
			अगर (irq == old_irq[cfg])
				वापस cfg;
	पूर्ण अन्यथा अणु
		क्रम (cfg = 0; cfg < ARRAY_SIZE(valid_irq); ++cfg)
			अगर (irq == valid_irq[cfg])
				वापस cfg;
	पूर्ण

	वापस INVALID_IRQ;
पूर्ण

/*
 * Perक्रमm certain arcane port-checks to see whether there
 * is a SoundScape board lurking behind the given ports.
 */
अटल पूर्णांक detect_sscape(काष्ठा soundscape *s, दीर्घ wss_io)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित d;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&s->lock, flags);

	/*
	 * The following code is lअगरted from the original OSS driver,
	 * and as I करोn't have a datasheet I cannot really comment
	 * on what it is करोing...
	 */
	अगर ((inb(HOST_CTRL_IO(s->io_base)) & 0x78) != 0)
		जाओ _करोne;

	d = inb(ODIE_ADDR_IO(s->io_base)) & 0xf0;
	अगर ((d & 0x80) != 0)
		जाओ _करोne;

	अगर (d == 0)
		s->ic_type = IC_ODIE;
	अन्यथा अगर ((d & 0x60) != 0)
		s->ic_type = IC_OPUS;
	अन्यथा
		जाओ _करोne;

	outb(0xfa, ODIE_ADDR_IO(s->io_base));
	अगर ((inb(ODIE_ADDR_IO(s->io_base)) & 0x9f) != 0x0a)
		जाओ _करोne;

	outb(0xfe, ODIE_ADDR_IO(s->io_base));
	अगर ((inb(ODIE_ADDR_IO(s->io_base)) & 0x9f) != 0x0e)
		जाओ _करोne;

	outb(0xfe, ODIE_ADDR_IO(s->io_base));
	d = inb(ODIE_DATA_IO(s->io_base));
	अगर (s->type != SSCAPE_VIVO && (d & 0x9f) != 0x0e)
		जाओ _करोne;

	अगर (s->ic_type == IC_OPUS)
		activate_ad1845_unsafe(s->io_base);

	अगर (s->type == SSCAPE_VIVO)
		wss_io += 4;

	d  = sscape_पढ़ो_unsafe(s->io_base, GA_HMCTL_REG);
	sscape_ग_लिखो_unsafe(s->io_base, GA_HMCTL_REG, d | 0xc0);

	/* रुको क्रम WSS codec */
	क्रम (d = 0; d < 500; d++) अणु
		अगर ((inb(wss_io) & 0x80) == 0)
			अवरोध;
		spin_unlock_irqrestore(&s->lock, flags);
		msleep(1);
		spin_lock_irqsave(&s->lock, flags);
	पूर्ण

	अगर ((inb(wss_io) & 0x80) != 0)
		जाओ _करोne;

	अगर (inb(wss_io + 2) == 0xff)
		जाओ _करोne;

	d  = sscape_पढ़ो_unsafe(s->io_base, GA_HMCTL_REG) & 0x3f;
	sscape_ग_लिखो_unsafe(s->io_base, GA_HMCTL_REG, d);

	अगर ((inb(wss_io) & 0x80) != 0)
		s->type = MEDIA_FX;

	d = sscape_पढ़ो_unsafe(s->io_base, GA_HMCTL_REG);
	sscape_ग_लिखो_unsafe(s->io_base, GA_HMCTL_REG, d | 0xc0);
	/* रुको क्रम WSS codec */
	क्रम (d = 0; d < 500; d++) अणु
		अगर ((inb(wss_io) & 0x80) == 0)
			अवरोध;
		spin_unlock_irqrestore(&s->lock, flags);
		msleep(1);
		spin_lock_irqsave(&s->lock, flags);
	पूर्ण

	/*
	 * SoundScape successfully detected!
	 */
	retval = 1;

_करोne:
	spin_unlock_irqrestore(&s->lock, flags);
	वापस retval;
पूर्ण

/*
 * ALSA callback function, called when attempting to खोलो the MIDI device.
 * Check that the MIDI firmware has been loaded, because we करोn't want
 * to crash the machine. Also check that someone isn't using the hardware
 * IOCTL device.
 */
अटल पूर्णांक mpu401_खोलो(काष्ठा snd_mpu401 *mpu)
अणु
	अगर (!verअगरy_mpu401(mpu)) अणु
		snd_prपूर्णांकk(KERN_ERR "sscape: MIDI disabled, "
				    "please load firmware\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Initialise an MPU-401 subdevice क्रम MIDI support on the SoundScape.
 */
अटल पूर्णांक create_mpu401(काष्ठा snd_card *card, पूर्णांक devnum,
			 अचिन्हित दीर्घ port, पूर्णांक irq)
अणु
	काष्ठा soundscape *sscape = get_card_soundscape(card);
	काष्ठा snd_rawmidi *rawmidi;
	पूर्णांक err;

	err = snd_mpu401_uart_new(card, devnum, MPU401_HW_MPU401, port,
				  MPU401_INFO_INTEGRATED, irq, &rawmidi);
	अगर (err == 0) अणु
		काष्ठा snd_mpu401 *mpu = rawmidi->निजी_data;
		mpu->खोलो_input = mpu401_खोलो;
		mpu->खोलो_output = mpu401_खोलो;
		mpu->निजी_data = sscape;

		initialise_mpu401(mpu);
	पूर्ण

	वापस err;
पूर्ण


/*
 * Create an AD1845 PCM subdevice on the SoundScape. The AD1845
 * is very much like a CS4231, with a few extra bits. We will
 * try to support at least some of the extra bits by overriding
 * some of the CS4231 callback.
 */
अटल पूर्णांक create_ad1845(काष्ठा snd_card *card, अचिन्हित port,
			 पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2)
अणु
	रेजिस्टर काष्ठा soundscape *sscape = get_card_soundscape(card);
	काष्ठा snd_wss *chip;
	पूर्णांक err;
	पूर्णांक codec_type = WSS_HW_DETECT;

	चयन (sscape->type) अणु
	हाल MEDIA_FX:
	हाल SSCAPE:
		/*
		 * There are some freak examples of early Soundscape cards
		 * with CS4231 instead of AD1848/CS4248. Unक्रमtunately, the
		 * CS4231 works only in CS4248 compatibility mode on
		 * these cards so क्रमce it.
		 */
		अगर (sscape->ic_type != IC_OPUS)
			codec_type = WSS_HW_AD1848;
		अवरोध;

	हाल SSCAPE_VIVO:
		port += 4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	err = snd_wss_create(card, port, -1, irq, dma1, dma2,
			     codec_type, WSS_HWSHARE_DMA1, &chip);
	अगर (!err) अणु
		अचिन्हित दीर्घ flags;

		अगर (sscape->type != SSCAPE_VIVO) अणु
			/*
			 * The input घड़ी frequency on the SoundScape must
			 * be 14.31818 MHz, because we must set this रेजिस्टर
			 * to get the playback to sound correct ...
			 */
			snd_wss_mce_up(chip);
			spin_lock_irqsave(&chip->reg_lock, flags);
			snd_wss_out(chip, AD1845_CLOCK, 0x20);
			spin_unlock_irqrestore(&chip->reg_lock, flags);
			snd_wss_mce_करोwn(chip);

		पूर्ण

		err = snd_wss_pcm(chip, 0);
		अगर (err < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "sscape: No PCM device "
					    "for AD1845 chip\n");
			जाओ _error;
		पूर्ण

		err = snd_wss_mixer(chip);
		अगर (err < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "sscape: No mixer device "
					    "for AD1845 chip\n");
			जाओ _error;
		पूर्ण
		अगर (chip->hardware != WSS_HW_AD1848) अणु
			err = snd_wss_समयr(chip, 0);
			अगर (err < 0) अणु
				snd_prपूर्णांकk(KERN_ERR "sscape: No timer device "
						    "for AD1845 chip\n");
				जाओ _error;
			पूर्ण
		पूर्ण

		अगर (sscape->type != SSCAPE_VIVO) अणु
			err = snd_ctl_add(card,
					  snd_ctl_new1(&midi_mixer_ctl, chip));
			अगर (err < 0) अणु
				snd_prपूर्णांकk(KERN_ERR "sscape: Could not create "
						    "MIDI mixer control\n");
				जाओ _error;
			पूर्ण
		पूर्ण

		sscape->chip = chip;
	पूर्ण

_error:
	वापस err;
पूर्ण


/*
 * Create an ALSA soundcard entry क्रम the SoundScape, using
 * the given list of port, IRQ and DMA resources.
 */
अटल पूर्णांक create_sscape(पूर्णांक dev, काष्ठा snd_card *card)
अणु
	काष्ठा soundscape *sscape = get_card_soundscape(card);
	अचिन्हित dma_cfg;
	अचिन्हित irq_cfg;
	अचिन्हित mpu_irq_cfg;
	काष्ठा resource *io_res;
	काष्ठा resource *wss_res;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	पूर्णांक val;
	स्थिर अक्षर *name;

	/*
	 * Grab IO ports that we will need to probe so that we
	 * can detect and control this hardware ...
	 */
	io_res = request_region(port[dev], 8, "SoundScape");
	अगर (!io_res) अणु
		snd_prपूर्णांकk(KERN_ERR
			   "sscape: can't grab port 0x%lx\n", port[dev]);
		वापस -EBUSY;
	पूर्ण
	wss_res = शून्य;
	अगर (sscape->type == SSCAPE_VIVO) अणु
		wss_res = request_region(wss_port[dev], 4, "SoundScape");
		अगर (!wss_res) अणु
			snd_prपूर्णांकk(KERN_ERR "sscape: can't grab port 0x%lx\n",
					    wss_port[dev]);
			err = -EBUSY;
			जाओ _release_region;
		पूर्ण
	पूर्ण

	/*
	 * Grab one DMA channel ...
	 */
	err = request_dma(dma[dev], "SoundScape");
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sscape: can't grab DMA %d\n", dma[dev]);
		जाओ _release_region;
	पूर्ण

	spin_lock_init(&sscape->lock);
	sscape->io_res = io_res;
	sscape->wss_res = wss_res;
	sscape->io_base = port[dev];

	अगर (!detect_sscape(sscape, wss_port[dev])) अणु
		prपूर्णांकk(KERN_ERR "sscape: hardware not detected at 0x%x\n",
			sscape->io_base);
		err = -ENODEV;
		जाओ _release_dma;
	पूर्ण

	चयन (sscape->type) अणु
	हाल MEDIA_FX:
		name = "MediaFX/SoundFX";
		अवरोध;
	हाल SSCAPE:
		name = "Soundscape";
		अवरोध;
	हाल SSCAPE_PNP:
		name = "Soundscape PnP";
		अवरोध;
	हाल SSCAPE_VIVO:
		name = "Soundscape VIVO";
		अवरोध;
	शेष:
		name = "unknown Soundscape";
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO "sscape: %s card detected at 0x%x, using IRQ %d, DMA %d\n",
			 name, sscape->io_base, irq[dev], dma[dev]);

	/*
	 * Check that the user didn't pass us garbage data ...
	 */
	irq_cfg = get_irq_config(sscape->type, irq[dev]);
	अगर (irq_cfg == INVALID_IRQ) अणु
		snd_prपूर्णांकk(KERN_ERR "sscape: Invalid IRQ %d\n", irq[dev]);
		err = -ENXIO;
		जाओ _release_dma;
	पूर्ण

	mpu_irq_cfg = get_irq_config(sscape->type, mpu_irq[dev]);
	अगर (mpu_irq_cfg == INVALID_IRQ) अणु
		snd_prपूर्णांकk(KERN_ERR "sscape: Invalid IRQ %d\n", mpu_irq[dev]);
		err = -ENXIO;
		जाओ _release_dma;
	पूर्ण

	/*
	 * Tell the on-board devices where their resources are (I think -
	 * I can't be sure without a datasheet ... So many magic values!)
	 */
	spin_lock_irqsave(&sscape->lock, flags);

	sscape_ग_लिखो_unsafe(sscape->io_base, GA_SMCFGA_REG, 0x2e);
	sscape_ग_लिखो_unsafe(sscape->io_base, GA_SMCFGB_REG, 0x00);

	/*
	 * Enable and configure the DMA channels ...
	 */
	sscape_ग_लिखो_unsafe(sscape->io_base, GA_DMACFG_REG, 0x50);
	dma_cfg = (sscape->ic_type == IC_OPUS ? 0x40 : 0x70);
	sscape_ग_लिखो_unsafe(sscape->io_base, GA_DMAA_REG, dma_cfg);
	sscape_ग_लिखो_unsafe(sscape->io_base, GA_DMAB_REG, 0x20);

	mpu_irq_cfg |= mpu_irq_cfg << 2;
	val = sscape_पढ़ो_unsafe(sscape->io_base, GA_HMCTL_REG) & 0xF7;
	अगर (joystick[dev])
		val |= 8;
	sscape_ग_लिखो_unsafe(sscape->io_base, GA_HMCTL_REG, val | 0x10);
	sscape_ग_लिखो_unsafe(sscape->io_base, GA_INTCFG_REG, 0xf0 | mpu_irq_cfg);
	sscape_ग_लिखो_unsafe(sscape->io_base,
			    GA_CDCFG_REG, 0x09 | DMA_8BIT
			    | (dma[dev] << 4) | (irq_cfg << 1));
	/*
	 * Enable the master IRQ ...
	 */
	sscape_ग_लिखो_unsafe(sscape->io_base, GA_INTENA_REG, 0x80);

	spin_unlock_irqrestore(&sscape->lock, flags);

	/*
	 * We have now enabled the codec chip, and so we should
	 * detect the AD1845 device ...
	 */
	err = create_ad1845(card, wss_port[dev], irq[dev],
			    dma[dev], dma2[dev]);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR
				"sscape: No AD1845 device at 0x%lx, IRQ %d\n",
				wss_port[dev], irq[dev]);
		जाओ _release_dma;
	पूर्ण
	म_नकल(card->driver, "SoundScape");
	म_नकल(card->लघुname, name);
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s at 0x%lx, IRQ %d, DMA1 %d, DMA2 %d\n",
		 name, sscape->chip->port, sscape->chip->irq,
		 sscape->chip->dma1, sscape->chip->dma2);

#घोषणा MIDI_DEVNUM  0
	अगर (sscape->type != SSCAPE_VIVO) अणु
		err = sscape_upload_bootblock(card);
		अगर (err >= 0)
			err = sscape_upload_microcode(card, err);

		अगर (err == 0) अणु
			err = create_mpu401(card, MIDI_DEVNUM, port[dev],
					    mpu_irq[dev]);
			अगर (err < 0) अणु
				snd_prपूर्णांकk(KERN_ERR "sscape: Failed to create "
						"MPU-401 device at 0x%lx\n",
						port[dev]);
				जाओ _release_dma;
			पूर्ण

			/*
			 * Initialize mixer
			 */
			spin_lock_irqsave(&sscape->lock, flags);
			sscape->midi_vol = 0;
			host_ग_लिखो_ctrl_unsafe(sscape->io_base,
						CMD_SET_MIDI_VOL, 100);
			host_ग_लिखो_ctrl_unsafe(sscape->io_base,
						sscape->midi_vol, 100);
			host_ग_लिखो_ctrl_unsafe(sscape->io_base,
						CMD_XXX_MIDI_VOL, 100);
			host_ग_लिखो_ctrl_unsafe(sscape->io_base,
						sscape->midi_vol, 100);
			host_ग_लिखो_ctrl_unsafe(sscape->io_base,
						CMD_SET_EXTMIDI, 100);
			host_ग_लिखो_ctrl_unsafe(sscape->io_base,
						0, 100);
			host_ग_लिखो_ctrl_unsafe(sscape->io_base, CMD_ACK, 100);

			set_midi_mode_unsafe(sscape->io_base);
			spin_unlock_irqrestore(&sscape->lock, flags);
		पूर्ण
	पूर्ण

	/*
	 * Now that we have successfully created this sound card,
	 * it is safe to store the poपूर्णांकer.
	 * NOTE: we only रेजिस्टर the sound card's "destructor"
	 *       function now that our "constructor" has completed.
	 */
	card->निजी_मुक्त = soundscape_मुक्त;

	वापस 0;

_release_dma:
	मुक्त_dma(dma[dev]);

_release_region:
	release_and_मुक्त_resource(wss_res);
	release_and_मुक्त_resource(io_res);

	वापस err;
पूर्ण


अटल पूर्णांक snd_sscape_match(काष्ठा device *pdev, अचिन्हित पूर्णांक i)
अणु
	/*
	 * Make sure we were given ALL of the other parameters.
	 */
	अगर (port[i] == SNDRV_AUTO_PORT)
		वापस 0;

	अगर (irq[i] == SNDRV_AUTO_IRQ ||
	    mpu_irq[i] == SNDRV_AUTO_IRQ ||
	    dma[i] == SNDRV_AUTO_DMA) अणु
		prपूर्णांकk(KERN_INFO
		       "sscape: insufficient parameters, "
		       "need IO, IRQ, MPU-IRQ and DMA\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक snd_sscape_probe(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card;
	काष्ठा soundscape *sscape;
	पूर्णांक ret;

	ret = snd_card_new(pdev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा soundscape), &card);
	अगर (ret < 0)
		वापस ret;

	sscape = get_card_soundscape(card);
	sscape->type = SSCAPE;

	dma[dev] &= 0x03;

	ret = create_sscape(dev, card);
	अगर (ret < 0)
		जाओ _release_card;

	ret = snd_card_रेजिस्टर(card);
	अगर (ret < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sscape: Failed to register sound card\n");
		जाओ _release_card;
	पूर्ण
	dev_set_drvdata(pdev, card);
	वापस 0;

_release_card:
	snd_card_मुक्त(card);
	वापस ret;
पूर्ण

अटल व्योम snd_sscape_हटाओ(काष्ठा device *devptr, अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(devptr));
पूर्ण

#घोषणा DEV_NAME "sscape"

अटल काष्ठा isa_driver snd_sscape_driver = अणु
	.match		= snd_sscape_match,
	.probe		= snd_sscape_probe,
	.हटाओ		= snd_sscape_हटाओ,
	/* FIXME: suspend/resume */
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PNP
अटल अंतरभूत पूर्णांक get_next_स्वतःindex(पूर्णांक i)
अणु
	जबतक (i < SNDRV_CARDS && port[i] != SNDRV_AUTO_PORT)
		++i;
	वापस i;
पूर्ण


अटल पूर्णांक sscape_pnp_detect(काष्ठा pnp_card_link *pcard,
			     स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	अटल पूर्णांक idx = 0;
	काष्ठा pnp_dev *dev;
	काष्ठा snd_card *card;
	काष्ठा soundscape *sscape;
	पूर्णांक ret;

	/*
	 * Allow this function to fail *quietly* अगर all the ISA PnP
	 * devices were configured using module parameters instead.
	 */
	idx = get_next_स्वतःindex(idx);
	अगर (idx >= SNDRV_CARDS)
		वापस -ENOSPC;

	/*
	 * Check that we still have room क्रम another sound card ...
	 */
	dev = pnp_request_card_device(pcard, pid->devs[0].id, शून्य);
	अगर (!dev)
		वापस -ENODEV;

	अगर (!pnp_is_active(dev)) अणु
		अगर (pnp_activate_dev(dev) < 0) अणु
			snd_prपूर्णांकk(KERN_INFO "sscape: device is inactive\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/*
	 * Create a new ALSA sound card entry, in anticipation
	 * of detecting our hardware ...
	 */
	ret = snd_card_new(&pcard->card->dev,
			   index[idx], id[idx], THIS_MODULE,
			   माप(काष्ठा soundscape), &card);
	अगर (ret < 0)
		वापस ret;

	sscape = get_card_soundscape(card);

	/*
	 * Identअगरy card model ...
	 */
	अगर (!म_भेदन("ENS4081", pid->id, 7))
		sscape->type = SSCAPE_VIVO;
	अन्यथा
		sscape->type = SSCAPE_PNP;

	/*
	 * Read the correct parameters off the ISA PnP bus ...
	 */
	port[idx] = pnp_port_start(dev, 0);
	irq[idx] = pnp_irq(dev, 0);
	mpu_irq[idx] = pnp_irq(dev, 1);
	dma[idx] = pnp_dma(dev, 0) & 0x03;
	अगर (sscape->type == SSCAPE_PNP) अणु
		dma2[idx] = dma[idx];
		wss_port[idx] = CODEC_IO(port[idx]);
	पूर्ण अन्यथा अणु
		wss_port[idx] = pnp_port_start(dev, 1);
		dma2[idx] = pnp_dma(dev, 1);
	पूर्ण

	ret = create_sscape(idx, card);
	अगर (ret < 0)
		जाओ _release_card;

	ret = snd_card_रेजिस्टर(card);
	अगर (ret < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "sscape: Failed to register sound card\n");
		जाओ _release_card;
	पूर्ण

	pnp_set_card_drvdata(pcard, card);
	++idx;
	वापस 0;

_release_card:
	snd_card_मुक्त(card);
	वापस ret;
पूर्ण

अटल व्योम sscape_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

अटल काष्ठा pnp_card_driver sscape_pnpc_driver = अणु
	.flags = PNP_DRIVER_RES_DO_NOT_CHANGE,
	.name = "sscape",
	.id_table = sscape_pnpids,
	.probe = sscape_pnp_detect,
	.हटाओ = sscape_pnp_हटाओ,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init sscape_init(व्योम)
अणु
	पूर्णांक err;

	err = isa_रेजिस्टर_driver(&snd_sscape_driver, SNDRV_CARDS);
#अगर_घोषित CONFIG_PNP
	अगर (!err)
		isa_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_card_driver(&sscape_pnpc_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;

	अगर (isa_रेजिस्टरed)
		err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास sscape_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_card_driver(&sscape_pnpc_driver);
	अगर (isa_रेजिस्टरed)
#पूर्ण_अगर
		isa_unरेजिस्टर_driver(&snd_sscape_driver);
पूर्ण

module_init(sscape_init);
module_निकास(sscape_निकास);
