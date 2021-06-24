<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

/*
 * This is the Fusion MPT base driver providing common API layer पूर्णांकerface
 * to store diag trigger values पूर्णांकo persistent driver triggers pages
 * क्रम MPT (Message Passing Technology) based controllers.
 *
 * Copyright (C) 2020  Broadcom Inc.
 *
 * Authors: Broadcom Inc.
 * Sreekanth Reddy  <sreekanth.reddy@broadcom.com>
 *
 * Send feedback to : MPT-FusionLinux.pdl@broadcom.com)
 */

#समावेश "mpi/mpi2_cnfg.h"

#अगर_अघोषित MPI2_TRIGGER_PAGES_H
#घोषणा MPI2_TRIGGER_PAGES_H

#घोषणा MPI2_CONFIG_EXTPAGETYPE_DRIVER_PERSISTENT_TRIGGER    (0xE0)
#घोषणा MPI26_DRIVER_TRIGGER_PAGE0_PAGEVERSION               (0x01)
प्रकार काष्ठा _MPI26_CONFIG_PAGE_DRIVER_TIGGER_0 अणु
	MPI2_CONFIG_EXTENDED_PAGE_HEADER	Header;	/* 0x00  */
	U16	TriggerFlags;		/* 0x08  */
	U16	Reserved0xA;		/* 0x0A */
	U32	Reserved0xC[61];	/* 0x0C */
पूर्ण _MPI26_CONFIG_PAGE_DRIVER_TIGGER_0, Mpi26DriverTriggerPage0_t;

/* Trigger Flags */
#घोषणा  MPI26_DRIVER_TRIGGER0_FLAG_MASTER_TRIGGER_VALID       (0x0001)
#घोषणा  MPI26_DRIVER_TRIGGER0_FLAG_MPI_EVENT_TRIGGER_VALID    (0x0002)
#घोषणा  MPI26_DRIVER_TRIGGER0_FLAG_SCSI_SENSE_TRIGGER_VALID   (0x0004)
#घोषणा  MPI26_DRIVER_TRIGGER0_FLAG_LOGINFO_TRIGGER_VALID      (0x0008)

#घोषणा MPI26_DRIVER_TRIGGER_PAGE1_PAGEVERSION               (0x01)
प्रकार काष्ठा _MPI26_DRIVER_MASTER_TIGGER_ENTRY अणु
	U32	MasterTriggerFlags;
पूर्ण MPI26_DRIVER_MASTER_TIGGER_ENTRY;

#घोषणा MPI26_MAX_MASTER_TRIGGERS                                   (1)
प्रकार काष्ठा _MPI26_CONFIG_PAGE_DRIVER_TIGGER_1 अणु
	MPI2_CONFIG_EXTENDED_PAGE_HEADER	Header;	/* 0x00 */
	U16	NumMasterTrigger;	/* 0x08 */
	U16	Reserved0xA;		/* 0x0A */
	MPI26_DRIVER_MASTER_TIGGER_ENTRY MasterTriggers[MPI26_MAX_MASTER_TRIGGERS];	/* 0x0C */
पूर्ण MPI26_CONFIG_PAGE_DRIVER_TIGGER_1, Mpi26DriverTriggerPage1_t;

#घोषणा MPI26_DRIVER_TRIGGER_PAGE2_PAGEVERSION               (0x01)
प्रकार काष्ठा _MPI26_DRIVER_MPI_EVENT_TIGGER_ENTRY अणु
	U16	MPIEventCode;		/* 0x00 */
	U16	MPIEventCodeSpecअगरic;	/* 0x02 */
पूर्ण MPI26_DRIVER_MPI_EVENT_TIGGER_ENTRY;

#घोषणा MPI26_MAX_MPI_EVENT_TRIGGERS                            (20)
प्रकार काष्ठा _MPI26_CONFIG_PAGE_DRIVER_TIGGER_2 अणु
	MPI2_CONFIG_EXTENDED_PAGE_HEADER        Header;	/* 0x00  */
	U16	NumMPIEventTrigger;     /* 0x08  */
	U16	Reserved0xA;		/* 0x0A */
	MPI26_DRIVER_MPI_EVENT_TIGGER_ENTRY MPIEventTriggers[MPI26_MAX_MPI_EVENT_TRIGGERS]; /* 0x0C */
पूर्ण MPI26_CONFIG_PAGE_DRIVER_TIGGER_2, Mpi26DriverTriggerPage2_t;

#घोषणा MPI26_DRIVER_TRIGGER_PAGE3_PAGEVERSION               (0x01)
प्रकार काष्ठा _MPI26_DRIVER_SCSI_SENSE_TIGGER_ENTRY अणु
	U8     ASCQ;		/* 0x00 */
	U8     ASC;		/* 0x01 */
	U8     SenseKey;	/* 0x02 */
	U8     Reserved;	/* 0x03 */
पूर्ण MPI26_DRIVER_SCSI_SENSE_TIGGER_ENTRY;

#घोषणा MPI26_MAX_SCSI_SENSE_TRIGGERS                            (20)
प्रकार काष्ठा _MPI26_CONFIG_PAGE_DRIVER_TIGGER_3 अणु
	MPI2_CONFIG_EXTENDED_PAGE_HEADER	Header;	/* 0x00  */
	U16	NumSCSISenseTrigger;			/* 0x08  */
	U16	Reserved0xA;				/* 0x0A */
	MPI26_DRIVER_SCSI_SENSE_TIGGER_ENTRY SCSISenseTriggers[MPI26_MAX_SCSI_SENSE_TRIGGERS];	/* 0x0C */
पूर्ण MPI26_CONFIG_PAGE_DRIVER_TIGGER_3, Mpi26DriverTriggerPage3_t;

#घोषणा MPI26_DRIVER_TRIGGER_PAGE4_PAGEVERSION               (0x01)
प्रकार काष्ठा _MPI26_DRIVER_IOCSTATUS_LOGINFO_TIGGER_ENTRY अणु
	U16        IOCStatus;      /* 0x00 */
	U16        Reserved;       /* 0x02 */
	U32        LogInfo;        /* 0x04 */
पूर्ण MPI26_DRIVER_IOCSTATUS_LOGINFO_TIGGER_ENTRY;

#घोषणा MPI26_MAX_LOGINFO_TRIGGERS                            (20)
प्रकार काष्ठा _MPI26_CONFIG_PAGE_DRIVER_TIGGER_4 अणु
	MPI2_CONFIG_EXTENDED_PAGE_HEADER	Header;	/* 0x00  */
	U16	NumIOCStatusLogInfoTrigger;		/* 0x08  */
	U16	Reserved0xA;				/* 0x0A */
	MPI26_DRIVER_IOCSTATUS_LOGINFO_TIGGER_ENTRY IOCStatusLoginfoTriggers[MPI26_MAX_LOGINFO_TRIGGERS];	/* 0x0C */
पूर्ण MPI26_CONFIG_PAGE_DRIVER_TIGGER_4, Mpi26DriverTriggerPage4_t;

#पूर्ण_अगर
