<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of.h>
#समावेश <linux/cache.h>
#समावेश <uapi/linux/mount.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/arcregs.h>
#समावेश <यंत्र/निश्चितs.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/mach_desc.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/dsp-impl.h>

#घोषणा FIX_PTR(x)  __यंत्र__ __अस्थिर__(";" : "+r"(x))

अचिन्हित पूर्णांक पूर्णांकr_to_DE_cnt;

/* Part of U-boot ABI: see head.S */
पूर्णांक __initdata uboot_tag;
पूर्णांक __initdata uboot_magic;
अक्षर __initdata *uboot_arg;

स्थिर काष्ठा machine_desc *machine_desc;

काष्ठा task_काष्ठा *_current_task[NR_CPUS];	/* For stack चयनing */

काष्ठा cpuinfo_arc cpuinfo_arc700[NR_CPUS];

अटल स्थिर काष्ठा id_to_str arc_legacy_rel[] = अणु
	/* ID.ARCVER,	Release */
#अगर_घोषित CONFIG_ISA_ARCOMPACT
	अणु 0x34, 	"R4.10"पूर्ण,
	अणु 0x35, 	"R4.11"पूर्ण,
#अन्यथा
	अणु 0x51, 	"R2.0" पूर्ण,
	अणु 0x52, 	"R2.1" पूर्ण,
	अणु 0x53,		"R3.0" पूर्ण,
#पूर्ण_अगर
	अणु 0x00,		शून्य   पूर्ण
पूर्ण;

अटल स्थिर काष्ठा id_to_str arc_hs_ver54_rel[] = अणु
	/* UARCH.MAJOR,	Release */
	अणु  0,		"R3.10a"पूर्ण,
	अणु  1,		"R3.50a"पूर्ण,
	अणु  2,		"R3.60a"पूर्ण,
	अणु  3,		"R4.00a"पूर्ण,
	अणु  0xFF,	शून्य   पूर्ण
पूर्ण;

अटल व्योम पढ़ो_decode_ccm_bcr(काष्ठा cpuinfo_arc *cpu)
अणु
	अगर (is_isa_arcompact()) अणु
		काष्ठा bcr_iccm_arcompact iccm;
		काष्ठा bcr_dccm_arcompact dccm;

		READ_BCR(ARC_REG_ICCM_BUILD, iccm);
		अगर (iccm.ver) अणु
			cpu->iccm.sz = 4096 << iccm.sz;	/* 8K to 512K */
			cpu->iccm.base_addr = iccm.base << 16;
		पूर्ण

		READ_BCR(ARC_REG_DCCM_BUILD, dccm);
		अगर (dccm.ver) अणु
			अचिन्हित दीर्घ base;
			cpu->dccm.sz = 2048 << dccm.sz;	/* 2K to 256K */

			base = पढ़ो_aux_reg(ARC_REG_DCCM_BASE_BUILD);
			cpu->dccm.base_addr = base & ~0xF;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा bcr_iccm_arcv2 iccm;
		काष्ठा bcr_dccm_arcv2 dccm;
		अचिन्हित दीर्घ region;

		READ_BCR(ARC_REG_ICCM_BUILD, iccm);
		अगर (iccm.ver) अणु
			cpu->iccm.sz = 256 << iccm.sz00;	/* 512B to 16M */
			अगर (iccm.sz00 == 0xF && iccm.sz01 > 0)
				cpu->iccm.sz <<= iccm.sz01;

			region = पढ़ो_aux_reg(ARC_REG_AUX_ICCM);
			cpu->iccm.base_addr = region & 0xF0000000;
		पूर्ण

		READ_BCR(ARC_REG_DCCM_BUILD, dccm);
		अगर (dccm.ver) अणु
			cpu->dccm.sz = 256 << dccm.sz0;
			अगर (dccm.sz0 == 0xF && dccm.sz1 > 0)
				cpu->dccm.sz <<= dccm.sz1;

			region = पढ़ो_aux_reg(ARC_REG_AUX_DCCM);
			cpu->dccm.base_addr = region & 0xF0000000;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम decode_arc_core(काष्ठा cpuinfo_arc *cpu)
