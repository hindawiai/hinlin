<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Useful PROM locations */

#अगर_अघोषित SUN3X_PROM_H
#घोषणा SUN3X_PROM_H

बाह्य व्योम (*sun3x_अक्षर_दो)(पूर्णांक);
बाह्य पूर्णांक (*sun3x_अक्षर_लो)(व्योम);
बाह्य पूर्णांक (*sun3x_mayget)(व्योम);
बाह्य पूर्णांक (*sun3x_mayput)(पूर्णांक);

व्योम sun3x_reboot(व्योम);
व्योम sun3x_पात(व्योम);
व्योम sun3x_prom_init(व्योम);
अचिन्हित दीर्घ sun3x_prom_ptov(अचिन्हित दीर्घ pa, अचिन्हित दीर्घ size);

/* पूर्णांकeresting hardware locations */
#घोषणा SUN3X_IOMMU       0x60000000
#घोषणा SUN3X_ENAREG      0x61000000
#घोषणा SUN3X_INTREG      0x61001400
#घोषणा SUN3X_DIAGREG     0x61001800
#घोषणा SUN3X_ZS1         0x62000000
#घोषणा SUN3X_ZS2         0x62002000
#घोषणा SUN3X_LANCE       0x65002000
#घोषणा SUN3X_EEPROM      0x64000000
#घोषणा SUN3X_IDPROM      0x640007d8
#घोषणा SUN3X_VIDEO_BASE  0x50400000
#घोषणा SUN3X_VIDEO_REGS  0x50300000

/* vector table */
#घोषणा SUN3X_PROM_BASE   0xfefe0000
#घोषणा SUN3X_P_GETCHAR   (SUN3X_PROM_BASE + 20)
#घोषणा SUN3X_P_PUTCHAR   (SUN3X_PROM_BASE + 24)
#घोषणा SUN3X_P_MAYGET    (SUN3X_PROM_BASE + 28)
#घोषणा SUN3X_P_MAYPUT    (SUN3X_PROM_BASE + 32)
#घोषणा SUN3X_P_REBOOT    (SUN3X_PROM_BASE + 96)
#घोषणा SUN3X_P_SETLEDS   (SUN3X_PROM_BASE + 144)
#घोषणा SUN3X_P_ABORT     (SUN3X_PROM_BASE + 152)

/* mapped area */
#घोषणा SUN3X_MAP_START   0xfee00000
#घोषणा SUN3X_MAP_END     0xff000000

#पूर्ण_अगर
