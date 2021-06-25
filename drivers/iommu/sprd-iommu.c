<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Unisoc IOMMU driver
 *
 * Copyright (C) 2020 Unisoc, Inc.
 * Author: Chunyan Zhang <chunyan.zhang@unisoc.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/iommu.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा SPRD_IOMMU_PAGE_SHIFT	12
#घोषणा SPRD_IOMMU_PAGE_SIZE	SZ_4K

#घोषणा SPRD_EX_CFG		0x0
#घोषणा SPRD_IOMMU_VAOR_BYPASS	BIT(4)
#घोषणा SPRD_IOMMU_GATE_EN	BIT(1)
#घोषणा SPRD_IOMMU_EN		BIT(0)
#घोषणा SPRD_EX_UPDATE		0x4
#घोषणा SPRD_EX_FIRST_VPN	0x8
#घोषणा SPRD_EX_VPN_RANGE	0xc
#घोषणा SPRD_EX_FIRST_PPN	0x10
#घोषणा SPRD_EX_DEFAULT_PPN	0x14

#घोषणा SPRD_IOMMU_VERSION	0x0
#घोषणा SPRD_VERSION_MASK	GENMASK(15, 8)
#घोषणा SPRD_VERSION_SHIFT	0x8
#घोषणा SPRD_VAU_CFG		0x4
#घोषणा SPRD_VAU_UPDATE		0x8
#घोषणा SPRD_VAU_AUTH_CFG	0xc
#घोषणा SPRD_VAU_FIRST_PPN	0x10
#घोषणा SPRD_VAU_DEFAULT_PPN_RD	0x14
#घोषणा SPRD_VAU_DEFAULT_PPN_WR	0x18
#घोषणा SPRD_VAU_FIRST_VPN	0x1c
#घोषणा SPRD_VAU_VPN_RANGE	0x20

क्रमागत sprd_iommu_version अणु
	SPRD_IOMMU_EX,
	SPRD_IOMMU_VAU,
पूर्ण;

/*
 * काष्ठा sprd_iommu_device - high-level sprd IOMMU device representation,
 * including hardware inक्रमmation and configuration, also driver data, etc
 *
 * @ver: sprd IOMMU IP version
 * @prot_page_va: protect page base भव address
 * @prot_page_pa: protect page base physical address, data would be
 *		  written to here जबतक translation fault
 * @base: mapped base address क्रम accessing रेजिस्टरs
 * @dev: poपूर्णांकer to basic device काष्ठाure
 * @iommu: IOMMU core representation
 * @group: IOMMU group
 * @eb: gate घड़ी which controls IOMMU access
 */
काष्ठा sprd_iommu_device अणु
	क्रमागत sprd_iommu_version	ver;
	u32			*prot_page_va;
	dma_addr_t		prot_page_pa;
	व्योम __iomem		*base;
	काष्ठा device		*dev;
	काष्ठा iommu_device	iommu;
	काष्ठा iommu_group	*group;
	काष्ठा clk		*eb;
पूर्ण;

काष्ठा sprd_iommu_करोमुख्य अणु
	spinlock_t		pgtlock; /* lock क्रम page table */
	काष्ठा iommu_करोमुख्य	करोमुख्य;
	u32			*pgt_va; /* page table भव address base */
	dma_addr_t		pgt_pa; /* page table physical address base */
	काष्ठा sprd_iommu_device	*sdev;
पूर्ण;

अटल स्थिर काष्ठा iommu_ops sprd_iommu_ops;

अटल काष्ठा sprd_iommu_करोमुख्य *to_sprd_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा sprd_iommu_करोमुख्य, करोमुख्य);
पूर्ण

अटल अंतरभूत व्योम
sprd_iommu_ग_लिखो(काष्ठा sprd_iommu_device *sdev, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, sdev->base + reg);
पूर्ण

