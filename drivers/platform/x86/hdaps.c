<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * hdaps.c - driver क्रम IBM's Hard Drive Active Protection System
 *
 * Copyright (C) 2005 Robert Love <rml@novell.com>
 * Copyright (C) 2005 Jesper Juhl <jj@chaosbits.net>
 *
 * The HardDisk Active Protection System (hdaps) is present in IBM ThinkPads
 * starting with the R40, T41, and X40.  It provides a basic two-axis
 * accelerometer and other data, such as the device's temperature.
 *
 * This driver is based on the करोcument by Mark A. Smith available at
 * http://www.almaden.ibm.com/cs/people/marksmith/tpaps.hपंचांगl and a lot of trial
 * and error.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/dmi.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पन.स>

#घोषणा HDAPS_LOW_PORT		0x1600	/* first port used by hdaps */
#घोषणा HDAPS_NR_PORTS		0x30	/* number of ports: 0x1600 - 0x162f */

#घोषणा HDAPS_PORT_STATE	0x1611	/* device state */
#घोषणा HDAPS_PORT_YPOS		0x1612	/* y-axis position */
#घोषणा	HDAPS_PORT_XPOS		0x1614	/* x-axis position */
#घोषणा HDAPS_PORT_TEMP1	0x1616	/* device temperature, in Celsius */
#घोषणा HDAPS_PORT_YVAR		0x1617	/* y-axis variance (what is this?) */
#घोषणा HDAPS_PORT_XVAR		0x1619	/* x-axis variance (what is this?) */
#घोषणा HDAPS_PORT_TEMP2	0x161b	/* device temperature (again?) */
#घोषणा HDAPS_PORT_UNKNOWN	0x161c	/* what is this? */
#घोषणा HDAPS_PORT_KMACT	0x161d	/* keyboard or mouse activity */

#घोषणा STATE_FRESH		0x50	/* accelerometer data is fresh */

#घोषणा KEYBD_MASK		0x20	/* set अगर keyboard activity */
#घोषणा MOUSE_MASK		0x40	/* set अगर mouse activity */
#घोषणा KEYBD_ISSET(n)		(!! (n & KEYBD_MASK))	/* keyboard used? */
#घोषणा MOUSE_ISSET(n)		(!! (n & MOUSE_MASK))	/* mouse used? */

#घोषणा INIT_TIMEOUT_MSECS	4000	/* रुको up to 4s क्रम device init ... */
#घोषणा INIT_WAIT_MSECS		200	/* ... in 200ms increments */

#घोषणा HDAPS_POLL_INTERVAL	50	/* poll क्रम input every 1/20s (50 ms)*/
#घोषणा HDAPS_INPUT_FUZZ	4	/* input event threshold */
#घोषणा HDAPS_INPUT_FLAT	4

#घोषणा HDAPS_X_AXIS		(1 << 0)
#घोषणा HDAPS_Y_AXIS		(1 << 1)
#घोषणा HDAPS_BOTH_AXES		(HDAPS_X_AXIS | HDAPS_Y_AXIS)

अटल काष्ठा platक्रमm_device *pdev;
अटल काष्ठा input_dev *hdaps_idev;
अटल अचिन्हित पूर्णांक hdaps_invert;
अटल u8 km_activity;
अटल पूर्णांक rest_x;
अटल पूर्णांक rest_y;

अटल DEFINE_MUTEX(hdaps_mtx);

/*
 * __get_latch - Get the value from a given port.  Callers must hold hdaps_mtx.
 */
अटल अंतरभूत u8 __get_latch(u16 port)
अणु
	वापस inb(port) & 0xff;
पूर्ण

/*
 * __check_latch - Check a port latch क्रम a given value.  Returns zero अगर the
 * port contains the given value.  Callers must hold hdaps_mtx.
 */
अटल अंतरभूत पूर्णांक __check_latch(u16 port, u8 val)
अणु
	अगर (__get_latch(port) == val)
		वापस 0;
	वापस -EINVAL;
पूर्ण

/*
 * __रुको_latch - Wait up to 100us क्रम a port latch to get a certain value,
 * वापसing zero अगर the value is obtained.  Callers must hold hdaps_mtx.
 */
अटल पूर्णांक __रुको_latch(u16 port, u8 val)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 20; i++) अणु
		अगर (!__check_latch(port, val))
			वापस 0;
		udelay(5);
	पूर्ण

	वापस -EIO;
पूर्ण

