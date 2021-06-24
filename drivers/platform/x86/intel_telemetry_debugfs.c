<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel SOC Telemetry debugfs Driver: Currently supports APL
 * Copyright (c) 2015, Intel Corporation.
 * All Rights Reserved.
 *
 * This file provides the debugfs पूर्णांकerfaces क्रम telemetry.
 * /sys/kernel/debug/telemetry/pss_info: Shows Primary Control Sub-Sys Counters
 * /sys/kernel/debug/telemetry/ioss_info: Shows IO Sub-System Counters
 * /sys/kernel/debug/telemetry/soc_states: Shows SoC State
 * /sys/kernel/debug/telemetry/pss_trace_verbosity: Read and Change Tracing
 *				Verbosity via firmware
 * /sys/kernel/debug/telemetry/ioss_race_verbosity: Write and Change Tracing
 *				Verbosity via firmware
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/mfd/पूर्णांकel_pmc_bxt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/suspend.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/पूर्णांकel_telemetry.h>

#घोषणा DRIVER_NAME			"telemetry_soc_debugfs"
#घोषणा DRIVER_VERSION			"1.0.0"

/* ApolloLake SoC Event-IDs */
#घोषणा TELEM_APL_PSS_PSTATES_ID	0x2802
#घोषणा TELEM_APL_PSS_IDLE_ID		0x2806
#घोषणा TELEM_APL_PCS_IDLE_BLOCKED_ID	0x2C00
#घोषणा TELEM_APL_PCS_S0IX_BLOCKED_ID	0x2C01
#घोषणा TELEM_APL_PSS_WAKEUP_ID		0x2C02
#घोषणा TELEM_APL_PSS_LTR_BLOCKING_ID	0x2C03

#घोषणा TELEM_APL_S0IX_TOTAL_OCC_ID	0x4000
#घोषणा TELEM_APL_S0IX_SHLW_OCC_ID	0x4001
#घोषणा TELEM_APL_S0IX_DEEP_OCC_ID	0x4002
#घोषणा TELEM_APL_S0IX_TOTAL_RES_ID	0x4800
#घोषणा TELEM_APL_S0IX_SHLW_RES_ID	0x4801
#घोषणा TELEM_APL_S0IX_DEEP_RES_ID	0x4802
#घोषणा TELEM_APL_D0IX_ID		0x581A
#घोषणा TELEM_APL_D3_ID			0x5819
#घोषणा TELEM_APL_PG_ID			0x5818

#घोषणा TELEM_INFO_SRAMEVTS_MASK	0xFF00
#घोषणा TELEM_INFO_SRAMEVTS_SHIFT	0x8
#घोषणा TELEM_SSRAM_READ_TIMEOUT	10

#घोषणा TELEM_MASK_BIT			1
#घोषणा TELEM_MASK_BYTE			0xFF
#घोषणा BYTES_PER_LONG			8
#घोषणा TELEM_APL_MASK_PCS_STATE	0xF

/* Max events in biपंचांगap to check क्रम */
#घोषणा TELEM_PSS_IDLE_EVTS		25
#घोषणा TELEM_PSS_IDLE_BLOCKED_EVTS	20
#घोषणा TELEM_PSS_S0IX_BLOCKED_EVTS	20
#घोषणा TELEM_PSS_S0IX_WAKEUP_EVTS	20
#घोषणा TELEM_PSS_LTR_BLOCKING_EVTS	20
#घोषणा TELEM_IOSS_DX_D0IX_EVTS		25
#घोषणा TELEM_IOSS_PG_EVTS		30

#घोषणा TELEM_CHECK_AND_PARSE_EVTS(EVTID, EVTNUM, BUF, EVTLOG, EVTDAT, MASK) अणु \
	अगर (evtlog[index].telem_evtid == (EVTID)) अणु \
		क्रम (idx = 0; idx < (EVTNUM); idx++) \
			(BUF)[idx] = ((EVTLOG) >> (EVTDAT)[idx].bit_pos) & \
				     (MASK); \
	जारी; \
	पूर्ण \
पूर्ण

#घोषणा TELEM_CHECK_AND_PARSE_CTRS(EVTID, CTR) अणु \
	अगर (evtlog[index].telem_evtid == (EVTID)) अणु \
		(CTR) = evtlog[index].telem_evtlog; \
		जारी; \
	पूर्ण \
पूर्ण

अटल u8 suspend_prep_ok;
अटल u32 suspend_shlw_ctr_temp, suspend_deep_ctr_temp;
अटल u64 suspend_shlw_res_temp, suspend_deep_res_temp;

काष्ठा telemetry_susp_stats अणु
	u32 shlw_ctr;
	u32 deep_ctr;
	u64 shlw_res;
	u64 deep_res;
पूर्ण;

/* Biपंचांगap definitions क्रम शेष counters in APL */
काष्ठा telem_pss_idle_stateinfo अणु
	स्थिर अक्षर *name;
	u32 bit_pos;
पूर्ण;

