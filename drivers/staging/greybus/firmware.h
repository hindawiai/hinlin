<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus Firmware Management Header
 *
 * Copyright 2016 Google Inc.
 * Copyright 2016 Linaro Ltd.
 */

#अगर_अघोषित __FIRMWARE_H
#घोषणा __FIRMWARE_H

#समावेश <linux/greybus.h>

#घोषणा FW_NAME_PREFIX	"gmp_"

/*
 * Length of the string in क्रमmat: "FW_NAME_PREFIX""%08x_%08x_%08x_%08x_%s.tftf"
 *                                  (3 + 1 + 4 * (8 + 1) + 10 + 1 + 4 + 1)
 */
#घोषणा FW_NAME_SIZE		56

/* Firmware Management Protocol specअगरic functions */
पूर्णांक fw_mgmt_init(व्योम);
व्योम fw_mgmt_निकास(व्योम);
काष्ठा gb_connection *to_fw_mgmt_connection(काष्ठा device *dev);
पूर्णांक gb_fw_mgmt_request_handler(काष्ठा gb_operation *op);
पूर्णांक gb_fw_mgmt_connection_init(काष्ठा gb_connection *connection);
व्योम gb_fw_mgmt_connection_निकास(काष्ठा gb_connection *connection);

/* Firmware Download Protocol specअगरic functions */
पूर्णांक gb_fw_करोwnload_request_handler(काष्ठा gb_operation *op);
पूर्णांक gb_fw_करोwnload_connection_init(काष्ठा gb_connection *connection);
व्योम gb_fw_करोwnload_connection_निकास(काष्ठा gb_connection *connection);

/* CAP Protocol specअगरic functions */
पूर्णांक cap_init(व्योम);
व्योम cap_निकास(व्योम);
पूर्णांक gb_cap_connection_init(काष्ठा gb_connection *connection);
व्योम gb_cap_connection_निकास(काष्ठा gb_connection *connection);

#पूर्ण_अगर /* __FIRMWARE_H */
