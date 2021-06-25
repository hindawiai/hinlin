<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus operations
 *
 * Copyright 2015-2016 Google Inc.
 */

#अगर_अघोषित _GB_AUDIO_MANAGER_PRIVATE_H_
#घोषणा _GB_AUDIO_MANAGER_PRIVATE_H_

#समावेश <linux/kobject.h>

#समावेश "audio_manager.h"

पूर्णांक gb_audio_manager_module_create(
	काष्ठा gb_audio_manager_module **module,
	काष्ठा kset *manager_kset,
	पूर्णांक id, काष्ठा gb_audio_manager_module_descriptor *desc);

/* module destroyed via kobject_put */

व्योम gb_audio_manager_module_dump(काष्ठा gb_audio_manager_module *module);

/* sysfs control */
व्योम gb_audio_manager_sysfs_init(काष्ठा kobject *kobj);

#पूर्ण_अगर /* _GB_AUDIO_MANAGER_PRIVATE_H_ */
