<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Pvpanic Device Support
 *
 *  Copyright (C) 2021 Oracle.
 */

#अगर_अघोषित PVPANIC_H_
#घोषणा PVPANIC_H_

काष्ठा pvpanic_instance अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक capability;
	अचिन्हित पूर्णांक events;
	काष्ठा list_head list;
पूर्ण;

पूर्णांक pvpanic_probe(काष्ठा pvpanic_instance *pi);
व्योम pvpanic_हटाओ(काष्ठा pvpanic_instance *pi);

#पूर्ण_अगर /* PVPANIC_H_ */
