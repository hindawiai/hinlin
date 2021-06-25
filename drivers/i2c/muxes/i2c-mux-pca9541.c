<शैली गुरु>
/*
 * I2C multiplexer driver क्रम PCA9541 bus master selector
 *
 * Copyright (c) 2010 Ericsson AB.
 *
 * Author: Guenter Roeck <linux@roeck-us.net>
 *
 * Derived from:
 *  pca954x.c
 *
 *  Copyright (c) 2008-2009 Roकरोlfo Giometti <giometti@linux.it>
 *  Copyright (c) 2008-2009 Eurotech S.p.A. <info@eurotech.it>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

/*
 * The PCA9541 is a bus master selector. It supports two I2C masters connected
 * to a single slave bus.
 *
 * Beक्रमe each bus transaction, a master has to acquire bus ownership. After the
 * transaction is complete, bus ownership has to be released. This fits well
 * पूर्णांकo the I2C multiplexer framework, which provides select and release
 * functions क्रम this purpose. For this reason, this driver is modeled as
 * single-channel I2C bus multiplexer.
 *
 * This driver assumes that the two bus masters are controlled by two dअगरferent
 * hosts. If a single host controls both masters, platक्रमm code has to ensure
 * that only one of the masters is instantiated at any given समय.
 */

#घोषणा PCA9541_CONTROL		0x01
#घोषणा PCA9541_ISTAT		0x02

#घोषणा PCA9541_CTL_MYBUS	BIT(0)
#घोषणा PCA9541_CTL_NMYBUS	BIT(1)
#घोषणा PCA9541_CTL_BUSON	BIT(2)
#घोषणा PCA9541_CTL_NBUSON	BIT(3)
#घोषणा PCA9541_CTL_BUSINIT	BIT(4)
#घोषणा PCA9541_CTL_TESTON	BIT(6)
#घोषणा PCA9541_CTL_NTESTON	BIT(7)

#घोषणा PCA9541_ISTAT_INTIN	BIT(0)
#घोषणा PCA9541_ISTAT_BUSINIT	BIT(1)
#घोषणा PCA9541_ISTAT_BUSOK	BIT(2)
#घोषणा PCA9541_ISTAT_BUSLOST	BIT(3)
#घोषणा PCA9541_ISTAT_MYTEST	BIT(6)
#घोषणा PCA9541_ISTAT_NMYTEST	BIT(7)

#घोषणा BUSON		(PCA9541_CTL_BUSON | PCA9541_CTL_NBUSON)
#घोषणा MYBUS		(PCA9541_CTL_MYBUS | PCA9541_CTL_NMYBUS)
#घोषणा mybus(x)	(!((x) & MYBUS) || ((x) & MYBUS) == MYBUS)
#घोषणा busoff(x)	(!((x) & BUSON) || ((x) & BUSON) == BUSON)

/* arbitration समयouts, in jअगरfies */
#घोषणा ARB_TIMEOUT	(HZ / 8)	/* 125 ms until क्रमcing bus ownership */
#घोषणा ARB2_TIMEOUT	(HZ / 4)	/* 250 ms until acquisition failure */

/* arbitration retry delays, in us */
#घोषणा SELECT_DELAY_SHORT	50
#घोषणा SELECT_DELAY_LONG	1000

काष्ठा pca9541 अणु
	काष्ठा i2c_client *client;
	अचिन्हित दीर्घ select_समयout;
	अचिन्हित दीर्घ arb_समयout;
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id pca9541_id[] = अणु
	अणु"pca9541", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, pca9541_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pca9541_of_match[] = अणु
	अणु .compatible = "nxp,pca9541" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pca9541_of_match);
#पूर्ण_अगर

/*
 * Write to chip रेजिस्टर. Don't use i2c_transfer()/i2c_smbus_xfer()
 * as they will try to lock the adapter a second समय.
 */
अटल पूर्णांक pca9541_reg_ग_लिखो(काष्ठा i2c_client *client, u8 command, u8 val)
अणु
	काष्ठा i2c_adapter *adap = client->adapter;
	जोड़ i2c_smbus_data data = अणु .byte = val पूर्ण;

	वापस __i2c_smbus_xfer(adap, client->addr, client->flags,
				I2C_SMBUS_WRITE, command,
				I2C_SMBUS_BYTE_DATA, &data);
