<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/* Copyright (C) 2006-2016 Oracle Corporation */

#अगर_अघोषित __VBOXVIDEO_H__
#घोषणा __VBOXVIDEO_H__

#घोषणा VBOX_VIDEO_MAX_SCREENS 64

/*
 * The last 4096 bytes of the guest VRAM contains the generic info क्रम all
 * DualView chunks: sizes and offsets of chunks. This is filled by miniport.
 *
 * Last 4096 bytes of each chunk contain chunk specअगरic data: framebuffer info,
 * etc. This is used exclusively by the corresponding instance of a display
 * driver.
 *
 * The VRAM layout:
 *   Last 4096 bytes - Adapter inक्रमmation area.
 *   4096 bytes aligned miniport heap (value specअगरied in the config rouded up).
 *   Slack - what left after भागiding the VRAM.
 *   4096 bytes aligned framebuffers:
 *     last 4096 bytes of each framebuffer is the display inक्रमmation area.
 *
 * The Virtual Graphics Adapter inक्रमmation in the guest VRAM is stored by the
 * guest video driver using काष्ठाures prepended by VBOXVIDEOINFOHDR.
 *
 * When the guest driver ग_लिखोs dword 0 to the VBE_DISPI_INDEX_VBOX_VIDEO
 * the host starts to process the info. The first element at the start of
 * the 4096 bytes region should be normally be a LINK that poपूर्णांकs to
 * actual inक्रमmation chain. That way the guest driver can have some
 * fixed layout of the inक्रमmation memory block and just reग_लिखो
 * the link to poपूर्णांक to relevant memory chain.
 *
 * The processing stops at the END element.
 *
 * The host can access the memory only when the port IO is processed.
 * All data that will be needed later must be copied from these 4096 bytes.
 * But other VRAM can be used by host until the mode is disabled.
 *
 * The guest driver ग_लिखोs dword 0xffffffff to the VBE_DISPI_INDEX_VBOX_VIDEO
 * to disable the mode.
 *
 * VBE_DISPI_INDEX_VBOX_VIDEO is used to पढ़ो the configuration inक्रमmation
 * from the host and issue commands to the host.
 *
 * The guest ग_लिखोs the VBE_DISPI_INDEX_VBOX_VIDEO index रेजिस्टर, the the
 * following operations with the VBE data रेजिस्टर can be perक्रमmed:
 *
 * Operation            Result
 * ग_लिखो 16 bit value   NOP
 * पढ़ो 16 bit value    count of monitors
 * ग_लिखो 32 bit value   set the vbox cmd value and the cmd processed by the host
 * पढ़ो 32 bit value    result of the last vbox command is वापसed
 */

काष्ठा vbva_cmd_hdr अणु
	s16 x;
	s16 y;
	u16 w;
	u16 h;
पूर्ण __packed;

/*
 * The VBVA ring buffer is suitable क्रम transferring large (< 2GB) amount of
 * data. For example big biपंचांगaps which करो not fit to the buffer.
 *
 * Guest starts writing to the buffer by initializing a record entry in the
 * records queue. VBVA_F_RECORD_PARTIAL indicates that the record is being
 * written. As data is written to the ring buffer, the guest increases
 * मुक्त_offset.
 *
 * The host पढ़ोs the records on flushes and processes all completed records.
 * When host encounters situation when only a partial record presents and
 * len_and_flags & ~VBVA_F_RECORD_PARTIAL >= VBVA_RING_BUFFER_SIZE -
 * VBVA_RING_BUFFER_THRESHOLD, the host fetched all record data and updates
 * data_offset. After that on each flush the host जारीs fetching the data
 * until the record is completed.
 */

#घोषणा VBVA_RING_BUFFER_SIZE        (4194304 - 1024)
#घोषणा VBVA_RING_BUFFER_THRESHOLD   (4096)

#घोषणा VBVA_MAX_RECORDS (64)

#घोषणा VBVA_F_MODE_ENABLED         0x00000001u
#घोषणा VBVA_F_MODE_VRDP            0x00000002u
#घोषणा VBVA_F_MODE_VRDP_RESET      0x00000004u
#घोषणा VBVA_F_MODE_VRDP_ORDER_MASK 0x00000008u

#घोषणा VBVA_F_STATE_PROCESSING     0x00010000u

#घोषणा VBVA_F_RECORD_PARTIAL       0x80000000u

काष्ठा vbva_record अणु
	u32 len_and_flags;
पूर्ण __packed;

/*
 * The minimum HGSMI heap size is PAGE_SIZE (4096 bytes) and is a restriction of
 * the runसमय heapsimple API. Use minimum 2 pages here, because the info area
 * also may contain other data (क्रम example hgsmi_host_flags काष्ठाure).
 */
#घोषणा VBVA_ADAPTER_INFORMATION_SIZE 65536
#घोषणा VBVA_MIN_BUFFER_SIZE          65536

/* The value क्रम port IO to let the adapter to पूर्णांकerpret the adapter memory. */
#घोषणा VBOX_VIDEO_DISABLE_ADAPTER_MEMORY        0xFFFFFFFF

/* The value क्रम port IO to let the adapter to पूर्णांकerpret the adapter memory. */
#घोषणा VBOX_VIDEO_INTERPRET_ADAPTER_MEMORY      0x00000000

/*
 * The value क्रम port IO to let the adapter to पूर्णांकerpret the display memory.
 * The display number is encoded in low 16 bits.
 */
#घोषणा VBOX_VIDEO_INTERPRET_DISPLAY_MEMORY_BASE 0x00010000

काष्ठा vbva_host_flags अणु
	u32 host_events;
	u32 supported_orders;
पूर्ण __packed;

काष्ठा vbva_buffer अणु
	काष्ठा vbva_host_flags host_flags;

	/* The offset where the data start in the buffer. */
	u32 data_offset;
	/* The offset where next data must be placed in the buffer. */
	u32 मुक्त_offset;

	/* The queue of record descriptions. */
	काष्ठा vbva_record records[VBVA_MAX_RECORDS];
	u32 record_first_index;
	u32 record_मुक्त_index;

	/* Space to leave मुक्त when large partial records are transferred. */
	u32 partial_ग_लिखो_tresh;

	u32 data_len;
	/* variable size क्रम the rest of the vbva_buffer area in VRAM. */
	u8 data[];
पूर्ण __packed;

#घोषणा VBVA_MAX_RECORD_SIZE (128 * 1024 * 1024)

/* guest->host commands */
#घोषणा VBVA_QUERY_CONF32			 1
#घोषणा VBVA_SET_CONF32				 2
#घोषणा VBVA_INFO_VIEW				 3
#घोषणा VBVA_INFO_HEAP				 4
#घोषणा VBVA_FLUSH				 5
#घोषणा VBVA_INFO_SCREEN			 6
#घोषणा VBVA_ENABLE				 7
#घोषणा VBVA_MOUSE_POINTER_SHAPE		 8
/* inक्रमms host about HGSMI caps. see vbva_caps below */
#घोषणा VBVA_INFO_CAPS				12
/* configures scanline, see VBVASCANLINECFG below */
#घोषणा VBVA_SCANLINE_CFG			13
/* requests scanline info, see VBVASCANLINEINFO below */
#घोषणा VBVA_SCANLINE_INFO			14
/* inक्रमm host about VBVA Command submission */
#घोषणा VBVA_CMDVBVA_SUBMIT			16
/* inक्रमm host about VBVA Command submission */
#घोषणा VBVA_CMDVBVA_FLUSH			17
/* G->H DMA command */
#घोषणा VBVA_CMDVBVA_CTL			18
/* Query most recent mode hपूर्णांकs sent */
#घोषणा VBVA_QUERY_MODE_HINTS			19
/*
 * Report the guest भव desktop position and size क्रम mapping host and
 * guest poपूर्णांकer positions.
 */
