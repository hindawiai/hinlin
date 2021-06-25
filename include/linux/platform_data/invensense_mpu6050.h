<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
* Copyright (C) 2012 Invensense, Inc.
*/

#अगर_अघोषित __INV_MPU6050_PLATFORM_H_
#घोषणा __INV_MPU6050_PLATFORM_H_

/**
 * काष्ठा inv_mpu6050_platक्रमm_data - Platक्रमm data क्रम the mpu driver
 * @orientation:	Orientation matrix of the chip (deprecated in favor of
 *			mounting matrix retrieved from device-tree)
 *
 * Contains platक्रमm specअगरic inक्रमmation on how to configure the MPU6050 to
 * work on this platक्रमm.  The orientation matrices are 3x3 rotation matrices
 * that are applied to the data to rotate from the mounting orientation to the
 * platक्रमm orientation.  The values must be one of 0, 1, or -1 and each row and
 * column should have exactly 1 non-zero value.
 *
 * Deprecated in favor of mounting matrix retrieved from device-tree.
 */
काष्ठा inv_mpu6050_platक्रमm_data अणु
	__s8 orientation[9];
पूर्ण;

#पूर्ण_अगर
