<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *	include/यंत्र-parisc/pdc_chassis.h
 *
 *	Copyright (C) 2002 Laurent Canet <canetl@esiee.fr>
 *	Copyright (C) 2002 Thibaut Varene <varenet@parisc-linux.org>
 *
 *      TODO:	- handle processor number on SMP प्रणालीs (Reporting Entity ID)
 *      	- handle message ID
 *      	- handle बारtamps
 */
 

#अगर_अघोषित _PARISC_PDC_CHASSIS_H
#घोषणा _PARISC_PDC_CHASSIS_H

/*
 * ----------
 * Prototypes
 * ----------
 */

पूर्णांक pdc_chassis_send_status(पूर्णांक message);
व्योम parisc_pdc_chassis_init(व्योम);


/*
 * -----------------
 * Direct call names
 * -----------------
 * They setup everything क्रम you, the Log message and the corresponding LED state
 */

#घोषणा PDC_CHASSIS_सूचीECT_BSTART	0
#घोषणा PDC_CHASSIS_सूचीECT_BCOMPLETE	1
#घोषणा PDC_CHASSIS_सूचीECT_SHUTDOWN	2
#घोषणा PDC_CHASSIS_सूचीECT_PANIC	3
#घोषणा PDC_CHASSIS_सूचीECT_HPMC		4
#घोषणा PDC_CHASSIS_सूचीECT_LPMC		5
#घोषणा PDC_CHASSIS_सूचीECT_DUMP		6	/* not yet implemented */
#घोषणा PDC_CHASSIS_सूचीECT_OOPS		7	/* not yet implemented */


/*
 * ------------
 * LEDs control
 * ------------
 * Set the three LEDs -- Run, Attn, and Fault.
 */

/* Old PDC LED control */
#घोषणा PDC_CHASSIS_DISP_DATA(v)	((अचिन्हित दीर्घ)(v) << 17)

/* 
 * Available PDC PAT LED states
 */

#घोषणा PDC_CHASSIS_LED_RUN_OFF		(0ULL << 4)
#घोषणा PDC_CHASSIS_LED_RUN_FLASH	(1ULL << 4)
#घोषणा PDC_CHASSIS_LED_RUN_ON		(2ULL << 4)
#घोषणा PDC_CHASSIS_LED_RUN_NC		(3ULL << 4)
#घोषणा PDC_CHASSIS_LED_ATTN_OFF	(0ULL << 6)
#घोषणा PDC_CHASSIS_LED_ATTN_FLASH	(1ULL << 6)
#घोषणा PDC_CHASSIS_LED_ATTN_NC		(3ULL << 6)	/* ATTN ON is invalid */
#घोषणा PDC_CHASSIS_LED_FAULT_OFF	(0ULL << 8)
#घोषणा PDC_CHASSIS_LED_FAULT_FLASH	(1ULL << 8)
#घोषणा PDC_CHASSIS_LED_FAULT_ON	(2ULL << 8)
#घोषणा PDC_CHASSIS_LED_FAULT_NC	(3ULL << 8)
#घोषणा PDC_CHASSIS_LED_VALID		(1ULL << 10)

/* 
 * Valid PDC PAT LED states combinations
 */

/* System running normally */
#घोषणा PDC_CHASSIS_LSTATE_RUN_NORMAL	(PDC_CHASSIS_LED_RUN_ON		| \
					 PDC_CHASSIS_LED_ATTN_OFF	| \
					 PDC_CHASSIS_LED_FAULT_OFF	| \
					 PDC_CHASSIS_LED_VALID		)
/* System crashed and rebooted itself successfully */
#घोषणा PDC_CHASSIS_LSTATE_RUN_CRASHREC	(PDC_CHASSIS_LED_RUN_ON		| \
					 PDC_CHASSIS_LED_ATTN_OFF	| \
					 PDC_CHASSIS_LED_FAULT_FLASH	| \
					 PDC_CHASSIS_LED_VALID		)
