<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 */

#अगर_अघोषित __CX25821_AUDIO_H__
#घोषणा __CX25821_AUDIO_H__

#घोषणा USE_RISC_NOOP		1
#घोषणा LINES_PER_BUFFER	15
#घोषणा AUDIO_LINE_SIZE		128

/* Number of buffer programs to use at once. */
#घोषणा NUMBER_OF_PROGRAMS	8

/*
 * Max size of the RISC program क्रम a buffer. - worst हाल is 2 ग_लिखोs per line
 * Space is also added क्रम the 4 no-op inकाष्ठाions added on the end.
 */
#अगर_अघोषित USE_RISC_NOOP
#घोषणा MAX_BUFFER_PROGRAM_SIZE						\
	(2 * LINES_PER_BUFFER * RISC_WRITE_INSTRUCTION_SIZE +		\
	 RISC_WRITECR_INSTRUCTION_SIZE * 4)
#पूर्ण_अगर

/* MAE 12 July 2005 Try to use NOOP RISC inकाष्ठाion instead */
#अगर_घोषित USE_RISC_NOOP
#घोषणा MAX_BUFFER_PROGRAM_SIZE						\
	(2 * LINES_PER_BUFFER * RISC_WRITE_INSTRUCTION_SIZE +		\
	 RISC_NOOP_INSTRUCTION_SIZE * 4)
#पूर्ण_अगर

/* Sizes of various inकाष्ठाions in bytes.  Used when adding inकाष्ठाions. */
#घोषणा RISC_WRITE_INSTRUCTION_SIZE	12
#घोषणा RISC_JUMP_INSTRUCTION_SIZE	12
#घोषणा RISC_SKIP_INSTRUCTION_SIZE	4
#घोषणा RISC_SYNC_INSTRUCTION_SIZE	4
#घोषणा RISC_WRITECR_INSTRUCTION_SIZE	16
#घोषणा RISC_NOOP_INSTRUCTION_SIZE	4

#घोषणा MAX_AUDIO_DMA_BUFFER_SIZE					\
	(MAX_BUFFER_PROGRAM_SIZE * NUMBER_OF_PROGRAMS +			\
	 RISC_SYNC_INSTRUCTION_SIZE)

#पूर्ण_अगर
