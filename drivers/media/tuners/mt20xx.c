<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2c tv tuner chip device driver
 * controls microtune tuners, mt2032 + mt2050 at the moment.
 *
 * This "mt20xx" module was split apart from the original "tuner" module.
 */
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश "tuner-i2c.h"
#समावेश "mt20xx.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

/* ---------------------------------------------------------------------- */

अटल अचिन्हित पूर्णांक optimize_vco  = 1;
module_param(optimize_vco,      पूर्णांक, 0644);

अटल अचिन्हित पूर्णांक tv_antenna    = 1;
module_param(tv_antenna,        पूर्णांक, 0644);

अटल अचिन्हित पूर्णांक radio_antenna;
module_param(radio_antenna,     पूर्णांक, 0644);

/* ---------------------------------------------------------------------- */

#घोषणा MT2032 0x04
#घोषणा MT2030 0x06
#घोषणा MT2040 0x07
#घोषणा MT2050 0x42

अटल अक्षर *microtune_part[] = अणु
	[ MT2030 ] = "MT2030",
	[ MT2032 ] = "MT2032",
	[ MT2040 ] = "MT2040",
	[ MT2050 ] = "MT2050",
पूर्ण;

काष्ठा microtune_priv अणु
	काष्ठा tuner_i2c_props i2c_props;

	अचिन्हित पूर्णांक xogc;
	//अचिन्हित पूर्णांक radio_अगर2;

	u32 frequency;
पूर्ण;

अटल व्योम microtune_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक microtune_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	*frequency = priv->frequency;
	वापस 0;
पूर्ण

// IsSpurInBand()?
अटल पूर्णांक mt2032_spurcheck(काष्ठा dvb_frontend *fe,
			    पूर्णांक f1, पूर्णांक f2, पूर्णांक spectrum_from,पूर्णांक spectrum_to)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	पूर्णांक n1=1,n2,f;

	f1=f1/1000; //scale to kHz to aव्योम 32bit overflows
	f2=f2/1000;
	spectrum_from/=1000;
	spectrum_to/=1000;

	tuner_dbg("spurcheck f1=%d f2=%d  from=%d to=%d\n",
		  f1,f2,spectrum_from,spectrum_to);

	करो अणु
	    n2=-n1;
	    f=n1*(f1-f2);
	    करो अणु
		n2--;
		f=f-f2;
		tuner_dbg("spurtest n1=%d n2=%d ftest=%d\n",n1,n2,f);

		अगर( (f>spectrum_from) && (f<spectrum_to))
			tuner_dbg("mt2032 spurcheck triggered: %d\n",n1);
	    पूर्ण जबतक ( (f>(f2-spectrum_to)) || (n2>-5));
	    n1++;
	पूर्ण जबतक (n1<5);

	वापस 1;
पूर्ण

