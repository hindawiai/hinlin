<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* DVB USB compliant Linux driver क्रम the Afatech 9005
 * USB1.1 DVB-T receiver.
 *
 * Copyright (C) 2007 Luca Olivetti (luca@ventoso.org)
 *
 * Thanks to Afatech who kindly provided inक्रमmation.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "af9005.h"

/* debug */
पूर्णांक dvb_usb_af9005_debug;
module_param_named(debug, dvb_usb_af9005_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		 "set debugging level (1=info,xfer=2,rc=4,reg=8,i2c=16,fw=32 (or-able))."
		 DVB_USB_DEBUG_STATUS);
/* enable obnoxious led */
bool dvb_usb_af9005_led = true;
module_param_named(led, dvb_usb_af9005_led, bool, 0644);
MODULE_PARM_DESC(led, "enable led (default: 1).");

/* eeprom dump */
अटल पूर्णांक dvb_usb_af9005_dump_eeprom;
module_param_named(dump_eeprom, dvb_usb_af9005_dump_eeprom, पूर्णांक, 0);
MODULE_PARM_DESC(dump_eeprom, "dump contents of the eeprom.");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

/* remote control decoder */
अटल पूर्णांक (*rc_decode) (काष्ठा dvb_usb_device *d, u8 *data, पूर्णांक len,
		u32 *event, पूर्णांक *state);
अटल व्योम *rc_keys;
अटल पूर्णांक *rc_keys_size;

u8 regmask[8] = अणु 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff पूर्ण;

काष्ठा af9005_device_state अणु
	u8 sequence;
	पूर्णांक led_state;
	अचिन्हित अक्षर data[256];
पूर्ण;

अटल पूर्णांक af9005_generic_पढ़ो_ग_लिखो(काष्ठा dvb_usb_device *d, u16 reg,
			      पूर्णांक पढ़ोग_लिखो, पूर्णांक type, u8 * values, पूर्णांक len)
अणु
	काष्ठा af9005_device_state *st = d->priv;
	u8 command, seq;
	पूर्णांक i, ret;

	अगर (len < 1) अणु
		err("generic read/write, less than 1 byte. Makes no sense.");
		वापस -EINVAL;
	पूर्ण
	अगर (len > 8) अणु
		err("generic read/write, more than 8 bytes. Not supported.");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&d->data_mutex);
	st->data[0] = 14;		/* rest of buffer length low */
	st->data[1] = 0;		/* rest of buffer length high */

	st->data[2] = AF9005_REGISTER_RW;	/* रेजिस्टर operation */
	st->data[3] = 12;		/* rest of buffer length */

	st->data[4] = seq = st->sequence++;	/* sequence number */

	st->data[5] = (u8) (reg >> 8);	/* रेजिस्टर address */
	st->data[6] = (u8) (reg & 0xff);

	अगर (type == AF9005_OFDM_REG) अणु
		command = AF9005_CMD_OFDM_REG;
	पूर्ण अन्यथा अणु
		command = AF9005_CMD_TUNER;
	पूर्ण

	अगर (len > 1)
		command |=
		    AF9005_CMD_BURST | AF9005_CMD_AUTOINC | (len - 1) << 3;
	command |= पढ़ोग_लिखो;
	अगर (पढ़ोग_लिखो == AF9005_CMD_WRITE)
		क्रम (i = 0; i < len; i++)
			st->data[8 + i] = values[i];
	अन्यथा अगर (type == AF9005_TUNER_REG)
		/* पढ़ो command क्रम tuner, the first byte contains the i2c address */
		st->data[8] = values[0];
	st->data[7] = command;

	ret = dvb_usb_generic_rw(d, st->data, 16, st->data, 17, 0);
	अगर (ret)
		जाओ ret;

	/* sanity check */
	अगर (st->data[2] != AF9005_REGISTER_RW_ACK) अणु
		err("generic read/write, wrong reply code.");
		ret = -EIO;
		जाओ ret;
	पूर्ण
	अगर (st->data[3] != 0x0d) अणु
		err("generic read/write, wrong length in reply.");
		ret = -EIO;
		जाओ ret;
	पूर्ण
	अगर (st->data[4] != seq) अणु
		err("generic read/write, wrong sequence in reply.");
		ret = -EIO;
		जाओ ret;
	पूर्ण
	/*
	 * In thesis, both input and output buffers should have
	 * identical values क्रम st->data[5] to st->data[8].
	 * However, winकरोws driver करोesn't check these fields, in fact
	 * someबार the रेजिस्टर in the reply is dअगरferent that what
	 * has been sent
	 */
	अगर (st->data[16] != 0x01) अणु
		err("generic read/write wrong status code in reply.");
		ret = -EIO;
		जाओ ret;
	पूर्ण

	अगर (पढ़ोग_लिखो == AF9005_CMD_READ)
		क्रम (i = 0; i < len; i++)
			values[i] = st->data[8 + i];

ret:
	mutex_unlock(&d->data_mutex);
	वापस ret;

पूर्ण

पूर्णांक af9005_पढ़ो_ofdm_रेजिस्टर(काष्ठा dvb_usb_device *d, u16 reg, u8 * value)
अणु
	पूर्णांक ret;
	deb_reg("read register %x ", reg);
	ret = af9005_generic_पढ़ो_ग_लिखो(d, reg,
					AF9005_CMD_READ, AF9005_OFDM_REG,
					value, 1);
	अगर (ret)
		deb_reg("failed\n");
	अन्यथा
		deb_reg("value %x\n", *value);
	वापस ret;
