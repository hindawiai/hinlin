<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * usbusy2y.c - ALSA USB US-428 Driver
 *
2005-04-14 Karsten Wiese
	Version 0.8.7.2:
	Call snd_card_मुक्त() instead of snd_card_मुक्त_in_thपढ़ो() to prevent oops with dead keyboard symptom.
	Tested ok with kernel 2.6.12-rc2.

2004-12-14 Karsten Wiese
	Version 0.8.7.1:
	snd_pcm_खोलो क्रम rawusb pcm-devices now वापसs -EBUSY अगर called without rawusb's hwdep device being खोलो.

2004-12-02 Karsten Wiese
	Version 0.8.7:
	Use macro usb_maxpacket() क्रम portability.

2004-10-26 Karsten Wiese
	Version 0.8.6:
	wake_up() process रुकोing in usX2Y_urbs_start() on error.

2004-10-21 Karsten Wiese
	Version 0.8.5:
	nrpacks is runसमय or compileसमय configurable now with tested values from 1 to 4.

2004-10-03 Karsten Wiese
	Version 0.8.2:
	Aव्योम any possible racing जबतक in prepare callback.

2004-09-30 Karsten Wiese
	Version 0.8.0:
	Simplअगरied things and made ohci work again.

2004-09-20 Karsten Wiese
	Version 0.7.3:
	Use usb_समाप्त_urb() instead of deprecated (kernel 2.6.9) usb_unlink_urb().

2004-07-13 Karsten Wiese
	Version 0.7.1:
	Don't sleep in START/STOP callbacks anymore.
	us428 channels C/D not handled just क्रम this version, sorry.

2004-06-21 Karsten Wiese
	Version 0.6.4:
	Temporarely suspend midi input
	to sanely call usb_set_पूर्णांकerface() when setting क्रमmat.

2004-06-12 Karsten Wiese
	Version 0.6.3:
	Made it thus the following rule is enक्रमced:
	"All pcm substreams of one usX2Y have to operate at the same rate & format."

2004-04-06 Karsten Wiese
	Version 0.6.0:
	Runs on 2.6.5 kernel without any "--with-debug=" things.
	us224 reported running.

2004-01-14 Karsten Wiese
	Version 0.5.1:
	Runs with 2.6.1 kernel.

2003-12-30 Karsten Wiese
	Version 0.4.1:
	Fix 24Bit 4Channel capturing क्रम the us428.

2003-11-27 Karsten Wiese, Martin Langer
	Version 0.4:
	us122 support.
	us224 could be tested by uncommenting the sections containing USB_ID_US224

2003-11-03 Karsten Wiese
	Version 0.3:
	24Bit support. 
	"arecord -D hw:1 -c 2 -r 48000 -M -f S24_3LE|aplay -D hw:1 -c 2 -r 48000 -M -f S24_3LE" works.

2003-08-22 Karsten Wiese
	Version 0.0.8:
	Removed EZUSB Firmware. First Stage Firmwareकरोwnload is now करोne by tascam-firmware करोwnloader.
	See:
	http://usb-midi-fw.sourceक्रमge.net/tascam-firmware.tar.gz

2003-06-18 Karsten Wiese
	Version 0.0.5:
	changed to compile with kernel 2.4.21 and alsa 0.9.4

2002-10-16 Karsten Wiese
	Version 0.0.4:
	compiles again with alsa-current.
	USB_ISO_ASAP not used anymore (most of the समय), instead
	urb->start_frame is calculated here now, some calls inside usb-driver करोn't need to happen anymore.

	To get the best out of this:
	Disable APM-support in the kernel as APM-BIOS calls (once each second) hard disable पूर्णांकerrupt क्रम many precious milliseconds.
	This helped me much on my slowish PII 400 & PIII 500.
	ACPI yet untested but might cause the same bad behaviour.
	Use a kernel with lowlatency and preemptiv patches applied.
	To स्वतःload snd-usb-midi append a line 
		post-install snd-usb-us428 modprobe snd-usb-midi
	to /etc/modules.conf.

	known problems:
	sliders, knobs, lights not yet handled except MASTER Volume slider.
       	"pcm -c 2" करोesn't work. "pcm -c 2 -m direct_interleaved" करोes.
	KDE3: "Enable full duplex operation" deadlocks.

	
2002-08-31 Karsten Wiese
	Version 0.0.3: audio also simplex;
	simplअगरying: iso urbs only 1 packet, melted काष्ठाs.
	ASYNC_UNLINK not used anymore: no more crashes so far.....
	क्रम alsa 0.9 rc3.

2002-08-09 Karsten Wiese
	Version 0.0.2: midi works with snd-usb-midi, audio (only fullduplex now) with i.e. bristol.
	The firmware has been snअगरfed from win2k us-428 driver 3.09.

 *   Copyright (c) 2002 - 2004 Karsten Wiese
