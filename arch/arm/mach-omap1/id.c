<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/id.c
 *
 * OMAP1 CPU identअगरication code
 *
 * Copyright (C) 2004 Nokia Corporation
 * Written by Tony Lindgren <tony@atomide.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश "soc.h"

#समावेश <mach/hardware.h>

#समावेश "common.h"

#घोषणा OMAP_DIE_ID_0		0xfffe1800
#घोषणा OMAP_DIE_ID_1		0xfffe1804
#घोषणा OMAP_PRODUCTION_ID_0	0xfffe2000
#घोषणा OMAP_PRODUCTION_ID_1	0xfffe2004
#घोषणा OMAP32_ID_0		0xfffed400
#घोषणा OMAP32_ID_1		0xfffed404

काष्ठा omap_id अणु
	u16	jtag_id;	/* Used to determine OMAP type */
	u8	die_rev;	/* Processor revision */
	u32	omap_id;	/* OMAP revision */
	u32	type;		/* Cpu id bits [31:08], cpu class bits [07:00] */
पूर्ण;

अटल अचिन्हित पूर्णांक omap_revision;

/* Register values to detect the OMAP version */
अटल काष्ठा omap_id omap_ids[] __initdata = अणु
	अणु .jtag_id = 0xb574, .die_rev = 0x2, .omap_id = 0x03310315, .type = 0x03100000पूर्ण,
	अणु .jtag_id = 0x355f, .die_rev = 0x0, .omap_id = 0x03320000, .type = 0x07300100पूर्ण,
	अणु .jtag_id = 0xb55f, .die_rev = 0x0, .omap_id = 0x03320000, .type = 0x07300300पूर्ण,
	अणु .jtag_id = 0xb62c, .die_rev = 0x1, .omap_id = 0x03320500, .type = 0x08500000पूर्ण,
	अणु .jtag_id = 0xb470, .die_rev = 0x0, .omap_id = 0x03310100, .type = 0x15100000पूर्ण,
	अणु .jtag_id = 0xb576, .die_rev = 0x0, .omap_id = 0x03320000, .type = 0x16100000पूर्ण,
	अणु .jtag_id = 0xb576, .die_rev = 0x2, .omap_id = 0x03320100, .type = 0x16110000पूर्ण,
	अणु .jtag_id = 0xb576, .die_rev = 0x3, .omap_id = 0x03320100, .type = 0x16100c00पूर्ण,
	अणु .jtag_id = 0xb576, .die_rev = 0x0, .omap_id = 0x03320200, .type = 0x16100d00पूर्ण,
	अणु .jtag_id = 0xb613, .die_rev = 0x0, .omap_id = 0x03320300, .type = 0x1610ef00पूर्ण,
	अणु .jtag_id = 0xb613, .die_rev = 0x0, .omap_id = 0x03320300, .type = 0x1610ef00पूर्ण,
	अणु .jtag_id = 0xb576, .die_rev = 0x1, .omap_id = 0x03320100, .type = 0x16110000पूर्ण,
	अणु .jtag_id = 0xb58c, .die_rev = 0x2, .omap_id = 0x03320200, .type = 0x16110b00पूर्ण,
	अणु .jtag_id = 0xb58c, .die_rev = 0x3, .omap_id = 0x03320200, .type = 0x16110c00पूर्ण,
	अणु .jtag_id = 0xb65f, .die_rev = 0x0, .omap_id = 0x03320400, .type = 0x16212300पूर्ण,
	अणु .jtag_id = 0xb65f, .die_rev = 0x1, .omap_id = 0x03320400, .type = 0x16212300पूर्ण,
	अणु .jtag_id = 0xb65f, .die_rev = 0x1, .omap_id = 0x03320500, .type = 0x16212300पूर्ण,
	अणु .jtag_id = 0xb5f7, .die_rev = 0x0, .omap_id = 0x03330000, .type = 0x17100000पूर्ण,
	अणु .jtag_id = 0xb5f7, .die_rev = 0x1, .omap_id = 0x03330100, .type = 0x17100000पूर्ण,
	अणु .jtag_id = 0xb5f7, .die_rev = 0x2, .omap_id = 0x03330100, .type = 0x17100000पूर्ण,
पूर्ण;

अचिन्हित पूर्णांक omap_rev(व्योम)
अणु
	वापस omap_revision;
पूर्ण
EXPORT_SYMBOL(omap_rev);

/*
 * Get OMAP type from PROD_ID.
 * 1710 has the PROD_ID in bits 15:00, not in 16:01 as करोcumented in TRM.
 * 1510 PROD_ID is empty, and 1610 PROD_ID करोes not make sense.
 * Unकरोcumented रेजिस्टर in TEST BLOCK is used as fallback; This seems to
 * work on 1510, 1610 & 1710. The official way hopefully will work in future
 * processors.
 */