पूर्ण

पूर्णांक af9005_पढ़ो_ofdm_रेजिस्टरs(काष्ठा dvb_usb_device *d, u16 reg,
			       u8 * values, पूर्णांक len)
अणु
	पूर्णांक ret;
	deb_reg("read %d registers %x ", len, reg);
	ret = af9005_generic_पढ़ो_ग_लिखो(d, reg,
					AF9005_CMD_READ, AF9005_OFDM_REG,
					values, len);
	अगर (ret)
		deb_reg("failed\n");
	अन्यथा
		debug_dump(values, len, deb_reg);
	वापस ret;
पूर्ण

पूर्णांक af9005_ग_लिखो_ofdm_रेजिस्टर(काष्ठा dvb_usb_device *d, u16 reg, u8 value)
अणु
	पूर्णांक ret;
	u8 temp = value;
	deb_reg("write register %x value %x ", reg, value);
	ret = af9005_generic_पढ़ो_ग_लिखो(d, reg,
					AF9005_CMD_WRITE, AF9005_OFDM_REG,
					&temp, 1);
	अगर (ret)
		deb_reg("failed\n");
	अन्यथा
		deb_reg("ok\n");
	वापस ret;
पूर्ण

पूर्णांक af9005_ग_लिखो_ofdm_रेजिस्टरs(काष्ठा dvb_usb_device *d, u16 reg,
				u8 * values, पूर्णांक len)
अणु
	पूर्णांक ret;
	deb_reg("write %d registers %x values ", len, reg);
	debug_dump(values, len, deb_reg);

	ret = af9005_generic_पढ़ो_ग_लिखो(d, reg,
					AF9005_CMD_WRITE, AF9005_OFDM_REG,
					values, len);
	अगर (ret)
		deb_reg("failed\n");
	अन्यथा
		deb_reg("ok\n");
	वापस ret;
पूर्ण

पूर्णांक af9005_पढ़ो_रेजिस्टर_bits(काष्ठा dvb_usb_device *d, u16 reg, u8 pos,
			      u8 len, u8 * value)
अणु
	u8 temp;
	पूर्णांक ret;
	deb_reg("read bits %x %x %x", reg, pos, len);
	ret = af9005_पढ़ो_ofdm_रेजिस्टर(d, reg, &temp);
	अगर (ret) अणु
		deb_reg(" failed\n");
		वापस ret;
	पूर्ण
	*value = (temp >> pos) & regmask[len - 1];
	deb_reg(" value %x\n", *value);
	वापस 0;

पूर्ण

पूर्णांक af9005_ग_लिखो_रेजिस्टर_bits(काष्ठा dvb_usb_device *d, u16 reg, u8 pos,
			       u8 len, u8 value)
अणु
	u8 temp, mask;
	पूर्णांक ret;
	deb_reg("write bits %x %x %x value %x\n", reg, pos, len, value);
	अगर (pos == 0 && len == 8)
		वापस af9005_ग_लिखो_ofdm_रेजिस्टर(d, reg, value);
	ret = af9005_पढ़ो_ofdm_रेजिस्टर(d, reg, &temp);
	अगर (ret)
		वापस ret;
	mask = regmask[len - 1] << pos;
	temp = (temp & ~mask) | ((value << pos) & mask);
	वापस af9005_ग_लिखो_ofdm_रेजिस्टर(d, reg, temp);

पूर्ण

अटल पूर्णांक af9005_usb_पढ़ो_tuner_रेजिस्टरs(काष्ठा dvb_usb_device *d,
					   u16 reg, u8 * values, पूर्णांक len)
अणु
	वापस af9005_generic_पढ़ो_ग_लिखो(d, reg,
					 AF9005_CMD_READ, AF9005_TUNER_REG,
					 values, len);
पूर्ण

अटल पूर्णांक af9005_usb_ग_लिखो_tuner_रेजिस्टरs(काष्ठा dvb_usb_device *d,
					    u16 reg, u8 * values, पूर्णांक len)
अणु
	वापस af9005_generic_पढ़ो_ग_लिखो(d, reg,
					 AF9005_CMD_WRITE,
					 AF9005_TUNER_REG, values, len);
पूर्ण

पूर्णांक af9005_ग_लिखो_tuner_रेजिस्टरs(काष्ठा dvb_usb_device *d, u16 reg,
				 u8 * values, पूर्णांक len)
अणु
	/* करोn't let the name of this function mislead you: it's just used
	   as an पूर्णांकerface from the firmware to the i2c bus. The actual
	   i2c addresses are contained in the data */
	पूर्णांक ret, i, करोne = 0, fail = 0;
	u8 temp;
	ret = af9005_usb_ग_लिखो_tuner_रेजिस्टरs(d, reg, values, len);
	अगर (ret)
		वापस ret;
	अगर (reg != 0xffff) अणु
		/* check अगर ग_लिखो करोne (0xa40d bit 1) or fail (0xa40d bit 2) */
		क्रम (i = 0; i < 200; i++) अणु
			ret =
			    af9005_पढ़ो_ofdm_रेजिस्टर(d,
						      xd_I2C_i2c_m_status_wdat_करोne,
						      &temp);
			अगर (ret)
				वापस ret;
			करोne = temp & (regmask[i2c_m_status_wdat_करोne_len - 1]
				       << i2c_m_status_wdat_करोne_pos);
			अगर (करोne)
				अवरोध;
			fail = temp & (regmask[i2c_m_status_wdat_fail_len - 1]
				       << i2c_m_status_wdat_fail_pos);
			अगर (fail)
				अवरोध;
			msleep(50);
		पूर्ण
		अगर (i == 200)
			वापस -ETIMEDOUT;
		अगर (fail) अणु
			/* clear ग_लिखो fail bit */
			af9005_ग_लिखो_रेजिस्टर_bits(d,
						   xd_I2C_i2c_m_status_wdat_fail,
						   i2c_m_status_wdat_fail_pos,
						   i2c_m_status_wdat_fail_len,
						   1);
			वापस -EIO;
		पूर्ण
		/* clear ग_लिखो करोne bit */
		ret =
		    af9005_ग_लिखो_रेजिस्टर_bits(d,
					       xd_I2C_i2c_m_status_wdat_fail,
					       i2c_m_status_wdat_करोne_pos,
					       i2c_m_status_wdat_करोne_len, 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक af9005_पढ़ो_tuner_रेजिस्टरs(काष्ठा dvb_usb_device *d, u16 reg, u8 addr,
				u8 * values, पूर्णांक len)
अणु
	/* करोn't let the name of this function mislead you: it's just used
	   as an पूर्णांकerface from the firmware to the i2c bus. The actual
	   i2c addresses are contained in the data */
	पूर्णांक ret, i;
	u8 temp, buf[2];

	buf[0] = addr;		/* tuner i2c address */
	buf[1] = values[0];	/* tuner रेजिस्टर */

	values[0] = addr + 0x01;	/* i2c पढ़ो address */

	अगर (reg == APO_REG_I2C_RW_SILICON_TUNER) अणु
		/* ग_लिखो tuner i2c address to tuner, 0c00c0 unकरोcumented, found by snअगरfing */
		ret = af9005_ग_लिखो_tuner_रेजिस्टरs(d, 0x00c0, buf, 2);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* send पढ़ो command to ofsm */
	ret = af9005_usb_पढ़ो_tuner_रेजिस्टरs(d, reg, values, 1);
	अगर (ret)
		वापस ret;

	/* check अगर पढ़ो करोne */
	क्रम (i = 0; i < 200; i++) अणु
		ret = af9005_पढ़ो_ofdm_रेजिस्टर(d, 0xa408, &temp);
		अगर (ret)
			वापस ret;
		अगर (temp & 0x01)
			अवरोध;
		msleep(50);
	पूर्ण
	अगर (i == 200)
		वापस -ETIMEDOUT;

	/* clear पढ़ो करोne bit (by writing 1) */
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, xd_I2C_i2c_m_data8, 1);
	अगर (ret)
		वापस ret;

	/* get पढ़ो data (available from 0xa400) */
	क्रम (i = 0; i < len; i++) अणु
		ret = af9005_पढ़ो_ofdm_रेजिस्टर(d, 0xa400 + i, &temp);
		अगर (ret)
			वापस ret;
		values[i] = temp;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_i2c_ग_लिखो(काष्ठा dvb_usb_device *d, u8 i2caddr, u8 reg,
			    u8 * data, पूर्णांक len)
अणु
	पूर्णांक ret, i;
	u8 buf[3];
	deb_i2c("i2c_write i2caddr %x, reg %x, len %d data ", i2caddr,
		reg, len);
	debug_dump(data, len, deb_i2c);

	क्रम (i = 0; i < len; i++) अणु
		buf[0] = i2caddr;
		buf[1] = reg + (u8) i;
		buf[2] = data[i];
		ret =
		    af9005_ग_लिखो_tuner_रेजिस्टरs(d,
						 APO_REG_I2C_RW_SILICON_TUNER,
						 buf, 3);
		अगर (ret) अणु
			deb_i2c("i2c_write failed\n");
			वापस ret;
		पूर्ण
	पूर्ण
	deb_i2c("i2c_write ok\n");
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_i2c_पढ़ो(काष्ठा dvb_usb_device *d, u8 i2caddr, u8 reg,
			   u8 * data, पूर्णांक len)
अणु
	पूर्णांक ret, i;
	u8 temp;
	deb_i2c("i2c_read i2caddr %x, reg %x, len %d\n ", i2caddr, reg, len);
	क्रम (i = 0; i < len; i++) अणु
		temp = reg + i;
		ret =
		    af9005_पढ़ो_tuner_रेजिस्टरs(d,
						APO_REG_I2C_RW_SILICON_TUNER,
						i2caddr, &temp, 1);
		अगर (ret) अणु
			deb_i2c("i2c_read failed\n");
			वापस ret;
		पूर्ण
		data[i] = temp;
	पूर्ण
	deb_i2c("i2c data read: ");
	debug_dump(data, len, deb_i2c);
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
			   पूर्णांक num)
