<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mtu3.h - MediaTek USB3 DRD header
 *
 * Copyright (C) 2016 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#अगर_अघोषित __MTU3_H__
#घोषणा __MTU3_H__

#समावेश <linux/device.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/extcon.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>

काष्ठा mtu3;
काष्ठा mtu3_ep;
काष्ठा mtu3_request;

#समावेश "mtu3_hw_regs.h"
#समावेश "mtu3_qmu.h"

#घोषणा	MU3D_EP_TXCR0(epnum)	(U3D_TX1CSR0 + (((epnum) - 1) * 0x10))
#घोषणा	MU3D_EP_TXCR1(epnum)	(U3D_TX1CSR1 + (((epnum) - 1) * 0x10))
#घोषणा	MU3D_EP_TXCR2(epnum)	(U3D_TX1CSR2 + (((epnum) - 1) * 0x10))

#घोषणा	MU3D_EP_RXCR0(epnum)	(U3D_RX1CSR0 + (((epnum) - 1) * 0x10))
#घोषणा	MU3D_EP_RXCR1(epnum)	(U3D_RX1CSR1 + (((epnum) - 1) * 0x10))
#घोषणा	MU3D_EP_RXCR2(epnum)	(U3D_RX1CSR2 + (((epnum) - 1) * 0x10))

#घोषणा USB_QMU_TQHIAR(epnum)	(U3D_TXQHIAR1 + (((epnum) - 1) * 0x4))
#घोषणा USB_QMU_RQHIAR(epnum)	(U3D_RXQHIAR1 + (((epnum) - 1) * 0x4))

#घोषणा USB_QMU_RQCSR(epnum)	(U3D_RXQCSR1 + (((epnum) - 1) * 0x10))
#घोषणा USB_QMU_RQSAR(epnum)	(U3D_RXQSAR1 + (((epnum) - 1) * 0x10))
#घोषणा USB_QMU_RQCPR(epnum)	(U3D_RXQCPR1 + (((epnum) - 1) * 0x10))

#घोषणा USB_QMU_TQCSR(epnum)	(U3D_TXQCSR1 + (((epnum) - 1) * 0x10))
#घोषणा USB_QMU_TQSAR(epnum)	(U3D_TXQSAR1 + (((epnum) - 1) * 0x10))
#घोषणा USB_QMU_TQCPR(epnum)	(U3D_TXQCPR1 + (((epnum) - 1) * 0x10))

#घोषणा SSUSB_U3_CTRL(p)	(U3D_SSUSB_U3_CTRL_0P + ((p) * 0x08))
#घोषणा SSUSB_U2_CTRL(p)	(U3D_SSUSB_U2_CTRL_0P + ((p) * 0x08))

#घोषणा MTU3_DRIVER_NAME	"mtu3"
#घोषणा	DMA_ADDR_INVALID	(~(dma_addr_t)0)

#घोषणा MTU3_EP_ENABLED		BIT(0)
#घोषणा MTU3_EP_STALL		BIT(1)
#घोषणा MTU3_EP_WEDGE		BIT(2)
#घोषणा MTU3_EP_BUSY		BIT(3)

#घोषणा MTU3_U3_IP_SLOT_DEFAULT 2
#घोषणा MTU3_U2_IP_SLOT_DEFAULT 1

/**
 * IP TRUNK version
 * from 0x1003 version, USB3 Gen2 is supported, two changes affect driver:
 * 1. MAXPKT and MULTI bits layout of TXCSR1 and RXCSR1 are adjusted,
 *    but not backward compatible
 * 2. QMU extend buffer length supported
 */
#घोषणा MTU3_TRUNK_VERS_1003	0x1003

/**
 * Normally the device works on HS or SS, to simplअगरy fअगरo management,
 * devide fअगरo पूर्णांकo some 512B parts, use biपंचांगap to manage it; And
 * 128 bits size of biपंचांगap is large enough, that means it can manage
 * up to 64KB fअगरo size.
 * NOTE: MTU3_EP_FIFO_UNIT should be घातer of two
 */
