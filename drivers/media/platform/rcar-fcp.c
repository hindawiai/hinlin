<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rcar-fcp.c  --  R-Car Frame Compression Processor Driver
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश <media/rcar-fcp.h>

काष्ठा rcar_fcp_device अणु
	काष्ठा list_head list;
	काष्ठा device *dev;
पूर्ण;

अटल LIST_HEAD(fcp_devices);
अटल DEFINE_MUTEX(fcp_lock);

/* -----------------------------------------------------------------------------
 * Public API
 */

/**
 * rcar_fcp_get - Find and acquire a reference to an FCP instance
 * @np: Device node of the FCP instance
 *
 * Search the list of रेजिस्टरed FCP instances क्रम the instance corresponding to
 * the given device node.
 *
 * Return a poपूर्णांकer to the FCP instance, or an ERR_PTR अगर the instance can't be
 * found.
 */
काष्ठा rcar_fcp_device *rcar_fcp_get(स्थिर काष्ठा device_node *np)
अणु
	काष्ठा rcar_fcp_device *fcp;

	mutex_lock(&fcp_lock);

	list_क्रम_each_entry(fcp, &fcp_devices, list) अणु
		अगर (fcp->dev->of_node != np)
			जारी;

		get_device(fcp->dev);
		जाओ करोne;
	पूर्ण

	fcp = ERR_PTR(-EPROBE_DEFER);

करोne:
	mutex_unlock(&fcp_lock);
	वापस fcp;
पूर्ण
EXPORT_SYMBOL_GPL(rcar_fcp_get);

/**
 * rcar_fcp_put - Release a reference to an FCP instance
 * @fcp: The FCP instance
 *
 * Release the FCP instance acquired by a call to rcar_fcp_get().
 */
व्योम rcar_fcp_put(काष्ठा rcar_fcp_device *fcp)
अणु
	अगर (fcp)
		put_device(fcp->dev);
पूर्ण
EXPORT_SYMBOL_GPL(rcar_fcp_put);

काष्ठा device *rcar_fcp_get_device(काष्ठा rcar_fcp_device *fcp)
अणु
	वापस fcp->dev;
पूर्ण
EXPORT_SYMBOL_GPL(rcar_fcp_get_device);

/**
 * rcar_fcp_enable - Enable an FCP
 * @fcp: The FCP instance
 *
 * Beक्रमe any memory access through an FCP is perक्रमmed by a module, the FCP
 * must be enabled by a call to this function. The enable calls are reference
 * counted, each successful call must be followed by one rcar_fcp_disable()
 * call when no more memory transfer can occur through the FCP.
 *
 * Return 0 on success or a negative error code अगर an error occurs. The enable
 * reference count isn't increased when this function वापसs an error.
 */
पूर्णांक rcar_fcp_enable(काष्ठा rcar_fcp_device *fcp)
अणु
	पूर्णांक ret;

	अगर (!fcp)
		वापस 0;

	ret = pm_runसमय_get_sync(fcp->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(fcp->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rcar_fcp_enable);

/**
 * rcar_fcp_disable - Disable an FCP
 * @fcp: The FCP instance
 *
 * This function is the counterpart of rcar_fcp_enable(). As enable calls are
 * reference counted a disable call may not disable the FCP synchronously.
 */
व्योम rcar_fcp_disable(काष्ठा rcar_fcp_device *fcp)
अणु
	अगर (fcp)
		pm_runसमय_put(fcp->dev);
पूर्ण
EXPORT_SYMBOL_GPL(rcar_fcp_disable);

/* -----------------------------------------------------------------------------
 * Platक्रमm Driver
 */

अटल पूर्णांक rcar_fcp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_fcp_device *fcp;

	fcp = devm_kzalloc(&pdev->dev, माप(*fcp), GFP_KERNEL);
	अगर (fcp == शून्य)
		वापस -ENOMEM;

	fcp->dev = &pdev->dev;

	dma_set_max_seg_size(fcp->dev, अच_पूर्णांक_उच्च);

	pm_runसमय_enable(&pdev->dev);

	mutex_lock(&fcp_lock);
	list_add_tail(&fcp->list, &fcp_devices);
	mutex_unlock(&fcp_lock);

	platक्रमm_set_drvdata(pdev, fcp);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_fcp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_fcp_device *fcp = platक्रमm_get_drvdata(pdev);

	mutex_lock(&fcp_lock);
	list_del(&fcp->list);
	mutex_unlock(&fcp_lock);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rcar_fcp_of_match[] = अणु
	अणु .compatible = "renesas,fcpf" पूर्ण,
	अणु .compatible = "renesas,fcpv" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_fcp_of_match);

अटल काष्ठा platक्रमm_driver rcar_fcp_platक्रमm_driver = अणु
	.probe		= rcar_fcp_probe,
	.हटाओ		= rcar_fcp_हटाओ,
	.driver		= अणु
		.name	= "rcar-fcp",
		.of_match_table = rcar_fcp_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rcar_fcp_platक्रमm_driver);

MODULE_ALIAS("rcar-fcp");
MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Renesas FCP Driver");
MODULE_LICENSE("GPL");
