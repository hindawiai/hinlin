<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Defines पूर्णांकerfaces क्रम पूर्णांकeracting with the Raspberry Pi firmware's
 * property channel.
 *
 * Copyright तऊ 2015 Broadcom
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/kref.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <soc/bcm2835/raspberrypi-firmware.h>

#घोषणा MBOX_MSG(chan, data28)		(((data28) & ~0xf) | ((chan) & 0xf))
#घोषणा MBOX_CHAN(msg)			((msg) & 0xf)
#घोषणा MBOX_DATA28(msg)		((msg) & ~0xf)
#घोषणा MBOX_CHAN_PROPERTY		8

अटल काष्ठा platक्रमm_device *rpi_hwmon;
अटल काष्ठा platक्रमm_device *rpi_clk;

काष्ठा rpi_firmware अणु
	काष्ठा mbox_client cl;
	काष्ठा mbox_chan *chan; /* The property channel. */
	काष्ठा completion c;
	u32 enabled;

	काष्ठा kref consumers;
पूर्ण;

अटल DEFINE_MUTEX(transaction_lock);

अटल व्योम response_callback(काष्ठा mbox_client *cl, व्योम *msg)
अणु
	काष्ठा rpi_firmware *fw = container_of(cl, काष्ठा rpi_firmware, cl);
	complete(&fw->c);
पूर्ण

/*
 * Sends a request to the firmware through the BCM2835 mailbox driver,
 * and synchronously रुकोs क्रम the reply.
 */
अटल पूर्णांक
rpi_firmware_transaction(काष्ठा rpi_firmware *fw, u32 chan, u32 data)
अणु
	u32 message = MBOX_MSG(chan, data);
	पूर्णांक ret;

	WARN_ON(data & 0xf);

	mutex_lock(&transaction_lock);
	reinit_completion(&fw->c);
	ret = mbox_send_message(fw->chan, &message);
	अगर (ret >= 0) अणु
		अगर (रुको_क्रम_completion_समयout(&fw->c, HZ)) अणु
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = -ETIMEDOUT;
			WARN_ONCE(1, "Firmware transaction timeout");
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(fw->cl.dev, "mbox_send_message returned %d\n", ret);
	पूर्ण
	mutex_unlock(&transaction_lock);

	वापस ret;
पूर्ण

/**
 * rpi_firmware_property_list - Submit firmware property list
 * @fw:		Poपूर्णांकer to firmware काष्ठाure from rpi_firmware_get().
 * @data:	Buffer holding tags.
 * @tag_size:	Size of tags buffer.
 *
 * Submits a set of concatenated tags to the VPU firmware through the
 * mailbox property पूर्णांकerface.
 *
 * The buffer header and the ending tag are added by this function and
 * करोn't need to be supplied, just the actual tags क्रम your operation.
 * See काष्ठा rpi_firmware_property_tag_header क्रम the per-tag
 * काष्ठाure.
 */
पूर्णांक rpi_firmware_property_list(काष्ठा rpi_firmware *fw,
			       व्योम *data, माप_प्रकार tag_size)
अणु
	माप_प्रकार size = tag_size + 12;
	u32 *buf;
	dma_addr_t bus_addr;
	पूर्णांक ret;

	/* Packets are processed a dword at a समय. */
	अगर (size & 3)
		वापस -EINVAL;

	buf = dma_alloc_coherent(fw->cl.dev, PAGE_ALIGN(size), &bus_addr,
				 GFP_ATOMIC);
	अगर (!buf)
		वापस -ENOMEM;

	/* The firmware will error out without parsing in this हाल. */
	WARN_ON(size >= 1024 * 1024);

	buf[0] = size;
	buf[1] = RPI_FIRMWARE_STATUS_REQUEST;
	स_नकल(&buf[2], data, tag_size);
	buf[size / 4 - 1] = RPI_FIRMWARE_PROPERTY_END;
	wmb();

	ret = rpi_firmware_transaction(fw, MBOX_CHAN_PROPERTY, bus_addr);

	rmb();
	स_नकल(data, &buf[2], tag_size);
	अगर (ret == 0 && buf[1] != RPI_FIRMWARE_STATUS_SUCCESS) अणु
		/*
		 * The tag name here might not be the one causing the
		 * error, अगर there were multiple tags in the request.
		 * But single-tag is the most common, so go with it.
		 */
		dev_err(fw->cl.dev, "Request 0x%08x returned status 0x%08x\n",
			buf[2], buf[1]);
		ret = -EINVAL;
	पूर्ण

	dma_मुक्त_coherent(fw->cl.dev, PAGE_ALIGN(size), buf, bus_addr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpi_firmware_property_list);

