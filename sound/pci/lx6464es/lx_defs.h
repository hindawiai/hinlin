<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* -*- linux-c -*- *
 *
 * ALSA driver क्रम the digigram lx6464es पूर्णांकerface
 * adapted upstream headers
 *
 * Copyright (c) 2009 Tim Blechmann <tim@klingt.org>
 */

#अगर_अघोषित LX_DEFS_H
#घोषणा LX_DEFS_H

/* code adapted from ethersound.h */
#घोषणा	XES_FREQ_COUNT8_MASK    0x00001FFF /* compteur 25MHz entre 8 ech. */
#घोषणा	XES_FREQ_COUNT8_44_MIN  0x00001288 /* 25M /
					    * [ 44k - ( 44.1k + 48k ) / 2 ]
					    * * 8 */
#घोषणा	XES_FREQ_COUNT8_44_MAX	0x000010F0 /* 25M / [ ( 44.1k + 48k ) / 2 ]
					    * * 8 */
#घोषणा	XES_FREQ_COUNT8_48_MAX	0x00000F08 /* 25M /
					    * [ 48k + ( 44.1k + 48k ) / 2 ]
					    * * 8 */

/* code adapted from LXES_रेजिस्टरs.h */

#घोषणा IOCR_OUTPUTS_OFFSET 0	/* (rw) offset क्रम the number of OUTs in the
				 * ConfES रेजिस्टर. */
#घोषणा IOCR_INPUTS_OFFSET  8	/* (rw) offset क्रम the number of INs in the
				 * ConfES रेजिस्टर. */
#घोषणा FREQ_RATIO_OFFSET  19	/* (rw) offset क्रम frequency ratio in the
				 * ConfES रेजिस्टर. */
#घोषणा	FREQ_RATIO_SINGLE_MODE 0x01 /* value क्रम single mode frequency ratio:
				     * sample rate = frequency rate. */

#घोषणा CONFES_READ_PART_MASK	0x00070000
#घोषणा CONFES_WRITE_PART_MASK	0x00F80000

/* code adapted from अगर_drv_mb.h */

#घोषणा MASK_SYS_STATUS_ERROR	(1L << 31) /* events that lead to a PCI irq अगर
					    * not yet pending */
#घोषणा MASK_SYS_STATUS_URUN	(1L << 30)
#घोषणा MASK_SYS_STATUS_ORUN	(1L << 29)
#घोषणा MASK_SYS_STATUS_EOBO	(1L << 28)
#घोषणा MASK_SYS_STATUS_EOBI	(1L << 27)
#घोषणा MASK_SYS_STATUS_FREQ	(1L << 26)
#घोषणा MASK_SYS_STATUS_ESA	(1L << 25) /* reserved, this is set by the
					    * XES */
#घोषणा MASK_SYS_STATUS_TIMER	(1L << 24)

#घोषणा MASK_SYS_ASYNC_EVENTS	(MASK_SYS_STATUS_ERROR |		\
				 MASK_SYS_STATUS_URUN  |		\
				 MASK_SYS_STATUS_ORUN  |		\
				 MASK_SYS_STATUS_EOBO  |		\
				 MASK_SYS_STATUS_EOBI  |		\
				 MASK_SYS_STATUS_FREQ  |		\
				 MASK_SYS_STATUS_ESA)

#घोषणा MASK_SYS_PCI_EVENTS		(MASK_SYS_ASYNC_EVENTS |	\
					 MASK_SYS_STATUS_TIMER)

#घोषणा MASK_SYS_TIMER_COUNT	0x0000FFFF

#घोषणा MASK_SYS_STATUS_EOT_PLX		(1L << 22) /* event that reमुख्यs
						    * पूर्णांकernal: reserved fo end
						    * of plx dma */
#घोषणा MASK_SYS_STATUS_XES		(1L << 21) /* event that reमुख्यs
						    * पूर्णांकernal: pending XES
						    * IRQ */
#घोषणा MASK_SYS_STATUS_CMD_DONE	(1L << 20) /* alternate command
						    * management: notअगरy driver
						    * instead of polling */


#घोषणा MAX_STREAM_BUFFER 5	/* max amount of stream buffers. */

#घोषणा MICROBLAZE_IBL_MIN		 32
#घोषणा MICROBLAZE_IBL_DEFAULT	        128
#घोषणा MICROBLAZE_IBL_MAX		512
/* #घोषणा MASK_GRANULARITY		(2*MICROBLAZE_IBL_MAX-1) */



