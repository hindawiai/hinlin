<शैली गुरु>
/*
 * AGPGART driver.
 * Copyright (C) 2004 Silicon Graphics, Inc.
 * Copyright (C) 2002-2005 Dave Jones.
 * Copyright (C) 1999 Jeff Harपंचांगann.
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
 * TODO:
 * - Allocate more than order 0 pages to aव्योम too much linear map splitting.
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/pm.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/set_memory.h>
#पूर्ण_अगर
#समावेश "agp.h"

__u32 *agp_gatt_table;
पूर्णांक agp_memory_reserved;

/*
 * Needed by the Nक्रमce GART driver क्रम the समय being. Would be
 * nice to करो this some other way instead of needing this export.
 */
EXPORT_SYMBOL_GPL(agp_memory_reserved);

/*
 * Generic routines क्रम handling agp_memory काष्ठाures -
 * They use the basic page allocation routines to करो the brunt of the work.
 */

व्योम agp_मुक्त_key(पूर्णांक key)
अणु
	अगर (key < 0)
		वापस;

	अगर (key < MAXKEY)
		clear_bit(key, agp_bridge->key_list);
पूर्ण
EXPORT_SYMBOL(agp_मुक्त_key);


अटल पूर्णांक agp_get_key(व्योम)
अणु
	पूर्णांक bit;

	bit = find_first_zero_bit(agp_bridge->key_list, MAXKEY);
	अगर (bit < MAXKEY) अणु
		set_bit(bit, agp_bridge->key_list);
		वापस bit;
	पूर्ण
	वापस -1;
पूर्ण

/*
 * Use kदो_स्मृति अगर possible क्रम the page list. Otherwise fall back to
 * vदो_स्मृति. This speeds things up and also saves memory क्रम small AGP
 * regions.
 */

