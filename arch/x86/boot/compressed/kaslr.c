<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kaslr.c
 *
 * This contains the routines needed to generate a reasonable level of
 * entropy to choose a अक्रमomized kernel base address offset in support
 * of Kernel Address Space Layout Ranकरोmization (KASLR). Additionally
 * handles walking the physical memory maps (and tracking memory regions
 * to aव्योम) in order to select a physical memory location that can
 * contain the entire properly aligned running kernel image.
 *
 */

/*
 * है_खाली() in linux/प्रकार.स is expected by next_args() to filter
 * out "space/lf/tab". While boot/प्रकार.स conflicts with linux/प्रकार.स,
 * since है_अंक() is implemented in both of them. Hence disable it
 * here.
 */
#घोषणा BOOT_CTYPE_H

#समावेश "misc.h"
#समावेश "error.h"
#समावेश "../string.h"

#समावेश <generated/compile.h>
#समावेश <linux/module.h>
#समावेश <linux/uts.h>
#समावेश <linux/utsname.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/efi.h>
#समावेश <generated/utsrelease.h>
#समावेश <यंत्र/efi.h>

/* Macros used by the included decompressor code below. */
#घोषणा STATIC
#समावेश <linux/decompress/mm.h>

#घोषणा _SETUP
#समावेश <यंत्र/setup.h>	/* For COMMAND_LINE_SIZE */
#अघोषित _SETUP

बाह्य अचिन्हित दीर्घ get_cmd_line_ptr(व्योम);

/* Simplअगरied build-specअगरic string क्रम starting entropy. */
अटल स्थिर अक्षर build_str[] = UTS_RELEASE " (" LINUX_COMPILE_BY "@"
		LINUX_COMPILE_HOST ") (" LINUX_COMPILER ") " UTS_VERSION;

अटल अचिन्हित दीर्घ rotate_xor(अचिन्हित दीर्घ hash, स्थिर व्योम *area,
				माप_प्रकार size)
अणु
	माप_प्रकार i;
	अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)area;

	क्रम (i = 0; i < size / माप(hash); i++) अणु
		/* Rotate by odd number of bits and XOR. */
		hash = (hash << ((माप(hash) * 8) - 7)) | (hash >> 7);
		hash ^= ptr[i];
	पूर्ण

	वापस hash;
पूर्ण

/* Attempt to create a simple but unpredictable starting entropy. */
अटल अचिन्हित दीर्घ get_boot_seed(व्योम)
अणु
	अचिन्हित दीर्घ hash = 0;

	hash = rotate_xor(hash, build_str, माप(build_str));
	hash = rotate_xor(hash, boot_params, माप(*boot_params));

	वापस hash;
पूर्ण

#घोषणा KASLR_COMPRESSED_BOOT
#समावेश "../../lib/kaslr.c"


/* Only supporting at most 4 unusable memmap regions with kaslr */
#घोषणा MAX_MEMMAP_REGIONS	4

अटल bool memmap_too_large;


/*
 * Store memory limit: MAXMEM on 64-bit and KERNEL_IMAGE_SIZE on 32-bit.
 * It may be reduced by "mem=nn[KMG]" or "memmap=nn[KMG]" command line options.
 */
अटल u64 mem_limit;

/* Number of immovable memory regions */
अटल पूर्णांक num_immovable_mem;

क्रमागत mem_aव्योम_index अणु
	MEM_AVOID_ZO_RANGE = 0,
	MEM_AVOID_INITRD,
	MEM_AVOID_CMDLINE,
	MEM_AVOID_BOOTPARAMS,
	MEM_AVOID_MEMMAP_BEGIN,
	MEM_AVOID_MEMMAP_END = MEM_AVOID_MEMMAP_BEGIN + MAX_MEMMAP_REGIONS - 1,
	MEM_AVOID_MAX,
पूर्ण;

अटल काष्ठा mem_vector mem_aव्योम[MEM_AVOID_MAX];

अटल bool mem_overlaps(काष्ठा mem_vector *one, काष्ठा mem_vector *two)
अणु
	/* Item one is entirely beक्रमe item two. */
	अगर (one->start + one->size <= two->start)
		वापस false;
	/* Item one is entirely after item two. */
	अगर (one->start >= two->start + two->size)
		वापस false;
	वापस true;
