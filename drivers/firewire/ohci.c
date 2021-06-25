<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम OHCI 1394 controllers
 *
 * Copyright (C) 2003-2006 Kristian Hoegsberg <krh@bitplanet.net>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/pmac_feature.h>
#पूर्ण_अगर

#समावेश "core.h"
#समावेश "ohci.h"

#घोषणा ohci_info(ohci, f, args...)	dev_info(ohci->card.device, f, ##args)
#घोषणा ohci_notice(ohci, f, args...)	dev_notice(ohci->card.device, f, ##args)
#घोषणा ohci_err(ohci, f, args...)	dev_err(ohci->card.device, f, ##args)

#घोषणा DESCRIPTOR_OUTPUT_MORE		0
#घोषणा DESCRIPTOR_OUTPUT_LAST		(1 << 12)
#घोषणा DESCRIPTOR_INPUT_MORE		(2 << 12)
#घोषणा DESCRIPTOR_INPUT_LAST		(3 << 12)
#घोषणा DESCRIPTOR_STATUS		(1 << 11)
#घोषणा DESCRIPTOR_KEY_IMMEDIATE	(2 << 8)
#घोषणा DESCRIPTOR_PING			(1 << 7)
#घोषणा DESCRIPTOR_YY			(1 << 6)
#घोषणा DESCRIPTOR_NO_IRQ		(0 << 4)
#घोषणा DESCRIPTOR_IRQ_ERROR		(1 << 4)
#घोषणा DESCRIPTOR_IRQ_ALWAYS		(3 << 4)
#घोषणा DESCRIPTOR_BRANCH_ALWAYS	(3 << 2)
#घोषणा DESCRIPTOR_WAIT			(3 << 0)

#घोषणा DESCRIPTOR_CMD			(0xf << 12)

काष्ठा descriptor अणु
	__le16 req_count;
	__le16 control;
	__le32 data_address;
	__le32 branch_address;
	__le16 res_count;
	__le16 transfer_status;
पूर्ण __attribute__((aligned(16)));

#घोषणा CONTROL_SET(regs)	(regs)
#घोषणा CONTROL_CLEAR(regs)	((regs) + 4)
#घोषणा COMMAND_PTR(regs)	((regs) + 12)
#घोषणा CONTEXT_MATCH(regs)	((regs) + 16)

#घोषणा AR_BUFFER_SIZE	(32*1024)
#घोषणा AR_BUFFERS_MIN	DIV_ROUND_UP(AR_BUFFER_SIZE, PAGE_SIZE)
/* we need at least two pages क्रम proper list management */
#घोषणा AR_BUFFERS	(AR_BUFFERS_MIN >= 2 ? AR_BUFFERS_MIN : 2)

#घोषणा MAX_ASYNC_PAYLOAD	4096
#घोषणा MAX_AR_PACKET_SIZE	(16 + MAX_ASYNC_PAYLOAD + 4)
#घोषणा AR_WRAPAROUND_PAGES	DIV_ROUND_UP(MAX_AR_PACKET_SIZE, PAGE_SIZE)

काष्ठा ar_context अणु
	काष्ठा fw_ohci *ohci;
	काष्ठा page *pages[AR_BUFFERS];
	व्योम *buffer;
	काष्ठा descriptor *descriptors;
	dma_addr_t descriptors_bus;
	व्योम *poपूर्णांकer;
	अचिन्हित पूर्णांक last_buffer_index;
	u32 regs;
	काष्ठा tasklet_काष्ठा tasklet;
पूर्ण;

काष्ठा context;

प्रकार पूर्णांक (*descriptor_callback_t)(काष्ठा context *ctx,
				     काष्ठा descriptor *d,
				     काष्ठा descriptor *last);

/*
 * A buffer that contains a block of DMA-able coherent memory used क्रम
 * storing a portion of a DMA descriptor program.
 */
काष्ठा descriptor_buffer अणु
	काष्ठा list_head list;
	dma_addr_t buffer_bus;
	माप_प्रकार buffer_size;
	माप_प्रकार used;
	काष्ठा descriptor buffer[];
पूर्ण;

काष्ठा context अणु
	काष्ठा fw_ohci *ohci;
	u32 regs;
	पूर्णांक total_allocation;
	u32 current_bus;
	bool running;
	bool flushing;

	/*
	 * List of page-sized buffers क्रम storing DMA descriptors.
	 * Head of list contains buffers in use and tail of list contains
	 * मुक्त buffers.
	 */
	काष्ठा list_head buffer_list;

	/*
	 * Poपूर्णांकer to a buffer inside buffer_list that contains the tail
	 * end of the current DMA program.
	 */
	काष्ठा descriptor_buffer *buffer_tail;

	/*
	 * The descriptor containing the branch address of the first
	 * descriptor that has not yet been filled by the device.
	 */
	काष्ठा descriptor *last;

	/*
	 * The last descriptor block in the DMA program. It contains the branch
	 * address that must be updated upon appending a new descriptor.
	 */
	काष्ठा descriptor *prev;
	पूर्णांक prev_z;

	descriptor_callback_t callback;

	काष्ठा tasklet_काष्ठा tasklet;
पूर्ण;

#घोषणा IT_HEADER_SY(v)          ((v) <<  0)
#घोषणा IT_HEADER_TCODE(v)       ((v) <<  4)
#घोषणा IT_HEADER_CHANNEL(v)     ((v) <<  8)
#घोषणा IT_HEADER_TAG(v)         ((v) << 14)
#घोषणा IT_HEADER_SPEED(v)       ((v) << 16)
#घोषणा IT_HEADER_DATA_LENGTH(v) ((v) << 16)

काष्ठा iso_context अणु
	काष्ठा fw_iso_context base;
	काष्ठा context context;
	व्योम *header;
	माप_प्रकार header_length;
	अचिन्हित दीर्घ flushing_completions;
	u32 mc_buffer_bus;
	u16 mc_completed;
	u16 last_बारtamp;
	u8 sync;
	u8 tags;
पूर्ण;

#घोषणा CONFIG_ROM_SIZE 1024

काष्ठा fw_ohci अणु
	काष्ठा fw_card card;

	__iomem अक्षर *रेजिस्टरs;
	पूर्णांक node_id;
	पूर्णांक generation;
	पूर्णांक request_generation;	/* क्रम बारtamping incoming requests */
	अचिन्हित quirks;
	अचिन्हित पूर्णांक pri_req_max;
	u32 bus_समय;
	bool bus_समय_running;
	bool is_root;
	bool csr_state_setclear_abdicate;
	पूर्णांक n_ir;
	पूर्णांक n_it;
	/*
	 * Spinlock क्रम accessing fw_ohci data.  Never call out of
	 * this driver with this lock held.
	 */
	spinlock_t lock;

	काष्ठा mutex phy_reg_mutex;

	व्योम *misc_buffer;
	dma_addr_t misc_buffer_bus;

	काष्ठा ar_context ar_request_ctx;
	काष्ठा ar_context ar_response_ctx;
	काष्ठा context at_request_ctx;
	काष्ठा context at_response_ctx;

	u32 it_context_support;
	u32 it_context_mask;     /* unoccupied IT contexts */
	काष्ठा iso_context *it_context_list;
	u64 ir_context_channels; /* unoccupied channels */
	u32 ir_context_support;
	u32 ir_context_mask;     /* unoccupied IR contexts */
	काष्ठा iso_context *ir_context_list;
	u64 mc_channels; /* channels in use by the multichannel IR context */
	bool mc_allocated;

	__be32    *config_rom;
	dma_addr_t config_rom_bus;
	__be32    *next_config_rom;
	dma_addr_t next_config_rom_bus;
	__be32     next_header;

	__le32    *self_id;
	dma_addr_t self_id_bus;
	काष्ठा work_काष्ठा bus_reset_work;

	u32 self_id_buffer[512];
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *selfid_workqueue;

अटल अंतरभूत काष्ठा fw_ohci *fw_ohci(काष्ठा fw_card *card)
अणु
	वापस container_of(card, काष्ठा fw_ohci, card);
पूर्ण

#घोषणा IT_CONTEXT_CYCLE_MATCH_ENABLE	0x80000000
#घोषणा IR_CONTEXT_BUFFER_FILL		0x80000000
#घोषणा IR_CONTEXT_ISOCH_HEADER		0x40000000
#घोषणा IR_CONTEXT_CYCLE_MATCH_ENABLE	0x20000000
#घोषणा IR_CONTEXT_MULTI_CHANNEL_MODE	0x10000000
#घोषणा IR_CONTEXT_DUAL_BUFFER_MODE	0x08000000

#घोषणा CONTEXT_RUN	0x8000
#घोषणा CONTEXT_WAKE	0x1000
#घोषणा CONTEXT_DEAD	0x0800
#घोषणा CONTEXT_ACTIVE	0x0400

#घोषणा OHCI1394_MAX_AT_REQ_RETRIES	0xf
#घोषणा OHCI1394_MAX_AT_RESP_RETRIES	0x2
#घोषणा OHCI1394_MAX_PHYS_RESP_RETRIES	0x8

#घोषणा OHCI1394_REGISTER_SIZE		0x800
#घोषणा OHCI1394_PCI_HCI_Control	0x40
#घोषणा SELF_ID_BUF_SIZE		0x800
#घोषणा OHCI_TCODE_PHY_PACKET		0x0e
#घोषणा OHCI_VERSION_1_1		0x010010

अटल अक्षर ohci_driver_name[] = KBUILD_MODNAME;

#घोषणा PCI_VENDOR_ID_PINNACLE_SYSTEMS	0x11bd
#घोषणा PCI_DEVICE_ID_AGERE_FW643	0x5901
#घोषणा PCI_DEVICE_ID_CREATIVE_SB1394	0x4001
#घोषणा PCI_DEVICE_ID_JMICRON_JMB38X_FW	0x2380
#घोषणा PCI_DEVICE_ID_TI_TSB12LV22	0x8009
#घोषणा PCI_DEVICE_ID_TI_TSB12LV26	0x8020
#घोषणा PCI_DEVICE_ID_TI_TSB82AA2	0x8025
#घोषणा PCI_DEVICE_ID_VIA_VT630X	0x3044
#घोषणा PCI_REV_ID_VIA_VT6306		0x46
#घोषणा PCI_DEVICE_ID_VIA_VT6315	0x3403

#घोषणा QUIRK_CYCLE_TIMER		0x1
#घोषणा QUIRK_RESET_PACKET		0x2
#घोषणा QUIRK_BE_HEADERS		0x4
#घोषणा QUIRK_NO_1394A			0x8
#घोषणा QUIRK_NO_MSI			0x10
#घोषणा QUIRK_TI_SLLZ059		0x20
#घोषणा QUIRK_IR_WAKE			0x40

/* In हाल of multiple matches in ohci_quirks[], only the first one is used. */
अटल स्थिर काष्ठा अणु
	अचिन्हित लघु venकरोr, device, revision, flags;
पूर्ण ohci_quirks[] = अणु
	अणुPCI_VENDOR_ID_AL, PCI_ANY_ID, PCI_ANY_ID,
		QUIRK_CYCLE_TIMERपूर्ण,

	अणुPCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_UNI_N_FW, PCI_ANY_ID,
		QUIRK_BE_HEADERSपूर्ण,

	अणुPCI_VENDOR_ID_ATT, PCI_DEVICE_ID_AGERE_FW643, 6,
		QUIRK_NO_MSIपूर्ण,

	अणुPCI_VENDOR_ID_CREATIVE, PCI_DEVICE_ID_CREATIVE_SB1394, PCI_ANY_ID,
		QUIRK_RESET_PACKETपूर्ण,

	अणुPCI_VENDOR_ID_JMICRON, PCI_DEVICE_ID_JMICRON_JMB38X_FW, PCI_ANY_ID,
		QUIRK_NO_MSIपूर्ण,

	अणुPCI_VENDOR_ID_NEC, PCI_ANY_ID, PCI_ANY_ID,
		QUIRK_CYCLE_TIMERपूर्ण,

	अणुPCI_VENDOR_ID_O2, PCI_ANY_ID, PCI_ANY_ID,
		QUIRK_NO_MSIपूर्ण,

	अणुPCI_VENDOR_ID_RICOH, PCI_ANY_ID, PCI_ANY_ID,
		QUIRK_CYCLE_TIMER | QUIRK_NO_MSIपूर्ण,

	अणुPCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_TSB12LV22, PCI_ANY_ID,
		QUIRK_CYCLE_TIMER | QUIRK_RESET_PACKET | QUIRK_NO_1394Aपूर्ण,

	अणुPCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_TSB12LV26, PCI_ANY_ID,
		QUIRK_RESET_PACKET | QUIRK_TI_SLLZ059पूर्ण,

	अणुPCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_TSB82AA2, PCI_ANY_ID,
		QUIRK_RESET_PACKET | QUIRK_TI_SLLZ059पूर्ण,

	अणुPCI_VENDOR_ID_TI, PCI_ANY_ID, PCI_ANY_ID,
		QUIRK_RESET_PACKETपूर्ण,

	अणुPCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VT630X, PCI_REV_ID_VIA_VT6306,
		QUIRK_CYCLE_TIMER | QUIRK_IR_WAKEपूर्ण,

	अणुPCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VT6315, 0,
		QUIRK_CYCLE_TIMER /* FIXME: necessary? */ | QUIRK_NO_MSIपूर्ण,

	अणुPCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VT6315, PCI_ANY_ID,
		QUIRK_NO_MSIपूर्ण,

	अणुPCI_VENDOR_ID_VIA, PCI_ANY_ID, PCI_ANY_ID,
		QUIRK_CYCLE_TIMER | QUIRK_NO_MSIपूर्ण,
पूर्ण;

/* This overrides anything that was found in ohci_quirks[]. */
अटल पूर्णांक param_quirks;
module_param_named(quirks, param_quirks, पूर्णांक, 0644);
MODULE_PARM_DESC(quirks, "Chip quirks (default = 0"
	", nonatomic cycle timer = "	__stringअगरy(QUIRK_CYCLE_TIMER)
	", reset packet generation = "	__stringअगरy(QUIRK_RESET_PACKET)
	", AR/selfID endianness = "	__stringअगरy(QUIRK_BE_HEADERS)
	", no 1394a enhancements = "	__stringअगरy(QUIRK_NO_1394A)
	", disable MSI = "		__stringअगरy(QUIRK_NO_MSI)
	", TI SLLZ059 erratum = "	__stringअगरy(QUIRK_TI_SLLZ059)
	", IR wake unreliable = "	__stringअगरy(QUIRK_IR_WAKE)
	")");

#घोषणा OHCI_PARAM_DEBUG_AT_AR		1
#घोषणा OHCI_PARAM_DEBUG_SELFIDS	2
#घोषणा OHCI_PARAM_DEBUG_IRQS		4
#घोषणा OHCI_PARAM_DEBUG_BUSRESETS	8 /* only effective beक्रमe chip init */

