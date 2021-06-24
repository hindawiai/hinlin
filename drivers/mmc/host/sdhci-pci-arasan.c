<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sdhci-pci-arasan.c - Driver क्रम Arasan PCI Controller with
 * पूर्णांकegrated phy.
 *
 * Copyright (C) 2017 Arasan Chip Systems Inc.
 *
 * Author: Atul Garg <agarg@arasan.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#समावेश "sdhci.h"
#समावेश "sdhci-pci.h"

/* Extra रेजिस्टरs क्रम Arasan SD/SDIO/MMC Host Controller with PHY */
#घोषणा PHY_ADDR_REG	0x300
#घोषणा PHY_DAT_REG	0x304

#घोषणा PHY_WRITE	BIT(8)
#घोषणा PHY_BUSY	BIT(9)
#घोषणा DATA_MASK	0xFF

/* PHY Specअगरic Registers */
#घोषणा DLL_STATUS	0x00
#घोषणा IPAD_CTRL1	0x01
#घोषणा IPAD_CTRL2	0x02
#घोषणा IPAD_STS	0x03
#घोषणा IOREN_CTRL1	0x06
#घोषणा IOREN_CTRL2	0x07
#घोषणा IOPU_CTRL1	0x08
#घोषणा IOPU_CTRL2	0x09
#घोषणा ITAP_DELAY	0x0C
#घोषणा OTAP_DELAY	0x0D
#घोषणा STRB_SEL	0x0E
#घोषणा CLKBUF_SEL	0x0F
#घोषणा MODE_CTRL	0x11
#घोषणा DLL_TRIM	0x12
#घोषणा CMD_CTRL	0x20
#घोषणा DATA_CTRL	0x21
#घोषणा STRB_CTRL	0x22
#घोषणा CLK_CTRL	0x23
#घोषणा PHY_CTRL	0x24

#घोषणा DLL_ENBL	BIT(3)
#घोषणा RTRIM_EN	BIT(1)
#घोषणा PDB_ENBL	BIT(1)
#घोषणा RETB_ENBL	BIT(6)
#घोषणा ODEN_CMD	BIT(1)
#घोषणा ODEN_DAT	0xFF
#घोषणा REN_STRB	BIT(0)
#घोषणा REN_CMND	BIT(1)
#घोषणा REN_DATA	0xFF
#घोषणा PU_CMD		BIT(1)
#घोषणा PU_DAT		0xFF
#घोषणा ITAPDLY_EN	BIT(0)
#घोषणा OTAPDLY_EN	BIT(0)
#घोषणा OD_REL_CMD	BIT(1)
#घोषणा OD_REL_DAT	0xFF
#घोषणा DLLTRM_ICP	0x8
#घोषणा PDB_CMND	BIT(0)
#घोषणा PDB_DATA	0xFF
#घोषणा PDB_STRB	BIT(0)
#घोषणा PDB_CLOCK	BIT(0)
#घोषणा CALDONE_MASK	0x10
#घोषणा DLL_RDY_MASK	0x10
#घोषणा MAX_CLK_BUF	0x7

/* Mode Controls */
#घोषणा ENHSTRB_MODE	BIT(0)
#घोषणा HS400_MODE	BIT(1)
#घोषणा LEGACY_MODE	BIT(2)
#घोषणा DDR50_MODE	BIT(3)

/*
 * Controller has no specअगरic bits क्रम HS200/HS.
 * Used BIT(4), BIT(5) क्रम software programming.
 */
#घोषणा HS200_MODE	BIT(4)
#घोषणा HISPD_MODE	BIT(5)

#घोषणा OTAPDLY(x)	(((x) << 1) | OTAPDLY_EN)
#घोषणा ITAPDLY(x)	(((x) << 1) | ITAPDLY_EN)
#घोषणा FREQSEL(x)	(((x) << 5) | DLL_ENBL)
#घोषणा IOPAD(x, y)	((x) | ((y) << 2))

/* Arasan निजी data */
काष्ठा arasan_host अणु
	u32 chg_clk;
पूर्ण;

अटल पूर्णांक arasan_phy_addr_poll(काष्ठा sdhci_host *host, u32 offset, u32 mask)
अणु
	kसमय_प्रकार समयout = kसमय_add_us(kसमय_get(), 100);
	bool failed;
	u8 val = 0;

	जबतक (1) अणु
		failed = kसमय_after(kसमय_get(), समयout);
		val = sdhci_पढ़ोw(host, PHY_ADDR_REG);
		अगर (!(val & mask))
			वापस 0;
		अगर (failed)
			वापस -EBUSY;
	पूर्ण
पूर्ण

अटल पूर्णांक arasan_phy_ग_लिखो(काष्ठा sdhci_host *host, u8 data, u8 offset)
अणु
	sdhci_ग_लिखोw(host, data, PHY_DAT_REG);
	sdhci_ग_लिखोw(host, (PHY_WRITE | offset), PHY_ADDR_REG);
	वापस arasan_phy_addr_poll(host, PHY_ADDR_REG, PHY_BUSY);
