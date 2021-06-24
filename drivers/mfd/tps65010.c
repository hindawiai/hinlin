<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tps65010 - driver क्रम tps6501x घातer management chips
 *
 * Copyright (C) 2004 Texas Instruments
 * Copyright (C) 2004-2005 David Brownell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/tps65010.h>

#समावेश <linux/gpio/driver.h>


/*-------------------------------------------------------------------------*/

#घोषणा	DRIVER_VERSION	"2 May 2005"
#घोषणा	DRIVER_NAME	(tps65010_driver.driver.name)

MODULE_DESCRIPTION("TPS6501x Power Management Driver");
MODULE_LICENSE("GPL");

अटल काष्ठा i2c_driver tps65010_driver;

/*-------------------------------------------------------------------------*/

/* This driver handles a family of multipurpose chips, which incorporate
 * voltage regulators, lithium ion/polymer battery अक्षरging, GPIOs, LEDs,
 * and other features often needed in portable devices like cell phones
 * or digital cameras.
 *
 * The tps65011 and tps65013 have dअगरferent voltage settings compared
 * to tps65010 and tps65012.  The tps65013 has a NO_CHG status/irq.
 * All except tps65010 have "wait" mode, possibly शेषed so that
 * battery-insert != device-on.
 *
 * We could distinguish between some models by checking VDCDC1.UVLO or
 * other रेजिस्टरs, unless they've been changed alपढ़ोy after घातerup
 * as part of board setup by a bootloader.
 */
क्रमागत tps_model अणु
	TPS65010,
	TPS65011,
	TPS65012,
	TPS65013,
पूर्ण;

काष्ठा tps65010 अणु
	काष्ठा i2c_client	*client;
	काष्ठा mutex		lock;
	काष्ठा delayed_work	work;
	काष्ठा dentry		*file;
	अचिन्हित		अक्षरging:1;
	अचिन्हित		por:1;
	अचिन्हित		model:8;
	u16			vbus;
	अचिन्हित दीर्घ		flags;
#घोषणा	FLAG_VBUS_CHANGED	0
#घोषणा	FLAG_IRQ_ENABLE		1

	/* copies of last रेजिस्टर state */
	u8			chgstatus, regstatus, chgconf;
	u8			nmask1, nmask2;

	u8			ouपंचांगask;
	काष्ठा gpio_chip	chip;
	काष्ठा platक्रमm_device	*leds;
पूर्ण;

#घोषणा	POWER_POLL_DELAY	msecs_to_jअगरfies(5000)

/*-------------------------------------------------------------------------*/

#अगर	defined(DEBUG) || defined(CONFIG_DEBUG_FS)

अटल व्योम dbg_chgstat(अक्षर *buf, माप_प्रकार len, u8 chgstatus)
अणु
	snम_लिखो(buf, len, "%02x%s%s%s%s%s%s%s%s\n",
		chgstatus,
		(chgstatus & TPS_CHG_USB) ? " USB" : "",
		(chgstatus & TPS_CHG_AC) ? " AC" : "",
		(chgstatus & TPS_CHG_THERM) ? " therm" : "",
		(chgstatus & TPS_CHG_TERM) ? " done" :
			((chgstatus & (TPS_CHG_USB|TPS_CHG_AC))
				? " (charging)" : ""),
		(chgstatus & TPS_CHG_TAPER_TMO) ? " taper_tmo" : "",
		(chgstatus & TPS_CHG_CHG_TMO) ? " charge_tmo" : "",
		(chgstatus & TPS_CHG_PRECHG_TMO) ? " prechg_tmo" : "",
		(chgstatus & TPS_CHG_TEMP_ERR) ? " temp_err" : "");
पूर्ण

अटल व्योम dbg_regstat(अक्षर *buf, माप_प्रकार len, u8 regstatus)
अणु
	snम_लिखो(buf, len, "%02x %s%s%s%s%s%s%s%s\n",
		regstatus,
		(regstatus & TPS_REG_ONOFF) ? "off" : "(on)",
		(regstatus & TPS_REG_COVER) ? " uncover" : "",
		(regstatus & TPS_REG_UVLO) ? " UVLO" : "",
		(regstatus & TPS_REG_NO_CHG) ? " NO_CHG" : "",
		(regstatus & TPS_REG_PG_LD02) ? " ld02_bad" : "",
		(regstatus & TPS_REG_PG_LD01) ? " ld01_bad" : "",
		(regstatus & TPS_REG_PG_MAIN) ? " main_bad" : "",
		(regstatus & TPS_REG_PG_CORE) ? " core_bad" : "");
पूर्ण