/* There was a प्रणाली पूर्णांकerruption that did not take the प्रणाली करोwn */
#घोषणा PDC_CHASSIS_LSTATE_RUN_SYSINT	(PDC_CHASSIS_LED_RUN_ON		| \
					 PDC_CHASSIS_LED_ATTN_FLASH	| \
					 PDC_CHASSIS_LED_FAULT_OFF	| \
					 PDC_CHASSIS_LED_VALID		)
/* System running and unexpected reboot or non-critical error detected */
#घोषणा PDC_CHASSIS_LSTATE_RUN_NCRIT	(PDC_CHASSIS_LED_RUN_ON		| \
					 PDC_CHASSIS_LED_ATTN_FLASH	| \
					 PDC_CHASSIS_LED_FAULT_FLASH	| \
					 PDC_CHASSIS_LED_VALID		)
/* Executing non-OS code */
#घोषणा PDC_CHASSIS_LSTATE_NONOS	(PDC_CHASSIS_LED_RUN_FLASH	| \
					 PDC_CHASSIS_LED_ATTN_OFF	| \
					 PDC_CHASSIS_LED_FAULT_OFF	| \
					 PDC_CHASSIS_LED_VALID		)
/* Boot failed - Executing non-OS code */
#घोषणा PDC_CHASSIS_LSTATE_NONOS_BFAIL	(PDC_CHASSIS_LED_RUN_FLASH	| \
					 PDC_CHASSIS_LED_ATTN_OFF	| \
					 PDC_CHASSIS_LED_FAULT_ON	| \
					 PDC_CHASSIS_LED_VALID		)
/* Unexpected reboot occurred - Executing non-OS code */
#घोषणा PDC_CHASSIS_LSTATE_NONOS_UNEXP	(PDC_CHASSIS_LED_RUN_FLASH	| \
					 PDC_CHASSIS_LED_ATTN_OFF	| \
					 PDC_CHASSIS_LED_FAULT_FLASH	| \
					 PDC_CHASSIS_LED_VALID		)
/* Executing non-OS code - Non-critical error detected */
#घोषणा PDC_CHASSIS_LSTATE_NONOS_NCRIT	(PDC_CHASSIS_LED_RUN_FLASH	| \
					 PDC_CHASSIS_LED_ATTN_FLASH	| \
					 PDC_CHASSIS_LED_FAULT_OFF	| \
					 PDC_CHASSIS_LED_VALID		)
/* Boot failed - Executing non-OS code - Non-critical error detected */
#घोषणा PDC_CHASSIS_LSTATE_BFAIL_NCRIT	(PDC_CHASSIS_LED_RUN_FLASH	| \
					 PDC_CHASSIS_LED_ATTN_FLASH	| \
					 PDC_CHASSIS_LED_FAULT_ON	| \
					 PDC_CHASSIS_LED_VALID		)
/* Unexpected reboot/recovering - Executing non-OS code - Non-critical error detected */
#घोषणा PDC_CHASSIS_LSTATE_UNEXP_NCRIT	(PDC_CHASSIS_LED_RUN_FLASH	| \
					 PDC_CHASSIS_LED_ATTN_FLASH	| \
					 PDC_CHASSIS_LED_FAULT_FLASH	| \
					 PDC_CHASSIS_LED_VALID		)
/* Cannot execute PDC */
#घोषणा PDC_CHASSIS_LSTATE_CANNOT_PDC	(PDC_CHASSIS_LED_RUN_OFF	| \
					 PDC_CHASSIS_LED_ATTN_OFF	| \
					 PDC_CHASSIS_LED_FAULT_OFF	| \
					 PDC_CHASSIS_LED_VALID		)
/* Boot failed - OS not up - PDC has detected a failure that prevents boot */
#घोषणा PDC_CHASSIS_LSTATE_FATAL_BFAIL	(PDC_CHASSIS_LED_RUN_OFF	| \
					 PDC_CHASSIS_LED_ATTN_OFF	| \
					 PDC_CHASSIS_LED_FAULT_ON	| \
					 PDC_CHASSIS_LED_VALID		)
