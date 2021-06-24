<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2020 - All Rights Reserved
 */
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/rpmsg/ns.h>
#समावेश <linux/slab.h>

#समावेश "rpmsg_internal.h"

/**
 * rpmsg_ns_रेजिस्टर_device() - रेजिस्टर name service device based on rpdev
 * @rpdev: prepared rpdev to be used क्रम creating endpoपूर्णांकs
 *
 * This function wraps rpmsg_रेजिस्टर_device() preparing the rpdev क्रम use as
 * basis क्रम the rpmsg name service device.
 */
पूर्णांक rpmsg_ns_रेजिस्टर_device(काष्ठा rpmsg_device *rpdev)
अणु
	म_नकल(rpdev->id.name, "rpmsg_ns");
	rpdev->driver_override = "rpmsg_ns";
	rpdev->src = RPMSG_NS_ADDR;
	rpdev->dst = RPMSG_NS_ADDR;

	वापस rpmsg_रेजिस्टर_device(rpdev);
पूर्ण
EXPORT_SYMBOL(rpmsg_ns_रेजिस्टर_device);

/* invoked when a name service announcement arrives */
अटल पूर्णांक rpmsg_ns_cb(काष्ठा rpmsg_device *rpdev, व्योम *data, पूर्णांक len,
		       व्योम *priv, u32 src)
अणु
	काष्ठा rpmsg_ns_msg *msg = data;
	काष्ठा rpmsg_device *newch;
	काष्ठा rpmsg_channel_info chinfo;
	काष्ठा device *dev = rpdev->dev.parent;
	पूर्णांक ret;

#अगर defined(CONFIG_DYNAMIC_DEBUG)
	dynamic_hex_dump("NS announcement: ", DUMP_PREFIX_NONE, 16, 1,
			 data, len, true);
#पूर्ण_अगर

	अगर (len != माप(*msg)) अणु
		dev_err(dev, "malformed ns msg (%d)\n", len);
		वापस -EINVAL;
	पूर्ण

	/* करोn't trust the remote processor क्रम null terminating the name */
	msg->name[RPMSG_NAME_SIZE - 1] = '\0';

	म_नकलन(chinfo.name, msg->name, माप(chinfo.name));
	chinfo.src = RPMSG_ADDR_ANY;
	chinfo.dst = rpmsg32_to_cpu(rpdev, msg->addr);

	dev_info(dev, "%sing channel %s addr 0x%x\n",
		 rpmsg32_to_cpu(rpdev, msg->flags) & RPMSG_NS_DESTROY ?
		 "destroy" : "creat", msg->name, chinfo.dst);

	अगर (rpmsg32_to_cpu(rpdev, msg->flags) & RPMSG_NS_DESTROY) अणु
		ret = rpmsg_release_channel(rpdev, &chinfo);
		अगर (ret)
			dev_err(dev, "rpmsg_destroy_channel failed: %d\n", ret);
	पूर्ण अन्यथा अणु
		newch = rpmsg_create_channel(rpdev, &chinfo);
		अगर (!newch)
			dev_err(dev, "rpmsg_create_channel failed\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rpmsg_ns_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा rpmsg_endpoपूर्णांक *ns_ept;
	काष्ठा rpmsg_channel_info ns_chinfo = अणु
		.src = RPMSG_NS_ADDR,
		.dst = RPMSG_NS_ADDR,
		.name = "name_service",
	पूर्ण;

	/*
	 * Create the NS announcement service endpoपूर्णांक associated to the RPMsg
	 * device. The endpoपूर्णांक will be स्वतःmatically destroyed when the RPMsg
	 * device will be deleted.
	 */
	ns_ept = rpmsg_create_ept(rpdev, rpmsg_ns_cb, शून्य, ns_chinfo);
	अगर (!ns_ept) अणु
		dev_err(&rpdev->dev, "failed to create the ns ept\n");
		वापस -ENOMEM;
	पूर्ण
	rpdev->ept = ns_ept;

	वापस 0;
पूर्ण

अटल काष्ठा rpmsg_driver rpmsg_ns_driver = अणु
	.drv.name = KBUILD_MODNAME,
	.probe = rpmsg_ns_probe,
पूर्ण;

अटल पूर्णांक rpmsg_ns_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_rpmsg_driver(&rpmsg_ns_driver);
	अगर (ret < 0)
		pr_err("%s: Failed to register rpmsg driver\n", __func__);

	वापस ret;
पूर्ण
postcore_initcall(rpmsg_ns_init);

अटल व्योम rpmsg_ns_निकास(व्योम)
अणु
	unरेजिस्टर_rpmsg_driver(&rpmsg_ns_driver);
पूर्ण
module_निकास(rpmsg_ns_निकास);

MODULE_DESCRIPTION("Name service announcement rpmsg driver");
MODULE_AUTHOR("Arnaud Pouliquen <arnaud.pouliquen@st.com>");
MODULE_ALIAS("rpmsg:" KBUILD_MODNAME);
MODULE_LICENSE("GPL v2");
