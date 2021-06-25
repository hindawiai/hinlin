<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/i2c/chips/lm8323.c
 *
 * Copyright (C) 2007-2009 Nokia Corporation
 *
 * Written by Daniel Stone <daniel.stone@nokia.com>
 *            Timo O. Karjalainen <timo.o.karjalainen@nokia.com>
 *
 * Updated by Felipe Balbi <felipe.balbi@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_data/lm8323.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>

/* Commands to send to the chip. */
#घोषणा LM8323_CMD_READ_ID		0x80 /* Read chip ID. */
#घोषणा LM8323_CMD_WRITE_CFG		0x81 /* Set configuration item. */
#घोषणा LM8323_CMD_READ_INT		0x82 /* Get पूर्णांकerrupt status. */
#घोषणा LM8323_CMD_RESET		0x83 /* Reset, same as बाह्यal one */
#घोषणा LM8323_CMD_WRITE_PORT_SEL	0x85 /* Set GPIO in/out. */
#घोषणा LM8323_CMD_WRITE_PORT_STATE	0x86 /* Set GPIO pullup. */
#घोषणा LM8323_CMD_READ_PORT_SEL	0x87 /* Get GPIO in/out. */
#घोषणा LM8323_CMD_READ_PORT_STATE	0x88 /* Get GPIO pullup. */
#घोषणा LM8323_CMD_READ_FIFO		0x89 /* Read byte from FIFO. */
#घोषणा LM8323_CMD_RPT_READ_FIFO	0x8a /* Read FIFO (no increment). */
#घोषणा LM8323_CMD_SET_ACTIVE		0x8b /* Set active समय. */
#घोषणा LM8323_CMD_READ_ERR		0x8c /* Get error status. */
#घोषणा LM8323_CMD_READ_ROTATOR		0x8e /* Read rotator status. */
#घोषणा LM8323_CMD_SET_DEBOUNCE		0x8f /* Set debouncing समय. */
#घोषणा LM8323_CMD_SET_KEY_SIZE		0x90 /* Set keypad size. */
#घोषणा LM8323_CMD_READ_KEY_SIZE	0x91 /* Get keypad size. */
#घोषणा LM8323_CMD_READ_CFG		0x92 /* Get configuration item. */
#घोषणा LM8323_CMD_WRITE_CLOCK		0x93 /* Set घड़ी config. */
#घोषणा LM8323_CMD_READ_CLOCK		0x94 /* Get घड़ी config. */
#घोषणा LM8323_CMD_PWM_WRITE		0x95 /* Write PWM script. */
#घोषणा LM8323_CMD_START_PWM		0x96 /* Start PWM engine. */
#घोषणा LM8323_CMD_STOP_PWM		0x97 /* Stop PWM engine. */

/* Interrupt status. */
#घोषणा INT_KEYPAD			0x01 /* Key event. */
#घोषणा INT_ROTATOR			0x02 /* Rotator event. */
#घोषणा INT_ERROR			0x08 /* Error: use CMD_READ_ERR. */
#घोषणा INT_NOINIT			0x10 /* Lost configuration. */
#घोषणा INT_PWM1			0x20 /* PWM1 stopped. */
#घोषणा INT_PWM2			0x40 /* PWM2 stopped. */
#घोषणा INT_PWM3			0x80 /* PWM3 stopped. */

/* Errors (संकेतled by INT_ERROR, पढ़ो with CMD_READ_ERR). */
#घोषणा ERR_BADPAR			0x01 /* Bad parameter. */
#घोषणा ERR_CMDUNK			0x02 /* Unknown command. */
#घोषणा ERR_KEYOVR			0x04 /* Too many keys pressed. */
#घोषणा ERR_FIFOOVER			0x40 /* FIFO overflow. */

/* Configuration keys (CMD_अणुWRITE,READपूर्ण_CFG). */
#घोषणा CFG_MUX1SEL			0x01 /* Select MUX1_OUT input. */
#घोषणा CFG_MUX1EN			0x02 /* Enable MUX1_OUT. */
#घोषणा CFG_MUX2SEL			0x04 /* Select MUX2_OUT input. */
#घोषणा CFG_MUX2EN			0x08 /* Enable MUX2_OUT. */
#घोषणा CFG_PSIZE			0x20 /* Package size (must be 0). */
#घोषणा CFG_ROTEN			0x40 /* Enable rotator. */

