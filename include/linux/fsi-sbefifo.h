<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SBEFIFO FSI Client device driver
 *
 * Copyright (C) IBM Corporation 2017
 */

#अगर_अघोषित LINUX_FSI_SBEFIFO_H
#घोषणा LINUX_FSI_SBEFIFO_H

#घोषणा SBEFIFO_CMD_PUT_OCC_SRAM	0xa404
#घोषणा SBEFIFO_CMD_GET_OCC_SRAM	0xa403
#घोषणा SBEFIFO_CMD_GET_SBE_FFDC	0xa801

#घोषणा SBEFIFO_MAX_FFDC_SIZE		0x2000

काष्ठा device;

पूर्णांक sbefअगरo_submit(काष्ठा device *dev, स्थिर __be32 *command, माप_प्रकार cmd_len,
		   __be32 *response, माप_प्रकार *resp_len);

पूर्णांक sbefअगरo_parse_status(काष्ठा device *dev, u16 cmd, __be32 *response,
			 माप_प्रकार resp_len, माप_प्रकार *data_len);

#पूर्ण_अगर /* LINUX_FSI_SBEFIFO_H */
