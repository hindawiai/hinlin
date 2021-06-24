<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित _LTQ_PROM_H__
#घोषणा _LTQ_PROM_H__

#घोषणा LTQ_SYS_TYPE_LEN	0x100
#घोषणा LTQ_SYS_REV_LEN		0x10

काष्ठा ltq_soc_info अणु
	अचिन्हित अक्षर *name;
	अचिन्हित पूर्णांक rev;
	अचिन्हित अक्षर rev_type[LTQ_SYS_REV_LEN];
	अचिन्हित पूर्णांक srev;
	अचिन्हित पूर्णांक partnum;
	अचिन्हित पूर्णांक type;
	अचिन्हित अक्षर sys_type[LTQ_SYS_TYPE_LEN];
	अचिन्हित अक्षर *compatible;
पूर्ण;

बाह्य व्योम ltq_soc_detect(काष्ठा ltq_soc_info *i);
बाह्य व्योम ltq_soc_init(व्योम);

#पूर्ण_अगर