अटल पूर्णांक mt2032_compute_freq(काष्ठा dvb_frontend *fe,
			       अचिन्हित पूर्णांक rfin,
			       अचिन्हित पूर्णांक अगर1, अचिन्हित पूर्णांक अगर2,
			       अचिन्हित पूर्णांक spectrum_from,
			       अचिन्हित पूर्णांक spectrum_to,
			       अचिन्हित अक्षर *buf,
			       पूर्णांक *ret_sel,
			       अचिन्हित पूर्णांक xogc) //all in Hz
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	अचिन्हित पूर्णांक fref,lo1,lo1n,lo1a,s,sel,lo1freq, desired_lo1,
		desired_lo2,lo2,lo2n,lo2a,lo2num,lo2freq;

	fref= 5250 *1000; //5.25MHz
	desired_lo1=rfin+अगर1;

	lo1=(2*(desired_lo1/1000)+(fref/1000)) / (2*fref/1000);
	lo1n=lo1/8;
	lo1a=lo1-(lo1n*8);

	s=rfin/1000/1000+1090;

	अगर(optimize_vco) अणु
		अगर(s>1890) sel=0;
		अन्यथा अगर(s>1720) sel=1;
		अन्यथा अगर(s>1530) sel=2;
		अन्यथा अगर(s>1370) sel=3;
		अन्यथा sel=4; // >1090
	पूर्ण
	अन्यथा अणु
		अगर(s>1790) sel=0; // <1958
		अन्यथा अगर(s>1617) sel=1;
		अन्यथा अगर(s>1449) sel=2;
		अन्यथा अगर(s>1291) sel=3;
		अन्यथा sel=4; // >1090
	पूर्ण
	*ret_sel=sel;

	lo1freq=(lo1a+8*lo1n)*fref;

	tuner_dbg("mt2032: rfin=%d lo1=%d lo1n=%d lo1a=%d sel=%d, lo1freq=%d\n",
		  rfin,lo1,lo1n,lo1a,sel,lo1freq);

	desired_lo2=lo1freq-rfin-अगर2;
	lo2=(desired_lo2)/fref;
	lo2n=lo2/8;
	lo2a=lo2-(lo2n*8);
	lo2num=((desired_lo2/1000)%(fref/1000))* 3780/(fref/1000); //scale to fit in 32bit arith
	lo2freq=(lo2a+8*lo2n)*fref + lo2num*(fref/1000)/3780*1000;

	tuner_dbg("mt2032: rfin=%d lo2=%d lo2n=%d lo2a=%d num=%d lo2freq=%d\n",
		  rfin,lo2,lo2n,lo2a,lo2num,lo2freq);

	अगर (lo1a > 7 || lo1n < 17 || lo1n > 48 || lo2a > 7 || lo2n < 17 ||
			lo2n > 30) अणु
		tuner_info("mt2032: frequency parameters out of range: %d %d %d %d\n",
			   lo1a, lo1n, lo2a,lo2n);
		वापस(-1);
	पूर्ण

	mt2032_spurcheck(fe, lo1freq, desired_lo2,  spectrum_from, spectrum_to);
	// should recalculate lo1 (one step up/करोwn)

	// set up MT2032 रेजिस्टर map क्रम transfer over i2c
	buf[0]=lo1n-1;
	buf[1]=lo1a | (sel<<4);
	buf[2]=0x86; // LOGC
	buf[3]=0x0f; //reserved
	buf[4]=0x1f;
	buf[5]=(lo2n-1) | (lo2a<<5);
	अगर(rfin >400*1000*1000)
		buf[6]=0xe4;
	अन्यथा
		buf[6]=0xf4; // set PKEN per rev 1.2
	buf[7]=8+xogc;
	buf[8]=0xc3; //reserved
	buf[9]=0x4e; //reserved
	buf[10]=0xec; //reserved
	buf[11]=(lo2num&0xff);
	buf[12]=(lo2num>>8) |0x80; // Lo2RST

	वापस 0;
पूर्ण

