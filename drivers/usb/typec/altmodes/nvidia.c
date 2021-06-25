<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 NVIDIA Corporation. All rights reserved.
 *
 * NVIDIA USB Type-C Alt Mode Driver
 */
#समावेश <linux/module.h>
#समावेश <linux/usb/typec_alपंचांगode.h>
#समावेश <linux/usb/typec_dp.h>
#समावेश "displayport.h"

अटल पूर्णांक nvidia_alपंचांगode_probe(काष्ठा typec_alपंचांगode *alt)
अणु
	अगर (alt->svid == USB_TYPEC_NVIDIA_VLINK_SID)
		वापस dp_alपंचांगode_probe(alt);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण

अटल व्योम nvidia_alपंचांगode_हटाओ(काष्ठा typec_alपंचांगode *alt)
अणु
	अगर (alt->svid == USB_TYPEC_NVIDIA_VLINK_SID)
		dp_alपंचांगode_हटाओ(alt);
पूर्ण

अटल स्थिर काष्ठा typec_device_id nvidia_typec_id[] = अणु
	अणु USB_TYPEC_NVIDIA_VLINK_SID, TYPEC_ANY_MODE पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(typec, nvidia_typec_id);

अटल काष्ठा typec_alपंचांगode_driver nvidia_alपंचांगode_driver = अणु
	.id_table = nvidia_typec_id,
	.probe = nvidia_alपंचांगode_probe,
	.हटाओ = nvidia_alपंचांगode_हटाओ,
	.driver = अणु
		.name = "typec_nvidia",
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;
module_typec_alपंचांगode_driver(nvidia_alपंचांगode_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("NVIDIA USB Type-C Alt Mode Driver");
