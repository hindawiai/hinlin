<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MUSB OTG driver debug defines
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 */

#अगर_अघोषित __MUSB_LINUX_DEBUG_H__
#घोषणा __MUSB_LINUX_DEBUG_H__

#घोषणा yprपूर्णांकk(facility, क्रमmat, args...) \
	करो अणु prपूर्णांकk(facility "%s %d: " क्रमmat , \
	__func__, __LINE__ , ## args); पूर्ण जबतक (0)
#घोषणा WARNING(fmt, args...) yprपूर्णांकk(KERN_WARNING, fmt, ## args)
#घोषणा INFO(fmt, args...) yprपूर्णांकk(KERN_INFO, fmt, ## args)
#घोषणा ERR(fmt, args...) yprपूर्णांकk(KERN_ERR, fmt, ## args)

व्योम musb_dbg(काष्ठा musb *musb, स्थिर अक्षर *fmt, ...);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम musb_init_debugfs(काष्ठा musb *musb);
व्योम musb_निकास_debugfs(काष्ठा musb *musb);
#अन्यथा
अटल अंतरभूत व्योम musb_init_debugfs(काष्ठा musb *musb)
अणु
पूर्ण
अटल अंतरभूत व्योम musb_निकास_debugfs(काष्ठा musb *musb)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर				/*  __MUSB_LINUX_DEBUG_H__ */
