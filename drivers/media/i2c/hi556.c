<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Intel Corporation.

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>

#घोषणा HI556_REG_VALUE_08BIT		1
#घोषणा HI556_REG_VALUE_16BIT		2
#घोषणा HI556_REG_VALUE_24BIT		3

#घोषणा HI556_LINK_FREQ_437MHZ		437000000ULL
#घोषणा HI556_MCLK			19200000
#घोषणा HI556_DATA_LANES		2
#घोषणा HI556_RGB_DEPTH			10

#घोषणा HI556_REG_CHIP_ID		0x0f16
#घोषणा HI556_CHIP_ID			0x0556

#घोषणा HI556_REG_MODE_SELECT		0x0a00
#घोषणा HI556_MODE_STANDBY		0x0000
#घोषणा HI556_MODE_STREAMING		0x0100

/* vertical-timings from sensor */
#घोषणा HI556_REG_FLL			0x0006
#घोषणा HI556_FLL_30FPS			0x0814
#घोषणा HI556_FLL_30FPS_MIN		0x0814
#घोषणा HI556_FLL_MAX			0x7fff

/* horizontal-timings from sensor */
#घोषणा HI556_REG_LLP			0x0008

/* Exposure controls from sensor */
#घोषणा HI556_REG_EXPOSURE		0x0074
#घोषणा HI556_EXPOSURE_MIN		6
#घोषणा HI556_EXPOSURE_MAX_MARGIN	2
#घोषणा HI556_EXPOSURE_STEP		1

/* Analog gain controls from sensor */
#घोषणा HI556_REG_ANALOG_GAIN		0x0077
#घोषणा HI556_ANAL_GAIN_MIN		0
#घोषणा HI556_ANAL_GAIN_MAX		240
#घोषणा HI556_ANAL_GAIN_STEP		1

/* Digital gain controls from sensor */
#घोषणा HI556_REG_MWB_GR_GAIN		0x0078
#घोषणा HI556_REG_MWB_GB_GAIN		0x007a
#घोषणा HI556_REG_MWB_R_GAIN		0x007c
#घोषणा HI556_REG_MWB_B_GAIN		0x007e
#घोषणा HI556_DGTL_GAIN_MIN		0
#घोषणा HI556_DGTL_GAIN_MAX		2048
#घोषणा HI556_DGTL_GAIN_STEP		1
#घोषणा HI556_DGTL_GAIN_DEFAULT		256

/* Test Pattern Control */
#घोषणा HI556_REG_ISP			0X0a05
#घोषणा HI556_REG_ISP_TPG_EN		0x01
#घोषणा HI556_REG_TEST_PATTERN		0x0201

क्रमागत अणु
	HI556_LINK_FREQ_437MHZ_INDEX,
पूर्ण;

काष्ठा hi556_reg अणु
	u16 address;
	u16 val;
पूर्ण;

काष्ठा hi556_reg_list अणु
	u32 num_of_regs;
	स्थिर काष्ठा hi556_reg *regs;
पूर्ण;

काष्ठा hi556_link_freq_config अणु
	स्थिर काष्ठा hi556_reg_list reg_list;
पूर्ण;

काष्ठा hi556_mode अणु
	/* Frame width in pixels */
	u32 width;

	/* Frame height in pixels */
	u32 height;

	/* Horizontal timining size */
	u32 llp;

	/* Default vertical timining size */
	u32 fll_def;

	/* Min vertical timining size */
	u32 fll_min;

	/* Link frequency needed क्रम this resolution */
	u32 link_freq_index;

	/* Sensor रेजिस्टर settings क्रम this resolution */
	स्थिर काष्ठा hi556_reg_list reg_list;
पूर्ण;

#घोषणा to_hi556(_sd) container_of(_sd, काष्ठा hi556, sd)