/* command opcodes, see reference क्रम details */

/*
 the capture bit position in the object_id field in driver commands
 depends upon the number of managed channels. For now, 64 IN + 64 OUT are
 supported. HOwever, the communication protocol क्रमsees 1024 channels, hence
 bit 10 indicates a capture (input) object).
*/
#घोषणा ID_IS_CAPTURE (1L << 10)
#घोषणा ID_OFFSET	13	/* object ID is at the 13th bit in the
				 * 1st command word.*/
#घोषणा ID_CH_MASK    0x3F
#घोषणा OPCODE_OFFSET	24	/* offset of the command opcode in the first
				 * command word.*/

क्रमागत cmd_mb_opcodes अणु
	CMD_00_INFO_DEBUG	        = 0x00,
	CMD_01_GET_SYS_CFG		= 0x01,
	CMD_02_SET_GRANULARITY		= 0x02,
	CMD_03_SET_TIMER_IRQ		= 0x03,
	CMD_04_GET_EVENT		= 0x04,
	CMD_05_GET_PIPES		= 0x05,

	CMD_06_ALLOCATE_PIPE            = 0x06,
	CMD_07_RELEASE_PIPE		= 0x07,
	CMD_08_ASK_BUFFERS		= 0x08,
	CMD_09_STOP_PIPE		= 0x09,
	CMD_0A_GET_PIPE_SPL_COUNT	= 0x0a,
	CMD_0B_TOGGLE_PIPE_STATE	= 0x0b,

	CMD_0C_DEF_STREAM		= 0x0c,
	CMD_0D_SET_MUTE			= 0x0d,
	CMD_0E_GET_STREAM_SPL_COUNT     = 0x0e,
	CMD_0F_UPDATE_BUFFER		= 0x0f,
	CMD_10_GET_BUFFER		= 0x10,
	CMD_11_CANCEL_BUFFER		= 0x11,
	CMD_12_GET_PEAK			= 0x12,
	CMD_13_SET_STREAM_STATE		= 0x13,
	CMD_14_INVALID			= 0x14,
पूर्ण;

/* pipe states */
क्रमागत pipe_state_t अणु
	PSTATE_IDLE	= 0,	/* the pipe is not processed in the XES_IRQ
				 * (मुक्त or stopped, or छोड़ोd). */
	PSTATE_RUN	= 1,	/* sustained play/record state. */
	PSTATE_PURGE	= 2,	/* the ES channels are now off, render pipes करो
				 * not DMA, record pipe करो a last DMA. */
	PSTATE_ACQUIRE	= 3,	/* the ES channels are now on, render pipes करो
				 * not yet increase their sample count, record
				 * pipes करो not DMA. */
	PSTATE_CLOSING	= 4,	/* the pipe is releasing, and may not yet
				 * receive an "alloc" command. */
पूर्ण;

/* stream states */
क्रमागत stream_state_t अणु
	SSTATE_STOP	=  0x00,       /* setting to stop resets the stream spl
					* count.*/
	SSTATE_RUN	= (0x01 << 0), /* start DMA and spl count handling. */
	SSTATE_PAUSE	= (0x01 << 1), /* छोड़ो DMA and spl count handling. */
पूर्ण;

/* buffer flags */
क्रमागत buffer_flags अणु
	BF_VALID	= 0x80,	/* set अगर the buffer is valid, clear अगर मुक्त.*/
	BF_CURRENT	= 0x40,	/* set अगर this is the current buffer (there is
				 * always a current buffer).*/
	BF_NOTIFY_EOB	= 0x20,	/* set अगर this buffer must cause a PCI event
				 * when finished.*/
	BF_CIRCULAR	= 0x10,	/* set अगर buffer[1] must be copied to buffer[0]
				 * by the end of this buffer.*/
	BF_64BITS_ADR	= 0x08,	/* set अगर the hi part of the address is valid.*/
	BF_xx		= 0x04,	/* future extension.*/
	BF_EOB		= 0x02,	/* set अगर finished, but not yet मुक्त.*/
	BF_PAUSE	= 0x01,	/* छोड़ो stream at buffer end.*/
	BF_ZERO		= 0x00,	/* no flags (init).*/
पूर्ण;

/*
*	Stream Flags definitions
*/
क्रमागत stream_flags अणु
	SF_ZERO		= 0x00000000, /* no flags (stream invalid). */
	SF_VALID	= 0x10000000, /* the stream has a valid DMA_conf
				       * info (setstreamक्रमmat). */
	SF_XRUN		= 0x20000000, /* the stream is un x-run state. */
	SF_START	= 0x40000000, /* the DMA is running.*/
	SF_ASIO		= 0x80000000, /* ASIO.*/
