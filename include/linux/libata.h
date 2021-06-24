<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright 2003-2005 Red Hat, Inc.  All rights reserved.
 *  Copyright 2003-2005 Jeff Garzik
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 */

#अगर_अघोषित __LINUX_LIBATA_H__
#घोषणा __LINUX_LIBATA_H__

#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/पन.स>
#समावेश <linux/ata.h>
#समावेश <linux/workqueue.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/acpi.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/sched.h>
#समावेश <linux/async.h>

/*
 * Define अगर arch has non-standard setup.  This is a _PCI_ standard
 * not a legacy or ISA standard.
 */
#अगर_घोषित CONFIG_ATA_NONSTANDARD
#समावेश <यंत्र/libata-porपंचांगap.h>
#अन्यथा
#घोषणा ATA_PRIMARY_IRQ(dev)	14
#घोषणा ATA_SECONDARY_IRQ(dev)	15
#पूर्ण_अगर

/*
 * compile-समय options: to be हटाओd as soon as all the drivers are
 * converted to the new debugging mechanism
 */
#अघोषित ATA_DEBUG		/* debugging output */
#अघोषित ATA_VERBOSE_DEBUG	/* yet more debugging output */
#अघोषित ATA_IRQ_TRAP		/* define to ack screaming irqs */
#अघोषित ATA_न_संशोधन		/* define to disable quick runसमय checks */


/* note: prपूर्णांकs function name क्रम you */
#अगर_घोषित ATA_DEBUG
#घोषणा DPRINTK(fmt, args...) prपूर्णांकk(KERN_ERR "%s: " fmt, __func__, ## args)
#अगर_घोषित ATA_VERBOSE_DEBUG
#घोषणा VPRINTK(fmt, args...) prपूर्णांकk(KERN_ERR "%s: " fmt, __func__, ## args)
#अन्यथा
#घोषणा VPRINTK(fmt, args...)
#पूर्ण_अगर	/* ATA_VERBOSE_DEBUG */
#अन्यथा
#घोषणा DPRINTK(fmt, args...)
#घोषणा VPRINTK(fmt, args...)
#पूर्ण_अगर	/* ATA_DEBUG */

#घोषणा ata_prपूर्णांक_version_once(dev, version)			\
(अणु								\
	अटल bool __prपूर्णांक_once;				\
								\
	अगर (!__prपूर्णांक_once) अणु					\
		__prपूर्णांक_once = true;				\
		ata_prपूर्णांक_version(dev, version);		\
	पूर्ण							\
पूर्ण)

/* NEW: debug levels */
#घोषणा HAVE_LIBATA_MSG 1

क्रमागत अणु
	ATA_MSG_DRV	= 0x0001,
	ATA_MSG_INFO	= 0x0002,
	ATA_MSG_PROBE	= 0x0004,
	ATA_MSG_WARN	= 0x0008,
	ATA_MSG_MALLOC	= 0x0010,
	ATA_MSG_CTL	= 0x0020,
	ATA_MSG_INTR	= 0x0040,
	ATA_MSG_ERR	= 0x0080,
पूर्ण;

#घोषणा ata_msg_drv(p)    ((p)->msg_enable & ATA_MSG_DRV)
#घोषणा ata_msg_info(p)   ((p)->msg_enable & ATA_MSG_INFO)
#घोषणा ata_msg_probe(p)  ((p)->msg_enable & ATA_MSG_PROBE)
#घोषणा ata_msg_warn(p)   ((p)->msg_enable & ATA_MSG_WARN)
#घोषणा ata_msg_दो_स्मृति(p) ((p)->msg_enable & ATA_MSG_MALLOC)
#घोषणा ata_msg_ctl(p)    ((p)->msg_enable & ATA_MSG_CTL)
#घोषणा ata_msg_पूर्णांकr(p)   ((p)->msg_enable & ATA_MSG_INTR)
#घोषणा ata_msg_err(p)    ((p)->msg_enable & ATA_MSG_ERR)

अटल अंतरभूत u32 ata_msg_init(पूर्णांक dval, पूर्णांक शेष_msg_enable_bits)
अणु
	अगर (dval < 0 || dval >= (माप(u32) * 8))
		वापस शेष_msg_enable_bits; /* should be 0x1 - only driver info msgs */
	अगर (!dval)
		वापस 0;
	वापस (1 << dval) - 1;
पूर्ण

/* defines only क्रम the स्थिरants which करोn't work well as क्रमागतs */
#घोषणा ATA_TAG_POISON		0xfafbfcfdU

