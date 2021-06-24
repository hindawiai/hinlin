<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <यंत्र/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"
#समावेश "mantis_reg.h"
#समावेश "mantis_i2c.h"

#घोषणा TRIALS			10000

अटल पूर्णांक mantis_i2c_पढ़ो(काष्ठा mantis_pci *mantis, स्थिर काष्ठा i2c_msg *msg)
अणु
	u32 rxd, i, stat, trials;

	dprपूर्णांकk(MANTIS_INFO, 0, "        %s:  Address=[0x%02x] <R>[ ",
		__func__, msg->addr);

	क्रम (i = 0; i < msg->len; i++) अणु
		rxd = (msg->addr << 25) | (1 << 24)
					| MANTIS_I2C_RATE_3
					| MANTIS_I2C_STOP
					| MANTIS_I2C_PGMODE;

		अगर (i == (msg->len - 1))
			rxd &= ~MANTIS_I2C_STOP;

		mmग_लिखो(MANTIS_INT_I2CDONE, MANTIS_INT_STAT);
		mmग_लिखो(rxd, MANTIS_I2CDATA_CTL);

		/* रुको क्रम xfer completion */
		क्रम (trials = 0; trials < TRIALS; trials++) अणु
			stat = mmपढ़ो(MANTIS_INT_STAT);
			अगर (stat & MANTIS_INT_I2CDONE)
				अवरोध;
		पूर्ण

		dprपूर्णांकk(MANTIS_TMG, 0, "I2CDONE: trials=%d\n", trials);

		/* रुको क्रम xfer completion */
		क्रम (trials = 0; trials < TRIALS; trials++) अणु
			stat = mmपढ़ो(MANTIS_INT_STAT);
			अगर (stat & MANTIS_INT_I2CRACK)
				अवरोध;
		पूर्ण

		dprपूर्णांकk(MANTIS_TMG, 0, "I2CRACK: trials=%d\n", trials);

		rxd = mmपढ़ो(MANTIS_I2CDATA_CTL);
		msg->buf[i] = (u8)((rxd >> 8) & 0xFF);
		dprपूर्णांकk(MANTIS_INFO, 0, "%02x ", msg->buf[i]);
	पूर्ण
	dprपूर्णांकk(MANTIS_INFO, 0, "]\n");

	वापस 0;
पूर्ण

अटल पूर्णांक mantis_i2c_ग_लिखो(काष्ठा mantis_pci *mantis, स्थिर काष्ठा i2c_msg *msg)
अणु
	पूर्णांक i;
	u32 txd = 0, stat, trials;

	dprपूर्णांकk(MANTIS_INFO, 0, "        %s: Address=[0x%02x] <W>[ ",
		__func__, msg->addr);

	क्रम (i = 0; i < msg->len; i++) अणु
		dprपूर्णांकk(MANTIS_INFO, 0, "%02x ", msg->buf[i]);
		txd = (msg->addr << 25) | (msg->buf[i] << 8)
					| MANTIS_I2C_RATE_3
					| MANTIS_I2C_STOP
					| MANTIS_I2C_PGMODE;

		अगर (i == (msg->len - 1))
			txd &= ~MANTIS_I2C_STOP;

		mmग_लिखो(MANTIS_INT_I2CDONE, MANTIS_INT_STAT);
		mmग_लिखो(txd, MANTIS_I2CDATA_CTL);

		/* रुको क्रम xfer completion */
		क्रम (trials = 0; trials < TRIALS; trials++) अणु
			stat = mmपढ़ो(MANTIS_INT_STAT);
			अगर (stat & MANTIS_INT_I2CDONE)
				अवरोध;
		पूर्ण

		dprपूर्णांकk(MANTIS_TMG, 0, "I2CDONE: trials=%d\n", trials);

		/* रुको क्रम xfer completion */
		क्रम (trials = 0; trials < TRIALS; trials++) अणु
			stat = mmपढ़ो(MANTIS_INT_STAT);
			अगर (stat & MANTIS_INT_I2CRACK)
				अवरोध;
		पूर्ण

		dprपूर्णांकk(MANTIS_TMG, 0, "I2CRACK: trials=%d\n", trials);
	पूर्ण
	dprपूर्णांकk(MANTIS_INFO, 0, "]\n");

	वापस 0;
पूर्ण