पूर्ण;


#घोषणा MASK_SPL_COUNT_HI 0x00FFFFFF /* 4 MSBits are status bits */
#घोषणा PSTATE_OFFSET             28 /* 4 MSBits are status bits */


#घोषणा MASK_STREAM_HAS_MAPPING	(1L << 12)
#घोषणा MASK_STREAM_IS_ASIO	(1L <<  9)
#घोषणा STREAM_FMT_OFFSET	10   /* the stream fmt bits start at the 10th
				      * bit in the command word. */

#घोषणा STREAM_FMT_16b          0x02
#घोषणा STREAM_FMT_पूर्णांकel        0x01

#घोषणा FREQ_FIELD_OFFSET	15  /* offset of the freq field in the response
				     * word */

#घोषणा BUFF_FLAGS_OFFSET	  24 /*  offset of the buffer flags in the
				      *  response word. */
#घोषणा MASK_DATA_SIZE	  0x00FFFFFF /* this must match the field size of
				      * datasize in the buffer_t काष्ठाure. */

#घोषणा MASK_BUFFER_ID	        0xFF /* the cancel command aरुकोs a buffer ID,
				      * may be 0xFF क्रम "current". */


/* code adapted from PcxErr_e.h */

/* Bits masks */

#घोषणा ERROR_MASK              0x8000

#घोषणा SOURCE_MASK             0x7800

#घोषणा E_SOURCE_BOARD          0x4000 /* 8 >> 1 */
#घोषणा E_SOURCE_DRV            0x2000 /* 4 >> 1 */
#घोषणा E_SOURCE_API            0x1000 /* 2 >> 1 */
/* Error tools */
#घोषणा E_SOURCE_TOOLS          0x0800 /* 1 >> 1 */
/* Error pcxaudio */
#घोषणा E_SOURCE_AUDIO          0x1800 /* 3 >> 1 */
/* Error भव pcx */
#घोषणा E_SOURCE_VPCX           0x2800 /* 5 >> 1 */
/* Error dispatcher */
#घोषणा E_SOURCE_DISPATCHER     0x3000 /* 6 >> 1 */
/* Error from CobraNet firmware */
#घोषणा E_SOURCE_COBRANET       0x3800 /* 7 >> 1 */

#घोषणा E_SOURCE_USER           0x7800

#घोषणा CLASS_MASK              0x0700

#घोषणा CODE_MASK               0x00FF

/* Bits values */

/* Values क्रम the error/warning bit */
#घोषणा ERROR_VALUE             0x8000
#घोषणा WARNING_VALUE           0x0000

/* Class values */
#घोषणा E_CLASS_GENERAL                  0x0000
#घोषणा E_CLASS_INVALID_CMD              0x0100
#घोषणा E_CLASS_INVALID_STD_OBJECT       0x0200
#घोषणा E_CLASS_RSRC_IMPOSSIBLE          0x0300
#घोषणा E_CLASS_WRONG_CONTEXT            0x0400
#घोषणा E_CLASS_BAD_SPECIFIC_PARAMETER   0x0500
#घोषणा E_CLASS_REAL_TIME_ERROR          0x0600
#घोषणा E_CLASS_सूचीECTSHOW               0x0700
#घोषणा E_CLASS_FREE                     0x0700


