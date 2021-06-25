<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Mellanox Technologies.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "dw_mmc.h"
#समावेश "dw_mmc-pltfm.h"

#घोषणा UHS_REG_EXT_SAMPLE_MASK		GENMASK(22, 16)
#घोषणा UHS_REG_EXT_DRIVE_MASK		GENMASK(29, 23)
#घोषणा BLUEFIELD_UHS_REG_EXT_SAMPLE	2
#घोषणा BLUEFIELD_UHS_REG_EXT_DRIVE	4

अटल व्योम dw_mci_bluefield_set_ios(काष्ठा dw_mci *host, काष्ठा mmc_ios *ios)
अणु
	u32 reg;

	/* Update the Drive and Sample fields in रेजिस्टर UHS_REG_EXT. */
	reg = mci_पढ़ोl(host, UHS_REG_EXT);
	reg &= ~UHS_REG_EXT_SAMPLE_MASK;
	reg |= FIELD_PREP(UHS_REG_EXT_SAMPLE_MASK,
			  BLUEFIELD_UHS_REG_EXT_SAMPLE);
	reg &= ~UHS_REG_EXT_DRIVE_MASK;
	reg |= FIELD_PREP(UHS_REG_EXT_DRIVE_MASK, BLUEFIELD_UHS_REG_EXT_DRIVE);
	mci_ग_लिखोl(host, UHS_REG_EXT, reg);
पूर्ण

अटल स्थिर काष्ठा dw_mci_drv_data bluefield_drv_data = अणु
	.set_ios		= dw_mci_bluefield_set_ios
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_mci_bluefield_match[] = अणु
	अणु .compatible = "mellanox,bluefield-dw-mshc",
	  .data = &bluefield_drv_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_mci_bluefield_match);

अटल पूर्णांक dw_mci_bluefield_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस dw_mci_pltfm_रेजिस्टर(pdev, &bluefield_drv_data);
पूर्ण

अटल काष्ठा platक्रमm_driver dw_mci_bluefield_pltfm_driver = अणु
	.probe		= dw_mci_bluefield_probe,
	.हटाओ		= dw_mci_pltfm_हटाओ,
	.driver		= अणु
		.name		= "dwmmc_bluefield",
		.probe_type	= PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table	= dw_mci_bluefield_match,
		.pm		= &dw_mci_pltfm_pmops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dw_mci_bluefield_pltfm_driver);

MODULE_DESCRIPTION("BlueField DW Multimedia Card driver");
MODULE_AUTHOR("Mellanox Technologies");
MODULE_LICENSE("GPL v2");
