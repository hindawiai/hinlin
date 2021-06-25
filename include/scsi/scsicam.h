<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * scsicam.h - SCSI CAM support functions, use क्रम HDIO_GETGEO, etc.
 *
 * Copyright 1993, 1994 Drew Eckhardt
 *      Visionary Computing 
 *      (Unix and Linux consulting and custom programming)
 *      drew@Coloraकरो.EDU
 *	+1 (303) 786-7975
 *
 * For more inक्रमmation, please consult the SCSI-CAM draft.
 */

#अगर_अघोषित SCSICAM_H
#घोषणा SCSICAM_H
पूर्णांक scsicam_bios_param(काष्ठा block_device *bdev, sector_t capacity, पूर्णांक *ip);
bool scsi_partsize(काष्ठा block_device *bdev, sector_t capacity, पूर्णांक geom[3]);
अचिन्हित अक्षर *scsi_bios_ptable(काष्ठा block_device *bdev);
#पूर्ण_अगर /* def SCSICAM_H */
