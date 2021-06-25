<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Enable PCIe link L0s/L1 state and Clock Power Management
 *
 * Copyright (C) 2007 Intel
 * Copyright (C) Zhang Yanmin (yanmin.zhang@पूर्णांकel.com)
 * Copyright (C) Shaohua Li (shaohua.li@पूर्णांकel.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pm.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>
#समावेश "../pci.h"

#अगर_घोषित MODULE_PARAM_PREFIX
#अघोषित MODULE_PARAM_PREFIX
#पूर्ण_अगर
#घोषणा MODULE_PARAM_PREFIX "pcie_aspm."

/* Note: those are not रेजिस्टर definitions */
#घोषणा ASPM_STATE_L0S_UP	(1)	/* Upstream direction L0s state */
#घोषणा ASPM_STATE_L0S_DW	(2)	/* Downstream direction L0s state */
#घोषणा ASPM_STATE_L1		(4)	/* L1 state */
#घोषणा ASPM_STATE_L1_1		(8)	/* ASPM L1.1 state */
#घोषणा ASPM_STATE_L1_2		(0x10)	/* ASPM L1.2 state */
#घोषणा ASPM_STATE_L1_1_PCIPM	(0x20)	/* PCI PM L1.1 state */
#घोषणा ASPM_STATE_L1_2_PCIPM	(0x40)	/* PCI PM L1.2 state */
#घोषणा ASPM_STATE_L1_SS_PCIPM	(ASPM_STATE_L1_1_PCIPM | ASPM_STATE_L1_2_PCIPM)
#घोषणा ASPM_STATE_L1_2_MASK	(ASPM_STATE_L1_2 | ASPM_STATE_L1_2_PCIPM)
#घोषणा ASPM_STATE_L1SS		(ASPM_STATE_L1_1 | ASPM_STATE_L1_1_PCIPM |\
				 ASPM_STATE_L1_2_MASK)
#घोषणा ASPM_STATE_L0S		(ASPM_STATE_L0S_UP | ASPM_STATE_L0S_DW)
#घोषणा ASPM_STATE_ALL		(ASPM_STATE_L0S | ASPM_STATE_L1 |	\
				 ASPM_STATE_L1SS)

काष्ठा aspm_latency अणु
	u32 l0s;			/* L0s latency (nsec) */
	u32 l1;				/* L1 latency (nsec) */
पूर्ण;

काष्ठा pcie_link_state अणु
	काष्ठा pci_dev *pdev;		/* Upstream component of the Link */
	काष्ठा pci_dev *करोwnstream;	/* Downstream component, function 0 */
	काष्ठा pcie_link_state *root;	/* poपूर्णांकer to the root port link */
	काष्ठा pcie_link_state *parent;	/* poपूर्णांकer to the parent Link state */
	काष्ठा list_head sibling;	/* node in link_list */

	/* ASPM state */
	u32 aspm_support:7;		/* Supported ASPM state */
	u32 aspm_enabled:7;		/* Enabled ASPM state */
	u32 aspm_capable:7;		/* Capable ASPM state with latency */
	u32 aspm_शेष:7;		/* Default ASPM state by BIOS */
	u32 aspm_disable:7;		/* Disabled ASPM state */

	/* Clock PM state */
	u32 clkpm_capable:1;		/* Clock PM capable? */
	u32 clkpm_enabled:1;		/* Current Clock PM state */
	u32 clkpm_शेष:1;		/* Default Clock PM state by BIOS */
	u32 clkpm_disable:1;		/* Clock PM disabled */

	/* Exit latencies */
	काष्ठा aspm_latency latency_up;	/* Upstream direction निकास latency */
	काष्ठा aspm_latency latency_dw;	/* Downstream direction निकास latency */
	/*
	 * Endpoपूर्णांक acceptable latencies. A pcie करोwnstream port only
	 * has one slot under it, so at most there are 8 functions.
	 */
	काष्ठा aspm_latency acceptable[8];
पूर्ण;

अटल पूर्णांक aspm_disabled, aspm_क्रमce;
अटल bool aspm_support_enabled = true;
अटल DEFINE_MUTEX(aspm_lock);
अटल LIST_HEAD(link_list);

#घोषणा POLICY_DEFAULT 0	/* BIOS शेष setting */
#घोषणा POLICY_PERFORMANCE 1	/* high perक्रमmance */
#घोषणा POLICY_POWERSAVE 2	/* high घातer saving */
#घोषणा POLICY_POWER_SUPERSAVE 3 /* possibly even more घातer saving */

#अगर_घोषित CONFIG_PCIEASPM_PERFORMANCE
अटल पूर्णांक aspm_policy = POLICY_PERFORMANCE;
#या_अगर defined CONFIG_PCIEASPM_POWERSAVE
अटल पूर्णांक aspm_policy = POLICY_POWERSAVE;
#या_अगर defined CONFIG_PCIEASPM_POWER_SUPERSAVE
अटल पूर्णांक aspm_policy = POLICY_POWER_SUPERSAVE;
#अन्यथा
अटल पूर्णांक aspm_policy;
#पूर्ण_अगर

अटल स्थिर अक्षर *policy_str[] = अणु
	[POLICY_DEFAULT] = "default",
	[POLICY_PERFORMANCE] = "performance",
	[POLICY_POWERSAVE] = "powersave",
	[POLICY_POWER_SUPERSAVE] = "powersupersave"
पूर्ण;

#घोषणा LINK_RETRAIN_TIMEOUT HZ

अटल पूर्णांक policy_to_aspm_state(काष्ठा pcie_link_state *link)
अणु
	चयन (aspm_policy) अणु
	हाल POLICY_PERFORMANCE:
		/* Disable ASPM and Clock PM */
		वापस 0;
	हाल POLICY_POWERSAVE:
		/* Enable ASPM L0s/L1 */
		वापस (ASPM_STATE_L0S | ASPM_STATE_L1);
	हाल POLICY_POWER_SUPERSAVE:
		/* Enable Everything */
		वापस ASPM_STATE_ALL;
	हाल POLICY_DEFAULT:
		वापस link->aspm_शेष;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक policy_to_clkpm_state(काष्ठा pcie_link_state *link)
अणु
	चयन (aspm_policy) अणु
	हाल POLICY_PERFORMANCE:
		/* Disable ASPM and Clock PM */
		वापस 0;
	हाल POLICY_POWERSAVE:
	हाल POLICY_POWER_SUPERSAVE:
		/* Enable Clock PM */
		वापस 1;
	हाल POLICY_DEFAULT:
		वापस link->clkpm_शेष;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pcie_set_clkpm_nocheck(काष्ठा pcie_link_state *link, पूर्णांक enable)
अणु
	काष्ठा pci_dev *child;
	काष्ठा pci_bus *linkbus = link->pdev->subordinate;
	u32 val = enable ? PCI_EXP_LNKCTL_CLKREQ_EN : 0;

	list_क्रम_each_entry(child, &linkbus->devices, bus_list)
		pcie_capability_clear_and_set_word(child, PCI_EXP_LNKCTL,
						   PCI_EXP_LNKCTL_CLKREQ_EN,
						   val);
	link->clkpm_enabled = !!enable;
पूर्ण

