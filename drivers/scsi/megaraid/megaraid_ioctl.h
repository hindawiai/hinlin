<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *			Linux MegaRAID device driver
 *
 * Copyright (c) 2003-2004  LSI Logic Corporation.
 *
 * खाता		: megaraid_ioctl.h
 *
 * Definitions to पूर्णांकerface with user level applications
 */

#अगर_अघोषित _MEGARAID_IOCTL_H_
#घोषणा _MEGARAID_IOCTL_H_

#समावेश <linux/types.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/समयr.h>

#समावेश "mbox_defs.h"

/*
 * console messages debug levels
 */
#घोषणा	CL_ANN		0	/* prपूर्णांक unconditionally, announcements */
#घोषणा CL_DLEVEL1	1	/* debug level 1, inक्रमmative */
#घोषणा CL_DLEVEL2	2	/* debug level 2, verbose */
#घोषणा CL_DLEVEL3	3	/* debug level 3, very verbose */

/**
 * con_log() - console log routine
 * @level		: indicates the severity of the message.
 * @fmt			: क्रमmat string
 *
 * con_log displays the error messages on the console based on the current
 * debug level. Also it attaches the appropriate kernel severity level with
 * the message.
 */
#घोषणा	con_log(level, fmt) अगर (LSI_DBGLVL >= level) prपूर्णांकk fmt;

/*
 * Definitions & Declarations needed to use common management module
 */

#घोषणा MEGAIOC_MAGIC		'm'
#घोषणा MEGAIOCCMD		_IOWR(MEGAIOC_MAGIC, 0, mimd_t)

#घोषणा MEGAIOC_QNADAP		'm'	/* Query # of adapters		*/
#घोषणा MEGAIOC_QDRVRVER	'e'	/* Query driver version		*/
#घोषणा MEGAIOC_QADAPINFO   	'g'	/* Query adapter inक्रमmation	*/

#घोषणा USCSICMD		0x80
#घोषणा UIOC_RD			0x00001
#घोषणा UIOC_WR			0x00002

#घोषणा MBOX_CMD		0x00000
#घोषणा GET_DRIVER_VER		0x10000
#घोषणा GET_N_ADAP		0x20000
#घोषणा GET_ADAP_INFO		0x30000
#घोषणा GET_CAP			0x40000
#घोषणा GET_STATS		0x50000
#घोषणा GET_IOCTL_VERSION	0x01

#घोषणा EXT_IOCTL_SIGN_SZ	16
#घोषणा EXT_IOCTL_SIGN		"$$_EXTD_IOCTL_$$"

#घोषणा	MBOX_LEGACY		0x00		/* ioctl has legacy mbox*/
#घोषणा MBOX_HPE		0x01		/* ioctl has hpe mbox	*/

#घोषणा	APPTYPE_MIMD		0x00		/* old existing apps	*/
#घोषणा APPTYPE_UIOC		0x01		/* new apps using uioc	*/

#घोषणा IOCTL_ISSUE		0x00000001	/* Issue ioctl		*/
#घोषणा IOCTL_ABORT		0x00000002	/* Abort previous ioctl	*/

#घोषणा DRVRTYPE_MBOX		0x00000001	/* regular mbox driver	*/
#घोषणा DRVRTYPE_HPE		0x00000002	/* new hpe driver	*/

#घोषणा MKADAP(adapno)	(MEGAIOC_MAGIC << 8 | (adapno) )
#घोषणा GETADAP(mkadap)	((mkadap) ^ MEGAIOC_MAGIC << 8)

#घोषणा MAX_DMA_POOLS		5		/* 4k, 8k, 16k, 32k, 64k*/


