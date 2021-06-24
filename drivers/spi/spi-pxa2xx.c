<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2005 Stephen Street / StreetFire Sound Lअसल
 * Copyright (C) 2013, Intel Corporation
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/spi/spi.h>

#समावेश "spi-pxa2xx.h"

MODULE_AUTHOR("Stephen Street");
MODULE_DESCRIPTION("PXA2xx SSP SPI Controller");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-spi");

#घोषणा TIMOUT_DFLT		1000

/*
 * क्रम testing SSCR1 changes that require SSP restart, basically
 * everything except the service and पूर्णांकerrupt enables, the pxa270 developer
 * manual says only SSCR1_SCFR, SSCR1_SPH, SSCR1_SPO need to be in this
 * list, but the PXA255 dev man says all bits without really meaning the
 * service and पूर्णांकerrupt enables
 */
#घोषणा SSCR1_CHANGE_MASK (SSCR1_TTELP | SSCR1_TTE | SSCR1_SCFR \
				| SSCR1_ECRA | SSCR1_ECRB | SSCR1_SCLKसूची \
				| SSCR1_SFRMसूची | SSCR1_RWOT | SSCR1_TRAIL \
				| SSCR1_IFS | SSCR1_STRF | SSCR1_EFWR \
				| SSCR1_RFT | SSCR1_TFT | SSCR1_MWDS \
				| SSCR1_SPH | SSCR1_SPO | SSCR1_LBM)

#घोषणा QUARK_X1000_SSCR1_CHANGE_MASK (QUARK_X1000_SSCR1_STRF	\
				| QUARK_X1000_SSCR1_EFWR	\
				| QUARK_X1000_SSCR1_RFT		\
				| QUARK_X1000_SSCR1_TFT		\
				| SSCR1_SPH | SSCR1_SPO | SSCR1_LBM)

#घोषणा CE4100_SSCR1_CHANGE_MASK (SSCR1_TTELP | SSCR1_TTE | SSCR1_SCFR \
				| SSCR1_ECRA | SSCR1_ECRB | SSCR1_SCLKसूची \
				| SSCR1_SFRMसूची | SSCR1_RWOT | SSCR1_TRAIL \
				| SSCR1_IFS | SSCR1_STRF | SSCR1_EFWR \
				| CE4100_SSCR1_RFT | CE4100_SSCR1_TFT | SSCR1_MWDS \
				| SSCR1_SPH | SSCR1_SPO | SSCR1_LBM)

#घोषणा LPSS_GENERAL_REG_RXTO_HOLDOFF_DISABLE	BIT(24)
#घोषणा LPSS_CS_CONTROL_SW_MODE			BIT(0)
#घोषणा LPSS_CS_CONTROL_CS_HIGH			BIT(1)
#घोषणा LPSS_CAPS_CS_EN_SHIFT			9
#घोषणा LPSS_CAPS_CS_EN_MASK			(0xf << LPSS_CAPS_CS_EN_SHIFT)

#घोषणा LPSS_PRIV_CLOCK_GATE 0x38
#घोषणा LPSS_PRIV_CLOCK_GATE_CLK_CTL_MASK 0x3
#घोषणा LPSS_PRIV_CLOCK_GATE_CLK_CTL_FORCE_ON 0x3

काष्ठा lpss_config अणु
	/* LPSS offset from drv_data->ioaddr */
	अचिन्हित offset;
	/* Register offsets from drv_data->lpss_base or -1 */
	पूर्णांक reg_general;
	पूर्णांक reg_ssp;
	पूर्णांक reg_cs_ctrl;
	पूर्णांक reg_capabilities;
	/* FIFO thresholds */
	u32 rx_threshold;
	u32 tx_threshold_lo;
	u32 tx_threshold_hi;
	/* Chip select control */
	अचिन्हित cs_sel_shअगरt;
	अचिन्हित cs_sel_mask;
	अचिन्हित cs_num;
	/* Quirks */
	अचिन्हित cs_clk_stays_gated : 1;
पूर्ण;

/* Keep these sorted with क्रमागत pxa_ssp_type */
अटल स्थिर काष्ठा lpss_config lpss_platक्रमms[] = अणु
	अणु	/* LPSS_LPT_SSP */
		.offset = 0x800,
		.reg_general = 0x08,
		.reg_ssp = 0x0c,
		.reg_cs_ctrl = 0x18,
		.reg_capabilities = -1,
		.rx_threshold = 64,
		.tx_threshold_lo = 160,
		.tx_threshold_hi = 224,
	पूर्ण,
	अणु	/* LPSS_BYT_SSP */
		.offset = 0x400,
		.reg_general = 0x08,
		.reg_ssp = 0x0c,
		.reg_cs_ctrl = 0x18,
		.reg_capabilities = -1,
		.rx_threshold = 64,
		.tx_threshold_lo = 160,
		.tx_threshold_hi = 224,
	पूर्ण,
	अणु	/* LPSS_BSW_SSP */
		.offset = 0x400,
		.reg_general = 0x08,
		.reg_ssp = 0x0c,
		.reg_cs_ctrl = 0x18,
		.reg_capabilities = -1,
		.rx_threshold = 64,
		.tx_threshold_lo = 160,
		.tx_threshold_hi = 224,
		.cs_sel_shअगरt = 2,
		.cs_sel_mask = 1 << 2,
		.cs_num = 2,
	पूर्ण,
	अणु	/* LPSS_SPT_SSP */
		.offset = 0x200,
		.reg_general = -1,
		.reg_ssp = 0x20,
		.reg_cs_ctrl = 0x24,
		.reg_capabilities = -1,
		.rx_threshold = 1,
		.tx_threshold_lo = 32,
		.tx_threshold_hi = 56,
	पूर्ण,
	अणु	/* LPSS_BXT_SSP */
		.offset = 0x200,
		.reg_general = -1,
		.reg_ssp = 0x20,
		.reg_cs_ctrl = 0x24,
		.reg_capabilities = 0xfc,
		.rx_threshold = 1,
		.tx_threshold_lo = 16,
		.tx_threshold_hi = 48,
		.cs_sel_shअगरt = 8,
		.cs_sel_mask = 3 << 8,
		.cs_clk_stays_gated = true,
	पूर्ण,
	अणु	/* LPSS_CNL_SSP */
		.offset = 0x200,
		.reg_general = -1,
		.reg_ssp = 0x20,
		.reg_cs_ctrl = 0x24,
		.reg_capabilities = 0xfc,
		.rx_threshold = 1,
		.tx_threshold_lo = 32,
		.tx_threshold_hi = 56,
		.cs_sel_shअगरt = 8,
		.cs_sel_mask = 3 << 8,
		.cs_clk_stays_gated = true,
	पूर्ण,
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा lpss_config
*lpss_get_config(स्थिर काष्ठा driver_data *drv_data)
अणु
	वापस &lpss_platक्रमms[drv_data->ssp_type - LPSS_LPT_SSP];
पूर्ण

अटल bool is_lpss_ssp(स्थिर काष्ठा driver_data *drv_data)
अणु
	चयन (drv_data->ssp_type) अणु
	हाल LPSS_LPT_SSP:
	हाल LPSS_BYT_SSP:
	हाल LPSS_BSW_SSP:
	हाल LPSS_SPT_SSP:
	हाल LPSS_BXT_SSP:
	हाल LPSS_CNL_SSP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_quark_x1000_ssp(स्थिर काष्ठा driver_data *drv_data)
अणु
	वापस drv_data->ssp_type == QUARK_X1000_SSP;
पूर्ण

अटल bool is_mmp2_ssp(स्थिर काष्ठा driver_data *drv_data)
अणु
	वापस drv_data->ssp_type == MMP2_SSP;
पूर्ण

अटल u32 pxa2xx_spi_get_ssrc1_change_mask(स्थिर काष्ठा driver_data *drv_data)
अणु
	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		वापस QUARK_X1000_SSCR1_CHANGE_MASK;
	हाल CE4100_SSP:
		वापस CE4100_SSCR1_CHANGE_MASK;
	शेष:
		वापस SSCR1_CHANGE_MASK;
	पूर्ण
पूर्ण

अटल u32
pxa2xx_spi_get_rx_शेष_thre(स्थिर काष्ठा driver_data *drv_data)
अणु
	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		वापस RX_THRESH_QUARK_X1000_DFLT;
	हाल CE4100_SSP:
		वापस RX_THRESH_CE4100_DFLT;
	शेष:
		वापस RX_THRESH_DFLT;
	पूर्ण
पूर्ण

अटल bool pxa2xx_spi_txfअगरo_full(स्थिर काष्ठा driver_data *drv_data)
अणु
	u32 mask;

	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		mask = QUARK_X1000_SSSR_TFL_MASK;
		अवरोध;
	हाल CE4100_SSP:
		mask = CE4100_SSSR_TFL_MASK;
		अवरोध;
	शेष:
		mask = SSSR_TFL_MASK;
		अवरोध;
	पूर्ण

	वापस (pxa2xx_spi_पढ़ो(drv_data, SSSR) & mask) == mask;
पूर्ण

अटल व्योम pxa2xx_spi_clear_rx_thre(स्थिर काष्ठा driver_data *drv_data,
				     u32 *sccr1_reg)
अणु
	u32 mask;

	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		mask = QUARK_X1000_SSCR1_RFT;
		अवरोध;
	हाल CE4100_SSP:
		mask = CE4100_SSCR1_RFT;
		अवरोध;
	शेष:
		mask = SSCR1_RFT;
		अवरोध;
	पूर्ण
	*sccr1_reg &= ~mask;
पूर्ण

अटल व्योम pxa2xx_spi_set_rx_thre(स्थिर काष्ठा driver_data *drv_data,
				   u32 *sccr1_reg, u32 threshold)
