<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005, 2006 IBM Corporation
 * Copyright (C) 2014, 2015 Intel Corporation
 *
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 *
 * This device driver implements the TPM पूर्णांकerface as defined in
 * the TCG TPM Interface Spec version 1.2, revision 1.0.
 */

#अगर_अघोषित __TPM_TIS_CORE_H__
#घोषणा __TPM_TIS_CORE_H__

#समावेश "tpm.h"

क्रमागत tis_access अणु
	TPM_ACCESS_VALID = 0x80,
	TPM_ACCESS_ACTIVE_LOCALITY = 0x20,
	TPM_ACCESS_REQUEST_PENDING = 0x04,
	TPM_ACCESS_REQUEST_USE = 0x02,
पूर्ण;

क्रमागत tis_status अणु
	TPM_STS_VALID = 0x80,
	TPM_STS_COMMAND_READY = 0x40,
	TPM_STS_GO = 0x20,
	TPM_STS_DATA_AVAIL = 0x10,
	TPM_STS_DATA_EXPECT = 0x08,
	TPM_STS_READ_ZERO = 0x23, /* bits that must be zero on पढ़ो */
पूर्ण;

क्रमागत tis_पूर्णांक_flags अणु
	TPM_GLOBAL_INT_ENABLE = 0x80000000,
	TPM_INTF_BURST_COUNT_STATIC = 0x100,
	TPM_INTF_CMD_READY_INT = 0x080,
	TPM_INTF_INT_EDGE_FALLING = 0x040,
	TPM_INTF_INT_EDGE_RISING = 0x020,
	TPM_INTF_INT_LEVEL_LOW = 0x010,
	TPM_INTF_INT_LEVEL_HIGH = 0x008,
	TPM_INTF_LOCALITY_CHANGE_INT = 0x004,
	TPM_INTF_STS_VALID_INT = 0x002,
	TPM_INTF_DATA_AVAIL_INT = 0x001,
पूर्ण;

क्रमागत tis_शेषs अणु
	TIS_MEM_LEN = 0x5000,
	TIS_SHORT_TIMEOUT = 750,	/* ms */
	TIS_LONG_TIMEOUT = 2000,	/* 2 sec */
पूर्ण;

/* Some समयout values are needed beक्रमe it is known whether the chip is
 * TPM 1.0 or TPM 2.0.
 */
#घोषणा TIS_TIMEOUT_A_MAX	max_t(पूर्णांक, TIS_SHORT_TIMEOUT, TPM2_TIMEOUT_A)
#घोषणा TIS_TIMEOUT_B_MAX	max_t(पूर्णांक, TIS_LONG_TIMEOUT, TPM2_TIMEOUT_B)
#घोषणा TIS_TIMEOUT_C_MAX	max_t(पूर्णांक, TIS_SHORT_TIMEOUT, TPM2_TIMEOUT_C)
#घोषणा TIS_TIMEOUT_D_MAX	max_t(पूर्णांक, TIS_SHORT_TIMEOUT, TPM2_TIMEOUT_D)

#घोषणा	TPM_ACCESS(l)			(0x0000 | ((l) << 12))
#घोषणा	TPM_INT_ENABLE(l)		(0x0008 | ((l) << 12))
#घोषणा	TPM_INT_VECTOR(l)		(0x000C | ((l) << 12))
#घोषणा	TPM_INT_STATUS(l)		(0x0010 | ((l) << 12))
#घोषणा	TPM_INTF_CAPS(l)		(0x0014 | ((l) << 12))
#घोषणा	TPM_STS(l)			(0x0018 | ((l) << 12))
#घोषणा	TPM_STS3(l)			(0x001b | ((l) << 12))
#घोषणा	TPM_DATA_FIFO(l)		(0x0024 | ((l) << 12))

#घोषणा	TPM_DID_VID(l)			(0x0F00 | ((l) << 12))
#घोषणा	TPM_RID(l)			(0x0F04 | ((l) << 12))

#घोषणा LPC_CNTRL_OFFSET		0x84
#घोषणा LPC_CLKRUN_EN			(1 << 2)
#घोषणा INTEL_LEGACY_BLK_BASE_ADDR	0xFED08000
#घोषणा ILB_REMAP_SIZE			0x100