#घोषणा VBVA_REPORT_INPUT_MAPPING		20
/* Report the guest cursor position and query the host position. */
#घोषणा VBVA_CURSOR_POSITION			21

/* host->guest commands */
#घोषणा VBVAHG_EVENT				1
#घोषणा VBVAHG_DISPLAY_CUSTOM			2

/* vbva_conf32::index */
#घोषणा VBOX_VBVA_CONF32_MONITOR_COUNT		0
#घोषणा VBOX_VBVA_CONF32_HOST_HEAP_SIZE		1
/*
 * Returns VINF_SUCCESS अगर the host can report mode hपूर्णांकs via VBVA.
 * Set value to VERR_NOT_SUPPORTED beक्रमe calling.
 */
#घोषणा VBOX_VBVA_CONF32_MODE_HINT_REPORTING	2
/*
 * Returns VINF_SUCCESS अगर the host can report guest cursor enabled status via
 * VBVA.  Set value to VERR_NOT_SUPPORTED beक्रमe calling.
 */
#घोषणा VBOX_VBVA_CONF32_GUEST_CURSOR_REPORTING	3
/*
 * Returns the currently available host cursor capabilities.  Available अगर
 * VBOX_VBVA_CONF32_GUEST_CURSOR_REPORTING वापसs success.
 */
#घोषणा VBOX_VBVA_CONF32_CURSOR_CAPABILITIES	4
/* Returns the supported flags in vbva_infoscreen.flags. */
#घोषणा VBOX_VBVA_CONF32_SCREEN_FLAGS		5
/* Returns the max size of VBVA record. */
#घोषणा VBOX_VBVA_CONF32_MAX_RECORD_SIZE	6

काष्ठा vbva_conf32 अणु
	u32 index;
	u32 value;
पूर्ण __packed;

/* Reserved क्रम historical reasons. */
#घोषणा VBOX_VBVA_CURSOR_CAPABILITY_RESERVED0   BIT(0)
/*
 * Guest cursor capability: can the host show a hardware cursor at the host
 * poपूर्णांकer location?
 */
#घोषणा VBOX_VBVA_CURSOR_CAPABILITY_HARDWARE    BIT(1)
/* Reserved क्रम historical reasons. */
#घोषणा VBOX_VBVA_CURSOR_CAPABILITY_RESERVED2   BIT(2)
/* Reserved क्रम historical reasons.  Must always be unset. */
#घोषणा VBOX_VBVA_CURSOR_CAPABILITY_RESERVED3   BIT(3)
/* Reserved क्रम historical reasons. */
#घोषणा VBOX_VBVA_CURSOR_CAPABILITY_RESERVED4   BIT(4)
/* Reserved क्रम historical reasons. */
#घोषणा VBOX_VBVA_CURSOR_CAPABILITY_RESERVED5   BIT(5)

काष्ठा vbva_infoview अणु
	/* Index of the screen, asचिन्हित by the guest. */
	u32 view_index;

	/* The screen offset in VRAM, the framebuffer starts here. */
	u32 view_offset;

	/* The size of the VRAM memory that can be used क्रम the view. */
	u32 view_size;

	/* The recommended maximum size of the VRAM memory क्रम the screen. */
	u32 max_screen_size;
पूर्ण __packed;

काष्ठा vbva_flush अणु
	u32 reserved;
पूर्ण __packed;

/* vbva_infoscreen.flags */
#घोषणा VBVA_SCREEN_F_NONE			0x0000
#घोषणा VBVA_SCREEN_F_ACTIVE			0x0001
/*
 * The भव monitor has been disabled by the guest and should be हटाओd
 * by the host and ignored क्रम purposes of poपूर्णांकer position calculation.
 */
#घोषणा VBVA_SCREEN_F_DISABLED			0x0002
/*
 * The भव monitor has been blanked by the guest and should be blacked
 * out by the host using width, height, etc values from the vbva_infoscreen
 * request.
 */
