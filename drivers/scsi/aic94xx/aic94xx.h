<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aic94xx SAS/SATA driver header file.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 *
 * $Id: //depot/aic94xx/aic94xx.h#31 $
 */

#अगर_अघोषित _AIC94XX_H_
#घोषणा _AIC94XX_H_

#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <scsi/libsas.h>

#घोषणा ASD_DRIVER_NAME		"aic94xx"
#घोषणा ASD_DRIVER_DESCRIPTION	"Adaptec aic94xx SAS/SATA driver"

#घोषणा asd_prपूर्णांकk(fmt, ...)	prपूर्णांकk(KERN_NOTICE ASD_DRIVER_NAME ": " fmt, ## __VA_ARGS__)

#अगर_घोषित ASD_ENTER_EXIT
#घोषणा ENTER  prपूर्णांकk(KERN_NOTICE "%s: ENTER %s\n", ASD_DRIVER_NAME, \
		__func__)
#घोषणा EXIT   prपूर्णांकk(KERN_NOTICE "%s: --EXIT %s\n", ASD_DRIVER_NAME, \
		__func__)
#अन्यथा
#घोषणा ENTER
#घोषणा EXIT
#पूर्ण_अगर

#अगर_घोषित ASD_DEBUG
#घोषणा ASD_DPRINTK asd_prपूर्णांकk
#अन्यथा
#घोषणा ASD_DPRINTK(fmt, ...) no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* 2*ITNL समयout + 1 second */
#घोषणा AIC94XX_SCB_TIMEOUT  (5*HZ)

बाह्य काष्ठा kmem_cache *asd_dma_token_cache;
बाह्य काष्ठा kmem_cache *asd_ascb_cache;

काष्ठा asd_ha_काष्ठा;
काष्ठा asd_ascb;

पूर्णांक  asd_पढ़ो_ocm(काष्ठा asd_ha_काष्ठा *asd_ha);
पूर्णांक  asd_पढ़ो_flash(काष्ठा asd_ha_काष्ठा *asd_ha);

पूर्णांक  asd_dev_found(काष्ठा करोमुख्य_device *dev);
व्योम asd_dev_gone(काष्ठा करोमुख्य_device *dev);

व्योम asd_invalidate_edb(काष्ठा asd_ascb *ascb, पूर्णांक edb_id);

पूर्णांक  asd_execute_task(काष्ठा sas_task *task, gfp_t gfp_flags);

व्योम asd_set_dmamode(काष्ठा करोमुख्य_device *dev);

/* ---------- TMFs ---------- */
पूर्णांक  asd_पात_task(काष्ठा sas_task *);
पूर्णांक  asd_पात_task_set(काष्ठा करोमुख्य_device *, u8 *lun);
पूर्णांक  asd_clear_aca(काष्ठा करोमुख्य_device *, u8 *lun);
पूर्णांक  asd_clear_task_set(काष्ठा करोमुख्य_device *, u8 *lun);
पूर्णांक  asd_lu_reset(काष्ठा करोमुख्य_device *, u8 *lun);
पूर्णांक  asd_I_T_nexus_reset(काष्ठा करोमुख्य_device *dev);
पूर्णांक  asd_query_task(काष्ठा sas_task *);

/* ---------- Adapter and Port management ---------- */
पूर्णांक  asd_clear_nexus_port(काष्ठा asd_sas_port *port);
पूर्णांक  asd_clear_nexus_ha(काष्ठा sas_ha_काष्ठा *sas_ha);

/* ---------- Phy Management ---------- */
पूर्णांक  asd_control_phy(काष्ठा asd_sas_phy *phy, क्रमागत phy_func func, व्योम *arg);

#पूर्ण_अगर
