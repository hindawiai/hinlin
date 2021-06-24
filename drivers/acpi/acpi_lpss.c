<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI support क्रम Intel Lynxpoपूर्णांक LPSS.
 *
 * Copyright (C) 2013, Intel Corporation
 * Authors: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 *          Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/dmi.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/x86/clk-lpss.h>
#समावेश <linux/platक्रमm_data/x86/pmc_atom.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pwm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/delay.h>

#समावेश "internal.h"

#अगर_घोषित CONFIG_X86_INTEL_LPSS

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/iosf_mbi.h>

#घोषणा LPSS_ADDR(desc) ((अचिन्हित दीर्घ)&desc)

#घोषणा LPSS_CLK_SIZE	0x04
#घोषणा LPSS_LTR_SIZE	0x18

/* Offsets relative to LPSS_PRIVATE_OFFSET */
#घोषणा LPSS_CLK_DIVIDER_DEF_MASK	(BIT(1) | BIT(16))
#घोषणा LPSS_RESETS			0x04
#घोषणा LPSS_RESETS_RESET_FUNC		BIT(0)
#घोषणा LPSS_RESETS_RESET_APB		BIT(1)
#घोषणा LPSS_GENERAL			0x08
#घोषणा LPSS_GENERAL_LTR_MODE_SW	BIT(2)
#घोषणा LPSS_GENERAL_UART_RTS_OVRD	BIT(3)
#घोषणा LPSS_SW_LTR			0x10
#घोषणा LPSS_AUTO_LTR			0x14
#घोषणा LPSS_LTR_SNOOP_REQ		BIT(15)
#घोषणा LPSS_LTR_SNOOP_MASK		0x0000FFFF
#घोषणा LPSS_LTR_SNOOP_LAT_1US		0x800
#घोषणा LPSS_LTR_SNOOP_LAT_32US		0xC00
#घोषणा LPSS_LTR_SNOOP_LAT_SHIFT	5
#घोषणा LPSS_LTR_SNOOP_LAT_CUTOFF	3000
#घोषणा LPSS_LTR_MAX_VAL		0x3FF
#घोषणा LPSS_TX_INT			0x20
#घोषणा LPSS_TX_INT_MASK		BIT(1)

#घोषणा LPSS_PRV_REG_COUNT		9

/* LPSS Flags */
#घोषणा LPSS_CLK			BIT(0)
#घोषणा LPSS_CLK_GATE			BIT(1)
#घोषणा LPSS_CLK_DIVIDER		BIT(2)
#घोषणा LPSS_LTR			BIT(3)
#घोषणा LPSS_SAVE_CTX			BIT(4)
/*
 * For some devices the DSDT AML code क्रम another device turns off the device
 * beक्रमe our suspend handler runs, causing us to पढ़ो/save all 1-s (0xffffffff)
 * as ctx रेजिस्टर values.
 * Luckily these devices always use the same ctx रेजिस्टर values, so we can
 * work around this by saving the ctx रेजिस्टरs once on activation.
 */
#घोषणा LPSS_SAVE_CTX_ONCE		BIT(5)
#घोषणा LPSS_NO_D3_DELAY		BIT(6)

काष्ठा lpss_निजी_data;

काष्ठा lpss_device_desc अणु
	अचिन्हित पूर्णांक flags;
	स्थिर अक्षर *clk_con_id;
	अचिन्हित पूर्णांक prv_offset;
	माप_प्रकार prv_size_override;
	काष्ठा property_entry *properties;
	व्योम (*setup)(काष्ठा lpss_निजी_data *pdata);
	bool resume_from_noirq;
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc lpss_dma_desc = अणु
	.flags = LPSS_CLK,
पूर्ण;

काष्ठा lpss_निजी_data अणु
	काष्ठा acpi_device *adev;
	व्योम __iomem *mmio_base;
	resource_माप_प्रकार mmio_size;
	अचिन्हित पूर्णांक fixed_clk_rate;
	काष्ठा clk *clk;
	स्थिर काष्ठा lpss_device_desc *dev_desc;
	u32 prv_reg_ctx[LPSS_PRV_REG_COUNT];
पूर्ण;

/* Devices which need to be in D3 beक्रमe lpss_iosf_enter_d3_state() proceeds */
अटल u32 pmc_atom_d3_mask = 0xfe000ffe;

/* LPSS run समय quirks */
अटल अचिन्हित पूर्णांक lpss_quirks;

/*
 * LPSS_QUIRK_ALWAYS_POWER_ON: override घातer state क्रम LPSS DMA device.
 *
 * The LPSS DMA controller has neither _PS0 nor _PS3 method. Moreover
 * it can be घातered off स्वतःmatically whenever the last LPSS device goes करोwn.
 * In हाल of no घातer any access to the DMA controller will hang the प्रणाली.
 * The behaviour is reproduced on some HP laptops based on Intel BayTrail as
 * well as on ASuS T100TA transक्रमmer.
 *
 * This quirk overrides घातer state of entire LPSS island to keep DMA घातered
 * on whenever we have at least one other device in use.
 */
#घोषणा LPSS_QUIRK_ALWAYS_POWER_ON	BIT(0)

/* UART Component Parameter Register */
#घोषणा LPSS_UART_CPR			0xF4
#घोषणा LPSS_UART_CPR_AFCE		BIT(4)

अटल व्योम lpss_uart_setup(काष्ठा lpss_निजी_data *pdata)
अणु
	अचिन्हित पूर्णांक offset;
	u32 val;

	offset = pdata->dev_desc->prv_offset + LPSS_TX_INT;
	val = पढ़ोl(pdata->mmio_base + offset);
	ग_लिखोl(val | LPSS_TX_INT_MASK, pdata->mmio_base + offset);

	val = पढ़ोl(pdata->mmio_base + LPSS_UART_CPR);
	अगर (!(val & LPSS_UART_CPR_AFCE)) अणु
		offset = pdata->dev_desc->prv_offset + LPSS_GENERAL;
		val = पढ़ोl(pdata->mmio_base + offset);
		val |= LPSS_GENERAL_UART_RTS_OVRD;
		ग_लिखोl(val, pdata->mmio_base + offset);
	पूर्ण
पूर्ण

अटल व्योम lpss_deनिश्चित_reset(काष्ठा lpss_निजी_data *pdata)
अणु
	अचिन्हित पूर्णांक offset;
	u32 val;

	offset = pdata->dev_desc->prv_offset + LPSS_RESETS;
	val = पढ़ोl(pdata->mmio_base + offset);
	val |= LPSS_RESETS_RESET_APB | LPSS_RESETS_RESET_FUNC;
	ग_लिखोl(val, pdata->mmio_base + offset);
पूर्ण