पूर्ण

अक्षर *skip_spaces(स्थिर अक्षर *str)
अणु
	जबतक (है_खाली(*str))
		++str;
	वापस (अक्षर *)str;
पूर्ण
#समावेश "../../../../lib/ctype.c"
#समावेश "../../../../lib/cmdline.c"

क्रमागत parse_mode अणु
	PARSE_MEMMAP,
	PARSE_EFI,
पूर्ण;

अटल पूर्णांक
parse_memmap(अक्षर *p, u64 *start, u64 *size, क्रमागत parse_mode mode)
अणु
	अक्षर *oldp;

	अगर (!p)
		वापस -EINVAL;

	/* We करोn't care about this option here */
	अगर (!म_भेदन(p, "exactmap", 8))
		वापस -EINVAL;

	oldp = p;
	*size = memparse(p, &p);
	अगर (p == oldp)
		वापस -EINVAL;

	चयन (*p) अणु
	हाल '#':
	हाल '$':
	हाल '!':
		*start = memparse(p + 1, &p);
		वापस 0;
	हाल '@':
		अगर (mode == PARSE_MEMMAP) अणु
			/*
			 * memmap=nn@ss specअगरies usable region, should
			 * be skipped
			 */
			*size = 0;
		पूर्ण अन्यथा अणु
			u64 flags;

			/*
			 * efi_fake_mem=nn@ss:attr the attr specअगरies
			 * flags that might imply a soft-reservation.
			 */
			*start = memparse(p + 1, &p);
			अगर (p && *p == ':') अणु
				p++;
				अगर (kम_से_अदीर्घl(p, 0, &flags) < 0)
					*size = 0;
				अन्यथा अगर (flags & EFI_MEMORY_SP)
					वापस 0;
			पूर्ण
			*size = 0;
		पूर्ण
		fallthrough;
	शेष:
		/*
		 * If w/o offset, only size specअगरied, memmap=nn[KMG] has the
		 * same behaviour as mem=nn[KMG]. It limits the max address
		 * प्रणाली can use. Region above the limit should be aव्योमed.
		 */
		*start = 0;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम mem_aव्योम_memmap(क्रमागत parse_mode mode, अक्षर *str)
अणु
	अटल पूर्णांक i;

	अगर (i >= MAX_MEMMAP_REGIONS)
		वापस;

	जबतक (str && (i < MAX_MEMMAP_REGIONS)) अणु
		पूर्णांक rc;
		u64 start, size;
		अक्षर *k = म_अक्षर(str, ',');

		अगर (k)
			*k++ = 0;

		rc = parse_memmap(str, &start, &size, mode);
		अगर (rc < 0)
			अवरोध;
		str = k;

		अगर (start == 0) अणु
			/* Store the specअगरied memory limit अगर size > 0 */
			अगर (size > 0 && size < mem_limit)
				mem_limit = size;

			जारी;
		पूर्ण

		mem_aव्योम[MEM_AVOID_MEMMAP_BEGIN + i].start = start;
		mem_aव्योम[MEM_AVOID_MEMMAP_BEGIN + i].size = size;
		i++;
	पूर्ण

	/* More than 4 memmaps, fail kaslr */
	अगर ((i >= MAX_MEMMAP_REGIONS) && str)
		memmap_too_large = true;
पूर्ण

/* Store the number of 1GB huge pages which users specअगरied: */
अटल अचिन्हित दीर्घ max_gb_huge_pages;

अटल व्योम parse_gb_huge_pages(अक्षर *param, अक्षर *val)
अणु
	अटल bool gbpage_sz;
	अक्षर *p;

	अगर (!म_भेद(param, "hugepagesz")) अणु
		p = val;
		अगर (memparse(p, &p) != PUD_SIZE) अणु
			gbpage_sz = false;
			वापस;
		पूर्ण

		अगर (gbpage_sz)
			warn("Repeatedly set hugeTLB page size of 1G!\n");
		gbpage_sz = true;
		वापस;
	पूर्ण

	अगर (!म_भेद(param, "hugepages") && gbpage_sz) अणु
		p = val;
		max_gb_huge_pages = simple_म_से_अदीर्घl(p, &p, 0);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम handle_mem_options(व्योम)
