<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) Intel Corp. 2007.
 * All Rights Reserved.
 *
 * Intel funded Tungsten Graphics (http://www.tungstengraphics.com) to
 * develop this driver.
 *
 * This file is part of the Vermilion Range fb driver.
 *
 * Authors:
 *   Thomas Hellstrथघm <thomas-at-tungstengraphics-करोt-com>
 *   Michel Dथअnzer <michel-at-tungstengraphics-करोt-com>
 *   Alan Hourihane <alanh-at-tungstengraphics-करोt-com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/mmzone.h>

/* #घोषणा VERMILION_DEBUG */

#समावेश "vermilion.h"

#घोषणा MODULE_NAME "vmlfb"

#घोषणा VML_TOHW(_val, _width) ((((_val) << (_width)) + 0x7FFF - (_val)) >> 16)

अटल काष्ठा mutex vml_mutex;
अटल काष्ठा list_head global_no_mode;
अटल काष्ठा list_head global_has_mode;
अटल काष्ठा fb_ops vmlfb_ops;
अटल काष्ठा vml_sys *subsys = शून्य;
अटल अक्षर *vml_शेष_mode = "1024x768@60";
अटल स्थिर काष्ठा fb_videomode शेषmode = अणु
	शून्य, 60, 1024, 768, 12896, 144, 24, 29, 3, 136, 6,
	0, FB_VMODE_NONINTERLACED
पूर्ण;

अटल u32 vml_mem_requested = (10 * 1024 * 1024);
अटल u32 vml_mem_contig = (4 * 1024 * 1024);
अटल u32 vml_mem_min = (4 * 1024 * 1024);

अटल u32 vml_घड़ीs[] = अणु
	6750,
	13500,
	27000,
	29700,
	37125,
	54000,
	59400,
	74250,
	120000,
	148500
पूर्ण;

अटल u32 vml_num_घड़ीs = ARRAY_SIZE(vml_घड़ीs);

/*
 * Allocate a contiguous vram area and make its linear kernel map
 * uncached.
 */

अटल पूर्णांक vmlfb_alloc_vram_area(काष्ठा vram_area *va, अचिन्हित max_order,
				 अचिन्हित min_order)
अणु
	gfp_t flags;
	अचिन्हित दीर्घ i;

	max_order++;
	करो अणु
		/*
		 * Really try hard to get the needed memory.
		 * We need memory below the first 32MB, so we
		 * add the __GFP_DMA flag that guarantees that we are
		 * below the first 16MB.
		 */

		flags = __GFP_DMA | __GFP_HIGH | __GFP_KSWAPD_RECLAIM;
		va->logical =
			 __get_मुक्त_pages(flags, --max_order);
	पूर्ण जबतक (va->logical == 0 && max_order > min_order);

	अगर (!va->logical)
		वापस -ENOMEM;

	va->phys = virt_to_phys((व्योम *)va->logical);
	va->size = PAGE_SIZE << max_order;
	va->order = max_order;

	/*
	 * It seems like __get_मुक्त_pages only ups the usage count
	 * of the first page. This करोesn't work with fault mapping, so
	 * up the usage count once more (XXX: should use split_page or
	 * compound page).
	 */

	स_रखो((व्योम *)va->logical, 0x00, va->size);
	क्रम (i = va->logical; i < va->logical + va->size; i += PAGE_SIZE) अणु
		get_page(virt_to_page(i));
	पूर्ण

	/*
	 * Change caching policy of the linear kernel map to aव्योम
	 * mapping type conflicts with user-space mappings.
	 */
	set_pages_uc(virt_to_page(va->logical), va->size >> PAGE_SHIFT);

	prपूर्णांकk(KERN_DEBUG MODULE_NAME
	       ": Allocated %ld bytes vram area at 0x%08lx\n",
	       va->size, va->phys);

	वापस 0;
पूर्ण

/*
 * Free a contiguous vram area and reset its linear kernel map
 * mapping type.
 */

अटल व्योम vmlfb_मुक्त_vram_area(काष्ठा vram_area *va)
अणु
	अचिन्हित दीर्घ j;

	अगर (va->logical) अणु

		/*
		 * Reset the linear kernel map caching policy.
		 */

		set_pages_wb(virt_to_page(va->logical),
				 va->size >> PAGE_SHIFT);

		/*
		 * Decrease the usage count on the pages we've used
		 * to compensate क्रम upping when allocating.
		 */

		क्रम (j = va->logical; j < va->logical + va->size;
		     j += PAGE_SIZE) अणु
			(व्योम)put_page_testzero(virt_to_page(j));
		पूर्ण

		prपूर्णांकk(KERN_DEBUG MODULE_NAME
		       ": Freeing %ld bytes vram area at 0x%08lx\n",
		       va->size, va->phys);
		मुक्त_pages(va->logical, va->order);

		va->logical = 0;
	पूर्ण
पूर्ण

/*
 * Free allocated vram.
 */

अटल व्योम vmlfb_मुक्त_vram(काष्ठा vml_info *vinfo)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vinfo->num_areas; ++i) अणु
		vmlfb_मुक्त_vram_area(&vinfo->vram[i]);
	पूर्ण
	vinfo->num_areas = 0;
