<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USBAUDIO_ENDPOINT_H
#घोषणा __USBAUDIO_ENDPOINT_H

#घोषणा SND_USB_ENDPOINT_TYPE_DATA     0
#घोषणा SND_USB_ENDPOINT_TYPE_SYNC     1

काष्ठा snd_usb_endpoपूर्णांक *snd_usb_get_endpoपूर्णांक(काष्ठा snd_usb_audio *chip,
					      पूर्णांक ep_num);

पूर्णांक snd_usb_add_endpoपूर्णांक(काष्ठा snd_usb_audio *chip, पूर्णांक ep_num, पूर्णांक type);

काष्ठा snd_usb_endpoपूर्णांक *
snd_usb_endpoपूर्णांक_खोलो(काष्ठा snd_usb_audio *chip,
		      स्थिर काष्ठा audioक्रमmat *fp,
		      स्थिर काष्ठा snd_pcm_hw_params *params,
		      bool is_sync_ep);
व्योम snd_usb_endpoपूर्णांक_बंद(काष्ठा snd_usb_audio *chip,
			    काष्ठा snd_usb_endpoपूर्णांक *ep);
पूर्णांक snd_usb_endpoपूर्णांक_configure(काष्ठा snd_usb_audio *chip,
			       काष्ठा snd_usb_endpoपूर्णांक *ep);
व्योम snd_usb_endpoपूर्णांक_suspend(काष्ठा snd_usb_endpoपूर्णांक *ep);

bool snd_usb_endpoपूर्णांक_compatible(काष्ठा snd_usb_audio *chip,
				 काष्ठा snd_usb_endpoपूर्णांक *ep,
				 स्थिर काष्ठा audioक्रमmat *fp,
				 स्थिर काष्ठा snd_pcm_hw_params *params);

व्योम snd_usb_endpoपूर्णांक_set_sync(काष्ठा snd_usb_audio *chip,
			       काष्ठा snd_usb_endpoपूर्णांक *data_ep,
			       काष्ठा snd_usb_endpoपूर्णांक *sync_ep);
व्योम snd_usb_endpoपूर्णांक_set_callback(काष्ठा snd_usb_endpoपूर्णांक *ep,
				   व्योम (*prepare)(काष्ठा snd_usb_substream *subs,
						   काष्ठा urb *urb),
				   व्योम (*retire)(काष्ठा snd_usb_substream *subs,
						  काष्ठा urb *urb),
				   काष्ठा snd_usb_substream *data_subs);

पूर्णांक snd_usb_endpoपूर्णांक_start(काष्ठा snd_usb_endpoपूर्णांक *ep);
व्योम snd_usb_endpoपूर्णांक_stop(काष्ठा snd_usb_endpoपूर्णांक *ep);
व्योम snd_usb_endpoपूर्णांक_sync_pending_stop(काष्ठा snd_usb_endpoपूर्णांक *ep);
व्योम snd_usb_endpoपूर्णांक_suspend(काष्ठा snd_usb_endpoपूर्णांक *ep);
पूर्णांक  snd_usb_endpoपूर्णांक_activate(काष्ठा snd_usb_endpoपूर्णांक *ep);
व्योम snd_usb_endpoपूर्णांक_release(काष्ठा snd_usb_endpoपूर्णांक *ep);
व्योम snd_usb_endpoपूर्णांक_मुक्त_all(काष्ठा snd_usb_audio *chip);

पूर्णांक snd_usb_endpoपूर्णांक_implicit_feedback_sink(काष्ठा snd_usb_endpoपूर्णांक *ep);
पूर्णांक snd_usb_endpoपूर्णांक_next_packet_size(काष्ठा snd_usb_endpoपूर्णांक *ep,
				      काष्ठा snd_urb_ctx *ctx, पूर्णांक idx);

#पूर्ण_अगर /* __USBAUDIO_ENDPOINT_H */
