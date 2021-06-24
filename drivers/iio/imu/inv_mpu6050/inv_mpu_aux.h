<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 TDK-InvenSense, Inc.
 */

#अगर_अघोषित INV_MPU_AUX_H_
#घोषणा INV_MPU_AUX_H_

#समावेश "inv_mpu_iio.h"

पूर्णांक inv_mpu_aux_init(स्थिर काष्ठा inv_mpu6050_state *st);

पूर्णांक inv_mpu_aux_पढ़ो(स्थिर काष्ठा inv_mpu6050_state *st, uपूर्णांक8_t addr,
		     uपूर्णांक8_t reg, uपूर्णांक8_t *val, माप_प्रकार size);

पूर्णांक inv_mpu_aux_ग_लिखो(स्थिर काष्ठा inv_mpu6050_state *st, uपूर्णांक8_t addr,
		      uपूर्णांक8_t reg, uपूर्णांक8_t val);

#पूर्ण_अगर		/* INV_MPU_AUX_H_ */