अणु
	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		*sccr1_reg |= QUARK_X1000_SSCR1_RxTresh(threshold);
		अवरोध;
	हाल CE4100_SSP:
		*sccr1_reg |= CE4100_SSCR1_RxTresh(threshold);
		अवरोध;
	शेष:
		*sccr1_reg |= SSCR1_RxTresh(threshold);
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 pxa2xx_configure_sscr0(स्थिर काष्ठा driver_data *drv_data,
				  u32 clk_भाग, u8 bits)
अणु
	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		वापस clk_भाग
			| QUARK_X1000_SSCR0_Motorola
			| QUARK_X1000_SSCR0_DataSize(bits > 32 ? 8 : bits)
			| SSCR0_SSE;
	शेष:
		वापस clk_भाग
			| SSCR0_Motorola
			| SSCR0_DataSize(bits > 16 ? bits - 16 : bits)
			| SSCR0_SSE
			| (bits > 16 ? SSCR0_EDSS : 0);
	पूर्ण
पूर्ण

/*
 * Read and ग_लिखो LPSS SSP निजी रेजिस्टरs. Caller must first check that
 * is_lpss_ssp() वापसs true beक्रमe these can be called.
 */
अटल u32 __lpss_ssp_पढ़ो_priv(काष्ठा driver_data *drv_data, अचिन्हित offset)
अणु
	WARN_ON(!drv_data->lpss_base);
	वापस पढ़ोl(drv_data->lpss_base + offset);
पूर्ण

अटल व्योम __lpss_ssp_ग_लिखो_priv(काष्ठा driver_data *drv_data,
				  अचिन्हित offset, u32 value)
अणु
	WARN_ON(!drv_data->lpss_base);
	ग_लिखोl(value, drv_data->lpss_base + offset);
पूर्ण

/*
 * lpss_ssp_setup - perक्रमm LPSS SSP specअगरic setup
 * @drv_data: poपूर्णांकer to the driver निजी data
 *
 * Perक्रमm LPSS SSP specअगरic setup. This function must be called first अगर
 * one is going to use LPSS SSP निजी रेजिस्टरs.
 */
अटल व्योम lpss_ssp_setup(काष्ठा driver_data *drv_data)
अणु
	स्थिर काष्ठा lpss_config *config;
	u32 value;

	config = lpss_get_config(drv_data);
	drv_data->lpss_base = drv_data->ioaddr + config->offset;

	/* Enable software chip select control */
	value = __lpss_ssp_पढ़ो_priv(drv_data, config->reg_cs_ctrl);
	value &= ~(LPSS_CS_CONTROL_SW_MODE | LPSS_CS_CONTROL_CS_HIGH);
	value |= LPSS_CS_CONTROL_SW_MODE | LPSS_CS_CONTROL_CS_HIGH;
	__lpss_ssp_ग_लिखो_priv(drv_data, config->reg_cs_ctrl, value);

	/* Enable multiblock DMA transfers */
	अगर (drv_data->controller_info->enable_dma) अणु
		__lpss_ssp_ग_लिखो_priv(drv_data, config->reg_ssp, 1);

		अगर (config->reg_general >= 0) अणु
			value = __lpss_ssp_पढ़ो_priv(drv_data,
						     config->reg_general);
			value |= LPSS_GENERAL_REG_RXTO_HOLDOFF_DISABLE;
			__lpss_ssp_ग_लिखो_priv(drv_data,
					      config->reg_general, value);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम lpss_ssp_select_cs(काष्ठा spi_device *spi,
			       स्थिर काष्ठा lpss_config *config)
अणु
	काष्ठा driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);
	u32 value, cs;

	अगर (!config->cs_sel_mask)
		वापस;

	value = __lpss_ssp_पढ़ो_priv(drv_data, config->reg_cs_ctrl);

	cs = spi->chip_select;
	cs <<= config->cs_sel_shअगरt;
	अगर (cs != (value & config->cs_sel_mask)) अणु
		/*
		 * When चयनing another chip select output active the
		 * output must be selected first and रुको 2 ssp_clk cycles
		 * beक्रमe changing state to active. Otherwise a लघु
		 * glitch will occur on the previous chip select since
		 * output select is latched but state control is not.
		 */
		value &= ~config->cs_sel_mask;
		value |= cs;
		__lpss_ssp_ग_लिखो_priv(drv_data,
				      config->reg_cs_ctrl, value);
		ndelay(1000000000 /
		       (drv_data->controller->max_speed_hz / 2));
	पूर्ण
पूर्ण

अटल व्योम lpss_ssp_cs_control(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);
	स्थिर काष्ठा lpss_config *config;
	u32 value;

	config = lpss_get_config(drv_data);

	अगर (enable)
		lpss_ssp_select_cs(spi, config);

	value = __lpss_ssp_पढ़ो_priv(drv_data, config->reg_cs_ctrl);
	अगर (enable)
		value &= ~LPSS_CS_CONTROL_CS_HIGH;
	अन्यथा
		value |= LPSS_CS_CONTROL_CS_HIGH;
	__lpss_ssp_ग_लिखो_priv(drv_data, config->reg_cs_ctrl, value);
	अगर (config->cs_clk_stays_gated) अणु
		u32 clkgate;

		/*
		 * Changing CS alone when dynamic घड़ी gating is on won't
		 * actually flip CS at that समय. This ruins SPI transfers
		 * that specअगरy delays, or have no data. Toggle the घड़ी mode
		 * to क्रमce on briefly to poke the CS pin to move.
		 */
		clkgate = __lpss_ssp_पढ़ो_priv(drv_data, LPSS_PRIV_CLOCK_GATE);
		value = (clkgate & ~LPSS_PRIV_CLOCK_GATE_CLK_CTL_MASK) |
			LPSS_PRIV_CLOCK_GATE_CLK_CTL_FORCE_ON;

		__lpss_ssp_ग_लिखो_priv(drv_data, LPSS_PRIV_CLOCK_GATE, value);
		__lpss_ssp_ग_लिखो_priv(drv_data, LPSS_PRIV_CLOCK_GATE, clkgate);
	पूर्ण
पूर्ण

अटल व्योम cs_निश्चित(काष्ठा spi_device *spi)
अणु
	काष्ठा chip_data *chip = spi_get_ctldata(spi);
	काष्ठा driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);

	अगर (drv_data->ssp_type == CE4100_SSP) अणु
		pxa2xx_spi_ग_लिखो(drv_data, SSSR, chip->frm);
		वापस;
	पूर्ण

	अगर (chip->cs_control) अणु
		chip->cs_control(PXA2XX_CS_ASSERT);
		वापस;
	पूर्ण

	अगर (chip->gpiod_cs) अणु
		gpiod_set_value(chip->gpiod_cs, chip->gpio_cs_inverted);
		वापस;
	पूर्ण

	अगर (is_lpss_ssp(drv_data))
		lpss_ssp_cs_control(spi, true);
पूर्ण

अटल व्योम cs_deनिश्चित(काष्ठा spi_device *spi)
अणु
	काष्ठा chip_data *chip = spi_get_ctldata(spi);
	काष्ठा driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);
	अचिन्हित दीर्घ समयout;

	अगर (drv_data->ssp_type == CE4100_SSP)
		वापस;

	/* Wait until SSP becomes idle beक्रमe deनिश्चितing the CS */
	समयout = jअगरfies + msecs_to_jअगरfies(10);
	जबतक (pxa2xx_spi_पढ़ो(drv_data, SSSR) & SSSR_BSY &&
	       !समय_after(jअगरfies, समयout))
		cpu_relax();

	अगर (chip->cs_control) अणु
		chip->cs_control(PXA2XX_CS_DEASSERT);
		वापस;
	पूर्ण

	अगर (chip->gpiod_cs) अणु
		gpiod_set_value(chip->gpiod_cs, !chip->gpio_cs_inverted);
		वापस;
	पूर्ण

	अगर (is_lpss_ssp(drv_data))
		lpss_ssp_cs_control(spi, false);
पूर्ण

अटल व्योम pxa2xx_spi_set_cs(काष्ठा spi_device *spi, bool level)
अणु
	अगर (level)
		cs_deनिश्चित(spi);
	अन्यथा
		cs_निश्चित(spi);
पूर्ण

पूर्णांक pxa2xx_spi_flush(काष्ठा driver_data *drv_data)
अणु
	अचिन्हित दीर्घ limit = loops_per_jअगरfy << 1;

	करो अणु
		जबतक (pxa2xx_spi_पढ़ो(drv_data, SSSR) & SSSR_RNE)
			pxa2xx_spi_पढ़ो(drv_data, SSDR);
	पूर्ण जबतक ((pxa2xx_spi_पढ़ो(drv_data, SSSR) & SSSR_BSY) && --limit);
	ग_लिखो_SSSR_CS(drv_data, SSSR_ROR);

	वापस limit;
पूर्ण

अटल व्योम pxa2xx_spi_off(काष्ठा driver_data *drv_data)
अणु
	/* On MMP, disabling SSE seems to corrupt the Rx FIFO */
	अगर (is_mmp2_ssp(drv_data))
		वापस;

	pxa2xx_spi_ग_लिखो(drv_data, SSCR0,
			 pxa2xx_spi_पढ़ो(drv_data, SSCR0) & ~SSCR0_SSE);
पूर्ण

अटल पूर्णांक null_ग_लिखोr(काष्ठा driver_data *drv_data)
अणु
	u8 n_bytes = drv_data->n_bytes;

	अगर (pxa2xx_spi_txfअगरo_full(drv_data)
		|| (drv_data->tx == drv_data->tx_end))
		वापस 0;

	pxa2xx_spi_ग_लिखो(drv_data, SSDR, 0);
	drv_data->tx += n_bytes;

	वापस 1;
पूर्ण

अटल पूर्णांक null_पढ़ोer(काष्ठा driver_data *drv_data)
अणु
	u8 n_bytes = drv_data->n_bytes;

	जबतक ((pxa2xx_spi_पढ़ो(drv_data, SSSR) & SSSR_RNE)
	       && (drv_data->rx < drv_data->rx_end)) अणु
		pxa2xx_spi_पढ़ो(drv_data, SSDR);
		drv_data->rx += n_bytes;
	पूर्ण

	वापस drv_data->rx == drv_data->rx_end;
