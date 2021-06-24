<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Flash memory access on SA11x0 based devices
 *
 * (C) 2000 Nicolas Pitre <nico@fluxnic.net>
 */
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/concat.h>

#समावेश <mach/hardware.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/mach/flash.h>

काष्ठा sa_subdev_info अणु
	अक्षर name[16];
	काष्ठा map_info map;
	काष्ठा mtd_info *mtd;
	काष्ठा flash_platक्रमm_data *plat;
पूर्ण;

काष्ठा sa_info अणु
	काष्ठा mtd_info		*mtd;
	पूर्णांक			num_subdev;
	काष्ठा sa_subdev_info	subdev[];
पूर्ण;

अटल DEFINE_SPINLOCK(sa1100_vpp_lock);
अटल पूर्णांक sa1100_vpp_refcnt;
अटल व्योम sa1100_set_vpp(काष्ठा map_info *map, पूर्णांक on)
अणु
	काष्ठा sa_subdev_info *subdev = container_of(map, काष्ठा sa_subdev_info, map);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sa1100_vpp_lock, flags);
	अगर (on) अणु
		अगर (++sa1100_vpp_refcnt == 1)   /* first nested 'on' */
			subdev->plat->set_vpp(1);
	पूर्ण अन्यथा अणु
		अगर (--sa1100_vpp_refcnt == 0)   /* last nested 'off' */
			subdev->plat->set_vpp(0);
	पूर्ण
	spin_unlock_irqrestore(&sa1100_vpp_lock, flags);
पूर्ण

अटल व्योम sa1100_destroy_subdev(काष्ठा sa_subdev_info *subdev)
अणु
	अगर (subdev->mtd)
		map_destroy(subdev->mtd);
	अगर (subdev->map.virt)
		iounmap(subdev->map.virt);
	release_mem_region(subdev->map.phys, subdev->map.size);
पूर्ण

