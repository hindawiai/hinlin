<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *   Lowlevel functions क्रम M-Audio Audiophile 192, Revolution 7.1 and 5.1
 *
 *	Copyright (c) 2003 Takashi Iwai <tiwai@suse.de>
 */      

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "revo.h"

/* a non-standard I2C device क्रम revo51 */
काष्ठा revo51_spec अणु
	काष्ठा snd_i2c_device *dev;
	काष्ठा snd_pt2258 *pt2258;
	काष्ठा ak4114 *ak4114;
पूर्ण;

अटल व्योम revo_i2s_mclk_changed(काष्ठा snd_ice1712 *ice)
अणु
	/* निश्चित PRST# to converters; MT05 bit 7 */
	outb(inb(ICEMT1724(ice, AC97_CMD)) | 0x80, ICEMT1724(ice, AC97_CMD));
	mdelay(5);
	/* deनिश्चित PRST# */
	outb(inb(ICEMT1724(ice, AC97_CMD)) & ~0x80, ICEMT1724(ice, AC97_CMD));
पूर्ण

/*
 * change the rate of Envy24HT, AK4355 and AK4381
 */
अटल व्योम revo_set_rate_val(काष्ठा snd_akm4xxx *ak, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर old, पंचांगp, dfs;
	पूर्णांक reg, shअगरt;

	अगर (rate == 0)	/* no hपूर्णांक - S/PDIF input is master, simply वापस */
		वापस;

	/* adjust DFS on codecs */
	अगर (rate > 96000)
		dfs = 2;
	अन्यथा अगर (rate > 48000)
		dfs = 1;
	अन्यथा
		dfs = 0;

	अगर (ak->type == SND_AK4355 || ak->type == SND_AK4358) अणु
		reg = 2;
		shअगरt = 4;
	पूर्ण अन्यथा अणु
		reg = 1;
		shअगरt = 3;
	पूर्ण
	पंचांगp = snd_akm4xxx_get(ak, 0, reg);
	old = (पंचांगp >> shअगरt) & 0x03;
	अगर (old == dfs)
		वापस;

	/* reset DFS */
	snd_akm4xxx_reset(ak, 1);
	पंचांगp = snd_akm4xxx_get(ak, 0, reg);
	पंचांगp &= ~(0x03 << shअगरt);
	पंचांगp |= dfs << shअगरt;
	/* snd_akm4xxx_ग_लिखो(ak, 0, reg, पंचांगp); */
	snd_akm4xxx_set(ak, 0, reg, पंचांगp); /* value is written in reset(0) */
	snd_akm4xxx_reset(ak, 0);
पूर्ण

/*
 * I2C access to the PT2258 volume controller on GPIO 6/7 (Revolution 5.1)
 */

अटल व्योम revo_i2c_start(काष्ठा snd_i2c_bus *bus)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	snd_ice1712_save_gpio_status(ice);
पूर्ण

अटल व्योम revo_i2c_stop(काष्ठा snd_i2c_bus *bus)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	snd_ice1712_restore_gpio_status(ice);
पूर्ण

अटल व्योम revo_i2c_direction(काष्ठा snd_i2c_bus *bus, पूर्णांक घड़ी, पूर्णांक data)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	अचिन्हित पूर्णांक mask, val;

	val = 0;
	अगर (घड़ी)
		val |= VT1724_REVO_I2C_CLOCK;	/* ग_लिखो SCL */
	अगर (data)
		val |= VT1724_REVO_I2C_DATA;	/* ग_लिखो SDA */
	mask = VT1724_REVO_I2C_CLOCK | VT1724_REVO_I2C_DATA;
	ice->gpio.direction &= ~mask;
	ice->gpio.direction |= val;
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
	snd_ice1712_gpio_set_mask(ice, ~mask);
पूर्ण

अटल व्योम revo_i2c_setlines(काष्ठा snd_i2c_bus *bus, पूर्णांक clk, पूर्णांक data)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	अचिन्हित पूर्णांक val = 0;

	अगर (clk)
		val |= VT1724_REVO_I2C_CLOCK;
	अगर (data)
		val |= VT1724_REVO_I2C_DATA;
	snd_ice1712_gpio_ग_लिखो_bits(ice,
				    VT1724_REVO_I2C_DATA |
				    VT1724_REVO_I2C_CLOCK, val);
	udelay(5);
पूर्ण

अटल पूर्णांक revo_i2c_getdata(काष्ठा snd_i2c_bus *bus, पूर्णांक ack)
अणु
	काष्ठा snd_ice1712 *ice = bus->निजी_data;
	पूर्णांक bit;

	अगर (ack)
		udelay(5);
	bit = snd_ice1712_gpio_पढ़ो_bits(ice, VT1724_REVO_I2C_DATA) ? 1 : 0;
	वापस bit;
पूर्ण

अटल काष्ठा snd_i2c_bit_ops revo51_bit_ops = अणु
	.start = revo_i2c_start,
	.stop = revo_i2c_stop,
	.direction = revo_i2c_direction,
	.setlines = revo_i2c_setlines,
	.getdata = revo_i2c_getdata,
पूर्ण;

अटल पूर्णांक revo51_i2c_init(काष्ठा snd_ice1712 *ice,
			   काष्ठा snd_pt2258 *pt)
अणु
	काष्ठा revo51_spec *spec;
	पूर्णांक err;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

	/* create the I2C bus */
	err = snd_i2c_bus_create(ice->card, "ICE1724 GPIO6", शून्य, &ice->i2c);
	अगर (err < 0)
		वापस err;

	ice->i2c->निजी_data = ice;
	ice->i2c->hw_ops.bit = &revo51_bit_ops;

	/* create the I2C device */
	err = snd_i2c_device_create(ice->i2c, "PT2258", 0x40, &spec->dev);
	अगर (err < 0)
		वापस err;

	pt->card = ice->card;
	pt->i2c_bus = ice->i2c;
	pt->i2c_dev = spec->dev;
	spec->pt2258 = pt;

	snd_pt2258_reset(pt);

	वापस 0;
पूर्ण

/*
 * initialize the chips on M-Audio Revolution cards
 */

#घोषणा AK_DAC(xname,xch) अणु .name = xname, .num_channels = xch पूर्ण

अटल स्थिर काष्ठा snd_akm4xxx_dac_channel revo71_front[] = अणु
	अणु
		.name = "PCM Playback Volume",
		.num_channels = 2,
		/* front channels DAC supports muting */
		.चयन_name = "PCM Playback Switch",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx_dac_channel revo71_surround[] = अणु
	AK_DAC("PCM Center Playback Volume", 1),
	AK_DAC("PCM LFE Playback Volume", 1),
	AK_DAC("PCM Side Playback Volume", 2),
	AK_DAC("PCM Rear Playback Volume", 2),
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx_dac_channel revo51_dac[] = अणु
	AK_DAC("PCM Playback Volume", 2),
	AK_DAC("PCM Center Playback Volume", 1),
	AK_DAC("PCM LFE Playback Volume", 1),
	AK_DAC("PCM Rear Playback Volume", 2),
	AK_DAC("PCM Headphone Volume", 2),
पूर्ण;

अटल स्थिर अक्षर *revo51_adc_input_names[] = अणु
	"Mic",
	"Line",
	"CD",
	शून्य
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx_adc_channel revo51_adc[] = अणु
	अणु
		.name = "PCM Capture Volume",
		.चयन_name = "PCM Capture Switch",
		.num_channels = 2,
		.input_names = revo51_adc_input_names
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_revo_front = अणु
	.type = SND_AK4381,
	.num_dacs = 2,
	.ops = अणु
		.set_rate_val = revo_set_rate_val
	पूर्ण,
	.dac_info = revo71_front,
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_revo_front_priv = अणु
	.caddr = 1,
	.cअगर = 0,
	.data_mask = VT1724_REVO_CDOUT,
	.clk_mask = VT1724_REVO_CCLK,
	.cs_mask = VT1724_REVO_CS0 | VT1724_REVO_CS1 | VT1724_REVO_CS2,
	.cs_addr = VT1724_REVO_CS0 | VT1724_REVO_CS2,
	.cs_none = VT1724_REVO_CS0 | VT1724_REVO_CS1 | VT1724_REVO_CS2,
	.add_flags = VT1724_REVO_CCLK, /* high at init */
	.mask_flags = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_revo_surround = अणु
	.type = SND_AK4355,
	.idx_offset = 1,
	.num_dacs = 6,
	.ops = अणु
		.set_rate_val = revo_set_rate_val
	पूर्ण,
	.dac_info = revo71_surround,
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_revo_surround_priv = अणु
	.caddr = 3,
	.cअगर = 0,
	.data_mask = VT1724_REVO_CDOUT,
	.clk_mask = VT1724_REVO_CCLK,
	.cs_mask = VT1724_REVO_CS0 | VT1724_REVO_CS1 | VT1724_REVO_CS2,
	.cs_addr = VT1724_REVO_CS0 | VT1724_REVO_CS1,
	.cs_none = VT1724_REVO_CS0 | VT1724_REVO_CS1 | VT1724_REVO_CS2,
	.add_flags = VT1724_REVO_CCLK, /* high at init */
	.mask_flags = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_revo51 = अणु
	.type = SND_AK4358,
	.num_dacs = 8,
	.ops = अणु
		.set_rate_val = revo_set_rate_val
	पूर्ण,
	.dac_info = revo51_dac,
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_revo51_priv = अणु
	.caddr = 2,
	.cअगर = 0,
	.data_mask = VT1724_REVO_CDOUT,
	.clk_mask = VT1724_REVO_CCLK,
	.cs_mask = VT1724_REVO_CS0 | VT1724_REVO_CS1,
	.cs_addr = VT1724_REVO_CS1,
	.cs_none = VT1724_REVO_CS0 | VT1724_REVO_CS1,
	.add_flags = VT1724_REVO_CCLK, /* high at init */
	.mask_flags = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_revo51_adc = अणु
	.type = SND_AK5365,
	.num_adcs = 2,
	.adc_info = revo51_adc,
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_revo51_adc_priv = अणु
	.caddr = 2,
	.cअगर = 0,
	.data_mask = VT1724_REVO_CDOUT,
	.clk_mask = VT1724_REVO_CCLK,
	.cs_mask = VT1724_REVO_CS0 | VT1724_REVO_CS1,
	.cs_addr = VT1724_REVO_CS0,
	.cs_none = VT1724_REVO_CS0 | VT1724_REVO_CS1,
	.add_flags = VT1724_REVO_CCLK, /* high at init */
	.mask_flags = 0,
पूर्ण;

अटल काष्ठा snd_pt2258 ptc_revo51_volume;

/* AK4358 क्रम AP192 DAC, AK5385A क्रम ADC */
अटल व्योम ap192_set_rate_val(काष्ठा snd_akm4xxx *ak, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];
	पूर्णांक dfs;

	revo_set_rate_val(ak, rate);

	/* reset CKS */
	snd_ice1712_gpio_ग_लिखो_bits(ice, 1 << 8, rate > 96000 ? 1 << 8 : 0);
	/* reset DFS pins of AK5385A क्रम ADC, too */
	अगर (rate > 96000)
		dfs = 2;
	अन्यथा अगर (rate > 48000)
		dfs = 1;
	अन्यथा
		dfs = 0;
	snd_ice1712_gpio_ग_लिखो_bits(ice, 3 << 9, dfs << 9);
	/* reset ADC */
	snd_ice1712_gpio_ग_लिखो_bits(ice, 1 << 11, 0);
	snd_ice1712_gpio_ग_लिखो_bits(ice, 1 << 11, 1 << 11);
पूर्ण

अटल स्थिर काष्ठा snd_akm4xxx_dac_channel ap192_dac[] = अणु
	AK_DAC("PCM Playback Volume", 2)
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_ap192 = अणु
	.type = SND_AK4358,
	.num_dacs = 2,
	.ops = अणु
		.set_rate_val = ap192_set_rate_val
	पूर्ण,
	.dac_info = ap192_dac,
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_ap192_priv = अणु
	.caddr = 2,
	.cअगर = 0,
	.data_mask = VT1724_REVO_CDOUT,
	.clk_mask = VT1724_REVO_CCLK,
	.cs_mask = VT1724_REVO_CS0 | VT1724_REVO_CS3,
	.cs_addr = VT1724_REVO_CS3,
	.cs_none = VT1724_REVO_CS0 | VT1724_REVO_CS3,
	.add_flags = VT1724_REVO_CCLK, /* high at init */
	.mask_flags = 0,
पूर्ण;

/* AK4114 support on Audiophile 192 */
/* CDTO (pin 32) -- GPIO2 pin 52
 * CDTI (pin 33) -- GPIO3 pin 53 (shared with AK4358)
 * CCLK (pin 34) -- GPIO1 pin 51 (shared with AK4358)
 * CSN  (pin 35) -- GPIO7 pin 59
 */
#घोषणा AK4114_ADDR	0x00

अटल व्योम ग_लिखो_data(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक gpio,
		       अचिन्हित पूर्णांक data, पूर्णांक idx)
अणु
	क्रम (; idx >= 0; idx--) अणु
		/* drop घड़ी */
		gpio &= ~VT1724_REVO_CCLK;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
		/* set data */
		अगर (data & (1 << idx))
			gpio |= VT1724_REVO_CDOUT;
		अन्यथा
			gpio &= ~VT1724_REVO_CDOUT;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
		/* उठाओ घड़ी */
		gpio |= VT1724_REVO_CCLK;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
	पूर्ण
पूर्ण

अटल अचिन्हित अक्षर पढ़ो_data(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक gpio,
			       पूर्णांक idx)
अणु
	अचिन्हित अक्षर data = 0;

	क्रम (; idx >= 0; idx--) अणु
		/* drop घड़ी */
		gpio &= ~VT1724_REVO_CCLK;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
		/* पढ़ो data */
		अगर (snd_ice1712_gpio_पढ़ो(ice) & VT1724_REVO_CDIN)
			data |= (1 << idx);
		udelay(1);
		/* उठाओ घड़ी */
		gpio |= VT1724_REVO_CCLK;
		snd_ice1712_gpio_ग_लिखो(ice, gpio);
		udelay(1);
	पूर्ण
	वापस data;
पूर्ण

अटल अचिन्हित पूर्णांक ap192_4wire_start(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	snd_ice1712_save_gpio_status(ice);
	पंचांगp = snd_ice1712_gpio_पढ़ो(ice);
	पंचांगp |= VT1724_REVO_CCLK; /* high at init */
	पंचांगp |= VT1724_REVO_CS0;
	पंचांगp &= ~VT1724_REVO_CS3;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	वापस पंचांगp;
पूर्ण

अटल व्योम ap192_4wire_finish(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक पंचांगp)
अणु
	पंचांगp |= VT1724_REVO_CS3;
	पंचांगp |= VT1724_REVO_CS0;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	snd_ice1712_restore_gpio_status(ice);
पूर्ण

अटल व्योम ap192_ak4114_ग_लिखो(व्योम *निजी_data, अचिन्हित अक्षर addr,
			       अचिन्हित अक्षर data)
अणु
	काष्ठा snd_ice1712 *ice = निजी_data;
	अचिन्हित पूर्णांक पंचांगp, addrdata;

	पंचांगp = ap192_4wire_start(ice);
	addrdata = (AK4114_ADDR << 6) | 0x20 | (addr & 0x1f);
	addrdata = (addrdata << 8) | data;
	ग_लिखो_data(ice, पंचांगp, addrdata, 15);
	ap192_4wire_finish(ice, पंचांगp);
पूर्ण

अटल अचिन्हित अक्षर ap192_ak4114_पढ़ो(व्योम *निजी_data, अचिन्हित अक्षर addr)
अणु
	काष्ठा snd_ice1712 *ice = निजी_data;
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित अक्षर data;

	पंचांगp = ap192_4wire_start(ice);
	ग_लिखो_data(ice, पंचांगp, (AK4114_ADDR << 6) | (addr & 0x1f), 7);
	data = पढ़ो_data(ice, पंचांगp, 7);
	ap192_4wire_finish(ice, पंचांगp);
	वापस data;
पूर्ण

अटल पूर्णांक ap192_ak4114_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित अक्षर ak4114_init_vals[] = अणु
		AK4114_RST | AK4114_PWN | AK4114_OCKS0,
		AK4114_DIF_I24I2S,
		AK4114_TX1E,
		AK4114_EFH_1024 | AK4114_DIT | AK4114_IPS(0),
		0,
		0
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर ak4114_init_txcsb[] = अणु
		0x41, 0x02, 0x2c, 0x00, 0x00
	पूर्ण;
	पूर्णांक err;

	काष्ठा revo51_spec *spec;
	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

	err = snd_ak4114_create(ice->card,
				 ap192_ak4114_पढ़ो,
				 ap192_ak4114_ग_लिखो,
				 ak4114_init_vals, ak4114_init_txcsb,
				 ice, &spec->ak4114);
	अगर (err < 0)
		वापस err;
	/* AK4114 in Revo cannot detect बाह्यal rate correctly.
	 * No reason to stop capture stream due to incorrect checks */
	spec->ak4114->check_flags = AK4114_CHECK_NO_RATE;

	वापस 0;
पूर्ण

अटल पूर्णांक revo_init(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा snd_akm4xxx *ak;
	पूर्णांक err;

	/* determine I2C, DACs and ADCs */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल VT1724_SUBDEVICE_REVOLUTION71:
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
		ice->gpio.i2s_mclk_changed = revo_i2s_mclk_changed;
		अवरोध;
	हाल VT1724_SUBDEVICE_REVOLUTION51:
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
		अवरोध;
	हाल VT1724_SUBDEVICE_AUDIOPHILE192:
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 2;
		अवरोध;
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण

	/* second stage of initialization, analog parts and others */
	ak = ice->akm = kसुस्मृति(2, माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	अगर (! ak)
		वापस -ENOMEM;
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल VT1724_SUBDEVICE_REVOLUTION71:
		ice->akm_codecs = 2;
		err = snd_ice1712_akm4xxx_init(ak, &akm_revo_front,
						&akm_revo_front_priv, ice);
		अगर (err < 0)
			वापस err;
		err = snd_ice1712_akm4xxx_init(ak+1, &akm_revo_surround,
						&akm_revo_surround_priv, ice);
		अगर (err < 0)
			वापस err;
		/* unmute all codecs */
		snd_ice1712_gpio_ग_लिखो_bits(ice, VT1724_REVO_MUTE,
						VT1724_REVO_MUTE);
		अवरोध;
	हाल VT1724_SUBDEVICE_REVOLUTION51:
		ice->akm_codecs = 2;
		err = snd_ice1712_akm4xxx_init(ak, &akm_revo51,
					       &akm_revo51_priv, ice);
		अगर (err < 0)
			वापस err;
		err = snd_ice1712_akm4xxx_init(ak+1, &akm_revo51_adc,
					       &akm_revo51_adc_priv, ice);
		अगर (err < 0)
			वापस err;
		err = revo51_i2c_init(ice, &ptc_revo51_volume);
		अगर (err < 0)
			वापस err;
		/* unmute all codecs */
		snd_ice1712_gpio_ग_लिखो_bits(ice, VT1724_REVO_MUTE,
					    VT1724_REVO_MUTE);
		अवरोध;
	हाल VT1724_SUBDEVICE_AUDIOPHILE192:
		ice->akm_codecs = 1;
		err = snd_ice1712_akm4xxx_init(ak, &akm_ap192, &akm_ap192_priv,
					       ice);
		अगर (err < 0)
			वापस err;
		err = ap192_ak4114_init(ice);
		अगर (err < 0)
			वापस err;
		
		/* unmute all codecs */
		snd_ice1712_gpio_ग_लिखो_bits(ice, VT1724_REVO_MUTE,
					    VT1724_REVO_MUTE);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक revo_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा revo51_spec *spec = ice->spec;
	पूर्णांक err;

	चयन (ice->eeprom.subvenकरोr) अणु
	हाल VT1724_SUBDEVICE_REVOLUTION71:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल VT1724_SUBDEVICE_REVOLUTION51:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		अगर (err < 0)
			वापस err;
		spec = ice->spec;
		err = snd_pt2258_build_controls(spec->pt2258);
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल VT1724_SUBDEVICE_AUDIOPHILE192:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		अगर (err < 0)
			वापस err;
		/* only capture SPDIF over AK4114 */
		err = snd_ak4114_build(spec->ak4114, शून्य,
		   ice->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
		अगर (err < 0)
			वापस err;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1724_revo_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_REVOLUTION71,
		.name = "M Audio Revolution-7.1",
		.model = "revo71",
		.chip_init = revo_init,
		.build_controls = revo_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_REVOLUTION51,
		.name = "M Audio Revolution-5.1",
		.model = "revo51",
		.chip_init = revo_init,
		.build_controls = revo_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_AUDIOPHILE192,
		.name = "M Audio Audiophile192",
		.model = "ap192",
		.chip_init = revo_init,
		.build_controls = revo_add_controls,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
