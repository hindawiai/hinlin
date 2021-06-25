<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2010 Sascha Hauer <s.hauer@pengutronix.de>
 * Copyright (C) 2005-2009 Freescale Semiconductor, Inc.
 */
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/imx-ipu-v3.h>
#समावेश "ipu-prv.h"

काष्ठा ipu_di अणु
	व्योम __iomem *base;
	पूर्णांक id;
	u32 module;
	काष्ठा clk *clk_di;	/* display input घड़ी */
	काष्ठा clk *clk_ipu;	/* IPU bus घड़ी */
	काष्ठा clk *clk_di_pixel; /* resulting pixel घड़ी */
	bool inuse;
	काष्ठा ipu_soc *ipu;
पूर्ण;

अटल DEFINE_MUTEX(di_mutex);

काष्ठा di_sync_config अणु
	पूर्णांक run_count;
	पूर्णांक run_src;
	पूर्णांक offset_count;
	पूर्णांक offset_src;
	पूर्णांक repeat_count;
	पूर्णांक cnt_clr_src;
	पूर्णांक cnt_polarity_gen_en;
	पूर्णांक cnt_polarity_clr_src;
	पूर्णांक cnt_polarity_trigger_src;
	पूर्णांक cnt_up;
	पूर्णांक cnt_करोwn;
पूर्ण;

क्रमागत di_pins अणु
	DI_PIN11 = 0,
	DI_PIN12 = 1,
	DI_PIN13 = 2,
	DI_PIN14 = 3,
	DI_PIN15 = 4,
	DI_PIN16 = 5,
	DI_PIN17 = 6,
	DI_PIN_CS = 7,

	DI_PIN_SER_CLK = 0,
	DI_PIN_SER_RS = 1,
पूर्ण;

क्रमागत di_sync_wave अणु
	DI_SYNC_NONE = 0,
	DI_SYNC_CLK = 1,
	DI_SYNC_INT_HSYNC = 2,
	DI_SYNC_HSYNC = 3,
	DI_SYNC_VSYNC = 4,
	DI_SYNC_DE = 6,

	DI_SYNC_CNT1 = 2,	/* counter >= 2 only */
	DI_SYNC_CNT4 = 5,	/* counter >= 5 only */
	DI_SYNC_CNT5 = 6,	/* counter >= 6 only */
पूर्ण;

#घोषणा SYNC_WAVE 0

#घोषणा DI_GENERAL		0x0000
#घोषणा DI_BS_CLKGEN0		0x0004
#घोषणा DI_BS_CLKGEN1		0x0008
#घोषणा DI_SW_GEN0(gen)		(0x000c + 4 * ((gen) - 1))
#घोषणा DI_SW_GEN1(gen)		(0x0030 + 4 * ((gen) - 1))
#घोषणा DI_STP_REP(gen)		(0x0148 + 4 * (((gen) - 1)/2))
#घोषणा DI_SYNC_AS_GEN		0x0054
#घोषणा DI_DW_GEN(gen)		(0x0058 + 4 * (gen))
#घोषणा DI_DW_SET(gen, set)	(0x0088 + 4 * ((gen) + 0xc * (set)))
#घोषणा DI_SER_CONF		0x015c
#घोषणा DI_SSC			0x0160
#घोषणा DI_POL			0x0164
#घोषणा DI_AW0			0x0168
#घोषणा DI_AW1			0x016c
#घोषणा DI_SCR_CONF		0x0170
#घोषणा DI_STAT			0x0174

#घोषणा DI_SW_GEN0_RUN_COUNT(x)			((x) << 19)
#घोषणा DI_SW_GEN0_RUN_SRC(x)			((x) << 16)
#घोषणा DI_SW_GEN0_OFFSET_COUNT(x)		((x) << 3)
#घोषणा DI_SW_GEN0_OFFSET_SRC(x)		((x) << 0)

#घोषणा DI_SW_GEN1_CNT_POL_GEN_EN(x)		((x) << 29)
#घोषणा DI_SW_GEN1_CNT_CLR_SRC(x)		((x) << 25)
#घोषणा DI_SW_GEN1_CNT_POL_TRIGGER_SRC(x)	((x) << 12)
#घोषणा DI_SW_GEN1_CNT_POL_CLR_SRC(x)		((x) << 9)
#घोषणा DI_SW_GEN1_CNT_DOWN(x)			((x) << 16)
#घोषणा DI_SW_GEN1_CNT_UP(x)			(x)
#घोषणा DI_SW_GEN1_AUTO_RELOAD			(0x10000000)

