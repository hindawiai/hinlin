<शैली गुरु>
/*
 * Driver क्रम Marvell NETA network controller Buffer Manager.
 *
 * Copyright (C) 2015 Marvell
 *
 * Marcin Wojtas <mw@semihalf.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mbus.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/skbuff.h>
#समावेश <net/hwbm.h>
#समावेश "mvneta_bm.h"

#घोषणा MVNETA_BM_DRIVER_NAME "mvneta_bm"
#घोषणा MVNETA_BM_DRIVER_VERSION "1.0"

अटल व्योम mvneta_bm_ग_लिखो(काष्ठा mvneta_bm *priv, u32 offset, u32 data)
अणु
	ग_लिखोl(data, priv->reg_base + offset);
पूर्ण

अटल u32 mvneta_bm_पढ़ो(काष्ठा mvneta_bm *priv, u32 offset)
अणु
	वापस पढ़ोl(priv->reg_base + offset);
पूर्ण

अटल व्योम mvneta_bm_pool_enable(काष्ठा mvneta_bm *priv, पूर्णांक pool_id)
अणु
	u32 val;

	val = mvneta_bm_पढ़ो(priv, MVNETA_BM_POOL_BASE_REG(pool_id));
	val |= MVNETA_BM_POOL_ENABLE_MASK;
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_POOL_BASE_REG(pool_id), val);

	/* Clear BM cause रेजिस्टर */
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_INTR_CAUSE_REG, 0);
पूर्ण

अटल व्योम mvneta_bm_pool_disable(काष्ठा mvneta_bm *priv, पूर्णांक pool_id)
अणु
	u32 val;

	val = mvneta_bm_पढ़ो(priv, MVNETA_BM_POOL_BASE_REG(pool_id));
	val &= ~MVNETA_BM_POOL_ENABLE_MASK;
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_POOL_BASE_REG(pool_id), val);
पूर्ण

अटल अंतरभूत व्योम mvneta_bm_config_set(काष्ठा mvneta_bm *priv, u32 mask)
अणु
	u32 val;

	val = mvneta_bm_पढ़ो(priv, MVNETA_BM_CONFIG_REG);
	val |= mask;
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_CONFIG_REG, val);
पूर्ण

अटल अंतरभूत व्योम mvneta_bm_config_clear(काष्ठा mvneta_bm *priv, u32 mask)
अणु
	u32 val;

	val = mvneta_bm_पढ़ो(priv, MVNETA_BM_CONFIG_REG);
	val &= ~mask;
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_CONFIG_REG, val);
पूर्ण

अटल व्योम mvneta_bm_pool_target_set(काष्ठा mvneta_bm *priv, पूर्णांक pool_id,
				      u8 target_id, u8 attr)
अणु
	u32 val;

	val = mvneta_bm_पढ़ो(priv, MVNETA_BM_XBAR_POOL_REG(pool_id));
	val &= ~MVNETA_BM_TARGET_ID_MASK(pool_id);
	val &= ~MVNETA_BM_XBAR_ATTR_MASK(pool_id);
	val |= MVNETA_BM_TARGET_ID_VAL(pool_id, target_id);
	val |= MVNETA_BM_XBAR_ATTR_VAL(pool_id, attr);

	mvneta_bm_ग_लिखो(priv, MVNETA_BM_XBAR_POOL_REG(pool_id), val);
पूर्ण

पूर्णांक mvneta_bm_स्थिरruct(काष्ठा hwbm_pool *hwbm_pool, व्योम *buf)
अणु
	काष्ठा mvneta_bm_pool *bm_pool =
		(काष्ठा mvneta_bm_pool *)hwbm_pool->priv;
	काष्ठा mvneta_bm *priv = bm_pool->priv;
	dma_addr_t phys_addr;

	/* In order to update buf_cookie field of RX descriptor properly,
	 * BM hardware expects buf भव address to be placed in the
	 * first four bytes of mapped buffer.
	 */
	*(u32 *)buf = (u32)buf;
	phys_addr = dma_map_single(&priv->pdev->dev, buf, bm_pool->buf_size,
				   DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(&priv->pdev->dev, phys_addr)))
		वापस -ENOMEM;

	mvneta_bm_pool_put_bp(priv, bm_pool, phys_addr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mvneta_bm_स्थिरruct);

