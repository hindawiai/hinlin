<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#अगर_अघोषित __CC_DEBUGFS_H__
#घोषणा __CC_DEBUGFS_H__

#अगर_घोषित CONFIG_DEBUG_FS
व्योम cc_debugfs_global_init(व्योम);
व्योम cc_debugfs_global_fini(व्योम);

पूर्णांक cc_debugfs_init(काष्ठा cc_drvdata *drvdata);
व्योम cc_debugfs_fini(काष्ठा cc_drvdata *drvdata);

#अन्यथा

अटल अंतरभूत व्योम cc_debugfs_global_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम cc_debugfs_global_fini(व्योम) अणुपूर्ण

अटल अंतरभूत पूर्णांक cc_debugfs_init(काष्ठा cc_drvdata *drvdata)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cc_debugfs_fini(काष्ठा cc_drvdata *drvdata) अणुपूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /*__CC_SYSFS_H__*/