/* Complete DRV error code क्रम the general class */
#घोषणा ED_GN           (ERROR_VALUE | E_SOURCE_DRV | E_CLASS_GENERAL)
#घोषणा ED_CONCURRENCY                  (ED_GN | 0x01)
#घोषणा ED_DSP_CRASHED                  (ED_GN | 0x02)
#घोषणा ED_UNKNOWN_BOARD                (ED_GN | 0x03)
#घोषणा ED_NOT_INSTALLED                (ED_GN | 0x04)
#घोषणा ED_CANNOT_OPEN_SVC_MANAGER      (ED_GN | 0x05)
#घोषणा ED_CANNOT_READ_REGISTRY         (ED_GN | 0x06)
#घोषणा ED_DSP_VERSION_MISMATCH         (ED_GN | 0x07)
#घोषणा ED_UNAVAILABLE_FEATURE          (ED_GN | 0x08)
#घोषणा ED_CANCELLED                    (ED_GN | 0x09)
#घोषणा ED_NO_RESPONSE_AT_IRQA          (ED_GN | 0x10)
#घोषणा ED_INVALID_ADDRESS              (ED_GN | 0x11)
#घोषणा ED_DSP_CORRUPTED                (ED_GN | 0x12)
#घोषणा ED_PENDING_OPERATION            (ED_GN | 0x13)
#घोषणा ED_NET_ALLOCATE_MEMORY_IMPOSSIBLE   (ED_GN | 0x14)
#घोषणा ED_NET_REGISTER_ERROR               (ED_GN | 0x15)
#घोषणा ED_NET_THREAD_ERROR                 (ED_GN | 0x16)
#घोषणा ED_NET_OPEN_ERROR                   (ED_GN | 0x17)
#घोषणा ED_NET_CLOSE_ERROR                  (ED_GN | 0x18)
#घोषणा ED_NET_NO_MORE_PACKET               (ED_GN | 0x19)
#घोषणा ED_NET_NO_MORE_BUFFER               (ED_GN | 0x1A)
#घोषणा ED_NET_SEND_ERROR                   (ED_GN | 0x1B)
#घोषणा ED_NET_RECEIVE_ERROR                (ED_GN | 0x1C)
#घोषणा ED_NET_WRONG_MSG_SIZE               (ED_GN | 0x1D)
#घोषणा ED_NET_WAIT_ERROR                   (ED_GN | 0x1E)
#घोषणा ED_NET_EEPROM_ERROR                 (ED_GN | 0x1F)
#घोषणा ED_INVALID_RS232_COM_NUMBER         (ED_GN | 0x20)
#घोषणा ED_INVALID_RS232_INIT               (ED_GN | 0x21)
#घोषणा ED_खाता_ERROR                       (ED_GN | 0x22)
#घोषणा ED_INVALID_GPIO_CMD                 (ED_GN | 0x23)
#घोषणा ED_RS232_ALREADY_OPENED             (ED_GN | 0x24)
#घोषणा ED_RS232_NOT_OPENED                 (ED_GN | 0x25)
#घोषणा ED_GPIO_ALREADY_OPENED              (ED_GN | 0x26)
#घोषणा ED_GPIO_NOT_OPENED                  (ED_GN | 0x27)
#घोषणा ED_REGISTRY_ERROR                   (ED_GN | 0x28) /* <- NCX */
#घोषणा ED_INVALID_SERVICE                  (ED_GN | 0x29) /* <- NCX */

#घोषणा ED_READ_खाता_ALREADY_OPENED	    (ED_GN | 0x2a) /* <- Decalage
							    * pour RCX
							    * (old 0x28)
							    * */
#घोषणा ED_READ_खाता_INVALID_COMMAND	    (ED_GN | 0x2b) /* ~ */
#घोषणा ED_READ_खाता_INVALID_PARAMETER	    (ED_GN | 0x2c) /* ~ */
#घोषणा ED_READ_खाता_ALREADY_CLOSED	    (ED_GN | 0x2d) /* ~ */
#घोषणा ED_READ_खाता_NO_INFORMATION	    (ED_GN | 0x2e) /* ~ */
#घोषणा ED_READ_खाता_INVALID_HANDLE	    (ED_GN | 0x2f) /* ~ */
#घोषणा ED_READ_खाता_END_OF_खाता	    (ED_GN | 0x30) /* ~ */
#घोषणा ED_READ_खाता_ERROR	            (ED_GN | 0x31) /* ~ */

#घोषणा ED_DSP_CRASHED_EXC_DSPSTACK_OVERFLOW (ED_GN | 0x32) /* <- Decalage pour
							     * PCX (old 0x14) */
#घोषणा ED_DSP_CRASHED_EXC_SYSSTACK_OVERFLOW (ED_GN | 0x33) /* ~ */
#घोषणा ED_DSP_CRASHED_EXC_ILLEGAL           (ED_GN | 0x34) /* ~ */
#घोषणा ED_DSP_CRASHED_EXC_TIMER_REENTRY     (ED_GN | 0x35) /* ~ */
#घोषणा ED_DSP_CRASHED_EXC_FATAL_ERROR       (ED_GN | 0x36) /* ~ */

#घोषणा ED_FLASH_PCCARD_NOT_PRESENT          (ED_GN | 0x37)

#घोषणा ED_NO_CURRENT_CLOCK                  (ED_GN | 0x38)

