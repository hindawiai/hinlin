<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _POWERPC_RTAS_H
#घोषणा _POWERPC_RTAS_H
#अगर_घोषित __KERNEL__

#समावेश <linux/spinlock.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/rtas-types.h>
#समावेश <linux/समय.स>
#समावेश <linux/cpumask.h>

/*
 * Definitions क्रम talking to the RTAS on CHRP machines.
 *
 * Copyright (C) 2001 Peter Bergner
 * Copyright (C) 2001 PPC 64 Team, IBM Corp
 */

#घोषणा RTAS_UNKNOWN_SERVICE (-1)
#घोषणा RTAS_INSTANTIATE_MAX (1ULL<<30) /* Don't instantiate rtas at/above this value */

/* Memory set aside क्रम sys_rtas to use with calls that need a work area. */
#घोषणा RTAS_USER_REGION_SIZE (64 * 1024)

/* RTAS वापस status codes */
#घोषणा RTAS_BUSY		-2    /* RTAS Busy */
#घोषणा RTAS_EXTENDED_DELAY_MIN	9900
#घोषणा RTAS_EXTENDED_DELAY_MAX	9905

/* statuses specअगरic to ibm,suspend-me */
#घोषणा RTAS_SUSPEND_ABORTED     9000 /* Suspension पातed */
#घोषणा RTAS_NOT_SUSPENDABLE    -9004 /* Partition not suspendable */
#घोषणा RTAS_THREADS_ACTIVE     -9005 /* Multiple processor thपढ़ोs active */
#घोषणा RTAS_OUTSTANDING_COPROC -9006 /* Outstanding coprocessor operations */

/*
 * In general to call RTAS use rtas_token("string") to lookup
 * an RTAS token क्रम the given string (e.g. "event-scan").
 * To actually perक्रमm the call use
 *    ret = rtas_call(token, n_in, n_out, ...)
 * Where n_in is the number of input parameters and
 *       n_out is the number of output parameters
 *
 * If the "string" is invalid on this प्रणाली, RTAS_UNKNOWN_SERVICE
 * will be वापसed as a token.  rtas_call() करोes look क्रम this
 * token and error out gracefully so rtas_call(rtas_token("str"), ...)
 * may be safely used क्रम one-shot calls to RTAS.
 *
 */

/* RTAS event classes */
#घोषणा RTAS_INTERNAL_ERROR		0x80000000 /* set bit 0 */
#घोषणा RTAS_EPOW_WARNING		0x40000000 /* set bit 1 */
#घोषणा RTAS_HOTPLUG_EVENTS		0x10000000 /* set bit 3 */
#घोषणा RTAS_IO_EVENTS			0x08000000 /* set bit 4 */
#घोषणा RTAS_EVENT_SCAN_ALL_EVENTS	0xffffffff

/* RTAS event severity */
#घोषणा RTAS_SEVERITY_FATAL		0x5
#घोषणा RTAS_SEVERITY_ERROR		0x4
#घोषणा RTAS_SEVERITY_ERROR_SYNC	0x3
#घोषणा RTAS_SEVERITY_WARNING		0x2
#घोषणा RTAS_SEVERITY_EVENT		0x1
#घोषणा RTAS_SEVERITY_NO_ERROR		0x0

/* RTAS event disposition */
#घोषणा RTAS_DISP_FULLY_RECOVERED	0x0
#घोषणा RTAS_DISP_LIMITED_RECOVERY	0x1
#घोषणा RTAS_DISP_NOT_RECOVERED		0x2

/* RTAS event initiator */
#घोषणा RTAS_INITIATOR_UNKNOWN		0x0
#घोषणा RTAS_INITIATOR_CPU		0x1
#घोषणा RTAS_INITIATOR_PCI		0x2
#घोषणा RTAS_INITIATOR_ISA		0x3
#घोषणा RTAS_INITIATOR_MEMORY		0x4
#घोषणा RTAS_INITIATOR_POWERMGM		0x5

/* RTAS event target */
#घोषणा RTAS_TARGET_UNKNOWN		0x0
#घोषणा RTAS_TARGET_CPU			0x1
#घोषणा RTAS_TARGET_PCI			0x2
#घोषणा RTAS_TARGET_ISA			0x3
#घोषणा RTAS_TARGET_MEMORY		0x4
#घोषणा RTAS_TARGET_POWERMGM		0x5

