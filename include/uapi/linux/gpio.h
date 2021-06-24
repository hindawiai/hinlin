<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * <linux/gpपन.स> - userspace ABI क्रम the GPIO अक्षरacter devices
 *
 * Copyright (C) 2016 Linus Walleij
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#अगर_अघोषित _UAPI_GPIO_H_
#घोषणा _UAPI_GPIO_H_

#समावेश <linux/स्थिर.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/*
 * The maximum size of name and label arrays.
 *
 * Must be a multiple of 8 to ensure 32/64-bit alignment of काष्ठाs.
 */
#घोषणा GPIO_MAX_NAME_SIZE 32

/**
 * काष्ठा gpiochip_info - Inक्रमmation about a certain GPIO chip
 * @name: the Linux kernel name of this GPIO chip
 * @label: a functional name क्रम this GPIO chip, such as a product
 * number, may be empty (i.e. label[0] == '\0')
 * @lines: number of GPIO lines on this chip
 */
काष्ठा gpiochip_info अणु
	अक्षर name[GPIO_MAX_NAME_SIZE];
	अक्षर label[GPIO_MAX_NAME_SIZE];
	__u32 lines;
पूर्ण;

/*
 * Maximum number of requested lines.
 *
 * Must be no greater than 64, as biपंचांगaps are restricted here to 64-bits
 * क्रम simplicity, and a multiple of 2 to ensure 32/64-bit alignment of
 * काष्ठाs.
 */
#घोषणा GPIO_V2_LINES_MAX 64

/*
 * The maximum number of configuration attributes associated with a line
 * request.
 */
#घोषणा GPIO_V2_LINE_NUM_ATTRS_MAX 10

/**
 * क्रमागत gpio_v2_line_flag - &काष्ठा gpio_v2_line_attribute.flags values
 * @GPIO_V2_LINE_FLAG_USED: line is not available क्रम request
 * @GPIO_V2_LINE_FLAG_ACTIVE_LOW: line active state is physical low
 * @GPIO_V2_LINE_FLAG_INPUT: line is an input
 * @GPIO_V2_LINE_FLAG_OUTPUT: line is an output
 * @GPIO_V2_LINE_FLAG_EDGE_RISING: line detects rising (inactive to active)
 * edges
 * @GPIO_V2_LINE_FLAG_EDGE_FALLING: line detects falling (active to
 * inactive) edges
 * @GPIO_V2_LINE_FLAG_OPEN_DRAIN: line is an खोलो drain output
 * @GPIO_V2_LINE_FLAG_OPEN_SOURCE: line is an खोलो source output
 * @GPIO_V2_LINE_FLAG_BIAS_PULL_UP: line has pull-up bias enabled
 * @GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN: line has pull-करोwn bias enabled
 * @GPIO_V2_LINE_FLAG_BIAS_DISABLED: line has bias disabled
 * @GPIO_V2_LINE_FLAG_EVENT_CLOCK_REALTIME: line events contain REALTIME बारtamps
 */
क्रमागत gpio_v2_line_flag अणु
	GPIO_V2_LINE_FLAG_USED			= _BITULL(0),
	GPIO_V2_LINE_FLAG_ACTIVE_LOW		= _BITULL(1),
	GPIO_V2_LINE_FLAG_INPUT			= _BITULL(2),
	GPIO_V2_LINE_FLAG_OUTPUT		= _BITULL(3),
	GPIO_V2_LINE_FLAG_EDGE_RISING		= _BITULL(4),
	GPIO_V2_LINE_FLAG_EDGE_FALLING		= _BITULL(5),
	GPIO_V2_LINE_FLAG_OPEN_DRAIN		= _BITULL(6),
	GPIO_V2_LINE_FLAG_OPEN_SOURCE		= _BITULL(7),
	GPIO_V2_LINE_FLAG_BIAS_PULL_UP		= _BITULL(8),
	GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN	= _BITULL(9),
	GPIO_V2_LINE_FLAG_BIAS_DISABLED		= _BITULL(10),
	GPIO_V2_LINE_FLAG_EVENT_CLOCK_REALTIME	= _BITULL(11),
