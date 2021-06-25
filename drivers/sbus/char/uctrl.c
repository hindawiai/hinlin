<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* uctrl.c: TS102 Microcontroller पूर्णांकerface on Tadpole Sparcbook 3
 *
 * Copyright 1999 Derrick J Brashear (shaकरोw@dementia.org)
 * Copyright 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ioport.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>

#घोषणा DEBUG 1
#अगर_घोषित DEBUG
#घोषणा dprपूर्णांकk(x) prपूर्णांकk x
#अन्यथा
#घोषणा dprपूर्णांकk(x)
#पूर्ण_अगर

काष्ठा uctrl_regs अणु
	u32 uctrl_पूर्णांकr;
	u32 uctrl_data;
	u32 uctrl_stat;
	u32 uctrl_xxx[5];
पूर्ण;

काष्ठा ts102_regs अणु
	u32 card_a_पूर्णांकr;
	u32 card_a_stat;
	u32 card_a_ctrl;
	u32 card_a_xxx;
	u32 card_b_पूर्णांकr;
	u32 card_b_stat;
	u32 card_b_ctrl;
	u32 card_b_xxx;
	u32 uctrl_पूर्णांकr;
	u32 uctrl_data;
	u32 uctrl_stat;
	u32 uctrl_xxx;
	u32 ts102_xxx[4];
पूर्ण;

/* Bits क्रम uctrl_पूर्णांकr रेजिस्टर */
#घोषणा UCTRL_INTR_TXE_REQ         0x01    /* transmit FIFO empty पूर्णांक req */
#घोषणा UCTRL_INTR_TXNF_REQ        0x02    /* transmit FIFO not full पूर्णांक req */
#घोषणा UCTRL_INTR_RXNE_REQ        0x04    /* receive FIFO not empty पूर्णांक req */
#घोषणा UCTRL_INTR_RXO_REQ         0x08    /* receive FIFO overflow पूर्णांक req */
#घोषणा UCTRL_INTR_TXE_MSK         0x10    /* transmit FIFO empty mask */
#घोषणा UCTRL_INTR_TXNF_MSK        0x20    /* transmit FIFO not full mask */
#घोषणा UCTRL_INTR_RXNE_MSK        0x40    /* receive FIFO not empty mask */
#घोषणा UCTRL_INTR_RXO_MSK         0x80    /* receive FIFO overflow mask */

/* Bits क्रम uctrl_stat रेजिस्टर */
#घोषणा UCTRL_STAT_TXE_STA         0x01    /* transmit FIFO empty status */
#घोषणा UCTRL_STAT_TXNF_STA        0x02    /* transmit FIFO not full status */
#घोषणा UCTRL_STAT_RXNE_STA        0x04    /* receive FIFO not empty status */
#घोषणा UCTRL_STAT_RXO_STA         0x08    /* receive FIFO overflow status */

अटल DEFINE_MUTEX(uctrl_mutex);
अटल स्थिर अक्षर *uctrl_extstatus[16] = अणु
        "main power available",
        "internal battery attached",
        "external battery attached",
        "external VGA attached",
        "external keyboard attached",
        "external mouse attached",
        "lid down",
        "internal battery currently charging",
        "external battery currently charging",
        "internal battery currently discharging",
        "external battery currently discharging",
पूर्ण;

/* Everything required क्रम one transaction with the uctrl */
काष्ठा uctrl_txn अणु
	u8 opcode;
	u8 inbits;
	u8 outbits;
	u8 *inbuf;
	u8 *outbuf;
पूर्ण;

काष्ठा uctrl_status अणु
	u8 current_temp; /* 0x07 */
	u8 reset_status; /* 0x0b */
	u16 event_status; /* 0x0c */
	u16 error_status; /* 0x10 */
	u16 बाह्यal_status; /* 0x11, 0x1b */
	u8 पूर्णांकernal_अक्षरge; /* 0x18 */
	u8 बाह्यal_अक्षरge; /* 0x19 */
	u16 control_lcd; /* 0x20 */
	u8 control_bitport; /* 0x21 */
	u8 speaker_volume; /* 0x23 */
	u8 control_tft_brightness; /* 0x24 */
	u8 control_kbd_repeat_delay; /* 0x28 */
	u8 control_kbd_repeat_period; /* 0x29 */
	u8 control_screen_contrast; /* 0x2F */
पूर्ण;

