<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *   Lowlevel functions क्रम Terratec EWS88MT/D, EWX24/96, DMX 6Fire
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 *                    2002 Takashi Iwai <tiwai@suse.de>
 */      

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/cs8427.h>
#समावेश <sound/asoundef.h>

#समावेश "ice1712.h"
#समावेश "ews.h"

#घोषणा SND_CS8404
#समावेश <sound/cs8403.h>

क्रमागत अणु
	EWS_I2C_CS8404 = 0, EWS_I2C_PCF1, EWS_I2C_PCF2,
	EWS_I2C_88D = 0,
	EWS_I2C_6FIRE = 0
पूर्ण;
	

/* additional i2c devices क्रम EWS boards */
काष्ठा ews_spec अणु
	काष्ठा snd_i2c_device *i2cdevs[3];
पूर्ण;

/*
 * access via i2c mode (क्रम EWX 24/96, EWS 88MT&D)
 */

/* send SDA and SCL */
अटल व्योम ewx_i2c_setlines(काष्ठा snd_i2c_bus *bus, पूर्णांक clk, पूर्णांक data)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	अचिन्हित अक्षर पंचांगp = 0;
	अगर (clk)
		पंचांगp |= ICE1712_EWX2496_SERIAL_CLOCK;
	अगर (data)
		पंचांगp |= ICE1712_EWX2496_SERIAL_DATA;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, पंचांगp);
	udelay(5);
पूर्ण

अटल पूर्णांक ewx_i2c_अ_लोlock(काष्ठा snd_i2c_bus *bus)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	वापस snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA) & ICE1712_EWX2496_SERIAL_CLOCK ? 1 : 0;
पूर्ण

अटल पूर्णांक ewx_i2c_getdata(काष्ठा snd_i2c_bus *bus, पूर्णांक ack)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	पूर्णांक bit;
	/* set RW pin to low */
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~ICE1712_EWX2496_RW);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, 0);
	अगर (ack)
		udelay(5);
	bit = snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA) & ICE1712_EWX2496_SERIAL_DATA ? 1 : 0;
	/* set RW pin to high */
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, ICE1712_EWX2496_RW);
	/* reset ग_लिखो mask */
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~ICE1712_EWX2496_SERIAL_CLOCK);
	वापस bit;
पूर्ण

अटल व्योम ewx_i2c_start(काष्ठा snd_i2c_bus *bus)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	अचिन्हित अक्षर mask;

	snd_ice1712_save_gpio_status(ice);
	/* set RW high */
	mask = ICE1712_EWX2496_RW;
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_EWX2496:
		mask |= ICE1712_EWX2496_AK4524_CS; /* CS high also */
		अवरोध;
	हाल ICE1712_SUBDEVICE_DMX6FIRE:
		mask |= ICE1712_6FIRE_AK4524_CS_MASK; /* CS high also */
		अवरोध;
	पूर्ण
	snd_ice1712_gpio_ग_लिखो_bits(ice, mask, mask);
पूर्ण

अटल व्योम ewx_i2c_stop(काष्ठा snd_i2c_bus *bus)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	snd_ice1712_restore_gpio_status(ice);
पूर्ण

अटल व्योम ewx_i2c_direction(काष्ठा snd_i2c_bus *bus, पूर्णांक घड़ी, पूर्णांक data)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	अचिन्हित अक्षर mask = 0;

	अगर (घड़ी)
		mask |= ICE1712_EWX2496_SERIAL_CLOCK; /* ग_लिखो SCL */
	अगर (data)
		mask |= ICE1712_EWX2496_SERIAL_DATA; /* ग_लिखो SDA */
	ice->gpio.direction &= ~(ICE1712_EWX2496_SERIAL_CLOCK|ICE1712_EWX2496_SERIAL_DATA);
	ice->gpio.direction |= mask;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_सूचीECTION, ice->gpio.direction);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~mask);
पूर्ण

अटल काष्ठा snd_i2c_bit_ops snd_ice1712_ewx_cs8427_bit_ops = अणु
	.start = ewx_i2c_start,
	.stop = ewx_i2c_stop,
	.direction = ewx_i2c_direction,
	.setlines = ewx_i2c_setlines,
	.अ_लोlock = ewx_i2c_अ_लोlock,
	.getdata = ewx_i2c_getdata,
पूर्ण;


/*
 * AK4524 access
 */

