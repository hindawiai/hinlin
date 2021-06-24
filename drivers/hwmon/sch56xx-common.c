<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *   Copyright (C) 2010-2012 Hans de Goede <hdegoede@redhat.com>           *
 *                                                                         *
 ***************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश "sch56xx-common.h"

/* Insmod parameters */
अटल पूर्णांक nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, पूर्णांक, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
	__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

#घोषणा SIO_SCH56XX_LD_EM	0x0C	/* Embedded uController Logical Dev */
#घोषणा SIO_UNLOCK_KEY		0x55	/* Key to enable Super-I/O */
#घोषणा SIO_LOCK_KEY		0xAA	/* Key to disable Super-I/O */

#घोषणा SIO_REG_LDSEL		0x07	/* Logical device select */
#घोषणा SIO_REG_DEVID		0x20	/* Device ID */
#घोषणा SIO_REG_ENABLE		0x30	/* Logical device enable */
#घोषणा SIO_REG_ADDR		0x66	/* Logical device address (2 bytes) */

#घोषणा SIO_SCH5627_ID		0xC6	/* Chipset ID */
#घोषणा SIO_SCH5636_ID		0xC7	/* Chipset ID */

#घोषणा REGION_LENGTH		10

#घोषणा SCH56XX_CMD_READ	0x02
#घोषणा SCH56XX_CMD_WRITE	0x03

/* Watchकरोg रेजिस्टरs */
#घोषणा SCH56XX_REG_WDOG_PRESET		0x58B
#घोषणा SCH56XX_REG_WDOG_CONTROL	0x58C
#घोषणा SCH56XX_WDOG_TIME_BASE_SEC	0x01
#घोषणा SCH56XX_REG_WDOG_OUTPUT_ENABLE	0x58E
#घोषणा SCH56XX_WDOG_OUTPUT_ENABLE	0x02

काष्ठा sch56xx_watchकरोg_data अणु
	u16 addr;
	काष्ठा mutex *io_lock;
	काष्ठा watchकरोg_info wdinfo;
	काष्ठा watchकरोg_device wddev;
	u8 watchकरोg_preset;
	u8 watchकरोg_control;
	u8 watchकरोg_output_enable;
पूर्ण;

अटल काष्ठा platक्रमm_device *sch56xx_pdev;

/* Super I/O functions */
अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक base, पूर्णांक reg)
अणु
	outb(reg, base);
	वापस inb(base + 1);
पूर्ण

अटल अंतरभूत पूर्णांक superio_enter(पूर्णांक base)
अणु
	/* Don't step on other drivers' I/O space by accident */
	अगर (!request_muxed_region(base, 2, "sch56xx")) अणु
		pr_err("I/O address 0x%04x already in use\n", base);
		वापस -EBUSY;
	पूर्ण

	outb(SIO_UNLOCK_KEY, base);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम superio_select(पूर्णांक base, पूर्णांक ld)
अणु
	outb(SIO_REG_LDSEL, base);
	outb(ld, base + 1);
पूर्ण

अटल अंतरभूत व्योम superio_निकास(पूर्णांक base)
अणु
	outb(SIO_LOCK_KEY, base);
	release_region(base, 2);
पूर्ण