अटल व्योम pcie_set_clkpm(काष्ठा pcie_link_state *link, पूर्णांक enable)
अणु
	/*
	 * Don't enable Clock PM अगर the link is not Clock PM capable
	 * or Clock PM is disabled
	 */
	अगर (!link->clkpm_capable || link->clkpm_disable)
		enable = 0;
	/* Need nothing अगर the specअगरied equals to current state */
	अगर (link->clkpm_enabled == enable)
		वापस;
	pcie_set_clkpm_nocheck(link, enable);
पूर्ण

अटल व्योम pcie_clkpm_cap_init(काष्ठा pcie_link_state *link, पूर्णांक blacklist)
अणु
	पूर्णांक capable = 1, enabled = 1;
	u32 reg32;
	u16 reg16;
	काष्ठा pci_dev *child;
	काष्ठा pci_bus *linkbus = link->pdev->subordinate;

	/* All functions should have the same cap and state, take the worst */
	list_क्रम_each_entry(child, &linkbus->devices, bus_list) अणु
		pcie_capability_पढ़ो_dword(child, PCI_EXP_LNKCAP, &reg32);
		अगर (!(reg32 & PCI_EXP_LNKCAP_CLKPM)) अणु
			capable = 0;
			enabled = 0;
			अवरोध;
		पूर्ण
		pcie_capability_पढ़ो_word(child, PCI_EXP_LNKCTL, &reg16);
		अगर (!(reg16 & PCI_EXP_LNKCTL_CLKREQ_EN))
			enabled = 0;
	पूर्ण
	link->clkpm_enabled = enabled;
	link->clkpm_शेष = enabled;
	link->clkpm_capable = capable;
	link->clkpm_disable = blacklist ? 1 : 0;
पूर्ण

अटल bool pcie_retrain_link(काष्ठा pcie_link_state *link)
अणु
	काष्ठा pci_dev *parent = link->pdev;
	अचिन्हित दीर्घ end_jअगरfies;
	u16 reg16;

	pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKCTL, &reg16);
	reg16 |= PCI_EXP_LNKCTL_RL;
	pcie_capability_ग_लिखो_word(parent, PCI_EXP_LNKCTL, reg16);
	अगर (parent->clear_retrain_link) अणु
		/*
		 * Due to an erratum in some devices the Retrain Link bit
		 * needs to be cleared again manually to allow the link
		 * training to succeed.
		 */
		reg16 &= ~PCI_EXP_LNKCTL_RL;
		pcie_capability_ग_लिखो_word(parent, PCI_EXP_LNKCTL, reg16);
	पूर्ण

	/* Wait क्रम link training end. Break out after रुकोing क्रम समयout */
	end_jअगरfies = jअगरfies + LINK_RETRAIN_TIMEOUT;
	करो अणु
		pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKSTA, &reg16);
		अगर (!(reg16 & PCI_EXP_LNKSTA_LT))
			अवरोध;
		msleep(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_jअगरfies));
	वापस !(reg16 & PCI_EXP_LNKSTA_LT);
पूर्ण

/*
 * pcie_aspm_configure_common_घड़ी: check अगर the 2 ends of a link
 *   could use common घड़ी. If they are, configure them to use the
 *   common घड़ी. That will reduce the ASPM state निकास latency.
 */
अटल व्योम pcie_aspm_configure_common_घड़ी(काष्ठा pcie_link_state *link)
अणु
	पूर्णांक same_घड़ी = 1;
	u16 reg16, parent_reg, child_reg[8];
	काष्ठा pci_dev *child, *parent = link->pdev;
	काष्ठा pci_bus *linkbus = parent->subordinate;
	/*
	 * All functions of a slot should have the same Slot Clock
	 * Configuration, so just check one function
	 */
	child = list_entry(linkbus->devices.next, काष्ठा pci_dev, bus_list);
	BUG_ON(!pci_is_pcie(child));

	/* Check करोwnstream component अगर bit Slot Clock Configuration is 1 */
	pcie_capability_पढ़ो_word(child, PCI_EXP_LNKSTA, &reg16);
	अगर (!(reg16 & PCI_EXP_LNKSTA_SLC))
		same_घड़ी = 0;

	/* Check upstream component अगर bit Slot Clock Configuration is 1 */
	pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKSTA, &reg16);
	अगर (!(reg16 & PCI_EXP_LNKSTA_SLC))
		same_घड़ी = 0;

	/* Port might be alपढ़ोy in common घड़ी mode */
	pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKCTL, &reg16);
	अगर (same_घड़ी && (reg16 & PCI_EXP_LNKCTL_CCC)) अणु
		bool consistent = true;

		list_क्रम_each_entry(child, &linkbus->devices, bus_list) अणु
			pcie_capability_पढ़ो_word(child, PCI_EXP_LNKCTL,
						  &reg16);
			अगर (!(reg16 & PCI_EXP_LNKCTL_CCC)) अणु
				consistent = false;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (consistent)
			वापस;
		pci_info(parent, "ASPM: current common clock configuration is inconsistent, reconfiguring\n");
	पूर्ण

	/* Configure करोwnstream component, all functions */
	list_क्रम_each_entry(child, &linkbus->devices, bus_list) अणु
		pcie_capability_पढ़ो_word(child, PCI_EXP_LNKCTL, &reg16);
		child_reg[PCI_FUNC(child->devfn)] = reg16;
		अगर (same_घड़ी)
			reg16 |= PCI_EXP_LNKCTL_CCC;
		अन्यथा
			reg16 &= ~PCI_EXP_LNKCTL_CCC;
		pcie_capability_ग_लिखो_word(child, PCI_EXP_LNKCTL, reg16);
	पूर्ण

	/* Configure upstream component */
	pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKCTL, &reg16);
	parent_reg = reg16;
	अगर (same_घड़ी)
		reg16 |= PCI_EXP_LNKCTL_CCC;
	अन्यथा
		reg16 &= ~PCI_EXP_LNKCTL_CCC;
	pcie_capability_ग_लिखो_word(parent, PCI_EXP_LNKCTL, reg16);

	अगर (pcie_retrain_link(link))
		वापस;

	/* Training failed. Restore common घड़ी configurations */
	pci_err(parent, "ASPM: Could not configure common clock\n");
	list_क्रम_each_entry(child, &linkbus->devices, bus_list)
		pcie_capability_ग_लिखो_word(child, PCI_EXP_LNKCTL,
					   child_reg[PCI_FUNC(child->devfn)]);
	pcie_capability_ग_लिखो_word(parent, PCI_EXP_LNKCTL, parent_reg);
पूर्ण

/* Convert L0s latency encoding to ns */
अटल u32 calc_l0s_latency(u32 lnkcap)
अणु
	u32 encoding = (lnkcap & PCI_EXP_LNKCAP_L0SEL) >> 12;

	अगर (encoding == 0x7)
		वापस (5 * 1000);	/* > 4us */
	वापस (64 << encoding);
पूर्ण

/* Convert L0s acceptable latency encoding to ns */
अटल u32 calc_l0s_acceptable(u32 encoding)
अणु
	अगर (encoding == 0x7)
		वापस -1U;
	वापस (64 << encoding);
पूर्ण

/* Convert L1 latency encoding to ns */
अटल u32 calc_l1_latency(u32 lnkcap)
अणु
	u32 encoding = (lnkcap & PCI_EXP_LNKCAP_L1EL) >> 15;

	अगर (encoding == 0x7)
		वापस (65 * 1000);	/* > 64us */
	वापस (1000 << encoding);
पूर्ण

/* Convert L1 acceptable latency encoding to ns */
अटल u32 calc_l1_acceptable(u32 encoding)
अणु
	अगर (encoding == 0x7)
		वापस -1U;
	वापस (1000 << encoding);
पूर्ण

/* Convert L1SS T_pwr encoding to usec */
अटल u32 calc_l1ss_pwron(काष्ठा pci_dev *pdev, u32 scale, u32 val)
अणु
	चयन (scale) अणु
	हाल 0:
		वापस val * 2;
	हाल 1:
		वापस val * 10;
	हाल 2:
		वापस val * 100;
	पूर्ण
	pci_err(pdev, "%s: Invalid T_PwrOn scale: %u\n", __func__, scale);
	वापस 0;
पूर्ण

अटल व्योम encode_l12_threshold(u32 threshold_us, u32 *scale, u32 *value)
अणु
	u32 threshold_ns = threshold_us * 1000;

	/* See PCIe r3.1, sec 7.33.3 and sec 6.18 */
	अगर (threshold_ns < 32) अणु
		*scale = 0;
		*value = threshold_ns;
	पूर्ण अन्यथा अगर (threshold_ns < 1024) अणु
		*scale = 1;
		*value = threshold_ns >> 5;
	पूर्ण अन्यथा अगर (threshold_ns < 32768) अणु
		*scale = 2;
		*value = threshold_ns >> 10;
	पूर्ण अन्यथा अगर (threshold_ns < 1048576) अणु
		*scale = 3;
		*value = threshold_ns >> 15;
	पूर्ण अन्यथा अगर (threshold_ns < 33554432) अणु
		*scale = 4;
		*value = threshold_ns >> 20;
	पूर्ण अन्यथा अणु
		*scale = 5;
		*value = threshold_ns >> 25;
	पूर्ण
पूर्ण

अटल व्योम pcie_aspm_check_latency(काष्ठा pci_dev *endpoपूर्णांक)
अणु
	u32 latency, l1_चयन_latency = 0;
	काष्ठा aspm_latency *acceptable;
	काष्ठा pcie_link_state *link;

	/* Device not in D0 करोesn't need latency check */
	अगर ((endpoपूर्णांक->current_state != PCI_D0) &&
	    (endpoपूर्णांक->current_state != PCI_UNKNOWN))
		वापस;

	link = endpoपूर्णांक->bus->self->link_state;
	acceptable = &link->acceptable[PCI_FUNC(endpoपूर्णांक->devfn)];

	जबतक (link) अणु
		/* Check upstream direction L0s latency */
		अगर ((link->aspm_capable & ASPM_STATE_L0S_UP) &&
		    (link->latency_up.l0s > acceptable->l0s))
			link->aspm_capable &= ~ASPM_STATE_L0S_UP;

		/* Check करोwnstream direction L0s latency */
		अगर ((link->aspm_capable & ASPM_STATE_L0S_DW) &&
		    (link->latency_dw.l0s > acceptable->l0s))
			link->aspm_capable &= ~ASPM_STATE_L0S_DW;
		/*
		 * Check L1 latency.
		 * Every चयन on the path to root complex need 1
		 * more microsecond क्रम L1. Spec करोesn't mention L0s.
		 *
		 * The निकास latencies क्रम L1 substates are not advertised
		 * by a device.  Since the spec also करोesn't mention a way
		 * to determine max latencies पूर्णांकroduced by enabling L1
		 * substates on the components, it is not clear how to करो
		 * a L1 substate निकास latency check.  We assume that the
		 * L1 निकास latencies advertised by a device include L1
		 * substate latencies (and hence करो not करो any check).
		 */
		latency = max_t(u32, link->latency_up.l1, link->latency_dw.l1);
		अगर ((link->aspm_capable & ASPM_STATE_L1) &&
		    (latency + l1_चयन_latency > acceptable->l1))
			link->aspm_capable &= ~ASPM_STATE_L1;
		l1_चयन_latency += 1000;

		link = link->parent;
	पूर्ण
पूर्ण

/*
 * The L1 PM substate capability is only implemented in function 0 in a
 * multi function device.
 */
अटल काष्ठा pci_dev *pci_function_0(काष्ठा pci_bus *linkbus)
अणु
	काष्ठा pci_dev *child;

	list_क्रम_each_entry(child, &linkbus->devices, bus_list)
		अगर (PCI_FUNC(child->devfn) == 0)
			वापस child;
	वापस शून्य;
पूर्ण

अटल व्योम pci_clear_and_set_dword(काष्ठा pci_dev *pdev, पूर्णांक pos,
				    u32 clear, u32 set)
अणु
	u32 val;

	pci_पढ़ो_config_dword(pdev, pos, &val);
	val &= ~clear;
	val |= set;
	pci_ग_लिखो_config_dword(pdev, pos, val);
पूर्ण

/* Calculate L1.2 PM substate timing parameters */
अटल व्योम aspm_calc_l1ss_info(काष्ठा pcie_link_state *link,
				u32 parent_l1ss_cap, u32 child_l1ss_cap)
