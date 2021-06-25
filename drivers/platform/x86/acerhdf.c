<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * acerhdf - A driver which monitors the temperature
 *           of the aspire one netbook, turns on/off the fan
 *           as soon as the upper/lower threshold is reached.
 *
 * (C) 2009 - Peter Kaestle     peter (a) piie.net
 *                              https://piie.net
 *     2009 Borislav Petkov	bp (a) alien8.de
 *
 * Inspired by and many thanks to:
 *  o acerfand   - Rachel Greenham
 *  o acer_ec.pl - Michael Kurz     michi.kurz (at) googlemail.com
 *               - Petr Tomasek     tomasek (#) etf,cuni,cz
 *               - Carlos Corbacho  cathectic (at) gmail.com
 *  o lkml       - Matthew Garrett
 *               - Borislav Petkov
 *               - Andreas Mohr
 */

#घोषणा pr_fmt(fmt) "acerhdf: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/thermal.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * The driver is started with "kernel mode off" by शेष. That means, the BIOS
 * is still in control of the fan. In this mode the driver allows to पढ़ो the
 * temperature of the cpu and a userspace tool may take over control of the fan.
 * If the driver is चयनed to "kernel mode" (e.g. via module parameter) the
 * driver is in full control of the fan. If you want the module to be started in
 * kernel mode by शेष, define the following:
 */
#अघोषित START_IN_KERNEL_MODE

#घोषणा DRV_VER "0.7.0"

/*
 * According to the Atom N270 datasheet,
 * (http://करोwnload.पूर्णांकel.com/design/processor/datashts/320032.pdf) the
 * CPU's optimal operating limits denoted in junction temperature as
 * measured by the on-die thermal monitor are within 0 <= Tj <= 90. So,
 * assume 89तओC is critical temperature.
 */
#घोषणा ACERHDF_TEMP_CRIT 89000
#घोषणा ACERHDF_FAN_OFF 0
#घोषणा ACERHDF_FAN_AUTO 1

/*
 * No matter what value the user माला_दो पूर्णांकo the fanon variable, turn on the fan
 * at 80 degree Celsius to prevent hardware damage
 */
#घोषणा ACERHDF_MAX_FANON 80000

/*
 * Maximum पूर्णांकerval between two temperature checks is 15 seconds, as the die
 * can get hot really fast under heavy load (plus we shouldn't क्रमget about
 * possible impact of _बाह्यal_ aggressive sources such as heaters, sun etc.)
 */
#घोषणा ACERHDF_MAX_INTERVAL 15

#अगर_घोषित START_IN_KERNEL_MODE
अटल पूर्णांक kernelmode = 1;
#अन्यथा
अटल पूर्णांक kernelmode;
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक पूर्णांकerval = 10;
अटल अचिन्हित पूर्णांक fanon = 60000;
अटल अचिन्हित पूर्णांक fanoff = 53000;
अटल अचिन्हित पूर्णांक verbose;
अटल अचिन्हित पूर्णांक list_supported;
अटल अचिन्हित पूर्णांक fanstate = ACERHDF_FAN_AUTO;
अटल अक्षर क्रमce_bios[16];
अटल अक्षर क्रमce_product[16];
अटल अचिन्हित पूर्णांक prev_पूर्णांकerval;
अटल काष्ठा thermal_zone_device *thz_dev;
अटल काष्ठा thermal_cooling_device *cl_dev;
अटल काष्ठा platक्रमm_device *acerhdf_dev;

module_param(kernelmode, uपूर्णांक, 0);
MODULE_PARM_DESC(kernelmode, "Kernel mode fan control on / off");
module_param(fanon, uपूर्णांक, 0600);
MODULE_PARM_DESC(fanon, "Turn the fan on above this temperature");
module_param(fanoff, uपूर्णांक, 0600);
MODULE_PARM_DESC(fanoff, "Turn the fan off below this temperature");
module_param(verbose, uपूर्णांक, 0600);
MODULE_PARM_DESC(verbose, "Enable verbose dmesg output");
module_param(list_supported, uपूर्णांक, 0600);
MODULE_PARM_DESC(list_supported, "List supported models and BIOS versions");
module_param_string(क्रमce_bios, क्रमce_bios, 16, 0);
MODULE_PARM_DESC(क्रमce_bios, "Pretend system has this known supported BIOS version");
module_param_string(क्रमce_product, क्रमce_product, 16, 0);
MODULE_PARM_DESC(क्रमce_product, "Pretend system is this known supported model");

/*
 * cmd_off: to चयन the fan completely off and check अगर the fan is off
 *	cmd_स्वतः: to set the BIOS in control of the fan. The BIOS regulates then
 *		the fan speed depending on the temperature
 */
काष्ठा fancmd अणु
	u8 cmd_off;
	u8 cmd_स्वतः;
पूर्ण;

काष्ठा manualcmd अणु
	u8 mreg;
	u8 moff;
पूर्ण;

/* शेष रेजिस्टर and command to disable fan in manual mode */
अटल स्थिर काष्ठा manualcmd mcmd = अणु
	.mreg = 0x94,
	.moff = 0xff,
पूर्ण;

/* BIOS settings - only used during probe */
काष्ठा bios_settings अणु
	स्थिर अक्षर *venकरोr;
	स्थिर अक्षर *product;
	स्थिर अक्षर *version;
	u8 fanreg;
	u8 tempreg;
	काष्ठा fancmd cmd;
	पूर्णांक mcmd_enable;
पूर्ण;

/* This could be a daughter काष्ठा in the above, but not worth the redirect */
काष्ठा ctrl_settings अणु
	u8 fanreg;
	u8 tempreg;
	काष्ठा fancmd cmd;
	पूर्णांक mcmd_enable;
पूर्ण;

अटल काष्ठा ctrl_settings ctrl_cfg __पढ़ो_mostly;

/* Register addresses and values क्रम dअगरferent BIOS versions */
अटल स्थिर काष्ठा bios_settings bios_tbl[] __initस्थिर = अणु
	/* AOA110 */
	अणु"Acer", "AOA110", "v0.3109", 0x55, 0x58, अणु0x1f, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA110", "v0.3114", 0x55, 0x58, अणु0x1f, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA110", "v0.3301", 0x55, 0x58, अणु0xaf, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA110", "v0.3304", 0x55, 0x58, अणु0xaf, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA110", "v0.3305", 0x55, 0x58, अणु0xaf, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA110", "v0.3307", 0x55, 0x58, अणु0xaf, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA110", "v0.3308", 0x55, 0x58, अणु0x21, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA110", "v0.3309", 0x55, 0x58, अणु0x21, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA110", "v0.3310", 0x55, 0x58, अणु0x21, 0x00पूर्ण, 0पूर्ण,
	/* AOA150 */
	अणु"Acer", "AOA150", "v0.3114", 0x55, 0x58, अणु0x1f, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA150", "v0.3301", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA150", "v0.3304", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA150", "v0.3305", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA150", "v0.3307", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA150", "v0.3308", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA150", "v0.3309", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AOA150", "v0.3310", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	/* LT1005u */
	अणु"Acer", "LT-10Q", "v0.3310", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	/* Acer 1410 */
	अणु"Acer", "Aspire 1410", "v0.3108", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v0.3113", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v0.3115", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v0.3117", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v0.3119", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v0.3120", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v1.3204", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v1.3303", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v1.3308", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v1.3310", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1410", "v1.3314", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	/* Acer 1810xx */
	अणु"Acer", "Aspire 1810TZ", "v0.3108", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v0.3108", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v0.3113", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v0.3113", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v0.3115", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v0.3115", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v0.3117", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v0.3117", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v0.3119", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v0.3119", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v0.3120", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v0.3120", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v1.3204", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v1.3204", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v1.3303", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v1.3303", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v1.3308", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v1.3308", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v1.3310", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v1.3310", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810TZ", "v1.3314", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1810T",  "v1.3314", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	/* Acer 5755G */
	अणु"Acer", "Aspire 5755G",  "V1.20",   0xab, 0xb4, अणु0x00, 0x08पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 5755G",  "V1.21",   0xab, 0xb3, अणु0x00, 0x08पूर्ण, 0पूर्ण,
	/* Acer 521 */
	अणु"Acer", "AO521", "V1.11", 0x55, 0x58, अणु0x1f, 0x00पूर्ण, 0पूर्ण,
	/* Acer 531 */
	अणु"Acer", "AO531h", "v0.3104", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AO531h", "v0.3201", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AO531h", "v0.3304", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	/* Acer 751 */
	अणु"Acer", "AO751h", "V0.3206", 0x55, 0x58, अणु0x21, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "AO751h", "V0.3212", 0x55, 0x58, अणु0x21, 0x00पूर्ण, 0पूर्ण,
	/* Acer 753 */
	अणु"Acer", "Aspire One 753", "V1.24", 0x93, 0xac, अणु0x14, 0x04पूर्ण, 1पूर्ण,
	/* Acer 1825 */
	अणु"Acer", "Aspire 1825PTZ", "V1.3118", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Acer", "Aspire 1825PTZ", "V1.3127", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	/* Acer Extensa 5420 */
	अणु"Acer", "Extensa 5420", "V1.17", 0x93, 0xac, अणु0x14, 0x04पूर्ण, 1पूर्ण,
	/* Acer Aspire 5315 */
	अणु"Acer", "Aspire 5315", "V1.19", 0x93, 0xac, अणु0x14, 0x04पूर्ण, 1पूर्ण,
	/* Acer Aspire 5739 */
	अणु"Acer", "Aspire 5739G", "V1.3311", 0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	/* Acer TravelMate 7730 */
	अणु"Acer", "TravelMate 7730G", "v0.3509", 0x55, 0x58, अणु0xaf, 0x00पूर्ण, 0पूर्ण,
	/* Acer Aspire 7551 */
	अणु"Acer", "Aspire 7551", "V1.18", 0x93, 0xa8, अणु0x14, 0x04पूर्ण, 1पूर्ण,
	/* Acer TravelMate TM8573T */
	अणु"Acer", "TM8573T", "V1.13", 0x93, 0xa8, अणु0x14, 0x04पूर्ण, 1पूर्ण,
	/* Gateway */
	अणु"Gateway", "AOA110", "v0.3103",  0x55, 0x58, अणु0x21, 0x00पूर्ण, 0पूर्ण,
	अणु"Gateway", "AOA150", "v0.3103",  0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Gateway", "LT31",   "v1.3103",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Gateway", "LT31",   "v1.3201",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Gateway", "LT31",   "v1.3302",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Gateway", "LT31",   "v1.3303t", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Gateway", "LT31",   "v1.3307",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	/* Packard Bell */
	अणु"Packard Bell", "DOA150",  "v0.3104",  0x55, 0x58, अणु0x21, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOA150",  "v0.3105",  0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "AOA110",  "v0.3105",  0x55, 0x58, अणु0x21, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "AOA150",  "v0.3105",  0x55, 0x58, अणु0x20, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "ENBFT",   "V1.3118",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "ENBFT",   "V1.3127",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMU",   "v1.3303",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMU",   "v0.3120",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMU",   "v0.3108",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMU",   "v0.3113",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMU",   "v0.3115",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMU",   "v0.3117",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMU",   "v0.3119",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMU",   "v1.3204",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMA",   "v1.3201",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMA",   "v1.3302",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTMA",   "v1.3303t", 0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	अणु"Packard Bell", "DOTVR46", "v1.3308",  0x55, 0x58, अणु0x9e, 0x00पूर्ण, 0पूर्ण,
	/* pewpew-terminator */
	अणु"", "", "", 0, 0, अणु0, 0पूर्ण, 0पूर्ण
पूर्ण;

/*
 * this काष्ठा is used to inकाष्ठा thermal layer to use bang_bang instead of
 * शेष governor क्रम acerhdf
 */
अटल काष्ठा thermal_zone_params acerhdf_zone_params = अणु
	.governor_name = "bang_bang",
पूर्ण;

अटल पूर्णांक acerhdf_get_temp(पूर्णांक *temp)
अणु
	u8 पढ़ो_temp;

	अगर (ec_पढ़ो(ctrl_cfg.tempreg, &पढ़ो_temp))
		वापस -EINVAL;

	*temp = पढ़ो_temp * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_get_fanstate(पूर्णांक *state)
अणु
	u8 fan;

	अगर (ec_पढ़ो(ctrl_cfg.fanreg, &fan))
		वापस -EINVAL;

	अगर (fan != ctrl_cfg.cmd.cmd_off)
		*state = ACERHDF_FAN_AUTO;
	अन्यथा
		*state = ACERHDF_FAN_OFF;

	वापस 0;
पूर्ण

अटल व्योम acerhdf_change_fanstate(पूर्णांक state)
अणु
	अचिन्हित अक्षर cmd;

	अगर (verbose)
		pr_notice("fan %s\n", state == ACERHDF_FAN_OFF ? "OFF" : "ON");

	अगर ((state != ACERHDF_FAN_OFF) && (state != ACERHDF_FAN_AUTO)) अणु
		pr_err("invalid fan state %d requested, setting to auto!\n",
		       state);
		state = ACERHDF_FAN_AUTO;
	पूर्ण

	cmd = (state == ACERHDF_FAN_OFF) ? ctrl_cfg.cmd.cmd_off
					 : ctrl_cfg.cmd.cmd_स्वतः;
	fanstate = state;

	ec_ग_लिखो(ctrl_cfg.fanreg, cmd);

	अगर (ctrl_cfg.mcmd_enable && state == ACERHDF_FAN_OFF) अणु
		अगर (verbose)
			pr_notice("turning off fan manually\n");
		ec_ग_लिखो(mcmd.mreg, mcmd.moff);
	पूर्ण
पूर्ण

अटल व्योम acerhdf_check_param(काष्ठा thermal_zone_device *thermal)
अणु
	अगर (fanon > ACERHDF_MAX_FANON) अणु
		pr_err("fanon temperature too high, set to %d\n",
		       ACERHDF_MAX_FANON);
		fanon = ACERHDF_MAX_FANON;
	पूर्ण

	अगर (kernelmode && prev_पूर्णांकerval != पूर्णांकerval) अणु
		अगर (पूर्णांकerval > ACERHDF_MAX_INTERVAL) अणु
			pr_err("interval too high, set to %d\n",
			       ACERHDF_MAX_INTERVAL);
			पूर्णांकerval = ACERHDF_MAX_INTERVAL;
		पूर्ण
		अगर (verbose)
			pr_notice("interval changed to: %d\n", पूर्णांकerval);

		अगर (thermal)
			thermal->polling_delay_jअगरfies =
				round_jअगरfies(msecs_to_jअगरfies(पूर्णांकerval * 1000));

		prev_पूर्णांकerval = पूर्णांकerval;
	पूर्ण
पूर्ण

/*
 * This is the thermal zone callback which करोes the delayed polling of the fan
 * state. We करो check /sysfs-originating settings here in acerhdf_check_param()
 * as late as the polling पूर्णांकerval is since we can't करो that in the respective
 * accessors of the module parameters.
 */
अटल पूर्णांक acerhdf_get_ec_temp(काष्ठा thermal_zone_device *thermal, पूर्णांक *t)
अणु
	पूर्णांक temp, err = 0;

	err = acerhdf_get_temp(&temp);
	अगर (err)
		वापस err;

	अगर (verbose)
		pr_notice("temp %d\n", temp);

	*t = temp;
	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_bind(काष्ठा thermal_zone_device *thermal,
			काष्ठा thermal_cooling_device *cdev)
अणु
	/* अगर the cooling device is the one from acerhdf bind it */
	अगर (cdev != cl_dev)
		वापस 0;

	अगर (thermal_zone_bind_cooling_device(thermal, 0, cdev,
			THERMAL_NO_LIMIT, THERMAL_NO_LIMIT,
			THERMAL_WEIGHT_DEFAULT)) अणु
		pr_err("error binding cooling dev\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_unbind(काष्ठा thermal_zone_device *thermal,
			  काष्ठा thermal_cooling_device *cdev)
अणु
	अगर (cdev != cl_dev)
		वापस 0;

	अगर (thermal_zone_unbind_cooling_device(thermal, 0, cdev)) अणु
		pr_err("error unbinding cooling dev\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम acerhdf_revert_to_bios_mode(व्योम)
अणु
	acerhdf_change_fanstate(ACERHDF_FAN_AUTO);
	kernelmode = 0;

	pr_notice("kernel mode fan control OFF\n");
पूर्ण
अटल अंतरभूत व्योम acerhdf_enable_kernelmode(व्योम)
अणु
	kernelmode = 1;

	pr_notice("kernel mode fan control ON\n");
पूर्ण

/*
 * set operation mode;
 * enabled: the thermal layer of the kernel takes care about
 *          the temperature and the fan.
 * disabled: the BIOS takes control of the fan.
 */
अटल पूर्णांक acerhdf_change_mode(काष्ठा thermal_zone_device *thermal,
			       क्रमागत thermal_device_mode mode)
अणु
	अगर (mode == THERMAL_DEVICE_DISABLED && kernelmode)
		acerhdf_revert_to_bios_mode();
	अन्यथा अगर (mode == THERMAL_DEVICE_ENABLED && !kernelmode)
		acerhdf_enable_kernelmode();

	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_get_trip_type(काष्ठा thermal_zone_device *thermal, पूर्णांक trip,
				 क्रमागत thermal_trip_type *type)
अणु
	अगर (trip == 0)
		*type = THERMAL_TRIP_ACTIVE;
	अन्यथा अगर (trip == 1)
		*type = THERMAL_TRIP_CRITICAL;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_get_trip_hyst(काष्ठा thermal_zone_device *thermal, पूर्णांक trip,
				 पूर्णांक *temp)
अणु
	अगर (trip != 0)
		वापस -EINVAL;

	*temp = fanon - fanoff;

	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_get_trip_temp(काष्ठा thermal_zone_device *thermal, पूर्णांक trip,
				 पूर्णांक *temp)
अणु
	अगर (trip == 0)
		*temp = fanon;
	अन्यथा अगर (trip == 1)
		*temp = ACERHDF_TEMP_CRIT;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_get_crit_temp(काष्ठा thermal_zone_device *thermal,
				 पूर्णांक *temperature)
अणु
	*temperature = ACERHDF_TEMP_CRIT;
	वापस 0;
पूर्ण

/* bind callback functions to thermalzone */
अटल काष्ठा thermal_zone_device_ops acerhdf_dev_ops = अणु
	.bind = acerhdf_bind,
	.unbind = acerhdf_unbind,
	.get_temp = acerhdf_get_ec_temp,
	.change_mode = acerhdf_change_mode,
	.get_trip_type = acerhdf_get_trip_type,
	.get_trip_hyst = acerhdf_get_trip_hyst,
	.get_trip_temp = acerhdf_get_trip_temp,
	.get_crit_temp = acerhdf_get_crit_temp,
पूर्ण;


/*
 * cooling device callback functions
 * get maximal fan cooling state
 */
अटल पूर्णांक acerhdf_get_max_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	*state = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	पूर्णांक err = 0, पंचांगp;

	err = acerhdf_get_fanstate(&पंचांगp);
	अगर (err)
		वापस err;

	*state = (पंचांगp == ACERHDF_FAN_AUTO) ? 1 : 0;
	वापस 0;
पूर्ण

/* change current fan state - is overwritten when running in kernel mode */
अटल पूर्णांक acerhdf_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ state)
अणु
	पूर्णांक cur_temp, cur_state, err = 0;

	अगर (!kernelmode)
		वापस 0;

	err = acerhdf_get_temp(&cur_temp);
	अगर (err) अणु
		pr_err("error reading temperature, hand off control to BIOS\n");
		जाओ err_out;
	पूर्ण

	err = acerhdf_get_fanstate(&cur_state);
	अगर (err) अणु
		pr_err("error reading fan state, hand off control to BIOS\n");
		जाओ err_out;
	पूर्ण

	अगर (state == 0) अणु
		अगर (cur_state == ACERHDF_FAN_AUTO)
			acerhdf_change_fanstate(ACERHDF_FAN_OFF);
	पूर्ण अन्यथा अणु
		अगर (cur_state == ACERHDF_FAN_OFF)
			acerhdf_change_fanstate(ACERHDF_FAN_AUTO);
	पूर्ण
	वापस 0;

err_out:
	acerhdf_revert_to_bios_mode();
	वापस -EINVAL;
पूर्ण

/* bind fan callbacks to fan device */
अटल स्थिर काष्ठा thermal_cooling_device_ops acerhdf_cooling_ops = अणु
	.get_max_state = acerhdf_get_max_state,
	.get_cur_state = acerhdf_get_cur_state,
	.set_cur_state = acerhdf_set_cur_state,
पूर्ण;

/* suspend / resume functionality */
अटल पूर्णांक acerhdf_suspend(काष्ठा device *dev)
अणु
	अगर (kernelmode)
		acerhdf_change_fanstate(ACERHDF_FAN_AUTO);

	अगर (verbose)
		pr_notice("going suspend\n");

	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_probe(काष्ठा platक्रमm_device *device)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक acerhdf_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops acerhdf_pm_ops = अणु
	.suspend = acerhdf_suspend,
	.मुक्तze  = acerhdf_suspend,
पूर्ण;

अटल काष्ठा platक्रमm_driver acerhdf_driver = अणु
	.driver = अणु
		.name  = "acerhdf",
		.pm    = &acerhdf_pm_ops,
	पूर्ण,
	.probe = acerhdf_probe,
	.हटाओ = acerhdf_हटाओ,
पूर्ण;

/* checks अगर str begins with start */
अटल पूर्णांक str_starts_with(स्थिर अक्षर *str, स्थिर अक्षर *start)
अणु
	अचिन्हित दीर्घ str_len = 0, start_len = 0;

	str_len = म_माप(str);
	start_len = म_माप(start);

	अगर (str_len >= start_len &&
			!म_भेदन(str, start, start_len))
		वापस 1;

	वापस 0;
पूर्ण

/* check hardware */
अटल पूर्णांक __init acerhdf_check_hardware(व्योम)
अणु
	अक्षर स्थिर *venकरोr, *version, *product;
	स्थिर काष्ठा bios_settings *bt = शून्य;
	पूर्णांक found = 0;

	/* get BIOS data */
	venकरोr  = dmi_get_प्रणाली_info(DMI_SYS_VENDOR);
	version = dmi_get_प्रणाली_info(DMI_BIOS_VERSION);
	product = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);

	अगर (!venकरोr || !version || !product) अणु
		pr_err("error getting hardware information\n");
		वापस -EINVAL;
	पूर्ण

	pr_info("Acer Aspire One Fan driver, v.%s\n", DRV_VER);

	अगर (list_supported) अणु
		pr_info("List of supported Manufacturer/Model/BIOS:\n");
		pr_info("---------------------------------------------------\n");
		क्रम (bt = bios_tbl; bt->venकरोr[0]; bt++) अणु
			pr_info("%-13s | %-17s | %-10s\n", bt->venकरोr,
				bt->product, bt->version);
		पूर्ण
		pr_info("---------------------------------------------------\n");
		वापस -ECANCELED;
	पूर्ण

	अगर (क्रमce_bios[0]) अणु
		version = क्रमce_bios;
		pr_info("forcing BIOS version: %s\n", version);
		kernelmode = 0;
	पूर्ण

	अगर (क्रमce_product[0]) अणु
		product = क्रमce_product;
		pr_info("forcing BIOS product: %s\n", product);
		kernelmode = 0;
	पूर्ण

	अगर (verbose)
		pr_info("BIOS info: %s %s, product: %s\n",
			venकरोr, version, product);

	/* search BIOS version and venकरोr in BIOS settings table */
	क्रम (bt = bios_tbl; bt->venकरोr[0]; bt++) अणु
		/*
		 * check अगर actual hardware BIOS venकरोr, product and version
		 * IDs start with the strings of BIOS table entry
		 */
		अगर (str_starts_with(venकरोr, bt->venकरोr) &&
				str_starts_with(product, bt->product) &&
				str_starts_with(version, bt->version)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		pr_err("unknown (unsupported) BIOS version %s/%s/%s, please report, aborting!\n",
		       venकरोr, product, version);
		वापस -EINVAL;
	पूर्ण

	/* Copy control settings from BIOS table beक्रमe we मुक्त it. */
	ctrl_cfg.fanreg = bt->fanreg;
	ctrl_cfg.tempreg = bt->tempreg;
	स_नकल(&ctrl_cfg.cmd, &bt->cmd, माप(काष्ठा fancmd));
	ctrl_cfg.mcmd_enable = bt->mcmd_enable;

	/*
	 * अगर started with kernel mode off, prevent the kernel from चयनing
	 * off the fan
	 */
	अगर (!kernelmode) अणु
		pr_notice("Fan control off, to enable do:\n");
		pr_notice("echo -n \"enabled\" > /sys/class/thermal/thermal_zoneN/mode # N=0,1,2...\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init acerhdf_रेजिस्टर_platक्रमm(व्योम)
अणु
	पूर्णांक err = 0;

	err = platक्रमm_driver_रेजिस्टर(&acerhdf_driver);
	अगर (err)
		वापस err;

	acerhdf_dev = platक्रमm_device_alloc("acerhdf", -1);
	अगर (!acerhdf_dev) अणु
		err = -ENOMEM;
		जाओ err_device_alloc;
	पूर्ण
	err = platक्रमm_device_add(acerhdf_dev);
	अगर (err)
		जाओ err_device_add;

	वापस 0;

err_device_add:
	platक्रमm_device_put(acerhdf_dev);
err_device_alloc:
	platक्रमm_driver_unरेजिस्टर(&acerhdf_driver);
	वापस err;
पूर्ण

अटल व्योम acerhdf_unरेजिस्टर_platक्रमm(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(acerhdf_dev);
	platक्रमm_driver_unरेजिस्टर(&acerhdf_driver);
पूर्ण

अटल पूर्णांक __init acerhdf_रेजिस्टर_thermal(व्योम)
अणु
	पूर्णांक ret;

	cl_dev = thermal_cooling_device_रेजिस्टर("acerhdf-fan", शून्य,
						 &acerhdf_cooling_ops);

	अगर (IS_ERR(cl_dev))
		वापस -EINVAL;

	thz_dev = thermal_zone_device_रेजिस्टर("acerhdf", 2, 0, शून्य,
					      &acerhdf_dev_ops,
					      &acerhdf_zone_params, 0,
					      (kernelmode) ? पूर्णांकerval*1000 : 0);
	अगर (IS_ERR(thz_dev))
		वापस -EINVAL;

	अगर (kernelmode)
		ret = thermal_zone_device_enable(thz_dev);
	अन्यथा
		ret = thermal_zone_device_disable(thz_dev);
	अगर (ret)
		वापस ret;

	अगर (म_भेद(thz_dev->governor->name,
				acerhdf_zone_params.governor_name)) अणु
		pr_err("Didn't get thermal governor %s, perhaps not compiled into thermal subsystem.\n",
				acerhdf_zone_params.governor_name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम acerhdf_unरेजिस्टर_thermal(व्योम)
अणु
	अगर (cl_dev) अणु
		thermal_cooling_device_unरेजिस्टर(cl_dev);
		cl_dev = शून्य;
	पूर्ण

	अगर (thz_dev) अणु
		thermal_zone_device_unरेजिस्टर(thz_dev);
		thz_dev = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __init acerhdf_init(व्योम)
अणु
	पूर्णांक err = 0;

	err = acerhdf_check_hardware();
	अगर (err)
		जाओ out_err;

	err = acerhdf_रेजिस्टर_platक्रमm();
	अगर (err)
		जाओ out_err;

	err = acerhdf_रेजिस्टर_thermal();
	अगर (err)
		जाओ err_unreg;

	वापस 0;

err_unreg:
	acerhdf_unरेजिस्टर_thermal();
	acerhdf_unरेजिस्टर_platक्रमm();

out_err:
	वापस err;
पूर्ण

अटल व्योम __निकास acerhdf_निकास(व्योम)
अणु
	acerhdf_change_fanstate(ACERHDF_FAN_AUTO);
	acerhdf_unरेजिस्टर_thermal();
	acerhdf_unरेजिस्टर_platक्रमm();
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter Kaestle");
MODULE_DESCRIPTION("Aspire One temperature and fan driver");
MODULE_ALIAS("dmi:*:*Acer*:pnAOA*:");
MODULE_ALIAS("dmi:*:*Acer*:pnAO751h*:");
MODULE_ALIAS("dmi:*:*Acer*:pnAspire*1410*:");
MODULE_ALIAS("dmi:*:*Acer*:pnAspire*1810*:");
MODULE_ALIAS("dmi:*:*Acer*:pnAspire*5755G:");
MODULE_ALIAS("dmi:*:*Acer*:pnAspire*1825PTZ:");
MODULE_ALIAS("dmi:*:*Acer*:pnAO521*:");
MODULE_ALIAS("dmi:*:*Acer*:pnAO531*:");
MODULE_ALIAS("dmi:*:*Acer*:pnAspire*5739G:");
MODULE_ALIAS("dmi:*:*Acer*:pnAspire*One*753:");
MODULE_ALIAS("dmi:*:*Acer*:pnAspire*5315:");
MODULE_ALIAS("dmi:*:*Acer*:TravelMate*7730G:");
MODULE_ALIAS("dmi:*:*Acer*:pnAspire*7551:");
MODULE_ALIAS("dmi:*:*Acer*:TM8573T:");
MODULE_ALIAS("dmi:*:*Gateway*:pnAOA*:");
MODULE_ALIAS("dmi:*:*Gateway*:pnLT31*:");
MODULE_ALIAS("dmi:*:*Packard*Bell*:pnAOA*:");
MODULE_ALIAS("dmi:*:*Packard*Bell*:pnDOA*:");
MODULE_ALIAS("dmi:*:*Packard*Bell*:pnDOTMU*:");
MODULE_ALIAS("dmi:*:*Packard*Bell*:pnENBFT*:");
MODULE_ALIAS("dmi:*:*Packard*Bell*:pnDOTMA*:");
MODULE_ALIAS("dmi:*:*Packard*Bell*:pnDOTVR46*:");
MODULE_ALIAS("dmi:*:*Acer*:pnExtensa*5420*:");

module_init(acerhdf_init);
module_निकास(acerhdf_निकास);

अटल पूर्णांक पूर्णांकerval_set_uपूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;

	ret = param_set_uपूर्णांक(val, kp);
	अगर (ret)
		वापस ret;

	acerhdf_check_param(thz_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops पूर्णांकerval_ops = अणु
	.set = पूर्णांकerval_set_uपूर्णांक,
	.get = param_get_uपूर्णांक,
पूर्ण;

module_param_cb(पूर्णांकerval, &पूर्णांकerval_ops, &पूर्णांकerval, 0600);
MODULE_PARM_DESC(पूर्णांकerval, "Polling interval of temperature check");