पूर्ण

अटल पूर्णांक arasan_phy_पढ़ो(काष्ठा sdhci_host *host, u8 offset, u8 *data)
अणु
	पूर्णांक ret;

	sdhci_ग_लिखोw(host, 0, PHY_DAT_REG);
	sdhci_ग_लिखोw(host, offset, PHY_ADDR_REG);
	ret = arasan_phy_addr_poll(host, PHY_ADDR_REG, PHY_BUSY);

	/* Masking valid data bits */
	*data = sdhci_पढ़ोw(host, PHY_DAT_REG) & DATA_MASK;
	वापस ret;
पूर्ण

अटल पूर्णांक arasan_phy_sts_poll(काष्ठा sdhci_host *host, u32 offset, u32 mask)
अणु
	पूर्णांक ret;
	kसमय_प्रकार समयout = kसमय_add_us(kसमय_get(), 100);
	bool failed;
	u8 val = 0;

	जबतक (1) अणु
		failed = kसमय_after(kसमय_get(), समयout);
		ret = arasan_phy_पढ़ो(host, offset, &val);
		अगर (ret)
			वापस -EBUSY;
		अन्यथा अगर (val & mask)
			वापस 0;
		अगर (failed)
			वापस -EBUSY;
	पूर्ण
पूर्ण

/* Initialize the Arasan PHY */
अटल पूर्णांक arasan_phy_init(काष्ठा sdhci_host *host)
अणु
	पूर्णांक ret;
	u8 val;

	/* Program IOPADs and रुको क्रम calibration to be करोne */
	अगर (arasan_phy_पढ़ो(host, IPAD_CTRL1, &val) ||
	    arasan_phy_ग_लिखो(host, val | RETB_ENBL | PDB_ENBL, IPAD_CTRL1) ||
	    arasan_phy_पढ़ो(host, IPAD_CTRL2, &val) ||
	    arasan_phy_ग_लिखो(host, val | RTRIM_EN, IPAD_CTRL2))
		वापस -EBUSY;
	ret = arasan_phy_sts_poll(host, IPAD_STS, CALDONE_MASK);
	अगर (ret)
		वापस -EBUSY;

	/* Program CMD/Data lines */
	अगर (arasan_phy_पढ़ो(host, IOREN_CTRL1, &val) ||
	    arasan_phy_ग_लिखो(host, val | REN_CMND | REN_STRB, IOREN_CTRL1) ||
	    arasan_phy_पढ़ो(host, IOPU_CTRL1, &val) ||
	    arasan_phy_ग_लिखो(host, val | PU_CMD, IOPU_CTRL1) ||
	    arasan_phy_पढ़ो(host, CMD_CTRL, &val) ||
	    arasan_phy_ग_लिखो(host, val | PDB_CMND, CMD_CTRL) ||
	    arasan_phy_पढ़ो(host, IOREN_CTRL2, &val) ||
	    arasan_phy_ग_लिखो(host, val | REN_DATA, IOREN_CTRL2) ||
	    arasan_phy_पढ़ो(host, IOPU_CTRL2, &val) ||
	    arasan_phy_ग_लिखो(host, val | PU_DAT, IOPU_CTRL2) ||
	    arasan_phy_पढ़ो(host, DATA_CTRL, &val) ||
	    arasan_phy_ग_लिखो(host, val | PDB_DATA, DATA_CTRL) ||
	    arasan_phy_पढ़ो(host, STRB_CTRL, &val) ||
	    arasan_phy_ग_लिखो(host, val | PDB_STRB, STRB_CTRL) ||
	    arasan_phy_पढ़ो(host, CLK_CTRL, &val) ||
	    arasan_phy_ग_लिखो(host, val | PDB_CLOCK, CLK_CTRL) ||
	    arasan_phy_पढ़ो(host, CLKBUF_SEL, &val) ||
	    arasan_phy_ग_लिखो(host, val | MAX_CLK_BUF, CLKBUF_SEL) ||
	    arasan_phy_ग_लिखो(host, LEGACY_MODE, MODE_CTRL))
		वापस -EBUSY;
	वापस 0;
पूर्ण

/* Set Arasan PHY क्रम dअगरferent modes */
अटल पूर्णांक arasan_phy_set(काष्ठा sdhci_host *host, u8 mode, u8 otap,
			  u8 drv_type, u8 itap, u8 trim, u8 clk)
