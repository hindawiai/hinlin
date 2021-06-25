<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Tascam US-X2Y USB soundcards
 *
 * FPGA Loader + ALSA Startup
 *
 * Copyright (c) 2003 by Karsten Wiese <annabellesgarden@yahoo.de>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <sound/core.h>
#समावेश <sound/meदो_स्मृति.h>
#समावेश <sound/pcm.h>
#समावेश <sound/hwdep.h>
#समावेश "usx2y.h"
#समावेश "usbusx2y.h"
#समावेश "usX2Yhwdep.h"

अटल vm_fault_t snd_us428ctls_vm_fault(काष्ठा vm_fault *vmf)
अणु
	अचिन्हित दीर्घ offset;
	काष्ठा page * page;
	व्योम *vaddr;

	snd_prपूर्णांकdd("ENTER, start %lXh, pgoff %ld\n",
		   vmf->vma->vm_start,
		   vmf->pgoff);
	
	offset = vmf->pgoff << PAGE_SHIFT;
	vaddr = (अक्षर *)((काष्ठा usX2Ydev *)vmf->vma->vm_निजी_data)->us428ctls_sharedmem + offset;
	page = virt_to_page(vaddr);
	get_page(page);
	vmf->page = page;

	snd_prपूर्णांकdd("vaddr=%p made us428ctls_vm_fault() page %p\n",
		    vaddr, page);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा us428ctls_vm_ops = अणु
	.fault = snd_us428ctls_vm_fault,
पूर्ण;

अटल पूर्णांक snd_us428ctls_mmap(काष्ठा snd_hwdep * hw, काष्ठा file *filp, काष्ठा vm_area_काष्ठा *area)
अणु
	अचिन्हित दीर्घ	size = (अचिन्हित दीर्घ)(area->vm_end - area->vm_start);
	काष्ठा usX2Ydev	*us428 = hw->निजी_data;

	// FIXME this hwdep पूर्णांकerface is used twice: fpga करोwnload and mmap क्रम controlling Lights etc. Maybe better using 2 hwdep devs?
	// so as दीर्घ as the device isn't fully initialised yet we वापस -EBUSY here.
 	अगर (!(us428->chip_status & USX2Y_STAT_CHIP_INIT))
		वापस -EBUSY;

	/* अगर userspace tries to mmap beyond end of our buffer, fail */ 
        अगर (size > PAGE_ALIGN(माप(काष्ठा us428ctls_sharedmem))) अणु
		snd_prपूर्णांकd( "%lu > %lu\n", size, (अचिन्हित दीर्घ)माप(काष्ठा us428ctls_sharedmem)); 
                वापस -EINVAL;
	पूर्ण

	अगर (!us428->us428ctls_sharedmem) अणु
		init_रुकोqueue_head(&us428->us428ctls_रुको_queue_head);
		us428->us428ctls_sharedmem = alloc_pages_exact(माप(काष्ठा us428ctls_sharedmem), GFP_KERNEL);
		अगर (!us428->us428ctls_sharedmem)
			वापस -ENOMEM;
		स_रखो(us428->us428ctls_sharedmem, -1, माप(काष्ठा us428ctls_sharedmem));
		us428->us428ctls_sharedmem->CtlSnapShotLast = -2;
	पूर्ण
	area->vm_ops = &us428ctls_vm_ops;
	area->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	area->vm_निजी_data = hw->निजी_data;
	वापस 0;
पूर्ण

