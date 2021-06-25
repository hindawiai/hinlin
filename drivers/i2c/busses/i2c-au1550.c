<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * i2c-au1550.c: SMBus (i2c) adapter क्रम Alchemy PSC पूर्णांकerface
 * Copyright (C) 2004 Embedded Edge, LLC <dan@embeddededge.com>
 *
 * 2.6 port by Matt Porter <mporter@kernel.crashing.org>
 *
 * The करोcumentation describes this as an SMBus controller, but it करोesn't
 * understand any of the SMBus protocol in hardware.  It's really an I2C
 * controller that could emulate most of the SMBus in software.
 *
 * This is just a skeleton adapter to use with the Au1550 PSC
 * algorithm.  It was developed क्रम the Pb1550, but will work with
 * any Au1550 board that has a similar PSC configuration.
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_psc.h>

#घोषणा PSC_SEL		0x00
#घोषणा PSC_CTRL	0x04
#घोषणा PSC_SMBCFG	0x08
#घोषणा PSC_SMBMSK	0x0C
#घोषणा PSC_SMBPCR	0x10
#घोषणा PSC_SMBSTAT	0x14
#घोषणा PSC_SMBEVNT	0x18
#घोषणा PSC_SMBTXRX	0x1C
#घोषणा PSC_SMBTMR	0x20

काष्ठा i2c_au1550_data अणु
	व्योम __iomem *psc_base;
	पूर्णांक	xfer_समयout;
	काष्ठा i2c_adapter adap;
पूर्ण;

अटल अंतरभूत व्योम WR(काष्ठा i2c_au1550_data *a, पूर्णांक r, अचिन्हित दीर्घ v)
अणु
	__raw_ग_लिखोl(v, a->psc_base + r);
	wmb();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ RD(काष्ठा i2c_au1550_data *a, पूर्णांक r)
अणु
	वापस __raw_पढ़ोl(a->psc_base + r);
पूर्ण

अटल पूर्णांक रुको_xfer_करोne(काष्ठा i2c_au1550_data *adap)
अणु
	पूर्णांक i;

	/* Wait क्रम Tx Buffer Empty */
	क्रम (i = 0; i < adap->xfer_समयout; i++) अणु
		अगर (RD(adap, PSC_SMBSTAT) & PSC_SMBSTAT_TE)
			वापस 0;

		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक रुको_ack(काष्ठा i2c_au1550_data *adap)
