<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	Driver क्रम ZyDAS zd1201 based wireless USB devices.
 *
 *	Copyright (c) 2004, 2005 Jeroen Vreeken (pe1rxq@amsat.org)
 *
 *	Parts of this driver have been derived from a wlan-ng version
 *	modअगरied by ZyDAS. They also made करोcumentation available, thanks!
 *	Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/wireless.h>
#समावेश <net/cfg80211.h>
#समावेश <net/iw_handler.h>
#समावेश <linux/माला.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/firmware.h>
#समावेश "zd1201.h"

अटल स्थिर काष्ठा usb_device_id zd1201_table[] = अणु
	अणुUSB_DEVICE(0x0586, 0x3400)पूर्ण, /* Peabird Wireless USB Adapter */
	अणुUSB_DEVICE(0x0ace, 0x1201)पूर्ण, /* ZyDAS ZD1201 Wireless USB Adapter */
	अणुUSB_DEVICE(0x050d, 0x6051)पूर्ण, /* Belkin F5D6051 usb  adapter */
	अणुUSB_DEVICE(0x0db0, 0x6823)पूर्ण, /* MSI UB11B usb  adapter */
	अणुUSB_DEVICE(0x1044, 0x8004)पूर्ण, /* Gigabyte GN-WLBZ101 */
	अणुUSB_DEVICE(0x1044, 0x8005)पूर्ण, /* GIGABYTE GN-WLBZ201 usb adapter */
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक ap;	/* Are we an AP or a normal station? */

#घोषणा ZD1201_VERSION	"0.15"

MODULE_AUTHOR("Jeroen Vreeken <pe1rxq@amsat.org>");
MODULE_DESCRIPTION("Driver for ZyDAS ZD1201 based USB Wireless adapters");
MODULE_VERSION(ZD1201_VERSION);
MODULE_LICENSE("GPL");
module_param(ap, पूर्णांक, 0);
MODULE_PARM_DESC(ap, "If non-zero Access Point firmware will be loaded");
MODULE_DEVICE_TABLE(usb, zd1201_table);


अटल पूर्णांक zd1201_fw_upload(काष्ठा usb_device *dev, पूर्णांक apfw)
अणु
	स्थिर काष्ठा firmware *fw_entry;
	स्थिर अक्षर *data;
	अचिन्हित दीर्घ len;
	पूर्णांक err;
	अचिन्हित अक्षर ret;
	अक्षर *buf;
	अक्षर *fwfile;

	अगर (apfw)
		fwfile = "zd1201-ap.fw";
	अन्यथा
		fwfile = "zd1201.fw";

	err = request_firmware(&fw_entry, fwfile, &dev->dev);
	अगर (err) अणु
		dev_err(&dev->dev, "Failed to load %s firmware file!\n", fwfile);
		dev_err(&dev->dev, "Make sure the hotplug firmware loader is installed.\n");
		dev_err(&dev->dev, "Goto http://linux-lc100020.sourceforge.net for more info.\n");
		वापस err;
	पूर्ण

	data = fw_entry->data;
        len = fw_entry->size;

	buf = kदो_स्मृति(1024, GFP_ATOMIC);
	अगर (!buf) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण
	
	जबतक (len > 0) अणु
		पूर्णांक translen = (len > 1024) ? 1024 : len;
		स_नकल(buf, data, translen);

		err = usb_control_msg(dev, usb_sndctrlpipe(dev, 0), 0,
		    USB_सूची_OUT | 0x40, 0, 0, buf, translen,
		    ZD1201_FW_TIMEOUT);
		अगर (err < 0)
			जाओ निकास;

		len -= translen;
		data += translen;
	पूर्ण
                                        
	err = usb_control_msg(dev, usb_sndctrlpipe(dev, 0), 0x2,
	    USB_सूची_OUT | 0x40, 0, 0, शून्य, 0, ZD1201_FW_TIMEOUT);
	अगर (err < 0)
		जाओ निकास;

	err = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0), 0x4,
	    USB_सूची_IN | 0x40, 0, 0, buf, माप(ret), ZD1201_FW_TIMEOUT);
	अगर (err < 0)
		जाओ निकास;

	स_नकल(&ret, buf, माप(ret));

	अगर (ret & 0x80) अणु
		err = -EIO;
		जाओ निकास;
	पूर्ण

	err = 0;
निकास:
	kमुक्त(buf);
	release_firmware(fw_entry);
	वापस err;
पूर्ण

MODULE_FIRMWARE("zd1201-ap.fw");
MODULE_FIRMWARE("zd1201.fw");

अटल व्योम zd1201_usbमुक्त(काष्ठा urb *urb)
अणु
	काष्ठा zd1201 *zd = urb->context;

	चयन(urb->status) अणु
		हाल -EILSEQ:
		हाल -ENODEV:
		हाल -ETIME:
		हाल -ENOENT:
		हाल -EPIPE:
		हाल -EOVERFLOW:
		हाल -ESHUTDOWN:
			dev_warn(&zd->usb->dev, "%s: urb failed: %d\n", 
			    zd->dev->name, urb->status);
	पूर्ण

	kमुक्त(urb->transfer_buffer);
	usb_मुक्त_urb(urb);
पूर्ण

/* cmdreq message: 
	u32 type
	u16 cmd
	u16 parm0
	u16 parm1
	u16 parm2
	u8  pad[4]

	total: 4 + 2 + 2 + 2 + 2 + 4 = 16
*/
अटल पूर्णांक zd1201_करोcmd(काष्ठा zd1201 *zd, पूर्णांक cmd, पूर्णांक parm0,
			पूर्णांक parm1, पूर्णांक parm2)
अणु
	अचिन्हित अक्षर *command;
	पूर्णांक ret;
	काष्ठा urb *urb;

	command = kदो_स्मृति(16, GFP_ATOMIC);
	अगर (!command)
		वापस -ENOMEM;

	*((__le32*)command) = cpu_to_le32(ZD1201_USB_CMDREQ);
	*((__le16*)&command[4]) = cpu_to_le16(cmd);
	*((__le16*)&command[6]) = cpu_to_le16(parm0);
	*((__le16*)&command[8]) = cpu_to_le16(parm1);
	*((__le16*)&command[10])= cpu_to_le16(parm2);

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		kमुक्त(command);
		वापस -ENOMEM;
	पूर्ण
	usb_fill_bulk_urb(urb, zd->usb, usb_sndbulkpipe(zd->usb, zd->endp_out2),
			  command, 16, zd1201_usbमुक्त, zd);
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret) अणु
		kमुक्त(command);
		usb_मुक्त_urb(urb);
	पूर्ण

	वापस ret;
पूर्ण

/* Callback after sending out a packet */
अटल व्योम zd1201_usbtx(काष्ठा urb *urb)
अणु
	काष्ठा zd1201 *zd = urb->context;
	netअगर_wake_queue(zd->dev);
पूर्ण