/*
 * __device_refresh - request a refresh from the accelerometer.  Does not रुको
 * क्रम refresh to complete.  Callers must hold hdaps_mtx.
 */
अटल व्योम __device_refresh(व्योम)
अणु
	udelay(200);
	अगर (inb(0x1604) != STATE_FRESH) अणु
		outb(0x11, 0x1610);
		outb(0x01, 0x161f);
	पूर्ण
पूर्ण

/*
 * __device_refresh_sync - request a synchronous refresh from the
 * accelerometer.  We रुको क्रम the refresh to complete.  Returns zero अगर
 * successful and nonzero on error.  Callers must hold hdaps_mtx.
 */
अटल पूर्णांक __device_refresh_sync(व्योम)
अणु
	__device_refresh();
	वापस __रुको_latch(0x1604, STATE_FRESH);
पूर्ण

/*
 * __device_complete - indicate to the accelerometer that we are करोne पढ़ोing
 * data, and then initiate an async refresh.  Callers must hold hdaps_mtx.
 */
अटल अंतरभूत व्योम __device_complete(व्योम)
अणु
	inb(0x161f);
	inb(0x1604);
	__device_refresh();
पूर्ण

/*
 * hdaps_पढ़ोb_one - पढ़ोs a byte from a single I/O port, placing the value in
 * the given poपूर्णांकer.  Returns zero on success or a negative error on failure.
 * Can sleep.
 */
अटल पूर्णांक hdaps_पढ़ोb_one(अचिन्हित पूर्णांक port, u8 *val)
अणु
	पूर्णांक ret;

	mutex_lock(&hdaps_mtx);

	/* करो a sync refresh -- we need to be sure that we पढ़ो fresh data */
	ret = __device_refresh_sync();
	अगर (ret)
		जाओ out;

	*val = inb(port);
	__device_complete();

out:
	mutex_unlock(&hdaps_mtx);
	वापस ret;
पूर्ण

/* __hdaps_पढ़ो_pair - पूर्णांकernal lockless helper क्रम hdaps_पढ़ो_pair(). */
अटल पूर्णांक __hdaps_पढ़ो_pair(अचिन्हित पूर्णांक port1, अचिन्हित पूर्णांक port2,
			     पूर्णांक *x, पूर्णांक *y)
अणु
	/* करो a sync refresh -- we need to be sure that we पढ़ो fresh data */
	अगर (__device_refresh_sync())
		वापस -EIO;

	*y = inw(port2);
	*x = inw(port1);
	km_activity = inb(HDAPS_PORT_KMACT);
	__device_complete();

	/* hdaps_invert is a bitvector to negate the axes */
	अगर (hdaps_invert & HDAPS_X_AXIS)
		*x = -*x;
	अगर (hdaps_invert & HDAPS_Y_AXIS)
		*y = -*y;

	वापस 0;
पूर्ण

/*
 * hdaps_पढ़ो_pair - पढ़ोs the values from a pair of ports, placing the values
 * in the given poपूर्णांकers.  Returns zero on success.  Can sleep.
 */
अटल पूर्णांक hdaps_पढ़ो_pair(अचिन्हित पूर्णांक port1, अचिन्हित पूर्णांक port2,
			   पूर्णांक *val1, पूर्णांक *val2)
अणु
	पूर्णांक ret;

	mutex_lock(&hdaps_mtx);
	ret = __hdaps_पढ़ो_pair(port1, port2, val1, val2);
	mutex_unlock(&hdaps_mtx);

	वापस ret;
पूर्ण

/*
 * hdaps_device_init - initialize the accelerometer.  Returns zero on success
 * and negative error code on failure.  Can sleep.
 */