क्रमागत अणु
	/* various global स्थिरants */
	LIBATA_MAX_PRD		= ATA_MAX_PRD / 2,
	LIBATA_DUMB_MAX_PRD	= ATA_MAX_PRD / 4,	/* Worst हाल */
	ATA_DEF_QUEUE		= 1,
	ATA_MAX_QUEUE		= 32,
	ATA_TAG_INTERNAL	= ATA_MAX_QUEUE,
	ATA_SHORT_PAUSE		= 16,

	ATAPI_MAX_DRAIN		= 16 << 10,

	ATA_ALL_DEVICES		= (1 << ATA_MAX_DEVICES) - 1,

	ATA_SHT_EMULATED	= 1,
	ATA_SHT_THIS_ID		= -1,

	/* काष्ठा ata_taskfile flags */
	ATA_TFLAG_LBA48		= (1 << 0), /* enable 48-bit LBA and "HOB" */
	ATA_TFLAG_ISADDR	= (1 << 1), /* enable r/w to nsect/lba regs */
	ATA_TFLAG_DEVICE	= (1 << 2), /* enable r/w to device reg */
	ATA_TFLAG_WRITE		= (1 << 3), /* data dir: host->dev==1 (ग_लिखो) */
	ATA_TFLAG_LBA		= (1 << 4), /* enable LBA */
	ATA_TFLAG_FUA		= (1 << 5), /* enable FUA */
	ATA_TFLAG_POLLING	= (1 << 6), /* set nIEN to 1 and use polling */

	/* काष्ठा ata_device stuff */
	ATA_DFLAG_LBA		= (1 << 0), /* device supports LBA */
	ATA_DFLAG_LBA48		= (1 << 1), /* device supports LBA48 */
	ATA_DFLAG_CDB_INTR	= (1 << 2), /* device निश्चितs INTRQ when पढ़ोy क्रम CDB */
	ATA_DFLAG_NCQ		= (1 << 3), /* device supports NCQ */
	ATA_DFLAG_FLUSH_EXT	= (1 << 4), /* करो FLUSH_EXT instead of FLUSH */
	ATA_DFLAG_ACPI_PENDING	= (1 << 5), /* ACPI resume action pending */
	ATA_DFLAG_ACPI_FAILED	= (1 << 6), /* ACPI on devcfg has failed */
	ATA_DFLAG_AN		= (1 << 7), /* AN configured */
	ATA_DFLAG_TRUSTED	= (1 << 8), /* device supports trusted send/recv */
	ATA_DFLAG_DMAसूची	= (1 << 10), /* device requires DMAसूची */
	ATA_DFLAG_CFG_MASK	= (1 << 12) - 1,

	ATA_DFLAG_PIO		= (1 << 12), /* device limited to PIO mode */
	ATA_DFLAG_NCQ_OFF	= (1 << 13), /* device limited to non-NCQ mode */
	ATA_DFLAG_SLEEPING	= (1 << 15), /* device is sleeping */
	ATA_DFLAG_DUBIOUS_XFER	= (1 << 16), /* data transfer not verअगरied */
	ATA_DFLAG_NO_UNLOAD	= (1 << 17), /* device करोesn't support unload */
	ATA_DFLAG_UNLOCK_HPA	= (1 << 18), /* unlock HPA */
	ATA_DFLAG_NCQ_SEND_RECV = (1 << 19), /* device supports NCQ SEND and RECV */
	ATA_DFLAG_NCQ_PRIO	= (1 << 20), /* device supports NCQ priority */
	ATA_DFLAG_NCQ_PRIO_ENABLE = (1 << 21), /* Priority cmds sent to dev */
	ATA_DFLAG_INIT_MASK	= (1 << 24) - 1,

	ATA_DFLAG_DETACH	= (1 << 24),
	ATA_DFLAG_DETACHED	= (1 << 25),

	ATA_DFLAG_DA		= (1 << 26), /* device supports Device Attention */
	ATA_DFLAG_DEVSLP	= (1 << 27), /* device supports Device Sleep */
	ATA_DFLAG_ACPI_DISABLED = (1 << 28), /* ACPI क्रम the device is disabled */
	ATA_DFLAG_D_SENSE	= (1 << 29), /* Descriptor sense requested */
	ATA_DFLAG_ZAC		= (1 << 30), /* ZAC device */

	ATA_DEV_UNKNOWN		= 0,	/* unknown device */
	ATA_DEV_ATA		= 1,	/* ATA device */
	ATA_DEV_ATA_UNSUP	= 2,	/* ATA device (unsupported) */
	ATA_DEV_ATAPI		= 3,	/* ATAPI device */
	ATA_DEV_ATAPI_UNSUP	= 4,	/* ATAPI device (unsupported) */
	ATA_DEV_PMP		= 5,	/* SATA port multiplier */
	ATA_DEV_PMP_UNSUP	= 6,	/* SATA port multiplier (unsupported) */
	ATA_DEV_SEMB		= 7,	/* SEMB */
	ATA_DEV_SEMB_UNSUP	= 8,	/* SEMB (unsupported) */
	ATA_DEV_ZAC		= 9,	/* ZAC device */
	ATA_DEV_ZAC_UNSUP	= 10,	/* ZAC device (unsupported) */
	ATA_DEV_NONE		= 11,	/* no device */

	/* काष्ठा ata_link flags */
	/* NOTE: काष्ठा ata_क्रमce_param currently stores lflags in u16 */
	ATA_LFLAG_NO_HRST	= (1 << 1), /* aव्योम hardreset */
	ATA_LFLAG_NO_SRST	= (1 << 2), /* aव्योम softreset */
	ATA_LFLAG_ASSUME_ATA	= (1 << 3), /* assume ATA class */
	ATA_LFLAG_ASSUME_SEMB	= (1 << 4), /* assume SEMB class */
	ATA_LFLAG_ASSUME_CLASS	= ATA_LFLAG_ASSUME_ATA | ATA_LFLAG_ASSUME_SEMB,
	ATA_LFLAG_NO_RETRY	= (1 << 5), /* करोn't retry this link */
	ATA_LFLAG_DISABLED	= (1 << 6), /* link is disabled */
	ATA_LFLAG_SW_ACTIVITY	= (1 << 7), /* keep activity stats */
	ATA_LFLAG_NO_LPM	= (1 << 8), /* disable LPM on this link */
	ATA_LFLAG_RST_ONCE	= (1 << 9), /* limit recovery to one reset */
	ATA_LFLAG_CHANGED	= (1 << 10), /* LPM state changed on this link */
	ATA_LFLAG_NO_DB_DELAY	= (1 << 11), /* no debounce delay on link resume */

	/* काष्ठा ata_port flags */
	ATA_FLAG_SLAVE_POSS	= (1 << 0), /* host supports slave dev */
					    /* (करोesn't imply presence) */
	ATA_FLAG_SATA		= (1 << 1),
	ATA_FLAG_NO_LPM		= (1 << 2), /* host not happy with LPM */
	ATA_FLAG_NO_LOG_PAGE	= (1 << 5), /* करो not issue log page पढ़ो */
	ATA_FLAG_NO_ATAPI	= (1 << 6), /* No ATAPI support */
	ATA_FLAG_PIO_DMA	= (1 << 7), /* PIO cmds via DMA */
	ATA_FLAG_PIO_LBA48	= (1 << 8), /* Host DMA engine is LBA28 only */
	ATA_FLAG_PIO_POLLING	= (1 << 9), /* use polling PIO अगर LLD
					     * करोesn't handle PIO पूर्णांकerrupts */
	ATA_FLAG_NCQ		= (1 << 10), /* host supports NCQ */
	ATA_FLAG_NO_POWEROFF_SPINDOWN = (1 << 11), /* करोn't spinकरोwn beक्रमe घातeroff */
	ATA_FLAG_NO_HIBERNATE_SPINDOWN = (1 << 12), /* करोn't spinकरोwn beक्रमe hibernation */
	ATA_FLAG_DEBUGMSG	= (1 << 13),
	ATA_FLAG_FPDMA_AA		= (1 << 14), /* driver supports Auto-Activate */
	ATA_FLAG_IGN_SIMPLEX	= (1 << 15), /* ignore SIMPLEX */
	ATA_FLAG_NO_IORDY	= (1 << 16), /* controller lacks iordy */
	ATA_FLAG_ACPI_SATA	= (1 << 17), /* need native SATA ACPI layout */
	ATA_FLAG_AN		= (1 << 18), /* controller supports AN */
	ATA_FLAG_PMP		= (1 << 19), /* controller supports PMP */
	ATA_FLAG_FPDMA_AUX	= (1 << 20), /* controller supports H2DFIS aux field */
	ATA_FLAG_EM		= (1 << 21), /* driver supports enclosure
					      * management */
	ATA_FLAG_SW_ACTIVITY	= (1 << 22), /* driver supports sw activity
					      * led */
	ATA_FLAG_NO_DIPM	= (1 << 23), /* host not happy with DIPM */
	ATA_FLAG_SAS_HOST	= (1 << 24), /* SAS host */

	/* bits 24:31 of ap->flags are reserved क्रम LLD specअगरic flags */


	/* काष्ठा ata_port pflags */
	ATA_PFLAG_EH_PENDING	= (1 << 0), /* EH pending */
	ATA_PFLAG_EH_IN_PROGRESS = (1 << 1), /* EH in progress */
	ATA_PFLAG_FROZEN	= (1 << 2), /* port is frozen */
	ATA_PFLAG_RECOVERED	= (1 << 3), /* recovery action perक्रमmed */
	ATA_PFLAG_LOADING	= (1 << 4), /* boot/loading probe */
	ATA_PFLAG_SCSI_HOTPLUG	= (1 << 6), /* SCSI hotplug scheduled */
	ATA_PFLAG_INITIALIZING	= (1 << 7), /* being initialized, करोn't touch */
	ATA_PFLAG_RESETTING	= (1 << 8), /* reset in progress */
	ATA_PFLAG_UNLOADING	= (1 << 9), /* driver is being unloaded */
	ATA_PFLAG_UNLOADED	= (1 << 10), /* driver is unloaded */

	ATA_PFLAG_SUSPENDED	= (1 << 17), /* port is suspended (घातer) */
	ATA_PFLAG_PM_PENDING	= (1 << 18), /* PM operation pending */
	ATA_PFLAG_INIT_GTM_VALID = (1 << 19), /* initial gपंचांग data valid */

	ATA_PFLAG_PIO32		= (1 << 20),  /* 32bit PIO */
	ATA_PFLAG_PIO32CHANGE	= (1 << 21),  /* 32bit PIO can be turned on/off */
	ATA_PFLAG_EXTERNAL	= (1 << 22),  /* eSATA/बाह्यal port */

	/* काष्ठा ata_queued_cmd flags */
	ATA_QCFLAG_ACTIVE	= (1 << 0), /* cmd not yet ack'd to scsi lyer */
	ATA_QCFLAG_DMAMAP	= (1 << 1), /* SG table is DMA mapped */
	ATA_QCFLAG_IO		= (1 << 3), /* standard IO command */
	ATA_QCFLAG_RESULT_TF	= (1 << 4), /* result TF requested */
	ATA_QCFLAG_CLEAR_EXCL	= (1 << 5), /* clear excl_link on completion */
	ATA_QCFLAG_QUIET	= (1 << 6), /* करोn't report device error */
	ATA_QCFLAG_RETRY	= (1 << 7), /* retry after failure */

	ATA_QCFLAG_FAILED	= (1 << 16), /* cmd failed and is owned by EH */
	ATA_QCFLAG_SENSE_VALID	= (1 << 17), /* sense data valid */
	ATA_QCFLAG_EH_SCHEDULED = (1 << 18), /* EH scheduled (obsolete) */

	/* host set flags */
	ATA_HOST_SIMPLEX	= (1 << 0),	/* Host is simplex, one DMA channel per host only */
	ATA_HOST_STARTED	= (1 << 1),	/* Host started */
	ATA_HOST_PARALLEL_SCAN	= (1 << 2),	/* Ports on this host can be scanned in parallel */
	ATA_HOST_IGNORE_ATA	= (1 << 3),	/* Ignore ATA devices on this host. */

	/* bits 24:31 of host->flags are reserved क्रम LLD specअगरic flags */

	/* various lengths of समय */
	ATA_TMOUT_BOOT		= 30000,	/* heuristic */
	ATA_TMOUT_BOOT_QUICK	=  7000,	/* heuristic */
	ATA_TMOUT_INTERNAL_QUICK = 5000,
	ATA_TMOUT_MAX_PARK	= 30000,

	/*
	 * GoVault needs 2s and iVDR disk HHD424020F7SV00 800ms.  2s
	 * is too much without parallel probing.  Use 2s अगर parallel
	 * probing is available, 800ms otherwise.
	 */
	ATA_TMOUT_FF_WAIT_LONG	=  2000,
	ATA_TMOUT_FF_WAIT	=   800,

	/* Spec mandates to रुको क्रम ">= 2ms" beक्रमe checking status
	 * after reset.  We रुको 150ms, because that was the magic
	 * delay used क्रम ATAPI devices in Hale Landis's ATADRVR, क्रम
	 * the period of समय between when the ATA command रेजिस्टर is
	 * written, and then status is checked.  Because रुकोing क्रम
	 * "a while" beक्रमe checking status is fine, post SRST, we
	 * perक्रमm this magic delay here as well.
	 *
	 * Old drivers/ide uses the 2mS rule and then रुकोs क्रम पढ़ोy.
	 */
	ATA_WAIT_AFTER_RESET	=  150,

	/* If PMP is supported, we have to करो follow-up SRST.  As some
	 * PMPs करोn't send D2H Reg FIS after hardreset, LLDs are
	 * advised to रुको only क्रम the following duration beक्रमe
	 * करोing SRST.
	 */
	ATA_TMOUT_PMP_SRST_WAIT	= 5000,

	/* When the LPM policy is set to ATA_LPM_MAX_POWER, there might
	 * be a spurious PHY event, so ignore the first PHY event that
	 * occurs within 10s after the policy change.
	 */
	ATA_TMOUT_SPURIOUS_PHY	= 10000,

	/* ATA bus states */
	BUS_UNKNOWN		= 0,
	BUS_DMA			= 1,
	BUS_IDLE		= 2,
	BUS_NOINTR		= 3,
	BUS_NODATA		= 4,
	BUS_TIMER		= 5,
	BUS_PIO			= 6,
	BUS_EDD			= 7,
	BUS_IDENTIFY		= 8,
	BUS_PACKET		= 9,

	/* SATA port states */
	PORT_UNKNOWN		= 0,
	PORT_ENABLED		= 1,
	PORT_DISABLED		= 2,

	/* encoding various smaller biपंचांगaps पूर्णांकo a single
	 * अचिन्हित दीर्घ biपंचांगap
	 */
	ATA_NR_PIO_MODES	= 7,
	ATA_NR_MWDMA_MODES	= 5,
	ATA_NR_UDMA_MODES	= 8,

	ATA_SHIFT_PIO		= 0,
	ATA_SHIFT_MWDMA		= ATA_SHIFT_PIO + ATA_NR_PIO_MODES,
	ATA_SHIFT_UDMA		= ATA_SHIFT_MWDMA + ATA_NR_MWDMA_MODES,
	ATA_SHIFT_PRIO		= 6,

	ATA_PRIO_HIGH		= 2,
	/* size of buffer to pad xfers ending on unaligned boundaries */
	ATA_DMA_PAD_SZ		= 4,

	/* ering size */
	ATA_ERING_SIZE		= 32,

	/* वापस values क्रम ->qc_defer */
	ATA_DEFER_LINK		= 1,
	ATA_DEFER_PORT		= 2,

	/* desc_len क्रम ata_eh_info and context */
	ATA_EH_DESC_LEN		= 80,

	/* reset / recovery action types */
	ATA_EH_REVALIDATE	= (1 << 0),
	ATA_EH_SOFTRESET	= (1 << 1), /* meaningful only in ->prereset */
	ATA_EH_HARDRESET	= (1 << 2), /* meaningful only in ->prereset */
	ATA_EH_RESET		= ATA_EH_SOFTRESET | ATA_EH_HARDRESET,
	ATA_EH_ENABLE_LINK	= (1 << 3),
	ATA_EH_PARK		= (1 << 5), /* unload heads and stop I/O */

	ATA_EH_PERDEV_MASK	= ATA_EH_REVALIDATE | ATA_EH_PARK,
	ATA_EH_ALL_ACTIONS	= ATA_EH_REVALIDATE | ATA_EH_RESET |
				  ATA_EH_ENABLE_LINK,

	/* ata_eh_info->flags */
	ATA_EHI_HOTPLUGGED	= (1 << 0),  /* could have been hotplugged */
	ATA_EHI_NO_AUTOPSY	= (1 << 2),  /* no स्वतःpsy */
	ATA_EHI_QUIET		= (1 << 3),  /* be quiet */
	ATA_EHI_NO_RECOVERY	= (1 << 4),  /* no recovery */

	ATA_EHI_DID_SOFTRESET	= (1 << 16), /* alपढ़ोy soft-reset this port */
	ATA_EHI_DID_HARDRESET	= (1 << 17), /* alपढ़ोy soft-reset this port */
	ATA_EHI_PRINTINFO	= (1 << 18), /* prपूर्णांक configuration info */
	ATA_EHI_SETMODE		= (1 << 19), /* configure transfer mode */
	ATA_EHI_POST_SETMODE	= (1 << 20), /* revalidating after seपंचांगode */

	ATA_EHI_DID_RESET	= ATA_EHI_DID_SOFTRESET | ATA_EHI_DID_HARDRESET,

	/* mask of flags to transfer *to* the slave link */
	ATA_EHI_TO_SLAVE_MASK	= ATA_EHI_NO_AUTOPSY | ATA_EHI_QUIET,

	/* max tries अगर error condition is still set after ->error_handler */
	ATA_EH_MAX_TRIES	= 5,

	/* someबार resuming a link requires several retries */
	ATA_LINK_RESUME_TRIES	= 5,

	/* how hard are we gonna try to probe/recover devices */
	ATA_PROBE_MAX_TRIES	= 3,
	ATA_EH_DEV_TRIES	= 3,
	ATA_EH_PMP_TRIES	= 5,
	ATA_EH_PMP_LINK_TRIES	= 3,

	SATA_PMP_RW_TIMEOUT	= 3000,		/* PMP पढ़ो/ग_लिखो समयout */

	/* This should match the actual table size of
	 * ata_eh_cmd_समयout_table in libata-eh.c.
	 */
	ATA_EH_CMD_TIMEOUT_TABLE_SIZE = 6,

	/* Horkage types. May be set by libata or controller on drives
	   (some horkage may be drive/controller pair dependent */

	ATA_HORKAGE_DIAGNOSTIC	= (1 << 0),	/* Failed boot diag */
	ATA_HORKAGE_NODMA	= (1 << 1),	/* DMA problems */
	ATA_HORKAGE_NONCQ	= (1 << 2),	/* Don't use NCQ */
	ATA_HORKAGE_MAX_SEC_128	= (1 << 3),	/* Limit max sects to 128 */
	ATA_HORKAGE_BROKEN_HPA	= (1 << 4),	/* Broken HPA */
	ATA_HORKAGE_DISABLE	= (1 << 5),	/* Disable it */
	ATA_HORKAGE_HPA_SIZE	= (1 << 6),	/* native size off by one */
	ATA_HORKAGE_IVB		= (1 << 8),	/* cbl det validity bit bugs */
	ATA_HORKAGE_STUCK_ERR	= (1 << 9),	/* stuck ERR on next PACKET */
	ATA_HORKAGE_BRIDGE_OK	= (1 << 10),	/* no bridge limits */
	ATA_HORKAGE_ATAPI_MOD16_DMA = (1 << 11), /* use ATAPI DMA क्रम commands
						    not multiple of 16 bytes */
	ATA_HORKAGE_FIRMWARE_WARN = (1 << 12),	/* firmware update warning */
	ATA_HORKAGE_1_5_GBPS	= (1 << 13),	/* क्रमce 1.5 Gbps */
	ATA_HORKAGE_NOSETXFER	= (1 << 14),	/* skip SETXFER, SATA only */
	ATA_HORKAGE_BROKEN_FPDMA_AA	= (1 << 15),	/* skip AA */
	ATA_HORKAGE_DUMP_ID	= (1 << 16),	/* dump IDENTIFY data */
	ATA_HORKAGE_MAX_SEC_LBA48 = (1 << 17),	/* Set max sects to 65535 */
	ATA_HORKAGE_ATAPI_DMAसूची = (1 << 18),	/* device requires dmadir */
	ATA_HORKAGE_NO_NCQ_TRIM	= (1 << 19),	/* करोn't use queued TRIM */
	ATA_HORKAGE_NOLPM	= (1 << 20),	/* करोn't use LPM */
	ATA_HORKAGE_WD_BROKEN_LPM = (1 << 21),	/* some WDs have broken LPM */
	ATA_HORKAGE_ZERO_AFTER_TRIM = (1 << 22),/* guarantees zero after trim */
	ATA_HORKAGE_NO_DMA_LOG	= (1 << 23),	/* करोn't use DMA क्रम log पढ़ो */
	ATA_HORKAGE_NOTRIM	= (1 << 24),	/* करोn't use TRIM */
	ATA_HORKAGE_MAX_SEC_1024 = (1 << 25),	/* Limit max sects to 1024 */
	ATA_HORKAGE_MAX_TRIM_128M = (1 << 26),	/* Limit max trim size to 128M */

	 /* DMA mask क्रम user DMA control: User visible values; DO NOT
	    rक्रमागतber */
	ATA_DMA_MASK_ATA	= (1 << 0),	/* DMA on ATA Disk */
	ATA_DMA_MASK_ATAPI	= (1 << 1),	/* DMA on ATAPI */
	ATA_DMA_MASK_CFA	= (1 << 2),	/* DMA on CF Card */

	/* ATAPI command types */
	ATAPI_READ		= 0,		/* READs */
	ATAPI_WRITE		= 1,		/* WRITEs */
	ATAPI_READ_CD		= 2,		/* READ CD [MSF] */
	ATAPI_PASS_THRU		= 3,		/* SAT pass-thru */
	ATAPI_MISC		= 4,		/* the rest */

	/* Timing स्थिरants */
	ATA_TIMING_SETUP	= (1 << 0),
	ATA_TIMING_ACT8B	= (1 << 1),
	ATA_TIMING_REC8B	= (1 << 2),
	ATA_TIMING_CYC8B	= (1 << 3),
	ATA_TIMING_8BIT		= ATA_TIMING_ACT8B | ATA_TIMING_REC8B |
				  ATA_TIMING_CYC8B,
	ATA_TIMING_ACTIVE	= (1 << 4),
	ATA_TIMING_RECOVER	= (1 << 5),
	ATA_TIMING_DMACK_HOLD	= (1 << 6),
	ATA_TIMING_CYCLE	= (1 << 7),
	ATA_TIMING_UDMA		= (1 << 8),
	ATA_TIMING_ALL		= ATA_TIMING_SETUP | ATA_TIMING_ACT8B |
				  ATA_TIMING_REC8B | ATA_TIMING_CYC8B |
				  ATA_TIMING_ACTIVE | ATA_TIMING_RECOVER |
				  ATA_TIMING_DMACK_HOLD | ATA_TIMING_CYCLE |
				  ATA_TIMING_UDMA,

	/* ACPI स्थिरants */
	ATA_ACPI_FILTER_SETXFER	= 1 << 0,
	ATA_ACPI_FILTER_LOCK	= 1 << 1,
	ATA_ACPI_FILTER_DIPM	= 1 << 2,
	ATA_ACPI_FILTER_FPDMA_OFFSET = 1 << 3,	/* FPDMA non-zero offset */
	ATA_ACPI_FILTER_FPDMA_AA = 1 << 4,	/* FPDMA स्वतः activate */

	ATA_ACPI_FILTER_DEFAULT	= ATA_ACPI_FILTER_SETXFER |
				  ATA_ACPI_FILTER_LOCK |
				  ATA_ACPI_FILTER_DIPM,