पूर्ण

अटल पूर्णांक u8_ग_लिखोr(काष्ठा driver_data *drv_data)
अणु
	अगर (pxa2xx_spi_txfअगरo_full(drv_data)
		|| (drv_data->tx == drv_data->tx_end))
		वापस 0;

	pxa2xx_spi_ग_लिखो(drv_data, SSDR, *(u8 *)(drv_data->tx));
	++drv_data->tx;

	वापस 1;
पूर्ण

अटल पूर्णांक u8_पढ़ोer(काष्ठा driver_data *drv_data)
अणु
	जबतक ((pxa2xx_spi_पढ़ो(drv_data, SSSR) & SSSR_RNE)
	       && (drv_data->rx < drv_data->rx_end)) अणु
		*(u8 *)(drv_data->rx) = pxa2xx_spi_पढ़ो(drv_data, SSDR);
		++drv_data->rx;
	पूर्ण

	वापस drv_data->rx == drv_data->rx_end;
पूर्ण

अटल पूर्णांक u16_ग_लिखोr(काष्ठा driver_data *drv_data)
अणु
	अगर (pxa2xx_spi_txfअगरo_full(drv_data)
		|| (drv_data->tx == drv_data->tx_end))
		वापस 0;

	pxa2xx_spi_ग_लिखो(drv_data, SSDR, *(u16 *)(drv_data->tx));
	drv_data->tx += 2;

	वापस 1;
पूर्ण

अटल पूर्णांक u16_पढ़ोer(काष्ठा driver_data *drv_data)
अणु
	जबतक ((pxa2xx_spi_पढ़ो(drv_data, SSSR) & SSSR_RNE)
	       && (drv_data->rx < drv_data->rx_end)) अणु
		*(u16 *)(drv_data->rx) = pxa2xx_spi_पढ़ो(drv_data, SSDR);
		drv_data->rx += 2;
	पूर्ण

	वापस drv_data->rx == drv_data->rx_end;
पूर्ण

अटल पूर्णांक u32_ग_लिखोr(काष्ठा driver_data *drv_data)
अणु
	अगर (pxa2xx_spi_txfअगरo_full(drv_data)
		|| (drv_data->tx == drv_data->tx_end))
		वापस 0;

	pxa2xx_spi_ग_लिखो(drv_data, SSDR, *(u32 *)(drv_data->tx));
	drv_data->tx += 4;

	वापस 1;
पूर्ण

अटल पूर्णांक u32_पढ़ोer(काष्ठा driver_data *drv_data)
अणु
	जबतक ((pxa2xx_spi_पढ़ो(drv_data, SSSR) & SSSR_RNE)
	       && (drv_data->rx < drv_data->rx_end)) अणु
		*(u32 *)(drv_data->rx) = pxa2xx_spi_पढ़ो(drv_data, SSDR);
		drv_data->rx += 4;
	पूर्ण

	वापस drv_data->rx == drv_data->rx_end;
पूर्ण

अटल व्योम reset_sccr1(काष्ठा driver_data *drv_data)
अणु
	काष्ठा chip_data *chip =
		spi_get_ctldata(drv_data->controller->cur_msg->spi);
	u32 sccr1_reg;

	sccr1_reg = pxa2xx_spi_पढ़ो(drv_data, SSCR1) & ~drv_data->पूर्णांक_cr1;
	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		sccr1_reg &= ~QUARK_X1000_SSCR1_RFT;
		अवरोध;
	हाल CE4100_SSP:
		sccr1_reg &= ~CE4100_SSCR1_RFT;
		अवरोध;
	शेष:
		sccr1_reg &= ~SSCR1_RFT;
		अवरोध;
	पूर्ण
	sccr1_reg |= chip->threshold;
	pxa2xx_spi_ग_लिखो(drv_data, SSCR1, sccr1_reg);
पूर्ण