अटल काष्ठा telem_pss_idle_stateinfo telem_apl_pss_idle_data[] = अणु
	अणु"IA_CORE0_C1E",		0पूर्ण,
	अणु"IA_CORE1_C1E",		1पूर्ण,
	अणु"IA_CORE2_C1E",		2पूर्ण,
	अणु"IA_CORE3_C1E",		3पूर्ण,
	अणु"IA_CORE0_C6",			16पूर्ण,
	अणु"IA_CORE1_C6",			17पूर्ण,
	अणु"IA_CORE2_C6",			18पूर्ण,
	अणु"IA_CORE3_C6",			19पूर्ण,
	अणु"IA_MODULE0_C7",		32पूर्ण,
	अणु"IA_MODULE1_C7",		33पूर्ण,
	अणु"GT_RC6",			40पूर्ण,
	अणु"IUNIT_PROCESSING_IDLE",	41पूर्ण,
	अणु"FAR_MEM_IDLE",		43पूर्ण,
	अणु"DISPLAY_IDLE",		44पूर्ण,
	अणु"IUNIT_INPUT_SYSTEM_IDLE",	45पूर्ण,
	अणु"PCS_STATUS",			60पूर्ण,
पूर्ण;

काष्ठा telem_pcs_blkd_info अणु
	स्थिर अक्षर *name;
	u32 bit_pos;
पूर्ण;

अटल काष्ठा telem_pcs_blkd_info telem_apl_pcs_idle_blkd_data[] = अणु
	अणु"COMPUTE",			0पूर्ण,
	अणु"MISC",			8पूर्ण,
	अणु"MODULE_ACTIONS_PENDING",	16पूर्ण,
	अणु"LTR",				24पूर्ण,
	अणु"DISPLAY_WAKE",		32पूर्ण,
	अणु"ISP_WAKE",			40पूर्ण,
	अणु"PSF0_ACTIVE",			48पूर्ण,
पूर्ण;

अटल काष्ठा telem_pcs_blkd_info telem_apl_pcs_s0ix_blkd_data[] = अणु
	अणु"LTR",				0पूर्ण,
	अणु"IRTL",			8पूर्ण,
	अणु"WAKE_DEADLINE_PENDING",	16पूर्ण,
	अणु"DISPLAY",			24पूर्ण,
	अणु"ISP",				32पूर्ण,
	अणु"CORE",			40पूर्ण,
	अणु"PMC",				48पूर्ण,
	अणु"MISC",			56पूर्ण,
पूर्ण;

काष्ठा telem_pss_ltr_info अणु
	स्थिर अक्षर *name;
	u32 bit_pos;
पूर्ण;

अटल काष्ठा telem_pss_ltr_info telem_apl_pss_ltr_data[] = अणु
	अणु"CORE_ACTIVE",		0पूर्ण,
	अणु"MEM_UP",		8पूर्ण,
	अणु"DFX",			16पूर्ण,
	अणु"DFX_FORCE_LTR",	24पूर्ण,
	अणु"DISPLAY",		32पूर्ण,
	अणु"ISP",			40पूर्ण,
	अणु"SOUTH",		48पूर्ण,
पूर्ण;

काष्ठा telem_pss_wakeup_info अणु
	स्थिर अक्षर *name;
	u32 bit_pos;
पूर्ण;

अटल काष्ठा telem_pss_wakeup_info telem_apl_pss_wakeup[] = अणु
	अणु"IP_IDLE",			0पूर्ण,
	अणु"DISPLAY_WAKE",		8पूर्ण,
	अणु"VOLTAGE_REG_INT",		16पूर्ण,
	अणु"DROWSY_TIMER (HOTPLUG)",	24पूर्ण,
	अणु"CORE_WAKE",			32पूर्ण,
	अणु"MISC_S0IX",			40पूर्ण,
	अणु"MISC_ABORT",			56पूर्ण,
पूर्ण;

काष्ठा telem_ioss_d0ix_stateinfo अणु
	स्थिर अक्षर *name;
	u32 bit_pos;
पूर्ण;

अटल काष्ठा telem_ioss_d0ix_stateinfo telem_apl_ioss_d0ix_data[] = अणु
	अणु"CSE",		0पूर्ण,
	अणु"SCC2",	1पूर्ण,
	अणु"GMM",		2पूर्ण,
	अणु"XDCI",	3पूर्ण,
	अणु"XHCI",	4पूर्ण,
	अणु"ISH",		5पूर्ण,
	अणु"AVS",		6पूर्ण,
	अणु"PCIE0P1",	7पूर्ण,
	अणु"PECI0P0",	8पूर्ण,
	अणु"LPSS",	9पूर्ण,
	अणु"SCC",		10पूर्ण,
	अणु"PWM",		11पूर्ण,
	अणु"PCIE1_P3",    12पूर्ण,
	अणु"PCIE1_P2",    13पूर्ण,
	अणु"PCIE1_P1",    14पूर्ण,
	अणु"PCIE1_P0",    15पूर्ण,
	अणु"CNV",		16पूर्ण,
	अणु"SATA",	17पूर्ण,
	अणु"PRTC",	18पूर्ण,
पूर्ण;

काष्ठा telem_ioss_pg_info अणु
	स्थिर अक्षर *name;
	u32 bit_pos;
पूर्ण;