अटल अंतरभूत u32
sprd_iommu_पढ़ो(काष्ठा sprd_iommu_device *sdev, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(sdev->base + reg);
पूर्ण

अटल अंतरभूत व्योम
sprd_iommu_update_bits(काष्ठा sprd_iommu_device *sdev, अचिन्हित पूर्णांक reg,
		  u32 mask, u32 shअगरt, u32 val)
अणु
	u32 t = sprd_iommu_पढ़ो(sdev, reg);

	t = (t & (~(mask << shअगरt))) | ((val & mask) << shअगरt);
	sprd_iommu_ग_लिखो(sdev, reg, t);
पूर्ण

अटल अंतरभूत पूर्णांक
sprd_iommu_get_version(काष्ठा sprd_iommu_device *sdev)
अणु
	पूर्णांक ver = (sprd_iommu_पढ़ो(sdev, SPRD_IOMMU_VERSION) &
		   SPRD_VERSION_MASK) >> SPRD_VERSION_SHIFT;

	चयन (ver) अणु
	हाल SPRD_IOMMU_EX:
	हाल SPRD_IOMMU_VAU:
		वापस ver;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल माप_प्रकार
sprd_iommu_pgt_size(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	वापस ((करोमुख्य->geometry.aperture_end -
		 करोमुख्य->geometry.aperture_start + 1) >>
		SPRD_IOMMU_PAGE_SHIFT) * माप(u32);
पूर्ण

अटल काष्ठा iommu_करोमुख्य *sprd_iommu_करोमुख्य_alloc(अचिन्हित पूर्णांक करोमुख्य_type)
अणु
	काष्ठा sprd_iommu_करोमुख्य *करोm;

	अगर (करोमुख्य_type != IOMMU_DOMAIN_DMA && करोमुख्य_type != IOMMU_DOMAIN_UNMANAGED)
		वापस शून्य;

	करोm = kzalloc(माप(*करोm), GFP_KERNEL);
	अगर (!करोm)
		वापस शून्य;

	अगर (iommu_get_dma_cookie(&करोm->करोमुख्य)) अणु
		kमुक्त(करोm);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&करोm->pgtlock);

	करोm->करोमुख्य.geometry.aperture_start = 0;
	करोm->करोमुख्य.geometry.aperture_end = SZ_256M - 1;

	वापस &करोm->करोमुख्य;
पूर्ण

अटल व्योम sprd_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा sprd_iommu_करोमुख्य *करोm = to_sprd_करोमुख्य(करोमुख्य);

	iommu_put_dma_cookie(करोमुख्य);
	kमुक्त(करोm);
पूर्ण

अटल व्योम sprd_iommu_first_vpn(काष्ठा sprd_iommu_करोमुख्य *करोm)
अणु
	काष्ठा sprd_iommu_device *sdev = करोm->sdev;
	u32 val;
	अचिन्हित पूर्णांक reg;

	अगर (sdev->ver == SPRD_IOMMU_EX)
		reg = SPRD_EX_FIRST_VPN;
	अन्यथा
		reg = SPRD_VAU_FIRST_VPN;

	val = करोm->करोमुख्य.geometry.aperture_start >> SPRD_IOMMU_PAGE_SHIFT;
	sprd_iommu_ग_लिखो(sdev, reg, val);
पूर्ण

अटल व्योम sprd_iommu_vpn_range(काष्ठा sprd_iommu_करोमुख्य *करोm)
अणु
	काष्ठा sprd_iommu_device *sdev = करोm->sdev;
	u32 val;
	अचिन्हित पूर्णांक reg;

	अगर (sdev->ver == SPRD_IOMMU_EX)
		reg = SPRD_EX_VPN_RANGE;
	अन्यथा
		reg = SPRD_VAU_VPN_RANGE;

	val = (करोm->करोमुख्य.geometry.aperture_end -
	       करोm->करोमुख्य.geometry.aperture_start) >> SPRD_IOMMU_PAGE_SHIFT;
	sprd_iommu_ग_लिखो(sdev, reg, val);
पूर्ण

अटल व्योम sprd_iommu_first_ppn(काष्ठा sprd_iommu_करोमुख्य *करोm)
अणु
	u32 val = करोm->pgt_pa >> SPRD_IOMMU_PAGE_SHIFT;
	काष्ठा sprd_iommu_device *sdev = करोm->sdev;
	अचिन्हित पूर्णांक reg;

	अगर (sdev->ver == SPRD_IOMMU_EX)
		reg = SPRD_EX_FIRST_PPN;
	अन्यथा
		reg = SPRD_VAU_FIRST_PPN;

	sprd_iommu_ग_लिखो(sdev, reg, val);
पूर्ण

अटल व्योम sprd_iommu_शेष_ppn(काष्ठा sprd_iommu_device *sdev)
अणु
	u32 val = sdev->prot_page_pa >> SPRD_IOMMU_PAGE_SHIFT;

	अगर (sdev->ver == SPRD_IOMMU_EX) अणु
		sprd_iommu_ग_लिखो(sdev, SPRD_EX_DEFAULT_PPN, val);
	पूर्ण अन्यथा अगर (sdev->ver == SPRD_IOMMU_VAU) अणु
		sprd_iommu_ग_लिखो(sdev, SPRD_VAU_DEFAULT_PPN_RD, val);
		sprd_iommu_ग_लिखो(sdev, SPRD_VAU_DEFAULT_PPN_WR, val);
	पूर्ण
पूर्ण

अटल व्योम sprd_iommu_hw_en(काष्ठा sprd_iommu_device *sdev, bool en)
अणु
	अचिन्हित पूर्णांक reg_cfg;
	u32 mask, val;

	अगर (sdev->ver == SPRD_IOMMU_EX)
		reg_cfg = SPRD_EX_CFG;
	अन्यथा
		reg_cfg = SPRD_VAU_CFG;

	mask = SPRD_IOMMU_EN | SPRD_IOMMU_GATE_EN;
	val = en ? mask : 0;
	sprd_iommu_update_bits(sdev, reg_cfg, mask, 0, val);
पूर्ण

अटल पूर्णांक sprd_iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				    काष्ठा device *dev)
अणु
	काष्ठा sprd_iommu_device *sdev = dev_iommu_priv_get(dev);
	काष्ठा sprd_iommu_करोमुख्य *करोm = to_sprd_करोमुख्य(करोमुख्य);
	माप_प्रकार pgt_size = sprd_iommu_pgt_size(करोमुख्य);

	अगर (करोm->sdev) अणु
		pr_err("There's already a device attached to this domain.\n");
		वापस -EINVAL;
	पूर्ण

	करोm->pgt_va = dma_alloc_coherent(sdev->dev, pgt_size, &करोm->pgt_pa, GFP_KERNEL);
	अगर (!करोm->pgt_va)
		वापस -ENOMEM;

	करोm->sdev = sdev;

	sprd_iommu_first_ppn(करोm);
	sprd_iommu_first_vpn(करोm);
	sprd_iommu_vpn_range(करोm);
	sprd_iommu_शेष_ppn(sdev);
	sprd_iommu_hw_en(sdev, true);

	वापस 0;
