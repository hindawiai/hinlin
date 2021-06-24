<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2017 IBM Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/log2.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/regmap.h>

#समावेश <linux/aspeed-lpc-ctrl.h>

#घोषणा DEVICE_NAME	"aspeed-lpc-ctrl"

#घोषणा HICR5 0x80
#घोषणा HICR5_ENL2H	BIT(8)
#घोषणा HICR5_ENFWH	BIT(10)

#घोषणा HICR6 0x84
#घोषणा SW_FWH2AHB	BIT(17)

#घोषणा HICR7 0x88
#घोषणा HICR8 0x8c

काष्ठा aspeed_lpc_ctrl अणु
	काष्ठा miscdevice	miscdev;
	काष्ठा regmap		*regmap;
	काष्ठा clk		*clk;
	phys_addr_t		mem_base;
	resource_माप_प्रकार		mem_size;
	u32			pnor_size;
	u32			pnor_base;
	bool			fwh2ahb;
पूर्ण;

अटल काष्ठा aspeed_lpc_ctrl *file_aspeed_lpc_ctrl(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data, काष्ठा aspeed_lpc_ctrl,
			miscdev);
पूर्ण

अटल पूर्णांक aspeed_lpc_ctrl_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा aspeed_lpc_ctrl *lpc_ctrl = file_aspeed_lpc_ctrl(file);
	अचिन्हित दीर्घ vsize = vma->vm_end - vma->vm_start;
	pgprot_t prot = vma->vm_page_prot;

	अगर (vma->vm_pgoff + vsize > lpc_ctrl->mem_base + lpc_ctrl->mem_size)
		वापस -EINVAL;

	/* ast2400/2500 AHB accesses are not cache coherent */
	prot = pgprot_noncached(prot);

	अगर (remap_pfn_range(vma, vma->vm_start,
		(lpc_ctrl->mem_base >> PAGE_SHIFT) + vma->vm_pgoff,
		vsize, prot))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल दीर्घ aspeed_lpc_ctrl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ param)
अणु
	काष्ठा aspeed_lpc_ctrl *lpc_ctrl = file_aspeed_lpc_ctrl(file);
	काष्ठा device *dev = file->निजी_data;
	व्योम __user *p = (व्योम __user *)param;
	काष्ठा aspeed_lpc_ctrl_mapping map;
	u32 addr;
	u32 size;
	दीर्घ rc;

	अगर (copy_from_user(&map, p, माप(map)))
		वापस -EFAULT;

	अगर (map.flags != 0)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल ASPEED_LPC_CTRL_IOCTL_GET_SIZE:
		/* The flash winकरोws करोn't report their size */
		अगर (map.winकरोw_type != ASPEED_LPC_CTRL_WINDOW_MEMORY)
			वापस -EINVAL;

		/* Support more than one winकरोw id in the future */
		अगर (map.winकरोw_id != 0)
			वापस -EINVAL;

		/* If memory-region is not described in device tree */
		अगर (!lpc_ctrl->mem_size) अणु
			dev_dbg(dev, "Didn't find reserved memory\n");
			वापस -ENXIO;
		पूर्ण

		map.size = lpc_ctrl->mem_size;

		वापस copy_to_user(p, &map, माप(map)) ? -EFAULT : 0;
	हाल ASPEED_LPC_CTRL_IOCTL_MAP:

		/*
		 * The top half of HICR7 is the MSB of the BMC address of the
		 * mapping.
		 * The bottom half of HICR7 is the MSB of the HOST LPC
		 * firmware space address of the mapping.
		 *
		 * The 1 bits in the top of half of HICR8 represent the bits
		 * (in the requested address) that should be ignored and
		 * replaced with those from the top half of HICR7.
		 * The 1 bits in the bottom half of HICR8 represent the bits
		 * (in the requested address) that should be kept and pass
		 * पूर्णांकo the BMC address space.
		 */

		/*
		 * It करोesn't make sense to talk about a size or offset with
		 * low 16 bits set. Both HICR7 and HICR8 talk about the top 16
		 * bits of addresses and sizes.
		 */

		अगर ((map.size & 0x0000ffff) || (map.offset & 0x0000ffff))
			वापस -EINVAL;

		/*
		 * Because of the way the masks work in HICR8 offset has to
		 * be a multiple of size.
		 */
		अगर (map.offset & (map.size - 1))
			वापस -EINVAL;

		अगर (map.winकरोw_type == ASPEED_LPC_CTRL_WINDOW_FLASH) अणु
			अगर (!lpc_ctrl->pnor_size) अणु
				dev_dbg(dev, "Didn't find host pnor flash\n");
				वापस -ENXIO;
			पूर्ण
			addr = lpc_ctrl->pnor_base;
			size = lpc_ctrl->pnor_size;
		पूर्ण अन्यथा अगर (map.winकरोw_type == ASPEED_LPC_CTRL_WINDOW_MEMORY) अणु
			/* If memory-region is not described in device tree */
			अगर (!lpc_ctrl->mem_size) अणु
				dev_dbg(dev, "Didn't find reserved memory\n");
				वापस -ENXIO;
			पूर्ण
			addr = lpc_ctrl->mem_base;
			size = lpc_ctrl->mem_size;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		/* Check overflow first! */
		अगर (map.offset + map.size < map.offset ||
			map.offset + map.size > size)
			वापस -EINVAL;

		अगर (map.size == 0 || map.size > size)
			वापस -EINVAL;

		addr += map.offset;

		/*
		 * addr (host lpc address) is safe regardless of values. This
		 * simply changes the address the host has to request on its
		 * side of the LPC bus. This cannot impact the hosts own
		 * memory space by surprise as LPC specअगरic accessors are
		 * required. The only strange thing that could be करोne is
		 * setting the lower 16 bits but the shअगरt takes care of that.
		 */

		rc = regmap_ग_लिखो(lpc_ctrl->regmap, HICR7,
				(addr | (map.addr >> 16)));
		अगर (rc)
			वापस rc;

		rc = regmap_ग_लिखो(lpc_ctrl->regmap, HICR8,
				(~(map.size - 1)) | ((map.size >> 16) - 1));
		अगर (rc)
			वापस rc;

		/*
		 * Switch to FWH2AHB mode, AST2600 only.
		 *
		 * The other bits in this रेजिस्टर are पूर्णांकerrupt status bits
		 * that are cleared by writing 1. As we करोn't want to clear
		 * them, set only the bit of पूर्णांकerest.
		 */
		अगर (lpc_ctrl->fwh2ahb)
			regmap_ग_लिखो(lpc_ctrl->regmap, HICR6, SW_FWH2AHB);

		/*
		 * Enable LPC FHW cycles. This is required क्रम the host to
		 * access the regions specअगरied.
		 */
		वापस regmap_update_bits(lpc_ctrl->regmap, HICR5,
				HICR5_ENFWH | HICR5_ENL2H,
				HICR5_ENFWH | HICR5_ENL2H);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा file_operations aspeed_lpc_ctrl_fops = अणु
	.owner		= THIS_MODULE,
	.mmap		= aspeed_lpc_ctrl_mmap,
	.unlocked_ioctl	= aspeed_lpc_ctrl_ioctl,
पूर्ण;

