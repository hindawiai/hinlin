<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CPU_SH4_RTC_H
#घोषणा __ASM_SH_CPU_SH4_RTC_H

#अगर defined(CONFIG_CPU_SUBTYPE_SH7722) || defined(CONFIG_CPU_SUBTYPE_SH7723)
#घोषणा rtc_reg_size		माप(u16)
#अन्यथा
#घोषणा rtc_reg_size		माप(u32)
#पूर्ण_अगर

#घोषणा RTC_BIT_INVERTED	0x40	/* bug on SH7750, SH7750S */
#घोषणा RTC_DEF_CAPABILITIES	RTC_CAP_4_DIGIT_YEAR

#पूर्ण_अगर /* __ASM_SH_CPU_SH4_RTC_H */
