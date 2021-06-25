<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  include/linux/mmc/sdio_func.h
 *
 *  Copyright 2007-2008 Pierre Ossman
 */

#अगर_अघोषित LINUX_MMC_SDIO_FUNC_H
#घोषणा LINUX_MMC_SDIO_FUNC_H

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <linux/mmc/pm.h>

काष्ठा mmc_card;
काष्ठा sdio_func;

प्रकार व्योम (sdio_irq_handler_t)(काष्ठा sdio_func *);

/*
 * SDIO function CIS tuple (unknown to the core)
 */
काष्ठा sdio_func_tuple अणु
	काष्ठा sdio_func_tuple *next;
	अचिन्हित अक्षर code;
	अचिन्हित अक्षर size;
	अचिन्हित अक्षर data[];
पूर्ण;

/*
 * SDIO function devices
 */
काष्ठा sdio_func अणु
	काष्ठा mmc_card		*card;		/* the card this device beदीर्घs to */
	काष्ठा device		dev;		/* the device */
	sdio_irq_handler_t	*irq_handler;	/* IRQ callback */
	अचिन्हित पूर्णांक		num;		/* function number */

	अचिन्हित अक्षर		class;		/* standard पूर्णांकerface class */
	अचिन्हित लघु		venकरोr;		/* venकरोr id */
	अचिन्हित लघु		device;		/* device id */

	अचिन्हित		max_blksize;	/* maximum block size */
	अचिन्हित		cur_blksize;	/* current block size */

	अचिन्हित		enable_समयout;	/* max enable समयout in msec */

	अचिन्हित पूर्णांक		state;		/* function state */
#घोषणा SDIO_STATE_PRESENT	(1<<0)		/* present in sysfs */

	u8			*पंचांगpbuf;	/* DMA:able scratch buffer */

	u8			major_rev;	/* major revision number */
	u8			minor_rev;	/* minor revision number */
	अचिन्हित		num_info;	/* number of info strings */
	स्थिर अक्षर		**info;		/* info strings */

	काष्ठा sdio_func_tuple *tuples;
पूर्ण;

#घोषणा sdio_func_present(f)	((f)->state & SDIO_STATE_PRESENT)

#घोषणा sdio_func_set_present(f) ((f)->state |= SDIO_STATE_PRESENT)

#घोषणा sdio_func_id(f)		(dev_name(&(f)->dev))

#घोषणा sdio_get_drvdata(f)	dev_get_drvdata(&(f)->dev)
#घोषणा sdio_set_drvdata(f,d)	dev_set_drvdata(&(f)->dev, d)
#घोषणा dev_to_sdio_func(d)	container_of(d, काष्ठा sdio_func, dev)

/*
 * SDIO function device driver
 */
काष्ठा sdio_driver अणु
	अक्षर *name;
	स्थिर काष्ठा sdio_device_id *id_table;

	पूर्णांक (*probe)(काष्ठा sdio_func *, स्थिर काष्ठा sdio_device_id *);
	व्योम (*हटाओ)(काष्ठा sdio_func *);

	काष्ठा device_driver drv;
पूर्ण;

/**
 * SDIO_DEVICE - macro used to describe a specअगरic SDIO device
 * @vend: the 16 bit manufacturer code
 * @dev: the 16 bit function id
 *
 * This macro is used to create a काष्ठा sdio_device_id that matches a
 * specअगरic device. The class field will be set to SDIO_ANY_ID.
 */
#घोषणा SDIO_DEVICE(vend,dev) \
	.class = SDIO_ANY_ID, \
	.venकरोr = (vend), .device = (dev)

/**
 * SDIO_DEVICE_CLASS - macro used to describe a specअगरic SDIO device class
 * @dev_class: the 8 bit standard पूर्णांकerface code
 *
 * This macro is used to create a काष्ठा sdio_device_id that matches a
 * specअगरic standard SDIO function type.  The venकरोr and device fields will
 * be set to SDIO_ANY_ID.
 */
#घोषणा SDIO_DEVICE_CLASS(dev_class) \
	.class = (dev_class), \
	.venकरोr = SDIO_ANY_ID, .device = SDIO_ANY_ID

