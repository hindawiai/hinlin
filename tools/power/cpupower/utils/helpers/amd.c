<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर defined(__i386__) || defined(__x86_64__)
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>

#समावेश <pci/pci.h>

#समावेश "helpers/helpers.h"

#घोषणा MSR_AMD_PSTATE_STATUS	0xc0010063
#घोषणा MSR_AMD_PSTATE		0xc0010064
#घोषणा MSR_AMD_PSTATE_LIMIT	0xc0010061

जोड़ core_pstate अणु
	/* pre fam 17h: */
	काष्ठा अणु
		अचिन्हित fid:6;
		अचिन्हित did:3;
		अचिन्हित vid:7;
		अचिन्हित res1:6;
		अचिन्हित nbdid:1;
		अचिन्हित res2:2;
		अचिन्हित nbvid:7;
		अचिन्हित iddval:8;
		अचिन्हित iddभाग:2;
		अचिन्हित res3:21;
		अचिन्हित en:1;
	पूर्ण pstate;
	/* since fam 17h: */
	काष्ठा अणु
		अचिन्हित fid:8;
		अचिन्हित did:6;
		अचिन्हित vid:8;
		अचिन्हित iddval:8;
		अचिन्हित iddभाग:2;
		अचिन्हित res1:31;
		अचिन्हित en:1;
	पूर्ण pstatedef;
	अचिन्हित दीर्घ दीर्घ val;
पूर्ण;

अटल पूर्णांक get_did(जोड़ core_pstate pstate)
अणु
	पूर्णांक t;

	अगर (cpuघातer_cpu_info.caps & CPUPOWER_CAP_AMD_PSTATEDEF)
		t = pstate.pstatedef.did;
	अन्यथा अगर (cpuघातer_cpu_info.family == 0x12)
		t = pstate.val & 0xf;
	अन्यथा
		t = pstate.pstate.did;

	वापस t;
पूर्ण

अटल पूर्णांक get_cof(जोड़ core_pstate pstate)
अणु
	पूर्णांक t;
	पूर्णांक fid, did, cof;

	did = get_did(pstate);
	अगर (cpuघातer_cpu_info.caps & CPUPOWER_CAP_AMD_PSTATEDEF) अणु
		fid = pstate.pstatedef.fid;
		cof = 200 * fid / did;
	पूर्ण अन्यथा अणु
		t = 0x10;
		fid = pstate.pstate.fid;
		अगर (cpuघातer_cpu_info.family == 0x11)
			t = 0x8;
		cof = (100 * (fid + t)) >> did;
	पूर्ण
	वापस cof;
पूर्ण

/* Needs:
 * cpu          -> the cpu that माला_लो evaluated
 * boost_states -> how much boost states the machines support
 *
 * Fills up:
 * pstates -> a poपूर्णांकer to an array of size MAX_HW_PSTATES
 *            must be initialized with zeros.
 *            All available  HW pstates (including boost states)
 * no      -> amount of pstates above array got filled up with
 *
 * वापसs zero on success, -1 on failure
 */
पूर्णांक decode_pstates(अचिन्हित पूर्णांक cpu, पूर्णांक boost_states,
		   अचिन्हित दीर्घ *pstates, पूर्णांक *no)
अणु
	पूर्णांक i, psmax;
	जोड़ core_pstate pstate;
	अचिन्हित दीर्घ दीर्घ val;

	/* Only पढ़ो out frequencies from HW अगर HW Pstate is supported,
	 * otherwise frequencies are exported via ACPI tables.
	 */
	अगर (!(cpuघातer_cpu_info.caps & CPUPOWER_CAP_AMD_HW_PSTATE))
		वापस -1;

	अगर (पढ़ो_msr(cpu, MSR_AMD_PSTATE_LIMIT, &val))
		वापस -1;

	psmax = (val >> 4) & 0x7;
	psmax += boost_states;
	क्रम (i = 0; i <= psmax; i++) अणु
		अगर (i >= MAX_HW_PSTATES) अणु
			ख_लिखो(मानक_त्रुटि, "HW pstates [%d] exceeding max [%d]\n",
				psmax, MAX_HW_PSTATES);
			वापस -1;
		पूर्ण
		अगर (पढ़ो_msr(cpu, MSR_AMD_PSTATE + i, &pstate.val))
			वापस -1;

		/* The enabled bit (bit 63) is common क्रम all families */
		अगर (!pstate.pstatedef.en)
			जारी;

		pstates[i] = get_cof(pstate);
	पूर्ण
	*no = i;
	वापस 0;
पूर्ण

पूर्णांक amd_pci_get_num_boost_states(पूर्णांक *active, पूर्णांक *states)
अणु
	काष्ठा pci_access *pci_acc;
	काष्ठा pci_dev *device;
	uपूर्णांक8_t val = 0;

	*active = *states = 0;

	device = pci_slot_func_init(&pci_acc, 0x18, 4);

	अगर (device == शून्य)
		वापस -ENODEV;

	val = pci_पढ़ो_byte(device, 0x15c);
	अगर (val & 3)
		*active = 1;
	अन्यथा
		*active = 0;
	*states = (val >> 2) & 7;

	pci_cleanup(pci_acc);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* defined(__i386__) || defined(__x86_64__) */