/*
 * BYT PWM used क्रम backlight control by the i915 driver on प्रणालीs without
 * the Crystal Cove PMIC.
 */
अटल काष्ठा pwm_lookup byt_pwm_lookup[] = अणु
	PWM_LOOKUP_WITH_MODULE("80860F09:00", 0, "0000:00:02.0",
			       "pwm_soc_backlight", 0, PWM_POLARITY_NORMAL,
			       "pwm-lpss-platform"),
पूर्ण;

अटल व्योम byt_pwm_setup(काष्ठा lpss_निजी_data *pdata)
अणु
	काष्ठा acpi_device *adev = pdata->adev;

	/* Only call pwm_add_table क्रम the first PWM controller */
	अगर (!adev->pnp.unique_id || म_भेद(adev->pnp.unique_id, "1"))
		वापस;

	pwm_add_table(byt_pwm_lookup, ARRAY_SIZE(byt_pwm_lookup));
पूर्ण

#घोषणा LPSS_I2C_ENABLE			0x6c

अटल व्योम byt_i2c_setup(काष्ठा lpss_निजी_data *pdata)
अणु
	स्थिर अक्षर *uid_str = acpi_device_uid(pdata->adev);
	acpi_handle handle = pdata->adev->handle;
	अचिन्हित दीर्घ दीर्घ shared_host = 0;
	acpi_status status;
	दीर्घ uid = 0;

	/* Expected to always be true, but better safe then sorry */
	अगर (uid_str)
		uid = simple_म_से_दीर्घ(uid_str, शून्य, 10);

	/* Detect I2C bus shared with PUNIT and ignore its d3 status */
	status = acpi_evaluate_पूर्णांकeger(handle, "_SEM", शून्य, &shared_host);
	अगर (ACPI_SUCCESS(status) && shared_host && uid)
		pmc_atom_d3_mask &= ~(BIT_LPSS2_F1_I2C1 << (uid - 1));

	lpss_deनिश्चित_reset(pdata);

	अगर (पढ़ोl(pdata->mmio_base + pdata->dev_desc->prv_offset))
		pdata->fixed_clk_rate = 133000000;

	ग_लिखोl(0, pdata->mmio_base + LPSS_I2C_ENABLE);
पूर्ण

/* BSW PWM used क्रम backlight control by the i915 driver */
अटल काष्ठा pwm_lookup bsw_pwm_lookup[] = अणु
	PWM_LOOKUP_WITH_MODULE("80862288:00", 0, "0000:00:02.0",
			       "pwm_soc_backlight", 0, PWM_POLARITY_NORMAL,
			       "pwm-lpss-platform"),
पूर्ण;

अटल व्योम bsw_pwm_setup(काष्ठा lpss_निजी_data *pdata)
अणु
	काष्ठा acpi_device *adev = pdata->adev;

	/* Only call pwm_add_table क्रम the first PWM controller */
	अगर (!adev->pnp.unique_id || म_भेद(adev->pnp.unique_id, "1"))
		वापस;

	pwm_add_table(bsw_pwm_lookup, ARRAY_SIZE(bsw_pwm_lookup));
पूर्ण

अटल स्थिर काष्ठा lpss_device_desc lpt_dev_desc = अणु
	.flags = LPSS_CLK | LPSS_CLK_GATE | LPSS_CLK_DIVIDER | LPSS_LTR
			| LPSS_SAVE_CTX,
	.prv_offset = 0x800,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc lpt_i2c_dev_desc = अणु
	.flags = LPSS_CLK | LPSS_CLK_GATE | LPSS_LTR | LPSS_SAVE_CTX,
	.prv_offset = 0x800,
पूर्ण;

अटल काष्ठा property_entry uart_properties[] = अणु
	PROPERTY_ENTRY_U32("reg-io-width", 4),
	PROPERTY_ENTRY_U32("reg-shift", 2),
	PROPERTY_ENTRY_BOOL("snps,uart-16550-compatible"),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc lpt_uart_dev_desc = अणु
	.flags = LPSS_CLK | LPSS_CLK_GATE | LPSS_CLK_DIVIDER | LPSS_LTR
			| LPSS_SAVE_CTX,
	.clk_con_id = "baudclk",
	.prv_offset = 0x800,
	.setup = lpss_uart_setup,
	.properties = uart_properties,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc lpt_sdio_dev_desc = अणु
	.flags = LPSS_LTR,
	.prv_offset = 0x1000,
	.prv_size_override = 0x1018,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc byt_pwm_dev_desc = अणु
	.flags = LPSS_SAVE_CTX,
	.prv_offset = 0x800,
	.setup = byt_pwm_setup,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc bsw_pwm_dev_desc = अणु
	.flags = LPSS_SAVE_CTX_ONCE | LPSS_NO_D3_DELAY,
	.prv_offset = 0x800,
	.setup = bsw_pwm_setup,
	.resume_from_noirq = true,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc byt_uart_dev_desc = अणु
	.flags = LPSS_CLK | LPSS_CLK_GATE | LPSS_CLK_DIVIDER | LPSS_SAVE_CTX,
	.clk_con_id = "baudclk",
	.prv_offset = 0x800,
	.setup = lpss_uart_setup,
	.properties = uart_properties,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc bsw_uart_dev_desc = अणु
	.flags = LPSS_CLK | LPSS_CLK_GATE | LPSS_CLK_DIVIDER | LPSS_SAVE_CTX
			| LPSS_NO_D3_DELAY,
	.clk_con_id = "baudclk",
	.prv_offset = 0x800,
	.setup = lpss_uart_setup,
	.properties = uart_properties,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc byt_spi_dev_desc = अणु
	.flags = LPSS_CLK | LPSS_CLK_GATE | LPSS_CLK_DIVIDER | LPSS_SAVE_CTX,
	.prv_offset = 0x400,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc byt_sdio_dev_desc = अणु
	.flags = LPSS_CLK,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc byt_i2c_dev_desc = अणु
	.flags = LPSS_CLK | LPSS_SAVE_CTX,
	.prv_offset = 0x800,
	.setup = byt_i2c_setup,
	.resume_from_noirq = true,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc bsw_i2c_dev_desc = अणु
	.flags = LPSS_CLK | LPSS_SAVE_CTX | LPSS_NO_D3_DELAY,
	.prv_offset = 0x800,
	.setup = byt_i2c_setup,
	.resume_from_noirq = true,
पूर्ण;

अटल स्थिर काष्ठा lpss_device_desc bsw_spi_dev_desc = अणु
	.flags = LPSS_CLK | LPSS_CLK_GATE | LPSS_CLK_DIVIDER | LPSS_SAVE_CTX
			| LPSS_NO_D3_DELAY,
	.prv_offset = 0x400,
	.setup = lpss_deनिश्चित_reset,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id lpss_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT,	शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT,	शून्य),
	अणुपूर्ण
