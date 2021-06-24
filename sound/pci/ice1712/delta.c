<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *   Lowlevel functions क्रम M-Audio Delta 1010, 1010E, 44, 66, 66E, Dio2496,
 *			    Audiophile, Digigram VX442
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */      

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश <sound/cs8427.h>
#समावेश <sound/asoundef.h>

#समावेश "ice1712.h"
#समावेश "delta.h"

#घोषणा SND_CS8403
#समावेश <sound/cs8403.h>


/*
 * CS8427 via SPI mode (क्रम Audiophile), emulated I2C
 */

/* send 8 bits */
अटल व्योम ap_cs8427_ग_लिखो_byte(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर data, अचिन्हित अक्षर पंचांगp)
अणु
	पूर्णांक idx;

	क्रम (idx = 7; idx >= 0; idx--) अणु
		पंचांगp &= ~(ICE1712_DELTA_AP_DOUT|ICE1712_DELTA_AP_CCLK);
		अगर (data & (1 << idx))
			पंचांगp |= ICE1712_DELTA_AP_DOUT;
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
		udelay(5);
		पंचांगp |= ICE1712_DELTA_AP_CCLK;
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
		udelay(5);
	पूर्ण
पूर्ण

/* पढ़ो 8 bits */
अटल अचिन्हित अक्षर ap_cs8427_पढ़ो_byte(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर पंचांगp)
अणु
	अचिन्हित अक्षर data = 0;
	पूर्णांक idx;
	
	क्रम (idx = 7; idx >= 0; idx--) अणु
		पंचांगp &= ~ICE1712_DELTA_AP_CCLK;
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
		udelay(5);
		अगर (snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA) & ICE1712_DELTA_AP_DIN)
			data |= 1 << idx;
		पंचांगp |= ICE1712_DELTA_AP_CCLK;
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
		udelay(5);
	पूर्ण
	वापस data;
पूर्ण

/* निश्चित chip select */
अटल अचिन्हित अक्षर ap_cs8427_codec_select(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित अक्षर पंचांगp;
	पंचांगp = snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA);
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_DELTA1010E:
	हाल ICE1712_SUBDEVICE_DELTA1010LT:
		पंचांगp &= ~ICE1712_DELTA_1010LT_CS;
		पंचांगp |= ICE1712_DELTA_1010LT_CCLK | ICE1712_DELTA_1010LT_CS_CS8427;
		अवरोध;
	हाल ICE1712_SUBDEVICE_AUDIOPHILE:
	हाल ICE1712_SUBDEVICE_DELTA410:
		पंचांगp |= ICE1712_DELTA_AP_CCLK | ICE1712_DELTA_AP_CS_CODEC;
		पंचांगp &= ~ICE1712_DELTA_AP_CS_DIGITAL;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA66E:
		पंचांगp |= ICE1712_DELTA_66E_CCLK | ICE1712_DELTA_66E_CS_CHIP_A |
		       ICE1712_DELTA_66E_CS_CHIP_B;
		पंचांगp &= ~ICE1712_DELTA_66E_CS_CS8427;
		अवरोध;
	हाल ICE1712_SUBDEVICE_VX442:
		पंचांगp |= ICE1712_VX442_CCLK | ICE1712_VX442_CODEC_CHIP_A | ICE1712_VX442_CODEC_CHIP_B;
		पंचांगp &= ~ICE1712_VX442_CS_DIGITAL;
		अवरोध;
	पूर्ण
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
	udelay(5);
	वापस पंचांगp;
पूर्ण

/* deनिश्चित chip select */
अटल व्योम ap_cs8427_codec_deनिश्चित(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर पंचांगp)
अणु
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_DELTA1010E:
	हाल ICE1712_SUBDEVICE_DELTA1010LT:
		पंचांगp &= ~ICE1712_DELTA_1010LT_CS;
		पंचांगp |= ICE1712_DELTA_1010LT_CS_NONE;
		अवरोध;
	हाल ICE1712_SUBDEVICE_AUDIOPHILE:
	हाल ICE1712_SUBDEVICE_DELTA410:
		पंचांगp |= ICE1712_DELTA_AP_CS_DIGITAL;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA66E:
		पंचांगp |= ICE1712_DELTA_66E_CS_CS8427;
		अवरोध;
	हाल ICE1712_SUBDEVICE_VX442:
		पंचांगp |= ICE1712_VX442_CS_DIGITAL;
		अवरोध;
	पूर्ण
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
पूर्ण