/* RTAS event type */
#घोषणा RTAS_TYPE_RETRY			0x01
#घोषणा RTAS_TYPE_TCE_ERR		0x02
#घोषणा RTAS_TYPE_INTERN_DEV_FAIL	0x03
#घोषणा RTAS_TYPE_TIMEOUT		0x04
#घोषणा RTAS_TYPE_DATA_PARITY		0x05
#घोषणा RTAS_TYPE_ADDR_PARITY		0x06
#घोषणा RTAS_TYPE_CACHE_PARITY		0x07
#घोषणा RTAS_TYPE_ADDR_INVALID		0x08
#घोषणा RTAS_TYPE_ECC_UNCORR		0x09
#घोषणा RTAS_TYPE_ECC_CORR		0x0a
#घोषणा RTAS_TYPE_EPOW			0x40
#घोषणा RTAS_TYPE_PLATFORM		0xE0
#घोषणा RTAS_TYPE_IO			0xE1
#घोषणा RTAS_TYPE_INFO			0xE2
#घोषणा RTAS_TYPE_DEALLOC		0xE3
#घोषणा RTAS_TYPE_DUMP			0xE4
#घोषणा RTAS_TYPE_HOTPLUG		0xE5
/* I करोn't add PowerMGM events right now, this is a dअगरferent topic */ 
#घोषणा RTAS_TYPE_PMGM_POWER_SW_ON	0x60
#घोषणा RTAS_TYPE_PMGM_POWER_SW_OFF	0x61
#घोषणा RTAS_TYPE_PMGM_LID_OPEN		0x62
#घोषणा RTAS_TYPE_PMGM_LID_CLOSE	0x63
#घोषणा RTAS_TYPE_PMGM_SLEEP_BTN	0x64
#घोषणा RTAS_TYPE_PMGM_WAKE_BTN		0x65
#घोषणा RTAS_TYPE_PMGM_BATTERY_WARN	0x66
#घोषणा RTAS_TYPE_PMGM_BATTERY_CRIT	0x67
#घोषणा RTAS_TYPE_PMGM_SWITCH_TO_BAT	0x68
#घोषणा RTAS_TYPE_PMGM_SWITCH_TO_AC	0x69
#घोषणा RTAS_TYPE_PMGM_KBD_OR_MOUSE	0x6a
#घोषणा RTAS_TYPE_PMGM_ENCLOS_OPEN	0x6b
#घोषणा RTAS_TYPE_PMGM_ENCLOS_CLOSED	0x6c
#घोषणा RTAS_TYPE_PMGM_RING_INDICATE	0x6d
#घोषणा RTAS_TYPE_PMGM_LAN_ATTENTION	0x6e
#घोषणा RTAS_TYPE_PMGM_TIME_ALARM	0x6f
#घोषणा RTAS_TYPE_PMGM_CONFIG_CHANGE	0x70
#घोषणा RTAS_TYPE_PMGM_SERVICE_PROC	0x71
/* Platक्रमm Resource Reassignment Notअगरication */
#घोषणा RTAS_TYPE_PRRN			0xA0

/* RTAS check-exception vector offset */
#घोषणा RTAS_VECTOR_EXTERNAL_INTERRUPT	0x500

अटल अंतरभूत uपूर्णांक8_t rtas_error_severity(स्थिर काष्ठा rtas_error_log *elog)
अणु
	वापस (elog->byte1 & 0xE0) >> 5;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t rtas_error_disposition(स्थिर काष्ठा rtas_error_log *elog)
अणु
	वापस (elog->byte1 & 0x18) >> 3;
पूर्ण

अटल अंतरभूत
व्योम rtas_set_disposition_recovered(काष्ठा rtas_error_log *elog)
अणु
	elog->byte1 &= ~0x18;
	elog->byte1 |= (RTAS_DISP_FULLY_RECOVERED << 3);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t rtas_error_extended(स्थिर काष्ठा rtas_error_log *elog)
अणु
	वापस (elog->byte1 & 0x04) >> 2;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t rtas_error_initiator(स्थिर काष्ठा rtas_error_log *elog)
अणु
	वापस (elog->byte2 & 0xf0) >> 4;
पूर्ण

#घोषणा rtas_error_type(x)	((x)->byte3)

