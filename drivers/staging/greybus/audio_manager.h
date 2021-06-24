<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus operations
 *
 * Copyright 2015-2016 Google Inc.
 */

#अगर_अघोषित _GB_AUDIO_MANAGER_H_
#घोषणा _GB_AUDIO_MANAGER_H_

#समावेश <linux/kobject.h>
#समावेश <linux/list.h>

#घोषणा GB_AUDIO_MANAGER_NAME "gb_audio_manager"
#घोषणा GB_AUDIO_MANAGER_MODULE_NAME_LEN 64
#घोषणा GB_AUDIO_MANAGER_MODULE_NAME_LEN_SSCANF "63"

काष्ठा gb_audio_manager_module_descriptor अणु
	अक्षर name[GB_AUDIO_MANAGER_MODULE_NAME_LEN];
	पूर्णांक vid;
	पूर्णांक pid;
	पूर्णांक पूर्णांकf_id;
	अचिन्हित पूर्णांक ip_devices;
	अचिन्हित पूर्णांक op_devices;
पूर्ण;

काष्ठा gb_audio_manager_module अणु
	काष्ठा kobject kobj;
	काष्ठा list_head list;
	पूर्णांक id;
	काष्ठा gb_audio_manager_module_descriptor desc;
पूर्ण;

/*
 * Creates a new gb_audio_manager_module_descriptor, using the specअगरied
 * descriptor.
 *
 * Returns a negative result on error, or the id of the newly created module.
 *
 */
पूर्णांक gb_audio_manager_add(काष्ठा gb_audio_manager_module_descriptor *desc);

/*
 * Removes a connected gb_audio_manager_module_descriptor क्रम the specअगरied ID.
 *
 * Returns zero on success, or a negative value on error.
 */
पूर्णांक gb_audio_manager_हटाओ(पूर्णांक id);

/*
 * Removes all connected gb_audio_modules
 *
 * Returns zero on success, or a negative value on error.
 */
व्योम gb_audio_manager_हटाओ_all(व्योम);

/*
 * Retrieves a gb_audio_manager_module_descriptor क्रम the specअगरied id.
 * Returns the gb_audio_manager_module_descriptor काष्ठाure,
 * or शून्य अगर there is no module with the specअगरied ID.
 */
काष्ठा gb_audio_manager_module *gb_audio_manager_get_module(पूर्णांक id);

/*
 * Decreases the refcount of the module, obtained by the get function.
 * Modules are हटाओd via gb_audio_manager_हटाओ
 */
व्योम gb_audio_manager_put_module(काष्ठा gb_audio_manager_module *module);

/*
 * Dumps the module क्रम the specअगरied id
 * Return 0 on success
 */
पूर्णांक gb_audio_manager_dump_module(पूर्णांक id);

/*
 * Dumps all connected modules
 */
व्योम gb_audio_manager_dump_all(व्योम);

#पूर्ण_अगर /* _GB_AUDIO_MANAGER_H_ */