अणु
	काष्ठा pci_dev *child = link->करोwnstream, *parent = link->pdev;
	u32 val1, val2, scale1, scale2;
	u32 t_common_mode, t_घातer_on, l1_2_threshold, scale, value;
	u32 ctl1 = 0, ctl2 = 0;
	u32 pctl1, pctl2, cctl1, cctl2;
	u32 pl1_2_enables, cl1_2_enables;

	अगर (!(link->aspm_support & ASPM_STATE_L1_2_MASK))
		वापस;

	/* Choose the greater of the two Port Common_Mode_Restore_Times */
	val1 = (parent_l1ss_cap & PCI_L1SS_CAP_CM_RESTORE_TIME) >> 8;
	val2 = (child_l1ss_cap & PCI_L1SS_CAP_CM_RESTORE_TIME) >> 8;
	t_common_mode = max(val1, val2);

	/* Choose the greater of the two Port T_POWER_ON बार */
	val1   = (parent_l1ss_cap & PCI_L1SS_CAP_P_PWR_ON_VALUE) >> 19;
	scale1 = (parent_l1ss_cap & PCI_L1SS_CAP_P_PWR_ON_SCALE) >> 16;
	val2   = (child_l1ss_cap & PCI_L1SS_CAP_P_PWR_ON_VALUE) >> 19;
	scale2 = (child_l1ss_cap & PCI_L1SS_CAP_P_PWR_ON_SCALE) >> 16;

	अगर (calc_l1ss_pwron(parent, scale1, val1) >
	    calc_l1ss_pwron(child, scale2, val2)) अणु
		ctl2 |= scale1 | (val1 << 3);
		t_घातer_on = calc_l1ss_pwron(parent, scale1, val1);
	पूर्ण अन्यथा अणु
		ctl2 |= scale2 | (val2 << 3);
		t_घातer_on = calc_l1ss_pwron(child, scale2, val2);
	पूर्ण

	/*
	 * Set LTR_L1.2_THRESHOLD to the समय required to transition the
	 * Link from L0 to L1.2 and back to L0 so we enter L1.2 only अगर
	 * करोwnstream devices report (via LTR) that they can tolerate at
	 * least that much latency.
	 *
	 * Based on PCIe r3.1, sec 5.5.3.3.1, Figures 5-16 and 5-17, and
	 * Table 5-11.  T(POWER_OFF) is at most 2us and T(L1.2) is at
	 * least 4us.
	 */
	l1_2_threshold = 2 + 4 + t_common_mode + t_घातer_on;
	encode_l12_threshold(l1_2_threshold, &scale, &value);
	ctl1 |= t_common_mode << 8 | scale << 29 | value << 16;

	pci_पढ़ो_config_dword(parent, parent->l1ss + PCI_L1SS_CTL1, &pctl1);
	pci_पढ़ो_config_dword(parent, parent->l1ss + PCI_L1SS_CTL2, &pctl2);
	pci_पढ़ो_config_dword(child, child->l1ss + PCI_L1SS_CTL1, &cctl1);
	pci_पढ़ो_config_dword(child, child->l1ss + PCI_L1SS_CTL2, &cctl2);

	अगर (ctl1 == pctl1 && ctl1 == cctl1 &&
	    ctl2 == pctl2 && ctl2 == cctl2)
		वापस;

	/* Disable L1.2 जबतक updating.  See PCIe r5.0, sec 5.5.4, 7.8.3.3 */
	pl1_2_enables = pctl1 & PCI_L1SS_CTL1_L1_2_MASK;
	cl1_2_enables = cctl1 & PCI_L1SS_CTL1_L1_2_MASK;

	अगर (pl1_2_enables || cl1_2_enables) अणु
		pci_clear_and_set_dword(child, child->l1ss + PCI_L1SS_CTL1,
					PCI_L1SS_CTL1_L1_2_MASK, 0);
		pci_clear_and_set_dword(parent, parent->l1ss + PCI_L1SS_CTL1,
					PCI_L1SS_CTL1_L1_2_MASK, 0);
	पूर्ण

	/* Program T_POWER_ON बार in both ports */
	pci_ग_लिखो_config_dword(parent, parent->l1ss + PCI_L1SS_CTL2, ctl2);
	pci_ग_लिखो_config_dword(child, child->l1ss + PCI_L1SS_CTL2, ctl2);

	/* Program Common_Mode_Restore_Time in upstream device */
	pci_clear_and_set_dword(parent, parent->l1ss + PCI_L1SS_CTL1,
				PCI_L1SS_CTL1_CM_RESTORE_TIME, ctl1);

	/* Program LTR_L1.2_THRESHOLD समय in both ports */
	pci_clear_and_set_dword(parent,	parent->l1ss + PCI_L1SS_CTL1,
				PCI_L1SS_CTL1_LTR_L12_TH_VALUE |
				PCI_L1SS_CTL1_LTR_L12_TH_SCALE, ctl1);
	pci_clear_and_set_dword(child, child->l1ss + PCI_L1SS_CTL1,
				PCI_L1SS_CTL1_LTR_L12_TH_VALUE |
				PCI_L1SS_CTL1_LTR_L12_TH_SCALE, ctl1);

	अगर (pl1_2_enables || cl1_2_enables) अणु
		pci_clear_and_set_dword(parent, parent->l1ss + PCI_L1SS_CTL1, 0,
					pl1_2_enables);
		pci_clear_and_set_dword(child, child->l1ss + PCI_L1SS_CTL1, 0,
					cl1_2_enables);
	पूर्ण
पूर्ण

अटल व्योम pcie_aspm_cap_init(काष्ठा pcie_link_state *link, पूर्णांक blacklist)
अणु
	काष्ठा pci_dev *child = link->करोwnstream, *parent = link->pdev;
	u32 parent_lnkcap, child_lnkcap;
	u16 parent_lnkctl, child_lnkctl;
	u32 parent_l1ss_cap, child_l1ss_cap;
	u32 parent_l1ss_ctl1 = 0, child_l1ss_ctl1 = 0;
	काष्ठा pci_bus *linkbus = parent->subordinate;

	अगर (blacklist) अणु
		/* Set enabled/disable so that we will disable ASPM later */
		link->aspm_enabled = ASPM_STATE_ALL;
		link->aspm_disable = ASPM_STATE_ALL;
		वापस;
	पूर्ण

	/*
	 * If ASPM not supported, करोn't mess with the घड़ीs and link,
	 * bail out now.
	 */
	pcie_capability_पढ़ो_dword(parent, PCI_EXP_LNKCAP, &parent_lnkcap);
	pcie_capability_पढ़ो_dword(child, PCI_EXP_LNKCAP, &child_lnkcap);
	अगर (!(parent_lnkcap & child_lnkcap & PCI_EXP_LNKCAP_ASPMS))
		वापस;

	/* Configure common घड़ी beक्रमe checking latencies */
	pcie_aspm_configure_common_घड़ी(link);

	/*
	 * Re-पढ़ो upstream/करोwnstream components' रेजिस्टर state after
	 * घड़ी configuration.  L0s & L1 निकास latencies in the otherwise
	 * पढ़ो-only Link Capabilities may change depending on common घड़ी
	 * configuration (PCIe r5.0, sec 7.5.3.6).
	 */
	pcie_capability_पढ़ो_dword(parent, PCI_EXP_LNKCAP, &parent_lnkcap);
	pcie_capability_पढ़ो_dword(child, PCI_EXP_LNKCAP, &child_lnkcap);
	pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKCTL, &parent_lnkctl);
	pcie_capability_पढ़ो_word(child, PCI_EXP_LNKCTL, &child_lnkctl);

	/*
	 * Setup L0s state
	 *
	 * Note that we must not enable L0s in either direction on a
	 * given link unless components on both sides of the link each
	 * support L0s.
	 */
	अगर (parent_lnkcap & child_lnkcap & PCI_EXP_LNKCAP_ASPM_L0S)
		link->aspm_support |= ASPM_STATE_L0S;

	अगर (child_lnkctl & PCI_EXP_LNKCTL_ASPM_L0S)
		link->aspm_enabled |= ASPM_STATE_L0S_UP;
	अगर (parent_lnkctl & PCI_EXP_LNKCTL_ASPM_L0S)
		link->aspm_enabled |= ASPM_STATE_L0S_DW;
	link->latency_up.l0s = calc_l0s_latency(parent_lnkcap);
	link->latency_dw.l0s = calc_l0s_latency(child_lnkcap);

	/* Setup L1 state */
	अगर (parent_lnkcap & child_lnkcap & PCI_EXP_LNKCAP_ASPM_L1)
		link->aspm_support |= ASPM_STATE_L1;

	अगर (parent_lnkctl & child_lnkctl & PCI_EXP_LNKCTL_ASPM_L1)
		link->aspm_enabled |= ASPM_STATE_L1;
	link->latency_up.l1 = calc_l1_latency(parent_lnkcap);
	link->latency_dw.l1 = calc_l1_latency(child_lnkcap);

	/* Setup L1 substate */
	pci_पढ़ो_config_dword(parent, parent->l1ss + PCI_L1SS_CAP,
			      &parent_l1ss_cap);
	pci_पढ़ो_config_dword(child, child->l1ss + PCI_L1SS_CAP,
			      &child_l1ss_cap);

	अगर (!(parent_l1ss_cap & PCI_L1SS_CAP_L1_PM_SS))
		parent_l1ss_cap = 0;
	अगर (!(child_l1ss_cap & PCI_L1SS_CAP_L1_PM_SS))
		child_l1ss_cap = 0;

	/*
	 * If we करोn't have LTR क्रम the entire path from the Root Complex
	 * to this device, we can't use ASPM L1.2 because it relies on the
	 * LTR_L1.2_THRESHOLD.  See PCIe r4.0, secs 5.5.4, 6.18.
	 */
	अगर (!child->ltr_path)
		child_l1ss_cap &= ~PCI_L1SS_CAP_ASPM_L1_2;

	अगर (parent_l1ss_cap & child_l1ss_cap & PCI_L1SS_CAP_ASPM_L1_1)
		link->aspm_support |= ASPM_STATE_L1_1;
	अगर (parent_l1ss_cap & child_l1ss_cap & PCI_L1SS_CAP_ASPM_L1_2)
		link->aspm_support |= ASPM_STATE_L1_2;
	अगर (parent_l1ss_cap & child_l1ss_cap & PCI_L1SS_CAP_PCIPM_L1_1)
		link->aspm_support |= ASPM_STATE_L1_1_PCIPM;
	अगर (parent_l1ss_cap & child_l1ss_cap & PCI_L1SS_CAP_PCIPM_L1_2)
		link->aspm_support |= ASPM_STATE_L1_2_PCIPM;

	अगर (parent_l1ss_cap)
		pci_पढ़ो_config_dword(parent, parent->l1ss + PCI_L1SS_CTL1,
				      &parent_l1ss_ctl1);
	अगर (child_l1ss_cap)
		pci_पढ़ो_config_dword(child, child->l1ss + PCI_L1SS_CTL1,
				      &child_l1ss_ctl1);

	अगर (parent_l1ss_ctl1 & child_l1ss_ctl1 & PCI_L1SS_CTL1_ASPM_L1_1)
		link->aspm_enabled |= ASPM_STATE_L1_1;
	अगर (parent_l1ss_ctl1 & child_l1ss_ctl1 & PCI_L1SS_CTL1_ASPM_L1_2)
		link->aspm_enabled |= ASPM_STATE_L1_2;
	अगर (parent_l1ss_ctl1 & child_l1ss_ctl1 & PCI_L1SS_CTL1_PCIPM_L1_1)
		link->aspm_enabled |= ASPM_STATE_L1_1_PCIPM;
	अगर (parent_l1ss_ctl1 & child_l1ss_ctl1 & PCI_L1SS_CTL1_PCIPM_L1_2)
		link->aspm_enabled |= ASPM_STATE_L1_2_PCIPM;

	अगर (link->aspm_support & ASPM_STATE_L1SS)
		aspm_calc_l1ss_info(link, parent_l1ss_cap, child_l1ss_cap);

	/* Save शेष state */
	link->aspm_शेष = link->aspm_enabled;

	/* Setup initial capable state. Will be updated later */
	link->aspm_capable = link->aspm_support;

	/* Get and check endpoपूर्णांक acceptable latencies */
	list_क्रम_each_entry(child, &linkbus->devices, bus_list) अणु
		u32 reg32, encoding;
		काष्ठा aspm_latency *acceptable =
			&link->acceptable[PCI_FUNC(child->devfn)];

		अगर (pci_pcie_type(child) != PCI_EXP_TYPE_ENDPOINT &&
		    pci_pcie_type(child) != PCI_EXP_TYPE_LEG_END)
			जारी;

		pcie_capability_पढ़ो_dword(child, PCI_EXP_DEVCAP, &reg32);
		/* Calculate endpoपूर्णांक L0s acceptable latency */
		encoding = (reg32 & PCI_EXP_DEVCAP_L0S) >> 6;
		acceptable->l0s = calc_l0s_acceptable(encoding);
		/* Calculate endpoपूर्णांक L1 acceptable latency */
		encoding = (reg32 & PCI_EXP_DEVCAP_L1) >> 9;
		acceptable->l1 = calc_l1_acceptable(encoding);

		pcie_aspm_check_latency(child);
	पूर्ण
पूर्ण

/* Configure the ASPM L1 substates */
अटल व्योम pcie_config_aspm_l1ss(काष्ठा pcie_link_state *link, u32 state)
अणु
	u32 val, enable_req;
	काष्ठा pci_dev *child = link->करोwnstream, *parent = link->pdev;

	enable_req = (link->aspm_enabled ^ state) & state;

	/*
	 * Here are the rules specअगरied in the PCIe spec क्रम enabling L1SS:
	 * - When enabling L1.x, enable bit at parent first, then at child
	 * - When disabling L1.x, disable bit at child first, then at parent
	 * - When enabling ASPM L1.x, need to disable L1
	 *   (at child followed by parent).
	 * - The ASPM/PCIPM L1.2 must be disabled जबतक programming timing
	 *   parameters
	 *
	 * To keep it simple, disable all L1SS bits first, and later enable
	 * what is needed.
	 */

	/* Disable all L1 substates */
	pci_clear_and_set_dword(child, child->l1ss + PCI_L1SS_CTL1,
				PCI_L1SS_CTL1_L1SS_MASK, 0);
	pci_clear_and_set_dword(parent, parent->l1ss + PCI_L1SS_CTL1,
				PCI_L1SS_CTL1_L1SS_MASK, 0);
	/*
	 * If needed, disable L1, and it माला_लो enabled later
	 * in pcie_config_aspm_link().
	 */
	अगर (enable_req & (ASPM_STATE_L1_1 | ASPM_STATE_L1_2)) अणु
		pcie_capability_clear_and_set_word(child, PCI_EXP_LNKCTL,
						   PCI_EXP_LNKCTL_ASPM_L1, 0);
		pcie_capability_clear_and_set_word(parent, PCI_EXP_LNKCTL,
						   PCI_EXP_LNKCTL_ASPM_L1, 0);
	पूर्ण

	val = 0;
	अगर (state & ASPM_STATE_L1_1)
		val |= PCI_L1SS_CTL1_ASPM_L1_1;
	अगर (state & ASPM_STATE_L1_2)
		val |= PCI_L1SS_CTL1_ASPM_L1_2;
	अगर (state & ASPM_STATE_L1_1_PCIPM)
		val |= PCI_L1SS_CTL1_PCIPM_L1_1;
	अगर (state & ASPM_STATE_L1_2_PCIPM)
		val |= PCI_L1SS_CTL1_PCIPM_L1_2;

	/* Enable what we need to enable */
	pci_clear_and_set_dword(parent, parent->l1ss + PCI_L1SS_CTL1,
				PCI_L1SS_CTL1_L1SS_MASK, val);
	pci_clear_and_set_dword(child, child->l1ss + PCI_L1SS_CTL1,
				PCI_L1SS_CTL1_L1SS_MASK, val);
पूर्ण

अटल व्योम pcie_config_aspm_dev(काष्ठा pci_dev *pdev, u32 val)
अणु
	pcie_capability_clear_and_set_word(pdev, PCI_EXP_LNKCTL,
					   PCI_EXP_LNKCTL_ASPMC, val);
पूर्ण

