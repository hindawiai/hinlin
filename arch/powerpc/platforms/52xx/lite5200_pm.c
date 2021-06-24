<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mpc52xx.h>
#समावेश <यंत्र/चयन_to.h>

/* defined in lite5200_sleep.S and only used here */
बाह्य व्योम lite5200_low_घातer(व्योम __iomem *sram, व्योम __iomem *mbar);

अटल काष्ठा mpc52xx_cdm __iomem *cdm;
अटल काष्ठा mpc52xx_पूर्णांकr __iomem *pic;
अटल काष्ठा mpc52xx_sdma __iomem *bes;
अटल काष्ठा mpc52xx_xlb __iomem *xlb;
अटल काष्ठा mpc52xx_gpio __iomem *gps;
अटल काष्ठा mpc52xx_gpio_wkup __iomem *gpw;
अटल व्योम __iomem *pci;
अटल व्योम __iomem *sram;
अटल स्थिर पूर्णांक sram_size = 0x4000;	/* 16 kBytes */
अटल व्योम __iomem *mbar;

अटल suspend_state_t lite5200_pm_target_state;

अटल पूर्णांक lite5200_pm_valid(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
	हाल PM_SUSPEND_MEM:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक lite5200_pm_begin(suspend_state_t state)
अणु
	अगर (lite5200_pm_valid(state)) अणु
		lite5200_pm_target_state = state;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक lite5200_pm_prepare(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id immr_ids[] = अणु
		अणु .compatible = "fsl,mpc5200-immr", पूर्ण,
		अणु .compatible = "fsl,mpc5200b-immr", पूर्ण,
		अणु .type = "soc", .compatible = "mpc5200", पूर्ण, /* lite5200 */
		अणु .type = "builtin", .compatible = "mpc5200", पूर्ण, /* efika */
		अणुपूर्ण
	पूर्ण;
	u64 regaddr64 = 0;
	स्थिर u32 *regaddr_p;

	/* deep sleep? let mpc52xx code handle that */
	अगर (lite5200_pm_target_state == PM_SUSPEND_STANDBY)
		वापस mpc52xx_pm_prepare();

	अगर (lite5200_pm_target_state != PM_SUSPEND_MEM)
		वापस -EINVAL;

	/* map रेजिस्टरs */
	np = of_find_matching_node(शून्य, immr_ids);
	regaddr_p = of_get_address(np, 0, शून्य, शून्य);
	अगर (regaddr_p)
		regaddr64 = of_translate_address(np, regaddr_p);
	of_node_put(np);

	mbar = ioremap((u32) regaddr64, 0xC000);
	अगर (!mbar) अणु
		prपूर्णांकk(KERN_ERR "%s:%i Error mapping registers\n", __func__, __LINE__);
		वापस -ENOSYS;
	पूर्ण

	cdm = mbar + 0x200;
	pic = mbar + 0x500;
	gps = mbar + 0xb00;
	gpw = mbar + 0xc00;
	pci = mbar + 0xd00;
	bes = mbar + 0x1200;
	xlb = mbar + 0x1f00;
	sram = mbar + 0x8000;

	वापस 0;
पूर्ण

/* save and restore रेजिस्टरs not bound to any real devices */
अटल काष्ठा mpc52xx_cdm scdm;
अटल काष्ठा mpc52xx_पूर्णांकr spic;
अटल काष्ठा mpc52xx_sdma sbes;
अटल काष्ठा mpc52xx_xlb sxlb;
अटल काष्ठा mpc52xx_gpio sgps;
अटल काष्ठा mpc52xx_gpio_wkup sgpw;
अटल अक्षर spci[0x200];

अटल व्योम lite5200_save_regs(व्योम)
अणु
	_स_नकल_fromio(&spic, pic, माप(*pic));
	_स_नकल_fromio(&sbes, bes, माप(*bes));
	_स_नकल_fromio(&scdm, cdm, माप(*cdm));
	_स_नकल_fromio(&sxlb, xlb, माप(*xlb));
	_स_नकल_fromio(&sgps, gps, माप(*gps));
	_स_नकल_fromio(&sgpw, gpw, माप(*gpw));
	_स_नकल_fromio(spci, pci, 0x200);

	_स_नकल_fromio(saved_sram, sram, sram_size);
पूर्ण

अटल व्योम lite5200_restore_regs(व्योम)
अणु
	पूर्णांक i;
	_स_नकल_toio(sram, saved_sram, sram_size);

	/* PCI Configuration */
	_स_नकल_toio(pci, spci, 0x200);

	/*
	 * GPIOs. Interrupt Master Enable has higher address then other
	 * रेजिस्टरs, so just स_नकल is ok.
	 */
	_स_नकल_toio(gpw, &sgpw, माप(*gpw));
	_स_नकल_toio(gps, &sgps, माप(*gps));


	/* XLB Arbitrer */
	out_be32(&xlb->snoop_winकरोw, sxlb.snoop_winकरोw);
	out_be32(&xlb->master_priority, sxlb.master_priority);
	out_be32(&xlb->master_pri_enable, sxlb.master_pri_enable);

	/* enable */
	out_be32(&xlb->पूर्णांक_enable, sxlb.पूर्णांक_enable);
	out_be32(&xlb->config, sxlb.config);


	/* CDM - Clock Distribution Module */
	out_8(&cdm->ipb_clk_sel, scdm.ipb_clk_sel);
	out_8(&cdm->pci_clk_sel, scdm.pci_clk_sel);

	out_8(&cdm->ext_48mhz_en, scdm.ext_48mhz_en);
	out_8(&cdm->fd_enable, scdm.fd_enable);
	out_be16(&cdm->fd_counters, scdm.fd_counters);

	out_be32(&cdm->clk_enables, scdm.clk_enables);

	out_8(&cdm->osc_disable, scdm.osc_disable);

	out_be16(&cdm->mclken_भाग_psc1, scdm.mclken_भाग_psc1);
	out_be16(&cdm->mclken_भाग_psc2, scdm.mclken_भाग_psc2);
	out_be16(&cdm->mclken_भाग_psc3, scdm.mclken_भाग_psc3);
	out_be16(&cdm->mclken_भाग_psc6, scdm.mclken_भाग_psc6);


	/* BESTCOMM */
	out_be32(&bes->taskBar, sbes.taskBar);
	out_be32(&bes->currentPoपूर्णांकer, sbes.currentPoपूर्णांकer);
	out_be32(&bes->endPoपूर्णांकer, sbes.endPoपूर्णांकer);
	out_be32(&bes->variablePoपूर्णांकer, sbes.variablePoपूर्णांकer);

	out_8(&bes->IntVect1, sbes.IntVect1);
	out_8(&bes->IntVect2, sbes.IntVect2);
	out_be16(&bes->PtdCntrl, sbes.PtdCntrl);

	क्रम (i=0; i<32; i++)
		out_8(&bes->ipr[i], sbes.ipr[i]);

	out_be32(&bes->cReqSelect, sbes.cReqSelect);
	out_be32(&bes->task_size0, sbes.task_size0);
	out_be32(&bes->task_size1, sbes.task_size1);
	out_be32(&bes->MDEDebug, sbes.MDEDebug);
	out_be32(&bes->ADSDebug, sbes.ADSDebug);
	out_be32(&bes->Value1, sbes.Value1);
	out_be32(&bes->Value2, sbes.Value2);
	out_be32(&bes->Control, sbes.Control);
	out_be32(&bes->Status, sbes.Status);
	out_be32(&bes->PTDDebug, sbes.PTDDebug);

	/* restore tasks */
	क्रम (i=0; i<16; i++)
		out_be16(&bes->tcr[i], sbes.tcr[i]);

	/* enable पूर्णांकerrupts */
	out_be32(&bes->IntPend, sbes.IntPend);
	out_be32(&bes->IntMask, sbes.IntMask);


	/* PIC */
	out_be32(&pic->per_pri1, spic.per_pri1);
	out_be32(&pic->per_pri2, spic.per_pri2);
	out_be32(&pic->per_pri3, spic.per_pri3);

	out_be32(&pic->मुख्य_pri1, spic.मुख्य_pri1);
	out_be32(&pic->मुख्य_pri2, spic.मुख्य_pri2);

	out_be32(&pic->enc_status, spic.enc_status);

	/* unmask and enable पूर्णांकerrupts */
	out_be32(&pic->per_mask, spic.per_mask);
	out_be32(&pic->मुख्य_mask, spic.मुख्य_mask);
	out_be32(&pic->ctrl, spic.ctrl);
पूर्ण

अटल पूर्णांक lite5200_pm_enter(suspend_state_t state)
अणु
	/* deep sleep? let mpc52xx code handle that */
	अगर (state == PM_SUSPEND_STANDBY) अणु
		वापस mpc52xx_pm_enter(state);
	पूर्ण

	lite5200_save_regs();

	/* effectively save FP regs */
	enable_kernel_fp();

	lite5200_low_घातer(sram, mbar);

	lite5200_restore_regs();

	iounmap(mbar);
	वापस 0;
पूर्ण

अटल व्योम lite5200_pm_finish(व्योम)
अणु
	/* deep sleep? let mpc52xx code handle that */
	अगर (lite5200_pm_target_state == PM_SUSPEND_STANDBY)
		mpc52xx_pm_finish();
पूर्ण

अटल व्योम lite5200_pm_end(व्योम)
अणु
	lite5200_pm_target_state = PM_SUSPEND_ON;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops lite5200_pm_ops = अणु
	.valid		= lite5200_pm_valid,
	.begin		= lite5200_pm_begin,
	.prepare	= lite5200_pm_prepare,
	.enter		= lite5200_pm_enter,
	.finish		= lite5200_pm_finish,
	.end		= lite5200_pm_end,
पूर्ण;

पूर्णांक __init lite5200_pm_init(व्योम)
अणु
	suspend_set_ops(&lite5200_pm_ops);
	वापस 0;
पूर्ण
