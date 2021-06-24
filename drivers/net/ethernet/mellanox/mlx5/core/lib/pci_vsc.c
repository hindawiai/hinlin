<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies */

#समावेश <linux/pci.h>
#समावेश "mlx5_core.h"
#समावेश "pci_vsc.h"

#घोषणा MLX5_EXTRACT_C(source, offset, size)	\
	((((u32)(source)) >> (offset)) & MLX5_ONES32(size))
#घोषणा MLX5_EXTRACT(src, start, len)		\
	(((len) == 32) ? (src) : MLX5_EXTRACT_C(src, start, len))
#घोषणा MLX5_ONES32(size)			\
	((size) ? (0xffffffff >> (32 - (size))) : 0)
#घोषणा MLX5_MASK32(offset, size)		\
	(MLX5_ONES32(size) << (offset))
#घोषणा MLX5_MERGE_C(rsrc1, rsrc2, start, len)  \
	((((rsrc2) << (start)) & (MLX5_MASK32((start), (len)))) | \
	((rsrc1) & (~MLX5_MASK32((start), (len)))))
#घोषणा MLX5_MERGE(rsrc1, rsrc2, start, len)	\
	(((len) == 32) ? (rsrc2) : MLX5_MERGE_C(rsrc1, rsrc2, start, len))
#घोषणा vsc_पढ़ो(dev, offset, val) \
	pci_पढ़ो_config_dword((dev)->pdev, (dev)->vsc_addr + (offset), (val))
#घोषणा vsc_ग_लिखो(dev, offset, val) \
	pci_ग_लिखो_config_dword((dev)->pdev, (dev)->vsc_addr + (offset), (val))
#घोषणा VSC_MAX_RETRIES 2048

क्रमागत अणु
	VSC_CTRL_OFFSET = 0x4,
	VSC_COUNTER_OFFSET = 0x8,
	VSC_SEMAPHORE_OFFSET = 0xc,
	VSC_ADDR_OFFSET = 0x10,
	VSC_DATA_OFFSET = 0x14,

	VSC_FLAG_BIT_OFFS = 31,
	VSC_FLAG_BIT_LEN = 1,

	VSC_SYND_BIT_OFFS = 30,
	VSC_SYND_BIT_LEN = 1,

	VSC_ADDR_BIT_OFFS = 0,
	VSC_ADDR_BIT_LEN = 30,

	VSC_SPACE_BIT_OFFS = 0,
	VSC_SPACE_BIT_LEN = 16,

	VSC_SIZE_VLD_BIT_OFFS = 28,
	VSC_SIZE_VLD_BIT_LEN = 1,

	VSC_STATUS_BIT_OFFS = 29,
	VSC_STATUS_BIT_LEN = 3,
पूर्ण;

व्योम mlx5_pci_vsc_init(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!mlx5_core_is_pf(dev))
		वापस;

	dev->vsc_addr = pci_find_capability(dev->pdev,
					    PCI_CAP_ID_VNDR);
	अगर (!dev->vsc_addr)
		mlx5_core_warn(dev, "Failed to get valid vendor specific ID\n");
पूर्ण

पूर्णांक mlx5_vsc_gw_lock(काष्ठा mlx5_core_dev *dev)
अणु
	u32 counter = 0;
	पूर्णांक retries = 0;
	u32 lock_val;
	पूर्णांक ret;

	pci_cfg_access_lock(dev->pdev);
	करो अणु
		अगर (retries > VSC_MAX_RETRIES) अणु
			ret = -EBUSY;
			जाओ pci_unlock;
		पूर्ण

		/* Check अगर semaphore is alपढ़ोy locked */
		ret = vsc_पढ़ो(dev, VSC_SEMAPHORE_OFFSET, &lock_val);
		अगर (ret)
			जाओ pci_unlock;

		अगर (lock_val) अणु
			retries++;
			usleep_range(1000, 2000);
			जारी;
		पूर्ण

		/* Read and ग_लिखो counter value, अगर written value is
		 * the same, semaphore was acquired successfully.
		 */
		ret = vsc_पढ़ो(dev, VSC_COUNTER_OFFSET, &counter);
		अगर (ret)
			जाओ pci_unlock;

		ret = vsc_ग_लिखो(dev, VSC_SEMAPHORE_OFFSET, counter);
		अगर (ret)
			जाओ pci_unlock;

		ret = vsc_पढ़ो(dev, VSC_SEMAPHORE_OFFSET, &lock_val);
		अगर (ret)
			जाओ pci_unlock;

		retries++;
	पूर्ण जबतक (counter != lock_val);

	वापस 0;

