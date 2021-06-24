<शैली गुरु>
/*
 * Copyright (C) 2017 Spपढ़ोtrum Communications Inc.
 *
 * SPDX-License-Identअगरier: GPL-2.0
 */

#समावेश <linux/delay.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sizes.h>

/* Registers definitions क्रम ADI controller */
#घोषणा REG_ADI_CTRL0			0x4
#घोषणा REG_ADI_CHN_PRIL		0x8
#घोषणा REG_ADI_CHN_PRIH		0xc
#घोषणा REG_ADI_INT_EN			0x10
#घोषणा REG_ADI_INT_RAW			0x14
#घोषणा REG_ADI_INT_MASK		0x18
#घोषणा REG_ADI_INT_CLR			0x1c
#घोषणा REG_ADI_GSSI_CFG0		0x20
#घोषणा REG_ADI_GSSI_CFG1		0x24
#घोषणा REG_ADI_RD_CMD			0x28
#घोषणा REG_ADI_RD_DATA			0x2c
#घोषणा REG_ADI_ARM_FIFO_STS		0x30
#घोषणा REG_ADI_STS			0x34
#घोषणा REG_ADI_EVT_FIFO_STS		0x38
#घोषणा REG_ADI_ARM_CMD_STS		0x3c
#घोषणा REG_ADI_CHN_EN			0x40
#घोषणा REG_ADI_CHN_ADDR(id)		(0x44 + (id - 2) * 4)
#घोषणा REG_ADI_CHN_EN1			0x20c

/* Bits definitions क्रम रेजिस्टर REG_ADI_GSSI_CFG0 */
#घोषणा BIT_CLK_ALL_ON			BIT(30)

/* Bits definitions क्रम रेजिस्टर REG_ADI_RD_DATA */
#घोषणा BIT_RD_CMD_BUSY			BIT(31)
#घोषणा RD_ADDR_SHIFT			16
#घोषणा RD_VALUE_MASK			GENMASK(15, 0)
#घोषणा RD_ADDR_MASK			GENMASK(30, 16)

/* Bits definitions क्रम रेजिस्टर REG_ADI_ARM_FIFO_STS */
#घोषणा BIT_FIFO_FULL			BIT(11)
#घोषणा BIT_FIFO_EMPTY			BIT(10)

/*
 * ADI slave devices include RTC, ADC, regulator, अक्षरger, thermal and so on.
 * The slave devices address offset is always 0x8000 and size is 4K.
 */
#घोषणा ADI_SLAVE_ADDR_SIZE		SZ_4K
#घोषणा ADI_SLAVE_OFFSET		0x8000

/* Timeout (ms) क्रम the trylock of hardware spinlocks */
#घोषणा ADI_HWSPINLOCK_TIMEOUT		5000
/*
 * ADI controller has 50 channels including 2 software channels
 * and 48 hardware channels.
 */
#घोषणा ADI_HW_CHNS			50

#घोषणा ADI_FIFO_DRAIN_TIMEOUT		1000
#घोषणा ADI_READ_TIMEOUT		2000
#घोषणा REG_ADDR_LOW_MASK		GENMASK(11, 0)

/* Registers definitions क्रम PMIC watchकरोg controller */
#घोषणा REG_WDG_LOAD_LOW		0x80
#घोषणा REG_WDG_LOAD_HIGH		0x84
#घोषणा REG_WDG_CTRL			0x88
#घोषणा REG_WDG_LOCK			0xa0

/* Bits definitions क्रम रेजिस्टर REG_WDG_CTRL */
#घोषणा BIT_WDG_RUN			BIT(1)
#घोषणा BIT_WDG_NEW			BIT(2)
#घोषणा BIT_WDG_RST			BIT(3)

/* Registers definitions क्रम PMIC */
#घोषणा PMIC_RST_STATUS			0xee8
#घोषणा PMIC_MODULE_EN			0xc08
#घोषणा PMIC_CLK_EN			0xc18
#घोषणा BIT_WDG_EN			BIT(2)

/* Definition of PMIC reset status रेजिस्टर */
#घोषणा HWRST_STATUS_SECURITY		0x02
#घोषणा HWRST_STATUS_RECOVERY		0x20
#घोषणा HWRST_STATUS_NORMAL		0x40
#घोषणा HWRST_STATUS_ALARM		0x50
#घोषणा HWRST_STATUS_SLEEP		0x60
#घोषणा HWRST_STATUS_FASTBOOT		0x30
#घोषणा HWRST_STATUS_SPECIAL		0x70
#घोषणा HWRST_STATUS_PANIC		0x80
#घोषणा HWRST_STATUS_CFTREBOOT		0x90
#घोषणा HWRST_STATUS_AUTODLOADER	0xa0
#घोषणा HWRST_STATUS_IQMODE		0xb0
#घोषणा HWRST_STATUS_SPRDISK		0xc0
#घोषणा HWRST_STATUS_FACTORYTEST	0xe0
#घोषणा HWRST_STATUS_WATCHDOG		0xf0