अटल काष्ठा telem_ioss_pg_info telem_apl_ioss_pg_data[] = अणु
	अणु"LPSS",	0पूर्ण,
	अणु"SCC",		1पूर्ण,
	अणु"P2SB",	2पूर्ण,
	अणु"SCC2",	3पूर्ण,
	अणु"GMM",		4पूर्ण,
	अणु"PCIE0",	5पूर्ण,
	अणु"XDCI",	6पूर्ण,
	अणु"xHCI",	7पूर्ण,
	अणु"CSE",		8पूर्ण,
	अणु"SPI",		9पूर्ण,
	अणु"AVSPGD4",	10पूर्ण,
	अणु"AVSPGD3",	11पूर्ण,
	अणु"AVSPGD2",	12पूर्ण,
	अणु"AVSPGD1",	13पूर्ण,
	अणु"ISH",		14पूर्ण,
	अणु"EXI",		15पूर्ण,
	अणु"NPKVRC",	16पूर्ण,
	अणु"NPKVNN",	17पूर्ण,
	अणु"CUNIT",	18पूर्ण,
	अणु"FUSE_CTRL",	19पूर्ण,
	अणु"PCIE1",	20पूर्ण,
	अणु"CNV",		21पूर्ण,
	अणु"LPC",		22पूर्ण,
	अणु"SATA",	23पूर्ण,
	अणु"SMB",		24पूर्ण,
	अणु"PRTC",	25पूर्ण,
पूर्ण;

काष्ठा telemetry_debugfs_conf अणु
	काष्ठा telemetry_susp_stats suspend_stats;
	काष्ठा dentry *telemetry_dbg_dir;

	/* Biपंचांगap Data */
	काष्ठा telem_ioss_d0ix_stateinfo *ioss_d0ix_data;
	काष्ठा telem_pss_idle_stateinfo *pss_idle_data;
	काष्ठा telem_pcs_blkd_info *pcs_idle_blkd_data;
	काष्ठा telem_pcs_blkd_info *pcs_s0ix_blkd_data;
	काष्ठा telem_pss_wakeup_info *pss_wakeup;
	काष्ठा telem_pss_ltr_info *pss_ltr_data;
	काष्ठा telem_ioss_pg_info *ioss_pg_data;
	u8 pcs_idle_blkd_evts;
	u8 pcs_s0ix_blkd_evts;
	u8 pss_wakeup_evts;
	u8 pss_idle_evts;
	u8 pss_ltr_evts;
	u8 ioss_d0ix_evts;
	u8 ioss_pg_evts;

	/* IDs */
	u16  pss_ltr_blocking_id;
	u16  pcs_idle_blkd_id;
	u16  pcs_s0ix_blkd_id;
	u16  s0ix_total_occ_id;
	u16  s0ix_shlw_occ_id;
	u16  s0ix_deep_occ_id;
	u16  s0ix_total_res_id;
	u16  s0ix_shlw_res_id;
	u16  s0ix_deep_res_id;
	u16  pss_wakeup_id;
	u16  ioss_d0ix_id;
	u16  pstates_id;
	u16  pss_idle_id;
	u16  ioss_d3_id;
	u16  ioss_pg_id;
पूर्ण;

अटल काष्ठा telemetry_debugfs_conf *debugfs_conf;

अटल काष्ठा telemetry_debugfs_conf telem_apl_debugfs_conf = अणु
	.pss_idle_data = telem_apl_pss_idle_data,
	.pcs_idle_blkd_data = telem_apl_pcs_idle_blkd_data,
	.pcs_s0ix_blkd_data = telem_apl_pcs_s0ix_blkd_data,
	.pss_ltr_data = telem_apl_pss_ltr_data,
	.pss_wakeup = telem_apl_pss_wakeup,
	.ioss_d0ix_data = telem_apl_ioss_d0ix_data,
	.ioss_pg_data = telem_apl_ioss_pg_data,

	.pss_idle_evts = ARRAY_SIZE(telem_apl_pss_idle_data),
	.pcs_idle_blkd_evts = ARRAY_SIZE(telem_apl_pcs_idle_blkd_data),
	.pcs_s0ix_blkd_evts = ARRAY_SIZE(telem_apl_pcs_s0ix_blkd_data),
	.pss_ltr_evts = ARRAY_SIZE(telem_apl_pss_ltr_data),
	.pss_wakeup_evts = ARRAY_SIZE(telem_apl_pss_wakeup),
	.ioss_d0ix_evts = ARRAY_SIZE(telem_apl_ioss_d0ix_data),
	.ioss_pg_evts = ARRAY_SIZE(telem_apl_ioss_pg_data),

	.pstates_id = TELEM_APL_PSS_PSTATES_ID,
	.pss_idle_id = TELEM_APL_PSS_IDLE_ID,
	.pcs_idle_blkd_id = TELEM_APL_PCS_IDLE_BLOCKED_ID,
	.pcs_s0ix_blkd_id = TELEM_APL_PCS_S0IX_BLOCKED_ID,
	.pss_wakeup_id = TELEM_APL_PSS_WAKEUP_ID,
	.pss_ltr_blocking_id = TELEM_APL_PSS_LTR_BLOCKING_ID,
	.s0ix_total_occ_id = TELEM_APL_S0IX_TOTAL_OCC_ID,
	.s0ix_shlw_occ_id = TELEM_APL_S0IX_SHLW_OCC_ID,
	.s0ix_deep_occ_id = TELEM_APL_S0IX_DEEP_OCC_ID,
	.s0ix_total_res_id = TELEM_APL_S0IX_TOTAL_RES_ID,
	.s0ix_shlw_res_id = TELEM_APL_S0IX_SHLW_RES_ID,
	.s0ix_deep_res_id = TELEM_APL_S0IX_DEEP_RES_ID,
	.ioss_d0ix_id = TELEM_APL_D0IX_ID,
	.ioss_d3_id = TELEM_APL_D3_ID,
	.ioss_pg_id = TELEM_APL_PG_ID,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id telemetry_debugfs_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT,	&telem_apl_debugfs_conf),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_PLUS,	&telem_apl_debugfs_conf),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, telemetry_debugfs_cpu_ids);

