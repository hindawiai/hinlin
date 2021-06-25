<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2016-17 IBM Corp.
 */

#अगर_अघोषित _VAS_H
#घोषणा _VAS_H
#समावेश <linux/atomic.h>
#समावेश <linux/idr.h>
#समावेश <यंत्र/vas.h>
#समावेश <linux/पन.स>
#समावेश <linux/dcache.h>
#समावेश <linux/mutex.h>
#समावेश <linux/stringअगरy.h>

/*
 * Overview of Virtual Accelerator Switchboard (VAS).
 *
 * VAS is a hardware "switchboard" that allows senders and receivers to
 * exchange messages with _minimal_ kernel involvment. The receivers are
 * typically NX coprocessor engines that perक्रमm compression or encryption
 * in hardware, but receivers can also be other software thपढ़ोs.
 *
 * Senders are user/kernel thपढ़ोs that submit compression/encryption or
 * other requests to the receivers. Senders must क्रमmat their messages as
 * Coprocessor Request Blocks (CRB)s and submit them using the "copy" and
 * "paste" inकाष्ठाions which were पूर्णांकroduced in Power9.
 *
 * A Power node can have (upto?) 8 Power chips. There is one instance of
 * VAS in each Power9 chip. Each instance of VAS has 64K winकरोws or ports,
 * Senders and receivers must each connect to a separate winकरोw beक्रमe they
 * can exchange messages through the चयनboard.
 *
 * Each winकरोw is described by two types of winकरोw contexts:
 *
 *	Hypervisor Winकरोw Context (HVWC) of size VAS_HVWC_SIZE bytes
 *
 *	OS/User Winकरोw Context (UWC) of size VAS_UWC_SIZE bytes.
 *
 * A winकरोw context can be viewed as a set of 64-bit रेजिस्टरs. The settings
 * in these रेजिस्टरs configure/control/determine the behavior of the VAS
 * hardware when messages are sent/received through the winकरोw. The रेजिस्टरs
 * in the HVWC are configured by the kernel जबतक the रेजिस्टरs in the UWC can
 * be configured by the kernel or by the user space application that is using
 * the winकरोw.
 *
 * The HVWCs क्रम all winकरोws on a specअगरic instance of VAS are in a contiguous
 * range of hardware addresses or Base address region (BAR) referred to as the
 * HVWC BAR क्रम the instance. Similarly the UWCs क्रम all winकरोws on an instance
 * are referred to as the UWC BAR क्रम the instance.
 *
 * The two BARs क्रम each instance are defined Power9 MMIO Ranges spपढ़ोsheet
 * and available to the kernel in the VAS node's "reg" property in the device
 * tree:
 *
 *	/proc/device-tree/vयंत्र@.../reg
 *
 * (see vas_probe() क्रम details on the reg property).
 *
 * The kernel maps the HVWC and UWC BAR regions पूर्णांकo the kernel address
 * space (hvwc_map and uwc_map). The kernel can then access the winकरोw
 * contexts of a specअगरic winकरोw using:
 *
 *	 hvwc = hvwc_map + winid * VAS_HVWC_SIZE.
 *	 uwc = uwc_map + winid * VAS_UWC_SIZE.
 *
 * where winid is the winकरोw index (0..64K).
 *
 * As mentioned, a winकरोw context is used to "configure" a winकरोw. Besides
 * this configuration address, each _send_ winकरोw also has a unique hardware
 * "paste" address that is used to submit requests/CRBs (see vas_paste_crb()).
 *
 * The hardware paste address क्रम a winकरोw is computed using the "paste
 * base address" and "paste win id shअगरt" reg properties in the VAS device
 * tree node using:
 *
 *	paste_addr = paste_base + ((winid << paste_win_id_shअगरt))
 *
 * (again, see vas_probe() क्रम ->paste_base_addr and ->paste_win_id_shअगरt).
 *
 * The kernel maps this hardware address पूर्णांकo the sender's address space
 * after which they can use the 'paste' inकाष्ठाion (new in Power9) to
 * send a message (submit a request aka CRB) to the coprocessor.
 *
 * NOTE: In the initial version, senders can only in-kernel drivers/thपढ़ोs.
 *	 Support क्रम user space thपढ़ोs will be added in follow-on patches.
 *
 * TODO: Do we need to map the UWC पूर्णांकo user address space so they can वापस
 *	 credits? Its NA क्रम NX but may be needed क्रम other receive winकरोws.
 *
 */

