<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implement the AER root port service driver. The driver रेजिस्टरs an IRQ
 * handler. When a root port triggers an AER पूर्णांकerrupt, the IRQ handler
 * collects root port status and schedules work.
 *
 * Copyright (C) 2006 Intel Corp.
 *	Tom Long Nguyen (tom.l.nguyen@पूर्णांकel.com)
 *	Zhang Yanmin (yanmin.zhang@पूर्णांकel.com)
 *
 * (C) Copyright 2009 Hewlett-Packard Development Company, L.P.
 *    Andrew Patterson <andrew.patterson@hp.com>
 */

#घोषणा pr_fmt(fmt) "AER: " fmt
#घोषणा dev_fmt pr_fmt

#समावेश <linux/bitops.h>
#समावेश <linux/cper.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pm.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/slab.h>
#समावेश <acpi/apei.h>
#समावेश <ras/ras_event.h>

#समावेश "../pci.h"
#समावेश "portdrv.h"

#घोषणा AER_ERROR_SOURCES_MAX		128

#घोषणा AER_MAX_TYPखातापूर्ण_COR_ERRS		16	/* as per PCI_ERR_COR_STATUS */
#घोषणा AER_MAX_TYPखातापूर्ण_UNCOR_ERRS	27	/* as per PCI_ERR_UNCOR_STATUS*/

काष्ठा aer_err_source अणु
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक id;
पूर्ण;

काष्ठा aer_rpc अणु
	काष्ठा pci_dev *rpd;		/* Root Port device */
	DECLARE_KFIFO(aer_fअगरo, काष्ठा aer_err_source, AER_ERROR_SOURCES_MAX);
पूर्ण;

/* AER stats क्रम the device */
काष्ठा aer_stats अणु

	/*
	 * Fields क्रम all AER capable devices. They indicate the errors
	 * "as seen by this device". Note that this may mean that अगर an
	 * end poपूर्णांक is causing problems, the AER counters may increment
	 * at its link partner (e.g. root port) because the errors will be
	 * "seen" by the link partner and not the the problematic end poपूर्णांक
	 * itself (which may report all counters as 0 as it never saw any
	 * problems).
	 */
	/* Counters क्रम dअगरferent type of correctable errors */
	u64 dev_cor_errs[AER_MAX_TYPखातापूर्ण_COR_ERRS];
	/* Counters क्रम dअगरferent type of fatal uncorrectable errors */
	u64 dev_fatal_errs[AER_MAX_TYPखातापूर्ण_UNCOR_ERRS];
	/* Counters क्रम dअगरferent type of nonfatal uncorrectable errors */
	u64 dev_nonfatal_errs[AER_MAX_TYPखातापूर्ण_UNCOR_ERRS];
	/* Total number of ERR_COR sent by this device */
	u64 dev_total_cor_errs;
	/* Total number of ERR_FATAL sent by this device */
	u64 dev_total_fatal_errs;
	/* Total number of ERR_NONFATAL sent by this device */
	u64 dev_total_nonfatal_errs;

	/*
	 * Fields क्रम Root ports & root complex event collectors only, these
	 * indicate the total number of ERR_COR, ERR_FATAL, and ERR_NONFATAL
	 * messages received by the root port / event collector, INCLUDING the
	 * ones that are generated पूर्णांकernally (by the rootport itself)
	 */
	u64 rootport_total_cor_errs;
	u64 rootport_total_fatal_errs;
	u64 rootport_total_nonfatal_errs;
पूर्ण;

#घोषणा AER_LOG_TLP_MASKS		(PCI_ERR_UNC_POISON_TLP|	\
					PCI_ERR_UNC_ECRC|		\
					PCI_ERR_UNC_UNSUP|		\
					PCI_ERR_UNC_COMP_ABORT|		\
					PCI_ERR_UNC_UNX_COMP|		\
					PCI_ERR_UNC_MALF_TLP)

#घोषणा SYSTEM_ERROR_INTR_ON_MESG_MASK	(PCI_EXP_RTCTL_SECEE|	\
					PCI_EXP_RTCTL_SENFEE|	\
					PCI_EXP_RTCTL_SEFEE)
#घोषणा ROOT_PORT_INTR_ON_MESG_MASK	(PCI_ERR_ROOT_CMD_COR_EN|	\
					PCI_ERR_ROOT_CMD_NONFATAL_EN|	\
					PCI_ERR_ROOT_CMD_FATAL_EN)
#घोषणा ERR_COR_ID(d)			(d & 0xffff)
#घोषणा ERR_UNCOR_ID(d)			(d >> 16)

अटल पूर्णांक pcie_aer_disable;
अटल pci_ers_result_t aer_root_reset(काष्ठा pci_dev *dev);

व्योम pci_no_aer(व्योम)
अणु
	pcie_aer_disable = 1;
पूर्ण

bool pci_aer_available(व्योम)
अणु
	वापस !pcie_aer_disable && pci_msi_enabled();
पूर्ण

#अगर_घोषित CONFIG_PCIE_ECRC

#घोषणा ECRC_POLICY_DEFAULT 0		/* ECRC set by BIOS */
#घोषणा ECRC_POLICY_OFF     1		/* ECRC off क्रम perक्रमmance */
#घोषणा ECRC_POLICY_ON      2		/* ECRC on क्रम data पूर्णांकegrity */

अटल पूर्णांक ecrc_policy = ECRC_POLICY_DEFAULT;

अटल स्थिर अक्षर * स्थिर ecrc_policy_str[] = अणु
	[ECRC_POLICY_DEFAULT] = "bios",
	[ECRC_POLICY_OFF] = "off",
	[ECRC_POLICY_ON] = "on"
पूर्ण;

/**
 * enable_ecrc_checking - enable PCIe ECRC checking क्रम a device
 * @dev: the PCI device
 *
 * Returns 0 on success, or negative on failure.
 */
अटल पूर्णांक enable_ecrc_checking(काष्ठा pci_dev *dev)
अणु
	पूर्णांक aer = dev->aer_cap;
	u32 reg32;

	अगर (!aer)
		वापस -ENODEV;

	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_CAP, &reg32);
	अगर (reg32 & PCI_ERR_CAP_ECRC_GENC)
		reg32 |= PCI_ERR_CAP_ECRC_GENE;
	अगर (reg32 & PCI_ERR_CAP_ECRC_CHKC)
		reg32 |= PCI_ERR_CAP_ECRC_CHKE;
	pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_CAP, reg32);

	वापस 0;
पूर्ण

/**
 * disable_ecrc_checking - disables PCIe ECRC checking क्रम a device
 * @dev: the PCI device
 *
 * Returns 0 on success, or negative on failure.
 */
अटल पूर्णांक disable_ecrc_checking(काष्ठा pci_dev *dev)
अणु
	पूर्णांक aer = dev->aer_cap;
	u32 reg32;

	अगर (!aer)
		वापस -ENODEV;

	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_CAP, &reg32);
	reg32 &= ~(PCI_ERR_CAP_ECRC_GENE | PCI_ERR_CAP_ECRC_CHKE);
	pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_CAP, reg32);

	वापस 0;
पूर्ण

/**
 * pcie_set_ecrc_checking - set/unset PCIe ECRC checking क्रम a device based on global policy
 * @dev: the PCI device
 */
