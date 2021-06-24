<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/अक्षर/pc8736x_gpio.c

   National Semiconductor PC8736x GPIO driver.  Allows a user space
   process to play with the GPIO pins.

   Copyright (c) 2005,2006 Jim Cromie <jim.cromie@gmail.com>

   adapted from linux/drivers/अक्षर/scx200_gpio.c
   Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-प्रणाली.com>,
*/

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/cdev.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/mutex.h>
#समावेश <linux/nsc_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>

#घोषणा DEVNAME "pc8736x_gpio"

MODULE_AUTHOR("Jim Cromie <jim.cromie@gmail.com>");
MODULE_DESCRIPTION("NatSemi/Winbond PC-8736x GPIO Pin Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक major;		/* शेष to dynamic major */
module_param(major, पूर्णांक, 0);
MODULE_PARM_DESC(major, "Major device number");

अटल DEFINE_MUTEX(pc8736x_gpio_config_lock);
अटल अचिन्हित pc8736x_gpio_base;
अटल u8 pc8736x_gpio_shaकरोw[4];

#घोषणा SIO_BASE1       0x2E	/* 1st command-reg to check */
#घोषणा SIO_BASE2       0x4E	/* alt command-reg to check */

#घोषणा SIO_SID		0x20	/* SuperI/O ID Register */
#घोषणा SIO_SID_PC87365	0xe5	/* Expected value in ID Register क्रम PC87365 */
#घोषणा SIO_SID_PC87366	0xe9	/* Expected value in ID Register क्रम PC87366 */

#घोषणा SIO_CF1		0x21	/* chip config, bit0 is chip enable */

#घोषणा PC8736X_GPIO_RANGE	16 /* ioaddr range */
#घोषणा PC8736X_GPIO_CT		32 /* minors matching 4 8 bit ports */

#घोषणा SIO_UNIT_SEL	0x7	/* unit select reg */
#घोषणा SIO_UNIT_ACT	0x30	/* unit enable */
#घोषणा SIO_GPIO_UNIT	0x7	/* unit number of GPIO */
#घोषणा SIO_VLM_UNIT	0x0D
#घोषणा SIO_TMS_UNIT	0x0E

/* config-space addrs to पढ़ो/ग_लिखो each unit's runसमय addr */
#घोषणा SIO_BASE_HADDR		0x60
#घोषणा SIO_BASE_LADDR		0x61

/* GPIO config-space pin-control addresses */
#घोषणा SIO_GPIO_PIN_SELECT	0xF0
#घोषणा SIO_GPIO_PIN_CONFIG     0xF1
#घोषणा SIO_GPIO_PIN_EVENT      0xF2

अटल अचिन्हित अक्षर superio_cmd = 0;
अटल अचिन्हित अक्षर selected_device = 0xFF;	/* bogus start val */

/* GPIO port runसमय access, functionality */
अटल पूर्णांक port_offset[] = अणु 0, 4, 8, 10 पूर्ण;	/* non-unअगरorm offsets ! */
/* अटल पूर्णांक event_capable[] = अणु 1, 1, 0, 0 पूर्ण;   ports 2,3 are hobbled */

#घोषणा PORT_OUT	0
#घोषणा PORT_IN		1
#घोषणा PORT_EVT_EN	2
#घोषणा PORT_EVT_STST	3

अटल काष्ठा platक्रमm_device *pdev;  /* use in dev_*() */

अटल अंतरभूत व्योम superio_outb(पूर्णांक addr, पूर्णांक val)
अणु
	outb_p(addr, superio_cmd);
	outb_p(val, superio_cmd + 1);
पूर्ण

अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक addr)
अणु
	outb_p(addr, superio_cmd);
	वापस inb_p(superio_cmd + 1);
पूर्ण

अटल पूर्णांक pc8736x_superio_present(व्योम)
अणु
	पूर्णांक id;

	/* try the 2 possible values, पढ़ो a hardware reg to verअगरy */
	superio_cmd = SIO_BASE1;
	id = superio_inb(SIO_SID);
	अगर (id == SIO_SID_PC87365 || id == SIO_SID_PC87366)
		वापस superio_cmd;

	superio_cmd = SIO_BASE2;
	id = superio_inb(SIO_SID);
	अगर (id == SIO_SID_PC87365 || id == SIO_SID_PC87366)
		वापस superio_cmd;

	वापस 0;
पूर्ण

अटल व्योम device_select(अचिन्हित devldn)
अणु
	superio_outb(SIO_UNIT_SEL, devldn);
	selected_device = devldn;
पूर्ण

