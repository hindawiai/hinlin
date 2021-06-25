<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Renesas USB
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Copyright (C) 2019 Renesas Electronics Corporation
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA  02110-1301  USA
 *
 */
#अगर_अघोषित RENESAS_USB_H
#घोषणा RENESAS_USB_H
#समावेश <linux/notअगरier.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/ch9.h>

/*
 * module type
 *
 * it will be वापस value from get_id
 */
क्रमागत अणु
	USBHS_HOST = 0,
	USBHS_GADGET,
	USBHS_MAX,
पूर्ण;

/*
 * callback functions क्रम platक्रमm
 *
 * These functions are called from driver क्रम platक्रमm
 */
काष्ठा renesas_usbhs_platक्रमm_callback अणु

	/*
	 * option:
	 *
	 * Hardware init function क्रम platक्रमm.
	 * it is called when driver was probed.
	 */
	पूर्णांक (*hardware_init)(काष्ठा platक्रमm_device *pdev);

	/*
	 * option:
	 *
	 * Hardware निकास function क्रम platक्रमm.
	 * it is called when driver was हटाओd
	 */
	पूर्णांक (*hardware_निकास)(काष्ठा platक्रमm_device *pdev);

	/*
	 * option:
	 *
	 * क्रम board specअगरic घड़ी control
	 */
	पूर्णांक (*घातer_ctrl)(काष्ठा platक्रमm_device *pdev,
			   व्योम __iomem *base, पूर्णांक enable);

	/*
	 * option:
	 *
	 * Phy reset क्रम platक्रमm
	 */
	पूर्णांक (*phy_reset)(काष्ठा platक्रमm_device *pdev);

	/*
	 * get USB ID function
	 *  - USBHS_HOST
	 *  - USBHS_GADGET
	 */
	पूर्णांक (*get_id)(काष्ठा platक्रमm_device *pdev);

	/*
	 * get VBUS status function.
	 */
	पूर्णांक (*get_vbus)(काष्ठा platक्रमm_device *pdev);

	/*
	 * option:
	 *
	 * VBUS control is needed क्रम Host
	 */
	पूर्णांक (*set_vbus)(काष्ठा platक्रमm_device *pdev, पूर्णांक enable);

	/*
	 * option:
	 * extcon notअगरier to set host/peripheral mode.
	 */
	पूर्णांक (*notअगरier)(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			व्योम *data);
पूर्ण;

/*
 * parameters क्रम renesas usbhs
 *
 * some रेजिस्टर needs USB chip specअगरic parameters.
 * This काष्ठा show it to driver
 */

काष्ठा renesas_usbhs_driver_pipe_config अणु
	u8 type;	/* USB_ENDPOINT_XFER_xxx */
	u16 bufsize;
	u8 bufnum;
	bool द्विगुन_buf;
पूर्ण;
#घोषणा RENESAS_USBHS_PIPE(_type, _size, _num, _द्विगुन_buf)	अणु	\
			.type = (_type),		\
			.bufsize = (_size),		\
			.bufnum = (_num),		\
			.द्विगुन_buf = (_द्विगुन_buf),	\
	पूर्ण

काष्ठा renesas_usbhs_driver_param अणु
	/*
	 * pipe settings
	 */
	काष्ठा renesas_usbhs_driver_pipe_config *pipe_configs;
	पूर्णांक pipe_size; /* pipe_configs array size */

	/*
	 * option:
	 *
	 * क्रम BUSWAIT :: BWAIT
	 * see
	 *	renesas_usbhs/common.c :: usbhsc_set_busरुको()
	 * */
	पूर्णांक busरुको_bरुको;

	/*
	 * option:
	 *
	 * delay समय from notअगरy_hotplug callback
	 */
	पूर्णांक detection_delay; /* msec */

	/*
	 * option:
	 *
	 * dma id क्रम dmaengine
	 * The data transfer direction on D0FIFO/D1FIFO should be
	 * fixed क्रम keeping consistency.
	 * So, the platक्रमm id settings will be..
	 *	.d0_tx_id = xx_TX,
	 *	.d1_rx_id = xx_RX,
	 * or
	 *	.d1_tx_id = xx_TX,
	 *	.d0_rx_id = xx_RX,
	 */
	पूर्णांक d0_tx_id;
	पूर्णांक d0_rx_id;
	पूर्णांक d1_tx_id;
	पूर्णांक d1_rx_id;
	पूर्णांक d2_tx_id;
	पूर्णांक d2_rx_id;
	पूर्णांक d3_tx_id;
	पूर्णांक d3_rx_id;

	/*
	 * option:
	 *
	 * pio <--> dma border.
	 */
	पूर्णांक pio_dma_border; /* शेष is 64byte */

	/*
	 * option:
	 */
	u32 has_usb_dmac:1; /* क्रम USB-DMAC */
	u32 runसमय_pwctrl:1;
	u32 has_cnen:1;
	u32 cfअगरo_byte_addr:1; /* CFIFO is byte addressable */
#घोषणा USBHS_USB_DMAC_XFER_SIZE	32	/* hardcode the xfer size */
	u32 multi_clks:1;
	u32 has_new_pipe_configs:1;
पूर्ण;

/*
 * option:
 *
 * platक्रमm inक्रमmation क्रम renesas_usbhs driver.
 */
काष्ठा renesas_usbhs_platक्रमm_info अणु
	/*
	 * option:
	 *
	 * platक्रमm set these functions beक्रमe
	 * call platक्रमm_add_devices अगर needed
	 */
	काष्ठा renesas_usbhs_platक्रमm_callback	platक्रमm_callback;

	/*
	 * option:
	 *
	 * driver use these param क्रम some रेजिस्टर
	 */
	काष्ठा renesas_usbhs_driver_param	driver_param;
पूर्ण;

/*
 * macro क्रम platक्रमm
 */
#घोषणा renesas_usbhs_get_info(pdev)\
	((काष्ठा renesas_usbhs_platक्रमm_info *)(pdev)->dev.platक्रमm_data)
#पूर्ण_अगर /* RENESAS_USB_H */