अटल व्योम dbg_chgconf(पूर्णांक por, अक्षर *buf, माप_प्रकार len, u8 chgconfig)
अणु
	स्थिर अक्षर *hibit;

	अगर (por)
		hibit = (chgconfig & TPS_CHARGE_POR)
				? "POR=69ms" : "POR=1sec";
	अन्यथा
		hibit = (chgconfig & TPS65013_AUA) ? "AUA" : "";

	snम_लिखो(buf, len, "%02x %s%s%s AC=%d%% USB=%dmA %sCharge\n",
		chgconfig, hibit,
		(chgconfig & TPS_CHARGE_RESET) ? " reset" : "",
		(chgconfig & TPS_CHARGE_FAST) ? " fast" : "",
		(अणुपूर्णांक p; चयन ((chgconfig >> 3) & 3) अणु
		हाल 3:		p = 100; अवरोध;
		हाल 2:		p = 75; अवरोध;
		हाल 1:		p = 50; अवरोध;
		शेष:	p = 25; अवरोध;
		पूर्ण; p; पूर्ण),
		(chgconfig & TPS_VBUS_CHARGING)
			? ((chgconfig & TPS_VBUS_500MA) ? 500 : 100)
			: 0,
		(chgconfig & TPS_CHARGE_ENABLE) ? "" : "No");
पूर्ण

#पूर्ण_अगर

#अगर_घोषित	DEBUG

अटल व्योम show_chgstatus(स्थिर अक्षर *label, u8 chgstatus)
अणु
	अक्षर buf [100];

	dbg_chgstat(buf, माप buf, chgstatus);
	pr_debug("%s: %s %s", DRIVER_NAME, label, buf);
पूर्ण

अटल व्योम show_regstatus(स्थिर अक्षर *label, u8 regstatus)
अणु
	अक्षर buf [100];

	dbg_regstat(buf, माप buf, regstatus);
	pr_debug("%s: %s %s", DRIVER_NAME, label, buf);
पूर्ण

अटल व्योम show_chgconfig(पूर्णांक por, स्थिर अक्षर *label, u8 chgconfig)
अणु
	अक्षर buf [100];

	dbg_chgconf(por, buf, माप buf, chgconfig);
	pr_debug("%s: %s %s", DRIVER_NAME, label, buf);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम show_chgstatus(स्थिर अक्षर *label, u8 chgstatus) अणु पूर्ण
अटल अंतरभूत व्योम show_regstatus(स्थिर अक्षर *label, u8 chgstatus) अणु पूर्ण
अटल अंतरभूत व्योम show_chgconfig(पूर्णांक por, स्थिर अक्षर *label, u8 chgconfig) अणु पूर्ण

#पूर्ण_अगर

#अगर_घोषित	CONFIG_DEBUG_FS