अटल व्योम select_pin(अचिन्हित iminor)
अणु
	/* select GPIO port/pin from device minor number */
	device_select(SIO_GPIO_UNIT);
	superio_outb(SIO_GPIO_PIN_SELECT,
		     ((iminor << 1) & 0xF0) | (iminor & 0x7));
पूर्ण

अटल अंतरभूत u32 pc8736x_gpio_configure_fn(अचिन्हित index, u32 mask, u32 bits,
					    u32 func_slct)
अणु
	u32 config, new_config;

	mutex_lock(&pc8736x_gpio_config_lock);

	device_select(SIO_GPIO_UNIT);
	select_pin(index);

	/* पढ़ो current config value */
	config = superio_inb(func_slct);

	/* set new config */
	new_config = (config & mask) | bits;
	superio_outb(func_slct, new_config);

	mutex_unlock(&pc8736x_gpio_config_lock);

	वापस config;
पूर्ण

अटल u32 pc8736x_gpio_configure(अचिन्हित index, u32 mask, u32 bits)
अणु
	वापस pc8736x_gpio_configure_fn(index, mask, bits,
					 SIO_GPIO_PIN_CONFIG);
पूर्ण

अटल पूर्णांक pc8736x_gpio_get(अचिन्हित minor)
अणु
	पूर्णांक port, bit, val;

	port = minor >> 3;
	bit = minor & 7;
	val = inb_p(pc8736x_gpio_base + port_offset[port] + PORT_IN);
	val >>= bit;
	val &= 1;

	dev_dbg(&pdev->dev, "_gpio_get(%d from %x bit %d) == val %d\n",
		minor, pc8736x_gpio_base + port_offset[port] + PORT_IN, bit,
		val);

	वापस val;
पूर्ण

अटल व्योम pc8736x_gpio_set(अचिन्हित minor, पूर्णांक val)
अणु
	पूर्णांक port, bit, curval;

	minor &= 0x1f;
	port = minor >> 3;
	bit = minor & 7;
	curval = inb_p(pc8736x_gpio_base + port_offset[port] + PORT_OUT);

	dev_dbg(&pdev->dev, "addr:%x cur:%x bit-pos:%d cur-bit:%x + new:%d -> bit-new:%d\n",
		pc8736x_gpio_base + port_offset[port] + PORT_OUT,
		curval, bit, (curval & ~(1 << bit)), val, (val << bit));

	val = (curval & ~(1 << bit)) | (val << bit);

	dev_dbg(&pdev->dev, "gpio_set(minor:%d port:%d bit:%d)"
		" %2x -> %2x\n", minor, port, bit, curval, val);

	outb_p(val, pc8736x_gpio_base + port_offset[port] + PORT_OUT);

	curval = inb_p(pc8736x_gpio_base + port_offset[port] + PORT_OUT);
	val = inb_p(pc8736x_gpio_base + port_offset[port] + PORT_IN);

	dev_dbg(&pdev->dev, "wrote %x, read: %x\n", curval, val);
	pc8736x_gpio_shaकरोw[port] = val;
पूर्ण

अटल पूर्णांक pc8736x_gpio_current(अचिन्हित minor)
अणु
	पूर्णांक port, bit;
	minor &= 0x1f;
	port = minor >> 3;
	bit = minor & 7;
	वापस ((pc8736x_gpio_shaकरोw[port] >> bit) & 0x01);
पूर्ण

अटल व्योम pc8736x_gpio_change(अचिन्हित index)
अणु
	pc8736x_gpio_set(index, !pc8736x_gpio_current(index));
पूर्ण

अटल काष्ठा nsc_gpio_ops pc8736x_gpio_ops = अणु
	.owner		= THIS_MODULE,
	.gpio_config	= pc8736x_gpio_configure,
	.gpio_dump	= nsc_gpio_dump,
	.gpio_get	= pc8736x_gpio_get,
	.gpio_set	= pc8736x_gpio_set,
	.gpio_change	= pc8736x_gpio_change,
	.gpio_current	= pc8736x_gpio_current
पूर्ण;

अटल पूर्णांक pc8736x_gpio_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित m = iminor(inode);
	file->निजी_data = &pc8736x_gpio_ops;

	dev_dbg(&pdev->dev, "open %d\n", m);

	अगर (m >= PC8736X_GPIO_CT)
		वापस -EINVAL;
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations pc8736x_gpio_fileops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= pc8736x_gpio_खोलो,
	.ग_लिखो	= nsc_gpio_ग_लिखो,
	.पढ़ो	= nsc_gpio_पढ़ो,
	.llseek = no_llseek,