/* sequential ग_लिखो */
अटल पूर्णांक ap_cs8427_sendbytes(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर *bytes, पूर्णांक count)
अणु
	काष्ठा snd_ice1712 *ice = device->bus->निजी_data;
	पूर्णांक res = count;
	अचिन्हित अक्षर पंचांगp;

	mutex_lock(&ice->gpio_mutex);
	पंचांगp = ap_cs8427_codec_select(ice);
	ap_cs8427_ग_लिखो_byte(ice, (device->addr << 1) | 0, पंचांगp); /* address + ग_लिखो mode */
	जबतक (count-- > 0)
		ap_cs8427_ग_लिखो_byte(ice, *bytes++, पंचांगp);
	ap_cs8427_codec_deनिश्चित(ice, पंचांगp);
	mutex_unlock(&ice->gpio_mutex);
	वापस res;
पूर्ण

/* sequential पढ़ो */
अटल पूर्णांक ap_cs8427_पढ़ोbytes(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर *bytes, पूर्णांक count)
अणु
	काष्ठा snd_ice1712 *ice = device->bus->निजी_data;
	पूर्णांक res = count;
	अचिन्हित अक्षर पंचांगp;
	
	mutex_lock(&ice->gpio_mutex);
	पंचांगp = ap_cs8427_codec_select(ice);
	ap_cs8427_ग_लिखो_byte(ice, (device->addr << 1) | 1, पंचांगp); /* address + पढ़ो mode */
	जबतक (count-- > 0)
		*bytes++ = ap_cs8427_पढ़ो_byte(ice, पंचांगp);
	ap_cs8427_codec_deनिश्चित(ice, पंचांगp);
	mutex_unlock(&ice->gpio_mutex);
	वापस res;
पूर्ण

अटल पूर्णांक ap_cs8427_probeaddr(काष्ठा snd_i2c_bus *bus, अचिन्हित लघु addr)
अणु
	अगर (addr == 0x10)
		वापस 1;
	वापस -ENOENT;
पूर्ण

अटल स्थिर काष्ठा snd_i2c_ops ap_cs8427_i2c_ops = अणु
	.sendbytes = ap_cs8427_sendbytes,
	.पढ़ोbytes = ap_cs8427_पढ़ोbytes,
	.probeaddr = ap_cs8427_probeaddr,
पूर्ण;

/*
 */

अटल व्योम snd_ice1712_delta_cs8403_spdअगर_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर bits)
अणु
	अचिन्हित अक्षर पंचांगp, mask1, mask2;
	पूर्णांक idx;
	/* send byte to transmitter */
	mask1 = ICE1712_DELTA_SPDIF_OUT_STAT_CLOCK;
	mask2 = ICE1712_DELTA_SPDIF_OUT_STAT_DATA;
	mutex_lock(&ice->gpio_mutex);
	पंचांगp = snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA);
	क्रम (idx = 7; idx >= 0; idx--) अणु
		पंचांगp &= ~(mask1 | mask2);
		अगर (bits & (1 << idx))
			पंचांगp |= mask2;
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
		udelay(100);
		पंचांगp |= mask1;
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
		udelay(100);
	पूर्ण
	पंचांगp &= ~mask1;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
	mutex_unlock(&ice->gpio_mutex);
पूर्ण