#घोषणा DI_DW_GEN_ACCESS_SIZE_OFFSET		24
#घोषणा DI_DW_GEN_COMPONENT_SIZE_OFFSET		16

#घोषणा DI_GEN_POLARITY_1			(1 << 0)
#घोषणा DI_GEN_POLARITY_2			(1 << 1)
#घोषणा DI_GEN_POLARITY_3			(1 << 2)
#घोषणा DI_GEN_POLARITY_4			(1 << 3)
#घोषणा DI_GEN_POLARITY_5			(1 << 4)
#घोषणा DI_GEN_POLARITY_6			(1 << 5)
#घोषणा DI_GEN_POLARITY_7			(1 << 6)
#घोषणा DI_GEN_POLARITY_8			(1 << 7)
#घोषणा DI_GEN_POLARITY_DISP_CLK		(1 << 17)
#घोषणा DI_GEN_DI_CLK_EXT			(1 << 20)
#घोषणा DI_GEN_DI_VSYNC_EXT			(1 << 21)

#घोषणा DI_POL_DRDY_DATA_POLARITY		(1 << 7)
#घोषणा DI_POL_DRDY_POLARITY_15			(1 << 4)

#घोषणा DI_VSYNC_SEL_OFFSET			13

अटल अंतरभूत u32 ipu_di_पढ़ो(काष्ठा ipu_di *di, अचिन्हित offset)
अणु
	वापस पढ़ोl(di->base + offset);
पूर्ण

अटल अंतरभूत व्योम ipu_di_ग_लिखो(काष्ठा ipu_di *di, u32 value, अचिन्हित offset)
अणु
	ग_लिखोl(value, di->base + offset);
पूर्ण

अटल व्योम ipu_di_data_wave_config(काष्ठा ipu_di *di,
				     पूर्णांक wave_gen,
				     पूर्णांक access_size, पूर्णांक component_size)
अणु
	u32 reg;
	reg = (access_size << DI_DW_GEN_ACCESS_SIZE_OFFSET) |
	    (component_size << DI_DW_GEN_COMPONENT_SIZE_OFFSET);
	ipu_di_ग_लिखो(di, reg, DI_DW_GEN(wave_gen));
पूर्ण

अटल व्योम ipu_di_data_pin_config(काष्ठा ipu_di *di, पूर्णांक wave_gen, पूर्णांक di_pin,
		पूर्णांक set, पूर्णांक up, पूर्णांक करोwn)
अणु
	u32 reg;

	reg = ipu_di_पढ़ो(di, DI_DW_GEN(wave_gen));
	reg &= ~(0x3 << (di_pin * 2));
	reg |= set << (di_pin * 2);
	ipu_di_ग_लिखो(di, reg, DI_DW_GEN(wave_gen));

	ipu_di_ग_लिखो(di, (करोwn << 16) | up, DI_DW_SET(wave_gen, set));
पूर्ण

अटल व्योम ipu_di_sync_config(काष्ठा ipu_di *di, काष्ठा di_sync_config *config,
		पूर्णांक start, पूर्णांक count)
अणु
	u32 reg;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा di_sync_config *c = &config[i];
		पूर्णांक wave_gen = start + i + 1;

		अगर ((c->run_count >= 0x1000) || (c->offset_count >= 0x1000) ||
				(c->repeat_count >= 0x1000) ||
				(c->cnt_up >= 0x400) ||
				(c->cnt_करोwn >= 0x400)) अणु
			dev_err(di->ipu->dev, "DI%d counters out of range.\n",
					di->id);
			वापस;
		पूर्ण

		reg = DI_SW_GEN0_RUN_COUNT(c->run_count) |
			DI_SW_GEN0_RUN_SRC(c->run_src) |
			DI_SW_GEN0_OFFSET_COUNT(c->offset_count) |
			DI_SW_GEN0_OFFSET_SRC(c->offset_src);
		ipu_di_ग_लिखो(di, reg, DI_SW_GEN0(wave_gen));

		reg = DI_SW_GEN1_CNT_POL_GEN_EN(c->cnt_polarity_gen_en) |
			DI_SW_GEN1_CNT_CLR_SRC(c->cnt_clr_src) |
			DI_SW_GEN1_CNT_POL_TRIGGER_SRC(
					c->cnt_polarity_trigger_src) |
			DI_SW_GEN1_CNT_POL_CLR_SRC(c->cnt_polarity_clr_src) |
			DI_SW_GEN1_CNT_DOWN(c->cnt_करोwn) |
			DI_SW_GEN1_CNT_UP(c->cnt_up);

		/* Enable स्वतः reload */
		अगर (c->repeat_count == 0)
			reg |= DI_SW_GEN1_AUTO_RELOAD;

		ipu_di_ग_लिखो(di, reg, DI_SW_GEN1(wave_gen));

		reg = ipu_di_पढ़ो(di, DI_STP_REP(wave_gen));
		reg &= ~(0xffff << (16 * ((wave_gen - 1) & 0x1)));
		reg |= c->repeat_count << (16 * ((wave_gen - 1) & 0x1));
		ipu_di_ग_लिखो(di, reg, DI_STP_REP(wave_gen));
	पूर्ण
