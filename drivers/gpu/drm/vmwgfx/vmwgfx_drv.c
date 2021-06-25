<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2016 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश <linux/console.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/mem_encrypt.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_sysfs.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "ttm_object.h"
#समावेश "vmwgfx_binding.h"
#समावेश "vmwgfx_drv.h"

#घोषणा VMWGFX_DRIVER_DESC "Linux drm driver for VMware graphics devices"

#घोषणा VMW_MIN_INITIAL_WIDTH 800
#घोषणा VMW_MIN_INITIAL_HEIGHT 600

#घोषणा VMWGFX_VALIDATION_MEM_GRAN (16*PAGE_SIZE)


/**
 * Fully encoded drm commands. Might move to vmw_drm.h
 */

#घोषणा DRM_IOCTL_VMW_GET_PARAM					\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_GET_PARAM,		\
		 काष्ठा drm_vmw_getparam_arg)
#घोषणा DRM_IOCTL_VMW_ALLOC_DMABUF				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_ALLOC_DMABUF,	\
		जोड़ drm_vmw_alloc_dmabuf_arg)
#घोषणा DRM_IOCTL_VMW_UNREF_DMABUF				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_UNREF_DMABUF,	\
		काष्ठा drm_vmw_unref_dmabuf_arg)
#घोषणा DRM_IOCTL_VMW_CURSOR_BYPASS				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_CURSOR_BYPASS,	\
		 काष्ठा drm_vmw_cursor_bypass_arg)

#घोषणा DRM_IOCTL_VMW_CONTROL_STREAM				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_CONTROL_STREAM,	\
		 काष्ठा drm_vmw_control_stream_arg)
#घोषणा DRM_IOCTL_VMW_CLAIM_STREAM				\
	DRM_IOR(DRM_COMMAND_BASE + DRM_VMW_CLAIM_STREAM,	\
		 काष्ठा drm_vmw_stream_arg)
#घोषणा DRM_IOCTL_VMW_UNREF_STREAM				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_UNREF_STREAM,	\
		 काष्ठा drm_vmw_stream_arg)

#घोषणा DRM_IOCTL_VMW_CREATE_CONTEXT				\
	DRM_IOR(DRM_COMMAND_BASE + DRM_VMW_CREATE_CONTEXT,	\
		काष्ठा drm_vmw_context_arg)
#घोषणा DRM_IOCTL_VMW_UNREF_CONTEXT				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_UNREF_CONTEXT,	\
		काष्ठा drm_vmw_context_arg)
#घोषणा DRM_IOCTL_VMW_CREATE_SURFACE				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_CREATE_SURFACE,	\
		 जोड़ drm_vmw_surface_create_arg)
#घोषणा DRM_IOCTL_VMW_UNREF_SURFACE				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_UNREF_SURFACE,	\
		 काष्ठा drm_vmw_surface_arg)
#घोषणा DRM_IOCTL_VMW_REF_SURFACE				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_REF_SURFACE,	\
		 जोड़ drm_vmw_surface_reference_arg)
#घोषणा DRM_IOCTL_VMW_EXECBUF					\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_EXECBUF,		\
		काष्ठा drm_vmw_execbuf_arg)
#घोषणा DRM_IOCTL_VMW_GET_3D_CAP				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_GET_3D_CAP,		\
		 काष्ठा drm_vmw_get_3d_cap_arg)
#घोषणा DRM_IOCTL_VMW_FENCE_WAIT				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_FENCE_WAIT,		\
		 काष्ठा drm_vmw_fence_रुको_arg)
#घोषणा DRM_IOCTL_VMW_FENCE_SIGNALED				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_FENCE_SIGNALED,	\
		 काष्ठा drm_vmw_fence_संकेतed_arg)
#घोषणा DRM_IOCTL_VMW_FENCE_UNREF				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_FENCE_UNREF,		\
		 काष्ठा drm_vmw_fence_arg)
#घोषणा DRM_IOCTL_VMW_FENCE_EVENT				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_FENCE_EVENT,		\
		 काष्ठा drm_vmw_fence_event_arg)
#घोषणा DRM_IOCTL_VMW_PRESENT					\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_PRESENT,		\
		 काष्ठा drm_vmw_present_arg)
#घोषणा DRM_IOCTL_VMW_PRESENT_READBACK				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_PRESENT_READBACK,	\
		 काष्ठा drm_vmw_present_पढ़ोback_arg)
#घोषणा DRM_IOCTL_VMW_UPDATE_LAYOUT				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_UPDATE_LAYOUT,	\
		 काष्ठा drm_vmw_update_layout_arg)
#घोषणा DRM_IOCTL_VMW_CREATE_SHADER				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_CREATE_SHADER,	\
		 काष्ठा drm_vmw_shader_create_arg)
#घोषणा DRM_IOCTL_VMW_UNREF_SHADER				\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_UNREF_SHADER,	\
		 काष्ठा drm_vmw_shader_arg)
#घोषणा DRM_IOCTL_VMW_GB_SURFACE_CREATE				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_GB_SURFACE_CREATE,	\
		 जोड़ drm_vmw_gb_surface_create_arg)
#घोषणा DRM_IOCTL_VMW_GB_SURFACE_REF				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_GB_SURFACE_REF,	\
		 जोड़ drm_vmw_gb_surface_reference_arg)
#घोषणा DRM_IOCTL_VMW_SYNCCPU					\
	DRM_IOW(DRM_COMMAND_BASE + DRM_VMW_SYNCCPU,		\
		 काष्ठा drm_vmw_synccpu_arg)
#घोषणा DRM_IOCTL_VMW_CREATE_EXTENDED_CONTEXT			\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_CREATE_EXTENDED_CONTEXT,	\
		काष्ठा drm_vmw_context_arg)
#घोषणा DRM_IOCTL_VMW_GB_SURFACE_CREATE_EXT				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_GB_SURFACE_CREATE_EXT,	\
		जोड़ drm_vmw_gb_surface_create_ext_arg)
#घोषणा DRM_IOCTL_VMW_GB_SURFACE_REF_EXT				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_GB_SURFACE_REF_EXT,		\
		जोड़ drm_vmw_gb_surface_reference_ext_arg)
#घोषणा DRM_IOCTL_VMW_MSG						\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VMW_MSG,			\
		काष्ठा drm_vmw_msg_arg)

/*
 * The core DRM version of this macro करोesn't account क्रम
 * DRM_COMMAND_BASE.
 */

