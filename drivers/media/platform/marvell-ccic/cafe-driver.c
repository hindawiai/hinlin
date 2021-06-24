<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A driver क्रम the CMOS camera controller in the Marvell 88ALP01 "cafe"
 * multअगरunction chip.  Currently works with the Omnivision OV7670
 * sensor.
 *
 * The data sheet क्रम this device can be found at:
 *    http://wiki.laptop.org/images/5/5c/88ALP01_Datasheet_July_2007.pdf
 *
 * Copyright 2006-11 One Laptop Per Child Association, Inc.
 * Copyright 2006-11 Jonathan Corbet <corbet@lwn.net>
 * Copyright 2018 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 *
 * Written by Jonathan Corbet, corbet@lwn.net.
 *
 * v4l2_device/v4l2_subdev conversion by:
 * Copyright (C) 2009 Hans Verkuil <hverkuil@xs4all.nl>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/i2c/ov7670.h>
#समावेश <linux/device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>

#समावेश "mcam-core.h"

#घोषणा CAFE_VERSION 0x000002


/*
 * Parameters.
 */
MODULE_AUTHOR("Jonathan Corbet <corbet@lwn.net>");
MODULE_DESCRIPTION("Marvell 88ALP01 CMOS Camera Controller driver");
MODULE_LICENSE("GPL");

काष्ठा cafe_camera अणु
	पूर्णांक रेजिस्टरed;			/* Fully initialized? */
	काष्ठा mcam_camera mcam;
	काष्ठा pci_dev *pdev;
	काष्ठा i2c_adapter *i2c_adapter;
	रुको_queue_head_t smbus_रुको;	/* Waiting on i2c events */
पूर्ण;

/*
 * Most of the camera controller रेजिस्टरs are defined in mcam-core.h,
 * but the Cafe platक्रमm has some additional रेजिस्टरs of its own;
 * they are described here.
 */

/*
 * "General purpose register" has a couple of GPIOs used क्रम sensor
 * घातer and reset on OLPC XO 1.0 प्रणालीs.
 */
#घोषणा REG_GPR		0xb4
#घोषणा	  GPR_C1EN	  0x00000020	/* Pad 1 (घातer करोwn) enable */
#घोषणा	  GPR_C0EN	  0x00000010	/* Pad 0 (reset) enable */
#घोषणा	  GPR_C1	  0x00000002	/* Control 1 value */
/*
 * Control 0 is wired to reset on OLPC machines.  For ov7x sensors,
 * it is active low.
 */
#घोषणा	  GPR_C0	  0x00000001	/* Control 0 value */

/*
 * These रेजिस्टरs control the SMBUS module क्रम communicating
 * with the sensor.
 */
#घोषणा REG_TWSIC0	0xb8	/* TWSI (smbus) control 0 */
#घोषणा	  TWSIC0_EN	  0x00000001	/* TWSI enable */
#घोषणा	  TWSIC0_MODE	  0x00000002	/* 1 = 16-bit, 0 = 8-bit */
#घोषणा	  TWSIC0_SID	  0x000003fc	/* Slave ID */
/*
 * Subtle trickery: the slave ID field starts with bit 2.  But the
 * Linux i2c stack wants to treat the bottommost bit as a separate
 * पढ़ो/ग_लिखो bit, which is why slave ID's are usually presented
 * >>1.  For consistency with that behavior, we shअगरt over three
 * bits instead of two.
 */
#घोषणा	  TWSIC0_SID_SHIFT 3
#घोषणा	  TWSIC0_CLKDIV	  0x0007fc00	/* Clock भागider */
#घोषणा	  TWSIC0_MASKACK  0x00400000	/* Mask ack from sensor */
#घोषणा	  TWSIC0_OVMAGIC  0x00800000	/* Make it work on OV sensors */

#घोषणा REG_TWSIC1	0xbc	/* TWSI control 1 */
#घोषणा	  TWSIC1_DATA	  0x0000ffff	/* Data to/from camchip */
#घोषणा	  TWSIC1_ADDR	  0x00ff0000	/* Address (रेजिस्टर) */
#घोषणा	  TWSIC1_ADDR_SHIFT 16
#घोषणा	  TWSIC1_READ	  0x01000000	/* Set क्रम पढ़ो op */
#घोषणा	  TWSIC1_WSTAT	  0x02000000	/* Write status */
#घोषणा	  TWSIC1_RVALID	  0x04000000	/* Read data valid */
#घोषणा	  TWSIC1_ERROR	  0x08000000	/* Something screwed up */

