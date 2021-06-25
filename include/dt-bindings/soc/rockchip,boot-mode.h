<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ROCKCHIP_BOOT_MODE_H
#घोषणा __ROCKCHIP_BOOT_MODE_H

/*high 24 bits is tag, low 8 bits is type*/
#घोषणा REBOOT_FLAG		0x5242C300
/* normal boot */
#घोषणा BOOT_NORMAL		(REBOOT_FLAG + 0)
/* enter bootloader rockusb mode */
#घोषणा BOOT_BL_DOWNLOAD	(REBOOT_FLAG + 1)
/* enter recovery */
#घोषणा BOOT_RECOVERY		(REBOOT_FLAG + 3)
 /* enter fastboot mode */
#घोषणा BOOT_FASTBOOT		(REBOOT_FLAG + 9)

#पूर्ण_अगर
