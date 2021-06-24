<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 1999,2012
 *
 * Author(s): Martin Peschke <mpeschke@de.ibm.com>
 *	      Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित __SCLP_H__
#घोषणा __SCLP_H__

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/ebcdic.h>

/* maximum number of pages concerning our own memory management */
#घोषणा MAX_KMEM_PAGES (माप(अचिन्हित दीर्घ) << 3)
#घोषणा SCLP_CONSOLE_PAGES	6

#घोषणा SCLP_EVTYP_MASK(T) (1UL << (माप(sccb_mask_t) * BITS_PER_BYTE - (T)))

#घोषणा EVTYP_OPCMD		0x01
#घोषणा EVTYP_MSG		0x02
#घोषणा EVTYP_CONFMGMDATA	0x04
#घोषणा EVTYP_DIAG_TEST		0x07
#घोषणा EVTYP_STATECHANGE	0x08
#घोषणा EVTYP_PMSGCMD		0x09
#घोषणा EVTYP_ASYNC		0x0A
#घोषणा EVTYP_CTLPROGIDENT	0x0B
#घोषणा EVTYP_STORE_DATA	0x0C
#घोषणा EVTYP_ERRNOTIFY		0x18
#घोषणा EVTYP_VT220MSG		0x1A
#घोषणा EVTYP_SDIAS		0x1C
#घोषणा EVTYP_SIGQUIESCE	0x1D
#घोषणा EVTYP_OCF		0x1E

#घोषणा EVTYP_OPCMD_MASK	SCLP_EVTYP_MASK(EVTYP_OPCMD)
#घोषणा EVTYP_MSG_MASK		SCLP_EVTYP_MASK(EVTYP_MSG)
#घोषणा EVTYP_CONFMGMDATA_MASK	SCLP_EVTYP_MASK(EVTYP_CONFMGMDATA)
#घोषणा EVTYP_DIAG_TEST_MASK	SCLP_EVTYP_MASK(EVTYP_DIAG_TEST)
#घोषणा EVTYP_STATECHANGE_MASK	SCLP_EVTYP_MASK(EVTYP_STATECHANGE)
#घोषणा EVTYP_PMSGCMD_MASK	SCLP_EVTYP_MASK(EVTYP_PMSGCMD)
#घोषणा EVTYP_ASYNC_MASK	SCLP_EVTYP_MASK(EVTYP_ASYNC)
#घोषणा EVTYP_CTLPROGIDENT_MASK	SCLP_EVTYP_MASK(EVTYP_CTLPROGIDENT)
#घोषणा EVTYP_STORE_DATA_MASK	SCLP_EVTYP_MASK(EVTYP_STORE_DATA)
#घोषणा EVTYP_ERRNOTIFY_MASK	SCLP_EVTYP_MASK(EVTYP_ERRNOTIFY)
#घोषणा EVTYP_VT220MSG_MASK	SCLP_EVTYP_MASK(EVTYP_VT220MSG)
#घोषणा EVTYP_SDIAS_MASK	SCLP_EVTYP_MASK(EVTYP_SDIAS)
#घोषणा EVTYP_SIGQUIESCE_MASK	SCLP_EVTYP_MASK(EVTYP_SIGQUIESCE)
#घोषणा EVTYP_OCF_MASK		SCLP_EVTYP_MASK(EVTYP_OCF)

#घोषणा GNRLMSGFLGS_DOM		0x8000
#घोषणा GNRLMSGFLGS_SNDALRM	0x4000
#घोषणा GNRLMSGFLGS_HOLDMSG	0x2000

#घोषणा LNTPFLGS_CNTLTEXT	0x8000
#घोषणा LNTPFLGS_LABELTEXT	0x4000
#घोषणा LNTPFLGS_DATATEXT	0x2000
#घोषणा LNTPFLGS_ENDTEXT	0x1000
#घोषणा LNTPFLGS_PROMPTTEXT	0x0800

प्रकार अचिन्हित पूर्णांक sclp_cmdw_t;

