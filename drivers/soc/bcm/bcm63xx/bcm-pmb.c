<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2013 Broadcom
 * Copyright (C) 2020 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <dt-bindings/soc/bcm-pmb.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/reset/bcm63xx_pmb.h>

#घोषणा BPCM_ID_REG					0x00
#घोषणा BPCM_CAPABILITIES				0x04
#घोषणा  BPCM_CAP_NUM_ZONES				0x000000ff
#घोषणा  BPCM_CAP_SR_REG_BITS				0x0000ff00
#घोषणा  BPCM_CAP_PLLTYPE				0x00030000
#घोषणा  BPCM_CAP_UBUS					0x00080000
#घोषणा BPCM_CONTROL					0x08
#घोषणा BPCM_STATUS					0x0c
#घोषणा BPCM_ROSC_CONTROL				0x10
#घोषणा BPCM_ROSC_THRESH_H				0x14
#घोषणा BPCM_ROSC_THRESHOLD_BCM6838			0x14
#घोषणा BPCM_ROSC_THRESH_S				0x18
#घोषणा BPCM_ROSC_COUNT_BCM6838				0x18
#घोषणा BPCM_ROSC_COUNT					0x1c
#घोषणा BPCM_PWD_CONTROL_BCM6838			0x1c
#घोषणा BPCM_PWD_CONTROL				0x20
#घोषणा BPCM_SR_CONTROL_BCM6838				0x20
#घोषणा BPCM_PWD_ACCUM_CONTROL				0x24
#घोषणा BPCM_SR_CONTROL					0x28
#घोषणा BPCM_GLOBAL_CONTROL				0x2c
#घोषणा BPCM_MISC_CONTROL				0x30
#घोषणा BPCM_MISC_CONTROL2				0x34
#घोषणा BPCM_SGPHY_CNTL					0x38
#घोषणा BPCM_SGPHY_STATUS				0x3c
#घोषणा BPCM_ZONE0					0x40
#घोषणा  BPCM_ZONE_CONTROL				0x00
#घोषणा   BPCM_ZONE_CONTROL_MANUAL_CLK_EN		0x00000001
#घोषणा   BPCM_ZONE_CONTROL_MANUAL_RESET_CTL		0x00000002
#घोषणा   BPCM_ZONE_CONTROL_FREQ_SCALE_USED		0x00000004	/* R/O */
#घोषणा   BPCM_ZONE_CONTROL_DPG_CAPABLE			0x00000008	/* R/O */
#घोषणा   BPCM_ZONE_CONTROL_MANUAL_MEM_PWR		0x00000030
#घोषणा   BPCM_ZONE_CONTROL_MANUAL_ISO_CTL		0x00000040
#घोषणा   BPCM_ZONE_CONTROL_MANUAL_CTL			0x00000080
#घोषणा   BPCM_ZONE_CONTROL_DPG_CTL_EN			0x00000100
#घोषणा   BPCM_ZONE_CONTROL_PWR_DN_REQ			0x00000200
#घोषणा   BPCM_ZONE_CONTROL_PWR_UP_REQ			0x00000400
#घोषणा   BPCM_ZONE_CONTROL_MEM_PWR_CTL_EN		0x00000800
#घोषणा   BPCM_ZONE_CONTROL_BLK_RESET_ASSERT		0x00001000
#घोषणा   BPCM_ZONE_CONTROL_MEM_STBY			0x00002000
#घोषणा   BPCM_ZONE_CONTROL_RESERVED			0x0007c000
#घोषणा   BPCM_ZONE_CONTROL_PWR_CNTL_STATE		0x00f80000
#घोषणा   BPCM_ZONE_CONTROL_FREQ_SCALAR_DYN_SEL		0x01000000	/* R/O */
#घोषणा   BPCM_ZONE_CONTROL_PWR_OFF_STATE		0x02000000	/* R/O */
#घोषणा   BPCM_ZONE_CONTROL_PWR_ON_STATE		0x04000000	/* R/O */
#घोषणा   BPCM_ZONE_CONTROL_PWR_GOOD			0x08000000	/* R/O */
#घोषणा   BPCM_ZONE_CONTROL_DPG_PWR_STATE		0x10000000	/* R/O */
#घोषणा   BPCM_ZONE_CONTROL_MEM_PWR_STATE		0x20000000	/* R/O */
#घोषणा   BPCM_ZONE_CONTROL_ISO_STATE			0x40000000	/* R/O */
#घोषणा   BPCM_ZONE_CONTROL_RESET_STATE			0x80000000	/* R/O */
#घोषणा  BPCM_ZONE_CONFIG1				0x04
#घोषणा  BPCM_ZONE_CONFIG2				0x08
#घोषणा  BPCM_ZONE_FREQ_SCALAR_CONTROL			0x0c
#घोषणा  BPCM_ZONE_SIZE					0x10