पूर्ण;

/**
 * काष्ठा gpio_v2_line_values - Values of GPIO lines
 * @bits: a biपंचांगap containing the value of the lines, set to 1 क्रम active
 * and 0 क्रम inactive.
 * @mask: a biपंचांगap identअगरying the lines to get or set, with each bit
 * number corresponding to the index पूर्णांकo &काष्ठा
 * gpio_v2_line_request.offsets.
 */
काष्ठा gpio_v2_line_values अणु
	__aligned_u64 bits;
	__aligned_u64 mask;
पूर्ण;

/**
 * क्रमागत gpio_v2_line_attr_id - &काष्ठा gpio_v2_line_attribute.id values
 * identअगरying which field of the attribute जोड़ is in use.
 * @GPIO_V2_LINE_ATTR_ID_FLAGS: flags field is in use
 * @GPIO_V2_LINE_ATTR_ID_OUTPUT_VALUES: values field is in use
 * @GPIO_V2_LINE_ATTR_ID_DEBOUNCE: debounce_period_us field is in use
 */
क्रमागत gpio_v2_line_attr_id अणु
	GPIO_V2_LINE_ATTR_ID_FLAGS		= 1,
	GPIO_V2_LINE_ATTR_ID_OUTPUT_VALUES	= 2,
	GPIO_V2_LINE_ATTR_ID_DEBOUNCE		= 3,
पूर्ण;

/**
 * काष्ठा gpio_v2_line_attribute - a configurable attribute of a line
 * @id: attribute identअगरier with value from &क्रमागत gpio_v2_line_attr_id
 * @padding: reserved क्रम future use and must be zero filled
 * @flags: अगर id is %GPIO_V2_LINE_ATTR_ID_FLAGS, the flags क्रम the GPIO
 * line, with values from &क्रमागत gpio_v2_line_flag, such as
 * %GPIO_V2_LINE_FLAG_ACTIVE_LOW, %GPIO_V2_LINE_FLAG_OUTPUT etc, added
 * together.  This overrides the शेष flags contained in the &काष्ठा
 * gpio_v2_line_config क्रम the associated line.
 * @values: अगर id is %GPIO_V2_LINE_ATTR_ID_OUTPUT_VALUES, a biपंचांगap
 * containing the values to which the lines will be set, with each bit
 * number corresponding to the index पूर्णांकo &काष्ठा
 * gpio_v2_line_request.offsets.
 * @debounce_period_us: अगर id is %GPIO_V2_LINE_ATTR_ID_DEBOUNCE, the
 * desired debounce period, in microseconds
 */
काष्ठा gpio_v2_line_attribute अणु
	__u32 id;
	__u32 padding;
	जोड़ अणु
		__aligned_u64 flags;
		__aligned_u64 values;
		__u32 debounce_period_us;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा gpio_v2_line_config_attribute - a configuration attribute
 * associated with one or more of the requested lines.
 * @attr: the configurable attribute
 * @mask: a biपंचांगap identअगरying the lines to which the attribute applies,
 * with each bit number corresponding to the index पूर्णांकo &काष्ठा
 * gpio_v2_line_request.offsets.
 */
काष्ठा gpio_v2_line_config_attribute अणु
	काष्ठा gpio_v2_line_attribute attr;
	__aligned_u64 mask;
पूर्ण;

/**
 * काष्ठा gpio_v2_line_config - Configuration क्रम GPIO lines
 * @flags: flags क्रम the GPIO lines, with values from &क्रमागत
 * gpio_v2_line_flag, such as %GPIO_V2_LINE_FLAG_ACTIVE_LOW,
 * %GPIO_V2_LINE_FLAG_OUTPUT etc, added together.  This is the शेष क्रम
 * all requested lines but may be overridden क्रम particular lines using
 * @attrs.
 * @num_attrs: the number of attributes in @attrs
 * @padding: reserved क्रम future use and must be zero filled
 * @attrs: the configuration attributes associated with the requested
 * lines.  Any attribute should only be associated with a particular line
 * once.  If an attribute is associated with a line multiple बार then the
 * first occurrence (i.e. lowest index) has precedence.
 */