#घोषणा VAS_WINDOWS_PER_CHIP		(64 << 10)

/*
 * Hypervisor and OS/USer Winकरोw Context sizes
 */
#घोषणा VAS_HVWC_SIZE			512
#घोषणा VAS_UWC_SIZE			PAGE_SIZE

/*
 * Initial per-process credits.
 * Max send winकरोw credits:    4K-1 (12-bits in VAS_TX_WCRED)
 *
 * TODO: Needs tuning क्रम per-process credits
 */
#घोषणा VAS_TX_WCREDS_MAX		((4 << 10) - 1)
#घोषणा VAS_WCREDS_DEFAULT		(1 << 10)

/*
 * VAS Winकरोw Context Register Offsets and biपंचांगasks.
 * See Section 3.1.4 of VAS Work book
 */
#घोषणा VAS_LPID_OFFSET			0x010
#घोषणा VAS_LPID			PPC_BITMASK(0, 11)

#घोषणा VAS_PID_OFFSET			0x018
#घोषणा VAS_PID_ID			PPC_BITMASK(0, 19)

#घोषणा VAS_XLATE_MSR_OFFSET		0x020
#घोषणा VAS_XLATE_MSR_DR		PPC_BIT(0)
#घोषणा VAS_XLATE_MSR_TA		PPC_BIT(1)
#घोषणा VAS_XLATE_MSR_PR		PPC_BIT(2)
#घोषणा VAS_XLATE_MSR_US		PPC_BIT(3)
#घोषणा VAS_XLATE_MSR_HV		PPC_BIT(4)
#घोषणा VAS_XLATE_MSR_SF		PPC_BIT(5)

#घोषणा VAS_XLATE_LPCR_OFFSET		0x028
#घोषणा VAS_XLATE_LPCR_PAGE_SIZE	PPC_BITMASK(0, 2)
#घोषणा VAS_XLATE_LPCR_ISL		PPC_BIT(3)
#घोषणा VAS_XLATE_LPCR_TC		PPC_BIT(4)
#घोषणा VAS_XLATE_LPCR_SC		PPC_BIT(5)

#घोषणा VAS_XLATE_CTL_OFFSET		0x030
#घोषणा VAS_XLATE_MODE			PPC_BITMASK(0, 1)

#घोषणा VAS_AMR_OFFSET			0x040
#घोषणा VAS_AMR				PPC_BITMASK(0, 63)

#घोषणा VAS_SEIDR_OFFSET		0x048
#घोषणा VAS_SEIDR			PPC_BITMASK(0, 63)

#घोषणा VAS_FAULT_TX_WIN_OFFSET		0x050
#घोषणा VAS_FAULT_TX_WIN		PPC_BITMASK(48, 63)

#घोषणा VAS_OSU_INTR_SRC_RA_OFFSET	0x060
#घोषणा VAS_OSU_INTR_SRC_RA		PPC_BITMASK(8, 63)

#घोषणा VAS_HV_INTR_SRC_RA_OFFSET	0x070
#घोषणा VAS_HV_INTR_SRC_RA		PPC_BITMASK(8, 63)

#घोषणा VAS_PSWID_OFFSET		0x078
#घोषणा VAS_PSWID_EA_HANDLE		PPC_BITMASK(0, 31)

#घोषणा VAS_SPARE1_OFFSET		0x080
#घोषणा VAS_SPARE2_OFFSET		0x088
#घोषणा VAS_SPARE3_OFFSET		0x090
#घोषणा VAS_SPARE4_OFFSET		0x130
#घोषणा VAS_SPARE5_OFFSET		0x160
#घोषणा VAS_SPARE6_OFFSET		0x188

#घोषणा VAS_LFIFO_BAR_OFFSET		0x0A0
#घोषणा VAS_LFIFO_BAR			PPC_BITMASK(8, 53)
#घोषणा VAS_PAGE_MIGRATION_SELECT	PPC_BITMASK(54, 56)

