<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/video/console/sticore.c -
 *	core code क्रम console driver using HP's STI firmware
 *
 *	Copyright (C) 2000 Philipp Rumpf <prumpf@tux.org>
 *	Copyright (C) 2001-2020 Helge Deller <deller@gmx.de>
 *	Copyright (C) 2001-2002 Thomas Bogenकरोerfer <tsbogend@alpha.franken.de>
 * 
 * TODO:
 * - call STI in भव mode rather than in real mode
 * - screen blanking with state_mgmt() in text mode STI ? 
 * - try to make it work on m68k hp workstations ;)
 * 
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, KBUILD_MODNAME

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/font.h>

#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/grfioctl.h>

#समावेश "../fbdev/sticore.h"

#घोषणा STI_DRIVERVERSION "Version 0.9b"

अटल काष्ठा sti_काष्ठा *शेष_sti __पढ़ो_mostly;

/* number of STI ROMS found and their ptrs to each काष्ठा */
अटल पूर्णांक num_sti_roms __पढ़ो_mostly;
अटल काष्ठा sti_काष्ठा *sti_roms[MAX_STI_ROMS] __पढ़ो_mostly;


/* The colour indices used by STI are
 *   0 - Black
 *   1 - White
 *   2 - Red
 *   3 - Yellow/Brown
 *   4 - Green
 *   5 - Cyan
 *   6 - Blue
 *   7 - Magenta
 *
 * So we have the same colours as VGA (basically one bit each क्रम R, G, B),
 * but have to translate them, anyway. */

अटल स्थिर u8 col_trans[8] = अणु
        0, 6, 4, 5,
        2, 7, 3, 1
पूर्ण;

#घोषणा c_fg(sti, c) col_trans[((c>> 8) & 7)]
#घोषणा c_bg(sti, c) col_trans[((c>>11) & 7)]
#घोषणा c_index(sti, c) ((c) & 0xff)

अटल स्थिर काष्ठा sti_init_flags शेष_init_flags = अणु
	.रुको	= STI_WAIT, 
	.reset	= 1,
	.text	= 1, 
	.nontext = 1,
	.no_chg_bet = 1, 
	.no_chg_bei = 1, 
	.init_cmap_tx = 1,
पूर्ण;

अटल पूर्णांक sti_init_graph(काष्ठा sti_काष्ठा *sti)
अणु
	काष्ठा sti_init_inptr *inptr = &sti->sti_data->init_inptr;
	काष्ठा sti_init_inptr_ext *inptr_ext = &sti->sti_data->init_inptr_ext;
	काष्ठा sti_init_outptr *outptr = &sti->sti_data->init_outptr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, err;

	spin_lock_irqsave(&sti->lock, flags);

	स_रखो(inptr, 0, माप(*inptr));
	inptr->text_planes = 3; /* # of text planes (max 3 क्रम STI) */
	स_रखो(inptr_ext, 0, माप(*inptr_ext));
	inptr->ext_ptr = STI_PTR(inptr_ext);
	outptr->त्रुटि_सं = 0;

	ret = sti_call(sti, sti->init_graph, &शेष_init_flags, inptr,
		outptr, sti->glob_cfg);

	अगर (ret >= 0)
		sti->text_planes = outptr->text_planes;
	err = outptr->त्रुटि_सं;

	spin_unlock_irqrestore(&sti->lock, flags);

	अगर (ret < 0) अणु
		pr_err("STI init_graph failed (ret %d, errno %d)\n", ret, err);
		वापस -1;
	पूर्ण
	
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sti_conf_flags शेष_conf_flags = अणु
	.रुको	= STI_WAIT,
पूर्ण;

अटल व्योम sti_inq_conf(काष्ठा sti_काष्ठा *sti)
अणु
	काष्ठा sti_conf_inptr *inptr = &sti->sti_data->inq_inptr;
	काष्ठा sti_conf_outptr *outptr = &sti->sti_data->inq_outptr;
	अचिन्हित दीर्घ flags;
	s32 ret;

	outptr->ext_ptr = STI_PTR(&sti->sti_data->inq_outptr_ext);
	
	करो अणु
		spin_lock_irqsave(&sti->lock, flags);
		स_रखो(inptr, 0, माप(*inptr));
		ret = sti_call(sti, sti->inq_conf, &शेष_conf_flags,
			inptr, outptr, sti->glob_cfg);
		spin_unlock_irqrestore(&sti->lock, flags);
	पूर्ण जबतक (ret == 1);
पूर्ण

अटल स्थिर काष्ठा sti_font_flags शेष_font_flags = अणु
	.रुको		= STI_WAIT,
	.non_text	= 0,
पूर्ण;

व्योम
sti_अ_दो(काष्ठा sti_काष्ठा *sti, पूर्णांक c, पूर्णांक y, पूर्णांक x,
	 काष्ठा sti_cooked_font *font)
अणु
	काष्ठा sti_font_inptr *inptr = &sti->sti_data->font_inptr;
	काष्ठा sti_font_inptr inptr_शेष = अणु
		.font_start_addr = STI_PTR(font->raw),
		.index		= c_index(sti, c),
		.fg_color	= c_fg(sti, c),
		.bg_color	= c_bg(sti, c),
		.dest_x		= x * font->width,
		.dest_y		= y * font->height,
	पूर्ण;
	काष्ठा sti_font_outptr *outptr = &sti->sti_data->font_outptr;
	s32 ret;
	अचिन्हित दीर्घ flags;

	करो अणु
		spin_lock_irqsave(&sti->lock, flags);
		*inptr = inptr_शेष;
		ret = sti_call(sti, sti->font_unpmv, &शेष_font_flags,
			inptr, outptr, sti->glob_cfg);
		spin_unlock_irqrestore(&sti->lock, flags);
	पूर्ण जबतक (ret == 1);