अणु
	अक्षर *args = (अक्षर *)get_cmd_line_ptr();
	माप_प्रकार len;
	अक्षर *पंचांगp_cmdline;
	अक्षर *param, *val;
	u64 mem_size;

	अगर (!args)
		वापस;

	len = strnlen(args, COMMAND_LINE_SIZE-1);
	पंचांगp_cmdline = दो_स्मृति(len + 1);
	अगर (!पंचांगp_cmdline)
		error("Failed to allocate space for tmp_cmdline");

	स_नकल(पंचांगp_cmdline, args, len);
	पंचांगp_cmdline[len] = 0;
	args = पंचांगp_cmdline;

	/* Chew leading spaces */
	args = skip_spaces(args);

	जबतक (*args) अणु
		args = next_arg(args, &param, &val);
		/* Stop at -- */
		अगर (!val && म_भेद(param, "--") == 0)
			अवरोध;

		अगर (!म_भेद(param, "memmap")) अणु
			mem_aव्योम_memmap(PARSE_MEMMAP, val);
		पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_X86_64) && म_माला(param, "hugepages")) अणु
			parse_gb_huge_pages(param, val);
		पूर्ण अन्यथा अगर (!म_भेद(param, "mem")) अणु
			अक्षर *p = val;

			अगर (!म_भेद(p, "nopentium"))
				जारी;
			mem_size = memparse(p, &p);
			अगर (mem_size == 0)
				अवरोध;

			अगर (mem_size < mem_limit)
				mem_limit = mem_size;
		पूर्ण अन्यथा अगर (!म_भेद(param, "efi_fake_mem")) अणु
			mem_aव्योम_memmap(PARSE_EFI, val);
		पूर्ण
	पूर्ण

	मुक्त(पंचांगp_cmdline);
	वापस;
पूर्ण

/*
 * In theory, KASLR can put the kernel anywhere in the range of [16M, MAXMEM)
 * on 64-bit, and [16M, KERNEL_IMAGE_SIZE) on 32-bit.
 *
 * The mem_aव्योम array is used to store the ranges that need to be aव्योमed
 * when KASLR searches क्रम an appropriate अक्रमom address. We must aव्योम any
 * regions that are unsafe to overlap with during decompression, and other
 * things like the initrd, cmdline and boot_params. This comment seeks to
 * explain mem_aव्योम as clearly as possible since incorrect mem_aव्योम
 * memory ranges lead to really hard to debug boot failures.
 *
 * The initrd, cmdline, and boot_params are trivial to identअगरy क्रम
 * aव्योमing. They are MEM_AVOID_INITRD, MEM_AVOID_CMDLINE, and
 * MEM_AVOID_BOOTPARAMS respectively below.
 *
 * What is not obvious how to aव्योम is the range of memory that is used
 * during decompression (MEM_AVOID_ZO_RANGE below). This range must cover
 * the compressed kernel (ZO) and its run space, which is used to extract
 * the uncompressed kernel (VO) and relocs.
 *
 * ZO's full run size sits against the end of the decompression buffer, so
 * we can calculate where text, data, bss, etc of ZO are positioned more
 * easily.
 *
 * For additional background, the decompression calculations can be found
 * in header.S, and the memory diagram is based on the one found in misc.c.
 *
 * The following conditions are alपढ़ोy enक्रमced by the image layouts and
 * associated code:
 *  - input + input_size >= output + output_size
 *  - kernel_total_size <= init_size
 *  - kernel_total_size <= output_size (see Note below)
 *  - output + init_size >= output + output_size
 *
 * (Note that kernel_total_size and output_size have no fundamental
 * relationship, but output_size is passed to choose_अक्रमom_location
 * as a maximum of the two. The diagram is showing a हाल where
 * kernel_total_size is larger than output_size, but this हाल is
 * handled by bumping output_size.)
 *
 * The above conditions can be illustrated by a diagram:
 *
 * 0   output            input            input+input_size    output+init_size
 * |     |                 |                             |             |
 * |     |                 |                             |             |
 * |-----|--------|--------|--------------|-----------|--|-------------|
 *                |                       |           |
 *                |                       |           |
 * output+init_size-ZO_INIT_SIZE  output+output_size  output+kernel_total_size
 *
 * [output, output+init_size) is the entire memory range used क्रम
 * extracting the compressed image.
 *
 * [output, output+kernel_total_size) is the range needed क्रम the
 * uncompressed kernel (VO) and its run size (bss, brk, etc).
 *
 * [output, output+output_size) is VO plus relocs (i.e. the entire
 * uncompressed payload contained by ZO). This is the area of the buffer
 * written to during decompression.
 *
 * [output+init_size-ZO_INIT_SIZE, output+init_size) is the worst-हाल
 * range of the copied ZO and decompression code. (i.e. the range
 * covered backwards of size ZO_INIT_SIZE, starting from output+init_size.)
 *
 * [input, input+input_size) is the original copied compressed image (ZO)
 * (i.e. it करोes not include its run size). This range must be aव्योमed
 * because it contains the data used क्रम decompression.
 *
 * [input+input_size, output+init_size) is [_text, _end) क्रम ZO. This
 * range includes ZO's heap and stack, and must be aव्योमed since it
 * perक्रमms the decompression.
 *
 * Since the above two ranges need to be aव्योमed and they are adjacent,
 * they can be merged, resulting in: [input, output+init_size) which
 * becomes the MEM_AVOID_ZO_RANGE below.
 */
