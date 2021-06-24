<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#अगर_अघोषित _GDM_TTY_H_
#घोषणा _GDM_TTY_H_

#समावेश <linux/types.h>
#समावेश <linux/tty.h>

#घोषणा TTY_MAX_COUNT		2

#घोषणा MAX_ISSUE_NUM 3

क्रमागत TO_HOST_RESULT अणु
	TO_HOST_BUFFER_REQUEST_FAIL = 1,
	TO_HOST_PORT_CLOSE = 2,
	TO_HOST_INVALID_PACKET = 3,
पूर्ण;

क्रमागत RECV_PACKET_PROCESS अणु
	RECV_PACKET_PROCESS_COMPLETE = 0,
	RECV_PACKET_PROCESS_CONTINUE = 1,
पूर्ण;

काष्ठा gdm अणु
	काष्ठा tty_dev *tty_dev;
	काष्ठा tty_port port;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक minor;
पूर्ण;

काष्ठा tty_dev अणु
	व्योम *priv_dev;
	पूर्णांक (*send_func)(व्योम *priv_dev,
			 व्योम *data,
			 पूर्णांक len,
			 पूर्णांक tty_index,
			 व्योम (*cb)(व्योम *cb_data),
			 व्योम *cb_data);
	पूर्णांक (*recv_func)(व्योम *priv_dev,
			 पूर्णांक (*cb)(व्योम *data,
				   पूर्णांक len,
				   पूर्णांक tty_index,
				   काष्ठा tty_dev *tty_dev,
				   पूर्णांक complete));
	पूर्णांक (*send_control)(व्योम *priv_dev,
			    पूर्णांक request,
			    पूर्णांक value,
			    व्योम *data,
			    पूर्णांक len);
	काष्ठा gdm *gdm[2];
पूर्ण;

पूर्णांक रेजिस्टर_lte_tty_driver(व्योम);
व्योम unरेजिस्टर_lte_tty_driver(व्योम);
पूर्णांक रेजिस्टर_lte_tty_device(काष्ठा tty_dev *tty_dev, काष्ठा device *dev);
व्योम unरेजिस्टर_lte_tty_device(काष्ठा tty_dev *tty_dev);

#पूर्ण_अगर /* _GDM_USB_H_ */

