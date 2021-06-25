<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rtc-ds1305.c -- driver क्रम DS1305 and DS1306 SPI RTC chips
 *
 * Copyright (C) 2008 David Brownell
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtc.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ds1305.h>
#समावेश <linux/module.h>


/*
 * Registers ... mask DS1305_WRITE पूर्णांकo रेजिस्टर address to ग_लिखो,
 * otherwise you're पढ़ोing it.  All non-biपंचांगask values are BCD.
 */
#घोषणा DS1305_WRITE		0x80


/* RTC date/समय ... the मुख्य special हालs are that we:
 *  - Need fancy "hours" encoding in 12hour mode
 *  - Don't rely on the "day-of-week" field (or पंचांग_wday)
 *  - Are a 21st-century घड़ी (2000 <= year < 2100)
 */
#घोषणा DS1305_RTC_LEN		7		/* bytes क्रम RTC regs */

#घोषणा DS1305_SEC		0x00		/* रेजिस्टर addresses */
#घोषणा DS1305_MIN		0x01
#घोषणा DS1305_HOUR		0x02
#	define DS1305_HR_12		0x40	/* set == 12 hr mode */
#	define DS1305_HR_PM		0x20	/* set == PM (12hr mode) */
#घोषणा DS1305_WDAY		0x03
#घोषणा DS1305_MDAY		0x04
#घोषणा DS1305_MON		0x05
#घोषणा DS1305_YEAR		0x06


/* The two alarms have only sec/min/hour/wday fields (ALM_LEN).
 * DS1305_ALM_DISABLE disables a match field (some combos are bad).
 *
 * NOTE that since we करोn't use WDAY, we limit ourselves to alarms
 * only one day पूर्णांकo the future (vs potentially up to a week).
 *
 * NOTE ALSO that जबतक we could generate once-a-second IRQs (UIE), we
 * करोn't currently support them.  We'd either need to करो it only when
 * no alarm is pending (not the standard model), or to use the second
 * alarm (implying that this is a DS1305 not DS1306, *and* that either
 * it's wired up a second IRQ we know, or that INTCN is set)
 */
#घोषणा DS1305_ALM_LEN		4		/* bytes क्रम ALM regs */
#घोषणा DS1305_ALM_DISABLE	0x80

#घोषणा DS1305_ALM0(r)		(0x07 + (r))	/* रेजिस्टर addresses */
#घोषणा DS1305_ALM1(r)		(0x0b + (r))


/* three control रेजिस्टरs */
#घोषणा DS1305_CONTROL_LEN	3		/* bytes of control regs */

#घोषणा DS1305_CONTROL		0x0f		/* रेजिस्टर addresses */
#	define DS1305_nEOSC		0x80	/* low enables oscillator */
#	define DS1305_WP		0x40	/* ग_लिखो protect */
#	define DS1305_INTCN		0x04	/* clear == only पूर्णांक0 used */
#	define DS1306_1HZ		0x04	/* enable 1Hz output */
#	define DS1305_AEI1		0x02	/* enable ALM1 IRQ */
#	define DS1305_AEI0		0x01	/* enable ALM0 IRQ */
#घोषणा DS1305_STATUS		0x10
/* status has just AEIx bits, mirrored as IRQFx */
#घोषणा DS1305_TRICKLE		0x11
/* trickle bits are defined in <linux/spi/ds1305.h> */

/* a bunch of NVRAM */
#घोषणा DS1305_NVRAM_LEN	96		/* bytes of NVRAM */

#घोषणा DS1305_NVRAM		0x20		/* रेजिस्टर addresses */


काष्ठा ds1305 अणु
	काष्ठा spi_device	*spi;
	काष्ठा rtc_device	*rtc;

	काष्ठा work_काष्ठा	work;

	अचिन्हित दीर्घ		flags;
#घोषणा FLAG_EXITING	0

	bool			hr12;
	u8			ctrl[DS1305_CONTROL_LEN];
पूर्ण;


/*----------------------------------------------------------------------*/

/*
 * Utilities ...  tolerate 12-hour AM/PM notation in हाल of non-Linux
 * software (like a bootloader) which may require it.
 */

