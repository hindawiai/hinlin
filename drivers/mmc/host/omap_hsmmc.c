<शैली गुरु>
/*
 * drivers/mmc/host/omap_hsmmc.c
 *
 * Driver क्रम OMAP2430/3430 MMC controller.
 *
 * Copyright (C) 2007 Texas Instruments.
 *
 * Authors:
 *	Syed Mohammed Khasim	<x0khasim@ti.com>
 *	Madhusudhan		<madhu.cr@ti.com>
 *	Mohit Jalori		<mjalori@ti.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sizes.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/समयr.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/platक्रमm_data/hsmmc-omap.h>

/* OMAP HSMMC Host Controller Registers */
#घोषणा OMAP_HSMMC_SYSSTATUS	0x0014
#घोषणा OMAP_HSMMC_CON		0x002C
#घोषणा OMAP_HSMMC_SDMASA	0x0100
#घोषणा OMAP_HSMMC_BLK		0x0104
#घोषणा OMAP_HSMMC_ARG		0x0108
#घोषणा OMAP_HSMMC_CMD		0x010C
#घोषणा OMAP_HSMMC_RSP10	0x0110
#घोषणा OMAP_HSMMC_RSP32	0x0114
#घोषणा OMAP_HSMMC_RSP54	0x0118
#घोषणा OMAP_HSMMC_RSP76	0x011C
#घोषणा OMAP_HSMMC_DATA		0x0120
#घोषणा OMAP_HSMMC_PSTATE	0x0124
#घोषणा OMAP_HSMMC_HCTL		0x0128
#घोषणा OMAP_HSMMC_SYSCTL	0x012C
#घोषणा OMAP_HSMMC_STAT		0x0130
#घोषणा OMAP_HSMMC_IE		0x0134
#घोषणा OMAP_HSMMC_ISE		0x0138
#घोषणा OMAP_HSMMC_AC12		0x013C
#घोषणा OMAP_HSMMC_CAPA		0x0140

#घोषणा VS18			(1 << 26)
#घोषणा VS30			(1 << 25)
#घोषणा HSS			(1 << 21)
#घोषणा SDVS18			(0x5 << 9)
#घोषणा SDVS30			(0x6 << 9)
#घोषणा SDVS33			(0x7 << 9)
#घोषणा SDVS_MASK		0x00000E00
#घोषणा SDVSCLR			0xFFFFF1FF
#घोषणा SDVSDET			0x00000400
#घोषणा AUTOIDLE		0x1
#घोषणा SDBP			(1 << 8)
#घोषणा DTO			0xe
#घोषणा ICE			0x1
#घोषणा ICS			0x2
#घोषणा CEN			(1 << 2)
#घोषणा CLKD_MAX		0x3FF		/* max घड़ी भागisor: 1023 */
#घोषणा CLKD_MASK		0x0000FFC0
#घोषणा CLKD_SHIFT		6
#घोषणा DTO_MASK		0x000F0000
#घोषणा DTO_SHIFT		16
#घोषणा INIT_STREAM		(1 << 1)
#घोषणा ACEN_ACMD23		(2 << 2)
#घोषणा DP_SELECT		(1 << 21)
#घोषणा Dसूची			(1 << 4)
#घोषणा DMAE			0x1
#घोषणा MSBS			(1 << 5)
#घोषणा BCE			(1 << 1)
#घोषणा FOUR_BIT		(1 << 1)
#घोषणा HSPE			(1 << 2)
#घोषणा IWE			(1 << 24)
#घोषणा DDR			(1 << 19)
#घोषणा CLKEXTFREE		(1 << 16)
#घोषणा CTPL			(1 << 11)
#घोषणा DW8			(1 << 5)
#घोषणा OD			0x1
#घोषणा STAT_CLEAR		0xFFFFFFFF
#घोषणा INIT_STREAM_CMD		0x00000000
#घोषणा DUAL_VOLT_OCR_BIT	7
#घोषणा SRC			(1 << 25)
#घोषणा SRD			(1 << 26)
#घोषणा SOFTRESET		(1 << 1)

/* PSTATE */
#घोषणा DLEV_DAT(x)		(1 << (20 + (x)))

/* Interrupt masks क्रम IE and ISE रेजिस्टर */
#घोषणा CC_EN			(1 << 0)
#घोषणा TC_EN			(1 << 1)
#घोषणा BWR_EN			(1 << 4)
#घोषणा BRR_EN			(1 << 5)
#घोषणा CIRQ_EN			(1 << 8)
#घोषणा ERR_EN			(1 << 15)
#घोषणा CTO_EN			(1 << 16)
#घोषणा CCRC_EN			(1 << 17)
#घोषणा CEB_EN			(1 << 18)
#घोषणा CIE_EN			(1 << 19)
#घोषणा DTO_EN			(1 << 20)
#घोषणा DCRC_EN			(1 << 21)
#घोषणा DEB_EN			(1 << 22)
#घोषणा ACE_EN			(1 << 24)
#घोषणा CERR_EN			(1 << 28)
#घोषणा BADA_EN			(1 << 29)

#घोषणा INT_EN_MASK (BADA_EN | CERR_EN | ACE_EN | DEB_EN | DCRC_EN |\
		DTO_EN | CIE_EN | CEB_EN | CCRC_EN | CTO_EN | \
		BRR_EN | BWR_EN | TC_EN | CC_EN)

#घोषणा CNI	(1 << 7)
#घोषणा ACIE	(1 << 4)
#घोषणा ACEB	(1 << 3)
#घोषणा ACCE	(1 << 2)
#घोषणा ACTO	(1 << 1)
#घोषणा ACNE	(1 << 0)

#घोषणा MMC_AUTOSUSPEND_DELAY	100
#घोषणा MMC_TIMEOUT_MS		20		/* 20 mSec */
#घोषणा MMC_TIMEOUT_US		20000		/* 20000 micro Sec */
#घोषणा OMAP_MMC_MIN_CLOCK	400000
#घोषणा OMAP_MMC_MAX_CLOCK	52000000
#घोषणा DRIVER_NAME		"omap_hsmmc"

/*
 * One controller can have multiple slots, like on some omap boards using
 * omap.c controller driver. Luckily this is not currently करोne on any known
 * omap_hsmmc.c device.
 */
#घोषणा mmc_pdata(host)		host->pdata

/*
 * MMC Host controller पढ़ो/ग_लिखो API's
 */
