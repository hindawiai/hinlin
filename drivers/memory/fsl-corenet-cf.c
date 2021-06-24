<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CoreNet Coherency Fabric error reporting
 *
 * Copyright 2014 Freescale Semiconductor Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

क्रमागत ccf_version अणु
	CCF1,
	CCF2,
पूर्ण;

काष्ठा ccf_info अणु
	क्रमागत ccf_version version;
	पूर्णांक err_reg_offs;
	bool has_brr;
पूर्ण;

अटल स्थिर काष्ठा ccf_info ccf1_info = अणु
	.version = CCF1,
	.err_reg_offs = 0xa00,
	.has_brr = false,
पूर्ण;

अटल स्थिर काष्ठा ccf_info ccf2_info = अणु
	.version = CCF2,
	.err_reg_offs = 0xe40,
	.has_brr = true,
पूर्ण;

/*
 * This रेजिस्टर is present but not करोcumented, with dअगरferent values क्रम
 * IP_ID, on other chips with fsl,corenet2-cf such as t4240 and b4860.
 */
#घोषणा CCF_BRR			0xbf8
#घोषणा CCF_BRR_IPID		0xffff0000
#घोषणा CCF_BRR_IPID_T1040	0x09310000

अटल स्थिर काष्ठा of_device_id ccf_matches[] = अणु
	अणु
		.compatible = "fsl,corenet1-cf",
		.data = &ccf1_info,
	पूर्ण,
	अणु
		.compatible = "fsl,corenet2-cf",
		.data = &ccf2_info,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ccf_matches);

काष्ठा ccf_err_regs अणु
	u32 errdet;		/* 0x00 Error Detect Register */
	/* 0x04 Error Enable (ccf1)/Disable (ccf2) Register */
	u32 errdis;
	/* 0x08 Error Interrupt Enable Register (ccf2 only) */
	u32 errपूर्णांकen;
	u32 cecar;		/* 0x0c Error Capture Attribute Register */
	u32 cecaddrh;		/* 0x10 Error Capture Address High */
	u32 cecaddrl;		/* 0x14 Error Capture Address Low */
	u32 cecar2;		/* 0x18 Error Capture Attribute Register 2 */
पूर्ण;

/* LAE/CV also valid क्रम errdis and errपूर्णांकen */
#घोषणा ERRDET_LAE		(1 << 0)  /* Local Access Error */
#घोषणा ERRDET_CV		(1 << 1)  /* Coherency Violation */
#घोषणा ERRDET_UTID		(1 << 2)  /* Unavailable Target ID (t1040) */
#घोषणा ERRDET_MCST		(1 << 3)  /* Multicast Stash (t1040) */
#घोषणा ERRDET_CTYPE_SHIFT	26	  /* Capture Type (ccf2 only) */
#घोषणा ERRDET_CTYPE_MASK	(0x1f << ERRDET_CTYPE_SHIFT)
#घोषणा ERRDET_CAP		(1 << 31) /* Capture Valid (ccf2 only) */

#घोषणा CECAR_VAL		(1 << 0)  /* Valid (ccf1 only) */
#घोषणा CECAR_UVT		(1 << 15) /* Unavailable target ID (ccf1) */
#घोषणा CECAR_SRCID_SHIFT_CCF1	24
#घोषणा CECAR_SRCID_MASK_CCF1	(0xff << CECAR_SRCID_SHIFT_CCF1)
#घोषणा CECAR_SRCID_SHIFT_CCF2	18
#घोषणा CECAR_SRCID_MASK_CCF2	(0xff << CECAR_SRCID_SHIFT_CCF2)

#घोषणा CECADDRH_ADDRH		0xff

काष्ठा ccf_निजी अणु
	स्थिर काष्ठा ccf_info *info;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा ccf_err_regs __iomem *err_regs;
	bool t1040;
पूर्ण;