अणु
	u8 val;
	पूर्णांक ret;

	अगर (mode == HISPD_MODE || mode == HS200_MODE)
		ret = arasan_phy_ग_लिखो(host, 0x0, MODE_CTRL);
	अन्यथा
		ret = arasan_phy_ग_लिखो(host, mode, MODE_CTRL);
	अगर (ret)
		वापस ret;
	अगर (mode == HS400_MODE || mode == HS200_MODE) अणु
		ret = arasan_phy_पढ़ो(host, IPAD_CTRL1, &val);
		अगर (ret)
			वापस ret;
		ret = arasan_phy_ग_लिखो(host, IOPAD(val, drv_type), IPAD_CTRL1);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (mode == LEGACY_MODE) अणु
		ret = arasan_phy_ग_लिखो(host, 0x0, OTAP_DELAY);
		अगर (ret)
			वापस ret;
		ret = arasan_phy_ग_लिखो(host, 0x0, ITAP_DELAY);
	पूर्ण अन्यथा अणु
		ret = arasan_phy_ग_लिखो(host, OTAPDLY(otap), OTAP_DELAY);
		अगर (ret)
			वापस ret;
		अगर (mode != HS200_MODE)
			ret = arasan_phy_ग_लिखो(host, ITAPDLY(itap), ITAP_DELAY);
		अन्यथा
			ret = arasan_phy_ग_लिखो(host, 0x0, ITAP_DELAY);
	पूर्ण
	अगर (ret)
		वापस ret;
	अगर (mode != LEGACY_MODE) अणु
		ret = arasan_phy_ग_लिखो(host, trim, DLL_TRIM);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = arasan_phy_ग_लिखो(host, 0, DLL_STATUS);
	अगर (ret)
		वापस ret;
	अगर (mode != LEGACY_MODE) अणु
		ret = arasan_phy_ग_लिखो(host, FREQSEL(clk), DLL_STATUS);
		अगर (ret)
			वापस ret;
		ret = arasan_phy_sts_poll(host, DLL_STATUS, DLL_RDY_MASK);
		अगर (ret)
			वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक arasan_select_phy_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	काष्ठा arasan_host *arasan_host = sdhci_pci_priv(slot);
	u8 clk;

	अगर (arasan_host->chg_clk == host->mmc->ios.घड़ी)
		वापस 0;

	arasan_host->chg_clk = host->mmc->ios.घड़ी;
	अगर (host->mmc->ios.घड़ी == 200000000)
		clk = 0x0;
	अन्यथा अगर (host->mmc->ios.घड़ी == 100000000)
		clk = 0x2;
	अन्यथा अगर (host->mmc->ios.घड़ी == 50000000)
		clk = 0x1;
	अन्यथा
		clk = 0x0;

	अगर (host->mmc_host_ops.hs400_enhanced_strobe) अणु
		arasan_phy_set(host, ENHSTRB_MODE, 1, 0x0, 0x0,
			       DLLTRM_ICP, clk);
	पूर्ण अन्यथा अणु
		चयन (host->mmc->ios.timing) अणु
		हाल MMC_TIMING_LEGACY:
			arasan_phy_set(host, LEGACY_MODE, 0x0, 0x0, 0x0,
				       0x0, 0x0);
			अवरोध;
		हाल MMC_TIMING_MMC_HS:
		हाल MMC_TIMING_SD_HS:
			arasan_phy_set(host, HISPD_MODE, 0x3, 0x0, 0x2,
				       DLLTRM_ICP, clk);
			अवरोध;
		हाल MMC_TIMING_MMC_HS200:
		हाल MMC_TIMING_UHS_SDR104:
			arasan_phy_set(host, HS200_MODE, 0x2,
				       host->mmc->ios.drv_type, 0x0,
				       DLLTRM_ICP, clk);
			अवरोध;
		हाल MMC_TIMING_MMC_DDR52:
		हाल MMC_TIMING_UHS_DDR50:
			arasan_phy_set(host, DDR50_MODE, 0x1, 0x0,
				       0x0, DLLTRM_ICP, clk);
			अवरोध;
		हाल MMC_TIMING_MMC_HS400:
			arasan_phy_set(host, HS400_MODE, 0x1,
				       host->mmc->ios.drv_type, 0xa,
				       DLLTRM_ICP, clk);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक arasan_pci_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	पूर्णांक err;

	slot->host->mmc->caps |= MMC_CAP_NONREMOVABLE | MMC_CAP_8_BIT_DATA;
	err = arasan_phy_init(slot->host);
	अगर (err)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम arasan_sdhci_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	sdhci_set_घड़ी(host, घड़ी);

	/* Change phy settings क्रम the new घड़ी */
	arasan_select_phy_घड़ी(host);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops arasan_sdhci_pci_ops = अणु
	.set_घड़ी	= arasan_sdhci_set_घड़ी,
	.enable_dma	= sdhci_pci_enable_dma,
	.set_bus_width	= sdhci_set_bus_width,
	.reset		= sdhci_reset,
	.set_uhs_संकेतing	= sdhci_set_uhs_संकेतing,
पूर्ण;

स्थिर काष्ठा sdhci_pci_fixes sdhci_arasan = अणु
	.probe_slot = arasan_pci_probe_slot,
	.ops        = &arasan_sdhci_pci_ops,
	.priv_size  = माप(काष्ठा arasan_host),
पूर्ण;
