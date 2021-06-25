<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* dvb-usb-urb.c is part of the DVB USB library.
 *
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * This file keeps functions क्रम initializing and handling the
 * USB and URB stuff.
 */
#समावेश "dvb-usb-common.h"

पूर्णांक dvb_usb_generic_rw(काष्ठा dvb_usb_device *d, u8 *wbuf, u16 wlen, u8 *rbuf,
	u16 rlen, पूर्णांक delay_ms)
अणु
	पूर्णांक actlen = 0, ret = -ENOMEM;

	अगर (!d || wbuf == शून्य || wlen == 0)
		वापस -EINVAL;

	अगर (d->props.generic_bulk_ctrl_endpoपूर्णांक == 0) अणु
		err("endpoint for generic control not specified.");
		वापस -EINVAL;
	पूर्ण

	अगर ((ret = mutex_lock_पूर्णांकerruptible(&d->usb_mutex)))
		वापस ret;

	deb_xfer(">>> ");
	debug_dump(wbuf,wlen,deb_xfer);

	ret = usb_bulk_msg(d->udev,usb_sndbulkpipe(d->udev,
			d->props.generic_bulk_ctrl_endpoपूर्णांक), wbuf,wlen,&actlen,
			2000);

	अगर (ret)
		err("bulk message failed: %d (%d/%d)",ret,wlen,actlen);
	अन्यथा
		ret = actlen != wlen ? -1 : 0;

	/* an answer is expected, and no error beक्रमe */
	अगर (!ret && rbuf && rlen) अणु
		अगर (delay_ms)
			msleep(delay_ms);

		ret = usb_bulk_msg(d->udev,usb_rcvbulkpipe(d->udev,
				d->props.generic_bulk_ctrl_endpoपूर्णांक_response ?
				d->props.generic_bulk_ctrl_endpoपूर्णांक_response :
				d->props.generic_bulk_ctrl_endpoपूर्णांक),rbuf,rlen,&actlen,
				2000);

		अगर (ret)
			err("recv bulk message failed: %d",ret);
		अन्यथा अणु
			deb_xfer("<<< ");
			debug_dump(rbuf,actlen,deb_xfer);
		पूर्ण
	पूर्ण

	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_usb_generic_rw);

पूर्णांक dvb_usb_generic_ग_लिखो(काष्ठा dvb_usb_device *d, u8 *buf, u16 len)
अणु
	वापस dvb_usb_generic_rw(d,buf,len,शून्य,0,0);
पूर्ण
EXPORT_SYMBOL(dvb_usb_generic_ग_लिखो);

अटल व्योम dvb_usb_data_complete(काष्ठा usb_data_stream *stream, u8 *buffer, माप_प्रकार length)
अणु
	काष्ठा dvb_usb_adapter *adap = stream->user_priv;
	अगर (adap->feedcount > 0 && adap->state & DVB_USB_ADAP_STATE_DVB)
		dvb_dmx_swfilter(&adap->demux, buffer, length);
पूर्ण

अटल व्योम dvb_usb_data_complete_204(काष्ठा usb_data_stream *stream, u8 *buffer, माप_प्रकार length)
अणु
	काष्ठा dvb_usb_adapter *adap = stream->user_priv;
	अगर (adap->feedcount > 0 && adap->state & DVB_USB_ADAP_STATE_DVB)
		dvb_dmx_swfilter_204(&adap->demux, buffer, length);
पूर्ण

अटल व्योम dvb_usb_data_complete_raw(काष्ठा usb_data_stream *stream,
				      u8 *buffer, माप_प्रकार length)
अणु
	काष्ठा dvb_usb_adapter *adap = stream->user_priv;
	अगर (adap->feedcount > 0 && adap->state & DVB_USB_ADAP_STATE_DVB)
		dvb_dmx_swfilter_raw(&adap->demux, buffer, length);
पूर्ण

पूर्णांक dvb_usb_adapter_stream_init(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक i, ret = 0;
	क्रम (i = 0; i < adap->props.num_frontends; i++) अणु

		adap->fe_adap[i].stream.udev      = adap->dev->udev;
		अगर (adap->props.fe[i].caps & DVB_USB_ADAP_RECEIVES_204_BYTE_TS)
			adap->fe_adap[i].stream.complete =
				dvb_usb_data_complete_204;
		अन्यथा
		अगर (adap->props.fe[i].caps & DVB_USB_ADAP_RECEIVES_RAW_PAYLOAD)
			adap->fe_adap[i].stream.complete =
				dvb_usb_data_complete_raw;
		अन्यथा
		adap->fe_adap[i].stream.complete  = dvb_usb_data_complete;
		adap->fe_adap[i].stream.user_priv = adap;
		ret = usb_urb_init(&adap->fe_adap[i].stream,
				   &adap->props.fe[i].stream);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक dvb_usb_adapter_stream_निकास(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < adap->props.num_frontends; i++)
		usb_urb_निकास(&adap->fe_adap[i].stream);
	वापस 0;
पूर्ण