/* Use शेष समयout 50 ms that converts to watchकरोg values */
#घोषणा WDG_LOAD_VAL			((50 * 1000) / 32768)
#घोषणा WDG_LOAD_MASK			GENMASK(15, 0)
#घोषणा WDG_UNLOCK_KEY			0xe551

काष्ठा sprd_adi अणु
	काष्ठा spi_controller	*ctlr;
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा hwspinlock	*hwlock;
	अचिन्हित दीर्घ		slave_vbase;
	अचिन्हित दीर्घ		slave_pbase;
	काष्ठा notअगरier_block	restart_handler;
पूर्ण;

अटल पूर्णांक sprd_adi_check_paddr(काष्ठा sprd_adi *sadi, u32 paddr)
अणु
	अगर (paddr < sadi->slave_pbase || paddr >
	    (sadi->slave_pbase + ADI_SLAVE_ADDR_SIZE)) अणु
		dev_err(sadi->dev,
			"slave physical address is incorrect, addr = 0x%x\n",
			paddr);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ sprd_adi_to_vaddr(काष्ठा sprd_adi *sadi, u32 paddr)
अणु
	वापस (paddr - sadi->slave_pbase + sadi->slave_vbase);
पूर्ण

अटल पूर्णांक sprd_adi_drain_fअगरo(काष्ठा sprd_adi *sadi)
अणु
	u32 समयout = ADI_FIFO_DRAIN_TIMEOUT;
	u32 sts;

	करो अणु
		sts = पढ़ोl_relaxed(sadi->base + REG_ADI_ARM_FIFO_STS);
		अगर (sts & BIT_FIFO_EMPTY)
			अवरोध;

		cpu_relax();
	पूर्ण जबतक (--समयout);

	अगर (समयout == 0) अणु
		dev_err(sadi->dev, "drain write fifo timeout\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_adi_fअगरo_is_full(काष्ठा sprd_adi *sadi)
अणु
	वापस पढ़ोl_relaxed(sadi->base + REG_ADI_ARM_FIFO_STS) & BIT_FIFO_FULL;
पूर्ण

अटल पूर्णांक sprd_adi_पढ़ो(काष्ठा sprd_adi *sadi, u32 reg_paddr, u32 *पढ़ो_val)
अणु
	पूर्णांक पढ़ो_समयout = ADI_READ_TIMEOUT;
	अचिन्हित दीर्घ flags;
	u32 val, rd_addr;
	पूर्णांक ret = 0;

	अगर (sadi->hwlock) अणु
		ret = hwspin_lock_समयout_irqsave(sadi->hwlock,
						  ADI_HWSPINLOCK_TIMEOUT,
						  &flags);
		अगर (ret) अणु
			dev_err(sadi->dev, "get the hw lock failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Set the physical रेजिस्टर address need to पढ़ो पूर्णांकo RD_CMD रेजिस्टर,
	 * then ADI controller will start to transfer स्वतःmatically.
	 */
	ग_लिखोl_relaxed(reg_paddr, sadi->base + REG_ADI_RD_CMD);

	/*
	 * Wait पढ़ो operation complete, the BIT_RD_CMD_BUSY will be set
	 * simultaneously when writing पढ़ो command to रेजिस्टर, and the
	 * BIT_RD_CMD_BUSY will be cleared after the पढ़ो operation is
	 * completed.
	 */
	करो अणु
		val = पढ़ोl_relaxed(sadi->base + REG_ADI_RD_DATA);
		अगर (!(val & BIT_RD_CMD_BUSY))
			अवरोध;

		cpu_relax();
	पूर्ण जबतक (--पढ़ो_समयout);

	अगर (पढ़ो_समयout == 0) अणु
		dev_err(sadi->dev, "ADI read timeout\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * The वापस value includes data and पढ़ो रेजिस्टर address, from bit 0
	 * to bit 15 are data, and from bit 16 to bit 30 are पढ़ो रेजिस्टर
	 * address. Then we can check the वापसed रेजिस्टर address to validate
	 * data.
	 */
	rd_addr = (val & RD_ADDR_MASK) >> RD_ADDR_SHIFT;

	अगर (rd_addr != (reg_paddr & REG_ADDR_LOW_MASK)) अणु
		dev_err(sadi->dev, "read error, reg addr = 0x%x, val = 0x%x\n",
			reg_paddr, val);
		ret = -EIO;
		जाओ out;
	पूर्ण

	*पढ़ो_val = val & RD_VALUE_MASK;

out:
	अगर (sadi->hwlock)
		hwspin_unlock_irqrestore(sadi->hwlock, &flags);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_adi_ग_लिखो(काष्ठा sprd_adi *sadi, u32 reg_paddr, u32 val)
अणु
	अचिन्हित दीर्घ reg = sprd_adi_to_vaddr(sadi, reg_paddr);
	u32 समयout = ADI_FIFO_DRAIN_TIMEOUT;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (sadi->hwlock) अणु
		ret = hwspin_lock_समयout_irqsave(sadi->hwlock,
						  ADI_HWSPINLOCK_TIMEOUT,
						  &flags);
		अगर (ret) अणु
			dev_err(sadi->dev, "get the hw lock failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = sprd_adi_drain_fअगरo(sadi);
	अगर (ret < 0)
		जाओ out;

	/*
	 * we should रुको क्रम ग_लिखो fअगरo is empty beक्रमe writing data to PMIC
	 * रेजिस्टरs.
	 */
	करो अणु
		अगर (!sprd_adi_fअगरo_is_full(sadi)) अणु
			ग_लिखोl_relaxed(val, (व्योम __iomem *)reg);
			अवरोध;
		पूर्ण

		cpu_relax();
	पूर्ण जबतक (--समयout);

	अगर (समयout == 0) अणु
		dev_err(sadi->dev, "write fifo is full\n");
		ret = -EBUSY;
	पूर्ण

out:
	अगर (sadi->hwlock)
		hwspin_unlock_irqrestore(sadi->hwlock, &flags);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_adi_transfer_one(काष्ठा spi_controller *ctlr,
				 काष्ठा spi_device *spi_dev,
				 काष्ठा spi_transfer *t)
अणु
	काष्ठा sprd_adi *sadi = spi_controller_get_devdata(ctlr);
	u32 phy_reg, val;
	पूर्णांक ret;

	अगर (t->rx_buf) अणु
		phy_reg = *(u32 *)t->rx_buf + sadi->slave_pbase;

		ret = sprd_adi_check_paddr(sadi, phy_reg);
		अगर (ret)
			वापस ret;

		ret = sprd_adi_पढ़ो(sadi, phy_reg, &val);
		अगर (ret)
			वापस ret;

		*(u32 *)t->rx_buf = val;
	पूर्ण अन्यथा अगर (t->tx_buf) अणु
		u32 *p = (u32 *)t->tx_buf;

		/*
		 * Get the physical रेजिस्टर address need to ग_लिखो and convert
		 * the physical address to भव address. Since we need
		 * भव रेजिस्टर address to ग_लिखो.
		 */
		phy_reg = *p++ + sadi->slave_pbase;
		ret = sprd_adi_check_paddr(sadi, phy_reg);
		अगर (ret)
			वापस ret;

		val = *p;
		ret = sprd_adi_ग_लिखो(sadi, phy_reg, val);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		dev_err(sadi->dev, "no buffer for transfer\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sprd_adi_set_wdt_rst_mode(काष्ठा sprd_adi *sadi)
अणु
#अगर IS_ENABLED(CONFIG_SPRD_WATCHDOG)
	u32 val;

	/* Set शेष watchकरोg reboot mode */
	sprd_adi_पढ़ो(sadi, sadi->slave_pbase + PMIC_RST_STATUS, &val);
	val |= HWRST_STATUS_WATCHDOG;
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + PMIC_RST_STATUS, val);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक sprd_adi_restart_handler(काष्ठा notअगरier_block *this,
				    अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा sprd_adi *sadi = container_of(this, काष्ठा sprd_adi,
					     restart_handler);
	u32 val, reboot_mode = 0;

	अगर (!cmd)
		reboot_mode = HWRST_STATUS_NORMAL;
	अन्यथा अगर (!म_भेदन(cmd, "recovery", 8))
		reboot_mode = HWRST_STATUS_RECOVERY;
	अन्यथा अगर (!म_भेदन(cmd, "alarm", 5))
		reboot_mode = HWRST_STATUS_ALARM;
	अन्यथा अगर (!म_भेदन(cmd, "fastsleep", 9))
		reboot_mode = HWRST_STATUS_SLEEP;
	अन्यथा अगर (!म_भेदन(cmd, "bootloader", 10))
		reboot_mode = HWRST_STATUS_FASTBOOT;
	अन्यथा अगर (!म_भेदन(cmd, "panic", 5))
		reboot_mode = HWRST_STATUS_PANIC;
	अन्यथा अगर (!म_भेदन(cmd, "special", 7))
		reboot_mode = HWRST_STATUS_SPECIAL;
	अन्यथा अगर (!म_भेदन(cmd, "cftreboot", 9))
		reboot_mode = HWRST_STATUS_CFTREBOOT;
	अन्यथा अगर (!म_भेदन(cmd, "autodloader", 11))
		reboot_mode = HWRST_STATUS_AUTODLOADER;
	अन्यथा अगर (!म_भेदन(cmd, "iqmode", 6))
		reboot_mode = HWRST_STATUS_IQMODE;
	अन्यथा अगर (!म_भेदन(cmd, "sprdisk", 7))
		reboot_mode = HWRST_STATUS_SPRDISK;
	अन्यथा अगर (!म_भेदन(cmd, "tospanic", 8))
		reboot_mode = HWRST_STATUS_SECURITY;
	अन्यथा अगर (!म_भेदन(cmd, "factorytest", 11))
		reboot_mode = HWRST_STATUS_FACTORYTEST;
	अन्यथा
		reboot_mode = HWRST_STATUS_NORMAL;

	/* Record the reboot mode */
	sprd_adi_पढ़ो(sadi, sadi->slave_pbase + PMIC_RST_STATUS, &val);
	val &= ~HWRST_STATUS_WATCHDOG;
	val |= reboot_mode;
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + PMIC_RST_STATUS, val);

	/* Enable the पूर्णांकerface घड़ी of the watchकरोg */
	sprd_adi_पढ़ो(sadi, sadi->slave_pbase + PMIC_MODULE_EN, &val);
	val |= BIT_WDG_EN;
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + PMIC_MODULE_EN, val);

	/* Enable the work घड़ी of the watchकरोg */
	sprd_adi_पढ़ो(sadi, sadi->slave_pbase + PMIC_CLK_EN, &val);
	val |= BIT_WDG_EN;
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + PMIC_CLK_EN, val);

	/* Unlock the watchकरोg */
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + REG_WDG_LOCK, WDG_UNLOCK_KEY);

	sprd_adi_पढ़ो(sadi, sadi->slave_pbase + REG_WDG_CTRL, &val);
	val |= BIT_WDG_NEW;
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + REG_WDG_CTRL, val);

	/* Load the watchकरोg समयout value, 50ms is always enough. */
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + REG_WDG_LOAD_HIGH, 0);
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + REG_WDG_LOAD_LOW,
		       WDG_LOAD_VAL & WDG_LOAD_MASK);

	/* Start the watchकरोg to reset प्रणाली */
	sprd_adi_पढ़ो(sadi, sadi->slave_pbase + REG_WDG_CTRL, &val);
	val |= BIT_WDG_RUN | BIT_WDG_RST;
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + REG_WDG_CTRL, val);

	/* Lock the watchकरोg */
	sprd_adi_ग_लिखो(sadi, sadi->slave_pbase + REG_WDG_LOCK, ~WDG_UNLOCK_KEY);

	mdelay(1000);

	dev_emerg(sadi->dev, "Unable to restart system\n");
	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम sprd_adi_hw_init(काष्ठा sprd_adi *sadi)
