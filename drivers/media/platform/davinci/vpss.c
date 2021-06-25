<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Texas Instruments.
 *
 * common vpss प्रणाली module platक्रमm driver क्रम all video drivers.
 */
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/err.h>

#समावेश <media/davinci/vpss.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("VPSS Driver");
MODULE_AUTHOR("Texas Instruments");

/* DM644x defines */
#घोषणा DM644X_SBL_PCR_VPSS		(4)

#घोषणा DM355_VPSSBL_INTSEL		0x10
#घोषणा DM355_VPSSBL_EVTSEL		0x14
/* vpss BL रेजिस्टर offsets */
#घोषणा DM355_VPSSBL_CCDCMUX		0x1c
/* vpss CLK रेजिस्टर offsets */
#घोषणा DM355_VPSSCLK_CLKCTRL		0x04
/* masks and shअगरts */
#घोषणा VPSS_HSSISEL_SHIFT		4
/*
 * VDINT0 - vpss_पूर्णांक0, VDINT1 - vpss_पूर्णांक1, H3A - vpss_पूर्णांक4,
 * IPIPE_INT1_SDR - vpss_पूर्णांक5
 */
#घोषणा DM355_VPSSBL_INTSEL_DEFAULT	0xff83ff10
/* VENCINT - vpss_पूर्णांक8 */
#घोषणा DM355_VPSSBL_EVTSEL_DEFAULT	0x4

#घोषणा DM365_ISP5_PCCR				0x04
#घोषणा DM365_ISP5_PCCR_BL_CLK_ENABLE		BIT(0)
#घोषणा DM365_ISP5_PCCR_ISIF_CLK_ENABLE		BIT(1)
#घोषणा DM365_ISP5_PCCR_H3A_CLK_ENABLE		BIT(2)
#घोषणा DM365_ISP5_PCCR_RSZ_CLK_ENABLE		BIT(3)
#घोषणा DM365_ISP5_PCCR_IPIPE_CLK_ENABLE	BIT(4)
#घोषणा DM365_ISP5_PCCR_IPIPEIF_CLK_ENABLE	BIT(5)
#घोषणा DM365_ISP5_PCCR_RSV			BIT(6)

#घोषणा DM365_ISP5_BCR			0x08
#घोषणा DM365_ISP5_BCR_ISIF_OUT_ENABLE	BIT(1)

#घोषणा DM365_ISP5_INTSEL1		0x10
#घोषणा DM365_ISP5_INTSEL2		0x14
#घोषणा DM365_ISP5_INTSEL3		0x18
#घोषणा DM365_ISP5_CCDCMUX		0x20
#घोषणा DM365_ISP5_PG_FRAME_SIZE	0x28
#घोषणा DM365_VPBE_CLK_CTRL		0x00

#घोषणा VPSS_CLK_CTRL			0x01c40044
#घोषणा VPSS_CLK_CTRL_VENCCLKEN		BIT(3)
#घोषणा VPSS_CLK_CTRL_DACCLKEN		BIT(4)

/*
 * vpss पूर्णांकerrupts. VDINT0 - vpss_पूर्णांक0, VDINT1 - vpss_पूर्णांक1,
 * AF - vpss_पूर्णांक3
 */
#घोषणा DM365_ISP5_INTSEL1_DEFAULT	0x0b1f0100
/* AEW - vpss_पूर्णांक6, RSZ_INT_DMA - vpss_पूर्णांक5 */
#घोषणा DM365_ISP5_INTSEL2_DEFAULT	0x1f0a0f1f
/* VENC - vpss_पूर्णांक8 */
#घोषणा DM365_ISP5_INTSEL3_DEFAULT	0x00000015

/* masks and shअगरts क्रम DM365*/
#घोषणा DM365_CCDC_PG_VD_POL_SHIFT	0
#घोषणा DM365_CCDC_PG_HD_POL_SHIFT	1

#घोषणा CCD_SRC_SEL_MASK		(BIT_MASK(5) | BIT_MASK(4))
#घोषणा CCD_SRC_SEL_SHIFT		4

/* Dअगरferent SoC platक्रमms supported by this driver */
क्रमागत vpss_platक्रमm_type अणु
	DM644X,
	DM355,
	DM365,
पूर्ण;

/*
 * vpss operations. Depends on platक्रमm. Not all functions are available
 * on all platक्रमms. The api, first check अगर a function is available beक्रमe
 * invoking it. In the probe, the function ptrs are initialized based on
 * vpss name. vpss name can be "dm355_vpss", "dm644x_vpss" etc.
 */
