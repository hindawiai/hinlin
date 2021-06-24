<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __USB_TYPEC_MUX__
#घोषणा __USB_TYPEC_MUX__

#समावेश <linux/usb/typec_mux.h>

काष्ठा typec_चयन अणु
	काष्ठा device dev;
	typec_चयन_set_fn_t set;
पूर्ण;

काष्ठा typec_mux अणु
	काष्ठा device dev;
	typec_mux_set_fn_t set;
पूर्ण;

#घोषणा to_typec_चयन(_dev_) container_of(_dev_, काष्ठा typec_चयन, dev)
#घोषणा to_typec_mux(_dev_) container_of(_dev_, काष्ठा typec_mux, dev)

#पूर्ण_अगर /* __USB_TYPEC_MUX__ */