#घोषणा VBVA_SCREEN_F_BLANK			0x0004
/*
 * The भव monitor has been blanked by the guest and should be blacked
 * out by the host using the previous mode values क्रम width. height, etc.
 */
#घोषणा VBVA_SCREEN_F_BLANK2			0x0008

काष्ठा vbva_infoscreen अणु
	/* Which view contains the screen. */
	u32 view_index;

	/* Physical X origin relative to the primary screen. */
	s32 origin_x;

	/* Physical Y origin relative to the primary screen. */
	s32 origin_y;

	/* Offset of visible framebuffer relative to the framebuffer start. */
	u32 start_offset;

	/* The scan line size in bytes. */
	u32 line_size;

	/* Width of the screen. */
	u32 width;

	/* Height of the screen. */
	u32 height;

	/* Color depth. */
	u16 bits_per_pixel;

	/* VBVA_SCREEN_F_* */
	u16 flags;
पूर्ण __packed;

/* vbva_enable.flags */
#घोषणा VBVA_F_NONE				0x00000000
#घोषणा VBVA_F_ENABLE				0x00000001
#घोषणा VBVA_F_DISABLE				0x00000002
/* extended VBVA to be used with WDDM */
#घोषणा VBVA_F_EXTENDED				0x00000004
/* vbva offset is असलolute VRAM offset */
#घोषणा VBVA_F_ABSOFFSET			0x00000008

काष्ठा vbva_enable अणु
	u32 flags;
	u32 offset;
	s32 result;
पूर्ण __packed;

काष्ठा vbva_enable_ex अणु
	काष्ठा vbva_enable base;
	u32 screen_id;
पूर्ण __packed;

काष्ठा vbva_mouse_poपूर्णांकer_shape अणु
	/* The host result. */
	s32 result;

	/* VBOX_MOUSE_POINTER_* bit flags. */
	u32 flags;

	/* X coordinate of the hot spot. */
	u32 hot_X;

	/* Y coordinate of the hot spot. */
	u32 hot_y;

	/* Width of the poपूर्णांकer in pixels. */
	u32 width;

	/* Height of the poपूर्णांकer in scanlines. */
	u32 height;

	/* Poपूर्णांकer data.
	 *
	 * The data consists of 1 bpp AND mask followed by 32 bpp XOR (color)
	 * mask.
	 *
	 * For poपूर्णांकers without alpha channel the XOR mask pixels are 32 bit
	 * values: (lsb)BGR0(msb). For poपूर्णांकers with alpha channel the XOR mask
	 * consists of (lsb)BGRA(msb) 32 bit values.
	 *
	 * Guest driver must create the AND mask क्रम poपूर्णांकers with alpha chan.,
	 * so अगर host करोes not support alpha, the poपूर्णांकer could be displayed as
	 * a normal color poपूर्णांकer. The AND mask can be स्थिरructed from alpha
	 * values. For example alpha value >= 0xf0 means bit 0 in the AND mask.
	 *
	 * The AND mask is 1 bpp biपंचांगap with byte aligned scanlines. Size of AND
	 * mask, thereक्रमe, is and_len = (width + 7) / 8 * height. The padding
	 * bits at the end of any scanline are undefined.
	 *
	 * The XOR mask follows the AND mask on the next 4 bytes aligned offset:
	 * u8 *xor = and + (and_len + 3) & ~3
	 * Bytes in the gap between the AND and the XOR mask are undefined.
	 * XOR mask scanlines have no gap between them and size of XOR mask is:
	 * xor_len = width * 4 * height.
	 *
	 * Pपुनः_स्मृतिate 4 bytes क्रम accessing actual data as p->data.
	 */
	u8 data[4];
पूर्ण __packed;

