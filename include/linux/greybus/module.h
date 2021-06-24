<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus Module code
 *
 * Copyright 2016 Google Inc.
 * Copyright 2016 Linaro Ltd.
 */

#अगर_अघोषित __MODULE_H
#घोषणा __MODULE_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>

काष्ठा gb_module अणु
	काष्ठा device dev;
	काष्ठा gb_host_device *hd;

	काष्ठा list_head hd_node;

	u8 module_id;
	माप_प्रकार num_पूर्णांकerfaces;

	bool disconnected;

	काष्ठा gb_पूर्णांकerface *पूर्णांकerfaces[0];
पूर्ण;
#घोषणा to_gb_module(d) container_of(d, काष्ठा gb_module, dev)

काष्ठा gb_module *gb_module_create(काष्ठा gb_host_device *hd, u8 module_id,
				   माप_प्रकार num_पूर्णांकerfaces);
पूर्णांक gb_module_add(काष्ठा gb_module *module);
व्योम gb_module_del(काष्ठा gb_module *module);
व्योम gb_module_put(काष्ठा gb_module *module);

#पूर्ण_अगर /* __MODULE_H */
