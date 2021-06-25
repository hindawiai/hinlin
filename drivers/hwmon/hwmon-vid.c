<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * hwmon-vid.c - VID/VRM/VRD voltage conversions
 *
 * Copyright (c) 2004 Ruकरोlf Marek <r.marek@assembler.cz>
 *
 * Partly imported from i2c-vid.h of the lm_sensors project
 * Copyright (c) 2002 Mark D. Studebaker <mdsxyz123@yahoo.com>
 * With assistance from Trent Piepho <xyzzy@speakeasy.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hwmon-vid.h>

/*
 * Common code क्रम decoding VID pins.
 *
 * References:
 *
 * For VRM 8.4 to 9.1, "VRM x.y DC-DC Converter Design Guidelines",
 * available at http://developer.पूर्णांकel.com/.
 *
 * For VRD 10.0 and up, "VRD x.y Design Guide",
 * available at http://developer.पूर्णांकel.com/.
 *
 * AMD Athlon 64 and AMD Opteron Processors, AMD Publication 26094,
 * http://support.amd.com/us/Processor_TechDocs/26094.PDF
 * Table 74. VID Code Voltages
 * This corresponds to an arbitrary VRM code of 24 in the functions below.
 * These CPU models (K8 revision <= E) have 5 VID pins. See also:
 * Revision Guide क्रम AMD Athlon 64 and AMD Opteron Processors, AMD Publication 25759,
 * http://www.amd.com/us-en/assets/content_type/white_papers_and_tech_करोcs/25759.pdf
 *
 * AMD NPT Family 0Fh Processors, AMD Publication 32559,
 * http://www.amd.com/us-en/assets/content_type/white_papers_and_tech_करोcs/32559.pdf
 * Table 71. VID Code Voltages
 * This corresponds to an arbitrary VRM code of 25 in the functions below.
 * These CPU models (K8 revision >= F) have 6 VID pins. See also:
 * Revision Guide क्रम AMD NPT Family 0Fh Processors, AMD Publication 33610,
 * http://www.amd.com/us-en/assets/content_type/white_papers_and_tech_करोcs/33610.pdf
 *
 * The 17 specअगरication is in fact Intel Mobile Voltage Positioning -
 * (IMVP-II). You can find more inक्रमmation in the datasheet of Max1718
 * http://www.maxim-ic.com/quick_view2.cfm/qv_pk/2452
 *
 * The 13 specअगरication corresponds to the Intel Pentium M series. There
 * करोesn't seem to be any named specअगरication क्रम these. The conversion
 * tables are detailed directly in the various Pentium M datasheets:
 * https://www.पूर्णांकel.com/design/पूर्णांकarch/pentiumm/करोcs_pentiumm.hपंचांग
 *
 * The 14 specअगरication corresponds to Intel Core series. There
 * करोesn't seem to be any named specअगरication क्रम these. The conversion
 * tables are detailed directly in the various Pentium Core datasheets:
 * https://www.पूर्णांकel.com/design/mobile/datashts/309221.hपंचांग
 *
 * The 110 (VRM 11) specअगरication corresponds to Intel Conroe based series.
 * https://www.पूर्णांकel.com/design/processor/applnots/313214.hपंचांग
 */

/*
 * vrm is the VRM/VRD करोcument version multiplied by 10.
 * val is the 4-bit or more VID code.
 * Returned value is in mV to aव्योम भग्नing poपूर्णांक in the kernel.
 * Some VID have some bits in uV scale, this is rounded to mV.
 */
