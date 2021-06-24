<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_MMP2_H
#घोषणा __ASM_MACH_MMP2_H

#समावेश <linux/platक्रमm_data/pxa_sdhci.h>

बाह्य व्योम mmp2_समयr_init(व्योम);
बाह्य व्योम __init mmp2_init_icu(व्योम);
बाह्य व्योम __init mmp2_init_irq(व्योम);
बाह्य व्योम mmp2_clear_pmic_पूर्णांक(व्योम);

#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/platक्रमm_data/dma-mmp_tdma.h>

#समावेश "devices.h"

बाह्य काष्ठा pxa_device_desc mmp2_device_uart1;
बाह्य काष्ठा pxa_device_desc mmp2_device_uart2;
बाह्य काष्ठा pxa_device_desc mmp2_device_uart3;
बाह्य काष्ठा pxa_device_desc mmp2_device_uart4;
बाह्य काष्ठा pxa_device_desc mmp2_device_twsi1;
बाह्य काष्ठा pxa_device_desc mmp2_device_twsi2;
बाह्य काष्ठा pxa_device_desc mmp2_device_twsi3;
बाह्य काष्ठा pxa_device_desc mmp2_device_twsi4;
बाह्य काष्ठा pxa_device_desc mmp2_device_twsi5;
बाह्य काष्ठा pxa_device_desc mmp2_device_twsi6;
बाह्य काष्ठा pxa_device_desc mmp2_device_sdh0;
बाह्य काष्ठा pxa_device_desc mmp2_device_sdh1;
बाह्य काष्ठा pxa_device_desc mmp2_device_sdh2;
बाह्य काष्ठा pxa_device_desc mmp2_device_sdh3;
बाह्य काष्ठा pxa_device_desc mmp2_device_asram;
बाह्य काष्ठा pxa_device_desc mmp2_device_isram;

बाह्य काष्ठा platक्रमm_device mmp2_device_gpio;

अटल अंतरभूत पूर्णांक mmp2_add_uart(पूर्णांक id)
अणु
	काष्ठा pxa_device_desc *d = शून्य;

	चयन (id) अणु
	हाल 1: d = &mmp2_device_uart1; अवरोध;
	हाल 2: d = &mmp2_device_uart2; अवरोध;
	हाल 3: d = &mmp2_device_uart3; अवरोध;
	हाल 4: d = &mmp2_device_uart4; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस pxa_रेजिस्टर_device(d, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक mmp2_add_twsi(पूर्णांक id, काष्ठा i2c_pxa_platक्रमm_data *data,
				  काष्ठा i2c_board_info *info, अचिन्हित size)
अणु
	काष्ठा pxa_device_desc *d = शून्य;
	पूर्णांक ret;

	चयन (id) अणु
	हाल 1: d = &mmp2_device_twsi1; अवरोध;
	हाल 2: d = &mmp2_device_twsi2; अवरोध;
	हाल 3: d = &mmp2_device_twsi3; अवरोध;
	हाल 4: d = &mmp2_device_twsi4; अवरोध;
	हाल 5: d = &mmp2_device_twsi5; अवरोध;
	हाल 6: d = &mmp2_device_twsi6; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = i2c_रेजिस्टर_board_info(id - 1, info, size);
	अगर (ret)
		वापस ret;

	वापस pxa_रेजिस्टर_device(d, data, माप(*data));
पूर्ण

अटल अंतरभूत पूर्णांक mmp2_add_sdhost(पूर्णांक id, काष्ठा sdhci_pxa_platdata *data)
अणु
	काष्ठा pxa_device_desc *d = शून्य;

	चयन (id) अणु
	हाल 0: d = &mmp2_device_sdh0; अवरोध;
	हाल 1: d = &mmp2_device_sdh1; अवरोध;
	हाल 2: d = &mmp2_device_sdh2; अवरोध;
	हाल 3: d = &mmp2_device_sdh3; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस pxa_रेजिस्टर_device(d, data, माप(*data));
पूर्ण

अटल अंतरभूत पूर्णांक mmp2_add_asram(काष्ठा sram_platdata *data)
अणु
	वापस pxa_रेजिस्टर_device(&mmp2_device_asram, data, माप(*data));
पूर्ण

अटल अंतरभूत पूर्णांक mmp2_add_isram(काष्ठा sram_platdata *data)
अणु
	वापस pxa_रेजिस्टर_device(&mmp2_device_isram, data, माप(*data));
पूर्ण

#पूर्ण_अगर /* __ASM_MACH_MMP2_H */