अटल पूर्णांक param_debug;
module_param_named(debug, param_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Verbose logging (default = 0"
	", AT/AR events = "	__stringअगरy(OHCI_PARAM_DEBUG_AT_AR)
	", self-IDs = "		__stringअगरy(OHCI_PARAM_DEBUG_SELFIDS)
	", IRQs = "		__stringअगरy(OHCI_PARAM_DEBUG_IRQS)
	", busReset events = "	__stringअगरy(OHCI_PARAM_DEBUG_BUSRESETS)
	", or a combination, or all = -1)");

अटल bool param_remote_dma;
module_param_named(remote_dma, param_remote_dma, bool, 0444);
MODULE_PARM_DESC(remote_dma, "Enable unfiltered remote DMA (default = N)");

अटल व्योम log_irqs(काष्ठा fw_ohci *ohci, u32 evt)
अणु
	अगर (likely(!(param_debug &
			(OHCI_PARAM_DEBUG_IRQS | OHCI_PARAM_DEBUG_BUSRESETS))))
		वापस;

	अगर (!(param_debug & OHCI_PARAM_DEBUG_IRQS) &&
	    !(evt & OHCI1394_busReset))
		वापस;

	ohci_notice(ohci, "IRQ %08x%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", evt,
	    evt & OHCI1394_selfIDComplete	? " selfID"		: "",
	    evt & OHCI1394_RQPkt		? " AR_req"		: "",
	    evt & OHCI1394_RSPkt		? " AR_resp"		: "",
	    evt & OHCI1394_reqTxComplete	? " AT_req"		: "",
	    evt & OHCI1394_respTxComplete	? " AT_resp"		: "",
	    evt & OHCI1394_isochRx		? " IR"			: "",
	    evt & OHCI1394_isochTx		? " IT"			: "",
	    evt & OHCI1394_postedWriteErr	? " postedWriteErr"	: "",
	    evt & OHCI1394_cycleTooLong		? " cycleTooLong"	: "",
	    evt & OHCI1394_cycle64Seconds	? " cycle64Seconds"	: "",
	    evt & OHCI1394_cycleInconsistent	? " cycleInconsistent"	: "",
	    evt & OHCI1394_regAccessFail	? " regAccessFail"	: "",
	    evt & OHCI1394_unrecoverableError	? " unrecoverableError"	: "",
	    evt & OHCI1394_busReset		? " busReset"		: "",
	    evt & ~(OHCI1394_selfIDComplete | OHCI1394_RQPkt |
		    OHCI1394_RSPkt | OHCI1394_reqTxComplete |
		    OHCI1394_respTxComplete | OHCI1394_isochRx |
		    OHCI1394_isochTx | OHCI1394_postedWriteErr |
		    OHCI1394_cycleTooLong | OHCI1394_cycle64Seconds |
		    OHCI1394_cycleInconsistent |
		    OHCI1394_regAccessFail | OHCI1394_busReset)
						? " ?"			: "");
पूर्ण

अटल स्थिर अक्षर *speed[] = अणु
	[0] = "S100", [1] = "S200", [2] = "S400",    [3] = "beta",
पूर्ण;
अटल स्थिर अक्षर *घातer[] = अणु
	[0] = "+0W",  [1] = "+15W", [2] = "+30W",    [3] = "+45W",
	[4] = "-3W",  [5] = " ?W",  [6] = "-3..-6W", [7] = "-3..-10W",
पूर्ण;
अटल स्थिर अक्षर port[] = अणु '.', '-', 'p', 'c', पूर्ण;

अटल अक्षर _p(u32 *s, पूर्णांक shअगरt)
अणु
	वापस port[*s >> shअगरt & 3];
पूर्ण

अटल व्योम log_selfids(काष्ठा fw_ohci *ohci, पूर्णांक generation, पूर्णांक self_id_count)
अणु
	u32 *s;

	अगर (likely(!(param_debug & OHCI_PARAM_DEBUG_SELFIDS)))
		वापस;

	ohci_notice(ohci, "%d selfIDs, generation %d, local node ID %04x\n",
		    self_id_count, generation, ohci->node_id);

	क्रम (s = ohci->self_id_buffer; self_id_count--; ++s)
		अगर ((*s & 1 << 23) == 0)
			ohci_notice(ohci,
			    "selfID 0: %08x, phy %d [%c%c%c] %s gc=%d %s %s%s%s\n",
			    *s, *s >> 24 & 63, _p(s, 6), _p(s, 4), _p(s, 2),
			    speed[*s >> 14 & 3], *s >> 16 & 63,
			    घातer[*s >> 8 & 7], *s >> 22 & 1 ? "L" : "",
			    *s >> 11 & 1 ? "c" : "", *s & 2 ? "i" : "");
		अन्यथा
			ohci_notice(ohci,
			    "selfID n: %08x, phy %d [%c%c%c%c%c%c%c%c]\n",
			    *s, *s >> 24 & 63,
			    _p(s, 16), _p(s, 14), _p(s, 12), _p(s, 10),
			    _p(s,  8), _p(s,  6), _p(s,  4), _p(s,  2));
पूर्ण

अटल स्थिर अक्षर *evts[] = अणु
	[0x00] = "evt_no_status",	[0x01] = "-reserved-",
	[0x02] = "evt_long_packet",	[0x03] = "evt_missing_ack",
	[0x04] = "evt_underrun",	[0x05] = "evt_overrun",
	[0x06] = "evt_descriptor_read",	[0x07] = "evt_data_read",
	[0x08] = "evt_data_write",	[0x09] = "evt_bus_reset",
	[0x0a] = "evt_timeout",		[0x0b] = "evt_tcode_err",
	[0x0c] = "-reserved-",		[0x0d] = "-reserved-",
	[0x0e] = "evt_unknown",		[0x0f] = "evt_flushed",
	[0x10] = "-reserved-",		[0x11] = "ack_complete",
	[0x12] = "ack_pending ",	[0x13] = "-reserved-",
	[0x14] = "ack_busy_X",		[0x15] = "ack_busy_A",
	[0x16] = "ack_busy_B",		[0x17] = "-reserved-",
	[0x18] = "-reserved-",		[0x19] = "-reserved-",
	[0x1a] = "-reserved-",		[0x1b] = "ack_tardy",
	[0x1c] = "-reserved-",		[0x1d] = "ack_data_error",
	[0x1e] = "ack_type_error",	[0x1f] = "-reserved-",
	[0x20] = "pending/cancelled",
पूर्ण;
अटल स्थिर अक्षर *tcodes[] = अणु
	[0x0] = "QW req",		[0x1] = "BW req",
	[0x2] = "W resp",		[0x3] = "-reserved-",
	[0x4] = "QR req",		[0x5] = "BR req",
	[0x6] = "QR resp",		[0x7] = "BR resp",
	[0x8] = "cycle start",		[0x9] = "Lk req",
	[0xa] = "async stream packet",	[0xb] = "Lk resp",
	[0xc] = "-reserved-",		[0xd] = "-reserved-",
	[0xe] = "link internal",	[0xf] = "-reserved-",
पूर्ण;

अटल व्योम log_ar_at_event(काष्ठा fw_ohci *ohci,
			    अक्षर dir, पूर्णांक speed, u32 *header, पूर्णांक evt)
अणु
	पूर्णांक tcode = header[0] >> 4 & 0xf;
	अक्षर specअगरic[12];

	अगर (likely(!(param_debug & OHCI_PARAM_DEBUG_AT_AR)))
		वापस;

	अगर (unlikely(evt >= ARRAY_SIZE(evts)))
			evt = 0x1f;

	अगर (evt == OHCI1394_evt_bus_reset) अणु
		ohci_notice(ohci, "A%c evt_bus_reset, generation %d\n",
			    dir, (header[2] >> 16) & 0xff);
		वापस;
	पूर्ण

	चयन (tcode) अणु
	हाल 0x0: हाल 0x6: हाल 0x8:
		snम_लिखो(specअगरic, माप(specअगरic), " = %08x",
			 be32_to_cpu((__क्रमce __be32)header[3]));
		अवरोध;
	हाल 0x1: हाल 0x5: हाल 0x7: हाल 0x9: हाल 0xb:
		snम_लिखो(specअगरic, माप(specअगरic), " %x,%x",
			 header[3] >> 16, header[3] & 0xffff);
		अवरोध;
	शेष:
		specअगरic[0] = '\0';
	पूर्ण

	चयन (tcode) अणु
	हाल 0xa:
		ohci_notice(ohci, "A%c %s, %s\n",
			    dir, evts[evt], tcodes[tcode]);
		अवरोध;
	हाल 0xe:
		ohci_notice(ohci, "A%c %s, PHY %08x %08x\n",
			    dir, evts[evt], header[1], header[2]);
		अवरोध;
	हाल 0x0: हाल 0x1: हाल 0x4: हाल 0x5: हाल 0x9:
		ohci_notice(ohci,
			    "A%c spd %x tl %02x, %04x -> %04x, %s, %s, %04x%08x%s\n",
			    dir, speed, header[0] >> 10 & 0x3f,
			    header[1] >> 16, header[0] >> 16, evts[evt],
			    tcodes[tcode], header[1] & 0xffff, header[2], specअगरic);
		अवरोध;
	शेष:
		ohci_notice(ohci,
			    "A%c spd %x tl %02x, %04x -> %04x, %s, %s%s\n",
			    dir, speed, header[0] >> 10 & 0x3f,
			    header[1] >> 16, header[0] >> 16, evts[evt],
			    tcodes[tcode], specअगरic);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम reg_ग_लिखो(स्थिर काष्ठा fw_ohci *ohci, पूर्णांक offset, u32 data)
अणु
	ग_लिखोl(data, ohci->रेजिस्टरs + offset);
पूर्ण

अटल अंतरभूत u32 reg_पढ़ो(स्थिर काष्ठा fw_ohci *ohci, पूर्णांक offset)
अणु
	वापस पढ़ोl(ohci->रेजिस्टरs + offset);
पूर्ण

अटल अंतरभूत व्योम flush_ग_लिखोs(स्थिर काष्ठा fw_ohci *ohci)
अणु
	/* Do a dummy पढ़ो to flush ग_लिखोs. */
	reg_पढ़ो(ohci, OHCI1394_Version);
पूर्ण

/*
 * Beware!  पढ़ो_phy_reg(), ग_लिखो_phy_reg(), update_phy_reg(), and
 * पढ़ो_paged_phy_reg() require the caller to hold ohci->phy_reg_mutex.
 * In other words, only use ohci_पढ़ो_phy_reg() and ohci_update_phy_reg()
 * directly.  Exceptions are पूर्णांकrinsically serialized contexts like pci_probe.
 */
अटल पूर्णांक पढ़ो_phy_reg(काष्ठा fw_ohci *ohci, पूर्णांक addr)
अणु
	u32 val;
	पूर्णांक i;

	reg_ग_लिखो(ohci, OHCI1394_PhyControl, OHCI1394_PhyControl_Read(addr));
	क्रम (i = 0; i < 3 + 100; i++) अणु
		val = reg_पढ़ो(ohci, OHCI1394_PhyControl);
		अगर (!~val)
			वापस -ENODEV; /* Card was ejected. */

		अगर (val & OHCI1394_PhyControl_ReadDone)
			वापस OHCI1394_PhyControl_ReadData(val);

		/*
		 * Try a few बार without रुकोing.  Sleeping is necessary
		 * only when the link/PHY पूर्णांकerface is busy.
		 */
		अगर (i >= 3)
			msleep(1);
	पूर्ण
	ohci_err(ohci, "failed to read phy reg %d\n", addr);
	dump_stack();

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक ग_लिखो_phy_reg(स्थिर काष्ठा fw_ohci *ohci, पूर्णांक addr, u32 val)
अणु
	पूर्णांक i;

	reg_ग_लिखो(ohci, OHCI1394_PhyControl,
		  OHCI1394_PhyControl_Write(addr, val));
	क्रम (i = 0; i < 3 + 100; i++) अणु
		val = reg_पढ़ो(ohci, OHCI1394_PhyControl);
		अगर (!~val)
			वापस -ENODEV; /* Card was ejected. */

		अगर (!(val & OHCI1394_PhyControl_WritePending))
			वापस 0;

		अगर (i >= 3)
			msleep(1);
	पूर्ण
	ohci_err(ohci, "failed to write phy reg %d, val %u\n", addr, val);
	dump_stack();

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक update_phy_reg(काष्ठा fw_ohci *ohci, पूर्णांक addr,
			  पूर्णांक clear_bits, पूर्णांक set_bits)
अणु
	पूर्णांक ret = पढ़ो_phy_reg(ohci, addr);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The पूर्णांकerrupt status bits are cleared by writing a one bit.
	 * Aव्योम clearing them unless explicitly requested in set_bits.
	 */
	अगर (addr == 5)
		clear_bits |= PHY_INT_STATUS_BITS;

	वापस ग_लिखो_phy_reg(ohci, addr, (ret & ~clear_bits) | set_bits);
पूर्ण

अटल पूर्णांक पढ़ो_paged_phy_reg(काष्ठा fw_ohci *ohci, पूर्णांक page, पूर्णांक addr)
अणु
	पूर्णांक ret;

	ret = update_phy_reg(ohci, 7, PHY_PAGE_SELECT, page << 5);
	अगर (ret < 0)
		वापस ret;

	वापस पढ़ो_phy_reg(ohci, addr);
पूर्ण

अटल पूर्णांक ohci_पढ़ो_phy_reg(काष्ठा fw_card *card, पूर्णांक addr)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);
	पूर्णांक ret;

	mutex_lock(&ohci->phy_reg_mutex);
	ret = पढ़ो_phy_reg(ohci, addr);
	mutex_unlock(&ohci->phy_reg_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ohci_update_phy_reg(काष्ठा fw_card *card, पूर्णांक addr,
			       पूर्णांक clear_bits, पूर्णांक set_bits)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);
	पूर्णांक ret;

	mutex_lock(&ohci->phy_reg_mutex);
	ret = update_phy_reg(ohci, addr, clear_bits, set_bits);
	mutex_unlock(&ohci->phy_reg_mutex);

	वापस ret;
पूर्ण

अटल अंतरभूत dma_addr_t ar_buffer_bus(काष्ठा ar_context *ctx, अचिन्हित पूर्णांक i)
अणु
	वापस page_निजी(ctx->pages[i]);
पूर्ण

अटल व्योम ar_context_link_page(काष्ठा ar_context *ctx, अचिन्हित पूर्णांक index)
अणु
	काष्ठा descriptor *d;

	d = &ctx->descriptors[index];
	d->branch_address  &= cpu_to_le32(~0xf);
	d->res_count       =  cpu_to_le16(PAGE_SIZE);
	d->transfer_status =  0;

	wmb(); /* finish init of new descriptors beक्रमe branch_address update */
	d = &ctx->descriptors[ctx->last_buffer_index];
	d->branch_address  |= cpu_to_le32(1);

	ctx->last_buffer_index = index;

	reg_ग_लिखो(ctx->ohci, CONTROL_SET(ctx->regs), CONTEXT_WAKE);
पूर्ण

अटल व्योम ar_context_release(काष्ठा ar_context *ctx)
अणु
	काष्ठा device *dev = ctx->ohci->card.device;
	अचिन्हित पूर्णांक i;

	vunmap(ctx->buffer);

	क्रम (i = 0; i < AR_BUFFERS; i++) अणु
		अगर (ctx->pages[i])
			dma_मुक्त_pages(dev, PAGE_SIZE, ctx->pages[i],
				       ar_buffer_bus(ctx, i), DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

अटल व्योम ar_context_पात(काष्ठा ar_context *ctx, स्थिर अक्षर *error_msg)
अणु
	काष्ठा fw_ohci *ohci = ctx->ohci;

	अगर (reg_पढ़ो(ohci, CONTROL_CLEAR(ctx->regs)) & CONTEXT_RUN) अणु
		reg_ग_लिखो(ohci, CONTROL_CLEAR(ctx->regs), CONTEXT_RUN);
		flush_ग_लिखोs(ohci);

		ohci_err(ohci, "AR error: %s; DMA stopped\n", error_msg);
	पूर्ण
	/* FIXME: restart? */
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ar_next_buffer_index(अचिन्हित पूर्णांक index)
अणु
	वापस (index + 1) % AR_BUFFERS;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ar_first_buffer_index(काष्ठा ar_context *ctx)
अणु
	वापस ar_next_buffer_index(ctx->last_buffer_index);
पूर्ण

/*
 * We search क्रम the buffer that contains the last AR packet DMA data written
 * by the controller.
 */
अटल अचिन्हित पूर्णांक ar_search_last_active_buffer(काष्ठा ar_context *ctx,
						 अचिन्हित पूर्णांक *buffer_offset)
अणु
	अचिन्हित पूर्णांक i, next_i, last = ctx->last_buffer_index;
	__le16 res_count, next_res_count;

	i = ar_first_buffer_index(ctx);
	res_count = READ_ONCE(ctx->descriptors[i].res_count);

	/* A buffer that is not yet completely filled must be the last one. */
	जबतक (i != last && res_count == 0) अणु

		/* Peek at the next descriptor. */
		next_i = ar_next_buffer_index(i);
		rmb(); /* पढ़ो descriptors in order */
		next_res_count = READ_ONCE(ctx->descriptors[next_i].res_count);
		/*
		 * If the next descriptor is still empty, we must stop at this
		 * descriptor.
		 */
		अगर (next_res_count == cpu_to_le16(PAGE_SIZE)) अणु
			/*
			 * The exception is when the DMA data क्रम one packet is
			 * split over three buffers; in this हाल, the middle
			 * buffer's descriptor might be never updated by the
			 * controller and look still empty, and we have to peek
			 * at the third one.
			 */
			अगर (MAX_AR_PACKET_SIZE > PAGE_SIZE && i != last) अणु
				next_i = ar_next_buffer_index(next_i);
				rmb();
				next_res_count = READ_ONCE(ctx->descriptors[next_i].res_count);
				अगर (next_res_count != cpu_to_le16(PAGE_SIZE))
					जाओ next_buffer_is_active;
			पूर्ण

			अवरोध;
		पूर्ण

next_buffer_is_active:
		i = next_i;
		res_count = next_res_count;
	पूर्ण

	rmb(); /* पढ़ो res_count beक्रमe the DMA data */

	*buffer_offset = PAGE_SIZE - le16_to_cpu(res_count);
	अगर (*buffer_offset > PAGE_SIZE) अणु
		*buffer_offset = 0;
		ar_context_पात(ctx, "corrupted descriptor");
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम ar_sync_buffers_क्रम_cpu(काष्ठा ar_context *ctx,
				    अचिन्हित पूर्णांक end_buffer_index,
				    अचिन्हित पूर्णांक end_buffer_offset)
अणु
	अचिन्हित पूर्णांक i;

	i = ar_first_buffer_index(ctx);
	जबतक (i != end_buffer_index) अणु
		dma_sync_single_क्रम_cpu(ctx->ohci->card.device,
					ar_buffer_bus(ctx, i),
					PAGE_SIZE, DMA_FROM_DEVICE);
		i = ar_next_buffer_index(i);
	पूर्ण
	अगर (end_buffer_offset > 0)
		dma_sync_single_क्रम_cpu(ctx->ohci->card.device,
					ar_buffer_bus(ctx, i),
					end_buffer_offset, DMA_FROM_DEVICE);
पूर्ण

#अगर defined(CONFIG_PPC_PMAC) && defined(CONFIG_PPC32)
#घोषणा cond_le32_to_cpu(v) \
	(ohci->quirks & QUIRK_BE_HEADERS ? (__क्रमce __u32)(v) : le32_to_cpu(v))
#अन्यथा
#घोषणा cond_le32_to_cpu(v) le32_to_cpu(v)
#पूर्ण_अगर

अटल __le32 *handle_ar_packet(काष्ठा ar_context *ctx, __le32 *buffer)
अणु
	काष्ठा fw_ohci *ohci = ctx->ohci;
	काष्ठा fw_packet p;
	u32 status, length, tcode;
	पूर्णांक evt;

	p.header[0] = cond_le32_to_cpu(buffer[0]);
	p.header[1] = cond_le32_to_cpu(buffer[1]);
	p.header[2] = cond_le32_to_cpu(buffer[2]);

	tcode = (p.header[0] >> 4) & 0x0f;
	चयन (tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
	हाल TCODE_READ_QUADLET_RESPONSE:
		p.header[3] = (__क्रमce __u32) buffer[3];
		p.header_length = 16;
		p.payload_length = 0;
		अवरोध;

	हाल TCODE_READ_BLOCK_REQUEST :
		p.header[3] = cond_le32_to_cpu(buffer[3]);
		p.header_length = 16;
		p.payload_length = 0;
		अवरोध;

	हाल TCODE_WRITE_BLOCK_REQUEST:
	हाल TCODE_READ_BLOCK_RESPONSE:
	हाल TCODE_LOCK_REQUEST:
	हाल TCODE_LOCK_RESPONSE:
		p.header[3] = cond_le32_to_cpu(buffer[3]);
		p.header_length = 16;
		p.payload_length = p.header[3] >> 16;
		अगर (p.payload_length > MAX_ASYNC_PAYLOAD) अणु
			ar_context_पात(ctx, "invalid packet length");
			वापस शून्य;
		पूर्ण
		अवरोध;

	हाल TCODE_WRITE_RESPONSE:
	हाल TCODE_READ_QUADLET_REQUEST:
	हाल OHCI_TCODE_PHY_PACKET:
		p.header_length = 12;
		p.payload_length = 0;
		अवरोध;

	शेष:
		ar_context_पात(ctx, "invalid tcode");
		वापस शून्य;
	पूर्ण

	p.payload = (व्योम *) buffer + p.header_length;

	/* FIXME: What to करो about evt_* errors? */
	length = (p.header_length + p.payload_length + 3) / 4;
	status = cond_le32_to_cpu(buffer[length]);
	evt    = (status >> 16) & 0x1f;

	p.ack        = evt - 16;
	p.speed      = (status >> 21) & 0x7;
	p.बारtamp  = status & 0xffff;
	p.generation = ohci->request_generation;

	log_ar_at_event(ohci, 'R', p.speed, p.header, evt);

	/*
	 * Several controllers, notably from NEC and VIA, क्रमget to
	 * ग_लिखो ack_complete status at PHY packet reception.
	 */
	अगर (evt == OHCI1394_evt_no_status &&
	    (p.header[0] & 0xff) == (OHCI1394_phy_tcode << 4))
		p.ack = ACK_COMPLETE;

	/*
	 * The OHCI bus reset handler synthesizes a PHY packet with
	 * the new generation number when a bus reset happens (see
	 * section 8.4.2.3).  This helps us determine when a request
	 * was received and make sure we send the response in the same
	 * generation.  We only need this क्रम requests; क्रम responses
	 * we use the unique tlabel क्रम finding the matching
	 * request.
	 *
	 * Alas some chips someबार emit bus reset packets with a
	 * wrong generation.  We set the correct generation क्रम these
	 * at a slightly incorrect समय (in bus_reset_work).
	 */
	अगर (evt == OHCI1394_evt_bus_reset) अणु
		अगर (!(ohci->quirks & QUIRK_RESET_PACKET))
			ohci->request_generation = (p.header[2] >> 16) & 0xff;
	पूर्ण अन्यथा अगर (ctx == &ohci->ar_request_ctx) अणु
		fw_core_handle_request(&ohci->card, &p);
	पूर्ण अन्यथा अणु
		fw_core_handle_response(&ohci->card, &p);
	पूर्ण

	वापस buffer + length + 1;
पूर्ण

अटल व्योम *handle_ar_packets(काष्ठा ar_context *ctx, व्योम *p, व्योम *end)
अणु
	व्योम *next;

	जबतक (p < end) अणु
		next = handle_ar_packet(ctx, p);
		अगर (!next)
			वापस p;
		p = next;
	पूर्ण

	वापस p;
पूर्ण

अटल व्योम ar_recycle_buffers(काष्ठा ar_context *ctx, अचिन्हित पूर्णांक end_buffer)
अणु
	अचिन्हित पूर्णांक i;

	i = ar_first_buffer_index(ctx);
	जबतक (i != end_buffer) अणु
		dma_sync_single_क्रम_device(ctx->ohci->card.device,
					   ar_buffer_bus(ctx, i),
					   PAGE_SIZE, DMA_FROM_DEVICE);
		ar_context_link_page(ctx, i);
		i = ar_next_buffer_index(i);
	पूर्ण
पूर्ण

अटल व्योम ar_context_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा ar_context *ctx = (काष्ठा ar_context *)data;
	अचिन्हित पूर्णांक end_buffer_index, end_buffer_offset;
	व्योम *p, *end;

	p = ctx->poपूर्णांकer;
	अगर (!p)
		वापस;

	end_buffer_index = ar_search_last_active_buffer(ctx,
							&end_buffer_offset);
	ar_sync_buffers_क्रम_cpu(ctx, end_buffer_index, end_buffer_offset);
	end = ctx->buffer + end_buffer_index * PAGE_SIZE + end_buffer_offset;

	अगर (end_buffer_index < ar_first_buffer_index(ctx)) अणु
		/*
		 * The filled part of the overall buffer wraps around; handle
		 * all packets up to the buffer end here.  If the last packet
		 * wraps around, its tail will be visible after the buffer end
		 * because the buffer start pages are mapped there again.
		 */
		व्योम *buffer_end = ctx->buffer + AR_BUFFERS * PAGE_SIZE;
		p = handle_ar_packets(ctx, p, buffer_end);
		अगर (p < buffer_end)
			जाओ error;
		/* adjust p to poपूर्णांक back पूर्णांकo the actual buffer */
		p -= AR_BUFFERS * PAGE_SIZE;
	पूर्ण

	p = handle_ar_packets(ctx, p, end);
	अगर (p != end) अणु
		अगर (p > end)
			ar_context_पात(ctx, "inconsistent descriptor");
		जाओ error;
	पूर्ण

	ctx->poपूर्णांकer = p;
	ar_recycle_buffers(ctx, end_buffer_index);

	वापस;

error:
	ctx->poपूर्णांकer = शून्य;
पूर्ण

अटल पूर्णांक ar_context_init(काष्ठा ar_context *ctx, काष्ठा fw_ohci *ohci,
			   अचिन्हित पूर्णांक descriptors_offset, u32 regs)
अणु
	काष्ठा device *dev = ohci->card.device;
	अचिन्हित पूर्णांक i;
	dma_addr_t dma_addr;
	काष्ठा page *pages[AR_BUFFERS + AR_WRAPAROUND_PAGES];
	काष्ठा descriptor *d;

	ctx->regs        = regs;
	ctx->ohci        = ohci;
	tasklet_init(&ctx->tasklet, ar_context_tasklet, (अचिन्हित दीर्घ)ctx);

	क्रम (i = 0; i < AR_BUFFERS; i++) अणु
		ctx->pages[i] = dma_alloc_pages(dev, PAGE_SIZE, &dma_addr,
						DMA_FROM_DEVICE, GFP_KERNEL);
		अगर (!ctx->pages[i])
			जाओ out_of_memory;
		set_page_निजी(ctx->pages[i], dma_addr);
		dma_sync_single_क्रम_device(dev, dma_addr, PAGE_SIZE,
					   DMA_FROM_DEVICE);
	पूर्ण

	क्रम (i = 0; i < AR_BUFFERS; i++)
		pages[i]              = ctx->pages[i];
	क्रम (i = 0; i < AR_WRAPAROUND_PAGES; i++)
		pages[AR_BUFFERS + i] = ctx->pages[i];
	ctx->buffer = vmap(pages, ARRAY_SIZE(pages), VM_MAP, PAGE_KERNEL);
	अगर (!ctx->buffer)
		जाओ out_of_memory;

	ctx->descriptors     = ohci->misc_buffer     + descriptors_offset;
	ctx->descriptors_bus = ohci->misc_buffer_bus + descriptors_offset;

	क्रम (i = 0; i < AR_BUFFERS; i++) अणु
		d = &ctx->descriptors[i];
		d->req_count      = cpu_to_le16(PAGE_SIZE);
		d->control        = cpu_to_le16(DESCRIPTOR_INPUT_MORE |
						DESCRIPTOR_STATUS |
						DESCRIPTOR_BRANCH_ALWAYS);
		d->data_address   = cpu_to_le32(ar_buffer_bus(ctx, i));
		d->branch_address = cpu_to_le32(ctx->descriptors_bus +
			ar_next_buffer_index(i) * माप(काष्ठा descriptor));
	पूर्ण

	वापस 0;

out_of_memory:
	ar_context_release(ctx);

	वापस -ENOMEM;
पूर्ण

अटल व्योम ar_context_run(काष्ठा ar_context *ctx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < AR_BUFFERS; i++)
		ar_context_link_page(ctx, i);

	ctx->poपूर्णांकer = ctx->buffer;

	reg_ग_लिखो(ctx->ohci, COMMAND_PTR(ctx->regs), ctx->descriptors_bus | 1);
	reg_ग_लिखो(ctx->ohci, CONTROL_SET(ctx->regs), CONTEXT_RUN);
पूर्ण

अटल काष्ठा descriptor *find_branch_descriptor(काष्ठा descriptor *d, पूर्णांक z)
अणु
	__le16 branch;

	branch = d->control & cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS);

	/* figure out which descriptor the branch address goes in */
	अगर (z == 2 && branch == cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS))
		वापस d;
	अन्यथा
		वापस d + z - 1;