#घोषणा OMAP_HSMMC_READ(base, reg)	\
	__raw_पढ़ोl((base) + OMAP_HSMMC_##reg)

#घोषणा OMAP_HSMMC_WRITE(base, reg, val) \
	__raw_ग_लिखोl((val), (base) + OMAP_HSMMC_##reg)

काष्ठा omap_hsmmc_next अणु
	अचिन्हित पूर्णांक	dma_len;
	s32		cookie;
पूर्ण;

काष्ठा omap_hsmmc_host अणु
	काष्ठा	device		*dev;
	काष्ठा	mmc_host	*mmc;
	काष्ठा	mmc_request	*mrq;
	काष्ठा	mmc_command	*cmd;
	काष्ठा	mmc_data	*data;
	काष्ठा	clk		*fclk;
	काष्ठा	clk		*dbclk;
	काष्ठा	regulator	*pbias;
	bool			pbias_enabled;
	व्योम	__iomem		*base;
	bool			vqmmc_enabled;
	resource_माप_प्रकार		mapbase;
	spinlock_t		irq_lock; /* Prevent races with irq handler */
	अचिन्हित पूर्णांक		dma_len;
	अचिन्हित पूर्णांक		dma_sg_idx;
	अचिन्हित अक्षर		bus_mode;
	अचिन्हित अक्षर		घातer_mode;
	पूर्णांक			suspended;
	u32			con;
	u32			hctl;
	u32			sysctl;
	u32			capa;
	पूर्णांक			irq;
	पूर्णांक			wake_irq;
	पूर्णांक			use_dma, dma_ch;
	काष्ठा dma_chan		*tx_chan;
	काष्ठा dma_chan		*rx_chan;
	पूर्णांक			response_busy;
	पूर्णांक			context_loss;
	पूर्णांक			reqs_blocked;
	पूर्णांक			req_in_progress;
	अचिन्हित दीर्घ		clk_rate;
	अचिन्हित पूर्णांक		flags;
#घोषणा AUTO_CMD23		(1 << 0)        /* Auto CMD23 support */
#घोषणा HSMMC_SDIO_IRQ_ENABLED	(1 << 1)        /* SDIO irq enabled */
	काष्ठा omap_hsmmc_next	next_data;
	काष्ठा	omap_hsmmc_platक्रमm_data	*pdata;
पूर्ण;

काष्ठा omap_mmc_of_data अणु
	u32 reg_offset;
	u8 controller_flags;
पूर्ण;

अटल व्योम omap_hsmmc_start_dma_transfer(काष्ठा omap_hsmmc_host *host);

अटल पूर्णांक omap_hsmmc_enable_supply(काष्ठा mmc_host *mmc)
अणु
	पूर्णांक ret;
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_ios *ios = &mmc->ios;

	अगर (!IS_ERR(mmc->supply.vmmc)) अणु
		ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Enable पूर्णांकerface voltage rail, अगर needed */
	अगर (!IS_ERR(mmc->supply.vqmmc) && !host->vqmmc_enabled) अणु
		ret = regulator_enable(mmc->supply.vqmmc);
		अगर (ret) अणु
			dev_err(mmc_dev(mmc), "vmmc_aux reg enable failed\n");
			जाओ err_vqmmc;
		पूर्ण
		host->vqmmc_enabled = true;
	पूर्ण

	वापस 0;

err_vqmmc:
	अगर (!IS_ERR(mmc->supply.vmmc))
		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_hsmmc_disable_supply(काष्ठा mmc_host *mmc)
अणु
	पूर्णांक ret;
	पूर्णांक status;
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);

	अगर (!IS_ERR(mmc->supply.vqmmc) && host->vqmmc_enabled) अणु
		ret = regulator_disable(mmc->supply.vqmmc);
		अगर (ret) अणु
			dev_err(mmc_dev(mmc), "vmmc_aux reg disable failed\n");
			वापस ret;
		पूर्ण
		host->vqmmc_enabled = false;
	पूर्ण

	अगर (!IS_ERR(mmc->supply.vmmc)) अणु
		ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		अगर (ret)
			जाओ err_set_ocr;
	पूर्ण

	वापस 0;

err_set_ocr:
	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		status = regulator_enable(mmc->supply.vqmmc);
		अगर (status)
			dev_err(mmc_dev(mmc), "vmmc_aux re-enable failed\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक omap_hsmmc_set_pbias(काष्ठा omap_hsmmc_host *host, bool घातer_on)
अणु
	पूर्णांक ret;

	अगर (IS_ERR(host->pbias))
		वापस 0;

	अगर (घातer_on) अणु
		अगर (!host->pbias_enabled) अणु
			ret = regulator_enable(host->pbias);
			अगर (ret) अणु
				dev_err(host->dev, "pbias reg enable fail\n");
				वापस ret;
			पूर्ण
			host->pbias_enabled = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (host->pbias_enabled) अणु
			ret = regulator_disable(host->pbias);
			अगर (ret) अणु
				dev_err(host->dev, "pbias reg disable fail\n");
				वापस ret;
			पूर्ण
			host->pbias_enabled = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_hsmmc_set_घातer(काष्ठा omap_hsmmc_host *host, पूर्णांक घातer_on)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret = 0;

	/*
	 * If we करोn't see a Vcc regulator, assume it's a fixed
	 * voltage always-on regulator.
	 */
	अगर (IS_ERR(mmc->supply.vmmc))
		वापस 0;

	ret = omap_hsmmc_set_pbias(host, false);
	अगर (ret)
		वापस ret;

	/*
	 * Assume Vcc regulator is used only to घातer the card ... OMAP
	 * VDDS is used to घातer the pins, optionally with a transceiver to
	 * support cards using voltages other than VDDS (1.8V nominal).  When a
	 * transceiver is used, DAT3..7 are muxed as transceiver control pins.
	 *
	 * In some हालs this regulator won't support enable/disable;
	 * e.g. it's a fixed rail क्रम a WLAN chip.
	 *
	 * In other हालs vcc_aux चयनes पूर्णांकerface घातer.  Example, क्रम
	 * eMMC cards it represents VccQ.  Someबार transceivers or SDIO
	 * chips/cards need an पूर्णांकerface voltage rail too.
	 */
	अगर (घातer_on) अणु
		ret = omap_hsmmc_enable_supply(mmc);
		अगर (ret)
			वापस ret;

		ret = omap_hsmmc_set_pbias(host, true);
		अगर (ret)
			जाओ err_set_voltage;
	पूर्ण अन्यथा अणु
		ret = omap_hsmmc_disable_supply(mmc);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;

err_set_voltage:
	omap_hsmmc_disable_supply(mmc);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_hsmmc_disable_boot_regulator(काष्ठा regulator *reg)
अणु
	पूर्णांक ret;

	अगर (IS_ERR(reg))
		वापस 0;

	अगर (regulator_is_enabled(reg)) अणु
		ret = regulator_enable(reg);
		अगर (ret)
			वापस ret;

		ret = regulator_disable(reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_hsmmc_disable_boot_regulators(काष्ठा omap_hsmmc_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret;

	/*
	 * disable regulators enabled during boot and get the usecount
	 * right so that regulators can be enabled/disabled by checking
	 * the वापस value of regulator_is_enabled
	 */
	ret = omap_hsmmc_disable_boot_regulator(mmc->supply.vmmc);
	अगर (ret) अणु
		dev_err(host->dev, "fail to disable boot enabled vmmc reg\n");
		वापस ret;
	पूर्ण

	ret = omap_hsmmc_disable_boot_regulator(mmc->supply.vqmmc);
	अगर (ret) अणु
		dev_err(host->dev,
			"fail to disable boot enabled vmmc_aux reg\n");
		वापस ret;
	पूर्ण

	ret = omap_hsmmc_disable_boot_regulator(host->pbias);
	अगर (ret) अणु
		dev_err(host->dev,
			"failed to disable boot enabled pbias reg\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_hsmmc_reg_get(काष्ठा omap_hsmmc_host *host)
अणु
	पूर्णांक ret;
	काष्ठा mmc_host *mmc = host->mmc;


	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		वापस ret;

	/* Allow an aux regulator */
	अगर (IS_ERR(mmc->supply.vqmmc)) अणु
		mmc->supply.vqmmc = devm_regulator_get_optional(host->dev,
								"vmmc_aux");
		अगर (IS_ERR(mmc->supply.vqmmc)) अणु
			ret = PTR_ERR(mmc->supply.vqmmc);
			अगर ((ret != -ENODEV) && host->dev->of_node)
				वापस ret;
			dev_dbg(host->dev, "unable to get vmmc_aux regulator %ld\n",
				PTR_ERR(mmc->supply.vqmmc));
		पूर्ण
	पूर्ण

	host->pbias = devm_regulator_get_optional(host->dev, "pbias");
	अगर (IS_ERR(host->pbias)) अणु
		ret = PTR_ERR(host->pbias);
		अगर ((ret != -ENODEV) && host->dev->of_node) अणु
			dev_err(host->dev,
			"SD card detect fail? enable CONFIG_REGULATOR_PBIAS\n");
			वापस ret;
		पूर्ण
		dev_dbg(host->dev, "unable to get pbias regulator %ld\n",
			PTR_ERR(host->pbias));
	पूर्ण

	/* For eMMC करो not घातer off when not in sleep state */
	अगर (mmc_pdata(host)->no_regulator_off_init)
		वापस 0;

	ret = omap_hsmmc_disable_boot_regulators(host);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Start घड़ी to the card
 */
अटल व्योम omap_hsmmc_start_घड़ी(काष्ठा omap_hsmmc_host *host)
अणु
	OMAP_HSMMC_WRITE(host->base, SYSCTL,
		OMAP_HSMMC_READ(host->base, SYSCTL) | CEN);
पूर्ण

/*
 * Stop घड़ी to the card
 */
अटल व्योम omap_hsmmc_stop_घड़ी(काष्ठा omap_hsmmc_host *host)
अणु
	OMAP_HSMMC_WRITE(host->base, SYSCTL,
		OMAP_HSMMC_READ(host->base, SYSCTL) & ~CEN);
	अगर ((OMAP_HSMMC_READ(host->base, SYSCTL) & CEN) != 0x0)
		dev_dbg(mmc_dev(host->mmc), "MMC Clock is not stopped\n");
पूर्ण

अटल व्योम omap_hsmmc_enable_irq(काष्ठा omap_hsmmc_host *host,
				  काष्ठा mmc_command *cmd)
अणु
	u32 irq_mask = INT_EN_MASK;
	अचिन्हित दीर्घ flags;

	अगर (host->use_dma)
		irq_mask &= ~(BRR_EN | BWR_EN);

	/* Disable समयout क्रम erases */
	अगर (cmd->opcode == MMC_ERASE)
		irq_mask &= ~DTO_EN;

	spin_lock_irqsave(&host->irq_lock, flags);
	OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
	OMAP_HSMMC_WRITE(host->base, ISE, irq_mask);

	/* latch pending CIRQ, but करोn't संकेत MMC core */
	अगर (host->flags & HSMMC_SDIO_IRQ_ENABLED)
		irq_mask |= CIRQ_EN;
	OMAP_HSMMC_WRITE(host->base, IE, irq_mask);
	spin_unlock_irqrestore(&host->irq_lock, flags);
पूर्ण

अटल व्योम omap_hsmmc_disable_irq(काष्ठा omap_hsmmc_host *host)
अणु
	u32 irq_mask = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->irq_lock, flags);
	/* no transfer running but need to keep cirq अगर enabled */
	अगर (host->flags & HSMMC_SDIO_IRQ_ENABLED)
		irq_mask |= CIRQ_EN;
	OMAP_HSMMC_WRITE(host->base, ISE, irq_mask);
	OMAP_HSMMC_WRITE(host->base, IE, irq_mask);
	OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
	spin_unlock_irqrestore(&host->irq_lock, flags);
पूर्ण

/* Calculate भागisor क्रम the given घड़ी frequency */
अटल u16 calc_भागisor(काष्ठा omap_hsmmc_host *host, काष्ठा mmc_ios *ios)
अणु
	u16 dsor = 0;

	अगर (ios->घड़ी) अणु
		dsor = DIV_ROUND_UP(clk_get_rate(host->fclk), ios->घड़ी);
		अगर (dsor > CLKD_MAX)
			dsor = CLKD_MAX;
	पूर्ण

	वापस dsor;
पूर्ण

अटल व्योम omap_hsmmc_set_घड़ी(काष्ठा omap_hsmmc_host *host)
अणु
	काष्ठा mmc_ios *ios = &host->mmc->ios;
	अचिन्हित दीर्घ regval;
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ clkभाग;

	dev_vdbg(mmc_dev(host->mmc), "Set clock to %uHz\n", ios->घड़ी);

	omap_hsmmc_stop_घड़ी(host);

	regval = OMAP_HSMMC_READ(host->base, SYSCTL);
	regval = regval & ~(CLKD_MASK | DTO_MASK);
	clkभाग = calc_भागisor(host, ios);
	regval = regval | (clkभाग << 6) | (DTO << 16);
	OMAP_HSMMC_WRITE(host->base, SYSCTL, regval);
	OMAP_HSMMC_WRITE(host->base, SYSCTL,
		OMAP_HSMMC_READ(host->base, SYSCTL) | ICE);

	/* Wait till the ICS bit is set */
	समयout = jअगरfies + msecs_to_jअगरfies(MMC_TIMEOUT_MS);
	जबतक ((OMAP_HSMMC_READ(host->base, SYSCTL) & ICS) != ICS
		&& समय_beक्रमe(jअगरfies, समयout))
		cpu_relax();

	/*
	 * Enable High-Speed Support
	 * Pre-Requisites
	 *	- Controller should support High-Speed-Enable Bit
	 *	- Controller should not be using DDR Mode
	 *	- Controller should advertise that it supports High Speed
	 *	  in capabilities रेजिस्टर
	 *	- MMC/SD घड़ी coming out of controller > 25MHz
	 */
	अगर ((mmc_pdata(host)->features & HSMMC_HAS_HSPE_SUPPORT) &&
	    (ios->timing != MMC_TIMING_MMC_DDR52) &&
	    (ios->timing != MMC_TIMING_UHS_DDR50) &&
	    ((OMAP_HSMMC_READ(host->base, CAPA) & HSS) == HSS)) अणु
		regval = OMAP_HSMMC_READ(host->base, HCTL);
		अगर (clkभाग && (clk_get_rate(host->fclk)/clkभाग) > 25000000)
			regval |= HSPE;
		अन्यथा
			regval &= ~HSPE;

		OMAP_HSMMC_WRITE(host->base, HCTL, regval);
	पूर्ण

	omap_hsmmc_start_घड़ी(host);
पूर्ण

अटल व्योम omap_hsmmc_set_bus_width(काष्ठा omap_hsmmc_host *host)
अणु
	काष्ठा mmc_ios *ios = &host->mmc->ios;
	u32 con;

	con = OMAP_HSMMC_READ(host->base, CON);
	अगर (ios->timing == MMC_TIMING_MMC_DDR52 ||
	    ios->timing == MMC_TIMING_UHS_DDR50)
		con |= DDR;	/* configure in DDR mode */
	अन्यथा
		con &= ~DDR;
	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_8:
		OMAP_HSMMC_WRITE(host->base, CON, con | DW8);
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		OMAP_HSMMC_WRITE(host->base, CON, con & ~DW8);
		OMAP_HSMMC_WRITE(host->base, HCTL,
			OMAP_HSMMC_READ(host->base, HCTL) | FOUR_BIT);
		अवरोध;
	हाल MMC_BUS_WIDTH_1:
		OMAP_HSMMC_WRITE(host->base, CON, con & ~DW8);
		OMAP_HSMMC_WRITE(host->base, HCTL,
			OMAP_HSMMC_READ(host->base, HCTL) & ~FOUR_BIT);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम omap_hsmmc_set_bus_mode(काष्ठा omap_hsmmc_host *host)
अणु
	काष्ठा mmc_ios *ios = &host->mmc->ios;
	u32 con;

	con = OMAP_HSMMC_READ(host->base, CON);
	अगर (ios->bus_mode == MMC_BUSMODE_OPENDRAIN)
		OMAP_HSMMC_WRITE(host->base, CON, con | OD);
	अन्यथा
		OMAP_HSMMC_WRITE(host->base, CON, con & ~OD);
पूर्ण

#अगर_घोषित CONFIG_PM

/*
 * Restore the MMC host context, अगर it was lost as result of a
 * घातer state change.
 */
अटल पूर्णांक omap_hsmmc_context_restore(काष्ठा omap_hsmmc_host *host)
अणु
	काष्ठा mmc_ios *ios = &host->mmc->ios;
	u32 hctl, capa;
	अचिन्हित दीर्घ समयout;

	अगर (host->con == OMAP_HSMMC_READ(host->base, CON) &&
	    host->hctl == OMAP_HSMMC_READ(host->base, HCTL) &&
	    host->sysctl == OMAP_HSMMC_READ(host->base, SYSCTL) &&
	    host->capa == OMAP_HSMMC_READ(host->base, CAPA))
		वापस 0;

	host->context_loss++;

	अगर (host->pdata->controller_flags & OMAP_HSMMC_SUPPORTS_DUAL_VOLT) अणु
		अगर (host->घातer_mode != MMC_POWER_OFF &&
		    (1 << ios->vdd) <= MMC_VDD_23_24)
			hctl = SDVS18;
		अन्यथा
			hctl = SDVS30;
		capa = VS30 | VS18;
	पूर्ण अन्यथा अणु
		hctl = SDVS18;
		capa = VS18;
	पूर्ण

	अगर (host->mmc->caps & MMC_CAP_SDIO_IRQ)
		hctl |= IWE;

	OMAP_HSMMC_WRITE(host->base, HCTL,
			OMAP_HSMMC_READ(host->base, HCTL) | hctl);

	OMAP_HSMMC_WRITE(host->base, CAPA,
			OMAP_HSMMC_READ(host->base, CAPA) | capa);

	OMAP_HSMMC_WRITE(host->base, HCTL,
			OMAP_HSMMC_READ(host->base, HCTL) | SDBP);

	समयout = jअगरfies + msecs_to_jअगरfies(MMC_TIMEOUT_MS);
	जबतक ((OMAP_HSMMC_READ(host->base, HCTL) & SDBP) != SDBP
		&& समय_beक्रमe(jअगरfies, समयout))
		;

	OMAP_HSMMC_WRITE(host->base, ISE, 0);
	OMAP_HSMMC_WRITE(host->base, IE, 0);
	OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);

	/* Do not initialize card-specअगरic things अगर the घातer is off */
	अगर (host->घातer_mode == MMC_POWER_OFF)
		जाओ out;

	omap_hsmmc_set_bus_width(host);

	omap_hsmmc_set_घड़ी(host);

	omap_hsmmc_set_bus_mode(host);

out:
	dev_dbg(mmc_dev(host->mmc), "context is restored: restore count %d\n",
		host->context_loss);
	वापस 0;
पूर्ण

/*
 * Save the MMC host context (store the number of घातer state changes so far).
 */
अटल व्योम omap_hsmmc_context_save(काष्ठा omap_hsmmc_host *host)
अणु
	host->con =  OMAP_HSMMC_READ(host->base, CON);
	host->hctl = OMAP_HSMMC_READ(host->base, HCTL);
	host->sysctl =  OMAP_HSMMC_READ(host->base, SYSCTL);
	host->capa = OMAP_HSMMC_READ(host->base, CAPA);
पूर्ण

#अन्यथा

अटल पूर्णांक omap_hsmmc_context_restore(काष्ठा omap_hsmmc_host *host)
अणु
	वापस 0;
पूर्ण

अटल व्योम omap_hsmmc_context_save(काष्ठा omap_hsmmc_host *host)
अणु
पूर्ण

#पूर्ण_अगर

/*
 * Send init stream sequence to card
 * beक्रमe sending IDLE command
 */
अटल व्योम send_init_stream(काष्ठा omap_hsmmc_host *host)
अणु
	पूर्णांक reg = 0;
	अचिन्हित दीर्घ समयout;

	disable_irq(host->irq);

	OMAP_HSMMC_WRITE(host->base, IE, INT_EN_MASK);
	OMAP_HSMMC_WRITE(host->base, CON,
		OMAP_HSMMC_READ(host->base, CON) | INIT_STREAM);
	OMAP_HSMMC_WRITE(host->base, CMD, INIT_STREAM_CMD);

	समयout = jअगरfies + msecs_to_jअगरfies(MMC_TIMEOUT_MS);
	जबतक ((reg != CC_EN) && समय_beक्रमe(jअगरfies, समयout))
		reg = OMAP_HSMMC_READ(host->base, STAT) & CC_EN;

	OMAP_HSMMC_WRITE(host->base, CON,
		OMAP_HSMMC_READ(host->base, CON) & ~INIT_STREAM);

	OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
	OMAP_HSMMC_READ(host->base, STAT);

	enable_irq(host->irq);
पूर्ण

अटल sमाप_प्रकार
omap_hsmmc_show_slot_name(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा mmc_host *mmc = container_of(dev, काष्ठा mmc_host, class_dev);
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);

	वापस प्र_लिखो(buf, "%s\n", mmc_pdata(host)->name);
पूर्ण

अटल DEVICE_ATTR(slot_name, S_IRUGO, omap_hsmmc_show_slot_name, शून्य);

/*
 * Configure the response type and send the cmd.
 */
अटल व्योम
omap_hsmmc_start_command(काष्ठा omap_hsmmc_host *host, काष्ठा mmc_command *cmd,
	काष्ठा mmc_data *data)
अणु
	पूर्णांक cmdreg = 0, resptype = 0, cmdtype = 0;

	dev_vdbg(mmc_dev(host->mmc), "%s: CMD%d, argument 0x%08x\n",
		mmc_hostname(host->mmc), cmd->opcode, cmd->arg);
	host->cmd = cmd;

	omap_hsmmc_enable_irq(host, cmd);

	host->response_busy = 0;
	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136)
			resptype = 1;
		अन्यथा अगर (cmd->flags & MMC_RSP_BUSY) अणु
			resptype = 3;
			host->response_busy = 1;
		पूर्ण अन्यथा
			resptype = 2;
	पूर्ण

	/*
	 * Unlike OMAP1 controller, the cmdtype करोes not seem to be based on
	 * ac, bc, adtc, bcr. Only commands ending an खोलो ended transfer need
	 * a val of 0x3, rest 0x0.
	 */
	अगर (cmd == host->mrq->stop)
		cmdtype = 0x3;

	cmdreg = (cmd->opcode << 24) | (resptype << 16) | (cmdtype << 22);

	अगर ((host->flags & AUTO_CMD23) && mmc_op_multi(cmd->opcode) &&
	    host->mrq->sbc) अणु
		cmdreg |= ACEN_ACMD23;
		OMAP_HSMMC_WRITE(host->base, SDMASA, host->mrq->sbc->arg);
	पूर्ण
	अगर (data) अणु
		cmdreg |= DP_SELECT | MSBS | BCE;
		अगर (data->flags & MMC_DATA_READ)
			cmdreg |= Dसूची;
		अन्यथा
			cmdreg &= ~(Dसूची);
	पूर्ण

	अगर (host->use_dma)
		cmdreg |= DMAE;

	host->req_in_progress = 1;

	OMAP_HSMMC_WRITE(host->base, ARG, cmd->arg);
	OMAP_HSMMC_WRITE(host->base, CMD, cmdreg);
पूर्ण

अटल काष्ठा dma_chan *omap_hsmmc_get_dma_chan(काष्ठा omap_hsmmc_host *host,
	काष्ठा mmc_data *data)
अणु
	वापस data->flags & MMC_DATA_WRITE ? host->tx_chan : host->rx_chan;
पूर्ण

अटल व्योम omap_hsmmc_request_करोne(काष्ठा omap_hsmmc_host *host, काष्ठा mmc_request *mrq)
अणु
	पूर्णांक dma_ch;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->irq_lock, flags);
	host->req_in_progress = 0;
	dma_ch = host->dma_ch;
	spin_unlock_irqrestore(&host->irq_lock, flags);

	omap_hsmmc_disable_irq(host);
	/* Do not complete the request अगर DMA is still in progress */
	अगर (mrq->data && host->use_dma && dma_ch != -1)
		वापस;
	host->mrq = शून्य;
	mmc_request_करोne(host->mmc, mrq);
पूर्ण

/*
 * Notअगरy the transfer complete to MMC core
 */
अटल व्योम
omap_hsmmc_xfer_करोne(काष्ठा omap_hsmmc_host *host, काष्ठा mmc_data *data)
अणु
	अगर (!data) अणु
		काष्ठा mmc_request *mrq = host->mrq;

		/* TC beक्रमe CC from CMD6 - करोn't know why, but it happens */
		अगर (host->cmd && host->cmd->opcode == 6 &&
		    host->response_busy) अणु
			host->response_busy = 0;
			वापस;
		पूर्ण

		omap_hsmmc_request_करोne(host, mrq);
		वापस;
	पूर्ण

	host->data = शून्य;

	अगर (!data->error)
		data->bytes_xfered += data->blocks * (data->blksz);
	अन्यथा
		data->bytes_xfered = 0;

	अगर (data->stop && (data->error || !host->mrq->sbc))
		omap_hsmmc_start_command(host, data->stop, शून्य);
	अन्यथा
		omap_hsmmc_request_करोne(host, data->mrq);
पूर्ण

/*
 * Notअगरy the core about command completion
 */
अटल व्योम
omap_hsmmc_cmd_करोne(काष्ठा omap_hsmmc_host *host, काष्ठा mmc_command *cmd)
अणु
	अगर (host->mrq->sbc && (host->cmd == host->mrq->sbc) &&
	    !host->mrq->sbc->error && !(host->flags & AUTO_CMD23)) अणु
		host->cmd = शून्य;
		omap_hsmmc_start_dma_transfer(host);
		omap_hsmmc_start_command(host, host->mrq->cmd,
						host->mrq->data);
		वापस;
	पूर्ण

	host->cmd = शून्य;

	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136) अणु
			/* response type 2 */
			cmd->resp[3] = OMAP_HSMMC_READ(host->base, RSP10);
			cmd->resp[2] = OMAP_HSMMC_READ(host->base, RSP32);
			cmd->resp[1] = OMAP_HSMMC_READ(host->base, RSP54);
			cmd->resp[0] = OMAP_HSMMC_READ(host->base, RSP76);
		पूर्ण अन्यथा अणु
			/* response types 1, 1b, 3, 4, 5, 6 */
			cmd->resp[0] = OMAP_HSMMC_READ(host->base, RSP10);
		पूर्ण
	पूर्ण
	अगर ((host->data == शून्य && !host->response_busy) || cmd->error)
		omap_hsmmc_request_करोne(host, host->mrq);
