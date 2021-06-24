<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * debug.h - Designware USB2 DRD controller debug header
 *
 * Copyright (C) 2015 Intel Corporation
 * Mian Yousaf Kaukab <yousaf.kaukab@पूर्णांकel.com>
 */

#समावेश "core.h"

#अगर_घोषित CONFIG_DEBUG_FS
पूर्णांक dwc2_debugfs_init(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_debugfs_निकास(काष्ठा dwc2_hsotg *hsotg);
#अन्यथा
अटल अंतरभूत पूर्णांक dwc2_debugfs_init(काष्ठा dwc2_hsotg *hsotg)
अणु  वापस 0;  पूर्ण
अटल अंतरभूत व्योम dwc2_debugfs_निकास(काष्ठा dwc2_hsotg *hsotg)
अणु  पूर्ण
#पूर्ण_अगर