व्योम agp_alloc_page_array(माप_प्रकार size, काष्ठा agp_memory *mem)
अणु
	mem->pages = kvदो_स्मृति(size, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(agp_alloc_page_array);

अटल काष्ठा agp_memory *agp_create_user_memory(अचिन्हित दीर्घ num_agp_pages)
अणु
	काष्ठा agp_memory *new;
	अचिन्हित दीर्घ alloc_size = num_agp_pages*माप(काष्ठा page *);

	अगर (पूर्णांक_उच्च/माप(काष्ठा page *) < num_agp_pages)
		वापस शून्य;

	new = kzalloc(माप(काष्ठा agp_memory), GFP_KERNEL);
	अगर (new == शून्य)
		वापस शून्य;

	new->key = agp_get_key();

	अगर (new->key < 0) अणु
		kमुक्त(new);
		वापस शून्य;
	पूर्ण

	agp_alloc_page_array(alloc_size, new);

	अगर (new->pages == शून्य) अणु
		agp_मुक्त_key(new->key);
		kमुक्त(new);
		वापस शून्य;
	पूर्ण
	new->num_scratch_pages = 0;
	वापस new;
पूर्ण

काष्ठा agp_memory *agp_create_memory(पूर्णांक scratch_pages)
अणु
	काष्ठा agp_memory *new;

	new = kzalloc(माप(काष्ठा agp_memory), GFP_KERNEL);
	अगर (new == शून्य)
		वापस शून्य;

	new->key = agp_get_key();

	अगर (new->key < 0) अणु
		kमुक्त(new);
		वापस शून्य;
	पूर्ण

	agp_alloc_page_array(PAGE_SIZE * scratch_pages, new);

	अगर (new->pages == शून्य) अणु
		agp_मुक्त_key(new->key);
		kमुक्त(new);
		वापस शून्य;
	पूर्ण
	new->num_scratch_pages = scratch_pages;
	new->type = AGP_NORMAL_MEMORY;
	वापस new;
पूर्ण
EXPORT_SYMBOL(agp_create_memory);

/**
 *	agp_मुक्त_memory - मुक्त memory associated with an agp_memory poपूर्णांकer.
 *
 *	@curr:		agp_memory poपूर्णांकer to be मुक्तd.
 *
 *	It is the only function that can be called when the backend is not owned
 *	by the caller.  (So it can मुक्त memory on client death.)
 */
व्योम agp_मुक्त_memory(काष्ठा agp_memory *curr)
अणु
	माप_प्रकार i;

	अगर (curr == शून्य)
		वापस;

	अगर (curr->is_bound)
		agp_unbind_memory(curr);

	अगर (curr->type >= AGP_USER_TYPES) अणु
		agp_generic_मुक्त_by_type(curr);
		वापस;
	पूर्ण

	अगर (curr->type != 0) अणु
		curr->bridge->driver->मुक्त_by_type(curr);
		वापस;
	पूर्ण
	अगर (curr->page_count != 0) अणु
		अगर (curr->bridge->driver->agp_destroy_pages) अणु
			curr->bridge->driver->agp_destroy_pages(curr);
		पूर्ण अन्यथा अणु

			क्रम (i = 0; i < curr->page_count; i++) अणु
				curr->bridge->driver->agp_destroy_page(
					curr->pages[i],
					AGP_PAGE_DESTROY_UNMAP);
			पूर्ण
			क्रम (i = 0; i < curr->page_count; i++) अणु
				curr->bridge->driver->agp_destroy_page(
					curr->pages[i],
					AGP_PAGE_DESTROY_FREE);
			पूर्ण
		पूर्ण
	पूर्ण
	agp_मुक्त_key(curr->key);
	agp_मुक्त_page_array(curr);
	kमुक्त(curr);
पूर्ण
EXPORT_SYMBOL(agp_मुक्त_memory);

#घोषणा ENTRIES_PER_PAGE		(PAGE_SIZE / माप(अचिन्हित दीर्घ))

/**
 *	agp_allocate_memory  -  allocate a group of pages of a certain type.
 *
 *	@bridge: an agp_bridge_data काष्ठा allocated क्रम the AGP host bridge.
 *	@page_count:	माप_प्रकार argument of the number of pages
 *	@type:	u32 argument of the type of memory to be allocated.
 *
 *	Every agp bridge device will allow you to allocate AGP_NORMAL_MEMORY which
 *	maps to physical ram.  Any other type is device dependent.
 *
 *	It वापसs शून्य whenever memory is unavailable.
 */
काष्ठा agp_memory *agp_allocate_memory(काष्ठा agp_bridge_data *bridge,
					माप_प्रकार page_count, u32 type)
अणु
	पूर्णांक scratch_pages;
	काष्ठा agp_memory *new;
	माप_प्रकार i;
	पूर्णांक cur_memory;

	अगर (!bridge)
		वापस शून्य;

	cur_memory = atomic_पढ़ो(&bridge->current_memory_agp);
	अगर ((cur_memory + page_count > bridge->max_memory_agp) ||
	    (cur_memory + page_count < page_count))
		वापस शून्य;

	अगर (type >= AGP_USER_TYPES) अणु
		new = agp_generic_alloc_user(page_count, type);
		अगर (new)
			new->bridge = bridge;
		वापस new;
	पूर्ण

	अगर (type != 0) अणु
		new = bridge->driver->alloc_by_type(page_count, type);
		अगर (new)
			new->bridge = bridge;
		वापस new;
	पूर्ण

	scratch_pages = (page_count + ENTRIES_PER_PAGE - 1) / ENTRIES_PER_PAGE;

	new = agp_create_memory(scratch_pages);

	अगर (new == शून्य)
		वापस शून्य;

	अगर (bridge->driver->agp_alloc_pages) अणु
		अगर (bridge->driver->agp_alloc_pages(bridge, new, page_count)) अणु
			agp_मुक्त_memory(new);
			वापस शून्य;
		पूर्ण
		new->bridge = bridge;
		वापस new;
	पूर्ण

	क्रम (i = 0; i < page_count; i++) अणु
		काष्ठा page *page = bridge->driver->agp_alloc_page(bridge);

		अगर (page == शून्य) अणु
			agp_मुक्त_memory(new);
			वापस शून्य;
		पूर्ण
		new->pages[i] = page;
		new->page_count++;
	पूर्ण
	new->bridge = bridge;

	वापस new;
पूर्ण
EXPORT_SYMBOL(agp_allocate_memory);


/* End - Generic routines क्रम handling agp_memory काष्ठाures */


अटल पूर्णांक agp_वापस_size(व्योम)
अणु
	पूर्णांक current_size;
	व्योम *temp;

	temp = agp_bridge->current_size;

	चयन (agp_bridge->driver->माप_प्रकारype) अणु
	हाल U8_APER_SIZE:
		current_size = A_SIZE_8(temp)->size;
		अवरोध;
	हाल U16_APER_SIZE:
		current_size = A_SIZE_16(temp)->size;
		अवरोध;
	हाल U32_APER_SIZE:
		current_size = A_SIZE_32(temp)->size;
		अवरोध;
	हाल LVL2_APER_SIZE:
		current_size = A_SIZE_LVL2(temp)->size;
		अवरोध;
	हाल FIXED_APER_SIZE:
		current_size = A_SIZE_FIX(temp)->size;
		अवरोध;
	शेष:
		current_size = 0;
		अवरोध;
	पूर्ण

	current_size -= (agp_memory_reserved / (1024*1024));
	अगर (current_size <0)
		current_size = 0;
	वापस current_size;
पूर्ण


पूर्णांक agp_num_entries(व्योम)
अणु
	पूर्णांक num_entries;
	व्योम *temp;

	temp = agp_bridge->current_size;

	चयन (agp_bridge->driver->माप_प्रकारype) अणु
	हाल U8_APER_SIZE:
		num_entries = A_SIZE_8(temp)->num_entries;
		अवरोध;
	हाल U16_APER_SIZE:
		num_entries = A_SIZE_16(temp)->num_entries;
		अवरोध;
	हाल U32_APER_SIZE:
		num_entries = A_SIZE_32(temp)->num_entries;
		अवरोध;
	हाल LVL2_APER_SIZE:
		num_entries = A_SIZE_LVL2(temp)->num_entries;
		अवरोध;
	हाल FIXED_APER_SIZE:
		num_entries = A_SIZE_FIX(temp)->num_entries;
		अवरोध;
	शेष:
		num_entries = 0;
		अवरोध;
	पूर्ण

	num_entries -= agp_memory_reserved>>PAGE_SHIFT;
	अगर (num_entries<0)
		num_entries = 0;
	वापस num_entries;
पूर्ण
EXPORT_SYMBOL_GPL(agp_num_entries);


/**
 *	agp_copy_info  -  copy bridge state inक्रमmation
 *
 *	@bridge: an agp_bridge_data काष्ठा allocated क्रम the AGP host bridge.
 *	@info:		agp_kern_info poपूर्णांकer.  The caller should insure that this poपूर्णांकer is valid.
 *
 *	This function copies inक्रमmation about the agp bridge device and the state of
 *	the agp backend पूर्णांकo an agp_kern_info poपूर्णांकer.
 */
पूर्णांक agp_copy_info(काष्ठा agp_bridge_data *bridge, काष्ठा agp_kern_info *info)
अणु
	स_रखो(info, 0, माप(काष्ठा agp_kern_info));
	अगर (!bridge) अणु
		info->chipset = NOT_SUPPORTED;
		वापस -EIO;
	पूर्ण

	info->version.major = bridge->version->major;
	info->version.minor = bridge->version->minor;
	info->chipset = SUPPORTED;
	info->device = bridge->dev;
	अगर (bridge->mode & AGPSTAT_MODE_3_0)
		info->mode = bridge->mode & ~AGP3_RESERVED_MASK;
	अन्यथा
		info->mode = bridge->mode & ~AGP2_RESERVED_MASK;
	info->aper_base = bridge->gart_bus_addr;
	info->aper_size = agp_वापस_size();
	info->max_memory = bridge->max_memory_agp;
	info->current_memory = atomic_पढ़ो(&bridge->current_memory_agp);
	info->cant_use_aperture = bridge->driver->cant_use_aperture;
	info->vm_ops = bridge->vm_ops;
	info->page_mask = ~0UL;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(agp_copy_info);

/* End - Routine to copy over inक्रमmation काष्ठाure */

/*
 * Routines क्रम handling swapping of agp_memory पूर्णांकo the GATT -
 * These routines take agp_memory and insert them पूर्णांकo the GATT.
 * They call device specअगरic routines to actually ग_लिखो to the GATT.
 */

/**
 *	agp_bind_memory  -  Bind an agp_memory काष्ठाure पूर्णांकo the GATT.
 *
 *	@curr:		agp_memory poपूर्णांकer
 *	@pg_start:	an offset पूर्णांकo the graphics aperture translation table
 *
 *	It वापसs -EINVAL अगर the poपूर्णांकer == शून्य.
 *	It वापसs -EBUSY अगर the area of the table requested is alपढ़ोy in use.
 */
पूर्णांक agp_bind_memory(काष्ठा agp_memory *curr, off_t pg_start)
अणु
	पूर्णांक ret_val;

	अगर (curr == शून्य)
		वापस -EINVAL;

	अगर (curr->is_bound) अणु
		prपूर्णांकk(KERN_INFO PFX "memory %p is already bound!\n", curr);
		वापस -EINVAL;
	पूर्ण
	अगर (!curr->is_flushed) अणु
		curr->bridge->driver->cache_flush();
		curr->is_flushed = true;
	पूर्ण

	ret_val = curr->bridge->driver->insert_memory(curr, pg_start, curr->type);

	अगर (ret_val != 0)
		वापस ret_val;

	curr->is_bound = true;
	curr->pg_start = pg_start;
	spin_lock(&agp_bridge->mapped_lock);
	list_add(&curr->mapped_list, &agp_bridge->mapped_list);
	spin_unlock(&agp_bridge->mapped_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(agp_bind_memory);


/**
 *	agp_unbind_memory  -  Removes an agp_memory काष्ठाure from the GATT
 *
 * @curr:	agp_memory poपूर्णांकer to be हटाओd from the GATT.
 *
 * It वापसs -EINVAL अगर this piece of agp_memory is not currently bound to
 * the graphics aperture translation table or अगर the agp_memory poपूर्णांकer == शून्य
 */
पूर्णांक agp_unbind_memory(काष्ठा agp_memory *curr)
अणु
	पूर्णांक ret_val;

	अगर (curr == शून्य)
		वापस -EINVAL;

	अगर (!curr->is_bound) अणु
		prपूर्णांकk(KERN_INFO PFX "memory %p was not bound!\n", curr);
		वापस -EINVAL;
	पूर्ण

	ret_val = curr->bridge->driver->हटाओ_memory(curr, curr->pg_start, curr->type);

	अगर (ret_val != 0)
		वापस ret_val;

	curr->is_bound = false;
	curr->pg_start = 0;
	spin_lock(&curr->bridge->mapped_lock);
	list_del(&curr->mapped_list);
	spin_unlock(&curr->bridge->mapped_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(agp_unbind_memory);


/* End - Routines क्रम handling swapping of agp_memory पूर्णांकo the GATT */


/* Generic Agp routines - Start */
अटल व्योम agp_v2_parse_one(u32 *requested_mode, u32 *bridge_agpstat, u32 *vga_agpstat)
अणु
	u32 पंचांगp;

	अगर (*requested_mode & AGP2_RESERVED_MASK) अणु
		prपूर्णांकk(KERN_INFO PFX "reserved bits set (%x) in mode 0x%x. Fixed.\n",
			*requested_mode & AGP2_RESERVED_MASK, *requested_mode);
		*requested_mode &= ~AGP2_RESERVED_MASK;
	पूर्ण

	/*
	 * Some dumb bridges are programmed to disobey the AGP2 spec.
	 * This is likely a BIOS misprogramming rather than घातeron शेष, or
	 * it would be a lot more common.
	 * https://bugs.मुक्तdesktop.org/show_bug.cgi?id=8816
	 * AGPv2 spec 6.1.9 states:
	 *   The RATE field indicates the data transfer rates supported by this
	 *   device. A.G.P. devices must report all that apply.
	 * Fix them up as best we can.
	 */
	चयन (*bridge_agpstat & 7) अणु
	हाल 4:
		*bridge_agpstat |= (AGPSTAT2_2X | AGPSTAT2_1X);
		prपूर्णांकk(KERN_INFO PFX "BIOS bug. AGP bridge claims to only support x4 rate. "
			"Fixing up support for x2 & x1\n");
		अवरोध;
	हाल 2:
		*bridge_agpstat |= AGPSTAT2_1X;
		prपूर्णांकk(KERN_INFO PFX "BIOS bug. AGP bridge claims to only support x2 rate. "
			"Fixing up support for x1\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Check the speed bits make sense. Only one should be set. */
	पंचांगp = *requested_mode & 7;
	चयन (पंचांगp) अणु
		हाल 0:
			prपूर्णांकk(KERN_INFO PFX "%s tried to set rate=x0. Setting to x1 mode.\n", current->comm);
			*requested_mode |= AGPSTAT2_1X;
			अवरोध;
		हाल 1:
		हाल 2:
			अवरोध;
		हाल 3:
			*requested_mode &= ~(AGPSTAT2_1X);	/* rate=2 */
			अवरोध;
		हाल 4:
			अवरोध;
		हाल 5:
		हाल 6:
		हाल 7:
			*requested_mode &= ~(AGPSTAT2_1X|AGPSTAT2_2X); /* rate=4*/
			अवरोध;
	पूर्ण

	/* disable SBA अगर it's not supported */
	अगर (!((*bridge_agpstat & AGPSTAT_SBA) && (*vga_agpstat & AGPSTAT_SBA) && (*requested_mode & AGPSTAT_SBA)))
		*bridge_agpstat &= ~AGPSTAT_SBA;

	/* Set rate */
	अगर (!((*bridge_agpstat & AGPSTAT2_4X) && (*vga_agpstat & AGPSTAT2_4X) && (*requested_mode & AGPSTAT2_4X)))
		*bridge_agpstat &= ~AGPSTAT2_4X;

	अगर (!((*bridge_agpstat & AGPSTAT2_2X) && (*vga_agpstat & AGPSTAT2_2X) && (*requested_mode & AGPSTAT2_2X)))
		*bridge_agpstat &= ~AGPSTAT2_2X;

	अगर (!((*bridge_agpstat & AGPSTAT2_1X) && (*vga_agpstat & AGPSTAT2_1X) && (*requested_mode & AGPSTAT2_1X)))
		*bridge_agpstat &= ~AGPSTAT2_1X;

	/* Now we know what mode it should be, clear out the unwanted bits. */
	अगर (*bridge_agpstat & AGPSTAT2_4X)
		*bridge_agpstat &= ~(AGPSTAT2_1X | AGPSTAT2_2X);	/* 4X */

	अगर (*bridge_agpstat & AGPSTAT2_2X)
		*bridge_agpstat &= ~(AGPSTAT2_1X | AGPSTAT2_4X);	/* 2X */

	अगर (*bridge_agpstat & AGPSTAT2_1X)
		*bridge_agpstat &= ~(AGPSTAT2_2X | AGPSTAT2_4X);	/* 1X */

	/* Apply any errata. */
	अगर (agp_bridge->flags & AGP_ERRATA_FASTWRITES)
		*bridge_agpstat &= ~AGPSTAT_FW;

	अगर (agp_bridge->flags & AGP_ERRATA_SBA)
		*bridge_agpstat &= ~AGPSTAT_SBA;

	अगर (agp_bridge->flags & AGP_ERRATA_1X) अणु
		*bridge_agpstat &= ~(AGPSTAT2_2X | AGPSTAT2_4X);
		*bridge_agpstat |= AGPSTAT2_1X;
	पूर्ण

	/* If we've dropped करोwn to 1X, disable fast ग_लिखोs. */
	अगर (*bridge_agpstat & AGPSTAT2_1X)
		*bridge_agpstat &= ~AGPSTAT_FW;
पूर्ण

/*
 * requested_mode = Mode requested by (typically) X.
 * bridge_agpstat = PCI_AGP_STATUS from agp bridge.
 * vga_agpstat = PCI_AGP_STATUS from graphic card.
 */
अटल व्योम agp_v3_parse_one(u32 *requested_mode, u32 *bridge_agpstat, u32 *vga_agpstat)
अणु
	u32 origbridge=*bridge_agpstat, origvga=*vga_agpstat;
	u32 पंचांगp;

	अगर (*requested_mode & AGP3_RESERVED_MASK) अणु
		prपूर्णांकk(KERN_INFO PFX "reserved bits set (%x) in mode 0x%x. Fixed.\n",
			*requested_mode & AGP3_RESERVED_MASK, *requested_mode);
		*requested_mode &= ~AGP3_RESERVED_MASK;
	पूर्ण

	/* Check the speed bits make sense. */
	पंचांगp = *requested_mode & 7;
	अगर (पंचांगp == 0) अणु
		prपूर्णांकk(KERN_INFO PFX "%s tried to set rate=x0. Setting to AGP3 x4 mode.\n", current->comm);
		*requested_mode |= AGPSTAT3_4X;
	पूर्ण
	अगर (पंचांगp >= 3) अणु
		prपूर्णांकk(KERN_INFO PFX "%s tried to set rate=x%d. Setting to AGP3 x8 mode.\n", current->comm, पंचांगp * 4);
		*requested_mode = (*requested_mode & ~7) | AGPSTAT3_8X;
	पूर्ण

	/* ARQSZ - Set the value to the maximum one.
	 * Don't allow the mode रेजिस्टर to override values. */
	*bridge_agpstat = ((*bridge_agpstat & ~AGPSTAT_ARQSZ) |
		max_t(u32,(*bridge_agpstat & AGPSTAT_ARQSZ),(*vga_agpstat & AGPSTAT_ARQSZ)));

	/* Calibration cycle.
	 * Don't allow the mode रेजिस्टर to override values. */
	*bridge_agpstat = ((*bridge_agpstat & ~AGPSTAT_CAL_MASK) |
		min_t(u32,(*bridge_agpstat & AGPSTAT_CAL_MASK),(*vga_agpstat & AGPSTAT_CAL_MASK)));

	/* SBA *must* be supported क्रम AGP v3 */
	*bridge_agpstat |= AGPSTAT_SBA;

	/*
	 * Set speed.
	 * Check क्रम invalid speeds. This can happen when applications
	 * written beक्रमe the AGP 3.0 standard pass AGP2.x modes to AGP3 hardware
	 */
	अगर (*requested_mode & AGPSTAT_MODE_3_0) अणु
		/*
		 * Caller hasn't a clue what it is करोing. Bridge is in 3.0 mode,
		 * have been passed a 3.0 mode, but with 2.x speed bits set.
		 * AGP2.x 4x -> AGP3.0 4x.
		 */
		अगर (*requested_mode & AGPSTAT2_4X) अणु
			prपूर्णांकk(KERN_INFO PFX "%s passes broken AGP3 flags (%x). Fixed.\n",
						current->comm, *requested_mode);
			*requested_mode &= ~AGPSTAT2_4X;
			*requested_mode |= AGPSTAT3_4X;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The caller करोesn't know what they are करोing. We are in 3.0 mode,
		 * but have been passed an AGP 2.x mode.
		 * Convert AGP 1x,2x,4x -> AGP 3.0 4x.
		 */
		prपूर्णांकk(KERN_INFO PFX "%s passes broken AGP2 flags (%x) in AGP3 mode. Fixed.\n",
					current->comm, *requested_mode);
		*requested_mode &= ~(AGPSTAT2_4X | AGPSTAT2_2X | AGPSTAT2_1X);
		*requested_mode |= AGPSTAT3_4X;
	पूर्ण

	अगर (*requested_mode & AGPSTAT3_8X) अणु
		अगर (!(*bridge_agpstat & AGPSTAT3_8X)) अणु
			*bridge_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_RSVD);
			*bridge_agpstat |= AGPSTAT3_4X;
			prपूर्णांकk(KERN_INFO PFX "%s requested AGPx8 but bridge not capable.\n", current->comm);
			वापस;
		पूर्ण
		अगर (!(*vga_agpstat & AGPSTAT3_8X)) अणु
			*bridge_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_RSVD);
			*bridge_agpstat |= AGPSTAT3_4X;
			prपूर्णांकk(KERN_INFO PFX "%s requested AGPx8 but graphic card not capable.\n", current->comm);
			वापस;
		पूर्ण
		/* All set, bridge & device can करो AGP x8*/
		*bridge_agpstat &= ~(AGPSTAT3_4X | AGPSTAT3_RSVD);
		जाओ करोne;

	पूर्ण अन्यथा अगर (*requested_mode & AGPSTAT3_4X) अणु
		*bridge_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_RSVD);
		*bridge_agpstat |= AGPSTAT3_4X;
		जाओ करोne;

	पूर्ण अन्यथा अणु

		/*
		 * If we didn't specअगरy an AGP mode, we see अगर both
		 * the graphics card, and the bridge can करो x8, and use अगर so.
		 * If not, we fall back to x4 mode.
		 */
		अगर ((*bridge_agpstat & AGPSTAT3_8X) && (*vga_agpstat & AGPSTAT3_8X)) अणु
			prपूर्णांकk(KERN_INFO PFX "No AGP mode specified. Setting to highest mode "
				"supported by bridge & card (x8).\n");
			*bridge_agpstat &= ~(AGPSTAT3_4X | AGPSTAT3_RSVD);
			*vga_agpstat &= ~(AGPSTAT3_4X | AGPSTAT3_RSVD);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_INFO PFX "Fell back to AGPx4 mode because ");
			अगर (!(*bridge_agpstat & AGPSTAT3_8X)) अणु
				prपूर्णांकk(KERN_INFO PFX "bridge couldn't do x8. bridge_agpstat:%x (orig=%x)\n",
					*bridge_agpstat, origbridge);
				*bridge_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_RSVD);
				*bridge_agpstat |= AGPSTAT3_4X;
			पूर्ण
			अगर (!(*vga_agpstat & AGPSTAT3_8X)) अणु
				prपूर्णांकk(KERN_INFO PFX "graphics card couldn't do x8. vga_agpstat:%x (orig=%x)\n",
					*vga_agpstat, origvga);
				*vga_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_RSVD);
				*vga_agpstat |= AGPSTAT3_4X;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	/* Apply any errata. */
	अगर (agp_bridge->flags & AGP_ERRATA_FASTWRITES)
		*bridge_agpstat &= ~AGPSTAT_FW;

	अगर (agp_bridge->flags & AGP_ERRATA_SBA)
		*bridge_agpstat &= ~AGPSTAT_SBA;

	अगर (agp_bridge->flags & AGP_ERRATA_1X) अणु
		*bridge_agpstat &= ~(AGPSTAT2_2X | AGPSTAT2_4X);
		*bridge_agpstat |= AGPSTAT2_1X;
	पूर्ण
