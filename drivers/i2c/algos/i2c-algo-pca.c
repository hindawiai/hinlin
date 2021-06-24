<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  i2c-algo-pca.c i2c driver algorithms क्रम PCA9564 adapters
 *    Copyright (C) 2004 Arcom Control Systems
 *    Copyright (C) 2008 Pengutronix
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-pca.h>

#घोषणा DEB1(fmt, args...) करो अणु अगर (i2c_debug >= 1)			\
				 prपूर्णांकk(KERN_DEBUG fmt, ## args); पूर्ण जबतक (0)
#घोषणा DEB2(fmt, args...) करो अणु अगर (i2c_debug >= 2)			\
				 prपूर्णांकk(KERN_DEBUG fmt, ## args); पूर्ण जबतक (0)
#घोषणा DEB3(fmt, args...) करो अणु अगर (i2c_debug >= 3)			\
				 prपूर्णांकk(KERN_DEBUG fmt, ## args); पूर्ण जबतक (0)

अटल पूर्णांक i2c_debug;

#घोषणा pca_outw(adap, reg, val) adap->ग_लिखो_byte(adap->data, reg, val)
#घोषणा pca_inw(adap, reg) adap->पढ़ो_byte(adap->data, reg)

#घोषणा pca_status(adap) pca_inw(adap, I2C_PCA_STA)
#घोषणा pca_घड़ी(adap) adap->i2c_घड़ी
#घोषणा pca_set_con(adap, val) pca_outw(adap, I2C_PCA_CON, val)
#घोषणा pca_get_con(adap) pca_inw(adap, I2C_PCA_CON)
#घोषणा pca_रुको(adap) adap->रुको_क्रम_completion(adap->data)

अटल व्योम pca_reset(काष्ठा i2c_algo_pca_data *adap)
अणु
	अगर (adap->chip == I2C_PCA_CHIP_9665) अणु
		/* Ignore the reset function from the module,
		 * we can use the parallel bus reset.
		 */
		pca_outw(adap, I2C_PCA_INDPTR, I2C_PCA_IPRESET);
		pca_outw(adap, I2C_PCA_IND, 0xA5);
		pca_outw(adap, I2C_PCA_IND, 0x5A);

		/*
		 * After a reset we need to re-apply any configuration
		 * (calculated in pca_init) to get the bus in a working state.
		 */
		pca_outw(adap, I2C_PCA_INDPTR, I2C_PCA_IMODE);
		pca_outw(adap, I2C_PCA_IND, adap->bus_settings.mode);
		pca_outw(adap, I2C_PCA_INDPTR, I2C_PCA_ISCLL);
		pca_outw(adap, I2C_PCA_IND, adap->bus_settings.tlow);
		pca_outw(adap, I2C_PCA_INDPTR, I2C_PCA_ISCLH);
		pca_outw(adap, I2C_PCA_IND, adap->bus_settings.thi);

		pca_set_con(adap, I2C_PCA_CON_ENSIO);
	पूर्ण अन्यथा अणु
		adap->reset_chip(adap->data);
		pca_set_con(adap, I2C_PCA_CON_ENSIO | adap->bus_settings.घड़ी_freq);
	पूर्ण
पूर्ण

/*
 * Generate a start condition on the i2c bus.
 *
 * वापसs after the start condition has occurred
 */
अटल पूर्णांक pca_start(काष्ठा i2c_algo_pca_data *adap)
अणु
	पूर्णांक sta = pca_get_con(adap);
	DEB2("=== START\n");
	sta |= I2C_PCA_CON_STA;
	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);
	वापस pca_रुको(adap);
पूर्ण

/*
 * Generate a repeated start condition on the i2c bus
 *
 * वापस after the repeated start condition has occurred
 */
अटल पूर्णांक pca_repeated_start(काष्ठा i2c_algo_pca_data *adap)
अणु
	पूर्णांक sta = pca_get_con(adap);
	DEB2("=== REPEATED START\n");
	sta |= I2C_PCA_CON_STA;
	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);
	वापस pca_रुको(adap);
पूर्ण

/*
 * Generate a stop condition on the i2c bus
 *
 * वापसs after the stop condition has been generated
 *
 * STOPs करो not generate an पूर्णांकerrupt or set the SI flag, since the
 * part वापसs the idle state (0xf8). Hence we करोn't need to
 * pca_रुको here.
 */
अटल व्योम pca_stop(काष्ठा i2c_algo_pca_data *adap)
अणु
	पूर्णांक sta = pca_get_con(adap);
	DEB2("=== STOP\n");
	sta |= I2C_PCA_CON_STO;
	sta &= ~(I2C_PCA_CON_STA|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);
पूर्ण

/*
 * Send the slave address and R/W bit
 *
 * वापसs after the address has been sent
 */
अटल पूर्णांक pca_address(काष्ठा i2c_algo_pca_data *adap,
		       काष्ठा i2c_msg *msg)
अणु
	पूर्णांक sta = pca_get_con(adap);
	पूर्णांक addr = i2c_8bit_addr_from_msg(msg);

	DEB2("=== SLAVE ADDRESS %#04x+%c=%#04x\n",
	     msg->addr, msg->flags & I2C_M_RD ? 'R' : 'W', addr);

	pca_outw(adap, I2C_PCA_DAT, addr);

	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_STA|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);

	वापस pca_रुको(adap);
