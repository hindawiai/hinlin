<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
   The compile-समय configurable शेषs क्रम the Linux SCSI tape driver.

   Copyright 1995-2003 Kai Makisara.

   Last modअगरied: Thu Feb 21 21:47:07 2008 by kai.makisara
*/

#अगर_अघोषित _ST_OPTIONS_H
#घोषणा _ST_OPTIONS_H

/* If TRY_सूचीECT_IO is non-zero, the driver tries to transfer data directly
   between the user buffer and tape drive. If this is not possible, driver
   buffer is used. If TRY_सूचीECT_IO is zero, driver buffer is always used. */
#घोषणा TRY_सूचीECT_IO 1

/* The driver करोes not रुको क्रम some operations to finish beक्रमe वापसing
   to the user program अगर ST_NOWAIT is non-zero. This helps अगर the SCSI
   adapter करोes not support multiple outstanding commands. However, the user
   should not give a new tape command beक्रमe the previous one has finished. */
#घोषणा ST_NOWAIT 0

/* If ST_IN_खाता_POS is nonzero, the driver positions the tape after the
   record been पढ़ो by the user program even अगर the tape has moved further
   because of buffered पढ़ोs. Should be set to zero to support also drives
   that can't space backwards over records. NOTE: The tape will be
   spaced backwards over an "accidentally" crossed filemark in any हाल. */
#घोषणा ST_IN_खाता_POS 0

/* If ST_RECOVERED_WRITE_FATAL is non-zero, recovered errors जबतक writing
   are considered "hard errors". */
#घोषणा ST_RECOVERED_WRITE_FATAL 0

/* The "guess" क्रम the block size क्रम devices that करोn't support MODE
   SENSE. */
#घोषणा ST_DEFAULT_BLOCK 0

/* The minimum tape driver buffer size in kilobytes in fixed block mode.
   Must be non-zero. */
#घोषणा ST_FIXED_BUFFER_BLOCKS 32

/* Maximum number of scatter/gather segments */
#घोषणा ST_MAX_SG      256

/* The number of scatter/gather segments to allocate at first try (must be
   smaller or equal to the maximum). */
#घोषणा ST_FIRST_SG    8

/* The size of the first scatter/gather segments (determines the maximum block
   size क्रम SCSI adapters not supporting scatter/gather). The शेष is set
   to try to allocate the buffer as one chunk. */
#घोषणा ST_FIRST_ORDER  5


/* The following lines define शेषs क्रम properties that can be set
   separately क्रम each drive using the MTSTOPTIONS ioctl. */

/* If ST_TWO_FM is non-zero, the driver ग_लिखोs two filemarks after a
   file being written. Some drives can't handle two filemarks at the
   end of data. */
#घोषणा ST_TWO_FM 0

/* If ST_BUFFER_WRITES is non-zero, ग_लिखोs in fixed block mode are
   buffered until the driver buffer is full or asynchronous ग_लिखो is
   triggered. May make detection of End-Of-Medium early enough fail. */
#घोषणा ST_BUFFER_WRITES 1

/* If ST_ASYNC_WRITES is non-zero, the SCSI ग_लिखो command may be started
   without रुकोing क्रम it to finish. May cause problems in multiple
   tape backups. */
#घोषणा ST_ASYNC_WRITES 1

/* If ST_READ_AHEAD is non-zero, blocks are पढ़ो ahead in fixed block
   mode. */
#घोषणा ST_READ_AHEAD 1

/* If ST_AUTO_LOCK is non-zero, the drive करोor is locked at the first
   पढ़ो or ग_लिखो command after the device is खोलोed. The करोor is खोलोed
   when the device is बंदd. */
#घोषणा ST_AUTO_LOCK 0

/* If ST_FAST_MTEOM is non-zero, the MTEOM ioctl is करोne using the
   direct SCSI command. The file number status is lost but this method
   is fast with some drives. Otherwise MTEOM is करोne by spacing over
   files and the file number status is retained. */
#घोषणा ST_FAST_MTEOM 0

/* If ST_SCSI2LOGICAL is nonzero, the logical block addresses are used क्रम
   MTIOCPOS and MTSEEK by शेष. Venकरोr addresses are used अगर ST_SCSI2LOGICAL
   is zero. */
#घोषणा ST_SCSI2LOGICAL 0

/* If ST_SYSV is non-zero, the tape behaves according to the SYS V semantics.
   The शेष is BSD semantics. */
#घोषणा ST_SYSV 0

/* If ST_SILI is non-zero, the SILI bit is set when पढ़ोing in variable block
   mode and the block size is determined using the residual वापसed by the HBA. */
#घोषणा ST_SILI 0

/* Time to रुको क्रम the drive to become पढ़ोy अगर blocking खोलो */
#घोषणा ST_BLOCK_SECONDS     120

#पूर्ण_अगर
