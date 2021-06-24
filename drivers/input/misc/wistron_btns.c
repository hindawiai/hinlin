<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Wistron laptop button driver
 * Copyright (C) 2005 Miloslav Trmac <mitr@volny.cz>
 * Copyright (C) 2005 Bernhard Rosenkraenzer <bero@arklinux.org>
 * Copyright (C) 2005 Dmitry Torokhov <dtor@mail.ru>
 */
#समावेश <linux/पन.स>
#समावेश <linux/dmi.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/module.h>
#समावेश <linux/preempt.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>

/* How often we poll keys - msecs */
#घोषणा POLL_INTERVAL_DEFAULT	500 /* when idle */
#घोषणा POLL_INTERVAL_BURST	100 /* when a key was recently pressed */

/* BIOS subप्रणाली IDs */
#घोषणा WIFI		0x35
#घोषणा BLUETOOTH	0x34
#घोषणा MAIL_LED	0x31

MODULE_AUTHOR("Miloslav Trmac <mitr@volny.cz>");
MODULE_DESCRIPTION("Wistron laptop button driver");
MODULE_LICENSE("GPL v2");

अटल bool क्रमce; /* = 0; */
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Load even if computer is not in database");

अटल अक्षर *keymap_name; /* = शून्य; */
module_param_named(keymap, keymap_name, अक्षरp, 0);
MODULE_PARM_DESC(keymap, "Keymap name, if it can't be autodetected [generic, 1557/MS2141]");

अटल काष्ठा platक्रमm_device *wistron_device;

 /* BIOS पूर्णांकerface implementation */

अटल व्योम __iomem *bios_entry_poपूर्णांक; /* BIOS routine entry poपूर्णांक */
अटल व्योम __iomem *bios_code_map_base;
अटल व्योम __iomem *bios_data_map_base;

अटल u8 cmos_address;

काष्ठा regs अणु
	u32 eax, ebx, ecx;
पूर्ण;

अटल व्योम call_bios(काष्ठा regs *regs)
अणु
	अचिन्हित दीर्घ flags;

	preempt_disable();
	local_irq_save(flags);
	यंत्र अस्थिर ("pushl %%ebp;"
		      "movl %7, %%ebp;"
		      "call *%6;"
		      "popl %%ebp"
		      : "=a" (regs->eax), "=b" (regs->ebx), "=c" (regs->ecx)
		      : "0" (regs->eax), "1" (regs->ebx), "2" (regs->ecx),
			"m" (bios_entry_poपूर्णांक), "m" (bios_data_map_base)
		      : "edx", "edi", "esi", "memory");
	local_irq_restore(flags);
	preempt_enable();
पूर्ण

अटल sमाप_प्रकार __init locate_wistron_bios(व्योम __iomem *base)
अणु
	अटल अचिन्हित अक्षर __initdata signature[] =
		अणु 0x42, 0x21, 0x55, 0x30 पूर्ण;
	sमाप_प्रकार offset;

	क्रम (offset = 0; offset < 0x10000; offset += 0x10) अणु
		अगर (check_signature(base + offset, signature,
				    माप(signature)) != 0)
			वापस offset;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक __init map_bios(व्योम)
अणु
	व्योम __iomem *base;
	sमाप_प्रकार offset;
	u32 entry_poपूर्णांक;

	base = ioremap(0xF0000, 0x10000); /* Can't fail */
	offset = locate_wistron_bios(base);
	अगर (offset < 0) अणु
		prपूर्णांकk(KERN_ERR "wistron_btns: BIOS entry point not found\n");
		iounmap(base);
		वापस -ENODEV;
	पूर्ण

	entry_poपूर्णांक = पढ़ोl(base + offset + 5);
	prपूर्णांकk(KERN_DEBUG
		"wistron_btns: BIOS signature found at %p, entry point %08X\n",
		base + offset, entry_poपूर्णांक);

	अगर (entry_poपूर्णांक >= 0xF0000) अणु
		bios_code_map_base = base;
		bios_entry_poपूर्णांक = bios_code_map_base + (entry_poपूर्णांक & 0xFFFF);
	पूर्ण अन्यथा अणु
		iounmap(base);
		bios_code_map_base = ioremap(entry_poपूर्णांक & ~0x3FFF, 0x4000);
		अगर (bios_code_map_base == शून्य) अणु
			prपूर्णांकk(KERN_ERR
				"wistron_btns: Can't map BIOS code at %08X\n",
				entry_poपूर्णांक & ~0x3FFF);
			जाओ err;
		पूर्ण
		bios_entry_poपूर्णांक = bios_code_map_base + (entry_poपूर्णांक & 0x3FFF);
	पूर्ण
	/* The Winकरोws driver maps 0x10000 bytes, we keep only one page... */
	bios_data_map_base = ioremap(0x400, 0xc00);
	अगर (bios_data_map_base == शून्य) अणु
		prपूर्णांकk(KERN_ERR "wistron_btns: Can't map BIOS data\n");
		जाओ err_code;
	पूर्ण
	वापस 0;

