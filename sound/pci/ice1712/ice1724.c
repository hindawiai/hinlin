<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम VT1724 ICEnsemble ICE1724 / VIA VT1724 (Envy24HT)
 *                   VIA VT1720 (Envy24PT)
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 *                    2002 James Stafक्रमd <jstafक्रमd@ampltd.com>
 *                    2003 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/initval.h>

#समावेश <sound/asoundef.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"

/* lowlevel routines */
#समावेश "amp.h"
#समावेश "revo.h"
#समावेश "aureon.h"
#समावेश "vt1720_mobo.h"
#समावेश "pontis.h"
#समावेश "prodigy192.h"
#समावेश "prodigy_hifi.h"
#समावेश "juli.h"
#समावेश "maya44.h"
#समावेश "phase.h"
#समावेश "wtm.h"
#समावेश "se.h"
#समावेश "quartet.h"
#समावेश "psc724.h"

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("VIA ICEnsemble ICE1724/1720 (Envy24HT/PT)");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;		/* Enable this card */
अटल अक्षर *model[SNDRV_CARDS];

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for ICE1724 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for ICE1724 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable ICE1724 soundcard.");
module_param_array(model, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(model, "Use the given board model.");


/* Both VT1720 and VT1724 have the same PCI IDs */
अटल स्थिर काष्ठा pci_device_id snd_vt1724_ids[] = अणु
	अणु PCI_VDEVICE(ICE, PCI_DEVICE_ID_VT1724), 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_vt1724_ids);


अटल पूर्णांक PRO_RATE_LOCKED;
अटल पूर्णांक PRO_RATE_RESET = 1;
अटल अचिन्हित पूर्णांक PRO_RATE_DEFAULT = 44100;

अटल स्थिर अक्षर * स्थिर ext_घड़ी_names[1] = अणु "IEC958 In" पूर्ण;

/*
 *  Basic I/O
 */

/*
 *  शेष rates, शेष घड़ी routines
 */

/* check whether the घड़ी mode is spdअगर-in */
अटल अंतरभूत पूर्णांक stdघड़ी_is_spdअगर_master(काष्ठा snd_ice1712 *ice)
अणु
	वापस (inb(ICEMT1724(ice, RATE)) & VT1724_SPDIF_MASTER) ? 1 : 0;
पूर्ण

/*
 * locking rate makes sense only क्रम पूर्णांकernal घड़ी mode
 */
अटल अंतरभूत पूर्णांक is_pro_rate_locked(काष्ठा snd_ice1712 *ice)
अणु
	वापस (!ice->is_spdअगर_master(ice)) && PRO_RATE_LOCKED;
पूर्ण

/*
 * ac97 section
 */

अटल अचिन्हित अक्षर snd_vt1724_ac97_पढ़ोy(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित अक्षर old_cmd;
	पूर्णांक पंचांग;
	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++) अणु
		old_cmd = inb(ICEMT1724(ice, AC97_CMD));
		अगर (old_cmd & (VT1724_AC97_WRITE | VT1724_AC97_READ))
			जारी;
		अगर (!(old_cmd & VT1724_AC97_READY))
			जारी;
		वापस old_cmd;
	पूर्ण
	dev_dbg(ice->card->dev, "snd_vt1724_ac97_ready: timeout\n");
	वापस old_cmd;
पूर्ण

अटल पूर्णांक snd_vt1724_ac97_रुको_bit(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर bit)
अणु
	पूर्णांक पंचांग;
	क्रम (पंचांग = 0; पंचांग < 0x10000; पंचांग++)
		अगर ((inb(ICEMT1724(ice, AC97_CMD)) & bit) == 0)
			वापस 0;
	dev_dbg(ice->card->dev, "snd_vt1724_ac97_wait_bit: timeout\n");
	वापस -EIO;
पूर्ण

अटल व्योम snd_vt1724_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
				  अचिन्हित लघु reg,
				  अचिन्हित लघु val)
अणु
	काष्ठा snd_ice1712 *ice = ac97->निजी_data;
	अचिन्हित अक्षर old_cmd;

	old_cmd = snd_vt1724_ac97_पढ़ोy(ice);
	old_cmd &= ~VT1724_AC97_ID_MASK;
	old_cmd |= ac97->num;
	outb(reg, ICEMT1724(ice, AC97_INDEX));
	outw(val, ICEMT1724(ice, AC97_DATA));
	outb(old_cmd | VT1724_AC97_WRITE, ICEMT1724(ice, AC97_CMD));
	snd_vt1724_ac97_रुको_bit(ice, VT1724_AC97_WRITE);
पूर्ण

अटल अचिन्हित लघु snd_vt1724_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा snd_ice1712 *ice = ac97->निजी_data;
	अचिन्हित अक्षर old_cmd;

	old_cmd = snd_vt1724_ac97_पढ़ोy(ice);
	old_cmd &= ~VT1724_AC97_ID_MASK;
	old_cmd |= ac97->num;
	outb(reg, ICEMT1724(ice, AC97_INDEX));
	outb(old_cmd | VT1724_AC97_READ, ICEMT1724(ice, AC97_CMD));
	अगर (snd_vt1724_ac97_रुको_bit(ice, VT1724_AC97_READ) < 0)
		वापस ~0;
	वापस inw(ICEMT1724(ice, AC97_DATA));
पूर्ण


/*
 * GPIO operations
 */

/* set gpio direction 0 = पढ़ो, 1 = ग_लिखो */
अटल व्योम snd_vt1724_set_gpio_dir(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data)
अणु
	outl(data, ICEREG1724(ice, GPIO_सूचीECTION));
	inw(ICEREG1724(ice, GPIO_सूचीECTION)); /* dummy पढ़ो क्रम pci-posting */
पूर्ण

/* get gpio direction 0 = पढ़ो, 1 = ग_लिखो */
अटल अचिन्हित पूर्णांक snd_vt1724_get_gpio_dir(काष्ठा snd_ice1712 *ice)
अणु
	वापस inl(ICEREG1724(ice, GPIO_सूचीECTION));
पूर्ण

/* set the gpio mask (0 = writable) */
अटल व्योम snd_vt1724_set_gpio_mask(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data)
अणु
	outw(data, ICEREG1724(ice, GPIO_WRITE_MASK));
	अगर (!ice->vt1720) /* VT1720 supports only 16 GPIO bits */
		outb((data >> 16) & 0xff, ICEREG1724(ice, GPIO_WRITE_MASK_22));
	inw(ICEREG1724(ice, GPIO_WRITE_MASK)); /* dummy पढ़ो क्रम pci-posting */
पूर्ण

