<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - I2C Controller core functions
 */

#अगर_अघोषित __ASM_ARCH_IIC_CORE_H
#घोषणा __ASM_ARCH_IIC_CORE_H __खाता__

/* These functions are only क्रम use with the core support code, such as
 * the cpu specअगरic initialisation code
 */

/* re-define device name depending on support. */
अटल अंतरभूत व्योम s3c_i2c0_setname(अक्षर *name)
अणु
	/* currently this device is always compiled in */
	s3c_device_i2c0.name = name;
पूर्ण

अटल अंतरभूत व्योम s3c_i2c1_setname(अक्षर *name)
अणु
#अगर_घोषित CONFIG_S3C_DEV_I2C1
	s3c_device_i2c1.name = name;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम s3c_i2c2_setname(अक्षर *name)
अणु
#अगर_घोषित CONFIG_S3C_DEV_I2C2
	s3c_device_i2c2.name = name;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __ASM_ARCH_IIC_H */
