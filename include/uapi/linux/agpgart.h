<शैली गुरु>
/*
 * AGPGART module version 0.99
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

#अगर_अघोषित _UAPI_AGP_H
#घोषणा _UAPI_AGP_H

#घोषणा AGPIOC_BASE       'A'
#घोषणा AGPIOC_INFO       _IOR (AGPIOC_BASE, 0, काष्ठा agp_info*)
#घोषणा AGPIOC_ACQUIRE    _IO  (AGPIOC_BASE, 1)
#घोषणा AGPIOC_RELEASE    _IO  (AGPIOC_BASE, 2)
#घोषणा AGPIOC_SETUP      _IOW (AGPIOC_BASE, 3, काष्ठा agp_setup*)
#घोषणा AGPIOC_RESERVE    _IOW (AGPIOC_BASE, 4, काष्ठा agp_region*)
#घोषणा AGPIOC_PROTECT    _IOW (AGPIOC_BASE, 5, काष्ठा agp_region*)
#घोषणा AGPIOC_ALLOCATE   _IOWR(AGPIOC_BASE, 6, काष्ठा agp_allocate*)
#घोषणा AGPIOC_DEALLOCATE _IOW (AGPIOC_BASE, 7, पूर्णांक)
#घोषणा AGPIOC_BIND       _IOW (AGPIOC_BASE, 8, काष्ठा agp_bind*)
#घोषणा AGPIOC_UNBIND     _IOW (AGPIOC_BASE, 9, काष्ठा agp_unbind*)
#घोषणा AGPIOC_CHIPSET_FLUSH _IO (AGPIOC_BASE, 10)

#घोषणा AGP_DEVICE      "/dev/agpgart"

#अगर_अघोषित TRUE
#घोषणा TRUE 1
#पूर्ण_अगर

#अगर_अघोषित FALSE
#घोषणा FALSE 0
#पूर्ण_अगर

#अगर_अघोषित __KERNEL__
#समावेश <linux/types.h>
#समावेश <मानककोष.स>

काष्ठा agp_version अणु
	__u16 major;
	__u16 minor;
पूर्ण;

प्रकार काष्ठा _agp_info अणु
	काष्ठा agp_version version;	/* version of the driver        */
	__u32 bridge_id;	/* bridge venकरोr/device         */
	__u32 agp_mode;		/* mode info of bridge          */
	अचिन्हित दीर्घ aper_base;/* base of aperture             */
	माप_प्रकार aper_size;	/* size of aperture             */
	माप_प्रकार pg_total;	/* max pages (swap + प्रणाली)    */
	माप_प्रकार pg_प्रणाली;	/* max pages (प्रणाली)           */
	माप_प्रकार pg_used;		/* current pages used           */
पूर्ण agp_info;

प्रकार काष्ठा _agp_setup अणु
	__u32 agp_mode;		/* mode info of bridge          */
पूर्ण agp_setup;

/*
 * The "prot" करोwn below needs still a "sleep" flag somehow ...
 */
प्रकार काष्ठा _agp_segment अणु
	__kernel_off_t pg_start;	/* starting page to populate    */
	__kernel_माप_प्रकार pg_count;	/* number of pages              */
	पूर्णांक prot;			/* prot flags क्रम mmap          */
पूर्ण agp_segment;

प्रकार काष्ठा _agp_region अणु
	__kernel_pid_t pid;		/* pid of process       */
	__kernel_माप_प्रकार seg_count;	/* number of segments   */
	काष्ठा _agp_segment *seg_list;
पूर्ण agp_region;

प्रकार काष्ठा _agp_allocate अणु
	पूर्णांक key;		/* tag of allocation            */
	__kernel_माप_प्रकार pg_count;/* number of pages             */
	__u32 type;		/* 0 == normal, other devspec   */
   	__u32 physical;         /* device specअगरic (some devices  
				 * need a phys address of the     
				 * actual page behind the gatt    
				 * table)                        */
पूर्ण agp_allocate;

प्रकार काष्ठा _agp_bind अणु
	पूर्णांक key;		/* tag of allocation            */
	__kernel_off_t pg_start;/* starting page to populate    */
पूर्ण agp_bind;

प्रकार काष्ठा _agp_unbind अणु
	पूर्णांक key;		/* tag of allocation            */
	__u32 priority;		/* priority क्रम paging out      */
पूर्ण agp_unbind;

#पूर्ण_अगर				/* __KERNEL__ */

#पूर्ण_अगर /* _UAPI_AGP_H */
