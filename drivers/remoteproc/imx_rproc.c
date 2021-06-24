<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Pengutronix, Oleksij Rempel <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/workqueue.h>

#समावेश "remoteproc_internal.h"

#घोषणा IMX7D_SRC_SCR			0x0C
#घोषणा IMX7D_ENABLE_M4			BIT(3)
#घोषणा IMX7D_SW_M4P_RST		BIT(2)
#घोषणा IMX7D_SW_M4C_RST		BIT(1)
#घोषणा IMX7D_SW_M4C_NON_SCLR_RST	BIT(0)

#घोषणा IMX7D_M4_RST_MASK		(IMX7D_ENABLE_M4 | IMX7D_SW_M4P_RST \
					 | IMX7D_SW_M4C_RST \
					 | IMX7D_SW_M4C_NON_SCLR_RST)

#घोषणा IMX7D_M4_START			(IMX7D_ENABLE_M4 | IMX7D_SW_M4P_RST \
					 | IMX7D_SW_M4C_RST)
#घोषणा IMX7D_M4_STOP			IMX7D_SW_M4C_NON_SCLR_RST

/* Address: 0x020D8000 */
#घोषणा IMX6SX_SRC_SCR			0x00
#घोषणा IMX6SX_ENABLE_M4		BIT(22)
#घोषणा IMX6SX_SW_M4P_RST		BIT(12)
#घोषणा IMX6SX_SW_M4C_NON_SCLR_RST	BIT(4)
#घोषणा IMX6SX_SW_M4C_RST		BIT(3)

#घोषणा IMX6SX_M4_START			(IMX6SX_ENABLE_M4 | IMX6SX_SW_M4P_RST \
					 | IMX6SX_SW_M4C_RST)
#घोषणा IMX6SX_M4_STOP			IMX6SX_SW_M4C_NON_SCLR_RST
#घोषणा IMX6SX_M4_RST_MASK		(IMX6SX_ENABLE_M4 | IMX6SX_SW_M4P_RST \
					 | IMX6SX_SW_M4C_NON_SCLR_RST \
					 | IMX6SX_SW_M4C_RST)

#घोषणा IMX_RPROC_MEM_MAX		32

/**
 * काष्ठा imx_rproc_mem - slim पूर्णांकernal memory काष्ठाure
 * @cpu_addr: MPU भव address of the memory region
 * @sys_addr: Bus address used to access the memory region
 * @size: Size of the memory region
 */
काष्ठा imx_rproc_mem अणु
	व्योम __iomem *cpu_addr;
	phys_addr_t sys_addr;
	माप_प्रकार size;
पूर्ण;

/* att flags */
/* M4 own area. Can be mapped at probe */
#घोषणा ATT_OWN		BIT(1)

/* address translation table */
काष्ठा imx_rproc_att अणु
	u32 da;	/* device address (From Cortex M4 view)*/
	u32 sa;	/* प्रणाली bus address */
	u32 size; /* size of reg range */
	पूर्णांक flags;
पूर्ण;

काष्ठा imx_rproc_dcfg अणु
	u32				src_reg;
	u32				src_mask;
	u32				src_start;
	u32				src_stop;
	स्थिर काष्ठा imx_rproc_att	*att;
	माप_प्रकार				att_size;
पूर्ण;

काष्ठा imx_rproc अणु
	काष्ठा device			*dev;
	काष्ठा regmap			*regmap;
	काष्ठा rproc			*rproc;
	स्थिर काष्ठा imx_rproc_dcfg	*dcfg;
	काष्ठा imx_rproc_mem		mem[IMX_RPROC_MEM_MAX];
	काष्ठा clk			*clk;
	काष्ठा mbox_client		cl;
	काष्ठा mbox_chan		*tx_ch;
	काष्ठा mbox_chan		*rx_ch;
	काष्ठा work_काष्ठा		rproc_work;
	काष्ठा workqueue_काष्ठा		*workqueue;
	व्योम __iomem			*rsc_table;
पूर्ण;

