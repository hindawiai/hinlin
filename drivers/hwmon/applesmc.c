<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/hwmon/applesmc.c - driver क्रम Apple's SMC (accelerometer, temperature
 * sensors, fan control, keyboard backlight control) used in Intel-based Apple
 * computers.
 *
 * Copyright (C) 2007 Nicolas Boichat <nicolas@boichat.ch>
 * Copyright (C) 2010 Henrik Rydberg <rydberg@euromail.se>
 *
 * Based on hdaps.c driver:
 * Copyright (C) 2005 Robert Love <rml@novell.com>
 * Copyright (C) 2005 Jesper Juhl <jj@chaosbits.net>
 *
 * Fan control based on smcFanControl:
 * Copyright (C) 2006 Hendrik Holपंचांगann <holपंचांगann@mac.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/dmi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/err.h>
#समावेश <linux/bits.h>

/* data port used by Apple SMC */
#घोषणा APPLESMC_DATA_PORT	0x300
/* command/status port used by Apple SMC */
#घोषणा APPLESMC_CMD_PORT	0x304

#घोषणा APPLESMC_NR_PORTS	32 /* 0x300-0x31f */

#घोषणा APPLESMC_MAX_DATA_LENGTH 32

/* Apple SMC status bits */
#घोषणा SMC_STATUS_AWAITING_DATA  BIT(0) /* SMC has data रुकोing to be पढ़ो */
#घोषणा SMC_STATUS_IB_CLOSED      BIT(1) /* Will ignore any input */
#घोषणा SMC_STATUS_BUSY           BIT(2) /* Command in progress */

/* Initial रुको is 8us */
#घोषणा APPLESMC_MIN_WAIT      0x0008

#घोषणा APPLESMC_READ_CMD	0x10
#घोषणा APPLESMC_WRITE_CMD	0x11
#घोषणा APPLESMC_GET_KEY_BY_INDEX_CMD	0x12
#घोषणा APPLESMC_GET_KEY_TYPE_CMD	0x13

#घोषणा KEY_COUNT_KEY		"#KEY" /* r-o ui32 */

#घोषणा LIGHT_SENSOR_LEFT_KEY	"ALV0" /* r-o अणुalv (6-10 bytes) */
#घोषणा LIGHT_SENSOR_RIGHT_KEY	"ALV1" /* r-o अणुalv (6-10 bytes) */
#घोषणा BACKLIGHT_KEY		"LKSB" /* w-o अणुlkb (2 bytes) */

#घोषणा CLAMSHELL_KEY		"MSLD" /* r-o ui8 (unused) */

#घोषणा MOTION_SENSOR_X_KEY	"MO_X" /* r-o sp78 (2 bytes) */
#घोषणा MOTION_SENSOR_Y_KEY	"MO_Y" /* r-o sp78 (2 bytes) */
#घोषणा MOTION_SENSOR_Z_KEY	"MO_Z" /* r-o sp78 (2 bytes) */
#घोषणा MOTION_SENSOR_KEY	"MOCN" /* r/w ui16 */

#घोषणा FANS_COUNT		"FNum" /* r-o ui8 */
#घोषणा FANS_MANUAL		"FS! " /* r-w ui16 */
#घोषणा FAN_ID_FMT		"F%dID" /* r-o अक्षर[16] */

#घोषणा TEMP_SENSOR_TYPE	"sp78"

/* List of keys used to पढ़ो/ग_लिखो fan speeds */
अटल स्थिर अक्षर *स्थिर fan_speed_fmt[] = अणु
	"F%dAc",		/* actual speed */
	"F%dMn",		/* minimum speed (rw) */
	"F%dMx",		/* maximum speed */
	"F%dSf",		/* safe speed - not all models */
	"F%dTg",		/* target speed (manual: rw) */
पूर्ण;

#घोषणा INIT_TIMEOUT_MSECS	5000	/* रुको up to 5s क्रम device init ... */
#घोषणा INIT_WAIT_MSECS		50	/* ... in 50ms increments */

#घोषणा APPLESMC_POLL_INTERVAL	50	/* msecs */
#घोषणा APPLESMC_INPUT_FUZZ	4	/* input event threshold */
#घोषणा APPLESMC_INPUT_FLAT	4

#घोषणा to_index(attr) (to_sensor_dev_attr(attr)->index & 0xffff)
#घोषणा to_option(attr) (to_sensor_dev_attr(attr)->index >> 16)

/* Dynamic device node attributes */
काष्ठा applesmc_dev_attr अणु
	काष्ठा sensor_device_attribute sda;	/* hwmon attributes */
	अक्षर name[32];				/* room क्रम node file name */
पूर्ण;

/* Dynamic device node group */
काष्ठा applesmc_node_group अणु
	अक्षर *क्रमmat;				/* क्रमmat string */
	व्योम *show;				/* show function */
	व्योम *store;				/* store function */
	पूर्णांक option;				/* function argument */
	काष्ठा applesmc_dev_attr *nodes;	/* dynamic node array */
पूर्ण;

/* AppleSMC entry - cached रेजिस्टर inक्रमmation */
काष्ठा applesmc_entry अणु
	अक्षर key[5];		/* four-letter key code */
	u8 valid;		/* set when entry is successfully पढ़ो once */
	u8 len;			/* bounded by APPLESMC_MAX_DATA_LENGTH */
	अक्षर type[5];		/* four-letter type code */
	u8 flags;		/* 0x10: func; 0x40: ग_लिखो; 0x80: पढ़ो */
पूर्ण;

/* Register lookup and रेजिस्टरs common to all SMCs */
अटल काष्ठा applesmc_रेजिस्टरs अणु
	काष्ठा mutex mutex;		/* रेजिस्टर पढ़ो/ग_लिखो mutex */
	अचिन्हित पूर्णांक key_count;		/* number of SMC रेजिस्टरs */
	अचिन्हित पूर्णांक fan_count;		/* number of fans */
	अचिन्हित पूर्णांक temp_count;	/* number of temperature रेजिस्टरs */
	अचिन्हित पूर्णांक temp_begin;	/* temperature lower index bound */
	अचिन्हित पूर्णांक temp_end;		/* temperature upper index bound */
	अचिन्हित पूर्णांक index_count;	/* size of temperature index array */
	पूर्णांक num_light_sensors;		/* number of light sensors */
	bool has_accelerometer;		/* has motion sensor */
	bool has_key_backlight;		/* has keyboard backlight */
	bool init_complete;		/* true when fully initialized */
	काष्ठा applesmc_entry *cache;	/* cached key entries */
	स्थिर अक्षर **index;		/* temperature key index */
