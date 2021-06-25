<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Amlogic Secure Monitor driver
 *
 * Copyright (C) 2016 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 */

#घोषणा pr_fmt(fmt) "meson-sm: " fmt

#समावेश <linux/arm-smccc.h>
#समावेश <linux/bug.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/types.h>
#समावेश <linux/sizes.h>
 #समावेश <linux/slab.h>

#समावेश <linux/firmware/meson/meson_sm.h>

काष्ठा meson_sm_cmd अणु
	अचिन्हित पूर्णांक index;
	u32 smc_id;
पूर्ण;
#घोषणा CMD(d, s) अणु .index = (d), .smc_id = (s), पूर्ण

काष्ठा meson_sm_chip अणु
	अचिन्हित पूर्णांक shmem_size;
	u32 cmd_shmem_in_base;
	u32 cmd_shmem_out_base;
	काष्ठा meson_sm_cmd cmd[];
पूर्ण;

अटल स्थिर काष्ठा meson_sm_chip gxbb_chip = अणु
	.shmem_size		= SZ_4K,
	.cmd_shmem_in_base	= 0x82000020,
	.cmd_shmem_out_base	= 0x82000021,
	.cmd = अणु
		CMD(SM_EFUSE_READ,	0x82000030),
		CMD(SM_EFUSE_WRITE,	0x82000031),
		CMD(SM_EFUSE_USER_MAX,	0x82000033),
		CMD(SM_GET_CHIP_ID,	0x82000044),
		CMD(SM_A1_PWRC_SET,	0x82000093),
		CMD(SM_A1_PWRC_GET,	0x82000095),
		अणु /* sentinel */ पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा meson_sm_firmware अणु
	स्थिर काष्ठा meson_sm_chip *chip;
	व्योम __iomem *sm_shmem_in_base;
	व्योम __iomem *sm_shmem_out_base;
पूर्ण;

अटल u32 meson_sm_get_cmd(स्थिर काष्ठा meson_sm_chip *chip,
			    अचिन्हित पूर्णांक cmd_index)
अणु
	स्थिर काष्ठा meson_sm_cmd *cmd = chip->cmd;

	जबतक (cmd->smc_id && cmd->index != cmd_index)
		cmd++;

	वापस cmd->smc_id;
पूर्ण

अटल u32 __meson_sm_call(u32 cmd, u32 arg0, u32 arg1, u32 arg2,
			   u32 arg3, u32 arg4)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(cmd, arg0, arg1, arg2, arg3, arg4, 0, 0, &res);
	वापस res.a0;
पूर्ण

अटल व्योम __iomem *meson_sm_map_shmem(u32 cmd_shmem, अचिन्हित पूर्णांक size)
अणु
	u32 sm_phy_base;

	sm_phy_base = __meson_sm_call(cmd_shmem, 0, 0, 0, 0, 0);
	अगर (!sm_phy_base)
		वापस 0;

	वापस ioremap_cache(sm_phy_base, size);
पूर्ण

/**
 * meson_sm_call - generic SMC32 call to the secure-monitor
 *
 * @fw:		Poपूर्णांकer to secure-monitor firmware
 * @cmd_index:	Index of the SMC32 function ID
 * @ret:	Returned value
 * @arg0:	SMC32 Argument 0
 * @arg1:	SMC32 Argument 1
 * @arg2:	SMC32 Argument 2
 * @arg3:	SMC32 Argument 3
 * @arg4:	SMC32 Argument 4
 *
 * Return:	0 on success, a negative value on error
 */
पूर्णांक meson_sm_call(काष्ठा meson_sm_firmware *fw, अचिन्हित पूर्णांक cmd_index,
		  u32 *ret, u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4)
अणु
	u32 cmd, lret;

	अगर (!fw->chip)
		वापस -ENOENT;

	cmd = meson_sm_get_cmd(fw->chip, cmd_index);
	अगर (!cmd)
		वापस -EINVAL;

	lret = __meson_sm_call(cmd, arg0, arg1, arg2, arg3, arg4);

	अगर (ret)
		*ret = lret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(meson_sm_call);

/**
 * meson_sm_call_पढ़ो - retrieve data from secure-monitor
 *
 * @fw:		Poपूर्णांकer to secure-monitor firmware
 * @buffer:	Buffer to store the retrieved data
 * @bsize:	Size of the buffer
 * @cmd_index:	Index of the SMC32 function ID
 * @arg0:	SMC32 Argument 0
 * @arg1:	SMC32 Argument 1
 * @arg2:	SMC32 Argument 2
 * @arg3:	SMC32 Argument 3
 * @arg4:	SMC32 Argument 4
 *
 * Return:	size of पढ़ो data on success, a negative value on error
 *		When 0 is वापसed there is no guarantee about the amount of
 *		data पढ़ो and bsize bytes are copied in buffer.
 */
पूर्णांक meson_sm_call_पढ़ो(काष्ठा meson_sm_firmware *fw, व्योम *buffer,
		       अचिन्हित पूर्णांक bsize, अचिन्हित पूर्णांक cmd_index, u32 arg0,
		       u32 arg1, u32 arg2, u32 arg3, u32 arg4)