अटल व्योम पूर्णांक_error_stop(काष्ठा driver_data *drv_data, स्थिर अक्षर *msg)
अणु
	/* Stop and reset SSP */
	ग_लिखो_SSSR_CS(drv_data, drv_data->clear_sr);
	reset_sccr1(drv_data);
	अगर (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_ग_लिखो(drv_data, SSTO, 0);
	pxa2xx_spi_flush(drv_data);
	pxa2xx_spi_off(drv_data);

	dev_err(&drv_data->pdev->dev, "%s\n", msg);

	drv_data->controller->cur_msg->status = -EIO;
	spi_finalize_current_transfer(drv_data->controller);
पूर्ण

अटल व्योम पूर्णांक_transfer_complete(काष्ठा driver_data *drv_data)
अणु
	/* Clear and disable पूर्णांकerrupts */
	ग_लिखो_SSSR_CS(drv_data, drv_data->clear_sr);
	reset_sccr1(drv_data);
	अगर (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_ग_लिखो(drv_data, SSTO, 0);

	spi_finalize_current_transfer(drv_data->controller);
पूर्ण

अटल irqवापस_t पूर्णांकerrupt_transfer(काष्ठा driver_data *drv_data)
अणु
	u32 irq_mask = (pxa2xx_spi_पढ़ो(drv_data, SSCR1) & SSCR1_TIE) ?
		       drv_data->mask_sr : drv_data->mask_sr & ~SSSR_TFS;

	u32 irq_status = pxa2xx_spi_पढ़ो(drv_data, SSSR) & irq_mask;

	अगर (irq_status & SSSR_ROR) अणु
		पूर्णांक_error_stop(drv_data, "interrupt_transfer: fifo overrun");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (irq_status & SSSR_TUR) अणु
		पूर्णांक_error_stop(drv_data, "interrupt_transfer: fifo underrun");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (irq_status & SSSR_TINT) अणु
		pxa2xx_spi_ग_लिखो(drv_data, SSSR, SSSR_TINT);
		अगर (drv_data->पढ़ो(drv_data)) अणु
			पूर्णांक_transfer_complete(drv_data);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* Drain rx fअगरo, Fill tx fअगरo and prevent overruns */
	करो अणु
		अगर (drv_data->पढ़ो(drv_data)) अणु
			पूर्णांक_transfer_complete(drv_data);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण जबतक (drv_data->ग_लिखो(drv_data));

	अगर (drv_data->पढ़ो(drv_data)) अणु
		पूर्णांक_transfer_complete(drv_data);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (drv_data->tx == drv_data->tx_end) अणु
		u32 bytes_left;
		u32 sccr1_reg;

		sccr1_reg = pxa2xx_spi_पढ़ो(drv_data, SSCR1);
		sccr1_reg &= ~SSCR1_TIE;

		/*
		 * PXA25x_SSP has no समयout, set up rx threshould क्रम the
		 * reमुख्यing RX bytes.
		 */
		अगर (pxa25x_ssp_comp(drv_data)) अणु
			u32 rx_thre;

			pxa2xx_spi_clear_rx_thre(drv_data, &sccr1_reg);

			bytes_left = drv_data->rx_end - drv_data->rx;
			चयन (drv_data->n_bytes) अणु
			हाल 4:
				bytes_left >>= 2;
				अवरोध;
			हाल 2:
				bytes_left >>= 1;
				अवरोध;
			पूर्ण

			rx_thre = pxa2xx_spi_get_rx_शेष_thre(drv_data);
			अगर (rx_thre > bytes_left)
				rx_thre = bytes_left;

			pxa2xx_spi_set_rx_thre(drv_data, &sccr1_reg, rx_thre);
		पूर्ण
		pxa2xx_spi_ग_लिखो(drv_data, SSCR1, sccr1_reg);
	पूर्ण

	/* We did something */
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम handle_bad_msg(काष्ठा driver_data *drv_data)
अणु
	pxa2xx_spi_off(drv_data);
	pxa2xx_spi_ग_लिखो(drv_data, SSCR1,
			 pxa2xx_spi_पढ़ो(drv_data, SSCR1) & ~drv_data->पूर्णांक_cr1);
	अगर (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_ग_लिखो(drv_data, SSTO, 0);
	ग_लिखो_SSSR_CS(drv_data, drv_data->clear_sr);

	dev_err(&drv_data->pdev->dev,
		"bad message state in interrupt handler\n");
पूर्ण

अटल irqवापस_t ssp_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा driver_data *drv_data = dev_id;
	u32 sccr1_reg;
	u32 mask = drv_data->mask_sr;
	u32 status;

	/*
	 * The IRQ might be shared with other peripherals so we must first
	 * check that are we RPM suspended or not. If we are we assume that
	 * the IRQ was not क्रम us (we shouldn't be RPM suspended when the
	 * पूर्णांकerrupt is enabled).
	 */
	अगर (pm_runसमय_suspended(&drv_data->pdev->dev))
		वापस IRQ_NONE;

	/*
	 * If the device is not yet in RPM suspended state and we get an
	 * पूर्णांकerrupt that is meant क्रम another device, check अगर status bits
	 * are all set to one. That means that the device is alपढ़ोy
	 * घातered off.
	 */
	status = pxa2xx_spi_पढ़ो(drv_data, SSSR);
	अगर (status == ~0)
		वापस IRQ_NONE;

	sccr1_reg = pxa2xx_spi_पढ़ो(drv_data, SSCR1);

	/* Ignore possible ग_लिखोs अगर we करोn't need to ग_लिखो */
	अगर (!(sccr1_reg & SSCR1_TIE))
		mask &= ~SSSR_TFS;

	/* Ignore RX समयout पूर्णांकerrupt अगर it is disabled */
	अगर (!(sccr1_reg & SSCR1_TINTE))
		mask &= ~SSSR_TINT;

	अगर (!(status & mask))
		वापस IRQ_NONE;

	pxa2xx_spi_ग_लिखो(drv_data, SSCR1, sccr1_reg & ~drv_data->पूर्णांक_cr1);
	pxa2xx_spi_ग_लिखो(drv_data, SSCR1, sccr1_reg);

	अगर (!drv_data->controller->cur_msg) अणु
		handle_bad_msg(drv_data);
		/* Never fail */
		वापस IRQ_HANDLED;
	पूर्ण

	वापस drv_data->transfer_handler(drv_data);
पूर्ण

/*
 * The Quark SPI has an additional 24 bit रेजिस्टर (DDS_CLK_RATE) to multiply
 * input frequency by fractions of 2^24. It also has a भागider by 5.
 *
 * There are क्रमmulas to get baud rate value क्रम given input frequency and
 * भागider parameters, such as DDS_CLK_RATE and SCR:
 *
 * Fsys = 200MHz
 *
 * Fssp = Fsys * DDS_CLK_RATE / 2^24			(1)
 * Baud rate = Fsclk = Fssp / (2 * (SCR + 1))		(2)
 *
 * DDS_CLK_RATE either 2^n or 2^n / 5.
 * SCR is in range 0 .. 255
 *
 * Divisor = 5^i * 2^j * 2 * k
 *       i = [0, 1]      i = 1 अगरf j = 0 or j > 3
 *       j = [0, 23]     j = 0 अगरf i = 1
 *       k = [1, 256]
 * Special हाल: j = 0, i = 1: Divisor = 2 / 5
 *
 * Accordingly to the specअगरication the recommended values क्रम DDS_CLK_RATE
 * are:
 *	Case 1:		2^n, n = [0, 23]
 *	Case 2:		2^24 * 2 / 5 (0x666666)
 *	Case 3:		less than or equal to 2^24 / 5 / 16 (0x33333)
 *
 * In all हालs the lowest possible value is better.
 *
 * The function calculates parameters क्रम all हालs and chooses the one बंदst
 * to the asked baud rate.
 */
अटल अचिन्हित पूर्णांक quark_x1000_get_clk_भाग(पूर्णांक rate, u32 *dds)
अणु
	अचिन्हित दीर्घ xtal = 200000000;
	अचिन्हित दीर्घ fref = xtal / 2;		/* mandatory भागision by 2,
						   see (2) */
						/* हाल 3 */
	अचिन्हित दीर्घ fref1 = fref / 2;		/* हाल 1 */
	अचिन्हित दीर्घ fref2 = fref * 2 / 5;	/* हाल 2 */
	अचिन्हित दीर्घ scale;
	अचिन्हित दीर्घ q, q1, q2;
	दीर्घ r, r1, r2;
	u32 mul;

	/* Case 1 */

	/* Set initial value क्रम DDS_CLK_RATE */
	mul = (1 << 24) >> 1;

	/* Calculate initial quot */
	q1 = DIV_ROUND_UP(fref1, rate);

	/* Scale q1 अगर it's too big */
	अगर (q1 > 256) अणु
		/* Scale q1 to range [1, 512] */
		scale = fls_दीर्घ(q1 - 1);
		अगर (scale > 9) अणु
			q1 >>= scale - 9;
			mul >>= scale - 9;
		पूर्ण

		/* Round the result अगर we have a reमुख्यder */
		q1 += q1 & 1;
	पूर्ण

	/* Decrease DDS_CLK_RATE as much as we can without loss in precision */
	scale = __ffs(q1);
	q1 >>= scale;
	mul >>= scale;

	/* Get the reमुख्यder */
	r1 = असल(fref1 / (1 << (24 - fls_दीर्घ(mul))) / q1 - rate);

	/* Case 2 */

	q2 = DIV_ROUND_UP(fref2, rate);
	r2 = असल(fref2 / q2 - rate);

	/*
	 * Choose the best between two: less reमुख्यder we have the better. We
	 * can't go हाल 2 अगर q2 is greater than 256 since SCR रेजिस्टर can
	 * hold only values 0 .. 255.
	 */
	अगर (r2 >= r1 || q2 > 256) अणु
		/* हाल 1 is better */
		r = r1;
		q = q1;
	पूर्ण अन्यथा अणु
		/* हाल 2 is better */
		r = r2;
		q = q2;
		mul = (1 << 24) * 2 / 5;
	पूर्ण

	/* Check हाल 3 only अगर the भागisor is big enough */
	अगर (fref / rate >= 80) अणु
		u64 fssp;
		u32 m;

		/* Calculate initial quot */
		q1 = DIV_ROUND_UP(fref, rate);
		m = (1 << 24) / q1;

		/* Get the reमुख्यder */
		fssp = (u64)fref * m;
		करो_भाग(fssp, 1 << 24);
		r1 = असल(fssp - rate);

		/* Choose this one अगर it suits better */
		अगर (r1 < r) अणु
			/* हाल 3 is better */
			q = 1;
			mul = m;
		पूर्ण
	पूर्ण

	*dds = mul;
	वापस q - 1;
पूर्ण

अटल अचिन्हित पूर्णांक ssp_get_clk_भाग(काष्ठा driver_data *drv_data, पूर्णांक rate)
अणु
	अचिन्हित दीर्घ ssp_clk = drv_data->controller->max_speed_hz;
	स्थिर काष्ठा ssp_device *ssp = drv_data->ssp;

	rate = min_t(पूर्णांक, ssp_clk, rate);

	/*
	 * Calculate the भागisor क्रम the SCR (Serial Clock Rate), aव्योमing
	 * that the SSP transmission rate can be greater than the device rate
	 */
	अगर (ssp->type == PXA25x_SSP || ssp->type == CE4100_SSP)
		वापस (DIV_ROUND_UP(ssp_clk, 2 * rate) - 1) & 0xff;
	अन्यथा
		वापस (DIV_ROUND_UP(ssp_clk, rate) - 1)  & 0xfff;
पूर्ण

अटल अचिन्हित पूर्णांक pxa2xx_ssp_get_clk_भाग(काष्ठा driver_data *drv_data,
					   पूर्णांक rate)
अणु
	काष्ठा chip_data *chip =
		spi_get_ctldata(drv_data->controller->cur_msg->spi);
	अचिन्हित पूर्णांक clk_भाग;

	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		clk_भाग = quark_x1000_get_clk_भाग(rate, &chip->dds_rate);
		अवरोध;
	शेष:
		clk_भाग = ssp_get_clk_भाग(drv_data, rate);
		अवरोध;
	पूर्ण
	वापस clk_भाग << 8;
पूर्ण

अटल bool pxa2xx_spi_can_dma(काष्ठा spi_controller *controller,
			       काष्ठा spi_device *spi,
			       काष्ठा spi_transfer *xfer)
अणु
	काष्ठा chip_data *chip = spi_get_ctldata(spi);

	वापस chip->enable_dma &&
	       xfer->len <= MAX_DMA_LEN &&
	       xfer->len >= chip->dma_burst_size;
पूर्ण

अटल पूर्णांक pxa2xx_spi_transfer_one(काष्ठा spi_controller *controller,
				   काष्ठा spi_device *spi,
				   काष्ठा spi_transfer *transfer)
अणु
	काष्ठा driver_data *drv_data = spi_controller_get_devdata(controller);
	काष्ठा spi_message *message = controller->cur_msg;
	काष्ठा chip_data *chip = spi_get_ctldata(spi);
	u32 dma_thresh = chip->dma_threshold;
	u32 dma_burst = chip->dma_burst_size;
	u32 change_mask = pxa2xx_spi_get_ssrc1_change_mask(drv_data);
	u32 clk_भाग;
	u8 bits;
	u32 speed;
	u32 cr0;
	u32 cr1;
	पूर्णांक err;
	पूर्णांक dma_mapped;

	/* Check अगर we can DMA this transfer */
	अगर (transfer->len > MAX_DMA_LEN && chip->enable_dma) अणु

		/* reject alपढ़ोy-mapped transfers; PIO won't always work */
		अगर (message->is_dma_mapped
				|| transfer->rx_dma || transfer->tx_dma) अणु
			dev_err(&spi->dev,
				"Mapped transfer length of %u is greater than %d\n",
				transfer->len, MAX_DMA_LEN);
			वापस -EINVAL;
		पूर्ण

		/* warn ... we क्रमce this to PIO mode */
		dev_warn_ratelimited(&spi->dev,
				     "DMA disabled for transfer length %ld greater than %d\n",
				     (दीर्घ)transfer->len, MAX_DMA_LEN);
	पूर्ण

	/* Setup the transfer state based on the type of transfer */
	अगर (pxa2xx_spi_flush(drv_data) == 0) अणु
		dev_err(&spi->dev, "Flush failed\n");
		वापस -EIO;
	पूर्ण
	drv_data->n_bytes = chip->n_bytes;
	drv_data->tx = (व्योम *)transfer->tx_buf;
	drv_data->tx_end = drv_data->tx + transfer->len;
	drv_data->rx = transfer->rx_buf;
	drv_data->rx_end = drv_data->rx + transfer->len;
	drv_data->ग_लिखो = drv_data->tx ? chip->ग_लिखो : null_ग_लिखोr;
	drv_data->पढ़ो = drv_data->rx ? chip->पढ़ो : null_पढ़ोer;

	/* Change speed and bit per word on a per transfer */
	bits = transfer->bits_per_word;
	speed = transfer->speed_hz;

	clk_भाग = pxa2xx_ssp_get_clk_भाग(drv_data, speed);

	अगर (bits <= 8) अणु
		drv_data->n_bytes = 1;
		drv_data->पढ़ो = drv_data->पढ़ो != null_पढ़ोer ?
					u8_पढ़ोer : null_पढ़ोer;
		drv_data->ग_लिखो = drv_data->ग_लिखो != null_ग_लिखोr ?
					u8_ग_लिखोr : null_ग_लिखोr;
	पूर्ण अन्यथा अगर (bits <= 16) अणु
		drv_data->n_bytes = 2;
		drv_data->पढ़ो = drv_data->पढ़ो != null_पढ़ोer ?
					u16_पढ़ोer : null_पढ़ोer;
		drv_data->ग_लिखो = drv_data->ग_लिखो != null_ग_लिखोr ?
					u16_ग_लिखोr : null_ग_लिखोr;
	पूर्ण अन्यथा अगर (bits <= 32) अणु
		drv_data->n_bytes = 4;
		drv_data->पढ़ो = drv_data->पढ़ो != null_पढ़ोer ?
					u32_पढ़ोer : null_पढ़ोer;
		drv_data->ग_लिखो = drv_data->ग_लिखो != null_ग_लिखोr ?
					u32_ग_लिखोr : null_ग_लिखोr;
	पूर्ण
	/*
	 * अगर bits/word is changed in dma mode, then must check the
	 * thresholds and burst also
	 */
	अगर (chip->enable_dma) अणु
		अगर (pxa2xx_spi_set_dma_burst_and_threshold(chip,
						spi,
						bits, &dma_burst,
						&dma_thresh))
			dev_warn_ratelimited(&spi->dev,
					     "DMA burst size reduced to match bits_per_word\n");
	पूर्ण

	dma_mapped = controller->can_dma &&
		     controller->can_dma(controller, spi, transfer) &&
		     controller->cur_msg_mapped;
	अगर (dma_mapped) अणु

		/* Ensure we have the correct पूर्णांकerrupt handler */
		drv_data->transfer_handler = pxa2xx_spi_dma_transfer;

		err = pxa2xx_spi_dma_prepare(drv_data, transfer);
		अगर (err)
			वापस err;

		/* Clear status and start DMA engine */
		cr1 = chip->cr1 | dma_thresh | drv_data->dma_cr1;
		pxa2xx_spi_ग_लिखो(drv_data, SSSR, drv_data->clear_sr);

		pxa2xx_spi_dma_start(drv_data);
	पूर्ण अन्यथा अणु
		/* Ensure we have the correct पूर्णांकerrupt handler	*/
		drv_data->transfer_handler = पूर्णांकerrupt_transfer;

		/* Clear status  */
		cr1 = chip->cr1 | chip->threshold | drv_data->पूर्णांक_cr1;
		ग_लिखो_SSSR_CS(drv_data, drv_data->clear_sr);
	पूर्ण

	/* NOTE:  PXA25x_SSP _could_ use बाह्यal घड़ीing ... */
	cr0 = pxa2xx_configure_sscr0(drv_data, clk_भाग, bits);
	अगर (!pxa25x_ssp_comp(drv_data))
		dev_dbg(&spi->dev, "%u Hz actual, %s\n",
			controller->max_speed_hz
				/ (1 + ((cr0 & SSCR0_SCR(0xfff)) >> 8)),
			dma_mapped ? "DMA" : "PIO");
	अन्यथा
		dev_dbg(&spi->dev, "%u Hz actual, %s\n",
			controller->max_speed_hz / 2
				/ (1 + ((cr0 & SSCR0_SCR(0x0ff)) >> 8)),
			dma_mapped ? "DMA" : "PIO");

	अगर (is_lpss_ssp(drv_data)) अणु
		अगर ((pxa2xx_spi_पढ़ो(drv_data, SSIRF) & 0xff)
		    != chip->lpss_rx_threshold)
			pxa2xx_spi_ग_लिखो(drv_data, SSIRF,
					 chip->lpss_rx_threshold);
		अगर ((pxa2xx_spi_पढ़ो(drv_data, SSITF) & 0xffff)
		    != chip->lpss_tx_threshold)
			pxa2xx_spi_ग_लिखो(drv_data, SSITF,
					 chip->lpss_tx_threshold);
	पूर्ण

	अगर (is_quark_x1000_ssp(drv_data) &&
	    (pxa2xx_spi_पढ़ो(drv_data, DDS_RATE) != chip->dds_rate))
		pxa2xx_spi_ग_लिखो(drv_data, DDS_RATE, chip->dds_rate);

	/* see अगर we need to reload the config रेजिस्टरs */
	अगर ((pxa2xx_spi_पढ़ो(drv_data, SSCR0) != cr0)
	    || (pxa2xx_spi_पढ़ो(drv_data, SSCR1) & change_mask)
	    != (cr1 & change_mask)) अणु
		/* stop the SSP, and update the other bits */
		अगर (!is_mmp2_ssp(drv_data))
			pxa2xx_spi_ग_लिखो(drv_data, SSCR0, cr0 & ~SSCR0_SSE);
		अगर (!pxa25x_ssp_comp(drv_data))
			pxa2xx_spi_ग_लिखो(drv_data, SSTO, chip->समयout);
		/* first set CR1 without पूर्णांकerrupt and service enables */
		pxa2xx_spi_ग_लिखो(drv_data, SSCR1, cr1 & change_mask);
		/* restart the SSP */
		pxa2xx_spi_ग_लिखो(drv_data, SSCR0, cr0);

	पूर्ण अन्यथा अणु
		अगर (!pxa25x_ssp_comp(drv_data))
			pxa2xx_spi_ग_लिखो(drv_data, SSTO, chip->समयout);
	पूर्ण

	अगर (is_mmp2_ssp(drv_data)) अणु
		u8 tx_level = (pxa2xx_spi_पढ़ो(drv_data, SSSR)
					& SSSR_TFL_MASK) >> 8;

		अगर (tx_level) अणु
			/* On MMP2, flipping SSE करोesn't to empty TXFIFO. */
			dev_warn(&spi->dev, "%d bytes of garbage in TXFIFO!\n",
								tx_level);
			अगर (tx_level > transfer->len)
				tx_level = transfer->len;
			drv_data->tx += tx_level;
		पूर्ण
	पूर्ण

	अगर (spi_controller_is_slave(controller)) अणु
		जबतक (drv_data->ग_लिखो(drv_data))
			;
		अगर (drv_data->gpiod_पढ़ोy) अणु
			gpiod_set_value(drv_data->gpiod_पढ़ोy, 1);
			udelay(1);
			gpiod_set_value(drv_data->gpiod_पढ़ोy, 0);
		पूर्ण
	पूर्ण

	/*
	 * Release the data by enabling service requests and पूर्णांकerrupts,
	 * without changing any mode bits
	 */
	pxa2xx_spi_ग_लिखो(drv_data, SSCR1, cr1);

	वापस 1;
पूर्ण

अटल पूर्णांक pxa2xx_spi_slave_पात(काष्ठा spi_controller *controller)
अणु
	काष्ठा driver_data *drv_data = spi_controller_get_devdata(controller);

	/* Stop and reset SSP */
	ग_लिखो_SSSR_CS(drv_data, drv_data->clear_sr);
	reset_sccr1(drv_data);
	अगर (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_ग_लिखो(drv_data, SSTO, 0);
	pxa2xx_spi_flush(drv_data);
	pxa2xx_spi_off(drv_data);

	dev_dbg(&drv_data->pdev->dev, "transfer aborted\n");

	drv_data->controller->cur_msg->status = -EINTR;
	spi_finalize_current_transfer(drv_data->controller);

	वापस 0;
पूर्ण

अटल व्योम pxa2xx_spi_handle_err(काष्ठा spi_controller *controller,
				 काष्ठा spi_message *msg)
अणु
	काष्ठा driver_data *drv_data = spi_controller_get_devdata(controller);

	/* Disable the SSP */
	pxa2xx_spi_off(drv_data);
	/* Clear and disable पूर्णांकerrupts and service requests */
	ग_लिखो_SSSR_CS(drv_data, drv_data->clear_sr);
	pxa2xx_spi_ग_लिखो(drv_data, SSCR1,
			 pxa2xx_spi_पढ़ो(drv_data, SSCR1)
			 & ~(drv_data->पूर्णांक_cr1 | drv_data->dma_cr1));
	अगर (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_ग_लिखो(drv_data, SSTO, 0);

	/*
	 * Stop the DMA अगर running. Note DMA callback handler may have unset
	 * the dma_running alपढ़ोy, which is fine as stopping is not needed
	 * then but we shouldn't rely this flag क्रम anything अन्यथा than
	 * stopping. For instance to dअगरferentiate between PIO and DMA
	 * transfers.
	 */
	अगर (atomic_पढ़ो(&drv_data->dma_running))
		pxa2xx_spi_dma_stop(drv_data);
पूर्ण

अटल पूर्णांक pxa2xx_spi_unprepare_transfer(काष्ठा spi_controller *controller)
अणु
	काष्ठा driver_data *drv_data = spi_controller_get_devdata(controller);

	/* Disable the SSP now */
	pxa2xx_spi_off(drv_data);

	वापस 0;
पूर्ण

अटल पूर्णांक setup_cs(काष्ठा spi_device *spi, काष्ठा chip_data *chip,
		    काष्ठा pxa2xx_spi_chip *chip_info)
अणु
	काष्ठा driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);
	काष्ठा gpio_desc *gpiod;
	पूर्णांक err = 0;

	अगर (chip == शून्य)
		वापस 0;

	अगर (drv_data->cs_gpiods) अणु
		gpiod = drv_data->cs_gpiods[spi->chip_select];
		अगर (gpiod) अणु
			chip->gpiod_cs = gpiod;
			chip->gpio_cs_inverted = spi->mode & SPI_CS_HIGH;
			gpiod_set_value(gpiod, chip->gpio_cs_inverted);
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (chip_info == शून्य)
		वापस 0;

	/* NOTE: setup() can be called multiple बार, possibly with
	 * dअगरferent chip_info, release previously requested GPIO
	 */
	अगर (chip->gpiod_cs) अणु
		gpiod_put(chip->gpiod_cs);
		chip->gpiod_cs = शून्य;
	पूर्ण

	/* If (*cs_control) is provided, ignore GPIO chip select */
	अगर (chip_info->cs_control) अणु
		chip->cs_control = chip_info->cs_control;
		वापस 0;
	पूर्ण

	अगर (gpio_is_valid(chip_info->gpio_cs)) अणु
		err = gpio_request(chip_info->gpio_cs, "SPI_CS");
		अगर (err) अणु
			dev_err(&spi->dev, "failed to request chip select GPIO%d\n",
				chip_info->gpio_cs);
			वापस err;
		पूर्ण

		gpiod = gpio_to_desc(chip_info->gpio_cs);
		chip->gpiod_cs = gpiod;
		chip->gpio_cs_inverted = spi->mode & SPI_CS_HIGH;

		err = gpiod_direction_output(gpiod, !chip->gpio_cs_inverted);
		अगर (err)
			gpiod_put(chip->gpiod_cs);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक setup(काष्ठा spi_device *spi)
अणु
	काष्ठा pxa2xx_spi_chip *chip_info;
	काष्ठा chip_data *chip;
	स्थिर काष्ठा lpss_config *config;
	काष्ठा driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);
	uपूर्णांक tx_thres, tx_hi_thres, rx_thres;
	पूर्णांक err;

	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		tx_thres = TX_THRESH_QUARK_X1000_DFLT;
		tx_hi_thres = 0;
		rx_thres = RX_THRESH_QUARK_X1000_DFLT;
		अवरोध;
	हाल CE4100_SSP:
		tx_thres = TX_THRESH_CE4100_DFLT;
		tx_hi_thres = 0;
		rx_thres = RX_THRESH_CE4100_DFLT;
		अवरोध;
	हाल LPSS_LPT_SSP:
	हाल LPSS_BYT_SSP:
	हाल LPSS_BSW_SSP:
	हाल LPSS_SPT_SSP:
	हाल LPSS_BXT_SSP:
	हाल LPSS_CNL_SSP:
		config = lpss_get_config(drv_data);
		tx_thres = config->tx_threshold_lo;
		tx_hi_thres = config->tx_threshold_hi;
		rx_thres = config->rx_threshold;
		अवरोध;
	शेष:
		tx_hi_thres = 0;
		अगर (spi_controller_is_slave(drv_data->controller)) अणु
			tx_thres = 1;
			rx_thres = 2;
		पूर्ण अन्यथा अणु
			tx_thres = TX_THRESH_DFLT;
			rx_thres = RX_THRESH_DFLT;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Only alloc on first setup */
	chip = spi_get_ctldata(spi);
	अगर (!chip) अणु
		chip = kzalloc(माप(काष्ठा chip_data), GFP_KERNEL);
		अगर (!chip)
			वापस -ENOMEM;

		अगर (drv_data->ssp_type == CE4100_SSP) अणु
			अगर (spi->chip_select > 4) अणु
				dev_err(&spi->dev,
					"failed setup: cs number must not be > 4.\n");
				kमुक्त(chip);
				वापस -EINVAL;
			पूर्ण

			chip->frm = spi->chip_select;
		पूर्ण
		chip->enable_dma = drv_data->controller_info->enable_dma;
		chip->समयout = TIMOUT_DFLT;
	पूर्ण

	/* protocol drivers may change the chip settings, so...
	 * अगर chip_info exists, use it */
	chip_info = spi->controller_data;

	/* chip_info isn't always needed */
	chip->cr1 = 0;
	अगर (chip_info) अणु
		अगर (chip_info->समयout)
			chip->समयout = chip_info->समयout;
		अगर (chip_info->tx_threshold)
			tx_thres = chip_info->tx_threshold;
		अगर (chip_info->tx_hi_threshold)
			tx_hi_thres = chip_info->tx_hi_threshold;
		अगर (chip_info->rx_threshold)
			rx_thres = chip_info->rx_threshold;
		chip->dma_threshold = 0;
		अगर (chip_info->enable_loopback)
			chip->cr1 = SSCR1_LBM;
	पूर्ण
	अगर (spi_controller_is_slave(drv_data->controller)) अणु
		chip->cr1 |= SSCR1_SCFR;
		chip->cr1 |= SSCR1_SCLKसूची;
		chip->cr1 |= SSCR1_SFRMसूची;
		chip->cr1 |= SSCR1_SPH;
	पूर्ण

	chip->lpss_rx_threshold = SSIRF_RxThresh(rx_thres);
	chip->lpss_tx_threshold = SSITF_TxLoThresh(tx_thres)
				| SSITF_TxHiThresh(tx_hi_thres);

	/* set dma burst and threshold outside of chip_info path so that अगर
	 * chip_info goes away after setting chip->enable_dma, the
	 * burst and threshold can still respond to changes in bits_per_word */
	अगर (chip->enable_dma) अणु
		/* set up legal burst and threshold क्रम dma */
		अगर (pxa2xx_spi_set_dma_burst_and_threshold(chip, spi,
						spi->bits_per_word,
						&chip->dma_burst_size,
						&chip->dma_threshold)) अणु
			dev_warn(&spi->dev,
				 "in setup: DMA burst size reduced to match bits_per_word\n");
		पूर्ण
		dev_dbg(&spi->dev,
			"in setup: DMA burst size set to %u\n",
			chip->dma_burst_size);
	पूर्ण

	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		chip->threshold = (QUARK_X1000_SSCR1_RxTresh(rx_thres)
				   & QUARK_X1000_SSCR1_RFT)
				   | (QUARK_X1000_SSCR1_TxTresh(tx_thres)
				   & QUARK_X1000_SSCR1_TFT);
		अवरोध;
	हाल CE4100_SSP:
		chip->threshold = (CE4100_SSCR1_RxTresh(rx_thres) & CE4100_SSCR1_RFT) |
			(CE4100_SSCR1_TxTresh(tx_thres) & CE4100_SSCR1_TFT);
		अवरोध;
	शेष:
		chip->threshold = (SSCR1_RxTresh(rx_thres) & SSCR1_RFT) |
			(SSCR1_TxTresh(tx_thres) & SSCR1_TFT);
		अवरोध;
	पूर्ण

	chip->cr1 &= ~(SSCR1_SPO | SSCR1_SPH);
	chip->cr1 |= (((spi->mode & SPI_CPHA) != 0) ? SSCR1_SPH : 0)
			| (((spi->mode & SPI_CPOL) != 0) ? SSCR1_SPO : 0);

	अगर (spi->mode & SPI_LOOP)
		chip->cr1 |= SSCR1_LBM;

	अगर (spi->bits_per_word <= 8) अणु
		chip->n_bytes = 1;
		chip->पढ़ो = u8_पढ़ोer;
		chip->ग_लिखो = u8_ग_लिखोr;
	पूर्ण अन्यथा अगर (spi->bits_per_word <= 16) अणु
		chip->n_bytes = 2;
		chip->पढ़ो = u16_पढ़ोer;
		chip->ग_लिखो = u16_ग_लिखोr;
	पूर्ण अन्यथा अगर (spi->bits_per_word <= 32) अणु
		chip->n_bytes = 4;
		chip->पढ़ो = u32_पढ़ोer;
		chip->ग_लिखो = u32_ग_लिखोr;
	पूर्ण

	spi_set_ctldata(spi, chip);

	अगर (drv_data->ssp_type == CE4100_SSP)
		वापस 0;

	err = setup_cs(spi, chip, chip_info);
	अगर (err)
		kमुक्त(chip);

	वापस err;
पूर्ण

अटल व्योम cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा chip_data *chip = spi_get_ctldata(spi);
	काष्ठा driver_data *drv_data =
		spi_controller_get_devdata(spi->controller);

	अगर (!chip)
		वापस;

	अगर (drv_data->ssp_type != CE4100_SSP && !drv_data->cs_gpiods &&
	    chip->gpiod_cs)
		gpiod_put(chip->gpiod_cs);

	kमुक्त(chip);
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id pxa2xx_spi_acpi_match[] = अणु
	अणु "INT33C0", LPSS_LPT_SSP पूर्ण,
	अणु "INT33C1", LPSS_LPT_SSP पूर्ण,
	अणु "INT3430", LPSS_LPT_SSP पूर्ण,
	अणु "INT3431", LPSS_LPT_SSP पूर्ण,
	अणु "80860F0E", LPSS_BYT_SSP पूर्ण,
	अणु "8086228E", LPSS_BSW_SSP पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pxa2xx_spi_acpi_match);
#पूर्ण_अगर

/*
 * PCI IDs of compound devices that पूर्णांकegrate both host controller and निजी
 * पूर्णांकegrated DMA engine. Please note these are not used in module
 * स्वतःloading and probing in this module but matching the LPSS SSP type.
 */
अटल स्थिर काष्ठा pci_device_id pxa2xx_spi_pci_compound_match[] = अणु
	/* SPT-LP */
	अणु PCI_VDEVICE(INTEL, 0x9d29), LPSS_SPT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d2a), LPSS_SPT_SSP पूर्ण,
	/* SPT-H */
	अणु PCI_VDEVICE(INTEL, 0xa129), LPSS_SPT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa12a), LPSS_SPT_SSP पूर्ण,
	/* KBL-H */
	अणु PCI_VDEVICE(INTEL, 0xa2a9), LPSS_SPT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa2aa), LPSS_SPT_SSP पूर्ण,
	/* CML-V */
	अणु PCI_VDEVICE(INTEL, 0xa3a9), LPSS_SPT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3aa), LPSS_SPT_SSP पूर्ण,
	/* BXT A-Step */
	अणु PCI_VDEVICE(INTEL, 0x0ac2), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ac4), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ac6), LPSS_BXT_SSP पूर्ण,
	/* BXT B-Step */
	अणु PCI_VDEVICE(INTEL, 0x1ac2), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ac4), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ac6), LPSS_BXT_SSP पूर्ण,
	/* GLK */
	अणु PCI_VDEVICE(INTEL, 0x31c2), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31c4), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31c6), LPSS_BXT_SSP पूर्ण,
	/* ICL-LP */
	अणु PCI_VDEVICE(INTEL, 0x34aa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34ab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34fb), LPSS_CNL_SSP पूर्ण,
	/* EHL */
	अणु PCI_VDEVICE(INTEL, 0x4b2a), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b2b), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b37), LPSS_BXT_SSP पूर्ण,
	/* JSL */
	अणु PCI_VDEVICE(INTEL, 0x4daa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4dab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4dfb), LPSS_CNL_SSP पूर्ण,
	/* TGL-H */
	अणु PCI_VDEVICE(INTEL, 0x43aa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43ab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43fb), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43fd), LPSS_CNL_SSP पूर्ण,
	/* ADL-P */
	अणु PCI_VDEVICE(INTEL, 0x51aa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51ab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51fb), LPSS_CNL_SSP पूर्ण,
	/* ADL-M */
	अणु PCI_VDEVICE(INTEL, 0x54aa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x54ab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x54fb), LPSS_CNL_SSP पूर्ण,
	/* APL */
	अणु PCI_VDEVICE(INTEL, 0x5ac2), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ac4), LPSS_BXT_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ac6), LPSS_BXT_SSP पूर्ण,
	/* ADL-S */
	अणु PCI_VDEVICE(INTEL, 0x7aaa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7aab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7af9), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7afb), LPSS_CNL_SSP पूर्ण,
	/* CNL-LP */
	अणु PCI_VDEVICE(INTEL, 0x9daa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9dab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9dfb), LPSS_CNL_SSP पूर्ण,
	/* CNL-H */
	अणु PCI_VDEVICE(INTEL, 0xa32a), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa32b), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa37b), LPSS_CNL_SSP पूर्ण,
	/* CML-LP */
	अणु PCI_VDEVICE(INTEL, 0x02aa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02ab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02fb), LPSS_CNL_SSP पूर्ण,
	/* CML-H */
	अणु PCI_VDEVICE(INTEL, 0x06aa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06ab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06fb), LPSS_CNL_SSP पूर्ण,
	/* TGL-LP */
	अणु PCI_VDEVICE(INTEL, 0xa0aa), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0ab), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0de), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0df), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0fb), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0fd), LPSS_CNL_SSP पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0fe), LPSS_CNL_SSP पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pxa2xx_spi_of_match[] = अणु
	अणु .compatible = "marvell,mmp2-ssp", .data = (व्योम *)MMP2_SSP पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa2xx_spi_of_match);