#घोषणा SCLP_CMDW_READ_CPU_INFO		0x00010001
#घोषणा SCLP_CMDW_READ_SCP_INFO		0x00020001
#घोषणा SCLP_CMDW_READ_STORAGE_INFO	0x00040001
#घोषणा SCLP_CMDW_READ_SCP_INFO_FORCED	0x00120001
#घोषणा SCLP_CMDW_READ_EVENT_DATA	0x00770005
#घोषणा SCLP_CMDW_WRITE_EVENT_DATA	0x00760005
#घोषणा SCLP_CMDW_WRITE_EVENT_MASK	0x00780005

#घोषणा GDS_ID_MDSMU		0x1310
#घोषणा GDS_ID_MDSROUTEINFO	0x1311
#घोषणा GDS_ID_AGUNWRKCORR	0x1549
#घोषणा GDS_ID_SNACONDREPORT	0x1532
#घोषणा GDS_ID_CPMSU		0x1212
#घोषणा GDS_ID_ROUTTARGINSTR	0x154D
#घोषणा GDS_ID_OPREQ		0x8070
#घोषणा GDS_ID_TEXTCMD		0x1320

#घोषणा GDS_KEY_SELFDEFTEXTMSG	0x31

क्रमागत sclp_pm_event अणु
	SCLP_PM_EVENT_FREEZE,
	SCLP_PM_EVENT_THAW,
	SCLP_PM_EVENT_RESTORE,
पूर्ण;

#घोषणा SCLP_PANIC_PRIO		1
#घोषणा SCLP_PANIC_PRIO_CLIENT	0

प्रकार u64 sccb_mask_t;

काष्ठा sccb_header अणु
	u16	length;
	u8	function_code;
	u8	control_mask[3];
	u16	response_code;
पूर्ण __attribute__((packed));

काष्ठा init_sccb अणु
	काष्ठा sccb_header header;
	u16 _reserved;
	u16 mask_length;
	u8 masks[4 * 1021];	/* variable length */
	/*
	 * u8 receive_mask[mask_length];
	 * u8 send_mask[mask_length];
	 * u8 sclp_receive_mask[mask_length];
	 * u8 sclp_send_mask[mask_length];
	 */
पूर्ण __attribute__((packed));

#घोषणा SCLP_MASK_SIZE_COMPAT 4

अटल अंतरभूत sccb_mask_t sccb_get_mask(u8 *masks, माप_प्रकार len, पूर्णांक i)
अणु
	sccb_mask_t res = 0;

	स_नकल(&res, masks + i * len, min(माप(res), len));
	वापस res;
पूर्ण

अटल अंतरभूत व्योम sccb_set_mask(u8 *masks, माप_प्रकार len, पूर्णांक i, sccb_mask_t val)
अणु
	स_रखो(masks + i * len, 0, len);
	स_नकल(masks + i * len, &val, min(माप(val), len));
पूर्ण

#घोषणा sccb_get_generic_mask(sccb, i)					\
(अणु									\
	__typeof__(sccb) __sccb = sccb;					\
									\
	sccb_get_mask(__sccb->masks, __sccb->mask_length, i);		\
पूर्ण)
#घोषणा sccb_get_recv_mask(sccb)	sccb_get_generic_mask(sccb, 0)
#घोषणा sccb_get_send_mask(sccb)	sccb_get_generic_mask(sccb, 1)
#घोषणा sccb_get_sclp_recv_mask(sccb)	sccb_get_generic_mask(sccb, 2)
#घोषणा sccb_get_sclp_send_mask(sccb)	sccb_get_generic_mask(sccb, 3)

#घोषणा sccb_set_generic_mask(sccb, i, val)				\
(अणु									\
	__typeof__(sccb) __sccb = sccb;					\
									\
	sccb_set_mask(__sccb->masks, __sccb->mask_length, i, val);	\
पूर्ण)
#घोषणा sccb_set_recv_mask(sccb, val)	    sccb_set_generic_mask(sccb, 0, val)
#घोषणा sccb_set_send_mask(sccb, val)	    sccb_set_generic_mask(sccb, 1, val)
#घोषणा sccb_set_sclp_recv_mask(sccb, val)  sccb_set_generic_mask(sccb, 2, val)
#घोषणा sccb_set_sclp_send_mask(sccb, val)  sccb_set_generic_mask(sccb, 3, val)