अटल पूर्णांक telemetry_debugfs_check_evts(व्योम)
अणु
	अगर ((debugfs_conf->pss_idle_evts > TELEM_PSS_IDLE_EVTS) ||
	    (debugfs_conf->pcs_idle_blkd_evts > TELEM_PSS_IDLE_BLOCKED_EVTS) ||
	    (debugfs_conf->pcs_s0ix_blkd_evts > TELEM_PSS_S0IX_BLOCKED_EVTS) ||
	    (debugfs_conf->pss_ltr_evts > TELEM_PSS_LTR_BLOCKING_EVTS) ||
	    (debugfs_conf->pss_wakeup_evts > TELEM_PSS_S0IX_WAKEUP_EVTS) ||
	    (debugfs_conf->ioss_d0ix_evts > TELEM_IOSS_DX_D0IX_EVTS) ||
	    (debugfs_conf->ioss_pg_evts > TELEM_IOSS_PG_EVTS))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक telem_pss_states_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा telemetry_evtlog evtlog[TELEM_MAX_OS_ALLOCATED_EVENTS];
	काष्ठा telemetry_debugfs_conf *conf = debugfs_conf;
	स्थिर अक्षर *name[TELEM_MAX_OS_ALLOCATED_EVENTS];
	u32 pcs_idle_blkd[TELEM_PSS_IDLE_BLOCKED_EVTS],
	    pcs_s0ix_blkd[TELEM_PSS_S0IX_BLOCKED_EVTS],
	    pss_s0ix_wakeup[TELEM_PSS_S0IX_WAKEUP_EVTS],
	    pss_ltr_blkd[TELEM_PSS_LTR_BLOCKING_EVTS],
	    pss_idle[TELEM_PSS_IDLE_EVTS];
	पूर्णांक index, idx, ret, err = 0;
	u64 pstates = 0;

	ret = telemetry_पढ़ो_eventlog(TELEM_PSS, evtlog,
				      TELEM_MAX_OS_ALLOCATED_EVENTS);
	अगर (ret < 0)
		वापस ret;

	err = telemetry_get_evtname(TELEM_PSS, name,
				    TELEM_MAX_OS_ALLOCATED_EVENTS);
	अगर (err < 0)
		वापस err;

	seq_माला_दो(s, "\n----------------------------------------------------\n");
	seq_माला_दो(s, "\tPSS TELEM EVENTLOG (Residency = field/19.2 us\n");
	seq_माला_दो(s, "----------------------------------------------------\n");
	क्रम (index = 0; index < ret; index++) अणु
		seq_म_लिखो(s, "%-32s %llu\n",
			   name[index], evtlog[index].telem_evtlog);

		/* Fetch PSS IDLE State */
		अगर (evtlog[index].telem_evtid == conf->pss_idle_id) अणु
			pss_idle[conf->pss_idle_evts - 1] =
			(evtlog[index].telem_evtlog >>
			conf->pss_idle_data[conf->pss_idle_evts - 1].bit_pos) &
			TELEM_APL_MASK_PCS_STATE;
		पूर्ण

		TELEM_CHECK_AND_PARSE_EVTS(conf->pss_idle_id,
					   conf->pss_idle_evts - 1,
					   pss_idle, evtlog[index].telem_evtlog,
					   conf->pss_idle_data, TELEM_MASK_BIT);

		TELEM_CHECK_AND_PARSE_EVTS(conf->pcs_idle_blkd_id,
					   conf->pcs_idle_blkd_evts,
					   pcs_idle_blkd,
					   evtlog[index].telem_evtlog,
					   conf->pcs_idle_blkd_data,
					   TELEM_MASK_BYTE);

		TELEM_CHECK_AND_PARSE_EVTS(conf->pcs_s0ix_blkd_id,
					   conf->pcs_s0ix_blkd_evts,
					   pcs_s0ix_blkd,
					   evtlog[index].telem_evtlog,
					   conf->pcs_s0ix_blkd_data,
					   TELEM_MASK_BYTE);

		TELEM_CHECK_AND_PARSE_EVTS(conf->pss_wakeup_id,
					   conf->pss_wakeup_evts,
					   pss_s0ix_wakeup,
					   evtlog[index].telem_evtlog,
					   conf->pss_wakeup, TELEM_MASK_BYTE);

		TELEM_CHECK_AND_PARSE_EVTS(conf->pss_ltr_blocking_id,
					   conf->pss_ltr_evts, pss_ltr_blkd,
					   evtlog[index].telem_evtlog,
					   conf->pss_ltr_data, TELEM_MASK_BYTE);

		अगर (evtlog[index].telem_evtid == debugfs_conf->pstates_id)
			pstates = evtlog[index].telem_evtlog;
	पूर्ण

	seq_माला_दो(s, "\n--------------------------------------\n");
	seq_माला_दो(s, "PStates\n");
	seq_माला_दो(s, "--------------------------------------\n");
	seq_माला_दो(s, "Domain\t\t\t\tFreq(Mhz)\n");
	seq_म_लिखो(s, " IA\t\t\t\t %llu\n GT\t\t\t\t %llu\n",
		   (pstates & TELEM_MASK_BYTE)*100,
		   ((pstates >> 8) & TELEM_MASK_BYTE)*50/3);

	seq_म_लिखो(s, " IUNIT\t\t\t\t %llu\n SA\t\t\t\t %llu\n",
		   ((pstates >> 16) & TELEM_MASK_BYTE)*25,
		   ((pstates >> 24) & TELEM_MASK_BYTE)*50/3);

	seq_माला_दो(s, "\n--------------------------------------\n");
	seq_माला_दो(s, "PSS IDLE Status\n");
	seq_माला_दो(s, "--------------------------------------\n");
	seq_माला_दो(s, "Device\t\t\t\t\tIDLE\n");
	क्रम (index = 0; index < debugfs_conf->pss_idle_evts; index++) अणु
		seq_म_लिखो(s, "%-32s\t%u\n",
			   debugfs_conf->pss_idle_data[index].name,
			   pss_idle[index]);
	पूर्ण

	seq_माला_दो(s, "\n--------------------------------------\n");
	seq_माला_दो(s, "PSS Idle blkd Status (~1ms saturating bucket)\n");
	seq_माला_दो(s, "--------------------------------------\n");
	seq_माला_दो(s, "Blocker\t\t\t\t\tCount\n");
	क्रम (index = 0; index < debugfs_conf->pcs_idle_blkd_evts; index++) अणु
		seq_म_लिखो(s, "%-32s\t%u\n",
			   debugfs_conf->pcs_idle_blkd_data[index].name,
			   pcs_idle_blkd[index]);
	पूर्ण

	seq_माला_दो(s, "\n--------------------------------------\n");
	seq_माला_दो(s, "PSS S0ix blkd Status (~1ms saturating bucket)\n");
	seq_माला_दो(s, "--------------------------------------\n");
	seq_माला_दो(s, "Blocker\t\t\t\t\tCount\n");
	क्रम (index = 0; index < debugfs_conf->pcs_s0ix_blkd_evts; index++) अणु
		seq_म_लिखो(s, "%-32s\t%u\n",
			   debugfs_conf->pcs_s0ix_blkd_data[index].name,
			   pcs_s0ix_blkd[index]);
	पूर्ण

	seq_माला_दो(s, "\n--------------------------------------\n");
	seq_माला_दो(s, "LTR Blocking Status (~1ms saturating bucket)\n");
	seq_माला_दो(s, "--------------------------------------\n");
	seq_माला_दो(s, "Blocker\t\t\t\t\tCount\n");
	क्रम (index = 0; index < debugfs_conf->pss_ltr_evts; index++) अणु
		seq_म_लिखो(s, "%-32s\t%u\n",
			   debugfs_conf->pss_ltr_data[index].name,
			   pss_s0ix_wakeup[index]);
	पूर्ण

	seq_माला_दो(s, "\n--------------------------------------\n");
	seq_माला_दो(s, "Wakes Status (~1ms saturating bucket)\n");
	seq_माला_दो(s, "--------------------------------------\n");
	seq_माला_दो(s, "Wakes\t\t\t\t\tCount\n");
	क्रम (index = 0; index < debugfs_conf->pss_wakeup_evts; index++) अणु
		seq_म_लिखो(s, "%-32s\t%u\n",
			   debugfs_conf->pss_wakeup[index].name,
			   pss_ltr_blkd[index]);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(telem_pss_states);