पूर्ण

/*
 * Read from chip रेजिस्टर. Don't use i2c_transfer()/i2c_smbus_xfer()
 * as they will try to lock adapter a second समय.
 */
अटल पूर्णांक pca9541_reg_पढ़ो(काष्ठा i2c_client *client, u8 command)
अणु
	काष्ठा i2c_adapter *adap = client->adapter;
	जोड़ i2c_smbus_data data;
	पूर्णांक ret;

	ret = __i2c_smbus_xfer(adap, client->addr, client->flags,
			       I2C_SMBUS_READ, command,
			       I2C_SMBUS_BYTE_DATA, &data);

	वापस ret ?: data.byte;
पूर्ण

/*
 * Arbitration management functions
 */

/* Release bus. Also reset NTESTON and BUSINIT अगर it was set. */
अटल व्योम pca9541_release_bus(काष्ठा i2c_client *client)
अणु
	पूर्णांक reg;

	reg = pca9541_reg_पढ़ो(client, PCA9541_CONTROL);
	अगर (reg >= 0 && !busoff(reg) && mybus(reg))
		pca9541_reg_ग_लिखो(client, PCA9541_CONTROL,
				  (reg & PCA9541_CTL_NBUSON) >> 1);
पूर्ण

/*
 * Arbitration is defined as a two-step process. A bus master can only activate
 * the slave bus अगर it owns it; otherwise it has to request ownership first.
 * This multi-step process ensures that access contention is resolved
 * gracefully.
 *
 * Bus	Ownership	Other master	Action
 * state		requested access
 * ----------------------------------------------------
 * off	-		yes		रुको क्रम arbitration समयout or
 *					क्रम other master to drop request
 * off	no		no		take ownership
 * off	yes		no		turn on bus
 * on	yes		-		करोne
 * on	no		-		रुको क्रम arbitration समयout or
 *					क्रम other master to release bus
 *
 * The मुख्य contention poपूर्णांक occurs अगर the slave bus is off and both masters
 * request ownership at the same समय. In this हाल, one master will turn on
 * the slave bus, believing that it owns it. The other master will request
 * bus ownership. Result is that the bus is turned on, and master which did
 * _not_ own the slave bus beक्रमe ends up owning it.
 */

/* Control commands per PCA9541 datasheet */
अटल स्थिर u8 pca9541_control[16] = अणु
	4, 0, 1, 5, 4, 4, 5, 5, 0, 0, 1, 1, 0, 4, 5, 1
पूर्ण;

/*
 * Channel arbitration
 *
 * Return values:
 *  <0: error
 *  0 : bus not acquired
 *  1 : bus acquired
 */
