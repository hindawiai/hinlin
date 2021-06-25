<शैली गुरु>
/*
 * Copyright (c) 2006 Dave Airlie <airlied@linux.ie>
 * Copyright तऊ 2006-2008,2010 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *	Chris Wilson <chris@chris-wilson.co.uk>
 */

#समावेश <linux/export.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/i2c.h>

#समावेश <drm/drm_hdcp.h>

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_gmbus.h"

काष्ठा gmbus_pin अणु
	स्थिर अक्षर *name;
	क्रमागत i915_gpio gpio;
पूर्ण;

/* Map gmbus pin pairs to names and रेजिस्टरs. */
अटल स्थिर काष्ठा gmbus_pin gmbus_pins[] = अणु
	[GMBUS_PIN_SSC] = अणु "ssc", GPIOB पूर्ण,
	[GMBUS_PIN_VGADDC] = अणु "vga", GPIOA पूर्ण,
	[GMBUS_PIN_PANEL] = अणु "panel", GPIOC पूर्ण,
	[GMBUS_PIN_DPC] = अणु "dpc", GPIOD पूर्ण,
	[GMBUS_PIN_DPB] = अणु "dpb", GPIOE पूर्ण,
	[GMBUS_PIN_DPD] = अणु "dpd", GPIOF पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gmbus_pin gmbus_pins_bdw[] = अणु
	[GMBUS_PIN_VGADDC] = अणु "vga", GPIOA पूर्ण,
	[GMBUS_PIN_DPC] = अणु "dpc", GPIOD पूर्ण,
	[GMBUS_PIN_DPB] = अणु "dpb", GPIOE पूर्ण,
	[GMBUS_PIN_DPD] = अणु "dpd", GPIOF पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gmbus_pin gmbus_pins_skl[] = अणु
	[GMBUS_PIN_DPC] = अणु "dpc", GPIOD पूर्ण,
	[GMBUS_PIN_DPB] = अणु "dpb", GPIOE पूर्ण,
	[GMBUS_PIN_DPD] = अणु "dpd", GPIOF पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gmbus_pin gmbus_pins_bxt[] = अणु
	[GMBUS_PIN_1_BXT] = अणु "dpb", GPIOB पूर्ण,
	[GMBUS_PIN_2_BXT] = अणु "dpc", GPIOC पूर्ण,
	[GMBUS_PIN_3_BXT] = अणु "misc", GPIOD पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gmbus_pin gmbus_pins_cnp[] = अणु
	[GMBUS_PIN_1_BXT] = अणु "dpb", GPIOB पूर्ण,
	[GMBUS_PIN_2_BXT] = अणु "dpc", GPIOC पूर्ण,
	[GMBUS_PIN_3_BXT] = अणु "misc", GPIOD पूर्ण,
	[GMBUS_PIN_4_CNP] = अणु "dpd", GPIOE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gmbus_pin gmbus_pins_icp[] = अणु
	[GMBUS_PIN_1_BXT] = अणु "dpa", GPIOB पूर्ण,
	[GMBUS_PIN_2_BXT] = अणु "dpb", GPIOC पूर्ण,
	[GMBUS_PIN_3_BXT] = अणु "dpc", GPIOD पूर्ण,
	[GMBUS_PIN_9_TC1_ICP] = अणु "tc1", GPIOJ पूर्ण,
	[GMBUS_PIN_10_TC2_ICP] = अणु "tc2", GPIOK पूर्ण,
	[GMBUS_PIN_11_TC3_ICP] = अणु "tc3", GPIOL पूर्ण,
	[GMBUS_PIN_12_TC4_ICP] = अणु "tc4", GPIOM पूर्ण,
	[GMBUS_PIN_13_TC5_TGP] = अणु "tc5", GPION पूर्ण,
	[GMBUS_PIN_14_TC6_TGP] = अणु "tc6", GPIOO पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gmbus_pin gmbus_pins_dg1[] = अणु
	[GMBUS_PIN_1_BXT] = अणु "dpa", GPIOB पूर्ण,
	[GMBUS_PIN_2_BXT] = अणु "dpb", GPIOC पूर्ण,
	[GMBUS_PIN_3_BXT] = अणु "dpc", GPIOD पूर्ण,
	[GMBUS_PIN_4_CNP] = अणु "dpd", GPIOE पूर्ण,
पूर्ण;

/* pin is expected to be valid */
अटल स्थिर काष्ठा gmbus_pin *get_gmbus_pin(काष्ठा drm_i915_निजी *dev_priv,
					     अचिन्हित पूर्णांक pin)
