<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000	Linus Torvalds & authors
 */

/*
 * Authors:	Petr Soucek <petr@ryston.cz>
 * 		Samuel Thibault <samuel.thibault@ens-lyon.org>
 */

/* truncates a in [b,c] */
#घोषणा IDE_IN(a,b,c)   ( ((a)<(b)) ? (b) : ( (a)>(c) ? (c) : (a)) )

#घोषणा IDE_IMPLY(a,b)	((!(a)) || (b))

#घोषणा QD_TIM1_PORT		(base)
#घोषणा QD_CONFIG_PORT		(base+0x01)
#घोषणा QD_TIM2_PORT		(base+0x02)
#घोषणा QD_CONTROL_PORT		(base+0x03)

#घोषणा QD_CONFIG_IDE_BASEPORT	0x01
#घोषणा QD_CONFIG_BASEPORT	0x02
#घोषणा QD_CONFIG_ID3		0x04
#घोषणा QD_CONFIG_DISABLED	0x08
#घोषणा QD_CONFIG_QD6500	0xc0
#घोषणा QD_CONFIG_QD6580_A	0xa0
#घोषणा QD_CONFIG_QD6580_B	0x50

#घोषणा QD_CONTR_SEC_DISABLED	0x01

#घोषणा QD_ID3			((config & QD_CONFIG_ID3)!=0)

#घोषणा QD_CONFIG(hwअगर)		((hwअगर)->config_data & 0x00ff)

अटल अंतरभूत u8 QD_TIMING(ide_drive_t *drive)
अणु
	वापस (अचिन्हित दीर्घ)ide_get_drivedata(drive) & 0x00ff;
पूर्ण

अटल अंतरभूत u8 QD_TIMREG(ide_drive_t *drive)
अणु
	वापस ((अचिन्हित दीर्घ)ide_get_drivedata(drive) & 0xff00) >> 8;
पूर्ण

#घोषणा QD6500_DEF_DATA		((QD_TIM1_PORT<<8) | (QD_ID3 ? 0x0c : 0x08))
#घोषणा QD6580_DEF_DATA		((QD_TIM1_PORT<<8) | (QD_ID3 ? 0x0a : 0x00))
#घोषणा QD6580_DEF_DATA2	((QD_TIM2_PORT<<8) | (QD_ID3 ? 0x0a : 0x00))
#घोषणा QD_DEF_CONTR		(0x40 | ((control & 0x02) ? 0x9f : 0x1f))

#घोषणा QD_TESTVAL		0x19	/* safe value */

/* Drive specअगरic timing taken from DOS driver v3.7 */

अटल काष्ठा qd65xx_timing_s अणु
	s8	offset;   /* ofset from the beginning of Model Number" */
	अक्षर	model[4];    /* 4 अक्षरs from Model number, no conversion */
	s16	active;   /* active समय */
	s16	recovery; /* recovery समय */
