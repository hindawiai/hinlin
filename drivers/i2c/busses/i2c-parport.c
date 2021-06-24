<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ------------------------------------------------------------------------ *
 * i2c-parport.c I2C bus over parallel port                                 *
 * ------------------------------------------------------------------------ *
   Copyright (C) 2003-2011 Jean Delvare <jdelvare@suse.de>

   Based on older i2c-philips-par.c driver
   Copyright (C) 1995-2000 Simon G. Vogl
   With some changes from:
   Froकरो Looijaard <froकरोl@dds.nl>
   Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>

 * ------------------------------------------------------------------------ */

#घोषणा pr_fmt(fmt) "i2c-parport: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/parport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>

#घोषणा PORT_DATA	0
#घोषणा PORT_STAT	1
#घोषणा PORT_CTRL	2

काष्ठा lineop अणु
	u8 val;
	u8 port;
	u8 inverted;
पूर्ण;

काष्ठा adapter_parm अणु
	काष्ठा lineop setsda;
	काष्ठा lineop setscl;
	काष्ठा lineop माला_लोda;
	काष्ठा lineop माला_लोcl;
	काष्ठा lineop init;
	अचिन्हित पूर्णांक smbus_alert:1;
पूर्ण;

अटल स्थिर काष्ठा adapter_parm adapter_parm[] = अणु
	/* type 0: Philips adapter */
	अणु
		.setsda	= अणु 0x80, PORT_DATA, 1 पूर्ण,
		.setscl	= अणु 0x08, PORT_CTRL, 0 पूर्ण,
		.माला_लोda	= अणु 0x80, PORT_STAT, 0 पूर्ण,
		.माला_लोcl	= अणु 0x08, PORT_STAT, 0 पूर्ण,
	पूर्ण,
	/* type 1: home brew teletext adapter */
	अणु
		.setsda	= अणु 0x02, PORT_DATA, 0 पूर्ण,
		.setscl	= अणु 0x01, PORT_DATA, 0 पूर्ण,
		.माला_लोda	= अणु 0x80, PORT_STAT, 1 पूर्ण,
	पूर्ण,
	/* type 2: Velleman K8000 adapter */
	अणु
		.setsda	= अणु 0x02, PORT_CTRL, 1 पूर्ण,
		.setscl	= अणु 0x08, PORT_CTRL, 1 पूर्ण,
		.माला_लोda	= अणु 0x10, PORT_STAT, 0 पूर्ण,
	पूर्ण,
	/* type 3: ELV adapter */
	अणु
		.setsda	= अणु 0x02, PORT_DATA, 1 पूर्ण,
		.setscl	= अणु 0x01, PORT_DATA, 1 पूर्ण,
		.माला_लोda	= अणु 0x40, PORT_STAT, 1 पूर्ण,
		.माला_लोcl	= अणु 0x08, PORT_STAT, 1 पूर्ण,
	पूर्ण,
	/* type 4: ADM1032 evaluation board */
	अणु
		.setsda	= अणु 0x02, PORT_DATA, 1 पूर्ण,
		.setscl	= अणु 0x01, PORT_DATA, 1 पूर्ण,
		.माला_लोda	= अणु 0x10, PORT_STAT, 1 पूर्ण,
		.init	= अणु 0xf0, PORT_DATA, 0 पूर्ण,
		.smbus_alert = 1,
	पूर्ण,
	/* type 5: ADM1025, ADM1030 and ADM1031 evaluation boards */
	अणु
		.setsda	= अणु 0x02, PORT_DATA, 1 पूर्ण,
		.setscl	= अणु 0x01, PORT_DATA, 1 पूर्ण,
		.माला_लोda	= अणु 0x10, PORT_STAT, 1 पूर्ण,
	पूर्ण,
	/* type 6: Barco LPT->DVI (K5800236) adapter */
	अणु
		.setsda	= अणु 0x02, PORT_DATA, 1 पूर्ण,
		.setscl	= अणु 0x01, PORT_DATA, 1 पूर्ण,
		.माला_लोda	= अणु 0x20, PORT_STAT, 0 पूर्ण,
		.माला_लोcl	= अणु 0x40, PORT_STAT, 0 पूर्ण,
		.init	= अणु 0xfc, PORT_DATA, 0 पूर्ण,
	पूर्ण,
	/* type 7: One For All JP1 parallel port adapter */
	अणु
		.setsda	= अणु 0x01, PORT_DATA, 0 पूर्ण,
		.setscl	= अणु 0x02, PORT_DATA, 0 पूर्ण,
		.माला_लोda	= अणु 0x80, PORT_STAT, 1 पूर्ण,
		.init	= अणु 0x04, PORT_DATA, 1 पूर्ण,
	पूर्ण,
	/* type 8: VCT-jig */
	अणु
		.setsda	= अणु 0x04, PORT_DATA, 1 पूर्ण,
		.setscl	= अणु 0x01, PORT_DATA, 1 पूर्ण,
		.माला_लोda	= अणु 0x40, PORT_STAT, 0 पूर्ण,
		.माला_लोcl	= अणु 0x80, PORT_STAT, 1 पूर्ण,
	पूर्ण,
