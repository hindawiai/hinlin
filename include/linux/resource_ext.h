<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015, Intel Corporation
 * Author: Jiang Liu <jiang.liu@linux.पूर्णांकel.com>
 */
#अगर_अघोषित _LINUX_RESOURCE_EXT_H
#घोषणा _LINUX_RESOURCE_EXT_H
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>

/* Represent resource winकरोw क्रम bridge devices */
काष्ठा resource_win अणु
	काष्ठा resource res;		/* In master (CPU) address space */
	resource_माप_प्रकार offset;		/* Translation offset क्रम bridge */
पूर्ण;

/*
 * Common resource list management data काष्ठाure and पूर्णांकerfaces to support
 * ACPI, PNP and PCI host bridge etc.
 */
काष्ठा resource_entry अणु
	काष्ठा list_head	node;
	काष्ठा resource		*res;	/* In master (CPU) address space */
	resource_माप_प्रकार		offset;	/* Translation offset क्रम bridge */
	काष्ठा resource		__res;	/* Default storage क्रम res */
पूर्ण;

बाह्य काष्ठा resource_entry *
resource_list_create_entry(काष्ठा resource *res, माप_प्रकार extra_size);
बाह्य व्योम resource_list_मुक्त(काष्ठा list_head *head);

अटल अंतरभूत व्योम resource_list_add(काष्ठा resource_entry *entry,
				     काष्ठा list_head *head)
अणु
	list_add(&entry->node, head);
पूर्ण

अटल अंतरभूत व्योम resource_list_add_tail(काष्ठा resource_entry *entry,
					  काष्ठा list_head *head)
अणु
	list_add_tail(&entry->node, head);
पूर्ण

अटल अंतरभूत व्योम resource_list_del(काष्ठा resource_entry *entry)
अणु
	list_del(&entry->node);
पूर्ण

अटल अंतरभूत व्योम resource_list_मुक्त_entry(काष्ठा resource_entry *entry)
अणु
	kमुक्त(entry);
पूर्ण

अटल अंतरभूत व्योम
resource_list_destroy_entry(काष्ठा resource_entry *entry)
अणु
	resource_list_del(entry);
	resource_list_मुक्त_entry(entry);
पूर्ण

#घोषणा resource_list_क्रम_each_entry(entry, list)	\
	list_क्रम_each_entry((entry), (list), node)

#घोषणा resource_list_क्रम_each_entry_safe(entry, पंचांगp, list)	\
	list_क्रम_each_entry_safe((entry), (पंचांगp), (list), node)

अटल अंतरभूत काष्ठा resource_entry *
resource_list_first_type(काष्ठा list_head *list, अचिन्हित दीर्घ type)
अणु
	काष्ठा resource_entry *entry;

	resource_list_क्रम_each_entry(entry, list) अणु
		अगर (resource_type(entry->res) == type)
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* _LINUX_RESOURCE_EXT_H */