पूर्ण

अटल व्योम context_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा context *ctx = (काष्ठा context *) data;
	काष्ठा descriptor *d, *last;
	u32 address;
	पूर्णांक z;
	काष्ठा descriptor_buffer *desc;

	desc = list_entry(ctx->buffer_list.next,
			काष्ठा descriptor_buffer, list);
	last = ctx->last;
	जबतक (last->branch_address != 0) अणु
		काष्ठा descriptor_buffer *old_desc = desc;
		address = le32_to_cpu(last->branch_address);
		z = address & 0xf;
		address &= ~0xf;
		ctx->current_bus = address;

		/* If the branch address poपूर्णांकs to a buffer outside of the
		 * current buffer, advance to the next buffer. */
		अगर (address < desc->buffer_bus ||
				address >= desc->buffer_bus + desc->used)
			desc = list_entry(desc->list.next,
					काष्ठा descriptor_buffer, list);
		d = desc->buffer + (address - desc->buffer_bus) / माप(*d);
		last = find_branch_descriptor(d, z);

		अगर (!ctx->callback(ctx, d, last))
			अवरोध;

		अगर (old_desc != desc) अणु
			/* If we've advanced to the next buffer, move the
			 * previous buffer to the मुक्त list. */
			अचिन्हित दीर्घ flags;
			old_desc->used = 0;
			spin_lock_irqsave(&ctx->ohci->lock, flags);
			list_move_tail(&old_desc->list, &ctx->buffer_list);
			spin_unlock_irqrestore(&ctx->ohci->lock, flags);
		पूर्ण
		ctx->last = last;
	पूर्ण
पूर्ण

/*
 * Allocate a new buffer and add it to the list of मुक्त buffers क्रम this
 * context.  Must be called with ohci->lock held.
 */
अटल पूर्णांक context_add_buffer(काष्ठा context *ctx)
अणु
	काष्ठा descriptor_buffer *desc;
	dma_addr_t bus_addr;
	पूर्णांक offset;

	/*
	 * 16MB of descriptors should be far more than enough क्रम any DMA
	 * program.  This will catch run-away userspace or DoS attacks.
	 */
	अगर (ctx->total_allocation >= 16*1024*1024)
		वापस -ENOMEM;

	desc = dma_alloc_coherent(ctx->ohci->card.device, PAGE_SIZE,
			&bus_addr, GFP_ATOMIC);
	अगर (!desc)
		वापस -ENOMEM;

	offset = (व्योम *)&desc->buffer - (व्योम *)desc;
	/*
	 * Some controllers, like JMicron ones, always issue 0x20-byte DMA पढ़ोs
	 * क्रम descriptors, even 0x10-byte ones. This can cause page faults when
	 * an IOMMU is in use and the oversized पढ़ो crosses a page boundary.
	 * Work around this by always leaving at least 0x10 bytes of padding.
	 */
	desc->buffer_size = PAGE_SIZE - offset - 0x10;
	desc->buffer_bus = bus_addr + offset;
	desc->used = 0;

	list_add_tail(&desc->list, &ctx->buffer_list);
	ctx->total_allocation += PAGE_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक context_init(काष्ठा context *ctx, काष्ठा fw_ohci *ohci,
			u32 regs, descriptor_callback_t callback)
अणु
	ctx->ohci = ohci;
	ctx->regs = regs;
	ctx->total_allocation = 0;

	INIT_LIST_HEAD(&ctx->buffer_list);
	अगर (context_add_buffer(ctx) < 0)
		वापस -ENOMEM;

	ctx->buffer_tail = list_entry(ctx->buffer_list.next,
			काष्ठा descriptor_buffer, list);

	tasklet_init(&ctx->tasklet, context_tasklet, (अचिन्हित दीर्घ)ctx);
	ctx->callback = callback;

	/*
	 * We put a dummy descriptor in the buffer that has a शून्य
	 * branch address and looks like it's been sent.  That way we
	 * have a descriptor to append DMA programs to.
	 */
	स_रखो(ctx->buffer_tail->buffer, 0, माप(*ctx->buffer_tail->buffer));
	ctx->buffer_tail->buffer->control = cpu_to_le16(DESCRIPTOR_OUTPUT_LAST);
	ctx->buffer_tail->buffer->transfer_status = cpu_to_le16(0x8011);
	ctx->buffer_tail->used += माप(*ctx->buffer_tail->buffer);
	ctx->last = ctx->buffer_tail->buffer;
	ctx->prev = ctx->buffer_tail->buffer;
	ctx->prev_z = 1;

	वापस 0;
पूर्ण

अटल व्योम context_release(काष्ठा context *ctx)
अणु
	काष्ठा fw_card *card = &ctx->ohci->card;
	काष्ठा descriptor_buffer *desc, *पंचांगp;

	list_क्रम_each_entry_safe(desc, पंचांगp, &ctx->buffer_list, list)
		dma_मुक्त_coherent(card->device, PAGE_SIZE, desc,
			desc->buffer_bus -
			((व्योम *)&desc->buffer - (व्योम *)desc));
पूर्ण

/* Must be called with ohci->lock held */
अटल काष्ठा descriptor *context_get_descriptors(काष्ठा context *ctx,
						  पूर्णांक z, dma_addr_t *d_bus)
अणु
	काष्ठा descriptor *d = शून्य;
	काष्ठा descriptor_buffer *desc = ctx->buffer_tail;

	अगर (z * माप(*d) > desc->buffer_size)
		वापस शून्य;

	अगर (z * माप(*d) > desc->buffer_size - desc->used) अणु
		/* No room क्रम the descriptor in this buffer, so advance to the
		 * next one. */

		अगर (desc->list.next == &ctx->buffer_list) अणु
			/* If there is no मुक्त buffer next in the list,
			 * allocate one. */
			अगर (context_add_buffer(ctx) < 0)
				वापस शून्य;
		पूर्ण
		desc = list_entry(desc->list.next,
				काष्ठा descriptor_buffer, list);
		ctx->buffer_tail = desc;
	पूर्ण

	d = desc->buffer + desc->used / माप(*d);
	स_रखो(d, 0, z * माप(*d));
	*d_bus = desc->buffer_bus + desc->used;

	वापस d;
पूर्ण

अटल व्योम context_run(काष्ठा context *ctx, u32 extra)
अणु
	काष्ठा fw_ohci *ohci = ctx->ohci;

	reg_ग_लिखो(ohci, COMMAND_PTR(ctx->regs),
		  le32_to_cpu(ctx->last->branch_address));
	reg_ग_लिखो(ohci, CONTROL_CLEAR(ctx->regs), ~0);
	reg_ग_लिखो(ohci, CONTROL_SET(ctx->regs), CONTEXT_RUN | extra);
	ctx->running = true;
	flush_ग_लिखोs(ohci);
पूर्ण

अटल व्योम context_append(काष्ठा context *ctx,
			   काष्ठा descriptor *d, पूर्णांक z, पूर्णांक extra)
अणु
	dma_addr_t d_bus;
	काष्ठा descriptor_buffer *desc = ctx->buffer_tail;
	काष्ठा descriptor *d_branch;

	d_bus = desc->buffer_bus + (d - desc->buffer) * माप(*d);

	desc->used += (z + extra) * माप(*d);

	wmb(); /* finish init of new descriptors beक्रमe branch_address update */

	d_branch = find_branch_descriptor(ctx->prev, ctx->prev_z);
	d_branch->branch_address = cpu_to_le32(d_bus | z);

	/*
	 * VT6306 incorrectly checks only the single descriptor at the
	 * CommandPtr when the wake bit is written, so अगर it's a
	 * multi-descriptor block starting with an INPUT_MORE, put a copy of
	 * the branch address in the first descriptor.
	 *
	 * Not करोing this क्रम transmit contexts since not sure how it पूर्णांकeracts
	 * with skip addresses.
	 */
	अगर (unlikely(ctx->ohci->quirks & QUIRK_IR_WAKE) &&
	    d_branch != ctx->prev &&
	    (ctx->prev->control & cpu_to_le16(DESCRIPTOR_CMD)) ==
	     cpu_to_le16(DESCRIPTOR_INPUT_MORE)) अणु
		ctx->prev->branch_address = cpu_to_le32(d_bus | z);
	पूर्ण

	ctx->prev = d;
	ctx->prev_z = z;
पूर्ण

अटल व्योम context_stop(काष्ठा context *ctx)
अणु
	काष्ठा fw_ohci *ohci = ctx->ohci;
	u32 reg;
	पूर्णांक i;

	reg_ग_लिखो(ohci, CONTROL_CLEAR(ctx->regs), CONTEXT_RUN);
	ctx->running = false;

	क्रम (i = 0; i < 1000; i++) अणु
		reg = reg_पढ़ो(ohci, CONTROL_SET(ctx->regs));
		अगर ((reg & CONTEXT_ACTIVE) == 0)
			वापस;

		अगर (i)
			udelay(10);
	पूर्ण
	ohci_err(ohci, "DMA context still active (0x%08x)\n", reg);
पूर्ण

काष्ठा driver_data अणु
	u8 अंतरभूत_data[8];
	काष्ठा fw_packet *packet;
पूर्ण;

/*
 * This function apppends a packet to the DMA queue क्रम transmission.
 * Must always be called with the ochi->lock held to ensure proper
 * generation handling and locking around packet queue manipulation.
 */
अटल पूर्णांक at_context_queue_packet(काष्ठा context *ctx,
				   काष्ठा fw_packet *packet)