क्रमागत tpm_tis_flags अणु
	TPM_TIS_ITPM_WORKAROUND		= BIT(0),
पूर्ण;

काष्ठा tpm_tis_data अणु
	u16 manufacturer_id;
	पूर्णांक locality;
	पूर्णांक irq;
	bool irq_tested;
	अचिन्हित पूर्णांक flags;
	व्योम __iomem *ilb_base_addr;
	u16 clkrun_enabled;
	रुको_queue_head_t पूर्णांक_queue;
	रुको_queue_head_t पढ़ो_queue;
	स्थिर काष्ठा tpm_tis_phy_ops *phy_ops;
	अचिन्हित लघु rng_quality;
पूर्ण;

काष्ठा tpm_tis_phy_ops अणु
	पूर्णांक (*पढ़ो_bytes)(काष्ठा tpm_tis_data *data, u32 addr, u16 len,
			  u8 *result);
	पूर्णांक (*ग_लिखो_bytes)(काष्ठा tpm_tis_data *data, u32 addr, u16 len,
			   स्थिर u8 *value);
	पूर्णांक (*पढ़ो16)(काष्ठा tpm_tis_data *data, u32 addr, u16 *result);
	पूर्णांक (*पढ़ो32)(काष्ठा tpm_tis_data *data, u32 addr, u32 *result);
	पूर्णांक (*ग_लिखो32)(काष्ठा tpm_tis_data *data, u32 addr, u32 src);
पूर्ण;

अटल अंतरभूत पूर्णांक tpm_tis_पढ़ो_bytes(काष्ठा tpm_tis_data *data, u32 addr,
				     u16 len, u8 *result)
अणु
	वापस data->phy_ops->पढ़ो_bytes(data, addr, len, result);
पूर्ण

अटल अंतरभूत पूर्णांक tpm_tis_पढ़ो8(काष्ठा tpm_tis_data *data, u32 addr, u8 *result)
अणु
	वापस data->phy_ops->पढ़ो_bytes(data, addr, 1, result);
पूर्ण

अटल अंतरभूत पूर्णांक tpm_tis_पढ़ो16(काष्ठा tpm_tis_data *data, u32 addr,
				 u16 *result)
अणु
	वापस data->phy_ops->पढ़ो16(data, addr, result);
पूर्ण

अटल अंतरभूत पूर्णांक tpm_tis_पढ़ो32(काष्ठा tpm_tis_data *data, u32 addr,
				 u32 *result)
अणु
	वापस data->phy_ops->पढ़ो32(data, addr, result);
पूर्ण

अटल अंतरभूत पूर्णांक tpm_tis_ग_लिखो_bytes(काष्ठा tpm_tis_data *data, u32 addr,
				      u16 len, स्थिर u8 *value)
अणु
	वापस data->phy_ops->ग_लिखो_bytes(data, addr, len, value);
पूर्ण

अटल अंतरभूत पूर्णांक tpm_tis_ग_लिखो8(काष्ठा tpm_tis_data *data, u32 addr, u8 value)
अणु
	वापस data->phy_ops->ग_लिखो_bytes(data, addr, 1, &value);
पूर्ण

अटल अंतरभूत पूर्णांक tpm_tis_ग_लिखो32(काष्ठा tpm_tis_data *data, u32 addr,
				  u32 value)
अणु
	वापस data->phy_ops->ग_लिखो32(data, addr, value);
पूर्ण

अटल अंतरभूत bool is_bsw(व्योम)
अणु
#अगर_घोषित CONFIG_X86
	वापस ((boot_cpu_data.x86_model == INTEL_FAM6_ATOM_AIRMONT) ? 1 : 0);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

व्योम tpm_tis_हटाओ(काष्ठा tpm_chip *chip);
पूर्णांक tpm_tis_core_init(काष्ठा device *dev, काष्ठा tpm_tis_data *priv, पूर्णांक irq,
		      स्थिर काष्ठा tpm_tis_phy_ops *phy_ops,
		      acpi_handle acpi_dev_handle);

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक tpm_tis_resume(काष्ठा device *dev);
#पूर्ण_अगर

#पूर्ण_अगर