अणु
	काष्ठा device_node *np = sadi->dev->of_node;
	पूर्णांक i, size, chn_cnt;
	स्थिर __be32 *list;
	u32 पंचांगp;

	/* Set all channels as शेष priority */
	ग_लिखोl_relaxed(0, sadi->base + REG_ADI_CHN_PRIL);
	ग_लिखोl_relaxed(0, sadi->base + REG_ADI_CHN_PRIH);

	/* Set घड़ी स्वतः gate mode */
	पंचांगp = पढ़ोl_relaxed(sadi->base + REG_ADI_GSSI_CFG0);
	पंचांगp &= ~BIT_CLK_ALL_ON;
	ग_लिखोl_relaxed(पंचांगp, sadi->base + REG_ADI_GSSI_CFG0);

	/* Set hardware channels setting */
	list = of_get_property(np, "sprd,hw-channels", &size);
	अगर (!list || !size) अणु
		dev_info(sadi->dev, "no hw channels setting in node\n");
		वापस;
	पूर्ण

	chn_cnt = size / 8;
	क्रम (i = 0; i < chn_cnt; i++) अणु
		u32 value;
		u32 chn_id = be32_to_cpu(*list++);
		u32 chn_config = be32_to_cpu(*list++);

		/* Channel 0 and 1 are software channels */
		अगर (chn_id < 2)
			जारी;

		ग_लिखोl_relaxed(chn_config, sadi->base +
			       REG_ADI_CHN_ADDR(chn_id));

		अगर (chn_id < 32) अणु
			value = पढ़ोl_relaxed(sadi->base + REG_ADI_CHN_EN);
			value |= BIT(chn_id);
			ग_लिखोl_relaxed(value, sadi->base + REG_ADI_CHN_EN);
		पूर्ण अन्यथा अगर (chn_id < ADI_HW_CHNS) अणु
			value = पढ़ोl_relaxed(sadi->base + REG_ADI_CHN_EN1);
			value |= BIT(chn_id - 32);
			ग_लिखोl_relaxed(value, sadi->base + REG_ADI_CHN_EN1);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_adi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा spi_controller *ctlr;
	काष्ठा sprd_adi *sadi;
	काष्ठा resource *res;
	u32 num_chipselect;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(&pdev->dev, "can not find the adi bus node\n");
		वापस -ENODEV;
	पूर्ण

	pdev->id = of_alias_get_id(np, "spi");
	num_chipselect = of_get_child_count(np);

	ctlr = spi_alloc_master(&pdev->dev, माप(काष्ठा sprd_adi));
	अगर (!ctlr)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, ctlr);
	sadi = spi_controller_get_devdata(ctlr);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sadi->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(sadi->base)) अणु
		ret = PTR_ERR(sadi->base);
		जाओ put_ctlr;
	पूर्ण

	sadi->slave_vbase = (अचिन्हित दीर्घ)sadi->base + ADI_SLAVE_OFFSET;
	sadi->slave_pbase = res->start + ADI_SLAVE_OFFSET;
	sadi->ctlr = ctlr;
	sadi->dev = &pdev->dev;
	ret = of_hwspin_lock_get_id(np, 0);
	अगर (ret > 0 || (IS_ENABLED(CONFIG_HWSPINLOCK) && ret == 0)) अणु
		sadi->hwlock =
			devm_hwspin_lock_request_specअगरic(&pdev->dev, ret);
		अगर (!sadi->hwlock) अणु
			ret = -ENXIO;
			जाओ put_ctlr;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ret) अणु
		हाल -ENOENT:
			dev_info(&pdev->dev, "no hardware spinlock supplied\n");
			अवरोध;
		शेष:
			dev_err_probe(&pdev->dev, ret, "failed to find hwlock id\n");
			जाओ put_ctlr;
		पूर्ण
	पूर्ण

	sprd_adi_hw_init(sadi);
	sprd_adi_set_wdt_rst_mode(sadi);

	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->bus_num = pdev->id;
	ctlr->num_chipselect = num_chipselect;
	ctlr->flags = SPI_MASTER_HALF_DUPLEX;
	ctlr->bits_per_word_mask = 0;
	ctlr->transfer_one = sprd_adi_transfer_one;

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register SPI controller\n");
		जाओ put_ctlr;
	पूर्ण

	sadi->restart_handler.notअगरier_call = sprd_adi_restart_handler;
	sadi->restart_handler.priority = 128;
	ret = रेजिस्टर_restart_handler(&sadi->restart_handler);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can not register restart handler\n");
		जाओ put_ctlr;
	पूर्ण

	वापस 0;

put_ctlr:
	spi_controller_put(ctlr);
	वापस ret;
पूर्ण

अटल पूर्णांक sprd_adi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(&pdev->dev);
	काष्ठा sprd_adi *sadi = spi_controller_get_devdata(ctlr);

	unरेजिस्टर_restart_handler(&sadi->restart_handler);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_adi_of_match[] = अणु
	अणु
		.compatible = "sprd,sc9860-adi",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_adi_of_match);

अटल काष्ठा platक्रमm_driver sprd_adi_driver = अणु
	.driver = अणु
		.name = "sprd-adi",
		.of_match_table = sprd_adi_of_match,
	पूर्ण,
	.probe = sprd_adi_probe,
	.हटाओ = sprd_adi_हटाओ,
पूर्ण;
module_platक्रमm_driver(sprd_adi_driver);

MODULE_DESCRIPTION("Spreadtrum ADI Controller Driver");
MODULE_AUTHOR("Baolin Wang <Baolin.Wang@spreadtrum.com>");
MODULE_LICENSE("GPL v2");