अणु
	काष्ठा fw_ohci *ohci = ctx->ohci;
	dma_addr_t d_bus, payload_bus;
	काष्ठा driver_data *driver_data;
	काष्ठा descriptor *d, *last;
	__le32 *header;
	पूर्णांक z, tcode;

	d = context_get_descriptors(ctx, 4, &d_bus);
	अगर (d == शून्य) अणु
		packet->ack = RCODE_SEND_ERROR;
		वापस -1;
	पूर्ण

	d[0].control   = cpu_to_le16(DESCRIPTOR_KEY_IMMEDIATE);
	d[0].res_count = cpu_to_le16(packet->बारtamp);

	/*
	 * The DMA क्रमmat क्रम asynchronous link packets is dअगरferent
	 * from the IEEE1394 layout, so shअगरt the fields around
	 * accordingly.
	 */

	tcode = (packet->header[0] >> 4) & 0x0f;
	header = (__le32 *) &d[1];
	चयन (tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
	हाल TCODE_WRITE_BLOCK_REQUEST:
	हाल TCODE_WRITE_RESPONSE:
	हाल TCODE_READ_QUADLET_REQUEST:
	हाल TCODE_READ_BLOCK_REQUEST:
	हाल TCODE_READ_QUADLET_RESPONSE:
	हाल TCODE_READ_BLOCK_RESPONSE:
	हाल TCODE_LOCK_REQUEST:
	हाल TCODE_LOCK_RESPONSE:
		header[0] = cpu_to_le32((packet->header[0] & 0xffff) |
					(packet->speed << 16));
		header[1] = cpu_to_le32((packet->header[1] & 0xffff) |
					(packet->header[0] & 0xffff0000));
		header[2] = cpu_to_le32(packet->header[2]);

		अगर (TCODE_IS_BLOCK_PACKET(tcode))
			header[3] = cpu_to_le32(packet->header[3]);
		अन्यथा
			header[3] = (__क्रमce __le32) packet->header[3];

		d[0].req_count = cpu_to_le16(packet->header_length);
		अवरोध;

	हाल TCODE_LINK_INTERNAL:
		header[0] = cpu_to_le32((OHCI1394_phy_tcode << 4) |
					(packet->speed << 16));
		header[1] = cpu_to_le32(packet->header[1]);
		header[2] = cpu_to_le32(packet->header[2]);
		d[0].req_count = cpu_to_le16(12);

		अगर (is_ping_packet(&packet->header[1]))
			d[0].control |= cpu_to_le16(DESCRIPTOR_PING);
		अवरोध;

	हाल TCODE_STREAM_DATA:
		header[0] = cpu_to_le32((packet->header[0] & 0xffff) |
					(packet->speed << 16));
		header[1] = cpu_to_le32(packet->header[0] & 0xffff0000);
		d[0].req_count = cpu_to_le16(8);
		अवरोध;

	शेष:
		/* BUG(); */
		packet->ack = RCODE_SEND_ERROR;
		वापस -1;
	पूर्ण

	BUILD_BUG_ON(माप(काष्ठा driver_data) > माप(काष्ठा descriptor));
	driver_data = (काष्ठा driver_data *) &d[3];
	driver_data->packet = packet;
	packet->driver_data = driver_data;

	अगर (packet->payload_length > 0) अणु
		अगर (packet->payload_length > माप(driver_data->अंतरभूत_data)) अणु
			payload_bus = dma_map_single(ohci->card.device,
						     packet->payload,
						     packet->payload_length,
						     DMA_TO_DEVICE);
			अगर (dma_mapping_error(ohci->card.device, payload_bus)) अणु
				packet->ack = RCODE_SEND_ERROR;
				वापस -1;
			पूर्ण
			packet->payload_bus	= payload_bus;
			packet->payload_mapped	= true;
		पूर्ण अन्यथा अणु
			स_नकल(driver_data->अंतरभूत_data, packet->payload,
			       packet->payload_length);
			payload_bus = d_bus + 3 * माप(*d);
		पूर्ण

		d[2].req_count    = cpu_to_le16(packet->payload_length);
		d[2].data_address = cpu_to_le32(payload_bus);
		last = &d[2];
		z = 3;
	पूर्ण अन्यथा अणु
		last = &d[0];
		z = 2;
	पूर्ण

	last->control |= cpu_to_le16(DESCRIPTOR_OUTPUT_LAST |
				     DESCRIPTOR_IRQ_ALWAYS |
				     DESCRIPTOR_BRANCH_ALWAYS);

	/* FIXME: Document how the locking works. */
	अगर (ohci->generation != packet->generation) अणु
		अगर (packet->payload_mapped)
			dma_unmap_single(ohci->card.device, payload_bus,
					 packet->payload_length, DMA_TO_DEVICE);
		packet->ack = RCODE_GENERATION;
		वापस -1;
	पूर्ण

	context_append(ctx, d, z, 4 - z);

	अगर (ctx->running)
		reg_ग_लिखो(ohci, CONTROL_SET(ctx->regs), CONTEXT_WAKE);
	अन्यथा
		context_run(ctx, 0);

	वापस 0;
पूर्ण

अटल व्योम at_context_flush(काष्ठा context *ctx)
अणु
	tasklet_disable(&ctx->tasklet);

	ctx->flushing = true;
	context_tasklet((अचिन्हित दीर्घ)ctx);
	ctx->flushing = false;

	tasklet_enable(&ctx->tasklet);
पूर्ण

अटल पूर्णांक handle_at_packet(काष्ठा context *context,
			    काष्ठा descriptor *d,
			    काष्ठा descriptor *last)
अणु
	काष्ठा driver_data *driver_data;
	काष्ठा fw_packet *packet;
	काष्ठा fw_ohci *ohci = context->ohci;
	पूर्णांक evt;

	अगर (last->transfer_status == 0 && !context->flushing)
		/* This descriptor isn't करोne yet, stop iteration. */
		वापस 0;

	driver_data = (काष्ठा driver_data *) &d[3];
	packet = driver_data->packet;
	अगर (packet == शून्य)
		/* This packet was cancelled, just जारी. */
		वापस 1;

	अगर (packet->payload_mapped)
		dma_unmap_single(ohci->card.device, packet->payload_bus,
				 packet->payload_length, DMA_TO_DEVICE);

	evt = le16_to_cpu(last->transfer_status) & 0x1f;
	packet->बारtamp = le16_to_cpu(last->res_count);

	log_ar_at_event(ohci, 'T', packet->speed, packet->header, evt);

	चयन (evt) अणु
	हाल OHCI1394_evt_समयout:
		/* Async response transmit समयd out. */
		packet->ack = RCODE_CANCELLED;
		अवरोध;

	हाल OHCI1394_evt_flushed:
		/*
		 * The packet was flushed should give same error as
		 * when we try to use a stale generation count.
		 */
		packet->ack = RCODE_GENERATION;
		अवरोध;

	हाल OHCI1394_evt_missing_ack:
		अगर (context->flushing)
			packet->ack = RCODE_GENERATION;
		अन्यथा अणु
			/*
			 * Using a valid (current) generation count, but the
			 * node is not on the bus or not sending acks.
			 */
			packet->ack = RCODE_NO_ACK;
		पूर्ण
		अवरोध;

	हाल ACK_COMPLETE + 0x10:
	हाल ACK_PENDING + 0x10:
	हाल ACK_BUSY_X + 0x10:
	हाल ACK_BUSY_A + 0x10:
	हाल ACK_BUSY_B + 0x10:
	हाल ACK_DATA_ERROR + 0x10:
	हाल ACK_TYPE_ERROR + 0x10:
		packet->ack = evt - 0x10;
		अवरोध;

	हाल OHCI1394_evt_no_status:
		अगर (context->flushing) अणु
			packet->ack = RCODE_GENERATION;
			अवरोध;
		पूर्ण
		fallthrough;

	शेष:
		packet->ack = RCODE_SEND_ERROR;
		अवरोध;
	पूर्ण

	packet->callback(packet, &ohci->card, packet->ack);

	वापस 1;
पूर्ण

#घोषणा HEADER_GET_DESTINATION(q)	(((q) >> 16) & 0xffff)
#घोषणा HEADER_GET_TCODE(q)		(((q) >> 4) & 0x0f)
#घोषणा HEADER_GET_OFFSET_HIGH(q)	(((q) >> 0) & 0xffff)
#घोषणा HEADER_GET_DATA_LENGTH(q)	(((q) >> 16) & 0xffff)
#घोषणा HEADER_GET_EXTENDED_TCODE(q)	(((q) >> 0) & 0xffff)

अटल व्योम handle_local_rom(काष्ठा fw_ohci *ohci,
			     काष्ठा fw_packet *packet, u32 csr)
अणु
	काष्ठा fw_packet response;
	पूर्णांक tcode, length, i;

	tcode = HEADER_GET_TCODE(packet->header[0]);
	अगर (TCODE_IS_BLOCK_PACKET(tcode))
		length = HEADER_GET_DATA_LENGTH(packet->header[3]);
	अन्यथा
		length = 4;

	i = csr - CSR_CONFIG_ROM;
	अगर (i + length > CONFIG_ROM_SIZE) अणु
		fw_fill_response(&response, packet->header,
				 RCODE_ADDRESS_ERROR, शून्य, 0);
	पूर्ण अन्यथा अगर (!TCODE_IS_READ_REQUEST(tcode)) अणु
		fw_fill_response(&response, packet->header,
				 RCODE_TYPE_ERROR, शून्य, 0);
	पूर्ण अन्यथा अणु
		fw_fill_response(&response, packet->header, RCODE_COMPLETE,
				 (व्योम *) ohci->config_rom + i, length);
	पूर्ण

	fw_core_handle_response(&ohci->card, &response);
पूर्ण

अटल व्योम handle_local_lock(काष्ठा fw_ohci *ohci,
			      काष्ठा fw_packet *packet, u32 csr)
अणु
	काष्ठा fw_packet response;
	पूर्णांक tcode, length, ext_tcode, sel, try;
	__be32 *payload, lock_old;
	u32 lock_arg, lock_data;

	tcode = HEADER_GET_TCODE(packet->header[0]);
	length = HEADER_GET_DATA_LENGTH(packet->header[3]);
	payload = packet->payload;
	ext_tcode = HEADER_GET_EXTENDED_TCODE(packet->header[3]);

	अगर (tcode == TCODE_LOCK_REQUEST &&
	    ext_tcode == EXTCODE_COMPARE_SWAP && length == 8) अणु
		lock_arg = be32_to_cpu(payload[0]);
		lock_data = be32_to_cpu(payload[1]);
	पूर्ण अन्यथा अगर (tcode == TCODE_READ_QUADLET_REQUEST) अणु
		lock_arg = 0;
		lock_data = 0;
	पूर्ण अन्यथा अणु
		fw_fill_response(&response, packet->header,
				 RCODE_TYPE_ERROR, शून्य, 0);
		जाओ out;
	पूर्ण

	sel = (csr - CSR_BUS_MANAGER_ID) / 4;
	reg_ग_लिखो(ohci, OHCI1394_CSRData, lock_data);
	reg_ग_लिखो(ohci, OHCI1394_CSRCompareData, lock_arg);
	reg_ग_लिखो(ohci, OHCI1394_CSRControl, sel);

	क्रम (try = 0; try < 20; try++)
		अगर (reg_पढ़ो(ohci, OHCI1394_CSRControl) & 0x80000000) अणु
			lock_old = cpu_to_be32(reg_पढ़ो(ohci,
							OHCI1394_CSRData));
			fw_fill_response(&response, packet->header,
					 RCODE_COMPLETE,
					 &lock_old, माप(lock_old));
			जाओ out;
		पूर्ण

	ohci_err(ohci, "swap not done (CSR lock timeout)\n");
	fw_fill_response(&response, packet->header, RCODE_BUSY, शून्य, 0);

 out:
	fw_core_handle_response(&ohci->card, &response);
पूर्ण

अटल व्योम handle_local_request(काष्ठा context *ctx, काष्ठा fw_packet *packet)
अणु
	u64 offset, csr;

	अगर (ctx == &ctx->ohci->at_request_ctx) अणु
		packet->ack = ACK_PENDING;
		packet->callback(packet, &ctx->ohci->card, packet->ack);
	पूर्ण

	offset =
		((अचिन्हित दीर्घ दीर्घ)
		 HEADER_GET_OFFSET_HIGH(packet->header[1]) << 32) |
		packet->header[2];
	csr = offset - CSR_REGISTER_BASE;

	/* Handle config rom पढ़ोs. */
	अगर (csr >= CSR_CONFIG_ROM && csr < CSR_CONFIG_ROM_END)
		handle_local_rom(ctx->ohci, packet, csr);
	अन्यथा चयन (csr) अणु
	हाल CSR_BUS_MANAGER_ID:
	हाल CSR_BANDWIDTH_AVAILABLE:
	हाल CSR_CHANNELS_AVAILABLE_HI:
	हाल CSR_CHANNELS_AVAILABLE_LO:
		handle_local_lock(ctx->ohci, packet, csr);
		अवरोध;
	शेष:
		अगर (ctx == &ctx->ohci->at_request_ctx)
			fw_core_handle_request(&ctx->ohci->card, packet);
		अन्यथा
			fw_core_handle_response(&ctx->ohci->card, packet);
		अवरोध;
	पूर्ण

	अगर (ctx == &ctx->ohci->at_response_ctx) अणु
		packet->ack = ACK_COMPLETE;
		packet->callback(packet, &ctx->ohci->card, packet->ack);
	पूर्ण
पूर्ण

अटल व्योम at_context_transmit(काष्ठा context *ctx, काष्ठा fw_packet *packet)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ctx->ohci->lock, flags);

	अगर (HEADER_GET_DESTINATION(packet->header[0]) == ctx->ohci->node_id &&
	    ctx->ohci->generation == packet->generation) अणु
		spin_unlock_irqrestore(&ctx->ohci->lock, flags);
		handle_local_request(ctx, packet);
		वापस;
	पूर्ण

	ret = at_context_queue_packet(ctx, packet);
	spin_unlock_irqrestore(&ctx->ohci->lock, flags);

	अगर (ret < 0)
		packet->callback(packet, &ctx->ohci->card, packet->ack);

पूर्ण

अटल व्योम detect_dead_context(काष्ठा fw_ohci *ohci,
				स्थिर अक्षर *name, अचिन्हित पूर्णांक regs)
अणु
	u32 ctl;

	ctl = reg_पढ़ो(ohci, CONTROL_SET(regs));
	अगर (ctl & CONTEXT_DEAD)
		ohci_err(ohci, "DMA context %s has stopped, error code: %s\n",
			name, evts[ctl & 0x1f]);
पूर्ण

अटल व्योम handle_dead_contexts(काष्ठा fw_ohci *ohci)
अणु
	अचिन्हित पूर्णांक i;
	अक्षर name[8];

	detect_dead_context(ohci, "ATReq", OHCI1394_AsReqTrContextBase);
	detect_dead_context(ohci, "ATRsp", OHCI1394_AsRspTrContextBase);
	detect_dead_context(ohci, "ARReq", OHCI1394_AsReqRcvContextBase);
	detect_dead_context(ohci, "ARRsp", OHCI1394_AsRspRcvContextBase);
	क्रम (i = 0; i < 32; ++i) अणु
		अगर (!(ohci->it_context_support & (1 << i)))
			जारी;
		प्र_लिखो(name, "IT%u", i);
		detect_dead_context(ohci, name, OHCI1394_IsoXmitContextBase(i));
	पूर्ण
	क्रम (i = 0; i < 32; ++i) अणु
		अगर (!(ohci->ir_context_support & (1 << i)))
			जारी;
		प्र_लिखो(name, "IR%u", i);
		detect_dead_context(ohci, name, OHCI1394_IsoRcvContextBase(i));
	पूर्ण
	/* TODO: maybe try to flush and restart the dead contexts */
पूर्ण

अटल u32 cycle_समयr_ticks(u32 cycle_समयr)
अणु
	u32 ticks;

	ticks = cycle_समयr & 0xfff;
	ticks += 3072 * ((cycle_समयr >> 12) & 0x1fff);
	ticks += (3072 * 8000) * (cycle_समयr >> 25);

	वापस ticks;
पूर्ण

/*
 * Some controllers exhibit one or more of the following bugs when updating the
 * iso cycle समयr रेजिस्टर:
 *  - When the lowest six bits are wrapping around to zero, a पढ़ो that happens
 *    at the same समय will वापस garbage in the lowest ten bits.
 *  - When the cycleOffset field wraps around to zero, the cycleCount field is
 *    not incremented क्रम about 60 ns.
 *  - Occasionally, the entire रेजिस्टर पढ़ोs zero.
 *
 * To catch these, we पढ़ो the रेजिस्टर three बार and ensure that the
 * dअगरference between each two consecutive पढ़ोs is approximately the same, i.e.
 * less than twice the other.  Furthermore, any negative dअगरference indicates an
 * error.  (A PCI पढ़ो should take at least 20 ticks of the 24.576 MHz समयr to
 * execute, so we have enough precision to compute the ratio of the dअगरferences.)
 */
अटल u32 get_cycle_समय(काष्ठा fw_ohci *ohci)
अणु
	u32 c0, c1, c2;
	u32 t0, t1, t2;
	s32 dअगरf01, dअगरf12;
	पूर्णांक i;

	c2 = reg_पढ़ो(ohci, OHCI1394_IsochronousCycleTimer);

	अगर (ohci->quirks & QUIRK_CYCLE_TIMER) अणु
		i = 0;
		c1 = c2;
		c2 = reg_पढ़ो(ohci, OHCI1394_IsochronousCycleTimer);
		करो अणु
			c0 = c1;
			c1 = c2;
			c2 = reg_पढ़ो(ohci, OHCI1394_IsochronousCycleTimer);
			t0 = cycle_समयr_ticks(c0);
			t1 = cycle_समयr_ticks(c1);
			t2 = cycle_समयr_ticks(c2);
			dअगरf01 = t1 - t0;
			dअगरf12 = t2 - t1;
		पूर्ण जबतक ((dअगरf01 <= 0 || dअगरf12 <= 0 ||
			  dअगरf01 / dअगरf12 >= 2 || dअगरf12 / dअगरf01 >= 2)
			 && i++ < 20);
	पूर्ण

	वापस c2;
पूर्ण

/*
 * This function has to be called at least every 64 seconds.  The bus_समय
 * field stores not only the upper 25 bits of the BUS_TIME रेजिस्टर but also
 * the most signअगरicant bit of the cycle समयr in bit 6 so that we can detect
 * changes in this bit.
 */
अटल u32 update_bus_समय(काष्ठा fw_ohci *ohci)
अणु
	u32 cycle_समय_seconds = get_cycle_समय(ohci) >> 25;

	अगर (unlikely(!ohci->bus_समय_running)) अणु
		reg_ग_लिखो(ohci, OHCI1394_IntMaskSet, OHCI1394_cycle64Seconds);
		ohci->bus_समय = (lower_32_bits(kसमय_get_seconds()) & ~0x7f) |
		                 (cycle_समय_seconds & 0x40);
		ohci->bus_समय_running = true;
	पूर्ण

	अगर ((ohci->bus_समय & 0x40) != (cycle_समय_seconds & 0x40))
		ohci->bus_समय += 0x40;

	वापस ohci->bus_समय | cycle_समय_seconds;
पूर्ण

अटल पूर्णांक get_status_क्रम_port(काष्ठा fw_ohci *ohci, पूर्णांक port_index)
अणु
	पूर्णांक reg;

	mutex_lock(&ohci->phy_reg_mutex);
	reg = ग_लिखो_phy_reg(ohci, 7, port_index);
	अगर (reg >= 0)
		reg = पढ़ो_phy_reg(ohci, 8);
	mutex_unlock(&ohci->phy_reg_mutex);
	अगर (reg < 0)
		वापस reg;

	चयन (reg & 0x0f) अणु
	हाल 0x06:
		वापस 2;	/* is child node (connected to parent node) */
	हाल 0x0e:
		वापस 3;	/* is parent node (connected to child node) */
	पूर्ण
	वापस 1;		/* not connected */
पूर्ण

अटल पूर्णांक get_self_id_pos(काष्ठा fw_ohci *ohci, u32 self_id,
	पूर्णांक self_id_count)
अणु
	पूर्णांक i;
	u32 entry;

	क्रम (i = 0; i < self_id_count; i++) अणु
		entry = ohci->self_id_buffer[i];
		अगर ((self_id & 0xff000000) == (entry & 0xff000000))
			वापस -1;
		अगर ((self_id & 0xff000000) < (entry & 0xff000000))
			वापस i;
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक initiated_reset(काष्ठा fw_ohci *ohci)
अणु
	पूर्णांक reg;
	पूर्णांक ret = 0;

	mutex_lock(&ohci->phy_reg_mutex);
	reg = ग_लिखो_phy_reg(ohci, 7, 0xe0); /* Select page 7 */
	अगर (reg >= 0) अणु
		reg = पढ़ो_phy_reg(ohci, 8);
		reg |= 0x40;
		reg = ग_लिखो_phy_reg(ohci, 8, reg); /* set PMODE bit */
		अगर (reg >= 0) अणु
			reg = पढ़ो_phy_reg(ohci, 12); /* पढ़ो रेजिस्टर 12 */
			अगर (reg >= 0) अणु
				अगर ((reg & 0x08) == 0x08) अणु
					/* bit 3 indicates "initiated reset" */
					ret = 0x2;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&ohci->phy_reg_mutex);
	वापस ret;
पूर्ण

/*
 * TI TSB82AA2B and TSB12LV26 करो not receive the selfID of a locally
 * attached TSB41BA3D phy; see http://www.ti.com/litv/pdf/sllz059.
 * Conकाष्ठा the selfID from phy रेजिस्टर contents.
 */
अटल पूर्णांक find_and_insert_self_id(काष्ठा fw_ohci *ohci, पूर्णांक self_id_count)
अणु
	पूर्णांक reg, i, pos, status;
	/* link active 1, speed 3, bridge 0, contender 1, more packets 0 */
	u32 self_id = 0x8040c800;

	reg = reg_पढ़ो(ohci, OHCI1394_NodeID);
	अगर (!(reg & OHCI1394_NodeID_idValid)) अणु
		ohci_notice(ohci,
			    "node ID not valid, new bus reset in progress\n");
		वापस -EBUSY;
	पूर्ण
	self_id |= ((reg & 0x3f) << 24); /* phy ID */

	reg = ohci_पढ़ो_phy_reg(&ohci->card, 4);
	अगर (reg < 0)
		वापस reg;
	self_id |= ((reg & 0x07) << 8); /* घातer class */

	reg = ohci_पढ़ो_phy_reg(&ohci->card, 1);
	अगर (reg < 0)
		वापस reg;
	self_id |= ((reg & 0x3f) << 16); /* gap count */

	क्रम (i = 0; i < 3; i++) अणु
		status = get_status_क्रम_port(ohci, i);
		अगर (status < 0)
			वापस status;
		self_id |= ((status & 0x3) << (6 - (i * 2)));
	पूर्ण

	self_id |= initiated_reset(ohci);

	pos = get_self_id_pos(ohci, self_id, self_id_count);
	अगर (pos >= 0) अणु
		स_हटाओ(&(ohci->self_id_buffer[pos+1]),
			&(ohci->self_id_buffer[pos]),
			(self_id_count - pos) * माप(*ohci->self_id_buffer));
		ohci->self_id_buffer[pos] = self_id;
		self_id_count++;
	पूर्ण
	वापस self_id_count;
पूर्ण