/* Clock settings (CMD_अणुWRITE,READपूर्ण_CLOCK). */
#घोषणा CLK_RCPWM_INTERNAL		0x00
#घोषणा CLK_RCPWM_EXTERNAL		0x03
#घोषणा CLK_SLOWCLKEN			0x08 /* Enable 32.768kHz घड़ी. */
#घोषणा CLK_SLOWCLKOUT			0x40 /* Enable slow pulse output. */

/* The possible addresses corresponding to CONFIG1 and CONFIG2 pin wirings. */
#घोषणा LM8323_I2C_ADDR00		(0x84 >> 1)	/* 1000 010x */
#घोषणा LM8323_I2C_ADDR01		(0x86 >> 1)	/* 1000 011x */
#घोषणा LM8323_I2C_ADDR10		(0x88 >> 1)	/* 1000 100x */
#घोषणा LM8323_I2C_ADDR11		(0x8A >> 1)	/* 1000 101x */

/* Key event fअगरo length */
#घोषणा LM8323_FIFO_LEN			15

/* Commands क्रम PWM engine; feed in with PWM_WRITE. */
/* Load ramp counter from duty cycle field (range 0 - 0xff). */
#घोषणा PWM_SET(v)			(0x4000 | ((v) & 0xff))
/* Go to start of script. */
#घोषणा PWM_GOTOSTART			0x0000
/*
 * Stop engine (generates पूर्णांकerrupt).  If reset is 1, clear the program
 * counter, अन्यथा leave it.
 */
#घोषणा PWM_END(reset)			(0xc000 | (!!(reset) << 11))
/*
 * Ramp.  If s is 1, भागide घड़ी by 512, अन्यथा भागide घड़ी by 16.
 * Take t घड़ी scales (up to 63) per step, क्रम n steps (up to 126).
 * If u is set, ramp up, अन्यथा ramp करोwn.
 */
#घोषणा PWM_RAMP(s, t, n, u)		((!!(s) << 14) | ((t) & 0x3f) << 8 | \
					 ((n) & 0x7f) | ((u) ? 0 : 0x80))
/*
 * Loop (i.e. jump back to pos) क्रम a given number of iterations (up to 63).
 * If cnt is zero, execute until PWM_END is encountered.
 */
#घोषणा PWM_LOOP(cnt, pos)		(0xa000 | (((cnt) & 0x3f) << 7) | \
					 ((pos) & 0x3f))
/*
 * Wait क्रम trigger.  Argument is a mask of channels, shअगरted by the channel
 * number, e.g. 0xa क्रम channels 3 and 1.  Note that channels are numbered
 * from 1, not 0.
 */
#घोषणा PWM_WAIT_TRIG(chans)		(0xe000 | (((chans) & 0x7) << 6))
/* Send trigger.  Argument is same as PWM_WAIT_TRIG. */
#घोषणा PWM_SEND_TRIG(chans)		(0xe000 | ((chans) & 0x7))

काष्ठा lm8323_pwm अणु
	पूर्णांक			id;
	पूर्णांक			fade_समय;
	पूर्णांक			brightness;
	पूर्णांक			desired_brightness;
	bool			enabled;
	bool			running;
	/* pwm lock */
	काष्ठा mutex		lock;
	काष्ठा work_काष्ठा	work;
	काष्ठा led_classdev	cdev;
	काष्ठा lm8323_chip	*chip;
पूर्ण;

काष्ठा lm8323_chip अणु
	/* device lock */
	काष्ठा mutex		lock;
	काष्ठा i2c_client	*client;
	काष्ठा input_dev	*idev;
	bool			kp_enabled;
	bool			pm_suspend;
	अचिन्हित		keys_करोwn;
	अक्षर			phys[32];
	अचिन्हित लघु		keymap[LM8323_KEYMAP_SIZE];
	पूर्णांक			size_x;
	पूर्णांक			size_y;
	पूर्णांक			debounce_समय;
	पूर्णांक			active_समय;
	काष्ठा lm8323_pwm	pwm[LM8323_NUM_PWMS];
