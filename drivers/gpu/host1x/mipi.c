<शैली गुरु>
/*
 * Copyright (C) 2013 NVIDIA Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#समावेश <linux/clk.h>
#समावेश <linux/host1x.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "dev.h"

#घोषणा MIPI_CAL_CTRL			0x00
#घोषणा MIPI_CAL_CTRL_NOISE_FILTER(x)	(((x) & 0xf) << 26)
#घोषणा MIPI_CAL_CTRL_PRESCALE(x)	(((x) & 0x3) << 24)
#घोषणा MIPI_CAL_CTRL_CLKEN_OVR		(1 << 4)
#घोषणा MIPI_CAL_CTRL_START		(1 << 0)

#घोषणा MIPI_CAL_AUTOCAL_CTRL		0x01

#घोषणा MIPI_CAL_STATUS			0x02
#घोषणा MIPI_CAL_STATUS_DONE		(1 << 16)
#घोषणा MIPI_CAL_STATUS_ACTIVE		(1 <<  0)

#घोषणा MIPI_CAL_CONFIG_CSIA		0x05
#घोषणा MIPI_CAL_CONFIG_CSIB		0x06
#घोषणा MIPI_CAL_CONFIG_CSIC		0x07
#घोषणा MIPI_CAL_CONFIG_CSID		0x08
#घोषणा MIPI_CAL_CONFIG_CSIE		0x09
#घोषणा MIPI_CAL_CONFIG_CSIF		0x0a
#घोषणा MIPI_CAL_CONFIG_DSIA		0x0e
#घोषणा MIPI_CAL_CONFIG_DSIB		0x0f
#घोषणा MIPI_CAL_CONFIG_DSIC		0x10
#घोषणा MIPI_CAL_CONFIG_DSID		0x11

#घोषणा MIPI_CAL_CONFIG_DSIA_CLK	0x19
#घोषणा MIPI_CAL_CONFIG_DSIB_CLK	0x1a
#घोषणा MIPI_CAL_CONFIG_CSIAB_CLK	0x1b
#घोषणा MIPI_CAL_CONFIG_DSIC_CLK	0x1c
#घोषणा MIPI_CAL_CONFIG_CSICD_CLK	0x1c
#घोषणा MIPI_CAL_CONFIG_DSID_CLK	0x1d
#घोषणा MIPI_CAL_CONFIG_CSIE_CLK	0x1d

/* क्रम data and घड़ी lanes */
#घोषणा MIPI_CAL_CONFIG_SELECT		(1 << 21)

/* क्रम data lanes */
#घोषणा MIPI_CAL_CONFIG_HSPDOS(x)	(((x) & 0x1f) << 16)
#घोषणा MIPI_CAL_CONFIG_HSPUOS(x)	(((x) & 0x1f) <<  8)
#घोषणा MIPI_CAL_CONFIG_TERMOS(x)	(((x) & 0x1f) <<  0)

/* क्रम घड़ी lanes */
#घोषणा MIPI_CAL_CONFIG_HSCLKPDOSD(x)	(((x) & 0x1f) <<  8)
#घोषणा MIPI_CAL_CONFIG_HSCLKPUOSD(x)	(((x) & 0x1f) <<  0)

#घोषणा MIPI_CAL_BIAS_PAD_CFG0		0x16
#घोषणा MIPI_CAL_BIAS_PAD_PDVCLAMP	(1 << 1)
#घोषणा MIPI_CAL_BIAS_PAD_E_VCLAMP_REF	(1 << 0)

#घोषणा MIPI_CAL_BIAS_PAD_CFG1		0x17
#घोषणा MIPI_CAL_BIAS_PAD_DRV_DN_REF(x) (((x) & 0x7) << 16)
#घोषणा MIPI_CAL_BIAS_PAD_DRV_UP_REF(x) (((x) & 0x7) << 8)

#घोषणा MIPI_CAL_BIAS_PAD_CFG2		0x18
#घोषणा MIPI_CAL_BIAS_PAD_VCLAMP(x)	(((x) & 0x7) << 16)
#घोषणा MIPI_CAL_BIAS_PAD_VAUXP(x)	(((x) & 0x7) << 4)
#घोषणा MIPI_CAL_BIAS_PAD_PDVREG	(1 << 1)

काष्ठा tegra_mipi_pad अणु
	अचिन्हित दीर्घ data;
	अचिन्हित दीर्घ clk;
पूर्ण;