अटल व्योम bus_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_ohci *ohci =
		container_of(work, काष्ठा fw_ohci, bus_reset_work);
	पूर्णांक self_id_count, generation, new_generation, i, j;
	u32 reg;
	व्योम *मुक्त_rom = शून्य;
	dma_addr_t मुक्त_rom_bus = 0;
	bool is_new_root;

	reg = reg_पढ़ो(ohci, OHCI1394_NodeID);
	अगर (!(reg & OHCI1394_NodeID_idValid)) अणु
		ohci_notice(ohci,
			    "node ID not valid, new bus reset in progress\n");
		वापस;
	पूर्ण
	अगर ((reg & OHCI1394_NodeID_nodeNumber) == 63) अणु
		ohci_notice(ohci, "malconfigured bus\n");
		वापस;
	पूर्ण
	ohci->node_id = reg & (OHCI1394_NodeID_busNumber |
			       OHCI1394_NodeID_nodeNumber);

	is_new_root = (reg & OHCI1394_NodeID_root) != 0;
	अगर (!(ohci->is_root && is_new_root))
		reg_ग_लिखो(ohci, OHCI1394_LinkControlSet,
			  OHCI1394_LinkControl_cycleMaster);
	ohci->is_root = is_new_root;

	reg = reg_पढ़ो(ohci, OHCI1394_SelfIDCount);
	अगर (reg & OHCI1394_SelfIDCount_selfIDError) अणु
		ohci_notice(ohci, "self ID receive error\n");
		वापस;
	पूर्ण
	/*
	 * The count in the SelfIDCount रेजिस्टर is the number of
	 * bytes in the self ID receive buffer.  Since we also receive
	 * the inverted quadlets and a header quadlet, we shअगरt one
	 * bit extra to get the actual number of self IDs.
	 */
	self_id_count = (reg >> 3) & 0xff;

	अगर (self_id_count > 252) अणु
		ohci_notice(ohci, "bad selfIDSize (%08x)\n", reg);
		वापस;
	पूर्ण

	generation = (cond_le32_to_cpu(ohci->self_id[0]) >> 16) & 0xff;
	rmb();

	क्रम (i = 1, j = 0; j < self_id_count; i += 2, j++) अणु
		u32 id  = cond_le32_to_cpu(ohci->self_id[i]);
		u32 id2 = cond_le32_to_cpu(ohci->self_id[i + 1]);

		अगर (id != ~id2) अणु
			/*
			 * If the invalid data looks like a cycle start packet,
			 * it's likely to be the result of the cycle master
			 * having a wrong gap count.  In this हाल, the self IDs
			 * so far are valid and should be processed so that the
			 * bus manager can then correct the gap count.
			 */
			अगर (id == 0xffff008f) अणु
				ohci_notice(ohci, "ignoring spurious self IDs\n");
				self_id_count = j;
				अवरोध;
			पूर्ण

			ohci_notice(ohci, "bad self ID %d/%d (%08x != ~%08x)\n",
				    j, self_id_count, id, id2);
			वापस;
		पूर्ण
		ohci->self_id_buffer[j] = id;
	पूर्ण

	अगर (ohci->quirks & QUIRK_TI_SLLZ059) अणु
		self_id_count = find_and_insert_self_id(ohci, self_id_count);
		अगर (self_id_count < 0) अणु
			ohci_notice(ohci,
				    "could not construct local self ID\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (self_id_count == 0) अणु
		ohci_notice(ohci, "no self IDs\n");
		वापस;
	पूर्ण
	rmb();

	/*
	 * Check the consistency of the self IDs we just पढ़ो.  The
	 * problem we face is that a new bus reset can start जबतक we
	 * पढ़ो out the self IDs from the DMA buffer. If this happens,
	 * the DMA buffer will be overwritten with new self IDs and we
	 * will पढ़ो out inconsistent data.  The OHCI specअगरication
	 * (section 11.2) recommends a technique similar to
	 * linux/seqlock.h, where we remember the generation of the
	 * self IDs in the buffer beक्रमe पढ़ोing them out and compare
	 * it to the current generation after पढ़ोing them out.  If
	 * the two generations match we know we have a consistent set
	 * of self IDs.
	 */

	new_generation = (reg_पढ़ो(ohci, OHCI1394_SelfIDCount) >> 16) & 0xff;
	अगर (new_generation != generation) अणु
		ohci_notice(ohci, "new bus reset, discarding self ids\n");
		वापस;
	पूर्ण

	/* FIXME: Document how the locking works. */
	spin_lock_irq(&ohci->lock);

	ohci->generation = -1; /* prevent AT packet queueing */
	context_stop(&ohci->at_request_ctx);
	context_stop(&ohci->at_response_ctx);

	spin_unlock_irq(&ohci->lock);

	/*
	 * Per OHCI 1.2 draft, clause 7.2.3.3, hardware may leave unsent
	 * packets in the AT queues and software needs to drain them.
	 * Some OHCI 1.1 controllers (JMicron) apparently require this too.
	 */
	at_context_flush(&ohci->at_request_ctx);
	at_context_flush(&ohci->at_response_ctx);

	spin_lock_irq(&ohci->lock);

	ohci->generation = generation;
	reg_ग_लिखो(ohci, OHCI1394_IntEventClear, OHCI1394_busReset);

	अगर (ohci->quirks & QUIRK_RESET_PACKET)
		ohci->request_generation = generation;

	/*
	 * This next bit is unrelated to the AT context stuff but we
	 * have to करो it under the spinlock also.  If a new config rom
	 * was set up beक्रमe this reset, the old one is now no दीर्घer
	 * in use and we can मुक्त it. Update the config rom poपूर्णांकers
	 * to poपूर्णांक to the current config rom and clear the
	 * next_config_rom poपूर्णांकer so a new update can take place.
	 */

	अगर (ohci->next_config_rom != शून्य) अणु
		अगर (ohci->next_config_rom != ohci->config_rom) अणु
			मुक्त_rom      = ohci->config_rom;
			मुक्त_rom_bus  = ohci->config_rom_bus;
		पूर्ण
		ohci->config_rom      = ohci->next_config_rom;
		ohci->config_rom_bus  = ohci->next_config_rom_bus;
		ohci->next_config_rom = शून्य;

		/*
		 * Restore config_rom image and manually update
		 * config_rom रेजिस्टरs.  Writing the header quadlet
		 * will indicate that the config rom is पढ़ोy, so we
		 * करो that last.
		 */
		reg_ग_लिखो(ohci, OHCI1394_BusOptions,
			  be32_to_cpu(ohci->config_rom[2]));
		ohci->config_rom[0] = ohci->next_header;
		reg_ग_लिखो(ohci, OHCI1394_ConfigROMhdr,
			  be32_to_cpu(ohci->next_header));
	पूर्ण

	अगर (param_remote_dma) अणु
		reg_ग_लिखो(ohci, OHCI1394_PhyReqFilterHiSet, ~0);
		reg_ग_लिखो(ohci, OHCI1394_PhyReqFilterLoSet, ~0);
	पूर्ण

	spin_unlock_irq(&ohci->lock);

	अगर (मुक्त_rom)
		dma_मुक्त_coherent(ohci->card.device, CONFIG_ROM_SIZE,
				  मुक्त_rom, मुक्त_rom_bus);

	log_selfids(ohci, generation, self_id_count);

	fw_core_handle_bus_reset(&ohci->card, ohci->node_id, generation,
				 self_id_count, ohci->self_id_buffer,
				 ohci->csr_state_setclear_abdicate);
	ohci->csr_state_setclear_abdicate = false;
पूर्ण

अटल irqवापस_t irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fw_ohci *ohci = data;
	u32 event, iso_event;
	पूर्णांक i;

	event = reg_पढ़ो(ohci, OHCI1394_IntEventClear);

	अगर (!event || !~event)
		वापस IRQ_NONE;

	/*
	 * busReset and postedWriteErr must not be cleared yet
	 * (OHCI 1.1 clauses 7.2.3.2 and 13.2.8.1)
	 */
	reg_ग_लिखो(ohci, OHCI1394_IntEventClear,
		  event & ~(OHCI1394_busReset | OHCI1394_postedWriteErr));
	log_irqs(ohci, event);

	अगर (event & OHCI1394_selfIDComplete)
		queue_work(selfid_workqueue, &ohci->bus_reset_work);

	अगर (event & OHCI1394_RQPkt)
		tasklet_schedule(&ohci->ar_request_ctx.tasklet);

	अगर (event & OHCI1394_RSPkt)
		tasklet_schedule(&ohci->ar_response_ctx.tasklet);

	अगर (event & OHCI1394_reqTxComplete)
		tasklet_schedule(&ohci->at_request_ctx.tasklet);

	अगर (event & OHCI1394_respTxComplete)
		tasklet_schedule(&ohci->at_response_ctx.tasklet);

	अगर (event & OHCI1394_isochRx) अणु
		iso_event = reg_पढ़ो(ohci, OHCI1394_IsoRecvIntEventClear);
		reg_ग_लिखो(ohci, OHCI1394_IsoRecvIntEventClear, iso_event);

		जबतक (iso_event) अणु
			i = ffs(iso_event) - 1;
			tasklet_schedule(
				&ohci->ir_context_list[i].context.tasklet);
			iso_event &= ~(1 << i);
		पूर्ण
	पूर्ण

	अगर (event & OHCI1394_isochTx) अणु
		iso_event = reg_पढ़ो(ohci, OHCI1394_IsoXmitIntEventClear);
		reg_ग_लिखो(ohci, OHCI1394_IsoXmitIntEventClear, iso_event);

		जबतक (iso_event) अणु
			i = ffs(iso_event) - 1;
			tasklet_schedule(
				&ohci->it_context_list[i].context.tasklet);
			iso_event &= ~(1 << i);
		पूर्ण
	पूर्ण

	अगर (unlikely(event & OHCI1394_regAccessFail))
		ohci_err(ohci, "register access failure\n");

	अगर (unlikely(event & OHCI1394_postedWriteErr)) अणु
		reg_पढ़ो(ohci, OHCI1394_PostedWriteAddressHi);
		reg_पढ़ो(ohci, OHCI1394_PostedWriteAddressLo);
		reg_ग_लिखो(ohci, OHCI1394_IntEventClear,
			  OHCI1394_postedWriteErr);
		अगर (prपूर्णांकk_ratelimit())
			ohci_err(ohci, "PCI posted write error\n");
	पूर्ण

	अगर (unlikely(event & OHCI1394_cycleTooLong)) अणु
		अगर (prपूर्णांकk_ratelimit())
			ohci_notice(ohci, "isochronous cycle too long\n");
		reg_ग_लिखो(ohci, OHCI1394_LinkControlSet,
			  OHCI1394_LinkControl_cycleMaster);
	पूर्ण

	अगर (unlikely(event & OHCI1394_cycleInconsistent)) अणु
		/*
		 * We need to clear this event bit in order to make
		 * cycleMatch isochronous I/O work.  In theory we should
		 * stop active cycleMatch iso contexts now and restart
		 * them at least two cycles later.  (FIXME?)
		 */
		अगर (prपूर्णांकk_ratelimit())
			ohci_notice(ohci, "isochronous cycle inconsistent\n");
	पूर्ण

	अगर (unlikely(event & OHCI1394_unrecoverableError))
		handle_dead_contexts(ohci);

	अगर (event & OHCI1394_cycle64Seconds) अणु
		spin_lock(&ohci->lock);
		update_bus_समय(ohci);
		spin_unlock(&ohci->lock);
	पूर्ण अन्यथा
		flush_ग_लिखोs(ohci);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक software_reset(काष्ठा fw_ohci *ohci)
अणु
	u32 val;
	पूर्णांक i;

	reg_ग_लिखो(ohci, OHCI1394_HCControlSet, OHCI1394_HCControl_softReset);
	क्रम (i = 0; i < 500; i++) अणु
		val = reg_पढ़ो(ohci, OHCI1394_HCControlSet);
		अगर (!~val)
			वापस -ENODEV; /* Card was ejected. */

		अगर (!(val & OHCI1394_HCControl_softReset))
			वापस 0;

		msleep(1);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल व्योम copy_config_rom(__be32 *dest, स्थिर __be32 *src, माप_प्रकार length)
अणु
	माप_प्रकार size = length * 4;

	स_नकल(dest, src, size);
	अगर (size < CONFIG_ROM_SIZE)
		स_रखो(&dest[length], 0, CONFIG_ROM_SIZE - size);
पूर्ण

अटल पूर्णांक configure_1394a_enhancements(काष्ठा fw_ohci *ohci)
अणु
	bool enable_1394a;
	पूर्णांक ret, clear, set, offset;

	/* Check अगर the driver should configure link and PHY. */
	अगर (!(reg_पढ़ो(ohci, OHCI1394_HCControlSet) &
	      OHCI1394_HCControl_programPhyEnable))
		वापस 0;

	/* Paranoia: check whether the PHY supports 1394a, too. */
	enable_1394a = false;
	ret = पढ़ो_phy_reg(ohci, 2);
	अगर (ret < 0)
		वापस ret;
	अगर ((ret & PHY_EXTENDED_REGISTERS) == PHY_EXTENDED_REGISTERS) अणु
		ret = पढ़ो_paged_phy_reg(ohci, 1, 8);
		अगर (ret < 0)
			वापस ret;
		अगर (ret >= 1)
			enable_1394a = true;
	पूर्ण

	अगर (ohci->quirks & QUIRK_NO_1394A)
		enable_1394a = false;

	/* Configure PHY and link consistently. */
	अगर (enable_1394a) अणु
		clear = 0;
		set = PHY_ENABLE_ACCEL | PHY_ENABLE_MULTI;
	पूर्ण अन्यथा अणु
		clear = PHY_ENABLE_ACCEL | PHY_ENABLE_MULTI;
		set = 0;
	पूर्ण
	ret = update_phy_reg(ohci, 5, clear, set);
	अगर (ret < 0)
		वापस ret;

	अगर (enable_1394a)
		offset = OHCI1394_HCControlSet;
	अन्यथा
		offset = OHCI1394_HCControlClear;
	reg_ग_लिखो(ohci, offset, OHCI1394_HCControl_aPhyEnhanceEnable);

	/* Clean up: configuration has been taken care of. */
	reg_ग_लिखो(ohci, OHCI1394_HCControlClear,
		  OHCI1394_HCControl_programPhyEnable);

	वापस 0;
पूर्ण

अटल पूर्णांक probe_tsb41ba3d(काष्ठा fw_ohci *ohci)
अणु
	/* TI venकरोr ID = 0x080028, TSB41BA3D product ID = 0x833005 (sic) */
	अटल स्थिर u8 id[] = अणु 0x08, 0x00, 0x28, 0x83, 0x30, 0x05, पूर्ण;
	पूर्णांक reg, i;

	reg = पढ़ो_phy_reg(ohci, 2);
	अगर (reg < 0)
		वापस reg;
	अगर ((reg & PHY_EXTENDED_REGISTERS) != PHY_EXTENDED_REGISTERS)
		वापस 0;

	क्रम (i = ARRAY_SIZE(id) - 1; i >= 0; i--) अणु
		reg = पढ़ो_paged_phy_reg(ohci, 1, i + 10);
		अगर (reg < 0)
			वापस reg;
		अगर (reg != id[i])
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक ohci_enable(काष्ठा fw_card *card,
		       स्थिर __be32 *config_rom, माप_प्रकार length)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);
	u32 lps, version, irqs;
	पूर्णांक i, ret;

	ret = software_reset(ohci);
	अगर (ret < 0) अणु
		ohci_err(ohci, "failed to reset ohci card\n");
		वापस ret;
	पूर्ण

	/*
	 * Now enable LPS, which we need in order to start accessing
	 * most of the रेजिस्टरs.  In fact, on some cards (ALI M5251),
	 * accessing रेजिस्टरs in the SClk करोमुख्य without LPS enabled
	 * will lock up the machine.  Wait 50msec to make sure we have
	 * full link enabled.  However, with some cards (well, at least
	 * a JMicron PCIe card), we have to try again someबार.
	 *
	 * TI TSB82AA2 + TSB81BA3(A) cards संकेत LPS enabled early but
	 * cannot actually use the phy at that समय.  These need tens of
	 * millisecods छोड़ो between LPS ग_लिखो and first phy access too.
	 */

	reg_ग_लिखो(ohci, OHCI1394_HCControlSet,
		  OHCI1394_HCControl_LPS |
		  OHCI1394_HCControl_postedWriteEnable);
	flush_ग_लिखोs(ohci);

	क्रम (lps = 0, i = 0; !lps && i < 3; i++) अणु
		msleep(50);
		lps = reg_पढ़ो(ohci, OHCI1394_HCControlSet) &
		      OHCI1394_HCControl_LPS;
	पूर्ण

	अगर (!lps) अणु
		ohci_err(ohci, "failed to set Link Power Status\n");
		वापस -EIO;
	पूर्ण

	अगर (ohci->quirks & QUIRK_TI_SLLZ059) अणु
		ret = probe_tsb41ba3d(ohci);
		अगर (ret < 0)
			वापस ret;
		अगर (ret)
			ohci_notice(ohci, "local TSB41BA3D phy\n");
		अन्यथा
			ohci->quirks &= ~QUIRK_TI_SLLZ059;
	पूर्ण

	reg_ग_लिखो(ohci, OHCI1394_HCControlClear,
		  OHCI1394_HCControl_noByteSwapData);

	reg_ग_लिखो(ohci, OHCI1394_SelfIDBuffer, ohci->self_id_bus);
	reg_ग_लिखो(ohci, OHCI1394_LinkControlSet,
		  OHCI1394_LinkControl_cycleTimerEnable |
		  OHCI1394_LinkControl_cycleMaster);

	reg_ग_लिखो(ohci, OHCI1394_ATRetries,
		  OHCI1394_MAX_AT_REQ_RETRIES |
		  (OHCI1394_MAX_AT_RESP_RETRIES << 4) |
		  (OHCI1394_MAX_PHYS_RESP_RETRIES << 8) |
		  (200 << 16));

	ohci->bus_समय_running = false;

	क्रम (i = 0; i < 32; i++)
		अगर (ohci->ir_context_support & (1 << i))
			reg_ग_लिखो(ohci, OHCI1394_IsoRcvContextControlClear(i),
				  IR_CONTEXT_MULTI_CHANNEL_MODE);

	version = reg_पढ़ो(ohci, OHCI1394_Version) & 0x00ff00ff;
	अगर (version >= OHCI_VERSION_1_1) अणु
		reg_ग_लिखो(ohci, OHCI1394_InitialChannelsAvailableHi,
			  0xfffffffe);
		card->broadcast_channel_स्वतः_allocated = true;
	पूर्ण

	/* Get implemented bits of the priority arbitration request counter. */
	reg_ग_लिखो(ohci, OHCI1394_FairnessControl, 0x3f);
	ohci->pri_req_max = reg_पढ़ो(ohci, OHCI1394_FairnessControl) & 0x3f;
	reg_ग_लिखो(ohci, OHCI1394_FairnessControl, 0);
	card->priority_budget_implemented = ohci->pri_req_max != 0;

	reg_ग_लिखो(ohci, OHCI1394_PhyUpperBound, FW_MAX_PHYSICAL_RANGE >> 16);
	reg_ग_लिखो(ohci, OHCI1394_IntEventClear, ~0);
	reg_ग_लिखो(ohci, OHCI1394_IntMaskClear, ~0);

	ret = configure_1394a_enhancements(ohci);
	अगर (ret < 0)
		वापस ret;

	/* Activate link_on bit and contender bit in our self ID packets.*/
	ret = ohci_update_phy_reg(card, 4, 0, PHY_LINK_ACTIVE | PHY_CONTENDER);
	अगर (ret < 0)
		वापस ret;

	/*
	 * When the link is not yet enabled, the atomic config rom
	 * update mechanism described below in ohci_set_config_rom()
	 * is not active.  We have to update ConfigRomHeader and
	 * BusOptions manually, and the ग_लिखो to ConfigROMmap takes
	 * effect immediately.  We tie this to the enabling of the
	 * link, so we have a valid config rom beक्रमe enabling - the
	 * OHCI requires that ConfigROMhdr and BusOptions have valid
	 * values beक्रमe enabling.
	 *
	 * However, when the ConfigROMmap is written, some controllers
	 * always पढ़ो back quadlets 0 and 2 from the config rom to
	 * the ConfigRomHeader and BusOptions रेजिस्टरs on bus reset.
	 * They shouldn't करो that in this initial हाल where the link
	 * isn't enabled.  This means we have to use the same
	 * workaround here, setting the bus header to 0 and then ग_लिखो
	 * the right values in the bus reset tasklet.
	 */

	अगर (config_rom) अणु
		ohci->next_config_rom =
			dma_alloc_coherent(ohci->card.device, CONFIG_ROM_SIZE,
					   &ohci->next_config_rom_bus,
					   GFP_KERNEL);
		अगर (ohci->next_config_rom == शून्य)
			वापस -ENOMEM;

		copy_config_rom(ohci->next_config_rom, config_rom, length);
	पूर्ण अन्यथा अणु
		/*
		 * In the suspend हाल, config_rom is शून्य, which
		 * means that we just reuse the old config rom.
		 */
		ohci->next_config_rom = ohci->config_rom;
		ohci->next_config_rom_bus = ohci->config_rom_bus;
	पूर्ण

	ohci->next_header = ohci->next_config_rom[0];
	ohci->next_config_rom[0] = 0;
	reg_ग_लिखो(ohci, OHCI1394_ConfigROMhdr, 0);
	reg_ग_लिखो(ohci, OHCI1394_BusOptions,
		  be32_to_cpu(ohci->next_config_rom[2]));
	reg_ग_लिखो(ohci, OHCI1394_ConfigROMmap, ohci->next_config_rom_bus);

	reg_ग_लिखो(ohci, OHCI1394_AsReqFilterHiSet, 0x80000000);

	irqs =	OHCI1394_reqTxComplete | OHCI1394_respTxComplete |
		OHCI1394_RQPkt | OHCI1394_RSPkt |
		OHCI1394_isochTx | OHCI1394_isochRx |
		OHCI1394_postedWriteErr |
		OHCI1394_selfIDComplete |
		OHCI1394_regAccessFail |
		OHCI1394_cycleInconsistent |
		OHCI1394_unrecoverableError |
		OHCI1394_cycleTooLong |
		OHCI1394_masterIntEnable;
	अगर (param_debug & OHCI_PARAM_DEBUG_BUSRESETS)
		irqs |= OHCI1394_busReset;
	reg_ग_लिखो(ohci, OHCI1394_IntMaskSet, irqs);

	reg_ग_लिखो(ohci, OHCI1394_HCControlSet,
		  OHCI1394_HCControl_linkEnable |
		  OHCI1394_HCControl_BIBimageValid);

	reg_ग_लिखो(ohci, OHCI1394_LinkControlSet,
		  OHCI1394_LinkControl_rcvSelfID |
		  OHCI1394_LinkControl_rcvPhyPkt);

	ar_context_run(&ohci->ar_request_ctx);
	ar_context_run(&ohci->ar_response_ctx);

	flush_ग_लिखोs(ohci);

	/* We are पढ़ोy to go, reset bus to finish initialization. */
	fw_schedule_bus_reset(&ohci->card, false, true);

	वापस 0;