पूर्ण

/*
 * Allocate vram. Currently we try to allocate contiguous areas from the
 * __GFP_DMA zone and puzzle them together. A better approach would be to
 * allocate one contiguous area क्रम scanout and use one-page allocations क्रम
 * offscreen areas. This requires user-space and GPU भव mappings.
 */

अटल पूर्णांक vmlfb_alloc_vram(काष्ठा vml_info *vinfo,
			    माप_प्रकार requested,
			    माप_प्रकार min_total, माप_प्रकार min_contig)
अणु
	पूर्णांक i, j;
	पूर्णांक order;
	पूर्णांक contiguous;
	पूर्णांक err;
	काष्ठा vram_area *va;
	काष्ठा vram_area *va2;

	vinfo->num_areas = 0;
	क्रम (i = 0; i < VML_VRAM_AREAS; ++i) अणु
		va = &vinfo->vram[i];
		order = 0;

		जबतक (requested > (PAGE_SIZE << order) && order < MAX_ORDER)
			order++;

		err = vmlfb_alloc_vram_area(va, order, 0);

		अगर (err)
			अवरोध;

		अगर (i == 0) अणु
			vinfo->vram_start = va->phys;
			vinfo->vram_logical = (व्योम __iomem *) va->logical;
			vinfo->vram_contig_size = va->size;
			vinfo->num_areas = 1;
		पूर्ण अन्यथा अणु
			contiguous = 0;

			क्रम (j = 0; j < i; ++j) अणु
				va2 = &vinfo->vram[j];
				अगर (va->phys + va->size == va2->phys ||
				    va2->phys + va2->size == va->phys) अणु
					contiguous = 1;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (contiguous) अणु
				vinfo->num_areas++;
				अगर (va->phys < vinfo->vram_start) अणु
					vinfo->vram_start = va->phys;
					vinfo->vram_logical =
						(व्योम __iomem *)va->logical;
				पूर्ण
				vinfo->vram_contig_size += va->size;
			पूर्ण अन्यथा अणु
				vmlfb_मुक्त_vram_area(va);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (requested < va->size)
			अवरोध;
		अन्यथा
			requested -= va->size;
	पूर्ण

	अगर (vinfo->vram_contig_size > min_total &&
	    vinfo->vram_contig_size > min_contig) अणु

		prपूर्णांकk(KERN_DEBUG MODULE_NAME
		       ": Contiguous vram: %ld bytes at physical 0x%08lx.\n",
		       (अचिन्हित दीर्घ)vinfo->vram_contig_size,
		       (अचिन्हित दीर्घ)vinfo->vram_start);

		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_ERR MODULE_NAME
	       ": Could not allocate requested minimal amount of vram.\n");

	vmlfb_मुक्त_vram(vinfo);

	वापस -ENOMEM;
पूर्ण

/*
 * Find the GPU to use with our display controller.
 */

अटल पूर्णांक vmlfb_get_gpu(काष्ठा vml_par *par)
अणु
	mutex_lock(&vml_mutex);

	par->gpu = pci_get_device(PCI_VENDOR_ID_INTEL, VML_DEVICE_GPU, शून्य);

	अगर (!par->gpu) अणु
		mutex_unlock(&vml_mutex);
		वापस -ENODEV;
	पूर्ण

	mutex_unlock(&vml_mutex);

	अगर (pci_enable_device(par->gpu) < 0)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * Find a contiguous vram area that contains a given offset from vram start.
 */
