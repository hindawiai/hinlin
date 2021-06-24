<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
 *   Daniel Vetter <daniel.vetter@ffwll.ch>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/kthपढ़ो.h>

#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_vblank.h>

#घोषणा DRM_IF_MAJOR 1
#घोषणा DRM_IF_MINOR 4

#घोषणा DRM_IF_VERSION(maj, min) (maj << 16 | min)

काष्ठा dentry;
काष्ठा dma_buf;
काष्ठा dma_buf_map;
काष्ठा drm_connector;
काष्ठा drm_crtc;
काष्ठा drm_framebuffer;
काष्ठा drm_gem_object;
काष्ठा drm_master;
काष्ठा drm_minor;
काष्ठा drm_prime_file_निजी;
काष्ठा drm_prपूर्णांकer;
काष्ठा drm_vblank_crtc;

/* drm_file.c */
बाह्य काष्ठा mutex drm_global_mutex;
bool drm_dev_needs_global_mutex(काष्ठा drm_device *dev);
काष्ठा drm_file *drm_file_alloc(काष्ठा drm_minor *minor);
व्योम drm_file_मुक्त(काष्ठा drm_file *file);
व्योम drm_lastबंद(काष्ठा drm_device *dev);

#अगर_घोषित CONFIG_PCI

/* drm_pci.c */
पूर्णांक drm_legacy_irq_by_busid(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv);
व्योम drm_pci_agp_destroy(काष्ठा drm_device *dev);
पूर्णांक drm_pci_set_busid(काष्ठा drm_device *dev, काष्ठा drm_master *master);

#अन्यथा

अटल अंतरभूत पूर्णांक drm_legacy_irq_by_busid(काष्ठा drm_device *dev, व्योम *data,
					  काष्ठा drm_file *file_priv)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम drm_pci_agp_destroy(काष्ठा drm_device *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक drm_pci_set_busid(काष्ठा drm_device *dev,
				    काष्ठा drm_master *master)
अणु
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर

/* drm_prime.c */
पूर्णांक drm_prime_handle_to_fd_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv);
पूर्णांक drm_prime_fd_to_handle_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv);

व्योम drm_prime_init_file_निजी(काष्ठा drm_prime_file_निजी *prime_fpriv);
व्योम drm_prime_destroy_file_निजी(काष्ठा drm_prime_file_निजी *prime_fpriv);
व्योम drm_prime_हटाओ_buf_handle_locked(काष्ठा drm_prime_file_निजी *prime_fpriv,
					काष्ठा dma_buf *dma_buf);

/* drm_drv.c */
काष्ठा drm_minor *drm_minor_acquire(अचिन्हित पूर्णांक minor_id);
व्योम drm_minor_release(काष्ठा drm_minor *minor);

/* drm_managed.c */
व्योम drm_managed_release(काष्ठा drm_device *dev);
व्योम drmm_add_final_kमुक्त(काष्ठा drm_device *dev, व्योम *container);

/* drm_vblank.c */
अटल अंतरभूत bool drm_vblank_passed(u64 seq, u64 ref)
अणु
	वापस (seq - ref) <= (1 << 23);
पूर्ण

व्योम drm_vblank_disable_and_save(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
पूर्णांक drm_vblank_get(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
व्योम drm_vblank_put(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
u64 drm_vblank_count(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);

/* drm_vblank_work.c */
अटल अंतरभूत व्योम drm_vblank_flush_worker(काष्ठा drm_vblank_crtc *vblank)
अणु
	kthपढ़ो_flush_worker(vblank->worker);
पूर्ण

अटल अंतरभूत व्योम drm_vblank_destroy_worker(काष्ठा drm_vblank_crtc *vblank)
अणु
	kthपढ़ो_destroy_worker(vblank->worker);
पूर्ण

पूर्णांक drm_vblank_worker_init(काष्ठा drm_vblank_crtc *vblank);
व्योम drm_vblank_cancel_pending_works(काष्ठा drm_vblank_crtc *vblank);
व्योम drm_handle_vblank_works(काष्ठा drm_vblank_crtc *vblank);

/* IOCTLS */
पूर्णांक drm_रुको_vblank_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp);
पूर्णांक drm_legacy_modeset_ctl_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv);

/* drm_irq.c */

/* IOCTLS */
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
पूर्णांक drm_legacy_irq_control(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv);
#पूर्ण_अगर

पूर्णांक drm_crtc_get_sequence_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp);

पूर्णांक drm_crtc_queue_sequence_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *filp);

/* drm_auth.c */
पूर्णांक drm_geपंचांगagic(काष्ठा drm_device *dev, व्योम *data,
		 काष्ठा drm_file *file_priv);