अणु
	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_DG1)
		वापस &gmbus_pins_dg1[pin];
	अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		वापस &gmbus_pins_icp[pin];
	अन्यथा अगर (HAS_PCH_CNP(dev_priv))
		वापस &gmbus_pins_cnp[pin];
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		वापस &gmbus_pins_bxt[pin];
	अन्यथा अगर (IS_GEN9_BC(dev_priv))
		वापस &gmbus_pins_skl[pin];
	अन्यथा अगर (IS_BROADWELL(dev_priv))
		वापस &gmbus_pins_bdw[pin];
	अन्यथा
		वापस &gmbus_pins[pin];
पूर्ण

bool पूर्णांकel_gmbus_is_valid_pin(काष्ठा drm_i915_निजी *dev_priv,
			      अचिन्हित पूर्णांक pin)
अणु
	अचिन्हित पूर्णांक size;

	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_DG1)
		size = ARRAY_SIZE(gmbus_pins_dg1);
	अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		size = ARRAY_SIZE(gmbus_pins_icp);
	अन्यथा अगर (HAS_PCH_CNP(dev_priv))
		size = ARRAY_SIZE(gmbus_pins_cnp);
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		size = ARRAY_SIZE(gmbus_pins_bxt);
	अन्यथा अगर (IS_GEN9_BC(dev_priv))
		size = ARRAY_SIZE(gmbus_pins_skl);
	अन्यथा अगर (IS_BROADWELL(dev_priv))
		size = ARRAY_SIZE(gmbus_pins_bdw);
	अन्यथा
		size = ARRAY_SIZE(gmbus_pins);

	वापस pin < size && get_gmbus_pin(dev_priv, pin)->name;
पूर्ण

/* Intel GPIO access functions */

#घोषणा I2C_RISEFALL_TIME 10

अटल अंतरभूत काष्ठा पूर्णांकel_gmbus *
to_पूर्णांकel_gmbus(काष्ठा i2c_adapter *i2c)
अणु
	वापस container_of(i2c, काष्ठा पूर्णांकel_gmbus, adapter);
पूर्ण

व्योम
पूर्णांकel_gmbus_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_de_ग_लिखो(dev_priv, GMBUS0, 0);
	पूर्णांकel_de_ग_लिखो(dev_priv, GMBUS4, 0);
पूर्ण

अटल व्योम pnv_gmbus_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv,
				   bool enable)
अणु
	u32 val;

	/* When using bit bashing क्रम I2C, this bit needs to be set to 1 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, DSPCLK_GATE_D);
	अगर (!enable)
		val |= PNV_GMBUSUNIT_CLOCK_GATE_DISABLE;
	अन्यथा
		val &= ~PNV_GMBUSUNIT_CLOCK_GATE_DISABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, DSPCLK_GATE_D, val);
पूर्ण

अटल व्योम pch_gmbus_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv,
				   bool enable)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_DSPCLK_GATE_D);
	अगर (!enable)
		val |= PCH_GMBUSUNIT_CLOCK_GATE_DISABLE;
	अन्यथा
		val &= ~PCH_GMBUSUNIT_CLOCK_GATE_DISABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, SOUTH_DSPCLK_GATE_D, val);
पूर्ण

अटल व्योम bxt_gmbus_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv,
				   bool enable)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, GEN9_CLKGATE_DIS_4);
	अगर (!enable)
		val |= BXT_GMBUS_GATING_DIS;
	अन्यथा
		val &= ~BXT_GMBUS_GATING_DIS;
	पूर्णांकel_de_ग_लिखो(dev_priv, GEN9_CLKGATE_DIS_4, val);
पूर्ण

अटल u32 get_reserved(काष्ठा पूर्णांकel_gmbus *bus)
अणु
	काष्ठा drm_i915_निजी *i915 = bus->dev_priv;
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 reserved = 0;

	/* On most chips, these bits must be preserved in software. */
	अगर (!IS_I830(i915) && !IS_I845G(i915))
		reserved = पूर्णांकel_uncore_पढ़ो_notrace(uncore, bus->gpio_reg) &
			   (GPIO_DATA_PULLUP_DISABLE |
			    GPIO_CLOCK_PULLUP_DISABLE);

	वापस reserved;
पूर्ण

अटल पूर्णांक get_घड़ी(व्योम *data)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = data;
	काष्ठा पूर्णांकel_uncore *uncore = &bus->dev_priv->uncore;
	u32 reserved = get_reserved(bus);

	पूर्णांकel_uncore_ग_लिखो_notrace(uncore,
				   bus->gpio_reg,
				   reserved | GPIO_CLOCK_सूची_MASK);
	पूर्णांकel_uncore_ग_लिखो_notrace(uncore, bus->gpio_reg, reserved);

	वापस (पूर्णांकel_uncore_पढ़ो_notrace(uncore, bus->gpio_reg) &
		GPIO_CLOCK_VAL_IN) != 0;
