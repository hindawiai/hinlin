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
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश <video/imx-ipu-v3.h>
#समावेश "ipu-prv.h"

#घोषणा DC_MAP_CONF_PTR(n)	(0x108 + ((n) & ~0x1) * 2)
#घोषणा DC_MAP_CONF_VAL(n)	(0x144 + ((n) & ~0x1) * 2)

#घोषणा DC_EVT_NF		0
#घोषणा DC_EVT_NL		1
#घोषणा DC_EVT_खातापूर्ण		2
#घोषणा DC_EVT_NFIELD		3
#घोषणा DC_EVT_EOL		4
#घोषणा DC_EVT_खातापूर्णIELD		5
#घोषणा DC_EVT_NEW_ADDR		6
#घोषणा DC_EVT_NEW_CHAN		7
#घोषणा DC_EVT_NEW_DATA		8

#घोषणा DC_EVT_NEW_ADDR_W_0	0
#घोषणा DC_EVT_NEW_ADDR_W_1	1
#घोषणा DC_EVT_NEW_CHAN_W_0	2
#घोषणा DC_EVT_NEW_CHAN_W_1	3
#घोषणा DC_EVT_NEW_DATA_W_0	4
#घोषणा DC_EVT_NEW_DATA_W_1	5
#घोषणा DC_EVT_NEW_ADDR_R_0	6
#घोषणा DC_EVT_NEW_ADDR_R_1	7
#घोषणा DC_EVT_NEW_CHAN_R_0	8
#घोषणा DC_EVT_NEW_CHAN_R_1	9
#घोषणा DC_EVT_NEW_DATA_R_0	10
#घोषणा DC_EVT_NEW_DATA_R_1	11

#घोषणा DC_WR_CH_CONF		0x0
#घोषणा DC_WR_CH_ADDR		0x4
#घोषणा DC_RL_CH(evt)		(8 + ((evt) & ~0x1) * 2)

#घोषणा DC_GEN			0xd4
#घोषणा DC_DISP_CONF1(disp)	(0xd8 + (disp) * 4)
#घोषणा DC_DISP_CONF2(disp)	(0xe8 + (disp) * 4)
#घोषणा DC_STAT			0x1c8

#घोषणा WROD(lf)		(0x18 | ((lf) << 1))
#घोषणा WRG			0x01
#घोषणा WCLK			0xc9

#घोषणा SYNC_WAVE 0
#घोषणा शून्य_WAVE (-1)

#घोषणा DC_GEN_SYNC_1_6_SYNC	(2 << 1)
#घोषणा DC_GEN_SYNC_PRIORITY_1	(1 << 7)

#घोषणा DC_WR_CH_CONF_WORD_SIZE_8		(0 << 0)
#घोषणा DC_WR_CH_CONF_WORD_SIZE_16		(1 << 0)
#घोषणा DC_WR_CH_CONF_WORD_SIZE_24		(2 << 0)
#घोषणा DC_WR_CH_CONF_WORD_SIZE_32		(3 << 0)
#घोषणा DC_WR_CH_CONF_DISP_ID_PARALLEL(i)	(((i) & 0x1) << 3)
#घोषणा DC_WR_CH_CONF_DISP_ID_SERIAL		(2 << 3)
#घोषणा DC_WR_CH_CONF_DISP_ID_ASYNC		(3 << 4)
#घोषणा DC_WR_CH_CONF_FIELD_MODE		(1 << 9)
#घोषणा DC_WR_CH_CONF_PROG_TYPE_NORMAL		(4 << 5)
#घोषणा DC_WR_CH_CONF_PROG_TYPE_MASK		(7 << 5)
#घोषणा DC_WR_CH_CONF_PROG_DI_ID		(1 << 2)
#घोषणा DC_WR_CH_CONF_PROG_DISP_ID(i)		(((i) & 0x1) << 3)

#घोषणा IPU_DC_NUM_CHANNELS	10

काष्ठा ipu_dc_priv;