अटल व्योम mem_aव्योम_init(अचिन्हित दीर्घ input, अचिन्हित दीर्घ input_size,
			   अचिन्हित दीर्घ output)
अणु
	अचिन्हित दीर्घ init_size = boot_params->hdr.init_size;
	u64 initrd_start, initrd_size;
	अचिन्हित दीर्घ cmd_line, cmd_line_size;

	/*
	 * Aव्योम the region that is unsafe to overlap during
	 * decompression.
	 */
	mem_aव्योम[MEM_AVOID_ZO_RANGE].start = input;
	mem_aव्योम[MEM_AVOID_ZO_RANGE].size = (output + init_size) - input;

	/* Aव्योम initrd. */
	initrd_start  = (u64)boot_params->ext_ramdisk_image << 32;
	initrd_start |= boot_params->hdr.ramdisk_image;
	initrd_size  = (u64)boot_params->ext_ramdisk_size << 32;
	initrd_size |= boot_params->hdr.ramdisk_size;
	mem_aव्योम[MEM_AVOID_INITRD].start = initrd_start;
	mem_aव्योम[MEM_AVOID_INITRD].size = initrd_size;
	/* No need to set mapping क्रम initrd, it will be handled in VO. */

	/* Aव्योम kernel command line. */
	cmd_line = get_cmd_line_ptr();
	/* Calculate size of cmd_line. */
	अगर (cmd_line) अणु
		cmd_line_size = strnlen((अक्षर *)cmd_line, COMMAND_LINE_SIZE-1) + 1;
		mem_aव्योम[MEM_AVOID_CMDLINE].start = cmd_line;
		mem_aव्योम[MEM_AVOID_CMDLINE].size = cmd_line_size;
	पूर्ण

	/* Aव्योम boot parameters. */
	mem_aव्योम[MEM_AVOID_BOOTPARAMS].start = (अचिन्हित दीर्घ)boot_params;
	mem_aव्योम[MEM_AVOID_BOOTPARAMS].size = माप(*boot_params);

	/* We करोn't need to set a mapping क्रम setup_data. */

	/* Mark the memmap regions we need to aव्योम */
	handle_mem_options();

	/* Enumerate the immovable memory regions */
	num_immovable_mem = count_immovable_mem_regions();
पूर्ण

/*
 * Does this memory vector overlap a known aव्योमed area? If so, record the
 * overlap region with the lowest address.
 */
अटल bool mem_aव्योम_overlap(काष्ठा mem_vector *img,
			      काष्ठा mem_vector *overlap)
