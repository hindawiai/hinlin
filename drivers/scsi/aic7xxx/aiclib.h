<शैली गुरु>
/*
 * Largely written by Julian Elischer (julian@tfs.com)
 * क्रम TRW Financial Systems.
 *
 * TRW Financial Systems, in accordance with their agreement with Carnegie
 * Mellon University, makes this software available to CMU to distribute
 * or use in any manner that they see fit as दीर्घ as this message is kept with
 * the software. For this reason TFS also grants any other persons or
 * organisations permission to use or modअगरy this software.
 *
 * TFS supplies this software to be खुलाly redistributed
 * on the understanding that TFS is not responsible क्रम the correct
 * functioning of this software in any circumstances.
 *
 * Ported to run under 386BSD by Julian Elischer (julian@tfs.com) Sept 1992
 *
 * $FreeBSD: src/sys/cam/scsi/scsi_all.h,v 1.21 2002/10/08 17:12:44 ken Exp $
 *
 * Copyright (c) 2003 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id$
 */

#अगर_अघोषित	_AICLIB_H
#घोषणा _AICLIB_H

काष्ठा scsi_sense
अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t byte2;
	uपूर्णांक8_t unused[2];
	uपूर्णांक8_t length;
	uपूर्णांक8_t control;
पूर्ण;

#घोषणा		SCSI_REV_0		0
#घोषणा		SCSI_REV_CCS		1
#घोषणा		SCSI_REV_2		2
#घोषणा		SCSI_REV_SPC		3
#घोषणा		SCSI_REV_SPC2		4

काष्ठा scsi_sense_data
अणु
	uपूर्णांक8_t error_code;
#घोषणा	SSD_ERRCODE			0x7F
#घोषणा		SSD_CURRENT_ERROR	0x70
#घोषणा		SSD_DEFERRED_ERROR	0x71
#घोषणा	SSD_ERRCODE_VALID	0x80	
	uपूर्णांक8_t segment;
	uपूर्णांक8_t flags;
#घोषणा	SSD_KEY				0x0F
#घोषणा		SSD_KEY_NO_SENSE	0x00
#घोषणा		SSD_KEY_RECOVERED_ERROR	0x01
#घोषणा		SSD_KEY_NOT_READY	0x02
#घोषणा		SSD_KEY_MEDIUM_ERROR	0x03
#घोषणा		SSD_KEY_HARDWARE_ERROR	0x04
#घोषणा		SSD_KEY_ILLEGAL_REQUEST	0x05
#घोषणा		SSD_KEY_UNIT_ATTENTION	0x06
#घोषणा		SSD_KEY_DATA_PROTECT	0x07
#घोषणा		SSD_KEY_BLANK_CHECK	0x08
#घोषणा		SSD_KEY_Venकरोr_Specअगरic	0x09
#घोषणा		SSD_KEY_COPY_ABORTED	0x0a
#घोषणा		SSD_KEY_ABORTED_COMMAND	0x0b		
#घोषणा		SSD_KEY_EQUAL		0x0c
#घोषणा		SSD_KEY_VOLUME_OVERFLOW	0x0d
#घोषणा		SSD_KEY_MISCOMPARE	0x0e
#घोषणा		SSD_KEY_RESERVED	0x0f			
#घोषणा	SSD_ILI		0x20
#घोषणा	SSD_EOM		0x40
#घोषणा	SSD_खाताMARK	0x80
	uपूर्णांक8_t info[4];
	uपूर्णांक8_t extra_len;
	uपूर्णांक8_t cmd_spec_info[4];
	uपूर्णांक8_t add_sense_code;
	uपूर्णांक8_t add_sense_code_qual;
	uपूर्णांक8_t fru;
	uपूर्णांक8_t sense_key_spec[3];
#घोषणा	SSD_SCS_VALID		0x80
#घोषणा SSD_FIELDPTR_CMD	0x40
#घोषणा SSD_BITPTR_VALID	0x08
#घोषणा SSD_BITPTR_VALUE	0x07
#घोषणा SSD_MIN_SIZE 18
	uपूर्णांक8_t extra_bytes[14];
#घोषणा SSD_FULL_SIZE माप(काष्ठा scsi_sense_data)
पूर्ण;

/************************* Large Disk Handling ********************************/
अटल अंतरभूत पूर्णांक
aic_sector_भाग(sector_t capacity, पूर्णांक heads, पूर्णांक sectors)
अणु
	/* ugly, ugly sector_भाग calling convention.. */
	sector_भाग(capacity, (heads * sectors));
	वापस (पूर्णांक)capacity;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
scsi_4btoul(uपूर्णांक8_t *bytes)
अणु
	uपूर्णांक32_t rv;

	rv = (bytes[0] << 24) |
	     (bytes[1] << 16) |
	     (bytes[2] << 8) |
	     bytes[3];
	वापस (rv);
पूर्ण

/* Macros क्रम generating the elements of the PCI ID tables. */

#घोषणा GETID(v, s) (अचिन्हित)(((v) >> (s)) & 0xFFFF ?: PCI_ANY_ID)

#घोषणा ID_C(x, c)						\
अणु								\
	GETID(x,32), GETID(x,48), GETID(x,0), GETID(x,16),	\
	(c) << 8, 0xFFFF00, 0					\
पूर्ण

#घोषणा ID2C(x)                          \
	ID_C(x, PCI_CLASS_STORAGE_SCSI), \
	ID_C(x, PCI_CLASS_STORAGE_RAID)

#घोषणा IसूचीOC(x)  ((x) | ~ID_ALL_IROC_MASK)

/* Generate IDs क्रम all 16 possibilites.
 * The argument has alपढ़ोy masked out
 * the 4 least signअगरicant bits of the device id.
 * (e.g., mask: ID_9005_GENERIC_MASK).
 */
#घोषणा ID16(x)                          \
	ID(x),                           \
	ID((x) | 0x0001000000000000ull), \
	ID((x) | 0x0002000000000000ull), \
	ID((x) | 0x0003000000000000ull), \
	ID((x) | 0x0004000000000000ull), \
	ID((x) | 0x0005000000000000ull), \
	ID((x) | 0x0006000000000000ull), \
	ID((x) | 0x0007000000000000ull), \
	ID((x) | 0x0008000000000000ull), \
	ID((x) | 0x0009000000000000ull), \
	ID((x) | 0x000A000000000000ull), \
	ID((x) | 0x000B000000000000ull), \
	ID((x) | 0x000C000000000000ull), \
	ID((x) | 0x000D000000000000ull), \
	ID((x) | 0x000E000000000000ull), \
	ID((x) | 0x000F000000000000ull)

#पूर्ण_अगर /*_AICLIB_H */
