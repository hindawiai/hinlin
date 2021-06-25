<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sbuslib.c: Helper library क्रम SBUS framebuffer drivers.
 *
 * Copyright (C) 2003 David S. Miller (davem@redhat.com)
 */

#समावेश <linux/compat.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/fbपन.स>

#समावेश "sbuslib.h"

व्योम sbusfb_fill_var(काष्ठा fb_var_screeninfo *var, काष्ठा device_node *dp,
		     पूर्णांक bpp)
अणु
	स_रखो(var, 0, माप(*var));

	var->xres = of_getपूर्णांकprop_शेष(dp, "width", 1152);
	var->yres = of_getपूर्णांकprop_शेष(dp, "height", 900);
	var->xres_भव = var->xres;
	var->yres_भव = var->yres;
	var->bits_per_pixel = bpp;
पूर्ण

EXPORT_SYMBOL(sbusfb_fill_var);

अटल अचिन्हित दीर्घ sbusfb_mmapsize(दीर्घ size, अचिन्हित दीर्घ fbsize)
अणु
	अगर (size == SBUS_MMAP_EMPTY) वापस 0;
	अगर (size >= 0) वापस size;
	वापस fbsize * (-size);
पूर्ण

पूर्णांक sbusfb_mmap_helper(काष्ठा sbus_mmap_map *map,
		       अचिन्हित दीर्घ physbase,
		       अचिन्हित दीर्घ fbsize,
		       अचिन्हित दीर्घ iospace,
		       काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित पूर्णांक size, page, r, map_size;
	अचिन्हित दीर्घ map_offset = 0;
	अचिन्हित दीर्घ off;
	पूर्णांक i;
                                        
	अगर (!(vma->vm_flags & (VM_SHARED | VM_MAYSHARE)))
		वापस -EINVAL;

	size = vma->vm_end - vma->vm_start;
	अगर (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		वापस -EINVAL;

	off = vma->vm_pgoff << PAGE_SHIFT;

	/* VM_IO | VM_DONTEXPAND | VM_DONTDUMP are set by remap_pfn_range() */

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	/* Each page, see which map applies */
	क्रम (page = 0; page < size; )अणु
		map_size = 0;
		क्रम (i = 0; map[i].size; i++)
			अगर (map[i].voff == off+page) अणु
				map_size = sbusfb_mmapsize(map[i].size, fbsize);
#अगर_घोषित __sparc_v9__
#घोषणा POFF_MASK	(PAGE_MASK|0x1UL)
#अन्यथा
#घोषणा POFF_MASK	(PAGE_MASK)
#पूर्ण_अगर				
				map_offset = (physbase + map[i].poff) & POFF_MASK;
				अवरोध;
			पूर्ण
		अगर (!map_size) अणु
			page += PAGE_SIZE;
			जारी;
		पूर्ण
		अगर (page + map_size > size)
			map_size = size - page;
		r = io_remap_pfn_range(vma,
					vma->vm_start + page,
					MK_IOSPACE_PFN(iospace,
						map_offset >> PAGE_SHIFT),
					map_size,
					vma->vm_page_prot);
		अगर (r)
			वापस -EAGAIN;
		page += map_size;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sbusfb_mmap_helper);

पूर्णांक sbusfb_ioctl_helper(अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ arg,
			काष्ठा fb_info *info,
			पूर्णांक type, पूर्णांक fb_depth, अचिन्हित दीर्घ fb_size)
अणु
	चयन(cmd) अणु
	हाल FBIOGTYPE: अणु
		काष्ठा fbtype __user *f = (काष्ठा fbtype __user *) arg;

		अगर (put_user(type, &f->fb_type) ||
		    put_user(info->var.yres, &f->fb_height) ||
		    put_user(info->var.xres, &f->fb_width) ||
		    put_user(fb_depth, &f->fb_depth) ||
		    put_user(0, &f->fb_cmsize) ||
		    put_user(fb_size, &f->fb_cmsize))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल FBIOPUTCMAP_SPARC: अणु
		काष्ठा fbcmap __user *c = (काष्ठा fbcmap __user *) arg;
		काष्ठा fb_cmap cmap;
		u16 red, green, blue;
		u8 red8, green8, blue8;
		अचिन्हित अक्षर __user *ured;
		अचिन्हित अक्षर __user *ugreen;
		अचिन्हित अक्षर __user *ublue;
		अचिन्हित पूर्णांक index, count, i;

		अगर (get_user(index, &c->index) ||
		    get_user(count, &c->count) ||
		    get_user(ured, &c->red) ||
		    get_user(ugreen, &c->green) ||
		    get_user(ublue, &c->blue))
			वापस -EFAULT;

		cmap.len = 1;
		cmap.red = &red;
		cmap.green = &green;
		cmap.blue = &blue;
		cmap.transp = शून्य;
		क्रम (i = 0; i < count; i++) अणु
			पूर्णांक err;

			अगर (get_user(red8, &ured[i]) ||
			    get_user(green8, &ugreen[i]) ||
			    get_user(blue8, &ublue[i]))
				वापस -EFAULT;

			red = red8 << 8;
			green = green8 << 8;
			blue = blue8 << 8;

			cmap.start = index + i;
			err = fb_set_cmap(&cmap, info);
			अगर (err)
				वापस err;
		पूर्ण
		वापस 0;
	पूर्ण
	हाल FBIOGETCMAP_SPARC: अणु
		काष्ठा fbcmap __user *c = (काष्ठा fbcmap __user *) arg;
		अचिन्हित अक्षर __user *ured;
		अचिन्हित अक्षर __user *ugreen;
		अचिन्हित अक्षर __user *ublue;
		काष्ठा fb_cmap *cmap = &info->cmap;
		अचिन्हित पूर्णांक index, count, i;
		u8 red, green, blue;

		अगर (get_user(index, &c->index) ||
		    get_user(count, &c->count) ||
		    get_user(ured, &c->red) ||
		    get_user(ugreen, &c->green) ||
		    get_user(ublue, &c->blue))
			वापस -EFAULT;

		अगर (index > cmap->len || count > cmap->len - index)
			वापस -EINVAL;

		क्रम (i = 0; i < count; i++) अणु
			red = cmap->red[index + i] >> 8;
			green = cmap->green[index + i] >> 8;
			blue = cmap->blue[index + i] >> 8;
			अगर (put_user(red, &ured[i]) ||
			    put_user(green, &ugreen[i]) ||
			    put_user(blue, &ublue[i]))
				वापस -EFAULT;
		पूर्ण
		वापस 0;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sbusfb_ioctl_helper);

