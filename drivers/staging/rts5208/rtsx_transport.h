<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#अगर_अघोषित __REALTEK_RTSX_TRANSPORT_H
#घोषणा __REALTEK_RTSX_TRANSPORT_H

#समावेश "rtsx.h"
#समावेश "rtsx_chip.h"

#घोषणा WAIT_TIME	2000

अचिन्हित पूर्णांक rtsx_stor_access_xfer_buf(अचिन्हित अक्षर *buffer,
				       अचिन्हित पूर्णांक buflen,
				       काष्ठा scsi_cmnd *srb,
				       अचिन्हित पूर्णांक *index,
				       अचिन्हित पूर्णांक *offset,
				       क्रमागत xfer_buf_dir dir);
व्योम rtsx_stor_set_xfer_buf(अचिन्हित अक्षर *buffer, अचिन्हित पूर्णांक buflen,
			    काष्ठा scsi_cmnd *srb);
व्योम rtsx_stor_get_xfer_buf(अचिन्हित अक्षर *buffer, अचिन्हित पूर्णांक buflen,
			    काष्ठा scsi_cmnd *srb);
व्योम rtsx_invoke_transport(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip);

#घोषणा rtsx_init_cmd(chip)			((chip)->ci = 0)

व्योम rtsx_add_cmd(काष्ठा rtsx_chip *chip, u8 cmd_type, u16 reg_addr, u8 mask,
		  u8 data);
व्योम rtsx_send_cmd_no_रुको(काष्ठा rtsx_chip *chip);
पूर्णांक rtsx_send_cmd(काष्ठा rtsx_chip *chip, u8 card, पूर्णांक समयout);

अटल अंतरभूत u8 *rtsx_get_cmd_data(काष्ठा rtsx_chip *chip)
अणु
#अगर_घोषित CMD_USING_SG
	वापस (u8 *)(chip->host_sg_tbl_ptr);
#अन्यथा
	वापस (u8 *)(chip->host_cmds_ptr);
#पूर्ण_अगर
पूर्ण

पूर्णांक rtsx_transfer_data(काष्ठा rtsx_chip *chip, u8 card, व्योम *buf, माप_प्रकार len,
		       पूर्णांक use_sg, क्रमागत dma_data_direction dma_dir,
		       पूर्णांक समयout);

पूर्णांक rtsx_transfer_data_partial(काष्ठा rtsx_chip *chip, u8 card,	व्योम *buf,
			       माप_प्रकार len, पूर्णांक use_sg, अचिन्हित पूर्णांक *index,
			       अचिन्हित पूर्णांक *offset,
			       क्रमागत dma_data_direction dma_dir, पूर्णांक समयout);

#पूर्ण_अगर   /* __REALTEK_RTSX_TRANSPORT_H */