पूर्ण

अटल व्योम ipu_di_sync_config_पूर्णांकerlaced(काष्ठा ipu_di *di,
		काष्ठा ipu_di_संकेत_cfg *sig)
अणु
	u32 h_total = sig->mode.hactive + sig->mode.hsync_len +
		sig->mode.hback_porch + sig->mode.hfront_porch;
	u32 v_total = sig->mode.vactive + sig->mode.vsync_len +
		sig->mode.vback_porch + sig->mode.vfront_porch;
	काष्ठा di_sync_config cfg[] = अणु
		अणु
			/* 1: पूर्णांकernal VSYNC क्रम each frame */
			.run_count = v_total * 2 - 1,
			.run_src = 3,			/* == counter 7 */
		पूर्ण, अणु
			/* PIN2: HSYNC waveक्रमm */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_CLK,
			.cnt_करोwn = sig->mode.hsync_len * 2,
		पूर्ण, अणु
			/* PIN3: VSYNC waveक्रमm */
			.run_count = v_total - 1,
			.run_src = 4,			/* == counter 7 */
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = 4,	/* == counter 7 */
			.cnt_करोwn = sig->mode.vsync_len * 2,
			.cnt_clr_src = DI_SYNC_CNT1,
		पूर्ण, अणु
			/* 4: Field */
			.run_count = v_total / 2,
			.run_src = DI_SYNC_HSYNC,
			.offset_count = h_total / 2,
			.offset_src = DI_SYNC_CLK,
			.repeat_count = 2,
			.cnt_clr_src = DI_SYNC_CNT1,
		पूर्ण, अणु
			/* 5: Active lines */
			.run_src = DI_SYNC_HSYNC,
			.offset_count = (sig->mode.vsync_len +
					 sig->mode.vback_porch) / 2,
			.offset_src = DI_SYNC_HSYNC,
			.repeat_count = sig->mode.vactive / 2,
			.cnt_clr_src = DI_SYNC_CNT4,
		पूर्ण, अणु
			/* 6: Active pixel, referenced by DC */
			.run_src = DI_SYNC_CLK,
			.offset_count = sig->mode.hsync_len +
					sig->mode.hback_porch,
			.offset_src = DI_SYNC_CLK,
			.repeat_count = sig->mode.hactive,
			.cnt_clr_src = DI_SYNC_CNT5,
		पूर्ण, अणु
			/* 7: Half line HSYNC */
			.run_count = h_total / 2 - 1,
			.run_src = DI_SYNC_CLK,
		पूर्ण
	पूर्ण;

	ipu_di_sync_config(di, cfg, 0, ARRAY_SIZE(cfg));

	ipu_di_ग_लिखो(di, v_total / 2 - 1, DI_SCR_CONF);
पूर्ण

अटल व्योम ipu_di_sync_config_nonपूर्णांकerlaced(काष्ठा ipu_di *di,
		काष्ठा ipu_di_संकेत_cfg *sig, पूर्णांक भाग)
