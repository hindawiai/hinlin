<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Setup platक्रमm devices needed by the Freescale multi-port host
 * and/or dual-role USB controller modules based on the description
 * in flat device tree.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>

काष्ठा fsl_usb2_dev_data अणु
	अक्षर *dr_mode;		/* controller mode */
	अक्षर *drivers[3];	/* drivers to instantiate क्रम this mode */
	क्रमागत fsl_usb2_operating_modes op_mode;	/* operating mode */
पूर्ण;

अटल काष्ठा fsl_usb2_dev_data dr_mode_data[] = अणु
	अणु
		.dr_mode = "host",
		.drivers = अणु "fsl-ehci", शून्य, शून्य, पूर्ण,
		.op_mode = FSL_USB2_DR_HOST,
	पूर्ण,
	अणु
		.dr_mode = "otg",
		.drivers = अणु "fsl-usb2-otg", "fsl-ehci", "fsl-usb2-udc", पूर्ण,
		.op_mode = FSL_USB2_DR_OTG,
	पूर्ण,
	अणु
		.dr_mode = "peripheral",
		.drivers = अणु "fsl-usb2-udc", शून्य, शून्य, पूर्ण,
		.op_mode = FSL_USB2_DR_DEVICE,
	पूर्ण,
पूर्ण;

अटल काष्ठा fsl_usb2_dev_data *get_dr_mode_data(काष्ठा device_node *np)
अणु
	स्थिर अचिन्हित अक्षर *prop;
	पूर्णांक i;

	prop = of_get_property(np, "dr_mode", शून्य);
	अगर (prop) अणु
		क्रम (i = 0; i < ARRAY_SIZE(dr_mode_data); i++) अणु
			अगर (!म_भेद(prop, dr_mode_data[i].dr_mode))
				वापस &dr_mode_data[i];
		पूर्ण
	पूर्ण
	pr_warn("%pOF: Invalid 'dr_mode' property, fallback to host mode\n",
		np);
	वापस &dr_mode_data[0]; /* mode not specअगरied, use host */
पूर्ण

अटल क्रमागत fsl_usb2_phy_modes determine_usb_phy(स्थिर अक्षर *phy_type)
अणु
	अगर (!phy_type)
		वापस FSL_USB2_PHY_NONE;
	अगर (!strहालcmp(phy_type, "ulpi"))
		वापस FSL_USB2_PHY_ULPI;
	अगर (!strहालcmp(phy_type, "utmi"))
		वापस FSL_USB2_PHY_UTMI;
	अगर (!strहालcmp(phy_type, "utmi_wide"))
		वापस FSL_USB2_PHY_UTMI_WIDE;
	अगर (!strहालcmp(phy_type, "utmi_dual"))
		वापस FSL_USB2_PHY_UTMI_DUAL;
	अगर (!strहालcmp(phy_type, "serial"))
		वापस FSL_USB2_PHY_SERIAL;

	वापस FSL_USB2_PHY_NONE;
पूर्ण

अटल काष्ठा platक्रमm_device *fsl_usb2_device_रेजिस्टर(
					काष्ठा platक्रमm_device *ofdev,
					काष्ठा fsl_usb2_platक्रमm_data *pdata,
					स्थिर अक्षर *name, पूर्णांक id)
अणु
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा resource *res = ofdev->resource;
	अचिन्हित पूर्णांक num = ofdev->num_resources;
	पूर्णांक retval;

	pdev = platक्रमm_device_alloc(name, id);
	अगर (!pdev) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	pdev->dev.parent = &ofdev->dev;

	pdev->dev.coherent_dma_mask = ofdev->dev.coherent_dma_mask;

	अगर (!pdev->dev.dma_mask) अणु
		pdev->dev.dma_mask = &ofdev->dev.coherent_dma_mask;
	पूर्ण अन्यथा अणु
		retval = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (retval)
			जाओ error;
	पूर्ण

	retval = platक्रमm_device_add_data(pdev, pdata, माप(*pdata));
	अगर (retval)
		जाओ error;

	अगर (num) अणु
		retval = platक्रमm_device_add_resources(pdev, res, num);
		अगर (retval)
			जाओ error;
	पूर्ण

	retval = platक्रमm_device_add(pdev);
	अगर (retval)
		जाओ error;

	वापस pdev;

error:
	platक्रमm_device_put(pdev);
	वापस ERR_PTR(retval);
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_usb2_mph_dr_of_match[];