पूर्ण

अटल व्योम sprd_iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
					     काष्ठा device *dev)
अणु
	काष्ठा sprd_iommu_करोमुख्य *करोm = to_sprd_करोमुख्य(करोमुख्य);
	काष्ठा sprd_iommu_device *sdev = करोm->sdev;
	माप_प्रकार pgt_size = sprd_iommu_pgt_size(करोमुख्य);

	अगर (!sdev)
		वापस;

	dma_मुक्त_coherent(sdev->dev, pgt_size, करोm->pgt_va, करोm->pgt_pa);
	sprd_iommu_hw_en(sdev, false);
	करोm->sdev = शून्य;
पूर्ण

अटल पूर्णांक sprd_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			  phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा sprd_iommu_करोमुख्य *करोm = to_sprd_करोमुख्य(करोमुख्य);
	अचिन्हित पूर्णांक page_num = size >> SPRD_IOMMU_PAGE_SHIFT;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	u32 *pgt_base_iova;
	u32 pabase = (u32)paddr;
	अचिन्हित दीर्घ start = करोमुख्य->geometry.aperture_start;
	अचिन्हित दीर्घ end = करोमुख्य->geometry.aperture_end;

	अगर (!करोm->sdev) अणु
		pr_err("No sprd_iommu_device attached to the domain\n");
		वापस -EINVAL;
	पूर्ण

	अगर (iova < start || (iova + size) > (end + 1)) अणु
		dev_err(करोm->sdev->dev, "(iova(0x%lx) + size(%zx)) are not in the range!\n",
			iova, size);
		वापस -EINVAL;
	पूर्ण

	pgt_base_iova = करोm->pgt_va + ((iova - start) >> SPRD_IOMMU_PAGE_SHIFT);

	spin_lock_irqsave(&करोm->pgtlock, flags);
	क्रम (i = 0; i < page_num; i++) अणु
		pgt_base_iova[i] = pabase >> SPRD_IOMMU_PAGE_SHIFT;
		pabase += SPRD_IOMMU_PAGE_SIZE;
	पूर्ण
	spin_unlock_irqrestore(&करोm->pgtlock, flags);

	वापस 0;
पूर्ण

