<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * SDHCI Controller driver क्रम TI's OMAP SoCs
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/thermal.h>

#समावेश "sdhci-pltfm.h"

#घोषणा SDHCI_OMAP_CON		0x12c
#घोषणा CON_DW8			BIT(5)
#घोषणा CON_DMA_MASTER		BIT(20)
#घोषणा CON_DDR			BIT(19)
#घोषणा CON_CLKEXTFREE		BIT(16)
#घोषणा CON_PADEN		BIT(15)
#घोषणा CON_CTPL		BIT(11)
#घोषणा CON_INIT		BIT(1)
#घोषणा CON_OD			BIT(0)

#घोषणा SDHCI_OMAP_DLL		0x0134
#घोषणा DLL_SWT			BIT(20)
#घोषणा DLL_FORCE_SR_C_SHIFT	13
#घोषणा DLL_FORCE_SR_C_MASK	(0x7f << DLL_FORCE_SR_C_SHIFT)
#घोषणा DLL_FORCE_VALUE		BIT(12)
#घोषणा DLL_CALIB		BIT(1)

#घोषणा SDHCI_OMAP_CMD		0x20c

#घोषणा SDHCI_OMAP_PSTATE	0x0224
#घोषणा PSTATE_DLEV_DAT0	BIT(20)
#घोषणा PSTATE_DATI		BIT(1)

#घोषणा SDHCI_OMAP_HCTL		0x228
#घोषणा HCTL_SDBP		BIT(8)
#घोषणा HCTL_SDVS_SHIFT		9
#घोषणा HCTL_SDVS_MASK		(0x7 << HCTL_SDVS_SHIFT)
#घोषणा HCTL_SDVS_33		(0x7 << HCTL_SDVS_SHIFT)
#घोषणा HCTL_SDVS_30		(0x6 << HCTL_SDVS_SHIFT)
#घोषणा HCTL_SDVS_18		(0x5 << HCTL_SDVS_SHIFT)

#घोषणा SDHCI_OMAP_SYSCTL	0x22c
#घोषणा SYSCTL_CEN		BIT(2)
#घोषणा SYSCTL_CLKD_SHIFT	6
#घोषणा SYSCTL_CLKD_MASK	0x3ff

#घोषणा SDHCI_OMAP_STAT		0x230

#घोषणा SDHCI_OMAP_IE		0x234
#घोषणा INT_CC_EN		BIT(0)

#घोषणा SDHCI_OMAP_AC12		0x23c
#घोषणा AC12_V1V8_SIGEN		BIT(19)
#घोषणा AC12_SCLK_SEL		BIT(23)

#घोषणा SDHCI_OMAP_CAPA		0x240
#घोषणा CAPA_VS33		BIT(24)
#घोषणा CAPA_VS30		BIT(25)
#घोषणा CAPA_VS18		BIT(26)

#घोषणा SDHCI_OMAP_CAPA2	0x0244
#घोषणा CAPA2_TSDR50		BIT(13)

#घोषणा SDHCI_OMAP_TIMEOUT	1		/* 1 msec */

#घोषणा SYSCTL_CLKD_MAX		0x3FF

#घोषणा IOV_1V8			1800000		/* 180000 uV */
#घोषणा IOV_3V0			3000000		/* 300000 uV */
#घोषणा IOV_3V3			3300000		/* 330000 uV */

#घोषणा MAX_PHASE_DELAY		0x7C

/* sdhci-omap controller flags */
#घोषणा SDHCI_OMAP_REQUIRE_IODELAY	BIT(0)
#घोषणा SDHCI_OMAP_SPECIAL_RESET	BIT(1)

काष्ठा sdhci_omap_data अणु
	u32 offset;
	u8 flags;
पूर्ण;

काष्ठा sdhci_omap_host अणु
	अक्षर			*version;
	व्योम __iomem		*base;
	काष्ठा device		*dev;
	काष्ठा	regulator	*pbias;
	bool			pbias_enabled;
	काष्ठा sdhci_host	*host;
	u8			bus_mode;
	u8			घातer_mode;
	u8			timing;
	u8			flags;

	काष्ठा pinctrl		*pinctrl;
	काष्ठा pinctrl_state	**pinctrl_state;
	bool			is_tuning;
	/* Omap specअगरic context save */
	u32			con;
	u32			hctl;
	u32			sysctl;
	u32			capa;
पूर्ण;

अटल व्योम sdhci_omap_start_घड़ी(काष्ठा sdhci_omap_host *omap_host);
अटल व्योम sdhci_omap_stop_घड़ी(काष्ठा sdhci_omap_host *omap_host);