अटल पूर्णांक dbg_show(काष्ठा seq_file *s, व्योम *_)
अणु
	काष्ठा tps65010	*tps = s->निजी;
	u8		value, v2;
	अचिन्हित	i;
	अक्षर		buf[100];
	स्थिर अक्षर	*chip;

	चयन (tps->model) अणु
	हाल TPS65010:	chip = "tps65010"; अवरोध;
	हाल TPS65011:	chip = "tps65011"; अवरोध;
	हाल TPS65012:	chip = "tps65012"; अवरोध;
	हाल TPS65013:	chip = "tps65013"; अवरोध;
	शेष:	chip = शून्य; अवरोध;
	पूर्ण
	seq_म_लिखो(s, "driver  %s\nversion %s\nchip    %s\n\n",
			DRIVER_NAME, DRIVER_VERSION, chip);

	mutex_lock(&tps->lock);

	/* FIXME how can we tell whether a battery is present?
	 * likely involves a अक्षरge gauging chip (like BQ26501).
	 */

	seq_म_लिखो(s, "%scharging\n\n", tps->अक्षरging ? "" : "(not) ");


	/* रेजिस्टरs क्रम monitoring battery अक्षरging and status; note
	 * that पढ़ोing chgstat and regstat may ack IRQs...
	 */
	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_CHGCONFIG);
	dbg_chgconf(tps->por, buf, माप buf, value);
	seq_म_लिखो(s, "chgconfig %s", buf);

	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_CHGSTATUS);
	dbg_chgstat(buf, माप buf, value);
	seq_म_लिखो(s, "chgstat   %s", buf);
	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_MASK1);
	dbg_chgstat(buf, माप buf, value);
	seq_म_लिखो(s, "mask1     %s", buf);
	/* ignore ackपूर्णांक1 */

	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_REGSTATUS);
	dbg_regstat(buf, माप buf, value);
	seq_म_लिखो(s, "regstat   %s", buf);
	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_MASK2);
	dbg_regstat(buf, माप buf, value);
	seq_म_लिखो(s, "mask2     %s\n", buf);
	/* ignore ackपूर्णांक2 */

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &tps->work,
			   POWER_POLL_DELAY);

	/* VMAIN voltage, enable lowघातer, etc */
	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_VDCDC1);
	seq_म_लिखो(s, "vdcdc1    %02x\n", value);

	/* VCORE voltage, vibrator on/off */
	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_VDCDC2);
	seq_म_लिखो(s, "vdcdc2    %02x\n", value);

	/* both LD0s, and their lowघातer behavior */
	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_VREGS1);
	seq_म_लिखो(s, "vregs1    %02x\n\n", value);


	/* LEDs and GPIOs */
	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_LED1_ON);
	v2 = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_LED1_PER);
	seq_म_लिखो(s, "led1 %s, on=%02x, per=%02x, %d/%d msec\n",
		(value & 0x80)
			? ((v2 & 0x80) ? "on" : "off")
			: ((v2 & 0x80) ? "blink" : "(nPG)"),
		value, v2,
		(value & 0x7f) * 10, (v2 & 0x7f) * 100);

	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_LED2_ON);
	v2 = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_LED2_PER);
	seq_म_लिखो(s, "led2 %s, on=%02x, per=%02x, %d/%d msec\n",
		(value & 0x80)
			? ((v2 & 0x80) ? "on" : "off")
			: ((v2 & 0x80) ? "blink" : "off"),
		value, v2,
		(value & 0x7f) * 10, (v2 & 0x7f) * 100);

	value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_DEFGPIO);
	v2 = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_MASK3);
	seq_म_लिखो(s, "defgpio %02x mask3 %02x\n", value, v2);

	क्रम (i = 0; i < 4; i++) अणु
		अगर (value & (1 << (4 + i)))
			seq_म_लिखो(s, "  gpio%d-out %s\n", i + 1,
				(value & (1 << i)) ? "low" : "hi ");
		अन्यथा
			seq_म_लिखो(s, "  gpio%d-in  %s %s %s\n", i + 1,
				(value & (1 << i)) ? "hi " : "low",
				(v2 & (1 << i)) ? "no-irq" : "irq",
				(v2 & (1 << (4 + i))) ? "rising" : "falling");
	पूर्ण

	mutex_unlock(&tps->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक dbg_tps_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, dbg_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debug_fops = अणु
	.खोलो		= dbg_tps_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

#घोषणा	DEBUG_FOPS	&debug_fops

#अन्यथा
#घोषणा	DEBUG_FOPS	शून्य
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/* handle IRQS in a task context, so we can use I2C calls */
अटल व्योम tps65010_पूर्णांकerrupt(काष्ठा tps65010 *tps)
अणु
	u8 पंचांगp = 0, mask, poll;

	/* IRQs won't trigger क्रम certain events, but we can get
	 * others by polling (normally, with बाह्यal घातer applied).
	 */
	poll = 0;

	/* regstatus irqs */
	अगर (tps->nmask2) अणु
		पंचांगp = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_REGSTATUS);
		mask = पंचांगp ^ tps->regstatus;
		tps->regstatus = पंचांगp;
		mask &= tps->nmask2;
	पूर्ण अन्यथा
		mask = 0;
	अगर (mask) अणु
		tps->regstatus =  पंचांगp;
		/* may need to shut something करोwn ... */

		/* "off" usually means deep sleep */
		अगर (पंचांगp & TPS_REG_ONOFF) अणु
			pr_info("%s: power off button\n", DRIVER_NAME);
#अगर 0
			/* REVISIT:  this might need its own workqueue
			 * plus tweaks including deadlock aव्योमance ...
			 * also needs to get error handling and probably
			 * an #अगर_घोषित CONFIG_HIBERNATION
			 */
			hibernate();
#पूर्ण_अगर
			poll = 1;
		पूर्ण
	पूर्ण

	/* chgstatus irqs */
	अगर (tps->nmask1) अणु
		पंचांगp = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_CHGSTATUS);
		mask = पंचांगp ^ tps->chgstatus;
		tps->chgstatus = पंचांगp;
		mask &= tps->nmask1;
	पूर्ण अन्यथा
		mask = 0;
	अगर (mask) अणु
		अचिन्हित	अक्षरging = 0;

		show_chgstatus("chg/irq", पंचांगp);
		अगर (पंचांगp & (TPS_CHG_USB|TPS_CHG_AC))
			show_chgconfig(tps->por, "conf", tps->chgconf);

		/* Unless it was turned off or disabled, we अक्षरge any
		 * battery whenever there's घातer available क्रम it
		 * and the अक्षरger hasn't been disabled.
		 */
		अगर (!(tps->chgstatus & ~(TPS_CHG_USB|TPS_CHG_AC))
				&& (tps->chgstatus & (TPS_CHG_USB|TPS_CHG_AC))
				&& (tps->chgconf & TPS_CHARGE_ENABLE)
				) अणु
			अगर (tps->chgstatus & TPS_CHG_USB) अणु
				/* VBUS options are पढ़ोonly until reconnect */
				अगर (mask & TPS_CHG_USB)
					set_bit(FLAG_VBUS_CHANGED, &tps->flags);
				अक्षरging = 1;
			पूर्ण अन्यथा अगर (tps->chgstatus & TPS_CHG_AC)
				अक्षरging = 1;
		पूर्ण
		अगर (अक्षरging != tps->अक्षरging) अणु
			tps->अक्षरging = अक्षरging;
			pr_info("%s: battery %scharging\n",
				DRIVER_NAME, अक्षरging ? "" :
				((tps->chgstatus & (TPS_CHG_USB|TPS_CHG_AC))
					? "NOT " : "dis"));
		पूर्ण
	पूर्ण

	/* always poll to detect (a) घातer removal, without tps65013
	 * NO_CHG IRQ; or (b) restart of अक्षरging after stop.
	 */
	अगर ((tps->model != TPS65013 || !tps->अक्षरging)
			&& (tps->chgstatus & (TPS_CHG_USB|TPS_CHG_AC)))
		poll = 1;
	अगर (poll)
		queue_delayed_work(प्रणाली_घातer_efficient_wq, &tps->work,
				   POWER_POLL_DELAY);

	/* also potentially gpio-in rise or fall */
पूर्ण

/* handle IRQs and polling using keventd क्रम now */
अटल व्योम tps65010_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tps65010		*tps;

	tps = container_of(to_delayed_work(work), काष्ठा tps65010, work);
	mutex_lock(&tps->lock);

	tps65010_पूर्णांकerrupt(tps);

	अगर (test_and_clear_bit(FLAG_VBUS_CHANGED, &tps->flags)) अणु
		u8	chgconfig, पंचांगp;

		chgconfig = i2c_smbus_पढ़ो_byte_data(tps->client,
					TPS_CHGCONFIG);
		chgconfig &= ~(TPS_VBUS_500MA | TPS_VBUS_CHARGING);
		अगर (tps->vbus == 500)
			chgconfig |= TPS_VBUS_500MA | TPS_VBUS_CHARGING;
		अन्यथा अगर (tps->vbus >= 100)
			chgconfig |= TPS_VBUS_CHARGING;

		i2c_smbus_ग_लिखो_byte_data(tps->client,
					  TPS_CHGCONFIG, chgconfig);

		/* vbus update fails unless VBUS is connected! */
		पंचांगp = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_CHGCONFIG);
		tps->chgconf = पंचांगp;
		show_chgconfig(tps->por, "update vbus", पंचांगp);
	पूर्ण

	अगर (test_and_clear_bit(FLAG_IRQ_ENABLE, &tps->flags))
		enable_irq(tps->client->irq);

	mutex_unlock(&tps->lock);
पूर्ण

अटल irqवापस_t tps65010_irq(पूर्णांक irq, व्योम *_tps)
अणु
	काष्ठा tps65010		*tps = _tps;

	disable_irq_nosync(irq);
	set_bit(FLAG_IRQ_ENABLE, &tps->flags);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &tps->work, 0);
	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/

/* offsets 0..3 == GPIO1..GPIO4
 * offsets 4..5 == LED1/nPG, LED2 (we set one of the non-BLINK modes)
 * offset 6 == vibrator motor driver
 */
अटल व्योम
tps65010_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	अगर (offset < 4)
		tps65010_set_gpio_out_value(offset + 1, value);
	अन्यथा अगर (offset < 6)
		tps65010_set_led(offset - 3, value ? ON : OFF);
	अन्यथा
		tps65010_set_vib(value);
पूर्ण