अटल पूर्णांक mt2032_check_lo_lock(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	पूर्णांक try,lock=0;
	अचिन्हित अक्षर buf[2];

	क्रम(try=0;try<10;try++) अणु
		buf[0]=0x0e;
		tuner_i2c_xfer_send(&priv->i2c_props,buf,1);
		tuner_i2c_xfer_recv(&priv->i2c_props,buf,1);
		tuner_dbg("mt2032 Reg.E=0x%02x\n",buf[0]);
		lock=buf[0] &0x06;

		अगर (lock==6)
			अवरोध;

		tuner_dbg("mt2032: pll wait 1ms for lock (0x%2x)\n",buf[0]);
		udelay(1000);
	पूर्ण
	वापस lock;
पूर्ण

अटल पूर्णांक mt2032_optimize_vco(काष्ठा dvb_frontend *fe,पूर्णांक sel,पूर्णांक lock)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर buf[2];
	पूर्णांक tad1;

	buf[0]=0x0f;
	tuner_i2c_xfer_send(&priv->i2c_props,buf,1);
	tuner_i2c_xfer_recv(&priv->i2c_props,buf,1);
	tuner_dbg("mt2032 Reg.F=0x%02x\n",buf[0]);
	tad1=buf[0]&0x07;

	अगर(tad1 ==0) वापस lock;
	अगर(tad1 ==1) वापस lock;

	अगर(tad1==2) अणु
		अगर(sel==0)
			वापस lock;
		अन्यथा sel--;
	पूर्ण
	अन्यथा अणु
		अगर(sel<4)
			sel++;
		अन्यथा
			वापस lock;
	पूर्ण

	tuner_dbg("mt2032 optimize_vco: sel=%d\n",sel);

	buf[0]=0x0f;
	buf[1]=sel;
	tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
	lock=mt2032_check_lo_lock(fe);
	वापस lock;
पूर्ण


अटल व्योम mt2032_set_अगर_freq(काष्ठा dvb_frontend *fe, अचिन्हित पूर्णांक rfin,
			       अचिन्हित पूर्णांक अगर1, अचिन्हित पूर्णांक अगर2,
			       अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	अचिन्हित अक्षर buf[21];
	पूर्णांक lपूर्णांक_try,ret,sel,lock=0;
	काष्ठा microtune_priv *priv = fe->tuner_priv;

	tuner_dbg("mt2032_set_if_freq rfin=%d if1=%d if2=%d from=%d to=%d\n",
		  rfin,अगर1,अगर2,from,to);

	buf[0]=0;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,1);
	tuner_i2c_xfer_recv(&priv->i2c_props,buf,21);

	buf[0]=0;
	ret=mt2032_compute_freq(fe,rfin,अगर1,अगर2,from,to,&buf[1],&sel,priv->xogc);
	अगर (ret<0)
		वापस;

	// send only the relevant रेजिस्टरs per Rev. 1.2
	buf[0]=0;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,4);
	buf[5]=5;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+5,4);
	buf[11]=11;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+11,3);
	अगर(ret!=3)
		tuner_warn("i2c i/o error: rc == %d (should be 3)\n",ret);

	// रुको क्रम PLLs to lock (per manual), retry LINT अगर not.
	क्रम(lपूर्णांक_try=0; lपूर्णांक_try<2; lपूर्णांक_try++) अणु
		lock=mt2032_check_lo_lock(fe);

		अगर(optimize_vco)
			lock=mt2032_optimize_vco(fe,sel,lock);
		अगर(lock==6) अवरोध;

		tuner_dbg("mt2032: re-init PLLs by LINT\n");
		buf[0]=7;
		buf[1]=0x80 +8+priv->xogc; // set LINT to re-init PLLs
		tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
		mdelay(10);
		buf[1]=8+priv->xogc;
		tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
	पूर्ण

	अगर (lock!=6)
		tuner_warn("MT2032 Fatal Error: PLLs didn't lock.\n");

	buf[0]=2;
	buf[1]=0x20; // LOGC क्रम optimal phase noise
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
	अगर (ret!=2)
		tuner_warn("i2c i/o error: rc == %d (should be 2)\n",ret);
पूर्ण


अटल पूर्णांक mt2032_set_tv_freq(काष्ठा dvb_frontend *fe,
			      काष्ठा analog_parameters *params)
अणु
	पूर्णांक अगर2,from,to;

	// संकेत bandwidth and picture carrier
	अगर (params->std & V4L2_STD_525_60) अणु
		// NTSC
		from = 40750*1000;
		to   = 46750*1000;
		अगर2  = 45750*1000;
	पूर्ण अन्यथा अणु
		// PAL
		from = 32900*1000;
		to   = 39900*1000;
		अगर2  = 38900*1000;
	पूर्ण

	mt2032_set_अगर_freq(fe, params->frequency*62500,
			   1090*1000*1000, अगर2, from, to);

	वापस 0;
पूर्ण