काष्ठा vpss_hw_ops अणु
	/* enable घड़ी */
	पूर्णांक (*enable_घड़ी)(क्रमागत vpss_घड़ी_sel घड़ी_sel, पूर्णांक en);
	/* select input to ccdc */
	व्योम (*select_ccdc_source)(क्रमागत vpss_ccdc_source_sel src_sel);
	/* clear wbl overflow bit */
	पूर्णांक (*clear_wbl_overflow)(क्रमागत vpss_wbl_sel wbl_sel);
	/* set sync polarity */
	व्योम (*set_sync_pol)(काष्ठा vpss_sync_pol);
	/* set the PG_FRAME_SIZE रेजिस्टर*/
	व्योम (*set_pg_frame_size)(काष्ठा vpss_pg_frame_size);
	/* check and clear पूर्णांकerrupt अगर occurred */
	पूर्णांक (*dma_complete_पूर्णांकerrupt)(व्योम);
पूर्ण;

/* vpss configuration */
काष्ठा vpss_oper_config अणु
	__iomem व्योम *vpss_regs_base0;
	__iomem व्योम *vpss_regs_base1;
	__iomem व्योम *vpss_regs_base2;
	क्रमागत vpss_platक्रमm_type platक्रमm;
	spinlock_t vpss_lock;
	काष्ठा vpss_hw_ops hw_ops;
पूर्ण;

अटल काष्ठा vpss_oper_config oper_cfg;

/* रेजिस्टर access routines */
अटल अंतरभूत u32 bl_regr(u32 offset)
अणु
	वापस __raw_पढ़ोl(oper_cfg.vpss_regs_base0 + offset);
पूर्ण

अटल अंतरभूत व्योम bl_regw(u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, oper_cfg.vpss_regs_base0 + offset);
पूर्ण

अटल अंतरभूत u32 vpss_regr(u32 offset)
अणु
	वापस __raw_पढ़ोl(oper_cfg.vpss_regs_base1 + offset);
पूर्ण

अटल अंतरभूत व्योम vpss_regw(u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, oper_cfg.vpss_regs_base1 + offset);
पूर्ण

/* For DM365 only */
अटल अंतरभूत u32 isp5_पढ़ो(u32 offset)
अणु
	वापस __raw_पढ़ोl(oper_cfg.vpss_regs_base0 + offset);
पूर्ण

/* For DM365 only */
अटल अंतरभूत व्योम isp5_ग_लिखो(u32 val, u32 offset)
अणु
	__raw_ग_लिखोl(val, oper_cfg.vpss_regs_base0 + offset);
पूर्ण

अटल व्योम dm365_select_ccdc_source(क्रमागत vpss_ccdc_source_sel src_sel)
अणु
	u32 temp = isp5_पढ़ो(DM365_ISP5_CCDCMUX) & ~CCD_SRC_SEL_MASK;

	/* अगर we are using pattern generator, enable it */
	अगर (src_sel == VPSS_PGLPBK || src_sel == VPSS_CCDCPG)
		temp |= 0x08;

	temp |= (src_sel << CCD_SRC_SEL_SHIFT);
	isp5_ग_लिखो(temp, DM365_ISP5_CCDCMUX);
पूर्ण

अटल व्योम dm355_select_ccdc_source(क्रमागत vpss_ccdc_source_sel src_sel)
अणु
	bl_regw(src_sel << VPSS_HSSISEL_SHIFT, DM355_VPSSBL_CCDCMUX);
पूर्ण

पूर्णांक vpss_dma_complete_पूर्णांकerrupt(व्योम)
अणु
	अगर (!oper_cfg.hw_ops.dma_complete_पूर्णांकerrupt)
		वापस 2;
	वापस oper_cfg.hw_ops.dma_complete_पूर्णांकerrupt();
पूर्ण
EXPORT_SYMBOL(vpss_dma_complete_पूर्णांकerrupt);

पूर्णांक vpss_select_ccdc_source(क्रमागत vpss_ccdc_source_sel src_sel)
अणु
	अगर (!oper_cfg.hw_ops.select_ccdc_source)
		वापस -EINVAL;

	oper_cfg.hw_ops.select_ccdc_source(src_sel);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vpss_select_ccdc_source);

अटल पूर्णांक dm644x_clear_wbl_overflow(क्रमागत vpss_wbl_sel wbl_sel)
अणु
	u32 mask = 1, val;

	अगर (wbl_sel < VPSS_PCR_AEW_WBL_0 ||
	    wbl_sel > VPSS_PCR_CCDC_WBL_O)
		वापस -EINVAL;

	/* writing a 0 clear the overflow */
	mask = ~(mask << wbl_sel);
	val = bl_regr(DM644X_SBL_PCR_VPSS) & mask;
	bl_regw(val, DM644X_SBL_PCR_VPSS);
	वापस 0;