अटल अंतरभूत u32 sdhci_omap_पढ़ोl(काष्ठा sdhci_omap_host *host,
				   अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(host->base + offset);
पूर्ण

अटल अंतरभूत व्योम sdhci_omap_ग_लिखोl(काष्ठा sdhci_omap_host *host,
				     अचिन्हित पूर्णांक offset, u32 data)
अणु
	ग_लिखोl(data, host->base + offset);
पूर्ण

अटल पूर्णांक sdhci_omap_set_pbias(काष्ठा sdhci_omap_host *omap_host,
				bool घातer_on, अचिन्हित पूर्णांक iov)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = omap_host->dev;

	अगर (IS_ERR(omap_host->pbias))
		वापस 0;

	अगर (घातer_on) अणु
		ret = regulator_set_voltage(omap_host->pbias, iov, iov);
		अगर (ret) अणु
			dev_err(dev, "pbias set voltage failed\n");
			वापस ret;
		पूर्ण

		अगर (omap_host->pbias_enabled)
			वापस 0;

		ret = regulator_enable(omap_host->pbias);
		अगर (ret) अणु
			dev_err(dev, "pbias reg enable fail\n");
			वापस ret;
		पूर्ण

		omap_host->pbias_enabled = true;
	पूर्ण अन्यथा अणु
		अगर (!omap_host->pbias_enabled)
			वापस 0;

		ret = regulator_disable(omap_host->pbias);
		अगर (ret) अणु
			dev_err(dev, "pbias reg disable fail\n");
			वापस ret;
		पूर्ण
		omap_host->pbias_enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_omap_enable_iov(काष्ठा sdhci_omap_host *omap_host,
				 अचिन्हित पूर्णांक iov)
अणु
	पूर्णांक ret;
	काष्ठा sdhci_host *host = omap_host->host;
	काष्ठा mmc_host *mmc = host->mmc;

	ret = sdhci_omap_set_pbias(omap_host, false, 0);
	अगर (ret)
		वापस ret;

	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		ret = regulator_set_voltage(mmc->supply.vqmmc, iov, iov);
		अगर (ret) अणु
			dev_err(mmc_dev(mmc), "vqmmc set voltage failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = sdhci_omap_set_pbias(omap_host, true, iov);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम sdhci_omap_conf_bus_घातer(काष्ठा sdhci_omap_host *omap_host,
				      अचिन्हित अक्षर संकेत_voltage)
अणु
	u32 reg;
	kसमय_प्रकार समयout;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_HCTL);
	reg &= ~HCTL_SDVS_MASK;

	अगर (संकेत_voltage == MMC_SIGNAL_VOLTAGE_330)
		reg |= HCTL_SDVS_33;
	अन्यथा
		reg |= HCTL_SDVS_18;

	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_HCTL, reg);

	reg |= HCTL_SDBP;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_HCTL, reg);

	/* रुको 1ms */
	समयout = kसमय_add_ms(kसमय_get(), SDHCI_OMAP_TIMEOUT);
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		अगर (sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_HCTL) & HCTL_SDBP)
			अवरोध;
		अगर (WARN_ON(समयकरोut))
			वापस;
		usleep_range(5, 10);
	पूर्ण
पूर्ण

अटल व्योम sdhci_omap_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);
	u32 reg;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	अगर (enable)
		reg |= (CON_CTPL | CON_CLKEXTFREE);
	अन्यथा
		reg &= ~(CON_CTPL | CON_CLKEXTFREE);
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, reg);

	sdhci_enable_sdio_irq(mmc, enable);
पूर्ण

अटल अंतरभूत व्योम sdhci_omap_set_dll(काष्ठा sdhci_omap_host *omap_host,
				      पूर्णांक count)
अणु
	पूर्णांक i;
	u32 reg;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_DLL);
	reg |= DLL_FORCE_VALUE;
	reg &= ~DLL_FORCE_SR_C_MASK;
	reg |= (count << DLL_FORCE_SR_C_SHIFT);
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_DLL, reg);

	reg |= DLL_CALIB;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_DLL, reg);
	क्रम (i = 0; i < 1000; i++) अणु
		reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_DLL);
		अगर (reg & DLL_CALIB)
			अवरोध;
	पूर्ण
	reg &= ~DLL_CALIB;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_DLL, reg);
पूर्ण

अटल व्योम sdhci_omap_disable_tuning(काष्ठा sdhci_omap_host *omap_host)
अणु
	u32 reg;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_AC12);
	reg &= ~AC12_SCLK_SEL;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_AC12, reg);

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_DLL);
	reg &= ~(DLL_FORCE_VALUE | DLL_SWT);
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_DLL, reg);
पूर्ण

