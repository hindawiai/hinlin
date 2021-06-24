<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant linux driver क्रम
 *
 * DM04/QQBOX DVB-S USB BOX	LME2510C + SHARP:BS2F7HZ7395
 *				LME2510C + LG TDQY-P001F
 *				LME2510C + BS2F7HZ0194
 *				LME2510 + LG TDQY-P001F
 *				LME2510 + BS2F7HZ0194
 *
 * MVB7395 (LME2510C+SHARP:BS2F7HZ7395)
 * SHARP:BS2F7HZ7395 = (STV0288+Sharp IX2505V)
 *
 * MV001F (LME2510+LGTDQY-P001F)
 * LG TDQY - P001F =(TDA8263 + TDA10086H)
 *
 * MVB0001F (LME2510C+LGTDQT-P001F)
 *
 * MV0194 (LME2510+SHARP:BS2F7HZ0194)
 * SHARP:BS2F7HZ0194 = (STV0299+IX2410)
 *
 * MVB0194 (LME2510C+SHARP0194)
 *
 * LME2510C + M88RS2000
 *
 * For firmware see Documentation/admin-guide/media/lmedm04.rst
 *
 * I2C addresses:
 * 0xd0 - STV0288	- Demodulator
 * 0xc0 - Sharp IX2505V	- Tuner
 * --
 * 0x1c - TDA10086   - Demodulator
 * 0xc0 - TDA8263    - Tuner
 * --
 * 0xd0 - STV0299	- Demodulator
 * 0xc0 - IX2410	- Tuner
 *
 * VID = 3344  PID LME2510=1122 LME2510C=1120
 *
 * Copyright (C) 2010 Malcolm Priestley (tvboxspy@gmail.com)
 * LME2510(C)(C) Leaguerme (Shenzhen) MicroElectronics Co., Ltd.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 *
 * Known Issues :
 *	LME2510: Non Intel USB chipsets fail to मुख्यtain High Speed on
 * Boot or Hot Plug.
 *
 * QQbox suffers from noise on LNB voltage.
 *
 *	LME2510: SHARP:BS2F7HZ0194(MV0194) cannot cold reset and share प्रणाली
 * with other tuners. After a cold reset streaming will not start.
 *
 * M88RS2000 suffers from loss of lock.
 */
#घोषणा DVB_USB_LOG_PREFIX "LME2510(C)"
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <media/rc-core.h>

#समावेश "dvb_usb.h"
#समावेश "lmedm04.h"
#समावेश "tda826x.h"
#समावेश "tda10086.h"
#समावेश "stv0288.h"
#समावेश "ix2505v.h"
#समावेश "stv0299.h"
#समावेश "dvb-pll.h"
#समावेश "z0194a.h"
#समावेश "m88rs2000.h"
#समावेश "ts2020.h"


#घोषणा LME2510_C_S7395	"dvb-usb-lme2510c-s7395.fw";
#घोषणा LME2510_C_LG	"dvb-usb-lme2510c-lg.fw";
#घोषणा LME2510_C_S0194	"dvb-usb-lme2510c-s0194.fw";
#घोषणा LME2510_C_RS2000 "dvb-usb-lme2510c-rs2000.fw";
#घोषणा LME2510_LG	"dvb-usb-lme2510-lg.fw";
#घोषणा LME2510_S0194	"dvb-usb-lme2510-s0194.fw";

/* debug */
अटल पूर्णांक dvb_usb_lme2510_debug;
#घोषणा lme_debug(var, level, args...) करो अणु \
	अगर ((var >= level)) \
		pr_debug(DVB_USB_LOG_PREFIX": " args); \
पूर्ण जबतक (0)
#घोषणा deb_info(level, args...) lme_debug(dvb_usb_lme2510_debug, level, args)
#घोषणा debug_data_snipet(level, name, p) \
	 deb_info(level, name" (%8phN)", p);
#घोषणा info(args...) pr_info(DVB_USB_LOG_PREFIX": "args)

module_param_named(debug, dvb_usb_lme2510_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info (or-able)).");

अटल पूर्णांक dvb_usb_lme2510_firmware;
module_param_named(firmware, dvb_usb_lme2510_firmware, पूर्णांक, 0644);
MODULE_PARM_DESC(firmware, "set default firmware 0=Sharp7395 1=LG");

अटल पूर्णांक pid_filter;
module_param_named(pid, pid_filter, पूर्णांक, 0644);
MODULE_PARM_DESC(pid, "set default 0=default 1=off 2=on");


DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा TUNER_DEFAULT	0x0
#घोषणा TUNER_LG	0x1
#घोषणा TUNER_S7395	0x2
#घोषणा TUNER_S0194	0x3
#घोषणा TUNER_RS2000	0x4