अटल पूर्णांक vmlfb_vram_offset(काष्ठा vml_info *vinfo, अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ aoffset;
	अचिन्हित i;

	क्रम (i = 0; i < vinfo->num_areas; ++i) अणु
		aoffset = offset - (vinfo->vram[i].phys - vinfo->vram_start);

		अगर (aoffset < vinfo->vram[i].size) अणु
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * Remap the MMIO रेजिस्टर spaces of the VDC and the GPU.
 */

अटल पूर्णांक vmlfb_enable_mmio(काष्ठा vml_par *par)
अणु
	पूर्णांक err;

	par->vdc_mem_base = pci_resource_start(par->vdc, 0);
	par->vdc_mem_size = pci_resource_len(par->vdc, 0);
	अगर (!request_mem_region(par->vdc_mem_base, par->vdc_mem_size, "vmlfb")) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME
		       ": Could not claim display controller MMIO.\n");
		वापस -EBUSY;
	पूर्ण
	par->vdc_mem = ioremap(par->vdc_mem_base, par->vdc_mem_size);
	अगर (par->vdc_mem == शून्य) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME
		       ": Could not map display controller MMIO.\n");
		err = -ENOMEM;
		जाओ out_err_0;
	पूर्ण

	par->gpu_mem_base = pci_resource_start(par->gpu, 0);
	par->gpu_mem_size = pci_resource_len(par->gpu, 0);
	अगर (!request_mem_region(par->gpu_mem_base, par->gpu_mem_size, "vmlfb")) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME ": Could not claim GPU MMIO.\n");
		err = -EBUSY;
		जाओ out_err_1;
	पूर्ण
	par->gpu_mem = ioremap(par->gpu_mem_base, par->gpu_mem_size);
	अगर (par->gpu_mem == शून्य) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME ": Could not map GPU MMIO.\n");
		err = -ENOMEM;
		जाओ out_err_2;
	पूर्ण

	वापस 0;

out_err_2:
	release_mem_region(par->gpu_mem_base, par->gpu_mem_size);
out_err_1:
	iounmap(par->vdc_mem);
out_err_0:
	release_mem_region(par->vdc_mem_base, par->vdc_mem_size);
	वापस err;
पूर्ण

/*
 * Unmap the VDC and GPU रेजिस्टर spaces.
 */

अटल व्योम vmlfb_disable_mmio(काष्ठा vml_par *par)
अणु
	iounmap(par->gpu_mem);
	release_mem_region(par->gpu_mem_base, par->gpu_mem_size);
	iounmap(par->vdc_mem);
	release_mem_region(par->vdc_mem_base, par->vdc_mem_size);
पूर्ण

/*
 * Release and uninit the VDC and GPU.
 */

अटल व्योम vmlfb_release_devices(काष्ठा vml_par *par)
अणु
	अगर (atomic_dec_and_test(&par->refcount)) अणु
		pci_disable_device(par->gpu);
		pci_disable_device(par->vdc);
	पूर्ण
पूर्ण

/*
 * Free up allocated resources क्रम a device.
 */

अटल व्योम vml_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा vml_info *vinfo;
	काष्ठा vml_par *par;

	info = pci_get_drvdata(dev);
	अगर (info) अणु
		vinfo = container_of(info, काष्ठा vml_info, info);
		par = vinfo->par;
		mutex_lock(&vml_mutex);
		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);
		vmlfb_मुक्त_vram(vinfo);
		vmlfb_disable_mmio(par);
		vmlfb_release_devices(par);
		kमुक्त(vinfo);
		kमुक्त(par);
		mutex_unlock(&vml_mutex);
	पूर्ण
पूर्ण

अटल व्योम vmlfb_set_pref_pixel_क्रमmat(काष्ठा fb_var_screeninfo *var)
अणु
	चयन (var->bits_per_pixel) अणु
	हाल 16:
		var->blue.offset = 0;
		var->blue.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->red.offset = 10;
		var->red.length = 5;
		var->transp.offset = 15;
		var->transp.length = 1;
		अवरोध;
	हाल 32:
		var->blue.offset = 0;
		var->blue.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->transp.offset = 24;
		var->transp.length = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	var->blue.msb_right = var->green.msb_right =
	    var->red.msb_right = var->transp.msb_right = 0;
पूर्ण

/*
 * Device initialization.
 * We initialize one vml_par काष्ठा per device and one vml_info
 * काष्ठा per pipe. Currently we have only one pipe.
 */

