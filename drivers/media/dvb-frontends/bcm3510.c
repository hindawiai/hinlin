<शैली गुरु>
/*
 * Support क्रम the Broadcom BCM3510 ATSC demodulator (1st generation Air2PC)
 *
 *  Copyright (C) 2001-5, B2C2 inc.
 *
 *  GPL/Linux driver written by Patrick Boettcher <patrick.boettcher@posteo.de>
 *
 *  This driver is "hard-coded" to be used with the 1st generation of
 *  Technisat/B2C2's Air2PC ATSC PCI/USB cards/boxes. The pll-programming
 *  (Panasonic CT10S) is located here, which is actually wrong. Unless there is
 *  another device with a BCM3510, this is no problem.
 *
 *  The driver works also with QAM64 DVB-C, but had an unreasonable high
 *  UNC. (Tested with the Air2PC ATSC 1st generation)
 *
 *  You'll need a firmware क्रम this driver in order to get it running. It is
 *  called "dvb-fe-bcm3510-01.fw".
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program; अगर not, ग_लिखो to the Free Software Foundation, Inc., 675 Mass
 * Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश <media/dvb_frontend.h>
#समावेश "bcm3510.h"
#समावेश "bcm3510_priv.h"

/* Max transfer size करोne by bcm3510_करो_hab_cmd() function */
#घोषणा MAX_XFER_SIZE	128

काष्ठा bcm3510_state अणु

	काष्ठा i2c_adapter* i2c;
	स्थिर काष्ठा bcm3510_config* config;
	काष्ठा dvb_frontend frontend;

	/* demodulator निजी data */
	काष्ठा mutex hab_mutex;
	u8 firmware_loaded:1;

	अचिन्हित दीर्घ next_status_check;
	अचिन्हित दीर्घ status_check_पूर्णांकerval;
	काष्ठा bcm3510_hab_cmd_status1 status1;
	काष्ठा bcm3510_hab_cmd_status2 status2;
पूर्ण;

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,2=i2c (|-able)).");

#घोषणा dprपूर्णांकk(level,x...) अगर (level & debug) prपूर्णांकk(x)
#घोषणा dbufout(b,l,m) अणु\
	    पूर्णांक i; \
	    क्रम (i = 0; i < l; i++) \
		m("%02x ",b[i]); \
पूर्ण
#घोषणा deb_info(args...) dprपूर्णांकk(0x01,args)
#घोषणा deb_i2c(args...)  dprपूर्णांकk(0x02,args)
#घोषणा deb_hab(args...)  dprपूर्णांकk(0x04,args)

/* transfer functions */
अटल पूर्णांक bcm3510_ग_लिखोbytes (काष्ठा bcm3510_state *state, u8 reg, u8 *buf, u8 len)
अणु
	u8 b[256];
	पूर्णांक err;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = b, .len = len + 1 पूर्ण;

	b[0] = reg;
	स_नकल(&b[1],buf,len);

	deb_i2c("i2c wr %02x: ",reg);
	dbufout(buf,len,deb_i2c);
	deb_i2c("\n");

	अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु

		deb_info("%s: i2c write error (addr %02x, reg %02x, err == %i)\n",
			__func__, state->config->demod_address, reg,  err);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_पढ़ोbytes (काष्ठा bcm3510_state *state, u8 reg, u8 *buf, u8 len)
अणु
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->config->demod_address, .flags = 0,        .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = buf,  .len = len पूर्ण
	पूर्ण;
	पूर्णांक err;

	स_रखो(buf,0,len);

	अगर ((err = i2c_transfer (state->i2c, msg, 2)) != 2) अणु
		deb_info("%s: i2c read error (addr %02x, reg %02x, err == %i)\n",
			__func__, state->config->demod_address, reg,  err);
		वापस -EREMOTEIO;
	पूर्ण
	deb_i2c("i2c rd %02x: ",reg);
	dbufout(buf,len,deb_i2c);
	deb_i2c("\n");

	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_ग_लिखोB(काष्ठा bcm3510_state *state, u8 reg, bcm3510_रेजिस्टर_value v)
