<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic System Framebuffers on x86
 * Copyright (c) 2012-2013 David Herrmann <dh.herrmann@gmail.com>
 *
 * EFI Quirks Copyright (c) 2006 Edgar Hucek <gimli@dark-green.com>
 */

/*
 * EFI Quirks
 * Several EFI प्रणालीs करो not correctly advertise their boot framebuffers.
 * Hence, we use this अटल table of known broken machines and fix up the
 * inक्रमmation so framebuffer drivers can load correctly.
 */

#समावेश <linux/dmi.h>
#समावेश <linux/err.h>
#समावेश <linux/efi.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/screen_info.h>
#समावेश <video/vga.h>

#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/sysfb.h>

क्रमागत अणु
	OVERRIDE_NONE = 0x0,
	OVERRIDE_BASE = 0x1,
	OVERRIDE_STRIDE = 0x2,
	OVERRIDE_HEIGHT = 0x4,
	OVERRIDE_WIDTH = 0x8,
पूर्ण;

काष्ठा efअगरb_dmi_info efअगरb_dmi_list[] = अणु
	[M_I17] = अणु "i17", 0x80010000, 1472 * 4, 1440, 900, OVERRIDE_NONE पूर्ण,
	[M_I20] = अणु "i20", 0x80010000, 1728 * 4, 1680, 1050, OVERRIDE_NONE पूर्ण, /* guess */
	[M_I20_SR] = अणु "imac7", 0x40010000, 1728 * 4, 1680, 1050, OVERRIDE_NONE पूर्ण,
	[M_I24] = अणु "i24", 0x80010000, 2048 * 4, 1920, 1200, OVERRIDE_NONE पूर्ण, /* guess */
	[M_I24_8_1] = अणु "imac8", 0xc0060000, 2048 * 4, 1920, 1200, OVERRIDE_NONE पूर्ण,
	[M_I24_10_1] = अणु "imac10", 0xc0010000, 2048 * 4, 1920, 1080, OVERRIDE_NONE पूर्ण,
	[M_I27_11_1] = अणु "imac11", 0xc0010000, 2560 * 4, 2560, 1440, OVERRIDE_NONE पूर्ण,
	[M_MINI]= अणु "mini", 0x80000000, 2048 * 4, 1024, 768, OVERRIDE_NONE पूर्ण,
	[M_MINI_3_1] = अणु "mini31", 0x40010000, 1024 * 4, 1024, 768, OVERRIDE_NONE पूर्ण,
	[M_MINI_4_1] = अणु "mini41", 0xc0010000, 2048 * 4, 1920, 1200, OVERRIDE_NONE पूर्ण,
	[M_MB] = अणु "macbook", 0x80000000, 2048 * 4, 1280, 800, OVERRIDE_NONE पूर्ण,
	[M_MB_5_1] = अणु "macbook51", 0x80010000, 2048 * 4, 1280, 800, OVERRIDE_NONE पूर्ण,
	[M_MB_6_1] = अणु "macbook61", 0x80010000, 2048 * 4, 1280, 800, OVERRIDE_NONE पूर्ण,
	[M_MB_7_1] = अणु "macbook71", 0x80010000, 2048 * 4, 1280, 800, OVERRIDE_NONE पूर्ण,
	[M_MBA] = अणु "mba", 0x80000000, 2048 * 4, 1280, 800, OVERRIDE_NONE पूर्ण,
	/* 11" Macbook Air 3,1 passes the wrong stride */
	[M_MBA_3] = अणु "mba3", 0, 2048 * 4, 0, 0, OVERRIDE_STRIDE पूर्ण,
	[M_MBP] = अणु "mbp", 0x80010000, 1472 * 4, 1440, 900, OVERRIDE_NONE पूर्ण,
	[M_MBP_2] = अणु "mbp2", 0, 0, 0, 0, OVERRIDE_NONE पूर्ण, /* placeholder */
	[M_MBP_2_2] = अणु "mbp22", 0x80010000, 1472 * 4, 1440, 900, OVERRIDE_NONE पूर्ण,
	[M_MBP_SR] = अणु "mbp3", 0x80030000, 2048 * 4, 1440, 900, OVERRIDE_NONE पूर्ण,
	[M_MBP_4] = अणु "mbp4", 0xc0060000, 2048 * 4, 1920, 1200, OVERRIDE_NONE पूर्ण,
	[M_MBP_5_1] = अणु "mbp51", 0xc0010000, 2048 * 4, 1440, 900, OVERRIDE_NONE पूर्ण,
	[M_MBP_5_2] = अणु "mbp52", 0xc0010000, 2048 * 4, 1920, 1200, OVERRIDE_NONE पूर्ण,
	[M_MBP_5_3] = अणु "mbp53", 0xd0010000, 2048 * 4, 1440, 900, OVERRIDE_NONE पूर्ण,
	[M_MBP_6_1] = अणु "mbp61", 0x90030000, 2048 * 4, 1920, 1200, OVERRIDE_NONE पूर्ण,
	[M_MBP_6_2] = अणु "mbp62", 0x90030000, 2048 * 4, 1680, 1050, OVERRIDE_NONE पूर्ण,
	[M_MBP_7_1] = अणु "mbp71", 0xc0010000, 2048 * 4, 1280, 800, OVERRIDE_NONE पूर्ण,
	[M_MBP_8_2] = अणु "mbp82", 0x90010000, 1472 * 4, 1440, 900, OVERRIDE_NONE पूर्ण,
	[M_UNKNOWN] = अणु शून्य, 0, 0, 0, 0, OVERRIDE_NONE पूर्ण
