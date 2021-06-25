<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 */

#समावेश <linux/export.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "atom.h"

bool radeon_ddc_probe(काष्ठा radeon_connector *radeon_connector, bool use_aux)
अणु
	u8 out = 0x0;
	u8 buf[8];
	पूर्णांक ret;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = DDC_ADDR,
			.flags = 0,
			.len = 1,
			.buf = &out,
		पूर्ण,
		अणु
			.addr = DDC_ADDR,
			.flags = I2C_M_RD,
			.len = 8,
			.buf = buf,
		पूर्ण
	पूर्ण;

	/* on hw with routers, select right port */
	अगर (radeon_connector->router.ddc_valid)
		radeon_router_select_ddc_port(radeon_connector);

	अगर (use_aux) अणु
		ret = i2c_transfer(&radeon_connector->ddc_bus->aux.ddc, msgs, 2);
	पूर्ण अन्यथा अणु
		ret = i2c_transfer(&radeon_connector->ddc_bus->adapter, msgs, 2);
	पूर्ण

	अगर (ret != 2)
		/* Couldn't find an accessible DDC on this connector */
		वापस false;
	/* Probe also क्रम valid EDID header
	 * EDID header starts with:
	 * 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00.
	 * Only the first 6 bytes must be valid as
	 * drm_edid_block_valid() can fix the last 2 bytes */
	अगर (drm_edid_header_is_valid(buf) < 6) अणु
		/* Couldn't find an accessible EDID on this
		 * connector */
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* bit banging i2c */

अटल पूर्णांक pre_xfer(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा radeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	काष्ठा radeon_device *rdev = i2c->dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t temp;

	mutex_lock(&i2c->mutex);

	/* RV410 appears to have a bug where the hw i2c in reset
	 * holds the i2c port in a bad state - चयन hw i2c away beक्रमe
	 * करोing DDC - करो this क्रम all r200s/r300s/r400s क्रम safety sake
	 */
	अगर (rec->hw_capable) अणु
		अगर ((rdev->family >= CHIP_R200) && !ASIC_IS_AVIVO(rdev)) अणु
			u32 reg;

			अगर (rdev->family >= CHIP_RV350)
				reg = RADEON_GPIO_MONID;
			अन्यथा अगर ((rdev->family == CHIP_R300) ||
				 (rdev->family == CHIP_R350))
				reg = RADEON_GPIO_DVI_DDC;
			अन्यथा
				reg = RADEON_GPIO_CRT2_DDC;

			mutex_lock(&rdev->dc_hw_i2c_mutex);
			अगर (rec->a_clk_reg == reg) अणु
				WREG32(RADEON_DVI_I2C_CNTL_0, (RADEON_I2C_SOFT_RST |
							       R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1)));
			पूर्ण अन्यथा अणु
				WREG32(RADEON_DVI_I2C_CNTL_0, (RADEON_I2C_SOFT_RST |
							       R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3)));
			पूर्ण
			mutex_unlock(&rdev->dc_hw_i2c_mutex);
		पूर्ण
	पूर्ण

	/* चयन the pads to ddc mode */
	अगर (ASIC_IS_DCE3(rdev) && rec->hw_capable) अणु
		temp = RREG32(rec->mask_clk_reg);
		temp &= ~(1 << 16);
		WREG32(rec->mask_clk_reg, temp);
	पूर्ण

	/* clear the output pin values */
	temp = RREG32(rec->a_clk_reg) & ~rec->a_clk_mask;
	WREG32(rec->a_clk_reg, temp);

	temp = RREG32(rec->a_data_reg) & ~rec->a_data_mask;
	WREG32(rec->a_data_reg, temp);

	/* set the pins to input */
	temp = RREG32(rec->en_clk_reg) & ~rec->en_clk_mask;
	WREG32(rec->en_clk_reg, temp);

	temp = RREG32(rec->en_data_reg) & ~rec->en_data_mask;
	WREG32(rec->en_data_reg, temp);

	/* mask the gpio pins क्रम software use */
	temp = RREG32(rec->mask_clk_reg) | rec->mask_clk_mask;
	WREG32(rec->mask_clk_reg, temp);
	temp = RREG32(rec->mask_clk_reg);

	temp = RREG32(rec->mask_data_reg) | rec->mask_data_mask;
	WREG32(rec->mask_data_reg, temp);
	temp = RREG32(rec->mask_data_reg);

	वापस 0;
पूर्ण