अटल पूर्णांक
tps65010_output(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	/* GPIOs may be input-only */
	अगर (offset < 4) अणु
		काष्ठा tps65010		*tps;

		tps = gpiochip_get_data(chip);
		अगर (!(tps->ouपंचांगask & (1 << offset)))
			वापस -EINVAL;
		tps65010_set_gpio_out_value(offset + 1, value);
	पूर्ण अन्यथा अगर (offset < 6)
		tps65010_set_led(offset - 3, value ? ON : OFF);
	अन्यथा
		tps65010_set_vib(value);

	वापस 0;
पूर्ण

अटल पूर्णांक tps65010_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	पूर्णांक			value;
	काष्ठा tps65010		*tps;

	tps = gpiochip_get_data(chip);

	अगर (offset < 4) अणु
		value = i2c_smbus_पढ़ो_byte_data(tps->client, TPS_DEFGPIO);
		अगर (value < 0)
			वापस value;
		अगर (value & (1 << (offset + 4)))	/* output */
			वापस !(value & (1 << offset));
		अन्यथा					/* input */
			वापस !!(value & (1 << offset));
	पूर्ण

	/* REVISIT we *could* report LED1/nPG and LED2 state ... */
	वापस 0;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल काष्ठा tps65010 *the_tps;

अटल पूर्णांक tps65010_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tps65010		*tps = i2c_get_clientdata(client);
	काष्ठा tps65010_board	*board = dev_get_platdata(&client->dev);

	अगर (board && board->tearकरोwn) अणु
		पूर्णांक status = board->tearकरोwn(client, board->context);
		अगर (status < 0)
			dev_dbg(&client->dev, "board %s %s err %d\n",
				"teardown", client->name, status);
	पूर्ण
	अगर (client->irq > 0)
		मुक्त_irq(client->irq, tps);
	cancel_delayed_work_sync(&tps->work);
	debugfs_हटाओ(tps->file);
	the_tps = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक tps65010_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tps65010		*tps;
	पूर्णांक			status;
	काष्ठा tps65010_board	*board = dev_get_platdata(&client->dev);

	अगर (the_tps) अणु
		dev_dbg(&client->dev, "only one tps6501x chip allowed\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EINVAL;

	tps = devm_kzalloc(&client->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	mutex_init(&tps->lock);
	INIT_DELAYED_WORK(&tps->work, tps65010_work);
	tps->client = client;
	tps->model = id->driver_data;

	/* the IRQ is active low, but many gpio lines can't support that
	 * so this driver uses falling-edge triggers instead.
	 */
	अगर (client->irq > 0) अणु
		status = request_irq(client->irq, tps65010_irq,
				     IRQF_TRIGGER_FALLING, DRIVER_NAME, tps);
		अगर (status < 0) अणु
			dev_dbg(&client->dev, "can't get IRQ %d, err %d\n",
					client->irq, status);
			वापस status;
		पूर्ण
		/* annoying race here, ideally we'd have an option
		 * to claim the irq now and enable it later.
		 * FIXME genirq IRQF_NOAUTOEN now solves that ...
		 */
		disable_irq(client->irq);
		set_bit(FLAG_IRQ_ENABLE, &tps->flags);
	पूर्ण अन्यथा
		dev_warn(&client->dev, "IRQ not configured!\n");


	चयन (tps->model) अणु
	हाल TPS65010:
	हाल TPS65012:
		tps->por = 1;
		अवरोध;
	/* अन्यथा CHGCONFIG.POR is replaced by AUA, enabling a WAIT mode */
	पूर्ण
	tps->chgconf = i2c_smbus_पढ़ो_byte_data(client, TPS_CHGCONFIG);
	show_chgconfig(tps->por, "conf/init", tps->chgconf);

	show_chgstatus("chg/init",
		i2c_smbus_पढ़ो_byte_data(client, TPS_CHGSTATUS));
	show_regstatus("reg/init",
		i2c_smbus_पढ़ो_byte_data(client, TPS_REGSTATUS));

	pr_debug("%s: vdcdc1 0x%02x, vdcdc2 %02x, vregs1 %02x\n", DRIVER_NAME,
		i2c_smbus_पढ़ो_byte_data(client, TPS_VDCDC1),
		i2c_smbus_पढ़ो_byte_data(client, TPS_VDCDC2),
		i2c_smbus_पढ़ो_byte_data(client, TPS_VREGS1));
	pr_debug("%s: defgpio 0x%02x, mask3 0x%02x\n", DRIVER_NAME,
		i2c_smbus_पढ़ो_byte_data(client, TPS_DEFGPIO),
		i2c_smbus_पढ़ो_byte_data(client, TPS_MASK3));

	i2c_set_clientdata(client, tps);
	the_tps = tps;

#अगर	defined(CONFIG_USB_GADGET) && !defined(CONFIG_USB_OTG)
	/* USB hosts can't draw VBUS.  OTG devices could, later
	 * when OTG infraकाष्ठाure enables it.  USB peripherals
	 * could be relying on VBUS जबतक booting, though.
	 */
	tps->vbus = 100;
#पूर्ण_अगर

	/* unmask the "interesting" irqs, then poll once to
	 * kickstart monitoring, initialize shaकरोwed status
	 * रेजिस्टरs, and maybe disable VBUS draw.
	 */
	tps->nmask1 = ~0;
	(व्योम) i2c_smbus_ग_लिखो_byte_data(client, TPS_MASK1, ~tps->nmask1);

	tps->nmask2 = TPS_REG_ONOFF;
	अगर (tps->model == TPS65013)
		tps->nmask2 |= TPS_REG_NO_CHG;
	(व्योम) i2c_smbus_ग_लिखो_byte_data(client, TPS_MASK2, ~tps->nmask2);

	(व्योम) i2c_smbus_ग_लिखो_byte_data(client, TPS_MASK3, 0x0f
		| i2c_smbus_पढ़ो_byte_data(client, TPS_MASK3));

	tps65010_work(&tps->work.work);

	tps->file = debugfs_create_file(DRIVER_NAME, S_IRUGO, शून्य,
				tps, DEBUG_FOPS);

	/* optionally रेजिस्टर GPIOs */
	अगर (board && board->base != 0) अणु
		tps->ouपंचांगask = board->ouपंचांगask;

		tps->chip.label = client->name;
		tps->chip.parent = &client->dev;
		tps->chip.owner = THIS_MODULE;

		tps->chip.set = tps65010_gpio_set;
		tps->chip.direction_output = tps65010_output;

		/* NOTE:  only partial support क्रम inमाला_दो; nyet IRQs */
		tps->chip.get = tps65010_gpio_get;

		tps->chip.base = board->base;
		tps->chip.ngpio = 7;
		tps->chip.can_sleep = 1;

		status = gpiochip_add_data(&tps->chip, tps);
		अगर (status < 0)
			dev_err(&client->dev, "can't add gpiochip, err %d\n",
					status);
		अन्यथा अगर (board->setup) अणु
			status = board->setup(client, board->context);
			अगर (status < 0) अणु
				dev_dbg(&client->dev,
					"board %s %s err %d\n",
					"setup", client->name, status);
				status = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps65010_id[] = अणु
	अणु "tps65010", TPS65010 पूर्ण,
	अणु "tps65011", TPS65011 पूर्ण,
	अणु "tps65012", TPS65012 पूर्ण,
	अणु "tps65013", TPS65013 पूर्ण,
	अणु "tps65014", TPS65011 पूर्ण,	/* tps65011 अक्षरging at 6.5V max */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps65010_id);

अटल काष्ठा i2c_driver tps65010_driver = अणु
	.driver = अणु
		.name	= "tps65010",
	पूर्ण,
	.probe	= tps65010_probe,
	.हटाओ	= tps65010_हटाओ,
	.id_table = tps65010_id,
पूर्ण;

/*-------------------------------------------------------------------------*/

/* Draw from VBUS:
 *   0 mA -- DON'T DRAW (might supply घातer instead)
 * 100 mA -- usb unit load (slowest अक्षरge rate)
 * 500 mA -- usb high घातer (fast battery अक्षरge)
 */
पूर्णांक tps65010_set_vbus_draw(अचिन्हित mA)
अणु
	अचिन्हित दीर्घ	flags;

	अगर (!the_tps)
		वापस -ENODEV;

	/* assumes non-SMP */
	local_irq_save(flags);
	अगर (mA >= 500)
		mA = 500;
	अन्यथा अगर (mA >= 100)
		mA = 100;
	अन्यथा
		mA = 0;
	the_tps->vbus = mA;
	अगर ((the_tps->chgstatus & TPS_CHG_USB)
			&& test_and_set_bit(
				FLAG_VBUS_CHANGED, &the_tps->flags)) अणु
		/* gadget drivers call this in_irq() */
		queue_delayed_work(प्रणाली_घातer_efficient_wq, &the_tps->work,
				   0);
	पूर्ण
	local_irq_restore(flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tps65010_set_vbus_draw);

/*-------------------------------------------------------------------------*/
/* tps65010_set_gpio_out_value parameter:
 * gpio:  GPIO1, GPIO2, GPIO3 or GPIO4
 * value: LOW or HIGH
 */
पूर्णांक tps65010_set_gpio_out_value(अचिन्हित gpio, अचिन्हित value)
अणु
	पूर्णांक	 status;
	अचिन्हित defgpio;

	अगर (!the_tps)
		वापस -ENODEV;
	अगर ((gpio < GPIO1) || (gpio > GPIO4))
		वापस -EINVAL;

	mutex_lock(&the_tps->lock);

	defgpio = i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_DEFGPIO);

	/* Configure GPIO क्रम output */
	defgpio |= 1 << (gpio + 3);

	/* Writing 1 क्रमces a logic 0 on that GPIO and vice versa */
	चयन (value) अणु
	हाल LOW:
		defgpio |= 1 << (gpio - 1);    /* set GPIO low by writing 1 */
		अवरोध;
	/* हाल HIGH: */
	शेष:
		defgpio &= ~(1 << (gpio - 1)); /* set GPIO high by writing 0 */
		अवरोध;
	पूर्ण

	status = i2c_smbus_ग_लिखो_byte_data(the_tps->client,
		TPS_DEFGPIO, defgpio);

	pr_debug("%s: gpio%dout = %s, defgpio 0x%02x\n", DRIVER_NAME,
		gpio, value ? "high" : "low",
		i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_DEFGPIO));

	mutex_unlock(&the_tps->lock);
	वापस status;