अटल पूर्णांक vml_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा vml_info *vinfo;
	काष्ठा fb_info *info;
	काष्ठा vml_par *par;
	पूर्णांक err = 0;

	par = kzalloc(माप(*par), GFP_KERNEL);
	अगर (par == शून्य)
		वापस -ENOMEM;

	vinfo = kzalloc(माप(*vinfo), GFP_KERNEL);
	अगर (vinfo == शून्य) अणु
		err = -ENOMEM;
		जाओ out_err_0;
	पूर्ण

	vinfo->par = par;
	par->vdc = dev;
	atomic_set(&par->refcount, 1);

	चयन (id->device) अणु
	हाल VML_DEVICE_VDC:
		अगर ((err = vmlfb_get_gpu(par)))
			जाओ out_err_1;
		pci_set_drvdata(dev, &vinfo->info);
		अवरोध;
	शेष:
		err = -ENODEV;
		जाओ out_err_1;
	पूर्ण

	info = &vinfo->info;
	info->flags = FBINFO_DEFAULT | FBINFO_PARTIAL_PAN_OK;

	err = vmlfb_enable_mmio(par);
	अगर (err)
		जाओ out_err_2;

	err = vmlfb_alloc_vram(vinfo, vml_mem_requested,
			       vml_mem_contig, vml_mem_min);
	अगर (err)
		जाओ out_err_3;

	म_नकल(info->fix.id, "Vermilion Range");
	info->fix.mmio_start = 0;
	info->fix.mmio_len = 0;
	info->fix.smem_start = vinfo->vram_start;
	info->fix.smem_len = vinfo->vram_contig_size;
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_TRUECOLOR;
	info->fix.ypanstep = 1;
	info->fix.xpanstep = 1;
	info->fix.ywrapstep = 0;
	info->fix.accel = FB_ACCEL_NONE;
	info->screen_base = vinfo->vram_logical;
	info->pseuकरो_palette = vinfo->pseuकरो_palette;
	info->par = par;
	info->fbops = &vmlfb_ops;
	info->device = &dev->dev;

	INIT_LIST_HEAD(&vinfo->head);
	vinfo->pipe_disabled = 1;
	vinfo->cur_blank_mode = FB_BLANK_UNBLANK;

	info->var.grayscale = 0;
	info->var.bits_per_pixel = 16;
	vmlfb_set_pref_pixel_क्रमmat(&info->var);

	अगर (!fb_find_mode
	    (&info->var, info, vml_शेष_mode, शून्य, 0, &शेषmode, 16)) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME ": Could not find initial mode\n");
	पूर्ण

	अगर (fb_alloc_cmap(&info->cmap, 256, 1) < 0) अणु
		err = -ENOMEM;
		जाओ out_err_4;
	पूर्ण

	err = रेजिस्टर_framebuffer(info);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME ": Register framebuffer error.\n");
		जाओ out_err_5;
	पूर्ण

	prपूर्णांकk("Initialized vmlfb\n");

	वापस 0;

out_err_5:
	fb_dealloc_cmap(&info->cmap);
out_err_4:
	vmlfb_मुक्त_vram(vinfo);
out_err_3:
	vmlfb_disable_mmio(par);
out_err_2:
	vmlfb_release_devices(par);
out_err_1:
	kमुक्त(vinfo);
out_err_0:
	kमुक्त(par);
	वापस err;
पूर्ण

अटल पूर्णांक vmlfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	/*
	 * Save रेजिस्टरs here?
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक vmlfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	/*
	 * Restore रेजिस्टरs here.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक vml_nearest_घड़ी(पूर्णांक घड़ी)
अणु

	पूर्णांक i;
	पूर्णांक cur_index;
	पूर्णांक cur_dअगरf;
	पूर्णांक dअगरf;

	cur_index = 0;
	cur_dअगरf = घड़ी - vml_घड़ीs[0];
	cur_dअगरf = (cur_dअगरf < 0) ? -cur_dअगरf : cur_dअगरf;
	क्रम (i = 1; i < vml_num_घड़ीs; ++i) अणु
		dअगरf = घड़ी - vml_घड़ीs[i];
		dअगरf = (dअगरf < 0) ? -dअगरf : dअगरf;
		अगर (dअगरf < cur_dअगरf) अणु
			cur_index = i;
			cur_dअगरf = dअगरf;
		पूर्ण
	पूर्ण
	वापस vml_घड़ीs[cur_index];
पूर्ण

अटल पूर्णांक vmlfb_check_var_locked(काष्ठा fb_var_screeninfo *var,
				  काष्ठा vml_info *vinfo)
अणु
	u32 pitch;
	u64 mem;
	पूर्णांक nearest_घड़ी;
	पूर्णांक घड़ी;
	पूर्णांक घड़ी_dअगरf;
	काष्ठा fb_var_screeninfo v;

	v = *var;
	घड़ी = PICOS2KHZ(var->pixघड़ी);

	अगर (subsys && subsys->nearest_घड़ी) अणु
		nearest_घड़ी = subsys->nearest_घड़ी(subsys, घड़ी);
	पूर्ण अन्यथा अणु
		nearest_घड़ी = vml_nearest_घड़ी(घड़ी);
	पूर्ण

	/*
	 * Accept a 20% dअगरf.
	 */

	घड़ी_dअगरf = nearest_घड़ी - घड़ी;
	घड़ी_dअगरf = (घड़ी_dअगरf < 0) ? -घड़ी_dअगरf : घड़ी_dअगरf;
	अगर (घड़ी_dअगरf > घड़ी / 5) अणु
#अगर 0
		prपूर्णांकk(KERN_DEBUG MODULE_NAME ": Diff failure. %d %d\n",घड़ी_dअगरf,घड़ी);
