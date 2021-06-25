<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_ISC_H
#घोषणा _ASM_S390_ISC_H

#समावेश <linux/types.h>

/*
 * I/O पूर्णांकerruption subclasses used by drivers.
 * Please add all used iscs here so that it is possible to distribute
 * isc usage between drivers.
 * Reminder: 0 is highest priority, 7 lowest.
 */
#घोषणा MAX_ISC 7

/* Regular I/O पूर्णांकerrupts. */
#घोषणा IO_SCH_ISC 3			/* regular I/O subchannels */
#घोषणा CONSOLE_ISC 1			/* console I/O subchannel */
#घोषणा EADM_SCH_ISC 4			/* EADM subchannels */
#घोषणा CHSC_SCH_ISC 7			/* CHSC subchannels */
#घोषणा VFIO_CCW_ISC IO_SCH_ISC		/* VFIO-CCW I/O subchannels */
/* Adapter पूर्णांकerrupts. */
#घोषणा QDIO_AIRQ_ISC IO_SCH_ISC	/* I/O subchannel in qdio mode */
#घोषणा PCI_ISC 2			/* PCI I/O subchannels */
#घोषणा GAL_ISC 5			/* GIB alert */
#घोषणा AP_ISC 6			/* adjunct processor (crypto) devices */

/* Functions क्रम registration of I/O पूर्णांकerruption subclasses */
व्योम isc_रेजिस्टर(अचिन्हित पूर्णांक isc);
व्योम isc_unरेजिस्टर(अचिन्हित पूर्णांक isc);

#पूर्ण_अगर /* _ASM_S390_ISC_H */