/*
 * Here's the weird global control रेजिस्टरs
 */
#घोषणा REG_GL_CSR     0x3004  /* Control/status रेजिस्टर */
#घोषणा	  GCSR_SRS	 0x00000001	/* SW Reset set */
#घोषणा	  GCSR_SRC	 0x00000002	/* SW Reset clear */
#घोषणा	  GCSR_MRS	 0x00000004	/* Master reset set */
#घोषणा	  GCSR_MRC	 0x00000008	/* HW Reset clear */
#घोषणा	  GCSR_CCIC_EN	 0x00004000    /* CCIC Clock enable */
#घोषणा REG_GL_IMASK   0x300c  /* Interrupt mask रेजिस्टर */
#घोषणा	  GIMSK_CCIC_EN		 0x00000004    /* CCIC Interrupt enable */

#घोषणा REG_GL_FCR	0x3038	/* GPIO functional control रेजिस्टर */
#घोषणा	  GFCR_GPIO_ON	  0x08		/* Camera GPIO enabled */
#घोषणा REG_GL_GPIOR	0x315c	/* GPIO रेजिस्टर */
#घोषणा	  GGPIO_OUT		0x80000	/* GPIO output */
#घोषणा	  GGPIO_VAL		0x00008	/* Output pin value */

#घोषणा REG_LEN		       (REG_GL_IMASK + 4)


/*
 * Debugging and related.
 */
#घोषणा cam_err(cam, fmt, arg...) \
	dev_err(&(cam)->pdev->dev, fmt, ##arg);
#घोषणा cam_warn(cam, fmt, arg...) \
	dev_warn(&(cam)->pdev->dev, fmt, ##arg);

/* -------------------------------------------------------------------- */
/*
 * The I2C/SMBUS पूर्णांकerface to the camera itself starts here.  The
 * controller handles SMBUS itself, presenting a relatively simple रेजिस्टर
 * पूर्णांकerface; all we have to करो is to tell it where to route the data.
 */
#घोषणा CAFE_SMBUS_TIMEOUT (HZ)  /* generous */

अटल अंतरभूत काष्ठा cafe_camera *to_cam(काष्ठा v4l2_device *dev)
अणु
	काष्ठा mcam_camera *m = container_of(dev, काष्ठा mcam_camera, v4l2_dev);
	वापस container_of(m, काष्ठा cafe_camera, mcam);
पूर्ण


अटल पूर्णांक cafe_smbus_ग_लिखो_करोne(काष्ठा mcam_camera *mcam)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक c1;

	/*
	 * We must delay after the पूर्णांकerrupt, or the controller माला_लो confused
	 * and never करोes give us good status.  Fortunately, we करोn't करो this
	 * often.
	 */
	udelay(20);
	spin_lock_irqsave(&mcam->dev_lock, flags);
	c1 = mcam_reg_पढ़ो(mcam, REG_TWSIC1);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);
	वापस (c1 & (TWSIC1_WSTAT|TWSIC1_ERROR)) != TWSIC1_WSTAT;
पूर्ण

अटल पूर्णांक cafe_smbus_ग_लिखो_data(काष्ठा cafe_camera *cam,
		u16 addr, u8 command, u8 value)
अणु
	अचिन्हित पूर्णांक rval;
	अचिन्हित दीर्घ flags;
	काष्ठा mcam_camera *mcam = &cam->mcam;

	spin_lock_irqsave(&mcam->dev_lock, flags);
	rval = TWSIC0_EN | ((addr << TWSIC0_SID_SHIFT) & TWSIC0_SID);
	rval |= TWSIC0_OVMAGIC;  /* Make OV sensors work */
	/*
	 * Marvell sez set clkभाग to all 1's क्रम now.
	 */
	rval |= TWSIC0_CLKDIV;
	mcam_reg_ग_लिखो(mcam, REG_TWSIC0, rval);
	(व्योम) mcam_reg_पढ़ो(mcam, REG_TWSIC1); /* क्रमce ग_लिखो */
	rval = value | ((command << TWSIC1_ADDR_SHIFT) & TWSIC1_ADDR);
	mcam_reg_ग_लिखो(mcam, REG_TWSIC1, rval);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);

	/* Unक्रमtunately, पढ़ोing TWSIC1 too soon after sending a command
	 * causes the device to die.
	 * Use a busy-रुको because we often send a large quantity of small
	 * commands at-once; using msleep() would cause a lot of context
	 * चयनes which take दीर्घer than 2ms, resulting in a noticeable
	 * boot-समय and capture-start delays.
	 */
	mdelay(2);

	/*
	 * Another sad fact is that someबार, commands silently complete but
	 * cafe_smbus_ग_लिखो_करोne() never becomes aware of this.
	 * This happens at अक्रमom and appears to possible occur with any
	 * command.
	 * We करोn't understand why this is. We work around this issue
	 * with the समयout in the रुको below, assuming that all commands
	 * complete within the समयout.
	 */
	रुको_event_समयout(cam->smbus_रुको, cafe_smbus_ग_लिखो_करोne(mcam),
			CAFE_SMBUS_TIMEOUT);

	spin_lock_irqsave(&mcam->dev_lock, flags);
	rval = mcam_reg_पढ़ो(mcam, REG_TWSIC1);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);

	अगर (rval & TWSIC1_WSTAT) अणु
		cam_err(cam, "SMBUS write (%02x/%02x/%02x) timed out\n", addr,
				command, value);
		वापस -EIO;
	पूर्ण
	अगर (rval & TWSIC1_ERROR) अणु
		cam_err(cam, "SMBUS write (%02x/%02x/%02x) error\n", addr,
				command, value);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण



अटल पूर्णांक cafe_smbus_पढ़ो_करोne(काष्ठा mcam_camera *mcam)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक c1;

	/*
	 * We must delay after the पूर्णांकerrupt, or the controller माला_लो confused
	 * and never करोes give us good status.  Fortunately, we करोn't करो this
	 * often.
	 */
	udelay(20);
	spin_lock_irqsave(&mcam->dev_lock, flags);
	c1 = mcam_reg_पढ़ो(mcam, REG_TWSIC1);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);
	वापस c1 & (TWSIC1_RVALID|TWSIC1_ERROR);
पूर्ण



अटल पूर्णांक cafe_smbus_पढ़ो_data(काष्ठा cafe_camera *cam,
		u16 addr, u8 command, u8 *value)
अणु
	अचिन्हित पूर्णांक rval;
	अचिन्हित दीर्घ flags;
	काष्ठा mcam_camera *mcam = &cam->mcam;

	spin_lock_irqsave(&mcam->dev_lock, flags);
	rval = TWSIC0_EN | ((addr << TWSIC0_SID_SHIFT) & TWSIC0_SID);
	rval |= TWSIC0_OVMAGIC; /* Make OV sensors work */
	/*
	 * Marvel sez set clkभाग to all 1's क्रम now.
	 */
	rval |= TWSIC0_CLKDIV;
	mcam_reg_ग_लिखो(mcam, REG_TWSIC0, rval);
	(व्योम) mcam_reg_पढ़ो(mcam, REG_TWSIC1); /* क्रमce ग_लिखो */
	rval = TWSIC1_READ | ((command << TWSIC1_ADDR_SHIFT) & TWSIC1_ADDR);
	mcam_reg_ग_लिखो(mcam, REG_TWSIC1, rval);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);

	रुको_event_समयout(cam->smbus_रुको,
			cafe_smbus_पढ़ो_करोne(mcam), CAFE_SMBUS_TIMEOUT);
	spin_lock_irqsave(&mcam->dev_lock, flags);
	rval = mcam_reg_पढ़ो(mcam, REG_TWSIC1);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);

	अगर (rval & TWSIC1_ERROR) अणु
		cam_err(cam, "SMBUS read (%02x/%02x) error\n", addr, command);
		वापस -EIO;
	पूर्ण
	अगर (!(rval & TWSIC1_RVALID)) अणु
		cam_err(cam, "SMBUS read (%02x/%02x) timed out\n", addr,
				command);
		वापस -EIO;
	पूर्ण
	*value = rval & 0xff;
	वापस 0;
पूर्ण

/*
 * Perक्रमm a transfer over SMBUS.  This thing is called under
 * the i2c bus lock, so we shouldn't race with ourselves...
 */