पूर्ण;

#अन्यथा

#घोषणा LPSS_ADDR(desc) (0UL)

#पूर्ण_अगर /* CONFIG_X86_INTEL_LPSS */

अटल स्थिर काष्ठा acpi_device_id acpi_lpss_device_ids[] = अणु
	/* Generic LPSS devices */
	अणु "INTL9C60", LPSS_ADDR(lpss_dma_desc) पूर्ण,

	/* Lynxpoपूर्णांक LPSS devices */
	अणु "INT33C0", LPSS_ADDR(lpt_dev_desc) पूर्ण,
	अणु "INT33C1", LPSS_ADDR(lpt_dev_desc) पूर्ण,
	अणु "INT33C2", LPSS_ADDR(lpt_i2c_dev_desc) पूर्ण,
	अणु "INT33C3", LPSS_ADDR(lpt_i2c_dev_desc) पूर्ण,
	अणु "INT33C4", LPSS_ADDR(lpt_uart_dev_desc) पूर्ण,
	अणु "INT33C5", LPSS_ADDR(lpt_uart_dev_desc) पूर्ण,
	अणु "INT33C6", LPSS_ADDR(lpt_sdio_dev_desc) पूर्ण,
	अणु "INT33C7", पूर्ण,

	/* BayTrail LPSS devices */
	अणु "80860F09", LPSS_ADDR(byt_pwm_dev_desc) पूर्ण,
	अणु "80860F0A", LPSS_ADDR(byt_uart_dev_desc) पूर्ण,
	अणु "80860F0E", LPSS_ADDR(byt_spi_dev_desc) पूर्ण,
	अणु "80860F14", LPSS_ADDR(byt_sdio_dev_desc) पूर्ण,
	अणु "80860F41", LPSS_ADDR(byt_i2c_dev_desc) पूर्ण,
	अणु "INT33B2", पूर्ण,
	अणु "INT33FC", पूर्ण,

	/* Braswell LPSS devices */
	अणु "80862286", LPSS_ADDR(lpss_dma_desc) पूर्ण,
	अणु "80862288", LPSS_ADDR(bsw_pwm_dev_desc) पूर्ण,
	अणु "8086228A", LPSS_ADDR(bsw_uart_dev_desc) पूर्ण,
	अणु "8086228E", LPSS_ADDR(bsw_spi_dev_desc) पूर्ण,
	अणु "808622C0", LPSS_ADDR(lpss_dma_desc) पूर्ण,
	अणु "808622C1", LPSS_ADDR(bsw_i2c_dev_desc) पूर्ण,

	/* Broadwell LPSS devices */
	अणु "INT3430", LPSS_ADDR(lpt_dev_desc) पूर्ण,
	अणु "INT3431", LPSS_ADDR(lpt_dev_desc) पूर्ण,
	अणु "INT3432", LPSS_ADDR(lpt_i2c_dev_desc) पूर्ण,
	अणु "INT3433", LPSS_ADDR(lpt_i2c_dev_desc) पूर्ण,
	अणु "INT3434", LPSS_ADDR(lpt_uart_dev_desc) पूर्ण,
	अणु "INT3435", LPSS_ADDR(lpt_uart_dev_desc) पूर्ण,
	अणु "INT3436", LPSS_ADDR(lpt_sdio_dev_desc) पूर्ण,
	अणु "INT3437", पूर्ण,

	/* Wildcat Poपूर्णांक LPSS devices */
	अणु "INT3438", LPSS_ADDR(lpt_dev_desc) पूर्ण,

	अणु पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_X86_INTEL_LPSS

अटल पूर्णांक is_memory(काष्ठा acpi_resource *res, व्योम *not_used)
अणु
	काष्ठा resource r;

	वापस !acpi_dev_resource_memory(res, &r);
पूर्ण

/* LPSS मुख्य घड़ी device. */
अटल काष्ठा platक्रमm_device *lpss_clk_dev;

अटल अंतरभूत व्योम lpt_रेजिस्टर_घड़ी_device(व्योम)
अणु
	lpss_clk_dev = platक्रमm_device_रेजिस्टर_simple("clk-lpt", -1, शून्य, 0);
पूर्ण

अटल पूर्णांक रेजिस्टर_device_घड़ी(काष्ठा acpi_device *adev,
				 काष्ठा lpss_निजी_data *pdata)
अणु
	स्थिर काष्ठा lpss_device_desc *dev_desc = pdata->dev_desc;
	स्थिर अक्षर *devname = dev_name(&adev->dev);
	काष्ठा clk *clk;
	काष्ठा lpss_clk_data *clk_data;
	स्थिर अक्षर *parent, *clk_name;
	व्योम __iomem *prv_base;

	अगर (!lpss_clk_dev)
		lpt_रेजिस्टर_घड़ी_device();

	clk_data = platक्रमm_get_drvdata(lpss_clk_dev);
	अगर (!clk_data)
		वापस -ENODEV;
	clk = clk_data->clk;

	अगर (!pdata->mmio_base
	    || pdata->mmio_size < dev_desc->prv_offset + LPSS_CLK_SIZE)
		वापस -ENODATA;

	parent = clk_data->name;
	prv_base = pdata->mmio_base + dev_desc->prv_offset;

	अगर (pdata->fixed_clk_rate) अणु
		clk = clk_रेजिस्टर_fixed_rate(शून्य, devname, parent, 0,
					      pdata->fixed_clk_rate);
		जाओ out;
	पूर्ण

	अगर (dev_desc->flags & LPSS_CLK_GATE) अणु
		clk = clk_रेजिस्टर_gate(शून्य, devname, parent, 0,
					prv_base, 0, 0, शून्य);
		parent = devname;
	पूर्ण

	अगर (dev_desc->flags & LPSS_CLK_DIVIDER) अणु
		/* Prevent भागision by zero */
		अगर (!पढ़ोl(prv_base))
			ग_लिखोl(LPSS_CLK_DIVIDER_DEF_MASK, prv_base);

		clk_name = kaप्र_लिखो(GFP_KERNEL, "%s-div", devname);
		अगर (!clk_name)
			वापस -ENOMEM;
		clk = clk_रेजिस्टर_fractional_भागider(शून्य, clk_name, parent,
						      0, prv_base,
						      1, 15, 16, 15, 0, शून्य);
		parent = clk_name;

		clk_name = kaप्र_लिखो(GFP_KERNEL, "%s-update", devname);
		अगर (!clk_name) अणु
			kमुक्त(parent);
			वापस -ENOMEM;
		पूर्ण
		clk = clk_रेजिस्टर_gate(शून्य, clk_name, parent,
					CLK_SET_RATE_PARENT | CLK_SET_RATE_GATE,
					prv_base, 31, 0, शून्य);
		kमुक्त(parent);
		kमुक्त(clk_name);
	पूर्ण