अटल पूर्णांक telem_ioss_states_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा telemetry_evtlog evtlog[TELEM_MAX_OS_ALLOCATED_EVENTS];
	स्थिर अक्षर *name[TELEM_MAX_OS_ALLOCATED_EVENTS];
	पूर्णांक index, ret, err;

	ret = telemetry_पढ़ो_eventlog(TELEM_IOSS, evtlog,
				      TELEM_MAX_OS_ALLOCATED_EVENTS);
	अगर (ret < 0)
		वापस ret;

	err = telemetry_get_evtname(TELEM_IOSS, name,
				    TELEM_MAX_OS_ALLOCATED_EVENTS);
	अगर (err < 0)
		वापस err;

	seq_माला_दो(s, "--------------------------------------\n");
	seq_माला_दो(s, "\tI0SS TELEMETRY EVENTLOG\n");
	seq_माला_दो(s, "--------------------------------------\n");
	क्रम (index = 0; index < ret; index++) अणु
		seq_म_लिखो(s, "%-32s 0x%llx\n",
			   name[index], evtlog[index].telem_evtlog);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(telem_ioss_states);

अटल पूर्णांक telem_soc_states_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	u32 d3_sts[TELEM_IOSS_DX_D0IX_EVTS], d0ix_sts[TELEM_IOSS_DX_D0IX_EVTS];
	u32 pg_sts[TELEM_IOSS_PG_EVTS], pss_idle[TELEM_PSS_IDLE_EVTS];
	काष्ठा telemetry_evtlog evtlog[TELEM_MAX_OS_ALLOCATED_EVENTS];
	u32 s0ix_total_ctr = 0, s0ix_shlw_ctr = 0, s0ix_deep_ctr = 0;
	u64 s0ix_total_res = 0, s0ix_shlw_res = 0, s0ix_deep_res = 0;
	काष्ठा telemetry_debugfs_conf *conf = debugfs_conf;
	काष्ठा pci_dev *dev = शून्य;
	पूर्णांक index, idx, ret;
	u32 d3_state;
	u16 pmcsr;

	ret = telemetry_पढ़ो_eventlog(TELEM_IOSS, evtlog,
				      TELEM_MAX_OS_ALLOCATED_EVENTS);
	अगर (ret < 0)
		वापस ret;

	क्रम (index = 0; index < ret; index++) अणु
		TELEM_CHECK_AND_PARSE_EVTS(conf->ioss_d3_id,
					   conf->ioss_d0ix_evts,
					   d3_sts, evtlog[index].telem_evtlog,
					   conf->ioss_d0ix_data,
					   TELEM_MASK_BIT);

		TELEM_CHECK_AND_PARSE_EVTS(conf->ioss_pg_id, conf->ioss_pg_evts,
					   pg_sts, evtlog[index].telem_evtlog,
					   conf->ioss_pg_data, TELEM_MASK_BIT);

		TELEM_CHECK_AND_PARSE_EVTS(conf->ioss_d0ix_id,
					   conf->ioss_d0ix_evts,
					   d0ix_sts, evtlog[index].telem_evtlog,
					   conf->ioss_d0ix_data,
					   TELEM_MASK_BIT);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_total_occ_id,
					   s0ix_total_ctr);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_occ_id,
					   s0ix_shlw_ctr);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_occ_id,
					   s0ix_deep_ctr);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_total_res_id,
					   s0ix_total_res);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_res_id,
					   s0ix_shlw_res);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_res_id,
					   s0ix_deep_res);
	पूर्ण

	seq_माला_दो(s, "\n---------------------------------------------------\n");
	seq_माला_दो(s, "S0IX Type\t\t\t Occurrence\t\t Residency(us)\n");
	seq_माला_दो(s, "---------------------------------------------------\n");

	seq_म_लिखो(s, "S0IX Shallow\t\t\t %10u\t %10llu\n",
		   s0ix_shlw_ctr -
		   conf->suspend_stats.shlw_ctr,
		   (u64)((s0ix_shlw_res -
		   conf->suspend_stats.shlw_res)*10/192));

	seq_म_लिखो(s, "S0IX Deep\t\t\t %10u\t %10llu\n",
		   s0ix_deep_ctr -
		   conf->suspend_stats.deep_ctr,
		   (u64)((s0ix_deep_res -
		   conf->suspend_stats.deep_res)*10/192));

	seq_म_लिखो(s, "Suspend(With S0ixShallow)\t %10u\t %10llu\n",
		   conf->suspend_stats.shlw_ctr,
		   (u64)(conf->suspend_stats.shlw_res*10)/192);

	seq_म_लिखो(s, "Suspend(With S0ixDeep)\t\t %10u\t %10llu\n",
		   conf->suspend_stats.deep_ctr,
		   (u64)(conf->suspend_stats.deep_res*10)/192);

	seq_म_लिखो(s, "TOTAL S0IX\t\t\t %10u\t %10llu\n", s0ix_total_ctr,
		   (u64)(s0ix_total_res*10/192));
	seq_माला_दो(s, "\n-------------------------------------------------\n");
	seq_माला_दो(s, "\t\tDEVICE STATES\n");
	seq_माला_दो(s, "-------------------------------------------------\n");

	क्रम_each_pci_dev(dev) अणु
		pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
		d3_state = ((pmcsr & PCI_PM_CTRL_STATE_MASK) ==
			    (__क्रमce पूर्णांक)PCI_D3hot) ? 1 : 0;

		seq_म_लिखो(s, "pci %04x %04X %s %20.20s: ",
			   dev->venकरोr, dev->device, dev_name(&dev->dev),
			   dev_driver_string(&dev->dev));
		seq_म_लिखो(s, " d3:%x\n", d3_state);
	पूर्ण

	seq_माला_दो(s, "\n--------------------------------------\n");
	seq_माला_दो(s, "D3/D0i3 Status\n");
	seq_माला_दो(s, "--------------------------------------\n");
	seq_माला_दो(s, "Block\t\t D3\t D0i3\n");
	क्रम (index = 0; index < conf->ioss_d0ix_evts; index++) अणु
		seq_म_लिखो(s, "%-10s\t %u\t %u\n",
			   conf->ioss_d0ix_data[index].name,
			   d3_sts[index], d0ix_sts[index]);
	पूर्ण

	seq_माला_दो(s, "\n--------------------------------------\n");
	seq_माला_दो(s, "South Complex PowerGate Status\n");
	seq_माला_दो(s, "--------------------------------------\n");
	seq_माला_दो(s, "Device\t\t PG\n");
	क्रम (index = 0; index < conf->ioss_pg_evts; index++) अणु
		seq_म_लिखो(s, "%-10s\t %u\n",
			   conf->ioss_pg_data[index].name,
			   pg_sts[index]);
	पूर्ण

	evtlog->telem_evtid = conf->pss_idle_id;
	ret = telemetry_पढ़ो_events(TELEM_PSS, evtlog, 1);
	अगर (ret < 0)
		वापस ret;

	seq_माला_दो(s, "\n-----------------------------------------\n");
	seq_माला_दो(s, "North Idle Status\n");
	seq_माला_दो(s, "-----------------------------------------\n");
	क्रम (idx = 0; idx < conf->pss_idle_evts - 1; idx++) अणु
		pss_idle[idx] =	(evtlog->telem_evtlog >>
				conf->pss_idle_data[idx].bit_pos) &
				TELEM_MASK_BIT;
	पूर्ण

	pss_idle[idx] = (evtlog->telem_evtlog >>
			conf->pss_idle_data[idx].bit_pos) &
			TELEM_APL_MASK_PCS_STATE;

	क्रम (index = 0; index < conf->pss_idle_evts; index++) अणु
		seq_म_लिखो(s, "%-30s %u\n",
			   conf->pss_idle_data[index].name,
			   pss_idle[index]);
	पूर्ण

	seq_माला_दो(s, "\nPCS_STATUS Code\n");
	seq_माला_दो(s, "0:C0 1:C1 2:C1_DN_WT_DEV 3:C2 4:C2_WT_DE_MEM_UP\n");
	seq_माला_दो(s, "5:C2_WT_DE_MEM_DOWN 6:C2_UP_WT_DEV 7:C2_DN 8:C2_VOA\n");
	seq_माला_दो(s, "9:C2_VOA_UP 10:S0IX_PRE 11:S0IX\n");

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(telem_soc_states);