#अगर_घोषित CONFIG_COMPAT
पूर्णांक sbusfb_compat_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल FBIOGTYPE:
	हाल FBIOSATTR:
	हाल FBIOGATTR:
	हाल FBIOSVIDEO:
	हाल FBIOGVIDEO:
	हाल FBIOSCURSOR32:
	हाल FBIOGCURSOR32:	/* This is not implemented yet.
				   Later it should be converted... */
	हाल FBIOSCURPOS:
	हाल FBIOGCURPOS:
	हाल FBIOGCURMAX:
		वापस info->fbops->fb_ioctl(info, cmd, arg);
	हाल FBIOPUTCMAP32:
	हाल FBIOPUTCMAP_SPARC: अणु
		काष्ठा fbcmap32 c;
		काष्ठा fb_cmap cmap;
		u16 red, green, blue;
		u8 red8, green8, blue8;
		अचिन्हित अक्षर __user *ured;
		अचिन्हित अक्षर __user *ugreen;
		अचिन्हित अक्षर __user *ublue;
		अचिन्हित पूर्णांक i;

		अगर (copy_from_user(&c, compat_ptr(arg), माप(c)))
			वापस -EFAULT;
		ured = compat_ptr(c.red);
		ugreen = compat_ptr(c.green);
		ublue = compat_ptr(c.blue);

		cmap.len = 1;
		cmap.red = &red;
		cmap.green = &green;
		cmap.blue = &blue;
		cmap.transp = शून्य;
		क्रम (i = 0; i < c.count; i++) अणु
			पूर्णांक err;

			अगर (get_user(red8, &ured[i]) ||
			    get_user(green8, &ugreen[i]) ||
			    get_user(blue8, &ublue[i]))
				वापस -EFAULT;

			red = red8 << 8;
			green = green8 << 8;
			blue = blue8 << 8;

			cmap.start = c.index + i;
			err = fb_set_cmap(&cmap, info);
			अगर (err)
				वापस err;
		पूर्ण
		वापस 0;
	पूर्ण
	हाल FBIOGETCMAP32: अणु
		काष्ठा fbcmap32 c;
		अचिन्हित अक्षर __user *ured;
		अचिन्हित अक्षर __user *ugreen;
		अचिन्हित अक्षर __user *ublue;
		काष्ठा fb_cmap *cmap = &info->cmap;
		अचिन्हित पूर्णांक index, i;
		u8 red, green, blue;

		अगर (copy_from_user(&c, compat_ptr(arg), माप(c)))
			वापस -EFAULT;
		index = c.index;
		ured = compat_ptr(c.red);
		ugreen = compat_ptr(c.green);
		ublue = compat_ptr(c.blue);

		अगर (index > cmap->len || c.count > cmap->len - index)
			वापस -EINVAL;

		क्रम (i = 0; i < c.count; i++) अणु
			red = cmap->red[index + i] >> 8;
			green = cmap->green[index + i] >> 8;
			blue = cmap->blue[index + i] >> 8;
			अगर (put_user(red, &ured[i]) ||
			    put_user(green, &ugreen[i]) ||
			    put_user(blue, &ublue[i]))
				वापस -EFAULT;
		पूर्ण
		वापस 0;
	पूर्ण
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sbusfb_compat_ioctl);
#पूर्ण_अगर