#घोषणा VMW_IOCTL_DEF(ioctl, func, flags) \
  [DRM_IOCTL_NR(DRM_IOCTL_##ioctl) - DRM_COMMAND_BASE] = अणुDRM_IOCTL_##ioctl, flags, funcपूर्ण

/*
 * Ioctl definitions.
 */

अटल स्थिर काष्ठा drm_ioctl_desc vmw_ioctls[] = अणु
	VMW_IOCTL_DEF(VMW_GET_PARAM, vmw_getparam_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_ALLOC_DMABUF, vmw_bo_alloc_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_UNREF_DMABUF, vmw_bo_unref_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_CURSOR_BYPASS,
		      vmw_kms_cursor_bypass_ioctl,
		      DRM_MASTER),

	VMW_IOCTL_DEF(VMW_CONTROL_STREAM, vmw_overlay_ioctl,
		      DRM_MASTER),
	VMW_IOCTL_DEF(VMW_CLAIM_STREAM, vmw_stream_claim_ioctl,
		      DRM_MASTER),
	VMW_IOCTL_DEF(VMW_UNREF_STREAM, vmw_stream_unref_ioctl,
		      DRM_MASTER),

	VMW_IOCTL_DEF(VMW_CREATE_CONTEXT, vmw_context_define_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_UNREF_CONTEXT, vmw_context_destroy_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_CREATE_SURFACE, vmw_surface_define_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_UNREF_SURFACE, vmw_surface_destroy_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_REF_SURFACE, vmw_surface_reference_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_EXECBUF, vmw_execbuf_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_FENCE_WAIT, vmw_fence_obj_रुको_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_FENCE_SIGNALED,
		      vmw_fence_obj_संकेतed_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_FENCE_UNREF, vmw_fence_obj_unref_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_FENCE_EVENT, vmw_fence_event_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_GET_3D_CAP, vmw_get_cap_3d_ioctl,
		      DRM_RENDER_ALLOW),

	/* these allow direct access to the framebuffers mark as master only */
	VMW_IOCTL_DEF(VMW_PRESENT, vmw_present_ioctl,
		      DRM_MASTER | DRM_AUTH),
	VMW_IOCTL_DEF(VMW_PRESENT_READBACK,
		      vmw_present_पढ़ोback_ioctl,
		      DRM_MASTER | DRM_AUTH),
	/*
	 * The permissions of the below ioctl are overridden in
	 * vmw_generic_ioctl(). We require either
	 * DRM_MASTER or capable(CAP_SYS_ADMIN).
	 */
	VMW_IOCTL_DEF(VMW_UPDATE_LAYOUT,
		      vmw_kms_update_layout_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_CREATE_SHADER,
		      vmw_shader_define_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_UNREF_SHADER,
		      vmw_shader_destroy_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_GB_SURFACE_CREATE,
		      vmw_gb_surface_define_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_GB_SURFACE_REF,
		      vmw_gb_surface_reference_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_SYNCCPU,
		      vmw_user_bo_synccpu_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_CREATE_EXTENDED_CONTEXT,
		      vmw_extended_context_define_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_GB_SURFACE_CREATE_EXT,
		      vmw_gb_surface_define_ext_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_GB_SURFACE_REF_EXT,
		      vmw_gb_surface_reference_ext_ioctl,
		      DRM_RENDER_ALLOW),
	VMW_IOCTL_DEF(VMW_MSG,
		      vmw_msg_ioctl,
		      DRM_RENDER_ALLOW),
पूर्ण;

अटल स्थिर काष्ठा pci_device_id vmw_pci_id_list[] = अणु
	अणु PCI_DEVICE(0x15ad, VMWGFX_PCI_ID_SVGA2) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, vmw_pci_id_list);

अटल पूर्णांक enable_fbdev = IS_ENABLED(CONFIG_DRM_VMWGFX_FBCON);
अटल पूर्णांक vmw_क्रमce_iommu;
अटल पूर्णांक vmw_restrict_iommu;
अटल पूर्णांक vmw_क्रमce_coherent;
अटल पूर्णांक vmw_restrict_dma_mask;
अटल पूर्णांक vmw_assume_16bpp;

अटल पूर्णांक vmw_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल पूर्णांक vmwgfx_pm_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			      व्योम *ptr);

MODULE_PARM_DESC(enable_fbdev, "Enable vmwgfx fbdev");
module_param_named(enable_fbdev, enable_fbdev, पूर्णांक, 0600);
MODULE_PARM_DESC(क्रमce_dma_api, "Force using the DMA API for TTM pages");
module_param_named(क्रमce_dma_api, vmw_क्रमce_iommu, पूर्णांक, 0600);
MODULE_PARM_DESC(restrict_iommu, "Try to limit IOMMU usage for TTM pages");
module_param_named(restrict_iommu, vmw_restrict_iommu, पूर्णांक, 0600);
MODULE_PARM_DESC(क्रमce_coherent, "Force coherent TTM pages");
module_param_named(क्रमce_coherent, vmw_क्रमce_coherent, पूर्णांक, 0600);
MODULE_PARM_DESC(restrict_dma_mask, "Restrict DMA mask to 44 bits with IOMMU");
module_param_named(restrict_dma_mask, vmw_restrict_dma_mask, पूर्णांक, 0600);
MODULE_PARM_DESC(assume_16bpp, "Assume 16-bpp when filtering modes");
module_param_named(assume_16bpp, vmw_assume_16bpp, पूर्णांक, 0600);


अटल व्योम vmw_prपूर्णांक_capabilities2(uपूर्णांक32_t capabilities2)
अणु
	DRM_INFO("Capabilities2:\n");
	अगर (capabilities2 & SVGA_CAP2_GROW_OTABLE)
		DRM_INFO("  Grow oTable.\n");
	अगर (capabilities2 & SVGA_CAP2_INTRA_SURFACE_COPY)
		DRM_INFO("  IntraSurface copy.\n");
	अगर (capabilities2 & SVGA_CAP2_DX3)
		DRM_INFO("  DX3.\n");
पूर्ण

अटल व्योम vmw_prपूर्णांक_capabilities(uपूर्णांक32_t capabilities)
अणु
	DRM_INFO("Capabilities:\n");
	अगर (capabilities & SVGA_CAP_RECT_COPY)
		DRM_INFO("  Rect copy.\n");
	अगर (capabilities & SVGA_CAP_CURSOR)
		DRM_INFO("  Cursor.\n");
	अगर (capabilities & SVGA_CAP_CURSOR_BYPASS)
		DRM_INFO("  Cursor bypass.\n");
	अगर (capabilities & SVGA_CAP_CURSOR_BYPASS_2)
		DRM_INFO("  Cursor bypass 2.\n");
	अगर (capabilities & SVGA_CAP_8BIT_EMULATION)
		DRM_INFO("  8bit emulation.\n");
	अगर (capabilities & SVGA_CAP_ALPHA_CURSOR)
		DRM_INFO("  Alpha cursor.\n");
	अगर (capabilities & SVGA_CAP_3D)
		DRM_INFO("  3D.\n");
	अगर (capabilities & SVGA_CAP_EXTENDED_FIFO)
		DRM_INFO("  Extended Fifo.\n");
	अगर (capabilities & SVGA_CAP_MULTIMON)
		DRM_INFO("  Multimon.\n");
	अगर (capabilities & SVGA_CAP_PITCHLOCK)
		DRM_INFO("  Pitchlock.\n");
	अगर (capabilities & SVGA_CAP_IRQMASK)
		DRM_INFO("  Irq mask.\n");
	अगर (capabilities & SVGA_CAP_DISPLAY_TOPOLOGY)
		DRM_INFO("  Display Topology.\n");
	अगर (capabilities & SVGA_CAP_GMR)
		DRM_INFO("  GMR.\n");
	अगर (capabilities & SVGA_CAP_TRACES)
		DRM_INFO("  Traces.\n");
	अगर (capabilities & SVGA_CAP_GMR2)
		DRM_INFO("  GMR2.\n");
	अगर (capabilities & SVGA_CAP_SCREEN_OBJECT_2)
		DRM_INFO("  Screen Object 2.\n");
	अगर (capabilities & SVGA_CAP_COMMAND_BUFFERS)
		DRM_INFO("  Command Buffers.\n");
	अगर (capabilities & SVGA_CAP_CMD_BUFFERS_2)
		DRM_INFO("  Command Buffers 2.\n");
	अगर (capabilities & SVGA_CAP_GBOBJECTS)
		DRM_INFO("  Guest Backed Resources.\n");
	अगर (capabilities & SVGA_CAP_DX)
		DRM_INFO("  DX Features.\n");
	अगर (capabilities & SVGA_CAP_HP_CMD_QUEUE)
		DRM_INFO("  HP Command Queue.\n");
पूर्ण

/**
 * vmw_dummy_query_bo_create - create a bo to hold a dummy query result
 *
 * @dev_priv: A device निजी काष्ठाure.
 *
 * This function creates a small buffer object that holds the query
 * result क्रम dummy queries emitted as query barriers.
 * The function will then map the first page and initialize a pending
 * occlusion query result काष्ठाure, Finally it will unmap the buffer.
 * No पूर्णांकerruptible रुकोs are करोne within this function.
 *
 * Returns an error अगर bo creation or initialization fails.
 */