पूर्ण

अटल पूर्णांक ohci_set_config_rom(काष्ठा fw_card *card,
			       स्थिर __be32 *config_rom, माप_प्रकार length)
अणु
	काष्ठा fw_ohci *ohci;
	__be32 *next_config_rom;
	dma_addr_t next_config_rom_bus;

	ohci = fw_ohci(card);

	/*
	 * When the OHCI controller is enabled, the config rom update
	 * mechanism is a bit tricky, but easy enough to use.  See
	 * section 5.5.6 in the OHCI specअगरication.
	 *
	 * The OHCI controller caches the new config rom address in a
	 * shaकरोw रेजिस्टर (ConfigROMmapNext) and needs a bus reset
	 * क्रम the changes to take place.  When the bus reset is
	 * detected, the controller loads the new values क्रम the
	 * ConfigRomHeader and BusOptions रेजिस्टरs from the specअगरied
	 * config rom and loads ConfigROMmap from the ConfigROMmapNext
	 * shaकरोw रेजिस्टर. All स्वतःmatically and atomically.
	 *
	 * Now, there's a twist to this story.  The स्वतःmatic load of
	 * ConfigRomHeader and BusOptions करोesn't honor the
	 * noByteSwapData bit, so with a be32 config rom, the
	 * controller will load be32 values in to these रेजिस्टरs
	 * during the atomic update, even on litte endian
	 * architectures.  The workaround we use is to put a 0 in the
	 * header quadlet; 0 is endian agnostic and means that the
	 * config rom isn't पढ़ोy yet.  In the bus reset tasklet we
	 * then set up the real values क्रम the two रेजिस्टरs.
	 *
	 * We use ohci->lock to aव्योम racing with the code that sets
	 * ohci->next_config_rom to शून्य (see bus_reset_work).
	 */

	next_config_rom =
		dma_alloc_coherent(ohci->card.device, CONFIG_ROM_SIZE,
				   &next_config_rom_bus, GFP_KERNEL);
	अगर (next_config_rom == शून्य)
		वापस -ENOMEM;

	spin_lock_irq(&ohci->lock);

	/*
	 * If there is not an alपढ़ोy pending config_rom update,
	 * push our new allocation पूर्णांकo the ohci->next_config_rom
	 * and then mark the local variable as null so that we
	 * won't deallocate the new buffer.
	 *
	 * OTOH, अगर there is a pending config_rom update, just
	 * use that buffer with the new config_rom data, and
	 * let this routine मुक्त the unused DMA allocation.
	 */

	अगर (ohci->next_config_rom == शून्य) अणु
		ohci->next_config_rom = next_config_rom;
		ohci->next_config_rom_bus = next_config_rom_bus;
		next_config_rom = शून्य;
	पूर्ण

	copy_config_rom(ohci->next_config_rom, config_rom, length);

	ohci->next_header = config_rom[0];
	ohci->next_config_rom[0] = 0;

	reg_ग_लिखो(ohci, OHCI1394_ConfigROMmap, ohci->next_config_rom_bus);

	spin_unlock_irq(&ohci->lock);

	/* If we didn't use the DMA allocation, delete it. */
	अगर (next_config_rom != शून्य)
		dma_मुक्त_coherent(ohci->card.device, CONFIG_ROM_SIZE,
				  next_config_rom, next_config_rom_bus);

	/*
	 * Now initiate a bus reset to have the changes take
	 * effect. We clean up the old config rom memory and DMA
	 * mappings in the bus reset tasklet, since the OHCI
	 * controller could need to access it beक्रमe the bus reset
	 * takes effect.
	 */

	fw_schedule_bus_reset(&ohci->card, true, true);

	वापस 0;
पूर्ण

अटल व्योम ohci_send_request(काष्ठा fw_card *card, काष्ठा fw_packet *packet)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);

	at_context_transmit(&ohci->at_request_ctx, packet);
पूर्ण

अटल व्योम ohci_send_response(काष्ठा fw_card *card, काष्ठा fw_packet *packet)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);

	at_context_transmit(&ohci->at_response_ctx, packet);
पूर्ण

अटल पूर्णांक ohci_cancel_packet(काष्ठा fw_card *card, काष्ठा fw_packet *packet)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);
	काष्ठा context *ctx = &ohci->at_request_ctx;
	काष्ठा driver_data *driver_data = packet->driver_data;
	पूर्णांक ret = -ENOENT;

	tasklet_disable_in_atomic(&ctx->tasklet);

	अगर (packet->ack != 0)
		जाओ out;

	अगर (packet->payload_mapped)
		dma_unmap_single(ohci->card.device, packet->payload_bus,
				 packet->payload_length, DMA_TO_DEVICE);

	log_ar_at_event(ohci, 'T', packet->speed, packet->header, 0x20);
	driver_data->packet = शून्य;
	packet->ack = RCODE_CANCELLED;
	packet->callback(packet, &ohci->card, packet->ack);
	ret = 0;
 out:
	tasklet_enable(&ctx->tasklet);

	वापस ret;
पूर्ण

अटल पूर्णांक ohci_enable_phys_dma(काष्ठा fw_card *card,
				पूर्णांक node_id, पूर्णांक generation)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);
	अचिन्हित दीर्घ flags;
	पूर्णांक n, ret = 0;

	अगर (param_remote_dma)
		वापस 0;

	/*
	 * FIXME:  Make sure this biपंचांगask is cleared when we clear the busReset
	 * पूर्णांकerrupt bit.  Clear physReqResourceAllBuses on bus reset.
	 */

	spin_lock_irqsave(&ohci->lock, flags);

	अगर (ohci->generation != generation) अणु
		ret = -ESTALE;
		जाओ out;
	पूर्ण

	/*
	 * Note, अगर the node ID contains a non-local bus ID, physical DMA is
	 * enabled क्रम _all_ nodes on remote buses.
	 */

	n = (node_id & 0xffc0) == LOCAL_BUS ? node_id & 0x3f : 63;
	अगर (n < 32)
		reg_ग_लिखो(ohci, OHCI1394_PhyReqFilterLoSet, 1 << n);
	अन्यथा
		reg_ग_लिखो(ohci, OHCI1394_PhyReqFilterHiSet, 1 << (n - 32));

	flush_ग_लिखोs(ohci);
 out:
	spin_unlock_irqrestore(&ohci->lock, flags);

	वापस ret;
पूर्ण

अटल u32 ohci_पढ़ो_csr(काष्ठा fw_card *card, पूर्णांक csr_offset)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);
	अचिन्हित दीर्घ flags;
	u32 value;

	चयन (csr_offset) अणु
	हाल CSR_STATE_CLEAR:
	हाल CSR_STATE_SET:
		अगर (ohci->is_root &&
		    (reg_पढ़ो(ohci, OHCI1394_LinkControlSet) &
		     OHCI1394_LinkControl_cycleMaster))
			value = CSR_STATE_BIT_CMSTR;
		अन्यथा
			value = 0;
		अगर (ohci->csr_state_setclear_abdicate)
			value |= CSR_STATE_BIT_ABDICATE;

		वापस value;

	हाल CSR_NODE_IDS:
		वापस reg_पढ़ो(ohci, OHCI1394_NodeID) << 16;

	हाल CSR_CYCLE_TIME:
		वापस get_cycle_समय(ohci);

	हाल CSR_BUS_TIME:
		/*
		 * We might be called just after the cycle समयr has wrapped
		 * around but just beक्रमe the cycle64Seconds handler, so we
		 * better check here, too, अगर the bus समय needs to be updated.
		 */
		spin_lock_irqsave(&ohci->lock, flags);
		value = update_bus_समय(ohci);
		spin_unlock_irqrestore(&ohci->lock, flags);
		वापस value;

	हाल CSR_BUSY_TIMEOUT:
		value = reg_पढ़ो(ohci, OHCI1394_ATRetries);
		वापस (value >> 4) & 0x0ffff00f;

	हाल CSR_PRIORITY_BUDGET:
		वापस (reg_पढ़ो(ohci, OHCI1394_FairnessControl) & 0x3f) |
			(ohci->pri_req_max << 8);

	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ohci_ग_लिखो_csr(काष्ठा fw_card *card, पूर्णांक csr_offset, u32 value)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);
	अचिन्हित दीर्घ flags;

	चयन (csr_offset) अणु
	हाल CSR_STATE_CLEAR:
		अगर ((value & CSR_STATE_BIT_CMSTR) && ohci->is_root) अणु
			reg_ग_लिखो(ohci, OHCI1394_LinkControlClear,
				  OHCI1394_LinkControl_cycleMaster);
			flush_ग_लिखोs(ohci);
		पूर्ण
		अगर (value & CSR_STATE_BIT_ABDICATE)
			ohci->csr_state_setclear_abdicate = false;
		अवरोध;

	हाल CSR_STATE_SET:
		अगर ((value & CSR_STATE_BIT_CMSTR) && ohci->is_root) अणु
			reg_ग_लिखो(ohci, OHCI1394_LinkControlSet,
				  OHCI1394_LinkControl_cycleMaster);
			flush_ग_लिखोs(ohci);
		पूर्ण
		अगर (value & CSR_STATE_BIT_ABDICATE)
			ohci->csr_state_setclear_abdicate = true;
		अवरोध;

	हाल CSR_NODE_IDS:
		reg_ग_लिखो(ohci, OHCI1394_NodeID, value >> 16);
		flush_ग_लिखोs(ohci);
		अवरोध;

	हाल CSR_CYCLE_TIME:
		reg_ग_लिखो(ohci, OHCI1394_IsochronousCycleTimer, value);
		reg_ग_लिखो(ohci, OHCI1394_IntEventSet,
			  OHCI1394_cycleInconsistent);
		flush_ग_लिखोs(ohci);
		अवरोध;

	हाल CSR_BUS_TIME:
		spin_lock_irqsave(&ohci->lock, flags);
		ohci->bus_समय = (update_bus_समय(ohci) & 0x40) |
		                 (value & ~0x7f);
		spin_unlock_irqrestore(&ohci->lock, flags);
		अवरोध;

	हाल CSR_BUSY_TIMEOUT:
		value = (value & 0xf) | ((value & 0xf) << 4) |
			((value & 0xf) << 8) | ((value & 0x0ffff000) << 4);
		reg_ग_लिखो(ohci, OHCI1394_ATRetries, value);
		flush_ग_लिखोs(ohci);
		अवरोध;

	हाल CSR_PRIORITY_BUDGET:
		reg_ग_लिखो(ohci, OHCI1394_FairnessControl, value & 0x3f);
		flush_ग_लिखोs(ohci);
		अवरोध;

	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम flush_iso_completions(काष्ठा iso_context *ctx)
अणु
	ctx->base.callback.sc(&ctx->base, ctx->last_बारtamp,
			      ctx->header_length, ctx->header,
			      ctx->base.callback_data);
	ctx->header_length = 0;
पूर्ण

अटल व्योम copy_iso_headers(काष्ठा iso_context *ctx, स्थिर u32 *dma_hdr)
अणु
	u32 *ctx_hdr;

	अगर (ctx->header_length + ctx->base.header_size > PAGE_SIZE) अणु
		अगर (ctx->base.drop_overflow_headers)
			वापस;
		flush_iso_completions(ctx);
	पूर्ण

	ctx_hdr = ctx->header + ctx->header_length;
	ctx->last_बारtamp = (u16)le32_to_cpu((__क्रमce __le32)dma_hdr[0]);

	/*
	 * The two iso header quadlets are byteswapped to little
	 * endian by the controller, but we want to present them
	 * as big endian क्रम consistency with the bus endianness.
	 */
	अगर (ctx->base.header_size > 0)
		ctx_hdr[0] = swab32(dma_hdr[1]); /* iso packet header */
	अगर (ctx->base.header_size > 4)
		ctx_hdr[1] = swab32(dma_hdr[0]); /* बारtamp */
	अगर (ctx->base.header_size > 8)
		स_नकल(&ctx_hdr[2], &dma_hdr[2], ctx->base.header_size - 8);
	ctx->header_length += ctx->base.header_size;
पूर्ण

अटल पूर्णांक handle_ir_packet_per_buffer(काष्ठा context *context,
				       काष्ठा descriptor *d,
				       काष्ठा descriptor *last)
अणु
	काष्ठा iso_context *ctx =
		container_of(context, काष्ठा iso_context, context);
	काष्ठा descriptor *pd;
	u32 buffer_dma;

	क्रम (pd = d; pd <= last; pd++)
		अगर (pd->transfer_status)
			अवरोध;
	अगर (pd > last)
		/* Descriptor(s) not करोne yet, stop iteration */
		वापस 0;

	जबतक (!(d->control & cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS))) अणु
		d++;
		buffer_dma = le32_to_cpu(d->data_address);
		dma_sync_single_range_क्रम_cpu(context->ohci->card.device,
					      buffer_dma & PAGE_MASK,
					      buffer_dma & ~PAGE_MASK,
					      le16_to_cpu(d->req_count),
					      DMA_FROM_DEVICE);
	पूर्ण

	copy_iso_headers(ctx, (u32 *) (last + 1));

	अगर (last->control & cpu_to_le16(DESCRIPTOR_IRQ_ALWAYS))
		flush_iso_completions(ctx);

	वापस 1;
पूर्ण

/* d == last because each descriptor block is only a single descriptor. */
अटल पूर्णांक handle_ir_buffer_fill(काष्ठा context *context,
				 काष्ठा descriptor *d,
				 काष्ठा descriptor *last)
अणु
	काष्ठा iso_context *ctx =
		container_of(context, काष्ठा iso_context, context);
	अचिन्हित पूर्णांक req_count, res_count, completed;
	u32 buffer_dma;

	req_count = le16_to_cpu(last->req_count);
	res_count = le16_to_cpu(READ_ONCE(last->res_count));
	completed = req_count - res_count;
	buffer_dma = le32_to_cpu(last->data_address);

	अगर (completed > 0) अणु
		ctx->mc_buffer_bus = buffer_dma;
		ctx->mc_completed = completed;
	पूर्ण

	अगर (res_count != 0)
		/* Descriptor(s) not करोne yet, stop iteration */
		वापस 0;

	dma_sync_single_range_क्रम_cpu(context->ohci->card.device,
				      buffer_dma & PAGE_MASK,
				      buffer_dma & ~PAGE_MASK,
				      completed, DMA_FROM_DEVICE);

	अगर (last->control & cpu_to_le16(DESCRIPTOR_IRQ_ALWAYS)) अणु
		ctx->base.callback.mc(&ctx->base,
				      buffer_dma + completed,
				      ctx->base.callback_data);
		ctx->mc_completed = 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम flush_ir_buffer_fill(काष्ठा iso_context *ctx)
अणु
	dma_sync_single_range_क्रम_cpu(ctx->context.ohci->card.device,
				      ctx->mc_buffer_bus & PAGE_MASK,
				      ctx->mc_buffer_bus & ~PAGE_MASK,
				      ctx->mc_completed, DMA_FROM_DEVICE);

	ctx->base.callback.mc(&ctx->base,
			      ctx->mc_buffer_bus + ctx->mc_completed,
			      ctx->base.callback_data);
	ctx->mc_completed = 0;
पूर्ण

अटल अंतरभूत व्योम sync_it_packet_क्रम_cpu(काष्ठा context *context,
					  काष्ठा descriptor *pd)