अटल पूर्णांक mt2032_set_radio_freq(काष्ठा dvb_frontend *fe,
				 काष्ठा analog_parameters *params)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	पूर्णांक अगर2;

	अगर (params->std & V4L2_STD_525_60) अणु
		tuner_dbg("pinnacle ntsc\n");
		अगर2 = 41300 * 1000;
	पूर्ण अन्यथा अणु
		tuner_dbg("pinnacle pal\n");
		अगर2 = 33300 * 1000;
	पूर्ण

	// per Manual क्रम FM tuning: first अगर center freq. 1085 MHz
	mt2032_set_अगर_freq(fe, params->frequency * 125 / 2,
			   1085*1000*1000,अगर2,अगर2,अगर2);

	वापस 0;
पूर्ण

अटल पूर्णांक mt2032_set_params(काष्ठा dvb_frontend *fe,
			     काष्ठा analog_parameters *params)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	पूर्णांक ret = -EINVAL;

	चयन (params->mode) अणु
	हाल V4L2_TUNER_RADIO:
		ret = mt2032_set_radio_freq(fe, params);
		priv->frequency = params->frequency * 125 / 2;
		अवरोध;
	हाल V4L2_TUNER_ANALOG_TV:
	हाल V4L2_TUNER_DIGITAL_TV:
		ret = mt2032_set_tv_freq(fe, params);
		priv->frequency = params->frequency * 62500;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops mt2032_tuner_ops = अणु
	.set_analog_params = mt2032_set_params,
	.release           = microtune_release,
	.get_frequency     = microtune_get_frequency,
पूर्ण;

// Initialization as described in "MT203x Programming Procedures", Rev 1.2, Feb.2001
अटल पूर्णांक mt2032_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर buf[21];
	पूर्णांक ret,xogc,xok=0;

	// Initialize Registers per spec.
	buf[1]=2; // Index to रेजिस्टर 2
	buf[2]=0xff;
	buf[3]=0x0f;
	buf[4]=0x1f;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+1,4);

	buf[5]=6; // Index रेजिस्टर 6
	buf[6]=0xe4;
	buf[7]=0x8f;
	buf[8]=0xc3;
	buf[9]=0x4e;
	buf[10]=0xec;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+5,6);

	buf[12]=13;  // Index रेजिस्टर 13
	buf[13]=0x32;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+12,2);

	// Adjust XOGC (रेजिस्टर 7), रुको क्रम XOK
	xogc=7;
	करो अणु
		tuner_dbg("mt2032: xogc = 0x%02x\n",xogc&0x07);
		mdelay(10);
		buf[0]=0x0e;
		tuner_i2c_xfer_send(&priv->i2c_props,buf,1);
		tuner_i2c_xfer_recv(&priv->i2c_props,buf,1);
		xok=buf[0]&0x01;
		tuner_dbg("mt2032: xok = 0x%02x\n",xok);
		अगर (xok == 1) अवरोध;

		xogc--;
		tuner_dbg("mt2032: xogc = 0x%02x\n",xogc&0x07);
		अगर (xogc == 3) अणु
			xogc=4; // min. 4 per spec
			अवरोध;
		पूर्ण
		buf[0]=0x07;
		buf[1]=0x88 + xogc;
		ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
		अगर (ret!=2)
			tuner_warn("i2c i/o error: rc == %d (should be 2)\n",ret);
	पूर्ण जबतक (xok != 1 );
	priv->xogc=xogc;

	स_नकल(&fe->ops.tuner_ops, &mt2032_tuner_ops, माप(काष्ठा dvb_tuner_ops));

	वापस(1);
पूर्ण

अटल व्योम mt2050_set_antenna(काष्ठा dvb_frontend *fe, अचिन्हित अक्षर antenna)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर buf[2];

	buf[0] = 6;
	buf[1] = antenna ? 0x11 : 0x10;
	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2);
	tuner_dbg("mt2050: enabled antenna connector %d\n", antenna);
