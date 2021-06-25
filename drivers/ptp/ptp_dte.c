<शैली गुरु>
/*
 * Copyright 2017 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/types.h>

#घोषणा DTE_NCO_LOW_TIME_REG	0x00
#घोषणा DTE_NCO_TIME_REG	0x04
#घोषणा DTE_NCO_OVERFLOW_REG	0x08
#घोषणा DTE_NCO_INC_REG		0x0c

#घोषणा DTE_NCO_SUM2_MASK	0xffffffff
#घोषणा DTE_NCO_SUM2_SHIFT	4ULL

#घोषणा DTE_NCO_SUM3_MASK	0xff
#घोषणा DTE_NCO_SUM3_SHIFT	36ULL
#घोषणा DTE_NCO_SUM3_WR_SHIFT	8

#घोषणा DTE_NCO_TS_WRAP_MASK	0xfff
#घोषणा DTE_NCO_TS_WRAP_LSHIFT	32

#घोषणा DTE_NCO_INC_DEFAULT	0x80000000
#घोषणा DTE_NUM_REGS_TO_RESTORE	4

/* Full wrap around is 44bits in ns (~4.887 hrs) */
#घोषणा DTE_WRAP_AROUND_NSEC_SHIFT 44

/* 44 bits NCO */
#घोषणा DTE_NCO_MAX_NS	0xFFFFFFFFFFFLL

/* 125MHz with 3.29 reg cfg */
#घोषणा DTE_PPB_ADJ(ppb) (u32)(भाग64_u64((((u64)असल(ppb) * BIT(28)) +\
				      62500000ULL), 125000000ULL))

/* ptp dte priv काष्ठाure */
काष्ठा ptp_dte अणु
	व्योम __iomem *regs;
	काष्ठा ptp_घड़ी *ptp_clk;
	काष्ठा ptp_घड़ी_info caps;
	काष्ठा device *dev;
	u32 ts_ovf_last;
	u32 ts_wrap_cnt;
	spinlock_t lock;
	u32 reg_val[DTE_NUM_REGS_TO_RESTORE];
पूर्ण;

अटल व्योम dte_ग_लिखो_nco(व्योम __iomem *regs, s64 ns)
अणु
	u32 sum2, sum3;

	sum2 = (u32)((ns >> DTE_NCO_SUM2_SHIFT) & DTE_NCO_SUM2_MASK);
	/* compensate क्रम ignoring sum1 */
	अगर (sum2 != DTE_NCO_SUM2_MASK)
		sum2++;

	/* to ग_लिखो sum3, bits [15:8] needs to be written */
	sum3 = (u32)(((ns >> DTE_NCO_SUM3_SHIFT) & DTE_NCO_SUM3_MASK) <<
		     DTE_NCO_SUM3_WR_SHIFT);

	ग_लिखोl(0, (regs + DTE_NCO_LOW_TIME_REG));
	ग_लिखोl(sum2, (regs + DTE_NCO_TIME_REG));
	ग_लिखोl(sum3, (regs + DTE_NCO_OVERFLOW_REG));
पूर्ण

अटल s64 dte_पढ़ो_nco(व्योम __iomem *regs)
अणु
	u32 sum2, sum3;
	s64 ns;

	/*
	 * ignoring sum1 (4 bits) gives a 16ns resolution, which
	 * works due to the async रेजिस्टर पढ़ो.
	 */
	sum3 = पढ़ोl(regs + DTE_NCO_OVERFLOW_REG) & DTE_NCO_SUM3_MASK;
	sum2 = पढ़ोl(regs + DTE_NCO_TIME_REG);
	ns = ((s64)sum3 << DTE_NCO_SUM3_SHIFT) |
		 ((s64)sum2 << DTE_NCO_SUM2_SHIFT);

	वापस ns;
पूर्ण