अटल पूर्णांक telem_s0ix_res_get(व्योम *data, u64 *val)
अणु
	काष्ठा telemetry_plt_config *plt_config = telemetry_get_pltdata();
	u64 s0ix_total_res;
	पूर्णांक ret;

	ret = पूर्णांकel_pmc_s0ix_counter_पढ़ो(plt_config->pmc, &s0ix_total_res);
	अगर (ret) अणु
		pr_err("Failed to read S0ix residency");
		वापस ret;
	पूर्ण

	*val = s0ix_total_res;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(telem_s0ix_fops, telem_s0ix_res_get, शून्य, "%llu\n");

अटल पूर्णांक telem_pss_trc_verb_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	u32 verbosity;
	पूर्णांक err;

	err = telemetry_get_trace_verbosity(TELEM_PSS, &verbosity);
	अगर (err) अणु
		pr_err("Get PSS Trace Verbosity Failed with Error %d\n", err);
		वापस -EFAULT;
	पूर्ण

	seq_म_लिखो(s, "PSS Trace Verbosity %u\n", verbosity);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार telem_pss_trc_verb_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *userbuf,
					माप_प्रकार count, loff_t *ppos)
अणु
	u32 verbosity;
	पूर्णांक err;

	err = kstrtou32_from_user(userbuf, count, 0, &verbosity);
	अगर (err)
		वापस err;

	err = telemetry_set_trace_verbosity(TELEM_PSS, verbosity);
	अगर (err) अणु
		pr_err("Changing PSS Trace Verbosity Failed. Error %d\n", err);
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक telem_pss_trc_verb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, telem_pss_trc_verb_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations telem_pss_trc_verb_ops = अणु
	.खोलो		= telem_pss_trc_verb_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= telem_pss_trc_verb_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक telem_ioss_trc_verb_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	u32 verbosity;
	पूर्णांक err;

	err = telemetry_get_trace_verbosity(TELEM_IOSS, &verbosity);
	अगर (err) अणु
		pr_err("Get IOSS Trace Verbosity Failed with Error %d\n", err);
		वापस -EFAULT;
	पूर्ण

	seq_म_लिखो(s, "IOSS Trace Verbosity %u\n", verbosity);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार telem_ioss_trc_verb_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *userbuf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	u32 verbosity;
	पूर्णांक err;

	err = kstrtou32_from_user(userbuf, count, 0, &verbosity);
	अगर (err)
		वापस err;

	err = telemetry_set_trace_verbosity(TELEM_IOSS, verbosity);
	अगर (err) अणु
		pr_err("Changing IOSS Trace Verbosity Failed. Error %d\n", err);
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक telem_ioss_trc_verb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, telem_ioss_trc_verb_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations telem_ioss_trc_verb_ops = अणु
	.खोलो		= telem_ioss_trc_verb_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= telem_ioss_trc_verb_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक pm_suspend_prep_cb(व्योम)