/* Create pool */
अटल पूर्णांक mvneta_bm_pool_create(काष्ठा mvneta_bm *priv,
				 काष्ठा mvneta_bm_pool *bm_pool)
अणु
	काष्ठा platक्रमm_device *pdev = priv->pdev;
	u8 target_id, attr;
	पूर्णांक size_bytes, err;
	size_bytes = माप(u32) * bm_pool->hwbm_pool.size;
	bm_pool->virt_addr = dma_alloc_coherent(&pdev->dev, size_bytes,
						&bm_pool->phys_addr,
						GFP_KERNEL);
	अगर (!bm_pool->virt_addr)
		वापस -ENOMEM;

	अगर (!IS_ALIGNED((u32)bm_pool->virt_addr, MVNETA_BM_POOL_PTR_ALIGN)) अणु
		dma_मुक्त_coherent(&pdev->dev, size_bytes, bm_pool->virt_addr,
				  bm_pool->phys_addr);
		dev_err(&pdev->dev, "BM pool %d is not %d bytes aligned\n",
			bm_pool->id, MVNETA_BM_POOL_PTR_ALIGN);
		वापस -ENOMEM;
	पूर्ण

	err = mvebu_mbus_get_dram_win_info(bm_pool->phys_addr, &target_id,
					   &attr);
	अगर (err < 0) अणु
		dma_मुक्त_coherent(&pdev->dev, size_bytes, bm_pool->virt_addr,
				  bm_pool->phys_addr);
		वापस err;
	पूर्ण

	/* Set pool address */
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_POOL_BASE_REG(bm_pool->id),
			bm_pool->phys_addr);

	mvneta_bm_pool_target_set(priv, bm_pool->id, target_id,  attr);
	mvneta_bm_pool_enable(priv, bm_pool->id);

	वापस 0;
पूर्ण

/* Notअगरy the driver that BM pool is being used as specअगरic type and वापस the
 * pool poपूर्णांकer on success
 */
काष्ठा mvneta_bm_pool *mvneta_bm_pool_use(काष्ठा mvneta_bm *priv, u8 pool_id,
					  क्रमागत mvneta_bm_type type, u8 port_id,
					  पूर्णांक pkt_size)
अणु
	काष्ठा mvneta_bm_pool *new_pool = &priv->bm_pools[pool_id];
	पूर्णांक num, err;

	अगर (new_pool->type == MVNETA_BM_LONG &&
	    new_pool->port_map != 1 << port_id) अणु
		dev_err(&priv->pdev->dev,
			"long pool cannot be shared by the ports\n");
		वापस शून्य;
	पूर्ण

	अगर (new_pool->type == MVNETA_BM_SHORT && new_pool->type != type) अणु
		dev_err(&priv->pdev->dev,
			"mixing pools' types between the ports is forbidden\n");
		वापस शून्य;
	पूर्ण

	अगर (new_pool->pkt_size == 0 || type != MVNETA_BM_SHORT)
		new_pool->pkt_size = pkt_size;

	/* Allocate buffers in हाल BM pool hasn't been used yet */
	अगर (new_pool->type == MVNETA_BM_FREE) अणु
		काष्ठा hwbm_pool *hwbm_pool = &new_pool->hwbm_pool;

		new_pool->priv = priv;
		new_pool->type = type;
		new_pool->buf_size = MVNETA_RX_BUF_SIZE(new_pool->pkt_size);
		hwbm_pool->frag_size =
			SKB_DATA_ALIGN(MVNETA_RX_BUF_SIZE(new_pool->pkt_size)) +
			SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
		hwbm_pool->स्थिरruct = mvneta_bm_स्थिरruct;
		hwbm_pool->priv = new_pool;
		mutex_init(&hwbm_pool->buf_lock);

		/* Create new pool */
		err = mvneta_bm_pool_create(priv, new_pool);
		अगर (err) अणु
			dev_err(&priv->pdev->dev, "fail to create pool %d\n",
				new_pool->id);
			वापस शून्य;
		पूर्ण

		/* Allocate buffers क्रम this pool */
		num = hwbm_pool_add(hwbm_pool, hwbm_pool->size);
		अगर (num != hwbm_pool->size) अणु
			WARN(1, "pool %d: %d of %d allocated\n",
			     new_pool->id, num, hwbm_pool->size);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस new_pool;