/**
 * rpi_firmware_property - Submit single firmware property
 * @fw:		Poपूर्णांकer to firmware काष्ठाure from rpi_firmware_get().
 * @tag:	One of क्रमागत_mbox_property_tag.
 * @tag_data:	Tag data buffer.
 * @buf_size:	Buffer size.
 *
 * Submits a single tag to the VPU firmware through the mailbox
 * property पूर्णांकerface.
 *
 * This is a convenience wrapper around
 * rpi_firmware_property_list() to aव्योम some of the
 * boilerplate in property calls.
 */
पूर्णांक rpi_firmware_property(काष्ठा rpi_firmware *fw,
			  u32 tag, व्योम *tag_data, माप_प्रकार buf_size)
अणु
	काष्ठा rpi_firmware_property_tag_header *header;
	पूर्णांक ret;

	/* Some mailboxes can use over 1k bytes. Rather than checking
	 * size and using stack or kदो_स्मृति depending on requirements,
	 * just use kदो_स्मृति. Mailboxes करोn't get called enough to worry
	 * too much about the समय taken in the allocation.
	 */
	व्योम *data = kदो_स्मृति(माप(*header) + buf_size, GFP_KERNEL);

	अगर (!data)
		वापस -ENOMEM;

	header = data;
	header->tag = tag;
	header->buf_size = buf_size;
	header->req_resp_size = 0;
	स_नकल(data + माप(*header), tag_data, buf_size);

	ret = rpi_firmware_property_list(fw, data, buf_size + माप(*header));

	स_नकल(tag_data, data + माप(*header), buf_size);

	kमुक्त(data);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpi_firmware_property);

अटल व्योम
rpi_firmware_prपूर्णांक_firmware_revision(काष्ठा rpi_firmware *fw)
अणु
	समय64_t date_and_समय;
	u32 packet;
	पूर्णांक ret = rpi_firmware_property(fw,
					RPI_FIRMWARE_GET_FIRMWARE_REVISION,
					&packet, माप(packet));

	अगर (ret)
		वापस;

	/* This is not compatible with y2038 */
	date_and_समय = packet;
	dev_info(fw->cl.dev, "Attached to firmware from %ptT\n", &date_and_समय);
पूर्ण

अटल व्योम
rpi_रेजिस्टर_hwmon_driver(काष्ठा device *dev, काष्ठा rpi_firmware *fw)
अणु
	u32 packet;
	पूर्णांक ret = rpi_firmware_property(fw, RPI_FIRMWARE_GET_THROTTLED,
					&packet, माप(packet));

	अगर (ret)
		वापस;

	rpi_hwmon = platक्रमm_device_रेजिस्टर_data(dev, "raspberrypi-hwmon",
						  -1, शून्य, 0);
पूर्ण

अटल व्योम rpi_रेजिस्टर_clk_driver(काष्ठा device *dev)
अणु
	काष्ठा device_node *firmware;

	/*
	 * Earlier DTs करोn't have a node क्रम the firmware घड़ीs but
	 * rely on us creating a platक्रमm device by hand. If we करो
	 * have a node क्रम the firmware घड़ीs, just bail out here.
	 */
	firmware = of_get_compatible_child(dev->of_node,
					   "raspberrypi,firmware-clocks");
	अगर (firmware) अणु
		of_node_put(firmware);
		वापस;
	पूर्ण

	rpi_clk = platक्रमm_device_रेजिस्टर_data(dev, "raspberrypi-clk",
						-1, शून्य, 0);
पूर्ण

अटल व्योम rpi_firmware_delete(काष्ठा kref *kref)
अणु
	काष्ठा rpi_firmware *fw = container_of(kref, काष्ठा rpi_firmware,
					       consumers);

	mbox_मुक्त_channel(fw->chan);
	kमुक्त(fw);
पूर्ण

व्योम rpi_firmware_put(काष्ठा rpi_firmware *fw)
अणु
	kref_put(&fw->consumers, rpi_firmware_delete);
पूर्ण
EXPORT_SYMBOL_GPL(rpi_firmware_put);