अणु
	काष्ठा bcr_uarch_build_arcv2 uarch;
	स्थिर काष्ठा id_to_str *tbl;

	अगर (cpu->core.family < 0x54) अणु /* includes arc700 */

		क्रम (tbl = &arc_legacy_rel[0]; tbl->id != 0; tbl++) अणु
			अगर (cpu->core.family == tbl->id) अणु
				cpu->release = tbl->str;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (is_isa_arcompact())
			cpu->name = "ARC700";
		अन्यथा अगर (tbl->str)
			cpu->name = "HS38";
		अन्यथा
			cpu->name = cpu->release = "Unknown";

		वापस;
	पूर्ण

	/*
	 * Initial HS cores bumped AUX IDENTITY.ARCVER क्रम each release until
	 * ARCVER 0x54 which पूर्णांकroduced AUX MICRO_ARCH_BUILD and subsequent
	 * releases only update it.
	 */
	READ_BCR(ARC_REG_MICRO_ARCH_BCR, uarch);

	अगर (uarch.prod == 4) अणु
		cpu->name = "HS48";
		cpu->extn.dual = 1;

	पूर्ण अन्यथा अणु
		cpu->name = "HS38";
	पूर्ण

	क्रम (tbl = &arc_hs_ver54_rel[0]; tbl->id != 0xFF; tbl++) अणु
		अगर (uarch.maj == tbl->id) अणु
			cpu->release = tbl->str;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_arc_build_cfg_regs(व्योम)