अटल पूर्णांक pca9541_arbitrate(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_mux_core *muxc = i2c_get_clientdata(client);
	काष्ठा pca9541 *data = i2c_mux_priv(muxc);
	पूर्णांक reg;

	reg = pca9541_reg_पढ़ो(client, PCA9541_CONTROL);
	अगर (reg < 0)
		वापस reg;

	अगर (busoff(reg)) अणु
		पूर्णांक istat;
		/*
		 * Bus is off. Request ownership or turn it on unless
		 * other master requested ownership.
		 */
		istat = pca9541_reg_पढ़ो(client, PCA9541_ISTAT);
		अगर (!(istat & PCA9541_ISTAT_NMYTEST)
		    || समय_is_beक्रमe_eq_jअगरfies(data->arb_समयout)) अणु
			/*
			 * Other master did not request ownership,
			 * or arbitration समयout expired. Take the bus.
			 */
			pca9541_reg_ग_लिखो(client,
					  PCA9541_CONTROL,
					  pca9541_control[reg & 0x0f]
					  | PCA9541_CTL_NTESTON);
			data->select_समयout = SELECT_DELAY_SHORT;
		पूर्ण अन्यथा अणु
			/*
			 * Other master requested ownership.
			 * Set extra दीर्घ समयout to give it समय to acquire it.
			 */
			data->select_समयout = SELECT_DELAY_LONG * 2;
		पूर्ण
	पूर्ण अन्यथा अगर (mybus(reg)) अणु
		/*
		 * Bus is on, and we own it. We are करोne with acquisition.
		 * Reset NTESTON and BUSINIT, then वापस success.
		 */
		अगर (reg & (PCA9541_CTL_NTESTON | PCA9541_CTL_BUSINIT))
			pca9541_reg_ग_लिखो(client,
					  PCA9541_CONTROL,
					  reg & ~(PCA9541_CTL_NTESTON
						  | PCA9541_CTL_BUSINIT));
		वापस 1;
	पूर्ण अन्यथा अणु
		/*
		 * Other master owns the bus.
		 * If arbitration समयout has expired, क्रमce ownership.
		 * Otherwise request it.
		 */
		data->select_समयout = SELECT_DELAY_LONG;
		अगर (समय_is_beक्रमe_eq_jअगरfies(data->arb_समयout)) अणु
			/* Time is up, take the bus and reset it. */
			pca9541_reg_ग_लिखो(client,
					  PCA9541_CONTROL,
					  pca9541_control[reg & 0x0f]
					  | PCA9541_CTL_BUSINIT
					  | PCA9541_CTL_NTESTON);
		पूर्ण अन्यथा अणु
			/* Request bus ownership अगर needed */
			अगर (!(reg & PCA9541_CTL_NTESTON))
				pca9541_reg_ग_लिखो(client,
						  PCA9541_CONTROL,
						  reg | PCA9541_CTL_NTESTON);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pca9541_select_chan(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा pca9541 *data = i2c_mux_priv(muxc);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout = jअगरfies + ARB2_TIMEOUT;
		/* give up after this समय */

	data->arb_समयout = jअगरfies + ARB_TIMEOUT;
		/* क्रमce bus ownership after this समय */

	करो अणु
		ret = pca9541_arbitrate(client);
		अगर (ret)
			वापस ret < 0 ? ret : 0;

		अगर (data->select_समयout == SELECT_DELAY_SHORT)
			udelay(data->select_समयout);
		अन्यथा
			msleep(data->select_समयout / 1000);
	पूर्ण जबतक (समय_is_after_eq_jअगरfies(समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक pca9541_release_chan(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा pca9541 *data = i2c_mux_priv(muxc);
	काष्ठा i2c_client *client = data->client;

	pca9541_release_bus(client);
	वापस 0;
पूर्ण

/*
 * I2C init/probing/निकास functions
 */
अटल पूर्णांक pca9541_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adap = client->adapter;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा pca9541 *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adap, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/*
	 * I2C accesses are unरक्षित here.
	 * We have to lock the I2C segment beक्रमe releasing the bus.
	 */
	i2c_lock_bus(adap, I2C_LOCK_SEGMENT);
	pca9541_release_bus(client);
	i2c_unlock_bus(adap, I2C_LOCK_SEGMENT);

	/* Create mux adapter */

	muxc = i2c_mux_alloc(adap, &client->dev, 1, माप(*data),
			     I2C_MUX_ARBITRATOR,
			     pca9541_select_chan, pca9541_release_chan);
	अगर (!muxc)
		वापस -ENOMEM;

	data = i2c_mux_priv(muxc);
	data->client = client;

	i2c_set_clientdata(client, muxc);

	ret = i2c_mux_add_adapter(muxc, 0, 0, 0);
	अगर (ret)
		वापस ret;

	dev_info(&client->dev, "registered master selector for I2C %s\n",
		 client->name);

	वापस 0;
पूर्ण

अटल पूर्णांक pca9541_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_mux_core *muxc = i2c_get_clientdata(client);

	i2c_mux_del_adapters(muxc);
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver pca9541_driver = अणु
	.driver = अणु
		   .name = "pca9541",
		   .of_match_table = of_match_ptr(pca9541_of_match),
		   पूर्ण,
	.probe = pca9541_probe,
	.हटाओ = pca9541_हटाओ,
	.id_table = pca9541_id,
पूर्ण;

module_i2c_driver(pca9541_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("PCA9541 I2C master selector driver");
MODULE_LICENSE("GPL v2");