/* AK4524 chip select; address 0x48 bit 0-3 */
अटल पूर्णांक snd_ice1712_ews88mt_chip_select(काष्ठा snd_ice1712 *ice, पूर्णांक chip_mask)
अणु
	काष्ठा ews_spec *spec = ice->spec;
	अचिन्हित अक्षर data, ndata;

	अगर (snd_BUG_ON(chip_mask < 0 || chip_mask > 0x0f))
		वापस -EINVAL;
	snd_i2c_lock(ice->i2c);
	अगर (snd_i2c_पढ़ोbytes(spec->i2cdevs[EWS_I2C_PCF2], &data, 1) != 1)
		जाओ __error;
	ndata = (data & 0xf0) | chip_mask;
	अगर (ndata != data)
		अगर (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_PCF2], &ndata, 1)
		    != 1)
			जाओ __error;
	snd_i2c_unlock(ice->i2c);
	वापस 0;

     __error:
	snd_i2c_unlock(ice->i2c);
	dev_err(ice->card->dev,
		"AK4524 chip select failed, check cable to the front module\n");
	वापस -EIO;
पूर्ण

/* start callback क्रम EWS88MT, needs to select a certain chip mask */
अटल व्योम ews88mt_ak4524_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];
	अचिन्हित अक्षर पंचांगp;
	/* निश्चित AK4524 CS */
	अगर (snd_ice1712_ews88mt_chip_select(ice, ~(1 << chip) & 0x0f) < 0)
		dev_err(ice->card->dev, "fatal error (ews88mt chip select)\n");
	snd_ice1712_save_gpio_status(ice);
	पंचांगp = ICE1712_EWS88_SERIAL_DATA |
		ICE1712_EWS88_SERIAL_CLOCK |
		ICE1712_EWS88_RW;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_सूचीECTION,
			  ice->gpio.direction | पंचांगp);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~पंचांगp);
पूर्ण

/* stop callback क्रम EWS88MT, needs to deselect chip mask */
अटल व्योम ews88mt_ak4524_unlock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];
	snd_ice1712_restore_gpio_status(ice);
	udelay(1);
	snd_ice1712_ews88mt_chip_select(ice, 0x0f);
पूर्ण

/* start callback क्रम EWX24/96 */
अटल व्योम ewx2496_ak4524_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];
	अचिन्हित अक्षर पंचांगp;
	snd_ice1712_save_gpio_status(ice);
	पंचांगp =  ICE1712_EWX2496_SERIAL_DATA |
		ICE1712_EWX2496_SERIAL_CLOCK |
		ICE1712_EWX2496_AK4524_CS |
		ICE1712_EWX2496_RW;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_सूचीECTION,
			  ice->gpio.direction | पंचांगp);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~पंचांगp);
पूर्ण

/* start callback क्रम DMX 6fire */
अटल व्योम dmx6fire_ak4524_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
	काष्ठा snd_ak4xxx_निजी *priv = (व्योम *)ak->निजी_value[0];
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];
	अचिन्हित अक्षर पंचांगp;
	snd_ice1712_save_gpio_status(ice);
	पंचांगp = priv->cs_mask = priv->cs_addr = (1 << chip) & ICE1712_6FIRE_AK4524_CS_MASK;
	पंचांगp |= ICE1712_6FIRE_SERIAL_DATA |
		ICE1712_6FIRE_SERIAL_CLOCK |
		ICE1712_6FIRE_RW;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_सूचीECTION,
			  ice->gpio.direction | पंचांगp);
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~पंचांगp);
पूर्ण

/*
 * CS8404 पूर्णांकerface on EWS88MT/D
 */

अटल व्योम snd_ice1712_ews_cs8404_spdअगर_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर bits)
अणु
	काष्ठा ews_spec *spec = ice->spec;
	अचिन्हित अक्षर bytes[2];

	snd_i2c_lock(ice->i2c);
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_EWS88MT:
	हाल ICE1712_SUBDEVICE_EWS88MT_NEW:
	हाल ICE1712_SUBDEVICE_PHASE88:
	हाल ICE1712_SUBDEVICE_TS88:
		अगर (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_CS8404], &bits, 1)
		    != 1)
			जाओ _error;
		अवरोध;
	हाल ICE1712_SUBDEVICE_EWS88D:
		अगर (snd_i2c_पढ़ोbytes(spec->i2cdevs[EWS_I2C_88D], bytes, 2)
		    != 2)
			जाओ _error;
		अगर (bits != bytes[1]) अणु
			bytes[1] = bits;
			अगर (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_88D],
					      bytes, 2) != 2)
				जाओ _error;
		पूर्ण
		अवरोध;
	पूर्ण
 _error:
	snd_i2c_unlock(ice->i2c);
पूर्ण

/*
 */