व्योम pcie_set_ecrc_checking(काष्ठा pci_dev *dev)
अणु
	चयन (ecrc_policy) अणु
	हाल ECRC_POLICY_DEFAULT:
		वापस;
	हाल ECRC_POLICY_OFF:
		disable_ecrc_checking(dev);
		अवरोध;
	हाल ECRC_POLICY_ON:
		enable_ecrc_checking(dev);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
पूर्ण

/**
 * pcie_ecrc_get_policy - parse kernel command-line ecrc option
 * @str: ECRC policy from kernel command line to use
 */
व्योम pcie_ecrc_get_policy(अक्षर *str)
अणु
	पूर्णांक i;

	i = match_string(ecrc_policy_str, ARRAY_SIZE(ecrc_policy_str), str);
	अगर (i < 0)
		वापस;

	ecrc_policy = i;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PCIE_ECRC */

#घोषणा	PCI_EXP_AER_FLAGS	(PCI_EXP_DEVCTL_CERE | PCI_EXP_DEVCTL_NFERE | \
				 PCI_EXP_DEVCTL_FERE | PCI_EXP_DEVCTL_URRE)

पूर्णांक pcie_aer_is_native(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_host_bridge *host = pci_find_host_bridge(dev->bus);

	अगर (!dev->aer_cap)
		वापस 0;

	वापस pcie_ports_native || host->native_aer;
पूर्ण

पूर्णांक pci_enable_pcie_error_reporting(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	अगर (!pcie_aer_is_native(dev))
		वापस -EIO;

	rc = pcie_capability_set_word(dev, PCI_EXP_DEVCTL, PCI_EXP_AER_FLAGS);
	वापस pcibios_err_to_त्रुटि_सं(rc);
पूर्ण
EXPORT_SYMBOL_GPL(pci_enable_pcie_error_reporting);

पूर्णांक pci_disable_pcie_error_reporting(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	अगर (!pcie_aer_is_native(dev))
		वापस -EIO;

	rc = pcie_capability_clear_word(dev, PCI_EXP_DEVCTL, PCI_EXP_AER_FLAGS);
	वापस pcibios_err_to_त्रुटि_सं(rc);
पूर्ण
EXPORT_SYMBOL_GPL(pci_disable_pcie_error_reporting);

पूर्णांक pci_aer_clear_nonfatal_status(काष्ठा pci_dev *dev)
अणु
	पूर्णांक aer = dev->aer_cap;
	u32 status, sev;

	अगर (!pcie_aer_is_native(dev))
		वापस -EIO;

	/* Clear status bits क्रम ERR_NONFATAL errors only */
	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_STATUS, &status);
	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_SEVER, &sev);
	status &= ~sev;
	अगर (status)
		pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_UNCOR_STATUS, status);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_aer_clear_nonfatal_status);

व्योम pci_aer_clear_fatal_status(काष्ठा pci_dev *dev)
अणु
	पूर्णांक aer = dev->aer_cap;
	u32 status, sev;

	अगर (!pcie_aer_is_native(dev))
		वापस;

	/* Clear status bits क्रम ERR_FATAL errors only */
	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_STATUS, &status);
	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_SEVER, &sev);
	status &= sev;
	अगर (status)
		pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_UNCOR_STATUS, status);
पूर्ण

/**
 * pci_aer_raw_clear_status - Clear AER error रेजिस्टरs.
 * @dev: the PCI device
 *
 * Clearing AER error status रेजिस्टरs unconditionally, regardless of
 * whether they're owned by firmware or the OS.
 *
 * Returns 0 on success, or negative on failure.
 */
पूर्णांक pci_aer_raw_clear_status(काष्ठा pci_dev *dev)
अणु
	पूर्णांक aer = dev->aer_cap;
	u32 status;
	पूर्णांक port_type;

	अगर (!aer)
		वापस -EIO;

	port_type = pci_pcie_type(dev);
	अगर (port_type == PCI_EXP_TYPE_ROOT_PORT ||
	    port_type == PCI_EXP_TYPE_RC_EC) अणु
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_ROOT_STATUS, &status);
		pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_ROOT_STATUS, status);
	पूर्ण

	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_COR_STATUS, &status);
	pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_COR_STATUS, status);

	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_STATUS, &status);
	pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_UNCOR_STATUS, status);

	वापस 0;
पूर्ण

पूर्णांक pci_aer_clear_status(काष्ठा pci_dev *dev)
अणु
	अगर (!pcie_aer_is_native(dev))
		वापस -EIO;

	वापस pci_aer_raw_clear_status(dev);
पूर्ण

व्योम pci_save_aer_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक aer = dev->aer_cap;
	काष्ठा pci_cap_saved_state *save_state;
	u32 *cap;

	अगर (!aer)
		वापस;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_ERR);
	अगर (!save_state)
		वापस;

	cap = &save_state->cap.data[0];
	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_MASK, cap++);
	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_SEVER, cap++);
	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_COR_MASK, cap++);
	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_CAP, cap++);
	अगर (pcie_cap_has_rtctl(dev))
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_ROOT_COMMAND, cap++);
पूर्ण

व्योम pci_restore_aer_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक aer = dev->aer_cap;
	काष्ठा pci_cap_saved_state *save_state;
	u32 *cap;

	अगर (!aer)
		वापस;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_ERR);
	अगर (!save_state)
		वापस;

	cap = &save_state->cap.data[0];
	pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_UNCOR_MASK, *cap++);
	pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_UNCOR_SEVER, *cap++);
	pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_COR_MASK, *cap++);
	pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_CAP, *cap++);
	अगर (pcie_cap_has_rtctl(dev))
		pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_ROOT_COMMAND, *cap++);
पूर्ण

व्योम pci_aer_init(काष्ठा pci_dev *dev)
अणु
	पूर्णांक n;

	dev->aer_cap = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR);
	अगर (!dev->aer_cap)
		वापस;

	dev->aer_stats = kzalloc(माप(काष्ठा aer_stats), GFP_KERNEL);

	/*
	 * We save/restore PCI_ERR_UNCOR_MASK, PCI_ERR_UNCOR_SEVER,
	 * PCI_ERR_COR_MASK, and PCI_ERR_CAP.  Root and Root Complex Event
	 * Collectors also implement PCI_ERR_ROOT_COMMAND (PCIe r5.0, sec
	 * 7.8.4).
	 */
	n = pcie_cap_has_rtctl(dev) ? 5 : 4;
	pci_add_ext_cap_save_buffer(dev, PCI_EXT_CAP_ID_ERR, माप(u32) * n);

	pci_aer_clear_status(dev);
पूर्ण

व्योम pci_aer_निकास(काष्ठा pci_dev *dev)
अणु
	kमुक्त(dev->aer_stats);
	dev->aer_stats = शून्य;
पूर्ण

#घोषणा AER_AGENT_RECEIVER		0
#घोषणा AER_AGENT_REQUESTER		1
#घोषणा AER_AGENT_COMPLETER		2
#घोषणा AER_AGENT_TRANSMITTER		3

#घोषणा AER_AGENT_REQUESTER_MASK(t)	((t == AER_CORRECTABLE) ?	\
	0 : (PCI_ERR_UNC_COMP_TIME|PCI_ERR_UNC_UNSUP))
