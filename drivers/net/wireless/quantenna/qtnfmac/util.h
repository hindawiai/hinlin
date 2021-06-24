<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015 Quantenna Communications. All rights reserved. */

#अगर_अघोषित QTNFMAC_UTIL_H
#घोषणा QTNFMAC_UTIL_H

#समावेश <linux/kernel.h>
#समावेश "core.h"

स्थिर अक्षर *qtnf_chipid_to_string(अचिन्हित दीर्घ chip_id);

व्योम qtnf_sta_list_init(काष्ठा qtnf_sta_list *list);

काष्ठा qtnf_sta_node *qtnf_sta_list_lookup(काष्ठा qtnf_sta_list *list,
					   स्थिर u8 *mac);
काष्ठा qtnf_sta_node *qtnf_sta_list_lookup_index(काष्ठा qtnf_sta_list *list,
						 माप_प्रकार index);
काष्ठा qtnf_sta_node *qtnf_sta_list_add(काष्ठा qtnf_vअगर *vअगर,
					स्थिर u8 *mac);
bool qtnf_sta_list_del(काष्ठा qtnf_vअगर *vअगर, स्थिर u8 *mac);

व्योम qtnf_sta_list_मुक्त(काष्ठा qtnf_sta_list *list);

अटल अंतरभूत माप_प्रकार qtnf_sta_list_size(स्थिर काष्ठा qtnf_sta_list *list)
अणु
	वापस atomic_पढ़ो(&list->size);
पूर्ण

अटल अंतरभूत bool qtnf_sta_list_empty(स्थिर काष्ठा qtnf_sta_list *list)
अणु
	वापस list_empty(&list->head);
पूर्ण

#पूर्ण_अगर /* QTNFMAC_UTIL_H */