पूर्ण

अटल पूर्णांक get_data(व्योम *data)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = data;
	काष्ठा पूर्णांकel_uncore *uncore = &bus->dev_priv->uncore;
	u32 reserved = get_reserved(bus);

	पूर्णांकel_uncore_ग_लिखो_notrace(uncore,
				   bus->gpio_reg,
				   reserved | GPIO_DATA_सूची_MASK);
	पूर्णांकel_uncore_ग_लिखो_notrace(uncore, bus->gpio_reg, reserved);

	वापस (पूर्णांकel_uncore_पढ़ो_notrace(uncore, bus->gpio_reg) &
		GPIO_DATA_VAL_IN) != 0;
पूर्ण

अटल व्योम set_घड़ी(व्योम *data, पूर्णांक state_high)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = data;
	काष्ठा पूर्णांकel_uncore *uncore = &bus->dev_priv->uncore;
	u32 reserved = get_reserved(bus);
	u32 घड़ी_bits;

	अगर (state_high)
		घड़ी_bits = GPIO_CLOCK_सूची_IN | GPIO_CLOCK_सूची_MASK;
	अन्यथा
		घड़ी_bits = GPIO_CLOCK_सूची_OUT | GPIO_CLOCK_सूची_MASK |
			     GPIO_CLOCK_VAL_MASK;

	पूर्णांकel_uncore_ग_लिखो_notrace(uncore,
				   bus->gpio_reg,
				   reserved | घड़ी_bits);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, bus->gpio_reg);
पूर्ण

अटल व्योम set_data(व्योम *data, पूर्णांक state_high)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = data;
	काष्ठा पूर्णांकel_uncore *uncore = &bus->dev_priv->uncore;
	u32 reserved = get_reserved(bus);
	u32 data_bits;

	अगर (state_high)
		data_bits = GPIO_DATA_सूची_IN | GPIO_DATA_सूची_MASK;
	अन्यथा
		data_bits = GPIO_DATA_सूची_OUT | GPIO_DATA_सूची_MASK |
			GPIO_DATA_VAL_MASK;

	पूर्णांकel_uncore_ग_लिखो_notrace(uncore, bus->gpio_reg, reserved | data_bits);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, bus->gpio_reg);
पूर्ण