#घोषणा AER_AGENT_COMPLETER_MASK(t)	((t == AER_CORRECTABLE) ?	\
	0 : PCI_ERR_UNC_COMP_ABORT)
#घोषणा AER_AGENT_TRANSMITTER_MASK(t)	((t == AER_CORRECTABLE) ?	\
	(PCI_ERR_COR_REP_ROLL|PCI_ERR_COR_REP_TIMER) : 0)

#घोषणा AER_GET_AGENT(t, e)						\
	((e & AER_AGENT_COMPLETER_MASK(t)) ? AER_AGENT_COMPLETER :	\
	(e & AER_AGENT_REQUESTER_MASK(t)) ? AER_AGENT_REQUESTER :	\
	(e & AER_AGENT_TRANSMITTER_MASK(t)) ? AER_AGENT_TRANSMITTER :	\
	AER_AGENT_RECEIVER)

#घोषणा AER_PHYSICAL_LAYER_ERROR	0
#घोषणा AER_DATA_LINK_LAYER_ERROR	1
#घोषणा AER_TRANSACTION_LAYER_ERROR	2

#घोषणा AER_PHYSICAL_LAYER_ERROR_MASK(t) ((t == AER_CORRECTABLE) ?	\
	PCI_ERR_COR_RCVR : 0)
#घोषणा AER_DATA_LINK_LAYER_ERROR_MASK(t) ((t == AER_CORRECTABLE) ?	\
	(PCI_ERR_COR_BAD_TLP|						\
	PCI_ERR_COR_BAD_DLLP|						\
	PCI_ERR_COR_REP_ROLL|						\
	PCI_ERR_COR_REP_TIMER) : PCI_ERR_UNC_DLP)

#घोषणा AER_GET_LAYER_ERROR(t, e)					\
	((e & AER_PHYSICAL_LAYER_ERROR_MASK(t)) ? AER_PHYSICAL_LAYER_ERROR : \
	(e & AER_DATA_LINK_LAYER_ERROR_MASK(t)) ? AER_DATA_LINK_LAYER_ERROR : \
	AER_TRANSACTION_LAYER_ERROR)

/*
 * AER error strings
 */
अटल स्थिर अक्षर *aer_error_severity_string[] = अणु
	"Uncorrected (Non-Fatal)",
	"Uncorrected (Fatal)",
	"Corrected"
पूर्ण;

अटल स्थिर अक्षर *aer_error_layer[] = अणु
	"Physical Layer",
	"Data Link Layer",
	"Transaction Layer"
पूर्ण;

अटल स्थिर अक्षर *aer_correctable_error_string[] = अणु
	"RxErr",			/* Bit Position 0	*/
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	"BadTLP",			/* Bit Position 6	*/
	"BadDLLP",			/* Bit Position 7	*/
	"Rollover",			/* Bit Position 8	*/
	शून्य,
	शून्य,
	शून्य,
	"Timeout",			/* Bit Position 12	*/
	"NonFatalErr",			/* Bit Position 13	*/
	"CorrIntErr",			/* Bit Position 14	*/
	"HeaderOF",			/* Bit Position 15	*/
	शून्य,				/* Bit Position 16	*/
	शून्य,				/* Bit Position 17	*/
	शून्य,				/* Bit Position 18	*/
	शून्य,				/* Bit Position 19	*/
	शून्य,				/* Bit Position 20	*/
	शून्य,				/* Bit Position 21	*/
	शून्य,				/* Bit Position 22	*/
	शून्य,				/* Bit Position 23	*/
	शून्य,				/* Bit Position 24	*/
	शून्य,				/* Bit Position 25	*/
	शून्य,				/* Bit Position 26	*/
	शून्य,				/* Bit Position 27	*/
	शून्य,				/* Bit Position 28	*/
	शून्य,				/* Bit Position 29	*/
	शून्य,				/* Bit Position 30	*/
	शून्य,				/* Bit Position 31	*/
पूर्ण;

अटल स्थिर अक्षर *aer_uncorrectable_error_string[] = अणु
	"Undefined",			/* Bit Position 0	*/
	शून्य,
	शून्य,
	शून्य,
	"DLP",				/* Bit Position 4	*/
	"SDES",				/* Bit Position 5	*/
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	"TLP",				/* Bit Position 12	*/
	"FCP",				/* Bit Position 13	*/
	"CmpltTO",			/* Bit Position 14	*/
	"CmpltAbrt",			/* Bit Position 15	*/
	"UnxCmplt",			/* Bit Position 16	*/
	"RxOF",				/* Bit Position 17	*/
	"MalfTLP",			/* Bit Position 18	*/
	"ECRC",				/* Bit Position 19	*/
	"UnsupReq",			/* Bit Position 20	*/
	"ACSViol",			/* Bit Position 21	*/
	"UncorrIntErr",			/* Bit Position 22	*/
	"BlockedTLP",			/* Bit Position 23	*/
	"AtomicOpBlocked",		/* Bit Position 24	*/
	"TLPBlockedErr",		/* Bit Position 25	*/
	"PoisonTLPBlocked",		/* Bit Position 26	*/
	शून्य,				/* Bit Position 27	*/
	शून्य,				/* Bit Position 28	*/
	शून्य,				/* Bit Position 29	*/
	शून्य,				/* Bit Position 30	*/
	शून्य,				/* Bit Position 31	*/
पूर्ण;

अटल स्थिर अक्षर *aer_agent_string[] = अणु
	"Receiver ID",
	"Requester ID",
	"Completer ID",
	"Transmitter ID"
पूर्ण;

#घोषणा aer_stats_dev_attr(name, stats_array, strings_array,		\
			   total_string, total_field)			\
	अटल sमाप_प्रकार							\
	name##_show(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		     अक्षर *buf)						\
अणु									\
	अचिन्हित पूर्णांक i;							\
	अक्षर *str = buf;						\
	काष्ठा pci_dev *pdev = to_pci_dev(dev);				\
	u64 *stats = pdev->aer_stats->stats_array;			\
									\
	क्रम (i = 0; i < ARRAY_SIZE(strings_array); i++) अणु		\
		अगर (strings_array[i])					\
			str += प्र_लिखो(str, "%s %llu\n",		\
				       strings_array[i], stats[i]);	\
		अन्यथा अगर (stats[i])					\
			str += प्र_लिखो(str, #stats_array "_bit[%d] %llu\n",\
				       i, stats[i]);			\
	पूर्ण								\
	str += प्र_लिखो(str, "TOTAL_%s %llu\n", total_string,		\
		       pdev->aer_stats->total_field);			\
	वापस str-buf;							\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

aer_stats_dev_attr(aer_dev_correctable, dev_cor_errs,
		   aer_correctable_error_string, "ERR_COR",
		   dev_total_cor_errs);
aer_stats_dev_attr(aer_dev_fatal, dev_fatal_errs,
		   aer_uncorrectable_error_string, "ERR_FATAL",
		   dev_total_fatal_errs);
aer_stats_dev_attr(aer_dev_nonfatal, dev_nonfatal_errs,
		   aer_uncorrectable_error_string, "ERR_NONFATAL",
		   dev_total_nonfatal_errs);

#घोषणा aer_stats_rootport_attr(name, field)				\
	अटल sमाप_प्रकार							\
	name##_show(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		     अक्षर *buf)						\
