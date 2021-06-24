<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित MFD_INTEL_PMC_BXT_H
#घोषणा MFD_INTEL_PMC_BXT_H

/* GCR reg offsets from GCR base */
#घोषणा PMC_GCR_PMC_CFG_REG		0x08
#घोषणा PMC_GCR_TELEM_DEEP_S0IX_REG	0x78
#घोषणा PMC_GCR_TELEM_SHLW_S0IX_REG	0x80

/* PMC_CFG_REG bit masks */
#घोषणा PMC_CFG_NO_REBOOT_EN		BIT(4)

/**
 * काष्ठा पूर्णांकel_pmc_dev - Intel PMC device काष्ठाure
 * @dev: Poपूर्णांकer to the parent PMC device
 * @scu: Poपूर्णांकer to the SCU IPC device data काष्ठाure
 * @gcr_mem_base: Virtual base address of GCR (Global Configuration Registers)
 * @gcr_lock: Lock used to serialize access to GCR रेजिस्टरs
 * @telem_base: Poपूर्णांकer to telemetry SSRAM base resource or %शून्य अगर not
 *		available
 */
काष्ठा पूर्णांकel_pmc_dev अणु
	काष्ठा device *dev;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;
	व्योम __iomem *gcr_mem_base;
	spinlock_t gcr_lock;
	काष्ठा resource *telem_base;
पूर्ण;

#अगर IS_ENABLED(CONFIG_MFD_INTEL_PMC_BXT)
पूर्णांक पूर्णांकel_pmc_gcr_पढ़ो64(काष्ठा पूर्णांकel_pmc_dev *pmc, u32 offset, u64 *data);
पूर्णांक पूर्णांकel_pmc_gcr_update(काष्ठा पूर्णांकel_pmc_dev *pmc, u32 offset, u32 mask, u32 val);
पूर्णांक पूर्णांकel_pmc_s0ix_counter_पढ़ो(काष्ठा पूर्णांकel_pmc_dev *pmc, u64 *data);
#अन्यथा
अटल अंतरभूत पूर्णांक पूर्णांकel_pmc_gcr_पढ़ो64(काष्ठा पूर्णांकel_pmc_dev *pmc, u32 offset,
				       u64 *data)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_pmc_gcr_update(काष्ठा पूर्णांकel_pmc_dev *pmc, u32 offset,
				       u32 mask, u32 val)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_pmc_s0ix_counter_पढ़ो(काष्ठा पूर्णांकel_pmc_dev *pmc, u64 *data)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* MFD_INTEL_PMC_BXT_H */
