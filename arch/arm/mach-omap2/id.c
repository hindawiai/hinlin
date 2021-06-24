<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap2/id.c
 *
 * OMAP2 CPU identअगरication code
 *
 * Copyright (C) 2005 Nokia Corporation
 * Written by Tony Lindgren <tony@atomide.com>
 *
 * Copyright (C) 2009-11 Texas Instruments
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_SOC_BUS
#समावेश <linux/sys_soc.h>
#पूर्ण_अगर

#समावेश <यंत्र/cputype.h>

#समावेश "common.h"

#समावेश "id.h"

#समावेश "soc.h"
#समावेश "control.h"

#घोषणा OMAP4_SILICON_TYPE_STANDARD		0x01
#घोषणा OMAP4_SILICON_TYPE_PERFORMANCE		0x02

#घोषणा OMAP_SOC_MAX_NAME_LENGTH		16

अटल अचिन्हित पूर्णांक omap_revision;
अटल अक्षर soc_name[OMAP_SOC_MAX_NAME_LENGTH];
अटल अक्षर soc_rev[OMAP_SOC_MAX_NAME_LENGTH];
u32 omap_features;

अचिन्हित पूर्णांक omap_rev(व्योम)
अणु
	वापस omap_revision;
पूर्ण
EXPORT_SYMBOL(omap_rev);

पूर्णांक omap_type(व्योम)
अणु
	अटल u32 val = OMAP2_DEVICETYPE_MASK;

	अगर (val < OMAP2_DEVICETYPE_MASK)
		वापस val;

	अगर (soc_is_omap24xx()) अणु
		val = omap_ctrl_पढ़ोl(OMAP24XX_CONTROL_STATUS);
	पूर्ण अन्यथा अगर (soc_is_ti81xx()) अणु
		val = omap_ctrl_पढ़ोl(TI81XX_CONTROL_STATUS);
	पूर्ण अन्यथा अगर (soc_is_am33xx() || soc_is_am43xx()) अणु
		val = omap_ctrl_पढ़ोl(AM33XX_CONTROL_STATUS);
	पूर्ण अन्यथा अगर (soc_is_omap34xx()) अणु
		val = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_STATUS);
	पूर्ण अन्यथा अगर (soc_is_omap44xx()) अणु
		val = omap_ctrl_पढ़ोl(OMAP4_CTRL_MODULE_CORE_STATUS);
	पूर्ण अन्यथा अगर (soc_is_omap54xx() || soc_is_dra7xx()) अणु
		val = omap_ctrl_पढ़ोl(OMAP5XXX_CONTROL_STATUS);
		val &= OMAP5_DEVICETYPE_MASK;
		val >>= 6;
		जाओ out;
	पूर्ण अन्यथा अणु
		pr_err("Cannot detect omap type!\n");
		जाओ out;
	पूर्ण

	val &= OMAP2_DEVICETYPE_MASK;
	val >>= 8;

out:
	वापस val;
पूर्ण
EXPORT_SYMBOL(omap_type);


/*----------------------------------------------------------------------------*/

#घोषणा OMAP_TAP_IDCODE		0x0204
#घोषणा OMAP_TAP_DIE_ID_0	0x0218
#घोषणा OMAP_TAP_DIE_ID_1	0x021C
#घोषणा OMAP_TAP_DIE_ID_2	0x0220
#घोषणा OMAP_TAP_DIE_ID_3	0x0224

#घोषणा OMAP_TAP_DIE_ID_44XX_0	0x0200
#घोषणा OMAP_TAP_DIE_ID_44XX_1	0x0208
#घोषणा OMAP_TAP_DIE_ID_44XX_2	0x020c
#घोषणा OMAP_TAP_DIE_ID_44XX_3	0x0210

#घोषणा पढ़ो_tap_reg(reg)	पढ़ोl_relaxed(tap_base  + (reg))

काष्ठा omap_id अणु
	u16	hawkeye;	/* Silicon type (Hawkeye id) */
	u8	dev;		/* Device type from production_id reg */
	u32	type;		/* Combined type id copied to omap_revision */
पूर्ण;

/* Register values to detect the OMAP version */
अटल काष्ठा omap_id omap_ids[] __initdata = अणु
	अणु .hawkeye = 0xb5d9, .dev = 0x0, .type = 0x24200024 पूर्ण,
	अणु .hawkeye = 0xb5d9, .dev = 0x1, .type = 0x24201024 पूर्ण,
	अणु .hawkeye = 0xb5d9, .dev = 0x2, .type = 0x24202024 पूर्ण,
	अणु .hawkeye = 0xb5d9, .dev = 0x4, .type = 0x24220024 पूर्ण,
	अणु .hawkeye = 0xb5d9, .dev = 0x8, .type = 0x24230024 पूर्ण,
	अणु .hawkeye = 0xb68a, .dev = 0x0, .type = 0x24300024 पूर्ण,
पूर्ण;

अटल व्योम __iomem *tap_base;
अटल u16 tap_prod_id;

व्योम omap_get_die_id(काष्ठा omap_die_id *odi)
अणु
	अगर (soc_is_omap44xx() || soc_is_omap54xx() || soc_is_dra7xx()) अणु
		odi->id_0 = पढ़ो_tap_reg(OMAP_TAP_DIE_ID_44XX_0);
		odi->id_1 = पढ़ो_tap_reg(OMAP_TAP_DIE_ID_44XX_1);
		odi->id_2 = पढ़ो_tap_reg(OMAP_TAP_DIE_ID_44XX_2);
		odi->id_3 = पढ़ो_tap_reg(OMAP_TAP_DIE_ID_44XX_3);

		वापस;
	पूर्ण
	odi->id_0 = पढ़ो_tap_reg(OMAP_TAP_DIE_ID_0);
	odi->id_1 = पढ़ो_tap_reg(OMAP_TAP_DIE_ID_1);
	odi->id_2 = पढ़ो_tap_reg(OMAP_TAP_DIE_ID_2);
	odi->id_3 = पढ़ो_tap_reg(OMAP_TAP_DIE_ID_3);
पूर्ण

अटल पूर्णांक __init omap_feed_अक्रमpool(व्योम)
अणु
	काष्ठा omap_die_id odi;

	/* Throw the die ID पूर्णांकo the entropy pool at boot */
	omap_get_die_id(&odi);
	add_device_अक्रमomness(&odi, माप(odi));
	वापस 0;
पूर्ण
omap_device_initcall(omap_feed_अक्रमpool);

व्योम __init omap2xxx_check_revision(व्योम)
अणु
	पूर्णांक i, j;
	u32 idcode, prod_id;
	u16 hawkeye;
	u8  dev_type, rev;
	काष्ठा omap_die_id odi;

	idcode = पढ़ो_tap_reg(OMAP_TAP_IDCODE);
	prod_id = पढ़ो_tap_reg(tap_prod_id);
	hawkeye = (idcode >> 12) & 0xffff;
	rev = (idcode >> 28) & 0x0f;
	dev_type = (prod_id >> 16) & 0x0f;
	omap_get_die_id(&odi);

	pr_debug("OMAP_TAP_IDCODE 0x%08x REV %i HAWKEYE 0x%04x MANF %03x\n",
		 idcode, rev, hawkeye, (idcode >> 1) & 0x7ff);
	pr_debug("OMAP_TAP_DIE_ID_0: 0x%08x\n", odi.id_0);
	pr_debug("OMAP_TAP_DIE_ID_1: 0x%08x DEV_REV: %i\n",
		 odi.id_1, (odi.id_1 >> 28) & 0xf);
	pr_debug("OMAP_TAP_DIE_ID_2: 0x%08x\n", odi.id_2);
	pr_debug("OMAP_TAP_DIE_ID_3: 0x%08x\n", odi.id_3);
	pr_debug("OMAP_TAP_PROD_ID_0: 0x%08x DEV_TYPE: %i\n",
		 prod_id, dev_type);

	/* Check hawkeye ids */
	क्रम (i = 0; i < ARRAY_SIZE(omap_ids); i++) अणु
		अगर (hawkeye == omap_ids[i].hawkeye)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(omap_ids)) अणु
		prपूर्णांकk(KERN_ERR "Unknown OMAP CPU id\n");
		वापस;
	पूर्ण

	क्रम (j = i; j < ARRAY_SIZE(omap_ids); j++) अणु
		अगर (dev_type == omap_ids[j].dev)
			अवरोध;
	पूर्ण

	अगर (j == ARRAY_SIZE(omap_ids)) अणु
		pr_err("Unknown OMAP device type. Handling it as OMAP%04x\n",
		       omap_ids[i].type >> 16);
		j = i;
	पूर्ण

	प्र_लिखो(soc_name, "OMAP%04x", omap_rev() >> 16);
	प्र_लिखो(soc_rev, "ES%x", (omap_rev() >> 12) & 0xf);

	pr_info("%s", soc_name);
	अगर ((omap_rev() >> 8) & 0x0f)
		pr_cont("%s", soc_rev);
	pr_cont("\n");