पूर्ण smcreg = अणु
	.mutex = __MUTEX_INITIALIZER(smcreg.mutex),
पूर्ण;

अटल स्थिर पूर्णांक debug;
अटल काष्ठा platक्रमm_device *pdev;
अटल s16 rest_x;
अटल s16 rest_y;
अटल u8 backlight_state[2];

अटल काष्ठा device *hwmon_dev;
अटल काष्ठा input_dev *applesmc_idev;

/*
 * Last index written to key_at_index sysfs file, and value to use क्रम all other
 * key_at_index_* sysfs files.
 */
अटल अचिन्हित पूर्णांक key_at_index;

अटल काष्ठा workqueue_काष्ठा *applesmc_led_wq;

/*
 * Wait क्रम specअगरic status bits with a mask on the SMC.
 * Used beक्रमe all transactions.
 * This करोes 10 fast loops of 8us then exponentially backs off क्रम a
 * minimum total रुको of 262ms. Depending on usleep_range this could
 * run out past 500ms.
 */

अटल पूर्णांक रुको_status(u8 val, u8 mask)
अणु
	u8 status;
	पूर्णांक us;
	पूर्णांक i;

	us = APPLESMC_MIN_WAIT;
	क्रम (i = 0; i < 24 ; i++) अणु
		status = inb(APPLESMC_CMD_PORT);
		अगर ((status & mask) == val)
			वापस 0;
		usleep_range(us, us * 2);
		अगर (i > 9)
			us <<= 1;
	पूर्ण
	वापस -EIO;
पूर्ण

/* send_byte - Write to SMC data port. Callers must hold applesmc_lock. */

अटल पूर्णांक send_byte(u8 cmd, u16 port)
अणु
	पूर्णांक status;

	status = रुको_status(0, SMC_STATUS_IB_CLOSED);
	अगर (status)
		वापस status;
	/*
	 * This needs to be a separate पढ़ो looking क्रम bit 0x04
	 * after bit 0x02 falls. If consolidated with the रुको above
	 * this extra पढ़ो may not happen अगर status वापसs both
	 * simultaneously and this would appear to be required.
	 */
	status = रुको_status(SMC_STATUS_BUSY, SMC_STATUS_BUSY);
	अगर (status)
		वापस status;

	outb(cmd, port);
	वापस 0;
पूर्ण

/* send_command - Write a command to the SMC. Callers must hold applesmc_lock. */

अटल पूर्णांक send_command(u8 cmd)
अणु
	पूर्णांक ret;

	ret = रुको_status(0, SMC_STATUS_IB_CLOSED);
	अगर (ret)
		वापस ret;
	outb(cmd, APPLESMC_CMD_PORT);
	वापस 0;
पूर्ण

/*
 * Based on logic from the Apple driver. This is issued beक्रमe any पूर्णांकeraction
 * If busy is stuck high, issue a पढ़ो command to reset the SMC state machine.
 * If busy is stuck high after the command then the SMC is jammed.
 */

अटल पूर्णांक smc_sane(व्योम)
अणु
	पूर्णांक ret;

	ret = रुको_status(0, SMC_STATUS_BUSY);
	अगर (!ret)
		वापस ret;
	ret = send_command(APPLESMC_READ_CMD);
	अगर (ret)
		वापस ret;
	वापस रुको_status(0, SMC_STATUS_BUSY);
पूर्ण

अटल पूर्णांक send_argument(स्थिर अक्षर *key)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		अगर (send_byte(key[i], APPLESMC_DATA_PORT))
			वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_smc(u8 cmd, स्थिर अक्षर *key, u8 *buffer, u8 len)
अणु
	u8 status, data = 0;
	पूर्णांक i;
	पूर्णांक ret;

	ret = smc_sane();
	अगर (ret)
		वापस ret;

	अगर (send_command(cmd) || send_argument(key)) अणु
		pr_warn("%.4s: read arg fail\n", key);
		वापस -EIO;
	पूर्ण

	/* This has no effect on newer (2012) SMCs */
	अगर (send_byte(len, APPLESMC_DATA_PORT)) अणु
		pr_warn("%.4s: read len fail\n", key);
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		अगर (रुको_status(SMC_STATUS_AWAITING_DATA | SMC_STATUS_BUSY,
				SMC_STATUS_AWAITING_DATA | SMC_STATUS_BUSY)) अणु
			pr_warn("%.4s: read data[%d] fail\n", key, i);
			वापस -EIO;
		पूर्ण
		buffer[i] = inb(APPLESMC_DATA_PORT);
	पूर्ण

	/* Read the data port until bit0 is cleared */
	क्रम (i = 0; i < 16; i++) अणु
		udelay(APPLESMC_MIN_WAIT);
		status = inb(APPLESMC_CMD_PORT);
		अगर (!(status & SMC_STATUS_AWAITING_DATA))
			अवरोध;
		data = inb(APPLESMC_DATA_PORT);
	पूर्ण
	अगर (i)
		pr_warn("flushed %d bytes, last value is: %d\n", i, data);

	वापस रुको_status(0, SMC_STATUS_BUSY);
पूर्ण

अटल पूर्णांक ग_लिखो_smc(u8 cmd, स्थिर अक्षर *key, स्थिर u8 *buffer, u8 len)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	ret = smc_sane();
	अगर (ret)
		वापस ret;

	अगर (send_command(cmd) || send_argument(key)) अणु
		pr_warn("%s: write arg fail\n", key);
		वापस -EIO;
	पूर्ण

	अगर (send_byte(len, APPLESMC_DATA_PORT)) अणु
		pr_warn("%.4s: write len fail\n", key);
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		अगर (send_byte(buffer[i], APPLESMC_DATA_PORT)) अणु
			pr_warn("%s: write data fail\n", key);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस रुको_status(0, SMC_STATUS_BUSY);
