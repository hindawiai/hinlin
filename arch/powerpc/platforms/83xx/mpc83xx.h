<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MPC83XX_H__
#घोषणा __MPC83XX_H__

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/pci-bridge.h>

/* System Clock Control Register */
#घोषणा MPC83XX_SCCR_OFFS          0xA08
#घोषणा MPC83XX_SCCR_USB_MASK      0x00f00000
#घोषणा MPC83XX_SCCR_USB_MPHCM_11  0x00c00000
#घोषणा MPC83XX_SCCR_USB_MPHCM_01  0x00400000
#घोषणा MPC83XX_SCCR_USB_MPHCM_10  0x00800000
#घोषणा MPC83XX_SCCR_USB_DRCM_11   0x00300000
#घोषणा MPC83XX_SCCR_USB_DRCM_01   0x00100000
#घोषणा MPC83XX_SCCR_USB_DRCM_10   0x00200000
#घोषणा MPC8315_SCCR_USB_MASK      0x00c00000
#घोषणा MPC8315_SCCR_USB_DRCM_11   0x00c00000
#घोषणा MPC8315_SCCR_USB_DRCM_01   0x00400000
#घोषणा MPC837X_SCCR_USB_DRCM_11   0x00c00000

/* प्रणाली i/o configuration रेजिस्टर low */
#घोषणा MPC83XX_SICRL_OFFS         0x114
#घोषणा MPC834X_SICRL_USB_MASK     0x60000000
#घोषणा MPC834X_SICRL_USB0         0x20000000
#घोषणा MPC834X_SICRL_USB1         0x40000000
#घोषणा MPC831X_SICRL_USB_MASK     0x00000c00
#घोषणा MPC831X_SICRL_USB_ULPI     0x00000800
#घोषणा MPC8315_SICRL_USB_MASK     0x000000fc
#घोषणा MPC8315_SICRL_USB_ULPI     0x00000054
#घोषणा MPC837X_SICRL_USB_MASK     0xf0000000
#घोषणा MPC837X_SICRL_USB_ULPI     0x50000000
#घोषणा MPC837X_SICRL_USBB_MASK    0x30000000
#घोषणा MPC837X_SICRL_SD           0x20000000

/* प्रणाली i/o configuration रेजिस्टर high */
#घोषणा MPC83XX_SICRH_OFFS         0x118
#घोषणा MPC8308_SICRH_USB_MASK     0x000c0000
#घोषणा MPC8308_SICRH_USB_ULPI     0x00040000
#घोषणा MPC834X_SICRH_USB_UTMI     0x00020000
#घोषणा MPC831X_SICRH_USB_MASK     0x000000e0
#घोषणा MPC831X_SICRH_USB_ULPI     0x000000a0
#घोषणा MPC8315_SICRH_USB_MASK     0x0000ff00
#घोषणा MPC8315_SICRH_USB_ULPI     0x00000000
#घोषणा MPC837X_SICRH_SPI_MASK     0x00000003
#घोषणा MPC837X_SICRH_SD           0x00000001

/* USB Control Register */
#घोषणा FSL_USB2_CONTROL_OFFS      0x500
#घोषणा CONTROL_UTMI_PHY_EN        0x00000200
#घोषणा CONTROL_REFSEL_24MHZ       0x00000040
#घोषणा CONTROL_REFSEL_48MHZ       0x00000080
#घोषणा CONTROL_PHY_CLK_SEL_ULPI   0x00000400
#घोषणा CONTROL_OTG_PORT           0x00000020

/* USB PORTSC Registers */
#घोषणा FSL_USB2_PORTSC1_OFFS      0x184
#घोषणा FSL_USB2_PORTSC2_OFFS      0x188
#घोषणा PORTSCX_PTW_16BIT          0x10000000
#घोषणा PORTSCX_PTS_UTMI           0x00000000
#घोषणा PORTSCX_PTS_ULPI           0x80000000

/*
 * Declaration क्रम the various functions exported by the
 * mpc83xx_* files. Mostly क्रम use by mpc83xx_setup
 */

बाह्य व्योम __noवापस mpc83xx_restart(अक्षर *cmd);
बाह्य दीर्घ mpc83xx_समय_init(व्योम);
बाह्य पूर्णांक mpc837x_usb_cfg(व्योम);
बाह्य पूर्णांक mpc834x_usb_cfg(व्योम);
बाह्य पूर्णांक mpc831x_usb_cfg(व्योम);
बाह्य व्योम mpc83xx_ipic_init_IRQ(व्योम);

#अगर_घोषित CONFIG_PCI
बाह्य व्योम mpc83xx_setup_pci(व्योम);
#अन्यथा
#घोषणा mpc83xx_setup_pci	शून्य
#पूर्ण_अगर

बाह्य पूर्णांक mpc83xx_declare_of_platक्रमm_devices(व्योम);
बाह्य व्योम mpc83xx_setup_arch(व्योम);

#पूर्ण_अगर				/* __MPC83XX_H__ */