काष्ठा gpio_v2_line_config अणु
	__aligned_u64 flags;
	__u32 num_attrs;
	/* Pad to fill implicit padding and reserve space क्रम future use. */
	__u32 padding[5];
	काष्ठा gpio_v2_line_config_attribute attrs[GPIO_V2_LINE_NUM_ATTRS_MAX];
पूर्ण;

/**
 * काष्ठा gpio_v2_line_request - Inक्रमmation about a request क्रम GPIO lines
 * @offsets: an array of desired lines, specअगरied by offset index क्रम the
 * associated GPIO chip
 * @consumer: a desired consumer label क्रम the selected GPIO lines such as
 * "my-bitbanged-relay"
 * @config: requested configuration क्रम the lines.
 * @num_lines: number of lines requested in this request, i.e. the number
 * of valid fields in the %GPIO_V2_LINES_MAX sized arrays, set to 1 to
 * request a single line
 * @event_buffer_size: a suggested minimum number of line events that the
 * kernel should buffer.  This is only relevant अगर edge detection is
 * enabled in the configuration. Note that this is only a suggested value
 * and the kernel may allocate a larger buffer or cap the size of the
 * buffer. If this field is zero then the buffer size शेषs to a minimum
 * of @num_lines * 16.
 * @padding: reserved क्रम future use and must be zero filled
 * @fd: अगर successful this field will contain a valid anonymous file handle
 * after a %GPIO_GET_LINE_IOCTL operation, zero or negative value means
 * error
 */
काष्ठा gpio_v2_line_request अणु
	__u32 offsets[GPIO_V2_LINES_MAX];
	अक्षर consumer[GPIO_MAX_NAME_SIZE];
	काष्ठा gpio_v2_line_config config;
	__u32 num_lines;
	__u32 event_buffer_size;
	/* Pad to fill implicit padding and reserve space क्रम future use. */
	__u32 padding[5];
	__s32 fd;
पूर्ण;

/**
 * काष्ठा gpio_v2_line_info - Inक्रमmation about a certain GPIO line
 * @name: the name of this GPIO line, such as the output pin of the line on
 * the chip, a rail or a pin header name on a board, as specअगरied by the
 * GPIO chip, may be empty (i.e. name[0] == '\0')
 * @consumer: a functional name क्रम the consumer of this GPIO line as set
 * by whatever is using it, will be empty अगर there is no current user but
 * may also be empty अगर the consumer करोesn't set this up
 * @offset: the local offset on this GPIO chip, fill this in when
 * requesting the line inक्रमmation from the kernel
 * @num_attrs: the number of attributes in @attrs
 * @flags: flags क्रम this GPIO line, with values from &क्रमागत
 * gpio_v2_line_flag, such as %GPIO_V2_LINE_FLAG_ACTIVE_LOW,
 * %GPIO_V2_LINE_FLAG_OUTPUT etc, added together.
 * @attrs: the configuration attributes associated with the line
 * @padding: reserved क्रम future use
 */
काष्ठा gpio_v2_line_info अणु
	अक्षर name[GPIO_MAX_NAME_SIZE];
	अक्षर consumer[GPIO_MAX_NAME_SIZE];
	__u32 offset;
	__u32 num_attrs;
	__aligned_u64 flags;
	काष्ठा gpio_v2_line_attribute attrs[GPIO_V2_LINE_NUM_ATTRS_MAX];
	/* Space reserved क्रम future use. */
	__u32 padding[4];
पूर्ण;

/**
 * क्रमागत gpio_v2_line_changed_type - &काष्ठा gpio_v2_line_changed.event_type
 * values
 * @GPIO_V2_LINE_CHANGED_REQUESTED: line has been requested
 * @GPIO_V2_LINE_CHANGED_RELEASED: line has been released
 * @GPIO_V2_LINE_CHANGED_CONFIG: line has been reconfigured
 */