/* No code running - Non-critical error detected (द्विगुन fault situation) */
#घोषणा PDC_CHASSIS_LSTATE_NOCODE_NCRIT	(PDC_CHASSIS_LED_RUN_OFF	| \
					 PDC_CHASSIS_LED_ATTN_FLASH	| \
					 PDC_CHASSIS_LED_FAULT_OFF	| \
					 PDC_CHASSIS_LED_VALID		)
/* Boot failed - OS not up - Fatal failure detected - Non-critical error detected */
#घोषणा PDC_CHASSIS_LSTATE_FATAL_NCRIT	(PDC_CHASSIS_LED_RUN_OFF	| \
					 PDC_CHASSIS_LED_ATTN_FLASH	| \
					 PDC_CHASSIS_LED_FAULT_ON	| \
					 PDC_CHASSIS_LED_VALID		)
/* All other states are invalid */


/*
 * --------------
 * PDC Log events
 * --------------
 * Here follows bits needed to fill up the log event sent to PDC_CHASSIS
 * The log message contains: Alert level, Source, Source detail,
 * Source ID, Problem detail, Caller activity, Activity status, 
 * Caller subactivity, Reporting entity type, Reporting entity ID,
 * Data type, Unique message ID and EOM. 
 */

/* Alert level */
#घोषणा PDC_CHASSIS_ALERT_FORWARD	(0ULL << 36)	/* no failure detected */
#घोषणा PDC_CHASSIS_ALERT_SERPROC	(1ULL << 36)	/* service proc - no failure */
#घोषणा PDC_CHASSIS_ALERT_NURGENT	(2ULL << 36)	/* non-urgent चालक attn */
#घोषणा PDC_CHASSIS_ALERT_BLOCKED	(3ULL << 36)	/* प्रणाली blocked */
#घोषणा PDC_CHASSIS_ALERT_CONF_CHG	(4ULL << 36)	/* unexpected configuration change */
#घोषणा PDC_CHASSIS_ALERT_ENV_PB	(5ULL << 36)	/* boot possible, environmental pb */
#घोषणा PDC_CHASSIS_ALERT_PENDING	(6ULL << 36)	/* boot possible, pending failure */
#घोषणा PDC_CHASSIS_ALERT_PERF_IMP	(8ULL << 36)	/* boot possible, perक्रमmance impaired */
#घोषणा PDC_CHASSIS_ALERT_FUNC_IMP	(10ULL << 36)	/* boot possible, functionality impaired */
#घोषणा PDC_CHASSIS_ALERT_SOFT_FAIL	(12ULL << 36)	/* software failure */
#घोषणा PDC_CHASSIS_ALERT_HANG		(13ULL << 36)	/* प्रणाली hang */
#घोषणा PDC_CHASSIS_ALERT_ENV_FATAL	(14ULL << 36)	/* fatal घातer or environmental pb */
#घोषणा PDC_CHASSIS_ALERT_HW_FATAL	(15ULL << 36)	/* fatal hardware problem */

/* Source */
#घोषणा PDC_CHASSIS_SRC_NONE		(0ULL << 28)	/* unknown, no source stated */
#घोषणा PDC_CHASSIS_SRC_PROC		(1ULL << 28)	/* processor */
/* For later use ? */
#घोषणा PDC_CHASSIS_SRC_PROC_CACHE	(2ULL << 28)	/* processor cache*/
#घोषणा PDC_CHASSIS_SRC_PDH		(3ULL << 28)	/* processor dependent hardware */
#घोषणा PDC_CHASSIS_SRC_PWR		(4ULL << 28)	/* घातer */
#घोषणा PDC_CHASSIS_SRC_FAB		(5ULL << 28)	/* fabric connector */
#घोषणा PDC_CHASSIS_SRC_PLATi		(6ULL << 28)	/* platक्रमm */
#घोषणा PDC_CHASSIS_SRC_MEM		(7ULL << 28)	/* memory */
#घोषणा PDC_CHASSIS_SRC_IO		(8ULL << 28)	/* I/O */
#घोषणा PDC_CHASSIS_SRC_CELL		(9ULL << 28)	/* cell */
#घोषणा PDC_CHASSIS_SRC_PD		(10ULL << 28)	/* रक्षित करोमुख्य */

/* Source detail field */
#घोषणा PDC_CHASSIS_SRC_D_PROC		(1ULL << 24)	/* processor general */

/* Source ID - platक्रमm dependent */
#घोषणा PDC_CHASSIS_SRC_ID_UNSPEC	(0ULL << 16)

/* Problem detail - problem source dependent */
#घोषणा PDC_CHASSIS_PB_D_PROC_NONE	(0ULL << 32)	/* no problem detail */
#घोषणा PDC_CHASSIS_PB_D_PROC_TIMEOUT	(4ULL << 32)	/* समयout */

/* Caller activity */
#घोषणा PDC_CHASSIS_CALL_ACT_HPUX_BL	(7ULL << 12)	/* Boot Loader */
#घोषणा PDC_CHASSIS_CALL_ACT_HPUX_PD	(8ULL << 12)	/* SAL_PD activities */
#घोषणा PDC_CHASSIS_CALL_ACT_HPUX_EVENT	(9ULL << 12)	/* SAL_EVENTS activities */
#घोषणा PDC_CHASSIS_CALL_ACT_HPUX_IO	(10ULL << 12)	/* SAL_IO activities */
#घोषणा PDC_CHASSIS_CALL_ACT_HPUX_PANIC	(11ULL << 12)	/* System panic */
#घोषणा PDC_CHASSIS_CALL_ACT_HPUX_INIT	(12ULL << 12)	/* System initialization */
#घोषणा PDC_CHASSIS_CALL_ACT_HPUX_SHUT	(13ULL << 12)	/* System shutकरोwn */
#घोषणा PDC_CHASSIS_CALL_ACT_HPUX_WARN	(14ULL << 12)	/* System warning */
#घोषणा PDC_CHASSIS_CALL_ACT_HPUX_DU	(15ULL << 12)	/* Display_Activity() update */

/* Activity status - implementation dependent */
#घोषणा PDC_CHASSIS_ACT_STATUS_UNSPEC	(0ULL << 0)

/* Caller subactivity - implementation dependent */
/* FIXME: other subactivities ? */
#घोषणा PDC_CHASSIS_CALL_SACT_UNSPEC	(0ULL << 4)	/* implementation dependent */

/* Reporting entity type */
#घोषणा PDC_CHASSIS_RET_GENERICOS	(12ULL << 52)	/* generic OSes */
#घोषणा PDC_CHASSIS_RET_IA64_NT		(13ULL << 52)	/* IA-64 NT */
#घोषणा PDC_CHASSIS_RET_HPUX		(14ULL << 52)	/* HP-UX */
#घोषणा PDC_CHASSIS_RET_DIAG		(15ULL << 52)	/* offline diagnostics & utilities */

/* Reporting entity ID */
#घोषणा PDC_CHASSIS_REID_UNSPEC		(0ULL << 44)