अटल अचिन्हित bcd2hour(u8 bcd)
अणु
	अगर (bcd & DS1305_HR_12) अणु
		अचिन्हित	hour = 0;

		bcd &= ~DS1305_HR_12;
		अगर (bcd & DS1305_HR_PM) अणु
			hour = 12;
			bcd &= ~DS1305_HR_PM;
		पूर्ण
		hour += bcd2bin(bcd);
		वापस hour - 1;
	पूर्ण
	वापस bcd2bin(bcd);
पूर्ण

अटल u8 hour2bcd(bool hr12, पूर्णांक hour)
अणु
	अगर (hr12) अणु
		hour++;
		अगर (hour <= 12)
			वापस DS1305_HR_12 | bin2bcd(hour);
		hour -= 12;
		वापस DS1305_HR_12 | DS1305_HR_PM | bin2bcd(hour);
	पूर्ण
	वापस bin2bcd(hour);
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * Interface to RTC framework
 */

अटल पूर्णांक ds1305_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा ds1305	*ds1305 = dev_get_drvdata(dev);
	u8		buf[2];
	दीर्घ		err = -EINVAL;

	buf[0] = DS1305_WRITE | DS1305_CONTROL;
	buf[1] = ds1305->ctrl[0];

	अगर (enabled) अणु
		अगर (ds1305->ctrl[0] & DS1305_AEI0)
			जाओ करोne;
		buf[1] |= DS1305_AEI0;
	पूर्ण अन्यथा अणु
		अगर (!(buf[1] & DS1305_AEI0))
			जाओ करोne;
		buf[1] &= ~DS1305_AEI0;
	पूर्ण
	err = spi_ग_लिखो_then_पढ़ो(ds1305->spi, buf, माप(buf), शून्य, 0);
	अगर (err >= 0)
		ds1305->ctrl[0] = buf[1];
करोne:
	वापस err;

पूर्ण


/*
 * Get/set of date and समय is pretty normal.
 */

अटल पूर्णांक ds1305_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा ds1305	*ds1305 = dev_get_drvdata(dev);
	u8		addr = DS1305_SEC;
	u8		buf[DS1305_RTC_LEN];
	पूर्णांक		status;

	/* Use ग_लिखो-then-पढ़ो to get all the date/समय रेजिस्टरs
	 * since dma from stack is nonportable
	 */
	status = spi_ग_लिखो_then_पढ़ो(ds1305->spi, &addr, माप(addr),
			buf, माप(buf));
	अगर (status < 0)
		वापस status;

	dev_vdbg(dev, "%s: %3ph, %4ph\n", "read", &buf[0], &buf[3]);

	/* Decode the रेजिस्टरs */
	समय->पंचांग_sec = bcd2bin(buf[DS1305_SEC]);
	समय->पंचांग_min = bcd2bin(buf[DS1305_MIN]);
	समय->पंचांग_hour = bcd2hour(buf[DS1305_HOUR]);
	समय->पंचांग_wday = buf[DS1305_WDAY] - 1;
	समय->पंचांग_mday = bcd2bin(buf[DS1305_MDAY]);
	समय->पंचांग_mon = bcd2bin(buf[DS1305_MON]) - 1;
	समय->पंचांग_year = bcd2bin(buf[DS1305_YEAR]) + 100;

	dev_vdbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"read", समय->पंचांग_sec, समय->पंचांग_min,
		समय->पंचांग_hour, समय->पंचांग_mday,
		समय->पंचांग_mon, समय->पंचांग_year, समय->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1305_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा ds1305	*ds1305 = dev_get_drvdata(dev);
	u8		buf[1 + DS1305_RTC_LEN];
	u8		*bp = buf;

	dev_vdbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write", समय->पंचांग_sec, समय->पंचांग_min,
		समय->पंचांग_hour, समय->पंचांग_mday,
		समय->पंचांग_mon, समय->पंचांग_year, समय->पंचांग_wday);

	/* Write रेजिस्टरs starting at the first समय/date address. */
	*bp++ = DS1305_WRITE | DS1305_SEC;

	*bp++ = bin2bcd(समय->पंचांग_sec);
	*bp++ = bin2bcd(समय->पंचांग_min);
	*bp++ = hour2bcd(ds1305->hr12, समय->पंचांग_hour);
	*bp++ = (समय->पंचांग_wday < 7) ? (समय->पंचांग_wday + 1) : 1;
	*bp++ = bin2bcd(समय->पंचांग_mday);
	*bp++ = bin2bcd(समय->पंचांग_mon + 1);
	*bp++ = bin2bcd(समय->पंचांग_year - 100);

	dev_dbg(dev, "%s: %3ph, %4ph\n", "write", &buf[1], &buf[4]);

	/* use ग_लिखो-then-पढ़ो since dma from stack is nonportable */
	वापस spi_ग_लिखो_then_पढ़ो(ds1305->spi, buf, माप(buf),
			शून्य, 0);
