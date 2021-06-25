<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Samsung ADC Controller core functions
 */

#अगर_अघोषित __ASM_PLAT_ADC_CORE_H
#घोषणा __ASM_PLAT_ADC_CORE_H __खाता__

/* These functions are only क्रम use with the core support code, such as
 * the cpu specअगरic initialisation code
 */

/* re-define device name depending on support. */
अटल अंतरभूत व्योम s3c_adc_setname(अक्षर *name)
अणु
#अगर defined(CONFIG_SAMSUNG_DEV_ADC) || defined(CONFIG_PLAT_S3C24XX)
	s3c_device_adc.name = name;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __ASM_PLAT_ADC_CORE_H */