अटल पूर्णांक vmw_dummy_query_bo_create(काष्ठा vmw_निजी *dev_priv)
अणु
	पूर्णांक ret;
	काष्ठा vmw_buffer_object *vbo;
	काष्ठा tपंचांग_bo_kmap_obj map;
	अस्थिर SVGA3dQueryResult *result;
	bool dummy;

	/*
	 * Create the vbo as pinned, so that a tryreserve will
	 * immediately succeed. This is because we're the only
	 * user of the bo currently.
	 */
	vbo = kzalloc(माप(*vbo), GFP_KERNEL);
	अगर (!vbo)
		वापस -ENOMEM;

	ret = vmw_bo_init(dev_priv, vbo, PAGE_SIZE,
			  &vmw_sys_placement, false, true,
			  &vmw_bo_bo_मुक्त);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = tपंचांग_bo_reserve(&vbo->base, false, true, शून्य);
	BUG_ON(ret != 0);
	vmw_bo_pin_reserved(vbo, true);

	ret = tपंचांग_bo_kmap(&vbo->base, 0, 1, &map);
	अगर (likely(ret == 0)) अणु
		result = tपंचांग_kmap_obj_भव(&map, &dummy);
		result->totalSize = माप(*result);
		result->state = SVGA3D_QUERYSTATE_PENDING;
		result->result32 = 0xff;
		tपंचांग_bo_kunmap(&map);
	पूर्ण
	vmw_bo_pin_reserved(vbo, false);
	tपंचांग_bo_unreserve(&vbo->base);

	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Dummy query buffer map failed.\n");
		vmw_bo_unreference(&vbo);
	पूर्ण अन्यथा
		dev_priv->dummy_query_bo = vbo;

	वापस ret;
पूर्ण

/**
 * vmw_request_device_late - Perक्रमm late device setup
 *
 * @dev_priv: Poपूर्णांकer to device निजी.
 *
 * This function perक्रमms setup of otables and enables large command
 * buffer submission. These tasks are split out to a separate function
 * because it reverts vmw_release_device_early and is पूर्णांकended to be used
 * by an error path in the hibernation code.
 */