#घोषणा MTU3_EP_FIFO_UNIT		(1 << 9)
#घोषणा MTU3_FIFO_BIT_SIZE		128
#घोषणा MTU3_U2_IP_EP0_FIFO_SIZE	64

/**
 * Maximum size of ep0 response buffer क्रम ch9 requests,
 * the SET_SEL request uses 6 so far, and GET_STATUS is 2
 */
#घोषणा EP0_RESPONSE_BUF  6

/* device operated link and speed got from DEVICE_CONF रेजिस्टर */
क्रमागत mtu3_speed अणु
	MTU3_SPEED_INACTIVE = 0,
	MTU3_SPEED_FULL = 1,
	MTU3_SPEED_HIGH = 3,
	MTU3_SPEED_SUPER = 4,
	MTU3_SPEED_SUPER_PLUS = 5,
पूर्ण;

/**
 * @MU3D_EP0_STATE_SETUP: रुकोs क्रम SETUP or received a SETUP
 *		without data stage.
 * @MU3D_EP0_STATE_TX: IN data stage
 * @MU3D_EP0_STATE_RX: OUT data stage
 * @MU3D_EP0_STATE_TX_END: the last IN data is transferred, and
 *		रुकोs क्रम its completion पूर्णांकerrupt
 * @MU3D_EP0_STATE_STALL: ep0 is in stall status, will be स्वतः-cleared
 *		after receives a SETUP.
 */
क्रमागत mtu3_g_ep0_state अणु
	MU3D_EP0_STATE_SETUP = 1,
	MU3D_EP0_STATE_TX,
	MU3D_EP0_STATE_RX,
	MU3D_EP0_STATE_TX_END,
	MU3D_EP0_STATE_STALL,
पूर्ण;

/**
 * MTU3_DR_FORCE_NONE: स्वतःmatically चयन host and periperal mode
 *		by IDPIN संकेत.
 * MTU3_DR_FORCE_HOST: क्रमce to enter host mode and override OTG
 *		IDPIN संकेत.
 * MTU3_DR_FORCE_DEVICE: क्रमce to enter peripheral mode.
 */
क्रमागत mtu3_dr_क्रमce_mode अणु
	MTU3_DR_FORCE_NONE = 0,
	MTU3_DR_FORCE_HOST,
	MTU3_DR_FORCE_DEVICE,
पूर्ण;

/**
 * @base: the base address of fअगरo
 * @limit: the biपंचांगap size in bits
 * @biपंचांगap: fअगरo biपंचांगap in unit of @MTU3_EP_FIFO_UNIT
 */
काष्ठा mtu3_fअगरo_info अणु
	u32 base;
	u32 limit;
	DECLARE_BITMAP(biपंचांगap, MTU3_FIFO_BIT_SIZE);
पूर्ण;

/**
 * General Purpose Descriptor (GPD):
 *	The क्रमmat of TX GPD is a little dअगरferent from RX one.
 *	And the size of GPD is 16 bytes.
 *
 * @dw0_info:
 *	bit0: Hardware Own (HWO)
 *	bit1: Buffer Descriptor Present (BDP), always 0, BD is not supported
 *	bit2: Bypass (BPS), 1: HW skips this GPD अगर HWO = 1
 *	bit6: [EL] Zero Length Packet (ZLP), moved from @dw3_info[29]
 *	bit7: Interrupt On Completion (IOC)
 *	bit[31:16]: ([EL] bit[31:12]) allow data buffer length (RX ONLY),
 *		the buffer length of the data to receive
 *	bit[23:16]: ([EL] bit[31:24]) extension address (TX ONLY),
 *		lower 4 bits are extension bits of @buffer,
 *		upper 4 bits are extension bits of @next_gpd
 * @next_gpd: Physical address of the next GPD
 * @buffer: Physical address of the data buffer
 * @dw3_info:
 *	bit[15:0]: ([EL] bit[19:0]) data buffer length,
 *		(TX): the buffer length of the data to transmit
 *		(RX): The total length of data received
 *	bit[23:16]: ([EL] bit[31:24]) extension address (RX ONLY),
 *		lower 4 bits are extension bits of @buffer,
 *		upper 4 bits are extension bits of @next_gpd
 *	bit29: ([EL] abanकरोned) Zero Length Packet (ZLP) (TX ONLY)
 */
