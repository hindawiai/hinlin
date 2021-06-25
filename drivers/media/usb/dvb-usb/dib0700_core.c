<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Linux driver क्रम devices based on the DiBcom DiB0700 USB bridge
 *
 *  Copyright (C) 2005-6 DiBcom, SA
 */
#समावेश "dib0700.h"

/* debug */
पूर्णांक dvb_usb_dib0700_debug;
module_param_named(debug,dvb_usb_dib0700_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,2=fw,4=fwdata,8=data (or-able))." DVB_USB_DEBUG_STATUS);

अटल पूर्णांक nb_packet_buffer_size = 21;
module_param(nb_packet_buffer_size, पूर्णांक, 0644);
MODULE_PARM_DESC(nb_packet_buffer_size,
	"Set the dib0700 driver data buffer size. This parameter corresponds to the number of TS packets. The actual size of the data buffer corresponds to this parameter multiplied by 188 (default: 21)");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);


पूर्णांक dib0700_get_version(काष्ठा dvb_usb_device *d, u32 *hwversion,
			u32 *romversion, u32 *ramversion, u32 *fwtype)
अणु
	काष्ठा dib0700_state *st = d->priv;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex) < 0) अणु
		err("could not acquire lock");
		वापस -EINTR;
	पूर्ण

	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0),
				  REQUEST_GET_VERSION,
				  USB_TYPE_VENDOR | USB_सूची_IN, 0, 0,
				  st->buf, 16, USB_CTRL_GET_TIMEOUT);
	अगर (hwversion != शून्य)
		*hwversion  = (st->buf[0] << 24)  | (st->buf[1] << 16)  |
			(st->buf[2] << 8)  | st->buf[3];
	अगर (romversion != शून्य)
		*romversion = (st->buf[4] << 24)  | (st->buf[5] << 16)  |
			(st->buf[6] << 8)  | st->buf[7];
	अगर (ramversion != शून्य)
		*ramversion = (st->buf[8] << 24)  | (st->buf[9] << 16)  |
			(st->buf[10] << 8) | st->buf[11];
	अगर (fwtype != शून्य)
		*fwtype     = (st->buf[12] << 24) | (st->buf[13] << 16) |
			(st->buf[14] << 8) | st->buf[15];
	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

/* expecting rx buffer: request data[0] data[1] ... data[2] */
अटल पूर्णांक dib0700_ctrl_wr(काष्ठा dvb_usb_device *d, u8 *tx, u8 txlen)
अणु
	पूर्णांक status;

	deb_data(">>> ");
	debug_dump(tx, txlen, deb_data);

	status = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev,0),
		tx[0], USB_TYPE_VENDOR | USB_सूची_OUT, 0, 0, tx, txlen,
		USB_CTRL_GET_TIMEOUT);

	अगर (status != txlen)
		deb_data("ep 0 write error (status = %d, len: %d)\n",status,txlen);

	वापस status < 0 ? status : 0;
पूर्ण

/* expecting tx buffer: request data[0] ... data[n] (n <= 4) */
पूर्णांक dib0700_ctrl_rd(काष्ठा dvb_usb_device *d, u8 *tx, u8 txlen, u8 *rx, u8 rxlen)
अणु
	u16 index, value;
	पूर्णांक status;

	अगर (txlen < 2) अणु
		err("tx buffer length is smaller than 2. Makes no sense.");
		वापस -EINVAL;
	पूर्ण
	अगर (txlen > 4) अणु
		err("tx buffer length is larger than 4. Not supported.");
		वापस -EINVAL;
	पूर्ण

	deb_data(">>> ");
	debug_dump(tx,txlen,deb_data);

	value = ((txlen - 2) << 8) | tx[1];
	index = 0;
	अगर (txlen > 2)
		index |= (tx[2] << 8);
	अगर (txlen > 3)
		index |= tx[3];

	status = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev,0), tx[0],
			USB_TYPE_VENDOR | USB_सूची_IN, value, index, rx, rxlen,
			USB_CTRL_GET_TIMEOUT);

	अगर (status < 0)
		deb_info("ep 0 read error (status = %d)\n",status);

	deb_data("<<< ");
	debug_dump(rx, rxlen, deb_data);

	वापस status; /* length in हाल of success */
पूर्ण

