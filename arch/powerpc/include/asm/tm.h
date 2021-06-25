<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Transactional memory support routines to reclaim and recheckpoपूर्णांक
 * transactional process state.
 *
 * Copyright 2012 Matt Evans & Michael Neuling, IBM Corporation.
 */

#समावेश <uapi/यंत्र/पंचांग.h>

#अगर_अघोषित __ASSEMBLY__

बाह्य व्योम पंचांग_reclaim(काष्ठा thपढ़ो_काष्ठा *thपढ़ो,
		       uपूर्णांक8_t cause);
बाह्य व्योम पंचांग_reclaim_current(uपूर्णांक8_t cause);
बाह्य व्योम पंचांग_recheckpoपूर्णांक(काष्ठा thपढ़ो_काष्ठा *thपढ़ो);
बाह्य व्योम पंचांग_save_sprs(काष्ठा thपढ़ो_काष्ठा *thपढ़ो);
बाह्य व्योम पंचांग_restore_sprs(काष्ठा thपढ़ो_काष्ठा *thपढ़ो);

बाह्य bool पंचांग_suspend_disabled;

#पूर्ण_अगर /* __ASSEMBLY__ */