अटल अचिन्हित पूर्णांक snd_vt1724_get_gpio_mask(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक mask;
	अगर (!ice->vt1720)
		mask = (अचिन्हित पूर्णांक)inb(ICEREG1724(ice, GPIO_WRITE_MASK_22));
	अन्यथा
		mask = 0;
	mask = (mask << 16) | inw(ICEREG1724(ice, GPIO_WRITE_MASK));
	वापस mask;
पूर्ण

अटल व्योम snd_vt1724_set_gpio_data(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data)
अणु
	outw(data, ICEREG1724(ice, GPIO_DATA));
	अगर (!ice->vt1720)
		outb(data >> 16, ICEREG1724(ice, GPIO_DATA_22));
	inw(ICEREG1724(ice, GPIO_DATA)); /* dummy पढ़ो क्रम pci-posting */
पूर्ण

अटल अचिन्हित पूर्णांक snd_vt1724_get_gpio_data(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक data;
	अगर (!ice->vt1720)
		data = (अचिन्हित पूर्णांक)inb(ICEREG1724(ice, GPIO_DATA_22));
	अन्यथा
		data = 0;
	data = (data << 16) | inw(ICEREG1724(ice, GPIO_DATA));
	वापस data;
पूर्ण

/*
 * MIDI
 */

अटल व्योम vt1724_midi_clear_rx(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक count;

	क्रम (count = inb(ICEREG1724(ice, MPU_RXFIFO)); count > 0; --count)
		inb(ICEREG1724(ice, MPU_DATA));
पूर्ण

अटल अंतरभूत काष्ठा snd_rawmidi_substream *
get_rawmidi_substream(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक stream)
अणु
	वापस list_first_entry(&ice->rmidi[0]->streams[stream].substreams,
				काष्ठा snd_rawmidi_substream, list);
पूर्ण

अटल व्योम enable_midi_irq(काष्ठा snd_ice1712 *ice, u8 flag, पूर्णांक enable);

अटल व्योम vt1724_midi_ग_लिखो(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा snd_rawmidi_substream *s;
	पूर्णांक count, i;
	u8 buffer[32];

	s = get_rawmidi_substream(ice, SNDRV_RAWMIDI_STREAM_OUTPUT);
	count = 31 - inb(ICEREG1724(ice, MPU_TXFIFO));
	अगर (count > 0) अणु
		count = snd_rawmidi_transmit(s, buffer, count);
		क्रम (i = 0; i < count; ++i)
			outb(buffer[i], ICEREG1724(ice, MPU_DATA));
	पूर्ण
	/* mask irq when all bytes have been transmitted.
	 * enabled again in output_trigger when the new data comes in.
	 */
	enable_midi_irq(ice, VT1724_IRQ_MPU_TX,
			!snd_rawmidi_transmit_empty(s));
पूर्ण

अटल व्योम vt1724_midi_पढ़ो(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा snd_rawmidi_substream *s;
	पूर्णांक count, i;
	u8 buffer[32];

	s = get_rawmidi_substream(ice, SNDRV_RAWMIDI_STREAM_INPUT);
	count = inb(ICEREG1724(ice, MPU_RXFIFO));
	अगर (count > 0) अणु
		count = min(count, 32);
		क्रम (i = 0; i < count; ++i)
			buffer[i] = inb(ICEREG1724(ice, MPU_DATA));
		snd_rawmidi_receive(s, buffer, count);
	पूर्ण
पूर्ण

/* call with ice->reg_lock */
अटल व्योम enable_midi_irq(काष्ठा snd_ice1712 *ice, u8 flag, पूर्णांक enable)
अणु
	u8 mask = inb(ICEREG1724(ice, IRQMASK));
	अगर (enable)
		mask &= ~flag;
	अन्यथा
		mask |= flag;
	outb(mask, ICEREG1724(ice, IRQMASK));
पूर्ण

अटल व्योम vt1724_enable_midi_irq(काष्ठा snd_rawmidi_substream *substream,
				   u8 flag, पूर्णांक enable)
अणु
	काष्ठा snd_ice1712 *ice = substream->rmidi->निजी_data;

	spin_lock_irq(&ice->reg_lock);
	enable_midi_irq(ice, flag, enable);
	spin_unlock_irq(&ice->reg_lock);
पूर्ण

अटल पूर्णांक vt1724_midi_output_खोलो(काष्ठा snd_rawmidi_substream *s)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vt1724_midi_output_बंद(काष्ठा snd_rawmidi_substream *s)
अणु
	वापस 0;
पूर्ण

अटल व्योम vt1724_midi_output_trigger(काष्ठा snd_rawmidi_substream *s, पूर्णांक up)
अणु
	काष्ठा snd_ice1712 *ice = s->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ice->reg_lock, flags);
	अगर (up) अणु
		ice->midi_output = 1;
		vt1724_midi_ग_लिखो(ice);
	पूर्ण अन्यथा अणु
		ice->midi_output = 0;
		enable_midi_irq(ice, VT1724_IRQ_MPU_TX, 0);
	पूर्ण
	spin_unlock_irqrestore(&ice->reg_lock, flags);
पूर्ण

अटल व्योम vt1724_midi_output_drain(काष्ठा snd_rawmidi_substream *s)
अणु
	काष्ठा snd_ice1712 *ice = s->rmidi->निजी_data;
	अचिन्हित दीर्घ समयout;

	vt1724_enable_midi_irq(s, VT1724_IRQ_MPU_TX, 0);
	/* 32 bytes should be transmitted in less than about 12 ms */
	समयout = jअगरfies + msecs_to_jअगरfies(15);
	करो अणु
		अगर (inb(ICEREG1724(ice, MPU_CTRL)) & VT1724_MPU_TX_EMPTY)
			अवरोध;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_after(समयout, jअगरfies));
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops vt1724_midi_output_ops = अणु
	.खोलो = vt1724_midi_output_खोलो,
	.बंद = vt1724_midi_output_बंद,
	.trigger = vt1724_midi_output_trigger,
	.drain = vt1724_midi_output_drain,
पूर्ण;

अटल पूर्णांक vt1724_midi_input_खोलो(काष्ठा snd_rawmidi_substream *s)
अणु
	vt1724_midi_clear_rx(s->rmidi->निजी_data);
	vt1724_enable_midi_irq(s, VT1724_IRQ_MPU_RX, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक vt1724_midi_input_बंद(काष्ठा snd_rawmidi_substream *s)
अणु
	vt1724_enable_midi_irq(s, VT1724_IRQ_MPU_RX, 0);
	वापस 0;
पूर्ण

अटल व्योम vt1724_midi_input_trigger(काष्ठा snd_rawmidi_substream *s, पूर्णांक up)
अणु
	काष्ठा snd_ice1712 *ice = s->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ice->reg_lock, flags);
	अगर (up) अणु
		ice->midi_input = 1;
		vt1724_midi_पढ़ो(ice);
	पूर्ण अन्यथा अणु
		ice->midi_input = 0;
	पूर्ण
	spin_unlock_irqrestore(&ice->reg_lock, flags);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops vt1724_midi_input_ops = अणु
	.खोलो = vt1724_midi_input_खोलो,
	.बंद = vt1724_midi_input_बंद,
	.trigger = vt1724_midi_input_trigger,
पूर्ण;


/*
 *  Interrupt handler
 */

अटल irqवापस_t snd_vt1724_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_ice1712 *ice = dev_id;
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर status_mask =
		VT1724_IRQ_MPU_RX | VT1724_IRQ_MPU_TX | VT1724_IRQ_MTPCM;
	पूर्णांक handled = 0;
	पूर्णांक समयout = 0;

	जबतक (1) अणु
		status = inb(ICEREG1724(ice, IRQSTAT));
		status &= status_mask;
		अगर (status == 0)
			अवरोध;
		spin_lock(&ice->reg_lock);
		अगर (++समयout > 10) अणु
			status = inb(ICEREG1724(ice, IRQSTAT));
			dev_err(ice->card->dev,
				"Too long irq loop, status = 0x%x\n", status);
			अगर (status & VT1724_IRQ_MPU_TX) अणु
				dev_err(ice->card->dev, "Disabling MPU_TX\n");
				enable_midi_irq(ice, VT1724_IRQ_MPU_TX, 0);
			पूर्ण
			spin_unlock(&ice->reg_lock);
			अवरोध;
		पूर्ण
		handled = 1;
		अगर (status & VT1724_IRQ_MPU_TX) अणु
			अगर (ice->midi_output)
				vt1724_midi_ग_लिखो(ice);
			अन्यथा
				enable_midi_irq(ice, VT1724_IRQ_MPU_TX, 0);
			/* Due to mysterical reasons, MPU_TX is always
			 * generated (and can't be cleared) when a PCM
			 * playback is going.  So let's ignore at the
			 * next loop.
			 */
			status_mask &= ~VT1724_IRQ_MPU_TX;
		पूर्ण
		अगर (status & VT1724_IRQ_MPU_RX) अणु
			अगर (ice->midi_input)
				vt1724_midi_पढ़ो(ice);
			अन्यथा
				vt1724_midi_clear_rx(ice);
		पूर्ण
		/* ack MPU irq */
		outb(status, ICEREG1724(ice, IRQSTAT));
		spin_unlock(&ice->reg_lock);
		अगर (status & VT1724_IRQ_MTPCM) अणु
			/*
			 * Multi-track PCM
			 * PCM assignment are:
			 * Playback DMA0 (M/C) = playback_pro_substream
			 * Playback DMA1 = playback_con_substream_ds[0]
			 * Playback DMA2 = playback_con_substream_ds[1]
			 * Playback DMA3 = playback_con_substream_ds[2]
			 * Playback DMA4 (SPDIF) = playback_con_substream
			 * Record DMA0 = capture_pro_substream
			 * Record DMA1 = capture_con_substream
			 */
			अचिन्हित अक्षर mtstat = inb(ICEMT1724(ice, IRQ));
			अगर (mtstat & VT1724_MULTI_PDMA0) अणु
				अगर (ice->playback_pro_substream)
					snd_pcm_period_elapsed(ice->playback_pro_substream);
			पूर्ण
			अगर (mtstat & VT1724_MULTI_RDMA0) अणु
				अगर (ice->capture_pro_substream)
					snd_pcm_period_elapsed(ice->capture_pro_substream);
			पूर्ण
			अगर (mtstat & VT1724_MULTI_PDMA1) अणु
				अगर (ice->playback_con_substream_ds[0])
					snd_pcm_period_elapsed(ice->playback_con_substream_ds[0]);
			पूर्ण
			अगर (mtstat & VT1724_MULTI_PDMA2) अणु
				अगर (ice->playback_con_substream_ds[1])
					snd_pcm_period_elapsed(ice->playback_con_substream_ds[1]);
			पूर्ण
			अगर (mtstat & VT1724_MULTI_PDMA3) अणु
				अगर (ice->playback_con_substream_ds[2])
					snd_pcm_period_elapsed(ice->playback_con_substream_ds[2]);
			पूर्ण
			अगर (mtstat & VT1724_MULTI_PDMA4) अणु
				अगर (ice->playback_con_substream)
					snd_pcm_period_elapsed(ice->playback_con_substream);
			पूर्ण
			अगर (mtstat & VT1724_MULTI_RDMA1) अणु
				अगर (ice->capture_con_substream)
					snd_pcm_period_elapsed(ice->capture_con_substream);
			पूर्ण
			/* ack anyway to aव्योम मुक्तze */
			outb(mtstat, ICEMT1724(ice, IRQ));
			/* ought to really handle this properly */
			अगर (mtstat & VT1724_MULTI_FIFO_ERR) अणु
				अचिन्हित अक्षर ख_स्थिति = inb(ICEMT1724(ice, DMA_FIFO_ERR));
				outb(ख_स्थिति, ICEMT1724(ice, DMA_FIFO_ERR));
				outb(VT1724_MULTI_FIFO_ERR | inb(ICEMT1724(ice, DMA_INT_MASK)), ICEMT1724(ice, DMA_INT_MASK));
				/* If I करोn't करो this, I get machine lockup due to continual पूर्णांकerrupts */
			पूर्ण

		पूर्ण
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण

/*
 *  PCM code - professional part (multitrack)
 */

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	8000, 9600, 11025, 12000, 16000, 22050, 24000,
	32000, 44100, 48000, 64000, 88200, 96000,
	176400, 192000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates_96 = अणु
	.count = ARRAY_SIZE(rates) - 2, /* up to 96000 */
	.list = rates,
	.mask = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates_48 = अणु
	.count = ARRAY_SIZE(rates) - 5, /* up to 48000 */
	.list = rates,
	.mask = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates_192 = अणु
	.count = ARRAY_SIZE(rates),
	.list = rates,
	.mask = 0,
पूर्ण;

काष्ठा vt1724_pcm_reg अणु
	अचिन्हित पूर्णांक addr;	/* ADDR रेजिस्टर offset */
	अचिन्हित पूर्णांक size;	/* SIZE रेजिस्टर offset */
	अचिन्हित पूर्णांक count;	/* COUNT रेजिस्टर offset */
	अचिन्हित पूर्णांक start;	/* start & छोड़ो bit */
पूर्ण;

अटल पूर्णांक snd_vt1724_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	अचिन्हित अक्षर what;
	अचिन्हित अक्षर old;
	काष्ठा snd_pcm_substream *s;

	what = 0;
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (snd_pcm_substream_chip(s) == ice) अणु
			स्थिर काष्ठा vt1724_pcm_reg *reg;
			reg = s->runसमय->निजी_data;
			what |= reg->start;
			snd_pcm_trigger_करोne(s, substream);
		पूर्ण
	पूर्ण

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		spin_lock(&ice->reg_lock);
		old = inb(ICEMT1724(ice, DMA_PAUSE));
		अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_PUSH)
			old |= what;
		अन्यथा
			old &= ~what;
		outb(old, ICEMT1724(ice, DMA_PAUSE));
		spin_unlock(&ice->reg_lock);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		spin_lock(&ice->reg_lock);
		old = inb(ICEMT1724(ice, DMA_CONTROL));
		अगर (cmd == SNDRV_PCM_TRIGGER_START)
			old |= what;
		अन्यथा
			old &= ~what;
		outb(old, ICEMT1724(ice, DMA_CONTROL));
		spin_unlock(&ice->reg_lock);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
		/* apps will have to restart stream */
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 */

#घोषणा DMA_STARTS	(VT1724_RDMA0_START|VT1724_PDMA0_START|VT1724_RDMA1_START|\
	VT1724_PDMA1_START|VT1724_PDMA2_START|VT1724_PDMA3_START|VT1724_PDMA4_START)
#घोषणा DMA_PAUSES	(VT1724_RDMA0_PAUSE|VT1724_PDMA0_PAUSE|VT1724_RDMA1_PAUSE|\
	VT1724_PDMA1_PAUSE|VT1724_PDMA2_PAUSE|VT1724_PDMA3_PAUSE|VT1724_PDMA4_PAUSE)

अटल स्थिर अचिन्हित पूर्णांक stdघड़ी_rate_list[16] = अणु
	48000, 24000, 12000, 9600, 32000, 16000, 8000, 96000, 44100,
	22050, 11025, 88200, 176400, 0, 192000, 64000
पूर्ण;

अटल अचिन्हित पूर्णांक stdघड़ी_get_rate(काष्ठा snd_ice1712 *ice)
अणु
	वापस stdघड़ी_rate_list[inb(ICEMT1724(ice, RATE)) & 15];
पूर्ण

अटल व्योम stdघड़ी_set_rate(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(stdघड़ी_rate_list); i++) अणु
		अगर (stdघड़ी_rate_list[i] == rate) अणु
			outb(i, ICEMT1724(ice, RATE));
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित अक्षर stdघड़ी_set_mclk(काष्ठा snd_ice1712 *ice,
				       अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर val, old;
	/* check MT02 */
	अगर (ice->eeprom.data[ICE_EEP2_ACLINK] & VT1724_CFG_PRO_I2S) अणु
		val = old = inb(ICEMT1724(ice, I2S_FORMAT));
		अगर (rate > 96000)
			val |= VT1724_MT_I2S_MCLK_128X; /* 128x MCLK */
		अन्यथा
			val &= ~VT1724_MT_I2S_MCLK_128X; /* 256x MCLK */
		अगर (val != old) अणु
			outb(val, ICEMT1724(ice, I2S_FORMAT));
			/* master घड़ी changed */
			वापस 1;
		पूर्ण
	पूर्ण
	/* no change in master घड़ी */
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_set_pro_rate(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate,
				    पूर्णांक क्रमce)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर mclk_change;
	अचिन्हित पूर्णांक i, old_rate;
	bool call_set_rate = false;

	अगर (rate > ice->hw_rates->list[ice->hw_rates->count - 1])
		वापस -EINVAL;

	spin_lock_irqsave(&ice->reg_lock, flags);
	अगर ((inb(ICEMT1724(ice, DMA_CONTROL)) & DMA_STARTS) ||
	    (inb(ICEMT1724(ice, DMA_PAUSE)) & DMA_PAUSES)) अणु
		/* running? we cannot change the rate now... */
		spin_unlock_irqrestore(&ice->reg_lock, flags);
		वापस ((rate == ice->cur_rate) && !क्रमce) ? 0 : -EBUSY;
	पूर्ण
	अगर (!क्रमce && is_pro_rate_locked(ice)) अणु
		/* comparing required and current rate - makes sense क्रम
		 * पूर्णांकernal घड़ी only */
		spin_unlock_irqrestore(&ice->reg_lock, flags);
		वापस (rate == ice->cur_rate) ? 0 : -EBUSY;
	पूर्ण

	अगर (क्रमce || !ice->is_spdअगर_master(ice)) अणु
		/* क्रमce means the rate was चयनed by ucontrol, otherwise
		 * setting घड़ी rate क्रम पूर्णांकernal घड़ी mode */
		old_rate = ice->get_rate(ice);
		अगर (क्रमce || (old_rate != rate))
			call_set_rate = true;
		अन्यथा अगर (rate == ice->cur_rate) अणु
			spin_unlock_irqrestore(&ice->reg_lock, flags);
			वापस 0;
		पूर्ण
	पूर्ण

	ice->cur_rate = rate;
	spin_unlock_irqrestore(&ice->reg_lock, flags);

	अगर (call_set_rate)
		ice->set_rate(ice, rate);

	/* setting master घड़ी */
	mclk_change = ice->set_mclk(ice, rate);

	अगर (mclk_change && ice->gpio.i2s_mclk_changed)
		ice->gpio.i2s_mclk_changed(ice);
	अगर (ice->gpio.set_pro_rate)
		ice->gpio.set_pro_rate(ice, rate);

	/* set up codecs */
	क्रम (i = 0; i < ice->akm_codecs; i++) अणु
		अगर (ice->akm[i].ops.set_rate_val)
			ice->akm[i].ops.set_rate_val(&ice->akm[i], rate);
	पूर्ण
	अगर (ice->spdअगर.ops.setup_rate)
		ice->spdअगर.ops.setup_rate(ice, rate);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	पूर्णांक i, chs;

	chs = params_channels(hw_params);
	mutex_lock(&ice->खोलो_mutex);
	/* mark surround channels */
	अगर (substream == ice->playback_pro_substream) अणु
		/* PDMA0 can be multi-channel up to 8 */
		chs = chs / 2 - 1;
		क्रम (i = 0; i < chs; i++) अणु
			अगर (ice->pcm_reserved[i] &&
			    ice->pcm_reserved[i] != substream) अणु
				mutex_unlock(&ice->खोलो_mutex);
				वापस -EBUSY;
			पूर्ण
			ice->pcm_reserved[i] = substream;
		पूर्ण
		क्रम (; i < 3; i++) अणु
			अगर (ice->pcm_reserved[i] == substream)
				ice->pcm_reserved[i] = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 3; i++) अणु
			/* check inभागidual playback stream */
			अगर (ice->playback_con_substream_ds[i] == substream) अणु
				अगर (ice->pcm_reserved[i] &&
				    ice->pcm_reserved[i] != substream) अणु
					mutex_unlock(&ice->खोलो_mutex);
					वापस -EBUSY;
				पूर्ण
				ice->pcm_reserved[i] = substream;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&ice->खोलो_mutex);

	वापस snd_vt1724_set_pro_rate(ice, params_rate(hw_params), 0);