पूर्णांक dib0700_set_gpio(काष्ठा dvb_usb_device *d, क्रमागत dib07x0_gpios gpio, u8 gpio_dir, u8 gpio_val)
अणु
	काष्ठा dib0700_state *st = d->priv;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex) < 0) अणु
		err("could not acquire lock");
		वापस -EINTR;
	पूर्ण

	st->buf[0] = REQUEST_SET_GPIO;
	st->buf[1] = gpio;
	st->buf[2] = ((gpio_dir & 0x01) << 7) | ((gpio_val & 0x01) << 6);

	ret = dib0700_ctrl_wr(d, st->buf, 3);

	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dib0700_set_usb_xfer_len(काष्ठा dvb_usb_device *d, u16 nb_ts_packets)
अणु
	काष्ठा dib0700_state *st = d->priv;
	पूर्णांक ret;

	अगर (st->fw_version >= 0x10201) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex) < 0) अणु
			err("could not acquire lock");
			वापस -EINTR;
		पूर्ण

		st->buf[0] = REQUEST_SET_USB_XFER_LEN;
		st->buf[1] = (nb_ts_packets >> 8) & 0xff;
		st->buf[2] = nb_ts_packets & 0xff;

		deb_info("set the USB xfer len to %i Ts packet\n", nb_ts_packets);

		ret = dib0700_ctrl_wr(d, st->buf, 3);
		mutex_unlock(&d->usb_mutex);
	पूर्ण अन्यथा अणु
		deb_info("this firmware does not allow to change the USB xfer len\n");
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * I2C master xfer function (supported in 1.20 firmware)
 */
अटल पूर्णांक dib0700_i2c_xfer_new(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg,
				पूर्णांक num)
अणु
	/* The new i2c firmware messages are more reliable and in particular
	   properly support i2c पढ़ो calls not preceded by a ग_लिखो */

	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा dib0700_state *st = d->priv;
	uपूर्णांक8_t bus_mode = 1;  /* 0=eeprom bus, 1=frontend bus */
	uपूर्णांक8_t gen_mode = 0; /* 0=master i2c, 1=gpio i2c */
	uपूर्णांक8_t en_start = 0;
	uपूर्णांक8_t en_stop = 0;
	पूर्णांक result, i;

	/* Ensure nobody अन्यथा hits the i2c bus जबतक we're sending our
	   sequence of messages, (such as the remote control thपढ़ो) */
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EINTR;

	क्रम (i = 0; i < num; i++) अणु
		अगर (i == 0) अणु
			/* First message in the transaction */
			en_start = 1;
		पूर्ण अन्यथा अगर (!(msg[i].flags & I2C_M_NOSTART)) अणु
			/* Device supports repeated-start */
			en_start = 1;
		पूर्ण अन्यथा अणु
			/* Not the first packet and device करोesn't support
			   repeated start */
			en_start = 0;
		पूर्ण
		अगर (i == (num - 1)) अणु
			/* Last message in the transaction */
			en_stop = 1;
		पूर्ण

		अगर (msg[i].flags & I2C_M_RD) अणु
			/* Read request */
			u16 index, value;
			uपूर्णांक8_t i2c_dest;

			i2c_dest = (msg[i].addr << 1);
			value = ((en_start << 7) | (en_stop << 6) |
				 (msg[i].len & 0x3F)) << 8 | i2c_dest;
			/* I2C ctrl + FE bus; */
			index = ((gen_mode << 6) & 0xC0) |
				((bus_mode << 4) & 0x30);

			result = usb_control_msg(d->udev,
						 usb_rcvctrlpipe(d->udev, 0),
						 REQUEST_NEW_I2C_READ,
						 USB_TYPE_VENDOR | USB_सूची_IN,
						 value, index, st->buf,
						 msg[i].len,
						 USB_CTRL_GET_TIMEOUT);
			अगर (result < 0) अणु
				deb_info("i2c read error (status = %d)\n", result);
				जाओ unlock;
			पूर्ण

			अगर (msg[i].len > माप(st->buf)) अणु
				deb_info("buffer too small to fit %d bytes\n",
					 msg[i].len);
				result = -EIO;
				जाओ unlock;
			पूर्ण

			स_नकल(msg[i].buf, st->buf, msg[i].len);

			deb_data("<<< ");
			debug_dump(msg[i].buf, msg[i].len, deb_data);

		पूर्ण अन्यथा अणु
			/* Write request */
			अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex) < 0) अणु
				err("could not acquire lock");
				result = -EINTR;
				जाओ unlock;
			पूर्ण
			st->buf[0] = REQUEST_NEW_I2C_WRITE;
			st->buf[1] = msg[i].addr << 1;
			st->buf[2] = (en_start << 7) | (en_stop << 6) |
				(msg[i].len & 0x3F);
			/* I2C ctrl + FE bus; */
			st->buf[3] = ((gen_mode << 6) & 0xC0) |
				 ((bus_mode << 4) & 0x30);

			अगर (msg[i].len > माप(st->buf) - 4) अणु
				deb_info("i2c message to big: %d\n",
					 msg[i].len);
				mutex_unlock(&d->usb_mutex);
				result = -EIO;
				जाओ unlock;
			पूर्ण

			/* The Actual i2c payload */
			स_नकल(&st->buf[4], msg[i].buf, msg[i].len);

			deb_data(">>> ");
			debug_dump(st->buf, msg[i].len + 4, deb_data);

			result = usb_control_msg(d->udev,
						 usb_sndctrlpipe(d->udev, 0),
						 REQUEST_NEW_I2C_WRITE,
						 USB_TYPE_VENDOR | USB_सूची_OUT,
						 0, 0, st->buf, msg[i].len + 4,
						 USB_CTRL_GET_TIMEOUT);
			mutex_unlock(&d->usb_mutex);
			अगर (result < 0) अणु
				deb_info("i2c write error (status = %d)\n", result);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	result = i;

unlock:
	mutex_unlock(&d->i2c_mutex);
	वापस result;
पूर्ण

/*
 * I2C master xfer function (pre-1.20 firmware)
 */
अटल पूर्णांक dib0700_i2c_xfer_legacy(काष्ठा i2c_adapter *adap,
				   काष्ठा i2c_msg *msg, पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा dib0700_state *st = d->priv;
	पूर्णांक i, len, result;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EINTR;
	अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex) < 0) अणु
		err("could not acquire lock");
		mutex_unlock(&d->i2c_mutex);
		वापस -EINTR;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		/* fill in the address */
		st->buf[1] = msg[i].addr << 1;
		/* fill the buffer */
		अगर (msg[i].len > माप(st->buf) - 2) अणु
			deb_info("i2c xfer to big: %d\n",
				msg[i].len);
			result = -EIO;
			जाओ unlock;
		पूर्ण
		स_नकल(&st->buf[2], msg[i].buf, msg[i].len);

		/* ग_लिखो/पढ़ो request */
		अगर (i+1 < num && (msg[i+1].flags & I2C_M_RD)) अणु
			st->buf[0] = REQUEST_I2C_READ;
			st->buf[1] |= 1;

			/* special thing in the current firmware: when length is zero the पढ़ो-failed */
			len = dib0700_ctrl_rd(d, st->buf, msg[i].len + 2,
					      st->buf, msg[i + 1].len);
			अगर (len <= 0) अणु
				deb_info("I2C read failed on address 0x%02x\n",
						msg[i].addr);
				result = -EIO;
				जाओ unlock;
			पूर्ण

			अगर (msg[i + 1].len > माप(st->buf)) अणु
				deb_info("i2c xfer buffer to small for %d\n",
					msg[i].len);
				result = -EIO;
				जाओ unlock;
			पूर्ण
			स_नकल(msg[i + 1].buf, st->buf, msg[i + 1].len);

			msg[i+1].len = len;

			i++;
		पूर्ण अन्यथा अणु
			st->buf[0] = REQUEST_I2C_WRITE;
			result = dib0700_ctrl_wr(d, st->buf, msg[i].len + 2);
			अगर (result < 0)
				जाओ unlock;
		पूर्ण
	पूर्ण
	result = i;
unlock:
	mutex_unlock(&d->usb_mutex);
	mutex_unlock(&d->i2c_mutex);

	वापस result;
पूर्ण