अटल अंतरभूत
uपूर्णांक32_t rtas_error_extended_log_length(स्थिर काष्ठा rtas_error_log *elog)
अणु
	वापस be32_to_cpu(elog->extended_log_length);
पूर्ण

#घोषणा RTAS_V6EXT_LOG_FORMAT_EVENT_LOG	14

#घोषणा RTAS_V6EXT_COMPANY_ID_IBM	(('I' << 24) | ('B' << 16) | ('M' << 8))

अटल
अंतरभूत uपूर्णांक8_t rtas_ext_event_log_क्रमmat(काष्ठा rtas_ext_event_log_v6 *ext_log)
अणु
	वापस ext_log->byte2 & 0x0F;
पूर्ण

अटल
अंतरभूत uपूर्णांक32_t rtas_ext_event_company_id(काष्ठा rtas_ext_event_log_v6 *ext_log)
अणु
	वापस be32_to_cpu(ext_log->company_id);
पूर्ण

/* pSeries event log क्रमmat */

/* Two bytes ASCII section IDs */
#घोषणा PSERIES_ELOG_SECT_ID_PRIV_HDR		(('P' << 8) | 'H')
#घोषणा PSERIES_ELOG_SECT_ID_USER_HDR		(('U' << 8) | 'H')
#घोषणा PSERIES_ELOG_SECT_ID_PRIMARY_SRC	(('P' << 8) | 'S')
#घोषणा PSERIES_ELOG_SECT_ID_EXTENDED_UH	(('E' << 8) | 'H')
#घोषणा PSERIES_ELOG_SECT_ID_FAILING_MTMS	(('M' << 8) | 'T')
#घोषणा PSERIES_ELOG_SECT_ID_SECONDARY_SRC	(('S' << 8) | 'S')
#घोषणा PSERIES_ELOG_SECT_ID_DUMP_LOCATOR	(('D' << 8) | 'H')
#घोषणा PSERIES_ELOG_SECT_ID_FW_ERROR		(('S' << 8) | 'W')
#घोषणा PSERIES_ELOG_SECT_ID_IMPACT_PART_ID	(('L' << 8) | 'P')
#घोषणा PSERIES_ELOG_SECT_ID_LOGIC_RESOURCE_ID	(('L' << 8) | 'R')
#घोषणा PSERIES_ELOG_SECT_ID_HMC_ID		(('H' << 8) | 'M')
#घोषणा PSERIES_ELOG_SECT_ID_EPOW		(('E' << 8) | 'P')
#घोषणा PSERIES_ELOG_SECT_ID_IO_EVENT		(('I' << 8) | 'E')
#घोषणा PSERIES_ELOG_SECT_ID_MANUFACT_INFO	(('M' << 8) | 'I')
#घोषणा PSERIES_ELOG_SECT_ID_CALL_HOME		(('C' << 8) | 'H')
#घोषणा PSERIES_ELOG_SECT_ID_USER_DEF		(('U' << 8) | 'D')
#घोषणा PSERIES_ELOG_SECT_ID_HOTPLUG		(('H' << 8) | 'P')
#घोषणा PSERIES_ELOG_SECT_ID_MCE		(('M' << 8) | 'C')

अटल
अंतरभूत uपूर्णांक16_t pseries_errorlog_id(काष्ठा pseries_errorlog *sect)
अणु
	वापस be16_to_cpu(sect->id);
पूर्ण

अटल
अंतरभूत uपूर्णांक16_t pseries_errorlog_length(काष्ठा pseries_errorlog *sect)
अणु
	वापस be16_to_cpu(sect->length);
पूर्ण

#घोषणा PSERIES_HP_ELOG_RESOURCE_CPU	1
#घोषणा PSERIES_HP_ELOG_RESOURCE_MEM	2
#घोषणा PSERIES_HP_ELOG_RESOURCE_SLOT	3
#घोषणा PSERIES_HP_ELOG_RESOURCE_PHB	4
#घोषणा PSERIES_HP_ELOG_RESOURCE_PMEM   6

#घोषणा PSERIES_HP_ELOG_ACTION_ADD	1
#घोषणा PSERIES_HP_ELOG_ACTION_REMOVE	2

#घोषणा PSERIES_HP_ELOG_ID_DRC_NAME	1
#घोषणा PSERIES_HP_ELOG_ID_DRC_INDEX	2
#घोषणा PSERIES_HP_ELOG_ID_DRC_COUNT	3
#घोषणा PSERIES_HP_ELOG_ID_DRC_IC	4

