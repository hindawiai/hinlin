<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XEN_PLATFORM_PCI_H
#घोषणा _XEN_PLATFORM_PCI_H

#घोषणा XEN_IOPORT_MAGIC_VAL 0x49d2
#घोषणा XEN_IOPORT_LINUX_PRODNUM 0x0003
#घोषणा XEN_IOPORT_LINUX_DRVVER  0x0001

#घोषणा XEN_IOPORT_BASE 0x10

#घोषणा XEN_IOPORT_PLATFLAGS	(XEN_IOPORT_BASE + 0) /* 1 byte access (R/W) */
#घोषणा XEN_IOPORT_MAGIC	(XEN_IOPORT_BASE + 0) /* 2 byte access (R) */
#घोषणा XEN_IOPORT_UNPLUG	(XEN_IOPORT_BASE + 0) /* 2 byte access (W) */
#घोषणा XEN_IOPORT_DRVVER	(XEN_IOPORT_BASE + 0) /* 4 byte access (W) */

#घोषणा XEN_IOPORT_SYSLOG	(XEN_IOPORT_BASE + 2) /* 1 byte access (W) */
#घोषणा XEN_IOPORT_PROTOVER	(XEN_IOPORT_BASE + 2) /* 1 byte access (R) */
#घोषणा XEN_IOPORT_PRODNUM	(XEN_IOPORT_BASE + 2) /* 2 byte access (W) */

#घोषणा XEN_UNPLUG_ALL_IDE_DISKS	(1<<0)
#घोषणा XEN_UNPLUG_ALL_NICS		(1<<1)
#घोषणा XEN_UNPLUG_AUX_IDE_DISKS	(1<<2)
#घोषणा XEN_UNPLUG_ALL			(XEN_UNPLUG_ALL_IDE_DISKS|\
					 XEN_UNPLUG_ALL_NICS|\
					 XEN_UNPLUG_AUX_IDE_DISKS)

#घोषणा XEN_UNPLUG_UNNECESSARY 		(1<<16)
#घोषणा XEN_UNPLUG_NEVER	 		(1<<17)

अटल अंतरभूत पूर्णांक xen_must_unplug_nics(व्योम) अणु
#अगर (defined(CONFIG_XEN_NETDEV_FRONTEND) || \
		defined(CONFIG_XEN_NETDEV_FRONTEND_MODULE)) && \
		defined(CONFIG_XEN_PVHVM)
        वापस 1;
#अन्यथा
        वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक xen_must_unplug_disks(व्योम) अणु
#अगर (defined(CONFIG_XEN_BLKDEV_FRONTEND) || \
		defined(CONFIG_XEN_BLKDEV_FRONTEND_MODULE)) && \
		defined(CONFIG_XEN_PVHVM)
        वापस 1;
#अन्यथा
        वापस 0;
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_XEN_PVHVM)
बाह्य bool xen_has_pv_devices(व्योम);
बाह्य bool xen_has_pv_disk_devices(व्योम);
बाह्य bool xen_has_pv_nic_devices(व्योम);
बाह्य bool xen_has_pv_and_legacy_disk_devices(व्योम);
#अन्यथा
अटल अंतरभूत bool xen_has_pv_devices(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_XEN);
पूर्ण
अटल अंतरभूत bool xen_has_pv_disk_devices(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_XEN);
पूर्ण
अटल अंतरभूत bool xen_has_pv_nic_devices(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_XEN);
पूर्ण
अटल अंतरभूत bool xen_has_pv_and_legacy_disk_devices(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _XEN_PLATFORM_PCI_H */