काष्ठा पढ़ो_cpu_info_sccb अणु
	काष्ठा	sccb_header header;
	u16	nr_configured;
	u16	offset_configured;
	u16	nr_standby;
	u16	offset_standby;
	/*
	 * Without ext sccb, काष्ठा size is PAGE_SIZE.
	 * With ext sccb, काष्ठा size is EXT_SCCB_READ_CPU.
	 */
	u8	reserved[];
पूर्ण __attribute__((packed, aligned(PAGE_SIZE)));

काष्ठा पढ़ो_info_sccb अणु
	काष्ठा	sccb_header header;	/* 0-7 */
	u16	rnmax;			/* 8-9 */
	u8	rnsize;			/* 10 */
	u8	_pad_11[16 - 11];	/* 11-15 */
	u16	ncpurl;			/* 16-17 */
	u16	cpuoff;			/* 18-19 */
	u8	_pad_20[24 - 20];	/* 20-23 */
	u8	loadparm[8];		/* 24-31 */
	u8	_pad_32[42 - 32];	/* 32-41 */
	u8	fac42;			/* 42 */
	u8	fac43;			/* 43 */
	u8	_pad_44[48 - 44];	/* 44-47 */
	u64	facilities;		/* 48-55 */
	u8	_pad_56[66 - 56];	/* 56-65 */
	u8	fac66;			/* 66 */
	u8	_pad_67[76 - 67];	/* 67-83 */
	u32	ibc;			/* 76-79 */
	u8	_pad80[84 - 80];	/* 80-83 */
	u8	fac84;			/* 84 */
	u8	fac85;			/* 85 */
	u8	_pad_86[91 - 86];	/* 86-90 */
	u8	fac91;			/* 91 */
	u8	_pad_92[98 - 92];	/* 92-97 */
	u8	fac98;			/* 98 */
	u8	hamaxघात;		/* 99 */
	u32	rnsize2;		/* 100-103 */
	u64	rnmax2;			/* 104-111 */
	u32	hsa_size;		/* 112-115 */
	u8	fac116;			/* 116 */
	u8	fac117;			/* 117 */
	u8	fac118;			/* 118 */
	u8	fac119;			/* 119 */
	u16	hcpua;			/* 120-121 */
	u8	_pad_122[124 - 122];	/* 122-123 */
	u32	hmfai;			/* 124-127 */
	u8	_pad_128[134 - 128];	/* 128-133 */
	u8	byte_134;			/* 134 */
	u8	cpudirq;		/* 135 */
	u16	cbl;			/* 136-137 */
	u8	_pad_138[EXT_SCCB_READ_SCP - 138];
पूर्ण __packed __aligned(PAGE_SIZE);

काष्ठा पढ़ो_storage_sccb अणु
	काष्ठा sccb_header header;
	u16 max_id;
	u16 asचिन्हित;
	u16 standby;
	u16 :16;
	u32 entries[0];
पूर्ण __packed;

अटल अंतरभूत व्योम sclp_fill_core_info(काष्ठा sclp_core_info *info,
				       काष्ठा पढ़ो_cpu_info_sccb *sccb)
अणु
	अक्षर *page = (अक्षर *) sccb;

	स_रखो(info, 0, माप(*info));
	info->configured = sccb->nr_configured;
	info->standby = sccb->nr_standby;
	info->combined = sccb->nr_configured + sccb->nr_standby;
	स_नकल(&info->core, page + sccb->offset_configured,
	       info->combined * माप(काष्ठा sclp_core_entry));
पूर्ण