क्रमागत ipu_dc_map अणु
	IPU_DC_MAP_RGB24,
	IPU_DC_MAP_RGB565,
	IPU_DC_MAP_GBR24, /* TVEv2 */
	IPU_DC_MAP_BGR666,
	IPU_DC_MAP_LVDS666,
	IPU_DC_MAP_BGR24,
पूर्ण;

काष्ठा ipu_dc अणु
	/* The display पूर्णांकerface number asचिन्हित to this dc channel */
	अचिन्हित पूर्णांक		di;
	व्योम __iomem		*base;
	काष्ठा ipu_dc_priv	*priv;
	पूर्णांक			chno;
	bool			in_use;
पूर्ण;

काष्ठा ipu_dc_priv अणु
	व्योम __iomem		*dc_reg;
	व्योम __iomem		*dc_पंचांगpl_reg;
	काष्ठा ipu_soc		*ipu;
	काष्ठा device		*dev;
	काष्ठा ipu_dc		channels[IPU_DC_NUM_CHANNELS];
	काष्ठा mutex		mutex;
	काष्ठा completion	comp;
	पूर्णांक			use_count;
पूर्ण;

अटल व्योम dc_link_event(काष्ठा ipu_dc *dc, पूर्णांक event, पूर्णांक addr, पूर्णांक priority)
अणु
	u32 reg;

	reg = पढ़ोl(dc->base + DC_RL_CH(event));
	reg &= ~(0xffff << (16 * (event & 0x1)));
	reg |= ((addr << 8) | priority) << (16 * (event & 0x1));
	ग_लिखोl(reg, dc->base + DC_RL_CH(event));
पूर्ण

अटल व्योम dc_ग_लिखो_पंचांगpl(काष्ठा ipu_dc *dc, पूर्णांक word, u32 opcode, u32 opeअक्रम,
		पूर्णांक map, पूर्णांक wave, पूर्णांक glue, पूर्णांक sync, पूर्णांक stop)
अणु
	काष्ठा ipu_dc_priv *priv = dc->priv;
	u32 reg1, reg2;

	अगर (opcode == WCLK) अणु
		reg1 = (opeअक्रम << 20) & 0xfff00000;
		reg2 = opeअक्रम >> 12 | opcode << 1 | stop << 9;
	पूर्ण अन्यथा अगर (opcode == WRG) अणु
		reg1 = sync | glue << 4 | ++wave << 11 | ((opeअक्रम << 15) & 0xffff8000);
		reg2 = opeअक्रम >> 17 | opcode << 7 | stop << 9;
	पूर्ण अन्यथा अणु
		reg1 = sync | glue << 4 | ++wave << 11 | ++map << 15 | ((opeअक्रम << 20) & 0xfff00000);
		reg2 = opeअक्रम >> 12 | opcode << 4 | stop << 9;
	पूर्ण
	ग_लिखोl(reg1, priv->dc_पंचांगpl_reg + word * 8);
	ग_लिखोl(reg2, priv->dc_पंचांगpl_reg + word * 8 + 4);
पूर्ण

अटल पूर्णांक ipu_bus_क्रमmat_to_map(u32 fmt)
अणु
	चयन (fmt) अणु
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		वापस IPU_DC_MAP_RGB24;
	हाल MEDIA_BUS_FMT_RGB565_1X16:
		वापस IPU_DC_MAP_RGB565;
	हाल MEDIA_BUS_FMT_GBR888_1X24:
		वापस IPU_DC_MAP_GBR24;
	हाल MEDIA_BUS_FMT_RGB666_1X18:
		वापस IPU_DC_MAP_BGR666;
	हाल MEDIA_BUS_FMT_RGB666_1X24_CPADHI:
		वापस IPU_DC_MAP_LVDS666;
	हाल MEDIA_BUS_FMT_BGR888_1X24:
		वापस IPU_DC_MAP_BGR24;
	पूर्ण
पूर्ण

पूर्णांक ipu_dc_init_sync(काष्ठा ipu_dc *dc, काष्ठा ipu_di *di, bool पूर्णांकerlaced,
		u32 bus_क्रमmat, u32 width)