out:
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	pdata->clk = clk;
	clk_रेजिस्टर_clkdev(clk, dev_desc->clk_con_id, devname);
	वापस 0;
पूर्ण

काष्ठा lpss_device_links अणु
	स्थिर अक्षर *supplier_hid;
	स्थिर अक्षर *supplier_uid;
	स्थिर अक्षर *consumer_hid;
	स्थिर अक्षर *consumer_uid;
	u32 flags;
	स्थिर काष्ठा dmi_प्रणाली_id *dep_missing_ids;
पूर्ण;

/* Please keep this list sorted alphabetically by venकरोr and model */
अटल स्थिर काष्ठा dmi_प्रणाली_id i2c1_dep_missing_dmi_ids[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "T200TA"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * The _DEP method is used to identअगरy dependencies but instead of creating
 * device links क्रम every handle in _DEP, only links in the following list are
 * created. That is necessary because, in the general हाल, _DEP can refer to
 * devices that might not have drivers, or that are on dअगरferent buses, or where
 * the supplier is not क्रमागतerated until after the consumer is probed.
 */
अटल स्थिर काष्ठा lpss_device_links lpss_device_links[] = अणु
	/* CHT External sdcard slot controller depends on PMIC I2C ctrl */
	अणु"808622C1", "7", "80860F14", "3", DL_FLAG_PM_RUNTIMEपूर्ण,
	/* CHT iGPU depends on PMIC I2C controller */
	अणु"808622C1", "7", "LNXVIDEO", शून्य, DL_FLAG_PM_RUNTIMEपूर्ण,
	/* BYT iGPU depends on the Embedded Controller I2C controller (UID 1) */
	अणु"80860F41", "1", "LNXVIDEO", शून्य, DL_FLAG_PM_RUNTIME,
	 i2c1_dep_missing_dmi_idsपूर्ण,
	/* BYT CR iGPU depends on PMIC I2C controller (UID 5 on CR) */
	अणु"80860F41", "5", "LNXVIDEO", शून्य, DL_FLAG_PM_RUNTIMEपूर्ण,
	/* BYT iGPU depends on PMIC I2C controller (UID 7 on non CR) */
	अणु"80860F41", "7", "LNXVIDEO", शून्य, DL_FLAG_PM_RUNTIMEपूर्ण,
पूर्ण;

अटल bool acpi_lpss_is_supplier(काष्ठा acpi_device *adev,
				  स्थिर काष्ठा lpss_device_links *link)
अणु
	वापस acpi_dev_hid_uid_match(adev, link->supplier_hid, link->supplier_uid);
पूर्ण

अटल bool acpi_lpss_is_consumer(काष्ठा acpi_device *adev,
				  स्थिर काष्ठा lpss_device_links *link)
अणु
	वापस acpi_dev_hid_uid_match(adev, link->consumer_hid, link->consumer_uid);
पूर्ण

काष्ठा hid_uid अणु
	स्थिर अक्षर *hid;
	स्थिर अक्षर *uid;
पूर्ण;

अटल पूर्णांक match_hid_uid(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	स्थिर काष्ठा hid_uid *id = data;

	अगर (!adev)
		वापस 0;

	वापस acpi_dev_hid_uid_match(adev, id->hid, id->uid);
पूर्ण

अटल काष्ठा device *acpi_lpss_find_device(स्थिर अक्षर *hid, स्थिर अक्षर *uid)
अणु
	काष्ठा device *dev;

	काष्ठा hid_uid data = अणु
		.hid = hid,
		.uid = uid,
	पूर्ण;

	dev = bus_find_device(&platक्रमm_bus_type, शून्य, &data, match_hid_uid);
	अगर (dev)
		वापस dev;

	वापस bus_find_device(&pci_bus_type, शून्य, &data, match_hid_uid);
पूर्ण

अटल bool acpi_lpss_dep(काष्ठा acpi_device *adev, acpi_handle handle)
अणु
	काष्ठा acpi_handle_list dep_devices;
	acpi_status status;
	पूर्णांक i;

	अगर (!acpi_has_method(adev->handle, "_DEP"))
		वापस false;

	status = acpi_evaluate_reference(adev->handle, "_DEP", शून्य,
					 &dep_devices);
	अगर (ACPI_FAILURE(status)) अणु
		dev_dbg(&adev->dev, "Failed to evaluate _DEP.\n");
		वापस false;
	पूर्ण

	क्रम (i = 0; i < dep_devices.count; i++) अणु
		अगर (dep_devices.handles[i] == handle)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम acpi_lpss_link_consumer(काष्ठा device *dev1,
				    स्थिर काष्ठा lpss_device_links *link)
अणु
	काष्ठा device *dev2;

	dev2 = acpi_lpss_find_device(link->consumer_hid, link->consumer_uid);
	अगर (!dev2)
		वापस;

	अगर ((link->dep_missing_ids && dmi_check_प्रणाली(link->dep_missing_ids))
	    || acpi_lpss_dep(ACPI_COMPANION(dev2), ACPI_HANDLE(dev1)))
		device_link_add(dev2, dev1, link->flags);

	put_device(dev2);
पूर्ण

अटल व्योम acpi_lpss_link_supplier(काष्ठा device *dev1,
				    स्थिर काष्ठा lpss_device_links *link)
अणु
	काष्ठा device *dev2;

	dev2 = acpi_lpss_find_device(link->supplier_hid, link->supplier_uid);
	अगर (!dev2)
		वापस;

	अगर ((link->dep_missing_ids && dmi_check_प्रणाली(link->dep_missing_ids))
	    || acpi_lpss_dep(ACPI_COMPANION(dev1), ACPI_HANDLE(dev2)))
		device_link_add(dev1, dev2, link->flags);

	put_device(dev2);
पूर्ण

अटल व्योम acpi_lpss_create_device_links(काष्ठा acpi_device *adev,
					  काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lpss_device_links); i++) अणु
		स्थिर काष्ठा lpss_device_links *link = &lpss_device_links[i];

		अगर (acpi_lpss_is_supplier(adev, link))
			acpi_lpss_link_consumer(&pdev->dev, link);

		अगर (acpi_lpss_is_consumer(adev, link))
			acpi_lpss_link_supplier(&pdev->dev, link);
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_lpss_create_device(काष्ठा acpi_device *adev,
				   स्थिर काष्ठा acpi_device_id *id)
अणु
	स्थिर काष्ठा lpss_device_desc *dev_desc;
	काष्ठा lpss_निजी_data *pdata;
	काष्ठा resource_entry *rentry;
	काष्ठा list_head resource_list;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	dev_desc = (स्थिर काष्ठा lpss_device_desc *)id->driver_data;
	अगर (!dev_desc) अणु
		pdev = acpi_create_platक्रमm_device(adev, शून्य);
		वापस IS_ERR_OR_शून्य(pdev) ? PTR_ERR(pdev) : 1;
	पूर्ण
	pdata = kzalloc(माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list, is_memory, शून्य);
	अगर (ret < 0)
		जाओ err_out;

	list_क्रम_each_entry(rentry, &resource_list, node)
		अगर (resource_type(rentry->res) == IORESOURCE_MEM) अणु
			अगर (dev_desc->prv_size_override)
				pdata->mmio_size = dev_desc->prv_size_override;
			अन्यथा
				pdata->mmio_size = resource_size(rentry->res);
			pdata->mmio_base = ioremap(rentry->res->start,
						   pdata->mmio_size);
			अवरोध;
		पूर्ण

	acpi_dev_मुक्त_resource_list(&resource_list);

	अगर (!pdata->mmio_base) अणु
		/* Aव्योम acpi_bus_attach() instantiating a pdev क्रम this dev. */
		adev->pnp.type.platक्रमm_id = 0;
		/* Skip the device, but जारी the namespace scan. */
		ret = 0;
		जाओ err_out;
	पूर्ण

	pdata->adev = adev;
	pdata->dev_desc = dev_desc;

	अगर (dev_desc->setup)
		dev_desc->setup(pdata);

	अगर (dev_desc->flags & LPSS_CLK) अणु
		ret = रेजिस्टर_device_घड़ी(adev, pdata);
		अगर (ret) अणु
			/* Skip the device, but जारी the namespace scan. */
			ret = 0;
			जाओ err_out;
		पूर्ण
	पूर्ण

	/*
	 * This works around a known issue in ACPI tables where LPSS devices
	 * have _PS0 and _PS3 without _PSC (and no घातer resources), so
	 * acpi_bus_init_घातer() will assume that the BIOS has put them पूर्णांकo D0.
	 */
	acpi_device_fix_up_घातer(adev);

	adev->driver_data = pdata;
	pdev = acpi_create_platक्रमm_device(adev, dev_desc->properties);
	अगर (!IS_ERR_OR_शून्य(pdev)) अणु
		acpi_lpss_create_device_links(adev, pdev);
		वापस 1;
	पूर्ण

	ret = PTR_ERR(pdev);
	adev->driver_data = शून्य;

 err_out:
	kमुक्त(pdata);
	वापस ret;
पूर्ण

अटल u32 __lpss_reg_पढ़ो(काष्ठा lpss_निजी_data *pdata, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(pdata->mmio_base + pdata->dev_desc->prv_offset + reg);
पूर्ण

अटल व्योम __lpss_reg_ग_लिखो(u32 val, काष्ठा lpss_निजी_data *pdata,
			     अचिन्हित पूर्णांक reg)
अणु
	ग_लिखोl(val, pdata->mmio_base + pdata->dev_desc->prv_offset + reg);
पूर्ण

अटल पूर्णांक lpss_reg_पढ़ो(काष्ठा device *dev, अचिन्हित पूर्णांक reg, u32 *val)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा lpss_निजी_data *pdata;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = acpi_bus_get_device(ACPI_HANDLE(dev), &adev);
	अगर (WARN_ON(ret))
		वापस ret;

	spin_lock_irqsave(&dev->घातer.lock, flags);
	अगर (pm_runसमय_suspended(dev)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	pdata = acpi_driver_data(adev);
	अगर (WARN_ON(!pdata || !pdata->mmio_base)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	*val = __lpss_reg_पढ़ो(pdata, reg);

 out:
	spin_unlock_irqrestore(&dev->घातer.lock, flags);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार lpss_ltr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	u32 ltr_value = 0;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	reg = म_भेद(attr->attr.name, "auto_ltr") ? LPSS_SW_LTR : LPSS_AUTO_LTR;
	ret = lpss_reg_पढ़ो(dev, reg, &ltr_value);
	अगर (ret)
		वापस ret;

	वापस snम_लिखो(buf, PAGE_SIZE, "%08x\n", ltr_value);
पूर्ण

अटल sमाप_प्रकार lpss_ltr_mode_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 ltr_mode = 0;
	अक्षर *outstr;
	पूर्णांक ret;

	ret = lpss_reg_पढ़ो(dev, LPSS_GENERAL, &ltr_mode);
	अगर (ret)
		वापस ret;

	outstr = (ltr_mode & LPSS_GENERAL_LTR_MODE_SW) ? "sw" : "auto";
	वापस प्र_लिखो(buf, "%s\n", outstr);
पूर्ण

अटल DEVICE_ATTR(स्वतः_ltr, S_IRUSR, lpss_ltr_show, शून्य);
अटल DEVICE_ATTR(sw_ltr, S_IRUSR, lpss_ltr_show, शून्य);
अटल DEVICE_ATTR(ltr_mode, S_IRUSR, lpss_ltr_mode_show, शून्य);

अटल काष्ठा attribute *lpss_attrs[] = अणु
	&dev_attr_स्वतः_ltr.attr,
	&dev_attr_sw_ltr.attr,
	&dev_attr_ltr_mode.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lpss_attr_group = अणु
	.attrs = lpss_attrs,
	.name = "lpss_ltr",
पूर्ण;

अटल व्योम acpi_lpss_set_ltr(काष्ठा device *dev, s32 val)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));
	u32 ltr_mode, ltr_val;

	ltr_mode = __lpss_reg_पढ़ो(pdata, LPSS_GENERAL);
	अगर (val < 0) अणु
		अगर (ltr_mode & LPSS_GENERAL_LTR_MODE_SW) अणु
			ltr_mode &= ~LPSS_GENERAL_LTR_MODE_SW;
			__lpss_reg_ग_लिखो(ltr_mode, pdata, LPSS_GENERAL);
		पूर्ण
		वापस;
	पूर्ण
	ltr_val = __lpss_reg_पढ़ो(pdata, LPSS_SW_LTR) & ~LPSS_LTR_SNOOP_MASK;
	अगर (val >= LPSS_LTR_SNOOP_LAT_CUTOFF) अणु
		ltr_val |= LPSS_LTR_SNOOP_LAT_32US;
		val = LPSS_LTR_MAX_VAL;
	पूर्ण अन्यथा अगर (val > LPSS_LTR_MAX_VAL) अणु
		ltr_val |= LPSS_LTR_SNOOP_LAT_32US | LPSS_LTR_SNOOP_REQ;
		val >>= LPSS_LTR_SNOOP_LAT_SHIFT;
	पूर्ण अन्यथा अणु
		ltr_val |= LPSS_LTR_SNOOP_LAT_1US | LPSS_LTR_SNOOP_REQ;
	पूर्ण
	ltr_val |= val;
	__lpss_reg_ग_लिखो(ltr_val, pdata, LPSS_SW_LTR);
	अगर (!(ltr_mode & LPSS_GENERAL_LTR_MODE_SW)) अणु
		ltr_mode |= LPSS_GENERAL_LTR_MODE_SW;
		__lpss_reg_ग_लिखो(ltr_mode, pdata, LPSS_GENERAL);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
/**
 * acpi_lpss_save_ctx() - Save the निजी रेजिस्टरs of LPSS device
 * @dev: LPSS device
 * @pdata: poपूर्णांकer to the निजी data of the LPSS device
 *
 * Most LPSS devices have निजी रेजिस्टरs which may loose their context when
 * the device is घातered करोwn. acpi_lpss_save_ctx() saves those रेजिस्टरs पूर्णांकo
 * prv_reg_ctx array.
 */
अटल व्योम acpi_lpss_save_ctx(काष्ठा device *dev,
			       काष्ठा lpss_निजी_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < LPSS_PRV_REG_COUNT; i++) अणु
		अचिन्हित दीर्घ offset = i * माप(u32);

		pdata->prv_reg_ctx[i] = __lpss_reg_पढ़ो(pdata, offset);
		dev_dbg(dev, "saving 0x%08x from LPSS reg at offset 0x%02lx\n",
			pdata->prv_reg_ctx[i], offset);
	पूर्ण
पूर्ण

/**
 * acpi_lpss_restore_ctx() - Restore the निजी रेजिस्टरs of LPSS device
 * @dev: LPSS device
 * @pdata: poपूर्णांकer to the निजी data of the LPSS device
 *
 * Restores the रेजिस्टरs that were previously stored with acpi_lpss_save_ctx().
 */
अटल व्योम acpi_lpss_restore_ctx(काष्ठा device *dev,
				  काष्ठा lpss_निजी_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < LPSS_PRV_REG_COUNT; i++) अणु
		अचिन्हित दीर्घ offset = i * माप(u32);

		__lpss_reg_ग_लिखो(pdata->prv_reg_ctx[i], pdata, offset);
		dev_dbg(dev, "restoring 0x%08x to LPSS reg at offset 0x%02lx\n",
			pdata->prv_reg_ctx[i], offset);
	पूर्ण
पूर्ण

अटल व्योम acpi_lpss_d3_to_d0_delay(काष्ठा lpss_निजी_data *pdata)
अणु
	/*
	 * The following delay is needed or the subsequent ग_लिखो operations may
	 * fail. The LPSS devices are actually PCI devices and the PCI spec
	 * expects 10ms delay beक्रमe the device can be accessed after D3 to D0
	 * transition. However some platक्रमms like BSW करोes not need this delay.
	 */
	अचिन्हित पूर्णांक delay = 10;	/* शेष 10ms delay */

	अगर (pdata->dev_desc->flags & LPSS_NO_D3_DELAY)
		delay = 0;

	msleep(delay);
पूर्ण

अटल पूर्णांक acpi_lpss_activate(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));
	पूर्णांक ret;

	ret = acpi_dev_resume(dev);
	अगर (ret)
		वापस ret;

	acpi_lpss_d3_to_d0_delay(pdata);

	/*
	 * This is called only on ->probe() stage where a device is either in
	 * known state defined by BIOS or most likely घातered off. Due to this
	 * we have to deनिश्चित reset line to be sure that ->probe() will
	 * recognize the device.
	 */
	अगर (pdata->dev_desc->flags & (LPSS_SAVE_CTX | LPSS_SAVE_CTX_ONCE))
		lpss_deनिश्चित_reset(pdata);

#अगर_घोषित CONFIG_PM
	अगर (pdata->dev_desc->flags & LPSS_SAVE_CTX_ONCE)
		acpi_lpss_save_ctx(dev, pdata);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम acpi_lpss_dismiss(काष्ठा device *dev)
अणु
	acpi_dev_suspend(dev, false);
पूर्ण

/* IOSF SB क्रम LPSS island */
#घोषणा LPSS_IOSF_UNIT_LPIOEP		0xA0
#घोषणा LPSS_IOSF_UNIT_LPIO1		0xAB
#घोषणा LPSS_IOSF_UNIT_LPIO2		0xAC

#घोषणा LPSS_IOSF_PMCSR			0x84
#घोषणा LPSS_PMCSR_D0			0
#घोषणा LPSS_PMCSR_D3hot		3
#घोषणा LPSS_PMCSR_Dx_MASK		GENMASK(1, 0)

#घोषणा LPSS_IOSF_GPIODEF0		0x154
#घोषणा LPSS_GPIODEF0_DMA1_D3		BIT(2)
#घोषणा LPSS_GPIODEF0_DMA2_D3		BIT(3)
#घोषणा LPSS_GPIODEF0_DMA_D3_MASK	GENMASK(3, 2)
#घोषणा LPSS_GPIODEF0_DMA_LLP		BIT(13)

अटल DEFINE_MUTEX(lpss_iosf_mutex);
अटल bool lpss_iosf_d3_entered = true;

अटल व्योम lpss_iosf_enter_d3_state(व्योम)
अणु
	u32 value1 = 0;
	u32 mask1 = LPSS_GPIODEF0_DMA_D3_MASK | LPSS_GPIODEF0_DMA_LLP;
	u32 value2 = LPSS_PMCSR_D3hot;
	u32 mask2 = LPSS_PMCSR_Dx_MASK;
	/*
	 * PMC provides an inक्रमmation about actual status of the LPSS devices.
	 * Here we पढ़ो the values related to LPSS घातer island, i.e. LPSS
	 * devices, excluding both LPSS DMA controllers, aदीर्घ with SCC करोमुख्य.
	 */
	u32 func_dis, d3_sts_0, pmc_status;
	पूर्णांक ret;

	ret = pmc_atom_पढ़ो(PMC_FUNC_DIS, &func_dis);
	अगर (ret)
		वापस;

	mutex_lock(&lpss_iosf_mutex);

	ret = pmc_atom_पढ़ो(PMC_D3_STS_0, &d3_sts_0);
	अगर (ret)
		जाओ निकास;

	/*
	 * Get the status of entire LPSS घातer island per device basis.
	 * Shutकरोwn both LPSS DMA controllers अगर and only अगर all other devices
	 * are alपढ़ोy in D3hot.
	 */
	pmc_status = (~(d3_sts_0 | func_dis)) & pmc_atom_d3_mask;
	अगर (pmc_status)
		जाओ निकास;

	iosf_mbi_modअगरy(LPSS_IOSF_UNIT_LPIO1, MBI_CFG_WRITE,
			LPSS_IOSF_PMCSR, value2, mask2);

	iosf_mbi_modअगरy(LPSS_IOSF_UNIT_LPIO2, MBI_CFG_WRITE,
			LPSS_IOSF_PMCSR, value2, mask2);

	iosf_mbi_modअगरy(LPSS_IOSF_UNIT_LPIOEP, MBI_CR_WRITE,
			LPSS_IOSF_GPIODEF0, value1, mask1);

	lpss_iosf_d3_entered = true;

निकास:
	mutex_unlock(&lpss_iosf_mutex);
पूर्ण

अटल व्योम lpss_iosf_निकास_d3_state(व्योम)
अणु
	u32 value1 = LPSS_GPIODEF0_DMA1_D3 | LPSS_GPIODEF0_DMA2_D3 |
		     LPSS_GPIODEF0_DMA_LLP;
	u32 mask1 = LPSS_GPIODEF0_DMA_D3_MASK | LPSS_GPIODEF0_DMA_LLP;
	u32 value2 = LPSS_PMCSR_D0;
	u32 mask2 = LPSS_PMCSR_Dx_MASK;

	mutex_lock(&lpss_iosf_mutex);

	अगर (!lpss_iosf_d3_entered)
		जाओ निकास;

	lpss_iosf_d3_entered = false;

	iosf_mbi_modअगरy(LPSS_IOSF_UNIT_LPIOEP, MBI_CR_WRITE,
			LPSS_IOSF_GPIODEF0, value1, mask1);

	iosf_mbi_modअगरy(LPSS_IOSF_UNIT_LPIO2, MBI_CFG_WRITE,
			LPSS_IOSF_PMCSR, value2, mask2);

	iosf_mbi_modअगरy(LPSS_IOSF_UNIT_LPIO1, MBI_CFG_WRITE,
			LPSS_IOSF_PMCSR, value2, mask2);

निकास:
	mutex_unlock(&lpss_iosf_mutex);
पूर्ण

अटल पूर्णांक acpi_lpss_suspend(काष्ठा device *dev, bool wakeup)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));
	पूर्णांक ret;

	अगर (pdata->dev_desc->flags & LPSS_SAVE_CTX)
		acpi_lpss_save_ctx(dev, pdata);

	ret = acpi_dev_suspend(dev, wakeup);

	/*
	 * This call must be last in the sequence, otherwise PMC will वापस
	 * wrong status क्रम devices being about to be घातered off. See
	 * lpss_iosf_enter_d3_state() क्रम further inक्रमmation.
	 */
	अगर (acpi_target_प्रणाली_state() == ACPI_STATE_S0 &&
	    lpss_quirks & LPSS_QUIRK_ALWAYS_POWER_ON && iosf_mbi_available())
		lpss_iosf_enter_d3_state();

	वापस ret;