पूर्ण

अटल पूर्णांक पढ़ो_रेजिस्टर_count(अचिन्हित पूर्णांक *count)
अणु
	__be32 be;
	पूर्णांक ret;

	ret = पढ़ो_smc(APPLESMC_READ_CMD, KEY_COUNT_KEY, (u8 *)&be, 4);
	अगर (ret)
		वापस ret;

	*count = be32_to_cpu(be);
	वापस 0;
पूर्ण

/*
 * Serialized I/O
 *
 * Returns zero on success or a negative error on failure.
 * All functions below are concurrency safe - callers should NOT hold lock.
 */

अटल पूर्णांक applesmc_पढ़ो_entry(स्थिर काष्ठा applesmc_entry *entry,
			       u8 *buf, u8 len)
अणु
	पूर्णांक ret;

	अगर (entry->len != len)
		वापस -EINVAL;
	mutex_lock(&smcreg.mutex);
	ret = पढ़ो_smc(APPLESMC_READ_CMD, entry->key, buf, len);
	mutex_unlock(&smcreg.mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक applesmc_ग_लिखो_entry(स्थिर काष्ठा applesmc_entry *entry,
				स्थिर u8 *buf, u8 len)
अणु
	पूर्णांक ret;

	अगर (entry->len != len)
		वापस -EINVAL;
	mutex_lock(&smcreg.mutex);
	ret = ग_लिखो_smc(APPLESMC_WRITE_CMD, entry->key, buf, len);
	mutex_unlock(&smcreg.mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा applesmc_entry *applesmc_get_entry_by_index(पूर्णांक index)
अणु
	काष्ठा applesmc_entry *cache = &smcreg.cache[index];
	u8 key[4], info[6];
	__be32 be;
	पूर्णांक ret = 0;

	अगर (cache->valid)
		वापस cache;

	mutex_lock(&smcreg.mutex);

	अगर (cache->valid)
		जाओ out;
	be = cpu_to_be32(index);
	ret = पढ़ो_smc(APPLESMC_GET_KEY_BY_INDEX_CMD, (u8 *)&be, key, 4);
	अगर (ret)
		जाओ out;
	ret = पढ़ो_smc(APPLESMC_GET_KEY_TYPE_CMD, key, info, 6);
	अगर (ret)
		जाओ out;

	स_नकल(cache->key, key, 4);
	cache->len = info[0];
	स_नकल(cache->type, &info[1], 4);
	cache->flags = info[5];
	cache->valid = 1;

out:
	mutex_unlock(&smcreg.mutex);
	अगर (ret)
		वापस ERR_PTR(ret);
	वापस cache;
पूर्ण

अटल पूर्णांक applesmc_get_lower_bound(अचिन्हित पूर्णांक *lo, स्थिर अक्षर *key)
अणु
	पूर्णांक begin = 0, end = smcreg.key_count;
	स्थिर काष्ठा applesmc_entry *entry;

	जबतक (begin != end) अणु
		पूर्णांक middle = begin + (end - begin) / 2;
		entry = applesmc_get_entry_by_index(middle);
		अगर (IS_ERR(entry)) अणु
			*lo = 0;
			वापस PTR_ERR(entry);
		पूर्ण
		अगर (म_भेद(entry->key, key) < 0)
			begin = middle + 1;
		अन्यथा
			end = middle;
	पूर्ण

	*lo = begin;
	वापस 0;
पूर्ण

अटल पूर्णांक applesmc_get_upper_bound(अचिन्हित पूर्णांक *hi, स्थिर अक्षर *key)
अणु
	पूर्णांक begin = 0, end = smcreg.key_count;
	स्थिर काष्ठा applesmc_entry *entry;

	जबतक (begin != end) अणु
		पूर्णांक middle = begin + (end - begin) / 2;
		entry = applesmc_get_entry_by_index(middle);
		अगर (IS_ERR(entry)) अणु
			*hi = smcreg.key_count;
			वापस PTR_ERR(entry);
		पूर्ण
		अगर (म_भेद(key, entry->key) < 0)
			end = middle;
		अन्यथा
			begin = middle + 1;
	पूर्ण

	*hi = begin;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा applesmc_entry *applesmc_get_entry_by_key(स्थिर अक्षर *key)
अणु
	पूर्णांक begin, end;
	पूर्णांक ret;

	ret = applesmc_get_lower_bound(&begin, key);
	अगर (ret)
		वापस ERR_PTR(ret);
	ret = applesmc_get_upper_bound(&end, key);
	अगर (ret)
		वापस ERR_PTR(ret);
	अगर (end - begin != 1)
		वापस ERR_PTR(-EINVAL);

	वापस applesmc_get_entry_by_index(begin);
पूर्ण

अटल पूर्णांक applesmc_पढ़ो_key(स्थिर अक्षर *key, u8 *buffer, u8 len)
अणु
	स्थिर काष्ठा applesmc_entry *entry;

	entry = applesmc_get_entry_by_key(key);
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);

	वापस applesmc_पढ़ो_entry(entry, buffer, len);
पूर्ण

अटल पूर्णांक applesmc_ग_लिखो_key(स्थिर अक्षर *key, स्थिर u8 *buffer, u8 len)
अणु
	स्थिर काष्ठा applesmc_entry *entry;

	entry = applesmc_get_entry_by_key(key);
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);

	वापस applesmc_ग_लिखो_entry(entry, buffer, len);
पूर्ण

अटल पूर्णांक applesmc_has_key(स्थिर अक्षर *key, bool *value)
अणु
	स्थिर काष्ठा applesmc_entry *entry;

	entry = applesmc_get_entry_by_key(key);
	अगर (IS_ERR(entry) && PTR_ERR(entry) != -EINVAL)
		वापस PTR_ERR(entry);

	*value = !IS_ERR(entry);
	वापस 0;
पूर्ण

/*
 * applesmc_पढ़ो_s16 - Read 16-bit चिन्हित big endian रेजिस्टर
 */
