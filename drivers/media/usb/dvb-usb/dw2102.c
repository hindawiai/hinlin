<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB framework compliant Linux driver क्रम the
 *	DVBWorld DVB-S 2101, 2102, DVB-S2 2104, DVB-C 3101,
 *	TeVii S421, S480, S482, S600, S630, S632, S650, S660, S662,
 *	Prof 1100, 7500,
 *	Geniatech SU3000, T220,
 *	TechnoTrend S2-4600,
 *	Terratec Cinergy S2 cards
 * Copyright (C) 2008-2012 Igor M. Liplianin (liplianin@me.by)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश <media/dvb-usb-ids.h>
#समावेश "dw2102.h"
#समावेश "si21xx.h"
#समावेश "stv0299.h"
#समावेश "z0194a.h"
#समावेश "stv0288.h"
#समावेश "stb6000.h"
#समावेश "eds1547.h"
#समावेश "cx24116.h"
#समावेश "tda1002x.h"
#समावेश "mt312.h"
#समावेश "zl10039.h"
#समावेश "ts2020.h"
#समावेश "ds3000.h"
#समावेश "stv0900.h"
#समावेश "stv6110.h"
#समावेश "stb6100.h"
#समावेश "stb6100_proc.h"
#समावेश "m88rs2000.h"
#समावेश "tda18271.h"
#समावेश "cxd2820r.h"
#समावेश "m88ds3103.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64


#घोषणा DW210X_READ_MSG 0
#घोषणा DW210X_WRITE_MSG 1

#घोषणा REG_1F_SYMBOLRATE_BYTE0 0x1f
#घोषणा REG_20_SYMBOLRATE_BYTE1 0x20
#घोषणा REG_21_SYMBOLRATE_BYTE2 0x21
/* on my own*/
#घोषणा DW2102_VOLTAGE_CTRL (0x1800)
#घोषणा SU3000_STREAM_CTRL (0x1900)
#घोषणा DW2102_RC_QUERY (0x1a00)
#घोषणा DW2102_LED_CTRL (0x1b00)

#घोषणा DW2101_FIRMWARE "dvb-usb-dw2101.fw"
#घोषणा DW2102_FIRMWARE "dvb-usb-dw2102.fw"
#घोषणा DW2104_FIRMWARE "dvb-usb-dw2104.fw"
#घोषणा DW3101_FIRMWARE "dvb-usb-dw3101.fw"
#घोषणा S630_FIRMWARE   "dvb-usb-s630.fw"
#घोषणा S660_FIRMWARE   "dvb-usb-s660.fw"
#घोषणा P1100_FIRMWARE  "dvb-usb-p1100.fw"
#घोषणा P7500_FIRMWARE  "dvb-usb-p7500.fw"

#घोषणा	err_str "did not find the firmware file '%s'. You can use <kernel_dir>/scripts/get_dvb_firmware to get the firmware"

काष्ठा dw2102_state अणु
	u8 initialized;
	u8 last_lock;
	u8 data[MAX_XFER_SIZE + 4];
	काष्ठा i2c_client *i2c_client_demod;
	काष्ठा i2c_client *i2c_client_tuner;

	/* fe hook functions*/
	पूर्णांक (*old_set_voltage)(काष्ठा dvb_frontend *f, क्रमागत fe_sec_voltage v);
	पूर्णांक (*fe_पढ़ो_status)(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_status *status);
पूर्ण;

/* debug */
अटल पूर्णांक dvb_usb_dw2102_debug;
module_param_named(debug, dvb_usb_dw2102_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info 2=xfer 4=rc(or-able))."
						DVB_USB_DEBUG_STATUS);

/* demod probe */
अटल पूर्णांक demod_probe = 1;
module_param_named(demod, demod_probe, पूर्णांक, 0644);
MODULE_PARM_DESC(demod, "demod to probe (1=cx24116 2=stv0903+stv6110 4=stv0903+stb6100(or-able)).");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक dw210x_op_rw(काष्ठा usb_device *dev, u8 request, u16 value,
			u16 index, u8 * data, u16 len, पूर्णांक flags)
अणु
	पूर्णांक ret;
	u8 *u8buf;
	अचिन्हित पूर्णांक pipe = (flags == DW210X_READ_MSG) ?
				usb_rcvctrlpipe(dev, 0) : usb_sndctrlpipe(dev, 0);
	u8 request_type = (flags == DW210X_READ_MSG) ? USB_सूची_IN : USB_सूची_OUT;

	u8buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!u8buf)
		वापस -ENOMEM;


	अगर (flags == DW210X_WRITE_MSG)
		स_नकल(u8buf, data, len);
	ret = usb_control_msg(dev, pipe, request, request_type | USB_TYPE_VENDOR,
				value, index , u8buf, len, 2000);

	अगर (flags == DW210X_READ_MSG)
		स_नकल(data, u8buf, len);

	kमुक्त(u8buf);
	वापस ret;
पूर्ण

/* I2C */
अटल पूर्णांक dw2102_i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
		पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक i = 0;
	u8 buf6[] = अणु0x2c, 0x05, 0xc0, 0, 0, 0, 0पूर्ण;
	u16 value;

	अगर (!d)
		वापस -ENODEV;
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	चयन (num) अणु
	हाल 2:
		/* पढ़ो stv0299 रेजिस्टर */
		value = msg[0].buf[0];/* रेजिस्टर */
		क्रम (i = 0; i < msg[1].len; i++) अणु
			dw210x_op_rw(d->udev, 0xb5, value + i, 0,
					buf6, 2, DW210X_READ_MSG);
			msg[1].buf[i] = buf6[0];
		पूर्ण
		अवरोध;
	हाल 1:
		चयन (msg[0].addr) अणु
		हाल 0x68:
			/* ग_लिखो to stv0299 रेजिस्टर */
			buf6[0] = 0x2a;
			buf6[1] = msg[0].buf[0];
			buf6[2] = msg[0].buf[1];
			dw210x_op_rw(d->udev, 0xb2, 0, 0,
					buf6, 3, DW210X_WRITE_MSG);
			अवरोध;
		हाल 0x60:
			अगर (msg[0].flags == 0) अणु
			/* ग_लिखो to tuner pll */
				buf6[0] = 0x2c;
				buf6[1] = 5;
				buf6[2] = 0xc0;
				buf6[3] = msg[0].buf[0];
				buf6[4] = msg[0].buf[1];
				buf6[5] = msg[0].buf[2];
				buf6[6] = msg[0].buf[3];
				dw210x_op_rw(d->udev, 0xb2, 0, 0,
						buf6, 7, DW210X_WRITE_MSG);
			पूर्ण अन्यथा अणु
			/* पढ़ो from tuner */
				dw210x_op_rw(d->udev, 0xb5, 0, 0,
						buf6, 1, DW210X_READ_MSG);
				msg[0].buf[0] = buf6[0];
			पूर्ण
			अवरोध;
		हाल (DW2102_RC_QUERY):
			dw210x_op_rw(d->udev, 0xb8, 0, 0,
					buf6, 2, DW210X_READ_MSG);
			msg[0].buf[0] = buf6[0];
			msg[0].buf[1] = buf6[1];
			अवरोध;
		हाल (DW2102_VOLTAGE_CTRL):
			buf6[0] = 0x30;
			buf6[1] = msg[0].buf[0];
			dw210x_op_rw(d->udev, 0xb2, 0, 0,
					buf6, 2, DW210X_WRITE_MSG);
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस num;
पूर्ण