*/

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>

#समावेश <sound/rawmidi.h>
#समावेश "usx2y.h"
#समावेश "usbusx2y.h"
#समावेश "usX2Yhwdep.h"



MODULE_AUTHOR("Karsten Wiese <annabellesgarden@yahoo.de>");
MODULE_DESCRIPTION("TASCAM "NAME_ALLCAPS" Version 0.8.7.2");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX; /* Index 0-max */
अटल अक्षर* id[SNDRV_CARDS] = SNDRV_DEFAULT_STR; /* Id क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP; /* Enable this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for "NAME_ALLCAPS".");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for "NAME_ALLCAPS".");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable "NAME_ALLCAPS".");


अटल पूर्णांक snd_usX2Y_card_used[SNDRV_CARDS];

अटल व्योम usX2Y_usb_disconnect(काष्ठा usb_device* usb_device, व्योम* ptr);
अटल व्योम snd_usX2Y_card_निजी_मुक्त(काष्ठा snd_card *card);

/* 
 * pipe 4 is used क्रम चयनing the lamps, setting samplerate, volumes ....   
 */
अटल व्योम i_usX2Y_Out04Int(काष्ठा urb *urb)
अणु
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (urb->status) अणु
		पूर्णांक 		i;
		काष्ठा usX2Ydev *usX2Y = urb->context;
		क्रम (i = 0; i < 10 && usX2Y->AS04.urb[i] != urb; i++);
		snd_prपूर्णांकdd("i_usX2Y_Out04Int() urb %i status=%i\n", i, urb->status);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम i_usX2Y_In04Int(काष्ठा urb *urb)
अणु
	पूर्णांक			err = 0;
	काष्ठा usX2Ydev		*usX2Y = urb->context;
	काष्ठा us428ctls_sharedmem	*us428ctls = usX2Y->us428ctls_sharedmem;

	usX2Y->In04IntCalls++;

	अगर (urb->status) अणु
		snd_prपूर्णांकdd("Interrupt Pipe 4 came back with status=%i\n", urb->status);
		वापस;
	पूर्ण

	//	prपूर्णांकk("%i:0x%02X ", 8, (पूर्णांक)((अचिन्हित अक्षर*)usX2Y->In04Buf)[8]); Master volume shows 0 here अगर fader is at max during boot ?!?
	अगर (us428ctls) अणु
		पूर्णांक dअगरf = -1;
		अगर (-2 == us428ctls->CtlSnapShotLast) अणु
			dअगरf = 0;
			स_नकल(usX2Y->In04Last, usX2Y->In04Buf, माप(usX2Y->In04Last));
			us428ctls->CtlSnapShotLast = -1;
		पूर्ण अन्यथा अणु
			पूर्णांक i;
			क्रम (i = 0; i < 21; i++) अणु
				अगर (usX2Y->In04Last[i] != ((अक्षर*)usX2Y->In04Buf)[i]) अणु
					अगर (dअगरf < 0)
						dअगरf = i;
					usX2Y->In04Last[i] = ((अक्षर*)usX2Y->In04Buf)[i];
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (0 <= dअगरf) अणु
			पूर्णांक n = us428ctls->CtlSnapShotLast + 1;
			अगर (n >= N_us428_ctl_BUFS  ||  n < 0)
				n = 0;
			स_नकल(us428ctls->CtlSnapShot + n, usX2Y->In04Buf, माप(us428ctls->CtlSnapShot[0]));
			us428ctls->CtlSnapShotDअगरfersAt[n] = dअगरf;
			us428ctls->CtlSnapShotLast = n;
			wake_up(&usX2Y->us428ctls_रुको_queue_head);
		पूर्ण
	पूर्ण
	
	
	अगर (usX2Y->US04) अणु
		अगर (0 == usX2Y->US04->submitted)
			करो अणु
				err = usb_submit_urb(usX2Y->US04->urb[usX2Y->US04->submitted++], GFP_ATOMIC);
			पूर्ण जबतक (!err && usX2Y->US04->submitted < usX2Y->US04->len);
	पूर्ण अन्यथा
		अगर (us428ctls && us428ctls->p4outLast >= 0 && us428ctls->p4outLast < N_us428_p4out_BUFS) अणु
			अगर (us428ctls->p4outLast != us428ctls->p4outSent) अणु
				पूर्णांक j, send = us428ctls->p4outSent + 1;
				अगर (send >= N_us428_p4out_BUFS)
					send = 0;
				क्रम (j = 0; j < URBS_AsyncSeq  &&  !err; ++j)
					अगर (0 == usX2Y->AS04.urb[j]->status) अणु
						काष्ठा us428_p4out *p4out = us428ctls->p4out + send;	// FIXME अगर more than 1 p4out is new, 1 माला_लो lost.
						usb_fill_bulk_urb(usX2Y->AS04.urb[j], usX2Y->dev,
								  usb_sndbulkpipe(usX2Y->dev, 0x04), &p4out->val.vol,
								  p4out->type == eLT_Light ? माप(काष्ठा us428_lights) : 5,
								  i_usX2Y_Out04Int, usX2Y);
						err = usb_submit_urb(usX2Y->AS04.urb[j], GFP_ATOMIC);
						us428ctls->p4outSent = send;
						अवरोध;
					पूर्ण
			पूर्ण
		पूर्ण

	अगर (err)
		snd_prपूर्णांकk(KERN_ERR "In04Int() usb_submit_urb err=%i\n", err);

	urb->dev = usX2Y->dev;
	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