अणु
	वापस bcm3510_ग_लिखोbytes(state,reg,&v.raw,1);
पूर्ण

अटल पूर्णांक bcm3510_पढ़ोB(काष्ठा bcm3510_state *state, u8 reg, bcm3510_रेजिस्टर_value *v)
अणु
	वापस bcm3510_पढ़ोbytes(state,reg,&v->raw,1);
पूर्ण

/* Host Access Buffer transfers */
अटल पूर्णांक bcm3510_hab_get_response(काष्ठा bcm3510_state *st, u8 *buf, पूर्णांक len)
अणु
	bcm3510_रेजिस्टर_value v;
	पूर्णांक ret,i;

	v.HABADR_a6.HABADR = 0;
	अगर ((ret = bcm3510_ग_लिखोB(st,0xa6,v)) < 0)
		वापस ret;

	क्रम (i = 0; i < len; i++) अणु
		अगर ((ret = bcm3510_पढ़ोB(st,0xa7,&v)) < 0)
			वापस ret;
		buf[i] = v.HABDATA_a7;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_hab_send_request(काष्ठा bcm3510_state *st, u8 *buf, पूर्णांक len)
अणु
	bcm3510_रेजिस्टर_value v,hab;
	पूर्णांक ret,i;
	अचिन्हित दीर्घ t;

/* Check अगर any previous HAB request still needs to be serviced by the
 * Acquisition Processor beक्रमe sending new request */
	अगर ((ret = bcm3510_पढ़ोB(st,0xa8,&v)) < 0)
		वापस ret;
	अगर (v.HABSTAT_a8.HABR) अणु
		deb_info("HAB is running already - clearing it.\n");
		v.HABSTAT_a8.HABR = 0;
		bcm3510_ग_लिखोB(st,0xa8,v);
//		वापस -EBUSY;
	पूर्ण

/* Send the start HAB Address (स्वतःmatically incremented after ग_लिखो of
 * HABDATA) and ग_लिखो the HAB Data */
	hab.HABADR_a6.HABADR = 0;
	अगर ((ret = bcm3510_ग_लिखोB(st,0xa6,hab)) < 0)
		वापस ret;

	क्रम (i = 0; i < len; i++) अणु
		hab.HABDATA_a7 = buf[i];
		अगर ((ret = bcm3510_ग_लिखोB(st,0xa7,hab)) < 0)
			वापस ret;
	पूर्ण

/* Set the HABR bit to indicate AP request in progress (LBHABR allows HABR to
 * be written) */
	v.raw = 0; v.HABSTAT_a8.HABR = 1; v.HABSTAT_a8.LDHABR = 1;
	अगर ((ret = bcm3510_ग_लिखोB(st,0xa8,v)) < 0)
		वापस ret;

