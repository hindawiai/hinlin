<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 or MIT */

#अगर_अघोषित _DRM_CLIENT_H_
#घोषणा _DRM_CLIENT_H_

#समावेश <linux/dma-buf-map.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>

काष्ठा drm_client_dev;
काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_framebuffer;
काष्ठा drm_gem_object;
काष्ठा drm_minor;
काष्ठा module;

/**
 * काष्ठा drm_client_funcs - DRM client callbacks
 */
काष्ठा drm_client_funcs अणु
	/**
	 * @owner: The module owner
	 */
	काष्ठा module *owner;

	/**
	 * @unरेजिस्टर:
	 *
	 * Called when &drm_device is unरेजिस्टरed. The client should respond by
	 * releasing its resources using drm_client_release().
	 *
	 * This callback is optional.
	 */
	व्योम (*unरेजिस्टर)(काष्ठा drm_client_dev *client);

	/**
	 * @restore:
	 *
	 * Called on drm_lastबंद(). The first client instance in the list that
	 * वापसs zero माला_लो the privilege to restore and no more clients are
	 * called. This callback is not called after @unरेजिस्टर has been called.
	 *
	 * Note that the core करोes not guarantee exclusion against concurrent
	 * drm_खोलो(). Clients need to ensure this themselves, क्रम example by
	 * using drm_master_पूर्णांकernal_acquire() and
	 * drm_master_पूर्णांकernal_release().
	 *
	 * This callback is optional.
	 */
	पूर्णांक (*restore)(काष्ठा drm_client_dev *client);

	/**
	 * @hotplug:
	 *
	 * Called on drm_kms_helper_hotplug_event().
	 * This callback is not called after @unरेजिस्टर has been called.
	 *
	 * This callback is optional.
	 */
	पूर्णांक (*hotplug)(काष्ठा drm_client_dev *client);
पूर्ण;

/**
 * काष्ठा drm_client_dev - DRM client instance
 */
काष्ठा drm_client_dev अणु
	/**
	 * @dev: DRM device
	 */
	काष्ठा drm_device *dev;

	/**
	 * @name: Name of the client.
	 */
	स्थिर अक्षर *name;

	/**
	 * @list:
	 *
	 * List of all clients of a DRM device, linked पूर्णांकo
	 * &drm_device.clientlist. Protected by &drm_device.clientlist_mutex.
	 */
	काष्ठा list_head list;

	/**
	 * @funcs: DRM client functions (optional)
	 */
	स्थिर काष्ठा drm_client_funcs *funcs;

	/**
	 * @file: DRM file
	 */
	काष्ठा drm_file *file;

	/**
	 * @modeset_mutex: Protects @modesets.
	 */
	काष्ठा mutex modeset_mutex;

	/**
	 * @modesets: CRTC configurations
	 */
	काष्ठा drm_mode_set *modesets;
पूर्ण;

पूर्णांक drm_client_init(काष्ठा drm_device *dev, काष्ठा drm_client_dev *client,
		    स्थिर अक्षर *name, स्थिर काष्ठा drm_client_funcs *funcs);
व्योम drm_client_release(काष्ठा drm_client_dev *client);
व्योम drm_client_रेजिस्टर(काष्ठा drm_client_dev *client);

व्योम drm_client_dev_unरेजिस्टर(काष्ठा drm_device *dev);
व्योम drm_client_dev_hotplug(काष्ठा drm_device *dev);
व्योम drm_client_dev_restore(काष्ठा drm_device *dev);

/**
 * काष्ठा drm_client_buffer - DRM client buffer
 */
काष्ठा drm_client_buffer अणु
	/**
	 * @client: DRM client
	 */
	काष्ठा drm_client_dev *client;

	/**
	 * @handle: Buffer handle
	 */
	u32 handle;

	/**
	 * @pitch: Buffer pitch
	 */
	u32 pitch;

	/**
	 * @gem: GEM object backing this buffer
	 */
	काष्ठा drm_gem_object *gem;

	/**
	 * @map: Virtual address क्रम the buffer
	 */
	काष्ठा dma_buf_map map;

	/**
	 * @fb: DRM framebuffer
	 */
	काष्ठा drm_framebuffer *fb;
पूर्ण;

काष्ठा drm_client_buffer *
drm_client_framebuffer_create(काष्ठा drm_client_dev *client, u32 width, u32 height, u32 क्रमmat);
व्योम drm_client_framebuffer_delete(काष्ठा drm_client_buffer *buffer);
पूर्णांक drm_client_framebuffer_flush(काष्ठा drm_client_buffer *buffer, काष्ठा drm_rect *rect);
पूर्णांक drm_client_buffer_vmap(काष्ठा drm_client_buffer *buffer, काष्ठा dma_buf_map *map);
व्योम drm_client_buffer_vunmap(काष्ठा drm_client_buffer *buffer);

पूर्णांक drm_client_modeset_create(काष्ठा drm_client_dev *client);
व्योम drm_client_modeset_मुक्त(काष्ठा drm_client_dev *client);
पूर्णांक drm_client_modeset_probe(काष्ठा drm_client_dev *client, अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height);
bool drm_client_rotation(काष्ठा drm_mode_set *modeset, अचिन्हित पूर्णांक *rotation);
पूर्णांक drm_client_modeset_check(काष्ठा drm_client_dev *client);
पूर्णांक drm_client_modeset_commit_locked(काष्ठा drm_client_dev *client);
पूर्णांक drm_client_modeset_commit(काष्ठा drm_client_dev *client);
पूर्णांक drm_client_modeset_dpms(काष्ठा drm_client_dev *client, पूर्णांक mode);

/**
 * drm_client_क्रम_each_modeset() - Iterate over client modesets
 * @modeset: &drm_mode_set loop cursor
 * @client: DRM client
 */
#घोषणा drm_client_क्रम_each_modeset(modeset, client) \
	क्रम ((अणु lockdep_निश्चित_held(&(client)->modeset_mutex); पूर्ण), \
	     modeset = (client)->modesets; modeset->crtc; modeset++)

/**
 * drm_client_क्रम_each_connector_iter - connector_list iterator macro
 * @connector: &काष्ठा drm_connector poपूर्णांकer used as cursor
 * @iter: &काष्ठा drm_connector_list_iter
 *
 * This iterates the connectors that are useable क्रम पूर्णांकernal clients (excludes
 * ग_लिखोback connectors).
 *
 * For more info see drm_क्रम_each_connector_iter().
 */
#घोषणा drm_client_क्रम_each_connector_iter(connector, iter) \
	drm_क्रम_each_connector_iter(connector, iter) \
		अगर (connector->connector_type != DRM_MODE_CONNECTOR_WRITEBACK)

व्योम drm_client_debugfs_init(काष्ठा drm_minor *minor);

#पूर्ण_अगर
