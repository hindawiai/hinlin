<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2010,2011      Thomas Renninger <trenn@suse.de>, Novell Inc.
 *
 *  PCI initialization based on example code from:
 *  Andreas Herrmann <andreas.herrmann3@amd.com>
 */

#अगर defined(__i386__) || defined(__x86_64__)

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <समय.स>
#समावेश <माला.स>

#समावेश <pci/pci.h>

#समावेश "idle_monitor/cpupower-monitor.h"
#समावेश "helpers/helpers.h"

#घोषणा PCI_NON_PC0_OFFSET	0xb0
#घोषणा PCI_PC1_OFFSET		0xb4
#घोषणा PCI_PC6_OFFSET		0xb8

#घोषणा PCI_MONITOR_ENABLE_REG  0xe0

#घोषणा PCI_NON_PC0_ENABLE_BIT	0
#घोषणा PCI_PC1_ENABLE_BIT	1
#घोषणा PCI_PC6_ENABLE_BIT	2

#घोषणा PCI_NBP1_STAT_OFFSET	0x98
#घोषणा PCI_NBP1_ACTIVE_BIT	2
#घोषणा PCI_NBP1_ENTERED_BIT	1

#घोषणा PCI_NBP1_CAP_OFFSET	0x90
#घोषणा PCI_NBP1_CAPABLE_BIT    31

#घोषणा OVERFLOW_MS		343597 /* 32 bit रेजिस्टर filled at 12500 HZ
					  (1 tick per 80ns) */

क्रमागत amd_fam14h_states अणुNON_PC0 = 0, PC1, PC6, NBP1,
			AMD_FAM14H_STATE_NUMपूर्ण;

अटल पूर्णांक fam14h_get_count_percent(अचिन्हित पूर्णांक self_id, द्विगुन *percent,
				    अचिन्हित पूर्णांक cpu);
अटल पूर्णांक fam14h_nbp1_count(अचिन्हित पूर्णांक id, अचिन्हित दीर्घ दीर्घ *count,
			     अचिन्हित पूर्णांक cpu);

अटल cstate_t amd_fam14h_cstates[AMD_FAM14H_STATE_NUM] = अणु
	अणु
		.name			= "!PC0",
		.desc			= N_("Package in sleep state (PC1 or deeper)"),
		.id			= NON_PC0,
		.range			= RANGE_PACKAGE,
		.get_count_percent	= fam14h_get_count_percent,
	पूर्ण,
	अणु
		.name			= "PC1",
		.desc			= N_("Processor Package C1"),
		.id			= PC1,
		.range			= RANGE_PACKAGE,
		.get_count_percent	= fam14h_get_count_percent,
	पूर्ण,
	अणु
		.name			= "PC6",
		.desc			= N_("Processor Package C6"),
		.id			= PC6,
		.range			= RANGE_PACKAGE,
		.get_count_percent	= fam14h_get_count_percent,
	पूर्ण,
	अणु
		.name			= "NBP1",
		.desc			= N_("North Bridge P1 boolean counter (returns 0 or 1)"),
		.id			= NBP1,
		.range			= RANGE_PACKAGE,
		.get_count		= fam14h_nbp1_count,
	पूर्ण,
पूर्ण;

अटल काष्ठा pci_access *pci_acc;
अटल काष्ठा pci_dev *amd_fam14h_pci_dev;
अटल पूर्णांक nbp1_entered;

अटल काष्ठा बारpec start_समय;
अटल अचिन्हित दीर्घ दीर्घ समयdअगरf;

#अगर_घोषित DEBUG
काष्ठा बारpec dbg_समय;
दीर्घ dbg_समयdअगरf;
#पूर्ण_अगर

अटल अचिन्हित दीर्घ दीर्घ *previous_count[AMD_FAM14H_STATE_NUM];
अटल अचिन्हित दीर्घ दीर्घ *current_count[AMD_FAM14H_STATE_NUM];

अटल पूर्णांक amd_fam14h_get_pci_info(काष्ठा cstate *state,
				   अचिन्हित पूर्णांक *pci_offset,
				   अचिन्हित पूर्णांक *enable_bit,
				   अचिन्हित पूर्णांक cpu)