अणु
	/* only implements what the mt2060 module करोes, करोn't know how
	   to make it really generic */
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक ret;
	u8 reg, addr;
	u8 *value;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	अगर (num > 2)
		warn("more than 2 i2c messages at a time is not handled yet. TODO.");

	अगर (num == 2) अणु
		/* पढ़ोs a single रेजिस्टर */
		reg = *msg[0].buf;
		addr = msg[0].addr;
		value = msg[1].buf;
		ret = af9005_i2c_पढ़ो(d, addr, reg, value, 1);
		अगर (ret == 0)
			ret = 2;
	पूर्ण अन्यथा अणु
		/* ग_लिखो one or more रेजिस्टरs */
		reg = msg[0].buf[0];
		addr = msg[0].addr;
		value = &msg[0].buf[1];
		ret = af9005_i2c_ग_लिखो(d, addr, reg, value, msg[0].len - 1);
		अगर (ret == 0)
			ret = 1;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस ret;
पूर्ण

अटल u32 af9005_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm af9005_i2c_algo = अणु
	.master_xfer = af9005_i2c_xfer,
	.functionality = af9005_i2c_func,
पूर्ण;

पूर्णांक af9005_send_command(काष्ठा dvb_usb_device *d, u8 command, u8 * wbuf,
			पूर्णांक wlen, u8 * rbuf, पूर्णांक rlen)
अणु
	काष्ठा af9005_device_state *st = d->priv;

	पूर्णांक ret, i, packet_len;
	u8 seq;

	अगर (wlen < 0) अणु
		err("send command, wlen less than 0 bytes. Makes no sense.");
		वापस -EINVAL;
	पूर्ण
	अगर (wlen > 54) अणु
		err("send command, wlen more than 54 bytes. Not supported.");
		वापस -EINVAL;
	पूर्ण
	अगर (rlen > 54) अणु
		err("send command, rlen more than 54 bytes. Not supported.");
		वापस -EINVAL;
	पूर्ण
	packet_len = wlen + 5;

	mutex_lock(&d->data_mutex);

	st->data[0] = (u8) (packet_len & 0xff);
	st->data[1] = (u8) ((packet_len & 0xff00) >> 8);

	st->data[2] = 0x26;		/* packet type */
	st->data[3] = wlen + 3;
	st->data[4] = seq = st->sequence++;
	st->data[5] = command;
	st->data[6] = wlen;
	क्रम (i = 0; i < wlen; i++)
		st->data[7 + i] = wbuf[i];
	ret = dvb_usb_generic_rw(d, st->data, wlen + 7, st->data, rlen + 7, 0);
	अगर (st->data[2] != 0x27) अणु
		err("send command, wrong reply code.");
		ret = -EIO;
	पूर्ण अन्यथा अगर (st->data[4] != seq) अणु
		err("send command, wrong sequence in reply.");
		ret = -EIO;
	पूर्ण अन्यथा अगर (st->data[5] != 0x01) अणु
		err("send command, wrong status code in reply.");
		ret = -EIO;
	पूर्ण अन्यथा अगर (st->data[6] != rlen) अणु
		err("send command, invalid data length in reply.");
		ret = -EIO;
	पूर्ण
	अगर (!ret) अणु
		क्रम (i = 0; i < rlen; i++)
			rbuf[i] = st->data[i + 7];
	पूर्ण

	mutex_unlock(&d->data_mutex);
	वापस ret;
पूर्ण

पूर्णांक af9005_पढ़ो_eeprom(काष्ठा dvb_usb_device *d, u8 address, u8 * values,
		       पूर्णांक len)