अटल पूर्णांक hdaps_device_init(व्योम)
अणु
	पूर्णांक total, ret = -ENXIO;

	mutex_lock(&hdaps_mtx);

	outb(0x13, 0x1610);
	outb(0x01, 0x161f);
	अगर (__रुको_latch(0x161f, 0x00))
		जाओ out;

	/*
	 * Most ThinkPads वापस 0x01.
	 *
	 * Others--namely the R50p, T41p, and T42p--वापस 0x03.  These laptops
	 * have "inverted" axises.
	 *
	 * The 0x02 value occurs when the chip has been previously initialized.
	 */
	अगर (__check_latch(0x1611, 0x03) &&
		     __check_latch(0x1611, 0x02) &&
		     __check_latch(0x1611, 0x01))
		जाओ out;

	prपूर्णांकk(KERN_DEBUG "hdaps: initial latch check good (0x%02x)\n",
	       __get_latch(0x1611));

	outb(0x17, 0x1610);
	outb(0x81, 0x1611);
	outb(0x01, 0x161f);
	अगर (__रुको_latch(0x161f, 0x00))
		जाओ out;
	अगर (__रुको_latch(0x1611, 0x00))
		जाओ out;
	अगर (__रुको_latch(0x1612, 0x60))
		जाओ out;
	अगर (__रुको_latch(0x1613, 0x00))
		जाओ out;
	outb(0x14, 0x1610);
	outb(0x01, 0x1611);
	outb(0x01, 0x161f);
	अगर (__रुको_latch(0x161f, 0x00))
		जाओ out;
	outb(0x10, 0x1610);
	outb(0xc8, 0x1611);
	outb(0x00, 0x1612);
	outb(0x02, 0x1613);
	outb(0x01, 0x161f);
	अगर (__रुको_latch(0x161f, 0x00))
		जाओ out;
	अगर (__device_refresh_sync())
		जाओ out;
	अगर (__रुको_latch(0x1611, 0x00))
		जाओ out;

	/* we have करोne our dance, now let's रुको क्रम the applause */
	क्रम (total = INIT_TIMEOUT_MSECS; total > 0; total -= INIT_WAIT_MSECS) अणु
		पूर्णांक x, y;

		/* a पढ़ो of the device helps push it पूर्णांकo action */
		__hdaps_पढ़ो_pair(HDAPS_PORT_XPOS, HDAPS_PORT_YPOS, &x, &y);
		अगर (!__रुको_latch(0x1611, 0x02)) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		msleep(INIT_WAIT_MSECS);
	पूर्ण

out:
	mutex_unlock(&hdaps_mtx);
	वापस ret;
पूर्ण


/* Device model stuff */

अटल पूर्णांक hdaps_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;

	ret = hdaps_device_init();
	अगर (ret)
		वापस ret;

	pr_info("device successfully initialized\n");
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hdaps_resume(काष्ठा device *dev)
अणु
	वापस hdaps_device_init();
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(hdaps_pm, शून्य, hdaps_resume);

अटल काष्ठा platक्रमm_driver hdaps_driver = अणु
	.probe = hdaps_probe,
	.driver	= अणु
		.name = "hdaps",
		.pm = &hdaps_pm,
	पूर्ण,
पूर्ण;

/*
 * hdaps_calibrate - Set our "resting" values.  Callers must hold hdaps_mtx.
 */
अटल व्योम hdaps_calibrate(व्योम)
अणु
	__hdaps_पढ़ो_pair(HDAPS_PORT_XPOS, HDAPS_PORT_YPOS, &rest_x, &rest_y);
पूर्ण

अटल व्योम hdaps_mousedev_poll(काष्ठा input_dev *input_dev)
अणु
	पूर्णांक x, y;

	mutex_lock(&hdaps_mtx);

	अगर (__hdaps_पढ़ो_pair(HDAPS_PORT_XPOS, HDAPS_PORT_YPOS, &x, &y))
		जाओ out;

	input_report_असल(input_dev, ABS_X, x - rest_x);
	input_report_असल(input_dev, ABS_Y, y - rest_y);
	input_sync(input_dev);

out:
	mutex_unlock(&hdaps_mtx);
पूर्ण


/* Sysfs Files */

अटल sमाप_प्रकार hdaps_position_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret, x, y;

	ret = hdaps_पढ़ो_pair(HDAPS_PORT_XPOS, HDAPS_PORT_YPOS, &x, &y);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "(%d,%d)\n", x, y);
पूर्ण

अटल sमाप_प्रकार hdaps_variance_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret, x, y;

	ret = hdaps_पढ़ो_pair(HDAPS_PORT_XVAR, HDAPS_PORT_YVAR, &x, &y);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "(%d,%d)\n", x, y);
पूर्ण

अटल sमाप_प्रकार hdaps_temp1_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 temp;
	पूर्णांक ret;

	ret = hdaps_पढ़ोb_one(HDAPS_PORT_TEMP1, &temp);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", temp);
पूर्ण

अटल sमाप_प्रकार hdaps_temp2_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 temp;
	पूर्णांक ret;

	ret = hdaps_पढ़ोb_one(HDAPS_PORT_TEMP2, &temp);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", temp);