पूर्ण

अटल पूर्णांक acpi_lpss_resume(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));
	पूर्णांक ret;

	/*
	 * This call is kept first to be in symmetry with
	 * acpi_lpss_runसमय_suspend() one.
	 */
	अगर (lpss_quirks & LPSS_QUIRK_ALWAYS_POWER_ON && iosf_mbi_available())
		lpss_iosf_निकास_d3_state();

	ret = acpi_dev_resume(dev);
	अगर (ret)
		वापस ret;

	acpi_lpss_d3_to_d0_delay(pdata);

	अगर (pdata->dev_desc->flags & (LPSS_SAVE_CTX | LPSS_SAVE_CTX_ONCE))
		acpi_lpss_restore_ctx(dev, pdata);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_lpss_करो_suspend_late(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	ret = pm_generic_suspend_late(dev);
	वापस ret ? ret : acpi_lpss_suspend(dev, device_may_wakeup(dev));
पूर्ण

अटल पूर्णांक acpi_lpss_suspend_late(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));

	अगर (pdata->dev_desc->resume_from_noirq)
		वापस 0;

	वापस acpi_lpss_करो_suspend_late(dev);
पूर्ण

अटल पूर्णांक acpi_lpss_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));
	पूर्णांक ret;

	अगर (pdata->dev_desc->resume_from_noirq) अणु
		/*
		 * The driver's ->suspend_late callback will be invoked by
		 * acpi_lpss_करो_suspend_late(), with the assumption that the
		 * driver really wanted to run that code in ->suspend_noirq, but
		 * it could not run after acpi_dev_suspend() and the driver
		 * expected the latter to be called in the "late" phase.
		 */
		ret = acpi_lpss_करो_suspend_late(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस acpi_subsys_suspend_noirq(dev);
पूर्ण

अटल पूर्णांक acpi_lpss_करो_resume_early(काष्ठा device *dev)
अणु
	पूर्णांक ret = acpi_lpss_resume(dev);

	वापस ret ? ret : pm_generic_resume_early(dev);
पूर्ण

अटल पूर्णांक acpi_lpss_resume_early(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));

	अगर (pdata->dev_desc->resume_from_noirq)
		वापस 0;

	अगर (dev_pm_skip_resume(dev))
		वापस 0;

	वापस acpi_lpss_करो_resume_early(dev);
