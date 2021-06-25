<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm ICE (Inline Crypto Engine) support.
 *
 * Copyright (c) 2014-2019, The Linux Foundation. All rights reserved.
 * Copyright 2019 Google LLC
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/qcom_scm.h>

#समावेश "ufshcd-crypto.h"
#समावेश "ufs-qcom.h"

#घोषणा AES_256_XTS_KEY_SIZE			64

/* QCOM ICE रेजिस्टरs */

#घोषणा QCOM_ICE_REG_CONTROL			0x0000
#घोषणा QCOM_ICE_REG_RESET			0x0004
#घोषणा QCOM_ICE_REG_VERSION			0x0008
#घोषणा QCOM_ICE_REG_FUSE_SETTING		0x0010
#घोषणा QCOM_ICE_REG_PARAMETERS_1		0x0014
#घोषणा QCOM_ICE_REG_PARAMETERS_2		0x0018
#घोषणा QCOM_ICE_REG_PARAMETERS_3		0x001C
#घोषणा QCOM_ICE_REG_PARAMETERS_4		0x0020
#घोषणा QCOM_ICE_REG_PARAMETERS_5		0x0024

/* QCOM ICE v3.X only */
#घोषणा QCOM_ICE_GENERAL_ERR_STTS		0x0040
#घोषणा QCOM_ICE_INVALID_CCFG_ERR_STTS		0x0030
#घोषणा QCOM_ICE_GENERAL_ERR_MASK		0x0044

/* QCOM ICE v2.X only */
#घोषणा QCOM_ICE_REG_NON_SEC_IRQ_STTS		0x0040
#घोषणा QCOM_ICE_REG_NON_SEC_IRQ_MASK		0x0044

#घोषणा QCOM_ICE_REG_NON_SEC_IRQ_CLR		0x0048
#घोषणा QCOM_ICE_REG_STREAM1_ERROR_SYNDROME1	0x0050
#घोषणा QCOM_ICE_REG_STREAM1_ERROR_SYNDROME2	0x0054
#घोषणा QCOM_ICE_REG_STREAM2_ERROR_SYNDROME1	0x0058
#घोषणा QCOM_ICE_REG_STREAM2_ERROR_SYNDROME2	0x005C
#घोषणा QCOM_ICE_REG_STREAM1_BIST_ERROR_VEC	0x0060
#घोषणा QCOM_ICE_REG_STREAM2_BIST_ERROR_VEC	0x0064
#घोषणा QCOM_ICE_REG_STREAM1_BIST_FINISH_VEC	0x0068
#घोषणा QCOM_ICE_REG_STREAM2_BIST_FINISH_VEC	0x006C
#घोषणा QCOM_ICE_REG_BIST_STATUS		0x0070
#घोषणा QCOM_ICE_REG_BYPASS_STATUS		0x0074
#घोषणा QCOM_ICE_REG_ADVANCED_CONTROL		0x1000
#घोषणा QCOM_ICE_REG_ENDIAN_SWAP		0x1004
#घोषणा QCOM_ICE_REG_TEST_BUS_CONTROL		0x1010
#घोषणा QCOM_ICE_REG_TEST_BUS_REG		0x1014

/* BIST ("built-in self-test"?) status flags */
#घोषणा QCOM_ICE_BIST_STATUS_MASK		0xF0000000

#घोषणा QCOM_ICE_FUSE_SETTING_MASK		0x1
#घोषणा QCOM_ICE_FORCE_HW_KEY0_SETTING_MASK	0x2
#घोषणा QCOM_ICE_FORCE_HW_KEY1_SETTING_MASK	0x4

#घोषणा qcom_ice_ग_लिखोl(host, val, reg)	\
	ग_लिखोl((val), (host)->ice_mmio + (reg))
#घोषणा qcom_ice_पढ़ोl(host, reg)	\
	पढ़ोl((host)->ice_mmio + (reg))

अटल bool qcom_ice_supported(काष्ठा ufs_qcom_host *host)
अणु
	काष्ठा device *dev = host->hba->dev;
	u32 regval = qcom_ice_पढ़ोl(host, QCOM_ICE_REG_VERSION);
	पूर्णांक major = regval >> 24;
	पूर्णांक minor = (regval >> 16) & 0xFF;
	पूर्णांक step = regval & 0xFFFF;

	/* For now this driver only supports ICE version 3. */
	अगर (major != 3) अणु
		dev_warn(dev, "Unsupported ICE version: v%d.%d.%d\n",
			 major, minor, step);
		वापस false;
	पूर्ण

	dev_info(dev, "Found QC Inline Crypto Engine (ICE) v%d.%d.%d\n",
		 major, minor, step);

	/* If fuses are blown, ICE might not work in the standard way. */
	regval = qcom_ice_पढ़ोl(host, QCOM_ICE_REG_FUSE_SETTING);
	अगर (regval & (QCOM_ICE_FUSE_SETTING_MASK |
		      QCOM_ICE_FORCE_HW_KEY0_SETTING_MASK |
		      QCOM_ICE_FORCE_HW_KEY1_SETTING_MASK)) अणु
		dev_warn(dev, "Fuses are blown; ICE is unusable!\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक ufs_qcom_ice_init(काष्ठा ufs_qcom_host *host)
अणु
	काष्ठा ufs_hba *hba = host->hba;
	काष्ठा device *dev = hba->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res;
	पूर्णांक err;

	अगर (!(ufshcd_पढ़ोl(hba, REG_CONTROLLER_CAPABILITIES) &
	      MASK_CRYPTO_SUPPORT))
		वापस 0;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ice");
	अगर (!res) अणु
		dev_warn(dev, "ICE registers not found\n");
		जाओ disable;
	पूर्ण

	अगर (!qcom_scm_ice_available()) अणु
		dev_warn(dev, "ICE SCM interface not found\n");
		जाओ disable;
	पूर्ण

	host->ice_mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(host->ice_mmio)) अणु
		err = PTR_ERR(host->ice_mmio);
		dev_err(dev, "Failed to map ICE registers; err=%d\n", err);
		वापस err;
	पूर्ण

	अगर (!qcom_ice_supported(host))
		जाओ disable;

	वापस 0;