पूर्ण

/*
 * DMA clean up क्रम command errors
 */
अटल व्योम omap_hsmmc_dma_cleanup(काष्ठा omap_hsmmc_host *host, पूर्णांक त्रुटि_सं)
अणु
	पूर्णांक dma_ch;
	अचिन्हित दीर्घ flags;

	host->data->error = त्रुटि_सं;

	spin_lock_irqsave(&host->irq_lock, flags);
	dma_ch = host->dma_ch;
	host->dma_ch = -1;
	spin_unlock_irqrestore(&host->irq_lock, flags);

	अगर (host->use_dma && dma_ch != -1) अणु
		काष्ठा dma_chan *chan = omap_hsmmc_get_dma_chan(host, host->data);

		dmaengine_terminate_all(chan);
		dma_unmap_sg(chan->device->dev,
			host->data->sg, host->data->sg_len,
			mmc_get_dma_dir(host->data));

		host->data->host_cookie = 0;
	पूर्ण
	host->data = शून्य;
पूर्ण

/*
 * Readable error output
 */
#अगर_घोषित CONFIG_MMC_DEBUG
अटल व्योम omap_hsmmc_dbg_report_irq(काष्ठा omap_hsmmc_host *host, u32 status)
अणु
	/* --- means reserved bit without definition at करोcumentation */
	अटल स्थिर अक्षर *omap_hsmmc_status_bits[] = अणु
		"CC"  , "TC"  , "BGE", "---", "BWR" , "BRR" , "---" , "---" ,
		"CIRQ",	"OBI" , "---", "---", "---" , "---" , "---" , "ERRI",
		"CTO" , "CCRC", "CEB", "CIE", "DTO" , "DCRC", "DEB" , "---" ,
		"ACE" , "---" , "---", "---", "CERR", "BADA", "---" , "---"
	पूर्ण;
	अक्षर res[256];
	अक्षर *buf = res;
	पूर्णांक len, i;

	len = प्र_लिखो(buf, "MMC IRQ 0x%x :", status);
	buf += len;

	क्रम (i = 0; i < ARRAY_SIZE(omap_hsmmc_status_bits); i++)
		अगर (status & (1 << i)) अणु
			len = प्र_लिखो(buf, " %s", omap_hsmmc_status_bits[i]);
			buf += len;
		पूर्ण

	dev_vdbg(mmc_dev(host->mmc), "%s\n", res);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम omap_hsmmc_dbg_report_irq(काष्ठा omap_hsmmc_host *host,
					     u32 status)