अटल पूर्णांक
पूर्णांकel_gpio_pre_xfer(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = container_of(adapter,
					       काष्ठा पूर्णांकel_gmbus,
					       adapter);
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;

	पूर्णांकel_gmbus_reset(dev_priv);

	अगर (IS_PINEVIEW(dev_priv))
		pnv_gmbus_घड़ी_gating(dev_priv, false);

	set_data(bus, 1);
	set_घड़ी(bus, 1);
	udelay(I2C_RISEFALL_TIME);
	वापस 0;
पूर्ण

अटल व्योम
पूर्णांकel_gpio_post_xfer(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = container_of(adapter,
					       काष्ठा पूर्णांकel_gmbus,
					       adapter);
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;

	set_data(bus, 1);
	set_घड़ी(bus, 1);

	अगर (IS_PINEVIEW(dev_priv))
		pnv_gmbus_घड़ी_gating(dev_priv, true);
पूर्ण

अटल व्योम
पूर्णांकel_gpio_setup(काष्ठा पूर्णांकel_gmbus *bus, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;
	काष्ठा i2c_algo_bit_data *algo;

	algo = &bus->bit_algo;

	bus->gpio_reg = GPIO(get_gmbus_pin(dev_priv, pin)->gpio);
	bus->adapter.algo_data = algo;
	algo->setsda = set_data;
	algo->setscl = set_घड़ी;
	algo->माला_लोda = get_data;
	algo->माला_लोcl = get_घड़ी;
	algo->pre_xfer = पूर्णांकel_gpio_pre_xfer;
	algo->post_xfer = पूर्णांकel_gpio_post_xfer;
	algo->udelay = I2C_RISEFALL_TIME;
	algo->समयout = usecs_to_jअगरfies(2200);
	algo->data = bus;
पूर्ण

अटल पूर्णांक gmbus_रुको(काष्ठा drm_i915_निजी *dev_priv, u32 status, u32 irq_en)
अणु
	DEFINE_WAIT(रुको);
	u32 gmbus2;
	पूर्णांक ret;

	/* Important: The hw handles only the first bit, so set only one! Since
	 * we also need to check क्रम NAKs besides the hw पढ़ोy/idle संकेत, we
	 * need to wake up periodically and check that ourselves.
	 */
	अगर (!HAS_GMBUS_IRQ(dev_priv))
		irq_en = 0;

	add_रुको_queue(&dev_priv->gmbus_रुको_queue, &रुको);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS4, irq_en);

	status |= GMBUS_SATOER;
	ret = रुको_क्रम_us((gmbus2 = पूर्णांकel_de_पढ़ो_fw(dev_priv, GMBUS2)) & status,
			  2);
	अगर (ret)
		ret = रुको_क्रम((gmbus2 = पूर्णांकel_de_पढ़ो_fw(dev_priv, GMBUS2)) & status,
			       50);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS4, 0);
	हटाओ_रुको_queue(&dev_priv->gmbus_रुको_queue, &रुको);

	अगर (gmbus2 & GMBUS_SATOER)
		वापस -ENXIO;

	वापस ret;
पूर्ण

अटल पूर्णांक
gmbus_रुको_idle(काष्ठा drm_i915_निजी *dev_priv)
अणु
	DEFINE_WAIT(रुको);
	u32 irq_enable;
	पूर्णांक ret;

	/* Important: The hw handles only the first bit, so set only one! */
	irq_enable = 0;
	अगर (HAS_GMBUS_IRQ(dev_priv))
		irq_enable = GMBUS_IDLE_EN;

	add_रुको_queue(&dev_priv->gmbus_रुको_queue, &रुको);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS4, irq_enable);

	ret = पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(&dev_priv->uncore,
					 GMBUS2, GMBUS_ACTIVE, 0,
					 10);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS4, 0);
	हटाओ_रुको_queue(&dev_priv->gmbus_रुको_queue, &रुको);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक gmbus_max_xfer_size(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस DISPLAY_VER(dev_priv) >= 9 ? GEN9_GMBUS_BYTE_COUNT_MAX :
	       GMBUS_BYTE_COUNT_MAX;
पूर्ण

अटल पूर्णांक
gmbus_xfer_पढ़ो_chunk(काष्ठा drm_i915_निजी *dev_priv,
		      अचिन्हित लघु addr, u8 *buf, अचिन्हित पूर्णांक len,
		      u32 gmbus0_reg, u32 gmbus1_index)
अणु
	अचिन्हित पूर्णांक size = len;
	bool burst_पढ़ो = len > gmbus_max_xfer_size(dev_priv);
	bool extra_byte_added = false;

	अगर (burst_पढ़ो) अणु
		/*
		 * As per HW Spec, क्रम 512Bytes need to पढ़ो extra Byte and
		 * Ignore the extra byte पढ़ो.
		 */
		अगर (len == 512) अणु
			extra_byte_added = true;
			len++;
		पूर्ण
		size = len % 256 + 256;
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS0,
				  gmbus0_reg | GMBUS_BYTE_CNT_OVERRIDE);
	पूर्ण

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS1,
			  gmbus1_index | GMBUS_CYCLE_WAIT | (size << GMBUS_BYTE_COUNT_SHIFT) | (addr << GMBUS_SLAVE_ADDR_SHIFT) | GMBUS_SLAVE_READ | GMBUS_SW_RDY);
	जबतक (len) अणु
		पूर्णांक ret;
		u32 val, loop = 0;

		ret = gmbus_रुको(dev_priv, GMBUS_HW_RDY, GMBUS_HW_RDY_EN);
		अगर (ret)
			वापस ret;

		val = पूर्णांकel_de_पढ़ो_fw(dev_priv, GMBUS3);
		करो अणु
			अगर (extra_byte_added && len == 1)
				अवरोध;

			*buf++ = val & 0xff;
			val >>= 8;
		पूर्ण जबतक (--len && ++loop < 4);

		अगर (burst_पढ़ो && len == size - 4)
			/* Reset the override bit */
			पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS0, gmbus0_reg);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * HW spec says that 512Bytes in Burst पढ़ो need special treaपंचांगent.
 * But it करोesn't talk about other multiple of 256Bytes. And couldn't locate
 * an I2C slave, which supports such a lengthy burst पढ़ो too क्रम experiments.
 *
 * So until things get clarअगरied on HW support, to aव्योम the burst पढ़ो length
 * in fold of 256Bytes except 512, max burst पढ़ो length is fixed at 767Bytes.
 */
#घोषणा INTEL_GMBUS_BURST_READ_MAX_LEN		767U

अटल पूर्णांक
gmbus_xfer_पढ़ो(काष्ठा drm_i915_निजी *dev_priv, काष्ठा i2c_msg *msg,
		u32 gmbus0_reg, u32 gmbus1_index)