अटल पूर्णांक sch56xx_send_cmd(u16 addr, u8 cmd, u16 reg, u8 v)
अणु
	u8 val;
	पूर्णांक i;
	/*
	 * According to SMSC क्रम the commands we use the maximum समय क्रम
	 * the EM to respond is 15 ms, but testing shows in practice it
	 * responds within 15-32 पढ़ोs, so we first busy poll, and अगर
	 * that fails sleep a bit and try again until we are way past
	 * the 15 ms maximum response समय.
	 */
	स्थिर पूर्णांक max_busy_polls = 64;
	स्थिर पूर्णांक max_lazy_polls = 32;

	/* (Optional) Write-Clear the EC to Host Mailbox Register */
	val = inb(addr + 1);
	outb(val, addr + 1);

	/* Set Mailbox Address Poपूर्णांकer to first location in Region 1 */
	outb(0x00, addr + 2);
	outb(0x80, addr + 3);

	/* Write Request Packet Header */
	outb(cmd, addr + 4); /* VREG Access Type पढ़ो:0x02 ग_लिखो:0x03 */
	outb(0x01, addr + 5); /* # of Entries: 1 Byte (8-bit) */
	outb(0x04, addr + 2); /* Mailbox AP to first data entry loc. */

	/* Write Value field */
	अगर (cmd == SCH56XX_CMD_WRITE)
		outb(v, addr + 4);

	/* Write Address field */
	outb(reg & 0xff, addr + 6);
	outb(reg >> 8, addr + 7);

	/* Execute the Ranकरोm Access Command */
	outb(0x01, addr); /* Write 01h to the Host-to-EC रेजिस्टर */

	/* EM Interface Polling "Algorithm" */
	क्रम (i = 0; i < max_busy_polls + max_lazy_polls; i++) अणु
		अगर (i >= max_busy_polls)
			msleep(1);
		/* Read Interrupt source Register */
		val = inb(addr + 8);
		/* Write Clear the पूर्णांकerrupt source bits */
		अगर (val)
			outb(val, addr + 8);
		/* Command Completed ? */
		अगर (val & 0x01)
			अवरोध;
	पूर्ण
	अगर (i == max_busy_polls + max_lazy_polls) अणु
		pr_err("Max retries exceeded reading virtual register 0x%04hx (%d)\n",
		       reg, 1);
		वापस -EIO;
	पूर्ण

	/*
	 * According to SMSC we may need to retry this, but sofar I've always
	 * seen this succeed in 1 try.
	 */
	क्रम (i = 0; i < max_busy_polls; i++) अणु
		/* Read EC-to-Host Register */
		val = inb(addr + 1);
		/* Command Completed ? */
		अगर (val == 0x01)
			अवरोध;

		अगर (i == 0)
			pr_warn("EC reports: 0x%02x reading virtual register 0x%04hx\n",
				(अचिन्हित पूर्णांक)val, reg);
	पूर्ण
	अगर (i == max_busy_polls) अणु
		pr_err("Max retries exceeded reading virtual register 0x%04hx (%d)\n",
		       reg, 2);
		वापस -EIO;
	पूर्ण

	/*
	 * According to the SMSC app note we should now करो:
	 *
	 * Set Mailbox Address Poपूर्णांकer to first location in Region 1 *
	 * outb(0x00, addr + 2);
	 * outb(0x80, addr + 3);
	 *
	 * But अगर we करो that things करोn't work, so let's not.
	 */

	/* Read Value field */
	अगर (cmd == SCH56XX_CMD_READ)
		वापस inb(addr + 4);

	वापस 0;
पूर्ण

पूर्णांक sch56xx_पढ़ो_भव_reg(u16 addr, u16 reg)
अणु
	वापस sch56xx_send_cmd(addr, SCH56XX_CMD_READ, reg, 0);
पूर्ण
EXPORT_SYMBOL(sch56xx_पढ़ो_भव_reg);

पूर्णांक sch56xx_ग_लिखो_भव_reg(u16 addr, u16 reg, u8 val)
अणु
	वापस sch56xx_send_cmd(addr, SCH56XX_CMD_WRITE, reg, val);
पूर्ण
EXPORT_SYMBOL(sch56xx_ग_लिखो_भव_reg);

पूर्णांक sch56xx_पढ़ो_भव_reg16(u16 addr, u16 reg)
अणु
	पूर्णांक lsb, msb;

	/* Read LSB first, this will cause the matching MSB to be latched */
	lsb = sch56xx_पढ़ो_भव_reg(addr, reg);
	अगर (lsb < 0)
		वापस lsb;

	msb = sch56xx_पढ़ो_भव_reg(addr, reg + 1);
	अगर (msb < 0)
		वापस msb;

	वापस lsb | (msb << 8);
पूर्ण
EXPORT_SYMBOL(sch56xx_पढ़ो_भव_reg16);