पूर्ण


/**
 * agp_collect_device_status - determine correct agp_cmd from various agp_stat's
 * @bridge: an agp_bridge_data काष्ठा allocated क्रम the AGP host bridge.
 * @requested_mode: requested agp_stat from userspace (Typically from X)
 * @bridge_agpstat: current agp_stat from AGP bridge.
 *
 * This function will hunt क्रम an AGP graphics card, and try to match
 * the requested mode to the capabilities of both the bridge and the card.
 */
u32 agp_collect_device_status(काष्ठा agp_bridge_data *bridge, u32 requested_mode, u32 bridge_agpstat)
अणु
	काष्ठा pci_dev *device = शून्य;
	u32 vga_agpstat;
	u8 cap_ptr;

	क्रम (;;) अणु
		device = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, device);
		अगर (!device) अणु
			prपूर्णांकk(KERN_INFO PFX "Couldn't find an AGP VGA controller.\n");
			वापस 0;
		पूर्ण
		cap_ptr = pci_find_capability(device, PCI_CAP_ID_AGP);
		अगर (cap_ptr)
			अवरोध;
	पूर्ण

	/*
	 * Ok, here we have a AGP device. Disable impossible
	 * settings, and adjust the पढ़ोqueue to the minimum.
	 */
	pci_पढ़ो_config_dword(device, cap_ptr+PCI_AGP_STATUS, &vga_agpstat);

	/* adjust RQ depth */
	bridge_agpstat = ((bridge_agpstat & ~AGPSTAT_RQ_DEPTH) |
	     min_t(u32, (requested_mode & AGPSTAT_RQ_DEPTH),
		 min_t(u32, (bridge_agpstat & AGPSTAT_RQ_DEPTH), (vga_agpstat & AGPSTAT_RQ_DEPTH))));

	/* disable FW अगर it's not supported */
	अगर (!((bridge_agpstat & AGPSTAT_FW) &&
		 (vga_agpstat & AGPSTAT_FW) &&
		 (requested_mode & AGPSTAT_FW)))
		bridge_agpstat &= ~AGPSTAT_FW;

	/* Check to see अगर we are operating in 3.0 mode */
	अगर (agp_bridge->mode & AGPSTAT_MODE_3_0)
		agp_v3_parse_one(&requested_mode, &bridge_agpstat, &vga_agpstat);
	अन्यथा
		agp_v2_parse_one(&requested_mode, &bridge_agpstat, &vga_agpstat);

	pci_dev_put(device);
	वापस bridge_agpstat;