पूर्ण;

क्रमागत ata_xfer_mask अणु
	ATA_MASK_PIO		= ((1LU << ATA_NR_PIO_MODES) - 1)
					<< ATA_SHIFT_PIO,
	ATA_MASK_MWDMA		= ((1LU << ATA_NR_MWDMA_MODES) - 1)
					<< ATA_SHIFT_MWDMA,
	ATA_MASK_UDMA		= ((1LU << ATA_NR_UDMA_MODES) - 1)
					<< ATA_SHIFT_UDMA,
पूर्ण;

क्रमागत hsm_task_states अणु
	HSM_ST_IDLE,		/* no command on going */
	HSM_ST_FIRST,		/* (रुकोing the device to)
				   ग_लिखो CDB or first data block */
	HSM_ST,			/* (रुकोing the device to) transfer data */
	HSM_ST_LAST,		/* (रुकोing the device to) complete command */
	HSM_ST_ERR,		/* error */
पूर्ण;

क्रमागत ata_completion_errors अणु
	AC_ERR_OK		= 0,	    /* no error */
	AC_ERR_DEV		= (1 << 0), /* device reported error */
	AC_ERR_HSM		= (1 << 1), /* host state machine violation */
	AC_ERR_TIMEOUT		= (1 << 2), /* समयout */
	AC_ERR_MEDIA		= (1 << 3), /* media error */
	AC_ERR_ATA_BUS		= (1 << 4), /* ATA bus error */
	AC_ERR_HOST_BUS		= (1 << 5), /* host bus error */
	AC_ERR_SYSTEM		= (1 << 6), /* प्रणाली error */
	AC_ERR_INVALID		= (1 << 7), /* invalid argument */
	AC_ERR_OTHER		= (1 << 8), /* unknown */
	AC_ERR_NODEV_HINT	= (1 << 9), /* polling device detection hपूर्णांक */
	AC_ERR_NCQ		= (1 << 10), /* marker क्रम offending NCQ qc */
पूर्ण;

/*
 * Link घातer management policy: If you alter this, you also need to
 * alter libata-scsi.c (क्रम the ascii descriptions)
 */
क्रमागत ata_lpm_policy अणु
	ATA_LPM_UNKNOWN,
	ATA_LPM_MAX_POWER,
	ATA_LPM_MED_POWER,
	ATA_LPM_MED_POWER_WITH_DIPM, /* Med घातer + DIPM as win IRST करोes */
	ATA_LPM_MIN_POWER_WITH_PARTIAL, /* Min Power + partial and slumber */
	ATA_LPM_MIN_POWER, /* Min घातer + no partial (slumber only) */
पूर्ण;

क्रमागत ata_lpm_hपूर्णांकs अणु
	ATA_LPM_EMPTY		= (1 << 0), /* port empty/probing */
	ATA_LPM_HIPM		= (1 << 1), /* may use HIPM */
	ATA_LPM_WAKE_ONLY	= (1 << 2), /* only wake up link */
पूर्ण;

/* क्रमward declarations */
काष्ठा scsi_device;
काष्ठा ata_port_operations;
काष्ठा ata_port;
काष्ठा ata_link;
काष्ठा ata_queued_cmd;

/* प्रकारs */
प्रकार व्योम (*ata_qc_cb_t) (काष्ठा ata_queued_cmd *qc);
प्रकार पूर्णांक (*ata_prereset_fn_t)(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline);
प्रकार पूर्णांक (*ata_reset_fn_t)(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes,
			      अचिन्हित दीर्घ deadline);
प्रकार व्योम (*ata_postreset_fn_t)(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes);

बाह्य काष्ठा device_attribute dev_attr_unload_heads;
#अगर_घोषित CONFIG_SATA_HOST
बाह्य काष्ठा device_attribute dev_attr_link_घातer_management_policy;
बाह्य काष्ठा device_attribute dev_attr_ncq_prio_enable;
बाह्य काष्ठा device_attribute dev_attr_em_message_type;
बाह्य काष्ठा device_attribute dev_attr_em_message;
बाह्य काष्ठा device_attribute dev_attr_sw_activity;
#पूर्ण_अगर

क्रमागत sw_activity अणु
	OFF,
	BLINK_ON,
	BLINK_OFF,
पूर्ण;

काष्ठा ata_taskfile अणु
	अचिन्हित दीर्घ		flags;		/* ATA_TFLAG_xxx */
	u8			protocol;	/* ATA_PROT_xxx */

	u8			ctl;		/* control reg */

	u8			hob_feature;	/* additional data */
	u8			hob_nsect;	/* to support LBA48 */
	u8			hob_lbal;
	u8			hob_lbam;
	u8			hob_lbah;

	u8			feature;
	u8			nsect;
	u8			lbal;
	u8			lbam;
	u8			lbah;

	u8			device;

	u8			command;	/* IO operation */

	u32			auxiliary;	/* auxiliary field */
						/* from SATA 3.1 and */
						/* ATA-8 ACS-3 */
पूर्ण;

#अगर_घोषित CONFIG_ATA_SFF
काष्ठा ata_ioports अणु
	व्योम __iomem		*cmd_addr;
	व्योम __iomem		*data_addr;
	व्योम __iomem		*error_addr;
	व्योम __iomem		*feature_addr;
	व्योम __iomem		*nsect_addr;
	व्योम __iomem		*lbal_addr;
	व्योम __iomem		*lbam_addr;
	व्योम __iomem		*lbah_addr;
	व्योम __iomem		*device_addr;
	व्योम __iomem		*status_addr;
	व्योम __iomem		*command_addr;
	व्योम __iomem		*altstatus_addr;
	व्योम __iomem		*ctl_addr;
#अगर_घोषित CONFIG_ATA_BMDMA
	व्योम __iomem		*bmdma_addr;
#पूर्ण_अगर /* CONFIG_ATA_BMDMA */
	व्योम __iomem		*scr_addr;
पूर्ण;
#पूर्ण_अगर /* CONFIG_ATA_SFF */

काष्ठा ata_host अणु
	spinlock_t		lock;
	काष्ठा device 		*dev;
	व्योम __iomem * स्थिर	*iomap;
	अचिन्हित पूर्णांक		n_ports;
	अचिन्हित पूर्णांक		n_tags;			/* nr of NCQ tags */
	व्योम			*निजी_data;
	काष्ठा ata_port_operations *ops;
	अचिन्हित दीर्घ		flags;
	काष्ठा kref		kref;

	काष्ठा mutex		eh_mutex;
	काष्ठा task_काष्ठा	*eh_owner;

	काष्ठा ata_port		*simplex_claimed;	/* channel owning the DMA */
	काष्ठा ata_port		*ports[];
पूर्ण;

काष्ठा ata_queued_cmd अणु
	काष्ठा ata_port		*ap;
	काष्ठा ata_device	*dev;

	काष्ठा scsi_cmnd	*scsicmd;
	व्योम			(*scsiकरोne)(काष्ठा scsi_cmnd *);

	काष्ठा ata_taskfile	tf;
	u8			cdb[ATAPI_CDB_LEN];

	अचिन्हित दीर्घ		flags;		/* ATA_QCFLAG_xxx */
	अचिन्हित पूर्णांक		tag;		/* libata core tag */
	अचिन्हित पूर्णांक		hw_tag;		/* driver tag */
	अचिन्हित पूर्णांक		n_elem;
	अचिन्हित पूर्णांक		orig_n_elem;

	पूर्णांक			dma_dir;

	अचिन्हित पूर्णांक		sect_size;

	अचिन्हित पूर्णांक		nbytes;
	अचिन्हित पूर्णांक		extrabytes;
	अचिन्हित पूर्णांक		curbytes;

	काष्ठा scatterlist	sgent;

	काष्ठा scatterlist	*sg;

	काष्ठा scatterlist	*cursg;
	अचिन्हित पूर्णांक		cursg_ofs;

	अचिन्हित पूर्णांक		err_mask;
	काष्ठा ata_taskfile	result_tf;
	ata_qc_cb_t		complete_fn;

	व्योम			*निजी_data;
	व्योम			*lldd_task;
पूर्ण;

काष्ठा ata_port_stats अणु
	अचिन्हित दीर्घ		unhandled_irq;
	अचिन्हित दीर्घ		idle_irq;
	अचिन्हित दीर्घ		rw_reqbuf;
पूर्ण;

काष्ठा ata_ering_entry अणु
	अचिन्हित पूर्णांक		eflags;
	अचिन्हित पूर्णांक		err_mask;
	u64			बारtamp;
पूर्ण;

काष्ठा ata_ering अणु
	पूर्णांक			cursor;
	काष्ठा ata_ering_entry	ring[ATA_ERING_SIZE];
पूर्ण;

काष्ठा ata_device अणु
	काष्ठा ata_link		*link;
	अचिन्हित पूर्णांक		devno;		/* 0 or 1 */
	अचिन्हित पूर्णांक		horkage;	/* List of broken features */
	अचिन्हित दीर्घ		flags;		/* ATA_DFLAG_xxx */
	काष्ठा scsi_device	*sdev;		/* attached SCSI device */
	व्योम			*निजी_data;
#अगर_घोषित CONFIG_ATA_ACPI
	जोड़ acpi_object	*gtf_cache;
	अचिन्हित पूर्णांक		gtf_filter;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SATA_ZPODD
	व्योम			*zpodd;
#पूर्ण_अगर
	काष्ठा device		tdev;
	/* n_sector is CLEAR_BEGIN, पढ़ो comment above CLEAR_BEGIN */
	u64			n_sectors;	/* size of device, अगर ATA */
	u64			n_native_sectors; /* native size, अगर ATA */
	अचिन्हित पूर्णांक		class;		/* ATA_DEV_xxx */
	अचिन्हित दीर्घ		unpark_deadline;

	u8			pio_mode;
	u8			dma_mode;
	u8			xfer_mode;
	अचिन्हित पूर्णांक		xfer_shअगरt;	/* ATA_SHIFT_xxx */

	अचिन्हित पूर्णांक		multi_count;	/* sectors count क्रम
						   READ/WRITE MULTIPLE */
	अचिन्हित पूर्णांक		max_sectors;	/* per-device max sectors */
	अचिन्हित पूर्णांक		cdb_len;

	/* per-dev xfer mask */
	अचिन्हित दीर्घ		pio_mask;
	अचिन्हित दीर्घ		mwdma_mask;
	अचिन्हित दीर्घ		udma_mask;

	/* क्रम CHS addressing */
	u16			cylinders;	/* Number of cylinders */
	u16			heads;		/* Number of heads */
	u16			sectors;	/* Number of sectors per track */

	जोड़ अणु
		u16		id[ATA_ID_WORDS]; /* IDENTIFY xxx DEVICE data */
		u32		gscr[SATA_PMP_GSCR_DWORDS]; /* PMP GSCR block */
	पूर्ण ____cacheline_aligned;

	/* DEVSLP Timing Variables from Identअगरy Device Data Log */
	u8			devslp_timing[ATA_LOG_DEVSLP_SIZE];

	/* NCQ send and receive log subcommand support */
	u8			ncq_send_recv_cmds[ATA_LOG_NCQ_SEND_RECV_SIZE];
	u8			ncq_non_data_cmds[ATA_LOG_NCQ_NON_DATA_SIZE];

	/* ZAC zone configuration */
	u32			zac_zoned_cap;
	u32			zac_zones_optimal_खोलो;
	u32			zac_zones_optimal_nonseq;
	u32			zac_zones_max_खोलो;

	/* error history */
	पूर्णांक			spdn_cnt;
	/* ering is CLEAR_END, पढ़ो comment above CLEAR_END */
	काष्ठा ata_ering	ering;