/* Incoming data */
अटल व्योम zd1201_usbrx(काष्ठा urb *urb)
अणु
	काष्ठा zd1201 *zd = urb->context;
	पूर्णांक मुक्त = 0;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर type;

	अगर (!zd)
		वापस;

	चयन(urb->status) अणु
		हाल -EILSEQ:
		हाल -ENODEV:
		हाल -ETIME:
		हाल -ENOENT:
		हाल -EPIPE:
		हाल -EOVERFLOW:
		हाल -ESHUTDOWN:
			dev_warn(&zd->usb->dev, "%s: rx urb failed: %d\n",
			    zd->dev->name, urb->status);
			मुक्त = 1;
			जाओ निकास;
	पूर्ण
	
	अगर (urb->status != 0 || urb->actual_length == 0)
		जाओ resubmit;

	type = data[0];
	अगर (type == ZD1201_PACKET_EVENTSTAT || type == ZD1201_PACKET_RESOURCE) अणु
		स_नकल(zd->rxdata, data, urb->actual_length);
		zd->rxlen = urb->actual_length;
		zd->rxdatas = 1;
		wake_up(&zd->rxdataq);
	पूर्ण
	/* Info frame */
	अगर (type == ZD1201_PACKET_INQUIRE) अणु
		पूर्णांक i = 0;
		अचिन्हित लघु infotype, copylen;
		infotype = le16_to_cpu(*(__le16*)&data[6]);

		अगर (infotype == ZD1201_INF_LINKSTATUS) अणु
			लघु linkstatus;

			linkstatus = le16_to_cpu(*(__le16*)&data[8]);
			चयन(linkstatus) अणु
				हाल 1:
					netअगर_carrier_on(zd->dev);
					अवरोध;
				हाल 2:
					netअगर_carrier_off(zd->dev);
					अवरोध;
				हाल 3:
					netअगर_carrier_off(zd->dev);
					अवरोध;
				हाल 4:
					netअगर_carrier_on(zd->dev);
					अवरोध;
				शेष:
					netअगर_carrier_off(zd->dev);
			पूर्ण
			जाओ resubmit;
		पूर्ण
		अगर (infotype == ZD1201_INF_ASSOCSTATUS) अणु
			लघु status = le16_to_cpu(*(__le16*)(data+8));
			पूर्णांक event;
			जोड़ iwreq_data wrqu;

			चयन (status) अणु
				हाल ZD1201_ASSOCSTATUS_STAASSOC:
				हाल ZD1201_ASSOCSTATUS_REASSOC:
					event = IWEVREGISTERED;
					अवरोध;
				हाल ZD1201_ASSOCSTATUS_DISASSOC:
				हाल ZD1201_ASSOCSTATUS_ASSOCFAIL:
				हाल ZD1201_ASSOCSTATUS_AUTHFAIL:
				शेष:
					event = IWEVEXPIRED;
			पूर्ण
			स_नकल(wrqu.addr.sa_data, data+10, ETH_ALEN);
			wrqu.addr.sa_family = ARPHRD_ETHER;

			/* Send event to user space */
			wireless_send_event(zd->dev, event, &wrqu, शून्य);

			जाओ resubmit;
		पूर्ण
		अगर (infotype == ZD1201_INF_AUTHREQ) अणु
			जोड़ iwreq_data wrqu;

			स_नकल(wrqu.addr.sa_data, data+8, ETH_ALEN);
			wrqu.addr.sa_family = ARPHRD_ETHER;
			/* There isn't a event that trully fits this request.
			   We assume that userspace will be smart enough to
			   see a new station being expired and sends back a
			   authstation ioctl to authorize it. */
			wireless_send_event(zd->dev, IWEVEXPIRED, &wrqu, शून्य);
			जाओ resubmit;
		पूर्ण
		/* Other infotypes are handled outside this handler */
		zd->rxlen = 0;
		जबतक (i < urb->actual_length) अणु
			copylen = le16_to_cpu(*(__le16*)&data[i+2]);
			/* Sanity check, someबार we get junk */
			अगर (copylen+zd->rxlen > माप(zd->rxdata))
				अवरोध;
			स_नकल(zd->rxdata+zd->rxlen, data+i+4, copylen);
			zd->rxlen += copylen;
			i += 64;
		पूर्ण
		अगर (i >= urb->actual_length) अणु
			zd->rxdatas = 1;
			wake_up(&zd->rxdataq);
		पूर्ण
		जाओ  resubmit;
	पूर्ण
	/* Actual data */
	अगर (data[urb->actual_length-1] == ZD1201_PACKET_RXDATA) अणु
		पूर्णांक datalen = urb->actual_length-1;
		अचिन्हित लघु len, fc, seq;

		len = ntohs(*(__be16 *)&data[datalen-2]);
		अगर (len>datalen)
			len=datalen;
		fc = le16_to_cpu(*(__le16 *)&data[datalen-16]);
		seq = le16_to_cpu(*(__le16 *)&data[datalen-24]);

		अगर (zd->monitor) अणु
			अगर (datalen < 24)
				जाओ resubmit;
			अगर (!(skb = dev_alloc_skb(datalen+24)))
				जाओ resubmit;
			
			skb_put_data(skb, &data[datalen - 16], 2);
			skb_put_data(skb, &data[datalen - 2], 2);
			skb_put_data(skb, &data[datalen - 14], 6);
			skb_put_data(skb, &data[datalen - 22], 6);
			skb_put_data(skb, &data[datalen - 8], 6);
			skb_put_data(skb, &data[datalen - 24], 2);
			skb_put_data(skb, data, len);
			skb->protocol = eth_type_trans(skb, zd->dev);
			zd->dev->stats.rx_packets++;
			zd->dev->stats.rx_bytes += skb->len;
			netअगर_rx(skb);
			जाओ resubmit;
		पूर्ण
			
		अगर ((seq & IEEE80211_SCTL_FRAG) ||
		    (fc & IEEE80211_FCTL_MOREFRAGS)) अणु
			काष्ठा zd1201_frag *frag = शून्य;
			अक्षर *ptr;

			अगर (datalen<14)
				जाओ resubmit;
			अगर ((seq & IEEE80211_SCTL_FRAG) == 0) अणु
				frag = kदो_स्मृति(माप(*frag), GFP_ATOMIC);
				अगर (!frag)
					जाओ resubmit;
				skb = dev_alloc_skb(IEEE80211_MAX_DATA_LEN +14+2);
				अगर (!skb) अणु
					kमुक्त(frag);
					जाओ resubmit;
				पूर्ण
				frag->skb = skb;
				frag->seq = seq & IEEE80211_SCTL_SEQ;
				skb_reserve(skb, 2);
				skb_put_data(skb, &data[datalen - 14], 12);
				skb_put_data(skb, &data[6], 2);
				skb_put_data(skb, data + 8, len);
				hlist_add_head(&frag->fnode, &zd->fraglist);
				जाओ resubmit;
			पूर्ण
			hlist_क्रम_each_entry(frag, &zd->fraglist, fnode)
				अगर (frag->seq == (seq&IEEE80211_SCTL_SEQ))
					अवरोध;
			अगर (!frag)
				जाओ resubmit;
			skb = frag->skb;
			ptr = skb_put(skb, len);
			अगर (ptr)
				स_नकल(ptr, data+8, len);
			अगर (fc & IEEE80211_FCTL_MOREFRAGS)
				जाओ resubmit;
			hlist_del_init(&frag->fnode);
			kमुक्त(frag);
		पूर्ण अन्यथा अणु
			अगर (datalen<14)
				जाओ resubmit;
			skb = dev_alloc_skb(len + 14 + 2);
			अगर (!skb)
				जाओ resubmit;
			skb_reserve(skb, 2);
			skb_put_data(skb, &data[datalen - 14], 12);
			skb_put_data(skb, &data[6], 2);
			skb_put_data(skb, data + 8, len);
		पूर्ण
		skb->protocol = eth_type_trans(skb, zd->dev);
		zd->dev->stats.rx_packets++;
		zd->dev->stats.rx_bytes += skb->len;
		netअगर_rx(skb);
	पूर्ण
resubmit:
	स_रखो(data, 0, ZD1201_RXSIZE);

	urb->status = 0;
	urb->dev = zd->usb;
	अगर(usb_submit_urb(urb, GFP_ATOMIC))
		मुक्त = 1;

निकास:
	अगर (मुक्त) अणु
		zd->rxlen = 0;
		zd->rxdatas = 1;
		wake_up(&zd->rxdataq);
		kमुक्त(urb->transfer_buffer);
	पूर्ण
पूर्ण

अटल पूर्णांक zd1201_अ_लोonfig(काष्ठा zd1201 *zd, पूर्णांक rid, व्योम *riddata,
	अचिन्हित पूर्णांक riddatalen)