अणु
	काष्ठा telemetry_evtlog evtlog[TELEM_MAX_OS_ALLOCATED_EVENTS];
	काष्ठा telemetry_debugfs_conf *conf = debugfs_conf;
	पूर्णांक ret, index;

	ret = telemetry_raw_पढ़ो_eventlog(TELEM_IOSS, evtlog,
			TELEM_MAX_OS_ALLOCATED_EVENTS);
	अगर (ret < 0) अणु
		suspend_prep_ok = 0;
		जाओ out;
	पूर्ण

	क्रम (index = 0; index < ret; index++) अणु

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_occ_id,
					   suspend_shlw_ctr_temp);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_occ_id,
					   suspend_deep_ctr_temp);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_res_id,
					   suspend_shlw_res_temp);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_res_id,
					   suspend_deep_res_temp);
	पूर्ण
	suspend_prep_ok = 1;
out:
	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक pm_suspend_निकास_cb(व्योम)
अणु
	काष्ठा telemetry_evtlog evtlog[TELEM_MAX_OS_ALLOCATED_EVENTS];
	अटल u32 suspend_shlw_ctr_निकास, suspend_deep_ctr_निकास;
	अटल u64 suspend_shlw_res_निकास, suspend_deep_res_निकास;
	काष्ठा telemetry_debugfs_conf *conf = debugfs_conf;
	पूर्णांक ret, index;

	अगर (!suspend_prep_ok)
		जाओ out;

	ret = telemetry_raw_पढ़ो_eventlog(TELEM_IOSS, evtlog,
					  TELEM_MAX_OS_ALLOCATED_EVENTS);
	अगर (ret < 0)
		जाओ out;

	क्रम (index = 0; index < ret; index++) अणु
		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_occ_id,
					   suspend_shlw_ctr_निकास);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_occ_id,
					   suspend_deep_ctr_निकास);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_res_id,
					   suspend_shlw_res_निकास);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_res_id,
					   suspend_deep_res_निकास);
	पूर्ण

	अगर ((suspend_shlw_ctr_निकास < suspend_shlw_ctr_temp) ||
	    (suspend_deep_ctr_निकास < suspend_deep_ctr_temp) ||
	    (suspend_shlw_res_निकास < suspend_shlw_res_temp) ||
	    (suspend_deep_res_निकास < suspend_deep_res_temp)) अणु
		pr_err("Wrong s0ix counters detected\n");
		जाओ out;
	पूर्ण

	/*
	 * Due to some design limitations in the firmware, someबार the
	 * counters करो not get updated by the समय we reach here. As a
	 * workaround, we try to see अगर this was a genuine हाल of sleep
	 * failure or not by cross-checking from PMC GCR रेजिस्टरs directly.
	 */
	अगर (suspend_shlw_ctr_निकास == suspend_shlw_ctr_temp &&
	    suspend_deep_ctr_निकास == suspend_deep_ctr_temp) अणु
		काष्ठा telemetry_plt_config *plt_config = telemetry_get_pltdata();
		काष्ठा पूर्णांकel_pmc_dev *pmc = plt_config->pmc;

		ret = पूर्णांकel_pmc_gcr_पढ़ो64(pmc, PMC_GCR_TELEM_SHLW_S0IX_REG,
					  &suspend_shlw_res_निकास);
		अगर (ret < 0)
			जाओ out;

		ret = पूर्णांकel_pmc_gcr_पढ़ो64(pmc, PMC_GCR_TELEM_DEEP_S0IX_REG,
					  &suspend_deep_res_निकास);
		अगर (ret < 0)
			जाओ out;

		अगर (suspend_shlw_res_निकास > suspend_shlw_res_temp)
			suspend_shlw_ctr_निकास++;

		अगर (suspend_deep_res_निकास > suspend_deep_res_temp)
			suspend_deep_ctr_निकास++;
	पूर्ण

	suspend_shlw_ctr_निकास -= suspend_shlw_ctr_temp;
	suspend_deep_ctr_निकास -= suspend_deep_ctr_temp;
	suspend_shlw_res_निकास -= suspend_shlw_res_temp;
	suspend_deep_res_निकास -= suspend_deep_res_temp;

	अगर (suspend_shlw_ctr_निकास != 0) अणु
		conf->suspend_stats.shlw_ctr +=
		suspend_shlw_ctr_निकास;

		conf->suspend_stats.shlw_res +=
		suspend_shlw_res_निकास;
	पूर्ण

	अगर (suspend_deep_ctr_निकास != 0) अणु
		conf->suspend_stats.deep_ctr +=
		suspend_deep_ctr_निकास;

		conf->suspend_stats.deep_res +=
		suspend_deep_res_निकास;
	पूर्ण

