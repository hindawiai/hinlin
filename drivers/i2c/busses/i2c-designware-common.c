<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Synopsys DesignWare I2C adapter driver.
 *
 * Based on the TI DAVINCI I2C adapter driver.
 *
 * Copyright (C) 2006 Texas Instruments.
 * Copyright (C) 2007 MontaVista Software Inc.
 * Copyright (C) 2009 Provigent Ltd.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/swab.h>
#समावेश <linux/types.h>

#समावेश "i2c-designware-core.h"

अटल अक्षर *पात_sources[] = अणु
	[ABRT_7B_ADDR_NOACK] =
		"slave address not acknowledged (7bit mode)",
	[ABRT_10ADDR1_NOACK] =
		"first address byte not acknowledged (10bit mode)",
	[ABRT_10ADDR2_NOACK] =
		"second address byte not acknowledged (10bit mode)",
	[ABRT_TXDATA_NOACK] =
		"data not acknowledged",
	[ABRT_GCALL_NOACK] =
		"no acknowledgement for a general call",
	[ABRT_GCALL_READ] =
		"read after general call",
	[ABRT_SBYTE_ACKDET] =
		"start byte acknowledged",
	[ABRT_SBYTE_NORSTRT] =
		"trying to send start byte when restart is disabled",
	[ABRT_10B_RD_NORSTRT] =
		"trying to read when restart is disabled (10bit mode)",
	[ABRT_MASTER_DIS] =
		"trying to use disabled adapter",
	[ARB_LOST] =
		"lost arbitration",
	[ABRT_SLAVE_FLUSH_TXFIFO] =
		"read command so flush old data in the TX FIFO",
	[ABRT_SLAVE_ARBLOST] =
		"slave lost the bus while transmitting data to a remote master",
	[ABRT_SLAVE_RD_INTX] =
		"incorrect slave-transmitter mode configuration",
पूर्ण;