अटल क्रमागत fsl_usb2_controller_ver usb_get_ver_info(काष्ठा device_node *np)
अणु
	क्रमागत fsl_usb2_controller_ver ver = FSL_USB_VER_NONE;

	/*
	 * वापसs 1 क्रम usb controller version 1.6
	 * वापसs 2 क्रम usb controller version 2.2
	 * वापसs 3 क्रम usb controller version 2.4
	 * वापसs 4 क्रम usb controller version 2.5
	 * वापसs 0 otherwise
	 */
	अगर (of_device_is_compatible(np, "fsl-usb2-dr")) अणु
		अगर (of_device_is_compatible(np, "fsl-usb2-dr-v1.6"))
			ver = FSL_USB_VER_1_6;
		अन्यथा अगर (of_device_is_compatible(np, "fsl-usb2-dr-v2.2"))
			ver = FSL_USB_VER_2_2;
		अन्यथा अगर (of_device_is_compatible(np, "fsl-usb2-dr-v2.4"))
			ver = FSL_USB_VER_2_4;
		अन्यथा अगर (of_device_is_compatible(np, "fsl-usb2-dr-v2.5"))
			ver = FSL_USB_VER_2_5;
		अन्यथा /* क्रम previous controller versions */
			ver = FSL_USB_VER_OLD;

		अगर (ver > FSL_USB_VER_NONE)
			वापस ver;
	पूर्ण

	अगर (of_device_is_compatible(np, "fsl,mpc5121-usb2-dr"))
		वापस FSL_USB_VER_OLD;

	अगर (of_device_is_compatible(np, "fsl-usb2-mph")) अणु
		अगर (of_device_is_compatible(np, "fsl-usb2-mph-v1.6"))
			ver = FSL_USB_VER_1_6;
		अन्यथा अगर (of_device_is_compatible(np, "fsl-usb2-mph-v2.2"))
			ver = FSL_USB_VER_2_2;
		अन्यथा अगर (of_device_is_compatible(np, "fsl-usb2-mph-v2.4"))
			ver = FSL_USB_VER_2_4;
		अन्यथा अगर (of_device_is_compatible(np, "fsl-usb2-mph-v2.5"))
			ver = FSL_USB_VER_2_5;
		अन्यथा /* क्रम previous controller versions */
			ver = FSL_USB_VER_OLD;
	पूर्ण

	वापस ver;
पूर्ण