काष्ठा qmu_gpd अणु
	__le32 dw0_info;
	__le32 next_gpd;
	__le32 buffer;
	__le32 dw3_info;
पूर्ण __packed;

/**
* dma: physical base address of GPD segment
* start: भव base address of GPD segment
* end: the last GPD element
* enqueue: the first empty GPD to use
* dequeue: the first completed GPD serviced by ISR
* NOTE: the size of GPD ring should be >= 2
*/
काष्ठा mtu3_gpd_ring अणु
	dma_addr_t dma;
	काष्ठा qmu_gpd *start;
	काष्ठा qmu_gpd *end;
	काष्ठा qmu_gpd *enqueue;
	काष्ठा qmu_gpd *dequeue;
पूर्ण;

/**
* @vbus: vbus 5V used by host mode
* @edev: बाह्यal connector used to detect vbus and iddig changes
* @vbus_nb: notअगरier क्रम vbus detection
* @vbus_work : work of vbus detection notअगरier, used to aव्योम sleep in
*		notअगरier callback which is atomic context
* @vbus_event : event of vbus detecion notअगरier
* @id_nb : notअगरier क्रम iddig(idpin) detection
* @id_work : work of iddig detection notअगरier
* @id_event : event of iddig detecion notअगरier
* @role_sw : use USB Role Switch to support dual-role चयन, can't use
*		extcon at the same समय, and extcon is deprecated.
* @role_sw_used : true when the USB Role Switch is used.
* @is_u3_drd: whether port0 supports usb3.0 dual-role device or not
* @manual_drd_enabled: it's true when supports dual-role device by debugfs
*		to चयन host/device modes depending on user input.
*/
काष्ठा otg_चयन_mtk अणु
	काष्ठा regulator *vbus;
	काष्ठा extcon_dev *edev;
	काष्ठा notअगरier_block vbus_nb;
	काष्ठा work_काष्ठा vbus_work;
	अचिन्हित दीर्घ vbus_event;
	काष्ठा notअगरier_block id_nb;
	काष्ठा work_काष्ठा id_work;
	अचिन्हित दीर्घ id_event;
	काष्ठा usb_role_चयन *role_sw;
	bool role_sw_used;
	bool is_u3_drd;
	bool manual_drd_enabled;
पूर्ण;

/**
 * @mac_base: रेजिस्टर base address of device MAC, exclude xHCI's
 * @ippc_base: रेजिस्टर base address of IP Power and Clock पूर्णांकerface (IPPC)
 * @vusb33: usb3.3V shared by device/host IP
 * @sys_clk: प्रणाली घड़ी of mtu3, shared by device/host IP
 * @ref_clk: reference घड़ी
 * @mcu_clk: mcu_bus_ck घड़ी क्रम AHB bus etc
 * @dma_clk: dma_bus_ck घड़ी क्रम AXI bus etc
 * @dr_mode: works in which mode:
 *		host only, device only or dual-role mode
 * @u2_ports: number of usb2.0 host ports
 * @u3_ports: number of usb3.0 host ports
 * @u3p_dis_msk: mask of disabling usb3 ports, क्रम example, bit0==1 to
 *		disable u3port0, bit1==1 to disable u3port1,... etc
 * @dbgfs_root: only used when supports manual dual-role चयन via debugfs
 * @uwk_en: it's true when supports remote wakeup in host mode
 * @uwk: syscon including usb wakeup glue layer between SSUSB IP and SPM
 * @uwk_reg_base: the base address of the wakeup glue layer in @uwk
 * @uwk_vers: the version of the wakeup glue layer
 */