अणु									\
	काष्ठा pci_dev *pdev = to_pci_dev(dev);				\
	वापस प्र_लिखो(buf, "%llu\n", pdev->aer_stats->field);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

aer_stats_rootport_attr(aer_rootport_total_err_cor,
			 rootport_total_cor_errs);
aer_stats_rootport_attr(aer_rootport_total_err_fatal,
			 rootport_total_fatal_errs);
aer_stats_rootport_attr(aer_rootport_total_err_nonfatal,
			 rootport_total_nonfatal_errs);

अटल काष्ठा attribute *aer_stats_attrs[] __ro_after_init = अणु
	&dev_attr_aer_dev_correctable.attr,
	&dev_attr_aer_dev_fatal.attr,
	&dev_attr_aer_dev_nonfatal.attr,
	&dev_attr_aer_rootport_total_err_cor.attr,
	&dev_attr_aer_rootport_total_err_fatal.attr,
	&dev_attr_aer_rootport_total_err_nonfatal.attr,
	शून्य
पूर्ण;

अटल umode_t aer_stats_attrs_are_visible(काष्ठा kobject *kobj,
					   काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (!pdev->aer_stats)
		वापस 0;

	अगर ((a == &dev_attr_aer_rootport_total_err_cor.attr ||
	     a == &dev_attr_aer_rootport_total_err_fatal.attr ||
	     a == &dev_attr_aer_rootport_total_err_nonfatal.attr) &&
	    ((pci_pcie_type(pdev) != PCI_EXP_TYPE_ROOT_PORT) &&
	     (pci_pcie_type(pdev) != PCI_EXP_TYPE_RC_EC)))
		वापस 0;

	वापस a->mode;
पूर्ण

स्थिर काष्ठा attribute_group aer_stats_attr_group = अणु
	.attrs  = aer_stats_attrs,
	.is_visible = aer_stats_attrs_are_visible,
पूर्ण;

अटल व्योम pci_dev_aer_stats_incr(काष्ठा pci_dev *pdev,
				   काष्ठा aer_err_info *info)
अणु
	अचिन्हित दीर्घ status = info->status & ~info->mask;
	पूर्णांक i, max = -1;
	u64 *counter = शून्य;
	काष्ठा aer_stats *aer_stats = pdev->aer_stats;

	अगर (!aer_stats)
		वापस;

	चयन (info->severity) अणु
	हाल AER_CORRECTABLE:
		aer_stats->dev_total_cor_errs++;
		counter = &aer_stats->dev_cor_errs[0];
		max = AER_MAX_TYPखातापूर्ण_COR_ERRS;
		अवरोध;
	हाल AER_NONFATAL:
		aer_stats->dev_total_nonfatal_errs++;
		counter = &aer_stats->dev_nonfatal_errs[0];
		max = AER_MAX_TYPखातापूर्ण_UNCOR_ERRS;
		अवरोध;
	हाल AER_FATAL:
		aer_stats->dev_total_fatal_errs++;
		counter = &aer_stats->dev_fatal_errs[0];
		max = AER_MAX_TYPखातापूर्ण_UNCOR_ERRS;
		अवरोध;
	पूर्ण

	क्रम_each_set_bit(i, &status, max)
		counter[i]++;
पूर्ण

अटल व्योम pci_rootport_aer_stats_incr(काष्ठा pci_dev *pdev,
				 काष्ठा aer_err_source *e_src)
अणु
	काष्ठा aer_stats *aer_stats = pdev->aer_stats;

	अगर (!aer_stats)
		वापस;

	अगर (e_src->status & PCI_ERR_ROOT_COR_RCV)
		aer_stats->rootport_total_cor_errs++;

	अगर (e_src->status & PCI_ERR_ROOT_UNCOR_RCV) अणु
		अगर (e_src->status & PCI_ERR_ROOT_FATAL_RCV)
			aer_stats->rootport_total_fatal_errs++;
		अन्यथा
			aer_stats->rootport_total_nonfatal_errs++;
	पूर्ण
पूर्ण

अटल व्योम __prपूर्णांक_tlp_header(काष्ठा pci_dev *dev,
			       काष्ठा aer_header_log_regs *t)
अणु
	pci_err(dev, "  TLP Header: %08x %08x %08x %08x\n",
		t->dw0, t->dw1, t->dw2, t->dw3);
पूर्ण

अटल व्योम __aer_prपूर्णांक_error(काष्ठा pci_dev *dev,
			      काष्ठा aer_err_info *info)
अणु
	स्थिर अक्षर **strings;
	अचिन्हित दीर्घ status = info->status & ~info->mask;
	स्थिर अक्षर *level, *errmsg;
	पूर्णांक i;

	अगर (info->severity == AER_CORRECTABLE) अणु
		strings = aer_correctable_error_string;
		level = KERN_WARNING;
	पूर्ण अन्यथा अणु
		strings = aer_uncorrectable_error_string;
		level = KERN_ERR;
	पूर्ण

	क्रम_each_set_bit(i, &status, 32) अणु
		errmsg = strings[i];
		अगर (!errmsg)
			errmsg = "Unknown Error Bit";

		pci_prपूर्णांकk(level, dev, "   [%2d] %-22s%s\n", i, errmsg,
				info->first_error == i ? " (First)" : "");
	पूर्ण
	pci_dev_aer_stats_incr(dev, info);
पूर्ण

व्योम aer_prपूर्णांक_error(काष्ठा pci_dev *dev, काष्ठा aer_err_info *info)
अणु
	पूर्णांक layer, agent;
	पूर्णांक id = ((dev->bus->number << 8) | dev->devfn);
	स्थिर अक्षर *level;

	अगर (!info->status) अणु
		pci_err(dev, "PCIe Bus Error: severity=%s, type=Inaccessible, (Unregistered Agent ID)\n",
			aer_error_severity_string[info->severity]);
		जाओ out;
	पूर्ण

	layer = AER_GET_LAYER_ERROR(info->severity, info->status);
	agent = AER_GET_AGENT(info->severity, info->status);

	level = (info->severity == AER_CORRECTABLE) ? KERN_WARNING : KERN_ERR;

	pci_prपूर्णांकk(level, dev, "PCIe Bus Error: severity=%s, type=%s, (%s)\n",
		   aer_error_severity_string[info->severity],
		   aer_error_layer[layer], aer_agent_string[agent]);

	pci_prपूर्णांकk(level, dev, "  device [%04x:%04x] error status/mask=%08x/%08x\n",
		   dev->venकरोr, dev->device, info->status, info->mask);

	__aer_prपूर्णांक_error(dev, info);

	अगर (info->tlp_header_valid)
		__prपूर्णांक_tlp_header(dev, &info->tlp);

out:
	अगर (info->id && info->error_dev_num > 1 && info->id == id)
		pci_err(dev, "  Error of this Agent is reported first\n");

	trace_aer_event(dev_name(&dev->dev), (info->status & ~info->mask),
			info->severity, info->tlp_header_valid, &info->tlp);
पूर्ण

अटल व्योम aer_prपूर्णांक_port_info(काष्ठा pci_dev *dev, काष्ठा aer_err_info *info)
अणु
	u8 bus = info->id >> 8;
	u8 devfn = info->id & 0xff;

	pci_info(dev, "%s%s error received: %04x:%02x:%02x.%d\n",
		 info->multi_error_valid ? "Multiple " : "",
		 aer_error_severity_string[info->severity],
		 pci_करोमुख्य_nr(dev->bus), bus, PCI_SLOT(devfn),
		 PCI_FUNC(devfn));
पूर्ण

#अगर_घोषित CONFIG_ACPI_APEI_PCIEAER
पूर्णांक cper_severity_to_aer(पूर्णांक cper_severity)
अणु
	चयन (cper_severity) अणु
	हाल CPER_SEV_RECOVERABLE:
		वापस AER_NONFATAL;
	हाल CPER_SEV_FATAL:
		वापस AER_FATAL;
	शेष:
		वापस AER_CORRECTABLE;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cper_severity_to_aer);