अणु
	काष्ठा af9005_device_state *st = d->priv;
	u8 seq;
	पूर्णांक ret, i;

	mutex_lock(&d->data_mutex);

	स_रखो(st->data, 0, माप(st->data));

	st->data[0] = 14;		/* length of rest of packet low */
	st->data[1] = 0;		/* length of rest of packer high */

	st->data[2] = 0x2a;		/* पढ़ो/ग_लिखो eeprom */

	st->data[3] = 12;		/* size */

	st->data[4] = seq = st->sequence++;

	st->data[5] = 0;		/* पढ़ो */

	st->data[6] = len;
	st->data[7] = address;
	ret = dvb_usb_generic_rw(d, st->data, 16, st->data, 14, 0);
	अगर (st->data[2] != 0x2b) अणु
		err("Read eeprom, invalid reply code");
		ret = -EIO;
	पूर्ण अन्यथा अगर (st->data[3] != 10) अणु
		err("Read eeprom, invalid reply length");
		ret = -EIO;
	पूर्ण अन्यथा अगर (st->data[4] != seq) अणु
		err("Read eeprom, wrong sequence in reply ");
		ret = -EIO;
	पूर्ण अन्यथा अगर (st->data[5] != 1) अणु
		err("Read eeprom, wrong status in reply ");
		ret = -EIO;
	पूर्ण

	अगर (!ret) अणु
		क्रम (i = 0; i < len; i++)
			values[i] = st->data[6 + i];
	पूर्ण
	mutex_unlock(&d->data_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक af9005_boot_packet(काष्ठा usb_device *udev, पूर्णांक type, u8 *reply,
			      u8 *buf, पूर्णांक size)
अणु
	u16 checksum;
	पूर्णांक act_len = 0, i, ret;

	स_रखो(buf, 0, size);
	buf[0] = (u8) (FW_BULKOUT_SIZE & 0xff);
	buf[1] = (u8) ((FW_BULKOUT_SIZE >> 8) & 0xff);
	चयन (type) अणु
	हाल FW_CONFIG:
		buf[2] = 0x11;
		buf[3] = 0x04;
		buf[4] = 0x00;	/* sequence number, original driver करोesn't increment it here */
		buf[5] = 0x03;
		checksum = buf[4] + buf[5];
		buf[6] = (u8) ((checksum >> 8) & 0xff);
		buf[7] = (u8) (checksum & 0xff);
		अवरोध;
	हाल FW_CONFIRM:
		buf[2] = 0x11;
		buf[3] = 0x04;
		buf[4] = 0x00;	/* sequence number, original driver करोesn't increment it here */
		buf[5] = 0x01;
		checksum = buf[4] + buf[5];
		buf[6] = (u8) ((checksum >> 8) & 0xff);
		buf[7] = (u8) (checksum & 0xff);
		अवरोध;
	हाल FW_BOOT:
		buf[2] = 0x10;
		buf[3] = 0x08;
		buf[4] = 0x00;	/* sequence number, original driver करोesn't increment it here */
		buf[5] = 0x97;
		buf[6] = 0xaa;
		buf[7] = 0x55;
		buf[8] = 0xa5;
		buf[9] = 0x5a;
		checksum = 0;
		क्रम (i = 4; i <= 9; i++)
			checksum += buf[i];
		buf[10] = (u8) ((checksum >> 8) & 0xff);
		buf[11] = (u8) (checksum & 0xff);
		अवरोध;
	शेष:
		err("boot packet invalid boot packet type");
		वापस -EINVAL;
	पूर्ण
	deb_fw(">>> ");
	debug_dump(buf, FW_BULKOUT_SIZE + 2, deb_fw);

	ret = usb_bulk_msg(udev,
			   usb_sndbulkpipe(udev, 0x02),
			   buf, FW_BULKOUT_SIZE + 2, &act_len, 2000);
	अगर (ret)
		err("boot packet bulk message failed: %d (%d/%d)", ret,
		    FW_BULKOUT_SIZE + 2, act_len);
	अन्यथा
		ret = act_len != FW_BULKOUT_SIZE + 2 ? -1 : 0;
	अगर (ret)
		वापस ret;
	स_रखो(buf, 0, 9);
	ret = usb_bulk_msg(udev,
			   usb_rcvbulkpipe(udev, 0x01), buf, 9, &act_len, 2000);
	अगर (ret) अणु
		err("boot packet recv bulk message failed: %d", ret);
		वापस ret;
	पूर्ण
	deb_fw("<<< ");
	debug_dump(buf, act_len, deb_fw);
	checksum = 0;
	चयन (type) अणु
	हाल FW_CONFIG:
		अगर (buf[2] != 0x11) अणु
			err("boot bad config header.");
			वापस -EIO;
		पूर्ण
		अगर (buf[3] != 0x05) अणु
			err("boot bad config size.");
			वापस -EIO;
		पूर्ण
		अगर (buf[4] != 0x00) अणु
			err("boot bad config sequence.");
			वापस -EIO;
		पूर्ण
		अगर (buf[5] != 0x04) अणु
			err("boot bad config subtype.");
			वापस -EIO;
		पूर्ण
		क्रम (i = 4; i <= 6; i++)
			checksum += buf[i];
		अगर (buf[7] * 256 + buf[8] != checksum) अणु
			err("boot bad config checksum.");
			वापस -EIO;
		पूर्ण
		*reply = buf[6];
		अवरोध;
	हाल FW_CONFIRM:
		अगर (buf[2] != 0x11) अणु
			err("boot bad confirm header.");
			वापस -EIO;
		पूर्ण
		अगर (buf[3] != 0x05) अणु
			err("boot bad confirm size.");
			वापस -EIO;
		पूर्ण
		अगर (buf[4] != 0x00) अणु
			err("boot bad confirm sequence.");
			वापस -EIO;
		पूर्ण
		अगर (buf[5] != 0x02) अणु
			err("boot bad confirm subtype.");
			वापस -EIO;
		पूर्ण
		क्रम (i = 4; i <= 6; i++)
			checksum += buf[i];
		अगर (buf[7] * 256 + buf[8] != checksum) अणु
			err("boot bad confirm checksum.");
			वापस -EIO;
		पूर्ण
		*reply = buf[6];
		अवरोध;
	हाल FW_BOOT:
		अगर (buf[2] != 0x10) अणु
			err("boot bad boot header.");
			वापस -EIO;
		पूर्ण
		अगर (buf[3] != 0x05) अणु
			err("boot bad boot size.");
			वापस -EIO;
		पूर्ण
		अगर (buf[4] != 0x00) अणु
			err("boot bad boot sequence.");
			वापस -EIO;
		पूर्ण
		अगर (buf[5] != 0x01) अणु
			err("boot bad boot pattern 01.");
			वापस -EIO;
		पूर्ण
		अगर (buf[6] != 0x10) अणु
			err("boot bad boot pattern 10.");
			वापस -EIO;
		पूर्ण
		क्रम (i = 4; i <= 6; i++)
			checksum += buf[i];
		अगर (buf[7] * 256 + buf[8] != checksum) अणु
			err("boot bad boot checksum.");
			वापस -EIO;
		पूर्ण
		अवरोध;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक af9005_करोwnload_firmware(काष्ठा usb_device *udev, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक i, packets, ret, act_len;

	u8 *buf;
	u8 reply;

	buf = kदो_स्मृति(FW_BULKOUT_SIZE + 2, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = af9005_boot_packet(udev, FW_CONFIG, &reply, buf,
				 FW_BULKOUT_SIZE + 2);
	अगर (ret)
		जाओ err;
	अगर (reply != 0x01) अणु
		err("before downloading firmware, FW_CONFIG expected 0x01, received 0x%x", reply);
		ret = -EIO;
		जाओ err;
	पूर्ण
	packets = fw->size / FW_BULKOUT_SIZE;
	buf[0] = (u8) (FW_BULKOUT_SIZE & 0xff);
	buf[1] = (u8) ((FW_BULKOUT_SIZE >> 8) & 0xff);
	क्रम (i = 0; i < packets; i++) अणु
		स_नकल(&buf[2], fw->data + i * FW_BULKOUT_SIZE,
		       FW_BULKOUT_SIZE);
		deb_fw(">>> ");
		debug_dump(buf, FW_BULKOUT_SIZE + 2, deb_fw);
		ret = usb_bulk_msg(udev,
				   usb_sndbulkpipe(udev, 0x02),
				   buf, FW_BULKOUT_SIZE + 2, &act_len, 1000);
		अगर (ret) अणु
			err("firmware download failed at packet %d with code %d", i, ret);
			जाओ err;
		पूर्ण
	पूर्ण
	ret = af9005_boot_packet(udev, FW_CONFIRM, &reply,
				 buf, FW_BULKOUT_SIZE + 2);
	अगर (ret)
		जाओ err;
	अगर (reply != (u8) (packets & 0xff)) अणु
		err("after downloading firmware, FW_CONFIRM expected 0x%x, received 0x%x", packets & 0xff, reply);
		ret = -EIO;
		जाओ err;
	पूर्ण
	ret = af9005_boot_packet(udev, FW_BOOT, &reply, buf,
				 FW_BULKOUT_SIZE + 2);
	अगर (ret)
		जाओ err;
	ret = af9005_boot_packet(udev, FW_CONFIG, &reply, buf,
				 FW_BULKOUT_SIZE + 2);
	अगर (ret)
		जाओ err;
	अगर (reply != 0x02) अणु
		err("after downloading firmware, FW_CONFIG expected 0x02, received 0x%x", reply);
		ret = -EIO;
		जाओ err;
	पूर्ण

err:
	kमुक्त(buf);
	वापस ret;

पूर्ण

पूर्णांक af9005_led_control(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	काष्ठा af9005_device_state *st = d->priv;
	पूर्णांक temp, ret;

	अगर (onoff && dvb_usb_af9005_led)
		temp = 1;
	अन्यथा
		temp = 0;
	अगर (st->led_state != temp) अणु
		ret =
		    af9005_ग_लिखो_रेजिस्टर_bits(d, xd_p_reg_top_locken1,
					       reg_top_locken1_pos,
					       reg_top_locken1_len, temp);
		अगर (ret)
			वापस ret;
		ret =
		    af9005_ग_लिखो_रेजिस्टर_bits(d, xd_p_reg_top_lock1,
					       reg_top_lock1_pos,
					       reg_top_lock1_len, temp);
		अगर (ret)
			वापस ret;
		st->led_state = temp;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	u8 buf[8];
	पूर्णांक i;

	/* without these calls the first commands after करोwnloading
	   the firmware fail. I put these calls here to simulate
	   what it is करोne in dvb-usb-init.c.
	 */
	काष्ठा usb_device *udev = adap->dev->udev;
	usb_clear_halt(udev, usb_sndbulkpipe(udev, 2));
	usb_clear_halt(udev, usb_rcvbulkpipe(udev, 1));
	अगर (dvb_usb_af9005_dump_eeprom) अणु
		prपूर्णांकk("EEPROM DUMP\n");
		क्रम (i = 0; i < 255; i += 8) अणु
			af9005_पढ़ो_eeprom(adap->dev, i, buf, 8);
			debug_dump(buf, 8, prपूर्णांकk);
		पूर्ण
	पूर्ण
	adap->fe_adap[0].fe = af9005_fe_attach(adap->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_rc_query(काष्ठा dvb_usb_device *d, u32 * event, पूर्णांक *state)
अणु
	काष्ठा af9005_device_state *st = d->priv;
	पूर्णांक ret, len;
	u8 seq;

	*state = REMOTE_NO_KEY_PRESSED;
	अगर (rc_decode == शून्य) अणु
		/* it shouldn't never come here */
		वापस 0;
	पूर्ण

	mutex_lock(&d->data_mutex);

	/* deb_info("rc_query\n"); */
	st->data[0] = 3;		/* rest of packet length low */
	st->data[1] = 0;		/* rest of packet length high */
	st->data[2] = 0x40;		/* पढ़ो remote */
	st->data[3] = 1;		/* rest of packet length */
	st->data[4] = seq = st->sequence++;	/* sequence number */
	ret = dvb_usb_generic_rw(d, st->data, 5, st->data, 256, 0);
	अगर (ret) अणु
		err("rc query failed");
		जाओ ret;
	पूर्ण
	अगर (st->data[2] != 0x41) अणु
		err("rc query bad header.");
		ret = -EIO;
		जाओ ret;
	पूर्ण अन्यथा अगर (st->data[4] != seq) अणु
		err("rc query bad sequence.");
		ret = -EIO;
		जाओ ret;
	पूर्ण
	len = st->data[5];
	अगर (len > 246) अणु
		err("rc query invalid length");
		ret = -EIO;
		जाओ ret;
	पूर्ण
	अगर (len > 0) अणु
		deb_rc("rc data (%d) ", len);
		debug_dump((st->data + 6), len, deb_rc);
		ret = rc_decode(d, &st->data[6], len, event, state);
		अगर (ret) अणु
			err("rc_decode failed");
			जाओ ret;
		पूर्ण अन्यथा अणु
			deb_rc("rc_decode state %x event %x\n", *state, *event);
			अगर (*state == REMOTE_KEY_REPEAT)
				*event = d->last_event;
		पूर्ण
	पूर्ण

ret:
	mutex_unlock(&d->data_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक af9005_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु

	वापस 0;
पूर्ण

अटल पूर्णांक af9005_pid_filter_control(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	पूर्णांक ret;
	deb_info("pid filter control  onoff %d\n", onoff);
	अगर (onoff) अणु
		ret =
		    af9005_ग_लिखो_ofdm_रेजिस्टर(adap->dev, XD_MP2IF_DMX_CTRL, 1);
		अगर (ret)
			वापस ret;
		ret =
		    af9005_ग_लिखो_रेजिस्टर_bits(adap->dev,
					       XD_MP2IF_DMX_CTRL, 1, 1, 1);
		अगर (ret)
			वापस ret;
		ret =
		    af9005_ग_लिखो_ofdm_रेजिस्टर(adap->dev, XD_MP2IF_DMX_CTRL, 1);
	पूर्ण अन्यथा
		ret =
		    af9005_ग_लिखो_ofdm_रेजिस्टर(adap->dev, XD_MP2IF_DMX_CTRL, 0);
	अगर (ret)
		वापस ret;
	deb_info("pid filter control ok\n");
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_pid_filter(काष्ठा dvb_usb_adapter *adap, पूर्णांक index,
			     u16 pid, पूर्णांक onoff)
अणु
	u8 cmd = index & 0x1f;
	पूर्णांक ret;
	deb_info("set pid filter, index %d, pid %x, onoff %d\n", index,
		 pid, onoff);
	अगर (onoff) अणु
		/* cannot use it as pid_filter_ctrl since it has to be करोne
		   beक्रमe setting the first pid */
		अगर (adap->feedcount == 1) अणु
			deb_info("first pid set, enable pid table\n");
			ret = af9005_pid_filter_control(adap, onoff);
			अगर (ret)
				वापस ret;
		पूर्ण
		ret =
		    af9005_ग_लिखो_ofdm_रेजिस्टर(adap->dev,
					       XD_MP2IF_PID_DATA_L,
					       (u8) (pid & 0xff));
		अगर (ret)
			वापस ret;
		ret =
		    af9005_ग_लिखो_ofdm_रेजिस्टर(adap->dev,
					       XD_MP2IF_PID_DATA_H,
					       (u8) (pid >> 8));
		अगर (ret)
			वापस ret;
		cmd |= 0x20 | 0x40;
	पूर्ण अन्यथा अणु
		अगर (adap->feedcount == 0) अणु
			deb_info("last pid unset, disable pid table\n");
			ret = af9005_pid_filter_control(adap, onoff);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(adap->dev, XD_MP2IF_PID_IDX, cmd);
	अगर (ret)
		वापस ret;
	deb_info("set pid ok\n");
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_identअगरy_state(काष्ठा usb_device *udev,
				 स्थिर काष्ठा dvb_usb_device_properties *props,
				 स्थिर काष्ठा dvb_usb_device_description **desc,
				 पूर्णांक *cold)
अणु
	पूर्णांक ret;
	u8 reply, *buf;

	buf = kदो_स्मृति(FW_BULKOUT_SIZE + 2, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = af9005_boot_packet(udev, FW_CONFIG, &reply,
				 buf, FW_BULKOUT_SIZE + 2);
	अगर (ret)
		जाओ err;
	deb_info("result of FW_CONFIG in identify state %d\n", reply);
	अगर (reply == 0x01)
		*cold = 1;
	अन्यथा अगर (reply == 0x02)
		*cold = 0;
	अन्यथा
		ret = -EIO;
	अगर (!ret)
		deb_info("Identify state cold = %d\n", *cold);

err:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल काष्ठा dvb_usb_device_properties af9005_properties;

अटल पूर्णांक af9005_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	वापस dvb_usb_device_init(पूर्णांकf, &af9005_properties,
				  THIS_MODULE, शून्य, adapter_nr);
पूर्ण

क्रमागत af9005_usb_table_entry अणु
	AFATECH_AF9005,
	TERRATEC_AF9005,
	ANSONIC_AF9005,
पूर्ण;

अटल काष्ठा usb_device_id af9005_usb_table[] = अणु
	[AFATECH_AF9005] = अणुUSB_DEVICE(USB_VID_AFATECH,
				USB_PID_AFATECH_AF9005)पूर्ण,
	[TERRATEC_AF9005] = अणुUSB_DEVICE(USB_VID_TERRATEC,
				USB_PID_TERRATEC_CINERGY_T_USB_XE)पूर्ण,
	[ANSONIC_AF9005] = अणुUSB_DEVICE(USB_VID_ANSONIC,
				USB_PID_ANSONIC_DVBT_USB)पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, af9005_usb_table);

अटल काष्ठा dvb_usb_device_properties af9005_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = DEVICE_SPECIFIC,
	.firmware = "af9005.fw",
	.करोwnload_firmware = af9005_करोwnload_firmware,
	.no_reconnect = 1,

	.size_of_priv = माप(काष्ठा af9005_device_state),

	.num_adapters = 1,
	.adapter = अणु
		    अणु
		    .num_frontends = 1,
		    .fe = अणुअणु
		     .caps =
		     DVB_USB_ADAP_HAS_PID_FILTER |
		     DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
		     .pid_filter_count = 32,
		     .pid_filter = af9005_pid_filter,
		     /* .pid_filter_ctrl = af9005_pid_filter_control, */
		     .frontend_attach = af9005_frontend_attach,
		     /* .tuner_attach     = af9005_tuner_attach, */
		     /* parameter क्रम the MPEG2-data transfer */
		     .stream = अणु
				.type = USB_BULK,
				.count = 10,
				.endpoपूर्णांक = 0x04,
				.u = अणु
				      .bulk = अणु
					       .buffersize = 4096,	/* actual size seen is 3948 */
					       पूर्ण
				      पूर्ण
				पूर्ण,
		     पूर्णपूर्ण,
		     पूर्ण
		    पूर्ण,
	.घातer_ctrl = af9005_घातer_ctrl,
	.identअगरy_state = af9005_identअगरy_state,

	.i2c_algo = &af9005_i2c_algo,

	.rc.legacy = अणु
		.rc_पूर्णांकerval = 200,
		.rc_map_table = शून्य,
		.rc_map_size = 0,
		.rc_query = af9005_rc_query,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक          = 2,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 1,

	.num_device_descs = 3,
	.devices = अणु
		    अणु.name = "Afatech DVB-T USB1.1 stick",
		     .cold_ids = अणु&af9005_usb_table[AFATECH_AF9005], शून्यपूर्ण,
		     .warm_ids = अणुशून्यपूर्ण,
		     पूर्ण,
		    अणु.name = "TerraTec Cinergy T USB XE",
		     .cold_ids = अणु&af9005_usb_table[TERRATEC_AF9005], शून्यपूर्ण,
		     .warm_ids = अणुशून्यपूर्ण,
		     पूर्ण,
		    अणु.name = "Ansonic DVB-T USB1.1 stick",
		     .cold_ids = अणु&af9005_usb_table[ANSONIC_AF9005], शून्यपूर्ण,
		     .warm_ids = अणुशून्यपूर्ण,
		     पूर्ण,
		    अणुशून्यपूर्ण,
		    पूर्ण
पूर्ण;

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver af9005_usb_driver = अणु
	.name = "dvb_usb_af9005",
	.probe = af9005_usb_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table = af9005_usb_table,
पूर्ण;

/* module stuff */
अटल पूर्णांक __init af9005_usb_module_init(व्योम)
अणु
	पूर्णांक result;
	अगर ((result = usb_रेजिस्टर(&af9005_usb_driver))) अणु
		err("usb_register failed. (%d)", result);
		वापस result;
	पूर्ण
#अगर IS_MODULE(CONFIG_DVB_USB_AF9005) || defined(CONFIG_DVB_USB_AF9005_REMOTE)
	/* FIXME: convert to todays kernel IR infraकाष्ठाure */
	rc_decode = symbol_request(af9005_rc_decode);
	rc_keys = symbol_request(rc_map_af9005_table);
	rc_keys_size = symbol_request(rc_map_af9005_table_size);
#पूर्ण_अगर
	अगर (rc_decode == शून्य || rc_keys == शून्य || rc_keys_size == शून्य) अणु
		err("af9005_rc_decode function not found, disabling remote");
		af9005_properties.rc.legacy.rc_query = शून्य;
	पूर्ण अन्यथा अणु
		af9005_properties.rc.legacy.rc_map_table = rc_keys;
		af9005_properties.rc.legacy.rc_map_size = *rc_keys_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास af9005_usb_module_निकास(व्योम)
अणु
	/* release rc decode symbols */
	अगर (rc_decode != शून्य)
		symbol_put(af9005_rc_decode);
	अगर (rc_keys != शून्य)
		symbol_put(rc_map_af9005_table);
	अगर (rc_keys_size != शून्य)
		symbol_put(rc_map_af9005_table_size);
	/* deरेजिस्टर this driver from the USB subप्रणाली */
	usb_deरेजिस्टर(&af9005_usb_driver);
पूर्ण

module_init(af9005_usb_module_init);
module_निकास(af9005_usb_module_निकास);

MODULE_AUTHOR("Luca Olivetti <luca@ventoso.org>");
MODULE_DESCRIPTION("Driver for Afatech 9005 DVB-T USB1.1 stick");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