अटल पूर्णांक sdhci_omap_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा thermal_zone_device *thermal_dev;
	काष्ठा device *dev = omap_host->dev;
	काष्ठा mmc_ios *ios = &mmc->ios;
	u32 start_winकरोw = 0, max_winकरोw = 0;
	bool single_poपूर्णांक_failure = false;
	bool dcrc_was_enabled = false;
	u8 cur_match, prev_match = 0;
	u32 length = 0, max_len = 0;
	u32 phase_delay = 0;
	पूर्णांक temperature;
	पूर्णांक ret = 0;
	u32 reg;
	पूर्णांक i;

	/* घड़ी tuning is not needed क्रम upto 52MHz */
	अगर (ios->घड़ी <= 52000000)
		वापस 0;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CAPA2);
	अगर (ios->timing == MMC_TIMING_UHS_SDR50 && !(reg & CAPA2_TSDR50))
		वापस 0;

	thermal_dev = thermal_zone_get_zone_by_name("cpu_thermal");
	अगर (IS_ERR(thermal_dev)) अणु
		dev_err(dev, "Unable to get thermal zone for tuning\n");
		वापस PTR_ERR(thermal_dev);
	पूर्ण

	ret = thermal_zone_get_temp(thermal_dev, &temperature);
	अगर (ret)
		वापस ret;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_DLL);
	reg |= DLL_SWT;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_DLL, reg);

	/*
	 * OMAP5/DRA74X/DRA72x Errata i802:
	 * DCRC error पूर्णांकerrupts (MMCHS_STAT[21] DCRC=0x1) can occur
	 * during the tuning procedure. So disable it during the
	 * tuning procedure.
	 */
	अगर (host->ier & SDHCI_INT_DATA_CRC) अणु
		host->ier &= ~SDHCI_INT_DATA_CRC;
		dcrc_was_enabled = true;
	पूर्ण

	omap_host->is_tuning = true;

	/*
	 * Stage 1: Search क्रम a maximum pass winकरोw ignoring any
	 * any single poपूर्णांक failures. If the tuning value ends up
	 * near it, move away from it in stage 2 below
	 */
	जबतक (phase_delay <= MAX_PHASE_DELAY) अणु
		sdhci_omap_set_dll(omap_host, phase_delay);

		cur_match = !mmc_send_tuning(mmc, opcode, शून्य);
		अगर (cur_match) अणु
			अगर (prev_match) अणु
				length++;
			पूर्ण अन्यथा अगर (single_poपूर्णांक_failure) अणु
				/* ignore single poपूर्णांक failure */
				length++;
			पूर्ण अन्यथा अणु
				start_winकरोw = phase_delay;
				length = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			single_poपूर्णांक_failure = prev_match;
		पूर्ण

		अगर (length > max_len) अणु
			max_winकरोw = start_winकरोw;
			max_len = length;
		पूर्ण

		prev_match = cur_match;
		phase_delay += 4;
	पूर्ण

	अगर (!max_len) अणु
		dev_err(dev, "Unable to find match\n");
		ret = -EIO;
		जाओ tuning_error;
	पूर्ण

	/*
	 * Assign tuning value as a ratio of maximum pass winकरोw based
	 * on temperature
	 */
	अगर (temperature < -20000)
		phase_delay = min(max_winकरोw + 4 * (max_len - 1) - 24,
				  max_winकरोw +
				  DIV_ROUND_UP(13 * max_len, 16) * 4);
	अन्यथा अगर (temperature < 20000)
		phase_delay = max_winकरोw + DIV_ROUND_UP(9 * max_len, 16) * 4;
	अन्यथा अगर (temperature < 40000)
		phase_delay = max_winकरोw + DIV_ROUND_UP(8 * max_len, 16) * 4;
	अन्यथा अगर (temperature < 70000)
		phase_delay = max_winकरोw + DIV_ROUND_UP(7 * max_len, 16) * 4;
	अन्यथा अगर (temperature < 90000)
		phase_delay = max_winकरोw + DIV_ROUND_UP(5 * max_len, 16) * 4;
	अन्यथा अगर (temperature < 120000)
		phase_delay = max_winकरोw + DIV_ROUND_UP(4 * max_len, 16) * 4;
	अन्यथा
		phase_delay = max_winकरोw + DIV_ROUND_UP(3 * max_len, 16) * 4;

	/*
	 * Stage 2: Search क्रम a single poपूर्णांक failure near the chosen tuning
	 * value in two steps. First in the +3 to +10 range and then in the
	 * +2 to -10 range. If found, move away from it in the appropriate
	 * direction by the appropriate amount depending on the temperature.
	 */
	क्रम (i = 3; i <= 10; i++) अणु
		sdhci_omap_set_dll(omap_host, phase_delay + i);

		अगर (mmc_send_tuning(mmc, opcode, शून्य)) अणु
			अगर (temperature < 10000)
				phase_delay += i + 6;
			अन्यथा अगर (temperature < 20000)
				phase_delay += i - 12;
			अन्यथा अगर (temperature < 70000)
				phase_delay += i - 8;
			अन्यथा
				phase_delay += i - 6;

			जाओ single_failure_found;
		पूर्ण
	पूर्ण

	क्रम (i = 2; i >= -10; i--) अणु
		sdhci_omap_set_dll(omap_host, phase_delay + i);

		अगर (mmc_send_tuning(mmc, opcode, शून्य)) अणु
			अगर (temperature < 10000)
				phase_delay += i + 12;
			अन्यथा अगर (temperature < 20000)
				phase_delay += i + 8;
			अन्यथा अगर (temperature < 70000)
				phase_delay += i + 8;
			अन्यथा अगर (temperature < 90000)
				phase_delay += i + 10;
			अन्यथा
				phase_delay += i + 12;

			जाओ single_failure_found;
		पूर्ण
	पूर्ण

single_failure_found:
	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_AC12);
	अगर (!(reg & AC12_SCLK_SEL)) अणु
		ret = -EIO;
		जाओ tuning_error;
	पूर्ण

	sdhci_omap_set_dll(omap_host, phase_delay);

	omap_host->is_tuning = false;

	जाओ ret;

tuning_error:
	omap_host->is_tuning = false;
	dev_err(dev, "Tuning failed\n");
	sdhci_omap_disable_tuning(omap_host);

ret:
	sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
	/* Reenable क्रमbidden पूर्णांकerrupt */
	अगर (dcrc_was_enabled)
		host->ier |= SDHCI_INT_DATA_CRC;
	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_omap_card_busy(काष्ठा mmc_host *mmc)