/* Data type */
#घोषणा PDC_CHASSIS_DT_NONE		(0ULL << 59)	/* data field unused */
/* For later use ? Do we need these ? */
#घोषणा PDC_CHASSIS_DT_PHYS_ADDR	(1ULL << 59)	/* physical address */
#घोषणा PDC_CHASSIS_DT_DATA_EXPECT	(2ULL << 59)	/* expected data */
#घोषणा PDC_CHASSIS_DT_ACTUAL		(3ULL << 59)	/* actual data */
#घोषणा PDC_CHASSIS_DT_PHYS_LOC		(4ULL << 59)	/* physical location */
#घोषणा PDC_CHASSIS_DT_PHYS_LOC_EXT	(5ULL << 59)	/* physical location extension */
#घोषणा PDC_CHASSIS_DT_TAG		(6ULL << 59)	/* tag */
#घोषणा PDC_CHASSIS_DT_SYNDROME		(7ULL << 59)	/* syndrome */
#घोषणा PDC_CHASSIS_DT_CODE_ADDR	(8ULL << 59)	/* code address */
#घोषणा PDC_CHASSIS_DT_ASCII_MSG	(9ULL << 59)	/* ascii message */
#घोषणा PDC_CHASSIS_DT_POST		(10ULL << 59)	/* POST code */
#घोषणा PDC_CHASSIS_DT_TIMESTAMP	(11ULL << 59)	/* बारtamp */
#घोषणा PDC_CHASSIS_DT_DEV_STAT		(12ULL << 59)	/* device status */
#घोषणा PDC_CHASSIS_DT_DEV_TYPE		(13ULL << 59)	/* device type */
#घोषणा PDC_CHASSIS_DT_PB_DET		(14ULL << 59)	/* problem detail */
#घोषणा PDC_CHASSIS_DT_ACT_LEV		(15ULL << 59)	/* activity level/समयout */
#घोषणा PDC_CHASSIS_DT_SER_NUM		(16ULL << 59)	/* serial number */
#घोषणा PDC_CHASSIS_DT_REV_NUM		(17ULL << 59)	/* revision number */
#घोषणा PDC_CHASSIS_DT_INTERRUPT	(18ULL << 59)	/* पूर्णांकerruption inक्रमmation */
#घोषणा PDC_CHASSIS_DT_TEST_NUM		(19ULL << 59)	/* test number */
#घोषणा PDC_CHASSIS_DT_STATE_CHG	(20ULL << 59)	/* major changes in प्रणाली state */
#घोषणा PDC_CHASSIS_DT_PROC_DEALLOC	(21ULL << 59)	/* processor deallocate */
#घोषणा PDC_CHASSIS_DT_RESET		(30ULL << 59)	/* reset type and cause */
#घोषणा PDC_CHASSIS_DT_PA_LEGACY	(31ULL << 59)	/* legacy PA hex chassis code */

/* System states - part of major changes in प्रणाली state data field */
#घोषणा PDC_CHASSIS_SYSTATE_BSTART	(0ULL << 0)	/* boot start */
#घोषणा PDC_CHASSIS_SYSTATE_BCOMP	(1ULL << 0)	/* boot complete */
#घोषणा PDC_CHASSIS_SYSTATE_CHANGE	(2ULL << 0)	/* major change */
#घोषणा PDC_CHASSIS_SYSTATE_LED		(3ULL << 0)	/* LED change */
#घोषणा PDC_CHASSIS_SYSTATE_PANIC	(9ULL << 0)	/* OS Panic */
#घोषणा PDC_CHASSIS_SYSTATE_DUMP	(10ULL << 0)	/* memory dump */
#घोषणा PDC_CHASSIS_SYSTATE_HPMC	(11ULL << 0)	/* processing HPMC */
#घोषणा PDC_CHASSIS_SYSTATE_HALT	(15ULL << 0)	/* प्रणाली halted */

/* Message ID */
#घोषणा PDC_CHASSIS_MSG_ID		(0ULL << 40)	/* we करो not handle msg IDs aपंचांग */

/* EOM - separates log entries */
#घोषणा PDC_CHASSIS_EOM_CLEAR		(0ULL << 43)
#घोषणा PDC_CHASSIS_EOM_SET		(1ULL << 43)

/*
 * Preक्रमmated well known messages
 */