काष्ठा bcm_pmb अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	spinlock_t lock;
	bool little_endian;
	काष्ठा genpd_onecell_data genpd_onecell_data;
पूर्ण;

काष्ठा bcm_pmb_pd_data अणु
	स्थिर अक्षर * स्थिर name;
	पूर्णांक id;
	u8 bus;
	u8 device;
पूर्ण;

काष्ठा bcm_pmb_pm_करोमुख्य अणु
	काष्ठा bcm_pmb *pmb;
	स्थिर काष्ठा bcm_pmb_pd_data *data;
	काष्ठा generic_pm_करोमुख्य genpd;
पूर्ण;

अटल पूर्णांक bcm_pmb_bpcm_पढ़ो(काष्ठा bcm_pmb *pmb, पूर्णांक bus, u8 device,
			     पूर्णांक offset, u32 *val)
अणु
	व्योम __iomem *base = pmb->base + bus * 0x20;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&pmb->lock, flags);
	err = bpcm_rd(base, device, offset, val);
	spin_unlock_irqrestore(&pmb->lock, flags);

	अगर (!err)
		*val = pmb->little_endian ? le32_to_cpu(*val) : be32_to_cpu(*val);

	वापस err;
पूर्ण

अटल पूर्णांक bcm_pmb_bpcm_ग_लिखो(काष्ठा bcm_pmb *pmb, पूर्णांक bus, u8 device,
			      पूर्णांक offset, u32 val)