अणु
	u32 reg, ac12;
	पूर्णांक ret = false;
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_omap_host *omap_host;
	u32 ier = host->ier;

	pltfm_host = sdhci_priv(host);
	omap_host = sdhci_pltfm_priv(pltfm_host);

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	ac12 = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_AC12);
	reg &= ~CON_CLKEXTFREE;
	अगर (ac12 & AC12_V1V8_SIGEN)
		reg |= CON_CLKEXTFREE;
	reg |= CON_PADEN;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, reg);

	disable_irq(host->irq);
	ier |= SDHCI_INT_CARD_INT;
	sdhci_ग_लिखोl(host, ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, ier, SDHCI_SIGNAL_ENABLE);

	/*
	 * Delay is required क्रम PSTATE to correctly reflect
	 * DLEV/CLEV values after PADEN is set.
	 */
	usleep_range(50, 100);
	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_PSTATE);
	अगर ((reg & PSTATE_DATI) || !(reg & PSTATE_DLEV_DAT0))
		ret = true;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	reg &= ~(CON_CLKEXTFREE | CON_PADEN);
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, reg);

	sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
	enable_irq(host->irq);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_omap_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
						  काष्ठा mmc_ios *ios)
अणु
	u32 reg;
	पूर्णांक ret;
	अचिन्हित पूर्णांक iov;
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_omap_host *omap_host;
	काष्ठा device *dev;

	pltfm_host = sdhci_priv(host);
	omap_host = sdhci_pltfm_priv(pltfm_host);
	dev = omap_host->dev;

	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_330) अणु
		reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CAPA);
		अगर (!(reg & CAPA_VS33))
			वापस -EOPNOTSUPP;

		sdhci_omap_conf_bus_घातer(omap_host, ios->संकेत_voltage);

		reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_AC12);
		reg &= ~AC12_V1V8_SIGEN;
		sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_AC12, reg);

		iov = IOV_3V3;
	पूर्ण अन्यथा अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_180) अणु
		reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CAPA);
		अगर (!(reg & CAPA_VS18))
			वापस -EOPNOTSUPP;

		sdhci_omap_conf_bus_घातer(omap_host, ios->संकेत_voltage);

		reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_AC12);
		reg |= AC12_V1V8_SIGEN;
		sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_AC12, reg);

		iov = IOV_1V8;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = sdhci_omap_enable_iov(omap_host, iov);
	अगर (ret) अणु
		dev_err(dev, "failed to switch IO voltage to %dmV\n", iov);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "IO voltage switched to %dmV\n", iov);
	वापस 0;
पूर्ण

अटल व्योम sdhci_omap_set_timing(काष्ठा sdhci_omap_host *omap_host, u8 timing)
अणु
	पूर्णांक ret;
	काष्ठा pinctrl_state *pinctrl_state;
	काष्ठा device *dev = omap_host->dev;

	अगर (!(omap_host->flags & SDHCI_OMAP_REQUIRE_IODELAY))
		वापस;

	अगर (omap_host->timing == timing)
		वापस;

	sdhci_omap_stop_घड़ी(omap_host);

	pinctrl_state = omap_host->pinctrl_state[timing];
	ret = pinctrl_select_state(omap_host->pinctrl, pinctrl_state);
	अगर (ret) अणु
		dev_err(dev, "failed to select pinctrl state\n");
		वापस;
	पूर्ण

	sdhci_omap_start_घड़ी(omap_host);
	omap_host->timing = timing;
पूर्ण

अटल व्योम sdhci_omap_set_घातer_mode(काष्ठा sdhci_omap_host *omap_host,
				      u8 घातer_mode)
अणु
	अगर (omap_host->bus_mode == MMC_POWER_OFF)
		sdhci_omap_disable_tuning(omap_host);
	omap_host->घातer_mode = घातer_mode;
पूर्ण

अटल व्योम sdhci_omap_set_bus_mode(काष्ठा sdhci_omap_host *omap_host,
				    अचिन्हित पूर्णांक mode)
अणु
	u32 reg;

	अगर (omap_host->bus_mode == mode)
		वापस;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	अगर (mode == MMC_BUSMODE_OPENDRAIN)
		reg |= CON_OD;
	अन्यथा
		reg &= ~CON_OD;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, reg);

	omap_host->bus_mode = mode;
पूर्ण

अटल व्योम sdhci_omap_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_omap_host *omap_host;

	pltfm_host = sdhci_priv(host);
	omap_host = sdhci_pltfm_priv(pltfm_host);

	sdhci_omap_set_bus_mode(omap_host, ios->bus_mode);
	sdhci_omap_set_timing(omap_host, ios->timing);
	sdhci_set_ios(mmc, ios);
	sdhci_omap_set_घातer_mode(omap_host, ios->घातer_mode);
पूर्ण

अटल u16 sdhci_omap_calc_भागisor(काष्ठा sdhci_pltfm_host *host,
				   अचिन्हित पूर्णांक घड़ी)
अणु
	u16 dsor;

	dsor = DIV_ROUND_UP(clk_get_rate(host->clk), घड़ी);
	अगर (dsor > SYSCTL_CLKD_MAX)
		dsor = SYSCTL_CLKD_MAX;

	वापस dsor;
पूर्ण

अटल व्योम sdhci_omap_start_घड़ी(काष्ठा sdhci_omap_host *omap_host)
अणु
	u32 reg;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_SYSCTL);
	reg |= SYSCTL_CEN;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_SYSCTL, reg);
पूर्ण

अटल व्योम sdhci_omap_stop_घड़ी(काष्ठा sdhci_omap_host *omap_host)
अणु
	u32 reg;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_SYSCTL);
	reg &= ~SYSCTL_CEN;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_SYSCTL, reg);
पूर्ण

अटल व्योम sdhci_omap_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);
	अचिन्हित दीर्घ clkभाग;

	sdhci_omap_stop_घड़ी(omap_host);

	अगर (!घड़ी)
		वापस;

	clkभाग = sdhci_omap_calc_भागisor(pltfm_host, घड़ी);
	clkभाग = (clkभाग & SYSCTL_CLKD_MASK) << SYSCTL_CLKD_SHIFT;
	sdhci_enable_clk(host, clkभाग);

	sdhci_omap_start_घड़ी(omap_host);
पूर्ण

अटल व्योम sdhci_omap_set_घातer(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
			  अचिन्हित लघु vdd)
अणु
	काष्ठा mmc_host *mmc = host->mmc;

	mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);
पूर्ण

अटल पूर्णांक sdhci_omap_enable_dma(काष्ठा sdhci_host *host)
अणु
	u32 reg;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	reg &= ~CON_DMA_MASTER;
	/* Switch to DMA slave mode when using बाह्यal DMA */
	अगर (!host->use_बाह्यal_dma)
		reg |= CON_DMA_MASTER;

	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, reg);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_omap_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	वापस clk_get_rate(pltfm_host->clk) / SYSCTL_CLKD_MAX;
पूर्ण

अटल व्योम sdhci_omap_set_bus_width(काष्ठा sdhci_host *host, पूर्णांक width)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);
	u32 reg;

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	अगर (width == MMC_BUS_WIDTH_8)
		reg |= CON_DW8;
	अन्यथा
		reg &= ~CON_DW8;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, reg);

	sdhci_set_bus_width(host, width);
पूर्ण

अटल व्योम sdhci_omap_init_74_घड़ीs(काष्ठा sdhci_host *host, u8 घातer_mode)
अणु
	u32 reg;
	kसमय_प्रकार समयout;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);

	अगर (omap_host->घातer_mode == घातer_mode)
		वापस;

	अगर (घातer_mode != MMC_POWER_ON)
		वापस;

	disable_irq(host->irq);

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	reg |= CON_INIT;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, reg);
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CMD, 0x0);

	/* रुको 1ms */
	समयout = kसमय_add_ms(kसमय_get(), SDHCI_OMAP_TIMEOUT);
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		अगर (sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_STAT) & INT_CC_EN)
			अवरोध;
		अगर (WARN_ON(समयकरोut))
			वापस;
		usleep_range(5, 10);
	पूर्ण

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	reg &= ~CON_INIT;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, reg);
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_STAT, INT_CC_EN);

	enable_irq(host->irq);
पूर्ण

अटल व्योम sdhci_omap_set_uhs_संकेतing(काष्ठा sdhci_host *host,
					 अचिन्हित पूर्णांक timing)
अणु
	u32 reg;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);

	sdhci_omap_stop_घड़ी(omap_host);

	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	अगर (timing == MMC_TIMING_UHS_DDR50 || timing == MMC_TIMING_MMC_DDR52)
		reg |= CON_DDR;
	अन्यथा
		reg &= ~CON_DDR;
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, reg);

	sdhci_set_uhs_संकेतing(host, timing);
	sdhci_omap_start_घड़ी(omap_host);
पूर्ण

#घोषणा MMC_TIMEOUT_US		20000		/* 20000 micro Sec */
अटल व्योम sdhci_omap_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);
	अचिन्हित दीर्घ limit = MMC_TIMEOUT_US;
	अचिन्हित दीर्घ i = 0;

	/* Don't reset data lines during tuning operation */
	अगर (omap_host->is_tuning)
		mask &= ~SDHCI_RESET_DATA;

	अगर (omap_host->flags & SDHCI_OMAP_SPECIAL_RESET) अणु
		sdhci_ग_लिखोb(host, mask, SDHCI_SOFTWARE_RESET);
		जबतक ((!(sdhci_पढ़ोb(host, SDHCI_SOFTWARE_RESET) & mask)) &&
		       (i++ < limit))
			udelay(1);
		i = 0;
		जबतक ((sdhci_पढ़ोb(host, SDHCI_SOFTWARE_RESET) & mask) &&
		       (i++ < limit))
			udelay(1);

		अगर (sdhci_पढ़ोb(host, SDHCI_SOFTWARE_RESET) & mask)
			dev_err(mmc_dev(host->mmc),
				"Timeout waiting on controller reset in %s\n",
				__func__);
		वापस;
	पूर्ण

	sdhci_reset(host, mask);
पूर्ण

#घोषणा CMD_ERR_MASK (SDHCI_INT_CRC | SDHCI_INT_END_BIT | SDHCI_INT_INDEX |\
		      SDHCI_INT_TIMEOUT)
#घोषणा CMD_MASK (CMD_ERR_MASK | SDHCI_INT_RESPONSE)

