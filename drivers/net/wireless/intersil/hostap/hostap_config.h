<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित HOSTAP_CONFIG_H
#घोषणा HOSTAP_CONFIG_H

/* In the previous versions of Host AP driver, support क्रम user space version
 * of IEEE 802.11 management (hostapd) used to be disabled in the शेष
 * configuration. From now on, support क्रम hostapd is always included and it is
 * possible to disable kernel driver version of IEEE 802.11 management with a
 * separate define, PRISM2_NO_KERNEL_IEEE80211_MGMT. */
/* #घोषणा PRISM2_NO_KERNEL_IEEE80211_MGMT */

/* Maximum number of events handler per one पूर्णांकerrupt */
#घोषणा PRISM2_MAX_INTERRUPT_EVENTS 20

/* Include code क्रम करोwnloading firmware images पूर्णांकo अस्थिर RAM. */
#घोषणा PRISM2_DOWNLOAD_SUPPORT

/* Allow kernel configuration to enable करोwnload support. */
#अगर !defined(PRISM2_DOWNLOAD_SUPPORT) && defined(CONFIG_HOSTAP_FIRMWARE)
#घोषणा PRISM2_DOWNLOAD_SUPPORT
#पूर्ण_अगर

/* Allow kernel configuration to enable non-अस्थिर करोwnload support. */
#अगर_घोषित CONFIG_HOSTAP_FIRMWARE_NVRAM
#घोषणा PRISM2_NON_VOLATILE_DOWNLOAD
#पूर्ण_अगर

/* Save low-level I/O क्रम debugging. This should not be enabled in normal use.
 */
/* #घोषणा PRISM2_IO_DEBUG */

/* Following defines can be used to हटाओ unneeded parts of the driver, e.g.,
 * to limit the size of the kernel module. Definitions can be added here in
 * hostap_config.h or they can be added to make command with ccflags-y,
 * e.g.,
 * 'make pccard ccflags-y="-DPRISM2_NO_DEBUG -DPRISM2_NO_PROCFS_DEBUG"'
 */

/* Do not include debug messages पूर्णांकo the driver */
/* #घोषणा PRISM2_NO_DEBUG */

/* Do not include /proc/net/prism2/wlan#/अणुरेजिस्टरs,debugपूर्ण */
/* #घोषणा PRISM2_NO_PROCFS_DEBUG */

/* Do not include station functionality (i.e., allow only Master (Host AP) mode
 */
/* #घोषणा PRISM2_NO_STATION_MODES */

#पूर्ण_अगर /* HOSTAP_CONFIG_H */
