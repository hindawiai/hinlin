<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#समावेश "util.h"
#समावेश "qtn_hw_ids.h"

व्योम qtnf_sta_list_init(काष्ठा qtnf_sta_list *list)
अणु
	अगर (unlikely(!list))
		वापस;

	INIT_LIST_HEAD(&list->head);
	atomic_set(&list->size, 0);
पूर्ण

काष्ठा qtnf_sta_node *qtnf_sta_list_lookup(काष्ठा qtnf_sta_list *list,
					   स्थिर u8 *mac)
अणु
	काष्ठा qtnf_sta_node *node;

	अगर (unlikely(!mac))
		वापस शून्य;

	list_क्रम_each_entry(node, &list->head, list) अणु
		अगर (ether_addr_equal(node->mac_addr, mac))
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा qtnf_sta_node *qtnf_sta_list_lookup_index(काष्ठा qtnf_sta_list *list,
						 माप_प्रकार index)
अणु
	काष्ठा qtnf_sta_node *node;

	अगर (qtnf_sta_list_size(list) <= index)
		वापस शून्य;

	list_क्रम_each_entry(node, &list->head, list) अणु
		अगर (index-- == 0)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा qtnf_sta_node *qtnf_sta_list_add(काष्ठा qtnf_vअगर *vअगर,
					स्थिर u8 *mac)
अणु
	काष्ठा qtnf_sta_list *list = &vअगर->sta_list;
	काष्ठा qtnf_sta_node *node;

	अगर (unlikely(!mac))
		वापस शून्य;

	node = qtnf_sta_list_lookup(list, mac);

	अगर (node)
		जाओ करोne;

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (unlikely(!node))
		जाओ करोne;

	ether_addr_copy(node->mac_addr, mac);
	list_add_tail(&node->list, &list->head);
	atomic_inc(&list->size);
	++vअगर->generation;

करोne:
	वापस node;
पूर्ण

bool qtnf_sta_list_del(काष्ठा qtnf_vअगर *vअगर, स्थिर u8 *mac)
अणु
	काष्ठा qtnf_sta_list *list = &vअगर->sta_list;
	काष्ठा qtnf_sta_node *node;
	bool ret = false;

	node = qtnf_sta_list_lookup(list, mac);

	अगर (node) अणु
		list_del(&node->list);
		atomic_dec(&list->size);
		kमुक्त(node);
		++vअगर->generation;
		ret = true;
	पूर्ण

	वापस ret;
पूर्ण

व्योम qtnf_sta_list_मुक्त(काष्ठा qtnf_sta_list *list)
अणु
	काष्ठा qtnf_sta_node *node, *पंचांगp;

	atomic_set(&list->size, 0);

	list_क्रम_each_entry_safe(node, पंचांगp, &list->head, list) अणु
		list_del(&node->list);
		kमुक्त(node);
	पूर्ण

	INIT_LIST_HEAD(&list->head);
पूर्ण

स्थिर अक्षर *qtnf_chipid_to_string(अचिन्हित दीर्घ chip_id)
अणु
	चयन (chip_id) अणु
	हाल QTN_CHIP_ID_TOPAZ:
		वापस "Topaz";
	हाल QTN_CHIP_ID_PEARL:
		वापस "Pearl revA";
	हाल QTN_CHIP_ID_PEARL_B:
		वापस "Pearl revB";
	हाल QTN_CHIP_ID_PEARL_C:
		वापस "Pearl revC";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(qtnf_chipid_to_string);