पूर्ण

/*
 * Transmit a byte.
 *
 * Returns after the byte has been transmitted
 */
अटल पूर्णांक pca_tx_byte(काष्ठा i2c_algo_pca_data *adap,
		       __u8 b)
अणु
	पूर्णांक sta = pca_get_con(adap);
	DEB2("=== WRITE %#04x\n", b);
	pca_outw(adap, I2C_PCA_DAT, b);

	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_STA|I2C_PCA_CON_SI);
	pca_set_con(adap, sta);

	वापस pca_रुको(adap);
पूर्ण

/*
 * Receive a byte
 *
 * वापसs immediately.
 */
अटल व्योम pca_rx_byte(काष्ठा i2c_algo_pca_data *adap,
			__u8 *b, पूर्णांक ack)
अणु
	*b = pca_inw(adap, I2C_PCA_DAT);
	DEB2("=== READ %#04x %s\n", *b, ack ? "ACK" : "NACK");
पूर्ण

/*
 * Setup ACK or NACK क्रम next received byte and रुको क्रम it to arrive.
 *
 * Returns after next byte has arrived.
 */
अटल पूर्णांक pca_rx_ack(काष्ठा i2c_algo_pca_data *adap,
		      पूर्णांक ack)
अणु
	पूर्णांक sta = pca_get_con(adap);

	sta &= ~(I2C_PCA_CON_STO|I2C_PCA_CON_STA|I2C_PCA_CON_SI|I2C_PCA_CON_AA);

	अगर (ack)
		sta |= I2C_PCA_CON_AA;

	pca_set_con(adap, sta);
	वापस pca_रुको(adap);
पूर्ण

अटल पूर्णांक pca_xfer(काष्ठा i2c_adapter *i2c_adap,
		    काष्ठा i2c_msg *msgs,
		    पूर्णांक num)