अटल पूर्णांक vmw_request_device_late(काष्ठा vmw_निजी *dev_priv)
अणु
	पूर्णांक ret;

	अगर (dev_priv->has_mob) अणु
		ret = vmw_otables_setup(dev_priv);
		अगर (unlikely(ret != 0)) अणु
			DRM_ERROR("Unable to initialize "
				  "guest Memory OBjects.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (dev_priv->cman) अणु
		ret = vmw_cmdbuf_set_pool_size(dev_priv->cman, 256*4096);
		अगर (ret) अणु
			काष्ठा vmw_cmdbuf_man *man = dev_priv->cman;

			dev_priv->cman = शून्य;
			vmw_cmdbuf_man_destroy(man);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_request_device(काष्ठा vmw_निजी *dev_priv)
अणु
	पूर्णांक ret;

	ret = vmw_fअगरo_init(dev_priv, &dev_priv->fअगरo);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Unable to initialize FIFO.\n");
		वापस ret;
	पूर्ण
	vmw_fence_fअगरo_up(dev_priv->fman);
	dev_priv->cman = vmw_cmdbuf_man_create(dev_priv);
	अगर (IS_ERR(dev_priv->cman)) अणु
		dev_priv->cman = शून्य;
		dev_priv->sm_type = VMW_SM_LEGACY;
	पूर्ण

	ret = vmw_request_device_late(dev_priv);
	अगर (ret)
		जाओ out_no_mob;

	ret = vmw_dummy_query_bo_create(dev_priv);
	अगर (unlikely(ret != 0))
		जाओ out_no_query_bo;

	वापस 0;

out_no_query_bo:
	अगर (dev_priv->cman)
		vmw_cmdbuf_हटाओ_pool(dev_priv->cman);
	अगर (dev_priv->has_mob) अणु
		काष्ठा tपंचांग_resource_manager *man;

		man = tपंचांग_manager_type(&dev_priv->bdev, VMW_PL_MOB);
		tपंचांग_resource_manager_evict_all(&dev_priv->bdev, man);
		vmw_otables_takeकरोwn(dev_priv);
	पूर्ण
	अगर (dev_priv->cman)
		vmw_cmdbuf_man_destroy(dev_priv->cman);
out_no_mob:
	vmw_fence_fअगरo_करोwn(dev_priv->fman);
	vmw_fअगरo_release(dev_priv, &dev_priv->fअगरo);
	वापस ret;
पूर्ण

/**
 * vmw_release_device_early - Early part of fअगरo takeकरोwn.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठा.
 *
 * This is the first part of command submission takeकरोwn, to be called beक्रमe
 * buffer management is taken करोwn.
 */
अटल व्योम vmw_release_device_early(काष्ठा vmw_निजी *dev_priv)
अणु
	/*
	 * Previous deकाष्ठाions should've released
	 * the pinned bo.
	 */

	BUG_ON(dev_priv->pinned_bo != शून्य);

	vmw_bo_unreference(&dev_priv->dummy_query_bo);
	अगर (dev_priv->cman)
		vmw_cmdbuf_हटाओ_pool(dev_priv->cman);

	अगर (dev_priv->has_mob) अणु
		काष्ठा tपंचांग_resource_manager *man;

		man = tपंचांग_manager_type(&dev_priv->bdev, VMW_PL_MOB);
		tपंचांग_resource_manager_evict_all(&dev_priv->bdev, man);
		vmw_otables_takeकरोwn(dev_priv);
	पूर्ण
पूर्ण

/**
 * vmw_release_device_late - Late part of fअगरo takeकरोwn.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठा.
 *
 * This is the last part of the command submission takeकरोwn, to be called when
 * command submission is no दीर्घer needed. It may रुको on pending fences.
 */
अटल व्योम vmw_release_device_late(काष्ठा vmw_निजी *dev_priv)
अणु
	vmw_fence_fअगरo_करोwn(dev_priv->fman);
	अगर (dev_priv->cman)
		vmw_cmdbuf_man_destroy(dev_priv->cman);

	vmw_fअगरo_release(dev_priv, &dev_priv->fअगरo);
पूर्ण

/*
 * Sets the initial_[width|height] fields on the given vmw_निजी.
 *
 * It करोes so by पढ़ोing SVGA_REG_[WIDTH|HEIGHT] regs and then
 * clamping the value to fb_max_[width|height] fields and the
 * VMW_MIN_INITIAL_[WIDTH|HEIGHT].
 * If the values appear to be invalid, set them to
 * VMW_MIN_INITIAL_[WIDTH|HEIGHT].
 */
अटल व्योम vmw_get_initial_size(काष्ठा vmw_निजी *dev_priv)
अणु
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;

	width = vmw_पढ़ो(dev_priv, SVGA_REG_WIDTH);
	height = vmw_पढ़ो(dev_priv, SVGA_REG_HEIGHT);

	width = max_t(uपूर्णांक32_t, width, VMW_MIN_INITIAL_WIDTH);
	height = max_t(uपूर्णांक32_t, height, VMW_MIN_INITIAL_HEIGHT);

	अगर (width > dev_priv->fb_max_width ||
	    height > dev_priv->fb_max_height) अणु

		/*
		 * This is a host error and shouldn't occur.
		 */

		width = VMW_MIN_INITIAL_WIDTH;
		height = VMW_MIN_INITIAL_HEIGHT;
	पूर्ण

	dev_priv->initial_width = width;
	dev_priv->initial_height = height;
पूर्ण

/**
 * vmw_dma_select_mode - Determine how DMA mappings should be set up क्रम this
 * प्रणाली.
 *
 * @dev_priv: Poपूर्णांकer to a काष्ठा vmw_निजी
 *
 * This functions tries to determine what actions need to be taken by the
 * driver to make प्रणाली pages visible to the device.
 * If this function decides that DMA is not possible, it वापसs -EINVAL.
 * The driver may then try to disable features of the device that require
 * DMA.
 */
अटल पूर्णांक vmw_dma_select_mode(काष्ठा vmw_निजी *dev_priv)
अणु
	अटल स्थिर अक्षर *names[vmw_dma_map_max] = अणु
		[vmw_dma_phys] = "Using physical TTM page addresses.",
		[vmw_dma_alloc_coherent] = "Using coherent TTM pages.",
		[vmw_dma_map_populate] = "Caching DMA mappings.",
		[vmw_dma_map_bind] = "Giving up DMA mappings early."पूर्ण;

	/* TTM currently करोesn't fully support SEV encryption. */
	अगर (mem_encrypt_active())
		वापस -EINVAL;

	अगर (vmw_क्रमce_coherent)
		dev_priv->map_mode = vmw_dma_alloc_coherent;
	अन्यथा अगर (vmw_restrict_iommu)
		dev_priv->map_mode = vmw_dma_map_bind;
	अन्यथा
		dev_priv->map_mode = vmw_dma_map_populate;

	DRM_INFO("DMA map mode: %s\n", names[dev_priv->map_mode]);
	वापस 0;
पूर्ण

/**
 * vmw_dma_masks - set required page- and dma masks
 *
 * @dev_priv: Poपूर्णांकer to काष्ठा drm-device
 *
 * With 32-bit we can only handle 32 bit PFNs. Optionally set that
 * restriction also क्रम 64-bit प्रणालीs.
 */
अटल पूर्णांक vmw_dma_masks(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	पूर्णांक ret = 0;

	ret = dma_set_mask_and_coherent(dev->dev, DMA_BIT_MASK(64));
	अगर (dev_priv->map_mode != vmw_dma_phys &&
	    (माप(अचिन्हित दीर्घ) == 4 || vmw_restrict_dma_mask)) अणु
		DRM_INFO("Restricting DMA addresses to 44 bits.\n");
		वापस dma_set_mask_and_coherent(dev->dev, DMA_BIT_MASK(44));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vmw_vram_manager_init(काष्ठा vmw_निजी *dev_priv)
अणु
	पूर्णांक ret;
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	ret = vmw_thp_init(dev_priv);
#अन्यथा
	ret = tपंचांग_range_man_init(&dev_priv->bdev, TTM_PL_VRAM, false,
				 dev_priv->vram_size >> PAGE_SHIFT);
#पूर्ण_अगर
	tपंचांग_resource_manager_set_used(tपंचांग_manager_type(&dev_priv->bdev, TTM_PL_VRAM), false);
	वापस ret;
पूर्ण

अटल व्योम vmw_vram_manager_fini(काष्ठा vmw_निजी *dev_priv)
अणु
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	vmw_thp_fini(dev_priv);
#अन्यथा
	tपंचांग_range_man_fini(&dev_priv->bdev, TTM_PL_VRAM);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक vmw_setup_pci_resources(काष्ठा vmw_निजी *dev,
				   अचिन्हित दीर्घ pci_id)
अणु
	resource_माप_प्रकार fअगरo_start;
	resource_माप_प्रकार fअगरo_size;
	पूर्णांक ret;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->drm.dev);

	pci_set_master(pdev);

	ret = pci_request_regions(pdev, "vmwgfx probe");
	अगर (ret)
		वापस ret;

	dev->io_start = pci_resource_start(pdev, 0);
	dev->vram_start = pci_resource_start(pdev, 1);
	dev->vram_size = pci_resource_len(pdev, 1);
	fअगरo_start = pci_resource_start(pdev, 2);
	fअगरo_size = pci_resource_len(pdev, 2);

	DRM_INFO("FIFO at %pa size is %llu kiB\n",
		 &fअगरo_start, (uपूर्णांक64_t)fअगरo_size / 1024);
	dev->fअगरo_mem = devm_memremap(dev->drm.dev,
				      fअगरo_start,
				      fअगरo_size,
				      MEMREMAP_WB);

	अगर (IS_ERR(dev->fअगरo_mem)) अणु
		DRM_ERROR("Failed mapping FIFO memory.\n");
		pci_release_regions(pdev);
		वापस PTR_ERR(dev->fअगरo_mem);
	पूर्ण

	/*
	 * This is approximate size of the vram, the exact size will only
	 * be known after we पढ़ो SVGA_REG_VRAM_SIZE. The PCI resource
	 * size will be equal to or bigger than the size reported by
	 * SVGA_REG_VRAM_SIZE.
	 */
	DRM_INFO("VRAM at %pa size is %llu kiB\n",
		 &dev->vram_start, (uपूर्णांक64_t)dev->vram_size / 1024);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_detect_version(काष्ठा vmw_निजी *dev)
अणु
	uपूर्णांक32_t svga_id;

	vmw_ग_लिखो(dev, SVGA_REG_ID, SVGA_ID_2);
	svga_id = vmw_पढ़ो(dev, SVGA_REG_ID);
	अगर (svga_id != SVGA_ID_2) अणु
		DRM_ERROR("Unsupported SVGA ID 0x%x on chipset 0x%x\n",
			  svga_id, dev->vmw_chipset);
		वापस -ENOSYS;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vmw_driver_load(काष्ठा vmw_निजी *dev_priv, u32 pci_id)
अणु
	पूर्णांक ret;
	क्रमागत vmw_res_type i;
	bool refuse_dma = false;
	अक्षर host_log[100] = अणु0पूर्ण;
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);

	dev_priv->vmw_chipset = pci_id;
	dev_priv->last_पढ़ो_seqno = (uपूर्णांक32_t) -100;
	dev_priv->drm.dev_निजी = dev_priv;

	mutex_init(&dev_priv->cmdbuf_mutex);
	mutex_init(&dev_priv->binding_mutex);
	tपंचांग_lock_init(&dev_priv->reservation_sem);
	spin_lock_init(&dev_priv->resource_lock);
	spin_lock_init(&dev_priv->hw_lock);
	spin_lock_init(&dev_priv->रुकोer_lock);
	spin_lock_init(&dev_priv->cap_lock);
	spin_lock_init(&dev_priv->cursor_lock);

	ret = vmw_setup_pci_resources(dev_priv, pci_id);
	अगर (ret)
		वापस ret;
	ret = vmw_detect_version(dev_priv);
	अगर (ret)
		जाओ out_no_pci_or_version;


	क्रम (i = vmw_res_context; i < vmw_res_max; ++i) अणु
		idr_init(&dev_priv->res_idr[i]);
		INIT_LIST_HEAD(&dev_priv->res_lru[i]);
	पूर्ण

	init_रुकोqueue_head(&dev_priv->fence_queue);
	init_रुकोqueue_head(&dev_priv->fअगरo_queue);
	dev_priv->fence_queue_रुकोers = 0;
	dev_priv->fअगरo_queue_रुकोers = 0;

	dev_priv->used_memory_size = 0;

	dev_priv->assume_16bpp = !!vmw_assume_16bpp;

	dev_priv->enable_fb = enable_fbdev;


	dev_priv->capabilities = vmw_पढ़ो(dev_priv, SVGA_REG_CAPABILITIES);

	अगर (dev_priv->capabilities & SVGA_CAP_CAP2_REGISTER) अणु
		dev_priv->capabilities2 = vmw_पढ़ो(dev_priv, SVGA_REG_CAP2);
	पूर्ण


	ret = vmw_dma_select_mode(dev_priv);
	अगर (unlikely(ret != 0)) अणु
		DRM_INFO("Restricting capabilities since DMA not available.\n");
		refuse_dma = true;
		अगर (dev_priv->capabilities & SVGA_CAP_GBOBJECTS)
			DRM_INFO("Disabling 3D acceleration.\n");
	पूर्ण

	dev_priv->vram_size = vmw_पढ़ो(dev_priv, SVGA_REG_VRAM_SIZE);
	dev_priv->fअगरo_mem_size = vmw_पढ़ो(dev_priv, SVGA_REG_MEM_SIZE);
	dev_priv->fb_max_width = vmw_पढ़ो(dev_priv, SVGA_REG_MAX_WIDTH);
	dev_priv->fb_max_height = vmw_पढ़ो(dev_priv, SVGA_REG_MAX_HEIGHT);

	vmw_get_initial_size(dev_priv);

	अगर (dev_priv->capabilities & SVGA_CAP_GMR2) अणु
		dev_priv->max_gmr_ids =
			vmw_पढ़ो(dev_priv, SVGA_REG_GMR_MAX_IDS);
		dev_priv->max_gmr_pages =
			vmw_पढ़ो(dev_priv, SVGA_REG_GMRS_MAX_PAGES);
		dev_priv->memory_size =
			vmw_पढ़ो(dev_priv, SVGA_REG_MEMORY_SIZE);
		dev_priv->memory_size -= dev_priv->vram_size;
	पूर्ण अन्यथा अणु
		/*
		 * An arbitrary limit of 512MiB on surface
		 * memory. But all HWV8 hardware supports GMR2.
		 */
		dev_priv->memory_size = 512*1024*1024;
	पूर्ण
	dev_priv->max_mob_pages = 0;
	dev_priv->max_mob_size = 0;
	अगर (dev_priv->capabilities & SVGA_CAP_GBOBJECTS) अणु
		uपूर्णांक64_t mem_size;

		अगर (dev_priv->capabilities2 & SVGA_CAP2_GB_MEMSIZE_2)
			mem_size = vmw_पढ़ो(dev_priv,
					    SVGA_REG_GBOBJECT_MEM_SIZE_KB);
		अन्यथा
			mem_size =
				vmw_पढ़ो(dev_priv,
					 SVGA_REG_SUGGESTED_GBOBJECT_MEM_SIZE_KB);

		/*
		 * Workaround क्रम low memory 2D VMs to compensate क्रम the
		 * allocation taken by fbdev
		 */
		अगर (!(dev_priv->capabilities & SVGA_CAP_3D))
			mem_size *= 3;

		dev_priv->max_mob_pages = mem_size * 1024 / PAGE_SIZE;
		dev_priv->prim_bb_mem =
			vmw_पढ़ो(dev_priv,
				 SVGA_REG_MAX_PRIMARY_BOUNDING_BOX_MEM);
		dev_priv->max_mob_size =
			vmw_पढ़ो(dev_priv, SVGA_REG_MOB_MAX_SIZE);
		dev_priv->stdu_max_width =
			vmw_पढ़ो(dev_priv, SVGA_REG_SCREENTARGET_MAX_WIDTH);
		dev_priv->stdu_max_height =
			vmw_पढ़ो(dev_priv, SVGA_REG_SCREENTARGET_MAX_HEIGHT);

		vmw_ग_लिखो(dev_priv, SVGA_REG_DEV_CAP,
			  SVGA3D_DEVCAP_MAX_TEXTURE_WIDTH);
		dev_priv->texture_max_width = vmw_पढ़ो(dev_priv,
						       SVGA_REG_DEV_CAP);
		vmw_ग_लिखो(dev_priv, SVGA_REG_DEV_CAP,
			  SVGA3D_DEVCAP_MAX_TEXTURE_HEIGHT);
		dev_priv->texture_max_height = vmw_पढ़ो(dev_priv,
							SVGA_REG_DEV_CAP);
	पूर्ण अन्यथा अणु
		dev_priv->texture_max_width = 8192;
		dev_priv->texture_max_height = 8192;
		dev_priv->prim_bb_mem = dev_priv->vram_size;
	पूर्ण

	vmw_prपूर्णांक_capabilities(dev_priv->capabilities);
	अगर (dev_priv->capabilities & SVGA_CAP_CAP2_REGISTER)
		vmw_prपूर्णांक_capabilities2(dev_priv->capabilities2);

	ret = vmw_dma_masks(dev_priv);
	अगर (unlikely(ret != 0))
		जाओ out_err0;

	dma_set_max_seg_size(dev_priv->drm.dev, U32_MAX);

	अगर (dev_priv->capabilities & SVGA_CAP_GMR2) अणु
		DRM_INFO("Max GMR ids is %u\n",
			 (अचिन्हित)dev_priv->max_gmr_ids);
		DRM_INFO("Max number of GMR pages is %u\n",
			 (अचिन्हित)dev_priv->max_gmr_pages);
		DRM_INFO("Max dedicated hypervisor surface memory is %u kiB\n",
			 (अचिन्हित)dev_priv->memory_size / 1024);
	पूर्ण
	DRM_INFO("Maximum display memory size is %llu kiB\n",
		 (uपूर्णांक64_t)dev_priv->prim_bb_mem / 1024);

	/* Need mmio memory to check क्रम fअगरo pitchlock cap. */
	अगर (!(dev_priv->capabilities & SVGA_CAP_DISPLAY_TOPOLOGY) &&
	    !(dev_priv->capabilities & SVGA_CAP_PITCHLOCK) &&
	    !vmw_fअगरo_have_pitchlock(dev_priv)) अणु
		ret = -ENOSYS;
		DRM_ERROR("Hardware has no pitchlock\n");
		जाओ out_err0;
	पूर्ण

	dev_priv->tdev = tपंचांग_object_device_init(&tपंचांग_mem_glob, 12,
						&vmw_prime_dmabuf_ops);

	अगर (unlikely(dev_priv->tdev == शून्य)) अणु
		DRM_ERROR("Unable to initialize TTM object management.\n");
		ret = -ENOMEM;
		जाओ out_err0;
	पूर्ण

	अगर (dev_priv->capabilities & SVGA_CAP_IRQMASK) अणु
		ret = vmw_irq_install(&dev_priv->drm, pdev->irq);
		अगर (ret != 0) अणु
			DRM_ERROR("Failed installing irq: %d\n", ret);
			जाओ out_no_irq;
		पूर्ण
	पूर्ण

	dev_priv->fman = vmw_fence_manager_init(dev_priv);
	अगर (unlikely(dev_priv->fman == शून्य)) अणु
		ret = -ENOMEM;
		जाओ out_no_fman;
	पूर्ण

	drm_vma_offset_manager_init(&dev_priv->vma_manager,
				    DRM_खाता_PAGE_OFFSET_START,
				    DRM_खाता_PAGE_OFFSET_SIZE);
	ret = tपंचांग_device_init(&dev_priv->bdev, &vmw_bo_driver,
			      dev_priv->drm.dev,
			      dev_priv->drm.anon_inode->i_mapping,
			      &dev_priv->vma_manager,
			      dev_priv->map_mode == vmw_dma_alloc_coherent,
			      false);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed initializing TTM buffer object driver.\n");
		जाओ out_no_bdev;
	पूर्ण

	/*
	 * Enable VRAM, but initially करोn't use it until SVGA is enabled and
	 * unhidden.
	 */

	ret = vmw_vram_manager_init(dev_priv);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed initializing memory manager for VRAM.\n");
		जाओ out_no_vram;
	पूर्ण

	/*
	 * "Guest Memory Regions" is an aperture like feature with
	 *  one slot per bo. There is an upper limit of the number of
	 *  slots as well as the bo size.
	 */
	dev_priv->has_gmr = true;
	/* TODO: This is most likely not correct */
	अगर (((dev_priv->capabilities & (SVGA_CAP_GMR | SVGA_CAP_GMR2)) == 0) ||
	    refuse_dma ||
	    vmw_gmrid_man_init(dev_priv, VMW_PL_GMR) != 0) अणु
		DRM_INFO("No GMR memory available. "
			 "Graphics memory resources are very limited.\n");
		dev_priv->has_gmr = false;
	पूर्ण

	अगर (dev_priv->capabilities & SVGA_CAP_GBOBJECTS && !refuse_dma) अणु
		dev_priv->has_mob = true;

		अगर (vmw_gmrid_man_init(dev_priv, VMW_PL_MOB) != 0) अणु
			DRM_INFO("No MOB memory available. "
				 "3D will be disabled.\n");
			dev_priv->has_mob = false;
		पूर्ण
	पूर्ण

	अगर (dev_priv->has_mob && (dev_priv->capabilities & SVGA_CAP_DX)) अणु
		spin_lock(&dev_priv->cap_lock);
		vmw_ग_लिखो(dev_priv, SVGA_REG_DEV_CAP, SVGA3D_DEVCAP_DXCONTEXT);
		अगर (vmw_पढ़ो(dev_priv, SVGA_REG_DEV_CAP))
			dev_priv->sm_type = VMW_SM_4;
		spin_unlock(&dev_priv->cap_lock);
	पूर्ण

	vmw_validation_mem_init_tपंचांग(dev_priv, VMWGFX_VALIDATION_MEM_GRAN);

	/* SVGA_CAP2_DX2 (DefineGBSurface_v3) is needed क्रम SM4_1 support */
	अगर (has_sm4_context(dev_priv) &&
	    (dev_priv->capabilities2 & SVGA_CAP2_DX2)) अणु
		vmw_ग_लिखो(dev_priv, SVGA_REG_DEV_CAP, SVGA3D_DEVCAP_SM41);

		अगर (vmw_पढ़ो(dev_priv, SVGA_REG_DEV_CAP))
			dev_priv->sm_type = VMW_SM_4_1;

		अगर (has_sm4_1_context(dev_priv) &&
		    (dev_priv->capabilities2 & SVGA_CAP2_DX3)) अणु
			vmw_ग_लिखो(dev_priv, SVGA_REG_DEV_CAP, SVGA3D_DEVCAP_SM5);
			अगर (vmw_पढ़ो(dev_priv, SVGA_REG_DEV_CAP))
				dev_priv->sm_type = VMW_SM_5;
		पूर्ण
	पूर्ण

	ret = vmw_kms_init(dev_priv);
	अगर (unlikely(ret != 0))
		जाओ out_no_kms;
	vmw_overlay_init(dev_priv);

	ret = vmw_request_device(dev_priv);
	अगर (ret)
		जाओ out_no_fअगरo;

	अगर (dev_priv->sm_type == VMW_SM_5)
		DRM_INFO("SM5 support available.\n");
	अगर (dev_priv->sm_type == VMW_SM_4_1)
		DRM_INFO("SM4_1 support available.\n");
	अगर (dev_priv->sm_type == VMW_SM_4)
		DRM_INFO("SM4 support available.\n");

	snम_लिखो(host_log, माप(host_log), "vmwgfx: Module Version: %d.%d.%d",
		VMWGFX_DRIVER_MAJOR, VMWGFX_DRIVER_MINOR,
		VMWGFX_DRIVER_PATCHLEVEL);
	vmw_host_log(host_log);

	अगर (dev_priv->enable_fb) अणु
		vmw_fअगरo_resource_inc(dev_priv);
		vmw_svga_enable(dev_priv);
		vmw_fb_init(dev_priv);
	पूर्ण

	dev_priv->pm_nb.notअगरier_call = vmwgfx_pm_notअगरier;
	रेजिस्टर_pm_notअगरier(&dev_priv->pm_nb);

	वापस 0;

