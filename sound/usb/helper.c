<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश "usbaudio.h"
#समावेश "helper.h"
#समावेश "quirks.h"

/*
 * combine bytes and get an पूर्णांकeger value
 */
अचिन्हित पूर्णांक snd_usb_combine_bytes(अचिन्हित अक्षर *bytes, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:  वापस *bytes;
	हाल 2:  वापस combine_word(bytes);
	हाल 3:  वापस combine_triple(bytes);
	हाल 4:  वापस combine_quad(bytes);
	शेष: वापस 0;
	पूर्ण
पूर्ण

/*
 * parse descriptor buffer and वापस the poपूर्णांकer starting the given
 * descriptor type.
 */
व्योम *snd_usb_find_desc(व्योम *descstart, पूर्णांक desclen, व्योम *after, u8 dtype)
अणु
	u8 *p, *end, *next;

	p = descstart;
	end = p + desclen;
	क्रम (; p < end;) अणु
		अगर (p[0] < 2)
			वापस शून्य;
		next = p + p[0];
		अगर (next > end)
			वापस शून्य;
		अगर (p[1] == dtype && (!after || (व्योम *)p > after)) अणु
			वापस p;
		पूर्ण
		p = next;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * find a class-specअगरied पूर्णांकerface descriptor with the given subtype.
 */
व्योम *snd_usb_find_csपूर्णांक_desc(व्योम *buffer, पूर्णांक buflen, व्योम *after, u8 dsubtype)
अणु
	अचिन्हित अक्षर *p = after;

	जबतक ((p = snd_usb_find_desc(buffer, buflen, p,
				      USB_DT_CS_INTERFACE)) != शून्य) अणु
		अगर (p[0] >= 3 && p[2] == dsubtype)
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Wrapper क्रम usb_control_msg().
 * Allocates a temp buffer to prevent dमुख्यg from/to the stack.
 */
पूर्णांक snd_usb_ctl_msg(काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe, __u8 request,
		    __u8 requesttype, __u16 value, __u16 index, व्योम *data,
		    __u16 size)
अणु
	पूर्णांक err;
	व्योम *buf = शून्य;
	पूर्णांक समयout;

	अगर (usb_pipe_type_check(dev, pipe))
		वापस -EINVAL;

	अगर (size > 0) अणु
		buf = kmemdup(data, size, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
	पूर्ण

	अगर (requesttype & USB_सूची_IN)
		समयout = USB_CTRL_GET_TIMEOUT;
	अन्यथा
		समयout = USB_CTRL_SET_TIMEOUT;

	err = usb_control_msg(dev, pipe, request, requesttype,
			      value, index, buf, size, समयout);

	अगर (size > 0) अणु
		स_नकल(data, buf, size);
		kमुक्त(buf);
	पूर्ण

	snd_usb_ctl_msg_quirk(dev, pipe, request, requesttype,
			      value, index, data, size);

	वापस err;
पूर्ण

अचिन्हित अक्षर snd_usb_parse_dataपूर्णांकerval(काष्ठा snd_usb_audio *chip,
					 काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	चयन (snd_usb_get_speed(chip->dev)) अणु
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_WIRELESS:
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		अगर (get_endpoपूर्णांक(alts, 0)->bInterval >= 1 &&
		    get_endpoपूर्णांक(alts, 0)->bInterval <= 4)
			वापस get_endpoपूर्णांक(alts, 0)->bInterval - 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा usb_host_पूर्णांकerface *
snd_usb_get_host_पूर्णांकerface(काष्ठा snd_usb_audio *chip, पूर्णांक अगरnum, पूर्णांक altsetting)
अणु
	काष्ठा usb_पूर्णांकerface *अगरace;

	अगरace = usb_अगरnum_to_अगर(chip->dev, अगरnum);
	अगर (!अगरace)
		वापस शून्य;
	वापस usb_altnum_to_altsetting(अगरace, altsetting);
पूर्ण