अणु
	पूर्णांक i;
	काष्ठा setup_data *ptr;
	u64 earliest = img->start + img->size;
	bool is_overlapping = false;

	क्रम (i = 0; i < MEM_AVOID_MAX; i++) अणु
		अगर (mem_overlaps(img, &mem_aव्योम[i]) &&
		    mem_aव्योम[i].start < earliest) अणु
			*overlap = mem_aव्योम[i];
			earliest = overlap->start;
			is_overlapping = true;
		पूर्ण
	पूर्ण

	/* Aव्योम all entries in the setup_data linked list. */
	ptr = (काष्ठा setup_data *)(अचिन्हित दीर्घ)boot_params->hdr.setup_data;
	जबतक (ptr) अणु
		काष्ठा mem_vector aव्योम;

		aव्योम.start = (अचिन्हित दीर्घ)ptr;
		aव्योम.size = माप(*ptr) + ptr->len;

		अगर (mem_overlaps(img, &aव्योम) && (aव्योम.start < earliest)) अणु
			*overlap = aव्योम;
			earliest = overlap->start;
			is_overlapping = true;
		पूर्ण

		अगर (ptr->type == SETUP_INसूचीECT &&
		    ((काष्ठा setup_indirect *)ptr->data)->type != SETUP_INसूचीECT) अणु
			aव्योम.start = ((काष्ठा setup_indirect *)ptr->data)->addr;
			aव्योम.size = ((काष्ठा setup_indirect *)ptr->data)->len;

			अगर (mem_overlaps(img, &aव्योम) && (aव्योम.start < earliest)) अणु
				*overlap = aव्योम;
				earliest = overlap->start;
				is_overlapping = true;
			पूर्ण
		पूर्ण

		ptr = (काष्ठा setup_data *)(अचिन्हित दीर्घ)ptr->next;
	पूर्ण

	वापस is_overlapping;
पूर्ण

काष्ठा slot_area अणु
	u64 addr;
	अचिन्हित दीर्घ num;
पूर्ण;

#घोषणा MAX_SLOT_AREA 100

अटल काष्ठा slot_area slot_areas[MAX_SLOT_AREA];
अटल अचिन्हित पूर्णांक slot_area_index;
अटल अचिन्हित दीर्घ slot_max;

अटल व्योम store_slot_info(काष्ठा mem_vector *region, अचिन्हित दीर्घ image_size)
अणु
	काष्ठा slot_area slot_area;

	अगर (slot_area_index == MAX_SLOT_AREA)
		वापस;

	slot_area.addr = region->start;
	slot_area.num = 1 + (region->size - image_size) / CONFIG_PHYSICAL_ALIGN;

	slot_areas[slot_area_index++] = slot_area;
	slot_max += slot_area.num;
पूर्ण

/*
 * Skip as many 1GB huge pages as possible in the passed region
 * according to the number which users specअगरied:
 */
अटल व्योम
process_gb_huge_pages(काष्ठा mem_vector *region, अचिन्हित दीर्घ image_size)
अणु
	u64 pud_start, pud_end;
	अचिन्हित दीर्घ gb_huge_pages;
	काष्ठा mem_vector पंचांगp;

	अगर (!IS_ENABLED(CONFIG_X86_64) || !max_gb_huge_pages) अणु
		store_slot_info(region, image_size);
		वापस;
	पूर्ण

	/* Are there any 1GB pages in the region? */
	pud_start = ALIGN(region->start, PUD_SIZE);
	pud_end = ALIGN_DOWN(region->start + region->size, PUD_SIZE);

	/* No good 1GB huge pages found: */
	अगर (pud_start >= pud_end) अणु
		store_slot_info(region, image_size);
		वापस;
	पूर्ण

	/* Check अगर the head part of the region is usable. */
	अगर (pud_start >= region->start + image_size) अणु
		पंचांगp.start = region->start;
		पंचांगp.size = pud_start - region->start;
		store_slot_info(&पंचांगp, image_size);
	पूर्ण

	/* Skip the good 1GB pages. */
	gb_huge_pages = (pud_end - pud_start) >> PUD_SHIFT;
	अगर (gb_huge_pages > max_gb_huge_pages) अणु
		pud_end = pud_start + (max_gb_huge_pages << PUD_SHIFT);
		max_gb_huge_pages = 0;
	पूर्ण अन्यथा अणु
		max_gb_huge_pages -= gb_huge_pages;
	पूर्ण

	/* Check अगर the tail part of the region is usable. */
	अगर (region->start + region->size >= pud_end + image_size) अणु
		पंचांगp.start = pud_end;
		पंचांगp.size = region->start + region->size - pud_end;
		store_slot_info(&पंचांगp, image_size);
	पूर्ण
