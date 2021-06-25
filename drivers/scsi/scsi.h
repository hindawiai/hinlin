<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  scsi.h Copyright (C) 1992 Drew Eckhardt 
 *         Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale
 *  generic SCSI package header file by
 *      Initial versions: Drew Eckhardt
 *      Subsequent revisions: Eric Youngdale
 *
 *  <drew@coloraकरो.edu>
 *
 *       Modअगरied by Eric Youngdale eric@andante.org to
 *       add scatter-gather, multiple outstanding request, and other
 *       enhancements.
 */
/*
 * NOTE:  this file only contains compatibility glue क्रम old drivers.  All
 * these wrappers will be हटाओd sooner or later.  For new code please use
 * the पूर्णांकerfaces declared in the headers in include/scsi/
 */

#अगर_अघोषित _SCSI_H
#घोषणा _SCSI_H

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi.h>

/*
 * Some defs, in हाल these are not defined अन्यथाwhere.
 */
#अगर_अघोषित TRUE
#घोषणा TRUE 1
#पूर्ण_अगर
#अगर_अघोषित FALSE
#घोषणा FALSE 0
#पूर्ण_अगर

काष्ठा Scsi_Host;
काष्ठा scsi_cmnd;
काष्ठा scsi_device;
काष्ठा scsi_target;
काष्ठा scatterlist;

#पूर्ण_अगर /* _SCSI_H */