अणु
	चयन (state->id) अणु
	हाल NON_PC0:
		*enable_bit = PCI_NON_PC0_ENABLE_BIT;
		*pci_offset = PCI_NON_PC0_OFFSET;
		अवरोध;
	हाल PC1:
		*enable_bit = PCI_PC1_ENABLE_BIT;
		*pci_offset = PCI_PC1_OFFSET;
		अवरोध;
	हाल PC6:
		*enable_bit = PCI_PC6_ENABLE_BIT;
		*pci_offset = PCI_PC6_OFFSET;
		अवरोध;
	हाल NBP1:
		*enable_bit = PCI_NBP1_ENTERED_BIT;
		*pci_offset = PCI_NBP1_STAT_OFFSET;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक amd_fam14h_init(cstate_t *state, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक enable_bit, pci_offset, ret;
	uपूर्णांक32_t val;

	ret = amd_fam14h_get_pci_info(state, &pci_offset, &enable_bit, cpu);
	अगर (ret)
		वापस ret;

	/* NBP1 needs extra treating -> ग_लिखो 1 to D18F6x98 bit 1 क्रम init */
	अगर (state->id == NBP1) अणु
		val = pci_पढ़ो_दीर्घ(amd_fam14h_pci_dev, pci_offset);
		val |= 1 << enable_bit;
		val = pci_ग_लिखो_दीर्घ(amd_fam14h_pci_dev, pci_offset, val);
		वापस ret;
	पूर्ण

	/* Enable monitor */
	val = pci_पढ़ो_दीर्घ(amd_fam14h_pci_dev, PCI_MONITOR_ENABLE_REG);
	dprपूर्णांक("Init %s: read at offset: 0x%x val: %u\n", state->name,
	       PCI_MONITOR_ENABLE_REG, (अचिन्हित पूर्णांक) val);
	val |= 1 << enable_bit;
	pci_ग_लिखो_दीर्घ(amd_fam14h_pci_dev, PCI_MONITOR_ENABLE_REG, val);

	dprपूर्णांक("Init %s: offset: 0x%x enable_bit: %d - val: %u (%u)\n",
	       state->name, PCI_MONITOR_ENABLE_REG, enable_bit,
	       (अचिन्हित पूर्णांक) val, cpu);

	/* Set counter to zero */
	pci_ग_लिखो_दीर्घ(amd_fam14h_pci_dev, pci_offset, 0);
	previous_count[state->id][cpu] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक amd_fam14h_disable(cstate_t *state, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक enable_bit, pci_offset, ret;
	uपूर्णांक32_t val;

	ret = amd_fam14h_get_pci_info(state, &pci_offset, &enable_bit, cpu);
	अगर (ret)
		वापस ret;

	val = pci_पढ़ो_दीर्घ(amd_fam14h_pci_dev, pci_offset);
	dprपूर्णांक("%s: offset: 0x%x %u\n", state->name, pci_offset, val);
	अगर (state->id == NBP1) अणु
		/* was the bit whether NBP1 got entered set? */
		nbp1_entered = (val & (1 << PCI_NBP1_ACTIVE_BIT)) |
			(val & (1 << PCI_NBP1_ENTERED_BIT));

		dprपूर्णांक("NBP1 was %sentered - 0x%x - enable_bit: "
		       "%d - pci_offset: 0x%x\n",
		       nbp1_entered ? "" : "not ",
		       val, enable_bit, pci_offset);
		वापस ret;
	पूर्ण
	current_count[state->id][cpu] = val;

	dprपूर्णांक("%s: Current -  %llu (%u)\n", state->name,
	       current_count[state->id][cpu], cpu);
	dprपूर्णांक("%s: Previous - %llu (%u)\n", state->name,
	       previous_count[state->id][cpu], cpu);

	val = pci_पढ़ो_दीर्घ(amd_fam14h_pci_dev, PCI_MONITOR_ENABLE_REG);
	val &= ~(1 << enable_bit);
	pci_ग_लिखो_दीर्घ(amd_fam14h_pci_dev, PCI_MONITOR_ENABLE_REG, val);

	वापस 0;
पूर्ण

अटल पूर्णांक fam14h_nbp1_count(अचिन्हित पूर्णांक id, अचिन्हित दीर्घ दीर्घ *count,
			     अचिन्हित पूर्णांक cpu)
अणु
	अगर (id == NBP1) अणु
		अगर (nbp1_entered)
			*count = 1;
		अन्यथा
			*count = 0;
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण
अटल पूर्णांक fam14h_get_count_percent(अचिन्हित पूर्णांक id, द्विगुन *percent,
				    अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ dअगरf;

	अगर (id >= AMD_FAM14H_STATE_NUM)
		वापस -1;
	/* residency count in 80ns -> भागide through 12.5 to get us residency */
	dअगरf = current_count[id][cpu] - previous_count[id][cpu];

	अगर (समयdअगरf == 0)
		*percent = 0.0;
	अन्यथा
		*percent = 100.0 * dअगरf / समयdअगरf / 12.5;

	dprपूर्णांक("Timediff: %llu - res~: %lu us - percent: %.2f %%\n",
	       समयdअगरf, dअगरf * 10 / 125, *percent);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_fam14h_start(व्योम)
अणु
	पूर्णांक num, cpu;
	घड़ी_समय_लो(CLOCK_REALTIME, &start_समय);
	क्रम (num = 0; num < AMD_FAM14H_STATE_NUM; num++) अणु
		क्रम (cpu = 0; cpu < cpu_count; cpu++)
			amd_fam14h_init(&amd_fam14h_cstates[num], cpu);
	पूर्ण
#अगर_घोषित DEBUG
	घड़ी_समय_लो(CLOCK_REALTIME, &dbg_समय);
	dbg_समयdअगरf = बारpec_dअगरf_us(start_समय, dbg_समय);
	dprपूर्णांक("Enabling counters took: %lu us\n",
	       dbg_समयdअगरf);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक amd_fam14h_stop(व्योम)
अणु
	पूर्णांक num, cpu;
	काष्ठा बारpec end_समय;

	घड़ी_समय_लो(CLOCK_REALTIME, &end_समय);

	क्रम (num = 0; num < AMD_FAM14H_STATE_NUM; num++) अणु
		क्रम (cpu = 0; cpu < cpu_count; cpu++)
			amd_fam14h_disable(&amd_fam14h_cstates[num], cpu);
	पूर्ण
#अगर_घोषित DEBUG
	घड़ी_समय_लो(CLOCK_REALTIME, &dbg_समय);
	dbg_समयdअगरf = बारpec_dअगरf_us(end_समय, dbg_समय);
	dprपूर्णांक("Disabling counters took: %lu ns\n", dbg_समयdअगरf);
#पूर्ण_अगर
	समयdअगरf = बारpec_dअगरf_us(start_समय, end_समय);
	अगर (समयdअगरf / 1000 > OVERFLOW_MS)
		prपूर्णांक_overflow_err((अचिन्हित पूर्णांक)समयdअगरf / 1000000,
				   OVERFLOW_MS / 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक is_nbp1_capable(व्योम)
अणु
	uपूर्णांक32_t val;
	val = pci_पढ़ो_दीर्घ(amd_fam14h_pci_dev, PCI_NBP1_CAP_OFFSET);
	वापस val & (1 << 31);
पूर्ण

काष्ठा cpuidle_monitor *amd_fam14h_रेजिस्टर(व्योम)
अणु
	पूर्णांक num;

	अगर (cpuघातer_cpu_info.venकरोr != X86_VENDOR_AMD)
		वापस शून्य;

	अगर (cpuघातer_cpu_info.family == 0x14)
		म_नकलन(amd_fam14h_monitor.name, "Fam_14h",
			MONITOR_NAME_LEN - 1);
	अन्यथा अगर (cpuघातer_cpu_info.family == 0x12)
		म_नकलन(amd_fam14h_monitor.name, "Fam_12h",
			MONITOR_NAME_LEN - 1);
	अन्यथा
		वापस शून्य;

	/* We करो not alloc क्रम nbp1 machine wide counter */
	क्रम (num = 0; num < AMD_FAM14H_STATE_NUM - 1; num++) अणु
		previous_count[num] = सुस्मृति(cpu_count,
					      माप(अचिन्हित दीर्घ दीर्घ));
		current_count[num]  = सुस्मृति(cpu_count,
					      माप(अचिन्हित दीर्घ दीर्घ));
	पूर्ण

	/* We need PCI device: Slot 18, Func 6, compare with BKDG
	   क्रम fam 12h/14h */
	amd_fam14h_pci_dev = pci_slot_func_init(&pci_acc, 0x18, 6);
	अगर (amd_fam14h_pci_dev == शून्य || pci_acc == शून्य)
		वापस शून्य;

	अगर (!is_nbp1_capable())
		amd_fam14h_monitor.hw_states_num = AMD_FAM14H_STATE_NUM - 1;

	amd_fam14h_monitor.name_len = म_माप(amd_fam14h_monitor.name);
	वापस &amd_fam14h_monitor;
पूर्ण

अटल व्योम amd_fam14h_unरेजिस्टर(व्योम)
अणु
	पूर्णांक num;
	क्रम (num = 0; num < AMD_FAM14H_STATE_NUM - 1; num++) अणु
		मुक्त(previous_count[num]);
		मुक्त(current_count[num]);
	पूर्ण
	pci_cleanup(pci_acc);
पूर्ण

काष्ठा cpuidle_monitor amd_fam14h_monitor = अणु
	.name			= "",
	.hw_states		= amd_fam14h_cstates,
	.hw_states_num		= AMD_FAM14H_STATE_NUM,
	.start			= amd_fam14h_start,
	.stop			= amd_fam14h_stop,
	.करो_रेजिस्टर		= amd_fam14h_रेजिस्टर,
	.unरेजिस्टर		= amd_fam14h_unरेजिस्टर,
	.flags.needs_root	= 1,
	.overflow_s		= OVERFLOW_MS / 1000,
पूर्ण;
#पूर्ण_अगर /* #अगर defined(__i386__) || defined(__x86_64__) */