अटल व्योम dte_ग_लिखो_nco_delta(काष्ठा ptp_dte *ptp_dte, s64 delta)
अणु
	s64 ns;

	ns = dte_पढ़ो_nco(ptp_dte->regs);

	/* handle wraparound conditions */
	अगर ((delta < 0) && (असल(delta) > ns)) अणु
		अगर (ptp_dte->ts_wrap_cnt) अणु
			ns += DTE_NCO_MAX_NS + delta;
			ptp_dte->ts_wrap_cnt--;
		पूर्ण अन्यथा अणु
			ns = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ns += delta;
		अगर (ns > DTE_NCO_MAX_NS) अणु
			ptp_dte->ts_wrap_cnt++;
			ns -= DTE_NCO_MAX_NS;
		पूर्ण
	पूर्ण

	dte_ग_लिखो_nco(ptp_dte->regs, ns);

	ptp_dte->ts_ovf_last = (ns >> DTE_NCO_TS_WRAP_LSHIFT) &
			DTE_NCO_TS_WRAP_MASK;
पूर्ण

अटल s64 dte_पढ़ो_nco_with_ovf(काष्ठा ptp_dte *ptp_dte)
अणु
	u32 ts_ovf;
	s64 ns = 0;

	ns = dte_पढ़ो_nco(ptp_dte->regs);

	/*Timestamp overflow: 8 LSB bits of sum3, 4 MSB bits of sum2 */
	ts_ovf = (ns >> DTE_NCO_TS_WRAP_LSHIFT) & DTE_NCO_TS_WRAP_MASK;

	/* Check क्रम wrap around */
	अगर (ts_ovf < ptp_dte->ts_ovf_last)
		ptp_dte->ts_wrap_cnt++;

	ptp_dte->ts_ovf_last = ts_ovf;

	/* adjust क्रम wraparounds */
	ns += (s64)(BIT_ULL(DTE_WRAP_AROUND_NSEC_SHIFT) * ptp_dte->ts_wrap_cnt);

	वापस ns;
पूर्ण

