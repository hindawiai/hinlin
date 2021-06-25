<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * processor_thermal_device.h
 * Copyright (c) 2020, Intel Corporation.
 */

#अगर_अघोषित __PROCESSOR_THERMAL_DEVICE_H__
#घोषणा __PROCESSOR_THERMAL_DEVICE_H__

#समावेश <linux/पूर्णांकel_rapl.h>

#घोषणा PCI_DEVICE_ID_INTEL_ADL_THERMAL	0x461d
#घोषणा PCI_DEVICE_ID_INTEL_BDW_THERMAL	0x1603
#घोषणा PCI_DEVICE_ID_INTEL_BSW_THERMAL	0x22DC

#घोषणा PCI_DEVICE_ID_INTEL_BXT0_THERMAL	0x0A8C
#घोषणा PCI_DEVICE_ID_INTEL_BXT1_THERMAL	0x1A8C
#घोषणा PCI_DEVICE_ID_INTEL_BXTX_THERMAL	0x4A8C
#घोषणा PCI_DEVICE_ID_INTEL_BXTP_THERMAL	0x5A8C

#घोषणा PCI_DEVICE_ID_INTEL_CNL_THERMAL	0x5a03
#घोषणा PCI_DEVICE_ID_INTEL_CFL_THERMAL	0x3E83
#घोषणा PCI_DEVICE_ID_INTEL_GLK_THERMAL	0x318C
#घोषणा PCI_DEVICE_ID_INTEL_HSB_THERMAL	0x0A03
#घोषणा PCI_DEVICE_ID_INTEL_ICL_THERMAL	0x8a03
#घोषणा PCI_DEVICE_ID_INTEL_JSL_THERMAL	0x4E03
#घोषणा PCI_DEVICE_ID_INTEL_SKL_THERMAL	0x1903
#घोषणा PCI_DEVICE_ID_INTEL_TGL_THERMAL	0x9A03

काष्ठा घातer_config अणु
	u32	index;
	u32	min_uw;
	u32	max_uw;
	u32	पंचांगin_us;
	u32	पंचांगax_us;
	u32	step_uw;
पूर्ण;

काष्ठा proc_thermal_device अणु
	काष्ठा device *dev;
	काष्ठा acpi_device *adev;
	काष्ठा घातer_config घातer_limits[2];
	काष्ठा पूर्णांक34x_thermal_zone *पूर्णांक340x_zone;
	काष्ठा पूर्णांकel_soc_dts_sensors *soc_dts;
	u32 mmio_feature_mask;
	व्योम __iomem *mmio_base;
पूर्ण;

काष्ठा rapl_mmio_regs अणु
	u64 reg_unit;
	u64 regs[RAPL_DOMAIN_MAX][RAPL_DOMAIN_REG_MAX];
	पूर्णांक limits[RAPL_DOMAIN_MAX];
पूर्ण;

#घोषणा PROC_THERMAL_FEATURE_NONE	0x00
#घोषणा PROC_THERMAL_FEATURE_RAPL	0x01
#घोषणा PROC_THERMAL_FEATURE_FIVR	0x02
#घोषणा PROC_THERMAL_FEATURE_DVFS	0x04
#घोषणा PROC_THERMAL_FEATURE_MBOX	0x08

#अगर IS_ENABLED(CONFIG_PROC_THERMAL_MMIO_RAPL)
पूर्णांक proc_thermal_rapl_add(काष्ठा pci_dev *pdev, काष्ठा proc_thermal_device *proc_priv);
व्योम proc_thermal_rapl_हटाओ(व्योम);
#अन्यथा
अटल पूर्णांक __maybe_unused proc_thermal_rapl_add(काष्ठा pci_dev *pdev,
						काष्ठा proc_thermal_device *proc_priv)
अणु
	वापस 0;
पूर्ण

अटल व्योम __maybe_unused proc_thermal_rapl_हटाओ(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक proc_thermal_rfim_add(काष्ठा pci_dev *pdev, काष्ठा proc_thermal_device *proc_priv);
व्योम proc_thermal_rfim_हटाओ(काष्ठा pci_dev *pdev);

पूर्णांक proc_thermal_mbox_add(काष्ठा pci_dev *pdev, काष्ठा proc_thermal_device *proc_priv);
व्योम proc_thermal_mbox_हटाओ(काष्ठा pci_dev *pdev);

#पूर्ण_अगर