अटल माप_प्रकार sprd_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			माप_प्रकार size, काष्ठा iommu_iotlb_gather *iotlb_gather)
अणु
	काष्ठा sprd_iommu_करोमुख्य *करोm = to_sprd_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	u32 *pgt_base_iova;
	अचिन्हित पूर्णांक page_num = size >> SPRD_IOMMU_PAGE_SHIFT;
	अचिन्हित दीर्घ start = करोमुख्य->geometry.aperture_start;
	अचिन्हित दीर्घ end = करोमुख्य->geometry.aperture_end;

	अगर (iova < start || (iova + size) > (end + 1))
		वापस -EINVAL;

	pgt_base_iova = करोm->pgt_va + ((iova - start) >> SPRD_IOMMU_PAGE_SHIFT);

	spin_lock_irqsave(&करोm->pgtlock, flags);
	स_रखो(pgt_base_iova, 0, page_num * माप(u32));
	spin_unlock_irqrestore(&करोm->pgtlock, flags);

	वापस 0;
पूर्ण

अटल व्योम sprd_iommu_sync_map(काष्ठा iommu_करोमुख्य *करोमुख्य,
				अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	काष्ठा sprd_iommu_करोमुख्य *करोm = to_sprd_करोमुख्य(करोमुख्य);
	अचिन्हित पूर्णांक reg;

	अगर (करोm->sdev->ver == SPRD_IOMMU_EX)
		reg = SPRD_EX_UPDATE;
	अन्यथा
		reg = SPRD_VAU_UPDATE;

	/* clear IOMMU TLB buffer after page table updated */
	sprd_iommu_ग_लिखो(करोm->sdev, reg, 0xffffffff);
पूर्ण

अटल व्योम sprd_iommu_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
			    काष्ठा iommu_iotlb_gather *iotlb_gather)
अणु
	sprd_iommu_sync_map(करोमुख्य, 0, 0);
पूर्ण

अटल phys_addr_t sprd_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					   dma_addr_t iova)
अणु
	काष्ठा sprd_iommu_करोमुख्य *करोm = to_sprd_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	phys_addr_t pa;
	अचिन्हित दीर्घ start = करोमुख्य->geometry.aperture_start;
	अचिन्हित दीर्घ end = करोमुख्य->geometry.aperture_end;

	अगर (WARN_ON(iova < start || iova > end))
		वापस 0;

	spin_lock_irqsave(&करोm->pgtlock, flags);
	pa = *(करोm->pgt_va + ((iova - start) >> SPRD_IOMMU_PAGE_SHIFT));
	pa = (pa << SPRD_IOMMU_PAGE_SHIFT) + ((iova - start) & (SPRD_IOMMU_PAGE_SIZE - 1));
	spin_unlock_irqrestore(&करोm->pgtlock, flags);

	वापस pa;
पूर्ण

अटल काष्ठा iommu_device *sprd_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा sprd_iommu_device *sdev;

	अगर (!fwspec || fwspec->ops != &sprd_iommu_ops)
		वापस ERR_PTR(-ENODEV);

	sdev = dev_iommu_priv_get(dev);

	वापस &sdev->iommu;
पूर्ण

अटल व्योम sprd_iommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	अगर (!fwspec || fwspec->ops != &sprd_iommu_ops)
		वापस;

	iommu_fwspec_मुक्त(dev);
पूर्ण

अटल काष्ठा iommu_group *sprd_iommu_device_group(काष्ठा device *dev)
अणु
	काष्ठा sprd_iommu_device *sdev = dev_iommu_priv_get(dev);

	वापस iommu_group_ref_get(sdev->group);
पूर्ण

अटल पूर्णांक sprd_iommu_of_xlate(काष्ठा device *dev, काष्ठा of_phandle_args *args)
अणु
	काष्ठा platक्रमm_device *pdev;

	अगर (!dev_iommu_priv_get(dev)) अणु
		pdev = of_find_device_by_node(args->np);
		dev_iommu_priv_set(dev, platक्रमm_get_drvdata(pdev));
		platक्रमm_device_put(pdev);
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा iommu_ops sprd_iommu_ops = अणु
	.करोमुख्य_alloc	= sprd_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त	= sprd_iommu_करोमुख्य_मुक्त,
	.attach_dev	= sprd_iommu_attach_device,
	.detach_dev	= sprd_iommu_detach_device,
	.map		= sprd_iommu_map,
	.unmap		= sprd_iommu_unmap,
	.iotlb_sync_map	= sprd_iommu_sync_map,
	.iotlb_sync	= sprd_iommu_sync,
	.iova_to_phys	= sprd_iommu_iova_to_phys,
	.probe_device	= sprd_iommu_probe_device,
	.release_device	= sprd_iommu_release_device,
	.device_group	= sprd_iommu_device_group,
	.of_xlate	= sprd_iommu_of_xlate,
	.pgsize_biपंचांगap	= ~0UL << SPRD_IOMMU_PAGE_SHIFT,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sprd_iommu_of_match[] = अणु
	अणु .compatible = "sprd,iommu-v1" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_iommu_of_match);

