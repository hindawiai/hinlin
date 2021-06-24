<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ffs-test.c -- user mode fileप्रणाली api क्रम usb composite function
 *
 * Copyright (C) 2010 Samsung Electronics
 *                    Author: Michal Nazarewicz <mina86@mina86.com>
 */

/* $(CROSS_COMPILE)cc -Wall -Wextra -g -o ffs-test ffs-test.c -lpthपढ़ो */


#घोषणा _DEFAULT_SOURCE /* क्रम endian.h */

#समावेश <endian.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <tools/le_byteshअगरt.h>

#समावेश "../../include/uapi/linux/usb/functionfs.h"


/******************** Little Endian Handling ********************************/

/*
 * cpu_to_le16/32 are used when initializing काष्ठाures, a context where a
 * function call is not allowed. To solve this, we code cpu_to_le16/32 in a way
 * that allows them to be used when initializing काष्ठाures.
 */

#अगर __BYTE_ORDER == __LITTLE_ENDIAN
#घोषणा cpu_to_le16(x)  (x)
#घोषणा cpu_to_le32(x)  (x)
#अन्यथा
#घोषणा cpu_to_le16(x)  ((((x) >> 8) & 0xffu) | (((x) & 0xffu) << 8))
#घोषणा cpu_to_le32(x)  \
	((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >>  8) | \
	(((x) & 0x0000ff00u) <<  8) | (((x) & 0x000000ffu) << 24))
#पूर्ण_अगर

#घोषणा le32_to_cpu(x)  le32toh(x)
#घोषणा le16_to_cpu(x)  le16toh(x)

/******************** Messages and Errors ***********************************/

अटल स्थिर अक्षर argv0[] = "ffs-test";

अटल अचिन्हित verbosity = 7;

अटल व्योम _msg(अचिन्हित level, स्थिर अक्षर *fmt, ...)
अणु
	अगर (level < 2)
		level = 2;
	अन्यथा अगर (level > 7)
		level = 7;

	अगर (level <= verbosity) अणु
		अटल स्थिर अक्षर levels[8][6] = अणु
			[2] = "crit:",
			[3] = "err: ",
			[4] = "warn:",
			[5] = "note:",
			[6] = "info:",
			[7] = "dbg: "
		पूर्ण;

		पूर्णांक _त्रुटि_सं = त्रुटि_सं;
		बहु_सूची ap;

		ख_लिखो(मानक_त्रुटि, "%s: %s ", argv0, levels[level]);
		बहु_शुरू(ap, fmt);
		भख_लिखो(मानक_त्रुटि, fmt, ap);
		बहु_पूर्ण(ap);

		अगर (fmt[म_माप(fmt) - 1] != '\n') अणु
			अक्षर buffer[128];
			म_त्रुटि_r(_त्रुटि_सं, buffer, माप buffer);
			ख_लिखो(मानक_त्रुटि, ": (-%d) %s\n", _त्रुटि_सं, buffer);
		पूर्ण

		ख_साफ(मानक_त्रुटि);
	पूर्ण
पूर्ण

#घोषणा die(...)  (_msg(2, __VA_ARGS__), निकास(1))
#घोषणा err(...)   _msg(3, __VA_ARGS__)
#घोषणा warn(...)  _msg(4, __VA_ARGS__)
#घोषणा note(...)  _msg(5, __VA_ARGS__)
#घोषणा info(...)  _msg(6, __VA_ARGS__)
#घोषणा debug(...) _msg(7, __VA_ARGS__)

#घोषणा die_on(cond, ...) करो अणु \
	अगर (cond) \
		die(__VA_ARGS__); \
	पूर्ण जबतक (0)


/******************** Descriptors and Strings *******************************/

अटल स्थिर काष्ठा अणु
	काष्ठा usb_functionfs_descs_head_v2 header;
	__le32 fs_count;
	__le32 hs_count;
	__le32 ss_count;
	काष्ठा अणु
		काष्ठा usb_पूर्णांकerface_descriptor पूर्णांकf;
		काष्ठा usb_endpoपूर्णांक_descriptor_no_audio sink;
		काष्ठा usb_endpoपूर्णांक_descriptor_no_audio source;
	पूर्ण __attribute__((packed)) fs_descs, hs_descs;
	काष्ठा अणु
		काष्ठा usb_पूर्णांकerface_descriptor पूर्णांकf;
		काष्ठा usb_endpoपूर्णांक_descriptor_no_audio sink;
		काष्ठा usb_ss_ep_comp_descriptor sink_comp;
		काष्ठा usb_endpoपूर्णांक_descriptor_no_audio source;
		काष्ठा usb_ss_ep_comp_descriptor source_comp;
	पूर्ण ss_descs;
