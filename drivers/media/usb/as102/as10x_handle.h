<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 */
#अगर_अघोषित _AS10X_HANDLE_H
#घोषणा _AS10X_HANDLE_H
काष्ठा as10x_bus_adapter_t;
काष्ठा as102_dev_t;

#समावेश "as10x_cmd.h"

/* values क्रम "mode" field */
#घोषणा REGMODE8	8
#घोषणा REGMODE16	16
#घोषणा REGMODE32	32

काष्ठा as102_priv_ops_t अणु
	पूर्णांक (*upload_fw_pkt)(काष्ठा as10x_bus_adapter_t *bus_adap,
			      अचिन्हित अक्षर *buf, पूर्णांक buflen, पूर्णांक swap32);

	पूर्णांक (*send_cmd)(काष्ठा as10x_bus_adapter_t *bus_adap,
			 अचिन्हित अक्षर *buf, पूर्णांक buflen);

	पूर्णांक (*xfer_cmd)(काष्ठा as10x_bus_adapter_t *bus_adap,
			 अचिन्हित अक्षर *send_buf, पूर्णांक send_buf_len,
			 अचिन्हित अक्षर *recv_buf, पूर्णांक recv_buf_len);

	पूर्णांक (*start_stream)(काष्ठा as102_dev_t *dev);
	व्योम (*stop_stream)(काष्ठा as102_dev_t *dev);

	पूर्णांक (*reset_target)(काष्ठा as10x_bus_adapter_t *bus_adap);

	पूर्णांक (*पढ़ो_ग_लिखो)(काष्ठा as10x_bus_adapter_t *bus_adap, uपूर्णांक8_t mode,
			  uपूर्णांक32_t rd_addr, uपूर्णांक16_t rd_len,
			  uपूर्णांक32_t wr_addr, uपूर्णांक16_t wr_len);

	पूर्णांक (*as102_पढ़ो_ep2)(काष्ठा as10x_bus_adapter_t *bus_adap,
			       अचिन्हित अक्षर *recv_buf,
			       पूर्णांक recv_buf_len);
पूर्ण;
#पूर्ण_अगर