क्रमागत gpio_v2_line_changed_type अणु
	GPIO_V2_LINE_CHANGED_REQUESTED	= 1,
	GPIO_V2_LINE_CHANGED_RELEASED	= 2,
	GPIO_V2_LINE_CHANGED_CONFIG	= 3,
पूर्ण;

/**
 * काष्ठा gpio_v2_line_info_changed - Inक्रमmation about a change in status
 * of a GPIO line
 * @info: updated line inक्रमmation
 * @बारtamp_ns: estimate of समय of status change occurrence, in nanoseconds
 * @event_type: the type of change with a value from &क्रमागत
 * gpio_v2_line_changed_type
 * @padding: reserved क्रम future use
 */
काष्ठा gpio_v2_line_info_changed अणु
	काष्ठा gpio_v2_line_info info;
	__aligned_u64 बारtamp_ns;
	__u32 event_type;
	/* Pad काष्ठा to 64-bit boundary and reserve space क्रम future use. */
	__u32 padding[5];
पूर्ण;

/**
 * क्रमागत gpio_v2_line_event_id - &काष्ठा gpio_v2_line_event.id values
 * @GPIO_V2_LINE_EVENT_RISING_EDGE: event triggered by a rising edge
 * @GPIO_V2_LINE_EVENT_FALLING_EDGE: event triggered by a falling edge
 */
क्रमागत gpio_v2_line_event_id अणु
	GPIO_V2_LINE_EVENT_RISING_EDGE	= 1,
	GPIO_V2_LINE_EVENT_FALLING_EDGE	= 2,
पूर्ण;

/**
 * काष्ठा gpio_v2_line_event - The actual event being pushed to userspace
 * @बारtamp_ns: best estimate of समय of event occurrence, in nanoseconds.
 * @id: event identअगरier with value from &क्रमागत gpio_v2_line_event_id
 * @offset: the offset of the line that triggered the event
 * @seqno: the sequence number क्रम this event in the sequence of events क्रम
 * all the lines in this line request
 * @line_seqno: the sequence number क्रम this event in the sequence of
 * events on this particular line
 * @padding: reserved क्रम future use
 *
 * By शेष the @बारtamp_ns is पढ़ो from %CLOCK_MONOTONIC and is
 * पूर्णांकended to allow the accurate measurement of the समय between events.
 * It करोes not provide the wall-घड़ी समय.
 *
 * If the %GPIO_V2_LINE_FLAG_EVENT_CLOCK_REALTIME flag is set then the
 * @बारtamp_ns is पढ़ो from %CLOCK_REALTIME.
 */
काष्ठा gpio_v2_line_event अणु
	__aligned_u64 बारtamp_ns;
	__u32 id;
	__u32 offset;
	__u32 seqno;
	__u32 line_seqno;
	/* Space reserved क्रम future use. */
	__u32 padding[6];
पूर्ण;

/*
 * ABI v1
 *
 * This version of the ABI is deprecated.
 * Use the latest version of the ABI, defined above, instead.
 */

/* Inक्रमmational flags */
#घोषणा GPIOLINE_FLAG_KERNEL		(1UL << 0) /* Line used by the kernel */
#घोषणा GPIOLINE_FLAG_IS_OUT		(1UL << 1)
#घोषणा GPIOLINE_FLAG_ACTIVE_LOW	(1UL << 2)
#घोषणा GPIOLINE_FLAG_OPEN_DRAIN	(1UL << 3)
#घोषणा GPIOLINE_FLAG_OPEN_SOURCE	(1UL << 4)
#घोषणा GPIOLINE_FLAG_BIAS_PULL_UP	(1UL << 5)
#घोषणा GPIOLINE_FLAG_BIAS_PULL_DOWN	(1UL << 6)
#घोषणा GPIOLINE_FLAG_BIAS_DISABLE	(1UL << 7)