पूर्ण __attribute__((packed)) descriptors = अणु
	.header = अणु
		.magic = cpu_to_le32(FUNCTIONFS_DESCRIPTORS_MAGIC_V2),
		.flags = cpu_to_le32(FUNCTIONFS_HAS_FS_DESC |
				     FUNCTIONFS_HAS_HS_DESC |
				     FUNCTIONFS_HAS_SS_DESC),
		.length = cpu_to_le32(माप descriptors),
	पूर्ण,
	.fs_count = cpu_to_le32(3),
	.fs_descs = अणु
		.पूर्णांकf = अणु
			.bLength = माप descriptors.fs_descs.पूर्णांकf,
			.bDescriptorType = USB_DT_INTERFACE,
			.bNumEndpoपूर्णांकs = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.iInterface = 1,
		पूर्ण,
		.sink = अणु
			.bLength = माप descriptors.fs_descs.sink,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 1 | USB_सूची_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			/* .wMaxPacketSize = स्वतःconfiguration (kernel) */
		पूर्ण,
		.source = अणु
			.bLength = माप descriptors.fs_descs.source,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 2 | USB_सूची_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			/* .wMaxPacketSize = स्वतःconfiguration (kernel) */
		पूर्ण,
	पूर्ण,
	.hs_count = cpu_to_le32(3),
	.hs_descs = अणु
		.पूर्णांकf = अणु
			.bLength = माप descriptors.fs_descs.पूर्णांकf,
			.bDescriptorType = USB_DT_INTERFACE,
			.bNumEndpoपूर्णांकs = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.iInterface = 1,
		पूर्ण,
		.sink = अणु
			.bLength = माप descriptors.hs_descs.sink,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 1 | USB_सूची_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = cpu_to_le16(512),
		पूर्ण,
		.source = अणु
			.bLength = माप descriptors.hs_descs.source,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 2 | USB_सूची_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = cpu_to_le16(512),
			.bInterval = 1, /* NAK every 1 uframe */
		पूर्ण,
	पूर्ण,
	.ss_count = cpu_to_le32(5),
	.ss_descs = अणु
		.पूर्णांकf = अणु
			.bLength = माप descriptors.fs_descs.पूर्णांकf,
			.bDescriptorType = USB_DT_INTERFACE,
			.bNumEndpoपूर्णांकs = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.iInterface = 1,
		पूर्ण,
		.sink = अणु
			.bLength = माप descriptors.hs_descs.sink,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 1 | USB_सूची_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = cpu_to_le16(1024),
		पूर्ण,
		.sink_comp = अणु
			.bLength = USB_DT_SS_EP_COMP_SIZE,
			.bDescriptorType = USB_DT_SS_ENDPOINT_COMP,
			.bMaxBurst = 0,
			.bmAttributes = 0,
			.wBytesPerInterval = 0,
		पूर्ण,
		.source = अणु
			.bLength = माप descriptors.hs_descs.source,
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 2 | USB_सूची_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = cpu_to_le16(1024),
			.bInterval = 1, /* NAK every 1 uframe */
		पूर्ण,
		.source_comp = अणु
			.bLength = USB_DT_SS_EP_COMP_SIZE,
			.bDescriptorType = USB_DT_SS_ENDPOINT_COMP,
			.bMaxBurst = 0,
			.bmAttributes = 0,
			.wBytesPerInterval = 0,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल माप_प्रकार descs_to_legacy(व्योम **legacy, स्थिर व्योम *descriptors_v2)
अणु
	स्थिर अचिन्हित अक्षर *descs_end, *descs_start;
	__u32 length, fs_count = 0, hs_count = 0, count;

	/* Read v2 header */
	अणु
		स्थिर काष्ठा अणु
			स्थिर काष्ठा usb_functionfs_descs_head_v2 header;
			स्थिर __le32 counts[];
		पूर्ण __attribute__((packed)) *स्थिर in = descriptors_v2;
		स्थिर __le32 *counts = in->counts;
		__u32 flags;

		अगर (le32_to_cpu(in->header.magic) !=
		    FUNCTIONFS_DESCRIPTORS_MAGIC_V2)
			वापस 0;
		length = le32_to_cpu(in->header.length);
		अगर (length <= माप in->header)
			वापस 0;
		length -= माप in->header;
		flags = le32_to_cpu(in->header.flags);
		अगर (flags & ~(FUNCTIONFS_HAS_FS_DESC | FUNCTIONFS_HAS_HS_DESC |
			      FUNCTIONFS_HAS_SS_DESC))
			वापस 0;

#घोषणा GET_NEXT_COUNT_IF_FLAG(ret, flg) करो अणु		\
			अगर (!(flags & (flg)))		\
				अवरोध;			\
			अगर (length < 4)			\
				वापस 0;		\
			ret = le32_to_cpu(*counts);	\
			length -= 4;			\
			++counts;			\
		पूर्ण जबतक (0)

		GET_NEXT_COUNT_IF_FLAG(fs_count, FUNCTIONFS_HAS_FS_DESC);
		GET_NEXT_COUNT_IF_FLAG(hs_count, FUNCTIONFS_HAS_HS_DESC);
		GET_NEXT_COUNT_IF_FLAG(count, FUNCTIONFS_HAS_SS_DESC);

		count = fs_count + hs_count;
		अगर (!count)
			वापस 0;
		descs_start = (स्थिर व्योम *)counts;

#अघोषित GET_NEXT_COUNT_IF_FLAG
	पूर्ण

	/*
	 * Find the end of FS and HS USB descriptors.  SS descriptors
	 * are ignored since legacy क्रमmat करोes not support them.
	 */
	descs_end = descs_start;
	करो अणु
		अगर (length < *descs_end)
			वापस 0;
		length -= *descs_end;
		descs_end += *descs_end;
	पूर्ण जबतक (--count);

	/* Allocate legacy descriptors and copy the data. */
	अणु
#आशय GCC diagnostic push
#आशय GCC diagnostic ignored "-Wdeprecated-declarations"
		काष्ठा अणु
			काष्ठा usb_functionfs_descs_head header;
			__u8 descriptors[];
		पूर्ण __attribute__((packed)) *out;
#आशय GCC diagnostic pop

		length = माप out->header + (descs_end - descs_start);
		out = दो_स्मृति(length);
		out->header.magic = cpu_to_le32(FUNCTIONFS_DESCRIPTORS_MAGIC);
		out->header.length = cpu_to_le32(length);
		out->header.fs_count = cpu_to_le32(fs_count);
		out->header.hs_count = cpu_to_le32(hs_count);
		स_नकल(out->descriptors, descs_start, descs_end - descs_start);
		*legacy = out;
	पूर्ण

	वापस length;
पूर्ण


#घोषणा STR_INTERFACE_ "Source/Sink"

अटल स्थिर काष्ठा अणु
	काष्ठा usb_functionfs_strings_head header;
	काष्ठा अणु
		__le16 code;
		स्थिर अक्षर str1[माप STR_INTERFACE_];
	पूर्ण __attribute__((packed)) lang0;
पूर्ण __attribute__((packed)) strings = अणु
	.header = अणु
		.magic = cpu_to_le32(FUNCTIONFS_STRINGS_MAGIC),
		.length = cpu_to_le32(माप strings),
		.str_count = cpu_to_le32(1),
		.lang_count = cpu_to_le32(1),
	पूर्ण,
	.lang0 = अणु
		cpu_to_le16(0x0409), /* en-us */
		STR_INTERFACE_,
	पूर्ण,
पूर्ण;

#घोषणा STR_INTERFACE strings.lang0.str1


/******************** Files and Thपढ़ोs Handling ****************************/

काष्ठा thपढ़ो;

अटल sमाप_प्रकार पढ़ो_wrap(काष्ठा thपढ़ो *t, व्योम *buf, माप_प्रकार nbytes);
अटल sमाप_प्रकार ग_लिखो_wrap(काष्ठा thपढ़ो *t, स्थिर व्योम *buf, माप_प्रकार nbytes);
अटल sमाप_प्रकार ep0_consume(काष्ठा thपढ़ो *t, स्थिर व्योम *buf, माप_प्रकार nbytes);
अटल sमाप_प्रकार fill_in_buf(काष्ठा thपढ़ो *t, व्योम *buf, माप_प्रकार nbytes);
अटल sमाप_प्रकार empty_out_buf(काष्ठा thपढ़ो *t, स्थिर व्योम *buf, माप_प्रकार nbytes);


अटल काष्ठा thपढ़ो अणु
	स्थिर अक्षर *स्थिर filename;
	माप_प्रकार buf_size;

	sमाप_प्रकार (*in)(काष्ठा thपढ़ो *, व्योम *, माप_प्रकार);
	स्थिर अक्षर *स्थिर in_name;

	sमाप_प्रकार (*out)(काष्ठा thपढ़ो *, स्थिर व्योम *, माप_प्रकार);
	स्थिर अक्षर *स्थिर out_name;

	पूर्णांक fd;
	pthपढ़ो_t id;
	व्योम *buf;
	sमाप_प्रकार status;
पूर्ण thपढ़ोs[] = अणु
	अणु
		"ep0", 4 * माप(काष्ठा usb_functionfs_event),
		पढ़ो_wrap, शून्य,
		ep0_consume, "<consume>",
		0, 0, शून्य, 0
	पूर्ण,
	अणु
		"ep1", 8 * 1024,
		fill_in_buf, "<in>",
		ग_लिखो_wrap, शून्य,
		0, 0, शून्य, 0
	पूर्ण,
	अणु
		"ep2", 8 * 1024,
		पढ़ो_wrap, शून्य,
		empty_out_buf, "<out>",
		0, 0, शून्य, 0
	पूर्ण,
पूर्ण;


अटल व्योम init_thपढ़ो(काष्ठा thपढ़ो *t)
अणु
	t->buf = दो_स्मृति(t->buf_size);
	die_on(!t->buf, "malloc");

	t->fd = खोलो(t->filename, O_RDWR);
	die_on(t->fd < 0, "%s", t->filename);
पूर्ण

अटल व्योम cleanup_thपढ़ो(व्योम *arg)
अणु
	काष्ठा thपढ़ो *t = arg;
	पूर्णांक ret, fd;

	fd = t->fd;
	अगर (t->fd < 0)
		वापस;
	t->fd = -1;

	/* test the FIFO ioctls (non-ep0 code paths) */
	अगर (t != thपढ़ोs) अणु
		ret = ioctl(fd, FUNCTIONFS_FIFO_STATUS);
		अगर (ret < 0) अणु
			/* ENODEV reported after disconnect */
			अगर (त्रुटि_सं != ENODEV)
				err("%s: get fifo status", t->filename);
		पूर्ण अन्यथा अगर (ret) अणु
			warn("%s: unclaimed = %d\n", t->filename, ret);
			अगर (ioctl(fd, FUNCTIONFS_FIFO_FLUSH) < 0)
				err("%s: fifo flush", t->filename);
		पूर्ण
	पूर्ण

	अगर (बंद(fd) < 0)
		err("%s: close", t->filename);

	मुक्त(t->buf);
	t->buf = शून्य;
पूर्ण

अटल व्योम *start_thपढ़ो_helper(व्योम *arg)
अणु
	स्थिर अक्षर *name, *op, *in_name, *out_name;
	काष्ठा thपढ़ो *t = arg;
	sमाप_प्रकार ret;

	info("%s: starts\n", t->filename);
	in_name = t->in_name ? t->in_name : t->filename;
	out_name = t->out_name ? t->out_name : t->filename;

	pthपढ़ो_cleanup_push(cleanup_thपढ़ो, arg);

	क्रम (;;) अणु
		pthपढ़ो_testcancel();

		ret = t->in(t, t->buf, t->buf_size);
		अगर (ret > 0) अणु
			ret = t->out(t, t->buf, ret);
			name = out_name;
			op = "write";
		पूर्ण अन्यथा अणु
			name = in_name;
			op = "read";
		पूर्ण

		अगर (ret > 0) अणु
			/* nop */
		पूर्ण अन्यथा अगर (!ret) अणु
			debug("%s: %s: EOF", name, op);
			अवरोध;
		पूर्ण अन्यथा अगर (त्रुटि_सं == EINTR || त्रुटि_सं == EAGAIN) अणु
			debug("%s: %s", name, op);
		पूर्ण अन्यथा अणु
			warn("%s: %s", name, op);
			अवरोध;
		पूर्ण
	पूर्ण

	pthपढ़ो_cleanup_pop(1);

	t->status = ret;
	info("%s: ends\n", t->filename);
	वापस शून्य;
पूर्ण

अटल व्योम start_thपढ़ो(काष्ठा thपढ़ो *t)
अणु
	debug("%s: starting\n", t->filename);

	die_on(pthपढ़ो_create(&t->id, शून्य, start_thपढ़ो_helper, t) < 0,
	       "pthread_create(%s)", t->filename);
पूर्ण

अटल व्योम join_thपढ़ो(काष्ठा thपढ़ो *t)
अणु
	पूर्णांक ret = pthपढ़ो_join(t->id, शून्य);

	अगर (ret < 0)
		err("%s: joining thread", t->filename);
	अन्यथा
		debug("%s: joined\n", t->filename);
पूर्ण


अटल sमाप_प्रकार पढ़ो_wrap(काष्ठा thपढ़ो *t, व्योम *buf, माप_प्रकार nbytes)
अणु
	वापस पढ़ो(t->fd, buf, nbytes);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_wrap(काष्ठा thपढ़ो *t, स्थिर व्योम *buf, माप_प्रकार nbytes)
अणु
	वापस ग_लिखो(t->fd, buf, nbytes);
पूर्ण


/******************** Empty/Fill buffer routines ****************************/

/* 0 -- stream of zeros, 1 -- i % 63, 2 -- pipe */
क्रमागत pattern अणु PAT_ZERO, PAT_SEQ, PAT_PIPE पूर्ण;
अटल क्रमागत pattern pattern;

अटल sमाप_प्रकार
fill_in_buf(काष्ठा thपढ़ो *ignore, व्योम *buf, माप_प्रकार nbytes)
अणु
	माप_प्रकार i;
	__u8 *p;

	(व्योम)ignore;

	चयन (pattern) अणु
	हाल PAT_ZERO:
		स_रखो(buf, 0, nbytes);
		अवरोध;

	हाल PAT_SEQ:
		क्रम (p = buf, i = 0; i < nbytes; ++i, ++p)
			*p = i % 63;
		अवरोध;

	हाल PAT_PIPE:
		वापस ख_पढ़ो(buf, 1, nbytes, मानक_निवेश);
	पूर्ण

	वापस nbytes;
पूर्ण

अटल sमाप_प्रकार
empty_out_buf(काष्ठा thपढ़ो *ignore, स्थिर व्योम *buf, माप_प्रकार nbytes)
अणु
	स्थिर __u8 *p;
	__u8 expected;
	sमाप_प्रकार ret;
	माप_प्रकार len;

	(व्योम)ignore;

	चयन (pattern) अणु
	हाल PAT_ZERO:
		expected = 0;
		क्रम (p = buf, len = 0; len < nbytes; ++p, ++len)
			अगर (*p)
				जाओ invalid;
		अवरोध;

	हाल PAT_SEQ:
		क्रम (p = buf, len = 0; len < nbytes; ++p, ++len)
			अगर (*p != len % 63) अणु
				expected = len % 63;
				जाओ invalid;
			पूर्ण
		अवरोध;

	हाल PAT_PIPE:
		ret = ख_डालो(buf, nbytes, 1, मानक_निकास);
		अगर (ret > 0)
			ख_साफ(मानक_निकास);
		अवरोध;

invalid:
		err("bad OUT byte %zd, expected %02x got %02x\n",
		    len, expected, *p);
		क्रम (p = buf, len = 0; len < nbytes; ++p, ++len) अणु
			अगर (0 == (len % 32))
				ख_लिखो(मानक_त्रुटि, "%4zd:", len);
			ख_लिखो(मानक_त्रुटि, " %02x", *p);
			अगर (31 == (len % 32))
				ख_लिखो(मानक_त्रुटि, "\n");
		पूर्ण
		ख_साफ(मानक_त्रुटि);
		त्रुटि_सं = EILSEQ;
		वापस -1;
	पूर्ण

	वापस len;