काष्ठा pseries_errorlog *get_pseries_errorlog(काष्ठा rtas_error_log *log,
					      uपूर्णांक16_t section_id);

/*
 * This can be set by the rtas_flash module so that it can get called
 * as the असलolutely last thing beक्रमe the kernel terminates.
 */
बाह्य व्योम (*rtas_flash_term_hook)(पूर्णांक);

बाह्य काष्ठा rtas_t rtas;

बाह्य पूर्णांक rtas_token(स्थिर अक्षर *service);
बाह्य पूर्णांक rtas_service_present(स्थिर अक्षर *service);
बाह्य पूर्णांक rtas_call(पूर्णांक token, पूर्णांक, पूर्णांक, पूर्णांक *, ...);
पूर्णांक rtas_call_reentrant(पूर्णांक token, पूर्णांक nargs, पूर्णांक nret, पूर्णांक *outमाला_दो, ...);
व्योम rtas_call_unlocked(काष्ठा rtas_args *args, पूर्णांक token, पूर्णांक nargs,
			पूर्णांक nret, ...);
बाह्य व्योम __noवापस rtas_restart(अक्षर *cmd);
बाह्य व्योम rtas_घातer_off(व्योम);
बाह्य व्योम __noवापस rtas_halt(व्योम);
बाह्य व्योम rtas_os_term(अक्षर *str);
व्योम rtas_activate_firmware(व्योम);
बाह्य पूर्णांक rtas_get_sensor(पूर्णांक sensor, पूर्णांक index, पूर्णांक *state);
बाह्य पूर्णांक rtas_get_sensor_fast(पूर्णांक sensor, पूर्णांक index, पूर्णांक *state);
बाह्य पूर्णांक rtas_get_घातer_level(पूर्णांक घातerकरोमुख्य, पूर्णांक *level);
बाह्य पूर्णांक rtas_set_घातer_level(पूर्णांक घातerकरोमुख्य, पूर्णांक level, पूर्णांक *setlevel);
बाह्य bool rtas_indicator_present(पूर्णांक token, पूर्णांक *maxindex);
बाह्य पूर्णांक rtas_set_indicator(पूर्णांक indicator, पूर्णांक index, पूर्णांक new_value);
बाह्य पूर्णांक rtas_set_indicator_fast(पूर्णांक indicator, पूर्णांक index, पूर्णांक new_value);
बाह्य व्योम rtas_progress(अक्षर *s, अचिन्हित लघु hex);
पूर्णांक rtas_ibm_suspend_me(पूर्णांक *fw_status);

काष्ठा rtc_समय;
बाह्य समय64_t rtas_get_boot_समय(व्योम);
बाह्य व्योम rtas_get_rtc_समय(काष्ठा rtc_समय *rtc_समय);
बाह्य पूर्णांक rtas_set_rtc_समय(काष्ठा rtc_समय *rtc_समय);

बाह्य अचिन्हित पूर्णांक rtas_busy_delay_समय(पूर्णांक status);
बाह्य अचिन्हित पूर्णांक rtas_busy_delay(पूर्णांक status);

बाह्य पूर्णांक early_init_dt_scan_rtas(अचिन्हित दीर्घ node,
		स्थिर अक्षर *uname, पूर्णांक depth, व्योम *data);

बाह्य व्योम pSeries_log_error(अक्षर *buf, अचिन्हित पूर्णांक err_type, पूर्णांक fatal);