अटल व्योम delta_spdअगर_शेष_get(काष्ठा snd_ice1712 *ice, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	snd_cs8403_decode_spdअगर_bits(&ucontrol->value.iec958, ice->spdअगर.cs8403_bits);
पूर्ण

अटल पूर्णांक delta_spdअगर_शेष_put(काष्ठा snd_ice1712 *ice, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = snd_cs8403_encode_spdअगर_bits(&ucontrol->value.iec958);
	spin_lock_irq(&ice->reg_lock);
	change = ice->spdअगर.cs8403_bits != val;
	ice->spdअगर.cs8403_bits = val;
	अगर (change && ice->playback_pro_substream == शून्य) अणु
		spin_unlock_irq(&ice->reg_lock);
		snd_ice1712_delta_cs8403_spdअगर_ग_लिखो(ice, val);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&ice->reg_lock);
	पूर्ण
	वापस change;
पूर्ण

अटल व्योम delta_spdअगर_stream_get(काष्ठा snd_ice1712 *ice, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	snd_cs8403_decode_spdअगर_bits(&ucontrol->value.iec958, ice->spdअगर.cs8403_stream_bits);
पूर्ण

अटल पूर्णांक delta_spdअगर_stream_put(काष्ठा snd_ice1712 *ice, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = snd_cs8403_encode_spdअगर_bits(&ucontrol->value.iec958);
	spin_lock_irq(&ice->reg_lock);
	change = ice->spdअगर.cs8403_stream_bits != val;
	ice->spdअगर.cs8403_stream_bits = val;
	अगर (change && ice->playback_pro_substream != शून्य) अणु
		spin_unlock_irq(&ice->reg_lock);
		snd_ice1712_delta_cs8403_spdअगर_ग_लिखो(ice, val);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&ice->reg_lock);
	पूर्ण
	वापस change;
पूर्ण


/*
 * AK4524 on Delta 44 and 66 to choose the chip mask
 */
अटल व्योम delta_ak4524_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
        काष्ठा snd_ak4xxx_निजी *priv = (व्योम *)ak->निजी_value[0];
        काष्ठा snd_ice1712 *ice = ak->निजी_data[0];

	snd_ice1712_save_gpio_status(ice);
	priv->cs_mask =
	priv->cs_addr = chip == 0 ? ICE1712_DELTA_CODEC_CHIP_A :
				    ICE1712_DELTA_CODEC_CHIP_B;
पूर्ण

/*
 * AK4524 on Delta1010LT to choose the chip address
 */
अटल व्योम delta1010lt_ak4524_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
        काष्ठा snd_ak4xxx_निजी *priv = (व्योम *)ak->निजी_value[0];
        काष्ठा snd_ice1712 *ice = ak->निजी_data[0];

	snd_ice1712_save_gpio_status(ice);
	priv->cs_mask = ICE1712_DELTA_1010LT_CS;
	priv->cs_addr = chip << 4;
पूर्ण

/*
 * AK4524 on Delta66 rev E to choose the chip address
 */
अटल व्योम delta66e_ak4524_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
	काष्ठा snd_ak4xxx_निजी *priv = (व्योम *)ak->निजी_value[0];
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];

	snd_ice1712_save_gpio_status(ice);
	priv->cs_mask =
	priv->cs_addr = chip == 0 ? ICE1712_DELTA_66E_CS_CHIP_A :
				    ICE1712_DELTA_66E_CS_CHIP_B;
पूर्ण

/*
 * AK4528 on VX442 to choose the chip mask
 */
अटल व्योम vx442_ak4524_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
        काष्ठा snd_ak4xxx_निजी *priv = (व्योम *)ak->निजी_value[0];
        काष्ठा snd_ice1712 *ice = ak->निजी_data[0];

	snd_ice1712_save_gpio_status(ice);
	priv->cs_mask =
	priv->cs_addr = chip == 0 ? ICE1712_VX442_CODEC_CHIP_A :
				    ICE1712_VX442_CODEC_CHIP_B;
पूर्ण

/*
 * change the DFS bit according rate क्रम Delta1010
 */
अटल व्योम delta_1010_set_rate_val(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर पंचांगp, पंचांगp2;

	अगर (rate == 0)	/* no hपूर्णांक - S/PDIF input is master, simply वापस */
		वापस;

	mutex_lock(&ice->gpio_mutex);
	पंचांगp = snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA);
	पंचांगp2 = पंचांगp & ~ICE1712_DELTA_DFS;
	अगर (rate > 48000)
		पंचांगp2 |= ICE1712_DELTA_DFS;
	अगर (पंचांगp != पंचांगp2)
		snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp2);
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

/*
 * change the rate of AK4524 on Delta 44/66, AP, 1010LT
 */