#घोषणा VAS_LDATA_STAMP_CTL_OFFSET	0x0A8
#घोषणा VAS_LDATA_STAMP			PPC_BITMASK(0, 1)
#घोषणा VAS_XTRA_WRITE			PPC_BIT(2)

#घोषणा VAS_LDMA_CACHE_CTL_OFFSET	0x0B0
#घोषणा VAS_LDMA_TYPE			PPC_BITMASK(0, 1)
#घोषणा VAS_LDMA_FIFO_DISABLE		PPC_BIT(2)

#घोषणा VAS_LRFIFO_PUSH_OFFSET		0x0B8
#घोषणा VAS_LRFIFO_PUSH			PPC_BITMASK(0, 15)

#घोषणा VAS_CURR_MSG_COUNT_OFFSET	0x0C0
#घोषणा VAS_CURR_MSG_COUNT		PPC_BITMASK(0, 7)

#घोषणा VAS_LNOTIFY_AFTER_COUNT_OFFSET	0x0C8
#घोषणा VAS_LNOTIFY_AFTER_COUNT		PPC_BITMASK(0, 7)

#घोषणा VAS_LRX_WCRED_OFFSET		0x0E0
#घोषणा VAS_LRX_WCRED			PPC_BITMASK(0, 15)

#घोषणा VAS_LRX_WCRED_ADDER_OFFSET	0x190
#घोषणा VAS_LRX_WCRED_ADDER		PPC_BITMASK(0, 15)

#घोषणा VAS_TX_WCRED_OFFSET		0x0F0
#घोषणा VAS_TX_WCRED			PPC_BITMASK(4, 15)

#घोषणा VAS_TX_WCRED_ADDER_OFFSET	0x1A0
#घोषणा VAS_TX_WCRED_ADDER		PPC_BITMASK(4, 15)

#घोषणा VAS_LFIFO_SIZE_OFFSET		0x100
#घोषणा VAS_LFIFO_SIZE			PPC_BITMASK(0, 3)

#घोषणा VAS_WINCTL_OFFSET		0x108
#घोषणा VAS_WINCTL_OPEN			PPC_BIT(0)
#घोषणा VAS_WINCTL_REJ_NO_CREDIT	PPC_BIT(1)
#घोषणा VAS_WINCTL_PIN			PPC_BIT(2)
#घोषणा VAS_WINCTL_TX_WCRED_MODE	PPC_BIT(3)
#घोषणा VAS_WINCTL_RX_WCRED_MODE	PPC_BIT(4)
#घोषणा VAS_WINCTL_TX_WORD_MODE		PPC_BIT(5)
#घोषणा VAS_WINCTL_RX_WORD_MODE		PPC_BIT(6)
#घोषणा VAS_WINCTL_RSVD_TXBUF		PPC_BIT(7)
#घोषणा VAS_WINCTL_THRESH_CTL		PPC_BITMASK(8, 9)
#घोषणा VAS_WINCTL_FAULT_WIN		PPC_BIT(10)
#घोषणा VAS_WINCTL_NX_WIN		PPC_BIT(11)

#घोषणा VAS_WIN_STATUS_OFFSET		0x110
#घोषणा VAS_WIN_BUSY			PPC_BIT(1)

#घोषणा VAS_WIN_CTX_CACHING_CTL_OFFSET	0x118
#घोषणा VAS_CASTOUT_REQ			PPC_BIT(0)
#घोषणा VAS_PUSH_TO_MEM			PPC_BIT(1)
#घोषणा VAS_WIN_CACHE_STATUS		PPC_BIT(4)

#घोषणा VAS_TX_RSVD_BUF_COUNT_OFFSET	0x120
#घोषणा VAS_RXVD_BUF_COUNT		PPC_BITMASK(58, 63)

#घोषणा VAS_LRFIFO_WIN_PTR_OFFSET	0x128
#घोषणा VAS_LRX_WIN_ID			PPC_BITMASK(0, 15)

/*
 * Local Notअगरication Control Register controls what happens in _response_
 * to a paste command and hence applies only to receive winकरोws.
 */