पूर्ण;

#घोषणा client_to_lm8323(c)	container_of(c, काष्ठा lm8323_chip, client)
#घोषणा dev_to_lm8323(d)	container_of(d, काष्ठा lm8323_chip, client->dev)
#घोषणा cdev_to_pwm(c)		container_of(c, काष्ठा lm8323_pwm, cdev)
#घोषणा work_to_pwm(w)		container_of(w, काष्ठा lm8323_pwm, work)

#घोषणा LM8323_MAX_DATA 8

/*
 * To ग_लिखो, we just access the chip's address in ग_लिखो mode, and dump the
 * command and data out on the bus.  The command byte and data are taken as
 * sequential u8s out of varargs, to a maximum of LM8323_MAX_DATA.
 */
अटल पूर्णांक lm8323_ग_लिखो(काष्ठा lm8323_chip *lm, पूर्णांक len, ...)
अणु
	पूर्णांक ret, i;
	बहु_सूची ap;
	u8 data[LM8323_MAX_DATA];

	बहु_शुरू(ap, len);

	अगर (unlikely(len > LM8323_MAX_DATA)) अणु
		dev_err(&lm->client->dev, "tried to send %d bytes\n", len);
		बहु_पूर्ण(ap);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < len; i++)
		data[i] = बहु_तर्क(ap, पूर्णांक);

	बहु_पूर्ण(ap);

	/*
	 * If the host is asleep जबतक we send the data, we can get a NACK
	 * back जबतक it wakes up, so try again, once.
	 */
	ret = i2c_master_send(lm->client, data, len);
	अगर (unlikely(ret == -EREMOTEIO))
		ret = i2c_master_send(lm->client, data, len);
	अगर (unlikely(ret != len))
		dev_err(&lm->client->dev, "sent %d bytes of %d total\n",
			len, ret);

	वापस ret;
पूर्ण

/*
 * To पढ़ो, we first send the command byte to the chip and end the transaction,
 * then access the chip in पढ़ो mode, at which poपूर्णांक it will send the data.
 */