अणु
पूर्ण
#पूर्ण_अगर  /* CONFIG_MMC_DEBUG */

/*
 * MMC controller पूर्णांकernal state machines reset
 *
 * Used to reset command or data पूर्णांकernal state machines, using respectively
 *  SRC or SRD bit of SYSCTL रेजिस्टर
 * Can be called from पूर्णांकerrupt context
 */
अटल अंतरभूत व्योम omap_hsmmc_reset_controller_fsm(काष्ठा omap_hsmmc_host *host,
						   अचिन्हित दीर्घ bit)
अणु
	अचिन्हित दीर्घ i = 0;
	अचिन्हित दीर्घ limit = MMC_TIMEOUT_US;

	OMAP_HSMMC_WRITE(host->base, SYSCTL,
			 OMAP_HSMMC_READ(host->base, SYSCTL) | bit);

	/*
	 * OMAP4 ES2 and greater has an updated reset logic.
	 * Monitor a 0->1 transition first
	 */
	अगर (mmc_pdata(host)->features & HSMMC_HAS_UPDATED_RESET) अणु
		जबतक ((!(OMAP_HSMMC_READ(host->base, SYSCTL) & bit))
					&& (i++ < limit))
			udelay(1);
	पूर्ण
	i = 0;

	जबतक ((OMAP_HSMMC_READ(host->base, SYSCTL) & bit) &&
		(i++ < limit))
		udelay(1);

	अगर (OMAP_HSMMC_READ(host->base, SYSCTL) & bit)
		dev_err(mmc_dev(host->mmc),
			"Timeout waiting on controller reset in %s\n",
			__func__);
पूर्ण

अटल व्योम hsmmc_command_incomplete(काष्ठा omap_hsmmc_host *host,
					पूर्णांक err, पूर्णांक end_cmd)
अणु
	अगर (end_cmd) अणु
		omap_hsmmc_reset_controller_fsm(host, SRC);
		अगर (host->cmd)
			host->cmd->error = err;
	पूर्ण

	अगर (host->data) अणु
		omap_hsmmc_reset_controller_fsm(host, SRD);
		omap_hsmmc_dma_cleanup(host, err);
	पूर्ण अन्यथा अगर (host->mrq && host->mrq->cmd)
		host->mrq->cmd->error = err;
पूर्ण

अटल व्योम omap_hsmmc_करो_irq(काष्ठा omap_hsmmc_host *host, पूर्णांक status)
अणु
	काष्ठा mmc_data *data;
	पूर्णांक end_cmd = 0, end_trans = 0;
	पूर्णांक error = 0;

	data = host->data;
	dev_vdbg(mmc_dev(host->mmc), "IRQ Status is %x\n", status);

	अगर (status & ERR_EN) अणु
		omap_hsmmc_dbg_report_irq(host, status);

		अगर (status & (CTO_EN | CCRC_EN | CEB_EN))
			end_cmd = 1;
		अगर (host->data || host->response_busy) अणु
			end_trans = !end_cmd;
			host->response_busy = 0;
		पूर्ण
		अगर (status & (CTO_EN | DTO_EN))
			hsmmc_command_incomplete(host, -ETIMEDOUT, end_cmd);
		अन्यथा अगर (status & (CCRC_EN | DCRC_EN | DEB_EN | CEB_EN |
				   BADA_EN))
			hsmmc_command_incomplete(host, -EILSEQ, end_cmd);

		अगर (status & ACE_EN) अणु
			u32 ac12;
			ac12 = OMAP_HSMMC_READ(host->base, AC12);
			अगर (!(ac12 & ACNE) && host->mrq->sbc) अणु
				end_cmd = 1;
				अगर (ac12 & ACTO)
					error =  -ETIMEDOUT;
				अन्यथा अगर (ac12 & (ACCE | ACEB | ACIE))
					error = -EILSEQ;
				host->mrq->sbc->error = error;
				hsmmc_command_incomplete(host, error, end_cmd);
			पूर्ण
			dev_dbg(mmc_dev(host->mmc), "AC12 err: 0x%x\n", ac12);
		पूर्ण
	पूर्ण

	OMAP_HSMMC_WRITE(host->base, STAT, status);
	अगर (end_cmd || ((status & CC_EN) && host->cmd))
		omap_hsmmc_cmd_करोne(host, host->cmd);
	अगर ((end_trans || (status & TC_EN)) && host->mrq)
		omap_hsmmc_xfer_करोne(host, data);