अटल व्योम ews88_spdअगर_शेष_get(काष्ठा snd_ice1712 *ice, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	snd_cs8404_decode_spdअगर_bits(&ucontrol->value.iec958, ice->spdअगर.cs8403_bits);
पूर्ण

अटल पूर्णांक ews88_spdअगर_शेष_put(काष्ठा snd_ice1712 *ice, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = snd_cs8404_encode_spdअगर_bits(&ucontrol->value.iec958);
	spin_lock_irq(&ice->reg_lock);
	change = ice->spdअगर.cs8403_bits != val;
	ice->spdअगर.cs8403_bits = val;
	अगर (change && ice->playback_pro_substream == शून्य) अणु
		spin_unlock_irq(&ice->reg_lock);
		snd_ice1712_ews_cs8404_spdअगर_ग_लिखो(ice, val);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&ice->reg_lock);
	पूर्ण
	वापस change;
पूर्ण

अटल व्योम ews88_spdअगर_stream_get(काष्ठा snd_ice1712 *ice, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	snd_cs8404_decode_spdअगर_bits(&ucontrol->value.iec958, ice->spdअगर.cs8403_stream_bits);
पूर्ण

अटल पूर्णांक ews88_spdअगर_stream_put(काष्ठा snd_ice1712 *ice, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = snd_cs8404_encode_spdअगर_bits(&ucontrol->value.iec958);
	spin_lock_irq(&ice->reg_lock);
	change = ice->spdअगर.cs8403_stream_bits != val;
	ice->spdअगर.cs8403_stream_bits = val;
	अगर (change && ice->playback_pro_substream != शून्य) अणु
		spin_unlock_irq(&ice->reg_lock);
		snd_ice1712_ews_cs8404_spdअगर_ग_लिखो(ice, val);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&ice->reg_lock);
	पूर्ण
	वापस change;
पूर्ण


/* खोलो callback */
अटल व्योम ews88_खोलो_spdअगर(काष्ठा snd_ice1712 *ice, काष्ठा snd_pcm_substream *substream)
अणु
	ice->spdअगर.cs8403_stream_bits = ice->spdअगर.cs8403_bits;
पूर्ण

/* set up SPDIF क्रम EWS88MT / EWS88D */
अटल व्योम ews88_setup_spdअगर(काष्ठा snd_ice1712 *ice, पूर्णांक rate)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक change;

	spin_lock_irqsave(&ice->reg_lock, flags);
	पंचांगp = ice->spdअगर.cs8403_stream_bits;
	अगर (पंचांगp & 0x10)		/* consumer */
		पंचांगp &= (पंचांगp & 0x01) ? ~0x06 : ~0x60;
	चयन (rate) अणु
	हाल 32000: पंचांगp |= (पंचांगp & 0x01) ? 0x02 : 0x00; अवरोध;
	हाल 44100: पंचांगp |= (पंचांगp & 0x01) ? 0x06 : 0x40; अवरोध;
	हाल 48000: पंचांगp |= (पंचांगp & 0x01) ? 0x04 : 0x20; अवरोध;
	शेष: पंचांगp |= (पंचांगp & 0x01) ? 0x06 : 0x40; अवरोध;
	पूर्ण
	change = ice->spdअगर.cs8403_stream_bits != पंचांगp;
	ice->spdअगर.cs8403_stream_bits = पंचांगp;
	spin_unlock_irqrestore(&ice->reg_lock, flags);
	अगर (change)
		snd_ctl_notअगरy(ice->card, SNDRV_CTL_EVENT_MASK_VALUE, &ice->spdअगर.stream_ctl->id);
	snd_ice1712_ews_cs8404_spdअगर_ग_लिखो(ice, पंचांगp);
पूर्ण


/*
 */
अटल स्थिर काष्ठा snd_akm4xxx akm_ews88mt = अणु
	.num_adcs = 8,
	.num_dacs = 8,
	.type = SND_AK4524,
	.ops = अणु
		.lock = ews88mt_ak4524_lock,
		.unlock = ews88mt_ak4524_unlock
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_ews88mt_priv = अणु
	.caddr = 2,
	.cअगर = 1, /* CIF high */
	.data_mask = ICE1712_EWS88_SERIAL_DATA,
	.clk_mask = ICE1712_EWS88_SERIAL_CLOCK,
	.cs_mask = 0,
	.cs_addr = 0,
	.cs_none = 0, /* no chip select on gpio */
	.add_flags = ICE1712_EWS88_RW, /* set rw bit high */
	.mask_flags = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_ewx2496 = अणु
	.num_adcs = 2,
	.num_dacs = 2,
	.type = SND_AK4524,
	.ops = अणु
		.lock = ewx2496_ak4524_lock
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_ewx2496_priv = अणु
	.caddr = 2,
	.cअगर = 1, /* CIF high */
	.data_mask = ICE1712_EWS88_SERIAL_DATA,
	.clk_mask = ICE1712_EWS88_SERIAL_CLOCK,
	.cs_mask = ICE1712_EWX2496_AK4524_CS,
	.cs_addr = ICE1712_EWX2496_AK4524_CS,
	.cs_none = 0,
	.add_flags = ICE1712_EWS88_RW, /* set rw bit high */
	.mask_flags = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_6fire = अणु
	.num_adcs = 6,
	.num_dacs = 6,
	.type = SND_AK4524,
	.ops = अणु
		.lock = dmx6fire_ak4524_lock
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_6fire_priv = अणु
	.caddr = 2,
	.cअगर = 1, /* CIF high */
	.data_mask = ICE1712_6FIRE_SERIAL_DATA,
	.clk_mask = ICE1712_6FIRE_SERIAL_CLOCK,
	.cs_mask = 0,
	.cs_addr = 0, /* set later */
	.cs_none = 0,
	.add_flags = ICE1712_6FIRE_RW, /* set rw bit high */
	.mask_flags = 0,
पूर्ण;

/*
 * initialize the chip
 */

/* 6fire specअगरic */
#घोषणा PCF9554_REG_INPUT      0
#घोषणा PCF9554_REG_OUTPUT     1
#घोषणा PCF9554_REG_POLARITY   2
#घोषणा PCF9554_REG_CONFIG     3

अटल पूर्णांक snd_ice1712_6fire_ग_लिखो_pca(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर reg, अचिन्हित अक्षर data);

अटल पूर्णांक snd_ice1712_ews_init(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err;
	काष्ठा snd_akm4xxx *ak;
	काष्ठा ews_spec *spec;

	/* set the analog DACs */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_EWX2496:
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 2;
		अवरोध;	
	हाल ICE1712_SUBDEVICE_EWS88MT:
	हाल ICE1712_SUBDEVICE_EWS88MT_NEW:
	हाल ICE1712_SUBDEVICE_PHASE88:
	हाल ICE1712_SUBDEVICE_TS88:
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 8;
		अवरोध;
	हाल ICE1712_SUBDEVICE_EWS88D:
		/* Note: not analog but ADAT I/O */
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 8;
		अवरोध;
	हाल ICE1712_SUBDEVICE_DMX6FIRE:
		ice->num_total_dacs = 6;
		ice->num_total_adcs = 6;
		अवरोध;
	पूर्ण

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

	/* create i2c */
	अगर ((err = snd_i2c_bus_create(ice->card, "ICE1712 GPIO 1", शून्य, &ice->i2c)) < 0) अणु
		dev_err(ice->card->dev, "unable to create I2C bus\n");
		वापस err;
	पूर्ण
	ice->i2c->निजी_data = ice;
	ice->i2c->hw_ops.bit = &snd_ice1712_ewx_cs8427_bit_ops;

	/* create i2c devices */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_DMX6FIRE:
		err = snd_i2c_device_create(ice->i2c, "PCF9554",
					    ICE1712_6FIRE_PCF9554_ADDR,
					    &spec->i2cdevs[EWS_I2C_6FIRE]);
		अगर (err < 0) अणु
			dev_err(ice->card->dev,
				"PCF9554 initialization failed\n");
			वापस err;
		पूर्ण
		snd_ice1712_6fire_ग_लिखो_pca(ice, PCF9554_REG_CONFIG, 0x80);
		अवरोध;
	हाल ICE1712_SUBDEVICE_EWS88MT:
	हाल ICE1712_SUBDEVICE_EWS88MT_NEW:
	हाल ICE1712_SUBDEVICE_PHASE88:
	हाल ICE1712_SUBDEVICE_TS88:

		err = snd_i2c_device_create(ice->i2c, "CS8404",
					    ICE1712_EWS88MT_CS8404_ADDR,
					    &spec->i2cdevs[EWS_I2C_CS8404]);
		अगर (err < 0)
			वापस err;
		err = snd_i2c_device_create(ice->i2c, "PCF8574 (1st)",
					    ICE1712_EWS88MT_INPUT_ADDR,
					    &spec->i2cdevs[EWS_I2C_PCF1]);
		अगर (err < 0)
			वापस err;
		err = snd_i2c_device_create(ice->i2c, "PCF8574 (2nd)",
					    ICE1712_EWS88MT_OUTPUT_ADDR,
					    &spec->i2cdevs[EWS_I2C_PCF2]);
		अगर (err < 0)
			वापस err;
		/* Check अगर the front module is connected */
		अगर ((err = snd_ice1712_ews88mt_chip_select(ice, 0x0f)) < 0)
			वापस err;
		अवरोध;
	हाल ICE1712_SUBDEVICE_EWS88D:
		err = snd_i2c_device_create(ice->i2c, "PCF8575",
					    ICE1712_EWS88D_PCF_ADDR,
					    &spec->i2cdevs[EWS_I2C_88D]);
		अगर (err < 0)
			वापस err;
		अवरोध;
	पूर्ण

	/* set up SPDIF पूर्णांकerface */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_EWX2496:
		अगर ((err = snd_ice1712_init_cs8427(ice, CS8427_BASE_ADDR)) < 0)
			वापस err;
		snd_cs8427_reg_ग_लिखो(ice->cs8427, CS8427_REG_RECVERRMASK, CS8427_UNLOCK | CS8427_CONF | CS8427_BIP | CS8427_PAR);
		अवरोध;
	हाल ICE1712_SUBDEVICE_DMX6FIRE:
		अगर ((err = snd_ice1712_init_cs8427(ice, ICE1712_6FIRE_CS8427_ADDR)) < 0)
			वापस err;
		snd_cs8427_reg_ग_लिखो(ice->cs8427, CS8427_REG_RECVERRMASK, CS8427_UNLOCK | CS8427_CONF | CS8427_BIP | CS8427_PAR);
		अवरोध;
	हाल ICE1712_SUBDEVICE_EWS88MT:
	हाल ICE1712_SUBDEVICE_EWS88MT_NEW:
	हाल ICE1712_SUBDEVICE_PHASE88:
	हाल ICE1712_SUBDEVICE_TS88:
	हाल ICE1712_SUBDEVICE_EWS88D:
		/* set up CS8404 */
		ice->spdअगर.ops.खोलो = ews88_खोलो_spdअगर;
		ice->spdअगर.ops.setup_rate = ews88_setup_spdअगर;
		ice->spdअगर.ops.शेष_get = ews88_spdअगर_शेष_get;
		ice->spdअगर.ops.शेष_put = ews88_spdअगर_शेष_put;
		ice->spdअगर.ops.stream_get = ews88_spdअगर_stream_get;
		ice->spdअगर.ops.stream_put = ews88_spdअगर_stream_put;
		/* Set spdअगर शेषs */
		snd_ice1712_ews_cs8404_spdअगर_ग_लिखो(ice, ice->spdअगर.cs8403_bits);
		अवरोध;
	पूर्ण

	/* no analog? */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_EWS88D:
		वापस 0;
	पूर्ण

	/* analog section */
	ak = ice->akm = kzalloc(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	अगर (! ak)
		वापस -ENOMEM;
	ice->akm_codecs = 1;

	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_EWS88MT:
	हाल ICE1712_SUBDEVICE_EWS88MT_NEW:
	हाल ICE1712_SUBDEVICE_PHASE88:
	हाल ICE1712_SUBDEVICE_TS88:
		err = snd_ice1712_akm4xxx_init(ak, &akm_ews88mt, &akm_ews88mt_priv, ice);
		अवरोध;
	हाल ICE1712_SUBDEVICE_EWX2496:
		err = snd_ice1712_akm4xxx_init(ak, &akm_ewx2496, &akm_ewx2496_priv, ice);
		अवरोध;
	हाल ICE1712_SUBDEVICE_DMX6FIRE:
		err = snd_ice1712_akm4xxx_init(ak, &akm_6fire, &akm_6fire_priv, ice);
		अवरोध;
	शेष:
		err = 0;
	पूर्ण

	वापस err;
पूर्ण

/*
 * EWX 24/96 specअगरic controls
 */

/* i/o sensitivity - this callback is shared among other devices, too */
अटल पूर्णांक snd_ice1712_ewx_io_sense_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)अणु

	अटल स्थिर अक्षर * स्थिर texts[2] = अणु
		"+4dBu", "-10dBV",
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_ice1712_ewx_io_sense_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर mask = kcontrol->निजी_value & 0xff;
	
	snd_ice1712_save_gpio_status(ice);
	ucontrol->value.क्रमागतerated.item[0] = snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA) & mask ? 1 : 0;
	snd_ice1712_restore_gpio_status(ice);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_ewx_io_sense_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर mask = kcontrol->निजी_value & 0xff;
	पूर्णांक val, nval;

	अगर (kcontrol->निजी_value & (1 << 31))
		वापस -EPERM;
	nval = ucontrol->value.क्रमागतerated.item[0] ? mask : 0;
	snd_ice1712_save_gpio_status(ice);
	val = snd_ice1712_पढ़ो(ice, ICE1712_IREG_GPIO_DATA);
	nval |= val & ~mask;
	snd_ice1712_ग_लिखो(ice, ICE1712_IREG_GPIO_DATA, nval);
	snd_ice1712_restore_gpio_status(ice);
	वापस val != nval;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_ewx2496_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Input Sensitivity Switch",
		.info = snd_ice1712_ewx_io_sense_info,
		.get = snd_ice1712_ewx_io_sense_get,
		.put = snd_ice1712_ewx_io_sense_put,
		.निजी_value = ICE1712_EWX2496_AIN_SEL,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Output Sensitivity Switch",
		.info = snd_ice1712_ewx_io_sense_info,
		.get = snd_ice1712_ewx_io_sense_get,
		.put = snd_ice1712_ewx_io_sense_put,
		.निजी_value = ICE1712_EWX2496_AOUT_SEL,
	पूर्ण,
पूर्ण;


/*
 * EWS88MT specअगरic controls
 */
/* analog output sensitivity;; address 0x48 bit 6 */
अटल पूर्णांक snd_ice1712_ews88mt_output_sense_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा ews_spec *spec = ice->spec;
	अचिन्हित अक्षर data;

	snd_i2c_lock(ice->i2c);
	अगर (snd_i2c_पढ़ोbytes(spec->i2cdevs[EWS_I2C_PCF2], &data, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	snd_i2c_unlock(ice->i2c);
	ucontrol->value.क्रमागतerated.item[0] = data & ICE1712_EWS88MT_OUTPUT_SENSE ? 1 : 0; /* high = -10dBV, low = +4dBu */
	वापस 0;
पूर्ण

/* analog output sensitivity;; address 0x48 bit 6 */
अटल पूर्णांक snd_ice1712_ews88mt_output_sense_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा ews_spec *spec = ice->spec;
	अचिन्हित अक्षर data, ndata;

	snd_i2c_lock(ice->i2c);
	अगर (snd_i2c_पढ़ोbytes(spec->i2cdevs[EWS_I2C_PCF2], &data, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	ndata = (data & ~ICE1712_EWS88MT_OUTPUT_SENSE) | (ucontrol->value.क्रमागतerated.item[0] ? ICE1712_EWS88MT_OUTPUT_SENSE : 0);
	अगर (ndata != data && snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_PCF2],
					       &ndata, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	snd_i2c_unlock(ice->i2c);
	वापस ndata != data;
पूर्ण

/* analog input sensitivity; address 0x46 */
अटल पूर्णांक snd_ice1712_ews88mt_input_sense_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा ews_spec *spec = ice->spec;
	पूर्णांक channel = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित अक्षर data;

	अगर (snd_BUG_ON(channel < 0 || channel > 7))
		वापस 0;
	snd_i2c_lock(ice->i2c);
	अगर (snd_i2c_पढ़ोbytes(spec->i2cdevs[EWS_I2C_PCF1], &data, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	/* reversed; high = +4dBu, low = -10dBV */
	ucontrol->value.क्रमागतerated.item[0] = data & (1 << channel) ? 0 : 1;
	snd_i2c_unlock(ice->i2c);
	वापस 0;
पूर्ण

/* analog output sensitivity; address 0x46 */
अटल पूर्णांक snd_ice1712_ews88mt_input_sense_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा ews_spec *spec = ice->spec;
	पूर्णांक channel = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित अक्षर data, ndata;

	अगर (snd_BUG_ON(channel < 0 || channel > 7))
		वापस 0;
	snd_i2c_lock(ice->i2c);
	अगर (snd_i2c_पढ़ोbytes(spec->i2cdevs[EWS_I2C_PCF1], &data, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	ndata = (data & ~(1 << channel)) | (ucontrol->value.क्रमागतerated.item[0] ? 0 : (1 << channel));
	अगर (ndata != data && snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_PCF1],
					       &ndata, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	snd_i2c_unlock(ice->i2c);
	वापस ndata != data;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_ews88mt_input_sense = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Input Sensitivity Switch",
	.info = snd_ice1712_ewx_io_sense_info,
	.get = snd_ice1712_ews88mt_input_sense_get,
	.put = snd_ice1712_ews88mt_input_sense_put,
	.count = 8,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_ews88mt_output_sense = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Output Sensitivity Switch",
	.info = snd_ice1712_ewx_io_sense_info,
	.get = snd_ice1712_ews88mt_output_sense_get,
	.put = snd_ice1712_ews88mt_output_sense_put,
पूर्ण;


/*
 * EWS88D specअगरic controls
 */

#घोषणा snd_ice1712_ews88d_control_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ice1712_ews88d_control_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा ews_spec *spec = ice->spec;
	पूर्णांक shअगरt = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 8) & 1;
	अचिन्हित अक्षर data[2];
	
	snd_i2c_lock(ice->i2c);
	अगर (snd_i2c_पढ़ोbytes(spec->i2cdevs[EWS_I2C_88D], data, 2) != 2) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	snd_i2c_unlock(ice->i2c);
	data[0] = (data[shअगरt >> 3] >> (shअगरt & 7)) & 0x01;
	अगर (invert)
		data[0] ^= 0x01;
	ucontrol->value.पूर्णांकeger.value[0] = data[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_ews88d_control_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा ews_spec *spec = ice->spec;
	पूर्णांक shअगरt = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 8) & 1;
	अचिन्हित अक्षर data[2], ndata[2];
	पूर्णांक change;

	snd_i2c_lock(ice->i2c);
	अगर (snd_i2c_पढ़ोbytes(spec->i2cdevs[EWS_I2C_88D], data, 2) != 2) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	ndata[shअगरt >> 3] = data[shअगरt >> 3] & ~(1 << (shअगरt & 7));
	अगर (invert) अणु
		अगर (! ucontrol->value.पूर्णांकeger.value[0])
			ndata[shअगरt >> 3] |= (1 << (shअगरt & 7));
	पूर्ण अन्यथा अणु
		अगर (ucontrol->value.पूर्णांकeger.value[0])
			ndata[shअगरt >> 3] |= (1 << (shअगरt & 7));
	पूर्ण
	change = (data[shअगरt >> 3] != ndata[shअगरt >> 3]);
	अगर (change &&
	    snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_88D], data, 2) != 2) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	snd_i2c_unlock(ice->i2c);
	वापस change;
पूर्ण

#घोषणा EWS88D_CONTROL(xअगरace, xname, xshअगरt, xinvert, xaccess) \
अणु .अगरace = xअगरace,\
  .name = xname,\
  .access = xaccess,\
  .info = snd_ice1712_ews88d_control_info,\
  .get = snd_ice1712_ews88d_control_get,\
  .put = snd_ice1712_ews88d_control_put,\
  .निजी_value = xshअगरt | (xinvert << 8),\
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_ews88d_controls[] = अणु
	EWS88D_CONTROL(SNDRV_CTL_ELEM_IFACE_MIXER, "IEC958 Input Optical", 0, 1, 0), /* inverted */
	EWS88D_CONTROL(SNDRV_CTL_ELEM_IFACE_MIXER, "ADAT Output Optical", 1, 0, 0),
	EWS88D_CONTROL(SNDRV_CTL_ELEM_IFACE_MIXER, "ADAT External Master Clock", 2, 0, 0),
	EWS88D_CONTROL(SNDRV_CTL_ELEM_IFACE_MIXER, "Enable ADAT", 3, 0, 0),
	EWS88D_CONTROL(SNDRV_CTL_ELEM_IFACE_MIXER, "ADAT Through", 4, 1, 0),
पूर्ण;


/*
 * DMX 6Fire specअगरic controls
 */

अटल पूर्णांक snd_ice1712_6fire_पढ़ो_pca(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर byte;
	काष्ठा ews_spec *spec = ice->spec;

	snd_i2c_lock(ice->i2c);
	byte = reg;
	अगर (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_6FIRE], &byte, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		dev_err(ice->card->dev, "cannot send pca\n");
		वापस -EIO;
	पूर्ण

	byte = 0;
	अगर (snd_i2c_पढ़ोbytes(spec->i2cdevs[EWS_I2C_6FIRE], &byte, 1) != 1) अणु
		snd_i2c_unlock(ice->i2c);
		dev_err(ice->card->dev, "cannot read pca\n");
		वापस -EIO;
	पूर्ण
	snd_i2c_unlock(ice->i2c);
	वापस byte;
पूर्ण

अटल पूर्णांक snd_ice1712_6fire_ग_लिखो_pca(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर reg, अचिन्हित अक्षर data)
अणु
	अचिन्हित अक्षर bytes[2];
	काष्ठा ews_spec *spec = ice->spec;

	snd_i2c_lock(ice->i2c);
	bytes[0] = reg;
	bytes[1] = data;
	अगर (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_6FIRE], bytes, 2) != 2) अणु
		snd_i2c_unlock(ice->i2c);
		वापस -EIO;
	पूर्ण
	snd_i2c_unlock(ice->i2c);
	वापस 0;
पूर्ण

#घोषणा snd_ice1712_6fire_control_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ice1712_6fire_control_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक shअगरt = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 8) & 1;
	पूर्णांक data;
	
	अगर ((data = snd_ice1712_6fire_पढ़ो_pca(ice, PCF9554_REG_OUTPUT)) < 0)
		वापस data;
	data = (data >> shअगरt) & 1;
	अगर (invert)
		data ^= 1;
	ucontrol->value.पूर्णांकeger.value[0] = data;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_6fire_control_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक shअगरt = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 8) & 1;
	पूर्णांक data, ndata;
	
	अगर ((data = snd_ice1712_6fire_पढ़ो_pca(ice, PCF9554_REG_OUTPUT)) < 0)
		वापस data;
	ndata = data & ~(1 << shअगरt);
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		ndata |= (1 << shअगरt);
	अगर (invert)
		ndata ^= (1 << shअगरt);
	अगर (data != ndata) अणु
		snd_ice1712_6fire_ग_लिखो_pca(ice, PCF9554_REG_OUTPUT, (अचिन्हित अक्षर)ndata);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_6fire_select_input_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"Internal", "Front Input", "Rear Input", "Wave Table"
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण
     
अटल पूर्णांक snd_ice1712_6fire_select_input_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक data;
	
	अगर ((data = snd_ice1712_6fire_पढ़ो_pca(ice, PCF9554_REG_OUTPUT)) < 0)
		वापस data;
	ucontrol->value.पूर्णांकeger.value[0] = data & 3;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ice1712_6fire_select_input_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक data, ndata;
	
	अगर ((data = snd_ice1712_6fire_पढ़ो_pca(ice, PCF9554_REG_OUTPUT)) < 0)
		वापस data;
	ndata = data & ~3;
	ndata |= (ucontrol->value.पूर्णांकeger.value[0] & 3);
	अगर (data != ndata) अणु
		snd_ice1712_6fire_ग_लिखो_pca(ice, PCF9554_REG_OUTPUT, (अचिन्हित अक्षर)ndata);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


#घोषणा DMX6FIRE_CONTROL(xname, xshअगरt, xinvert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,\
  .name = xname,\
  .info = snd_ice1712_6fire_control_info,\
  .get = snd_ice1712_6fire_control_get,\
  .put = snd_ice1712_6fire_control_put,\
  .निजी_value = xshअगरt | (xinvert << 8),\
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ice1712_6fire_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Input Select",
		.info = snd_ice1712_6fire_select_input_info,
		.get = snd_ice1712_6fire_select_input_get,
		.put = snd_ice1712_6fire_select_input_put,
	पूर्ण,
	DMX6FIRE_CONTROL("Front Digital Input Switch", 2, 1),
	// DMX6FIRE_CONTROL("Master Clock Select", 3, 0),
	DMX6FIRE_CONTROL("Optical Digital Input Switch", 4, 0),
	DMX6FIRE_CONTROL("Phono Analog Input Switch", 5, 0),
	DMX6FIRE_CONTROL("Breakbox LED", 6, 0),
पूर्ण;


अटल पूर्णांक snd_ice1712_ews_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;
	
	/* all terratec cards have spdअगर, but cs8427 module builds it's own controls */
	अगर (ice->cs8427 == शून्य) अणु
		err = snd_ice1712_spdअगर_build_controls(ice);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* ak4524 controls */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_EWX2496:
	हाल ICE1712_SUBDEVICE_EWS88MT:
	हाल ICE1712_SUBDEVICE_EWS88MT_NEW:
	हाल ICE1712_SUBDEVICE_PHASE88:
	हाल ICE1712_SUBDEVICE_TS88:
	हाल ICE1712_SUBDEVICE_DMX6FIRE:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		अगर (err < 0)
			वापस err;
		अवरोध;
	पूर्ण

	/* card specअगरic controls */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल ICE1712_SUBDEVICE_EWX2496:
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_ice1712_ewx2496_controls); idx++) अणु
			err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_ewx2496_controls[idx], ice));
			अगर (err < 0)
				वापस err;
		पूर्ण
		अवरोध;
	हाल ICE1712_SUBDEVICE_EWS88MT:
	हाल ICE1712_SUBDEVICE_EWS88MT_NEW:
	हाल ICE1712_SUBDEVICE_PHASE88:
	हाल ICE1712_SUBDEVICE_TS88:
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_ews88mt_input_sense, ice));
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_ews88mt_output_sense, ice));
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल ICE1712_SUBDEVICE_EWS88D:
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_ice1712_ews88d_controls); idx++) अणु
			err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_ews88d_controls[idx], ice));
			अगर (err < 0)
				वापस err;
		पूर्ण
		अवरोध;
	हाल ICE1712_SUBDEVICE_DMX6FIRE:
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_ice1712_6fire_controls); idx++) अणु
			err = snd_ctl_add(ice->card, snd_ctl_new1(&snd_ice1712_6fire_controls[idx], ice));
			अगर (err < 0)
				वापस err;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_ice1712_ews_cards[] = अणु
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_EWX2496,
		.name = "TerraTec EWX24/96",
		.model = "ewx2496",
		.chip_init = snd_ice1712_ews_init,
		.build_controls = snd_ice1712_ews_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_EWS88MT,
		.name = "TerraTec EWS88MT",
		.model = "ews88mt",
		.chip_init = snd_ice1712_ews_init,
		.build_controls = snd_ice1712_ews_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_EWS88MT_NEW,
		.name = "TerraTec EWS88MT",
		.model = "ews88mt_new",
		.chip_init = snd_ice1712_ews_init,
		.build_controls = snd_ice1712_ews_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_PHASE88,
		.name = "TerraTec Phase88",
		.model = "phase88",
		.chip_init = snd_ice1712_ews_init,
		.build_controls = snd_ice1712_ews_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_TS88,
		.name = "terrasoniq TS88",
		.model = "phase88",
		.chip_init = snd_ice1712_ews_init,
		.build_controls = snd_ice1712_ews_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_EWS88D,
		.name = "TerraTec EWS88D",
		.model = "ews88d",
		.chip_init = snd_ice1712_ews_init,
		.build_controls = snd_ice1712_ews_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = ICE1712_SUBDEVICE_DMX6FIRE,
		.name = "TerraTec DMX6Fire",
		.model = "dmx6fire",
		.chip_init = snd_ice1712_ews_init,
		.build_controls = snd_ice1712_ews_add_controls,
		.mpu401_1_name = "MIDI-Front DMX6fire",
		.mpu401_2_name = "Wavetable DMX6fire",
		.mpu401_2_info_flags = MPU401_INFO_OUTPUT,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