पूर्ण
EXPORT_SYMBOL(agp_collect_device_status);


व्योम agp_device_command(u32 bridge_agpstat, bool agp_v3)
अणु
	काष्ठा pci_dev *device = शून्य;
	पूर्णांक mode;

	mode = bridge_agpstat & 0x7;
	अगर (agp_v3)
		mode *= 4;

	क्रम_each_pci_dev(device) अणु
		u8 agp = pci_find_capability(device, PCI_CAP_ID_AGP);
		अगर (!agp)
			जारी;

		dev_info(&device->dev, "putting AGP V%d device into %dx mode\n",
			 agp_v3 ? 3 : 2, mode);
		pci_ग_लिखो_config_dword(device, agp + PCI_AGP_COMMAND, bridge_agpstat);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(agp_device_command);


व्योम get_agp_version(काष्ठा agp_bridge_data *bridge)
अणु
	u32 ncapid;

	/* Exit early अगर alपढ़ोy set by errata workarounds. */
	अगर (bridge->major_version != 0)
		वापस;

	pci_पढ़ो_config_dword(bridge->dev, bridge->capndx, &ncapid);
	bridge->major_version = (ncapid >> AGP_MAJOR_VERSION_SHIFT) & 0xf;
	bridge->minor_version = (ncapid >> AGP_MINOR_VERSION_SHIFT) & 0xf;
