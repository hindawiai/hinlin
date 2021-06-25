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

#समावेश <libusb.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#घोषणा VENDOR	0x1d6b
#घोषणा PRODUCT	0x0105

#घोषणा BUF_LEN		8192

/*
 * काष्ठा test_state - describes test program state
 * @list: list of devices वापसed by libusb_get_device_list function
 * @found: poपूर्णांकer to काष्ठा describing tested device
 * @ctx: context, set to शून्य
 * @handle: handle of tested device
 * @attached: indicates that device was attached to kernel, and has to be
 *            reattached at the end of test program
 */

काष्ठा test_state अणु
	libusb_device *found;
	libusb_context *ctx;
	libusb_device_handle *handle;
	पूर्णांक attached;
पूर्ण;

/*
 * test_init - initialize test program
 */

पूर्णांक test_init(काष्ठा test_state *state)
अणु
	पूर्णांक i, ret;
	sमाप_प्रकार cnt;
	libusb_device **list;

	state->found = शून्य;
	state->ctx = शून्य;
	state->handle = शून्य;
	state->attached = 0;

	ret = libusb_init(&state->ctx);
	अगर (ret) अणु
		म_लिखो("cannot init libusb: %s\n", libusb_error_name(ret));
		वापस 1;
	पूर्ण

	cnt = libusb_get_device_list(state->ctx, &list);
	अगर (cnt <= 0) अणु
		म_लिखो("no devices found\n");
		जाओ error1;
	पूर्ण

	क्रम (i = 0; i < cnt; ++i) अणु
		libusb_device *dev = list[i];
		काष्ठा libusb_device_descriptor desc;
		ret = libusb_get_device_descriptor(dev, &desc);
		अगर (ret) अणु
			म_लिखो("unable to get device descriptor: %s\n",
			       libusb_error_name(ret));
			जाओ error2;
		पूर्ण
		अगर (desc.idVenकरोr == VENDOR && desc.idProduct == PRODUCT) अणु
			state->found = dev;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!state->found) अणु
		म_लिखो("no devices found\n");
		जाओ error2;
	पूर्ण

	ret = libusb_खोलो(state->found, &state->handle);
	अगर (ret) अणु
		म_लिखो("cannot open device: %s\n", libusb_error_name(ret));
		जाओ error2;
	पूर्ण

	अगर (libusb_claim_पूर्णांकerface(state->handle, 0)) अणु
		ret = libusb_detach_kernel_driver(state->handle, 0);
		अगर (ret) अणु
			म_लिखो("unable to detach kernel driver: %s\n",
			       libusb_error_name(ret));
			जाओ error3;
		पूर्ण
		state->attached = 1;
		ret = libusb_claim_पूर्णांकerface(state->handle, 0);
		अगर (ret) अणु
			म_लिखो("cannot claim interface: %s\n",
			       libusb_error_name(ret));
			जाओ error4;
		पूर्ण
	पूर्ण

	वापस 0;

error4:
	अगर (state->attached == 1)
		libusb_attach_kernel_driver(state->handle, 0);

error3:
	libusb_बंद(state->handle);

error2:
	libusb_मुक्त_device_list(list, 1);

error1:
	libusb_निकास(state->ctx);
	वापस 1;
पूर्ण

/*
 * test_निकास - cleanup test program
 */

व्योम test_निकास(काष्ठा test_state *state)
अणु
	libusb_release_पूर्णांकerface(state->handle, 0);
	अगर (state->attached == 1)
		libusb_attach_kernel_driver(state->handle, 0);
	libusb_बंद(state->handle);
	libusb_निकास(state->ctx);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा test_state state;
	काष्ठा libusb_config_descriptor *conf;
	काष्ठा libusb_पूर्णांकerface_descriptor स्थिर *अगरace;
	अचिन्हित अक्षर addr;

	अगर (test_init(&state))
		वापस 1;

	libusb_get_config_descriptor(state.found, 0, &conf);
	अगरace = &conf->पूर्णांकerface[0].altsetting[0];
	addr = अगरace->endpoपूर्णांक[0].bEndpoपूर्णांकAddress;

	जबतक (1) अणु
		अटल अचिन्हित अक्षर buffer[BUF_LEN];
		पूर्णांक bytes;
		libusb_bulk_transfer(state.handle, addr, buffer, BUF_LEN,
				     &bytes, 500);
	पूर्ण
	test_निकास(&state);
पूर्ण