पूर्ण

अटल स्थिर काष्ठा sti_blkmv_flags clear_blkmv_flags = अणु
	.रुको	= STI_WAIT, 
	.color	= 1, 
	.clear	= 1, 
पूर्ण;

व्योम
sti_set(काष्ठा sti_काष्ठा *sti, पूर्णांक src_y, पूर्णांक src_x,
	पूर्णांक height, पूर्णांक width, u8 color)
अणु
	काष्ठा sti_blkmv_inptr *inptr = &sti->sti_data->blkmv_inptr;
	काष्ठा sti_blkmv_inptr inptr_शेष = अणु
		.fg_color	= color,
		.bg_color	= color,
		.src_x		= src_x,
		.src_y		= src_y,
		.dest_x		= src_x,
		.dest_y		= src_y,
		.width		= width,
		.height		= height,
	पूर्ण;
	काष्ठा sti_blkmv_outptr *outptr = &sti->sti_data->blkmv_outptr;
	s32 ret;
	अचिन्हित दीर्घ flags;
	
	करो अणु
		spin_lock_irqsave(&sti->lock, flags);
		*inptr = inptr_शेष;
		ret = sti_call(sti, sti->block_move, &clear_blkmv_flags,
			inptr, outptr, sti->glob_cfg);
		spin_unlock_irqrestore(&sti->lock, flags);
	पूर्ण जबतक (ret == 1);
पूर्ण

व्योम
sti_clear(काष्ठा sti_काष्ठा *sti, पूर्णांक src_y, पूर्णांक src_x,
	  पूर्णांक height, पूर्णांक width, पूर्णांक c, काष्ठा sti_cooked_font *font)
अणु
	काष्ठा sti_blkmv_inptr *inptr = &sti->sti_data->blkmv_inptr;
	काष्ठा sti_blkmv_inptr inptr_शेष = अणु
		.fg_color	= c_fg(sti, c),
		.bg_color	= c_bg(sti, c),
		.src_x		= src_x * font->width,
		.src_y		= src_y * font->height,
		.dest_x		= src_x * font->width,
		.dest_y		= src_y * font->height,
		.width		= width * font->width,
		.height		= height * font->height,
	पूर्ण;
	काष्ठा sti_blkmv_outptr *outptr = &sti->sti_data->blkmv_outptr;
	s32 ret;
	अचिन्हित दीर्घ flags;

	करो अणु
		spin_lock_irqsave(&sti->lock, flags);
		*inptr = inptr_शेष;
		ret = sti_call(sti, sti->block_move, &clear_blkmv_flags,
			inptr, outptr, sti->glob_cfg);
		spin_unlock_irqrestore(&sti->lock, flags);
	पूर्ण जबतक (ret == 1);
पूर्ण

अटल स्थिर काष्ठा sti_blkmv_flags शेष_blkmv_flags = अणु
	.रुको = STI_WAIT, 
पूर्ण;

व्योम
sti_bmove(काष्ठा sti_काष्ठा *sti, पूर्णांक src_y, पूर्णांक src_x,
	  पूर्णांक dst_y, पूर्णांक dst_x, पूर्णांक height, पूर्णांक width,
	  काष्ठा sti_cooked_font *font)
अणु
	काष्ठा sti_blkmv_inptr *inptr = &sti->sti_data->blkmv_inptr;
	काष्ठा sti_blkmv_inptr inptr_शेष = अणु
		.src_x		= src_x * font->width,
		.src_y		= src_y * font->height,
		.dest_x		= dst_x * font->width,
		.dest_y		= dst_y * font->height,
		.width		= width * font->width,
		.height		= height * font->height,
	पूर्ण;
	काष्ठा sti_blkmv_outptr *outptr = &sti->sti_data->blkmv_outptr;
	s32 ret;
	अचिन्हित दीर्घ flags;

	करो अणु
		spin_lock_irqsave(&sti->lock, flags);
		*inptr = inptr_शेष;
		ret = sti_call(sti, sti->block_move, &शेष_blkmv_flags,
			inptr, outptr, sti->glob_cfg);
		spin_unlock_irqrestore(&sti->lock, flags);
	पूर्ण जबतक (ret == 1);
पूर्ण