#अगर_घोषित CONFIG_ACPI

अटल पूर्णांक pxa2xx_spi_get_port_id(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev;
	अचिन्हित पूर्णांक devid;
	पूर्णांक port_id = -1;

	adev = ACPI_COMPANION(dev);
	अगर (adev && adev->pnp.unique_id &&
	    !kstrtouपूर्णांक(adev->pnp.unique_id, 0, &devid))
		port_id = devid;
	वापस port_id;
पूर्ण

#अन्यथा /* !CONFIG_ACPI */

अटल पूर्णांक pxa2xx_spi_get_port_id(काष्ठा device *dev)
अणु
	वापस -1;
पूर्ण

#पूर्ण_अगर /* CONFIG_ACPI */


#अगर_घोषित CONFIG_PCI

अटल bool pxa2xx_spi_idma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	वापस param == chan->device->dev;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI */

अटल काष्ठा pxa2xx_spi_controller *
pxa2xx_spi_init_pdata(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa2xx_spi_controller *pdata;
	काष्ठा ssp_device *ssp;
	काष्ठा resource *res;
	काष्ठा device *parent = pdev->dev.parent;
	काष्ठा pci_dev *pcidev = dev_is_pci(parent) ? to_pci_dev(parent) : शून्य;
	स्थिर काष्ठा pci_device_id *pcidev_id = शून्य;
	क्रमागत pxa_ssp_type type;
	स्थिर व्योम *match;

	अगर (pcidev)
		pcidev_id = pci_match_id(pxa2xx_spi_pci_compound_match, pcidev);

	match = device_get_match_data(&pdev->dev);
	अगर (match)
		type = (क्रमागत pxa_ssp_type)match;
	अन्यथा अगर (pcidev_id)
		type = (क्रमागत pxa_ssp_type)pcidev_id->driver_data;
	अन्यथा
		वापस ERR_PTR(-EINVAL);

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	ssp = &pdata->ssp;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ssp->mmio_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ssp->mmio_base))
		वापस ERR_CAST(ssp->mmio_base);

	ssp->phys_base = res->start;