/**
 * काष्ठा gpioline_info - Inक्रमmation about a certain GPIO line
 * @line_offset: the local offset on this GPIO device, fill this in when
 * requesting the line inक्रमmation from the kernel
 * @flags: various flags क्रम this line
 * @name: the name of this GPIO line, such as the output pin of the line on the
 * chip, a rail or a pin header name on a board, as specअगरied by the gpio
 * chip, may be empty (i.e. name[0] == '\0')
 * @consumer: a functional name क्रम the consumer of this GPIO line as set by
 * whatever is using it, will be empty अगर there is no current user but may
 * also be empty अगर the consumer करोesn't set this up
 *
 * Note: This काष्ठा is part of ABI v1 and is deprecated.
 * Use &काष्ठा gpio_v2_line_info instead.
 */
काष्ठा gpioline_info अणु
	__u32 line_offset;
	__u32 flags;
	अक्षर name[GPIO_MAX_NAME_SIZE];
	अक्षर consumer[GPIO_MAX_NAME_SIZE];
पूर्ण;

/* Maximum number of requested handles */
#घोषणा GPIOHANDLES_MAX 64

/* Possible line status change events */
क्रमागत अणु
	GPIOLINE_CHANGED_REQUESTED = 1,
	GPIOLINE_CHANGED_RELEASED,
	GPIOLINE_CHANGED_CONFIG,
पूर्ण;

/**
 * काष्ठा gpioline_info_changed - Inक्रमmation about a change in status
 * of a GPIO line
 * @info: updated line inक्रमmation
 * @बारtamp: estimate of समय of status change occurrence, in nanoseconds
 * @event_type: one of %GPIOLINE_CHANGED_REQUESTED,
 * %GPIOLINE_CHANGED_RELEASED and %GPIOLINE_CHANGED_CONFIG
 * @padding: reserved क्रम future use
 *
 * The &काष्ठा gpioline_info embedded here has 32-bit alignment on its own,
 * but it works fine with 64-bit alignment too. With its 72 byte size, we can
 * guarantee there are no implicit holes between it and subsequent members.
 * The 20-byte padding at the end makes sure we करोn't add any implicit padding
 * at the end of the काष्ठाure on 64-bit architectures.
 *
 * Note: This काष्ठा is part of ABI v1 and is deprecated.
 * Use &काष्ठा gpio_v2_line_info_changed instead.
 */
काष्ठा gpioline_info_changed अणु
	काष्ठा gpioline_info info;
	__u64 बारtamp;
	__u32 event_type;
	__u32 padding[5]; /* क्रम future use */
पूर्ण;

/* Linerequest flags */
#घोषणा GPIOHANDLE_REQUEST_INPUT	(1UL << 0)
#घोषणा GPIOHANDLE_REQUEST_OUTPUT	(1UL << 1)
#घोषणा GPIOHANDLE_REQUEST_ACTIVE_LOW	(1UL << 2)
#घोषणा GPIOHANDLE_REQUEST_OPEN_DRAIN	(1UL << 3)
#घोषणा GPIOHANDLE_REQUEST_OPEN_SOURCE	(1UL << 4)
#घोषणा GPIOHANDLE_REQUEST_BIAS_PULL_UP	(1UL << 5)
#घोषणा GPIOHANDLE_REQUEST_BIAS_PULL_DOWN	(1UL << 6)
#घोषणा GPIOHANDLE_REQUEST_BIAS_DISABLE	(1UL << 7)

/**
 * काष्ठा gpiohandle_request - Inक्रमmation about a GPIO handle request
 * @lineoffsets: an array of desired lines, specअगरied by offset index क्रम the
 * associated GPIO device
 * @flags: desired flags क्रम the desired GPIO lines, such as
 * %GPIOHANDLE_REQUEST_OUTPUT, %GPIOHANDLE_REQUEST_ACTIVE_LOW etc, added
 * together. Note that even अगर multiple lines are requested, the same flags
 * must be applicable to all of them, अगर you want lines with inभागidual
 * flags set, request them one by one. It is possible to select
 * a batch of input or output lines, but they must all have the same
 * अक्षरacteristics, i.e. all inमाला_दो or all outमाला_दो, all active low etc
 * @शेष_values: अगर the %GPIOHANDLE_REQUEST_OUTPUT is set क्रम a requested
 * line, this specअगरies the शेष output value, should be 0 (low) or
 * 1 (high), anything अन्यथा than 0 or 1 will be पूर्णांकerpreted as 1 (high)
 * @consumer_label: a desired consumer label क्रम the selected GPIO line(s)
 * such as "my-bitbanged-relay"
 * @lines: number of lines requested in this request, i.e. the number of
 * valid fields in the above arrays, set to 1 to request a single line
 * @fd: अगर successful this field will contain a valid anonymous file handle
 * after a %GPIO_GET_LINEHANDLE_IOCTL operation, zero or negative value
 * means error
 *
 * Note: This काष्ठा is part of ABI v1 and is deprecated.
 * Use &काष्ठा gpio_v2_line_request instead.
 */
काष्ठा gpiohandle_request अणु
	__u32 lineoffsets[GPIOHANDLES_MAX];
	__u32 flags;
	__u8 शेष_values[GPIOHANDLES_MAX];
	अक्षर consumer_label[GPIO_MAX_NAME_SIZE];
	__u32 lines;
	पूर्णांक fd;
पूर्ण;

/**
 * काष्ठा gpiohandle_config - Configuration क्रम a GPIO handle request
 * @flags: updated flags क्रम the requested GPIO lines, such as
 * %GPIOHANDLE_REQUEST_OUTPUT, %GPIOHANDLE_REQUEST_ACTIVE_LOW etc, added
 * together
 * @शेष_values: अगर the %GPIOHANDLE_REQUEST_OUTPUT is set in flags,
 * this specअगरies the शेष output value, should be 0 (low) or
 * 1 (high), anything अन्यथा than 0 or 1 will be पूर्णांकerpreted as 1 (high)
 * @padding: reserved क्रम future use and should be zero filled
 *
 * Note: This काष्ठा is part of ABI v1 and is deprecated.
 * Use &काष्ठा gpio_v2_line_config instead.
 */
काष्ठा gpiohandle_config अणु
	__u32 flags;
	__u8 शेष_values[GPIOHANDLES_MAX];
	__u32 padding[4]; /* padding क्रम future use */
पूर्ण;

/**
 * काष्ठा gpiohandle_data - Inक्रमmation of values on a GPIO handle
 * @values: when getting the state of lines this contains the current
 * state of a line, when setting the state of lines these should contain
 * the desired target state
 *
 * Note: This काष्ठा is part of ABI v1 and is deprecated.
 * Use &काष्ठा gpio_v2_line_values instead.
 */
काष्ठा gpiohandle_data अणु
	__u8 values[GPIOHANDLES_MAX];
पूर्ण;

/* Eventrequest flags */
#घोषणा GPIOEVENT_REQUEST_RISING_EDGE	(1UL << 0)
#घोषणा GPIOEVENT_REQUEST_FALLING_EDGE	(1UL << 1)
#घोषणा GPIOEVENT_REQUEST_BOTH_EDGES	((1UL << 0) | (1UL << 1))

/**
 * काष्ठा gpioevent_request - Inक्रमmation about a GPIO event request
 * @lineoffset: the desired line to subscribe to events from, specअगरied by
 * offset index क्रम the associated GPIO device
 * @handleflags: desired handle flags क्रम the desired GPIO line, such as
 * %GPIOHANDLE_REQUEST_ACTIVE_LOW or %GPIOHANDLE_REQUEST_OPEN_DRAIN
 * @eventflags: desired flags क्रम the desired GPIO event line, such as
 * %GPIOEVENT_REQUEST_RISING_EDGE or %GPIOEVENT_REQUEST_FALLING_EDGE
 * @consumer_label: a desired consumer label क्रम the selected GPIO line(s)
 * such as "my-listener"
 * @fd: अगर successful this field will contain a valid anonymous file handle
 * after a %GPIO_GET_LINEEVENT_IOCTL operation, zero or negative value
 * means error
 *
 * Note: This काष्ठा is part of ABI v1 and is deprecated.
 * Use &काष्ठा gpio_v2_line_request instead.
 */