क्रमागत uctrl_opcode अणु
  READ_SERIAL_NUMBER=0x1,
  READ_ETHERNET_ADDRESS=0x2,
  READ_HARDWARE_VERSION=0x3,
  READ_MICROCONTROLLER_VERSION=0x4,
  READ_MAX_TEMPERATURE=0x5,
  READ_MIN_TEMPERATURE=0x6,
  READ_CURRENT_TEMPERATURE=0x7,
  READ_SYSTEM_VARIANT=0x8,
  READ_POWERON_CYCLES=0x9,
  READ_POWERON_SECONDS=0xA,
  READ_RESET_STATUS=0xB,
  READ_EVENT_STATUS=0xC,
  READ_REAL_TIME_CLOCK=0xD,
  READ_EXTERNAL_VGA_PORT=0xE,
  READ_MICROCONTROLLER_ROM_CHECKSUM=0xF,
  READ_ERROR_STATUS=0x10,
  READ_EXTERNAL_STATUS=0x11,
  READ_USER_CONFIGURATION_AREA=0x12,
  READ_MICROCONTROLLER_VOLTAGE=0x13,
  READ_INTERNAL_BATTERY_VOLTAGE=0x14,
  READ_DCIN_VOLTAGE=0x15,
  READ_HORIZONTAL_POINTER_VOLTAGE=0x16,
  READ_VERTICAL_POINTER_VOLTAGE=0x17,
  READ_INTERNAL_BATTERY_CHARGE_LEVEL=0x18,
  READ_EXTERNAL_BATTERY_CHARGE_LEVEL=0x19,
  READ_REAL_TIME_CLOCK_ALARM=0x1A,
  READ_EVENT_STATUS_NO_RESET=0x1B,
  READ_INTERNAL_KEYBOARD_LAYOUT=0x1C,
  READ_EXTERNAL_KEYBOARD_LAYOUT=0x1D,
  READ_EEPROM_STATUS=0x1E,
  CONTROL_LCD=0x20,
  CONTROL_BITPORT=0x21,
  SPEAKER_VOLUME=0x23,
  CONTROL_TFT_BRIGHTNESS=0x24,
  CONTROL_WATCHDOG=0x25,
  CONTROL_FACTORY_EEPROM_AREA=0x26,
  CONTROL_KBD_TIME_UNTIL_REPEAT=0x28,
  CONTROL_KBD_TIME_BETWEEN_REPEATS=0x29,
  CONTROL_TIMEZONE=0x2A,
  CONTROL_MARK_SPACE_RATIO=0x2B,
  CONTROL_DIAGNOSTIC_MODE=0x2E,
  CONTROL_SCREEN_CONTRAST=0x2F,
  RING_BELL=0x30,
  SET_DIAGNOSTIC_STATUS=0x32,
  CLEAR_KEY_COMBINATION_TABLE=0x33,
  PERFORM_SOFTWARE_RESET=0x34,
  SET_REAL_TIME_CLOCK=0x35,
  RECALIBRATE_POINTING_STICK=0x36,
  SET_BELL_FREQUENCY=0x37,
  SET_INTERNAL_BATTERY_CHARGE_RATE=0x39,
  SET_EXTERNAL_BATTERY_CHARGE_RATE=0x3A,
  SET_REAL_TIME_CLOCK_ALARM=0x3B,
  READ_EEPROM=0x40,
  WRITE_EEPROM=0x41,
  WRITE_TO_STATUS_DISPLAY=0x42,
  DEFINE_SPECIAL_CHARACTER=0x43,
  DEFINE_KEY_COMBINATION_ENTRY=0x50,
  DEFINE_STRING_TABLE_ENTRY=0x51,
  DEFINE_STATUS_SCREEN_DISPLAY=0x52,
  PERFORM_EMU_COMMANDS=0x64,
  READ_EMU_REGISTER=0x65,
  WRITE_EMU_REGISTER=0x66,
  READ_EMU_RAM=0x67,
  WRITE_EMU_RAM=0x68,
  READ_BQ_REGISTER=0x69,
  WRITE_BQ_REGISTER=0x6A,
  SET_USER_PASSWORD=0x70,
  VERIFY_USER_PASSWORD=0x71,
  GET_SYSTEM_PASSWORD_KEY=0x72,
  VERIFY_SYSTEM_PASSWORD=0x73,
  POWER_OFF=0x82,
  POWER_RESTART=0x83,
