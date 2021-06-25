<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * device driver क्रम philips saa7134 based TV cards
 * i2c पूर्णांकerface support
 *
 * (c) 2001,02 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>

#समावेश <media/v4l2-common.h>

/* ----------------------------------------------------------- */

अटल अचिन्हित पूर्णांक i2c_debug;
module_param(i2c_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_debug,"enable debug messages [i2c]");

अटल अचिन्हित पूर्णांक i2c_scan;
module_param(i2c_scan, पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_scan,"scan i2c bus at insmod time");

#घोषणा i2c_dbg(level, fmt, arg...) करो अणु \
	अगर (i2c_debug == level) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("i2c: " fmt), ## arg); \
	पूर्ण जबतक (0)

#घोषणा i2c_cont(level, fmt, arg...) करो अणु \
	अगर (i2c_debug == level) \
		pr_cont(fmt, ## arg); \
	पूर्ण जबतक (0)

#घोषणा I2C_WAIT_DELAY  32
#घोषणा I2C_WAIT_RETRY  16

/* ----------------------------------------------------------- */

अटल अक्षर *str_i2c_status[] = अणु
	"IDLE", "DONE_STOP", "BUSY", "TO_SCL", "TO_ARB", "DONE_WRITE",
	"DONE_READ", "DONE_WRITE_TO", "DONE_READ_TO", "NO_DEVICE",
	"NO_ACKN", "BUS_ERR", "ARB_LOST", "SEQ_ERR", "ST_ERR", "SW_ERR"
पूर्ण;

क्रमागत i2c_status अणु
	IDLE          = 0,  // no I2C command pending
	DONE_STOP     = 1,  // I2C command करोne and STOP executed
	BUSY          = 2,  // executing I2C command
	TO_SCL        = 3,  // executing I2C command, समय out on घड़ी stretching
	TO_ARB        = 4,  // समय out on arbitration trial, still trying
	DONE_WRITE    = 5,  // I2C command करोne and aरुकोing next ग_लिखो command
	DONE_READ     = 6,  // I2C command करोne and aरुकोing next पढ़ो command
	DONE_WRITE_TO = 7,  // see 5, and समय out on status echo
	DONE_READ_TO  = 8,  // see 6, and समय out on status echo
	NO_DEVICE     = 9,  // no acknowledge on device slave address
	NO_ACKN       = 10, // no acknowledge after data byte transfer
	BUS_ERR       = 11, // bus error
	ARB_LOST      = 12, // arbitration lost during transfer
	SEQ_ERR       = 13, // erroneous programming sequence
	ST_ERR        = 14, // wrong status echoing
	SW_ERR        = 15  // software error
पूर्ण;

अटल अक्षर *str_i2c_attr[] = अणु
	"NOP", "STOP", "CONTINUE", "START"
पूर्ण;

क्रमागत i2c_attr अणु
	NOP           = 0,  // no operation on I2C bus
	STOP          = 1,  // stop condition, no associated byte transfer
	CONTINUE      = 2,  // जारी with byte transfer
	START         = 3   // start condition with byte transfer
पूर्ण;

अटल अंतरभूत क्रमागत i2c_status i2c_get_status(काष्ठा saa7134_dev *dev)
अणु
	क्रमागत i2c_status status;

	status = saa_पढ़ोb(SAA7134_I2C_ATTR_STATUS) & 0x0f;
	i2c_dbg(2, "i2c stat <= %s\n", str_i2c_status[status]);
	वापस status;
पूर्ण

अटल अंतरभूत व्योम i2c_set_status(काष्ठा saa7134_dev *dev,
				  क्रमागत i2c_status status)
अणु
	i2c_dbg(2, "i2c stat => %s\n", str_i2c_status[status]);
	saa_anकरोrb(SAA7134_I2C_ATTR_STATUS,0x0f,status);
पूर्ण

अटल अंतरभूत व्योम i2c_set_attr(काष्ठा saa7134_dev *dev, क्रमागत i2c_attr attr)
अणु
	i2c_dbg(2, "i2c attr => %s\n", str_i2c_attr[attr]);
	saa_anकरोrb(SAA7134_I2C_ATTR_STATUS,0xc0,attr << 6);
पूर्ण

अटल अंतरभूत पूर्णांक i2c_is_error(क्रमागत i2c_status status)
अणु
	चयन (status) अणु
	हाल NO_DEVICE:
	हाल NO_ACKN:
	हाल BUS_ERR:
	हाल ARB_LOST:
	हाल SEQ_ERR:
	हाल ST_ERR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक i2c_is_idle(क्रमागत i2c_status status)
अणु
	चयन (status) अणु
	हाल IDLE:
	हाल DONE_STOP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक i2c_is_busy(क्रमागत i2c_status status)
अणु
	चयन (status) अणु
	हाल BUSY:
	हाल TO_SCL:
	हाल TO_ARB:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक i2c_is_busy_रुको(काष्ठा saa7134_dev *dev)
अणु
	क्रमागत i2c_status status;
	पूर्णांक count;

	क्रम (count = 0; count < I2C_WAIT_RETRY; count++) अणु
		status = i2c_get_status(dev);
		अगर (!i2c_is_busy(status))
			अवरोध;
		saa_रुको(I2C_WAIT_DELAY);
	पूर्ण
	अगर (I2C_WAIT_RETRY == count)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक i2c_reset(काष्ठा saa7134_dev *dev)
अणु
	क्रमागत i2c_status status;
	पूर्णांक count;

	i2c_dbg(2, "i2c reset\n");
	status = i2c_get_status(dev);
	अगर (!i2c_is_error(status))
		वापस true;
	i2c_set_status(dev,status);

	क्रम (count = 0; count < I2C_WAIT_RETRY; count++) अणु
		status = i2c_get_status(dev);
		अगर (!i2c_is_error(status))
			अवरोध;
		udelay(I2C_WAIT_DELAY);
	पूर्ण
	अगर (I2C_WAIT_RETRY == count)
		वापस false;

	अगर (!i2c_is_idle(status))
		वापस false;

	i2c_set_attr(dev,NOP);
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_send_byte(काष्ठा saa7134_dev *dev,
				क्रमागत i2c_attr attr,
				अचिन्हित अक्षर data)
अणु
	क्रमागत i2c_status status;
	__u32 dword;

	/* have to ग_लिखो both attr + data in one 32bit word */
	dword  = saa_पढ़ोl(SAA7134_I2C_ATTR_STATUS >> 2);
	dword &= 0x0f;
	dword |= (attr << 6);
	dword |= ((__u32)data << 8);
	dword |= 0x00 << 16;  /* 100 kHz */
//	dword |= 0x40 << 16;  /* 400 kHz */
	dword |= 0xf0 << 24;
	saa_ग_लिखोl(SAA7134_I2C_ATTR_STATUS >> 2, dword);
	i2c_dbg(2, "i2c data => 0x%x\n", data);

	अगर (!i2c_is_busy_रुको(dev))
		वापस -EIO;
	status = i2c_get_status(dev);
	अगर (i2c_is_error(status))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_recv_byte(काष्ठा saa7134_dev *dev)
अणु
	क्रमागत i2c_status status;
	अचिन्हित अक्षर data;

	i2c_set_attr(dev,CONTINUE);
	अगर (!i2c_is_busy_रुको(dev))
		वापस -EIO;
	status = i2c_get_status(dev);
	अगर (i2c_is_error(status))
		वापस -EIO;
	data = saa_पढ़ोb(SAA7134_I2C_DATA);
	i2c_dbg(2, "i2c data <= 0x%x\n", data);
	वापस data;
पूर्ण

अटल पूर्णांक saa7134_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा saa7134_dev *dev = i2c_adap->algo_data;
	क्रमागत i2c_status status;
	अचिन्हित अक्षर data;
	पूर्णांक addr,rc,i,byte;

	status = i2c_get_status(dev);
	अगर (!i2c_is_idle(status))
		अगर (!i2c_reset(dev))
			वापस -EIO;

	i2c_dbg(2, "start xfer\n");
	i2c_dbg(1, "i2c xfer:");
	क्रम (i = 0; i < num; i++) अणु
		अगर (!(msgs[i].flags & I2C_M_NOSTART) || 0 == i) अणु
			/* send address */
			i2c_dbg(2, "send address\n");
			addr  = msgs[i].addr << 1;
			अगर (msgs[i].flags & I2C_M_RD)
				addr |= 1;
			अगर (i > 0 && msgs[i].flags &
			    I2C_M_RD && msgs[i].addr != 0x40 &&
			    msgs[i].addr != 0x41 &&
			    msgs[i].addr != 0x19) अणु
				/* workaround क्रम a saa7134 i2c bug
				 * needed to talk to the mt352 demux
				 * thanks to pinnacle क्रम the hपूर्णांक */
				पूर्णांक quirk = 0xfe;
				i2c_cont(1, " [%02x quirk]", quirk);
				i2c_send_byte(dev,START,quirk);
				i2c_recv_byte(dev);
			पूर्ण
			i2c_cont(1, " < %02x", addr);
			rc = i2c_send_byte(dev,START,addr);
			अगर (rc < 0)
				 जाओ err;
		पूर्ण
		अगर (msgs[i].flags & I2C_M_RD) अणु
			/* पढ़ो bytes */
			i2c_dbg(2, "read bytes\n");
			क्रम (byte = 0; byte < msgs[i].len; byte++) अणु
				i2c_cont(1, " =");
				rc = i2c_recv_byte(dev);
				अगर (rc < 0)
					जाओ err;
				i2c_cont(1, "%02x", rc);
				msgs[i].buf[byte] = rc;
			पूर्ण
			/* discard mysterious extra byte when पढ़ोing
			   from Samsung S5H1411.  i2c bus माला_लो error
			   अगर we करो not. */
			अगर (0x19 == msgs[i].addr) अणु
				i2c_cont(1, " ?");
				rc = i2c_recv_byte(dev);
				अगर (rc < 0)
					जाओ err;
				i2c_cont(1, "%02x", rc);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* ग_लिखो bytes */
			i2c_dbg(2, "write bytes\n");
			क्रम (byte = 0; byte < msgs[i].len; byte++) अणु
				data = msgs[i].buf[byte];
				i2c_cont(1, " %02x", data);
				rc = i2c_send_byte(dev,CONTINUE,data);
				अगर (rc < 0)
					जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण
	i2c_dbg(2, "xfer done\n");
	i2c_cont(1, " >");
	i2c_set_attr(dev,STOP);
	rc = -EIO;
	अगर (!i2c_is_busy_रुको(dev))
		जाओ err;
	status = i2c_get_status(dev);
	अगर (i2c_is_error(status))
		जाओ err;
	/* ensure that the bus is idle क्रम at least one bit slot */
	msleep(1);

	i2c_cont(1, "\n");
	वापस num;
 err:
	अगर (1 == i2c_debug) अणु
		status = i2c_get_status(dev);
		i2c_cont(1, " ERROR: %s\n", str_i2c_status[status]);
	पूर्ण
	वापस rc;
पूर्ण

/* ----------------------------------------------------------- */

अटल u32 functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm saa7134_algo = अणु
	.master_xfer   = saa7134_i2c_xfer,
	.functionality = functionality,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter saa7134_adap_ढाँचा = अणु
	.owner         = THIS_MODULE,
	.name          = "saa7134",
	.algo          = &saa7134_algo,
पूर्ण;

अटल स्थिर काष्ठा i2c_client saa7134_client_ढाँचा = अणु
	.name	= "saa7134 internal",
पूर्ण;

/* ----------------------------------------------------------- */

/*
 * On Medion 7134 पढ़ोing the SAA7134 chip config EEPROM needs DVB-T
 * demod i2c gate बंदd due to an address clash between this EEPROM
 * and the demod one.
 */
अटल व्योम saa7134_i2c_eeprom_md7134_gate(काष्ठा saa7134_dev *dev)
अणु
	u8 subaddr = 0x7, dmdregval;
	u8 data[2];
	पूर्णांक ret;
	काष्ठा i2c_msg i2cgatemsg_r[] = अणु अणु.addr = 0x08, .flags = 0,
					   .buf = &subaddr, .len = 1पूर्ण,
					  अणु.addr = 0x08,
					   .flags = I2C_M_RD,
					   .buf = &dmdregval, .len = 1पूर्ण
					पूर्ण;
	काष्ठा i2c_msg i2cgatemsg_w[] = अणु अणु.addr = 0x08, .flags = 0,
					   .buf = data, .len = 2पूर्ण पूर्ण;

	ret = i2c_transfer(&dev->i2c_adap, i2cgatemsg_r, 2);
	अगर ((ret == 2) && (dmdregval & 0x2)) अणु
		pr_debug("%s: DVB-T demod i2c gate was left open\n",
			 dev->name);

		data[0] = subaddr;
		data[1] = (dmdregval & ~0x2);
		अगर (i2c_transfer(&dev->i2c_adap, i2cgatemsg_w, 1) != 1)
			pr_err("%s: EEPROM i2c gate close failure\n",
			       dev->name);
	पूर्ण
पूर्ण

अटल पूर्णांक
saa7134_i2c_eeprom(काष्ठा saa7134_dev *dev, अचिन्हित अक्षर *eedata, पूर्णांक len)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक i,err;

	अगर (dev->board == SAA7134_BOARD_MD7134)
		saa7134_i2c_eeprom_md7134_gate(dev);

	dev->i2c_client.addr = 0xa0 >> 1;
	buf = 0;
	अगर (1 != (err = i2c_master_send(&dev->i2c_client,&buf,1))) अणु
		pr_info("%s: Huh, no eeprom present (err=%d)?\n",
		       dev->name,err);
		वापस -1;
	पूर्ण
	अगर (len != (err = i2c_master_recv(&dev->i2c_client,eedata,len))) अणु
		pr_warn("%s: i2c eeprom read error (err=%d)\n",
		       dev->name,err);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < len; i += 16) अणु
		पूर्णांक size = (len - i) > 16 ? 16 : len - i;

		pr_info("i2c eeprom %02x: %*ph\n", i, size, &eedata[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल अक्षर *i2c_devs[128] = अणु
	[ 0x20      ] = "mpeg encoder (saa6752hs)",
	[ 0xa0 >> 1 ] = "eeprom",
	[ 0xc0 >> 1 ] = "tuner (analog)",
	[ 0x86 >> 1 ] = "tda9887",
	[ 0x5a >> 1 ] = "remote control",
पूर्ण;

अटल व्योम करो_i2c_scan(काष्ठा i2c_client *c)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक i,rc;

	क्रम (i = 0; i < ARRAY_SIZE(i2c_devs); i++) अणु
		c->addr = i;
		rc = i2c_master_recv(c,&buf,0);
		अगर (rc < 0)
			जारी;
		pr_info("i2c scan: found device @ 0x%x  [%s]\n",
			 i << 1, i2c_devs[i] ? i2c_devs[i] : "???");
	पूर्ण
पूर्ण

पूर्णांक saa7134_i2c_रेजिस्टर(काष्ठा saa7134_dev *dev)
अणु
	dev->i2c_adap = saa7134_adap_ढाँचा;
	dev->i2c_adap.dev.parent = &dev->pci->dev;
	strscpy(dev->i2c_adap.name, dev->name, माप(dev->i2c_adap.name));
	dev->i2c_adap.algo_data = dev;
	i2c_set_adapdata(&dev->i2c_adap, &dev->v4l2_dev);
	i2c_add_adapter(&dev->i2c_adap);

	dev->i2c_client = saa7134_client_ढाँचा;
	dev->i2c_client.adapter = &dev->i2c_adap;

	saa7134_i2c_eeprom(dev,dev->eedata,माप(dev->eedata));
	अगर (i2c_scan)
		करो_i2c_scan(&dev->i2c_client);

	/* Instantiate the IR receiver device, अगर present */
	saa7134_probe_i2c_ir(dev);
	वापस 0;
पूर्ण

पूर्णांक saa7134_i2c_unरेजिस्टर(काष्ठा saa7134_dev *dev)
अणु
	i2c_del_adapter(&dev->i2c_adap);
	वापस 0;
पूर्ण