पूर्ण

/*
 * MMC controller IRQ handler
 */
अटल irqवापस_t omap_hsmmc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap_hsmmc_host *host = dev_id;
	पूर्णांक status;

	status = OMAP_HSMMC_READ(host->base, STAT);
	जबतक (status & (INT_EN_MASK | CIRQ_EN)) अणु
		अगर (host->req_in_progress)
			omap_hsmmc_करो_irq(host, status);

		अगर (status & CIRQ_EN)
			mmc_संकेत_sdio_irq(host->mmc);

		/* Flush posted ग_लिखो */
		status = OMAP_HSMMC_READ(host->base, STAT);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम set_sd_bus_घातer(काष्ठा omap_hsmmc_host *host)
अणु
	अचिन्हित दीर्घ i;

	OMAP_HSMMC_WRITE(host->base, HCTL,
			 OMAP_HSMMC_READ(host->base, HCTL) | SDBP);
	क्रम (i = 0; i < loops_per_jअगरfy; i++) अणु
		अगर (OMAP_HSMMC_READ(host->base, HCTL) & SDBP)
			अवरोध;
		cpu_relax();
	पूर्ण
पूर्ण

/*
 * Switch MMC पूर्णांकerface voltage ... only relevant क्रम MMC1.
 *
 * MMC2 and MMC3 use fixed 1.8V levels, and maybe a transceiver.
 * The MMC2 transceiver controls are used instead of DAT4..DAT7.
 * Some chips, like eMMC ones, use पूर्णांकernal transceivers.
 */
अटल पूर्णांक omap_hsmmc_चयन_opcond(काष्ठा omap_hsmmc_host *host, पूर्णांक vdd)
अणु
	u32 reg_val = 0;
	पूर्णांक ret;

	/* Disable the घड़ीs */
	clk_disable_unprepare(host->dbclk);

	/* Turn the घातer off */
	ret = omap_hsmmc_set_घातer(host, 0);

	/* Turn the घातer ON with given VDD 1.8 or 3.0v */
	अगर (!ret)
		ret = omap_hsmmc_set_घातer(host, 1);
	clk_prepare_enable(host->dbclk);

	अगर (ret != 0)
		जाओ err;

	OMAP_HSMMC_WRITE(host->base, HCTL,
		OMAP_HSMMC_READ(host->base, HCTL) & SDVSCLR);
	reg_val = OMAP_HSMMC_READ(host->base, HCTL);

	/*
	 * If a MMC dual voltage card is detected, the set_ios fn calls
	 * this fn with VDD bit set क्रम 1.8V. Upon card removal from the
	 * slot, omap_hsmmc_set_ios sets the VDD back to 3V on MMC_POWER_OFF.
	 *
	 * Cope with a bit of slop in the range ... per data sheets:
	 *  - "1.8V" क्रम vdds_mmc1/vdds_mmc1a can be up to 2.45V max,
	 *    but recommended values are 1.71V to 1.89V
	 *  - "3.0V" क्रम vdds_mmc1/vdds_mmc1a can be up to 3.5V max,
	 *    but recommended values are 2.7V to 3.3V
	 *
	 * Board setup code shouldn't permit anything very out-of-range.
	 * TWL4030-family VMMC1 and VSIM regulators are fine (aव्योमing the
	 * middle range) but VSIM can't घातer DAT4..DAT7 at more than 3V.
	 */
	अगर ((1 << vdd) <= MMC_VDD_23_24)
		reg_val |= SDVS18;
	अन्यथा
		reg_val |= SDVS30;

	OMAP_HSMMC_WRITE(host->base, HCTL, reg_val);
	set_sd_bus_घातer(host);

	वापस 0;
err:
	dev_err(mmc_dev(host->mmc), "Unable to switch operating voltage\n");
	वापस ret;
पूर्ण

अटल व्योम omap_hsmmc_dma_callback(व्योम *param)
अणु
	काष्ठा omap_hsmmc_host *host = param;
	काष्ठा dma_chan *chan;
	काष्ठा mmc_data *data;
	पूर्णांक req_in_progress;

	spin_lock_irq(&host->irq_lock);
	अगर (host->dma_ch < 0) अणु
		spin_unlock_irq(&host->irq_lock);
		वापस;
	पूर्ण

	data = host->mrq->data;
	chan = omap_hsmmc_get_dma_chan(host, data);
	अगर (!data->host_cookie)
		dma_unmap_sg(chan->device->dev,
			     data->sg, data->sg_len,
			     mmc_get_dma_dir(data));

	req_in_progress = host->req_in_progress;
	host->dma_ch = -1;
	spin_unlock_irq(&host->irq_lock);

	/* If DMA has finished after TC, complete the request */
	अगर (!req_in_progress) अणु
		काष्ठा mmc_request *mrq = host->mrq;

		host->mrq = शून्य;
		mmc_request_करोne(host->mmc, mrq);
	पूर्ण
पूर्ण

अटल पूर्णांक omap_hsmmc_pre_dma_transfer(काष्ठा omap_hsmmc_host *host,
				       काष्ठा mmc_data *data,
				       काष्ठा omap_hsmmc_next *next,
				       काष्ठा dma_chan *chan)
अणु
	पूर्णांक dma_len;

	अगर (!next && data->host_cookie &&
	    data->host_cookie != host->next_data.cookie) अणु
		dev_warn(host->dev, "[%s] invalid cookie: data->host_cookie %d"
		       " host->next_data.cookie %d\n",
		       __func__, data->host_cookie, host->next_data.cookie);
		data->host_cookie = 0;
	पूर्ण

	/* Check अगर next job is alपढ़ोy prepared */
	अगर (next || data->host_cookie != host->next_data.cookie) अणु
		dma_len = dma_map_sg(chan->device->dev, data->sg, data->sg_len,
				     mmc_get_dma_dir(data));

	पूर्ण अन्यथा अणु
		dma_len = host->next_data.dma_len;
		host->next_data.dma_len = 0;
	पूर्ण


	अगर (dma_len == 0)
		वापस -EINVAL;

	अगर (next) अणु
		next->dma_len = dma_len;
		data->host_cookie = ++next->cookie < 0 ? 1 : next->cookie;
	पूर्ण अन्यथा
		host->dma_len = dma_len;

	वापस 0;
पूर्ण

/*
 * Routine to configure and start DMA क्रम the MMC card
 */
अटल पूर्णांक omap_hsmmc_setup_dma_transfer(काष्ठा omap_hsmmc_host *host,
					काष्ठा mmc_request *req)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	पूर्णांक ret = 0, i;
	काष्ठा mmc_data *data = req->data;
	काष्ठा dma_chan *chan;
	काष्ठा dma_slave_config cfg = अणु
		.src_addr = host->mapbase + OMAP_HSMMC_DATA,
		.dst_addr = host->mapbase + OMAP_HSMMC_DATA,
		.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.src_maxburst = data->blksz / 4,
		.dst_maxburst = data->blksz / 4,
	पूर्ण;

	/* Sanity check: all the SG entries must be aligned by block size. */
	क्रम (i = 0; i < data->sg_len; i++) अणु
		काष्ठा scatterlist *sgl;

		sgl = data->sg + i;
		अगर (sgl->length % data->blksz)
			वापस -EINVAL;
	पूर्ण
	अगर ((data->blksz % 4) != 0)
		/* REVISIT: The MMC buffer increments only when MSB is written.
		 * Return error क्रम blksz which is non multiple of four.
		 */
		वापस -EINVAL;

	BUG_ON(host->dma_ch != -1);

	chan = omap_hsmmc_get_dma_chan(host, data);

	ret = dmaengine_slave_config(chan, &cfg);
	अगर (ret)
		वापस ret;

	ret = omap_hsmmc_pre_dma_transfer(host, data, शून्य, chan);
	अगर (ret)
		वापस ret;

	tx = dmaengine_prep_slave_sg(chan, data->sg, data->sg_len,
		data->flags & MMC_DATA_WRITE ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
		DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!tx) अणु
		dev_err(mmc_dev(host->mmc), "prep_slave_sg() failed\n");
		/* FIXME: cleanup */
		वापस -1;
	पूर्ण

	tx->callback = omap_hsmmc_dma_callback;
	tx->callback_param = host;

	/* Does not fail */
	dmaengine_submit(tx);

	host->dma_ch = 1;

	वापस 0;
पूर्ण

अटल व्योम set_data_समयout(काष्ठा omap_hsmmc_host *host,
			     अचिन्हित दीर्घ दीर्घ समयout_ns,
			     अचिन्हित पूर्णांक समयout_clks)
