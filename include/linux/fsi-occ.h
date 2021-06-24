<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित LINUX_FSI_OCC_H
#घोषणा LINUX_FSI_OCC_H

काष्ठा device;

#घोषणा OCC_RESP_CMD_IN_PRG		0xFF
#घोषणा OCC_RESP_SUCCESS		0
#घोषणा OCC_RESP_CMD_INVAL		0x11
#घोषणा OCC_RESP_CMD_LEN_INVAL		0x12
#घोषणा OCC_RESP_DATA_INVAL		0x13
#घोषणा OCC_RESP_CHKSUM_ERR		0x14
#घोषणा OCC_RESP_INT_ERR		0x15
#घोषणा OCC_RESP_BAD_STATE		0x16
#घोषणा OCC_RESP_CRIT_EXCEPT		0xE0
#घोषणा OCC_RESP_CRIT_INIT		0xE1
#घोषणा OCC_RESP_CRIT_WATCHDOG		0xE2
#घोषणा OCC_RESP_CRIT_OCB		0xE3
#घोषणा OCC_RESP_CRIT_HW		0xE4

पूर्णांक fsi_occ_submit(काष्ठा device *dev, स्थिर व्योम *request, माप_प्रकार req_len,
		   व्योम *response, माप_प्रकार *resp_len);

#पूर्ण_अगर /* LINUX_FSI_OCC_H */