अटल व्योम post_xfer(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा radeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	काष्ठा radeon_device *rdev = i2c->dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t temp;

	/* unmask the gpio pins क्रम software use */
	temp = RREG32(rec->mask_clk_reg) & ~rec->mask_clk_mask;
	WREG32(rec->mask_clk_reg, temp);
	temp = RREG32(rec->mask_clk_reg);

	temp = RREG32(rec->mask_data_reg) & ~rec->mask_data_mask;
	WREG32(rec->mask_data_reg, temp);
	temp = RREG32(rec->mask_data_reg);

	mutex_unlock(&i2c->mutex);
पूर्ण

अटल पूर्णांक get_घड़ी(व्योम *i2c_priv)
अणु
	काष्ठा radeon_i2c_chan *i2c = i2c_priv;
	काष्ठा radeon_device *rdev = i2c->dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t val;

	/* पढ़ो the value off the pin */
	val = RREG32(rec->y_clk_reg);
	val &= rec->y_clk_mask;

	वापस (val != 0);
पूर्ण


अटल पूर्णांक get_data(व्योम *i2c_priv)
अणु
	काष्ठा radeon_i2c_chan *i2c = i2c_priv;
	काष्ठा radeon_device *rdev = i2c->dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t val;

	/* पढ़ो the value off the pin */
	val = RREG32(rec->y_data_reg);
	val &= rec->y_data_mask;

	वापस (val != 0);
पूर्ण

अटल व्योम set_घड़ी(व्योम *i2c_priv, पूर्णांक घड़ी)
अणु
	काष्ठा radeon_i2c_chan *i2c = i2c_priv;
	काष्ठा radeon_device *rdev = i2c->dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t val;

	/* set pin direction */
	val = RREG32(rec->en_clk_reg) & ~rec->en_clk_mask;
	val |= घड़ी ? 0 : rec->en_clk_mask;
	WREG32(rec->en_clk_reg, val);
पूर्ण

अटल व्योम set_data(व्योम *i2c_priv, पूर्णांक data)
अणु
	काष्ठा radeon_i2c_chan *i2c = i2c_priv;
	काष्ठा radeon_device *rdev = i2c->dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec *rec = &i2c->rec;
	uपूर्णांक32_t val;

	/* set pin direction */
	val = RREG32(rec->en_data_reg) & ~rec->en_data_mask;
	val |= data ? 0 : rec->en_data_mask;
	WREG32(rec->en_data_reg, val);
पूर्ण

/* hw i2c */

अटल u32 radeon_get_i2c_prescale(काष्ठा radeon_device *rdev)
अणु
	u32 sclk = rdev->pm.current_sclk;
	u32 prescale = 0;
	u32 nm;
	u8 n, m, loop;
	पूर्णांक i2c_घड़ी;

	चयन (rdev->family) अणु
	हाल CHIP_R100:
	हाल CHIP_RV100:
	हाल CHIP_RS100:
	हाल CHIP_RV200:
	हाल CHIP_RS200:
	हाल CHIP_R200:
	हाल CHIP_RV250:
	हाल CHIP_RS300:
	हाल CHIP_RV280:
	हाल CHIP_R300:
	हाल CHIP_R350:
	हाल CHIP_RV350:
		i2c_घड़ी = 60;
		nm = (sclk * 10) / (i2c_घड़ी * 4);
		क्रम (loop = 1; loop < 255; loop++) अणु
			अगर ((nm / loop) < loop)
				अवरोध;
		पूर्ण
		n = loop - 1;
		m = loop - 2;
		prescale = m | (n << 8);
		अवरोध;
	हाल CHIP_RV380:
	हाल CHIP_RS400:
	हाल CHIP_RS480:
	हाल CHIP_R420:
	हाल CHIP_R423:
	हाल CHIP_RV410:
		prescale = (((sclk * 10)/(4 * 128 * 100) + 1) << 8) + 128;
		अवरोध;
	हाल CHIP_RS600:
	हाल CHIP_RS690:
	हाल CHIP_RS740:
		/* toकरो */
		अवरोध;
	हाल CHIP_RV515:
	हाल CHIP_R520:
	हाल CHIP_RV530:
	हाल CHIP_RV560:
	हाल CHIP_RV570:
	हाल CHIP_R580:
		i2c_घड़ी = 50;
		अगर (rdev->family == CHIP_R520)
			prescale = (127 << 8) + ((sclk * 10) / (4 * 127 * i2c_घड़ी));
		अन्यथा
			prescale = (((sclk * 10)/(4 * 128 * 100) + 1) << 8) + 128;
		अवरोध;
	हाल CHIP_R600:
	हाल CHIP_RV610:
	हाल CHIP_RV630:
	हाल CHIP_RV670:
		/* toकरो */
		अवरोध;
	हाल CHIP_RV620:
	हाल CHIP_RV635:
	हाल CHIP_RS780:
	हाल CHIP_RS880:
	हाल CHIP_RV770:
	हाल CHIP_RV730:
	हाल CHIP_RV710:
	हाल CHIP_RV740:
		/* toकरो */
		अवरोध;
	हाल CHIP_CEDAR:
	हाल CHIP_REDWOOD:
	हाल CHIP_JUNIPER:
	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
		/* toकरो */
		अवरोध;
	शेष:
		DRM_ERROR("i2c: unhandled radeon chip\n");
		अवरोध;
	पूर्ण
	वापस prescale;
पूर्ण


/* hw i2c engine क्रम r1xx-4xx hardware
 * hw can buffer up to 15 bytes
 */
अटल पूर्णांक r100_hw_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा radeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	काष्ठा radeon_device *rdev = i2c->dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec *rec = &i2c->rec;
	काष्ठा i2c_msg *p;
	पूर्णांक i, j, k, ret = num;
	u32 prescale;
	u32 i2c_cntl_0, i2c_cntl_1, i2c_data;
	u32 पंचांगp, reg;

	mutex_lock(&rdev->dc_hw_i2c_mutex);
	/* take the pm lock since we need a स्थिरant sclk */
	mutex_lock(&rdev->pm.mutex);

	prescale = radeon_get_i2c_prescale(rdev);

	reg = ((prescale << RADEON_I2C_PRESCALE_SHIFT) |
	       RADEON_I2C_DRIVE_EN |
	       RADEON_I2C_START |
	       RADEON_I2C_STOP |
	       RADEON_I2C_GO);

	अगर (rdev->is_atom_bios) अणु
		पंचांगp = RREG32(RADEON_BIOS_6_SCRATCH);
		WREG32(RADEON_BIOS_6_SCRATCH, पंचांगp | ATOM_S6_HW_I2C_BUSY_STATE);
	पूर्ण

	अगर (rec->mm_i2c) अणु
		i2c_cntl_0 = RADEON_I2C_CNTL_0;
		i2c_cntl_1 = RADEON_I2C_CNTL_1;
		i2c_data = RADEON_I2C_DATA;
	पूर्ण अन्यथा अणु
		i2c_cntl_0 = RADEON_DVI_I2C_CNTL_0;
		i2c_cntl_1 = RADEON_DVI_I2C_CNTL_1;
		i2c_data = RADEON_DVI_I2C_DATA;

		चयन (rdev->family) अणु
		हाल CHIP_R100:
		हाल CHIP_RV100:
		हाल CHIP_RS100:
		हाल CHIP_RV200:
		हाल CHIP_RS200:
		हाल CHIP_RS300:
			चयन (rec->mask_clk_reg) अणु
			हाल RADEON_GPIO_DVI_DDC:
				/* no gpio select bit */
				अवरोध;
			शेष:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			अवरोध;
		हाल CHIP_R200:
			/* only bit 4 on r200 */
			चयन (rec->mask_clk_reg) अणु
			हाल RADEON_GPIO_DVI_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1);
				अवरोध;
			हाल RADEON_GPIO_MONID:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3);
				अवरोध;
			शेष:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			अवरोध;
		हाल CHIP_RV250:
		हाल CHIP_RV280:
			/* bits 3 and 4 */
			चयन (rec->mask_clk_reg) अणु
			हाल RADEON_GPIO_DVI_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1);
				अवरोध;
			हाल RADEON_GPIO_VGA_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC2);
				अवरोध;
			हाल RADEON_GPIO_CRT2_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3);
				अवरोध;
			शेष:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			अवरोध;
		हाल CHIP_R300:
		हाल CHIP_R350:
			/* only bit 4 on r300/r350 */
			चयन (rec->mask_clk_reg) अणु
			हाल RADEON_GPIO_VGA_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1);
				अवरोध;
			हाल RADEON_GPIO_DVI_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3);
				अवरोध;
			शेष:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			अवरोध;
		हाल CHIP_RV350:
		हाल CHIP_RV380:
		हाल CHIP_R420:
		हाल CHIP_R423:
		हाल CHIP_RV410:
		हाल CHIP_RS400:
		हाल CHIP_RS480:
			/* bits 3 and 4 */
			चयन (rec->mask_clk_reg) अणु
			हाल RADEON_GPIO_VGA_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1);
				अवरोध;
			हाल RADEON_GPIO_DVI_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC2);
				अवरोध;
			हाल RADEON_GPIO_MONID:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3);
				अवरोध;
			शेष:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("unsupported asic\n");
			ret = -EINVAL;
			जाओ करोne;
			अवरोध;
		पूर्ण
	पूर्ण

	/* check क्रम bus probe */
	p = &msgs[0];
	अगर ((num == 1) && (p->len == 0)) अणु
		WREG32(i2c_cntl_0, (RADEON_I2C_DONE |
				    RADEON_I2C_NACK |
				    RADEON_I2C_HALT |
				    RADEON_I2C_SOFT_RST));
		WREG32(i2c_data, (p->addr << 1) & 0xff);
		WREG32(i2c_data, 0);
		WREG32(i2c_cntl_1, ((1 << RADEON_I2C_DATA_COUNT_SHIFT) |
				    (1 << RADEON_I2C_ADDR_COUNT_SHIFT) |
				    RADEON_I2C_EN |
				    (48 << RADEON_I2C_TIME_LIMIT_SHIFT)));
		WREG32(i2c_cntl_0, reg);
		क्रम (k = 0; k < 32; k++) अणु
			udelay(10);
			पंचांगp = RREG32(i2c_cntl_0);
			अगर (पंचांगp & RADEON_I2C_GO)
				जारी;
			पंचांगp = RREG32(i2c_cntl_0);
			अगर (पंचांगp & RADEON_I2C_DONE)
				अवरोध;
			अन्यथा अणु
				DRM_DEBUG("i2c write error 0x%08x\n", पंचांगp);
				WREG32(i2c_cntl_0, पंचांगp | RADEON_I2C_ABORT);
				ret = -EIO;
				जाओ करोne;
			पूर्ण
		पूर्ण
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		p = &msgs[i];
		क्रम (j = 0; j < p->len; j++) अणु
			अगर (p->flags & I2C_M_RD) अणु
				WREG32(i2c_cntl_0, (RADEON_I2C_DONE |
						    RADEON_I2C_NACK |
						    RADEON_I2C_HALT |
						    RADEON_I2C_SOFT_RST));
				WREG32(i2c_data, ((p->addr << 1) & 0xff) | 0x1);
				WREG32(i2c_cntl_1, ((1 << RADEON_I2C_DATA_COUNT_SHIFT) |
						    (1 << RADEON_I2C_ADDR_COUNT_SHIFT) |
						    RADEON_I2C_EN |
						    (48 << RADEON_I2C_TIME_LIMIT_SHIFT)));
				WREG32(i2c_cntl_0, reg | RADEON_I2C_RECEIVE);
				क्रम (k = 0; k < 32; k++) अणु
					udelay(10);
					पंचांगp = RREG32(i2c_cntl_0);
					अगर (पंचांगp & RADEON_I2C_GO)
						जारी;
					पंचांगp = RREG32(i2c_cntl_0);
					अगर (पंचांगp & RADEON_I2C_DONE)
						अवरोध;
					अन्यथा अणु
						DRM_DEBUG("i2c read error 0x%08x\n", पंचांगp);
						WREG32(i2c_cntl_0, पंचांगp | RADEON_I2C_ABORT);
						ret = -EIO;
						जाओ करोne;
					पूर्ण
				पूर्ण
				p->buf[j] = RREG32(i2c_data) & 0xff;
			पूर्ण अन्यथा अणु
				WREG32(i2c_cntl_0, (RADEON_I2C_DONE |
						    RADEON_I2C_NACK |
						    RADEON_I2C_HALT |
						    RADEON_I2C_SOFT_RST));
				WREG32(i2c_data, (p->addr << 1) & 0xff);
				WREG32(i2c_data, p->buf[j]);
				WREG32(i2c_cntl_1, ((1 << RADEON_I2C_DATA_COUNT_SHIFT) |
						    (1 << RADEON_I2C_ADDR_COUNT_SHIFT) |
						    RADEON_I2C_EN |
						    (48 << RADEON_I2C_TIME_LIMIT_SHIFT)));
				WREG32(i2c_cntl_0, reg);
				क्रम (k = 0; k < 32; k++) अणु
					udelay(10);
					पंचांगp = RREG32(i2c_cntl_0);
					अगर (पंचांगp & RADEON_I2C_GO)
						जारी;
					पंचांगp = RREG32(i2c_cntl_0);
					अगर (पंचांगp & RADEON_I2C_DONE)
						अवरोध;
					अन्यथा अणु
						DRM_DEBUG("i2c write error 0x%08x\n", पंचांगp);
						WREG32(i2c_cntl_0, पंचांगp | RADEON_I2C_ABORT);
						ret = -EIO;
						जाओ करोne;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	WREG32(i2c_cntl_0, 0);
	WREG32(i2c_cntl_1, 0);
	WREG32(i2c_cntl_0, (RADEON_I2C_DONE |
			    RADEON_I2C_NACK |
			    RADEON_I2C_HALT |
			    RADEON_I2C_SOFT_RST));

	अगर (rdev->is_atom_bios) अणु
		पंचांगp = RREG32(RADEON_BIOS_6_SCRATCH);
		पंचांगp &= ~ATOM_S6_HW_I2C_BUSY_STATE;
		WREG32(RADEON_BIOS_6_SCRATCH, पंचांगp);
	पूर्ण

	mutex_unlock(&rdev->pm.mutex);
	mutex_unlock(&rdev->dc_hw_i2c_mutex);

	वापस ret;