पूर्ण

अटल पूर्णांक snd_vt1724_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	पूर्णांक i;

	mutex_lock(&ice->खोलो_mutex);
	/* unmark surround channels */
	क्रम (i = 0; i < 3; i++)
		अगर (ice->pcm_reserved[i] == substream)
			ice->pcm_reserved[i] = शून्य;
	mutex_unlock(&ice->खोलो_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_playback_pro_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	अचिन्हित अक्षर val;
	अचिन्हित पूर्णांक size;

	spin_lock_irq(&ice->reg_lock);
	val = (8 - substream->runसमय->channels) >> 1;
	outb(val, ICEMT1724(ice, BURST));

	outl(substream->runसमय->dma_addr, ICEMT1724(ice, PLAYBACK_ADDR));

	size = (snd_pcm_lib_buffer_bytes(substream) >> 2) - 1;
	/* outl(size, ICEMT1724(ice, PLAYBACK_SIZE)); */
	outw(size, ICEMT1724(ice, PLAYBACK_SIZE));
	outb(size >> 16, ICEMT1724(ice, PLAYBACK_SIZE) + 2);
	size = (snd_pcm_lib_period_bytes(substream) >> 2) - 1;
	/* outl(size, ICEMT1724(ice, PLAYBACK_COUNT)); */
	outw(size, ICEMT1724(ice, PLAYBACK_COUNT));
	outb(size >> 16, ICEMT1724(ice, PLAYBACK_COUNT) + 2);

	spin_unlock_irq(&ice->reg_lock);

	/*
	dev_dbg(ice->card->dev, "pro prepare: ch = %d, addr = 0x%x, "
	       "buffer = 0x%x, period = 0x%x\n",
	       substream->runसमय->channels,
	       (अचिन्हित पूर्णांक)substream->runसमय->dma_addr,
	       snd_pcm_lib_buffer_bytes(substream),
	       snd_pcm_lib_period_bytes(substream));
	*/
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_vt1724_playback_pro_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(inl(ICEMT1724(ice, DMA_CONTROL)) & VT1724_PDMA0_START))
		वापस 0;
#अगर 0 /* पढ़ो PLAYBACK_ADDR */
	ptr = inl(ICEMT1724(ice, PLAYBACK_ADDR));
	अगर (ptr < substream->runसमय->dma_addr) अणु
		dev_dbg(ice->card->dev, "invalid negative ptr\n");
		वापस 0;
	पूर्ण
	ptr -= substream->runसमय->dma_addr;
	ptr = bytes_to_frames(substream->runसमय, ptr);
	अगर (ptr >= substream->runसमय->buffer_size) अणु
		dev_dbg(ice->card->dev, "invalid ptr %d (size=%d)\n",
			   (पूर्णांक)ptr, (पूर्णांक)substream->runसमय->period_size);
		वापस 0;
	पूर्ण
#अन्यथा /* पढ़ो PLAYBACK_SIZE */
	ptr = inl(ICEMT1724(ice, PLAYBACK_SIZE)) & 0xffffff;
	ptr = (ptr + 1) << 2;
	ptr = bytes_to_frames(substream->runसमय, ptr);
	अगर (!ptr)
		;
	अन्यथा अगर (ptr <= substream->runसमय->buffer_size)
		ptr = substream->runसमय->buffer_size - ptr;
	अन्यथा अणु
		dev_dbg(ice->card->dev, "invalid ptr %d (size=%d)\n",
			   (पूर्णांक)ptr, (पूर्णांक)substream->runसमय->buffer_size);
		ptr = 0;
	पूर्ण
#पूर्ण_अगर
	वापस ptr;
पूर्ण

अटल पूर्णांक snd_vt1724_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	स्थिर काष्ठा vt1724_pcm_reg *reg = substream->runसमय->निजी_data;

	spin_lock_irq(&ice->reg_lock);
	outl(substream->runसमय->dma_addr, ice->profi_port + reg->addr);
	outw((snd_pcm_lib_buffer_bytes(substream) >> 2) - 1,
	     ice->profi_port + reg->size);
	outw((snd_pcm_lib_period_bytes(substream) >> 2) - 1,
	     ice->profi_port + reg->count);
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_vt1724_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	स्थिर काष्ठा vt1724_pcm_reg *reg = substream->runसमय->निजी_data;
	माप_प्रकार ptr;

	अगर (!(inl(ICEMT1724(ice, DMA_CONTROL)) & reg->start))
		वापस 0;
#अगर 0 /* use ADDR रेजिस्टर */
	ptr = inl(ice->profi_port + reg->addr);
	ptr -= substream->runसमय->dma_addr;
	वापस bytes_to_frames(substream->runसमय, ptr);
#अन्यथा /* use SIZE रेजिस्टर */
	ptr = inw(ice->profi_port + reg->size);
	ptr = (ptr + 1) << 2;
	ptr = bytes_to_frames(substream->runसमय, ptr);
	अगर (!ptr)
		;
	अन्यथा अगर (ptr <= substream->runसमय->buffer_size)
		ptr = substream->runसमय->buffer_size - ptr;
	अन्यथा अणु
		dev_dbg(ice->card->dev, "invalid ptr %d (size=%d)\n",
			   (पूर्णांक)ptr, (पूर्णांक)substream->runसमय->buffer_size);
		ptr = 0;
	पूर्ण
	वापस ptr;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा vt1724_pcm_reg vt1724_pdma0_reg = अणु
	.addr = VT1724_MT_PLAYBACK_ADDR,
	.size = VT1724_MT_PLAYBACK_SIZE,
	.count = VT1724_MT_PLAYBACK_COUNT,
	.start = VT1724_PDMA0_START,
पूर्ण;

अटल स्थिर काष्ठा vt1724_pcm_reg vt1724_pdma4_reg = अणु
	.addr = VT1724_MT_PDMA4_ADDR,
	.size = VT1724_MT_PDMA4_SIZE,
	.count = VT1724_MT_PDMA4_COUNT,
	.start = VT1724_PDMA4_START,
पूर्ण;

अटल स्थिर काष्ठा vt1724_pcm_reg vt1724_rdma0_reg = अणु
	.addr = VT1724_MT_CAPTURE_ADDR,
	.size = VT1724_MT_CAPTURE_SIZE,
	.count = VT1724_MT_CAPTURE_COUNT,
	.start = VT1724_RDMA0_START,
पूर्ण;

अटल स्थिर काष्ठा vt1724_pcm_reg vt1724_rdma1_reg = अणु
	.addr = VT1724_MT_RDMA1_ADDR,
	.size = VT1724_MT_RDMA1_SIZE,
	.count = VT1724_MT_RDMA1_COUNT,
	.start = VT1724_RDMA1_START,
पूर्ण;

#घोषणा vt1724_playback_pro_reg vt1724_pdma0_reg
#घोषणा vt1724_playback_spdअगर_reg vt1724_pdma4_reg
#घोषणा vt1724_capture_pro_reg vt1724_rdma0_reg
#घोषणा vt1724_capture_spdअगर_reg vt1724_rdma1_reg

अटल स्थिर काष्ठा snd_pcm_hardware snd_vt1724_playback_pro = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
	.rates =		SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_192000,
	.rate_min =		8000,
	.rate_max =		192000,
	.channels_min =		2,
	.channels_max =		8,
	.buffer_bytes_max =	(1UL << 21),	/* 19bits dword */
	.period_bytes_min =	8 * 4 * 2,	/* FIXME: स्थिरraपूर्णांकs needed */
	.period_bytes_max =	(1UL << 21),
	.periods_min =		2,
	.periods_max =		1024,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_vt1724_spdअगर = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
	.rates =	        (SNDRV_PCM_RATE_32000|SNDRV_PCM_RATE_44100|
				 SNDRV_PCM_RATE_48000|SNDRV_PCM_RATE_88200|
				 SNDRV_PCM_RATE_96000|SNDRV_PCM_RATE_176400|
				 SNDRV_PCM_RATE_192000),
	.rate_min =		32000,
	.rate_max =		192000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(1UL << 18),	/* 16bits dword */
	.period_bytes_min =	2 * 4 * 2,
	.period_bytes_max =	(1UL << 18),
	.periods_min =		2,
	.periods_max =		1024,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_vt1724_2ch_stereo = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
	.rates =		SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_192000,
	.rate_min =		8000,
	.rate_max =		192000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(1UL << 18),	/* 16bits dword */
	.period_bytes_min =	2 * 4 * 2,
	.period_bytes_max =	(1UL << 18),
	.periods_min =		2,
	.periods_max =		1024,
पूर्ण;

/*
 * set rate स्थिरraपूर्णांकs
 */
अटल व्योम set_std_hw_rates(काष्ठा snd_ice1712 *ice)
अणु
	अगर (ice->eeprom.data[ICE_EEP2_ACLINK] & VT1724_CFG_PRO_I2S) अणु
		/* I2S */
		/* VT1720 करोesn't support more than 96kHz */
		अगर ((ice->eeprom.data[ICE_EEP2_I2S] & 0x08) && !ice->vt1720)
			ice->hw_rates = &hw_स्थिरraपूर्णांकs_rates_192;
		अन्यथा
			ice->hw_rates = &hw_स्थिरraपूर्णांकs_rates_96;
	पूर्ण अन्यथा अणु
		/* ACLINK */
		ice->hw_rates = &hw_स्थिरraपूर्णांकs_rates_48;
	पूर्ण
पूर्ण

अटल पूर्णांक set_rate_स्थिरraपूर्णांकs(काष्ठा snd_ice1712 *ice,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw.rate_min = ice->hw_rates->list[0];
	runसमय->hw.rate_max = ice->hw_rates->list[ice->hw_rates->count - 1];
	runसमय->hw.rates = SNDRV_PCM_RATE_KNOT;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  ice->hw_rates);
पूर्ण

