<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mfd/mcp-sa11x0.c
 *
 *  Copyright (C) 2001-2005 Russell King
 *
 *  SA11x0 MCP (Mulसमयdia Communications Port) driver.
 *
 *  MCP पढ़ो/ग_लिखो समयouts from Jordi Colomer, rehacked by rmk.
 */
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/mfd/mcp.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <linux/platक्रमm_data/mfd-mcp-sa11x0.h>

#घोषणा DRIVER_NAME "sa11x0-mcp"

काष्ठा mcp_sa11x0 अणु
	व्योम __iomem	*base0;
	व्योम __iomem	*base1;
	u32		mccr0;
	u32		mccr1;
पूर्ण;

/* Register offsets */
#घोषणा MCCR0(m)	((m)->base0 + 0x00)
#घोषणा MCDR0(m)	((m)->base0 + 0x08)
#घोषणा MCDR1(m)	((m)->base0 + 0x0c)
#घोषणा MCDR2(m)	((m)->base0 + 0x10)
#घोषणा MCSR(m)		((m)->base0 + 0x18)
#घोषणा MCCR1(m)	((m)->base1 + 0x00)

#घोषणा priv(mcp)	((काष्ठा mcp_sa11x0 *)mcp_priv(mcp))

अटल व्योम
mcp_sa11x0_set_telecom_भागisor(काष्ठा mcp *mcp, अचिन्हित पूर्णांक भागisor)
अणु
	काष्ठा mcp_sa11x0 *m = priv(mcp);

	भागisor /= 32;

	m->mccr0 &= ~0x00007f00;
	m->mccr0 |= भागisor << 8;
	ग_लिखोl_relaxed(m->mccr0, MCCR0(m));
पूर्ण

अटल व्योम
mcp_sa11x0_set_audio_भागisor(काष्ठा mcp *mcp, अचिन्हित पूर्णांक भागisor)
अणु
	काष्ठा mcp_sa11x0 *m = priv(mcp);

	भागisor /= 32;

	m->mccr0 &= ~0x0000007f;
	m->mccr0 |= भागisor;
	ग_लिखोl_relaxed(m->mccr0, MCCR0(m));
पूर्ण

/*
 * Write data to the device.  The bit should be set after 3 subframe
 * बार (each frame is 64 घड़ीs).  We रुको a maximum of 6 subframes.
 * We really should try करोing something more productive जबतक we
 * रुको.
 */