पूर्ण
EXPORT_SYMBOL(get_agp_version);


व्योम agp_generic_enable(काष्ठा agp_bridge_data *bridge, u32 requested_mode)
अणु
	u32 bridge_agpstat, temp;

	get_agp_version(agp_bridge);

	dev_info(&agp_bridge->dev->dev, "AGP %d.%d bridge\n",
		 agp_bridge->major_version, agp_bridge->minor_version);

	pci_पढ़ो_config_dword(agp_bridge->dev,
		      agp_bridge->capndx + PCI_AGP_STATUS, &bridge_agpstat);

	bridge_agpstat = agp_collect_device_status(agp_bridge, requested_mode, bridge_agpstat);
	अगर (bridge_agpstat == 0)
		/* Something bad happened. FIXME: Return error code? */
		वापस;

	bridge_agpstat |= AGPSTAT_AGP_ENABLE;

	/* Do AGP version specअगरic frobbing. */
	अगर (bridge->major_version >= 3) अणु
		अगर (bridge->mode & AGPSTAT_MODE_3_0) अणु
			/* If we have 3.5, we can करो the isoch stuff. */
			अगर (bridge->minor_version >= 5)
				agp_3_5_enable(bridge);
			agp_device_command(bridge_agpstat, true);
			वापस;
		पूर्ण अन्यथा अणु
		    /* Disable calibration cycle in RX91<1> when not in AGP3.0 mode of operation.*/
		    bridge_agpstat &= ~(7<<10) ;
		    pci_पढ़ो_config_dword(bridge->dev,
					bridge->capndx+AGPCTRL, &temp);
		    temp |= (1<<9);
		    pci_ग_लिखो_config_dword(bridge->dev,
					bridge->capndx+AGPCTRL, temp);

		    dev_info(&bridge->dev->dev, "bridge is in legacy mode, falling back to 2.x\n");
		पूर्ण
	पूर्ण

	/* AGP v<3 */
	agp_device_command(bridge_agpstat, false);