पूर्णांक drm_authmagic(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv);
पूर्णांक drm_seपंचांगaster_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
पूर्णांक drm_dropmaster_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
पूर्णांक drm_master_खोलो(काष्ठा drm_file *file_priv);
व्योम drm_master_release(काष्ठा drm_file *file_priv);
bool drm_master_पूर्णांकernal_acquire(काष्ठा drm_device *dev);
व्योम drm_master_पूर्णांकernal_release(काष्ठा drm_device *dev);

/* drm_sysfs.c */
बाह्य काष्ठा class *drm_class;

पूर्णांक drm_sysfs_init(व्योम);
व्योम drm_sysfs_destroy(व्योम);
काष्ठा device *drm_sysfs_minor_alloc(काष्ठा drm_minor *minor);
पूर्णांक drm_sysfs_connector_add(काष्ठा drm_connector *connector);
व्योम drm_sysfs_connector_हटाओ(काष्ठा drm_connector *connector);

व्योम drm_sysfs_lease_event(काष्ठा drm_device *dev);

/* drm_gem.c */
पूर्णांक drm_gem_init(काष्ठा drm_device *dev);
पूर्णांक drm_gem_handle_create_tail(काष्ठा drm_file *file_priv,
			       काष्ठा drm_gem_object *obj,
			       u32 *handlep);
पूर्णांक drm_gem_बंद_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
पूर्णांक drm_gem_flink_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
पूर्णांक drm_gem_खोलो_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv);
व्योम drm_gem_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file_निजी);
व्योम drm_gem_release(काष्ठा drm_device *dev, काष्ठा drm_file *file_निजी);
व्योम drm_gem_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
			स्थिर काष्ठा drm_gem_object *obj);

पूर्णांक drm_gem_pin(काष्ठा drm_gem_object *obj);
व्योम drm_gem_unpin(काष्ठा drm_gem_object *obj);
पूर्णांक drm_gem_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);
व्योम drm_gem_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);

पूर्णांक drm_gem_dumb_destroy(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			 u32 handle);

/* drm_debugfs.c drm_debugfs_crc.c */
#अगर defined(CONFIG_DEBUG_FS)
पूर्णांक drm_debugfs_init(काष्ठा drm_minor *minor, पूर्णांक minor_id,
		     काष्ठा dentry *root);
व्योम drm_debugfs_cleanup(काष्ठा drm_minor *minor);
व्योम drm_debugfs_connector_add(काष्ठा drm_connector *connector);
व्योम drm_debugfs_connector_हटाओ(काष्ठा drm_connector *connector);
व्योम drm_debugfs_crtc_add(काष्ठा drm_crtc *crtc);
व्योम drm_debugfs_crtc_हटाओ(काष्ठा drm_crtc *crtc);
व्योम drm_debugfs_crtc_crc_add(काष्ठा drm_crtc *crtc);
#अन्यथा
अटल अंतरभूत पूर्णांक drm_debugfs_init(काष्ठा drm_minor *minor, पूर्णांक minor_id,
				   काष्ठा dentry *root)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम drm_debugfs_cleanup(काष्ठा drm_minor *minor)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_debugfs_connector_add(काष्ठा drm_connector *connector)
अणु
पूर्ण
अटल अंतरभूत व्योम drm_debugfs_connector_हटाओ(काष्ठा drm_connector *connector)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_debugfs_crtc_add(काष्ठा drm_crtc *crtc)
अणु
पूर्ण
अटल अंतरभूत व्योम drm_debugfs_crtc_हटाओ(काष्ठा drm_crtc *crtc)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_debugfs_crtc_crc_add(काष्ठा drm_crtc *crtc)
अणु
पूर्ण

#पूर्ण_अगर

drm_ioctl_t drm_version;
drm_ioctl_t drm_getunique;
drm_ioctl_t drm_अ_लोlient;

/* drm_syncobj.c */
व्योम drm_syncobj_खोलो(काष्ठा drm_file *file_निजी);
व्योम drm_syncobj_release(काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_handle_to_fd_ioctl(काष्ठा drm_device *dev, व्योम *data,
				   काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_fd_to_handle_ioctl(काष्ठा drm_device *dev, व्योम *data,
				   काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_transfer_ioctl(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_समयline_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_reset_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_संकेत_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_समयline_संकेत_ioctl(काष्ठा drm_device *dev, व्योम *data,
				      काष्ठा drm_file *file_निजी);
पूर्णांक drm_syncobj_query_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_निजी);

/* drm_framebuffer.c */
व्योम drm_framebuffer_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
				स्थिर काष्ठा drm_framebuffer *fb);
व्योम drm_framebuffer_debugfs_init(काष्ठा drm_minor *minor);