/* अगर the card has the पूर्णांकernal rate locked (is_pro_locked), limit runसमय
   hw rates to the current पूर्णांकernal rate only.
*/
अटल व्योम स्थिरrain_rate_अगर_locked(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक rate;
	अगर (is_pro_rate_locked(ice)) अणु
		rate = ice->get_rate(ice);
		अगर (rate >= runसमय->hw.rate_min
		    && rate <= runसमय->hw.rate_max) अणु
			runसमय->hw.rate_min = rate;
			runसमय->hw.rate_max = rate;
		पूर्ण
	पूर्ण
पूर्ण


/* multi-channel playback needs alignment 8x32bit regardless of the channels
 * actually used
 */
#घोषणा VT1724_BUFFER_ALIGN	0x20

अटल पूर्णांक snd_vt1724_playback_pro_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	पूर्णांक chs, num_indeps;

	runसमय->निजी_data = (व्योम *)&vt1724_playback_pro_reg;
	ice->playback_pro_substream = substream;
	runसमय->hw = snd_vt1724_playback_pro;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	set_rate_स्थिरraपूर्णांकs(ice, substream);
	mutex_lock(&ice->खोलो_mutex);
	/* calculate the currently available channels */
	num_indeps = ice->num_total_dacs / 2 - 1;
	क्रम (chs = 0; chs < num_indeps; chs++) अणु
		अगर (ice->pcm_reserved[chs])
			अवरोध;
	पूर्ण
	chs = (chs + 1) * 2;
	runसमय->hw.channels_max = chs;
	अगर (chs > 2) /* channels must be even */
		snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS, 2);
	mutex_unlock(&ice->खोलो_mutex);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   VT1724_BUFFER_ALIGN);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   VT1724_BUFFER_ALIGN);
	स्थिरrain_rate_अगर_locked(substream);
	अगर (ice->pro_खोलो)
		ice->pro_खोलो(ice, substream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_capture_pro_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->निजी_data = (व्योम *)&vt1724_capture_pro_reg;
	ice->capture_pro_substream = substream;
	runसमय->hw = snd_vt1724_2ch_stereo;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	set_rate_स्थिरraपूर्णांकs(ice, substream);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   VT1724_BUFFER_ALIGN);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   VT1724_BUFFER_ALIGN);
	स्थिरrain_rate_अगर_locked(substream);
	अगर (ice->pro_खोलो)
		ice->pro_खोलो(ice, substream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_playback_pro_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	अगर (PRO_RATE_RESET)
		snd_vt1724_set_pro_rate(ice, ice->pro_rate_शेष, 0);
	ice->playback_pro_substream = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_capture_pro_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	अगर (PRO_RATE_RESET)
		snd_vt1724_set_pro_rate(ice, ice->pro_rate_शेष, 0);
	ice->capture_pro_substream = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_vt1724_playback_pro_ops = अणु
	.खोलो =		snd_vt1724_playback_pro_खोलो,
	.बंद =	snd_vt1724_playback_pro_बंद,
	.hw_params =	snd_vt1724_pcm_hw_params,
	.hw_मुक्त =	snd_vt1724_pcm_hw_मुक्त,
	.prepare =	snd_vt1724_playback_pro_prepare,
	.trigger =	snd_vt1724_pcm_trigger,
	.poपूर्णांकer =	snd_vt1724_playback_pro_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_vt1724_capture_pro_ops = अणु
	.खोलो =		snd_vt1724_capture_pro_खोलो,
	.बंद =	snd_vt1724_capture_pro_बंद,
	.hw_params =	snd_vt1724_pcm_hw_params,
	.hw_मुक्त =	snd_vt1724_pcm_hw_मुक्त,
	.prepare =	snd_vt1724_pcm_prepare,
	.trigger =	snd_vt1724_pcm_trigger,
	.poपूर्णांकer =	snd_vt1724_pcm_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_vt1724_pcm_profi(काष्ठा snd_ice1712 *ice, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक capt, err;

	अगर ((ice->eeprom.data[ICE_EEP2_SYSCONF] & VT1724_CFG_ADC_MASK) ==
	    VT1724_CFG_ADC_NONE)
		capt = 0;
	अन्यथा
		capt = 1;
	err = snd_pcm_new(ice->card, "ICE1724", device, 1, capt, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_vt1724_playback_pro_ops);
	अगर (capt)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_vt1724_capture_pro_ops);

	pcm->निजी_data = ice;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "ICE1724");

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &ice->pci->dev, 256*1024, 256*1024);

	ice->pcm_pro = pcm;

	वापस 0;
पूर्ण


/*
 * SPDIF PCM
 */

/* update spdअगर control bits; call with reg_lock */
अटल व्योम update_spdअगर_bits(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित अक्षर cbit, disabled;

	cbit = inb(ICEREG1724(ice, SPDIF_CFG));
	disabled = cbit & ~VT1724_CFG_SPDIF_OUT_EN;
	अगर (cbit != disabled)
		outb(disabled, ICEREG1724(ice, SPDIF_CFG));
	outw(val, ICEMT1724(ice, SPDIF_CTRL));
	अगर (cbit != disabled)
		outb(cbit, ICEREG1724(ice, SPDIF_CFG));
	outw(val, ICEMT1724(ice, SPDIF_CTRL));
पूर्ण

/* update SPDIF control bits according to the given rate */
अटल व्योम update_spdअगर_rate(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक val, nval;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ice->reg_lock, flags);
	nval = val = inw(ICEMT1724(ice, SPDIF_CTRL));
	nval &= ~(7 << 12);
	चयन (rate) अणु
	हाल 44100: अवरोध;
	हाल 48000: nval |= 2 << 12; अवरोध;
	हाल 32000: nval |= 3 << 12; अवरोध;
	हाल 88200: nval |= 4 << 12; अवरोध;
	हाल 96000: nval |= 5 << 12; अवरोध;
	हाल 192000: nval |= 6 << 12; अवरोध;
	हाल 176400: nval |= 7 << 12; अवरोध;
	पूर्ण
	अगर (val != nval)
		update_spdअगर_bits(ice, nval);
	spin_unlock_irqrestore(&ice->reg_lock, flags);
पूर्ण

अटल पूर्णांक snd_vt1724_playback_spdअगर_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	अगर (!ice->क्रमce_pdma4)
		update_spdअगर_rate(ice, substream->runसमय->rate);
	वापस snd_vt1724_pcm_prepare(substream);
पूर्ण

अटल पूर्णांक snd_vt1724_playback_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->निजी_data = (व्योम *)&vt1724_playback_spdअगर_reg;
	ice->playback_con_substream = substream;
	अगर (ice->क्रमce_pdma4) अणु
		runसमय->hw = snd_vt1724_2ch_stereo;
		set_rate_स्थिरraपूर्णांकs(ice, substream);
	पूर्ण अन्यथा
		runसमय->hw = snd_vt1724_spdअगर;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   VT1724_BUFFER_ALIGN);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   VT1724_BUFFER_ALIGN);
	स्थिरrain_rate_अगर_locked(substream);
	अगर (ice->spdअगर.ops.खोलो)
		ice->spdअगर.ops.खोलो(ice, substream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_playback_spdअगर_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	अगर (PRO_RATE_RESET)
		snd_vt1724_set_pro_rate(ice, ice->pro_rate_शेष, 0);
	ice->playback_con_substream = शून्य;
	अगर (ice->spdअगर.ops.बंद)
		ice->spdअगर.ops.बंद(ice, substream);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_capture_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->निजी_data = (व्योम *)&vt1724_capture_spdअगर_reg;
	ice->capture_con_substream = substream;
	अगर (ice->क्रमce_rdma1) अणु
		runसमय->hw = snd_vt1724_2ch_stereo;
		set_rate_स्थिरraपूर्णांकs(ice, substream);
	पूर्ण अन्यथा
		runसमय->hw = snd_vt1724_spdअगर;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   VT1724_BUFFER_ALIGN);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   VT1724_BUFFER_ALIGN);
	स्थिरrain_rate_अगर_locked(substream);
	अगर (ice->spdअगर.ops.खोलो)
		ice->spdअगर.ops.खोलो(ice, substream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_capture_spdअगर_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	अगर (PRO_RATE_RESET)
		snd_vt1724_set_pro_rate(ice, ice->pro_rate_शेष, 0);
	ice->capture_con_substream = शून्य;
	अगर (ice->spdअगर.ops.बंद)
		ice->spdअगर.ops.बंद(ice, substream);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_vt1724_playback_spdअगर_ops = अणु
	.खोलो =		snd_vt1724_playback_spdअगर_खोलो,
	.बंद =	snd_vt1724_playback_spdअगर_बंद,
	.hw_params =	snd_vt1724_pcm_hw_params,
	.hw_मुक्त =	snd_vt1724_pcm_hw_मुक्त,
	.prepare =	snd_vt1724_playback_spdअगर_prepare,
	.trigger =	snd_vt1724_pcm_trigger,
	.poपूर्णांकer =	snd_vt1724_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_vt1724_capture_spdअगर_ops = अणु
	.खोलो =		snd_vt1724_capture_spdअगर_खोलो,
	.बंद =	snd_vt1724_capture_spdअगर_बंद,
	.hw_params =	snd_vt1724_pcm_hw_params,
	.hw_मुक्त =	snd_vt1724_pcm_hw_मुक्त,
	.prepare =	snd_vt1724_pcm_prepare,
	.trigger =	snd_vt1724_pcm_trigger,
	.poपूर्णांकer =	snd_vt1724_pcm_poपूर्णांकer,
पूर्ण;


अटल पूर्णांक snd_vt1724_pcm_spdअगर(काष्ठा snd_ice1712 *ice, पूर्णांक device)
अणु
	अक्षर *name;
	काष्ठा snd_pcm *pcm;
	पूर्णांक play, capt;
	पूर्णांक err;

	अगर (ice->क्रमce_pdma4 ||
	    (ice->eeprom.data[ICE_EEP2_SPDIF] & VT1724_CFG_SPDIF_OUT_INT)) अणु
		play = 1;
		ice->has_spdअगर = 1;
	पूर्ण अन्यथा
		play = 0;
	अगर (ice->क्रमce_rdma1 ||
	    (ice->eeprom.data[ICE_EEP2_SPDIF] & VT1724_CFG_SPDIF_IN)) अणु
		capt = 1;
		ice->has_spdअगर = 1;
	पूर्ण अन्यथा
		capt = 0;
	अगर (!play && !capt)
		वापस 0; /* no spdअगर device */

	अगर (ice->क्रमce_pdma4 || ice->क्रमce_rdma1)
		name = "ICE1724 Secondary";
	अन्यथा
		name = "ICE1724 IEC958";
	err = snd_pcm_new(ice->card, name, device, play, capt, &pcm);
	अगर (err < 0)
		वापस err;

	अगर (play)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_vt1724_playback_spdअगर_ops);
	अगर (capt)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_vt1724_capture_spdअगर_ops);

	pcm->निजी_data = ice;
	pcm->info_flags = 0;
	म_नकल(pcm->name, name);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &ice->pci->dev, 256*1024, 256*1024);

	ice->pcm = pcm;

	वापस 0;
पूर्ण


/*
 * independent surround PCMs
 */

अटल स्थिर काष्ठा vt1724_pcm_reg vt1724_playback_dma_regs[3] = अणु
	अणु
		.addr = VT1724_MT_PDMA1_ADDR,
		.size = VT1724_MT_PDMA1_SIZE,
		.count = VT1724_MT_PDMA1_COUNT,
		.start = VT1724_PDMA1_START,
	पूर्ण,
	अणु
		.addr = VT1724_MT_PDMA2_ADDR,
		.size = VT1724_MT_PDMA2_SIZE,
		.count = VT1724_MT_PDMA2_COUNT,
		.start = VT1724_PDMA2_START,
	पूर्ण,
	अणु
		.addr = VT1724_MT_PDMA3_ADDR,
		.size = VT1724_MT_PDMA3_SIZE,
		.count = VT1724_MT_PDMA3_COUNT,
		.start = VT1724_PDMA3_START,
	पूर्ण,
पूर्ण;

अटल पूर्णांक snd_vt1724_playback_indep_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	अचिन्हित अक्षर val;

	spin_lock_irq(&ice->reg_lock);
	val = 3 - substream->number;
	अगर (inb(ICEMT1724(ice, BURST)) < val)
		outb(val, ICEMT1724(ice, BURST));
	spin_unlock_irq(&ice->reg_lock);
	वापस snd_vt1724_pcm_prepare(substream);
