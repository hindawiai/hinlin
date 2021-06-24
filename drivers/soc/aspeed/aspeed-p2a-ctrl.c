<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2019 Google Inc
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * Provides a simple driver to control the ASPEED P2A पूर्णांकerface which allows
 * the host to पढ़ो and ग_लिखो to various regions of the BMC's memory.
 */

#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/aspeed-p2a-ctrl.h>

#घोषणा DEVICE_NAME	"aspeed-p2a-ctrl"

/* SCU2C is a Misc. Control Register. */
#घोषणा SCU2C 0x2c
/* SCU180 is the PCIe Configuration Setting Control Register. */
#घोषणा SCU180 0x180
/* Bit 1 controls the P2A bridge, जबतक bit 0 controls the entire VGA device
 * on the PCI bus.
 */
#घोषणा SCU180_ENP2A BIT(1)

/* The ast2400/2500 both have six ranges. */
#घोषणा P2A_REGION_COUNT 6

काष्ठा region अणु
	u64 min;
	u64 max;
	u32 bit;
पूर्ण;

काष्ठा aspeed_p2a_model_data अणु
	/* min, max, bit */
	काष्ठा region regions[P2A_REGION_COUNT];
पूर्ण;

काष्ठा aspeed_p2a_ctrl अणु
	काष्ठा miscdevice miscdev;
	काष्ठा regmap *regmap;

	स्थिर काष्ठा aspeed_p2a_model_data *config;

	/* Access to these needs to be locked, held via probe, mapping ioctl,
	 * and release, हटाओ.
	 */
	काष्ठा mutex tracking;
	u32 पढ़ोers;
	u32 पढ़ोerग_लिखोrs[P2A_REGION_COUNT];

	phys_addr_t mem_base;
	resource_माप_प्रकार mem_size;
पूर्ण;

काष्ठा aspeed_p2a_user अणु
	काष्ठा file *file;
	काष्ठा aspeed_p2a_ctrl *parent;

	/* The entire memory space is खोलोed क्रम पढ़ोing once the bridge is
	 * enabled, thereक्रमe this needs only to be tracked once per user.
	 * If any user has it खोलो क्रम पढ़ो, the bridge must stay enabled.
	 */
	u32 पढ़ो;

	/* Each entry of the array corresponds to a P2A Region.  If the user
	 * खोलोs क्रम पढ़ो or पढ़ोग_लिखो, the reference goes up here.  On
	 * release, this array is walked and references adjusted accordingly.
	 */
	u32 पढ़ोग_लिखो[P2A_REGION_COUNT];
पूर्ण;

अटल व्योम aspeed_p2a_enable_bridge(काष्ठा aspeed_p2a_ctrl *p2a_ctrl)
अणु
	regmap_update_bits(p2a_ctrl->regmap,
		SCU180, SCU180_ENP2A, SCU180_ENP2A);
पूर्ण

अटल व्योम aspeed_p2a_disable_bridge(काष्ठा aspeed_p2a_ctrl *p2a_ctrl)
अणु
	regmap_update_bits(p2a_ctrl->regmap, SCU180, SCU180_ENP2A, 0);
पूर्ण

अटल पूर्णांक aspeed_p2a_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ vsize;
	pgprot_t prot;
	काष्ठा aspeed_p2a_user *priv = file->निजी_data;
	काष्ठा aspeed_p2a_ctrl *ctrl = priv->parent;

	अगर (ctrl->mem_base == 0 && ctrl->mem_size == 0)
		वापस -EINVAL;

	vsize = vma->vm_end - vma->vm_start;
	prot = vma->vm_page_prot;

	अगर (vma->vm_pgoff + vsize > ctrl->mem_base + ctrl->mem_size)
		वापस -EINVAL;

	/* ast2400/2500 AHB accesses are not cache coherent */
	prot = pgprot_noncached(prot);

	अगर (remap_pfn_range(vma, vma->vm_start,
		(ctrl->mem_base >> PAGE_SHIFT) + vma->vm_pgoff,
		vsize, prot))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल bool aspeed_p2a_region_acquire(काष्ठा aspeed_p2a_user *priv,
		काष्ठा aspeed_p2a_ctrl *ctrl,
		काष्ठा aspeed_p2a_ctrl_mapping *map)
