<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2006 Intel Corp.
 *     Tom Long Nguyen (tom.l.nguyen@पूर्णांकel.com)
 *     Zhang Yanmin (yanmin.zhang@पूर्णांकel.com)
 */

#अगर_अघोषित _AER_H_
#घोषणा _AER_H_

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

#घोषणा AER_NONFATAL			0
#घोषणा AER_FATAL			1
#घोषणा AER_CORRECTABLE			2
#घोषणा DPC_FATAL			3

काष्ठा pci_dev;

काष्ठा aer_header_log_regs अणु
	अचिन्हित पूर्णांक dw0;
	अचिन्हित पूर्णांक dw1;
	अचिन्हित पूर्णांक dw2;
	अचिन्हित पूर्णांक dw3;
पूर्ण;

काष्ठा aer_capability_regs अणु
	u32 header;
	u32 uncor_status;
	u32 uncor_mask;
	u32 uncor_severity;
	u32 cor_status;
	u32 cor_mask;
	u32 cap_control;
	काष्ठा aer_header_log_regs header_log;
	u32 root_command;
	u32 root_status;
	u16 cor_err_source;
	u16 uncor_err_source;
पूर्ण;

#अगर defined(CONFIG_PCIEAER)
/* PCIe port driver needs this function to enable AER */
पूर्णांक pci_enable_pcie_error_reporting(काष्ठा pci_dev *dev);
पूर्णांक pci_disable_pcie_error_reporting(काष्ठा pci_dev *dev);
पूर्णांक pci_aer_clear_nonfatal_status(काष्ठा pci_dev *dev);
व्योम pci_save_aer_state(काष्ठा pci_dev *dev);
व्योम pci_restore_aer_state(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक pci_enable_pcie_error_reporting(काष्ठा pci_dev *dev)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक pci_disable_pcie_error_reporting(काष्ठा pci_dev *dev)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक pci_aer_clear_nonfatal_status(काष्ठा pci_dev *dev)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम pci_save_aer_state(काष्ठा pci_dev *dev) अणुपूर्ण
अटल अंतरभूत व्योम pci_restore_aer_state(काष्ठा pci_dev *dev) अणुपूर्ण
#पूर्ण_अगर

व्योम cper_prपूर्णांक_aer(काष्ठा pci_dev *dev, पूर्णांक aer_severity,
		    काष्ठा aer_capability_regs *aer);
पूर्णांक cper_severity_to_aer(पूर्णांक cper_severity);
व्योम aer_recover_queue(पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
		       पूर्णांक severity, काष्ठा aer_capability_regs *aer_regs);
#पूर्ण_अगर //_AER_H_