#घोषणा SCLP_HAS_CHP_INFO	(sclp.facilities & 0x8000000000000000ULL)
#घोषणा SCLP_HAS_CHP_RECONFIG	(sclp.facilities & 0x2000000000000000ULL)
#घोषणा SCLP_HAS_CPU_INFO	(sclp.facilities & 0x0800000000000000ULL)
#घोषणा SCLP_HAS_CPU_RECONFIG	(sclp.facilities & 0x0400000000000000ULL)
#घोषणा SCLP_HAS_PCI_RECONFIG	(sclp.facilities & 0x0000000040000000ULL)
#घोषणा SCLP_HAS_AP_RECONFIG	(sclp.facilities & 0x0000000100000000ULL)

काष्ठा gds_subvector अणु
	u8	length;
	u8	key;
पूर्ण __attribute__((packed));

काष्ठा gds_vector अणु
	u16	length;
	u16	gds_id;
पूर्ण __attribute__((packed));

काष्ठा evbuf_header अणु
	u16	length;
	u8	type;
	u8	flags;
	u16	_reserved;
पूर्ण __attribute__((packed));

काष्ठा sclp_req अणु
	काष्ठा list_head list;		/* list_head क्रम request queueing. */
	sclp_cmdw_t command;		/* sclp command to execute */
	व्योम	*sccb;			/* poपूर्णांकer to the sccb to execute */
	अक्षर	status;			/* status of this request */
	पूर्णांक     start_count;		/* number of SVCs करोne क्रम this req */
	/* Callback that is called after reaching final status. */
	व्योम (*callback)(काष्ठा sclp_req *, व्योम *data);
	व्योम *callback_data;
	पूर्णांक queue_समयout;		/* request queue समयout (sec), set by
					   caller of sclp_add_request(), अगर
					   needed */
	/* Internal fields */
	अचिन्हित दीर्घ queue_expires;	/* request queue समयout (jअगरfies) */
पूर्ण;

#घोषणा SCLP_REQ_FILLED	  0x00	/* request is पढ़ोy to be processed */
#घोषणा SCLP_REQ_QUEUED	  0x01	/* request is queued to be processed */
#घोषणा SCLP_REQ_RUNNING  0x02	/* request is currently running */
#घोषणा SCLP_REQ_DONE	  0x03	/* request is completed successfully */
#घोषणा SCLP_REQ_FAILED	  0x05	/* request is finally failed */
#घोषणा SCLP_REQ_QUEUED_TIMEOUT 0x06	/* request on queue समयd out */

#घोषणा SCLP_QUEUE_INTERVAL 5	/* समयout पूर्णांकerval क्रम request queue */

/* function poपूर्णांकers that a high level driver has to use क्रम registration */
/* of some routines it wants to be called from the low level driver */
काष्ठा sclp_रेजिस्टर अणु
	काष्ठा list_head list;
	/* User wants to receive: */
	sccb_mask_t receive_mask;
	/* User wants to send: */
	sccb_mask_t send_mask;
	/* H/W can receive: */
	sccb_mask_t sclp_receive_mask;
	/* H/W can send: */
	sccb_mask_t sclp_send_mask;
	/* called अगर event type availability changes */
	व्योम (*state_change_fn)(काष्ठा sclp_रेजिस्टर *);
	/* called क्रम events in cp_receive_mask/sclp_receive_mask */
	व्योम (*receiver_fn)(काष्ठा evbuf_header *);
	/* called क्रम घातer management events */
	व्योम (*pm_event_fn)(काष्ठा sclp_रेजिस्टर *, क्रमागत sclp_pm_event);
	/* pm event posted flag */
	पूर्णांक pm_event_posted;
पूर्ण;

/* बाह्यals from sclp.c */
पूर्णांक sclp_add_request(काष्ठा sclp_req *req);
व्योम sclp_sync_रुको(व्योम);
पूर्णांक sclp_रेजिस्टर(काष्ठा sclp_रेजिस्टर *reg);
व्योम sclp_unरेजिस्टर(काष्ठा sclp_रेजिस्टर *reg);
पूर्णांक sclp_हटाओ_processed(काष्ठा sccb_header *sccb);
पूर्णांक sclp_deactivate(व्योम);
पूर्णांक sclp_reactivate(व्योम);
पूर्णांक sclp_sync_request(sclp_cmdw_t command, व्योम *sccb);
पूर्णांक sclp_sync_request_समयout(sclp_cmdw_t command, व्योम *sccb, पूर्णांक समयout);
पूर्णांक sclp_sdias_init(व्योम);