अणु
	काष्ठा i2c_algo_pca_data *adap = i2c_adap->algo_data;
	काष्ठा i2c_msg *msg = शून्य;
	पूर्णांक curmsg;
	पूर्णांक numbytes = 0;
	पूर्णांक state;
	पूर्णांक ret;
	पूर्णांक completed = 1;
	अचिन्हित दीर्घ समयout = jअगरfies + i2c_adap->समयout;

	जबतक ((state = pca_status(adap)) != 0xf8) अणु
		अगर (समय_beक्रमe(jअगरfies, समयout)) अणु
			msleep(10);
		पूर्ण अन्यथा अणु
			dev_dbg(&i2c_adap->dev, "bus is not idle. status is "
				"%#04x\n", state);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	DEB1("{{{ XFER %d messages\n", num);

	अगर (i2c_debug >= 2) अणु
		क्रम (curmsg = 0; curmsg < num; curmsg++) अणु
			पूर्णांक addr, i;
			msg = &msgs[curmsg];

			addr = (0x7f & msg->addr) ;

			अगर (msg->flags & I2C_M_RD)
				prपूर्णांकk(KERN_INFO "    [%02d] RD %d bytes from %#02x [%#02x, ...]\n",
				       curmsg, msg->len, addr, (addr << 1) | 1);
			अन्यथा अणु
				prपूर्णांकk(KERN_INFO "    [%02d] WR %d bytes to %#02x [%#02x%s",
				       curmsg, msg->len, addr, addr << 1,
				       msg->len == 0 ? "" : ", ");
				क्रम (i = 0; i < msg->len; i++)
					prपूर्णांकk("%#04x%s", msg->buf[i], i == msg->len - 1 ? "" : ", ");
				prपूर्णांकk("]\n");
			पूर्ण
		पूर्ण
	पूर्ण

	curmsg = 0;
	ret = -EIO;
	जबतक (curmsg < num) अणु
		state = pca_status(adap);

		DEB3("STATE is 0x%02x\n", state);
		msg = &msgs[curmsg];

		चयन (state) अणु
		हाल 0xf8: /* On reset or stop the bus is idle */
			completed = pca_start(adap);
			अवरोध;

		हाल 0x08: /* A START condition has been transmitted */
		हाल 0x10: /* A repeated start condition has been transmitted */
			completed = pca_address(adap, msg);
			अवरोध;

		हाल 0x18: /* SLA+W has been transmitted; ACK has been received */
		हाल 0x28: /* Data byte in I2CDAT has been transmitted; ACK has been received */
			अगर (numbytes < msg->len) अणु
				completed = pca_tx_byte(adap,
							msg->buf[numbytes]);
				numbytes++;
				अवरोध;
			पूर्ण
			curmsg++; numbytes = 0;
			अगर (curmsg == num)
				pca_stop(adap);
			अन्यथा
				completed = pca_repeated_start(adap);
			अवरोध;

		हाल 0x20: /* SLA+W has been transmitted; NOT ACK has been received */
			DEB2("NOT ACK received after SLA+W\n");
			pca_stop(adap);
			ret = -ENXIO;
			जाओ out;

		हाल 0x40: /* SLA+R has been transmitted; ACK has been received */
			completed = pca_rx_ack(adap, msg->len > 1);
			अवरोध;

		हाल 0x50: /* Data bytes has been received; ACK has been वापसed */
			अगर (numbytes < msg->len) अणु
				pca_rx_byte(adap, &msg->buf[numbytes], 1);
				numbytes++;
				completed = pca_rx_ack(adap,
						       numbytes < msg->len - 1);
				अवरोध;
			पूर्ण
			curmsg++; numbytes = 0;
			अगर (curmsg == num)
				pca_stop(adap);
			अन्यथा
				completed = pca_repeated_start(adap);
			अवरोध;

		हाल 0x48: /* SLA+R has been transmitted; NOT ACK has been received */
			DEB2("NOT ACK received after SLA+R\n");
			pca_stop(adap);
			ret = -ENXIO;
			जाओ out;

		हाल 0x30: /* Data byte in I2CDAT has been transmitted; NOT ACK has been received */
			DEB2("NOT ACK received after data byte\n");
			pca_stop(adap);
			जाओ out;

		हाल 0x38: /* Arbitration lost during SLA+W, SLA+R or data bytes */
			DEB2("Arbitration lost\n");
			/*
			 * The PCA9564 data sheet (2006-09-01) says "A
			 * START condition will be transmitted when the
			 * bus becomes मुक्त (STOP or SCL and SDA high)"
			 * when the STA bit is set (p. 11).
			 *
			 * In हाल this won't work, try pca_reset()
			 * instead.
			 */
			pca_start(adap);
			जाओ out;

		हाल 0x58: /* Data byte has been received; NOT ACK has been वापसed */
			अगर (numbytes == msg->len - 1) अणु
				pca_rx_byte(adap, &msg->buf[numbytes], 0);
				curmsg++; numbytes = 0;
				अगर (curmsg == num)
					pca_stop(adap);
				अन्यथा
					completed = pca_repeated_start(adap);
			पूर्ण अन्यथा अणु
				DEB2("NOT ACK sent after data byte received. "
				     "Not final byte. numbytes %d. len %d\n",
				     numbytes, msg->len);
				pca_stop(adap);
				जाओ out;
			पूर्ण
			अवरोध;
		हाल 0x70: /* Bus error - SDA stuck low */
			DEB2("BUS ERROR - SDA Stuck low\n");
			pca_reset(adap);
			जाओ out;
		हाल 0x78: /* Bus error - SCL stuck low (PCA9665) */
		हाल 0x90: /* Bus error - SCL stuck low (PCA9564) */
			DEB2("BUS ERROR - SCL Stuck low\n");
			pca_reset(adap);
			जाओ out;
		हाल 0x00: /* Bus error during master or slave mode due to illegal START or STOP condition */
			DEB2("BUS ERROR - Illegal START or STOP\n");
			pca_reset(adap);
			जाओ out;
		शेष:
			dev_err(&i2c_adap->dev, "unhandled SIO state 0x%02x\n", state);
			अवरोध;
		पूर्ण

		अगर (!completed)
			जाओ out;
	पूर्ण

	ret = curmsg;
 out:
	DEB1("}}} transferred %d/%d messages. "
	     "status is %#04x. control is %#04x\n",
	     curmsg, num, pca_status(adap),
	     pca_get_con(adap));
	वापस ret;
