<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routines क्रम control of the CS8427 via i2c bus
 *  IEC958 (S/PDIF) receiver & transmitter by Cirrus Logic
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/cs8427.h>
#समावेश <sound/asoundef.h>

अटल व्योम snd_cs8427_reset(काष्ठा snd_i2c_device *cs8427);

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("IEC958 (S/PDIF) receiver & transmitter by Cirrus Logic");
MODULE_LICENSE("GPL");

#घोषणा CS8427_ADDR			(0x20>>1) /* fixed address */

काष्ठा cs8427_stream अणु
	काष्ठा snd_pcm_substream *substream;
	अक्षर hw_status[24];		/* hardware status */
	अक्षर def_status[24];		/* शेष status */
	अक्षर pcm_status[24];		/* PCM निजी status */
	अक्षर hw_udata[32];
	काष्ठा snd_kcontrol *pcm_ctl;
पूर्ण;

काष्ठा cs8427 अणु
	अचिन्हित अक्षर regmap[0x14];	/* map of first 1 + 13 रेजिस्टरs */
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक reset_समयout;
	काष्ठा cs8427_stream playback;
	काष्ठा cs8427_stream capture;
पूर्ण;

पूर्णांक snd_cs8427_reg_ग_लिखो(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर reg,
			 अचिन्हित अक्षर val)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर buf[2];

	buf[0] = reg & 0x7f;
	buf[1] = val;
	अगर ((err = snd_i2c_sendbytes(device, buf, 2)) != 2) अणु
		snd_prपूर्णांकk(KERN_ERR "unable to send bytes 0x%02x:0x%02x "
			   "to CS8427 (%i)\n", buf[0], buf[1], err);
		वापस err < 0 ? err : -EIO;
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_cs8427_reg_ग_लिखो);

अटल पूर्णांक snd_cs8427_reg_पढ़ो(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर reg)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर buf;

	अगर ((err = snd_i2c_sendbytes(device, &reg, 1)) != 1) अणु
		snd_prपूर्णांकk(KERN_ERR "unable to send register 0x%x byte "
			   "to CS8427\n", reg);
		वापस err < 0 ? err : -EIO;
	पूर्ण
	अगर ((err = snd_i2c_पढ़ोbytes(device, &buf, 1)) != 1) अणु
		snd_prपूर्णांकk(KERN_ERR "unable to read register 0x%x byte "
			   "from CS8427\n", reg);
		वापस err < 0 ? err : -EIO;
	पूर्ण
	वापस buf;
पूर्ण

अटल पूर्णांक snd_cs8427_select_corudata(काष्ठा snd_i2c_device *device, पूर्णांक udata)
अणु
	काष्ठा cs8427 *chip = device->निजी_data;
	पूर्णांक err;

	udata = udata ? CS8427_BSEL : 0;
	अगर (udata != (chip->regmap[CS8427_REG_CSDATABUF] & udata)) अणु
		chip->regmap[CS8427_REG_CSDATABUF] &= ~CS8427_BSEL;
		chip->regmap[CS8427_REG_CSDATABUF] |= udata;
		err = snd_cs8427_reg_ग_लिखो(device, CS8427_REG_CSDATABUF,
					   chip->regmap[CS8427_REG_CSDATABUF]);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs8427_send_corudata(काष्ठा snd_i2c_device *device,
				    पूर्णांक udata,
				    अचिन्हित अक्षर *ndata,
				    पूर्णांक count)
