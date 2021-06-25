<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ci.h - common काष्ठाures, functions, and macros of the ChipIdea driver
 *
 * Copyright (C) 2008 Chipidea - MIPS Technologies, Inc. All rights reserved.
 *
 * Author: David Lopo
 */

#अगर_अघोषित __DRIVERS_USB_CHIPIDEA_CI_H
#घोषणा __DRIVERS_USB_CHIPIDEA_CI_H

#समावेश <linux/list.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg-fsm.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/ulpi/पूर्णांकerface.h>

/******************************************************************************
 * DEFINE
 *****************************************************************************/
#घोषणा TD_PAGE_COUNT      5
#घोषणा CI_HDRC_PAGE_SIZE  4096ul /* page size क्रम TD's */
#घोषणा ENDPT_MAX          32
#घोषणा CI_MAX_BUF_SIZE	(TD_PAGE_COUNT * CI_HDRC_PAGE_SIZE)

/******************************************************************************
 * REGISTERS
 *****************************************************************************/
/* Identअगरication Registers */
#घोषणा ID_ID				0x0
#घोषणा ID_HWGENERAL			0x4
#घोषणा ID_HWHOST			0x8
#घोषणा ID_HWDEVICE			0xc
#घोषणा ID_HWTXBUF			0x10
#घोषणा ID_HWRXBUF			0x14
#घोषणा ID_SBUSCFG			0x90

/* रेजिस्टर indices */
क्रमागत ci_hw_regs अणु
	CAP_CAPLENGTH,
	CAP_HCCPARAMS,
	CAP_DCCPARAMS,
	CAP_TESTMODE,
	CAP_LAST = CAP_TESTMODE,
	OP_USBCMD,
	OP_USBSTS,
	OP_USBINTR,
	OP_DEVICEADDR,
	OP_ENDPTLISTADDR,
	OP_TTCTRL,
	OP_BURSTSIZE,
	OP_ULPI_VIEWPORT,
	OP_PORTSC,
	OP_DEVLC,
	OP_OTGSC,
	OP_USBMODE,
	OP_ENDPTSETUPSTAT,
	OP_ENDPTPRIME,
	OP_ENDPTFLUSH,
	OP_ENDPTSTAT,
	OP_ENDPTCOMPLETE,
	OP_ENDPTCTRL,
	/* endptctrl1..15 follow */
	OP_LAST = OP_ENDPTCTRL + ENDPT_MAX / 2,
पूर्ण;

/******************************************************************************
 * STRUCTURES
 *****************************************************************************/
/**
 * काष्ठा ci_hw_ep - endpoपूर्णांक representation
 * @ep: endpoपूर्णांक काष्ठाure क्रम gadget drivers
 * @dir: endpoपूर्णांक direction (TX/RX)
 * @num: endpoपूर्णांक number
 * @type: endpoपूर्णांक type
 * @name: string description of the endpoपूर्णांक
 * @qh: queue head क्रम this endpoपूर्णांक
 * @wedge: is the endpoपूर्णांक wedged
 * @ci: poपूर्णांकer to the controller
 * @lock: poपूर्णांकer to controller's spinlock
 * @td_pool: poपूर्णांकer to controller's TD pool
 */
काष्ठा ci_hw_ep अणु
	काष्ठा usb_ep				ep;
	u8					dir;
	u8					num;
	u8					type;
	अक्षर					name[16];
	काष्ठा अणु
		काष्ठा list_head	queue;
		काष्ठा ci_hw_qh		*ptr;
		dma_addr_t		dma;
	पूर्ण					qh;
	पूर्णांक					wedge;

	/* global resources */
	काष्ठा ci_hdrc				*ci;
	spinlock_t				*lock;
	काष्ठा dma_pool				*td_pool;
	काष्ठा td_node				*pending_td;
पूर्ण;

क्रमागत ci_role अणु
	CI_ROLE_HOST = 0,
	CI_ROLE_GADGET,
	CI_ROLE_END,
पूर्ण;

क्रमागत ci_revision अणु
	CI_REVISION_1X = 10,	/* Revision 1.x */
	CI_REVISION_20 = 20, /* Revision 2.0 */
	CI_REVISION_21, /* Revision 2.1 */
	CI_REVISION_22, /* Revision 2.2 */
	CI_REVISION_23, /* Revision 2.3 */
	CI_REVISION_24, /* Revision 2.4 */
	CI_REVISION_25, /* Revision 2.5 */
	CI_REVISION_25_PLUS, /* Revision above than 2.5 */
	CI_REVISION_UNKNOWN = 99, /* Unknown Revision */
पूर्ण;

/**
 * काष्ठा ci_role_driver - host/gadget role driver
 * @start: start this role
 * @stop: stop this role
 * @irq: irq handler क्रम this role
 * @name: role name string (host/gadget)
 */