अटल व्योम pcie_config_aspm_link(काष्ठा pcie_link_state *link, u32 state)
अणु
	u32 upstream = 0, dwstream = 0;
	काष्ठा pci_dev *child = link->करोwnstream, *parent = link->pdev;
	काष्ठा pci_bus *linkbus = parent->subordinate;

	/* Enable only the states that were not explicitly disabled */
	state &= (link->aspm_capable & ~link->aspm_disable);

	/* Can't enable any substates अगर L1 is not enabled */
	अगर (!(state & ASPM_STATE_L1))
		state &= ~ASPM_STATE_L1SS;

	/* Spec says both ports must be in D0 beक्रमe enabling PCI PM substates*/
	अगर (parent->current_state != PCI_D0 || child->current_state != PCI_D0) अणु
		state &= ~ASPM_STATE_L1_SS_PCIPM;
		state |= (link->aspm_enabled & ASPM_STATE_L1_SS_PCIPM);
	पूर्ण

	/* Nothing to करो अगर the link is alपढ़ोy in the requested state */
	अगर (link->aspm_enabled == state)
		वापस;
	/* Convert ASPM state to upstream/करोwnstream ASPM रेजिस्टर state */
	अगर (state & ASPM_STATE_L0S_UP)
		dwstream |= PCI_EXP_LNKCTL_ASPM_L0S;
	अगर (state & ASPM_STATE_L0S_DW)
		upstream |= PCI_EXP_LNKCTL_ASPM_L0S;
	अगर (state & ASPM_STATE_L1) अणु
		upstream |= PCI_EXP_LNKCTL_ASPM_L1;
		dwstream |= PCI_EXP_LNKCTL_ASPM_L1;
	पूर्ण

	अगर (link->aspm_capable & ASPM_STATE_L1SS)
		pcie_config_aspm_l1ss(link, state);

	/*
	 * Spec 2.0 suggests all functions should be configured the
	 * same setting क्रम ASPM. Enabling ASPM L1 should be करोne in
	 * upstream component first and then करोwnstream, and vice
	 * versa क्रम disabling ASPM L1. Spec करोesn't mention L0S.
	 */
	अगर (state & ASPM_STATE_L1)
		pcie_config_aspm_dev(parent, upstream);
	list_क्रम_each_entry(child, &linkbus->devices, bus_list)
		pcie_config_aspm_dev(child, dwstream);
	अगर (!(state & ASPM_STATE_L1))
		pcie_config_aspm_dev(parent, upstream);

	link->aspm_enabled = state;
पूर्ण

अटल व्योम pcie_config_aspm_path(काष्ठा pcie_link_state *link)
अणु
	जबतक (link) अणु
		pcie_config_aspm_link(link, policy_to_aspm_state(link));
		link = link->parent;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_link_state(काष्ठा pcie_link_state *link)
अणु
	link->pdev->link_state = शून्य;
	kमुक्त(link);
पूर्ण