/*
 * Prepare some urbs
 */
पूर्णांक usX2Y_AsyncSeq04_init(काष्ठा usX2Ydev *usX2Y)
अणु
	पूर्णांक	err = 0,
		i;

	usX2Y->AS04.buffer = kदो_स्मृति_array(URBS_AsyncSeq,
					   URB_DataLen_AsyncSeq, GFP_KERNEL);
	अगर (शून्य == usX2Y->AS04.buffer) अणु
		err = -ENOMEM;
	पूर्ण अन्यथा
		क्रम (i = 0; i < URBS_AsyncSeq; ++i) अणु
			अगर (शून्य == (usX2Y->AS04.urb[i] = usb_alloc_urb(0, GFP_KERNEL))) अणु
				err = -ENOMEM;
				अवरोध;
			पूर्ण
			usb_fill_bulk_urb(	usX2Y->AS04.urb[i], usX2Y->dev,
						usb_sndbulkpipe(usX2Y->dev, 0x04),
						usX2Y->AS04.buffer + URB_DataLen_AsyncSeq*i, 0,
						i_usX2Y_Out04Int, usX2Y
				);
			err = usb_urb_ep_type_check(usX2Y->AS04.urb[i]);
			अगर (err < 0)
				अवरोध;
		पूर्ण
	वापस err;
पूर्ण

पूर्णांक usX2Y_In04_init(काष्ठा usX2Ydev *usX2Y)
अणु
	अगर (! (usX2Y->In04urb = usb_alloc_urb(0, GFP_KERNEL)))
		वापस -ENOMEM;

	अगर (! (usX2Y->In04Buf = kदो_स्मृति(21, GFP_KERNEL)))
		वापस -ENOMEM;
	 
	init_रुकोqueue_head(&usX2Y->In04WaitQueue);
	usb_fill_पूर्णांक_urb(usX2Y->In04urb, usX2Y->dev, usb_rcvपूर्णांकpipe(usX2Y->dev, 0x4),
			 usX2Y->In04Buf, 21,
			 i_usX2Y_In04Int, usX2Y,
			 10);
	अगर (usb_urb_ep_type_check(usX2Y->In04urb))
		वापस -EINVAL;
	वापस usb_submit_urb(usX2Y->In04urb, GFP_KERNEL);
पूर्ण

अटल व्योम usX2Y_unlinkSeq(काष्ठा snd_usX2Y_AsyncSeq *S)
अणु
	पूर्णांक	i;
	क्रम (i = 0; i < URBS_AsyncSeq; ++i) अणु
		usb_समाप्त_urb(S->urb[i]);
		usb_मुक्त_urb(S->urb[i]);
		S->urb[i] = शून्य;
	पूर्ण
	kमुक्त(S->buffer);
पूर्ण


अटल स्थिर काष्ठा usb_device_id snd_usX2Y_usb_id_table[] = अणु
	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	0x1604,
		.idProduct =	USB_ID_US428 
	पूर्ण,
	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	0x1604,
		.idProduct =	USB_ID_US122 
	पूर्ण,
 	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	0x1604,
		.idProduct =	USB_ID_US224
	पूर्ण,
	अणु /* terminator */ पूर्ण
पूर्ण;

अटल पूर्णांक usX2Y_create_card(काष्ठा usb_device *device,
			     काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     काष्ठा snd_card **cardp)