पूर्ण
EXPORT_SYMBOL(tps65010_set_gpio_out_value);

/*-------------------------------------------------------------------------*/
/* tps65010_set_led parameter:
 * led:  LED1 or LED2
 * mode: ON, OFF or BLINK
 */
पूर्णांक tps65010_set_led(अचिन्हित led, अचिन्हित mode)
अणु
	पूर्णांक	 status;
	अचिन्हित led_on, led_per, offs;

	अगर (!the_tps)
		वापस -ENODEV;

	अगर (led == LED1)
		offs = 0;
	अन्यथा अणु
		offs = 2;
		led = LED2;
	पूर्ण

	mutex_lock(&the_tps->lock);

	pr_debug("%s: led%i_on   0x%02x\n", DRIVER_NAME, led,
		i2c_smbus_पढ़ो_byte_data(the_tps->client,
				TPS_LED1_ON + offs));

	pr_debug("%s: led%i_per  0x%02x\n", DRIVER_NAME, led,
		i2c_smbus_पढ़ो_byte_data(the_tps->client,
				TPS_LED1_PER + offs));

	चयन (mode) अणु
	हाल OFF:
		led_on  = 1 << 7;
		led_per = 0 << 7;
		अवरोध;
	हाल ON:
		led_on  = 1 << 7;
		led_per = 1 << 7;
		अवरोध;
	हाल BLINK:
		led_on  = 0x30 | (0 << 7);
		led_per = 0x08 | (1 << 7);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s: Wrong mode parameter for set_led()\n",
		       DRIVER_NAME);
		mutex_unlock(&the_tps->lock);
		वापस -EINVAL;
	पूर्ण

	status = i2c_smbus_ग_लिखो_byte_data(the_tps->client,
			TPS_LED1_ON + offs, led_on);

	अगर (status != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to write led%i_on register\n",
		       DRIVER_NAME, led);
		mutex_unlock(&the_tps->lock);
		वापस status;
	पूर्ण

	pr_debug("%s: led%i_on   0x%02x\n", DRIVER_NAME, led,
		i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_LED1_ON + offs));

	status = i2c_smbus_ग_लिखो_byte_data(the_tps->client,
			TPS_LED1_PER + offs, led_per);

	अगर (status != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to write led%i_per register\n",
		       DRIVER_NAME, led);
		mutex_unlock(&the_tps->lock);
		वापस status;
	पूर्ण

	pr_debug("%s: led%i_per  0x%02x\n", DRIVER_NAME, led,
		i2c_smbus_पढ़ो_byte_data(the_tps->client,
				TPS_LED1_PER + offs));

	mutex_unlock(&the_tps->lock);

	वापस status;