#पूर्ण_अगर
		वापस -EINVAL;
	पूर्ण

	v.pixघड़ी = KHZ2PICOS(nearest_घड़ी);

	अगर (var->xres > VML_MAX_XRES || var->yres > VML_MAX_YRES) अणु
		prपूर्णांकk(KERN_DEBUG MODULE_NAME ": Resolution failure.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (var->xres_भव > VML_MAX_XRES_VIRTUAL) अणु
		prपूर्णांकk(KERN_DEBUG MODULE_NAME
		       ": Virtual resolution failure.\n");
		वापस -EINVAL;
	पूर्ण
	चयन (v.bits_per_pixel) अणु
	हाल 0 ... 16:
		v.bits_per_pixel = 16;
		अवरोध;
	हाल 17 ... 32:
		v.bits_per_pixel = 32;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG MODULE_NAME ": Invalid bpp: %d.\n",
		       var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	pitch = ALIGN((var->xres * var->bits_per_pixel) >> 3, 0x40);
	mem = (u64)pitch * var->yres_भव;
	अगर (mem > vinfo->vram_contig_size) अणु
		वापस -ENOMEM;
	पूर्ण

	चयन (v.bits_per_pixel) अणु
	हाल 16:
		अगर (var->blue.offset != 0 ||
		    var->blue.length != 5 ||
		    var->green.offset != 5 ||
		    var->green.length != 5 ||
		    var->red.offset != 10 ||
		    var->red.length != 5 ||
		    var->transp.offset != 15 || var->transp.length != 1) अणु
			vmlfb_set_pref_pixel_क्रमmat(&v);
		पूर्ण
		अवरोध;
	हाल 32:
		अगर (var->blue.offset != 0 ||
		    var->blue.length != 8 ||
		    var->green.offset != 8 ||
		    var->green.length != 8 ||
		    var->red.offset != 16 ||
		    var->red.length != 8 ||
		    (var->transp.length != 0 && var->transp.length != 8) ||
		    (var->transp.length == 8 && var->transp.offset != 24)) अणु
			vmlfb_set_pref_pixel_क्रमmat(&v);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*var = v;

	वापस 0;
पूर्ण

अटल पूर्णांक vmlfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा vml_info *vinfo = container_of(info, काष्ठा vml_info, info);
	पूर्णांक ret;

	mutex_lock(&vml_mutex);
	ret = vmlfb_check_var_locked(var, vinfo);
	mutex_unlock(&vml_mutex);

	वापस ret;
पूर्ण

अटल व्योम vml_रुको_vblank(काष्ठा vml_info *vinfo)
अणु
	/* Wait क्रम vblank. For now, just रुको क्रम a 50Hz cycle (20ms)) */
	mdelay(20);
पूर्ण

अटल व्योम vmlfb_disable_pipe(काष्ठा vml_info *vinfo)
अणु
	काष्ठा vml_par *par = vinfo->par;

	/* Disable the MDVO pad */
	VML_WRITE32(par, VML_RCOMPSTAT, 0);
	जबतक (!(VML_READ32(par, VML_RCOMPSTAT) & VML_MDVO_VDC_I_RCOMP)) ;

	/* Disable display planes */
	VML_WRITE32(par, VML_DSPCCNTR,
		    VML_READ32(par, VML_DSPCCNTR) & ~VML_GFX_ENABLE);
	(व्योम)VML_READ32(par, VML_DSPCCNTR);
	/* Wait क्रम vblank क्रम the disable to take effect */
	vml_रुको_vblank(vinfo);

	/* Next, disable display pipes */
	VML_WRITE32(par, VML_PIPEACONF, 0);
	(व्योम)VML_READ32(par, VML_PIPEACONF);

	vinfo->pipe_disabled = 1;
पूर्ण

#अगर_घोषित VERMILION_DEBUG
अटल व्योम vml_dump_regs(काष्ठा vml_info *vinfo)
अणु
	काष्ठा vml_par *par = vinfo->par;

	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": Modesetting register dump:\n");
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tHTOTAL_A         : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_HTOTAL_A));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tHBLANK_A         : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_HBLANK_A));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tHSYNC_A          : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_HSYNC_A));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tVTOTAL_A         : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_VTOTAL_A));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tVBLANK_A         : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_VBLANK_A));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tVSYNC_A          : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_VSYNC_A));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tDSPCSTRIDE       : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_DSPCSTRIDE));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tDSPCSIZE         : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_DSPCSIZE));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tDSPCPOS          : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_DSPCPOS));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tDSPARB           : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_DSPARB));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tDSPCADDR         : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_DSPCADDR));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tBCLRPAT_A        : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_BCLRPAT_A));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tCANVSCLR_A       : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_CANVSCLR_A));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tPIPEASRC         : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_PIPEASRC));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tPIPEACONF        : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_PIPEACONF));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tDSPCCNTR         : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_DSPCCNTR));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": \tRCOMPSTAT        : 0x%08x\n",
	       (अचिन्हित)VML_READ32(par, VML_RCOMPSTAT));
	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": End of modesetting register dump.\n");
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vmlfb_set_par_locked(काष्ठा vml_info *vinfo)
अणु
	काष्ठा vml_par *par = vinfo->par;
	काष्ठा fb_info *info = &vinfo->info;
	काष्ठा fb_var_screeninfo *var = &info->var;
	u32 htotal, hactive, hblank_start, hblank_end, hsync_start, hsync_end;
	u32 vtotal, vactive, vblank_start, vblank_end, vsync_start, vsync_end;
	u32 dspcntr;
	पूर्णांक घड़ी;

	vinfo->bytes_per_pixel = var->bits_per_pixel >> 3;
	vinfo->stride = ALIGN(var->xres_भव * vinfo->bytes_per_pixel, 0x40);
	info->fix.line_length = vinfo->stride;

	अगर (!subsys)
		वापस 0;

	htotal =
	    var->xres + var->right_margin + var->hsync_len + var->left_margin;
	hactive = var->xres;
	hblank_start = var->xres;
	hblank_end = htotal;
	hsync_start = hactive + var->right_margin;
	hsync_end = hsync_start + var->hsync_len;

	vtotal =
	    var->yres + var->lower_margin + var->vsync_len + var->upper_margin;
	vactive = var->yres;
	vblank_start = var->yres;
	vblank_end = vtotal;
	vsync_start = vactive + var->lower_margin;
	vsync_end = vsync_start + var->vsync_len;

	dspcntr = VML_GFX_ENABLE | VML_GFX_GAMMABYPASS;
	घड़ी = PICOS2KHZ(var->pixघड़ी);

	अगर (subsys->nearest_घड़ी) अणु
		घड़ी = subsys->nearest_घड़ी(subsys, घड़ी);
	पूर्ण अन्यथा अणु
		घड़ी = vml_nearest_घड़ी(घड़ी);
	पूर्ण
	prपूर्णांकk(KERN_DEBUG MODULE_NAME
	       ": Set mode Hfreq : %d kHz, Vfreq : %d Hz.\n", घड़ी / htotal,
	       ((घड़ी / htotal) * 1000) / vtotal);

	चयन (var->bits_per_pixel) अणु
	हाल 16:
		dspcntr |= VML_GFX_ARGB1555;
		अवरोध;
	हाल 32:
		अगर (var->transp.length == 8)
			dspcntr |= VML_GFX_ARGB8888 | VML_GFX_ALPHAMULT;
		अन्यथा
			dspcntr |= VML_GFX_RGB0888;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	vmlfb_disable_pipe(vinfo);
	mb();

	अगर (subsys->set_घड़ी)
		subsys->set_घड़ी(subsys, घड़ी);
	अन्यथा
		वापस -EINVAL;

	VML_WRITE32(par, VML_HTOTAL_A, ((htotal - 1) << 16) | (hactive - 1));
	VML_WRITE32(par, VML_HBLANK_A,
		    ((hblank_end - 1) << 16) | (hblank_start - 1));
	VML_WRITE32(par, VML_HSYNC_A,
		    ((hsync_end - 1) << 16) | (hsync_start - 1));
	VML_WRITE32(par, VML_VTOTAL_A, ((vtotal - 1) << 16) | (vactive - 1));
	VML_WRITE32(par, VML_VBLANK_A,
		    ((vblank_end - 1) << 16) | (vblank_start - 1));
	VML_WRITE32(par, VML_VSYNC_A,
		    ((vsync_end - 1) << 16) | (vsync_start - 1));
	VML_WRITE32(par, VML_DSPCSTRIDE, vinfo->stride);
	VML_WRITE32(par, VML_DSPCSIZE,
		    ((var->yres - 1) << 16) | (var->xres - 1));
	VML_WRITE32(par, VML_DSPCPOS, 0x00000000);
	VML_WRITE32(par, VML_DSPARB, VML_FIFO_DEFAULT);
	VML_WRITE32(par, VML_BCLRPAT_A, 0x00000000);
	VML_WRITE32(par, VML_CANVSCLR_A, 0x00000000);
	VML_WRITE32(par, VML_PIPEASRC,
		    ((var->xres - 1) << 16) | (var->yres - 1));

	wmb();
	VML_WRITE32(par, VML_PIPEACONF, VML_PIPE_ENABLE);
	wmb();
	VML_WRITE32(par, VML_DSPCCNTR, dspcntr);
	wmb();
	VML_WRITE32(par, VML_DSPCADDR, (u32) vinfo->vram_start +
		    var->yoffset * vinfo->stride +
		    var->xoffset * vinfo->bytes_per_pixel);

	VML_WRITE32(par, VML_RCOMPSTAT, VML_MDVO_PAD_ENABLE);

	जबतक (!(VML_READ32(par, VML_RCOMPSTAT) &
		 (VML_MDVO_VDC_I_RCOMP | VML_MDVO_PAD_ENABLE))) ;

	vinfo->pipe_disabled = 0;