अटल u16 __init omap_get_jtag_id(व्योम)
अणु
	u32 prod_id, omap_id;

	prod_id = omap_पढ़ोl(OMAP_PRODUCTION_ID_1);
	omap_id = omap_पढ़ोl(OMAP32_ID_1);

	/* Check क्रम unusable OMAP_PRODUCTION_ID_1 on 1611B/5912 and 730/850 */
	अगर (((prod_id >> 20) == 0) || (prod_id == omap_id))
		prod_id = 0;
	अन्यथा
		prod_id &= 0xffff;

	अगर (prod_id)
		वापस prod_id;

	/* Use OMAP32_ID_1 as fallback */
	prod_id = ((omap_id >> 12) & 0xffff);

	वापस prod_id;
पूर्ण

/*
 * Get OMAP revision from DIE_REV.
 * Early 1710 processors may have broken OMAP_DIE_ID, it contains PROD_ID.
 * Unकरोcumented रेजिस्टर in the TEST BLOCK is used as fallback.
 * REVISIT: This करोes not seem to work on 1510
 */
अटल u8 __init omap_get_die_rev(व्योम)
अणु
	u32 die_rev;

	die_rev = omap_पढ़ोl(OMAP_DIE_ID_1);

	/* Check क्रम broken OMAP_DIE_ID on early 1710 */
	अगर (((die_rev >> 12) & 0xffff) == omap_get_jtag_id())
		die_rev = 0;

	die_rev = (die_rev >> 17) & 0xf;
	अगर (die_rev)
		वापस die_rev;

	die_rev = (omap_पढ़ोl(OMAP32_ID_1) >> 28) & 0xf;

	वापस die_rev;
पूर्ण

व्योम __init omap_check_revision(व्योम)
अणु
	पूर्णांक i;
	u16 jtag_id;
	u8 die_rev;
	u32 omap_id;
	u8 cpu_type;

	jtag_id = omap_get_jtag_id();
	die_rev = omap_get_die_rev();
	omap_id = omap_पढ़ोl(OMAP32_ID_0);

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_DEBUG "OMAP_DIE_ID_0: 0x%08x\n", omap_पढ़ोl(OMAP_DIE_ID_0));
	prपूर्णांकk(KERN_DEBUG "OMAP_DIE_ID_1: 0x%08x DIE_REV: %i\n",
		omap_पढ़ोl(OMAP_DIE_ID_1),
	       (omap_पढ़ोl(OMAP_DIE_ID_1) >> 17) & 0xf);
	prपूर्णांकk(KERN_DEBUG "OMAP_PRODUCTION_ID_0: 0x%08x\n",
		omap_पढ़ोl(OMAP_PRODUCTION_ID_0));
	prपूर्णांकk(KERN_DEBUG "OMAP_PRODUCTION_ID_1: 0x%08x JTAG_ID: 0x%04x\n",
		omap_पढ़ोl(OMAP_PRODUCTION_ID_1),
		omap_पढ़ोl(OMAP_PRODUCTION_ID_1) & 0xffff);
	prपूर्णांकk(KERN_DEBUG "OMAP32_ID_0: 0x%08x\n", omap_पढ़ोl(OMAP32_ID_0));
	prपूर्णांकk(KERN_DEBUG "OMAP32_ID_1: 0x%08x\n", omap_पढ़ोl(OMAP32_ID_1));
	prपूर्णांकk(KERN_DEBUG "JTAG_ID: 0x%04x DIE_REV: %i\n", jtag_id, die_rev);
#पूर्ण_अगर

	प्रणाली_serial_high = omap_पढ़ोl(OMAP_DIE_ID_0);
	प्रणाली_serial_low = omap_पढ़ोl(OMAP_DIE_ID_1);

	/* First check only the major version in a safe way */
	क्रम (i = 0; i < ARRAY_SIZE(omap_ids); i++) अणु
		अगर (jtag_id == (omap_ids[i].jtag_id)) अणु
			omap_revision = omap_ids[i].type;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check अगर we can find the die revision */
	क्रम (i = 0; i < ARRAY_SIZE(omap_ids); i++) अणु
		अगर (jtag_id == omap_ids[i].jtag_id && die_rev == omap_ids[i].die_rev) अणु
			omap_revision = omap_ids[i].type;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Finally check also the omap_id */
	क्रम (i = 0; i < ARRAY_SIZE(omap_ids); i++) अणु
		अगर (jtag_id == omap_ids[i].jtag_id
		    && die_rev == omap_ids[i].die_rev
		    && omap_id == omap_ids[i].omap_id) अणु
			omap_revision = omap_ids[i].type;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Add the cpu class info (7xx, 15xx, 16xx, 24xx) */
	cpu_type = omap_revision >> 24;

	चयन (cpu_type) अणु
	हाल 0x07:
	हाल 0x08:
		omap_revision |= 0x07;
		अवरोध;
	हाल 0x03:
	हाल 0x15:
		omap_revision |= 0x15;
		अवरोध;
	हाल 0x16:
	हाल 0x17:
		omap_revision |= 0x16;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "Unknown OMAP cpu type: 0x%02x\n", cpu_type);
	पूर्ण

	pr_info("OMAP%04x", omap_revision >> 16);
	अगर ((omap_revision >> 8) & 0xff)
		pr_cont("%x", (omap_revision >> 8) & 0xff);
	pr_cont(" revision %i handled as %02xxx id: %08x%08x\n",
	       die_rev, omap_revision & 0xff, प्रणाली_serial_low,
	       प्रणाली_serial_high);
पूर्ण

