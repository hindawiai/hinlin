<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014-2016 Qualcomm Atheros, Inc.
 */

#समावेश <linux/device.h>
#समावेश "wil_platform.h"

पूर्णांक __init wil_platक्रमm_modinit(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम wil_platक्रमm_modनिकास(व्योम)
अणु
पूर्ण

/* wil_platक्रमm_init() - wil6210 platक्रमm module init
 *
 * The function must be called beक्रमe all other functions in this module.
 * It वापसs a handle which is used with the rest of the API
 *
 */
व्योम *wil_platक्रमm_init(काष्ठा device *dev, काष्ठा wil_platक्रमm_ops *ops,
			स्थिर काष्ठा wil_platक्रमm_rops *rops, व्योम *wil_handle)
अणु
	व्योम *handle = ops; /* to वापस some non-शून्य क्रम 'void' impl. */

	अगर (!ops) अणु
		dev_err(dev,
			"Invalid parameter. Cannot init platform module\n");
		वापस शून्य;
	पूर्ण

	/* platक्रमm specअगरic init functions should be called here */

	वापस handle;
पूर्ण