अणु
	काष्ठा cs8427 *chip = device->निजी_data;
	अक्षर *hw_data = udata ?
		chip->playback.hw_udata : chip->playback.hw_status;
	अचिन्हित अक्षर data[32];
	पूर्णांक err, idx;

	अगर (!स_भेद(hw_data, ndata, count))
		वापस 0;
	अगर ((err = snd_cs8427_select_corudata(device, udata)) < 0)
		वापस err;
	स_नकल(hw_data, ndata, count);
	अगर (udata) अणु
		स_रखो(data, 0, माप(data));
		अगर (स_भेद(hw_data, data, count) == 0) अणु
			chip->regmap[CS8427_REG_UDATABUF] &= ~CS8427_UBMMASK;
			chip->regmap[CS8427_REG_UDATABUF] |= CS8427_UBMZEROS |
				CS8427_EFTUI;
			err = snd_cs8427_reg_ग_लिखो(device, CS8427_REG_UDATABUF,
						   chip->regmap[CS8427_REG_UDATABUF]);
			वापस err < 0 ? err : 0;
		पूर्ण
	पूर्ण
	data[0] = CS8427_REG_AUTOINC | CS8427_REG_CORU_DATABUF;
	क्रम (idx = 0; idx < count; idx++)
		data[idx + 1] = bitrev8(ndata[idx]);
	अगर (snd_i2c_sendbytes(device, data, count + 1) != count + 1)
		वापस -EIO;
	वापस 1;
पूर्ण

अटल व्योम snd_cs8427_मुक्त(काष्ठा snd_i2c_device *device)
अणु
	kमुक्त(device->निजी_data);
पूर्ण

पूर्णांक snd_cs8427_init(काष्ठा snd_i2c_bus *bus,
		    काष्ठा snd_i2c_device *device)
