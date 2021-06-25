<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "mlx4.h"

#घोषणा BAD_ACCESS			0xBADACCE5
#घोषणा HEALTH_BUFFER_SIZE		0x40
#घोषणा CR_ENABLE_BIT			swab32(BIT(6))
#घोषणा CR_ENABLE_BIT_OFFSET		0xF3F04
#घोषणा MAX_NUM_OF_DUMPS_TO_STORE	(8)

#घोषणा REGION_CR_SPACE "cr-space"
#घोषणा REGION_FW_HEALTH "fw-health"

अटल स्थिर अक्षर * स्थिर region_cr_space_str = REGION_CR_SPACE;
अटल स्थिर अक्षर * स्थिर region_fw_health_str = REGION_FW_HEALTH;

अटल स्थिर काष्ठा devlink_region_ops region_cr_space_ops = अणु
	.name = REGION_CR_SPACE,
	.deकाष्ठाor = &kvमुक्त,
पूर्ण;

अटल स्थिर काष्ठा devlink_region_ops region_fw_health_ops = अणु
	.name = REGION_FW_HEALTH,
	.deकाष्ठाor = &kvमुक्त,
पूर्ण;

/* Set to true in हाल cr enable bit was set to true beक्रमe crdump */
अटल bool crdump_enbale_bit_set;

अटल व्योम crdump_enable_crspace_access(काष्ठा mlx4_dev *dev,
					 u8 __iomem *cr_space)
अणु
	/* Get current enable bit value */
	crdump_enbale_bit_set =
		पढ़ोl(cr_space + CR_ENABLE_BIT_OFFSET) & CR_ENABLE_BIT;

	/* Enable FW CR filter (set bit6 to 0) */
	अगर (crdump_enbale_bit_set)
		ग_लिखोl(पढ़ोl(cr_space + CR_ENABLE_BIT_OFFSET) & ~CR_ENABLE_BIT,
		       cr_space + CR_ENABLE_BIT_OFFSET);

	/* Enable block अस्थिर crspace accesses */
	ग_लिखोl(swab32(1), cr_space + dev->caps.health_buffer_addrs +
	       HEALTH_BUFFER_SIZE);
पूर्ण

अटल व्योम crdump_disable_crspace_access(काष्ठा mlx4_dev *dev,
					  u8 __iomem *cr_space)
अणु
	/* Disable block अस्थिर crspace accesses */
	ग_लिखोl(0, cr_space + dev->caps.health_buffer_addrs +
	       HEALTH_BUFFER_SIZE);

	/* Restore FW CR filter value (set bit6 to original value) */
	अगर (crdump_enbale_bit_set)
		ग_लिखोl(पढ़ोl(cr_space + CR_ENABLE_BIT_OFFSET) | CR_ENABLE_BIT,
		       cr_space + CR_ENABLE_BIT_OFFSET);
पूर्ण

अटल व्योम mlx4_crdump_collect_crspace(काष्ठा mlx4_dev *dev,
					u8 __iomem *cr_space,
					u32 id)
अणु
	काष्ठा mlx4_fw_crdump *crdump = &dev->persist->crdump;
	काष्ठा pci_dev *pdev = dev->persist->pdev;
	अचिन्हित दीर्घ cr_res_size;
	u8 *crspace_data;
	पूर्णांक offset;
	पूर्णांक err;

	अगर (!crdump->region_crspace) अणु
		mlx4_err(dev, "crdump: cr-space region is NULL\n");
		वापस;
	पूर्ण

	/* Try to collect CR space */
	cr_res_size = pci_resource_len(pdev, 0);
	crspace_data = kvदो_स्मृति(cr_res_size, GFP_KERNEL);
	अगर (crspace_data) अणु
		क्रम (offset = 0; offset < cr_res_size; offset += 4)
			*(u32 *)(crspace_data + offset) =
					पढ़ोl(cr_space + offset);

		err = devlink_region_snapshot_create(crdump->region_crspace,
						     crspace_data, id);
		अगर (err) अणु
			kvमुक्त(crspace_data);
			mlx4_warn(dev, "crdump: devlink create %s snapshot id %d err %d\n",
				  region_cr_space_str, id, err);
		पूर्ण अन्यथा अणु
			mlx4_info(dev, "crdump: added snapshot %d to devlink region %s\n",
				  id, region_cr_space_str);
		पूर्ण
	पूर्ण अन्यथा अणु
		mlx4_err(dev, "crdump: Failed to allocate crspace buffer\n");
	पूर्ण
पूर्ण

अटल व्योम mlx4_crdump_collect_fw_health(काष्ठा mlx4_dev *dev,
					  u8 __iomem *cr_space,
					  u32 id)
