<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/	
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C ADC driver inक्रमmation
 */

#अगर_अघोषित __LINUX_SOC_SAMSUNG_S3C_ADC_H
#घोषणा __LINUX_SOC_SAMSUNG_S3C_ADC_H __खाता__

काष्ठा s3c_adc_client;
काष्ठा platक्रमm_device;

बाह्य पूर्णांक s3c_adc_start(काष्ठा s3c_adc_client *client,
			 अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक nr_samples);

बाह्य पूर्णांक s3c_adc_पढ़ो(काष्ठा s3c_adc_client *client, अचिन्हित पूर्णांक ch);

बाह्य काष्ठा s3c_adc_client *
	s3c_adc_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			 व्योम (*select)(काष्ठा s3c_adc_client *client,
					अचिन्हित selected),
			 व्योम (*conv)(काष्ठा s3c_adc_client *client,
				      अचिन्हित d0, अचिन्हित d1,
				      अचिन्हित *samples_left),
			 अचिन्हित पूर्णांक is_ts);

बाह्य व्योम s3c_adc_release(काष्ठा s3c_adc_client *client);

#पूर्ण_अगर /* __LINUX_SOC_SAMSUNG_S3C_ADC_H */