अटल पूर्णांक applesmc_पढ़ो_s16(स्थिर अक्षर *key, s16 *value)
अणु
	u8 buffer[2];
	पूर्णांक ret;

	ret = applesmc_पढ़ो_key(key, buffer, 2);
	अगर (ret)
		वापस ret;

	*value = ((s16)buffer[0] << 8) | buffer[1];
	वापस 0;
पूर्ण

/*
 * applesmc_device_init - initialize the accelerometer.  Can sleep.
 */
अटल व्योम applesmc_device_init(व्योम)
अणु
	पूर्णांक total;
	u8 buffer[2];

	अगर (!smcreg.has_accelerometer)
		वापस;

	क्रम (total = INIT_TIMEOUT_MSECS; total > 0; total -= INIT_WAIT_MSECS) अणु
		अगर (!applesmc_पढ़ो_key(MOTION_SENSOR_KEY, buffer, 2) &&
				(buffer[0] != 0x00 || buffer[1] != 0x00))
			वापस;
		buffer[0] = 0xe0;
		buffer[1] = 0x00;
		applesmc_ग_लिखो_key(MOTION_SENSOR_KEY, buffer, 2);
		msleep(INIT_WAIT_MSECS);
	पूर्ण

	pr_warn("failed to init the device\n");
पूर्ण

अटल पूर्णांक applesmc_init_index(काष्ठा applesmc_रेजिस्टरs *s)
अणु
	स्थिर काष्ठा applesmc_entry *entry;
	अचिन्हित पूर्णांक i;

	अगर (s->index)
		वापस 0;

	s->index = kसुस्मृति(s->temp_count, माप(s->index[0]), GFP_KERNEL);
	अगर (!s->index)
		वापस -ENOMEM;

	क्रम (i = s->temp_begin; i < s->temp_end; i++) अणु
		entry = applesmc_get_entry_by_index(i);
		अगर (IS_ERR(entry))
			जारी;
		अगर (म_भेद(entry->type, TEMP_SENSOR_TYPE))
			जारी;
		s->index[s->index_count++] = entry->key;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * applesmc_init_smcreg_try - Try to initialize रेजिस्टर cache. Idempotent.
 */
अटल पूर्णांक applesmc_init_smcreg_try(व्योम)
अणु
	काष्ठा applesmc_रेजिस्टरs *s = &smcreg;
	bool left_light_sensor = false, right_light_sensor = false;
	अचिन्हित पूर्णांक count;
	u8 पंचांगp[1];
	पूर्णांक ret;

	अगर (s->init_complete)
		वापस 0;

	ret = पढ़ो_रेजिस्टर_count(&count);
	अगर (ret)
		वापस ret;

	अगर (s->cache && s->key_count != count) अणु
		pr_warn("key count changed from %d to %d\n",
			s->key_count, count);
		kमुक्त(s->cache);
		s->cache = शून्य;
	पूर्ण
	s->key_count = count;

	अगर (!s->cache)
		s->cache = kसुस्मृति(s->key_count, माप(*s->cache), GFP_KERNEL);
	अगर (!s->cache)
		वापस -ENOMEM;

	ret = applesmc_पढ़ो_key(FANS_COUNT, पंचांगp, 1);
	अगर (ret)
		वापस ret;
	s->fan_count = पंचांगp[0];
	अगर (s->fan_count > 10)
		s->fan_count = 10;

	ret = applesmc_get_lower_bound(&s->temp_begin, "T");
	अगर (ret)
		वापस ret;
	ret = applesmc_get_lower_bound(&s->temp_end, "U");
	अगर (ret)
		वापस ret;
	s->temp_count = s->temp_end - s->temp_begin;

	ret = applesmc_init_index(s);
	अगर (ret)
		वापस ret;

	ret = applesmc_has_key(LIGHT_SENSOR_LEFT_KEY, &left_light_sensor);
	अगर (ret)
		वापस ret;
	ret = applesmc_has_key(LIGHT_SENSOR_RIGHT_KEY, &right_light_sensor);
	अगर (ret)
		वापस ret;
	ret = applesmc_has_key(MOTION_SENSOR_KEY, &s->has_accelerometer);
	अगर (ret)
		वापस ret;
	ret = applesmc_has_key(BACKLIGHT_KEY, &s->has_key_backlight);
	अगर (ret)
		वापस ret;

	s->num_light_sensors = left_light_sensor + right_light_sensor;
	s->init_complete = true;

	pr_info("key=%d fan=%d temp=%d index=%d acc=%d lux=%d kbd=%d\n",
	       s->key_count, s->fan_count, s->temp_count, s->index_count,
	       s->has_accelerometer,
	       s->num_light_sensors,
	       s->has_key_backlight);

	वापस 0;
पूर्ण

अटल व्योम applesmc_destroy_smcreg(व्योम)
अणु
	kमुक्त(smcreg.index);
	smcreg.index = शून्य;
	kमुक्त(smcreg.cache);
	smcreg.cache = शून्य;
	smcreg.init_complete = false;
पूर्ण

/*
 * applesmc_init_smcreg - Initialize रेजिस्टर cache.
 *
 * Retries until initialization is successful, or the operation बार out.
 *
 */
अटल पूर्णांक applesmc_init_smcreg(व्योम)
अणु
	पूर्णांक ms, ret;

	क्रम (ms = 0; ms < INIT_TIMEOUT_MSECS; ms += INIT_WAIT_MSECS) अणु
		ret = applesmc_init_smcreg_try();
		अगर (!ret) अणु
			अगर (ms)
				pr_info("init_smcreg() took %d ms\n", ms);
			वापस 0;
		पूर्ण
		msleep(INIT_WAIT_MSECS);
	पूर्ण

	applesmc_destroy_smcreg();

	वापस ret;
पूर्ण

/* Device model stuff */
अटल पूर्णांक applesmc_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	ret = applesmc_init_smcreg();
	अगर (ret)
		वापस ret;

	applesmc_device_init();

	वापस 0;
पूर्ण