//SENSOR_INITIALIZATION
अटल स्थिर काष्ठा hi556_reg mipi_data_rate_874mbps[] = अणु
	अणु0x0e00, 0x0102पूर्ण,
	अणु0x0e02, 0x0102पूर्ण,
	अणु0x0e0c, 0x0100पूर्ण,
	अणु0x2000, 0x7400पूर्ण,
	अणु0x2002, 0x001cपूर्ण,
	अणु0x2004, 0x0242पूर्ण,
	अणु0x2006, 0x0942पूर्ण,
	अणु0x2008, 0x7007पूर्ण,
	अणु0x200a, 0x0fd9पूर्ण,
	अणु0x200c, 0x0259पूर्ण,
	अणु0x200e, 0x7008पूर्ण,
	अणु0x2010, 0x160eपूर्ण,
	अणु0x2012, 0x0047पूर्ण,
	अणु0x2014, 0x2118पूर्ण,
	अणु0x2016, 0x0041पूर्ण,
	अणु0x2018, 0x00d8पूर्ण,
	अणु0x201a, 0x0145पूर्ण,
	अणु0x201c, 0x0006पूर्ण,
	अणु0x201e, 0x0181पूर्ण,
	अणु0x2020, 0x13ccपूर्ण,
	अणु0x2022, 0x2057पूर्ण,
	अणु0x2024, 0x7001पूर्ण,
	अणु0x2026, 0x0fcaपूर्ण,
	अणु0x2028, 0x00cbपूर्ण,
	अणु0x202a, 0x009fपूर्ण,
	अणु0x202c, 0x7002पूर्ण,
	अणु0x202e, 0x13ccपूर्ण,
	अणु0x2030, 0x019bपूर्ण,
	अणु0x2032, 0x014dपूर्ण,
	अणु0x2034, 0x2987पूर्ण,
	अणु0x2036, 0x2766पूर्ण,
	अणु0x2038, 0x0020पूर्ण,
	अणु0x203a, 0x2060पूर्ण,
	अणु0x203c, 0x0e5dपूर्ण,
	अणु0x203e, 0x181dपूर्ण,
	अणु0x2040, 0x2066पूर्ण,
	अणु0x2042, 0x20c4पूर्ण,
	अणु0x2044, 0x5000पूर्ण,
	अणु0x2046, 0x0005पूर्ण,
	अणु0x2048, 0x0000पूर्ण,
	अणु0x204a, 0x01dbपूर्ण,
	अणु0x204c, 0x025aपूर्ण,
	अणु0x204e, 0x00c0पूर्ण,
	अणु0x2050, 0x0005पूर्ण,
	अणु0x2052, 0x0006पूर्ण,
	अणु0x2054, 0x0ad9पूर्ण,
	अणु0x2056, 0x0259पूर्ण,
	अणु0x2058, 0x0618पूर्ण,
	अणु0x205a, 0x0258पूर्ण,
	अणु0x205c, 0x2266पूर्ण,
	अणु0x205e, 0x20c8पूर्ण,
	अणु0x2060, 0x2060पूर्ण,
	अणु0x2062, 0x707bपूर्ण,
	अणु0x2064, 0x0fddपूर्ण,
	अणु0x2066, 0x81b8पूर्ण,
	अणु0x2068, 0x5040पूर्ण,
	अणु0x206a, 0x0020पूर्ण,
	अणु0x206c, 0x5060पूर्ण,
	अणु0x206e, 0x3143पूर्ण,
	अणु0x2070, 0x5081पूर्ण,
	अणु0x2072, 0x025cपूर्ण,
	अणु0x2074, 0x7800पूर्ण,
	अणु0x2076, 0x7400पूर्ण,
	अणु0x2078, 0x001cपूर्ण,
	अणु0x207a, 0x0242पूर्ण,
	अणु0x207c, 0x0942पूर्ण,
	अणु0x207e, 0x0bd9पूर्ण,
	अणु0x2080, 0x0259पूर्ण,
	अणु0x2082, 0x7008पूर्ण,
	अणु0x2084, 0x160eपूर्ण,
	अणु0x2086, 0x0047पूर्ण,
	अणु0x2088, 0x2118पूर्ण,
	अणु0x208a, 0x0041पूर्ण,
	अणु0x208c, 0x00d8पूर्ण,
	अणु0x208e, 0x0145पूर्ण,
	अणु0x2090, 0x0006पूर्ण,
	अणु0x2092, 0x0181पूर्ण,
	अणु0x2094, 0x13ccपूर्ण,
	अणु0x2096, 0x2057पूर्ण,
	अणु0x2098, 0x7001पूर्ण,
	अणु0x209a, 0x0fcaपूर्ण,
	अणु0x209c, 0x00cbपूर्ण,
	अणु0x209e, 0x009fपूर्ण,
	अणु0x20a0, 0x7002पूर्ण,
	अणु0x20a2, 0x13ccपूर्ण,
	अणु0x20a4, 0x019bपूर्ण,
	अणु0x20a6, 0x014dपूर्ण,
	अणु0x20a8, 0x2987पूर्ण,
	अणु0x20aa, 0x2766पूर्ण,
	अणु0x20ac, 0x0020पूर्ण,
	अणु0x20ae, 0x2060पूर्ण,
	अणु0x20b0, 0x0e5dपूर्ण,
	अणु0x20b2, 0x181dपूर्ण,
	अणु0x20b4, 0x2066पूर्ण,
	अणु0x20b6, 0x20c4पूर्ण,
	अणु0x20b8, 0x50a0पूर्ण,
	अणु0x20ba, 0x0005पूर्ण,
	अणु0x20bc, 0x0000पूर्ण,
	अणु0x20be, 0x01dbपूर्ण,
	अणु0x20c0, 0x025aपूर्ण,
	अणु0x20c2, 0x00c0पूर्ण,
	अणु0x20c4, 0x0005पूर्ण,
	अणु0x20c6, 0x0006पूर्ण,
	अणु0x20c8, 0x0ad9पूर्ण,
	अणु0x20ca, 0x0259पूर्ण,
	अणु0x20cc, 0x0618पूर्ण,
	अणु0x20ce, 0x0258पूर्ण,
	अणु0x20d0, 0x2266पूर्ण,
	अणु0x20d2, 0x20c8पूर्ण,
	अणु0x20d4, 0x2060पूर्ण,
	अणु0x20d6, 0x707bपूर्ण,
	अणु0x20d8, 0x0fddपूर्ण,
	अणु0x20da, 0x86b8पूर्ण,
	अणु0x20dc, 0x50e0पूर्ण,
	अणु0x20de, 0x0020पूर्ण,
	अणु0x20e0, 0x5100पूर्ण,
	अणु0x20e2, 0x3143पूर्ण,
	अणु0x20e4, 0x5121पूर्ण,
	अणु0x20e6, 0x7800पूर्ण,
	अणु0x20e8, 0x3140पूर्ण,
	अणु0x20ea, 0x01c4पूर्ण,
	अणु0x20ec, 0x01c1पूर्ण,
	अणु0x20ee, 0x01c0पूर्ण,
	अणु0x20f0, 0x01c4पूर्ण,
	अणु0x20f2, 0x2700पूर्ण,
	अणु0x20f4, 0x3d40पूर्ण,
	अणु0x20f6, 0x7800पूर्ण,
	अणु0x20f8, 0xffffपूर्ण,
	अणु0x27fe, 0xe000पूर्ण,
	अणु0x3000, 0x60f8पूर्ण,
	अणु0x3002, 0x187fपूर्ण,
	अणु0x3004, 0x7060पूर्ण,
	अणु0x3006, 0x0114पूर्ण,
	अणु0x3008, 0x60b0पूर्ण,
	अणु0x300a, 0x1473पूर्ण,
	अणु0x300c, 0x0013पूर्ण,
	अणु0x300e, 0x140fपूर्ण,
	अणु0x3010, 0x0040पूर्ण,
	अणु0x3012, 0x100fपूर्ण,
	अणु0x3014, 0x60f8पूर्ण,
	अणु0x3016, 0x187fपूर्ण,
	अणु0x3018, 0x7060पूर्ण,
	अणु0x301a, 0x0114पूर्ण,
	अणु0x301c, 0x60b0पूर्ण,
	अणु0x301e, 0x1473पूर्ण,
	अणु0x3020, 0x0013पूर्ण,
	अणु0x3022, 0x140fपूर्ण,
	अणु0x3024, 0x0040पूर्ण,
	अणु0x3026, 0x000fपूर्ण,

	अणु0x0b00, 0x0000पूर्ण,
	अणु0x0b02, 0x0045पूर्ण,
	अणु0x0b04, 0xb405पूर्ण,
	अणु0x0b06, 0xc403पूर्ण,
	अणु0x0b08, 0x0081पूर्ण,
	अणु0x0b0a, 0x8252पूर्ण,
	अणु0x0b0c, 0xf814पूर्ण,
	अणु0x0b0e, 0xc618पूर्ण,
	अणु0x0b10, 0xa828पूर्ण,
	अणु0x0b12, 0x004cपूर्ण,
	अणु0x0b14, 0x4068पूर्ण,
	अणु0x0b16, 0x0000पूर्ण,
	अणु0x0f30, 0x5b15पूर्ण,
	अणु0x0f32, 0x7067पूर्ण,
	अणु0x0954, 0x0009पूर्ण,
	अणु0x0956, 0x0000पूर्ण,
	अणु0x0958, 0xbb80पूर्ण,
	अणु0x095a, 0x5140पूर्ण,
	अणु0x0c00, 0x1110पूर्ण,
	अणु0x0c02, 0x0011पूर्ण,
	अणु0x0c04, 0x0000पूर्ण,
	अणु0x0c06, 0x0200पूर्ण,
	अणु0x0c10, 0x0040पूर्ण,
	अणु0x0c12, 0x0040पूर्ण,
	अणु0x0c14, 0x0040पूर्ण,
	अणु0x0c16, 0x0040पूर्ण,
	अणु0x0a10, 0x4000पूर्ण,
	अणु0x3068, 0xf800पूर्ण,
	अणु0x306a, 0xf876पूर्ण,
	अणु0x006c, 0x0000पूर्ण,
	अणु0x005e, 0x0200पूर्ण,
	अणु0x000e, 0x0100पूर्ण,
	अणु0x0e0a, 0x0001पूर्ण,
	अणु0x004a, 0x0100पूर्ण,
	अणु0x004c, 0x0000पूर्ण,
	अणु0x004e, 0x0100पूर्ण,
	अणु0x000c, 0x0022पूर्ण,
	अणु0x0008, 0x0b00पूर्ण,
	अणु0x005a, 0x0202पूर्ण,
	अणु0x0012, 0x000eपूर्ण,
	अणु0x0018, 0x0a33पूर्ण,
	अणु0x0022, 0x0008पूर्ण,
	अणु0x0028, 0x0017पूर्ण,
	अणु0x0024, 0x0028पूर्ण,
	अणु0x002a, 0x002dपूर्ण,
	अणु0x0026, 0x0030पूर्ण,
	अणु0x002c, 0x07c9पूर्ण,
	अणु0x002e, 0x1111पूर्ण,
	अणु0x0030, 0x1111पूर्ण,
	अणु0x0032, 0x1111पूर्ण,
	अणु0x0006, 0x07bcपूर्ण,
	अणु0x0a22, 0x0000पूर्ण,
	अणु0x0a12, 0x0a20पूर्ण,
	अणु0x0a14, 0x0798पूर्ण,
	अणु0x003e, 0x0000पूर्ण,
	अणु0x0074, 0x080eपूर्ण,
	अणु0x0070, 0x0407पूर्ण,
	अणु0x0002, 0x0000पूर्ण,
	अणु0x0a02, 0x0100पूर्ण,
	अणु0x0a24, 0x0100पूर्ण,
	अणु0x0046, 0x0000पूर्ण,
	अणु0x0076, 0x0000पूर्ण,
	अणु0x0060, 0x0000पूर्ण,
	अणु0x0062, 0x0530पूर्ण,
	अणु0x0064, 0x0500पूर्ण,
	अणु0x0066, 0x0530पूर्ण,
	अणु0x0068, 0x0500पूर्ण,
	अणु0x0122, 0x0300पूर्ण,
	अणु0x015a, 0xff08पूर्ण,
	अणु0x0804, 0x0300पूर्ण,
	अणु0x0806, 0x0100पूर्ण,
	अणु0x005c, 0x0102पूर्ण,
	अणु0x0a1a, 0x0800पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hi556_reg mode_2592x1944_regs[] = अणु
	अणु0x0a00, 0x0000पूर्ण,
	अणु0x0b0a, 0x8252पूर्ण,
	अणु0x0f30, 0x5b15पूर्ण,
	अणु0x0f32, 0x7067पूर्ण,
	अणु0x004a, 0x0100पूर्ण,
	अणु0x004c, 0x0000पूर्ण,
	अणु0x004e, 0x0100पूर्ण,
	अणु0x000c, 0x0022पूर्ण,
	अणु0x0008, 0x0b00पूर्ण,
	अणु0x005a, 0x0202पूर्ण,
	अणु0x0012, 0x000eपूर्ण,
	अणु0x0018, 0x0a33पूर्ण,
	अणु0x0022, 0x0008पूर्ण,
	अणु0x0028, 0x0017पूर्ण,
	अणु0x0024, 0x0028पूर्ण,
	अणु0x002a, 0x002dपूर्ण,
	अणु0x0026, 0x0030पूर्ण,
	अणु0x002c, 0x07c9पूर्ण,
	अणु0x002e, 0x1111पूर्ण,
	अणु0x0030, 0x1111पूर्ण,
	अणु0x0032, 0x1111पूर्ण,
	अणु0x0006, 0x0814पूर्ण,
	अणु0x0a22, 0x0000पूर्ण,
	अणु0x0a12, 0x0a20पूर्ण,
	अणु0x0a14, 0x0798पूर्ण,
	अणु0x003e, 0x0000पूर्ण,
	अणु0x0074, 0x0812पूर्ण,
	अणु0x0070, 0x0409पूर्ण,
	अणु0x0804, 0x0300पूर्ण,
	अणु0x0806, 0x0100पूर्ण,
	अणु0x0a04, 0x014aपूर्ण,
	अणु0x090c, 0x0fdcपूर्ण,
	अणु0x090e, 0x002dपूर्ण,

	अणु0x0902, 0x4319पूर्ण,
	अणु0x0914, 0xc10aपूर्ण,
	अणु0x0916, 0x071fपूर्ण,
	अणु0x0918, 0x0408पूर्ण,
	अणु0x091a, 0x0c0dपूर्ण,
	अणु0x091c, 0x0f09पूर्ण,
	अणु0x091e, 0x0a00पूर्ण,
	अणु0x0958, 0xbb80पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hi556_reg mode_1296x972_regs[] = अणु
	अणु0x0a00, 0x0000पूर्ण,
	अणु0x0b0a, 0x8259पूर्ण,
	अणु0x0f30, 0x5b15पूर्ण,
	अणु0x0f32, 0x7167पूर्ण,
	अणु0x004a, 0x0100पूर्ण,
	अणु0x004c, 0x0000पूर्ण,
	अणु0x004e, 0x0100पूर्ण,
	अणु0x000c, 0x0122पूर्ण,
	अणु0x0008, 0x0b00पूर्ण,
	अणु0x005a, 0x0404पूर्ण,
	अणु0x0012, 0x000cपूर्ण,
	अणु0x0018, 0x0a33पूर्ण,
	अणु0x0022, 0x0008पूर्ण,
	अणु0x0028, 0x0017पूर्ण,
	अणु0x0024, 0x0022पूर्ण,
	अणु0x002a, 0x002bपूर्ण,
	अणु0x0026, 0x0030पूर्ण,
	अणु0x002c, 0x07c9पूर्ण,
	अणु0x002e, 0x3311पूर्ण,
	अणु0x0030, 0x3311पूर्ण,
	अणु0x0032, 0x3311पूर्ण,
	अणु0x0006, 0x0814पूर्ण,
	अणु0x0a22, 0x0000पूर्ण,
	अणु0x0a12, 0x0510पूर्ण,
	अणु0x0a14, 0x03ccपूर्ण,
	अणु0x003e, 0x0000पूर्ण,
	अणु0x0074, 0x0812पूर्ण,
	अणु0x0070, 0x0409पूर्ण,
	अणु0x0804, 0x0308पूर्ण,
	अणु0x0806, 0x0100पूर्ण,
	अणु0x0a04, 0x016aपूर्ण,
	अणु0x090e, 0x0010पूर्ण,
	अणु0x090c, 0x09c0पूर्ण,

	अणु0x0902, 0x4319पूर्ण,
	अणु0x0914, 0xc106पूर्ण,
	अणु0x0916, 0x040eपूर्ण,
	अणु0x0918, 0x0304पूर्ण,
	अणु0x091a, 0x0708पूर्ण,
	अणु0x091c, 0x0e06पूर्ण,
	अणु0x091e, 0x0300पूर्ण,
	अणु0x0958, 0xbb80पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर hi556_test_pattern_menu[] = अणु
	"Disabled",
	"Solid Colour",
	"100% Colour Bars",
	"Fade To Grey Colour Bars",
	"PN9",
	"Gradient Horizontal",
	"Gradient Vertical",
	"Check Board",
	"Slant Pattern",
