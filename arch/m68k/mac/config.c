<शैली गुरु>
/*
 *  linux/arch/m68k/mac/config.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/*
 * Miscellaneous linux stuff
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/पूर्णांकerrupt.h>
/* keyb */
#समावेश <linux/अक्रमom.h>
#समावेश <linux/delay.h>
/* keyb */
#समावेश <linux/init.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#समावेश <linux/pmu.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bootinfo-mac.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/machdep.h>

#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/machw.h>

#समावेश <यंत्र/mac_iop.h>
#समावेश <यंत्र/mac_via.h>
#समावेश <यंत्र/mac_oss.h>
#समावेश <यंत्र/mac_psc.h>

/* Mac bootinfo काष्ठा */
काष्ठा mac_booter_data mac_bi_data;

/* The phys. video addr. - might be bogus on some machines */
अटल अचिन्हित दीर्घ mac_orig_videoaddr;

बाह्य पूर्णांक mac_hwclk(पूर्णांक, काष्ठा rtc_समय *);
बाह्य व्योम iop_init(व्योम);
बाह्य व्योम via_init(व्योम);
बाह्य व्योम via_init_घड़ी(व्योम);
बाह्य व्योम oss_init(व्योम);
बाह्य व्योम psc_init(व्योम);
बाह्य व्योम baboon_init(व्योम);