अटल irqवापस_t ccf_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ccf_निजी *ccf = dev_id;
	अटल DEFINE_RATELIMIT_STATE(ratelimit, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);
	u32 errdet, cecar, cecar2;
	u64 addr;
	u32 src_id;
	bool uvt = false;
	bool cap_valid = false;

	errdet = ioपढ़ो32be(&ccf->err_regs->errdet);
	cecar = ioपढ़ो32be(&ccf->err_regs->cecar);
	cecar2 = ioपढ़ो32be(&ccf->err_regs->cecar2);
	addr = ioपढ़ो32be(&ccf->err_regs->cecaddrl);
	addr |= ((u64)(ioपढ़ो32be(&ccf->err_regs->cecaddrh) &
		       CECADDRH_ADDRH)) << 32;

	अगर (!__ratelimit(&ratelimit))
		जाओ out;

	चयन (ccf->info->version) अणु
	हाल CCF1:
		अगर (cecar & CECAR_VAL) अणु
			अगर (cecar & CECAR_UVT)
				uvt = true;

			src_id = (cecar & CECAR_SRCID_MASK_CCF1) >>
				 CECAR_SRCID_SHIFT_CCF1;
			cap_valid = true;
		पूर्ण

		अवरोध;
	हाल CCF2:
		अगर (errdet & ERRDET_CAP) अणु
			src_id = (cecar & CECAR_SRCID_MASK_CCF2) >>
				 CECAR_SRCID_SHIFT_CCF2;
			cap_valid = true;
		पूर्ण

		अवरोध;
	पूर्ण

	dev_crit(ccf->dev, "errdet 0x%08x cecar 0x%08x cecar2 0x%08x\n",
		 errdet, cecar, cecar2);

	अगर (errdet & ERRDET_LAE) अणु
		अगर (uvt)
			dev_crit(ccf->dev, "LAW Unavailable Target ID\n");
		अन्यथा
			dev_crit(ccf->dev, "Local Access Window Error\n");
	पूर्ण

	अगर (errdet & ERRDET_CV)
		dev_crit(ccf->dev, "Coherency Violation\n");

	अगर (errdet & ERRDET_UTID)
		dev_crit(ccf->dev, "Unavailable Target ID\n");

	अगर (errdet & ERRDET_MCST)
		dev_crit(ccf->dev, "Multicast Stash\n");

	अगर (cap_valid) अणु
		dev_crit(ccf->dev, "address 0x%09llx, src id 0x%x\n",
			 addr, src_id);
	पूर्ण

out:
	ioग_लिखो32be(errdet, &ccf->err_regs->errdet);
	वापस errdet ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक ccf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ccf_निजी *ccf;
	काष्ठा resource *r;
	स्थिर काष्ठा of_device_id *match;
	u32 errपूर्णांकen;
	पूर्णांक ret, irq;

	match = of_match_device(ccf_matches, &pdev->dev);
	अगर (WARN_ON(!match))
		वापस -ENODEV;

	ccf = devm_kzalloc(&pdev->dev, माप(*ccf), GFP_KERNEL);
	अगर (!ccf)
		वापस -ENOMEM;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "%s: no mem resource\n", __func__);
		वापस -ENXIO;
	पूर्ण

	ccf->regs = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(ccf->regs))
		वापस PTR_ERR(ccf->regs);

	ccf->dev = &pdev->dev;
	ccf->info = match->data;
	ccf->err_regs = ccf->regs + ccf->info->err_reg_offs;

	अगर (ccf->info->has_brr) अणु
		u32 brr = ioपढ़ो32be(ccf->regs + CCF_BRR);

		अगर ((brr & CCF_BRR_IPID) == CCF_BRR_IPID_T1040)
			ccf->t1040 = true;
	पूर्ण

	dev_set_drvdata(&pdev->dev, ccf);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, ccf_irq, 0, pdev->name, ccf);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s: can't request irq\n", __func__);
		वापस ret;
	पूर्ण

	errपूर्णांकen = ERRDET_LAE | ERRDET_CV;
	अगर (ccf->t1040)
		errपूर्णांकen |= ERRDET_UTID | ERRDET_MCST;

	चयन (ccf->info->version) अणु
	हाल CCF1:
		/* On CCF1 this रेजिस्टर enables rather than disables. */
		ioग_लिखो32be(errपूर्णांकen, &ccf->err_regs->errdis);
		अवरोध;

	हाल CCF2:
		ioग_लिखो32be(0, &ccf->err_regs->errdis);
		ioग_लिखो32be(errपूर्णांकen, &ccf->err_regs->errपूर्णांकen);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ccf_निजी *ccf = dev_get_drvdata(&pdev->dev);

	चयन (ccf->info->version) अणु
	हाल CCF1:
		ioग_लिखो32be(0, &ccf->err_regs->errdis);
		अवरोध;

	हाल CCF2:
		/*
		 * We clear errdis on ccf1 because that's the only way to
		 * disable पूर्णांकerrupts, but on ccf2 there's no need to disable
		 * detection.
		 */
		ioग_लिखो32be(0, &ccf->err_regs->errपूर्णांकen);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ccf_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = ccf_matches,
	पूर्ण,
	.probe = ccf_probe,
	.हटाओ = ccf_हटाओ,
पूर्ण;

module_platक्रमm_driver(ccf_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Freescale Semiconductor");
MODULE_DESCRIPTION("Freescale CoreNet Coherency Fabric error reporting");