अणु
	अटल अचिन्हित अक्षर initvals1[] = अणु
	  CS8427_REG_CONTROL1 | CS8427_REG_AUTOINC,
	  /* CS8427_REG_CONTROL1: RMCK to OMCK, valid PCM audio, disable mutes,
	     TCBL=output */
	  CS8427_SWCLK | CS8427_TCBLसूची,
	  /* CS8427_REG_CONTROL2: hold last valid audio sample, RMCK=256*Fs,
	     normal stereo operation */
	  0x00,
	  /* CS8427_REG_DATAFLOW: output drivers normal operation, Tx<=serial,
	     Rx=>serial */
	  CS8427_TXDSERIAL | CS8427_SPDAES3RECEIVER,
	  /* CS8427_REG_CLOCKSOURCE: Run off, CMCK=256*Fs,
	     output समय base = OMCK, input समय base = recovered input घड़ी,
	     recovered input घड़ी source is ILRCK changed to AES3INPUT
	     (workaround, see snd_cs8427_reset) */
	  CS8427_RXDILRCK,
	  /* CS8427_REG_SERIALINPUT: Serial audio input port data क्रमmat = I2S,
	     24-bit, 64*Fsi */
	  CS8427_SIDEL | CS8427_SILRPOL,
	  /* CS8427_REG_SERIALOUTPUT: Serial audio output port data क्रमmat
	     = I2S, 24-bit, 64*Fsi */
	  CS8427_SODEL | CS8427_SOLRPOL,
	पूर्ण;
	अटल अचिन्हित अक्षर initvals2[] = अणु
	  CS8427_REG_RECVERRMASK | CS8427_REG_AUTOINC,
	  /* CS8427_REG_RECVERRMASK: unmask the input PLL घड़ी, V, confidence,
	     biphase, parity status bits */
	  /* CS8427_UNLOCK | CS8427_V | CS8427_CONF | CS8427_BIP | CS8427_PAR,*/
	  0xff, /* set everything */
	  /* CS8427_REG_CSDATABUF:
	     Registers 32-55 winकरोw to CS buffer
	     Inhibit D->E transfers from overwriting first 5 bytes of CS data.
	     Inhibit D->E transfers (all) of CS data.
	     Allow E->F transfer of CS data.
	     One byte mode; both A/B channels get same written CB data.
	     A channel info is output to chip's EMPH* pin. */
	  CS8427_CBMR | CS8427_DETCI,
	  /* CS8427_REG_UDATABUF:
	     Use पूर्णांकernal buffer to transmit User (U) data.
	     Chip's U pin is an output.
	     Transmit all O's क्रम user data.
	     Inhibit D->E transfers.
	     Inhibit E->F transfers. */
	  CS8427_UD | CS8427_EFTUI | CS8427_DETUI,
	पूर्ण;
	काष्ठा cs8427 *chip = device->निजी_data;
	पूर्णांक err;
	अचिन्हित अक्षर buf[24];

	snd_i2c_lock(bus);
	err = snd_cs8427_reg_पढ़ो(device, CS8427_REG_ID_AND_VER);
	अगर (err != CS8427_VER8427A) अणु
		/* give second chance */
		snd_prपूर्णांकk(KERN_WARNING "invalid CS8427 signature 0x%x: "
			   "let me try again...\n", err);
		err = snd_cs8427_reg_पढ़ो(device, CS8427_REG_ID_AND_VER);
	पूर्ण
	अगर (err != CS8427_VER8427A) अणु
		snd_i2c_unlock(bus);
		snd_prपूर्णांकk(KERN_ERR "unable to find CS8427 signature "
			   "(expected 0x%x, read 0x%x),\n",
			   CS8427_VER8427A, err);
		snd_prपूर्णांकk(KERN_ERR "   initialization is not completed\n");
		वापस -EFAULT;
	पूर्ण
	/* turn off run bit जबतक making changes to configuration */
	err = snd_cs8427_reg_ग_लिखो(device, CS8427_REG_CLOCKSOURCE, 0x00);
	अगर (err < 0)
		जाओ __fail;
	/* send initial values */
	स_नकल(chip->regmap + (initvals1[0] & 0x7f), initvals1 + 1, 6);
	अगर ((err = snd_i2c_sendbytes(device, initvals1, 7)) != 7) अणु
		err = err < 0 ? err : -EIO;
		जाओ __fail;
	पूर्ण
	/* Turn off CS8427 पूर्णांकerrupt stuff that is not used in hardware */
	स_रखो(buf, 0, 7);
	/* from address 9 to 15 */
	buf[0] = 9;	/* रेजिस्टर */
	अगर ((err = snd_i2c_sendbytes(device, buf, 7)) != 7)
		जाओ __fail;
	/* send transfer initialization sequence */
	स_नकल(chip->regmap + (initvals2[0] & 0x7f), initvals2 + 1, 3);
	अगर ((err = snd_i2c_sendbytes(device, initvals2, 4)) != 4) अणु
		err = err < 0 ? err : -EIO;
		जाओ __fail;
	पूर्ण
	/* ग_लिखो शेष channel status bytes */
	put_unaligned_le32(SNDRV_PCM_DEFAULT_CON_SPDIF, buf);
	स_रखो(buf + 4, 0, 24 - 4);
	अगर (snd_cs8427_send_corudata(device, 0, buf, 24) < 0)
		जाओ __fail;
	स_नकल(chip->playback.def_status, buf, 24);
	स_नकल(chip->playback.pcm_status, buf, 24);
	snd_i2c_unlock(bus);

	/* turn on run bit and rock'n'roll */
	snd_cs8427_reset(device);

	वापस 0;

__fail:
	snd_i2c_unlock(bus);

	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_cs8427_init);

पूर्णांक snd_cs8427_create(काष्ठा snd_i2c_bus *bus,
		      अचिन्हित अक्षर addr,
		      अचिन्हित पूर्णांक reset_समयout,
		      काष्ठा snd_i2c_device **r_cs8427)
अणु
	पूर्णांक err;
	काष्ठा cs8427 *chip;
	काष्ठा snd_i2c_device *device;

	err = snd_i2c_device_create(bus, "CS8427", CS8427_ADDR | (addr & 7),
				    &device);
	अगर (err < 0)
		वापस err;
	chip = device->निजी_data = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		snd_i2c_device_मुक्त(device);
		वापस -ENOMEM;
	पूर्ण
	device->निजी_मुक्त = snd_cs8427_मुक्त;

	अगर (reset_समयout < 1)
		reset_समयout = 1;
	chip->reset_समयout = reset_समयout;

	err = snd_cs8427_init(bus, device);
	अगर (err)
		जाओ __fail;

