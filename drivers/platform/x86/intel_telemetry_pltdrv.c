<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel SOC Telemetry Platक्रमm Driver: Currently supports APL
 * Copyright (c) 2015, Intel Corporation.
 * All Rights Reserved.
 *
 * This file provides the platक्रमm specअगरic telemetry implementation क्रम APL.
 * It used the PUNIT and PMC IPC पूर्णांकerfaces क्रम configuring the counters.
 * The accumulated results are fetched from SRAM.
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/पूर्णांकel_punit_ipc.h>
#समावेश <यंत्र/पूर्णांकel_telemetry.h>

#घोषणा DRIVER_NAME	"intel_telemetry"
#घोषणा DRIVER_VERSION	"1.0.0"

#घोषणा TELEM_TRC_VERBOSITY_MASK	0x3

#घोषणा TELEM_MIN_PERIOD(x)		((x) & 0x7F0000)
#घोषणा TELEM_MAX_PERIOD(x)		((x) & 0x7F000000)
#घोषणा TELEM_SAMPLE_PERIOD_INVALID(x)	((x) & (BIT(7)))
#घोषणा TELEM_CLEAR_SAMPLE_PERIOD(x)	((x) &= ~0x7F)

#घोषणा TELEM_SAMPLING_DEFAULT_PERIOD	0xD

#घोषणा TELEM_MAX_EVENTS_SRAM		28
#घोषणा TELEM_SSRAM_STARTTIME_OFFSET	8
#घोषणा TELEM_SSRAM_EVTLOG_OFFSET	16

#घोषणा IOSS_TELEM			0xeb
#घोषणा IOSS_TELEM_EVENT_READ		0x0
#घोषणा IOSS_TELEM_EVENT_WRITE		0x1
#घोषणा IOSS_TELEM_INFO_READ		0x2
#घोषणा IOSS_TELEM_TRACE_CTL_READ	0x5
#घोषणा IOSS_TELEM_TRACE_CTL_WRITE	0x6
#घोषणा IOSS_TELEM_EVENT_CTL_READ	0x7
#घोषणा IOSS_TELEM_EVENT_CTL_WRITE	0x8
#घोषणा IOSS_TELEM_EVT_WRITE_SIZE	0x3

#घोषणा TELEM_INFO_SRAMEVTS_MASK	0xFF00
#घोषणा TELEM_INFO_SRAMEVTS_SHIFT	0x8
#घोषणा TELEM_SSRAM_READ_TIMEOUT	10

#घोषणा TELEM_INFO_NENABLES_MASK	0xFF
#घोषणा TELEM_EVENT_ENABLE		0x8000

#घोषणा TELEM_MASK_BIT			1
#घोषणा TELEM_MASK_BYTE			0xFF
#घोषणा BYTES_PER_LONG			8
#घोषणा TELEM_MASK_PCS_STATE		0xF

#घोषणा TELEM_DISABLE(x)		((x) &= ~(BIT(31)))
#घोषणा TELEM_CLEAR_EVENTS(x)		((x) |= (BIT(30)))
#घोषणा TELEM_ENABLE_SRAM_EVT_TRACE(x)	((x) &= ~(BIT(30) | BIT(24)))
#घोषणा TELEM_ENABLE_PERIODIC(x)	((x) |= (BIT(23) | BIT(31) | BIT(7)))
#घोषणा TELEM_EXTRACT_VERBOSITY(x, y)	((y) = (((x) >> 27) & 0x3))
#घोषणा TELEM_CLEAR_VERBOSITY_BITS(x)	((x) &= ~(BIT(27) | BIT(28)))
#घोषणा TELEM_SET_VERBOSITY_BITS(x, y)	((x) |= ((y) << 27))

क्रमागत telemetry_action अणु
	TELEM_UPDATE = 0,
	TELEM_ADD,
	TELEM_RESET,
	TELEM_ACTION_NONE
पूर्ण;

काष्ठा telem_ssram_region अणु
	u64 बारtamp;
	u64 start_समय;
	u64 events[TELEM_MAX_EVENTS_SRAM];
पूर्ण;

अटल काष्ठा telemetry_plt_config *telm_conf;

/*
 * The following counters are programmed by शेष during setup.
 * Only 20 allocated to kernel driver
 */
अटल काष्ठा telemetry_evपंचांगap
	telemetry_apl_ioss_शेष_events[TELEM_MAX_OS_ALLOCATED_EVENTS] = अणु
	अणु"SOC_S0IX_TOTAL_RES",			0x4800पूर्ण,
	अणु"SOC_S0IX_TOTAL_OCC",			0x4000पूर्ण,
	अणु"SOC_S0IX_SHALLOW_RES",		0x4801पूर्ण,
	अणु"SOC_S0IX_SHALLOW_OCC",		0x4001पूर्ण,
	अणु"SOC_S0IX_DEEP_RES",			0x4802पूर्ण,
	अणु"SOC_S0IX_DEEP_OCC",			0x4002पूर्ण,
	अणु"PMC_POWER_GATE",			0x5818पूर्ण,
	अणु"PMC_D3_STATES",			0x5819पूर्ण,
	अणु"PMC_D0I3_STATES",			0x581Aपूर्ण,
	अणु"PMC_S0IX_WAKE_REASON_GPIO",		0x6000पूर्ण,
	अणु"PMC_S0IX_WAKE_REASON_TIMER",		0x6001पूर्ण,
	अणु"PMC_S0IX_WAKE_REASON_VNNREQ",         0x6002पूर्ण,
	अणु"PMC_S0IX_WAKE_REASON_LOWPOWER",       0x6003पूर्ण,
	अणु"PMC_S0IX_WAKE_REASON_EXTERNAL",       0x6004पूर्ण,
	अणु"PMC_S0IX_WAKE_REASON_MISC",           0x6005पूर्ण,
	अणु"PMC_S0IX_BLOCKING_IPS_D3_D0I3",       0x6006पूर्ण,
	अणु"PMC_S0IX_BLOCKING_IPS_PG",            0x6007पूर्ण,
	अणु"PMC_S0IX_BLOCKING_MISC_IPS_PG",       0x6008पूर्ण,
	अणु"PMC_S0IX_BLOCK_IPS_VNN_REQ",          0x6009पूर्ण,
	अणु"PMC_S0IX_BLOCK_IPS_CLOCKS",           0x600Bपूर्ण,
