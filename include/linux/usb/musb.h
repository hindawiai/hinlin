<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This is used to क्रम host and peripheral modes of the driver क्रम
 * Inventra (Multidrop) Highspeed Dual-Role Controllers:  (M)HDRC.
 *
 * Board initialization should put one of these पूर्णांकo dev->platक्रमm_data,
 * probably on some platक्रमm_device named "musb-hdrc".  It encapsulates
 * key configuration dअगरferences between boards.
 */

#अगर_अघोषित __LINUX_USB_MUSB_H
#घोषणा __LINUX_USB_MUSB_H

/* The USB role is defined by the connector used on the board, so दीर्घ as
 * standards are being followed.  (Developer boards someबार won't.)
 */
क्रमागत musb_mode अणु
	MUSB_UNDEFINED = 0,
	MUSB_HOST,		/* A or Mini-A connector */
	MUSB_PERIPHERAL,	/* B or Mini-B connector */
	MUSB_OTG		/* Mini-AB connector */
पूर्ण;

काष्ठा clk;

क्रमागत musb_fअगरo_style अणु
	FIFO_RXTX,
	FIFO_TX,
	FIFO_RX
पूर्ण __attribute__ ((packed));

क्रमागत musb_buf_mode अणु
	BUF_SINGLE,
	BUF_DOUBLE
पूर्ण __attribute__ ((packed));

काष्ठा musb_fअगरo_cfg अणु
	u8			hw_ep_num;
	क्रमागत musb_fअगरo_style	style;
	क्रमागत musb_buf_mode	mode;
	u16			maxpacket;
पूर्ण;

#घोषणा MUSB_EP_FIFO(ep, st, m, pkt)		\
अणु						\
	.hw_ep_num	= ep,			\
	.style		= st,			\
	.mode		= m,			\
	.maxpacket	= pkt,			\
पूर्ण

#घोषणा MUSB_EP_FIFO_SINGLE(ep, st, pkt)	\
	MUSB_EP_FIFO(ep, st, BUF_SINGLE, pkt)

#घोषणा MUSB_EP_FIFO_DOUBLE(ep, st, pkt)	\
	MUSB_EP_FIFO(ep, st, BUF_DOUBLE, pkt)

काष्ठा musb_hdrc_eps_bits अणु
	स्थिर अक्षर	name[16];
	u8		bits;
पूर्ण;

काष्ठा musb_hdrc_config अणु
	काष्ठा musb_fअगरo_cfg	*fअगरo_cfg;	/* board fअगरo configuration */
	अचिन्हित		fअगरo_cfg_size;	/* size of the fअगरo configuration */

	/* MUSB configuration-specअगरic details */
	अचिन्हित	multipoपूर्णांक:1;	/* multipoपूर्णांक device */
	अचिन्हित	dyn_fअगरo:1 __deprecated; /* supports dynamic fअगरo sizing */

	/* need to explicitly de-निश्चित the port reset after resume? */
	अचिन्हित	host_port_deनिश्चित_reset_at_resume:1;

	u8		num_eps;	/* number of endpoपूर्णांकs _with_ ep0 */
	u8		ram_bits;	/* ram address size */

	u32		maximum_speed;
पूर्ण;

काष्ठा musb_hdrc_platक्रमm_data अणु
	/* MUSB_HOST, MUSB_PERIPHERAL, or MUSB_OTG */
	u8		mode;

	/* क्रम clk_get() */
	स्थिर अक्षर	*घड़ी;

	/* (HOST or OTG) चयन VBUS on/off */
	पूर्णांक		(*set_vbus)(काष्ठा device *dev, पूर्णांक is_on);

	/* (HOST or OTG) mA/2 घातer supplied on (शेष = 8mA) */
	u8		घातer;

	/* (PERIPHERAL) mA/2 max घातer consumed (शेष = 100mA) */
	u8		min_घातer;

	/* (HOST or OTG) msec/2 after VBUS on till घातer good */
	u8		potpgt;

	/* (HOST or OTG) program PHY क्रम बाह्यal Vbus */
	अचिन्हित	extvbus:1;

	/* Power the device on or off */
	पूर्णांक		(*set_घातer)(पूर्णांक state);

	/* MUSB configuration-specअगरic details */
	स्थिर काष्ठा musb_hdrc_config *config;

	/* Architecture specअगरic board data	*/
	व्योम		*board_data;

	/* Platक्रमm specअगरic काष्ठा musb_ops poपूर्णांकer */
	स्थिर व्योम	*platक्रमm_ops;
पूर्ण;

क्रमागत musb_vbus_id_status अणु
	MUSB_UNKNOWN = 0,
	MUSB_ID_GROUND,
	MUSB_ID_FLOAT,
	MUSB_VBUS_VALID,
	MUSB_VBUS_OFF,
पूर्ण;

#अगर IS_ENABLED(CONFIG_USB_MUSB_HDRC)
पूर्णांक musb_mailbox(क्रमागत musb_vbus_id_status status);
#अन्यथा
अटल अंतरभूत पूर्णांक musb_mailbox(क्रमागत musb_vbus_id_status status)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* TUSB 6010 support */

#घोषणा	TUSB6010_OSCCLK_60	16667	/* psec/clk @ 60.0 MHz */
#घोषणा	TUSB6010_REFCLK_24	41667	/* psec/clk @ 24.0 MHz XI */
#घोषणा	TUSB6010_REFCLK_19	52083	/* psec/clk @ 19.2 MHz CLKIN */

#अगर_घोषित	CONFIG_ARCH_OMAP2

बाह्य पूर्णांक __init tusb6010_setup_पूर्णांकerface(
		काष्ठा musb_hdrc_platक्रमm_data *data,
		अचिन्हित ps_refclk, अचिन्हित रुकोpin,
		अचिन्हित async_cs, अचिन्हित sync_cs,
		अचिन्हित irq, अचिन्हित dmachan);

बाह्य पूर्णांक tusb6010_platक्रमm_reसमय(अचिन्हित is_refclk);

#पूर्ण_अगर	/* OMAP2 */

#पूर्ण_अगर /* __LINUX_USB_MUSB_H */