पूर्ण
EXPORT_SYMBOL_GPL(mvneta_bm_pool_use);

/* Free all buffers from the pool */
व्योम mvneta_bm_bufs_मुक्त(काष्ठा mvneta_bm *priv, काष्ठा mvneta_bm_pool *bm_pool,
			 u8 port_map)
अणु
	पूर्णांक i;

	bm_pool->port_map &= ~port_map;
	अगर (bm_pool->port_map)
		वापस;

	mvneta_bm_config_set(priv, MVNETA_BM_EMPTY_LIMIT_MASK);

	क्रम (i = 0; i < bm_pool->hwbm_pool.buf_num; i++) अणु
		dma_addr_t buf_phys_addr;
		u32 *vaddr;

		/* Get buffer physical address (indirect access) */
		buf_phys_addr = mvneta_bm_pool_get_bp(priv, bm_pool);

		/* Work-around to the problems when destroying the pool,
		 * when it occurs that a पढ़ो access to BPPI वापसs 0.
		 */
		अगर (buf_phys_addr == 0)
			जारी;

		vaddr = phys_to_virt(buf_phys_addr);
		अगर (!vaddr)
			अवरोध;

		dma_unmap_single(&priv->pdev->dev, buf_phys_addr,
				 bm_pool->buf_size, DMA_FROM_DEVICE);
		hwbm_buf_मुक्त(&bm_pool->hwbm_pool, vaddr);
	पूर्ण

	mvneta_bm_config_clear(priv, MVNETA_BM_EMPTY_LIMIT_MASK);

	/* Update BM driver with number of buffers हटाओd from pool */
	bm_pool->hwbm_pool.buf_num -= i;
पूर्ण
EXPORT_SYMBOL_GPL(mvneta_bm_bufs_मुक्त);

/* Cleanup pool */
व्योम mvneta_bm_pool_destroy(काष्ठा mvneta_bm *priv,
			    काष्ठा mvneta_bm_pool *bm_pool, u8 port_map)
अणु
	काष्ठा hwbm_pool *hwbm_pool = &bm_pool->hwbm_pool;
	bm_pool->port_map &= ~port_map;
	अगर (bm_pool->port_map)
		वापस;

	bm_pool->type = MVNETA_BM_FREE;

	mvneta_bm_bufs_मुक्त(priv, bm_pool, port_map);
	अगर (hwbm_pool->buf_num)
		WARN(1, "cannot free all buffers in pool %d\n", bm_pool->id);

	अगर (bm_pool->virt_addr) अणु
		dma_मुक्त_coherent(&priv->pdev->dev,
				  माप(u32) * hwbm_pool->size,
				  bm_pool->virt_addr, bm_pool->phys_addr);
		bm_pool->virt_addr = शून्य;
	पूर्ण

	mvneta_bm_pool_disable(priv, bm_pool->id);
पूर्ण
EXPORT_SYMBOL_GPL(mvneta_bm_pool_destroy);