अणु
	पूर्णांक err;
	पूर्णांक i = 0;
	पूर्णांक code;
	पूर्णांक rid_fid;
	पूर्णांक length;
	अचिन्हित अक्षर *pdata;

	zd->rxdatas = 0;
	err = zd1201_करोcmd(zd, ZD1201_CMDCODE_ACCESS, rid, 0, 0);
	अगर (err)
		वापस err;

	रुको_event_पूर्णांकerruptible(zd->rxdataq, zd->rxdatas);
	अगर (!zd->rxlen)
		वापस -EIO;

	code = le16_to_cpu(*(__le16*)(&zd->rxdata[4]));
	rid_fid = le16_to_cpu(*(__le16*)(&zd->rxdata[6]));
	length = le16_to_cpu(*(__le16*)(&zd->rxdata[8]));
	अगर (length > zd->rxlen)
		length = zd->rxlen-6;

	/* If access bit is not on, then error */
	अगर ((code & ZD1201_ACCESSBIT) != ZD1201_ACCESSBIT || rid_fid != rid )
		वापस -EINVAL;

	/* Not enough buffer क्रम allocating data */
	अगर (riddatalen != (length - 4)) अणु
		dev_dbg(&zd->usb->dev, "riddatalen mismatches, expected=%u, (packet=%u) length=%u, rid=0x%04X, rid_fid=0x%04X\n",
		    riddatalen, zd->rxlen, length, rid, rid_fid);
		वापस -ENODATA;
	पूर्ण

	zd->rxdatas = 0;
	/* Issue SetRxRid commnd */			
	err = zd1201_करोcmd(zd, ZD1201_CMDCODE_SETRXRID, rid, 0, length);
	अगर (err)
		वापस err;

	/* Receive RID record from resource packets */
	रुको_event_पूर्णांकerruptible(zd->rxdataq, zd->rxdatas);
	अगर (!zd->rxlen)
		वापस -EIO;

	अगर (zd->rxdata[zd->rxlen - 1] != ZD1201_PACKET_RESOURCE) अणु
		dev_dbg(&zd->usb->dev, "Packet type mismatch: 0x%x not 0x3\n",
		    zd->rxdata[zd->rxlen-1]);
		वापस -EINVAL;
	पूर्ण

	/* Set the data poपूर्णांकer and received data length */
	pdata = zd->rxdata;
	length = zd->rxlen;

	करो अणु
		पूर्णांक actual_length;

		actual_length = (length > 64) ? 64 : length;

		अगर (pdata[0] != 0x3) अणु
			dev_dbg(&zd->usb->dev, "Rx Resource packet type error: %02X\n",
			    pdata[0]);
			वापस -EINVAL;
		पूर्ण

		अगर (actual_length != 64) अणु
			/* Trim the last packet type byte */
			actual_length--;
		पूर्ण

		/* Skip the 4 bytes header (RID length and RID) */
		अगर (i == 0) अणु
			pdata += 8;
			actual_length -= 8;
		पूर्ण अन्यथा अणु
			pdata += 4;
			actual_length -= 4;
		पूर्ण
		
		स_नकल(riddata, pdata, actual_length);
		riddata += actual_length;
		pdata += actual_length;
		length -= 64;
		i++;
	पूर्ण जबतक (length > 0);

	वापस 0;
पूर्ण

/*
 *	resreq:
 *		byte	type
 *		byte	sequence
 *		u16	reserved
 *		byte	data[12]
 *	total: 16
 */
अटल पूर्णांक zd1201_setconfig(काष्ठा zd1201 *zd, पूर्णांक rid, व्योम *buf, पूर्णांक len, पूर्णांक रुको)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर *request;
	पूर्णांक reqlen;
	अक्षर seq=0;
	काष्ठा urb *urb;
	gfp_t gfp_mask = रुको ? GFP_NOIO : GFP_ATOMIC;

	len += 4;			/* first 4 are क्रम header */

	zd->rxdatas = 0;
	zd->rxlen = 0;
	क्रम (seq=0; len > 0; seq++) अणु
		request = kदो_स्मृति(16, gfp_mask);
		अगर (!request)
			वापस -ENOMEM;
		urb = usb_alloc_urb(0, gfp_mask);
		अगर (!urb) अणु
			kमुक्त(request);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(request, 0, 16);
		reqlen = len>12 ? 12 : len;
		request[0] = ZD1201_USB_RESREQ;
		request[1] = seq;
		request[2] = 0;
		request[3] = 0;
		अगर (request[1] == 0) अणु
			/* add header */
			*(__le16*)&request[4] = cpu_to_le16((len-2+1)/2);
			*(__le16*)&request[6] = cpu_to_le16(rid);
			स_नकल(request+8, buf, reqlen-4);
			buf += reqlen-4;
		पूर्ण अन्यथा अणु
			स_नकल(request+4, buf, reqlen);
			buf += reqlen;
		पूर्ण

		len -= reqlen;

		usb_fill_bulk_urb(urb, zd->usb, usb_sndbulkpipe(zd->usb,
		    zd->endp_out2), request, 16, zd1201_usbमुक्त, zd);
		err = usb_submit_urb(urb, gfp_mask);
		अगर (err)
			जाओ err;
	पूर्ण

	request = kदो_स्मृति(16, gfp_mask);
	अगर (!request)
		वापस -ENOMEM;
	urb = usb_alloc_urb(0, gfp_mask);
	अगर (!urb) अणु
		kमुक्त(request);
		वापस -ENOMEM;
	पूर्ण
	*((__le32*)request) = cpu_to_le32(ZD1201_USB_CMDREQ);
	*((__le16*)&request[4]) = 
	    cpu_to_le16(ZD1201_CMDCODE_ACCESS|ZD1201_ACCESSBIT);
	*((__le16*)&request[6]) = cpu_to_le16(rid);
	*((__le16*)&request[8]) = cpu_to_le16(0);
	*((__le16*)&request[10]) = cpu_to_le16(0);
	usb_fill_bulk_urb(urb, zd->usb, usb_sndbulkpipe(zd->usb, zd->endp_out2),
	     request, 16, zd1201_usbमुक्त, zd);
	err = usb_submit_urb(urb, gfp_mask);
	अगर (err)
		जाओ err;
	
	अगर (रुको) अणु
		रुको_event_पूर्णांकerruptible(zd->rxdataq, zd->rxdatas);
		अगर (!zd->rxlen || le16_to_cpu(*(__le16*)&zd->rxdata[6]) != rid) अणु
			dev_dbg(&zd->usb->dev, "wrong or no RID received\n");
		पूर्ण
	पूर्ण

	वापस 0;
err:
	kमुक्त(request);
	usb_मुक्त_urb(urb);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक zd1201_अ_लोonfig16(काष्ठा zd1201 *zd, पूर्णांक rid, लघु *val)
अणु
	पूर्णांक err;
	__le16 zdval;

	err = zd1201_अ_लोonfig(zd, rid, &zdval, माप(__le16));
	अगर (err)
		वापस err;
	*val = le16_to_cpu(zdval);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक zd1201_setconfig16(काष्ठा zd1201 *zd, पूर्णांक rid, लघु val)
अणु
	__le16 zdval = cpu_to_le16(val);
	वापस (zd1201_setconfig(zd, rid, &zdval, माप(__le16), 1));
पूर्ण

