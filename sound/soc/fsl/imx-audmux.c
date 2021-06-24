<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2012 Freescale Semiconductor, Inc.
// Copyright 2012 Linaro Ltd.
// Copyright 2009 Pengutronix, Sascha Hauer <s.hauer@pengutronix.de>
//
// Initial development of this code was funded by
// Phytec Messtechnik GmbH, https://www.phytec.de

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "imx-audmux.h"

#घोषणा DRIVER_NAME "imx-audmux"

अटल काष्ठा clk *audmux_clk;
अटल व्योम __iomem *audmux_base;
अटल u32 *regcache;
अटल u32 reg_max;

#घोषणा IMX_AUDMUX_V2_PTCR(x)		((x) * 8)
#घोषणा IMX_AUDMUX_V2_PDCR(x)		((x) * 8 + 4)

#अगर_घोषित CONFIG_DEBUG_FS
अटल काष्ठा dentry *audmux_debugfs_root;

/* There is an annoying discontinuity in the SSI numbering with regard
 * to the Linux number of the devices */
अटल स्थिर अक्षर *audmux_port_string(पूर्णांक port)
अणु
	चयन (port) अणु
	हाल MX31_AUDMUX_PORT1_SSI0:
		वापस "imx-ssi.0";
	हाल MX31_AUDMUX_PORT2_SSI1:
		वापस "imx-ssi.1";
	हाल MX31_AUDMUX_PORT3_SSI_PINS_3:
		वापस "SSI3";
	हाल MX31_AUDMUX_PORT4_SSI_PINS_4:
		वापस "SSI4";
	हाल MX31_AUDMUX_PORT5_SSI_PINS_5:
		वापस "SSI5";
	हाल MX31_AUDMUX_PORT6_SSI_PINS_6:
		वापस "SSI6";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल sमाप_प्रकार audmux_पढ़ो_file(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार ret;
	अक्षर *buf;
	uपूर्णांकptr_t port = (uपूर्णांकptr_t)file->निजी_data;
	u32 pdcr, ptcr;

	अगर (audmux_clk) अणु
		ret = clk_prepare_enable(audmux_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ptcr = पढ़ोl(audmux_base + IMX_AUDMUX_V2_PTCR(port));
	pdcr = पढ़ोl(audmux_base + IMX_AUDMUX_V2_PDCR(port));

	अगर (audmux_clk)
		clk_disable_unprepare(audmux_clk);

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = scnम_लिखो(buf, PAGE_SIZE, "PDCR: %08x\nPTCR: %08x\n",
		       pdcr, ptcr);

	अगर (ptcr & IMX_AUDMUX_V2_PTCR_TFSसूची)
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
				"TxFS output from %s, ",
				audmux_port_string((ptcr >> 27) & 0x7));
	अन्यथा
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
				"TxFS input, ");

	अगर (ptcr & IMX_AUDMUX_V2_PTCR_TCLKसूची)
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
				"TxClk output from %s",
				audmux_port_string((ptcr >> 22) & 0x7));
	अन्यथा
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
				"TxClk input");

	ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "\n");

	अगर (ptcr & IMX_AUDMUX_V2_PTCR_SYN) अणु
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
				"Port is symmetric");
	पूर्ण अन्यथा अणु
		अगर (ptcr & IMX_AUDMUX_V2_PTCR_RFSसूची)
			ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
					"RxFS output from %s, ",
					audmux_port_string((ptcr >> 17) & 0x7));
		अन्यथा
			ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
					"RxFS input, ");

		अगर (ptcr & IMX_AUDMUX_V2_PTCR_RCLKसूची)
			ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
					"RxClk output from %s",
					audmux_port_string((ptcr >> 12) & 0x7));
		अन्यथा
			ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
					"RxClk input");
	पूर्ण

	ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
			"\nData received from %s\n",
			audmux_port_string((pdcr >> 13) & 0x7));

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, ret);

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations audmux_debugfs_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = audmux_पढ़ो_file,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम audmux_debugfs_init(व्योम)
अणु
	uपूर्णांकptr_t i;
	अक्षर buf[20];

	audmux_debugfs_root = debugfs_create_dir("audmux", शून्य);

	क्रम (i = 0; i < MX31_AUDMUX_PORT7_SSI_PINS_7 + 1; i++) अणु
		snम_लिखो(buf, माप(buf), "ssi%lu", i);
		debugfs_create_file(buf, 0444, audmux_debugfs_root,
				    (व्योम *)i, &audmux_debugfs_fops);
	पूर्ण
पूर्ण

अटल व्योम audmux_debugfs_हटाओ(व्योम)
अणु
	debugfs_हटाओ_recursive(audmux_debugfs_root);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम audmux_debugfs_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम audmux_debugfs_हटाओ(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल क्रमागत imx_audmux_type अणु
	IMX21_AUDMUX,
	IMX31_AUDMUX,
पूर्ण audmux_type;

अटल स्थिर काष्ठा of_device_id imx_audmux_dt_ids[] = अणु
	अणु .compatible = "fsl,imx21-audmux", .data = (व्योम *)IMX21_AUDMUX, पूर्ण,
	अणु .compatible = "fsl,imx31-audmux", .data = (व्योम *)IMX31_AUDMUX, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_audmux_dt_ids);

अटल स्थिर uपूर्णांक8_t port_mapping[] = अणु
	0x0, 0x4, 0x8, 0x10, 0x14, 0x1c,
पूर्ण;