काष्ठा lme2510_state अणु
	अचिन्हित दीर्घ पूर्णांक_urb_due;
	क्रमागत fe_status lock_status;
	u8 id;
	u8 tuner_config;
	u8 संकेत_level;
	u8 संकेत_sn;
	u8 समय_key;
	u8 i2c_talk_onoff;
	u8 i2c_gate;
	u8 i2c_tuner_gate_w;
	u8 i2c_tuner_gate_r;
	u8 i2c_tuner_addr;
	u8 stream_on;
	u8 pid_size;
	u8 pid_off;
	u8 पूर्णांक_buffer[128];
	काष्ठा urb *lme_urb;
	u8 usb_buffer[64];
	/* Frontend original calls */
	पूर्णांक (*fe_पढ़ो_status)(काष्ठा dvb_frontend *, क्रमागत fe_status *);
	पूर्णांक (*fe_पढ़ो_संकेत_strength)(काष्ठा dvb_frontend *, u16 *);
	पूर्णांक (*fe_पढ़ो_snr)(काष्ठा dvb_frontend *, u16 *);
	पूर्णांक (*fe_पढ़ो_ber)(काष्ठा dvb_frontend *, u32 *);
	पूर्णांक (*fe_पढ़ो_ucblocks)(काष्ठा dvb_frontend *, u32 *);
	पूर्णांक (*fe_set_voltage)(काष्ठा dvb_frontend *, क्रमागत fe_sec_voltage);
	u8 dvb_usb_lme2510_firmware;
पूर्ण;

अटल पूर्णांक lme2510_usb_talk(काष्ठा dvb_usb_device *d,
			    u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen)