व्योम cper_prपूर्णांक_aer(काष्ठा pci_dev *dev, पूर्णांक aer_severity,
		    काष्ठा aer_capability_regs *aer)
अणु
	पूर्णांक layer, agent, tlp_header_valid = 0;
	u32 status, mask;
	काष्ठा aer_err_info info;

	अगर (aer_severity == AER_CORRECTABLE) अणु
		status = aer->cor_status;
		mask = aer->cor_mask;
	पूर्ण अन्यथा अणु
		status = aer->uncor_status;
		mask = aer->uncor_mask;
		tlp_header_valid = status & AER_LOG_TLP_MASKS;
	पूर्ण

	layer = AER_GET_LAYER_ERROR(aer_severity, status);
	agent = AER_GET_AGENT(aer_severity, status);

	स_रखो(&info, 0, माप(info));
	info.severity = aer_severity;
	info.status = status;
	info.mask = mask;
	info.first_error = PCI_ERR_CAP_FEP(aer->cap_control);

	pci_err(dev, "aer_status: 0x%08x, aer_mask: 0x%08x\n", status, mask);
	__aer_prपूर्णांक_error(dev, &info);
	pci_err(dev, "aer_layer=%s, aer_agent=%s\n",
		aer_error_layer[layer], aer_agent_string[agent]);

	अगर (aer_severity != AER_CORRECTABLE)
		pci_err(dev, "aer_uncor_severity: 0x%08x\n",
			aer->uncor_severity);

	अगर (tlp_header_valid)
		__prपूर्णांक_tlp_header(dev, &aer->header_log);

	trace_aer_event(dev_name(&dev->dev), (status & ~mask),
			aer_severity, tlp_header_valid, &aer->header_log);
पूर्ण
#पूर्ण_अगर

/**
 * add_error_device - list device to be handled
 * @e_info: poपूर्णांकer to error info
 * @dev: poपूर्णांकer to pci_dev to be added
 */
अटल पूर्णांक add_error_device(काष्ठा aer_err_info *e_info, काष्ठा pci_dev *dev)
अणु
	अगर (e_info->error_dev_num < AER_MAX_MULTI_ERR_DEVICES) अणु
		e_info->dev[e_info->error_dev_num] = pci_dev_get(dev);
		e_info->error_dev_num++;
		वापस 0;
	पूर्ण
	वापस -ENOSPC;
पूर्ण

/**
 * is_error_source - check whether the device is source of reported error
 * @dev: poपूर्णांकer to pci_dev to be checked
 * @e_info: poपूर्णांकer to reported error info
 */
अटल bool is_error_source(काष्ठा pci_dev *dev, काष्ठा aer_err_info *e_info)
अणु
	पूर्णांक aer = dev->aer_cap;
	u32 status, mask;
	u16 reg16;

	/*
	 * When bus id is equal to 0, it might be a bad id
	 * reported by root port.
	 */
	अगर ((PCI_BUS_NUM(e_info->id) != 0) &&
	    !(dev->bus->bus_flags & PCI_BUS_FLAGS_NO_AERSID)) अणु
		/* Device ID match? */
		अगर (e_info->id == ((dev->bus->number << 8) | dev->devfn))
			वापस true;

		/* Continue id comparing अगर there is no multiple error */
		अगर (!e_info->multi_error_valid)
			वापस false;
	पूर्ण

	/*
	 * When either
	 *      1) bus id is equal to 0. Some ports might lose the bus
	 *              id of error source id;
	 *      2) bus flag PCI_BUS_FLAGS_NO_AERSID is set
	 *      3) There are multiple errors and prior ID comparing fails;
	 * We check AER status रेजिस्टरs to find possible reporter.
	 */
	अगर (atomic_पढ़ो(&dev->enable_cnt) == 0)
		वापस false;

	/* Check अगर AER is enabled */
	pcie_capability_पढ़ो_word(dev, PCI_EXP_DEVCTL, &reg16);
	अगर (!(reg16 & PCI_EXP_AER_FLAGS))
		वापस false;

	अगर (!aer)
		वापस false;

	/* Check अगर error is recorded */
	अगर (e_info->severity == AER_CORRECTABLE) अणु
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_COR_STATUS, &status);
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_COR_MASK, &mask);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_STATUS, &status);
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_MASK, &mask);
	पूर्ण
	अगर (status & ~mask)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक find_device_iter(काष्ठा pci_dev *dev, व्योम *data)
अणु
	काष्ठा aer_err_info *e_info = (काष्ठा aer_err_info *)data;

	अगर (is_error_source(dev, e_info)) अणु
		/* List this device */
		अगर (add_error_device(e_info, dev)) अणु
			/* We cannot handle more... Stop iteration */
			/* TODO: Should prपूर्णांक error message here? */
			वापस 1;
		पूर्ण

		/* If there is only a single error, stop iteration */
		अगर (!e_info->multi_error_valid)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * find_source_device - search through device hierarchy क्रम source device
 * @parent: poपूर्णांकer to Root Port pci_dev data काष्ठाure
 * @e_info: including detailed error inक्रमmation such like id
 *
 * Return true अगर found.
 *
 * Invoked by DPC when error is detected at the Root Port.
 * Caller of this function must set id, severity, and multi_error_valid of
 * काष्ठा aer_err_info poपूर्णांकed by @e_info properly.  This function must fill
 * e_info->error_dev_num and e_info->dev[], based on the given inक्रमmation.
 */
अटल bool find_source_device(काष्ठा pci_dev *parent,
		काष्ठा aer_err_info *e_info)
अणु
	काष्ठा pci_dev *dev = parent;
	पूर्णांक result;

	/* Must reset in this function */
	e_info->error_dev_num = 0;

	/* Is Root Port an agent that sends error message? */
	result = find_device_iter(dev, e_info);
	अगर (result)
		वापस true;

	अगर (pci_pcie_type(parent) == PCI_EXP_TYPE_RC_EC)
		pcie_walk_rcec(parent, find_device_iter, e_info);
	अन्यथा
		pci_walk_bus(parent->subordinate, find_device_iter, e_info);

	अगर (!e_info->error_dev_num) अणु
		pci_info(parent, "can't find device of ID%04x\n", e_info->id);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * handle_error_source - handle logging error पूर्णांकo an event log
 * @dev: poपूर्णांकer to pci_dev data काष्ठाure of error source device
 * @info: comprehensive error inक्रमmation
 *
 * Invoked when an error being detected by Root Port.
 */
