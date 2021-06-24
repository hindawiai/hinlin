<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/misc/xillybus_of.c
 *
 * Copyright 2011 Xillybus Ltd, http://xillybus.com
 *
 * Driver क्रम the Xillybus FPGA/host framework using Open Firmware.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/err.h>
#समावेश "xillybus.h"

MODULE_DESCRIPTION("Xillybus driver for Open Firmware");
MODULE_AUTHOR("Eli Billauer, Xillybus Ltd.");
MODULE_VERSION("1.06");
MODULE_ALIAS("xillybus_of");
MODULE_LICENSE("GPL v2");

अटल स्थिर अक्षर xillyname[] = "xillybus_of";

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id xillybus_of_match[] = अणु
	अणु .compatible = "xillybus,xillybus-1.00.a", पूर्ण,
	अणु .compatible = "xlnx,xillybus-1.00.a", पूर्ण, /* Deprecated */
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, xillybus_of_match);

अटल व्योम xilly_dma_sync_single_क्रम_cpu_of(काष्ठा xilly_endpoपूर्णांक *ep,
					     dma_addr_t dma_handle,
					     माप_प्रकार size,
					     पूर्णांक direction)
अणु
	dma_sync_single_क्रम_cpu(ep->dev, dma_handle, size, direction);
पूर्ण

अटल व्योम xilly_dma_sync_single_क्रम_device_of(काष्ठा xilly_endpoपूर्णांक *ep,
						dma_addr_t dma_handle,
						माप_प्रकार size,
						पूर्णांक direction)
अणु
	dma_sync_single_क्रम_device(ep->dev, dma_handle, size, direction);
पूर्ण

अटल व्योम xilly_dma_sync_single_nop(काष्ठा xilly_endpoपूर्णांक *ep,
				      dma_addr_t dma_handle,
				      माप_प्रकार size,
				      पूर्णांक direction)
अणु
पूर्ण

अटल व्योम xilly_of_unmap(व्योम *ptr)
अणु
	काष्ठा xilly_mapping *data = ptr;

	dma_unmap_single(data->device, data->dma_addr,
			 data->size, data->direction);

	kमुक्त(ptr);
पूर्ण

अटल पूर्णांक xilly_map_single_of(काष्ठा xilly_endpoपूर्णांक *ep,
			       व्योम *ptr,
			       माप_प्रकार size,
			       पूर्णांक direction,
			       dma_addr_t *ret_dma_handle
	)
अणु
	dma_addr_t addr;
	काष्ठा xilly_mapping *this;

	this = kzalloc(माप(*this), GFP_KERNEL);
	अगर (!this)
		वापस -ENOMEM;

	addr = dma_map_single(ep->dev, ptr, size, direction);

	अगर (dma_mapping_error(ep->dev, addr)) अणु
		kमुक्त(this);
		वापस -ENODEV;
	पूर्ण

	this->device = ep->dev;
	this->dma_addr = addr;
	this->size = size;
	this->direction = direction;

	*ret_dma_handle = addr;

	वापस devm_add_action_or_reset(ep->dev, xilly_of_unmap, this);
पूर्ण

अटल काष्ठा xilly_endpoपूर्णांक_hardware of_hw = अणु
	.owner = THIS_MODULE,
	.hw_sync_sgl_क्रम_cpu = xilly_dma_sync_single_क्रम_cpu_of,
	.hw_sync_sgl_क्रम_device = xilly_dma_sync_single_क्रम_device_of,
	.map_single = xilly_map_single_of,
पूर्ण;

अटल काष्ठा xilly_endpoपूर्णांक_hardware of_hw_coherent = अणु
	.owner = THIS_MODULE,
	.hw_sync_sgl_क्रम_cpu = xilly_dma_sync_single_nop,
	.hw_sync_sgl_क्रम_device = xilly_dma_sync_single_nop,
	.map_single = xilly_map_single_of,
पूर्ण;

अटल पूर्णांक xilly_drv_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device *dev = &op->dev;
	काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक;
	पूर्णांक rc;
	पूर्णांक irq;
	काष्ठा xilly_endpoपूर्णांक_hardware *ephw = &of_hw;

	अगर (of_property_पढ़ो_bool(dev->of_node, "dma-coherent"))
		ephw = &of_hw_coherent;

	endpoपूर्णांक = xillybus_init_endpoपूर्णांक(शून्य, dev, ephw);

	अगर (!endpoपूर्णांक)
		वापस -ENOMEM;

	dev_set_drvdata(dev, endpoपूर्णांक);

	endpoपूर्णांक->रेजिस्टरs = devm_platक्रमm_ioremap_resource(op, 0);
	अगर (IS_ERR(endpoपूर्णांक->रेजिस्टरs))
		वापस PTR_ERR(endpoपूर्णांक->रेजिस्टरs);

	irq = platक्रमm_get_irq(op, 0);

	rc = devm_request_irq(dev, irq, xillybus_isr, 0, xillyname, endpoपूर्णांक);

	अगर (rc) अणु
		dev_err(endpoपूर्णांक->dev,
			"Failed to register IRQ handler. Aborting.\n");
		वापस -ENODEV;
	पूर्ण

	वापस xillybus_endpoपूर्णांक_discovery(endpoपूर्णांक);
पूर्ण

अटल पूर्णांक xilly_drv_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device *dev = &op->dev;
	काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक = dev_get_drvdata(dev);

	xillybus_endpoपूर्णांक_हटाओ(endpoपूर्णांक);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xillybus_platक्रमm_driver = अणु
	.probe = xilly_drv_probe,
	.हटाओ = xilly_drv_हटाओ,
	.driver = अणु
		.name = xillyname,
		.of_match_table = xillybus_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xillybus_platक्रमm_driver);