पूर्ण

अटल पूर्णांक acpi_lpss_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));
	पूर्णांक ret;

	/* Follow acpi_subsys_resume_noirq(). */
	अगर (dev_pm_skip_resume(dev))
		वापस 0;

	ret = pm_generic_resume_noirq(dev);
	अगर (ret)
		वापस ret;

	अगर (!pdata->dev_desc->resume_from_noirq)
		वापस 0;

	/*
	 * The driver's ->resume_early callback will be invoked by
	 * acpi_lpss_करो_resume_early(), with the assumption that the driver
	 * really wanted to run that code in ->resume_noirq, but it could not
	 * run beक्रमe acpi_dev_resume() and the driver expected the latter to be
	 * called in the "early" phase.
	 */
	वापस acpi_lpss_करो_resume_early(dev);
पूर्ण

अटल पूर्णांक acpi_lpss_करो_restore_early(काष्ठा device *dev)
अणु
	पूर्णांक ret = acpi_lpss_resume(dev);

	वापस ret ? ret : pm_generic_restore_early(dev);
पूर्ण

अटल पूर्णांक acpi_lpss_restore_early(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));

	अगर (pdata->dev_desc->resume_from_noirq)
		वापस 0;

	वापस acpi_lpss_करो_restore_early(dev);
पूर्ण

