<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AHCI SATA platक्रमm driver
 *
 * Copyright 2004-2005  Red Hat, Inc.
 *   Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2010  MontaVista Software, LLC.
 *   Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#अगर_अघोषित _AHCI_PLATFORM_H
#घोषणा _AHCI_PLATFORM_H

#समावेश <linux/compiler.h>

काष्ठा device;
काष्ठा ata_port_info;
काष्ठा ahci_host_priv;
काष्ठा platक्रमm_device;
काष्ठा scsi_host_ढाँचा;

पूर्णांक ahci_platक्रमm_enable_phys(काष्ठा ahci_host_priv *hpriv);
व्योम ahci_platक्रमm_disable_phys(काष्ठा ahci_host_priv *hpriv);
पूर्णांक ahci_platक्रमm_enable_clks(काष्ठा ahci_host_priv *hpriv);
व्योम ahci_platक्रमm_disable_clks(काष्ठा ahci_host_priv *hpriv);
पूर्णांक ahci_platक्रमm_enable_regulators(काष्ठा ahci_host_priv *hpriv);
व्योम ahci_platक्रमm_disable_regulators(काष्ठा ahci_host_priv *hpriv);
पूर्णांक ahci_platक्रमm_enable_resources(काष्ठा ahci_host_priv *hpriv);
व्योम ahci_platक्रमm_disable_resources(काष्ठा ahci_host_priv *hpriv);
काष्ठा ahci_host_priv *ahci_platक्रमm_get_resources(
	काष्ठा platक्रमm_device *pdev, अचिन्हित पूर्णांक flags);
पूर्णांक ahci_platक्रमm_init_host(काष्ठा platक्रमm_device *pdev,
			    काष्ठा ahci_host_priv *hpriv,
			    स्थिर काष्ठा ata_port_info *pi_ढाँचा,
			    काष्ठा scsi_host_ढाँचा *sht);

व्योम ahci_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *pdev);

पूर्णांक ahci_platक्रमm_suspend_host(काष्ठा device *dev);
पूर्णांक ahci_platक्रमm_resume_host(काष्ठा device *dev);
पूर्णांक ahci_platक्रमm_suspend(काष्ठा device *dev);
पूर्णांक ahci_platक्रमm_resume(काष्ठा device *dev);

#घोषणा AHCI_PLATFORM_GET_RESETS	0x01

#पूर्ण_अगर /* _AHCI_PLATFORM_H */