अणु
	u32 size;
	पूर्णांक ret;

	अगर (!fw->chip)
		वापस -ENOENT;

	अगर (!fw->chip->cmd_shmem_out_base)
		वापस -EINVAL;

	अगर (bsize > fw->chip->shmem_size)
		वापस -EINVAL;

	अगर (meson_sm_call(fw, cmd_index, &size, arg0, arg1, arg2, arg3, arg4) < 0)
		वापस -EINVAL;

	अगर (size > bsize)
		वापस -EINVAL;

	ret = size;

	अगर (!size)
		size = bsize;

	अगर (buffer)
		स_नकल(buffer, fw->sm_shmem_out_base, size);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(meson_sm_call_पढ़ो);

/**
 * meson_sm_call_ग_लिखो - send data to secure-monitor
 *
 * @fw:		Poपूर्णांकer to secure-monitor firmware
 * @buffer:	Buffer containing data to send
 * @size:	Size of the data to send
 * @cmd_index:	Index of the SMC32 function ID
 * @arg0:	SMC32 Argument 0
 * @arg1:	SMC32 Argument 1
 * @arg2:	SMC32 Argument 2
 * @arg3:	SMC32 Argument 3
 * @arg4:	SMC32 Argument 4
 *
 * Return:	size of sent data on success, a negative value on error
 */
पूर्णांक meson_sm_call_ग_लिखो(काष्ठा meson_sm_firmware *fw, व्योम *buffer,
			अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक cmd_index, u32 arg0,
			u32 arg1, u32 arg2, u32 arg3, u32 arg4)
अणु
	u32 written;

	अगर (!fw->chip)
		वापस -ENOENT;

	अगर (size > fw->chip->shmem_size)
		वापस -EINVAL;

	अगर (!fw->chip->cmd_shmem_in_base)
		वापस -EINVAL;

	स_नकल(fw->sm_shmem_in_base, buffer, size);

	अगर (meson_sm_call(fw, cmd_index, &written, arg0, arg1, arg2, arg3, arg4) < 0)
		वापस -EINVAL;

	अगर (!written)
		वापस -EINVAL;

	वापस written;
पूर्ण
EXPORT_SYMBOL(meson_sm_call_ग_लिखो);

/**
 * meson_sm_get - get poपूर्णांकer to meson_sm_firmware काष्ठाure.
 *
 * @sm_node:		Poपूर्णांकer to the secure-monitor Device Tree node.
 *
 * Return:		शून्य is the secure-monitor device is not पढ़ोy.
 */
काष्ठा meson_sm_firmware *meson_sm_get(काष्ठा device_node *sm_node)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(sm_node);

	अगर (!pdev)
		वापस शून्य;

	वापस platक्रमm_get_drvdata(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(meson_sm_get);

#घोषणा SM_CHIP_ID_LENGTH	119
#घोषणा SM_CHIP_ID_OFFSET	4
#घोषणा SM_CHIP_ID_SIZE		12

अटल sमाप_प्रकार serial_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा meson_sm_firmware *fw;
	uपूर्णांक8_t *id_buf;
	पूर्णांक ret;

	fw = platक्रमm_get_drvdata(pdev);

	id_buf = kदो_स्मृति(SM_CHIP_ID_LENGTH, GFP_KERNEL);
	अगर (!id_buf)
		वापस -ENOMEM;

	ret = meson_sm_call_पढ़ो(fw, id_buf, SM_CHIP_ID_LENGTH, SM_GET_CHIP_ID,
				 0, 0, 0, 0, 0);
	अगर (ret < 0) अणु
		kमुक्त(id_buf);
		वापस ret;
	पूर्ण

	ret = प्र_लिखो(buf, "%12phN\n", &id_buf[SM_CHIP_ID_OFFSET]);

	kमुक्त(id_buf);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RO(serial);

अटल काष्ठा attribute *meson_sm_sysfs_attributes[] = अणु
	&dev_attr_serial.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group meson_sm_sysfs_attr_group = अणु
	.attrs = meson_sm_sysfs_attributes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_sm_ids[] = अणु
	अणु .compatible = "amlogic,meson-gxbb-sm", .data = &gxbb_chip पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक __init meson_sm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा meson_sm_chip *chip;
	काष्ठा meson_sm_firmware *fw;

	fw = devm_kzalloc(dev, माप(*fw), GFP_KERNEL);
	अगर (!fw)
		वापस -ENOMEM;

	chip = of_match_device(meson_sm_ids, dev)->data;

	अगर (chip->cmd_shmem_in_base) अणु
		fw->sm_shmem_in_base = meson_sm_map_shmem(chip->cmd_shmem_in_base,
							  chip->shmem_size);
		अगर (WARN_ON(!fw->sm_shmem_in_base))
			जाओ out;
	पूर्ण

	अगर (chip->cmd_shmem_out_base) अणु
		fw->sm_shmem_out_base = meson_sm_map_shmem(chip->cmd_shmem_out_base,
							   chip->shmem_size);
		अगर (WARN_ON(!fw->sm_shmem_out_base))
			जाओ out_in_base;
	पूर्ण

	fw->chip = chip;

	platक्रमm_set_drvdata(pdev, fw);

	pr_info("secure-monitor enabled\n");

	अगर (sysfs_create_group(&pdev->dev.kobj, &meson_sm_sysfs_attr_group))
		जाओ out_in_base;

	वापस 0;

out_in_base:
	iounmap(fw->sm_shmem_in_base);
out:
	वापस -EINVAL;
पूर्ण

अटल काष्ठा platक्रमm_driver meson_sm_driver = अणु
	.driver = अणु
		.name = "meson-sm",
		.of_match_table = of_match_ptr(meson_sm_ids),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver_probe(meson_sm_driver, meson_sm_probe);
MODULE_LICENSE("GPL v2");
