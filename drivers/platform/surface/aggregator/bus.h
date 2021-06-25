<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Surface System Aggregator Module bus and device पूर्णांकegration.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _SURFACE_AGGREGATOR_BUS_H
#घोषणा _SURFACE_AGGREGATOR_BUS_H

#समावेश <linux/surface_aggregator/controller.h>

#अगर_घोषित CONFIG_SURFACE_AGGREGATOR_BUS

व्योम ssam_controller_हटाओ_clients(काष्ठा ssam_controller *ctrl);

पूर्णांक ssam_bus_रेजिस्टर(व्योम);
व्योम ssam_bus_unरेजिस्टर(व्योम);

#अन्यथा /* CONFIG_SURFACE_AGGREGATOR_BUS */

अटल अंतरभूत व्योम ssam_controller_हटाओ_clients(काष्ठा ssam_controller *ctrl) अणुपूर्ण
अटल अंतरभूत पूर्णांक ssam_bus_रेजिस्टर(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ssam_bus_unरेजिस्टर(व्योम) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_SURFACE_AGGREGATOR_BUS */
#पूर्ण_अगर /* _SURFACE_AGGREGATOR_BUS_H */