out_no_fअगरo:
	vmw_overlay_बंद(dev_priv);
	vmw_kms_बंद(dev_priv);
out_no_kms:
	अगर (dev_priv->has_mob)
		vmw_gmrid_man_fini(dev_priv, VMW_PL_MOB);
	अगर (dev_priv->has_gmr)
		vmw_gmrid_man_fini(dev_priv, VMW_PL_GMR);
	vmw_vram_manager_fini(dev_priv);
out_no_vram:
	tपंचांग_device_fini(&dev_priv->bdev);
out_no_bdev:
	vmw_fence_manager_takeकरोwn(dev_priv->fman);
out_no_fman:
	अगर (dev_priv->capabilities & SVGA_CAP_IRQMASK)
		vmw_irq_uninstall(&dev_priv->drm);
out_no_irq:
	tपंचांग_object_device_release(&dev_priv->tdev);
out_err0:
	क्रम (i = vmw_res_context; i < vmw_res_max; ++i)
		idr_destroy(&dev_priv->res_idr[i]);

	अगर (dev_priv->ctx.staged_bindings)
		vmw_binding_state_मुक्त(dev_priv->ctx.staged_bindings);
out_no_pci_or_version:
	pci_release_regions(pdev);
	वापस ret;
पूर्ण

अटल व्योम vmw_driver_unload(काष्ठा drm_device *dev)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	क्रमागत vmw_res_type i;

	unरेजिस्टर_pm_notअगरier(&dev_priv->pm_nb);

	अगर (dev_priv->ctx.res_ht_initialized)
		drm_ht_हटाओ(&dev_priv->ctx.res_ht);
	vमुक्त(dev_priv->ctx.cmd_bounce);
	अगर (dev_priv->enable_fb) अणु
		vmw_fb_off(dev_priv);
		vmw_fb_बंद(dev_priv);
		vmw_fअगरo_resource_dec(dev_priv);
		vmw_svga_disable(dev_priv);
	पूर्ण

	vmw_kms_बंद(dev_priv);
	vmw_overlay_बंद(dev_priv);

	अगर (dev_priv->has_gmr)
		vmw_gmrid_man_fini(dev_priv, VMW_PL_GMR);

	vmw_release_device_early(dev_priv);
	अगर (dev_priv->has_mob)
		vmw_gmrid_man_fini(dev_priv, VMW_PL_MOB);
	vmw_vram_manager_fini(dev_priv);
	tपंचांग_device_fini(&dev_priv->bdev);
	drm_vma_offset_manager_destroy(&dev_priv->vma_manager);
	vmw_release_device_late(dev_priv);
	vmw_fence_manager_takeकरोwn(dev_priv->fman);
	अगर (dev_priv->capabilities & SVGA_CAP_IRQMASK)
		vmw_irq_uninstall(&dev_priv->drm);

	tपंचांग_object_device_release(&dev_priv->tdev);
	अगर (dev_priv->ctx.staged_bindings)
		vmw_binding_state_मुक्त(dev_priv->ctx.staged_bindings);

	क्रम (i = vmw_res_context; i < vmw_res_max; ++i)
		idr_destroy(&dev_priv->res_idr[i]);

	pci_release_regions(pdev);