पूर्ण;


अटल काष्ठा telemetry_evपंचांगap
	telemetry_apl_pss_शेष_events[TELEM_MAX_OS_ALLOCATED_EVENTS] = अणु
	अणु"IA_CORE0_C6_RES",			0x0400पूर्ण,
	अणु"IA_CORE0_C6_CTR",			0x0000पूर्ण,
	अणु"IA_MODULE0_C7_RES",			0x0410पूर्ण,
	अणु"IA_MODULE0_C7_CTR",			0x000Eपूर्ण,
	अणु"IA_C0_RES",				0x0805पूर्ण,
	अणु"PCS_LTR",				0x2801पूर्ण,
	अणु"PSTATES",				0x2802पूर्ण,
	अणु"SOC_S0I3_RES",			0x0409पूर्ण,
	अणु"SOC_S0I3_CTR",			0x000Aपूर्ण,
	अणु"PCS_S0I3_CTR",			0x0009पूर्ण,
	अणु"PCS_C1E_RES",				0x041Aपूर्ण,
	अणु"PCS_IDLE_STATUS",			0x2806पूर्ण,
	अणु"IA_PERF_LIMITS",			0x280Bपूर्ण,
	अणु"GT_PERF_LIMITS",			0x280Cपूर्ण,
	अणु"PCS_WAKEUP_S0IX_CTR",			0x0030पूर्ण,
	अणु"PCS_IDLE_BLOCKED",			0x2C00पूर्ण,
	अणु"PCS_S0IX_BLOCKED",			0x2C01पूर्ण,
	अणु"PCS_S0IX_WAKE_REASONS",		0x2C02पूर्ण,
	अणु"PCS_LTR_BLOCKING",			0x2C03पूर्ण,
	अणु"PC2_AND_MEM_SHALLOW_IDLE_RES",	0x1D40पूर्ण,
पूर्ण;

अटल काष्ठा telemetry_evपंचांगap
	telemetry_glk_pss_शेष_events[TELEM_MAX_OS_ALLOCATED_EVENTS] = अणु
	अणु"IA_CORE0_C6_RES",			0x0400पूर्ण,
	अणु"IA_CORE0_C6_CTR",			0x0000पूर्ण,
	अणु"IA_MODULE0_C7_RES",			0x0410पूर्ण,
	अणु"IA_MODULE0_C7_CTR",			0x000Cपूर्ण,
	अणु"IA_C0_RES",				0x0805पूर्ण,
	अणु"PCS_LTR",				0x2801पूर्ण,
	अणु"PSTATES",				0x2802पूर्ण,
	अणु"SOC_S0I3_RES",			0x0407पूर्ण,
	अणु"SOC_S0I3_CTR",			0x0008पूर्ण,
	अणु"PCS_S0I3_CTR",			0x0007पूर्ण,
	अणु"PCS_C1E_RES",				0x0414पूर्ण,
	अणु"PCS_IDLE_STATUS",			0x2806पूर्ण,
	अणु"IA_PERF_LIMITS",			0x280Bपूर्ण,
	अणु"GT_PERF_LIMITS",			0x280Cपूर्ण,
	अणु"PCS_WAKEUP_S0IX_CTR",			0x0025पूर्ण,
	अणु"PCS_IDLE_BLOCKED",			0x2C00पूर्ण,
	अणु"PCS_S0IX_BLOCKED",			0x2C01पूर्ण,
	अणु"PCS_S0IX_WAKE_REASONS",		0x2C02पूर्ण,
	अणु"PCS_LTR_BLOCKING",			0x2C03पूर्ण,
	अणु"PC2_AND_MEM_SHALLOW_IDLE_RES",	0x1D40पूर्ण,
पूर्ण;

/* APL specअगरic Data */
अटल काष्ठा telemetry_plt_config telem_apl_config = अणु
	.pss_config = अणु
		.telem_evts = telemetry_apl_pss_शेष_events,
	पूर्ण,
	.ioss_config = अणु
		.telem_evts = telemetry_apl_ioss_शेष_events,
	पूर्ण,
पूर्ण;

/* GLK specअगरic Data */
अटल काष्ठा telemetry_plt_config telem_glk_config = अणु
	.pss_config = अणु
		.telem_evts = telemetry_glk_pss_शेष_events,
	पूर्ण,
	.ioss_config = अणु
		.telem_evts = telemetry_apl_ioss_शेष_events,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id telemetry_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT,	&telem_apl_config),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_PLUS,	&telem_glk_config),
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(x86cpu, telemetry_cpu_ids);

अटल अंतरभूत पूर्णांक telem_get_unitconfig(क्रमागत telemetry_unit telem_unit,
				     काष्ठा telemetry_unit_config **unit_config)
अणु
	अगर (telem_unit == TELEM_PSS)
		*unit_config = &(telm_conf->pss_config);
	अन्यथा अगर (telem_unit == TELEM_IOSS)
		*unit_config = &(telm_conf->ioss_config);
	अन्यथा
		वापस -EINVAL;

	वापस 0;

पूर्ण

अटल पूर्णांक telemetry_check_evtid(क्रमागत telemetry_unit telem_unit,
				 u32 *evपंचांगap, u8 len,
				 क्रमागत telemetry_action action)
अणु
	काष्ठा telemetry_unit_config *unit_config;
	पूर्णांक ret;

	ret = telem_get_unitconfig(telem_unit, &unit_config);
	अगर (ret < 0)
		वापस ret;

	चयन (action) अणु
	हाल TELEM_RESET:
		अगर (len > TELEM_MAX_EVENTS_SRAM)
			वापस -EINVAL;

		अवरोध;

	हाल TELEM_UPDATE:
		अगर (len > TELEM_MAX_EVENTS_SRAM)
			वापस -EINVAL;

		अगर ((len > 0) && (evपंचांगap == शून्य))
			वापस -EINVAL;

		अवरोध;

	हाल TELEM_ADD:
		अगर ((len + unit_config->ssram_evts_used) >
		    TELEM_MAX_EVENTS_SRAM)
			वापस -EINVAL;

		अगर ((len > 0) && (evपंचांगap == शून्य))
			वापस -EINVAL;

		अवरोध;

	शेष:
		pr_err("Unknown Telemetry action specified %d\n", action);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक telemetry_plt_config_ioss_event(u32 evt_id, पूर्णांक index)