पूर्ण;

अटल स्थिर s64 link_freq_menu_items[] = अणु
	HI556_LINK_FREQ_437MHZ,
पूर्ण;

अटल स्थिर काष्ठा hi556_link_freq_config link_freq_configs[] = अणु
	[HI556_LINK_FREQ_437MHZ_INDEX] = अणु
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mipi_data_rate_874mbps),
			.regs = mipi_data_rate_874mbps,
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hi556_mode supported_modes[] = अणु
	अणु
		.width = 2592,
		.height = 1944,
		.fll_def = HI556_FLL_30FPS,
		.fll_min = HI556_FLL_30FPS_MIN,
		.llp = 0x0b00,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_2592x1944_regs),
			.regs = mode_2592x1944_regs,
		पूर्ण,
		.link_freq_index = HI556_LINK_FREQ_437MHZ_INDEX,
	पूर्ण,
	अणु
		.width = 1296,
		.height = 972,
		.fll_def = HI556_FLL_30FPS,
		.fll_min = HI556_FLL_30FPS_MIN,
		.llp = 0x0b00,
		.reg_list = अणु
			.num_of_regs = ARRAY_SIZE(mode_1296x972_regs),
			.regs = mode_1296x972_regs,
		पूर्ण,
		.link_freq_index = HI556_LINK_FREQ_437MHZ_INDEX,
	पूर्ण