पूर्ण

अटल sमाप_प्रकार hdaps_keyboard_activity_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", KEYBD_ISSET(km_activity));
पूर्ण

अटल sमाप_प्रकार hdaps_mouse_activity_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", MOUSE_ISSET(km_activity));
पूर्ण

अटल sमाप_प्रकार hdaps_calibrate_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "(%d,%d)\n", rest_x, rest_y);
पूर्ण

अटल sमाप_प्रकार hdaps_calibrate_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	mutex_lock(&hdaps_mtx);
	hdaps_calibrate();
	mutex_unlock(&hdaps_mtx);

	वापस count;
पूर्ण

अटल sमाप_प्रकार hdaps_invert_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", hdaps_invert);
पूर्ण

अटल sमाप_प्रकार hdaps_invert_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक invert;

	अगर (माला_पूछो(buf, "%d", &invert) != 1 ||
	    invert < 0 || invert > HDAPS_BOTH_AXES)
		वापस -EINVAL;

	hdaps_invert = invert;
	hdaps_calibrate();

	वापस count;
पूर्ण

अटल DEVICE_ATTR(position, 0444, hdaps_position_show, शून्य);
अटल DEVICE_ATTR(variance, 0444, hdaps_variance_show, शून्य);
अटल DEVICE_ATTR(temp1, 0444, hdaps_temp1_show, शून्य);
अटल DEVICE_ATTR(temp2, 0444, hdaps_temp2_show, शून्य);
अटल DEVICE_ATTR(keyboard_activity, 0444, hdaps_keyboard_activity_show, शून्य);
अटल DEVICE_ATTR(mouse_activity, 0444, hdaps_mouse_activity_show, शून्य);
अटल DEVICE_ATTR(calibrate, 0644, hdaps_calibrate_show,hdaps_calibrate_store);
अटल DEVICE_ATTR(invert, 0644, hdaps_invert_show, hdaps_invert_store);

अटल काष्ठा attribute *hdaps_attributes[] = अणु
	&dev_attr_position.attr,
	&dev_attr_variance.attr,
	&dev_attr_temp1.attr,
	&dev_attr_temp2.attr,
	&dev_attr_keyboard_activity.attr,
	&dev_attr_mouse_activity.attr,
	&dev_attr_calibrate.attr,
	&dev_attr_invert.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group hdaps_attribute_group = अणु
	.attrs = hdaps_attributes,
पूर्ण;


/* Module stuff */