अटल व्योम devm_rpi_firmware_put(व्योम *data)
अणु
	काष्ठा rpi_firmware *fw = data;

	rpi_firmware_put(fw);
पूर्ण

अटल पूर्णांक rpi_firmware_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rpi_firmware *fw;

	/*
	 * Memory will be मुक्तd by rpi_firmware_delete() once all users have
	 * released their firmware handles. Don't use devm_kzalloc() here.
	 */
	fw = kzalloc(माप(*fw), GFP_KERNEL);
	अगर (!fw)
		वापस -ENOMEM;

	fw->cl.dev = dev;
	fw->cl.rx_callback = response_callback;
	fw->cl.tx_block = true;

	fw->chan = mbox_request_channel(&fw->cl, 0);
	अगर (IS_ERR(fw->chan)) अणु
		पूर्णांक ret = PTR_ERR(fw->chan);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get mbox channel: %d\n", ret);
		वापस ret;
	पूर्ण

	init_completion(&fw->c);
	kref_init(&fw->consumers);

	platक्रमm_set_drvdata(pdev, fw);

	rpi_firmware_prपूर्णांक_firmware_revision(fw);
	rpi_रेजिस्टर_hwmon_driver(dev, fw);
	rpi_रेजिस्टर_clk_driver(dev);

	वापस 0;
पूर्ण

अटल व्योम rpi_firmware_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rpi_firmware *fw = platक्रमm_get_drvdata(pdev);

	अगर (!fw)
		वापस;

	rpi_firmware_property(fw, RPI_FIRMWARE_NOTIFY_REBOOT, शून्य, 0);
पूर्ण

अटल पूर्णांक rpi_firmware_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rpi_firmware *fw = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(rpi_hwmon);
	rpi_hwmon = शून्य;
	platक्रमm_device_unरेजिस्टर(rpi_clk);
	rpi_clk = शून्य;

	rpi_firmware_put(fw);

	वापस 0;
पूर्ण

/**
 * rpi_firmware_get - Get poपूर्णांकer to rpi_firmware काष्ठाure.
 * @firmware_node:    Poपूर्णांकer to the firmware Device Tree node.
 *
 * The reference to rpi_firmware has to be released with rpi_firmware_put().
 *
 * Returns शून्य is the firmware device is not पढ़ोy.
 */
काष्ठा rpi_firmware *rpi_firmware_get(काष्ठा device_node *firmware_node)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(firmware_node);
	काष्ठा rpi_firmware *fw;

	अगर (!pdev)
		वापस शून्य;

	fw = platक्रमm_get_drvdata(pdev);
	अगर (!fw)
		वापस शून्य;

	अगर (!kref_get_unless_zero(&fw->consumers))
		वापस शून्य;

	वापस fw;
पूर्ण
EXPORT_SYMBOL_GPL(rpi_firmware_get);

/**
 * devm_rpi_firmware_get - Get poपूर्णांकer to rpi_firmware काष्ठाure.
 * @firmware_node:    Poपूर्णांकer to the firmware Device Tree node.
 *
 * Returns शून्य is the firmware device is not पढ़ोy.
 */
काष्ठा rpi_firmware *devm_rpi_firmware_get(काष्ठा device *dev,
					   काष्ठा device_node *firmware_node)
अणु
	काष्ठा rpi_firmware *fw;

	fw = rpi_firmware_get(firmware_node);
	अगर (!fw)
		वापस शून्य;

	अगर (devm_add_action_or_reset(dev, devm_rpi_firmware_put, fw))
		वापस शून्य;

	वापस fw;
पूर्ण
EXPORT_SYMBOL_GPL(devm_rpi_firmware_get);

अटल स्थिर काष्ठा of_device_id rpi_firmware_of_match[] = अणु
	अणु .compatible = "raspberrypi,bcm2835-firmware", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rpi_firmware_of_match);

अटल काष्ठा platक्रमm_driver rpi_firmware_driver = अणु
	.driver = अणु
		.name = "raspberrypi-firmware",
		.of_match_table = rpi_firmware_of_match,
	पूर्ण,
	.probe		= rpi_firmware_probe,
	.shutकरोwn	= rpi_firmware_shutकरोwn,
	.हटाओ		= rpi_firmware_हटाओ,
पूर्ण;
module_platक्रमm_driver(rpi_firmware_driver);

MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_DESCRIPTION("Raspberry Pi firmware driver");
MODULE_LICENSE("GPL v2");