पूर्ण

अटल पूर्णांक snd_vt1724_playback_indep_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	mutex_lock(&ice->खोलो_mutex);
	/* alपढ़ोy used by PDMA0? */
	अगर (ice->pcm_reserved[substream->number]) अणु
		mutex_unlock(&ice->खोलो_mutex);
		वापस -EBUSY; /* FIXME: should handle blocking mode properly */
	पूर्ण
	mutex_unlock(&ice->खोलो_mutex);
	runसमय->निजी_data = (व्योम *)&vt1724_playback_dma_regs[substream->number];
	ice->playback_con_substream_ds[substream->number] = substream;
	runसमय->hw = snd_vt1724_2ch_stereo;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	set_rate_स्थिरraपूर्णांकs(ice, substream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_playback_indep_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	अगर (PRO_RATE_RESET)
		snd_vt1724_set_pro_rate(ice, ice->pro_rate_शेष, 0);
	ice->playback_con_substream_ds[substream->number] = शून्य;
	ice->pcm_reserved[substream->number] = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_vt1724_playback_indep_ops = अणु
	.खोलो =		snd_vt1724_playback_indep_खोलो,
	.बंद =	snd_vt1724_playback_indep_बंद,
	.hw_params =	snd_vt1724_pcm_hw_params,
	.hw_मुक्त =	snd_vt1724_pcm_hw_मुक्त,
	.prepare =	snd_vt1724_playback_indep_prepare,
	.trigger =	snd_vt1724_pcm_trigger,
	.poपूर्णांकer =	snd_vt1724_pcm_poपूर्णांकer,
पूर्ण;


अटल पूर्णांक snd_vt1724_pcm_indep(काष्ठा snd_ice1712 *ice, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक play;
	पूर्णांक err;

	play = ice->num_total_dacs / 2 - 1;
	अगर (play <= 0)
		वापस 0;

	err = snd_pcm_new(ice->card, "ICE1724 Surrounds", device, play, 0, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_vt1724_playback_indep_ops);

	pcm->निजी_data = ice;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "ICE1724 Surround PCM");

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &ice->pci->dev, 256*1024, 256*1024);

	ice->pcm_ds = pcm;

	वापस 0;
पूर्ण


/*
 *  Mixer section
 */

अटल पूर्णांक snd_vt1724_ac97_mixer(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err;

	अगर (!(ice->eeprom.data[ICE_EEP2_ACLINK] & VT1724_CFG_PRO_I2S)) अणु
		काष्ठा snd_ac97_bus *pbus;
		काष्ठा snd_ac97_ढाँचा ac97;
		अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
			.ग_लिखो = snd_vt1724_ac97_ग_लिखो,
			.पढ़ो = snd_vt1724_ac97_पढ़ो,
		पूर्ण;

		/* cold reset */
		outb(inb(ICEMT1724(ice, AC97_CMD)) | 0x80, ICEMT1724(ice, AC97_CMD));
		mdelay(5); /* FIXME */
		outb(inb(ICEMT1724(ice, AC97_CMD)) & ~0x80, ICEMT1724(ice, AC97_CMD));

		err = snd_ac97_bus(ice->card, 0, &ops, शून्य, &pbus);
		अगर (err < 0)
			वापस err;
		स_रखो(&ac97, 0, माप(ac97));
		ac97.निजी_data = ice;
		err = snd_ac97_mixer(pbus, &ac97, &ice->ac97);
		अगर (err < 0)
			dev_warn(ice->card->dev,
				 "cannot initialize pro ac97, skipped\n");
		अन्यथा
			वापस 0;
	पूर्ण
	/* I2S mixer only */
	म_जोड़ो(ice->card->mixername, "ICE1724 - multitrack");
	वापस 0;
पूर्ण

/*
 *
 */

अटल अंतरभूत अचिन्हित पूर्णांक eeprom_triple(काष्ठा snd_ice1712 *ice, पूर्णांक idx)
अणु
	वापस (अचिन्हित पूर्णांक)ice->eeprom.data[idx] | \
		((अचिन्हित पूर्णांक)ice->eeprom.data[idx + 1] << 8) | \
		((अचिन्हित पूर्णांक)ice->eeprom.data[idx + 2] << 16);
पूर्ण

अटल व्योम snd_vt1724_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ice1712 *ice = entry->निजी_data;
	अचिन्हित पूर्णांक idx;

	snd_iम_लिखो(buffer, "%s\n\n", ice->card->दीर्घname);
	snd_iम_लिखो(buffer, "EEPROM:\n");

	snd_iम_लिखो(buffer, "  Subvendor        : 0x%x\n", ice->eeprom.subvenकरोr);
	snd_iम_लिखो(buffer, "  Size             : %i bytes\n", ice->eeprom.size);
	snd_iम_लिखो(buffer, "  Version          : %i\n", ice->eeprom.version);
	snd_iम_लिखो(buffer, "  System Config    : 0x%x\n",
		    ice->eeprom.data[ICE_EEP2_SYSCONF]);
	snd_iम_लिखो(buffer, "  ACLink           : 0x%x\n",
		    ice->eeprom.data[ICE_EEP2_ACLINK]);
	snd_iम_लिखो(buffer, "  I2S              : 0x%x\n",
		    ice->eeprom.data[ICE_EEP2_I2S]);
	snd_iम_लिखो(buffer, "  S/PDIF           : 0x%x\n",
		    ice->eeprom.data[ICE_EEP2_SPDIF]);
	snd_iम_लिखो(buffer, "  GPIO direction   : 0x%x\n",
		    ice->eeprom.gpiodir);
	snd_iम_लिखो(buffer, "  GPIO mask        : 0x%x\n",
		    ice->eeprom.gpiomask);
	snd_iम_लिखो(buffer, "  GPIO state       : 0x%x\n",
		    ice->eeprom.gpiostate);
	क्रम (idx = 0x12; idx < ice->eeprom.size; idx++)
		snd_iम_लिखो(buffer, "  Extra #%02i        : 0x%x\n",
			    idx, ice->eeprom.data[idx]);

	snd_iम_लिखो(buffer, "\nRegisters:\n");

	snd_iम_लिखो(buffer, "  PSDOUT03 : 0x%08x\n",
		    (अचिन्हित)inl(ICEMT1724(ice, ROUTE_PLAYBACK)));
	क्रम (idx = 0x0; idx < 0x20 ; idx++)
		snd_iम_लिखो(buffer, "  CCS%02x    : 0x%02x\n",
			    idx, inb(ice->port+idx));
	क्रम (idx = 0x0; idx < 0x30 ; idx++)
		snd_iम_लिखो(buffer, "  MT%02x     : 0x%02x\n",
			    idx, inb(ice->profi_port+idx));
पूर्ण

अटल व्योम snd_vt1724_proc_init(काष्ठा snd_ice1712 *ice)
अणु
	snd_card_ro_proc_new(ice->card, "ice1724", ice, snd_vt1724_proc_पढ़ो);
पूर्ण

/*
 *
 */

अटल पूर्णांक snd_vt1724_eeprom_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = माप(काष्ठा snd_ice1712_eeprom);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_eeprom_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	स_नकल(ucontrol->value.bytes.data, &ice->eeprom, माप(ice->eeprom));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_eeprom = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.name = "ICE1724 EEPROM",
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = snd_vt1724_eeprom_info,
	.get = snd_vt1724_eeprom_get
पूर्ण;

/*
 */
अटल पूर्णांक snd_vt1724_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक encode_spdअगर_bits(काष्ठा snd_aes_iec958 *diga)
अणु
	अचिन्हित पूर्णांक val, rbits;

	val = diga->status[0] & 0x03; /* professional, non-audio */
	अगर (val & 0x01) अणु
		/* professional */
		अगर ((diga->status[0] & IEC958_AES0_PRO_EMPHASIS) ==
		    IEC958_AES0_PRO_EMPHASIS_5015)
			val |= 1U << 3;
		rbits = (diga->status[4] >> 3) & 0x0f;
		अगर (rbits) अणु
			चयन (rbits) अणु
			हाल 2: val |= 5 << 12; अवरोध; /* 96k */
			हाल 3: val |= 6 << 12; अवरोध; /* 192k */
			हाल 10: val |= 4 << 12; अवरोध; /* 88.2k */
			हाल 11: val |= 7 << 12; अवरोध; /* 176.4k */
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (diga->status[0] & IEC958_AES0_PRO_FS) अणु
			हाल IEC958_AES0_PRO_FS_44100:
				अवरोध;
			हाल IEC958_AES0_PRO_FS_32000:
				val |= 3U << 12;
				अवरोध;
			शेष:
				val |= 2U << 12;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* consumer */
		val |= diga->status[1] & 0x04; /* copyright */
		अगर ((diga->status[0] & IEC958_AES0_CON_EMPHASIS) ==
		    IEC958_AES0_CON_EMPHASIS_5015)
			val |= 1U << 3;
		val |= (अचिन्हित पूर्णांक)(diga->status[1] & 0x3f) << 4; /* category */
		val |= (अचिन्हित पूर्णांक)(diga->status[3] & IEC958_AES3_CON_FS) << 12; /* fs */
	पूर्ण
	वापस val;
पूर्ण

अटल व्योम decode_spdअगर_bits(काष्ठा snd_aes_iec958 *diga, अचिन्हित पूर्णांक val)
अणु
	स_रखो(diga->status, 0, माप(diga->status));
	diga->status[0] = val & 0x03; /* professional, non-audio */
	अगर (val & 0x01) अणु
		/* professional */
		अगर (val & (1U << 3))
			diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_5015;
		चयन ((val >> 12) & 0x7) अणु
		हाल 0:
			अवरोध;
		हाल 2:
			diga->status[0] |= IEC958_AES0_PRO_FS_32000;
			अवरोध;
		शेष:
			diga->status[0] |= IEC958_AES0_PRO_FS_48000;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* consumer */
		diga->status[0] |= val & (1U << 2); /* copyright */
		अगर (val & (1U << 3))
			diga->status[0] |= IEC958_AES0_CON_EMPHASIS_5015;
		diga->status[1] |= (val >> 4) & 0x3f; /* category */
		diga->status[3] |= (val >> 12) & 0x07; /* fs */
	पूर्ण
पूर्ण

अटल पूर्णांक snd_vt1724_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	val = inw(ICEMT1724(ice, SPDIF_CTRL));
	decode_spdअगर_bits(&ucontrol->value.iec958, val);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val, old;

	val = encode_spdअगर_bits(&ucontrol->value.iec958);
	spin_lock_irq(&ice->reg_lock);
	old = inw(ICEMT1724(ice, SPDIF_CTRL));
	अगर (val != old)
		update_spdअगर_bits(ice, val);
	spin_unlock_irq(&ice->reg_lock);
	वापस val != old;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_spdअगर_शेष =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
	.info =		snd_vt1724_spdअगर_info,
	.get =		snd_vt1724_spdअगर_शेष_get,
	.put =		snd_vt1724_spdअगर_शेष_put
पूर्ण;

अटल पूर्णांक snd_vt1724_spdअगर_maskc_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PROFESSIONAL |
						     IEC958_AES0_CON_NOT_COPYRIGHT |
						     IEC958_AES0_CON_EMPHASIS;
	ucontrol->value.iec958.status[1] = IEC958_AES1_CON_ORIGINAL |
						     IEC958_AES1_CON_CATEGORY;
	ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_spdअगर_maskp_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = IEC958_AES0_NONAUDIO |
						     IEC958_AES0_PROFESSIONAL |
						     IEC958_AES0_PRO_FS |
						     IEC958_AES0_PRO_EMPHASIS;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_spdअगर_maskc =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("", PLAYBACK, CON_MASK),
	.info =		snd_vt1724_spdअगर_info,
	.get =		snd_vt1724_spdअगर_maskc_get,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_spdअगर_maskp =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("", PLAYBACK, PRO_MASK),
	.info =		snd_vt1724_spdअगर_info,
	.get =		snd_vt1724_spdअगर_maskp_get,
पूर्ण;

#घोषणा snd_vt1724_spdअगर_sw_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_vt1724_spdअगर_sw_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = inb(ICEREG1724(ice, SPDIF_CFG)) &
		VT1724_CFG_SPDIF_OUT_EN ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_spdअगर_sw_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर old, val;

	spin_lock_irq(&ice->reg_lock);
	old = val = inb(ICEREG1724(ice, SPDIF_CFG));
	val &= ~VT1724_CFG_SPDIF_OUT_EN;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= VT1724_CFG_SPDIF_OUT_EN;
	अगर (old != val)
		outb(val, ICEREG1724(ice, SPDIF_CFG));
	spin_unlock_irq(&ice->reg_lock);
	वापस old != val;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_spdअगर_चयन =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	/* FIXME: the following conflict with IEC958 Playback Route */
	/* .name =         SNDRV_CTL_NAME_IEC958("", PLAYBACK, SWITCH), */
	.name =         SNDRV_CTL_NAME_IEC958("Output ", NONE, SWITCH),
	.info =		snd_vt1724_spdअगर_sw_info,
	.get =		snd_vt1724_spdअगर_sw_get,
	.put =		snd_vt1724_spdअगर_sw_put
पूर्ण;


#अगर 0 /* NOT USED YET */
/*
 * GPIO access from बाह्य
 */

#घोषणा snd_vt1724_gpio_info		snd_ctl_boolean_mono_info

पूर्णांक snd_vt1724_gpio_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक shअगरt = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value & (1<<24)) ? 1 : 0;

	snd_ice1712_save_gpio_status(ice);
	ucontrol->value.पूर्णांकeger.value[0] =
		(snd_ice1712_gpio_पढ़ो(ice) & (1 << shअगरt) ? 1 : 0) ^ invert;
	snd_ice1712_restore_gpio_status(ice);
	वापस 0;