अटल व्योम handle_error_source(काष्ठा pci_dev *dev, काष्ठा aer_err_info *info)
अणु
	पूर्णांक aer = dev->aer_cap;

	अगर (info->severity == AER_CORRECTABLE) अणु
		/*
		 * Correctable error करोes not need software पूर्णांकervention.
		 * No need to go through error recovery process.
		 */
		अगर (aer)
			pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_COR_STATUS,
					info->status);
		अगर (pcie_aer_is_native(dev))
			pcie_clear_device_status(dev);
	पूर्ण अन्यथा अगर (info->severity == AER_NONFATAL)
		pcie_करो_recovery(dev, pci_channel_io_normal, aer_root_reset);
	अन्यथा अगर (info->severity == AER_FATAL)
		pcie_करो_recovery(dev, pci_channel_io_frozen, aer_root_reset);
	pci_dev_put(dev);
पूर्ण

#अगर_घोषित CONFIG_ACPI_APEI_PCIEAER

#घोषणा AER_RECOVER_RING_ORDER		4
#घोषणा AER_RECOVER_RING_SIZE		(1 << AER_RECOVER_RING_ORDER)

काष्ठा aer_recover_entry अणु
	u8	bus;
	u8	devfn;
	u16	करोमुख्य;
	पूर्णांक	severity;
	काष्ठा aer_capability_regs *regs;
पूर्ण;

अटल DEFINE_KFIFO(aer_recover_ring, काष्ठा aer_recover_entry,
		    AER_RECOVER_RING_SIZE);

अटल व्योम aer_recover_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aer_recover_entry entry;
	काष्ठा pci_dev *pdev;

	जबतक (kfअगरo_get(&aer_recover_ring, &entry)) अणु
		pdev = pci_get_करोमुख्य_bus_and_slot(entry.करोमुख्य, entry.bus,
						   entry.devfn);
		अगर (!pdev) अणु
			pr_err("AER recover: Can not find pci_dev for %04x:%02x:%02x:%x\n",
			       entry.करोमुख्य, entry.bus,
			       PCI_SLOT(entry.devfn), PCI_FUNC(entry.devfn));
			जारी;
		पूर्ण
		cper_prपूर्णांक_aer(pdev, entry.severity, entry.regs);
		अगर (entry.severity == AER_NONFATAL)
			pcie_करो_recovery(pdev, pci_channel_io_normal,
					 aer_root_reset);
		अन्यथा अगर (entry.severity == AER_FATAL)
			pcie_करो_recovery(pdev, pci_channel_io_frozen,
					 aer_root_reset);
		pci_dev_put(pdev);
	पूर्ण
पूर्ण

/*
 * Mutual exclusion क्रम ग_लिखोrs of aer_recover_ring, पढ़ोer side करोn't
 * need lock, because there is only one पढ़ोer and lock is not needed
 * between पढ़ोer and ग_लिखोr.
 */
अटल DEFINE_SPINLOCK(aer_recover_ring_lock);
अटल DECLARE_WORK(aer_recover_work, aer_recover_work_func);

व्योम aer_recover_queue(पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
		       पूर्णांक severity, काष्ठा aer_capability_regs *aer_regs)
अणु
	काष्ठा aer_recover_entry entry = अणु
		.bus		= bus,
		.devfn		= devfn,
		.करोमुख्य		= करोमुख्य,
		.severity	= severity,
		.regs		= aer_regs,
	पूर्ण;

	अगर (kfअगरo_in_spinlocked(&aer_recover_ring, &entry, 1,
				 &aer_recover_ring_lock))
		schedule_work(&aer_recover_work);
	अन्यथा
		pr_err("AER recover: Buffer overflow when recovering AER for %04x:%02x:%02x:%x\n",
		       करोमुख्य, bus, PCI_SLOT(devfn), PCI_FUNC(devfn));
पूर्ण
EXPORT_SYMBOL_GPL(aer_recover_queue);
#पूर्ण_अगर

/**
 * aer_get_device_error_info - पढ़ो error status from dev and store it to info
 * @dev: poपूर्णांकer to the device expected to have a error record
 * @info: poपूर्णांकer to काष्ठाure to store the error record
 *
 * Return 1 on success, 0 on error.
 *
 * Note that @info is reused among all error devices. Clear fields properly.
 */
पूर्णांक aer_get_device_error_info(काष्ठा pci_dev *dev, काष्ठा aer_err_info *info)
अणु
	पूर्णांक type = pci_pcie_type(dev);
	पूर्णांक aer = dev->aer_cap;
	पूर्णांक temp;

	/* Must reset in this function */
	info->status = 0;
	info->tlp_header_valid = 0;

	/* The device might not support AER */
	अगर (!aer)
		वापस 0;

	अगर (info->severity == AER_CORRECTABLE) अणु
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_COR_STATUS,
			&info->status);
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_COR_MASK,
			&info->mask);
		अगर (!(info->status & ~info->mask))
			वापस 0;
	पूर्ण अन्यथा अगर (type == PCI_EXP_TYPE_ROOT_PORT ||
		   type == PCI_EXP_TYPE_RC_EC ||
		   type == PCI_EXP_TYPE_DOWNSTREAM ||
		   info->severity == AER_NONFATAL) अणु

		/* Link is still healthy क्रम IO पढ़ोs */
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_STATUS,
			&info->status);
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_MASK,
			&info->mask);
		अगर (!(info->status & ~info->mask))
			वापस 0;

		/* Get First Error Poपूर्णांकer */
		pci_पढ़ो_config_dword(dev, aer + PCI_ERR_CAP, &temp);
		info->first_error = PCI_ERR_CAP_FEP(temp);

		अगर (info->status & AER_LOG_TLP_MASKS) अणु
			info->tlp_header_valid = 1;
			pci_पढ़ो_config_dword(dev,
				aer + PCI_ERR_HEADER_LOG, &info->tlp.dw0);
			pci_पढ़ो_config_dword(dev,
				aer + PCI_ERR_HEADER_LOG + 4, &info->tlp.dw1);
			pci_पढ़ो_config_dword(dev,
				aer + PCI_ERR_HEADER_LOG + 8, &info->tlp.dw2);
			pci_पढ़ो_config_dword(dev,
				aer + PCI_ERR_HEADER_LOG + 12, &info->tlp.dw3);
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत व्योम aer_process_err_devices(काष्ठा aer_err_info *e_info)
अणु
	पूर्णांक i;

	/* Report all beक्रमe handle them, not to lost records by reset etc. */
	क्रम (i = 0; i < e_info->error_dev_num && e_info->dev[i]; i++) अणु
		अगर (aer_get_device_error_info(e_info->dev[i], e_info))
			aer_prपूर्णांक_error(e_info->dev[i], e_info);
	पूर्ण
	क्रम (i = 0; i < e_info->error_dev_num && e_info->dev[i]; i++) अणु
		अगर (aer_get_device_error_info(e_info->dev[i], e_info))
			handle_error_source(e_info->dev[i], e_info);
	पूर्ण
पूर्ण

/**
 * aer_isr_one_error - consume an error detected by root port
 * @rpc: poपूर्णांकer to the root port which holds an error
 * @e_src: poपूर्णांकer to an error source
 */
अटल व्योम aer_isr_one_error(काष्ठा aer_rpc *rpc,
		काष्ठा aer_err_source *e_src)