पूर्ण
EXPORT_SYMBOL(tps65010_set_led);

/*-------------------------------------------------------------------------*/
/* tps65010_set_vib parameter:
 * value: ON or OFF
 */
पूर्णांक tps65010_set_vib(अचिन्हित value)
अणु
	पूर्णांक	 status;
	अचिन्हित vdcdc2;

	अगर (!the_tps)
		वापस -ENODEV;

	mutex_lock(&the_tps->lock);

	vdcdc2 = i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_VDCDC2);
	vdcdc2 &= ~(1 << 1);
	अगर (value)
		vdcdc2 |= (1 << 1);
	status = i2c_smbus_ग_लिखो_byte_data(the_tps->client,
		TPS_VDCDC2, vdcdc2);

	pr_debug("%s: vibrator %s\n", DRIVER_NAME, value ? "on" : "off");

	mutex_unlock(&the_tps->lock);
	वापस status;
पूर्ण
EXPORT_SYMBOL(tps65010_set_vib);

/*-------------------------------------------------------------------------*/
/* tps65010_set_low_pwr parameter:
 * mode: ON or OFF
 */
पूर्णांक tps65010_set_low_pwr(अचिन्हित mode)
अणु
	पूर्णांक	 status;
	अचिन्हित vdcdc1;

	अगर (!the_tps)
		वापस -ENODEV;

	mutex_lock(&the_tps->lock);

	pr_debug("%s: %s low_pwr, vdcdc1 0x%02x\n", DRIVER_NAME,
		mode ? "enable" : "disable",
		i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_VDCDC1));

	vdcdc1 = i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_VDCDC1);

	चयन (mode) अणु
	हाल OFF:
		vdcdc1 &= ~TPS_ENABLE_LP; /* disable ENABLE_LP bit */
		अवरोध;
	/* हाल ON: */
	शेष:
		vdcdc1 |= TPS_ENABLE_LP;  /* enable ENABLE_LP bit */
		अवरोध;
	पूर्ण

	status = i2c_smbus_ग_लिखो_byte_data(the_tps->client,
			TPS_VDCDC1, vdcdc1);

	अगर (status != 0)
		prपूर्णांकk(KERN_ERR "%s: Failed to write vdcdc1 register\n",
			DRIVER_NAME);
	अन्यथा
		pr_debug("%s: vdcdc1 0x%02x\n", DRIVER_NAME,
			i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_VDCDC1));

	mutex_unlock(&the_tps->lock);

	वापस status;
पूर्ण
EXPORT_SYMBOL(tps65010_set_low_pwr);

/*-------------------------------------------------------------------------*/
/* tps65010_config_vregs1 parameter:
 * value to be written to VREGS1 रेजिस्टर
 * Note: The complete रेजिस्टर is written, set all bits you need
 */