#घोषणा VAS_LNOTIFY_CTL_OFFSET		0x138
#घोषणा VAS_NOTIFY_DISABLE		PPC_BIT(0)
#घोषणा VAS_INTR_DISABLE		PPC_BIT(1)
#घोषणा VAS_NOTIFY_EARLY		PPC_BIT(2)
#घोषणा VAS_NOTIFY_OSU_INTR		PPC_BIT(3)

#घोषणा VAS_LNOTIFY_PID_OFFSET		0x140
#घोषणा VAS_LNOTIFY_PID			PPC_BITMASK(0, 19)

#घोषणा VAS_LNOTIFY_LPID_OFFSET		0x148
#घोषणा VAS_LNOTIFY_LPID		PPC_BITMASK(0, 11)

#घोषणा VAS_LNOTIFY_TID_OFFSET		0x150
#घोषणा VAS_LNOTIFY_TID			PPC_BITMASK(0, 15)

#घोषणा VAS_LNOTIFY_SCOPE_OFFSET	0x158
#घोषणा VAS_LNOTIFY_MIN_SCOPE		PPC_BITMASK(0, 1)
#घोषणा VAS_LNOTIFY_MAX_SCOPE		PPC_BITMASK(2, 3)

#घोषणा VAS_NX_UTIL_OFFSET		0x1B0
#घोषणा VAS_NX_UTIL			PPC_BITMASK(0, 63)

/* SE: Side effects */
#घोषणा VAS_NX_UTIL_SE_OFFSET		0x1B8
#घोषणा VAS_NX_UTIL_SE			PPC_BITMASK(0, 63)

#घोषणा VAS_NX_UTIL_ADDER_OFFSET	0x180
#घोषणा VAS_NX_UTIL_ADDER		PPC_BITMASK(32, 63)

/*
 * VREG(x):
 * Expand a रेजिस्टर's लघु name (eg: LPID) पूर्णांकo two parameters:
 *	- the रेजिस्टर's लघु name in string क्रमm ("LPID"), and
 *	- the name of the macro (eg: VAS_LPID_OFFSET), defining the
 *	  रेजिस्टर's offset in the winकरोw context
 */
#घोषणा VREG_SFX(n, s)	__stringअगरy(n), VAS_##n##s
#घोषणा VREG(r)		VREG_SFX(r, _OFFSET)

/*
 * Local Notअगरy Scope Control Register. (Receive winकरोws only).
 */
क्रमागत vas_notअगरy_scope अणु
	VAS_SCOPE_LOCAL,
	VAS_SCOPE_GROUP,
	VAS_SCOPE_VECTORED_GROUP,
	VAS_SCOPE_UNUSED,
पूर्ण;

/*
 * Local DMA Cache Control Register (Receive winकरोws only).
 */
क्रमागत vas_dma_type अणु
	VAS_DMA_TYPE_INJECT,
	VAS_DMA_TYPE_WRITE,
पूर्ण;

/*
 * Local Notअगरy Scope Control Register. (Receive winकरोws only).
 * Not applicable to NX receive winकरोws.
 */
क्रमागत vas_notअगरy_after_count अणु
	VAS_NOTIFY_AFTER_256 = 0,
	VAS_NOTIFY_NONE,
	VAS_NOTIFY_AFTER_2
पूर्ण;

/*
 * NX can generate an पूर्णांकerrupt क्रम multiple faults and expects kernel
 * to process all of them. So पढ़ो all valid CRB entries until find the
 * invalid one. So use pswid which is pasted by NX and ccw[0] (reserved
 * bit in BE) to check valid CRB. CCW[0] will not be touched by user
 * space. Application माला_लो CRB क्रमmt error अगर it updates this bit.
 *
 * Invalidate FIFO during allocation and process all entries from last
 * successful पढ़ो until finds invalid pswid and ccw[0] values.
 * After पढ़ोing each CRB entry from fault FIFO, the kernel invalidate
 * it by updating pswid with FIFO_INVALID_ENTRY and CCW[0] with
 * CCW0_INVALID.
 */
#घोषणा FIFO_INVALID_ENTRY	0xffffffff
#घोषणा CCW0_INVALID		1

