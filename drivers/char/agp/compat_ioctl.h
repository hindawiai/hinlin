<शैली गुरु>
/*
 * Copyright (C) 1999 Jeff Harपंचांगann
 * Copyright (C) 1999 Precision Insight, Inc.
 * Copyright (C) 1999 Xi Graphics, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _AGP_COMPAT_IOCTL_H
#घोषणा _AGP_COMPAT_IOCTL_H

#समावेश <linux/compat.h>
#समावेश <linux/agpgart.h>

#घोषणा AGPIOC_INFO32       _IOR (AGPIOC_BASE, 0, compat_uptr_t)
#घोषणा AGPIOC_ACQUIRE32    _IO  (AGPIOC_BASE, 1)
#घोषणा AGPIOC_RELEASE32    _IO  (AGPIOC_BASE, 2)
#घोषणा AGPIOC_SETUP32      _IOW (AGPIOC_BASE, 3, compat_uptr_t)
#घोषणा AGPIOC_RESERVE32    _IOW (AGPIOC_BASE, 4, compat_uptr_t)
#घोषणा AGPIOC_PROTECT32    _IOW (AGPIOC_BASE, 5, compat_uptr_t)
#घोषणा AGPIOC_ALLOCATE32   _IOWR(AGPIOC_BASE, 6, compat_uptr_t)
#घोषणा AGPIOC_DEALLOCATE32 _IOW (AGPIOC_BASE, 7, compat_पूर्णांक_t)
#घोषणा AGPIOC_BIND32       _IOW (AGPIOC_BASE, 8, compat_uptr_t)
#घोषणा AGPIOC_UNBIND32     _IOW (AGPIOC_BASE, 9, compat_uptr_t)
#घोषणा AGPIOC_CHIPSET_FLUSH32 _IO (AGPIOC_BASE, 10)

काष्ठा agp_info32 अणु
	काष्ठा agp_version version;	/* version of the driver        */
	u32 bridge_id;		/* bridge venकरोr/device         */
	u32 agp_mode;		/* mode info of bridge          */
	compat_दीर्घ_t aper_base;	/* base of aperture             */
	compat_माप_प्रकार aper_size;	/* size of aperture             */
	compat_माप_प्रकार pg_total;	/* max pages (swap + प्रणाली)    */
	compat_माप_प्रकार pg_प्रणाली;	/* max pages (प्रणाली)           */
	compat_माप_प्रकार pg_used;		/* current pages used           */
पूर्ण;

/*
 * The "prot" करोwn below needs still a "sleep" flag somehow ...
 */
काष्ठा agp_segment32 अणु
	compat_off_t pg_start;		/* starting page to populate    */
	compat_माप_प्रकार pg_count;	/* number of pages              */
	compat_पूर्णांक_t prot;		/* prot flags क्रम mmap          */
पूर्ण;

काष्ठा agp_region32 अणु
	compat_pid_t pid;		/* pid of process               */
	compat_माप_प्रकार seg_count;	/* number of segments           */
	काष्ठा agp_segment32 *seg_list;
पूर्ण;

काष्ठा agp_allocate32 अणु
	compat_पूर्णांक_t key;		/* tag of allocation            */
	compat_माप_प्रकार pg_count;	/* number of pages              */
	u32 type;		/* 0 == normal, other devspec   */
	u32 physical;           /* device specअगरic (some devices
				 * need a phys address of the
				 * actual page behind the gatt
				 * table)                        */
पूर्ण;

काष्ठा agp_bind32 अणु
	compat_पूर्णांक_t key;		/* tag of allocation            */
	compat_off_t pg_start;		/* starting page to populate    */
पूर्ण;

काष्ठा agp_unbind32 अणु
	compat_पूर्णांक_t key;		/* tag of allocation            */
	u32 priority;		/* priority क्रम paging out      */
पूर्ण;

बाह्य काष्ठा agp_front_data agp_fe;

पूर्णांक agpioc_acquire_wrap(काष्ठा agp_file_निजी *priv);
पूर्णांक agpioc_release_wrap(काष्ठा agp_file_निजी *priv);
पूर्णांक agpioc_protect_wrap(काष्ठा agp_file_निजी *priv);
पूर्णांक agpioc_setup_wrap(काष्ठा agp_file_निजी *priv, व्योम __user *arg);
पूर्णांक agpioc_deallocate_wrap(काष्ठा agp_file_निजी *priv, पूर्णांक arg);
काष्ठा agp_file_निजी *agp_find_निजी(pid_t pid);
काष्ठा agp_client *agp_create_client(pid_t id);
पूर्णांक agp_हटाओ_client(pid_t id);
पूर्णांक agp_create_segment(काष्ठा agp_client *client, काष्ठा agp_region *region);
व्योम agp_मुक्त_memory_wrap(काष्ठा agp_memory *memory);
काष्ठा agp_memory *agp_allocate_memory_wrap(माप_प्रकार pg_count, u32 type);
काष्ठा agp_memory *agp_find_mem_by_key(पूर्णांक key);
काष्ठा agp_client *agp_find_client_by_pid(pid_t id);

#पूर्ण_अगर /* _AGP_COMPAT_H */