अणु
	u8 *buf = msg->buf;
	अचिन्हित पूर्णांक rx_size = msg->len;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret;

	करो अणु
		अगर (HAS_GMBUS_BURST_READ(dev_priv))
			len = min(rx_size, INTEL_GMBUS_BURST_READ_MAX_LEN);
		अन्यथा
			len = min(rx_size, gmbus_max_xfer_size(dev_priv));

		ret = gmbus_xfer_पढ़ो_chunk(dev_priv, msg->addr, buf, len,
					    gmbus0_reg, gmbus1_index);
		अगर (ret)
			वापस ret;

		rx_size -= len;
		buf += len;
	पूर्ण जबतक (rx_size != 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
gmbus_xfer_ग_लिखो_chunk(काष्ठा drm_i915_निजी *dev_priv,
		       अचिन्हित लघु addr, u8 *buf, अचिन्हित पूर्णांक len,
		       u32 gmbus1_index)
अणु
	अचिन्हित पूर्णांक chunk_size = len;
	u32 val, loop;

	val = loop = 0;
	जबतक (len && loop < 4) अणु
		val |= *buf++ << (8 * loop++);
		len -= 1;
	पूर्ण

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS3, val);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS1,
			  gmbus1_index | GMBUS_CYCLE_WAIT | (chunk_size << GMBUS_BYTE_COUNT_SHIFT) | (addr << GMBUS_SLAVE_ADDR_SHIFT) | GMBUS_SLAVE_WRITE | GMBUS_SW_RDY);
	जबतक (len) अणु
		पूर्णांक ret;

		val = loop = 0;
		करो अणु
			val |= *buf++ << (8 * loop);
		पूर्ण जबतक (--len && ++loop < 4);

		पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS3, val);

		ret = gmbus_रुको(dev_priv, GMBUS_HW_RDY, GMBUS_HW_RDY_EN);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gmbus_xfer_ग_लिखो(काष्ठा drm_i915_निजी *dev_priv, काष्ठा i2c_msg *msg,
		 u32 gmbus1_index)
अणु
	u8 *buf = msg->buf;
	अचिन्हित पूर्णांक tx_size = msg->len;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret;

	करो अणु
		len = min(tx_size, gmbus_max_xfer_size(dev_priv));

		ret = gmbus_xfer_ग_लिखो_chunk(dev_priv, msg->addr, buf, len,
					     gmbus1_index);
		अगर (ret)
			वापस ret;

		buf += len;
		tx_size -= len;
	पूर्ण जबतक (tx_size != 0);

	वापस 0;
पूर्ण

/*
 * The gmbus controller can combine a 1 or 2 byte ग_लिखो with another पढ़ो/ग_लिखो
 * that immediately follows it by using an "INDEX" cycle.
 */
अटल bool
gmbus_is_index_xfer(काष्ठा i2c_msg *msgs, पूर्णांक i, पूर्णांक num)
अणु
	वापस (i + 1 < num &&
		msgs[i].addr == msgs[i + 1].addr &&
		!(msgs[i].flags & I2C_M_RD) &&
		(msgs[i].len == 1 || msgs[i].len == 2) &&
		msgs[i + 1].len > 0);
पूर्ण

अटल पूर्णांक
gmbus_index_xfer(काष्ठा drm_i915_निजी *dev_priv, काष्ठा i2c_msg *msgs,
		 u32 gmbus0_reg)
अणु
	u32 gmbus1_index = 0;
	u32 gmbus5 = 0;
	पूर्णांक ret;

	अगर (msgs[0].len == 2)
		gmbus5 = GMBUS_2BYTE_INDEX_EN |
			 msgs[0].buf[1] | (msgs[0].buf[0] << 8);
	अगर (msgs[0].len == 1)
		gmbus1_index = GMBUS_CYCLE_INDEX |
			       (msgs[0].buf[0] << GMBUS_SLAVE_INDEX_SHIFT);

	/* GMBUS5 holds 16-bit index */
	अगर (gmbus5)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS5, gmbus5);

	अगर (msgs[1].flags & I2C_M_RD)
		ret = gmbus_xfer_पढ़ो(dev_priv, &msgs[1], gmbus0_reg,
				      gmbus1_index);
	अन्यथा
		ret = gmbus_xfer_ग_लिखो(dev_priv, &msgs[1], gmbus1_index);

	/* Clear GMBUS5 after each index transfer */
	अगर (gmbus5)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS5, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक
करो_gmbus_xfer(काष्ठा i2c_adapter *adapter, काष्ठा i2c_msg *msgs, पूर्णांक num,
	      u32 gmbus0_source)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = container_of(adapter,
					       काष्ठा पूर्णांकel_gmbus,
					       adapter);
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;
	पूर्णांक i = 0, inc, try = 0;
	पूर्णांक ret = 0;

	/* Display WA #0868: skl,bxt,kbl,cfl,glk,cnl */
	अगर (IS_GEN9_LP(dev_priv))
		bxt_gmbus_घड़ी_gating(dev_priv, false);
	अन्यथा अगर (HAS_PCH_SPT(dev_priv) || HAS_PCH_CNP(dev_priv))
		pch_gmbus_घड़ी_gating(dev_priv, false);

retry:
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS0, gmbus0_source | bus->reg0);

	क्रम (; i < num; i += inc) अणु
		inc = 1;
		अगर (gmbus_is_index_xfer(msgs, i, num)) अणु
			ret = gmbus_index_xfer(dev_priv, &msgs[i],
					       gmbus0_source | bus->reg0);
			inc = 2; /* an index transmission is two msgs */
		पूर्ण अन्यथा अगर (msgs[i].flags & I2C_M_RD) अणु
			ret = gmbus_xfer_पढ़ो(dev_priv, &msgs[i],
					      gmbus0_source | bus->reg0, 0);
		पूर्ण अन्यथा अणु
			ret = gmbus_xfer_ग_लिखो(dev_priv, &msgs[i], 0);
		पूर्ण

		अगर (!ret)
			ret = gmbus_रुको(dev_priv,
					 GMBUS_HW_WAIT_PHASE, GMBUS_HW_WAIT_EN);
		अगर (ret == -ETIMEDOUT)
			जाओ समयout;
		अन्यथा अगर (ret)
			जाओ clear_err;
	पूर्ण

	/* Generate a STOP condition on the bus. Note that gmbus can't generata
	 * a STOP on the very first cycle. To simplअगरy the code we
	 * unconditionally generate the STOP condition with an additional gmbus
	 * cycle. */
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS1, GMBUS_CYCLE_STOP | GMBUS_SW_RDY);

	/* Mark the GMBUS पूर्णांकerface as disabled after रुकोing क्रम idle.
	 * We will re-enable it at the start of the next xfer,
	 * till then let it sleep.
	 */
	अगर (gmbus_रुको_idle(dev_priv)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "GMBUS [%s] timed out waiting for idle\n",
			    adapter->name);
		ret = -ETIMEDOUT;
	पूर्ण
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS0, 0);
	ret = ret ?: i;
	जाओ out;

clear_err:
	/*
	 * Wait क्रम bus to IDLE beक्रमe clearing NAK.
	 * If we clear the NAK जबतक bus is still active, then it will stay
	 * active and the next transaction may fail.
	 *
	 * If no ACK is received during the address phase of a transaction, the
	 * adapter must report -ENXIO. It is not clear what to वापस अगर no ACK
	 * is received at other बार. But we have to be careful to not वापस
	 * spurious -ENXIO because that will prevent i2c and drm edid functions
	 * from retrying. So वापस -ENXIO only when gmbus properly quiescents -
	 * timing out seems to happen when there _is_ a ddc chip present, but
	 * it's slow responding and only answers on the 2nd retry.
	 */
	ret = -ENXIO;
	अगर (gmbus_रुको_idle(dev_priv)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "GMBUS [%s] timed out after NAK\n",
			    adapter->name);
		ret = -ETIMEDOUT;
	पूर्ण

	/* Toggle the Software Clear Interrupt bit. This has the effect
	 * of resetting the GMBUS controller and so clearing the
	 * BUS_ERROR उठाओd by the slave's NAK.
	 */
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS1, GMBUS_SW_CLR_INT);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS1, 0);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS0, 0);

	drm_dbg_kms(&dev_priv->drm, "GMBUS [%s] NAK for addr: %04x %c(%d)\n",
		    adapter->name, msgs[i].addr,
		    (msgs[i].flags & I2C_M_RD) ? 'r' : 'w', msgs[i].len);

	/*
	 * Passive adapters someबार NAK the first probe. Retry the first
	 * message once on -ENXIO क्रम GMBUS transfers; the bit banging algorithm
	 * has retries पूर्णांकernally. See also the retry loop in
	 * drm_करो_probe_ddc_edid, which bails out on the first -ENXIO.
	 */
	अगर (ret == -ENXIO && i == 0 && try++ == 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "GMBUS [%s] NAK on first message, retry\n",
			    adapter->name);
		जाओ retry;
	पूर्ण

	जाओ out;