अटल पूर्णांक zd1201_drvr_start(काष्ठा zd1201 *zd)
अणु
	पूर्णांक err, i;
	लघु max;
	__le16 zdmax;
	अचिन्हित अक्षर *buffer;

	buffer = kzalloc(ZD1201_RXSIZE, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	usb_fill_bulk_urb(zd->rx_urb, zd->usb, 
	    usb_rcvbulkpipe(zd->usb, zd->endp_in), buffer, ZD1201_RXSIZE,
	    zd1201_usbrx, zd);

	err = usb_submit_urb(zd->rx_urb, GFP_KERNEL);
	अगर (err)
		जाओ err_buffer;

	err = zd1201_करोcmd(zd, ZD1201_CMDCODE_INIT, 0, 0, 0);
	अगर (err)
		जाओ err_urb;

	err = zd1201_अ_लोonfig(zd, ZD1201_RID_CNFMAXTXBUFFERNUMBER, &zdmax,
	    माप(__le16));
	अगर (err)
		जाओ err_urb;

	max = le16_to_cpu(zdmax);
	क्रम (i=0; i<max; i++) अणु
		err = zd1201_करोcmd(zd, ZD1201_CMDCODE_ALLOC, 1514, 0, 0);
		अगर (err)
			जाओ err_urb;
	पूर्ण

	वापस 0;

err_urb:
	usb_समाप्त_urb(zd->rx_urb);
	वापस err;
err_buffer:
	kमुक्त(buffer);
	वापस err;
पूर्ण

/*	Magic alert: The firmware करोesn't seem to like the MAC state being
 *	toggled in promisc (aka monitor) mode.
 *	(It works a number of बार, but will halt eventually)
 *	So we turn it of beक्रमe disabling and on after enabling अगर needed.
 */
अटल पूर्णांक zd1201_enable(काष्ठा zd1201 *zd)
अणु
	पूर्णांक err;

	अगर (zd->mac_enabled)
		वापस 0;

	err = zd1201_करोcmd(zd, ZD1201_CMDCODE_ENABLE, 0, 0, 0);
	अगर (!err)
		zd->mac_enabled = 1;

	अगर (zd->monitor)
		err = zd1201_setconfig16(zd, ZD1201_RID_PROMISCUOUSMODE, 1);

	वापस err;
पूर्ण

अटल पूर्णांक zd1201_disable(काष्ठा zd1201 *zd)
अणु
	पूर्णांक err;

	अगर (!zd->mac_enabled)
		वापस 0;
	अगर (zd->monitor) अणु
		err = zd1201_setconfig16(zd, ZD1201_RID_PROMISCUOUSMODE, 0);
		अगर (err)
			वापस err;
	पूर्ण

	err = zd1201_करोcmd(zd, ZD1201_CMDCODE_DISABLE, 0, 0, 0);
	अगर (!err)
		zd->mac_enabled = 0;
	वापस err;
पूर्ण

अटल पूर्णांक zd1201_mac_reset(काष्ठा zd1201 *zd)
अणु
	अगर (!zd->mac_enabled)
		वापस 0;
	zd1201_disable(zd);
	वापस zd1201_enable(zd);
पूर्ण

अटल पूर्णांक zd1201_join(काष्ठा zd1201 *zd, अक्षर *essid, पूर्णांक essidlen)
अणु
	पूर्णांक err, val;
	अक्षर buf[IW_ESSID_MAX_SIZE+2];

	err = zd1201_disable(zd);
	अगर (err)
		वापस err;

	val = ZD1201_CNFAUTHENTICATION_OPENSYSTEM;
	val |= ZD1201_CNFAUTHENTICATION_SHAREDKEY;
	err = zd1201_setconfig16(zd, ZD1201_RID_CNFAUTHENTICATION, val);
	अगर (err)
		वापस err;

	*(__le16 *)buf = cpu_to_le16(essidlen);
	स_नकल(buf+2, essid, essidlen);
	अगर (!zd->ap) अणु	/* Normal station */
		err = zd1201_setconfig(zd, ZD1201_RID_CNFDESIREDSSID, buf,
		    IW_ESSID_MAX_SIZE+2, 1);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु	/* AP */
		err = zd1201_setconfig(zd, ZD1201_RID_CNFOWNSSID, buf,
		    IW_ESSID_MAX_SIZE+2, 1);
		अगर (err)
			वापस err;
	पूर्ण

	err = zd1201_setconfig(zd, ZD1201_RID_CNFOWNMACADDR, 
	    zd->dev->dev_addr, zd->dev->addr_len, 1);
	अगर (err)
		वापस err;

	err = zd1201_enable(zd);
	अगर (err)
		वापस err;

	msleep(100);
	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);

	/* Start MAC with wildcard अगर no essid set */
	अगर (!zd->mac_enabled)
		zd1201_join(zd, zd->essid, zd->essidlen);
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_net_stop(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

/*
	RFC 1042 encapsulates Ethernet frames in 802.11 frames
	by prefixing them with 0xaa, 0xaa, 0x03) followed by a SNAP OID of 0
	(0x00, 0x00, 0x00). Zd requires an additional padding, copy
	of ethernet addresses, length of the standard RFC 1042 packet
	and a command byte (which is nul क्रम tx).
	
	tx frame (from Wlan NG):
	RFC 1042:
		llc		0xAA 0xAA 0x03 (802.2 LLC)
		snap		0x00 0x00 0x00 (Ethernet encapsulated)
		type		2 bytes, Ethernet type field
		payload		(minus eth header)
	Zydas specअगरic:
		padding		1B अगर (skb->len+8+1)%64==0
		Eth MAC addr	12 bytes, Ethernet MAC addresses
		length		2 bytes, RFC 1042 packet length 
				(llc+snap+type+payload)
		zd		1 null byte, zd1201 packet type
 */
अटल netdev_tx_t zd1201_hard_start_xmit(काष्ठा sk_buff *skb,
						काष्ठा net_device *dev)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	अचिन्हित अक्षर *txbuf = zd->txdata;
	पूर्णांक txbuflen, pad = 0, err;
	काष्ठा urb *urb = zd->tx_urb;

	अगर (!zd->mac_enabled || zd->monitor) अणु
		dev->stats.tx_dropped++;
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	netअगर_stop_queue(dev);

	txbuflen = skb->len + 8 + 1;
	अगर (txbuflen%64 == 0) अणु
		pad = 1;
		txbuflen++;
	पूर्ण
	txbuf[0] = 0xAA;
	txbuf[1] = 0xAA;
	txbuf[2] = 0x03;
	txbuf[3] = 0x00;	/* rfc1042 */
	txbuf[4] = 0x00;
	txbuf[5] = 0x00;

	skb_copy_from_linear_data_offset(skb, 12, txbuf + 6, skb->len - 12);
	अगर (pad)
		txbuf[skb->len-12+6]=0;
	skb_copy_from_linear_data(skb, txbuf + skb->len - 12 + 6 + pad, 12);
	*(__be16*)&txbuf[skb->len+6+pad] = htons(skb->len-12+6);
	txbuf[txbuflen-1] = 0;

	usb_fill_bulk_urb(urb, zd->usb, usb_sndbulkpipe(zd->usb, zd->endp_out),
	    txbuf, txbuflen, zd1201_usbtx, zd);

	err = usb_submit_urb(zd->tx_urb, GFP_ATOMIC);
	अगर (err) अणु
		dev->stats.tx_errors++;
		netअगर_start_queue(dev);
	पूर्ण अन्यथा अणु
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb->len;
	पूर्ण
	kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम zd1201_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);

	अगर (!zd)
		वापस;
	dev_warn(&zd->usb->dev, "%s: TX timeout, shooting down urb\n",
	    dev->name);
	usb_unlink_urb(zd->tx_urb);
	dev->stats.tx_errors++;
	/* Restart the समयout to quiet the watchकरोg: */
	netअगर_trans_update(dev); /* prevent tx समयout */
पूर्ण

अटल पूर्णांक zd1201_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा zd1201 *zd = netdev_priv(dev);
	पूर्णांक err;

	अगर (!zd)
		वापस -ENODEV;

	err = zd1201_setconfig(zd, ZD1201_RID_CNFOWNMACADDR, 
	    addr->sa_data, dev->addr_len, 1);
	अगर (err)
		वापस err;
	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	वापस zd1201_mac_reset(zd);
पूर्ण

अटल काष्ठा iw_statistics *zd1201_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);

	वापस &zd->iwstats;
पूर्ण

अटल व्योम zd1201_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित अक्षर reqbuf[ETH_ALEN*ZD1201_MAXMULTI];
	पूर्णांक i;

	अगर (netdev_mc_count(dev) > ZD1201_MAXMULTI)
		वापस;

	i = 0;
	netdev_क्रम_each_mc_addr(ha, dev)
		स_नकल(reqbuf + i++ * ETH_ALEN, ha->addr, ETH_ALEN);
	zd1201_setconfig(zd, ZD1201_RID_CNFGROUPADDRESS, reqbuf,
			 netdev_mc_count(dev) * ETH_ALEN, 0);
पूर्ण

अटल पूर्णांक zd1201_config_commit(काष्ठा net_device *dev, 
    काष्ठा iw_request_info *info, काष्ठा iw_poपूर्णांक *data, अक्षर *essid)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);

	वापस zd1201_mac_reset(zd);
पूर्ण

