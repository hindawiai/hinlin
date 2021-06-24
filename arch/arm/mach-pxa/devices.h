<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा PDMA_FILTER_PARAM(_prio, _requestor) (&(काष्ठा pxad_param) अणु \
	.prio = PXAD_PRIO_##_prio, .drcmr = _requestor पूर्ण)
काष्ठा mmp_dma_platdata;

बाह्य काष्ठा platक्रमm_device pxa_device_pmu;
बाह्य काष्ठा platक्रमm_device pxa_device_mci;
बाह्य काष्ठा platक्रमm_device pxa3xx_device_mci2;
बाह्य काष्ठा platक्रमm_device pxa3xx_device_mci3;
बाह्य काष्ठा platक्रमm_device pxa25x_device_udc;
बाह्य काष्ठा platक्रमm_device pxa27x_device_udc;
बाह्य काष्ठा platक्रमm_device pxa3xx_device_u2d;
बाह्य काष्ठा platक्रमm_device pxa_device_fb;
बाह्य काष्ठा platक्रमm_device pxa_device_ffuart;
बाह्य काष्ठा platक्रमm_device pxa_device_btuart;
बाह्य काष्ठा platक्रमm_device pxa_device_stuart;
बाह्य काष्ठा platक्रमm_device pxa_device_hwuart;
बाह्य काष्ठा platक्रमm_device pxa_device_i2c;
बाह्य काष्ठा platक्रमm_device pxa_device_i2s;
बाह्य काष्ठा platक्रमm_device pxa_device_ficp;
बाह्य काष्ठा platक्रमm_device sa1100_device_rtc;
बाह्य काष्ठा platक्रमm_device pxa_device_rtc;
बाह्य काष्ठा platक्रमm_device pxa_device_ac97;

बाह्य काष्ठा platक्रमm_device pxa27x_device_i2c_घातer;
बाह्य काष्ठा platक्रमm_device pxa27x_device_ohci;
बाह्य काष्ठा platक्रमm_device pxa27x_device_keypad;

बाह्य काष्ठा platक्रमm_device pxa25x_device_ssp;
बाह्य काष्ठा platक्रमm_device pxa25x_device_nssp;
बाह्य काष्ठा platक्रमm_device pxa25x_device_assp;
बाह्य काष्ठा platक्रमm_device pxa27x_device_ssp1;
बाह्य काष्ठा platक्रमm_device pxa27x_device_ssp2;
बाह्य काष्ठा platक्रमm_device pxa27x_device_ssp3;
बाह्य काष्ठा platक्रमm_device pxa3xx_device_ssp1;
बाह्य काष्ठा platक्रमm_device pxa3xx_device_ssp2;
बाह्य काष्ठा platक्रमm_device pxa3xx_device_ssp3;
बाह्य काष्ठा platक्रमm_device pxa3xx_device_ssp4;

बाह्य काष्ठा platक्रमm_device pxa25x_device_pwm0;
बाह्य काष्ठा platक्रमm_device pxa25x_device_pwm1;
बाह्य काष्ठा platक्रमm_device pxa27x_device_pwm0;
बाह्य काष्ठा platक्रमm_device pxa27x_device_pwm1;

बाह्य काष्ठा platक्रमm_device pxa3xx_device_nand;
बाह्य काष्ठा platक्रमm_device pxa3xx_device_i2c_घातer;

बाह्य काष्ठा platक्रमm_device pxa3xx_device_gcu;

बाह्य काष्ठा platक्रमm_device pxa_device_asoc_platक्रमm;
बाह्य काष्ठा platक्रमm_device pxa_device_asoc_ssp1;
बाह्य काष्ठा platक्रमm_device pxa_device_asoc_ssp2;
बाह्य काष्ठा platक्रमm_device pxa_device_asoc_ssp3;
बाह्य काष्ठा platक्रमm_device pxa_device_asoc_ssp4;

बाह्य काष्ठा platक्रमm_device pxa25x_device_gpio;
बाह्य काष्ठा platक्रमm_device pxa27x_device_gpio;
बाह्य काष्ठा platक्रमm_device pxa3xx_device_gpio;
बाह्य काष्ठा platक्रमm_device pxa93x_device_gpio;

व्योम __init pxa_रेजिस्टर_device(काष्ठा platक्रमm_device *dev, व्योम *data);
व्योम __init pxa2xx_set_dmac_info(काष्ठा mmp_dma_platdata *dma_pdata);

काष्ठा i2c_pxa_platक्रमm_data;
बाह्य व्योम pxa_set_i2c_info(काष्ठा i2c_pxa_platक्रमm_data *info);
#अगर_घोषित CONFIG_PXA27x
बाह्य व्योम pxa27x_set_i2c_घातer_info(काष्ठा i2c_pxa_platक्रमm_data *info);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PXA3xx
बाह्य व्योम pxa3xx_set_i2c_घातer_info(काष्ठा i2c_pxa_platक्रमm_data *info);
#पूर्ण_अगर