पूर्ण;

/* ----- Device list ------------------------------------------------------ */

काष्ठा i2c_par अणु
	काष्ठा pardevice *pdev;
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data algo_data;
	काष्ठा i2c_smbus_alert_setup alert_data;
	काष्ठा i2c_client *ara;
	काष्ठा list_head node;
पूर्ण;

अटल LIST_HEAD(adapter_list);
अटल DEFINE_MUTEX(adapter_list_lock);

#घोषणा MAX_DEVICE 4
अटल पूर्णांक parport[MAX_DEVICE] = अणु0, -1, -1, -1पूर्ण;
module_param_array(parport, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(parport,
		 "List of parallel ports to bind to, by index.\n"
		 " At most " __stringअगरy(MAX_DEVICE) " devices are supported.\n"
		 " Default is one device connected to parport0.\n"
);

अटल पूर्णांक type = -1;
module_param(type, पूर्णांक, 0);
MODULE_PARM_DESC(type,
	"Type of adapter:\n"
	" 0 = Philips adapter\n"
	" 1 = home brew teletext adapter\n"
	" 2 = Velleman K8000 adapter\n"
	" 3 = ELV adapter\n"
	" 4 = ADM1032 evaluation board\n"
	" 5 = ADM1025, ADM1030 and ADM1031 evaluation boards\n"
	" 6 = Barco LPT->DVI (K5800236) adapter\n"
	" 7 = One For All JP1 parallel port adapter\n"
	" 8 = VCT-jig\n"
);

/* ----- Low-level parallel port access ----------------------------------- */

अटल व्योम port_ग_लिखो_data(काष्ठा parport *p, अचिन्हित अक्षर d)
अणु
	parport_ग_लिखो_data(p, d);
पूर्ण

अटल व्योम port_ग_लिखो_control(काष्ठा parport *p, अचिन्हित अक्षर d)
अणु
	parport_ग_लिखो_control(p, d);
पूर्ण

अटल अचिन्हित अक्षर port_पढ़ो_data(काष्ठा parport *p)
अणु
	वापस parport_पढ़ो_data(p);
पूर्ण

अटल अचिन्हित अक्षर port_पढ़ो_status(काष्ठा parport *p)
अणु
	वापस parport_पढ़ो_status(p);
पूर्ण

अटल अचिन्हित अक्षर port_पढ़ो_control(काष्ठा parport *p)
अणु
	वापस parport_पढ़ो_control(p);
पूर्ण

अटल व्योम (* स्थिर port_ग_लिखो[])(काष्ठा parport *, अचिन्हित अक्षर) = अणु
	port_ग_लिखो_data,
	शून्य,
	port_ग_लिखो_control,
पूर्ण;

अटल अचिन्हित अक्षर (* स्थिर port_पढ़ो[])(काष्ठा parport *) = अणु
	port_पढ़ो_data,
	port_पढ़ो_status,
	port_पढ़ो_control,
पूर्ण;

/* ----- Unअगरied line operation functions --------------------------------- */

अटल अंतरभूत व्योम line_set(काष्ठा parport *data, पूर्णांक state,
	स्थिर काष्ठा lineop *op)
अणु
	u8 oldval = port_पढ़ो[op->port](data);

	/* Touch only the bit(s) needed */
	अगर ((op->inverted && !state) || (!op->inverted && state))
		port_ग_लिखो[op->port](data, oldval | op->val);
	अन्यथा
		port_ग_लिखो[op->port](data, oldval & ~op->val);
पूर्ण

अटल अंतरभूत पूर्णांक line_get(काष्ठा parport *data,
	स्थिर काष्ठा lineop *op)
अणु
	u8 oldval = port_पढ़ो[op->port](data);

	वापस ((op->inverted && (oldval & op->val) != op->val)
	    || (!op->inverted && (oldval & op->val) == op->val));
पूर्ण

/* ----- I2C algorithm call-back functions and काष्ठाures ----------------- */

अटल व्योम parport_setscl(व्योम *data, पूर्णांक state)
अणु
	line_set((काष्ठा parport *) data, state, &adapter_parm[type].setscl);
पूर्ण

अटल व्योम parport_setsda(व्योम *data, पूर्णांक state)
अणु
	line_set((काष्ठा parport *) data, state, &adapter_parm[type].setsda);
पूर्ण

अटल पूर्णांक parport_माला_लोcl(व्योम *data)
अणु
	वापस line_get((काष्ठा parport *) data, &adapter_parm[type].माला_लोcl);
पूर्ण

अटल पूर्णांक parport_माला_लोda(व्योम *data)
अणु
	वापस line_get((काष्ठा parport *) data, &adapter_parm[type].माला_लोda);
पूर्ण

/* Encapsulate the functions above in the correct काष्ठाure.
   Note that this is only a ढाँचा, from which the real काष्ठाures are
   copied. The attaching code will set माला_लोcl to शून्य क्रम adapters that
   cannot पढ़ो SCL back, and will also make the data field poपूर्णांक to
   the parallel port काष्ठाure. */
अटल स्थिर काष्ठा i2c_algo_bit_data parport_algo_data = अणु
	.setsda		= parport_setsda,
	.setscl		= parport_setscl,
	.माला_लोda		= parport_माला_लोda,
	.माला_लोcl		= parport_माला_लोcl,
	.udelay		= 10, /* ~50 kbps */
	.समयout	= HZ,
पूर्ण;

/* ----- I2c and parallel port call-back functions and काष्ठाures --------- */

अटल व्योम i2c_parport_irq(व्योम *data)
अणु
	काष्ठा i2c_par *adapter = data;
	काष्ठा i2c_client *ara = adapter->ara;

	अगर (ara) अणु
		dev_dbg(&ara->dev, "SMBus alert received\n");
		i2c_handle_smbus_alert(ara);
	पूर्ण अन्यथा
		dev_dbg(&adapter->adapter.dev,
			"SMBus alert received but no ARA client!\n");
पूर्ण

अटल व्योम i2c_parport_attach(काष्ठा parport *port)
अणु
	काष्ठा i2c_par *adapter;
	पूर्णांक i;
	काष्ठा pardev_cb i2c_parport_cb;

	क्रम (i = 0; i < MAX_DEVICE; i++) अणु
		अगर (parport[i] == -1)
			जारी;
		अगर (port->number == parport[i])
			अवरोध;
	पूर्ण
	अगर (i == MAX_DEVICE) अणु
		pr_debug("Not using parport%d.\n", port->number);
		वापस;
	पूर्ण

	adapter = kzalloc(माप(काष्ठा i2c_par), GFP_KERNEL);
	अगर (!adapter)
		वापस;
	स_रखो(&i2c_parport_cb, 0, माप(i2c_parport_cb));
	i2c_parport_cb.flags = PARPORT_FLAG_EXCL;
	i2c_parport_cb.irq_func = i2c_parport_irq;
	i2c_parport_cb.निजी = adapter;

	pr_debug("attaching to %s\n", port->name);
	parport_disable_irq(port);
	adapter->pdev = parport_रेजिस्टर_dev_model(port, "i2c-parport",
						   &i2c_parport_cb, i);
	अगर (!adapter->pdev) अणु
		pr_err("Unable to register with parport\n");
		जाओ err_मुक्त;
	पूर्ण

	/* Fill the rest of the काष्ठाure */
	adapter->adapter.owner = THIS_MODULE;
	adapter->adapter.class = I2C_CLASS_HWMON;
	strlcpy(adapter->adapter.name, "Parallel port adapter",
		माप(adapter->adapter.name));
	adapter->algo_data = parport_algo_data;
	/* Slow करोwn अगर we can't sense SCL */
	अगर (!adapter_parm[type].माला_लोcl.val) अणु
		adapter->algo_data.माला_लोcl = शून्य;
		adapter->algo_data.udelay = 50; /* ~10 kbps */
	पूर्ण
	adapter->algo_data.data = port;
	adapter->adapter.algo_data = &adapter->algo_data;
	adapter->adapter.dev.parent = port->physport->dev;

	अगर (parport_claim_or_block(adapter->pdev) < 0) अणु
		dev_err(&adapter->pdev->dev,
			"Could not claim parallel port\n");
		जाओ err_unरेजिस्टर;
	पूर्ण

	/* Reset hardware to a sane state (SCL and SDA high) */
	parport_setsda(port, 1);
	parport_setscl(port, 1);
	/* Other init अगर needed (घातer on...) */
	अगर (adapter_parm[type].init.val) अणु
		line_set(port, 1, &adapter_parm[type].init);
		/* Give घातered devices some समय to settle */
		msleep(100);
	पूर्ण

	अगर (i2c_bit_add_bus(&adapter->adapter) < 0) अणु
		dev_err(&adapter->pdev->dev, "Unable to register with I2C\n");
		जाओ err_unरेजिस्टर;
	पूर्ण

	/* Setup SMBus alert अगर supported */
	अगर (adapter_parm[type].smbus_alert) अणु
		काष्ठा i2c_client *ara;

		ara = i2c_new_smbus_alert_device(&adapter->adapter,
						 &adapter->alert_data);
		अगर (!IS_ERR(ara)) अणु
			adapter->ara = ara;
			parport_enable_irq(port);
		पूर्ण अन्यथा अणु
			dev_warn(&adapter->pdev->dev,
				 "Failed to register ARA client\n");
		पूर्ण
	पूर्ण

	/* Add the new adapter to the list */
	mutex_lock(&adapter_list_lock);
	list_add_tail(&adapter->node, &adapter_list);
	mutex_unlock(&adapter_list_lock);
	वापस;

 err_unरेजिस्टर:
	parport_release(adapter->pdev);
	parport_unरेजिस्टर_device(adapter->pdev);
 err_मुक्त:
	kमुक्त(adapter);
पूर्ण

अटल व्योम i2c_parport_detach(काष्ठा parport *port)
अणु
	काष्ठा i2c_par *adapter, *_n;

	/* Walk the list */
	mutex_lock(&adapter_list_lock);
	list_क्रम_each_entry_safe(adapter, _n, &adapter_list, node) अणु
		अगर (adapter->pdev->port == port) अणु
			अगर (adapter->ara) अणु
				parport_disable_irq(port);
				i2c_unरेजिस्टर_device(adapter->ara);
			पूर्ण
			i2c_del_adapter(&adapter->adapter);

			/* Un-init अगर needed (घातer off...) */
			अगर (adapter_parm[type].init.val)
				line_set(port, 0, &adapter_parm[type].init);

			parport_release(adapter->pdev);
			parport_unरेजिस्टर_device(adapter->pdev);
			list_del(&adapter->node);
			kमुक्त(adapter);
		पूर्ण
	पूर्ण
	mutex_unlock(&adapter_list_lock);
पूर्ण

अटल काष्ठा parport_driver i2c_parport_driver = अणु
	.name = "i2c-parport",
	.match_port = i2c_parport_attach,
	.detach = i2c_parport_detach,
	.devmodel = true,
पूर्ण;

/* ----- Module loading, unloading and inक्रमmation ------------------------ */

अटल पूर्णांक __init i2c_parport_init(व्योम)
अणु
	अगर (type < 0) अणु
		pr_warn("adapter type unspecified\n");
		वापस -ENODEV;
	पूर्ण

	अगर (type >= ARRAY_SIZE(adapter_parm)) अणु
		pr_warn("invalid type (%d)\n", type);
		वापस -ENODEV;
	पूर्ण

	वापस parport_रेजिस्टर_driver(&i2c_parport_driver);
पूर्ण

अटल व्योम __निकास i2c_parport_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&i2c_parport_driver);
पूर्ण

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("I2C bus over parallel port");
MODULE_LICENSE("GPL");

module_init(i2c_parport_init);
module_निकास(i2c_parport_निकास);