/* Polling method: Wait until the AP finishes processing the HAB request */
	t = jअगरfies + 1*HZ;
	जबतक (समय_beक्रमe(jअगरfies, t)) अणु
		deb_info("waiting for HAB to complete\n");
		msleep(10);
		अगर ((ret = bcm3510_पढ़ोB(st,0xa8,&v)) < 0)
			वापस ret;

		अगर (!v.HABSTAT_a8.HABR)
			वापस 0;
	पूर्ण

	deb_info("send_request execution timed out.\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक bcm3510_करो_hab_cmd(काष्ठा bcm3510_state *st, u8 cmd, u8 msgid, u8 *obuf, u8 olen, u8 *ibuf, u8 ilen)
अणु
	u8 ob[MAX_XFER_SIZE], ib[MAX_XFER_SIZE];
	पूर्णांक ret = 0;

	अगर (ilen + 2 > माप(ib)) अणु
		deb_hab("do_hab_cmd: ilen=%d is too big!\n", ilen);
		वापस -EINVAL;
	पूर्ण

	अगर (olen + 2 > माप(ob)) अणु
		deb_hab("do_hab_cmd: olen=%d is too big!\n", olen);
		वापस -EINVAL;
	पूर्ण

	ob[0] = cmd;
	ob[1] = msgid;
	स_नकल(&ob[2],obuf,olen);

	deb_hab("hab snd: ");
	dbufout(ob,olen+2,deb_hab);
	deb_hab("\n");

	अगर (mutex_lock_पूर्णांकerruptible(&st->hab_mutex) < 0)
		वापस -EAGAIN;

	अगर ((ret = bcm3510_hab_send_request(st, ob, olen+2)) < 0 ||
		(ret = bcm3510_hab_get_response(st, ib, ilen+2)) < 0)
		जाओ error;

	deb_hab("hab get: ");
	dbufout(ib,ilen+2,deb_hab);
	deb_hab("\n");

	स_नकल(ibuf,&ib[2],ilen);
error:
	mutex_unlock(&st->hab_mutex);
	वापस ret;
पूर्ण

#अगर 0
/* not needed, we use a semaphore to prevent HAB races */
अटल पूर्णांक bcm3510_is_ap_पढ़ोy(काष्ठा bcm3510_state *st)
अणु
	bcm3510_रेजिस्टर_value ap,hab;
	पूर्णांक ret;

	अगर ((ret = bcm3510_पढ़ोB(st,0xa8,&hab)) < 0 ||
		(ret = bcm3510_पढ़ोB(st,0xa2,&ap) < 0))
		वापस ret;

	अगर (ap.APSTAT1_a2.RESET || ap.APSTAT1_a2.IDLE || ap.APSTAT1_a2.STOP || hab.HABSTAT_a8.HABR) अणु
		deb_info("AP is busy\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक bcm3510_bert_reset(काष्ठा bcm3510_state *st)
अणु
	bcm3510_रेजिस्टर_value b;
	पूर्णांक ret;

	अगर ((ret = bcm3510_पढ़ोB(st,0xfa,&b)) < 0)
		वापस ret;

	b.BERCTL_fa.RESYNC = 0; bcm3510_ग_लिखोB(st,0xfa,b);
	b.BERCTL_fa.RESYNC = 1; bcm3510_ग_लिखोB(st,0xfa,b);
	b.BERCTL_fa.RESYNC = 0; bcm3510_ग_लिखोB(st,0xfa,b);
	b.BERCTL_fa.CNTCTL = 1; b.BERCTL_fa.BITCNT = 1; bcm3510_ग_लिखोB(st,0xfa,b);

	/* clear residual bit counter TODO  */
	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_refresh_state(काष्ठा bcm3510_state *st)
अणु
	अगर (समय_after(jअगरfies,st->next_status_check)) अणु
		bcm3510_करो_hab_cmd(st, CMD_STATUS, MSGID_STATUS1, शून्य,0, (u8 *)&st->status1, माप(st->status1));
		bcm3510_करो_hab_cmd(st, CMD_STATUS, MSGID_STATUS2, शून्य,0, (u8 *)&st->status2, माप(st->status2));
		st->next_status_check = jअगरfies + (st->status_check_पूर्णांकerval*HZ)/1000;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा bcm3510_state* st = fe->demodulator_priv;
	bcm3510_refresh_state(st);

	*status = 0;
	अगर (st->status1.STATUS1.RECEIVER_LOCK)
		*status |= FE_HAS_LOCK | FE_HAS_SYNC;

	अगर (st->status1.STATUS1.FEC_LOCK)
		*status |= FE_HAS_VITERBI;

	अगर (st->status1.STATUS1.OUT_PLL_LOCK)
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;

	अगर (*status & FE_HAS_LOCK)
		st->status_check_पूर्णांकerval = 1500;
	अन्यथा /* more frequently checks अगर no lock has been achieved yet */
		st->status_check_पूर्णांकerval = 500;

	deb_info("real_status: %02x\n",*status);
	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा bcm3510_state* st = fe->demodulator_priv;
	bcm3510_refresh_state(st);

	*ber = (st->status2.LDBER0 << 16) | (st->status2.LDBER1 << 8) | st->status2.LDBER2;
	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_पढ़ो_unc(काष्ठा dvb_frontend* fe, u32* unc)
अणु
	काष्ठा bcm3510_state* st = fe->demodulator_priv;
	bcm3510_refresh_state(st);
	*unc = (st->status2.LDUERC0 << 8) | st->status2.LDUERC1;
	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा bcm3510_state* st = fe->demodulator_priv;
	s32 t;

	bcm3510_refresh_state(st);
	t = st->status2.SIGNAL;

	अगर (t > 190)
		t = 190;
	अगर (t < 90)
		t = 90;

	t -= 90;
	t = t * 0xff / 100;
	/* normalize अगर necessary */
	*strength = (t << 8) | t;
	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा bcm3510_state* st = fe->demodulator_priv;
	bcm3510_refresh_state(st);

	*snr = st->status1.SNR_EST0*1000 + ((st->status1.SNR_EST1*1000) >> 8);
	वापस 0;
पूर्ण

/* tuner frontend programming */
अटल पूर्णांक bcm3510_tuner_cmd(काष्ठा bcm3510_state* st,u8 bc, u16 n, u8 a)
अणु
	काष्ठा bcm3510_hab_cmd_tune c;
	स_रखो(&c,0,माप(काष्ठा bcm3510_hab_cmd_tune));

/* I2C Mode disabled,  set 16 control / Data pairs */
	c.length = 0x10;
	c.घड़ी_width = 0;
/* CS1, CS0, DATA, CLK bits control the tuner RF_AGC_SEL pin is set to
 * logic high (as Configuration) */
	c.misc = 0x10;
/* Set duration of the initial state of TUNCTL = 3.34 micro Sec */
	c.TUNCTL_state = 0x40;

/* PRESCALER DIVIDE RATIO | BC1_2_3_4; (band चयन), 1stosc REFERENCE COUNTER REF_S12 and REF_S11 */
	c.ctl_dat[0].ctrl.size = BITS_8;
	c.ctl_dat[0].data      = 0x80 | bc;

/* Control DATA pin, 1stosc REFERENCE COUNTER REF_S10 to REF_S3 */
	c.ctl_dat[1].ctrl.size = BITS_8;
	c.ctl_dat[1].data      = 4;

/* set CONTROL BIT 1 to 1, 1stosc REFERENCE COUNTER REF_S2 to REF_S1 */
	c.ctl_dat[2].ctrl.size = BITS_3;
	c.ctl_dat[2].data      = 0x20;

/* control CS0 pin, pulse byte ? */
	c.ctl_dat[3].ctrl.size = BITS_3;
	c.ctl_dat[3].ctrl.clk_off = 1;
	c.ctl_dat[3].ctrl.cs0  = 1;
	c.ctl_dat[3].data      = 0x40;

/* PGM_S18 to PGM_S11 */
	c.ctl_dat[4].ctrl.size = BITS_8;
	c.ctl_dat[4].data      = n >> 3;

/* PGM_S10 to PGM_S8, SWL_S7 to SWL_S3 */
	c.ctl_dat[5].ctrl.size = BITS_8;
	c.ctl_dat[5].data      = ((n & 0x7) << 5) | (a >> 2);

/* SWL_S2 and SWL_S1, set CONTROL BIT 2 to 0 */
	c.ctl_dat[6].ctrl.size = BITS_3;
	c.ctl_dat[6].data      = (a << 6) & 0xdf;

/* control CS0 pin, pulse byte ? */
	c.ctl_dat[7].ctrl.size = BITS_3;
	c.ctl_dat[7].ctrl.clk_off = 1;
	c.ctl_dat[7].ctrl.cs0  = 1;
	c.ctl_dat[7].data      = 0x40;

/* PRESCALER DIVIDE RATIO, 2nकरोsc REFERENCE COUNTER REF_S12 and REF_S11 */
	c.ctl_dat[8].ctrl.size = BITS_8;
	c.ctl_dat[8].data      = 0x80;

/* 2nकरोsc REFERENCE COUNTER REF_S10 to REF_S3 */
	c.ctl_dat[9].ctrl.size = BITS_8;
	c.ctl_dat[9].data      = 0x10;

/* set CONTROL BIT 1 to 1, 2nकरोsc REFERENCE COUNTER REF_S2 to REF_S1 */
	c.ctl_dat[10].ctrl.size = BITS_3;
	c.ctl_dat[10].data      = 0x20;

/* pulse byte */
	c.ctl_dat[11].ctrl.size = BITS_3;
	c.ctl_dat[11].ctrl.clk_off = 1;
	c.ctl_dat[11].ctrl.cs1  = 1;
	c.ctl_dat[11].data      = 0x40;

/* PGM_S18 to PGM_S11 */
	c.ctl_dat[12].ctrl.size = BITS_8;
	c.ctl_dat[12].data      = 0x2a;

/* PGM_S10 to PGM_S8 and SWL_S7 to SWL_S3 */
	c.ctl_dat[13].ctrl.size = BITS_8;
	c.ctl_dat[13].data      = 0x8e;

/* SWL_S2 and SWL_S1 and set CONTROL BIT 2 to 0 */
	c.ctl_dat[14].ctrl.size = BITS_3;
	c.ctl_dat[14].data      = 0;

/* Pulse Byte */
	c.ctl_dat[15].ctrl.size = BITS_3;
	c.ctl_dat[15].ctrl.clk_off = 1;
	c.ctl_dat[15].ctrl.cs1  = 1;
	c.ctl_dat[15].data      = 0x40;

	वापस bcm3510_करो_hab_cmd(st,CMD_TUNE, MSGID_TUNE,(u8 *) &c,माप(c), शून्य, 0);
पूर्ण

अटल पूर्णांक bcm3510_set_freq(काष्ठा bcm3510_state* st,u32 freq)
अणु
	u8 bc,a;
	u16 n;
	s32 YIntercept,Tfvco1;

	freq /= 1000;

	deb_info("%dkHz:",freq);
	/* set Band Switch */
	अगर (freq <= 168000)
		bc = 0x1c;
	अन्यथा अगर (freq <= 378000)
		bc = 0x2c;
	अन्यथा
		bc = 0x30;

	अगर (freq >= 470000) अणु
		freq -= 470001;
		YIntercept = 18805;
	पूर्ण अन्यथा अगर (freq >= 90000) अणु
		freq -= 90001;
		YIntercept = 15005;
	पूर्ण अन्यथा अगर (freq >= 76000)अणु
		freq -= 76001;
		YIntercept = 14865;
	पूर्ण अन्यथा अणु
		freq -= 54001;
		YIntercept = 14645;
	पूर्ण

	Tfvco1 = (((freq/6000)*60 + YIntercept)*4)/10;

	n = Tfvco1 >> 6;
	a = Tfvco1 & 0x3f;

	deb_info(" BC1_2_3_4: %x, N: %x A: %x\n", bc, n, a);
	अगर (n >= 16 && n <= 2047)
		वापस bcm3510_tuner_cmd(st,bc,n,a);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bcm3510_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा bcm3510_state* st = fe->demodulator_priv;
	काष्ठा bcm3510_hab_cmd_ext_acquire cmd;
	काष्ठा bcm3510_hab_cmd_bert_control bert;
	पूर्णांक ret;

	स_रखो(&cmd,0,माप(cmd));
	चयन (c->modulation) अणु
		हाल QAM_256:
			cmd.ACQUIRE0.MODE = 0x1;
			cmd.ACQUIRE1.SYM_RATE = 0x1;
			cmd.ACQUIRE1.IF_FREQ = 0x1;
			अवरोध;
		हाल QAM_64:
			cmd.ACQUIRE0.MODE = 0x2;
			cmd.ACQUIRE1.SYM_RATE = 0x2;
			cmd.ACQUIRE1.IF_FREQ = 0x1;
			अवरोध;
#अगर 0
		हाल QAM_256:
			cmd.ACQUIRE0.MODE = 0x3;
			अवरोध;
		हाल QAM_128:
			cmd.ACQUIRE0.MODE = 0x4;
			अवरोध;
		हाल QAM_64:
			cmd.ACQUIRE0.MODE = 0x5;
			अवरोध;
		हाल QAM_32:
			cmd.ACQUIRE0.MODE = 0x6;
			अवरोध;
		हाल QAM_16:
			cmd.ACQUIRE0.MODE = 0x7;
			अवरोध;
#पूर्ण_अगर
		हाल VSB_8:
			cmd.ACQUIRE0.MODE = 0x8;
			cmd.ACQUIRE1.SYM_RATE = 0x0;
			cmd.ACQUIRE1.IF_FREQ = 0x0;
			अवरोध;
		हाल VSB_16:
			cmd.ACQUIRE0.MODE = 0x9;
			cmd.ACQUIRE1.SYM_RATE = 0x0;
			cmd.ACQUIRE1.IF_FREQ = 0x0;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	cmd.ACQUIRE0.OFFSET = 0;
	cmd.ACQUIRE0.NTSCSWEEP = 1;
	cmd.ACQUIRE0.FA = 1;
	cmd.ACQUIRE0.BW = 0;

/*	अगर (enableOffset) अणु
		cmd.IF_OFFSET0 = xx;
		cmd.IF_OFFSET1 = xx;

		cmd.SYM_OFFSET0 = xx;
		cmd.SYM_OFFSET1 = xx;
		अगर (enableNtscSweep) अणु
			cmd.NTSC_OFFSET0;
			cmd.NTSC_OFFSET1;
		पूर्ण
	पूर्ण */
	bcm3510_करो_hab_cmd(st, CMD_ACQUIRE, MSGID_EXT_TUNER_ACQUIRE, (u8 *) &cmd, माप(cmd), शून्य, 0);

/* करोing it with dअगरferent MSGIDs, data book and source dअगरfers */
	bert.BE = 0;
	bert.unused = 0;
	bcm3510_करो_hab_cmd(st, CMD_STATE_CONTROL, MSGID_BERT_CONTROL, (u8 *) &bert, माप(bert), शून्य, 0);
	bcm3510_करो_hab_cmd(st, CMD_STATE_CONTROL, MSGID_BERT_SET, (u8 *) &bert, माप(bert), शून्य, 0);

	bcm3510_bert_reset(st);

	ret = bcm3510_set_freq(st, c->frequency);
	अगर (ret < 0)
		वापस ret;

	स_रखो(&st->status1,0,माप(st->status1));
	स_रखो(&st->status2,0,माप(st->status2));
	st->status_check_पूर्णांकerval = 500;

/* Give the AP some समय */
	msleep(200);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_sleep(काष्ठा dvb_frontend* fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_get_tune_settings(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 1000;
	s->step_size = 0;
	s->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल व्योम bcm3510_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा bcm3510_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

/* firmware करोwnload:
 * firmware file is build up like this:
 * 16bit addr, 16bit length, 8byte of length
 */
#घोषणा BCM3510_DEFAULT_FIRMWARE "dvb-fe-bcm3510-01.fw"

अटल पूर्णांक bcm3510_ग_लिखो_ram(काष्ठा bcm3510_state *st, u16 addr, स्थिर u8 *b,
			     u16 len)
अणु
	पूर्णांक ret = 0,i;
	bcm3510_रेजिस्टर_value vH, vL,vD;

	vH.MADRH_a9 = addr >> 8;
	vL.MADRL_aa = addr;
	अगर ((ret = bcm3510_ग_लिखोB(st,0xa9,vH)) < 0) वापस ret;
	अगर ((ret = bcm3510_ग_लिखोB(st,0xaa,vL)) < 0) वापस ret;

	क्रम (i = 0; i < len; i++) अणु
		vD.MDATA_ab = b[i];
		अगर ((ret = bcm3510_ग_लिखोB(st,0xab,vD)) < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_करोwnload_firmware(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा bcm3510_state* st = fe->demodulator_priv;
	स्थिर काष्ठा firmware *fw;
	u16 addr,len;
	स्थिर u8 *b;
	पूर्णांक ret,i;

	deb_info("requesting firmware\n");
	अगर ((ret = st->config->request_firmware(fe, &fw, BCM3510_DEFAULT_FIRMWARE)) < 0) अणु
		err("could not load firmware (%s): %d",BCM3510_DEFAULT_FIRMWARE,ret);
		वापस ret;
	पूर्ण
	deb_info("got firmware: %zu\n", fw->size);

	b = fw->data;
	क्रम (i = 0; i < fw->size;) अणु
		addr = le16_to_cpu(*((__le16 *)&b[i]));
		len  = le16_to_cpu(*((__le16 *)&b[i+2]));
		deb_info("firmware chunk, addr: 0x%04x, len: 0x%04x, total length: 0x%04zx\n",addr,len,fw->size);
		अगर ((ret = bcm3510_ग_लिखो_ram(st,addr,&b[i+4],len)) < 0) अणु
			err("firmware download failed: %d\n",ret);
			वापस ret;
		पूर्ण
		i += 4 + len;
	पूर्ण
	release_firmware(fw);
	deb_info("firmware download successfully completed\n");
	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_check_firmware_version(काष्ठा bcm3510_state *st)
अणु
	काष्ठा bcm3510_hab_cmd_get_version_info ver;
	bcm3510_करो_hab_cmd(st,CMD_GET_VERSION_INFO,MSGID_GET_VERSION_INFO,शून्य,0,(u8*)&ver,माप(ver));

	deb_info("Version information: 0x%02x 0x%02x 0x%02x 0x%02x\n",
		ver.microcode_version, ver.script_version, ver.config_version, ver.demod_version);

	अगर (ver.script_version == BCM3510_DEF_SCRIPT_VERSION &&
		ver.config_version == BCM3510_DEF_CONFIG_VERSION &&
		ver.demod_version  == BCM3510_DEF_DEMOD_VERSION)
		वापस 0;

	deb_info("version check failed\n");
	वापस -ENODEV;
पूर्ण

/* (un)resetting the AP */
अटल पूर्णांक bcm3510_reset(काष्ठा bcm3510_state *st)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ  t;
	bcm3510_रेजिस्टर_value v;

	bcm3510_पढ़ोB(st,0xa0,&v); v.HCTL1_a0.RESET = 1;
	अगर ((ret = bcm3510_ग_लिखोB(st,0xa0,v)) < 0)
		वापस ret;

	t = jअगरfies + 3*HZ;
	जबतक (समय_beक्रमe(jअगरfies, t)) अणु
		msleep(10);
		अगर ((ret = bcm3510_पढ़ोB(st,0xa2,&v)) < 0)
			वापस ret;

		अगर (v.APSTAT1_a2.RESET)
			वापस 0;
	पूर्ण
	deb_info("reset timed out\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक bcm3510_clear_reset(काष्ठा bcm3510_state *st)
अणु
	bcm3510_रेजिस्टर_value v;
	पूर्णांक ret;
	अचिन्हित दीर्घ t;

	v.raw = 0;
	अगर ((ret = bcm3510_ग_लिखोB(st,0xa0,v)) < 0)
		वापस ret;

	t = jअगरfies + 3*HZ;
	जबतक (समय_beक्रमe(jअगरfies, t)) अणु
		msleep(10);
		अगर ((ret = bcm3510_पढ़ोB(st,0xa2,&v)) < 0)
			वापस ret;

		/* verअगरy that reset is cleared */
		अगर (!v.APSTAT1_a2.RESET)
			वापस 0;
	पूर्ण
	deb_info("reset clear timed out\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक bcm3510_init_cold(काष्ठा bcm3510_state *st)
अणु
	पूर्णांक ret;
	bcm3510_रेजिस्टर_value v;

	/* पढ़ो Acquisation Processor status रेजिस्टर and check it is not in RUN mode */
	अगर ((ret = bcm3510_पढ़ोB(st,0xa2,&v)) < 0)
		वापस ret;
	अगर (v.APSTAT1_a2.RUN) अणु
		deb_info("AP is already running - firmware already loaded.\n");
		वापस 0;
	पूर्ण

	deb_info("reset?\n");
	अगर ((ret = bcm3510_reset(st)) < 0)
		वापस ret;

	deb_info("tristate?\n");
	/* tri-state */
	v.TSTCTL_2e.CTL = 0;
	अगर ((ret = bcm3510_ग_लिखोB(st,0x2e,v)) < 0)
		वापस ret;

	deb_info("firmware?\n");
	अगर ((ret = bcm3510_करोwnload_firmware(&st->frontend)) < 0 ||
		(ret = bcm3510_clear_reset(st)) < 0)
		वापस ret;

	/* anything left here to Let the acquisition processor begin execution at program counter 0000 ??? */

	वापस 0;
पूर्ण

अटल पूर्णांक bcm3510_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा bcm3510_state* st = fe->demodulator_priv;
	bcm3510_रेजिस्टर_value j;
	काष्ठा bcm3510_hab_cmd_set_agc c;
	पूर्णांक ret;

	अगर ((ret = bcm3510_पढ़ोB(st,0xca,&j)) < 0)
		वापस ret;

	deb_info("JDEC: %02x\n",j.raw);

	चयन (j.JDEC_ca.JDEC) अणु
		हाल JDEC_WAIT_AT_RAM:
			deb_info("attempting to download firmware\n");
			अगर ((ret = bcm3510_init_cold(st)) < 0)
				वापस ret;
			fallthrough;
		हाल JDEC_EEPROM_LOAD_WAIT:
			deb_info("firmware is loaded\n");
			bcm3510_check_firmware_version(st);
			अवरोध;
		शेष:
			वापस -ENODEV;
	पूर्ण

	स_रखो(&c,0,1);
	c.SEL = 1;
	bcm3510_करो_hab_cmd(st,CMD_AUTO_PARAM,MSGID_SET_RF_AGC_SEL,(u8 *)&c,माप(c),शून्य,0);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा dvb_frontend_ops bcm3510_ops;

काष्ठा dvb_frontend* bcm3510_attach(स्थिर काष्ठा bcm3510_config *config,
				   काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा bcm3510_state* state = शून्य;
	पूर्णांक ret;
	bcm3510_रेजिस्टर_value v;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा bcm3510_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */

	state->config = config;
	state->i2c = i2c;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &bcm3510_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	mutex_init(&state->hab_mutex);

	अगर ((ret = bcm3510_पढ़ोB(state,0xe0,&v)) < 0)
		जाओ error;

	deb_info("Revision: 0x%1x, Layer: 0x%1x.\n",v.REVID_e0.REV,v.REVID_e0.LAYER);

	अगर ((v.REVID_e0.REV != 0x1 && v.REVID_e0.LAYER != 0xb) && /* cold */
		(v.REVID_e0.REV != 0x8 && v.REVID_e0.LAYER != 0x0))   /* warm */
		जाओ error;

	info("Revision: 0x%1x, Layer: 0x%1x.",v.REVID_e0.REV,v.REVID_e0.LAYER);

	bcm3510_reset(state);

	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(bcm3510_attach);

अटल स्थिर काष्ठा dvb_frontend_ops bcm3510_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name = "Broadcom BCM3510 VSB/QAM frontend",
		.frequency_min_hz =  54 * MHz,
		.frequency_max_hz = 803 * MHz,
		.caps =
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_8VSB | FE_CAN_16VSB |
			FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_128 | FE_CAN_QAM_256
	पूर्ण,

	.release = bcm3510_release,

	.init = bcm3510_init,
	.sleep = bcm3510_sleep,

	.set_frontend = bcm3510_set_frontend,
	.get_tune_settings = bcm3510_get_tune_settings,

	.पढ़ो_status = bcm3510_पढ़ो_status,
	.पढ़ो_ber = bcm3510_पढ़ो_ber,
	.पढ़ो_संकेत_strength = bcm3510_पढ़ो_संकेत_strength,
	.पढ़ो_snr = bcm3510_पढ़ो_snr,
	.पढ़ो_ucblocks = bcm3510_पढ़ो_unc,
पूर्ण;

MODULE_DESCRIPTION("Broadcom BCM3510 ATSC (8VSB/16VSB & ITU J83 AnnexB FEC QAM64/256) demodulator driver");
MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_LICENSE("GPL");
