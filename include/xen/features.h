<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * features.h
 *
 * Query the features reported by Xen.
 *
 * Copyright (c) 2006, Ian Campbell
 */

#अगर_अघोषित __XEN_FEATURES_H__
#घोषणा __XEN_FEATURES_H__

#समावेश <xen/पूर्णांकerface/features.h>

व्योम xen_setup_features(व्योम);

बाह्य u8 xen_features[XENFEAT_NR_SUBMAPS * 32];

अटल अंतरभूत पूर्णांक xen_feature(पूर्णांक flag)
अणु
	वापस xen_features[flag];
पूर्ण

#पूर्ण_अगर /* __ASM_XEN_FEATURES_H__ */