अटल पूर्णांक dw2102_serit_i2c_transfer(काष्ठा i2c_adapter *adap,
						काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	u8 buf6[] = अणु0, 0, 0, 0, 0, 0, 0पूर्ण;

	अगर (!d)
		वापस -ENODEV;
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	चयन (num) अणु
	हाल 2:
		अगर (msg[0].len != 1) अणु
			warn("i2c rd: len=%d is not 1!\n",
			     msg[0].len);
			num = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		अगर (2 + msg[1].len > माप(buf6)) अणु
			warn("i2c rd: len=%d is too big!\n",
			     msg[1].len);
			num = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		/* पढ़ो si2109 रेजिस्टर by number */
		buf6[0] = msg[0].addr << 1;
		buf6[1] = msg[0].len;
		buf6[2] = msg[0].buf[0];
		dw210x_op_rw(d->udev, 0xc2, 0, 0,
				buf6, msg[0].len + 2, DW210X_WRITE_MSG);
		/* पढ़ो si2109 रेजिस्टर */
		dw210x_op_rw(d->udev, 0xc3, 0xd0, 0,
				buf6, msg[1].len + 2, DW210X_READ_MSG);
		स_नकल(msg[1].buf, buf6 + 2, msg[1].len);

		अवरोध;
	हाल 1:
		चयन (msg[0].addr) अणु
		हाल 0x68:
			अगर (2 + msg[0].len > माप(buf6)) अणु
				warn("i2c wr: len=%d is too big!\n",
				     msg[0].len);
				num = -EOPNOTSUPP;
				अवरोध;
			पूर्ण

			/* ग_लिखो to si2109 रेजिस्टर */
			buf6[0] = msg[0].addr << 1;
			buf6[1] = msg[0].len;
			स_नकल(buf6 + 2, msg[0].buf, msg[0].len);
			dw210x_op_rw(d->udev, 0xc2, 0, 0, buf6,
					msg[0].len + 2, DW210X_WRITE_MSG);
			अवरोध;
		हाल(DW2102_RC_QUERY):
			dw210x_op_rw(d->udev, 0xb8, 0, 0,
					buf6, 2, DW210X_READ_MSG);
			msg[0].buf[0] = buf6[0];
			msg[0].buf[1] = buf6[1];
			अवरोध;
		हाल(DW2102_VOLTAGE_CTRL):
			buf6[0] = 0x30;
			buf6[1] = msg[0].buf[0];
			dw210x_op_rw(d->udev, 0xb2, 0, 0,
					buf6, 2, DW210X_WRITE_MSG);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस num;
पूर्ण

अटल पूर्णांक dw2102_earda_i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक ret;

	अगर (!d)
		वापस -ENODEV;
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	चयन (num) अणु
	हाल 2: अणु
		/* पढ़ो */
		/* first ग_लिखो first रेजिस्टर number */
		u8 ibuf[MAX_XFER_SIZE], obuf[3];

		अगर (2 + msg[0].len != माप(obuf)) अणु
			warn("i2c rd: len=%d is not 1!\n",
			     msg[0].len);
			ret = -EOPNOTSUPP;
			जाओ unlock;
		पूर्ण

		अगर (2 + msg[1].len > माप(ibuf)) अणु
			warn("i2c rd: len=%d is too big!\n",
			     msg[1].len);
			ret = -EOPNOTSUPP;
			जाओ unlock;
		पूर्ण

		obuf[0] = msg[0].addr << 1;
		obuf[1] = msg[0].len;
		obuf[2] = msg[0].buf[0];
		dw210x_op_rw(d->udev, 0xc2, 0, 0,
				obuf, msg[0].len + 2, DW210X_WRITE_MSG);
		/* second पढ़ो रेजिस्टरs */
		dw210x_op_rw(d->udev, 0xc3, 0xd1 , 0,
				ibuf, msg[1].len + 2, DW210X_READ_MSG);
		स_नकल(msg[1].buf, ibuf + 2, msg[1].len);

		अवरोध;
	पूर्ण
	हाल 1:
		चयन (msg[0].addr) अणु
		हाल 0x68: अणु
			/* ग_लिखो to रेजिस्टर */
			u8 obuf[MAX_XFER_SIZE];

			अगर (2 + msg[0].len > माप(obuf)) अणु
				warn("i2c wr: len=%d is too big!\n",
				     msg[1].len);
				ret = -EOPNOTSUPP;
				जाओ unlock;
			पूर्ण

			obuf[0] = msg[0].addr << 1;
			obuf[1] = msg[0].len;
			स_नकल(obuf + 2, msg[0].buf, msg[0].len);
			dw210x_op_rw(d->udev, 0xc2, 0, 0,
					obuf, msg[0].len + 2, DW210X_WRITE_MSG);
			अवरोध;
		पूर्ण
		हाल 0x61: अणु
			/* ग_लिखो to tuner */
			u8 obuf[MAX_XFER_SIZE];

			अगर (2 + msg[0].len > माप(obuf)) अणु
				warn("i2c wr: len=%d is too big!\n",
				     msg[1].len);
				ret = -EOPNOTSUPP;
				जाओ unlock;
			पूर्ण

			obuf[0] = msg[0].addr << 1;
			obuf[1] = msg[0].len;
			स_नकल(obuf + 2, msg[0].buf, msg[0].len);
			dw210x_op_rw(d->udev, 0xc2, 0, 0,
					obuf, msg[0].len + 2, DW210X_WRITE_MSG);
			अवरोध;
		पूर्ण
		हाल(DW2102_RC_QUERY): अणु
			u8 ibuf[2];
			dw210x_op_rw(d->udev, 0xb8, 0, 0,
					ibuf, 2, DW210X_READ_MSG);
			स_नकल(msg[0].buf, ibuf , 2);
			अवरोध;
		पूर्ण
		हाल(DW2102_VOLTAGE_CTRL): अणु
			u8 obuf[2];
			obuf[0] = 0x30;
			obuf[1] = msg[0].buf[0];
			dw210x_op_rw(d->udev, 0xb2, 0, 0,
					obuf, 2, DW210X_WRITE_MSG);
			अवरोध;
		पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण
	ret = num;

unlock:
	mutex_unlock(&d->i2c_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dw2104_i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक len, i, j, ret;

	अगर (!d)
		वापस -ENODEV;
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (j = 0; j < num; j++) अणु
		चयन (msg[j].addr) अणु
		हाल(DW2102_RC_QUERY): अणु
			u8 ibuf[2];
			dw210x_op_rw(d->udev, 0xb8, 0, 0,
					ibuf, 2, DW210X_READ_MSG);
			स_नकल(msg[j].buf, ibuf , 2);
			अवरोध;
		पूर्ण
		हाल(DW2102_VOLTAGE_CTRL): अणु
			u8 obuf[2];
			obuf[0] = 0x30;
			obuf[1] = msg[j].buf[0];
			dw210x_op_rw(d->udev, 0xb2, 0, 0,
					obuf, 2, DW210X_WRITE_MSG);
			अवरोध;
		पूर्ण
		/*हाल 0x55: cx24116
		हाल 0x6a: stv0903
		हाल 0x68: ds3000, stv0903
		हाल 0x60: ts2020, stv6110, stb6100 */
		शेष: अणु
			अगर (msg[j].flags == I2C_M_RD) अणु
				/* पढ़ो रेजिस्टरs */
				u8  ibuf[MAX_XFER_SIZE];

				अगर (2 + msg[j].len > माप(ibuf)) अणु
					warn("i2c rd: len=%d is too big!\n",
					     msg[j].len);
					ret = -EOPNOTSUPP;
					जाओ unlock;
				पूर्ण

				dw210x_op_rw(d->udev, 0xc3,
						(msg[j].addr << 1) + 1, 0,
						ibuf, msg[j].len + 2,
						DW210X_READ_MSG);
				स_नकल(msg[j].buf, ibuf + 2, msg[j].len);
				mdelay(10);
			पूर्ण अन्यथा अगर (((msg[j].buf[0] == 0xb0) &&
						(msg[j].addr == 0x68)) ||
						((msg[j].buf[0] == 0xf7) &&
						(msg[j].addr == 0x55))) अणु
				/* ग_लिखो firmware */
				u8 obuf[19];
				obuf[0] = msg[j].addr << 1;
				obuf[1] = (msg[j].len > 15 ? 17 : msg[j].len);
				obuf[2] = msg[j].buf[0];
				len = msg[j].len - 1;
				i = 1;
				करो अणु
					स_नकल(obuf + 3, msg[j].buf + i,
							(len > 16 ? 16 : len));
					dw210x_op_rw(d->udev, 0xc2, 0, 0,
						obuf, (len > 16 ? 16 : len) + 3,
						DW210X_WRITE_MSG);
					i += 16;
					len -= 16;
				पूर्ण जबतक (len > 0);
			पूर्ण अन्यथा अणु
				/* ग_लिखो रेजिस्टरs */
				u8 obuf[MAX_XFER_SIZE];

				अगर (2 + msg[j].len > माप(obuf)) अणु
					warn("i2c wr: len=%d is too big!\n",
					     msg[j].len);
					ret = -EOPNOTSUPP;
					जाओ unlock;
				पूर्ण

				obuf[0] = msg[j].addr << 1;
				obuf[1] = msg[j].len;
				स_नकल(obuf + 2, msg[j].buf, msg[j].len);
				dw210x_op_rw(d->udev, 0xc2, 0, 0,
						obuf, msg[j].len + 2,
						DW210X_WRITE_MSG);
			पूर्ण
			अवरोध;
		पूर्ण
		पूर्ण

	पूर्ण
	ret = num;

unlock:
	mutex_unlock(&d->i2c_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dw3101_i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
								पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!d)
		वापस -ENODEV;
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	चयन (num) अणु
	हाल 2: अणु
		/* पढ़ो */
		/* first ग_लिखो first रेजिस्टर number */
		u8 ibuf[MAX_XFER_SIZE], obuf[3];

		अगर (2 + msg[0].len != माप(obuf)) अणु
			warn("i2c rd: len=%d is not 1!\n",
			     msg[0].len);
			ret = -EOPNOTSUPP;
			जाओ unlock;
		पूर्ण
		अगर (2 + msg[1].len > माप(ibuf)) अणु
			warn("i2c rd: len=%d is too big!\n",
			     msg[1].len);
			ret = -EOPNOTSUPP;
			जाओ unlock;
		पूर्ण
		obuf[0] = msg[0].addr << 1;
		obuf[1] = msg[0].len;
		obuf[2] = msg[0].buf[0];
		dw210x_op_rw(d->udev, 0xc2, 0, 0,
				obuf, msg[0].len + 2, DW210X_WRITE_MSG);
		/* second पढ़ो रेजिस्टरs */
		dw210x_op_rw(d->udev, 0xc3, 0x19 , 0,
				ibuf, msg[1].len + 2, DW210X_READ_MSG);
		स_नकल(msg[1].buf, ibuf + 2, msg[1].len);

		अवरोध;
	पूर्ण
	हाल 1:
		चयन (msg[0].addr) अणु
		हाल 0x60:
		हाल 0x0c: अणु
			/* ग_लिखो to रेजिस्टर */
			u8 obuf[MAX_XFER_SIZE];

			अगर (2 + msg[0].len > माप(obuf)) अणु
				warn("i2c wr: len=%d is too big!\n",
				     msg[0].len);
				ret = -EOPNOTSUPP;
				जाओ unlock;
			पूर्ण
			obuf[0] = msg[0].addr << 1;
			obuf[1] = msg[0].len;
			स_नकल(obuf + 2, msg[0].buf, msg[0].len);
			dw210x_op_rw(d->udev, 0xc2, 0, 0,
					obuf, msg[0].len + 2, DW210X_WRITE_MSG);
			अवरोध;
		पूर्ण
		हाल(DW2102_RC_QUERY): अणु
			u8 ibuf[2];
			dw210x_op_rw(d->udev, 0xb8, 0, 0,
					ibuf, 2, DW210X_READ_MSG);
			स_नकल(msg[0].buf, ibuf , 2);
			अवरोध;
		पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		deb_xfer("%02x:%02x: %s ", i, msg[i].addr,
				msg[i].flags == 0 ? ">>>" : "<<<");
		debug_dump(msg[i].buf, msg[i].len, deb_xfer);
	पूर्ण
	ret = num;

unlock:
	mutex_unlock(&d->i2c_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक s6x0_i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
								पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा usb_device *udev;
	पूर्णांक len, i, j, ret;

	अगर (!d)
		वापस -ENODEV;
	udev = d->udev;
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (j = 0; j < num; j++) अणु
		चयन (msg[j].addr) अणु
		हाल (DW2102_RC_QUERY): अणु
			u8 ibuf[5];
			dw210x_op_rw(d->udev, 0xb8, 0, 0,
					ibuf, 5, DW210X_READ_MSG);
			स_नकल(msg[j].buf, ibuf + 3, 2);
			अवरोध;
		पूर्ण
		हाल (DW2102_VOLTAGE_CTRL): अणु
			u8 obuf[2];

			obuf[0] = 1;
			obuf[1] = msg[j].buf[1];/* off-on */
			dw210x_op_rw(d->udev, 0x8a, 0, 0,
					obuf, 2, DW210X_WRITE_MSG);
			obuf[0] = 3;
			obuf[1] = msg[j].buf[0];/* 13v-18v */
			dw210x_op_rw(d->udev, 0x8a, 0, 0,
					obuf, 2, DW210X_WRITE_MSG);
			अवरोध;
		पूर्ण
		हाल (DW2102_LED_CTRL): अणु
			u8 obuf[2];

			obuf[0] = 5;
			obuf[1] = msg[j].buf[0];
			dw210x_op_rw(d->udev, 0x8a, 0, 0,
					obuf, 2, DW210X_WRITE_MSG);
			अवरोध;
		पूर्ण
		/*हाल 0x55: cx24116
		हाल 0x6a: stv0903
		हाल 0x68: ds3000, stv0903, rs2000
		हाल 0x60: ts2020, stv6110, stb6100
		हाल 0xa0: eeprom */
		शेष: अणु
			अगर (msg[j].flags == I2C_M_RD) अणु
				/* पढ़ो रेजिस्टरs */
				u8 ibuf[MAX_XFER_SIZE];

				अगर (msg[j].len > माप(ibuf)) अणु
					warn("i2c rd: len=%d is too big!\n",
					     msg[j].len);
					ret = -EOPNOTSUPP;
					जाओ unlock;
				पूर्ण

				dw210x_op_rw(d->udev, 0x91, 0, 0,
						ibuf, msg[j].len,
						DW210X_READ_MSG);
				स_नकल(msg[j].buf, ibuf, msg[j].len);
				अवरोध;
			पूर्ण अन्यथा अगर ((msg[j].buf[0] == 0xb0) &&
						(msg[j].addr == 0x68)) अणु
				/* ग_लिखो firmware */
				u8 obuf[19];
				obuf[0] = (msg[j].len > 16 ?
						18 : msg[j].len + 1);
				obuf[1] = msg[j].addr << 1;
				obuf[2] = msg[j].buf[0];
				len = msg[j].len - 1;
				i = 1;
				करो अणु
					स_नकल(obuf + 3, msg[j].buf + i,
							(len > 16 ? 16 : len));
					dw210x_op_rw(d->udev, 0x80, 0, 0,
						obuf, (len > 16 ? 16 : len) + 3,
						DW210X_WRITE_MSG);
					i += 16;
					len -= 16;
				पूर्ण जबतक (len > 0);
			पूर्ण अन्यथा अगर (j < (num - 1)) अणु
				/* ग_लिखो रेजिस्टर addr beक्रमe पढ़ो */
				u8 obuf[MAX_XFER_SIZE];

				अगर (2 + msg[j].len > माप(obuf)) अणु
					warn("i2c wr: len=%d is too big!\n",
					     msg[j].len);
					ret = -EOPNOTSUPP;
					जाओ unlock;
				पूर्ण

				obuf[0] = msg[j + 1].len;
				obuf[1] = (msg[j].addr << 1);
				स_नकल(obuf + 2, msg[j].buf, msg[j].len);
				dw210x_op_rw(d->udev,
						le16_to_cpu(udev->descriptor.idProduct) ==
						0x7500 ? 0x92 : 0x90, 0, 0,
						obuf, msg[j].len + 2,
						DW210X_WRITE_MSG);
				अवरोध;
			पूर्ण अन्यथा अणु
				/* ग_लिखो रेजिस्टरs */
				u8 obuf[MAX_XFER_SIZE];

				अगर (2 + msg[j].len > माप(obuf)) अणु
					warn("i2c wr: len=%d is too big!\n",
					     msg[j].len);
					ret = -EOPNOTSUPP;
					जाओ unlock;
				पूर्ण
				obuf[0] = msg[j].len + 1;
				obuf[1] = (msg[j].addr << 1);
				स_नकल(obuf + 2, msg[j].buf, msg[j].len);
				dw210x_op_rw(d->udev, 0x80, 0, 0,
						obuf, msg[j].len + 2,
						DW210X_WRITE_MSG);
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		पूर्ण
	पूर्ण
	ret = num;

unlock:
	mutex_unlock(&d->i2c_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक su3000_i2c_transfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
								पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा dw2102_state *state;

	अगर (!d)
		वापस -ENODEV;

	state = d->priv;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;
	अगर (mutex_lock_पूर्णांकerruptible(&d->data_mutex) < 0) अणु
		mutex_unlock(&d->i2c_mutex);
		वापस -EAGAIN;
	पूर्ण

	चयन (num) अणु
	हाल 1:
		चयन (msg[0].addr) अणु
		हाल SU3000_STREAM_CTRL:
			state->data[0] = msg[0].buf[0] + 0x36;
			state->data[1] = 3;
			state->data[2] = 0;
			अगर (dvb_usb_generic_rw(d, state->data, 3,
					state->data, 0, 0) < 0)
				err("i2c transfer failed.");
			अवरोध;
		हाल DW2102_RC_QUERY:
			state->data[0] = 0x10;
			अगर (dvb_usb_generic_rw(d, state->data, 1,
					state->data, 2, 0) < 0)
				err("i2c transfer failed.");
			msg[0].buf[1] = state->data[0];
			msg[0].buf[0] = state->data[1];
			अवरोध;
		शेष:
			अगर (3 + msg[0].len > माप(state->data)) अणु
				warn("i2c wr: len=%d is too big!\n",
				     msg[0].len);
				num = -EOPNOTSUPP;
				अवरोध;
			पूर्ण

			/* always i2c ग_लिखो*/
			state->data[0] = 0x08;
			state->data[1] = msg[0].addr;
			state->data[2] = msg[0].len;

			स_नकल(&state->data[3], msg[0].buf, msg[0].len);

			अगर (dvb_usb_generic_rw(d, state->data, msg[0].len + 3,
						state->data, 1, 0) < 0)
				err("i2c transfer failed.");

		पूर्ण
		अवरोध;
	हाल 2:
		/* always i2c पढ़ो */
		अगर (4 + msg[0].len > माप(state->data)) अणु
			warn("i2c rd: len=%d is too big!\n",
			     msg[0].len);
			num = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		अगर (1 + msg[1].len > माप(state->data)) अणु
			warn("i2c rd: len=%d is too big!\n",
			     msg[1].len);
			num = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		state->data[0] = 0x09;
		state->data[1] = msg[0].len;
		state->data[2] = msg[1].len;
		state->data[3] = msg[0].addr;
		स_नकल(&state->data[4], msg[0].buf, msg[0].len);

		अगर (dvb_usb_generic_rw(d, state->data, msg[0].len + 4,
					state->data, msg[1].len + 1, 0) < 0)
			err("i2c transfer failed.");

		स_नकल(msg[1].buf, &state->data[1], msg[1].len);
		अवरोध;
	शेष:
		warn("more than 2 i2c messages at a time is not handled yet.");
		अवरोध;
	पूर्ण
	mutex_unlock(&d->data_mutex);
	mutex_unlock(&d->i2c_mutex);
	वापस num;
पूर्ण

अटल u32 dw210x_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm dw2102_i2c_algo = अणु
	.master_xfer = dw2102_i2c_transfer,
	.functionality = dw210x_i2c_func,
पूर्ण;

अटल काष्ठा i2c_algorithm dw2102_serit_i2c_algo = अणु
	.master_xfer = dw2102_serit_i2c_transfer,
	.functionality = dw210x_i2c_func,
पूर्ण;

अटल काष्ठा i2c_algorithm dw2102_earda_i2c_algo = अणु
	.master_xfer = dw2102_earda_i2c_transfer,
	.functionality = dw210x_i2c_func,
पूर्ण;

अटल काष्ठा i2c_algorithm dw2104_i2c_algo = अणु
	.master_xfer = dw2104_i2c_transfer,
	.functionality = dw210x_i2c_func,
पूर्ण;

अटल काष्ठा i2c_algorithm dw3101_i2c_algo = अणु
	.master_xfer = dw3101_i2c_transfer,
	.functionality = dw210x_i2c_func,
पूर्ण;

अटल काष्ठा i2c_algorithm s6x0_i2c_algo = अणु
	.master_xfer = s6x0_i2c_transfer,
	.functionality = dw210x_i2c_func,
पूर्ण;

अटल काष्ठा i2c_algorithm su3000_i2c_algo = अणु
	.master_xfer = su3000_i2c_transfer,
	.functionality = dw210x_i2c_func,
पूर्ण;

अटल पूर्णांक dw210x_पढ़ो_mac_address(काष्ठा dvb_usb_device *d, u8 mac[6])
अणु
	पूर्णांक i;
	u8 ibuf[] = अणु0, 0पूर्ण;
	u8 eeprom[256], eepromline[16];

	क्रम (i = 0; i < 256; i++) अणु
		अगर (dw210x_op_rw(d->udev, 0xb6, 0xa0 , i, ibuf, 2, DW210X_READ_MSG) < 0) अणु
			err("read eeprom failed.");
			वापस -1;
		पूर्ण अन्यथा अणु
			eepromline[i%16] = ibuf[0];
			eeprom[i] = ibuf[0];
		पूर्ण
		अगर ((i % 16) == 15) अणु
			deb_xfer("%02x: ", i - 15);
			debug_dump(eepromline, 16, deb_xfer);
		पूर्ण
	पूर्ण

	स_नकल(mac, eeprom + 8, 6);
	वापस 0;
पूर्ण;

अटल पूर्णांक s6x0_पढ़ो_mac_address(काष्ठा dvb_usb_device *d, u8 mac[6])
अणु
	पूर्णांक i, ret;
	u8 ibuf[] = अणु 0 पूर्ण, obuf[] = अणु 0 पूर्ण;
	u8 eeprom[256], eepromline[16];
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = 0xa0 >> 1,
			.flags = 0,
			.buf = obuf,
			.len = 1,
		पूर्ण, अणु
			.addr = 0xa0 >> 1,
			.flags = I2C_M_RD,
			.buf = ibuf,
			.len = 1,
		पूर्ण
	पूर्ण;

	क्रम (i = 0; i < 256; i++) अणु
		obuf[0] = i;
		ret = s6x0_i2c_transfer(&d->i2c_adap, msg, 2);
		अगर (ret != 2) अणु
			err("read eeprom failed.");
			वापस -1;
		पूर्ण अन्यथा अणु
			eepromline[i % 16] = ibuf[0];
			eeprom[i] = ibuf[0];
		पूर्ण

		अगर ((i % 16) == 15) अणु
			deb_xfer("%02x: ", i - 15);
			debug_dump(eepromline, 16, deb_xfer);
		पूर्ण
	पूर्ण

	स_नकल(mac, eeprom + 16, 6);
	वापस 0;
पूर्ण;

अटल पूर्णांक su3000_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	अटल u8 command_start[] = अणु0x00पूर्ण;
	अटल u8 command_stop[] = अणु0x01पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = SU3000_STREAM_CTRL,
		.flags = 0,
		.buf = onoff ? command_start : command_stop,
		.len = 1
	पूर्ण;

	i2c_transfer(&adap->dev->i2c_adap, &msg, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक su3000_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक i)
अणु
	काष्ठा dw2102_state *state = (काष्ठा dw2102_state *)d->priv;
	पूर्णांक ret = 0;

	info("%s: %d, initialized %d", __func__, i, state->initialized);

	अगर (i && !state->initialized) अणु
		mutex_lock(&d->data_mutex);

		state->data[0] = 0xde;
		state->data[1] = 0;

		state->initialized = 1;
		/* reset board */
		ret = dvb_usb_generic_rw(d, state->data, 2, शून्य, 0, 0);
		mutex_unlock(&d->data_mutex);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक su3000_पढ़ो_mac_address(काष्ठा dvb_usb_device *d, u8 mac[6])
अणु
	पूर्णांक i;
	u8 obuf[] = अणु 0x1f, 0xf0 पूर्ण;
	u8 ibuf[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = 0x51,
			.flags = 0,
			.buf = obuf,
			.len = 2,
		पूर्ण, अणु
			.addr = 0x51,
			.flags = I2C_M_RD,
			.buf = ibuf,
			.len = 1,

		पूर्ण
	पूर्ण;

	क्रम (i = 0; i < 6; i++) अणु
		obuf[1] = 0xf0 + i;
		अगर (i2c_transfer(&d->i2c_adap, msg, 2) != 2)
			अवरोध;
		अन्यथा
			mac[i] = ibuf[0];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक su3000_identअगरy_state(काष्ठा usb_device *udev,
				 स्थिर काष्ठा dvb_usb_device_properties *props,
				 स्थिर काष्ठा dvb_usb_device_description **desc,
				 पूर्णांक *cold)
अणु
	info("%s", __func__);

	*cold = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक dw210x_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	अटल u8 command_13v[] = अणु0x00, 0x01पूर्ण;
	अटल u8 command_18v[] = अणु0x01, 0x01पूर्ण;
	अटल u8 command_off[] = अणु0x00, 0x00पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = DW2102_VOLTAGE_CTRL,
		.flags = 0,
		.buf = command_off,
		.len = 2,
	पूर्ण;

	काष्ठा dvb_usb_adapter *udev_adap =
		(काष्ठा dvb_usb_adapter *)(fe->dvb->priv);
	अगर (voltage == SEC_VOLTAGE_18)
		msg.buf = command_18v;
	अन्यथा अगर (voltage == SEC_VOLTAGE_13)
		msg.buf = command_13v;

	i2c_transfer(&udev_adap->dev->i2c_adap, &msg, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक s660_set_voltage(काष्ठा dvb_frontend *fe,
			    क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा dvb_usb_adapter *d =
		(काष्ठा dvb_usb_adapter *)(fe->dvb->priv);
	काष्ठा dw2102_state *st = (काष्ठा dw2102_state *)d->dev->priv;

	dw210x_set_voltage(fe, voltage);
	अगर (st->old_set_voltage)
		st->old_set_voltage(fe, voltage);

	वापस 0;
पूर्ण

अटल व्योम dw210x_led_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक offon)
अणु
	अटल u8 led_off[] = अणु 0 पूर्ण;
	अटल u8 led_on[] = अणु 1 पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = DW2102_LED_CTRL,
		.flags = 0,
		.buf = led_off,
		.len = 1
	पूर्ण;
	काष्ठा dvb_usb_adapter *udev_adap =
		(काष्ठा dvb_usb_adapter *)(fe->dvb->priv);

	अगर (offon)
		msg.buf = led_on;
	i2c_transfer(&udev_adap->dev->i2c_adap, &msg, 1);
पूर्ण

अटल पूर्णांक tt_s2_4600_पढ़ो_status(काष्ठा dvb_frontend *fe,
				  क्रमागत fe_status *status)
अणु
	काष्ठा dvb_usb_adapter *d =
		(काष्ठा dvb_usb_adapter *)(fe->dvb->priv);
	काष्ठा dw2102_state *st = (काष्ठा dw2102_state *)d->dev->priv;
	पूर्णांक ret;

	ret = st->fe_पढ़ो_status(fe, status);

	/* resync slave fअगरo when संकेत change from unlock to lock */
	अगर ((*status & FE_HAS_LOCK) && (!st->last_lock))
		su3000_streaming_ctrl(d, 1);

	st->last_lock = (*status & FE_HAS_LOCK) ? 1 : 0;
	वापस ret;
पूर्ण

अटल काष्ठा stv0299_config sharp_z0194a_config = अणु
	.demod_address = 0x68,
	.inittab = sharp_z0194a_inittab,
	.mclk = 88000000UL,
	.invert = 1,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_1,
	.volt13_op0_op1 = STV0299_VOLT13_OP1,
	.min_delay_ms = 100,
	.set_symbol_rate = sharp_z0194a_set_symbol_rate,
पूर्ण;

अटल काष्ठा cx24116_config dw2104_config = अणु
	.demod_address = 0x55,
	.mpg_clk_pos_pol = 0x01,
पूर्ण;

अटल काष्ठा si21xx_config serit_sp1511lhb_config = अणु
	.demod_address = 0x68,
	.min_delay_ms = 100,

पूर्ण;

अटल काष्ठा tda10023_config dw3101_tda10023_config = अणु
	.demod_address = 0x0c,
	.invert = 1,
पूर्ण;

अटल काष्ठा mt312_config zl313_config = अणु
	.demod_address = 0x0e,
पूर्ण;

अटल काष्ठा ds3000_config dw2104_ds3000_config = अणु
	.demod_address = 0x68,
पूर्ण;

अटल काष्ठा ts2020_config dw2104_ts2020_config = अणु
	.tuner_address = 0x60,
	.clk_out_भाग = 1,
	.frequency_भाग = 1060000,
पूर्ण;

अटल काष्ठा ds3000_config s660_ds3000_config = अणु
	.demod_address = 0x68,
	.ci_mode = 1,
	.set_lock_led = dw210x_led_ctrl,
पूर्ण;

अटल काष्ठा ts2020_config s660_ts2020_config = अणु
	.tuner_address = 0x60,
	.clk_out_भाग = 1,
	.frequency_भाग = 1146000,
पूर्ण;

अटल काष्ठा stv0900_config dw2104a_stv0900_config = अणु
	.demod_address = 0x6a,
	.demod_mode = 0,
	.xtal = 27000000,
	.clkmode = 3,/* 0-CLKI, 2-XTALI, अन्यथा AUTO */
	.diseqc_mode = 2,/* 2/3 PWM */
	.tun1_maddress = 0,/* 0x60 */
	.tun1_adc = 0,/* 2 Vpp */
	.path1_mode = 3,
पूर्ण;

अटल काष्ठा stb6100_config dw2104a_stb6100_config = अणु
	.tuner_address = 0x60,
	.refघड़ी = 27000000,
पूर्ण;

अटल काष्ठा stv0900_config dw2104_stv0900_config = अणु
	.demod_address = 0x68,
	.demod_mode = 0,
	.xtal = 8000000,
	.clkmode = 3,
	.diseqc_mode = 2,
	.tun1_maddress = 0,
	.tun1_adc = 1,/* 1 Vpp */
	.path1_mode = 3,
पूर्ण;

अटल काष्ठा stv6110_config dw2104_stv6110_config = अणु
	.i2c_address = 0x60,
	.mclk = 16000000,
	.clk_भाग = 1,
पूर्ण;

अटल काष्ठा stv0900_config prof_7500_stv0900_config = अणु
	.demod_address = 0x6a,
	.demod_mode = 0,
	.xtal = 27000000,
	.clkmode = 3,/* 0-CLKI, 2-XTALI, अन्यथा AUTO */
	.diseqc_mode = 2,/* 2/3 PWM */
	.tun1_maddress = 0,/* 0x60 */
	.tun1_adc = 0,/* 2 Vpp */
	.path1_mode = 3,
	.tun1_type = 3,
	.set_lock_led = dw210x_led_ctrl,
पूर्ण;

अटल काष्ठा ds3000_config su3000_ds3000_config = अणु
	.demod_address = 0x68,
	.ci_mode = 1,
	.set_lock_led = dw210x_led_ctrl,
पूर्ण;

अटल काष्ठा cxd2820r_config cxd2820r_config = अणु
	.i2c_address = 0x6c, /* (0xd8 >> 1) */
	.ts_mode = 0x38,
	.ts_घड़ी_inv = 1,
पूर्ण;

अटल काष्ठा tda18271_config tda18271_config = अणु
	.output_opt = TDA18271_OUTPUT_LT_OFF,
	.gate = TDA18271_GATE_DIGITAL,
पूर्ण;

अटल u8 m88rs2000_inittab[] = अणु
	DEMOD_WRITE, 0x9a, 0x30,
	DEMOD_WRITE, 0x00, 0x01,
	WRITE_DELAY, 0x19, 0x00,
	DEMOD_WRITE, 0x00, 0x00,
	DEMOD_WRITE, 0x9a, 0xb0,
	DEMOD_WRITE, 0x81, 0xc1,
	DEMOD_WRITE, 0x81, 0x81,
	DEMOD_WRITE, 0x86, 0xc6,
	DEMOD_WRITE, 0x9a, 0x30,
	DEMOD_WRITE, 0xf0, 0x80,
	DEMOD_WRITE, 0xf1, 0xbf,
	DEMOD_WRITE, 0xb0, 0x45,
	DEMOD_WRITE, 0xb2, 0x01,
	DEMOD_WRITE, 0x9a, 0xb0,
	0xff, 0xaa, 0xff
पूर्ण;

अटल काष्ठा m88rs2000_config s421_m88rs2000_config = अणु
	.demod_addr = 0x68,
	.inittab = m88rs2000_inittab,
पूर्ण;

अटल पूर्णांक dw2104_frontend_attach(काष्ठा dvb_usb_adapter *d)
अणु
	काष्ठा dvb_tuner_ops *tuner_ops = शून्य;

	अगर (demod_probe & 4) अणु
		d->fe_adap[0].fe = dvb_attach(stv0900_attach, &dw2104a_stv0900_config,
				&d->dev->i2c_adap, 0);
		अगर (d->fe_adap[0].fe != शून्य) अणु
			अगर (dvb_attach(stb6100_attach, d->fe_adap[0].fe,
					&dw2104a_stb6100_config,
					&d->dev->i2c_adap)) अणु
				tuner_ops = &d->fe_adap[0].fe->ops.tuner_ops;
				tuner_ops->set_frequency = stb6100_set_freq;
				tuner_ops->get_frequency = stb6100_get_freq;
				tuner_ops->set_bandwidth = stb6100_set_bandw;
				tuner_ops->get_bandwidth = stb6100_get_bandw;
				d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
				info("Attached STV0900+STB6100!");
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (demod_probe & 2) अणु
		d->fe_adap[0].fe = dvb_attach(stv0900_attach, &dw2104_stv0900_config,
				&d->dev->i2c_adap, 0);
		अगर (d->fe_adap[0].fe != शून्य) अणु
			अगर (dvb_attach(stv6110_attach, d->fe_adap[0].fe,
					&dw2104_stv6110_config,
					&d->dev->i2c_adap)) अणु
				d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
				info("Attached STV0900+STV6110A!");
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (demod_probe & 1) अणु
		d->fe_adap[0].fe = dvb_attach(cx24116_attach, &dw2104_config,
				&d->dev->i2c_adap);
		अगर (d->fe_adap[0].fe != शून्य) अणु
			d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached cx24116!");
			वापस 0;
		पूर्ण
	पूर्ण

	d->fe_adap[0].fe = dvb_attach(ds3000_attach, &dw2104_ds3000_config,
			&d->dev->i2c_adap);
	अगर (d->fe_adap[0].fe != शून्य) अणु
		dvb_attach(ts2020_attach, d->fe_adap[0].fe,
			&dw2104_ts2020_config, &d->dev->i2c_adap);
		d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
		info("Attached DS3000!");
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

अटल काष्ठा dvb_usb_device_properties dw2102_properties;
अटल काष्ठा dvb_usb_device_properties dw2104_properties;
अटल काष्ठा dvb_usb_device_properties s6x0_properties;

अटल पूर्णांक dw2102_frontend_attach(काष्ठा dvb_usb_adapter *d)
अणु
	अगर (dw2102_properties.i2c_algo == &dw2102_serit_i2c_algo) अणु
		/*dw2102_properties.adapter->tuner_attach = शून्य;*/
		d->fe_adap[0].fe = dvb_attach(si21xx_attach, &serit_sp1511lhb_config,
					&d->dev->i2c_adap);
		अगर (d->fe_adap[0].fe != शून्य) अणु
			d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached si21xx!");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (dw2102_properties.i2c_algo == &dw2102_earda_i2c_algo) अणु
		d->fe_adap[0].fe = dvb_attach(stv0288_attach, &earda_config,
					&d->dev->i2c_adap);
		अगर (d->fe_adap[0].fe != शून्य) अणु
			अगर (dvb_attach(stb6000_attach, d->fe_adap[0].fe, 0x61,
					&d->dev->i2c_adap)) अणु
				d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
				info("Attached stv0288!");
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dw2102_properties.i2c_algo == &dw2102_i2c_algo) अणु
		/*dw2102_properties.adapter->tuner_attach = dw2102_tuner_attach;*/
		d->fe_adap[0].fe = dvb_attach(stv0299_attach, &sharp_z0194a_config,
					&d->dev->i2c_adap);
		अगर (d->fe_adap[0].fe != शून्य) अणु
			d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached stv0299!");
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक dw3101_frontend_attach(काष्ठा dvb_usb_adapter *d)
अणु
	d->fe_adap[0].fe = dvb_attach(tda10023_attach, &dw3101_tda10023_config,
				&d->dev->i2c_adap, 0x48);
	अगर (d->fe_adap[0].fe != शून्य) अणु
		info("Attached tda10023!");
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक zl100313_frontend_attach(काष्ठा dvb_usb_adapter *d)
अणु
	d->fe_adap[0].fe = dvb_attach(mt312_attach, &zl313_config,
			&d->dev->i2c_adap);
	अगर (d->fe_adap[0].fe != शून्य) अणु
		अगर (dvb_attach(zl10039_attach, d->fe_adap[0].fe, 0x60,
				&d->dev->i2c_adap)) अणु
			d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached zl100313+zl10039!");
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक stv0288_frontend_attach(काष्ठा dvb_usb_adapter *d)
अणु
	u8 obuf[] = अणु7, 1पूर्ण;

	d->fe_adap[0].fe = dvb_attach(stv0288_attach, &earda_config,
			&d->dev->i2c_adap);

	अगर (d->fe_adap[0].fe == शून्य)
		वापस -EIO;

	अगर (शून्य == dvb_attach(stb6000_attach, d->fe_adap[0].fe, 0x61, &d->dev->i2c_adap))
		वापस -EIO;

	d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;

	dw210x_op_rw(d->dev->udev, 0x8a, 0, 0, obuf, 2, DW210X_WRITE_MSG);

	info("Attached stv0288+stb6000!");

	वापस 0;

पूर्ण

अटल पूर्णांक ds3000_frontend_attach(काष्ठा dvb_usb_adapter *d)
अणु
	काष्ठा dw2102_state *st = d->dev->priv;
	u8 obuf[] = अणु7, 1पूर्ण;

	d->fe_adap[0].fe = dvb_attach(ds3000_attach, &s660_ds3000_config,
			&d->dev->i2c_adap);

	अगर (d->fe_adap[0].fe == शून्य)
		वापस -EIO;

	dvb_attach(ts2020_attach, d->fe_adap[0].fe, &s660_ts2020_config,
		&d->dev->i2c_adap);

	st->old_set_voltage = d->fe_adap[0].fe->ops.set_voltage;
	d->fe_adap[0].fe->ops.set_voltage = s660_set_voltage;

	dw210x_op_rw(d->dev->udev, 0x8a, 0, 0, obuf, 2, DW210X_WRITE_MSG);

	info("Attached ds3000+ts2020!");

	वापस 0;
पूर्ण

अटल पूर्णांक prof_7500_frontend_attach(काष्ठा dvb_usb_adapter *d)
अणु
	u8 obuf[] = अणु7, 1पूर्ण;

	d->fe_adap[0].fe = dvb_attach(stv0900_attach, &prof_7500_stv0900_config,
					&d->dev->i2c_adap, 0);
	अगर (d->fe_adap[0].fe == शून्य)
		वापस -EIO;

	d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;

	dw210x_op_rw(d->dev->udev, 0x8a, 0, 0, obuf, 2, DW210X_WRITE_MSG);

	info("Attached STV0900+STB6100A!");

	वापस 0;
पूर्ण

अटल पूर्णांक su3000_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap->dev;
	काष्ठा dw2102_state *state = d->priv;

	mutex_lock(&d->data_mutex);

	state->data[0] = 0xe;
	state->data[1] = 0x80;
	state->data[2] = 0;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0xe;
	state->data[1] = 0x02;
	state->data[2] = 1;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");
	msleep(300);

	state->data[0] = 0xe;
	state->data[1] = 0x83;
	state->data[2] = 0;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0xe;
	state->data[1] = 0x83;
	state->data[2] = 1;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0x51;

	अगर (dvb_usb_generic_rw(d, state->data, 1, state->data, 1, 0) < 0)
		err("command 0x51 transfer failed.");

	mutex_unlock(&d->data_mutex);

	adap->fe_adap[0].fe = dvb_attach(ds3000_attach, &su3000_ds3000_config,
					&d->i2c_adap);
	अगर (adap->fe_adap[0].fe == शून्य)
		वापस -EIO;

	अगर (dvb_attach(ts2020_attach, adap->fe_adap[0].fe,
				&dw2104_ts2020_config,
				&d->i2c_adap)) अणु
		info("Attached DS3000/TS2020!");
		वापस 0;
	पूर्ण

	info("Failed to attach DS3000/TS2020!");
	वापस -EIO;
पूर्ण

अटल पूर्णांक t220_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap->dev;
	काष्ठा dw2102_state *state = d->priv;

	mutex_lock(&d->data_mutex);

	state->data[0] = 0xe;
	state->data[1] = 0x87;
	state->data[2] = 0x0;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0xe;
	state->data[1] = 0x86;
	state->data[2] = 1;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0xe;
	state->data[1] = 0x80;
	state->data[2] = 0;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	msleep(50);

	state->data[0] = 0xe;
	state->data[1] = 0x80;
	state->data[2] = 1;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0x51;

	अगर (dvb_usb_generic_rw(d, state->data, 1, state->data, 1, 0) < 0)
		err("command 0x51 transfer failed.");

	mutex_unlock(&d->data_mutex);

	adap->fe_adap[0].fe = dvb_attach(cxd2820r_attach, &cxd2820r_config,
					&d->i2c_adap, शून्य);
	अगर (adap->fe_adap[0].fe != शून्य) अणु
		अगर (dvb_attach(tda18271_attach, adap->fe_adap[0].fe, 0x60,
					&d->i2c_adap, &tda18271_config)) अणु
			info("Attached TDA18271HD/CXD2820R!");
			वापस 0;
		पूर्ण
	पूर्ण

	info("Failed to attach TDA18271HD/CXD2820R!");
	वापस -EIO;
पूर्ण

अटल पूर्णांक m88rs2000_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap->dev;
	काष्ठा dw2102_state *state = d->priv;

	mutex_lock(&d->data_mutex);

	state->data[0] = 0x51;

	अगर (dvb_usb_generic_rw(d, state->data, 1, state->data, 1, 0) < 0)
		err("command 0x51 transfer failed.");

	mutex_unlock(&d->data_mutex);

	adap->fe_adap[0].fe = dvb_attach(m88rs2000_attach,
					&s421_m88rs2000_config,
					&d->i2c_adap);

	अगर (adap->fe_adap[0].fe == शून्य)
		वापस -EIO;

	अगर (dvb_attach(ts2020_attach, adap->fe_adap[0].fe,
				&dw2104_ts2020_config,
				&d->i2c_adap)) अणु
		info("Attached RS2000/TS2020!");
		वापस 0;
	पूर्ण

	info("Failed to attach RS2000/TS2020!");
	वापस -EIO;
पूर्ण

अटल पूर्णांक tt_s2_4600_frontend_attach_probe_demod(काष्ठा dvb_usb_device *d,
						  स्थिर पूर्णांक probe_addr)
अणु
	काष्ठा dw2102_state *state = d->priv;

	state->data[0] = 0x9;
	state->data[1] = 0x1;
	state->data[2] = 0x1;
	state->data[3] = probe_addr;
	state->data[4] = 0x0;

	अगर (dvb_usb_generic_rw(d, state->data, 5, state->data, 2, 0) < 0) अणु
		err("i2c probe for address 0x%x failed.", probe_addr);
		वापस 0;
	पूर्ण

	अगर (state->data[0] != 8) /* fail(7) or error, no device at address */
		वापस 0;

	/* probing successful */
	वापस 1;
पूर्ण

अटल पूर्णांक tt_s2_4600_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap->dev;
	काष्ठा dw2102_state *state = d->priv;
	काष्ठा i2c_adapter *i2c_adapter;
	काष्ठा i2c_client *client;
	काष्ठा i2c_board_info board_info;
	काष्ठा m88ds3103_platक्रमm_data m88ds3103_pdata = अणुपूर्ण;
	काष्ठा ts2020_config ts2020_config = अणुपूर्ण;
	पूर्णांक demod_addr;

	mutex_lock(&d->data_mutex);

	state->data[0] = 0xe;
	state->data[1] = 0x80;
	state->data[2] = 0x0;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0xe;
	state->data[1] = 0x02;
	state->data[2] = 1;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");
	msleep(300);

	state->data[0] = 0xe;
	state->data[1] = 0x83;
	state->data[2] = 0;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0xe;
	state->data[1] = 0x83;
	state->data[2] = 1;

	अगर (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0x51;

	अगर (dvb_usb_generic_rw(d, state->data, 1, state->data, 1, 0) < 0)
		err("command 0x51 transfer failed.");

	/* probe क्रम demodulator i2c address */
	demod_addr = -1;
	अगर (tt_s2_4600_frontend_attach_probe_demod(d, 0x68))
		demod_addr = 0x68;
	अन्यथा अगर (tt_s2_4600_frontend_attach_probe_demod(d, 0x69))
		demod_addr = 0x69;
	अन्यथा अगर (tt_s2_4600_frontend_attach_probe_demod(d, 0x6a))
		demod_addr = 0x6a;

	mutex_unlock(&d->data_mutex);

	अगर (demod_addr < 0) अणु
		err("probing for demodulator failed. Is the external power switched on?");
		वापस -ENODEV;
	पूर्ण

	/* attach demod */
	m88ds3103_pdata.clk = 27000000;
	m88ds3103_pdata.i2c_wr_max = 33;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_CI;
	m88ds3103_pdata.ts_clk = 16000;
	m88ds3103_pdata.ts_clk_pol = 0;
	m88ds3103_pdata.spec_inv = 0;
	m88ds3103_pdata.agc = 0x99;
	m88ds3103_pdata.agc_inv = 0;
	m88ds3103_pdata.clk_out = M88DS3103_CLOCK_OUT_ENABLED;
	m88ds3103_pdata.envelope_mode = 0;
	m88ds3103_pdata.lnb_hv_pol = 1;
	m88ds3103_pdata.lnb_en_pol = 0;
	स_रखो(&board_info, 0, माप(board_info));
	अगर (demod_addr == 0x6a)
		strscpy(board_info.type, "m88ds3103b", I2C_NAME_SIZE);
	अन्यथा
		strscpy(board_info.type, "m88ds3103", I2C_NAME_SIZE);
	board_info.addr = demod_addr;
	board_info.platक्रमm_data = &m88ds3103_pdata;
	request_module("m88ds3103");
	client = i2c_new_client_device(&d->i2c_adap, &board_info);
	अगर (!i2c_client_has_driver(client))
		वापस -ENODEV;
	अगर (!try_module_get(client->dev.driver->owner)) अणु
		i2c_unरेजिस्टर_device(client);
		वापस -ENODEV;
	पूर्ण
	adap->fe_adap[0].fe = m88ds3103_pdata.get_dvb_frontend(client);
	i2c_adapter = m88ds3103_pdata.get_i2c_adapter(client);

	state->i2c_client_demod = client;

	/* attach tuner */
	ts2020_config.fe = adap->fe_adap[0].fe;
	स_रखो(&board_info, 0, माप(board_info));
	strscpy(board_info.type, "ts2022", I2C_NAME_SIZE);
	board_info.addr = 0x60;
	board_info.platक्रमm_data = &ts2020_config;
	request_module("ts2020");
	client = i2c_new_client_device(i2c_adapter, &board_info);

	अगर (!i2c_client_has_driver(client)) अणु
		dvb_frontend_detach(adap->fe_adap[0].fe);
		वापस -ENODEV;
	पूर्ण

	अगर (!try_module_get(client->dev.driver->owner)) अणु
		i2c_unरेजिस्टर_device(client);
		dvb_frontend_detach(adap->fe_adap[0].fe);
		वापस -ENODEV;
	पूर्ण

	/* delegate संकेत strength measurement to tuner */
	adap->fe_adap[0].fe->ops.पढ़ो_संकेत_strength =
			adap->fe_adap[0].fe->ops.tuner_ops.get_rf_strength;

	state->i2c_client_tuner = client;

	/* hook fe: need to resync the slave fअगरo when संकेत locks */
	state->fe_पढ़ो_status = adap->fe_adap[0].fe->ops.पढ़ो_status;
	adap->fe_adap[0].fe->ops.पढ़ो_status = tt_s2_4600_पढ़ो_status;

	state->last_lock = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक dw2102_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x60,
		&adap->dev->i2c_adap, DVB_PLL_OPERA1);
	वापस 0;
पूर्ण

अटल पूर्णांक dw3101_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x60,
		&adap->dev->i2c_adap, DVB_PLL_TUA6034);

	वापस 0;
पूर्ण

अटल पूर्णांक dw2102_rc_query(काष्ठा dvb_usb_device *d)
अणु
	u8 key[2];
	काष्ठा i2c_msg msg = अणु
		.addr = DW2102_RC_QUERY,
		.flags = I2C_M_RD,
		.buf = key,
		.len = 2
	पूर्ण;

	अगर (d->props.i2c_algo->master_xfer(&d->i2c_adap, &msg, 1) == 1) अणु
		अगर (msg.buf[0] != 0xff) अणु
			deb_rc("%s: rc code: %x, %x\n",
					__func__, key[0], key[1]);
			rc_keyकरोwn(d->rc_dev, RC_PROTO_UNKNOWN, key[0], 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prof_rc_query(काष्ठा dvb_usb_device *d)
अणु
	u8 key[2];
	काष्ठा i2c_msg msg = अणु
		.addr = DW2102_RC_QUERY,
		.flags = I2C_M_RD,
		.buf = key,
		.len = 2
	पूर्ण;

	अगर (d->props.i2c_algo->master_xfer(&d->i2c_adap, &msg, 1) == 1) अणु
		अगर (msg.buf[0] != 0xff) अणु
			deb_rc("%s: rc code: %x, %x\n",
					__func__, key[0], key[1]);
			rc_keyकरोwn(d->rc_dev, RC_PROTO_UNKNOWN, key[0] ^ 0xff,
				   0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक su3000_rc_query(काष्ठा dvb_usb_device *d)
अणु
	u8 key[2];
	काष्ठा i2c_msg msg = अणु
		.addr = DW2102_RC_QUERY,
		.flags = I2C_M_RD,
		.buf = key,
		.len = 2
	पूर्ण;

	अगर (d->props.i2c_algo->master_xfer(&d->i2c_adap, &msg, 1) == 1) अणु
		अगर (msg.buf[0] != 0xff) अणु
			deb_rc("%s: rc code: %x, %x\n",
					__func__, key[0], key[1]);
			rc_keyकरोwn(d->rc_dev, RC_PROTO_RC5,
				   RC_SCANCODE_RC5(key[1], key[0]), 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत dw2102_table_entry अणु
	CYPRESS_DW2102,
	CYPRESS_DW2101,
	CYPRESS_DW2104,
	TEVII_S650,
	TERRATEC_CINERGY_S,
	CYPRESS_DW3101,
	TEVII_S630,
	PROF_1100,
	TEVII_S660,
	PROF_7500,
	GENIATECH_SU3000,
	HAUPPAUGE_MAX_S2,
	TERRATEC_CINERGY_S2,
	TEVII_S480_1,
	TEVII_S480_2,
	X3M_SPC1400HD,
	TEVII_S421,
	TEVII_S632,
	TERRATEC_CINERGY_S2_R2,
	TERRATEC_CINERGY_S2_R3,
	TERRATEC_CINERGY_S2_R4,
	TERRATEC_CINERGY_S2_1,
	TERRATEC_CINERGY_S2_2,
	GOTVIEW_SAT_HD,
	GENIATECH_T220,
	TECHNOTREND_S2_4600,
	TEVII_S482_1,
	TEVII_S482_2,
	TERRATEC_CINERGY_S2_BOX,
	TEVII_S662
पूर्ण;

अटल काष्ठा usb_device_id dw2102_table[] = अणु
	[CYPRESS_DW2102] = अणुUSB_DEVICE(USB_VID_CYPRESS, USB_PID_DW2102)पूर्ण,
	[CYPRESS_DW2101] = अणुUSB_DEVICE(USB_VID_CYPRESS, 0x2101)पूर्ण,
	[CYPRESS_DW2104] = अणुUSB_DEVICE(USB_VID_CYPRESS, USB_PID_DW2104)पूर्ण,
	[TEVII_S650] = अणुUSB_DEVICE(0x9022, USB_PID_TEVII_S650)पूर्ण,
	[TERRATEC_CINERGY_S] = अणुUSB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_S)पूर्ण,
	[CYPRESS_DW3101] = अणुUSB_DEVICE(USB_VID_CYPRESS, USB_PID_DW3101)पूर्ण,
	[TEVII_S630] = अणुUSB_DEVICE(0x9022, USB_PID_TEVII_S630)पूर्ण,
	[PROF_1100] = अणुUSB_DEVICE(0x3011, USB_PID_PROF_1100)पूर्ण,
	[TEVII_S660] = अणुUSB_DEVICE(0x9022, USB_PID_TEVII_S660)पूर्ण,
	[PROF_7500] = अणुUSB_DEVICE(0x3034, 0x7500)पूर्ण,
	[GENIATECH_SU3000] = अणुUSB_DEVICE(0x1f4d, 0x3000)पूर्ण,
	[HAUPPAUGE_MAX_S2] = अणुUSB_DEVICE(0x2040, 0xd900)पूर्ण,
	[TERRATEC_CINERGY_S2] = अणुUSB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_S2_R1)पूर्ण,
	[TEVII_S480_1] = अणुUSB_DEVICE(0x9022, USB_PID_TEVII_S480_1)पूर्ण,
	[TEVII_S480_2] = अणुUSB_DEVICE(0x9022, USB_PID_TEVII_S480_2)पूर्ण,
	[X3M_SPC1400HD] = अणुUSB_DEVICE(0x1f4d, 0x3100)पूर्ण,
	[TEVII_S421] = अणुUSB_DEVICE(0x9022, USB_PID_TEVII_S421)पूर्ण,
	[TEVII_S632] = अणुUSB_DEVICE(0x9022, USB_PID_TEVII_S632)पूर्ण,
	[TERRATEC_CINERGY_S2_R2] = अणुUSB_DEVICE(USB_VID_TERRATEC,
				    USB_PID_TERRATEC_CINERGY_S2_R2)पूर्ण,
	[TERRATEC_CINERGY_S2_R3] = अणुUSB_DEVICE(USB_VID_TERRATEC,
				    USB_PID_TERRATEC_CINERGY_S2_R3)पूर्ण,
	[TERRATEC_CINERGY_S2_R4] = अणुUSB_DEVICE(USB_VID_TERRATEC,
				    USB_PID_TERRATEC_CINERGY_S2_R4)पूर्ण,
	[TERRATEC_CINERGY_S2_1] = अणुUSB_DEVICE(USB_VID_TERRATEC_2,
				   USB_PID_TERRATEC_CINERGY_S2_1)पूर्ण,
	[TERRATEC_CINERGY_S2_2] = अणुUSB_DEVICE(USB_VID_TERRATEC_2,
				   USB_PID_TERRATEC_CINERGY_S2_2)पूर्ण,
	[GOTVIEW_SAT_HD] = अणुUSB_DEVICE(0x1FE1, USB_PID_GOTVIEW_SAT_HD)पूर्ण,
	[GENIATECH_T220] = अणुUSB_DEVICE(0x1f4d, 0xD220)पूर्ण,
	[TECHNOTREND_S2_4600] = अणुUSB_DEVICE(USB_VID_TECHNOTREND,
		USB_PID_TECHNOTREND_CONNECT_S2_4600)पूर्ण,
	[TEVII_S482_1] = अणुUSB_DEVICE(0x9022, 0xd483)पूर्ण,
	[TEVII_S482_2] = अणुUSB_DEVICE(0x9022, 0xd484)पूर्ण,
	[TERRATEC_CINERGY_S2_BOX] = अणुUSB_DEVICE(USB_VID_TERRATEC, 0x0105)पूर्ण,
	[TEVII_S662] = अणुUSB_DEVICE(0x9022, USB_PID_TEVII_S662)पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, dw2102_table);

अटल पूर्णांक dw2102_load_firmware(काष्ठा usb_device *dev,
			स्थिर काष्ठा firmware *frmwr)
अणु
	u8 *b, *p;
	पूर्णांक ret = 0, i;
	u8 reset;
	u8 reset16[] = अणु0, 0, 0, 0, 0, 0, 0पूर्ण;
	स्थिर काष्ठा firmware *fw;

	चयन (le16_to_cpu(dev->descriptor.idProduct)) अणु
	हाल 0x2101:
		ret = request_firmware(&fw, DW2101_FIRMWARE, &dev->dev);
		अगर (ret != 0) अणु
			err(err_str, DW2101_FIRMWARE);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		fw = frmwr;
		अवरोध;
	पूर्ण
	info("start downloading DW210X firmware");
	p = kदो_स्मृति(fw->size, GFP_KERNEL);
	reset = 1;
	/*stop the CPU*/
	dw210x_op_rw(dev, 0xa0, 0x7f92, 0, &reset, 1, DW210X_WRITE_MSG);
	dw210x_op_rw(dev, 0xa0, 0xe600, 0, &reset, 1, DW210X_WRITE_MSG);

	अगर (p != शून्य) अणु
		स_नकल(p, fw->data, fw->size);
		क्रम (i = 0; i < fw->size; i += 0x40) अणु
			b = (u8 *) p + i;
			अगर (dw210x_op_rw(dev, 0xa0, i, 0, b , 0x40,
					DW210X_WRITE_MSG) != 0x40) अणु
				err("error while transferring firmware");
				ret = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण
		/* restart the CPU */
		reset = 0;
		अगर (ret || dw210x_op_rw(dev, 0xa0, 0x7f92, 0, &reset, 1,
					DW210X_WRITE_MSG) != 1) अणु
			err("could not restart the USB controller CPU.");
			ret = -EINVAL;
		पूर्ण
		अगर (ret || dw210x_op_rw(dev, 0xa0, 0xe600, 0, &reset, 1,
					DW210X_WRITE_MSG) != 1) अणु
			err("could not restart the USB controller CPU.");
			ret = -EINVAL;
		पूर्ण
		/* init रेजिस्टरs */
		चयन (le16_to_cpu(dev->descriptor.idProduct)) अणु
		हाल USB_PID_TEVII_S650:
			dw2104_properties.rc.core.rc_codes = RC_MAP_TEVII_NEC;
			fallthrough;
		हाल USB_PID_DW2104:
			reset = 1;
			dw210x_op_rw(dev, 0xc4, 0x0000, 0, &reset, 1,
					DW210X_WRITE_MSG);
			fallthrough;
		हाल USB_PID_DW3101:
			reset = 0;
			dw210x_op_rw(dev, 0xbf, 0x0040, 0, &reset, 0,
					DW210X_WRITE_MSG);
			अवरोध;
		हाल USB_PID_TERRATEC_CINERGY_S:
		हाल USB_PID_DW2102:
			dw210x_op_rw(dev, 0xbf, 0x0040, 0, &reset, 0,
					DW210X_WRITE_MSG);
			dw210x_op_rw(dev, 0xb9, 0x0000, 0, &reset16[0], 2,
					DW210X_READ_MSG);
			/* check STV0299 frontend  */
			dw210x_op_rw(dev, 0xb5, 0, 0, &reset16[0], 2,
					DW210X_READ_MSG);
			अगर ((reset16[0] == 0xa1) || (reset16[0] == 0x80)) अणु
				dw2102_properties.i2c_algo = &dw2102_i2c_algo;
				dw2102_properties.adapter->fe[0].tuner_attach = &dw2102_tuner_attach;
				अवरोध;
			पूर्ण अन्यथा अणु
				/* check STV0288 frontend  */
				reset16[0] = 0xd0;
				reset16[1] = 1;
				reset16[2] = 0;
				dw210x_op_rw(dev, 0xc2, 0, 0, &reset16[0], 3,
						DW210X_WRITE_MSG);
				dw210x_op_rw(dev, 0xc3, 0xd1, 0, &reset16[0], 3,
						DW210X_READ_MSG);
				अगर (reset16[2] == 0x11) अणु
					dw2102_properties.i2c_algo = &dw2102_earda_i2c_algo;
					अवरोध;
				पूर्ण
			पूर्ण
			fallthrough;
		हाल 0x2101:
			dw210x_op_rw(dev, 0xbc, 0x0030, 0, &reset16[0], 2,
					DW210X_READ_MSG);
			dw210x_op_rw(dev, 0xba, 0x0000, 0, &reset16[0], 7,
					DW210X_READ_MSG);
			dw210x_op_rw(dev, 0xba, 0x0000, 0, &reset16[0], 7,
					DW210X_READ_MSG);
			dw210x_op_rw(dev, 0xb9, 0x0000, 0, &reset16[0], 2,
					DW210X_READ_MSG);
			अवरोध;
		पूर्ण

		msleep(100);
		kमुक्त(p);
	पूर्ण

	अगर (le16_to_cpu(dev->descriptor.idProduct) == 0x2101)
		release_firmware(fw);
	वापस ret;
पूर्ण

अटल काष्ठा dvb_usb_device_properties dw2102_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = DEVICE_SPECIFIC,
	.firmware = DW2102_FIRMWARE,
	.no_reconnect = 1,

	.i2c_algo = &dw2102_serit_i2c_algo,

	.rc.core = अणु
		.rc_पूर्णांकerval = 150,
		.rc_codes = RC_MAP_DM1105_NEC,
		.module_name = "dw2102",
		.allowed_protos   = RC_PROTO_BIT_NEC,
		.rc_query = dw2102_rc_query,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x81,
	/* parameter क्रम the MPEG2-data transfer */
	.num_adapters = 1,
	.करोwnload_firmware = dw2102_load_firmware,
	.पढ़ो_mac_address = dw210x_पढ़ो_mac_address,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach = dw2102_frontend_attach,
			.stream = अणु
				.type = USB_BULK,
				.count = 8,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.num_device_descs = 3,
	.devices = अणु
		अणु"DVBWorld DVB-S 2102 USB2.0",
			अणु&dw2102_table[CYPRESS_DW2102], शून्यपूर्ण,
			अणुशून्यपूर्ण,
		पूर्ण,
		अणु"DVBWorld DVB-S 2101 USB2.0",
			अणु&dw2102_table[CYPRESS_DW2101], शून्यपूर्ण,
			अणुशून्यपूर्ण,
		पूर्ण,
		अणु"TerraTec Cinergy S USB",
			अणु&dw2102_table[TERRATEC_CINERGY_S], शून्यपूर्ण,
			अणुशून्यपूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties dw2104_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = DEVICE_SPECIFIC,
	.firmware = DW2104_FIRMWARE,
	.no_reconnect = 1,

	.i2c_algo = &dw2104_i2c_algo,
	.rc.core = अणु
		.rc_पूर्णांकerval = 150,
		.rc_codes = RC_MAP_DM1105_NEC,
		.module_name = "dw2102",
		.allowed_protos   = RC_PROTO_BIT_NEC,
		.rc_query = dw2102_rc_query,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x81,
	/* parameter क्रम the MPEG2-data transfer */
	.num_adapters = 1,
	.करोwnload_firmware = dw2102_load_firmware,
	.पढ़ो_mac_address = dw210x_पढ़ो_mac_address,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach = dw2104_frontend_attach,
			.stream = अणु
				.type = USB_BULK,
				.count = 8,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.num_device_descs = 2,
	.devices = अणु
		अणु "DVBWorld DW2104 USB2.0",
			अणु&dw2102_table[CYPRESS_DW2104], शून्यपूर्ण,
			अणुशून्यपूर्ण,
		पूर्ण,
		अणु "TeVii S650 USB2.0",
			अणु&dw2102_table[TEVII_S650], शून्यपूर्ण,
			अणुशून्यपूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties dw3101_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = DEVICE_SPECIFIC,
	.firmware = DW3101_FIRMWARE,
	.no_reconnect = 1,

	.i2c_algo = &dw3101_i2c_algo,
	.rc.core = अणु
		.rc_पूर्णांकerval = 150,
		.rc_codes = RC_MAP_DM1105_NEC,
		.module_name = "dw2102",
		.allowed_protos   = RC_PROTO_BIT_NEC,
		.rc_query = dw2102_rc_query,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x81,
	/* parameter क्रम the MPEG2-data transfer */
	.num_adapters = 1,
	.करोwnload_firmware = dw2102_load_firmware,
	.पढ़ो_mac_address = dw210x_पढ़ो_mac_address,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach = dw3101_frontend_attach,
			.tuner_attach = dw3101_tuner_attach,
			.stream = अणु
				.type = USB_BULK,
				.count = 8,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.num_device_descs = 1,
	.devices = अणु
		अणु "DVBWorld DVB-C 3101 USB2.0",
			अणु&dw2102_table[CYPRESS_DW3101], शून्यपूर्ण,
			अणुशून्यपूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties s6x0_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = DEVICE_SPECIFIC,
	.size_of_priv = माप(काष्ठा dw2102_state),
	.firmware = S630_FIRMWARE,
	.no_reconnect = 1,

	.i2c_algo = &s6x0_i2c_algo,
	.rc.core = अणु
		.rc_पूर्णांकerval = 150,
		.rc_codes = RC_MAP_TEVII_NEC,
		.module_name = "dw2102",
		.allowed_protos   = RC_PROTO_BIT_NEC,
		.rc_query = dw2102_rc_query,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x81,
	.num_adapters = 1,
	.करोwnload_firmware = dw2102_load_firmware,
	.पढ़ो_mac_address = s6x0_पढ़ो_mac_address,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach = zl100313_frontend_attach,
			.stream = अणु
				.type = USB_BULK,
				.count = 8,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.num_device_descs = 1,
	.devices = अणु
		अणु"TeVii S630 USB",
			अणु&dw2102_table[TEVII_S630], शून्यपूर्ण,
			अणुशून्यपूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dvb_usb_device_description d1100 = अणु
	"Prof 1100 USB ",
	अणु&dw2102_table[PROF_1100], शून्यपूर्ण,
	अणुशून्यपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dvb_usb_device_description d660 = अणु
	"TeVii S660 USB",
	अणु&dw2102_table[TEVII_S660], शून्यपूर्ण,
	अणुशून्यपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dvb_usb_device_description d480_1 = अणु
	"TeVii S480.1 USB",
	अणु&dw2102_table[TEVII_S480_1], शून्यपूर्ण,
	अणुशून्यपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dvb_usb_device_description d480_2 = अणु
	"TeVii S480.2 USB",
	अणु&dw2102_table[TEVII_S480_2], शून्यपूर्ण,
	अणुशून्यपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dvb_usb_device_description d7500 = अणु
	"Prof 7500 USB DVB-S2",
	अणु&dw2102_table[PROF_7500], शून्यपूर्ण,
	अणुशून्यपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dvb_usb_device_description d421 = अणु
	"TeVii S421 PCI",
	अणु&dw2102_table[TEVII_S421], शून्यपूर्ण,
	अणुशून्यपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dvb_usb_device_description d632 = अणु
	"TeVii S632 USB",
	अणु&dw2102_table[TEVII_S632], शून्यपूर्ण,
	अणुशून्यपूर्ण,
पूर्ण;

अटल काष्ठा dvb_usb_device_properties su3000_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = DEVICE_SPECIFIC,
	.size_of_priv = माप(काष्ठा dw2102_state),
	.घातer_ctrl = su3000_घातer_ctrl,
	.num_adapters = 1,
	.identअगरy_state	= su3000_identअगरy_state,
	.i2c_algo = &su3000_i2c_algo,

	.rc.core = अणु
		.rc_पूर्णांकerval = 150,
		.rc_codes = RC_MAP_SU3000,
		.module_name = "dw2102",
		.allowed_protos   = RC_PROTO_BIT_RC5,
		.rc_query = su3000_rc_query,
	पूर्ण,

	.पढ़ो_mac_address = su3000_पढ़ो_mac_address,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = su3000_streaming_ctrl,
			.frontend_attach  = su3000_frontend_attach,
			.stream = अणु
				.type = USB_BULK,
				.count = 8,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.num_device_descs = 9,
	.devices = अणु
		अणु "SU3000HD DVB-S USB2.0",
			अणु &dw2102_table[GENIATECH_SU3000], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "Hauppauge MAX S2 or WinTV NOVA HD USB2.0",
			अणु &dw2102_table[HAUPPAUGE_MAX_S2], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "Terratec Cinergy S2 USB HD",
			अणु &dw2102_table[TERRATEC_CINERGY_S2], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "X3M TV SPC1400HD PCI",
			अणु &dw2102_table[X3M_SPC1400HD], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "Terratec Cinergy S2 USB HD Rev.2",
			अणु &dw2102_table[TERRATEC_CINERGY_S2_R2], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "Terratec Cinergy S2 USB HD Rev.3",
			अणु &dw2102_table[TERRATEC_CINERGY_S2_R3], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "Terratec Cinergy S2 PCIe Dual Port 1",
			अणु &dw2102_table[TERRATEC_CINERGY_S2_1], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "Terratec Cinergy S2 PCIe Dual Port 2",
			अणु &dw2102_table[TERRATEC_CINERGY_S2_2], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "GOTVIEW Satellite HD",
			अणु &dw2102_table[GOTVIEW_SAT_HD], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties t220_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = DEVICE_SPECIFIC,
	.size_of_priv = माप(काष्ठा dw2102_state),
	.घातer_ctrl = su3000_घातer_ctrl,
	.num_adapters = 1,
	.identअगरy_state	= su3000_identअगरy_state,
	.i2c_algo = &su3000_i2c_algo,

	.rc.core = अणु
		.rc_पूर्णांकerval = 150,
		.rc_codes = RC_MAP_SU3000,
		.module_name = "dw2102",
		.allowed_protos   = RC_PROTO_BIT_RC5,
		.rc_query = su3000_rc_query,
	पूर्ण,

	.पढ़ो_mac_address = su3000_पढ़ो_mac_address,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणु अणु
			.streaming_ctrl   = su3000_streaming_ctrl,
			.frontend_attach  = t220_frontend_attach,
			.stream = अणु
				.type = USB_BULK,
				.count = 8,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण पूर्ण,
		पूर्ण
	पूर्ण,
	.num_device_descs = 1,
	.devices = अणु
		अणु "Geniatech T220 DVB-T/T2 USB2.0",
			अणु &dw2102_table[GENIATECH_T220], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties tt_s2_4600_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = DEVICE_SPECIFIC,
	.size_of_priv = माप(काष्ठा dw2102_state),
	.घातer_ctrl = su3000_घातer_ctrl,
	.num_adapters = 1,
	.identअगरy_state	= su3000_identअगरy_state,
	.i2c_algo = &su3000_i2c_algo,

	.rc.core = अणु
		.rc_पूर्णांकerval = 250,
		.rc_codes = RC_MAP_TT_1500,
		.module_name = "dw2102",
		.allowed_protos   = RC_PROTO_BIT_RC5,
		.rc_query = su3000_rc_query,
	पूर्ण,

	.पढ़ो_mac_address = su3000_पढ़ो_mac_address,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = su3000_streaming_ctrl,
			.frontend_attach  = tt_s2_4600_frontend_attach,
			.stream = अणु
				.type = USB_BULK,
				.count = 8,
				.endpoपूर्णांक = 0x82,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण पूर्ण,
		पूर्ण
	पूर्ण,
	.num_device_descs = 5,
	.devices = अणु
		अणु "TechnoTrend TT-connect S2-4600",
			अणु &dw2102_table[TECHNOTREND_S2_4600], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "TeVii S482 (tuner 1)",
			अणु &dw2102_table[TEVII_S482_1], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "TeVii S482 (tuner 2)",
			अणु &dw2102_table[TEVII_S482_2], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "Terratec Cinergy S2 USB BOX",
			अणु &dw2102_table[TERRATEC_CINERGY_S2_BOX], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु "TeVii S662",
			अणु &dw2102_table[TEVII_S662], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल पूर्णांक dw2102_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक retval = -ENOMEM;
	काष्ठा dvb_usb_device_properties *p1100;
	काष्ठा dvb_usb_device_properties *s660;
	काष्ठा dvb_usb_device_properties *p7500;
	काष्ठा dvb_usb_device_properties *s421;

	p1100 = kmemdup(&s6x0_properties,
			माप(काष्ठा dvb_usb_device_properties), GFP_KERNEL);
	अगर (!p1100)
		जाओ err0;

	/* copy शेष काष्ठाure */
	/* fill only dअगरferent fields */
	p1100->firmware = P1100_FIRMWARE;
	p1100->devices[0] = d1100;
	p1100->rc.core.rc_query = prof_rc_query;
	p1100->rc.core.rc_codes = RC_MAP_TBS_NEC;
	p1100->adapter->fe[0].frontend_attach = stv0288_frontend_attach;

	s660 = kmemdup(&s6x0_properties,
		       माप(काष्ठा dvb_usb_device_properties), GFP_KERNEL);
	अगर (!s660)
		जाओ err1;

	s660->firmware = S660_FIRMWARE;
	s660->num_device_descs = 3;
	s660->devices[0] = d660;
	s660->devices[1] = d480_1;
	s660->devices[2] = d480_2;
	s660->adapter->fe[0].frontend_attach = ds3000_frontend_attach;

	p7500 = kmemdup(&s6x0_properties,
			माप(काष्ठा dvb_usb_device_properties), GFP_KERNEL);
	अगर (!p7500)
		जाओ err2;

	p7500->firmware = P7500_FIRMWARE;
	p7500->devices[0] = d7500;
	p7500->rc.core.rc_query = prof_rc_query;
	p7500->rc.core.rc_codes = RC_MAP_TBS_NEC;
	p7500->adapter->fe[0].frontend_attach = prof_7500_frontend_attach;


	s421 = kmemdup(&su3000_properties,
		       माप(काष्ठा dvb_usb_device_properties), GFP_KERNEL);
	अगर (!s421)
		जाओ err3;

	s421->num_device_descs = 2;
	s421->devices[0] = d421;
	s421->devices[1] = d632;
	s421->adapter->fe[0].frontend_attach = m88rs2000_frontend_attach;

	अगर (0 == dvb_usb_device_init(पूर्णांकf, &dw2102_properties,
			THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &dw2104_properties,
			THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &dw3101_properties,
			THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &s6x0_properties,
			THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, p1100,
			THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, s660,
			THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, p7500,
			THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, s421,
			THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &su3000_properties,
			 THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &t220_properties,
			 THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &tt_s2_4600_properties,
			 THIS_MODULE, शून्य, adapter_nr)) अणु

		/* clean up copied properties */
		kमुक्त(s421);
		kमुक्त(p7500);
		kमुक्त(s660);
		kमुक्त(p1100);

		वापस 0;
	पूर्ण

	retval = -ENODEV;
	kमुक्त(s421);
err3:
	kमुक्त(p7500);
err2:
	kमुक्त(s660);
err1:
	kमुक्त(p1100);
err0:
	वापस retval;
पूर्ण

अटल व्योम dw2102_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा dw2102_state *st = (काष्ठा dw2102_state *)d->priv;
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

अटल काष्ठा usb_driver dw2102_driver = अणु
	.name = "dw2102",
	.probe = dw2102_probe,
	.disconnect = dw2102_disconnect,
	.id_table = dw2102_table,
पूर्ण;

module_usb_driver(dw2102_driver);

MODULE_AUTHOR("Igor M. Liplianin (c) liplianin@me.by");
MODULE_DESCRIPTION("Driver for DVBWorld DVB-S 2101, 2102, DVB-S2 2104, DVB-C 3101 USB2.0, TeVii S421, S480, S482, S600, S630, S632, S650, TeVii S660, S662, Prof 1100, 7500 USB2.0, Geniatech SU3000, T220, TechnoTrend S2-4600, Terratec Cinergy S2 devices");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(DW2101_FIRMWARE);
MODULE_FIRMWARE(DW2102_FIRMWARE);
MODULE_FIRMWARE(DW2104_FIRMWARE);
MODULE_FIRMWARE(DW3101_FIRMWARE);
MODULE_FIRMWARE(S630_FIRMWARE);
MODULE_FIRMWARE(S660_FIRMWARE);
MODULE_FIRMWARE(P1100_FIRMWARE);
MODULE_FIRMWARE(P7500_FIRMWARE);