काष्ठा ci_role_driver अणु
	पूर्णांक		(*start)(काष्ठा ci_hdrc *);
	व्योम		(*stop)(काष्ठा ci_hdrc *);
	irqवापस_t	(*irq)(काष्ठा ci_hdrc *);
	स्थिर अक्षर	*name;
पूर्ण;

/**
 * काष्ठा hw_bank - hardware रेजिस्टर mapping representation
 * @lpm: set अगर the device is LPM capable
 * @phys: physical address of the controller's रेजिस्टरs
 * @असल: असलolute address of the beginning of रेजिस्टर winकरोw
 * @cap: capability रेजिस्टरs
 * @op: operational रेजिस्टरs
 * @size: size of the रेजिस्टर winकरोw
 * @regmap: रेजिस्टर lookup table
 */
काष्ठा hw_bank अणु
	अचिन्हित	lpm;
	resource_माप_प्रकार	phys;
	व्योम __iomem	*असल;
	व्योम __iomem	*cap;
	व्योम __iomem	*op;
	माप_प्रकार		size;
	व्योम __iomem	*regmap[OP_LAST + 1];
पूर्ण;

/**
 * काष्ठा ci_hdrc - chipidea device representation
 * @dev: poपूर्णांकer to parent device
 * @lock: access synchronization
 * @hw_bank: hardware रेजिस्टर mapping
 * @irq: IRQ number
 * @roles: array of supported roles क्रम this controller
 * @role: current role
 * @is_otg: अगर the device is otg-capable
 * @fsm: otg finite state machine
 * @otg_fsm_hrसमयr: hrसमयr क्रम otg fsm समयrs
 * @hr_समयouts: समय out list क्रम active otg fsm समयrs
 * @enabled_otg_समयr_bits: bits of enabled otg समयrs
 * @next_otg_समयr: next nearest enabled समयr to be expired
 * @work: work क्रम role changing
 * @wq: workqueue thपढ़ो
 * @qh_pool: allocation pool क्रम queue heads
 * @td_pool: allocation pool क्रम transfer descriptors
 * @gadget: device side representation क्रम peripheral controller
 * @driver: gadget driver
 * @resume_state: save the state of gadget suspend from
 * @hw_ep_max: total number of endpoपूर्णांकs supported by hardware
 * @ci_hw_ep: array of endpoपूर्णांकs
 * @ep0_dir: ep0 direction
 * @ep0out: poपूर्णांकer to ep0 OUT endpoपूर्णांक
 * @ep0in: poपूर्णांकer to ep0 IN endpoपूर्णांक
 * @status: ep0 status request
 * @setaddr: अगर we should set the address on status completion
 * @address: usb address received from the host
 * @remote_wakeup: host-enabled remote wakeup
 * @suspended: suspended by host
 * @test_mode: the selected test mode
 * @platdata: platक्रमm specअगरic inक्रमmation supplied by parent device
 * @vbus_active: is VBUS active
 * @ulpi: poपूर्णांकer to ULPI device, अगर any
 * @ulpi_ops: ULPI पढ़ो/ग_लिखो ops क्रम this device
 * @phy: poपूर्णांकer to PHY, अगर any
 * @usb_phy: poपूर्णांकer to USB PHY, अगर any and अगर using the USB PHY framework
 * @hcd: poपूर्णांकer to usb_hcd क्रम ehci host driver
 * @debugfs: root dentry क्रम this controller in debugfs
 * @id_event: indicates there is an id event, and handled at ci_otg_work
 * @b_sess_valid_event: indicates there is a vbus event, and handled
 * at ci_otg_work
 * @imx28_ग_लिखो_fix: Freescale imx28 needs swp inकाष्ठाion क्रम writing
 * @supports_runसमय_pm: अगर runसमय pm is supported
 * @in_lpm: अगर the core in low घातer mode
 * @wakeup_पूर्णांक: अगर wakeup पूर्णांकerrupt occur
 * @rev: The revision number क्रम controller
 */
