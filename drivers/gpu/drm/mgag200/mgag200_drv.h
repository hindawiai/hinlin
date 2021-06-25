<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2010 Matt Turner.
 * Copyright 2012 Red Hat
 *
 * Authors: Matthew Garrett
 * 	    Matt Turner
 *	    Dave Airlie
 */
#अगर_अघोषित __MGAG200_DRV_H__
#घोषणा __MGAG200_DRV_H__

#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/i2c.h>

#समावेश <video/vga.h>

#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "mgag200_reg.h"

#घोषणा DRIVER_AUTHOR		"Matthew Garrett"

#घोषणा DRIVER_NAME		"mgag200"
#घोषणा DRIVER_DESC		"MGA G200 SE"
#घोषणा DRIVER_DATE		"20110418"

#घोषणा DRIVER_MAJOR		1
#घोषणा DRIVER_MINOR		0
#घोषणा DRIVER_PATCHLEVEL	0

#घोषणा RREG8(reg) ioपढ़ो8(((व्योम __iomem *)mdev->rmmio) + (reg))
#घोषणा WREG8(reg, v) ioग_लिखो8(v, ((व्योम __iomem *)mdev->rmmio) + (reg))
#घोषणा RREG32(reg) ioपढ़ो32(((व्योम __iomem *)mdev->rmmio) + (reg))
#घोषणा WREG32(reg, v) ioग_लिखो32(v, ((व्योम __iomem *)mdev->rmmio) + (reg))

#घोषणा MGA_BIOS_OFFSET		0x7ffc

#घोषणा ATTR_INDEX 0x1fc0
#घोषणा ATTR_DATA 0x1fc1

#घोषणा WREG_ATTR(reg, v)					\
	करो अणु							\
		RREG8(0x1fda);					\
		WREG8(ATTR_INDEX, reg);				\
		WREG8(ATTR_DATA, v);				\
	पूर्ण जबतक (0)						\

#घोषणा RREG_SEQ(reg, v)					\
	करो अणु							\
		WREG8(MGAREG_SEQ_INDEX, reg);			\
		v = RREG8(MGAREG_SEQ_DATA);			\
	पूर्ण जबतक (0)						\

#घोषणा WREG_SEQ(reg, v)					\
	करो अणु							\
		WREG8(MGAREG_SEQ_INDEX, reg);			\
		WREG8(MGAREG_SEQ_DATA, v);			\
	पूर्ण जबतक (0)						\

#घोषणा RREG_CRT(reg, v)					\
	करो अणु							\
		WREG8(MGAREG_CRTC_INDEX, reg);			\
		v = RREG8(MGAREG_CRTC_DATA);			\
	पूर्ण जबतक (0)						\

#घोषणा WREG_CRT(reg, v)					\
	करो अणु							\
		WREG8(MGAREG_CRTC_INDEX, reg);			\
		WREG8(MGAREG_CRTC_DATA, v);			\
	पूर्ण जबतक (0)						\

#घोषणा RREG_ECRT(reg, v)					\
	करो अणु							\
		WREG8(MGAREG_CRTCEXT_INDEX, reg);		\
		v = RREG8(MGAREG_CRTCEXT_DATA);			\
	पूर्ण जबतक (0)						\

#घोषणा WREG_ECRT(reg, v)					\
	करो अणु							\
		WREG8(MGAREG_CRTCEXT_INDEX, reg);				\
		WREG8(MGAREG_CRTCEXT_DATA, v);				\
	पूर्ण जबतक (0)						\

#घोषणा GFX_INDEX 0x1fce
#घोषणा GFX_DATA 0x1fcf

#घोषणा WREG_GFX(reg, v)					\
	करो अणु							\
		WREG8(GFX_INDEX, reg);				\
		WREG8(GFX_DATA, v);				\
	पूर्ण जबतक (0)						\

#घोषणा DAC_INDEX 0x3c00
#घोषणा DAC_DATA 0x3c0a

#घोषणा WREG_DAC(reg, v)					\
	करो अणु							\
		WREG8(DAC_INDEX, reg);				\
		WREG8(DAC_DATA, v);				\
	पूर्ण जबतक (0)						\

#घोषणा MGA_MISC_OUT 0x1fc2
#घोषणा MGA_MISC_IN 0x1fcc

#घोषणा MGAG200_MAX_FB_HEIGHT 4096
#घोषणा MGAG200_MAX_FB_WIDTH 4096

#घोषणा to_mga_connector(x) container_of(x, काष्ठा mga_connector, base)

काष्ठा mga_i2c_chan अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा drm_device *dev;
	काष्ठा i2c_algo_bit_data bit;
	पूर्णांक data, घड़ी;
पूर्ण;

काष्ठा mga_connector अणु
	काष्ठा drm_connector base;
	काष्ठा mga_i2c_chan *i2c;
पूर्ण;

काष्ठा mga_mc अणु
	resource_माप_प्रकार			vram_size;
	resource_माप_प्रकार			vram_base;
	resource_माप_प्रकार			vram_winकरोw;
पूर्ण;

क्रमागत mga_type अणु
	G200_PCI,
	G200_AGP,
	G200_SE_A,
	G200_SE_B,
	G200_WB,
	G200_EV,
	G200_EH,
	G200_EH3,
	G200_ER,
	G200_EW3,
पूर्ण;

/* HW करोes not handle 'startadd' field correct. */
#घोषणा MGAG200_FLAG_HW_BUG_NO_STARTADD	(1ul << 8)

#घोषणा MGAG200_TYPE_MASK	(0x000000ff)
#घोषणा MGAG200_FLAG_MASK	(0x00ffff00)

#घोषणा IS_G200_SE(mdev) (mdev->type == G200_SE_A || mdev->type == G200_SE_B)

काष्ठा mga_device अणु
	काष्ठा drm_device		base;
	अचिन्हित दीर्घ			flags;

	resource_माप_प्रकार			rmmio_base;
	resource_माप_प्रकार			rmmio_size;
	व्योम __iomem			*rmmio;

	काष्ठा mga_mc			mc;

	व्योम __iomem			*vram;
	माप_प्रकार				vram_fb_available;

	क्रमागत mga_type			type;

	पूर्णांक bpp_shअगरts[4];

	पूर्णांक fb_mtrr;

	जोड़ अणु
		काष्ठा अणु
			दीर्घ ref_clk;
			दीर्घ pclk_min;
			दीर्घ pclk_max;
		पूर्ण g200;
		काष्ठा अणु
			/* SE model number stored in reg 0x1e24 */
			u32 unique_rev_id;
		पूर्ण g200se;
	पूर्ण model;


	काष्ठा mga_connector connector;
	काष्ठा drm_simple_display_pipe display_pipe;
पूर्ण;

अटल अंतरभूत काष्ठा mga_device *to_mga_device(काष्ठा drm_device *dev)
अणु
	वापस container_of(dev, काष्ठा mga_device, base);
पूर्ण

अटल अंतरभूत क्रमागत mga_type
mgag200_type_from_driver_data(kernel_uदीर्घ_t driver_data)
अणु
	वापस (क्रमागत mga_type)(driver_data & MGAG200_TYPE_MASK);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
mgag200_flags_from_driver_data(kernel_uदीर्घ_t driver_data)
अणु
	वापस driver_data & MGAG200_FLAG_MASK;
पूर्ण

				/* mgag200_mode.c */
पूर्णांक mgag200_modeset_init(काष्ठा mga_device *mdev);

				/* mgag200_i2c.c */
काष्ठा mga_i2c_chan *mgag200_i2c_create(काष्ठा drm_device *dev);
व्योम mgag200_i2c_destroy(काष्ठा mga_i2c_chan *i2c);

				/* mgag200_mm.c */
पूर्णांक mgag200_mm_init(काष्ठा mga_device *mdev);

#पूर्ण_अगर				/* __MGAG200_DRV_H__ */
