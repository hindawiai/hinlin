<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Driver क्रम 53c700 and 53c700-66 chips from NCR and Symbios
 *
 * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com
 */

#अगर_अघोषित _53C700_H
#घोषणा _53C700_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>

/* Turn on क्रम general debugging---too verbose क्रम normal use */
#अघोषित	NCR_700_DEBUG
/* Debug the tag queues, checking hash queue allocation and deallocation
 * and search क्रम duplicate tags */
#अघोषित NCR_700_TAG_DEBUG

#अगर_घोषित NCR_700_DEBUG
#घोषणा DEBUG(x)	prपूर्णांकk x
#घोषणा DDEBUG(prefix, sdev, fmt, a...) \
	sdev_prपूर्णांकk(prefix, sdev, fmt, ##a)
#घोषणा CDEBUG(prefix, scmd, fmt, a...) \
	scmd_prपूर्णांकk(prefix, scmd, fmt, ##a)
#अन्यथा
#घोषणा DEBUG(x)	करो अणुपूर्ण जबतक (0)
#घोषणा DDEBUG(prefix, scmd, fmt, a...) करो अणुपूर्ण जबतक (0)
#घोषणा CDEBUG(prefix, scmd, fmt, a...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* The number of available command slots */
#घोषणा NCR_700_COMMAND_SLOTS_PER_HOST	64
/* The maximum number of Scatter Gathers we allow */
#घोषणा NCR_700_SG_SEGMENTS		32
/* The maximum number of luns (make this of the क्रमm 2^n) */
#घोषणा NCR_700_MAX_LUNS		32
#घोषणा NCR_700_LUN_MASK		(NCR_700_MAX_LUNS - 1)
/* Maximum number of tags the driver ever allows per device */
#घोषणा NCR_700_MAX_TAGS		16
/* Tag depth the driver starts out with (can be altered in sysfs) */
#घोषणा NCR_700_DEFAULT_TAGS		4
/* This is the शेष number of commands per LUN in the untagged हाल.
 * two is a good value because it means we can have one command active and
 * one command fully prepared and रुकोing
 */
#घोषणा NCR_700_CMD_PER_LUN		2
/* magic byte identअगरying an पूर्णांकernally generated REQUEST_SENSE command */
#घोषणा NCR_700_INTERNAL_SENSE_MAGIC	0x42

काष्ठा NCR_700_Host_Parameters;

/* These are the बाह्यally used routines */
काष्ठा Scsi_Host *NCR_700_detect(काष्ठा scsi_host_ढाँचा *,
		काष्ठा NCR_700_Host_Parameters *, काष्ठा device *);
पूर्णांक NCR_700_release(काष्ठा Scsi_Host *host);
irqवापस_t NCR_700_पूर्णांकr(पूर्णांक, व्योम *);


क्रमागत NCR_700_Host_State अणु
	NCR_700_HOST_BUSY,
	NCR_700_HOST_FREE,
पूर्ण;

काष्ठा NCR_700_SG_List अणु
	/* The following is a script fragment to move the buffer onto the
	 * bus and then link the next fragment or वापस */
	#घोषणा	SCRIPT_MOVE_DATA_IN		0x09000000
	#घोषणा	SCRIPT_MOVE_DATA_OUT		0x08000000
	__u32	ins;
	__u32	pAddr;
	#घोषणा	SCRIPT_NOP			0x80000000
	#घोषणा	SCRIPT_RETURN			0x90080000
पूर्ण;

काष्ठा NCR_700_Device_Parameters अणु
	/* space क्रम creating a request sense command. Really, except
	 * क्रम the annoying SCSI-2 requirement क्रम LUN inक्रमmation in
	 * cmnd[1], this could be in अटल storage */
	अचिन्हित अक्षर cmnd[MAX_COMMAND_SIZE];
	__u8	depth;
	काष्ठा scsi_cmnd *current_cmnd;	/* currently active command */
पूर्ण;


/* The SYNC negotiation sequence looks like:
 * 
 * If DEV_NEGOTIATED_SYNC not set, tack and SDTR message on to the
 * initial identअगरy क्रम the device and set DEV_BEGIN_SYNC_NEGOTIATION
 * If we get an SDTR reply, work out the SXFER parameters, squirrel
 * them away here, clear DEV_BEGIN_SYNC_NEGOTIATION and set
 * DEV_NEGOTIATED_SYNC.  If we get a REJECT msg, squirrel
 *
 *
 * 0:7	SXFER_REG negotiated value क्रम this device
 * 8:15 Current queue depth
 * 16	negotiated SYNC flag
 * 17 begin SYNC negotiation flag 
 * 18 device supports tag queueing */
#घोषणा NCR_700_DEV_NEGOTIATED_SYNC	(1<<16)
#घोषणा NCR_700_DEV_BEGIN_SYNC_NEGOTIATION	(1<<17)
#घोषणा NCR_700_DEV_PRINT_SYNC_NEGOTIATION (1<<19)

अटल अंतरभूत अक्षर *NCR_700_get_sense_cmnd(काष्ठा scsi_device *SDp)
अणु
	काष्ठा NCR_700_Device_Parameters *hostdata = SDp->hostdata;

	वापस hostdata->cmnd;
पूर्ण

अटल अंतरभूत व्योम
NCR_700_set_depth(काष्ठा scsi_device *SDp, __u8 depth)
अणु
	काष्ठा NCR_700_Device_Parameters *hostdata = SDp->hostdata;

	hostdata->depth = depth;
पूर्ण
अटल अंतरभूत __u8
NCR_700_get_depth(काष्ठा scsi_device *SDp)
अणु
	काष्ठा NCR_700_Device_Parameters *hostdata = SDp->hostdata;

	वापस hostdata->depth;
पूर्ण
अटल अंतरभूत पूर्णांक
NCR_700_is_flag_set(काष्ठा scsi_device *SDp, __u32 flag)
अणु
	वापस (spi_flags(SDp->sdev_target) & flag) == flag;
पूर्ण
अटल अंतरभूत पूर्णांक
NCR_700_is_flag_clear(काष्ठा scsi_device *SDp, __u32 flag)
अणु
	वापस (spi_flags(SDp->sdev_target) & flag) == 0;
पूर्ण
अटल अंतरभूत व्योम
NCR_700_set_flag(काष्ठा scsi_device *SDp, __u32 flag)
अणु
	spi_flags(SDp->sdev_target) |= flag;
पूर्ण
अटल अंतरभूत व्योम
NCR_700_clear_flag(काष्ठा scsi_device *SDp, __u32 flag)
अणु
	spi_flags(SDp->sdev_target) &= ~flag;
पूर्ण

क्रमागत NCR_700_tag_neg_state अणु
	NCR_700_START_TAG_NEGOTIATION = 0,
	NCR_700_DURING_TAG_NEGOTIATION = 1,
	NCR_700_FINISHED_TAG_NEGOTIATION = 2,
पूर्ण;

अटल अंतरभूत क्रमागत NCR_700_tag_neg_state
NCR_700_get_tag_neg_state(काष्ठा scsi_device *SDp)
अणु
	वापस (क्रमागत NCR_700_tag_neg_state)((spi_flags(SDp->sdev_target)>>20) & 0x3);
पूर्ण

अटल अंतरभूत व्योम
NCR_700_set_tag_neg_state(काष्ठा scsi_device *SDp,
			  क्रमागत NCR_700_tag_neg_state state)
अणु
	/* clear the slot */
	spi_flags(SDp->sdev_target) &= ~(0x3 << 20);
	spi_flags(SDp->sdev_target) |= ((__u32)state) << 20;
पूर्ण

काष्ठा NCR_700_command_slot अणु
	काष्ठा NCR_700_SG_List	SG[NCR_700_SG_SEGMENTS+1];
	काष्ठा NCR_700_SG_List	*pSG;
	#घोषणा NCR_700_SLOT_MASK 0xFC
	#घोषणा NCR_700_SLOT_MAGIC 0xb8
	#घोषणा	NCR_700_SLOT_FREE (0|NCR_700_SLOT_MAGIC) /* slot may be used */
	#घोषणा NCR_700_SLOT_BUSY (1|NCR_700_SLOT_MAGIC) /* slot has command active on HA */
	#घोषणा NCR_700_SLOT_QUEUED (2|NCR_700_SLOT_MAGIC) /* slot has command to be made active on HA */
	__u8	state;
	#घोषणा NCR_700_FLAG_AUTOSENSE	0x01
	__u8	flags;
	__u8	pad1[2];	/* Needed क्रम m68k where min alignment is 2 bytes */
	पूर्णांक	tag;
	__u32	resume_offset;
	काष्ठा scsi_cmnd *cmnd;
	/* The pci_mapped address of the actual command in cmnd */
	dma_addr_t	pCmd;
	__u32		temp;
	/* अगर this command is a pci_single mapping, holds the dma address
	 * क्रम later unmapping in the करोne routine */
	dma_addr_t	dma_handle;
	/* historical remnant, now used to link मुक्त commands */
	काष्ठा NCR_700_command_slot *ITL_क्रमw;
पूर्ण;

काष्ठा NCR_700_Host_Parameters अणु
	/* These must be filled in by the calling driver */
	पूर्णांक	घड़ी;			/* board घड़ी speed in MHz */
	व्योम __iomem	*base;		/* the base क्रम the port (copied to host) */
	काष्ठा device	*dev;
	__u32	dmode_extra;	/* adjustable bus settings */
	__u32	dcntl_extra;	/* adjustable bus settings */
	__u32	ctest7_extra;	/* adjustable bus settings */
	__u32	dअगरferential:1;	/* अगर we are dअगरferential */
#अगर_घोषित CONFIG_53C700_LE_ON_BE
	/* This option is क्रम HP only.  Set it अगर your chip is wired क्रम
	 * little endian on this platक्रमm (which is big endian) */
	__u32	क्रमce_le_on_be:1;
#पूर्ण_अगर
	__u32	chip710:1;	/* set अगर really a 710 not 700 */
	__u32	burst_length:4;	/* set to 0 to disable 710 bursting */
	__u32	noncoherent:1;	/* needs to use non-coherent DMA */

	/* NOTHING BELOW HERE NEEDS ALTERING */
	__u32	fast:1;		/* अगर we can alter the SCSI bus घड़ी
                                   speed (so can negiotiate sync) */
	पूर्णांक	sync_घड़ी;	/* The speed of the SYNC core */

	__u32	*script;		/* poपूर्णांकer to script location */
	__u32	pScript;		/* physical mem addr of script */

	क्रमागत NCR_700_Host_State state; /* रक्षित by state lock */
	काष्ठा scsi_cmnd *cmd;
	/* Note: pScript contains the single consistent block of
	 * memory.  All the msgin, msgout and status are allocated in
	 * this memory too (at separate cache lines).  TOTAL_MEM_SIZE
	 * represents the total size of this area */
#घोषणा	MSG_ARRAY_SIZE	8
#घोषणा	MSGOUT_OFFSET	(L1_CACHE_ALIGN(माप(SCRIPT)))
	__u8	*msgout;
#घोषणा MSGIN_OFFSET	(MSGOUT_OFFSET + L1_CACHE_ALIGN(MSG_ARRAY_SIZE))
	__u8	*msgin;
#घोषणा STATUS_OFFSET	(MSGIN_OFFSET + L1_CACHE_ALIGN(MSG_ARRAY_SIZE))
	__u8	*status;
#घोषणा SLOTS_OFFSET	(STATUS_OFFSET + L1_CACHE_ALIGN(MSG_ARRAY_SIZE))
	काष्ठा NCR_700_command_slot	*slots;
#घोषणा	TOTAL_MEM_SIZE	(SLOTS_OFFSET + L1_CACHE_ALIGN(माप(काष्ठा NCR_700_command_slot) * NCR_700_COMMAND_SLOTS_PER_HOST))
	पूर्णांक	saved_slot_position;
	पूर्णांक	command_slot_count; /* रक्षित by state lock */
	__u8	tag_negotiated;
	__u8	rev;
	__u8	reselection_id;
	__u8	min_period;

	/* Free list, singly linked by ITL_क्रमw elements */
	काष्ठा NCR_700_command_slot *मुक्त_list;
	/* Completion क्रम रुकोed क्रम ops, like reset, पात or
	 * device reset.
	 *
	 * NOTE: relies on single thपढ़ोing in the error handler to
	 * have only one outstanding at once */
	काष्ठा completion *eh_complete;
पूर्ण;

/*
 *	53C700 Register Interface - the offset from the Selected base
 *	I/O address */
#अगर_घोषित CONFIG_53C700_LE_ON_BE
#घोषणा bE	(hostdata->क्रमce_le_on_be ? 0 : 3)
#घोषणा	bSWAP	(hostdata->क्रमce_le_on_be)
#घोषणा bEBus	(!hostdata->क्रमce_le_on_be)
#या_अगर defined(__BIG_ENDIAN)
#घोषणा bE	3
#घोषणा bSWAP	0
#या_अगर defined(__LITTLE_ENDIAN)
#घोषणा bE	0
#घोषणा bSWAP	0
#अन्यथा
#त्रुटि "__BIG_ENDIAN or __LITTLE_ENDIAN must be defined, did you include byteorder.h?"
#पूर्ण_अगर
#अगर_अघोषित bEBus
#अगर_घोषित CONFIG_53C700_BE_BUS
#घोषणा bEBus	1
#अन्यथा
#घोषणा bEBus	0
#पूर्ण_अगर
#पूर्ण_अगर
#घोषणा bS_to_cpu(x)	(bSWAP ? le32_to_cpu(x) : (x))
#घोषणा bS_to_host(x)	(bSWAP ? cpu_to_le32(x) : (x))

/* NOTE: These रेजिस्टरs are in the LE रेजिस्टर space only, the required byte
 * swapping is करोne by the NCR_700_अणुपढ़ो|ग_लिखोपूर्ण[b] functions */
#घोषणा	SCNTL0_REG			0x00
#घोषणा		FULL_ARBITRATION	0xc0
#घोषणा 	PARITY			0x08
#घोषणा		ENABLE_PARITY		0x04
#घोषणा 	AUTO_ATN		0x02
#घोषणा	SCNTL1_REG			0x01
#घोषणा 	SLOW_BUS		0x80
#घोषणा		ENABLE_SELECT		0x20
#घोषणा		ASSERT_RST		0x08
#घोषणा		ASSERT_EVEN_PARITY	0x04
#घोषणा	SDID_REG			0x02
#घोषणा	SIEN_REG			0x03
#घोषणा 	PHASE_MM_INT		0x80
#घोषणा 	FUNC_COMP_INT		0x40
#घोषणा 	SEL_TIMEOUT_INT		0x20
#घोषणा 	SELECT_INT		0x10
#घोषणा 	GROSS_ERR_INT		0x08
#घोषणा 	UX_DISC_INT		0x04
#घोषणा 	RST_INT			0x02
#घोषणा 	PAR_ERR_INT		0x01
#घोषणा	SCID_REG			0x04
#घोषणा SXFER_REG			0x05
#घोषणा		ASYNC_OPERATION		0x00
#घोषणा SODL_REG                        0x06
#घोषणा	SOCL_REG			0x07
#घोषणा	SFBR_REG			0x08
#घोषणा	SIDL_REG			0x09
#घोषणा	SBDL_REG			0x0A
#घोषणा	SBCL_REG			0x0B
/* पढ़ो bits */
#घोषणा		SBCL_IO			0x01
/*ग_लिखो bits */
#घोषणा		SYNC_DIV_AS_ASYNC	0x00
#घोषणा		SYNC_DIV_1_0		0x01
#घोषणा		SYNC_DIV_1_5		0x02
#घोषणा		SYNC_DIV_2_0		0x03
#घोषणा	DSTAT_REG			0x0C
#घोषणा		ILGL_INST_DETECTED	0x01
#घोषणा		WATCH_DOG_INTERRUPT	0x02
#घोषणा		SCRIPT_INT_RECEIVED	0x04
#घोषणा		ABORTED			0x10
#घोषणा	SSTAT0_REG			0x0D
#घोषणा		PARITY_ERROR		0x01
#घोषणा		SCSI_RESET_DETECTED	0x02
#घोषणा		UNEXPECTED_DISCONNECT	0x04
#घोषणा		SCSI_GROSS_ERROR	0x08
#घोषणा		SELECTED		0x10
#घोषणा		SELECTION_TIMEOUT	0x20
#घोषणा		FUNCTION_COMPLETE	0x40
#घोषणा		PHASE_MISMATCH 		0x80
#घोषणा	SSTAT1_REG			0x0E
#घोषणा		SIDL_REG_FULL		0x80
#घोषणा		SODR_REG_FULL		0x40
#घोषणा		SODL_REG_FULL		0x20
#घोषणा SSTAT2_REG                      0x0F
#घोषणा CTEST0_REG                      0x14
#घोषणा		BTB_TIMER_DISABLE	0x40
#घोषणा CTEST1_REG                      0x15
#घोषणा CTEST2_REG                      0x16
#घोषणा CTEST3_REG                      0x17
#घोषणा CTEST4_REG                      0x18
#घोषणा         DISABLE_FIFO            0x00
#घोषणा         SLBE                    0x10
#घोषणा         SFWR                    0x08
#घोषणा         BYTE_LANE0              0x04
#घोषणा         BYTE_LANE1              0x05
#घोषणा         BYTE_LANE2              0x06
#घोषणा         BYTE_LANE3              0x07
#घोषणा         SCSI_ZMODE              0x20
#घोषणा         ZMODE                   0x40
#घोषणा CTEST5_REG                      0x19
#घोषणा         MASTER_CONTROL          0x10
#घोषणा         DMA_सूचीECTION           0x08
#घोषणा CTEST7_REG                      0x1B
#घोषणा		BURST_DISABLE		0x80 /* 710 only */
#घोषणा		SEL_TIMEOUT_DISABLE	0x10 /* 710 only */
#घोषणा         DFP                     0x08
#घोषणा         EVP                     0x04
#घोषणा         CTEST7_TT1              0x02
#घोषणा		DIFF			0x01
#घोषणा CTEST6_REG                      0x1A
#घोषणा	TEMP_REG			0x1C
#घोषणा	DFIFO_REG			0x20
#घोषणा		FLUSH_DMA_FIFO		0x80
#घोषणा		CLR_FIFO		0x40
#घोषणा	ISTAT_REG			0x21
#घोषणा		ABORT_OPERATION		0x80
#घोषणा		SOFTWARE_RESET_710	0x40
#घोषणा		DMA_INT_PENDING		0x01
#घोषणा		SCSI_INT_PENDING	0x02
#घोषणा		CONNECTED		0x08
#घोषणा CTEST8_REG                      0x22
#घोषणा         LAST_DIS_ENBL           0x01
#घोषणा		SHORTEN_FILTERING	0x04
#घोषणा		ENABLE_ACTIVE_NEGATION	0x10
#घोषणा		GENERATE_RECEIVE_PARITY	0x20
#घोषणा		CLR_FIFO_710		0x04
#घोषणा		FLUSH_DMA_FIFO_710	0x08
#घोषणा CTEST9_REG                      0x23
#घोषणा	DBC_REG				0x24
#घोषणा	DCMD_REG			0x27
#घोषणा	DNAD_REG			0x28
#घोषणा	DIEN_REG			0x39
#घोषणा		BUS_FAULT		0x20
#घोषणा 	ABORT_INT		0x10
#घोषणा 	INT_INST_INT		0x04
#घोषणा 	WD_INT			0x02
#घोषणा 	ILGL_INST_INT		0x01
#घोषणा	DCNTL_REG			0x3B
#घोषणा		SOFTWARE_RESET		0x01
#घोषणा		COMPAT_700_MODE		0x01
#घोषणा 	SCRPTS_16BITS		0x20
#घोषणा		EA_710			0x20
#घोषणा		ASYNC_DIV_2_0		0x00
#घोषणा		ASYNC_DIV_1_5		0x40
#घोषणा		ASYNC_DIV_1_0		0x80
#घोषणा		ASYNC_DIV_3_0		0xc0
#घोषणा DMODE_710_REG			0x38
#घोषणा	DMODE_700_REG			0x34
#घोषणा		BURST_LENGTH_1		0x00
#घोषणा		BURST_LENGTH_2		0x40
#घोषणा		BURST_LENGTH_4		0x80
#घोषणा		BURST_LENGTH_8		0xC0
#घोषणा		DMODE_FC1		0x10
#घोषणा		DMODE_FC2		0x20
#घोषणा 	BW16			32 
#घोषणा 	MODE_286		16
#घोषणा 	IO_XFER			8
#घोषणा 	FIXED_ADDR		4

#घोषणा DSP_REG                         0x2C
#घोषणा DSPS_REG                        0x30

/* Parameters to begin SDTR negotiations.  Empirically, I find that
 * the 53c700-66 cannot handle an offset >8, so करोn't change this  */
#घोषणा NCR_700_MAX_OFFSET	8
/* Was hoping the max offset would be greater क्रम the 710, but
 * empirically it seems to be 8 also */
#घोषणा NCR_710_MAX_OFFSET	8
#घोषणा NCR_700_MIN_XFERP	1
#घोषणा NCR_710_MIN_XFERP	0
#घोषणा NCR_700_MIN_PERIOD	25 /* क्रम SDTR message, 100ns */

#घोषणा script_patch_32(h, script, symbol, value) \
अणु \
	पूर्णांक i; \
	dma_addr_t da = value; \
	क्रम(i=0; i< (माप(A_##symbol##_used) / माप(__u32)); i++) अणु \
		__u32 val = bS_to_cpu((script)[A_##symbol##_used[i]]) + da; \
		(script)[A_##symbol##_used[i]] = bS_to_host(val); \
		dma_sync_to_dev((h), &(script)[A_##symbol##_used[i]], 4); \
		DEBUG((" script, patching %s at %d to %pad\n", \
		       #symbol, A_##symbol##_used[i], &da)); \
	पूर्ण \
पूर्ण

#घोषणा script_patch_32_असल(h, script, symbol, value) \
अणु \
	पूर्णांक i; \
	dma_addr_t da = value; \
	क्रम(i=0; i< (माप(A_##symbol##_used) / माप(__u32)); i++) अणु \
		(script)[A_##symbol##_used[i]] = bS_to_host(da); \
		dma_sync_to_dev((h), &(script)[A_##symbol##_used[i]], 4); \
		DEBUG((" script, patching %s at %d to %pad\n", \
		       #symbol, A_##symbol##_used[i], &da)); \
	पूर्ण \
पूर्ण

/* Used क्रम patching the SCSI ID in the SELECT inकाष्ठाion */
#घोषणा script_patch_ID(h, script, symbol, value) \
अणु \
	पूर्णांक i; \
	क्रम(i=0; i< (माप(A_##symbol##_used) / माप(__u32)); i++) अणु \
		__u32 val = bS_to_cpu((script)[A_##symbol##_used[i]]); \
		val &= 0xff00ffff; \
		val |= ((value) & 0xff) << 16; \
		(script)[A_##symbol##_used[i]] = bS_to_host(val); \
		dma_sync_to_dev((h), &(script)[A_##symbol##_used[i]], 4); \
		DEBUG((" script, patching ID field %s at %d to 0x%x\n", \
		       #symbol, A_##symbol##_used[i], val)); \
	पूर्ण \
पूर्ण

#घोषणा script_patch_16(h, script, symbol, value) \
अणु \
	पूर्णांक i; \
	क्रम(i=0; i< (माप(A_##symbol##_used) / माप(__u32)); i++) अणु \
		__u32 val = bS_to_cpu((script)[A_##symbol##_used[i]]); \
		val &= 0xffff0000; \
		val |= ((value) & 0xffff); \
		(script)[A_##symbol##_used[i]] = bS_to_host(val); \
		dma_sync_to_dev((h), &(script)[A_##symbol##_used[i]], 4); \
		DEBUG((" script, patching short field %s at %d to 0x%x\n", \
		       #symbol, A_##symbol##_used[i], val)); \
	पूर्ण \
पूर्ण


अटल अंतरभूत __u8
NCR_700_पढ़ोb(काष्ठा Scsi_Host *host, __u32 reg)
अणु
	स्थिर काष्ठा NCR_700_Host_Parameters *hostdata
		= (काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];

	वापस ioपढ़ो8(hostdata->base + (reg^bE));
पूर्ण

अटल अंतरभूत __u32
NCR_700_पढ़ोl(काष्ठा Scsi_Host *host, __u32 reg)
अणु
	स्थिर काष्ठा NCR_700_Host_Parameters *hostdata
		= (काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];
	__u32 value = bEBus ? ioपढ़ो32be(hostdata->base + reg) :
		ioपढ़ो32(hostdata->base + reg);
#अगर 1
	/* sanity check the रेजिस्टर */
	BUG_ON((reg & 0x3) != 0);
#पूर्ण_अगर

	वापस value;
पूर्ण

अटल अंतरभूत व्योम
NCR_700_ग_लिखोb(__u8 value, काष्ठा Scsi_Host *host, __u32 reg)
अणु
	स्थिर काष्ठा NCR_700_Host_Parameters *hostdata
		= (काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];

	ioग_लिखो8(value, hostdata->base + (reg^bE));
पूर्ण

अटल अंतरभूत व्योम
NCR_700_ग_लिखोl(__u32 value, काष्ठा Scsi_Host *host, __u32 reg)
अणु
	स्थिर काष्ठा NCR_700_Host_Parameters *hostdata
		= (काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];

#अगर 1
	/* sanity check the रेजिस्टर */
	BUG_ON((reg & 0x3) != 0);
#पूर्ण_अगर

	bEBus ? ioग_लिखो32be(value, hostdata->base + reg): 
		ioग_लिखो32(value, hostdata->base + reg);
पूर्ण

#पूर्ण_अगर
