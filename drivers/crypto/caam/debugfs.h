<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2019 NXP */

#अगर_अघोषित CAAM_DEBUGFS_H
#घोषणा CAAM_DEBUGFS_H

काष्ठा dentry;
काष्ठा caam_drv_निजी;

#अगर_घोषित CONFIG_DEBUG_FS
व्योम caam_debugfs_init(काष्ठा caam_drv_निजी *ctrlpriv, काष्ठा dentry *root);
#अन्यथा
अटल अंतरभूत व्योम caam_debugfs_init(काष्ठा caam_drv_निजी *ctrlpriv,
				     काष्ठा dentry *root)
अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_DEBUG_FS) && defined(CONFIG_CAAM_QI)
व्योम caam_debugfs_qi_congested(व्योम);
व्योम caam_debugfs_qi_init(काष्ठा caam_drv_निजी *ctrlpriv);
#अन्यथा
अटल अंतरभूत व्योम caam_debugfs_qi_congested(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम caam_debugfs_qi_init(काष्ठा caam_drv_निजी *ctrlpriv) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CAAM_DEBUGFS_H */