#अगर_घोषित CONFIG_PPC_PSERIES
बाह्य समय64_t last_rtas_event;
बाह्य पूर्णांक clobbering_unपढ़ो_rtas_event(व्योम);
बाह्य पूर्णांक pseries_devicetree_update(s32 scope);
बाह्य व्योम post_mobility_fixup(व्योम);
पूर्णांक rtas_syscall_dispatch_ibm_suspend_me(u64 handle);
#अन्यथा
अटल अंतरभूत पूर्णांक clobbering_unपढ़ो_rtas_event(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक rtas_syscall_dispatch_ibm_suspend_me(u64 handle)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_RTAS_DAEMON
बाह्य व्योम rtas_cancel_event_scan(व्योम);
#अन्यथा
अटल अंतरभूत व्योम rtas_cancel_event_scan(व्योम) अणु पूर्ण
#पूर्ण_अगर

/* Error types logged.  */
#घोषणा ERR_FLAG_ALREADY_LOGGED	0x0
#घोषणा ERR_FLAG_BOOT		0x1 	/* log was pulled from NVRAM on boot */
#घोषणा ERR_TYPE_RTAS_LOG	0x2	/* from rtas event-scan */
#घोषणा ERR_TYPE_KERNEL_PANIC	0x4	/* from die()/panic() */
#घोषणा ERR_TYPE_KERNEL_PANIC_GZ 0x8	/* ditto, compressed */

/* All the types and not flags */
#घोषणा ERR_TYPE_MASK \
	(ERR_TYPE_RTAS_LOG | ERR_TYPE_KERNEL_PANIC | ERR_TYPE_KERNEL_PANIC_GZ)

#घोषणा RTAS_DEBUG KERN_DEBUG "RTAS: "
 
#घोषणा RTAS_ERROR_LOG_MAX 2048

/*
 * Return the firmware-specअगरied size of the error log buffer
 *  क्रम all rtas calls that require an error buffer argument.
 *  This includes 'check-exception' and 'rtas-last-error'.
 */
बाह्य पूर्णांक rtas_get_error_log_max(व्योम);

/* Event Scan Parameters */
#घोषणा EVENT_SCAN_ALL_EVENTS	0xf0000000
#घोषणा SURVEILLANCE_TOKEN	9000
#घोषणा LOG_NUMBER		64		/* must be a घातer of two */
#घोषणा LOG_NUMBER_MASK		(LOG_NUMBER-1)

/* Some RTAS ops require a data buffer and that buffer must be < 4G.
 * Rather than having a memory allocator, just use this buffer
 * (get the lock first), make the RTAS call.  Copy the data instead
 * of holding the buffer क्रम दीर्घ.
 */

#घोषणा RTAS_DATA_BUF_SIZE 4096
बाह्य spinlock_t rtas_data_buf_lock;
बाह्य अक्षर rtas_data_buf[RTAS_DATA_BUF_SIZE];

/* RMO buffer reserved क्रम user-space RTAS use */
बाह्य अचिन्हित दीर्घ rtas_rmo_buf;

#घोषणा GLOBAL_INTERRUPT_QUEUE 9005

/**
 * rtas_config_addr - Format a busno, devfn and reg क्रम RTAS.
 * @busno: The bus number.
 * @devfn: The device and function number as encoded by PCI_DEVFN().
 * @reg: The रेजिस्टर number.
 *
 * This function encodes the given busno, devfn and रेजिस्टर number as
 * required क्रम RTAS calls that take a "config_addr" parameter.
 * See PAPR requirement 7.3.4-1 क्रम more info.
 */
अटल अंतरभूत u32 rtas_config_addr(पूर्णांक busno, पूर्णांक devfn, पूर्णांक reg)
अणु
	वापस ((reg & 0xf00) << 20) | ((busno & 0xff) << 16) |
			(devfn << 8) | (reg & 0xff);
पूर्ण

बाह्य व्योम rtas_give_समयbase(व्योम);
बाह्य व्योम rtas_take_समयbase(व्योम);

#अगर_घोषित CONFIG_PPC_RTAS
अटल अंतरभूत पूर्णांक page_is_rtas_user_buf(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ paddr = (pfn << PAGE_SHIFT);
	अगर (paddr >= rtas_rmo_buf && paddr < (rtas_rmo_buf + RTAS_USER_REGION_SIZE))
		वापस 1;
	वापस 0;
पूर्ण

/* Not the best place to put pSeries_coalesce_init, will be fixed when we
 * move some of the rtas suspend-me stuff to pseries */
बाह्य व्योम pSeries_coalesce_init(व्योम);
व्योम rtas_initialize(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक page_is_rtas_user_buf(अचिन्हित दीर्घ pfn) अणु वापस 0;पूर्ण
अटल अंतरभूत व्योम pSeries_coalesce_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rtas_initialize(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक call_rtas(स्थिर अक्षर *, पूर्णांक, पूर्णांक, अचिन्हित दीर्घ *, ...);

#अगर_घोषित CONFIG_HV_PERF_CTRS
व्योम पढ़ो_24x7_sys_info(व्योम);
#अन्यथा
अटल अंतरभूत व्योम पढ़ो_24x7_sys_info(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _POWERPC_RTAS_H */