अटल पूर्णांक dib0700_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg,
			    पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा dib0700_state *st = d->priv;

	अगर (st->fw_use_new_i2c_api == 1) अणु
		/* User running at least fw 1.20 */
		वापस dib0700_i2c_xfer_new(adap, msg, num);
	पूर्ण अन्यथा अणु
		/* Use legacy calls */
		वापस dib0700_i2c_xfer_legacy(adap, msg, num);
	पूर्ण
पूर्ण

अटल u32 dib0700_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

काष्ठा i2c_algorithm dib0700_i2c_algo = अणु
	.master_xfer   = dib0700_i2c_xfer,
	.functionality = dib0700_i2c_func,
पूर्ण;

पूर्णांक dib0700_identअगरy_state(काष्ठा usb_device *udev,
			   स्थिर काष्ठा dvb_usb_device_properties *props,
			   स्थिर काष्ठा dvb_usb_device_description **desc,
			   पूर्णांक *cold)
अणु
	s16 ret;
	u8 *b;

	b = kदो_स्मृति(16, GFP_KERNEL);
	अगर (!b)
		वापस	-ENOMEM;


	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
		REQUEST_GET_VERSION, USB_TYPE_VENDOR | USB_सूची_IN, 0, 0, b, 16, USB_CTRL_GET_TIMEOUT);

	deb_info("FW GET_VERSION length: %d\n",ret);

	*cold = ret <= 0;
	deb_info("cold: %d\n", *cold);

	kमुक्त(b);
	वापस 0;
पूर्ण

अटल पूर्णांक dib0700_set_घड़ी(काष्ठा dvb_usb_device *d, u8 en_pll,
	u8 pll_src, u8 pll_range, u8 घड़ी_gpio3, u16 pll_preभाग,
	u16 pll_loopभाग, u16 मुक्त_भाग, u16 dsuScaler)
अणु
	काष्ठा dib0700_state *st = d->priv;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex) < 0) अणु
		err("could not acquire lock");
		वापस -EINTR;
	पूर्ण

	st->buf[0] = REQUEST_SET_CLOCK;
	st->buf[1] = (en_pll << 7) | (pll_src << 6) |
		(pll_range << 5) | (घड़ी_gpio3 << 4);
	st->buf[2] = (pll_preभाग >> 8)  & 0xff; /* MSB */
	st->buf[3] =  pll_preभाग        & 0xff; /* LSB */
	st->buf[4] = (pll_loopभाग >> 8) & 0xff; /* MSB */
	st->buf[5] =  pll_loopभाग       & 0xff; /* LSB */
	st->buf[6] = (मुक्त_भाग >> 8)    & 0xff; /* MSB */
	st->buf[7] =  मुक्त_भाग          & 0xff; /* LSB */
	st->buf[8] = (dsuScaler >> 8)   & 0xff; /* MSB */
	st->buf[9] =  dsuScaler         & 0xff; /* LSB */

	ret = dib0700_ctrl_wr(d, st->buf, 10);
	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण

पूर्णांक dib0700_set_i2c_speed(काष्ठा dvb_usb_device *d, u16 scl_kHz)
अणु
	काष्ठा dib0700_state *st = d->priv;
	u16 भागider;
	पूर्णांक ret;

	अगर (scl_kHz == 0)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex) < 0) अणु
		err("could not acquire lock");
		वापस -EINTR;
	पूर्ण

	st->buf[0] = REQUEST_SET_I2C_PARAM;
	भागider = (u16) (30000 / scl_kHz);
	st->buf[1] = 0;
	st->buf[2] = (u8) (भागider >> 8);
	st->buf[3] = (u8) (भागider & 0xff);
	भागider = (u16) (72000 / scl_kHz);
	st->buf[4] = (u8) (भागider >> 8);
	st->buf[5] = (u8) (भागider & 0xff);
	भागider = (u16) (72000 / scl_kHz); /* घड़ी: 72MHz */
	st->buf[6] = (u8) (भागider >> 8);
	st->buf[7] = (u8) (भागider & 0xff);

	deb_info("setting I2C speed: %04x %04x %04x (%d kHz).",
		(st->buf[2] << 8) | (st->buf[3]), (st->buf[4] << 8) |
		st->buf[5], (st->buf[6] << 8) | st->buf[7], scl_kHz);

	ret = dib0700_ctrl_wr(d, st->buf, 8);
	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण


पूर्णांक dib0700_ctrl_घड़ी(काष्ठा dvb_usb_device *d, u32 clk_MHz, u8 घड़ी_out_gp3)
अणु
	चयन (clk_MHz) अणु
		हाल 72: dib0700_set_घड़ी(d, 1, 0, 1, घड़ी_out_gp3, 2, 24, 0, 0x4c); अवरोध;
		शेष: वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib0700_jumpram(काष्ठा usb_device *udev, u32 address)
अणु
	पूर्णांक ret = 0, actlen;
	u8 *buf;

	buf = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	buf[0] = REQUEST_JUMPRAM;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = 0;
	buf[4] = (address >> 24) & 0xff;
	buf[5] = (address >> 16) & 0xff;
	buf[6] = (address >> 8)  & 0xff;
	buf[7] =  address        & 0xff;

	अगर ((ret = usb_bulk_msg(udev, usb_sndbulkpipe(udev, 0x01),buf,8,&actlen,1000)) < 0) अणु
		deb_fw("jumpram to 0x%x failed\n",address);
		जाओ out;
	पूर्ण
	अगर (actlen != 8) अणु
		deb_fw("jumpram to 0x%x failed\n",address);
		ret = -EIO;
		जाओ out;
	पूर्ण
out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

पूर्णांक dib0700_करोwnload_firmware(काष्ठा usb_device *udev, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा hexline hx;
	पूर्णांक pos = 0, ret, act_len, i, adap_num;
	u8 *buf;
	u32 fw_version;

	buf = kदो_स्मृति(260, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक ((ret = dvb_usb_get_hexline(fw, &hx, &pos)) > 0) अणु
		deb_fwdata("writing to address 0x%08x (buffer: 0x%02x %02x)\n",
				hx.addr, hx.len, hx.chk);

		buf[0] = hx.len;
		buf[1] = (hx.addr >> 8) & 0xff;
		buf[2] =  hx.addr       & 0xff;
		buf[3] = hx.type;
		स_नकल(&buf[4],hx.data,hx.len);
		buf[4+hx.len] = hx.chk;

		ret = usb_bulk_msg(udev,
			usb_sndbulkpipe(udev, 0x01),
			buf,
			hx.len + 5,
			&act_len,
			1000);

		अगर (ret < 0) अणु
			err("firmware download failed at %d with %d",pos,ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (ret == 0) अणु
		/* start the firmware */
		अगर ((ret = dib0700_jumpram(udev, 0x70000000)) == 0) अणु
			info("firmware started successfully.");
			msleep(500);
		पूर्ण
	पूर्ण अन्यथा
		ret = -EIO;

	/* the number of ts packet has to be at least 1 */
	अगर (nb_packet_buffer_size < 1)
		nb_packet_buffer_size = 1;

	/* get the firmware version */
	usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				  REQUEST_GET_VERSION,
				  USB_TYPE_VENDOR | USB_सूची_IN, 0, 0,
				  buf, 16, USB_CTRL_GET_TIMEOUT);
	fw_version = (buf[8] << 24) | (buf[9] << 16) | (buf[10] << 8) | buf[11];

	/* set the buffer size - DVB-USB is allocating URB buffers
	 * only after the firwmare करोwnload was successful */
	क्रम (i = 0; i < dib0700_device_count; i++) अणु
		क्रम (adap_num = 0; adap_num < dib0700_devices[i].num_adapters;
				adap_num++) अणु
			अगर (fw_version >= 0x10201) अणु
				dib0700_devices[i].adapter[adap_num].fe[0].stream.u.bulk.buffersize = 188*nb_packet_buffer_size;
			पूर्ण अन्यथा अणु
				/* क्रम fw version older than 1.20.1,
				 * the buffersize has to be n बार 512 */
				dib0700_devices[i].adapter[adap_num].fe[0].stream.u.bulk.buffersize = ((188*nb_packet_buffer_size+188/2)/512)*512;
				अगर (dib0700_devices[i].adapter[adap_num].fe[0].stream.u.bulk.buffersize < 512)
					dib0700_devices[i].adapter[adap_num].fe[0].stream.u.bulk.buffersize = 512;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

पूर्णांक dib0700_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;
	पूर्णांक ret;

	अगर ((onoff != 0) && (st->fw_version >= 0x10201)) अणु
		/* क्रम firmware later than 1.20.1,
		 * the USB xfer length can be set  */
		ret = dib0700_set_usb_xfer_len(adap->dev,
			st->nb_packet_buffer_size);
		अगर (ret < 0) अणु
			deb_info("can not set the USB xfer len\n");
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_lock(&adap->dev->usb_mutex);

	st->buf[0] = REQUEST_ENABLE_VIDEO;
	/* this bit gives a kind of command,
	 * rather than enabling something or not */
	st->buf[1] = (onoff << 4) | 0x00;

	अगर (st->disable_streaming_master_mode == 1)
		st->buf[2] = 0x00;
	अन्यथा
		st->buf[2] = 0x01 << 4; /* Master mode */

	st->buf[3] = 0x00;

	deb_info("modifying (%d) streaming state for %d\n", onoff, adap->id);

	st->channel_state &= ~0x3;
	अगर ((adap->fe_adap[0].stream.props.endpoपूर्णांक != 2)
			&& (adap->fe_adap[0].stream.props.endpoपूर्णांक != 3)) अणु
		deb_info("the endpoint number (%i) is not correct, use the adapter id instead", adap->fe_adap[0].stream.props.endpoपूर्णांक);
		अगर (onoff)
			st->channel_state |=	1 << (adap->id);
		अन्यथा
			st->channel_state |=	1 << ~(adap->id);
	पूर्ण अन्यथा अणु
		अगर (onoff)
			st->channel_state |=	1 << (adap->fe_adap[0].stream.props.endpoपूर्णांक-2);
		अन्यथा
			st->channel_state |=	1 << (3-adap->fe_adap[0].stream.props.endpoपूर्णांक);
	पूर्ण

	st->buf[2] |= st->channel_state;

	deb_info("data for streaming: %x %x\n", st->buf[1], st->buf[2]);

	ret = dib0700_ctrl_wr(adap->dev, st->buf, 4);
	mutex_unlock(&adap->dev->usb_mutex);

	वापस ret;
पूर्ण

पूर्णांक dib0700_change_protocol(काष्ठा rc_dev *rc, u64 *rc_proto)
अणु
	काष्ठा dvb_usb_device *d = rc->priv;
	काष्ठा dib0700_state *st = d->priv;
	पूर्णांक new_proto, ret;

	अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex) < 0) अणु
		err("could not acquire lock");
		वापस -EINTR;
	पूर्ण

	st->buf[0] = REQUEST_SET_RC;
	st->buf[1] = 0;
	st->buf[2] = 0;

	/* Set the IR mode */
	अगर (*rc_proto & RC_PROTO_BIT_RC5) अणु
		new_proto = 1;
		*rc_proto = RC_PROTO_BIT_RC5;
	पूर्ण अन्यथा अगर (*rc_proto & RC_PROTO_BIT_NEC) अणु
		new_proto = 0;
		*rc_proto = RC_PROTO_BIT_NEC;
	पूर्ण अन्यथा अगर (*rc_proto & RC_PROTO_BIT_RC6_MCE) अणु
		अगर (st->fw_version < 0x10200) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		new_proto = 2;
		*rc_proto = RC_PROTO_BIT_RC6_MCE;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	st->buf[1] = new_proto;

	ret = dib0700_ctrl_wr(d, st->buf, 3);
	अगर (ret < 0) अणु
		err("ir protocol setup failed");
		जाओ out;
	पूर्ण

	d->props.rc.core.protocol = *rc_proto;