अटल पूर्णांक cafe_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr,
		अचिन्हित लघु flags, अक्षर rw, u8 command,
		पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा cafe_camera *cam = i2c_get_adapdata(adapter);
	पूर्णांक ret = -EINVAL;

	/*
	 * This पूर्णांकerface would appear to only करो byte data ops.  OK
	 * it can करो word too, but the cam chip has no use क्रम that.
	 */
	अगर (size != I2C_SMBUS_BYTE_DATA) अणु
		cam_err(cam, "funky xfer size %d\n", size);
		वापस -EINVAL;
	पूर्ण

	अगर (rw == I2C_SMBUS_WRITE)
		ret = cafe_smbus_ग_लिखो_data(cam, addr, command, data->byte);
	अन्यथा अगर (rw == I2C_SMBUS_READ)
		ret = cafe_smbus_पढ़ो_data(cam, addr, command, &data->byte);
	वापस ret;
पूर्ण


अटल व्योम cafe_smbus_enable_irq(काष्ठा cafe_camera *cam)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cam->mcam.dev_lock, flags);
	mcam_reg_set_bit(&cam->mcam, REG_IRQMASK, TWSIIRQS);
	spin_unlock_irqrestore(&cam->mcam.dev_lock, flags);
पूर्ण

अटल u32 cafe_smbus_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_READ_BYTE_DATA  |
	       I2C_FUNC_SMBUS_WRITE_BYTE_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm cafe_smbus_algo = अणु
	.smbus_xfer = cafe_smbus_xfer,
	.functionality = cafe_smbus_func
पूर्ण;

अटल पूर्णांक cafe_smbus_setup(काष्ठा cafe_camera *cam)
अणु
	काष्ठा i2c_adapter *adap;
	पूर्णांक ret;

	adap = kzalloc(माप(*adap), GFP_KERNEL);
	अगर (adap == शून्य)
		वापस -ENOMEM;
	adap->owner = THIS_MODULE;
	adap->algo = &cafe_smbus_algo;
	strscpy(adap->name, "cafe_ccic", माप(adap->name));
	adap->dev.parent = &cam->pdev->dev;
	i2c_set_adapdata(adap, cam);
	ret = i2c_add_adapter(adap);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Unable to register cafe i2c adapter\n");
		kमुक्त(adap);
		वापस ret;
	पूर्ण

	cam->i2c_adapter = adap;
	cafe_smbus_enable_irq(cam);
	वापस 0;
पूर्ण

अटल व्योम cafe_smbus_shutकरोwn(काष्ठा cafe_camera *cam)
अणु
	i2c_del_adapter(cam->i2c_adapter);
	kमुक्त(cam->i2c_adapter);
पूर्ण


/*
 * Controller-level stuff
 */

अटल व्योम cafe_ctlr_init(काष्ठा mcam_camera *mcam)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mcam->dev_lock, flags);
	/*
	 * Added magic to bring up the hardware on the B-Test board
	 */
	mcam_reg_ग_लिखो(mcam, 0x3038, 0x8);
	mcam_reg_ग_लिखो(mcam, 0x315c, 0x80008);
	/*
	 * Go through the dance needed to wake the device up.
	 * Note that these रेजिस्टरs are global and shared
	 * with the न_अंकD and SD devices.  Interaction between the
	 * three still needs to be examined.
	 */
	mcam_reg_ग_लिखो(mcam, REG_GL_CSR, GCSR_SRS|GCSR_MRS); /* Needed? */
	mcam_reg_ग_लिखो(mcam, REG_GL_CSR, GCSR_SRC|GCSR_MRC);
	mcam_reg_ग_लिखो(mcam, REG_GL_CSR, GCSR_SRC|GCSR_MRS);
	/*
	 * Here we must रुको a bit क्रम the controller to come around.
	 */
	spin_unlock_irqrestore(&mcam->dev_lock, flags);
	msleep(5);
	spin_lock_irqsave(&mcam->dev_lock, flags);

	mcam_reg_ग_लिखो(mcam, REG_GL_CSR, GCSR_CCIC_EN|GCSR_SRC|GCSR_MRC);
	mcam_reg_set_bit(mcam, REG_GL_IMASK, GIMSK_CCIC_EN);
	/*
	 * Mask all पूर्णांकerrupts.
	 */
	mcam_reg_ग_लिखो(mcam, REG_IRQMASK, 0);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);
पूर्ण