/* Synchronize device with memorized backlight state */
अटल पूर्णांक applesmc_pm_resume(काष्ठा device *dev)
अणु
	अगर (smcreg.has_key_backlight)
		applesmc_ग_लिखो_key(BACKLIGHT_KEY, backlight_state, 2);
	वापस 0;
पूर्ण

/* Reinitialize device on resume from hibernation */
अटल पूर्णांक applesmc_pm_restore(काष्ठा device *dev)
अणु
	applesmc_device_init();
	वापस applesmc_pm_resume(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops applesmc_pm_ops = अणु
	.resume = applesmc_pm_resume,
	.restore = applesmc_pm_restore,
पूर्ण;

अटल काष्ठा platक्रमm_driver applesmc_driver = अणु
	.probe = applesmc_probe,
	.driver	= अणु
		.name = "applesmc",
		.pm = &applesmc_pm_ops,
	पूर्ण,
पूर्ण;

/*
 * applesmc_calibrate - Set our "resting" values.  Callers must
 * hold applesmc_lock.
 */
अटल व्योम applesmc_calibrate(व्योम)
अणु
	applesmc_पढ़ो_s16(MOTION_SENSOR_X_KEY, &rest_x);
	applesmc_पढ़ो_s16(MOTION_SENSOR_Y_KEY, &rest_y);
	rest_x = -rest_x;
पूर्ण

अटल व्योम applesmc_idev_poll(काष्ठा input_dev *idev)
अणु
	s16 x, y;

	अगर (applesmc_पढ़ो_s16(MOTION_SENSOR_X_KEY, &x))
		वापस;
	अगर (applesmc_पढ़ो_s16(MOTION_SENSOR_Y_KEY, &y))
		वापस;

	x = -x;
	input_report_असल(idev, ABS_X, x - rest_x);
	input_report_असल(idev, ABS_Y, y - rest_y);
	input_sync(idev);
पूर्ण

/* Sysfs Files */

अटल sमाप_प्रकार applesmc_name_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "applesmc\n");
पूर्ण

अटल sमाप_प्रकार applesmc_position_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	s16 x, y, z;

	ret = applesmc_पढ़ो_s16(MOTION_SENSOR_X_KEY, &x);
	अगर (ret)
		जाओ out;
	ret = applesmc_पढ़ो_s16(MOTION_SENSOR_Y_KEY, &y);
	अगर (ret)
		जाओ out;
	ret = applesmc_पढ़ो_s16(MOTION_SENSOR_Z_KEY, &z);
	अगर (ret)
		जाओ out;

out:
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(buf, "(%d,%d,%d)\n", x, y, z);
पूर्ण

अटल sमाप_प्रकार applesmc_light_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	स्थिर काष्ठा applesmc_entry *entry;
	अटल पूर्णांक data_length;
	पूर्णांक ret;
	u8 left = 0, right = 0;
	u8 buffer[10];

	अगर (!data_length) अणु
		entry = applesmc_get_entry_by_key(LIGHT_SENSOR_LEFT_KEY);
		अगर (IS_ERR(entry))
			वापस PTR_ERR(entry);
		अगर (entry->len > 10)
			वापस -ENXIO;
		data_length = entry->len;
		pr_info("light sensor data length set to %d\n", data_length);
	पूर्ण

	ret = applesmc_पढ़ो_key(LIGHT_SENSOR_LEFT_KEY, buffer, data_length);
	अगर (ret)
		जाओ out;
	/* newer macbooks report a single 10-bit bigendian value */
	अगर (data_length == 10) अणु
		left = be16_to_cpu(*(__be16 *)(buffer + 6)) >> 2;
		जाओ out;
	पूर्ण
	left = buffer[2];

	ret = applesmc_पढ़ो_key(LIGHT_SENSOR_RIGHT_KEY, buffer, data_length);
	अगर (ret)
		जाओ out;
	right = buffer[2];

out:
	अगर (ret)
		वापस ret;

	वापस sysfs_emit(sysfsbuf, "(%d,%d)\n", left, right);
पूर्ण

/* Displays sensor key as label */
अटल sमाप_प्रकार applesmc_show_sensor_label(काष्ठा device *dev,
			काष्ठा device_attribute *devattr, अक्षर *sysfsbuf)
अणु
	स्थिर अक्षर *key = smcreg.index[to_index(devattr)];

	वापस sysfs_emit(sysfsbuf, "%s\n", key);
पूर्ण

/* Displays degree Celsius * 1000 */
अटल sमाप_प्रकार applesmc_show_temperature(काष्ठा device *dev,
			काष्ठा device_attribute *devattr, अक्षर *sysfsbuf)