अणु
	u32 ग_लिखो_buf;

	ग_लिखो_buf = evt_id | TELEM_EVENT_ENABLE;
	ग_लिखो_buf <<= BITS_PER_BYTE;
	ग_लिखो_buf |= index;

	वापस पूर्णांकel_scu_ipc_dev_command(telm_conf->scu, IOSS_TELEM,
					 IOSS_TELEM_EVENT_WRITE, &ग_लिखो_buf,
					 IOSS_TELEM_EVT_WRITE_SIZE, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक telemetry_plt_config_pss_event(u32 evt_id, पूर्णांक index)
अणु
	u32 ग_लिखो_buf;
	पूर्णांक ret;

	ग_लिखो_buf = evt_id | TELEM_EVENT_ENABLE;
	ret = पूर्णांकel_punit_ipc_command(IPC_PUNIT_BIOS_WRITE_TELE_EVENT,
				      index, 0, &ग_लिखो_buf, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक telemetry_setup_iossevtconfig(काष्ठा telemetry_evtconfig evtconfig,
					 क्रमागत telemetry_action action)
अणु
	काष्ठा पूर्णांकel_scu_ipc_dev *scu = telm_conf->scu;
	u8 num_ioss_evts, ioss_period;
	पूर्णांक ret, index, idx;
	u32 *ioss_evपंचांगap;
	u32 telem_ctrl;

	num_ioss_evts = evtconfig.num_evts;
	ioss_period = evtconfig.period;
	ioss_evपंचांगap = evtconfig.evपंचांगap;

	/* Get telemetry EVENT CTL */
	ret = पूर्णांकel_scu_ipc_dev_command(scu, IOSS_TELEM,
				    IOSS_TELEM_EVENT_CTL_READ, शून्य, 0,
				    &telem_ctrl, माप(telem_ctrl));
	अगर (ret) अणु
		pr_err("IOSS TELEM_CTRL Read Failed\n");
		वापस ret;
	पूर्ण

	/* Disable Telemetry */
	TELEM_DISABLE(telem_ctrl);

	ret = पूर्णांकel_scu_ipc_dev_command(scu, IOSS_TELEM,
				    IOSS_TELEM_EVENT_CTL_WRITE, &telem_ctrl,
				    माप(telem_ctrl), शून्य, 0);
	अगर (ret) अणु
		pr_err("IOSS TELEM_CTRL Event Disable Write Failed\n");
		वापस ret;
	पूर्ण


	/* Reset Everything */
	अगर (action == TELEM_RESET) अणु
		/* Clear All Events */
		TELEM_CLEAR_EVENTS(telem_ctrl);

		ret = पूर्णांकel_scu_ipc_dev_command(scu, IOSS_TELEM,
					    IOSS_TELEM_EVENT_CTL_WRITE,
					    &telem_ctrl, माप(telem_ctrl),
					    शून्य, 0);
		अगर (ret) अणु
			pr_err("IOSS TELEM_CTRL Event Disable Write Failed\n");
			वापस ret;
		पूर्ण
		telm_conf->ioss_config.ssram_evts_used = 0;

		/* Configure Events */
		क्रम (idx = 0; idx < num_ioss_evts; idx++) अणु
			अगर (telemetry_plt_config_ioss_event(
			    telm_conf->ioss_config.telem_evts[idx].evt_id,
			    idx)) अणु
				pr_err("IOSS TELEM_RESET Fail for data: %x\n",
				telm_conf->ioss_config.telem_evts[idx].evt_id);
				जारी;
			पूर्ण
			telm_conf->ioss_config.ssram_evts_used++;
		पूर्ण
	पूर्ण

	/* Re-Configure Everything */
	अगर (action == TELEM_UPDATE) अणु
		/* Clear All Events */
		TELEM_CLEAR_EVENTS(telem_ctrl);

		ret = पूर्णांकel_scu_ipc_dev_command(scu, IOSS_TELEM,
					    IOSS_TELEM_EVENT_CTL_WRITE,
					    &telem_ctrl, माप(telem_ctrl),
					    शून्य, 0);
		अगर (ret) अणु
			pr_err("IOSS TELEM_CTRL Event Disable Write Failed\n");
			वापस ret;
		पूर्ण
		telm_conf->ioss_config.ssram_evts_used = 0;

		/* Configure Events */
		क्रम (index = 0; index < num_ioss_evts; index++) अणु
			telm_conf->ioss_config.telem_evts[index].evt_id =
			ioss_evपंचांगap[index];

			अगर (telemetry_plt_config_ioss_event(
			    telm_conf->ioss_config.telem_evts[index].evt_id,
			    index)) अणु
				pr_err("IOSS TELEM_UPDATE Fail for Evt%x\n",
					ioss_evपंचांगap[index]);
				जारी;
			पूर्ण
			telm_conf->ioss_config.ssram_evts_used++;
		पूर्ण
	पूर्ण

	/* Add some Events */
	अगर (action == TELEM_ADD) अणु
		/* Configure Events */
		क्रम (index = telm_conf->ioss_config.ssram_evts_used, idx = 0;
		     idx < num_ioss_evts; index++, idx++) अणु
			telm_conf->ioss_config.telem_evts[index].evt_id =
			ioss_evपंचांगap[idx];

			अगर (telemetry_plt_config_ioss_event(
			    telm_conf->ioss_config.telem_evts[index].evt_id,
			    index)) अणु
				pr_err("IOSS TELEM_ADD Fail for Event %x\n",
					ioss_evपंचांगap[idx]);
				जारी;
			पूर्ण
			telm_conf->ioss_config.ssram_evts_used++;
		पूर्ण
	पूर्ण

	/* Enable Periodic Telemetry Events and enable SRAM trace */
	TELEM_CLEAR_SAMPLE_PERIOD(telem_ctrl);
	TELEM_ENABLE_SRAM_EVT_TRACE(telem_ctrl);
	TELEM_ENABLE_PERIODIC(telem_ctrl);
	telem_ctrl |= ioss_period;

	ret = पूर्णांकel_scu_ipc_dev_command(scu, IOSS_TELEM,
				    IOSS_TELEM_EVENT_CTL_WRITE,
				    &telem_ctrl, माप(telem_ctrl), शून्य, 0);
	अगर (ret) अणु
		pr_err("IOSS TELEM_CTRL Event Enable Write Failed\n");
		वापस ret;
	पूर्ण

	telm_conf->ioss_config.curr_period = ioss_period;

	वापस 0;
पूर्ण


अटल पूर्णांक telemetry_setup_pssevtconfig(काष्ठा telemetry_evtconfig evtconfig,
					क्रमागत telemetry_action action)
अणु
	u8 num_pss_evts, pss_period;
	पूर्णांक ret, index, idx;
	u32 *pss_evपंचांगap;
	u32 telem_ctrl;

	num_pss_evts = evtconfig.num_evts;
	pss_period = evtconfig.period;
	pss_evपंचांगap = evtconfig.evपंचांगap;

	/* PSS Config */
	/* Get telemetry EVENT CTL */
	ret = पूर्णांकel_punit_ipc_command(IPC_PUNIT_BIOS_READ_TELE_EVENT_CTRL,
				      0, 0, शून्य, &telem_ctrl);
	अगर (ret) अणु
		pr_err("PSS TELEM_CTRL Read Failed\n");
		वापस ret;
	पूर्ण

	/* Disable Telemetry */
	TELEM_DISABLE(telem_ctrl);
	ret = पूर्णांकel_punit_ipc_command(IPC_PUNIT_BIOS_WRITE_TELE_EVENT_CTRL,
				      0, 0, &telem_ctrl, शून्य);
	अगर (ret) अणु
		pr_err("PSS TELEM_CTRL Event Disable Write Failed\n");
		वापस ret;
	पूर्ण

	/* Reset Everything */
	अगर (action == TELEM_RESET) अणु
		/* Clear All Events */
		TELEM_CLEAR_EVENTS(telem_ctrl);

		ret = पूर्णांकel_punit_ipc_command(
				IPC_PUNIT_BIOS_WRITE_TELE_EVENT_CTRL,
				0, 0, &telem_ctrl, शून्य);
		अगर (ret) अणु
			pr_err("PSS TELEM_CTRL Event Disable Write Failed\n");
			वापस ret;
		पूर्ण
		telm_conf->pss_config.ssram_evts_used = 0;
		/* Configure Events */
		क्रम (idx = 0; idx < num_pss_evts; idx++) अणु
			अगर (telemetry_plt_config_pss_event(
			    telm_conf->pss_config.telem_evts[idx].evt_id,
			    idx)) अणु
				pr_err("PSS TELEM_RESET Fail for Event %x\n",
				telm_conf->pss_config.telem_evts[idx].evt_id);
				जारी;
			पूर्ण
			telm_conf->pss_config.ssram_evts_used++;
		पूर्ण
	पूर्ण

	/* Re-Configure Everything */
	अगर (action == TELEM_UPDATE) अणु
		/* Clear All Events */
		TELEM_CLEAR_EVENTS(telem_ctrl);

		ret = पूर्णांकel_punit_ipc_command(
				IPC_PUNIT_BIOS_WRITE_TELE_EVENT_CTRL,
				0, 0, &telem_ctrl, शून्य);
		अगर (ret) अणु
			pr_err("PSS TELEM_CTRL Event Disable Write Failed\n");
			वापस ret;
		पूर्ण
		telm_conf->pss_config.ssram_evts_used = 0;

		/* Configure Events */
		क्रम (index = 0; index < num_pss_evts; index++) अणु
			telm_conf->pss_config.telem_evts[index].evt_id =
			pss_evपंचांगap[index];

			अगर (telemetry_plt_config_pss_event(
			    telm_conf->pss_config.telem_evts[index].evt_id,
			    index)) अणु
				pr_err("PSS TELEM_UPDATE Fail for Event %x\n",
					pss_evपंचांगap[index]);
				जारी;
			पूर्ण
			telm_conf->pss_config.ssram_evts_used++;
		पूर्ण
	पूर्ण

	/* Add some Events */
	अगर (action == TELEM_ADD) अणु
		/* Configure Events */
		क्रम (index = telm_conf->pss_config.ssram_evts_used, idx = 0;
		     idx < num_pss_evts; index++, idx++) अणु

			telm_conf->pss_config.telem_evts[index].evt_id =
			pss_evपंचांगap[idx];

			अगर (telemetry_plt_config_pss_event(
			    telm_conf->pss_config.telem_evts[index].evt_id,
			    index)) अणु
				pr_err("PSS TELEM_ADD Fail for Event %x\n",
					pss_evपंचांगap[idx]);
				जारी;
			पूर्ण
			telm_conf->pss_config.ssram_evts_used++;
		पूर्ण
	पूर्ण

	/* Enable Periodic Telemetry Events and enable SRAM trace */
	TELEM_CLEAR_SAMPLE_PERIOD(telem_ctrl);
	TELEM_ENABLE_SRAM_EVT_TRACE(telem_ctrl);
	TELEM_ENABLE_PERIODIC(telem_ctrl);
	telem_ctrl |= pss_period;

	ret = पूर्णांकel_punit_ipc_command(IPC_PUNIT_BIOS_WRITE_TELE_EVENT_CTRL,
				      0, 0, &telem_ctrl, शून्य);
	अगर (ret) अणु
		pr_err("PSS TELEM_CTRL Event Enable Write Failed\n");
		वापस ret;
	पूर्ण

	telm_conf->pss_config.curr_period = pss_period;

	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_setup_evtconfig(काष्ठा telemetry_evtconfig pss_evtconfig,
				     काष्ठा telemetry_evtconfig ioss_evtconfig,
				     क्रमागत telemetry_action action)
अणु
	पूर्णांक ret;

	mutex_lock(&(telm_conf->telem_lock));

	अगर ((action == TELEM_UPDATE) && (telm_conf->telem_in_use)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = telemetry_check_evtid(TELEM_PSS, pss_evtconfig.evपंचांगap,
				    pss_evtconfig.num_evts, action);
	अगर (ret)
		जाओ out;

	ret = telemetry_check_evtid(TELEM_IOSS, ioss_evtconfig.evपंचांगap,
				    ioss_evtconfig.num_evts, action);
	अगर (ret)
		जाओ out;

	अगर (ioss_evtconfig.num_evts) अणु
		ret = telemetry_setup_iossevtconfig(ioss_evtconfig, action);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (pss_evtconfig.num_evts) अणु
		ret = telemetry_setup_pssevtconfig(pss_evtconfig, action);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर ((action == TELEM_UPDATE) || (action == TELEM_ADD))
		telm_conf->telem_in_use = true;
	अन्यथा
		telm_conf->telem_in_use = false;

out:
	mutex_unlock(&(telm_conf->telem_lock));
	वापस ret;
पूर्ण

अटल पूर्णांक telemetry_setup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा telemetry_evtconfig pss_evtconfig, ioss_evtconfig;
	u32 पढ़ो_buf, events, event_regs;
	पूर्णांक ret;

	ret = पूर्णांकel_scu_ipc_dev_command(telm_conf->scu, IOSS_TELEM,
					IOSS_TELEM_INFO_READ, शून्य, 0,
					&पढ़ो_buf, माप(पढ़ो_buf));
	अगर (ret) अणु
		dev_err(&pdev->dev, "IOSS TELEM_INFO Read Failed\n");
		वापस ret;
	पूर्ण

	/* Get telemetry Info */
	events = (पढ़ो_buf & TELEM_INFO_SRAMEVTS_MASK) >>
		  TELEM_INFO_SRAMEVTS_SHIFT;
	event_regs = पढ़ो_buf & TELEM_INFO_NENABLES_MASK;
	अगर ((events < TELEM_MAX_EVENTS_SRAM) ||
	    (event_regs < TELEM_MAX_EVENTS_SRAM)) अणु
		dev_err(&pdev->dev, "IOSS:Insufficient Space for SRAM Trace\n");
		dev_err(&pdev->dev, "SRAM Events %d; Event Regs %d\n",
			events, event_regs);
		वापस -ENOMEM;
	पूर्ण

	telm_conf->ioss_config.min_period = TELEM_MIN_PERIOD(पढ़ो_buf);
	telm_conf->ioss_config.max_period = TELEM_MAX_PERIOD(पढ़ो_buf);

	/* PUNIT Mailbox Setup */
	ret = पूर्णांकel_punit_ipc_command(IPC_PUNIT_BIOS_READ_TELE_INFO, 0, 0,
				      शून्य, &पढ़ो_buf);
	अगर (ret) अणु
		dev_err(&pdev->dev, "PSS TELEM_INFO Read Failed\n");
		वापस ret;
	पूर्ण

	/* Get telemetry Info */
	events = (पढ़ो_buf & TELEM_INFO_SRAMEVTS_MASK) >>
		  TELEM_INFO_SRAMEVTS_SHIFT;
	event_regs = पढ़ो_buf & TELEM_INFO_SRAMEVTS_MASK;
	अगर ((events < TELEM_MAX_EVENTS_SRAM) ||
	    (event_regs < TELEM_MAX_EVENTS_SRAM)) अणु
		dev_err(&pdev->dev, "PSS:Insufficient Space for SRAM Trace\n");
		dev_err(&pdev->dev, "SRAM Events %d; Event Regs %d\n",
			events, event_regs);
		वापस -ENOMEM;
	पूर्ण

	telm_conf->pss_config.min_period = TELEM_MIN_PERIOD(पढ़ो_buf);
	telm_conf->pss_config.max_period = TELEM_MAX_PERIOD(पढ़ो_buf);

	pss_evtconfig.evपंचांगap = शून्य;
	pss_evtconfig.num_evts = TELEM_MAX_OS_ALLOCATED_EVENTS;
	pss_evtconfig.period = TELEM_SAMPLING_DEFAULT_PERIOD;

	ioss_evtconfig.evपंचांगap = शून्य;
	ioss_evtconfig.num_evts = TELEM_MAX_OS_ALLOCATED_EVENTS;
	ioss_evtconfig.period = TELEM_SAMPLING_DEFAULT_PERIOD;

	ret = telemetry_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TELEM_RESET);
	अगर (ret) अणु
		dev_err(&pdev->dev, "TELEMETRY Setup Failed\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक telemetry_plt_update_events(काष्ठा telemetry_evtconfig pss_evtconfig,
				काष्ठा telemetry_evtconfig ioss_evtconfig)
अणु
	पूर्णांक ret;

	अगर ((pss_evtconfig.num_evts > 0) &&
	    (TELEM_SAMPLE_PERIOD_INVALID(pss_evtconfig.period))) अणु
		pr_err("PSS Sampling Period Out of Range\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((ioss_evtconfig.num_evts > 0) &&
	    (TELEM_SAMPLE_PERIOD_INVALID(ioss_evtconfig.period))) अणु
		pr_err("IOSS Sampling Period Out of Range\n");
		वापस -EINVAL;
	पूर्ण

	ret = telemetry_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TELEM_UPDATE);
	अगर (ret)
		pr_err("TELEMETRY Config Failed\n");

	वापस ret;
पूर्ण


अटल पूर्णांक telemetry_plt_set_sampling_period(u8 pss_period, u8 ioss_period)
अणु
	u32 telem_ctrl = 0;
	पूर्णांक ret = 0;

	mutex_lock(&(telm_conf->telem_lock));
	अगर (ioss_period) अणु
		काष्ठा पूर्णांकel_scu_ipc_dev *scu = telm_conf->scu;

		अगर (TELEM_SAMPLE_PERIOD_INVALID(ioss_period)) अणु
			pr_err("IOSS Sampling Period Out of Range\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/* Get telemetry EVENT CTL */
		ret = पूर्णांकel_scu_ipc_dev_command(scu, IOSS_TELEM,
					    IOSS_TELEM_EVENT_CTL_READ, शून्य, 0,
					    &telem_ctrl, माप(telem_ctrl));
		अगर (ret) अणु
			pr_err("IOSS TELEM_CTRL Read Failed\n");
			जाओ out;
		पूर्ण

		/* Disable Telemetry */
		TELEM_DISABLE(telem_ctrl);

		ret = पूर्णांकel_scu_ipc_dev_command(scu, IOSS_TELEM,
						IOSS_TELEM_EVENT_CTL_WRITE,
						&telem_ctrl, माप(telem_ctrl),
						शून्य, 0);
		अगर (ret) अणु
			pr_err("IOSS TELEM_CTRL Event Disable Write Failed\n");
			जाओ out;
		पूर्ण

		/* Enable Periodic Telemetry Events and enable SRAM trace */
		TELEM_CLEAR_SAMPLE_PERIOD(telem_ctrl);
		TELEM_ENABLE_SRAM_EVT_TRACE(telem_ctrl);
		TELEM_ENABLE_PERIODIC(telem_ctrl);
		telem_ctrl |= ioss_period;

		ret = पूर्णांकel_scu_ipc_dev_command(scu, IOSS_TELEM,
						IOSS_TELEM_EVENT_CTL_WRITE,
						&telem_ctrl, माप(telem_ctrl),
						शून्य, 0);
		अगर (ret) अणु
			pr_err("IOSS TELEM_CTRL Event Enable Write Failed\n");
			जाओ out;
		पूर्ण
		telm_conf->ioss_config.curr_period = ioss_period;
	पूर्ण

	अगर (pss_period) अणु
		अगर (TELEM_SAMPLE_PERIOD_INVALID(pss_period)) अणु
			pr_err("PSS Sampling Period Out of Range\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/* Get telemetry EVENT CTL */
		ret = पूर्णांकel_punit_ipc_command(
				IPC_PUNIT_BIOS_READ_TELE_EVENT_CTRL,
				0, 0, शून्य, &telem_ctrl);
		अगर (ret) अणु
			pr_err("PSS TELEM_CTRL Read Failed\n");
			जाओ out;
		पूर्ण

		/* Disable Telemetry */
		TELEM_DISABLE(telem_ctrl);
		ret = पूर्णांकel_punit_ipc_command(
				IPC_PUNIT_BIOS_WRITE_TELE_EVENT_CTRL,
				0, 0, &telem_ctrl, शून्य);
		अगर (ret) अणु
			pr_err("PSS TELEM_CTRL Event Disable Write Failed\n");
			जाओ out;
		पूर्ण

		/* Enable Periodic Telemetry Events and enable SRAM trace */
		TELEM_CLEAR_SAMPLE_PERIOD(telem_ctrl);
		TELEM_ENABLE_SRAM_EVT_TRACE(telem_ctrl);
		TELEM_ENABLE_PERIODIC(telem_ctrl);
		telem_ctrl |= pss_period;

		ret = पूर्णांकel_punit_ipc_command(
				IPC_PUNIT_BIOS_WRITE_TELE_EVENT_CTRL,
				0, 0, &telem_ctrl, शून्य);
		अगर (ret) अणु
			pr_err("PSS TELEM_CTRL Event Enable Write Failed\n");
			जाओ out;
		पूर्ण
		telm_conf->pss_config.curr_period = pss_period;
	पूर्ण

out:
	mutex_unlock(&(telm_conf->telem_lock));
	वापस ret;
पूर्ण


अटल पूर्णांक telemetry_plt_get_sampling_period(u8 *pss_min_period,
					     u8 *pss_max_period,
					     u8 *ioss_min_period,
					     u8 *ioss_max_period)
अणु
	*pss_min_period = telm_conf->pss_config.min_period;
	*pss_max_period = telm_conf->pss_config.max_period;
	*ioss_min_period = telm_conf->ioss_config.min_period;
	*ioss_max_period = telm_conf->ioss_config.max_period;

	वापस 0;
पूर्ण


अटल पूर्णांक telemetry_plt_reset_events(व्योम)
अणु
	काष्ठा telemetry_evtconfig pss_evtconfig, ioss_evtconfig;
	पूर्णांक ret;

	pss_evtconfig.evपंचांगap = शून्य;
	pss_evtconfig.num_evts = TELEM_MAX_OS_ALLOCATED_EVENTS;
	pss_evtconfig.period = TELEM_SAMPLING_DEFAULT_PERIOD;

	ioss_evtconfig.evपंचांगap = शून्य;
	ioss_evtconfig.num_evts = TELEM_MAX_OS_ALLOCATED_EVENTS;
	ioss_evtconfig.period = TELEM_SAMPLING_DEFAULT_PERIOD;

	ret = telemetry_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TELEM_RESET);
	अगर (ret)
		pr_err("TELEMETRY Reset Failed\n");

	वापस ret;
पूर्ण


अटल पूर्णांक telemetry_plt_get_eventconfig(काष्ठा telemetry_evtconfig *pss_config,
					काष्ठा telemetry_evtconfig *ioss_config,
					पूर्णांक pss_len, पूर्णांक ioss_len)
अणु
	u32 *pss_evपंचांगap, *ioss_evपंचांगap;
	u32 index;

	pss_evपंचांगap = pss_config->evपंचांगap;
	ioss_evपंचांगap = ioss_config->evपंचांगap;

	mutex_lock(&(telm_conf->telem_lock));
	pss_config->num_evts = telm_conf->pss_config.ssram_evts_used;
	ioss_config->num_evts = telm_conf->ioss_config.ssram_evts_used;

	pss_config->period = telm_conf->pss_config.curr_period;
	ioss_config->period = telm_conf->ioss_config.curr_period;

	अगर ((pss_len < telm_conf->pss_config.ssram_evts_used) ||
	    (ioss_len < telm_conf->ioss_config.ssram_evts_used)) अणु
		mutex_unlock(&(telm_conf->telem_lock));
		वापस -EINVAL;
	पूर्ण

	क्रम (index = 0; index < telm_conf->pss_config.ssram_evts_used;
	     index++) अणु
		pss_evपंचांगap[index] =
		telm_conf->pss_config.telem_evts[index].evt_id;
	पूर्ण

	क्रम (index = 0; index < telm_conf->ioss_config.ssram_evts_used;
	     index++) अणु
		ioss_evपंचांगap[index] =
		telm_conf->ioss_config.telem_evts[index].evt_id;
	पूर्ण

	mutex_unlock(&(telm_conf->telem_lock));
	वापस 0;
पूर्ण


अटल पूर्णांक telemetry_plt_add_events(u8 num_pss_evts, u8 num_ioss_evts,
				    u32 *pss_evपंचांगap, u32 *ioss_evपंचांगap)
अणु
	काष्ठा telemetry_evtconfig pss_evtconfig, ioss_evtconfig;
	पूर्णांक ret;

	pss_evtconfig.evपंचांगap = pss_evपंचांगap;
	pss_evtconfig.num_evts = num_pss_evts;
	pss_evtconfig.period = telm_conf->pss_config.curr_period;

	ioss_evtconfig.evपंचांगap = ioss_evपंचांगap;
	ioss_evtconfig.num_evts = num_ioss_evts;
	ioss_evtconfig.period = telm_conf->ioss_config.curr_period;

	ret = telemetry_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TELEM_ADD);
	अगर (ret)
		pr_err("TELEMETRY ADD Failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक telem_evtlog_पढ़ो(क्रमागत telemetry_unit telem_unit,
			     काष्ठा telem_ssram_region *ssram_region, u8 len)
अणु
	काष्ठा telemetry_unit_config *unit_config;
	u64 बारtamp_prev, बारtamp_next;
	पूर्णांक ret, index, समयout = 0;

	ret = telem_get_unitconfig(telem_unit, &unit_config);
	अगर (ret < 0)
		वापस ret;

	अगर (len > unit_config->ssram_evts_used)
		len = unit_config->ssram_evts_used;

	करो अणु
		बारtamp_prev = पढ़ोq(unit_config->regmap);
		अगर (!बारtamp_prev) अणु
			pr_err("Ssram under update. Please Try Later\n");
			वापस -EBUSY;
		पूर्ण

		ssram_region->start_समय = पढ़ोq(unit_config->regmap +
						 TELEM_SSRAM_STARTTIME_OFFSET);

		क्रम (index = 0; index < len; index++) अणु
			ssram_region->events[index] =
			पढ़ोq(unit_config->regmap + TELEM_SSRAM_EVTLOG_OFFSET +
			      BYTES_PER_LONG*index);
		पूर्ण

		बारtamp_next = पढ़ोq(unit_config->regmap);
		अगर (!बारtamp_next) अणु
			pr_err("Ssram under update. Please Try Later\n");
			वापस -EBUSY;
		पूर्ण

		अगर (समयout++ > TELEM_SSRAM_READ_TIMEOUT) अणु
			pr_err("Timeout while reading Events\n");
			वापस -EBUSY;
		पूर्ण

	पूर्ण जबतक (बारtamp_prev != बारtamp_next);

	ssram_region->बारtamp = बारtamp_next;

	वापस len;
पूर्ण

अटल पूर्णांक telemetry_plt_raw_पढ़ो_eventlog(क्रमागत telemetry_unit telem_unit,
					   काष्ठा telemetry_evtlog *evtlog,
					   पूर्णांक len, पूर्णांक log_all_evts)
अणु
	पूर्णांक index, idx1, ret, पढ़ोlen = len;
	काष्ठा telem_ssram_region ssram_region;
	काष्ठा telemetry_evपंचांगap *evपंचांगap;

	चयन (telem_unit)	अणु
	हाल TELEM_PSS:
		evपंचांगap = telm_conf->pss_config.telem_evts;
		अवरोध;

	हाल TELEM_IOSS:
		evपंचांगap = telm_conf->ioss_config.telem_evts;
		अवरोध;

	शेष:
		pr_err("Unknown Telemetry Unit Specified %d\n", telem_unit);
		वापस -EINVAL;
	पूर्ण

	अगर (!log_all_evts)
		पढ़ोlen = TELEM_MAX_EVENTS_SRAM;

	ret = telem_evtlog_पढ़ो(telem_unit, &ssram_region, पढ़ोlen);
	अगर (ret < 0)
		वापस ret;

	/* Invalid evt-id array specअगरied via length mismatch */
	अगर ((!log_all_evts) && (len > ret))
		वापस -EINVAL;

	अगर (log_all_evts)
		क्रम (index = 0; index < ret; index++) अणु
			evtlog[index].telem_evtlog = ssram_region.events[index];
			evtlog[index].telem_evtid = evपंचांगap[index].evt_id;
		पूर्ण
	अन्यथा
		क्रम (index = 0, पढ़ोlen = 0; (index < ret) && (पढ़ोlen < len);
		     index++) अणु
			क्रम (idx1 = 0; idx1 < len; idx1++) अणु
				/* Elements matched */
				अगर (evपंचांगap[index].evt_id ==
				    evtlog[idx1].telem_evtid) अणु
					evtlog[idx1].telem_evtlog =
					ssram_region.events[index];
					पढ़ोlen++;

					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

	वापस पढ़ोlen;
पूर्ण

अटल पूर्णांक telemetry_plt_पढ़ो_eventlog(क्रमागत telemetry_unit telem_unit,
		काष्ठा telemetry_evtlog *evtlog, पूर्णांक len, पूर्णांक log_all_evts)
अणु
	पूर्णांक ret;

	mutex_lock(&(telm_conf->telem_lock));
	ret = telemetry_plt_raw_पढ़ो_eventlog(telem_unit, evtlog,
					      len, log_all_evts);
	mutex_unlock(&(telm_conf->telem_lock));

	वापस ret;
पूर्ण

अटल पूर्णांक telemetry_plt_get_trace_verbosity(क्रमागत telemetry_unit telem_unit,
					     u32 *verbosity)
अणु
	u32 temp = 0;
	पूर्णांक ret;

	अगर (verbosity == शून्य)
		वापस -EINVAL;

	mutex_lock(&(telm_conf->telem_trace_lock));
	चयन (telem_unit) अणु
	हाल TELEM_PSS:
		ret = पूर्णांकel_punit_ipc_command(
				IPC_PUNIT_BIOS_READ_TELE_TRACE_CTRL,
				0, 0, शून्य, &temp);
		अगर (ret) अणु
			pr_err("PSS TRACE_CTRL Read Failed\n");
			जाओ out;
		पूर्ण

		अवरोध;

	हाल TELEM_IOSS:
		ret = पूर्णांकel_scu_ipc_dev_command(telm_conf->scu,
				IOSS_TELEM, IOSS_TELEM_TRACE_CTL_READ,
				शून्य, 0, &temp, माप(temp));
		अगर (ret) अणु
			pr_err("IOSS TRACE_CTL Read Failed\n");
			जाओ out;
		पूर्ण

		अवरोध;

	शेष:
		pr_err("Unknown Telemetry Unit Specified %d\n", telem_unit);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	TELEM_EXTRACT_VERBOSITY(temp, *verbosity);

out:
	mutex_unlock(&(telm_conf->telem_trace_lock));
	वापस ret;
पूर्ण

अटल पूर्णांक telemetry_plt_set_trace_verbosity(क्रमागत telemetry_unit telem_unit,
					     u32 verbosity)
अणु
	u32 temp = 0;
	पूर्णांक ret;

	verbosity &= TELEM_TRC_VERBOSITY_MASK;

	mutex_lock(&(telm_conf->telem_trace_lock));
	चयन (telem_unit) अणु
	हाल TELEM_PSS:
		ret = पूर्णांकel_punit_ipc_command(
				IPC_PUNIT_BIOS_READ_TELE_TRACE_CTRL,
				0, 0, शून्य, &temp);
		अगर (ret) अणु
			pr_err("PSS TRACE_CTRL Read Failed\n");
			जाओ out;
		पूर्ण

		TELEM_CLEAR_VERBOSITY_BITS(temp);
		TELEM_SET_VERBOSITY_BITS(temp, verbosity);

		ret = पूर्णांकel_punit_ipc_command(
				IPC_PUNIT_BIOS_WRITE_TELE_TRACE_CTRL,
				0, 0, &temp, शून्य);
		अगर (ret) अणु
			pr_err("PSS TRACE_CTRL Verbosity Set Failed\n");
			जाओ out;
		पूर्ण
		अवरोध;

	हाल TELEM_IOSS:
		ret = पूर्णांकel_scu_ipc_dev_command(telm_conf->scu, IOSS_TELEM,
						IOSS_TELEM_TRACE_CTL_READ,
						शून्य, 0, &temp, माप(temp));
		अगर (ret) अणु
			pr_err("IOSS TRACE_CTL Read Failed\n");
			जाओ out;
		पूर्ण

		TELEM_CLEAR_VERBOSITY_BITS(temp);
		TELEM_SET_VERBOSITY_BITS(temp, verbosity);

		ret = पूर्णांकel_scu_ipc_dev_command(telm_conf->scu, IOSS_TELEM,
						IOSS_TELEM_TRACE_CTL_WRITE,
						&temp, माप(temp), शून्य, 0);
		अगर (ret) अणु
			pr_err("IOSS TRACE_CTL Verbosity Set Failed\n");
			जाओ out;
		पूर्ण
		अवरोध;

	शेष:
		pr_err("Unknown Telemetry Unit Specified %d\n", telem_unit);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&(telm_conf->telem_trace_lock));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा telemetry_core_ops telm_pltops = अणु
	.get_trace_verbosity = telemetry_plt_get_trace_verbosity,
	.set_trace_verbosity = telemetry_plt_set_trace_verbosity,
	.set_sampling_period = telemetry_plt_set_sampling_period,
	.get_sampling_period = telemetry_plt_get_sampling_period,
	.raw_पढ़ो_eventlog = telemetry_plt_raw_पढ़ो_eventlog,
	.get_eventconfig = telemetry_plt_get_eventconfig,
	.update_events = telemetry_plt_update_events,
	.पढ़ो_eventlog = telemetry_plt_पढ़ो_eventlog,
	.reset_events = telemetry_plt_reset_events,
	.add_events = telemetry_plt_add_events,