/**
 * काष्ठा uioc_t - the common ioctl packet काष्ठाure
 *
 * @signature	: Must be "$$_EXTD_IOCTL_$$"
 * @mb_type	: Type of the mail box (MB_LEGACY or MB_HPE)
 * @app_type	: Type of the issuing application (existing or new)
 * @opcode	: Opcode of the command
 * @adapno	: Adapter number
 * @cmdbuf	: Poपूर्णांकer to buffer - can poपूर्णांक to mbox or plain data buffer
 * @xferlen	: xferlen क्रम DCMD and non mailbox commands
 * @data_dir	: Direction of the data transfer
 * @status	: Status from the driver
 * @reserved	: reserved bytes क्रम future expansion
 *
 * @user_data	: user data transfer address is saved in this
 * @user_data_len: length of the data buffer sent by user app
 * @user_pthru	: user passthru address is saves in this (null अगर DCMD)
 * @pthru32	: kernel address passthru (allocated per kioc)
 * @pthru32_h	: physicall address of @pthru32
 * @list	: क्रम kioc मुक्त pool list मुख्यtenance
 * @करोne	: call back routine क्रम llds to call when kioc is completed
 * @buf_vaddr	: dma pool buffer attached to kioc क्रम data transfer
 * @buf_paddr	: physical address of the dma pool buffer
 * @pool_index	: index of the dma pool that @buf_vaddr is taken from
 * @मुक्त_buf	: indicates अगर buffer needs to be मुक्तd after kioc completes
 *
 * Note		: All LSI drivers understand only this packet. Any other
 *		: क्रमmat sent by applications would be converted to this.
 */
प्रकार काष्ठा uioc अणु

/* User Apps: */

	uपूर्णांक8_t			signature[EXT_IOCTL_SIGN_SZ];
	uपूर्णांक16_t		mb_type;
	uपूर्णांक16_t		app_type;
	uपूर्णांक32_t		opcode;
	uपूर्णांक32_t		adapno;
	uपूर्णांक64_t		cmdbuf;
	uपूर्णांक32_t		xferlen;
	uपूर्णांक32_t		data_dir;
	पूर्णांक32_t			status;
	uपूर्णांक8_t			reserved[128];

/* Driver Data: */
	व्योम __user *		user_data;
	uपूर्णांक32_t		user_data_len;

	/* 64bit alignment */
	uपूर्णांक32_t                pad_क्रम_64bit_align;

	mraid_passthru_t	__user *user_pthru;

	mraid_passthru_t	*pthru32;
	dma_addr_t		pthru32_h;

	काष्ठा list_head	list;
	व्योम			(*करोne)(काष्ठा uioc*);

	caddr_t			buf_vaddr;
	dma_addr_t		buf_paddr;
	पूर्णांक8_t			pool_index;
	uपूर्णांक8_t			मुक्त_buf;

	uपूर्णांक8_t			समयकरोut;

पूर्ण __attribute__ ((aligned(1024),packed)) uioc_t;

/* For on-stack uioc समयrs. */
काष्ठा uioc_समयout अणु
	काष्ठा समयr_list समयr;
	uioc_t		  *uioc;
पूर्ण;

/**
 * काष्ठा mraid_hba_info - inक्रमmation about the controller
 *
 * @pci_venकरोr_id		: PCI venकरोr id
 * @pci_device_id		: PCI device id
 * @subप्रणाली_venकरोr_id		: PCI subप्रणाली venकरोr id
 * @subप्रणाली_device_id		: PCI subप्रणाली device id
 * @baseport			: base port of hba memory
 * @pci_bus			: PCI bus
 * @pci_dev_fn			: PCI device/function values
 * @irq				: पूर्णांकerrupt vector क्रम the device
 *
 * Extended inक्रमmation of 256 bytes about the controller. Align on the single
 * byte boundary so that 32-bit applications can be run on 64-bit platक्रमm
 * drivers withoug re-compilation.
 * NOTE: reduce the number of reserved bytes whenever new field are added, so
 * that total size of the काष्ठाure reमुख्यs 256 bytes.
 */
प्रकार काष्ठा mraid_hba_info अणु

	uपूर्णांक16_t	pci_venकरोr_id;
	uपूर्णांक16_t	pci_device_id;
	uपूर्णांक16_t	subsys_venकरोr_id;
	uपूर्णांक16_t	subsys_device_id;

	uपूर्णांक64_t	baseport;
	uपूर्णांक8_t		pci_bus;
	uपूर्णांक8_t		pci_dev_fn;
	uपूर्णांक8_t		pci_slot;
	uपूर्णांक8_t		irq;

	uपूर्णांक32_t	unique_id;
	uपूर्णांक32_t	host_no;

	uपूर्णांक8_t		num_ldrv;
पूर्ण __attribute__ ((aligned(256), packed)) mraid_hba_info_t;