बाह्य व्योम mac_mksound(अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

अटल व्योम mac_get_model(अक्षर *str);
अटल व्योम mac_identअगरy(व्योम);
अटल व्योम mac_report_hardware(व्योम);

अटल व्योम __init mac_sched_init(व्योम)
अणु
	via_init_घड़ी();
पूर्ण

/*
 * Parse a Macपूर्णांकosh-specअगरic record in the bootinfo
 */

पूर्णांक __init mac_parse_bootinfo(स्थिर काष्ठा bi_record *record)
अणु
	पूर्णांक unknown = 0;
	स्थिर व्योम *data = record->data;

	चयन (be16_to_cpu(record->tag)) अणु
	हाल BI_MAC_MODEL:
		mac_bi_data.id = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_VADDR:
		mac_bi_data.videoaddr = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_VDEPTH:
		mac_bi_data.videodepth = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_VROW:
		mac_bi_data.videorow = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_VDIM:
		mac_bi_data.dimensions = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_VLOGICAL:
		mac_orig_videoaddr = be32_to_cpup(data);
		mac_bi_data.videological =
			VIDEOMEMBASE + (mac_orig_videoaddr & ~VIDEOMEMMASK);
		अवरोध;
	हाल BI_MAC_SCCBASE:
		mac_bi_data.sccbase = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_BTIME:
		mac_bi_data.bootसमय = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_GMTBIAS:
		mac_bi_data.gmtbias = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_MEMSIZE:
		mac_bi_data.memsize = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_CPUID:
		mac_bi_data.cpuid = be32_to_cpup(data);
		अवरोध;
	हाल BI_MAC_ROMBASE:
		mac_bi_data.rombase = be32_to_cpup(data);
		अवरोध;
	शेष:
		unknown = 1;
		अवरोध;
	पूर्ण
	वापस unknown;
पूर्ण

व्योम __init config_mac(व्योम)
अणु
	अगर (!MACH_IS_MAC)
		pr_err("ERROR: no Mac, but config_mac() called!!\n");

	mach_sched_init = mac_sched_init;
	mach_init_IRQ = mac_init_IRQ;
	mach_get_model = mac_get_model;
	mach_hwclk = mac_hwclk;
	mach_reset = mac_reset;
	mach_halt = mac_घातeroff;
	mach_घातer_off = mac_घातeroff;
#अगर IS_ENABLED(CONFIG_INPUT_M68K_BEEP)
	mach_beep = mac_mksound;
#पूर्ण_अगर

	/*
	 * Determine hardware present
	 */

	mac_identअगरy();
	mac_report_hardware();

	/*
	 * AFAIK only the IIci takes a cache card.  The IIfx has onboard
	 * cache ... someone needs to figure out how to tell अगर it's on or
	 * not.
	 */

	अगर (macपूर्णांकosh_config->ident == MAC_MODEL_IICI)
		mach_l2_flush = via_l2_flush;
पूर्ण


/*
 * Macपूर्णांकosh Table: hardcoded model configuration data.
 *
 * Much of this was defined by Alan, based on who knows what करोcs.
 * I've added a lot more, and some of that was pure guesswork based
 * on hardware pages present on the Mac web site. Possibly wildly
 * inaccurate, so look here अगर a new Mac model won't run. Example: अगर
 * a Mac crashes immediately after the VIA1 रेजिस्टरs have been dumped
 * to the screen, it probably died attempting to पढ़ो DirB on a RBV.
 * Meaning it should have MAC_VIA_IICI here :-)
 */

काष्ठा mac_model *macपूर्णांकosh_config;
EXPORT_SYMBOL(macपूर्णांकosh_config);

अटल काष्ठा mac_model mac_data_table[] = अणु
	/*
	 * We'll pretend to be a Macintosh II, that's pretty safe.
	 */

	अणु
		.ident		= MAC_MODEL_II,
		.name		= "Unknown",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_UNSUPPORTED, /* IWM */
	पूर्ण,

	/*
	 * Original Mac II hardware
	 */

	अणु
		.ident		= MAC_MODEL_II,
		.name		= "II",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_UNSUPPORTED, /* IWM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_IIX,
		.name		= "IIx",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_IICX,
		.name		= "IIcx",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_SE30,
		.name		= "SE/30",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण,

	/*
	 * Weirdअगरied Mac II hardware - all subtly dअगरferent. Gee thanks
	 * Apple. All these boxes seem to have VIA2 in a dअगरferent place to
	 * the Mac II (+1A000 rather than +4000)
	 * CSA: see http://developer.apple.com/technotes/hw/hw_09.hपंचांगl
	 */

	अणु
		.ident		= MAC_MODEL_IICI,
		.name		= "IIci",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_IIFX,
		.name		= "IIfx",
		.adb_type	= MAC_ADB_IOP,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_IIFX,
		.scc_type	= MAC_SCC_IOP,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_SWIM_IOP, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_IISI,
		.name		= "IIsi",
		.adb_type	= MAC_ADB_EGRET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_IIVI,
		.name		= "IIvi",
		.adb_type	= MAC_ADB_EGRET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_IIVX,
		.name		= "IIvx",
		.adb_type	= MAC_ADB_EGRET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM */
	पूर्ण,

	/*
	 * Classic models (guessing: similar to SE/30? Nope, similar to LC...)
	 */

	अणु
		.ident		= MAC_MODEL_CLII,
		.name		= "Classic II",
		.adb_type	= MAC_ADB_EGRET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_CCL,
		.name		= "Color Classic",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_CCLII,
		.name		= "Color Classic II",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM 2 */
	पूर्ण,

	/*
	 * Some Mac LC machines. Basically the same as the IIci, ADB like IIsi
	 */

	अणु
		.ident		= MAC_MODEL_LC,
		.name		= "LC",
		.adb_type	= MAC_ADB_EGRET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_LCII,
		.name		= "LC II",
		.adb_type	= MAC_ADB_EGRET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_LCIII,
		.name		= "LC III",
		.adb_type	= MAC_ADB_EGRET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM 2 */
	पूर्ण,

	/*
	 * Quadra. Video is at 0xF9000000, via is like a MacII. We label it
	 * dअगरferently as some of the stuff connected to VIA2 seems dअगरferent.
	 * Better SCSI chip and onboard ethernet using a NatSemi SONIC except
	 * the 660AV and 840AV which use an AMD 79C940 (MACE).
	 * The 700, 900 and 950 have some I/O chips in the wrong place to
	 * confuse us. The 840AV has a SCSI location of its own (same as
	 * the 660AV).
	 */

	अणु
		.ident		= MAC_MODEL_Q605,
		.name		= "Quadra 605",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_QUADRA,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_Q605_ACC,
		.name		= "Quadra 605",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_QUADRA,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_Q610,
		.name		= "Quadra 610",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_QUADRA,
		.ether_type	= MAC_ETHER_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_Q630,
		.name		= "Quadra 630",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.ide_type	= MAC_IDE_QUADRA,
		.scc_type	= MAC_SCC_QUADRA,
		.expansion_type	= MAC_EXP_PDS_COMM,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_Q650,
		.name		= "Quadra 650",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_QUADRA,
		.ether_type	= MAC_ETHER_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण,
	/* The Q700 करोes have a NS Sonic */
	अणु
		.ident		= MAC_MODEL_Q700,
		.name		= "Quadra 700",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA2,
		.scc_type	= MAC_SCC_QUADRA,
		.ether_type	= MAC_ETHER_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_Q800,
		.name		= "Quadra 800",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_QUADRA,
		.ether_type	= MAC_ETHER_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_Q840,
		.name		= "Quadra 840AV",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA3,
		.scc_type	= MAC_SCC_PSC,
		.ether_type	= MAC_ETHER_MACE,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_UNSUPPORTED, /* New Age */
	पूर्ण, अणु
		.ident		= MAC_MODEL_Q900,
		.name		= "Quadra 900",
		.adb_type	= MAC_ADB_IOP,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA2,
		.scc_type	= MAC_SCC_IOP,
		.ether_type	= MAC_ETHER_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_SWIM_IOP, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_Q950,
		.name		= "Quadra 950",
		.adb_type	= MAC_ADB_IOP,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA2,
		.scc_type	= MAC_SCC_IOP,
		.ether_type	= MAC_ETHER_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_SWIM_IOP, /* SWIM */
	पूर्ण,

	/*
	 * Perक्रमma - more LC type machines
	 */

	अणु
		.ident		= MAC_MODEL_P460,
		.name		= "Performa 460",
		.adb_type	= MAC_ADB_EGRET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_P475,
		.name		= "Performa 475",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_P475F,
		.name		= "Performa 475",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_P520,
		.name		= "Performa 520",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_P550,
		.name		= "Performa 550",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM 2 */
	पूर्ण,
	/* These have the comm slot, and thereक्रमe possibly SONIC ethernet */
	अणु
		.ident		= MAC_MODEL_P575,
		.name		= "Performa 575",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS_COMM,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_P588,
		.name		= "Performa 588",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.ide_type	= MAC_IDE_QUADRA,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS_COMM,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_TV,
		.name		= "TV",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_P600,
		.name		= "Performa 600",
		.adb_type	= MAC_ADB_EGRET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_LC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_LC, /* SWIM */
	पूर्ण,

	/*
	 * Centris - just guessing again; maybe like Quadra.
	 * The C610 may or may not have SONIC. We probe to make sure.
	 */

	अणु
		.ident		= MAC_MODEL_C610,
		.name		= "Centris 610",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_QUADRA,
		.ether_type	= MAC_ETHER_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_C650,
		.name		= "Centris 650",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA,
		.scc_type	= MAC_SCC_QUADRA,
		.ether_type	= MAC_ETHER_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_QUADRA, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_C660,
		.name		= "Centris 660AV",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_QUADRA3,
		.scc_type	= MAC_SCC_PSC,
		.ether_type	= MAC_ETHER_MACE,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.floppy_type	= MAC_FLOPPY_UNSUPPORTED, /* New Age */
	पूर्ण,

	/*
	 * The PowerBooks all the same "Combo" custom IC क्रम SCSI and SCC
	 * and a PMU (in two variations?) क्रम ADB. Most of them use the
	 * Quadra-style VIAs. A few models also have IDE from hell.
	 */

	अणु
		.ident		= MAC_MODEL_PB140,
		.name		= "PowerBook 140",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB145,
		.name		= "PowerBook 145",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB150,
		.name		= "PowerBook 150",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_OLD,
		.ide_type	= MAC_IDE_PB,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB160,
		.name		= "PowerBook 160",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB165,
		.name		= "PowerBook 165",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB165C,
		.name		= "PowerBook 165c",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB170,
		.name		= "PowerBook 170",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB180,
		.name		= "PowerBook 180",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB180C,
		.name		= "PowerBook 180c",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB190,
		.name		= "PowerBook 190",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.ide_type	= MAC_IDE_BABOON,
		.scc_type	= MAC_SCC_QUADRA,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM 2 */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB520,
		.name		= "PowerBook 520",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_QUADRA,
		.scsi_type	= MAC_SCSI_OLD,
		.scc_type	= MAC_SCC_QUADRA,
		.ether_type	= MAC_ETHER_SONIC,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM 2 */
	पूर्ण,

	/*
	 * PowerBook Duos are pretty much like normal PowerBooks
	 * All of these probably have onboard SONIC in the Dock which
	 * means we'll have to probe क्रम it eventually.
	 */

	अणु
		.ident		= MAC_MODEL_PB210,
		.name		= "PowerBook Duo 210",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADRA,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB230,
		.name		= "PowerBook Duo 230",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADRA,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB250,
		.name		= "PowerBook Duo 250",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADRA,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB270C,
		.name		= "PowerBook Duo 270c",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADRA,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB280,
		.name		= "PowerBook Duo 280",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADRA,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण, अणु
		.ident		= MAC_MODEL_PB280C,
		.name		= "PowerBook Duo 280c",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADRA,
		.expansion_type	= MAC_EXP_NUBUS,
		.floppy_type	= MAC_FLOPPY_OLD, /* SWIM */
	पूर्ण,

	/*
	 * Other stuff?
	 */

	अणु
		.ident		= -1
	पूर्ण
पूर्ण;

अटल काष्ठा resource scc_a_rsrcs[] = अणु
	अणु .flags = IORESOURCE_MEM पूर्ण,
	अणु .flags = IORESOURCE_IRQ पूर्ण,
पूर्ण;

अटल काष्ठा resource scc_b_rsrcs[] = अणु
	अणु .flags = IORESOURCE_MEM पूर्ण,
	अणु .flags = IORESOURCE_IRQ पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device scc_a_pdev = अणु
	.name           = "scc",
	.id             = 0,
पूर्ण;
EXPORT_SYMBOL(scc_a_pdev);

काष्ठा platक्रमm_device scc_b_pdev = अणु
	.name           = "scc",
	.id             = 1,
पूर्ण;
EXPORT_SYMBOL(scc_b_pdev);

अटल व्योम __init mac_identअगरy(व्योम)
अणु
	काष्ठा mac_model *m;

	/* Penguin data useful? */
	पूर्णांक model = mac_bi_data.id;
	अगर (!model) अणु
		/* no bootinfo model id -> NetBSD booter was used! */
		/* XXX FIXME: अवरोधs क्रम model > 31 */
		model = (mac_bi_data.cpuid >> 2) & 63;
		pr_warn("No bootinfo model ID, using cpuid instead (obsolete bootloader?)\n");
	पूर्ण

	macपूर्णांकosh_config = mac_data_table;
	क्रम (m = macपूर्णांकosh_config; m->ident != -1; m++) अणु
		अगर (m->ident == model) अणु
			macपूर्णांकosh_config = m;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Set up serial port resources क्रम the console initcall. */

	scc_a_rsrcs[0].start     = (resource_माप_प्रकार)mac_bi_data.sccbase + 2;
	scc_a_rsrcs[0].end       = scc_a_rsrcs[0].start;
	scc_a_pdev.num_resources = ARRAY_SIZE(scc_a_rsrcs);
	scc_a_pdev.resource      = scc_a_rsrcs;

	scc_b_rsrcs[0].start     = (resource_माप_प्रकार)mac_bi_data.sccbase;
	scc_b_rsrcs[0].end       = scc_b_rsrcs[0].start;
	scc_b_pdev.num_resources = ARRAY_SIZE(scc_b_rsrcs);
	scc_b_pdev.resource      = scc_b_rsrcs;

	चयन (macपूर्णांकosh_config->scc_type) अणु
	हाल MAC_SCC_PSC:
		scc_a_rsrcs[1].start = scc_a_rsrcs[1].end = IRQ_MAC_SCC_A;
		scc_b_rsrcs[1].start = scc_b_rsrcs[1].end = IRQ_MAC_SCC_B;
		अवरोध;
	शेष:
		/* On non-PSC machines, the serial ports share an IRQ. */
		अगर (macपूर्णांकosh_config->ident == MAC_MODEL_IIFX) अणु
			scc_a_rsrcs[1].start = scc_a_rsrcs[1].end = IRQ_MAC_SCC;
			scc_b_rsrcs[1].start = scc_b_rsrcs[1].end = IRQ_MAC_SCC;
		पूर्ण अन्यथा अणु
			scc_a_rsrcs[1].start = scc_a_rsrcs[1].end = IRQ_AUTO_4;
			scc_b_rsrcs[1].start = scc_b_rsrcs[1].end = IRQ_AUTO_4;
		पूर्ण
		अवरोध;
	पूर्ण

	pr_info("Detected Macintosh model: %d\n", model);

	/*
	 * Report booter data:
	 */
	prपूर्णांकk(KERN_DEBUG " Penguin bootinfo data:\n");
	prपूर्णांकk(KERN_DEBUG " Video: addr 0x%lx row 0x%lx depth %lx dimensions %ld x %ld\n",
		mac_bi_data.videoaddr, mac_bi_data.videorow,
		mac_bi_data.videodepth, mac_bi_data.dimensions & 0xFFFF,
		mac_bi_data.dimensions >> 16);
	prपूर्णांकk(KERN_DEBUG " Videological 0x%lx phys. 0x%lx, SCC at 0x%lx\n",
		mac_bi_data.videological, mac_orig_videoaddr,
		mac_bi_data.sccbase);
	prपूर्णांकk(KERN_DEBUG " Boottime: 0x%lx GMTBias: 0x%lx\n",
		mac_bi_data.bootसमय, mac_bi_data.gmtbias);
	prपूर्णांकk(KERN_DEBUG " Machine ID: %ld CPUid: 0x%lx memory size: 0x%lx\n",
		mac_bi_data.id, mac_bi_data.cpuid, mac_bi_data.memsize);

	iop_init();
	oss_init();
	via_init();
	psc_init();
	baboon_init();

#अगर_घोषित CONFIG_ADB_CUDA
	find_via_cuda();
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
	find_via_pmu();
#पूर्ण_अगर
पूर्ण

अटल व्योम __init mac_report_hardware(व्योम)
अणु
	pr_info("Apple Macintosh %s\n", macपूर्णांकosh_config->name);
पूर्ण

अटल व्योम mac_get_model(अक्षर *str)
अणु
	म_नकल(str, "Macintosh ");
	म_जोड़ो(str, macपूर्णांकosh_config->name);
पूर्ण

अटल स्थिर काष्ठा resource mac_scsi_iअगरx_rsrc[] __initस्थिर = अणु
	अणु
		.flags = IORESOURCE_IRQ,
		.start = IRQ_MAC_SCSI,
		.end   = IRQ_MAC_SCSI,
	पूर्ण, अणु
		.flags = IORESOURCE_MEM,
		.start = 0x50008000,
		.end   = 0x50009FFF,
	पूर्ण, अणु
		.flags = IORESOURCE_MEM,
		.start = 0x50008000,
		.end   = 0x50009FFF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource mac_scsi_duo_rsrc[] __initस्थिर = अणु
	अणु
		.flags = IORESOURCE_MEM,
		.start = 0xFEE02000,
		.end   = 0xFEE03FFF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource mac_scsi_old_rsrc[] __initस्थिर = अणु
	अणु
		.flags = IORESOURCE_IRQ,
		.start = IRQ_MAC_SCSI,
		.end   = IRQ_MAC_SCSI,
	पूर्ण, अणु
		.flags = IORESOURCE_MEM,
		.start = 0x50010000,
		.end   = 0x50011FFF,
	पूर्ण, अणु
		.flags = IORESOURCE_MEM,
		.start = 0x50006000,
		.end   = 0x50007FFF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource mac_scsi_ccl_rsrc[] __initस्थिर = अणु
	अणु
		.flags = IORESOURCE_IRQ,
		.start = IRQ_MAC_SCSI,
		.end   = IRQ_MAC_SCSI,
	पूर्ण, अणु
		.flags = IORESOURCE_MEM,
		.start = 0x50F10000,
		.end   = 0x50F11FFF,
	पूर्ण, अणु
		.flags = IORESOURCE_MEM,
		.start = 0x50F06000,
		.end   = 0x50F07FFF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource mac_ide_quadra_rsrc[] __initस्थिर = अणु
	DEFINE_RES_MEM(0x50F1A000, 0x104),
	DEFINE_RES_IRQ(IRQ_NUBUS_F),
पूर्ण;

अटल स्थिर काष्ठा resource mac_ide_pb_rsrc[] __initस्थिर = अणु
	DEFINE_RES_MEM(0x50F1A000, 0x104),
	DEFINE_RES_IRQ(IRQ_NUBUS_C),
पूर्ण;

अटल स्थिर काष्ठा resource mac_pata_baboon_rsrc[] __initस्थिर = अणु
	DEFINE_RES_MEM(0x50F1A000, 0x38),
	DEFINE_RES_MEM(0x50F1A038, 0x04),
	DEFINE_RES_IRQ(IRQ_BABOON_1),
पूर्ण;

अटल स्थिर काष्ठा pata_platक्रमm_info mac_pata_baboon_data __initस्थिर = अणु
	.ioport_shअगरt = 2,
पूर्ण;

पूर्णांक __init mac_platक्रमm_init(व्योम)
अणु
	phys_addr_t swim_base = 0;

	अगर (!MACH_IS_MAC)
		वापस -ENODEV;

	/*
	 * Serial devices
	 */

	platक्रमm_device_रेजिस्टर(&scc_a_pdev);
	platक्रमm_device_रेजिस्टर(&scc_b_pdev);

	/*
	 * Floppy device
	 */

	चयन (macपूर्णांकosh_config->floppy_type) अणु
	हाल MAC_FLOPPY_QUADRA:
		swim_base = 0x5001E000;
		अवरोध;
	हाल MAC_FLOPPY_OLD:
		swim_base = 0x50016000;
		अवरोध;
	हाल MAC_FLOPPY_LC:
		swim_base = 0x50F16000;
		अवरोध;
	पूर्ण

	अगर (swim_base) अणु
		काष्ठा resource swim_rsrc = अणु
			.flags = IORESOURCE_MEM,
			.start = swim_base,
			.end   = swim_base + 0x1FFF,
		पूर्ण;

		platक्रमm_device_रेजिस्टर_simple("swim", -1, &swim_rsrc, 1);
	पूर्ण

	/*
	 * SCSI device(s)
	 */

	चयन (macपूर्णांकosh_config->scsi_type) अणु
	हाल MAC_SCSI_QUADRA:
	हाल MAC_SCSI_QUADRA3:
		platक्रमm_device_रेजिस्टर_simple("mac_esp", 0, शून्य, 0);
		अवरोध;
	हाल MAC_SCSI_QUADRA2:
		platक्रमm_device_रेजिस्टर_simple("mac_esp", 0, शून्य, 0);
		अगर ((macपूर्णांकosh_config->ident == MAC_MODEL_Q900) ||
		    (macपूर्णांकosh_config->ident == MAC_MODEL_Q950))
			platक्रमm_device_रेजिस्टर_simple("mac_esp", 1, शून्य, 0);
		अवरोध;
	हाल MAC_SCSI_IIFX:
		/* Addresses from The Guide to Mac Family Hardware.
		 * $5000 8000 - $5000 9FFF: SCSI DMA
		 * $5000 A000 - $5000 BFFF: Alternate SCSI
		 * $5000 C000 - $5000 DFFF: Alternate SCSI (DMA)
		 * $5000 E000 - $5000 FFFF: Alternate SCSI (Hsk)
		 * The A/UX header file sys/uconfig.h says $50F0 8000.
		 * The "SCSI DMA" custom IC embeds the 53C80 core and
		 * supports Programmed IO, DMA and PDMA (hardware handshake).
		 */
		platक्रमm_device_रेजिस्टर_simple("mac_scsi", 0,
			mac_scsi_iअगरx_rsrc, ARRAY_SIZE(mac_scsi_iअगरx_rsrc));
		अवरोध;
	हाल MAC_SCSI_DUO:
		/* Addresses from the Duo Dock II Developer Note.
		 * $FEE0 2000 - $FEE0 3FFF: normal mode
		 * $FEE0 4000 - $FEE0 5FFF: pseuकरो DMA without /DRQ
		 * $FEE0 6000 - $FEE0 7FFF: pseuकरो DMA with /DRQ
		 * The NetBSD code indicates that both 5380 chips share
		 * an IRQ (?) which would need careful handling (see mac_esp).
		 */
		platक्रमm_device_रेजिस्टर_simple("mac_scsi", 1,
			mac_scsi_duo_rsrc, ARRAY_SIZE(mac_scsi_duo_rsrc));
		fallthrough;
	हाल MAC_SCSI_OLD:
		/* Addresses from Developer Notes क्रम Duo System,
		 * PowerBook 180 & 160, 140 & 170, Macपूर्णांकosh IIsi
		 * and also from The Guide to Mac Family Hardware क्रम
		 * SE/30, II, IIx, IIcx, IIci.
		 * $5000 6000 - $5000 7FFF: pseuकरो-DMA with /DRQ
		 * $5001 0000 - $5001 1FFF: normal mode
		 * $5001 2000 - $5001 3FFF: pseuकरो-DMA without /DRQ
		 * GMFH says that $5000 0000 - $50FF FFFF "wraps
		 * $5000 0000 - $5001 FFFF eight बार" (!)
		 * mess.org says IIci and Color Classic करो not alias
		 * I/O address space.
		 */
		platक्रमm_device_रेजिस्टर_simple("mac_scsi", 0,
			mac_scsi_old_rsrc, ARRAY_SIZE(mac_scsi_old_rsrc));
		अवरोध;
	हाल MAC_SCSI_LC:
		/* Addresses from Mac LC data in Designing Cards & Drivers 3ed.
		 * Also from the Developer Notes क्रम Classic II, LC III,
		 * Color Classic and IIvx.
		 * $50F0 6000 - $50F0 7FFF: SCSI handshake
		 * $50F1 0000 - $50F1 1FFF: SCSI
		 * $50F1 2000 - $50F1 3FFF: SCSI DMA
		 */
		platक्रमm_device_रेजिस्टर_simple("mac_scsi", 0,
			mac_scsi_ccl_rsrc, ARRAY_SIZE(mac_scsi_ccl_rsrc));
		अवरोध;
	पूर्ण

	/*
	 * IDE device
	 */

	चयन (macपूर्णांकosh_config->ide_type) अणु
	हाल MAC_IDE_QUADRA:
		platक्रमm_device_रेजिस्टर_simple("mac_ide", -1,
			mac_ide_quadra_rsrc, ARRAY_SIZE(mac_ide_quadra_rsrc));
		अवरोध;
	हाल MAC_IDE_PB:
		platक्रमm_device_रेजिस्टर_simple("mac_ide", -1,
			mac_ide_pb_rsrc, ARRAY_SIZE(mac_ide_pb_rsrc));
		अवरोध;
	हाल MAC_IDE_BABOON:
		platक्रमm_device_रेजिस्टर_resndata(शून्य, "pata_platform", -1,
			mac_pata_baboon_rsrc, ARRAY_SIZE(mac_pata_baboon_rsrc),
			&mac_pata_baboon_data, माप(mac_pata_baboon_data));
		अवरोध;
	पूर्ण

	/*
	 * Ethernet device
	 */

	अगर (macपूर्णांकosh_config->ether_type == MAC_ETHER_SONIC ||
	    macपूर्णांकosh_config->expansion_type == MAC_EXP_PDS_COMM)
		platक्रमm_device_रेजिस्टर_simple("macsonic", -1, शून्य, 0);

	अगर (macपूर्णांकosh_config->expansion_type == MAC_EXP_PDS ||
	    macपूर्णांकosh_config->expansion_type == MAC_EXP_PDS_COMM)
		platक्रमm_device_रेजिस्टर_simple("mac89x0", -1, शून्य, 0);

	अगर (macपूर्णांकosh_config->ether_type == MAC_ETHER_MACE)
		platक्रमm_device_रेजिस्टर_simple("macmace", -1, शून्य, 0);

	वापस 0;
पूर्ण

arch_initcall(mac_platक्रमm_init);
