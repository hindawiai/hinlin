<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2007-2011, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/tty.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>

#समावेश "framebuffer.h"
#समावेश "gem.h"
#समावेश "gtt.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

अटल स्थिर काष्ठा drm_framebuffer_funcs psb_fb_funcs = अणु
	.destroy = drm_gem_fb_destroy,
	.create_handle = drm_gem_fb_create_handle,
पूर्ण;

#घोषणा CMAP_TOHW(_val, _width) ((((_val) << (_width)) + 0x7FFF - (_val)) >> 16)

अटल पूर्णांक psbfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_framebuffer *fb = fb_helper->fb;
	uपूर्णांक32_t v;

	अगर (!fb)
		वापस -ENOMEM;

	अगर (regno > 255)
		वापस 1;

	red = CMAP_TOHW(red, info->var.red.length);
	blue = CMAP_TOHW(blue, info->var.blue.length);
	green = CMAP_TOHW(green, info->var.green.length);
	transp = CMAP_TOHW(transp, info->var.transp.length);

	v = (red << info->var.red.offset) |
	    (green << info->var.green.offset) |
	    (blue << info->var.blue.offset) |
	    (transp << info->var.transp.offset);

	अगर (regno < 16) अणु
		चयन (fb->क्रमmat->cpp[0] * 8) अणु
		हाल 16:
			((uपूर्णांक32_t *) info->pseuकरो_palette)[regno] = v;
			अवरोध;
		हाल 24:
		हाल 32:
			((uपूर्णांक32_t *) info->pseuकरो_palette)[regno] = v;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल vm_fault_t psbfb_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_framebuffer *fb = vma->vm_निजी_data;
	काष्ठा drm_device *dev = fb->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gtt_range *gtt = to_gtt_range(fb->obj[0]);
	पूर्णांक page_num;
	पूर्णांक i;
	अचिन्हित दीर्घ address;
	vm_fault_t ret = VM_FAULT_SIGBUS;
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ phys_addr = (अचिन्हित दीर्घ)dev_priv->stolen_base +
				  gtt->offset;

	page_num = vma_pages(vma);
	address = vmf->address - (vmf->pgoff << PAGE_SHIFT);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	क्रम (i = 0; i < page_num; i++) अणु
		pfn = (phys_addr >> PAGE_SHIFT);

		ret = vmf_insert_mixed(vma, address,
				__pfn_to_pfn_t(pfn, PFN_DEV));
		अगर (unlikely(ret & VM_FAULT_ERROR))
			अवरोध;
		address += PAGE_SIZE;
		phys_addr += PAGE_SIZE;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम psbfb_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
पूर्ण

अटल व्योम psbfb_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा psbfb_vm_ops = अणु
	.fault	= psbfb_vm_fault,
	.खोलो	= psbfb_vm_खोलो,
	.बंद	= psbfb_vm_बंद
पूर्ण;

