<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Interface क्रम Surface ACPI Notअगरy (SAN) driver.
 *
 * Provides access to discrete GPU notअगरications sent from ACPI via the SAN
 * driver, which are not handled by this driver directly.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _LINUX_SURFACE_ACPI_NOTIFY_H
#घोषणा _LINUX_SURFACE_ACPI_NOTIFY_H

#समावेश <linux/notअगरier.h>
#समावेश <linux/types.h>

/**
 * काष्ठा san_dgpu_event - Discrete GPU ACPI event.
 * @category: Category of the event.
 * @target:   Target ID of the event source.
 * @command:  Command ID of the event.
 * @instance: Instance ID of the event source.
 * @length:   Length of the event's payload data (in bytes).
 * @payload:  Poपूर्णांकer to the event's payload data.
 */
काष्ठा san_dgpu_event अणु
	u8 category;
	u8 target;
	u8 command;
	u8 instance;
	u16 length;
	u8 *payload;
पूर्ण;

पूर्णांक san_client_link(काष्ठा device *client);
पूर्णांक san_dgpu_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb);
पूर्णांक san_dgpu_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb);

#पूर्ण_अगर /* _LINUX_SURFACE_ACPI_NOTIFY_H */