पूर्ण;

/* Fields between ATA_DEVICE_CLEAR_BEGIN and ATA_DEVICE_CLEAR_END are
 * cleared to zero on ata_dev_init().
 */
#घोषणा ATA_DEVICE_CLEAR_BEGIN		दुरत्व(काष्ठा ata_device, n_sectors)
#घोषणा ATA_DEVICE_CLEAR_END		दुरत्व(काष्ठा ata_device, ering)

काष्ठा ata_eh_info अणु
	काष्ठा ata_device	*dev;		/* offending device */
	u32			serror;		/* SError from LLDD */
	अचिन्हित पूर्णांक		err_mask;	/* port-wide err_mask */
	अचिन्हित पूर्णांक		action;		/* ATA_EH_* action mask */
	अचिन्हित पूर्णांक		dev_action[ATA_MAX_DEVICES]; /* dev EH action */
	अचिन्हित पूर्णांक		flags;		/* ATA_EHI_* flags */

	अचिन्हित पूर्णांक		probe_mask;

	अक्षर			desc[ATA_EH_DESC_LEN];
	पूर्णांक			desc_len;
पूर्ण;

काष्ठा ata_eh_context अणु
	काष्ठा ata_eh_info	i;
	पूर्णांक			tries[ATA_MAX_DEVICES];
	पूर्णांक			cmd_समयout_idx[ATA_MAX_DEVICES]
					       [ATA_EH_CMD_TIMEOUT_TABLE_SIZE];
	अचिन्हित पूर्णांक		classes[ATA_MAX_DEVICES];
	अचिन्हित पूर्णांक		did_probe_mask;
	अचिन्हित पूर्णांक		unloaded_mask;
	अचिन्हित पूर्णांक		saved_ncq_enabled;
	u8			saved_xfer_mode[ATA_MAX_DEVICES];
	/* बारtamp क्रम the last reset attempt or success */
	अचिन्हित दीर्घ		last_reset;
पूर्ण;

काष्ठा ata_acpi_drive
अणु
	u32 pio;
	u32 dma;
पूर्ण __packed;

काष्ठा ata_acpi_gपंचांग अणु
	काष्ठा ata_acpi_drive drive[2];
	u32 flags;
पूर्ण __packed;

काष्ठा ata_link अणु
	काष्ठा ata_port		*ap;
	पूर्णांक			pmp;		/* port multiplier port # */

	काष्ठा device		tdev;
	अचिन्हित पूर्णांक		active_tag;	/* active tag on this link */
	u32			sactive;	/* active NCQ commands */

	अचिन्हित पूर्णांक		flags;		/* ATA_LFLAG_xxx */

	u32			saved_scontrol;	/* SControl on probe */
	अचिन्हित पूर्णांक		hw_sata_spd_limit;
	अचिन्हित पूर्णांक		sata_spd_limit;
	अचिन्हित पूर्णांक		sata_spd;	/* current SATA PHY speed */
	क्रमागत ata_lpm_policy	lpm_policy;

	/* record runसमय error info, रक्षित by host_set lock */
	काष्ठा ata_eh_info	eh_info;
	/* EH context */
	काष्ठा ata_eh_context	eh_context;

	काष्ठा ata_device	device[ATA_MAX_DEVICES];

	अचिन्हित दीर्घ		last_lpm_change; /* when last LPM change happened */
पूर्ण;
#घोषणा ATA_LINK_CLEAR_BEGIN		दुरत्व(काष्ठा ata_link, active_tag)
#घोषणा ATA_LINK_CLEAR_END		दुरत्व(काष्ठा ata_link, device[0])

काष्ठा ata_port अणु
	काष्ठा Scsi_Host	*scsi_host; /* our co-allocated scsi host */
	काष्ठा ata_port_operations *ops;
	spinlock_t		*lock;
	/* Flags owned by the EH context. Only EH should touch these once the
	   port is active */
	अचिन्हित दीर्घ		flags;	/* ATA_FLAG_xxx */
	/* Flags that change dynamically, रक्षित by ap->lock */
	अचिन्हित पूर्णांक		pflags; /* ATA_PFLAG_xxx */
	अचिन्हित पूर्णांक		prपूर्णांक_id; /* user visible unique port ID */
	अचिन्हित पूर्णांक            local_port_no; /* host local port num */
	अचिन्हित पूर्णांक		port_no; /* 0 based port no. inside the host */

#अगर_घोषित CONFIG_ATA_SFF
	काष्ठा ata_ioports	ioaddr;	/* ATA cmd/ctl/dma रेजिस्टर blocks */
	u8			ctl;	/* cache of ATA control रेजिस्टर */
	u8			last_ctl;	/* Cache last written value */
	काष्ठा ata_link*	sff_pio_task_link; /* link currently used */
	काष्ठा delayed_work	sff_pio_task;
#अगर_घोषित CONFIG_ATA_BMDMA
	काष्ठा ata_bmdma_prd	*bmdma_prd;	/* BMDMA SG list */
	dma_addr_t		bmdma_prd_dma;	/* and its DMA mapping */
#पूर्ण_अगर /* CONFIG_ATA_BMDMA */
#पूर्ण_अगर /* CONFIG_ATA_SFF */

	अचिन्हित पूर्णांक		pio_mask;
	अचिन्हित पूर्णांक		mwdma_mask;
	अचिन्हित पूर्णांक		udma_mask;
	अचिन्हित पूर्णांक		cbl;	/* cable type; ATA_CBL_xxx */

	काष्ठा ata_queued_cmd	qcmd[ATA_MAX_QUEUE + 1];
	अचिन्हित दीर्घ		sas_tag_allocated; /* क्रम sas tag allocation only */
	u64			qc_active;
	पूर्णांक			nr_active_links; /* #links with active qcs */
	अचिन्हित पूर्णांक		sas_last_tag;	/* track next tag hw expects */

	काष्ठा ata_link		link;		/* host शेष link */
	काष्ठा ata_link		*slave_link;	/* see ata_slave_link_init() */

	पूर्णांक			nr_pmp_links;	/* nr of available PMP links */
	काष्ठा ata_link		*pmp_link;	/* array of PMP links */
	काष्ठा ata_link		*excl_link;	/* क्रम PMP qc exclusion */

	काष्ठा ata_port_stats	stats;
	काष्ठा ata_host		*host;
	काष्ठा device 		*dev;
	काष्ठा device		tdev;

	काष्ठा mutex		scsi_scan_mutex;
	काष्ठा delayed_work	hotplug_task;
	काष्ठा work_काष्ठा	scsi_rescan_task;

	अचिन्हित पूर्णांक		hsm_task_state;

	u32			msg_enable;
	काष्ठा list_head	eh_करोne_q;
	रुको_queue_head_t	eh_रुको_q;
	पूर्णांक			eh_tries;
	काष्ठा completion	park_req_pending;

	pm_message_t		pm_mesg;
	क्रमागत ata_lpm_policy	target_lpm_policy;

	काष्ठा समयr_list	fastdrain_समयr;
	अचिन्हित दीर्घ		fastdrain_cnt;

	async_cookie_t		cookie;

	पूर्णांक			em_message_type;
	व्योम			*निजी_data;

#अगर_घोषित CONFIG_ATA_ACPI
	काष्ठा ata_acpi_gपंचांग	__acpi_init_gपंचांग; /* use ata_acpi_init_gपंचांग() */
#पूर्ण_अगर
	/* owned by EH */
	u8			sector_buf[ATA_SECT_SIZE] ____cacheline_aligned;
पूर्ण;

/* The following initializer overrides a method to शून्य whether one of
 * its parent has the method defined or not.  This is equivalent to
 * ERR_PTR(-ENOENT).  Unक्रमtunately, ERR_PTR करोesn't render a स्थिरant
 * expression and thus can't be used as an initializer.
 */
#घोषणा ATA_OP_शून्य		(व्योम *)(अचिन्हित दीर्घ)(-ENOENT)

काष्ठा ata_port_operations अणु
	/*
	 * Command execution
	 */
	पूर्णांक (*qc_defer)(काष्ठा ata_queued_cmd *qc);
	पूर्णांक (*check_atapi_dma)(काष्ठा ata_queued_cmd *qc);
	क्रमागत ata_completion_errors (*qc_prep)(काष्ठा ata_queued_cmd *qc);
	अचिन्हित पूर्णांक (*qc_issue)(काष्ठा ata_queued_cmd *qc);
	bool (*qc_fill_rtf)(काष्ठा ata_queued_cmd *qc);

	/*
	 * Configuration and exception handling
	 */
	पूर्णांक  (*cable_detect)(काष्ठा ata_port *ap);
	अचिन्हित दीर्घ (*mode_filter)(काष्ठा ata_device *dev, अचिन्हित दीर्घ xfer_mask);
	व्योम (*set_piomode)(काष्ठा ata_port *ap, काष्ठा ata_device *dev);
	व्योम (*set_dmamode)(काष्ठा ata_port *ap, काष्ठा ata_device *dev);
	पूर्णांक  (*set_mode)(काष्ठा ata_link *link, काष्ठा ata_device **r_failed_dev);
	अचिन्हित पूर्णांक (*पढ़ो_id)(काष्ठा ata_device *dev, काष्ठा ata_taskfile *tf, u16 *id);

	व्योम (*dev_config)(काष्ठा ata_device *dev);

	व्योम (*मुक्तze)(काष्ठा ata_port *ap);
	व्योम (*thaw)(काष्ठा ata_port *ap);
	ata_prereset_fn_t	prereset;
	ata_reset_fn_t		softreset;
	ata_reset_fn_t		hardreset;
	ata_postreset_fn_t	postreset;
	ata_prereset_fn_t	pmp_prereset;
	ata_reset_fn_t		pmp_softreset;
	ata_reset_fn_t		pmp_hardreset;
	ata_postreset_fn_t	pmp_postreset;
	व्योम (*error_handler)(काष्ठा ata_port *ap);
	व्योम (*lost_पूर्णांकerrupt)(काष्ठा ata_port *ap);
	व्योम (*post_पूर्णांकernal_cmd)(काष्ठा ata_queued_cmd *qc);
	व्योम (*sched_eh)(काष्ठा ata_port *ap);
	व्योम (*end_eh)(काष्ठा ata_port *ap);

	/*
	 * Optional features
	 */
	पूर्णांक  (*scr_पढ़ो)(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val);
	पूर्णांक  (*scr_ग_लिखो)(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val);
	व्योम (*pmp_attach)(काष्ठा ata_port *ap);
	व्योम (*pmp_detach)(काष्ठा ata_port *ap);
	पूर्णांक  (*set_lpm)(काष्ठा ata_link *link, क्रमागत ata_lpm_policy policy,
			अचिन्हित hपूर्णांकs);

	/*
	 * Start, stop, suspend and resume
	 */
	पूर्णांक  (*port_suspend)(काष्ठा ata_port *ap, pm_message_t mesg);
	पूर्णांक  (*port_resume)(काष्ठा ata_port *ap);
	पूर्णांक  (*port_start)(काष्ठा ata_port *ap);
	व्योम (*port_stop)(काष्ठा ata_port *ap);
	व्योम (*host_stop)(काष्ठा ata_host *host);

#अगर_घोषित CONFIG_ATA_SFF
	/*
	 * SFF / taskfile oriented ops
	 */
	व्योम (*sff_dev_select)(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device);
	व्योम (*sff_set_devctl)(काष्ठा ata_port *ap, u8 ctl);
	u8   (*sff_check_status)(काष्ठा ata_port *ap);
	u8   (*sff_check_altstatus)(काष्ठा ata_port *ap);
	व्योम (*sff_tf_load)(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf);
	व्योम (*sff_tf_पढ़ो)(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf);
	व्योम (*sff_exec_command)(काष्ठा ata_port *ap,
				 स्थिर काष्ठा ata_taskfile *tf);
	अचिन्हित पूर्णांक (*sff_data_xfer)(काष्ठा ata_queued_cmd *qc,
			अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen, पूर्णांक rw);
	व्योम (*sff_irq_on)(काष्ठा ata_port *);
	bool (*sff_irq_check)(काष्ठा ata_port *);
	व्योम (*sff_irq_clear)(काष्ठा ata_port *);
	व्योम (*sff_drain_fअगरo)(काष्ठा ata_queued_cmd *qc);

#अगर_घोषित CONFIG_ATA_BMDMA
	व्योम (*bmdma_setup)(काष्ठा ata_queued_cmd *qc);
	व्योम (*bmdma_start)(काष्ठा ata_queued_cmd *qc);
	व्योम (*bmdma_stop)(काष्ठा ata_queued_cmd *qc);
	u8   (*bmdma_status)(काष्ठा ata_port *ap);
#पूर्ण_अगर /* CONFIG_ATA_BMDMA */
#पूर्ण_अगर /* CONFIG_ATA_SFF */

	sमाप_प्रकार (*em_show)(काष्ठा ata_port *ap, अक्षर *buf);
	sमाप_प्रकार (*em_store)(काष्ठा ata_port *ap, स्थिर अक्षर *message,
			    माप_प्रकार size);
	sमाप_प्रकार (*sw_activity_show)(काष्ठा ata_device *dev, अक्षर *buf);
	sमाप_प्रकार (*sw_activity_store)(काष्ठा ata_device *dev,
				     क्रमागत sw_activity val);
	sमाप_प्रकार (*transmit_led_message)(काष्ठा ata_port *ap, u32 state,
					sमाप_प्रकार size);

	/*
	 * Obsolete
	 */
	व्योम (*phy_reset)(काष्ठा ata_port *ap);
	व्योम (*eng_समयout)(काष्ठा ata_port *ap);

	/*
	 * ->inherits must be the last field and all the preceding
	 * fields must be poपूर्णांकers.
	 */
	स्थिर काष्ठा ata_port_operations	*inherits;