#अगर_घोषित VERMILION_DEBUG
	vml_dump_regs(vinfo);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक vmlfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा vml_info *vinfo = container_of(info, काष्ठा vml_info, info);
	पूर्णांक ret;

	mutex_lock(&vml_mutex);
	list_move(&vinfo->head, (subsys) ? &global_has_mode : &global_no_mode);
	ret = vmlfb_set_par_locked(vinfo);

	mutex_unlock(&vml_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक vmlfb_blank_locked(काष्ठा vml_info *vinfo)
अणु
	काष्ठा vml_par *par = vinfo->par;
	u32 cur = VML_READ32(par, VML_PIPEACONF);

	चयन (vinfo->cur_blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		अगर (vinfo->pipe_disabled) अणु
			vmlfb_set_par_locked(vinfo);
		पूर्ण
		VML_WRITE32(par, VML_PIPEACONF, cur & ~VML_PIPE_FORCE_BORDER);
		(व्योम)VML_READ32(par, VML_PIPEACONF);
		अवरोध;
	हाल FB_BLANK_NORMAL:
		अगर (vinfo->pipe_disabled) अणु
			vmlfb_set_par_locked(vinfo);
		पूर्ण
		VML_WRITE32(par, VML_PIPEACONF, cur | VML_PIPE_FORCE_BORDER);
		(व्योम)VML_READ32(par, VML_PIPEACONF);
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
		अगर (!vinfo->pipe_disabled) अणु
			vmlfb_disable_pipe(vinfo);
		पूर्ण
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		अगर (!vinfo->pipe_disabled) अणु
			vmlfb_disable_pipe(vinfo);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmlfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा vml_info *vinfo = container_of(info, काष्ठा vml_info, info);
	पूर्णांक ret;

	mutex_lock(&vml_mutex);
	vinfo->cur_blank_mode = blank_mode;
	ret = vmlfb_blank_locked(vinfo);
	mutex_unlock(&vml_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक vmlfb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा vml_info *vinfo = container_of(info, काष्ठा vml_info, info);
	काष्ठा vml_par *par = vinfo->par;

	mutex_lock(&vml_mutex);
	VML_WRITE32(par, VML_DSPCADDR, (u32) vinfo->vram_start +
		    var->yoffset * vinfo->stride +
		    var->xoffset * vinfo->bytes_per_pixel);
	(व्योम)VML_READ32(par, VML_DSPCADDR);
	mutex_unlock(&vml_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक vmlfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			   u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	u32 v;

	अगर (regno >= 16)
		वापस -EINVAL;

	अगर (info->var.grayscale) अणु
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण

	अगर (info->fix.visual != FB_VISUAL_TRUECOLOR)
		वापस -EINVAL;

	red = VML_TOHW(red, info->var.red.length);
	blue = VML_TOHW(blue, info->var.blue.length);
	green = VML_TOHW(green, info->var.green.length);
	transp = VML_TOHW(transp, info->var.transp.length);

	v = (red << info->var.red.offset) |
	    (green << info->var.green.offset) |
	    (blue << info->var.blue.offset) |
	    (transp << info->var.transp.offset);

	चयन (info->var.bits_per_pixel) अणु
	हाल 16:
		((u32 *) info->pseuकरो_palette)[regno] = v;
		अवरोध;
	हाल 24:
	हाल 32:
		((u32 *) info->pseuकरो_palette)[regno] = v;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vmlfb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vml_info *vinfo = container_of(info, काष्ठा vml_info, info);
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;
	पूर्णांक ret;
	अचिन्हित दीर्घ prot;

	ret = vmlfb_vram_offset(vinfo, offset);
	अगर (ret)
		वापस -EINVAL;

	prot = pgprot_val(vma->vm_page_prot) & ~_PAGE_CACHE_MASK;
	pgprot_val(vma->vm_page_prot) =
		prot | cachemode2protval(_PAGE_CACHE_MODE_UC_MINUS);

	वापस vm_iomap_memory(vma, vinfo->vram_start,
			vinfo->vram_contig_size);
पूर्ण

अटल पूर्णांक vmlfb_sync(काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vmlfb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	वापस -EINVAL;	/* just to क्रमce soft_cursor() call */
पूर्ण

अटल काष्ठा fb_ops vmlfb_ops = अणु
	.owner = THIS_MODULE,
	.fb_खोलो = vmlfb_खोलो,
	.fb_release = vmlfb_release,
	.fb_check_var = vmlfb_check_var,
	.fb_set_par = vmlfb_set_par,
	.fb_blank = vmlfb_blank,
	.fb_pan_display = vmlfb_pan_display,
	.fb_fillrect = cfb_fillrect,
	.fb_copyarea = cfb_copyarea,
	.fb_imageblit = cfb_imageblit,
	.fb_cursor = vmlfb_cursor,
	.fb_sync = vmlfb_sync,
	.fb_mmap = vmlfb_mmap,
	.fb_setcolreg = vmlfb_setcolreg
पूर्ण;

अटल स्थिर काष्ठा pci_device_id vml_ids[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, VML_DEVICE_VDC)पूर्ण,
	अणु0पूर्ण
पूर्ण;

अटल काष्ठा pci_driver vmlfb_pci_driver = अणु
	.name = "vmlfb",
	.id_table = vml_ids,
	.probe = vml_pci_probe,
	.हटाओ = vml_pci_हटाओ,
पूर्ण;

अटल व्योम __निकास vmlfb_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&vmlfb_pci_driver);
पूर्ण

अटल पूर्णांक __init vmlfb_init(व्योम)
अणु

#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options(MODULE_NAME, &option))
		वापस -ENODEV;
#पूर्ण_अगर

	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": initializing\n");
	mutex_init(&vml_mutex);
	INIT_LIST_HEAD(&global_no_mode);
	INIT_LIST_HEAD(&global_has_mode);

	वापस pci_रेजिस्टर_driver(&vmlfb_pci_driver);
पूर्ण

पूर्णांक vmlfb_रेजिस्टर_subsys(काष्ठा vml_sys *sys)
अणु
	काष्ठा vml_info *entry;
	काष्ठा list_head *list;
	u32 save_activate;

	mutex_lock(&vml_mutex);
	अगर (subsys != शून्य) अणु
		subsys->restore(subsys);
	पूर्ण
	subsys = sys;
	subsys->save(subsys);

	/*
	 * We need to restart list traversal क्रम each item, since we
	 * release the list mutex in the loop.
	 */

	list = global_no_mode.next;
	जबतक (list != &global_no_mode) अणु
		list_del_init(list);
		entry = list_entry(list, काष्ठा vml_info, head);

		/*
		 * First, try the current mode which might not be
		 * completely validated with respect to the pixel घड़ी.
		 */

		अगर (!vmlfb_check_var_locked(&entry->info.var, entry)) अणु
			vmlfb_set_par_locked(entry);
			list_add_tail(list, &global_has_mode);
		पूर्ण अन्यथा अणु

			/*
			 * Didn't work. Try to find another mode,
			 * that matches this subsys.
			 */

			mutex_unlock(&vml_mutex);
			save_activate = entry->info.var.activate;
			entry->info.var.bits_per_pixel = 16;
			vmlfb_set_pref_pixel_क्रमmat(&entry->info.var);
			अगर (fb_find_mode(&entry->info.var,
					 &entry->info,
					 vml_शेष_mode, शून्य, 0, शून्य, 16)) अणु
				entry->info.var.activate |=
				    FB_ACTIVATE_FORCE | FB_ACTIVATE_NOW;
				fb_set_var(&entry->info, &entry->info.var);
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_ERR MODULE_NAME
				       ": Sorry. no mode found for this subsys.\n");
			पूर्ण
			entry->info.var.activate = save_activate;
			mutex_lock(&vml_mutex);
		पूर्ण
		vmlfb_blank_locked(entry);
		list = global_no_mode.next;
	पूर्ण
	mutex_unlock(&vml_mutex);

	prपूर्णांकk(KERN_DEBUG MODULE_NAME ": Registered %s subsystem.\n",
				subsys->name ? subsys->name : "unknown");
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(vmlfb_रेजिस्टर_subsys);

व्योम vmlfb_unरेजिस्टर_subsys(काष्ठा vml_sys *sys)
अणु
	काष्ठा vml_info *entry, *next;

	mutex_lock(&vml_mutex);
	अगर (subsys != sys) अणु
		mutex_unlock(&vml_mutex);
		वापस;
	पूर्ण
	subsys->restore(subsys);
	subsys = शून्य;
	list_क्रम_each_entry_safe(entry, next, &global_has_mode, head) अणु
		prपूर्णांकk(KERN_DEBUG MODULE_NAME ": subsys disable pipe\n");
		vmlfb_disable_pipe(entry);
		list_move_tail(&entry->head, &global_no_mode);
	पूर्ण
	mutex_unlock(&vml_mutex);
पूर्ण

EXPORT_SYMBOL_GPL(vmlfb_unरेजिस्टर_subsys);

module_init(vmlfb_init);
module_निकास(vmlfb_cleanup);

MODULE_AUTHOR("Tungsten Graphics");
MODULE_DESCRIPTION("Initialization of the Vermilion display devices");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