पूर्ण
EXPORT_SYMBOL(agp_generic_enable);


पूर्णांक agp_generic_create_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	अक्षर *table;
	अक्षर *table_end;
	पूर्णांक page_order;
	पूर्णांक num_entries;
	पूर्णांक i;
	व्योम *temp;
	काष्ठा page *page;

	/* The generic routines can't handle 2 level gatt's */
	अगर (bridge->driver->माप_प्रकारype == LVL2_APER_SIZE)
		वापस -EINVAL;

	table = शून्य;
	i = bridge->aperture_size_idx;
	temp = bridge->current_size;
	page_order = num_entries = 0;

	अगर (bridge->driver->माप_प्रकारype != FIXED_APER_SIZE) अणु
		करो अणु
			चयन (bridge->driver->माप_प्रकारype) अणु
			हाल U8_APER_SIZE:
				page_order =
				    A_SIZE_8(temp)->page_order;
				num_entries =
				    A_SIZE_8(temp)->num_entries;
				अवरोध;
			हाल U16_APER_SIZE:
				page_order = A_SIZE_16(temp)->page_order;
				num_entries = A_SIZE_16(temp)->num_entries;
				अवरोध;
			हाल U32_APER_SIZE:
				page_order = A_SIZE_32(temp)->page_order;
				num_entries = A_SIZE_32(temp)->num_entries;
				अवरोध;
				/* This हाल will never really happen. */
			हाल FIXED_APER_SIZE:
			हाल LVL2_APER_SIZE:
			शेष:
				page_order = num_entries = 0;
				अवरोध;
			पूर्ण

			table = alloc_gatt_pages(page_order);

			अगर (table == शून्य) अणु
				i++;
				चयन (bridge->driver->माप_प्रकारype) अणु
				हाल U8_APER_SIZE:
					bridge->current_size = A_IDX8(bridge);
					अवरोध;
				हाल U16_APER_SIZE:
					bridge->current_size = A_IDX16(bridge);
					अवरोध;
				हाल U32_APER_SIZE:
					bridge->current_size = A_IDX32(bridge);
					अवरोध;
				/* These हालs will never really happen. */
				हाल FIXED_APER_SIZE:
				हाल LVL2_APER_SIZE:
				शेष:
					अवरोध;
				पूर्ण
				temp = bridge->current_size;
			पूर्ण अन्यथा अणु
				bridge->aperture_size_idx = i;
			पूर्ण
		पूर्ण जबतक (!table && (i < bridge->driver->num_aperture_sizes));
	पूर्ण अन्यथा अणु
		page_order = ((काष्ठा aper_size_info_fixed *) temp)->page_order;
		num_entries = ((काष्ठा aper_size_info_fixed *) temp)->num_entries;
		table = alloc_gatt_pages(page_order);
	पूर्ण

	अगर (table == शून्य)
		वापस -ENOMEM;

	table_end = table + ((PAGE_SIZE * (1 << page_order)) - 1);

	क्रम (page = virt_to_page(table); page <= virt_to_page(table_end); page++)
		SetPageReserved(page);

	bridge->gatt_table_real = (u32 *) table;
	agp_gatt_table = (व्योम *)table;

	bridge->driver->cache_flush();
#अगर_घोषित CONFIG_X86
	अगर (set_memory_uc((अचिन्हित दीर्घ)table, 1 << page_order))
		prपूर्णांकk(KERN_WARNING "Could not set GATT table memory to UC!\n");

	bridge->gatt_table = (u32 __iomem *)table;
#अन्यथा
	bridge->gatt_table = ioremap(virt_to_phys(table),
					(PAGE_SIZE * (1 << page_order)));
	bridge->driver->cache_flush();
#पूर्ण_अगर

	अगर (bridge->gatt_table == शून्य) अणु
		क्रम (page = virt_to_page(table); page <= virt_to_page(table_end); page++)
			ClearPageReserved(page);

		मुक्त_gatt_pages(table, page_order);

		वापस -ENOMEM;
	पूर्ण
	bridge->gatt_bus_addr = virt_to_phys(bridge->gatt_table_real);

	/* AK: bogus, should encode addresses > 4GB */
	क्रम (i = 0; i < num_entries; i++) अणु
		ग_लिखोl(bridge->scratch_page, bridge->gatt_table+i);
		पढ़ोl(bridge->gatt_table+i);	/* PCI Posting. */
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(agp_generic_create_gatt_table);

पूर्णांक agp_generic_मुक्त_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक page_order;
	अक्षर *table, *table_end;
	व्योम *temp;
	काष्ठा page *page;

	temp = bridge->current_size;

	चयन (bridge->driver->माप_प्रकारype) अणु
	हाल U8_APER_SIZE:
		page_order = A_SIZE_8(temp)->page_order;
		अवरोध;
	हाल U16_APER_SIZE:
		page_order = A_SIZE_16(temp)->page_order;
		अवरोध;
	हाल U32_APER_SIZE:
		page_order = A_SIZE_32(temp)->page_order;
		अवरोध;
	हाल FIXED_APER_SIZE:
		page_order = A_SIZE_FIX(temp)->page_order;
		अवरोध;
	हाल LVL2_APER_SIZE:
		/* The generic routines can't deal with 2 level gatt's */
		वापस -EINVAL;
	शेष:
		page_order = 0;
		अवरोध;
	पूर्ण

	/* Do not worry about मुक्तing memory, because अगर this is
	 * called, then all agp memory is deallocated and हटाओd
	 * from the table. */

#अगर_घोषित CONFIG_X86
	set_memory_wb((अचिन्हित दीर्घ)bridge->gatt_table, 1 << page_order);
#अन्यथा
	iounmap(bridge->gatt_table);
#पूर्ण_अगर
	table = (अक्षर *) bridge->gatt_table_real;
	table_end = table + ((PAGE_SIZE * (1 << page_order)) - 1);

	क्रम (page = virt_to_page(table); page <= virt_to_page(table_end); page++)
		ClearPageReserved(page);

	मुक्त_gatt_pages(bridge->gatt_table_real, page_order);

	agp_gatt_table = शून्य;
	bridge->gatt_table = शून्य;
	bridge->gatt_table_real = शून्य;
	bridge->gatt_bus_addr = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(agp_generic_मुक्त_gatt_table);


पूर्णांक agp_generic_insert_memory(काष्ठा agp_memory * mem, off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक num_entries;
	माप_प्रकार i;
	off_t j;
	व्योम *temp;
	काष्ठा agp_bridge_data *bridge;
	पूर्णांक mask_type;

	bridge = mem->bridge;
	अगर (!bridge)
		वापस -EINVAL;

	अगर (mem->page_count == 0)
		वापस 0;

	temp = bridge->current_size;

	चयन (bridge->driver->माप_प्रकारype) अणु
	हाल U8_APER_SIZE:
		num_entries = A_SIZE_8(temp)->num_entries;
		अवरोध;
	हाल U16_APER_SIZE:
		num_entries = A_SIZE_16(temp)->num_entries;
		अवरोध;
	हाल U32_APER_SIZE:
		num_entries = A_SIZE_32(temp)->num_entries;
		अवरोध;
	हाल FIXED_APER_SIZE:
		num_entries = A_SIZE_FIX(temp)->num_entries;
		अवरोध;
	हाल LVL2_APER_SIZE:
		/* The generic routines can't deal with 2 level gatt's */
		वापस -EINVAL;
	शेष:
		num_entries = 0;
		अवरोध;
	पूर्ण

	num_entries -= agp_memory_reserved/PAGE_SIZE;
	अगर (num_entries < 0) num_entries = 0;

	अगर (type != mem->type)
		वापस -EINVAL;

	mask_type = bridge->driver->agp_type_to_mask_type(bridge, type);
	अगर (mask_type != 0) अणु
		/* The generic routines know nothing of memory types */
		वापस -EINVAL;
	पूर्ण

	अगर (((pg_start + mem->page_count) > num_entries) ||
	    ((pg_start + mem->page_count) < pg_start))
		वापस -EINVAL;

	j = pg_start;

	जबतक (j < (pg_start + mem->page_count)) अणु
		अगर (!PGE_EMPTY(bridge, पढ़ोl(bridge->gatt_table+j)))
			वापस -EBUSY;
		j++;
	पूर्ण

	अगर (!mem->is_flushed) अणु
		bridge->driver->cache_flush();
		mem->is_flushed = true;
	पूर्ण

	क्रम (i = 0, j = pg_start; i < mem->page_count; i++, j++) अणु
		ग_लिखोl(bridge->driver->mask_memory(bridge,
						   page_to_phys(mem->pages[i]),
						   mask_type),
		       bridge->gatt_table+j);
	पूर्ण
	पढ़ोl(bridge->gatt_table+j-1);	/* PCI Posting. */

	bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(agp_generic_insert_memory);


पूर्णांक agp_generic_हटाओ_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	माप_प्रकार i;
	काष्ठा agp_bridge_data *bridge;
	पूर्णांक mask_type, num_entries;

	bridge = mem->bridge;
	अगर (!bridge)
		वापस -EINVAL;

	अगर (mem->page_count == 0)
		वापस 0;

	अगर (type != mem->type)
		वापस -EINVAL;

	num_entries = agp_num_entries();
	अगर (((pg_start + mem->page_count) > num_entries) ||
	    ((pg_start + mem->page_count) < pg_start))
		वापस -EINVAL;

	mask_type = bridge->driver->agp_type_to_mask_type(bridge, type);
	अगर (mask_type != 0) अणु
		/* The generic routines know nothing of memory types */
		वापस -EINVAL;
	पूर्ण

	/* AK: bogus, should encode addresses > 4GB */
	क्रम (i = pg_start; i < (mem->page_count + pg_start); i++) अणु
		ग_लिखोl(bridge->scratch_page, bridge->gatt_table+i);
	पूर्ण
	पढ़ोl(bridge->gatt_table+i-1);	/* PCI Posting. */

	bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(agp_generic_हटाओ_memory);

काष्ठा agp_memory *agp_generic_alloc_by_type(माप_प्रकार page_count, पूर्णांक type)
अणु
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(agp_generic_alloc_by_type);

व्योम agp_generic_मुक्त_by_type(काष्ठा agp_memory *curr)
अणु
	agp_मुक्त_page_array(curr);
	agp_मुक्त_key(curr->key);
	kमुक्त(curr);
पूर्ण
EXPORT_SYMBOL(agp_generic_मुक्त_by_type);

काष्ठा agp_memory *agp_generic_alloc_user(माप_प्रकार page_count, पूर्णांक type)
अणु
	काष्ठा agp_memory *new;
	पूर्णांक i;
	पूर्णांक pages;

	pages = (page_count + ENTRIES_PER_PAGE - 1) / ENTRIES_PER_PAGE;
	new = agp_create_user_memory(page_count);
	अगर (new == शून्य)
		वापस शून्य;

	क्रम (i = 0; i < page_count; i++)
		new->pages[i] = शून्य;
	new->page_count = 0;
	new->type = type;
	new->num_scratch_pages = pages;

	वापस new;
पूर्ण
EXPORT_SYMBOL(agp_generic_alloc_user);

/*
 * Basic Page Allocation Routines -
 * These routines handle page allocation and by शेष they reserve the allocated
 * memory.  They also handle incrementing the current_memory_agp value, Which is checked
 * against a maximum value.
 */

पूर्णांक agp_generic_alloc_pages(काष्ठा agp_bridge_data *bridge, काष्ठा agp_memory *mem, माप_प्रकार num_pages)
अणु
	काष्ठा page * page;
	पूर्णांक i, ret = -ENOMEM;

	क्रम (i = 0; i < num_pages; i++) अणु
		page = alloc_page(GFP_KERNEL | GFP_DMA32 | __GFP_ZERO);
		/* agp_मुक्त_memory() needs gart address */
		अगर (page == शून्य)
			जाओ out;

#अगर_अघोषित CONFIG_X86
		map_page_पूर्णांकo_agp(page);
#पूर्ण_अगर
		get_page(page);
		atomic_inc(&agp_bridge->current_memory_agp);

		mem->pages[i] = page;
		mem->page_count++;
	पूर्ण

#अगर_घोषित CONFIG_X86
	set_pages_array_uc(mem->pages, num_pages);
#पूर्ण_अगर
	ret = 0;
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(agp_generic_alloc_pages);

काष्ठा page *agp_generic_alloc_page(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा page * page;

	page = alloc_page(GFP_KERNEL | GFP_DMA32 | __GFP_ZERO);
	अगर (page == शून्य)
		वापस शून्य;

	map_page_पूर्णांकo_agp(page);

	get_page(page);
	atomic_inc(&agp_bridge->current_memory_agp);
	वापस page;
पूर्ण
EXPORT_SYMBOL(agp_generic_alloc_page);

व्योम agp_generic_destroy_pages(काष्ठा agp_memory *mem)
अणु
	पूर्णांक i;
	काष्ठा page *page;

	अगर (!mem)
		वापस;

#अगर_घोषित CONFIG_X86
	set_pages_array_wb(mem->pages, mem->page_count);
#पूर्ण_अगर

	क्रम (i = 0; i < mem->page_count; i++) अणु
		page = mem->pages[i];

#अगर_अघोषित CONFIG_X86
		unmap_page_from_agp(page);
#पूर्ण_अगर
		put_page(page);
		__मुक्त_page(page);
		atomic_dec(&agp_bridge->current_memory_agp);
		mem->pages[i] = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(agp_generic_destroy_pages);

व्योम agp_generic_destroy_page(काष्ठा page *page, पूर्णांक flags)
अणु
	अगर (page == शून्य)
		वापस;

	अगर (flags & AGP_PAGE_DESTROY_UNMAP)
		unmap_page_from_agp(page);

	अगर (flags & AGP_PAGE_DESTROY_FREE) अणु
		put_page(page);
		__मुक्त_page(page);
		atomic_dec(&agp_bridge->current_memory_agp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(agp_generic_destroy_page);

/* End Basic Page Allocation Routines */


/**
 * agp_enable  -  initialise the agp poपूर्णांक-to-poपूर्णांक connection.
 *
 * @bridge: an agp_bridge_data काष्ठा allocated क्रम the AGP host bridge.
 * @mode:	agp mode रेजिस्टर value to configure with.
 */
व्योम agp_enable(काष्ठा agp_bridge_data *bridge, u32 mode)
अणु
	अगर (!bridge)
		वापस;
	bridge->driver->agp_enable(bridge, mode);
पूर्ण
EXPORT_SYMBOL(agp_enable);

/* When we हटाओ the global variable agp_bridge from all drivers
 * then agp_alloc_bridge and agp_generic_find_bridge need to be updated
 */

काष्ठा agp_bridge_data *agp_generic_find_bridge(काष्ठा pci_dev *pdev)
अणु
	अगर (list_empty(&agp_bridges))
		वापस शून्य;

	वापस agp_bridge;
पूर्ण

अटल व्योम ipi_handler(व्योम *null)
अणु
	flush_agp_cache();
पूर्ण

व्योम global_cache_flush(व्योम)
अणु
	on_each_cpu(ipi_handler, शून्य, 1);
पूर्ण
EXPORT_SYMBOL(global_cache_flush);

अचिन्हित दीर्घ agp_generic_mask_memory(काष्ठा agp_bridge_data *bridge,
				      dma_addr_t addr, पूर्णांक type)
अणु
	/* memory type is ignored in the generic routine */
	अगर (bridge->driver->masks)
		वापस addr | bridge->driver->masks[0].mask;
	अन्यथा
		वापस addr;
पूर्ण
EXPORT_SYMBOL(agp_generic_mask_memory);

पूर्णांक agp_generic_type_to_mask_type(काष्ठा agp_bridge_data *bridge,
				  पूर्णांक type)
अणु
	अगर (type >= AGP_USER_TYPES)
		वापस 0;
	वापस type;
पूर्ण
EXPORT_SYMBOL(agp_generic_type_to_mask_type);

/*
 * These functions are implemented according to the AGPv3 spec,
 * which covers implementation details that had previously been
 * left खोलो.
 */

पूर्णांक agp3_generic_fetch_size(व्योम)
अणु
	u16 temp_size;
	पूर्णांक i;
	काष्ठा aper_size_info_16 *values;

	pci_पढ़ो_config_word(agp_bridge->dev, agp_bridge->capndx+AGPAPSIZE, &temp_size);
	values = A_SIZE_16(agp_bridge->driver->aperture_sizes);

	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		अगर (temp_size == values[i].size_value) अणु
			agp_bridge->previous_size =
				agp_bridge->current_size = (व्योम *) (values + i);

			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(agp3_generic_fetch_size);

व्योम agp3_generic_tlbflush(काष्ठा agp_memory *mem)
अणु
	u32 ctrl;
	pci_पढ़ो_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPCTRL, &ctrl);
	pci_ग_लिखो_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPCTRL, ctrl & ~AGPCTRL_GTLBEN);
	pci_ग_लिखो_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPCTRL, ctrl);
