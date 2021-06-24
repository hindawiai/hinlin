<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम Infrasonic Quartet
 *
 *	Copyright (c) 2009 Pavel Hofman <pavel.hofman@ivitera.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <sound/core.h>
#समावेश <sound/tlv.h>
#समावेश <sound/info.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश <sound/ak4113.h>
#समावेश "quartet.h"

काष्ठा qtet_spec अणु
	काष्ठा ak4113 *ak4113;
	अचिन्हित पूर्णांक scr;	/* प्रणाली control रेजिस्टर */
	अचिन्हित पूर्णांक mcr;	/* monitoring control रेजिस्टर */
	अचिन्हित पूर्णांक cpld;	/* cpld रेजिस्टर */
पूर्ण;

काष्ठा qtet_kcontrol_निजी अणु
	अचिन्हित पूर्णांक bit;
	व्योम (*set_रेजिस्टर)(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक val);
	अचिन्हित पूर्णांक (*get_रेजिस्टर)(काष्ठा snd_ice1712 *ice);
	स्थिर अक्षर * स्थिर texts[2];
पूर्ण;

क्रमागत अणु
	IN12_SEL = 0,
	IN34_SEL,
	AIN34_SEL,
	COAX_OUT,
	IN12_MON12,
	IN12_MON34,
	IN34_MON12,
	IN34_MON34,
	OUT12_MON34,
	OUT34_MON12,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ext_घड़ी_names[3] = अणु"IEC958 In", "Word Clock 1xFS",
	"Word Clock 256xFS"पूर्ण;

/* chip address on I2C bus */
#घोषणा AK4113_ADDR		0x26	/* S/PDIF receiver */

/* chip address on SPI bus */
#घोषणा AK4620_ADDR		0x02	/* ADC/DAC */


/*
 * GPIO pins
 */

/* GPIO0 - O - DATA0, def. 0 */
#घोषणा GPIO_D0			(1<<0)
/* GPIO1 - I/O - DATA1, Jack Detect Input0 (0:present, 1:missing), def. 1 */
#घोषणा GPIO_D1_JACKDTC0	(1<<1)
/* GPIO2 - I/O - DATA2, Jack Detect Input1 (0:present, 1:missing), def. 1 */
#घोषणा GPIO_D2_JACKDTC1	(1<<2)
/* GPIO3 - I/O - DATA3, def. 1 */
#घोषणा GPIO_D3			(1<<3)
/* GPIO4 - I/O - DATA4, SPI CDTO, def. 1 */
#घोषणा GPIO_D4_SPI_CDTO	(1<<4)
/* GPIO5 - I/O - DATA5, SPI CCLK, def. 1 */
#घोषणा GPIO_D5_SPI_CCLK	(1<<5)
/* GPIO6 - I/O - DATA6, Cable Detect Input (0:detected, 1:not detected */
#घोषणा GPIO_D6_CD		(1<<6)
/* GPIO7 - I/O - DATA7, Device Detect Input (0:detected, 1:not detected */
#घोषणा GPIO_D7_DD		(1<<7)
/* GPIO8 - O - CPLD Chip Select, def. 1 */
#घोषणा GPIO_CPLD_CSN		(1<<8)
/* GPIO9 - O - CPLD रेजिस्टर पढ़ो/ग_लिखो (0:ग_लिखो, 1:पढ़ो), def. 0 */
#घोषणा GPIO_CPLD_RW		(1<<9)
/* GPIO10 - O - SPI Chip Select क्रम CODEC#0, def. 1 */
#घोषणा GPIO_SPI_CSN0		(1<<10)
/* GPIO11 - O - SPI Chip Select क्रम CODEC#1, def. 1 */
#घोषणा GPIO_SPI_CSN1		(1<<11)
/* GPIO12 - O - Ex. Register Output Enable (0:enable, 1:disable), def. 1,
 * init 0 */
#घोषणा GPIO_EX_GPIOE		(1<<12)
/* GPIO13 - O - Ex. Register0 Chip Select क्रम System Control Register,
 * def. 1 */
#घोषणा GPIO_SCR		(1<<13)
/* GPIO14 - O - Ex. Register1 Chip Select क्रम Monitor Control Register,
 * def. 1 */
#घोषणा GPIO_MCR		(1<<14)

#घोषणा GPIO_SPI_ALL		(GPIO_D4_SPI_CDTO | GPIO_D5_SPI_CCLK |\
		GPIO_SPI_CSN0 | GPIO_SPI_CSN1)

#घोषणा GPIO_DATA_MASK		(GPIO_D0 | GPIO_D1_JACKDTC0 | \
		GPIO_D2_JACKDTC1 | GPIO_D3 | \
		GPIO_D4_SPI_CDTO | GPIO_D5_SPI_CCLK | \
		GPIO_D6_CD | GPIO_D7_DD)

/* System Control Register GPIO_SCR data bits */
/* Mic/Line select relay (0:line, 1:mic) */
#घोषणा SCR_RELAY		GPIO_D0
/* Phantom घातer drive control (0:5V, 1:48V) */
#घोषणा SCR_PHP_V		GPIO_D1_JACKDTC0
/* H/W mute control (0:Normal, 1:Mute) */
#घोषणा SCR_MUTE		GPIO_D2_JACKDTC1
/* Phantom घातer control (0:Phantom on, 1:off) */
#घोषणा SCR_PHP			GPIO_D3
/* Analog input 1/2 Source Select */
#घोषणा SCR_AIN12_SEL0		GPIO_D4_SPI_CDTO
#घोषणा SCR_AIN12_SEL1		GPIO_D5_SPI_CCLK
/* Analog input 3/4 Source Select (0:line, 1:hi-z) */
#घोषणा SCR_AIN34_SEL		GPIO_D6_CD
/* Codec Power Down (0:घातer करोwn, 1:normal) */
#घोषणा SCR_CODEC_PDN		GPIO_D7_DD