अटल पूर्णांक mantis_i2c_xfer(काष्ठा i2c_adapter *adapter, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक ret = 0, i = 0, trials;
	u32 stat, data, txd;
	काष्ठा mantis_pci *mantis;
	काष्ठा mantis_hwconfig *config;

	mantis = i2c_get_adapdata(adapter);
	BUG_ON(!mantis);
	config = mantis->hwconfig;
	BUG_ON(!config);

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Messages:%d", num);
	mutex_lock(&mantis->i2c_lock);

	जबतक (i < num) अणु
		/* Byte MODE */
		अगर ((config->i2c_mode & MANTIS_BYTE_MODE) &&
		    ((i + 1) < num)			&&
		    (msgs[i].len < 2)			&&
		    (msgs[i + 1].len < 2)		&&
		    (msgs[i + 1].flags & I2C_M_RD)) अणु

			dprपूर्णांकk(MANTIS_DEBUG, 0, "        Byte MODE:\n");

			/* Read operation */
			txd = msgs[i].addr << 25 | (0x1 << 24)
						 | (msgs[i].buf[0] << 16)
						 | MANTIS_I2C_RATE_3;

			mmग_लिखो(txd, MANTIS_I2CDATA_CTL);
			/* रुको क्रम xfer completion */
			क्रम (trials = 0; trials < TRIALS; trials++) अणु
				stat = mmपढ़ो(MANTIS_INT_STAT);
				अगर (stat & MANTIS_INT_I2CDONE)
					अवरोध;
			पूर्ण

			/* check क्रम xfer completion */
			अगर (stat & MANTIS_INT_I2CDONE) अणु
				/* check xfer was acknowledged */
				अगर (stat & MANTIS_INT_I2CRACK) अणु
					data = mmपढ़ो(MANTIS_I2CDATA_CTL);
					msgs[i + 1].buf[0] = (data >> 8) & 0xff;
					dprपूर्णांकk(MANTIS_DEBUG, 0, "        Byte <%d> RXD=0x%02x  [%02x]\n", 0x0, data, msgs[i + 1].buf[0]);
				पूर्ण अन्यथा अणु
					/* I/O error */
					dprपूर्णांकk(MANTIS_ERROR, 1, "        I/O error, LINE:%d", __LINE__);
					ret = -EIO;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* I/O error */
				dprपूर्णांकk(MANTIS_ERROR, 1, "        I/O error, LINE:%d", __LINE__);
				ret = -EIO;
				अवरोध;
			पूर्ण
			i += 2; /* Write/Read operation in one go */
		पूर्ण

		अगर (i < num) अणु
			अगर (msgs[i].flags & I2C_M_RD)
				ret = mantis_i2c_पढ़ो(mantis, &msgs[i]);
			अन्यथा
				ret = mantis_i2c_ग_लिखो(mantis, &msgs[i]);

			i++;
			अगर (ret < 0)
				जाओ bail_out;
		पूर्ण

	पूर्ण

	mutex_unlock(&mantis->i2c_lock);

	वापस num;

bail_out:
	mutex_unlock(&mantis->i2c_lock);
	वापस ret;
पूर्ण

अटल u32 mantis_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mantis_algo = अणु
	.master_xfer		= mantis_i2c_xfer,
	.functionality		= mantis_i2c_func,
पूर्ण;

पूर्णांक mantis_i2c_init(काष्ठा mantis_pci *mantis)
अणु
	u32 पूर्णांकstat;
	काष्ठा i2c_adapter *i2c_adapter = &mantis->adapter;
	काष्ठा pci_dev *pdev		= mantis->pdev;

	init_रुकोqueue_head(&mantis->i2c_wq);
	mutex_init(&mantis->i2c_lock);
	strscpy(i2c_adapter->name, "Mantis I2C", माप(i2c_adapter->name));
	i2c_set_adapdata(i2c_adapter, mantis);

	i2c_adapter->owner	= THIS_MODULE;
	i2c_adapter->algo	= &mantis_algo;
	i2c_adapter->algo_data	= शून्य;
	i2c_adapter->समयout	= 500;
	i2c_adapter->retries	= 3;
	i2c_adapter->dev.parent	= &pdev->dev;

	mantis->i2c_rc		= i2c_add_adapter(i2c_adapter);
	अगर (mantis->i2c_rc < 0)
		वापस mantis->i2c_rc;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Initializing I2C ..");

	पूर्णांकstat = mmपढ़ो(MANTIS_INT_STAT);
	mmपढ़ो(MANTIS_INT_MASK);
	mmग_लिखो(पूर्णांकstat, MANTIS_INT_STAT);
	dprपूर्णांकk(MANTIS_DEBUG, 1, "Disabling I2C interrupt");
	mantis_mask_पूर्णांकs(mantis, MANTIS_INT_I2CDONE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_i2c_init);

पूर्णांक mantis_i2c_निकास(काष्ठा mantis_pci *mantis)
अणु
	dprपूर्णांकk(MANTIS_DEBUG, 1, "Disabling I2C interrupt");
	mantis_mask_पूर्णांकs(mantis, MANTIS_INT_I2CDONE);

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Removing I2C adapter");
	i2c_del_adapter(&mantis->adapter);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_i2c_निकास);