/* Boot started */
#घोषणा PDC_CHASSIS_PMSG_BSTART		(PDC_CHASSIS_ALERT_SERPROC	| \
					 PDC_CHASSIS_SRC_PROC		| \
					 PDC_CHASSIS_SRC_D_PROC		| \
					 PDC_CHASSIS_SRC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PROC_NONE	| \
					 PDC_CHASSIS_CALL_ACT_HPUX_INIT	| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CALL_SACT_UNSPEC	| \
					 PDC_CHASSIS_RET_HPUX		| \
					 PDC_CHASSIS_REID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_BSTART	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

/* Boot complete */
#घोषणा PDC_CHASSIS_PMSG_BCOMPLETE	(PDC_CHASSIS_ALERT_SERPROC	| \
					 PDC_CHASSIS_SRC_PROC		| \
					 PDC_CHASSIS_SRC_D_PROC		| \
					 PDC_CHASSIS_SRC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PROC_NONE	| \
					 PDC_CHASSIS_CALL_ACT_HPUX_INIT	| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CALL_SACT_UNSPEC	| \
					 PDC_CHASSIS_RET_HPUX		| \
					 PDC_CHASSIS_REID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_BCOMP	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

/* Shutकरोwn */
#घोषणा PDC_CHASSIS_PMSG_SHUTDOWN	(PDC_CHASSIS_ALERT_SERPROC	| \
					 PDC_CHASSIS_SRC_PROC		| \
					 PDC_CHASSIS_SRC_D_PROC		| \
					 PDC_CHASSIS_SRC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PROC_NONE	| \
					 PDC_CHASSIS_CALL_ACT_HPUX_SHUT	| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CALL_SACT_UNSPEC	| \
					 PDC_CHASSIS_RET_HPUX		| \
					 PDC_CHASSIS_REID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_HALT	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

/* Panic */
#घोषणा PDC_CHASSIS_PMSG_PANIC		(PDC_CHASSIS_ALERT_SOFT_FAIL	| \
					 PDC_CHASSIS_SRC_PROC		| \
					 PDC_CHASSIS_SRC_D_PROC		| \
					 PDC_CHASSIS_SRC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PROC_NONE	| \
					 PDC_CHASSIS_CALL_ACT_HPUX_PANIC| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CALL_SACT_UNSPEC	| \
					 PDC_CHASSIS_RET_HPUX		| \
					 PDC_CHASSIS_REID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_PANIC	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

// FIXME: extrapolated data
/* HPMC */
#घोषणा PDC_CHASSIS_PMSG_HPMC		(PDC_CHASSIS_ALERT_CONF_CHG /*?*/	| \
					 PDC_CHASSIS_SRC_PROC		| \
					 PDC_CHASSIS_SRC_D_PROC		| \
					 PDC_CHASSIS_SRC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PROC_NONE	| \
					 PDC_CHASSIS_CALL_ACT_HPUX_WARN	| \
					 PDC_CHASSIS_RET_HPUX		| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_HPMC	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

/* LPMC */
#घोषणा PDC_CHASSIS_PMSG_LPMC		(PDC_CHASSIS_ALERT_BLOCKED /*?*/| \
					 PDC_CHASSIS_SRC_PROC		| \
					 PDC_CHASSIS_SRC_D_PROC		| \
					 PDC_CHASSIS_SRC_ID_UNSPEC	| \
					 PDC_CHASSIS_PB_D_PROC_NONE	| \
					 PDC_CHASSIS_CALL_ACT_HPUX_WARN	| \
					 PDC_CHASSIS_ACT_STATUS_UNSPEC	| \
					 PDC_CHASSIS_CALL_SACT_UNSPEC	| \
					 PDC_CHASSIS_RET_HPUX		| \
					 PDC_CHASSIS_REID_UNSPEC	| \
					 PDC_CHASSIS_DT_STATE_CHG	| \
					 PDC_CHASSIS_SYSTATE_CHANGE	| \
					 PDC_CHASSIS_MSG_ID		| \
					 PDC_CHASSIS_EOM_SET		)

#पूर्ण_अगर /* _PARISC_PDC_CHASSIS_H */