अणु
	u32 h_total = sig->mode.hactive + sig->mode.hsync_len +
		sig->mode.hback_porch + sig->mode.hfront_porch;
	u32 v_total = sig->mode.vactive + sig->mode.vsync_len +
		sig->mode.vback_porch + sig->mode.vfront_porch;
	काष्ठा di_sync_config cfg[] = अणु
		अणु
			/* 1: INT_HSYNC */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
		पूर्ण , अणु
			/* PIN2: HSYNC */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
			.offset_count = भाग * sig->v_to_h_sync,
			.offset_src = DI_SYNC_CLK,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_CLK,
			.cnt_करोwn = sig->mode.hsync_len * 2,
		पूर्ण , अणु
			/* PIN3: VSYNC */
			.run_count = v_total - 1,
			.run_src = DI_SYNC_INT_HSYNC,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_INT_HSYNC,
			.cnt_करोwn = sig->mode.vsync_len * 2,
		पूर्ण , अणु
			/* 4: Line Active */
			.run_src = DI_SYNC_HSYNC,
			.offset_count = sig->mode.vsync_len +
					sig->mode.vback_porch,
			.offset_src = DI_SYNC_HSYNC,
			.repeat_count = sig->mode.vactive,
			.cnt_clr_src = DI_SYNC_VSYNC,
		पूर्ण , अणु
			/* 5: Pixel Active, referenced by DC */
			.run_src = DI_SYNC_CLK,
			.offset_count = sig->mode.hsync_len +
					sig->mode.hback_porch,
			.offset_src = DI_SYNC_CLK,
			.repeat_count = sig->mode.hactive,
			.cnt_clr_src = 5, /* Line Active */
		पूर्ण , अणु
			/* unused */
		पूर्ण , अणु
			/* unused */
		पूर्ण,
	पूर्ण;
	/* can't use #7 and #8 क्रम line active and pixel active counters */
	काष्ठा di_sync_config cfg_vga[] = अणु
		अणु
			/* 1: INT_HSYNC */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
		पूर्ण , अणु
			/* 2: VSYNC */
			.run_count = v_total - 1,
			.run_src = DI_SYNC_INT_HSYNC,
		पूर्ण , अणु
			/* 3: Line Active */
			.run_src = DI_SYNC_INT_HSYNC,
			.offset_count = sig->mode.vsync_len +
					sig->mode.vback_porch,
			.offset_src = DI_SYNC_INT_HSYNC,
			.repeat_count = sig->mode.vactive,
			.cnt_clr_src = 3 /* VSYNC */,
		पूर्ण , अणु
			/* PIN4: HSYNC क्रम VGA via TVEv2 on TQ MBa53 */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
			.offset_count = भाग * sig->v_to_h_sync + 18, /* magic value from Freescale TVE driver */
			.offset_src = DI_SYNC_CLK,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_CLK,
			.cnt_करोwn = sig->mode.hsync_len * 2,
		पूर्ण , अणु
			/* 5: Pixel Active संकेत to DC */
			.run_src = DI_SYNC_CLK,
			.offset_count = sig->mode.hsync_len +
					sig->mode.hback_porch,
			.offset_src = DI_SYNC_CLK,
			.repeat_count = sig->mode.hactive,
			.cnt_clr_src = 4, /* Line Active */
		पूर्ण , अणु
			/* PIN6: VSYNC क्रम VGA via TVEv2 on TQ MBa53 */
			.run_count = v_total - 1,
			.run_src = DI_SYNC_INT_HSYNC,
			.offset_count = 1, /* magic value from Freescale TVE driver */
			.offset_src = DI_SYNC_INT_HSYNC,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_INT_HSYNC,
			.cnt_करोwn = sig->mode.vsync_len * 2,
		पूर्ण , अणु
			/* PIN4: HSYNC क्रम VGA via TVEv2 on i.MX53-QSB */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
			.offset_count = भाग * sig->v_to_h_sync + 18, /* magic value from Freescale TVE driver */
			.offset_src = DI_SYNC_CLK,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_CLK,
			.cnt_करोwn = sig->mode.hsync_len * 2,
		पूर्ण , अणु
			/* PIN6: VSYNC क्रम VGA via TVEv2 on i.MX53-QSB */
			.run_count = v_total - 1,
			.run_src = DI_SYNC_INT_HSYNC,
			.offset_count = 1, /* magic value from Freescale TVE driver */
			.offset_src = DI_SYNC_INT_HSYNC,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_INT_HSYNC,
			.cnt_करोwn = sig->mode.vsync_len * 2,
		पूर्ण , अणु
			/* unused */
		पूर्ण,
	पूर्ण;

	ipu_di_ग_लिखो(di, v_total - 1, DI_SCR_CONF);
	अगर (sig->hsync_pin == 2 && sig->vsync_pin == 3)
		ipu_di_sync_config(di, cfg, 0, ARRAY_SIZE(cfg));
	अन्यथा
		ipu_di_sync_config(di, cfg_vga, 0, ARRAY_SIZE(cfg_vga));