पूर्ण

अटल u32 pca_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm pca_algo = अणु
	.master_xfer	= pca_xfer,
	.functionality	= pca_func,
पूर्ण;

अटल अचिन्हित पूर्णांक pca_probe_chip(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_algo_pca_data *pca_data = adap->algo_data;
	/* The trick here is to check अगर there is an indirect रेजिस्टर
	 * available. If there is one, we will पढ़ो the value we first
	 * wrote on I2C_PCA_IADR. Otherwise, we will पढ़ो the last value
	 * we wrote on I2C_PCA_ADR
	 */
	pca_outw(pca_data, I2C_PCA_INDPTR, I2C_PCA_IADR);
	pca_outw(pca_data, I2C_PCA_IND, 0xAA);
	pca_outw(pca_data, I2C_PCA_INDPTR, I2C_PCA_ITO);
	pca_outw(pca_data, I2C_PCA_IND, 0x00);
	pca_outw(pca_data, I2C_PCA_INDPTR, I2C_PCA_IADR);
	अगर (pca_inw(pca_data, I2C_PCA_IND) == 0xAA) अणु
		prपूर्णांकk(KERN_INFO "%s: PCA9665 detected.\n", adap->name);
		pca_data->chip = I2C_PCA_CHIP_9665;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "%s: PCA9564 detected.\n", adap->name);
		pca_data->chip = I2C_PCA_CHIP_9564;
	पूर्ण
	वापस pca_data->chip;
पूर्ण