disable:
	dev_warn(dev, "Disabling inline encryption support\n");
	hba->caps &= ~UFSHCD_CAP_CRYPTO;
	वापस 0;
पूर्ण

अटल व्योम qcom_ice_low_घातer_mode_enable(काष्ठा ufs_qcom_host *host)
अणु
	u32 regval;

	regval = qcom_ice_पढ़ोl(host, QCOM_ICE_REG_ADVANCED_CONTROL);
	/*
	 * Enable low घातer mode sequence
	 * [0]-0, [1]-0, [2]-0, [3]-E, [4]-0, [5]-0, [6]-0, [7]-0
	 */
	regval |= 0x7000;
	qcom_ice_ग_लिखोl(host, regval, QCOM_ICE_REG_ADVANCED_CONTROL);
पूर्ण

अटल व्योम qcom_ice_optimization_enable(काष्ठा ufs_qcom_host *host)
अणु
	u32 regval;

	/* ICE Optimizations Enable Sequence */
	regval = qcom_ice_पढ़ोl(host, QCOM_ICE_REG_ADVANCED_CONTROL);
	regval |= 0xD807100;
	/* ICE HPG requires delay beक्रमe writing */
	udelay(5);
	qcom_ice_ग_लिखोl(host, regval, QCOM_ICE_REG_ADVANCED_CONTROL);
	udelay(5);
पूर्ण

पूर्णांक ufs_qcom_ice_enable(काष्ठा ufs_qcom_host *host)
अणु
	अगर (!(host->hba->caps & UFSHCD_CAP_CRYPTO))
		वापस 0;
	qcom_ice_low_घातer_mode_enable(host);
	qcom_ice_optimization_enable(host);
	वापस ufs_qcom_ice_resume(host);
पूर्ण

/* Poll until all BIST bits are reset */
अटल पूर्णांक qcom_ice_रुको_bist_status(काष्ठा ufs_qcom_host *host)
अणु
	पूर्णांक count;
	u32 reg;

	क्रम (count = 0; count < 100; count++) अणु
		reg = qcom_ice_पढ़ोl(host, QCOM_ICE_REG_BIST_STATUS);
		अगर (!(reg & QCOM_ICE_BIST_STATUS_MASK))
			अवरोध;
		udelay(50);
	पूर्ण
	अगर (reg)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

पूर्णांक ufs_qcom_ice_resume(काष्ठा ufs_qcom_host *host)
अणु
	पूर्णांक err;

	अगर (!(host->hba->caps & UFSHCD_CAP_CRYPTO))
		वापस 0;

	err = qcom_ice_रुको_bist_status(host);
	अगर (err) अणु
		dev_err(host->hba->dev, "BIST status error (%d)\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Program a key पूर्णांकo a QC ICE keyslot, or evict a keyslot.  QC ICE requires
 * venकरोr-specअगरic SCM calls क्रम this; it करोesn't support the standard way.
 */
पूर्णांक ufs_qcom_ice_program_key(काष्ठा ufs_hba *hba,
			     स्थिर जोड़ ufs_crypto_cfg_entry *cfg, पूर्णांक slot)
अणु
	जोड़ ufs_crypto_cap_entry cap;
	जोड़ अणु
		u8 bytes[AES_256_XTS_KEY_SIZE];
		u32 words[AES_256_XTS_KEY_SIZE / माप(u32)];
	पूर्ण key;
	पूर्णांक i;
	पूर्णांक err;

	अगर (!(cfg->config_enable & UFS_CRYPTO_CONFIGURATION_ENABLE))
		वापस qcom_scm_ice_invalidate_key(slot);

	/* Only AES-256-XTS has been tested so far. */
	cap = hba->crypto_cap_array[cfg->crypto_cap_idx];
	अगर (cap.algorithm_id != UFS_CRYPTO_ALG_AES_XTS ||
	    cap.key_size != UFS_CRYPTO_KEY_SIZE_256) अणु
		dev_err_ratelimited(hba->dev,
				    "Unhandled crypto capability; algorithm_id=%d, key_size=%d\n",
				    cap.algorithm_id, cap.key_size);
		वापस -EINVAL;
	पूर्ण

	स_नकल(key.bytes, cfg->crypto_key, AES_256_XTS_KEY_SIZE);

	/*
	 * The SCM call byte-swaps the 32-bit words of the key.  So we have to
	 * करो the same, in order क्रम the final key be correct.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(key.words); i++)
		__cpu_to_be32s(&key.words[i]);

	err = qcom_scm_ice_set_key(slot, key.bytes, AES_256_XTS_KEY_SIZE,
				   QCOM_SCM_ICE_CIPHER_AES_256_XTS,
				   cfg->data_unit_size);
	memzero_explicit(&key, माप(key));
	वापस err;
पूर्ण
