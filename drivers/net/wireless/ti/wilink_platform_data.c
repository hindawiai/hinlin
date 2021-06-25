<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2010-2011 Texas Instruments, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/wl12xx.h>

अटल काष्ठा wl1251_platक्रमm_data *wl1251_platक्रमm_data;

पूर्णांक __init wl1251_set_platक्रमm_data(स्थिर काष्ठा wl1251_platक्रमm_data *data)
अणु
	अगर (wl1251_platक्रमm_data)
		वापस -EBUSY;
	अगर (!data)
		वापस -EINVAL;

	wl1251_platक्रमm_data = kmemdup(data, माप(*data), GFP_KERNEL);
	अगर (!wl1251_platक्रमm_data)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

काष्ठा wl1251_platक्रमm_data *wl1251_get_platक्रमm_data(व्योम)
अणु
	अगर (!wl1251_platक्रमm_data)
		वापस ERR_PTR(-ENODEV);

	वापस wl1251_platक्रमm_data;
पूर्ण
EXPORT_SYMBOL(wl1251_get_platक्रमm_data);