अटल __poll_t snd_us428ctls_poll(काष्ठा snd_hwdep *hw, काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t	mask = 0;
	काष्ठा usX2Ydev	*us428 = hw->निजी_data;
	काष्ठा us428ctls_sharedmem *shm = us428->us428ctls_sharedmem;
	अगर (us428->chip_status & USX2Y_STAT_CHIP_HUP)
		वापस EPOLLHUP;

	poll_रुको(file, &us428->us428ctls_रुको_queue_head, रुको);

	अगर (shm != शून्य && shm->CtlSnapShotLast != shm->CtlSnapShotRed)
		mask |= EPOLLIN;

	वापस mask;
पूर्ण


अटल पूर्णांक snd_usX2Y_hwdep_dsp_status(काष्ठा snd_hwdep *hw,
				      काष्ठा snd_hwdep_dsp_status *info)
अणु
	अटल स्थिर अक्षर * स्थिर type_ids[USX2Y_TYPE_NUMS] = अणु
		[USX2Y_TYPE_122] = "us122",
		[USX2Y_TYPE_224] = "us224",
		[USX2Y_TYPE_428] = "us428",
	पूर्ण;
	काष्ठा usX2Ydev	*us428 = hw->निजी_data;
	पूर्णांक id = -1;

	चयन (le16_to_cpu(us428->dev->descriptor.idProduct)) अणु
	हाल USB_ID_US122:
		id = USX2Y_TYPE_122;
		अवरोध;
	हाल USB_ID_US224:
		id = USX2Y_TYPE_224;
		अवरोध;
	हाल USB_ID_US428:
		id = USX2Y_TYPE_428;
		अवरोध;
	पूर्ण
	अगर (0 > id)
		वापस -ENODEV;
	म_नकल(info->id, type_ids[id]);
	info->num_dsps = 2;		// 0: Prepad Data, 1: FPGA Code
	अगर (us428->chip_status & USX2Y_STAT_CHIP_INIT)
		info->chip_पढ़ोy = 1;
	info->version = USX2Y_DRIVER_VERSION;
	वापस 0;
पूर्ण


अटल पूर्णांक usX2Y_create_usbmidi(काष्ठा snd_card *card)
अणु
	अटल स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info quirk_data_1 = अणु
		.out_ep = 0x06,
		.in_ep = 0x06,
		.out_cables =	0x001,
		.in_cables =	0x001
	पूर्ण;
	अटल स्थिर काष्ठा snd_usb_audio_quirk quirk_1 = अणु
		.venकरोr_name =	"TASCAM",
		.product_name =	NAME_ALLCAPS,
		.अगरnum = 	0,
       		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = &quirk_data_1
	पूर्ण;
	अटल स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info quirk_data_2 = अणु
		.out_ep = 0x06,
		.in_ep = 0x06,
		.out_cables =	0x003,
		.in_cables =	0x003
	पूर्ण;
	अटल स्थिर काष्ठा snd_usb_audio_quirk quirk_2 = अणु
		.venकरोr_name =	"TASCAM",
		.product_name =	"US428",
		.अगरnum = 	0,
       		.type = QUIRK_MIDI_FIXED_ENDPOINT,
		.data = &quirk_data_2
	पूर्ण;
	काष्ठा usb_device *dev = usX2Y(card)->dev;
	काष्ठा usb_पूर्णांकerface *अगरace = usb_अगरnum_to_अगर(dev, 0);
	स्थिर काष्ठा snd_usb_audio_quirk *quirk =
		le16_to_cpu(dev->descriptor.idProduct) == USB_ID_US428 ?
		&quirk_2 : &quirk_1;

	snd_prपूर्णांकdd("usX2Y_create_usbmidi \n");
	वापस snd_usbmidi_create(card, अगरace, &usX2Y(card)->midi_list, quirk);
पूर्ण

अटल पूर्णांक usX2Y_create_alsa_devices(काष्ठा snd_card *card)
अणु
	पूर्णांक err;

	करो अणु
		अगर ((err = usX2Y_create_usbmidi(card)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "usX2Y_create_alsa_devices: usX2Y_create_usbmidi error %i \n", err);
			अवरोध;
		पूर्ण
		अगर ((err = usX2Y_audio_create(card)) < 0) 
			अवरोध;
		अगर ((err = usX2Y_hwdep_pcm_new(card)) < 0)
			अवरोध;
		अगर ((err = snd_card_रेजिस्टर(card)) < 0)
			अवरोध;
	पूर्ण जबतक (0);

	वापस err;
पूर्ण 

अटल पूर्णांक snd_usX2Y_hwdep_dsp_load(काष्ठा snd_hwdep *hw,
				    काष्ठा snd_hwdep_dsp_image *dsp)
अणु
	काष्ठा usX2Ydev *priv = hw->निजी_data;
	काष्ठा usb_device* dev = priv->dev;
	पूर्णांक lret, err;
	अक्षर *buf;

	snd_prपूर्णांकdd( "dsp_load %s\n", dsp->name);

	buf = memdup_user(dsp->image, dsp->length);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	err = usb_set_पूर्णांकerface(dev, 0, 1);
	अगर (err)
		snd_prपूर्णांकk(KERN_ERR "usb_set_interface error \n");
	अन्यथा
		err = usb_bulk_msg(dev, usb_sndbulkpipe(dev, 2), buf, dsp->length, &lret, 6000);
	kमुक्त(buf);
	अगर (err)
		वापस err;
	अगर (dsp->index == 1) अणु
		msleep(250);				// give the device some समय
		err = usX2Y_AsyncSeq04_init(priv);
		अगर (err) अणु
			snd_prपूर्णांकk(KERN_ERR "usX2Y_AsyncSeq04_init error \n");
			वापस err;
		पूर्ण
		err = usX2Y_In04_init(priv);
		अगर (err) अणु
			snd_prपूर्णांकk(KERN_ERR "usX2Y_In04_init error \n");
			वापस err;
		पूर्ण
		err = usX2Y_create_alsa_devices(hw->card);
		अगर (err) अणु
			snd_prपूर्णांकk(KERN_ERR "usX2Y_create_alsa_devices error %i \n", err);
			snd_card_मुक्त(hw->card);
			वापस err;
		पूर्ण
		priv->chip_status |= USX2Y_STAT_CHIP_INIT; 
		snd_prपूर्णांकdd("%s: alsa all started\n", hw->name);
	पूर्ण
	वापस err;
पूर्ण


पूर्णांक usX2Y_hwdep_new(काष्ठा snd_card *card, काष्ठा usb_device* device)
अणु
	पूर्णांक err;
	काष्ठा snd_hwdep *hw;

	अगर ((err = snd_hwdep_new(card, SND_USX2Y_LOADER_ID, 0, &hw)) < 0)
		वापस err;

	hw->अगरace = SNDRV_HWDEP_IFACE_USX2Y;
	hw->निजी_data = usX2Y(card);
	hw->ops.dsp_status = snd_usX2Y_hwdep_dsp_status;
	hw->ops.dsp_load = snd_usX2Y_hwdep_dsp_load;
	hw->ops.mmap = snd_us428ctls_mmap;
	hw->ops.poll = snd_us428ctls_poll;
	hw->exclusive = 1;
	प्र_लिखो(hw->name, "/dev/bus/usb/%03d/%03d", device->bus->busnum, device->devnum);
	वापस 0;
पूर्ण