काष्ठा tegra_mipi_soc अणु
	bool has_clk_lane;
	स्थिर काष्ठा tegra_mipi_pad *pads;
	अचिन्हित पूर्णांक num_pads;

	bool घड़ी_enable_override;
	bool needs_vclamp_ref;

	/* bias pad configuration settings */
	u8 pad_drive_करोwn_ref;
	u8 pad_drive_up_ref;

	u8 pad_vclamp_level;
	u8 pad_vauxp_level;

	/* calibration settings क्रम data lanes */
	u8 hspकरोs;
	u8 hspuos;
	u8 termos;

	/* calibration settings क्रम घड़ी lanes */
	u8 hsclkpकरोs;
	u8 hsclkpuos;
पूर्ण;

काष्ठा tegra_mipi अणु
	स्थिर काष्ठा tegra_mipi_soc *soc;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा mutex lock;
	काष्ठा clk *clk;

	अचिन्हित दीर्घ usage_count;
पूर्ण;

काष्ठा tegra_mipi_device अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा tegra_mipi *mipi;
	काष्ठा device *device;
	अचिन्हित दीर्घ pads;
पूर्ण;

अटल अंतरभूत u32 tegra_mipi_पढ़ोl(काष्ठा tegra_mipi *mipi,
				   अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl(mipi->regs + (offset << 2));
पूर्ण

अटल अंतरभूत व्योम tegra_mipi_ग_लिखोl(काष्ठा tegra_mipi *mipi, u32 value,
				     अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl(value, mipi->regs + (offset << 2));
पूर्ण

अटल पूर्णांक tegra_mipi_घातer_up(काष्ठा tegra_mipi *mipi)
अणु
	u32 value;
	पूर्णांक err;

	err = clk_enable(mipi->clk);
	अगर (err < 0)
		वापस err;

	value = tegra_mipi_पढ़ोl(mipi, MIPI_CAL_BIAS_PAD_CFG0);
	value &= ~MIPI_CAL_BIAS_PAD_PDVCLAMP;

	अगर (mipi->soc->needs_vclamp_ref)
		value |= MIPI_CAL_BIAS_PAD_E_VCLAMP_REF;

	tegra_mipi_ग_लिखोl(mipi, value, MIPI_CAL_BIAS_PAD_CFG0);

	value = tegra_mipi_पढ़ोl(mipi, MIPI_CAL_BIAS_PAD_CFG2);
	value &= ~MIPI_CAL_BIAS_PAD_PDVREG;
	tegra_mipi_ग_लिखोl(mipi, value, MIPI_CAL_BIAS_PAD_CFG2);

	clk_disable(mipi->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_mipi_घातer_करोwn(काष्ठा tegra_mipi *mipi)
अणु
	u32 value;
	पूर्णांक err;

	err = clk_enable(mipi->clk);
	अगर (err < 0)
		वापस err;

	/*
	 * The MIPI_CAL_BIAS_PAD_PDVREG controls a voltage regulator that
	 * supplies the DSI pads. This must be kept enabled until none of the
	 * DSI lanes are used anymore.
	 */
	value = tegra_mipi_पढ़ोl(mipi, MIPI_CAL_BIAS_PAD_CFG2);
	value |= MIPI_CAL_BIAS_PAD_PDVREG;
	tegra_mipi_ग_लिखोl(mipi, value, MIPI_CAL_BIAS_PAD_CFG2);

	/*
	 * MIPI_CAL_BIAS_PAD_PDVCLAMP and MIPI_CAL_BIAS_PAD_E_VCLAMP_REF
	 * control a regulator that supplies current to the pre-driver logic.
	 * Powering करोwn this regulator causes DSI to fail, so it must reमुख्य
	 * घातered on until none of the DSI lanes are used anymore.
	 */
	value = tegra_mipi_पढ़ोl(mipi, MIPI_CAL_BIAS_PAD_CFG0);

	अगर (mipi->soc->needs_vclamp_ref)
		value &= ~MIPI_CAL_BIAS_PAD_E_VCLAMP_REF;

	value |= MIPI_CAL_BIAS_PAD_PDVCLAMP;
	tegra_mipi_ग_लिखोl(mipi, value, MIPI_CAL_BIAS_PAD_CFG0);

	वापस 0;
पूर्ण

काष्ठा tegra_mipi_device *tegra_mipi_request(काष्ठा device *device,
					     काष्ठा device_node *np)
अणु
	काष्ठा tegra_mipi_device *dev;
	काष्ठा of_phandle_args args;
	पूर्णांक err;

	err = of_parse_phandle_with_args(np, "nvidia,mipi-calibrate",
					 "#nvidia,mipi-calibrate-cells", 0,
					 &args);
	अगर (err < 0)
		वापस ERR_PTR(err);

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	dev->pdev = of_find_device_by_node(args.np);
	अगर (!dev->pdev) अणु
		err = -ENODEV;
		जाओ मुक्त;
	पूर्ण

	dev->mipi = platक्रमm_get_drvdata(dev->pdev);
	अगर (!dev->mipi) अणु
		err = -EPROBE_DEFER;
		जाओ put;
	पूर्ण

	of_node_put(args.np);

	dev->pads = args.args[0];
	dev->device = device;

	वापस dev;

put:
	platक्रमm_device_put(dev->pdev);
मुक्त:
	kमुक्त(dev);
out:
	of_node_put(args.np);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(tegra_mipi_request);

व्योम tegra_mipi_मुक्त(काष्ठा tegra_mipi_device *device)
अणु
	platक्रमm_device_put(device->pdev);
	kमुक्त(device);
पूर्ण
EXPORT_SYMBOL(tegra_mipi_मुक्त);

पूर्णांक tegra_mipi_enable(काष्ठा tegra_mipi_device *dev)
अणु
	पूर्णांक err = 0;

	mutex_lock(&dev->mipi->lock);

	अगर (dev->mipi->usage_count++ == 0)
		err = tegra_mipi_घातer_up(dev->mipi);

	mutex_unlock(&dev->mipi->lock);

	वापस err;

पूर्ण
EXPORT_SYMBOL(tegra_mipi_enable);

पूर्णांक tegra_mipi_disable(काष्ठा tegra_mipi_device *dev)
अणु
	पूर्णांक err = 0;

	mutex_lock(&dev->mipi->lock);

	अगर (--dev->mipi->usage_count == 0)
		err = tegra_mipi_घातer_करोwn(dev->mipi);

	mutex_unlock(&dev->mipi->lock);

	वापस err;

पूर्ण
EXPORT_SYMBOL(tegra_mipi_disable);

पूर्णांक tegra_mipi_finish_calibration(काष्ठा tegra_mipi_device *device)
अणु
	काष्ठा tegra_mipi *mipi = device->mipi;
	व्योम __iomem *status_reg = mipi->regs + (MIPI_CAL_STATUS << 2);
	u32 value;
	पूर्णांक err;

	err = पढ़ोl_relaxed_poll_समयout(status_reg, value,
					 !(value & MIPI_CAL_STATUS_ACTIVE) &&
					 (value & MIPI_CAL_STATUS_DONE), 50,
					 250000);
	mutex_unlock(&device->mipi->lock);
	clk_disable(device->mipi->clk);

	वापस err;
पूर्ण
EXPORT_SYMBOL(tegra_mipi_finish_calibration);

पूर्णांक tegra_mipi_start_calibration(काष्ठा tegra_mipi_device *device)
अणु
	स्थिर काष्ठा tegra_mipi_soc *soc = device->mipi->soc;
	अचिन्हित पूर्णांक i;
	u32 value;
	पूर्णांक err;

	err = clk_enable(device->mipi->clk);
	अगर (err < 0)
		वापस err;

	mutex_lock(&device->mipi->lock);

	value = MIPI_CAL_BIAS_PAD_DRV_DN_REF(soc->pad_drive_करोwn_ref) |
		MIPI_CAL_BIAS_PAD_DRV_UP_REF(soc->pad_drive_up_ref);
	tegra_mipi_ग_लिखोl(device->mipi, value, MIPI_CAL_BIAS_PAD_CFG1);

	value = tegra_mipi_पढ़ोl(device->mipi, MIPI_CAL_BIAS_PAD_CFG2);
	value &= ~MIPI_CAL_BIAS_PAD_VCLAMP(0x7);
	value &= ~MIPI_CAL_BIAS_PAD_VAUXP(0x7);
	value |= MIPI_CAL_BIAS_PAD_VCLAMP(soc->pad_vclamp_level);
	value |= MIPI_CAL_BIAS_PAD_VAUXP(soc->pad_vauxp_level);
	tegra_mipi_ग_लिखोl(device->mipi, value, MIPI_CAL_BIAS_PAD_CFG2);

	क्रम (i = 0; i < soc->num_pads; i++) अणु
		u32 clk = 0, data = 0;

		अगर (device->pads & BIT(i)) अणु
			data = MIPI_CAL_CONFIG_SELECT |
			       MIPI_CAL_CONFIG_HSPDOS(soc->hspकरोs) |
			       MIPI_CAL_CONFIG_HSPUOS(soc->hspuos) |
			       MIPI_CAL_CONFIG_TERMOS(soc->termos);
			clk = MIPI_CAL_CONFIG_SELECT |
			      MIPI_CAL_CONFIG_HSCLKPDOSD(soc->hsclkpकरोs) |
			      MIPI_CAL_CONFIG_HSCLKPUOSD(soc->hsclkpuos);
		पूर्ण

		tegra_mipi_ग_लिखोl(device->mipi, data, soc->pads[i].data);

		अगर (soc->has_clk_lane && soc->pads[i].clk != 0)
			tegra_mipi_ग_लिखोl(device->mipi, clk, soc->pads[i].clk);
	पूर्ण

	value = tegra_mipi_पढ़ोl(device->mipi, MIPI_CAL_CTRL);
	value &= ~MIPI_CAL_CTRL_NOISE_FILTER(0xf);
	value &= ~MIPI_CAL_CTRL_PRESCALE(0x3);
	value |= MIPI_CAL_CTRL_NOISE_FILTER(0xa);
	value |= MIPI_CAL_CTRL_PRESCALE(0x2);

	अगर (!soc->घड़ी_enable_override)
		value &= ~MIPI_CAL_CTRL_CLKEN_OVR;
	अन्यथा
		value |= MIPI_CAL_CTRL_CLKEN_OVR;

	tegra_mipi_ग_लिखोl(device->mipi, value, MIPI_CAL_CTRL);

	/* clear any pending status bits */
	value = tegra_mipi_पढ़ोl(device->mipi, MIPI_CAL_STATUS);
	tegra_mipi_ग_लिखोl(device->mipi, value, MIPI_CAL_STATUS);

	value = tegra_mipi_पढ़ोl(device->mipi, MIPI_CAL_CTRL);
	value |= MIPI_CAL_CTRL_START;
	tegra_mipi_ग_लिखोl(device->mipi, value, MIPI_CAL_CTRL);

	/*
	 * Wait क्रम min 72uS to let calibration logic finish calibration
	 * sequence codes beक्रमe रुकोing क्रम pads idle state to apply the
	 * results.
	 */
	usleep_range(75, 80);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_mipi_start_calibration);

अटल स्थिर काष्ठा tegra_mipi_pad tegra114_mipi_pads[] = अणु
	अणु .data = MIPI_CAL_CONFIG_CSIA पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIB पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIC पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSID पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIE पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSIA पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSIB पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSIC पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSID पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_mipi_soc tegra114_mipi_soc = अणु
	.has_clk_lane = false,
	.pads = tegra114_mipi_pads,
	.num_pads = ARRAY_SIZE(tegra114_mipi_pads),
	.घड़ी_enable_override = true,
	.needs_vclamp_ref = true,
	.pad_drive_करोwn_ref = 0x2,
	.pad_drive_up_ref = 0x0,
	.pad_vclamp_level = 0x0,
	.pad_vauxp_level = 0x0,
	.hspकरोs = 0x0,
	.hspuos = 0x4,
	.termos = 0x5,
	.hsclkpकरोs = 0x0,
	.hsclkpuos = 0x4,
पूर्ण;

अटल स्थिर काष्ठा tegra_mipi_pad tegra124_mipi_pads[] = अणु
	अणु .data = MIPI_CAL_CONFIG_CSIA, .clk = MIPI_CAL_CONFIG_CSIAB_CLK पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIB, .clk = MIPI_CAL_CONFIG_CSIAB_CLK पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIC, .clk = MIPI_CAL_CONFIG_CSICD_CLK पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSID, .clk = MIPI_CAL_CONFIG_CSICD_CLK पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIE, .clk = MIPI_CAL_CONFIG_CSIE_CLK  पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSIA, .clk = MIPI_CAL_CONFIG_DSIA_CLK  पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSIB, .clk = MIPI_CAL_CONFIG_DSIB_CLK  पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_mipi_soc tegra124_mipi_soc = अणु
	.has_clk_lane = true,
	.pads = tegra124_mipi_pads,
	.num_pads = ARRAY_SIZE(tegra124_mipi_pads),
	.घड़ी_enable_override = true,
	.needs_vclamp_ref = true,
	.pad_drive_करोwn_ref = 0x2,
	.pad_drive_up_ref = 0x0,
	.pad_vclamp_level = 0x0,
	.pad_vauxp_level = 0x0,
	.hspकरोs = 0x0,
	.hspuos = 0x0,
	.termos = 0x0,
	.hsclkpकरोs = 0x1,
	.hsclkpuos = 0x2,
पूर्ण;

अटल स्थिर काष्ठा tegra_mipi_soc tegra132_mipi_soc = अणु
	.has_clk_lane = true,
	.pads = tegra124_mipi_pads,
	.num_pads = ARRAY_SIZE(tegra124_mipi_pads),
	.घड़ी_enable_override = false,
	.needs_vclamp_ref = false,
	.pad_drive_करोwn_ref = 0x0,
	.pad_drive_up_ref = 0x3,
	.pad_vclamp_level = 0x0,
	.pad_vauxp_level = 0x0,
	.hspकरोs = 0x0,
	.hspuos = 0x0,
	.termos = 0x0,
	.hsclkpकरोs = 0x3,
	.hsclkpuos = 0x2,
पूर्ण;

अटल स्थिर काष्ठा tegra_mipi_pad tegra210_mipi_pads[] = अणु
	अणु .data = MIPI_CAL_CONFIG_CSIA, .clk = 0 पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIB, .clk = 0 पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIC, .clk = 0 पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSID, .clk = 0 पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIE, .clk = 0 पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_CSIF, .clk = 0 पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSIA, .clk = MIPI_CAL_CONFIG_DSIA_CLK पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSIB, .clk = MIPI_CAL_CONFIG_DSIB_CLK पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSIC, .clk = MIPI_CAL_CONFIG_DSIC_CLK पूर्ण,
	अणु .data = MIPI_CAL_CONFIG_DSID, .clk = MIPI_CAL_CONFIG_DSID_CLK पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_mipi_soc tegra210_mipi_soc = अणु
	.has_clk_lane = true,
	.pads = tegra210_mipi_pads,
	.num_pads = ARRAY_SIZE(tegra210_mipi_pads),
	.घड़ी_enable_override = true,
	.needs_vclamp_ref = false,
	.pad_drive_करोwn_ref = 0x0,
	.pad_drive_up_ref = 0x3,
	.pad_vclamp_level = 0x1,
	.pad_vauxp_level = 0x1,
	.hspकरोs = 0x0,
	.hspuos = 0x2,
	.termos = 0x0,
	.hsclkpकरोs = 0x0,
	.hsclkpuos = 0x2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_mipi_of_match[] = अणु
	अणु .compatible = "nvidia,tegra114-mipi", .data = &tegra114_mipi_soc पूर्ण,
	अणु .compatible = "nvidia,tegra124-mipi", .data = &tegra124_mipi_soc पूर्ण,
	अणु .compatible = "nvidia,tegra132-mipi", .data = &tegra132_mipi_soc पूर्ण,
	अणु .compatible = "nvidia,tegra210-mipi", .data = &tegra210_mipi_soc पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक tegra_mipi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा tegra_mipi *mipi;
	काष्ठा resource *res;
	पूर्णांक err;

	match = of_match_node(tegra_mipi_of_match, pdev->dev.of_node);
	अगर (!match)
		वापस -ENODEV;

	mipi = devm_kzalloc(&pdev->dev, माप(*mipi), GFP_KERNEL);
	अगर (!mipi)
		वापस -ENOMEM;

	mipi->soc = match->data;
	mipi->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mipi->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mipi->regs))
		वापस PTR_ERR(mipi->regs);

	mutex_init(&mipi->lock);

	mipi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mipi->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस PTR_ERR(mipi->clk);
	पूर्ण

	err = clk_prepare(mipi->clk);
	अगर (err < 0)
		वापस err;

	platक्रमm_set_drvdata(pdev, mipi);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_mipi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_mipi *mipi = platक्रमm_get_drvdata(pdev);

	clk_unprepare(mipi->clk);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver tegra_mipi_driver = अणु
	.driver = अणु
		.name = "tegra-mipi",
		.of_match_table = tegra_mipi_of_match,
	पूर्ण,
	.probe = tegra_mipi_probe,
	.हटाओ = tegra_mipi_हटाओ,
पूर्ण;