पूर्ण

अटल व्योम ipu_di_config_घड़ी(काष्ठा ipu_di *di,
	स्थिर काष्ठा ipu_di_संकेत_cfg *sig)
अणु
	काष्ठा clk *clk;
	अचिन्हित clkgen0;
	uपूर्णांक32_t val;

	अगर (sig->clkflags & IPU_DI_CLKMODE_EXT) अणु
		/*
		 * CLKMODE_EXT means we must use the DI घड़ी: this is
		 * needed क्रम things like LVDS which needs to feed the
		 * DI and LDB with the same pixel घड़ी.
		 */
		clk = di->clk_di;

		अगर (sig->clkflags & IPU_DI_CLKMODE_SYNC) अणु
			/*
			 * CLKMODE_SYNC means that we want the DI to be
			 * घड़ीed at the same rate as the parent घड़ी.
			 * This is needed (eg) क्रम LDB which needs to be
			 * fed with the same pixel घड़ी.  We assume that
			 * the LDB घड़ी has alपढ़ोy been set correctly.
			 */
			clkgen0 = 1 << 4;
		पूर्ण अन्यथा अणु
			/*
			 * We can use the भागider.  We should really have
			 * a flag here indicating whether the bridge can
			 * cope with a fractional भागider or not.  For the
			 * समय being, let's go क्रम simplicitly and
			 * reliability.
			 */
			अचिन्हित दीर्घ in_rate;
			अचिन्हित भाग;

			clk_set_rate(clk, sig->mode.pixelघड़ी);

			in_rate = clk_get_rate(clk);
			भाग = DIV_ROUND_CLOSEST(in_rate, sig->mode.pixelघड़ी);
			भाग = clamp(भाग, 1U, 255U);

			clkgen0 = भाग << 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * For other पूर्णांकerfaces, we can arbitarily select between
		 * the DI specअगरic घड़ी and the पूर्णांकernal IPU घड़ी.  See
		 * DI_GENERAL bit 20.  We select the IPU घड़ी अगर it can
		 * give us a घड़ी rate within 1% of the requested frequency,
		 * otherwise we use the DI घड़ी.
		 */
		अचिन्हित दीर्घ rate, clkrate;
		अचिन्हित भाग, error;

		clkrate = clk_get_rate(di->clk_ipu);
		भाग = DIV_ROUND_CLOSEST(clkrate, sig->mode.pixelघड़ी);
		भाग = clamp(भाग, 1U, 255U);
		rate = clkrate / भाग;

		error = rate / (sig->mode.pixelघड़ी / 1000);

		dev_dbg(di->ipu->dev, "  IPU clock can give %lu with divider %u, error %d.%u%%\n",
			rate, भाग, (चिन्हित)(error - 1000) / 10, error % 10);

		/* Allow a 1% error */
		अगर (error < 1010 && error >= 990) अणु
			clk = di->clk_ipu;

			clkgen0 = भाग << 4;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ in_rate;
			अचिन्हित भाग;

			clk = di->clk_di;

			clk_set_rate(clk, sig->mode.pixelघड़ी);

			in_rate = clk_get_rate(clk);
			भाग = DIV_ROUND_CLOSEST(in_rate, sig->mode.pixelघड़ी);
			भाग = clamp(भाग, 1U, 255U);

			clkgen0 = भाग << 4;
		पूर्ण
	पूर्ण

	di->clk_di_pixel = clk;

	/* Set the भागider */
	ipu_di_ग_लिखो(di, clkgen0, DI_BS_CLKGEN0);

	/*
	 * Set the high/low periods.  Bits 24:16 give us the falling edge,
	 * and bits 8:0 give the rising edge.  LSB is fraction, and is
	 * based on the भागider above.  We want a 50% duty cycle, so set
	 * the falling edge to be half the भागider.
	 */
	ipu_di_ग_लिखो(di, (clkgen0 >> 4) << 16, DI_BS_CLKGEN1);

	/* Finally select the input घड़ी */
	val = ipu_di_पढ़ो(di, DI_GENERAL) & ~DI_GEN_DI_CLK_EXT;
	अगर (clk == di->clk_di)
		val |= DI_GEN_DI_CLK_EXT;
	ipu_di_ग_लिखो(di, val, DI_GENERAL);

	dev_dbg(di->ipu->dev, "Want %luHz IPU %luHz DI %luHz using %s, %luHz\n",
		sig->mode.pixelघड़ी,
		clk_get_rate(di->clk_ipu),
		clk_get_rate(di->clk_di),
		clk == di->clk_di ? "DI" : "IPU",
		clk_get_rate(di->clk_di_pixel) / (clkgen0 >> 4));
