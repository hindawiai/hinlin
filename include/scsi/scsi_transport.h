<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* 
 *  Transport specअगरic attributes.
 *
 *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.
 */
#अगर_अघोषित SCSI_TRANSPORT_H
#घोषणा SCSI_TRANSPORT_H

#समावेश <linux/transport_class.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bug.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>

काष्ठा scsi_transport_ढाँचा अणु
	/* the attribute containers */
	काष्ठा transport_container host_attrs;
	काष्ठा transport_container target_attrs;
	काष्ठा transport_container device_attrs;

	/*
	 * If set, called from sysfs and legacy procfs rescanning code.
	 */
	पूर्णांक (*user_scan)(काष्ठा Scsi_Host *, uपूर्णांक, uपूर्णांक, u64);

	/* The size of the specअगरic transport attribute काष्ठाure (a
	 * space of this size will be left at the end of the
	 * scsi_* काष्ठाure */
	पूर्णांक	device_size;
	पूर्णांक	device_निजी_offset;
	पूर्णांक	target_size;
	पूर्णांक	target_निजी_offset;
	पूर्णांक	host_size;
	/* no निजी offset क्रम the host; there's an alternative mechanism */

	/*
	 * True अगर the transport wants to use a host-based work-queue
	 */
	अचिन्हित पूर्णांक create_work_queue : 1;

	/*
	 * Allows a transport to override the शेष error handler.
	 */
	व्योम (* eh_strategy_handler)(काष्ठा Scsi_Host *);
पूर्ण;

#घोषणा transport_class_to_shost(tc) \
	dev_to_shost((tc)->parent)


/* Private area मुख्यtenance. The driver requested allocations come
 * directly after the transport class allocations (अगर any).  The idea
 * is that you *must* call these only once.  The code assumes that the
 * initial values are the ones the transport specअगरic code requires */
अटल अंतरभूत व्योम
scsi_transport_reserve_target(काष्ठा scsi_transport_ढाँचा * t, पूर्णांक space)
अणु
	BUG_ON(t->target_निजी_offset != 0);
	t->target_निजी_offset = ALIGN(t->target_size, माप(व्योम *));
	t->target_size = t->target_निजी_offset + space;
पूर्ण
अटल अंतरभूत व्योम
scsi_transport_reserve_device(काष्ठा scsi_transport_ढाँचा * t, पूर्णांक space)
अणु
	BUG_ON(t->device_निजी_offset != 0);
	t->device_निजी_offset = ALIGN(t->device_size, माप(व्योम *));
	t->device_size = t->device_निजी_offset + space;
पूर्ण
अटल अंतरभूत व्योम *
scsi_transport_target_data(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	वापस (u8 *)starget->starget_data
		+ shost->transportt->target_निजी_offset;

पूर्ण
अटल अंतरभूत व्योम *
scsi_transport_device_data(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	वापस (u8 *)sdev->sdev_data
		+ shost->transportt->device_निजी_offset;
पूर्ण

व्योम __scsi_init_queue(काष्ठा Scsi_Host *shost, काष्ठा request_queue *q);

#पूर्ण_अगर /* SCSI_TRANSPORT_H */