out:
	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

/* This is the काष्ठाure of the RC response packet starting in firmware 1.20 */
काष्ठा dib0700_rc_response अणु
	u8 report_id;
	u8 data_state;
	जोड़ अणु
		काष्ठा अणु
			u8 प्रणाली;
			u8 not_प्रणाली;
			u8 data;
			u8 not_data;
		पूर्ण nec;
		काष्ठा अणु
			u8 not_used;
			u8 प्रणाली;
			u8 data;
			u8 not_data;
		पूर्ण rc5;
	पूर्ण;
पूर्ण;
#घोषणा RC_MSG_SIZE_V1_20 6

अटल व्योम dib0700_rc_urb_completion(काष्ठा urb *purb)
अणु
	काष्ठा dvb_usb_device *d = purb->context;
	काष्ठा dib0700_rc_response *poll_reply;
	क्रमागत rc_proto protocol;
	u32 keycode;
	u8 toggle;

	deb_info("%s()\n", __func__);
	अगर (d->rc_dev == शून्य) अणु
		/* This will occur अगर disable_rc_polling=1 */
		kमुक्त(purb->transfer_buffer);
		usb_मुक्त_urb(purb);
		वापस;
	पूर्ण

	poll_reply = purb->transfer_buffer;

	अगर (purb->status < 0) अणु
		deb_info("discontinuing polling\n");
		kमुक्त(purb->transfer_buffer);
		usb_मुक्त_urb(purb);
		वापस;
	पूर्ण

	अगर (purb->actual_length != RC_MSG_SIZE_V1_20) अणु
		deb_info("malformed rc msg size=%d\n", purb->actual_length);
		जाओ resubmit;
	पूर्ण

	deb_data("IR ID = %02X state = %02X System = %02X %02X Cmd = %02X %02X (len %d)\n",
		 poll_reply->report_id, poll_reply->data_state,
		 poll_reply->nec.प्रणाली, poll_reply->nec.not_प्रणाली,
		 poll_reply->nec.data, poll_reply->nec.not_data,
		 purb->actual_length);

	चयन (d->props.rc.core.protocol) अणु
	हाल RC_PROTO_BIT_NEC:
		toggle = 0;

		/* NEC protocol sends repeat code as 0 0 0 FF */
		अगर (poll_reply->nec.प्रणाली     == 0x00 &&
		    poll_reply->nec.not_प्रणाली == 0x00 &&
		    poll_reply->nec.data       == 0x00 &&
		    poll_reply->nec.not_data   == 0xff) अणु
			poll_reply->data_state = 2;
			rc_repeat(d->rc_dev);
			जाओ resubmit;
		पूर्ण

		अगर ((poll_reply->nec.data ^ poll_reply->nec.not_data) != 0xff) अणु
			deb_data("NEC32 protocol\n");
			keycode = RC_SCANCODE_NEC32(poll_reply->nec.प्रणाली     << 24 |
						     poll_reply->nec.not_प्रणाली << 16 |
						     poll_reply->nec.data       << 8  |
						     poll_reply->nec.not_data);
			protocol = RC_PROTO_NEC32;
		पूर्ण अन्यथा अगर ((poll_reply->nec.प्रणाली ^ poll_reply->nec.not_प्रणाली) != 0xff) अणु
			deb_data("NEC extended protocol\n");
			keycode = RC_SCANCODE_NECX(poll_reply->nec.प्रणाली << 8 |
						    poll_reply->nec.not_प्रणाली,
						    poll_reply->nec.data);

			protocol = RC_PROTO_NECX;
		पूर्ण अन्यथा अणु
			deb_data("NEC normal protocol\n");
			keycode = RC_SCANCODE_NEC(poll_reply->nec.प्रणाली,
						   poll_reply->nec.data);
			protocol = RC_PROTO_NEC;
		पूर्ण

		अवरोध;
	शेष:
		deb_data("RC5 protocol\n");
		protocol = RC_PROTO_RC5;
		toggle = poll_reply->report_id;
		keycode = RC_SCANCODE_RC5(poll_reply->rc5.प्रणाली, poll_reply->rc5.data);

		अगर ((poll_reply->rc5.data ^ poll_reply->rc5.not_data) != 0xff) अणु
			/* Key failed पूर्णांकegrity check */
			err("key failed integrity check: %02x %02x %02x %02x",
			    poll_reply->rc5.not_used, poll_reply->rc5.प्रणाली,
			    poll_reply->rc5.data, poll_reply->rc5.not_data);
			जाओ resubmit;
		पूर्ण

		अवरोध;
	पूर्ण

	rc_keyकरोwn(d->rc_dev, protocol, keycode, toggle);