अणु
	काष्ठा lme2510_state *st = d->priv;
	पूर्णांक ret = 0;

	अगर (max(wlen, rlen) > माप(st->usb_buffer))
		वापस -EINVAL;

	ret = mutex_lock_पूर्णांकerruptible(&d->usb_mutex);
	अगर (ret < 0)
		वापस -EAGAIN;

	स_नकल(st->usb_buffer, wbuf, wlen);

	ret = dvb_usbv2_generic_rw_locked(d, st->usb_buffer, wlen,
					  st->usb_buffer, rlen);

	अगर (rlen)
		स_नकल(rbuf, st->usb_buffer, rlen);

	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक lme2510_stream_restart(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा lme2510_state *st = d->priv;
	u8 all_pids[] = LME_ALL_PIDS;
	u8 stream_on[] = LME_ST_ON_W;
	u8 rbuff[1];
	अगर (st->pid_off)
		lme2510_usb_talk(d, all_pids, माप(all_pids),
				 rbuff, माप(rbuff));
	/*Restart Stream Command*/
	वापस lme2510_usb_talk(d, stream_on, माप(stream_on),
				rbuff, माप(rbuff));
पूर्ण

अटल पूर्णांक lme2510_enable_pid(काष्ठा dvb_usb_device *d, u8 index, u16 pid_out)
अणु
	काष्ठा lme2510_state *st = d->priv;
	अटल u8 pid_buff[] = LME_ZERO_PID;
	अटल u8 rbuf[1];
	u8 pid_no = index * 2;
	u8 pid_len = pid_no + 2;
	पूर्णांक ret = 0;
	deb_info(1, "PID Setting Pid %04x", pid_out);

	अगर (st->pid_size == 0)
		ret |= lme2510_stream_restart(d);

	pid_buff[2] = pid_no;
	pid_buff[3] = (u8)pid_out & 0xff;
	pid_buff[4] = pid_no + 1;
	pid_buff[5] = (u8)(pid_out >> 8);

	अगर (pid_len > st->pid_size)
		st->pid_size = pid_len;
	pid_buff[7] = 0x80 + st->pid_size;

	ret |= lme2510_usb_talk(d, pid_buff ,
		माप(pid_buff) , rbuf, माप(rbuf));

	अगर (st->stream_on)
		ret |= lme2510_stream_restart(d);

	वापस ret;
पूर्ण

/* Convert range from 0x00-0xff to 0x0000-0xffff */
#घोषणा reg_to_16bits(x)	((x) | ((x) << 8))

अटल व्योम lme2510_update_stats(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा lme2510_state *st = adap_to_priv(adap);
	काष्ठा dvb_frontend *fe = adap->fe[0];
	काष्ठा dtv_frontend_properties *c;
	u32 s_पंचांगp = 0, c_पंचांगp = 0;

	अगर (!fe)
		वापस;

	c = &fe->dtv_property_cache;

	c->block_count.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	अगर (st->i2c_talk_onoff) अणु
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस;
	पूर्ण

	चयन (st->tuner_config) अणु
	हाल TUNER_LG:
		s_पंचांगp = reg_to_16bits(0xff - st->संकेत_level);
		c_पंचांगp = reg_to_16bits(0xff - st->संकेत_sn);
		अवरोध;
	हाल TUNER_S7395:
	हाल TUNER_S0194:
		s_पंचांगp = 0xffff - (((st->संकेत_level * 2) << 8) * 5 / 4);
		c_पंचांगp = reg_to_16bits((0xff - st->संकेत_sn - 0xa1) * 3);
		अवरोध;
	हाल TUNER_RS2000:
		s_पंचांगp = reg_to_16bits(st->संकेत_level);
		c_पंचांगp = reg_to_16bits(st->संकेत_sn);
	पूर्ण

	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_RELATIVE;
	c->strength.stat[0].uvalue = (u64)s_पंचांगp;

	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_RELATIVE;
	c->cnr.stat[0].uvalue = (u64)c_पंचांगp;
पूर्ण

अटल व्योम lme2510_पूर्णांक_response(काष्ठा urb *lme_urb)
अणु
	काष्ठा dvb_usb_adapter *adap = lme_urb->context;
	काष्ठा lme2510_state *st = adap_to_priv(adap);
	u8 *ibuf, *rbuf;
	पूर्णांक i = 0, offset;
	u32 key;
	u8 संकेत_lock = 0;

	चयन (lme_urb->status) अणु
	हाल 0:
	हाल -ETIMEDOUT:
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:
		info("Error %x", lme_urb->status);
		अवरोध;
	पूर्ण

	rbuf = (u8 *) lme_urb->transfer_buffer;

	offset = ((lme_urb->actual_length/8) > 4)
			? 4 : (lme_urb->actual_length/8) ;

	क्रम (i = 0; i < offset; ++i) अणु
		ibuf = (u8 *)&rbuf[i*8];
		deb_info(5, "INT O/S C =%02x C/O=%02x Type =%02x%02x",
		offset, i, ibuf[0], ibuf[1]);

		चयन (ibuf[0]) अणु
		हाल 0xaa:
			debug_data_snipet(1, "INT Remote data snippet", ibuf);
			अगर (!adap_to_d(adap)->rc_dev)
				अवरोध;

			key = RC_SCANCODE_NEC32(ibuf[2] << 24 |
						ibuf[3] << 16 |
						ibuf[4] << 8  |
						ibuf[5]);

			deb_info(1, "INT Key = 0x%08x", key);
			rc_keyकरोwn(adap_to_d(adap)->rc_dev, RC_PROTO_NEC32, key,
				   0);
			अवरोध;
		हाल 0xbb:
			चयन (st->tuner_config) अणु
			हाल TUNER_LG:
				संकेत_lock = ibuf[2] & BIT(5);
				st->संकेत_level = ibuf[4];
				st->संकेत_sn = ibuf[3];
				st->समय_key = ibuf[7];
				अवरोध;
			हाल TUNER_S7395:
			हाल TUNER_S0194:
				/* Tweak क्रम earlier firmware*/
				अगर (ibuf[1] == 0x03) अणु
					संकेत_lock = ibuf[2] & BIT(4);
					st->संकेत_level = ibuf[3];
					st->संकेत_sn = ibuf[4];
				पूर्ण अन्यथा अणु
					st->संकेत_level = ibuf[4];
					st->संकेत_sn = ibuf[5];
				पूर्ण
				अवरोध;
			हाल TUNER_RS2000:
				संकेत_lock = ibuf[2] & 0xee;
				st->संकेत_level = ibuf[5];
				st->संकेत_sn = ibuf[4];
				st->समय_key = ibuf[7];
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			/* Interrupt will also throw just BIT 0 as lock */
			संकेत_lock |= ibuf[2] & BIT(0);

			अगर (!संकेत_lock)
				st->lock_status &= ~FE_HAS_LOCK;

			lme2510_update_stats(adap);

			debug_data_snipet(5, "INT Remote data snippet in", ibuf);
		अवरोध;
		हाल 0xcc:
			debug_data_snipet(1, "INT Control data snippet", ibuf);
			अवरोध;
		शेष:
			debug_data_snipet(1, "INT Unknown data snippet", ibuf);
		अवरोध;
		पूर्ण
	पूर्ण

	usb_submit_urb(lme_urb, GFP_ATOMIC);

	/* Interrupt urb is due every 48 msecs जबतक streaming the buffer
	 * stores up to 4 periods अगर missed. Allow 200 msec क्रम next पूर्णांकerrupt.
	 */
	st->पूर्णांक_urb_due = jअगरfies + msecs_to_jअगरfies(200);
पूर्ण

अटल पूर्णांक lme2510_पूर्णांक_पढ़ो(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा lme2510_state *lme_पूर्णांक = adap_to_priv(adap);
	काष्ठा usb_host_endpoपूर्णांक *ep;

	lme_पूर्णांक->lme_urb = usb_alloc_urb(0, GFP_KERNEL);

	अगर (lme_पूर्णांक->lme_urb == शून्य)
			वापस -ENOMEM;

	usb_fill_पूर्णांक_urb(lme_पूर्णांक->lme_urb,
			 d->udev,
			 usb_rcvपूर्णांकpipe(d->udev, 0xa),
			 lme_पूर्णांक->पूर्णांक_buffer,
			 माप(lme_पूर्णांक->पूर्णांक_buffer),
			 lme2510_पूर्णांक_response,
			 adap,
			 8);

	/* Quirk of pipe reporting PIPE_BULK but behaves as पूर्णांकerrupt */
	ep = usb_pipe_endpoपूर्णांक(d->udev, lme_पूर्णांक->lme_urb->pipe);

	अगर (usb_endpoपूर्णांक_type(&ep->desc) == USB_ENDPOINT_XFER_BULK)
		lme_पूर्णांक->lme_urb->pipe = usb_rcvbulkpipe(d->udev, 0xa);

	usb_submit_urb(lme_पूर्णांक->lme_urb, GFP_KERNEL);
	info("INT Interrupt Service Started");

	वापस 0;
पूर्ण

अटल पूर्णांक lme2510_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा lme2510_state *st = adap_to_priv(adap);
	अटल u8 clear_pid_reg[] = LME_ALL_PIDS;
	अटल u8 rbuf[1];
	पूर्णांक ret = 0;

	deb_info(1, "PID Clearing Filter");

	mutex_lock(&d->i2c_mutex);

	अगर (!onoff) अणु
		ret |= lme2510_usb_talk(d, clear_pid_reg,
			माप(clear_pid_reg), rbuf, माप(rbuf));
		st->pid_off = true;
	पूर्ण अन्यथा
		st->pid_off = false;

	st->pid_size = 0;

	mutex_unlock(&d->i2c_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक lme2510_pid_filter(काष्ठा dvb_usb_adapter *adap, पूर्णांक index, u16 pid,
	पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	पूर्णांक ret = 0;

	deb_info(3, "%s PID=%04x Index=%04x onoff=%02x", __func__,
		pid, index, onoff);

	अगर (onoff) अणु
		mutex_lock(&d->i2c_mutex);
		ret |= lme2510_enable_pid(d, index, pid);
		mutex_unlock(&d->i2c_mutex);
	पूर्ण


	वापस ret;
पूर्ण


अटल पूर्णांक lme2510_वापस_status(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret;
	u8 *data;

	data = kzalloc(6, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0),
			      0x06, 0x80, 0x0302, 0x00,
			      data, 0x6, 200);
	अगर (ret != 6)
		ret = -EINVAL;
	अन्यथा
		ret = data[2];

	info("Firmware Status: %6ph", data);

	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक lme2510_msg(काष्ठा dvb_usb_device *d,
		u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen)
अणु
	काष्ठा lme2510_state *st = d->priv;

	st->i2c_talk_onoff = 1;

	वापस lme2510_usb_talk(d, wbuf, wlen, rbuf, rlen);
पूर्ण

अटल पूर्णांक lme2510_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
				 पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	काष्ठा lme2510_state *st = d->priv;
	अटल u8 obuf[64], ibuf[64];
	पूर्णांक i, पढ़ो, पढ़ो_o;
	u16 len;
	u8 gate;

	mutex_lock(&d->i2c_mutex);

	क्रम (i = 0; i < num; i++) अणु
		पढ़ो_o = msg[i].flags & I2C_M_RD;
		पढ़ो = i + 1 < num && msg[i + 1].flags & I2C_M_RD;
		पढ़ो |= पढ़ो_o;
		gate = (msg[i].addr == st->i2c_tuner_addr)
			? (पढ़ो)	? st->i2c_tuner_gate_r
					: st->i2c_tuner_gate_w
			: st->i2c_gate;
		obuf[0] = gate | (पढ़ो << 7);

		अगर (gate == 5)
			obuf[1] = (पढ़ो) ? 2 : msg[i].len + 1;
		अन्यथा
			obuf[1] = msg[i].len + पढ़ो + 1;

		obuf[2] = msg[i].addr << 1;

		अगर (पढ़ो) अणु
			अगर (पढ़ो_o)
				len = 3;
			अन्यथा अणु
				स_नकल(&obuf[3], msg[i].buf, msg[i].len);
				obuf[msg[i].len+3] = msg[i+1].len;
				len = msg[i].len+4;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(&obuf[3], msg[i].buf, msg[i].len);
			len = msg[i].len+3;
		पूर्ण

		अगर (lme2510_msg(d, obuf, len, ibuf, 64) < 0) अणु
			deb_info(1, "i2c transfer failed.");
			mutex_unlock(&d->i2c_mutex);
			वापस -EAGAIN;
		पूर्ण

		अगर (पढ़ो) अणु
			अगर (पढ़ो_o)
				स_नकल(msg[i].buf, &ibuf[1], msg[i].len);
			अन्यथा अणु
				स_नकल(msg[i+1].buf, &ibuf[1], msg[i+1].len);
				i++;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस i;
पूर्ण

अटल u32 lme2510_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm lme2510_i2c_algo = अणु
	.master_xfer   = lme2510_i2c_xfer,
	.functionality = lme2510_i2c_func,
पूर्ण;

अटल पूर्णांक lme2510_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_adapter *adap = fe_to_adap(fe);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा lme2510_state *st = adap_to_priv(adap);
	अटल u8 clear_reg_3[] = LME_ALL_PIDS;
	अटल u8 rbuf[1];
	पूर्णांक ret = 0, rlen = माप(rbuf);

	deb_info(1, "STM  (%02x)", onoff);

	/* Streaming is started by FE_HAS_LOCK */
	अगर (onoff == 1)
		st->stream_on = 1;
	अन्यथा अणु
		deb_info(1, "STM Steam Off");
		/* mutex is here only to aव्योम collision with I2C */
		mutex_lock(&d->i2c_mutex);

		ret = lme2510_usb_talk(d, clear_reg_3,
				माप(clear_reg_3), rbuf, rlen);
		st->stream_on = 0;
		st->i2c_talk_onoff = 1;

		mutex_unlock(&d->i2c_mutex);
	पूर्ण

	वापस (ret < 0) ? -ENODEV : 0;
पूर्ण

अटल u8 check_sum(u8 *p, u8 len)
अणु
	u8 sum = 0;
	जबतक (len--)
		sum += *p++;
	वापस sum;
पूर्ण

अटल पूर्णांक lme2510_करोwnload_firmware(काष्ठा dvb_usb_device *d,
					स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret = 0;
	u8 *data;
	u16 j, wlen, len_in, start, end;
	u8 packet_size, dlen, i;
	u8 *fw_data;

	packet_size = 0x31;
	len_in = 1;

	data = kzalloc(128, GFP_KERNEL);
	अगर (!data) अणु
		info("FRM Could not start Firmware Download"\
			"(Buffer allocation failed)");
		वापस -ENOMEM;
	पूर्ण

	info("FRM Starting Firmware Download");

	क्रम (i = 1; i < 3; i++) अणु
		start = (i == 1) ? 0 : 512;
		end = (i == 1) ? 512 : fw->size;
		क्रम (j = start; j < end; j += (packet_size+1)) अणु
			fw_data = (u8 *)(fw->data + j);
			अगर ((end - j) > packet_size) अणु
				data[0] = i;
				dlen = packet_size;
			पूर्ण अन्यथा अणु
				data[0] = i | 0x80;
				dlen = (u8)(end - j)-1;
			पूर्ण
			data[1] = dlen;
			स_नकल(&data[2], fw_data, dlen+1);
			wlen = (u8) dlen + 4;
			data[wlen-1] = check_sum(fw_data, dlen+1);
			deb_info(1, "Data S=%02x:E=%02x CS= %02x", data[3],
				data[dlen+2], data[dlen+3]);
			lme2510_usb_talk(d, data, wlen, data, len_in);
			ret |= (data[0] == 0x88) ? 0 : -1;
		पूर्ण
	पूर्ण

	data[0] = 0x8a;
	len_in = 1;
	msleep(2000);
	lme2510_usb_talk(d, data, len_in, data, len_in);
	msleep(400);

	अगर (ret < 0)
		info("FRM Firmware Download Failed (%04x)" , ret);
	अन्यथा
		info("FRM Firmware Download Completed - Resetting Device");

	kमुक्त(data);
	वापस RECONNECTS_USB;
पूर्ण

अटल व्योम lme_coldreset(काष्ठा dvb_usb_device *d)
अणु
	u8 data[1] = अणु0पूर्ण;
	data[0] = 0x0a;
	info("FRM Firmware Cold Reset");

	lme2510_usb_talk(d, data, माप(data), data, माप(data));

	वापस;
पूर्ण

अटल स्थिर अक्षर fw_c_s7395[] = LME2510_C_S7395;
अटल स्थिर अक्षर fw_c_lg[] = LME2510_C_LG;
अटल स्थिर अक्षर fw_c_s0194[] = LME2510_C_S0194;
अटल स्थिर अक्षर fw_c_rs2000[] = LME2510_C_RS2000;
अटल स्थिर अक्षर fw_lg[] = LME2510_LG;
अटल स्थिर अक्षर fw_s0194[] = LME2510_S0194;

अटल स्थिर अक्षर *lme_firmware_चयन(काष्ठा dvb_usb_device *d, पूर्णांक cold)
अणु
	काष्ठा lme2510_state *st = d->priv;
	काष्ठा usb_device *udev = d->udev;
	स्थिर काष्ठा firmware *fw = शून्य;
	स्थिर अक्षर *fw_lme;
	पूर्णांक ret = 0;

	cold = (cold > 0) ? (cold & 1) : 0;

	चयन (le16_to_cpu(udev->descriptor.idProduct)) अणु
	हाल 0x1122:
		चयन (st->dvb_usb_lme2510_firmware) अणु
		शेष:
		हाल TUNER_S0194:
			fw_lme = fw_s0194;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			अगर (ret == 0) अणु
				st->dvb_usb_lme2510_firmware = TUNER_S0194;
				cold = 0;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल TUNER_LG:
			fw_lme = fw_lg;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			अगर (ret == 0) अणु
				st->dvb_usb_lme2510_firmware = TUNER_LG;
				अवरोध;
			पूर्ण
			st->dvb_usb_lme2510_firmware = TUNER_DEFAULT;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x1120:
		चयन (st->dvb_usb_lme2510_firmware) अणु
		शेष:
		हाल TUNER_S7395:
			fw_lme = fw_c_s7395;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			अगर (ret == 0) अणु
				st->dvb_usb_lme2510_firmware = TUNER_S7395;
				cold = 0;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल TUNER_LG:
			fw_lme = fw_c_lg;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			अगर (ret == 0) अणु
				st->dvb_usb_lme2510_firmware = TUNER_LG;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल TUNER_S0194:
			fw_lme = fw_c_s0194;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			अगर (ret == 0) अणु
				st->dvb_usb_lme2510_firmware = TUNER_S0194;
				अवरोध;
			पूर्ण
			st->dvb_usb_lme2510_firmware = TUNER_DEFAULT;
			cold = 0;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x22f0:
		fw_lme = fw_c_rs2000;
		st->dvb_usb_lme2510_firmware = TUNER_RS2000;
		अवरोध;
	शेष:
		fw_lme = fw_c_s7395;
	पूर्ण

	release_firmware(fw);

	अगर (cold) अणु
		dvb_usb_lme2510_firmware = st->dvb_usb_lme2510_firmware;
		info("FRM Changing to %s firmware", fw_lme);
		lme_coldreset(d);
		वापस शून्य;
	पूर्ण

	वापस fw_lme;
पूर्ण

अटल काष्ठा tda10086_config tda10086_config = अणु
	.demod_address = 0x0e,
	.invert = 0,
	.diseqc_tone = 1,
	.xtal_freq = TDA10086_XTAL_16M,
पूर्ण;

अटल काष्ठा stv0288_config lme_config = अणु
	.demod_address = 0x68,
	.min_delay_ms = 15,
	.inittab = s7395_inittab,
पूर्ण;

अटल काष्ठा ix2505v_config lme_tuner = अणु
	.tuner_address = 0x60,
	.min_delay_ms = 100,
	.tuner_gain = 0x0,
	.tuner_अक्षरgepump = 0x3,
पूर्ण;

अटल काष्ठा stv0299_config sharp_z0194_config = अणु
	.demod_address = 0x68,
	.inittab = sharp_z0194a_inittab,
	.mclk = 88000000UL,
	.invert = 0,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_1,
	.volt13_op0_op1 = STV0299_VOLT13_OP1,
	.min_delay_ms = 100,
	.set_symbol_rate = sharp_z0194a_set_symbol_rate,
पूर्ण;

अटल काष्ठा m88rs2000_config m88rs2000_config = अणु
	.demod_addr = 0x68
पूर्ण;

अटल काष्ठा ts2020_config ts2020_config = अणु
	.tuner_address = 0x60,
	.clk_out_भाग = 7,
	.करोnt_poll = true
पूर्ण;

अटल पूर्णांक dm04_lme2510_set_voltage(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा lme2510_state *st = fe_to_priv(fe);
	अटल u8 voltage_low[] = LME_VOLTAGE_L;
	अटल u8 voltage_high[] = LME_VOLTAGE_H;
	अटल u8 rbuf[1];
	पूर्णांक ret = 0, len = 3, rlen = 1;

	mutex_lock(&d->i2c_mutex);

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_18:
		ret |= lme2510_usb_talk(d,
			voltage_high, len, rbuf, rlen);
		अवरोध;

	हाल SEC_VOLTAGE_OFF:
	हाल SEC_VOLTAGE_13:
	शेष:
		ret |= lme2510_usb_talk(d,
				voltage_low, len, rbuf, rlen);
		अवरोध;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);

	अगर (st->tuner_config == TUNER_RS2000)
		अगर (st->fe_set_voltage)
			st->fe_set_voltage(fe, voltage);


	वापस (ret < 0) ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक dm04_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा lme2510_state *st = d->priv;
	पूर्णांक ret = 0;

	अगर (st->i2c_talk_onoff) अणु
		अगर (st->fe_पढ़ो_status) अणु
			ret = st->fe_पढ़ो_status(fe, status);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		st->lock_status = *status;

		अगर (*status & FE_HAS_LOCK && st->stream_on) अणु
			mutex_lock(&d->i2c_mutex);

			st->i2c_talk_onoff = 0;
			ret = lme2510_stream_restart(d);

			mutex_unlock(&d->i2c_mutex);
		पूर्ण

		वापस ret;
	पूर्ण

	/* Timeout of पूर्णांकerrupt reached on RS2000 */
	अगर (st->tuner_config == TUNER_RS2000 &&
	    समय_after(jअगरfies, st->पूर्णांक_urb_due))
		st->lock_status &= ~FE_HAS_LOCK;

	*status = st->lock_status;

	अगर (!(*status & FE_HAS_LOCK)) अणु
		काष्ठा dvb_usb_adapter *adap = fe_to_adap(fe);

		st->i2c_talk_onoff = 1;

		lme2510_update_stats(adap);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dm04_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा lme2510_state *st = fe_to_priv(fe);

	अगर (st->fe_पढ़ो_संकेत_strength && !st->stream_on)
		वापस st->fe_पढ़ो_संकेत_strength(fe, strength);

	अगर (c->strength.stat[0].scale == FE_SCALE_RELATIVE)
		*strength = (u16)c->strength.stat[0].uvalue;
	अन्यथा
		*strength = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक dm04_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा lme2510_state *st = fe_to_priv(fe);

	अगर (st->fe_पढ़ो_snr && !st->stream_on)
		वापस st->fe_पढ़ो_snr(fe, snr);

	अगर (c->cnr.stat[0].scale == FE_SCALE_RELATIVE)
		*snr = (u16)c->cnr.stat[0].uvalue;
	अन्यथा
		*snr = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक dm04_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा lme2510_state *st = fe_to_priv(fe);

	अगर (st->fe_पढ़ो_ber && !st->stream_on)
		वापस st->fe_पढ़ो_ber(fe, ber);

	*ber = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक dm04_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा lme2510_state *st = fe_to_priv(fe);

	अगर (st->fe_पढ़ो_ucblocks && !st->stream_on)
		वापस st->fe_पढ़ो_ucblocks(fe, ucblocks);

	*ucblocks = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक lme_name(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा lme2510_state *st = adap_to_priv(adap);
	स्थिर अक्षर *desc = d->name;
	अटल स्थिर अक्षर * स्थिर fe_name[] = अणु
		"", " LG TDQY-P001F", " SHARP:BS2F7HZ7395",
		" SHARP:BS2F7HZ0194", " RS2000"पूर्ण;
	अक्षर *name = adap->fe[0]->ops.info.name;

	strscpy(name, desc, 128);
	strlcat(name, fe_name[st->tuner_config], 128);

	वापस 0;
पूर्ण

अटल पूर्णांक dm04_lme2510_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा lme2510_state *st = d->priv;
	पूर्णांक ret = 0;

	st->i2c_talk_onoff = 1;
	चयन (le16_to_cpu(d->udev->descriptor.idProduct)) अणु
	हाल 0x1122:
	हाल 0x1120:
		st->i2c_gate = 4;
		adap->fe[0] = dvb_attach(tda10086_attach,
			&tda10086_config, &d->i2c_adap);
		अगर (adap->fe[0]) अणु
			info("TUN Found Frontend TDA10086");
			st->i2c_tuner_gate_w = 4;
			st->i2c_tuner_gate_r = 4;
			st->i2c_tuner_addr = 0x60;
			st->tuner_config = TUNER_LG;
			अगर (st->dvb_usb_lme2510_firmware != TUNER_LG) अणु
				st->dvb_usb_lme2510_firmware = TUNER_LG;
				ret = lme_firmware_चयन(d, 1) ? 0 : -ENODEV;
			पूर्ण
			अवरोध;
		पूर्ण

		st->i2c_gate = 4;
		adap->fe[0] = dvb_attach(stv0299_attach,
				&sharp_z0194_config, &d->i2c_adap);
		अगर (adap->fe[0]) अणु
			info("FE Found Stv0299");
			st->i2c_tuner_gate_w = 4;
			st->i2c_tuner_gate_r = 5;
			st->i2c_tuner_addr = 0x60;
			st->tuner_config = TUNER_S0194;
			अगर (st->dvb_usb_lme2510_firmware != TUNER_S0194) अणु
				st->dvb_usb_lme2510_firmware = TUNER_S0194;
				ret = lme_firmware_चयन(d, 1) ? 0 : -ENODEV;
			पूर्ण
			अवरोध;
		पूर्ण

		st->i2c_gate = 5;
		adap->fe[0] = dvb_attach(stv0288_attach, &lme_config,
			&d->i2c_adap);

		अगर (adap->fe[0]) अणु
			info("FE Found Stv0288");
			st->i2c_tuner_gate_w = 4;
			st->i2c_tuner_gate_r = 5;
			st->i2c_tuner_addr = 0x60;
			st->tuner_config = TUNER_S7395;
			अगर (st->dvb_usb_lme2510_firmware != TUNER_S7395) अणु
				st->dvb_usb_lme2510_firmware = TUNER_S7395;
				ret = lme_firmware_चयन(d, 1) ? 0 : -ENODEV;
			पूर्ण
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 0x22f0:
		st->i2c_gate = 5;
		adap->fe[0] = dvb_attach(m88rs2000_attach,
			&m88rs2000_config, &d->i2c_adap);

		अगर (adap->fe[0]) अणु
			info("FE Found M88RS2000");
			st->i2c_tuner_gate_w = 5;
			st->i2c_tuner_gate_r = 5;
			st->i2c_tuner_addr = 0x60;
			st->tuner_config = TUNER_RS2000;
			st->fe_set_voltage =
				adap->fe[0]->ops.set_voltage;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (adap->fe[0] == शून्य) अणु
		info("DM04/QQBOX Not Powered up or not Supported");
		वापस -ENODEV;
	पूर्ण

	अगर (ret) अणु
		अगर (adap->fe[0]) अणु
			dvb_frontend_detach(adap->fe[0]);
			adap->fe[0] = शून्य;
		पूर्ण
		d->rc_map = शून्य;
		वापस -ENODEV;
	पूर्ण

	st->fe_पढ़ो_status = adap->fe[0]->ops.पढ़ो_status;
	st->fe_पढ़ो_संकेत_strength = adap->fe[0]->ops.पढ़ो_संकेत_strength;
	st->fe_पढ़ो_snr = adap->fe[0]->ops.पढ़ो_snr;
	st->fe_पढ़ो_ber = adap->fe[0]->ops.पढ़ो_ber;
	st->fe_पढ़ो_ucblocks = adap->fe[0]->ops.पढ़ो_ucblocks;

	adap->fe[0]->ops.पढ़ो_status = dm04_पढ़ो_status;
	adap->fe[0]->ops.पढ़ो_संकेत_strength = dm04_पढ़ो_संकेत_strength;
	adap->fe[0]->ops.पढ़ो_snr = dm04_पढ़ो_snr;
	adap->fe[0]->ops.पढ़ो_ber = dm04_पढ़ो_ber;
	adap->fe[0]->ops.पढ़ो_ucblocks = dm04_पढ़ो_ucblocks;
	adap->fe[0]->ops.set_voltage = dm04_lme2510_set_voltage;

	ret = lme_name(adap);
	वापस ret;
पूर्ण

अटल पूर्णांक dm04_lme2510_tuner(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा lme2510_state *st = adap_to_priv(adap);
	अटल स्थिर अक्षर * स्थिर tun_msg[] = अणु"", "TDA8263", "IX2505V", "DVB_PLL_OPERA", "RS2000"पूर्ण;
	पूर्णांक ret = 0;

	चयन (st->tuner_config) अणु
	हाल TUNER_LG:
		अगर (dvb_attach(tda826x_attach, adap->fe[0], 0x60,
			&d->i2c_adap, 1))
			ret = st->tuner_config;
		अवरोध;
	हाल TUNER_S7395:
		अगर (dvb_attach(ix2505v_attach , adap->fe[0], &lme_tuner,
			&d->i2c_adap))
			ret = st->tuner_config;
		अवरोध;
	हाल TUNER_S0194:
		अगर (dvb_attach(dvb_pll_attach , adap->fe[0], 0x60,
			&d->i2c_adap, DVB_PLL_OPERA1))
			ret = st->tuner_config;
		अवरोध;
	हाल TUNER_RS2000:
		अगर (dvb_attach(ts2020_attach, adap->fe[0],
			       &ts2020_config, &d->i2c_adap))
			ret = st->tuner_config;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		info("TUN Found %s tuner", tun_msg[ret]);
	पूर्ण अन्यथा अणु
		info("TUN No tuner found");
		वापस -ENODEV;
	पूर्ण

	/* Start the Interrupt*/
	ret = lme2510_पूर्णांक_पढ़ो(adap);
	अगर (ret < 0) अणु
		info("INT Unable to start Interrupt Service");
		वापस -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lme2510_घातerup(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	काष्ठा lme2510_state *st = d->priv;
	अटल u8 lnb_on[] = LNB_ON;
	अटल u8 lnb_off[] = LNB_OFF;
	अटल u8 rbuf[1];
	पूर्णांक ret = 0, len = 3, rlen = 1;

	mutex_lock(&d->i2c_mutex);

	ret = lme2510_usb_talk(d, onoff ? lnb_on : lnb_off, len, rbuf, rlen);

	st->i2c_talk_onoff = 1;

	mutex_unlock(&d->i2c_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक lme2510_get_adapter_count(काष्ठा dvb_usb_device *d)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक lme2510_identअगरy_state(काष्ठा dvb_usb_device *d, स्थिर अक्षर **name)
अणु
	काष्ठा lme2510_state *st = d->priv;
	पूर्णांक status;

	usb_reset_configuration(d->udev);

	usb_set_पूर्णांकerface(d->udev,
		d->props->bInterfaceNumber, 1);

	st->dvb_usb_lme2510_firmware = dvb_usb_lme2510_firmware;

	status = lme2510_वापस_status(d);
	अगर (status == 0x44) अणु
		*name = lme_firmware_चयन(d, 0);
		वापस COLD;
	पूर्ण

	अगर (status != 0x47)
		वापस -EINVAL;

	वापस WARM;
पूर्ण

अटल पूर्णांक lme2510_get_stream_config(काष्ठा dvb_frontend *fe, u8 *ts_type,
		काष्ठा usb_data_stream_properties *stream)
अणु
	काष्ठा dvb_usb_adapter *adap = fe_to_adap(fe);
	काष्ठा dvb_usb_device *d;

	अगर (adap == शून्य)
		वापस 0;

	d = adap_to_d(adap);

	/* Turn PID filter on the fly by module option */
	अगर (pid_filter == 2) अणु
		adap->pid_filtering  = true;
		adap->max_feed_count = 15;
	पूर्ण

	अगर (!(le16_to_cpu(d->udev->descriptor.idProduct)
		== 0x1122))
		stream->endpoपूर्णांक = 0x8;

	वापस 0;
पूर्ण

अटल पूर्णांक lme2510_get_rc_config(काष्ठा dvb_usb_device *d,
	काष्ठा dvb_usb_rc *rc)
अणु
	rc->allowed_protos = RC_PROTO_BIT_NEC32;
	वापस 0;
पूर्ण

अटल व्योम lme2510_निकास(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा lme2510_state *st = d->priv;

	अगर (st->lme_urb) अणु
		usb_समाप्त_urb(st->lme_urb);
		usb_मुक्त_urb(st->lme_urb);
		info("Interrupt Service Stopped");
	पूर्ण
पूर्ण

अटल काष्ठा dvb_usb_device_properties lme2510_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.bInterfaceNumber = 0,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा lme2510_state),
	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x01,

	.करोwnload_firmware = lme2510_करोwnload_firmware,

	.घातer_ctrl       = lme2510_घातerup,
	.identअगरy_state   = lme2510_identअगरy_state,
	.i2c_algo         = &lme2510_i2c_algo,

	.frontend_attach  = dm04_lme2510_frontend_attach,
	.tuner_attach = dm04_lme2510_tuner,
	.get_stream_config = lme2510_get_stream_config,
	.get_adapter_count = lme2510_get_adapter_count,
	.streaming_ctrl   = lme2510_streaming_ctrl,

	.get_rc_config = lme2510_get_rc_config,

	.निकास = lme2510_निकास,
	.adapter = अणु
		अणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER|
				DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
			.pid_filter_count = 15,
			.pid_filter = lme2510_pid_filter,
			.pid_filter_ctrl  = lme2510_pid_filter_ctrl,
			.stream =
			DVB_USB_STREAM_BULK(0x86, 10, 4096),
		पूर्ण,
		अणु
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id lme2510_id_table[] = अणु
	अणु	DVB_USB_DEVICE(0x3344, 0x1122, &lme2510_props,
		"DM04_LME2510_DVB-S", RC_MAP_LME2510)	पूर्ण,
	अणु	DVB_USB_DEVICE(0x3344, 0x1120, &lme2510_props,
		"DM04_LME2510C_DVB-S", RC_MAP_LME2510)	पूर्ण,
	अणु	DVB_USB_DEVICE(0x3344, 0x22f0, &lme2510_props,
		"DM04_LME2510C_DVB-S RS2000", RC_MAP_LME2510)	पूर्ण,
	अणुपूर्ण		/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, lme2510_id_table);

अटल काष्ठा usb_driver lme2510_driver = अणु
	.name		= KBUILD_MODNAME,
	.probe		= dvb_usbv2_probe,
	.disconnect	= dvb_usbv2_disconnect,
	.id_table	= lme2510_id_table,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(lme2510_driver);

MODULE_AUTHOR("Malcolm Priestley <tvboxspy@gmail.com>");
MODULE_DESCRIPTION("LME2510(C) DVB-S USB2.0");
MODULE_VERSION("2.07");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(LME2510_C_S7395);
MODULE_FIRMWARE(LME2510_C_LG);
MODULE_FIRMWARE(LME2510_C_S0194);
MODULE_FIRMWARE(LME2510_C_RS2000);
MODULE_FIRMWARE(LME2510_LG);
MODULE_FIRMWARE(LME2510_S0194);

