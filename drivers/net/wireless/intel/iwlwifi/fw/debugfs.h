<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश "runtime.h"

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
व्योम iwl_fwrt_dbgfs_रेजिस्टर(काष्ठा iwl_fw_runसमय *fwrt,
			    काष्ठा dentry *dbgfs_dir);

#अन्यथा
अटल अंतरभूत व्योम iwl_fwrt_dbgfs_रेजिस्टर(काष्ठा iwl_fw_runसमय *fwrt,
					   काष्ठा dentry *dbgfs_dir) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUGFS */
