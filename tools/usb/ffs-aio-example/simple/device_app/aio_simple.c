<शैली गुरु>
/*
 * This is मुक्त and unencumbered software released पूर्णांकo the खुला करोमुख्य.
 *
 * Anyone is मुक्त to copy, modअगरy, publish, use, compile, sell, or
 * distribute this software, either in source code क्रमm or as a compiled
 * binary, क्रम any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright पूर्णांकerest in the
 * software to the खुला करोमुख्य. We make this dedication क्रम the benefit
 * of the खुला at large and to the detriment of our heirs and
 * successors. We पूर्णांकend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more inक्रमmation, please refer to <http://unlicense.org/>
 */

#घोषणा _BSD_SOURCE /* क्रम endian.h */

#समावेश <endian.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/poll.h>
#समावेश <unistd.h>
#समावेश <stdbool.h>
#समावेश <sys/eventfd.h>

#समावेश "libaio.h"
#घोषणा IOCB_FLAG_RESFD         (1 << 0)

#समावेश <linux/usb/functionfs.h>

#घोषणा BUF_LEN		8192

/******************** Descriptors and Strings *******************************/

अटल स्थिर काष्ठा अणु
	काष्ठा usb_functionfs_descs_head_v2 header;
	__le32 fs_count;
	__le32 hs_count;
	काष्ठा अणु
		काष्ठा usb_पूर्णांकerface_descriptor पूर्णांकf;
		काष्ठा usb_endpoपूर्णांक_descriptor_no_audio bulk_sink;
		काष्ठा usb_endpoपूर्णांक_descriptor_no_audio bulk_source;
	पूर्ण __attribute__ ((__packed__)) fs_descs, hs_descs;
पूर्ण __attribute__ ((__packed__)) descriptors = अणु
	.header = अणु
		.magic = htole32(FUNCTIONFS_DESCRIPTORS_MAGIC_V2),
		.flags = htole32(FUNCTIONFS_HAS_FS_DESC |
				     FUNCTIONFS_HAS_HS_DESC),
		.length = htole32(माप(descriptors)),
	पूर्ण,
	.fs_count = htole32(3),
	.fs_descs = अणु
		.पूर्णांकf = अणु
			.bLength = माप(descriptors.fs_descs.पूर्णांकf),
			.bDescriptorType = USB_DT_INTERFACE,
			.bNumEndpoपूर्णांकs = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.iInterface = 1,
		पूर्ण,
		.bulk_sink = अणु
			.bLength = माप(descriptors.fs_descs.bulk_sink),
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 1 | USB_सूची_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
		पूर्ण,
		.bulk_source = अणु
			.bLength = माप(descriptors.fs_descs.bulk_source),
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 2 | USB_सूची_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
		पूर्ण,
	पूर्ण,
	.hs_count = htole32(3),
	.hs_descs = अणु
		.पूर्णांकf = अणु
			.bLength = माप(descriptors.hs_descs.पूर्णांकf),
			.bDescriptorType = USB_DT_INTERFACE,
			.bNumEndpoपूर्णांकs = 2,
			.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
			.iInterface = 1,
		पूर्ण,
		.bulk_sink = अणु
			.bLength = माप(descriptors.hs_descs.bulk_sink),
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 1 | USB_सूची_IN,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = htole16(512),
		पूर्ण,
		.bulk_source = अणु
			.bLength = माप(descriptors.hs_descs.bulk_source),
			.bDescriptorType = USB_DT_ENDPOINT,
			.bEndpoपूर्णांकAddress = 2 | USB_सूची_OUT,
			.bmAttributes = USB_ENDPOINT_XFER_BULK,
			.wMaxPacketSize = htole16(512),
		पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा STR_INTERFACE "AIO Test"

अटल स्थिर काष्ठा अणु
	काष्ठा usb_functionfs_strings_head header;
	काष्ठा अणु
		__le16 code;
		स्थिर अक्षर str1[माप(STR_INTERFACE)];
	पूर्ण __attribute__ ((__packed__)) lang0;
पूर्ण __attribute__ ((__packed__)) strings = अणु
	.header = अणु
		.magic = htole32(FUNCTIONFS_STRINGS_MAGIC),
		.length = htole32(माप(strings)),
		.str_count = htole32(1),
		.lang_count = htole32(1),
	पूर्ण,
	.lang0 = अणु
		htole16(0x0409), /* en-us */
		STR_INTERFACE,
	पूर्ण,
पूर्ण;

/******************** Endpoपूर्णांकs handling *******************************/

अटल व्योम display_event(काष्ठा usb_functionfs_event *event)
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
	चयन (event->type) अणु
	हाल FUNCTIONFS_BIND:
	हाल FUNCTIONFS_UNBIND:
	हाल FUNCTIONFS_ENABLE:
	हाल FUNCTIONFS_DISABLE:
	हाल FUNCTIONFS_SETUP:
	हाल FUNCTIONFS_SUSPEND:
	हाल FUNCTIONFS_RESUME:
		म_लिखो("Event %s\n", names[event->type]);
	पूर्ण
पूर्ण

अटल व्योम handle_ep0(पूर्णांक ep0, bool *पढ़ोy)
अणु
	काष्ठा usb_functionfs_event event;
	पूर्णांक ret;

	काष्ठा pollfd pfds[1];
	pfds[0].fd = ep0;
	pfds[0].events = POLLIN;

	ret = poll(pfds, 1, 0);

	अगर (ret && (pfds[0].revents & POLLIN)) अणु
		ret = पढ़ो(ep0, &event, माप(event));
		अगर (!ret) अणु
			लिखो_त्रुटि("unable to read event from ep0");
			वापस;
		पूर्ण
		display_event(&event);
		चयन (event.type) अणु
		हाल FUNCTIONFS_SETUP:
			अगर (event.u.setup.bRequestType & USB_सूची_IN)
				ग_लिखो(ep0, शून्य, 0);
			अन्यथा
				पढ़ो(ep0, शून्य, 0);
			अवरोध;

		हाल FUNCTIONFS_ENABLE:
			*पढ़ोy = true;
			अवरोध;

		हाल FUNCTIONFS_DISABLE:
			*पढ़ोy = false;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक i, ret;
	अक्षर *ep_path;

	पूर्णांक ep0;
	पूर्णांक ep[2];

	io_context_t ctx;

	पूर्णांक evfd;
	fd_set rfds;

	अक्षर *buf_in, *buf_out;
	काष्ठा iocb *iocb_in, *iocb_out;
	पूर्णांक req_in = 0, req_out = 0;
	bool पढ़ोy;

	अगर (argc != 2) अणु
		म_लिखो("ffs directory not specified!\n");
		वापस 1;
	पूर्ण

	ep_path = दो_स्मृति(म_माप(argv[1]) + 4 /* "/ep#" */ + 1 /* '\0' */);
	अगर (!ep_path) अणु
		लिखो_त्रुटि("malloc");
		वापस 1;
	पूर्ण

	/* खोलो endpoपूर्णांक files */
	प्र_लिखो(ep_path, "%s/ep0", argv[1]);
	ep0 = खोलो(ep_path, O_RDWR);
	अगर (ep0 < 0) अणु
		लिखो_त्रुटि("unable to open ep0");
		वापस 1;
	पूर्ण
	अगर (ग_लिखो(ep0, &descriptors, माप(descriptors)) < 0) अणु
		लिखो_त्रुटि("unable do write descriptors");
		वापस 1;
	पूर्ण
	अगर (ग_लिखो(ep0, &strings, माप(strings)) < 0) अणु
		लिखो_त्रुटि("unable to write strings");
		वापस 1;
	पूर्ण
	क्रम (i = 0; i < 2; ++i) अणु
		प्र_लिखो(ep_path, "%s/ep%d", argv[1], i+1);
		ep[i] = खोलो(ep_path, O_RDWR);
		अगर (ep[i] < 0) अणु
			म_लिखो("unable to open ep%d: %s\n", i+1,
			       म_त्रुटि(त्रुटि_सं));
			वापस 1;
		पूर्ण
	पूर्ण

	मुक्त(ep_path);

	स_रखो(&ctx, 0, माप(ctx));
	/* setup aio context to handle up to 2 requests */
	अगर (io_setup(2, &ctx) < 0) अणु
		लिखो_त्रुटि("unable to setup aio");
		वापस 1;
	पूर्ण

	evfd = eventfd(0, 0);
	अगर (evfd < 0) अणु
		लिखो_त्रुटि("unable to open eventfd");
		वापस 1;
	पूर्ण

	/* alloc buffers and requests */
	buf_in = दो_स्मृति(BUF_LEN);
	buf_out = दो_स्मृति(BUF_LEN);
	iocb_in = दो_स्मृति(माप(*iocb_in));
	iocb_out = दो_स्मृति(माप(*iocb_out));

	जबतक (1) अणु
		FD_ZERO(&rfds);
		FD_SET(ep0, &rfds);
		FD_SET(evfd, &rfds);

		ret = select(((ep0 > evfd) ? ep0 : evfd)+1,
			     &rfds, शून्य, शून्य, शून्य);
		अगर (ret < 0) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;
			लिखो_त्रुटि("select");
			अवरोध;
		पूर्ण

		अगर (FD_ISSET(ep0, &rfds))
			handle_ep0(ep0, &पढ़ोy);

		/* we are रुकोing क्रम function ENABLE */
		अगर (!पढ़ोy)
			जारी;

		/* अगर something was submitted we रुको क्रम event */
		अगर (FD_ISSET(evfd, &rfds)) अणु
			uपूर्णांक64_t ev_cnt;
			ret = पढ़ो(evfd, &ev_cnt, माप(ev_cnt));
			अगर (ret < 0) अणु
				लिखो_त्रुटि("unable to read eventfd");
				अवरोध;
			पूर्ण

			काष्ठा io_event e[2];
			/* we रुको क्रम one event */
			ret = io_getevents(ctx, 1, 2, e, शून्य);
			/* अगर we got event */
			क्रम (i = 0; i < ret; ++i) अणु
				अगर (e[i].obj->aio_fildes == ep[0]) अणु
					म_लिखो("ev=in; ret=%lu\n", e[i].res);
					req_in = 0;
				पूर्ण अन्यथा अगर (e[i].obj->aio_fildes == ep[1]) अणु
					म_लिखो("ev=out; ret=%lu\n", e[i].res);
					req_out = 0;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!req_in) अणु /* अगर IN transfer not requested*/
			/* prepare ग_लिखो request */
			io_prep_pग_लिखो(iocb_in, ep[0], buf_in, BUF_LEN, 0);
			/* enable eventfd notअगरication */
			iocb_in->u.c.flags |= IOCB_FLAG_RESFD;
			iocb_in->u.c.resfd = evfd;
			/* submit table of requests */
			ret = io_submit(ctx, 1, &iocb_in);
			अगर (ret >= 0) अणु /* अगर ret > 0 request is queued */
				req_in = 1;
				म_लिखो("submit: in\n");
			पूर्ण अन्यथा
				लिखो_त्रुटि("unable to submit request");
		पूर्ण
		अगर (!req_out) अणु /* अगर OUT transfer not requested */
			/* prepare पढ़ो request */
			io_prep_pपढ़ो(iocb_out, ep[1], buf_out, BUF_LEN, 0);
			/* enable eventfs notअगरication */
			iocb_out->u.c.flags |= IOCB_FLAG_RESFD;
			iocb_out->u.c.resfd = evfd;
			/* submit table of requests */
			ret = io_submit(ctx, 1, &iocb_out);
			अगर (ret >= 0) अणु /* अगर ret > 0 request is queued */
				req_out = 1;
				म_लिखो("submit: out\n");
			पूर्ण अन्यथा
				लिखो_त्रुटि("unable to submit request");
		पूर्ण
	पूर्ण

	/* मुक्त resources */

	io_destroy(ctx);

	मुक्त(buf_in);
	मुक्त(buf_out);
	मुक्त(iocb_in);
	मुक्त(iocb_out);

	क्रम (i = 0; i < 2; ++i)
		बंद(ep[i]);
	बंद(ep0);

	वापस 0;
पूर्ण