पूर्णांक tps65010_config_vregs1(अचिन्हित value)
अणु
	पूर्णांक	 status;

	अगर (!the_tps)
		वापस -ENODEV;

	mutex_lock(&the_tps->lock);

	pr_debug("%s: vregs1 0x%02x\n", DRIVER_NAME,
			i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_VREGS1));

	status = i2c_smbus_ग_लिखो_byte_data(the_tps->client,
			TPS_VREGS1, value);

	अगर (status != 0)
		prपूर्णांकk(KERN_ERR "%s: Failed to write vregs1 register\n",
			DRIVER_NAME);
	अन्यथा
		pr_debug("%s: vregs1 0x%02x\n", DRIVER_NAME,
			i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_VREGS1));

	mutex_unlock(&the_tps->lock);

	वापस status;
पूर्ण
EXPORT_SYMBOL(tps65010_config_vregs1);

पूर्णांक tps65010_config_vdcdc2(अचिन्हित value)
अणु
	काष्ठा i2c_client *c;
	पूर्णांक	 status;

	अगर (!the_tps)
		वापस -ENODEV;

	c = the_tps->client;
	mutex_lock(&the_tps->lock);

	pr_debug("%s: vdcdc2 0x%02x\n", DRIVER_NAME,
		 i2c_smbus_पढ़ो_byte_data(c, TPS_VDCDC2));

	status = i2c_smbus_ग_लिखो_byte_data(c, TPS_VDCDC2, value);

	अगर (status != 0)
		prपूर्णांकk(KERN_ERR "%s: Failed to write vdcdc2 register\n",
			DRIVER_NAME);
	अन्यथा
		pr_debug("%s: vregs1 0x%02x\n", DRIVER_NAME,
			 i2c_smbus_पढ़ो_byte_data(c, TPS_VDCDC2));

	mutex_unlock(&the_tps->lock);
	वापस status;
पूर्ण
EXPORT_SYMBOL(tps65010_config_vdcdc2);

/*-------------------------------------------------------------------------*/
/* tps65013_set_low_pwr parameter:
 * mode: ON or OFF
 */

/* FIXME: Assumes AC or USB घातer is present. Setting AUA bit is not
	required अगर घातer supply is through a battery */

पूर्णांक tps65013_set_low_pwr(अचिन्हित mode)
अणु
	पूर्णांक	 status;
	अचिन्हित vdcdc1, chgconfig;

	अगर (!the_tps || the_tps->por)
		वापस -ENODEV;

	mutex_lock(&the_tps->lock);

	pr_debug("%s: %s low_pwr, chgconfig 0x%02x vdcdc1 0x%02x\n",
		DRIVER_NAME,
		mode ? "enable" : "disable",
		i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_CHGCONFIG),
		i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_VDCDC1));

	chgconfig = i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_CHGCONFIG);
	vdcdc1 = i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_VDCDC1);

	चयन (mode) अणु
	हाल OFF:
		chgconfig &= ~TPS65013_AUA; /* disable AUA bit */
		vdcdc1 &= ~TPS_ENABLE_LP; /* disable ENABLE_LP bit */
		अवरोध;
	/* हाल ON: */
	शेष:
		chgconfig |= TPS65013_AUA;  /* enable AUA bit */
		vdcdc1 |= TPS_ENABLE_LP;  /* enable ENABLE_LP bit */
		अवरोध;
	पूर्ण

	status = i2c_smbus_ग_लिखो_byte_data(the_tps->client,
			TPS_CHGCONFIG, chgconfig);
	अगर (status != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to write chconfig register\n",
	 DRIVER_NAME);
		mutex_unlock(&the_tps->lock);
		वापस status;
	पूर्ण

	chgconfig = i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_CHGCONFIG);
	the_tps->chgconf = chgconfig;
	show_chgconfig(0, "chgconf", chgconfig);

	status = i2c_smbus_ग_लिखो_byte_data(the_tps->client,
			TPS_VDCDC1, vdcdc1);

	अगर (status != 0)
		prपूर्णांकk(KERN_ERR "%s: Failed to write vdcdc1 register\n",
	 DRIVER_NAME);
	अन्यथा
		pr_debug("%s: vdcdc1 0x%02x\n", DRIVER_NAME,
			i2c_smbus_पढ़ो_byte_data(the_tps->client, TPS_VDCDC1));

	mutex_unlock(&the_tps->lock);

	वापस status;
पूर्ण
EXPORT_SYMBOL(tps65013_set_low_pwr);

/*-------------------------------------------------------------------------*/

अटल पूर्णांक __init tps_init(व्योम)
अणु
	वापस i2c_add_driver(&tps65010_driver);
पूर्ण
/* NOTE:  this MUST be initialized beक्रमe the other parts of the प्रणाली
 * that rely on it ... but after the i2c bus on which this relies.
 * That is, much earlier than on PC-type प्रणालीs, which करोn't often use
 * I2C as a core प्रणाली bus.
 */
subsys_initcall(tps_init);

अटल व्योम __निकास tps_निकास(व्योम)
अणु
	i2c_del_driver(&tps65010_driver);
पूर्ण
module_निकास(tps_निकास);