पूर्ण

अटल व्योम vmw_postबंद(काष्ठा drm_device *dev,
			 काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_fpriv *vmw_fp = vmw_fpriv(file_priv);

	tपंचांग_object_file_release(&vmw_fp->tfile);
	kमुक्त(vmw_fp);
पूर्ण

अटल पूर्णांक vmw_driver_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा vmw_fpriv *vmw_fp;
	पूर्णांक ret = -ENOMEM;

	vmw_fp = kzalloc(माप(*vmw_fp), GFP_KERNEL);
	अगर (unlikely(!vmw_fp))
		वापस ret;

	vmw_fp->tfile = tपंचांग_object_file_init(dev_priv->tdev, 10);
	अगर (unlikely(vmw_fp->tfile == शून्य))
		जाओ out_no_tfile;

	file_priv->driver_priv = vmw_fp;

	वापस 0;

out_no_tfile:
	kमुक्त(vmw_fp);
	वापस ret;
पूर्ण

अटल दीर्घ vmw_generic_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg,
			      दीर्घ (*ioctl_func)(काष्ठा file *, अचिन्हित पूर्णांक,
						 अचिन्हित दीर्घ))
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा drm_device *dev = file_priv->minor->dev;
	अचिन्हित पूर्णांक nr = DRM_IOCTL_NR(cmd);
	अचिन्हित पूर्णांक flags;

	/*
	 * Do extra checking on driver निजी ioctls.
	 */

	अगर ((nr >= DRM_COMMAND_BASE) && (nr < DRM_COMMAND_END)
	    && (nr < DRM_COMMAND_BASE + dev->driver->num_ioctls)) अणु
		स्थिर काष्ठा drm_ioctl_desc *ioctl =
			&vmw_ioctls[nr - DRM_COMMAND_BASE];

		अगर (nr == DRM_COMMAND_BASE + DRM_VMW_EXECBUF) अणु
			वापस ioctl_func(filp, cmd, arg);
		पूर्ण अन्यथा अगर (nr == DRM_COMMAND_BASE + DRM_VMW_UPDATE_LAYOUT) अणु
			अगर (!drm_is_current_master(file_priv) &&
			    !capable(CAP_SYS_ADMIN))
				वापस -EACCES;
		पूर्ण

		अगर (unlikely(ioctl->cmd != cmd))
			जाओ out_io_encoding;

		flags = ioctl->flags;
	पूर्ण अन्यथा अगर (!drm_ioctl_flags(nr, &flags))
		वापस -EINVAL;

	वापस ioctl_func(filp, cmd, arg);