पूर्ण


/******************** Endpoपूर्णांकs routines ************************************/

अटल व्योम handle_setup(स्थिर काष्ठा usb_ctrlrequest *setup)
अणु
	म_लिखो("bRequestType = %d\n", setup->bRequestType);
	म_लिखो("bRequest     = %d\n", setup->bRequest);
	म_लिखो("wValue       = %d\n", le16_to_cpu(setup->wValue));
	म_लिखो("wIndex       = %d\n", le16_to_cpu(setup->wIndex));
	म_लिखो("wLength      = %d\n", le16_to_cpu(setup->wLength));
पूर्ण

अटल sमाप_प्रकार
ep0_consume(काष्ठा thपढ़ो *ignore, स्थिर व्योम *buf, माप_प्रकार nbytes)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		[FUNCTIONFS_BIND] = "BIND",
		[FUNCTIONFS_UNBIND] = "UNBIND",
		[FUNCTIONFS_ENABLE] = "ENABLE",
		[FUNCTIONFS_DISABLE] = "DISABLE",
		[FUNCTIONFS_SETUP] = "SETUP",
		[FUNCTIONFS_SUSPEND] = "SUSPEND",
		[FUNCTIONFS_RESUME] = "RESUME",
	पूर्ण;

	स्थिर काष्ठा usb_functionfs_event *event = buf;
	माप_प्रकार n;

	(व्योम)ignore;

	क्रम (n = nbytes / माप *event; n; --n, ++event)
		चयन (event->type) अणु
		हाल FUNCTIONFS_BIND:
		हाल FUNCTIONFS_UNBIND:
		हाल FUNCTIONFS_ENABLE:
		हाल FUNCTIONFS_DISABLE:
		हाल FUNCTIONFS_SETUP:
		हाल FUNCTIONFS_SUSPEND:
		हाल FUNCTIONFS_RESUME:
			म_लिखो("Event %s\n", names[event->type]);
			अगर (event->type == FUNCTIONFS_SETUP)
				handle_setup(&event->u.setup);
			अवरोध;

		शेष:
			म_लिखो("Event %03u (unknown)\n", event->type);
		पूर्ण

	वापस nbytes;
पूर्ण

अटल व्योम ep0_init(काष्ठा thपढ़ो *t, bool legacy_descriptors)
अणु
	व्योम *legacy;
	sमाप_प्रकार ret;
	माप_प्रकार len;

	अगर (legacy_descriptors) अणु
		info("%s: writing descriptors\n", t->filename);
		जाओ legacy;
	पूर्ण

	info("%s: writing descriptors (in v2 format)\n", t->filename);
	ret = ग_लिखो(t->fd, &descriptors, माप descriptors);

	अगर (ret < 0 && त्रुटि_सं == EINVAL) अणु
		warn("%s: new format rejected, trying legacy\n", t->filename);
legacy:
		len = descs_to_legacy(&legacy, &descriptors);
		अगर (len) अणु
			ret = ग_लिखो(t->fd, legacy, len);
			मुक्त(legacy);
		पूर्ण
	पूर्ण
	die_on(ret < 0, "%s: write: descriptors", t->filename);

	info("%s: writing strings\n", t->filename);
	ret = ग_लिखो(t->fd, &strings, माप strings);
	die_on(ret < 0, "%s: write: strings", t->filename);
पूर्ण


/******************** Main **************************************************/

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	bool legacy_descriptors;
	अचिन्हित i;

	legacy_descriptors = argc > 2 && !म_भेद(argv[1], "-l");

	init_thपढ़ो(thपढ़ोs);
	ep0_init(thपढ़ोs, legacy_descriptors);

	क्रम (i = 1; i < माप thपढ़ोs / माप *thपढ़ोs; ++i)
		init_thपढ़ो(thपढ़ोs + i);

	क्रम (i = 1; i < माप thपढ़ोs / माप *thपढ़ोs; ++i)
		start_thपढ़ो(thपढ़ोs + i);

	start_thपढ़ो_helper(thपढ़ोs);

	क्रम (i = 1; i < माप thपढ़ोs / माप *thपढ़ोs; ++i)
		join_thपढ़ो(thपढ़ोs + i);

	वापस 0;
पूर्ण