अटल u32 sdhci_omap_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);

	अगर (omap_host->is_tuning && host->cmd && !host->data_early &&
	    (पूर्णांकmask & CMD_ERR_MASK)) अणु

		/*
		 * Since we are not resetting data lines during tuning
		 * operation, data error or data complete पूर्णांकerrupts
		 * might still arrive. Mark this request as a failure
		 * but still रुको क्रम the data पूर्णांकerrupt
		 */
		अगर (पूर्णांकmask & SDHCI_INT_TIMEOUT)
			host->cmd->error = -ETIMEDOUT;
		अन्यथा
			host->cmd->error = -EILSEQ;

		host->cmd = शून्य;

		/*
		 * Someबार command error पूर्णांकerrupts and command complete
		 * पूर्णांकerrupt will arrive together. Clear all command related
		 * पूर्णांकerrupts here.
		 */
		sdhci_ग_लिखोl(host, पूर्णांकmask & CMD_MASK, SDHCI_INT_STATUS);
		पूर्णांकmask &= ~CMD_MASK;
	पूर्ण

	वापस पूर्णांकmask;
पूर्ण

अटल व्योम sdhci_omap_set_समयout(काष्ठा sdhci_host *host,
				   काष्ठा mmc_command *cmd)
अणु
	अगर (cmd->opcode == MMC_ERASE)
		sdhci_set_data_समयout_irq(host, false);

	__sdhci_set_समयout(host, cmd);
पूर्ण

अटल काष्ठा sdhci_ops sdhci_omap_ops = अणु
	.set_घड़ी = sdhci_omap_set_घड़ी,
	.set_घातer = sdhci_omap_set_घातer,
	.enable_dma = sdhci_omap_enable_dma,
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.get_min_घड़ी = sdhci_omap_get_min_घड़ी,
	.set_bus_width = sdhci_omap_set_bus_width,
	.platक्रमm_send_init_74_घड़ीs = sdhci_omap_init_74_घड़ीs,
	.reset = sdhci_omap_reset,
	.set_uhs_संकेतing = sdhci_omap_set_uhs_संकेतing,
	.irq = sdhci_omap_irq,
	.set_समयout = sdhci_omap_set_समयout,
पूर्ण;

अटल पूर्णांक sdhci_omap_set_capabilities(काष्ठा sdhci_omap_host *omap_host)
अणु
	u32 reg;
	पूर्णांक ret = 0;
	काष्ठा device *dev = omap_host->dev;
	काष्ठा regulator *vqmmc;

	vqmmc = regulator_get(dev, "vqmmc");
	अगर (IS_ERR(vqmmc)) अणु
		ret = PTR_ERR(vqmmc);
		जाओ reg_put;
	पूर्ण

	/* voltage capabilities might be set by boot loader, clear it */
	reg = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CAPA);
	reg &= ~(CAPA_VS18 | CAPA_VS30 | CAPA_VS33);

	अगर (regulator_is_supported_voltage(vqmmc, IOV_3V3, IOV_3V3))
		reg |= CAPA_VS33;
	अगर (regulator_is_supported_voltage(vqmmc, IOV_1V8, IOV_1V8))
		reg |= CAPA_VS18;

	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CAPA, reg);

reg_put:
	regulator_put(vqmmc);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_omap_pdata = अणु
	.quirks = SDHCI_QUIRK_BROKEN_CARD_DETECTION |
		  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN |
		  SDHCI_QUIRK_NO_HISPD_BIT |
		  SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC,
	.quirks2 = SDHCI_QUIRK2_ACMD23_BROKEN |
		   SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
		   SDHCI_QUIRK2_RSP_136_HAS_CRC |
		   SDHCI_QUIRK2_DISABLE_HW_TIMEOUT,
	.ops = &sdhci_omap_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_omap_data k2g_data = अणु
	.offset = 0x200,
पूर्ण;

अटल स्थिर काष्ठा sdhci_omap_data am335_data = अणु
	.offset = 0x200,
	.flags = SDHCI_OMAP_SPECIAL_RESET,
पूर्ण;

अटल स्थिर काष्ठा sdhci_omap_data am437_data = अणु
	.offset = 0x200,
	.flags = SDHCI_OMAP_SPECIAL_RESET,
पूर्ण;

अटल स्थिर काष्ठा sdhci_omap_data dra7_data = अणु
	.offset = 0x200,
	.flags	= SDHCI_OMAP_REQUIRE_IODELAY,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_sdhci_match[] = अणु
	अणु .compatible = "ti,dra7-sdhci", .data = &dra7_data पूर्ण,
	अणु .compatible = "ti,k2g-sdhci", .data = &k2g_data पूर्ण,
	अणु .compatible = "ti,am335-sdhci", .data = &am335_data पूर्ण,
	अणु .compatible = "ti,am437-sdhci", .data = &am437_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_sdhci_match);

अटल काष्ठा pinctrl_state
*sdhci_omap_iodelay_pinctrl_state(काष्ठा sdhci_omap_host *omap_host, अक्षर *mode,
				  u32 *caps, u32 capmask)
अणु
	काष्ठा device *dev = omap_host->dev;
	अक्षर *version = omap_host->version;
	काष्ठा pinctrl_state *pinctrl_state = ERR_PTR(-ENODEV);
	अक्षर str[20];

	अगर (!(*caps & capmask))
		जाओ ret;

	अगर (version) अणु
		snम_लिखो(str, 20, "%s-%s", mode, version);
		pinctrl_state = pinctrl_lookup_state(omap_host->pinctrl, str);
	पूर्ण

	अगर (IS_ERR(pinctrl_state))
		pinctrl_state = pinctrl_lookup_state(omap_host->pinctrl, mode);

	अगर (IS_ERR(pinctrl_state)) अणु
		dev_err(dev, "no pinctrl state for %s mode", mode);
		*caps &= ~capmask;
	पूर्ण