पूर्ण
EXPORT_SYMBOL(agp3_generic_tlbflush);

पूर्णांक agp3_generic_configure(व्योम)
अणु
	u32 temp;
	काष्ठा aper_size_info_16 *current_size;

	current_size = A_SIZE_16(agp_bridge->current_size);

	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* set aperture size */
	pci_ग_लिखो_config_word(agp_bridge->dev, agp_bridge->capndx+AGPAPSIZE, current_size->size_value);
	/* set gart poपूर्णांकer */
	pci_ग_लिखो_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPGARTLO, agp_bridge->gatt_bus_addr);
	/* enable aperture and GTLB */
	pci_पढ़ो_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPCTRL, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPCTRL, temp | AGPCTRL_APERENB | AGPCTRL_GTLBEN);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(agp3_generic_configure);

व्योम agp3_generic_cleanup(व्योम)
अणु
	u32 ctrl;
	pci_पढ़ो_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPCTRL, &ctrl);
	pci_ग_लिखो_config_dword(agp_bridge->dev, agp_bridge->capndx+AGPCTRL, ctrl & ~AGPCTRL_APERENB);
पूर्ण
EXPORT_SYMBOL(agp3_generic_cleanup);

स्थिर काष्ठा aper_size_info_16 agp3_generic_sizes[AGP_GENERIC_SIZES_ENTRIES] =
अणु
	अणु4096, 1048576, 10,0x000पूर्ण,
	अणु2048,  524288, 9, 0x800पूर्ण,
	अणु1024,  262144, 8, 0xc00पूर्ण,
	अणु 512,  131072, 7, 0xe00पूर्ण,
	अणु 256,   65536, 6, 0xf00पूर्ण,
	अणु 128,   32768, 5, 0xf20पूर्ण,
	अणु  64,   16384, 4, 0xf30पूर्ण,
	अणु  32,    8192, 3, 0xf38पूर्ण,
	अणु  16,    4096, 2, 0xf3cपूर्ण,
	अणु   8,    2048, 1, 0xf3eपूर्ण,
	अणु   4,    1024, 0, 0xf3fपूर्ण
पूर्ण;
EXPORT_SYMBOL(agp3_generic_sizes);