काष्ठा ssusb_mtk अणु
	काष्ठा device *dev;
	काष्ठा mtu3 *u3d;
	व्योम __iomem *mac_base;
	व्योम __iomem *ippc_base;
	काष्ठा phy **phys;
	पूर्णांक num_phys;
	/* common घातer & घड़ी */
	काष्ठा regulator *vusb33;
	काष्ठा clk *sys_clk;
	काष्ठा clk *ref_clk;
	काष्ठा clk *mcu_clk;
	काष्ठा clk *dma_clk;
	/* otg */
	काष्ठा otg_चयन_mtk otg_चयन;
	क्रमागत usb_dr_mode dr_mode;
	bool is_host;
	पूर्णांक u2_ports;
	पूर्णांक u3_ports;
	पूर्णांक u3p_dis_msk;
	काष्ठा dentry *dbgfs_root;
	/* usb wakeup क्रम host mode */
	bool uwk_en;
	काष्ठा regmap *uwk;
	u32 uwk_reg_base;
	u32 uwk_vers;
पूर्ण;

/**
 * @fअगरo_size: it is (@slot + 1) * @fअगरo_seg_size
 * @fअगरo_seg_size: it is roundup_घात_of_two(@maxp)
 */
काष्ठा mtu3_ep अणु
	काष्ठा usb_ep ep;
	अक्षर name[12];
	काष्ठा mtu3 *mtu;
	u8 epnum;
	u8 type;
	u8 is_in;
	u16 maxp;
	पूर्णांक slot;
	u32 fअगरo_size;
	u32 fअगरo_addr;
	u32 fअगरo_seg_size;
	काष्ठा mtu3_fअगरo_info *fअगरo;

	काष्ठा list_head req_list;
	काष्ठा mtu3_gpd_ring gpd_ring;
	स्थिर काष्ठा usb_ss_ep_comp_descriptor *comp_desc;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;

	पूर्णांक flags;
पूर्ण;

काष्ठा mtu3_request अणु
	काष्ठा usb_request request;
	काष्ठा list_head list;
	काष्ठा mtu3_ep *mep;
	काष्ठा mtu3 *mtu;
	काष्ठा qmu_gpd *gpd;
	पूर्णांक epnum;
पूर्ण;

अटल अंतरभूत काष्ठा ssusb_mtk *dev_to_ssusb(काष्ठा device *dev)
अणु
	वापस dev_get_drvdata(dev);
पूर्ण

/**
 * काष्ठा mtu3 - device driver instance data.
 * @slot: MTU3_U2_IP_SLOT_DEFAULT क्रम U2 IP only,
 *		MTU3_U3_IP_SLOT_DEFAULT क्रम U3 IP
 * @may_wakeup: means device's remote wakeup is enabled
 * @is_self_घातered: is reported in device status and the config descriptor
 * @delayed_status: true when function drivers ask क्रम delayed status
 * @gen2cp: compatible with USB3 Gen2 IP
 * @ep0_req: dummy request used जबतक handling standard USB requests
 *		क्रम GET_STATUS and SET_SEL
 * @setup_buf: ep0 response buffer क्रम GET_STATUS and SET_SEL requests
 */
काष्ठा mtu3 अणु
	spinlock_t lock;
	काष्ठा ssusb_mtk *ssusb;
	काष्ठा device *dev;
	व्योम __iomem *mac_base;
	व्योम __iomem *ippc_base;
	पूर्णांक irq;

	काष्ठा mtu3_fअगरo_info tx_fअगरo;
	काष्ठा mtu3_fअगरo_info rx_fअगरo;

	काष्ठा mtu3_ep *ep_array;
	काष्ठा mtu3_ep *in_eps;
	काष्ठा mtu3_ep *out_eps;
	काष्ठा mtu3_ep *ep0;
	पूर्णांक num_eps;
	पूर्णांक slot;
	पूर्णांक active_ep;

	काष्ठा dma_pool	*qmu_gpd_pool;
	क्रमागत mtu3_g_ep0_state ep0_state;
	काष्ठा usb_gadget g;	/* the gadget */
	काष्ठा usb_gadget_driver *gadget_driver;
	काष्ठा mtu3_request ep0_req;
	u8 setup_buf[EP0_RESPONSE_BUF];
	क्रमागत usb_device_speed max_speed;
	क्रमागत usb_device_speed speed;

	अचिन्हित is_active:1;
	अचिन्हित may_wakeup:1;
	अचिन्हित is_self_घातered:1;
	अचिन्हित test_mode:1;
	अचिन्हित softconnect:1;
	अचिन्हित u1_enable:1;
	अचिन्हित u2_enable:1;
	अचिन्हित is_u3_ip:1;
	अचिन्हित delayed_status:1;
	अचिन्हित gen2cp:1;

	u8 address;
	u8 test_mode_nr;
	u32 hw_version;