अटल पूर्णांक ptp_dte_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	u32 nco_incr;
	अचिन्हित दीर्घ flags;
	काष्ठा ptp_dte *ptp_dte = container_of(ptp, काष्ठा ptp_dte, caps);

	अगर (असल(ppb) > ptp_dte->caps.max_adj) अणु
		dev_err(ptp_dte->dev, "ppb adj too big\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ppb < 0)
		nco_incr = DTE_NCO_INC_DEFAULT - DTE_PPB_ADJ(ppb);
	अन्यथा
		nco_incr = DTE_NCO_INC_DEFAULT + DTE_PPB_ADJ(ppb);

	spin_lock_irqsave(&ptp_dte->lock, flags);
	ग_लिखोl(nco_incr, ptp_dte->regs + DTE_NCO_INC_REG);
	spin_unlock_irqrestore(&ptp_dte->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_dte_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ptp_dte *ptp_dte = container_of(ptp, काष्ठा ptp_dte, caps);

	spin_lock_irqsave(&ptp_dte->lock, flags);
	dte_ग_लिखो_nco_delta(ptp_dte, delta);
	spin_unlock_irqrestore(&ptp_dte->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_dte_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ptp_dte *ptp_dte = container_of(ptp, काष्ठा ptp_dte, caps);

	spin_lock_irqsave(&ptp_dte->lock, flags);
	*ts = ns_to_बारpec64(dte_पढ़ो_nco_with_ovf(ptp_dte));
	spin_unlock_irqrestore(&ptp_dte->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_dte_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			     स्थिर काष्ठा बारpec64 *ts)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ptp_dte *ptp_dte = container_of(ptp, काष्ठा ptp_dte, caps);

	spin_lock_irqsave(&ptp_dte->lock, flags);

	/* Disable nco increment */
	ग_लिखोl(0, ptp_dte->regs + DTE_NCO_INC_REG);

	dte_ग_लिखो_nco(ptp_dte->regs, बारpec64_to_ns(ts));

	/* reset overflow and wrap counter */
	ptp_dte->ts_ovf_last = 0;
	ptp_dte->ts_wrap_cnt = 0;

	/* Enable nco increment */
	ग_लिखोl(DTE_NCO_INC_DEFAULT, ptp_dte->regs + DTE_NCO_INC_REG);

	spin_unlock_irqrestore(&ptp_dte->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_dte_enable(काष्ठा ptp_घड़ी_info *ptp,
			    काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info ptp_dte_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "DTE PTP timer",
	.max_adj	= 50000000,
	.n_ext_ts	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfreq	= ptp_dte_adjfreq,
	.adjसमय	= ptp_dte_adjसमय,
	.समय_लो64	= ptp_dte_समय_लो,
	.समय_रखो64	= ptp_dte_समय_रखो,
	.enable		= ptp_dte_enable,
पूर्ण;

अटल पूर्णांक ptp_dte_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ptp_dte *ptp_dte;
	काष्ठा device *dev = &pdev->dev;

	ptp_dte = devm_kzalloc(dev, माप(काष्ठा ptp_dte), GFP_KERNEL);
	अगर (!ptp_dte)
		वापस -ENOMEM;

	ptp_dte->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ptp_dte->regs))
		वापस PTR_ERR(ptp_dte->regs);

	spin_lock_init(&ptp_dte->lock);

	ptp_dte->dev = dev;
	ptp_dte->caps = ptp_dte_caps;
	ptp_dte->ptp_clk = ptp_घड़ी_रेजिस्टर(&ptp_dte->caps, &pdev->dev);
	अगर (IS_ERR(ptp_dte->ptp_clk)) अणु
		dev_err(dev,
			"%s: Failed to register ptp clock\n", __func__);
		वापस PTR_ERR(ptp_dte->ptp_clk);
	पूर्ण

	platक्रमm_set_drvdata(pdev, ptp_dte);

	dev_info(dev, "ptp clk probe done\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_dte_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ptp_dte *ptp_dte = platक्रमm_get_drvdata(pdev);
	u8 i;

	ptp_घड़ी_unरेजिस्टर(ptp_dte->ptp_clk);

	क्रम (i = 0; i < DTE_NUM_REGS_TO_RESTORE; i++)
		ग_लिखोl(0, ptp_dte->regs + (i * माप(u32)));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ptp_dte_suspend(काष्ठा device *dev)
अणु
	काष्ठा ptp_dte *ptp_dte = dev_get_drvdata(dev);
	u8 i;

	क्रम (i = 0; i < DTE_NUM_REGS_TO_RESTORE; i++) अणु
		ptp_dte->reg_val[i] =
			पढ़ोl(ptp_dte->regs + (i * माप(u32)));
	पूर्ण

	/* disable the nco */
	ग_लिखोl(0, ptp_dte->regs + DTE_NCO_INC_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_dte_resume(काष्ठा device *dev)
अणु
	काष्ठा ptp_dte *ptp_dte = dev_get_drvdata(dev);
	u8 i;

	क्रम (i = 0; i < DTE_NUM_REGS_TO_RESTORE; i++) अणु
		अगर ((i * माप(u32)) != DTE_NCO_OVERFLOW_REG)
			ग_लिखोl(ptp_dte->reg_val[i],
				(ptp_dte->regs + (i * माप(u32))));
		अन्यथा
			ग_लिखोl(((ptp_dte->reg_val[i] &
				DTE_NCO_SUM3_MASK) << DTE_NCO_SUM3_WR_SHIFT),
				(ptp_dte->regs + (i * माप(u32))));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ptp_dte_pm_ops = अणु
	.suspend = ptp_dte_suspend,
	.resume = ptp_dte_resume
पूर्ण;

#घोषणा PTP_DTE_PM_OPS	(&ptp_dte_pm_ops)
#अन्यथा
#घोषणा PTP_DTE_PM_OPS	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id ptp_dte_of_match[] = अणु
	अणु .compatible = "brcm,ptp-dte", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ptp_dte_of_match);

अटल काष्ठा platक्रमm_driver ptp_dte_driver = अणु
	.driver = अणु
		.name = "ptp-dte",
		.pm = PTP_DTE_PM_OPS,
		.of_match_table = ptp_dte_of_match,
	पूर्ण,
	.probe    = ptp_dte_probe,
	.हटाओ   = ptp_dte_हटाओ,
पूर्ण;
module_platक्रमm_driver(ptp_dte_driver);

MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("Broadcom DTE PTP Clock driver");
MODULE_LICENSE("GPL v2");