/* Complete DRV error code क्रम real समय class */
#घोषणा ED_RT           (ERROR_VALUE | E_SOURCE_DRV | E_CLASS_REAL_TIME_ERROR)
#घोषणा ED_DSP_TIMED_OUT                (ED_RT | 0x01)
#घोषणा ED_DSP_CHK_TIMED_OUT            (ED_RT | 0x02)
#घोषणा ED_STREAM_OVERRUN               (ED_RT | 0x03)
#घोषणा ED_DSP_BUSY                     (ED_RT | 0x04)
#घोषणा ED_DSP_SEMAPHORE_TIME_OUT       (ED_RT | 0x05)
#घोषणा ED_BOARD_TIME_OUT               (ED_RT | 0x06)
#घोषणा ED_XILINX_ERROR                 (ED_RT | 0x07)
#घोषणा ED_COBRANET_ITF_NOT_RESPONDING  (ED_RT | 0x08)

/* Complete BOARD error code क्रम the invaid standard object class */
#घोषणा EB_ISO          (ERROR_VALUE | E_SOURCE_BOARD | \
			 E_CLASS_INVALID_STD_OBJECT)
#घोषणा EB_INVALID_EFFECT               (EB_ISO | 0x00)
#घोषणा EB_INVALID_PIPE                 (EB_ISO | 0x40)
#घोषणा EB_INVALID_STREAM               (EB_ISO | 0x80)
#घोषणा EB_INVALID_AUDIO                (EB_ISO | 0xC0)

/* Complete BOARD error code क्रम impossible resource allocation class */
#घोषणा EB_RI           (ERROR_VALUE | E_SOURCE_BOARD | E_CLASS_RSRC_IMPOSSIBLE)
#घोषणा EB_ALLOCATE_ALL_STREAM_TRANSFERT_BUFFERS_IMPOSSIBLE (EB_RI | 0x01)
#घोषणा EB_ALLOCATE_PIPE_SAMPLE_BUFFER_IMPOSSIBLE           (EB_RI | 0x02)

#घोषणा EB_ALLOCATE_MEM_STREAM_IMPOSSIBLE		\
	EB_ALLOCATE_ALL_STREAM_TRANSFERT_BUFFERS_IMPOSSIBLE
#घोषणा EB_ALLOCATE_MEM_PIPE_IMPOSSIBLE			\
	EB_ALLOCATE_PIPE_SAMPLE_BUFFER_IMPOSSIBLE

#घोषणा EB_ALLOCATE_DIFFERED_CMD_IMPOSSIBLE     (EB_RI | 0x03)
#घोषणा EB_TOO_MANY_DIFFERED_CMD                (EB_RI | 0x04)
#घोषणा EB_RBUFFERS_TABLE_OVERFLOW              (EB_RI | 0x05)
#घोषणा EB_ALLOCATE_EFFECTS_IMPOSSIBLE          (EB_RI | 0x08)
#घोषणा EB_ALLOCATE_EFFECT_POS_IMPOSSIBLE       (EB_RI | 0x09)
#घोषणा EB_RBUFFER_NOT_AVAILABLE                (EB_RI | 0x0A)
#घोषणा EB_ALLOCATE_CONTEXT_LIII_IMPOSSIBLE     (EB_RI | 0x0B)
#घोषणा EB_STATUS_DIALOG_IMPOSSIBLE             (EB_RI | 0x1D)
#घोषणा EB_CONTROL_CMD_IMPOSSIBLE               (EB_RI | 0x1E)
#घोषणा EB_STATUS_SEND_IMPOSSIBLE               (EB_RI | 0x1F)
#घोषणा EB_ALLOCATE_PIPE_IMPOSSIBLE             (EB_RI | 0x40)
#घोषणा EB_ALLOCATE_STREAM_IMPOSSIBLE           (EB_RI | 0x80)
#घोषणा EB_ALLOCATE_AUDIO_IMPOSSIBLE            (EB_RI | 0xC0)

/* Complete BOARD error code क्रम wrong call context class */
#घोषणा EB_WCC          (ERROR_VALUE | E_SOURCE_BOARD | E_CLASS_WRONG_CONTEXT)
#घोषणा EB_CMD_REFUSED                  (EB_WCC | 0x00)
#घोषणा EB_START_STREAM_REFUSED         (EB_WCC | 0xFC)
#घोषणा EB_SPC_REFUSED                  (EB_WCC | 0xFD)
#घोषणा EB_CSN_REFUSED                  (EB_WCC | 0xFE)
#घोषणा EB_CSE_REFUSED                  (EB_WCC | 0xFF)




#पूर्ण_अगर /* LX_DEFS_H */