पूर्ण;

अटल काष्ठा uctrl_driver अणु
	काष्ठा uctrl_regs __iomem *regs;
	पूर्णांक irq;
	पूर्णांक pending;
	काष्ठा uctrl_status status;
पूर्ण *global_driver;

अटल व्योम uctrl_get_event_status(काष्ठा uctrl_driver *);
अटल व्योम uctrl_get_बाह्यal_status(काष्ठा uctrl_driver *);

अटल दीर्घ
uctrl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
		शेष:
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
uctrl_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&uctrl_mutex);
	uctrl_get_event_status(global_driver);
	uctrl_get_बाह्यal_status(global_driver);
	mutex_unlock(&uctrl_mutex);
	वापस 0;
पूर्ण

अटल irqवापस_t uctrl_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा file_operations uctrl_fops = अणु
	.owner =	THIS_MODULE,
	.llseek =	no_llseek,
	.unlocked_ioctl =	uctrl_ioctl,
	.खोलो =		uctrl_खोलो,
पूर्ण;

अटल काष्ठा miscdevice uctrl_dev = अणु
	UCTRL_MINOR,
	"uctrl",
	&uctrl_fops
पूर्ण;

/* Wait क्रम space to ग_लिखो, then ग_लिखो to it */
#घोषणा WRITEUCTLDATA(value) \
अणु \
  अचिन्हित पूर्णांक i; \
  क्रम (i = 0; i < 10000; i++) अणु \
      अगर (UCTRL_STAT_TXNF_STA & sbus_पढ़ोl(&driver->regs->uctrl_stat)) \
      अवरोध; \
  पूर्ण \
  dprपूर्णांकk(("write data 0x%02x\n", value)); \
  sbus_ग_लिखोl(value, &driver->regs->uctrl_data); \
पूर्ण

/* Wait क्रम something to पढ़ो, पढ़ो it, then clear the bit */
#घोषणा READUCTLDATA(value) \
अणु \
  अचिन्हित पूर्णांक i; \
  value = 0; \
  क्रम (i = 0; i < 10000; i++) अणु \
      अगर ((UCTRL_STAT_RXNE_STA & sbus_पढ़ोl(&driver->regs->uctrl_stat)) == 0) \
      अवरोध; \
    udelay(1); \
  पूर्ण \
  value = sbus_पढ़ोl(&driver->regs->uctrl_data); \
  dprपूर्णांकk(("read data 0x%02x\n", value)); \
  sbus_ग_लिखोl(UCTRL_STAT_RXNE_STA, &driver->regs->uctrl_stat); \
पूर्ण

अटल व्योम uctrl_करो_txn(काष्ठा uctrl_driver *driver, काष्ठा uctrl_txn *txn)
अणु
	पूर्णांक stat, incnt, outcnt, bytecnt, पूर्णांकr;
	u32 byte;

	stat = sbus_पढ़ोl(&driver->regs->uctrl_stat);
	पूर्णांकr = sbus_पढ़ोl(&driver->regs->uctrl_पूर्णांकr);
	sbus_ग_लिखोl(stat, &driver->regs->uctrl_stat);

	dprपूर्णांकk(("interrupt stat 0x%x int 0x%x\n", stat, पूर्णांकr));

	incnt = txn->inbits;
	outcnt = txn->outbits;
	byte = (txn->opcode << 8);
	WRITEUCTLDATA(byte);

	bytecnt = 0;
	जबतक (incnt > 0) अणु
		byte = (txn->inbuf[bytecnt] << 8);
		WRITEUCTLDATA(byte);
		incnt--;
		bytecnt++;
	पूर्ण

	/* Get the ack */
	READUCTLDATA(byte);
	dprपूर्णांकk(("ack was %x\n", (byte >> 8)));

	bytecnt = 0;
	जबतक (outcnt > 0) अणु
		READUCTLDATA(byte);
		txn->outbuf[bytecnt] = (byte >> 8);
		dprपूर्णांकk(("set byte to %02x\n", byte));
		outcnt--;
		bytecnt++;
	पूर्ण
पूर्ण