अटल पूर्णांक aspeed_lpc_ctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_lpc_ctrl *lpc_ctrl;
	काष्ठा device_node *node;
	काष्ठा resource resm;
	काष्ठा device *dev;
	काष्ठा device_node *np;
	पूर्णांक rc;

	dev = &pdev->dev;

	lpc_ctrl = devm_kzalloc(dev, माप(*lpc_ctrl), GFP_KERNEL);
	अगर (!lpc_ctrl)
		वापस -ENOMEM;

	/* If flash is described in device tree then store */
	node = of_parse_phandle(dev->of_node, "flash", 0);
	अगर (!node) अणु
		dev_dbg(dev, "Didn't find host pnor flash node\n");
	पूर्ण अन्यथा अणु
		rc = of_address_to_resource(node, 1, &resm);
		of_node_put(node);
		अगर (rc) अणु
			dev_err(dev, "Couldn't address to resource for flash\n");
			वापस rc;
		पूर्ण

		lpc_ctrl->pnor_size = resource_size(&resm);
		lpc_ctrl->pnor_base = resm.start;
	पूर्ण


	dev_set_drvdata(&pdev->dev, lpc_ctrl);

	/* If memory-region is described in device tree then store */
	node = of_parse_phandle(dev->of_node, "memory-region", 0);
	अगर (!node) अणु
		dev_dbg(dev, "Didn't find reserved memory\n");
	पूर्ण अन्यथा अणु
		rc = of_address_to_resource(node, 0, &resm);
		of_node_put(node);
		अगर (rc) अणु
			dev_err(dev, "Couldn't address to resource for reserved memory\n");
			वापस -ENXIO;
		पूर्ण

		lpc_ctrl->mem_size = resource_size(&resm);
		lpc_ctrl->mem_base = resm.start;

		अगर (!is_घातer_of_2(lpc_ctrl->mem_size)) अणु
			dev_err(dev, "Reserved memory size must be a power of 2, got %u\n",
			       (अचिन्हित पूर्णांक)lpc_ctrl->mem_size);
			वापस -EINVAL;
		पूर्ण

		अगर (!IS_ALIGNED(lpc_ctrl->mem_base, lpc_ctrl->mem_size)) अणु
			dev_err(dev, "Reserved memory must be naturally aligned for size %u\n",
			       (अचिन्हित पूर्णांक)lpc_ctrl->mem_size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	np = pdev->dev.parent->of_node;
	अगर (!of_device_is_compatible(np, "aspeed,ast2400-lpc-v2") &&
	    !of_device_is_compatible(np, "aspeed,ast2500-lpc-v2") &&
	    !of_device_is_compatible(np, "aspeed,ast2600-lpc-v2")) अणु
		dev_err(dev, "unsupported LPC device binding\n");
		वापस -ENODEV;
	पूर्ण

	lpc_ctrl->regmap = syscon_node_to_regmap(np);
	अगर (IS_ERR(lpc_ctrl->regmap)) अणु
		dev_err(dev, "Couldn't get regmap\n");
		वापस -ENODEV;
	पूर्ण

	lpc_ctrl->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(lpc_ctrl->clk)) अणु
		dev_err(dev, "couldn't get clock\n");
		वापस PTR_ERR(lpc_ctrl->clk);
	पूर्ण
	rc = clk_prepare_enable(lpc_ctrl->clk);
	अगर (rc) अणु
		dev_err(dev, "couldn't enable clock\n");
		वापस rc;
	पूर्ण

	अगर (of_device_is_compatible(dev->of_node, "aspeed,ast2600-lpc-ctrl"))
		lpc_ctrl->fwh2ahb = true;

	lpc_ctrl->miscdev.minor = MISC_DYNAMIC_MINOR;
	lpc_ctrl->miscdev.name = DEVICE_NAME;
	lpc_ctrl->miscdev.fops = &aspeed_lpc_ctrl_fops;
	lpc_ctrl->miscdev.parent = dev;
	rc = misc_रेजिस्टर(&lpc_ctrl->miscdev);
	अगर (rc) अणु
		dev_err(dev, "Unable to register device\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	clk_disable_unprepare(lpc_ctrl->clk);
	वापस rc;
पूर्ण

अटल पूर्णांक aspeed_lpc_ctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_lpc_ctrl *lpc_ctrl = dev_get_drvdata(&pdev->dev);

	misc_deरेजिस्टर(&lpc_ctrl->miscdev);
	clk_disable_unprepare(lpc_ctrl->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aspeed_lpc_ctrl_match[] = अणु
	अणु .compatible = "aspeed,ast2400-lpc-ctrl" पूर्ण,
	अणु .compatible = "aspeed,ast2500-lpc-ctrl" पूर्ण,
	अणु .compatible = "aspeed,ast2600-lpc-ctrl" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver aspeed_lpc_ctrl_driver = अणु
	.driver = अणु
		.name		= DEVICE_NAME,
		.of_match_table = aspeed_lpc_ctrl_match,
	पूर्ण,
	.probe = aspeed_lpc_ctrl_probe,
	.हटाओ = aspeed_lpc_ctrl_हटाओ,
पूर्ण;

module_platक्रमm_driver(aspeed_lpc_ctrl_driver);

MODULE_DEVICE_TABLE(of, aspeed_lpc_ctrl_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cyril Bur <cyrilbur@gmail.com>");
MODULE_DESCRIPTION("Control for ASPEED LPC HOST to BMC mappings");