पूर्ण;

अटल व्योम __init pc8736x_init_shaकरोw(व्योम)
अणु
	पूर्णांक port;

	/* पढ़ो the current values driven on the GPIO संकेतs */
	क्रम (port = 0; port < 4; ++port)
		pc8736x_gpio_shaकरोw[port]
		    = inb_p(pc8736x_gpio_base + port_offset[port]
			    + PORT_OUT);

पूर्ण

अटल काष्ठा cdev pc8736x_gpio_cdev;

अटल पूर्णांक __init pc8736x_gpio_init(व्योम)
अणु
	पूर्णांक rc;
	dev_t devid;

	pdev = platक्रमm_device_alloc(DEVNAME, 0);
	अगर (!pdev)
		वापस -ENOMEM;

	rc = platक्रमm_device_add(pdev);
	अगर (rc) अणु
		rc = -ENODEV;
		जाओ unकरो_platक्रमm_dev_alloc;
	पूर्ण
	dev_info(&pdev->dev, "NatSemi pc8736x GPIO Driver Initializing\n");

	अगर (!pc8736x_superio_present()) अणु
		rc = -ENODEV;
		dev_err(&pdev->dev, "no device found\n");
		जाओ unकरो_platक्रमm_dev_add;
	पूर्ण
	pc8736x_gpio_ops.dev = &pdev->dev;

	/* Verअगरy that chip and it's GPIO unit are both enabled.
	   My BIOS करोes this, so I take minimum action here
	 */
	rc = superio_inb(SIO_CF1);
	अगर (!(rc & 0x01)) अणु
		rc = -ENODEV;
		dev_err(&pdev->dev, "device not enabled\n");
		जाओ unकरो_platक्रमm_dev_add;
	पूर्ण
	device_select(SIO_GPIO_UNIT);
	अगर (!superio_inb(SIO_UNIT_ACT)) अणु
		rc = -ENODEV;
		dev_err(&pdev->dev, "GPIO unit not enabled\n");
		जाओ unकरो_platक्रमm_dev_add;
	पूर्ण

	/* पढ़ो the GPIO unit base addr that chip responds to */
	pc8736x_gpio_base = (superio_inb(SIO_BASE_HADDR) << 8
			     | superio_inb(SIO_BASE_LADDR));

	अगर (!request_region(pc8736x_gpio_base, PC8736X_GPIO_RANGE, DEVNAME)) अणु
		rc = -ENODEV;
		dev_err(&pdev->dev, "GPIO ioport %x busy\n",
			pc8736x_gpio_base);
		जाओ unकरो_platक्रमm_dev_add;
	पूर्ण
	dev_info(&pdev->dev, "GPIO ioport %x reserved\n", pc8736x_gpio_base);

	अगर (major) अणु
		devid = MKDEV(major, 0);
		rc = रेजिस्टर_chrdev_region(devid, PC8736X_GPIO_CT, DEVNAME);
	पूर्ण अन्यथा अणु
		rc = alloc_chrdev_region(&devid, 0, PC8736X_GPIO_CT, DEVNAME);
		major = MAJOR(devid);
	पूर्ण

	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "register-chrdev failed: %d\n", rc);
		जाओ unकरो_request_region;
	पूर्ण
	अगर (!major) अणु
		major = rc;
		dev_dbg(&pdev->dev, "got dynamic major %d\n", major);
	पूर्ण

	pc8736x_init_shaकरोw();

	/* ignore minor errs, and succeed */
	cdev_init(&pc8736x_gpio_cdev, &pc8736x_gpio_fileops);
	cdev_add(&pc8736x_gpio_cdev, devid, PC8736X_GPIO_CT);

	वापस 0;

unकरो_request_region:
	release_region(pc8736x_gpio_base, PC8736X_GPIO_RANGE);
unकरो_platक्रमm_dev_add:
	platक्रमm_device_del(pdev);
unकरो_platक्रमm_dev_alloc:
	platक्रमm_device_put(pdev);

	वापस rc;
पूर्ण

अटल व्योम __निकास pc8736x_gpio_cleanup(व्योम)
अणु
	dev_dbg(&pdev->dev, "cleanup\n");

	cdev_del(&pc8736x_gpio_cdev);
	unरेजिस्टर_chrdev_region(MKDEV(major,0), PC8736X_GPIO_CT);
	release_region(pc8736x_gpio_base, PC8736X_GPIO_RANGE);

	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

module_init(pc8736x_gpio_init);
module_निकास(pc8736x_gpio_cleanup);