/*
 * One per instance of VAS. Each instance will have a separate set of
 * receive winकरोws, one per coprocessor type.
 *
 * See also function header of set_vinst_win() क्रम details on ->winकरोws[]
 * and ->rxwin[] tables.
 */
काष्ठा vas_instance अणु
	पूर्णांक vas_id;
	काष्ठा ida ida;
	काष्ठा list_head node;
	काष्ठा platक्रमm_device *pdev;

	u64 hvwc_bar_start;
	u64 uwc_bar_start;
	u64 paste_base_addr;
	u64 paste_win_id_shअगरt;

	u64 irq_port;
	पूर्णांक virq;
	पूर्णांक fault_crbs;
	पूर्णांक fault_fअगरo_size;
	पूर्णांक fअगरo_in_progress;	/* To wake up thपढ़ो or वापस IRQ_HANDLED */
	spinlock_t fault_lock;	/* Protects fअगरo_in_progress update */
	व्योम *fault_fअगरo;
	काष्ठा vas_winकरोw *fault_win; /* Fault winकरोw */

	काष्ठा mutex mutex;
	काष्ठा vas_winकरोw *rxwin[VAS_COP_TYPE_MAX];
	काष्ठा vas_winकरोw *winकरोws[VAS_WINDOWS_PER_CHIP];

	अक्षर *name;
	अक्षर *dbgname;
	काष्ठा dentry *dbgdir;
पूर्ण;

/*
 * In-kernel state a VAS winकरोw. One per winकरोw.
 */
काष्ठा vas_winकरोw अणु
	/* Fields common to send and receive winकरोws */
	काष्ठा vas_instance *vinst;
	पूर्णांक winid;
	bool tx_win;		/* True अगर send winकरोw */
	bool nx_win;		/* True अगर NX winकरोw */
	bool user_win;		/* True अगर user space winकरोw */
	व्योम *hvwc_map;		/* HV winकरोw context */
	व्योम *uwc_map;		/* OS/User winकरोw context */
	काष्ठा pid *pid;	/* Linux process id of owner */
	काष्ठा pid *tgid;	/* Thपढ़ो group ID of owner */
	काष्ठा mm_काष्ठा *mm;	/* Linux process mm_काष्ठा */
	पूर्णांक wcreds_max;		/* Winकरोw credits */

	अक्षर *dbgname;
	काष्ठा dentry *dbgdir;

	/* Fields applicable only to send winकरोws */
	व्योम *paste_kaddr;
	अक्षर *paste_addr_name;
	काष्ठा vas_winकरोw *rxwin;

	/* Feilds applicable only to receive winकरोws */
	क्रमागत vas_cop_type cop;
	atomic_t num_txwins;
पूर्ण;

/*
 * Container क्रम the hardware state of a winकरोw. One per-winकरोw.
 *
 * A VAS Winकरोw context is a 512-byte area in the hardware that contains
 * a set of 64-bit रेजिस्टरs. Inभागidual bit-fields in these रेजिस्टरs
 * determine the configuration/operation of the hardware. काष्ठा vas_winctx
 * is a container क्रम the रेजिस्टर fields in the winकरोw context.
 */
काष्ठा vas_winctx अणु
	व्योम *rx_fअगरo;
	पूर्णांक rx_fअगरo_size;
	पूर्णांक wcreds_max;
	पूर्णांक rsvd_txbuf_count;

	bool user_win;
	bool nx_win;
	bool fault_win;
	bool rsvd_txbuf_enable;
	bool pin_win;
	bool rej_no_credit;
	bool tx_wcred_mode;
	bool rx_wcred_mode;
	bool tx_word_mode;
	bool rx_word_mode;
	bool data_stamp;
	bool xtra_ग_लिखो;
	bool notअगरy_disable;
	bool पूर्णांकr_disable;
	bool fअगरo_disable;
	bool notअगरy_early;
	bool notअगरy_os_पूर्णांकr_reg;

	पूर्णांक lpid;
	पूर्णांक pidr;		/* value from SPRN_PID, not linux pid */
	पूर्णांक lnotअगरy_lpid;
	पूर्णांक lnotअगरy_pid;
	पूर्णांक lnotअगरy_tid;
	u32 pswid;
	पूर्णांक rx_win_id;
	पूर्णांक fault_win_id;
	पूर्णांक tc_mode;

	u64 irq_port;

	क्रमागत vas_dma_type dma_type;
	क्रमागत vas_notअगरy_scope min_scope;
	क्रमागत vas_notअगरy_scope max_scope;
	क्रमागत vas_notअगरy_after_count notअगरy_after_count;