अणु
	काष्ठा ipu_dc_priv *priv = dc->priv;
	पूर्णांक addr, sync;
	u32 reg = 0;
	पूर्णांक map;

	dc->di = ipu_di_get_num(di);

	map = ipu_bus_क्रमmat_to_map(bus_क्रमmat);

	/*
	 * In पूर्णांकerlaced mode we need more counters to create the asymmetric
	 * per-field VSYNC संकेतs. The pixel active संकेत synchronising DC
	 * to DI moves to संकेत generator #6 (see ipu-di.c). In progressive
	 * mode counter #5 is used.
	 */
	sync = पूर्णांकerlaced ? 6 : 5;

	/* Reserve 5 microcode ढाँचा words क्रम each DI */
	अगर (dc->di)
		addr = 5;
	अन्यथा
		addr = 0;

	अगर (पूर्णांकerlaced) अणु
		dc_link_event(dc, DC_EVT_NL, addr, 3);
		dc_link_event(dc, DC_EVT_EOL, addr, 2);
		dc_link_event(dc, DC_EVT_NEW_DATA, addr, 1);

		/* Init ढाँचा microcode */
		dc_ग_लिखो_पंचांगpl(dc, addr, WROD(0), 0, map, SYNC_WAVE, 0, sync, 1);
	पूर्ण अन्यथा अणु
		dc_link_event(dc, DC_EVT_NL, addr + 2, 3);
		dc_link_event(dc, DC_EVT_EOL, addr + 3, 2);
		dc_link_event(dc, DC_EVT_NEW_DATA, addr + 1, 1);

		/* Init ढाँचा microcode */
		dc_ग_लिखो_पंचांगpl(dc, addr + 2, WROD(0), 0, map, SYNC_WAVE, 8, sync, 1);
		dc_ग_लिखो_पंचांगpl(dc, addr + 3, WROD(0), 0, map, SYNC_WAVE, 4, sync, 0);
		dc_ग_लिखो_पंचांगpl(dc, addr + 4, WRG, 0, map, शून्य_WAVE, 0, 0, 1);
		dc_ग_लिखो_पंचांगpl(dc, addr + 1, WROD(0), 0, map, SYNC_WAVE, 0, sync, 1);
	पूर्ण

	dc_link_event(dc, DC_EVT_NF, 0, 0);
	dc_link_event(dc, DC_EVT_NFIELD, 0, 0);
	dc_link_event(dc, DC_EVT_खातापूर्ण, 0, 0);
	dc_link_event(dc, DC_EVT_खातापूर्णIELD, 0, 0);
	dc_link_event(dc, DC_EVT_NEW_CHAN, 0, 0);
	dc_link_event(dc, DC_EVT_NEW_ADDR, 0, 0);

	reg = पढ़ोl(dc->base + DC_WR_CH_CONF);
	अगर (पूर्णांकerlaced)
		reg |= DC_WR_CH_CONF_FIELD_MODE;
	अन्यथा
		reg &= ~DC_WR_CH_CONF_FIELD_MODE;
	ग_लिखोl(reg, dc->base + DC_WR_CH_CONF);

	ग_लिखोl(0x0, dc->base + DC_WR_CH_ADDR);
	ग_लिखोl(width, priv->dc_reg + DC_DISP_CONF2(dc->di));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dc_init_sync);

व्योम ipu_dc_enable(काष्ठा ipu_soc *ipu)
अणु
	काष्ठा ipu_dc_priv *priv = ipu->dc_priv;

	mutex_lock(&priv->mutex);

	अगर (!priv->use_count)
		ipu_module_enable(priv->ipu, IPU_CONF_DC_EN);

	priv->use_count++;

	mutex_unlock(&priv->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dc_enable);

व्योम ipu_dc_enable_channel(काष्ठा ipu_dc *dc)
अणु
	u32 reg;

	reg = पढ़ोl(dc->base + DC_WR_CH_CONF);
	reg |= DC_WR_CH_CONF_PROG_TYPE_NORMAL;
	ग_लिखोl(reg, dc->base + DC_WR_CH_CONF);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dc_enable_channel);