#घोषणा SCR_AIN12_LINE		(0)
#घोषणा SCR_AIN12_MIC		(SCR_AIN12_SEL0)
#घोषणा SCR_AIN12_LOWCUT	(SCR_AIN12_SEL1 | SCR_AIN12_SEL0)

/* Monitor Control Register GPIO_MCR data bits */
/* Input 1/2 to Monitor 1/2 (0:off, 1:on) */
#घोषणा MCR_IN12_MON12		GPIO_D0
/* Input 1/2 to Monitor 3/4 (0:off, 1:on) */
#घोषणा MCR_IN12_MON34		GPIO_D1_JACKDTC0
/* Input 3/4 to Monitor 1/2 (0:off, 1:on) */
#घोषणा MCR_IN34_MON12		GPIO_D2_JACKDTC1
/* Input 3/4 to Monitor 3/4 (0:off, 1:on) */
#घोषणा MCR_IN34_MON34		GPIO_D3
/* Output to Monitor 1/2 (0:off, 1:on) */
#घोषणा MCR_OUT34_MON12		GPIO_D4_SPI_CDTO
/* Output to Monitor 3/4 (0:off, 1:on) */
#घोषणा MCR_OUT12_MON34		GPIO_D5_SPI_CCLK

/* CPLD Register DATA bits */
/* Clock Rate Select */
#घोषणा CPLD_CKS0		GPIO_D0
#घोषणा CPLD_CKS1		GPIO_D1_JACKDTC0
#घोषणा CPLD_CKS2		GPIO_D2_JACKDTC1
/* Sync Source Select (0:Internal, 1:External) */
#घोषणा CPLD_SYNC_SEL		GPIO_D3
/* Word Clock FS Select (0:FS, 1:256FS) */
#घोषणा CPLD_WORD_SEL		GPIO_D4_SPI_CDTO
/* Coaxial Output Source (IS-Link) (0:SPDIF, 1:I2S) */
#घोषणा CPLD_COAX_OUT		GPIO_D5_SPI_CCLK
/* Input 1/2 Source Select (0:Analog12, 1:An34) */
#घोषणा CPLD_IN12_SEL		GPIO_D6_CD
/* Input 3/4 Source Select (0:Analog34, 1:Digital In) */
#घोषणा CPLD_IN34_SEL		GPIO_D7_DD

/* पूर्णांकernal घड़ी (CPLD_SYNC_SEL = 0) options */
#घोषणा CPLD_CKS_44100HZ	(0)
#घोषणा CPLD_CKS_48000HZ	(CPLD_CKS0)
#घोषणा CPLD_CKS_88200HZ	(CPLD_CKS1)
#घोषणा CPLD_CKS_96000HZ	(CPLD_CKS1 | CPLD_CKS0)
#घोषणा CPLD_CKS_176400HZ	(CPLD_CKS2)
#घोषणा CPLD_CKS_192000HZ	(CPLD_CKS2 | CPLD_CKS0)

#घोषणा CPLD_CKS_MASK		(CPLD_CKS0 | CPLD_CKS1 | CPLD_CKS2)

/* बाह्यal घड़ी (CPLD_SYNC_SEL = 1) options */
/* बाह्यal घड़ी - SPDIF */
#घोषणा CPLD_EXT_SPDIF	(0 | CPLD_SYNC_SEL)
/* बाह्यal घड़ी - WordClock 1xfs */
#घोषणा CPLD_EXT_WORDCLOCK_1FS	(CPLD_CKS1 | CPLD_SYNC_SEL)
/* बाह्यal घड़ी - WordClock 256xfs */
#घोषणा CPLD_EXT_WORDCLOCK_256FS	(CPLD_CKS1 | CPLD_WORD_SEL |\
		CPLD_SYNC_SEL)

#घोषणा EXT_SPDIF_TYPE			0
#घोषणा EXT_WORDCLOCK_1FS_TYPE		1
#घोषणा EXT_WORDCLOCK_256FS_TYPE	2

#घोषणा AK4620_DFS0		(1<<0)
#घोषणा AK4620_DFS1		(1<<1)
#घोषणा AK4620_CKS0		(1<<2)
#घोषणा AK4620_CKS1		(1<<3)
/* Clock and Format Control रेजिस्टर */
#घोषणा AK4620_DFS_REG		0x02

/* Deem and Volume Control रेजिस्टर */
#घोषणा AK4620_DEEMVOL_REG	0x03
#घोषणा AK4620_SMUTE		(1<<7)

/*
 * Conversion from पूर्णांक value to its binary क्रमm. Used क्रम debugging.
 * The output buffer must be allocated prior to calling the function.
 */
अटल अक्षर *get_binary(अक्षर *buffer, पूर्णांक value)
अणु
	पूर्णांक i, j, pos;
	pos = 0;
	क्रम (i = 0; i < 4; ++i) अणु
		क्रम (j = 0; j < 8; ++j) अणु
			अगर (value & (1 << (31-(i*8 + j))))
				buffer[pos] = '1';
			अन्यथा
				buffer[pos] = '0';
			pos++;
		पूर्ण
		अगर (i < 3) अणु
			buffer[pos] = ' ';
			pos++;
		पूर्ण
	पूर्ण
	buffer[pos] = '\0';
	वापस buffer;