अटल व्योम mvneta_bm_pools_init(काष्ठा mvneta_bm *priv)
अणु
	काष्ठा device_node *dn = priv->pdev->dev.of_node;
	काष्ठा mvneta_bm_pool *bm_pool;
	अक्षर prop[15];
	u32 size;
	पूर्णांक i;

	/* Activate BM unit */
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_COMMAND_REG, MVNETA_BM_START_MASK);

	/* Create all pools with maximum size */
	क्रम (i = 0; i < MVNETA_BM_POOLS_NUM; i++) अणु
		bm_pool = &priv->bm_pools[i];
		bm_pool->id = i;
		bm_pool->type = MVNETA_BM_FREE;

		/* Reset पढ़ो poपूर्णांकer */
		mvneta_bm_ग_लिखो(priv, MVNETA_BM_POOL_READ_PTR_REG(i), 0);

		/* Reset ग_लिखो poपूर्णांकer */
		mvneta_bm_ग_लिखो(priv, MVNETA_BM_POOL_WRITE_PTR_REG(i), 0);

		/* Configure pool size according to DT or use शेष value */
		प्र_लिखो(prop, "pool%d,capacity", i);
		अगर (of_property_पढ़ो_u32(dn, prop, &size)) अणु
			size = MVNETA_BM_POOL_CAP_DEF;
		पूर्ण अन्यथा अगर (size > MVNETA_BM_POOL_CAP_MAX) अणु
			dev_warn(&priv->pdev->dev,
				 "Illegal pool %d capacity %d, set to %d\n",
				 i, size, MVNETA_BM_POOL_CAP_MAX);
			size = MVNETA_BM_POOL_CAP_MAX;
		पूर्ण अन्यथा अगर (size < MVNETA_BM_POOL_CAP_MIN) अणु
			dev_warn(&priv->pdev->dev,
				 "Illegal pool %d capacity %d, set to %d\n",
				 i, size, MVNETA_BM_POOL_CAP_MIN);
			size = MVNETA_BM_POOL_CAP_MIN;
		पूर्ण अन्यथा अगर (!IS_ALIGNED(size, MVNETA_BM_POOL_CAP_ALIGN)) अणु
			dev_warn(&priv->pdev->dev,
				 "Illegal pool %d capacity %d, round to %d\n",
				 i, size, ALIGN(size,
				 MVNETA_BM_POOL_CAP_ALIGN));
			size = ALIGN(size, MVNETA_BM_POOL_CAP_ALIGN);
		पूर्ण
		bm_pool->hwbm_pool.size = size;

		mvneta_bm_ग_लिखो(priv, MVNETA_BM_POOL_SIZE_REG(i),
				bm_pool->hwbm_pool.size);

		/* Obtain custom pkt_size from DT */
		प्र_लिखो(prop, "pool%d,pkt-size", i);
		अगर (of_property_पढ़ो_u32(dn, prop, &bm_pool->pkt_size))
			bm_pool->pkt_size = 0;
	पूर्ण
पूर्ण

अटल व्योम mvneta_bm_शेष_set(काष्ठा mvneta_bm *priv)
अणु
	u32 val;

	/* Mask BM all पूर्णांकerrupts */
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_INTR_MASK_REG, 0);

	/* Clear BM cause रेजिस्टर */
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_INTR_CAUSE_REG, 0);

	/* Set BM configuration रेजिस्टर */
	val = mvneta_bm_पढ़ो(priv, MVNETA_BM_CONFIG_REG);

	/* Reduce MaxInBurstSize from 32 BPs to 16 BPs */
	val &= ~MVNETA_BM_MAX_IN_BURST_SIZE_MASK;
	val |= MVNETA_BM_MAX_IN_BURST_SIZE_16BP;
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_CONFIG_REG, val);
पूर्ण