#अगर_घोषित CONFIG_PCI
	अगर (pcidev_id) अणु
		pdata->tx_param = parent;
		pdata->rx_param = parent;
		pdata->dma_filter = pxa2xx_spi_idma_filter;
	पूर्ण
#पूर्ण_अगर

	ssp->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ssp->clk))
		वापस ERR_CAST(ssp->clk);

	ssp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ssp->irq < 0)
		वापस ERR_PTR(ssp->irq);

	ssp->type = type;
	ssp->dev = &pdev->dev;
	ssp->port_id = pxa2xx_spi_get_port_id(&pdev->dev);

	pdata->is_slave = device_property_पढ़ो_bool(&pdev->dev, "spi-slave");
	pdata->num_chipselect = 1;
	pdata->enable_dma = true;
	pdata->dma_burst_size = 1;

	वापस pdata;
पूर्ण

अटल पूर्णांक pxa2xx_spi_fw_translate_cs(काष्ठा spi_controller *controller,
				      अचिन्हित पूर्णांक cs)
अणु
	काष्ठा driver_data *drv_data = spi_controller_get_devdata(controller);

	अगर (has_acpi_companion(&drv_data->pdev->dev)) अणु
		चयन (drv_data->ssp_type) अणु
		/*
		 * For Atoms the ACPI DeviceSelection used by the Winकरोws
		 * driver starts from 1 instead of 0 so translate it here
		 * to match what Linux expects.
		 */
		हाल LPSS_BYT_SSP:
		हाल LPSS_BSW_SSP:
			वापस cs - 1;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस cs;
