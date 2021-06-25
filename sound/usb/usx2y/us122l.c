<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007, 2008 Karsten Wiese <fzu@wemgehoertderstaat.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#घोषणा MODNAME "US122L"
#समावेश "usb_stream.c"
#समावेश "../usbaudio.h"
#समावेश "../midi.h"
#समावेश "us122l.h"

MODULE_AUTHOR("Karsten Wiese <fzu@wemgehoertderstaat.de>");
MODULE_DESCRIPTION("TASCAM "NAME_ALLCAPS" Version 0.5");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-max */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* Id क्रम this card */
							/* Enable this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for "NAME_ALLCAPS".");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for "NAME_ALLCAPS".");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable "NAME_ALLCAPS".");

/* driver_info flags */
#घोषणा US122L_FLAG_US144	BIT(0)

अटल पूर्णांक snd_us122l_card_used[SNDRV_CARDS];

अटल पूर्णांक us122l_create_usbmidi(काष्ठा snd_card *card)
अणु
	अटल स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info quirk_data = अणु
		.out_ep = 4,
		.in_ep = 3,
		.out_cables =	0x001,
		.in_cables =	0x001
	पूर्ण;
	अटल स्थिर काष्ठा snd_usb_audio_quirk quirk = अणु
		.venकरोr_name =	"US122L",
		.product_name =	NAME_ALLCAPS,
		.अगरnum = 	1,
		.type = QUIRK_MIDI_US122L,
		.data = &quirk_data
	पूर्ण;
	काष्ठा usb_device *dev = US122L(card)->dev;
	काष्ठा usb_पूर्णांकerface *अगरace = usb_अगरnum_to_अगर(dev, 1);

	वापस snd_usbmidi_create(card, अगरace,
				  &US122L(card)->midi_list, &quirk);
पूर्ण

अटल पूर्णांक us144_create_usbmidi(काष्ठा snd_card *card)
अणु
	अटल स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info quirk_data = अणु
		.out_ep = 4,
		.in_ep = 3,
		.out_cables =	0x001,
		.in_cables =	0x001
	पूर्ण;
	अटल स्थिर काष्ठा snd_usb_audio_quirk quirk = अणु
		.venकरोr_name =	"US144",
		.product_name =	NAME_ALLCAPS,
		.अगरnum = 	0,
		.type = QUIRK_MIDI_US122L,
		.data = &quirk_data
	पूर्ण;
	काष्ठा usb_device *dev = US122L(card)->dev;
	काष्ठा usb_पूर्णांकerface *अगरace = usb_अगरnum_to_अगर(dev, 0);

	वापस snd_usbmidi_create(card, अगरace,
				  &US122L(card)->midi_list, &quirk);
पूर्ण

अटल व्योम pt_info_set(काष्ठा usb_device *dev, u8 v)
अणु
	पूर्णांक ret;

	ret = usb_control_msg_send(dev, 0, 'I',
				   USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				   v, 0, शून्य, 0, 1000, GFP_NOIO);
	snd_prपूर्णांकdd(KERN_DEBUG "%i\n", ret);
पूर्ण