अटल पूर्णांक mvneta_bm_init(काष्ठा mvneta_bm *priv)
अणु
	mvneta_bm_शेष_set(priv);

	/* Allocate and initialize BM pools काष्ठाures */
	priv->bm_pools = devm_kसुस्मृति(&priv->pdev->dev, MVNETA_BM_POOLS_NUM,
				      माप(काष्ठा mvneta_bm_pool),
				      GFP_KERNEL);
	अगर (!priv->bm_pools)
		वापस -ENOMEM;

	mvneta_bm_pools_init(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक mvneta_bm_get_sram(काष्ठा device_node *dn,
			      काष्ठा mvneta_bm *priv)
अणु
	priv->bppi_pool = of_gen_pool_get(dn, "internal-mem", 0);
	अगर (!priv->bppi_pool)
		वापस -ENOMEM;

	priv->bppi_virt_addr = gen_pool_dma_alloc(priv->bppi_pool,
						  MVNETA_BM_BPPI_SIZE,
						  &priv->bppi_phys_addr);
	अगर (!priv->bppi_virt_addr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम mvneta_bm_put_sram(काष्ठा mvneta_bm *priv)
अणु
	gen_pool_मुक्त(priv->bppi_pool, priv->bppi_phys_addr,
		      MVNETA_BM_BPPI_SIZE);
पूर्ण

काष्ठा mvneta_bm *mvneta_bm_get(काष्ठा device_node *node)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(node);

	वापस pdev ? platक्रमm_get_drvdata(pdev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(mvneta_bm_get);

व्योम mvneta_bm_put(काष्ठा mvneta_bm *priv)
अणु
	platक्रमm_device_put(priv->pdev);
पूर्ण
EXPORT_SYMBOL_GPL(mvneta_bm_put);

अटल पूर्णांक mvneta_bm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *dn = pdev->dev.of_node;
	काष्ठा mvneta_bm *priv;
	पूर्णांक err;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा mvneta_bm), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->reg_base))
		वापस PTR_ERR(priv->reg_base);

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);
	err = clk_prepare_enable(priv->clk);
	अगर (err < 0)
		वापस err;

	err = mvneta_bm_get_sram(dn, priv);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to allocate internal memory\n");
		जाओ err_clk;
	पूर्ण

	priv->pdev = pdev;

	/* Initialize buffer manager पूर्णांकernals */
	err = mvneta_bm_init(priv);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to initialize controller\n");
		जाओ err_sram;
	पूर्ण

	dn->data = priv;
	platक्रमm_set_drvdata(pdev, priv);

	dev_info(&pdev->dev, "Buffer Manager for network controller enabled\n");

	वापस 0;

err_sram:
	mvneta_bm_put_sram(priv);
err_clk:
	clk_disable_unprepare(priv->clk);
	वापस err;
पूर्ण

अटल पूर्णांक mvneta_bm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvneta_bm *priv = platक्रमm_get_drvdata(pdev);
	u8 all_ports_map = 0xff;
	पूर्णांक i = 0;

	क्रम (i = 0; i < MVNETA_BM_POOLS_NUM; i++) अणु
		काष्ठा mvneta_bm_pool *bm_pool = &priv->bm_pools[i];

		mvneta_bm_pool_destroy(priv, bm_pool, all_ports_map);
	पूर्ण

	mvneta_bm_put_sram(priv);

	/* Dectivate BM unit */
	mvneta_bm_ग_लिखो(priv, MVNETA_BM_COMMAND_REG, MVNETA_BM_STOP_MASK);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mvneta_bm_match[] = अणु
	अणु .compatible = "marvell,armada-380-neta-bm" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mvneta_bm_match);

अटल काष्ठा platक्रमm_driver mvneta_bm_driver = अणु
	.probe = mvneta_bm_probe,
	.हटाओ = mvneta_bm_हटाओ,
	.driver = अणु
		.name = MVNETA_BM_DRIVER_NAME,
		.of_match_table = mvneta_bm_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mvneta_bm_driver);

MODULE_DESCRIPTION("Marvell NETA Buffer Manager Driver - www.marvell.com");
MODULE_AUTHOR("Marcin Wojtas <mw@semihalf.com>");
MODULE_LICENSE("GPL v2");