out_io_encoding:
	DRM_ERROR("Invalid command format, ioctl %d\n",
		  nr - DRM_COMMAND_BASE);

	वापस -EINVAL;
पूर्ण

अटल दीर्घ vmw_unlocked_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	वापस vmw_generic_ioctl(filp, cmd, arg, &drm_ioctl);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ vmw_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	वापस vmw_generic_ioctl(filp, cmd, arg, &drm_compat_ioctl);
पूर्ण
#पूर्ण_अगर

अटल व्योम vmw_master_set(काष्ठा drm_device *dev,
			   काष्ठा drm_file *file_priv,
			   bool from_खोलो)
अणु
	/*
	 * Inक्रमm a new master that the layout may have changed जबतक
	 * it was gone.
	 */
	अगर (!from_खोलो)
		drm_sysfs_hotplug_event(dev);
पूर्ण

अटल व्योम vmw_master_drop(काष्ठा drm_device *dev,
			    काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);

	vmw_kms_legacy_hotspot_clear(dev_priv);
	अगर (!dev_priv->enable_fb)
		vmw_svga_disable(dev_priv);
पूर्ण

/**
 * __vmw_svga_enable - Enable SVGA mode, FIFO and use of VRAM.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठा.
 * Needs the reservation sem to be held in non-exclusive mode.
 */
अटल व्योम __vmw_svga_enable(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&dev_priv->bdev, TTM_PL_VRAM);

	अगर (!tपंचांग_resource_manager_used(man)) अणु
		vmw_ग_लिखो(dev_priv, SVGA_REG_ENABLE, SVGA_REG_ENABLE);
		tपंचांग_resource_manager_set_used(man, true);
	पूर्ण
पूर्ण

/**
 * vmw_svga_enable - Enable SVGA mode, FIFO and use of VRAM.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठा.
 */
व्योम vmw_svga_enable(काष्ठा vmw_निजी *dev_priv)
अणु
	(व्योम) tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, false);
	__vmw_svga_enable(dev_priv);
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
पूर्ण

/**
 * __vmw_svga_disable - Disable SVGA mode and use of VRAM.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठा.
 * Needs the reservation sem to be held in exclusive mode.
 * Will not empty VRAM. VRAM must be emptied by caller.
 */
अटल व्योम __vmw_svga_disable(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&dev_priv->bdev, TTM_PL_VRAM);

	अगर (tपंचांग_resource_manager_used(man)) अणु
		tपंचांग_resource_manager_set_used(man, false);
		vmw_ग_लिखो(dev_priv, SVGA_REG_ENABLE,
			  SVGA_REG_ENABLE_HIDE |
			  SVGA_REG_ENABLE_ENABLE);
	पूर्ण
पूर्ण

/**
 * vmw_svga_disable - Disable SVGA_MODE, and use of VRAM. Keep the fअगरo
 * running.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठा.
 * Will empty VRAM.
 */
व्योम vmw_svga_disable(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&dev_priv->bdev, TTM_PL_VRAM);
	/*
	 * Disabling SVGA will turn off device modesetting capabilities, so
	 * notअगरy KMS about that so that it करोesn't cache atomic state that
	 * isn't valid anymore, क्रम example crtcs turned on.
	 * Strictly we'd want to करो this under the SVGA lock (or an SVGA mutex),
	 * but vmw_kms_lost_device() takes the reservation sem and thus we'll
	 * end up with lock order reversal. Thus, a master may actually perक्रमm
	 * a new modeset just after we call vmw_kms_lost_device() and race with
	 * vmw_svga_disable(), but that should at worst cause atomic KMS state
	 * to be inconsistent with the device, causing modesetting problems.
	 *
	 */
	vmw_kms_lost_device(&dev_priv->drm);
	tपंचांग_ग_लिखो_lock(&dev_priv->reservation_sem, false);
	अगर (tपंचांग_resource_manager_used(man)) अणु
		अगर (tपंचांग_resource_manager_evict_all(&dev_priv->bdev, man))
			DRM_ERROR("Failed evicting VRAM buffers.\n");
		tपंचांग_resource_manager_set_used(man, false);
		vmw_ग_लिखो(dev_priv, SVGA_REG_ENABLE,
			  SVGA_REG_ENABLE_HIDE |
			  SVGA_REG_ENABLE_ENABLE);
	पूर्ण
	tपंचांग_ग_लिखो_unlock(&dev_priv->reservation_sem);
पूर्ण

अटल व्योम vmw_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	tपंचांग_mem_global_release(&tपंचांग_mem_glob);
	drm_dev_unरेजिस्टर(dev);
	vmw_driver_unload(dev);
पूर्ण

अटल अचिन्हित दीर्घ
vmw_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ uaddr,
		      अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
		      अचिन्हित दीर्घ flags)
अणु
	काष्ठा drm_file *file_priv = file->निजी_data;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(file_priv->minor->dev);

	वापस drm_get_unmapped_area(file, uaddr, len, pgoff, flags,
				     &dev_priv->vma_manager);
पूर्ण

अटल पूर्णांक vmwgfx_pm_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			      व्योम *ptr)
अणु
	काष्ठा vmw_निजी *dev_priv =
		container_of(nb, काष्ठा vmw_निजी, pm_nb);

	चयन (val) अणु
	हाल PM_HIBERNATION_PREPARE:
		/*
		 * Take the reservation sem in ग_लिखो mode, which will make sure
		 * there are no other processes holding a buffer object
		 * reservation, meaning we should be able to evict all buffer
		 * objects अगर needed.
		 * Once user-space processes have been frozen, we can release
		 * the lock again.
		 */
		tपंचांग_suspend_lock(&dev_priv->reservation_sem);
		dev_priv->suspend_locked = true;
		अवरोध;
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_RESTORE:
		अगर (READ_ONCE(dev_priv->suspend_locked)) अणु
			dev_priv->suspend_locked = false;
			tपंचांग_suspend_unlock(&dev_priv->reservation_sem);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vmw_pci_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);

	अगर (dev_priv->refuse_hibernation)
		वापस -EBUSY;

	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);
	वापस 0;
