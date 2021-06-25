<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    standard tape device functions क्रम ibm tapes.
 *
 *    Copyright IBM Corp. 2001, 2006
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _TAPE_STD_H
#घोषणा _TAPE_STD_H

#समावेश <यंत्र/tape390.h>

/*
 * Biggest block size to handle. Currently 64K because we only build
 * channel programs without data chaining.
 */
#घोषणा MAX_BLOCKSIZE   65535

/*
 * The CCW commands क्रम the Tape type of command.
 */
#घोषणा INVALID_00		0x00	/* Invalid cmd */
#घोषणा BACKSPACEBLOCK		0x27	/* Back Space block */
#घोषणा BACKSPACEखाता		0x2f	/* Back Space file */
#घोषणा DATA_SEC_ERASE		0x97	/* Data security erase */
#घोषणा ERASE_GAP		0x17	/* Erase Gap */
#घोषणा FORSPACEBLOCK		0x37	/* Forward space block */
#घोषणा FORSPACEखाता		0x3F	/* Forward Space file */
#घोषणा FORCE_STREAM_CNT	0xEB	/* Forced streaming count # */
#घोषणा NOP			0x03	/* No operation	*/
#घोषणा READ_FORWARD		0x02	/* Read क्रमward */
#घोषणा REWIND			0x07	/* Rewind */
#घोषणा REWIND_UNLOAD		0x0F	/* Rewind and Unload */
#घोषणा SENSE			0x04	/* Sense */
#घोषणा NEW_MODE_SET		0xEB	/* Guess it is Mode set */
#घोषणा WRITE_CMD		0x01	/* Write */
#घोषणा WRITETAPEMARK		0x1F	/* Write Tape Mark */

#घोषणा ASSIGN			0xB7	/* 3420 REJECT,3480 OK	*/
#घोषणा CONTROL_ACCESS		0xE3	/* Set high speed */
#घोषणा DIAG_MODE_SET		0x0B	/* 3420 NOP, 3480 REJECT */
#घोषणा LOAD_DISPLAY		0x9F	/* 3420 REJECT,3480 OK */
#घोषणा LOCATE			0x4F	/* 3420 REJ, 3480 NOP */
#घोषणा LOOP_WRITE_TO_READ	0x8B	/* 3480 REJECT */
#घोषणा MODE_SET_DB		0xDB	/* 3420 REJECT,3480 OK */
#घोषणा MODE_SET_C3		0xC3	/* क्रम 3420 */
#घोषणा MODE_SET_CB		0xCB	/* क्रम 3420 */
#घोषणा MODE_SET_D3		0xD3	/* क्रम 3420 */
#घोषणा READ_BACKWARD		0x0C	/* */
#घोषणा READ_BLOCK_ID		0x22	/* 3420 REJECT,3480 OK */
#घोषणा READ_BUFFER		0x12	/* 3420 REJECT,3480 OK */
#घोषणा READ_BUFF_LOG		0x24	/* 3420 REJECT,3480 OK */
#घोषणा RELEASE			0xD4	/* 3420 NOP, 3480 REJECT */
#घोषणा REQ_TRK_IN_ERROR	0x1B	/* 3420 NOP, 3480 REJECT */
#घोषणा RESERVE			0xF4	/* 3420 NOP, 3480 REJECT */
#घोषणा SENSE_GROUP_ID		0x34	/* 3420 REJECT,3480 OK */
#घोषणा SENSE_ID		0xE4	/* 3420 REJECT,3480 OK */
#घोषणा READ_DEV_CHAR		0x64	/* Read device अक्षरacteristics */
#घोषणा SET_DIAGNOSE		0x4B	/* 3420 NOP, 3480 REJECT */
#घोषणा SET_GROUP_ID		0xAF	/* 3420 REJECT,3480 OK */
#घोषणा SET_TAPE_WRITE_IMMED	0xC3	/* क्रम 3480 */
#घोषणा SUSPEND			0x5B	/* 3420 REJ, 3480 NOP */
#घोषणा SYNC			0x43	/* Synchronize (flush buffer) */
#घोषणा UNASSIGN		0xC7	/* 3420 REJECT,3480 OK */
#घोषणा PERF_SUBSYS_FUNC	0x77	/* 3490 CMD */
#घोषणा READ_CONFIG_DATA	0xFA	/* 3490 CMD */
#घोषणा READ_MESSAGE_ID		0x4E	/* 3490 CMD */
#घोषणा READ_SUBSYS_DATA	0x3E	/* 3490 CMD */
#घोषणा SET_INTERFACE_ID	0x73	/* 3490 CMD */