अणु
	काष्ठा mlx4_fw_crdump *crdump = &dev->persist->crdump;
	u8 *health_data;
	पूर्णांक offset;
	पूर्णांक err;

	अगर (!crdump->region_fw_health) अणु
		mlx4_err(dev, "crdump: fw-health region is NULL\n");
		वापस;
	पूर्ण

	/* Try to collect health buffer */
	health_data = kvदो_स्मृति(HEALTH_BUFFER_SIZE, GFP_KERNEL);
	अगर (health_data) अणु
		u8 __iomem *health_buf_start =
				cr_space + dev->caps.health_buffer_addrs;

		क्रम (offset = 0; offset < HEALTH_BUFFER_SIZE; offset += 4)
			*(u32 *)(health_data + offset) =
					पढ़ोl(health_buf_start + offset);

		err = devlink_region_snapshot_create(crdump->region_fw_health,
						     health_data, id);
		अगर (err) अणु
			kvमुक्त(health_data);
			mlx4_warn(dev, "crdump: devlink create %s snapshot id %d err %d\n",
				  region_fw_health_str, id, err);
		पूर्ण अन्यथा अणु
			mlx4_info(dev, "crdump: added snapshot %d to devlink region %s\n",
				  id, region_fw_health_str);
		पूर्ण
	पूर्ण अन्यथा अणु
		mlx4_err(dev, "crdump: Failed to allocate health buffer\n");
	पूर्ण
पूर्ण

पूर्णांक mlx4_crdump_collect(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlx4_priv(dev));
	काष्ठा mlx4_fw_crdump *crdump = &dev->persist->crdump;
	काष्ठा pci_dev *pdev = dev->persist->pdev;
	अचिन्हित दीर्घ cr_res_size;
	u8 __iomem *cr_space;
	पूर्णांक err;
	u32 id;

	अगर (!dev->caps.health_buffer_addrs) अणु
		mlx4_info(dev, "crdump: FW doesn't support health buffer access, skipping\n");
		वापस 0;
	पूर्ण

	अगर (!crdump->snapshot_enable) अणु
		mlx4_info(dev, "crdump: devlink snapshot disabled, skipping\n");
		वापस 0;
	पूर्ण

	cr_res_size = pci_resource_len(pdev, 0);

	cr_space = ioremap(pci_resource_start(pdev, 0), cr_res_size);
	अगर (!cr_space) अणु
		mlx4_err(dev, "crdump: Failed to map pci cr region\n");
		वापस -ENODEV;
	पूर्ण

	/* Get the available snapshot ID क्रम the dumps */
	err = devlink_region_snapshot_id_get(devlink, &id);
	अगर (err) अणु
		mlx4_err(dev, "crdump: devlink get snapshot id err %d\n", err);
		iounmap(cr_space);
		वापस err;
	पूर्ण

	crdump_enable_crspace_access(dev, cr_space);

	/* Try to capture dumps */
	mlx4_crdump_collect_crspace(dev, cr_space, id);
	mlx4_crdump_collect_fw_health(dev, cr_space, id);

	/* Release reference on the snapshot id */
	devlink_region_snapshot_id_put(devlink, id);

	crdump_disable_crspace_access(dev, cr_space);

	iounmap(cr_space);
	वापस 0;
पूर्ण

पूर्णांक mlx4_crdump_init(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlx4_priv(dev));
	काष्ठा mlx4_fw_crdump *crdump = &dev->persist->crdump;
	काष्ठा pci_dev *pdev = dev->persist->pdev;

	crdump->snapshot_enable = false;

	/* Create cr-space region */
	crdump->region_crspace =
		devlink_region_create(devlink,
				      &region_cr_space_ops,
				      MAX_NUM_OF_DUMPS_TO_STORE,
				      pci_resource_len(pdev, 0));
	अगर (IS_ERR(crdump->region_crspace))
		mlx4_warn(dev, "crdump: create devlink region %s err %ld\n",
			  region_cr_space_str,
			  PTR_ERR(crdump->region_crspace));

	/* Create fw-health region */
	crdump->region_fw_health =
		devlink_region_create(devlink,
				      &region_fw_health_ops,
				      MAX_NUM_OF_DUMPS_TO_STORE,
				      HEALTH_BUFFER_SIZE);
	अगर (IS_ERR(crdump->region_fw_health))
		mlx4_warn(dev, "crdump: create devlink region %s err %ld\n",
			  region_fw_health_str,
			  PTR_ERR(crdump->region_fw_health));

	वापस 0;
पूर्ण

व्योम mlx4_crdump_end(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_fw_crdump *crdump = &dev->persist->crdump;

	devlink_region_destroy(crdump->region_fw_health);
	devlink_region_destroy(crdump->region_crspace);
पूर्ण