अटल व्योम uctrl_get_event_status(काष्ठा uctrl_driver *driver)
अणु
	काष्ठा uctrl_txn txn;
	u8 outbits[2];

	txn.opcode = READ_EVENT_STATUS;
	txn.inbits = 0;
	txn.outbits = 2;
	txn.inbuf = शून्य;
	txn.outbuf = outbits;

	uctrl_करो_txn(driver, &txn);

	dprपूर्णांकk(("bytes %x %x\n", (outbits[0] & 0xff), (outbits[1] & 0xff)));
	driver->status.event_status = 
		((outbits[0] & 0xff) << 8) | (outbits[1] & 0xff);
	dprपूर्णांकk(("ev is %x\n", driver->status.event_status));
पूर्ण

अटल व्योम uctrl_get_बाह्यal_status(काष्ठा uctrl_driver *driver)
अणु
	काष्ठा uctrl_txn txn;
	u8 outbits[2];
	पूर्णांक i, v;

	txn.opcode = READ_EXTERNAL_STATUS;
	txn.inbits = 0;
	txn.outbits = 2;
	txn.inbuf = शून्य;
	txn.outbuf = outbits;

	uctrl_करो_txn(driver, &txn);

	dprपूर्णांकk(("bytes %x %x\n", (outbits[0] & 0xff), (outbits[1] & 0xff)));
	driver->status.बाह्यal_status = 
		((outbits[0] * 256) + (outbits[1]));
	dprपूर्णांकk(("ex is %x\n", driver->status.बाह्यal_status));
	v = driver->status.बाह्यal_status;
	क्रम (i = 0; v != 0; i++, v >>= 1) अणु
		अगर (v & 1) अणु
			dprपूर्णांकk(("%s%s", " ", uctrl_extstatus[i]));
		पूर्ण
	पूर्ण
	dprपूर्णांकk(("\n"));
	
पूर्ण

अटल पूर्णांक uctrl_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा uctrl_driver *p;
	पूर्णांक err = -ENOMEM;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p) अणु
		prपूर्णांकk(KERN_ERR "uctrl: Unable to allocate device struct.\n");
		जाओ out;
	पूर्ण

	p->regs = of_ioremap(&op->resource[0], 0,
			     resource_size(&op->resource[0]),
			     "uctrl");
	अगर (!p->regs) अणु
		prपूर्णांकk(KERN_ERR "uctrl: Unable to map registers.\n");
		जाओ out_मुक्त;
	पूर्ण

	p->irq = op->archdata.irqs[0];
	err = request_irq(p->irq, uctrl_पूर्णांकerrupt, 0, "uctrl", p);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "uctrl: Unable to register irq.\n");
		जाओ out_iounmap;
	पूर्ण

	err = misc_रेजिस्टर(&uctrl_dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "uctrl: Unable to register misc device.\n");
		जाओ out_मुक्त_irq;
	पूर्ण

	sbus_ग_लिखोl(UCTRL_INTR_RXNE_REQ|UCTRL_INTR_RXNE_MSK, &p->regs->uctrl_पूर्णांकr);
	prपूर्णांकk(KERN_INFO "%pOF: uctrl regs[0x%p] (irq %d)\n",
	       op->dev.of_node, p->regs, p->irq);
	uctrl_get_event_status(p);
	uctrl_get_बाह्यal_status(p);

	dev_set_drvdata(&op->dev, p);
	global_driver = p;

out:
	वापस err;

out_मुक्त_irq:
	मुक्त_irq(p->irq, p);

out_iounmap:
	of_iounmap(&op->resource[0], p->regs, resource_size(&op->resource[0]));

out_मुक्त:
	kमुक्त(p);
	जाओ out;
पूर्ण

अटल पूर्णांक uctrl_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा uctrl_driver *p = dev_get_drvdata(&op->dev);

	अगर (p) अणु
		misc_deरेजिस्टर(&uctrl_dev);
		मुक्त_irq(p->irq, p);
		of_iounmap(&op->resource[0], p->regs, resource_size(&op->resource[0]));
		kमुक्त(p);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id uctrl_match[] = अणु
	अणु
		.name = "uctrl",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, uctrl_match);

अटल काष्ठा platक्रमm_driver uctrl_driver = अणु
	.driver = अणु
		.name = "uctrl",
		.of_match_table = uctrl_match,
	पूर्ण,
	.probe		= uctrl_probe,
	.हटाओ		= uctrl_हटाओ,
पूर्ण;


module_platक्रमm_driver(uctrl_driver);

MODULE_LICENSE("GPL");
