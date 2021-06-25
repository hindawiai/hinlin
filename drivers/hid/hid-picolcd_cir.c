<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/***************************************************************************
 *   Copyright (C) 2010-2012 by Bruno Prथऊmont <bonbons@linux-vserver.org>  *
 *                                                                         *
 *   Based on Logitech G13 driver (v0.4)                                   *
 *     Copyright (C) 2009 by Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#समावेश <linux/hid.h>
#समावेश <linux/hid-debug.h>
#समावेश <linux/input.h>
#समावेश "hid-ids.h"

#समावेश <linux/fb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/backlight.h>
#समावेश <linux/lcd.h>

#समावेश <linux/leds.h>

#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>

#समावेश <linux/completion.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <media/rc-core.h>

#समावेश "hid-picolcd.h"


पूर्णांक picolcd_raw_cir(काष्ठा picolcd_data *data,
		काष्ठा hid_report *report, u8 *raw_data, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, w, sz;
	काष्ठा ir_raw_event rawir = अणुपूर्ण;

	/* ignore अगर rc_dev is शून्य or status is shunned */
	spin_lock_irqsave(&data->lock, flags);
	अगर (!data->rc_dev || (data->status & PICOLCD_CIR_SHUN)) अणु
		spin_unlock_irqrestore(&data->lock, flags);
		वापस 1;
	पूर्ण
	spin_unlock_irqrestore(&data->lock, flags);

	/* PicoLCD USB packets contain 16-bit पूर्णांकervals in network order,
	 * with value negated क्रम pulse. Intervals are in microseconds.
	 *
	 * Note: some userspace LIRC code क्रम PicoLCD says negated values
	 * क्रम space - is it a matter of IR chip? (pulse क्रम my TSOP2236)
	 *
	 * In addition, the first पूर्णांकerval seems to be around 15000 + base
	 * पूर्णांकerval क्रम non-first report of IR data - thus the quirk below
	 * to get RC_CODE to understand Sony and JVC remotes I have at hand
	 */
	sz = size > 0 ? min((पूर्णांक)raw_data[0], size-1) : 0;
	क्रम (i = 0; i+1 < sz; i += 2) अणु
		w = (raw_data[i] << 8) | (raw_data[i+1]);
		rawir.pulse = !!(w & 0x8000);
		rawir.duration = rawir.pulse ? (65536 - w) : w;
		/* Quirk!! - see above */
		अगर (i == 0 && rawir.duration > 15000)
			rawir.duration -= 15000;
		ir_raw_event_store(data->rc_dev, &rawir);
	पूर्ण
	ir_raw_event_handle(data->rc_dev);

	वापस 1;
पूर्ण

अटल पूर्णांक picolcd_cir_खोलो(काष्ठा rc_dev *dev)
अणु
	काष्ठा picolcd_data *data = dev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data->lock, flags);
	data->status &= ~PICOLCD_CIR_SHUN;
	spin_unlock_irqrestore(&data->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम picolcd_cir_बंद(काष्ठा rc_dev *dev)
अणु
	काष्ठा picolcd_data *data = dev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data->lock, flags);
	data->status |= PICOLCD_CIR_SHUN;
	spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

/* initialize CIR input device */
पूर्णांक picolcd_init_cir(काष्ठा picolcd_data *data, काष्ठा hid_report *report)
अणु
	काष्ठा rc_dev *rdev;
	पूर्णांक ret = 0;

	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rdev)
		वापस -ENOMEM;

	rdev->priv             = data;
	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->खोलो             = picolcd_cir_खोलो;
	rdev->बंद            = picolcd_cir_बंद;
	rdev->device_name      = data->hdev->name;
	rdev->input_phys       = data->hdev->phys;
	rdev->input_id.bustype = data->hdev->bus;
	rdev->input_id.venकरोr  = data->hdev->venकरोr;
	rdev->input_id.product = data->hdev->product;
	rdev->input_id.version = data->hdev->version;
	rdev->dev.parent       = &data->hdev->dev;
	rdev->driver_name      = PICOLCD_NAME;
	rdev->map_name         = RC_MAP_RC6_MCE;
	rdev->समयout          = MS_TO_US(100);
	rdev->rx_resolution    = 1;

	ret = rc_रेजिस्टर_device(rdev);
	अगर (ret)
		जाओ err;
	data->rc_dev = rdev;
	वापस 0;

err:
	rc_मुक्त_device(rdev);
	वापस ret;
पूर्ण

व्योम picolcd_निकास_cir(काष्ठा picolcd_data *data)
अणु
	काष्ठा rc_dev *rdev = data->rc_dev;

	data->rc_dev = शून्य;
	rc_unरेजिस्टर_device(rdev);
पूर्ण