ret:
	वापस pinctrl_state;
पूर्ण

अटल पूर्णांक sdhci_omap_config_iodelay_pinctrl_state(काष्ठा sdhci_omap_host
						   *omap_host)
अणु
	काष्ठा device *dev = omap_host->dev;
	काष्ठा sdhci_host *host = omap_host->host;
	काष्ठा mmc_host *mmc = host->mmc;
	u32 *caps = &mmc->caps;
	u32 *caps2 = &mmc->caps2;
	काष्ठा pinctrl_state *state;
	काष्ठा pinctrl_state **pinctrl_state;

	अगर (!(omap_host->flags & SDHCI_OMAP_REQUIRE_IODELAY))
		वापस 0;

	pinctrl_state = devm_kसुस्मृति(dev,
				     MMC_TIMING_MMC_HS200 + 1,
				     माप(*pinctrl_state),
				     GFP_KERNEL);
	अगर (!pinctrl_state)
		वापस -ENOMEM;

	omap_host->pinctrl = devm_pinctrl_get(omap_host->dev);
	अगर (IS_ERR(omap_host->pinctrl)) अणु
		dev_err(dev, "Cannot get pinctrl\n");
		वापस PTR_ERR(omap_host->pinctrl);
	पूर्ण

	state = pinctrl_lookup_state(omap_host->pinctrl, "default");
	अगर (IS_ERR(state)) अणु
		dev_err(dev, "no pinctrl state for default mode\n");
		वापस PTR_ERR(state);
	पूर्ण
	pinctrl_state[MMC_TIMING_LEGACY] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "sdr104", caps,
						 MMC_CAP_UHS_SDR104);
	अगर (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_SDR104] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "ddr50", caps,
						 MMC_CAP_UHS_DDR50);
	अगर (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_DDR50] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "sdr50", caps,
						 MMC_CAP_UHS_SDR50);
	अगर (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_SDR50] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "sdr25", caps,
						 MMC_CAP_UHS_SDR25);
	अगर (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_SDR25] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "sdr12", caps,
						 MMC_CAP_UHS_SDR12);
	अगर (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_UHS_SDR12] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "ddr_1_8v", caps,
						 MMC_CAP_1_8V_DDR);
	अगर (!IS_ERR(state)) अणु
		pinctrl_state[MMC_TIMING_MMC_DDR52] = state;
	पूर्ण अन्यथा अणु
		state = sdhci_omap_iodelay_pinctrl_state(omap_host, "ddr_3_3v",
							 caps,
							 MMC_CAP_3_3V_DDR);
		अगर (!IS_ERR(state))
			pinctrl_state[MMC_TIMING_MMC_DDR52] = state;
	पूर्ण

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "hs", caps,
						 MMC_CAP_SD_HIGHSPEED);
	अगर (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_SD_HS] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "hs", caps,
						 MMC_CAP_MMC_HIGHSPEED);
	अगर (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_MMC_HS] = state;

	state = sdhci_omap_iodelay_pinctrl_state(omap_host, "hs200_1_8v", caps2,
						 MMC_CAP2_HS200_1_8V_SDR);
	अगर (!IS_ERR(state))
		pinctrl_state[MMC_TIMING_MMC_HS200] = state;

	omap_host->pinctrl_state = pinctrl_state;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा soc_device_attribute sdhci_omap_soc_devices[] = अणु
	अणु
		.machine = "DRA7[45]*",
		.revision = "ES1.[01]",
	पूर्ण,
	अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक sdhci_omap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	u32 offset;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_omap_host *omap_host;
	काष्ठा mmc_host *mmc;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा sdhci_omap_data *data;
	स्थिर काष्ठा soc_device_attribute *soc;
	काष्ठा resource *regs;

	match = of_match_device(omap_sdhci_match, dev);
	अगर (!match)
		वापस -EINVAL;

	data = (काष्ठा sdhci_omap_data *)match->data;
	अगर (!data) अणु
		dev_err(dev, "no sdhci omap data\n");
		वापस -EINVAL;
	पूर्ण
	offset = data->offset;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs)
		वापस -ENXIO;

	host = sdhci_pltfm_init(pdev, &sdhci_omap_pdata,
				माप(*omap_host));
	अगर (IS_ERR(host)) अणु
		dev_err(dev, "Failed sdhci_pltfm_init\n");
		वापस PTR_ERR(host);
	पूर्ण

	pltfm_host = sdhci_priv(host);
	omap_host = sdhci_pltfm_priv(pltfm_host);
	omap_host->host = host;
	omap_host->base = host->ioaddr;
	omap_host->dev = dev;
	omap_host->घातer_mode = MMC_POWER_UNDEFINED;
	omap_host->timing = MMC_TIMING_LEGACY;
	omap_host->flags = data->flags;
	host->ioaddr += offset;
	host->mapbase = regs->start + offset;

	mmc = host->mmc;
	sdhci_get_of_property(pdev);
	ret = mmc_of_parse(mmc);
	अगर (ret)
		जाओ err_pltfm_मुक्त;

	soc = soc_device_match(sdhci_omap_soc_devices);
	अगर (soc) अणु
		omap_host->version = "rev11";
		अगर (!म_भेद(dev_name(dev), "4809c000.mmc"))
			mmc->f_max = 96000000;
		अगर (!म_भेद(dev_name(dev), "480b4000.mmc"))
			mmc->f_max = 48000000;
		अगर (!म_भेद(dev_name(dev), "480ad000.mmc"))
			mmc->f_max = 48000000;
	पूर्ण

	अगर (!mmc_can_gpio_ro(mmc))
		mmc->caps2 |= MMC_CAP2_NO_WRITE_PROTECT;

	pltfm_host->clk = devm_clk_get(dev, "fck");
	अगर (IS_ERR(pltfm_host->clk)) अणु
		ret = PTR_ERR(pltfm_host->clk);
		जाओ err_pltfm_मुक्त;
	पूर्ण

	ret = clk_set_rate(pltfm_host->clk, mmc->f_max);
	अगर (ret) अणु
		dev_err(dev, "failed to set clock to %d\n", mmc->f_max);
		जाओ err_pltfm_मुक्त;
	पूर्ण

	omap_host->pbias = devm_regulator_get_optional(dev, "pbias");
	अगर (IS_ERR(omap_host->pbias)) अणु
		ret = PTR_ERR(omap_host->pbias);
		अगर (ret != -ENODEV)
			जाओ err_pltfm_मुक्त;
		dev_dbg(dev, "unable to get pbias regulator %d\n", ret);
	पूर्ण
	omap_host->pbias_enabled = false;

	/*
	 * omap_device_pm_करोमुख्य has callbacks to enable the मुख्य
	 * functional घड़ी, पूर्णांकerface घड़ी and also configure the
	 * SYSCONFIG रेजिस्टर of omap devices. The callback will be invoked
	 * as part of pm_runसमय_get_sync.
	 */
	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed\n");
		pm_runसमय_put_noidle(dev);
		जाओ err_rpm_disable;
	पूर्ण

	ret = sdhci_omap_set_capabilities(omap_host);
	अगर (ret) अणु
		dev_err(dev, "failed to set system capabilities\n");
		जाओ err_put_sync;
	पूर्ण

	host->mmc_host_ops.start_संकेत_voltage_चयन =
					sdhci_omap_start_संकेत_voltage_चयन;
	host->mmc_host_ops.set_ios = sdhci_omap_set_ios;
	host->mmc_host_ops.card_busy = sdhci_omap_card_busy;
	host->mmc_host_ops.execute_tuning = sdhci_omap_execute_tuning;
	host->mmc_host_ops.enable_sdio_irq = sdhci_omap_enable_sdio_irq;

	/* Switch to बाह्यal DMA only अगर there is the "dmas" property */
	अगर (of_find_property(dev->of_node, "dmas", शून्य))
		sdhci_चयन_बाह्यal_dma(host, true);

	/* R1B responses is required to properly manage HW busy detection. */
	mmc->caps |= MMC_CAP_NEED_RSP_BUSY;

	ret = sdhci_setup_host(host);
	अगर (ret)
		जाओ err_put_sync;

	ret = sdhci_omap_config_iodelay_pinctrl_state(omap_host);
	अगर (ret)
		जाओ err_cleanup_host;

	ret = __sdhci_add_host(host);
	अगर (ret)
		जाओ err_cleanup_host;

	वापस 0;