/**
 * mcontroller	: adapter info काष्ठाure क्रम old mimd_t apps
 *
 * @base	: base address
 * @irq		: irq number
 * @numldrv	: number of logical drives
 * @pcibus	: pci bus
 * @pcidev	: pci device
 * @pcअगरun	: pci function
 * @pciid	: pci id
 * @pcivenकरोr	: venकरोr id
 * @pcislot	: slot number
 * @uid		: unique id
 */
प्रकार काष्ठा mcontroller अणु

	uपूर्णांक64_t	base;
	uपूर्णांक8_t		irq;
	uपूर्णांक8_t		numldrv;
	uपूर्णांक8_t		pcibus;
	uपूर्णांक16_t	pcidev;
	uपूर्णांक8_t		pcअगरun;
	uपूर्णांक16_t	pciid;
	uपूर्णांक16_t	pcivenकरोr;
	uपूर्णांक8_t		pcislot;
	uपूर्णांक32_t	uid;

पूर्ण __attribute__ ((packed)) mcontroller_t;


/**
 * mm_dmapool_t	: Represents one dma pool with just one buffer
 *
 * @vaddr	: Virtual address
 * @paddr	: DMA physicall address
 * @bufsize	: In KB - 4 = 4k, 8 = 8k etc.
 * @handle	: Handle to the dma pool
 * @lock	: lock to synchronize access to the pool
 * @in_use	: If pool alपढ़ोy in use, attach new block
 */
प्रकार काष्ठा mm_dmapool अणु
	caddr_t		vaddr;
	dma_addr_t	paddr;
	uपूर्णांक32_t	buf_size;
	काष्ठा dma_pool	*handle;
	spinlock_t	lock;
	uपूर्णांक8_t		in_use;
पूर्ण mm_dmapool_t;


/**
 * mraid_mmadp_t: Structure that drivers pass during (un)registration
 *
 * @unique_id		: Any unique id (usually PCI bus+dev+fn)
 * @drvr_type		: megaraid or hpe (DRVRTYPE_MBOX or DRVRTYPE_HPE)
 * @drv_data		: Driver specअगरic; not touched by the common module
 * @समयout		: समयout क्रम issued kiocs
 * @max_kioc		: Maximum ioctl packets acceptable by the lld
 * @pdev		: pci dev; used क्रम allocating dma'ble memory
 * @issue_uioc		: Driver supplied routine to issue uioc_t commands
 *			: issue_uioc(drvr_data, kioc, ISSUE/ABORT, uioc_करोne)
 * @quiescent		: flag to indicate अगर ioctl can be issued to this adp
 * @list		: attach with the global list of adapters
 * @kioc_list		: block of mem क्रम @max_kioc number of kiocs
 * @kioc_pool		: pool of मुक्त kiocs
 * @kioc_pool_lock	: protection क्रम मुक्त pool
 * @kioc_semaphore	: so as not to exceed @max_kioc parallel ioctls
 * @mbox_list		: block of mem क्रम @max_kioc number of mboxes
 * @pthru_dma_pool	: DMA pool to allocate passthru packets
 * @dma_pool_list	: array of dma pools
 */

प्रकार काष्ठा mraid_mmadp अणु

/* Filled by driver */

	uपूर्णांक32_t		unique_id;
	uपूर्णांक32_t		drvr_type;
	अचिन्हित दीर्घ		drvr_data;
	uपूर्णांक16_t		समयout;
	uपूर्णांक8_t			max_kioc;

	काष्ठा pci_dev		*pdev;

	पूर्णांक(*issue_uioc)(अचिन्हित दीर्घ, uioc_t *, uपूर्णांक32_t);

/* Maपूर्णांकained by common module */
	uपूर्णांक32_t		quiescent;

	काष्ठा list_head	list;
	uioc_t			*kioc_list;
	काष्ठा list_head	kioc_pool;
	spinlock_t		kioc_pool_lock;
	काष्ठा semaphore	kioc_semaphore;

	mbox64_t		*mbox_list;
	काष्ठा dma_pool		*pthru_dma_pool;
	mm_dmapool_t		dma_pool_list[MAX_DMA_POOLS];

पूर्ण mraid_mmadp_t;

पूर्णांक mraid_mm_रेजिस्टर_adp(mraid_mmadp_t *);
पूर्णांक mraid_mm_unरेजिस्टर_adp(uपूर्णांक32_t);
uपूर्णांक32_t mraid_mm_adapter_app_handle(uपूर्णांक32_t);

#पूर्ण_अगर /* _MEGARAID_IOCTL_H_ */
