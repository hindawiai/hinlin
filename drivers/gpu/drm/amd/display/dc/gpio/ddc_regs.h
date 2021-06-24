<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#अगर_अघोषित DRIVERS_GPU_DRM_AMD_DC_DEV_DC_GPIO_DDC_REGS_H_
#घोषणा DRIVERS_GPU_DRM_AMD_DC_DEV_DC_GPIO_DDC_REGS_H_

#समावेश "gpio_regs.h"

/****************************** new रेजिस्टर headers */
/*** following in header */

#घोषणा DDC_GPIO_REG_LIST_ENTRY(type,cd,id) \
	.type ## _reg =   REG(DC_GPIO_DDC ## id ## _ ## type),\
	.type ## _mask =  DC_GPIO_DDC ## id ## _ ## type ## __DC_GPIO_DDC ## id ## cd ## _ ## type ## _MASK,\
	.type ## _shअगरt = DC_GPIO_DDC ## id ## _ ## type ## __DC_GPIO_DDC ## id ## cd ## _ ## type ## __SHIFT

#घोषणा DDC_GPIO_REG_LIST(cd,id) \
	अणु\
	DDC_GPIO_REG_LIST_ENTRY(MASK,cd,id),\
	DDC_GPIO_REG_LIST_ENTRY(A,cd,id),\
	DDC_GPIO_REG_LIST_ENTRY(EN,cd,id),\
	DDC_GPIO_REG_LIST_ENTRY(Y,cd,id)\
	पूर्ण

