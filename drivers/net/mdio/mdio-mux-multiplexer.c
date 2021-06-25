<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* MDIO bus multiplexer using kernel multiplexer subप्रणाली
 *
 * Copyright 2019 NXP
 */

#समावेश <linux/mdio-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा mdio_mux_multiplexer_state अणु
	काष्ठा mux_control *muxc;
	bool करो_deselect;
	व्योम *mux_handle;
पूर्ण;

/**
 * mdio_mux_multiplexer_चयन_fn - This function is called by the mdio-mux
 *                                  layer when it thinks the mdio bus
 *                                  multiplexer needs to चयन.
 * @current_child:  current value of the mux रेजिस्टर.
 * @desired_child: value of the 'reg' property of the target child MDIO node.
 * @data: Private data used by this चयन_fn passed to mdio_mux_init function
 *        via mdio_mux_init(.., .., .., .., data, ..).
 *
 * The first समय this function is called, current_child == -1.
 * If current_child == desired_child, then the mux is alपढ़ोy set to the
 * correct bus.
 */
अटल पूर्णांक mdio_mux_multiplexer_चयन_fn(पूर्णांक current_child, पूर्णांक desired_child,
					  व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mdio_mux_multiplexer_state *s;
	पूर्णांक ret = 0;

	pdev = (काष्ठा platक्रमm_device *)data;
	s = platक्रमm_get_drvdata(pdev);

	अगर (!(current_child ^ desired_child))
		वापस 0;

	अगर (s->करो_deselect)
		ret = mux_control_deselect(s->muxc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "mux_control_deselect failed in %s: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret =  mux_control_select(s->muxc, desired_child);
	अगर (!ret) अणु
		dev_dbg(&pdev->dev, "%s %d -> %d\n", __func__, current_child,
			desired_child);
		s->करो_deselect = true;
	पूर्ण अन्यथा अणु
		s->करो_deselect = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mdio_mux_multiplexer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mdio_mux_multiplexer_state *s;
	पूर्णांक ret = 0;

	s = devm_kzalloc(&pdev->dev, माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	s->muxc = devm_mux_control_get(dev, शून्य);
	अगर (IS_ERR(s->muxc)) अणु
		ret = PTR_ERR(s->muxc);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get mux: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, s);

	ret = mdio_mux_init(&pdev->dev, pdev->dev.of_node,
			    mdio_mux_multiplexer_चयन_fn, &s->mux_handle,
			    pdev, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक mdio_mux_multiplexer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mdio_mux_multiplexer_state *s = platक्रमm_get_drvdata(pdev);

	mdio_mux_uninit(s->mux_handle);

	अगर (s->करो_deselect)
		mux_control_deselect(s->muxc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mdio_mux_multiplexer_match[] = अणु
	अणु .compatible = "mdio-mux-multiplexer", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mdio_mux_multiplexer_match);

अटल काष्ठा platक्रमm_driver mdio_mux_multiplexer_driver = अणु
	.driver = अणु
		.name		= "mdio-mux-multiplexer",
		.of_match_table	= mdio_mux_multiplexer_match,
	पूर्ण,
	.probe		= mdio_mux_multiplexer_probe,
	.हटाओ		= mdio_mux_multiplexer_हटाओ,
पूर्ण;

module_platक्रमm_driver(mdio_mux_multiplexer_driver);

MODULE_DESCRIPTION("MDIO bus multiplexer using kernel multiplexer subsystem");
MODULE_AUTHOR("Pankaj Bansal <pankaj.bansal@nxp.com>");
MODULE_LICENSE("GPL");