#अगर 0	// it's nice क्रम पढ़ो tests
	अणु
	अक्षर buf[128];
	पूर्णांक xx;
	buf[0] = 0x81;
	snd_i2c_sendbytes(device, buf, 1);
	snd_i2c_पढ़ोbytes(device, buf, 127);
	क्रम (xx = 0; xx < 127; xx++)
		prपूर्णांकk(KERN_DEBUG "reg[0x%x] = 0x%x\n", xx+1, buf[xx]);
	पूर्ण
#पूर्ण_अगर
	
	अगर (r_cs8427)
		*r_cs8427 = device;
	वापस 0;

      __fail:
      	snd_i2c_device_मुक्त(device);
      	वापस err < 0 ? err : -EIO;
पूर्ण

EXPORT_SYMBOL(snd_cs8427_create);

/*
 * Reset the chip using run bit, also lock PLL using ILRCK and
 * put back AES3INPUT. This workaround is described in latest
 * CS8427 datasheet, otherwise TXDSERIAL will not work.
 */
अटल व्योम snd_cs8427_reset(काष्ठा snd_i2c_device *cs8427)
अणु
	काष्ठा cs8427 *chip;
	अचिन्हित दीर्घ end_समय;
	पूर्णांक data, aes3input = 0;

	अगर (snd_BUG_ON(!cs8427))
		वापस;
	chip = cs8427->निजी_data;
	snd_i2c_lock(cs8427->bus);
	अगर ((chip->regmap[CS8427_REG_CLOCKSOURCE] & CS8427_RXDAES3INPUT) ==
	    CS8427_RXDAES3INPUT)  /* AES3 bit is set */
		aes3input = 1;
	chip->regmap[CS8427_REG_CLOCKSOURCE] &= ~(CS8427_RUN | CS8427_RXDMASK);
	snd_cs8427_reg_ग_लिखो(cs8427, CS8427_REG_CLOCKSOURCE,
			     chip->regmap[CS8427_REG_CLOCKSOURCE]);
	udelay(200);
	chip->regmap[CS8427_REG_CLOCKSOURCE] |= CS8427_RUN | CS8427_RXDILRCK;
	snd_cs8427_reg_ग_लिखो(cs8427, CS8427_REG_CLOCKSOURCE,
			     chip->regmap[CS8427_REG_CLOCKSOURCE]);
	udelay(200);
	snd_i2c_unlock(cs8427->bus);
	end_समय = jअगरfies + chip->reset_समयout;
	जबतक (समय_after_eq(end_समय, jअगरfies)) अणु
		snd_i2c_lock(cs8427->bus);
		data = snd_cs8427_reg_पढ़ो(cs8427, CS8427_REG_RECVERRORS);
		snd_i2c_unlock(cs8427->bus);
		अगर (!(data & CS8427_UNLOCK))
			अवरोध;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	snd_i2c_lock(cs8427->bus);
	chip->regmap[CS8427_REG_CLOCKSOURCE] &= ~CS8427_RXDMASK;
	अगर (aes3input)
		chip->regmap[CS8427_REG_CLOCKSOURCE] |= CS8427_RXDAES3INPUT;
	snd_cs8427_reg_ग_लिखो(cs8427, CS8427_REG_CLOCKSOURCE,
			     chip->regmap[CS8427_REG_CLOCKSOURCE]);
	snd_i2c_unlock(cs8427->bus);
पूर्ण

