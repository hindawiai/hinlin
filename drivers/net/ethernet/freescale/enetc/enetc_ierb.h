<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2021 NXP Semiconductors */

#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>

#अगर IS_ENABLED(CONFIG_FSL_ENETC_IERB)

पूर्णांक enetc_ierb_रेजिस्टर_pf(काष्ठा platक्रमm_device *pdev,
			   काष्ठा pci_dev *pf_pdev);

#अन्यथा

अटल अंतरभूत पूर्णांक enetc_ierb_रेजिस्टर_pf(काष्ठा platक्रमm_device *pdev,
					 काष्ठा pci_dev *pf_pdev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर
