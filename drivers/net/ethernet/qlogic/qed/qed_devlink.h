<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Marvell/Qlogic FastLinQ NIC driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 */
#अगर_अघोषित _QED_DEVLINK_H
#घोषणा _QED_DEVLINK_H

#समावेश <linux/qed/qed_अगर.h>
#समावेश <net/devlink.h>

काष्ठा devlink *qed_devlink_रेजिस्टर(काष्ठा qed_dev *cdev);
व्योम qed_devlink_unरेजिस्टर(काष्ठा devlink *devlink);

व्योम qed_fw_reporters_create(काष्ठा devlink *devlink);
व्योम qed_fw_reporters_destroy(काष्ठा devlink *devlink);

पूर्णांक qed_report_fatal_error(काष्ठा devlink *dl, क्रमागत qed_hw_err_type err_type);

#पूर्ण_अगर