अणु
	अचिन्हित दीर्घ दीर्घ समयout = समयout_ns;
	अचिन्हित पूर्णांक cycle_ns;
	uपूर्णांक32_t reg, clkd, dto = 0;

	reg = OMAP_HSMMC_READ(host->base, SYSCTL);
	clkd = (reg & CLKD_MASK) >> CLKD_SHIFT;
	अगर (clkd == 0)
		clkd = 1;

	cycle_ns = 1000000000 / (host->clk_rate / clkd);
	करो_भाग(समयout, cycle_ns);
	समयout += समयout_clks;
	अगर (समयout) अणु
		जबतक ((समयout & 0x80000000) == 0) अणु
			dto += 1;
			समयout <<= 1;
		पूर्ण
		dto = 31 - dto;
		समयout <<= 1;
		अगर (समयout && dto)
			dto += 1;
		अगर (dto >= 13)
			dto -= 13;
		अन्यथा
			dto = 0;
		अगर (dto > 14)
			dto = 14;
	पूर्ण

	reg &= ~DTO_MASK;
	reg |= dto << DTO_SHIFT;
	OMAP_HSMMC_WRITE(host->base, SYSCTL, reg);
पूर्ण

अटल व्योम omap_hsmmc_start_dma_transfer(काष्ठा omap_hsmmc_host *host)
अणु
	काष्ठा mmc_request *req = host->mrq;
	काष्ठा dma_chan *chan;

	अगर (!req->data)
		वापस;
	OMAP_HSMMC_WRITE(host->base, BLK, (req->data->blksz)
				| (req->data->blocks << 16));
	set_data_समयout(host, req->data->समयout_ns,
				req->data->समयout_clks);
	chan = omap_hsmmc_get_dma_chan(host, req->data);
	dma_async_issue_pending(chan);
पूर्ण

/*
 * Configure block length क्रम MMC/SD cards and initiate the transfer.
 */
अटल पूर्णांक
omap_hsmmc_prepare_data(काष्ठा omap_hsmmc_host *host, काष्ठा mmc_request *req)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ दीर्घ समयout;

	host->data = req->data;

	अगर (req->data == शून्य) अणु
		OMAP_HSMMC_WRITE(host->base, BLK, 0);
		अगर (req->cmd->flags & MMC_RSP_BUSY) अणु
			समयout = req->cmd->busy_समयout * NSEC_PER_MSEC;

			/*
			 * Set an arbitrary 100ms data समयout क्रम commands with
			 * busy संकेत and no indication of busy_समयout.
			 */
			अगर (!समयout)
				समयout = 100000000U;

			set_data_समयout(host, समयout, 0);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (host->use_dma) अणु
		ret = omap_hsmmc_setup_dma_transfer(host, req);
		अगर (ret != 0) अणु
			dev_err(mmc_dev(host->mmc), "MMC start dma failure\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम omap_hsmmc_post_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq,
				पूर्णांक err)
अणु
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (host->use_dma && data->host_cookie) अणु
		काष्ठा dma_chan *c = omap_hsmmc_get_dma_chan(host, data);

		dma_unmap_sg(c->device->dev, data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
		data->host_cookie = 0;
	पूर्ण
पूर्ण

अटल व्योम omap_hsmmc_pre_req(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);

	अगर (mrq->data->host_cookie) अणु
		mrq->data->host_cookie = 0;
		वापस ;
	पूर्ण

	अगर (host->use_dma) अणु
		काष्ठा dma_chan *c = omap_hsmmc_get_dma_chan(host, mrq->data);

		अगर (omap_hsmmc_pre_dma_transfer(host, mrq->data,
						&host->next_data, c))
			mrq->data->host_cookie = 0;
	पूर्ण
पूर्ण

/*
 * Request function. क्रम पढ़ो/ग_लिखो operation
 */
अटल व्योम omap_hsmmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *req)
अणु
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);
	पूर्णांक err;

	BUG_ON(host->req_in_progress);
	BUG_ON(host->dma_ch != -1);
	अगर (host->reqs_blocked)
		host->reqs_blocked = 0;
	WARN_ON(host->mrq != शून्य);
	host->mrq = req;
	host->clk_rate = clk_get_rate(host->fclk);
	err = omap_hsmmc_prepare_data(host, req);
	अगर (err) अणु
		req->cmd->error = err;
		अगर (req->data)
			req->data->error = err;
		host->mrq = शून्य;
		mmc_request_करोne(mmc, req);
		वापस;
	पूर्ण
	अगर (req->sbc && !(host->flags & AUTO_CMD23)) अणु
		omap_hsmmc_start_command(host, req->sbc, शून्य);
		वापस;
	पूर्ण

	omap_hsmmc_start_dma_transfer(host);
	omap_hsmmc_start_command(host, req->cmd, req->data);
पूर्ण

/* Routine to configure घड़ी values. Exposed API to core */
अटल व्योम omap_hsmmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);
	पूर्णांक करो_send_init_stream = 0;

	अगर (ios->घातer_mode != host->घातer_mode) अणु
		चयन (ios->घातer_mode) अणु
		हाल MMC_POWER_OFF:
			omap_hsmmc_set_घातer(host, 0);
			अवरोध;
		हाल MMC_POWER_UP:
			omap_hsmmc_set_घातer(host, 1);
			अवरोध;
		हाल MMC_POWER_ON:
			करो_send_init_stream = 1;
			अवरोध;
		पूर्ण
		host->घातer_mode = ios->घातer_mode;
	पूर्ण

	/* FIXME: set रेजिस्टरs based only on changes to ios */

	omap_hsmmc_set_bus_width(host);

	अगर (host->pdata->controller_flags & OMAP_HSMMC_SUPPORTS_DUAL_VOLT) अणु
		/* Only MMC1 can पूर्णांकerface at 3V without some flavor
		 * of बाह्यal transceiver; but they all handle 1.8V.
		 */
		अगर ((OMAP_HSMMC_READ(host->base, HCTL) & SDVSDET) &&
			(ios->vdd == DUAL_VOLT_OCR_BIT)) अणु
				/*
				 * The mmc_select_voltage fn of the core करोes
				 * not seem to set the घातer_mode to
				 * MMC_POWER_UP upon recalculating the voltage.
				 * vdd 1.8v.
				 */
			अगर (omap_hsmmc_चयन_opcond(host, ios->vdd) != 0)
				dev_dbg(mmc_dev(host->mmc),
						"Switch operation failed\n");
		पूर्ण
	पूर्ण

	omap_hsmmc_set_घड़ी(host);

	अगर (करो_send_init_stream)
		send_init_stream(host);

	omap_hsmmc_set_bus_mode(host);
पूर्ण

अटल व्योम omap_hsmmc_init_card(काष्ठा mmc_host *mmc, काष्ठा mmc_card *card)
अणु
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);

	अगर (card->type == MMC_TYPE_SDIO || card->type == MMC_TYPE_SD_COMBO) अणु
		काष्ठा device_node *np = mmc_dev(mmc)->of_node;

		/*
		 * REVISIT: should be moved to sdio core and made more
		 * general e.g. by expanding the DT bindings of child nodes
		 * to provide a mechanism to provide this inक्रमmation:
		 * Documentation/devicetree/bindings/mmc/mmc-card.txt
		 */

		np = of_get_compatible_child(np, "ti,wl1251");
		अगर (np) अणु
			/*
			 * We have TI wl1251 attached to MMC3. Pass this
			 * inक्रमmation to the SDIO core because it can't be
			 * probed by normal methods.
			 */

			dev_info(host->dev, "found wl1251\n");
			card->quirks |= MMC_QUIRK_NONSTD_SDIO;
			card->cccr.wide_bus = 1;
			card->cis.venकरोr = 0x104c;
			card->cis.device = 0x9066;
			card->cis.blksize = 512;
			card->cis.max_dtr = 24000000;
			card->ocr = 0x80;
			of_node_put(np);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम omap_hsmmc_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);
	u32 irq_mask, con;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->irq_lock, flags);

	con = OMAP_HSMMC_READ(host->base, CON);
	irq_mask = OMAP_HSMMC_READ(host->base, ISE);
	अगर (enable) अणु
		host->flags |= HSMMC_SDIO_IRQ_ENABLED;
		irq_mask |= CIRQ_EN;
		con |= CTPL | CLKEXTFREE;
	पूर्ण अन्यथा अणु
		host->flags &= ~HSMMC_SDIO_IRQ_ENABLED;
		irq_mask &= ~CIRQ_EN;
		con &= ~(CTPL | CLKEXTFREE);
	पूर्ण
	OMAP_HSMMC_WRITE(host->base, CON, con);
	OMAP_HSMMC_WRITE(host->base, IE, irq_mask);

	/*
	 * अगर enable, piggy back detection on current request
	 * but always disable immediately
	 */
	अगर (!host->req_in_progress || !enable)
		OMAP_HSMMC_WRITE(host->base, ISE, irq_mask);

	/* flush posted ग_लिखो */
	OMAP_HSMMC_READ(host->base, IE);

	spin_unlock_irqrestore(&host->irq_lock, flags);
पूर्ण

अटल पूर्णांक omap_hsmmc_configure_wake_irq(काष्ठा omap_hsmmc_host *host)
अणु
	पूर्णांक ret;

	/*
	 * For omaps with wake-up path, wakeirq will be irq from pinctrl and
	 * क्रम other omaps, wakeirq will be from GPIO (dat line remuxed to
	 * gpio). wakeirq is needed to detect sdio irq in runसमय suspend state
	 * with functional घड़ी disabled.
	 */
	अगर (!host->dev->of_node || !host->wake_irq)
		वापस -ENODEV;

	ret = dev_pm_set_dedicated_wake_irq(host->dev, host->wake_irq);
	अगर (ret) अणु
		dev_err(mmc_dev(host->mmc), "Unable to request wake IRQ\n");
		जाओ err;
	पूर्ण

	/*
	 * Some omaps करोn't have wake-up path from deeper idle states
	 * and need to remux SDIO DAT1 to GPIO क्रम wake-up from idle.
	 */
	अगर (host->pdata->controller_flags & OMAP_HSMMC_SWAKEUP_MISSING) अणु
		काष्ठा pinctrl *p = devm_pinctrl_get(host->dev);
		अगर (IS_ERR(p)) अणु
			ret = PTR_ERR(p);
			जाओ err_मुक्त_irq;
		पूर्ण

		अगर (IS_ERR(pinctrl_lookup_state(p, PINCTRL_STATE_IDLE))) अणु
			dev_info(host->dev, "missing idle pinctrl state\n");
			devm_pinctrl_put(p);
			ret = -EINVAL;
			जाओ err_मुक्त_irq;
		पूर्ण
		devm_pinctrl_put(p);
	पूर्ण

	OMAP_HSMMC_WRITE(host->base, HCTL,
			 OMAP_HSMMC_READ(host->base, HCTL) | IWE);
	वापस 0;