पूर्ण

/* hw i2c engine क्रम r5xx hardware
 * hw can buffer up to 15 bytes
 */
अटल पूर्णांक r500_hw_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा radeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	काष्ठा radeon_device *rdev = i2c->dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec *rec = &i2c->rec;
	काष्ठा i2c_msg *p;
	पूर्णांक i, j, reमुख्यing, current_count, buffer_offset, ret = num;
	u32 prescale;
	u32 पंचांगp, reg;
	u32 saved1, saved2;

	mutex_lock(&rdev->dc_hw_i2c_mutex);
	/* take the pm lock since we need a स्थिरant sclk */
	mutex_lock(&rdev->pm.mutex);

	prescale = radeon_get_i2c_prescale(rdev);

	/* clear gpio mask bits */
	पंचांगp = RREG32(rec->mask_clk_reg);
	पंचांगp &= ~rec->mask_clk_mask;
	WREG32(rec->mask_clk_reg, पंचांगp);
	पंचांगp = RREG32(rec->mask_clk_reg);

	पंचांगp = RREG32(rec->mask_data_reg);
	पंचांगp &= ~rec->mask_data_mask;
	WREG32(rec->mask_data_reg, पंचांगp);
	पंचांगp = RREG32(rec->mask_data_reg);

	/* clear pin values */
	पंचांगp = RREG32(rec->a_clk_reg);
	पंचांगp &= ~rec->a_clk_mask;
	WREG32(rec->a_clk_reg, पंचांगp);
	पंचांगp = RREG32(rec->a_clk_reg);

	पंचांगp = RREG32(rec->a_data_reg);
	पंचांगp &= ~rec->a_data_mask;
	WREG32(rec->a_data_reg, पंचांगp);
	पंचांगp = RREG32(rec->a_data_reg);

	/* set the pins to input */
	पंचांगp = RREG32(rec->en_clk_reg);
	पंचांगp &= ~rec->en_clk_mask;
	WREG32(rec->en_clk_reg, पंचांगp);
	पंचांगp = RREG32(rec->en_clk_reg);

	पंचांगp = RREG32(rec->en_data_reg);
	पंचांगp &= ~rec->en_data_mask;
	WREG32(rec->en_data_reg, पंचांगp);
	पंचांगp = RREG32(rec->en_data_reg);

	/* */
	पंचांगp = RREG32(RADEON_BIOS_6_SCRATCH);
	WREG32(RADEON_BIOS_6_SCRATCH, पंचांगp | ATOM_S6_HW_I2C_BUSY_STATE);
	saved1 = RREG32(AVIVO_DC_I2C_CONTROL1);
	saved2 = RREG32(0x494);
	WREG32(0x494, saved2 | 0x1);

	WREG32(AVIVO_DC_I2C_ARBITRATION, AVIVO_DC_I2C_SW_WANTS_TO_USE_I2C);
	क्रम (i = 0; i < 50; i++) अणु
		udelay(1);
		अगर (RREG32(AVIVO_DC_I2C_ARBITRATION) & AVIVO_DC_I2C_SW_CAN_USE_I2C)
			अवरोध;
	पूर्ण
	अगर (i == 50) अणु
		DRM_ERROR("failed to get i2c bus\n");
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

	reg = AVIVO_DC_I2C_START | AVIVO_DC_I2C_STOP | AVIVO_DC_I2C_EN;
	चयन (rec->mask_clk_reg) अणु
	हाल AVIVO_DC_GPIO_DDC1_MASK:
		reg |= AVIVO_DC_I2C_PIN_SELECT(AVIVO_SEL_DDC1);
		अवरोध;
	हाल AVIVO_DC_GPIO_DDC2_MASK:
		reg |= AVIVO_DC_I2C_PIN_SELECT(AVIVO_SEL_DDC2);
		अवरोध;
	हाल AVIVO_DC_GPIO_DDC3_MASK:
		reg |= AVIVO_DC_I2C_PIN_SELECT(AVIVO_SEL_DDC3);
		अवरोध;
	शेष:
		DRM_ERROR("gpio not supported with hw i2c\n");
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* check क्रम bus probe */
	p = &msgs[0];
	अगर ((num == 1) && (p->len == 0)) अणु
		WREG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
					      AVIVO_DC_I2C_NACK |
					      AVIVO_DC_I2C_HALT));
		WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_SOFT_RESET);
		udelay(1);
		WREG32(AVIVO_DC_I2C_RESET, 0);

		WREG32(AVIVO_DC_I2C_DATA, (p->addr << 1) & 0xff);
		WREG32(AVIVO_DC_I2C_DATA, 0);

		WREG32(AVIVO_DC_I2C_CONTROL3, AVIVO_DC_I2C_TIME_LIMIT(48));
		WREG32(AVIVO_DC_I2C_CONTROL2, (AVIVO_DC_I2C_ADDR_COUNT(1) |
					       AVIVO_DC_I2C_DATA_COUNT(1) |
					       (prescale << 16)));
		WREG32(AVIVO_DC_I2C_CONTROL1, reg);
		WREG32(AVIVO_DC_I2C_STATUS1, AVIVO_DC_I2C_GO);
		क्रम (j = 0; j < 200; j++) अणु
			udelay(50);
			पंचांगp = RREG32(AVIVO_DC_I2C_STATUS1);
			अगर (पंचांगp & AVIVO_DC_I2C_GO)
				जारी;
			पंचांगp = RREG32(AVIVO_DC_I2C_STATUS1);
			अगर (पंचांगp & AVIVO_DC_I2C_DONE)
				अवरोध;
			अन्यथा अणु
				DRM_DEBUG("i2c write error 0x%08x\n", पंचांगp);
				WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_ABORT);
				ret = -EIO;
				जाओ करोne;
			पूर्ण
		पूर्ण
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		p = &msgs[i];
		reमुख्यing = p->len;
		buffer_offset = 0;
		अगर (p->flags & I2C_M_RD) अणु
			जबतक (reमुख्यing) अणु
				अगर (reमुख्यing > 15)
					current_count = 15;
				अन्यथा
					current_count = reमुख्यing;
				WREG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
							      AVIVO_DC_I2C_NACK |
							      AVIVO_DC_I2C_HALT));
				WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_SOFT_RESET);
				udelay(1);
				WREG32(AVIVO_DC_I2C_RESET, 0);

				WREG32(AVIVO_DC_I2C_DATA, ((p->addr << 1) & 0xff) | 0x1);
				WREG32(AVIVO_DC_I2C_CONTROL3, AVIVO_DC_I2C_TIME_LIMIT(48));
				WREG32(AVIVO_DC_I2C_CONTROL2, (AVIVO_DC_I2C_ADDR_COUNT(1) |
							       AVIVO_DC_I2C_DATA_COUNT(current_count) |
							       (prescale << 16)));
				WREG32(AVIVO_DC_I2C_CONTROL1, reg | AVIVO_DC_I2C_RECEIVE);
				WREG32(AVIVO_DC_I2C_STATUS1, AVIVO_DC_I2C_GO);
				क्रम (j = 0; j < 200; j++) अणु
					udelay(50);
					पंचांगp = RREG32(AVIVO_DC_I2C_STATUS1);
					अगर (पंचांगp & AVIVO_DC_I2C_GO)
						जारी;
					पंचांगp = RREG32(AVIVO_DC_I2C_STATUS1);
					अगर (पंचांगp & AVIVO_DC_I2C_DONE)
						अवरोध;
					अन्यथा अणु
						DRM_DEBUG("i2c read error 0x%08x\n", पंचांगp);
						WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_ABORT);
						ret = -EIO;
						जाओ करोne;
					पूर्ण
				पूर्ण
				क्रम (j = 0; j < current_count; j++)
					p->buf[buffer_offset + j] = RREG32(AVIVO_DC_I2C_DATA) & 0xff;
				reमुख्यing -= current_count;
				buffer_offset += current_count;
			पूर्ण
		पूर्ण अन्यथा अणु
			जबतक (reमुख्यing) अणु
				अगर (reमुख्यing > 15)
					current_count = 15;
				अन्यथा
					current_count = reमुख्यing;
				WREG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
							      AVIVO_DC_I2C_NACK |
							      AVIVO_DC_I2C_HALT));
				WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_SOFT_RESET);
				udelay(1);
				WREG32(AVIVO_DC_I2C_RESET, 0);

				WREG32(AVIVO_DC_I2C_DATA, (p->addr << 1) & 0xff);
				क्रम (j = 0; j < current_count; j++)
					WREG32(AVIVO_DC_I2C_DATA, p->buf[buffer_offset + j]);

				WREG32(AVIVO_DC_I2C_CONTROL3, AVIVO_DC_I2C_TIME_LIMIT(48));
				WREG32(AVIVO_DC_I2C_CONTROL2, (AVIVO_DC_I2C_ADDR_COUNT(1) |
							       AVIVO_DC_I2C_DATA_COUNT(current_count) |
							       (prescale << 16)));
				WREG32(AVIVO_DC_I2C_CONTROL1, reg);
				WREG32(AVIVO_DC_I2C_STATUS1, AVIVO_DC_I2C_GO);
				क्रम (j = 0; j < 200; j++) अणु
					udelay(50);
					पंचांगp = RREG32(AVIVO_DC_I2C_STATUS1);
					अगर (पंचांगp & AVIVO_DC_I2C_GO)
						जारी;
					पंचांगp = RREG32(AVIVO_DC_I2C_STATUS1);
					अगर (पंचांगp & AVIVO_DC_I2C_DONE)
						अवरोध;
					अन्यथा अणु
						DRM_DEBUG("i2c write error 0x%08x\n", पंचांगp);
						WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_ABORT);
						ret = -EIO;
						जाओ करोne;
					पूर्ण
				पूर्ण
				reमुख्यing -= current_count;
				buffer_offset += current_count;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	WREG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
				      AVIVO_DC_I2C_NACK |
				      AVIVO_DC_I2C_HALT));
	WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_SOFT_RESET);
	udelay(1);
	WREG32(AVIVO_DC_I2C_RESET, 0);

	WREG32(AVIVO_DC_I2C_ARBITRATION, AVIVO_DC_I2C_SW_DONE_USING_I2C);
	WREG32(AVIVO_DC_I2C_CONTROL1, saved1);
	WREG32(0x494, saved2);
	पंचांगp = RREG32(RADEON_BIOS_6_SCRATCH);
	पंचांगp &= ~ATOM_S6_HW_I2C_BUSY_STATE;
	WREG32(RADEON_BIOS_6_SCRATCH, पंचांगp);

	mutex_unlock(&rdev->pm.mutex);
	mutex_unlock(&rdev->dc_hw_i2c_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक radeon_hw_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			      काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा radeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	काष्ठा radeon_device *rdev = i2c->dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec *rec = &i2c->rec;
	पूर्णांक ret = 0;

	mutex_lock(&i2c->mutex);

	चयन (rdev->family) अणु
	हाल CHIP_R100:
	हाल CHIP_RV100:
	हाल CHIP_RS100:
	हाल CHIP_RV200:
	हाल CHIP_RS200:
	हाल CHIP_R200:
	हाल CHIP_RV250:
	हाल CHIP_RS300:
	हाल CHIP_RV280:
	हाल CHIP_R300:
	हाल CHIP_R350:
	हाल CHIP_RV350:
	हाल CHIP_RV380:
	हाल CHIP_R420:
	हाल CHIP_R423:
	हाल CHIP_RV410:
	हाल CHIP_RS400:
	हाल CHIP_RS480:
		ret = r100_hw_i2c_xfer(i2c_adap, msgs, num);
		अवरोध;
	हाल CHIP_RS600:
	हाल CHIP_RS690:
	हाल CHIP_RS740:
		/* XXX fill in hw i2c implementation */
		अवरोध;
	हाल CHIP_RV515:
	हाल CHIP_R520:
	हाल CHIP_RV530:
	हाल CHIP_RV560:
	हाल CHIP_RV570:
	हाल CHIP_R580:
		अगर (rec->mm_i2c)
			ret = r100_hw_i2c_xfer(i2c_adap, msgs, num);
		अन्यथा
			ret = r500_hw_i2c_xfer(i2c_adap, msgs, num);
		अवरोध;
	हाल CHIP_R600:
	हाल CHIP_RV610:
	हाल CHIP_RV630:
	हाल CHIP_RV670:
		/* XXX fill in hw i2c implementation */
		अवरोध;
	हाल CHIP_RV620:
	हाल CHIP_RV635:
	हाल CHIP_RS780:
	हाल CHIP_RS880:
	हाल CHIP_RV770:
	हाल CHIP_RV730:
	हाल CHIP_RV710:
	हाल CHIP_RV740:
		/* XXX fill in hw i2c implementation */
		अवरोध;
	हाल CHIP_CEDAR:
	हाल CHIP_REDWOOD:
	हाल CHIP_JUNIPER:
	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
		/* XXX fill in hw i2c implementation */
		अवरोध;
	शेष:
		DRM_ERROR("i2c: unhandled radeon chip\n");
		ret = -EIO;
		अवरोध;
	पूर्ण

	mutex_unlock(&i2c->mutex);

	वापस ret;
पूर्ण

अटल u32 radeon_hw_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm radeon_i2c_algo = अणु
	.master_xfer = radeon_hw_i2c_xfer,
	.functionality = radeon_hw_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_algorithm radeon_atom_i2c_algo = अणु
	.master_xfer = radeon_atom_hw_i2c_xfer,
	.functionality = radeon_atom_hw_i2c_func,
पूर्ण;

काष्ठा radeon_i2c_chan *radeon_i2c_create(काष्ठा drm_device *dev,
					  काष्ठा radeon_i2c_bus_rec *rec,
					  स्थिर अक्षर *name)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_i2c_chan *i2c;
	पूर्णांक ret;

	/* करोn't add the mm_i2c bus unless hw_i2c is enabled */
	अगर (rec->mm_i2c && (radeon_hw_i2c == 0))
		वापस शून्य;

	i2c = kzalloc(माप(काष्ठा radeon_i2c_chan), GFP_KERNEL);
	अगर (i2c == शून्य)
		वापस शून्य;

	i2c->rec = *rec;
	i2c->adapter.owner = THIS_MODULE;
	i2c->adapter.class = I2C_CLASS_DDC;
	i2c->adapter.dev.parent = dev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adapter, i2c);
	mutex_init(&i2c->mutex);
	अगर (rec->mm_i2c ||
	    (rec->hw_capable &&
	     radeon_hw_i2c &&
	     ((rdev->family <= CHIP_RS480) ||
	      ((rdev->family >= CHIP_RV515) && (rdev->family <= CHIP_R580))))) अणु
		/* set the radeon hw i2c adapter */
		snम_लिखो(i2c->adapter.name, माप(i2c->adapter.name),
			 "Radeon i2c hw bus %s", name);
		i2c->adapter.algo = &radeon_i2c_algo;
		ret = i2c_add_adapter(&i2c->adapter);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण अन्यथा अगर (rec->hw_capable &&
		   radeon_hw_i2c &&
		   ASIC_IS_DCE3(rdev)) अणु
		/* hw i2c using atom */
		snम_लिखो(i2c->adapter.name, माप(i2c->adapter.name),
			 "Radeon i2c hw bus %s", name);
		i2c->adapter.algo = &radeon_atom_i2c_algo;
		ret = i2c_add_adapter(&i2c->adapter);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण अन्यथा अणु
		/* set the radeon bit adapter */
		snम_लिखो(i2c->adapter.name, माप(i2c->adapter.name),
			 "Radeon i2c bit bus %s", name);
		i2c->adapter.algo_data = &i2c->bit;
		i2c->bit.pre_xfer = pre_xfer;
		i2c->bit.post_xfer = post_xfer;
		i2c->bit.setsda = set_data;
		i2c->bit.setscl = set_घड़ी;
		i2c->bit.माला_लोda = get_data;
		i2c->bit.माला_लोcl = get_घड़ी;
		i2c->bit.udelay = 10;
		i2c->bit.समयout = usecs_to_jअगरfies(2200);	/* from VESA */
		i2c->bit.data = i2c;
		ret = i2c_bit_add_bus(&i2c->adapter);
		अगर (ret) अणु
			DRM_ERROR("Failed to register bit i2c %s\n", name);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	वापस i2c;
