<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MISCDEVICE_H
#घोषणा _LINUX_MISCDEVICE_H
#समावेश <linux/major.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>

/*
 *	These allocations are managed by device@lanana.org. If you need
 *	an entry that is not asचिन्हित here, it can be moved and
 *	reasचिन्हित or dynamically set अगर a fixed value is not justअगरied.
 */

#घोषणा PSMOUSE_MINOR		1
#घोषणा MS_BUSMOUSE_MINOR	2	/* unused */
#घोषणा ATIXL_BUSMOUSE_MINOR	3	/* unused */
/*#घोषणा AMIGAMOUSE_MINOR	4	FIXME OBSOLETE */
#घोषणा ATARIMOUSE_MINOR	5	/* unused */
#घोषणा SUN_MOUSE_MINOR		6	/* unused */
#घोषणा APOLLO_MOUSE_MINOR	7	/* unused */
#घोषणा PC110PAD_MINOR		9	/* unused */
/*#घोषणा ADB_MOUSE_MINOR	10	FIXME OBSOLETE */
#घोषणा WATCHDOG_MINOR		130	/* Watchकरोg समयr     */
#घोषणा TEMP_MINOR		131	/* Temperature Sensor */
#घोषणा APM_MINOR_DEV		134
#घोषणा RTC_MINOR		135
/*#घोषणा EFI_RTC_MINOR		136	was EFI Time services */
#घोषणा VHCI_MINOR		137
#घोषणा SUN_OPENPROM_MINOR	139
#घोषणा DMAPI_MINOR		140	/* unused */
#घोषणा NVRAM_MINOR		144
#घोषणा SBUS_FLASH_MINOR	152
#घोषणा SGI_MMTIMER		153
#घोषणा PMU_MINOR		154
#घोषणा STORE_QUEUE_MINOR	155	/* unused */
#घोषणा LCD_MINOR		156
#घोषणा AC_MINOR		157
#घोषणा BUTTON_MINOR		158	/* Major 10, Minor 158, /dev/nwbutton */
#घोषणा NWFLASH_MINOR		160	/* MAJOR is 10 - miscdevice */
#घोषणा ENVCTRL_MINOR		162
#घोषणा I2O_MINOR		166
#घोषणा UCTRL_MINOR		174
#घोषणा AGPGART_MINOR		175
#घोषणा TOSH_MINOR_DEV		181
#घोषणा HWRNG_MINOR		183
#घोषणा MICROCODE_MINOR		184
#घोषणा KEYPAD_MINOR		185
#घोषणा IRNET_MINOR		187
#घोषणा D7S_MINOR		193
#घोषणा VFIO_MINOR		196
#घोषणा PXA3XX_GCU_MINOR	197
#घोषणा TUN_MINOR		200
#घोषणा CUSE_MINOR		203
#घोषणा MWAVE_MINOR		219	/* ACP/Mwave Modem */
#घोषणा MPT_MINOR		220
#घोषणा MPT2SAS_MINOR		221
#घोषणा MPT3SAS_MINOR		222
#घोषणा UINPUT_MINOR		223
#घोषणा MISC_MCELOG_MINOR	227
#घोषणा HPET_MINOR		228
#घोषणा FUSE_MINOR		229
#घोषणा SNAPSHOT_MINOR		231
#घोषणा KVM_MINOR		232
#घोषणा BTRFS_MINOR		234
#घोषणा AUTOFS_MINOR		235
#घोषणा MAPPER_CTRL_MINOR	236
#घोषणा LOOP_CTRL_MINOR		237
#घोषणा VHOST_NET_MINOR		238
#घोषणा UHID_MINOR		239
#घोषणा USERIO_MINOR		240
#घोषणा VHOST_VSOCK_MINOR	241
#घोषणा RFKILL_MINOR		242
#घोषणा MISC_DYNAMIC_MINOR	255

काष्ठा device;
काष्ठा attribute_group;

काष्ठा miscdevice  अणु
	पूर्णांक minor;
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations *fops;
	काष्ठा list_head list;
	काष्ठा device *parent;
	काष्ठा device *this_device;
	स्थिर काष्ठा attribute_group **groups;
	स्थिर अक्षर *nodename;
	umode_t mode;
पूर्ण;

बाह्य पूर्णांक misc_रेजिस्टर(काष्ठा miscdevice *misc);
बाह्य व्योम misc_deरेजिस्टर(काष्ठा miscdevice *misc);

/*
 * Helper macro क्रम drivers that करोn't करो anything special in the initcall.
 * This helps to eliminate boilerplate code.
 */
#घोषणा builtin_misc_device(__misc_device) \
	builtin_driver(__misc_device, misc_रेजिस्टर)

/*
 * Helper macro क्रम drivers that करोn't करो anything special in module init / निकास
 * call. This helps to eliminate boilerplate code.
 */
#घोषणा module_misc_device(__misc_device) \
	module_driver(__misc_device, misc_रेजिस्टर, misc_deरेजिस्टर)

#घोषणा MODULE_ALIAS_MISCDEV(minor)				\
	MODULE_ALIAS("char-major-" __stringअगरy(MISC_MAJOR)	\
	"-" __stringअगरy(minor))
#पूर्ण_अगर