#घोषणा SENSE_COMMAND_REJECT		0x80
#घोषणा SENSE_INTERVENTION_REQUIRED	0x40
#घोषणा SENSE_BUS_OUT_CHECK		0x20
#घोषणा SENSE_EQUIPMENT_CHECK		0x10
#घोषणा SENSE_DATA_CHECK		0x08
#घोषणा SENSE_OVERRUN			0x04
#घोषणा SENSE_DEFERRED_UNIT_CHECK	0x02
#घोषणा SENSE_ASSIGNED_ELSEWHERE	0x01

#घोषणा SENSE_LOCATE_FAILURE		0x80
#घोषणा SENSE_DRIVE_ONLINE		0x40
#घोषणा SENSE_RESERVED			0x20
#घोषणा SENSE_RECORD_SEQUENCE_ERR	0x10
#घोषणा SENSE_BEGINNING_OF_TAPE		0x08
#घोषणा SENSE_WRITE_MODE		0x04
#घोषणा SENSE_WRITE_PROTECT		0x02
#घोषणा SENSE_NOT_CAPABLE		0x01

#घोषणा SENSE_CHANNEL_ADAPTER_CODE	0xE0
#घोषणा SENSE_CHANNEL_ADAPTER_LOC	0x10
#घोषणा SENSE_REPORTING_CU		0x08
#घोषणा SENSE_AUTOMATIC_LOADER		0x04
#घोषणा SENSE_TAPE_SYNC_MODE		0x02
#घोषणा SENSE_TAPE_POSITIONING		0x01

/* discipline functions */
काष्ठा tape_request *tape_std_पढ़ो_block(काष्ठा tape_device *, माप_प्रकार);
व्योम tape_std_पढ़ो_backward(काष्ठा tape_device *device,
			    काष्ठा tape_request *request);
काष्ठा tape_request *tape_std_ग_लिखो_block(काष्ठा tape_device *, माप_प्रकार);

/* Some non-mtop commands. */
पूर्णांक tape_std_assign(काष्ठा tape_device *);
पूर्णांक tape_std_unassign(काष्ठा tape_device *);
पूर्णांक tape_std_पढ़ो_block_id(काष्ठा tape_device *device, __u64 *id);
पूर्णांक tape_std_display(काष्ठा tape_device *, काष्ठा display_काष्ठा *disp);
पूर्णांक tape_std_terminate_ग_लिखो(काष्ठा tape_device *);

/* Standard magnetic tape commands. */
पूर्णांक tape_std_mtbsf(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtbsfm(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtbsr(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtcompression(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mteom(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mterase(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtfsf(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtfsfm(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtfsr(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtload(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtnop(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtoffl(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtreset(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtreten(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtrew(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtsetblk(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtunload(काष्ठा tape_device *, पूर्णांक);
पूर्णांक tape_std_mtweof(काष्ठा tape_device *, पूर्णांक);

/* Event handlers */
व्योम tape_std_process_eov(काष्ठा tape_device *);

/* S390 tape types */
क्रमागत s390_tape_type अणु
        tape_3480,
        tape_3490,
        tape_3590,
        tape_3592,
पूर्ण;

#पूर्ण_अगर // _TAPE_STD_H