पूर्ण

/*
 * This function is called to adjust a video mode to IPU restrictions.
 * It is meant to be called from drm crtc mode_fixup() methods.
 */
पूर्णांक ipu_di_adjust_videomode(काष्ठा ipu_di *di, काष्ठा videomode *mode)
अणु
	u32 dअगरf;

	अगर (mode->vfront_porch >= 2)
		वापस 0;

	dअगरf = 2 - mode->vfront_porch;

	अगर (mode->vback_porch >= dअगरf) अणु
		mode->vfront_porch = 2;
		mode->vback_porch -= dअगरf;
	पूर्ण अन्यथा अगर (mode->vsync_len > dअगरf) अणु
		mode->vfront_porch = 2;
		mode->vsync_len = mode->vsync_len - dअगरf;
	पूर्ण अन्यथा अणु
		dev_warn(di->ipu->dev, "failed to adjust videomode\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(di->ipu->dev, "videomode adapted for IPU restrictions\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_di_adjust_videomode);

अटल u32 ipu_di_gen_polarity(पूर्णांक pin)
अणु
	चयन (pin) अणु
	हाल 1:
		वापस DI_GEN_POLARITY_1;
	हाल 2:
		वापस DI_GEN_POLARITY_2;
	हाल 3:
		वापस DI_GEN_POLARITY_3;
	हाल 4:
		वापस DI_GEN_POLARITY_4;
	हाल 5:
		वापस DI_GEN_POLARITY_5;
	हाल 6:
		वापस DI_GEN_POLARITY_6;
	हाल 7:
		वापस DI_GEN_POLARITY_7;
	हाल 8:
		वापस DI_GEN_POLARITY_8;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ipu_di_init_sync_panel(काष्ठा ipu_di *di, काष्ठा ipu_di_संकेत_cfg *sig)
अणु
	u32 reg;
	u32 di_gen, vsync_cnt;
	u32 भाग;

	dev_dbg(di->ipu->dev, "disp %d: panel size = %d x %d\n",
		di->id, sig->mode.hactive, sig->mode.vactive);

	dev_dbg(di->ipu->dev, "Clocks: IPU %luHz DI %luHz Needed %luHz\n",
		clk_get_rate(di->clk_ipu),
		clk_get_rate(di->clk_di),
		sig->mode.pixelघड़ी);

	mutex_lock(&di_mutex);

	ipu_di_config_घड़ी(di, sig);

	भाग = ipu_di_पढ़ो(di, DI_BS_CLKGEN0) & 0xfff;
	भाग = भाग / 16;		/* Now भागider is पूर्णांकeger portion */

	/* Setup pixel घड़ी timing */
	/* Down समय is half of period */
	ipu_di_ग_लिखो(di, (भाग << 16), DI_BS_CLKGEN1);

	ipu_di_data_wave_config(di, SYNC_WAVE, भाग - 1, भाग - 1);
	ipu_di_data_pin_config(di, SYNC_WAVE, DI_PIN15, 3, 0, भाग * 2);

	di_gen = ipu_di_पढ़ो(di, DI_GENERAL) & DI_GEN_DI_CLK_EXT;
	di_gen |= DI_GEN_DI_VSYNC_EXT;

	अगर (sig->mode.flags & DISPLAY_FLAGS_INTERLACED) अणु
		ipu_di_sync_config_पूर्णांकerlaced(di, sig);

		/* set y_sel = 1 */
		di_gen |= 0x10000000;

		vsync_cnt = 3;
	पूर्ण अन्यथा अणु
		ipu_di_sync_config_nonपूर्णांकerlaced(di, sig, भाग);

		vsync_cnt = 3;
		अगर (di->id == 1)
			/*
			 * TODO: change only क्रम TVEv2, parallel display
			 * uses pin 2 / 3
			 */
			अगर (!(sig->hsync_pin == 2 && sig->vsync_pin == 3))
				vsync_cnt = 6;
	पूर्ण

	अगर (sig->mode.flags & DISPLAY_FLAGS_HSYNC_HIGH)
		di_gen |= ipu_di_gen_polarity(sig->hsync_pin);
	अगर (sig->mode.flags & DISPLAY_FLAGS_VSYNC_HIGH)
		di_gen |= ipu_di_gen_polarity(sig->vsync_pin);

	अगर (sig->clk_pol)
		di_gen |= DI_GEN_POLARITY_DISP_CLK;

	ipu_di_ग_लिखो(di, di_gen, DI_GENERAL);

	ipu_di_ग_लिखो(di, (--vsync_cnt << DI_VSYNC_SEL_OFFSET) | 0x00000002,
		     DI_SYNC_AS_GEN);

	reg = ipu_di_पढ़ो(di, DI_POL);
	reg &= ~(DI_POL_DRDY_DATA_POLARITY | DI_POL_DRDY_POLARITY_15);

	अगर (sig->enable_pol)
		reg |= DI_POL_DRDY_POLARITY_15;
	अगर (sig->data_pol)
		reg |= DI_POL_DRDY_DATA_POLARITY;

	ipu_di_ग_लिखो(di, reg, DI_POL);

	mutex_unlock(&di_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_di_init_sync_panel);

