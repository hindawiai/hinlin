<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IDE_FLOPPY_H
#घोषणा __IDE_FLOPPY_H

#समावेश "ide-gd.h"

#अगर_घोषित CONFIG_IDE_GD_ATAPI
/*
 * Pages of the SELECT SENSE / MODE SENSE packet commands.
 * See SFF-8070i spec.
 */
#घोषणा	IDEFLOPPY_CAPABILITIES_PAGE	0x1b
#घोषणा IDEFLOPPY_FLEXIBLE_DISK_PAGE	0x05

/* IOCTLs used in low-level क्रमmatting. */
#घोषणा	IDEFLOPPY_IOCTL_FORMAT_SUPPORTED	0x4600
#घोषणा	IDEFLOPPY_IOCTL_FORMAT_GET_CAPACITY	0x4601
#घोषणा	IDEFLOPPY_IOCTL_FORMAT_START		0x4602
#घोषणा IDEFLOPPY_IOCTL_FORMAT_GET_PROGRESS	0x4603

/* ide-floppy.c */
बाह्य स्थिर काष्ठा ide_disk_ops ide_atapi_disk_ops;
व्योम ide_floppy_create_mode_sense_cmd(काष्ठा ide_atapi_pc *, u8);
व्योम ide_floppy_create_पढ़ो_capacity_cmd(काष्ठा ide_atapi_pc *);

/* ide-floppy_ioctl.c */
पूर्णांक ide_floppy_ioctl(ide_drive_t *, काष्ठा block_device *, भ_शेषe_t,
		     अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
पूर्णांक ide_floppy_compat_ioctl(ide_drive_t *, काष्ठा block_device *, भ_शेषe_t,
			    अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

#अगर_घोषित CONFIG_IDE_PROC_FS
/* ide-floppy_proc.c */
बाह्य ide_proc_entry_t ide_floppy_proc[];
बाह्य स्थिर काष्ठा ide_proc_devset ide_floppy_settings[];
#पूर्ण_अगर
#अन्यथा
#घोषणा ide_floppy_proc		शून्य
#घोषणा ide_floppy_settings	शून्य
#पूर्ण_अगर

#पूर्ण_अगर /*__IDE_FLOPPY_H */