पूर्ण;

काष्ठा ata_port_info अणु
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		link_flags;
	अचिन्हित दीर्घ		pio_mask;
	अचिन्हित दीर्घ		mwdma_mask;
	अचिन्हित दीर्घ		udma_mask;
	काष्ठा ata_port_operations *port_ops;
	व्योम 			*निजी_data;
पूर्ण;

काष्ठा ata_timing अणु
	अचिन्हित लघु mode;		/* ATA mode */
	अचिन्हित लघु setup;		/* t1 */
	अचिन्हित लघु act8b;		/* t2 क्रम 8-bit I/O */
	अचिन्हित लघु rec8b;		/* t2i क्रम 8-bit I/O */
	अचिन्हित लघु cyc8b;		/* t0 क्रम 8-bit I/O */
	अचिन्हित लघु active;		/* t2 or tD */
	अचिन्हित लघु recover;		/* t2i or tK */
	अचिन्हित लघु dmack_hold;	/* tj */
	अचिन्हित लघु cycle;		/* t0 */
	अचिन्हित लघु udma;		/* t2CYCTYP/2 */
पूर्ण;

/*
 * Core layer - drivers/ata/libata-core.c
 */
बाह्य काष्ठा ata_port_operations ata_dummy_port_ops;
बाह्य स्थिर काष्ठा ata_port_info ata_dummy_port_info;

अटल अंतरभूत bool ata_is_atapi(u8 prot)
अणु
	वापस prot & ATA_PROT_FLAG_ATAPI;
पूर्ण

अटल अंतरभूत bool ata_is_pio(u8 prot)
अणु
	वापस prot & ATA_PROT_FLAG_PIO;
पूर्ण

अटल अंतरभूत bool ata_is_dma(u8 prot)
अणु
	वापस prot & ATA_PROT_FLAG_DMA;
पूर्ण

अटल अंतरभूत bool ata_is_ncq(u8 prot)
अणु
	वापस prot & ATA_PROT_FLAG_NCQ;
पूर्ण

अटल अंतरभूत bool ata_is_data(u8 prot)
अणु
	वापस prot & (ATA_PROT_FLAG_PIO | ATA_PROT_FLAG_DMA);
पूर्ण

अटल अंतरभूत पूर्णांक is_multi_taskfile(काष्ठा ata_taskfile *tf)
अणु
	वापस (tf->command == ATA_CMD_READ_MULTI) ||
	       (tf->command == ATA_CMD_WRITE_MULTI) ||
	       (tf->command == ATA_CMD_READ_MULTI_EXT) ||
	       (tf->command == ATA_CMD_WRITE_MULTI_EXT) ||
	       (tf->command == ATA_CMD_WRITE_MULTI_FUA_EXT);
पूर्ण

अटल अंतरभूत पूर्णांक ata_port_is_dummy(काष्ठा ata_port *ap)
अणु
	वापस ap->ops == &ata_dummy_port_ops;
पूर्ण

बाह्य पूर्णांक ata_std_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline);
बाह्य पूर्णांक ata_रुको_after_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline,
				पूर्णांक (*check_पढ़ोy)(काष्ठा ata_link *link));
बाह्य पूर्णांक sata_std_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			      अचिन्हित दीर्घ deadline);
बाह्य व्योम ata_std_postreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes);

बाह्य काष्ठा ata_host *ata_host_alloc(काष्ठा device *dev, पूर्णांक max_ports);
बाह्य काष्ठा ata_host *ata_host_alloc_pinfo(काष्ठा device *dev,
			स्थिर काष्ठा ata_port_info * स्थिर * ppi, पूर्णांक n_ports);
बाह्य व्योम ata_host_get(काष्ठा ata_host *host);
बाह्य व्योम ata_host_put(काष्ठा ata_host *host);
बाह्य पूर्णांक ata_host_start(काष्ठा ata_host *host);
बाह्य पूर्णांक ata_host_रेजिस्टर(काष्ठा ata_host *host,
			     काष्ठा scsi_host_ढाँचा *sht);
बाह्य पूर्णांक ata_host_activate(काष्ठा ata_host *host, पूर्णांक irq,
			     irq_handler_t irq_handler, अचिन्हित दीर्घ irq_flags,
			     काष्ठा scsi_host_ढाँचा *sht);
बाह्य व्योम ata_host_detach(काष्ठा ata_host *host);
बाह्य व्योम ata_host_init(काष्ठा ata_host *, काष्ठा device *, काष्ठा ata_port_operations *);
बाह्य पूर्णांक ata_scsi_detect(काष्ठा scsi_host_ढाँचा *sht);
बाह्य पूर्णांक ata_scsi_ioctl(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd,
			  व्योम __user *arg);
#अगर_घोषित CONFIG_COMPAT
#घोषणा ATA_SCSI_COMPAT_IOCTL .compat_ioctl = ata_scsi_ioctl,
#अन्यथा
#घोषणा ATA_SCSI_COMPAT_IOCTL /* empty */
#पूर्ण_अगर
बाह्य पूर्णांक ata_scsi_queuecmd(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *cmd);
#अगर IS_REACHABLE(CONFIG_ATA)
bool ata_scsi_dma_need_drain(काष्ठा request *rq);
#अन्यथा
#घोषणा ata_scsi_dma_need_drain शून्य
#पूर्ण_अगर
बाह्य पूर्णांक ata_sas_scsi_ioctl(काष्ठा ata_port *ap, काष्ठा scsi_device *dev,
			    अचिन्हित पूर्णांक cmd, व्योम __user *arg);
बाह्य bool ata_link_online(काष्ठा ata_link *link);
बाह्य bool ata_link_offline(काष्ठा ata_link *link);
#अगर_घोषित CONFIG_PM
बाह्य पूर्णांक ata_host_suspend(काष्ठा ata_host *host, pm_message_t mesg);
बाह्य व्योम ata_host_resume(काष्ठा ata_host *host);
बाह्य व्योम ata_sas_port_suspend(काष्ठा ata_port *ap);
बाह्य व्योम ata_sas_port_resume(काष्ठा ata_port *ap);
#अन्यथा
अटल अंतरभूत व्योम ata_sas_port_suspend(काष्ठा ata_port *ap)
अणु
पूर्ण
अटल अंतरभूत व्योम ata_sas_port_resume(काष्ठा ata_port *ap)
अणु
पूर्ण
#पूर्ण_अगर
बाह्य पूर्णांक ata_ratelimit(व्योम);
बाह्य व्योम ata_msleep(काष्ठा ata_port *ap, अचिन्हित पूर्णांक msecs);
बाह्य u32 ata_रुको_रेजिस्टर(काष्ठा ata_port *ap, व्योम __iomem *reg, u32 mask,
			u32 val, अचिन्हित दीर्घ पूर्णांकerval, अचिन्हित दीर्घ समयout);
बाह्य पूर्णांक atapi_cmd_type(u8 opcode);
बाह्य अचिन्हित दीर्घ ata_pack_xfermask(अचिन्हित दीर्घ pio_mask,
			अचिन्हित दीर्घ mwdma_mask, अचिन्हित दीर्घ udma_mask);
बाह्य व्योम ata_unpack_xfermask(अचिन्हित दीर्घ xfer_mask,
			अचिन्हित दीर्घ *pio_mask, अचिन्हित दीर्घ *mwdma_mask,
			अचिन्हित दीर्घ *udma_mask);
बाह्य u8 ata_xfer_mask2mode(अचिन्हित दीर्घ xfer_mask);
बाह्य अचिन्हित दीर्घ ata_xfer_mode2mask(u8 xfer_mode);
बाह्य पूर्णांक ata_xfer_mode2shअगरt(अचिन्हित दीर्घ xfer_mode);
बाह्य स्थिर अक्षर *ata_mode_string(अचिन्हित दीर्घ xfer_mask);
बाह्य अचिन्हित दीर्घ ata_id_xfermask(स्थिर u16 *id);
बाह्य पूर्णांक ata_std_qc_defer(काष्ठा ata_queued_cmd *qc);
बाह्य क्रमागत ata_completion_errors ata_noop_qc_prep(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम ata_sg_init(काष्ठा ata_queued_cmd *qc, काष्ठा scatterlist *sg,
		 अचिन्हित पूर्णांक n_elem);
बाह्य अचिन्हित पूर्णांक ata_dev_classअगरy(स्थिर काष्ठा ata_taskfile *tf);
बाह्य व्योम ata_dev_disable(काष्ठा ata_device *adev);
बाह्य व्योम ata_id_string(स्थिर u16 *id, अचिन्हित अक्षर *s,
			  अचिन्हित पूर्णांक ofs, अचिन्हित पूर्णांक len);
बाह्य व्योम ata_id_c_string(स्थिर u16 *id, अचिन्हित अक्षर *s,
			    अचिन्हित पूर्णांक ofs, अचिन्हित पूर्णांक len);
बाह्य अचिन्हित पूर्णांक ata_करो_dev_पढ़ो_id(काष्ठा ata_device *dev,
					काष्ठा ata_taskfile *tf, u16 *id);
बाह्य व्योम ata_qc_complete(काष्ठा ata_queued_cmd *qc);
बाह्य u64 ata_qc_get_active(काष्ठा ata_port *ap);
बाह्य व्योम ata_scsi_simulate(काष्ठा ata_device *dev, काष्ठा scsi_cmnd *cmd);
बाह्य पूर्णांक ata_std_bios_param(काष्ठा scsi_device *sdev,
			      काष्ठा block_device *bdev,
			      sector_t capacity, पूर्णांक geom[]);
बाह्य व्योम ata_scsi_unlock_native_capacity(काष्ठा scsi_device *sdev);
बाह्य पूर्णांक ata_scsi_slave_config(काष्ठा scsi_device *sdev);
बाह्य व्योम ata_scsi_slave_destroy(काष्ठा scsi_device *sdev);
बाह्य पूर्णांक ata_scsi_change_queue_depth(काष्ठा scsi_device *sdev,
				       पूर्णांक queue_depth);
बाह्य पूर्णांक __ata_change_queue_depth(काष्ठा ata_port *ap, काष्ठा scsi_device *sdev,
				    पूर्णांक queue_depth);
बाह्य काष्ठा ata_device *ata_dev_pair(काष्ठा ata_device *adev);
बाह्य पूर्णांक ata_करो_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed_dev);
बाह्य व्योम ata_scsi_port_error_handler(काष्ठा Scsi_Host *host, काष्ठा ata_port *ap);
बाह्य व्योम ata_scsi_cmd_error_handler(काष्ठा Scsi_Host *host, काष्ठा ata_port *ap, काष्ठा list_head *eh_q);

/*
 * SATA specअगरic code - drivers/ata/libata-sata.c
 */
#अगर_घोषित CONFIG_SATA_HOST
बाह्य स्थिर अचिन्हित दीर्घ sata_deb_timing_normal[];
बाह्य स्थिर अचिन्हित दीर्घ sata_deb_timing_hotplug[];
बाह्य स्थिर अचिन्हित दीर्घ sata_deb_timing_दीर्घ[];

अटल अंतरभूत स्थिर अचिन्हित दीर्घ *
sata_ehc_deb_timing(काष्ठा ata_eh_context *ehc)
अणु
	अगर (ehc->i.flags & ATA_EHI_HOTPLUGGED)
		वापस sata_deb_timing_hotplug;
	अन्यथा
		वापस sata_deb_timing_normal;
पूर्ण

बाह्य पूर्णांक sata_scr_valid(काष्ठा ata_link *link);
बाह्य पूर्णांक sata_scr_पढ़ो(काष्ठा ata_link *link, पूर्णांक reg, u32 *val);
बाह्य पूर्णांक sata_scr_ग_लिखो(काष्ठा ata_link *link, पूर्णांक reg, u32 val);
बाह्य पूर्णांक sata_scr_ग_लिखो_flush(काष्ठा ata_link *link, पूर्णांक reg, u32 val);
बाह्य पूर्णांक sata_set_spd(काष्ठा ata_link *link);
बाह्य पूर्णांक sata_link_hardreset(काष्ठा ata_link *link,
			स्थिर अचिन्हित दीर्घ *timing, अचिन्हित दीर्घ deadline,
			bool *online, पूर्णांक (*check_पढ़ोy)(काष्ठा ata_link *));
बाह्य पूर्णांक sata_link_resume(काष्ठा ata_link *link, स्थिर अचिन्हित दीर्घ *params,
			    अचिन्हित दीर्घ deadline);