बाह्य पूर्णांक sdio_रेजिस्टर_driver(काष्ठा sdio_driver *);
बाह्य व्योम sdio_unरेजिस्टर_driver(काष्ठा sdio_driver *);

/**
 * module_sdio_driver() - Helper macro क्रम रेजिस्टरing a SDIO driver
 * @__sdio_driver: sdio_driver काष्ठा
 *
 * Helper macro क्रम SDIO drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_sdio_driver(__sdio_driver) \
	module_driver(__sdio_driver, sdio_रेजिस्टर_driver, \
		      sdio_unरेजिस्टर_driver)

/*
 * SDIO I/O operations
 */
बाह्य व्योम sdio_claim_host(काष्ठा sdio_func *func);
बाह्य व्योम sdio_release_host(काष्ठा sdio_func *func);

बाह्य पूर्णांक sdio_enable_func(काष्ठा sdio_func *func);
बाह्य पूर्णांक sdio_disable_func(काष्ठा sdio_func *func);

बाह्य पूर्णांक sdio_set_block_size(काष्ठा sdio_func *func, अचिन्हित blksz);

बाह्य पूर्णांक sdio_claim_irq(काष्ठा sdio_func *func, sdio_irq_handler_t *handler);
बाह्य पूर्णांक sdio_release_irq(काष्ठा sdio_func *func);

बाह्य अचिन्हित पूर्णांक sdio_align_size(काष्ठा sdio_func *func, अचिन्हित पूर्णांक sz);

बाह्य u8 sdio_पढ़ोb(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr, पूर्णांक *err_ret);
बाह्य u16 sdio_पढ़ोw(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr, पूर्णांक *err_ret);
बाह्य u32 sdio_पढ़ोl(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr, पूर्णांक *err_ret);

बाह्य पूर्णांक sdio_स_नकल_fromio(काष्ठा sdio_func *func, व्योम *dst,
	अचिन्हित पूर्णांक addr, पूर्णांक count);
बाह्य पूर्णांक sdio_पढ़ोsb(काष्ठा sdio_func *func, व्योम *dst,
	अचिन्हित पूर्णांक addr, पूर्णांक count);

बाह्य व्योम sdio_ग_लिखोb(काष्ठा sdio_func *func, u8 b,
	अचिन्हित पूर्णांक addr, पूर्णांक *err_ret);
बाह्य व्योम sdio_ग_लिखोw(काष्ठा sdio_func *func, u16 b,
	अचिन्हित पूर्णांक addr, पूर्णांक *err_ret);
बाह्य व्योम sdio_ग_लिखोl(काष्ठा sdio_func *func, u32 b,
	अचिन्हित पूर्णांक addr, पूर्णांक *err_ret);

बाह्य u8 sdio_ग_लिखोb_पढ़ोb(काष्ठा sdio_func *func, u8 ग_लिखो_byte,
	अचिन्हित पूर्णांक addr, पूर्णांक *err_ret);

बाह्य पूर्णांक sdio_स_नकल_toio(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr,
	व्योम *src, पूर्णांक count);
बाह्य पूर्णांक sdio_ग_लिखोsb(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr,
	व्योम *src, पूर्णांक count);

बाह्य अचिन्हित अक्षर sdio_f0_पढ़ोb(काष्ठा sdio_func *func,
	अचिन्हित पूर्णांक addr, पूर्णांक *err_ret);
बाह्य व्योम sdio_f0_ग_लिखोb(काष्ठा sdio_func *func, अचिन्हित अक्षर b,
	अचिन्हित पूर्णांक addr, पूर्णांक *err_ret);

बाह्य mmc_pm_flag_t sdio_get_host_pm_caps(काष्ठा sdio_func *func);
बाह्य पूर्णांक sdio_set_host_pm_flags(काष्ठा sdio_func *func, mmc_pm_flag_t flags);

बाह्य व्योम sdio_retune_crc_disable(काष्ठा sdio_func *func);
बाह्य व्योम sdio_retune_crc_enable(काष्ठा sdio_func *func);

बाह्य व्योम sdio_retune_hold_now(काष्ठा sdio_func *func);
बाह्य व्योम sdio_retune_release(काष्ठा sdio_func *func);

#पूर्ण_अगर /* LINUX_MMC_SDIO_FUNC_H */
