<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IDE_DISK_H
#घोषणा __IDE_DISK_H

#समावेश "ide-gd.h"

#अगर_घोषित CONFIG_IDE_GD_ATA
/* ide-disk.c */
बाह्य स्थिर काष्ठा ide_disk_ops ide_ata_disk_ops;
ide_decl_devset(address);
ide_decl_devset(multcount);
ide_decl_devset(nowerr);
ide_decl_devset(wcache);
ide_decl_devset(acoustic);

/* ide-disk_ioctl.c */
पूर्णांक ide_disk_ioctl(ide_drive_t *, काष्ठा block_device *, भ_शेषe_t, अचिन्हित पूर्णांक,
		   अचिन्हित दीर्घ);

#अगर_घोषित CONFIG_IDE_PROC_FS
/* ide-disk_proc.c */
बाह्य ide_proc_entry_t ide_disk_proc[];
बाह्य स्थिर काष्ठा ide_proc_devset ide_disk_settings[];
#पूर्ण_अगर
#अन्यथा
#घोषणा ide_disk_proc		शून्य
#घोषणा ide_disk_settings	शून्य
#पूर्ण_अगर

#पूर्ण_अगर /* __IDE_DISK_H */