पूर्ण

/*
 * Get/set of alarm is a bit funky:
 *
 * - First there's the inherent raciness of getting the (partitioned)
 *   status of an alarm that could trigger जबतक we're पढ़ोing parts
 *   of that status.
 *
 * - Second there's its limited range (we could increase it a bit by
 *   relying on WDAY), which means it will easily roll over.
 *
 * - Third there's the choice of two alarms and alarm संकेतs.
 *   Here we use ALM0 and expect that nINT0 (खोलो drain) is used;
 *   that's the only real option क्रम DS1306 runसमय alarms, and is
 *   natural on DS1305.
 *
 * - Fourth, there's also ALM1, and a second पूर्णांकerrupt संकेत:
 *     + On DS1305 ALM1 uses nINT1 (when INTCN=1) अन्यथा nINT0;
 *     + On DS1306 ALM1 only uses INT1 (an active high pulse)
 *       and it won't work when VCC1 is active.
 *
 *   So to be most general, we should probably set both alarms to the
 *   same value, letting ALM1 be the wakeup event source on DS1306
 *   and handling several wiring options on DS1305.
 *
 * - Fअगरth, we support the polled mode (as well as possible; why not?)
 *   even when no पूर्णांकerrupt line is wired to an IRQ.
 */

/*
 * Context: caller holds rtc->ops_lock (to protect ds1305->ctrl)
 */
अटल पूर्णांक ds1305_get_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा ds1305	*ds1305 = dev_get_drvdata(dev);
	काष्ठा spi_device *spi = ds1305->spi;
	u8		addr;
	पूर्णांक		status;
	u8		buf[DS1305_ALM_LEN];

	/* Refresh control रेजिस्टर cache BEFORE पढ़ोing ALM0 रेजिस्टरs,
	 * since पढ़ोing alarm रेजिस्टरs acks any pending IRQ.  That
	 * makes वापसing "pending" status a bit of a lie, but that bit
	 * of EFI status is at best fragile anyway (given IRQ handlers).
	 */
	addr = DS1305_CONTROL;
	status = spi_ग_लिखो_then_पढ़ो(spi, &addr, माप(addr),
			ds1305->ctrl, माप(ds1305->ctrl));
	अगर (status < 0)
		वापस status;

	alm->enabled = !!(ds1305->ctrl[0] & DS1305_AEI0);
	alm->pending = !!(ds1305->ctrl[1] & DS1305_AEI0);

	/* get and check ALM0 रेजिस्टरs */
	addr = DS1305_ALM0(DS1305_SEC);
	status = spi_ग_लिखो_then_पढ़ो(spi, &addr, माप(addr),
			buf, माप(buf));
	अगर (status < 0)
		वापस status;

	dev_vdbg(dev, "%s: %02x %02x %02x %02x\n",
		"alm0 read", buf[DS1305_SEC], buf[DS1305_MIN],
		buf[DS1305_HOUR], buf[DS1305_WDAY]);

	अगर ((DS1305_ALM_DISABLE & buf[DS1305_SEC])
			|| (DS1305_ALM_DISABLE & buf[DS1305_MIN])
			|| (DS1305_ALM_DISABLE & buf[DS1305_HOUR]))
		वापस -EIO;

	/* Stuff these values पूर्णांकo alm->समय and let RTC framework code
	 * fill in the rest ... and also handle rollover to tomorrow when
	 * that's needed.
	 */
	alm->समय.पंचांग_sec = bcd2bin(buf[DS1305_SEC]);
	alm->समय.पंचांग_min = bcd2bin(buf[DS1305_MIN]);
	alm->समय.पंचांग_hour = bcd2hour(buf[DS1305_HOUR]);

	वापस 0;