अणु
	स्थिर अक्षर *key = smcreg.index[to_index(devattr)];
	पूर्णांक ret;
	s16 value;
	पूर्णांक temp;

	ret = applesmc_पढ़ो_s16(key, &value);
	अगर (ret)
		वापस ret;

	temp = 250 * (value >> 6);

	वापस sysfs_emit(sysfsbuf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार applesmc_show_fan_speed(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक speed = 0;
	अक्षर newkey[5];
	u8 buffer[2];

	scnम_लिखो(newkey, माप(newkey), fan_speed_fmt[to_option(attr)],
		  to_index(attr));

	ret = applesmc_पढ़ो_key(newkey, buffer, 2);
	अगर (ret)
		वापस ret;

	speed = ((buffer[0] << 8 | buffer[1]) >> 2);
	वापस sysfs_emit(sysfsbuf, "%u\n", speed);
पूर्ण

अटल sमाप_प्रकार applesmc_store_fan_speed(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *sysfsbuf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ speed;
	अक्षर newkey[5];
	u8 buffer[2];

	अगर (kम_से_अदीर्घ(sysfsbuf, 10, &speed) < 0 || speed >= 0x4000)
		वापस -EINVAL;		/* Bigger than a 14-bit value */

	scnम_लिखो(newkey, माप(newkey), fan_speed_fmt[to_option(attr)],
		  to_index(attr));

	buffer[0] = (speed >> 6) & 0xff;
	buffer[1] = (speed << 2) & 0xff;
	ret = applesmc_ग_लिखो_key(newkey, buffer, 2);

	अगर (ret)
		वापस ret;
	अन्यथा
		वापस count;
पूर्ण

अटल sमाप_प्रकार applesmc_show_fan_manual(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	पूर्णांक ret;
	u16 manual = 0;
	u8 buffer[2];

	ret = applesmc_पढ़ो_key(FANS_MANUAL, buffer, 2);
	अगर (ret)
		वापस ret;

	manual = ((buffer[0] << 8 | buffer[1]) >> to_index(attr)) & 0x01;
	वापस sysfs_emit(sysfsbuf, "%d\n", manual);
पूर्ण

अटल sमाप_प्रकार applesmc_store_fan_manual(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *sysfsbuf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	u8 buffer[2];
	अचिन्हित दीर्घ input;
	u16 val;

	अगर (kम_से_अदीर्घ(sysfsbuf, 10, &input) < 0)
		वापस -EINVAL;

	ret = applesmc_पढ़ो_key(FANS_MANUAL, buffer, 2);
	अगर (ret)
		जाओ out;

	val = (buffer[0] << 8 | buffer[1]);

	अगर (input)
		val = val | (0x01 << to_index(attr));
	अन्यथा
		val = val & ~(0x01 << to_index(attr));

	buffer[0] = (val >> 8) & 0xFF;
	buffer[1] = val & 0xFF;

	ret = applesmc_ग_लिखो_key(FANS_MANUAL, buffer, 2);

out:
	अगर (ret)
		वापस ret;
	अन्यथा
		वापस count;
पूर्ण

अटल sमाप_प्रकार applesmc_show_fan_position(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	पूर्णांक ret;
	अक्षर newkey[5];
	u8 buffer[17];

	scnम_लिखो(newkey, माप(newkey), FAN_ID_FMT, to_index(attr));

	ret = applesmc_पढ़ो_key(newkey, buffer, 16);
	buffer[16] = 0;

	अगर (ret)
		वापस ret;

	वापस sysfs_emit(sysfsbuf, "%s\n", buffer + 4);
पूर्ण

अटल sमाप_प्रकार applesmc_calibrate_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	वापस sysfs_emit(sysfsbuf, "(%d,%d)\n", rest_x, rest_y);
पूर्ण

अटल sमाप_प्रकार applesmc_calibrate_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *sysfsbuf, माप_प्रकार count)
अणु
	applesmc_calibrate();

	वापस count;
पूर्ण

अटल व्योम applesmc_backlight_set(काष्ठा work_काष्ठा *work)
अणु
	applesmc_ग_लिखो_key(BACKLIGHT_KEY, backlight_state, 2);
पूर्ण
अटल DECLARE_WORK(backlight_work, &applesmc_backlight_set);

अटल व्योम applesmc_brightness_set(काष्ठा led_classdev *led_cdev,
						क्रमागत led_brightness value)
अणु
	पूर्णांक ret;

	backlight_state[0] = value;
	ret = queue_work(applesmc_led_wq, &backlight_work);

	अगर (debug && (!ret))
		dev_dbg(led_cdev->dev, "work was already on the queue.\n");
पूर्ण

अटल sमाप_प्रकार applesmc_key_count_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	पूर्णांक ret;
	u8 buffer[4];
	u32 count;

	ret = applesmc_पढ़ो_key(KEY_COUNT_KEY, buffer, 4);
	अगर (ret)
		वापस ret;

	count = ((u32)buffer[0]<<24) + ((u32)buffer[1]<<16) +
						((u32)buffer[2]<<8) + buffer[3];
	वापस sysfs_emit(sysfsbuf, "%d\n", count);
पूर्ण

अटल sमाप_प्रकार applesmc_key_at_index_पढ़ो_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	स्थिर काष्ठा applesmc_entry *entry;
	पूर्णांक ret;

	entry = applesmc_get_entry_by_index(key_at_index);
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);
	ret = applesmc_पढ़ो_entry(entry, sysfsbuf, entry->len);
	अगर (ret)
		वापस ret;

	वापस entry->len;
पूर्ण

अटल sमाप_प्रकार applesmc_key_at_index_data_length_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	स्थिर काष्ठा applesmc_entry *entry;

	entry = applesmc_get_entry_by_index(key_at_index);
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);

	वापस sysfs_emit(sysfsbuf, "%d\n", entry->len);
पूर्ण

अटल sमाप_प्रकार applesmc_key_at_index_type_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	स्थिर काष्ठा applesmc_entry *entry;

	entry = applesmc_get_entry_by_index(key_at_index);
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);

	वापस sysfs_emit(sysfsbuf, "%s\n", entry->type);
पूर्ण

अटल sमाप_प्रकार applesmc_key_at_index_name_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	स्थिर काष्ठा applesmc_entry *entry;

	entry = applesmc_get_entry_by_index(key_at_index);
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);

	वापस sysfs_emit(sysfsbuf, "%s\n", entry->key);
पूर्ण

अटल sमाप_प्रकार applesmc_key_at_index_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *sysfsbuf)
अणु
	वापस sysfs_emit(sysfsbuf, "%d\n", key_at_index);
पूर्ण

अटल sमाप_प्रकार applesmc_key_at_index_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *sysfsbuf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ newkey;

	अगर (kम_से_अदीर्घ(sysfsbuf, 10, &newkey) < 0
	    || newkey >= smcreg.key_count)
		वापस -EINVAL;

	key_at_index = newkey;
	वापस count;
पूर्ण

अटल काष्ठा led_classdev applesmc_backlight = अणु
	.name			= "smc::kbd_backlight",
	.शेष_trigger	= "nand-disk",
	.brightness_set		= applesmc_brightness_set,
पूर्ण;

