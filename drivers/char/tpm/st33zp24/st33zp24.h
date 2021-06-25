<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STMicroelectronics TPM Linux driver क्रम TPM ST33ZP24
 * Copyright (C) 2009 - 2016  STMicroelectronics
 */

#अगर_अघोषित __LOCAL_ST33ZP24_H__
#घोषणा __LOCAL_ST33ZP24_H__

#घोषणा TPM_WRITE_सूचीECTION	0x80
#घोषणा ST33ZP24_बफ_मानE	2048

काष्ठा st33zp24_dev अणु
	काष्ठा tpm_chip *chip;
	व्योम *phy_id;
	स्थिर काष्ठा st33zp24_phy_ops *ops;
	पूर्णांक locality;
	पूर्णांक irq;
	u32 पूर्णांकrs;
	पूर्णांक io_lpcpd;
	रुको_queue_head_t पढ़ो_queue;
पूर्ण;


काष्ठा st33zp24_phy_ops अणु
	पूर्णांक (*send)(व्योम *phy_id, u8 tpm_रेजिस्टर, u8 *tpm_data, पूर्णांक tpm_size);
	पूर्णांक (*recv)(व्योम *phy_id, u8 tpm_रेजिस्टर, u8 *tpm_data, पूर्णांक tpm_size);
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक st33zp24_pm_suspend(काष्ठा device *dev);
पूर्णांक st33zp24_pm_resume(काष्ठा device *dev);
#पूर्ण_अगर

पूर्णांक st33zp24_probe(व्योम *phy_id, स्थिर काष्ठा st33zp24_phy_ops *ops,
		   काष्ठा device *dev, पूर्णांक irq, पूर्णांक io_lpcpd);
पूर्णांक st33zp24_हटाओ(काष्ठा tpm_chip *chip);
#पूर्ण_अगर /* __LOCAL_ST33ZP24_H__ */