पूर्ण;

व्योम efअगरb_setup_from_dmi(काष्ठा screen_info *si, स्थिर अक्षर *opt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < M_UNKNOWN; i++) अणु
		अगर (efअगरb_dmi_list[i].base != 0 &&
		    !म_भेद(opt, efअगरb_dmi_list[i].optname)) अणु
			si->lfb_base = efअगरb_dmi_list[i].base;
			si->lfb_linelength = efअगरb_dmi_list[i].stride;
			si->lfb_width = efअगरb_dmi_list[i].width;
			si->lfb_height = efअगरb_dmi_list[i].height;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा choose_value(dmivalue, fwvalue, field, flags) (अणु	\
		typeof(fwvalue) _ret_ = fwvalue;		\
		अगर ((flags) & (field))				\
			_ret_ = dmivalue;			\
		अन्यथा अगर ((fwvalue) == 0)			\
			_ret_ = dmivalue;			\
		_ret_;						\
	पूर्ण)

अटल पूर्णांक __init efअगरb_set_प्रणाली(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	काष्ठा efअगरb_dmi_info *info = id->driver_data;

	अगर (info->base == 0 && info->height == 0 && info->width == 0 &&
	    info->stride == 0)
		वापस 0;

	/* Trust the bootloader over the DMI tables */
	अगर (screen_info.lfb_base == 0) अणु
#अगर defined(CONFIG_PCI)
		काष्ठा pci_dev *dev = शून्य;
		पूर्णांक found_bar = 0;
#पूर्ण_अगर
		अगर (info->base) अणु
			screen_info.lfb_base = choose_value(info->base,
				screen_info.lfb_base, OVERRIDE_BASE,
				info->flags);

#अगर defined(CONFIG_PCI)
			/* make sure that the address in the table is actually
			 * on a VGA device's PCI BAR */

			क्रम_each_pci_dev(dev) अणु
				पूर्णांक i;
				अगर ((dev->class >> 8) != PCI_CLASS_DISPLAY_VGA)
					जारी;
				क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
					resource_माप_प्रकार start, end;
					अचिन्हित दीर्घ flags;

					flags = pci_resource_flags(dev, i);
					अगर (!(flags & IORESOURCE_MEM))
						जारी;

					अगर (flags & IORESOURCE_UNSET)
						जारी;

					अगर (pci_resource_len(dev, i) == 0)
						जारी;

					start = pci_resource_start(dev, i);
					end = pci_resource_end(dev, i);
					अगर (screen_info.lfb_base >= start &&
					    screen_info.lfb_base < end) अणु
						found_bar = 1;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (!found_bar)
				screen_info.lfb_base = 0;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	अगर (screen_info.lfb_base) अणु
		screen_info.lfb_linelength = choose_value(info->stride,
			screen_info.lfb_linelength, OVERRIDE_STRIDE,
			info->flags);
		screen_info.lfb_width = choose_value(info->width,
			screen_info.lfb_width, OVERRIDE_WIDTH,
			info->flags);
		screen_info.lfb_height = choose_value(info->height,
			screen_info.lfb_height, OVERRIDE_HEIGHT,
			info->flags);
		अगर (screen_info.orig_video_isVGA == 0)
			screen_info.orig_video_isVGA = VIDEO_TYPE_EFI;
	पूर्ण अन्यथा अणु
		screen_info.lfb_linelength = 0;
		screen_info.lfb_width = 0;
		screen_info.lfb_height = 0;
		screen_info.orig_video_isVGA = 0;
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_INFO "efifb: dmi detected %s - framebuffer at 0x%08x "
			 "(%dx%d, stride %d)\n", id->ident,
			 screen_info.lfb_base, screen_info.lfb_width,
			 screen_info.lfb_height, screen_info.lfb_linelength);

	वापस 1;