काष्ठा ci_hdrc अणु
	काष्ठा device			*dev;
	spinlock_t			lock;
	काष्ठा hw_bank			hw_bank;
	पूर्णांक				irq;
	काष्ठा ci_role_driver		*roles[CI_ROLE_END];
	क्रमागत ci_role			role;
	bool				is_otg;
	काष्ठा usb_otg			otg;
	काष्ठा otg_fsm			fsm;
	काष्ठा hrसमयr			otg_fsm_hrसमयr;
	kसमय_प्रकार				hr_समयouts[NUM_OTG_FSM_TIMERS];
	अचिन्हित			enabled_otg_समयr_bits;
	क्रमागत otg_fsm_समयr		next_otg_समयr;
	काष्ठा usb_role_चयन		*role_चयन;
	काष्ठा work_काष्ठा		work;
	काष्ठा workqueue_काष्ठा		*wq;

	काष्ठा dma_pool			*qh_pool;
	काष्ठा dma_pool			*td_pool;

	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;
	क्रमागत usb_device_state		resume_state;
	अचिन्हित			hw_ep_max;
	काष्ठा ci_hw_ep			ci_hw_ep[ENDPT_MAX];
	u32				ep0_dir;
	काष्ठा ci_hw_ep			*ep0out, *ep0in;

	काष्ठा usb_request		*status;
	bool				setaddr;
	u8				address;
	u8				remote_wakeup;
	u8				suspended;
	u8				test_mode;

	काष्ठा ci_hdrc_platक्रमm_data	*platdata;
	पूर्णांक				vbus_active;
	काष्ठा ulpi			*ulpi;
	काष्ठा ulpi_ops 		ulpi_ops;
	काष्ठा phy			*phy;
	/* old usb_phy पूर्णांकerface */
	काष्ठा usb_phy			*usb_phy;
	काष्ठा usb_hcd			*hcd;
	काष्ठा dentry			*debugfs;
	bool				id_event;
	bool				b_sess_valid_event;
	bool				imx28_ग_लिखो_fix;
	bool				supports_runसमय_pm;
	bool				in_lpm;
	bool				wakeup_पूर्णांक;
	क्रमागत ci_revision		rev;
पूर्ण;

अटल अंतरभूत काष्ठा ci_role_driver *ci_role(काष्ठा ci_hdrc *ci)
अणु
	BUG_ON(ci->role >= CI_ROLE_END || !ci->roles[ci->role]);
	वापस ci->roles[ci->role];
पूर्ण

अटल अंतरभूत पूर्णांक ci_role_start(काष्ठा ci_hdrc *ci, क्रमागत ci_role role)
अणु
	पूर्णांक ret;

	अगर (role >= CI_ROLE_END)
		वापस -EINVAL;

	अगर (!ci->roles[role])
		वापस -ENXIO;

	ret = ci->roles[role]->start(ci);
	अगर (!ret)
		ci->role = role;
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ci_role_stop(काष्ठा ci_hdrc *ci)
अणु
	क्रमागत ci_role role = ci->role;

	अगर (role == CI_ROLE_END)
		वापस;

	ci->role = CI_ROLE_END;

	ci->roles[role]->stop(ci);
पूर्ण

अटल अंतरभूत क्रमागत usb_role ci_role_to_usb_role(काष्ठा ci_hdrc *ci)
अणु
	अगर (ci->role == CI_ROLE_HOST)
		वापस USB_ROLE_HOST;
	अन्यथा अगर (ci->role == CI_ROLE_GADGET && ci->vbus_active)
		वापस USB_ROLE_DEVICE;
	अन्यथा
		वापस USB_ROLE_NONE;
पूर्ण

अटल अंतरभूत क्रमागत ci_role usb_role_to_ci_role(क्रमागत usb_role role)
अणु
	अगर (role == USB_ROLE_HOST)
		वापस CI_ROLE_HOST;
	अन्यथा अगर (role == USB_ROLE_DEVICE)
		वापस CI_ROLE_GADGET;
	अन्यथा
		वापस CI_ROLE_END;
पूर्ण

/**
 * hw_पढ़ो_id_reg: पढ़ोs from a identअगरication रेजिस्टर
 * @ci: the controller
 * @offset: offset from the beginning of identअगरication रेजिस्टरs region
 * @mask: bitfield mask
 *
 * This function वापसs रेजिस्टर contents
 */
अटल अंतरभूत u32 hw_पढ़ो_id_reg(काष्ठा ci_hdrc *ci, u32 offset, u32 mask)
अणु
	वापस ioपढ़ो32(ci->hw_bank.असल + offset) & mask;
पूर्ण

/**
 * hw_ग_लिखो_id_reg: ग_लिखोs to a identअगरication रेजिस्टर
 * @ci: the controller
 * @offset: offset from the beginning of identअगरication रेजिस्टरs region
 * @mask: bitfield mask
 * @data: new value
 */
अटल अंतरभूत व्योम hw_ग_लिखो_id_reg(काष्ठा ci_hdrc *ci, u32 offset,
			    u32 mask, u32 data)
अणु
	अगर (~mask)
		data = (ioपढ़ो32(ci->hw_bank.असल + offset) & ~mask)
			| (data & mask);

	ioग_लिखो32(data, ci->hw_bank.असल + offset);
पूर्ण

/**
 * hw_पढ़ो: पढ़ोs from a hw रेजिस्टर
 * @ci: the controller
 * @reg:  रेजिस्टर index
 * @mask: bitfield mask
 *
 * This function वापसs रेजिस्टर contents
 */