पूर्ण

#घोषणा OMAP3_SHOW_FEATURE(feat)		\
	अगर (omap3_has_ ##feat())		\
		n += scnम_लिखो(buf + n, माप(buf) - n, #feat " ");

अटल व्योम __init omap3_cpuinfo(व्योम)
अणु
	स्थिर अक्षर *cpu_name;
	अक्षर buf[64];
	पूर्णांक n = 0;

	स_रखो(buf, 0, माप(buf));

	/*
	 * OMAP3430 and OMAP3530 are assumed to be same.
	 *
	 * OMAP3525, OMAP3515 and OMAP3503 can be detected only based
	 * on available features. Upon detection, update the CPU id
	 * and CPU class bits.
	 */
	अगर (soc_is_omap3630()) अणु
		अगर (omap3_has_iva() && omap3_has_sgx()) अणु
			cpu_name = (omap3_has_isp()) ? "OMAP3630/DM3730" : "OMAP3621";
		पूर्ण अन्यथा अगर (omap3_has_iva()) अणु
			cpu_name = "DM3725";
		पूर्ण अन्यथा अगर (omap3_has_sgx()) अणु
			cpu_name = "OMAP3615/AM3715";
		पूर्ण अन्यथा अणु
			cpu_name = (omap3_has_isp()) ? "AM3703" : "OMAP3611";
		पूर्ण
	पूर्ण अन्यथा अगर (soc_is_am35xx()) अणु
		cpu_name = (omap3_has_sgx()) ? "AM3517" : "AM3505";
	पूर्ण अन्यथा अगर (soc_is_ti816x()) अणु
		cpu_name = "TI816X";
	पूर्ण अन्यथा अगर (soc_is_am335x()) अणु
		cpu_name =  "AM335X";
	पूर्ण अन्यथा अगर (soc_is_am437x()) अणु
		cpu_name =  "AM437x";
	पूर्ण अन्यथा अगर (soc_is_ti814x()) अणु
		cpu_name = "TI814X";
	पूर्ण अन्यथा अगर (omap3_has_iva() && omap3_has_sgx()) अणु
		/* OMAP3430, OMAP3525, OMAP3515, OMAP3503 devices */
		cpu_name = "OMAP3430/3530";
	पूर्ण अन्यथा अगर (omap3_has_iva()) अणु
		cpu_name = "OMAP3525";
	पूर्ण अन्यथा अगर (omap3_has_sgx()) अणु
		cpu_name = "OMAP3515";
	पूर्ण अन्यथा अणु
		cpu_name = "OMAP3503";
	पूर्ण

	scnम_लिखो(soc_name, माप(soc_name), "%s", cpu_name);

	/* Prपूर्णांक verbose inक्रमmation */
	n += scnम_लिखो(buf, माप(buf) - n, "%s %s (", soc_name, soc_rev);

	OMAP3_SHOW_FEATURE(l2cache);
	OMAP3_SHOW_FEATURE(iva);
	OMAP3_SHOW_FEATURE(sgx);
	OMAP3_SHOW_FEATURE(neon);
	OMAP3_SHOW_FEATURE(isp);
	OMAP3_SHOW_FEATURE(192mhz_clk);
	अगर (*(buf + n - 1) == ' ')
		n--;
	n += scnम_लिखो(buf + n, माप(buf) - n, ")\n");
	pr_info("%s", buf);
पूर्ण

#घोषणा OMAP3_CHECK_FEATURE(status,feat)				\
	अगर (((status & OMAP3_ ##feat## _MASK) 				\
		>> OMAP3_ ##feat## _SHIFT) != FEAT_ ##feat## _NONE) अणु 	\
		omap_features |= OMAP3_HAS_ ##feat;			\
	पूर्ण

व्योम __init omap3xxx_check_features(व्योम)
अणु
	u32 status;

	omap_features = 0;

	status = omap_ctrl_पढ़ोl(OMAP3_CONTROL_OMAP_STATUS);

	OMAP3_CHECK_FEATURE(status, L2CACHE);
	OMAP3_CHECK_FEATURE(status, IVA);
	OMAP3_CHECK_FEATURE(status, SGX);
	OMAP3_CHECK_FEATURE(status, NEON);
	OMAP3_CHECK_FEATURE(status, ISP);
	अगर (soc_is_omap3630())
		omap_features |= OMAP3_HAS_192MHZ_CLK;
	अगर (soc_is_omap3430() || soc_is_omap3630())
		omap_features |= OMAP3_HAS_IO_WAKEUP;
	अगर (soc_is_omap3630() || omap_rev() == OMAP3430_REV_ES3_1 ||
	    omap_rev() == OMAP3430_REV_ES3_1_2)
		omap_features |= OMAP3_HAS_IO_CHAIN_CTRL;

	omap_features |= OMAP3_HAS_SDRC;

	/*
	 * am35x fixups:
	 * - The am35x Chip ID रेजिस्टर has bits 12, 7:5, and 3:2 marked as
	 *   reserved and thereक्रमe वापस 0 when पढ़ो.  Unक्रमtunately,
	 *   OMAP3_CHECK_FEATURE() will पूर्णांकerpret some of those zeroes to
	 *   mean that a feature is present even though it isn't so clear
	 *   the incorrectly set feature bits.
	 */
	अगर (soc_is_am35xx())
		omap_features &= ~(OMAP3_HAS_IVA | OMAP3_HAS_ISP);

	/*
	 * TODO: Get additional info (where applicable)
	 *       e.g. Size of L2 cache.
	 */

	omap3_cpuinfo();
पूर्ण

व्योम __init omap4xxx_check_features(व्योम)
अणु
	u32 si_type;

	si_type =
	(पढ़ो_tap_reg(OMAP4_CTRL_MODULE_CORE_STD_FUSE_PROD_ID_1) >> 16) & 0x03;

	अगर (si_type == OMAP4_SILICON_TYPE_PERFORMANCE)
		omap_features = OMAP4_HAS_PERF_SILICON;
पूर्ण

व्योम __init ti81xx_check_features(व्योम)
अणु
	omap_features = OMAP3_HAS_NEON;
	omap3_cpuinfo();
पूर्ण

व्योम __init am33xx_check_features(व्योम)
अणु
	u32 status;

	omap_features = OMAP3_HAS_NEON;

	status = omap_ctrl_पढ़ोl(AM33XX_DEV_FEATURE);
	अगर (status & AM33XX_SGX_MASK)
		omap_features |= OMAP3_HAS_SGX;

	omap3_cpuinfo();
पूर्ण

व्योम __init omap3xxx_check_revision(व्योम)
अणु
	स्थिर अक्षर *cpu_rev;
	u32 cpuid, idcode;
	u16 hawkeye;
	u8 rev;

	/*
	 * We cannot access revision रेजिस्टरs on ES1.0.
	 * If the processor type is Cortex-A8 and the revision is 0x0
	 * it means its Cortex r0p0 which is 3430 ES1.0.
	 */
	cpuid = पढ़ो_cpuid_id();
	अगर ((((cpuid >> 4) & 0xfff) == 0xc08) && ((cpuid & 0xf) == 0x0)) अणु
		omap_revision = OMAP3430_REV_ES1_0;
		cpu_rev = "1.0";
		वापस;
	पूर्ण

	/*
	 * Detection क्रम 34xx ES2.0 and above can be करोne with just
	 * hawkeye and rev. See TRM 1.5.2 Device Identअगरication.
	 * Note that rev करोes not map directly to our defined processor
	 * revision numbers as ES1.0 uses value 0.
	 */
	idcode = पढ़ो_tap_reg(OMAP_TAP_IDCODE);
	hawkeye = (idcode >> 12) & 0xffff;
	rev = (idcode >> 28) & 0xff;

	चयन (hawkeye) अणु
	हाल 0xb7ae:
		/* Handle 34xx/35xx devices */
		चयन (rev) अणु
		हाल 0: /* Take care of early samples */
		हाल 1:
			omap_revision = OMAP3430_REV_ES2_0;
			cpu_rev = "2.0";
			अवरोध;
		हाल 2:
			omap_revision = OMAP3430_REV_ES2_1;
			cpu_rev = "2.1";
			अवरोध;
		हाल 3:
			omap_revision = OMAP3430_REV_ES3_0;
			cpu_rev = "3.0";
			अवरोध;
		हाल 4:
			omap_revision = OMAP3430_REV_ES3_1;
			cpu_rev = "3.1";
			अवरोध;
		हाल 7:
		शेष:
			/* Use the latest known revision as शेष */
			omap_revision = OMAP3430_REV_ES3_1_2;
			cpu_rev = "3.1.2";
		पूर्ण
		अवरोध;
	हाल 0xb868:
		/*
		 * Handle OMAP/AM 3505/3517 devices
		 *
		 * Set the device to be OMAP3517 here. Actual device
		 * is identअगरied later based on the features.
		 */
		चयन (rev) अणु
		हाल 0:
			omap_revision = AM35XX_REV_ES1_0;
			cpu_rev = "1.0";
			अवरोध;
		हाल 1:
		शेष:
			omap_revision = AM35XX_REV_ES1_1;
			cpu_rev = "1.1";
		पूर्ण
		अवरोध;
	हाल 0xb891:
		/* Handle 36xx devices */

		चयन(rev) अणु
		हाल 0: /* Take care of early samples */
			omap_revision = OMAP3630_REV_ES1_0;
			cpu_rev = "1.0";
			अवरोध;
		हाल 1:
			omap_revision = OMAP3630_REV_ES1_1;
			cpu_rev = "1.1";
			अवरोध;
		हाल 2:
		शेष:
			omap_revision = OMAP3630_REV_ES1_2;
			cpu_rev = "1.2";
		पूर्ण
		अवरोध;
	हाल 0xb81e:
		चयन (rev) अणु
		हाल 0:
			omap_revision = TI8168_REV_ES1_0;
			cpu_rev = "1.0";
			अवरोध;
		हाल 1:
			omap_revision = TI8168_REV_ES1_1;
			cpu_rev = "1.1";
			अवरोध;
		हाल 2:
			omap_revision = TI8168_REV_ES2_0;
			cpu_rev = "2.0";
			अवरोध;
		हाल 3:
		शेष:
			omap_revision = TI8168_REV_ES2_1;
			cpu_rev = "2.1";
		पूर्ण
		अवरोध;
	हाल 0xb944:
		चयन (rev) अणु
		हाल 0:
			omap_revision = AM335X_REV_ES1_0;
			cpu_rev = "1.0";
			अवरोध;
		हाल 1:
			omap_revision = AM335X_REV_ES2_0;
			cpu_rev = "2.0";
			अवरोध;
		हाल 2:
		शेष:
			omap_revision = AM335X_REV_ES2_1;
			cpu_rev = "2.1";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0xb98c:
		चयन (rev) अणु
		हाल 0:
			omap_revision = AM437X_REV_ES1_0;
			cpu_rev = "1.0";
			अवरोध;
		हाल 1:
			omap_revision = AM437X_REV_ES1_1;
			cpu_rev = "1.1";
			अवरोध;
		हाल 2:
		शेष:
			omap_revision = AM437X_REV_ES1_2;
			cpu_rev = "1.2";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0xb8f2:
	हाल 0xb968:
		चयन (rev) अणु
		हाल 0:
		हाल 1:
			omap_revision = TI8148_REV_ES1_0;
			cpu_rev = "1.0";
			अवरोध;
		हाल 2:
			omap_revision = TI8148_REV_ES2_0;
			cpu_rev = "2.0";
			अवरोध;
		हाल 3:
		शेष:
			omap_revision = TI8148_REV_ES2_1;
			cpu_rev = "2.1";
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		/* Unknown शेष to latest silicon rev as शेष */
		omap_revision = OMAP3630_REV_ES1_2;
		cpu_rev = "1.2";
		pr_warn("Warning: unknown chip type: hawkeye %04x, assuming OMAP3630ES1.2\n",
			hawkeye);
	पूर्ण
	प्र_लिखो(soc_rev, "ES%s", cpu_rev);
पूर्ण

व्योम __init omap4xxx_check_revision(व्योम)
अणु
	u32 idcode;
	u16 hawkeye;
	u8 rev;

	/*
	 * The IC rev detection is करोne with hawkeye and rev.
	 * Note that rev करोes not map directly to defined processor
	 * revision numbers as ES1.0 uses value 0.
	 */
	idcode = पढ़ो_tap_reg(OMAP_TAP_IDCODE);
	hawkeye = (idcode >> 12) & 0xffff;
	rev = (idcode >> 28) & 0xf;

	/*
	 * Few initial 4430 ES2.0 samples IDCODE is same as ES1.0
	 * Use ARM रेजिस्टर to detect the correct ES version
	 */
	अगर (!rev && (hawkeye != 0xb94e) && (hawkeye != 0xb975)) अणु
		idcode = पढ़ो_cpuid_id();
		rev = (idcode & 0xf) - 1;
	पूर्ण

	चयन (hawkeye) अणु
	हाल 0xb852:
		चयन (rev) अणु
		हाल 0:
			omap_revision = OMAP4430_REV_ES1_0;
			अवरोध;
		हाल 1:
		शेष:
			omap_revision = OMAP4430_REV_ES2_0;
		पूर्ण
		अवरोध;
	हाल 0xb95c:
		चयन (rev) अणु
		हाल 3:
			omap_revision = OMAP4430_REV_ES2_1;
			अवरोध;
		हाल 4:
			omap_revision = OMAP4430_REV_ES2_2;
			अवरोध;
		हाल 6:
		शेष:
			omap_revision = OMAP4430_REV_ES2_3;
		पूर्ण
		अवरोध;
	हाल 0xb94e:
		चयन (rev) अणु
		हाल 0:
			omap_revision = OMAP4460_REV_ES1_0;
			अवरोध;
		हाल 2:
		शेष:
			omap_revision = OMAP4460_REV_ES1_1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0xb975:
		चयन (rev) अणु
		हाल 0:
		शेष:
			omap_revision = OMAP4470_REV_ES1_0;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		/* Unknown शेष to latest silicon rev as शेष */
		omap_revision = OMAP4430_REV_ES2_3;
	पूर्ण

	प्र_लिखो(soc_name, "OMAP%04x", omap_rev() >> 16);
	प्र_लिखो(soc_rev, "ES%d.%d", (omap_rev() >> 12) & 0xf,
						(omap_rev() >> 8) & 0xf);
	pr_info("%s %s\n", soc_name, soc_rev);
पूर्ण

व्योम __init omap5xxx_check_revision(व्योम)
अणु
	u32 idcode;
	u16 hawkeye;
	u8 rev;

	idcode = पढ़ो_tap_reg(OMAP_TAP_IDCODE);
	hawkeye = (idcode >> 12) & 0xffff;
	rev = (idcode >> 28) & 0xff;
	चयन (hawkeye) अणु
	हाल 0xb942:
		चयन (rev) अणु
		हाल 0:
			/* No support क्रम ES1.0 Test chip */
			BUG();
		हाल 1:
		शेष:
			omap_revision = OMAP5430_REV_ES2_0;
		पूर्ण
		अवरोध;

	हाल 0xb998:
		चयन (rev) अणु
		हाल 0:
			/* No support क्रम ES1.0 Test chip */
			BUG();
		हाल 1:
		शेष:
			omap_revision = OMAP5432_REV_ES2_0;
		पूर्ण
		अवरोध;

	शेष:
		/* Unknown शेष to latest silicon rev as शेष*/
		omap_revision = OMAP5430_REV_ES2_0;
	पूर्ण

	प्र_लिखो(soc_name, "OMAP%04x", omap_rev() >> 16);
	प्र_लिखो(soc_rev, "ES%d.0", (omap_rev() >> 12) & 0xf);

	pr_info("%s %s\n", soc_name, soc_rev);
पूर्ण

व्योम __init dra7xxx_check_revision(व्योम)
अणु
	u32 idcode;
	u16 hawkeye;
	u8 rev, package;
	काष्ठा omap_die_id odi;

	omap_get_die_id(&odi);
	package = (odi.id_2 >> 16) & 0x3;
	idcode = पढ़ो_tap_reg(OMAP_TAP_IDCODE);
	hawkeye = (idcode >> 12) & 0xffff;
	rev = (idcode >> 28) & 0xff;
	चयन (hawkeye) अणु
	हाल 0xbb50:
		चयन (rev) अणु
		हाल 0:
		शेष:
			चयन (package) अणु
			हाल 0x2:
				omap_revision = DRA762_ABZ_REV_ES1_0;
				अवरोध;
			हाल 0x3:
				omap_revision = DRA762_ACD_REV_ES1_0;
				अवरोध;
			शेष:
				omap_revision = DRA762_REV_ES1_0;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0xb990:
		चयन (rev) अणु
		हाल 0:
			omap_revision = DRA752_REV_ES1_0;
			अवरोध;
		हाल 1:
			omap_revision = DRA752_REV_ES1_1;
			अवरोध;
		हाल 2:
		शेष:
			omap_revision = DRA752_REV_ES2_0;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0xb9bc:
		चयन (rev) अणु
		हाल 0:
			omap_revision = DRA722_REV_ES1_0;
			अवरोध;
		हाल 1:
			omap_revision = DRA722_REV_ES2_0;
			अवरोध;
		हाल 2:
		शेष:
			omap_revision = DRA722_REV_ES2_1;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		/* Unknown शेष to latest silicon rev as शेष*/
		pr_warn("%s: unknown idcode=0x%08x (hawkeye=0x%08x,rev=0x%x)\n",
			__func__, idcode, hawkeye, rev);
		omap_revision = DRA752_REV_ES2_0;
	पूर्ण

	प्र_लिखो(soc_name, "DRA%03x", omap_rev() >> 16);
	प्र_लिखो(soc_rev, "ES%d.%d", (omap_rev() >> 12) & 0xf,
		(omap_rev() >> 8) & 0xf);

	pr_info("%s %s\n", soc_name, soc_rev);
पूर्ण

/*
 * Set up things क्रम map_io and processor detection later on. Gets called
 * pretty much first thing from board init. For multi-omap, this माला_लो
 * cpu_is_omapxxxx() working accurately enough क्रम map_io. Then we'll try to
 * detect the exact revision later on in omap2_detect_revision() once map_io
 * is करोne.
 */
व्योम __init omap2_set_globals_tap(u32 class, व्योम __iomem *tap)
अणु
	omap_revision = class;
	tap_base = tap;

	/* XXX What is this पूर्णांकended to करो? */
	अगर (soc_is_omap34xx())
		tap_prod_id = 0x0210;
	अन्यथा
		tap_prod_id = 0x0208;
पूर्ण

#अगर_घोषित CONFIG_SOC_BUS

अटल स्थिर अक्षर * स्थिर omap_types[] = अणु
	[OMAP2_DEVICE_TYPE_TEST]	= "TST",
	[OMAP2_DEVICE_TYPE_EMU]		= "EMU",
	[OMAP2_DEVICE_TYPE_SEC]		= "HS",
	[OMAP2_DEVICE_TYPE_GP]		= "GP",
	[OMAP2_DEVICE_TYPE_BAD]		= "BAD",
पूर्ण;

अटल स्थिर अक्षर * __init omap_get_family(व्योम)
अणु
	अगर (soc_is_omap24xx())
		वापस kaप्र_लिखो(GFP_KERNEL, "OMAP2");
	अन्यथा अगर (soc_is_omap34xx())
		वापस kaप्र_लिखो(GFP_KERNEL, "OMAP3");
	अन्यथा अगर (soc_is_omap44xx())
		वापस kaप्र_लिखो(GFP_KERNEL, "OMAP4");
	अन्यथा अगर (soc_is_omap54xx())
		वापस kaप्र_लिखो(GFP_KERNEL, "OMAP5");
	अन्यथा अगर (soc_is_am33xx() || soc_is_am335x())
		वापस kaप्र_लिखो(GFP_KERNEL, "AM33xx");
	अन्यथा अगर (soc_is_am43xx())
		वापस kaप्र_लिखो(GFP_KERNEL, "AM43xx");
	अन्यथा अगर (soc_is_dra7xx())
		वापस kaप्र_लिखो(GFP_KERNEL, "DRA7");
	अन्यथा
		वापस kaप्र_लिखो(GFP_KERNEL, "Unknown");
पूर्ण

अटल sमाप_प्रकार
type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", omap_types[omap_type()]);
पूर्ण

अटल DEVICE_ATTR_RO(type);

अटल काष्ठा attribute *omap_soc_attrs[] = अणु
	&dev_attr_type.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(omap_soc);

व्योम __init omap_soc_device_init(व्योम)
अणु
	काष्ठा soc_device *soc_dev;
	काष्ठा soc_device_attribute *soc_dev_attr;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस;

	soc_dev_attr->machine  = soc_name;
	soc_dev_attr->family   = omap_get_family();
	soc_dev_attr->revision = soc_rev;
	soc_dev_attr->custom_attr_group = omap_soc_groups[0];

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr);
		वापस;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SOC_BUS */