पूर्ण

अटल u64 slots_fetch_अक्रमom(व्योम)
अणु
	अचिन्हित दीर्घ slot;
	अचिन्हित पूर्णांक i;

	/* Handle हाल of no slots stored. */
	अगर (slot_max == 0)
		वापस 0;

	slot = kaslr_get_अक्रमom_दीर्घ("Physical") % slot_max;

	क्रम (i = 0; i < slot_area_index; i++) अणु
		अगर (slot >= slot_areas[i].num) अणु
			slot -= slot_areas[i].num;
			जारी;
		पूर्ण
		वापस slot_areas[i].addr + ((u64)slot * CONFIG_PHYSICAL_ALIGN);
	पूर्ण

	अगर (i == slot_area_index)
		debug_माला_दोtr("slots_fetch_random() failed!?\n");
	वापस 0;
पूर्ण

अटल व्योम __process_mem_region(काष्ठा mem_vector *entry,
				 अचिन्हित दीर्घ minimum,
				 अचिन्हित दीर्घ image_size)
अणु
	काष्ठा mem_vector region, overlap;
	u64 region_end;

	/* Enक्रमce minimum and memory limit. */
	region.start = max_t(u64, entry->start, minimum);
	region_end = min(entry->start + entry->size, mem_limit);

	/* Give up अगर slot area array is full. */
	जबतक (slot_area_index < MAX_SLOT_AREA) अणु
		/* Potentially उठाओ address to meet alignment needs. */
		region.start = ALIGN(region.start, CONFIG_PHYSICAL_ALIGN);

		/* Did we उठाओ the address above the passed in memory entry? */
		अगर (region.start > region_end)
			वापस;

		/* Reduce size by any delta from the original address. */
		region.size = region_end - region.start;

		/* Return अगर region can't contain decompressed kernel */
		अगर (region.size < image_size)
			वापस;

		/* If nothing overlaps, store the region and वापस. */
		अगर (!mem_aव्योम_overlap(&region, &overlap)) अणु
			process_gb_huge_pages(&region, image_size);
			वापस;
		पूर्ण

		/* Store beginning of region अगर holds at least image_size. */
		अगर (overlap.start >= region.start + image_size) अणु
			region.size = overlap.start - region.start;
			process_gb_huge_pages(&region, image_size);
		पूर्ण

		/* Clip off the overlapping region and start over. */
		region.start = overlap.start + overlap.size;
	पूर्ण
पूर्ण

अटल bool process_mem_region(काष्ठा mem_vector *region,
			       अचिन्हित दीर्घ minimum,
			       अचिन्हित दीर्घ image_size)
अणु
	पूर्णांक i;
	/*
	 * If no immovable memory found, or MEMORY_HOTREMOVE disabled,
	 * use @region directly.
	 */
	अगर (!num_immovable_mem) अणु
		__process_mem_region(region, minimum, image_size);

		अगर (slot_area_index == MAX_SLOT_AREA) अणु
			debug_माला_दोtr("Aborted e820/efi memmap scan (slot_areas full)!\n");
			वापस true;
		पूर्ण
		वापस false;
	पूर्ण

