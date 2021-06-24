<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#अगर_अघोषित _IONIC_BUS_H_
#घोषणा _IONIC_BUS_H_

पूर्णांक ionic_bus_get_irq(काष्ठा ionic *ionic, अचिन्हित पूर्णांक num);
स्थिर अक्षर *ionic_bus_info(काष्ठा ionic *ionic);
पूर्णांक ionic_bus_alloc_irq_vectors(काष्ठा ionic *ionic, अचिन्हित पूर्णांक nपूर्णांकrs);
व्योम ionic_bus_मुक्त_irq_vectors(काष्ठा ionic *ionic);
पूर्णांक ionic_bus_रेजिस्टर_driver(व्योम);
व्योम ionic_bus_unरेजिस्टर_driver(व्योम);
व्योम __iomem *ionic_bus_map_dbpage(काष्ठा ionic *ionic, पूर्णांक page_num);
व्योम ionic_bus_unmap_dbpage(काष्ठा ionic *ionic, व्योम __iomem *page);

#पूर्ण_अगर /* _IONIC_BUS_H_ */
