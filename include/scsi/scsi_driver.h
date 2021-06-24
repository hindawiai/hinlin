<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_SCSI_DRIVER_H
#घोषणा _SCSI_SCSI_DRIVER_H

#समावेश <linux/blk_types.h>
#समावेश <linux/device.h>

काष्ठा module;
काष्ठा request;
काष्ठा scsi_cmnd;
काष्ठा scsi_device;

काष्ठा scsi_driver अणु
	काष्ठा device_driver	gendrv;

	व्योम (*rescan)(काष्ठा device *);
	blk_status_t (*init_command)(काष्ठा scsi_cmnd *);
	व्योम (*uninit_command)(काष्ठा scsi_cmnd *);
	पूर्णांक (*करोne)(काष्ठा scsi_cmnd *);
	पूर्णांक (*eh_action)(काष्ठा scsi_cmnd *, पूर्णांक);
	व्योम (*eh_reset)(काष्ठा scsi_cmnd *);
पूर्ण;
#घोषणा to_scsi_driver(drv) \
	container_of((drv), काष्ठा scsi_driver, gendrv)

बाह्य पूर्णांक scsi_रेजिस्टर_driver(काष्ठा device_driver *);
#घोषणा scsi_unरेजिस्टर_driver(drv) \
	driver_unरेजिस्टर(drv);

बाह्य पूर्णांक scsi_रेजिस्टर_पूर्णांकerface(काष्ठा class_पूर्णांकerface *);
#घोषणा scsi_unरेजिस्टर_पूर्णांकerface(पूर्णांकf) \
	class_पूर्णांकerface_unरेजिस्टर(पूर्णांकf)

#पूर्ण_अगर /* _SCSI_SCSI_DRIVER_H */
