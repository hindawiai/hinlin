<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 2007 - 2009 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित DCA_H
#घोषणा DCA_H

#समावेश <linux/pci.h>

/* DCA Provider API */

/* DCA Notअगरier Interface */
व्योम dca_रेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb);
व्योम dca_unरेजिस्टर_notअगरy(काष्ठा notअगरier_block *nb);

#घोषणा DCA_PROVIDER_ADD     0x0001
#घोषणा DCA_PROVIDER_REMOVE  0x0002

काष्ठा dca_provider अणु
	काष्ठा list_head	node;
	स्थिर काष्ठा dca_ops	*ops;
	काष्ठा device 		*cd;
	पूर्णांक			 id;
पूर्ण;

काष्ठा dca_करोमुख्य अणु
	काष्ठा list_head	node;
	काष्ठा list_head	dca_providers;
	काष्ठा pci_bus		*pci_rc;
पूर्ण;

काष्ठा dca_ops अणु
	पूर्णांक	(*add_requester)    (काष्ठा dca_provider *, काष्ठा device *);
	पूर्णांक	(*हटाओ_requester) (काष्ठा dca_provider *, काष्ठा device *);
	u8	(*get_tag)	    (काष्ठा dca_provider *, काष्ठा device *,
				     पूर्णांक cpu);
	पूर्णांक	(*dev_managed)      (काष्ठा dca_provider *, काष्ठा device *);
पूर्ण;

काष्ठा dca_provider *alloc_dca_provider(स्थिर काष्ठा dca_ops *ops,
					पूर्णांक priv_size);
व्योम मुक्त_dca_provider(काष्ठा dca_provider *dca);
पूर्णांक रेजिस्टर_dca_provider(काष्ठा dca_provider *dca, काष्ठा device *dev);
व्योम unरेजिस्टर_dca_provider(काष्ठा dca_provider *dca, काष्ठा device *dev);

अटल अंतरभूत व्योम *dca_priv(काष्ठा dca_provider *dca)
अणु
	वापस (व्योम *)dca + माप(काष्ठा dca_provider);
पूर्ण

/* Requester API */
#घोषणा DCA_GET_TAG_TWO_ARGS
पूर्णांक dca_add_requester(काष्ठा device *dev);
पूर्णांक dca_हटाओ_requester(काष्ठा device *dev);
u8 dca_get_tag(पूर्णांक cpu);
u8 dca3_get_tag(काष्ठा device *dev, पूर्णांक cpu);

/* पूर्णांकernal stuff */
पूर्णांक __init dca_sysfs_init(व्योम);
व्योम __निकास dca_sysfs_निकास(व्योम);
पूर्णांक dca_sysfs_add_provider(काष्ठा dca_provider *dca, काष्ठा device *dev);
व्योम dca_sysfs_हटाओ_provider(काष्ठा dca_provider *dca);
पूर्णांक dca_sysfs_add_req(काष्ठा dca_provider *dca, काष्ठा device *dev, पूर्णांक slot);
व्योम dca_sysfs_हटाओ_req(काष्ठा dca_provider *dca, पूर्णांक slot);

#पूर्ण_अगर /* DCA_H */