पूर्ण

/*
 * Context: caller holds rtc->ops_lock (to protect ds1305->ctrl)
 */
अटल पूर्णांक ds1305_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा ds1305	*ds1305 = dev_get_drvdata(dev);
	काष्ठा spi_device *spi = ds1305->spi;
	अचिन्हित दीर्घ	now, later;
	काष्ठा rtc_समय	पंचांग;
	पूर्णांक		status;
	u8		buf[1 + DS1305_ALM_LEN];

	/* convert desired alarm to समय_प्रकार */
	later = rtc_पंचांग_to_समय64(&alm->समय);

	/* Read current समय as समय_प्रकार */
	status = ds1305_get_समय(dev, &पंचांग);
	अगर (status < 0)
		वापस status;
	now = rtc_पंचांग_to_समय64(&पंचांग);

	/* make sure alarm fires within the next 24 hours */
	अगर (later <= now)
		वापस -EINVAL;
	अगर ((later - now) > 24 * 60 * 60)
		वापस -गलत_तर्क;

	/* disable alarm अगर needed */
	अगर (ds1305->ctrl[0] & DS1305_AEI0) अणु
		ds1305->ctrl[0] &= ~DS1305_AEI0;

		buf[0] = DS1305_WRITE | DS1305_CONTROL;
		buf[1] = ds1305->ctrl[0];
		status = spi_ग_लिखो_then_पढ़ो(ds1305->spi, buf, 2, शून्य, 0);
		अगर (status < 0)
			वापस status;
	पूर्ण

	/* ग_लिखो alarm */
	buf[0] = DS1305_WRITE | DS1305_ALM0(DS1305_SEC);
	buf[1 + DS1305_SEC] = bin2bcd(alm->समय.पंचांग_sec);
	buf[1 + DS1305_MIN] = bin2bcd(alm->समय.पंचांग_min);
	buf[1 + DS1305_HOUR] = hour2bcd(ds1305->hr12, alm->समय.पंचांग_hour);
	buf[1 + DS1305_WDAY] = DS1305_ALM_DISABLE;

	dev_dbg(dev, "%s: %02x %02x %02x %02x\n",
		"alm0 write", buf[1 + DS1305_SEC], buf[1 + DS1305_MIN],
		buf[1 + DS1305_HOUR], buf[1 + DS1305_WDAY]);

	status = spi_ग_लिखो_then_पढ़ो(spi, buf, माप(buf), शून्य, 0);
	अगर (status < 0)
		वापस status;

	/* enable alarm अगर requested */
	अगर (alm->enabled) अणु
		ds1305->ctrl[0] |= DS1305_AEI0;

		buf[0] = DS1305_WRITE | DS1305_CONTROL;
		buf[1] = ds1305->ctrl[0];
		status = spi_ग_लिखो_then_पढ़ो(ds1305->spi, buf, 2, शून्य, 0);
	पूर्ण

	वापस status;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल पूर्णांक ds1305_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा ds1305	*ds1305 = dev_get_drvdata(dev);
	अक्षर		*diodes = "no";
	अक्षर		*resistors = "";

	/* ctrl[2] is treated as पढ़ो-only; no locking needed */
	अगर ((ds1305->ctrl[2] & 0xf0) == DS1305_TRICKLE_MAGIC) अणु
		चयन (ds1305->ctrl[2] & 0x0c) अणु
		हाल DS1305_TRICKLE_DS2:
			diodes = "2 diodes, ";
			अवरोध;
		हाल DS1305_TRICKLE_DS1:
			diodes = "1 diode, ";
			अवरोध;
		शेष:
			जाओ करोne;
		पूर्ण
		चयन (ds1305->ctrl[2] & 0x03) अणु
		हाल DS1305_TRICKLE_2K:
			resistors = "2k Ohm";
			अवरोध;
		हाल DS1305_TRICKLE_4K:
			resistors = "4k Ohm";
			अवरोध;
		हाल DS1305_TRICKLE_8K:
			resistors = "8k Ohm";
			अवरोध;
		शेष:
			diodes = "no";
			अवरोध;
		पूर्ण
	पूर्ण

करोne:
	seq_म_लिखो(seq, "trickle_charge\t: %s%s\n", diodes, resistors);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा ds1305_proc	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा rtc_class_ops ds1305_ops = अणु
	.पढ़ो_समय	= ds1305_get_समय,
	.set_समय	= ds1305_set_समय,
	.पढ़ो_alarm	= ds1305_get_alarm,
	.set_alarm	= ds1305_set_alarm,
	.proc		= ds1305_proc,
	.alarm_irq_enable = ds1305_alarm_irq_enable,
पूर्ण;

अटल व्योम ds1305_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ds1305	*ds1305 = container_of(work, काष्ठा ds1305, work);
	काष्ठा spi_device *spi = ds1305->spi;
	u8		buf[3];
	पूर्णांक		status;

	/* lock to protect ds1305->ctrl */
	rtc_lock(ds1305->rtc);

	/* Disable the IRQ, and clear its status ... क्रम now, we "know"
	 * that अगर more than one alarm is active, they're in sync.
	 * Note that पढ़ोing ALM data रेजिस्टरs also clears IRQ status.
	 */
	ds1305->ctrl[0] &= ~(DS1305_AEI1 | DS1305_AEI0);
	ds1305->ctrl[1] = 0;

	buf[0] = DS1305_WRITE | DS1305_CONTROL;
	buf[1] = ds1305->ctrl[0];
	buf[2] = 0;

	status = spi_ग_लिखो_then_पढ़ो(spi, buf, माप(buf),
			शून्य, 0);
	अगर (status < 0)
		dev_dbg(&spi->dev, "clear irq --> %d\n", status);

	rtc_unlock(ds1305->rtc);

	अगर (!test_bit(FLAG_EXITING, &ds1305->flags))
		enable_irq(spi->irq);

	rtc_update_irq(ds1305->rtc, 1, RTC_AF | RTC_IRQF);
पूर्ण

/*
 * This "real" IRQ handler hands off to a workqueue mostly to allow
 * mutex locking क्रम ds1305->ctrl ... unlike I2C, we could issue async
 * I/O requests in IRQ context (to clear the IRQ status).
 */
अटल irqवापस_t ds1305_irq(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा ds1305		*ds1305 = p;

	disable_irq(irq);
	schedule_work(&ds1305->work);
	वापस IRQ_HANDLED;
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * Interface क्रम NVRAM
 */

अटल व्योम msg_init(काष्ठा spi_message *m, काष्ठा spi_transfer *x,
		u8 *addr, माप_प्रकार count, अक्षर *tx, अक्षर *rx)
अणु
	spi_message_init(m);
	स_रखो(x, 0, 2 * माप(*x));

	x->tx_buf = addr;
	x->len = 1;
	spi_message_add_tail(x, m);

	x++;

	x->tx_buf = tx;
	x->rx_buf = rx;
	x->len = count;
	spi_message_add_tail(x, m);
पूर्ण

अटल पूर्णांक ds1305_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *buf,
			     माप_प्रकार count)
अणु
	काष्ठा ds1305		*ds1305 = priv;
	काष्ठा spi_device	*spi = ds1305->spi;
	u8			addr;
	काष्ठा spi_message	m;
	काष्ठा spi_transfer	x[2];

	addr = DS1305_NVRAM + off;
	msg_init(&m, x, &addr, count, शून्य, buf);

	वापस spi_sync(spi, &m);
पूर्ण

अटल पूर्णांक ds1305_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *buf,
			      माप_प्रकार count)
अणु
	काष्ठा ds1305		*ds1305 = priv;
	काष्ठा spi_device	*spi = ds1305->spi;
	u8			addr;
	काष्ठा spi_message	m;
	काष्ठा spi_transfer	x[2];

	addr = (DS1305_WRITE | DS1305_NVRAM) + off;
	msg_init(&m, x, &addr, count, buf, शून्य);

	वापस spi_sync(spi, &m);
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * Interface to SPI stack
 */