समयout:
	drm_dbg_kms(&dev_priv->drm,
		    "GMBUS [%s] timed out, falling back to bit banging on pin %d\n",
		    bus->adapter.name, bus->reg0 & 0xff);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, GMBUS0, 0);

	/*
	 * Hardware may not support GMBUS over these pins? Try GPIO bitbanging
	 * instead. Use EAGAIN to have i2c core retry.
	 */
	ret = -EAGAIN;

out:
	/* Display WA #0868: skl,bxt,kbl,cfl,glk,cnl */
	अगर (IS_GEN9_LP(dev_priv))
		bxt_gmbus_घड़ी_gating(dev_priv, true);
	अन्यथा अगर (HAS_PCH_SPT(dev_priv) || HAS_PCH_CNP(dev_priv))
		pch_gmbus_घड़ी_gating(dev_priv, true);

	वापस ret;
पूर्ण

अटल पूर्णांक
gmbus_xfer(काष्ठा i2c_adapter *adapter, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा पूर्णांकel_gmbus *bus =
		container_of(adapter, काष्ठा पूर्णांकel_gmbus, adapter);
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक ret;

	wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_GMBUS);

	अगर (bus->क्रमce_bit) अणु
		ret = i2c_bit_algo.master_xfer(adapter, msgs, num);
		अगर (ret < 0)
			bus->क्रमce_bit &= ~GMBUS_FORCE_BIT_RETRY;
	पूर्ण अन्यथा अणु
		ret = करो_gmbus_xfer(adapter, msgs, num, 0);
		अगर (ret == -EAGAIN)
			bus->क्रमce_bit |= GMBUS_FORCE_BIT_RETRY;
	पूर्ण

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_GMBUS, wakeref);

	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_gmbus_output_aksv(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा पूर्णांकel_gmbus *bus =
		container_of(adapter, काष्ठा पूर्णांकel_gmbus, adapter);
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;
	u8 cmd = DRM_HDCP_DDC_AKSV;
	u8 buf[DRM_HDCP_KSV_LEN] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = DRM_HDCP_DDC_ADDR,
			.flags = 0,
			.len = माप(cmd),
			.buf = &cmd,
		पूर्ण,
		अणु
			.addr = DRM_HDCP_DDC_ADDR,
			.flags = 0,
			.len = माप(buf),
			.buf = buf,
		पूर्ण
	पूर्ण;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक ret;

	wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_GMBUS);
	mutex_lock(&dev_priv->gmbus_mutex);

	/*
	 * In order to output Aksv to the receiver, use an indexed ग_लिखो to
	 * pass the i2c command, and tell GMBUS to use the HW-provided value
	 * instead of sourcing GMBUS3 क्रम the data.
	 */
	ret = करो_gmbus_xfer(adapter, msgs, ARRAY_SIZE(msgs), GMBUS_AKSV_SELECT);

	mutex_unlock(&dev_priv->gmbus_mutex);
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_GMBUS, wakeref);

	वापस ret;
पूर्ण

अटल u32 gmbus_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस i2c_bit_algo.functionality(adapter) &
		(I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
		/* I2C_FUNC_10BIT_ADDR | */
		I2C_FUNC_SMBUS_READ_BLOCK_DATA |
		I2C_FUNC_SMBUS_BLOCK_PROC_CALL);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm gmbus_algorithm = अणु
	.master_xfer	= gmbus_xfer,
	.functionality	= gmbus_func
पूर्ण;