पूर्णांक vid_from_reg(पूर्णांक val, u8 vrm)
अणु
	पूर्णांक vid;

	चयन (vrm) अणु

	हाल 100:		/* VRD 10.0 */
		/* compute in uV, round to mV */
		val &= 0x3f;
		अगर ((val & 0x1f) == 0x1f)
			वापस 0;
		अगर ((val & 0x1f) <= 0x09 || val == 0x0a)
			vid = 1087500 - (val & 0x1f) * 25000;
		अन्यथा
			vid = 1862500 - (val & 0x1f) * 25000;
		अगर (val & 0x20)
			vid -= 12500;
		वापस (vid + 500) / 1000;

	हाल 110:		/* Intel Conroe */
				/* compute in uV, round to mV */
		val &= 0xff;
		अगर (val < 0x02 || val > 0xb2)
			वापस 0;
		वापस (1600000 - (val - 2) * 6250 + 500) / 1000;

	हाल 24:		/* Athlon64 & Opteron */
		val &= 0x1f;
		अगर (val == 0x1f)
			वापस 0;
		fallthrough;
	हाल 25:		/* AMD NPT 0Fh */
		val &= 0x3f;
		वापस (val < 32) ? 1550 - 25 * val
			: 775 - (25 * (val - 31)) / 2;

	हाल 26:		/* AMD family 10h to 15h, serial VID */
		val &= 0x7f;
		अगर (val >= 0x7c)
			वापस 0;
		वापस DIV_ROUND_CLOSEST(15500 - 125 * val, 10);

	हाल 91:		/* VRM 9.1 */
	हाल 90:		/* VRM 9.0 */
		val &= 0x1f;
		वापस val == 0x1f ? 0 :
				     1850 - val * 25;

	हाल 85:		/* VRM 8.5 */
		val &= 0x1f;
		वापस (val & 0x10  ? 25 : 0) +
		       ((val & 0x0f) > 0x04 ? 2050 : 1250) -
		       ((val & 0x0f) * 50);

	हाल 84:		/* VRM 8.4 */
		val &= 0x0f;
		fallthrough;
	हाल 82:		/* VRM 8.2 */
		val &= 0x1f;
		वापस val == 0x1f ? 0 :
		       val & 0x10  ? 5100 - (val) * 100 :
				     2050 - (val) * 50;
	हाल 17:		/* Intel IMVP-II */
		val &= 0x1f;
		वापस val & 0x10 ? 975 - (val & 0xF) * 25 :
				    1750 - val * 50;
	हाल 13:
	हाल 131:
		val &= 0x3f;
		/* Exception क्रम Eden ULV 500 MHz */
		अगर (vrm == 131 && val == 0x3f)
			val++;
		वापस 1708 - val * 16;
	हाल 14:		/* Intel Core */
				/* compute in uV, round to mV */
		val &= 0x7f;
		वापस val > 0x77 ? 0 : (1500000 - (val * 12500) + 500) / 1000;
	शेष:		/* report 0 क्रम unknown */
		अगर (vrm)
			pr_warn("Requested unsupported VRM version (%u)\n",
				(अचिन्हित पूर्णांक)vrm);
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(vid_from_reg);

/*
 * After this poपूर्णांक is the code to स्वतःmatically determine which
 * VRM/VRD specअगरication should be used depending on the CPU.
 */

काष्ठा vrm_model अणु
	u8 venकरोr;
	u8 family;
	u8 model_from;
	u8 model_to;
	u8 stepping_to;
	u8 vrm_type;
पूर्ण;

#घोषणा ANY 0xFF

#अगर_घोषित CONFIG_X86

/*
 * The stepping_to parameter is highest acceptable stepping क्रम current line.
 * The model match must be exact क्रम 4-bit values. For model values 0x10
 * and above (extended model), all models below the parameter will match.
 */

अटल काष्ठा vrm_model vrm_models[] = अणु
	अणुX86_VENDOR_AMD, 0x6, 0x0, ANY, ANY, 90पूर्ण,	/* Athlon Duron etc */
	अणुX86_VENDOR_AMD, 0xF, 0x0, 0x3F, ANY, 24पूर्ण,	/* Athlon 64, Opteron */
	/*
	 * In theory, all NPT family 0Fh processors have 6 VID pins and should
	 * thus use vrm 25, however in practice not all मुख्यboards route the
	 * 6th VID pin because it is never needed. So we use the 5 VID pin
	 * variant (vrm 24) क्रम the models which exist today.
	 */
	अणुX86_VENDOR_AMD, 0xF, 0x40, 0x7F, ANY, 24पूर्ण,	/* NPT family 0Fh */
	अणुX86_VENDOR_AMD, 0xF, 0x80, ANY, ANY, 25पूर्ण,	/* future fam. 0Fh */
	अणुX86_VENDOR_AMD, 0x10, 0x0, ANY, ANY, 25पूर्ण,	/* NPT family 10h */
	अणुX86_VENDOR_AMD, 0x11, 0x0, ANY, ANY, 26पूर्ण,	/* family 11h */
	अणुX86_VENDOR_AMD, 0x12, 0x0, ANY, ANY, 26पूर्ण,	/* family 12h */
	अणुX86_VENDOR_AMD, 0x14, 0x0, ANY, ANY, 26पूर्ण,	/* family 14h */
	अणुX86_VENDOR_AMD, 0x15, 0x0, ANY, ANY, 26पूर्ण,	/* family 15h */

	अणुX86_VENDOR_INTEL, 0x6, 0x0, 0x6, ANY, 82पूर्ण,	/* Pentium Pro,
							 * Pentium II, Xeon,
							 * Mobile Pentium,
							 * Celeron */
	अणुX86_VENDOR_INTEL, 0x6, 0x7, 0x7, ANY, 84पूर्ण,	/* Pentium III, Xeon */
	अणुX86_VENDOR_INTEL, 0x6, 0x8, 0x8, ANY, 82पूर्ण,	/* Pentium III, Xeon */
	अणुX86_VENDOR_INTEL, 0x6, 0x9, 0x9, ANY, 13पूर्ण,	/* Pentium M (130 nm) */
	अणुX86_VENDOR_INTEL, 0x6, 0xA, 0xA, ANY, 82पूर्ण,	/* Pentium III Xeon */
	अणुX86_VENDOR_INTEL, 0x6, 0xB, 0xB, ANY, 85पूर्ण,	/* Tualatin */
	अणुX86_VENDOR_INTEL, 0x6, 0xD, 0xD, ANY, 13पूर्ण,	/* Pentium M (90 nm) */
	अणुX86_VENDOR_INTEL, 0x6, 0xE, 0xE, ANY, 14पूर्ण,	/* Intel Core (65 nm) */
	अणुX86_VENDOR_INTEL, 0x6, 0xF, ANY, ANY, 110पूर्ण,	/* Intel Conroe and
							 * later */
	अणुX86_VENDOR_INTEL, 0xF, 0x0, 0x0, ANY, 90पूर्ण,	/* P4 */
	अणुX86_VENDOR_INTEL, 0xF, 0x1, 0x1, ANY, 90पूर्ण,	/* P4 Willamette */
	अणुX86_VENDOR_INTEL, 0xF, 0x2, 0x2, ANY, 90पूर्ण,	/* P4 Northwood */
	अणुX86_VENDOR_INTEL, 0xF, 0x3, ANY, ANY, 100पूर्ण,	/* Prescott and above
							 * assume VRD 10 */

	अणुX86_VENDOR_CENTAUR, 0x6, 0x7, 0x7, ANY, 85पूर्ण,	/* Eden ESP/Ezra */
	अणुX86_VENDOR_CENTAUR, 0x6, 0x8, 0x8, 0x7, 85पूर्ण,	/* Ezra T */
	अणुX86_VENDOR_CENTAUR, 0x6, 0x9, 0x9, 0x7, 85पूर्ण,	/* Nehemiah */
	अणुX86_VENDOR_CENTAUR, 0x6, 0x9, 0x9, ANY, 17पूर्ण,	/* C3-M, Eden-N */
	अणुX86_VENDOR_CENTAUR, 0x6, 0xA, 0xA, 0x7, 0पूर्ण,	/* No inक्रमmation */
	अणुX86_VENDOR_CENTAUR, 0x6, 0xA, 0xA, ANY, 13पूर्ण,	/* C7-M, C7,
							 * Eden (Esther) */
	अणुX86_VENDOR_CENTAUR, 0x6, 0xD, 0xD, ANY, 134पूर्ण,	/* C7-D, C7-M, C7,
							 * Eden (Esther) */
