<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-ep93xx/include/mach/ts72xx.h
 */

/*
 * TS72xx memory map:
 *
 * virt		phys		size
 * febff000	22000000	4K	model number रेजिस्टर (bits 0-2)
 * febfe000	22400000	4K	options रेजिस्टर
 * febfd000	22800000	4K	options रेजिस्टर #2
 * febfc000     23400000        4K      CPLD version रेजिस्टर
 */

#अगर_अघोषित __TS72XX_H_
#घोषणा __TS72XX_H_

#घोषणा TS72XX_MODEL_PHYS_BASE		0x22000000
#घोषणा TS72XX_MODEL_VIRT_BASE		IOMEM(0xfebff000)
#घोषणा TS72XX_MODEL_SIZE		0x00001000

#घोषणा TS72XX_MODEL_TS7200		0x00
#घोषणा TS72XX_MODEL_TS7250		0x01
#घोषणा TS72XX_MODEL_TS7260		0x02
#घोषणा TS72XX_MODEL_TS7300		0x03
#घोषणा TS72XX_MODEL_TS7400		0x04
#घोषणा TS72XX_MODEL_MASK		0x07


#घोषणा TS72XX_OPTIONS_PHYS_BASE	0x22400000
#घोषणा TS72XX_OPTIONS_VIRT_BASE	IOMEM(0xfebfe000)
#घोषणा TS72XX_OPTIONS_SIZE		0x00001000

#घोषणा TS72XX_OPTIONS_COM2_RS485	0x02
#घोषणा TS72XX_OPTIONS_MAX197		0x01


#घोषणा TS72XX_OPTIONS2_PHYS_BASE	0x22800000
#घोषणा TS72XX_OPTIONS2_VIRT_BASE	IOMEM(0xfebfd000)
#घोषणा TS72XX_OPTIONS2_SIZE		0x00001000

#घोषणा TS72XX_OPTIONS2_TS9420		0x04
#घोषणा TS72XX_OPTIONS2_TS9420_BOOT	0x02

#घोषणा TS72XX_CPLDVER_PHYS_BASE	0x23400000
#घोषणा TS72XX_CPLDVER_VIRT_BASE	IOMEM(0xfebfc000)
#घोषणा TS72XX_CPLDVER_SIZE		0x00001000

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत पूर्णांक ts72xx_model(व्योम)
अणु
	वापस __raw_पढ़ोb(TS72XX_MODEL_VIRT_BASE) & TS72XX_MODEL_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक board_is_ts7200(व्योम)
अणु
	वापस ts72xx_model() == TS72XX_MODEL_TS7200;
पूर्ण

अटल अंतरभूत पूर्णांक board_is_ts7250(व्योम)
अणु
	वापस ts72xx_model() == TS72XX_MODEL_TS7250;
पूर्ण

अटल अंतरभूत पूर्णांक board_is_ts7260(व्योम)
अणु
	वापस ts72xx_model() == TS72XX_MODEL_TS7260;
पूर्ण

अटल अंतरभूत पूर्णांक board_is_ts7300(व्योम)
अणु
	वापस ts72xx_model()  == TS72XX_MODEL_TS7300;
पूर्ण

अटल अंतरभूत पूर्णांक board_is_ts7400(व्योम)
अणु
	वापस ts72xx_model() == TS72XX_MODEL_TS7400;
पूर्ण

अटल अंतरभूत पूर्णांक is_max197_installed(व्योम)
अणु
	वापस !!(__raw_पढ़ोb(TS72XX_OPTIONS_VIRT_BASE) &
					TS72XX_OPTIONS_MAX197);
पूर्ण

अटल अंतरभूत पूर्णांक is_ts9420_installed(व्योम)
अणु
	वापस !!(__raw_पढ़ोb(TS72XX_OPTIONS2_VIRT_BASE) &
					TS72XX_OPTIONS2_TS9420);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __TS72XX_H_ */