अटल व्योम sti_flush(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	flush_icache_range(start, end);
पूर्ण

अटल व्योम sti_rom_copy(अचिन्हित दीर्घ base, अचिन्हित दीर्घ count, व्योम *dest)
अणु
	अचिन्हित दीर्घ dest_start = (अचिन्हित दीर्घ) dest;

	/* this still needs to be revisited (see arch/parisc/mm/init.c:246) ! */
	जबतक (count >= 4) अणु
		count -= 4;
		*(u32 *)dest = gsc_पढ़ोl(base);
		base += 4;
		dest += 4;
	पूर्ण
	जबतक (count) अणु
		count--;
		*(u8 *)dest = gsc_पढ़ोb(base);
		base++;
		dest++;
	पूर्ण

	sti_flush(dest_start, (अचिन्हित दीर्घ)dest);
पूर्ण




अटल अक्षर शेष_sti_path[21] __पढ़ो_mostly;

#अगर_अघोषित MODULE
अटल पूर्णांक __init sti_setup(अक्षर *str)
अणु
	अगर (str)
		strlcpy (शेष_sti_path, str, माप (शेष_sti_path));
	
	वापस 1;
पूर्ण

/*	Assuming the machine has multiple STI consoles (=graphic cards) which
 *	all get detected by sticon, the user may define with the linux kernel
 *	parameter sti=<x> which of them will be the initial boot-console.
 *	<x> is a number between 0 and MAX_STI_ROMS, with 0 as the शेष 
 *	STI screen.
 */
__setup("sti=", sti_setup);
#पूर्ण_अगर



अटल अक्षर *font_name;
अटल पूर्णांक font_index,
	   font_height,
	   font_width;
#अगर_अघोषित MODULE
अटल पूर्णांक sti_font_setup(अक्षर *str)
अणु
	/*
	 * The शेष font can be selected in various ways.
	 * a) sti_font=VGA8x16, sti_font=10x20, sti_font=10*20 selects
	 *    an built-in Linux framebuffer font.
	 * b) sti_font=<index>, where index is (1..x) with 1 selecting
	 *    the first HP STI ROM built-in font..
	 */

	अगर (*str >= '0' && *str <= '9') अणु
		अक्षर *x;

		अगर ((x = म_अक्षर(str, 'x')) || (x = strchr(str, '*'))) अणु
			font_height = simple_म_से_अदीर्घ(str, शून्य, 0);
			font_width = simple_म_से_अदीर्घ(x+1, शून्य, 0);
		पूर्ण अन्यथा अणु
			font_index = simple_म_से_अदीर्घ(str, शून्य, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		font_name = str;	/* fb font name */
	पूर्ण

	वापस 1;
पूर्ण

/*	The optional linux kernel parameter "sti_font" defines which font
 *	should be used by the sticon driver to draw अक्षरacters to the screen.
 *	Possible values are:
 *	- sti_font=<fb_fontname>:
 *		<fb_fontname> is the name of one of the linux-kernel built-in 
 *		framebuffer font names (e.g. VGA8x16, SUN22x18). 
 *		This is only available अगर the fonts have been अटलally compiled 
 *		in with e.g. the CONFIG_FONT_8x16 or CONFIG_FONT_SUN12x22 options.
 *	- sti_font=<number>	(<number> = 1,2,3,...)
 *		most STI ROMs have built-in HP specअगरic fonts, which can be selected
 *		by giving the desired number to the sticon driver. 
 *		NOTE: This number is machine and STI ROM dependend.
 *	- sti_font=<height>x<width>  (e.g. sti_font=16x8)
 *		<height> and <width> gives hपूर्णांकs to the height and width of the
 *		font which the user wants. The sticon driver will try to use
 *		a font with this height and width, but अगर no suitable font is
 *		found, sticon will use the शेष 8x8 font.
 */
__setup("sti_font=", sti_font_setup);
#पूर्ण_अगर


	
अटल व्योम sti_dump_globcfg(काष्ठा sti_glob_cfg *glob_cfg,
			     अचिन्हित पूर्णांक sti_mem_request)
अणु
	काष्ठा sti_glob_cfg_ext *cfg;
	
	pr_debug("%d text planes\n"
		"%4d x %4d screen resolution\n"
		"%4d x %4d offscreen\n"
		"%4d x %4d layout\n"
		"regions at %08x %08x %08x %08x\n"
		"regions at %08x %08x %08x %08x\n"
		"reent_lvl %d\n"
		"save_addr %08x\n",
		glob_cfg->text_planes,
		glob_cfg->onscreen_x, glob_cfg->onscreen_y,
		glob_cfg->offscreen_x, glob_cfg->offscreen_y,
		glob_cfg->total_x, glob_cfg->total_y,
		glob_cfg->region_ptrs[0], glob_cfg->region_ptrs[1],
		glob_cfg->region_ptrs[2], glob_cfg->region_ptrs[3],
		glob_cfg->region_ptrs[4], glob_cfg->region_ptrs[5],
		glob_cfg->region_ptrs[6], glob_cfg->region_ptrs[7],
		glob_cfg->reent_lvl,
		glob_cfg->save_addr);

	/* dump extended cfg */ 
	cfg = PTR_STI((अचिन्हित दीर्घ)glob_cfg->ext_ptr);
	pr_debug("monitor %d\n"
		"in friendly mode: %d\n"
		"power consumption %d watts\n"
		"freq ref %d\n"
		"sti_mem_addr %08x (size=%d bytes)\n",
		cfg->curr_mon,
		cfg->मित्रly_boot,
		cfg->घातer,
		cfg->freq_ref,
		cfg->sti_mem_addr, sti_mem_request);
पूर्ण

अटल व्योम sti_dump_outptr(काष्ठा sti_काष्ठा *sti)
अणु
	pr_debug("%d bits per pixel\n"
		"%d used bits\n"
		"%d planes\n"
		"attributes %08x\n",
		 sti->sti_data->inq_outptr.bits_per_pixel,
		 sti->sti_data->inq_outptr.bits_used,
		 sti->sti_data->inq_outptr.planes,
		 sti->sti_data->inq_outptr.attributes);
पूर्ण

अटल पूर्णांक sti_init_glob_cfg(काष्ठा sti_काष्ठा *sti, अचिन्हित दीर्घ rom_address,
			     अचिन्हित दीर्घ hpa)
अणु
	काष्ठा sti_glob_cfg *glob_cfg;
	काष्ठा sti_glob_cfg_ext *glob_cfg_ext;
	व्योम *save_addr;
	व्योम *sti_mem_addr;
	पूर्णांक i, size;

	अगर (sti->sti_mem_request < 256)
		sti->sti_mem_request = 256; /* STI शेष */

	size = माप(काष्ठा sti_all_data) + sti->sti_mem_request - 256;

	sti->sti_data = kzalloc(size, STI_LOWMEM);
	अगर (!sti->sti_data)
		वापस -ENOMEM;

	glob_cfg	= &sti->sti_data->glob_cfg;
	glob_cfg_ext	= &sti->sti_data->glob_cfg_ext;
	save_addr	= &sti->sti_data->save_addr;
	sti_mem_addr	= &sti->sti_data->sti_mem_addr;

	glob_cfg->ext_ptr = STI_PTR(glob_cfg_ext);
	glob_cfg->save_addr = STI_PTR(save_addr);
	क्रम (i=0; i<8; i++) अणु
		अचिन्हित दीर्घ newhpa, len;
	       
		अगर (sti->pd) अणु
			अचिन्हित अक्षर offs = sti->rm_entry[i];
				
			अगर (offs == 0)
				जारी;
			अगर (offs != PCI_ROM_ADDRESS &&
			    (offs < PCI_BASE_ADDRESS_0 ||
			     offs > PCI_BASE_ADDRESS_5)) अणु
				pr_warn("STI pci region mapping for region %d (%02x) can't be mapped\n",
					i,sti->rm_entry[i]);
				जारी;
			पूर्ण
			newhpa = pci_resource_start (sti->pd, (offs - PCI_BASE_ADDRESS_0) / 4);
		पूर्ण अन्यथा
			newhpa = (i == 0) ? rom_address : hpa;

		sti->regions_phys[i] =
			REGION_OFFSET_TO_PHYS(sti->regions[i], newhpa);
		
		len = sti->regions[i].region_desc.length * 4096;
		अगर (len)
			glob_cfg->region_ptrs[i] = sti->regions_phys[i];
		
		pr_debug("region #%d: phys %08lx, region_ptr %08x, len=%lukB, "
			 "btlb=%d, sysonly=%d, cache=%d, last=%d\n",
			i, sti->regions_phys[i], glob_cfg->region_ptrs[i],
			len/1024,
			sti->regions[i].region_desc.btlb,
			sti->regions[i].region_desc.sys_only,
			sti->regions[i].region_desc.cache, 
			sti->regions[i].region_desc.last);

		/* last entry reached ? */
		अगर (sti->regions[i].region_desc.last)
			अवरोध;
	पूर्ण

	अगर (++i<8 && sti->regions[i].region)
		pr_warn("future ptr (0x%8x) not yet supported !\n",
			sti->regions[i].region);

	glob_cfg_ext->sti_mem_addr = STI_PTR(sti_mem_addr);

	sti->glob_cfg = glob_cfg;
	
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_FONT_SUPPORT
अटल काष्ठा sti_cooked_font *
sti_select_fbfont(काष्ठा sti_cooked_rom *cooked_rom, स्थिर अक्षर *fbfont_name)
अणु
	स्थिर काष्ठा font_desc *fbfont = शून्य;
	अचिन्हित पूर्णांक size, bpc;
	व्योम *dest;
	काष्ठा sti_rom_font *nf;
	काष्ठा sti_cooked_font *cooked_font;
	
	अगर (fbfont_name && म_माप(fbfont_name))
		fbfont = find_font(fbfont_name);
	अगर (!fbfont)
		fbfont = get_शेष_font(1024,768, ~(u32)0, ~(u32)0);
	अगर (!fbfont)
		वापस शून्य;

	pr_info("STI selected %ux%u framebuffer font %s for sticon\n",
			fbfont->width, fbfont->height, fbfont->name);
			
	bpc = ((fbfont->width+7)/8) * fbfont->height; 
	size = bpc * fbfont->अक्षरcount;
	size += माप(काष्ठा sti_rom_font);

	nf = kzalloc(size, STI_LOWMEM);
	अगर (!nf)
		वापस शून्य;

	nf->first_अक्षर = 0;
	nf->last_अक्षर = fbfont->अक्षरcount - 1;
	nf->width = fbfont->width;
	nf->height = fbfont->height;
	nf->font_type = STI_FONT_HPROMAN8;
	nf->bytes_per_अक्षर = bpc;
	nf->next_font = 0;
	nf->underline_height = 1;
	nf->underline_pos = fbfont->height - nf->underline_height;

	dest = nf;
	dest += माप(काष्ठा sti_rom_font);
	स_नकल(dest, fbfont->data, bpc * fbfont->अक्षरcount);

	cooked_font = kzalloc(माप(*cooked_font), GFP_KERNEL);
	अगर (!cooked_font) अणु
		kमुक्त(nf);
		वापस शून्य;
	पूर्ण
	
	cooked_font->raw = nf;
	cooked_font->raw_ptr = nf;
	cooked_font->next_font = शून्य;

	cooked_rom->font_start = cooked_font;

	वापस cooked_font;
पूर्ण
#अन्यथा
अटल काष्ठा sti_cooked_font *
sti_select_fbfont(काष्ठा sti_cooked_rom *cooked_rom, स्थिर अक्षर *fbfont_name)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sti_search_font(काष्ठा sti_cooked_rom *rom, पूर्णांक height, पूर्णांक width)
अणु
	काष्ठा sti_cooked_font *font;
	पूर्णांक i = 0;

	क्रम (font = rom->font_start; font; font = font->next_font, i++) अणु
		अगर ((font->raw->width == width) &&
		    (font->raw->height == height))
			वापस i;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा sti_cooked_font *sti_select_font(काष्ठा sti_cooked_rom *rom)
अणु
	काष्ठा sti_cooked_font *font;
	पूर्णांक i;

	/* check क्रम framebuffer-font first */
	अगर (!font_index) अणु
		font = sti_select_fbfont(rom, font_name);
		अगर (font)
			वापस font;
	पूर्ण

	अगर (font_width && font_height)
		font_index = sti_search_font(rom,
				font_height, font_width);

	क्रम (font = rom->font_start, i = font_index - 1;
		font && (i > 0);
		font = font->next_font, i--);

	अगर (font)
		वापस font;
	अन्यथा
		वापस rom->font_start;
पूर्ण


अटल व्योम sti_dump_rom(काष्ठा sti_काष्ठा *sti)
अणु
	काष्ठा sti_rom *rom = sti->rom->raw;
	काष्ठा sti_cooked_font *font_start;
	पूर्णांक nr;

	pr_info("  id %04x-%04x, conforms to spec rev. %d.%02x\n",
		rom->graphics_id[0], 
		rom->graphics_id[1],
		rom->revno[0] >> 4, 
		rom->revno[0] & 0x0f);
	pr_debug("  supports %d monitors\n", rom->num_mons);
	pr_debug("  font start %08x\n", rom->font_start);
	pr_debug("  region list %08x\n", rom->region_list);
	pr_debug("  init_graph %08x\n", rom->init_graph);
	pr_debug("  bus support %02x\n", rom->bus_support);
	pr_debug("  ext bus support %02x\n", rom->ext_bus_support);
	pr_debug("  alternate code type %d\n", rom->alt_code_type);

	font_start = sti->rom->font_start;
	nr = 0;
	जबतक (font_start) अणु
		काष्ठा sti_rom_font *f = font_start->raw;

		pr_info("    built-in font #%d: size %dx%d, chars %d-%d, bpc %d\n", ++nr,
			f->width, f->height,
			f->first_अक्षर, f->last_अक्षर, f->bytes_per_अक्षर);
		font_start = font_start->next_font;
	पूर्ण
पूर्ण


अटल पूर्णांक sti_cook_fonts(काष्ठा sti_cooked_rom *cooked_rom,
			  काष्ठा sti_rom *raw_rom)
अणु
	काष्ठा sti_rom_font *raw_font, *font_start;
	काष्ठा sti_cooked_font *cooked_font;
	
	cooked_font = kzalloc(माप(*cooked_font), GFP_KERNEL);
	अगर (!cooked_font)
		वापस 0;

	cooked_rom->font_start = cooked_font;

	raw_font = ((व्योम *)raw_rom) + (raw_rom->font_start);

	font_start = raw_font;
	cooked_font->raw = raw_font;

	जबतक (raw_font->next_font) अणु
		raw_font = ((व्योम *)font_start) + (raw_font->next_font);

		cooked_font->next_font = kzalloc(माप(*cooked_font), GFP_KERNEL);
		अगर (!cooked_font->next_font)
			वापस 1;

		cooked_font = cooked_font->next_font;

		cooked_font->raw = raw_font;
	पूर्ण

	cooked_font->next_font = शून्य;
	वापस 1;
पूर्ण

#घोषणा BMODE_RELOCATE(offset)		offset = (offset) / 4;
#घोषणा BMODE_LAST_ADDR_OFFS		0x50

व्योम sti_font_convert_bytemode(काष्ठा sti_काष्ठा *sti, काष्ठा sti_cooked_font *f)
अणु
	अचिन्हित अक्षर *n, *p, *q;
	पूर्णांक size = f->raw->bytes_per_अक्षर * (f->raw->last_अक्षर + 1) + माप(काष्ठा sti_rom_font);
	काष्ठा sti_rom_font *old_font;

	अगर (sti->wordmode)
		वापस;

	old_font = f->raw_ptr;
	n = kसुस्मृति(4, size, STI_LOWMEM);
	f->raw_ptr = n;
	अगर (!n)
		वापस;
	p = n + 3;
	q = (अचिन्हित अक्षर *) f->raw;
	जबतक (size--) अणु
		*p = *q++;
		p += 4;
	पूर्ण
	/* store new ptr to byte-mode font and delete old font */
	f->raw = (काष्ठा sti_rom_font *) (n + 3);
	kमुक्त(old_font);
पूर्ण
EXPORT_SYMBOL(sti_font_convert_bytemode);

अटल व्योम sti_bmode_rom_copy(अचिन्हित दीर्घ base, अचिन्हित दीर्घ count,
			       व्योम *dest)
अणु
	अचिन्हित दीर्घ dest_start = (अचिन्हित दीर्घ) dest;

	जबतक (count) अणु
		count--;
		*(u8 *)dest = gsc_पढ़ोl(base);
		base += 4;
		dest++;
	पूर्ण

	sti_flush(dest_start, (अचिन्हित दीर्घ)dest);
पूर्ण

अटल काष्ठा sti_rom *sti_get_bmode_rom (अचिन्हित दीर्घ address)
अणु
	काष्ठा sti_rom *raw;
	u32 size;
	काष्ठा sti_rom_font *raw_font, *font_start;

	sti_bmode_rom_copy(address + BMODE_LAST_ADDR_OFFS, माप(size), &size);

	size = (size+3) / 4;
	raw = kदो_स्मृति(size, STI_LOWMEM);
	अगर (raw) अणु
		sti_bmode_rom_copy(address, size, raw);
		स_हटाओ (&raw->res004, &raw->type[0], 0x3c);
		raw->type[3] = raw->res004;

		BMODE_RELOCATE (raw->region_list);
		BMODE_RELOCATE (raw->font_start);

		BMODE_RELOCATE (raw->init_graph);
		BMODE_RELOCATE (raw->state_mgmt);
		BMODE_RELOCATE (raw->font_unpmv);
		BMODE_RELOCATE (raw->block_move);
		BMODE_RELOCATE (raw->inq_conf);

		raw_font = ((व्योम *)raw) + raw->font_start;
		font_start = raw_font;
		
		जबतक (raw_font->next_font) अणु
			BMODE_RELOCATE (raw_font->next_font);
			raw_font = ((व्योम *)font_start) + raw_font->next_font;
		पूर्ण
	पूर्ण
	वापस raw;
पूर्ण

अटल काष्ठा sti_rom *sti_get_wmode_rom(अचिन्हित दीर्घ address)
अणु
	काष्ठा sti_rom *raw;
	अचिन्हित दीर्घ size;

	/* पढ़ो the ROM size directly from the काष्ठा in ROM */ 
	size = gsc_पढ़ोl(address + दुरत्व(काष्ठा sti_rom,last_addr));

	raw = kदो_स्मृति(size, STI_LOWMEM);
	अगर (raw)
		sti_rom_copy(address, size, raw);

	वापस raw;
पूर्ण

अटल पूर्णांक sti_पढ़ो_rom(पूर्णांक wordmode, काष्ठा sti_काष्ठा *sti,
			अचिन्हित दीर्घ address)
अणु
	काष्ठा sti_cooked_rom *cooked;
	काष्ठा sti_rom *raw = शून्य;
	अचिन्हित दीर्घ revno;

	cooked = kदो_स्मृति(माप *cooked, GFP_KERNEL);
	अगर (!cooked)
		जाओ out_err;

	अगर (wordmode)
		raw = sti_get_wmode_rom (address);
	अन्यथा
		raw = sti_get_bmode_rom (address);

	अगर (!raw)
		जाओ out_err;

	अगर (!sti_cook_fonts(cooked, raw)) अणु
		pr_warn("No font found for STI at %08lx\n", address);
		जाओ out_err;
	पूर्ण

	अगर (raw->region_list)
		स_नकल(sti->regions, ((व्योम *)raw)+raw->region_list, माप(sti->regions));

	address = (अचिन्हित दीर्घ) STI_PTR(raw);

	pr_info("STI %s ROM supports 32 %sbit firmware functions.\n",
		wordmode ? "word mode" : "byte mode",
		raw->alt_code_type == ALT_CODE_TYPE_PA_RISC_64
		? "and 64 " : "");

	sti->font_unpmv = address + (raw->font_unpmv & 0x03ffffff);
	sti->block_move = address + (raw->block_move & 0x03ffffff);
	sti->init_graph = address + (raw->init_graph & 0x03ffffff);
	sti->inq_conf   = address + (raw->inq_conf   & 0x03ffffff);

	sti->rom = cooked;
	sti->rom->raw = raw;
	sti_dump_rom(sti);

	sti->wordmode = wordmode;
	sti->font = sti_select_font(sti->rom);
	sti->font->width = sti->font->raw->width;
	sti->font->height = sti->font->raw->height;
	sti_font_convert_bytemode(sti, sti->font);

	sti->sti_mem_request = raw->sti_mem_req;
	sti->graphics_id[0] = raw->graphics_id[0];
	sti->graphics_id[1] = raw->graphics_id[1];

	/* check अगर the ROM routines in this card are compatible */
	अगर (wordmode || sti->graphics_id[1] != 0x09A02587)
		जाओ ok;

	revno = (raw->revno[0] << 8) | raw->revno[1];

	चयन (sti->graphics_id[0]) अणु
	हाल S9000_ID_HCRX:
		/* HyperA or HyperB ? */
		अगर (revno == 0x8408 || revno == 0x840b)
			जाओ msg_not_supported;
		अवरोध;
	हाल CRT_ID_THUNDER:
		अगर (revno == 0x8509)
			जाओ msg_not_supported;
		अवरोध;
	हाल CRT_ID_THUNDER2:
		अगर (revno == 0x850c)
			जाओ msg_not_supported;
	पूर्ण
ok:
	वापस 1;

msg_not_supported:
	pr_warn("Sorry, this GSC/STI card is not yet supported.\n");
	pr_warn("Please see https://parisc.wiki.kernel.org/"
		"index.php/Graphics_howto for more info.\n");
	/* fall through */
out_err:
	kमुक्त(raw);
	kमुक्त(cooked);
	वापस 0;
पूर्ण

अटल काष्ठा sti_काष्ठा *sti_try_rom_generic(अचिन्हित दीर्घ address,
					      अचिन्हित दीर्घ hpa,
					      काष्ठा pci_dev *pd)
अणु
	काष्ठा sti_काष्ठा *sti;
	पूर्णांक ok;
	u32 sig;

	अगर (num_sti_roms >= MAX_STI_ROMS) अणु
		pr_warn("maximum number of STI ROMS reached !\n");
		वापस शून्य;
	पूर्ण
	
	sti = kzalloc(माप(*sti), GFP_KERNEL);
	अगर (!sti)
		वापस शून्य;

	spin_lock_init(&sti->lock);

test_rom:
	/* अगर we can't पढ़ो the ROM, bail out early.  Not being able
	 * to पढ़ो the hpa is okay, क्रम romless sti */
	अगर (pdc_add_valid(address))
		जाओ out_err;

	sig = gsc_पढ़ोl(address);

	/* check क्रम a PCI ROM काष्ठाure */
	अगर ((le32_to_cpu(sig)==0xaa55)) अणु
		अचिन्हित पूर्णांक i, rm_offset;
		u32 *rm;
		i = gsc_पढ़ोl(address+0x04);
		अगर (i != 1) अणु
			/* The ROM could have multiple architecture 
			 * dependent images (e.g. i386, parisc,...) */
			pr_warn("PCI ROM is not a STI ROM type image (0x%8x)\n", i);
			जाओ out_err;
		पूर्ण
		
		sti->pd = pd;

		i = gsc_पढ़ोl(address+0x0c);
		pr_debug("PCI ROM size (from header) = %d kB\n",
			le16_to_cpu(i>>16)*512/1024);
		rm_offset = le16_to_cpu(i & 0xffff);
		अगर (rm_offset) अणु 
			/* पढ़ो 16 bytes from the pci region mapper array */
			rm = (u32*) &sti->rm_entry;
			*rm++ = gsc_पढ़ोl(address+rm_offset+0x00);
			*rm++ = gsc_पढ़ोl(address+rm_offset+0x04);
			*rm++ = gsc_पढ़ोl(address+rm_offset+0x08);
			*rm++ = gsc_पढ़ोl(address+rm_offset+0x0c);
		पूर्ण

		address += le32_to_cpu(gsc_पढ़ोl(address+8));
		pr_debug("sig %04x, PCI STI ROM at %08lx\n", sig, address);
		जाओ test_rom;
	पूर्ण
	
	ok = 0;
	
	अगर ((sig & 0xff) == 0x01) अणु
		pr_debug("    byte mode ROM at %08lx, hpa at %08lx\n",
		       address, hpa);
		ok = sti_पढ़ो_rom(0, sti, address);
	पूर्ण

	अगर ((sig & 0xffff) == 0x0303) अणु
		pr_debug("    word mode ROM at %08lx, hpa at %08lx\n",
		       address, hpa);
		ok = sti_पढ़ो_rom(1, sti, address);
	पूर्ण

	अगर (!ok)
		जाओ out_err;

	अगर (sti_init_glob_cfg(sti, address, hpa))
		जाओ out_err; /* not enough memory */

	/* disable STI PCI ROM. ROM and card RAM overlap and
	 * leaving it enabled would क्रमce HPMCs
	 */
	अगर (sti->pd) अणु
		अचिन्हित दीर्घ rom_base;
		rom_base = pci_resource_start(sti->pd, PCI_ROM_RESOURCE);	
		pci_ग_लिखो_config_dword(sti->pd, PCI_ROM_ADDRESS, rom_base & ~PCI_ROM_ADDRESS_ENABLE);
		pr_debug("STI PCI ROM disabled\n");
	पूर्ण

	अगर (sti_init_graph(sti))
		जाओ out_err;

	sti_inq_conf(sti);
	sti_dump_globcfg(sti->glob_cfg, sti->sti_mem_request);
	sti_dump_outptr(sti);
	
	pr_info("    graphics card name: %s\n",
		sti->sti_data->inq_outptr.dev_name);

	sti_roms[num_sti_roms] = sti;
	num_sti_roms++;
	
	वापस sti;

out_err:
	kमुक्त(sti);
	वापस शून्य;
पूर्ण

अटल व्योम sticore_check_क्रम_शेष_sti(काष्ठा sti_काष्ठा *sti, अक्षर *path)
अणु
	अगर (म_भेद (path, शेष_sti_path) == 0)
		शेष_sti = sti;
पूर्ण

/*
 * on newer प्रणालीs PDC gives the address of the ROM 
 * in the additional address field addr[1] जबतक on
 * older Systems the PDC stores it in page0->proc_sti 
 */
अटल पूर्णांक __init sticore_pa_init(काष्ठा parisc_device *dev)
अणु
	अक्षर pa_path[21];
	काष्ठा sti_काष्ठा *sti = शून्य;
	पूर्णांक hpa = dev->hpa.start;

	अगर (dev->num_addrs && dev->addr[0])
		sti = sti_try_rom_generic(dev->addr[0], hpa, शून्य);
	अगर (!sti)
		sti = sti_try_rom_generic(hpa, hpa, शून्य);
	अगर (!sti)
		sti = sti_try_rom_generic(PAGE0->proc_sti, hpa, शून्य);
	अगर (!sti)
		वापस 1;

	prपूर्णांक_pa_hwpath(dev, pa_path);
	sticore_check_क्रम_शेष_sti(sti, pa_path);
	वापस 0;
पूर्ण


अटल पूर्णांक sticore_pci_init(काष्ठा pci_dev *pd, स्थिर काष्ठा pci_device_id *ent)
अणु
#अगर_घोषित CONFIG_PCI
	अचिन्हित दीर्घ fb_base, rom_base;
	अचिन्हित पूर्णांक fb_len, rom_len;
	पूर्णांक err;
	काष्ठा sti_काष्ठा *sti;
	
	err = pci_enable_device(pd);
	अगर (err < 0) अणु
		dev_err(&pd->dev, "Cannot enable PCI device\n");
		वापस err;
	पूर्ण

	fb_base = pci_resource_start(pd, 0);
	fb_len = pci_resource_len(pd, 0);
	rom_base = pci_resource_start(pd, PCI_ROM_RESOURCE);
	rom_len = pci_resource_len(pd, PCI_ROM_RESOURCE);
	अगर (rom_base) अणु
		pci_ग_लिखो_config_dword(pd, PCI_ROM_ADDRESS, rom_base | PCI_ROM_ADDRESS_ENABLE);
		pr_debug("STI PCI ROM enabled at 0x%08lx\n", rom_base);
	पूर्ण

	pr_info("STI PCI graphic ROM found at %08lx (%u kB), fb at %08lx (%u MB)\n",
		rom_base, rom_len/1024, fb_base, fb_len/1024/1024);

	pr_debug("Trying PCI STI ROM at %08lx, PCI hpa at %08lx\n",
		    rom_base, fb_base);

	sti = sti_try_rom_generic(rom_base, fb_base, pd);
	अगर (sti) अणु
		अक्षर pa_path[30];
		prपूर्णांक_pci_hwpath(pd, pa_path);
		sticore_check_क्रम_शेष_sti(sti, pa_path);
	पूर्ण
	
	अगर (!sti) अणु
		pr_warn("Unable to handle STI device '%s'\n", pci_name(pd));
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

	वापस 0;
पूर्ण


अटल व्योम __निकास sticore_pci_हटाओ(काष्ठा pci_dev *pd)
अणु
	BUG();
पूर्ण


अटल काष्ठा pci_device_id sti_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_VISUALIZE_EG) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_VISUALIZE_FX6) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_VISUALIZE_FX4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_VISUALIZE_FX2) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_VISUALIZE_FXE) पूर्ण,
	अणु 0, पूर्ण /* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, sti_pci_tbl);

अटल काष्ठा pci_driver pci_sti_driver = अणु
	.name		= "sti",
	.id_table	= sti_pci_tbl,
	.probe		= sticore_pci_init,
	.हटाओ		= __निकास_p(sticore_pci_हटाओ),
पूर्ण;

अटल काष्ठा parisc_device_id sti_pa_tbl[] = अणु
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00077 पूर्ण,
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00085 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(parisc, sti_pa_tbl);

अटल काष्ठा parisc_driver pa_sti_driver __refdata = अणु
	.name		= "sti",
	.id_table	= sti_pa_tbl,
	.probe		= sticore_pa_init,
पूर्ण;


/*
 * sti_init_roms() - detects all STI ROMs and stores them in sti_roms[]
 */