अणु
	काष्ठा pci_dev *pdev = rpc->rpd;
	काष्ठा aer_err_info e_info;

	pci_rootport_aer_stats_incr(pdev, e_src);

	/*
	 * There is a possibility that both correctable error and
	 * uncorrectable error being logged. Report correctable error first.
	 */
	अगर (e_src->status & PCI_ERR_ROOT_COR_RCV) अणु
		e_info.id = ERR_COR_ID(e_src->id);
		e_info.severity = AER_CORRECTABLE;

		अगर (e_src->status & PCI_ERR_ROOT_MULTI_COR_RCV)
			e_info.multi_error_valid = 1;
		अन्यथा
			e_info.multi_error_valid = 0;
		aer_prपूर्णांक_port_info(pdev, &e_info);

		अगर (find_source_device(pdev, &e_info))
			aer_process_err_devices(&e_info);
	पूर्ण

	अगर (e_src->status & PCI_ERR_ROOT_UNCOR_RCV) अणु
		e_info.id = ERR_UNCOR_ID(e_src->id);

		अगर (e_src->status & PCI_ERR_ROOT_FATAL_RCV)
			e_info.severity = AER_FATAL;
		अन्यथा
			e_info.severity = AER_NONFATAL;

		अगर (e_src->status & PCI_ERR_ROOT_MULTI_UNCOR_RCV)
			e_info.multi_error_valid = 1;
		अन्यथा
			e_info.multi_error_valid = 0;

		aer_prपूर्णांक_port_info(pdev, &e_info);

		अगर (find_source_device(pdev, &e_info))
			aer_process_err_devices(&e_info);
	पूर्ण
पूर्ण

/**
 * aer_isr - consume errors detected by root port
 * @irq: IRQ asचिन्हित to Root Port
 * @context: poपूर्णांकer to Root Port data काष्ठाure
 *
 * Invoked, as DPC, when root port records new detected error
 */
अटल irqवापस_t aer_isr(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा pcie_device *dev = (काष्ठा pcie_device *)context;
	काष्ठा aer_rpc *rpc = get_service_data(dev);
	काष्ठा aer_err_source e_src;

	अगर (kfअगरo_is_empty(&rpc->aer_fअगरo))
		वापस IRQ_NONE;

	जबतक (kfअगरo_get(&rpc->aer_fअगरo, &e_src))
		aer_isr_one_error(rpc, &e_src);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * aer_irq - Root Port's ISR
 * @irq: IRQ asचिन्हित to Root Port
 * @context: poपूर्णांकer to Root Port data काष्ठाure
 *
 * Invoked when Root Port detects AER messages.
 */
अटल irqवापस_t aer_irq(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा pcie_device *pdev = (काष्ठा pcie_device *)context;
	काष्ठा aer_rpc *rpc = get_service_data(pdev);
	काष्ठा pci_dev *rp = rpc->rpd;
	पूर्णांक aer = rp->aer_cap;
	काष्ठा aer_err_source e_src = अणुपूर्ण;

	pci_पढ़ो_config_dword(rp, aer + PCI_ERR_ROOT_STATUS, &e_src.status);
	अगर (!(e_src.status & (PCI_ERR_ROOT_UNCOR_RCV|PCI_ERR_ROOT_COR_RCV)))
		वापस IRQ_NONE;

	pci_पढ़ो_config_dword(rp, aer + PCI_ERR_ROOT_ERR_SRC, &e_src.id);
	pci_ग_लिखो_config_dword(rp, aer + PCI_ERR_ROOT_STATUS, e_src.status);

	अगर (!kfअगरo_put(&rpc->aer_fअगरo, e_src))
		वापस IRQ_HANDLED;

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक set_device_error_reporting(काष्ठा pci_dev *dev, व्योम *data)
अणु
	bool enable = *((bool *)data);
	पूर्णांक type = pci_pcie_type(dev);

	अगर ((type == PCI_EXP_TYPE_ROOT_PORT) ||
	    (type == PCI_EXP_TYPE_RC_EC) ||
	    (type == PCI_EXP_TYPE_UPSTREAM) ||
	    (type == PCI_EXP_TYPE_DOWNSTREAM)) अणु
		अगर (enable)
			pci_enable_pcie_error_reporting(dev);
		अन्यथा
			pci_disable_pcie_error_reporting(dev);
	पूर्ण

	अगर (enable)
		pcie_set_ecrc_checking(dev);

	वापस 0;
पूर्ण

/**
 * set_करोwnstream_devices_error_reporting - enable/disable the error reporting  bits on the root port and its करोwnstream ports.
 * @dev: poपूर्णांकer to root port's pci_dev data काष्ठाure
 * @enable: true = enable error reporting, false = disable error reporting.
 */
अटल व्योम set_करोwnstream_devices_error_reporting(काष्ठा pci_dev *dev,
						   bool enable)
अणु
	set_device_error_reporting(dev, &enable);

	अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_RC_EC)
		pcie_walk_rcec(dev, set_device_error_reporting, &enable);
	अन्यथा अगर (dev->subordinate)
		pci_walk_bus(dev->subordinate, set_device_error_reporting,
			     &enable);

पूर्ण

/**
 * aer_enable_rootport - enable Root Port's पूर्णांकerrupts when receiving messages
 * @rpc: poपूर्णांकer to a Root Port data काष्ठाure
 *
 * Invoked when PCIe bus loads AER service driver.
 */
अटल व्योम aer_enable_rootport(काष्ठा aer_rpc *rpc)
अणु
	काष्ठा pci_dev *pdev = rpc->rpd;
	पूर्णांक aer = pdev->aer_cap;
	u16 reg16;
	u32 reg32;

	/* Clear PCIe Capability's Device Status */
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_DEVSTA, &reg16);
	pcie_capability_ग_लिखो_word(pdev, PCI_EXP_DEVSTA, reg16);

	/* Disable प्रणाली error generation in response to error messages */
	pcie_capability_clear_word(pdev, PCI_EXP_RTCTL,
				   SYSTEM_ERROR_INTR_ON_MESG_MASK);

	/* Clear error status */
	pci_पढ़ो_config_dword(pdev, aer + PCI_ERR_ROOT_STATUS, &reg32);
	pci_ग_लिखो_config_dword(pdev, aer + PCI_ERR_ROOT_STATUS, reg32);
	pci_पढ़ो_config_dword(pdev, aer + PCI_ERR_COR_STATUS, &reg32);
	pci_ग_लिखो_config_dword(pdev, aer + PCI_ERR_COR_STATUS, reg32);
	pci_पढ़ो_config_dword(pdev, aer + PCI_ERR_UNCOR_STATUS, &reg32);
	pci_ग_लिखो_config_dword(pdev, aer + PCI_ERR_UNCOR_STATUS, reg32);

	/*
	 * Enable error reporting क्रम the root port device and करोwnstream port
	 * devices.
	 */
	set_करोwnstream_devices_error_reporting(pdev, true);

	/* Enable Root Port's पूर्णांकerrupt in response to error messages */
	pci_पढ़ो_config_dword(pdev, aer + PCI_ERR_ROOT_COMMAND, &reg32);
	reg32 |= ROOT_PORT_INTR_ON_MESG_MASK;
	pci_ग_लिखो_config_dword(pdev, aer + PCI_ERR_ROOT_COMMAND, reg32);