काष्ठा gpioevent_request अणु
	__u32 lineoffset;
	__u32 handleflags;
	__u32 eventflags;
	अक्षर consumer_label[GPIO_MAX_NAME_SIZE];
	पूर्णांक fd;
पूर्ण;

/*
 * GPIO event types
 */
#घोषणा GPIOEVENT_EVENT_RISING_EDGE 0x01
#घोषणा GPIOEVENT_EVENT_FALLING_EDGE 0x02

/**
 * काष्ठा gpioevent_data - The actual event being pushed to userspace
 * @बारtamp: best estimate of समय of event occurrence, in nanoseconds
 * @id: event identअगरier
 *
 * Note: This काष्ठा is part of ABI v1 and is deprecated.
 * Use &काष्ठा gpio_v2_line_event instead.
 */
काष्ठा gpioevent_data अणु
	__u64 बारtamp;
	__u32 id;
पूर्ण;

/*
 * v1 and v2 ioctl()s
 */
#घोषणा GPIO_GET_CHIPINFO_IOCTL _IOR(0xB4, 0x01, काष्ठा gpiochip_info)
#घोषणा GPIO_GET_LINEINFO_UNWATCH_IOCTL _IOWR(0xB4, 0x0C, __u32)

/*
 * v2 ioctl()s
 */
#घोषणा GPIO_V2_GET_LINEINFO_IOCTL _IOWR(0xB4, 0x05, काष्ठा gpio_v2_line_info)
#घोषणा GPIO_V2_GET_LINEINFO_WATCH_IOCTL _IOWR(0xB4, 0x06, काष्ठा gpio_v2_line_info)
#घोषणा GPIO_V2_GET_LINE_IOCTL _IOWR(0xB4, 0x07, काष्ठा gpio_v2_line_request)
#घोषणा GPIO_V2_LINE_SET_CONFIG_IOCTL _IOWR(0xB4, 0x0D, काष्ठा gpio_v2_line_config)
#घोषणा GPIO_V2_LINE_GET_VALUES_IOCTL _IOWR(0xB4, 0x0E, काष्ठा gpio_v2_line_values)
#घोषणा GPIO_V2_LINE_SET_VALUES_IOCTL _IOWR(0xB4, 0x0F, काष्ठा gpio_v2_line_values)

/*
 * v1 ioctl()s
 *
 * These ioctl()s are deprecated.  Use the v2 equivalent instead.
 */
#घोषणा GPIO_GET_LINEINFO_IOCTL _IOWR(0xB4, 0x02, काष्ठा gpioline_info)
#घोषणा GPIO_GET_LINEHANDLE_IOCTL _IOWR(0xB4, 0x03, काष्ठा gpiohandle_request)
#घोषणा GPIO_GET_LINEEVENT_IOCTL _IOWR(0xB4, 0x04, काष्ठा gpioevent_request)
#घोषणा GPIOHANDLE_GET_LINE_VALUES_IOCTL _IOWR(0xB4, 0x08, काष्ठा gpiohandle_data)
#घोषणा GPIOHANDLE_SET_LINE_VALUES_IOCTL _IOWR(0xB4, 0x09, काष्ठा gpiohandle_data)
#घोषणा GPIOHANDLE_SET_CONFIG_IOCTL _IOWR(0xB4, 0x0A, काष्ठा gpiohandle_config)
#घोषणा GPIO_GET_LINEINFO_WATCH_IOCTL _IOWR(0xB4, 0x0B, काष्ठा gpioline_info)

#पूर्ण_अगर /* _UAPI_GPIO_H_ */