पूर्ण

व्योम vpss_set_sync_pol(काष्ठा vpss_sync_pol sync)
अणु
	अगर (!oper_cfg.hw_ops.set_sync_pol)
		वापस;

	oper_cfg.hw_ops.set_sync_pol(sync);
पूर्ण
EXPORT_SYMBOL(vpss_set_sync_pol);

पूर्णांक vpss_clear_wbl_overflow(क्रमागत vpss_wbl_sel wbl_sel)
अणु
	अगर (!oper_cfg.hw_ops.clear_wbl_overflow)
		वापस -EINVAL;

	वापस oper_cfg.hw_ops.clear_wbl_overflow(wbl_sel);
पूर्ण
EXPORT_SYMBOL(vpss_clear_wbl_overflow);

/*
 *  dm355_enable_घड़ी - Enable VPSS Clock
 *  @घड़ी_sel: Clock to be enabled/disabled
 *  @en: enable/disable flag
 *
 *  This is called to enable or disable a vpss घड़ी
 */
अटल पूर्णांक dm355_enable_घड़ी(क्रमागत vpss_घड़ी_sel घड़ी_sel, पूर्णांक en)
अणु
	अचिन्हित दीर्घ flags;
	u32 utemp, mask = 0x1, shअगरt = 0;

	चयन (घड़ी_sel) अणु
	हाल VPSS_VPBE_CLOCK:
		/* nothing since lsb */
		अवरोध;
	हाल VPSS_VENC_CLOCK_SEL:
		shअगरt = 2;
		अवरोध;
	हाल VPSS_CFALD_CLOCK:
		shअगरt = 3;
		अवरोध;
	हाल VPSS_H3A_CLOCK:
		shअगरt = 4;
		अवरोध;
	हाल VPSS_IPIPE_CLOCK:
		shअगरt = 5;
		अवरोध;
	हाल VPSS_CCDC_CLOCK:
		shअगरt = 6;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "dm355_enable_clock: Invalid selector: %d\n",
		       घड़ी_sel);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&oper_cfg.vpss_lock, flags);
	utemp = vpss_regr(DM355_VPSSCLK_CLKCTRL);
	अगर (!en)
		utemp &= ~(mask << shअगरt);
	अन्यथा
		utemp |= (mask << shअगरt);

	vpss_regw(utemp, DM355_VPSSCLK_CLKCTRL);
	spin_unlock_irqrestore(&oper_cfg.vpss_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक dm365_enable_घड़ी(क्रमागत vpss_घड़ी_sel घड़ी_sel, पूर्णांक en)
अणु
	अचिन्हित दीर्घ flags;
	u32 utemp, mask = 0x1, shअगरt = 0, offset = DM365_ISP5_PCCR;
	u32 (*पढ़ो)(u32 offset) = isp5_पढ़ो;
	व्योम(*ग_लिखो)(u32 val, u32 offset) = isp5_ग_लिखो;

	चयन (घड़ी_sel) अणु
	हाल VPSS_BL_CLOCK:
		अवरोध;
	हाल VPSS_CCDC_CLOCK:
		shअगरt = 1;
		अवरोध;
	हाल VPSS_H3A_CLOCK:
		shअगरt = 2;
		अवरोध;
	हाल VPSS_RSZ_CLOCK:
		shअगरt = 3;
		अवरोध;
	हाल VPSS_IPIPE_CLOCK:
		shअगरt = 4;
		अवरोध;
	हाल VPSS_IPIPEIF_CLOCK:
		shअगरt = 5;
		अवरोध;
	हाल VPSS_PCLK_INTERNAL:
		shअगरt = 6;
		अवरोध;
	हाल VPSS_PSYNC_CLOCK_SEL:
		shअगरt = 7;
		अवरोध;
	हाल VPSS_VPBE_CLOCK:
		पढ़ो = vpss_regr;
		ग_लिखो = vpss_regw;
		offset = DM365_VPBE_CLK_CTRL;
		अवरोध;
	हाल VPSS_VENC_CLOCK_SEL:
		shअगरt = 2;
		पढ़ो = vpss_regr;
		ग_लिखो = vpss_regw;
		offset = DM365_VPBE_CLK_CTRL;
		अवरोध;
	हाल VPSS_LDC_CLOCK:
		shअगरt = 3;
		पढ़ो = vpss_regr;
		ग_लिखो = vpss_regw;
		offset = DM365_VPBE_CLK_CTRL;
		अवरोध;
	हाल VPSS_FDIF_CLOCK:
		shअगरt = 4;
		पढ़ो = vpss_regr;
		ग_लिखो = vpss_regw;
		offset = DM365_VPBE_CLK_CTRL;
		अवरोध;
	हाल VPSS_OSD_CLOCK_SEL:
		shअगरt = 6;
		पढ़ो = vpss_regr;
		ग_लिखो = vpss_regw;
		offset = DM365_VPBE_CLK_CTRL;
		अवरोध;
	हाल VPSS_LDC_CLOCK_SEL:
		shअगरt = 7;
		पढ़ो = vpss_regr;
		ग_लिखो = vpss_regw;
		offset = DM365_VPBE_CLK_CTRL;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "dm365_enable_clock: Invalid selector: %d\n",
		       घड़ी_sel);
		वापस -1;
	पूर्ण

	spin_lock_irqsave(&oper_cfg.vpss_lock, flags);
	utemp = पढ़ो(offset);
	अगर (!en) अणु
		mask = ~mask;
		utemp &= (mask << shअगरt);
	पूर्ण अन्यथा
		utemp |= (mask << shअगरt);

	ग_लिखो(utemp, offset);
	spin_unlock_irqrestore(&oper_cfg.vpss_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक vpss_enable_घड़ी(क्रमागत vpss_घड़ी_sel घड़ी_sel, पूर्णांक en)
अणु
	अगर (!oper_cfg.hw_ops.enable_घड़ी)
		वापस -EINVAL;

	वापस oper_cfg.hw_ops.enable_घड़ी(घड़ी_sel, en);
पूर्ण
EXPORT_SYMBOL(vpss_enable_घड़ी);

व्योम dm365_vpss_set_sync_pol(काष्ठा vpss_sync_pol sync)
अणु
	पूर्णांक val = 0;
	val = isp5_पढ़ो(DM365_ISP5_CCDCMUX);

	val |= (sync.ccdpg_hdpol << DM365_CCDC_PG_HD_POL_SHIFT);
	val |= (sync.ccdpg_vdpol << DM365_CCDC_PG_VD_POL_SHIFT);

	isp5_ग_लिखो(val, DM365_ISP5_CCDCMUX);
पूर्ण
EXPORT_SYMBOL(dm365_vpss_set_sync_pol);

व्योम vpss_set_pg_frame_size(काष्ठा vpss_pg_frame_size frame_size)
अणु
	अगर (!oper_cfg.hw_ops.set_pg_frame_size)
		वापस;

	oper_cfg.hw_ops.set_pg_frame_size(frame_size);
पूर्ण
EXPORT_SYMBOL(vpss_set_pg_frame_size);

व्योम dm365_vpss_set_pg_frame_size(काष्ठा vpss_pg_frame_size frame_size)
अणु
	पूर्णांक current_reg = ((frame_size.hlpfr >> 1) - 1) << 16;

	current_reg |= (frame_size.pplen - 1);
	isp5_ग_लिखो(current_reg, DM365_ISP5_PG_FRAME_SIZE);
पूर्ण
EXPORT_SYMBOL(dm365_vpss_set_pg_frame_size);

अटल पूर्णांक vpss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	अक्षर *platक्रमm_name;

	अगर (!pdev->dev.platक्रमm_data) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -ENOENT;
	पूर्ण

	platक्रमm_name = pdev->dev.platक्रमm_data;
	अगर (!म_भेद(platक्रमm_name, "dm355_vpss"))
		oper_cfg.platक्रमm = DM355;
	अन्यथा अगर (!म_भेद(platक्रमm_name, "dm365_vpss"))
		oper_cfg.platक्रमm = DM365;
	अन्यथा अगर (!म_भेद(platक्रमm_name, "dm644x_vpss"))
		oper_cfg.platक्रमm = DM644X;
	अन्यथा अणु
		dev_err(&pdev->dev, "vpss driver not supported on this platform\n");
		वापस -ENODEV;
	पूर्ण

	dev_info(&pdev->dev, "%s vpss probed\n", platक्रमm_name);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	oper_cfg.vpss_regs_base0 = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(oper_cfg.vpss_regs_base0))
		वापस PTR_ERR(oper_cfg.vpss_regs_base0);

	अगर (oper_cfg.platक्रमm == DM355 || oper_cfg.platक्रमm == DM365) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);

		oper_cfg.vpss_regs_base1 = devm_ioremap_resource(&pdev->dev,
								 res);
		अगर (IS_ERR(oper_cfg.vpss_regs_base1))
			वापस PTR_ERR(oper_cfg.vpss_regs_base1);
	पूर्ण

	अगर (oper_cfg.platक्रमm == DM355) अणु
		oper_cfg.hw_ops.enable_घड़ी = dm355_enable_घड़ी;
		oper_cfg.hw_ops.select_ccdc_source = dm355_select_ccdc_source;
		/* Setup vpss पूर्णांकerrupts */
		bl_regw(DM355_VPSSBL_INTSEL_DEFAULT, DM355_VPSSBL_INTSEL);
		bl_regw(DM355_VPSSBL_EVTSEL_DEFAULT, DM355_VPSSBL_EVTSEL);
	पूर्ण अन्यथा अगर (oper_cfg.platक्रमm == DM365) अणु
		oper_cfg.hw_ops.enable_घड़ी = dm365_enable_घड़ी;
		oper_cfg.hw_ops.select_ccdc_source = dm365_select_ccdc_source;
		/* Setup vpss पूर्णांकerrupts */
		isp5_ग_लिखो((isp5_पढ़ो(DM365_ISP5_PCCR) |
				      DM365_ISP5_PCCR_BL_CLK_ENABLE |
				      DM365_ISP5_PCCR_ISIF_CLK_ENABLE |
				      DM365_ISP5_PCCR_H3A_CLK_ENABLE |
				      DM365_ISP5_PCCR_RSZ_CLK_ENABLE |
				      DM365_ISP5_PCCR_IPIPE_CLK_ENABLE |
				      DM365_ISP5_PCCR_IPIPEIF_CLK_ENABLE |
				      DM365_ISP5_PCCR_RSV), DM365_ISP5_PCCR);
		isp5_ग_लिखो((isp5_पढ़ो(DM365_ISP5_BCR) |
			    DM365_ISP5_BCR_ISIF_OUT_ENABLE), DM365_ISP5_BCR);
		isp5_ग_लिखो(DM365_ISP5_INTSEL1_DEFAULT, DM365_ISP5_INTSEL1);
		isp5_ग_लिखो(DM365_ISP5_INTSEL2_DEFAULT, DM365_ISP5_INTSEL2);
		isp5_ग_लिखो(DM365_ISP5_INTSEL3_DEFAULT, DM365_ISP5_INTSEL3);
	पूर्ण अन्यथा
		oper_cfg.hw_ops.clear_wbl_overflow = dm644x_clear_wbl_overflow;

	pm_runसमय_enable(&pdev->dev);

	pm_runसमय_get(&pdev->dev);

	spin_lock_init(&oper_cfg.vpss_lock);
	dev_info(&pdev->dev, "%s vpss probe success\n", platक्रमm_name);

	वापस 0;