पूर्ण

अटल व्योम mt2050_set_अगर_freq(काष्ठा dvb_frontend *fe,अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक अगर2)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	अचिन्हित पूर्णांक अगर1=1218*1000*1000;
	अचिन्हित पूर्णांक f_lo1,f_lo2,lo1,lo2,f_lo1_modulo,f_lo2_modulo,num1,num2,भाग1a,भाग1b,भाग2a,भाग2b;
	पूर्णांक ret;
	अचिन्हित अक्षर buf[6];

	tuner_dbg("mt2050_set_if_freq freq=%d if1=%d if2=%d\n",
		  freq,अगर1,अगर2);

	f_lo1=freq+अगर1;
	f_lo1=(f_lo1/1000000)*1000000;

	f_lo2=f_lo1-freq-अगर2;
	f_lo2=(f_lo2/50000)*50000;

	lo1=f_lo1/4000000;
	lo2=f_lo2/4000000;

	f_lo1_modulo= f_lo1-(lo1*4000000);
	f_lo2_modulo= f_lo2-(lo2*4000000);

	num1=4*f_lo1_modulo/4000000;
	num2=4096*(f_lo2_modulo/1000)/4000;

	// toकरो spurchecks

	भाग1a=(lo1/12)-1;
	भाग1b=lo1-(भाग1a+1)*12;

	भाग2a=(lo2/8)-1;
	भाग2b=lo2-(भाग2a+1)*8;

	अगर (debug > 1) अणु
		tuner_dbg("lo1 lo2 = %d %d\n", lo1, lo2);
		tuner_dbg("num1 num2 div1a div1b div2a div2b= %x %x %x %x %x %x\n",
			  num1,num2,भाग1a,भाग1b,भाग2a,भाग2b);
	पूर्ण

	buf[0]=1;
	buf[1]= 4*भाग1b + num1;
	अगर(freq<275*1000*1000) buf[1] = buf[1]|0x80;

	buf[2]=भाग1a;
	buf[3]=32*भाग2b + num2/256;
	buf[4]=num2-(num2/256)*256;
	buf[5]=भाग2a;
	अगर(num2!=0) buf[5]=buf[5]|0x40;

	अगर (debug > 1)
		tuner_dbg("bufs is: %*ph\n", 6, buf);

	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,6);
	अगर (ret!=6)
		tuner_warn("i2c i/o error: rc == %d (should be 6)\n",ret);
पूर्ण

अटल पूर्णांक mt2050_set_tv_freq(काष्ठा dvb_frontend *fe,
			      काष्ठा analog_parameters *params)
अणु
	अचिन्हित पूर्णांक अगर2;

	अगर (params->std & V4L2_STD_525_60) अणु
		// NTSC
		अगर2 = 45750*1000;
	पूर्ण अन्यथा अणु
		// PAL
		अगर2 = 38900*1000;
	पूर्ण
	अगर (V4L2_TUNER_DIGITAL_TV == params->mode) अणु
		// DVB (pinnacle 300i)
		अगर2 = 36150*1000;
	पूर्ण
	mt2050_set_अगर_freq(fe, params->frequency*62500, अगर2);
	mt2050_set_antenna(fe, tv_antenna);

	वापस 0;
पूर्ण

अटल पूर्णांक mt2050_set_radio_freq(काष्ठा dvb_frontend *fe,
				 काष्ठा analog_parameters *params)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	पूर्णांक अगर2;

	अगर (params->std & V4L2_STD_525_60) अणु
		tuner_dbg("pinnacle ntsc\n");
		अगर2 = 41300 * 1000;
	पूर्ण अन्यथा अणु
		tuner_dbg("pinnacle pal\n");
		अगर2 = 33300 * 1000;
	पूर्ण

	mt2050_set_अगर_freq(fe, params->frequency * 125 / 2, अगर2);
	mt2050_set_antenna(fe, radio_antenna);

	वापस 0;