पूर्ण

/**
 * aer_disable_rootport - disable Root Port's पूर्णांकerrupts when receiving messages
 * @rpc: poपूर्णांकer to a Root Port data काष्ठाure
 *
 * Invoked when PCIe bus unloads AER service driver.
 */
अटल व्योम aer_disable_rootport(काष्ठा aer_rpc *rpc)
अणु
	काष्ठा pci_dev *pdev = rpc->rpd;
	पूर्णांक aer = pdev->aer_cap;
	u32 reg32;

	/*
	 * Disable error reporting क्रम the root port device and करोwnstream port
	 * devices.
	 */
	set_करोwnstream_devices_error_reporting(pdev, false);

	/* Disable Root's पूर्णांकerrupt in response to error messages */
	pci_पढ़ो_config_dword(pdev, aer + PCI_ERR_ROOT_COMMAND, &reg32);
	reg32 &= ~ROOT_PORT_INTR_ON_MESG_MASK;
	pci_ग_लिखो_config_dword(pdev, aer + PCI_ERR_ROOT_COMMAND, reg32);

	/* Clear Root's error status reg */
	pci_पढ़ो_config_dword(pdev, aer + PCI_ERR_ROOT_STATUS, &reg32);
	pci_ग_लिखो_config_dword(pdev, aer + PCI_ERR_ROOT_STATUS, reg32);
पूर्ण

/**
 * aer_हटाओ - clean up resources
 * @dev: poपूर्णांकer to the pcie_dev data काष्ठाure
 *
 * Invoked when PCI Express bus unloads or AER probe fails.
 */
अटल व्योम aer_हटाओ(काष्ठा pcie_device *dev)
अणु
	काष्ठा aer_rpc *rpc = get_service_data(dev);

	aer_disable_rootport(rpc);
पूर्ण

/**
 * aer_probe - initialize resources
 * @dev: poपूर्णांकer to the pcie_dev data काष्ठाure
 *
 * Invoked when PCI Express bus loads AER service driver.
 */
अटल पूर्णांक aer_probe(काष्ठा pcie_device *dev)
अणु
	पूर्णांक status;
	काष्ठा aer_rpc *rpc;
	काष्ठा device *device = &dev->device;
	काष्ठा pci_dev *port = dev->port;

	/* Limit to Root Ports or Root Complex Event Collectors */
	अगर ((pci_pcie_type(port) != PCI_EXP_TYPE_RC_EC) &&
	    (pci_pcie_type(port) != PCI_EXP_TYPE_ROOT_PORT))
		वापस -ENODEV;

	rpc = devm_kzalloc(device, माप(काष्ठा aer_rpc), GFP_KERNEL);
	अगर (!rpc)
		वापस -ENOMEM;

	rpc->rpd = port;
	INIT_KFIFO(rpc->aer_fअगरo);
	set_service_data(dev, rpc);

	status = devm_request_thपढ़ोed_irq(device, dev->irq, aer_irq, aer_isr,
					   IRQF_SHARED, "aerdrv", dev);
	अगर (status) अणु
		pci_err(port, "request AER IRQ %d failed\n", dev->irq);
		वापस status;
	पूर्ण

	aer_enable_rootport(rpc);
	pci_info(port, "enabled with IRQ %d\n", dev->irq);
	वापस 0;
पूर्ण

/**
 * aer_root_reset - reset Root Port hierarchy, RCEC, or RCiEP
 * @dev: poपूर्णांकer to Root Port, RCEC, or RCiEP
 *
 * Invoked by Port Bus driver when perक्रमming reset.
 */
अटल pci_ers_result_t aer_root_reset(काष्ठा pci_dev *dev)
अणु
	पूर्णांक type = pci_pcie_type(dev);
	काष्ठा pci_dev *root;
	पूर्णांक aer;
	काष्ठा pci_host_bridge *host = pci_find_host_bridge(dev->bus);
	u32 reg32;
	पूर्णांक rc;

	/*
	 * Only Root Ports and RCECs have AER Root Command and Root Status
	 * रेजिस्टरs.  If "dev" is an RCiEP, the relevant रेजिस्टरs are in
	 * the RCEC.
	 */
	अगर (type == PCI_EXP_TYPE_RC_END)
		root = dev->rcec;
	अन्यथा
		root = pcie_find_root_port(dev);

	/*
	 * If the platक्रमm retained control of AER, an RCiEP may not have
	 * an RCEC visible to us, so dev->rcec ("root") may be शून्य.  In
	 * that हाल, firmware is responsible क्रम these रेजिस्टरs.
	 */
	aer = root ? root->aer_cap : 0;

	अगर ((host->native_aer || pcie_ports_native) && aer) अणु
		/* Disable Root's पूर्णांकerrupt in response to error messages */
		pci_पढ़ो_config_dword(root, aer + PCI_ERR_ROOT_COMMAND, &reg32);
		reg32 &= ~ROOT_PORT_INTR_ON_MESG_MASK;
		pci_ग_लिखो_config_dword(root, aer + PCI_ERR_ROOT_COMMAND, reg32);
	पूर्ण

	अगर (type == PCI_EXP_TYPE_RC_EC || type == PCI_EXP_TYPE_RC_END) अणु
		अगर (pcie_has_flr(dev)) अणु
			rc = pcie_flr(dev);
			pci_info(dev, "has been reset (%d)\n", rc);
		पूर्ण अन्यथा अणु
			pci_info(dev, "not reset (no FLR support)\n");
			rc = -ENOTTY;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = pci_bus_error_reset(dev);
		pci_info(dev, "%s Port link has been reset (%d)\n",
			pci_is_root_bus(dev->bus) ? "Root" : "Downstream", rc);
	पूर्ण

	अगर ((host->native_aer || pcie_ports_native) && aer) अणु
		/* Clear Root Error Status */
		pci_पढ़ो_config_dword(root, aer + PCI_ERR_ROOT_STATUS, &reg32);
		pci_ग_लिखो_config_dword(root, aer + PCI_ERR_ROOT_STATUS, reg32);

		/* Enable Root Port's पूर्णांकerrupt in response to error messages */
		pci_पढ़ो_config_dword(root, aer + PCI_ERR_ROOT_COMMAND, &reg32);
		reg32 |= ROOT_PORT_INTR_ON_MESG_MASK;
		pci_ग_लिखो_config_dword(root, aer + PCI_ERR_ROOT_COMMAND, reg32);
	पूर्ण

	वापस rc ? PCI_ERS_RESULT_DISCONNECT : PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल काष्ठा pcie_port_service_driver aerdriver = अणु
	.name		= "aer",
	.port_type	= PCIE_ANY_PORT,
	.service	= PCIE_PORT_SERVICE_AER,

	.probe		= aer_probe,
	.हटाओ		= aer_हटाओ,
पूर्ण;

/**
 * pcie_aer_init - रेजिस्टर AER root service driver
 *
 * Invoked when AER root service driver is loaded.
 */
पूर्णांक __init pcie_aer_init(व्योम)
अणु
	अगर (!pci_aer_available())
		वापस -ENXIO;
	वापस pcie_port_service_रेजिस्टर(&aerdriver);
पूर्ण