अटल स्थिर काष्ठा imx_rproc_att imx_rproc_att_imx8mq[] = अणु
	/* dev addr , sys addr  , size	    , flags */
	/* TCML - alias */
	अणु 0x00000000, 0x007e0000, 0x00020000, 0 पूर्ण,
	/* OCRAM_S */
	अणु 0x00180000, 0x00180000, 0x00008000, 0 पूर्ण,
	/* OCRAM */
	अणु 0x00900000, 0x00900000, 0x00020000, 0 पूर्ण,
	/* OCRAM */
	अणु 0x00920000, 0x00920000, 0x00020000, 0 पूर्ण,
	/* QSPI Code - alias */
	अणु 0x08000000, 0x08000000, 0x08000000, 0 पूर्ण,
	/* DDR (Code) - alias */
	अणु 0x10000000, 0x80000000, 0x0FFE0000, 0 पूर्ण,
	/* TCML */
	अणु 0x1FFE0000, 0x007E0000, 0x00020000, ATT_OWN पूर्ण,
	/* TCMU */
	अणु 0x20000000, 0x00800000, 0x00020000, ATT_OWN पूर्ण,
	/* OCRAM_S */
	अणु 0x20180000, 0x00180000, 0x00008000, ATT_OWN पूर्ण,
	/* OCRAM */
	अणु 0x20200000, 0x00900000, 0x00020000, ATT_OWN पूर्ण,
	/* OCRAM */
	अणु 0x20220000, 0x00920000, 0x00020000, ATT_OWN पूर्ण,
	/* DDR (Data) */
	अणु 0x40000000, 0x40000000, 0x80000000, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx_rproc_att imx_rproc_att_imx7d[] = अणु
	/* dev addr , sys addr  , size	    , flags */
	/* OCRAM_S (M4 Boot code) - alias */
	अणु 0x00000000, 0x00180000, 0x00008000, 0 पूर्ण,
	/* OCRAM_S (Code) */
	अणु 0x00180000, 0x00180000, 0x00008000, ATT_OWN पूर्ण,
	/* OCRAM (Code) - alias */
	अणु 0x00900000, 0x00900000, 0x00020000, 0 पूर्ण,
	/* OCRAM_EPDC (Code) - alias */
	अणु 0x00920000, 0x00920000, 0x00020000, 0 पूर्ण,
	/* OCRAM_PXP (Code) - alias */
	अणु 0x00940000, 0x00940000, 0x00008000, 0 पूर्ण,
	/* TCML (Code) */
	अणु 0x1FFF8000, 0x007F8000, 0x00008000, ATT_OWN पूर्ण,
	/* DDR (Code) - alias, first part of DDR (Data) */
	अणु 0x10000000, 0x80000000, 0x0FFF0000, 0 पूर्ण,

	/* TCMU (Data) */
	अणु 0x20000000, 0x00800000, 0x00008000, ATT_OWN पूर्ण,
	/* OCRAM (Data) */
	अणु 0x20200000, 0x00900000, 0x00020000, 0 पूर्ण,
	/* OCRAM_EPDC (Data) */
	अणु 0x20220000, 0x00920000, 0x00020000, 0 पूर्ण,
	/* OCRAM_PXP (Data) */
	अणु 0x20240000, 0x00940000, 0x00008000, 0 पूर्ण,
	/* DDR (Data) */
	अणु 0x80000000, 0x80000000, 0x60000000, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx_rproc_att imx_rproc_att_imx6sx[] = अणु
	/* dev addr , sys addr  , size	    , flags */
	/* TCML (M4 Boot Code) - alias */
	अणु 0x00000000, 0x007F8000, 0x00008000, 0 पूर्ण,
	/* OCRAM_S (Code) */
	अणु 0x00180000, 0x008F8000, 0x00004000, 0 पूर्ण,
	/* OCRAM_S (Code) - alias */
	अणु 0x00180000, 0x008FC000, 0x00004000, 0 पूर्ण,
	/* TCML (Code) */
	अणु 0x1FFF8000, 0x007F8000, 0x00008000, ATT_OWN पूर्ण,
	/* DDR (Code) - alias, first part of DDR (Data) */
	अणु 0x10000000, 0x80000000, 0x0FFF8000, 0 पूर्ण,

	/* TCMU (Data) */
	अणु 0x20000000, 0x00800000, 0x00008000, ATT_OWN पूर्ण,
	/* OCRAM_S (Data) - alias? */
	अणु 0x208F8000, 0x008F8000, 0x00004000, 0 पूर्ण,
	/* DDR (Data) */
	अणु 0x80000000, 0x80000000, 0x60000000, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx_rproc_dcfg imx_rproc_cfg_imx8mq = अणु
	.src_reg	= IMX7D_SRC_SCR,
	.src_mask	= IMX7D_M4_RST_MASK,
	.src_start	= IMX7D_M4_START,
	.src_stop	= IMX7D_M4_STOP,
	.att		= imx_rproc_att_imx8mq,
	.att_size	= ARRAY_SIZE(imx_rproc_att_imx8mq),