#घोषणा DDC_REG_LIST(cd,id) \
	DDC_GPIO_REG_LIST(cd,id),\
	.ddc_setup = REG(DC_I2C_DDC ## id ## _SETUP)

	#घोषणा DDC_REG_LIST_DCN2(cd, id) \
	DDC_GPIO_REG_LIST(cd, id),\
	.ddc_setup = REG(DC_I2C_DDC ## id ## _SETUP),\
	.phy_aux_cntl = REG(PHY_AUX_CNTL), \
	.dc_gpio_aux_ctrl_5 = REG(DC_GPIO_AUX_CTRL_5)

#घोषणा DDC_GPIO_VGA_REG_LIST_ENTRY(type,cd)\
	.type ## _reg =   REG(DC_GPIO_DDCVGA_ ## type),\
	.type ## _mask =  DC_GPIO_DDCVGA_ ## type ## __DC_GPIO_DDCVGA ## cd ## _ ## type ## _MASK,\
	.type ## _shअगरt = DC_GPIO_DDCVGA_ ## type ## __DC_GPIO_DDCVGA ## cd ## _ ## type ## __SHIFT

#घोषणा DDC_GPIO_VGA_REG_LIST(cd) \
	अणु\
	DDC_GPIO_VGA_REG_LIST_ENTRY(MASK,cd),\
	DDC_GPIO_VGA_REG_LIST_ENTRY(A,cd),\
	DDC_GPIO_VGA_REG_LIST_ENTRY(EN,cd),\
	DDC_GPIO_VGA_REG_LIST_ENTRY(Y,cd)\
	पूर्ण

#घोषणा DDC_VGA_REG_LIST(cd) \
	DDC_GPIO_VGA_REG_LIST(cd),\
	.ddc_setup = mmDC_I2C_DDCVGA_SETUP

#घोषणा DDC_GPIO_I2C_REG_LIST_ENTRY(type,cd) \
	.type ## _reg =   REG(DC_GPIO_I2CPAD_ ## type),\
	.type ## _mask =  DC_GPIO_I2CPAD_ ## type ## __DC_GPIO_ ## cd ## _ ## type ## _MASK,\
	.type ## _shअगरt = DC_GPIO_I2CPAD_ ## type ## __DC_GPIO_ ## cd ## _ ## type ## __SHIFT

#घोषणा DDC_GPIO_I2C_REG_LIST(cd) \
	अणु\
	DDC_GPIO_I2C_REG_LIST_ENTRY(MASK,cd),\
	DDC_GPIO_I2C_REG_LIST_ENTRY(A,cd),\
	DDC_GPIO_I2C_REG_LIST_ENTRY(EN,cd),\
	DDC_GPIO_I2C_REG_LIST_ENTRY(Y,cd)\
	पूर्ण

#घोषणा DDC_I2C_REG_LIST(cd) \
	DDC_GPIO_I2C_REG_LIST(cd),\
	.ddc_setup = 0

#घोषणा DDC_I2C_REG_LIST_DCN2(cd) \
	DDC_GPIO_I2C_REG_LIST(cd),\
	.ddc_setup = 0,\
	.phy_aux_cntl = REG(PHY_AUX_CNTL), \
	.dc_gpio_aux_ctrl_5 = REG(DC_GPIO_AUX_CTRL_5)
#घोषणा DDC_MASK_SH_LIST_COMMON(mask_sh) \
		SF_DDC(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABLE, mask_sh),\
		SF_DDC(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_EDID_DETECT_ENABLE, mask_sh),\
		SF_DDC(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_EDID_DETECT_MODE, mask_sh),\
		SF_DDC(DC_GPIO_DDC1_MASK, DC_GPIO_DDC1DATA_PD_EN, mask_sh),\
		SF_DDC(DC_GPIO_DDC1_MASK, DC_GPIO_DDC1CLK_PD_EN, mask_sh),\
		SF_DDC(DC_GPIO_DDC1_MASK, AUX_PAD1_MODE, mask_sh)

#घोषणा DDC_MASK_SH_LIST(mask_sh) \
		DDC_MASK_SH_LIST_COMMON(mask_sh),\
		SF_DDC(DC_GPIO_I2CPAD_MASK, DC_GPIO_SDA_PD_DIS, mask_sh),\
		SF_DDC(DC_GPIO_I2CPAD_MASK, DC_GPIO_SCL_PD_DIS, mask_sh)

#घोषणा DDC_MASK_SH_LIST_DCN2(mask_sh, cd) \
	अणुDDC_MASK_SH_LIST_COMMON(mask_sh),\
	0,\
	0,\
	(PHY_AUX_CNTL__AUX## cd ##_PAD_RXSEL## mask_sh),\
	(DC_GPIO_AUX_CTRL_5__DDC_PAD## cd ##_I2CMODE## mask_sh)पूर्ण

काष्ठा ddc_रेजिस्टरs अणु
	काष्ठा gpio_रेजिस्टरs gpio;
	uपूर्णांक32_t ddc_setup;
	uपूर्णांक32_t phy_aux_cntl;
	uपूर्णांक32_t dc_gpio_aux_ctrl_5;
पूर्ण;

काष्ठा ddc_sh_mask अणु
	/* i2c_dd_setup */
	uपूर्णांक32_t DC_I2C_DDC1_ENABLE;
	uपूर्णांक32_t DC_I2C_DDC1_EDID_DETECT_ENABLE;
	uपूर्णांक32_t DC_I2C_DDC1_EDID_DETECT_MODE;
	/* ddc1_mask */
	uपूर्णांक32_t DC_GPIO_DDC1DATA_PD_EN;
	uपूर्णांक32_t DC_GPIO_DDC1CLK_PD_EN;
	uपूर्णांक32_t AUX_PAD1_MODE;
	/* i2cpad_mask */
	uपूर्णांक32_t DC_GPIO_SDA_PD_DIS;
	uपूर्णांक32_t DC_GPIO_SCL_PD_DIS;
	//phy_aux_cntl
	uपूर्णांक32_t AUX_PAD_RXSEL;
	uपूर्णांक32_t DDC_PAD_I2CMODE;
पूर्ण;



/*** following in dc_resource */

#घोषणा ddc_data_regs(id) \
अणु\
	DDC_REG_LIST(DATA,id)\
पूर्ण

#घोषणा ddc_clk_regs(id) \
अणु\
	DDC_REG_LIST(CLK,id)\
पूर्ण

#घोषणा ddc_vga_data_regs \
अणु\
	DDC_VGA_REG_LIST(DATA)\
पूर्ण

#घोषणा ddc_vga_clk_regs \
अणु\
	DDC_VGA_REG_LIST(CLK)\
पूर्ण

#घोषणा ddc_i2c_data_regs \
अणु\
	DDC_I2C_REG_LIST(SDA)\
पूर्ण

#घोषणा ddc_i2c_clk_regs \
अणु\
	DDC_I2C_REG_LIST(SCL)\
पूर्ण
#घोषणा ddc_data_regs_dcn2(id) \
अणु\
	DDC_REG_LIST_DCN2(DATA, id)\
पूर्ण

#घोषणा ddc_clk_regs_dcn2(id) \
अणु\
	DDC_REG_LIST_DCN2(CLK, id)\
पूर्ण

#घोषणा ddc_i2c_data_regs_dcn2 \
अणु\
	DDC_I2C_REG_LIST_DCN2(SDA)\
पूर्ण

#घोषणा ddc_i2c_clk_regs_dcn2 \
अणु\
	DDC_REG_LIST_DCN2(SCL)\
पूर्ण


#पूर्ण_अगर /* DRIVERS_GPU_DRM_AMD_DC_DEV_DC_GPIO_DDC_REGS_H_ */
