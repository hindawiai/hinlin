<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* sun_uflash.c - Driver क्रम user-programmable flash on
 *                Sun Microप्रणालीs SME boardsets.
 *
 * This driver करोes NOT provide access to the OBP-flash क्रम
 * safety reasons-- use <linux>/drivers/sbus/अक्षर/flash.c instead.
 *
 * Copyright (c) 2001 Eric Brower (ebrower@usa.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/prom.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>

#घोषणा UFLASH_OBPNAME	"flashprom"
#घोषणा DRIVER_NAME	"sun_uflash"
#घोषणा PFX		DRIVER_NAME ": "

#घोषणा UFLASH_WINDOW_SIZE	0x200000
#घोषणा UFLASH_BUSWIDTH		1			/* EBus is 8-bit */

MODULE_AUTHOR("Eric Brower <ebrower@usa.net>");
MODULE_DESCRIPTION("User-programmable flash device on Sun Microsystems boardsets");
MODULE_LICENSE("GPL");
MODULE_VERSION("2.1");

काष्ठा uflash_dev अणु
	स्थिर अक्षर		*name;	/* device name */
	काष्ठा map_info 	map;	/* mtd map info */
	काष्ठा mtd_info		*mtd;	/* mtd info */
पूर्ण;

काष्ठा map_info uflash_map_templ = अणु
	.name =		"SUNW,???-????",
	.size =		UFLASH_WINDOW_SIZE,
	.bankwidth =	UFLASH_BUSWIDTH,
पूर्ण;

पूर्णांक uflash_devinit(काष्ठा platक्रमm_device *op, काष्ठा device_node *dp)
अणु
	काष्ठा uflash_dev *up;

	अगर (op->resource[1].flags) अणु
		/* Non-CFI userflash device-- once I find one we
		 * can work on supporting it.
		 */
		prपूर्णांकk(KERN_ERR PFX "Unsupported device at %pOF, 0x%llx\n",
		       dp, (अचिन्हित दीर्घ दीर्घ)op->resource[0].start);

		वापस -ENODEV;
	पूर्ण

	up = kzalloc(माप(काष्ठा uflash_dev), GFP_KERNEL);
	अगर (!up) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate struct uflash_dev\n");
		वापस -ENOMEM;
	पूर्ण

	/* copy शेषs and tweak parameters */
	स_नकल(&up->map, &uflash_map_templ, माप(uflash_map_templ));

	up->map.size = resource_size(&op->resource[0]);

	up->name = of_get_property(dp, "model", शून्य);
	अगर (up->name && 0 < म_माप(up->name))
		up->map.name = up->name;

	up->map.phys = op->resource[0].start;

	up->map.virt = of_ioremap(&op->resource[0], 0, up->map.size,
				  DRIVER_NAME);
	अगर (!up->map.virt) अणु
		prपूर्णांकk(KERN_ERR PFX "Failed to map device.\n");
		kमुक्त(up);

		वापस -EINVAL;
	पूर्ण

	simple_map_init(&up->map);

	/* MTD registration */
	up->mtd = करो_map_probe("cfi_probe", &up->map);
	अगर (!up->mtd) अणु
		of_iounmap(&op->resource[0], up->map.virt, up->map.size);
		kमुक्त(up);

		वापस -ENXIO;
	पूर्ण

	up->mtd->owner = THIS_MODULE;

	mtd_device_रेजिस्टर(up->mtd, शून्य, 0);

	dev_set_drvdata(&op->dev, up);

	वापस 0;
पूर्ण

अटल पूर्णांक uflash_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;

	/* Flashprom must have the "user" property in order to
	 * be used by this driver.
	 */
	अगर (!of_find_property(dp, "user", शून्य))
		वापस -ENODEV;

	वापस uflash_devinit(op, dp);
पूर्ण

अटल पूर्णांक uflash_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा uflash_dev *up = dev_get_drvdata(&op->dev);

	अगर (up->mtd) अणु
		mtd_device_unरेजिस्टर(up->mtd);
		map_destroy(up->mtd);
	पूर्ण
	अगर (up->map.virt) अणु
		of_iounmap(&op->resource[0], up->map.virt, up->map.size);
		up->map.virt = शून्य;
	पूर्ण

	kमुक्त(up);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id uflash_match[] = अणु
	अणु
		.name = UFLASH_OBPNAME,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, uflash_match);

अटल काष्ठा platक्रमm_driver uflash_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = uflash_match,
	पूर्ण,
	.probe		= uflash_probe,
	.हटाओ		= uflash_हटाओ,
पूर्ण;

module_platक्रमm_driver(uflash_driver);