err_code:
	iounmap(bios_code_map_base);
err:
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम unmap_bios(व्योम)
अणु
	iounmap(bios_code_map_base);
	iounmap(bios_data_map_base);
पूर्ण

 /* BIOS calls */

अटल u16 bios_pop_queue(व्योम)
अणु
	काष्ठा regs regs;

	स_रखो(&regs, 0, माप (regs));
	regs.eax = 0x9610;
	regs.ebx = 0x061C;
	regs.ecx = 0x0000;
	call_bios(&regs);

	वापस regs.eax;
पूर्ण

अटल व्योम bios_attach(व्योम)
अणु
	काष्ठा regs regs;

	स_रखो(&regs, 0, माप (regs));
	regs.eax = 0x9610;
	regs.ebx = 0x012E;
	call_bios(&regs);
पूर्ण

अटल व्योम bios_detach(व्योम)
अणु
	काष्ठा regs regs;

	स_रखो(&regs, 0, माप (regs));
	regs.eax = 0x9610;
	regs.ebx = 0x002E;
	call_bios(&regs);
पूर्ण

अटल u8 bios_get_cmos_address(व्योम)
अणु
	काष्ठा regs regs;

	स_रखो(&regs, 0, माप (regs));
	regs.eax = 0x9610;
	regs.ebx = 0x051C;
	call_bios(&regs);

	वापस regs.ecx;
पूर्ण

अटल u16 bios_get_शेष_setting(u8 subsys)
अणु
	काष्ठा regs regs;

	स_रखो(&regs, 0, माप (regs));
	regs.eax = 0x9610;
	regs.ebx = 0x0200 | subsys;
	call_bios(&regs);

	वापस regs.eax;
पूर्ण

अटल व्योम bios_set_state(u8 subsys, पूर्णांक enable)
अणु
	काष्ठा regs regs;

	स_रखो(&regs, 0, माप (regs));
	regs.eax = 0x9610;
	regs.ebx = (enable ? 0x0100 : 0x0000) | subsys;
	call_bios(&regs);
पूर्ण

/* Hardware database */

#घोषणा KE_WIFI		(KE_LAST + 1)
#घोषणा KE_BLUETOOTH	(KE_LAST + 2)

#घोषणा FE_MAIL_LED 0x01
#घोषणा FE_WIFI_LED 0x02
#घोषणा FE_UNTESTED 0x80

अटल काष्ठा key_entry *keymap; /* = शून्य; Current key map */
अटल bool have_wअगरi;
अटल bool have_bluetooth;
अटल पूर्णांक leds_present;	/* biपंचांगask of leds present */

अटल पूर्णांक __init dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	स्थिर काष्ठा key_entry *key;

	keymap = dmi->driver_data;
	क्रम (key = keymap; key->type != KE_END; key++) अणु
		अगर (key->type == KE_WIFI)
			have_wअगरi = true;
		अन्यथा अगर (key->type == KE_BLUETOOTH)
			have_bluetooth = true;
	पूर्ण
	leds_present = key->code & (FE_MAIL_LED | FE_WIFI_LED);

	वापस 1;
पूर्ण

अटल काष्ठा key_entry keymap_empty[] __initdata = अणु
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_fs_amilo_pro_v2000[] __initdata = अणु
	अणु KE_KEY,  0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY,  0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY,  0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_KEY,  0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY,  0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_END,  0 पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_fs_amilo_pro_v3505[] __initdata = अणु
	अणु KE_KEY,       0x01, अणुKEY_HELPपूर्ण पूर्ण,          /* Fn+F1 */
	अणु KE_KEY,       0x06, अणुKEY_DISPLAYTOGGLEपूर्ण पूर्ण, /* Fn+F4 */
	अणु KE_BLUETOOTH, 0x30 पूर्ण,                      /* Fn+F10 */
	अणु KE_KEY,       0x31, अणुKEY_MAILपूर्ण पूर्ण,          /* mail button */
	अणु KE_KEY,       0x36, अणुKEY_WWWपूर्ण पूर्ण,           /* www button */
	अणु KE_WIFI,      0x78 पूर्ण,                      /* satellite dish button */
	अणु KE_END,       0 पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_fs_amilo_pro_v8210[] __initdata = अणु
	अणु KE_KEY,       0x01, अणुKEY_HELPपूर्ण पूर्ण,          /* Fn+F1 */
	अणु KE_KEY,       0x06, अणुKEY_DISPLAYTOGGLEपूर्ण पूर्ण, /* Fn+F4 */
	अणु KE_BLUETOOTH, 0x30 पूर्ण,                      /* Fn+F10 */
	अणु KE_KEY,       0x31, अणुKEY_MAILपूर्ण पूर्ण,          /* mail button */
	अणु KE_KEY,       0x36, अणुKEY_WWWपूर्ण पूर्ण,           /* www button */
	अणु KE_WIFI,      0x78 पूर्ण,                      /* satelite dish button */
	अणु KE_END,       FE_WIFI_LED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_fujitsu_n3510[] __initdata = अणु
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x71, अणुKEY_STOPCDपूर्ण पूर्ण,
	अणु KE_KEY, 0x72, अणुKEY_PLAYPAUSEपूर्ण पूर्ण,
	अणु KE_KEY, 0x74, अणुKEY_REWINDपूर्ण पूर्ण,
	अणु KE_KEY, 0x78, अणुKEY_FORWARDपूर्ण पूर्ण,
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_wistron_ms2111[] __initdata = अणु
	अणु KE_KEY,  0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY,  0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY,  0x13, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_KEY,  0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY,  0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_END, FE_MAIL_LED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_wistron_md40100[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x37, अणुKEY_DISPLAYTOGGLEपूर्ण पूर्ण, /* Display on/off */
	अणु KE_END, FE_MAIL_LED | FE_WIFI_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_wistron_ms2141[] __initdata = अणु
	अणु KE_KEY,  0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY,  0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_KEY,  0x22, अणुKEY_REWINDपूर्ण पूर्ण,
	अणु KE_KEY,  0x23, अणुKEY_FORWARDपूर्ण पूर्ण,
	अणु KE_KEY,  0x24, अणुKEY_PLAYPAUSEपूर्ण पूर्ण,
	अणु KE_KEY,  0x25, अणुKEY_STOPCDपूर्ण पूर्ण,
	अणु KE_KEY,  0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY,  0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_END,  0 पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_aspire_1500[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x03, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x49, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_BLUETOOTH, 0x44 पूर्ण,
	अणु KE_END, FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_aspire_1600[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x03, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x08, अणुKEY_MUTEपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x49, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_BLUETOOTH, 0x44 पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_UNTESTED पूर्ण
पूर्ण;

/* 3020 has been tested */
अटल काष्ठा key_entry keymap_acer_aspire_5020[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x03, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x05, अणुKEY_SWITCHVIDEOMODEपूर्ण पूर्ण, /* Display selection */
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x6a, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_BLUETOOTH, 0x44 पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_travelmate_2410[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x6d, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x6a, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_BLUETOOTH, 0x44 पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_travelmate_110[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x03, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x08, अणुKEY_MUTEपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x20, अणुKEY_VOLUMEUPपूर्ण पूर्ण,
	अणु KE_KEY, 0x21, अणुKEY_VOLUMEDOWNपूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_SW, 0x4a, अणु.sw = अणुSW_LID, 1पूर्णपूर्ण पूर्ण, /* lid बंद */
	अणु KE_SW, 0x4b, अणु.sw = अणुSW_LID, 0पूर्णपूर्ण पूर्ण, /* lid खोलो */
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_travelmate_300[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x03, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x08, अणुKEY_MUTEपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x20, अणुKEY_VOLUMEUPपूर्ण पूर्ण,
	अणु KE_KEY, 0x21, अणुKEY_VOLUMEDOWNपूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_BLUETOOTH, 0x44 पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_travelmate_380[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x03, अणुKEY_POWERपूर्ण पूर्ण, /* not 370 */
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_UNTESTED पूर्ण
पूर्ण;

/* unusual map */
अटल काष्ठा key_entry keymap_acer_travelmate_220[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_END, FE_WIFI_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_travelmate_230[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_END, FE_WIFI_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_travelmate_240[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x03, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x08, अणुKEY_MUTEपूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_BLUETOOTH, 0x44 पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_END, FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_travelmate_350[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x14, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_KEY, 0x15, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_WIFI_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_travelmate_360[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x14, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_KEY, 0x15, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x40, अणुKEY_WLANपूर्ण पूर्ण,
	अणु KE_END, FE_WIFI_LED | FE_UNTESTED पूर्ण /* no mail led */
पूर्ण;

/* Wअगरi subप्रणाली only activates the led. Thereक्रमe we need to pass
 * wअगरi event as a normal key, then userspace can really change the wअगरi state.
 * TODO we need to export led state to userspace (wअगरi and mail) */
अटल काष्ठा key_entry keymap_acer_travelmate_610[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_KEY, 0x14, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x15, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x40, अणुKEY_WLANपूर्ण पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_WIFI_LED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_acer_travelmate_630[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x03, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x08, अणुKEY_MUTEपूर्ण पूर्ण, /* not 620 */
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_KEY, 0x20, अणुKEY_VOLUMEUPपूर्ण पूर्ण,
	अणु KE_KEY, 0x21, अणुKEY_VOLUMEDOWNपूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_aखोलो_1559as[] __initdata = अणु
	अणु KE_KEY,  0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY,  0x06, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_KEY,  0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY,  0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_KEY,  0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY,  0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_END,  0 पूर्ण,
पूर्ण;

अटल काष्ठा key_entry keymap_fs_amilo_d88x0[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x08, अणुKEY_MUTEपूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_WIFI_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_wistron_md2900[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_END, FE_MAIL_LED | FE_UNTESTED पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_wistron_md96500[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x05, अणुKEY_SWITCHVIDEOMODEपूर्ण पूर्ण, /* Display selection */
	अणु KE_KEY, 0x06, अणुKEY_DISPLAYTOGGLEपूर्ण पूर्ण, /* Display on/off */
	अणु KE_KEY, 0x08, अणुKEY_MUTEपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x20, अणुKEY_VOLUMEUPपूर्ण पूर्ण,
	अणु KE_KEY, 0x21, अणुKEY_VOLUMEDOWNपूर्ण पूर्ण,
	अणु KE_KEY, 0x22, अणुKEY_REWINDपूर्ण पूर्ण,
	अणु KE_KEY, 0x23, अणुKEY_FORWARDपूर्ण पूर्ण,
	अणु KE_KEY, 0x24, अणुKEY_PLAYPAUSEपूर्ण पूर्ण,
	अणु KE_KEY, 0x25, अणुKEY_STOPCDपूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_BLUETOOTH, 0x44 पूर्ण,
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_wistron_generic[] __initdata = अणु
	अणु KE_KEY, 0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY, 0x02, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x03, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x05, अणुKEY_SWITCHVIDEOMODEपूर्ण पूर्ण, /* Display selection */
	अणु KE_KEY, 0x06, अणुKEY_DISPLAYTOGGLEपूर्ण पूर्ण, /* Display on/off */
	अणु KE_KEY, 0x08, अणुKEY_MUTEपूर्ण पूर्ण,
	अणु KE_KEY, 0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY, 0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_KEY, 0x13, अणुKEY_PROG3पूर्ण पूर्ण,
	अणु KE_KEY, 0x14, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x15, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x20, अणुKEY_VOLUMEUPपूर्ण पूर्ण,
	अणु KE_KEY, 0x21, अणुKEY_VOLUMEDOWNपूर्ण पूर्ण,
	अणु KE_KEY, 0x22, अणुKEY_REWINDपूर्ण पूर्ण,
	अणु KE_KEY, 0x23, अणुKEY_FORWARDपूर्ण पूर्ण,
	अणु KE_KEY, 0x24, अणुKEY_PLAYPAUSEपूर्ण पूर्ण,
	अणु KE_KEY, 0x25, अणुKEY_STOPCDपूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY, 0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_KEY, 0x37, अणुKEY_DISPLAYTOGGLEपूर्ण पूर्ण, /* Display on/off */
	अणु KE_KEY, 0x40, अणुKEY_WLANपूर्ण पूर्ण,
	अणु KE_KEY, 0x49, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_SW, 0x4a, अणु.sw = अणुSW_LID, 1पूर्णपूर्ण पूर्ण, /* lid बंद */
	अणु KE_SW, 0x4b, अणु.sw = अणुSW_LID, 0पूर्णपूर्ण पूर्ण, /* lid खोलो */
	अणु KE_KEY, 0x6a, अणुKEY_CONFIGपूर्ण पूर्ण,
	अणु KE_KEY, 0x6d, अणुKEY_POWERपूर्ण पूर्ण,
	अणु KE_KEY, 0x71, अणुKEY_STOPCDपूर्ण पूर्ण,
	अणु KE_KEY, 0x72, अणुKEY_PLAYPAUSEपूर्ण पूर्ण,
	अणु KE_KEY, 0x74, अणुKEY_REWINDपूर्ण पूर्ण,
	अणु KE_KEY, 0x78, अणुKEY_FORWARDपूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_BLUETOOTH, 0x44 पूर्ण,
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_aखोलो_1557[] __initdata = अणु
	अणु KE_KEY,  0x01, अणुKEY_HELPपूर्ण पूर्ण,
	अणु KE_KEY,  0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY,  0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_KEY,  0x22, अणुKEY_REWINDपूर्ण पूर्ण,
	अणु KE_KEY,  0x23, अणुKEY_FORWARDपूर्ण पूर्ण,
	अणु KE_KEY,  0x24, अणुKEY_PLAYPAUSEपूर्ण पूर्ण,
	अणु KE_KEY,  0x25, अणुKEY_STOPCDपूर्ण पूर्ण,
	अणु KE_KEY,  0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY,  0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_END,  0 पूर्ण
पूर्ण;

अटल काष्ठा key_entry keymap_prestigio[] __initdata = अणु
	अणु KE_KEY,  0x11, अणुKEY_PROG1पूर्ण पूर्ण,
	अणु KE_KEY,  0x12, अणुKEY_PROG2पूर्ण पूर्ण,
	अणु KE_WIFI, 0x30 पूर्ण,
	अणु KE_KEY,  0x22, अणुKEY_REWINDपूर्ण पूर्ण,
	अणु KE_KEY,  0x23, अणुKEY_FORWARDपूर्ण पूर्ण,
	अणु KE_KEY,  0x24, अणुKEY_PLAYPAUSEपूर्ण पूर्ण,
	अणु KE_KEY,  0x25, अणुKEY_STOPCDपूर्ण पूर्ण,
	अणु KE_KEY,  0x31, अणुKEY_MAILपूर्ण पूर्ण,
	अणु KE_KEY,  0x36, अणुKEY_WWWपूर्ण पूर्ण,
	अणु KE_END,  0 पूर्ण
पूर्ण;


/*
 * If your machine is not here (which is currently rather likely), please send
 * a list of buttons and their key codes (reported when loading this module
 * with क्रमce=1) and the output of dmidecode to $MODULE_AUTHOR.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_ids[] __initस्थिर = अणु
	अणु
		/* Fujitsu-Siemens Amilo Pro V2000 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Pro V2000"),
		पूर्ण,
		.driver_data = keymap_fs_amilo_pro_v2000
	पूर्ण,
	अणु
		/* Fujitsu-Siemens Amilo Pro Edition V3505 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Pro Edition V3505"),
		पूर्ण,
		.driver_data = keymap_fs_amilo_pro_v3505
	पूर्ण,
	अणु
		/* Fujitsu-Siemens Amilo Pro Edition V8210 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Pro Series V8210"),
		पूर्ण,
		.driver_data = keymap_fs_amilo_pro_v8210
	पूर्ण,
	अणु
		/* Fujitsu-Siemens Amilo M7400 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO M        "),
		पूर्ण,
		.driver_data = keymap_fs_amilo_pro_v2000
	पूर्ण,
	अणु
		/* Maxdata Pro 7000 DX */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MAXDATA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Pro 7000"),
		पूर्ण,
		.driver_data = keymap_fs_amilo_pro_v2000
	पूर्ण,
	अणु
		/* Fujitsu N3510 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "N3510"),
		पूर्ण,
		.driver_data = keymap_fujitsu_n3510
	पूर्ण,
	अणु
		/* Acer Aspire 1500 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 1500"),
		पूर्ण,
		.driver_data = keymap_acer_aspire_1500
	पूर्ण,
	अणु
		/* Acer Aspire 1600 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 1600"),
		पूर्ण,
		.driver_data = keymap_acer_aspire_1600
	पूर्ण,
	अणु
		/* Acer Aspire 3020 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 3020"),
		पूर्ण,
		.driver_data = keymap_acer_aspire_5020
	पूर्ण,
	अणु
		/* Acer Aspire 5020 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5020"),
		पूर्ण,
		.driver_data = keymap_acer_aspire_5020
	पूर्ण,
	अणु
		/* Acer TravelMate 2100 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 2100"),
		पूर्ण,
		.driver_data = keymap_acer_aspire_5020
	पूर्ण,
	अणु
		/* Acer TravelMate 2410 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 2410"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_2410
	पूर्ण,
	अणु
		/* Acer TravelMate C300 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate C300"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_300
	पूर्ण,
	अणु
		/* Acer TravelMate C100 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate C100"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_300
	पूर्ण,
	अणु
		/* Acer TravelMate C110 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate C110"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_110
	पूर्ण,
	अणु
		/* Acer TravelMate 380 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 380"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_380
	पूर्ण,
	अणु
		/* Acer TravelMate 370 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 370"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_380 /* keyboard minus 1 key */
	पूर्ण,
	अणु
		/* Acer TravelMate 220 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 220"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_220
	पूर्ण,
	अणु
		/* Acer TravelMate 260 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 260"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_220
	पूर्ण,
	अणु
		/* Acer TravelMate 230 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 230"),
			/* acerhk looks क्रम "TravelMate F4..." ?! */
		पूर्ण,
		.driver_data = keymap_acer_travelmate_230
	पूर्ण,
	अणु
		/* Acer TravelMate 280 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 280"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_230
	पूर्ण,
	अणु
		/* Acer TravelMate 240 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 240"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_240
	पूर्ण,
	अणु
		/* Acer TravelMate 250 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 250"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_240
	पूर्ण,
	अणु
		/* Acer TravelMate 2424NWXCi */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 2420"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_240
	पूर्ण,
	अणु
		/* Acer TravelMate 350 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 350"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_350
	पूर्ण,
	अणु
		/* Acer TravelMate 360 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 360"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_360
	पूर्ण,
	अणु
		/* Acer TravelMate 610 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ACER"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 610"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_610
	पूर्ण,
	अणु
		/* Acer TravelMate 620 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 620"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_630
	पूर्ण,
	अणु
		/* Acer TravelMate 630 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 630"),
		पूर्ण,
		.driver_data = keymap_acer_travelmate_630
	पूर्ण,
	अणु
		/* AOpen 1559AS */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "E2U"),
			DMI_MATCH(DMI_BOARD_NAME, "E2U"),
		पूर्ण,
		.driver_data = keymap_aखोलो_1559as
	पूर्ण,
	अणु
		/* Medion MD 9783 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDIONNB"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MD 9783"),
		पूर्ण,
		.driver_data = keymap_wistron_ms2111
	पूर्ण,
	अणु
		/* Medion MD 40100 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDIONNB"),
			DMI_MATCH(DMI_PRODUCT_NAME, "WID2000"),
		पूर्ण,
		.driver_data = keymap_wistron_md40100
	पूर्ण,
	अणु
		/* Medion MD 2900 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDIONNB"),
			DMI_MATCH(DMI_PRODUCT_NAME, "WIM 2000"),
		पूर्ण,
		.driver_data = keymap_wistron_md2900
	पूर्ण,
	अणु
		/* Medion MD 42200 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Medion"),
			DMI_MATCH(DMI_PRODUCT_NAME, "WIM 2030"),
		पूर्ण,
		.driver_data = keymap_fs_amilo_pro_v2000
	पूर्ण,
	अणु
		/* Medion MD 96500 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDIONPC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "WIM 2040"),
		पूर्ण,
		.driver_data = keymap_wistron_md96500
	पूर्ण,
	अणु
		/* Medion MD 95400 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDIONPC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "WIM 2050"),
		पूर्ण,
		.driver_data = keymap_wistron_md96500
	पूर्ण,
	अणु
		/* Fujitsu Siemens Amilo D7820 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"), /* not sure */
			DMI_MATCH(DMI_PRODUCT_NAME, "Amilo D"),
		पूर्ण,
		.driver_data = keymap_fs_amilo_d88x0
	पूर्ण,
	अणु
		/* Fujitsu Siemens Amilo D88x0 */
		.callback = dmi_matched,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO D"),
		पूर्ण,
		.driver_data = keymap_fs_amilo_d88x0
	पूर्ण,
	अणु शून्य, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, dmi_ids);

/* Copy the good keymap, as the original ones are मुक्त'd */
अटल पूर्णांक __init copy_keymap(व्योम)
अणु
	स्थिर काष्ठा key_entry *key;
	काष्ठा key_entry *new_keymap;
	अचिन्हित पूर्णांक length = 1;

	क्रम (key = keymap; key->type != KE_END; key++)
		length++;

	new_keymap = kmemdup(keymap, length * माप(काष्ठा key_entry),
			     GFP_KERNEL);
	अगर (!new_keymap)
		वापस -ENOMEM;

	keymap = new_keymap;

	वापस 0;
पूर्ण

अटल पूर्णांक __init select_keymap(व्योम)
अणु
	dmi_check_प्रणाली(dmi_ids);
	अगर (keymap_name != शून्य) अणु
		अगर (म_भेद (keymap_name, "1557/MS2141") == 0)
			keymap = keymap_wistron_ms2141;
		अन्यथा अगर (म_भेद (keymap_name, "aopen1557") == 0)
			keymap = keymap_aखोलो_1557;
		अन्यथा अगर (म_भेद (keymap_name, "prestigio") == 0)
			keymap = keymap_prestigio;
		अन्यथा अगर (म_भेद (keymap_name, "generic") == 0)
			keymap = keymap_wistron_generic;
		अन्यथा अणु
			prपूर्णांकk(KERN_ERR "wistron_btns: Keymap unknown\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (keymap == शून्य) अणु
		अगर (!क्रमce) अणु
			prपूर्णांकk(KERN_ERR "wistron_btns: System unknown\n");
			वापस -ENODEV;
		पूर्ण
		keymap = keymap_empty;
	पूर्ण

	वापस copy_keymap();
पूर्ण

 /* Input layer पूर्णांकerface */

अटल काष्ठा input_dev *wistron_idev;
अटल अचिन्हित दीर्घ jअगरfies_last_press;
अटल bool wअगरi_enabled;
अटल bool bluetooth_enabled;

 /* led management */
अटल व्योम wistron_mail_led_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness value)
अणु
	bios_set_state(MAIL_LED, (value != LED_OFF) ? 1 : 0);
पूर्ण

/* same as setting up wअगरi card, but क्रम laptops on which the led is managed */
अटल व्योम wistron_wअगरi_led_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness value)
अणु
	bios_set_state(WIFI, (value != LED_OFF) ? 1 : 0);
पूर्ण

अटल काष्ठा led_classdev wistron_mail_led = अणु
	.name			= "wistron:green:mail",
	.brightness_set		= wistron_mail_led_set,
पूर्ण;

अटल काष्ठा led_classdev wistron_wअगरi_led = अणु
	.name			= "wistron:red:wifi",
	.brightness_set		= wistron_wअगरi_led_set,
पूर्ण;

अटल व्योम wistron_led_init(काष्ठा device *parent)
अणु
	अगर (leds_present & FE_WIFI_LED) अणु
		u16 wअगरi = bios_get_शेष_setting(WIFI);
		अगर (wअगरi & 1) अणु
			wistron_wअगरi_led.brightness = (wअगरi & 2) ? LED_FULL : LED_OFF;
			अगर (led_classdev_रेजिस्टर(parent, &wistron_wअगरi_led))
				leds_present &= ~FE_WIFI_LED;
			अन्यथा
				bios_set_state(WIFI, wistron_wअगरi_led.brightness);

		पूर्ण अन्यथा
			leds_present &= ~FE_WIFI_LED;
	पूर्ण

	अगर (leds_present & FE_MAIL_LED) अणु
		/* bios_get_शेष_setting(MAIL) always retuns 0, so just turn the led off */
		wistron_mail_led.brightness = LED_OFF;
		अगर (led_classdev_रेजिस्टर(parent, &wistron_mail_led))
			leds_present &= ~FE_MAIL_LED;
		अन्यथा
			bios_set_state(MAIL_LED, wistron_mail_led.brightness);
	पूर्ण
पूर्ण

अटल व्योम wistron_led_हटाओ(व्योम)
अणु
	अगर (leds_present & FE_MAIL_LED)
		led_classdev_unरेजिस्टर(&wistron_mail_led);

	अगर (leds_present & FE_WIFI_LED)
		led_classdev_unरेजिस्टर(&wistron_wअगरi_led);
पूर्ण

अटल अंतरभूत व्योम wistron_led_suspend(व्योम)
अणु
	अगर (leds_present & FE_MAIL_LED)
		led_classdev_suspend(&wistron_mail_led);

	अगर (leds_present & FE_WIFI_LED)
		led_classdev_suspend(&wistron_wअगरi_led);
पूर्ण

अटल अंतरभूत व्योम wistron_led_resume(व्योम)
अणु
	अगर (leds_present & FE_MAIL_LED)
		led_classdev_resume(&wistron_mail_led);

	अगर (leds_present & FE_WIFI_LED)
		led_classdev_resume(&wistron_wअगरi_led);
पूर्ण

अटल व्योम handle_key(u8 code)
अणु
	स्थिर काष्ठा key_entry *key =
		sparse_keymap_entry_from_scancode(wistron_idev, code);

	अगर (key) अणु
		चयन (key->type) अणु
		हाल KE_WIFI:
			अगर (have_wअगरi) अणु
				wअगरi_enabled = !wअगरi_enabled;
				bios_set_state(WIFI, wअगरi_enabled);
			पूर्ण
			अवरोध;

		हाल KE_BLUETOOTH:
			अगर (have_bluetooth) अणु
				bluetooth_enabled = !bluetooth_enabled;
				bios_set_state(BLUETOOTH, bluetooth_enabled);
			पूर्ण
			अवरोध;

		शेष:
			sparse_keymap_report_entry(wistron_idev, key, 1, true);
			अवरोध;
		पूर्ण
		jअगरfies_last_press = jअगरfies;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_NOTICE
			"wistron_btns: Unknown key code %02X\n", code);
	पूर्ण
पूर्ण

अटल व्योम poll_bios(bool discard)
अणु
	u8 qlen;
	u16 val;

	क्रम (;;) अणु
		qlen = CMOS_READ(cmos_address);
		अगर (qlen == 0)
			अवरोध;
		val = bios_pop_queue();
		अगर (val != 0 && !discard)
			handle_key((u8)val);
	पूर्ण
पूर्ण

अटल पूर्णांक wistron_flush(काष्ठा input_dev *dev)
अणु
	/* Flush stale event queue */
	poll_bios(true);

	वापस 0;
पूर्ण

अटल व्योम wistron_poll(काष्ठा input_dev *dev)
अणु
	poll_bios(false);

	/* Increase poll frequency अगर user is currently pressing keys (< 2s ago) */
	अगर (समय_beक्रमe(jअगरfies, jअगरfies_last_press + 2 * HZ))
		input_set_poll_पूर्णांकerval(dev, POLL_INTERVAL_BURST);
	अन्यथा
		input_set_poll_पूर्णांकerval(dev, POLL_INTERVAL_DEFAULT);
पूर्ण

अटल पूर्णांक wistron_setup_keymap(काष्ठा input_dev *dev,
					  काष्ठा key_entry *entry)
अणु
	चयन (entry->type) अणु

	/* अगर wअगरi or bluetooth are not available, create normal keys */
	हाल KE_WIFI:
		अगर (!have_wअगरi) अणु
			entry->type = KE_KEY;
			entry->keycode = KEY_WLAN;
		पूर्ण
		अवरोध;

	हाल KE_BLUETOOTH:
		अगर (!have_bluetooth) अणु
			entry->type = KE_KEY;
			entry->keycode = KEY_BLUETOOTH;
		पूर्ण
		अवरोध;

	हाल KE_END:
		अगर (entry->code & FE_UNTESTED)
			prपूर्णांकk(KERN_WARNING "Untested laptop multimedia keys, "
				"please report success or failure to "
				"eric.piel@tremplin-utc.net\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_input_dev(व्योम)
अणु
	पूर्णांक error;

	wistron_idev = input_allocate_device();
	अगर (!wistron_idev)
		वापस -ENOMEM;

	wistron_idev->name = "Wistron laptop buttons";
	wistron_idev->phys = "wistron/input0";
	wistron_idev->id.bustype = BUS_HOST;
	wistron_idev->dev.parent = &wistron_device->dev;

	wistron_idev->खोलो = wistron_flush;

	error = sparse_keymap_setup(wistron_idev, keymap, wistron_setup_keymap);
	अगर (error)
		जाओ err_मुक्त_dev;

	error = input_setup_polling(wistron_idev, wistron_poll);
	अगर (error)
		जाओ err_मुक्त_dev;

	input_set_poll_पूर्णांकerval(wistron_idev, POLL_INTERVAL_DEFAULT);

	error = input_रेजिस्टर_device(wistron_idev);
	अगर (error)
		जाओ err_मुक्त_dev;

	वापस 0;

 err_मुक्त_dev:
	input_मुक्त_device(wistron_idev);
	वापस error;
पूर्ण

/* Driver core */

अटल पूर्णांक wistron_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक err;

	bios_attach();
	cmos_address = bios_get_cmos_address();

	अगर (have_wअगरi) अणु
		u16 wअगरi = bios_get_शेष_setting(WIFI);
		अगर (wअगरi & 1)
			wअगरi_enabled = wअगरi & 2;
		अन्यथा
			have_wअगरi = 0;

		अगर (have_wअगरi)
			bios_set_state(WIFI, wअगरi_enabled);
	पूर्ण

	अगर (have_bluetooth) अणु
		u16 bt = bios_get_शेष_setting(BLUETOOTH);
		अगर (bt & 1)
			bluetooth_enabled = bt & 2;
		अन्यथा
			have_bluetooth = false;

		अगर (have_bluetooth)
			bios_set_state(BLUETOOTH, bluetooth_enabled);
	पूर्ण

	wistron_led_init(&dev->dev);

	err = setup_input_dev();
	अगर (err) अणु
		bios_detach();
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wistron_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	wistron_led_हटाओ();
	input_unरेजिस्टर_device(wistron_idev);
	bios_detach();

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wistron_suspend(काष्ठा device *dev)
अणु
	अगर (have_wअगरi)
		bios_set_state(WIFI, 0);

	अगर (have_bluetooth)
		bios_set_state(BLUETOOTH, 0);

	wistron_led_suspend();

	वापस 0;
पूर्ण

अटल पूर्णांक wistron_resume(काष्ठा device *dev)
अणु
	अगर (have_wअगरi)
		bios_set_state(WIFI, wअगरi_enabled);

	अगर (have_bluetooth)
		bios_set_state(BLUETOOTH, bluetooth_enabled);

	wistron_led_resume();

	poll_bios(true);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops wistron_pm_ops = अणु
	.suspend	= wistron_suspend,
	.resume		= wistron_resume,
	.घातeroff	= wistron_suspend,
	.restore	= wistron_resume,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver wistron_driver = अणु
	.driver		= अणु
		.name	= "wistron-bios",
#अगर_घोषित CONFIG_PM
		.pm	= &wistron_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe		= wistron_probe,
	.हटाओ		= wistron_हटाओ,
पूर्ण;

अटल पूर्णांक __init wb_module_init(व्योम)
अणु
	पूर्णांक err;

	err = select_keymap();
	अगर (err)
		वापस err;

	err = map_bios();
	अगर (err)
		जाओ err_मुक्त_keymap;

	err = platक्रमm_driver_रेजिस्टर(&wistron_driver);
	अगर (err)
		जाओ err_unmap_bios;

	wistron_device = platक्रमm_device_alloc("wistron-bios", -1);
	अगर (!wistron_device) अणु
		err = -ENOMEM;
		जाओ err_unरेजिस्टर_driver;
	पूर्ण

	err = platक्रमm_device_add(wistron_device);
	अगर (err)
		जाओ err_मुक्त_device;

	वापस 0;

 err_मुक्त_device:
	platक्रमm_device_put(wistron_device);
 err_unरेजिस्टर_driver:
	platक्रमm_driver_unरेजिस्टर(&wistron_driver);
 err_unmap_bios:
	unmap_bios();
 err_मुक्त_keymap:
	kमुक्त(keymap);

	वापस err;
पूर्ण

अटल व्योम __निकास wb_module_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(wistron_device);
	platक्रमm_driver_unरेजिस्टर(&wistron_driver);
	unmap_bios();
	kमुक्त(keymap);
पूर्ण

module_init(wb_module_init);
module_निकास(wb_module_निकास);