पूर्ण

#घोषणा EFIFB_DMI_SYSTEM_ID(venकरोr, name, क्रमागतid)		\
	अणु							\
		efअगरb_set_प्रणाली,				\
		name,						\
		अणु						\
			DMI_MATCH(DMI_BIOS_VENDOR, venकरोr),	\
			DMI_MATCH(DMI_PRODUCT_NAME, name)	\
		पूर्ण,						\
		&efअगरb_dmi_list[क्रमागतid]				\
	पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id efअगरb_dmi_प्रणाली_table[] __initस्थिर = अणु
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "iMac4,1", M_I17),
	/* At least one of these two will be right; maybe both? */
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "iMac5,1", M_I20),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "iMac5,1", M_I20),
	/* At least one of these two will be right; maybe both? */
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "iMac6,1", M_I24),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "iMac6,1", M_I24),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "iMac7,1", M_I20_SR),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "iMac8,1", M_I24_8_1),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "iMac10,1", M_I24_10_1),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "iMac11,1", M_I27_11_1),
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "Macmini1,1", M_MINI),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "Macmini3,1", M_MINI_3_1),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "Macmini4,1", M_MINI_4_1),
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "MacBook1,1", M_MB),
	/* At least one of these two will be right; maybe both? */
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "MacBook2,1", M_MB),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBook2,1", M_MB),
	/* At least one of these two will be right; maybe both? */
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "MacBook3,1", M_MB),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBook3,1", M_MB),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBook4,1", M_MB),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBook5,1", M_MB_5_1),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBook6,1", M_MB_6_1),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBook7,1", M_MB_7_1),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookAir1,1", M_MBA),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookAir3,1", M_MBA_3),
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "MacBookPro1,1", M_MBP),
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "MacBookPro2,1", M_MBP_2),
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "MacBookPro2,2", M_MBP_2_2),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro2,1", M_MBP_2),
	EFIFB_DMI_SYSTEM_ID("Apple Computer, Inc.", "MacBookPro3,1", M_MBP_SR),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro3,1", M_MBP_SR),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro4,1", M_MBP_4),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro5,1", M_MBP_5_1),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro5,2", M_MBP_5_2),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro5,3", M_MBP_5_3),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro6,1", M_MBP_6_1),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro6,2", M_MBP_6_2),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro7,1", M_MBP_7_1),
	EFIFB_DMI_SYSTEM_ID("Apple Inc.", "MacBookPro8,2", M_MBP_8_2),
	अणुपूर्ण,
पूर्ण;

/*
 * Some devices have a portrait LCD but advertise a landscape resolution (and
 * pitch). We simply swap width and height क्रम these devices so that we can
 * correctly deal with some of them coming with multiple resolutions.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id efअगरb_dmi_swap_width_height[] __initस्थिर = अणु
	अणु
		/*
		 * Lenovo MIIX310-10ICR, only some batches have the troublesome
		 * 800x1280 portrait screen. Luckily the portrait version has
		 * its own BIOS version, so we match on that.
		 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "MIIX 310-10ICR"),
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "1HCN44WW"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo MIIX 320-10ICR with 800x1280 portrait screen */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_PRODUCT_VERSION,
					"Lenovo MIIX 320-10ICR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo D330 with 800x1280 or 1200x1920 portrait screen */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_EXACT_MATCH(DMI_PRODUCT_VERSION,
					"Lenovo ideapad D330-10IGM"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

__init व्योम sysfb_apply_efi_quirks(व्योम)
अणु
	अगर (screen_info.orig_video_isVGA != VIDEO_TYPE_EFI ||
	    !(screen_info.capabilities & VIDEO_CAPABILITY_SKIP_QUIRKS))
		dmi_check_प्रणाली(efअगरb_dmi_प्रणाली_table);

	अगर (screen_info.orig_video_isVGA == VIDEO_TYPE_EFI &&
	    dmi_check_प्रणाली(efअगरb_dmi_swap_width_height)) अणु
		u16 temp = screen_info.lfb_width;

		screen_info.lfb_width = screen_info.lfb_height;
		screen_info.lfb_height = temp;
		screen_info.lfb_linelength = 4 * screen_info.lfb_width;
	पूर्ण
पूर्ण