पूर्ण

/*
 * Initial setup of the conversion array GPIO <-> rate
 */
अटल स्थिर अचिन्हित पूर्णांक qtet_rates[] = अणु
	44100, 48000, 88200,
	96000, 176400, 192000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक cks_vals[] = अणु
	CPLD_CKS_44100HZ, CPLD_CKS_48000HZ, CPLD_CKS_88200HZ,
	CPLD_CKS_96000HZ, CPLD_CKS_176400HZ, CPLD_CKS_192000HZ,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list qtet_rates_info = अणु
	.count = ARRAY_SIZE(qtet_rates),
	.list = qtet_rates,
	.mask = 0,
पूर्ण;

अटल व्योम qtet_ak4113_ग_लिखो(व्योम *निजी_data, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर val)
अणु
	snd_vt1724_ग_लिखो_i2c((काष्ठा snd_ice1712 *)निजी_data, AK4113_ADDR,
			reg, val);
पूर्ण

अटल अचिन्हित अक्षर qtet_ak4113_पढ़ो(व्योम *निजी_data, अचिन्हित अक्षर reg)
अणु
	वापस snd_vt1724_पढ़ो_i2c((काष्ठा snd_ice1712 *)निजी_data,
			AK4113_ADDR, reg);
पूर्ण


/*
 * AK4620 section
 */

/*
 * Write data to addr रेजिस्टर of ak4620
 */
अटल व्योम qtet_akm_ग_लिखो(काष्ठा snd_akm4xxx *ak, पूर्णांक chip,
		अचिन्हित अक्षर addr, अचिन्हित अक्षर data)
अणु
	अचिन्हित पूर्णांक पंचांगp, orig_dir;
	पूर्णांक idx;
	अचिन्हित पूर्णांक addrdata;
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];

	अगर (snd_BUG_ON(chip < 0 || chip >= 4))
		वापस;
	/*dev_dbg(ice->card->dev, "Writing to AK4620: chip=%d, addr=0x%x,
	  data=0x%x\न", chip, addr, data);*/
	orig_dir = ice->gpio.get_dir(ice);
	ice->gpio.set_dir(ice, orig_dir | GPIO_SPI_ALL);
	/* set mask - only SPI bits */
	ice->gpio.set_mask(ice, ~GPIO_SPI_ALL);

	पंचांगp = ice->gpio.get_data(ice);
	/* high all */
	पंचांगp |= GPIO_SPI_ALL;
	ice->gpio.set_data(ice, पंचांगp);
	udelay(100);
	/* drop chip select */
	अगर (chip)
		/* CODEC 1 */
		पंचांगp &= ~GPIO_SPI_CSN1;
	अन्यथा
		पंचांगp &= ~GPIO_SPI_CSN0;
	ice->gpio.set_data(ice, पंचांगp);
	udelay(100);

	/* build I2C address + data byte */
	addrdata = (AK4620_ADDR << 6) | 0x20 | (addr & 0x1f);
	addrdata = (addrdata << 8) | data;
	क्रम (idx = 15; idx >= 0; idx--) अणु
		/* drop घड़ी */
		पंचांगp &= ~GPIO_D5_SPI_CCLK;
		ice->gpio.set_data(ice, पंचांगp);
		udelay(100);
		/* set data */
		अगर (addrdata & (1 << idx))
			पंचांगp |= GPIO_D4_SPI_CDTO;
		अन्यथा
			पंचांगp &= ~GPIO_D4_SPI_CDTO;
		ice->gpio.set_data(ice, पंचांगp);
		udelay(100);
		/* उठाओ घड़ी */
		पंचांगp |= GPIO_D5_SPI_CCLK;
		ice->gpio.set_data(ice, पंचांगp);
		udelay(100);
	पूर्ण
	/* all back to 1 */
	पंचांगp |= GPIO_SPI_ALL;
	ice->gpio.set_data(ice, पंचांगp);
	udelay(100);

	/* वापस all gpios to non-writable */
	ice->gpio.set_mask(ice, 0xffffff);
	/* restore GPIOs direction */
	ice->gpio.set_dir(ice, orig_dir);
पूर्ण

अटल व्योम qtet_akm_set_regs(काष्ठा snd_akm4xxx *ak, अचिन्हित अक्षर addr,
		अचिन्हित अक्षर mask, अचिन्हित अक्षर value)
अणु
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक chip;
	क्रम (chip = 0; chip < ak->num_chips; chip++) अणु
		पंचांगp = snd_akm4xxx_get(ak, chip, addr);
		/* clear the bits */
		पंचांगp &= ~mask;
		/* set the new bits */
		पंचांगp |= value;
		snd_akm4xxx_ग_लिखो(ak, chip, addr, पंचांगp);
	पूर्ण
पूर्ण

/*
 * change the rate of AK4620
 */