अटल पूर्णांक cafe_ctlr_घातer_up(काष्ठा mcam_camera *mcam)
अणु
	/*
	 * Part one of the sensor dance: turn the global
	 * GPIO संकेत on.
	 */
	mcam_reg_ग_लिखो(mcam, REG_GL_FCR, GFCR_GPIO_ON);
	mcam_reg_ग_लिखो(mcam, REG_GL_GPIOR, GGPIO_OUT|GGPIO_VAL);
	/*
	 * Put the sensor पूर्णांकo operational mode (assumes OLPC-style
	 * wiring).  Control 0 is reset - set to 1 to operate.
	 * Control 1 is घातer करोwn, set to 0 to operate.
	 */
	mcam_reg_ग_लिखो(mcam, REG_GPR, GPR_C1EN|GPR_C0EN); /* pwr up, reset */
	mcam_reg_ग_लिखो(mcam, REG_GPR, GPR_C1EN|GPR_C0EN|GPR_C0);

	वापस 0;
पूर्ण

अटल व्योम cafe_ctlr_घातer_करोwn(काष्ठा mcam_camera *mcam)
अणु
	mcam_reg_ग_लिखो(mcam, REG_GPR, GPR_C1EN|GPR_C0EN|GPR_C1);
	mcam_reg_ग_लिखो(mcam, REG_GL_FCR, GFCR_GPIO_ON);
	mcam_reg_ग_लिखो(mcam, REG_GL_GPIOR, GGPIO_OUT);
पूर्ण



/*
 * The platक्रमm पूर्णांकerrupt handler.
 */
अटल irqवापस_t cafe_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cafe_camera *cam = data;
	काष्ठा mcam_camera *mcam = &cam->mcam;
	अचिन्हित पूर्णांक irqs, handled;

	spin_lock(&mcam->dev_lock);
	irqs = mcam_reg_पढ़ो(mcam, REG_IRQSTAT);
	handled = cam->रेजिस्टरed && mccic_irq(mcam, irqs);
	अगर (irqs & TWSIIRQS) अणु
		mcam_reg_ग_लिखो(mcam, REG_IRQSTAT, TWSIIRQS);
		wake_up(&cam->smbus_रुको);
		handled = 1;
	पूर्ण
	spin_unlock(&mcam->dev_lock);
	वापस IRQ_RETVAL(handled);
पूर्ण

/* -------------------------------------------------------------------------- */

अटल काष्ठा ov7670_config sensor_cfg = अणु
	/*
	 * Exclude QCIF mode, because it only captures a tiny portion
	 * of the sensor FOV
	 */
	.min_width = 320,
	.min_height = 240,

	/*
	 * Set the घड़ी speed क्रम the XO 1; I करोn't believe this
	 * driver has ever run anywhere अन्यथा.
	 */
	.घड़ी_speed = 45,
	.use_smbus = 1,
पूर्ण;

अटल काष्ठा i2c_board_info ov7670_info = अणु
	.type = "ov7670",
	.addr = 0x42 >> 1,
	.platक्रमm_data = &sensor_cfg,
पूर्ण;

/* -------------------------------------------------------------------------- */
/*
 * PCI पूर्णांकerface stuff.
 */

