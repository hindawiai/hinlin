<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_REBOOT_H
#घोषणा _UAPI_LINUX_REBOOT_H

/*
 * Magic values required to use _reboot() प्रणाली call.
 */

#घोषणा	LINUX_REBOOT_MAGIC1	0xfee1dead
#घोषणा	LINUX_REBOOT_MAGIC2	672274793
#घोषणा	LINUX_REBOOT_MAGIC2A	85072278
#घोषणा	LINUX_REBOOT_MAGIC2B	369367448
#घोषणा	LINUX_REBOOT_MAGIC2C	537993216


/*
 * Commands accepted by the _reboot() प्रणाली call.
 *
 * RESTART     Restart प्रणाली using शेष command and mode.
 * HALT        Stop OS and give प्रणाली control to ROM monitor, अगर any.
 * CAD_ON      Ctrl-Alt-Del sequence causes RESTART command.
 * CAD_OFF     Ctrl-Alt-Del sequence sends संक_विघ्न to init task.
 * POWER_OFF   Stop OS and हटाओ all घातer from प्रणाली, अगर possible.
 * RESTART2    Restart प्रणाली using given command string.
 * SW_SUSPEND  Suspend प्रणाली using software suspend अगर compiled in.
 * KEXEC       Restart प्रणाली using a previously loaded Linux kernel
 */

#घोषणा	LINUX_REBOOT_CMD_RESTART	0x01234567
#घोषणा	LINUX_REBOOT_CMD_HALT		0xCDEF0123
#घोषणा	LINUX_REBOOT_CMD_CAD_ON		0x89ABCDEF
#घोषणा	LINUX_REBOOT_CMD_CAD_OFF	0x00000000
#घोषणा	LINUX_REBOOT_CMD_POWER_OFF	0x4321FEDC
#घोषणा	LINUX_REBOOT_CMD_RESTART2	0xA1B2C3D4
#घोषणा	LINUX_REBOOT_CMD_SW_SUSPEND	0xD000FCE2
#घोषणा	LINUX_REBOOT_CMD_KEXEC		0x45584543



#पूर्ण_अगर /* _UAPI_LINUX_REBOOT_H */