पूर्णांक ipu_di_enable(काष्ठा ipu_di *di)
अणु
	पूर्णांक ret;

	WARN_ON(IS_ERR(di->clk_di_pixel));

	ret = clk_prepare_enable(di->clk_di_pixel);
	अगर (ret)
		वापस ret;

	ipu_module_enable(di->ipu, di->module);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_di_enable);

पूर्णांक ipu_di_disable(काष्ठा ipu_di *di)
अणु
	WARN_ON(IS_ERR(di->clk_di_pixel));

	ipu_module_disable(di->ipu, di->module);

	clk_disable_unprepare(di->clk_di_pixel);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_di_disable);

पूर्णांक ipu_di_get_num(काष्ठा ipu_di *di)
अणु
	वापस di->id;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_di_get_num);

अटल DEFINE_MUTEX(ipu_di_lock);

काष्ठा ipu_di *ipu_di_get(काष्ठा ipu_soc *ipu, पूर्णांक disp)
अणु
	काष्ठा ipu_di *di;

	अगर (disp > 1)
		वापस ERR_PTR(-EINVAL);

	di = ipu->di_priv[disp];

	mutex_lock(&ipu_di_lock);

	अगर (di->inuse) अणु
		di = ERR_PTR(-EBUSY);
		जाओ out;
	पूर्ण

	di->inuse = true;
out:
	mutex_unlock(&ipu_di_lock);

	वापस di;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_di_get);

व्योम ipu_di_put(काष्ठा ipu_di *di)
अणु
	mutex_lock(&ipu_di_lock);

	di->inuse = false;

	mutex_unlock(&ipu_di_lock);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_di_put);

पूर्णांक ipu_di_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev, पूर्णांक id,
		अचिन्हित दीर्घ base,
		u32 module, काष्ठा clk *clk_ipu)
अणु
	काष्ठा ipu_di *di;

	अगर (id > 1)
		वापस -ENODEV;

	di = devm_kzalloc(dev, माप(*di), GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	ipu->di_priv[id] = di;

	di->clk_di = devm_clk_get(dev, id ? "di1" : "di0");
	अगर (IS_ERR(di->clk_di))
		वापस PTR_ERR(di->clk_di);

	di->module = module;
	di->id = id;
	di->clk_ipu = clk_ipu;
	di->base = devm_ioremap(dev, base, PAGE_SIZE);
	अगर (!di->base)
		वापस -ENOMEM;

	ipu_di_ग_लिखो(di, 0x10, DI_BS_CLKGEN0);

	dev_dbg(dev, "DI%d base: 0x%08lx remapped to %p\n",
			id, base, di->base);
	di->inuse = false;
	di->ipu = ipu;

	वापस 0;
पूर्ण

व्योम ipu_di_निकास(काष्ठा ipu_soc *ipu, पूर्णांक id)
अणु
पूर्ण
