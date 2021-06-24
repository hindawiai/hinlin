<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2002 by Paul Davis <pbd@op.net>
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <sound/core.h>
#समावेश <sound/snd_wavefront.h>
#समावेश <sound/initval.h>

/* Control bits क्रम the Load Control Register
 */

#घोषणा FX_LSB_TRANSFER 0x01    /* transfer after DSP LSB byte written */
#घोषणा FX_MSB_TRANSFER 0x02    /* transfer after DSP MSB byte written */
#घोषणा FX_AUTO_INCR    0x04    /* स्वतः-increment DSP address after transfer */

#घोषणा WAIT_IDLE	0xff

अटल पूर्णांक
wavefront_fx_idle (snd_wavefront_t *dev)

अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक x = 0x80;

	क्रम (i = 0; i < 1000; i++) अणु
		x = inb (dev->fx_status);
		अगर ((x & 0x80) == 0) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (x & 0x80) अणु
		snd_prपूर्णांकk ("FX device never idle.\n");
		वापस 0;
	पूर्ण

	वापस (1);
पूर्ण

अटल व्योम
wavefront_fx_mute (snd_wavefront_t *dev, पूर्णांक onoff)

अणु
	अगर (!wavefront_fx_idle(dev)) अणु
		वापस;
	पूर्ण

	outb (onoff ? 0x02 : 0x00, dev->fx_op);
पूर्ण

अटल पूर्णांक
wavefront_fx_स_रखो (snd_wavefront_t *dev,
		     पूर्णांक page,
		     पूर्णांक addr,
		     पूर्णांक cnt,
		     अचिन्हित लघु *data)
अणु
	अगर (page < 0 || page > 7) अणु
		snd_prपूर्णांकk ("FX memset: "
			"page must be >= 0 and <= 7\n");
		वापस -EINVAL;
	पूर्ण

	अगर (addr < 0 || addr > 0x7f) अणु
		snd_prपूर्णांकk ("FX memset: "
			"addr must be >= 0 and <= 7f\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cnt == 1) अणु

		outb (FX_LSB_TRANSFER, dev->fx_lcr);
		outb (page, dev->fx_dsp_page);
		outb (addr, dev->fx_dsp_addr);
		outb ((data[0] >> 8), dev->fx_dsp_msb);
		outb ((data[0] & 0xff), dev->fx_dsp_lsb);

		snd_prपूर्णांकk ("FX: addr %d:%x set to 0x%x\n",
			page, addr, data[0]);

	पूर्ण अन्यथा अणु
		पूर्णांक i;

		outb (FX_AUTO_INCR|FX_LSB_TRANSFER, dev->fx_lcr);
		outb (page, dev->fx_dsp_page);
		outb (addr, dev->fx_dsp_addr);

		क्रम (i = 0; i < cnt; i++) अणु
			outb ((data[i] >> 8), dev->fx_dsp_msb);
			outb ((data[i] & 0xff), dev->fx_dsp_lsb);
			अगर (!wavefront_fx_idle (dev)) अणु
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i != cnt) अणु
			snd_prपूर्णांकk ("FX memset "
				    "(0x%x, 0x%x, 0x%lx, %d) incomplete\n",
				    page, addr, (अचिन्हित दीर्घ) data, cnt);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
snd_wavefront_fx_detect (snd_wavefront_t *dev)