/*
 * Clock is not required, access to some of IOMMUs is controlled by gate
 * clk, enabled घड़ीs क्रम that kind of IOMMUs beक्रमe accessing.
 * Return 0 क्रम success or no घड़ीs found.
 */
अटल पूर्णांक sprd_iommu_clk_enable(काष्ठा sprd_iommu_device *sdev)
अणु
	काष्ठा clk *eb;

	eb = devm_clk_get_optional(sdev->dev, शून्य);
	अगर (!eb)
		वापस 0;

	अगर (IS_ERR(eb))
		वापस PTR_ERR(eb);

	sdev->eb = eb;
	वापस clk_prepare_enable(eb);
पूर्ण

अटल व्योम sprd_iommu_clk_disable(काष्ठा sprd_iommu_device *sdev)
अणु
	अगर (sdev->eb)
		clk_disable_unprepare(sdev->eb);
पूर्ण

अटल पूर्णांक sprd_iommu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_iommu_device *sdev;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *base;
	पूर्णांक ret;

	sdev = devm_kzalloc(dev, माप(*sdev), GFP_KERNEL);
	अगर (!sdev)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base)) अणु
		dev_err(dev, "Failed to get ioremap resource.\n");
		वापस PTR_ERR(base);
	पूर्ण
	sdev->base = base;

	sdev->prot_page_va = dma_alloc_coherent(dev, SPRD_IOMMU_PAGE_SIZE,
						&sdev->prot_page_pa, GFP_KERNEL);
	अगर (!sdev->prot_page_va)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, sdev);
	sdev->dev = dev;

	/* All the client devices are in the same iommu-group */
	sdev->group = iommu_group_alloc();
	अगर (IS_ERR(sdev->group)) अणु
		ret = PTR_ERR(sdev->group);
		जाओ मुक्त_page;
	पूर्ण

	ret = iommu_device_sysfs_add(&sdev->iommu, dev, शून्य, dev_name(dev));
	अगर (ret)
		जाओ put_group;

	ret = iommu_device_रेजिस्टर(&sdev->iommu, &sprd_iommu_ops, dev);
	अगर (ret)
		जाओ हटाओ_sysfs;

	अगर (!iommu_present(&platक्रमm_bus_type))
		bus_set_iommu(&platक्रमm_bus_type, &sprd_iommu_ops);

	ret = sprd_iommu_clk_enable(sdev);
	अगर (ret)
		जाओ unरेजिस्टर_iommu;

	ret = sprd_iommu_get_version(sdev);
	अगर (ret < 0) अणु
		dev_err(dev, "IOMMU version(%d) is invalid.\n", ret);
		जाओ disable_clk;
	पूर्ण
	sdev->ver = ret;

	वापस 0;

disable_clk:
	sprd_iommu_clk_disable(sdev);
unरेजिस्टर_iommu:
	iommu_device_unरेजिस्टर(&sdev->iommu);
हटाओ_sysfs:
	iommu_device_sysfs_हटाओ(&sdev->iommu);
put_group:
	iommu_group_put(sdev->group);
मुक्त_page:
	dma_मुक्त_coherent(sdev->dev, SPRD_IOMMU_PAGE_SIZE, sdev->prot_page_va, sdev->prot_page_pa);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_iommu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_iommu_device *sdev = platक्रमm_get_drvdata(pdev);

	dma_मुक्त_coherent(sdev->dev, SPRD_IOMMU_PAGE_SIZE, sdev->prot_page_va, sdev->prot_page_pa);

	iommu_group_put(sdev->group);
	sdev->group = शून्य;

	bus_set_iommu(&platक्रमm_bus_type, शून्य);

	platक्रमm_set_drvdata(pdev, शून्य);
	iommu_device_sysfs_हटाओ(&sdev->iommu);
	iommu_device_unरेजिस्टर(&sdev->iommu);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sprd_iommu_driver = अणु
	.driver	= अणु
		.name		= "sprd-iommu",
		.of_match_table	= sprd_iommu_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe	= sprd_iommu_probe,
	.हटाओ	= sprd_iommu_हटाओ,
पूर्ण;
module_platक्रमm_driver(sprd_iommu_driver);

MODULE_DESCRIPTION("IOMMU driver for Unisoc SoCs");
MODULE_ALIAS("platform:sprd-iommu");
MODULE_LICENSE("GPL");
