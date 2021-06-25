<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *	watchकरोg_core.h
 *
 *	(c) Copyright 2008-2011 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	(c) Copyright 2008-2011 Wim Van Sebroeck <wim@iguana.be>.
 *
 *	This source code is part of the generic code that can be used
 *	by all the watchकरोg समयr drivers.
 *
 *	Based on source code of the following authors:
 *	  Matt Domsch <Matt_Domsch@dell.com>,
 *	  Rob Radez <rob@osinvestor.com>,
 *	  Rusty Lynch <rusty@linux.co.पूर्णांकel.com>
 *	  Satyam Sharma <satyam@infradead.org>
 *	  Randy Dunlap <अक्रमy.dunlap@oracle.com>
 *
 *	Neither Alan Cox, CymruNet Ltd., Wim Van Sebroeck nor Iguana vzw.
 *	admit liability nor provide warranty क्रम any of this software.
 *	This material is provided "AS-IS" and at no अक्षरge.
 */

#घोषणा MAX_DOGS	32	/* Maximum number of watchकरोg devices */

/*
 *	Functions/procedures to be called by the core
 */
बाह्य पूर्णांक watchकरोg_dev_रेजिस्टर(काष्ठा watchकरोg_device *);
बाह्य व्योम watchकरोg_dev_unरेजिस्टर(काष्ठा watchकरोg_device *);
बाह्य पूर्णांक __init watchकरोg_dev_init(व्योम);
बाह्य व्योम __निकास watchकरोg_dev_निकास(व्योम);