#अगर defined(CONFIG_MEMORY_HOTREMOVE) && defined(CONFIG_ACPI)
	/*
	 * If immovable memory found, filter the पूर्णांकersection between
	 * immovable memory and @region.
	 */
	क्रम (i = 0; i < num_immovable_mem; i++) अणु
		u64 start, end, entry_end, region_end;
		काष्ठा mem_vector entry;

		अगर (!mem_overlaps(region, &immovable_mem[i]))
			जारी;

		start = immovable_mem[i].start;
		end = start + immovable_mem[i].size;
		region_end = region->start + region->size;

		entry.start = clamp(region->start, start, end);
		entry_end = clamp(region_end, start, end);
		entry.size = entry_end - entry.start;

		__process_mem_region(&entry, minimum, image_size);

		अगर (slot_area_index == MAX_SLOT_AREA) अणु
			debug_माला_दोtr("Aborted e820/efi memmap scan when walking immovable regions(slot_areas full)!\n");
			वापस 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_EFI
/*
 * Returns true अगर we processed the EFI memmap, which we prefer over the E820
 * table अगर it is available.
 */
अटल bool
process_efi_entries(अचिन्हित दीर्घ minimum, अचिन्हित दीर्घ image_size)
अणु
	काष्ठा efi_info *e = &boot_params->efi_info;
	bool efi_mirror_found = false;
	काष्ठा mem_vector region;
	efi_memory_desc_t *md;
	अचिन्हित दीर्घ pmap;
	अक्षर *signature;
	u32 nr_desc;
	पूर्णांक i;

	signature = (अक्षर *)&e->efi_loader_signature;
	अगर (म_भेदन(signature, EFI32_LOADER_SIGNATURE, 4) &&
	    म_भेदन(signature, EFI64_LOADER_SIGNATURE, 4))
		वापस false;

#अगर_घोषित CONFIG_X86_32
	/* Can't handle data above 4GB at this समय */
	अगर (e->efi_memmap_hi) अणु
		warn("EFI memmap is above 4GB, can't be handled now on x86_32. EFI should be disabled.\n");
		वापस false;
	पूर्ण
	pmap =  e->efi_memmap;
#अन्यथा
	pmap = (e->efi_memmap | ((__u64)e->efi_memmap_hi << 32));
#पूर्ण_अगर

	nr_desc = e->efi_memmap_size / e->efi_memdesc_size;
	क्रम (i = 0; i < nr_desc; i++) अणु
		md = efi_early_memdesc_ptr(pmap, e->efi_memdesc_size, i);
		अगर (md->attribute & EFI_MEMORY_MORE_RELIABLE) अणु
			efi_mirror_found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nr_desc; i++) अणु
		md = efi_early_memdesc_ptr(pmap, e->efi_memdesc_size, i);

		/*
		 * Here we are more conservative in picking मुक्त memory than
		 * the EFI spec allows:
		 *
		 * According to the spec, EFI_BOOT_SERVICES_अणुCODE|DATAपूर्ण are also
		 * मुक्त memory and thus available to place the kernel image पूर्णांकo,
		 * but in practice there's firmware where using that memory leads
		 * to crashes.
		 *
		 * Only EFI_CONVENTIONAL_MEMORY is guaranteed to be मुक्त.
		 */
		अगर (md->type != EFI_CONVENTIONAL_MEMORY)
			जारी;

		अगर (efi_soft_reserve_enabled() &&
		    (md->attribute & EFI_MEMORY_SP))
			जारी;

		अगर (efi_mirror_found &&
		    !(md->attribute & EFI_MEMORY_MORE_RELIABLE))
			जारी;

		region.start = md->phys_addr;
		region.size = md->num_pages << EFI_PAGE_SHIFT;
		अगर (process_mem_region(&region, minimum, image_size))
			अवरोध;
	पूर्ण
	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool
process_efi_entries(अचिन्हित दीर्घ minimum, अचिन्हित दीर्घ image_size)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल व्योम process_e820_entries(अचिन्हित दीर्घ minimum,
				 अचिन्हित दीर्घ image_size)
अणु
	पूर्णांक i;
	काष्ठा mem_vector region;
	काष्ठा boot_e820_entry *entry;

	/* Verअगरy potential e820 positions, appending to slots list. */
	क्रम (i = 0; i < boot_params->e820_entries; i++) अणु
		entry = &boot_params->e820_table[i];
		/* Skip non-RAM entries. */
		अगर (entry->type != E820_TYPE_RAM)
			जारी;
		region.start = entry->addr;
		region.size = entry->size;
		अगर (process_mem_region(&region, minimum, image_size))
			अवरोध;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ find_अक्रमom_phys_addr(अचिन्हित दीर्घ minimum,
					   अचिन्हित दीर्घ image_size)