अणु
	काष्ठा bcr_समयr समयr;
	काष्ठा bcr_generic bcr;
	काष्ठा cpuinfo_arc *cpu = &cpuinfo_arc700[smp_processor_id()];
	काष्ठा bcr_isa_arcv2 isa;
	काष्ठा bcr_actionpoपूर्णांक ap;

	FIX_PTR(cpu);

	READ_BCR(AUX_IDENTITY, cpu->core);
	decode_arc_core(cpu);

	READ_BCR(ARC_REG_TIMERS_BCR, समयr);
	cpu->extn.समयr0 = समयr.t0;
	cpu->extn.समयr1 = समयr.t1;
	cpu->extn.rtc = समयr.rtc;

	cpu->vec_base = पढ़ो_aux_reg(AUX_INTR_VEC_BASE);

	READ_BCR(ARC_REG_MUL_BCR, cpu->extn_mpy);

	/* Read CCM BCRs क्रम boot reporting even अगर not enabled in Kconfig */
	पढ़ो_decode_ccm_bcr(cpu);

	पढ़ो_decode_mmu_bcr();
	पढ़ो_decode_cache_bcr();

	अगर (is_isa_arcompact()) अणु
		काष्ठा bcr_fp_arcompact sp, dp;
		काष्ठा bcr_bpu_arcompact bpu;

		READ_BCR(ARC_REG_FP_BCR, sp);
		READ_BCR(ARC_REG_DPFP_BCR, dp);
		cpu->extn.fpu_sp = sp.ver ? 1 : 0;
		cpu->extn.fpu_dp = dp.ver ? 1 : 0;

		READ_BCR(ARC_REG_BPU_BCR, bpu);
		cpu->bpu.ver = bpu.ver;
		cpu->bpu.full = bpu.fam ? 1 : 0;
		अगर (bpu.ent) अणु
			cpu->bpu.num_cache = 256 << (bpu.ent - 1);
			cpu->bpu.num_pred = 256 << (bpu.ent - 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा bcr_fp_arcv2 spdp;
		काष्ठा bcr_bpu_arcv2 bpu;

		READ_BCR(ARC_REG_FP_V2_BCR, spdp);
		cpu->extn.fpu_sp = spdp.sp ? 1 : 0;
		cpu->extn.fpu_dp = spdp.dp ? 1 : 0;

		READ_BCR(ARC_REG_BPU_BCR, bpu);
		cpu->bpu.ver = bpu.ver;
		cpu->bpu.full = bpu.ft;
		cpu->bpu.num_cache = 256 << bpu.bce;
		cpu->bpu.num_pred = 2048 << bpu.pte;
		cpu->bpu.ret_stk = 4 << bpu.rse;

		/* अगर dual issue hardware, is it enabled ? */
		अगर (cpu->extn.dual) अणु
			अचिन्हित पूर्णांक exec_ctrl;

			READ_BCR(AUX_EXEC_CTRL, exec_ctrl);
			cpu->extn.dual_enb = !(exec_ctrl & 1);
		पूर्ण
	पूर्ण

	READ_BCR(ARC_REG_AP_BCR, ap);
	अगर (ap.ver) अणु
		cpu->extn.ap_num = 2 << ap.num;
		cpu->extn.ap_full = !ap.min;
	पूर्ण

	READ_BCR(ARC_REG_SMART_BCR, bcr);
	cpu->extn.smart = bcr.ver ? 1 : 0;

	READ_BCR(ARC_REG_RTT_BCR, bcr);
	cpu->extn.rtt = bcr.ver ? 1 : 0;

	READ_BCR(ARC_REG_ISA_CFG_BCR, isa);

	/* some hacks क्रम lack of feature BCR info in old ARC700 cores */
	अगर (is_isa_arcompact()) अणु
		अगर (!isa.ver)	/* ISA BCR असलent, use Kconfig info */
			cpu->isa.atomic = IS_ENABLED(CONFIG_ARC_HAS_LLSC);
		अन्यथा अणु
			/* ARC700_BUILD only has 2 bits of isa info */
			काष्ठा bcr_generic bcr = *(काष्ठा bcr_generic *)&isa;
			cpu->isa.atomic = bcr.info & 1;
		पूर्ण

		cpu->isa.be = IS_ENABLED(CONFIG_CPU_BIG_ENDIAN);

		 /* there's no direct way to distinguish 750 vs. 770 */
		अगर (unlikely(cpu->core.family < 0x34 || cpu->mmu.ver < 3))
			cpu->name = "ARC750";
	पूर्ण अन्यथा अणु
		cpu->isa = isa;
	पूर्ण
पूर्ण

अटल अक्षर *arc_cpu_mumbojumbo(पूर्णांक cpu_id, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा cpuinfo_arc *cpu = &cpuinfo_arc700[cpu_id];
	काष्ठा bcr_identity *core = &cpu->core;
	अक्षर mpy_opt[16];
	पूर्णांक n = 0;

	FIX_PTR(cpu);

	n += scnम_लिखो(buf + n, len - n,
		       "\nIDENTITY\t: ARCVER [%#02x] ARCNUM [%#02x] CHIPID [%#4x]\n",
		       core->family, core->cpu_id, core->chip_id);

	n += scnम_लिखो(buf + n, len - n, "processor [%d]\t: %s %s (%s ISA) %s%s%s\n",
		       cpu_id, cpu->name, cpu->release,
		       is_isa_arcompact() ? "ARCompact" : "ARCv2",
		       IS_AVAIL1(cpu->isa.be, "[Big-Endian]"),
		       IS_AVAIL3(cpu->extn.dual, cpu->extn.dual_enb, " Dual-Issue "));

	n += scnम_लिखो(buf + n, len - n, "Timers\t\t: %s%s%s%s%s%s\nISA Extn\t: ",
		       IS_AVAIL1(cpu->extn.समयr0, "Timer0 "),
		       IS_AVAIL1(cpu->extn.समयr1, "Timer1 "),
		       IS_AVAIL2(cpu->extn.rtc, "RTC [UP 64-bit] ", CONFIG_ARC_TIMERS_64BIT),
		       IS_AVAIL2(cpu->extn.gfrc, "GFRC [SMP 64-bit] ", CONFIG_ARC_TIMERS_64BIT));

	अगर (cpu->extn_mpy.ver) अणु
		अगर (is_isa_arcompact()) अणु
			scnम_लिखो(mpy_opt, 16, "mpy");
		पूर्ण अन्यथा अणु

			पूर्णांक opt = 2;	/* stock MPY/MPYH */

			अगर (cpu->extn_mpy.dsp)	/* OPT 7-9 */
				opt = cpu->extn_mpy.dsp + 6;

			scnम_लिखो(mpy_opt, 16, "mpy[opt %d] ", opt);
		पूर्ण
	पूर्ण

	n += scnम_लिखो(buf + n, len - n, "%s%s%s%s%s%s%s%s\n",
		       IS_AVAIL2(cpu->isa.atomic, "atomic ", CONFIG_ARC_HAS_LLSC),
		       IS_AVAIL2(cpu->isa.ldd, "ll64 ", CONFIG_ARC_HAS_LL64),
		       IS_AVAIL2(cpu->isa.unalign, "unalign ", CONFIG_ARC_USE_UNALIGNED_MEM_ACCESS),
		       IS_AVAIL1(cpu->extn_mpy.ver, mpy_opt),
		       IS_AVAIL1(cpu->isa.भाग_rem, "div_rem "));

	अगर (cpu->bpu.ver) अणु
		n += scnम_लिखो(buf + n, len - n,
			      "BPU\t\t: %s%s match, cache:%d, Predict Table:%d Return stk: %d",
			      IS_AVAIL1(cpu->bpu.full, "full"),
			      IS_AVAIL1(!cpu->bpu.full, "partial"),
			      cpu->bpu.num_cache, cpu->bpu.num_pred, cpu->bpu.ret_stk);

		अगर (is_isa_arcv2()) अणु
			काष्ठा bcr_lpb lpb;

			READ_BCR(ARC_REG_LPB_BUILD, lpb);
			अगर (lpb.ver) अणु
				अचिन्हित पूर्णांक ctl;
				ctl = पढ़ो_aux_reg(ARC_REG_LPB_CTRL);

				n += scnम_लिखो(buf + n, len - n, " Loop Buffer:%d %s",
					       lpb.entries,
					       IS_DISABLED_RUN(!ctl));
			पूर्ण
		पूर्ण
		n += scnम_लिखो(buf + n, len - n, "\n");
	पूर्ण

	वापस buf;
पूर्ण

अटल अक्षर *arc_extn_mumbojumbo(पूर्णांक cpu_id, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक n = 0;
	काष्ठा cpuinfo_arc *cpu = &cpuinfo_arc700[cpu_id];

	FIX_PTR(cpu);

	n += scnम_लिखो(buf + n, len - n, "Vector Table\t: %#x\n", cpu->vec_base);

	अगर (cpu->extn.fpu_sp || cpu->extn.fpu_dp)
		n += scnम_लिखो(buf + n, len - n, "FPU\t\t: %s%s\n",
			       IS_AVAIL1(cpu->extn.fpu_sp, "SP "),
			       IS_AVAIL1(cpu->extn.fpu_dp, "DP "));

	अगर (cpu->extn.ap_num | cpu->extn.smart | cpu->extn.rtt) अणु
		n += scnम_लिखो(buf + n, len - n, "DEBUG\t\t: %s%s",
			       IS_AVAIL1(cpu->extn.smart, "smaRT "),
			       IS_AVAIL1(cpu->extn.rtt, "RTT "));
		अगर (cpu->extn.ap_num) अणु
			n += scnम_लिखो(buf + n, len - n, "ActionPoint %d/%s",
				       cpu->extn.ap_num,
				       cpu->extn.ap_full ? "full":"min");
		पूर्ण
		n += scnम_लिखो(buf + n, len - n, "\n");
	पूर्ण

	अगर (cpu->dccm.sz || cpu->iccm.sz)
		n += scnम_लिखो(buf + n, len - n, "Extn [CCM]\t: DCCM @ %x, %d KB / ICCM: @ %x, %d KB\n",
			       cpu->dccm.base_addr, TO_KB(cpu->dccm.sz),
			       cpu->iccm.base_addr, TO_KB(cpu->iccm.sz));

	अगर (is_isa_arcv2()) अणु

		/* Error Protection: ECC/Parity */
		काष्ठा bcr_erp erp;
		READ_BCR(ARC_REG_ERP_BUILD, erp);

		अगर (erp.ver) अणु
			काष्ठा  ctl_erp ctl;
			READ_BCR(ARC_REG_ERP_CTRL, ctl);

			/* inverted bits: 0 means enabled */
			n += scnम_लिखो(buf + n, len - n, "Extn [ECC]\t: %s%s%s%s%s%s\n",
				IS_AVAIL3(erp.ic,  !ctl.dpi, "IC "),
				IS_AVAIL3(erp.dc,  !ctl.dpd, "DC "),
				IS_AVAIL3(erp.mmu, !ctl.mpd, "MMU "));
		पूर्ण
	पूर्ण

	वापस buf;
पूर्ण

व्योम chk_opt_strict(अक्षर *opt_name, bool hw_exists, bool opt_ena)
अणु
	अगर (hw_exists && !opt_ena)
		pr_warn(" ! Enable %s for working apps\n", opt_name);
	अन्यथा अगर (!hw_exists && opt_ena)
		panic("Disable %s, hardware NOT present\n", opt_name);
पूर्ण

व्योम chk_opt_weak(अक्षर *opt_name, bool hw_exists, bool opt_ena)
अणु
	अगर (!hw_exists && opt_ena)
		panic("Disable %s, hardware NOT present\n", opt_name);
पूर्ण

अटल व्योम arc_chk_core_config(व्योम)
अणु
	काष्ठा cpuinfo_arc *cpu = &cpuinfo_arc700[smp_processor_id()];
	पूर्णांक present = 0;

	अगर (!cpu->extn.समयr0)
		panic("Timer0 is not present!\n");

	अगर (!cpu->extn.समयr1)
		panic("Timer1 is not present!\n");

#अगर_घोषित CONFIG_ARC_HAS_DCCM
	/*
	 * DCCM can be arbit placed in hardware.
	 * Make sure it's placement/sz matches what Linux is built with
	 */
	अगर ((अचिन्हित पूर्णांक)__arc_dccm_base != cpu->dccm.base_addr)
		panic("Linux built with incorrect DCCM Base address\n");

	अगर (CONFIG_ARC_DCCM_SZ * SZ_1K != cpu->dccm.sz)
		panic("Linux built with incorrect DCCM Size\n");
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARC_HAS_ICCM
	अगर (CONFIG_ARC_ICCM_SZ * SZ_1K != cpu->iccm.sz)
		panic("Linux built with incorrect ICCM Size\n");
#पूर्ण_अगर

	/*
	 * FP hardware/software config sanity
	 * -If hardware present, kernel needs to save/restore FPU state
	 * -If not, it will crash trying to save/restore the non-existant regs
	 */

	अगर (is_isa_arcompact()) अणु
		/* only DPDP checked since SP has no arch visible regs */
		present = cpu->extn.fpu_dp;
		CHK_OPT_STRICT(CONFIG_ARC_FPU_SAVE_RESTORE, present);
	पूर्ण अन्यथा अणु
		/* Accumulator Low:High pair (r58:59) present अगर DSP MPY or FPU */
		present = cpu->extn_mpy.dsp | cpu->extn.fpu_sp | cpu->extn.fpu_dp;
		CHK_OPT_STRICT(CONFIG_ARC_HAS_ACCL_REGS, present);

		dsp_config_check();
	पूर्ण
पूर्ण

/*
 * Initialize and setup the processor core
 * This is called by all the CPUs thus should not करो special हाल stuff
 *    such as only क्रम boot CPU etc
 */

व्योम setup_processor(व्योम)
अणु
	अक्षर str[512];
	पूर्णांक cpu_id = smp_processor_id();

	पढ़ो_arc_build_cfg_regs();
	arc_init_IRQ();

	pr_info("%s", arc_cpu_mumbojumbo(cpu_id, str, माप(str)));

	arc_mmu_init();
	arc_cache_init();

	pr_info("%s", arc_extn_mumbojumbo(cpu_id, str, माप(str)));
	pr_info("%s", arc_platक्रमm_smp_cpuinfo());

	arc_chk_core_config();
पूर्ण

अटल अंतरभूत bool uboot_arg_invalid(अचिन्हित दीर्घ addr)
अणु
	/*
	 * Check that it is a untranslated address (although MMU is not enabled
	 * yet, it being a high address ensures this is not by fluke)
	 */
	अगर (addr < PAGE_OFFSET)
		वापस true;

	/* Check that address करोesn't clobber resident kernel image */
	वापस addr >= (अचिन्हित दीर्घ)_stext && addr <= (अचिन्हित दीर्घ)_end;
पूर्ण

#घोषणा IGNORE_ARGS		"Ignore U-boot args: "

/* uboot_tag values क्रम U-boot - kernel ABI revision 0; see head.S */
#घोषणा UBOOT_TAG_NONE		0
#घोषणा UBOOT_TAG_CMDLINE	1
#घोषणा UBOOT_TAG_DTB		2
/* We always pass 0 as magic from U-boot */
#घोषणा UBOOT_MAGIC_VALUE	0

व्योम __init handle_uboot_args(व्योम)
अणु
	bool use_embedded_dtb = true;
	bool append_cmdline = false;

	/* check that we know this tag */
	अगर (uboot_tag != UBOOT_TAG_NONE &&
	    uboot_tag != UBOOT_TAG_CMDLINE &&
	    uboot_tag != UBOOT_TAG_DTB) अणु
		pr_warn(IGNORE_ARGS "invalid uboot tag: '%08x'\n", uboot_tag);
		जाओ ignore_uboot_args;
	पूर्ण

	अगर (uboot_magic != UBOOT_MAGIC_VALUE) अणु
		pr_warn(IGNORE_ARGS "non zero uboot magic\n");
		जाओ ignore_uboot_args;
	पूर्ण

	अगर (uboot_tag != UBOOT_TAG_NONE &&
            uboot_arg_invalid((अचिन्हित दीर्घ)uboot_arg)) अणु
		pr_warn(IGNORE_ARGS "invalid uboot arg: '%px'\n", uboot_arg);
		जाओ ignore_uboot_args;
	पूर्ण

	/* see अगर U-boot passed an बाह्यal Device Tree blob */
	अगर (uboot_tag == UBOOT_TAG_DTB) अणु
		machine_desc = setup_machine_fdt((व्योम *)uboot_arg);

		/* बाह्यal Device Tree blob is invalid - use embedded one */
		use_embedded_dtb = !machine_desc;
	पूर्ण

	अगर (uboot_tag == UBOOT_TAG_CMDLINE)
		append_cmdline = true;

ignore_uboot_args:

	अगर (use_embedded_dtb) अणु
		machine_desc = setup_machine_fdt(__dtb_start);
		अगर (!machine_desc)
			panic("Embedded DT invalid\n");
	पूर्ण

	/*
	 * NOTE: @boot_command_line is populated by setup_machine_fdt() so this
	 * append processing can only happen after.
	 */
	अगर (append_cmdline) अणु
		/* Ensure a whitespace between the 2 cmdlines */
		strlcat(boot_command_line, " ", COMMAND_LINE_SIZE);
		strlcat(boot_command_line, uboot_arg, COMMAND_LINE_SIZE);
	पूर्ण
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	handle_uboot_args();

	/* Save unparsed command line copy क्रम /proc/cmdline */
	*cmdline_p = boot_command_line;

	/* To क्रमce early parsing of things like mem=xxx */
	parse_early_param();

	/* Platक्रमm/board specअगरic: e.g. early console registration */
	अगर (machine_desc->init_early)
		machine_desc->init_early();

	smp_init_cpus();

	setup_processor();
	setup_arch_memory();

	/* copy flat DT out of .init and then unflatten it */
	unflatten_and_copy_device_tree();

	/* Can be issue अगर someone passes cmd line arg "ro"
	 * But that is unlikely so keeping it as it is
	 */
	root_mountflags &= ~MS_RDONLY;

	arc_unwind_init();
पूर्ण

/*
 * Called from start_kernel() - boot CPU only
 */
व्योम __init समय_init(व्योम)
अणु
	of_clk_init(शून्य);
	समयr_probe();
पूर्ण

अटल पूर्णांक __init customize_machine(व्योम)
अणु
	अगर (machine_desc->init_machine)
		machine_desc->init_machine();

	वापस 0;
पूर्ण
arch_initcall(customize_machine);

अटल पूर्णांक __init init_late_machine(व्योम)
अणु
	अगर (machine_desc->init_late)
		machine_desc->init_late();

	वापस 0;
पूर्ण
late_initcall(init_late_machine);
/*
 *  Get CPU inक्रमmation क्रम use by the procfs.
 */

#घोषणा cpu_to_ptr(c)	((व्योम *)(0xFFFF0000 | (अचिन्हित पूर्णांक)(c)))
#घोषणा ptr_to_cpu(p)	(~0xFFFF0000UL & (अचिन्हित पूर्णांक)(p))

अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	अक्षर *str;
	पूर्णांक cpu_id = ptr_to_cpu(v);
	काष्ठा device *cpu_dev = get_cpu_device(cpu_id);
	काष्ठा clk *cpu_clk;
	अचिन्हित दीर्घ freq = 0;

	अगर (!cpu_online(cpu_id)) अणु
		seq_म_लिखो(m, "processor [%d]\t: Offline\n", cpu_id);
		जाओ करोne;
	पूर्ण

	str = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!str)
		जाओ करोne;

	seq_म_लिखो(m, arc_cpu_mumbojumbo(cpu_id, str, PAGE_SIZE));

	cpu_clk = clk_get(cpu_dev, शून्य);
	अगर (IS_ERR(cpu_clk)) अणु
		seq_म_लिखो(m, "CPU speed \t: Cannot get clock for processor [%d]\n",
			   cpu_id);
	पूर्ण अन्यथा अणु
		freq = clk_get_rate(cpu_clk);
	पूर्ण
	अगर (freq)
		seq_म_लिखो(m, "CPU speed\t: %lu.%02lu Mhz\n",
			   freq / 1000000, (freq / 10000) % 100);

	seq_म_लिखो(m, "Bogo MIPS\t: %lu.%02lu\n",
		   loops_per_jअगरfy / (500000 / HZ),
		   (loops_per_jअगरfy / (5000 / HZ)) % 100);

	seq_म_लिखो(m, arc_mmu_mumbojumbo(cpu_id, str, PAGE_SIZE));
	seq_म_लिखो(m, arc_cache_mumbojumbo(cpu_id, str, PAGE_SIZE));
	seq_म_लिखो(m, arc_extn_mumbojumbo(cpu_id, str, PAGE_SIZE));
	seq_म_लिखो(m, arc_platक्रमm_smp_cpuinfo());

	मुक्त_page((अचिन्हित दीर्घ)str);
करोne:
	seq_म_लिखो(m, "\n");

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	/*
	 * Callback वापसs cpu-id to iterator क्रम show routine, शून्य to stop.
	 * However since शून्य is also a valid cpu-id (0), we use a round-about
	 * way to pass it w/o having to kदो_स्मृति/मुक्त a 2 byte string.
	 * Encode cpu-id as 0xFFcccc, which is decoded by show routine.
	 */
	वापस *pos < nr_cpu_ids ? cpu_to_ptr(*pos) : शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cpu, cpu_topology);

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_present_cpu(cpu)
	    रेजिस्टर_cpu(&per_cpu(cpu_topology, cpu), cpu);

	वापस 0;
पूर्ण

subsys_initcall(topology_init);