out:
	suspend_prep_ok = 0;
	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक pm_notअगरication(काष्ठा notअगरier_block *this,
			   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	चयन (event) अणु
	हाल PM_SUSPEND_PREPARE:
		वापस pm_suspend_prep_cb();
	हाल PM_POST_SUSPEND:
		वापस pm_suspend_निकास_cb();
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block pm_notअगरier = अणु
	.notअगरier_call = pm_notअगरication,
पूर्ण;

अटल पूर्णांक __init telemetry_debugfs_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	पूर्णांक err;
	काष्ठा dentry *dir;

	/* Only APL supported क्रम now */
	id = x86_match_cpu(telemetry_debugfs_cpu_ids);
	अगर (!id)
		वापस -ENODEV;

	debugfs_conf = (काष्ठा telemetry_debugfs_conf *)id->driver_data;

	अगर (!telemetry_get_pltdata()) अणु
		pr_info("Invalid pltconfig, ensure IPC1 device is enabled in BIOS\n");
		वापस -ENODEV;
	पूर्ण

	err = telemetry_debugfs_check_evts();
	अगर (err < 0) अणु
		pr_info("telemetry_debugfs_check_evts failed\n");
		वापस -EINVAL;
	पूर्ण

	रेजिस्टर_pm_notअगरier(&pm_notअगरier);

	dir = debugfs_create_dir("telemetry", शून्य);
	debugfs_conf->telemetry_dbg_dir = dir;

	debugfs_create_file("pss_info", S_IFREG | S_IRUGO, dir, शून्य,
			    &telem_pss_states_fops);
	debugfs_create_file("ioss_info", S_IFREG | S_IRUGO, dir, शून्य,
			    &telem_ioss_states_fops);
	debugfs_create_file("soc_states", S_IFREG | S_IRUGO, dir, शून्य,
			    &telem_soc_states_fops);
	debugfs_create_file("s0ix_residency_usec", S_IFREG | S_IRUGO, dir, शून्य,
			    &telem_s0ix_fops);
	debugfs_create_file("pss_trace_verbosity", S_IFREG | S_IRUGO, dir, शून्य,
			    &telem_pss_trc_verb_ops);
	debugfs_create_file("ioss_trace_verbosity", S_IFREG | S_IRUGO, dir,
			    शून्य, &telem_ioss_trc_verb_ops);
	वापस 0;
पूर्ण

अटल व्योम __निकास telemetry_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(debugfs_conf->telemetry_dbg_dir);
	debugfs_conf->telemetry_dbg_dir = शून्य;
	unरेजिस्टर_pm_notअगरier(&pm_notअगरier);
पूर्ण

late_initcall(telemetry_debugfs_init);
module_निकास(telemetry_debugfs_निकास);

MODULE_AUTHOR("Souvik Kumar Chakravarty <souvik.k.chakravarty@intel.com>");
MODULE_DESCRIPTION("Intel SoC Telemetry debugfs Interface");
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