अटल काष्ठा applesmc_node_group info_group[] = अणु
	अणु "name", applesmc_name_show पूर्ण,
	अणु "key_count", applesmc_key_count_show पूर्ण,
	अणु "key_at_index", applesmc_key_at_index_show, applesmc_key_at_index_store पूर्ण,
	अणु "key_at_index_name", applesmc_key_at_index_name_show पूर्ण,
	अणु "key_at_index_type", applesmc_key_at_index_type_show पूर्ण,
	अणु "key_at_index_data_length", applesmc_key_at_index_data_length_show पूर्ण,
	अणु "key_at_index_data", applesmc_key_at_index_पढ़ो_show पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा applesmc_node_group accelerometer_group[] = अणु
	अणु "position", applesmc_position_show पूर्ण,
	अणु "calibrate", applesmc_calibrate_show, applesmc_calibrate_store पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा applesmc_node_group light_sensor_group[] = अणु
	अणु "light", applesmc_light_show पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा applesmc_node_group fan_group[] = अणु
	अणु "fan%d_label", applesmc_show_fan_position पूर्ण,
	अणु "fan%d_input", applesmc_show_fan_speed, शून्य, 0 पूर्ण,
	अणु "fan%d_min", applesmc_show_fan_speed, applesmc_store_fan_speed, 1 पूर्ण,
	अणु "fan%d_max", applesmc_show_fan_speed, शून्य, 2 पूर्ण,
	अणु "fan%d_safe", applesmc_show_fan_speed, शून्य, 3 पूर्ण,
	अणु "fan%d_output", applesmc_show_fan_speed, applesmc_store_fan_speed, 4 पूर्ण,
	अणु "fan%d_manual", applesmc_show_fan_manual, applesmc_store_fan_manual पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा applesmc_node_group temp_group[] = अणु
	अणु "temp%d_label", applesmc_show_sensor_label पूर्ण,
	अणु "temp%d_input", applesmc_show_temperature पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Module stuff */

/*
 * applesmc_destroy_nodes - हटाओ files and मुक्त associated memory
 */
अटल व्योम applesmc_destroy_nodes(काष्ठा applesmc_node_group *groups)
अणु
	काष्ठा applesmc_node_group *grp;
	काष्ठा applesmc_dev_attr *node;

	क्रम (grp = groups; grp->nodes; grp++) अणु
		क्रम (node = grp->nodes; node->sda.dev_attr.attr.name; node++)
			sysfs_हटाओ_file(&pdev->dev.kobj,
					  &node->sda.dev_attr.attr);
		kमुक्त(grp->nodes);
		grp->nodes = शून्य;
	पूर्ण
पूर्ण

/*
 * applesmc_create_nodes - create a two-dimensional group of sysfs files
 */
अटल पूर्णांक applesmc_create_nodes(काष्ठा applesmc_node_group *groups, पूर्णांक num)
अणु
	काष्ठा applesmc_node_group *grp;
	काष्ठा applesmc_dev_attr *node;
	काष्ठा attribute *attr;
	पूर्णांक ret, i;

	क्रम (grp = groups; grp->क्रमmat; grp++) अणु
		grp->nodes = kसुस्मृति(num + 1, माप(*node), GFP_KERNEL);
		अगर (!grp->nodes) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		क्रम (i = 0; i < num; i++) अणु
			node = &grp->nodes[i];
			scnम_लिखो(node->name, माप(node->name), grp->क्रमmat,
				  i + 1);
			node->sda.index = (grp->option << 16) | (i & 0xffff);
			node->sda.dev_attr.show = grp->show;
			node->sda.dev_attr.store = grp->store;
			attr = &node->sda.dev_attr.attr;
			sysfs_attr_init(attr);
			attr->name = node->name;
			attr->mode = 0444 | (grp->store ? 0200 : 0);
			ret = sysfs_create_file(&pdev->dev.kobj, attr);
			अगर (ret) अणु
				attr->name = शून्य;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
out:
	applesmc_destroy_nodes(groups);
	वापस ret;
पूर्ण

/* Create accelerometer resources */
अटल पूर्णांक applesmc_create_accelerometer(व्योम)
अणु
	पूर्णांक ret;

	अगर (!smcreg.has_accelerometer)
		वापस 0;

	ret = applesmc_create_nodes(accelerometer_group, 1);
	अगर (ret)
		जाओ out;

	applesmc_idev = input_allocate_device();
	अगर (!applesmc_idev) अणु
		ret = -ENOMEM;
		जाओ out_sysfs;
	पूर्ण

	/* initial calibrate क्रम the input device */
	applesmc_calibrate();

	/* initialize the input device */
	applesmc_idev->name = "applesmc";
	applesmc_idev->id.bustype = BUS_HOST;
	applesmc_idev->dev.parent = &pdev->dev;
	input_set_असल_params(applesmc_idev, ABS_X,
			-256, 256, APPLESMC_INPUT_FUZZ, APPLESMC_INPUT_FLAT);
	input_set_असल_params(applesmc_idev, ABS_Y,
			-256, 256, APPLESMC_INPUT_FUZZ, APPLESMC_INPUT_FLAT);

	ret = input_setup_polling(applesmc_idev, applesmc_idev_poll);
	अगर (ret)
		जाओ out_idev;

	input_set_poll_पूर्णांकerval(applesmc_idev, APPLESMC_POLL_INTERVAL);

	ret = input_रेजिस्टर_device(applesmc_idev);
	अगर (ret)
		जाओ out_idev;

	वापस 0;

out_idev:
	input_मुक्त_device(applesmc_idev);

out_sysfs:
	applesmc_destroy_nodes(accelerometer_group);

out:
	pr_warn("driver init failed (ret=%d)!\n", ret);
	वापस ret;
पूर्ण

/* Release all resources used by the accelerometer */
अटल व्योम applesmc_release_accelerometer(व्योम)
अणु
	अगर (!smcreg.has_accelerometer)
		वापस;
	input_unरेजिस्टर_device(applesmc_idev);
	applesmc_destroy_nodes(accelerometer_group);
पूर्ण

अटल पूर्णांक applesmc_create_light_sensor(व्योम)
अणु
	अगर (!smcreg.num_light_sensors)
		वापस 0;
	वापस applesmc_create_nodes(light_sensor_group, 1);
पूर्ण

अटल व्योम applesmc_release_light_sensor(व्योम)
अणु
	अगर (!smcreg.num_light_sensors)
		वापस;
	applesmc_destroy_nodes(light_sensor_group);
पूर्ण