err_मुक्त_irq:
	dev_pm_clear_wake_irq(host->dev);
err:
	dev_warn(host->dev, "no SDIO IRQ support, falling back to polling\n");
	host->wake_irq = 0;
	वापस ret;
पूर्ण

अटल व्योम omap_hsmmc_conf_bus_घातer(काष्ठा omap_hsmmc_host *host)
अणु
	u32 hctl, capa, value;

	/* Only MMC1 supports 3.0V */
	अगर (host->pdata->controller_flags & OMAP_HSMMC_SUPPORTS_DUAL_VOLT) अणु
		hctl = SDVS30;
		capa = VS30 | VS18;
	पूर्ण अन्यथा अणु
		hctl = SDVS18;
		capa = VS18;
	पूर्ण

	value = OMAP_HSMMC_READ(host->base, HCTL) & ~SDVS_MASK;
	OMAP_HSMMC_WRITE(host->base, HCTL, value | hctl);

	value = OMAP_HSMMC_READ(host->base, CAPA);
	OMAP_HSMMC_WRITE(host->base, CAPA, value | capa);

	/* Set SD bus घातer bit */
	set_sd_bus_घातer(host);
पूर्ण

अटल पूर्णांक omap_hsmmc_multi_io_quirk(काष्ठा mmc_card *card,
				     अचिन्हित पूर्णांक direction, पूर्णांक blk_size)
अणु
	/* This controller can't करो multiblock पढ़ोs due to hw bugs */
	अगर (direction == MMC_DATA_READ)
		वापस 1;

	वापस blk_size;
पूर्ण

अटल काष्ठा mmc_host_ops omap_hsmmc_ops = अणु
	.post_req = omap_hsmmc_post_req,
	.pre_req = omap_hsmmc_pre_req,
	.request = omap_hsmmc_request,
	.set_ios = omap_hsmmc_set_ios,
	.get_cd = mmc_gpio_get_cd,
	.get_ro = mmc_gpio_get_ro,
	.init_card = omap_hsmmc_init_card,
	.enable_sdio_irq = omap_hsmmc_enable_sdio_irq,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक mmc_regs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mmc_host *mmc = s->निजी;
	काष्ठा omap_hsmmc_host *host = mmc_priv(mmc);

	seq_म_लिखो(s, "mmc%d:\n", mmc->index);
	seq_म_लिखो(s, "sdio irq mode\t%s\n",
		   (mmc->caps & MMC_CAP_SDIO_IRQ) ? "interrupt" : "polling");

	अगर (mmc->caps & MMC_CAP_SDIO_IRQ) अणु
		seq_म_लिखो(s, "sdio irq \t%s\n",
			   (host->flags & HSMMC_SDIO_IRQ_ENABLED) ?  "enabled"
			   : "disabled");
	पूर्ण
	seq_म_लिखो(s, "ctx_loss:\t%d\n", host->context_loss);

	pm_runसमय_get_sync(host->dev);
	seq_माला_दो(s, "\nregs:\n");
	seq_म_लिखो(s, "CON:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, CON));
	seq_म_लिखो(s, "PSTATE:\t\t0x%08x\n",
		   OMAP_HSMMC_READ(host->base, PSTATE));
	seq_म_लिखो(s, "HCTL:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, HCTL));
	seq_म_लिखो(s, "SYSCTL:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, SYSCTL));
	seq_म_लिखो(s, "IE:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, IE));
	seq_म_लिखो(s, "ISE:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, ISE));
	seq_म_लिखो(s, "CAPA:\t\t0x%08x\n",
			OMAP_HSMMC_READ(host->base, CAPA));

	pm_runसमय_mark_last_busy(host->dev);
	pm_runसमय_put_स्वतःsuspend(host->dev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mmc_regs);

अटल व्योम omap_hsmmc_debugfs(काष्ठा mmc_host *mmc)
अणु
	अगर (mmc->debugfs_root)
		debugfs_create_file("regs", S_IRUSR, mmc->debugfs_root,
			mmc, &mmc_regs_fops);
पूर्ण

#अन्यथा

अटल व्योम omap_hsmmc_debugfs(काष्ठा mmc_host *mmc)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा omap_mmc_of_data omap3_pre_es3_mmc_of_data = अणु
	/* See 35xx errata 2.1.1.128 in SPRZ278F */
	.controller_flags = OMAP_HSMMC_BROKEN_MULTIBLOCK_READ,
पूर्ण;

अटल स्थिर काष्ठा omap_mmc_of_data omap4_mmc_of_data = अणु
	.reg_offset = 0x100,
पूर्ण;
अटल स्थिर काष्ठा omap_mmc_of_data am33xx_mmc_of_data = अणु
	.reg_offset = 0x100,
	.controller_flags = OMAP_HSMMC_SWAKEUP_MISSING,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_mmc_of_match[] = अणु
	अणु
		.compatible = "ti,omap2-hsmmc",
	पूर्ण,
	अणु
		.compatible = "ti,omap3-pre-es3-hsmmc",
		.data = &omap3_pre_es3_mmc_of_data,
	पूर्ण,
	अणु
		.compatible = "ti,omap3-hsmmc",
	पूर्ण,
	अणु
		.compatible = "ti,omap4-hsmmc",
		.data = &omap4_mmc_of_data,
	पूर्ण,
	अणु
		.compatible = "ti,am33xx-hsmmc",
		.data = &am33xx_mmc_of_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_mmc_of_match);

अटल काष्ठा omap_hsmmc_platक्रमm_data *of_get_hsmmc_pdata(काष्ठा device *dev)
अणु
	काष्ठा omap_hsmmc_platक्रमm_data *pdata, *legacy;
	काष्ठा device_node *np = dev->of_node;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM); /* out of memory */

	legacy = dev_get_platdata(dev);
	अगर (legacy && legacy->name)
		pdata->name = legacy->name;

	अगर (of_find_property(np, "ti,dual-volt", शून्य))
		pdata->controller_flags |= OMAP_HSMMC_SUPPORTS_DUAL_VOLT;

	अगर (of_find_property(np, "ti,non-removable", शून्य)) अणु
		pdata->nonremovable = true;
		pdata->no_regulator_off_init = true;
	पूर्ण

	अगर (of_find_property(np, "ti,needs-special-reset", शून्य))
		pdata->features |= HSMMC_HAS_UPDATED_RESET;

	अगर (of_find_property(np, "ti,needs-special-hs-handling", शून्य))
		pdata->features |= HSMMC_HAS_HSPE_SUPPORT;

	वापस pdata;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा omap_hsmmc_platक्रमm_data
			*of_get_hsmmc_pdata(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक omap_hsmmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_hsmmc_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा mmc_host *mmc;
	काष्ठा omap_hsmmc_host *host = शून्य;
	काष्ठा resource *res;
	पूर्णांक ret, irq;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा omap_mmc_of_data *data;
	व्योम __iomem *base;

	match = of_match_device(of_match_ptr(omap_mmc_of_match), &pdev->dev);
	अगर (match) अणु
		pdata = of_get_hsmmc_pdata(&pdev->dev);

		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);

		अगर (match->data) अणु
			data = match->data;
			pdata->reg_offset = data->reg_offset;
			pdata->controller_flags |= data->controller_flags;
		पूर्ण
	पूर्ण

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "Platform Data is missing\n");
		वापस -ENXIO;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (res == शून्य || irq < 0)
		वापस -ENXIO;

	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	mmc = mmc_alloc_host(माप(काष्ठा omap_hsmmc_host), &pdev->dev);
	अगर (!mmc) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ err1;

	host		= mmc_priv(mmc);
	host->mmc	= mmc;
	host->pdata	= pdata;
	host->dev	= &pdev->dev;
	host->use_dma	= 1;
	host->dma_ch	= -1;
	host->irq	= irq;
	host->mapbase	= res->start + pdata->reg_offset;
	host->base	= base + pdata->reg_offset;
	host->घातer_mode = MMC_POWER_OFF;
	host->next_data.cookie = 1;
	host->pbias_enabled = false;
	host->vqmmc_enabled = false;

	platक्रमm_set_drvdata(pdev, host);

	अगर (pdev->dev.of_node)
		host->wake_irq = irq_of_parse_and_map(pdev->dev.of_node, 1);

	mmc->ops	= &omap_hsmmc_ops;

	mmc->f_min = OMAP_MMC_MIN_CLOCK;

	अगर (pdata->max_freq > 0)
		mmc->f_max = pdata->max_freq;
	अन्यथा अगर (mmc->f_max == 0)
		mmc->f_max = OMAP_MMC_MAX_CLOCK;

	spin_lock_init(&host->irq_lock);

	host->fclk = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(host->fclk)) अणु
		ret = PTR_ERR(host->fclk);
		host->fclk = शून्य;
		जाओ err1;
	पूर्ण

	अगर (host->pdata->controller_flags & OMAP_HSMMC_BROKEN_MULTIBLOCK_READ) अणु
		dev_info(&pdev->dev, "multiblock reads disabled due to 35xx erratum 2.1.1.128; MMC read performance may suffer\n");
		omap_hsmmc_ops.multi_io_quirk = omap_hsmmc_multi_io_quirk;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);
	pm_runसमय_enable(host->dev);
	pm_runसमय_get_sync(host->dev);
	pm_runसमय_set_स्वतःsuspend_delay(host->dev, MMC_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(host->dev);

	omap_hsmmc_context_save(host);

	host->dbclk = devm_clk_get(&pdev->dev, "mmchsdb_fck");
	/*
	 * MMC can still work without debounce घड़ी.
	 */
	अगर (IS_ERR(host->dbclk)) अणु
		host->dbclk = शून्य;
	पूर्ण अन्यथा अगर (clk_prepare_enable(host->dbclk) != 0) अणु
		dev_warn(mmc_dev(host->mmc), "Failed to enable debounce clk\n");
		host->dbclk = शून्य;
	पूर्ण

	/* Set this to a value that allows allocating an entire descriptor
	 * list within a page (zero order allocation). */
	mmc->max_segs = 64;

	mmc->max_blk_size = 512;       /* Block Length at max can be 1024 */
	mmc->max_blk_count = 0xFFFF;    /* No. of Blocks is 16 bits */
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;

	mmc->caps |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
		     MMC_CAP_WAIT_WHILE_BUSY | MMC_CAP_CMD23;

	mmc->caps |= mmc_pdata(host)->caps;
	अगर (mmc->caps & MMC_CAP_8_BIT_DATA)
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	अगर (mmc_pdata(host)->nonremovable)
		mmc->caps |= MMC_CAP_NONREMOVABLE;

	mmc->pm_caps |= mmc_pdata(host)->pm_caps;

	omap_hsmmc_conf_bus_घातer(host);

	host->rx_chan = dma_request_chan(&pdev->dev, "rx");
	अगर (IS_ERR(host->rx_chan)) अणु
		dev_err(mmc_dev(host->mmc), "RX DMA channel request failed\n");
		ret = PTR_ERR(host->rx_chan);
		जाओ err_irq;
	पूर्ण

	host->tx_chan = dma_request_chan(&pdev->dev, "tx");
	अगर (IS_ERR(host->tx_chan)) अणु
		dev_err(mmc_dev(host->mmc), "TX DMA channel request failed\n");
		ret = PTR_ERR(host->tx_chan);
		जाओ err_irq;
	पूर्ण

	/*
	 * Limit the maximum segment size to the lower of the request size
	 * and the DMA engine device segment size limits.  In reality, with
	 * 32-bit transfers, the DMA engine can करो दीर्घer segments than this
	 * but there is no way to represent that in the DMA model - अगर we
	 * increase this figure here, we get warnings from the DMA API debug.
	 */
	mmc->max_seg_size = min3(mmc->max_req_size,
			dma_get_max_seg_size(host->rx_chan->device->dev),
			dma_get_max_seg_size(host->tx_chan->device->dev));

	/* Request IRQ क्रम MMC operations */
	ret = devm_request_irq(&pdev->dev, host->irq, omap_hsmmc_irq, 0,
			mmc_hostname(mmc), host);
	अगर (ret) अणु
		dev_err(mmc_dev(host->mmc), "Unable to grab HSMMC IRQ\n");
		जाओ err_irq;
	पूर्ण

	ret = omap_hsmmc_reg_get(host);
	अगर (ret)
		जाओ err_irq;

	अगर (!mmc->ocr_avail)
		mmc->ocr_avail = mmc_pdata(host)->ocr_mask;

	omap_hsmmc_disable_irq(host);

	/*
	 * For now, only support SDIO पूर्णांकerrupt अगर we have a separate
	 * wake-up पूर्णांकerrupt configured from device tree. This is because
	 * the wake-up पूर्णांकerrupt is needed क्रम idle state and some
	 * platक्रमms need special quirks. And we करोn't want to add new
	 * legacy mux platक्रमm init code callbacks any दीर्घer as we
	 * are moving to DT based booting anyways.
	 */
	ret = omap_hsmmc_configure_wake_irq(host);
	अगर (!ret)
		mmc->caps |= MMC_CAP_SDIO_IRQ;

	mmc_add_host(mmc);

	अगर (mmc_pdata(host)->name != शून्य) अणु
		ret = device_create_file(&mmc->class_dev, &dev_attr_slot_name);
		अगर (ret < 0)
			जाओ err_slot_name;
	पूर्ण

	omap_hsmmc_debugfs(mmc);
	pm_runसमय_mark_last_busy(host->dev);
	pm_runसमय_put_स्वतःsuspend(host->dev);

	वापस 0;

err_slot_name:
	mmc_हटाओ_host(mmc);
err_irq:
	device_init_wakeup(&pdev->dev, false);
	अगर (!IS_ERR_OR_शून्य(host->tx_chan))
		dma_release_channel(host->tx_chan);
	अगर (!IS_ERR_OR_शून्य(host->rx_chan))
		dma_release_channel(host->rx_chan);
	pm_runसमय_करोnt_use_स्वतःsuspend(host->dev);
	pm_runसमय_put_sync(host->dev);
	pm_runसमय_disable(host->dev);
	clk_disable_unprepare(host->dbclk);
err1:
	mmc_मुक्त_host(mmc);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक omap_hsmmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_hsmmc_host *host = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(host->dev);
	mmc_हटाओ_host(host->mmc);

	dma_release_channel(host->tx_chan);
	dma_release_channel(host->rx_chan);

	dev_pm_clear_wake_irq(host->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(host->dev);
	pm_runसमय_put_sync(host->dev);
	pm_runसमय_disable(host->dev);
	device_init_wakeup(&pdev->dev, false);
	clk_disable_unprepare(host->dbclk);

	mmc_मुक्त_host(host->mmc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omap_hsmmc_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_hsmmc_host *host = dev_get_drvdata(dev);

	अगर (!host)
		वापस 0;

	pm_runसमय_get_sync(host->dev);

	अगर (!(host->mmc->pm_flags & MMC_PM_KEEP_POWER)) अणु
		OMAP_HSMMC_WRITE(host->base, ISE, 0);
		OMAP_HSMMC_WRITE(host->base, IE, 0);
		OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
		OMAP_HSMMC_WRITE(host->base, HCTL,
				OMAP_HSMMC_READ(host->base, HCTL) & ~SDBP);
	पूर्ण

	clk_disable_unprepare(host->dbclk);

	pm_runसमय_put_sync(host->dev);
	वापस 0;
पूर्ण

/* Routine to resume the MMC device */
अटल पूर्णांक omap_hsmmc_resume(काष्ठा device *dev)
अणु
	काष्ठा omap_hsmmc_host *host = dev_get_drvdata(dev);

	अगर (!host)
		वापस 0;

	pm_runसमय_get_sync(host->dev);

	clk_prepare_enable(host->dbclk);

	अगर (!(host->mmc->pm_flags & MMC_PM_KEEP_POWER))
		omap_hsmmc_conf_bus_घातer(host);

	pm_runसमय_mark_last_busy(host->dev);
	pm_runसमय_put_स्वतःsuspend(host->dev);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक omap_hsmmc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_hsmmc_host *host;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	host = dev_get_drvdata(dev);
	omap_hsmmc_context_save(host);
	dev_dbg(dev, "disabled\n");

	spin_lock_irqsave(&host->irq_lock, flags);
	अगर ((host->mmc->caps & MMC_CAP_SDIO_IRQ) &&
	    (host->flags & HSMMC_SDIO_IRQ_ENABLED)) अणु
		/* disable sdio irq handling to prevent race */
		OMAP_HSMMC_WRITE(host->base, ISE, 0);
		OMAP_HSMMC_WRITE(host->base, IE, 0);

		अगर (!(OMAP_HSMMC_READ(host->base, PSTATE) & DLEV_DAT(1))) अणु
			/*
			 * dat1 line low, pending sdio irq
			 * race condition: possible irq handler running on
			 * multi-core, पात
			 */
			dev_dbg(dev, "pending sdio irq, abort suspend\n");
			OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
			OMAP_HSMMC_WRITE(host->base, ISE, CIRQ_EN);
			OMAP_HSMMC_WRITE(host->base, IE, CIRQ_EN);
			pm_runसमय_mark_last_busy(dev);
			ret = -EBUSY;
			जाओ पात;
		पूर्ण

		pinctrl_pm_select_idle_state(dev);
	पूर्ण अन्यथा अणु
		pinctrl_pm_select_idle_state(dev);
	पूर्ण

पात:
	spin_unlock_irqrestore(&host->irq_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक omap_hsmmc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा omap_hsmmc_host *host;
	अचिन्हित दीर्घ flags;

	host = dev_get_drvdata(dev);
	omap_hsmmc_context_restore(host);
	dev_dbg(dev, "enabled\n");

	spin_lock_irqsave(&host->irq_lock, flags);
	अगर ((host->mmc->caps & MMC_CAP_SDIO_IRQ) &&
	    (host->flags & HSMMC_SDIO_IRQ_ENABLED)) अणु

		pinctrl_select_शेष_state(host->dev);

		/* irq lost, अगर pinmux incorrect */
		OMAP_HSMMC_WRITE(host->base, STAT, STAT_CLEAR);
		OMAP_HSMMC_WRITE(host->base, ISE, CIRQ_EN);
		OMAP_HSMMC_WRITE(host->base, IE, CIRQ_EN);
	पूर्ण अन्यथा अणु
		pinctrl_select_शेष_state(host->dev);
	पूर्ण
	spin_unlock_irqrestore(&host->irq_lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_hsmmc_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(omap_hsmmc_suspend, omap_hsmmc_resume)
	.runसमय_suspend = omap_hsmmc_runसमय_suspend,
	.runसमय_resume = omap_hsmmc_runसमय_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver omap_hsmmc_driver = अणु
	.probe		= omap_hsmmc_probe,
	.हटाओ		= omap_hsmmc_हटाओ,
	.driver		= अणु
		.name = DRIVER_NAME,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm = &omap_hsmmc_dev_pm_ops,
		.of_match_table = of_match_ptr(omap_mmc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_hsmmc_driver);
MODULE_DESCRIPTION("OMAP High Speed Multimedia Card driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Texas Instruments Inc");