क्रमागत अणु
	sclp_init_state_uninitialized,
	sclp_init_state_initializing,
	sclp_init_state_initialized
पूर्ण;

बाह्य पूर्णांक sclp_init_state;
बाह्य पूर्णांक sclp_console_pages;
बाह्य पूर्णांक sclp_console_drop;
बाह्य अचिन्हित दीर्घ sclp_console_full;
बाह्य bool sclp_mask_compat_mode;

बाह्य अक्षर *sclp_early_sccb;

व्योम sclp_early_रुको_irq(व्योम);
पूर्णांक sclp_early_cmd(sclp_cmdw_t cmd, व्योम *sccb);
अचिन्हित पूर्णांक sclp_early_con_check_linemode(काष्ठा init_sccb *sccb);
अचिन्हित पूर्णांक sclp_early_con_check_vt220(काष्ठा init_sccb *sccb);
पूर्णांक sclp_early_set_event_mask(काष्ठा init_sccb *sccb,
			      sccb_mask_t receive_mask,
			      sccb_mask_t send_mask);
काष्ठा पढ़ो_info_sccb * __init sclp_early_get_info(व्योम);

/* useful अंतरभूतs */

/* Perक्रमm service call. Return 0 on success, non-zero otherwise. */
अटल अंतरभूत पूर्णांक sclp_service_call(sclp_cmdw_t command, व्योम *sccb)
अणु
	पूर्णांक cc = 4; /* Initialize क्रम program check handling */

	यंत्र अस्थिर(
		"0:	.insn	rre,0xb2200000,%1,%2\n"	 /* servc %1,%2 */
		"1:	ipm	%0\n"
		"	srl	%0,28\n"
		"2:\n"
		EX_TABLE(0b, 2b)
		EX_TABLE(1b, 2b)
		: "+&d" (cc) : "d" (command), "a" ((अचिन्हित दीर्घ)sccb)
		: "cc", "memory");
	अगर (cc == 4)
		वापस -EINVAL;
	अगर (cc == 3)
		वापस -EIO;
	अगर (cc == 2)
		वापस -EBUSY;
	वापस 0;
पूर्ण

/* VM uses EBCDIC 037, LPAR+native(SE+HMC) use EBCDIC 500 */
/* translate single अक्षरacter from ASCII to EBCDIC */
अटल अंतरभूत अचिन्हित अक्षर
sclp_ascebc(अचिन्हित अक्षर ch)
अणु
	वापस (MACHINE_IS_VM) ? _ascebc[ch] : _ascebc_500[ch];
पूर्ण

/* translate string from EBCDIC to ASCII */
अटल अंतरभूत व्योम
sclp_ebcasc_str(अक्षर *str, पूर्णांक nr)
अणु
	(MACHINE_IS_VM) ? EBCASC(str, nr) : EBCASC_500(str, nr);
पूर्ण

/* translate string from ASCII to EBCDIC */
अटल अंतरभूत व्योम
sclp_ascebc_str(अक्षर *str, पूर्णांक nr)
अणु
	(MACHINE_IS_VM) ? ASCEBC(str, nr) : ASCEBC_500(str, nr);
पूर्ण

अटल अंतरभूत काष्ठा gds_vector *
sclp_find_gds_vector(व्योम *start, व्योम *end, u16 id)
अणु
	काष्ठा gds_vector *v;

	क्रम (v = start; (व्योम *) v < end; v = (व्योम *) v + v->length)
		अगर (v->gds_id == id)
			वापस v;
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा gds_subvector *
sclp_find_gds_subvector(व्योम *start, व्योम *end, u8 key)
अणु
	काष्ठा gds_subvector *sv;

	क्रम (sv = start; (व्योम *) sv < end; sv = (व्योम *) sv + sv->length)
		अगर (sv->key == key)
			वापस sv;
	वापस शून्य;
पूर्ण

#पूर्ण_अगर	 /* __SCLP_H__ */