पूर्ण

अटल पूर्णांक mt2050_set_params(काष्ठा dvb_frontend *fe,
			     काष्ठा analog_parameters *params)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	पूर्णांक ret = -EINVAL;

	चयन (params->mode) अणु
	हाल V4L2_TUNER_RADIO:
		ret = mt2050_set_radio_freq(fe, params);
		priv->frequency = params->frequency * 125 / 2;
		अवरोध;
	हाल V4L2_TUNER_ANALOG_TV:
	हाल V4L2_TUNER_DIGITAL_TV:
		ret = mt2050_set_tv_freq(fe, params);
		priv->frequency = params->frequency * 62500;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops mt2050_tuner_ops = अणु
	.set_analog_params = mt2050_set_params,
	.release           = microtune_release,
	.get_frequency     = microtune_get_frequency,
पूर्ण;

अटल पूर्णांक mt2050_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा microtune_priv *priv = fe->tuner_priv;
	अचिन्हित अक्षर buf[2];

	buf[0] = 6;
	buf[1] = 0x10;
	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2); /* घातer */

	buf[0] = 0x0f;
	buf[1] = 0x0f;
	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2); /* m1lo */

	buf[0] = 0x0d;
	tuner_i2c_xfer_send(&priv->i2c_props, buf, 1);
	tuner_i2c_xfer_recv(&priv->i2c_props, buf, 1);

	tuner_dbg("mt2050: sro is %x\n", buf[0]);

	स_नकल(&fe->ops.tuner_ops, &mt2050_tuner_ops, माप(काष्ठा dvb_tuner_ops));

	वापस 0;
पूर्ण

काष्ठा dvb_frontend *microtune_attach(काष्ठा dvb_frontend *fe,
				      काष्ठा i2c_adapter* i2c_adap,
				      u8 i2c_addr)
अणु
	काष्ठा microtune_priv *priv = शून्य;
	अक्षर *name;
	अचिन्हित अक्षर buf[21];
	पूर्णांक company_code;

	priv = kzalloc(माप(काष्ठा microtune_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;
	fe->tuner_priv = priv;

	priv->i2c_props.addr = i2c_addr;
	priv->i2c_props.adap = i2c_adap;
	priv->i2c_props.name = "mt20xx";

	//priv->radio_अगर2 = 10700 * 1000;	/* 10.7MHz - FM radio */

	स_रखो(buf,0,माप(buf));

	name = "unknown";

	tuner_i2c_xfer_send(&priv->i2c_props,buf,1);
	tuner_i2c_xfer_recv(&priv->i2c_props,buf,21);
	अगर (debug)
		tuner_dbg("MT20xx hexdump: %*ph\n", 21, buf);

	company_code = buf[0x11] << 8 | buf[0x12];
	tuner_info("microtune: companycode=%04x part=%02x rev=%02x\n",
		   company_code,buf[0x13],buf[0x14]);


	अगर (buf[0x13] < ARRAY_SIZE(microtune_part) &&
	    शून्य != microtune_part[buf[0x13]])
		name = microtune_part[buf[0x13]];
	चयन (buf[0x13]) अणु
	हाल MT2032:
		mt2032_init(fe);
		अवरोध;
	हाल MT2050:
		mt2050_init(fe);
		अवरोध;
	शेष:
		tuner_info("microtune %s found, not (yet?) supported, sorry :-/\n",
			   name);
		वापस शून्य;
	पूर्ण

	strscpy(fe->ops.tuner_ops.info.name, name,
		माप(fe->ops.tuner_ops.info.name));
	tuner_info("microtune %s found, OK\n",name);
	वापस fe;
पूर्ण

EXPORT_SYMBOL_GPL(microtune_attach);

MODULE_DESCRIPTION("Microtune tuner driver");
MODULE_AUTHOR("Ralph Metzler, Gerd Knorr, Gunther Mayer");
MODULE_LICENSE("GPL");