पूर्णांक sch56xx_पढ़ो_भव_reg12(u16 addr, u16 msb_reg, u16 lsn_reg,
			       पूर्णांक high_nibble)
अणु
	पूर्णांक msb, lsn;

	/* Read MSB first, this will cause the matching LSN to be latched */
	msb = sch56xx_पढ़ो_भव_reg(addr, msb_reg);
	अगर (msb < 0)
		वापस msb;

	lsn = sch56xx_पढ़ो_भव_reg(addr, lsn_reg);
	अगर (lsn < 0)
		वापस lsn;

	अगर (high_nibble)
		वापस (msb << 4) | (lsn >> 4);
	अन्यथा
		वापस (msb << 4) | (lsn & 0x0f);
पूर्ण
EXPORT_SYMBOL(sch56xx_पढ़ो_भव_reg12);

/*
 * Watchकरोg routines
 */

अटल पूर्णांक watchकरोg_set_समयout(काष्ठा watchकरोg_device *wddev,
				अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा sch56xx_watchकरोg_data *data = watchकरोg_get_drvdata(wddev);
	अचिन्हित पूर्णांक resolution;
	u8 control;
	पूर्णांक ret;

	/* 1 second or 60 second resolution? */
	अगर (समयout <= 255)
		resolution = 1;
	अन्यथा
		resolution = 60;

	अगर (समयout < resolution || समयout > (resolution * 255))
		वापस -EINVAL;

	अगर (resolution == 1)
		control = data->watchकरोg_control | SCH56XX_WDOG_TIME_BASE_SEC;
	अन्यथा
		control = data->watchकरोg_control & ~SCH56XX_WDOG_TIME_BASE_SEC;

	अगर (data->watchकरोg_control != control) अणु
		mutex_lock(data->io_lock);
		ret = sch56xx_ग_लिखो_भव_reg(data->addr,
						SCH56XX_REG_WDOG_CONTROL,
						control);
		mutex_unlock(data->io_lock);
		अगर (ret)
			वापस ret;

		data->watchकरोg_control = control;
	पूर्ण

	/*
	 * Remember new समयout value, but करो not ग_लिखो as that (re)starts
	 * the watchकरोg countकरोwn.
	 */
	data->watchकरोg_preset = DIV_ROUND_UP(समयout, resolution);
	wddev->समयout = data->watchकरोg_preset * resolution;

	वापस 0;
पूर्ण

अटल पूर्णांक watchकरोg_start(काष्ठा watchकरोg_device *wddev)
अणु
	काष्ठा sch56xx_watchकरोg_data *data = watchकरोg_get_drvdata(wddev);
	पूर्णांक ret;
	u8 val;

	/*
	 * The sch56xx's watchकरोg cannot really be started / stopped
	 * it is always running, but we can aव्योम the समयr expiring
	 * from causing a प्रणाली reset by clearing the output enable bit.
	 *
	 * The sch56xx's watchकरोg will set the watchकरोg event bit, bit 0
	 * of the second पूर्णांकerrupt source रेजिस्टर (at base-address + 9),
	 * when the समयr expires.
	 *
	 * This will only cause a प्रणाली reset अगर the 0-1 flank happens when
	 * output enable is true. Setting output enable after the flank will
	 * not cause a reset, nor will the समयr expiring a second समय.
	 * This means we must clear the watchकरोg event bit in हाल it is set.
	 *
	 * The समयr may still be running (after a recent watchकरोg_stop) and
	 * mere milliseconds away from expiring, so the समयr must be reset
	 * first!
	 */

	mutex_lock(data->io_lock);

	/* 1. Reset the watchकरोg countकरोwn counter */
	ret = sch56xx_ग_लिखो_भव_reg(data->addr, SCH56XX_REG_WDOG_PRESET,
					data->watchकरोg_preset);
	अगर (ret)
		जाओ leave;

	/* 2. Enable output */
	val = data->watchकरोg_output_enable | SCH56XX_WDOG_OUTPUT_ENABLE;
	ret = sch56xx_ग_लिखो_भव_reg(data->addr,
					SCH56XX_REG_WDOG_OUTPUT_ENABLE, val);
	अगर (ret)
		जाओ leave;

	data->watchकरोg_output_enable = val;

	/* 3. Clear the watchकरोg event bit अगर set */
	val = inb(data->addr + 9);
	अगर (val & 0x01)
		outb(0x01, data->addr + 9);

leave:
	mutex_unlock(data->io_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक watchकरोg_trigger(काष्ठा watchकरोg_device *wddev)
अणु
	काष्ठा sch56xx_watchकरोg_data *data = watchकरोg_get_drvdata(wddev);
	पूर्णांक ret;

	/* Reset the watchकरोg countकरोwn counter */
	mutex_lock(data->io_lock);
	ret = sch56xx_ग_लिखो_भव_reg(data->addr, SCH56XX_REG_WDOG_PRESET,
					data->watchकरोg_preset);
	mutex_unlock(data->io_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक watchकरोg_stop(काष्ठा watchकरोg_device *wddev)
अणु
	काष्ठा sch56xx_watchकरोg_data *data = watchकरोg_get_drvdata(wddev);
	पूर्णांक ret = 0;
	u8 val;

	val = data->watchकरोg_output_enable & ~SCH56XX_WDOG_OUTPUT_ENABLE;
	mutex_lock(data->io_lock);
	ret = sch56xx_ग_लिखो_भव_reg(data->addr,
					SCH56XX_REG_WDOG_OUTPUT_ENABLE, val);
	mutex_unlock(data->io_lock);
	अगर (ret)
		वापस ret;

	data->watchकरोg_output_enable = val;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops watchकरोg_ops = अणु
	.owner		= THIS_MODULE,
	.start		= watchकरोg_start,
	.stop		= watchकरोg_stop,
	.ping		= watchकरोg_trigger,
	.set_समयout	= watchकरोg_set_समयout,
पूर्ण;

काष्ठा sch56xx_watchकरोg_data *sch56xx_watchकरोg_रेजिस्टर(काष्ठा device *parent,
	u16 addr, u32 revision, काष्ठा mutex *io_lock, पूर्णांक check_enabled)
अणु
	काष्ठा sch56xx_watchकरोg_data *data;
	पूर्णांक err, control, output_enable;

	/* Cache the watchकरोg रेजिस्टरs */
	mutex_lock(io_lock);
	control =
		sch56xx_पढ़ो_भव_reg(addr, SCH56XX_REG_WDOG_CONTROL);
	output_enable =
		sch56xx_पढ़ो_भव_reg(addr, SCH56XX_REG_WDOG_OUTPUT_ENABLE);
	mutex_unlock(io_lock);

	अगर (control < 0)
		वापस शून्य;
	अगर (output_enable < 0)
		वापस शून्य;
	अगर (check_enabled && !(output_enable & SCH56XX_WDOG_OUTPUT_ENABLE)) अणु
		pr_warn("Watchdog not enabled by BIOS, not registering\n");
		वापस शून्य;
	पूर्ण

	data = kzalloc(माप(काष्ठा sch56xx_watchकरोg_data), GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	data->addr = addr;
	data->io_lock = io_lock;

	strlcpy(data->wdinfo.identity, "sch56xx watchdog",
		माप(data->wdinfo.identity));
	data->wdinfo.firmware_version = revision;
	data->wdinfo.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT;
	अगर (!nowayout)
		data->wdinfo.options |= WDIOF_MAGICCLOSE;

	data->wddev.info = &data->wdinfo;
	data->wddev.ops = &watchकरोg_ops;
	data->wddev.parent = parent;
	data->wddev.समयout = 60;
	data->wddev.min_समयout = 1;
	data->wddev.max_समयout = 255 * 60;
	अगर (nowayout)
		set_bit(WDOG_NO_WAY_OUT, &data->wddev.status);
	अगर (output_enable & SCH56XX_WDOG_OUTPUT_ENABLE)
		set_bit(WDOG_ACTIVE, &data->wddev.status);

	/* Since the watchकरोg uses a करोwncounter there is no रेजिस्टर to पढ़ो
	   the BIOS set समयout from (अगर any was set at all) ->
	   Choose a preset which will give us a 1 minute समयout */
	अगर (control & SCH56XX_WDOG_TIME_BASE_SEC)
		data->watchकरोg_preset = 60; /* seconds */
	अन्यथा
		data->watchकरोg_preset = 1; /* minute */

	data->watchकरोg_control = control;
	data->watchकरोg_output_enable = output_enable;

	watchकरोg_set_drvdata(&data->wddev, data);
	err = watchकरोg_रेजिस्टर_device(&data->wddev);
	अगर (err) अणु
		pr_err("Registering watchdog chardev: %d\n", err);
		kमुक्त(data);
		वापस शून्य;
	पूर्ण

	वापस data;
पूर्ण
EXPORT_SYMBOL(sch56xx_watchकरोg_रेजिस्टर);

व्योम sch56xx_watchकरोg_unरेजिस्टर(काष्ठा sch56xx_watchकरोg_data *data)
अणु
	watchकरोg_unरेजिस्टर_device(&data->wddev);
	kमुक्त(data);
पूर्ण
EXPORT_SYMBOL(sch56xx_watchकरोg_unरेजिस्टर);

/*
 * platक्रमm dev find, add and हटाओ functions
 */

अटल पूर्णांक __init sch56xx_find(पूर्णांक sioaddr, स्थिर अक्षर **name)
अणु
	u8 devid;
	अचिन्हित लघु address;
	पूर्णांक err;

	err = superio_enter(sioaddr);
	अगर (err)
		वापस err;

	devid = superio_inb(sioaddr, SIO_REG_DEVID);
	चयन (devid) अणु
	हाल SIO_SCH5627_ID:
		*name = "sch5627";
		अवरोध;
	हाल SIO_SCH5636_ID:
		*name = "sch5636";
		अवरोध;
	शेष:
		pr_debug("Unsupported device id: 0x%02x\n",
			 (अचिन्हित पूर्णांक)devid);
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	superio_select(sioaddr, SIO_SCH56XX_LD_EM);

	अगर (!(superio_inb(sioaddr, SIO_REG_ENABLE) & 0x01)) अणु
		pr_warn("Device not activated\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	/*
	 * Warning the order of the low / high byte is the other way around
	 * as on most other superio devices!!
	 */
	address = superio_inb(sioaddr, SIO_REG_ADDR) |
		   superio_inb(sioaddr, SIO_REG_ADDR + 1) << 8;
	अगर (address == 0) अणु
		pr_warn("Base address not set\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण
	err = address;

निकास:
	superio_निकास(sioaddr);
	वापस err;
पूर्ण

अटल पूर्णांक __init sch56xx_device_add(पूर्णांक address, स्थिर अक्षर *name)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + REGION_LENGTH - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	sch56xx_pdev = platक्रमm_device_alloc(name, address);
	अगर (!sch56xx_pdev)
		वापस -ENOMEM;

	res.name = sch56xx_pdev->name;
	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास_device_put;

	err = platक्रमm_device_add_resources(sch56xx_pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed\n");
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(sch56xx_pdev);
	अगर (err) अणु
		pr_err("Device addition failed\n");
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(sch56xx_pdev);

	वापस err;
पूर्ण

अटल पूर्णांक __init sch56xx_init(व्योम)
अणु
	पूर्णांक address;
	स्थिर अक्षर *name = शून्य;

	address = sch56xx_find(0x4e, &name);
	अगर (address < 0)
		address = sch56xx_find(0x2e, &name);
	अगर (address < 0)
		वापस address;

	वापस sch56xx_device_add(address, name);
पूर्ण

अटल व्योम __निकास sch56xx_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(sch56xx_pdev);
पूर्ण

MODULE_DESCRIPTION("SMSC SCH56xx Hardware Monitoring Common Code");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");

module_init(sch56xx_init);
module_निकास(sch56xx_निकास);
