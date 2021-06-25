<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SiFive Platक्रमm EDAC Driver
 *
 * Copyright (C) 2018-2019 SiFive, Inc.
 *
 * This driver is partially based on octeon_edac-pc.c
 *
 */
#समावेश <linux/edac.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "edac_module.h"
#समावेश <soc/sअगरive/sअगरive_l2_cache.h>

#घोषणा DRVNAME "sifive_edac"

काष्ठा sअगरive_edac_priv अणु
	काष्ठा notअगरier_block notअगरier;
	काष्ठा edac_device_ctl_info *dci;
पूर्ण;

/**
 * EDAC error callback
 *
 * @event: non-zero अगर unrecoverable.
 */
अटल
पूर्णांक ecc_err_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	स्थिर अक्षर *msg = (अक्षर *)ptr;
	काष्ठा sअगरive_edac_priv *p;

	p = container_of(this, काष्ठा sअगरive_edac_priv, notअगरier);

	अगर (event == SIFIVE_L2_ERR_TYPE_UE)
		edac_device_handle_ue(p->dci, 0, 0, msg);
	अन्यथा अगर (event == SIFIVE_L2_ERR_TYPE_CE)
		edac_device_handle_ce(p->dci, 0, 0, msg);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक ecc_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sअगरive_edac_priv *p;

	p = devm_kzalloc(&pdev->dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	p->notअगरier.notअगरier_call = ecc_err_event;
	platक्रमm_set_drvdata(pdev, p);

	p->dci = edac_device_alloc_ctl_info(0, "sifive_ecc", 1, "sifive_ecc",
					    1, 1, शून्य, 0,
					    edac_device_alloc_index());
	अगर (!p->dci)
		वापस -ENOMEM;

	p->dci->dev = &pdev->dev;
	p->dci->mod_name = "Sifive ECC Manager";
	p->dci->ctl_name = dev_name(&pdev->dev);
	p->dci->dev_name = dev_name(&pdev->dev);

	अगर (edac_device_add_device(p->dci)) अणु
		dev_err(p->dci->dev, "failed to register with EDAC core\n");
		जाओ err;
	पूर्ण

	रेजिस्टर_sअगरive_l2_error_notअगरier(&p->notअगरier);

	वापस 0;

err:
	edac_device_मुक्त_ctl_info(p->dci);

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक ecc_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sअगरive_edac_priv *p = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_sअगरive_l2_error_notअगरier(&p->notअगरier);
	edac_device_del_device(&pdev->dev);
	edac_device_मुक्त_ctl_info(p->dci);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device *sअगरive_pdev;

अटल पूर्णांक __init sअगरive_edac_init(व्योम)
अणु
	पूर्णांक ret;

	sअगरive_pdev = platक्रमm_device_रेजिस्टर_simple(DRVNAME, 0, शून्य, 0);
	अगर (IS_ERR(sअगरive_pdev))
		वापस PTR_ERR(sअगरive_pdev);

	ret = ecc_रेजिस्टर(sअगरive_pdev);
	अगर (ret)
		platक्रमm_device_unरेजिस्टर(sअगरive_pdev);

	वापस ret;
पूर्ण

अटल व्योम __निकास sअगरive_edac_निकास(व्योम)
अणु
	ecc_unरेजिस्टर(sअगरive_pdev);
	platक्रमm_device_unरेजिस्टर(sअगरive_pdev);
पूर्ण

module_init(sअगरive_edac_init);
module_निकास(sअगरive_edac_निकास);

MODULE_AUTHOR("SiFive Inc.");
MODULE_DESCRIPTION("SiFive platform EDAC driver");
MODULE_LICENSE("GPL v2");