पूर्ण qd65xx_timing [] = अणु
	अणु 30, "2040", 110, 225 पूर्ण,  /* Conner CP30204			*/
	अणु 30, "2045", 135, 225 पूर्ण,  /* Conner CP30254			*/
	अणु 30, "1040", 155, 325 पूर्ण,  /* Conner CP30104			*/
	अणु 30, "1047", 135, 265 पूर्ण,  /* Conner CP30174			*/
	अणु 30, "5344", 135, 225 पूर्ण,  /* Conner CP3544			*/
	अणु 30, "01 4", 175, 405 पूर्ण,  /* Conner CP-3104			*/
	अणु 27, "C030", 175, 375 पूर्ण,  /* Conner CP3000			*/
	अणु  8, "PL42", 110, 295 पूर्ण,  /* Quantum LP240			*/
	अणु  8, "PL21", 110, 315 पूर्ण,  /* Quantum LP120			*/
	अणु  8, "PL25", 175, 385 पूर्ण,  /* Quantum LP52			*/
	अणु  4, "PA24", 110, 285 पूर्ण,  /* WD Piranha SP4200			*/
	अणु  6, "2200", 110, 260 पूर्ण,  /* WD Caviar AC2200			*/
	अणु  6, "3204", 110, 235 पूर्ण,  /* WD Caviar AC2340			*/
	अणु  6, "1202", 110, 265 पूर्ण,  /* WD Caviar AC2120			*/
	अणु  0, "DS3-", 135, 315 पूर्ण,  /* Teac SD340			*/
	अणु  8, "KM32", 175, 355 पूर्ण,  /* Toshiba MK234			*/
	अणु  2, "53A1", 175, 355 पूर्ण,  /* Seagate ST351A			*/
	अणु  2, "4108", 175, 295 पूर्ण,  /* Seagate ST1480A			*/
	अणु  2, "1344", 175, 335 पूर्ण,  /* Seagate ST3144A			*/
	अणु  6, "7 12", 110, 225 पूर्ण,  /* Maxtor 7213A			*/
	अणु 30, "02F4", 145, 295 पूर्ण,  /* Conner 3204F			*/
	अणु  2, "1302", 175, 335 पूर्ण,  /* Seagate ST3120A			*/
	अणु  2, "2334", 145, 265 पूर्ण,  /* Seagate ST3243A			*/
	अणु  2, "2338", 145, 275 पूर्ण,  /* Seagate ST3283A			*/
	अणु  2, "3309", 145, 275 पूर्ण,  /* Seagate ST3390A			*/
	अणु  2, "5305", 145, 275 पूर्ण,  /* Seagate ST3550A			*/
	अणु  2, "4100", 175, 295 पूर्ण,  /* Seagate ST1400A			*/
	अणु  2, "4110", 175, 295 पूर्ण,  /* Seagate ST1401A			*/
	अणु  2, "6300", 135, 265 पूर्ण,  /* Seagate ST3600A			*/
	अणु  2, "5300", 135, 265 पूर्ण,  /* Seagate ST3500A			*/
	अणु  6, "7 31", 135, 225 पूर्ण,  /* Maxtor 7131 AT			*/
	अणु  6, "7 43", 115, 265 पूर्ण,  /* Maxtor 7345 AT			*/
	अणु  6, "7 42", 110, 255 पूर्ण,  /* Maxtor 7245 AT			*/
	अणु  6, "3 04", 135, 265 पूर्ण,  /* Maxtor 340 AT			*/
	अणु  6, "61 0", 135, 285 पूर्ण,  /* WD AC160				*/
	अणु  6, "1107", 135, 235 पूर्ण,  /* WD AC1170				*/
	अणु  6, "2101", 110, 220 पूर्ण,  /* WD AC1210				*/
	अणु  6, "4202", 135, 245 पूर्ण,  /* WD AC2420				*/
	अणु  6, "41 0", 175, 355 पूर्ण,  /* WD Caviar 140			*/
	अणु  6, "82 0", 175, 355 पूर्ण,  /* WD Caviar 280			*/
	अणु  8, "PL01", 175, 375 पूर्ण,  /* Quantum LP105			*/
	अणु  8, "PL25", 110, 295 पूर्ण,  /* Quantum LP525			*/
	अणु 10, "4S 2", 175, 385 पूर्ण,  /* Quantum ELS42			*/
	अणु 10, "8S 5", 175, 385 पूर्ण,  /* Quantum ELS85			*/
	अणु 10, "1S72", 175, 385 पूर्ण,  /* Quantum ELS127			*/
	अणु 10, "1S07", 175, 385 पूर्ण,  /* Quantum ELS170			*/
	अणु  8, "ZE42", 135, 295 पूर्ण,  /* Quantum EZ240			*/
	अणु  8, "ZE21", 175, 385 पूर्ण,  /* Quantum EZ127			*/
	अणु  8, "ZE58", 175, 385 पूर्ण,  /* Quantum EZ85			*/
	अणु  8, "ZE24", 175, 385 पूर्ण,  /* Quantum EZ42			*/
	अणु 27, "C036", 155, 325 पूर्ण,  /* Conner CP30064			*/
	अणु 27, "C038", 155, 325 पूर्ण,  /* Conner CP30084			*/
	अणु  6, "2205", 110, 255 पूर्ण,  /* WDC AC2250			*/
	अणु  2, " CHA", 140, 415 पूर्ण,  /* WDC AH series; WDC AH260, WDC	*/
	अणु  2, " CLA", 140, 415 पूर्ण,  /* WDC AL series: WDC AL2120, 2170,	*/
	अणु  4, "UC41", 140, 415 पूर्ण,  /* WDC CU140				*/
	अणु  6, "1207", 130, 275 पूर्ण,  /* WDC AC2170			*/
	अणु  6, "2107", 130, 275 पूर्ण,  /* WDC AC1270			*/
	अणु  6, "5204", 130, 275 पूर्ण,  /* WDC AC2540			*/
	अणु 30, "3004", 110, 235 पूर्ण,  /* Conner CP30340			*/
	अणु 30, "0345", 135, 255 पूर्ण,  /* Conner CP30544			*/
	अणु 12, "12A3", 175, 320 पूर्ण,  /* MAXTOR LXT-213A			*/
	अणु 12, "43A0", 145, 240 पूर्ण,  /* MAXTOR LXT-340A			*/
	अणु  6, "7 21", 180, 290 पूर्ण,  /* Maxtor 7120 AT			*/
	अणु  6, "7 71", 135, 240 पूर्ण,  /* Maxtor 7170 AT			*/
	अणु 12, "45\0000", 110, 205 पूर्ण,   /* MAXTOR MXT-540		*/
	अणु  8, "PL11", 180, 290 पूर्ण,  /* QUANTUM LP110A			*/
	अणु  8, "OG21", 150, 275 पूर्ण,  /* QUANTUM GO120			*/
	अणु 12, "42A5", 175, 320 पूर्ण,  /* MAXTOR LXT-245A			*/
	अणु  2, "2309", 175, 295 पूर्ण,  /* ST3290A				*/
	अणु  2, "3358", 180, 310 पूर्ण,  /* ST3385A				*/
	अणु  2, "6355", 180, 310 पूर्ण,  /* ST3655A				*/
	अणु  2, "1900", 175, 270 पूर्ण,  /* ST9100A				*/
	अणु  2, "1954", 175, 270 पूर्ण,  /* ST9145A				*/
	अणु  2, "1909", 175, 270 पूर्ण,  /* ST9190AG				*/
	अणु  2, "2953", 175, 270 पूर्ण,  /* ST9235A				*/
	अणु  2, "1359", 175, 270 पूर्ण,  /* ST3195A				*/
	अणु 24, "3R11", 175, 290 पूर्ण,  /* ALPS ELECTRIC Co.,LTD, DR311C	*/
	अणु  0, "2M26", 175, 215 पूर्ण,  /* M262XT-0Ah			*/
	अणु  4, "2253", 175, 300 पूर्ण,  /* HP C2235A				*/
	अणु  4, "-32A", 145, 245 पूर्ण,  /* H3133-A2				*/
	अणु 30, "0326", 150, 270 पूर्ण,  /* Samsung Electronics 120MB		*/
	अणु 30, "3044", 110, 195 पूर्ण,  /* Conner CFA340A			*/
	अणु 30, "43A0", 110, 195 पूर्ण,  /* Conner CFA340A			*/
	अणु -1, "    ", 175, 415 पूर्ण   /* unknown disk name			*/
पूर्ण;