out_मुक्त:
	kमुक्त(i2c);
	वापस शून्य;

पूर्ण

व्योम radeon_i2c_destroy(काष्ठा radeon_i2c_chan *i2c)
अणु
	अगर (!i2c)
		वापस;
	WARN_ON(i2c->has_aux);
	i2c_del_adapter(&i2c->adapter);
	kमुक्त(i2c);
पूर्ण

/* Add the शेष buses */
व्योम radeon_i2c_init(काष्ठा radeon_device *rdev)
अणु
	अगर (radeon_hw_i2c)
		DRM_INFO("hw_i2c forced on, you may experience display detection problems!\n");

	अगर (rdev->is_atom_bios)
		radeon_atombios_i2c_init(rdev);
	अन्यथा
		radeon_combios_i2c_init(rdev);
पूर्ण

/* हटाओ all the buses */
व्योम radeon_i2c_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RADEON_MAX_I2C_BUS; i++) अणु
		अगर (rdev->i2c_bus[i]) अणु
			radeon_i2c_destroy(rdev->i2c_bus[i]);
			rdev->i2c_bus[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/* Add additional buses */
व्योम radeon_i2c_add(काष्ठा radeon_device *rdev,
		    काष्ठा radeon_i2c_bus_rec *rec,
		    स्थिर अक्षर *name)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	पूर्णांक i;

	क्रम (i = 0; i < RADEON_MAX_I2C_BUS; i++) अणु
		अगर (!rdev->i2c_bus[i]) अणु
			rdev->i2c_bus[i] = radeon_i2c_create(dev, rec, name);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/* looks up bus based on id */
काष्ठा radeon_i2c_chan *radeon_i2c_lookup(काष्ठा radeon_device *rdev,
					  काष्ठा radeon_i2c_bus_rec *i2c_bus)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RADEON_MAX_I2C_BUS; i++) अणु
		अगर (rdev->i2c_bus[i] &&
		    (rdev->i2c_bus[i]->rec.i2c_id == i2c_bus->i2c_id)) अणु
			वापस rdev->i2c_bus[i];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम radeon_i2c_get_byte(काष्ठा radeon_i2c_chan *i2c_bus,
			 u8 slave_addr,
			 u8 addr,
			 u8 *val)
