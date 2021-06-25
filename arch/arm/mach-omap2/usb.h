<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/platक्रमm_data/usb-omap.h>

/* AM35x */
/* USB 2.0 PHY Control */
#घोषणा CONF2_PHY_GPIOMODE	(1 << 23)
#घोषणा CONF2_OTGMODE		(3 << 14)
#घोषणा CONF2_NO_OVERRIDE	(0 << 14)
#घोषणा CONF2_FORCE_HOST	(1 << 14)
#घोषणा CONF2_FORCE_DEVICE	(2 << 14)
#घोषणा CONF2_FORCE_HOST_VBUS_LOW (3 << 14)
#घोषणा CONF2_SESENDEN		(1 << 13)
#घोषणा CONF2_VBDTCTEN		(1 << 12)
#घोषणा CONF2_REFFREQ_24MHZ	(2 << 8)
#घोषणा CONF2_REFFREQ_26MHZ	(7 << 8)
#घोषणा CONF2_REFFREQ_13MHZ	(6 << 8)
#घोषणा CONF2_REFFREQ		(0xf << 8)
#घोषणा CONF2_PHYCLKGD		(1 << 7)
#घोषणा CONF2_VBUSSENSE		(1 << 6)
#घोषणा CONF2_PHY_PLLON		(1 << 5)
#घोषणा CONF2_RESET		(1 << 4)
#घोषणा CONF2_PHYPWRDN		(1 << 3)
#घोषणा CONF2_OTGPWRDN		(1 << 2)
#घोषणा CONF2_DATPOL		(1 << 1)

/* TI81XX specअगरic definitions */
#घोषणा USBCTRL0	0x620
#घोषणा USBSTAT0	0x624

/* TI816X PHY controls bits */
#घोषणा TI816X_USBPHY0_NORMAL_MODE	(1 << 0)
#घोषणा TI816X_USBPHY_REFCLK_OSC	(1 << 8)

/* TI814X PHY controls bits */
#घोषणा USBPHY_CM_PWRDN		(1 << 0)
#घोषणा USBPHY_OTG_PWRDN	(1 << 1)
#घोषणा USBPHY_CHGDET_DIS	(1 << 2)
#घोषणा USBPHY_CHGDET_RSTRT	(1 << 3)
#घोषणा USBPHY_SRCONDM		(1 << 4)
#घोषणा USBPHY_SINKONDP		(1 << 5)
#घोषणा USBPHY_CHGISINK_EN	(1 << 6)
#घोषणा USBPHY_CHGVSRC_EN	(1 << 7)
#घोषणा USBPHY_DMPULLUP		(1 << 8)
#घोषणा USBPHY_DPPULLUP		(1 << 9)
#घोषणा USBPHY_CDET_EXTCTL	(1 << 10)
#घोषणा USBPHY_GPIO_MODE	(1 << 12)
#घोषणा USBPHY_DPOPBUFCTL	(1 << 13)
#घोषणा USBPHY_DMOPBUFCTL	(1 << 14)
#घोषणा USBPHY_DPINPUT		(1 << 15)
#घोषणा USBPHY_DMINPUT		(1 << 16)
#घोषणा USBPHY_DPGPIO_PD	(1 << 17)
#घोषणा USBPHY_DMGPIO_PD	(1 << 18)
#घोषणा USBPHY_OTGVDET_EN	(1 << 19)
#घोषणा USBPHY_OTGSESSEND_EN	(1 << 20)
#घोषणा USBPHY_DATA_POLARITY	(1 << 23)

काष्ठा usbhs_phy_data अणु
	पूर्णांक port;		/* 1 indexed port number */
	पूर्णांक reset_gpio;
	पूर्णांक vcc_gpio;
	bool vcc_polarity;	/* 1 active high, 0 active low */
पूर्ण;

बाह्य व्योम usb_musb_init(काष्ठा omap_musb_board_data *board_data);
बाह्य व्योम usbhs_init(काष्ठा usbhs_omap_platक्रमm_data *pdata);
बाह्य पूर्णांक usbhs_init_phys(काष्ठा usbhs_phy_data *phy, पूर्णांक num_phys);

बाह्य व्योम am35x_musb_reset(व्योम);
बाह्य व्योम am35x_musb_phy_घातer(u8 on);
बाह्य व्योम am35x_musb_clear_irq(व्योम);
बाह्य व्योम am35x_set_mode(u8 musb_mode);