पूर्ण;

अटल पूर्णांक telemetry_pltdrv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	व्योम __iomem *mem;
	पूर्णांक ret;

	id = x86_match_cpu(telemetry_cpu_ids);
	अगर (!id)
		वापस -ENODEV;

	telm_conf = (काष्ठा telemetry_plt_config *)id->driver_data;

	telm_conf->pmc = dev_get_drvdata(pdev->dev.parent);

	mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	telm_conf->pss_config.regmap = mem;

	mem = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	telm_conf->ioss_config.regmap = mem;

	telm_conf->scu = devm_पूर्णांकel_scu_ipc_dev_get(&pdev->dev);
	अगर (!telm_conf->scu) अणु
		ret = -EPROBE_DEFER;
		जाओ out;
	पूर्ण

	mutex_init(&telm_conf->telem_lock);
	mutex_init(&telm_conf->telem_trace_lock);

	ret = telemetry_setup(pdev);
	अगर (ret)
		जाओ out;

	ret = telemetry_set_pltdata(&telm_pltops, telm_conf);
	अगर (ret) अणु
		dev_err(&pdev->dev, "TELEMETRY Set Pltops Failed.\n");
		जाओ out;
	पूर्ण

	वापस 0;

out:
	dev_err(&pdev->dev, "TELEMETRY Setup Failed.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक telemetry_pltdrv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	telemetry_clear_pltdata();
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver telemetry_soc_driver = अणु
	.probe		= telemetry_pltdrv_probe,
	.हटाओ		= telemetry_pltdrv_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init telemetry_module_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&telemetry_soc_driver);
पूर्ण

अटल व्योम __निकास telemetry_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&telemetry_soc_driver);
पूर्ण

device_initcall(telemetry_module_init);
module_निकास(telemetry_module_निकास);

MODULE_AUTHOR("Souvik Kumar Chakravarty <souvik.k.chakravarty@intel.com>");
MODULE_DESCRIPTION("Intel SoC Telemetry Platform Driver");
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