अणु
	u8 out_buf[2];
	u8 in_buf[2];
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = slave_addr,
			.flags = 0,
			.len = 1,
			.buf = out_buf,
		पूर्ण,
		अणु
			.addr = slave_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = in_buf,
		पूर्ण
	पूर्ण;

	out_buf[0] = addr;
	out_buf[1] = 0;

	अगर (i2c_transfer(&i2c_bus->adapter, msgs, 2) == 2) अणु
		*val = in_buf[0];
		DRM_DEBUG("val = 0x%02x\n", *val);
	पूर्ण अन्यथा अणु
		DRM_DEBUG("i2c 0x%02x 0x%02x read failed\n",
			  addr, *val);
	पूर्ण
पूर्ण

व्योम radeon_i2c_put_byte(काष्ठा radeon_i2c_chan *i2c_bus,
			 u8 slave_addr,
			 u8 addr,
			 u8 val)
अणु
	uपूर्णांक8_t out_buf[2];
	काष्ठा i2c_msg msg = अणु
		.addr = slave_addr,
		.flags = 0,
		.len = 2,
		.buf = out_buf,
	पूर्ण;

	out_buf[0] = addr;
	out_buf[1] = val;

	अगर (i2c_transfer(&i2c_bus->adapter, &msg, 1) != 1)
		DRM_DEBUG("i2c 0x%02x 0x%02x write failed\n",
			  addr, val);