err_cleanup_host:
	sdhci_cleanup_host(host);

err_put_sync:
	pm_runसमय_put_sync(dev);

err_rpm_disable:
	pm_runसमय_disable(dev);

err_pltfm_मुक्त:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_omap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);

	sdhci_हटाओ_host(host, true);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण
#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम sdhci_omap_context_save(काष्ठा sdhci_omap_host *omap_host)
अणु
	omap_host->con = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CON);
	omap_host->hctl = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_HCTL);
	omap_host->capa = sdhci_omap_पढ़ोl(omap_host, SDHCI_OMAP_CAPA);
पूर्ण

अटल व्योम sdhci_omap_context_restore(काष्ठा sdhci_omap_host *omap_host)
अणु
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CON, omap_host->con);
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_HCTL, omap_host->hctl);
	sdhci_omap_ग_लिखोl(omap_host, SDHCI_OMAP_CAPA, omap_host->capa);
पूर्ण

अटल पूर्णांक __maybe_unused sdhci_omap_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);

	sdhci_suspend_host(host);

	sdhci_omap_context_save(omap_host);

	pinctrl_pm_select_idle_state(dev);

	pm_runसमय_क्रमce_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sdhci_omap_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);

	pm_runसमय_क्रमce_resume(dev);

	pinctrl_pm_select_शेष_state(dev);

	sdhci_omap_context_restore(omap_host);

	sdhci_resume_host(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(sdhci_omap_dev_pm_ops, sdhci_omap_suspend,
			 sdhci_omap_resume);

अटल काष्ठा platक्रमm_driver sdhci_omap_driver = अणु
	.probe = sdhci_omap_probe,
	.हटाओ = sdhci_omap_हटाओ,
	.driver = अणु
		   .name = "sdhci-omap",
		   .probe_type = PROBE_PREFER_ASYNCHRONOUS,
		   .pm = &sdhci_omap_dev_pm_ops,
		   .of_match_table = omap_sdhci_match,
		  पूर्ण,
पूर्ण;

module_platक्रमm_driver(sdhci_omap_driver);

MODULE_DESCRIPTION("SDHCI driver for OMAP SoCs");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sdhci_omap");
