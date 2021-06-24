<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IMPORTANT: The following स्थिरants must match the ones used and defined in
 * बाह्यal/qemu/include/hw/misc/goldfish_pipe.h
 */

#अगर_अघोषित GOLDFISH_PIPE_QEMU_H
#घोषणा GOLDFISH_PIPE_QEMU_H

/* List of bitflags वापसed in status of CMD_POLL command */
क्रमागत PipePollFlags अणु
	PIPE_POLL_IN	= 1 << 0,
	PIPE_POLL_OUT	= 1 << 1,
	PIPE_POLL_HUP	= 1 << 2
पूर्ण;

/* Possible status values used to संकेत errors */
क्रमागत PipeErrors अणु
	PIPE_ERROR_INVAL	= -1,
	PIPE_ERROR_AGAIN	= -2,
	PIPE_ERROR_NOMEM	= -3,
	PIPE_ERROR_IO		= -4
पूर्ण;

/* Bit-flags used to संकेत events from the emulator */
क्रमागत PipeWakeFlags अणु
	/* emulator बंदd pipe */
	PIPE_WAKE_CLOSED		= 1 << 0,

	/* pipe can now be पढ़ो from */
	PIPE_WAKE_READ			= 1 << 1,

	/* pipe can now be written to */
	PIPE_WAKE_WRITE			= 1 << 2,

	/* unlock this pipe's DMA buffer */
	PIPE_WAKE_UNLOCK_DMA		= 1 << 3,

	/* unlock DMA buffer of the pipe shared to this pipe */
	PIPE_WAKE_UNLOCK_DMA_SHARED	= 1 << 4,
पूर्ण;

/* Possible pipe closing reasons */
क्रमागत PipeCloseReason अणु
	/* guest sent a बंद command */
	PIPE_CLOSE_GRACEFUL		= 0,

	/* guest rebooted, we're closing the pipes */
	PIPE_CLOSE_REBOOT		= 1,

	/* बंद old pipes on snapshot load */
	PIPE_CLOSE_LOAD_SNAPSHOT	= 2,

	/* some unrecoverable error on the pipe */
	PIPE_CLOSE_ERROR		= 3,
पूर्ण;

/* Bit flags क्रम the 'flags' field */
क्रमागत PipeFlagsBits अणु
	BIT_CLOSED_ON_HOST = 0,  /* pipe बंदd by host */
	BIT_WAKE_ON_WRITE  = 1,  /* want to be woken on ग_लिखोs */
	BIT_WAKE_ON_READ   = 2,  /* want to be woken on पढ़ोs */
पूर्ण;

क्रमागत PipeRegs अणु
	PIPE_REG_CMD = 0,

	PIPE_REG_SIGNAL_BUFFER_HIGH = 4,
	PIPE_REG_SIGNAL_BUFFER = 8,
	PIPE_REG_SIGNAL_BUFFER_COUNT = 12,

	PIPE_REG_OPEN_BUFFER_HIGH = 20,
	PIPE_REG_OPEN_BUFFER = 24,

	PIPE_REG_VERSION = 36,

	PIPE_REG_GET_SIGNALLED = 48,
पूर्ण;

क्रमागत PipeCmdCode अणु
	/* to be used by the pipe device itself */
	PIPE_CMD_OPEN		= 1,

	PIPE_CMD_CLOSE,
	PIPE_CMD_POLL,
	PIPE_CMD_WRITE,
	PIPE_CMD_WAKE_ON_WRITE,
	PIPE_CMD_READ,
	PIPE_CMD_WAKE_ON_READ,

	/*
	 * TODO(zyy): implement a deferred पढ़ो/ग_लिखो execution to allow
	 * parallel processing of pipe operations on the host.
	 */
	PIPE_CMD_WAKE_ON_DONE_IO,
पूर्ण;

#पूर्ण_अगर /* GOLDFISH_PIPE_QEMU_H */