अटल पूर्णांक sticore_initialized __पढ़ो_mostly;

अटल व्योम sti_init_roms(व्योम)
अणु
	अगर (sticore_initialized)
		वापस;

	sticore_initialized = 1;

	pr_info("STI GSC/PCI core graphics driver "
			STI_DRIVERVERSION "\n");

	/* Register drivers क्रम native & PCI cards */
	रेजिस्टर_parisc_driver(&pa_sti_driver);
	WARN_ON(pci_रेजिस्टर_driver(&pci_sti_driver));

	/* अगर we didn't find the given शेष sti, take the first one */
	अगर (!शेष_sti)
		शेष_sti = sti_roms[0];

पूर्ण

/*
 * index = 0 gives शेष sti
 * index > 0 gives other stis in detection order
 */
काष्ठा sti_काष्ठा * sti_get_rom(अचिन्हित पूर्णांक index)
अणु
	अगर (!sticore_initialized)
		sti_init_roms();

	अगर (index == 0)
		वापस शेष_sti;

	अगर (index > num_sti_roms)
		वापस शून्य;

	वापस sti_roms[index-1];
पूर्ण
EXPORT_SYMBOL(sti_get_rom);


पूर्णांक sti_call(स्थिर काष्ठा sti_काष्ठा *sti, अचिन्हित दीर्घ func,
		स्थिर व्योम *flags, व्योम *inptr, व्योम *outptr,
		काष्ठा sti_glob_cfg *glob_cfg)
अणु
	अचिन्हित दीर्घ _flags = STI_PTR(flags);
	अचिन्हित दीर्घ _inptr = STI_PTR(inptr);
	अचिन्हित दीर्घ _outptr = STI_PTR(outptr);
	अचिन्हित दीर्घ _glob_cfg = STI_PTR(glob_cfg);
	पूर्णांक ret;

#अगर_घोषित CONFIG_64BIT
	/* Check क्रम overflow when using 32bit STI on 64bit kernel. */
	अगर (WARN_ONCE(_flags>>32 || _inptr>>32 || _outptr>>32 || _glob_cfg>>32,
			"Out of 32bit-range pointers!"))
		वापस -1;
#पूर्ण_अगर

	ret = pdc_sti_call(func, _flags, _inptr, _outptr, _glob_cfg);

	वापस ret;
पूर्ण

MODULE_AUTHOR("Philipp Rumpf, Helge Deller, Thomas Bogendoerfer");
MODULE_DESCRIPTION("Core STI driver for HP's NGLE series graphics cards in HP PARISC machines");
MODULE_LICENSE("GPL v2");