अटल व्योम usb_stream_hwdep_vm_खोलो(काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा us122l *us122l = area->vm_निजी_data;
	atomic_inc(&us122l->mmap_count);
	snd_prपूर्णांकdd(KERN_DEBUG "%i\n", atomic_पढ़ो(&us122l->mmap_count));
पूर्ण

अटल vm_fault_t usb_stream_hwdep_vm_fault(काष्ठा vm_fault *vmf)
अणु
	अचिन्हित दीर्घ offset;
	काष्ठा page *page;
	व्योम *vaddr;
	काष्ठा us122l *us122l = vmf->vma->vm_निजी_data;
	काष्ठा usb_stream *s;

	mutex_lock(&us122l->mutex);
	s = us122l->sk.s;
	अगर (!s)
		जाओ unlock;

	offset = vmf->pgoff << PAGE_SHIFT;
	अगर (offset < PAGE_ALIGN(s->पढ़ो_size))
		vaddr = (अक्षर *)s + offset;
	अन्यथा अणु
		offset -= PAGE_ALIGN(s->पढ़ो_size);
		अगर (offset >= PAGE_ALIGN(s->ग_लिखो_size))
			जाओ unlock;

		vaddr = us122l->sk.ग_लिखो_page + offset;
	पूर्ण
	page = virt_to_page(vaddr);

	get_page(page);
	mutex_unlock(&us122l->mutex);

	vmf->page = page;

	वापस 0;
unlock:
	mutex_unlock(&us122l->mutex);
	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल व्योम usb_stream_hwdep_vm_बंद(काष्ठा vm_area_काष्ठा *area)
अणु
	काष्ठा us122l *us122l = area->vm_निजी_data;
	atomic_dec(&us122l->mmap_count);
	snd_prपूर्णांकdd(KERN_DEBUG "%i\n", atomic_पढ़ो(&us122l->mmap_count));
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा usb_stream_hwdep_vm_ops = अणु
	.खोलो = usb_stream_hwdep_vm_खोलो,
	.fault = usb_stream_hwdep_vm_fault,
	.बंद = usb_stream_hwdep_vm_बंद,
पूर्ण;


अटल पूर्णांक usb_stream_hwdep_खोलो(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
	काष्ठा us122l	*us122l = hw->निजी_data;
	काष्ठा usb_पूर्णांकerface *अगरace;
	snd_prपूर्णांकdd(KERN_DEBUG "%p %p\n", hw, file);
	अगर (hw->used >= 2)
		वापस -EBUSY;

	अगर (!us122l->first)
		us122l->first = file;

	अगर (us122l->is_us144) अणु
		अगरace = usb_अगरnum_to_अगर(us122l->dev, 0);
		usb_स्वतःpm_get_पूर्णांकerface(अगरace);
	पूर्ण
	अगरace = usb_अगरnum_to_अगर(us122l->dev, 1);
	usb_स्वतःpm_get_पूर्णांकerface(अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक usb_stream_hwdep_release(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
	काष्ठा us122l	*us122l = hw->निजी_data;
	काष्ठा usb_पूर्णांकerface *अगरace;
	snd_prपूर्णांकdd(KERN_DEBUG "%p %p\n", hw, file);

	अगर (us122l->is_us144) अणु
		अगरace = usb_अगरnum_to_अगर(us122l->dev, 0);
		usb_स्वतःpm_put_पूर्णांकerface(अगरace);
	पूर्ण
	अगरace = usb_अगरnum_to_अगर(us122l->dev, 1);
	usb_स्वतःpm_put_पूर्णांकerface(अगरace);
	अगर (us122l->first == file)
		us122l->first = शून्य;
	mutex_lock(&us122l->mutex);
	अगर (us122l->master == file)
		us122l->master = us122l->slave;

	us122l->slave = शून्य;
	mutex_unlock(&us122l->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक usb_stream_hwdep_mmap(काष्ठा snd_hwdep *hw,
				 काष्ठा file *filp, काष्ठा vm_area_काष्ठा *area)
अणु
	अचिन्हित दीर्घ	size = area->vm_end - area->vm_start;
	काष्ठा us122l	*us122l = hw->निजी_data;
	अचिन्हित दीर्घ offset;
	काष्ठा usb_stream *s;
	पूर्णांक err = 0;
	bool पढ़ो;

	offset = area->vm_pgoff << PAGE_SHIFT;
	mutex_lock(&us122l->mutex);
	s = us122l->sk.s;
	पढ़ो = offset < s->पढ़ो_size;
	अगर (पढ़ो && area->vm_flags & VM_WRITE) अणु
		err = -EPERM;
		जाओ out;
	पूर्ण
	snd_prपूर्णांकdd(KERN_DEBUG "%lu %u\n", size,
		    पढ़ो ? s->पढ़ो_size : s->ग_लिखो_size);
	/* अगर userspace tries to mmap beyond end of our buffer, fail */
	अगर (size > PAGE_ALIGN(पढ़ो ? s->पढ़ो_size : s->ग_लिखो_size)) अणु
		snd_prपूर्णांकk(KERN_WARNING "%lu > %u\n", size,
			   पढ़ो ? s->पढ़ो_size : s->ग_लिखो_size);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	area->vm_ops = &usb_stream_hwdep_vm_ops;
	area->vm_flags |= VM_DONTDUMP;
	अगर (!पढ़ो)
		area->vm_flags |= VM_DONTEXPAND;
	area->vm_निजी_data = us122l;
	atomic_inc(&us122l->mmap_count);
out:
	mutex_unlock(&us122l->mutex);
	वापस err;
पूर्ण

अटल __poll_t usb_stream_hwdep_poll(काष्ठा snd_hwdep *hw,
					  काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा us122l	*us122l = hw->निजी_data;
	अचिन्हित	*polled;
	__poll_t	mask;

	poll_रुको(file, &us122l->sk.sleep, रुको);

	mask = EPOLLIN | EPOLLOUT | EPOLLWRNORM | EPOLLERR;
	अगर (mutex_trylock(&us122l->mutex)) अणु
		काष्ठा usb_stream *s = us122l->sk.s;
		अगर (s && s->state == usb_stream_पढ़ोy) अणु
			अगर (us122l->first == file)
				polled = &s->periods_polled;
			अन्यथा
				polled = &us122l->second_periods_polled;
			अगर (*polled != s->periods_करोne) अणु
				*polled = s->periods_करोne;
				mask = EPOLLIN | EPOLLOUT | EPOLLWRNORM;
			पूर्ण अन्यथा
				mask = 0;
		पूर्ण
		mutex_unlock(&us122l->mutex);
	पूर्ण
	वापस mask;
पूर्ण

अटल व्योम us122l_stop(काष्ठा us122l *us122l)
अणु
	काष्ठा list_head *p;
	list_क्रम_each(p, &us122l->midi_list)
		snd_usbmidi_input_stop(p);

	usb_stream_stop(&us122l->sk);
	usb_stream_मुक्त(&us122l->sk);
पूर्ण

अटल पूर्णांक us122l_set_sample_rate(काष्ठा usb_device *dev, पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक ep = 0x81;
	अचिन्हित अक्षर data[3];
	पूर्णांक err;

	data[0] = rate;
	data[1] = rate >> 8;
	data[2] = rate >> 16;
	err = usb_control_msg_send(dev, 0, UAC_SET_CUR,
				   USB_TYPE_CLASS | USB_RECIP_ENDPOINT | USB_सूची_OUT,
				   UAC_EP_CS_ATTR_SAMPLE_RATE << 8, ep, data, 3,
				   1000, GFP_NOIO);
	अगर (err)
		snd_prपूर्णांकk(KERN_ERR "%d: cannot set freq %d to ep 0x%x\n",
			   dev->devnum, rate, ep);
	वापस err;
पूर्ण

अटल bool us122l_start(काष्ठा us122l *us122l,
			 अचिन्हित rate, अचिन्हित period_frames)
अणु
	काष्ठा list_head *p;
	पूर्णांक err;
	अचिन्हित use_packsize = 0;
	bool success = false;

	अगर (us122l->dev->speed == USB_SPEED_HIGH) अणु
		/* The us-122l's descriptor शेषs to iso max_packsize 78,
		   which isn't needed क्रम samplerates <= 48000.
		   Lets save some memory:
		*/
		चयन (rate) अणु
		हाल 44100:
			use_packsize = 36;
			अवरोध;
		हाल 48000:
			use_packsize = 42;
			अवरोध;
		हाल 88200:
			use_packsize = 72;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!usb_stream_new(&us122l->sk, us122l->dev, 1, 2,
			    rate, use_packsize, period_frames, 6))
		जाओ out;

	err = us122l_set_sample_rate(us122l->dev, rate);
	अगर (err < 0) अणु
		us122l_stop(us122l);
		snd_prपूर्णांकk(KERN_ERR "us122l_set_sample_rate error \n");
		जाओ out;
	पूर्ण
	err = usb_stream_start(&us122l->sk);
	अगर (err < 0) अणु
		us122l_stop(us122l);
		snd_prपूर्णांकk(KERN_ERR "us122l_start error %i \n", err);
		जाओ out;
	पूर्ण
	list_क्रम_each(p, &us122l->midi_list)
		snd_usbmidi_input_start(p);
	success = true;
out:
	वापस success;
पूर्ण

अटल पूर्णांक usb_stream_hwdep_ioctl(काष्ठा snd_hwdep *hw, काष्ठा file *file,
				  अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usb_stream_config cfg;
	काष्ठा us122l *us122l = hw->निजी_data;
	काष्ठा usb_stream *s;
	अचिन्हित min_period_frames;
	पूर्णांक err = 0;
	bool high_speed;

	अगर (cmd != SNDRV_USB_STREAM_IOCTL_SET_PARAMS)
		वापस -ENOTTY;

	अगर (copy_from_user(&cfg, (व्योम __user *)arg, माप(cfg)))
		वापस -EFAULT;

	अगर (cfg.version != USB_STREAM_INTERFACE_VERSION)
		वापस -ENXIO;

	high_speed = us122l->dev->speed == USB_SPEED_HIGH;
	अगर ((cfg.sample_rate != 44100 && cfg.sample_rate != 48000  &&
	     (!high_speed ||
	      (cfg.sample_rate != 88200 && cfg.sample_rate != 96000))) ||
	    cfg.frame_size != 6 ||
	    cfg.period_frames > 0x3000)
		वापस -EINVAL;

	चयन (cfg.sample_rate) अणु
	हाल 44100:
		min_period_frames = 48;
		अवरोध;
	हाल 48000:
		min_period_frames = 52;
		अवरोध;
	शेष:
		min_period_frames = 104;
		अवरोध;
	पूर्ण
	अगर (!high_speed)
		min_period_frames <<= 1;
	अगर (cfg.period_frames < min_period_frames)
		वापस -EINVAL;

	snd_घातer_रुको(hw->card, SNDRV_CTL_POWER_D0);

	mutex_lock(&us122l->mutex);
	s = us122l->sk.s;
	अगर (!us122l->master)
		us122l->master = file;
	अन्यथा अगर (us122l->master != file) अणु
		अगर (!s || स_भेद(&cfg, &s->cfg, माप(cfg))) अणु
			err = -EIO;
			जाओ unlock;
		पूर्ण
		us122l->slave = file;
	पूर्ण
	अगर (!s || स_भेद(&cfg, &s->cfg, माप(cfg)) ||
	    s->state == usb_stream_xrun) अणु
		us122l_stop(us122l);
		अगर (!us122l_start(us122l, cfg.sample_rate, cfg.period_frames))
			err = -EIO;
		अन्यथा
			err = 1;
	पूर्ण
unlock:
	mutex_unlock(&us122l->mutex);
	wake_up_all(&us122l->sk.sleep);
	वापस err;
पूर्ण

#घोषणा SND_USB_STREAM_ID "USB STREAM"
अटल पूर्णांक usb_stream_hwdep_new(काष्ठा snd_card *card)
अणु
	पूर्णांक err;
	काष्ठा snd_hwdep *hw;
	काष्ठा usb_device *dev = US122L(card)->dev;

	err = snd_hwdep_new(card, SND_USB_STREAM_ID, 0, &hw);
	अगर (err < 0)
		वापस err;

	hw->अगरace = SNDRV_HWDEP_IFACE_USB_STREAM;
	hw->निजी_data = US122L(card);
	hw->ops.खोलो = usb_stream_hwdep_खोलो;
	hw->ops.release = usb_stream_hwdep_release;
	hw->ops.ioctl = usb_stream_hwdep_ioctl;
	hw->ops.ioctl_compat = usb_stream_hwdep_ioctl;
	hw->ops.mmap = usb_stream_hwdep_mmap;
	hw->ops.poll = usb_stream_hwdep_poll;

	प्र_लिखो(hw->name, "/dev/bus/usb/%03d/%03d/hwdeppcm",
		dev->bus->busnum, dev->devnum);
	वापस 0;
पूर्ण


अटल bool us122l_create_card(काष्ठा snd_card *card)
अणु
	पूर्णांक err;
	काष्ठा us122l *us122l = US122L(card);

	अगर (us122l->is_us144) अणु
		err = usb_set_पूर्णांकerface(us122l->dev, 0, 1);
		अगर (err) अणु
			snd_prपूर्णांकk(KERN_ERR "usb_set_interface error \n");
			वापस false;
		पूर्ण
	पूर्ण
	err = usb_set_पूर्णांकerface(us122l->dev, 1, 1);
	अगर (err) अणु
		snd_prपूर्णांकk(KERN_ERR "usb_set_interface error \n");
		वापस false;
	पूर्ण

	pt_info_set(us122l->dev, 0x11);
	pt_info_set(us122l->dev, 0x10);

	अगर (!us122l_start(us122l, 44100, 256))
		वापस false;

	अगर (us122l->is_us144)
		err = us144_create_usbmidi(card);
	अन्यथा
		err = us122l_create_usbmidi(card);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "us122l_create_usbmidi error %i \n", err);
		जाओ stop;
	पूर्ण
	err = usb_stream_hwdep_new(card);
	अगर (err < 0) अणु
/* release the midi resources */
		काष्ठा list_head *p;
		list_क्रम_each(p, &us122l->midi_list)
			snd_usbmidi_disconnect(p);

		जाओ stop;
	पूर्ण
	वापस true;

stop:
	us122l_stop(us122l);
	वापस false;
पूर्ण

अटल व्योम snd_us122l_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा us122l	*us122l = US122L(card);
	पूर्णांक		index = us122l->card_index;
	अगर (index >= 0  &&  index < SNDRV_CARDS)
		snd_us122l_card_used[index] = 0;
पूर्ण

अटल पूर्णांक usx2y_create_card(काष्ठा usb_device *device,
			     काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     काष्ठा snd_card **cardp,
			     अचिन्हित दीर्घ flags)
अणु
	पूर्णांक		dev;
	काष्ठा snd_card *card;
	पूर्णांक err;

	क्रम (dev = 0; dev < SNDRV_CARDS; ++dev)
		अगर (enable[dev] && !snd_us122l_card_used[dev])
			अवरोध;
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	err = snd_card_new(&पूर्णांकf->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा us122l), &card);
	अगर (err < 0)
		वापस err;
	snd_us122l_card_used[US122L(card)->card_index = dev] = 1;
	card->निजी_मुक्त = snd_us122l_मुक्त;
	US122L(card)->dev = device;
	mutex_init(&US122L(card)->mutex);
	init_रुकोqueue_head(&US122L(card)->sk.sleep);
	US122L(card)->is_us144 = flags & US122L_FLAG_US144;
	INIT_LIST_HEAD(&US122L(card)->midi_list);
	म_नकल(card->driver, "USB "NAME_ALLCAPS"");
	प्र_लिखो(card->लघुname, "TASCAM "NAME_ALLCAPS"");
	प्र_लिखो(card->दीर्घname, "%s (%x:%x if %d at %03d/%03d)",
		card->लघुname,
		le16_to_cpu(device->descriptor.idVenकरोr),
		le16_to_cpu(device->descriptor.idProduct),
		0,
		US122L(card)->dev->bus->busnum,
		US122L(card)->dev->devnum
		);
	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक us122l_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *device_id,
			    काष्ठा snd_card **cardp)
अणु
	काष्ठा usb_device *device = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = usx2y_create_card(device, पूर्णांकf, &card, device_id->driver_info);
	अगर (err < 0)
		वापस err;

	अगर (!us122l_create_card(card)) अणु
		snd_card_मुक्त(card);
		वापस -EINVAL;
	पूर्ण

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	usb_get_पूर्णांकf(usb_अगरnum_to_अगर(device, 0));
	usb_get_dev(device);
	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_us122l_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *device = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (id->driver_info & US122L_FLAG_US144 &&
			device->speed == USB_SPEED_HIGH) अणु
		snd_prपूर्णांकk(KERN_ERR "disable ehci-hcd to run US-144 \n");
		वापस -ENODEV;
	पूर्ण

	snd_prपूर्णांकdd(KERN_DEBUG"%p:%i\n",
		    पूर्णांकf, पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);
	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 1)
		वापस 0;

	err = us122l_usb_probe(usb_get_पूर्णांकf(पूर्णांकf), id, &card);
	अगर (err < 0) अणु
		usb_put_पूर्णांकf(पूर्णांकf);
		वापस err;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, card);
	वापस 0;
पूर्ण

अटल व्योम snd_us122l_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा snd_card *card;
	काष्ठा us122l *us122l;
	काष्ठा list_head *p;

	card = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!card)
		वापस;

	snd_card_disconnect(card);

	us122l = US122L(card);
	mutex_lock(&us122l->mutex);
	us122l_stop(us122l);
	mutex_unlock(&us122l->mutex);

/* release the midi resources */
	list_क्रम_each(p, &us122l->midi_list) अणु
		snd_usbmidi_disconnect(p);
	पूर्ण

	usb_put_पूर्णांकf(usb_अगरnum_to_अगर(us122l->dev, 0));
	usb_put_पूर्णांकf(usb_अगरnum_to_अगर(us122l->dev, 1));
	usb_put_dev(us122l->dev);

	जबतक (atomic_पढ़ो(&us122l->mmap_count))
		msleep(500);

	snd_card_मुक्त(card);
पूर्ण

अटल पूर्णांक snd_us122l_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा snd_card *card;
	काष्ठा us122l *us122l;
	काष्ठा list_head *p;

	card = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!card)
		वापस 0;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	us122l = US122L(card);
	अगर (!us122l)
		वापस 0;

	list_क्रम_each(p, &us122l->midi_list)
		snd_usbmidi_input_stop(p);

	mutex_lock(&us122l->mutex);
	usb_stream_stop(&us122l->sk);
	mutex_unlock(&us122l->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_us122l_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा snd_card *card;
	काष्ठा us122l *us122l;
	काष्ठा list_head *p;
	पूर्णांक err;

	card = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!card)
		वापस 0;

	us122l = US122L(card);
	अगर (!us122l)
		वापस 0;

	mutex_lock(&us122l->mutex);
	/* needed, करोesn't restart without: */
	अगर (us122l->is_us144) अणु
		err = usb_set_पूर्णांकerface(us122l->dev, 0, 1);
		अगर (err) अणु
			snd_prपूर्णांकk(KERN_ERR "usb_set_interface error \n");
			जाओ unlock;
		पूर्ण
	पूर्ण
	err = usb_set_पूर्णांकerface(us122l->dev, 1, 1);
	अगर (err) अणु
		snd_prपूर्णांकk(KERN_ERR "usb_set_interface error \n");
		जाओ unlock;
	पूर्ण

	pt_info_set(us122l->dev, 0x11);
	pt_info_set(us122l->dev, 0x10);

	err = us122l_set_sample_rate(us122l->dev,
				     us122l->sk.s->cfg.sample_rate);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "us122l_set_sample_rate error \n");
		जाओ unlock;
	पूर्ण
	err = usb_stream_start(&us122l->sk);
	अगर (err)
		जाओ unlock;

	list_क्रम_each(p, &us122l->midi_list)
		snd_usbmidi_input_start(p);