अटल पूर्णांक ds1305_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ds1305			*ds1305;
	पूर्णांक				status;
	u8				addr, value;
	काष्ठा ds1305_platक्रमm_data	*pdata = dev_get_platdata(&spi->dev);
	bool				ग_लिखो_ctrl = false;
	काष्ठा nvmem_config ds1305_nvmem_cfg = अणु
		.name = "ds1305_nvram",
		.word_size = 1,
		.stride = 1,
		.size = DS1305_NVRAM_LEN,
		.reg_पढ़ो = ds1305_nvram_पढ़ो,
		.reg_ग_लिखो = ds1305_nvram_ग_लिखो,
	पूर्ण;

	/* Sanity check board setup data.  This may be hooked up
	 * in 3wire mode, but we करोn't care.  Note that unless
	 * there's an inverter in place, this needs SPI_CS_HIGH!
	 */
	अगर ((spi->bits_per_word && spi->bits_per_word != 8)
			|| (spi->max_speed_hz > 2000000)
			|| !(spi->mode & SPI_CPHA))
		वापस -EINVAL;

	/* set up driver data */
	ds1305 = devm_kzalloc(&spi->dev, माप(*ds1305), GFP_KERNEL);
	अगर (!ds1305)
		वापस -ENOMEM;
	ds1305->spi = spi;
	spi_set_drvdata(spi, ds1305);

	/* पढ़ो and cache control रेजिस्टरs */
	addr = DS1305_CONTROL;
	status = spi_ग_लिखो_then_पढ़ो(spi, &addr, माप(addr),
			ds1305->ctrl, माप(ds1305->ctrl));
	अगर (status < 0) अणु
		dev_dbg(&spi->dev, "can't %s, %d\n",
				"read", status);
		वापस status;
	पूर्ण

	dev_dbg(&spi->dev, "ctrl %s: %3ph\n", "read", ds1305->ctrl);

	/* Sanity check रेजिस्टर values ... partially compensating क्रम the
	 * fact that SPI has no device handshake.  A pullup on MISO would
	 * make these tests fail; but not all प्रणालीs will have one.  If
	 * some रेजिस्टर is neither 0x00 nor 0xff, a chip is likely there.
	 */
	अगर ((ds1305->ctrl[0] & 0x38) != 0 || (ds1305->ctrl[1] & 0xfc) != 0) अणु
		dev_dbg(&spi->dev, "RTC chip is not present\n");
		वापस -ENODEV;
	पूर्ण
	अगर (ds1305->ctrl[2] == 0)
		dev_dbg(&spi->dev, "chip may not be present\n");

	/* enable ग_लिखोs अगर needed ... अगर we were paranoid it would
	 * make sense to enable them only when असलolutely necessary.
	 */
	अगर (ds1305->ctrl[0] & DS1305_WP) अणु
		u8		buf[2];

		ds1305->ctrl[0] &= ~DS1305_WP;

		buf[0] = DS1305_WRITE | DS1305_CONTROL;
		buf[1] = ds1305->ctrl[0];
		status = spi_ग_लिखो_then_पढ़ो(spi, buf, माप(buf), शून्य, 0);

		dev_dbg(&spi->dev, "clear WP --> %d\n", status);
		अगर (status < 0)
			वापस status;
	पूर्ण

	/* on DS1305, maybe start oscillator; like most low घातer
	 * oscillators, it may take a second to stabilize
	 */
	अगर (ds1305->ctrl[0] & DS1305_nEOSC) अणु
		ds1305->ctrl[0] &= ~DS1305_nEOSC;
		ग_लिखो_ctrl = true;
		dev_warn(&spi->dev, "SET TIME!\n");
	पूर्ण

	/* ack any pending IRQs */
	अगर (ds1305->ctrl[1]) अणु
		ds1305->ctrl[1] = 0;
		ग_लिखो_ctrl = true;
	पूर्ण

	/* this may need one-समय (re)init */
	अगर (pdata) अणु
		/* maybe enable trickle अक्षरge */
		अगर (((ds1305->ctrl[2] & 0xf0) != DS1305_TRICKLE_MAGIC)) अणु
			ds1305->ctrl[2] = DS1305_TRICKLE_MAGIC
						| pdata->trickle;
			ग_लिखो_ctrl = true;
		पूर्ण

		/* on DS1306, configure 1 Hz संकेत */
		अगर (pdata->is_ds1306) अणु
			अगर (pdata->en_1hz) अणु
				अगर (!(ds1305->ctrl[0] & DS1306_1HZ)) अणु
					ds1305->ctrl[0] |= DS1306_1HZ;
					ग_लिखो_ctrl = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (ds1305->ctrl[0] & DS1306_1HZ) अणु
					ds1305->ctrl[0] &= ~DS1306_1HZ;
					ग_लिखो_ctrl = true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ग_लिखो_ctrl) अणु
		u8		buf[4];

		buf[0] = DS1305_WRITE | DS1305_CONTROL;
		buf[1] = ds1305->ctrl[0];
		buf[2] = ds1305->ctrl[1];
		buf[3] = ds1305->ctrl[2];
		status = spi_ग_लिखो_then_पढ़ो(spi, buf, माप(buf), शून्य, 0);
		अगर (status < 0) अणु
			dev_dbg(&spi->dev, "can't %s, %d\n",
					"write", status);
			वापस status;
		पूर्ण

		dev_dbg(&spi->dev, "ctrl %s: %3ph\n", "write", ds1305->ctrl);
	पूर्ण

	/* see अगर non-Linux software set up AM/PM mode */
	addr = DS1305_HOUR;
	status = spi_ग_लिखो_then_पढ़ो(spi, &addr, माप(addr),
				&value, माप(value));
	अगर (status < 0) अणु
		dev_dbg(&spi->dev, "read HOUR --> %d\n", status);
		वापस status;
	पूर्ण

	ds1305->hr12 = (DS1305_HR_12 & value) != 0;
	अगर (ds1305->hr12)
		dev_dbg(&spi->dev, "AM/PM\n");

	/* रेजिस्टर RTC ... from here on, ds1305->ctrl needs locking */
	ds1305->rtc = devm_rtc_allocate_device(&spi->dev);
	अगर (IS_ERR(ds1305->rtc))
		वापस PTR_ERR(ds1305->rtc);

	ds1305->rtc->ops = &ds1305_ops;
	ds1305->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	ds1305->rtc->range_max = RTC_TIMESTAMP_END_2099;

	ds1305_nvmem_cfg.priv = ds1305;
	status = devm_rtc_रेजिस्टर_device(ds1305->rtc);
	अगर (status)
		वापस status;

	devm_rtc_nvmem_रेजिस्टर(ds1305->rtc, &ds1305_nvmem_cfg);

	/* Maybe set up alarm IRQ; be पढ़ोy to handle it triggering right
	 * away.  NOTE that we करोn't share this.  The संकेत is active low,
	 * and we can't ack it beक्रमe a SPI message delay.  We temporarily
	 * disable the IRQ until it's acked, which lets us work with more
	 * IRQ trigger modes (not all IRQ controllers can करो falling edge).
	 */
	अगर (spi->irq) अणु
		INIT_WORK(&ds1305->work, ds1305_work);
		status = devm_request_irq(&spi->dev, spi->irq, ds1305_irq,
				0, dev_name(&ds1305->rtc->dev), ds1305);
		अगर (status < 0) अणु
			dev_err(&spi->dev, "request_irq %d --> %d\n",
					spi->irq, status);
		पूर्ण अन्यथा अणु
			device_set_wakeup_capable(&spi->dev, 1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds1305_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ds1305 *ds1305 = spi_get_drvdata(spi);

	/* carefully shut करोwn irq and workqueue, अगर present */
	अगर (spi->irq) अणु
		set_bit(FLAG_EXITING, &ds1305->flags);
		devm_मुक्त_irq(&spi->dev, spi->irq, ds1305);
		cancel_work_sync(&ds1305->work);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver ds1305_driver = अणु
	.driver.name	= "rtc-ds1305",
	.probe		= ds1305_probe,
	.हटाओ		= ds1305_हटाओ,
	/* REVISIT add suspend/resume */
पूर्ण;

module_spi_driver(ds1305_driver);

MODULE_DESCRIPTION("RTC driver for DS1305 and DS1306 chips");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:rtc-ds1305");