पूर्ण

पूर्णांक snd_ice1712_gpio_put(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक shअगरt = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value & (1<<24)) ? mask : 0;
	अचिन्हित पूर्णांक val, nval;

	अगर (kcontrol->निजी_value & (1 << 31))
		वापस -EPERM;
	nval = (ucontrol->value.पूर्णांकeger.value[0] ? (1 << shअगरt) : 0) ^ invert;
	snd_ice1712_save_gpio_status(ice);
	val = snd_ice1712_gpio_पढ़ो(ice);
	nval |= val & ~(1 << shअगरt);
	अगर (val != nval)
		snd_ice1712_gpio_ग_लिखो(ice, nval);
	snd_ice1712_restore_gpio_status(ice);
	वापस val != nval;
पूर्ण
#पूर्ण_अगर /* NOT USED YET */

/*
 *  rate
 */
अटल पूर्णांक snd_vt1724_pro_पूर्णांकernal_घड़ी_info(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक hw_rates_count = ice->hw_rates->count;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;

	/* पूर्णांकernal घड़ीs */
	uinfo->value.क्रमागतerated.items = hw_rates_count;
	/* बाह्यal घड़ीs */
	अगर (ice->क्रमce_rdma1 ||
	    (ice->eeprom.data[ICE_EEP2_SPDIF] & VT1724_CFG_SPDIF_IN))
		uinfo->value.क्रमागतerated.items += ice->ext_घड़ी_count;
	/* upper limit - keep at top */
	अगर (uinfo->value.क्रमागतerated.item >= uinfo->value.क्रमागतerated.items)
		uinfo->value.क्रमागतerated.item = uinfo->value.क्रमागतerated.items - 1;
	अगर (uinfo->value.क्रमागतerated.item >= hw_rates_count)
		/* ext_घड़ी items */
		म_नकल(uinfo->value.क्रमागतerated.name,
				ice->ext_घड़ी_names[
				uinfo->value.क्रमागतerated.item - hw_rates_count]);
	अन्यथा
		/* पूर्णांक घड़ी items */
		प्र_लिखो(uinfo->value.क्रमागतerated.name, "%d",
			ice->hw_rates->list[uinfo->value.क्रमागतerated.item]);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_pro_पूर्णांकernal_घड़ी_get(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक i, rate;

	spin_lock_irq(&ice->reg_lock);
	अगर (ice->is_spdअगर_master(ice)) अणु
		ucontrol->value.क्रमागतerated.item[0] = ice->hw_rates->count +
			ice->get_spdअगर_master_type(ice);
	पूर्ण अन्यथा अणु
		rate = ice->get_rate(ice);
		ucontrol->value.क्रमागतerated.item[0] = 0;
		क्रम (i = 0; i < ice->hw_rates->count; i++) अणु
			अगर (ice->hw_rates->list[i] == rate) अणु
				ucontrol->value.क्रमागतerated.item[0] = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक stdघड़ी_get_spdअगर_master_type(काष्ठा snd_ice1712 *ice)
अणु
	/* standard बाह्यal घड़ी - only single type - SPDIF IN */
	वापस 0;
पूर्ण

/* setting घड़ी to बाह्यal - SPDIF */
अटल पूर्णांक stdघड़ी_set_spdअगर_घड़ी(काष्ठा snd_ice1712 *ice, पूर्णांक type)
अणु
	अचिन्हित अक्षर oval;
	अचिन्हित अक्षर i2s_oval;
	oval = inb(ICEMT1724(ice, RATE));
	outb(oval | VT1724_SPDIF_MASTER, ICEMT1724(ice, RATE));
	/* setting 256fs */
	i2s_oval = inb(ICEMT1724(ice, I2S_FORMAT));
	outb(i2s_oval & ~VT1724_MT_I2S_MCLK_128X, ICEMT1724(ice, I2S_FORMAT));
	वापस 0;
पूर्ण


अटल पूर्णांक snd_vt1724_pro_पूर्णांकernal_घड़ी_put(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक old_rate, new_rate;
	अचिन्हित पूर्णांक item = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक first_ext_घड़ी = ice->hw_rates->count;

	अगर (item >  first_ext_घड़ी + ice->ext_घड़ी_count - 1)
		वापस -EINVAL;

	/* अगर rate = 0 => बाह्यal घड़ी */
	spin_lock_irq(&ice->reg_lock);
	अगर (ice->is_spdअगर_master(ice))
		old_rate = 0;
	अन्यथा
		old_rate = ice->get_rate(ice);
	अगर (item >= first_ext_घड़ी) अणु
		/* चयनing to बाह्यal घड़ी */
		ice->set_spdअगर_घड़ी(ice, item - first_ext_घड़ी);
		new_rate = 0;
	पूर्ण अन्यथा अणु
		/* पूर्णांकernal on-card घड़ी */
		new_rate = ice->hw_rates->list[item];
		ice->pro_rate_शेष = new_rate;
		spin_unlock_irq(&ice->reg_lock);
		snd_vt1724_set_pro_rate(ice, ice->pro_rate_शेष, 1);
		spin_lock_irq(&ice->reg_lock);
	पूर्ण
	spin_unlock_irq(&ice->reg_lock);

	/* the first चयन to the ext. घड़ी mode? */
	अगर (old_rate != new_rate && !new_rate) अणु
		/* notअगरy akm chips as well */
		अचिन्हित पूर्णांक i;
		अगर (ice->gpio.set_pro_rate)
			ice->gpio.set_pro_rate(ice, 0);
		क्रम (i = 0; i < ice->akm_codecs; i++) अणु
			अगर (ice->akm[i].ops.set_rate_val)
				ice->akm[i].ops.set_rate_val(&ice->akm[i], 0);
		पूर्ण
	पूर्ण
	वापस old_rate != new_rate;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_pro_पूर्णांकernal_घड़ी = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Multi Track Internal Clock",
	.info = snd_vt1724_pro_पूर्णांकernal_घड़ी_info,
	.get = snd_vt1724_pro_पूर्णांकernal_घड़ी_get,
	.put = snd_vt1724_pro_पूर्णांकernal_घड़ी_put
पूर्ण;

#घोषणा snd_vt1724_pro_rate_locking_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_vt1724_pro_rate_locking_get(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = PRO_RATE_LOCKED;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_pro_rate_locking_put(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक change = 0, nval;

	nval = ucontrol->value.पूर्णांकeger.value[0] ? 1 : 0;
	spin_lock_irq(&ice->reg_lock);
	change = PRO_RATE_LOCKED != nval;
	PRO_RATE_LOCKED = nval;
	spin_unlock_irq(&ice->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_pro_rate_locking = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Multi Track Rate Locking",
	.info = snd_vt1724_pro_rate_locking_info,
	.get = snd_vt1724_pro_rate_locking_get,
	.put = snd_vt1724_pro_rate_locking_put
पूर्ण;

#घोषणा snd_vt1724_pro_rate_reset_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_vt1724_pro_rate_reset_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = PRO_RATE_RESET ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_pro_rate_reset_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक change = 0, nval;

	nval = ucontrol->value.पूर्णांकeger.value[0] ? 1 : 0;
	spin_lock_irq(&ice->reg_lock);
	change = PRO_RATE_RESET != nval;
	PRO_RATE_RESET = nval;
	spin_unlock_irq(&ice->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_pro_rate_reset = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Multi Track Rate Reset",
	.info = snd_vt1724_pro_rate_reset_info,
	.get = snd_vt1724_pro_rate_reset_get,
	.put = snd_vt1724_pro_rate_reset_put
पूर्ण;


/*
 * routing
 */
अटल पूर्णांक snd_vt1724_pro_route_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"PCM Out", /* 0 */
		"H/W In 0", "H/W In 1", /* 1-2 */
		"IEC958 In L", "IEC958 In R", /* 3-4 */
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 5, texts);
पूर्ण

अटल अंतरभूत पूर्णांक analog_route_shअगरt(पूर्णांक idx)
अणु
	वापस (idx % 2) * 12 + ((idx / 2) * 3) + 8;
पूर्ण

अटल अंतरभूत पूर्णांक digital_route_shअगरt(पूर्णांक idx)
अणु
	वापस idx * 3;
पूर्ण

पूर्णांक snd_ice1724_get_route_val(काष्ठा snd_ice1712 *ice, पूर्णांक shअगरt)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित अक्षर eitem;
	अटल स्थिर अचिन्हित अक्षर xlate[8] = अणु
		0, 255, 1, 2, 255, 255, 3, 4,
	पूर्ण;

	val = inl(ICEMT1724(ice, ROUTE_PLAYBACK));
	val >>= shअगरt;
	val &= 7; /* we now have 3 bits per output */
	eitem = xlate[val];
	अगर (eitem == 255) अणु
		snd_BUG();
		वापस 0;
	पूर्ण
	वापस eitem;
पूर्ण

पूर्णांक snd_ice1724_put_route_val(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक val,
								पूर्णांक shअगरt)
अणु
	अचिन्हित पूर्णांक old_val, nval;
	पूर्णांक change;
	अटल स्थिर अचिन्हित अक्षर xroute[8] = अणु
		0, /* PCM */
		2, /* PSDIN0 Left */
		3, /* PSDIN0 Right */
		6, /* SPDIN Left */
		7, /* SPDIN Right */
	पूर्ण;

	nval = xroute[val % 5];
	val = old_val = inl(ICEMT1724(ice, ROUTE_PLAYBACK));
	val &= ~(0x07 << shअगरt);
	val |= nval << shअगरt;
	change = val != old_val;
	अगर (change)
		outl(val, ICEMT1724(ice, ROUTE_PLAYBACK));
	वापस change;
पूर्ण

अटल पूर्णांक snd_vt1724_pro_route_analog_get(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	ucontrol->value.क्रमागतerated.item[0] =
		snd_ice1724_get_route_val(ice, analog_route_shअगरt(idx));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_pro_route_analog_put(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	वापस snd_ice1724_put_route_val(ice,
					 ucontrol->value.क्रमागतerated.item[0],
					 analog_route_shअगरt(idx));
पूर्ण

अटल पूर्णांक snd_vt1724_pro_route_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	ucontrol->value.क्रमागतerated.item[0] =
		snd_ice1724_get_route_val(ice, digital_route_shअगरt(idx));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_pro_route_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	वापस snd_ice1724_put_route_val(ice,
					 ucontrol->value.क्रमागतerated.item[0],
					 digital_route_shअगरt(idx));
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_mixer_pro_analog_route =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "H/W Playback Route",
	.info = snd_vt1724_pro_route_info,
	.get = snd_vt1724_pro_route_analog_get,
	.put = snd_vt1724_pro_route_analog_put,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_mixer_pro_spdअगर_route = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, NONE) "Route",
	.info = snd_vt1724_pro_route_info,
	.get = snd_vt1724_pro_route_spdअगर_get,
	.put = snd_vt1724_pro_route_spdअगर_put,
	.count = 2,
पूर्ण;


अटल पूर्णांक snd_vt1724_pro_peak_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 22; /* FIXME: क्रम compatibility with ice1712... */
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_pro_peak_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx;

	spin_lock_irq(&ice->reg_lock);
	क्रम (idx = 0; idx < 22; idx++) अणु
		outb(idx, ICEMT1724(ice, MONITOR_PEAKINDEX));
		ucontrol->value.पूर्णांकeger.value[idx] =
			inb(ICEMT1724(ice, MONITOR_PEAKDATA));
	पूर्ण
	spin_unlock_irq(&ice->reg_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_vt1724_mixer_pro_peak = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = "Multi Track Peak",
	.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info = snd_vt1724_pro_peak_info,
	.get = snd_vt1724_pro_peak_get
पूर्ण;

/*
 *
 */

अटल स्थिर काष्ठा snd_ice1712_card_info no_matched;


/*
  ooAoo cards with no controls
*/
अटल स्थिर अचिन्हित अक्षर ooaoo_sq210_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x4c,	/* 49MHz crystal, no mpu401, no ADC,
					   1xDACs */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0x78,	/* no volume, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc1,	/* out-en, out-पूर्णांक, out-ext */
	[ICE_EEP2_GPIO_सूची]    = 0x00,	/* no GPIOs are used */
	[ICE_EEP2_GPIO_सूची1]   = 0x00,
	[ICE_EEP2_GPIO_सूची2]   = 0x00,
	[ICE_EEP2_GPIO_MASK]   = 0xff,
	[ICE_EEP2_GPIO_MASK1]  = 0xff,
	[ICE_EEP2_GPIO_MASK2]  = 0xff,

	[ICE_EEP2_GPIO_STATE]  = 0x00, /* inमाला_दो */
	[ICE_EEP2_GPIO_STATE1] = 0x00, /* all 1, but GPIO_CPLD_RW
					  and GPIO15 always zero */
	[ICE_EEP2_GPIO_STATE2] = 0x00, /* inमाला_दो */
पूर्ण;


अटल स्थिर काष्ठा snd_ice1712_card_info snd_vt1724_ooaoo_cards[] = अणु
	अणु
		.name = "ooAoo SQ210a",
		.model = "sq210a",
		.eeprom_size = माप(ooaoo_sq210_eeprom),
		.eeprom_data = ooaoo_sq210_eeprom,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा snd_ice1712_card_info *card_tables[] = अणु
	snd_vt1724_revo_cards,
	snd_vt1724_amp_cards,
	snd_vt1724_aureon_cards,
	snd_vt1720_mobo_cards,
	snd_vt1720_pontis_cards,
	snd_vt1724_prodigy_hअगरi_cards,
	snd_vt1724_prodigy192_cards,
	snd_vt1724_juli_cards,
	snd_vt1724_maya44_cards,
	snd_vt1724_phase_cards,
	snd_vt1724_wपंचांग_cards,
	snd_vt1724_se_cards,
	snd_vt1724_qtet_cards,
	snd_vt1724_ooaoo_cards,
	snd_vt1724_psc724_cards,
	शून्य,
पूर्ण;


/*
 */

अटल व्योम रुको_i2c_busy(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक t = 0x10000;
	जबतक ((inb(ICEREG1724(ice, I2C_CTRL)) & VT1724_I2C_BUSY) && t--)
		;
	अगर (t == -1)
		dev_err(ice->card->dev, "i2c busy timeout\n");
पूर्ण

अचिन्हित अक्षर snd_vt1724_पढ़ो_i2c(काष्ठा snd_ice1712 *ice,
				  अचिन्हित अक्षर dev, अचिन्हित अक्षर addr)
अणु
	अचिन्हित अक्षर val;

	mutex_lock(&ice->i2c_mutex);
	रुको_i2c_busy(ice);
	outb(addr, ICEREG1724(ice, I2C_BYTE_ADDR));
	outb(dev & ~VT1724_I2C_WRITE, ICEREG1724(ice, I2C_DEV_ADDR));
	रुको_i2c_busy(ice);
	val = inb(ICEREG1724(ice, I2C_DATA));
	mutex_unlock(&ice->i2c_mutex);
	/*
	dev_dbg(ice->card->dev, "i2c_read: [0x%x,0x%x] = 0x%x\n", dev, addr, val);
	*/
	वापस val;
पूर्ण

व्योम snd_vt1724_ग_लिखो_i2c(काष्ठा snd_ice1712 *ice,
			  अचिन्हित अक्षर dev, अचिन्हित अक्षर addr, अचिन्हित अक्षर data)
अणु
	mutex_lock(&ice->i2c_mutex);
	रुको_i2c_busy(ice);
	/*
	dev_dbg(ice->card->dev, "i2c_write: [0x%x,0x%x] = 0x%x\n", dev, addr, data);
	*/
	outb(addr, ICEREG1724(ice, I2C_BYTE_ADDR));
	outb(data, ICEREG1724(ice, I2C_DATA));
	outb(dev | VT1724_I2C_WRITE, ICEREG1724(ice, I2C_DEV_ADDR));
	रुको_i2c_busy(ice);
	mutex_unlock(&ice->i2c_mutex);
पूर्ण

अटल पूर्णांक snd_vt1724_पढ़ो_eeprom(काष्ठा snd_ice1712 *ice,
				  स्थिर अक्षर *modelname)
अणु
	स्थिर पूर्णांक dev = 0xa0;		/* EEPROM device address */
	अचिन्हित पूर्णांक i, size;
	स्थिर काष्ठा snd_ice1712_card_info * स्थिर *tbl, *c;

	अगर (!modelname || !*modelname) अणु
		ice->eeprom.subvenकरोr = 0;
		अगर ((inb(ICEREG1724(ice, I2C_CTRL)) & VT1724_I2C_EEPROM) != 0)
			ice->eeprom.subvenकरोr =
				(snd_vt1724_पढ़ो_i2c(ice, dev, 0x00) << 0) |
				(snd_vt1724_पढ़ो_i2c(ice, dev, 0x01) << 8) |
				(snd_vt1724_पढ़ो_i2c(ice, dev, 0x02) << 16) |
				(snd_vt1724_पढ़ो_i2c(ice, dev, 0x03) << 24);
		अगर (ice->eeprom.subvenकरोr == 0 ||
		    ice->eeprom.subvenकरोr == (अचिन्हित पूर्णांक)-1) अणु
			/* invalid subvenकरोr from EEPROM, try the PCI
			 * subststem ID instead
			 */
			u16 venकरोr, device;
			pci_पढ़ो_config_word(ice->pci, PCI_SUBSYSTEM_VENDOR_ID,
					     &venकरोr);
			pci_पढ़ो_config_word(ice->pci, PCI_SUBSYSTEM_ID, &device);
			ice->eeprom.subvenकरोr =
				((अचिन्हित पूर्णांक)swab16(venकरोr) << 16) | swab16(device);
			अगर (ice->eeprom.subvenकरोr == 0 ||
			    ice->eeprom.subvenकरोr == (अचिन्हित पूर्णांक)-1) अणु
				dev_err(ice->card->dev,
					"No valid ID is found\n");
				वापस -ENXIO;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (tbl = card_tables; *tbl; tbl++) अणु
		क्रम (c = *tbl; c->name; c++) अणु
			अगर (modelname && c->model &&
			    !म_भेद(modelname, c->model)) अणु
				dev_info(ice->card->dev,
					 "Using board model %s\n",
				       c->name);
				ice->eeprom.subvenकरोr = c->subvenकरोr;
			पूर्ण अन्यथा अगर (c->subvenकरोr != ice->eeprom.subvenकरोr)
				जारी;
			ice->card_info = c;
			अगर (!c->eeprom_size || !c->eeprom_data)
				जाओ found;
			/* अगर the EEPROM is given by the driver, use it */
			dev_dbg(ice->card->dev, "using the defined eeprom..\n");
			ice->eeprom.version = 2;
			ice->eeprom.size = c->eeprom_size + 6;
			स_नकल(ice->eeprom.data, c->eeprom_data, c->eeprom_size);
			जाओ पढ़ो_skipped;
		पूर्ण
	पूर्ण
	dev_warn(ice->card->dev, "No matching model found for ID 0x%x\n",
	       ice->eeprom.subvenकरोr);
#अगर_घोषित CONFIG_PM_SLEEP
	/* assume AC97-only card which can suspend without additional code */
	ice->pm_suspend_enabled = 1;
#पूर्ण_अगर

 found:
	ice->eeprom.size = snd_vt1724_पढ़ो_i2c(ice, dev, 0x04);
	अगर (ice->eeprom.size < 6)
		ice->eeprom.size = 32;
	अन्यथा अगर (ice->eeprom.size > 32) अणु
		dev_err(ice->card->dev, "Invalid EEPROM (size = %i)\n",
		       ice->eeprom.size);
		वापस -EIO;
	पूर्ण
	ice->eeprom.version = snd_vt1724_पढ़ो_i2c(ice, dev, 0x05);
	अगर (ice->eeprom.version != 1 && ice->eeprom.version != 2)
		dev_warn(ice->card->dev, "Invalid EEPROM version %i\n",
		       ice->eeprom.version);
	size = ice->eeprom.size - 6;
	क्रम (i = 0; i < size; i++)
		ice->eeprom.data[i] = snd_vt1724_पढ़ो_i2c(ice, dev, i + 6);

 पढ़ो_skipped:
	ice->eeprom.gpiomask = eeprom_triple(ice, ICE_EEP2_GPIO_MASK);
	ice->eeprom.gpiostate = eeprom_triple(ice, ICE_EEP2_GPIO_STATE);
	ice->eeprom.gpiodir = eeprom_triple(ice, ICE_EEP2_GPIO_सूची);

	वापस 0;
पूर्ण



अटल व्योम snd_vt1724_chip_reset(काष्ठा snd_ice1712 *ice)
अणु
	outb(VT1724_RESET , ICEREG1724(ice, CONTROL));
	inb(ICEREG1724(ice, CONTROL)); /* pci posting flush */
	msleep(10);
	outb(0, ICEREG1724(ice, CONTROL));
	inb(ICEREG1724(ice, CONTROL)); /* pci posting flush */
	msleep(10);
पूर्ण

अटल पूर्णांक snd_vt1724_chip_init(काष्ठा snd_ice1712 *ice)
अणु
	outb(ice->eeprom.data[ICE_EEP2_SYSCONF], ICEREG1724(ice, SYS_CFG));
	outb(ice->eeprom.data[ICE_EEP2_ACLINK], ICEREG1724(ice, AC97_CFG));
	outb(ice->eeprom.data[ICE_EEP2_I2S], ICEREG1724(ice, I2S_FEATURES));
	outb(ice->eeprom.data[ICE_EEP2_SPDIF], ICEREG1724(ice, SPDIF_CFG));

	ice->gpio.ग_लिखो_mask = ice->eeprom.gpiomask;
	ice->gpio.direction = ice->eeprom.gpiodir;
	snd_vt1724_set_gpio_mask(ice, ice->eeprom.gpiomask);
	snd_vt1724_set_gpio_dir(ice, ice->eeprom.gpiodir);
	snd_vt1724_set_gpio_data(ice, ice->eeprom.gpiostate);

	outb(0, ICEREG1724(ice, POWERDOWN));

	/* MPU_RX and TX irq masks are cleared later dynamically */
	outb(VT1724_IRQ_MPU_RX | VT1724_IRQ_MPU_TX , ICEREG1724(ice, IRQMASK));

	/* करोn't handle FIFO overrun/underruns (just yet),
	 * since they cause machine lockups
	 */
	outb(VT1724_MULTI_FIFO_ERR, ICEMT1724(ice, DMA_INT_MASK));

	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_spdअगर_build_controls(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err;
	काष्ठा snd_kcontrol *kctl;

	अगर (snd_BUG_ON(!ice->pcm))
		वापस -EIO;

	अगर (!ice->own_routing) अणु
		err = snd_ctl_add(ice->card,
			snd_ctl_new1(&snd_vt1724_mixer_pro_spdअगर_route, ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_vt1724_spdअगर_चयन, ice));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_vt1724_spdअगर_शेष, ice));
	अगर (err < 0)
		वापस err;
	kctl->id.device = ice->pcm->device;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_vt1724_spdअगर_maskc, ice));
	अगर (err < 0)
		वापस err;
	kctl->id.device = ice->pcm->device;
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_vt1724_spdअगर_maskp, ice));
	अगर (err < 0)
		वापस err;
	kctl->id.device = ice->pcm->device;
#अगर 0 /* use शेष only */
	err = snd_ctl_add(ice->card, kctl = snd_ctl_new1(&snd_vt1724_spdअगर_stream, ice));
	अगर (err < 0)
		वापस err;
	kctl->id.device = ice->pcm->device;
	ice->spdअगर.stream_ctl = kctl;
#पूर्ण_अगर
	वापस 0;
पूर्ण


अटल पूर्णांक snd_vt1724_build_controls(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err;

	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_vt1724_eeprom, ice));
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_vt1724_pro_पूर्णांकernal_घड़ी, ice));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_vt1724_pro_rate_locking, ice));
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_vt1724_pro_rate_reset, ice));
	अगर (err < 0)
		वापस err;

	अगर (!ice->own_routing && ice->num_total_dacs > 0) अणु
		काष्ठा snd_kcontrol_new पंचांगp = snd_vt1724_mixer_pro_analog_route;
		पंचांगp.count = ice->num_total_dacs;
		अगर (ice->vt1720 && पंचांगp.count > 2)
			पंचांगp.count = 2;
		err = snd_ctl_add(ice->card, snd_ctl_new1(&पंचांगp, ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस snd_ctl_add(ice->card,
			   snd_ctl_new1(&snd_vt1724_mixer_pro_peak, ice));
पूर्ण

अटल पूर्णांक snd_vt1724_मुक्त(काष्ठा snd_ice1712 *ice)
अणु
	अगर (!ice->port)
		जाओ __hw_end;
	/* mask all पूर्णांकerrupts */
	outb(0xff, ICEMT1724(ice, DMA_INT_MASK));
	outb(0xff, ICEREG1724(ice, IRQMASK));
	/* --- */
__hw_end:
	अगर (ice->irq >= 0)
		मुक्त_irq(ice->irq, ice);
	pci_release_regions(ice->pci);
	snd_ice1712_akm4xxx_मुक्त(ice);
	pci_disable_device(ice->pci);
	kमुक्त(ice->spec);
	kमुक्त(ice);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ice1712 *ice = device->device_data;
	वापस snd_vt1724_मुक्त(ice);
पूर्ण

अटल पूर्णांक snd_vt1724_create(काष्ठा snd_card *card,
			     काष्ठा pci_dev *pci,
			     स्थिर अक्षर *modelname,
			     काष्ठा snd_ice1712 **r_ice1712)
अणु
	काष्ठा snd_ice1712 *ice;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_vt1724_dev_मुक्त,
	पूर्ण;

	*r_ice1712 = शून्य;

	/* enable PCI device */
	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	ice = kzalloc(माप(*ice), GFP_KERNEL);
	अगर (ice == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	ice->vt1724 = 1;
	spin_lock_init(&ice->reg_lock);
	mutex_init(&ice->gpio_mutex);
	mutex_init(&ice->खोलो_mutex);
	mutex_init(&ice->i2c_mutex);
	ice->gpio.set_mask = snd_vt1724_set_gpio_mask;
	ice->gpio.get_mask = snd_vt1724_get_gpio_mask;
	ice->gpio.set_dir = snd_vt1724_set_gpio_dir;
	ice->gpio.get_dir = snd_vt1724_get_gpio_dir;
	ice->gpio.set_data = snd_vt1724_set_gpio_data;
	ice->gpio.get_data = snd_vt1724_get_gpio_data;
	ice->card = card;
	ice->pci = pci;
	ice->irq = -1;
	pci_set_master(pci);
	snd_vt1724_proc_init(ice);

	card->निजी_data = ice;

	err = pci_request_regions(pci, "ICE1724");
	अगर (err < 0) अणु
		kमुक्त(ice);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	ice->port = pci_resource_start(pci, 0);
	ice->profi_port = pci_resource_start(pci, 1);

	अगर (request_irq(pci->irq, snd_vt1724_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, ice)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_vt1724_मुक्त(ice);
		वापस -EIO;
	पूर्ण

	ice->irq = pci->irq;
	card->sync_irq = ice->irq;

	snd_vt1724_chip_reset(ice);
	अगर (snd_vt1724_पढ़ो_eeprom(ice, modelname) < 0) अणु
		snd_vt1724_मुक्त(ice);
		वापस -EIO;
	पूर्ण
	अगर (snd_vt1724_chip_init(ice) < 0) अणु
		snd_vt1724_मुक्त(ice);
		वापस -EIO;
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, ice, &ops);
	अगर (err < 0) अणु
		snd_vt1724_मुक्त(ice);
		वापस err;
	पूर्ण

	*r_ice1712 = ice;
	वापस 0;
पूर्ण


/*
 *
 * Registration
 *
 */

अटल पूर्णांक snd_vt1724_probe(काष्ठा pci_dev *pci,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_ice1712 *ice;
	पूर्णांक pcm_dev = 0, err;
	स्थिर काष्ठा snd_ice1712_card_info * स्थिर *tbl, *c;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	म_नकल(card->driver, "ICE1724");
	म_नकल(card->लघुname, "ICEnsemble ICE1724");

	err = snd_vt1724_create(card, pci, model[dev], &ice);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	/* field init beक्रमe calling chip_init */
	ice->ext_घड़ी_count = 0;

	क्रम (tbl = card_tables; *tbl; tbl++) अणु
		क्रम (c = *tbl; c->name; c++) अणु
			अगर ((model[dev] && c->model &&
			     !म_भेद(model[dev], c->model)) ||
			    (c->subvenकरोr == ice->eeprom.subvenकरोr)) अणु
				म_नकल(card->लघुname, c->name);
				अगर (c->driver) /* specअगरic driver? */
					म_नकल(card->driver, c->driver);
				अगर (c->chip_init) अणु
					err = c->chip_init(ice);
					अगर (err < 0) अणु
						snd_card_मुक्त(card);
						वापस err;
					पूर्ण
				पूर्ण
				जाओ __found;
			पूर्ण
		पूर्ण
	पूर्ण
	c = &no_matched;
__found:
	/*
	* VT1724 has separate DMAs क्रम the analog and the SPDIF streams जबतक
	* ICE1712 has only one क्रम both (mixed up).
	*
	* Confusingly the analog PCM is named "professional" here because it
	* was called so in ice1712 driver, and vt1724 driver is derived from
	* ice1712 driver.
	*/
	ice->pro_rate_शेष = PRO_RATE_DEFAULT;
	अगर (!ice->is_spdअगर_master)
		ice->is_spdअगर_master = stdघड़ी_is_spdअगर_master;
	अगर (!ice->get_rate)
		ice->get_rate = stdघड़ी_get_rate;
	अगर (!ice->set_rate)
		ice->set_rate = stdघड़ी_set_rate;
	अगर (!ice->set_mclk)
		ice->set_mclk = stdघड़ी_set_mclk;
	अगर (!ice->set_spdअगर_घड़ी)
		ice->set_spdअगर_घड़ी = stdघड़ी_set_spdअगर_घड़ी;
	अगर (!ice->get_spdअगर_master_type)
		ice->get_spdअगर_master_type = stdघड़ी_get_spdअगर_master_type;
	अगर (!ice->ext_घड़ी_names)
		ice->ext_घड़ी_names = ext_घड़ी_names;
	अगर (!ice->ext_घड़ी_count)
		ice->ext_घड़ी_count = ARRAY_SIZE(ext_घड़ी_names);

	अगर (!ice->hw_rates)
		set_std_hw_rates(ice);

	err = snd_vt1724_pcm_profi(ice, pcm_dev++);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_vt1724_pcm_spdअगर(ice, pcm_dev++);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_vt1724_pcm_indep(ice, pcm_dev++);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_vt1724_ac97_mixer(ice);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_vt1724_build_controls(ice);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर (ice->pcm && ice->has_spdअगर) अणु /* has SPDIF I/O */
		err = snd_vt1724_spdअगर_build_controls(ice);
		अगर (err < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (c->build_controls) अणु
		err = c->build_controls(ice);
		अगर (err < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (!c->no_mpu401) अणु
		अगर (ice->eeprom.data[ICE_EEP2_SYSCONF] & VT1724_CFG_MPU401) अणु
			काष्ठा snd_rawmidi *rmidi;

			err = snd_rawmidi_new(card, "MIDI", 0, 1, 1, &rmidi);
			अगर (err < 0) अणु
				snd_card_मुक्त(card);
				वापस err;
			पूर्ण
			ice->rmidi[0] = rmidi;
			rmidi->निजी_data = ice;
			म_नकल(rmidi->name, "ICE1724 MIDI");
			rmidi->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
					    SNDRV_RAWMIDI_INFO_INPUT |
					    SNDRV_RAWMIDI_INFO_DUPLEX;
			snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
					    &vt1724_midi_output_ops);
			snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
					    &vt1724_midi_input_ops);

			/* set watermarks */
			outb(VT1724_MPU_RX_FIFO | 0x1,
			     ICEREG1724(ice, MPU_FIFO_WM));
			outb(0x1, ICEREG1724(ice, MPU_FIFO_WM));
			/* set UART mode */
			outb(VT1724_MPU_UART, ICEREG1724(ice, MPU_CTRL));
		पूर्ण
	पूर्ण

	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i",
		card->लघुname, ice->port, ice->irq);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_vt1724_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा snd_card *card = pci_get_drvdata(pci);
	काष्ठा snd_ice1712 *ice = card->निजी_data;

	अगर (ice->card_info && ice->card_info->chip_निकास)
		ice->card_info->chip_निकास(ice);
	snd_card_मुक्त(card);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_vt1724_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ice1712 *ice = card->निजी_data;

	अगर (!ice->pm_suspend_enabled)
		वापस 0;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	snd_ac97_suspend(ice->ac97);

	spin_lock_irq(&ice->reg_lock);
	ice->pm_saved_is_spdअगर_master = ice->is_spdअगर_master(ice);
	ice->pm_saved_spdअगर_ctrl = inw(ICEMT1724(ice, SPDIF_CTRL));
	ice->pm_saved_spdअगर_cfg = inb(ICEREG1724(ice, SPDIF_CFG));
	ice->pm_saved_route = inl(ICEMT1724(ice, ROUTE_PLAYBACK));
	spin_unlock_irq(&ice->reg_lock);

	अगर (ice->pm_suspend)
		ice->pm_suspend(ice);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ice1712 *ice = card->निजी_data;

	अगर (!ice->pm_suspend_enabled)
		वापस 0;

	snd_vt1724_chip_reset(ice);

	अगर (snd_vt1724_chip_init(ice) < 0) अणु
		snd_card_disconnect(card);
		वापस -EIO;
	पूर्ण

	अगर (ice->pm_resume)
		ice->pm_resume(ice);

	अगर (ice->pm_saved_is_spdअगर_master) अणु
		/* चयनing to बाह्यal घड़ी via SPDIF */
		ice->set_spdअगर_घड़ी(ice, 0);
	पूर्ण अन्यथा अणु
		/* पूर्णांकernal on-card घड़ी */
		पूर्णांक rate;
		अगर (ice->cur_rate)
			rate = ice->cur_rate;
		अन्यथा
			rate = ice->pro_rate_शेष;
		snd_vt1724_set_pro_rate(ice, rate, 1);
	पूर्ण

	update_spdअगर_bits(ice, ice->pm_saved_spdअगर_ctrl);

	outb(ice->pm_saved_spdअगर_cfg, ICEREG1724(ice, SPDIF_CFG));
	outl(ice->pm_saved_route, ICEMT1724(ice, ROUTE_PLAYBACK));

	snd_ac97_resume(ice->ac97);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_vt1724_pm, snd_vt1724_suspend, snd_vt1724_resume);
#घोषणा SND_VT1724_PM_OPS	&snd_vt1724_pm
#अन्यथा
#घोषणा SND_VT1724_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver vt1724_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_vt1724_ids,
	.probe = snd_vt1724_probe,
	.हटाओ = snd_vt1724_हटाओ,
	.driver = अणु
		.pm = SND_VT1724_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(vt1724_driver);
