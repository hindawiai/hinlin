<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_HPET_H
#घोषणा _ASM_X86_HPET_H

#समावेश <linux/msi.h>

#अगर_घोषित CONFIG_HPET_TIMER

#घोषणा HPET_MMAP_SIZE		1024

#घोषणा HPET_ID			0x000
#घोषणा HPET_PERIOD		0x004
#घोषणा HPET_CFG		0x010
#घोषणा HPET_STATUS		0x020
#घोषणा HPET_COUNTER		0x0f0

#घोषणा HPET_Tn_CFG(n)		(0x100 + 0x20 * n)
#घोषणा HPET_Tn_CMP(n)		(0x108 + 0x20 * n)
#घोषणा HPET_Tn_ROUTE(n)	(0x110 + 0x20 * n)

#घोषणा HPET_T0_CFG		0x100
#घोषणा HPET_T0_CMP		0x108
#घोषणा HPET_T0_ROUTE		0x110
#घोषणा HPET_T1_CFG		0x120
#घोषणा HPET_T1_CMP		0x128
#घोषणा HPET_T1_ROUTE		0x130
#घोषणा HPET_T2_CFG		0x140
#घोषणा HPET_T2_CMP		0x148
#घोषणा HPET_T2_ROUTE		0x150

#घोषणा HPET_ID_REV		0x000000ff
#घोषणा HPET_ID_NUMBER		0x00001f00
#घोषणा HPET_ID_64BIT		0x00002000
#घोषणा HPET_ID_LEGSUP		0x00008000
#घोषणा HPET_ID_VENDOR		0xffff0000
#घोषणा	HPET_ID_NUMBER_SHIFT	8
#घोषणा HPET_ID_VENDOR_SHIFT	16

#घोषणा HPET_CFG_ENABLE		0x001
#घोषणा HPET_CFG_LEGACY		0x002
#घोषणा	HPET_LEGACY_8254	2
#घोषणा	HPET_LEGACY_RTC		8

#घोषणा HPET_TN_LEVEL		0x0002
#घोषणा HPET_TN_ENABLE		0x0004
#घोषणा HPET_TN_PERIODIC	0x0008
#घोषणा HPET_TN_PERIODIC_CAP	0x0010
#घोषणा HPET_TN_64BIT_CAP	0x0020
#घोषणा HPET_TN_SETVAL		0x0040
#घोषणा HPET_TN_32BIT		0x0100
#घोषणा HPET_TN_ROUTE		0x3e00
#घोषणा HPET_TN_FSB		0x4000
#घोषणा HPET_TN_FSB_CAP		0x8000
#घोषणा HPET_TN_ROUTE_SHIFT	9

/* Max HPET Period is 10^8 femto sec as in HPET spec */
#घोषणा HPET_MAX_PERIOD		100000000UL
/*
 * Min HPET period is 10^5 femto sec just क्रम safety. If it is less than this,
 * then 32 bit HPET counter wrapsaround in less than 0.5 sec.
 */
#घोषणा HPET_MIN_PERIOD		100000UL

/* hpet memory map physical address */
बाह्य अचिन्हित दीर्घ hpet_address;
बाह्य अचिन्हित दीर्घ क्रमce_hpet_address;
बाह्य bool boot_hpet_disable;
बाह्य u8 hpet_blockid;
बाह्य bool hpet_क्रमce_user;
बाह्य bool hpet_msi_disable;
बाह्य पूर्णांक is_hpet_enabled(व्योम);
बाह्य पूर्णांक hpet_enable(व्योम);
बाह्य व्योम hpet_disable(व्योम);
बाह्य अचिन्हित पूर्णांक hpet_पढ़ोl(अचिन्हित पूर्णांक a);
बाह्य व्योम क्रमce_hpet_resume(व्योम);

#अगर_घोषित CONFIG_HPET_EMULATE_RTC

#समावेश <linux/पूर्णांकerrupt.h>

प्रकार irqवापस_t (*rtc_irq_handler)(पूर्णांक पूर्णांकerrupt, व्योम *cookie);
बाह्य पूर्णांक hpet_mask_rtc_irq_bit(अचिन्हित दीर्घ bit_mask);
बाह्य पूर्णांक hpet_set_rtc_irq_bit(अचिन्हित दीर्घ bit_mask);
बाह्य पूर्णांक hpet_set_alarm_समय(अचिन्हित अक्षर hrs, अचिन्हित अक्षर min,
			       अचिन्हित अक्षर sec);
बाह्य पूर्णांक hpet_set_periodic_freq(अचिन्हित दीर्घ freq);
बाह्य पूर्णांक hpet_rtc_dropped_irq(व्योम);
बाह्य पूर्णांक hpet_rtc_समयr_init(व्योम);
बाह्य irqवापस_t hpet_rtc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
बाह्य पूर्णांक hpet_रेजिस्टर_irq_handler(rtc_irq_handler handler);
बाह्य व्योम hpet_unरेजिस्टर_irq_handler(rtc_irq_handler handler);

#पूर्ण_अगर /* CONFIG_HPET_EMULATE_RTC */

#अन्यथा /* CONFIG_HPET_TIMER */

अटल अंतरभूत पूर्णांक hpet_enable(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक is_hpet_enabled(व्योम) अणु वापस 0; पूर्ण
#घोषणा hpet_पढ़ोl(a) 0
#घोषणा शेष_setup_hpet_msi	शून्य

#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_X86_HPET_H */