resubmit:
	/* Clean the buffer beक्रमe we requeue */
	स_रखो(purb->transfer_buffer, 0, RC_MSG_SIZE_V1_20);

	/* Requeue URB */
	usb_submit_urb(purb, GFP_ATOMIC);
पूर्ण

पूर्णांक dib0700_rc_setup(काष्ठा dvb_usb_device *d, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dib0700_state *st = d->priv;
	काष्ठा urb *purb;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *e;
	पूर्णांक ret, rc_ep = 1;
	अचिन्हित पूर्णांक pipe = 0;

	/* Poll-based. Don't initialize bulk mode */
	अगर (st->fw_version < 0x10200 || !पूर्णांकf)
		वापस 0;

	/* Starting in firmware 1.20, the RC info is provided on a bulk pipe */

	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < rc_ep + 1)
		वापस -ENODEV;

	purb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (purb == शून्य)
		वापस -ENOMEM;

	purb->transfer_buffer = kzalloc(RC_MSG_SIZE_V1_20, GFP_KERNEL);
	अगर (purb->transfer_buffer == शून्य) अणु
		err("rc kzalloc failed");
		usb_मुक्त_urb(purb);
		वापस -ENOMEM;
	पूर्ण

	purb->status = -EINPROGRESS;

	/*
	 * Some devices like the Hauppauge NovaTD model 52009 use an पूर्णांकerrupt
	 * endpoपूर्णांक, जबतक others use a bulk one.
	 */
	e = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[rc_ep].desc;
	अगर (usb_endpoपूर्णांक_dir_in(e)) अणु
		अगर (usb_endpoपूर्णांक_xfer_bulk(e)) अणु
			pipe = usb_rcvbulkpipe(d->udev, rc_ep);
			usb_fill_bulk_urb(purb, d->udev, pipe,
					  purb->transfer_buffer,
					  RC_MSG_SIZE_V1_20,
					  dib0700_rc_urb_completion, d);

		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(e)) अणु
			pipe = usb_rcvपूर्णांकpipe(d->udev, rc_ep);
			usb_fill_पूर्णांक_urb(purb, d->udev, pipe,
					  purb->transfer_buffer,
					  RC_MSG_SIZE_V1_20,
					  dib0700_rc_urb_completion, d, 1);
		पूर्ण
	पूर्ण

	अगर (!pipe) अणु
		err("There's no endpoint for remote controller");
		kमुक्त(purb->transfer_buffer);
		usb_मुक्त_urb(purb);
		वापस 0;
	पूर्ण

	ret = usb_submit_urb(purb, GFP_ATOMIC);
	अगर (ret) अणु
		err("rc submit urb failed");
		kमुक्त(purb->transfer_buffer);
		usb_मुक्त_urb(purb);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dib0700_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक i;
	काष्ठा dvb_usb_device *dev;

	क्रम (i = 0; i < dib0700_device_count; i++)
		अगर (dvb_usb_device_init(पूर्णांकf, &dib0700_devices[i], THIS_MODULE,
		    &dev, adapter_nr) == 0) अणु
			काष्ठा dib0700_state *st = dev->priv;
			u32 hwversion, romversion, fw_version, fwtype;

			dib0700_get_version(dev, &hwversion, &romversion,
				&fw_version, &fwtype);

			deb_info("Firmware version: %x, %d, 0x%x, %d\n",
				hwversion, romversion, fw_version, fwtype);

			st->fw_version = fw_version;
			st->nb_packet_buffer_size = (u32)nb_packet_buffer_size;

			/* Disable polling mode on newer firmwares */
			अगर (st->fw_version >= 0x10200)
				dev->props.rc.core.bulk_mode = true;
			अन्यथा
				dev->props.rc.core.bulk_mode = false;

			dib0700_rc_setup(dev, पूर्णांकf);

			वापस 0;
		पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम dib0700_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा dib0700_state *st = d->priv;
	काष्ठा i2c_client *client;

	/* हटाओ I2C client क्रम tuner */
	client = st->i2c_client_tuner;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	/* हटाओ I2C client क्रम demodulator */
	client = st->i2c_client_demod;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	dvb_usb_device_निकास(पूर्णांकf);
पूर्ण


अटल काष्ठा usb_driver dib0700_driver = अणु
	.name       = "dvb_usb_dib0700",
	.probe      = dib0700_probe,
	.disconnect = dib0700_disconnect,
	.id_table   = dib0700_usb_id_table,
पूर्ण;

module_usb_driver(dib0700_driver);

MODULE_FIRMWARE("dvb-usb-dib0700-1.20.fw");
MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for devices based on DiBcom DiB0700 - USB bridge");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