unlock:
	mutex_unlock(&us122l->mutex);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा usb_device_id snd_us122l_usb_id_table[] = अणु
	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	0x0644,
		.idProduct =	USB_ID_US122L
	पूर्ण,
	अणु	/* US-144 only works at USB1.1! Disable module ehci-hcd. */
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	0x0644,
		.idProduct =	USB_ID_US144,
		.driver_info =	US122L_FLAG_US144
	पूर्ण,
	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	0x0644,
		.idProduct =	USB_ID_US122MKII
	पूर्ण,
	अणु
		.match_flags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr =	0x0644,
		.idProduct =	USB_ID_US144MKII,
		.driver_info =	US122L_FLAG_US144
	पूर्ण,
	अणु /* terminator */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, snd_us122l_usb_id_table);
अटल काष्ठा usb_driver snd_us122l_usb_driver = अणु
	.name =		"snd-usb-us122l",
	.probe =	snd_us122l_probe,
	.disconnect =	snd_us122l_disconnect,
	.suspend =	snd_us122l_suspend,
	.resume =	snd_us122l_resume,
	.reset_resume =	snd_us122l_resume,
	.id_table =	snd_us122l_usb_id_table,
	.supports_स्वतःsuspend = 1
पूर्ण;

module_usb_driver(snd_us122l_usb_driver);
