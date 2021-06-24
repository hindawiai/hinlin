<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD Secure Processor driver
 *
 * Copyright (C) 2017-2019 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 * Author: Gary R Hook <gary.hook@amd.com>
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 */

#अगर_अघोषित __SP_DEV_H__
#घोषणा __SP_DEV_H__

#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>

#घोषणा SP_MAX_NAME_LEN		32

#घोषणा CACHE_NONE			0x00
#घोषणा CACHE_WB_NO_ALLOC		0xb7

/* Structure to hold CCP device data */
काष्ठा ccp_device;
काष्ठा ccp_vdata अणु
	स्थिर अचिन्हित पूर्णांक version;
	स्थिर अचिन्हित पूर्णांक dma_chan_attr;
	व्योम (*setup)(काष्ठा ccp_device *);
	स्थिर काष्ठा ccp_actions *perक्रमm;
	स्थिर अचिन्हित पूर्णांक offset;
	स्थिर अचिन्हित पूर्णांक rsamax;
पूर्ण;

काष्ठा sev_vdata अणु
	स्थिर अचिन्हित पूर्णांक cmdresp_reg;
	स्थिर अचिन्हित पूर्णांक cmdbuff_addr_lo_reg;
	स्थिर अचिन्हित पूर्णांक cmdbuff_addr_hi_reg;
पूर्ण;

काष्ठा tee_vdata अणु
	स्थिर अचिन्हित पूर्णांक cmdresp_reg;
	स्थिर अचिन्हित पूर्णांक cmdbuff_addr_lo_reg;
	स्थिर अचिन्हित पूर्णांक cmdbuff_addr_hi_reg;
	स्थिर अचिन्हित पूर्णांक ring_wptr_reg;
	स्थिर अचिन्हित पूर्णांक ring_rptr_reg;
पूर्ण;

काष्ठा psp_vdata अणु
	स्थिर काष्ठा sev_vdata *sev;
	स्थिर काष्ठा tee_vdata *tee;
	स्थिर अचिन्हित पूर्णांक feature_reg;
	स्थिर अचिन्हित पूर्णांक पूर्णांकen_reg;
	स्थिर अचिन्हित पूर्णांक पूर्णांकsts_reg;
पूर्ण;

/* Structure to hold SP device data */
काष्ठा sp_dev_vdata अणु
	स्थिर अचिन्हित पूर्णांक bar;

	स्थिर काष्ठा ccp_vdata *ccp_vdata;
	स्थिर काष्ठा psp_vdata *psp_vdata;
पूर्ण;

काष्ठा sp_device अणु
	काष्ठा list_head entry;

	काष्ठा device *dev;

	काष्ठा sp_dev_vdata *dev_vdata;
	अचिन्हित पूर्णांक ord;
	अक्षर name[SP_MAX_NAME_LEN];

	/* Bus specअगरic device inक्रमmation */
	व्योम *dev_specअगरic;

	/* I/O area used क्रम device communication. */
	व्योम __iomem *io_map;

	/* DMA caching attribute support */
	अचिन्हित पूर्णांक axcache;

	/* get and set master device */
	काष्ठा sp_device*(*get_psp_master_device)(व्योम);
	व्योम (*set_psp_master_device)(काष्ठा sp_device *);
	व्योम (*clear_psp_master_device)(काष्ठा sp_device *);

	bool irq_रेजिस्टरed;
	bool use_tasklet;

	अचिन्हित पूर्णांक ccp_irq;
	irq_handler_t ccp_irq_handler;
	व्योम *ccp_irq_data;

	अचिन्हित पूर्णांक psp_irq;
	irq_handler_t psp_irq_handler;
	व्योम *psp_irq_data;

	व्योम *ccp_data;
	व्योम *psp_data;
पूर्ण;

पूर्णांक sp_pci_init(व्योम);
व्योम sp_pci_निकास(व्योम);

पूर्णांक sp_platक्रमm_init(व्योम);
व्योम sp_platक्रमm_निकास(व्योम);

काष्ठा sp_device *sp_alloc_काष्ठा(काष्ठा device *dev);

पूर्णांक sp_init(काष्ठा sp_device *sp);
व्योम sp_destroy(काष्ठा sp_device *sp);
काष्ठा sp_device *sp_get_master(व्योम);

पूर्णांक sp_suspend(काष्ठा sp_device *sp);
पूर्णांक sp_resume(काष्ठा sp_device *sp);
पूर्णांक sp_request_ccp_irq(काष्ठा sp_device *sp, irq_handler_t handler,
		       स्थिर अक्षर *name, व्योम *data);
व्योम sp_मुक्त_ccp_irq(काष्ठा sp_device *sp, व्योम *data);
पूर्णांक sp_request_psp_irq(काष्ठा sp_device *sp, irq_handler_t handler,
		       स्थिर अक्षर *name, व्योम *data);
व्योम sp_मुक्त_psp_irq(काष्ठा sp_device *sp, व्योम *data);
काष्ठा sp_device *sp_get_psp_master_device(व्योम);

#अगर_घोषित CONFIG_CRYPTO_DEV_SP_CCP

पूर्णांक ccp_dev_init(काष्ठा sp_device *sp);
व्योम ccp_dev_destroy(काष्ठा sp_device *sp);

व्योम ccp_dev_suspend(काष्ठा sp_device *sp);
व्योम ccp_dev_resume(काष्ठा sp_device *sp);

#अन्यथा	/* !CONFIG_CRYPTO_DEV_SP_CCP */

अटल अंतरभूत पूर्णांक ccp_dev_init(काष्ठा sp_device *sp)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ccp_dev_destroy(काष्ठा sp_device *sp) अणु पूर्ण
अटल अंतरभूत व्योम ccp_dev_suspend(काष्ठा sp_device *sp) अणु पूर्ण
अटल अंतरभूत व्योम ccp_dev_resume(काष्ठा sp_device *sp) अणु पूर्ण
#पूर्ण_अगर	/* CONFIG_CRYPTO_DEV_SP_CCP */

#अगर_घोषित CONFIG_CRYPTO_DEV_SP_PSP

पूर्णांक psp_dev_init(काष्ठा sp_device *sp);
व्योम psp_pci_init(व्योम);
व्योम psp_dev_destroy(काष्ठा sp_device *sp);
व्योम psp_pci_निकास(व्योम);

#अन्यथा /* !CONFIG_CRYPTO_DEV_SP_PSP */

अटल अंतरभूत पूर्णांक psp_dev_init(काष्ठा sp_device *sp) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम psp_pci_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम psp_dev_destroy(काष्ठा sp_device *sp) अणु पूर्ण
अटल अंतरभूत व्योम psp_pci_निकास(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_SP_PSP */

#पूर्ण_अगर