व्योम ipu_dc_disable_channel(काष्ठा ipu_dc *dc)
अणु
	u32 val;

	val = पढ़ोl(dc->base + DC_WR_CH_CONF);
	val &= ~DC_WR_CH_CONF_PROG_TYPE_MASK;
	ग_लिखोl(val, dc->base + DC_WR_CH_CONF);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dc_disable_channel);

व्योम ipu_dc_disable(काष्ठा ipu_soc *ipu)
अणु
	काष्ठा ipu_dc_priv *priv = ipu->dc_priv;

	mutex_lock(&priv->mutex);

	priv->use_count--;
	अगर (!priv->use_count)
		ipu_module_disable(priv->ipu, IPU_CONF_DC_EN);

	अगर (priv->use_count < 0)
		priv->use_count = 0;

	mutex_unlock(&priv->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dc_disable);

अटल व्योम ipu_dc_map_config(काष्ठा ipu_dc_priv *priv, क्रमागत ipu_dc_map map,
		पूर्णांक byte_num, पूर्णांक offset, पूर्णांक mask)
अणु
	पूर्णांक ptr = map * 3 + byte_num;
	u32 reg;

	reg = पढ़ोl(priv->dc_reg + DC_MAP_CONF_VAL(ptr));
	reg &= ~(0xffff << (16 * (ptr & 0x1)));
	reg |= ((offset << 8) | mask) << (16 * (ptr & 0x1));
	ग_लिखोl(reg, priv->dc_reg + DC_MAP_CONF_VAL(ptr));

	reg = पढ़ोl(priv->dc_reg + DC_MAP_CONF_PTR(map));
	reg &= ~(0x1f << ((16 * (map & 0x1)) + (5 * byte_num)));
	reg |= ptr << ((16 * (map & 0x1)) + (5 * byte_num));
	ग_लिखोl(reg, priv->dc_reg + DC_MAP_CONF_PTR(map));
पूर्ण

अटल व्योम ipu_dc_map_clear(काष्ठा ipu_dc_priv *priv, पूर्णांक map)
अणु
	u32 reg = पढ़ोl(priv->dc_reg + DC_MAP_CONF_PTR(map));

	ग_लिखोl(reg & ~(0xffff << (16 * (map & 0x1))),
		     priv->dc_reg + DC_MAP_CONF_PTR(map));
पूर्ण

काष्ठा ipu_dc *ipu_dc_get(काष्ठा ipu_soc *ipu, पूर्णांक channel)
अणु
	काष्ठा ipu_dc_priv *priv = ipu->dc_priv;
	काष्ठा ipu_dc *dc;

	अगर (channel >= IPU_DC_NUM_CHANNELS)
		वापस ERR_PTR(-ENODEV);

	dc = &priv->channels[channel];

	mutex_lock(&priv->mutex);

	अगर (dc->in_use) अणु
		mutex_unlock(&priv->mutex);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	dc->in_use = true;

	mutex_unlock(&priv->mutex);

	वापस dc;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dc_get);

व्योम ipu_dc_put(काष्ठा ipu_dc *dc)
अणु
	काष्ठा ipu_dc_priv *priv = dc->priv;

	mutex_lock(&priv->mutex);
	dc->in_use = false;
	mutex_unlock(&priv->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dc_put);

पूर्णांक ipu_dc_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev,
		अचिन्हित दीर्घ base, अचिन्हित दीर्घ ढाँचा_base)
अणु
	काष्ठा ipu_dc_priv *priv;
	अटल पूर्णांक channel_offsets[] = अणु 0, 0x1c, 0x38, 0x54, 0x58, 0x5c,
		0x78, 0, 0x94, 0xb4पूर्ण;
	पूर्णांक i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->mutex);

	priv->dev = dev;
	priv->ipu = ipu;
	priv->dc_reg = devm_ioremap(dev, base, PAGE_SIZE);
	priv->dc_पंचांगpl_reg = devm_ioremap(dev, ढाँचा_base, PAGE_SIZE);
	अगर (!priv->dc_reg || !priv->dc_पंचांगpl_reg)
		वापस -ENOMEM;

	क्रम (i = 0; i < IPU_DC_NUM_CHANNELS; i++) अणु
		priv->channels[i].chno = i;
		priv->channels[i].priv = priv;
		priv->channels[i].base = priv->dc_reg + channel_offsets[i];
	पूर्ण

	ग_लिखोl(DC_WR_CH_CONF_WORD_SIZE_24 | DC_WR_CH_CONF_DISP_ID_PARALLEL(1) |
			DC_WR_CH_CONF_PROG_DI_ID,
			priv->channels[1].base + DC_WR_CH_CONF);
	ग_लिखोl(DC_WR_CH_CONF_WORD_SIZE_24 | DC_WR_CH_CONF_DISP_ID_PARALLEL(0),
			priv->channels[5].base + DC_WR_CH_CONF);

	ग_लिखोl(DC_GEN_SYNC_1_6_SYNC | DC_GEN_SYNC_PRIORITY_1,
		priv->dc_reg + DC_GEN);

	ipu->dc_priv = priv;

	dev_dbg(dev, "DC base: 0x%08lx template base: 0x%08lx\n",
			base, ढाँचा_base);

	/* rgb24 */
	ipu_dc_map_clear(priv, IPU_DC_MAP_RGB24);
	ipu_dc_map_config(priv, IPU_DC_MAP_RGB24, 0, 7, 0xff); /* blue */
	ipu_dc_map_config(priv, IPU_DC_MAP_RGB24, 1, 15, 0xff); /* green */
	ipu_dc_map_config(priv, IPU_DC_MAP_RGB24, 2, 23, 0xff); /* red */

	/* rgb565 */
	ipu_dc_map_clear(priv, IPU_DC_MAP_RGB565);
	ipu_dc_map_config(priv, IPU_DC_MAP_RGB565, 0, 4, 0xf8); /* blue */
	ipu_dc_map_config(priv, IPU_DC_MAP_RGB565, 1, 10, 0xfc); /* green */
	ipu_dc_map_config(priv, IPU_DC_MAP_RGB565, 2, 15, 0xf8); /* red */

	/* gbr24 */
	ipu_dc_map_clear(priv, IPU_DC_MAP_GBR24);
	ipu_dc_map_config(priv, IPU_DC_MAP_GBR24, 2, 15, 0xff); /* green */
	ipu_dc_map_config(priv, IPU_DC_MAP_GBR24, 1, 7, 0xff); /* blue */
	ipu_dc_map_config(priv, IPU_DC_MAP_GBR24, 0, 23, 0xff); /* red */

	/* bgr666 */
	ipu_dc_map_clear(priv, IPU_DC_MAP_BGR666);
	ipu_dc_map_config(priv, IPU_DC_MAP_BGR666, 0, 5, 0xfc); /* blue */
	ipu_dc_map_config(priv, IPU_DC_MAP_BGR666, 1, 11, 0xfc); /* green */
	ipu_dc_map_config(priv, IPU_DC_MAP_BGR666, 2, 17, 0xfc); /* red */

	/* lvds666 */
	ipu_dc_map_clear(priv, IPU_DC_MAP_LVDS666);
	ipu_dc_map_config(priv, IPU_DC_MAP_LVDS666, 0, 5, 0xfc); /* blue */
	ipu_dc_map_config(priv, IPU_DC_MAP_LVDS666, 1, 13, 0xfc); /* green */
	ipu_dc_map_config(priv, IPU_DC_MAP_LVDS666, 2, 21, 0xfc); /* red */

	/* bgr24 */
	ipu_dc_map_clear(priv, IPU_DC_MAP_BGR24);
	ipu_dc_map_config(priv, IPU_DC_MAP_BGR24, 2, 7, 0xff); /* red */
	ipu_dc_map_config(priv, IPU_DC_MAP_BGR24, 1, 15, 0xff); /* green */
	ipu_dc_map_config(priv, IPU_DC_MAP_BGR24, 0, 23, 0xff); /* blue */

	वापस 0;
पूर्ण

व्योम ipu_dc_निकास(काष्ठा ipu_soc *ipu)
अणु
पूर्ण