अटल पूर्णांक snd_cs8427_in_status_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs8427_in_status_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_i2c_device *device = snd_kcontrol_chip(kcontrol);
	पूर्णांक data;

	snd_i2c_lock(device->bus);
	data = snd_cs8427_reg_पढ़ो(device, kcontrol->निजी_value);
	snd_i2c_unlock(device->bus);
	अगर (data < 0)
		वापस data;
	ucontrol->value.पूर्णांकeger.value[0] = data;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs8427_qsubcode_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = 10;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs8427_qsubcode_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_i2c_device *device = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर reg = CS8427_REG_QSUBCODE;
	पूर्णांक err;

	snd_i2c_lock(device->bus);
	अगर ((err = snd_i2c_sendbytes(device, &reg, 1)) != 1) अणु
		snd_prपूर्णांकk(KERN_ERR "unable to send register 0x%x byte "
			   "to CS8427\n", reg);
		snd_i2c_unlock(device->bus);
		वापस err < 0 ? err : -EIO;
	पूर्ण
	err = snd_i2c_पढ़ोbytes(device, ucontrol->value.bytes.data, 10);
	अगर (err != 10) अणु
		snd_prपूर्णांकk(KERN_ERR "unable to read Q-subcode bytes "
			   "from CS8427\n");
		snd_i2c_unlock(device->bus);
		वापस err < 0 ? err : -EIO;
	पूर्ण
	snd_i2c_unlock(device->bus);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs8427_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs8427_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_i2c_device *device = snd_kcontrol_chip(kcontrol);
	काष्ठा cs8427 *chip = device->निजी_data;
	
	snd_i2c_lock(device->bus);
	स_नकल(ucontrol->value.iec958.status, chip->playback.def_status, 24);
	snd_i2c_unlock(device->bus);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs8427_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_i2c_device *device = snd_kcontrol_chip(kcontrol);
	काष्ठा cs8427 *chip = device->निजी_data;
	अचिन्हित अक्षर *status = kcontrol->निजी_value ?
		chip->playback.pcm_status : chip->playback.def_status;
	काष्ठा snd_pcm_runसमय *runसमय = chip->playback.substream ?
		chip->playback.substream->runसमय : शून्य;
	पूर्णांक err, change;

	snd_i2c_lock(device->bus);
	change = स_भेद(ucontrol->value.iec958.status, status, 24) != 0;
	स_नकल(status, ucontrol->value.iec958.status, 24);
	अगर (change && (kcontrol->निजी_value ?
		       runसमय != शून्य : runसमय == शून्य)) अणु
		err = snd_cs8427_send_corudata(device, 0, status, 24);
		अगर (err < 0)
			change = err;
	पूर्ण
	snd_i2c_unlock(device->bus);
	वापस change;
पूर्ण

अटल पूर्णांक snd_cs8427_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs8427_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	स_रखो(ucontrol->value.iec958.status, 0xff, 24);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs8427_iec958_controls[] = अणु
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.info =		snd_cs8427_in_status_info,
	.name =		"IEC958 CS8427 Input Status",
	.access =	(SNDRV_CTL_ELEM_ACCESS_READ |
			 SNDRV_CTL_ELEM_ACCESS_VOLATILE),
	.get =		snd_cs8427_in_status_get,
	.निजी_value = 15,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.info =		snd_cs8427_in_status_info,
	.name =		"IEC958 CS8427 Error Status",
	.access =	(SNDRV_CTL_ELEM_ACCESS_READ |
			 SNDRV_CTL_ELEM_ACCESS_VOLATILE),
	.get =		snd_cs8427_in_status_get,
	.निजी_value = 16,
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
	.info =		snd_cs8427_spdअगर_mask_info,
	.get =		snd_cs8427_spdअगर_mask_get,
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =		snd_cs8427_spdअगर_info,
	.get =		snd_cs8427_spdअगर_get,
	.put =		snd_cs8427_spdअगर_put,
	.निजी_value = 0
पूर्ण,
अणु
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_INACTIVE),
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
	.info =		snd_cs8427_spdअगर_info,
	.get =		snd_cs8427_spdअगर_get,
	.put =		snd_cs8427_spdअगर_put,
	.निजी_value = 1
पूर्ण,
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.info =		snd_cs8427_qsubcode_info,
	.name =		"IEC958 Q-subcode Capture Default",
	.access =	(SNDRV_CTL_ELEM_ACCESS_READ |
			 SNDRV_CTL_ELEM_ACCESS_VOLATILE),
	.get =		snd_cs8427_qsubcode_get