पूर्ण;

बाह्य काष्ठा mutex vas_mutex;

बाह्य काष्ठा vas_instance *find_vas_instance(पूर्णांक vasid);
बाह्य व्योम vas_init_dbgdir(व्योम);
बाह्य व्योम vas_instance_init_dbgdir(काष्ठा vas_instance *vinst);
बाह्य व्योम vas_winकरोw_init_dbgdir(काष्ठा vas_winकरोw *win);
बाह्य व्योम vas_winकरोw_मुक्त_dbgdir(काष्ठा vas_winकरोw *win);
बाह्य पूर्णांक vas_setup_fault_winकरोw(काष्ठा vas_instance *vinst);
बाह्य irqवापस_t vas_fault_thपढ़ो_fn(पूर्णांक irq, व्योम *data);
बाह्य irqवापस_t vas_fault_handler(पूर्णांक irq, व्योम *dev_id);
बाह्य व्योम vas_वापस_credit(काष्ठा vas_winकरोw *winकरोw, bool tx);
बाह्य काष्ठा vas_winकरोw *vas_pswid_to_winकरोw(काष्ठा vas_instance *vinst,
						uपूर्णांक32_t pswid);
बाह्य व्योम vas_win_paste_addr(काष्ठा vas_winकरोw *winकरोw, u64 *addr,
					पूर्णांक *len);

अटल अंतरभूत पूर्णांक vas_winकरोw_pid(काष्ठा vas_winकरोw *winकरोw)
अणु
	वापस pid_vnr(winकरोw->pid);
पूर्ण

अटल अंतरभूत व्योम vas_log_ग_लिखो(काष्ठा vas_winकरोw *win, अक्षर *name,
			व्योम *regptr, u64 val)
अणु
	अगर (val)
		pr_debug("%swin #%d: %s reg %p, val 0x%016llx\n",
				win->tx_win ? "Tx" : "Rx", win->winid, name,
				regptr, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_uwc_reg(काष्ठा vas_winकरोw *win, अक्षर *name,
			s32 reg, u64 val)
अणु
	व्योम *regptr;

	regptr = win->uwc_map + reg;
	vas_log_ग_लिखो(win, name, regptr, val);

	out_be64(regptr, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_hvwc_reg(काष्ठा vas_winकरोw *win, अक्षर *name,
			s32 reg, u64 val)
अणु
	व्योम *regptr;

	regptr = win->hvwc_map + reg;
	vas_log_ग_लिखो(win, name, regptr, val);

	out_be64(regptr, val);
पूर्ण

अटल अंतरभूत u64 पढ़ो_hvwc_reg(काष्ठा vas_winकरोw *win,
			अक्षर *name __maybe_unused, s32 reg)
अणु
	वापस in_be64(win->hvwc_map+reg);
पूर्ण

/*
 * Encode/decode the Partition Send Winकरोw ID (PSWID) क्रम a winकरोw in
 * a way that we can uniquely identअगरy any winकरोw in the प्रणाली. i.e.
 * we should be able to locate the 'struct vas_window' given the PSWID.
 *
 *	Bits	Usage
 *	0:7	VAS id (8 bits)
 *	8:15	Unused, 0 (3 bits)
 *	16:31	Winकरोw id (16 bits)
 */
अटल अंतरभूत u32 encode_pswid(पूर्णांक vasid, पूर्णांक winid)
अणु
	वापस ((u32)winid | (vasid << (31 - 7)));
पूर्ण

अटल अंतरभूत व्योम decode_pswid(u32 pswid, पूर्णांक *vasid, पूर्णांक *winid)
अणु
	अगर (vasid)
		*vasid = pswid >> (31 - 7) & 0xFF;

	अगर (winid)
		*winid = pswid & 0xFFFF;
पूर्ण
#पूर्ण_अगर /* _VAS_H */
