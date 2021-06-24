<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/* Copyright (C) 2006-2017 Oracle Corporation */

#अगर_अघोषित __HGSMI_DEFS_H__
#घोषणा __HGSMI_DEFS_H__

/* Buffer sequence type mask. */
#घोषणा HGSMI_BUFFER_HEADER_F_SEQ_MASK     0x03
/* Single buffer, not a part of a sequence. */
#घोषणा HGSMI_BUFFER_HEADER_F_SEQ_SINGLE   0x00
/* The first buffer in a sequence. */
#घोषणा HGSMI_BUFFER_HEADER_F_SEQ_START    0x01
/* A middle buffer in a sequence. */
#घोषणा HGSMI_BUFFER_HEADER_F_SEQ_CONTINUE 0x02
/* The last buffer in a sequence. */
#घोषणा HGSMI_BUFFER_HEADER_F_SEQ_END      0x03

/* 16 bytes buffer header. */
काष्ठा hgsmi_buffer_header अणु
	u32 data_size;		/* Size of data that follows the header. */
	u8 flags;		/* HGSMI_BUFFER_HEADER_F_* */
	u8 channel;		/* The channel the data must be routed to. */
	u16 channel_info;	/* Opaque to the HGSMI, used by the channel. */

	जोड़ अणु
		/* Opaque placeholder to make the जोड़ 8 bytes. */
		u8 header_data[8];

		/* HGSMI_BUFFER_HEADER_F_SEQ_SINGLE */
		काष्ठा अणु
			u32 reserved1;	/* A reserved field, initialize to 0. */
			u32 reserved2;	/* A reserved field, initialize to 0. */
		पूर्ण buffer;

		/* HGSMI_BUFFER_HEADER_F_SEQ_START */
		काष्ठा अणु
			/* Must be the same क्रम all buffers in the sequence. */
			u32 sequence_number;
			/* The total size of the sequence. */
			u32 sequence_size;
		पूर्ण sequence_start;

		/*
		 * HGSMI_BUFFER_HEADER_F_SEQ_CONTINUE and
		 * HGSMI_BUFFER_HEADER_F_SEQ_END
		 */
		काष्ठा अणु
			/* Must be the same क्रम all buffers in the sequence. */
			u32 sequence_number;
			/* Data offset in the entire sequence. */
			u32 sequence_offset;
		पूर्ण sequence_जारी;
	पूर्ण u;
पूर्ण __packed;

/* 8 bytes buffer tail. */
काष्ठा hgsmi_buffer_tail अणु
	/* Reserved, must be initialized to 0. */
	u32 reserved;
	/*
	 * One-at-a-Time Hash: https://www.burtleburtle.net/bob/hash/करोobs.hपंचांगl
	 * Over the header, offset and क्रम first 4 bytes of the tail.
	 */
	u32 checksum;
पूर्ण __packed;

/*
 * The size of the array of channels. Array indexes are u8.
 * Note: the value must not be changed.
 */
#घोषणा HGSMI_NUMBER_OF_CHANNELS 0x100

#पूर्ण_अगर
