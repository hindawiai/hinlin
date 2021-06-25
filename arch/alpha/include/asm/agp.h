<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित AGP_H
#घोषणा AGP_H 1

#समावेश <यंत्र/पन.स>

/* dummy क्रम now */

#घोषणा map_page_पूर्णांकo_agp(page) 
#घोषणा unmap_page_from_agp(page) 
#घोषणा flush_agp_cache() mb()

/* GATT allocation. Returns/accepts GATT kernel भव address. */
#घोषणा alloc_gatt_pages(order)		\
	((अक्षर *)__get_मुक्त_pages(GFP_KERNEL, (order)))
#घोषणा मुक्त_gatt_pages(table, order)	\
	मुक्त_pages((अचिन्हित दीर्घ)(table), (order))

#पूर्ण_अगर