अणु
	/* This is a crude check, but its the best one I have क्रम now.
	   Certainly on the Maui and the Tropez, wavefront_fx_idle() will
	   report "never idle", which suggests that this test should
	   work OK.
	*/

	अगर (inb (dev->fx_status) & 0x80) अणु
		snd_prपूर्णांकk ("Hmm, probably a Maui or Tropez.\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
snd_wavefront_fx_खोलो (काष्ठा snd_hwdep *hw, काष्ठा file *file)

अणु
	अगर (!try_module_get(hw->card->module))
		वापस -EFAULT;
	file->निजी_data = hw;
	वापस 0;
पूर्ण

पूर्णांक 
snd_wavefront_fx_release (काष्ठा snd_hwdep *hw, काष्ठा file *file)

अणु
	module_put(hw->card->module);
	वापस 0;
पूर्ण

पूर्णांक
snd_wavefront_fx_ioctl (काष्ठा snd_hwdep *sdev, काष्ठा file *file,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)

अणु
	काष्ठा snd_card *card;
	snd_wavefront_card_t *acard;
	snd_wavefront_t *dev;
	wavefront_fx_info r;
	अचिन्हित लघु *page_data = शून्य;
	अचिन्हित लघु *pd;
	पूर्णांक err = 0;

	card = sdev->card;
	अगर (snd_BUG_ON(!card))
		वापस -ENODEV;
	अगर (snd_BUG_ON(!card->निजी_data))
		वापस -ENODEV;

	acard = card->निजी_data;
	dev = &acard->wavefront;

	अगर (copy_from_user (&r, (व्योम __user *)arg, माप (wavefront_fx_info)))
		वापस -EFAULT;

	चयन (r.request) अणु
	हाल WFFX_MUTE:
		wavefront_fx_mute (dev, r.data[0]);
		वापस -EIO;

	हाल WFFX_MEMSET:
		अगर (r.data[2] <= 0) अणु
			snd_prपूर्णांकk ("cannot write "
				"<= 0 bytes to FX\n");
			वापस -EIO;
		पूर्ण अन्यथा अगर (r.data[2] == 1) अणु
			pd = (अचिन्हित लघु *) &r.data[3];
		पूर्ण अन्यथा अणु
			अगर (r.data[2] > 256) अणु
				snd_prपूर्णांकk ("cannot write "
					    "> 512 bytes to FX\n");
				वापस -EIO;
			पूर्ण
			page_data = memdup_user((अचिन्हित अक्षर __user *)
						r.data[3],
						r.data[2] * माप(लघु));
			अगर (IS_ERR(page_data))
				वापस PTR_ERR(page_data);
			pd = page_data;
		पूर्ण

		err = wavefront_fx_स_रखो (dev,
			     r.data[0], /* page */
			     r.data[1], /* addr */
			     r.data[2], /* cnt */
			     pd);
		kमुक्त(page_data);
		अवरोध;

	शेष:
		snd_prपूर्णांकk ("FX: ioctl %d not yet supported\n",
			    r.request);
		वापस -ENOTTY;
	पूर्ण
	वापस err;
पूर्ण

/* YSS225 initialization.

   This code was developed using DOSEMU. The Turtle Beach SETUPSND
   utility was run with I/O tracing in DOSEMU enabled, and a reस्थिरruction
   of the port I/O करोne, using the Yamaha faxback करोcument as a guide
   to add more logic to the code. Its really pretty weird.

   This is the approach of just dumping the whole I/O
   sequence as a series of port/value pairs and a simple loop
   that outमाला_दो it.
*/

पूर्णांक
snd_wavefront_fx_start (snd_wavefront_t *dev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	स्थिर काष्ठा firmware *firmware = शून्य;

	अगर (dev->fx_initialized)
		वापस 0;

	err = request_firmware(&firmware, "yamaha/yss225_registers.bin",
			       dev->card->dev);
	अगर (err < 0) अणु
		err = -1;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i + 1 < firmware->size; i += 2) अणु
		अगर (firmware->data[i] >= 8 && firmware->data[i] < 16) अणु
			outb(firmware->data[i + 1],
			     dev->base + firmware->data[i]);
		पूर्ण अन्यथा अगर (firmware->data[i] == WAIT_IDLE) अणु
			अगर (!wavefront_fx_idle(dev)) अणु
				err = -1;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकk(KERN_ERR "invalid address"
				   " in register data\n");
			err = -1;
			जाओ out;
		पूर्ण
	पूर्ण

	dev->fx_initialized = 1;
	err = 0;

out:
	release_firmware(firmware);
	वापस err;
पूर्ण

MODULE_FIRMWARE("yamaha/yss225_registers.bin");
