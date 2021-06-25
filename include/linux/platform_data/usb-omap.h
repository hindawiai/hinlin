<शैली गुरु>
/*
 * usb-omap.h - Platक्रमm data क्रम the various OMAP USB IPs
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 2, as published by the Free Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा OMAP3_HS_USB_PORTS	3

क्रमागत usbhs_omap_port_mode अणु
	OMAP_USBHS_PORT_MODE_UNUSED,
	OMAP_EHCI_PORT_MODE_PHY,
	OMAP_EHCI_PORT_MODE_TLL,
	OMAP_EHCI_PORT_MODE_HSIC,
	OMAP_OHCI_PORT_MODE_PHY_6PIN_DATSE0,
	OMAP_OHCI_PORT_MODE_PHY_6PIN_DPDM,
	OMAP_OHCI_PORT_MODE_PHY_3PIN_DATSE0,
	OMAP_OHCI_PORT_MODE_PHY_4PIN_DPDM,
	OMAP_OHCI_PORT_MODE_TLL_6PIN_DATSE0,
	OMAP_OHCI_PORT_MODE_TLL_6PIN_DPDM,
	OMAP_OHCI_PORT_MODE_TLL_3PIN_DATSE0,
	OMAP_OHCI_PORT_MODE_TLL_4PIN_DPDM,
	OMAP_OHCI_PORT_MODE_TLL_2PIN_DATSE0,
	OMAP_OHCI_PORT_MODE_TLL_2PIN_DPDM
पूर्ण;

काष्ठा usbtll_omap_platक्रमm_data अणु
	क्रमागत usbhs_omap_port_mode		port_mode[OMAP3_HS_USB_PORTS];
पूर्ण;

काष्ठा ehci_hcd_omap_platक्रमm_data अणु
	क्रमागत usbhs_omap_port_mode	port_mode[OMAP3_HS_USB_PORTS];
	पूर्णांक				reset_gpio_port[OMAP3_HS_USB_PORTS];
	काष्ठा regulator		*regulator[OMAP3_HS_USB_PORTS];
	अचिन्हित			phy_reset:1;
पूर्ण;

काष्ठा ohci_hcd_omap_platक्रमm_data अणु
	क्रमागत usbhs_omap_port_mode	port_mode[OMAP3_HS_USB_PORTS];
	अचिन्हित			es2_compatibility:1;
पूर्ण;

काष्ठा usbhs_omap_platक्रमm_data अणु
	पूर्णांक				nports;
	क्रमागत usbhs_omap_port_mode	port_mode[OMAP3_HS_USB_PORTS];
	पूर्णांक				reset_gpio_port[OMAP3_HS_USB_PORTS];
	काष्ठा regulator		*regulator[OMAP3_HS_USB_PORTS];

	काष्ठा ehci_hcd_omap_platक्रमm_data	*ehci_data;
	काष्ठा ohci_hcd_omap_platक्रमm_data	*ohci_data;

	/* OMAP3 <= ES2.1 have a single ulpi bypass control bit */
	अचिन्हित single_ulpi_bypass:1;
	अचिन्हित es2_compatibility:1;
	अचिन्हित phy_reset:1;
पूर्ण;

/*-------------------------------------------------------------------------*/

काष्ठा omap_musb_board_data अणु
	u8	पूर्णांकerface_type;
	u8	mode;
	u16	घातer;
	अचिन्हित extvbus:1;
	व्योम	(*set_phy_घातer)(u8 on);
	व्योम	(*clear_irq)(व्योम);
	व्योम	(*set_mode)(u8 mode);
	व्योम	(*reset)(व्योम);
पूर्ण;

क्रमागत musb_पूर्णांकerface अणु
	MUSB_INTERFACE_ULPI,
	MUSB_INTERFACE_UTMI
पूर्ण;