पूर्ण

अटल पूर्णांक vpss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक vpss_suspend(काष्ठा device *dev)
अणु
	pm_runसमय_put(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक vpss_resume(काष्ठा device *dev)
अणु
	pm_runसमय_get(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vpss_pm_ops = अणु
	.suspend = vpss_suspend,
	.resume = vpss_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver vpss_driver = अणु
	.driver = अणु
		.name	= "vpss",
		.pm = &vpss_pm_ops,
	पूर्ण,
	.हटाओ = vpss_हटाओ,
	.probe = vpss_probe,
पूर्ण;

अटल व्योम vpss_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vpss_driver);
	iounmap(oper_cfg.vpss_regs_base2);
	release_mem_region(VPSS_CLK_CTRL, 4);
पूर्ण

अटल पूर्णांक __init vpss_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!request_mem_region(VPSS_CLK_CTRL, 4, "vpss_clock_control"))
		वापस -EBUSY;

	oper_cfg.vpss_regs_base2 = ioremap(VPSS_CLK_CTRL, 4);
	अगर (unlikely(!oper_cfg.vpss_regs_base2)) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	ग_लिखोl(VPSS_CLK_CTRL_VENCCLKEN |
	       VPSS_CLK_CTRL_DACCLKEN, oper_cfg.vpss_regs_base2);

	ret = platक्रमm_driver_रेजिस्टर(&vpss_driver);
	अगर (ret)
		जाओ err_pd_रेजिस्टर;

	वापस 0;

err_pd_रेजिस्टर:
	iounmap(oper_cfg.vpss_regs_base2);
err_ioremap:
	release_mem_region(VPSS_CLK_CTRL, 4);
	वापस ret;
पूर्ण
subsys_initcall(vpss_init);
module_निकास(vpss_निकास);
