<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010, Intel Corporation.
 *
 * Author: John Fastabend <john.r.fastabend@पूर्णांकel.com>
 */

#अगर_अघोषित _DCB_EVENT_H
#घोषणा _DCB_EVENT_H

क्रमागत dcbevent_notअगर_type अणु
	DCB_APP_EVENT = 1,
पूर्ण;

#अगर_घोषित CONFIG_DCB
पूर्णांक रेजिस्टर_dcbevent_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_dcbevent_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक call_dcbevent_notअगरiers(अचिन्हित दीर्घ val, व्योम *v);
#अन्यथा
अटल अंतरभूत पूर्णांक
रेजिस्टर_dcbevent_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक unरेजिस्टर_dcbevent_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक call_dcbevent_notअगरiers(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DCB */

#पूर्ण_अगर