/* hdaps_dmi_match - found a match.  वापस one, लघु-circuiting the hunt. */
अटल पूर्णांक __init hdaps_dmi_match(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_info("%s detected\n", id->ident);
	वापस 1;
पूर्ण

/* hdaps_dmi_match_invert - found an inverted match. */
अटल पूर्णांक __init hdaps_dmi_match_invert(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	hdaps_invert = (अचिन्हित दीर्घ)id->driver_data;
	pr_info("inverting axis (%u) readings\n", hdaps_invert);
	वापस hdaps_dmi_match(id);
पूर्ण

#घोषणा HDAPS_DMI_MATCH_INVERT(venकरोr, model, axes) अणु	\
	.ident = venकरोr " " model,			\
	.callback = hdaps_dmi_match_invert,		\
	.driver_data = (व्योम *)axes,			\
	.matches = अणु					\
		DMI_MATCH(DMI_BOARD_VENDOR, venकरोr),	\
		DMI_MATCH(DMI_PRODUCT_VERSION, model)	\
	पूर्ण						\
पूर्ण

#घोषणा HDAPS_DMI_MATCH_NORMAL(venकरोr, model)		\
	HDAPS_DMI_MATCH_INVERT(venकरोr, model, 0)

/* Note that HDAPS_DMI_MATCH_NORMAL("ThinkPad T42") would match
   "ThinkPad T42p", so the order of the entries matters.
   If your ThinkPad is not recognized, please update to latest
   BIOS. This is especially the हाल क्रम some R52 ThinkPads. */
अटल स्थिर काष्ठा dmi_प्रणाली_id hdaps_whitelist[] __initस्थिर = अणु
	HDAPS_DMI_MATCH_INVERT("IBM", "ThinkPad R50p", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_NORMAL("IBM", "ThinkPad R50"),
	HDAPS_DMI_MATCH_NORMAL("IBM", "ThinkPad R51"),
	HDAPS_DMI_MATCH_NORMAL("IBM", "ThinkPad R52"),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad R61i", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad R61", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_INVERT("IBM", "ThinkPad T41p", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_NORMAL("IBM", "ThinkPad T41"),
	HDAPS_DMI_MATCH_INVERT("IBM", "ThinkPad T42p", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_NORMAL("IBM", "ThinkPad T42"),
	HDAPS_DMI_MATCH_NORMAL("IBM", "ThinkPad T43"),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad T400", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad T60", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad T61p", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad T61", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_NORMAL("IBM", "ThinkPad X40"),
	HDAPS_DMI_MATCH_INVERT("IBM", "ThinkPad X41", HDAPS_Y_AXIS),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad X60", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad X61s", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad X61", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_NORMAL("IBM", "ThinkPad Z60m"),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad Z61m", HDAPS_BOTH_AXES),
	HDAPS_DMI_MATCH_INVERT("LENOVO", "ThinkPad Z61p", HDAPS_BOTH_AXES),
	अणु .ident = शून्य पूर्ण
पूर्ण;

अटल पूर्णांक __init hdaps_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!dmi_check_प्रणाली(hdaps_whitelist)) अणु
		pr_warn("supported laptop not found!\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!request_region(HDAPS_LOW_PORT, HDAPS_NR_PORTS, "hdaps")) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&hdaps_driver);
	अगर (ret)
		जाओ out_region;

	pdev = platक्रमm_device_रेजिस्टर_simple("hdaps", -1, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		ret = PTR_ERR(pdev);
		जाओ out_driver;
	पूर्ण

	ret = sysfs_create_group(&pdev->dev.kobj, &hdaps_attribute_group);
	अगर (ret)
		जाओ out_device;

	hdaps_idev = input_allocate_device();
	अगर (!hdaps_idev) अणु
		ret = -ENOMEM;
		जाओ out_group;
	पूर्ण

	/* initial calibrate क्रम the input device */
	hdaps_calibrate();

	/* initialize the input class */
	hdaps_idev->name = "hdaps";
	hdaps_idev->phys = "isa1600/input0";
	hdaps_idev->id.bustype = BUS_ISA;
	hdaps_idev->dev.parent = &pdev->dev;
	input_set_असल_params(hdaps_idev, ABS_X,
			-256, 256, HDAPS_INPUT_FUZZ, HDAPS_INPUT_FLAT);
	input_set_असल_params(hdaps_idev, ABS_Y,
			-256, 256, HDAPS_INPUT_FUZZ, HDAPS_INPUT_FLAT);

	ret = input_setup_polling(hdaps_idev, hdaps_mousedev_poll);
	अगर (ret)
		जाओ out_idev;

	input_set_poll_पूर्णांकerval(hdaps_idev, HDAPS_POLL_INTERVAL);

	ret = input_रेजिस्टर_device(hdaps_idev);
	अगर (ret)
		जाओ out_idev;

	pr_info("driver successfully loaded\n");
	वापस 0;

out_idev:
	input_मुक्त_device(hdaps_idev);
out_group:
	sysfs_हटाओ_group(&pdev->dev.kobj, &hdaps_attribute_group);
out_device:
	platक्रमm_device_unरेजिस्टर(pdev);
out_driver:
	platक्रमm_driver_unरेजिस्टर(&hdaps_driver);
out_region:
	release_region(HDAPS_LOW_PORT, HDAPS_NR_PORTS);
out:
	pr_warn("driver init failed (ret=%d)!\n", ret);
	वापस ret;
पूर्ण

अटल व्योम __निकास hdaps_निकास(व्योम)
अणु
	input_unरेजिस्टर_device(hdaps_idev);
	sysfs_हटाओ_group(&pdev->dev.kobj, &hdaps_attribute_group);
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&hdaps_driver);
	release_region(HDAPS_LOW_PORT, HDAPS_NR_PORTS);

	pr_info("driver unloaded\n");
पूर्ण

module_init(hdaps_init);
module_निकास(hdaps_निकास);

module_param_named(invert, hdaps_invert, पूर्णांक, 0);
MODULE_PARM_DESC(invert, "invert data along each axis. 1 invert x-axis, "
		 "2 invert y-axis, 3 invert both axes.");

MODULE_AUTHOR("Robert Love");
MODULE_DESCRIPTION("IBM Hard Drive Active Protection System (HDAPS) driver");
MODULE_LICENSE("GPL v2");