अटल पूर्णांक applesmc_create_key_backlight(व्योम)
अणु
	अगर (!smcreg.has_key_backlight)
		वापस 0;
	applesmc_led_wq = create_singlethपढ़ो_workqueue("applesmc-led");
	अगर (!applesmc_led_wq)
		वापस -ENOMEM;
	वापस led_classdev_रेजिस्टर(&pdev->dev, &applesmc_backlight);
पूर्ण

अटल व्योम applesmc_release_key_backlight(व्योम)
अणु
	अगर (!smcreg.has_key_backlight)
		वापस;
	led_classdev_unरेजिस्टर(&applesmc_backlight);
	destroy_workqueue(applesmc_led_wq);
पूर्ण

अटल पूर्णांक applesmc_dmi_match(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	वापस 1;
पूर्ण

/*
 * Note that DMI_MATCH(...,"MacBook") will match "MacBookPro1,1".
 * So we need to put "Apple MacBook Pro" beक्रमe "Apple MacBook".
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id applesmc_whitelist[] __initस्थिर = अणु
	अणु applesmc_dmi_match, "Apple MacBook Air", अणु
	  DMI_MATCH(DMI_BOARD_VENDOR, "Apple"),
	  DMI_MATCH(DMI_PRODUCT_NAME, "MacBookAir") पूर्ण,
	पूर्ण,
	अणु applesmc_dmi_match, "Apple MacBook Pro", अणु
	  DMI_MATCH(DMI_BOARD_VENDOR, "Apple"),
	  DMI_MATCH(DMI_PRODUCT_NAME, "MacBookPro") पूर्ण,
	पूर्ण,
	अणु applesmc_dmi_match, "Apple MacBook", अणु
	  DMI_MATCH(DMI_BOARD_VENDOR, "Apple"),
	  DMI_MATCH(DMI_PRODUCT_NAME, "MacBook") पूर्ण,
	पूर्ण,
	अणु applesmc_dmi_match, "Apple Macmini", अणु
	  DMI_MATCH(DMI_BOARD_VENDOR, "Apple"),
	  DMI_MATCH(DMI_PRODUCT_NAME, "Macmini") पूर्ण,
	पूर्ण,
	अणु applesmc_dmi_match, "Apple MacPro", अणु
	  DMI_MATCH(DMI_BOARD_VENDOR, "Apple"),
	  DMI_MATCH(DMI_PRODUCT_NAME, "MacPro") पूर्ण,
	पूर्ण,
	अणु applesmc_dmi_match, "Apple iMac", अणु
	  DMI_MATCH(DMI_BOARD_VENDOR, "Apple"),
	  DMI_MATCH(DMI_PRODUCT_NAME, "iMac") पूर्ण,
	पूर्ण,
	अणु applesmc_dmi_match, "Apple Xserve", अणु
	  DMI_MATCH(DMI_BOARD_VENDOR, "Apple"),
	  DMI_MATCH(DMI_PRODUCT_NAME, "Xserve") पूर्ण,
	पूर्ण,
	अणु .ident = शून्य पूर्ण
पूर्ण;

अटल पूर्णांक __init applesmc_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!dmi_check_प्रणाली(applesmc_whitelist)) अणु
		pr_warn("supported laptop not found!\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!request_region(APPLESMC_DATA_PORT, APPLESMC_NR_PORTS,
								"applesmc")) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&applesmc_driver);
	अगर (ret)
		जाओ out_region;

	pdev = platक्रमm_device_रेजिस्टर_simple("applesmc", APPLESMC_DATA_PORT,
					       शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		ret = PTR_ERR(pdev);
		जाओ out_driver;
	पूर्ण

	/* create रेजिस्टर cache */
	ret = applesmc_init_smcreg();
	अगर (ret)
		जाओ out_device;

	ret = applesmc_create_nodes(info_group, 1);
	अगर (ret)
		जाओ out_smcreg;

	ret = applesmc_create_nodes(fan_group, smcreg.fan_count);
	अगर (ret)
		जाओ out_info;

	ret = applesmc_create_nodes(temp_group, smcreg.index_count);
	अगर (ret)
		जाओ out_fans;

	ret = applesmc_create_accelerometer();
	अगर (ret)
		जाओ out_temperature;

	ret = applesmc_create_light_sensor();
	अगर (ret)
		जाओ out_accelerometer;

	ret = applesmc_create_key_backlight();
	अगर (ret)
		जाओ out_light_sysfs;

	hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(hwmon_dev)) अणु
		ret = PTR_ERR(hwmon_dev);
		जाओ out_light_ledclass;
	पूर्ण

	वापस 0;

out_light_ledclass:
	applesmc_release_key_backlight();
out_light_sysfs:
	applesmc_release_light_sensor();
out_accelerometer:
	applesmc_release_accelerometer();
out_temperature:
	applesmc_destroy_nodes(temp_group);
out_fans:
	applesmc_destroy_nodes(fan_group);
out_info:
	applesmc_destroy_nodes(info_group);
out_smcreg:
	applesmc_destroy_smcreg();
out_device:
	platक्रमm_device_unरेजिस्टर(pdev);
out_driver:
	platक्रमm_driver_unरेजिस्टर(&applesmc_driver);
out_region:
	release_region(APPLESMC_DATA_PORT, APPLESMC_NR_PORTS);
out:
	pr_warn("driver init failed (ret=%d)!\n", ret);
	वापस ret;
पूर्ण

अटल व्योम __निकास applesmc_निकास(व्योम)
अणु
	hwmon_device_unरेजिस्टर(hwmon_dev);
	applesmc_release_key_backlight();
	applesmc_release_light_sensor();
	applesmc_release_accelerometer();
	applesmc_destroy_nodes(temp_group);
	applesmc_destroy_nodes(fan_group);
	applesmc_destroy_nodes(info_group);
	applesmc_destroy_smcreg();
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&applesmc_driver);
	release_region(APPLESMC_DATA_PORT, APPLESMC_NR_PORTS);
पूर्ण

module_init(applesmc_init);
module_निकास(applesmc_निकास);

MODULE_AUTHOR("Nicolas Boichat");
MODULE_DESCRIPTION("Apple SMC");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(dmi, applesmc_whitelist);