अटल अंतरभूत u32 hw_पढ़ो(काष्ठा ci_hdrc *ci, क्रमागत ci_hw_regs reg, u32 mask)
अणु
	वापस ioपढ़ो32(ci->hw_bank.regmap[reg]) & mask;
पूर्ण

#अगर_घोषित CONFIG_SOC_IMX28
अटल अंतरभूत व्योम imx28_ci_ग_लिखोl(u32 val, अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ ("swp %0, %0, [%1]" : : "r"(val), "r"(addr));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम imx28_ci_ग_लिखोl(u32 val, अस्थिर व्योम __iomem *addr)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम __hw_ग_लिखो(काष्ठा ci_hdrc *ci, u32 val,
		व्योम __iomem *addr)
अणु
	अगर (ci->imx28_ग_लिखो_fix)
		imx28_ci_ग_लिखोl(val, addr);
	अन्यथा
		ioग_लिखो32(val, addr);
पूर्ण

/**
 * hw_ग_लिखो: ग_लिखोs to a hw रेजिस्टर
 * @ci: the controller
 * @reg:  रेजिस्टर index
 * @mask: bitfield mask
 * @data: new value
 */
अटल अंतरभूत व्योम hw_ग_लिखो(काष्ठा ci_hdrc *ci, क्रमागत ci_hw_regs reg,
			    u32 mask, u32 data)
अणु
	अगर (~mask)
		data = (ioपढ़ो32(ci->hw_bank.regmap[reg]) & ~mask)
			| (data & mask);

	__hw_ग_लिखो(ci, data, ci->hw_bank.regmap[reg]);
पूर्ण

/**
 * hw_test_and_clear: tests & clears a hw रेजिस्टर
 * @ci: the controller
 * @reg:  रेजिस्टर index
 * @mask: bitfield mask
 *
 * This function वापसs रेजिस्टर contents
 */
अटल अंतरभूत u32 hw_test_and_clear(काष्ठा ci_hdrc *ci, क्रमागत ci_hw_regs reg,
				    u32 mask)
अणु
	u32 val = ioपढ़ो32(ci->hw_bank.regmap[reg]) & mask;

	__hw_ग_लिखो(ci, val, ci->hw_bank.regmap[reg]);
	वापस val;
पूर्ण

/**
 * hw_test_and_ग_लिखो: tests & ग_लिखोs a hw रेजिस्टर
 * @ci: the controller
 * @reg:  रेजिस्टर index
 * @mask: bitfield mask
 * @data: new value
 *
 * This function वापसs रेजिस्टर contents
 */
अटल अंतरभूत u32 hw_test_and_ग_लिखो(काष्ठा ci_hdrc *ci, क्रमागत ci_hw_regs reg,
				    u32 mask, u32 data)
अणु
	u32 val = hw_पढ़ो(ci, reg, ~0);

	hw_ग_लिखो(ci, reg, mask, data);
	वापस (val & mask) >> __ffs(mask);
पूर्ण

/**
 * ci_otg_is_fsm_mode: runसमय check अगर otg controller
 * is in otg fsm mode.
 *
 * @ci: chipidea device
 */
अटल अंतरभूत bool ci_otg_is_fsm_mode(काष्ठा ci_hdrc *ci)
अणु
#अगर_घोषित CONFIG_USB_OTG_FSM
	काष्ठा usb_otg_caps *otg_caps = &ci->platdata->ci_otg_caps;

	वापस ci->is_otg && ci->roles[CI_ROLE_HOST] &&
		ci->roles[CI_ROLE_GADGET] && (otg_caps->srp_support ||
		otg_caps->hnp_support || otg_caps->adp_support);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

पूर्णांक ci_ulpi_init(काष्ठा ci_hdrc *ci);
व्योम ci_ulpi_निकास(काष्ठा ci_hdrc *ci);
पूर्णांक ci_ulpi_resume(काष्ठा ci_hdrc *ci);

u32 hw_पढ़ो_पूर्णांकr_enable(काष्ठा ci_hdrc *ci);

u32 hw_पढ़ो_पूर्णांकr_status(काष्ठा ci_hdrc *ci);

पूर्णांक hw_device_reset(काष्ठा ci_hdrc *ci);

पूर्णांक hw_port_test_set(काष्ठा ci_hdrc *ci, u8 mode);

u8 hw_port_test_get(काष्ठा ci_hdrc *ci);

व्योम hw_phymode_configure(काष्ठा ci_hdrc *ci);

व्योम ci_platक्रमm_configure(काष्ठा ci_hdrc *ci);

व्योम dbg_create_files(काष्ठा ci_hdrc *ci);

व्योम dbg_हटाओ_files(काष्ठा ci_hdrc *ci);
#पूर्ण_अगर	/* __DRIVERS_USB_CHIPIDEA_CI_H */
