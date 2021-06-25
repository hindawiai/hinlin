<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Include file क्रम the पूर्णांकerface to an APM BIOS
 * Copyright 1994-2001 Stephen Rothwell (sfr@canb.auug.org.au)
 */
#अगर_अघोषित _LINUX_APM_H
#घोषणा _LINUX_APM_H

#समावेश <uapi/linux/apm_मूलप्रण.स>


#घोषणा APM_CS		(GDT_ENTRY_APMBIOS_BASE * 8)
#घोषणा APM_CS_16	(APM_CS + 8)
#घोषणा APM_DS		(APM_CS_16 + 8)

/* Results of APM Installation Check */
#घोषणा APM_16_BIT_SUPPORT	0x0001
#घोषणा APM_32_BIT_SUPPORT	0x0002
#घोषणा APM_IDLE_SLOWS_CLOCK	0x0004
#घोषणा APM_BIOS_DISABLED      	0x0008
#घोषणा APM_BIOS_DISENGAGED     0x0010

/*
 * Data क्रम APM that is persistent across module unload/load
 */
काष्ठा apm_info अणु
	काष्ठा apm_bios_info	bios;
	अचिन्हित लघु		connection_version;
	पूर्णांक			get_घातer_status_broken;
	पूर्णांक			get_घातer_status_swabinminutes;
	पूर्णांक			allow_पूर्णांकs;
	पूर्णांक			क्रमbid_idle;
	पूर्णांक			realmode_घातer_off;
	पूर्णांक			disabled;
पूर्ण;

/*
 * The APM function codes
 */
#घोषणा	APM_FUNC_INST_CHECK	0x5300
#घोषणा	APM_FUNC_REAL_CONN	0x5301
#घोषणा	APM_FUNC_16BIT_CONN	0x5302
#घोषणा	APM_FUNC_32BIT_CONN	0x5303
#घोषणा	APM_FUNC_DISCONN	0x5304
#घोषणा	APM_FUNC_IDLE		0x5305
#घोषणा	APM_FUNC_BUSY		0x5306
#घोषणा	APM_FUNC_SET_STATE	0x5307
#घोषणा	APM_FUNC_ENABLE_PM	0x5308
#घोषणा	APM_FUNC_RESTORE_BIOS	0x5309
#घोषणा	APM_FUNC_GET_STATUS	0x530a
#घोषणा	APM_FUNC_GET_EVENT	0x530b
#घोषणा	APM_FUNC_GET_STATE	0x530c
#घोषणा	APM_FUNC_ENABLE_DEV_PM	0x530d
#घोषणा	APM_FUNC_VERSION	0x530e
#घोषणा	APM_FUNC_ENGAGE_PM	0x530f
#घोषणा	APM_FUNC_GET_CAP	0x5310
#घोषणा	APM_FUNC_RESUME_TIMER	0x5311
#घोषणा	APM_FUNC_RESUME_ON_RING	0x5312
#घोषणा	APM_FUNC_TIMER		0x5313

/*
 * Function code क्रम APM_FUNC_RESUME_TIMER
 */
#घोषणा	APM_FUNC_DISABLE_TIMER	0
#घोषणा	APM_FUNC_GET_TIMER	1
#घोषणा	APM_FUNC_SET_TIMER	2

/*
 * Function code क्रम APM_FUNC_RESUME_ON_RING
 */
#घोषणा	APM_FUNC_DISABLE_RING	0
#घोषणा	APM_FUNC_ENABLE_RING	1
#घोषणा	APM_FUNC_GET_RING	2

/*
 * Function code क्रम APM_FUNC_TIMER_STATUS
 */
#घोषणा	APM_FUNC_TIMER_DISABLE	0
#घोषणा	APM_FUNC_TIMER_ENABLE	1
#घोषणा	APM_FUNC_TIMER_GET	2

/*
 * in arch/i386/kernel/setup.c
 */
बाह्य काष्ठा apm_info	apm_info;

/*
 * This is the "All Devices" ID communicated to the BIOS
 */
#घोषणा APM_DEVICE_BALL		((apm_info.connection_version > 0x0100) ? \
				 APM_DEVICE_ALL : APM_DEVICE_OLD_ALL)
#पूर्ण_अगर	/* LINUX_APM_H */