अणु
	पूर्णांक i;
	u64 base, end;
	bool matched = false;

	base = map->addr;
	end = map->addr + (map->length - 1);

	/* If the value is a legal u32, it will find a match. */
	क्रम (i = 0; i < P2A_REGION_COUNT; i++) अणु
		स्थिर काष्ठा region *curr = &ctrl->config->regions[i];

		/* If the top of this region is lower than your base, skip it.
		 */
		अगर (curr->max < base)
			जारी;

		/* If the bottom of this region is higher than your end, bail.
		 */
		अगर (curr->min > end)
			अवरोध;

		/* Lock this and update it, thereक्रमe it someone अन्यथा is
		 * closing their file out, this'll preserve the increment.
		 */
		mutex_lock(&ctrl->tracking);
		ctrl->पढ़ोerग_लिखोrs[i] += 1;
		mutex_unlock(&ctrl->tracking);

		/* Track with the user, so when they बंद their file, we can
		 * decrement properly.
		 */
		priv->पढ़ोग_लिखो[i] += 1;

		/* Enable the region as पढ़ो-ग_लिखो. */
		regmap_update_bits(ctrl->regmap, SCU2C, curr->bit, 0);
		matched = true;
	पूर्ण

	वापस matched;
पूर्ण

अटल दीर्घ aspeed_p2a_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ data)
अणु
	काष्ठा aspeed_p2a_user *priv = file->निजी_data;
	काष्ठा aspeed_p2a_ctrl *ctrl = priv->parent;
	व्योम __user *arg = (व्योम __user *)data;
	काष्ठा aspeed_p2a_ctrl_mapping map;

	अगर (copy_from_user(&map, arg, माप(map)))
		वापस -EFAULT;

	चयन (cmd) अणु
	हाल ASPEED_P2A_CTRL_IOCTL_SET_WINDOW:
		/* If they want a region to be पढ़ो-only, since the entire
		 * region is पढ़ो-only once enabled, we just need to track this
		 * user wants to पढ़ो from the bridge, and अगर it's not enabled.
		 * Enable it.
		 */
		अगर (map.flags == ASPEED_P2A_CTRL_READ_ONLY) अणु
			mutex_lock(&ctrl->tracking);
			ctrl->पढ़ोers += 1;
			mutex_unlock(&ctrl->tracking);

			/* Track with the user, so when they बंद their file,
			 * we can decrement properly.
			 */
			priv->पढ़ो += 1;
		पूर्ण अन्यथा अगर (map.flags == ASPEED_P2A_CTRL_READWRITE) अणु
			/* If we करोn't acquire any region वापस error. */
			अगर (!aspeed_p2a_region_acquire(priv, ctrl, &map)) अणु
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Invalid map flags. */
			वापस -EINVAL;
		पूर्ण

		aspeed_p2a_enable_bridge(ctrl);
		वापस 0;
	हाल ASPEED_P2A_CTRL_IOCTL_GET_MEMORY_CONFIG:
		/* This is a request क्रम the memory-region and corresponding
		 * length that is used by the driver क्रम mmap.
		 */

		map.flags = 0;
		map.addr = ctrl->mem_base;
		map.length = ctrl->mem_size;

		वापस copy_to_user(arg, &map, माप(map)) ? -EFAULT : 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण


/*
 * When a user खोलोs this file, we create a काष्ठाure to track their mappings.
 *
 * A user can map a region as पढ़ो-only (bridge enabled), or पढ़ो-ग_लिखो (bit
 * flipped, and bridge enabled).  Either way, this tracking is used, s.t. when
 * they release the device references are handled.
 *
 * The bridge is not enabled until a user calls an ioctl to map a region,
 * simply खोलोing the device करोes not enable it.
 */
