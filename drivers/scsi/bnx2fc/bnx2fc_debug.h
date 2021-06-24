<शैली गुरु>
/* bnx2fc_debug.h: QLogic Linux FCoE offload driver.
 * Handles operations such as session offload/upload etc, and manages
 * session resources such as connection id and qp resources.
 *
 * Copyright (c) 2008-2013 Broadcom Corporation
 * Copyright (c) 2014-2016 QLogic Corporation
 * Copyright (c) 2016-2017 Cavium Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 */

#अगर_अघोषित __BNX2FC_DEBUG__
#घोषणा __BNX2FC_DEBUG__

/* Log level bit mask */
#घोषणा LOG_IO		0x01	/* scsi cmd error, cleanup */
#घोषणा LOG_TGT		0x02	/* Session setup, cleanup, etc' */
#घोषणा LOG_HBA		0x04	/* lport events, link, mtu, etc' */
#घोषणा LOG_ELS		0x08	/* ELS logs */
#घोषणा LOG_MISC	0x10	/* fcoe L2 frame related logs*/
#घोषणा LOG_ALL		0xff	/* LOG all messages */

बाह्य अचिन्हित पूर्णांक bnx2fc_debug_level;

#घोषणा BNX2FC_ELS_DBG(fmt, ...)				\
करो अणु								\
	अगर (unlikely(bnx2fc_debug_level & LOG_ELS))		\
		pr_info(fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

#घोषणा BNX2FC_MISC_DBG(fmt, ...)				\
करो अणु								\
	अगर (unlikely(bnx2fc_debug_level & LOG_MISC))		\
		pr_info(fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

__म_लिखो(2, 3)
व्योम BNX2FC_IO_DBG(स्थिर काष्ठा bnx2fc_cmd *io_req, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम BNX2FC_TGT_DBG(स्थिर काष्ठा bnx2fc_rport *tgt, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम BNX2FC_HBA_DBG(स्थिर काष्ठा fc_lport *lport, स्थिर अक्षर *fmt, ...);

#पूर्ण_अगर