अटल पूर्णांक pca_init(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_algo_pca_data *pca_data = adap->algo_data;

	adap->algo = &pca_algo;

	अगर (pca_probe_chip(adap) == I2C_PCA_CHIP_9564) अणु
		अटल पूर्णांक freqs[] = अणु330, 288, 217, 146, 88, 59, 44, 36पूर्ण;
		पूर्णांक घड़ी;

		अगर (pca_data->i2c_घड़ी > 7) अणु
			चयन (pca_data->i2c_घड़ी) अणु
			हाल 330000:
				pca_data->i2c_घड़ी = I2C_PCA_CON_330kHz;
				अवरोध;
			हाल 288000:
				pca_data->i2c_घड़ी = I2C_PCA_CON_288kHz;
				अवरोध;
			हाल 217000:
				pca_data->i2c_घड़ी = I2C_PCA_CON_217kHz;
				अवरोध;
			हाल 146000:
				pca_data->i2c_घड़ी = I2C_PCA_CON_146kHz;
				अवरोध;
			हाल 88000:
				pca_data->i2c_घड़ी = I2C_PCA_CON_88kHz;
				अवरोध;
			हाल 59000:
				pca_data->i2c_घड़ी = I2C_PCA_CON_59kHz;
				अवरोध;
			हाल 44000:
				pca_data->i2c_घड़ी = I2C_PCA_CON_44kHz;
				अवरोध;
			हाल 36000:
				pca_data->i2c_घड़ी = I2C_PCA_CON_36kHz;
				अवरोध;
			शेष:
				prपूर्णांकk(KERN_WARNING
					"%s: Invalid I2C clock speed selected."
					" Using default 59kHz.\n", adap->name);
			pca_data->i2c_घड़ी = I2C_PCA_CON_59kHz;
			पूर्ण
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "%s: "
				"Choosing the clock frequency based on "
				"index is deprecated."
				" Use the nominal frequency.\n", adap->name);
		पूर्ण

		घड़ी = pca_घड़ी(pca_data);
		prपूर्णांकk(KERN_INFO "%s: Clock frequency is %dkHz\n",
		     adap->name, freqs[घड़ी]);

		/* Store settings as these will be needed when the PCA chip is reset */
		pca_data->bus_settings.घड़ी_freq = घड़ी;

		pca_reset(pca_data);
	पूर्ण अन्यथा अणु
		पूर्णांक घड़ी;
		पूर्णांक mode;
		पूर्णांक tlow, thi;
		/* Values can be found on PCA9665 datasheet section 7.3.2.6 */
		पूर्णांक min_tlow, min_thi;
		/* These values are the maximum उठाओ and fall values allowed
		 * by the I2C operation mode (Standard, Fast or Fast+)
		 * They are used (added) below to calculate the घड़ी भागiders
		 * of PCA9665. Note that they are slightly dअगरferent of the
		 * real maximum, to allow the change on mode exactly on the
		 * maximum घड़ी rate क्रम each mode
		 */
		पूर्णांक उठाओ_fall_समय;

		अगर (pca_data->i2c_घड़ी > 1265800) अणु
			prपूर्णांकk(KERN_WARNING "%s: I2C clock speed too high."
				" Using 1265.8kHz.\n", adap->name);
			pca_data->i2c_घड़ी = 1265800;
		पूर्ण

		अगर (pca_data->i2c_घड़ी < 60300) अणु
			prपूर्णांकk(KERN_WARNING "%s: I2C clock speed too low."
				" Using 60.3kHz.\n", adap->name);
			pca_data->i2c_घड़ी = 60300;
		पूर्ण

		/* To aव्योम पूर्णांकeger overflow, use घड़ी/100 क्रम calculations */
		घड़ी = pca_घड़ी(pca_data) / 100;

		अगर (pca_data->i2c_घड़ी > I2C_MAX_FAST_MODE_PLUS_FREQ) अणु
			mode = I2C_PCA_MODE_TURBO;
			min_tlow = 14;
			min_thi  = 5;
			उठाओ_fall_समय = 22; /* Raise 11e-8s, Fall 11e-8s */
		पूर्ण अन्यथा अगर (pca_data->i2c_घड़ी > I2C_MAX_FAST_MODE_FREQ) अणु
			mode = I2C_PCA_MODE_FASTP;
			min_tlow = 17;
			min_thi  = 9;
			उठाओ_fall_समय = 22; /* Raise 11e-8s, Fall 11e-8s */
		पूर्ण अन्यथा अगर (pca_data->i2c_घड़ी > I2C_MAX_STANDARD_MODE_FREQ) अणु
			mode = I2C_PCA_MODE_FAST;
			min_tlow = 44;
			min_thi  = 20;
			उठाओ_fall_समय = 58; /* Raise 29e-8s, Fall 29e-8s */
		पूर्ण अन्यथा अणु
			mode = I2C_PCA_MODE_STD;
			min_tlow = 157;
			min_thi  = 134;
			उठाओ_fall_समय = 127; /* Raise 29e-8s, Fall 98e-8s */
		पूर्ण

		/* The minimum घड़ी that respects the thi/tlow = 134/157 is
		 * 64800 Hz. Below that, we have to fix the tlow to 255 and
		 * calculate the thi factor.
		 */
		अगर (घड़ी < 648) अणु
			tlow = 255;
			thi = 1000000 - घड़ी * उठाओ_fall_समय;
			thi /= (I2C_PCA_OSC_PER * घड़ी) - tlow;
		पूर्ण अन्यथा अणु
			tlow = (1000000 - घड़ी * उठाओ_fall_समय) * min_tlow;
			tlow /= I2C_PCA_OSC_PER * घड़ी * (min_thi + min_tlow);
			thi = tlow * min_thi / min_tlow;
		पूर्ण

		/* Store settings as these will be needed when the PCA chip is reset */
		pca_data->bus_settings.mode = mode;
		pca_data->bus_settings.tlow = tlow;
		pca_data->bus_settings.thi = thi;

		pca_reset(pca_data);

		prपूर्णांकk(KERN_INFO
		     "%s: Clock frequency is %dHz\n", adap->name, घड़ी * 100);
	पूर्ण
	udelay(500); /* 500 us क्रम oscillator to stabilise */

	वापस 0;
पूर्ण

/*
 * रेजिस्टरing functions to load algorithms at runसमय
 */
पूर्णांक i2c_pca_add_bus(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक rval;

	rval = pca_init(adap);
	अगर (rval)
		वापस rval;

	वापस i2c_add_adapter(adap);
पूर्ण
EXPORT_SYMBOL(i2c_pca_add_bus);

पूर्णांक i2c_pca_add_numbered_bus(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक rval;

	rval = pca_init(adap);
	अगर (rval)
		वापस rval;

	वापस i2c_add_numbered_adapter(adap);
पूर्ण
EXPORT_SYMBOL(i2c_pca_add_numbered_bus);

MODULE_AUTHOR("Ian Campbell <icampbell@arcom.com>");
MODULE_AUTHOR("Wolfram Sang <kernel@pengutronix.de>");
MODULE_DESCRIPTION("I2C-Bus PCA9564/PCA9665 algorithm");
MODULE_LICENSE("GPL");

module_param(i2c_debug, पूर्णांक, 0);