अटल पूर्णांक cafe_pci_probe(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा cafe_camera *cam;
	काष्ठा mcam_camera *mcam;
	काष्ठा v4l2_async_subdev *asd;

	/*
	 * Start putting together one of our big camera काष्ठाures.
	 */
	ret = -ENOMEM;
	cam = kzalloc(माप(काष्ठा cafe_camera), GFP_KERNEL);
	अगर (cam == शून्य)
		जाओ out;
	pci_set_drvdata(pdev, cam);
	cam->pdev = pdev;
	mcam = &cam->mcam;
	mcam->chip_id = MCAM_CAFE;
	spin_lock_init(&mcam->dev_lock);
	init_रुकोqueue_head(&cam->smbus_रुको);
	mcam->plat_घातer_up = cafe_ctlr_घातer_up;
	mcam->plat_घातer_करोwn = cafe_ctlr_घातer_करोwn;
	mcam->dev = &pdev->dev;
	snम_लिखो(mcam->bus_info, माप(mcam->bus_info), "PCI:%s", pci_name(pdev));
	/*
	 * Vदो_स्मृति mode क्रम buffers is traditional with this driver.
	 * We *might* be able to run DMA_contig, especially on a प्रणाली
	 * with CMA in it.
	 */
	mcam->buffer_mode = B_vदो_स्मृति;
	/*
	 * Get set up on the PCI bus.
	 */
	ret = pci_enable_device(pdev);
	अगर (ret)
		जाओ out_मुक्त;
	pci_set_master(pdev);

	ret = -EIO;
	mcam->regs = pci_iomap(pdev, 0, 0);
	अगर (!mcam->regs) अणु
		prपूर्णांकk(KERN_ERR "Unable to ioremap cafe-ccic regs\n");
		जाओ out_disable;
	पूर्ण
	mcam->regs_size = pci_resource_len(pdev, 0);
	ret = request_irq(pdev->irq, cafe_irq, IRQF_SHARED, "cafe-ccic", cam);
	अगर (ret)
		जाओ out_iounmap;

	/*
	 * Initialize the controller.
	 */
	cafe_ctlr_init(mcam);

	/*
	 * Set up I2C/SMBUS communications.  We have to drop the mutex here
	 * because the sensor could attach in this call chain, leading to
	 * unsightly deadlocks.
	 */
	ret = cafe_smbus_setup(cam);
	अगर (ret)
		जाओ out_pकरोwn;

	v4l2_async_notअगरier_init(&mcam->notअगरier);

	asd = v4l2_async_notअगरier_add_i2c_subdev(&mcam->notअगरier,
					i2c_adapter_id(cam->i2c_adapter),
					ov7670_info.addr,
					काष्ठा v4l2_async_subdev);
	अगर (IS_ERR(asd)) अणु
		ret = PTR_ERR(asd);
		जाओ out_smbus_shutकरोwn;
	पूर्ण

	ret = mccic_रेजिस्टर(mcam);
	अगर (ret)
		जाओ out_smbus_shutकरोwn;

	clkdev_create(mcam->mclk, "xclk", "%d-%04x",
		i2c_adapter_id(cam->i2c_adapter), ov7670_info.addr);

	अगर (!IS_ERR(i2c_new_client_device(cam->i2c_adapter, &ov7670_info))) अणु
		cam->रेजिस्टरed = 1;
		वापस 0;
	पूर्ण

	mccic_shutकरोwn(mcam);
out_smbus_shutकरोwn:
	cafe_smbus_shutकरोwn(cam);
out_pकरोwn:
	cafe_ctlr_घातer_करोwn(mcam);
	मुक्त_irq(pdev->irq, cam);
out_iounmap:
	pci_iounmap(pdev, mcam->regs);
out_disable:
	pci_disable_device(pdev);
out_मुक्त:
	kमुक्त(cam);
out:
	वापस ret;
पूर्ण


/*
 * Shut करोwn an initialized device
 */
अटल व्योम cafe_shutकरोwn(काष्ठा cafe_camera *cam)
अणु
	mccic_shutकरोwn(&cam->mcam);
	cafe_smbus_shutकरोwn(cam);
	मुक्त_irq(cam->pdev->irq, cam);
	pci_iounmap(cam->pdev, cam->mcam.regs);
पूर्ण


अटल व्योम cafe_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cafe_camera *cam = pci_get_drvdata(pdev);

	अगर (cam == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "pci_remove on unknown pdev %p\n", pdev);
		वापस;
	पूर्ण
	cafe_shutकरोwn(cam);
	kमुक्त(cam);
पूर्ण


/*
 * Basic घातer management.
 */
अटल पूर्णांक __maybe_unused cafe_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा cafe_camera *cam = dev_get_drvdata(dev);

	mccic_suspend(&cam->mcam);
	वापस 0;
पूर्ण


अटल पूर्णांक __maybe_unused cafe_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा cafe_camera *cam = dev_get_drvdata(dev);

	cafe_ctlr_init(&cam->mcam);
	वापस mccic_resume(&cam->mcam);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cafe_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL,
		     PCI_DEVICE_ID_MARVELL_88ALP01_CCIC) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, cafe_ids);

अटल SIMPLE_DEV_PM_OPS(cafe_pci_pm_ops, cafe_pci_suspend, cafe_pci_resume);

अटल काष्ठा pci_driver cafe_pci_driver = अणु
	.name = "cafe1000-ccic",
	.id_table = cafe_ids,
	.probe = cafe_pci_probe,
	.हटाओ = cafe_pci_हटाओ,
	.driver.pm = &cafe_pci_pm_ops,
पूर्ण;




अटल पूर्णांक __init cafe_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_NOTICE "Marvell M88ALP01 'CAFE' Camera Controller version %d\n",
			CAFE_VERSION);
	ret = pci_रेजिस्टर_driver(&cafe_pci_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Unable to register cafe_ccic driver\n");
		जाओ out;
	पूर्ण
	ret = 0;

out:
	वापस ret;
पूर्ण


अटल व्योम __निकास cafe_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cafe_pci_driver);
पूर्ण

module_init(cafe_init);
module_निकास(cafe_निकास);