अटल व्योम gmbus_lock_bus(काष्ठा i2c_adapter *adapter,
			   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = to_पूर्णांकel_gmbus(adapter);
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;

	mutex_lock(&dev_priv->gmbus_mutex);
पूर्ण

अटल पूर्णांक gmbus_trylock_bus(काष्ठा i2c_adapter *adapter,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = to_पूर्णांकel_gmbus(adapter);
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;

	वापस mutex_trylock(&dev_priv->gmbus_mutex);
पूर्ण

अटल व्योम gmbus_unlock_bus(काष्ठा i2c_adapter *adapter,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = to_पूर्णांकel_gmbus(adapter);
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;

	mutex_unlock(&dev_priv->gmbus_mutex);
पूर्ण

अटल स्थिर काष्ठा i2c_lock_operations gmbus_lock_ops = अणु
	.lock_bus =    gmbus_lock_bus,
	.trylock_bus = gmbus_trylock_bus,
	.unlock_bus =  gmbus_unlock_bus,
पूर्ण;

/**
 * पूर्णांकel_gmbus_setup - instantiate all Intel i2c GMBuses
 * @dev_priv: i915 device निजी
 */
पूर्णांक पूर्णांकel_gmbus_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	काष्ठा पूर्णांकel_gmbus *bus;
	अचिन्हित पूर्णांक pin;
	पूर्णांक ret;

	अगर (!HAS_DISPLAY(dev_priv))
		वापस 0;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		dev_priv->gpio_mmio_base = VLV_DISPLAY_BASE;
	अन्यथा अगर (!HAS_GMCH(dev_priv))
		/*
		 * Broxton uses the same PCH offsets क्रम South Display Engine,
		 * even though it करोesn't have a PCH.
		 */
		dev_priv->gpio_mmio_base = PCH_DISPLAY_BASE;

	mutex_init(&dev_priv->gmbus_mutex);
	init_रुकोqueue_head(&dev_priv->gmbus_रुको_queue);

	क्रम (pin = 0; pin < ARRAY_SIZE(dev_priv->gmbus); pin++) अणु
		अगर (!पूर्णांकel_gmbus_is_valid_pin(dev_priv, pin))
			जारी;

		bus = &dev_priv->gmbus[pin];

		bus->adapter.owner = THIS_MODULE;
		bus->adapter.class = I2C_CLASS_DDC;
		snम_लिखो(bus->adapter.name,
			 माप(bus->adapter.name),
			 "i915 gmbus %s",
			 get_gmbus_pin(dev_priv, pin)->name);

		bus->adapter.dev.parent = &pdev->dev;
		bus->dev_priv = dev_priv;

		bus->adapter.algo = &gmbus_algorithm;
		bus->adapter.lock_ops = &gmbus_lock_ops;

		/*
		 * We wish to retry with bit banging
		 * after a समयd out GMBUS attempt.
		 */
		bus->adapter.retries = 1;

		/* By शेष use a conservative घड़ी rate */
		bus->reg0 = pin | GMBUS_RATE_100KHZ;

		/* gmbus seems to be broken on i830 */
		अगर (IS_I830(dev_priv))
			bus->क्रमce_bit = 1;

		पूर्णांकel_gpio_setup(bus, pin);

		ret = i2c_add_adapter(&bus->adapter);
		अगर (ret)
			जाओ err;
	पूर्ण

	पूर्णांकel_gmbus_reset(dev_priv);

	वापस 0;

err:
	जबतक (pin--) अणु
		अगर (!पूर्णांकel_gmbus_is_valid_pin(dev_priv, pin))
			जारी;

		bus = &dev_priv->gmbus[pin];
		i2c_del_adapter(&bus->adapter);
	पूर्ण
	वापस ret;
पूर्ण

काष्ठा i2c_adapter *पूर्णांकel_gmbus_get_adapter(काष्ठा drm_i915_निजी *dev_priv,
					    अचिन्हित पूर्णांक pin)
अणु
	अगर (drm_WARN_ON(&dev_priv->drm,
			!पूर्णांकel_gmbus_is_valid_pin(dev_priv, pin)))
		वापस शून्य;

	वापस &dev_priv->gmbus[pin].adapter;
पूर्ण

व्योम पूर्णांकel_gmbus_set_speed(काष्ठा i2c_adapter *adapter, पूर्णांक speed)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = to_पूर्णांकel_gmbus(adapter);

	bus->reg0 = (bus->reg0 & ~(0x3 << 8)) | speed;
पूर्ण

व्योम पूर्णांकel_gmbus_क्रमce_bit(काष्ठा i2c_adapter *adapter, bool क्रमce_bit)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = to_पूर्णांकel_gmbus(adapter);
	काष्ठा drm_i915_निजी *dev_priv = bus->dev_priv;

	mutex_lock(&dev_priv->gmbus_mutex);

	bus->क्रमce_bit += क्रमce_bit ? 1 : -1;
	drm_dbg_kms(&dev_priv->drm,
		    "%sabling bit-banging on %s. force bit now %d\n",
		    क्रमce_bit ? "en" : "dis", adapter->name,
		    bus->क्रमce_bit);

	mutex_unlock(&dev_priv->gmbus_mutex);
पूर्ण

bool पूर्णांकel_gmbus_is_क्रमced_bit(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = to_पूर्णांकel_gmbus(adapter);

	वापस bus->क्रमce_bit;
पूर्ण

व्योम पूर्णांकel_gmbus_tearकरोwn(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_gmbus *bus;
	अचिन्हित पूर्णांक pin;

	क्रम (pin = 0; pin < ARRAY_SIZE(dev_priv->gmbus); pin++) अणु
		अगर (!पूर्णांकel_gmbus_is_valid_pin(dev_priv, pin))
			जारी;

		bus = &dev_priv->gmbus[pin];
		i2c_del_adapter(&bus->adapter);
	पूर्ण
पूर्ण
