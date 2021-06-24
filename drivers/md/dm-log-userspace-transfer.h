<शैली गुरु>
/*
 * Copyright (C) 2006-2009 Red Hat, Inc.
 *
 * This file is released under the LGPL.
 */

#अगर_अघोषित __DM_LOG_USERSPACE_TRANSFER_H__
#घोषणा __DM_LOG_USERSPACE_TRANSFER_H__

#घोषणा DM_MSG_PREFIX "dm-log-userspace"

पूर्णांक dm_ulog_tfr_init(व्योम);
व्योम dm_ulog_tfr_निकास(व्योम);
पूर्णांक dm_consult_userspace(स्थिर अक्षर *uuid, uपूर्णांक64_t luid, पूर्णांक request_type,
			 अक्षर *data, माप_प्रकार data_size,
			 अक्षर *rdata, माप_प्रकार *rdata_size);

#पूर्ण_अगर /* __DM_LOG_USERSPACE_TRANSFER_H__ */