अणु
	__le16 control;
	u32 buffer_dma;

	/* only packets beginning with OUTPUT_MORE* have data buffers */
	अगर (pd->control & cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS))
		वापस;

	/* skip over the OUTPUT_MORE_IMMEDIATE descriptor */
	pd += 2;

	/*
	 * If the packet has a header, the first OUTPUT_MORE/LAST descriptor's
	 * data buffer is in the context program's coherent page and must not
	 * be synced.
	 */
	अगर ((le32_to_cpu(pd->data_address) & PAGE_MASK) ==
	    (context->current_bus          & PAGE_MASK)) अणु
		अगर (pd->control & cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS))
			वापस;
		pd++;
	पूर्ण

	करो अणु
		buffer_dma = le32_to_cpu(pd->data_address);
		dma_sync_single_range_क्रम_cpu(context->ohci->card.device,
					      buffer_dma & PAGE_MASK,
					      buffer_dma & ~PAGE_MASK,
					      le16_to_cpu(pd->req_count),
					      DMA_TO_DEVICE);
		control = pd->control;
		pd++;
	पूर्ण जबतक (!(control & cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS)));
पूर्ण

अटल पूर्णांक handle_it_packet(काष्ठा context *context,
			    काष्ठा descriptor *d,
			    काष्ठा descriptor *last)
अणु
	काष्ठा iso_context *ctx =
		container_of(context, काष्ठा iso_context, context);
	काष्ठा descriptor *pd;
	__be32 *ctx_hdr;

	क्रम (pd = d; pd <= last; pd++)
		अगर (pd->transfer_status)
			अवरोध;
	अगर (pd > last)
		/* Descriptor(s) not करोne yet, stop iteration */
		वापस 0;

	sync_it_packet_क्रम_cpu(context, d);

	अगर (ctx->header_length + 4 > PAGE_SIZE) अणु
		अगर (ctx->base.drop_overflow_headers)
			वापस 1;
		flush_iso_completions(ctx);
	पूर्ण

	ctx_hdr = ctx->header + ctx->header_length;
	ctx->last_बारtamp = le16_to_cpu(last->res_count);
	/* Present this value as big-endian to match the receive code */
	*ctx_hdr = cpu_to_be32((le16_to_cpu(pd->transfer_status) << 16) |
			       le16_to_cpu(pd->res_count));
	ctx->header_length += 4;

	अगर (last->control & cpu_to_le16(DESCRIPTOR_IRQ_ALWAYS))
		flush_iso_completions(ctx);

	वापस 1;
पूर्ण

अटल व्योम set_multichannel_mask(काष्ठा fw_ohci *ohci, u64 channels)
अणु
	u32 hi = channels >> 32, lo = channels;

	reg_ग_लिखो(ohci, OHCI1394_IRMultiChanMaskHiClear, ~hi);
	reg_ग_लिखो(ohci, OHCI1394_IRMultiChanMaskLoClear, ~lo);
	reg_ग_लिखो(ohci, OHCI1394_IRMultiChanMaskHiSet, hi);
	reg_ग_लिखो(ohci, OHCI1394_IRMultiChanMaskLoSet, lo);
	ohci->mc_channels = channels;
पूर्ण

अटल काष्ठा fw_iso_context *ohci_allocate_iso_context(काष्ठा fw_card *card,
				पूर्णांक type, पूर्णांक channel, माप_प्रकार header_size)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(card);
	काष्ठा iso_context *ctx;
	descriptor_callback_t callback;
	u64 *channels;
	u32 *mask, regs;
	पूर्णांक index, ret = -EBUSY;

	spin_lock_irq(&ohci->lock);

	चयन (type) अणु
	हाल FW_ISO_CONTEXT_TRANSMIT:
		mask     = &ohci->it_context_mask;
		callback = handle_it_packet;
		index    = ffs(*mask) - 1;
		अगर (index >= 0) अणु
			*mask &= ~(1 << index);
			regs = OHCI1394_IsoXmitContextBase(index);
			ctx  = &ohci->it_context_list[index];
		पूर्ण
		अवरोध;

	हाल FW_ISO_CONTEXT_RECEIVE:
		channels = &ohci->ir_context_channels;
		mask     = &ohci->ir_context_mask;
		callback = handle_ir_packet_per_buffer;
		index    = *channels & 1ULL << channel ? ffs(*mask) - 1 : -1;
		अगर (index >= 0) अणु
			*channels &= ~(1ULL << channel);
			*mask     &= ~(1 << index);
			regs = OHCI1394_IsoRcvContextBase(index);
			ctx  = &ohci->ir_context_list[index];
		पूर्ण
		अवरोध;

	हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:
		mask     = &ohci->ir_context_mask;
		callback = handle_ir_buffer_fill;
		index    = !ohci->mc_allocated ? ffs(*mask) - 1 : -1;
		अगर (index >= 0) अणु
			ohci->mc_allocated = true;
			*mask &= ~(1 << index);
			regs = OHCI1394_IsoRcvContextBase(index);
			ctx  = &ohci->ir_context_list[index];
		पूर्ण
		अवरोध;

	शेष:
		index = -1;
		ret = -ENOSYS;
	पूर्ण

	spin_unlock_irq(&ohci->lock);

	अगर (index < 0)
		वापस ERR_PTR(ret);

	स_रखो(ctx, 0, माप(*ctx));
	ctx->header_length = 0;
	ctx->header = (व्योम *) __get_मुक्त_page(GFP_KERNEL);
	अगर (ctx->header == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ret = context_init(&ctx->context, ohci, regs, callback);
	अगर (ret < 0)
		जाओ out_with_header;

	अगर (type == FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL) अणु
		set_multichannel_mask(ohci, 0);
		ctx->mc_completed = 0;
	पूर्ण

	वापस &ctx->base;

 out_with_header:
	मुक्त_page((अचिन्हित दीर्घ)ctx->header);
 out:
	spin_lock_irq(&ohci->lock);

	चयन (type) अणु
	हाल FW_ISO_CONTEXT_RECEIVE:
		*channels |= 1ULL << channel;
		अवरोध;

	हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:
		ohci->mc_allocated = false;
		अवरोध;
	पूर्ण
	*mask |= 1 << index;

	spin_unlock_irq(&ohci->lock);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक ohci_start_iso(काष्ठा fw_iso_context *base,
			  s32 cycle, u32 sync, u32 tags)
अणु
	काष्ठा iso_context *ctx = container_of(base, काष्ठा iso_context, base);
	काष्ठा fw_ohci *ohci = ctx->context.ohci;
	u32 control = IR_CONTEXT_ISOCH_HEADER, match;
	पूर्णांक index;

	/* the controller cannot start without any queued packets */
	अगर (ctx->context.last->branch_address == 0)
		वापस -ENODATA;

	चयन (ctx->base.type) अणु
	हाल FW_ISO_CONTEXT_TRANSMIT:
		index = ctx - ohci->it_context_list;
		match = 0;
		अगर (cycle >= 0)
			match = IT_CONTEXT_CYCLE_MATCH_ENABLE |
				(cycle & 0x7fff) << 16;

		reg_ग_लिखो(ohci, OHCI1394_IsoXmitIntEventClear, 1 << index);
		reg_ग_लिखो(ohci, OHCI1394_IsoXmitIntMaskSet, 1 << index);
		context_run(&ctx->context, match);
		अवरोध;

	हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:
		control |= IR_CONTEXT_BUFFER_FILL|IR_CONTEXT_MULTI_CHANNEL_MODE;
		fallthrough;
	हाल FW_ISO_CONTEXT_RECEIVE:
		index = ctx - ohci->ir_context_list;
		match = (tags << 28) | (sync << 8) | ctx->base.channel;
		अगर (cycle >= 0) अणु
			match |= (cycle & 0x07fff) << 12;
			control |= IR_CONTEXT_CYCLE_MATCH_ENABLE;
		पूर्ण

		reg_ग_लिखो(ohci, OHCI1394_IsoRecvIntEventClear, 1 << index);
		reg_ग_लिखो(ohci, OHCI1394_IsoRecvIntMaskSet, 1 << index);
		reg_ग_लिखो(ohci, CONTEXT_MATCH(ctx->context.regs), match);
		context_run(&ctx->context, control);

		ctx->sync = sync;
		ctx->tags = tags;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ohci_stop_iso(काष्ठा fw_iso_context *base)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(base->card);
	काष्ठा iso_context *ctx = container_of(base, काष्ठा iso_context, base);
	पूर्णांक index;

	चयन (ctx->base.type) अणु
	हाल FW_ISO_CONTEXT_TRANSMIT:
		index = ctx - ohci->it_context_list;
		reg_ग_लिखो(ohci, OHCI1394_IsoXmitIntMaskClear, 1 << index);
		अवरोध;

	हाल FW_ISO_CONTEXT_RECEIVE:
	हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:
		index = ctx - ohci->ir_context_list;
		reg_ग_लिखो(ohci, OHCI1394_IsoRecvIntMaskClear, 1 << index);
		अवरोध;
	पूर्ण
	flush_ग_लिखोs(ohci);
	context_stop(&ctx->context);
	tasklet_समाप्त(&ctx->context.tasklet);

	वापस 0;
पूर्ण

अटल व्योम ohci_मुक्त_iso_context(काष्ठा fw_iso_context *base)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(base->card);
	काष्ठा iso_context *ctx = container_of(base, काष्ठा iso_context, base);
	अचिन्हित दीर्घ flags;
	पूर्णांक index;

	ohci_stop_iso(base);
	context_release(&ctx->context);
	मुक्त_page((अचिन्हित दीर्घ)ctx->header);

	spin_lock_irqsave(&ohci->lock, flags);

	चयन (base->type) अणु
	हाल FW_ISO_CONTEXT_TRANSMIT:
		index = ctx - ohci->it_context_list;
		ohci->it_context_mask |= 1 << index;
		अवरोध;

	हाल FW_ISO_CONTEXT_RECEIVE:
		index = ctx - ohci->ir_context_list;
		ohci->ir_context_mask |= 1 << index;
		ohci->ir_context_channels |= 1ULL << base->channel;
		अवरोध;

	हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:
		index = ctx - ohci->ir_context_list;
		ohci->ir_context_mask |= 1 << index;
		ohci->ir_context_channels |= ohci->mc_channels;
		ohci->mc_channels = 0;
		ohci->mc_allocated = false;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&ohci->lock, flags);
पूर्ण

अटल पूर्णांक ohci_set_iso_channels(काष्ठा fw_iso_context *base, u64 *channels)
अणु
	काष्ठा fw_ohci *ohci = fw_ohci(base->card);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	चयन (base->type) अणु
	हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:

		spin_lock_irqsave(&ohci->lock, flags);

		/* Don't allow multichannel to grab other contexts' channels. */
		अगर (~ohci->ir_context_channels & ~ohci->mc_channels & *channels) अणु
			*channels = ohci->ir_context_channels;
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			set_multichannel_mask(ohci, *channels);
			ret = 0;
		पूर्ण

		spin_unlock_irqrestore(&ohci->lock, flags);

		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम ohci_resume_iso_dma(काष्ठा fw_ohci *ohci)
अणु
	पूर्णांक i;
	काष्ठा iso_context *ctx;

	क्रम (i = 0 ; i < ohci->n_ir ; i++) अणु
		ctx = &ohci->ir_context_list[i];
		अगर (ctx->context.running)
			ohci_start_iso(&ctx->base, 0, ctx->sync, ctx->tags);
	पूर्ण

	क्रम (i = 0 ; i < ohci->n_it ; i++) अणु
		ctx = &ohci->it_context_list[i];
		अगर (ctx->context.running)
			ohci_start_iso(&ctx->base, 0, ctx->sync, ctx->tags);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक queue_iso_transmit(काष्ठा iso_context *ctx,
			      काष्ठा fw_iso_packet *packet,
			      काष्ठा fw_iso_buffer *buffer,
			      अचिन्हित दीर्घ payload)
अणु
	काष्ठा descriptor *d, *last, *pd;
	काष्ठा fw_iso_packet *p;
	__le32 *header;
	dma_addr_t d_bus, page_bus;
	u32 z, header_z, payload_z, irq;
	u32 payload_index, payload_end_index, next_page_index;
	पूर्णांक page, end_page, i, length, offset;

	p = packet;
	payload_index = payload;

	अगर (p->skip)
		z = 1;
	अन्यथा
		z = 2;
	अगर (p->header_length > 0)
		z++;

	/* Determine the first page the payload isn't contained in. */
	end_page = PAGE_ALIGN(payload_index + p->payload_length) >> PAGE_SHIFT;
	अगर (p->payload_length > 0)
		payload_z = end_page - (payload_index >> PAGE_SHIFT);
	अन्यथा
		payload_z = 0;

	z += payload_z;

	/* Get header size in number of descriptors. */
	header_z = DIV_ROUND_UP(p->header_length, माप(*d));

	d = context_get_descriptors(&ctx->context, z + header_z, &d_bus);
	अगर (d == शून्य)
		वापस -ENOMEM;

	अगर (!p->skip) अणु
		d[0].control   = cpu_to_le16(DESCRIPTOR_KEY_IMMEDIATE);
		d[0].req_count = cpu_to_le16(8);
		/*
		 * Link the skip address to this descriptor itself.  This causes
		 * a context to skip a cycle whenever lost cycles or FIFO
		 * overruns occur, without dropping the data.  The application
		 * should then decide whether this is an error condition or not.
		 * FIXME:  Make the context's cycle-lost behaviour configurable?
		 */
		d[0].branch_address = cpu_to_le32(d_bus | z);

		header = (__le32 *) &d[1];
		header[0] = cpu_to_le32(IT_HEADER_SY(p->sy) |
					IT_HEADER_TAG(p->tag) |
					IT_HEADER_TCODE(TCODE_STREAM_DATA) |
					IT_HEADER_CHANNEL(ctx->base.channel) |
					IT_HEADER_SPEED(ctx->base.speed));
		header[1] =
			cpu_to_le32(IT_HEADER_DATA_LENGTH(p->header_length +
							  p->payload_length));
	पूर्ण

	अगर (p->header_length > 0) अणु
		d[2].req_count    = cpu_to_le16(p->header_length);
		d[2].data_address = cpu_to_le32(d_bus + z * माप(*d));
		स_नकल(&d[z], p->header, p->header_length);
	पूर्ण

	pd = d + z - payload_z;
	payload_end_index = payload_index + p->payload_length;
	क्रम (i = 0; i < payload_z; i++) अणु
		page               = payload_index >> PAGE_SHIFT;
		offset             = payload_index & ~PAGE_MASK;
		next_page_index    = (page + 1) << PAGE_SHIFT;
		length             =
			min(next_page_index, payload_end_index) - payload_index;
		pd[i].req_count    = cpu_to_le16(length);

		page_bus = page_निजी(buffer->pages[page]);
		pd[i].data_address = cpu_to_le32(page_bus + offset);

		dma_sync_single_range_क्रम_device(ctx->context.ohci->card.device,
						 page_bus, offset, length,
						 DMA_TO_DEVICE);

		payload_index += length;
	पूर्ण

	अगर (p->पूर्णांकerrupt)
		irq = DESCRIPTOR_IRQ_ALWAYS;
	अन्यथा
		irq = DESCRIPTOR_NO_IRQ;

	last = z == 2 ? d : d + z - 1;
	last->control |= cpu_to_le16(DESCRIPTOR_OUTPUT_LAST |
				     DESCRIPTOR_STATUS |
				     DESCRIPTOR_BRANCH_ALWAYS |
				     irq);

	context_append(&ctx->context, d, z, header_z);

	वापस 0;
पूर्ण

अटल पूर्णांक queue_iso_packet_per_buffer(काष्ठा iso_context *ctx,
				       काष्ठा fw_iso_packet *packet,
				       काष्ठा fw_iso_buffer *buffer,
				       अचिन्हित दीर्घ payload)
अणु
	काष्ठा device *device = ctx->context.ohci->card.device;
	काष्ठा descriptor *d, *pd;
	dma_addr_t d_bus, page_bus;
	u32 z, header_z, rest;
	पूर्णांक i, j, length;
	पूर्णांक page, offset, packet_count, header_size, payload_per_buffer;

	/*
	 * The OHCI controller माला_दो the isochronous header and trailer in the
	 * buffer, so we need at least 8 bytes.
	 */
	packet_count = packet->header_length / ctx->base.header_size;
	header_size  = max(ctx->base.header_size, (माप_प्रकार)8);

	/* Get header size in number of descriptors. */
	header_z = DIV_ROUND_UP(header_size, माप(*d));
	page     = payload >> PAGE_SHIFT;
	offset   = payload & ~PAGE_MASK;
	payload_per_buffer = packet->payload_length / packet_count;

	क्रम (i = 0; i < packet_count; i++) अणु
		/* d poपूर्णांकs to the header descriptor */
		z = DIV_ROUND_UP(payload_per_buffer + offset, PAGE_SIZE) + 1;
		d = context_get_descriptors(&ctx->context,
				z + header_z, &d_bus);
		अगर (d == शून्य)
			वापस -ENOMEM;

		d->control      = cpu_to_le16(DESCRIPTOR_STATUS |
					      DESCRIPTOR_INPUT_MORE);
		अगर (packet->skip && i == 0)
			d->control |= cpu_to_le16(DESCRIPTOR_WAIT);
		d->req_count    = cpu_to_le16(header_size);
		d->res_count    = d->req_count;
		d->transfer_status = 0;
		d->data_address = cpu_to_le32(d_bus + (z * माप(*d)));

		rest = payload_per_buffer;
		pd = d;
		क्रम (j = 1; j < z; j++) अणु
			pd++;
			pd->control = cpu_to_le16(DESCRIPTOR_STATUS |
						  DESCRIPTOR_INPUT_MORE);

			अगर (offset + rest < PAGE_SIZE)
				length = rest;
			अन्यथा
				length = PAGE_SIZE - offset;
			pd->req_count = cpu_to_le16(length);
			pd->res_count = pd->req_count;
			pd->transfer_status = 0;

			page_bus = page_निजी(buffer->pages[page]);
			pd->data_address = cpu_to_le32(page_bus + offset);

			dma_sync_single_range_क्रम_device(device, page_bus,
							 offset, length,
							 DMA_FROM_DEVICE);

			offset = (offset + length) & ~PAGE_MASK;
			rest -= length;
			अगर (offset == 0)
				page++;
		पूर्ण
		pd->control = cpu_to_le16(DESCRIPTOR_STATUS |
					  DESCRIPTOR_INPUT_LAST |
					  DESCRIPTOR_BRANCH_ALWAYS);
		अगर (packet->पूर्णांकerrupt && i == packet_count - 1)
			pd->control |= cpu_to_le16(DESCRIPTOR_IRQ_ALWAYS);

		context_append(&ctx->context, d, z, header_z);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक queue_iso_buffer_fill(काष्ठा iso_context *ctx,
				 काष्ठा fw_iso_packet *packet,
				 काष्ठा fw_iso_buffer *buffer,
				 अचिन्हित दीर्घ payload)
अणु
	काष्ठा descriptor *d;
	dma_addr_t d_bus, page_bus;
	पूर्णांक page, offset, rest, z, i, length;

	page   = payload >> PAGE_SHIFT;
	offset = payload & ~PAGE_MASK;
	rest   = packet->payload_length;

	/* We need one descriptor क्रम each page in the buffer. */
	z = DIV_ROUND_UP(offset + rest, PAGE_SIZE);

	अगर (WARN_ON(offset & 3 || rest & 3 || page + z > buffer->page_count))
		वापस -EFAULT;

	क्रम (i = 0; i < z; i++) अणु
		d = context_get_descriptors(&ctx->context, 1, &d_bus);
		अगर (d == शून्य)
			वापस -ENOMEM;

		d->control = cpu_to_le16(DESCRIPTOR_INPUT_MORE |
					 DESCRIPTOR_BRANCH_ALWAYS);
		अगर (packet->skip && i == 0)
			d->control |= cpu_to_le16(DESCRIPTOR_WAIT);
		अगर (packet->पूर्णांकerrupt && i == z - 1)
			d->control |= cpu_to_le16(DESCRIPTOR_IRQ_ALWAYS);

		अगर (offset + rest < PAGE_SIZE)
			length = rest;
		अन्यथा
			length = PAGE_SIZE - offset;
		d->req_count = cpu_to_le16(length);
		d->res_count = d->req_count;
		d->transfer_status = 0;

		page_bus = page_निजी(buffer->pages[page]);
		d->data_address = cpu_to_le32(page_bus + offset);

		dma_sync_single_range_क्रम_device(ctx->context.ohci->card.device,
						 page_bus, offset, length,
						 DMA_FROM_DEVICE);

		rest -= length;
		offset = 0;
		page++;

		context_append(&ctx->context, d, 1, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ohci_queue_iso(काष्ठा fw_iso_context *base,
			  काष्ठा fw_iso_packet *packet,
			  काष्ठा fw_iso_buffer *buffer,
			  अचिन्हित दीर्घ payload)
अणु
	काष्ठा iso_context *ctx = container_of(base, काष्ठा iso_context, base);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENOSYS;

	spin_lock_irqsave(&ctx->context.ohci->lock, flags);
	चयन (base->type) अणु
	हाल FW_ISO_CONTEXT_TRANSMIT:
		ret = queue_iso_transmit(ctx, packet, buffer, payload);
		अवरोध;
	हाल FW_ISO_CONTEXT_RECEIVE:
		ret = queue_iso_packet_per_buffer(ctx, packet, buffer, payload);
		अवरोध;
	हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:
		ret = queue_iso_buffer_fill(ctx, packet, buffer, payload);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ctx->context.ohci->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम ohci_flush_queue_iso(काष्ठा fw_iso_context *base)
अणु
	काष्ठा context *ctx =
			&container_of(base, काष्ठा iso_context, base)->context;

	reg_ग_लिखो(ctx->ohci, CONTROL_SET(ctx->regs), CONTEXT_WAKE);
पूर्ण

अटल पूर्णांक ohci_flush_iso_completions(काष्ठा fw_iso_context *base)
अणु
	काष्ठा iso_context *ctx = container_of(base, काष्ठा iso_context, base);
	पूर्णांक ret = 0;

	tasklet_disable_in_atomic(&ctx->context.tasklet);

	अगर (!test_and_set_bit_lock(0, &ctx->flushing_completions)) अणु
		context_tasklet((अचिन्हित दीर्घ)&ctx->context);

		चयन (base->type) अणु
		हाल FW_ISO_CONTEXT_TRANSMIT:
		हाल FW_ISO_CONTEXT_RECEIVE:
			अगर (ctx->header_length != 0)
				flush_iso_completions(ctx);
			अवरोध;
		हाल FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL:
			अगर (ctx->mc_completed != 0)
				flush_ir_buffer_fill(ctx);
			अवरोध;
		शेष:
			ret = -ENOSYS;
		पूर्ण

		clear_bit_unlock(0, &ctx->flushing_completions);
		smp_mb__after_atomic();
	पूर्ण

	tasklet_enable(&ctx->context.tasklet);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा fw_card_driver ohci_driver = अणु
	.enable			= ohci_enable,
	.पढ़ो_phy_reg		= ohci_पढ़ो_phy_reg,
	.update_phy_reg		= ohci_update_phy_reg,
	.set_config_rom		= ohci_set_config_rom,
	.send_request		= ohci_send_request,
	.send_response		= ohci_send_response,
	.cancel_packet		= ohci_cancel_packet,
	.enable_phys_dma	= ohci_enable_phys_dma,
	.पढ़ो_csr		= ohci_पढ़ो_csr,
	.ग_लिखो_csr		= ohci_ग_लिखो_csr,

	.allocate_iso_context	= ohci_allocate_iso_context,
	.मुक्त_iso_context	= ohci_मुक्त_iso_context,
	.set_iso_channels	= ohci_set_iso_channels,
	.queue_iso		= ohci_queue_iso,
	.flush_queue_iso	= ohci_flush_queue_iso,
	.flush_iso_completions	= ohci_flush_iso_completions,
	.start_iso		= ohci_start_iso,
	.stop_iso		= ohci_stop_iso,
पूर्ण;

#अगर_घोषित CONFIG_PPC_PMAC
अटल व्योम pmac_ohci_on(काष्ठा pci_dev *dev)
अणु
	अगर (machine_is(घातermac)) अणु
		काष्ठा device_node *ofn = pci_device_to_OF_node(dev);

		अगर (ofn) अणु
			pmac_call_feature(PMAC_FTR_1394_CABLE_POWER, ofn, 0, 1);
			pmac_call_feature(PMAC_FTR_1394_ENABLE, ofn, 0, 1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pmac_ohci_off(काष्ठा pci_dev *dev)
अणु
	अगर (machine_is(घातermac)) अणु
		काष्ठा device_node *ofn = pci_device_to_OF_node(dev);

		अगर (ofn) अणु
			pmac_call_feature(PMAC_FTR_1394_ENABLE, ofn, 0, 0);
			pmac_call_feature(PMAC_FTR_1394_CABLE_POWER, ofn, 0, 0);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pmac_ohci_on(काष्ठा pci_dev *dev) अणुपूर्ण
अटल अंतरभूत व्योम pmac_ohci_off(काष्ठा pci_dev *dev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

अटल पूर्णांक pci_probe(काष्ठा pci_dev *dev,
			       स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fw_ohci *ohci;
	u32 bus_options, max_receive, link_speed, version;
	u64 guid;
	पूर्णांक i, err;
	माप_प्रकार size;

	अगर (dev->venकरोr == PCI_VENDOR_ID_PINNACLE_SYSTEMS) अणु
		dev_err(&dev->dev, "Pinnacle MovieBoard is not yet supported\n");
		वापस -ENOSYS;
	पूर्ण

	ohci = kzalloc(माप(*ohci), GFP_KERNEL);
	अगर (ohci == शून्य) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	fw_card_initialize(&ohci->card, &ohci_driver, &dev->dev);

	pmac_ohci_on(dev);

	err = pci_enable_device(dev);
	अगर (err) अणु
		dev_err(&dev->dev, "failed to enable OHCI hardware\n");
		जाओ fail_मुक्त;
	पूर्ण

	pci_set_master(dev);
	pci_ग_लिखो_config_dword(dev, OHCI1394_PCI_HCI_Control, 0);
	pci_set_drvdata(dev, ohci);

	spin_lock_init(&ohci->lock);
	mutex_init(&ohci->phy_reg_mutex);

	INIT_WORK(&ohci->bus_reset_work, bus_reset_work);

	अगर (!(pci_resource_flags(dev, 0) & IORESOURCE_MEM) ||
	    pci_resource_len(dev, 0) < OHCI1394_REGISTER_SIZE) अणु
		ohci_err(ohci, "invalid MMIO resource\n");
		err = -ENXIO;
		जाओ fail_disable;
	पूर्ण

	err = pci_request_region(dev, 0, ohci_driver_name);
	अगर (err) अणु
		ohci_err(ohci, "MMIO resource unavailable\n");
		जाओ fail_disable;
	पूर्ण

	ohci->रेजिस्टरs = pci_iomap(dev, 0, OHCI1394_REGISTER_SIZE);
	अगर (ohci->रेजिस्टरs == शून्य) अणु
		ohci_err(ohci, "failed to remap registers\n");
		err = -ENXIO;
		जाओ fail_iomem;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ohci_quirks); i++)
		अगर ((ohci_quirks[i].venकरोr == dev->venकरोr) &&
		    (ohci_quirks[i].device == (अचिन्हित लघु)PCI_ANY_ID ||
		     ohci_quirks[i].device == dev->device) &&
		    (ohci_quirks[i].revision == (अचिन्हित लघु)PCI_ANY_ID ||
		     ohci_quirks[i].revision >= dev->revision)) अणु
			ohci->quirks = ohci_quirks[i].flags;
			अवरोध;
		पूर्ण
	अगर (param_quirks)
		ohci->quirks = param_quirks;

	/*
	 * Because dma_alloc_coherent() allocates at least one page,
	 * we save space by using a common buffer क्रम the AR request/
	 * response descriptors and the self IDs buffer.
	 */
	BUILD_BUG_ON(AR_BUFFERS * माप(काष्ठा descriptor) > PAGE_SIZE/4);
	BUILD_BUG_ON(SELF_ID_BUF_SIZE > PAGE_SIZE/2);
	ohci->misc_buffer = dma_alloc_coherent(ohci->card.device,
					       PAGE_SIZE,
					       &ohci->misc_buffer_bus,
					       GFP_KERNEL);
	अगर (!ohci->misc_buffer) अणु
		err = -ENOMEM;
		जाओ fail_iounmap;
	पूर्ण

	err = ar_context_init(&ohci->ar_request_ctx, ohci, 0,
			      OHCI1394_AsReqRcvContextControlSet);
	अगर (err < 0)
		जाओ fail_misc_buf;

	err = ar_context_init(&ohci->ar_response_ctx, ohci, PAGE_SIZE/4,
			      OHCI1394_AsRspRcvContextControlSet);
	अगर (err < 0)
		जाओ fail_arreq_ctx;

	err = context_init(&ohci->at_request_ctx, ohci,
			   OHCI1394_AsReqTrContextControlSet, handle_at_packet);
	अगर (err < 0)
		जाओ fail_arrsp_ctx;

	err = context_init(&ohci->at_response_ctx, ohci,
			   OHCI1394_AsRspTrContextControlSet, handle_at_packet);
	अगर (err < 0)
		जाओ fail_atreq_ctx;

	reg_ग_लिखो(ohci, OHCI1394_IsoRecvIntMaskSet, ~0);
	ohci->ir_context_channels = ~0ULL;
	ohci->ir_context_support = reg_पढ़ो(ohci, OHCI1394_IsoRecvIntMaskSet);
	reg_ग_लिखो(ohci, OHCI1394_IsoRecvIntMaskClear, ~0);
	ohci->ir_context_mask = ohci->ir_context_support;
	ohci->n_ir = hweight32(ohci->ir_context_mask);
	size = माप(काष्ठा iso_context) * ohci->n_ir;
	ohci->ir_context_list = kzalloc(size, GFP_KERNEL);

	reg_ग_लिखो(ohci, OHCI1394_IsoXmitIntMaskSet, ~0);
	ohci->it_context_support = reg_पढ़ो(ohci, OHCI1394_IsoXmitIntMaskSet);
	/* JMicron JMB38x often shows 0 at first पढ़ो, just ignore it */
	अगर (!ohci->it_context_support) अणु
		ohci_notice(ohci, "overriding IsoXmitIntMask\n");
		ohci->it_context_support = 0xf;
	पूर्ण
	reg_ग_लिखो(ohci, OHCI1394_IsoXmitIntMaskClear, ~0);
	ohci->it_context_mask = ohci->it_context_support;
	ohci->n_it = hweight32(ohci->it_context_mask);
	size = माप(काष्ठा iso_context) * ohci->n_it;
	ohci->it_context_list = kzalloc(size, GFP_KERNEL);

	अगर (ohci->it_context_list == शून्य || ohci->ir_context_list == शून्य) अणु
		err = -ENOMEM;
		जाओ fail_contexts;
	पूर्ण

	ohci->self_id     = ohci->misc_buffer     + PAGE_SIZE/2;
	ohci->self_id_bus = ohci->misc_buffer_bus + PAGE_SIZE/2;

	bus_options = reg_पढ़ो(ohci, OHCI1394_BusOptions);
	max_receive = (bus_options >> 12) & 0xf;
	link_speed = bus_options & 0x7;
	guid = ((u64) reg_पढ़ो(ohci, OHCI1394_GUIDHi) << 32) |
		reg_पढ़ो(ohci, OHCI1394_GUIDLo);

	अगर (!(ohci->quirks & QUIRK_NO_MSI))
		pci_enable_msi(dev);
	अगर (request_irq(dev->irq, irq_handler,
			pci_dev_msi_enabled(dev) ? 0 : IRQF_SHARED,
			ohci_driver_name, ohci)) अणु
		ohci_err(ohci, "failed to allocate interrupt %d\n", dev->irq);
		err = -EIO;
		जाओ fail_msi;
	पूर्ण

	err = fw_card_add(&ohci->card, max_receive, link_speed, guid);
	अगर (err)
		जाओ fail_irq;

	version = reg_पढ़ो(ohci, OHCI1394_Version) & 0x00ff00ff;
	ohci_notice(ohci,
		    "added OHCI v%x.%x device as card %d, "
		    "%d IR + %d IT contexts, quirks 0x%x%s\n",
		    version >> 16, version & 0xff, ohci->card.index,
		    ohci->n_ir, ohci->n_it, ohci->quirks,
		    reg_पढ़ो(ohci, OHCI1394_PhyUpperBound) ?
			", physUB" : "");

	वापस 0;

 fail_irq:
	मुक्त_irq(dev->irq, ohci);
 fail_msi:
	pci_disable_msi(dev);
 fail_contexts:
	kमुक्त(ohci->ir_context_list);
	kमुक्त(ohci->it_context_list);
	context_release(&ohci->at_response_ctx);
 fail_atreq_ctx:
	context_release(&ohci->at_request_ctx);
 fail_arrsp_ctx:
	ar_context_release(&ohci->ar_response_ctx);
 fail_arreq_ctx:
	ar_context_release(&ohci->ar_request_ctx);
 fail_misc_buf:
	dma_मुक्त_coherent(ohci->card.device, PAGE_SIZE,
			  ohci->misc_buffer, ohci->misc_buffer_bus);
 fail_iounmap:
	pci_iounmap(dev, ohci->रेजिस्टरs);
 fail_iomem:
	pci_release_region(dev, 0);
 fail_disable:
	pci_disable_device(dev);
 fail_मुक्त:
	kमुक्त(ohci);
	pmac_ohci_off(dev);
 fail:
	वापस err;
पूर्ण

अटल व्योम pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fw_ohci *ohci = pci_get_drvdata(dev);

	/*
	 * If the removal is happening from the suspend state, LPS won't be
	 * enabled and host रेजिस्टरs (eg., IntMaskClear) won't be accessible.
	 */
	अगर (reg_पढ़ो(ohci, OHCI1394_HCControlSet) & OHCI1394_HCControl_LPS) अणु
		reg_ग_लिखो(ohci, OHCI1394_IntMaskClear, ~0);
		flush_ग_लिखोs(ohci);
	पूर्ण
	cancel_work_sync(&ohci->bus_reset_work);
	fw_core_हटाओ_card(&ohci->card);

	/*
	 * FIXME: Fail all pending packets here, now that the upper
	 * layers can't queue any more.
	 */

	software_reset(ohci);
	मुक्त_irq(dev->irq, ohci);

	अगर (ohci->next_config_rom && ohci->next_config_rom != ohci->config_rom)
		dma_मुक्त_coherent(ohci->card.device, CONFIG_ROM_SIZE,
				  ohci->next_config_rom, ohci->next_config_rom_bus);
	अगर (ohci->config_rom)
		dma_मुक्त_coherent(ohci->card.device, CONFIG_ROM_SIZE,
				  ohci->config_rom, ohci->config_rom_bus);
	ar_context_release(&ohci->ar_request_ctx);
	ar_context_release(&ohci->ar_response_ctx);
	dma_मुक्त_coherent(ohci->card.device, PAGE_SIZE,
			  ohci->misc_buffer, ohci->misc_buffer_bus);
	context_release(&ohci->at_request_ctx);
	context_release(&ohci->at_response_ctx);
	kमुक्त(ohci->it_context_list);
	kमुक्त(ohci->ir_context_list);
	pci_disable_msi(dev);
	pci_iounmap(dev, ohci->रेजिस्टरs);
	pci_release_region(dev, 0);
	pci_disable_device(dev);
	kमुक्त(ohci);
	pmac_ohci_off(dev);

	dev_notice(&dev->dev, "removed fw-ohci device\n");
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pci_suspend(काष्ठा pci_dev *dev, pm_message_t state)
अणु
	काष्ठा fw_ohci *ohci = pci_get_drvdata(dev);
	पूर्णांक err;

	software_reset(ohci);
	err = pci_save_state(dev);
	अगर (err) अणु
		ohci_err(ohci, "pci_save_state failed\n");
		वापस err;
	पूर्ण
	err = pci_set_घातer_state(dev, pci_choose_state(dev, state));
	अगर (err)
		ohci_err(ohci, "pci_set_power_state failed with %d\n", err);
	pmac_ohci_off(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_resume(काष्ठा pci_dev *dev)
अणु
	काष्ठा fw_ohci *ohci = pci_get_drvdata(dev);
	पूर्णांक err;

	pmac_ohci_on(dev);
	pci_set_घातer_state(dev, PCI_D0);
	pci_restore_state(dev);
	err = pci_enable_device(dev);
	अगर (err) अणु
		ohci_err(ohci, "pci_enable_device failed\n");
		वापस err;
	पूर्ण

	/* Some प्रणालीs करोn't setup GUID रेजिस्टर on resume from ram  */
	अगर (!reg_पढ़ो(ohci, OHCI1394_GUIDLo) &&
					!reg_पढ़ो(ohci, OHCI1394_GUIDHi)) अणु
		reg_ग_लिखो(ohci, OHCI1394_GUIDLo, (u32)ohci->card.guid);
		reg_ग_लिखो(ohci, OHCI1394_GUIDHi, (u32)(ohci->card.guid >> 32));
	पूर्ण

	err = ohci_enable(&ohci->card, शून्य, 0);
	अगर (err)
		वापस err;

	ohci_resume_iso_dma(ohci);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id pci_table[] = अणु
	अणु PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_FIREWIRE_OHCI, ~0) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_table);

अटल काष्ठा pci_driver fw_ohci_pci_driver = अणु
	.name		= ohci_driver_name,
	.id_table	= pci_table,
	.probe		= pci_probe,
	.हटाओ		= pci_हटाओ,
#अगर_घोषित CONFIG_PM
	.resume		= pci_resume,
	.suspend	= pci_suspend,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init fw_ohci_init(व्योम)
अणु
	selfid_workqueue = alloc_workqueue(KBUILD_MODNAME, WQ_MEM_RECLAIM, 0);
	अगर (!selfid_workqueue)
		वापस -ENOMEM;

	वापस pci_रेजिस्टर_driver(&fw_ohci_pci_driver);
पूर्ण

अटल व्योम __निकास fw_ohci_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&fw_ohci_pci_driver);
	destroy_workqueue(selfid_workqueue);
पूर्ण

module_init(fw_ohci_init);
module_निकास(fw_ohci_cleanup);

MODULE_AUTHOR("Kristian Hoegsberg <krh@bitplanet.net>");
MODULE_DESCRIPTION("Driver for PCI OHCI IEEE1394 controllers");
MODULE_LICENSE("GPL");

/* Provide a module alias so root-on-sbp2 initrds करोn't अवरोध. */
MODULE_ALIAS("ohci1394");