अटल पूर्णांक dw_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा dw_i2c_dev *dev = context;

	*val = पढ़ोl_relaxed(dev->base + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा dw_i2c_dev *dev = context;

	ग_लिखोl_relaxed(val, dev->base + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_reg_पढ़ो_swab(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा dw_i2c_dev *dev = context;

	*val = swab32(पढ़ोl_relaxed(dev->base + reg));

	वापस 0;
पूर्ण

अटल पूर्णांक dw_reg_ग_लिखो_swab(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा dw_i2c_dev *dev = context;

	ग_लिखोl_relaxed(swab32(val), dev->base + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_reg_पढ़ो_word(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा dw_i2c_dev *dev = context;

	*val = पढ़ोw_relaxed(dev->base + reg) |
		(पढ़ोw_relaxed(dev->base + reg + 2) << 16);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_reg_ग_लिखो_word(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा dw_i2c_dev *dev = context;

	ग_लिखोw_relaxed(val, dev->base + reg);
	ग_लिखोw_relaxed(val >> 16, dev->base + reg + 2);

	वापस 0;
पूर्ण

/**
 * i2c_dw_init_regmap() - Initialize रेजिस्टरs map
 * @dev: device निजी data
 *
 * Autodetects needed रेजिस्टर access mode and creates the regmap with
 * corresponding पढ़ो/ग_लिखो callbacks. This must be called beक्रमe करोing any
 * other रेजिस्टर access.
 */
पूर्णांक i2c_dw_init_regmap(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा regmap_config map_cfg = अणु
		.reg_bits = 32,
		.val_bits = 32,
		.reg_stride = 4,
		.disable_locking = true,
		.reg_पढ़ो = dw_reg_पढ़ो,
		.reg_ग_लिखो = dw_reg_ग_लिखो,
		.max_रेजिस्टर = DW_IC_COMP_TYPE,
	पूर्ण;
	u32 reg;
	पूर्णांक ret;

	/*
	 * Skip detecting the रेजिस्टरs map configuration अगर the regmap has
	 * alपढ़ोy been provided by a higher code.
	 */
	अगर (dev->map)
		वापस 0;

	ret = i2c_dw_acquire_lock(dev);
	अगर (ret)
		वापस ret;

	reg = पढ़ोl(dev->base + DW_IC_COMP_TYPE);
	i2c_dw_release_lock(dev);

	अगर ((dev->flags & MODEL_MASK) == MODEL_AMD_NAVI_GPU)
		map_cfg.max_रेजिस्टर = AMD_UCSI_INTR_REG;

	अगर (reg == swab32(DW_IC_COMP_TYPE_VALUE)) अणु
		map_cfg.reg_पढ़ो = dw_reg_पढ़ो_swab;
		map_cfg.reg_ग_लिखो = dw_reg_ग_लिखो_swab;
	पूर्ण अन्यथा अगर (reg == (DW_IC_COMP_TYPE_VALUE & 0x0000ffff)) अणु
		map_cfg.reg_पढ़ो = dw_reg_पढ़ो_word;
		map_cfg.reg_ग_लिखो = dw_reg_ग_लिखो_word;
	पूर्ण अन्यथा अगर (reg != DW_IC_COMP_TYPE_VALUE) अणु
		dev_err(dev->dev,
			"Unknown Synopsys component type: 0x%08x\n", reg);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Note we'll check the वापस value of the regmap IO accessors only
	 * at the probe stage. The rest of the code won't करो this because
	 * basically we have MMIO-based regmap so non of the पढ़ो/ग_लिखो methods
	 * can fail.
	 */
	dev->map = devm_regmap_init(dev->dev, शून्य, dev, &map_cfg);
	अगर (IS_ERR(dev->map)) अणु
		dev_err(dev->dev, "Failed to init the registers map\n");
		वापस PTR_ERR(dev->map);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर u32 supported_speeds[] = अणु
	I2C_MAX_HIGH_SPEED_MODE_FREQ,
	I2C_MAX_FAST_MODE_PLUS_FREQ,
	I2C_MAX_FAST_MODE_FREQ,
	I2C_MAX_STANDARD_MODE_FREQ,
पूर्ण;

पूर्णांक i2c_dw_validate_speed(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_timings *t = &dev->timings;
	अचिन्हित पूर्णांक i;

	/*
	 * Only standard mode at 100kHz, fast mode at 400kHz,
	 * fast mode plus at 1MHz and high speed mode at 3.4MHz are supported.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(supported_speeds); i++) अणु
		अगर (t->bus_freq_hz == supported_speeds[i])
			वापस 0;
	पूर्ण

	dev_err(dev->dev,
		"%d Hz is unsupported, only 100kHz, 400kHz, 1MHz and 3.4MHz are supported\n",
		t->bus_freq_hz);

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_dw_validate_speed);

#अगर_घोषित CONFIG_ACPI

#समावेश <linux/dmi.h>

/*
 * The HCNT/LCNT inक्रमmation coming from ACPI should be the most accurate
 * क्रम given platक्रमm. However, some प्रणालीs get it wrong. On such प्रणालीs
 * we get better results by calculating those based on the input घड़ी.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id i2c_dw_no_acpi_params[] = अणु
	अणु
		.ident = "Dell Inspiron 7348",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7348"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम i2c_dw_acpi_params(काष्ठा device *device, अक्षर method[],
			       u16 *hcnt, u16 *lcnt, u32 *sda_hold)
अणु
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER पूर्ण;
	acpi_handle handle = ACPI_HANDLE(device);
	जोड़ acpi_object *obj;

	अगर (dmi_check_प्रणाली(i2c_dw_no_acpi_params))
		वापस;

	अगर (ACPI_FAILURE(acpi_evaluate_object(handle, method, शून्य, &buf)))
		वापस;

	obj = (जोड़ acpi_object *)buf.poपूर्णांकer;
	अगर (obj->type == ACPI_TYPE_PACKAGE && obj->package.count == 3) अणु
		स्थिर जोड़ acpi_object *objs = obj->package.elements;

		*hcnt = (u16)objs[0].पूर्णांकeger.value;
		*lcnt = (u16)objs[1].पूर्णांकeger.value;
		*sda_hold = (u32)objs[2].पूर्णांकeger.value;
	पूर्ण

	kमुक्त(buf.poपूर्णांकer);
पूर्ण

पूर्णांक i2c_dw_acpi_configure(काष्ठा device *device)
अणु
	काष्ठा dw_i2c_dev *dev = dev_get_drvdata(device);
	काष्ठा i2c_timings *t = &dev->timings;
	u32 ss_ht = 0, fp_ht = 0, hs_ht = 0, fs_ht = 0;

	/*
	 * Try to get SDA hold समय and *CNT values from an ACPI method क्रम
	 * selected speed modes.
	 */
	i2c_dw_acpi_params(device, "SSCN", &dev->ss_hcnt, &dev->ss_lcnt, &ss_ht);
	i2c_dw_acpi_params(device, "FPCN", &dev->fp_hcnt, &dev->fp_lcnt, &fp_ht);
	i2c_dw_acpi_params(device, "HSCN", &dev->hs_hcnt, &dev->hs_lcnt, &hs_ht);
	i2c_dw_acpi_params(device, "FMCN", &dev->fs_hcnt, &dev->fs_lcnt, &fs_ht);

	चयन (t->bus_freq_hz) अणु
	हाल I2C_MAX_STANDARD_MODE_FREQ:
		dev->sda_hold_समय = ss_ht;
		अवरोध;
	हाल I2C_MAX_FAST_MODE_PLUS_FREQ:
		dev->sda_hold_समय = fp_ht;
		अवरोध;
	हाल I2C_MAX_HIGH_SPEED_MODE_FREQ:
		dev->sda_hold_समय = hs_ht;
		अवरोध;
	हाल I2C_MAX_FAST_MODE_FREQ:
	शेष:
		dev->sda_hold_समय = fs_ht;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_dw_acpi_configure);

अटल u32 i2c_dw_acpi_round_bus_speed(काष्ठा device *device)
अणु
	u32 acpi_speed;
	पूर्णांक i;

	acpi_speed = i2c_acpi_find_bus_speed(device);
	/*
	 * Some DSTDs use a non standard speed, round करोwn to the lowest
	 * standard speed.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(supported_speeds); i++) अणु
		अगर (acpi_speed >= supported_speeds[i])
			वापस supported_speeds[i];
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा	/* CONFIG_ACPI */

अटल अंतरभूत u32 i2c_dw_acpi_round_bus_speed(काष्ठा device *device) अणु वापस 0; पूर्ण

#पूर्ण_अगर	/* CONFIG_ACPI */

व्योम i2c_dw_adjust_bus_speed(काष्ठा dw_i2c_dev *dev)
अणु
	u32 acpi_speed = i2c_dw_acpi_round_bus_speed(dev->dev);
	काष्ठा i2c_timings *t = &dev->timings;

	/*
	 * Find bus speed from the "clock-frequency" device property, ACPI
	 * or by using fast mode अगर neither is set.
	 */
	अगर (acpi_speed && t->bus_freq_hz)
		t->bus_freq_hz = min(t->bus_freq_hz, acpi_speed);
	अन्यथा अगर (acpi_speed || t->bus_freq_hz)
		t->bus_freq_hz = max(t->bus_freq_hz, acpi_speed);
	अन्यथा
		t->bus_freq_hz = I2C_MAX_FAST_MODE_FREQ;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_dw_adjust_bus_speed);

u32 i2c_dw_scl_hcnt(u32 ic_clk, u32 tSYMBOL, u32 tf, पूर्णांक cond, पूर्णांक offset)
अणु
	/*
	 * DesignWare I2C core करोesn't seem to have solid strategy to meet
	 * the tHD;STA timing spec.  Configuring _HCNT based on tHIGH spec
	 * will result in violation of the tHD;STA spec.
	 */
	अगर (cond)
		/*
		 * Conditional expression:
		 *
		 *   IC_[FS]S_SCL_HCNT + (1+4+3) >= IC_CLK * tHIGH
		 *
		 * This is based on the DW manuals, and represents an ideal
		 * configuration.  The resulting I2C bus speed will be
		 * faster than any of the others.
		 *
		 * If your hardware is मुक्त from tHD;STA issue, try this one.
		 */
		वापस (ic_clk * tSYMBOL + 500000) / 1000000 - 8 + offset;
	अन्यथा
		/*
		 * Conditional expression:
		 *
		 *   IC_[FS]S_SCL_HCNT + 3 >= IC_CLK * (tHD;STA + tf)
		 *
		 * This is just experimental rule; the tHD;STA period turned
		 * out to be proportinal to (_HCNT + 3).  With this setting,
		 * we could meet both tHIGH and tHD;STA timing specs.
		 *
		 * If unsure, you'd better to take this alternative.
		 *
		 * The reason why we need to take पूर्णांकo account "tf" here,
		 * is the same as described in i2c_dw_scl_lcnt().
		 */
		वापस (ic_clk * (tSYMBOL + tf) + 500000) / 1000000
			- 3 + offset;
पूर्ण

u32 i2c_dw_scl_lcnt(u32 ic_clk, u32 tLOW, u32 tf, पूर्णांक offset)
अणु
	/*
	 * Conditional expression:
	 *
	 *   IC_[FS]S_SCL_LCNT + 1 >= IC_CLK * (tLOW + tf)
	 *
	 * DW I2C core starts counting the SCL CNTs क्रम the LOW period
	 * of the SCL घड़ी (tLOW) as soon as it pulls the SCL line.
	 * In order to meet the tLOW timing spec, we need to take पूर्णांकo
	 * account the fall समय of SCL संकेत (tf).  Default tf value
	 * should be 0.3 us, क्रम safety.
	 */
	वापस ((ic_clk * (tLOW + tf) + 500000) / 1000000) - 1 + offset;
पूर्ण

पूर्णांक i2c_dw_set_sda_hold(काष्ठा dw_i2c_dev *dev)
अणु
	u32 reg;
	पूर्णांक ret;

	ret = i2c_dw_acquire_lock(dev);
	अगर (ret)
		वापस ret;

	/* Configure SDA Hold Time अगर required */
	ret = regmap_पढ़ो(dev->map, DW_IC_COMP_VERSION, &reg);
	अगर (ret)
		जाओ err_release_lock;

	अगर (reg >= DW_IC_SDA_HOLD_MIN_VERS) अणु
		अगर (!dev->sda_hold_समय) अणु
			/* Keep previous hold समय setting अगर no one set it */
			ret = regmap_पढ़ो(dev->map, DW_IC_SDA_HOLD,
					  &dev->sda_hold_समय);
			अगर (ret)
				जाओ err_release_lock;
		पूर्ण

		/*
		 * Workaround क्रम aव्योमing TX arbitration lost in हाल I2C
		 * slave pulls SDA करोwn "too quickly" after falling edge of
		 * SCL by enabling non-zero SDA RX hold. Specअगरication says it
		 * extends incoming SDA low to high transition जबतक SCL is
		 * high but it appears to help also above issue.
		 */
		अगर (!(dev->sda_hold_समय & DW_IC_SDA_HOLD_RX_MASK))
			dev->sda_hold_समय |= 1 << DW_IC_SDA_HOLD_RX_SHIFT;

		dev_dbg(dev->dev, "SDA Hold Time TX:RX = %d:%d\n",
			dev->sda_hold_समय & ~(u32)DW_IC_SDA_HOLD_RX_MASK,
			dev->sda_hold_समय >> DW_IC_SDA_HOLD_RX_SHIFT);
	पूर्ण अन्यथा अगर (dev->set_sda_hold_समय) अणु
		dev->set_sda_hold_समय(dev);
	पूर्ण अन्यथा अगर (dev->sda_hold_समय) अणु
		dev_warn(dev->dev,
			"Hardware too old to adjust SDA hold time.\n");
		dev->sda_hold_समय = 0;
	पूर्ण

err_release_lock:
	i2c_dw_release_lock(dev);

	वापस ret;
पूर्ण

व्योम __i2c_dw_disable(काष्ठा dw_i2c_dev *dev)
अणु
	पूर्णांक समयout = 100;
	u32 status;

	करो अणु
		__i2c_dw_disable_noरुको(dev);
		/*
		 * The enable status रेजिस्टर may be unimplemented, but
		 * in that हाल this test पढ़ोs zero and निकासs the loop.
		 */
		regmap_पढ़ो(dev->map, DW_IC_ENABLE_STATUS, &status);
		अगर ((status & 1) == 0)
			वापस;

		/*
		 * Wait 10 बार the संकेतing period of the highest I2C
		 * transfer supported by the driver (क्रम 400KHz this is
		 * 25us) as described in the DesignWare I2C databook.
		 */
		usleep_range(25, 250);
	पूर्ण जबतक (समयout--);

	dev_warn(dev->dev, "timeout in disabling adapter\n");
पूर्ण

अचिन्हित दीर्घ i2c_dw_clk_rate(काष्ठा dw_i2c_dev *dev)
अणु
	/*
	 * Clock is not necessary अगर we got LCNT/HCNT values directly from
	 * the platक्रमm code.
	 */
	अगर (WARN_ON_ONCE(!dev->get_clk_rate_khz))
		वापस 0;
	वापस dev->get_clk_rate_khz(dev);
पूर्ण

पूर्णांक i2c_dw_prepare_clk(काष्ठा dw_i2c_dev *dev, bool prepare)
अणु
	पूर्णांक ret;

	अगर (IS_ERR(dev->clk))
		वापस PTR_ERR(dev->clk);

	अगर (prepare) अणु
		/* Optional पूर्णांकerface घड़ी */
		ret = clk_prepare_enable(dev->pclk);
		अगर (ret)
			वापस ret;

		ret = clk_prepare_enable(dev->clk);
		अगर (ret)
			clk_disable_unprepare(dev->pclk);

		वापस ret;
	पूर्ण

	clk_disable_unprepare(dev->clk);
	clk_disable_unprepare(dev->pclk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_dw_prepare_clk);

पूर्णांक i2c_dw_acquire_lock(काष्ठा dw_i2c_dev *dev)
अणु
	पूर्णांक ret;

	अगर (!dev->acquire_lock)
		वापस 0;

	ret = dev->acquire_lock();
	अगर (!ret)
		वापस 0;

	dev_err(dev->dev, "couldn't acquire bus ownership\n");

	वापस ret;
पूर्ण

व्योम i2c_dw_release_lock(काष्ठा dw_i2c_dev *dev)
अणु
	अगर (dev->release_lock)
		dev->release_lock();
पूर्ण

/*
 * Waiting क्रम bus not busy
 */
पूर्णांक i2c_dw_रुको_bus_not_busy(काष्ठा dw_i2c_dev *dev)
अणु
	u32 status;
	पूर्णांक ret;

	ret = regmap_पढ़ो_poll_समयout(dev->map, DW_IC_STATUS, status,
				       !(status & DW_IC_STATUS_ACTIVITY),
				       1100, 20000);
	अगर (ret) अणु
		dev_warn(dev->dev, "timeout waiting for bus ready\n");

		i2c_recover_bus(&dev->adapter);

		regmap_पढ़ो(dev->map, DW_IC_STATUS, &status);
		अगर (!(status & DW_IC_STATUS_ACTIVITY))
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक i2c_dw_handle_tx_पात(काष्ठा dw_i2c_dev *dev)
अणु
	अचिन्हित दीर्घ पात_source = dev->पात_source;
	पूर्णांक i;

	अगर (पात_source & DW_IC_TX_ABRT_NOACK) अणु
		क्रम_each_set_bit(i, &पात_source, ARRAY_SIZE(पात_sources))
			dev_dbg(dev->dev,
				"%s: %s\n", __func__, पात_sources[i]);
		वापस -EREMOTEIO;
	पूर्ण

	क्रम_each_set_bit(i, &पात_source, ARRAY_SIZE(पात_sources))
		dev_err(dev->dev, "%s: %s\n", __func__, पात_sources[i]);

	अगर (पात_source & DW_IC_TX_ARB_LOST)
		वापस -EAGAIN;
	अन्यथा अगर (पात_source & DW_IC_TX_ABRT_GCALL_READ)
		वापस -EINVAL; /* wrong msgs[] data */
	अन्यथा
		वापस -EIO;
पूर्ण

पूर्णांक i2c_dw_set_fअगरo_size(काष्ठा dw_i2c_dev *dev)
अणु
	u32 param, tx_fअगरo_depth, rx_fअगरo_depth;
	पूर्णांक ret;

	/*
	 * Try to detect the FIFO depth अगर not set by पूर्णांकerface driver,
	 * the depth could be from 2 to 256 from HW spec.
	 */
	ret = regmap_पढ़ो(dev->map, DW_IC_COMP_PARAM_1, &param);
	अगर (ret)
		वापस ret;

	tx_fअगरo_depth = ((param >> 16) & 0xff) + 1;
	rx_fअगरo_depth = ((param >> 8)  & 0xff) + 1;
	अगर (!dev->tx_fअगरo_depth) अणु
		dev->tx_fअगरo_depth = tx_fअगरo_depth;
		dev->rx_fअगरo_depth = rx_fअगरo_depth;
	पूर्ण अन्यथा अगर (tx_fअगरo_depth >= 2) अणु
		dev->tx_fअगरo_depth = min_t(u32, dev->tx_fअगरo_depth,
				tx_fअगरo_depth);
		dev->rx_fअगरo_depth = min_t(u32, dev->rx_fअगरo_depth,
				rx_fअगरo_depth);
	पूर्ण

	वापस 0;
पूर्ण

u32 i2c_dw_func(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा dw_i2c_dev *dev = i2c_get_adapdata(adap);

	वापस dev->functionality;
पूर्ण

व्योम i2c_dw_disable(काष्ठा dw_i2c_dev *dev)
अणु
	u32 dummy;

	/* Disable controller */
	__i2c_dw_disable(dev);

	/* Disable all पूर्णांकerrupts */
	regmap_ग_लिखो(dev->map, DW_IC_INTR_MASK, 0);
	regmap_पढ़ो(dev->map, DW_IC_CLR_INTR, &dummy);
पूर्ण

व्योम i2c_dw_disable_पूर्णांक(काष्ठा dw_i2c_dev *dev)
अणु
	regmap_ग_लिखो(dev->map, DW_IC_INTR_MASK, 0);
पूर्ण

MODULE_DESCRIPTION("Synopsys DesignWare I2C bus adapter core");
MODULE_LICENSE("GPL");