पूर्ण;

काष्ठा hi556 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	/* V4L2 Controls */
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *pixel_rate;
	काष्ठा v4l2_ctrl *vblank;
	काष्ठा v4l2_ctrl *hblank;
	काष्ठा v4l2_ctrl *exposure;

	/* Current mode */
	स्थिर काष्ठा hi556_mode *cur_mode;

	/* To serialize asynchronus callbacks */
	काष्ठा mutex mutex;

	/* Streaming on/off */
	bool streaming;
पूर्ण;

अटल u64 to_pixel_rate(u32 f_index)
अणु
	u64 pixel_rate = link_freq_menu_items[f_index] * 2 * HI556_DATA_LANES;

	करो_भाग(pixel_rate, HI556_RGB_DEPTH);

	वापस pixel_rate;
पूर्ण

अटल पूर्णांक hi556_पढ़ो_reg(काष्ठा hi556 *hi556, u16 reg, u16 len, u32 *val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&hi556->sd);
	काष्ठा i2c_msg msgs[2];
	u8 addr_buf[2];
	u8 data_buf[4] = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (len > 4)
		वापस -EINVAL;

	put_unaligned_be16(reg, addr_buf);
	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = माप(addr_buf);
	msgs[0].buf = addr_buf;
	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = &data_buf[4 - len];

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs))
		वापस -EIO;

	*val = get_unaligned_be32(data_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक hi556_ग_लिखो_reg(काष्ठा hi556 *hi556, u16 reg, u16 len, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&hi556->sd);
	u8 buf[6];

	अगर (len > 4)
		वापस -EINVAL;

	put_unaligned_be16(reg, buf);
	put_unaligned_be32(val << 8 * (4 - len), buf + 2);
	अगर (i2c_master_send(client, buf, len + 2) != len + 2)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक hi556_ग_लिखो_reg_list(काष्ठा hi556 *hi556,
				स्थिर काष्ठा hi556_reg_list *r_list)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&hi556->sd);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < r_list->num_of_regs; i++) अणु
		ret = hi556_ग_लिखो_reg(hi556, r_list->regs[i].address,
				      HI556_REG_VALUE_16BIT,
				      r_list->regs[i].val);
		अगर (ret) अणु
			dev_err_ratelimited(&client->dev,
					    "failed to write reg 0x%4.4x. error = %d",
					    r_list->regs[i].address, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hi556_update_digital_gain(काष्ठा hi556 *hi556, u32 d_gain)
अणु
	पूर्णांक ret;

	ret = hi556_ग_लिखो_reg(hi556, HI556_REG_MWB_GR_GAIN,
			      HI556_REG_VALUE_16BIT, d_gain);
	अगर (ret)
		वापस ret;

	ret = hi556_ग_लिखो_reg(hi556, HI556_REG_MWB_GB_GAIN,
			      HI556_REG_VALUE_16BIT, d_gain);
	अगर (ret)
		वापस ret;

	ret = hi556_ग_लिखो_reg(hi556, HI556_REG_MWB_R_GAIN,
			      HI556_REG_VALUE_16BIT, d_gain);
	अगर (ret)
		वापस ret;

	वापस hi556_ग_लिखो_reg(hi556, HI556_REG_MWB_B_GAIN,
			       HI556_REG_VALUE_16BIT, d_gain);
पूर्ण

अटल पूर्णांक hi556_test_pattern(काष्ठा hi556 *hi556, u32 pattern)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (pattern) अणु
		ret = hi556_पढ़ो_reg(hi556, HI556_REG_ISP,
				     HI556_REG_VALUE_08BIT, &val);
		अगर (ret)
			वापस ret;

		ret = hi556_ग_लिखो_reg(hi556, HI556_REG_ISP,
				      HI556_REG_VALUE_08BIT,
				      val | HI556_REG_ISP_TPG_EN);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस hi556_ग_लिखो_reg(hi556, HI556_REG_TEST_PATTERN,
			       HI556_REG_VALUE_08BIT, pattern);
पूर्ण

अटल पूर्णांक hi556_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा hi556 *hi556 = container_of(ctrl->handler,
					     काष्ठा hi556, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&hi556->sd);
	s64 exposure_max;
	पूर्णांक ret = 0;

	/* Propagate change of current control to all related controls */
	अगर (ctrl->id == V4L2_CID_VBLANK) अणु
		/* Update max exposure जबतक meeting expected vblanking */
		exposure_max = hi556->cur_mode->height + ctrl->val -
			       HI556_EXPOSURE_MAX_MARGIN;
		__v4l2_ctrl_modअगरy_range(hi556->exposure,
					 hi556->exposure->minimum,
					 exposure_max, hi556->exposure->step,
					 exposure_max);
	पूर्ण

	/* V4L2 controls values will be applied only when घातer is alपढ़ोy up */
	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ANALOGUE_GAIN:
		ret = hi556_ग_लिखो_reg(hi556, HI556_REG_ANALOG_GAIN,
				      HI556_REG_VALUE_16BIT, ctrl->val);
		अवरोध;

	हाल V4L2_CID_DIGITAL_GAIN:
		ret = hi556_update_digital_gain(hi556, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE:
		ret = hi556_ग_लिखो_reg(hi556, HI556_REG_EXPOSURE,
				      HI556_REG_VALUE_16BIT, ctrl->val);
		अवरोध;

	हाल V4L2_CID_VBLANK:
		/* Update FLL that meets expected vertical blanking */
		ret = hi556_ग_लिखो_reg(hi556, HI556_REG_FLL,
				      HI556_REG_VALUE_16BIT,
				      hi556->cur_mode->height + ctrl->val);
		अवरोध;

	हाल V4L2_CID_TEST_PATTERN:
		ret = hi556_test_pattern(hi556, ctrl->val);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops hi556_ctrl_ops = अणु
	.s_ctrl = hi556_set_ctrl,
पूर्ण;

अटल पूर्णांक hi556_init_controls(काष्ठा hi556 *hi556)
अणु
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr;
	s64 exposure_max, h_blank;
	पूर्णांक ret;

	ctrl_hdlr = &hi556->ctrl_handler;
	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 8);
	अगर (ret)
		वापस ret;

	ctrl_hdlr->lock = &hi556->mutex;
	hi556->link_freq = v4l2_ctrl_new_पूर्णांक_menu(ctrl_hdlr, &hi556_ctrl_ops,
						  V4L2_CID_LINK_FREQ,
					ARRAY_SIZE(link_freq_menu_items) - 1,
					0, link_freq_menu_items);
	अगर (hi556->link_freq)
		hi556->link_freq->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	hi556->pixel_rate = v4l2_ctrl_new_std
			    (ctrl_hdlr, &hi556_ctrl_ops,
			     V4L2_CID_PIXEL_RATE, 0,
			     to_pixel_rate(HI556_LINK_FREQ_437MHZ_INDEX),
			     1,
			     to_pixel_rate(HI556_LINK_FREQ_437MHZ_INDEX));
	hi556->vblank = v4l2_ctrl_new_std(ctrl_hdlr, &hi556_ctrl_ops,
					  V4L2_CID_VBLANK,
					  hi556->cur_mode->fll_min -
					  hi556->cur_mode->height,
					  HI556_FLL_MAX -
					  hi556->cur_mode->height, 1,
					  hi556->cur_mode->fll_def -
					  hi556->cur_mode->height);

	h_blank = hi556->cur_mode->llp - hi556->cur_mode->width;

	hi556->hblank = v4l2_ctrl_new_std(ctrl_hdlr, &hi556_ctrl_ops,
					  V4L2_CID_HBLANK, h_blank, h_blank, 1,
					  h_blank);
	अगर (hi556->hblank)
		hi556->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	v4l2_ctrl_new_std(ctrl_hdlr, &hi556_ctrl_ops, V4L2_CID_ANALOGUE_GAIN,
			  HI556_ANAL_GAIN_MIN, HI556_ANAL_GAIN_MAX,
			  HI556_ANAL_GAIN_STEP, HI556_ANAL_GAIN_MIN);
	v4l2_ctrl_new_std(ctrl_hdlr, &hi556_ctrl_ops, V4L2_CID_DIGITAL_GAIN,
			  HI556_DGTL_GAIN_MIN, HI556_DGTL_GAIN_MAX,
			  HI556_DGTL_GAIN_STEP, HI556_DGTL_GAIN_DEFAULT);
	exposure_max = hi556->cur_mode->fll_def - HI556_EXPOSURE_MAX_MARGIN;
	hi556->exposure = v4l2_ctrl_new_std(ctrl_hdlr, &hi556_ctrl_ops,
					    V4L2_CID_EXPOSURE,
					    HI556_EXPOSURE_MIN, exposure_max,
					    HI556_EXPOSURE_STEP,
					    exposure_max);
	v4l2_ctrl_new_std_menu_items(ctrl_hdlr, &hi556_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(hi556_test_pattern_menu) - 1,
				     0, 0, hi556_test_pattern_menu);
	अगर (ctrl_hdlr->error)
		वापस ctrl_hdlr->error;

	hi556->sd.ctrl_handler = ctrl_hdlr;

	वापस 0;
पूर्ण

अटल व्योम hi556_assign_pad_क्रमmat(स्थिर काष्ठा hi556_mode *mode,
				    काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	fmt->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक hi556_start_streaming(काष्ठा hi556 *hi556)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&hi556->sd);
	स्थिर काष्ठा hi556_reg_list *reg_list;
	पूर्णांक link_freq_index, ret;

	link_freq_index = hi556->cur_mode->link_freq_index;
	reg_list = &link_freq_configs[link_freq_index].reg_list;
	ret = hi556_ग_लिखो_reg_list(hi556, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set plls");
		वापस ret;
	पूर्ण

	reg_list = &hi556->cur_mode->reg_list;
	ret = hi556_ग_लिखो_reg_list(hi556, reg_list);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set mode");
		वापस ret;
	पूर्ण

	ret = __v4l2_ctrl_handler_setup(hi556->sd.ctrl_handler);
	अगर (ret)
		वापस ret;

	ret = hi556_ग_लिखो_reg(hi556, HI556_REG_MODE_SELECT,
			      HI556_REG_VALUE_16BIT, HI556_MODE_STREAMING);

	अगर (ret) अणु
		dev_err(&client->dev, "failed to set stream");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hi556_stop_streaming(काष्ठा hi556 *hi556)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&hi556->sd);

	अगर (hi556_ग_लिखो_reg(hi556, HI556_REG_MODE_SELECT,
			    HI556_REG_VALUE_16BIT, HI556_MODE_STANDBY))
		dev_err(&client->dev, "failed to set stream");
पूर्ण

अटल पूर्णांक hi556_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा hi556 *hi556 = to_hi556(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (hi556->streaming == enable)
		वापस 0;

	mutex_lock(&hi556->mutex);
	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			mutex_unlock(&hi556->mutex);
			वापस ret;
		पूर्ण

		ret = hi556_start_streaming(hi556);
		अगर (ret) अणु
			enable = 0;
			hi556_stop_streaming(hi556);
			pm_runसमय_put(&client->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		hi556_stop_streaming(hi556);
		pm_runसमय_put(&client->dev);
	पूर्ण

	hi556->streaming = enable;
	mutex_unlock(&hi556->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused hi556_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा hi556 *hi556 = to_hi556(sd);

	mutex_lock(&hi556->mutex);
	अगर (hi556->streaming)
		hi556_stop_streaming(hi556);

	mutex_unlock(&hi556->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hi556_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा hi556 *hi556 = to_hi556(sd);
	पूर्णांक ret;

	mutex_lock(&hi556->mutex);
	अगर (hi556->streaming) अणु
		ret = hi556_start_streaming(hi556);
		अगर (ret)
			जाओ error;
	पूर्ण

	mutex_unlock(&hi556->mutex);

	वापस 0;

error:
	hi556_stop_streaming(hi556);
	hi556->streaming = 0;
	mutex_unlock(&hi556->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक hi556_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा hi556 *hi556 = to_hi556(sd);
	स्थिर काष्ठा hi556_mode *mode;
	s32 vblank_def, h_blank;

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes), width,
				      height, fmt->क्रमmat.width,
				      fmt->क्रमmat.height);

	mutex_lock(&hi556->mutex);
	hi556_assign_pad_क्रमmat(mode, &fmt->क्रमmat);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad) = fmt->क्रमmat;
	पूर्ण अन्यथा अणु
		hi556->cur_mode = mode;
		__v4l2_ctrl_s_ctrl(hi556->link_freq, mode->link_freq_index);
		__v4l2_ctrl_s_ctrl_पूर्णांक64(hi556->pixel_rate,
					 to_pixel_rate(mode->link_freq_index));

		/* Update limits and set FPS to शेष */
		vblank_def = mode->fll_def - mode->height;
		__v4l2_ctrl_modअगरy_range(hi556->vblank,
					 mode->fll_min - mode->height,
					 HI556_FLL_MAX - mode->height, 1,
					 vblank_def);
		__v4l2_ctrl_s_ctrl(hi556->vblank, vblank_def);

		h_blank = hi556->cur_mode->llp - hi556->cur_mode->width;

		__v4l2_ctrl_modअगरy_range(hi556->hblank, h_blank, h_blank, 1,
					 h_blank);
	पूर्ण

	mutex_unlock(&hi556->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hi556_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा hi556 *hi556 = to_hi556(sd);

	mutex_lock(&hi556->mutex);
	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		fmt->क्रमmat = *v4l2_subdev_get_try_क्रमmat(&hi556->sd, cfg,
							  fmt->pad);
	अन्यथा
		hi556_assign_pad_क्रमmat(hi556->cur_mode, &fmt->क्रमmat);

	mutex_unlock(&hi556->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hi556_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_SGRBG10_1X10;

	वापस 0;
पूर्ण

अटल पूर्णांक hi556_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->index >= ARRAY_SIZE(supported_modes))
		वापस -EINVAL;

	अगर (fse->code != MEDIA_BUS_FMT_SGRBG10_1X10)
		वापस -EINVAL;

	fse->min_width = supported_modes[fse->index].width;
	fse->max_width = fse->min_width;
	fse->min_height = supported_modes[fse->index].height;
	fse->max_height = fse->min_height;

	वापस 0;
पूर्ण

अटल पूर्णांक hi556_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा hi556 *hi556 = to_hi556(sd);

	mutex_lock(&hi556->mutex);
	hi556_assign_pad_क्रमmat(&supported_modes[0],
				v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0));
	mutex_unlock(&hi556->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops hi556_video_ops = अणु
	.s_stream = hi556_set_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops hi556_pad_ops = अणु
	.set_fmt = hi556_set_क्रमmat,
	.get_fmt = hi556_get_क्रमmat,
	.क्रमागत_mbus_code = hi556_क्रमागत_mbus_code,
	.क्रमागत_frame_size = hi556_क्रमागत_frame_size,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops hi556_subdev_ops = अणु
	.video = &hi556_video_ops,
	.pad = &hi556_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations hi556_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops hi556_पूर्णांकernal_ops = अणु
	.खोलो = hi556_खोलो,
पूर्ण;

अटल पूर्णांक hi556_identअगरy_module(काष्ठा hi556 *hi556)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&hi556->sd);
	पूर्णांक ret;
	u32 val;

	ret = hi556_पढ़ो_reg(hi556, HI556_REG_CHIP_ID,
			     HI556_REG_VALUE_16BIT, &val);
	अगर (ret)
		वापस ret;

	अगर (val != HI556_CHIP_ID) अणु
		dev_err(&client->dev, "chip id mismatch: %x!=%x",
			HI556_CHIP_ID, val);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hi556_check_hwcfg(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *ep;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	u32 mclk;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i, j;

	अगर (!fwnode)
		वापस -ENXIO;

	ret = fwnode_property_पढ़ो_u32(fwnode, "clock-frequency", &mclk);
	अगर (ret) अणु
		dev_err(dev, "can't get clock frequency");
		वापस ret;
	पूर्ण

	अगर (mclk != HI556_MCLK) अणु
		dev_err(dev, "external clock %d is not supported", mclk);
		वापस -EINVAL;
	पूर्ण

	ep = fwnode_graph_get_next_endpoपूर्णांक(fwnode, शून्य);
	अगर (!ep)
		वापस -ENXIO;

	ret = v4l2_fwnode_endpoपूर्णांक_alloc_parse(ep, &bus_cfg);
	fwnode_handle_put(ep);
	अगर (ret)
		वापस ret;

	अगर (bus_cfg.bus.mipi_csi2.num_data_lanes != 2) अणु
		dev_err(dev, "number of CSI2 data lanes %d is not supported",
			bus_cfg.bus.mipi_csi2.num_data_lanes);
		ret = -EINVAL;
		जाओ check_hwcfg_error;
	पूर्ण

	अगर (!bus_cfg.nr_of_link_frequencies) अणु
		dev_err(dev, "no link frequencies defined");
		ret = -EINVAL;
		जाओ check_hwcfg_error;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(link_freq_menu_items); i++) अणु
		क्रम (j = 0; j < bus_cfg.nr_of_link_frequencies; j++) अणु
			अगर (link_freq_menu_items[i] ==
				bus_cfg.link_frequencies[j])
				अवरोध;
		पूर्ण

		अगर (j == bus_cfg.nr_of_link_frequencies) अणु
			dev_err(dev, "no link frequency %lld supported",
				link_freq_menu_items[i]);
			ret = -EINVAL;
			जाओ check_hwcfg_error;
		पूर्ण
	पूर्ण

check_hwcfg_error:
	v4l2_fwnode_endpoपूर्णांक_मुक्त(&bus_cfg);

	वापस ret;
पूर्ण

अटल पूर्णांक hi556_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा hi556 *hi556 = to_hi556(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	pm_runसमय_disable(&client->dev);
	mutex_destroy(&hi556->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hi556_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा hi556 *hi556;
	पूर्णांक ret;

	ret = hi556_check_hwcfg(&client->dev);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to check HW configuration: %d",
			ret);
		वापस ret;
	पूर्ण

	hi556 = devm_kzalloc(&client->dev, माप(*hi556), GFP_KERNEL);
	अगर (!hi556)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&hi556->sd, client, &hi556_subdev_ops);
	ret = hi556_identअगरy_module(hi556);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to find sensor: %d", ret);
		वापस ret;
	पूर्ण

	mutex_init(&hi556->mutex);
	hi556->cur_mode = &supported_modes[0];
	ret = hi556_init_controls(hi556);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init controls: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	hi556->sd.पूर्णांकernal_ops = &hi556_पूर्णांकernal_ops;
	hi556->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	hi556->sd.entity.ops = &hi556_subdev_entity_ops;
	hi556->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	hi556->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&hi556->sd.entity, 1, &hi556->pad);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to init entity pads: %d", ret);
		जाओ probe_error_v4l2_ctrl_handler_मुक्त;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&hi556->sd);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to register V4L2 subdev: %d",
			ret);
		जाओ probe_error_media_entity_cleanup;
	पूर्ण

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

probe_error_media_entity_cleanup:
	media_entity_cleanup(&hi556->sd.entity);

probe_error_v4l2_ctrl_handler_मुक्त:
	v4l2_ctrl_handler_मुक्त(hi556->sd.ctrl_handler);
	mutex_destroy(&hi556->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hi556_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(hi556_suspend, hi556_resume)
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id hi556_acpi_ids[] = अणु
	अणु"INT3537"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, hi556_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver hi556_i2c_driver = अणु
	.driver = अणु
		.name = "hi556",
		.pm = &hi556_pm_ops,
		.acpi_match_table = ACPI_PTR(hi556_acpi_ids),
	पूर्ण,
	.probe_new = hi556_probe,
	.हटाओ = hi556_हटाओ,
पूर्ण;

module_i2c_driver(hi556_i2c_driver);

MODULE_AUTHOR("Shawn Tu <shawnx.tu@intel.com>");
MODULE_DESCRIPTION("Hynix HI556 sensor driver");
MODULE_LICENSE("GPL v2");