पूर्ण

अटल माप_प्रकार pxa2xx_spi_max_dma_transfer_size(काष्ठा spi_device *spi)
अणु
	वापस MAX_DMA_LEN;
पूर्ण

अटल पूर्णांक pxa2xx_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pxa2xx_spi_controller *platक्रमm_info;
	काष्ठा spi_controller *controller;
	काष्ठा driver_data *drv_data;
	काष्ठा ssp_device *ssp;
	स्थिर काष्ठा lpss_config *config;
	पूर्णांक status, count;
	u32 पंचांगp;

	platक्रमm_info = dev_get_platdata(dev);
	अगर (!platक्रमm_info) अणु
		platक्रमm_info = pxa2xx_spi_init_pdata(pdev);
		अगर (IS_ERR(platक्रमm_info)) अणु
			dev_err(&pdev->dev, "missing platform data\n");
			वापस PTR_ERR(platक्रमm_info);
		पूर्ण
	पूर्ण

	ssp = pxa_ssp_request(pdev->id, pdev->name);
	अगर (!ssp)
		ssp = &platक्रमm_info->ssp;

	अगर (!ssp->mmio_base) अणु
		dev_err(&pdev->dev, "failed to get ssp\n");
		वापस -ENODEV;
	पूर्ण

	अगर (platक्रमm_info->is_slave)
		controller = devm_spi_alloc_slave(dev, माप(*drv_data));
	अन्यथा
		controller = devm_spi_alloc_master(dev, माप(*drv_data));

	अगर (!controller) अणु
		dev_err(&pdev->dev, "cannot alloc spi_controller\n");
		pxa_ssp_मुक्त(ssp);
		वापस -ENOMEM;
	पूर्ण
	drv_data = spi_controller_get_devdata(controller);
	drv_data->controller = controller;
	drv_data->controller_info = platक्रमm_info;
	drv_data->pdev = pdev;
	drv_data->ssp = ssp;

	controller->dev.of_node = pdev->dev.of_node;
	/* the spi->mode bits understood by this driver: */
	controller->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LOOP;

	controller->bus_num = ssp->port_id;
	controller->dma_alignment = DMA_ALIGNMENT;
	controller->cleanup = cleanup;
	controller->setup = setup;
	controller->set_cs = pxa2xx_spi_set_cs;
	controller->transfer_one = pxa2xx_spi_transfer_one;
	controller->slave_पात = pxa2xx_spi_slave_पात;
	controller->handle_err = pxa2xx_spi_handle_err;
	controller->unprepare_transfer_hardware = pxa2xx_spi_unprepare_transfer;
	controller->fw_translate_cs = pxa2xx_spi_fw_translate_cs;
	controller->स्वतः_runसमय_pm = true;
	controller->flags = SPI_CONTROLLER_MUST_RX | SPI_CONTROLLER_MUST_TX;

	drv_data->ssp_type = ssp->type;

	drv_data->ioaddr = ssp->mmio_base;
	drv_data->ssdr_physical = ssp->phys_base + SSDR;
	अगर (pxa25x_ssp_comp(drv_data)) अणु
		चयन (drv_data->ssp_type) अणु
		हाल QUARK_X1000_SSP:
			controller->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
			अवरोध;
		शेष:
			controller->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 16);
			अवरोध;
		पूर्ण

		drv_data->पूर्णांक_cr1 = SSCR1_TIE | SSCR1_RIE;
		drv_data->dma_cr1 = 0;
		drv_data->clear_sr = SSSR_ROR;
		drv_data->mask_sr = SSSR_RFS | SSSR_TFS | SSSR_ROR;
	पूर्ण अन्यथा अणु
		controller->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
		drv_data->पूर्णांक_cr1 = SSCR1_TIE | SSCR1_RIE | SSCR1_TINTE;
		drv_data->dma_cr1 = DEFAULT_DMA_CR1;
		drv_data->clear_sr = SSSR_ROR | SSSR_TINT;
		drv_data->mask_sr = SSSR_TINT | SSSR_RFS | SSSR_TFS
						| SSSR_ROR | SSSR_TUR;
	पूर्ण

	status = request_irq(ssp->irq, ssp_पूर्णांक, IRQF_SHARED, dev_name(dev),
			drv_data);
	अगर (status < 0) अणु
		dev_err(&pdev->dev, "cannot get IRQ %d\n", ssp->irq);
		जाओ out_error_controller_alloc;
	पूर्ण

	/* Setup DMA अगर requested */
	अगर (platक्रमm_info->enable_dma) अणु
		status = pxa2xx_spi_dma_setup(drv_data);
		अगर (status) अणु
			dev_warn(dev, "no DMA channels available, using PIO\n");
			platक्रमm_info->enable_dma = false;
		पूर्ण अन्यथा अणु
			controller->can_dma = pxa2xx_spi_can_dma;
			controller->max_dma_len = MAX_DMA_LEN;
			controller->max_transfer_size =
				pxa2xx_spi_max_dma_transfer_size;
		पूर्ण
	पूर्ण

	/* Enable SOC घड़ी */
	status = clk_prepare_enable(ssp->clk);
	अगर (status)
		जाओ out_error_dma_irq_alloc;

	controller->max_speed_hz = clk_get_rate(ssp->clk);
	/*
	 * Set minimum speed क्रम all other platक्रमms than Intel Quark which is
	 * able करो under 1 Hz transfers.
	 */
	अगर (!pxa25x_ssp_comp(drv_data))
		controller->min_speed_hz =
			DIV_ROUND_UP(controller->max_speed_hz, 4096);
	अन्यथा अगर (!is_quark_x1000_ssp(drv_data))
		controller->min_speed_hz =
			DIV_ROUND_UP(controller->max_speed_hz, 512);

	/* Load शेष SSP configuration */
	pxa2xx_spi_ग_लिखो(drv_data, SSCR0, 0);
	चयन (drv_data->ssp_type) अणु
	हाल QUARK_X1000_SSP:
		पंचांगp = QUARK_X1000_SSCR1_RxTresh(RX_THRESH_QUARK_X1000_DFLT) |
		      QUARK_X1000_SSCR1_TxTresh(TX_THRESH_QUARK_X1000_DFLT);
		pxa2xx_spi_ग_लिखो(drv_data, SSCR1, पंचांगp);

		/* using the Motorola SPI protocol and use 8 bit frame */
		पंचांगp = QUARK_X1000_SSCR0_Motorola | QUARK_X1000_SSCR0_DataSize(8);
		pxa2xx_spi_ग_लिखो(drv_data, SSCR0, पंचांगp);
		अवरोध;
	हाल CE4100_SSP:
		पंचांगp = CE4100_SSCR1_RxTresh(RX_THRESH_CE4100_DFLT) |
		      CE4100_SSCR1_TxTresh(TX_THRESH_CE4100_DFLT);
		pxa2xx_spi_ग_लिखो(drv_data, SSCR1, पंचांगp);
		पंचांगp = SSCR0_SCR(2) | SSCR0_Motorola | SSCR0_DataSize(8);
		pxa2xx_spi_ग_लिखो(drv_data, SSCR0, पंचांगp);
		अवरोध;
	शेष:

		अगर (spi_controller_is_slave(controller)) अणु
			पंचांगp = SSCR1_SCFR |
			      SSCR1_SCLKसूची |
			      SSCR1_SFRMसूची |
			      SSCR1_RxTresh(2) |
			      SSCR1_TxTresh(1) |
			      SSCR1_SPH;
		पूर्ण अन्यथा अणु
			पंचांगp = SSCR1_RxTresh(RX_THRESH_DFLT) |
			      SSCR1_TxTresh(TX_THRESH_DFLT);
		पूर्ण
		pxa2xx_spi_ग_लिखो(drv_data, SSCR1, पंचांगp);
		पंचांगp = SSCR0_Motorola | SSCR0_DataSize(8);
		अगर (!spi_controller_is_slave(controller))
			पंचांगp |= SSCR0_SCR(2);
		pxa2xx_spi_ग_लिखो(drv_data, SSCR0, पंचांगp);
		अवरोध;
	पूर्ण

	अगर (!pxa25x_ssp_comp(drv_data))
		pxa2xx_spi_ग_लिखो(drv_data, SSTO, 0);

	अगर (!is_quark_x1000_ssp(drv_data))
		pxa2xx_spi_ग_लिखो(drv_data, SSPSP, 0);

	अगर (is_lpss_ssp(drv_data)) अणु
		lpss_ssp_setup(drv_data);
		config = lpss_get_config(drv_data);
		अगर (config->reg_capabilities >= 0) अणु
			पंचांगp = __lpss_ssp_पढ़ो_priv(drv_data,
						   config->reg_capabilities);
			पंचांगp &= LPSS_CAPS_CS_EN_MASK;
			पंचांगp >>= LPSS_CAPS_CS_EN_SHIFT;
			platक्रमm_info->num_chipselect = ffz(पंचांगp);
		पूर्ण अन्यथा अगर (config->cs_num) अणु
			platक्रमm_info->num_chipselect = config->cs_num;
		पूर्ण
	पूर्ण
	controller->num_chipselect = platक्रमm_info->num_chipselect;

	count = gpiod_count(&pdev->dev, "cs");
	अगर (count > 0) अणु
		पूर्णांक i;

		controller->num_chipselect = max_t(पूर्णांक, count,
			controller->num_chipselect);

		drv_data->cs_gpiods = devm_kसुस्मृति(&pdev->dev,
			controller->num_chipselect, माप(काष्ठा gpio_desc *),
			GFP_KERNEL);
		अगर (!drv_data->cs_gpiods) अणु
			status = -ENOMEM;
			जाओ out_error_घड़ी_enabled;
		पूर्ण

		क्रम (i = 0; i < controller->num_chipselect; i++) अणु
			काष्ठा gpio_desc *gpiod;

			gpiod = devm_gpiod_get_index(dev, "cs", i, GPIOD_ASIS);
			अगर (IS_ERR(gpiod)) अणु
				/* Means use native chip select */
				अगर (PTR_ERR(gpiod) == -ENOENT)
					जारी;

				status = PTR_ERR(gpiod);
				जाओ out_error_घड़ी_enabled;
			पूर्ण अन्यथा अणु
				drv_data->cs_gpiods[i] = gpiod;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (platक्रमm_info->is_slave) अणु
		drv_data->gpiod_पढ़ोy = devm_gpiod_get_optional(dev,
						"ready", GPIOD_OUT_LOW);
		अगर (IS_ERR(drv_data->gpiod_पढ़ोy)) अणु
			status = PTR_ERR(drv_data->gpiod_पढ़ोy);
			जाओ out_error_घड़ी_enabled;
		पूर्ण
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	/* Register with the SPI framework */
	platक्रमm_set_drvdata(pdev, drv_data);
	status = spi_रेजिस्टर_controller(controller);
	अगर (status != 0) अणु
		dev_err(&pdev->dev, "problem registering spi controller\n");
		जाओ out_error_pm_runसमय_enabled;
	पूर्ण

	वापस status;