बाह्य व्योम ata_eh_analyze_ncq_error(काष्ठा ata_link *link);
#अन्यथा
अटल अंतरभूत स्थिर अचिन्हित दीर्घ *
sata_ehc_deb_timing(काष्ठा ata_eh_context *ehc)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक sata_scr_valid(काष्ठा ata_link *link) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक sata_scr_पढ़ो(काष्ठा ata_link *link, पूर्णांक reg, u32 *val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक sata_scr_ग_लिखो(काष्ठा ata_link *link, पूर्णांक reg, u32 val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक sata_scr_ग_लिखो_flush(काष्ठा ata_link *link, पूर्णांक reg, u32 val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक sata_set_spd(काष्ठा ata_link *link) अणु वापस -EOPNOTSUPP; पूर्ण
अटल अंतरभूत पूर्णांक sata_link_hardreset(काष्ठा ata_link *link,
				      स्थिर अचिन्हित दीर्घ *timing,
				      अचिन्हित दीर्घ deadline,
				      bool *online,
				      पूर्णांक (*check_पढ़ोy)(काष्ठा ata_link *))
अणु
	अगर (online)
		*online = false;
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक sata_link_resume(काष्ठा ata_link *link,
				   स्थिर अचिन्हित दीर्घ *params,
				   अचिन्हित दीर्घ deadline)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत व्योम ata_eh_analyze_ncq_error(काष्ठा ata_link *link) अणु पूर्ण
#पूर्ण_अगर
बाह्य पूर्णांक sata_link_debounce(काष्ठा ata_link *link,
			स्थिर अचिन्हित दीर्घ *params, अचिन्हित दीर्घ deadline);
बाह्य पूर्णांक sata_link_scr_lpm(काष्ठा ata_link *link, क्रमागत ata_lpm_policy policy,
			     bool spm_wakeup);
बाह्य पूर्णांक ata_slave_link_init(काष्ठा ata_port *ap);
बाह्य व्योम ata_sas_port_destroy(काष्ठा ata_port *);
बाह्य काष्ठा ata_port *ata_sas_port_alloc(काष्ठा ata_host *,
					   काष्ठा ata_port_info *, काष्ठा Scsi_Host *);
बाह्य व्योम ata_sas_async_probe(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_sas_sync_probe(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_sas_port_init(काष्ठा ata_port *);
बाह्य पूर्णांक ata_sas_port_start(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_sas_tport_add(काष्ठा device *parent, काष्ठा ata_port *ap);
बाह्य व्योम ata_sas_tport_delete(काष्ठा ata_port *ap);
बाह्य व्योम ata_sas_port_stop(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_sas_slave_configure(काष्ठा scsi_device *, काष्ठा ata_port *);
बाह्य पूर्णांक ata_sas_queuecmd(काष्ठा scsi_cmnd *cmd, काष्ठा ata_port *ap);
बाह्य व्योम ata_tf_to_fis(स्थिर काष्ठा ata_taskfile *tf,
			  u8 pmp, पूर्णांक is_cmd, u8 *fis);
बाह्य व्योम ata_tf_from_fis(स्थिर u8 *fis, काष्ठा ata_taskfile *tf);
बाह्य पूर्णांक ata_qc_complete_multiple(काष्ठा ata_port *ap, u64 qc_active);
बाह्य bool sata_lpm_ignore_phy_events(काष्ठा ata_link *link);
बाह्य पूर्णांक sata_async_notअगरication(काष्ठा ata_port *ap);

बाह्य पूर्णांक ata_cable_40wire(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_cable_80wire(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_cable_sata(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_cable_ignore(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_cable_unknown(काष्ठा ata_port *ap);

/* Timing helpers */
बाह्य अचिन्हित पूर्णांक ata_pio_need_iordy(स्थिर काष्ठा ata_device *);
बाह्य u8 ata_timing_cycle2mode(अचिन्हित पूर्णांक xfer_shअगरt, पूर्णांक cycle);

/* PCI */
#अगर_घोषित CONFIG_PCI
काष्ठा pci_dev;

काष्ठा pci_bits अणु
	अचिन्हित पूर्णांक		reg;	/* PCI config रेजिस्टर to पढ़ो */
	अचिन्हित पूर्णांक		width;	/* 1 (8 bit), 2 (16 bit), 4 (32 bit) */
	अचिन्हित दीर्घ		mask;
	अचिन्हित दीर्घ		val;
पूर्ण;

बाह्य पूर्णांक pci_test_config_bits(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_bits *bits);
बाह्य व्योम ata_pci_shutकरोwn_one(काष्ठा pci_dev *pdev);
बाह्य व्योम ata_pci_हटाओ_one(काष्ठा pci_dev *pdev);

#अगर_घोषित CONFIG_PM
बाह्य व्योम ata_pci_device_करो_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg);
बाह्य पूर्णांक __must_check ata_pci_device_करो_resume(काष्ठा pci_dev *pdev);
बाह्य पूर्णांक ata_pci_device_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg);
बाह्य पूर्णांक ata_pci_device_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर /* CONFIG_PM */
#पूर्ण_अगर /* CONFIG_PCI */

काष्ठा platक्रमm_device;

बाह्य पूर्णांक ata_platक्रमm_हटाओ_one(काष्ठा platक्रमm_device *pdev);

/*
 * ACPI - drivers/ata/libata-acpi.c
 */
#अगर_घोषित CONFIG_ATA_ACPI
अटल अंतरभूत स्थिर काष्ठा ata_acpi_gपंचांग *ata_acpi_init_gपंचांग(काष्ठा ata_port *ap)
अणु
	अगर (ap->pflags & ATA_PFLAG_INIT_GTM_VALID)
		वापस &ap->__acpi_init_gपंचांग;
	वापस शून्य;
पूर्ण
पूर्णांक ata_acpi_sपंचांग(काष्ठा ata_port *ap, स्थिर काष्ठा ata_acpi_gपंचांग *sपंचांग);
पूर्णांक ata_acpi_gपंचांग(काष्ठा ata_port *ap, काष्ठा ata_acpi_gपंचांग *sपंचांग);
अचिन्हित दीर्घ ata_acpi_gपंचांग_xfermask(काष्ठा ata_device *dev,
				    स्थिर काष्ठा ata_acpi_gपंचांग *gपंचांग);
पूर्णांक ata_acpi_cbl_80wire(काष्ठा ata_port *ap, स्थिर काष्ठा ata_acpi_gपंचांग *gपंचांग);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा ata_acpi_gपंचांग *ata_acpi_init_gपंचांग(काष्ठा ata_port *ap)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक ata_acpi_sपंचांग(स्थिर काष्ठा ata_port *ap,
			       काष्ठा ata_acpi_gपंचांग *sपंचांग)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक ata_acpi_gपंचांग(स्थिर काष्ठा ata_port *ap,
			       काष्ठा ata_acpi_gपंचांग *sपंचांग)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ata_acpi_gपंचांग_xfermask(काष्ठा ata_device *dev,
					स्थिर काष्ठा ata_acpi_gपंचांग *gपंचांग)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ata_acpi_cbl_80wire(काष्ठा ata_port *ap,
				      स्थिर काष्ठा ata_acpi_gपंचांग *gपंचांग)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * EH - drivers/ata/libata-eh.c
 */
बाह्य व्योम ata_port_schedule_eh(काष्ठा ata_port *ap);
बाह्य व्योम ata_port_रुको_eh(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_link_पात(काष्ठा ata_link *link);
बाह्य पूर्णांक ata_port_पात(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_port_मुक्तze(काष्ठा ata_port *ap);

बाह्य व्योम ata_eh_मुक्तze_port(काष्ठा ata_port *ap);
बाह्य व्योम ata_eh_thaw_port(काष्ठा ata_port *ap);

बाह्य व्योम ata_eh_qc_complete(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम ata_eh_qc_retry(काष्ठा ata_queued_cmd *qc);

बाह्य व्योम ata_करो_eh(काष्ठा ata_port *ap, ata_prereset_fn_t prereset,
		      ata_reset_fn_t softreset, ata_reset_fn_t hardreset,
		      ata_postreset_fn_t postreset);
बाह्य व्योम ata_std_error_handler(काष्ठा ata_port *ap);
बाह्य व्योम ata_std_sched_eh(काष्ठा ata_port *ap);
बाह्य व्योम ata_std_end_eh(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_link_nr_enabled(काष्ठा ata_link *link);

/*
 * Base operations to inherit from and initializers क्रम sht
 *
 * Operations
 *
 * base  : Common to all libata drivers.
 * sata  : SATA controllers w/ native पूर्णांकerface.
 * pmp   : SATA controllers w/ PMP support.
 * sff   : SFF ATA controllers w/o BMDMA support.
 * bmdma : SFF ATA controllers w/ BMDMA support.
 *
 * sht initializers
 *
 * BASE  : Common to all libata drivers.  The user must set
 *	   sg_tablesize and dma_boundary.
 * PIO   : SFF ATA controllers w/ only PIO support.
 * BMDMA : SFF ATA controllers w/ BMDMA support.  sg_tablesize and
 *	   dma_boundary are set to BMDMA limits.
 * NCQ   : SATA controllers supporting NCQ.  The user must set
 *	   sg_tablesize, dma_boundary and can_queue.
 */
बाह्य स्थिर काष्ठा ata_port_operations ata_base_port_ops;
बाह्य स्थिर काष्ठा ata_port_operations sata_port_ops;
बाह्य काष्ठा device_attribute *ata_common_sdev_attrs[];

/*
 * All sht initializers (BASE, PIO, BMDMA, NCQ) must be instantiated
 * by the edge drivers.  Because the 'module' field of sht must be the
 * edge driver's module reference, otherwise the driver can be unloaded
 * even अगर the scsi_device is being accessed.
 */
#घोषणा __ATA_BASE_SHT(drv_name)				\
	.module			= THIS_MODULE,			\
	.name			= drv_name,			\
	.ioctl			= ata_scsi_ioctl,		\
	ATA_SCSI_COMPAT_IOCTL					\
	.queuecommand		= ata_scsi_queuecmd,		\
	.dma_need_drain		= ata_scsi_dma_need_drain,	\
	.can_queue		= ATA_DEF_QUEUE,		\
	.tag_alloc_policy	= BLK_TAG_ALLOC_RR,		\
	.this_id		= ATA_SHT_THIS_ID,		\
	.emulated		= ATA_SHT_EMULATED,		\
	.proc_name		= drv_name,			\
	.slave_configure	= ata_scsi_slave_config,	\
	.slave_destroy		= ata_scsi_slave_destroy,	\
	.bios_param		= ata_std_bios_param,		\
	.unlock_native_capacity	= ata_scsi_unlock_native_capacity

#घोषणा ATA_BASE_SHT(drv_name)					\
	__ATA_BASE_SHT(drv_name),				\
	.sdev_attrs		= ata_common_sdev_attrs

#अगर_घोषित CONFIG_SATA_HOST
बाह्य काष्ठा device_attribute *ata_ncq_sdev_attrs[];

#घोषणा ATA_NCQ_SHT(drv_name)					\
	__ATA_BASE_SHT(drv_name),				\
	.sdev_attrs		= ata_ncq_sdev_attrs,		\
	.change_queue_depth	= ata_scsi_change_queue_depth
#पूर्ण_अगर

/*
 * PMP helpers
 */
#अगर_घोषित CONFIG_SATA_PMP
अटल अंतरभूत bool sata_pmp_supported(काष्ठा ata_port *ap)
अणु
	वापस ap->flags & ATA_FLAG_PMP;
पूर्ण

अटल अंतरभूत bool sata_pmp_attached(काष्ठा ata_port *ap)
अणु
	वापस ap->nr_pmp_links != 0;
पूर्ण

अटल अंतरभूत bool ata_is_host_link(स्थिर काष्ठा ata_link *link)
अणु
	वापस link == &link->ap->link || link == link->ap->slave_link;
पूर्ण
#अन्यथा /* CONFIG_SATA_PMP */
अटल अंतरभूत bool sata_pmp_supported(काष्ठा ata_port *ap)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool sata_pmp_attached(काष्ठा ata_port *ap)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool ata_is_host_link(स्थिर काष्ठा ata_link *link)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_SATA_PMP */

अटल अंतरभूत पूर्णांक sata_srst_pmp(काष्ठा ata_link *link)
अणु
	अगर (sata_pmp_supported(link->ap) && ata_is_host_link(link))
		वापस SATA_PMP_CTRL_PORT;
	वापस link->pmp;
पूर्ण

/*
 * prपूर्णांकk helpers
 */
__म_लिखो(3, 4)
व्योम ata_port_prपूर्णांकk(स्थिर काष्ठा ata_port *ap, स्थिर अक्षर *level,
		     स्थिर अक्षर *fmt, ...);
__म_लिखो(3, 4)
व्योम ata_link_prपूर्णांकk(स्थिर काष्ठा ata_link *link, स्थिर अक्षर *level,
		     स्थिर अक्षर *fmt, ...);
__म_लिखो(3, 4)
व्योम ata_dev_prपूर्णांकk(स्थिर काष्ठा ata_device *dev, स्थिर अक्षर *level,
		    स्थिर अक्षर *fmt, ...);

#घोषणा ata_port_err(ap, fmt, ...)				\
	ata_port_prपूर्णांकk(ap, KERN_ERR, fmt, ##__VA_ARGS__)
#घोषणा ata_port_warn(ap, fmt, ...)				\
	ata_port_prपूर्णांकk(ap, KERN_WARNING, fmt, ##__VA_ARGS__)
#घोषणा ata_port_notice(ap, fmt, ...)				\
	ata_port_prपूर्णांकk(ap, KERN_NOTICE, fmt, ##__VA_ARGS__)
#घोषणा ata_port_info(ap, fmt, ...)				\
	ata_port_prपूर्णांकk(ap, KERN_INFO, fmt, ##__VA_ARGS__)
#घोषणा ata_port_dbg(ap, fmt, ...)				\
	ata_port_prपूर्णांकk(ap, KERN_DEBUG, fmt, ##__VA_ARGS__)

#घोषणा ata_link_err(link, fmt, ...)				\
	ata_link_prपूर्णांकk(link, KERN_ERR, fmt, ##__VA_ARGS__)
#घोषणा ata_link_warn(link, fmt, ...)				\
	ata_link_prपूर्णांकk(link, KERN_WARNING, fmt, ##__VA_ARGS__)
#घोषणा ata_link_notice(link, fmt, ...)				\
	ata_link_prपूर्णांकk(link, KERN_NOTICE, fmt, ##__VA_ARGS__)
#घोषणा ata_link_info(link, fmt, ...)				\
	ata_link_prपूर्णांकk(link, KERN_INFO, fmt, ##__VA_ARGS__)
#घोषणा ata_link_dbg(link, fmt, ...)				\
	ata_link_prपूर्णांकk(link, KERN_DEBUG, fmt, ##__VA_ARGS__)

#घोषणा ata_dev_err(dev, fmt, ...)				\
	ata_dev_prपूर्णांकk(dev, KERN_ERR, fmt, ##__VA_ARGS__)
#घोषणा ata_dev_warn(dev, fmt, ...)				\
	ata_dev_prपूर्णांकk(dev, KERN_WARNING, fmt, ##__VA_ARGS__)
#घोषणा ata_dev_notice(dev, fmt, ...)				\
	ata_dev_prपूर्णांकk(dev, KERN_NOTICE, fmt, ##__VA_ARGS__)
#घोषणा ata_dev_info(dev, fmt, ...)				\
	ata_dev_prपूर्णांकk(dev, KERN_INFO, fmt, ##__VA_ARGS__)
#घोषणा ata_dev_dbg(dev, fmt, ...)				\
	ata_dev_prपूर्णांकk(dev, KERN_DEBUG, fmt, ##__VA_ARGS__)

व्योम ata_prपूर्णांक_version(स्थिर काष्ठा device *dev, स्थिर अक्षर *version);

/*
 * ata_eh_info helpers
 */
बाह्य __म_लिखो(2, 3)
व्योम __ata_ehi_push_desc(काष्ठा ata_eh_info *ehi, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 3)
व्योम ata_ehi_push_desc(काष्ठा ata_eh_info *ehi, स्थिर अक्षर *fmt, ...);
बाह्य व्योम ata_ehi_clear_desc(काष्ठा ata_eh_info *ehi);

अटल अंतरभूत व्योम ata_ehi_hotplugged(काष्ठा ata_eh_info *ehi)
अणु
	ehi->probe_mask |= (1 << ATA_MAX_DEVICES) - 1;
	ehi->flags |= ATA_EHI_HOTPLUGGED;
	ehi->action |= ATA_EH_RESET | ATA_EH_ENABLE_LINK;
	ehi->err_mask |= AC_ERR_ATA_BUS;
पूर्ण

/*
 * port description helpers
 */
बाह्य __म_लिखो(2, 3)
व्योम ata_port_desc(काष्ठा ata_port *ap, स्थिर अक्षर *fmt, ...);
#अगर_घोषित CONFIG_PCI
बाह्य व्योम ata_port_pbar_desc(काष्ठा ata_port *ap, पूर्णांक bar, sमाप_प्रकार offset,
			       स्थिर अक्षर *name);
#पूर्ण_अगर

अटल अंतरभूत bool ata_tag_पूर्णांकernal(अचिन्हित पूर्णांक tag)
अणु
	वापस tag == ATA_TAG_INTERNAL;
पूर्ण

अटल अंतरभूत bool ata_tag_valid(अचिन्हित पूर्णांक tag)
अणु
	वापस tag < ATA_MAX_QUEUE || ata_tag_पूर्णांकernal(tag);
पूर्ण

#घोषणा __ata_qc_क्रम_each(ap, qc, tag, max_tag, fn)		\
	क्रम ((tag) = 0; (tag) < (max_tag) &&			\
	     (अणु qc = fn((ap), (tag)); 1; पूर्ण); (tag)++)		\

/*
 * Internal use only, iterate commands ignoring error handling and
 * status of 'qc'.
 */
#घोषणा ata_qc_क्रम_each_raw(ap, qc, tag)					\
	__ata_qc_क्रम_each(ap, qc, tag, ATA_MAX_QUEUE, __ata_qc_from_tag)

/*
 * Iterate all potential commands that can be queued
 */
#घोषणा ata_qc_क्रम_each(ap, qc, tag)					\
	__ata_qc_क्रम_each(ap, qc, tag, ATA_MAX_QUEUE, ata_qc_from_tag)

/*
 * Like ata_qc_क्रम_each, but with the पूर्णांकernal tag included
 */
#घोषणा ata_qc_क्रम_each_with_पूर्णांकernal(ap, qc, tag)			\
	__ata_qc_क्रम_each(ap, qc, tag, ATA_MAX_QUEUE + 1, ata_qc_from_tag)

/*
 * device helpers
 */
अटल अंतरभूत अचिन्हित पूर्णांक ata_class_enabled(अचिन्हित पूर्णांक class)
अणु
	वापस class == ATA_DEV_ATA || class == ATA_DEV_ATAPI ||
		class == ATA_DEV_PMP || class == ATA_DEV_SEMB ||
		class == ATA_DEV_ZAC;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ata_class_disabled(अचिन्हित पूर्णांक class)
अणु
	वापस class == ATA_DEV_ATA_UNSUP || class == ATA_DEV_ATAPI_UNSUP ||
		class == ATA_DEV_PMP_UNSUP || class == ATA_DEV_SEMB_UNSUP ||
		class == ATA_DEV_ZAC_UNSUP;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ata_class_असलent(अचिन्हित पूर्णांक class)
अणु
	वापस !ata_class_enabled(class) && !ata_class_disabled(class);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ata_dev_enabled(स्थिर काष्ठा ata_device *dev)
अणु
	वापस ata_class_enabled(dev->class);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ata_dev_disabled(स्थिर काष्ठा ata_device *dev)
अणु
	वापस ata_class_disabled(dev->class);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ata_dev_असलent(स्थिर काष्ठा ata_device *dev)
अणु
	वापस ata_class_असलent(dev->class);
पूर्ण

/*
 * link helpers
 */
अटल अंतरभूत पूर्णांक ata_link_max_devices(स्थिर काष्ठा ata_link *link)
अणु
	अगर (ata_is_host_link(link) && link->ap->flags & ATA_FLAG_SLAVE_POSS)
		वापस 2;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक ata_link_active(काष्ठा ata_link *link)
अणु
	वापस ata_tag_valid(link->active_tag) || link->sactive;
पूर्ण

/*
 * Iterators
 *
 * ATA_LITER_* स्थिरants are used to select link iteration mode and
 * ATA_DITER_* device iteration mode.
 *
 * For a custom iteration directly using ata_अणुlink|devपूर्ण_next(), अगर
 * @link or @dev, respectively, is शून्य, the first element is
 * वापसed.  @dev and @link can be any valid device or link and the
 * next element according to the iteration mode will be वापसed.
 * After the last element, शून्य is वापसed.
 */
क्रमागत ata_link_iter_mode अणु
	ATA_LITER_EDGE,		/* अगर present, PMP links only; otherwise,
				 * host link.  no slave link */
	ATA_LITER_HOST_FIRST,	/* host link followed by PMP or slave links */
	ATA_LITER_PMP_FIRST,	/* PMP links followed by host link,
				 * slave link still comes after host link */
पूर्ण;

क्रमागत ata_dev_iter_mode अणु
	ATA_DITER_ENABLED,
	ATA_DITER_ENABLED_REVERSE,
	ATA_DITER_ALL,
	ATA_DITER_ALL_REVERSE,
पूर्ण;

बाह्य काष्ठा ata_link *ata_link_next(काष्ठा ata_link *link,
				      काष्ठा ata_port *ap,
				      क्रमागत ata_link_iter_mode mode);

बाह्य काष्ठा ata_device *ata_dev_next(काष्ठा ata_device *dev,
				       काष्ठा ata_link *link,
				       क्रमागत ata_dev_iter_mode mode);

/*
 * Shortcut notation क्रम iterations
 *
 * ata_क्रम_each_link() iterates over each link of @ap according to
 * @mode.  @link poपूर्णांकs to the current link in the loop.  @link is
 * शून्य after loop termination.  ata_क्रम_each_dev() works the same way
 * except that it iterates over each device of @link.
 *
 * Note that the mode prefixes ATA_अणुL|Dपूर्णITER_ shouldn't need to be
 * specअगरied when using the following लघुhand notations.  Only the
 * mode itself (EDGE, HOST_FIRST, ENABLED, etc...) should be
 * specअगरied.  This not only increases brevity but also makes it
 * impossible to use ATA_LITER_* क्रम device iteration or vice-versa.
 */
#घोषणा ata_क्रम_each_link(link, ap, mode) \
	क्रम ((link) = ata_link_next(शून्य, (ap), ATA_LITER_##mode); (link); \
	     (link) = ata_link_next((link), (ap), ATA_LITER_##mode))

#घोषणा ata_क्रम_each_dev(dev, link, mode) \
	क्रम ((dev) = ata_dev_next(शून्य, (link), ATA_DITER_##mode); (dev); \
	     (dev) = ata_dev_next((dev), (link), ATA_DITER_##mode))

/**
 *	ata_ncq_enabled - Test whether NCQ is enabled
 *	@dev: ATA device to test क्रम
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	1 अगर NCQ is enabled क्रम @dev, 0 otherwise.
 */
अटल अंतरभूत पूर्णांक ata_ncq_enabled(काष्ठा ata_device *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_SATA_HOST))
		वापस 0;
	वापस (dev->flags & (ATA_DFLAG_PIO | ATA_DFLAG_NCQ_OFF |
			      ATA_DFLAG_NCQ)) == ATA_DFLAG_NCQ;
पूर्ण

अटल अंतरभूत bool ata_fpdma_dsm_supported(काष्ठा ata_device *dev)
अणु
	वापस (dev->flags & ATA_DFLAG_NCQ_SEND_RECV) &&
		(dev->ncq_send_recv_cmds[ATA_LOG_NCQ_SEND_RECV_DSM_OFFSET] &
		 ATA_LOG_NCQ_SEND_RECV_DSM_TRIM);
पूर्ण

अटल अंतरभूत bool ata_fpdma_पढ़ो_log_supported(काष्ठा ata_device *dev)
अणु
	वापस (dev->flags & ATA_DFLAG_NCQ_SEND_RECV) &&
		(dev->ncq_send_recv_cmds[ATA_LOG_NCQ_SEND_RECV_RD_LOG_OFFSET] &
		 ATA_LOG_NCQ_SEND_RECV_RD_LOG_SUPPORTED);
पूर्ण

अटल अंतरभूत bool ata_fpdma_zac_mgmt_in_supported(काष्ठा ata_device *dev)
अणु
	वापस (dev->flags & ATA_DFLAG_NCQ_SEND_RECV) &&
		(dev->ncq_send_recv_cmds[ATA_LOG_NCQ_SEND_RECV_ZAC_MGMT_OFFSET] &
		ATA_LOG_NCQ_SEND_RECV_ZAC_MGMT_IN_SUPPORTED);
पूर्ण

अटल अंतरभूत bool ata_fpdma_zac_mgmt_out_supported(काष्ठा ata_device *dev)
अणु
	वापस (dev->ncq_non_data_cmds[ATA_LOG_NCQ_NON_DATA_ZAC_MGMT_OFFSET] &
		ATA_LOG_NCQ_NON_DATA_ZAC_MGMT_OUT);
पूर्ण

अटल अंतरभूत व्योम ata_qc_set_polling(काष्ठा ata_queued_cmd *qc)
अणु
	qc->tf.ctl |= ATA_NIEN;
पूर्ण

अटल अंतरभूत काष्ठा ata_queued_cmd *__ata_qc_from_tag(काष्ठा ata_port *ap,
						       अचिन्हित पूर्णांक tag)
अणु
	अगर (ata_tag_valid(tag))
		वापस &ap->qcmd[tag];
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा ata_queued_cmd *ata_qc_from_tag(काष्ठा ata_port *ap,
						     अचिन्हित पूर्णांक tag)
अणु
	काष्ठा ata_queued_cmd *qc = __ata_qc_from_tag(ap, tag);

	अगर (unlikely(!qc) || !ap->ops->error_handler)
		वापस qc;

	अगर ((qc->flags & (ATA_QCFLAG_ACTIVE |
			  ATA_QCFLAG_FAILED)) == ATA_QCFLAG_ACTIVE)
		वापस qc;

	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ata_qc_raw_nbytes(काष्ठा ata_queued_cmd *qc)
अणु
	वापस qc->nbytes - min(qc->extrabytes, qc->nbytes);
पूर्ण

अटल अंतरभूत व्योम ata_tf_init(काष्ठा ata_device *dev, काष्ठा ata_taskfile *tf)
अणु
	स_रखो(tf, 0, माप(*tf));

#अगर_घोषित CONFIG_ATA_SFF
	tf->ctl = dev->link->ap->ctl;
#अन्यथा
	tf->ctl = ATA_DEVCTL_OBS;
#पूर्ण_अगर
	अगर (dev->devno == 0)
		tf->device = ATA_DEVICE_OBS;
	अन्यथा
		tf->device = ATA_DEVICE_OBS | ATA_DEV1;
पूर्ण

अटल अंतरभूत व्योम ata_qc_reinit(काष्ठा ata_queued_cmd *qc)
अणु
	qc->dma_dir = DMA_NONE;
	qc->sg = शून्य;
	qc->flags = 0;
	qc->cursg = शून्य;
	qc->cursg_ofs = 0;
	qc->nbytes = qc->extrabytes = qc->curbytes = 0;
	qc->n_elem = 0;
	qc->err_mask = 0;
	qc->sect_size = ATA_SECT_SIZE;

	ata_tf_init(qc->dev, &qc->tf);

	/* init result_tf such that it indicates normal completion */
	qc->result_tf.command = ATA_DRDY;
	qc->result_tf.feature = 0;
पूर्ण

अटल अंतरभूत पूर्णांक ata_try_flush_cache(स्थिर काष्ठा ata_device *dev)
अणु
	वापस ata_id_wcache_enabled(dev->id) ||
	       ata_id_has_flush(dev->id) ||
	       ata_id_has_flush_ext(dev->id);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ac_err_mask(u8 status)
अणु
	अगर (status & (ATA_BUSY | ATA_DRQ))
		वापस AC_ERR_HSM;
	अगर (status & (ATA_ERR | ATA_DF))
		वापस AC_ERR_DEV;
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __ac_err_mask(u8 status)
अणु
	अचिन्हित पूर्णांक mask = ac_err_mask(status);
	अगर (mask == 0)
		वापस AC_ERR_OTHER;
	वापस mask;
पूर्ण

अटल अंतरभूत काष्ठा ata_port *ata_shost_to_port(काष्ठा Scsi_Host *host)
अणु
	वापस *(काष्ठा ata_port **)&host->hostdata[0];
पूर्ण

अटल अंतरभूत पूर्णांक ata_check_पढ़ोy(u8 status)
अणु
	अगर (!(status & ATA_BUSY))
		वापस 1;

	/* 0xff indicates either no device or device not पढ़ोy */
	अगर (status == 0xff)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ata_deadline(अचिन्हित दीर्घ from_jअगरfies,
					 अचिन्हित दीर्घ समयout_msecs)
अणु
	वापस from_jअगरfies + msecs_to_jअगरfies(समयout_msecs);
पूर्ण

/* Don't खोलो code these in drivers as there are traps. Firstly the range may
   change in future hardware and specs, secondly 0xFF means 'no DMA' but is
   > UDMA_0. Dyma ddreigiau */

अटल अंतरभूत पूर्णांक ata_using_mwdma(काष्ठा ata_device *adev)
अणु
	अगर (adev->dma_mode >= XFER_MW_DMA_0 && adev->dma_mode <= XFER_MW_DMA_4)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ata_using_udma(काष्ठा ata_device *adev)
अणु
	अगर (adev->dma_mode >= XFER_UDMA_0 && adev->dma_mode <= XFER_UDMA_7)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ata_dma_enabled(काष्ठा ata_device *adev)
अणु
	वापस (adev->dma_mode == 0xFF ? 0 : 1);
पूर्ण

/**************************************************************************
 * PATA timings - drivers/ata/libata-pata-timings.c
 */
बाह्य स्थिर काष्ठा ata_timing *ata_timing_find_mode(u8 xfer_mode);
बाह्य पूर्णांक ata_timing_compute(काष्ठा ata_device *, अचिन्हित लघु,
			      काष्ठा ata_timing *, पूर्णांक, पूर्णांक);
बाह्य व्योम ata_timing_merge(स्थिर काष्ठा ata_timing *,
			     स्थिर काष्ठा ata_timing *, काष्ठा ata_timing *,
			     अचिन्हित पूर्णांक);

/**************************************************************************
 * PMP - drivers/ata/libata-pmp.c
 */
#अगर_घोषित CONFIG_SATA_PMP

बाह्य स्थिर काष्ठा ata_port_operations sata_pmp_port_ops;

बाह्य पूर्णांक sata_pmp_qc_defer_cmd_चयन(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम sata_pmp_error_handler(काष्ठा ata_port *ap);

#अन्यथा /* CONFIG_SATA_PMP */

#घोषणा sata_pmp_port_ops		sata_port_ops
#घोषणा sata_pmp_qc_defer_cmd_चयन	ata_std_qc_defer
#घोषणा sata_pmp_error_handler		ata_std_error_handler

#पूर्ण_अगर /* CONFIG_SATA_PMP */


/**************************************************************************
 * SFF - drivers/ata/libata-sff.c
 */
#अगर_घोषित CONFIG_ATA_SFF

बाह्य स्थिर काष्ठा ata_port_operations ata_sff_port_ops;
बाह्य स्थिर काष्ठा ata_port_operations ata_bmdma32_port_ops;

/* PIO only, sg_tablesize and dma_boundary limits can be हटाओd */
#घोषणा ATA_PIO_SHT(drv_name)					\
	ATA_BASE_SHT(drv_name),					\
	.sg_tablesize		= LIBATA_MAX_PRD,		\
	.dma_boundary		= ATA_DMA_BOUNDARY

बाह्य व्योम ata_sff_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device);
बाह्य u8 ata_sff_check_status(काष्ठा ata_port *ap);
बाह्य व्योम ata_sff_छोड़ो(काष्ठा ata_port *ap);
बाह्य व्योम ata_sff_dma_छोड़ो(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_sff_busy_sleep(काष्ठा ata_port *ap,
			      अचिन्हित दीर्घ समयout_pat, अचिन्हित दीर्घ समयout);
बाह्य पूर्णांक ata_sff_रुको_पढ़ोy(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline);
बाह्य व्योम ata_sff_tf_load(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf);
बाह्य व्योम ata_sff_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf);
बाह्य व्योम ata_sff_exec_command(काष्ठा ata_port *ap,
				 स्थिर काष्ठा ata_taskfile *tf);
बाह्य अचिन्हित पूर्णांक ata_sff_data_xfer(काष्ठा ata_queued_cmd *qc,
			अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen, पूर्णांक rw);
बाह्य अचिन्हित पूर्णांक ata_sff_data_xfer32(काष्ठा ata_queued_cmd *qc,
			अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen, पूर्णांक rw);
बाह्य व्योम ata_sff_irq_on(काष्ठा ata_port *ap);
बाह्य व्योम ata_sff_irq_clear(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_sff_hsm_move(काष्ठा ata_port *ap, काष्ठा ata_queued_cmd *qc,
			    u8 status, पूर्णांक in_wq);
बाह्य व्योम ata_sff_queue_work(काष्ठा work_काष्ठा *work);
बाह्य व्योम ata_sff_queue_delayed_work(काष्ठा delayed_work *dwork,
		अचिन्हित दीर्घ delay);
बाह्य व्योम ata_sff_queue_pio_task(काष्ठा ata_link *link, अचिन्हित दीर्घ delay);
बाह्य अचिन्हित पूर्णांक ata_sff_qc_issue(काष्ठा ata_queued_cmd *qc);
बाह्य bool ata_sff_qc_fill_rtf(काष्ठा ata_queued_cmd *qc);
बाह्य अचिन्हित पूर्णांक ata_sff_port_पूर्णांकr(काष्ठा ata_port *ap,
				      काष्ठा ata_queued_cmd *qc);
बाह्य irqवापस_t ata_sff_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
बाह्य व्योम ata_sff_lost_पूर्णांकerrupt(काष्ठा ata_port *ap);
बाह्य व्योम ata_sff_मुक्तze(काष्ठा ata_port *ap);
बाह्य व्योम ata_sff_thaw(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_sff_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline);
बाह्य अचिन्हित पूर्णांक ata_sff_dev_classअगरy(काष्ठा ata_device *dev, पूर्णांक present,
					  u8 *r_err);
बाह्य पूर्णांक ata_sff_रुको_after_reset(काष्ठा ata_link *link, अचिन्हित पूर्णांक devmask,
				    अचिन्हित दीर्घ deadline);
बाह्य पूर्णांक ata_sff_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes,
			     अचिन्हित दीर्घ deadline);
बाह्य पूर्णांक sata_sff_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			       अचिन्हित दीर्घ deadline);
बाह्य व्योम ata_sff_postreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes);
बाह्य व्योम ata_sff_drain_fअगरo(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम ata_sff_error_handler(काष्ठा ata_port *ap);
बाह्य व्योम ata_sff_std_ports(काष्ठा ata_ioports *ioaddr);
#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक ata_pci_sff_init_host(काष्ठा ata_host *host);
बाह्य पूर्णांक ata_pci_sff_prepare_host(काष्ठा pci_dev *pdev,
				    स्थिर काष्ठा ata_port_info * स्थिर * ppi,
				    काष्ठा ata_host **r_host);
बाह्य पूर्णांक ata_pci_sff_activate_host(काष्ठा ata_host *host,
				     irq_handler_t irq_handler,
				     काष्ठा scsi_host_ढाँचा *sht);
बाह्य पूर्णांक ata_pci_sff_init_one(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा ata_port_info * स्थिर * ppi,
		काष्ठा scsi_host_ढाँचा *sht, व्योम *host_priv, पूर्णांक hflags);
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_ATA_BMDMA

बाह्य स्थिर काष्ठा ata_port_operations ata_bmdma_port_ops;

#घोषणा ATA_BMDMA_SHT(drv_name)					\
	ATA_BASE_SHT(drv_name),					\
	.sg_tablesize		= LIBATA_MAX_PRD,		\
	.dma_boundary		= ATA_DMA_BOUNDARY

बाह्य क्रमागत ata_completion_errors ata_bmdma_qc_prep(काष्ठा ata_queued_cmd *qc);
बाह्य अचिन्हित पूर्णांक ata_bmdma_qc_issue(काष्ठा ata_queued_cmd *qc);
बाह्य क्रमागत ata_completion_errors ata_bmdma_dumb_qc_prep(काष्ठा ata_queued_cmd *qc);
बाह्य अचिन्हित पूर्णांक ata_bmdma_port_पूर्णांकr(काष्ठा ata_port *ap,
				      काष्ठा ata_queued_cmd *qc);
बाह्य irqवापस_t ata_bmdma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
बाह्य व्योम ata_bmdma_error_handler(काष्ठा ata_port *ap);
बाह्य व्योम ata_bmdma_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम ata_bmdma_irq_clear(काष्ठा ata_port *ap);
बाह्य व्योम ata_bmdma_setup(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम ata_bmdma_start(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम ata_bmdma_stop(काष्ठा ata_queued_cmd *qc);
बाह्य u8 ata_bmdma_status(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_bmdma_port_start(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_bmdma_port_start32(काष्ठा ata_port *ap);

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक ata_pci_bmdma_clear_simplex(काष्ठा pci_dev *pdev);
बाह्य व्योम ata_pci_bmdma_init(काष्ठा ata_host *host);
बाह्य पूर्णांक ata_pci_bmdma_prepare_host(काष्ठा pci_dev *pdev,
				      स्थिर काष्ठा ata_port_info * स्थिर * ppi,
				      काष्ठा ata_host **r_host);
बाह्य पूर्णांक ata_pci_bmdma_init_one(काष्ठा pci_dev *pdev,
				  स्थिर काष्ठा ata_port_info * स्थिर * ppi,
				  काष्ठा scsi_host_ढाँचा *sht,
				  व्योम *host_priv, पूर्णांक hflags);
#पूर्ण_अगर /* CONFIG_PCI */
#पूर्ण_अगर /* CONFIG_ATA_BMDMA */

/**
 *	ata_sff_busy_रुको - Wait क्रम a port status रेजिस्टर
 *	@ap: Port to रुको क्रम.
 *	@bits: bits that must be clear
 *	@max: number of 10uS रुकोs to perक्रमm
 *
 *	Waits up to max*10 microseconds क्रम the selected bits in the port's
 *	status रेजिस्टर to be cleared.
 *	Returns final value of status रेजिस्टर.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल अंतरभूत u8 ata_sff_busy_रुको(काष्ठा ata_port *ap, अचिन्हित पूर्णांक bits,
				   अचिन्हित पूर्णांक max)
अणु
	u8 status;

	करो अणु
		udelay(10);
		status = ap->ops->sff_check_status(ap);
		max--;
	पूर्ण जबतक (status != 0xff && (status & bits) && (max > 0));

	वापस status;
पूर्ण

/**
 *	ata_रुको_idle - Wait क्रम a port to be idle.
 *	@ap: Port to रुको क्रम.
 *
 *	Waits up to 10ms क्रम port's BUSY and DRQ संकेतs to clear.
 *	Returns final value of status रेजिस्टर.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल अंतरभूत u8 ata_रुको_idle(काष्ठा ata_port *ap)
अणु
	u8 status = ata_sff_busy_रुको(ap, ATA_BUSY | ATA_DRQ, 1000);

#अगर_घोषित ATA_DEBUG
	अगर (status != 0xff && (status & (ATA_BUSY | ATA_DRQ)))
		ata_port_prपूर्णांकk(ap, KERN_DEBUG, "abnormal Status 0x%X\n",
				status);
#पूर्ण_अगर

	वापस status;
पूर्ण
#पूर्ण_अगर /* CONFIG_ATA_SFF */

#पूर्ण_अगर /* __LINUX_LIBATA_H__ */