अटल व्योम delta_ak4524_set_rate_val(काष्ठा snd_akm4xxx *ak, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर पंचांगp, पंचांगp2;
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];

	अगर (rate == 0)	/* no hपूर्णांक - S/PDIF input is master, simply वापस */
		वापस;

	/* check beक्रमe reset ak4524 to aव्योम unnecessary clicks */
	mutex_lock(&ice->gpio_mutex);
	पंचांगp = snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA);
	mutex_unlock(&ice->gpio_mutex);
	पंचांगp2 = पंचांगp & ~ICE1712_DELTA_DFS; 
	अगर (rate > 48000)
		पंचांगp2 |= ICE1712_DELTA_DFS;
	अगर (पंचांगp == पंचांगp2)
		वापस;

	/* करो it again */
	snd_akm4xxx_reset(ak, 1);
	mutex_lock(&ice->gpio_mutex);
	पंचांगp = snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA) & ~ICE1712_DELTA_DFS;
	अगर (rate > 48000)
		पंचांगp |= ICE1712_DELTA_DFS;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
	mutex_unlock(&ice->gpio_mutex);
	snd_akm4xxx_reset(ak, 0);
पूर्ण

/*
 * change the rate of AK4524 on VX442
 */
अटल व्योम vx442_ak4524_set_rate_val(काष्ठा snd_akm4xxx *ak, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर val;

	val = (rate > 48000) ? 0x65 : 0x60;
	अगर (snd_akm4xxx_get(ak, 0, 0x02) != val ||
	    snd_akm4xxx_get(ak, 1, 0x02) != val) अणु
		snd_akm4xxx_reset(ak, 1);
		snd_akm4xxx_ग_लिखो(ak, 0, 0x02, val);
		snd_akm4xxx_ग_लिखो(ak, 1, 0x02, val);
		snd_akm4xxx_reset(ak, 0);
	पूर्ण
पूर्ण


/*
 * SPDIF ops क्रम Delta 1010, Dio, 66
 */

/* खोलो callback */
अटल व्योम delta_खोलो_spdअगर(काष्ठा snd_ice1712 *ice, काष्ठा snd_pcm_substream *substream)
अणु
	ice->spdअगर.cs8403_stream_bits = ice->spdअगर.cs8403_bits;
पूर्ण

/* set up */
अटल व्योम delta_setup_spdअगर(काष्ठा snd_ice1712 *ice, पूर्णांक rate)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक change;

	spin_lock_irqsave(&ice->reg_lock, flags);
	पंचांगp = ice->spdअगर.cs8403_stream_bits;
	अगर (पंचांगp & 0x01)		/* consumer */
		पंचांगp &= (पंचांगp & 0x01) ? ~0x06 : ~0x18;
	चयन (rate) अणु
	हाल 32000: पंचांगp |= (पंचांगp & 0x01) ? 0x04 : 0x00; अवरोध;
	हाल 44100: पंचांगp |= (पंचांगp & 0x01) ? 0x00 : 0x10; अवरोध;
	हाल 48000: पंचांगp |= (पंचांगp & 0x01) ? 0x02 : 0x08; अवरोध;
	शेष: पंचांगp |= (पंचांगp & 0x01) ? 0x00 : 0x18; अवरोध;
	पूर्ण
	change = ice->spdअगर.cs8403_stream_bits != पंचांगp;
	ice->spdअगर.cs8403_stream_bits = पंचांगp;
	spin_unlock_irqrestore(&ice->reg_lock, flags);
	अगर (change)
		snd_ctl_notअगरy(ice->card, SNDRV_CTL_EVENT_MASK_VALUE, &ice->spdअगर.stream_ctl->id);
	snd_ice1712_delta_cs8403_spdअगर_ग_लिखो(ice, पंचांगp);
पूर्ण

#घोषणा snd_ice1712_delta1010lt_wordघड़ी_status_info \
	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ice1712_delta1010lt_wordघड़ी_status_get(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अक्षर reg = 0x10; /* CS8427 receiver error रेजिस्टर */
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	अगर (snd_i2c_sendbytes(ice->cs8427, &reg, 1) != 1)
		dev_err(ice->card->dev,
			"unable to send register 0x%x byte to CS8427\n", reg);
	snd_i2c_पढ़ोbytes(ice->cs8427, &reg, 1);
	ucontrol->value.पूर्णांकeger.value[0] = (reg & CS8427_UNLOCK) ? 1 : 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_delta1010lt_wordघड़ी_status =
अणु
	.access =	(SNDRV_CTL_ELEM_ACCESS_READ),
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Word Clock Status",
	.info =		snd_ice1712_delta1010lt_wordघड़ी_status_info,
	.get =		snd_ice1712_delta1010lt_wordघड़ी_status_get,
पूर्ण;

/*
 * initialize the chips on M-Audio cards
 */

अटल स्थिर काष्ठा snd_akm4xxx akm_audiophile = अणु
	.type = SND_AK4528,
	.num_adcs = 2,
	.num_dacs = 2,
	.ops = अणु
		.set_rate_val = delta_ak4524_set_rate_val
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_audiophile_priv = अणु
	.caddr = 2,
	.cअगर = 0,
	.data_mask = ICE1712_DELTA_AP_DOUT,
	.clk_mask = ICE1712_DELTA_AP_CCLK,
	.cs_mask = ICE1712_DELTA_AP_CS_CODEC,
	.cs_addr = ICE1712_DELTA_AP_CS_CODEC,
	.cs_none = 0,
	.add_flags = ICE1712_DELTA_AP_CS_DIGITAL,
	.mask_flags = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_delta410 = अणु
	.type = SND_AK4529,
	.num_adcs = 2,
	.num_dacs = 8,
	.ops = अणु
		.set_rate_val = delta_ak4524_set_rate_val
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_delta410_priv = अणु
	.caddr = 0,
	.cअगर = 0,
	.data_mask = ICE1712_DELTA_AP_DOUT,
	.clk_mask = ICE1712_DELTA_AP_CCLK,
	.cs_mask = ICE1712_DELTA_AP_CS_CODEC,
	.cs_addr = ICE1712_DELTA_AP_CS_CODEC,
	.cs_none = 0,
	.add_flags = ICE1712_DELTA_AP_CS_DIGITAL,
	.mask_flags = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_delta1010lt = अणु
	.type = SND_AK4524,
	.num_adcs = 8,
	.num_dacs = 8,
	.ops = अणु
		.lock = delta1010lt_ak4524_lock,
		.set_rate_val = delta_ak4524_set_rate_val
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_delta1010lt_priv = अणु
	.caddr = 2,
	.cअगर = 0, /* the शेष level of the CIF pin from AK4524 */
	.data_mask = ICE1712_DELTA_1010LT_DOUT,
	.clk_mask = ICE1712_DELTA_1010LT_CCLK,
	.cs_mask = 0,
	.cs_addr = 0, /* set later */
	.cs_none = ICE1712_DELTA_1010LT_CS_NONE,
	.add_flags = 0,
	.mask_flags = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_delta66e = अणु
	.type = SND_AK4524,
	.num_adcs = 4,
	.num_dacs = 4,
	.ops = अणु
		.lock = delta66e_ak4524_lock,
		.set_rate_val = delta_ak4524_set_rate_val
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_delta66e_priv = अणु
	.caddr = 2,
	.cअगर = 0, /* the शेष level of the CIF pin from AK4524 */
	.data_mask = ICE1712_DELTA_66E_DOUT,
	.clk_mask = ICE1712_DELTA_66E_CCLK,
	.cs_mask = 0,
	.cs_addr = 0, /* set later */
	.cs_none = 0,
	.add_flags = 0,
	.mask_flags = 0,
पूर्ण;


अटल स्थिर काष्ठा snd_akm4xxx akm_delta44 = अणु
	.type = SND_AK4524,
	.num_adcs = 4,
	.num_dacs = 4,
	.ops = अणु
		.lock = delta_ak4524_lock,
		.set_rate_val = delta_ak4524_set_rate_val
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_delta44_priv = अणु
	.caddr = 2,
	.cअगर = 0, /* the शेष level of the CIF pin from AK4524 */
	.data_mask = ICE1712_DELTA_CODEC_SERIAL_DATA,
	.clk_mask = ICE1712_DELTA_CODEC_SERIAL_CLOCK,
	.cs_mask = 0,
	.cs_addr = 0, /* set later */
	.cs_none = 0,
	.add_flags = 0,
	.mask_flags = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_vx442 = अणु
	.type = SND_AK4524,
	.num_adcs = 4,
	.num_dacs = 4,
	.ops = अणु
		.lock = vx442_ak4524_lock,
		.set_rate_val = vx442_ak4524_set_rate_val
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_vx442_priv = अणु
	.caddr = 2,
	.cअगर = 0,
	.data_mask = ICE1712_VX442_DOUT,
	.clk_mask = ICE1712_VX442_CCLK,
	.cs_mask = 0,
	.cs_addr = 0, /* set later */
	.cs_none = 0,
	.add_flags = 0,
	.mask_flags = 0,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_ice1712_delta_resume(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित अक्षर akm_img_bak[AK4XXX_IMAGE_SIZE];
	अचिन्हित अक्षर akm_vol_bak[AK4XXX_IMAGE_SIZE];

	/* init spdअगर */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_AUDIOPHILE:
	हाल ICE1712_SUBDEVICE_DELTA410:
	हाल ICE1712_SUBDEVICE_DELTA1010E:
	हाल ICE1712_SUBDEVICE_DELTA1010LT:
	हाल ICE1712_SUBDEVICE_VX442:
	हाल ICE1712_SUBDEVICE_DELTA66E:
		snd_cs8427_init(ice->i2c, ice->cs8427);
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA1010:
	हाल ICE1712_SUBDEVICE_MEDIASTATION:
		/* nothing */
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTADIO2496:
	हाल ICE1712_SUBDEVICE_DELTA66:
		/* Set spdअगर शेषs */
		snd_ice1712_delta_cs8403_spdअगर_ग_लिखो(ice, ice->spdअगर.cs8403_bits);
		अवरोध;
	पूर्ण

	/* init codec and restore रेजिस्टरs */
	अगर (ice->akm_codecs) अणु
		स_नकल(akm_img_bak, ice->akm->images, माप(akm_img_bak));
		स_नकल(akm_vol_bak, ice->akm->volumes, माप(akm_vol_bak));
		snd_akm4xxx_init(ice->akm);
		स_नकल(ice->akm->images, akm_img_bak, माप(akm_img_bak));
		स_नकल(ice->akm->volumes, akm_vol_bak, माप(akm_vol_bak));
		snd_akm4xxx_reset(ice->akm, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_delta_suspend(काष्ठा snd_ice1712 *ice)
अणु
	अगर (ice->akm_codecs) /* reset & mute codec */
		snd_akm4xxx_reset(ice->akm, 1);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_ice1712_delta_init(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err;
	काष्ठा snd_akm4xxx *ak;
	अचिन्हित अक्षर पंचांगp;

	अगर (ice->eeprom.subvenकरोr == ICE1712_SUBDEVICE_DELTA1010 &&
	    ice->eeprom.gpiodir == 0x7b)
		ice->eeprom.subvenकरोr = ICE1712_SUBDEVICE_DELTA1010E;

	अगर (ice->eeprom.subvenकरोr == ICE1712_SUBDEVICE_DELTA66 &&
	    ice->eeprom.gpiodir == 0xfb)
	    	ice->eeprom.subvenकरोr = ICE1712_SUBDEVICE_DELTA66E;

	/* determine I2C, DACs and ADCs */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_AUDIOPHILE:
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 2;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA410:
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA44:
	हाल ICE1712_SUBDEVICE_DELTA66:
		ice->num_total_dacs = ice->omni ? 8 : 4;
		ice->num_total_adcs = ice->omni ? 8 : 4;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA1010:
	हाल ICE1712_SUBDEVICE_DELTA1010E:
	हाल ICE1712_SUBDEVICE_DELTA1010LT:
	हाल ICE1712_SUBDEVICE_MEDIASTATION:
	हाल ICE1712_SUBDEVICE_EसूचीOLDA2496:
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 8;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTADIO2496:
		ice->num_total_dacs = 4;	/* two AK4324 codecs */
		अवरोध;
	हाल ICE1712_SUBDEVICE_VX442:
	हाल ICE1712_SUBDEVICE_DELTA66E:	/* omni not supported yet */
		ice->num_total_dacs = 4;
		ice->num_total_adcs = 4;
		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_PM_SLEEP
	ice->pm_resume = snd_ice1712_delta_resume;
	ice->pm_suspend = snd_ice1712_delta_suspend;
	ice->pm_suspend_enabled = 1;
#पूर्ण_अगर
	/* initialize the SPI घड़ी to high */
	पंचांगp = snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA);
	पंचांगp |= ICE1712_DELTA_AP_CCLK;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
	udelay(5);

	/* initialize spdअगर */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_AUDIOPHILE:
	हाल ICE1712_SUBDEVICE_DELTA410:
	हाल ICE1712_SUBDEVICE_DELTA1010E:
	हाल ICE1712_SUBDEVICE_DELTA1010LT:
	हाल ICE1712_SUBDEVICE_VX442:
	हाल ICE1712_SUBDEVICE_DELTA66E:
		अगर ((err = snd_i2c_bus_create(ice->card, "ICE1712 GPIO 1", शून्य, &ice->i2c)) < 0) अणु
			dev_err(ice->card->dev, "unable to create I2C bus\n");
			वापस err;
		पूर्ण
		ice->i2c->निजी_data = ice;
		ice->i2c->ops = &ap_cs8427_i2c_ops;
		अगर ((err = snd_ice1712_init_cs8427(ice, CS8427_BASE_ADDR)) < 0)
			वापस err;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA1010:
	हाल ICE1712_SUBDEVICE_MEDIASTATION:
		ice->gpio.set_pro_rate = delta_1010_set_rate_val;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTADIO2496:
		ice->gpio.set_pro_rate = delta_1010_set_rate_val;
		fallthrough;
	हाल ICE1712_SUBDEVICE_DELTA66:
		ice->spdअगर.ops.खोलो = delta_खोलो_spdअगर;
		ice->spdअगर.ops.setup_rate = delta_setup_spdअगर;
		ice->spdअगर.ops.शेष_get = delta_spdअगर_शेष_get;
		ice->spdअगर.ops.शेष_put = delta_spdअगर_शेष_put;
		ice->spdअगर.ops.stream_get = delta_spdअगर_stream_get;
		ice->spdअगर.ops.stream_put = delta_spdअगर_stream_put;
		/* Set spdअगर शेषs */
		snd_ice1712_delta_cs8403_spdअगर_ग_लिखो(ice, ice->spdअगर.cs8403_bits);
		अवरोध;
	पूर्ण

	/* no analog? */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_DELTA1010:
	हाल ICE1712_SUBDEVICE_DELTA1010E:
	हाल ICE1712_SUBDEVICE_DELTADIO2496:
	हाल ICE1712_SUBDEVICE_MEDIASTATION:
		वापस 0;
	पूर्ण

	/* second stage of initialization, analog parts and others */
	ak = ice->akm = kदो_स्मृति(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	अगर (! ak)
		वापस -ENOMEM;
	ice->akm_codecs = 1;

	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_AUDIOPHILE:
		err = snd_ice1712_akm4xxx_init(ak, &akm_audiophile, &akm_audiophile_priv, ice);
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA410:
		err = snd_ice1712_akm4xxx_init(ak, &akm_delta410, &akm_delta410_priv, ice);
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA1010LT:
	हाल ICE1712_SUBDEVICE_EसूचीOLDA2496:
		err = snd_ice1712_akm4xxx_init(ak, &akm_delta1010lt, &akm_delta1010lt_priv, ice);
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA66:
	हाल ICE1712_SUBDEVICE_DELTA44:
		err = snd_ice1712_akm4xxx_init(ak, &akm_delta44, &akm_delta44_priv, ice);
		अवरोध;
	हाल ICE1712_SUBDEVICE_VX442:
		err = snd_ice1712_akm4xxx_init(ak, &akm_vx442, &akm_vx442_priv, ice);
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA66E:
		err = snd_ice1712_akm4xxx_init(ak, &akm_delta66e, &akm_delta66e_priv, ice);
		अवरोध;
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण


/*
 * additional controls क्रम M-Audio cards
 */

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_delta1010_wordघड़ी_select =
ICE1712_GPIO(SNDRV_CTL_ELEM_IFACE_MIXER, "Word Clock Sync", 0, ICE1712_DELTA_WORD_CLOCK_SELECT, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_delta1010lt_wordघड़ी_select =
ICE1712_GPIO(SNDRV_CTL_ELEM_IFACE_MIXER, "Word Clock Sync", 0, ICE1712_DELTA_1010LT_WORDCLOCK, 0, 0);
अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_delta1010_wordघड़ी_status =
ICE1712_GPIO(SNDRV_CTL_ELEM_IFACE_MIXER, "Word Clock Status", 0, ICE1712_DELTA_WORD_CLOCK_STATUS, 1, SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE);
अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_deltadio2496_spdअगर_in_select =
ICE1712_GPIO(SNDRV_CTL_ELEM_IFACE_MIXER, "IEC958 Input Optical", 0, ICE1712_DELTA_SPDIF_INPUT_SELECT, 0, 0);
अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_delta_spdअगर_in_status =
ICE1712_GPIO(SNDRV_CTL_ELEM_IFACE_MIXER, "Delta IEC958 Input Status", 0, ICE1712_DELTA_SPDIF_IN_STAT, 1, SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE);


अटल पूर्णांक snd_ice1712_delta_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err;

	/* 1010 and dio specअगरic controls */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_DELTA1010:
	हाल ICE1712_SUBDEVICE_MEDIASTATION:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta1010_wordघड़ी_select, ice));
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta1010_wordघड़ी_status, ice));
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTADIO2496:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_deltadio2496_spdअगर_in_select, ice));
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DELTA1010E:
	हाल ICE1712_SUBDEVICE_DELTA1010LT:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta1010lt_wordघड़ी_select, ice));
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta1010lt_wordघड़ी_status, ice));
		अगर (err < 0)
			वापस err;
		अवरोध;
	पूर्ण

	/* normal spdअगर controls */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_DELTA1010:
	हाल ICE1712_SUBDEVICE_DELTADIO2496:
	हाल ICE1712_SUBDEVICE_DELTA66:
	हाल ICE1712_SUBDEVICE_MEDIASTATION:
		err = snd_ice1712_spdअगर_build_controls(ice);
		अगर (err < 0)
			वापस err;
		अवरोध;
	पूर्ण

	/* spdअगर status in */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_DELTA1010:
	हाल ICE1712_SUBDEVICE_DELTADIO2496:
	हाल ICE1712_SUBDEVICE_DELTA66:
	हाल ICE1712_SUBDEVICE_MEDIASTATION:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_delta_spdअगर_in_status, ice));
		अगर (err < 0)
			वापस err;
		अवरोध;
	पूर्ण

	/* ak4524 controls */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_DELTA1010LT:
	हाल ICE1712_SUBDEVICE_AUDIOPHILE:
	हाल ICE1712_SUBDEVICE_DELTA410:
	हाल ICE1712_SUBDEVICE_DELTA44:
	हाल ICE1712_SUBDEVICE_DELTA66:
	हाल ICE1712_SUBDEVICE_VX442:
	हाल ICE1712_SUBDEVICE_DELTA66E:
	हाल ICE1712_SUBDEVICE_EसूचीOLDA2496:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		अगर (err < 0)
			वापस err;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_ice1712_delta_cards[] = अणु
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_DELTA1010,
		.name = "M Audio Delta 1010",
		.model = "delta1010",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_DELTADIO2496,
		.name = "M Audio Delta DiO 2496",
		.model = "dio2496",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
		.no_mpu401 = 1,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_DELTA66,
		.name = "M Audio Delta 66",
		.model = "delta66",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
		.no_mpu401 = 1,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_DELTA44,
		.name = "M Audio Delta 44",
		.model = "delta44",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
		.no_mpu401 = 1,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_AUDIOPHILE,
		.name = "M Audio Audiophile 24/96",
		.model = "audiophile",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_DELTA410,
		.name = "M Audio Delta 410",
		.model = "delta410",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_DELTA1010LT,
		.name = "M Audio Delta 1010LT",
		.model = "delta1010lt",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_VX442,
		.name = "Digigram VX442",
		.model = "vx442",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
		.no_mpu401 = 1,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_MEDIASTATION,
		.name = "Lionstracs Mediastation",
		.model = "mediastation",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_EसूचीOLDA2496,
		.name = "Edirol DA2496",
		.model = "da2496",
		.chip_init = snd_ice1712_delta_init,
		.build_controls = snd_ice1712_delta_add_controls,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
