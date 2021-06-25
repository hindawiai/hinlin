<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright(c) 2020 Intel Corporation. All rights reserved. */
#समावेश <linux/device.h>
#समावेश <linux/module.h>

/**
 * DOC: cxl bus
 *
 * The CXL bus provides namespace क्रम control devices and a rendezvous
 * poपूर्णांक क्रम cross-device पूर्णांकerleave coordination.
 */
काष्ठा bus_type cxl_bus_type = अणु
	.name = "cxl",
पूर्ण;
EXPORT_SYMBOL_GPL(cxl_bus_type);

अटल __init पूर्णांक cxl_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&cxl_bus_type);
पूर्ण

अटल व्योम cxl_bus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&cxl_bus_type);
पूर्ण

module_init(cxl_bus_init);
module_निकास(cxl_bus_निकास);
MODULE_LICENSE("GPL v2");