pci_unlock:
	pci_cfg_access_unlock(dev->pdev);
	वापस ret;
पूर्ण

पूर्णांक mlx5_vsc_gw_unlock(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक ret;

	ret = vsc_ग_लिखो(dev, VSC_SEMAPHORE_OFFSET, MLX5_VSC_UNLOCK);
	pci_cfg_access_unlock(dev->pdev);
	वापस ret;
पूर्ण

पूर्णांक mlx5_vsc_gw_set_space(काष्ठा mlx5_core_dev *dev, u16 space,
			  u32 *ret_space_size)
अणु
	पूर्णांक ret;
	u32 val = 0;

	अगर (!mlx5_vsc_accessible(dev))
		वापस -EINVAL;

	अगर (ret_space_size)
		*ret_space_size = 0;

	/* Get a unique val */
	ret = vsc_पढ़ो(dev, VSC_CTRL_OFFSET, &val);
	अगर (ret)
		जाओ out;

	/* Try to modअगरy the lock */
	val = MLX5_MERGE(val, space, VSC_SPACE_BIT_OFFS, VSC_SPACE_BIT_LEN);
	ret = vsc_ग_लिखो(dev, VSC_CTRL_OFFSET, val);
	अगर (ret)
		जाओ out;

	/* Verअगरy lock was modअगरied */
	ret = vsc_पढ़ो(dev, VSC_CTRL_OFFSET, &val);
	अगर (ret)
		जाओ out;

	अगर (MLX5_EXTRACT(val, VSC_STATUS_BIT_OFFS, VSC_STATUS_BIT_LEN) == 0)
		वापस -EINVAL;

	/* Get space max address अगर indicated by size valid bit */
	अगर (ret_space_size &&
	    MLX5_EXTRACT(val, VSC_SIZE_VLD_BIT_OFFS, VSC_SIZE_VLD_BIT_LEN)) अणु
		ret = vsc_पढ़ो(dev, VSC_ADDR_OFFSET, &val);
		अगर (ret) अणु
			mlx5_core_warn(dev, "Failed to get max space size\n");
			जाओ out;
		पूर्ण
		*ret_space_size = MLX5_EXTRACT(val, VSC_ADDR_BIT_OFFS,
					       VSC_ADDR_BIT_LEN);
	पूर्ण
	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_vsc_रुको_on_flag(काष्ठा mlx5_core_dev *dev, u8 expected_val)
अणु
	पूर्णांक retries = 0;
	u32 flag;
	पूर्णांक ret;

	करो अणु
		अगर (retries > VSC_MAX_RETRIES)
			वापस -EBUSY;

		ret = vsc_पढ़ो(dev, VSC_ADDR_OFFSET, &flag);
		अगर (ret)
			वापस ret;
		flag = MLX5_EXTRACT(flag, VSC_FLAG_BIT_OFFS, VSC_FLAG_BIT_LEN);
		retries++;

		अगर ((retries & 0xf) == 0)
			usleep_range(1000, 2000);

	पूर्ण जबतक (flag != expected_val);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_vsc_gw_ग_लिखो(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक address,
			     u32 data)
अणु
	पूर्णांक ret;

	अगर (MLX5_EXTRACT(address, VSC_SYND_BIT_OFFS,
			 VSC_FLAG_BIT_LEN + VSC_SYND_BIT_LEN))
		वापस -EINVAL;

	/* Set flag to 0x1 */
	address = MLX5_MERGE(address, 1, VSC_FLAG_BIT_OFFS, 1);
	ret = vsc_ग_लिखो(dev, VSC_DATA_OFFSET, data);
	अगर (ret)
		जाओ out;

	ret = vsc_ग_लिखो(dev, VSC_ADDR_OFFSET, address);
	अगर (ret)
		जाओ out;

	/* Wait क्रम the flag to be cleared */
	ret = mlx5_vsc_रुको_on_flag(dev, 0);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_vsc_gw_पढ़ो(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक address,
			    u32 *data)
अणु
	पूर्णांक ret;

	अगर (MLX5_EXTRACT(address, VSC_SYND_BIT_OFFS,
			 VSC_FLAG_BIT_LEN + VSC_SYND_BIT_LEN))
		वापस -EINVAL;

	ret = vsc_ग_लिखो(dev, VSC_ADDR_OFFSET, address);
	अगर (ret)
		जाओ out;

	ret = mlx5_vsc_रुको_on_flag(dev, 1);
	अगर (ret)
		जाओ out;

	ret = vsc_पढ़ो(dev, VSC_DATA_OFFSET, data);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_vsc_gw_पढ़ो_fast(काष्ठा mlx5_core_dev *dev,
				 अचिन्हित पूर्णांक पढ़ो_addr,
				 अचिन्हित पूर्णांक *next_पढ़ो_addr,
				 u32 *data)
अणु
	पूर्णांक ret;

	ret = mlx5_vsc_gw_पढ़ो(dev, पढ़ो_addr, data);
	अगर (ret)
		जाओ out;

	ret = vsc_पढ़ो(dev, VSC_ADDR_OFFSET, next_पढ़ो_addr);
	अगर (ret)
		जाओ out;

	*next_पढ़ो_addr = MLX5_EXTRACT(*next_पढ़ो_addr, VSC_ADDR_BIT_OFFS,
				       VSC_ADDR_BIT_LEN);

	अगर (*next_पढ़ो_addr <= पढ़ो_addr)
		ret = -EINVAL;
out:
	वापस ret;
पूर्ण

पूर्णांक mlx5_vsc_gw_पढ़ो_block_fast(काष्ठा mlx5_core_dev *dev, u32 *data,
				पूर्णांक length)
अणु
	अचिन्हित पूर्णांक next_पढ़ो_addr = 0;
	अचिन्हित पूर्णांक पढ़ो_addr = 0;

	जबतक (पढ़ो_addr < length) अणु
		अगर (mlx5_vsc_gw_पढ़ो_fast(dev, पढ़ो_addr, &next_पढ़ो_addr,
					  &data[(पढ़ो_addr >> 2)]))
			वापस पढ़ो_addr;

		पढ़ो_addr = next_पढ़ो_addr;
	पूर्ण
	वापस length;
पूर्ण

पूर्णांक mlx5_vsc_sem_set_space(काष्ठा mlx5_core_dev *dev, u16 space,
			   क्रमागत mlx5_vsc_state state)
अणु
	u32 data, id = 0;
	पूर्णांक ret;

	ret = mlx5_vsc_gw_set_space(dev, MLX5_SEMAPHORE_SPACE_DOMAIN, शून्य);
	अगर (ret) अणु
		mlx5_core_warn(dev, "Failed to set gw space %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (state == MLX5_VSC_LOCK) अणु
		/* Get a unique ID based on the counter */
		ret = vsc_पढ़ो(dev, VSC_COUNTER_OFFSET, &id);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Try to modअगरy lock */
	ret = mlx5_vsc_gw_ग_लिखो(dev, space, id);
	अगर (ret)
		वापस ret;

	/* Verअगरy lock was modअगरied */
	ret = mlx5_vsc_gw_पढ़ो(dev, space, &data);
	अगर (ret)
		वापस -EINVAL;

	अगर (data != id)
		वापस -EBUSY;

	वापस 0;
पूर्ण