अटल व्योम
mcp_sa11x0_ग_लिखो(काष्ठा mcp *mcp, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा mcp_sa11x0 *m = priv(mcp);
	पूर्णांक ret = -ETIME;
	पूर्णांक i;

	ग_लिखोl_relaxed(reg << 17 | MCDR2_Wr | (val & 0xffff), MCDR2(m));

	क्रम (i = 0; i < 2; i++) अणु
		udelay(mcp->rw_समयout);
		अगर (पढ़ोl_relaxed(MCSR(m)) & MCSR_CWC) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		prपूर्णांकk(KERN_WARNING "mcp: write timed out\n");
पूर्ण

/*
 * Read data from the device.  The bit should be set after 3 subframe
 * बार (each frame is 64 घड़ीs).  We रुको a maximum of 6 subframes.
 * We really should try करोing something more productive जबतक we
 * रुको.
 */
अटल अचिन्हित पूर्णांक
mcp_sa11x0_पढ़ो(काष्ठा mcp *mcp, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा mcp_sa11x0 *m = priv(mcp);
	पूर्णांक ret = -ETIME;
	पूर्णांक i;

	ग_लिखोl_relaxed(reg << 17 | MCDR2_Rd, MCDR2(m));

	क्रम (i = 0; i < 2; i++) अणु
		udelay(mcp->rw_समयout);
		अगर (पढ़ोl_relaxed(MCSR(m)) & MCSR_CRC) अणु
			ret = पढ़ोl_relaxed(MCDR2(m)) & 0xffff;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		prपूर्णांकk(KERN_WARNING "mcp: read timed out\n");

	वापस ret;
पूर्ण

अटल व्योम mcp_sa11x0_enable(काष्ठा mcp *mcp)
अणु
	काष्ठा mcp_sa11x0 *m = priv(mcp);

	ग_लिखोl(-1, MCSR(m));
	m->mccr0 |= MCCR0_MCE;
	ग_लिखोl_relaxed(m->mccr0, MCCR0(m));
पूर्ण

अटल व्योम mcp_sa11x0_disable(काष्ठा mcp *mcp)
अणु
	काष्ठा mcp_sa11x0 *m = priv(mcp);

	m->mccr0 &= ~MCCR0_MCE;
	ग_लिखोl_relaxed(m->mccr0, MCCR0(m));
पूर्ण

/*
 * Our methods.
 */
अटल काष्ठा mcp_ops mcp_sa11x0 = अणु
	.set_telecom_भागisor	= mcp_sa11x0_set_telecom_भागisor,
	.set_audio_भागisor	= mcp_sa11x0_set_audio_भागisor,
	.reg_ग_लिखो		= mcp_sa11x0_ग_लिखो,
	.reg_पढ़ो		= mcp_sa11x0_पढ़ो,
	.enable			= mcp_sa11x0_enable,
	.disable		= mcp_sa11x0_disable,
पूर्ण;

अटल पूर्णांक mcp_sa11x0_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mcp_plat_data *data = dev_get_platdata(&dev->dev);
	काष्ठा resource *mem0, *mem1;
	काष्ठा mcp_sa11x0 *m;
	काष्ठा mcp *mcp;
	पूर्णांक ret;

	अगर (!data)
		वापस -ENODEV;

	mem0 = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	mem1 = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);
	अगर (!mem0 || !mem1)
		वापस -ENXIO;

	अगर (!request_mem_region(mem0->start, resource_size(mem0),
				DRIVER_NAME)) अणु
		ret = -EBUSY;
		जाओ err_mem0;
	पूर्ण

	अगर (!request_mem_region(mem1->start, resource_size(mem1),
				DRIVER_NAME)) अणु
		ret = -EBUSY;
		जाओ err_mem1;
	पूर्ण

	mcp = mcp_host_alloc(&dev->dev, माप(काष्ठा mcp_sa11x0));
	अगर (!mcp) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	mcp->owner		= THIS_MODULE;
	mcp->ops		= &mcp_sa11x0;
	mcp->sclk_rate		= data->sclk_rate;

	m = priv(mcp);
	m->mccr0 = data->mccr0 | 0x7f7f;
	m->mccr1 = data->mccr1;

	m->base0 = ioremap(mem0->start, resource_size(mem0));
	m->base1 = ioremap(mem1->start, resource_size(mem1));
	अगर (!m->base0 || !m->base1) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	platक्रमm_set_drvdata(dev, mcp);

	/*
	 * Initialise device.  Note that we initially
	 * set the sampling rate to minimum.
	 */
	ग_लिखोl_relaxed(-1, MCSR(m));
	ग_लिखोl_relaxed(m->mccr1, MCCR1(m));
	ग_लिखोl_relaxed(m->mccr0, MCCR0(m));

	/*
	 * Calculate the पढ़ो/ग_लिखो समयout (us) from the bit घड़ी
	 * rate.  This is the period क्रम 3 64-bit frames.  Always
	 * round this समय up.
	 */
	mcp->rw_समयout = DIV_ROUND_UP(64 * 3 * 1000000, mcp->sclk_rate);

	ret = mcp_host_add(mcp, data->codec_pdata);
	अगर (ret == 0)
		वापस 0;

 err_ioremap:
	iounmap(m->base1);
	iounmap(m->base0);
	mcp_host_मुक्त(mcp);
 err_alloc:
	release_mem_region(mem1->start, resource_size(mem1));
 err_mem1:
	release_mem_region(mem0->start, resource_size(mem0));
 err_mem0:
	वापस ret;
पूर्ण

अटल पूर्णांक mcp_sa11x0_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mcp *mcp = platक्रमm_get_drvdata(dev);
	काष्ठा mcp_sa11x0 *m = priv(mcp);
	काष्ठा resource *mem0, *mem1;

	अगर (m->mccr0 & MCCR0_MCE)
		dev_warn(&dev->dev,
			 "device left active (missing disable call?)\n");

	mem0 = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	mem1 = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);

	mcp_host_del(mcp);
	iounmap(m->base1);
	iounmap(m->base0);
	mcp_host_मुक्त(mcp);
	release_mem_region(mem1->start, resource_size(mem1));
	release_mem_region(mem0->start, resource_size(mem0));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mcp_sa11x0_suspend(काष्ठा device *dev)
अणु
	काष्ठा mcp_sa11x0 *m = priv(dev_get_drvdata(dev));

	अगर (m->mccr0 & MCCR0_MCE)
		dev_warn(dev, "device left active (missing disable call?)\n");

	ग_लिखोl(m->mccr0 & ~MCCR0_MCE, MCCR0(m));

	वापस 0;
पूर्ण

अटल पूर्णांक mcp_sa11x0_resume(काष्ठा device *dev)
अणु
	काष्ठा mcp_sa11x0 *m = priv(dev_get_drvdata(dev));

	ग_लिखोl_relaxed(m->mccr1, MCCR1(m));
	ग_लिखोl_relaxed(m->mccr0, MCCR0(m));

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mcp_sa11x0_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend = mcp_sa11x0_suspend,
	.मुक्तze = mcp_sa11x0_suspend,
	.घातeroff = mcp_sa11x0_suspend,
	.resume_noirq = mcp_sa11x0_resume,
	.thaw_noirq = mcp_sa11x0_resume,
	.restore_noirq = mcp_sa11x0_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा platक्रमm_driver mcp_sa11x0_driver = अणु
	.probe		= mcp_sa11x0_probe,
	.हटाओ		= mcp_sa11x0_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.pm	= &mcp_sa11x0_pm_ops,
	पूर्ण,
पूर्ण;

/*
 * This needs re-working
 */
module_platक्रमm_driver(mcp_sa11x0_driver);

MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("SA11x0 multimedia communications port driver");
MODULE_LICENSE("GPL");