अटल व्योम qtet_akm_set_rate_val(काष्ठा snd_akm4xxx *ak, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर ak4620_dfs;

	अगर (rate == 0)  /* no hपूर्णांक - S/PDIF input is master or the new spdअगर
			   input rate undetected, simply वापस */
		वापस;

	/* adjust DFS on codecs - see datasheet */
	अगर (rate > 108000)
		ak4620_dfs = AK4620_DFS1 | AK4620_CKS1;
	अन्यथा अगर (rate > 54000)
		ak4620_dfs = AK4620_DFS0 | AK4620_CKS0;
	अन्यथा
		ak4620_dfs = 0;

	/* set new value */
	qtet_akm_set_regs(ak, AK4620_DFS_REG, AK4620_DFS0 | AK4620_DFS1 |
			AK4620_CKS0 | AK4620_CKS1, ak4620_dfs);
पूर्ण

#घोषणा AK_CONTROL(xname, xch)	अणु .name = xname, .num_channels = xch पूर्ण

#घोषणा PCM_12_PLAYBACK_VOLUME	"PCM 1/2 Playback Volume"
#घोषणा PCM_34_PLAYBACK_VOLUME	"PCM 3/4 Playback Volume"
#घोषणा PCM_12_CAPTURE_VOLUME	"PCM 1/2 Capture Volume"
#घोषणा PCM_34_CAPTURE_VOLUME	"PCM 3/4 Capture Volume"

अटल स्थिर काष्ठा snd_akm4xxx_dac_channel qtet_dac[] = अणु
	AK_CONTROL(PCM_12_PLAYBACK_VOLUME, 2),
	AK_CONTROL(PCM_34_PLAYBACK_VOLUME, 2),
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx_adc_channel qtet_adc[] = अणु
	AK_CONTROL(PCM_12_CAPTURE_VOLUME, 2),
	AK_CONTROL(PCM_34_CAPTURE_VOLUME, 2),
पूर्ण;

अटल स्थिर काष्ठा snd_akm4xxx akm_qtet_dac = अणु
	.type = SND_AK4620,
	.num_dacs = 4,	/* DAC1 - Output 12
	*/
	.num_adcs = 4,	/* ADC1 - Input 12
	*/
	.ops = अणु
		.ग_लिखो = qtet_akm_ग_लिखो,
		.set_rate_val = qtet_akm_set_rate_val,
	पूर्ण,
	.dac_info = qtet_dac,
	.adc_info = qtet_adc,
पूर्ण;

/* Communication routines with the CPLD */


/* Writes data to बाह्यal रेजिस्टर reg, both reg and data are
 * GPIO representations */
अटल व्योम reg_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	mutex_lock(&ice->gpio_mutex);
	/* set direction of used GPIOs*/
	/* all outमाला_दो */
	पंचांगp = 0x00ffff;
	ice->gpio.set_dir(ice, पंचांगp);
	/* mask - writable bits */
	ice->gpio.set_mask(ice, ~(पंचांगp));
	/* ग_लिखो the data */
	पंचांगp = ice->gpio.get_data(ice);
	पंचांगp &= ~GPIO_DATA_MASK;
	पंचांगp |= data;
	ice->gpio.set_data(ice, पंचांगp);
	udelay(100);
	/* drop output enable */
	पंचांगp &=  ~GPIO_EX_GPIOE;
	ice->gpio.set_data(ice, पंचांगp);
	udelay(100);
	/* drop the रेजिस्टर gpio */
	पंचांगp &= ~reg;
	ice->gpio.set_data(ice, पंचांगp);
	udelay(100);
	/* उठाओ the रेजिस्टर GPIO */
	पंचांगp |= reg;
	ice->gpio.set_data(ice, पंचांगp);
	udelay(100);

	/* उठाओ all data gpios */
	पंचांगp |= GPIO_DATA_MASK;
	ice->gpio.set_data(ice, पंचांगp);
	/* mask - immutable bits */
	ice->gpio.set_mask(ice, 0xffffff);
	/* outमाला_दो only 8-15 */
	ice->gpio.set_dir(ice, 0x00ff00);
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल अचिन्हित पूर्णांक get_scr(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा qtet_spec *spec = ice->spec;
	वापस spec->scr;
पूर्ण

अटल अचिन्हित पूर्णांक get_mcr(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा qtet_spec *spec = ice->spec;
	वापस spec->mcr;
पूर्ण

अटल अचिन्हित पूर्णांक get_cpld(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा qtet_spec *spec = ice->spec;
	वापस spec->cpld;
पूर्ण

अटल व्योम set_scr(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक val)
अणु
	काष्ठा qtet_spec *spec = ice->spec;
	reg_ग_लिखो(ice, GPIO_SCR, val);
	spec->scr = val;
पूर्ण

अटल व्योम set_mcr(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक val)
अणु
	काष्ठा qtet_spec *spec = ice->spec;
	reg_ग_लिखो(ice, GPIO_MCR, val);
	spec->mcr = val;
पूर्ण

अटल व्योम set_cpld(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक val)
अणु
	काष्ठा qtet_spec *spec = ice->spec;
	reg_ग_लिखो(ice, GPIO_CPLD_CSN, val);
	spec->cpld = val;
पूर्ण

अटल व्योम proc_regs_पढ़ो(काष्ठा snd_info_entry *entry,
		काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ice1712 *ice = entry->निजी_data;
	अक्षर bin_buffer[36];

	snd_iम_लिखो(buffer, "SCR:	%s\n", get_binary(bin_buffer,
				get_scr(ice)));
	snd_iम_लिखो(buffer, "MCR:	%s\n", get_binary(bin_buffer,
				get_mcr(ice)));
	snd_iम_लिखो(buffer, "CPLD:	%s\n", get_binary(bin_buffer,
				get_cpld(ice)));
पूर्ण

अटल व्योम proc_init(काष्ठा snd_ice1712 *ice)
अणु
	snd_card_ro_proc_new(ice->card, "quartet", ice, proc_regs_पढ़ो);
पूर्ण

अटल पूर्णांक qtet_mute_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	val = get_scr(ice) & SCR_MUTE;
	ucontrol->value.पूर्णांकeger.value[0] = (val) ? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक qtet_mute_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक old, new, smute;
	old = get_scr(ice) & SCR_MUTE;
	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		/* unmute */
		new = 0;
		/* un-smuting DAC */
		smute = 0;
	पूर्ण अन्यथा अणु
		/* mute */
		new = SCR_MUTE;
		/* smuting DAC */
		smute = AK4620_SMUTE;
	पूर्ण
	अगर (old != new) अणु
		काष्ठा snd_akm4xxx *ak = ice->akm;
		set_scr(ice, (get_scr(ice) & ~SCR_MUTE) | new);
		/* set smute */
		qtet_akm_set_regs(ak, AK4620_DEEMVOL_REG, AK4620_SMUTE, smute);
		वापस 1;
	पूर्ण
	/* no change */
	वापस 0;
पूर्ण

अटल पूर्णांक qtet_ain12_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] =
		अणु"Line In 1/2", "Mic", "Mic + Low-cut"पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(texts), texts);
पूर्ण

अटल पूर्णांक qtet_ain12_sw_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val, result;
	val = get_scr(ice) & (SCR_AIN12_SEL1 | SCR_AIN12_SEL0);
	चयन (val) अणु
	हाल SCR_AIN12_LINE:
		result = 0;
		अवरोध;
	हाल SCR_AIN12_MIC:
		result = 1;
		अवरोध;
	हाल SCR_AIN12_LOWCUT:
		result = 2;
		अवरोध;
	शेष:
		/* BUG - no other combinations allowed */
		snd_BUG();
		result = 0;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = result;
	वापस 0;
पूर्ण

अटल पूर्णांक qtet_ain12_sw_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक old, new, पंचांगp, masked_old;
	old = new = get_scr(ice);
	masked_old = old & (SCR_AIN12_SEL1 | SCR_AIN12_SEL0);
	पंचांगp = ucontrol->value.पूर्णांकeger.value[0];
	अगर (पंचांगp == 2)
		पंचांगp = 3;	/* binary 10 is not supported */
	पंचांगp <<= 4;	/* shअगरting to SCR_AIN12_SEL0 */
	अगर (पंचांगp != masked_old) अणु
		/* change requested */
		चयन (पंचांगp) अणु
		हाल SCR_AIN12_LINE:
			new = old & ~(SCR_AIN12_SEL1 | SCR_AIN12_SEL0);
			set_scr(ice, new);
			/* turn off relay */
			new &= ~SCR_RELAY;
			set_scr(ice, new);
			अवरोध;
		हाल SCR_AIN12_MIC:
			/* turn on relay */
			new = old | SCR_RELAY;
			set_scr(ice, new);
			new = (new & ~SCR_AIN12_SEL1) | SCR_AIN12_SEL0;
			set_scr(ice, new);
			अवरोध;
		हाल SCR_AIN12_LOWCUT:
			/* turn on relay */
			new = old | SCR_RELAY;
			set_scr(ice, new);
			new |= SCR_AIN12_SEL1 | SCR_AIN12_SEL0;
			set_scr(ice, new);
			अवरोध;
		शेष:
			snd_BUG();
		पूर्ण
		वापस 1;
	पूर्ण
	/* no change */
	वापस 0;
पूर्ण

अटल पूर्णांक qtet_php_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	/* अगर phantom voltage =48V, phantom on */
	val = get_scr(ice) & SCR_PHP_V;
	ucontrol->value.पूर्णांकeger.value[0] = val ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक qtet_php_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक old, new;
	old = new = get_scr(ice);
	अगर (ucontrol->value.पूर्णांकeger.value[0] /* phantom on requested */
			&& (~old & SCR_PHP_V)) /* 0 = voltage 5V */ अणु
		/* is off, turn on */
		/* turn voltage on first, = 1 */
		new = old | SCR_PHP_V;
		set_scr(ice, new);
		/* turn phantom on, = 0 */
		new &= ~SCR_PHP;
		set_scr(ice, new);
	पूर्ण अन्यथा अगर (!ucontrol->value.पूर्णांकeger.value[0] && (old & SCR_PHP_V)) अणु
		/* phantom off requested and 1 = voltage 48V */
		/* is on, turn off */
		/* turn voltage off first, = 0 */
		new = old & ~SCR_PHP_V;
		set_scr(ice, new);
		/* turn phantom off, = 1 */
		new |= SCR_PHP;
		set_scr(ice, new);
	पूर्ण
	अगर (old != new)
		वापस 1;
	/* no change */
	वापस 0;
पूर्ण

#घोषणा PRIV_SW(xid, xbit, xreg)	[xid] = अणु.bit = xbit,\
	.set_रेजिस्टर = set_##xreg,\
	.get_रेजिस्टर = get_##xreg, पूर्ण


#घोषणा PRIV_ENUM2(xid, xbit, xreg, xtext1, xtext2)	[xid] = अणु.bit = xbit,\
	.set_रेजिस्टर = set_##xreg,\
	.get_रेजिस्टर = get_##xreg,\
	.texts = अणुxtext1, xtext2पूर्ण पूर्ण

अटल स्थिर काष्ठा qtet_kcontrol_निजी qtet_निजीs[] = अणु
	PRIV_ENUM2(IN12_SEL, CPLD_IN12_SEL, cpld, "An In 1/2", "An In 3/4"),
	PRIV_ENUM2(IN34_SEL, CPLD_IN34_SEL, cpld, "An In 3/4", "IEC958 In"),
	PRIV_ENUM2(AIN34_SEL, SCR_AIN34_SEL, scr, "Line In 3/4", "Hi-Z"),
	PRIV_ENUM2(COAX_OUT, CPLD_COAX_OUT, cpld, "IEC958", "I2S"),
	PRIV_SW(IN12_MON12, MCR_IN12_MON12, mcr),
	PRIV_SW(IN12_MON34, MCR_IN12_MON34, mcr),
	PRIV_SW(IN34_MON12, MCR_IN34_MON12, mcr),
	PRIV_SW(IN34_MON34, MCR_IN34_MON34, mcr),
	PRIV_SW(OUT12_MON34, MCR_OUT12_MON34, mcr),
	PRIV_SW(OUT34_MON12, MCR_OUT34_MON12, mcr),
पूर्ण;

अटल पूर्णांक qtet_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा qtet_kcontrol_निजी निजी =
		qtet_निजीs[kcontrol->निजी_value];
	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(निजी.texts),
				 निजी.texts);
पूर्ण

अटल पूर्णांक qtet_sw_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा qtet_kcontrol_निजी निजी =
		qtet_निजीs[kcontrol->निजी_value];
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] =
		(निजी.get_रेजिस्टर(ice) & निजी.bit) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक qtet_sw_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा qtet_kcontrol_निजी निजी =
		qtet_निजीs[kcontrol->निजी_value];
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक old, new;
	old = निजी.get_रेजिस्टर(ice);
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		new = old | निजी.bit;
	अन्यथा
		new = old & ~निजी.bit;
	अगर (old != new) अणु
		निजी.set_रेजिस्टर(ice, new);
		वापस 1;
	पूर्ण
	/* no change */
	वापस 0;
पूर्ण

#घोषणा qtet_sw_info	snd_ctl_boolean_mono_info

#घोषणा QTET_CONTROL(xname, xtype, xpriv)	\
	अणु.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,\
	.name = xname,\
	.info = qtet_##xtype##_info,\
	.get = qtet_sw_get,\
	.put = qtet_sw_put,\
	.निजी_value = xpriv पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new qtet_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Master Playback Switch",
		.info = qtet_sw_info,
		.get = qtet_mute_get,
		.put = qtet_mute_put,
		.निजी_value = 0
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Phantom Power",
		.info = qtet_sw_info,
		.get = qtet_php_get,
		.put = qtet_php_put,
		.निजी_value = 0
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog In 1/2 Capture Switch",
		.info = qtet_ain12_क्रमागत_info,
		.get = qtet_ain12_sw_get,
		.put = qtet_ain12_sw_put,
		.निजी_value = 0
	पूर्ण,
	QTET_CONTROL("Analog In 3/4 Capture Switch", क्रमागत, AIN34_SEL),
	QTET_CONTROL("PCM In 1/2 Capture Switch", क्रमागत, IN12_SEL),
	QTET_CONTROL("PCM In 3/4 Capture Switch", क्रमागत, IN34_SEL),
	QTET_CONTROL("Coax Output Source", क्रमागत, COAX_OUT),
	QTET_CONTROL("Analog In 1/2 to Monitor 1/2", sw, IN12_MON12),
	QTET_CONTROL("Analog In 1/2 to Monitor 3/4", sw, IN12_MON34),
	QTET_CONTROL("Analog In 3/4 to Monitor 1/2", sw, IN34_MON12),
	QTET_CONTROL("Analog In 3/4 to Monitor 3/4", sw, IN34_MON34),
	QTET_CONTROL("Output 1/2 to Monitor 3/4", sw, OUT12_MON34),
	QTET_CONTROL("Output 3/4 to Monitor 1/2", sw, OUT34_MON12),
पूर्ण;

अटल स्थिर अक्षर * स्थिर follower_vols[] = अणु
	PCM_12_PLAYBACK_VOLUME,
	PCM_34_PLAYBACK_VOLUME,
	शून्य
पूर्ण;

अटल
DECLARE_TLV_DB_SCALE(qtet_master_db_scale, -6350, 50, 1);

अटल काष्ठा snd_kcontrol *ctl_find(काष्ठा snd_card *card,
				     स्थिर अक्षर *name)
अणु
	काष्ठा snd_ctl_elem_id sid = अणु0पूर्ण;

	strscpy(sid.name, name, माप(sid.name));
	sid.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	वापस snd_ctl_find_id(card, &sid);
पूर्ण

अटल व्योम add_followers(काष्ठा snd_card *card,
			  काष्ठा snd_kcontrol *master, स्थिर अक्षर * स्थिर *list)
अणु
	क्रम (; *list; list++) अणु
		काष्ठा snd_kcontrol *follower = ctl_find(card, *list);
		अगर (follower)
			snd_ctl_add_follower(master, follower);
	पूर्ण
पूर्ण

अटल पूर्णांक qtet_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा qtet_spec *spec = ice->spec;
	पूर्णांक err, i;
	काष्ठा snd_kcontrol *vmaster;
	err = snd_ice1712_akm4xxx_build_controls(ice);
	अगर (err < 0)
		वापस err;
	क्रम (i = 0; i < ARRAY_SIZE(qtet_controls); i++) अणु
		err = snd_ctl_add(ice->card,
				snd_ctl_new1(&qtet_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Create भव master control */
	vmaster = snd_ctl_make_भव_master("Master Playback Volume",
			qtet_master_db_scale);
	अगर (!vmaster)
		वापस -ENOMEM;
	add_followers(ice->card, vmaster, follower_vols);
	err = snd_ctl_add(ice->card, vmaster);
	अगर (err < 0)
		वापस err;
	/* only capture SPDIF over AK4113 */
	वापस snd_ak4113_build(spec->ak4113,
			ice->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
पूर्ण

अटल अंतरभूत पूर्णांक qtet_is_spdअगर_master(काष्ठा snd_ice1712 *ice)
अणु
	/* CPLD_SYNC_SEL: 0 = पूर्णांकernal, 1 = बाह्यal (i.e. spdअगर master) */
	वापस (get_cpld(ice) & CPLD_SYNC_SEL) ? 1 : 0;
पूर्ण

अटल अचिन्हित पूर्णांक qtet_get_rate(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर result;

	result =  get_cpld(ice) & CPLD_CKS_MASK;
	क्रम (i = 0; i < ARRAY_SIZE(cks_vals); i++)
		अगर (cks_vals[i] == result)
			वापस qtet_rates[i];
	वापस 0;
पूर्ण

अटल पूर्णांक get_cks_val(पूर्णांक rate)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(qtet_rates); i++)
		अगर (qtet_rates[i] == rate)
			वापस cks_vals[i];
	वापस 0;
पूर्ण

/* setting new rate */
अटल व्योम qtet_set_rate(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक new;
	अचिन्हित अक्षर val;
	/* चयनing ice1724 to बाह्यal घड़ी - supplied by ext. circuits */
	val = inb(ICEMT1724(ice, RATE));
	outb(val | VT1724_SPDIF_MASTER, ICEMT1724(ice, RATE));

	new =  (get_cpld(ice) & ~CPLD_CKS_MASK) | get_cks_val(rate);
	/* चयन to पूर्णांकernal घड़ी, drop CPLD_SYNC_SEL */
	new &= ~CPLD_SYNC_SEL;
	/* dev_dbg(ice->card->dev, "QT - set_rate: old %x, new %x\n",
	   get_cpld(ice), new); */
	set_cpld(ice, new);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर qtet_set_mclk(काष्ठा snd_ice1712 *ice,
		अचिन्हित पूर्णांक rate)
अणु
	/* no change in master घड़ी */
	वापस 0;
पूर्ण

/* setting घड़ी to बाह्यal - SPDIF */
अटल पूर्णांक qtet_set_spdअगर_घड़ी(काष्ठा snd_ice1712 *ice, पूर्णांक type)
अणु
	अचिन्हित पूर्णांक old, new;

	old = new = get_cpld(ice);
	new &= ~(CPLD_CKS_MASK | CPLD_WORD_SEL);
	चयन (type) अणु
	हाल EXT_SPDIF_TYPE:
		new |= CPLD_EXT_SPDIF;
		अवरोध;
	हाल EXT_WORDCLOCK_1FS_TYPE:
		new |= CPLD_EXT_WORDCLOCK_1FS;
		अवरोध;
	हाल EXT_WORDCLOCK_256FS_TYPE:
		new |= CPLD_EXT_WORDCLOCK_256FS;
		अवरोध;
	शेष:
		snd_BUG();
	पूर्ण
	अगर (old != new) अणु
		set_cpld(ice, new);
		/* changed */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qtet_get_spdअगर_master_type(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक result;
	val = get_cpld(ice);
	/* checking only rate/घड़ी-related bits */
	val &= (CPLD_CKS_MASK | CPLD_WORD_SEL | CPLD_SYNC_SEL);
	अगर (!(val & CPLD_SYNC_SEL)) अणु
		/* चयनed to पूर्णांकernal घड़ी, is not any बाह्यal type */
		result = -1;
	पूर्ण अन्यथा अणु
		चयन (val) अणु
		हाल (CPLD_EXT_SPDIF):
			result = EXT_SPDIF_TYPE;
			अवरोध;
		हाल (CPLD_EXT_WORDCLOCK_1FS):
			result = EXT_WORDCLOCK_1FS_TYPE;
			अवरोध;
		हाल (CPLD_EXT_WORDCLOCK_256FS):
			result = EXT_WORDCLOCK_256FS_TYPE;
			अवरोध;
		शेष:
			/* undefined combination of बाह्यal घड़ी setup */
			snd_BUG();
			result = 0;
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

/* Called when ak4113 detects change in the input SPDIF stream */
अटल व्योम qtet_ak4113_change(काष्ठा ak4113 *ak4113, अचिन्हित अक्षर c0,
		अचिन्हित अक्षर c1)
अणु
	काष्ठा snd_ice1712 *ice = ak4113->change_callback_निजी;
	पूर्णांक rate;
	अगर ((qtet_get_spdअगर_master_type(ice) == EXT_SPDIF_TYPE) &&
			c1) अणु
		/* only क्रम SPDIF master mode, rate was changed */
		rate = snd_ak4113_बाह्यal_rate(ak4113);
		/* dev_dbg(ice->card->dev, "ak4113 - input rate changed to %d\n",
		   rate); */
		qtet_akm_set_rate_val(ice->akm, rate);
	पूर्ण
पूर्ण

/*
 * If घड़ी slaved to SPDIF-IN, setting runसमय rate
 * to the detected बाह्यal rate
 */
अटल व्योम qtet_spdअगर_in_खोलो(काष्ठा snd_ice1712 *ice,
		काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा qtet_spec *spec = ice->spec;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक rate;

	अगर (qtet_get_spdअगर_master_type(ice) != EXT_SPDIF_TYPE)
		/* not बाह्यal SPDIF, no rate limitation */
		वापस;
	/* only बाह्यal SPDIF can detect incoming sample rate */
	rate = snd_ak4113_बाह्यal_rate(spec->ak4113);
	अगर (rate >= runसमय->hw.rate_min && rate <= runसमय->hw.rate_max) अणु
		runसमय->hw.rate_min = rate;
		runसमय->hw.rate_max = rate;
	पूर्ण
पूर्ण

/*
 * initialize the chip
 */
अटल पूर्णांक qtet_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित अक्षर ak4113_init_vals[] = अणु
		/* AK4113_REG_PWRDN */	AK4113_RST | AK4113_PWN |
			AK4113_OCKS0 | AK4113_OCKS1,
		/* AK4113_REQ_FORMAT */	AK4113_DIF_I24I2S | AK4113_VTX |
			AK4113_DEM_OFF | AK4113_DEAU,
		/* AK4113_REG_IO0 */	AK4113_OPS2 | AK4113_TXE |
			AK4113_XTL_24_576M,
		/* AK4113_REG_IO1 */	AK4113_EFH_1024LRCLK | AK4113_IPS(0),
		/* AK4113_REG_INT0_MASK */	0,
		/* AK4113_REG_INT1_MASK */	0,
		/* AK4113_REG_DATDTS */		0,
	पूर्ण;
	पूर्णांक err;
	काष्ठा qtet_spec *spec;
	काष्ठा snd_akm4xxx *ak;
	अचिन्हित अक्षर val;

	/* चयनing ice1724 to बाह्यal घड़ी - supplied by ext. circuits */
	val = inb(ICEMT1724(ice, RATE));
	outb(val | VT1724_SPDIF_MASTER, ICEMT1724(ice, RATE));

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	/* qtet is घड़ीed by Xilinx array */
	ice->hw_rates = &qtet_rates_info;
	ice->is_spdअगर_master = qtet_is_spdअगर_master;
	ice->get_rate = qtet_get_rate;
	ice->set_rate = qtet_set_rate;
	ice->set_mclk = qtet_set_mclk;
	ice->set_spdअगर_घड़ी = qtet_set_spdअगर_घड़ी;
	ice->get_spdअगर_master_type = qtet_get_spdअगर_master_type;
	ice->ext_घड़ी_names = ext_घड़ी_names;
	ice->ext_घड़ी_count = ARRAY_SIZE(ext_घड़ी_names);
	/* since Qtet can detect correct SPDIF-in rate, all streams can be
	 * limited to this specअगरic rate */
	ice->spdअगर.ops.खोलो = ice->pro_खोलो = qtet_spdअगर_in_खोलो;
	ice->spec = spec;

	/* Mute Off */
	/* SCR Initialize*/
	/* keep codec घातer करोwn first */
	set_scr(ice, SCR_PHP);
	udelay(1);
	/* codec घातer up */
	set_scr(ice, SCR_PHP | SCR_CODEC_PDN);

	/* MCR Initialize */
	set_mcr(ice, 0);

	/* CPLD Initialize */
	set_cpld(ice, 0);


	ice->num_total_dacs = 2;
	ice->num_total_adcs = 2;

	ice->akm = kसुस्मृति(2, माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	ak = ice->akm;
	अगर (!ak)
		वापस -ENOMEM;
	/* only one codec with two chips */
	ice->akm_codecs = 1;
	err = snd_ice1712_akm4xxx_init(ak, &akm_qtet_dac, शून्य, ice);
	अगर (err < 0)
		वापस err;
	err = snd_ak4113_create(ice->card,
			qtet_ak4113_पढ़ो,
			qtet_ak4113_ग_लिखो,
			ak4113_init_vals,
			ice, &spec->ak4113);
	अगर (err < 0)
		वापस err;
	/* callback क्रम codecs rate setting */
	spec->ak4113->change_callback = qtet_ak4113_change;
	spec->ak4113->change_callback_निजी = ice;
	/* AK41143 in Quartet can detect बाह्यal rate correctly
	 * (i.e. check_flags = 0) */
	spec->ak4113->check_flags = 0;

	proc_init(ice);

	qtet_set_rate(ice, 44100);
	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित अक्षर qtet_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x28,	/* घड़ी 256(24MHz), mpu401, 1xADC,
					   1xDACs, SPDIF in */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0x78,	/* 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, in, out-ext */
	[ICE_EEP2_GPIO_सूची]    = 0x00,	/* 0-7 inमाला_दो, चयनed to output
					   only during output operations */
	[ICE_EEP2_GPIO_सूची1]   = 0xff,  /* 8-15 outमाला_दो */
	[ICE_EEP2_GPIO_सूची2]   = 0x00,
	[ICE_EEP2_GPIO_MASK]   = 0xff,	/* changed only क्रम OUT operations */
	[ICE_EEP2_GPIO_MASK1]  = 0x00,
	[ICE_EEP2_GPIO_MASK2]  = 0xff,

	[ICE_EEP2_GPIO_STATE]  = 0x00, /* inमाला_दो */
	[ICE_EEP2_GPIO_STATE1] = 0x7d, /* all 1, but GPIO_CPLD_RW
					  and GPIO15 always zero */
	[ICE_EEP2_GPIO_STATE2] = 0x00, /* inमाला_दो */
पूर्ण;

/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1724_qtet_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_QTET,
		.name = "Infrasonic Quartet",
		.model = "quartet",
		.chip_init = qtet_init,
		.build_controls = qtet_add_controls,
		.eeprom_size = माप(qtet_eeprom),
		.eeprom_data = qtet_eeprom,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