अटल पूर्णांक zd1201_get_name(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, अक्षर *name, अक्षर *extra)
अणु
	म_नकल(name, "IEEE 802.11b");
	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_set_freq(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_freq *freq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु channel = 0;
	पूर्णांक err;

	अगर (freq->e == 0)
		channel = freq->m;
	अन्यथा
		channel = ieee80211_frequency_to_channel(freq->m);

	err = zd1201_setconfig16(zd, ZD1201_RID_CNFOWNCHANNEL, channel);
	अगर (err)
		वापस err;

	zd1201_mac_reset(zd);

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_get_freq(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_freq *freq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु channel;
	पूर्णांक err;

	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFOWNCHANNEL, &channel);
	अगर (err)
		वापस err;
	freq->e = 0;
	freq->m = channel;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_set_mode(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, __u32 *mode, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु porttype, monitor = 0;
	अचिन्हित अक्षर buffer[IW_ESSID_MAX_SIZE+2];
	पूर्णांक err;

	अगर (zd->ap) अणु
		अगर (*mode != IW_MODE_MASTER)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	err = zd1201_setconfig16(zd, ZD1201_RID_PROMISCUOUSMODE, 0);
	अगर (err)
		वापस err;
	zd->dev->type = ARPHRD_ETHER;
	चयन(*mode) अणु
		हाल IW_MODE_MONITOR:
			monitor = 1;
			zd->dev->type = ARPHRD_IEEE80211;
			/* Make sure we are no दीर्घer associated with by
			   setting an 'impossible' essid.
			   (otherwise we mess up firmware)
			 */
			zd1201_join(zd, "\0-*#\0", 5);
			/* Put port in pIBSS */
			fallthrough;
		हाल 8: /* No pseuकरो-IBSS in wireless extensions (yet) */
			porttype = ZD1201_PORTTYPE_PSEUDOIBSS;
			अवरोध;
		हाल IW_MODE_ADHOC:
			porttype = ZD1201_PORTTYPE_IBSS;
			अवरोध;
		हाल IW_MODE_INFRA:
			porttype = ZD1201_PORTTYPE_BSS;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	err = zd1201_setconfig16(zd, ZD1201_RID_CNFPORTTYPE, porttype);
	अगर (err)
		वापस err;
	अगर (zd->monitor && !monitor) अणु
			zd1201_disable(zd);
			*(__le16 *)buffer = cpu_to_le16(zd->essidlen);
			स_नकल(buffer+2, zd->essid, zd->essidlen);
			err = zd1201_setconfig(zd, ZD1201_RID_CNFDESIREDSSID,
			    buffer, IW_ESSID_MAX_SIZE+2, 1);
			अगर (err)
				वापस err;
	पूर्ण
	zd->monitor = monitor;
	/* If monitor mode is set we करोn't actually turn it on here since it
	 * is करोne during mac reset anyway (see zd1201_mac_enable).
	 */
	zd1201_mac_reset(zd);

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_get_mode(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, __u32 *mode, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु porttype;
	पूर्णांक err;

	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFPORTTYPE, &porttype);
	अगर (err)
		वापस err;
	चयन(porttype) अणु
		हाल ZD1201_PORTTYPE_IBSS:
			*mode = IW_MODE_ADHOC;
			अवरोध;
		हाल ZD1201_PORTTYPE_BSS:
			*mode = IW_MODE_INFRA;
			अवरोध;
		हाल ZD1201_PORTTYPE_WDS:
			*mode = IW_MODE_REPEAT;
			अवरोध;
		हाल ZD1201_PORTTYPE_PSEUDOIBSS:
			*mode = 8;/* No Pseuकरो-IBSS... */
			अवरोध;
		हाल ZD1201_PORTTYPE_AP:
			*mode = IW_MODE_MASTER;
			अवरोध;
		शेष:
			dev_dbg(&zd->usb->dev, "Unknown porttype: %d\n",
			    porttype);
			*mode = IW_MODE_AUTO;
	पूर्ण
	अगर (zd->monitor)
		*mode = IW_MODE_MONITOR;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_get_range(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_poपूर्णांक *wrq, अक्षर *extra)
अणु
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;

	wrq->length = माप(काष्ठा iw_range);
	स_रखो(range, 0, माप(काष्ठा iw_range));
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = WIRELESS_EXT;

	range->max_qual.qual = 128;
	range->max_qual.level = 128;
	range->max_qual.noise = 128;
	range->max_qual.updated = 7;

	range->encoding_size[0] = 5;
	range->encoding_size[1] = 13;
	range->num_encoding_sizes = 2;
	range->max_encoding_tokens = ZD1201_NUMKEYS;

	range->num_bitrates = 4;
	range->bitrate[0] = 1000000;
	range->bitrate[1] = 2000000;
	range->bitrate[2] = 5500000;
	range->bitrate[3] = 11000000;

	range->min_rts = 0;
	range->min_frag = ZD1201_FRAGMIN;
	range->max_rts = ZD1201_RTSMAX;
	range->min_frag = ZD1201_FRAGMAX;

	वापस 0;
पूर्ण

/*	Little bit of magic here: we only get the quality अगर we poll
 *	क्रम it, and we never get an actual request to trigger such
 *	a poll. Thereक्रमe we 'assume' that the user will soon ask क्रम
 *	the stats after asking the bssid.
 */
अटल पूर्णांक zd1201_get_wap(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा sockaddr *ap_addr, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	अचिन्हित अक्षर buffer[6];

	अगर (!zd1201_अ_लोonfig(zd, ZD1201_RID_COMMSQUALITY, buffer, 6)) अणु
		/* Unक्रमtunately the quality and noise reported is useless.
		   they seem to be accumulators that increase until you
		   पढ़ो them, unless we poll on a fixed पूर्णांकerval we can't
		   use them
		 */
		/*zd->iwstats.qual.qual = le16_to_cpu(((__le16 *)buffer)[0]);*/
		zd->iwstats.qual.level = le16_to_cpu(((__le16 *)buffer)[1]);
		/*zd->iwstats.qual.noise = le16_to_cpu(((__le16 *)buffer)[2]);*/
		zd->iwstats.qual.updated = 2;
	पूर्ण

	वापस zd1201_अ_लोonfig(zd, ZD1201_RID_CURRENTBSSID, ap_addr->sa_data, 6);
पूर्ण

अटल पूर्णांक zd1201_set_scan(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_poपूर्णांक *srq, अक्षर *extra)
अणु
	/* We करो everything in get_scan */
	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_get_scan(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_poपूर्णांक *srq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	पूर्णांक err, i, j, enabled_save;
	काष्ठा iw_event iwe;
	अक्षर *cev = extra;
	अक्षर *end_buf = extra + IW_SCAN_MAX_DATA;

	/* No scanning in AP mode */
	अगर (zd->ap)
		वापस -EOPNOTSUPP;

	/* Scan करोesn't seem to work अगर disabled */
	enabled_save = zd->mac_enabled;
	zd1201_enable(zd);

	zd->rxdatas = 0;
	err = zd1201_करोcmd(zd, ZD1201_CMDCODE_INQUIRE, 
	     ZD1201_INQ_SCANRESULTS, 0, 0);
	अगर (err)
		वापस err;

	रुको_event_पूर्णांकerruptible(zd->rxdataq, zd->rxdatas);
	अगर (!zd->rxlen)
		वापस -EIO;

	अगर (le16_to_cpu(*(__le16*)&zd->rxdata[2]) != ZD1201_INQ_SCANRESULTS)
		वापस -EIO;

	क्रम(i=8; i<zd->rxlen; i+=62) अणु
		iwe.cmd = SIOCGIWAP;
		iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
		स_नकल(iwe.u.ap_addr.sa_data, zd->rxdata+i+6, 6);
		cev = iwe_stream_add_event(info, cev, end_buf,
					   &iwe, IW_EV_ADDR_LEN);

		iwe.cmd = SIOCGIWESSID;
		iwe.u.data.length = zd->rxdata[i+16];
		iwe.u.data.flags = 1;
		cev = iwe_stream_add_poपूर्णांक(info, cev, end_buf,
					   &iwe, zd->rxdata+i+18);

		iwe.cmd = SIOCGIWMODE;
		अगर (zd->rxdata[i+14]&0x01)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_ADHOC;
		cev = iwe_stream_add_event(info, cev, end_buf,
					   &iwe, IW_EV_UINT_LEN);
		
		iwe.cmd = SIOCGIWFREQ;
		iwe.u.freq.m = zd->rxdata[i+0];
		iwe.u.freq.e = 0;
		cev = iwe_stream_add_event(info, cev, end_buf,
					   &iwe, IW_EV_FREQ_LEN);
		
		iwe.cmd = SIOCGIWRATE;
		iwe.u.bitrate.fixed = 0;
		iwe.u.bitrate.disabled = 0;
		क्रम (j=0; j<10; j++) अगर (zd->rxdata[i+50+j]) अणु
			iwe.u.bitrate.value = (zd->rxdata[i+50+j]&0x7f)*500000;
			cev = iwe_stream_add_event(info, cev, end_buf,
						   &iwe, IW_EV_PARAM_LEN);
		पूर्ण
		
		iwe.cmd = SIOCGIWENCODE;
		iwe.u.data.length = 0;
		अगर (zd->rxdata[i+14]&0x10)
			iwe.u.data.flags = IW_ENCODE_ENABLED;
		अन्यथा
			iwe.u.data.flags = IW_ENCODE_DISABLED;
		cev = iwe_stream_add_poपूर्णांक(info, cev, end_buf, &iwe, शून्य);
		
		iwe.cmd = IWEVQUAL;
		iwe.u.qual.qual = zd->rxdata[i+4];
		iwe.u.qual.noise= zd->rxdata[i+2]/10-100;
		iwe.u.qual.level = (256+zd->rxdata[i+4]*100)/255-100;
		iwe.u.qual.updated = 7;
		cev = iwe_stream_add_event(info, cev, end_buf,
					   &iwe, IW_EV_QUAL_LEN);
	पूर्ण

	अगर (!enabled_save)
		zd1201_disable(zd);

	srq->length = cev - extra;
	srq->flags = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_set_essid(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_poपूर्णांक *data, अक्षर *essid)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);

	अगर (data->length > IW_ESSID_MAX_SIZE)
		वापस -EINVAL;
	अगर (data->length < 1)
		data->length = 1;
	zd->essidlen = data->length;
	स_रखो(zd->essid, 0, IW_ESSID_MAX_SIZE+1);
	स_नकल(zd->essid, essid, data->length);
	वापस zd1201_join(zd, zd->essid, zd->essidlen);
पूर्ण

अटल पूर्णांक zd1201_get_essid(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_poपूर्णांक *data, अक्षर *essid)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);

	स_नकल(essid, zd->essid, zd->essidlen);
	data->flags = 1;
	data->length = zd->essidlen;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_get_nick(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
    काष्ठा iw_poपूर्णांक *data, अक्षर *nick)
अणु
	म_नकल(nick, "zd1201");
	data->flags = 1;
	data->length = म_माप(nick);
	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_set_rate(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु rate;
	पूर्णांक err;

	चयन (rrq->value) अणु
		हाल 1000000:
			rate = ZD1201_RATEB1;
			अवरोध;
		हाल 2000000:
			rate = ZD1201_RATEB2;
			अवरोध;
		हाल 5500000:
			rate = ZD1201_RATEB5;
			अवरोध;
		हाल 11000000:
		शेष:
			rate = ZD1201_RATEB11;
			अवरोध;
	पूर्ण
	अगर (!rrq->fixed) अणु /* Also enable all lower bitrates */
		rate |= rate-1;
	पूर्ण

	err = zd1201_setconfig16(zd, ZD1201_RID_TXRATECNTL, rate);
	अगर (err)
		वापस err;

	वापस zd1201_mac_reset(zd);
पूर्ण

अटल पूर्णांक zd1201_get_rate(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु rate;
	पूर्णांक err;

	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CURRENTTXRATE, &rate);
	अगर (err)
		वापस err;

	चयन(rate) अणु
		हाल 1:
			rrq->value = 1000000;
			अवरोध;
		हाल 2:
			rrq->value = 2000000;
			अवरोध;
		हाल 5:
			rrq->value = 5500000;
			अवरोध;
		हाल 11:
			rrq->value = 11000000;
			अवरोध;
		शेष:
			rrq->value = 0;
	पूर्ण
	rrq->fixed = 0;
	rrq->disabled = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_set_rts(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
    काष्ठा iw_param *rts, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	पूर्णांक err;
	लघु val = rts->value;

	अगर (rts->disabled || !rts->fixed)
		val = ZD1201_RTSMAX;
	अगर (val > ZD1201_RTSMAX)
		वापस -EINVAL;
	अगर (val < 0)
		वापस -EINVAL;

	err = zd1201_setconfig16(zd, ZD1201_RID_CNFRTSTHRESHOLD, val);
	अगर (err)
		वापस err;
	वापस zd1201_mac_reset(zd);
पूर्ण

अटल पूर्णांक zd1201_get_rts(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
    काष्ठा iw_param *rts, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु rtst;
	पूर्णांक err;

	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFRTSTHRESHOLD, &rtst);
	अगर (err)
		वापस err;
	rts->value = rtst;
	rts->disabled = (rts->value == ZD1201_RTSMAX);
	rts->fixed = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_set_frag(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
    काष्ठा iw_param *frag, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	पूर्णांक err;
	लघु val = frag->value;

	अगर (frag->disabled || !frag->fixed)
		val = ZD1201_FRAGMAX;
	अगर (val > ZD1201_FRAGMAX)
		वापस -EINVAL;
	अगर (val < ZD1201_FRAGMIN)
		वापस -EINVAL;
	अगर (val & 1)
		वापस -EINVAL;
	err = zd1201_setconfig16(zd, ZD1201_RID_CNFFRAGTHRESHOLD, val);
	अगर (err)
		वापस err;
	वापस zd1201_mac_reset(zd);
पूर्ण

अटल पूर्णांक zd1201_get_frag(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
    काष्ठा iw_param *frag, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु fragt;
	पूर्णांक err;

	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFFRAGTHRESHOLD, &fragt);
	अगर (err)
		वापस err;
	frag->value = fragt;
	frag->disabled = (frag->value == ZD1201_FRAGMAX);
	frag->fixed = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_set_retry(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_get_retry(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_set_encode(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_poपूर्णांक *erq, अक्षर *key)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु i;
	पूर्णांक err, rid;

	अगर (erq->length > ZD1201_MAXKEYLEN)
		वापस -EINVAL;

	i = (erq->flags & IW_ENCODE_INDEX)-1;
	अगर (i == -1) अणु
		err = zd1201_अ_लोonfig16(zd,ZD1201_RID_CNFDEFAULTKEYID,&i);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = zd1201_setconfig16(zd, ZD1201_RID_CNFDEFAULTKEYID, i);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (i < 0 || i >= ZD1201_NUMKEYS)
		वापस -EINVAL;

	rid = ZD1201_RID_CNFDEFAULTKEY0 + i;
	err = zd1201_setconfig(zd, rid, key, erq->length, 1);
	अगर (err)
		वापस err;
	zd->encode_keylen[i] = erq->length;
	स_नकल(zd->encode_keys[i], key, erq->length);

	i=0;
	अगर (!(erq->flags & IW_ENCODE_DISABLED & IW_ENCODE_MODE)) अणु
		i |= 0x01;
		zd->encode_enabled = 1;
	पूर्ण अन्यथा
		zd->encode_enabled = 0;
	अगर (erq->flags & IW_ENCODE_RESTRICTED & IW_ENCODE_MODE) अणु
		i |= 0x02;
		zd->encode_restricted = 1;
	पूर्ण अन्यथा
		zd->encode_restricted = 0;
	err = zd1201_setconfig16(zd, ZD1201_RID_CNFWEBFLAGS, i);
	अगर (err)
		वापस err;

	अगर (zd->encode_enabled)
		i = ZD1201_CNFAUTHENTICATION_SHAREDKEY;
	अन्यथा
		i = ZD1201_CNFAUTHENTICATION_OPENSYSTEM;
	err = zd1201_setconfig16(zd, ZD1201_RID_CNFAUTHENTICATION, i);
	अगर (err)
		वापस err;

	वापस zd1201_mac_reset(zd);
पूर्ण

अटल पूर्णांक zd1201_get_encode(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_poपूर्णांक *erq, अक्षर *key)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु i;
	पूर्णांक err;

	अगर (zd->encode_enabled)
		erq->flags = IW_ENCODE_ENABLED;
	अन्यथा
		erq->flags = IW_ENCODE_DISABLED;
	अगर (zd->encode_restricted)
		erq->flags |= IW_ENCODE_RESTRICTED;
	अन्यथा
		erq->flags |= IW_ENCODE_OPEN;

	i = (erq->flags & IW_ENCODE_INDEX) -1;
	अगर (i == -1) अणु
		err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFDEFAULTKEYID, &i);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (i<0 || i>= ZD1201_NUMKEYS)
		वापस -EINVAL;

	erq->flags |= i+1;

	erq->length = zd->encode_keylen[i];
	स_नकल(key, zd->encode_keys[i], erq->length);

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_set_घातer(काष्ठा net_device *dev, 
    काष्ठा iw_request_info *info, काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु enabled, duration, level;
	पूर्णांक err;

	enabled = vwrq->disabled ? 0 : 1;
	अगर (enabled) अणु
		अगर (vwrq->flags & IW_POWER_PERIOD) अणु
			duration = vwrq->value;
			err = zd1201_setconfig16(zd, 
			    ZD1201_RID_CNFMAXSLEEPDURATION, duration);
			अगर (err)
				वापस err;
			जाओ out;
		पूर्ण
		अगर (vwrq->flags & IW_POWER_TIMEOUT) अणु
			err = zd1201_अ_लोonfig16(zd, 
			    ZD1201_RID_CNFMAXSLEEPDURATION, &duration);
			अगर (err)
				वापस err;
			level = vwrq->value * 4 / duration;
			अगर (level > 4)
				level = 4;
			अगर (level < 0)
				level = 0;
			err = zd1201_setconfig16(zd, ZD1201_RID_CNFPMEPS,
			    level);
			अगर (err)
				वापस err;
			जाओ out;
		पूर्ण
		वापस -EINVAL;
	पूर्ण
out:
	वापस zd1201_setconfig16(zd, ZD1201_RID_CNFPMENABLED, enabled);
पूर्ण

अटल पूर्णांक zd1201_get_घातer(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु enabled, level, duration;
	पूर्णांक err;

	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFPMENABLED, &enabled);
	अगर (err)
		वापस err;
	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFPMEPS, &level);
	अगर (err)
		वापस err;
	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFMAXSLEEPDURATION, &duration);
	अगर (err)
		वापस err;
	vwrq->disabled = enabled ? 0 : 1;
	अगर (vwrq->flags & IW_POWER_TYPE) अणु
		अगर (vwrq->flags & IW_POWER_PERIOD) अणु
			vwrq->value = duration;
			vwrq->flags = IW_POWER_PERIOD;
		पूर्ण अन्यथा अणु
			vwrq->value = duration * level / 4;
			vwrq->flags = IW_POWER_TIMEOUT;
		पूर्ण
	पूर्ण
	अगर (vwrq->flags & IW_POWER_MODE) अणु
		अगर (enabled && level)
			vwrq->flags = IW_POWER_UNICAST_R;
		अन्यथा
			vwrq->flags = IW_POWER_ALL_R;
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर iw_handler zd1201_iw_handler[] =
अणु
	(iw_handler) zd1201_config_commit,	/* SIOCSIWCOMMIT */
	(iw_handler) zd1201_get_name,    	/* SIOCGIWNAME */
	(iw_handler) शून्य,			/* SIOCSIWNWID */
	(iw_handler) शून्य,			/* SIOCGIWNWID */
	(iw_handler) zd1201_set_freq,		/* SIOCSIWFREQ */
	(iw_handler) zd1201_get_freq,		/* SIOCGIWFREQ */
	(iw_handler) zd1201_set_mode,		/* SIOCSIWMODE */
	(iw_handler) zd1201_get_mode,		/* SIOCGIWMODE */
	(iw_handler) शून्य,                  	/* SIOCSIWSENS */
	(iw_handler) शून्य,           		/* SIOCGIWSENS */
	(iw_handler) शून्य,			/* SIOCSIWRANGE */
	(iw_handler) zd1201_get_range,           /* SIOCGIWRANGE */
	(iw_handler) शून्य,			/* SIOCSIWPRIV */
	(iw_handler) शून्य,			/* SIOCGIWPRIV */
	(iw_handler) शून्य,			/* SIOCSIWSTATS */
	(iw_handler) शून्य,			/* SIOCGIWSTATS */
	(iw_handler) शून्य,			/* SIOCSIWSPY */
	(iw_handler) शून्य,			/* SIOCGIWSPY */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य/*zd1201_set_wap*/,		/* SIOCSIWAP */
	(iw_handler) zd1201_get_wap,		/* SIOCGIWAP */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,       		/* SIOCGIWAPLIST */
	(iw_handler) zd1201_set_scan,		/* SIOCSIWSCAN */
	(iw_handler) zd1201_get_scan,		/* SIOCGIWSCAN */
	(iw_handler) zd1201_set_essid,		/* SIOCSIWESSID */
	(iw_handler) zd1201_get_essid,		/* SIOCGIWESSID */
	(iw_handler) शून्य,         		/* SIOCSIWNICKN */
	(iw_handler) zd1201_get_nick, 		/* SIOCGIWNICKN */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) शून्य,			/* -- hole -- */
	(iw_handler) zd1201_set_rate,		/* SIOCSIWRATE */
	(iw_handler) zd1201_get_rate,		/* SIOCGIWRATE */
	(iw_handler) zd1201_set_rts,		/* SIOCSIWRTS */
	(iw_handler) zd1201_get_rts,		/* SIOCGIWRTS */
	(iw_handler) zd1201_set_frag,		/* SIOCSIWFRAG */
	(iw_handler) zd1201_get_frag,		/* SIOCGIWFRAG */
	(iw_handler) शून्य,         		/* SIOCSIWTXPOW */
	(iw_handler) शून्य,          		/* SIOCGIWTXPOW */
	(iw_handler) zd1201_set_retry,		/* SIOCSIWRETRY */
	(iw_handler) zd1201_get_retry,		/* SIOCGIWRETRY */
	(iw_handler) zd1201_set_encode,		/* SIOCSIWENCODE */
	(iw_handler) zd1201_get_encode,		/* SIOCGIWENCODE */
	(iw_handler) zd1201_set_घातer,		/* SIOCSIWPOWER */
	(iw_handler) zd1201_get_घातer,		/* SIOCGIWPOWER */
पूर्ण;

अटल पूर्णांक zd1201_set_hostauth(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);

	अगर (!zd->ap)
		वापस -EOPNOTSUPP;

	वापस zd1201_setconfig16(zd, ZD1201_RID_CNFHOSTAUTH, rrq->value);
पूर्ण

अटल पूर्णांक zd1201_get_hostauth(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु hostauth;
	पूर्णांक err;

	अगर (!zd->ap)
		वापस -EOPNOTSUPP;

	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFHOSTAUTH, &hostauth);
	अगर (err)
		वापस err;
	rrq->value = hostauth;
	rrq->fixed = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक zd1201_auth_sta(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा sockaddr *sta, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	अचिन्हित अक्षर buffer[10];

	अगर (!zd->ap)
		वापस -EOPNOTSUPP;

	स_नकल(buffer, sta->sa_data, ETH_ALEN);
	*(लघु*)(buffer+6) = 0;	/* 0==success, 1==failure */
	*(लघु*)(buffer+8) = 0;

	वापस zd1201_setconfig(zd, ZD1201_RID_AUTHENTICATESTA, buffer, 10, 1);
पूर्ण

अटल पूर्णांक zd1201_set_maxassoc(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);

	अगर (!zd->ap)
		वापस -EOPNOTSUPP;

	वापस zd1201_setconfig16(zd, ZD1201_RID_CNFMAXASSOCSTATIONS, rrq->value);
पूर्ण

अटल पूर्णांक zd1201_get_maxassoc(काष्ठा net_device *dev,
    काष्ठा iw_request_info *info, काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा zd1201 *zd = netdev_priv(dev);
	लघु maxassoc;
	पूर्णांक err;

	अगर (!zd->ap)
		वापस -EOPNOTSUPP;

	err = zd1201_अ_लोonfig16(zd, ZD1201_RID_CNFMAXASSOCSTATIONS, &maxassoc);
	अगर (err)
		वापस err;
	rrq->value = maxassoc;
	rrq->fixed = 1;

	वापस 0;
पूर्ण

अटल स्थिर iw_handler zd1201_निजी_handler[] = अणु
	(iw_handler) zd1201_set_hostauth,	/* ZD1201SIWHOSTAUTH */
	(iw_handler) zd1201_get_hostauth,	/* ZD1201GIWHOSTAUTH */
	(iw_handler) zd1201_auth_sta,		/* ZD1201SIWAUTHSTA */
	(iw_handler) शून्य,			/* nothing to get */
	(iw_handler) zd1201_set_maxassoc,	/* ZD1201SIMAXASSOC */
	(iw_handler) zd1201_get_maxassoc,	/* ZD1201GIMAXASSOC */
पूर्ण;

अटल स्थिर काष्ठा iw_priv_args zd1201_निजी_args[] = अणु
	अणु ZD1201SIWHOSTAUTH, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	    IW_PRIV_TYPE_NONE, "sethostauth" पूर्ण,
	अणु ZD1201GIWHOSTAUTH, IW_PRIV_TYPE_NONE,
	    IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "gethostauth" पूर्ण,
	अणु ZD1201SIWAUTHSTA, IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1,
	    IW_PRIV_TYPE_NONE, "authstation" पूर्ण,
	अणु ZD1201SIWMAXASSOC, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	    IW_PRIV_TYPE_NONE, "setmaxassoc" पूर्ण,
	अणु ZD1201GIWMAXASSOC, IW_PRIV_TYPE_NONE,
	    IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getmaxassoc" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iw_handler_def zd1201_iw_handlers = अणु
	.num_standard 		= ARRAY_SIZE(zd1201_iw_handler),
	.num_निजी 		= ARRAY_SIZE(zd1201_निजी_handler),
	.num_निजी_args 	= ARRAY_SIZE(zd1201_निजी_args),
	.standard 		= (iw_handler *)zd1201_iw_handler,
	.निजी 		= (iw_handler *)zd1201_निजी_handler,
	.निजी_args 		= (काष्ठा iw_priv_args *) zd1201_निजी_args,
	.get_wireless_stats	= zd1201_get_wireless_stats,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops zd1201_netdev_ops = अणु
	.nकरो_खोलो		= zd1201_net_खोलो,
	.nकरो_stop		= zd1201_net_stop,
	.nकरो_start_xmit		= zd1201_hard_start_xmit,
	.nकरो_tx_समयout		= zd1201_tx_समयout,
	.nकरो_set_rx_mode	= zd1201_set_multicast,
	.nकरो_set_mac_address	= zd1201_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक zd1201_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा zd1201 *zd;
	काष्ठा net_device *dev;
	काष्ठा usb_device *usb;
	पूर्णांक err;
	लघु porttype;
	अक्षर buf[IW_ESSID_MAX_SIZE+2];

	usb = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	dev = alloc_etherdev(माप(*zd));
	अगर (!dev)
		वापस -ENOMEM;
	zd = netdev_priv(dev);
	zd->dev = dev;

	zd->ap = ap;
	zd->usb = usb;
	zd->हटाओd = 0;
	init_रुकोqueue_head(&zd->rxdataq);
	INIT_HLIST_HEAD(&zd->fraglist);
	
	err = zd1201_fw_upload(usb, zd->ap);
	अगर (err) अणु
		dev_err(&usb->dev, "zd1201 firmware upload failed: %d\n", err);
		जाओ err_zd;
	पूर्ण
	
	zd->endp_in = 1;
	zd->endp_out = 1;
	zd->endp_out2 = 2;
	zd->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	zd->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!zd->rx_urb || !zd->tx_urb) अणु
		err = -ENOMEM;
		जाओ err_zd;
	पूर्ण

	mdelay(100);
	err = zd1201_drvr_start(zd);
	अगर (err)
		जाओ err_zd;

	err = zd1201_setconfig16(zd, ZD1201_RID_CNFMAXDATALEN, 2312);
	अगर (err)
		जाओ err_start;

	err = zd1201_setconfig16(zd, ZD1201_RID_TXRATECNTL,
	    ZD1201_RATEB1 | ZD1201_RATEB2 | ZD1201_RATEB5 | ZD1201_RATEB11);
	अगर (err)
		जाओ err_start;

	dev->netdev_ops = &zd1201_netdev_ops;
	dev->wireless_handlers = &zd1201_iw_handlers;
	dev->watchकरोg_समयo = ZD1201_TX_TIMEOUT;
	म_नकल(dev->name, "wlan%d");

	err = zd1201_अ_लोonfig(zd, ZD1201_RID_CNFOWNMACADDR, 
	    dev->dev_addr, dev->addr_len);
	अगर (err)
		जाओ err_start;

	/* Set wildcard essid to match zd->essid */
	*(__le16 *)buf = cpu_to_le16(0);
	err = zd1201_setconfig(zd, ZD1201_RID_CNFDESIREDSSID, buf,
	    IW_ESSID_MAX_SIZE+2, 1);
	अगर (err)
		जाओ err_start;

	अगर (zd->ap)
		porttype = ZD1201_PORTTYPE_AP;
	अन्यथा
		porttype = ZD1201_PORTTYPE_BSS;
	err = zd1201_setconfig16(zd, ZD1201_RID_CNFPORTTYPE, porttype);
	अगर (err)
		जाओ err_start;

	SET_NETDEV_DEV(dev, &usb->dev);

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ err_start;
	dev_info(&usb->dev, "%s: ZD1201 USB Wireless interface\n",
	    dev->name);

	usb_set_पूर्णांकfdata(पूर्णांकerface, zd);
	zd1201_enable(zd);	/* zd1201 likes to startup enabled, */
	zd1201_disable(zd);	/* पूर्णांकerfering with all the wअगरis in range */
	वापस 0;

err_start:
	/* Leave the device in reset state */
	zd1201_करोcmd(zd, ZD1201_CMDCODE_INIT, 0, 0, 0);
err_zd:
	usb_मुक्त_urb(zd->tx_urb);
	usb_मुक्त_urb(zd->rx_urb);
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल व्योम zd1201_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा zd1201 *zd = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा hlist_node *node2;
	काष्ठा zd1201_frag *frag;

	अगर (!zd)
		वापस;
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	hlist_क्रम_each_entry_safe(frag, node2, &zd->fraglist, fnode) अणु
		hlist_del_init(&frag->fnode);
		kमुक्त_skb(frag->skb);
		kमुक्त(frag);
	पूर्ण

	अगर (zd->tx_urb) अणु
		usb_समाप्त_urb(zd->tx_urb);
		usb_मुक्त_urb(zd->tx_urb);
	पूर्ण
	अगर (zd->rx_urb) अणु
		usb_समाप्त_urb(zd->rx_urb);
		usb_मुक्त_urb(zd->rx_urb);
	पूर्ण

	अगर (zd->dev) अणु
		unरेजिस्टर_netdev(zd->dev);
		मुक्त_netdev(zd->dev);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक zd1201_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			   pm_message_t message)
अणु
	काष्ठा zd1201 *zd = usb_get_पूर्णांकfdata(पूर्णांकerface);

	netअगर_device_detach(zd->dev);

	zd->was_enabled = zd->mac_enabled;

	अगर (zd->was_enabled)
		वापस zd1201_disable(zd);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक zd1201_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा zd1201 *zd = usb_get_पूर्णांकfdata(पूर्णांकerface);

	अगर (!zd || !zd->dev)
		वापस -ENODEV;

	netअगर_device_attach(zd->dev);

	अगर (zd->was_enabled)
		वापस zd1201_enable(zd);
	अन्यथा
		वापस 0;
पूर्ण

#अन्यथा

#घोषणा zd1201_suspend शून्य
#घोषणा zd1201_resume  शून्य

#पूर्ण_अगर

अटल काष्ठा usb_driver zd1201_usb = अणु
	.name = "zd1201",
	.probe = zd1201_probe,
	.disconnect = zd1201_disconnect,
	.id_table = zd1201_table,
	.suspend = zd1201_suspend,
	.resume = zd1201_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(zd1201_usb);