अणु
	व्योम __iomem *base = pmb->base + bus * 0x20;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	val = pmb->little_endian ? cpu_to_le32(val) : cpu_to_be32(val);

	spin_lock_irqsave(&pmb->lock, flags);
	err = bpcm_wr(base, device, offset, val);
	spin_unlock_irqrestore(&pmb->lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक bcm_pmb_घातer_off_zone(काष्ठा bcm_pmb *pmb, पूर्णांक bus, u8 device,
				  पूर्णांक zone)
अणु
	पूर्णांक offset;
	u32 val;
	पूर्णांक err;

	offset = BPCM_ZONE0 + zone * BPCM_ZONE_SIZE + BPCM_ZONE_CONTROL;

	err = bcm_pmb_bpcm_पढ़ो(pmb, bus, device, offset, &val);
	अगर (err)
		वापस err;

	val |= BPCM_ZONE_CONTROL_PWR_DN_REQ;
	val &= ~BPCM_ZONE_CONTROL_PWR_UP_REQ;

	err = bcm_pmb_bpcm_ग_लिखो(pmb, bus, device, offset, val);

	वापस err;
पूर्ण

अटल पूर्णांक bcm_pmb_घातer_on_zone(काष्ठा bcm_pmb *pmb, पूर्णांक bus, u8 device,
				 पूर्णांक zone)
अणु
	पूर्णांक offset;
	u32 val;
	पूर्णांक err;

	offset = BPCM_ZONE0 + zone * BPCM_ZONE_SIZE + BPCM_ZONE_CONTROL;

	err = bcm_pmb_bpcm_पढ़ो(pmb, bus, device, offset, &val);
	अगर (err)
		वापस err;

	अगर (!(val & BPCM_ZONE_CONTROL_PWR_ON_STATE)) अणु
		val &= ~BPCM_ZONE_CONTROL_PWR_DN_REQ;
		val |= BPCM_ZONE_CONTROL_DPG_CTL_EN;
		val |= BPCM_ZONE_CONTROL_PWR_UP_REQ;
		val |= BPCM_ZONE_CONTROL_MEM_PWR_CTL_EN;
		val |= BPCM_ZONE_CONTROL_BLK_RESET_ASSERT;

		err = bcm_pmb_bpcm_ग_लिखो(pmb, bus, device, offset, val);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bcm_pmb_घातer_off_device(काष्ठा bcm_pmb *pmb, पूर्णांक bus, u8 device)
अणु
	पूर्णांक offset;
	u32 val;
	पूर्णांक err;

	/* Entire device can be घातered off by घातering off the 0th zone */
	offset = BPCM_ZONE0 + BPCM_ZONE_CONTROL;

	err = bcm_pmb_bpcm_पढ़ो(pmb, bus, device, offset, &val);
	अगर (err)
		वापस err;

	अगर (!(val & BPCM_ZONE_CONTROL_PWR_OFF_STATE)) अणु
		val = BPCM_ZONE_CONTROL_PWR_DN_REQ;

		err = bcm_pmb_bpcm_ग_लिखो(pmb, bus, device, offset, val);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bcm_pmb_घातer_on_device(काष्ठा bcm_pmb *pmb, पूर्णांक bus, u8 device)
अणु
	u32 val;
	पूर्णांक err;
	पूर्णांक i;

	err = bcm_pmb_bpcm_पढ़ो(pmb, bus, device, BPCM_CAPABILITIES, &val);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < (val & BPCM_CAP_NUM_ZONES); i++) अणु
		err = bcm_pmb_घातer_on_zone(pmb, bus, device, i);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bcm_pmb_घातer_on_sata(काष्ठा bcm_pmb *pmb, पूर्णांक bus, u8 device)
अणु
	पूर्णांक err;

	err = bcm_pmb_घातer_on_zone(pmb, bus, device, 0);
	अगर (err)
		वापस err;

	/* Does not apply to the BCM963158 */
	err = bcm_pmb_bpcm_ग_लिखो(pmb, bus, device, BPCM_MISC_CONTROL, 0);
	अगर (err)
		वापस err;

	err = bcm_pmb_bpcm_ग_लिखो(pmb, bus, device, BPCM_SR_CONTROL, 0xffffffff);
	अगर (err)
		वापस err;

	err = bcm_pmb_bpcm_ग_लिखो(pmb, bus, device, BPCM_SR_CONTROL, 0);

	वापस err;
पूर्ण