अटल पूर्णांक sa1100_probe_subdev(काष्ठा sa_subdev_info *subdev, काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ phys;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	phys = res->start;
	size = res->end - phys + 1;

	/*
	 * Retrieve the bankwidth from the MSC रेजिस्टरs.
	 * We currently only implement CS0 and CS1 here.
	 */
	चयन (phys) अणु
	शेष:
		prपूर्णांकk(KERN_WARNING "SA1100 flash: unknown base address "
		       "0x%08lx, assuming CS0\n", phys);
		fallthrough;
	हाल SA1100_CS0_PHYS:
		subdev->map.bankwidth = (MSC0 & MSC_RBW) ? 2 : 4;
		अवरोध;

	हाल SA1100_CS1_PHYS:
		subdev->map.bankwidth = ((MSC0 >> 16) & MSC_RBW) ? 2 : 4;
		अवरोध;
	पूर्ण

	अगर (!request_mem_region(phys, size, subdev->name)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (subdev->plat->set_vpp)
		subdev->map.set_vpp = sa1100_set_vpp;

	subdev->map.phys = phys;
	subdev->map.size = size;
	subdev->map.virt = ioremap(phys, size);
	अगर (!subdev->map.virt) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	simple_map_init(&subdev->map);

	/*
	 * Now let's probe क्रम the actual flash.  Do it here since
	 * specअगरic machine settings might have been set above.
	 */
	subdev->mtd = करो_map_probe(subdev->plat->map_name, &subdev->map);
	अगर (subdev->mtd == शून्य) अणु
		ret = -ENXIO;
		जाओ err;
	पूर्ण

	prपूर्णांकk(KERN_INFO "SA1100 flash: CFI device at 0x%08lx, %uMiB, %d-bit\n",
		phys, (अचिन्हित)(subdev->mtd->size >> 20),
		subdev->map.bankwidth * 8);

	वापस 0;

 err:
	sa1100_destroy_subdev(subdev);
 out:
	वापस ret;
पूर्ण

अटल व्योम sa1100_destroy(काष्ठा sa_info *info, काष्ठा flash_platक्रमm_data *plat)
अणु
	पूर्णांक i;

	अगर (info->mtd) अणु
		mtd_device_unरेजिस्टर(info->mtd);
		अगर (info->mtd != info->subdev[0].mtd)
			mtd_concat_destroy(info->mtd);
	पूर्ण

	क्रम (i = info->num_subdev - 1; i >= 0; i--)
		sa1100_destroy_subdev(&info->subdev[i]);
	kमुक्त(info);

	अगर (plat->निकास)
		plat->निकास();
पूर्ण

अटल काष्ठा sa_info *sa1100_setup_mtd(काष्ठा platक्रमm_device *pdev,
					काष्ठा flash_platक्रमm_data *plat)
अणु
	काष्ठा sa_info *info;
	पूर्णांक nr, size, i, ret = 0;

	/*
	 * Count number of devices.
	 */
	क्रम (nr = 0; ; nr++)
		अगर (!platक्रमm_get_resource(pdev, IORESOURCE_MEM, nr))
			अवरोध;

	अगर (nr == 0) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	size = माप(काष्ठा sa_info) + माप(काष्ठा sa_subdev_info) * nr;

	/*
	 * Allocate the map_info काष्ठाs in one go.
	 */
	info = kzalloc(size, GFP_KERNEL);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (plat->init) अणु
		ret = plat->init();
		अगर (ret)
			जाओ err;
	पूर्ण

	/*
	 * Claim and then map the memory regions.
	 */
	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा sa_subdev_info *subdev = &info->subdev[i];
		काष्ठा resource *res;

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!res)
			अवरोध;

		subdev->map.name = subdev->name;
		प्र_लिखो(subdev->name, "%s-%d", plat->name, i);
		subdev->plat = plat;

		ret = sa1100_probe_subdev(subdev, res);
		अगर (ret)
			अवरोध;
	पूर्ण

	info->num_subdev = i;

	/*
	 * ENXIO is special.  It means we didn't find a chip when we probed.
	 */
	अगर (ret != 0 && !(ret == -ENXIO && info->num_subdev > 0))
		जाओ err;

	/*
	 * If we found one device, करोn't bother with concat support.  If
	 * we found multiple devices, use concat अगर we have it available,
	 * otherwise fail.  Either way, it'll be called "sa1100".
	 */
	अगर (info->num_subdev == 1) अणु
		म_नकल(info->subdev[0].name, plat->name);
		info->mtd = info->subdev[0].mtd;
		ret = 0;
	पूर्ण अन्यथा अगर (info->num_subdev > 1) अणु
		काष्ठा mtd_info **cdev;

		cdev = kदो_स्मृति_array(nr, माप(*cdev), GFP_KERNEL);
		अगर (!cdev) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		/*
		 * We detected multiple devices.  Concatenate them together.
		 */
		क्रम (i = 0; i < info->num_subdev; i++)
			cdev[i] = info->subdev[i].mtd;

		info->mtd = mtd_concat_create(cdev, info->num_subdev,
					      plat->name);
		kमुक्त(cdev);
		अगर (info->mtd == शून्य) अणु
			ret = -ENXIO;
			जाओ err;
		पूर्ण
	पूर्ण
	info->mtd->dev.parent = &pdev->dev;

	अगर (ret == 0)
		वापस info;

 err:
	sa1100_destroy(info, plat);
 out:
	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर अक्षर * स्थिर part_probes[] = अणु "cmdlinepart", "RedBoot", शून्य पूर्ण;

अटल पूर्णांक sa1100_mtd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा flash_platक्रमm_data *plat = dev_get_platdata(&pdev->dev);
	काष्ठा sa_info *info;
	पूर्णांक err;

	अगर (!plat)
		वापस -ENODEV;

	info = sa1100_setup_mtd(pdev, plat);
	अगर (IS_ERR(info)) अणु
		err = PTR_ERR(info);
		जाओ out;
	पूर्ण

	/*
	 * Partition selection stuff.
	 */
	mtd_device_parse_रेजिस्टर(info->mtd, part_probes, शून्य, plat->parts,
				  plat->nr_parts);

	platक्रमm_set_drvdata(pdev, info);
	err = 0;

 out:
	वापस err;
पूर्ण

अटल पूर्णांक sa1100_mtd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sa_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा flash_platक्रमm_data *plat = dev_get_platdata(&pdev->dev);

	sa1100_destroy(info, plat);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sa1100_mtd_driver = अणु
	.probe		= sa1100_mtd_probe,
	.हटाओ		= sa1100_mtd_हटाओ,
	.driver		= अणु
		.name	= "sa1100-mtd",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sa1100_mtd_driver);

MODULE_AUTHOR("Nicolas Pitre");
MODULE_DESCRIPTION("SA1100 CFI map driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sa1100-mtd");