अटल पूर्णांक pcie_aspm_sanity_check(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *child;
	u32 reg32;

	/*
	 * Some functions in a slot might not all be PCIe functions,
	 * very strange. Disable ASPM क्रम the whole slot
	 */
	list_क्रम_each_entry(child, &pdev->subordinate->devices, bus_list) अणु
		अगर (!pci_is_pcie(child))
			वापस -EINVAL;

		/*
		 * If ASPM is disabled then we're not going to change
		 * the BIOS state. It's safe to continue even if it's a
		 * pre-1.1 device
		 */

		अगर (aspm_disabled)
			जारी;

		/*
		 * Disable ASPM क्रम pre-1.1 PCIe device, we follow MS to use
		 * RBER bit to determine अगर a function is 1.1 version device
		 */
		pcie_capability_पढ़ो_dword(child, PCI_EXP_DEVCAP, &reg32);
		अगर (!(reg32 & PCI_EXP_DEVCAP_RBER) && !aspm_क्रमce) अणु
			pci_info(child, "disabling ASPM on pre-1.1 PCIe device.  You can enable it with 'pcie_aspm=force'\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा pcie_link_state *alloc_pcie_link_state(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcie_link_state *link;

	link = kzalloc(माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस शून्य;

	INIT_LIST_HEAD(&link->sibling);
	link->pdev = pdev;
	link->करोwnstream = pci_function_0(pdev->subordinate);

	/*
	 * Root Ports and PCI/PCI-X to PCIe Bridges are roots of PCIe
	 * hierarchies.  Note that some PCIe host implementations omit
	 * the root ports entirely, in which हाल a करोwnstream port on
	 * a चयन may become the root of the link state chain क्रम all
	 * its subordinate endpoपूर्णांकs.
	 */
	अगर (pci_pcie_type(pdev) == PCI_EXP_TYPE_ROOT_PORT ||
	    pci_pcie_type(pdev) == PCI_EXP_TYPE_PCIE_BRIDGE ||
	    !pdev->bus->parent->self) अणु
		link->root = link;
	पूर्ण अन्यथा अणु
		काष्ठा pcie_link_state *parent;

		parent = pdev->bus->parent->self->link_state;
		अगर (!parent) अणु
			kमुक्त(link);
			वापस शून्य;
		पूर्ण

		link->parent = parent;
		link->root = link->parent->root;
	पूर्ण

	list_add(&link->sibling, &link_list);
	pdev->link_state = link;
	वापस link;
पूर्ण

अटल व्योम pcie_aspm_update_sysfs_visibility(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *child;

	list_क्रम_each_entry(child, &pdev->subordinate->devices, bus_list)
		sysfs_update_group(&child->dev.kobj, &aspm_ctrl_attr_group);
पूर्ण

/*
 * pcie_aspm_init_link_state: Initiate PCI express link state.
 * It is called after the pcie and its children devices are scanned.
 * @pdev: the root port or चयन करोwnstream port
 */
व्योम pcie_aspm_init_link_state(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcie_link_state *link;
	पूर्णांक blacklist = !!pcie_aspm_sanity_check(pdev);

	अगर (!aspm_support_enabled)
		वापस;

	अगर (pdev->link_state)
		वापस;

	/*
	 * We allocate pcie_link_state क्रम the component on the upstream
	 * end of a Link, so there's nothing to करो unless this device is
	 * करोwnstream port.
	 */
	अगर (!pcie_करोwnstream_port(pdev))
		वापस;

	/* VIA has a strange chipset, root port is under a bridge */
	अगर (pci_pcie_type(pdev) == PCI_EXP_TYPE_ROOT_PORT &&
	    pdev->bus->self)
		वापस;

	करोwn_पढ़ो(&pci_bus_sem);
	अगर (list_empty(&pdev->subordinate->devices))
		जाओ out;

	mutex_lock(&aspm_lock);
	link = alloc_pcie_link_state(pdev);
	अगर (!link)
		जाओ unlock;
	/*
	 * Setup initial ASPM state. Note that we need to configure
	 * upstream links also because capable state of them can be
	 * update through pcie_aspm_cap_init().
	 */
	pcie_aspm_cap_init(link, blacklist);

	/* Setup initial Clock PM state */
	pcie_clkpm_cap_init(link, blacklist);

	/*
	 * At this stage drivers haven't had an opportunity to change the
	 * link policy setting. Enabling ASPM on broken hardware can cripple
	 * it even beक्रमe the driver has had a chance to disable ASPM, so
	 * शेष to a safe level right now. If we're enabling ASPM beyond
	 * the BIOS's expectation, we'll करो so once pci_enable_device() is
	 * called.
	 */
	अगर (aspm_policy != POLICY_POWERSAVE &&
	    aspm_policy != POLICY_POWER_SUPERSAVE) अणु
		pcie_config_aspm_path(link);
		pcie_set_clkpm(link, policy_to_clkpm_state(link));
	पूर्ण

	pcie_aspm_update_sysfs_visibility(pdev);

unlock:
	mutex_unlock(&aspm_lock);
out:
	up_पढ़ो(&pci_bus_sem);
पूर्ण

/* Recheck latencies and update aspm_capable क्रम links under the root */
अटल व्योम pcie_update_aspm_capable(काष्ठा pcie_link_state *root)
अणु
	काष्ठा pcie_link_state *link;
	BUG_ON(root->parent);
	list_क्रम_each_entry(link, &link_list, sibling) अणु
		अगर (link->root != root)
			जारी;
		link->aspm_capable = link->aspm_support;
	पूर्ण
	list_क्रम_each_entry(link, &link_list, sibling) अणु
		काष्ठा pci_dev *child;
		काष्ठा pci_bus *linkbus = link->pdev->subordinate;
		अगर (link->root != root)
			जारी;
		list_क्रम_each_entry(child, &linkbus->devices, bus_list) अणु
			अगर ((pci_pcie_type(child) != PCI_EXP_TYPE_ENDPOINT) &&
			    (pci_pcie_type(child) != PCI_EXP_TYPE_LEG_END))
				जारी;
			pcie_aspm_check_latency(child);
		पूर्ण
	पूर्ण
पूर्ण

/* @pdev: the endpoपूर्णांक device */
व्योम pcie_aspm_निकास_link_state(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *parent = pdev->bus->self;
	काष्ठा pcie_link_state *link, *root, *parent_link;

	अगर (!parent || !parent->link_state)
		वापस;

	करोwn_पढ़ो(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	/*
	 * All PCIe functions are in one slot, हटाओ one function will हटाओ
	 * the whole slot, so just रुको until we are the last function left.
	 */
	अगर (!list_empty(&parent->subordinate->devices))
		जाओ out;

	link = parent->link_state;
	root = link->root;
	parent_link = link->parent;

	/* All functions are हटाओd, so just disable ASPM क्रम the link */
	pcie_config_aspm_link(link, 0);
	list_del(&link->sibling);
	/* Clock PM is क्रम endpoपूर्णांक device */
	मुक्त_link_state(link);

	/* Recheck latencies and configure upstream links */
	अगर (parent_link) अणु
		pcie_update_aspm_capable(root);
		pcie_config_aspm_path(parent_link);
	पूर्ण
out:
	mutex_unlock(&aspm_lock);
	up_पढ़ो(&pci_bus_sem);
पूर्ण

/* @pdev: the root port or चयन करोwnstream port */
व्योम pcie_aspm_pm_state_change(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcie_link_state *link = pdev->link_state;

	अगर (aspm_disabled || !link)
		वापस;
	/*
	 * Devices changed PM state, we should recheck अगर latency
	 * meets all functions' requirement
	 */
	करोwn_पढ़ो(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	pcie_update_aspm_capable(link->root);
	pcie_config_aspm_path(link);
	mutex_unlock(&aspm_lock);
	up_पढ़ो(&pci_bus_sem);
पूर्ण

व्योम pcie_aspm_घातersave_config_link(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcie_link_state *link = pdev->link_state;

	अगर (aspm_disabled || !link)
		वापस;

	अगर (aspm_policy != POLICY_POWERSAVE &&
	    aspm_policy != POLICY_POWER_SUPERSAVE)
		वापस;

	करोwn_पढ़ो(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	pcie_config_aspm_path(link);
	pcie_set_clkpm(link, policy_to_clkpm_state(link));
	mutex_unlock(&aspm_lock);
	up_पढ़ो(&pci_bus_sem);
पूर्ण

अटल काष्ठा pcie_link_state *pcie_aspm_get_link(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *bridge;

	अगर (!pci_is_pcie(pdev))
		वापस शून्य;

	bridge = pci_upstream_bridge(pdev);
	अगर (!bridge || !pci_is_pcie(bridge))
		वापस शून्य;

	वापस bridge->link_state;
पूर्ण

अटल पूर्णांक __pci_disable_link_state(काष्ठा pci_dev *pdev, पूर्णांक state, bool sem)
अणु
	काष्ठा pcie_link_state *link = pcie_aspm_get_link(pdev);

	अगर (!link)
		वापस -EINVAL;
	/*
	 * A driver requested that ASPM be disabled on this device, but
	 * अगर we करोn't have permission to manage ASPM (e.g., on ACPI
	 * प्रणालीs we have to observe the FADT ACPI_FADT_NO_ASPM bit and
	 * the _OSC method), we can't honor that request.  Winकरोws has
	 * a similar mechanism using "PciASPMOptOut", which is also
	 * ignored in this situation.
	 */
	अगर (aspm_disabled) अणु
		pci_warn(pdev, "can't disable ASPM; OS doesn't have ASPM control\n");
		वापस -EPERM;
	पूर्ण

	अगर (sem)
		करोwn_पढ़ो(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	अगर (state & PCIE_LINK_STATE_L0S)
		link->aspm_disable |= ASPM_STATE_L0S;
	अगर (state & PCIE_LINK_STATE_L1)
		/* L1 PM substates require L1 */
		link->aspm_disable |= ASPM_STATE_L1 | ASPM_STATE_L1SS;
	अगर (state & PCIE_LINK_STATE_L1_1)
		link->aspm_disable |= ASPM_STATE_L1_1;
	अगर (state & PCIE_LINK_STATE_L1_2)
		link->aspm_disable |= ASPM_STATE_L1_2;
	अगर (state & PCIE_LINK_STATE_L1_1_PCIPM)
		link->aspm_disable |= ASPM_STATE_L1_1_PCIPM;
	अगर (state & PCIE_LINK_STATE_L1_2_PCIPM)
		link->aspm_disable |= ASPM_STATE_L1_2_PCIPM;
	pcie_config_aspm_link(link, policy_to_aspm_state(link));

	अगर (state & PCIE_LINK_STATE_CLKPM)
		link->clkpm_disable = 1;
	pcie_set_clkpm(link, policy_to_clkpm_state(link));
	mutex_unlock(&aspm_lock);
	अगर (sem)
		up_पढ़ो(&pci_bus_sem);

	वापस 0;
पूर्ण

पूर्णांक pci_disable_link_state_locked(काष्ठा pci_dev *pdev, पूर्णांक state)
अणु
	वापस __pci_disable_link_state(pdev, state, false);
पूर्ण
EXPORT_SYMBOL(pci_disable_link_state_locked);

/**
 * pci_disable_link_state - Disable device's link state, so the link will
 * never enter specअगरic states.  Note that अगर the BIOS didn't grant ASPM
 * control to the OS, this करोes nothing because we can't touch the LNKCTL
 * रेजिस्टर. Returns 0 or a negative त्रुटि_सं.
 *
 * @pdev: PCI device
 * @state: ASPM link state to disable
 */
पूर्णांक pci_disable_link_state(काष्ठा pci_dev *pdev, पूर्णांक state)
अणु
	वापस __pci_disable_link_state(pdev, state, true);
पूर्ण
EXPORT_SYMBOL(pci_disable_link_state);

अटल पूर्णांक pcie_aspm_set_policy(स्थिर अक्षर *val,
				स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i;
	काष्ठा pcie_link_state *link;

	अगर (aspm_disabled)
		वापस -EPERM;
	i = sysfs_match_string(policy_str, val);
	अगर (i < 0)
		वापस i;
	अगर (i == aspm_policy)
		वापस 0;

	करोwn_पढ़ो(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	aspm_policy = i;
	list_क्रम_each_entry(link, &link_list, sibling) अणु
		pcie_config_aspm_link(link, policy_to_aspm_state(link));
		pcie_set_clkpm(link, policy_to_clkpm_state(link));
	पूर्ण
	mutex_unlock(&aspm_lock);
	up_पढ़ो(&pci_bus_sem);
	वापस 0;
पूर्ण

अटल पूर्णांक pcie_aspm_get_policy(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i, cnt = 0;
	क्रम (i = 0; i < ARRAY_SIZE(policy_str); i++)
		अगर (i == aspm_policy)
			cnt += प्र_लिखो(buffer + cnt, "[%s] ", policy_str[i]);
		अन्यथा
			cnt += प्र_लिखो(buffer + cnt, "%s ", policy_str[i]);
	cnt += प्र_लिखो(buffer + cnt, "\n");
	वापस cnt;
पूर्ण

module_param_call(policy, pcie_aspm_set_policy, pcie_aspm_get_policy,
	शून्य, 0644);

/**
 * pcie_aspm_enabled - Check अगर PCIe ASPM has been enabled क्रम a device.
 * @pdev: Target device.
 *
 * Relies on the upstream bridge's link_state being valid.  The link_state
 * is deallocated only when the last child of the bridge (i.e., @pdev or a
 * sibling) is हटाओd, and the caller should be holding a reference to
 * @pdev, so this should be safe.
 */
bool pcie_aspm_enabled(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcie_link_state *link = pcie_aspm_get_link(pdev);

	अगर (!link)
		वापस false;

	वापस link->aspm_enabled;
पूर्ण
EXPORT_SYMBOL_GPL(pcie_aspm_enabled);

अटल sमाप_प्रकार aspm_attr_show_common(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf, u8 state)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pcie_link_state *link = pcie_aspm_get_link(pdev);

	वापस प्र_लिखो(buf, "%d\n", (link->aspm_enabled & state) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार aspm_attr_store_common(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार len, u8 state)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pcie_link_state *link = pcie_aspm_get_link(pdev);
	bool state_enable;

	अगर (strtobool(buf, &state_enable) < 0)
		वापस -EINVAL;

	करोwn_पढ़ो(&pci_bus_sem);
	mutex_lock(&aspm_lock);

	अगर (state_enable) अणु
		link->aspm_disable &= ~state;
		/* need to enable L1 क्रम substates */
		अगर (state & ASPM_STATE_L1SS)
			link->aspm_disable &= ~ASPM_STATE_L1;
	पूर्ण अन्यथा अणु
		link->aspm_disable |= state;
	पूर्ण

	pcie_config_aspm_link(link, policy_to_aspm_state(link));

	mutex_unlock(&aspm_lock);
	up_पढ़ो(&pci_bus_sem);

	वापस len;
पूर्ण

#घोषणा ASPM_ATTR(_f, _s)						\
अटल sमाप_प्रकार _f##_show(काष्ठा device *dev,				\
			 काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु वापस aspm_attr_show_common(dev, attr, buf, ASPM_STATE_##_s); पूर्ण	\
									\
अटल sमाप_प्रकार _f##_store(काष्ठा device *dev,				\
			  काष्ठा device_attribute *attr,		\
			  स्थिर अक्षर *buf, माप_प्रकार len)			\
अणु वापस aspm_attr_store_common(dev, attr, buf, len, ASPM_STATE_##_s); पूर्ण

ASPM_ATTR(l0s_aspm, L0S)
ASPM_ATTR(l1_aspm, L1)
ASPM_ATTR(l1_1_aspm, L1_1)
ASPM_ATTR(l1_2_aspm, L1_2)
ASPM_ATTR(l1_1_pcipm, L1_1_PCIPM)
ASPM_ATTR(l1_2_pcipm, L1_2_PCIPM)

अटल sमाप_प्रकार clkpm_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pcie_link_state *link = pcie_aspm_get_link(pdev);

	वापस प्र_लिखो(buf, "%d\n", link->clkpm_enabled);
पूर्ण

अटल sमाप_प्रकार clkpm_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pcie_link_state *link = pcie_aspm_get_link(pdev);
	bool state_enable;

	अगर (strtobool(buf, &state_enable) < 0)
		वापस -EINVAL;

	करोwn_पढ़ो(&pci_bus_sem);
	mutex_lock(&aspm_lock);

	link->clkpm_disable = !state_enable;
	pcie_set_clkpm(link, policy_to_clkpm_state(link));

	mutex_unlock(&aspm_lock);
	up_पढ़ो(&pci_bus_sem);

	वापस len;
पूर्ण

अटल DEVICE_ATTR_RW(clkpm);
अटल DEVICE_ATTR_RW(l0s_aspm);
अटल DEVICE_ATTR_RW(l1_aspm);
अटल DEVICE_ATTR_RW(l1_1_aspm);
अटल DEVICE_ATTR_RW(l1_2_aspm);
अटल DEVICE_ATTR_RW(l1_1_pcipm);
अटल DEVICE_ATTR_RW(l1_2_pcipm);

अटल काष्ठा attribute *aspm_ctrl_attrs[] = अणु
	&dev_attr_clkpm.attr,
	&dev_attr_l0s_aspm.attr,
	&dev_attr_l1_aspm.attr,
	&dev_attr_l1_1_aspm.attr,
	&dev_attr_l1_2_aspm.attr,
	&dev_attr_l1_1_pcipm.attr,
	&dev_attr_l1_2_pcipm.attr,
	शून्य
पूर्ण;

अटल umode_t aspm_ctrl_attrs_are_visible(काष्ठा kobject *kobj,
					   काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pcie_link_state *link = pcie_aspm_get_link(pdev);
	अटल स्थिर u8 aspm_state_map[] = अणु
		ASPM_STATE_L0S,
		ASPM_STATE_L1,
		ASPM_STATE_L1_1,
		ASPM_STATE_L1_2,
		ASPM_STATE_L1_1_PCIPM,
		ASPM_STATE_L1_2_PCIPM,
	पूर्ण;

	अगर (aspm_disabled || !link)
		वापस 0;

	अगर (n == 0)
		वापस link->clkpm_capable ? a->mode : 0;

	वापस link->aspm_capable & aspm_state_map[n - 1] ? a->mode : 0;
पूर्ण

स्थिर काष्ठा attribute_group aspm_ctrl_attr_group = अणु
	.name = "link",
	.attrs = aspm_ctrl_attrs,
	.is_visible = aspm_ctrl_attrs_are_visible,
पूर्ण;

अटल पूर्णांक __init pcie_aspm_disable(अक्षर *str)
अणु
	अगर (!म_भेद(str, "off")) अणु
		aspm_policy = POLICY_DEFAULT;
		aspm_disabled = 1;
		aspm_support_enabled = false;
		prपूर्णांकk(KERN_INFO "PCIe ASPM is disabled\n");
	पूर्ण अन्यथा अगर (!म_भेद(str, "force")) अणु
		aspm_क्रमce = 1;
		prपूर्णांकk(KERN_INFO "PCIe ASPM is forcibly enabled\n");
	पूर्ण
	वापस 1;
पूर्ण

__setup("pcie_aspm=", pcie_aspm_disable);

व्योम pcie_no_aspm(व्योम)
अणु
	/*
	 * Disabling ASPM is पूर्णांकended to prevent the kernel from modअगरying
	 * existing hardware state, not to clear existing state. To that end:
	 * (a) set policy to POLICY_DEFAULT in order to aव्योम changing state
	 * (b) prevent userspace from changing policy
	 */
	अगर (!aspm_क्रमce) अणु
		aspm_policy = POLICY_DEFAULT;
		aspm_disabled = 1;
	पूर्ण
पूर्ण

bool pcie_aspm_support_enabled(व्योम)
अणु
	वापस aspm_support_enabled;
पूर्ण
EXPORT_SYMBOL(pcie_aspm_support_enabled);