अटल पूर्णांक bcm_pmb_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा bcm_pmb_pm_करोमुख्य *pd = container_of(genpd, काष्ठा bcm_pmb_pm_करोमुख्य, genpd);
	स्थिर काष्ठा bcm_pmb_pd_data *data = pd->data;
	काष्ठा bcm_pmb *pmb = pd->pmb;

	चयन (data->id) अणु
	हाल BCM_PMB_PCIE0:
	हाल BCM_PMB_PCIE1:
	हाल BCM_PMB_PCIE2:
		वापस bcm_pmb_घातer_on_zone(pmb, data->bus, data->device, 0);
	हाल BCM_PMB_HOST_USB:
		वापस bcm_pmb_घातer_on_device(pmb, data->bus, data->device);
	हाल BCM_PMB_SATA:
		वापस bcm_pmb_घातer_on_sata(pmb, data->bus, data->device);
	शेष:
		dev_err(pmb->dev, "unsupported device id: %d\n", data->id);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_pmb_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा bcm_pmb_pm_करोमुख्य *pd = container_of(genpd, काष्ठा bcm_pmb_pm_करोमुख्य, genpd);
	स्थिर काष्ठा bcm_pmb_pd_data *data = pd->data;
	काष्ठा bcm_pmb *pmb = pd->pmb;

	चयन (data->id) अणु
	हाल BCM_PMB_PCIE0:
	हाल BCM_PMB_PCIE1:
	हाल BCM_PMB_PCIE2:
		वापस bcm_pmb_घातer_off_zone(pmb, data->bus, data->device, 0);
	हाल BCM_PMB_HOST_USB:
		वापस bcm_pmb_घातer_off_device(pmb, data->bus, data->device);
	शेष:
		dev_err(pmb->dev, "unsupported device id: %d\n", data->id);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_pmb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा bcm_pmb_pd_data *table;
	स्थिर काष्ठा bcm_pmb_pd_data *e;
	काष्ठा resource *res;
	काष्ठा bcm_pmb *pmb;
	पूर्णांक max_id;
	पूर्णांक err;

	pmb = devm_kzalloc(dev, माप(*pmb), GFP_KERNEL);
	अगर (!pmb)
		वापस -ENOMEM;

	pmb->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pmb->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(pmb->base))
		वापस PTR_ERR(pmb->base);

	spin_lock_init(&pmb->lock);

	pmb->little_endian = !of_device_is_big_endian(dev->of_node);

	table = of_device_get_match_data(dev);
	अगर (!table)
		वापस -EINVAL;

	max_id = 0;
	क्रम (e = table; e->name; e++)
		max_id = max(max_id, e->id);

	pmb->genpd_onecell_data.num_करोमुख्यs = max_id + 1;
	pmb->genpd_onecell_data.करोमुख्यs =
		devm_kसुस्मृति(dev, pmb->genpd_onecell_data.num_करोमुख्यs,
			     माप(काष्ठा generic_pm_करोमुख्य *), GFP_KERNEL);
	अगर (!pmb->genpd_onecell_data.करोमुख्यs)
		वापस -ENOMEM;

	क्रम (e = table; e->name; e++) अणु
		काष्ठा bcm_pmb_pm_करोमुख्य *pd = devm_kzalloc(dev, माप(*pd), GFP_KERNEL);

		pd->pmb = pmb;
		pd->data = e;
		pd->genpd.name = e->name;
		pd->genpd.घातer_on = bcm_pmb_घातer_on;
		pd->genpd.घातer_off = bcm_pmb_घातer_off;

		pm_genpd_init(&pd->genpd, शून्य, true);
		pmb->genpd_onecell_data.करोमुख्यs[e->id] = &pd->genpd;
	पूर्ण

	err = of_genpd_add_provider_onecell(dev->of_node, &pmb->genpd_onecell_data);
	अगर (err) अणु
		dev_err(dev, "failed to add genpd provider: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bcm_pmb_pd_data bcm_pmb_bcm4908_data[] = अणु
	अणु .name = "pcie2", .id = BCM_PMB_PCIE2, .bus = 0, .device = 2, पूर्ण,
	अणु .name = "pcie0", .id = BCM_PMB_PCIE0, .bus = 1, .device = 14, पूर्ण,
	अणु .name = "pcie1", .id = BCM_PMB_PCIE1, .bus = 1, .device = 15, पूर्ण,
	अणु .name = "usb", .id = BCM_PMB_HOST_USB, .bus = 1, .device = 17, पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bcm_pmb_pd_data bcm_pmb_bcm63138_data[] = अणु
	अणु .name = "sata", .id = BCM_PMB_SATA, .bus = 0, .device = 3, पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm_pmb_of_match[] = अणु
	अणु .compatible = "brcm,bcm4908-pmb", .data = &bcm_pmb_bcm4908_data, पूर्ण,
	अणु .compatible = "brcm,bcm63138-pmb", .data = &bcm_pmb_bcm63138_data, पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm_pmb_driver = अणु
	.driver = अणु
		.name = "bcm-pmb",
		.of_match_table = bcm_pmb_of_match,
	पूर्ण,
	.probe  = bcm_pmb_probe,
पूर्ण;

builtin_platक्रमm_driver(bcm_pmb_driver);