/* poपूर्णांकer is visible */
#घोषणा VBOX_MOUSE_POINTER_VISIBLE		0x0001
/* poपूर्णांकer has alpha channel */
#घोषणा VBOX_MOUSE_POINTER_ALPHA		0x0002
/* poपूर्णांकerData contains new poपूर्णांकer shape */
#घोषणा VBOX_MOUSE_POINTER_SHAPE		0x0004

/*
 * The guest driver can handle asynch guest cmd completion by पढ़ोing the
 * command offset from io port.
 */
#घोषणा VBVACAPS_COMPLETEGCMD_BY_IOREAD		0x00000001
/* the guest driver can handle video adapter IRQs */
#घोषणा VBVACAPS_IRQ				0x00000002
/* The guest can पढ़ो video mode hपूर्णांकs sent via VBVA. */
#घोषणा VBVACAPS_VIDEO_MODE_HINTS		0x00000004
/* The guest can चयन to a software cursor on demand. */
#घोषणा VBVACAPS_DISABLE_CURSOR_INTEGRATION	0x00000008
/* The guest करोes not depend on host handling the VBE रेजिस्टरs. */
#घोषणा VBVACAPS_USE_VBVA_ONLY			0x00000010

काष्ठा vbva_caps अणु
	s32 rc;
	u32 caps;
पूर्ण __packed;

/* Query the most recent mode hपूर्णांकs received from the host. */
काष्ठा vbva_query_mode_hपूर्णांकs अणु
	/* The maximum number of screens to वापस hपूर्णांकs क्रम. */
	u16 hपूर्णांकs_queried_count;
	/* The size of the mode hपूर्णांक काष्ठाures directly following this one. */
	u16 hपूर्णांक_काष्ठाure_guest_size;
	/* Return code क्रम the operation. Initialise to VERR_NOT_SUPPORTED. */
	s32 rc;
पूर्ण __packed;

/*
 * Structure in which a mode hपूर्णांक is वापसed. The guest allocates an array
 * of these immediately after the vbva_query_mode_hपूर्णांकs काष्ठाure.
 * To accommodate future extensions, the vbva_query_mode_hपूर्णांकs काष्ठाure
 * specअगरies the size of the vbva_modehपूर्णांक काष्ठाures allocated by the guest,
 * and the host only fills out काष्ठाure elements which fit पूर्णांकo that size. The
 * host should fill any unused members (e.g. dx, dy) or काष्ठाure space on the
 * end with ~0. The whole काष्ठाure can legally be set to ~0 to skip a screen.
 */
काष्ठा vbva_modehपूर्णांक अणु
	u32 magic;
	u32 cx;
	u32 cy;
	u32 bpp;		/* Which has never been used... */
	u32 display;
	u32 dx;			/* X offset पूर्णांकo the भव frame-buffer. */
	u32 dy;			/* Y offset पूर्णांकo the भव frame-buffer. */
	u32 enabled;		/* Not flags. Add new members क्रम new flags. */
पूर्ण __packed;

#घोषणा VBVAMODEHINT_MAGIC 0x0801add9u

/*
 * Report the rectangle relative to which असलolute poपूर्णांकer events should be
 * expressed. This inक्रमmation reमुख्यs valid until the next VBVA resize event
 * क्रम any screen, at which समय it is reset to the bounding rectangle of all
 * भव screens and must be re-set.
 */
काष्ठा vbva_report_input_mapping अणु
	s32 x;	/* Upper left X co-ordinate relative to the first screen. */
	s32 y;	/* Upper left Y co-ordinate relative to the first screen. */
	u32 cx;	/* Rectangle width. */
	u32 cy;	/* Rectangle height. */
पूर्ण __packed;

/*
 * Report the guest cursor position and query the host one. The host may wish
 * to use the guest inक्रमmation to re-position its own cursor (though this is
 * currently unlikely).
 */
काष्ठा vbva_cursor_position अणु
	u32 report_position;	/* Are we reporting a position? */
	u32 x;			/* Guest cursor X position */
	u32 y;			/* Guest cursor Y position */
पूर्ण __packed;

#पूर्ण_अगर