अटल पूर्णांक fsl_usb2_mph_dr_of_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा platक्रमm_device *usb_dev;
	काष्ठा fsl_usb2_platक्रमm_data data, *pdata;
	काष्ठा fsl_usb2_dev_data *dev_data;
	स्थिर काष्ठा of_device_id *match;
	स्थिर अचिन्हित अक्षर *prop;
	अटल अचिन्हित पूर्णांक idx;
	पूर्णांक i;

	अगर (!of_device_is_available(np))
		वापस -ENODEV;

	match = of_match_device(fsl_usb2_mph_dr_of_match, &ofdev->dev);
	अगर (!match)
		वापस -ENODEV;

	pdata = &data;
	अगर (match->data)
		स_नकल(pdata, match->data, माप(data));
	अन्यथा
		स_रखो(pdata, 0, माप(data));

	dev_data = get_dr_mode_data(np);

	अगर (of_device_is_compatible(np, "fsl-usb2-mph")) अणु
		अगर (of_get_property(np, "port0", शून्य))
			pdata->port_enables |= FSL_USB2_PORT0_ENABLED;

		अगर (of_get_property(np, "port1", शून्य))
			pdata->port_enables |= FSL_USB2_PORT1_ENABLED;

		pdata->operating_mode = FSL_USB2_MPH_HOST;
	पूर्ण अन्यथा अणु
		अगर (of_get_property(np, "fsl,invert-drvvbus", शून्य))
			pdata->invert_drvvbus = 1;

		अगर (of_get_property(np, "fsl,invert-pwr-fault", शून्य))
			pdata->invert_pwr_fault = 1;

		/* setup mode selected in the device tree */
		pdata->operating_mode = dev_data->op_mode;
	पूर्ण

	prop = of_get_property(np, "phy_type", शून्य);
	pdata->phy_mode = determine_usb_phy(prop);
	pdata->controller_ver = usb_get_ver_info(np);

	/* Activate Erratum by पढ़ोing property in device tree */
	pdata->has_fsl_erratum_a007792 =
		of_property_पढ़ो_bool(np, "fsl,usb-erratum-a007792");
	pdata->has_fsl_erratum_a005275 =
		of_property_पढ़ो_bool(np, "fsl,usb-erratum-a005275");
	pdata->has_fsl_erratum_a005697 =
		of_property_पढ़ो_bool(np, "fsl,usb_erratum-a005697");
	pdata->has_fsl_erratum_a006918 =
		of_property_पढ़ो_bool(np, "fsl,usb_erratum-a006918");
	pdata->has_fsl_erratum_14 =
		of_property_पढ़ो_bool(np, "fsl,usb_erratum-14");

	/*
	 * Determine whether phy_clk_valid needs to be checked
	 * by पढ़ोing property in device tree
	 */
	pdata->check_phy_clk_valid =
		of_property_पढ़ो_bool(np, "phy-clk-valid");

	अगर (pdata->have_sysअगर_regs) अणु
		अगर (pdata->controller_ver == FSL_USB_VER_NONE) अणु
			dev_warn(&ofdev->dev, "Could not get controller version\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(dev_data->drivers); i++) अणु
		अगर (!dev_data->drivers[i])
			जारी;
		usb_dev = fsl_usb2_device_रेजिस्टर(ofdev, pdata,
					dev_data->drivers[i], idx);
		अगर (IS_ERR(usb_dev)) अणु
			dev_err(&ofdev->dev, "Can't register usb device\n");
			वापस PTR_ERR(usb_dev);
		पूर्ण
	पूर्ण
	idx++;
	वापस 0;
पूर्ण

अटल पूर्णांक __unरेजिस्टर_subdev(काष्ठा device *dev, व्योम *d)
अणु
	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_usb2_mph_dr_of_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	device_क्रम_each_child(&ofdev->dev, शून्य, __unरेजिस्टर_subdev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC_MPC512x

#घोषणा USBGENCTRL		0x200		/* NOTE: big endian */
#घोषणा GC_WU_INT_CLR		(1 << 5)	/* Wakeup पूर्णांक clear */
#घोषणा GC_ULPI_SEL		(1 << 4)	/* ULPI i/f select (usb0 only)*/
#घोषणा GC_PPP			(1 << 3)	/* Inv. Port Power Polarity */
#घोषणा GC_PFP			(1 << 2)	/* Inv. Power Fault Polarity */
#घोषणा GC_WU_ULPI_EN		(1 << 1)	/* Wakeup on ULPI event */
#घोषणा GC_WU_IE		(1 << 1)	/* Wakeup पूर्णांकerrupt enable */

#घोषणा ISIPHYCTRL		0x204		/* NOTE: big endian */
#घोषणा PHYCTRL_PHYE		(1 << 4)	/* On-chip UTMI PHY enable */
#घोषणा PHYCTRL_BSENH		(1 << 3)	/* Bit Stuff Enable High */
#घोषणा PHYCTRL_BSEN		(1 << 2)	/* Bit Stuff Enable */
#घोषणा PHYCTRL_LSFE		(1 << 1)	/* Line State Filter Enable */
#घोषणा PHYCTRL_PXE		(1 << 0)	/* PHY oscillator enable */

पूर्णांक fsl_usb2_mpc5121_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_usb2_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा clk *clk;
	पूर्णांक err;

	clk = devm_clk_get(pdev->dev.parent, "ipg");
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "failed to get clk\n");
		वापस PTR_ERR(clk);
	पूर्ण
	err = clk_prepare_enable(clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable clk\n");
		वापस err;
	पूर्ण
	pdata->clk = clk;

	अगर (pdata->phy_mode == FSL_USB2_PHY_UTMI_WIDE) अणु
		u32 reg = 0;

		अगर (pdata->invert_drvvbus)
			reg |= GC_PPP;

		अगर (pdata->invert_pwr_fault)
			reg |= GC_PFP;

		out_be32(pdata->regs + ISIPHYCTRL, PHYCTRL_PHYE | PHYCTRL_PXE);
		out_be32(pdata->regs + USBGENCTRL, reg);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fsl_usb2_mpc5121_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_usb2_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	pdata->regs = शून्य;

	अगर (pdata->clk)
		clk_disable_unprepare(pdata->clk);
पूर्ण

अटल काष्ठा fsl_usb2_platक्रमm_data fsl_usb2_mpc5121_pd = अणु
	.big_endian_desc = 1,
	.big_endian_mmio = 1,
	.es = 1,
	.have_sysअगर_regs = 0,
	.le_setup_buf = 1,
	.init = fsl_usb2_mpc5121_init,
	.निकास = fsl_usb2_mpc5121_निकास,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PPC_MPC512x */

अटल काष्ठा fsl_usb2_platक्रमm_data fsl_usb2_mpc8xxx_pd = अणु
	.have_sysअगर_regs = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_usb2_mph_dr_of_match[] = अणु
	अणु .compatible = "fsl-usb2-mph", .data = &fsl_usb2_mpc8xxx_pd, पूर्ण,
	अणु .compatible = "fsl-usb2-dr", .data = &fsl_usb2_mpc8xxx_pd, पूर्ण,
#अगर_घोषित CONFIG_PPC_MPC512x
	अणु .compatible = "fsl,mpc5121-usb2-dr", .data = &fsl_usb2_mpc5121_pd, पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_usb2_mph_dr_of_match);

अटल काष्ठा platक्रमm_driver fsl_usb2_mph_dr_driver = अणु
	.driver = अणु
		.name = "fsl-usb2-mph-dr",
		.of_match_table = fsl_usb2_mph_dr_of_match,
	पूर्ण,
	.probe	= fsl_usb2_mph_dr_of_probe,
	.हटाओ	= fsl_usb2_mph_dr_of_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsl_usb2_mph_dr_driver);

MODULE_DESCRIPTION("FSL MPH DR OF devices driver");
MODULE_AUTHOR("Anatolij Gustschin <agust@denx.de>");
MODULE_LICENSE("GPL");
