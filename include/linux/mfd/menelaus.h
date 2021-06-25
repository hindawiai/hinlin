<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Functions to access Menelaus घातer management chip
 */

#अगर_अघोषित __ASM_ARCH_MENELAUS_H
#घोषणा __ASM_ARCH_MENELAUS_H

काष्ठा device;

काष्ठा menelaus_platक्रमm_data अणु
	पूर्णांक (* late_init)(काष्ठा device *dev);
पूर्ण;

बाह्य पूर्णांक menelaus_रेजिस्टर_mmc_callback(व्योम (*callback)(व्योम *data, u8 card_mask),
					  व्योम *data);
बाह्य व्योम menelaus_unरेजिस्टर_mmc_callback(व्योम);
बाह्य पूर्णांक menelaus_set_mmc_खोलोdrain(पूर्णांक slot, पूर्णांक enable);
बाह्य पूर्णांक menelaus_set_mmc_slot(पूर्णांक slot, पूर्णांक enable, पूर्णांक घातer, पूर्णांक cd_on);

बाह्य पूर्णांक menelaus_set_vmem(अचिन्हित पूर्णांक mV);
बाह्य पूर्णांक menelaus_set_vio(अचिन्हित पूर्णांक mV);
बाह्य पूर्णांक menelaus_set_vmmc(अचिन्हित पूर्णांक mV);
बाह्य पूर्णांक menelaus_set_vaux(अचिन्हित पूर्णांक mV);
बाह्य पूर्णांक menelaus_set_vdcdc(पूर्णांक dcdc, अचिन्हित पूर्णांक mV);
बाह्य पूर्णांक menelaus_set_slot_sel(पूर्णांक enable);
बाह्य पूर्णांक menelaus_get_slot_pin_states(व्योम);
बाह्य पूर्णांक menelaus_set_vcore_hw(अचिन्हित पूर्णांक roof_mV, अचिन्हित पूर्णांक न्यूनमान_mV);

#घोषणा EN_VPLL_SLEEP	(1 << 7)
#घोषणा EN_VMMC_SLEEP	(1 << 6)
#घोषणा EN_VAUX_SLEEP	(1 << 5)
#घोषणा EN_VIO_SLEEP	(1 << 4)
#घोषणा EN_VMEM_SLEEP	(1 << 3)
#घोषणा EN_DC3_SLEEP	(1 << 2)
#घोषणा EN_DC2_SLEEP	(1 << 1)
#घोषणा EN_VC_SLEEP	(1 << 0)

बाह्य पूर्णांक menelaus_set_regulator_sleep(पूर्णांक enable, u32 val);

#पूर्ण_अगर