पूर्ण

/* ddc router चयनing */
व्योम radeon_router_select_ddc_port(काष्ठा radeon_connector *radeon_connector)
अणु
	u8 val;

	अगर (!radeon_connector->router.ddc_valid)
		वापस;

	अगर (!radeon_connector->router_bus)
		वापस;

	radeon_i2c_get_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x3, &val);
	val &= ~radeon_connector->router.ddc_mux_control_pin;
	radeon_i2c_put_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x3, val);
	radeon_i2c_get_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x1, &val);
	val &= ~radeon_connector->router.ddc_mux_control_pin;
	val |= radeon_connector->router.ddc_mux_state;
	radeon_i2c_put_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x1, val);
पूर्ण

/* घड़ी/data router चयनing */
व्योम radeon_router_select_cd_port(काष्ठा radeon_connector *radeon_connector)
अणु
	u8 val;

	अगर (!radeon_connector->router.cd_valid)
		वापस;

	अगर (!radeon_connector->router_bus)
		वापस;

	radeon_i2c_get_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x3, &val);
	val &= ~radeon_connector->router.cd_mux_control_pin;
	radeon_i2c_put_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x3, val);
	radeon_i2c_get_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x1, &val);
	val &= ~radeon_connector->router.cd_mux_control_pin;
	val |= radeon_connector->router.cd_mux_state;
	radeon_i2c_put_byte(radeon_connector->router_bus,
			    radeon_connector->router.i2c_addr,
			    0x1, val);
पूर्ण