पूर्ण;

अटल अंतरभूत काष्ठा mtu3 *gadget_to_mtu3(काष्ठा usb_gadget *g)
अणु
	वापस container_of(g, काष्ठा mtu3, g);
पूर्ण

अटल अंतरभूत काष्ठा mtu3_request *to_mtu3_request(काष्ठा usb_request *req)
अणु
	वापस req ? container_of(req, काष्ठा mtu3_request, request) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mtu3_ep *to_mtu3_ep(काष्ठा usb_ep *ep)
अणु
	वापस ep ? container_of(ep, काष्ठा mtu3_ep, ep) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा mtu3_request *next_request(काष्ठा mtu3_ep *mep)
अणु
	वापस list_first_entry_or_null(&mep->req_list, काष्ठा mtu3_request,
					list);
पूर्ण

अटल अंतरभूत व्योम mtu3_ग_लिखोl(व्योम __iomem *base, u32 offset, u32 data)
अणु
	ग_लिखोl(data, base + offset);
पूर्ण

अटल अंतरभूत u32 mtu3_पढ़ोl(व्योम __iomem *base, u32 offset)
अणु
	वापस पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत व्योम mtu3_setbits(व्योम __iomem *base, u32 offset, u32 bits)
अणु
	व्योम __iomem *addr = base + offset;
	u32 पंचांगp = पढ़ोl(addr);

	ग_लिखोl((पंचांगp | (bits)), addr);
पूर्ण

अटल अंतरभूत व्योम mtu3_clrbits(व्योम __iomem *base, u32 offset, u32 bits)
अणु
	व्योम __iomem *addr = base + offset;
	u32 पंचांगp = पढ़ोl(addr);

	ग_लिखोl((पंचांगp & ~(bits)), addr);
पूर्ण

पूर्णांक ssusb_check_घड़ीs(काष्ठा ssusb_mtk *ssusb, u32 ex_clks);
काष्ठा usb_request *mtu3_alloc_request(काष्ठा usb_ep *ep, gfp_t gfp_flags);
व्योम mtu3_मुक्त_request(काष्ठा usb_ep *ep, काष्ठा usb_request *req);
व्योम mtu3_req_complete(काष्ठा mtu3_ep *mep,
		काष्ठा usb_request *req, पूर्णांक status);

पूर्णांक mtu3_config_ep(काष्ठा mtu3 *mtu, काष्ठा mtu3_ep *mep,
		पूर्णांक पूर्णांकerval, पूर्णांक burst, पूर्णांक mult);
व्योम mtu3_deconfig_ep(काष्ठा mtu3 *mtu, काष्ठा mtu3_ep *mep);
व्योम mtu3_ep_stall_set(काष्ठा mtu3_ep *mep, bool set);
व्योम mtu3_ep0_setup(काष्ठा mtu3 *mtu);
व्योम mtu3_start(काष्ठा mtu3 *mtu);
व्योम mtu3_stop(काष्ठा mtu3 *mtu);
व्योम mtu3_dev_on_off(काष्ठा mtu3 *mtu, पूर्णांक is_on);
व्योम mtu3_set_speed(काष्ठा mtu3 *mtu, क्रमागत usb_device_speed speed);

पूर्णांक mtu3_gadget_setup(काष्ठा mtu3 *mtu);
व्योम mtu3_gadget_cleanup(काष्ठा mtu3 *mtu);
व्योम mtu3_gadget_reset(काष्ठा mtu3 *mtu);
व्योम mtu3_gadget_suspend(काष्ठा mtu3 *mtu);
व्योम mtu3_gadget_resume(काष्ठा mtu3 *mtu);
व्योम mtu3_gadget_disconnect(काष्ठा mtu3 *mtu);

irqवापस_t mtu3_ep0_isr(काष्ठा mtu3 *mtu);
बाह्य स्थिर काष्ठा usb_ep_ops mtu3_ep0_ops;

#पूर्ण_अगर