अणु
	पूर्णांक		dev;
	काष्ठा snd_card *	card;
	पूर्णांक err;

	क्रम (dev = 0; dev < SNDRV_CARDS; ++dev)
		अगर (enable[dev] && !snd_usX2Y_card_used[dev])
			अवरोध;
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	err = snd_card_new(&पूर्णांकf->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा usX2Ydev), &card);
	अगर (err < 0)
		वापस err;
	snd_usX2Y_card_used[usX2Y(card)->card_index = dev] = 1;
	card->निजी_मुक्त = snd_usX2Y_card_निजी_मुक्त;
	usX2Y(card)->dev = device;
	init_रुकोqueue_head(&usX2Y(card)->prepare_रुको_queue);
	mutex_init(&usX2Y(card)->pcm_mutex);
	INIT_LIST_HEAD(&usX2Y(card)->midi_list);
	म_नकल(card->driver, "USB "NAME_ALLCAPS"");
	प्र_लिखो(card->लघुname, "TASCAM "NAME_ALLCAPS"");
	प्र_लिखो(card->दीर्घname, "%s (%x:%x if %d at %03d/%03d)",
		card->लघुname, 
		le16_to_cpu(device->descriptor.idVenकरोr),
		le16_to_cpu(device->descriptor.idProduct),
		0,//us428(card)->usbmidi.अगरnum,
		usX2Y(card)->dev->bus->busnum, usX2Y(card)->dev->devnum
		);
	*cardp = card;
	वापस 0;
पूर्ण


अटल पूर्णांक usX2Y_usb_probe(काष्ठा usb_device *device,
			   काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *device_id,
			   काष्ठा snd_card **cardp)
अणु
	पूर्णांक		err;
	काष्ठा snd_card *	card;

	*cardp = शून्य;
	अगर (le16_to_cpu(device->descriptor.idVenकरोr) != 0x1604 ||
	    (le16_to_cpu(device->descriptor.idProduct) != USB_ID_US122 &&
	     le16_to_cpu(device->descriptor.idProduct) != USB_ID_US224 &&
	     le16_to_cpu(device->descriptor.idProduct) != USB_ID_US428))
		वापस -EINVAL;

	err = usX2Y_create_card(device, पूर्णांकf, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = usX2Y_hwdep_new(card, device)) < 0  ||
	    (err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	*cardp = card;
	वापस 0;
पूर्ण

/*
 * new 2.5 USB kernel API
 */
अटल पूर्णांक snd_usX2Y_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = usX2Y_usb_probe(पूर्णांकerface_to_usbdev(पूर्णांकf), पूर्णांकf, id, &card);
	अगर (err < 0)
		वापस err;
	dev_set_drvdata(&पूर्णांकf->dev, card);
	वापस 0;
पूर्ण

अटल व्योम snd_usX2Y_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	usX2Y_usb_disconnect(पूर्णांकerface_to_usbdev(पूर्णांकf),
				 usb_get_पूर्णांकfdata(पूर्णांकf));
पूर्ण

MODULE_DEVICE_TABLE(usb, snd_usX2Y_usb_id_table);
अटल काष्ठा usb_driver snd_usX2Y_usb_driver = अणु
	.name =		"snd-usb-usx2y",
	.probe =	snd_usX2Y_probe,
	.disconnect =	snd_usX2Y_disconnect,
	.id_table =	snd_usX2Y_usb_id_table,
पूर्ण;

अटल व्योम snd_usX2Y_card_निजी_मुक्त(काष्ठा snd_card *card)
अणु
	kमुक्त(usX2Y(card)->In04Buf);
	usb_मुक्त_urb(usX2Y(card)->In04urb);
	अगर (usX2Y(card)->us428ctls_sharedmem)
		मुक्त_pages_exact(usX2Y(card)->us428ctls_sharedmem,
				 माप(*usX2Y(card)->us428ctls_sharedmem));
	अगर (usX2Y(card)->card_index >= 0  &&  usX2Y(card)->card_index < SNDRV_CARDS)
		snd_usX2Y_card_used[usX2Y(card)->card_index] = 0;
पूर्ण

/*
 * Frees the device.
 */
अटल व्योम usX2Y_usb_disconnect(काष्ठा usb_device *device, व्योम* ptr)
अणु
	अगर (ptr) अणु
		काष्ठा snd_card *card = ptr;
		काष्ठा usX2Ydev *usX2Y = usX2Y(card);
		काष्ठा list_head *p;
		usX2Y->chip_status = USX2Y_STAT_CHIP_HUP;
		usX2Y_unlinkSeq(&usX2Y->AS04);
		usb_समाप्त_urb(usX2Y->In04urb);
		snd_card_disconnect(card);
		/* release the midi resources */
		list_क्रम_each(p, &usX2Y->midi_list) अणु
			snd_usbmidi_disconnect(p);
		पूर्ण
		अगर (usX2Y->us428ctls_sharedmem) 
			wake_up(&usX2Y->us428ctls_रुको_queue_head);
		snd_card_मुक्त(card);
	पूर्ण
पूर्ण

module_usb_driver(snd_usX2Y_usb_driver);