out_error_pm_runसमय_enabled:
	pm_runसमय_disable(&pdev->dev);

out_error_घड़ी_enabled:
	clk_disable_unprepare(ssp->clk);

out_error_dma_irq_alloc:
	pxa2xx_spi_dma_release(drv_data);
	मुक्त_irq(ssp->irq, drv_data);

out_error_controller_alloc:
	pxa_ssp_मुक्त(ssp);
	वापस status;
पूर्ण

अटल पूर्णांक pxa2xx_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा driver_data *drv_data = platक्रमm_get_drvdata(pdev);
	काष्ठा ssp_device *ssp = drv_data->ssp;

	pm_runसमय_get_sync(&pdev->dev);

	spi_unरेजिस्टर_controller(drv_data->controller);

	/* Disable the SSP at the peripheral and SOC level */
	pxa2xx_spi_ग_लिखो(drv_data, SSCR0, 0);
	clk_disable_unprepare(ssp->clk);

	/* Release DMA */
	अगर (drv_data->controller_info->enable_dma)
		pxa2xx_spi_dma_release(drv_data);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	/* Release IRQ */
	मुक्त_irq(ssp->irq, drv_data);

	/* Release SSP */
	pxa_ssp_मुक्त(ssp);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pxa2xx_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा driver_data *drv_data = dev_get_drvdata(dev);
	काष्ठा ssp_device *ssp = drv_data->ssp;
	पूर्णांक status;

	status = spi_controller_suspend(drv_data->controller);
	अगर (status != 0)
		वापस status;
	pxa2xx_spi_ग_लिखो(drv_data, SSCR0, 0);

	अगर (!pm_runसमय_suspended(dev))
		clk_disable_unprepare(ssp->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा driver_data *drv_data = dev_get_drvdata(dev);
	काष्ठा ssp_device *ssp = drv_data->ssp;
	पूर्णांक status;

	/* Enable the SSP घड़ी */
	अगर (!pm_runसमय_suspended(dev)) अणु
		status = clk_prepare_enable(ssp->clk);
		अगर (status)
			वापस status;
	पूर्ण

	/* Start the queue running */
	वापस spi_controller_resume(drv_data->controller);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pxa2xx_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा driver_data *drv_data = dev_get_drvdata(dev);

	clk_disable_unprepare(drv_data->ssp->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा driver_data *drv_data = dev_get_drvdata(dev);
	पूर्णांक status;

	status = clk_prepare_enable(drv_data->ssp->clk);
	वापस status;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops pxa2xx_spi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pxa2xx_spi_suspend, pxa2xx_spi_resume)
	SET_RUNTIME_PM_OPS(pxa2xx_spi_runसमय_suspend,
			   pxa2xx_spi_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver driver = अणु
	.driver = अणु
		.name	= "pxa2xx-spi",
		.pm	= &pxa2xx_spi_pm_ops,
		.acpi_match_table = ACPI_PTR(pxa2xx_spi_acpi_match),
		.of_match_table = of_match_ptr(pxa2xx_spi_of_match),
	पूर्ण,
	.probe = pxa2xx_spi_probe,
	.हटाओ = pxa2xx_spi_हटाओ,
पूर्ण;

अटल पूर्णांक __init pxa2xx_spi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&driver);
पूर्ण
subsys_initcall(pxa2xx_spi_init);

अटल व्योम __निकास pxa2xx_spi_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&driver);
पूर्ण
module_निकास(pxa2xx_spi_निकास);

MODULE_SOFTDEP("pre: dw_dmac");