पूर्णांक imx_audmux_v1_configure_port(अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक pcr)
अणु
	अगर (audmux_type != IMX21_AUDMUX)
		वापस -EINVAL;

	अगर (!audmux_base)
		वापस -ENOSYS;

	अगर (port >= ARRAY_SIZE(port_mapping))
		वापस -EINVAL;

	ग_लिखोl(pcr, audmux_base + port_mapping[port]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_audmux_v1_configure_port);

पूर्णांक imx_audmux_v2_configure_port(अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक ptcr,
		अचिन्हित पूर्णांक pdcr)
अणु
	पूर्णांक ret;

	अगर (audmux_type != IMX31_AUDMUX)
		वापस -EINVAL;

	अगर (!audmux_base)
		वापस -ENOSYS;

	अगर (audmux_clk) अणु
		ret = clk_prepare_enable(audmux_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ग_लिखोl(ptcr, audmux_base + IMX_AUDMUX_V2_PTCR(port));
	ग_लिखोl(pdcr, audmux_base + IMX_AUDMUX_V2_PDCR(port));

	अगर (audmux_clk)
		clk_disable_unprepare(audmux_clk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_audmux_v2_configure_port);

अटल पूर्णांक imx_audmux_parse_dt_शेषs(काष्ठा platक्रमm_device *pdev,
		काष्ठा device_node *of_node)
अणु
	काष्ठा device_node *child;

	क्रम_each_available_child_of_node(of_node, child) अणु
		अचिन्हित पूर्णांक port;
		अचिन्हित पूर्णांक ptcr = 0;
		अचिन्हित पूर्णांक pdcr = 0;
		अचिन्हित पूर्णांक pcr = 0;
		अचिन्हित पूर्णांक val;
		पूर्णांक ret;
		पूर्णांक i = 0;

		ret = of_property_पढ़ो_u32(child, "fsl,audmux-port", &port);
		अगर (ret) अणु
			dev_warn(&pdev->dev, "Failed to get fsl,audmux-port of child node \"%pOF\"\n",
					child);
			जारी;
		पूर्ण
		अगर (!of_property_पढ़ो_bool(child, "fsl,port-config")) अणु
			dev_warn(&pdev->dev, "child node \"%pOF\" does not have property fsl,port-config\n",
					child);
			जारी;
		पूर्ण

		क्रम (i = 0; (ret = of_property_पढ़ो_u32_index(child,
					"fsl,port-config", i, &val)) == 0;
				++i) अणु
			अगर (audmux_type == IMX31_AUDMUX) अणु
				अगर (i % 2)
					pdcr |= val;
				अन्यथा
					ptcr |= val;
			पूर्ण अन्यथा अणु
				pcr |= val;
			पूर्ण
		पूर्ण

		अगर (ret != -EOVERFLOW) अणु
			dev_err(&pdev->dev, "Failed to read u32 at index %d of child %pOF\n",
					i, child);
			जारी;
		पूर्ण

		अगर (audmux_type == IMX31_AUDMUX) अणु
			अगर (i % 2) अणु
				dev_err(&pdev->dev, "One pdcr value is missing in child node %pOF\n",
						child);
				जारी;
			पूर्ण
			imx_audmux_v2_configure_port(port, ptcr, pdcr);
		पूर्ण अन्यथा अणु
			imx_audmux_v1_configure_port(port, pcr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_audmux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	audmux_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(audmux_base))
		वापस PTR_ERR(audmux_base);

	audmux_clk = devm_clk_get(&pdev->dev, "audmux");
	अगर (IS_ERR(audmux_clk)) अणु
		dev_dbg(&pdev->dev, "cannot get clock: %ld\n",
				PTR_ERR(audmux_clk));
		audmux_clk = शून्य;
	पूर्ण

	audmux_type = (क्रमागत imx_audmux_type)of_device_get_match_data(&pdev->dev);

	चयन (audmux_type) अणु
	हाल IMX31_AUDMUX:
		audmux_debugfs_init();
		reg_max = 14;
		अवरोध;
	हाल IMX21_AUDMUX:
		reg_max = 6;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "unsupported version!\n");
		वापस -EINVAL;
	पूर्ण

	regcache = devm_kzalloc(&pdev->dev, माप(u32) * reg_max, GFP_KERNEL);
	अगर (!regcache)
		वापस -ENOMEM;

	imx_audmux_parse_dt_शेषs(pdev, pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_audmux_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (audmux_type == IMX31_AUDMUX)
		audmux_debugfs_हटाओ();

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक imx_audmux_suspend(काष्ठा device *dev)
अणु
	पूर्णांक i;

	clk_prepare_enable(audmux_clk);

	क्रम (i = 0; i < reg_max; i++)
		regcache[i] = पढ़ोl(audmux_base + i * 4);

	clk_disable_unprepare(audmux_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_audmux_resume(काष्ठा device *dev)
अणु
	पूर्णांक i;

	clk_prepare_enable(audmux_clk);

	क्रम (i = 0; i < reg_max; i++)
		ग_लिखोl(regcache[i], audmux_base + i * 4);

	clk_disable_unprepare(audmux_clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops imx_audmux_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(imx_audmux_suspend, imx_audmux_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_audmux_driver = अणु
	.probe		= imx_audmux_probe,
	.हटाओ		= imx_audmux_हटाओ,
	.driver	= अणु
		.name	= DRIVER_NAME,
		.pm = &imx_audmux_pm,
		.of_match_table = imx_audmux_dt_ids,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init imx_audmux_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&imx_audmux_driver);
पूर्ण
subsys_initcall(imx_audmux_init);

अटल व्योम __निकास imx_audmux_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&imx_audmux_driver);
पूर्ण
module_निकास(imx_audmux_निकास);

MODULE_DESCRIPTION("Freescale i.MX AUDMUX driver");
MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