अटल पूर्णांक lm8323_पढ़ो(काष्ठा lm8323_chip *lm, u8 cmd, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;

	/*
	 * If the host is asleep जबतक we send the byte, we can get a NACK
	 * back जबतक it wakes up, so try again, once.
	 */
	ret = i2c_master_send(lm->client, &cmd, 1);
	अगर (unlikely(ret == -EREMOTEIO))
		ret = i2c_master_send(lm->client, &cmd, 1);
	अगर (unlikely(ret != 1)) अणु
		dev_err(&lm->client->dev, "sending read cmd 0x%02x failed\n",
			cmd);
		वापस 0;
	पूर्ण

	ret = i2c_master_recv(lm->client, buf, len);
	अगर (unlikely(ret != len))
		dev_err(&lm->client->dev, "wanted %d bytes, got %d\n",
			len, ret);

	वापस ret;
पूर्ण

/*
 * Set the chip active समय (idle समय beक्रमe it enters halt).
 */
अटल व्योम lm8323_set_active_समय(काष्ठा lm8323_chip *lm, पूर्णांक समय)
अणु
	lm8323_ग_लिखो(lm, 2, LM8323_CMD_SET_ACTIVE, समय >> 2);
पूर्ण

/*
 * The संकेतs are AT-style: the low 7 bits are the keycode, and the top
 * bit indicates the state (1 क्रम करोwn, 0 क्रम up).
 */
अटल अंतरभूत u8 lm8323_whichkey(u8 event)
अणु
	वापस event & 0x7f;
पूर्ण

अटल अंतरभूत पूर्णांक lm8323_ispress(u8 event)
अणु
	वापस (event & 0x80) ? 1 : 0;
पूर्ण

अटल व्योम process_keys(काष्ठा lm8323_chip *lm)
अणु
	u8 event;
	u8 key_fअगरo[LM8323_FIFO_LEN + 1];
	पूर्णांक old_keys_करोwn = lm->keys_करोwn;
	पूर्णांक ret;
	पूर्णांक i = 0;

	/*
	 * Read all key events from the FIFO at once. Next READ_FIFO clears the
	 * FIFO even अगर we didn't पढ़ो all events previously.
	 */
	ret = lm8323_पढ़ो(lm, LM8323_CMD_READ_FIFO, key_fअगरo, LM8323_FIFO_LEN);

	अगर (ret < 0) अणु
		dev_err(&lm->client->dev, "Failed reading fifo \n");
		वापस;
	पूर्ण
	key_fअगरo[ret] = 0;

	जबतक ((event = key_fअगरo[i++])) अणु
		u8 key = lm8323_whichkey(event);
		पूर्णांक isकरोwn = lm8323_ispress(event);
		अचिन्हित लघु keycode = lm->keymap[key];

		dev_vdbg(&lm->client->dev, "key 0x%02x %s\n",
			 key, isकरोwn ? "down" : "up");

		अगर (lm->kp_enabled) अणु
			input_event(lm->idev, EV_MSC, MSC_SCAN, key);
			input_report_key(lm->idev, keycode, isकरोwn);
			input_sync(lm->idev);
		पूर्ण

		अगर (isकरोwn)
			lm->keys_करोwn++;
		अन्यथा
			lm->keys_करोwn--;
	पूर्ण

	/*
	 * Errata: We need to ensure that the chip never enters halt mode
	 * during a keypress, so set active समय to 0.  When it's released,
	 * we can enter halt again, so set the active समय back to normal.
	 */
	अगर (!old_keys_करोwn && lm->keys_करोwn)
		lm8323_set_active_समय(lm, 0);
	अगर (old_keys_करोwn && !lm->keys_करोwn)
		lm8323_set_active_समय(lm, lm->active_समय);
पूर्ण

अटल व्योम lm8323_process_error(काष्ठा lm8323_chip *lm)
अणु
	u8 error;

	अगर (lm8323_पढ़ो(lm, LM8323_CMD_READ_ERR, &error, 1) == 1) अणु
		अगर (error & ERR_FIFOOVER)
			dev_vdbg(&lm->client->dev, "fifo overflow!\n");
		अगर (error & ERR_KEYOVR)
			dev_vdbg(&lm->client->dev,
					"more than two keys pressed\n");
		अगर (error & ERR_CMDUNK)
			dev_vdbg(&lm->client->dev,
					"unknown command submitted\n");
		अगर (error & ERR_BADPAR)
			dev_vdbg(&lm->client->dev, "bad command parameter\n");
	पूर्ण
पूर्ण

अटल व्योम lm8323_reset(काष्ठा lm8323_chip *lm)
अणु
	/* The करोcs say we must pass 0xAA as the data byte. */
	lm8323_ग_लिखो(lm, 2, LM8323_CMD_RESET, 0xAA);
पूर्ण

अटल पूर्णांक lm8323_configure(काष्ठा lm8323_chip *lm)
अणु
	पूर्णांक keysize = (lm->size_x << 4) | lm->size_y;
	पूर्णांक घड़ी = (CLK_SLOWCLKEN | CLK_RCPWM_EXTERNAL);
	पूर्णांक debounce = lm->debounce_समय >> 2;
	पूर्णांक active = lm->active_समय >> 2;

	/*
	 * Active समय must be greater than the debounce समय: अगर it's
	 * a बंद-run thing, give ourselves a 12ms buffer.
	 */
	अगर (debounce >= active)
		active = debounce + 3;

	lm8323_ग_लिखो(lm, 2, LM8323_CMD_WRITE_CFG, 0);
	lm8323_ग_लिखो(lm, 2, LM8323_CMD_WRITE_CLOCK, घड़ी);
	lm8323_ग_लिखो(lm, 2, LM8323_CMD_SET_KEY_SIZE, keysize);
	lm8323_set_active_समय(lm, lm->active_समय);
	lm8323_ग_लिखो(lm, 2, LM8323_CMD_SET_DEBOUNCE, debounce);
	lm8323_ग_लिखो(lm, 3, LM8323_CMD_WRITE_PORT_STATE, 0xff, 0xff);
	lm8323_ग_लिखो(lm, 3, LM8323_CMD_WRITE_PORT_SEL, 0, 0);

	/*
	 * Not much we can करो about errors at this poपूर्णांक, so just hope
	 * क्रम the best.
	 */

	वापस 0;
पूर्ण

अटल व्योम pwm_करोne(काष्ठा lm8323_pwm *pwm)
अणु
	mutex_lock(&pwm->lock);
	pwm->running = false;
	अगर (pwm->desired_brightness != pwm->brightness)
		schedule_work(&pwm->work);
	mutex_unlock(&pwm->lock);
पूर्ण

/*
 * Bottom half: handle the पूर्णांकerrupt by posting key events, or dealing with
 * errors appropriately.
 */
अटल irqवापस_t lm8323_irq(पूर्णांक irq, व्योम *_lm)
अणु
	काष्ठा lm8323_chip *lm = _lm;
	u8 पूर्णांकs;
	पूर्णांक i;

	mutex_lock(&lm->lock);

	जबतक ((lm8323_पढ़ो(lm, LM8323_CMD_READ_INT, &पूर्णांकs, 1) == 1) && पूर्णांकs) अणु
		अगर (likely(पूर्णांकs & INT_KEYPAD))
			process_keys(lm);
		अगर (पूर्णांकs & INT_ROTATOR) अणु
			/* We करोn't currently support the rotator. */
			dev_vdbg(&lm->client->dev, "rotator fired\n");
		पूर्ण
		अगर (पूर्णांकs & INT_ERROR) अणु
			dev_vdbg(&lm->client->dev, "error!\n");
			lm8323_process_error(lm);
		पूर्ण
		अगर (पूर्णांकs & INT_NOINIT) अणु
			dev_err(&lm->client->dev, "chip lost config; "
						  "reinitialising\n");
			lm8323_configure(lm);
		पूर्ण
		क्रम (i = 0; i < LM8323_NUM_PWMS; i++) अणु
			अगर (पूर्णांकs & (INT_PWM1 << i)) अणु
				dev_vdbg(&lm->client->dev,
					 "pwm%d engine completed\n", i);
				pwm_करोne(&lm->pwm[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&lm->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Read the chip ID.
 */
अटल पूर्णांक lm8323_पढ़ो_id(काष्ठा lm8323_chip *lm, u8 *buf)
अणु
	पूर्णांक bytes;

	bytes = lm8323_पढ़ो(lm, LM8323_CMD_READ_ID, buf, 2);
	अगर (unlikely(bytes != 2))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम lm8323_ग_लिखो_pwm_one(काष्ठा lm8323_pwm *pwm, पूर्णांक pos, u16 cmd)
अणु
	lm8323_ग_लिखो(pwm->chip, 4, LM8323_CMD_PWM_WRITE, (pos << 2) | pwm->id,
		     (cmd & 0xff00) >> 8, cmd & 0x00ff);
पूर्ण

/*
 * Write a script पूर्णांकo a given PWM engine, concluding with PWM_END.
 * If 'kill' is nonzero, the engine will be shut करोwn at the end
 * of the script, producing a zero output. Otherwise the engine
 * will be kept running at the final PWM level indefinitely.
 */
अटल व्योम lm8323_ग_लिखो_pwm(काष्ठा lm8323_pwm *pwm, पूर्णांक समाप्त,
			     पूर्णांक len, स्थिर u16 *cmds)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		lm8323_ग_लिखो_pwm_one(pwm, i, cmds[i]);

	lm8323_ग_लिखो_pwm_one(pwm, i++, PWM_END(समाप्त));
	lm8323_ग_लिखो(pwm->chip, 2, LM8323_CMD_START_PWM, pwm->id);
	pwm->running = true;
पूर्ण

अटल व्योम lm8323_pwm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lm8323_pwm *pwm = work_to_pwm(work);
	पूर्णांक भाग512, perstep, steps, hz, up, समाप्त;
	u16 pwm_cmds[3];
	पूर्णांक num_cmds = 0;

	mutex_lock(&pwm->lock);

	/*
	 * Do nothing अगर we're alपढ़ोy at the requested level,
	 * or previous setting is not yet complete. In the latter
	 * हाल we will be called again when the previous PWM script
	 * finishes.
	 */
	अगर (pwm->running || pwm->desired_brightness == pwm->brightness)
		जाओ out;

	समाप्त = (pwm->desired_brightness == 0);
	up = (pwm->desired_brightness > pwm->brightness);
	steps = असल(pwm->desired_brightness - pwm->brightness);

	/*
	 * Convert समय (in ms) पूर्णांकo a भागisor (512 or 16 on a refclk of
	 * 32768Hz), and number of ticks per step.
	 */
	अगर ((pwm->fade_समय / steps) > (32768 / 512)) अणु
		भाग512 = 1;
		hz = 32768 / 512;
	पूर्ण अन्यथा अणु
		भाग512 = 0;
		hz = 32768 / 16;
	पूर्ण

	perstep = (hz * pwm->fade_समय) / (steps * 1000);

	अगर (perstep == 0)
		perstep = 1;
	अन्यथा अगर (perstep > 63)
		perstep = 63;

	जबतक (steps) अणु
		पूर्णांक s;

		s = min(126, steps);
		pwm_cmds[num_cmds++] = PWM_RAMP(भाग512, perstep, s, up);
		steps -= s;
	पूर्ण

	lm8323_ग_लिखो_pwm(pwm, समाप्त, num_cmds, pwm_cmds);
	pwm->brightness = pwm->desired_brightness;

 out:
	mutex_unlock(&pwm->lock);
पूर्ण

अटल व्योम lm8323_pwm_set_brightness(काष्ठा led_classdev *led_cdev,
				      क्रमागत led_brightness brightness)
अणु
	काष्ठा lm8323_pwm *pwm = cdev_to_pwm(led_cdev);
	काष्ठा lm8323_chip *lm = pwm->chip;

	mutex_lock(&pwm->lock);
	pwm->desired_brightness = brightness;
	mutex_unlock(&pwm->lock);

	अगर (in_पूर्णांकerrupt()) अणु
		schedule_work(&pwm->work);
	पूर्ण अन्यथा अणु
		/*
		 * Schedule PWM work as usual unless we are going पूर्णांकo suspend
		 */
		mutex_lock(&lm->lock);
		अगर (likely(!lm->pm_suspend))
			schedule_work(&pwm->work);
		अन्यथा
			lm8323_pwm_work(&pwm->work);
		mutex_unlock(&lm->lock);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार lm8323_pwm_show_समय(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm8323_pwm *pwm = cdev_to_pwm(led_cdev);

	वापस प्र_लिखो(buf, "%d\n", pwm->fade_समय);
पूर्ण

अटल sमाप_प्रकार lm8323_pwm_store_समय(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm8323_pwm *pwm = cdev_to_pwm(led_cdev);
	पूर्णांक ret, समय;

	ret = kstrtoपूर्णांक(buf, 10, &समय);
	/* Numbers only, please. */
	अगर (ret)
		वापस ret;

	pwm->fade_समय = समय;

	वापस म_माप(buf);
पूर्ण
अटल DEVICE_ATTR(समय, 0644, lm8323_pwm_show_समय, lm8323_pwm_store_समय);

अटल काष्ठा attribute *lm8323_pwm_attrs[] = अणु
	&dev_attr_समय.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lm8323_pwm);

अटल पूर्णांक init_pwm(काष्ठा lm8323_chip *lm, पूर्णांक id, काष्ठा device *dev,
		    स्थिर अक्षर *name)
अणु
	काष्ठा lm8323_pwm *pwm;

	BUG_ON(id > 3);

	pwm = &lm->pwm[id - 1];

	pwm->id = id;
	pwm->fade_समय = 0;
	pwm->brightness = 0;
	pwm->desired_brightness = 0;
	pwm->running = false;
	pwm->enabled = false;
	INIT_WORK(&pwm->work, lm8323_pwm_work);
	mutex_init(&pwm->lock);
	pwm->chip = lm;

	अगर (name) अणु
		pwm->cdev.name = name;
		pwm->cdev.brightness_set = lm8323_pwm_set_brightness;
		pwm->cdev.groups = lm8323_pwm_groups;
		अगर (led_classdev_रेजिस्टर(dev, &pwm->cdev) < 0) अणु
			dev_err(dev, "couldn't register PWM %d\n", id);
			वापस -1;
		पूर्ण
		pwm->enabled = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver lm8323_i2c_driver;

अटल sमाप_प्रकार lm8323_show_disable(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm8323_chip *lm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", !lm->kp_enabled);
पूर्ण

अटल sमाप_प्रकार lm8323_set_disable(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm8323_chip *lm = dev_get_drvdata(dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	ret = kstrtouपूर्णांक(buf, 10, &i);
	अगर (ret)
		वापस ret;

	mutex_lock(&lm->lock);
	lm->kp_enabled = !i;
	mutex_unlock(&lm->lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(disable_kp, 0644, lm8323_show_disable, lm8323_set_disable);

अटल पूर्णांक lm8323_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lm8323_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा input_dev *idev;
	काष्ठा lm8323_chip *lm;
	पूर्णांक pwm;
	पूर्णांक i, err;
	अचिन्हित दीर्घ पंचांगo;
	u8 data[2];

	अगर (!pdata || !pdata->size_x || !pdata->size_y) अणु
		dev_err(&client->dev, "missing platform_data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->size_x > 8) अणु
		dev_err(&client->dev, "invalid x size %d specified\n",
			pdata->size_x);
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->size_y > 12) अणु
		dev_err(&client->dev, "invalid y size %d specified\n",
			pdata->size_y);
		वापस -EINVAL;
	पूर्ण

	lm = kzalloc(माप *lm, GFP_KERNEL);
	idev = input_allocate_device();
	अगर (!lm || !idev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	lm->client = client;
	lm->idev = idev;
	mutex_init(&lm->lock);

	lm->size_x = pdata->size_x;
	lm->size_y = pdata->size_y;
	dev_vdbg(&client->dev, "Keypad size: %d x %d\n",
		 lm->size_x, lm->size_y);

	lm->debounce_समय = pdata->debounce_समय;
	lm->active_समय = pdata->active_समय;

	lm8323_reset(lm);

	/* Nothing's set up to service the IRQ yet, so just spin क्रम max.
	 * 100ms until we can configure. */
	पंचांगo = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (lm8323_पढ़ो(lm, LM8323_CMD_READ_INT, data, 1) == 1) अणु
		अगर (data[0] & INT_NOINIT)
			अवरोध;

		अगर (समय_after(jअगरfies, पंचांगo)) अणु
			dev_err(&client->dev,
				"timeout waiting for initialisation\n");
			अवरोध;
		पूर्ण

		msleep(1);
	पूर्ण

	lm8323_configure(lm);

	/* If a true probe check the device */
	अगर (lm8323_पढ़ो_id(lm, data) != 0) अणु
		dev_err(&client->dev, "device not found\n");
		err = -ENODEV;
		जाओ fail1;
	पूर्ण

	क्रम (pwm = 0; pwm < LM8323_NUM_PWMS; pwm++) अणु
		err = init_pwm(lm, pwm + 1, &client->dev,
			       pdata->pwm_names[pwm]);
		अगर (err < 0)
			जाओ fail2;
	पूर्ण

	lm->kp_enabled = true;
	err = device_create_file(&client->dev, &dev_attr_disable_kp);
	अगर (err < 0)
		जाओ fail2;

	idev->name = pdata->name ? : "LM8323 keypad";
	snम_लिखो(lm->phys, माप(lm->phys),
		 "%s/input-kp", dev_name(&client->dev));
	idev->phys = lm->phys;

	idev->evbit[0] = BIT(EV_KEY) | BIT(EV_MSC);
	__set_bit(MSC_SCAN, idev->mscbit);
	क्रम (i = 0; i < LM8323_KEYMAP_SIZE; i++) अणु
		__set_bit(pdata->keymap[i], idev->keybit);
		lm->keymap[i] = pdata->keymap[i];
	पूर्ण
	__clear_bit(KEY_RESERVED, idev->keybit);

	अगर (pdata->repeat)
		__set_bit(EV_REP, idev->evbit);

	err = input_रेजिस्टर_device(idev);
	अगर (err) अणु
		dev_dbg(&client->dev, "error registering input device\n");
		जाओ fail3;
	पूर्ण

	err = request_thपढ़ोed_irq(client->irq, शून्य, lm8323_irq,
			  IRQF_TRIGGER_LOW|IRQF_ONESHOT, "lm8323", lm);
	अगर (err) अणु
		dev_err(&client->dev, "could not get IRQ %d\n", client->irq);
		जाओ fail4;
	पूर्ण

	i2c_set_clientdata(client, lm);

	device_init_wakeup(&client->dev, 1);
	enable_irq_wake(client->irq);

	वापस 0;

fail4:
	input_unरेजिस्टर_device(idev);
	idev = शून्य;
fail3:
	device_हटाओ_file(&client->dev, &dev_attr_disable_kp);
fail2:
	जबतक (--pwm >= 0)
		अगर (lm->pwm[pwm].enabled)
			led_classdev_unरेजिस्टर(&lm->pwm[pwm].cdev);
fail1:
	input_मुक्त_device(idev);
	kमुक्त(lm);
	वापस err;
पूर्ण

अटल पूर्णांक lm8323_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm8323_chip *lm = i2c_get_clientdata(client);
	पूर्णांक i;

	disable_irq_wake(client->irq);
	मुक्त_irq(client->irq, lm);

	input_unरेजिस्टर_device(lm->idev);

	device_हटाओ_file(&lm->client->dev, &dev_attr_disable_kp);

	क्रम (i = 0; i < 3; i++)
		अगर (lm->pwm[i].enabled)
			led_classdev_unरेजिस्टर(&lm->pwm[i].cdev);

	kमुक्त(lm);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * We करोn't need to explicitly suspend the chip, as it alपढ़ोy चयनes off
 * when there's no activity.
 */
अटल पूर्णांक lm8323_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा lm8323_chip *lm = i2c_get_clientdata(client);
	पूर्णांक i;

	irq_set_irq_wake(client->irq, 0);
	disable_irq(client->irq);

	mutex_lock(&lm->lock);
	lm->pm_suspend = true;
	mutex_unlock(&lm->lock);

	क्रम (i = 0; i < 3; i++)
		अगर (lm->pwm[i].enabled)
			led_classdev_suspend(&lm->pwm[i].cdev);

	वापस 0;
पूर्ण

अटल पूर्णांक lm8323_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा lm8323_chip *lm = i2c_get_clientdata(client);
	पूर्णांक i;

	mutex_lock(&lm->lock);
	lm->pm_suspend = false;
	mutex_unlock(&lm->lock);

	क्रम (i = 0; i < 3; i++)
		अगर (lm->pwm[i].enabled)
			led_classdev_resume(&lm->pwm[i].cdev);

	enable_irq(client->irq);
	irq_set_irq_wake(client->irq, 1);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(lm8323_pm_ops, lm8323_suspend, lm8323_resume);

अटल स्थिर काष्ठा i2c_device_id lm8323_id[] = अणु
	अणु "lm8323", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver lm8323_i2c_driver = अणु
	.driver = अणु
		.name	= "lm8323",
		.pm	= &lm8323_pm_ops,
	पूर्ण,
	.probe		= lm8323_probe,
	.हटाओ		= lm8323_हटाओ,
	.id_table	= lm8323_id,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm8323_id);

module_i2c_driver(lm8323_i2c_driver);

MODULE_AUTHOR("Timo O. Karjalainen <timo.o.karjalainen@nokia.com>");
MODULE_AUTHOR("Daniel Stone");
MODULE_AUTHOR("Felipe Balbi <felipe.balbi@nokia.com>");
MODULE_DESCRIPTION("LM8323 keypad driver");
MODULE_LICENSE("GPL");

