<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* sbuslib.h: SBUS fb helper library पूर्णांकerfaces */
#अगर_अघोषित _SBUSLIB_H
#घोषणा _SBUSLIB_H

काष्ठा sbus_mmap_map अणु
	अचिन्हित दीर्घ voff;
	अचिन्हित दीर्घ poff;
	अचिन्हित दीर्घ size;
पूर्ण;

#घोषणा SBUS_MMAP_FBSIZE(n) (-n)
#घोषणा SBUS_MMAP_EMPTY	0x80000000

बाह्य व्योम sbusfb_fill_var(काष्ठा fb_var_screeninfo *var,
			    काष्ठा device_node *dp, पूर्णांक bpp);
काष्ठा vm_area_काष्ठा;
बाह्य पूर्णांक sbusfb_mmap_helper(काष्ठा sbus_mmap_map *map,
			      अचिन्हित दीर्घ physbase, अचिन्हित दीर्घ fbsize,
			      अचिन्हित दीर्घ iospace,
			      काष्ठा vm_area_काष्ठा *vma);
पूर्णांक sbusfb_ioctl_helper(अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ arg,
			काष्ठा fb_info *info,
			पूर्णांक type, पूर्णांक fb_depth, अचिन्हित दीर्घ fb_size);
पूर्णांक sbusfb_compat_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg);

#पूर्ण_अगर /* _SBUSLIB_H */