पूर्ण;

अटल स्थिर काष्ठा imx_rproc_dcfg imx_rproc_cfg_imx7d = अणु
	.src_reg	= IMX7D_SRC_SCR,
	.src_mask	= IMX7D_M4_RST_MASK,
	.src_start	= IMX7D_M4_START,
	.src_stop	= IMX7D_M4_STOP,
	.att		= imx_rproc_att_imx7d,
	.att_size	= ARRAY_SIZE(imx_rproc_att_imx7d),
पूर्ण;

अटल स्थिर काष्ठा imx_rproc_dcfg imx_rproc_cfg_imx6sx = अणु
	.src_reg	= IMX6SX_SRC_SCR,
	.src_mask	= IMX6SX_M4_RST_MASK,
	.src_start	= IMX6SX_M4_START,
	.src_stop	= IMX6SX_M4_STOP,
	.att		= imx_rproc_att_imx6sx,
	.att_size	= ARRAY_SIZE(imx_rproc_att_imx6sx),
पूर्ण;

अटल पूर्णांक imx_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा imx_rproc *priv = rproc->priv;
	स्थिर काष्ठा imx_rproc_dcfg *dcfg = priv->dcfg;
	काष्ठा device *dev = priv->dev;
	पूर्णांक ret;

	ret = regmap_update_bits(priv->regmap, dcfg->src_reg,
				 dcfg->src_mask, dcfg->src_start);
	अगर (ret)
		dev_err(dev, "Failed to enable M4!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक imx_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा imx_rproc *priv = rproc->priv;
	स्थिर काष्ठा imx_rproc_dcfg *dcfg = priv->dcfg;
	काष्ठा device *dev = priv->dev;
	पूर्णांक ret;

	ret = regmap_update_bits(priv->regmap, dcfg->src_reg,
				 dcfg->src_mask, dcfg->src_stop);
	अगर (ret)
		dev_err(dev, "Failed to stop M4!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक imx_rproc_da_to_sys(काष्ठा imx_rproc *priv, u64 da,
			       माप_प्रकार len, u64 *sys)
अणु
	स्थिर काष्ठा imx_rproc_dcfg *dcfg = priv->dcfg;
	पूर्णांक i;

	/* parse address translation table */
	क्रम (i = 0; i < dcfg->att_size; i++) अणु
		स्थिर काष्ठा imx_rproc_att *att = &dcfg->att[i];

		अगर (da >= att->da && da + len < att->da + att->size) अणु
			अचिन्हित पूर्णांक offset = da - att->da;

			*sys = att->sa + offset;
			वापस 0;
		पूर्ण
	पूर्ण

	dev_warn(priv->dev, "Translation failed: da = 0x%llx len = 0x%zx\n",
		 da, len);
	वापस -ENOENT;
पूर्ण

अटल व्योम *imx_rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा imx_rproc *priv = rproc->priv;
	व्योम *va = शून्य;
	u64 sys;
	पूर्णांक i;

	अगर (len == 0)
		वापस शून्य;

	/*
	 * On device side we have many aliases, so we need to convert device
	 * address (M4) to प्रणाली bus address first.
	 */
	अगर (imx_rproc_da_to_sys(priv, da, len, &sys))
		वापस शून्य;

	क्रम (i = 0; i < IMX_RPROC_MEM_MAX; i++) अणु
		अगर (sys >= priv->mem[i].sys_addr && sys + len <
		    priv->mem[i].sys_addr +  priv->mem[i].size) अणु
			अचिन्हित पूर्णांक offset = sys - priv->mem[i].sys_addr;
			/* __क्रमce to make sparse happy with type conversion */
			va = (__क्रमce व्योम *)(priv->mem[i].cpu_addr + offset);
			अवरोध;
		पूर्ण
	पूर्ण

	dev_dbg(&rproc->dev, "da = 0x%llx len = 0x%zx va = 0x%p\n",
		da, len, va);

	वापस va;
पूर्ण

अटल पूर्णांक imx_rproc_mem_alloc(काष्ठा rproc *rproc,
			       काष्ठा rproc_mem_entry *mem)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	व्योम *va;

	dev_dbg(dev, "map memory: %p+%zx\n", &mem->dma, mem->len);
	va = ioremap_wc(mem->dma, mem->len);
	अगर (IS_ERR_OR_शून्य(va)) अणु
		dev_err(dev, "Unable to map memory region: %p+%zx\n",
			&mem->dma, mem->len);
		वापस -ENOMEM;
	पूर्ण

	/* Update memory entry va */
	mem->va = va;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_rproc_mem_release(काष्ठा rproc *rproc,
				 काष्ठा rproc_mem_entry *mem)
अणु
	dev_dbg(rproc->dev.parent, "unmap memory: %pa\n", &mem->dma);
	iounmap(mem->va);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_rproc_prepare(काष्ठा rproc *rproc)
अणु
	काष्ठा imx_rproc *priv = rproc->priv;
	काष्ठा device_node *np = priv->dev->of_node;
	काष्ठा of_phandle_iterator it;
	काष्ठा rproc_mem_entry *mem;
	काष्ठा reserved_mem *rmem;
	u32 da;

	/* Register associated reserved memory regions */
	of_phandle_iterator_init(&it, np, "memory-region", शून्य, 0);
	जबतक (of_phandle_iterator_next(&it) == 0) अणु
		/*
		 * Ignore the first memory region which will be used vdev buffer.
		 * No need to करो extra handlings, rproc_add_virtio_dev will handle it.
		 */
		अगर (!म_भेद(it.node->name, "vdev0buffer"))
			जारी;

		rmem = of_reserved_mem_lookup(it.node);
		अगर (!rmem) अणु
			dev_err(priv->dev, "unable to acquire memory-region\n");
			वापस -EINVAL;
		पूर्ण

		/* No need to translate pa to da, i.MX use same map */
		da = rmem->base;

		/* Register memory region */
		mem = rproc_mem_entry_init(priv->dev, शून्य, (dma_addr_t)rmem->base, rmem->size, da,
					   imx_rproc_mem_alloc, imx_rproc_mem_release,
					   it.node->name);

		अगर (mem)
			rproc_coredump_add_segment(rproc, da, rmem->size);
		अन्यथा
			वापस -ENOMEM;

		rproc_add_carveout(rproc, mem);
	पूर्ण

	वापस  0;
पूर्ण

अटल पूर्णांक imx_rproc_parse_fw(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret;

	ret = rproc_elf_load_rsc_table(rproc, fw);
	अगर (ret)
		dev_info(&rproc->dev, "No resource table in elf\n");

	वापस 0;
पूर्ण

अटल व्योम imx_rproc_kick(काष्ठा rproc *rproc, पूर्णांक vqid)
अणु
	काष्ठा imx_rproc *priv = rproc->priv;
	पूर्णांक err;
	__u32 mmsg;

	अगर (!priv->tx_ch) अणु
		dev_err(priv->dev, "No initialized mbox tx channel\n");
		वापस;
	पूर्ण

	/*
	 * Send the index of the triggered virtqueue as the mu payload.
	 * Let remote processor know which virtqueue is used.
	 */
	mmsg = vqid << 16;

	err = mbox_send_message(priv->tx_ch, (व्योम *)&mmsg);
	अगर (err < 0)
		dev_err(priv->dev, "%s: failed (%d, err:%d)\n",
			__func__, vqid, err);
पूर्ण

अटल पूर्णांक imx_rproc_attach(काष्ठा rproc *rproc)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा resource_table *imx_rproc_get_loaded_rsc_table(काष्ठा rproc *rproc, माप_प्रकार *table_sz)
अणु
	काष्ठा imx_rproc *priv = rproc->priv;

	/* The resource table has alपढ़ोy been mapped in imx_rproc_addr_init */
	अगर (!priv->rsc_table)
		वापस शून्य;

	*table_sz = SZ_1K;
	वापस (काष्ठा resource_table *)priv->rsc_table;
पूर्ण

अटल स्थिर काष्ठा rproc_ops imx_rproc_ops = अणु
	.prepare	= imx_rproc_prepare,
	.attach		= imx_rproc_attach,
	.start		= imx_rproc_start,
	.stop		= imx_rproc_stop,
	.kick		= imx_rproc_kick,
	.da_to_va       = imx_rproc_da_to_va,
	.load		= rproc_elf_load_segments,
	.parse_fw	= imx_rproc_parse_fw,
	.find_loaded_rsc_table = rproc_elf_find_loaded_rsc_table,
	.get_loaded_rsc_table = imx_rproc_get_loaded_rsc_table,
	.sanity_check	= rproc_elf_sanity_check,
	.get_boot_addr	= rproc_elf_get_boot_addr,
पूर्ण;

अटल पूर्णांक imx_rproc_addr_init(काष्ठा imx_rproc *priv,
			       काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा imx_rproc_dcfg *dcfg = priv->dcfg;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक a, b = 0, err, nph;

	/* remap required addresses */
	क्रम (a = 0; a < dcfg->att_size; a++) अणु
		स्थिर काष्ठा imx_rproc_att *att = &dcfg->att[a];

		अगर (!(att->flags & ATT_OWN))
			जारी;

		अगर (b >= IMX_RPROC_MEM_MAX)
			अवरोध;

		priv->mem[b].cpu_addr = devm_ioremap(&pdev->dev,
						     att->sa, att->size);
		अगर (!priv->mem[b].cpu_addr) अणु
			dev_err(dev, "failed to remap %#x bytes from %#x\n", att->size, att->sa);
			वापस -ENOMEM;
		पूर्ण
		priv->mem[b].sys_addr = att->sa;
		priv->mem[b].size = att->size;
		b++;
	पूर्ण

	/* memory-region is optional property */
	nph = of_count_phandle_with_args(np, "memory-region", शून्य);
	अगर (nph <= 0)
		वापस 0;

	/* remap optional addresses */
	क्रम (a = 0; a < nph; a++) अणु
		काष्ठा device_node *node;
		काष्ठा resource res;

		node = of_parse_phandle(np, "memory-region", a);
		/* Not map vdev region */
		अगर (!म_भेद(node->name, "vdev"))
			जारी;
		err = of_address_to_resource(node, 0, &res);
		अगर (err) अणु
			dev_err(dev, "unable to resolve memory region\n");
			वापस err;
		पूर्ण

		of_node_put(node);

		अगर (b >= IMX_RPROC_MEM_MAX)
			अवरोध;

		/* Not use resource version, because we might share region */
		priv->mem[b].cpu_addr = devm_ioremap(&pdev->dev, res.start, resource_size(&res));
		अगर (!priv->mem[b].cpu_addr) अणु
			dev_err(dev, "failed to remap %pr\n", &res);
			वापस -ENOMEM;
		पूर्ण
		priv->mem[b].sys_addr = res.start;
		priv->mem[b].size = resource_size(&res);
		अगर (!म_भेद(node->name, "rsc_table"))
			priv->rsc_table = priv->mem[b].cpu_addr;
		b++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx_rproc_vq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा imx_rproc *priv = container_of(work, काष्ठा imx_rproc,
					      rproc_work);

	rproc_vq_पूर्णांकerrupt(priv->rproc, 0);
	rproc_vq_पूर्णांकerrupt(priv->rproc, 1);
पूर्ण

अटल व्योम imx_rproc_rx_callback(काष्ठा mbox_client *cl, व्योम *msg)
अणु
	काष्ठा rproc *rproc = dev_get_drvdata(cl->dev);
	काष्ठा imx_rproc *priv = rproc->priv;

	queue_work(priv->workqueue, &priv->rproc_work);
पूर्ण

अटल पूर्णांक imx_rproc_xtr_mbox_init(काष्ठा rproc *rproc)
अणु
	काष्ठा imx_rproc *priv = rproc->priv;
	काष्ठा device *dev = priv->dev;
	काष्ठा mbox_client *cl;
	पूर्णांक ret;

	अगर (!of_get_property(dev->of_node, "mbox-names", शून्य))
		वापस 0;

	cl = &priv->cl;
	cl->dev = dev;
	cl->tx_block = true;
	cl->tx_tout = 100;
	cl->knows_txकरोne = false;
	cl->rx_callback = imx_rproc_rx_callback;

	priv->tx_ch = mbox_request_channel_byname(cl, "tx");
	अगर (IS_ERR(priv->tx_ch)) अणु
		ret = PTR_ERR(priv->tx_ch);
		वापस dev_err_probe(cl->dev, ret,
				     "failed to request tx mailbox channel: %d\n", ret);
	पूर्ण

	priv->rx_ch = mbox_request_channel_byname(cl, "rx");
	अगर (IS_ERR(priv->rx_ch)) अणु
		mbox_मुक्त_channel(priv->tx_ch);
		ret = PTR_ERR(priv->rx_ch);
		वापस dev_err_probe(cl->dev, ret,
				     "failed to request rx mailbox channel: %d\n", ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx_rproc_मुक्त_mbox(काष्ठा rproc *rproc)
अणु
	काष्ठा imx_rproc *priv = rproc->priv;

	mbox_मुक्त_channel(priv->tx_ch);
	mbox_मुक्त_channel(priv->rx_ch);
पूर्ण

अटल पूर्णांक imx_rproc_detect_mode(काष्ठा imx_rproc *priv)
अणु
	स्थिर काष्ठा imx_rproc_dcfg *dcfg = priv->dcfg;
	काष्ठा device *dev = priv->dev;
	पूर्णांक ret;
	u32 val;

	ret = regmap_पढ़ो(priv->regmap, dcfg->src_reg, &val);
	अगर (ret) अणु
		dev_err(dev, "Failed to read src\n");
		वापस ret;
	पूर्ण

	अगर (!(val & dcfg->src_stop))
		priv->rproc->state = RPROC_DETACHED;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा imx_rproc *priv;
	काष्ठा rproc *rproc;
	काष्ठा regmap_config config = अणु .name = "imx-rproc" पूर्ण;
	स्थिर काष्ठा imx_rproc_dcfg *dcfg;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = syscon_regmap_lookup_by_phandle(np, "syscon");
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to find syscon\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	regmap_attach_dev(dev, regmap, &config);

	/* set some other name then imx */
	rproc = rproc_alloc(dev, "imx-rproc", &imx_rproc_ops,
			    शून्य, माप(*priv));
	अगर (!rproc)
		वापस -ENOMEM;

	dcfg = of_device_get_match_data(dev);
	अगर (!dcfg) अणु
		ret = -EINVAL;
		जाओ err_put_rproc;
	पूर्ण

	priv = rproc->priv;
	priv->rproc = rproc;
	priv->regmap = regmap;
	priv->dcfg = dcfg;
	priv->dev = dev;

	dev_set_drvdata(dev, rproc);
	priv->workqueue = create_workqueue(dev_name(dev));
	अगर (!priv->workqueue) अणु
		dev_err(dev, "cannot create workqueue\n");
		ret = -ENOMEM;
		जाओ err_put_rproc;
	पूर्ण

	ret = imx_rproc_xtr_mbox_init(rproc);
	अगर (ret)
		जाओ err_put_wkq;

	ret = imx_rproc_addr_init(priv, pdev);
	अगर (ret) अणु
		dev_err(dev, "failed on imx_rproc_addr_init\n");
		जाओ err_put_mbox;
	पूर्ण

	ret = imx_rproc_detect_mode(priv);
	अगर (ret)
		जाओ err_put_mbox;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "Failed to get clock\n");
		ret = PTR_ERR(priv->clk);
		जाओ err_put_mbox;
	पूर्ण

	/*
	 * clk क्रम M4 block including memory. Should be
	 * enabled beक्रमe .start क्रम FW transfer.
	 */
	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(&rproc->dev, "Failed to enable clock\n");
		जाओ err_put_mbox;
	पूर्ण

	INIT_WORK(&priv->rproc_work, imx_rproc_vq_work);

	ret = rproc_add(rproc);
	अगर (ret) अणु
		dev_err(dev, "rproc_add failed\n");
		जाओ err_put_clk;
	पूर्ण

	वापस 0;

err_put_clk:
	clk_disable_unprepare(priv->clk);
err_put_mbox:
	imx_rproc_मुक्त_mbox(rproc);
err_put_wkq:
	destroy_workqueue(priv->workqueue);
err_put_rproc:
	rproc_मुक्त(rproc);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_rproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);
	काष्ठा imx_rproc *priv = rproc->priv;

	clk_disable_unprepare(priv->clk);
	rproc_del(rproc);
	imx_rproc_मुक्त_mbox(rproc);
	rproc_मुक्त(rproc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_rproc_of_match[] = अणु
	अणु .compatible = "fsl,imx7d-cm4", .data = &imx_rproc_cfg_imx7d पूर्ण,
	अणु .compatible = "fsl,imx6sx-cm4", .data = &imx_rproc_cfg_imx6sx पूर्ण,
	अणु .compatible = "fsl,imx8mq-cm4", .data = &imx_rproc_cfg_imx8mq पूर्ण,
	अणु .compatible = "fsl,imx8mm-cm4", .data = &imx_rproc_cfg_imx8mq पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_rproc_of_match);

अटल काष्ठा platक्रमm_driver imx_rproc_driver = अणु
	.probe = imx_rproc_probe,
	.हटाओ = imx_rproc_हटाओ,
	.driver = अणु
		.name = "imx-rproc",
		.of_match_table = imx_rproc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx_rproc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("i.MX remote processor control driver");
MODULE_AUTHOR("Oleksij Rempel <o.rempel@pengutronix.de>");