अटल पूर्णांक acpi_lpss_restore_noirq(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));
	पूर्णांक ret;

	ret = pm_generic_restore_noirq(dev);
	अगर (ret)
		वापस ret;

	अगर (!pdata->dev_desc->resume_from_noirq)
		वापस 0;

	/* This is analogous to what happens in acpi_lpss_resume_noirq(). */
	वापस acpi_lpss_करो_restore_early(dev);
पूर्ण

अटल पूर्णांक acpi_lpss_करो_घातeroff_late(काष्ठा device *dev)
अणु
	पूर्णांक ret = pm_generic_घातeroff_late(dev);

	वापस ret ? ret : acpi_lpss_suspend(dev, device_may_wakeup(dev));
पूर्ण

अटल पूर्णांक acpi_lpss_घातeroff_late(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));

	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	अगर (pdata->dev_desc->resume_from_noirq)
		वापस 0;

	वापस acpi_lpss_करो_घातeroff_late(dev);
पूर्ण

अटल पूर्णांक acpi_lpss_घातeroff_noirq(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));

	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	अगर (pdata->dev_desc->resume_from_noirq) अणु
		/* This is analogous to the acpi_lpss_suspend_noirq() हाल. */
		पूर्णांक ret = acpi_lpss_करो_घातeroff_late(dev);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pm_generic_घातeroff_noirq(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक acpi_lpss_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret = pm_generic_runसमय_suspend(dev);

	वापस ret ? ret : acpi_lpss_suspend(dev, true);
पूर्ण

अटल पूर्णांक acpi_lpss_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret = acpi_lpss_resume(dev);

	वापस ret ? ret : pm_generic_runसमय_resume(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा dev_pm_करोमुख्य acpi_lpss_pm_करोमुख्य = अणु
#अगर_घोषित CONFIG_PM
	.activate = acpi_lpss_activate,
	.dismiss = acpi_lpss_dismiss,
#पूर्ण_अगर
	.ops = अणु
#अगर_घोषित CONFIG_PM
#अगर_घोषित CONFIG_PM_SLEEP
		.prepare = acpi_subsys_prepare,
		.complete = acpi_subsys_complete,
		.suspend = acpi_subsys_suspend,
		.suspend_late = acpi_lpss_suspend_late,
		.suspend_noirq = acpi_lpss_suspend_noirq,
		.resume_noirq = acpi_lpss_resume_noirq,
		.resume_early = acpi_lpss_resume_early,
		.मुक्तze = acpi_subsys_मुक्तze,
		.घातeroff = acpi_subsys_घातeroff,
		.घातeroff_late = acpi_lpss_घातeroff_late,
		.घातeroff_noirq = acpi_lpss_घातeroff_noirq,
		.restore_noirq = acpi_lpss_restore_noirq,
		.restore_early = acpi_lpss_restore_early,
#पूर्ण_अगर
		.runसमय_suspend = acpi_lpss_runसमय_suspend,
		.runसमय_resume = acpi_lpss_runसमय_resume,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल पूर्णांक acpi_lpss_platक्रमm_notअगरy(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(data);
	काष्ठा lpss_निजी_data *pdata;
	काष्ठा acpi_device *adev;
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(acpi_lpss_device_ids, &pdev->dev);
	अगर (!id || !id->driver_data)
		वापस 0;

	अगर (acpi_bus_get_device(ACPI_HANDLE(&pdev->dev), &adev))
		वापस 0;

	pdata = acpi_driver_data(adev);
	अगर (!pdata)
		वापस 0;

	अगर (pdata->mmio_base &&
	    pdata->mmio_size < pdata->dev_desc->prv_offset + LPSS_LTR_SIZE) अणु
		dev_err(&pdev->dev, "MMIO size insufficient to access LTR\n");
		वापस 0;
	पूर्ण

	चयन (action) अणु
	हाल BUS_NOTIFY_BIND_DRIVER:
		dev_pm_करोमुख्य_set(&pdev->dev, &acpi_lpss_pm_करोमुख्य);
		अवरोध;
	हाल BUS_NOTIFY_DRIVER_NOT_BOUND:
	हाल BUS_NOTIFY_UNBOUND_DRIVER:
		dev_pm_करोमुख्य_set(&pdev->dev, शून्य);
		अवरोध;
	हाल BUS_NOTIFY_ADD_DEVICE:
		dev_pm_करोमुख्य_set(&pdev->dev, &acpi_lpss_pm_करोमुख्य);
		अगर (pdata->dev_desc->flags & LPSS_LTR)
			वापस sysfs_create_group(&pdev->dev.kobj,
						  &lpss_attr_group);
		अवरोध;
	हाल BUS_NOTIFY_DEL_DEVICE:
		अगर (pdata->dev_desc->flags & LPSS_LTR)
			sysfs_हटाओ_group(&pdev->dev.kobj, &lpss_attr_group);
		dev_pm_करोमुख्य_set(&pdev->dev, शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block acpi_lpss_nb = अणु
	.notअगरier_call = acpi_lpss_platक्रमm_notअगरy,
पूर्ण;

अटल व्योम acpi_lpss_bind(काष्ठा device *dev)
अणु
	काष्ठा lpss_निजी_data *pdata = acpi_driver_data(ACPI_COMPANION(dev));

	अगर (!pdata || !pdata->mmio_base || !(pdata->dev_desc->flags & LPSS_LTR))
		वापस;

	अगर (pdata->mmio_size >= pdata->dev_desc->prv_offset + LPSS_LTR_SIZE)
		dev->घातer.set_latency_tolerance = acpi_lpss_set_ltr;
	अन्यथा
		dev_err(dev, "MMIO size insufficient to access LTR\n");
पूर्ण

अटल व्योम acpi_lpss_unbind(काष्ठा device *dev)
अणु
	dev->घातer.set_latency_tolerance = शून्य;
पूर्ण

अटल काष्ठा acpi_scan_handler lpss_handler = अणु
	.ids = acpi_lpss_device_ids,
	.attach = acpi_lpss_create_device,
	.bind = acpi_lpss_bind,
	.unbind = acpi_lpss_unbind,
पूर्ण;

व्योम __init acpi_lpss_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	पूर्णांक ret;

	ret = lpt_clk_init();
	अगर (ret)
		वापस;

	id = x86_match_cpu(lpss_cpu_ids);
	अगर (id)
		lpss_quirks |= LPSS_QUIRK_ALWAYS_POWER_ON;

	bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type, &acpi_lpss_nb);
	acpi_scan_add_handler(&lpss_handler);
पूर्ण

#अन्यथा

अटल काष्ठा acpi_scan_handler lpss_handler = अणु
	.ids = acpi_lpss_device_ids,
पूर्ण;

व्योम __init acpi_lpss_init(व्योम)
अणु
	acpi_scan_add_handler(&lpss_handler);
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_INTEL_LPSS */