पूर्णपूर्ण;

पूर्णांक snd_cs8427_iec958_build(काष्ठा snd_i2c_device *cs8427,
			    काष्ठा snd_pcm_substream *play_substream,
			    काष्ठा snd_pcm_substream *cap_substream)
अणु
	काष्ठा cs8427 *chip = cs8427->निजी_data;
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!play_substream || !cap_substream))
		वापस -EINVAL;
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_cs8427_iec958_controls); idx++) अणु
		kctl = snd_ctl_new1(&snd_cs8427_iec958_controls[idx], cs8427);
		अगर (kctl == शून्य)
			वापस -ENOMEM;
		kctl->id.device = play_substream->pcm->device;
		kctl->id.subdevice = play_substream->number;
		err = snd_ctl_add(cs8427->bus->card, kctl);
		अगर (err < 0)
			वापस err;
		अगर (! म_भेद(kctl->id.name,
			     SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM)))
			chip->playback.pcm_ctl = kctl;
	पूर्ण

	chip->playback.substream = play_substream;
	chip->capture.substream = cap_substream;
	अगर (snd_BUG_ON(!chip->playback.pcm_ctl))
		वापस -EIO;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_cs8427_iec958_build);

पूर्णांक snd_cs8427_iec958_active(काष्ठा snd_i2c_device *cs8427, पूर्णांक active)
अणु
	काष्ठा cs8427 *chip;

	अगर (snd_BUG_ON(!cs8427))
		वापस -ENXIO;
	chip = cs8427->निजी_data;
	अगर (active)
		स_नकल(chip->playback.pcm_status,
		       chip->playback.def_status, 24);
	chip->playback.pcm_ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(cs8427->bus->card,
		       SNDRV_CTL_EVENT_MASK_VALUE | SNDRV_CTL_EVENT_MASK_INFO,
		       &chip->playback.pcm_ctl->id);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_cs8427_iec958_active);

पूर्णांक snd_cs8427_iec958_pcm(काष्ठा snd_i2c_device *cs8427, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा cs8427 *chip;
	अक्षर *status;
	पूर्णांक err, reset;

	अगर (snd_BUG_ON(!cs8427))
		वापस -ENXIO;
	chip = cs8427->निजी_data;
	status = chip->playback.pcm_status;
	snd_i2c_lock(cs8427->bus);
	अगर (status[0] & IEC958_AES0_PROFESSIONAL) अणु
		status[0] &= ~IEC958_AES0_PRO_FS;
		चयन (rate) अणु
		हाल 32000: status[0] |= IEC958_AES0_PRO_FS_32000; अवरोध;
		हाल 44100: status[0] |= IEC958_AES0_PRO_FS_44100; अवरोध;
		हाल 48000: status[0] |= IEC958_AES0_PRO_FS_48000; अवरोध;
		शेष: status[0] |= IEC958_AES0_PRO_FS_NOTID; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		status[3] &= ~IEC958_AES3_CON_FS;
		चयन (rate) अणु
		हाल 32000: status[3] |= IEC958_AES3_CON_FS_32000; अवरोध;
		हाल 44100: status[3] |= IEC958_AES3_CON_FS_44100; अवरोध;
		हाल 48000: status[3] |= IEC958_AES3_CON_FS_48000; अवरोध;
		पूर्ण
	पूर्ण
	err = snd_cs8427_send_corudata(cs8427, 0, status, 24);
	अगर (err > 0)
		snd_ctl_notअगरy(cs8427->bus->card,
			       SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->playback.pcm_ctl->id);
	reset = chip->rate != rate;
	chip->rate = rate;
	snd_i2c_unlock(cs8427->bus);
	अगर (reset)
		snd_cs8427_reset(cs8427);
	वापस err < 0 ? err : 0;
पूर्ण

EXPORT_SYMBOL(snd_cs8427_iec958_pcm);