अटल पूर्णांक aspeed_p2a_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा aspeed_p2a_user *priv;

	priv = kदो_स्मृति(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->file = file;
	priv->पढ़ो = 0;
	स_रखो(priv->पढ़ोग_लिखो, 0, माप(priv->पढ़ोग_लिखो));

	/* The file's निजी_data is initialized to the p2a_ctrl. */
	priv->parent = file->निजी_data;

	/* Set the file's private_data to the user's data. */
	file->निजी_data = priv;

	वापस 0;
पूर्ण

/*
 * This will बंद the users mappings.  It will go through what they had खोलोed
 * क्रम पढ़ोग_लिखो, and decrement those counts.  If at the end, this is the last
 * user, it'll बंद the bridge.
 */
अटल पूर्णांक aspeed_p2a_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक i;
	u32 bits = 0;
	bool खोलो_regions = false;
	काष्ठा aspeed_p2a_user *priv = file->निजी_data;

	/* Lock others from changing these values until everything is updated
	 * in one pass.
	 */
	mutex_lock(&priv->parent->tracking);

	priv->parent->पढ़ोers -= priv->पढ़ो;

	क्रम (i = 0; i < P2A_REGION_COUNT; i++) अणु
		priv->parent->पढ़ोerग_लिखोrs[i] -= priv->पढ़ोग_लिखो[i];

		अगर (priv->parent->पढ़ोerग_लिखोrs[i] > 0)
			खोलो_regions = true;
		अन्यथा
			bits |= priv->parent->config->regions[i].bit;
	पूर्ण

	/* Setting a bit to 1 disables the region, so let's just OR with the
	 * above to disable any.
	 */

	/* Note, अगर another user is trying to ioctl, they can't grab tracking,
	 * and thereक्रमe can't grab either रेजिस्टर mutex.
	 * If another user is trying to बंद, they can't grab tracking either.
	 */
	regmap_update_bits(priv->parent->regmap, SCU2C, bits, bits);

	/* If parent->पढ़ोers is zero and खोलो winकरोws is 0, disable the
	 * bridge.
	 */
	अगर (!खोलो_regions && priv->parent->पढ़ोers == 0)
		aspeed_p2a_disable_bridge(priv->parent);

	mutex_unlock(&priv->parent->tracking);

	kमुक्त(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations aspeed_p2a_ctrl_fops = अणु
	.owner = THIS_MODULE,
	.mmap = aspeed_p2a_mmap,
	.unlocked_ioctl = aspeed_p2a_ioctl,
	.खोलो = aspeed_p2a_खोलो,
	.release = aspeed_p2a_release,
पूर्ण;

/* The regions are controlled by SCU2C */
अटल व्योम aspeed_p2a_disable_all(काष्ठा aspeed_p2a_ctrl *p2a_ctrl)
अणु
	पूर्णांक i;
	u32 value = 0;

	क्रम (i = 0; i < P2A_REGION_COUNT; i++)
		value |= p2a_ctrl->config->regions[i].bit;

	regmap_update_bits(p2a_ctrl->regmap, SCU2C, value, value);

	/* Disable the bridge. */
	aspeed_p2a_disable_bridge(p2a_ctrl);
पूर्ण

अटल पूर्णांक aspeed_p2a_ctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_p2a_ctrl *misc_ctrl;
	काष्ठा device *dev;
	काष्ठा resource resm;
	काष्ठा device_node *node;
	पूर्णांक rc = 0;

	dev = &pdev->dev;

	misc_ctrl = devm_kzalloc(dev, माप(*misc_ctrl), GFP_KERNEL);
	अगर (!misc_ctrl)
		वापस -ENOMEM;

	mutex_init(&misc_ctrl->tracking);

	/* optional. */
	node = of_parse_phandle(dev->of_node, "memory-region", 0);
	अगर (node) अणु
		rc = of_address_to_resource(node, 0, &resm);
		of_node_put(node);
		अगर (rc) अणु
			dev_err(dev, "Couldn't address to resource for reserved memory\n");
			वापस -ENODEV;
		पूर्ण

		misc_ctrl->mem_size = resource_size(&resm);
		misc_ctrl->mem_base = resm.start;
	पूर्ण

	misc_ctrl->regmap = syscon_node_to_regmap(pdev->dev.parent->of_node);
	अगर (IS_ERR(misc_ctrl->regmap)) अणु
		dev_err(dev, "Couldn't get regmap\n");
		वापस -ENODEV;
	पूर्ण

	misc_ctrl->config = of_device_get_match_data(dev);

	dev_set_drvdata(&pdev->dev, misc_ctrl);

	aspeed_p2a_disable_all(misc_ctrl);

	misc_ctrl->miscdev.minor = MISC_DYNAMIC_MINOR;
	misc_ctrl->miscdev.name = DEVICE_NAME;
	misc_ctrl->miscdev.fops = &aspeed_p2a_ctrl_fops;
	misc_ctrl->miscdev.parent = dev;

	rc = misc_रेजिस्टर(&misc_ctrl->miscdev);
	अगर (rc)
		dev_err(dev, "Unable to register device\n");

	वापस rc;
पूर्ण

अटल पूर्णांक aspeed_p2a_ctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_p2a_ctrl *p2a_ctrl = dev_get_drvdata(&pdev->dev);

	misc_deरेजिस्टर(&p2a_ctrl->miscdev);

	वापस 0;
पूर्ण

#घोषणा SCU2C_DRAM	BIT(25)
#घोषणा SCU2C_SPI	BIT(24)
#घोषणा SCU2C_SOC	BIT(23)
#घोषणा SCU2C_FLASH	BIT(22)

अटल स्थिर काष्ठा aspeed_p2a_model_data ast2400_model_data = अणु
	.regions = अणु
		अणु0x00000000, 0x17FFFFFF, SCU2C_FLASHपूर्ण,
		अणु0x18000000, 0x1FFFFFFF, SCU2C_SOCपूर्ण,
		अणु0x20000000, 0x2FFFFFFF, SCU2C_FLASHपूर्ण,
		अणु0x30000000, 0x3FFFFFFF, SCU2C_SPIपूर्ण,
		अणु0x40000000, 0x5FFFFFFF, SCU2C_DRAMपूर्ण,
		अणु0x60000000, 0xFFFFFFFF, SCU2C_SOCपूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा aspeed_p2a_model_data ast2500_model_data = अणु
	.regions = अणु
		अणु0x00000000, 0x0FFFFFFF, SCU2C_FLASHपूर्ण,
		अणु0x10000000, 0x1FFFFFFF, SCU2C_SOCपूर्ण,
		अणु0x20000000, 0x3FFFFFFF, SCU2C_FLASHपूर्ण,
		अणु0x40000000, 0x5FFFFFFF, SCU2C_SOCपूर्ण,
		अणु0x60000000, 0x7FFFFFFF, SCU2C_SPIपूर्ण,
		अणु0x80000000, 0xFFFFFFFF, SCU2C_DRAMपूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id aspeed_p2a_ctrl_match[] = अणु
	अणु .compatible = "aspeed,ast2400-p2a-ctrl",
	  .data = &ast2400_model_data पूर्ण,
	अणु .compatible = "aspeed,ast2500-p2a-ctrl",
	  .data = &ast2500_model_data पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver aspeed_p2a_ctrl_driver = अणु
	.driver = अणु
		.name		= DEVICE_NAME,
		.of_match_table = aspeed_p2a_ctrl_match,
	पूर्ण,
	.probe = aspeed_p2a_ctrl_probe,
	.हटाओ = aspeed_p2a_ctrl_हटाओ,
पूर्ण;

module_platक्रमm_driver(aspeed_p2a_ctrl_driver);

MODULE_DEVICE_TABLE(of, aspeed_p2a_ctrl_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Venture <venture@google.com>");
MODULE_DESCRIPTION("Control for aspeed 2400/2500 P2A VGA HOST to BMC mappings");