अणु
	अचिन्हित दीर्घ stat;

	अगर (रुको_xfer_करोne(adap))
		वापस -ETIMEDOUT;

	stat = RD(adap, PSC_SMBEVNT);
	अगर ((stat & (PSC_SMBEVNT_DN | PSC_SMBEVNT_AN | PSC_SMBEVNT_AL)) != 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक रुको_master_करोne(काष्ठा i2c_au1550_data *adap)
अणु
	पूर्णांक i;

	/* Wait क्रम Master Done. */
	क्रम (i = 0; i < 2 * adap->xfer_समयout; i++) अणु
		अगर ((RD(adap, PSC_SMBEVNT) & PSC_SMBEVNT_MD) != 0)
			वापस 0;
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
करो_address(काष्ठा i2c_au1550_data *adap, अचिन्हित पूर्णांक addr, पूर्णांक rd, पूर्णांक q)
अणु
	अचिन्हित दीर्घ stat;

	/* Reset the FIFOs, clear events. */
	stat = RD(adap, PSC_SMBSTAT);
	WR(adap, PSC_SMBEVNT, PSC_SMBEVNT_ALLCLR);

	अगर (!(stat & PSC_SMBSTAT_TE) || !(stat & PSC_SMBSTAT_RE)) अणु
		WR(adap, PSC_SMBPCR, PSC_SMBPCR_DC);
		जबतक ((RD(adap, PSC_SMBPCR) & PSC_SMBPCR_DC) != 0)
			cpu_relax();
		udelay(50);
	पूर्ण

	/* Write out the i2c chip address and specअगरy operation */
	addr <<= 1;
	अगर (rd)
		addr |= 1;

	/* zero-byte xfers stop immediately */
	अगर (q)
		addr |= PSC_SMBTXRX_STP;

	/* Put byte पूर्णांकo fअगरo, start up master. */
	WR(adap, PSC_SMBTXRX, addr);
	WR(adap, PSC_SMBPCR, PSC_SMBPCR_MS);
	अगर (रुको_ack(adap))
		वापस -EIO;
	वापस (q) ? रुको_master_करोne(adap) : 0;
पूर्ण

अटल पूर्णांक रुको_क्रम_rx_byte(काष्ठा i2c_au1550_data *adap, अचिन्हित अक्षर *out)
अणु
	पूर्णांक j;

	अगर (रुको_xfer_करोne(adap))
		वापस -EIO;

	j =  adap->xfer_समयout * 100;
	करो अणु
		j--;
		अगर (j <= 0)
			वापस -EIO;

		अगर ((RD(adap, PSC_SMBSTAT) & PSC_SMBSTAT_RE) == 0)
			j = 0;
		अन्यथा
			udelay(1);
	पूर्ण जबतक (j > 0);

	*out = RD(adap, PSC_SMBTXRX);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_पढ़ो(काष्ठा i2c_au1550_data *adap, अचिन्हित अक्षर *buf,
		    अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (len == 0)
		वापस 0;

	/* A पढ़ो is perक्रमmed by stuffing the transmit fअगरo with
	 * zero bytes क्रम timing, रुकोing क्रम bytes to appear in the
	 * receive fअगरo, then पढ़ोing the bytes.
	 */
	i = 0;
	जबतक (i < (len - 1)) अणु
		WR(adap, PSC_SMBTXRX, 0);
		अगर (रुको_क्रम_rx_byte(adap, &buf[i]))
			वापस -EIO;

		i++;
	पूर्ण

	/* The last byte has to indicate transfer करोne. */
	WR(adap, PSC_SMBTXRX, PSC_SMBTXRX_STP);
	अगर (रुको_master_करोne(adap))
		वापस -EIO;

	buf[i] = (अचिन्हित अक्षर)(RD(adap, PSC_SMBTXRX) & 0xff);
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_ग_लिखो(काष्ठा i2c_au1550_data *adap, अचिन्हित अक्षर *buf,
		     अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ data;

	अगर (len == 0)
		वापस 0;

	i = 0;
	जबतक (i < (len-1)) अणु
		data = buf[i];
		WR(adap, PSC_SMBTXRX, data);
		अगर (रुको_ack(adap))
			वापस -EIO;
		i++;
	पूर्ण

	/* The last byte has to indicate transfer करोne. */
	data = buf[i];
	data |= PSC_SMBTXRX_STP;
	WR(adap, PSC_SMBTXRX, data);
	अगर (रुको_master_करोne(adap))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक
au1550_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा i2c_au1550_data *adap = i2c_adap->algo_data;
	काष्ठा i2c_msg *p;
	पूर्णांक i, err = 0;

	WR(adap, PSC_CTRL, PSC_CTRL_ENABLE);

	क्रम (i = 0; !err && i < num; i++) अणु
		p = &msgs[i];
		err = करो_address(adap, p->addr, p->flags & I2C_M_RD,
				 (p->len == 0));
		अगर (err || !p->len)
			जारी;
		अगर (p->flags & I2C_M_RD)
			err = i2c_पढ़ो(adap, p->buf, p->len);
		अन्यथा
			err = i2c_ग_लिखो(adap, p->buf, p->len);
	पूर्ण

	/* Return the number of messages processed, or the error code.
	*/
	अगर (err == 0)
		err = num;

	WR(adap, PSC_CTRL, PSC_CTRL_SUSPEND);

	वापस err;
पूर्ण

अटल u32 au1550_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm au1550_algo = अणु
	.master_xfer	= au1550_xfer,
	.functionality	= au1550_func,
पूर्ण;

अटल व्योम i2c_au1550_setup(काष्ठा i2c_au1550_data *priv)
अणु
	अचिन्हित दीर्घ cfg;

	WR(priv, PSC_CTRL, PSC_CTRL_DISABLE);
	WR(priv, PSC_SEL, PSC_SEL_PS_SMBUSMODE);
	WR(priv, PSC_SMBCFG, 0);
	WR(priv, PSC_CTRL, PSC_CTRL_ENABLE);
	जबतक ((RD(priv, PSC_SMBSTAT) & PSC_SMBSTAT_SR) == 0)
		cpu_relax();

	cfg = PSC_SMBCFG_RT_FIFO8 | PSC_SMBCFG_TT_FIFO8 | PSC_SMBCFG_DD_DISABLE;
	WR(priv, PSC_SMBCFG, cfg);

	/* Divide by 8 to get a 6.25 MHz घड़ी.  The later protocol
	 * timings are based on this घड़ी.
	 */
	cfg |= PSC_SMBCFG_SET_DIV(PSC_SMBCFG_DIV8);
	WR(priv, PSC_SMBCFG, cfg);
	WR(priv, PSC_SMBMSK, PSC_SMBMSK_ALLMASK);

	/* Set the protocol समयr values.  See Table 71 in the
	 * Au1550 Data Book क्रम standard timing values.
	 */
	WR(priv, PSC_SMBTMR, PSC_SMBTMR_SET_TH(0) | PSC_SMBTMR_SET_PS(20) | \
		PSC_SMBTMR_SET_PU(20) | PSC_SMBTMR_SET_SH(20) | \
		PSC_SMBTMR_SET_SU(20) | PSC_SMBTMR_SET_CL(20) | \
		PSC_SMBTMR_SET_CH(20));

	cfg |= PSC_SMBCFG_DE_ENABLE;
	WR(priv, PSC_SMBCFG, cfg);
	जबतक ((RD(priv, PSC_SMBSTAT) & PSC_SMBSTAT_SR) == 0)
		cpu_relax();

	WR(priv, PSC_CTRL, PSC_CTRL_SUSPEND);
पूर्ण

अटल व्योम i2c_au1550_disable(काष्ठा i2c_au1550_data *priv)
अणु
	WR(priv, PSC_SMBCFG, 0);
	WR(priv, PSC_CTRL, PSC_CTRL_DISABLE);
पूर्ण

/*
 * रेजिस्टरing functions to load algorithms at runसमय
 * Prior to calling us, the 50MHz घड़ी frequency and routing
 * must have been set up क्रम the PSC indicated by the adapter.
 */
अटल पूर्णांक
i2c_au1550_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_au1550_data *priv;
	काष्ठा resource *r;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा i2c_au1550_data),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->psc_base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(priv->psc_base))
		वापस PTR_ERR(priv->psc_base);

	priv->xfer_समयout = 200;

	priv->adap.nr = pdev->id;
	priv->adap.algo = &au1550_algo;
	priv->adap.algo_data = priv;
	priv->adap.dev.parent = &pdev->dev;
	strlcpy(priv->adap.name, "Au1xxx PSC I2C", माप(priv->adap.name));

	/* Now, set up the PSC क्रम SMBus PIO mode. */
	i2c_au1550_setup(priv);

	ret = i2c_add_numbered_adapter(&priv->adap);
	अगर (ret) अणु
		i2c_au1550_disable(priv);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_au1550_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_au1550_data *priv = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&priv->adap);
	i2c_au1550_disable(priv);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक i2c_au1550_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_au1550_data *priv = dev_get_drvdata(dev);

	i2c_au1550_disable(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_au1550_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_au1550_data *priv = dev_get_drvdata(dev);

	i2c_au1550_setup(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops i2c_au1550_pmops = अणु
	.suspend	= i2c_au1550_suspend,
	.resume		= i2c_au1550_resume,
पूर्ण;

#घोषणा AU1XPSC_SMBUS_PMOPS (&i2c_au1550_pmops)

#अन्यथा
#घोषणा AU1XPSC_SMBUS_PMOPS शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver au1xpsc_smbus_driver = अणु
	.driver = अणु
		.name	= "au1xpsc_smbus",
		.pm	= AU1XPSC_SMBUS_PMOPS,
	पूर्ण,
	.probe		= i2c_au1550_probe,
	.हटाओ		= i2c_au1550_हटाओ,
पूर्ण;

module_platक्रमm_driver(au1xpsc_smbus_driver);

MODULE_AUTHOR("Dan Malek, Embedded Edge, LLC.");
MODULE_DESCRIPTION("SMBus adapter Alchemy pb1550");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:au1xpsc_smbus");
