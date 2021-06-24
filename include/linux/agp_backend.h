<शैली गुरु>
/*
 * AGPGART backend specअगरic includes. Not क्रम userspace consumption.
 *
 * Copyright (C) 2004 Silicon Graphics, Inc.
 * Copyright (C) 2002-2003 Dave Jones
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

#अगर_अघोषित _AGP_BACKEND_H
#घोषणा _AGP_BACKEND_H 1

#समावेश <linux/list.h>

क्रमागत chipset_type अणु
	NOT_SUPPORTED,
	SUPPORTED,
पूर्ण;

काष्ठा agp_version अणु
	u16 major;
	u16 minor;
पूर्ण;

काष्ठा agp_kern_info अणु
	काष्ठा agp_version version;
	काष्ठा pci_dev *device;
	क्रमागत chipset_type chipset;
	अचिन्हित दीर्घ mode;
	अचिन्हित दीर्घ aper_base;
	माप_प्रकार aper_size;
	पूर्णांक max_memory;		/* In pages */
	पूर्णांक current_memory;
	bool cant_use_aperture;
	अचिन्हित दीर्घ page_mask;
	स्थिर काष्ठा vm_operations_काष्ठा *vm_ops;
पूर्ण;

/*
 * The agp_memory काष्ठाure has inक्रमmation about the block of agp memory
 * allocated.  A caller may manipulate the next and prev poपूर्णांकers to link
 * each allocated item पूर्णांकo a list.  These poपूर्णांकers are ignored by the backend.
 * Everything अन्यथा should never be written to, but the caller may पढ़ो any of
 * the items to determine the status of this block of agp memory.
 */

काष्ठा agp_bridge_data;

काष्ठा agp_memory अणु
	काष्ठा agp_memory *next;
	काष्ठा agp_memory *prev;
	काष्ठा agp_bridge_data *bridge;
	काष्ठा page **pages;
	माप_प्रकार page_count;
	पूर्णांक key;
	पूर्णांक num_scratch_pages;
	off_t pg_start;
	u32 type;
	u32 physical;
	bool is_bound;
	bool is_flushed;
	/* list of agp_memory mapped to the aperture */
	काष्ठा list_head mapped_list;
	/* DMA-mapped addresses */
	काष्ठा scatterlist *sg_list;
	पूर्णांक num_sg;
पूर्ण;

#घोषणा AGP_NORMAL_MEMORY 0

#घोषणा AGP_USER_TYPES (1 << 16)
#घोषणा AGP_USER_MEMORY (AGP_USER_TYPES)
#घोषणा AGP_USER_CACHED_MEMORY (AGP_USER_TYPES + 1)

बाह्य काष्ठा agp_bridge_data *agp_bridge;
बाह्य काष्ठा list_head agp_bridges;

बाह्य काष्ठा agp_bridge_data *(*agp_find_bridge)(काष्ठा pci_dev *);

बाह्य व्योम agp_मुक्त_memory(काष्ठा agp_memory *);
बाह्य काष्ठा agp_memory *agp_allocate_memory(काष्ठा agp_bridge_data *, माप_प्रकार, u32);
बाह्य पूर्णांक agp_copy_info(काष्ठा agp_bridge_data *, काष्ठा agp_kern_info *);
बाह्य पूर्णांक agp_bind_memory(काष्ठा agp_memory *, off_t);
बाह्य पूर्णांक agp_unbind_memory(काष्ठा agp_memory *);
बाह्य व्योम agp_enable(काष्ठा agp_bridge_data *, u32);
बाह्य काष्ठा agp_bridge_data *agp_backend_acquire(काष्ठा pci_dev *);
बाह्य व्योम agp_backend_release(काष्ठा agp_bridge_data *);

#पूर्ण_अगर				/* _AGP_BACKEND_H */
