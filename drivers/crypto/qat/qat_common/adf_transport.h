<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_TRANSPORT_H
#घोषणा ADF_TRANSPORT_H

#समावेश "adf_accel_devices.h"

काष्ठा adf_etr_ring_data;

प्रकार व्योम (*adf_callback_fn)(व्योम *resp_msg);

पूर्णांक adf_create_ring(काष्ठा adf_accel_dev *accel_dev, स्थिर अक्षर *section,
		    u32 bank_num, u32 num_mgs, u32 msg_size,
		    स्थिर अक्षर *ring_name, adf_callback_fn callback,
		    पूर्णांक poll_mode, काष्ठा adf_etr_ring_data **ring_ptr);

पूर्णांक adf_send_message(काष्ठा adf_etr_ring_data *ring, u32 *msg);
व्योम adf_हटाओ_ring(काष्ठा adf_etr_ring_data *ring);
#पूर्ण_अगर