अटल पूर्णांक psbfb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_fb_helper *fb_helper = info->par;
	काष्ठा drm_framebuffer *fb = fb_helper->fb;

	अगर (vma->vm_pgoff != 0)
		वापस -EINVAL;
	अगर (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		वापस -EINVAL;

	/*
	 * If this is a GEM object then info->screen_base is the भव
	 * kernel remapping of the object. FIXME: Review अगर this is
	 * suitable क्रम our mmap work
	 */
	vma->vm_ops = &psbfb_vm_ops;
	vma->vm_निजी_data = (व्योम *)fb;
	vma->vm_flags |= VM_IO | VM_MIXEDMAP | VM_DONTEXPAND | VM_DONTDUMP;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops psbfb_unaccel_ops = अणु
	.owner = THIS_MODULE,
	DRM_FB_HELPER_DEFAULT_OPS,
	.fb_setcolreg = psbfb_setcolreg,
	.fb_fillrect = drm_fb_helper_cfb_fillrect,
	.fb_copyarea = drm_fb_helper_cfb_copyarea,
	.fb_imageblit = drm_fb_helper_cfb_imageblit,
	.fb_mmap = psbfb_mmap,
पूर्ण;

/**
 *	psb_framebuffer_init	-	initialize a framebuffer
 *	@dev: our DRM device
 *	@fb: framebuffer to set up
 *	@mode_cmd: mode description
 *	@obj: backing object
 *
 *	Configure and fill in the boilerplate क्रम our frame buffer. Return
 *	0 on success or an error code अगर we fail.
 */
अटल पूर्णांक psb_framebuffer_init(काष्ठा drm_device *dev,
					काष्ठा drm_framebuffer *fb,
					स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
					काष्ठा drm_gem_object *obj)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;
	पूर्णांक ret;

	/*
	 * Reject unknown क्रमmats, YUV क्रमmats, and क्रमmats with more than
	 * 4 bytes per pixel.
	 */
	info = drm_get_क्रमmat_info(dev, mode_cmd);
	अगर (!info || !info->depth || info->cpp[0] > 4)
		वापस -EINVAL;

	अगर (mode_cmd->pitches[0] & 63)
		वापस -EINVAL;

	drm_helper_mode_fill_fb_काष्ठा(dev, fb, mode_cmd);
	fb->obj[0] = obj;
	ret = drm_framebuffer_init(dev, fb, &psb_fb_funcs);
	अगर (ret) अणु
		dev_err(dev->dev, "framebuffer init failed: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	psb_framebuffer_create	-	create a framebuffer backed by gt
 *	@dev: our DRM device
 *	@mode_cmd: the description of the requested mode
 *	@obj: the backing object
 *
 *	Create a framebuffer object backed by the gt, and fill in the
 *	boilerplate required
 *
 *	TODO: review object references
 */

अटल काष्ठा drm_framebuffer *psb_framebuffer_create
			(काष्ठा drm_device *dev,
			 स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			 काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_framebuffer *fb;
	पूर्णांक ret;

	fb = kzalloc(माप(*fb), GFP_KERNEL);
	अगर (!fb)
		वापस ERR_PTR(-ENOMEM);

	ret = psb_framebuffer_init(dev, fb, mode_cmd, obj);
	अगर (ret) अणु
		kमुक्त(fb);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस fb;
पूर्ण

/**
 *	psbfb_alloc		-	allocate frame buffer memory
 *	@dev: the DRM device
 *	@aligned_size: space needed
 *
 *	Allocate the frame buffer. In the usual हाल we get a GTT range that
 *	is stolen memory backed and lअगरe is simple. If there isn't sufficient
 *	we fail as we करोn't have the भव mapping space to really vmap it
 *	and the kernel console code can't handle non linear framebuffers.
 *
 *	Re-address this as and अगर the framebuffer layer grows this ability.
 */
अटल काष्ठा gtt_range *psbfb_alloc(काष्ठा drm_device *dev, पूर्णांक aligned_size)
अणु
	काष्ठा gtt_range *backing;
	/* Begin by trying to use stolen memory backing */
	backing = psb_gtt_alloc_range(dev, aligned_size, "fb", 1, PAGE_SIZE);
	अगर (backing) अणु
		backing->gem.funcs = &psb_gem_object_funcs;
		drm_gem_निजी_object_init(dev, &backing->gem, aligned_size);
		वापस backing;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 *	psbfb_create		-	create a framebuffer
 *	@fb_helper: the framebuffer helper
 *	@sizes: specअगरication of the layout
 *
 *	Create a framebuffer to the specअगरications provided
 */
अटल पूर्णांक psbfb_create(काष्ठा drm_fb_helper *fb_helper,
				काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा drm_device *dev = fb_helper->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा fb_info *info;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_mode_fb_cmd2 mode_cmd;
	पूर्णांक size;
	पूर्णांक ret;
	काष्ठा gtt_range *backing;
	u32 bpp, depth;

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;
	bpp = sizes->surface_bpp;
	depth = sizes->surface_depth;

	/* No 24bit packed */
	अगर (bpp == 24)
		bpp = 32;

	mode_cmd.pitches[0] = ALIGN(mode_cmd.width * DIV_ROUND_UP(bpp, 8), 64);

	size = mode_cmd.pitches[0] * mode_cmd.height;
	size = ALIGN(size, PAGE_SIZE);

	/* Allocate the framebuffer in the GTT with stolen page backing */
	backing = psbfb_alloc(dev, size);
	अगर (backing == शून्य)
		वापस -ENOMEM;

	स_रखो(dev_priv->vram_addr + backing->offset, 0, size);

	info = drm_fb_helper_alloc_fbi(fb_helper);
	अगर (IS_ERR(info)) अणु
		ret = PTR_ERR(info);
		जाओ out;
	पूर्ण

	mode_cmd.pixel_क्रमmat = drm_mode_legacy_fb_क्रमmat(bpp, depth);

	fb = psb_framebuffer_create(dev, &mode_cmd, &backing->gem);
	अगर (IS_ERR(fb)) अणु
		ret = PTR_ERR(fb);
		जाओ out;
	पूर्ण

	fb_helper->fb = fb;

	info->fbops = &psbfb_unaccel_ops;

	info->fix.smem_start = dev->mode_config.fb_base;
	info->fix.smem_len = size;
	info->fix.ywrapstep = 0;
	info->fix.ypanstep = 0;

	/* Accessed stolen memory directly */
	info->screen_base = dev_priv->vram_addr + backing->offset;
	info->screen_size = size;

	अगर (dev_priv->gtt.stolen_size) अणु
		info->apertures->ranges[0].base = dev->mode_config.fb_base;
		info->apertures->ranges[0].size = dev_priv->gtt.stolen_size;
	पूर्ण

	drm_fb_helper_fill_info(info, fb_helper, sizes);

	info->fix.mmio_start = pci_resource_start(pdev, 0);
	info->fix.mmio_len = pci_resource_len(pdev, 0);

	/* Use शेष scratch pixmap (info->pixmap.flags = FB_PIXMAP_SYSTEM) */

	dev_dbg(dev->dev, "allocated %dx%d fb\n", fb->width, fb->height);

	वापस 0;
out:
	psb_gtt_मुक्त_range(dev, backing);
	वापस ret;
पूर्ण

/**
 *	psb_user_framebuffer_create	-	create framebuffer
 *	@dev: our DRM device
 *	@filp: client file
 *	@cmd: mode request
 *
 *	Create a new framebuffer backed by a userspace GEM object
 */
अटल काष्ठा drm_framebuffer *psb_user_framebuffer_create
			(काष्ठा drm_device *dev, काष्ठा drm_file *filp,
			 स्थिर काष्ठा drm_mode_fb_cmd2 *cmd)
अणु
	काष्ठा drm_gem_object *obj;

	/*
	 *	Find the GEM object and thus the gtt range object that is
	 *	to back this space
	 */
	obj = drm_gem_object_lookup(filp, cmd->handles[0]);
	अगर (obj == शून्य)
		वापस ERR_PTR(-ENOENT);

	/* Let the core code करो all the work */
	वापस psb_framebuffer_create(dev, cmd, obj);
पूर्ण

अटल पूर्णांक psbfb_probe(काष्ठा drm_fb_helper *fb_helper,
				काष्ठा drm_fb_helper_surface_size *sizes)
अणु
	काष्ठा drm_device *dev = fb_helper->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अचिन्हित पूर्णांक fb_size;
	पूर्णांक bytespp;

	bytespp = sizes->surface_bpp / 8;
	अगर (bytespp == 3)	/* no 24bit packed */
		bytespp = 4;

	/* If the mode will not fit in 32bit then चयन to 16bit to get
	   a console on full resolution. The X mode setting server will
	   allocate its own 32bit GEM framebuffer */
	fb_size = ALIGN(sizes->surface_width * bytespp, 64) *
		  sizes->surface_height;
	fb_size = ALIGN(fb_size, PAGE_SIZE);

	अगर (fb_size > dev_priv->vram_stolen_size) अणु
                sizes->surface_bpp = 16;
                sizes->surface_depth = 16;
        पूर्ण

	वापस psbfb_create(fb_helper, sizes);
पूर्ण

अटल स्थिर काष्ठा drm_fb_helper_funcs psb_fb_helper_funcs = अणु
	.fb_probe = psbfb_probe,
पूर्ण;

अटल पूर्णांक psb_fbdev_destroy(काष्ठा drm_device *dev,
			     काष्ठा drm_fb_helper *fb_helper)
अणु
	काष्ठा drm_framebuffer *fb = fb_helper->fb;

	drm_fb_helper_unरेजिस्टर_fbi(fb_helper);

	drm_fb_helper_fini(fb_helper);
	drm_framebuffer_unरेजिस्टर_निजी(fb);
	drm_framebuffer_cleanup(fb);

	अगर (fb->obj[0])
		drm_gem_object_put(fb->obj[0]);
	kमुक्त(fb);

	वापस 0;
पूर्ण

पूर्णांक psb_fbdev_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_fb_helper *fb_helper;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक ret;

	fb_helper = kzalloc(माप(*fb_helper), GFP_KERNEL);
	अगर (!fb_helper) अणु
		dev_err(dev->dev, "no memory\n");
		वापस -ENOMEM;
	पूर्ण

	dev_priv->fb_helper = fb_helper;

	drm_fb_helper_prepare(dev, fb_helper, &psb_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, fb_helper);
	अगर (ret)
		जाओ मुक्त;

	/* disable all the possible outमाला_दो/crtcs beक्रमe entering KMS mode */
	drm_helper_disable_unused_functions(dev);

	ret = drm_fb_helper_initial_config(fb_helper, 32);
	अगर (ret)
		जाओ fini;

	वापस 0;

fini:
	drm_fb_helper_fini(fb_helper);
मुक्त:
	kमुक्त(fb_helper);
	वापस ret;
पूर्ण

अटल व्योम psb_fbdev_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	अगर (!dev_priv->fb_helper)
		वापस;

	psb_fbdev_destroy(dev, dev_priv->fb_helper);
	kमुक्त(dev_priv->fb_helper);
	dev_priv->fb_helper = शून्य;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs psb_mode_funcs = अणु
	.fb_create = psb_user_framebuffer_create,
	.output_poll_changed = drm_fb_helper_output_poll_changed,
पूर्ण;

अटल व्योम psb_setup_outमाला_दो(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा drm_connector *connector;

	drm_mode_create_scaling_mode_property(dev);

	/* It is ok क्रम this to fail - we just करोn't get backlight control */
	अगर (!dev_priv->backlight_property)
		dev_priv->backlight_property = drm_property_create_range(dev, 0,
							"backlight", 0, 100);
	dev_priv->ops->output_init(dev);

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list,
			    head) अणु
		काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
		काष्ठा drm_encoder *encoder = &gma_encoder->base;
		पूर्णांक crtc_mask = 0, clone_mask = 0;

		/* valid crtcs */
		चयन (gma_encoder->type) अणु
		हाल INTEL_OUTPUT_ANALOG:
			crtc_mask = (1 << 0);
			clone_mask = (1 << INTEL_OUTPUT_ANALOG);
			अवरोध;
		हाल INTEL_OUTPUT_SDVO:
			crtc_mask = dev_priv->ops->sdvo_mask;
			clone_mask = 0;
			अवरोध;
		हाल INTEL_OUTPUT_LVDS:
			crtc_mask = dev_priv->ops->lvds_mask;
			clone_mask = 0;
			अवरोध;
		हाल INTEL_OUTPUT_MIPI:
			crtc_mask = (1 << 0);
			clone_mask = 0;
			अवरोध;
		हाल INTEL_OUTPUT_MIPI2:
			crtc_mask = (1 << 2);
			clone_mask = 0;
			अवरोध;
		हाल INTEL_OUTPUT_HDMI:
			crtc_mask = dev_priv->ops->hdmi_mask;
			clone_mask = (1 << INTEL_OUTPUT_HDMI);
			अवरोध;
		हाल INTEL_OUTPUT_DISPLAYPORT:
			crtc_mask = (1 << 0) | (1 << 1);
			clone_mask = 0;
			अवरोध;
		हाल INTEL_OUTPUT_EDP:
			crtc_mask = (1 << 1);
			clone_mask = 0;
		पूर्ण
		encoder->possible_crtcs = crtc_mask;
		encoder->possible_clones =
		    gma_connector_clones(dev, clone_mask);
	पूर्ण
पूर्ण

व्योम psb_modeset_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	पूर्णांक i;

	drm_mode_config_init(dev);

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	dev->mode_config.funcs = &psb_mode_funcs;

	/* set memory base */
	/* Oaktrail and Poulsbo should use BAR 2*/
	pci_पढ़ो_config_dword(pdev, PSB_BSM, (u32 *)&(dev->mode_config.fb_base));

	/* num pipes is 2 क्रम PSB but 1 क्रम Mrst */
	क्रम (i = 0; i < dev_priv->num_pipe; i++)
		psb_पूर्णांकel_crtc_init(dev, i, mode_dev);

	dev->mode_config.max_width = 4096;
	dev->mode_config.max_height = 4096;

	psb_setup_outमाला_दो(dev);

	अगर (dev_priv->ops->errata)
	        dev_priv->ops->errata(dev);

        dev_priv->modeset = true;
पूर्ण

व्योम psb_modeset_cleanup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अगर (dev_priv->modeset) अणु
		drm_kms_helper_poll_fini(dev);
		psb_fbdev_fini(dev);
		drm_mode_config_cleanup(dev);
	पूर्ण
पूर्ण