पूर्ण

अटल पूर्णांक vmw_pci_resume(काष्ठा pci_dev *pdev)
अणु
	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	वापस pci_enable_device(pdev);
पूर्ण

अटल पूर्णांक vmw_pm_suspend(काष्ठा device *kdev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kdev);
	काष्ठा pm_message dummy;

	dummy.event = 0;

	वापस vmw_pci_suspend(pdev, dummy);
पूर्ण

अटल पूर्णांक vmw_pm_resume(काष्ठा device *kdev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kdev);

	वापस vmw_pci_resume(pdev);
पूर्ण

अटल पूर्णांक vmw_pm_मुक्तze(काष्ठा device *kdev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kdev);
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	/*
	 * Unlock क्रम vmw_kms_suspend.
	 * No user-space processes should be running now.
	 */
	tपंचांग_suspend_unlock(&dev_priv->reservation_sem);
	ret = vmw_kms_suspend(&dev_priv->drm);
	अगर (ret) अणु
		tपंचांग_suspend_lock(&dev_priv->reservation_sem);
		DRM_ERROR("Failed to freeze modesetting.\n");
		वापस ret;
	पूर्ण
	अगर (dev_priv->enable_fb)
		vmw_fb_off(dev_priv);

	tपंचांग_suspend_lock(&dev_priv->reservation_sem);
	vmw_execbuf_release_pinned_bo(dev_priv);
	vmw_resource_evict_all(dev_priv);
	vmw_release_device_early(dev_priv);
	जबतक (tपंचांग_device_swapout(&dev_priv->bdev, &ctx, GFP_KERNEL) > 0);
	अगर (dev_priv->enable_fb)
		vmw_fअगरo_resource_dec(dev_priv);
	अगर (atomic_पढ़ो(&dev_priv->num_fअगरo_resources) != 0) अणु
		DRM_ERROR("Can't hibernate while 3D resources are active.\n");
		अगर (dev_priv->enable_fb)
			vmw_fअगरo_resource_inc(dev_priv);
		WARN_ON(vmw_request_device_late(dev_priv));
		dev_priv->suspend_locked = false;
		tपंचांग_suspend_unlock(&dev_priv->reservation_sem);
		अगर (dev_priv->suspend_state)
			vmw_kms_resume(dev);
		अगर (dev_priv->enable_fb)
			vmw_fb_on(dev_priv);
		वापस -EBUSY;
	पूर्ण

	vmw_fence_fअगरo_करोwn(dev_priv->fman);
	__vmw_svga_disable(dev_priv);

	vmw_release_device_late(dev_priv);
	वापस 0;
पूर्ण

अटल पूर्णांक vmw_pm_restore(काष्ठा device *kdev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(kdev);
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	पूर्णांक ret;

	vmw_ग_लिखो(dev_priv, SVGA_REG_ID, SVGA_ID_2);
	(व्योम) vmw_पढ़ो(dev_priv, SVGA_REG_ID);

	अगर (dev_priv->enable_fb)
		vmw_fअगरo_resource_inc(dev_priv);

	ret = vmw_request_device(dev_priv);
	अगर (ret)
		वापस ret;

	अगर (dev_priv->enable_fb)
		__vmw_svga_enable(dev_priv);

	vmw_fence_fअगरo_up(dev_priv->fman);
	dev_priv->suspend_locked = false;
	tपंचांग_suspend_unlock(&dev_priv->reservation_sem);
	अगर (dev_priv->suspend_state)
		vmw_kms_resume(&dev_priv->drm);

	अगर (dev_priv->enable_fb)
		vmw_fb_on(dev_priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vmw_pm_ops = अणु
	.मुक्तze = vmw_pm_मुक्तze,
	.thaw = vmw_pm_restore,
	.restore = vmw_pm_restore,
	.suspend = vmw_pm_suspend,
	.resume = vmw_pm_resume,
पूर्ण;

अटल स्थिर काष्ठा file_operations vmwgfx_driver_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = vmw_unlocked_ioctl,
	.mmap = vmw_mmap,
	.poll = vmw_fops_poll,
	.पढ़ो = vmw_fops_पढ़ो,
#अगर defined(CONFIG_COMPAT)
	.compat_ioctl = vmw_compat_ioctl,
#पूर्ण_अगर
	.llseek = noop_llseek,
	.get_unmapped_area = vmw_get_unmapped_area,
पूर्ण;

अटल स्थिर काष्ठा drm_driver driver = अणु
	.driver_features =
	DRIVER_MODESET | DRIVER_RENDER | DRIVER_ATOMIC,
	.ioctls = vmw_ioctls,
	.num_ioctls = ARRAY_SIZE(vmw_ioctls),
	.master_set = vmw_master_set,
	.master_drop = vmw_master_drop,
	.खोलो = vmw_driver_खोलो,
	.postबंद = vmw_postबंद,

	.dumb_create = vmw_dumb_create,
	.dumb_map_offset = vmw_dumb_map_offset,
	.dumb_destroy = vmw_dumb_destroy,

	.prime_fd_to_handle = vmw_prime_fd_to_handle,
	.prime_handle_to_fd = vmw_prime_handle_to_fd,

	.fops = &vmwgfx_driver_fops,
	.name = VMWGFX_DRIVER_NAME,
	.desc = VMWGFX_DRIVER_DESC,
	.date = VMWGFX_DRIVER_DATE,
	.major = VMWGFX_DRIVER_MAJOR,
	.minor = VMWGFX_DRIVER_MINOR,
	.patchlevel = VMWGFX_DRIVER_PATCHLEVEL
पूर्ण;

अटल काष्ठा pci_driver vmw_pci_driver = अणु
	.name = VMWGFX_DRIVER_NAME,
	.id_table = vmw_pci_id_list,
	.probe = vmw_probe,
	.हटाओ = vmw_हटाओ,
	.driver = अणु
		.pm = &vmw_pm_ops
	पूर्ण
पूर्ण;

अटल पूर्णांक vmw_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा vmw_निजी *vmw;
	पूर्णांक ret;

	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "svgadrmfb");
	अगर (ret)
		वापस ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	vmw = devm_drm_dev_alloc(&pdev->dev, &driver,
				 काष्ठा vmw_निजी, drm);
	अगर (IS_ERR(vmw))
		वापस PTR_ERR(vmw);

	pci_set_drvdata(pdev, &vmw->drm);

	ret = tपंचांग_mem_global_init(&tपंचांग_mem_glob, &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = vmw_driver_load(vmw, ent->device);
	अगर (ret)
		वापस ret;

	ret = drm_dev_रेजिस्टर(&vmw->drm, 0);
	अगर (ret) अणु
		vmw_driver_unload(&vmw->drm);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init vmwgfx_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (vgacon_text_क्रमce())
		वापस -EINVAL;

	ret = pci_रेजिस्टर_driver(&vmw_pci_driver);
	अगर (ret)
		DRM_ERROR("Failed initializing DRM.\n");
	वापस ret;
पूर्ण

अटल व्योम __निकास vmwgfx_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&vmw_pci_driver);
पूर्ण

module_init(vmwgfx_init);
module_निकास(vmwgfx_निकास);

MODULE_AUTHOR("VMware Inc. and others");
MODULE_DESCRIPTION("Standalone drm driver for the VMware SVGA device");
MODULE_LICENSE("GPL and additional rights");
MODULE_VERSION(__stringअगरy(VMWGFX_DRIVER_MAJOR) "."
	       __stringअगरy(VMWGFX_DRIVER_MINOR) "."
	       __stringअगरy(VMWGFX_DRIVER_PATCHLEVEL) "."
	       "0");