पूर्ण;

/*
 * Special हाल क्रम VIA model D: there are two dअगरferent possible
 * VID tables, so we have to figure out first, which one must be
 * used. This resolves temporary drm value 134 to 14 (Intel Core
 * 7-bit VID), 13 (Pentium M 6-bit VID) or 131 (Pentium M 6-bit VID
 * + quirk क्रम Eden ULV 500 MHz).
 * Note: something similar might be needed क्रम model A, I'm not sure.
 */
अटल u8 get_via_model_d_vrm(व्योम)
अणु
	अचिन्हित पूर्णांक vid, bअक्रम, __maybe_unused dummy;
	अटल स्थिर अक्षर *bअक्रमs[4] = अणु
		"C7-M", "C7", "Eden", "C7-D"
	पूर्ण;

	rdmsr(0x198, dummy, vid);
	vid &= 0xff;

	rdmsr(0x1154, bअक्रम, dummy);
	bअक्रम = ((bअक्रम >> 4) ^ (bअक्रम >> 2)) & 0x03;

	अगर (vid > 0x3f) अणु
		pr_info("Using %d-bit VID table for VIA %s CPU\n",
			7, bअक्रमs[bअक्रम]);
		वापस 14;
	पूर्ण अन्यथा अणु
		pr_info("Using %d-bit VID table for VIA %s CPU\n",
			6, bअक्रमs[bअक्रम]);
		/* Enable quirk क्रम Eden */
		वापस bअक्रम == 2 ? 131 : 13;
	पूर्ण
पूर्ण

अटल u8 find_vrm(u8 family, u8 model, u8 stepping, u8 venकरोr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vrm_models); i++) अणु
		अगर (venकरोr == vrm_models[i].venकरोr &&
		    family == vrm_models[i].family &&
		    model >= vrm_models[i].model_from &&
		    model <= vrm_models[i].model_to &&
		    stepping <= vrm_models[i].stepping_to)
			वापस vrm_models[i].vrm_type;
	पूर्ण

	वापस 0;
पूर्ण

u8 vid_which_vrm(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	u8 vrm_ret;

	अगर (c->x86 < 6)		/* Any CPU with family lower than 6 */
		वापस 0;	/* करोesn't have VID */

	vrm_ret = find_vrm(c->x86, c->x86_model, c->x86_stepping, c->x86_venकरोr);
	अगर (vrm_ret == 134)
		vrm_ret = get_via_model_d_vrm();
	अगर (vrm_ret == 0)
		pr_info("Unknown VRM version of your x86 CPU\n");
	वापस vrm_ret;
पूर्ण

/* and now क्रम something completely dअगरferent क्रम the non-x86 world */
#अन्यथा
u8 vid_which_vrm(व्योम)
अणु
	pr_info("Unknown VRM version of your CPU\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL(vid_which_vrm);

MODULE_AUTHOR("Rudolf Marek <r.marek@assembler.cz>");

MODULE_DESCRIPTION("hwmon-vid driver");
MODULE_LICENSE("GPL");