अणु
	u64 phys_addr;

	/* Bail out early अगर it's impossible to succeed. */
	अगर (minimum + image_size > mem_limit)
		वापस 0;

	/* Check अगर we had too many memmaps. */
	अगर (memmap_too_large) अणु
		debug_माला_दोtr("Aborted memory entries scan (more than 4 memmap= args)!\n");
		वापस 0;
	पूर्ण

	अगर (!process_efi_entries(minimum, image_size))
		process_e820_entries(minimum, image_size);

	phys_addr = slots_fetch_अक्रमom();

	/* Perक्रमm a final check to make sure the address is in range. */
	अगर (phys_addr < minimum || phys_addr + image_size > mem_limit) अणु
		warn("Invalid physical address chosen!\n");
		वापस 0;
	पूर्ण

	वापस (अचिन्हित दीर्घ)phys_addr;
पूर्ण

अटल अचिन्हित दीर्घ find_अक्रमom_virt_addr(अचिन्हित दीर्घ minimum,
					   अचिन्हित दीर्घ image_size)
अणु
	अचिन्हित दीर्घ slots, अक्रमom_addr;

	/*
	 * There are how many CONFIG_PHYSICAL_ALIGN-sized slots
	 * that can hold image_size within the range of minimum to
	 * KERNEL_IMAGE_SIZE?
	 */
	slots = 1 + (KERNEL_IMAGE_SIZE - minimum - image_size) / CONFIG_PHYSICAL_ALIGN;

	अक्रमom_addr = kaslr_get_अक्रमom_दीर्घ("Virtual") % slots;

	वापस अक्रमom_addr * CONFIG_PHYSICAL_ALIGN + minimum;
पूर्ण

/*
 * Since this function examines addresses much more numerically,
 * it takes the input and output poपूर्णांकers as 'unsigned long'.
 */
व्योम choose_अक्रमom_location(अचिन्हित दीर्घ input,
			    अचिन्हित दीर्घ input_size,
			    अचिन्हित दीर्घ *output,
			    अचिन्हित दीर्घ output_size,
			    अचिन्हित दीर्घ *virt_addr)
अणु
	अचिन्हित दीर्घ अक्रमom_addr, min_addr;

	अगर (cmdline_find_option_bool("nokaslr")) अणु
		warn("KASLR disabled: 'nokaslr' on cmdline.");
		वापस;
	पूर्ण

	boot_params->hdr.loadflags |= KASLR_FLAG;

	अगर (IS_ENABLED(CONFIG_X86_32))
		mem_limit = KERNEL_IMAGE_SIZE;
	अन्यथा
		mem_limit = MAXMEM;

	/* Record the various known unsafe memory ranges. */
	mem_aव्योम_init(input, input_size, *output);

	/*
	 * Low end of the अक्रमomization range should be the
	 * smaller of 512M or the initial kernel image
	 * location:
	 */
	min_addr = min(*output, 512UL << 20);
	/* Make sure minimum is aligned. */
	min_addr = ALIGN(min_addr, CONFIG_PHYSICAL_ALIGN);

	/* Walk available memory entries to find a अक्रमom address. */
	अक्रमom_addr = find_अक्रमom_phys_addr(min_addr, output_size);
	अगर (!अक्रमom_addr) अणु
		warn("Physical KASLR disabled: no suitable memory region!");
	पूर्ण अन्यथा अणु
		/* Update the new physical address location. */
		अगर (*output != अक्रमom_addr)
			*output = अक्रमom_addr;
	पूर्ण


	/* Pick अक्रमom भव address starting from LOAD_PHYSICAL_ADDR. */
	अगर (IS_ENABLED(CONFIG_X86_64))
		अक्रमom_addr = find_अक्रमom_virt_addr(LOAD_PHYSICAL_ADDR, output_size);
	*virt_addr = अक्रमom_addr;
पूर्ण
