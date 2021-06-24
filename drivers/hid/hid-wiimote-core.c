<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HID driver क्रम Nपूर्णांकenकरो Wii / Wii U peripherals
 * Copyright (c) 2011-2013 David Herrmann <dh.herrmann@gmail.com>
 */

/*
 */

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश "hid-ids.h"
#समावेश "hid-wiimote.h"

/* output queue handling */

अटल पूर्णांक wiimote_hid_send(काष्ठा hid_device *hdev, __u8 *buffer,
			    माप_प्रकार count)
अणु
	__u8 *buf;
	पूर्णांक ret;

	अगर (!hdev->ll_driver->output_report)
		वापस -ENODEV;

	buf = kmemdup(buffer, count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_output_report(hdev, buf, count);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम wiimote_queue_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wiimote_queue *queue = container_of(work, काष्ठा wiimote_queue,
						   worker);
	काष्ठा wiimote_data *wdata = container_of(queue, काष्ठा wiimote_data,
						  queue);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&wdata->queue.lock, flags);

	जबतक (wdata->queue.head != wdata->queue.tail) अणु
		spin_unlock_irqrestore(&wdata->queue.lock, flags);
		ret = wiimote_hid_send(wdata->hdev,
				 wdata->queue.outq[wdata->queue.tail].data,
				 wdata->queue.outq[wdata->queue.tail].size);
		अगर (ret < 0) अणु
			spin_lock_irqsave(&wdata->state.lock, flags);
			wiimote_cmd_पात(wdata);
			spin_unlock_irqrestore(&wdata->state.lock, flags);
		पूर्ण
		spin_lock_irqsave(&wdata->queue.lock, flags);

		wdata->queue.tail = (wdata->queue.tail + 1) % WIIMOTE_बफ_मानE;
	पूर्ण

	spin_unlock_irqrestore(&wdata->queue.lock, flags);
पूर्ण

अटल व्योम wiimote_queue(काष्ठा wiimote_data *wdata, स्थिर __u8 *buffer,
								माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;
	__u8 newhead;

	अगर (count > HID_MAX_BUFFER_SIZE) अणु
		hid_warn(wdata->hdev, "Sending too large output report\n");

		spin_lock_irqsave(&wdata->queue.lock, flags);
		जाओ out_error;
	पूर्ण

	/*
	 * Copy new request पूर्णांकo our output queue and check whether the
	 * queue is full. If it is full, discard this request.
	 * If it is empty we need to start a new worker that will
	 * send out the buffer to the hid device.
	 * If the queue is not empty, then there must be a worker
	 * that is currently sending out our buffer and this worker
	 * will reschedule itself until the queue is empty.
	 */

	spin_lock_irqsave(&wdata->queue.lock, flags);

	स_नकल(wdata->queue.outq[wdata->queue.head].data, buffer, count);
	wdata->queue.outq[wdata->queue.head].size = count;
	newhead = (wdata->queue.head + 1) % WIIMOTE_बफ_मानE;

	अगर (wdata->queue.head == wdata->queue.tail) अणु
		wdata->queue.head = newhead;
		schedule_work(&wdata->queue.worker);
	पूर्ण अन्यथा अगर (newhead != wdata->queue.tail) अणु
		wdata->queue.head = newhead;
	पूर्ण अन्यथा अणु
		hid_warn(wdata->hdev, "Output queue is full");
		जाओ out_error;
	पूर्ण

	जाओ out_unlock;

out_error:
	wiimote_cmd_पात(wdata);
out_unlock:
	spin_unlock_irqrestore(&wdata->queue.lock, flags);
पूर्ण

/*
 * This sets the rumble bit on the given output report अगर rumble is
 * currently enabled.
 * \cmd1 must poपूर्णांक to the second byte in the output report => &cmd[1]
 * This must be called on nearly every output report beक्रमe passing it
 * पूर्णांकo the output queue!
 */
अटल अंतरभूत व्योम wiiproto_keep_rumble(काष्ठा wiimote_data *wdata, __u8 *cmd1)
अणु
	अगर (wdata->state.flags & WIIPROTO_FLAG_RUMBLE)
		*cmd1 |= 0x01;
पूर्ण

व्योम wiiproto_req_rumble(काष्ठा wiimote_data *wdata, __u8 rumble)
अणु
	__u8 cmd[2];

	rumble = !!rumble;
	अगर (rumble == !!(wdata->state.flags & WIIPROTO_FLAG_RUMBLE))
		वापस;

	अगर (rumble)
		wdata->state.flags |= WIIPROTO_FLAG_RUMBLE;
	अन्यथा
		wdata->state.flags &= ~WIIPROTO_FLAG_RUMBLE;

	cmd[0] = WIIPROTO_REQ_RUMBLE;
	cmd[1] = 0;

	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, माप(cmd));
पूर्ण

व्योम wiiproto_req_leds(काष्ठा wiimote_data *wdata, पूर्णांक leds)
अणु
	__u8 cmd[2];

	leds &= WIIPROTO_FLAGS_LEDS;
	अगर ((wdata->state.flags & WIIPROTO_FLAGS_LEDS) == leds)
		वापस;
	wdata->state.flags = (wdata->state.flags & ~WIIPROTO_FLAGS_LEDS) | leds;

	cmd[0] = WIIPROTO_REQ_LED;
	cmd[1] = 0;

	अगर (leds & WIIPROTO_FLAG_LED1)
		cmd[1] |= 0x10;
	अगर (leds & WIIPROTO_FLAG_LED2)
		cmd[1] |= 0x20;
	अगर (leds & WIIPROTO_FLAG_LED3)
		cmd[1] |= 0x40;
	अगर (leds & WIIPROTO_FLAG_LED4)
		cmd[1] |= 0x80;

	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, माप(cmd));
पूर्ण

/*
 * Check what peripherals of the wiimote are currently
 * active and select a proper DRM that supports all of
 * the requested data inमाला_दो.
 *
 * Not all combinations are actually supported. The following
 * combinations work only with limitations:
 *  - IR cam in extended or full mode disables any data transmission
 *    of extension controllers. There is no DRM mode that supports
 *    extension bytes plus extended/full IR.
 *  - IR cam with accelerometer and extension *_EXT8 is not supported.
 *    However, all extensions that need *_EXT8 are devices that करोn't
 *    support IR cameras. Hence, this shouldn't happen under normal
 *    operation.
 *  - *_EXT16 is only supported in combination with buttons and
 *    accelerometer. No IR or similar can be active simultaneously. As
 *    above, all modules that require it are mutually exclusive with
 *    IR/etc. so this करोesn't matter.
 */
अटल __u8 select_drm(काष्ठा wiimote_data *wdata)
अणु
	__u8 ir = wdata->state.flags & WIIPROTO_FLAGS_IR;
	bool ext;

	ext = (wdata->state.flags & WIIPROTO_FLAG_EXT_USED) ||
	      (wdata->state.flags & WIIPROTO_FLAG_MP_USED);

	/* some 3rd-party balance-boards are hard-coded to KEE, *sigh* */
	अगर (wdata->state.devtype == WIIMOTE_DEV_BALANCE_BOARD) अणु
		अगर (ext)
			वापस WIIPROTO_REQ_DRM_KEE;
		अन्यथा
			वापस WIIPROTO_REQ_DRM_K;
	पूर्ण

	अगर (ir == WIIPROTO_FLAG_IR_BASIC) अणु
		अगर (wdata->state.flags & WIIPROTO_FLAG_ACCEL) अणु
			/* GEN10 and ealier devices bind IR क्रमmats to DRMs.
			 * Hence, we cannot use DRM_KAI here as it might be
			 * bound to IR_EXT. Use DRM_KAIE unconditionally so we
			 * work with all devices and our parsers can use the
			 * fixed क्रमmats, too. */
			वापस WIIPROTO_REQ_DRM_KAIE;
		पूर्ण अन्यथा अणु
			वापस WIIPROTO_REQ_DRM_KIE;
		पूर्ण
	पूर्ण अन्यथा अगर (ir == WIIPROTO_FLAG_IR_EXT) अणु
		वापस WIIPROTO_REQ_DRM_KAI;
	पूर्ण अन्यथा अगर (ir == WIIPROTO_FLAG_IR_FULL) अणु
		वापस WIIPROTO_REQ_DRM_SKAI1;
	पूर्ण अन्यथा अणु
		अगर (wdata->state.flags & WIIPROTO_FLAG_ACCEL) अणु
			अगर (ext)
				वापस WIIPROTO_REQ_DRM_KAE;
			अन्यथा
				वापस WIIPROTO_REQ_DRM_KA;
		पूर्ण अन्यथा अणु
			अगर (ext)
				वापस WIIPROTO_REQ_DRM_KEE;
			अन्यथा
				वापस WIIPROTO_REQ_DRM_K;
		पूर्ण
	पूर्ण
पूर्ण

व्योम wiiproto_req_drm(काष्ठा wiimote_data *wdata, __u8 drm)
अणु
	__u8 cmd[3];

	अगर (wdata->state.flags & WIIPROTO_FLAG_DRM_LOCKED)
		drm = wdata->state.drm;
	अन्यथा अगर (drm == WIIPROTO_REQ_शून्य)
		drm = select_drm(wdata);

	cmd[0] = WIIPROTO_REQ_DRM;
	cmd[1] = 0;
	cmd[2] = drm;

	wdata->state.drm = drm;
	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, माप(cmd));
पूर्ण

व्योम wiiproto_req_status(काष्ठा wiimote_data *wdata)
अणु
	__u8 cmd[2];

	cmd[0] = WIIPROTO_REQ_SREQ;
	cmd[1] = 0;

	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, माप(cmd));
पूर्ण

व्योम wiiproto_req_accel(काष्ठा wiimote_data *wdata, __u8 accel)
अणु
	accel = !!accel;
	अगर (accel == !!(wdata->state.flags & WIIPROTO_FLAG_ACCEL))
		वापस;

	अगर (accel)
		wdata->state.flags |= WIIPROTO_FLAG_ACCEL;
	अन्यथा
		wdata->state.flags &= ~WIIPROTO_FLAG_ACCEL;

	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
पूर्ण

व्योम wiiproto_req_ir1(काष्ठा wiimote_data *wdata, __u8 flags)
अणु
	__u8 cmd[2];

	cmd[0] = WIIPROTO_REQ_IR1;
	cmd[1] = flags;

	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, माप(cmd));
पूर्ण

व्योम wiiproto_req_ir2(काष्ठा wiimote_data *wdata, __u8 flags)
अणु
	__u8 cmd[2];

	cmd[0] = WIIPROTO_REQ_IR2;
	cmd[1] = flags;

	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, माप(cmd));
पूर्ण

#घोषणा wiiproto_req_wreg(wdata, os, buf, sz) \
			wiiproto_req_wmem((wdata), false, (os), (buf), (sz))

#घोषणा wiiproto_req_weeprom(wdata, os, buf, sz) \
			wiiproto_req_wmem((wdata), true, (os), (buf), (sz))

अटल व्योम wiiproto_req_wmem(काष्ठा wiimote_data *wdata, bool eeprom,
				__u32 offset, स्थिर __u8 *buf, __u8 size)
अणु
	__u8 cmd[22];

	अगर (size > 16 || size == 0) अणु
		hid_warn(wdata->hdev, "Invalid length %d wmem request\n", size);
		वापस;
	पूर्ण

	स_रखो(cmd, 0, माप(cmd));
	cmd[0] = WIIPROTO_REQ_WMEM;
	cmd[2] = (offset >> 16) & 0xff;
	cmd[3] = (offset >> 8) & 0xff;
	cmd[4] = offset & 0xff;
	cmd[5] = size;
	स_नकल(&cmd[6], buf, size);

	अगर (!eeprom)
		cmd[1] |= 0x04;

	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, माप(cmd));
पूर्ण

व्योम wiiproto_req_rmem(काष्ठा wiimote_data *wdata, bool eeprom, __u32 offset,
								__u16 size)
अणु
	__u8 cmd[7];

	अगर (size == 0) अणु
		hid_warn(wdata->hdev, "Invalid length %d rmem request\n", size);
		वापस;
	पूर्ण

	cmd[0] = WIIPROTO_REQ_RMEM;
	cmd[1] = 0;
	cmd[2] = (offset >> 16) & 0xff;
	cmd[3] = (offset >> 8) & 0xff;
	cmd[4] = offset & 0xff;
	cmd[5] = (size >> 8) & 0xff;
	cmd[6] = size & 0xff;

	अगर (!eeprom)
		cmd[1] |= 0x04;

	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, माप(cmd));
पूर्ण

/* requries the cmd-mutex to be held */
पूर्णांक wiimote_cmd_ग_लिखो(काष्ठा wiimote_data *wdata, __u32 offset,
						स्थिर __u8 *wmem, __u8 size)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiimote_cmd_set(wdata, WIIPROTO_REQ_WMEM, 0);
	wiiproto_req_wreg(wdata, offset, wmem, size);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	ret = wiimote_cmd_रुको(wdata);
	अगर (!ret && wdata->state.cmd_err)
		ret = -EIO;

	वापस ret;
पूर्ण

/* requries the cmd-mutex to be held */
sमाप_प्रकार wiimote_cmd_पढ़ो(काष्ठा wiimote_data *wdata, __u32 offset, __u8 *rmem,
								__u8 size)
अणु
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार ret;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.cmd_पढ़ो_size = size;
	wdata->state.cmd_पढ़ो_buf = rmem;
	wiimote_cmd_set(wdata, WIIPROTO_REQ_RMEM, offset & 0xffff);
	wiiproto_req_rreg(wdata, offset, size);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	ret = wiimote_cmd_रुको(wdata);

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.cmd_पढ़ो_buf = शून्य;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	अगर (!ret) अणु
		अगर (wdata->state.cmd_पढ़ो_size == 0)
			ret = -EIO;
		अन्यथा
			ret = wdata->state.cmd_पढ़ो_size;
	पूर्ण

	वापस ret;
पूर्ण

/* requires the cmd-mutex to be held */
अटल पूर्णांक wiimote_cmd_init_ext(काष्ठा wiimote_data *wdata)
अणु
	__u8 wmem;
	पूर्णांक ret;

	/* initialize extension */
	wmem = 0x55;
	ret = wiimote_cmd_ग_लिखो(wdata, 0xa400f0, &wmem, माप(wmem));
	अगर (ret)
		वापस ret;

	/* disable शेष encryption */
	wmem = 0x0;
	ret = wiimote_cmd_ग_लिखो(wdata, 0xa400fb, &wmem, माप(wmem));
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* requires the cmd-mutex to be held */
अटल __u8 wiimote_cmd_पढ़ो_ext(काष्ठा wiimote_data *wdata, __u8 *rmem)
अणु
	पूर्णांक ret;

	/* पढ़ो extension ID */
	ret = wiimote_cmd_पढ़ो(wdata, 0xa400fa, rmem, 6);
	अगर (ret != 6)
		वापस WIIMOTE_EXT_NONE;

	hid_dbg(wdata->hdev, "extension ID: %6phC\n", rmem);

	अगर (rmem[0] == 0xff && rmem[1] == 0xff && rmem[2] == 0xff &&
	    rmem[3] == 0xff && rmem[4] == 0xff && rmem[5] == 0xff)
		वापस WIIMOTE_EXT_NONE;

	अगर (rmem[4] == 0x00 && rmem[5] == 0x00)
		वापस WIIMOTE_EXT_NUNCHUK;
	अगर (rmem[4] == 0x01 && rmem[5] == 0x01)
		वापस WIIMOTE_EXT_CLASSIC_CONTROLLER;
	अगर (rmem[4] == 0x04 && rmem[5] == 0x02)
		वापस WIIMOTE_EXT_BALANCE_BOARD;
	अगर (rmem[4] == 0x01 && rmem[5] == 0x20)
		वापस WIIMOTE_EXT_PRO_CONTROLLER;
	अगर (rmem[0] == 0x01 && rmem[1] == 0x00 &&
	    rmem[4] == 0x01 && rmem[5] == 0x03)
		वापस WIIMOTE_EXT_DRUMS;
	अगर (rmem[0] == 0x00 && rmem[1] == 0x00 &&
	    rmem[4] == 0x01 && rmem[5] == 0x03)
		वापस WIIMOTE_EXT_GUITAR;

	वापस WIIMOTE_EXT_UNKNOWN;
पूर्ण

/* requires the cmd-mutex to be held */
अटल पूर्णांक wiimote_cmd_init_mp(काष्ठा wiimote_data *wdata)
अणु
	__u8 wmem;
	पूर्णांक ret;

	/* initialize MP */
	wmem = 0x55;
	ret = wiimote_cmd_ग_लिखो(wdata, 0xa600f0, &wmem, माप(wmem));
	अगर (ret)
		वापस ret;

	/* disable शेष encryption */
	wmem = 0x0;
	ret = wiimote_cmd_ग_लिखो(wdata, 0xa600fb, &wmem, माप(wmem));
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* requires the cmd-mutex to be held */
अटल bool wiimote_cmd_map_mp(काष्ठा wiimote_data *wdata, __u8 exttype)
अणु
	__u8 wmem;

	/* map MP with correct pass-through mode */
	चयन (exttype) अणु
	हाल WIIMOTE_EXT_CLASSIC_CONTROLLER:
	हाल WIIMOTE_EXT_DRUMS:
	हाल WIIMOTE_EXT_GUITAR:
		wmem = 0x07;
		अवरोध;
	हाल WIIMOTE_EXT_NUNCHUK:
		wmem = 0x05;
		अवरोध;
	शेष:
		wmem = 0x04;
		अवरोध;
	पूर्ण

	वापस wiimote_cmd_ग_लिखो(wdata, 0xa600fe, &wmem, माप(wmem));
पूर्ण

/* requires the cmd-mutex to be held */
अटल bool wiimote_cmd_पढ़ो_mp(काष्ठा wiimote_data *wdata, __u8 *rmem)
अणु
	पूर्णांक ret;

	/* पढ़ो motion plus ID */
	ret = wiimote_cmd_पढ़ो(wdata, 0xa600fa, rmem, 6);
	अगर (ret != 6)
		वापस false;

	hid_dbg(wdata->hdev, "motion plus ID: %6phC\n", rmem);

	अगर (rmem[5] == 0x05)
		वापस true;

	hid_info(wdata->hdev, "unknown motion plus ID: %6phC\n", rmem);

	वापस false;
पूर्ण

/* requires the cmd-mutex to be held */
अटल __u8 wiimote_cmd_पढ़ो_mp_mapped(काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret;
	__u8 rmem[6];

	/* पढ़ो motion plus ID */
	ret = wiimote_cmd_पढ़ो(wdata, 0xa400fa, rmem, 6);
	अगर (ret != 6)
		वापस WIIMOTE_MP_NONE;

	hid_dbg(wdata->hdev, "mapped motion plus ID: %6phC\n", rmem);

	अगर (rmem[0] == 0xff && rmem[1] == 0xff && rmem[2] == 0xff &&
	    rmem[3] == 0xff && rmem[4] == 0xff && rmem[5] == 0xff)
		वापस WIIMOTE_MP_NONE;

	अगर (rmem[4] == 0x04 && rmem[5] == 0x05)
		वापस WIIMOTE_MP_SINGLE;
	अन्यथा अगर (rmem[4] == 0x05 && rmem[5] == 0x05)
		वापस WIIMOTE_MP_PASSTHROUGH_NUNCHUK;
	अन्यथा अगर (rmem[4] == 0x07 && rmem[5] == 0x05)
		वापस WIIMOTE_MP_PASSTHROUGH_CLASSIC;

	वापस WIIMOTE_MP_UNKNOWN;
पूर्ण

/* device module handling */

अटल स्थिर __u8 * स्थिर wiimote_devtype_mods[WIIMOTE_DEV_NUM] = अणु
	[WIIMOTE_DEV_PENDING] = (स्थिर __u8[])अणु
		WIIMOD_शून्य,
	पूर्ण,
	[WIIMOTE_DEV_UNKNOWN] = (स्थिर __u8[])अणु
		WIIMOD_NO_MP,
		WIIMOD_शून्य,
	पूर्ण,
	[WIIMOTE_DEV_GENERIC] = (स्थिर __u8[])अणु
		WIIMOD_KEYS,
		WIIMOD_RUMBLE,
		WIIMOD_BATTERY,
		WIIMOD_LED1,
		WIIMOD_LED2,
		WIIMOD_LED3,
		WIIMOD_LED4,
		WIIMOD_ACCEL,
		WIIMOD_IR,
		WIIMOD_शून्य,
	पूर्ण,
	[WIIMOTE_DEV_GEN10] = (स्थिर __u8[])अणु
		WIIMOD_KEYS,
		WIIMOD_RUMBLE,
		WIIMOD_BATTERY,
		WIIMOD_LED1,
		WIIMOD_LED2,
		WIIMOD_LED3,
		WIIMOD_LED4,
		WIIMOD_ACCEL,
		WIIMOD_IR,
		WIIMOD_शून्य,
	पूर्ण,
	[WIIMOTE_DEV_GEN20] = (स्थिर __u8[])अणु
		WIIMOD_KEYS,
		WIIMOD_RUMBLE,
		WIIMOD_BATTERY,
		WIIMOD_LED1,
		WIIMOD_LED2,
		WIIMOD_LED3,
		WIIMOD_LED4,
		WIIMOD_ACCEL,
		WIIMOD_IR,
		WIIMOD_BUILTIN_MP,
		WIIMOD_शून्य,
	पूर्ण,
	[WIIMOTE_DEV_BALANCE_BOARD] = (स्थिर __u8[]) अणु
		WIIMOD_BATTERY,
		WIIMOD_LED1,
		WIIMOD_NO_MP,
		WIIMOD_शून्य,
	पूर्ण,
	[WIIMOTE_DEV_PRO_CONTROLLER] = (स्थिर __u8[]) अणु
		WIIMOD_BATTERY,
		WIIMOD_LED1,
		WIIMOD_LED2,
		WIIMOD_LED3,
		WIIMOD_LED4,
		WIIMOD_NO_MP,
		WIIMOD_शून्य,
	पूर्ण,
पूर्ण;

अटल व्योम wiimote_modules_load(काष्ठा wiimote_data *wdata,
				 अचिन्हित पूर्णांक devtype)
अणु
	bool need_input = false;
	स्थिर __u8 *mods, *iter;
	स्थिर काष्ठा wiimod_ops *ops;
	पूर्णांक ret;

	mods = wiimote_devtype_mods[devtype];

	क्रम (iter = mods; *iter != WIIMOD_शून्य; ++iter) अणु
		अगर (wiimod_table[*iter]->flags & WIIMOD_FLAG_INPUT) अणु
			need_input = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (need_input) अणु
		wdata->input = input_allocate_device();
		अगर (!wdata->input)
			वापस;

		input_set_drvdata(wdata->input, wdata);
		wdata->input->dev.parent = &wdata->hdev->dev;
		wdata->input->id.bustype = wdata->hdev->bus;
		wdata->input->id.venकरोr = wdata->hdev->venकरोr;
		wdata->input->id.product = wdata->hdev->product;
		wdata->input->id.version = wdata->hdev->version;
		wdata->input->name = WIIMOTE_NAME;
	पूर्ण

	क्रम (iter = mods; *iter != WIIMOD_शून्य; ++iter) अणु
		ops = wiimod_table[*iter];
		अगर (!ops->probe)
			जारी;

		ret = ops->probe(ops, wdata);
		अगर (ret)
			जाओ error;
	पूर्ण

	अगर (wdata->input) अणु
		ret = input_रेजिस्टर_device(wdata->input);
		अगर (ret)
			जाओ error;
	पूर्ण

	spin_lock_irq(&wdata->state.lock);
	wdata->state.devtype = devtype;
	spin_unlock_irq(&wdata->state.lock);
	वापस;

error:
	क्रम ( ; iter-- != mods; ) अणु
		ops = wiimod_table[*iter];
		अगर (ops->हटाओ)
			ops->हटाओ(ops, wdata);
	पूर्ण

	अगर (wdata->input) अणु
		input_मुक्त_device(wdata->input);
		wdata->input = शून्य;
	पूर्ण
पूर्ण

अटल व्योम wiimote_modules_unload(काष्ठा wiimote_data *wdata)
अणु
	स्थिर __u8 *mods, *iter;
	स्थिर काष्ठा wiimod_ops *ops;
	अचिन्हित दीर्घ flags;

	mods = wiimote_devtype_mods[wdata->state.devtype];

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.devtype = WIIMOTE_DEV_UNKNOWN;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	/* find end of list */
	क्रम (iter = mods; *iter != WIIMOD_शून्य; ++iter)
		/* empty */ ;

	अगर (wdata->input) अणु
		input_get_device(wdata->input);
		input_unरेजिस्टर_device(wdata->input);
	पूर्ण

	क्रम ( ; iter-- != mods; ) अणु
		ops = wiimod_table[*iter];
		अगर (ops->हटाओ)
			ops->हटाओ(ops, wdata);
	पूर्ण

	अगर (wdata->input) अणु
		input_put_device(wdata->input);
		wdata->input = शून्य;
	पूर्ण
पूर्ण

/* device extension handling */

अटल व्योम wiimote_ext_load(काष्ठा wiimote_data *wdata, अचिन्हित पूर्णांक ext)
अणु
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा wiimod_ops *ops;
	पूर्णांक ret;

	ops = wiimod_ext_table[ext];

	अगर (ops->probe) अणु
		ret = ops->probe(ops, wdata);
		अगर (ret)
			ext = WIIMOTE_EXT_UNKNOWN;
	पूर्ण

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.exttype = ext;
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल व्योम wiimote_ext_unload(काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा wiimod_ops *ops;

	ops = wiimod_ext_table[wdata->state.exttype];

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.exttype = WIIMOTE_EXT_UNKNOWN;
	wdata->state.flags &= ~WIIPROTO_FLAG_EXT_USED;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	अगर (ops->हटाओ)
		ops->हटाओ(ops, wdata);
पूर्ण

अटल व्योम wiimote_mp_load(काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा wiimod_ops *ops;
	पूर्णांक ret;
	__u8 mode = 2;

	ops = &wiimod_mp;
	अगर (ops->probe) अणु
		ret = ops->probe(ops, wdata);
		अगर (ret)
			mode = 1;
	पूर्ण

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.mp = mode;
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल व्योम wiimote_mp_unload(काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा wiimod_ops *ops;

	अगर (wdata->state.mp < 2)
		वापस;

	ops = &wiimod_mp;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.mp = 0;
	wdata->state.flags &= ~WIIPROTO_FLAG_MP_USED;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	अगर (ops->हटाओ)
		ops->हटाओ(ops, wdata);
पूर्ण

/* device (re-)initialization and detection */

अटल स्थिर अक्षर *wiimote_devtype_names[WIIMOTE_DEV_NUM] = अणु
	[WIIMOTE_DEV_PENDING] = "Pending",
	[WIIMOTE_DEV_UNKNOWN] = "Unknown",
	[WIIMOTE_DEV_GENERIC] = "Generic",
	[WIIMOTE_DEV_GEN10] = "Nintendo Wii Remote (Gen 1)",
	[WIIMOTE_DEV_GEN20] = "Nintendo Wii Remote Plus (Gen 2)",
	[WIIMOTE_DEV_BALANCE_BOARD] = "Nintendo Wii Balance Board",
	[WIIMOTE_DEV_PRO_CONTROLLER] = "Nintendo Wii U Pro Controller",
पूर्ण;

/* Try to guess the device type based on all collected inक्रमmation. We
 * first try to detect by अटल extension types, then VID/PID and the
 * device name. If we cannot detect the device, we use
 * WIIMOTE_DEV_GENERIC so all modules will get probed on the device. */
अटल व्योम wiimote_init_set_type(काष्ठा wiimote_data *wdata,
				  __u8 exttype)
अणु
	__u8 devtype = WIIMOTE_DEV_GENERIC;
	__u16 venकरोr, product;
	स्थिर अक्षर *name;

	venकरोr = wdata->hdev->venकरोr;
	product = wdata->hdev->product;
	name = wdata->hdev->name;

	अगर (exttype == WIIMOTE_EXT_BALANCE_BOARD) अणु
		devtype = WIIMOTE_DEV_BALANCE_BOARD;
		जाओ करोne;
	पूर्ण अन्यथा अगर (exttype == WIIMOTE_EXT_PRO_CONTROLLER) अणु
		devtype = WIIMOTE_DEV_PRO_CONTROLLER;
		जाओ करोne;
	पूर्ण

	अगर (!म_भेद(name, "Nintendo RVL-CNT-01")) अणु
		devtype = WIIMOTE_DEV_GEN10;
		जाओ करोne;
	पूर्ण अन्यथा अगर (!म_भेद(name, "Nintendo RVL-CNT-01-TR")) अणु
		devtype = WIIMOTE_DEV_GEN20;
		जाओ करोne;
	पूर्ण अन्यथा अगर (!म_भेद(name, "Nintendo RVL-WBC-01")) अणु
		devtype = WIIMOTE_DEV_BALANCE_BOARD;
		जाओ करोne;
	पूर्ण अन्यथा अगर (!म_भेद(name, "Nintendo RVL-CNT-01-UC")) अणु
		devtype = WIIMOTE_DEV_PRO_CONTROLLER;
		जाओ करोne;
	पूर्ण

	अगर (venकरोr == USB_VENDOR_ID_NINTENDO) अणु
		अगर (product == USB_DEVICE_ID_NINTENDO_WIIMOTE) अणु
			devtype = WIIMOTE_DEV_GEN10;
			जाओ करोne;
		पूर्ण अन्यथा अगर (product == USB_DEVICE_ID_NINTENDO_WIIMOTE2) अणु
			devtype = WIIMOTE_DEV_GEN20;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	अगर (devtype == WIIMOTE_DEV_GENERIC)
		hid_info(wdata->hdev, "cannot detect device; NAME: %s VID: %04x PID: %04x EXT: %04x\n",
			name, venकरोr, product, exttype);
	अन्यथा
		hid_info(wdata->hdev, "detected device: %s\n",
			 wiimote_devtype_names[devtype]);

	wiimote_modules_load(wdata, devtype);
पूर्ण

अटल व्योम wiimote_init_detect(काष्ठा wiimote_data *wdata)
अणु
	__u8 exttype = WIIMOTE_EXT_NONE, extdata[6];
	bool ext;
	पूर्णांक ret;

	wiimote_cmd_acquire_noपूर्णांक(wdata);

	spin_lock_irq(&wdata->state.lock);
	wdata->state.devtype = WIIMOTE_DEV_UNKNOWN;
	wiimote_cmd_set(wdata, WIIPROTO_REQ_SREQ, 0);
	wiiproto_req_status(wdata);
	spin_unlock_irq(&wdata->state.lock);

	ret = wiimote_cmd_रुको_noपूर्णांक(wdata);
	अगर (ret)
		जाओ out_release;

	spin_lock_irq(&wdata->state.lock);
	ext = wdata->state.flags & WIIPROTO_FLAG_EXT_PLUGGED;
	spin_unlock_irq(&wdata->state.lock);

	अगर (!ext)
		जाओ out_release;

	wiimote_cmd_init_ext(wdata);
	exttype = wiimote_cmd_पढ़ो_ext(wdata, extdata);

out_release:
	wiimote_cmd_release(wdata);
	wiimote_init_set_type(wdata, exttype);

	/* schedule MP समयr */
	spin_lock_irq(&wdata->state.lock);
	अगर (!(wdata->state.flags & WIIPROTO_FLAG_BUILTIN_MP) &&
	    !(wdata->state.flags & WIIPROTO_FLAG_NO_MP))
		mod_समयr(&wdata->समयr, jअगरfies + HZ * 4);
	spin_unlock_irq(&wdata->state.lock);
पूर्ण

/*
 * MP hotplug events are not generated by the wiimote. Thereक्रमe, we need
 * polling to detect it. We use a 4s पूर्णांकerval क्रम polling MP रेजिस्टरs. This
 * seems reasonable considering applications can trigger it manually via
 * sysfs requests.
 */
अटल व्योम wiimote_init_poll_mp(काष्ठा wiimote_data *wdata)
अणु
	bool mp;
	__u8 mpdata[6];

	wiimote_cmd_acquire_noपूर्णांक(wdata);
	wiimote_cmd_init_mp(wdata);
	mp = wiimote_cmd_पढ़ो_mp(wdata, mpdata);
	wiimote_cmd_release(wdata);

	/* load/unload MP module अगर it changed */
	अगर (mp) अणु
		अगर (!wdata->state.mp) अणु
			hid_info(wdata->hdev, "detected extension: Nintendo Wii Motion Plus\n");
			wiimote_mp_load(wdata);
		पूर्ण
	पूर्ण अन्यथा अगर (wdata->state.mp) अणु
		wiimote_mp_unload(wdata);
	पूर्ण

	mod_समयr(&wdata->समयr, jअगरfies + HZ * 4);
पूर्ण

/*
 * Check whether the wiimote is in the expected state. The extension रेजिस्टरs
 * may change during hotplug and initialization so we might get hotplug events
 * that we caused by remapping some memory.
 * We use some heuristics here to check known states. If the wiimote is in the
 * expected state, we can ignore the hotplug event.
 *
 * Returns "true" अगर the device is in expected state, "false" अगर we should
 * reकरो hotplug handling and extension initialization.
 */
अटल bool wiimote_init_check(काष्ठा wiimote_data *wdata)
अणु
	__u32 flags;
	__u8 type, data[6];
	bool ret, poll_mp;

	spin_lock_irq(&wdata->state.lock);
	flags = wdata->state.flags;
	spin_unlock_irq(&wdata->state.lock);

	wiimote_cmd_acquire_noपूर्णांक(wdata);

	/* If MP is used and active, but the extension is not, we expect:
	 *   पढ़ो_mp_mapped() == WIIMOTE_MP_SINGLE
	 *   state.flags == !EXT_ACTIVE && !MP_PLUGGED && MP_ACTIVE
	 * We करो not check EXT_PLUGGED because it might change during
	 * initialization of MP without extensions.
	 *  - If MP is unplugged/replugged, पढ़ो_mp_mapped() fails
	 *  - If EXT is plugged, MP_PLUGGED will get set */
	अगर (wdata->state.exttype == WIIMOTE_EXT_NONE &&
	    wdata->state.mp > 0 && (flags & WIIPROTO_FLAG_MP_USED)) अणु
		type = wiimote_cmd_पढ़ो_mp_mapped(wdata);
		ret = type == WIIMOTE_MP_SINGLE;

		spin_lock_irq(&wdata->state.lock);
		ret = ret && !(wdata->state.flags & WIIPROTO_FLAG_EXT_ACTIVE);
		ret = ret && !(wdata->state.flags & WIIPROTO_FLAG_MP_PLUGGED);
		ret = ret && (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE);
		spin_unlock_irq(&wdata->state.lock);

		अगर (!ret)
			hid_dbg(wdata->hdev, "state left: !EXT && MP\n");

		/* जबतक MP is mapped, we get EXT_PLUGGED events */
		poll_mp = false;

		जाओ out_release;
	पूर्ण

	/* If MP is unused, but the extension port is used, we expect:
	 *   पढ़ो_ext == state.exttype
	 *   state.flags == !MP_ACTIVE && EXT_ACTIVE
	 * - If MP is plugged/unplugged, our समयr detects it
	 * - If EXT is unplugged/replugged, EXT_ACTIVE will become unset */
	अगर (!(flags & WIIPROTO_FLAG_MP_USED) &&
	    wdata->state.exttype != WIIMOTE_EXT_NONE) अणु
		type = wiimote_cmd_पढ़ो_ext(wdata, data);
		ret = type == wdata->state.exttype;

		spin_lock_irq(&wdata->state.lock);
		ret = ret && !(wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE);
		ret = ret && (wdata->state.flags & WIIPROTO_FLAG_EXT_ACTIVE);
		spin_unlock_irq(&wdata->state.lock);

		अगर (!ret)
			hid_dbg(wdata->hdev, "state left: EXT && !MP\n");

		/* poll MP क्रम hotplug events */
		poll_mp = true;

		जाओ out_release;
	पूर्ण

	/* If neither MP nor an extension are used, we expect:
	 *   पढ़ो_ext() == WIIMOTE_EXT_NONE
	 *   state.flags == !MP_ACTIVE && !EXT_ACTIVE && !EXT_PLUGGED
	 * No need to perक्रमm any action in this हाल as everything is
	 * disabled alपढ़ोy.
	 * - If MP is plugged/unplugged, our समयr detects it
	 * - If EXT is plugged, EXT_PLUGGED will be set */
	अगर (!(flags & WIIPROTO_FLAG_MP_USED) &&
	    wdata->state.exttype == WIIMOTE_EXT_NONE) अणु
		type = wiimote_cmd_पढ़ो_ext(wdata, data);
		ret = type == wdata->state.exttype;

		spin_lock_irq(&wdata->state.lock);
		ret = ret && !(wdata->state.flags & WIIPROTO_FLAG_EXT_ACTIVE);
		ret = ret && !(wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE);
		ret = ret && !(wdata->state.flags & WIIPROTO_FLAG_EXT_PLUGGED);
		spin_unlock_irq(&wdata->state.lock);

		अगर (!ret)
			hid_dbg(wdata->hdev, "state left: !EXT && !MP\n");

		/* poll MP क्रम hotplug events */
		poll_mp = true;

		जाओ out_release;
	पूर्ण

	/* The trickiest part is अगर both EXT and MP are active. We cannot पढ़ो
	 * the EXT ID, anymore, because MP is mapped over it. However, we use
	 * a handy trick here:
	 *   - EXT_ACTIVE is unset whenever !MP_PLUGGED is sent
	 * MP_PLUGGED might be re-sent again beक्रमe we are scheduled, but
	 * EXT_ACTIVE will stay unset.
	 * So it is enough to check क्रम mp_mapped() and MP_ACTIVE and
	 * EXT_ACTIVE. EXT_PLUGGED is a sanity check. */
	अगर (wdata->state.exttype != WIIMOTE_EXT_NONE &&
	    wdata->state.mp > 0 && (flags & WIIPROTO_FLAG_MP_USED)) अणु
		type = wiimote_cmd_पढ़ो_mp_mapped(wdata);
		ret = type != WIIMOTE_MP_NONE;
		ret = ret && type != WIIMOTE_MP_UNKNOWN;
		ret = ret && type != WIIMOTE_MP_SINGLE;

		spin_lock_irq(&wdata->state.lock);
		ret = ret && (wdata->state.flags & WIIPROTO_FLAG_EXT_PLUGGED);
		ret = ret && (wdata->state.flags & WIIPROTO_FLAG_EXT_ACTIVE);
		ret = ret && (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE);
		spin_unlock_irq(&wdata->state.lock);

		अगर (!ret)
			hid_dbg(wdata->hdev, "state left: EXT && MP\n");

		/* जबतक MP is mapped, we get EXT_PLUGGED events */
		poll_mp = false;

		जाओ out_release;
	पूर्ण

	/* unknown state */
	ret = false;

out_release:
	wiimote_cmd_release(wdata);

	/* only poll क्रम MP अगर requested and अगर state didn't change */
	अगर (ret && poll_mp && !(flags & WIIPROTO_FLAG_BUILTIN_MP) &&
	    !(flags & WIIPROTO_FLAG_NO_MP))
		wiimote_init_poll_mp(wdata);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *wiimote_exttype_names[WIIMOTE_EXT_NUM] = अणु
	[WIIMOTE_EXT_NONE] = "None",
	[WIIMOTE_EXT_UNKNOWN] = "Unknown",
	[WIIMOTE_EXT_NUNCHUK] = "Nintendo Wii Nunchuk",
	[WIIMOTE_EXT_CLASSIC_CONTROLLER] = "Nintendo Wii Classic Controller",
	[WIIMOTE_EXT_BALANCE_BOARD] = "Nintendo Wii Balance Board",
	[WIIMOTE_EXT_PRO_CONTROLLER] = "Nintendo Wii U Pro Controller",
	[WIIMOTE_EXT_DRUMS] = "Nintendo Wii Drums",
	[WIIMOTE_EXT_GUITAR] = "Nintendo Wii Guitar",
पूर्ण;

/*
 * Handle hotplug events
 * If we receive an hotplug event and the device-check failed, we deinitialize
 * the extension ports, re-पढ़ो all extension IDs and set the device पूर्णांकo
 * the desired state. This involves mapping MP पूर्णांकo the मुख्य extension
 * रेजिस्टरs, setting up extension passthrough modes and initializing the
 * requested extensions.
 */
अटल व्योम wiimote_init_hotplug(काष्ठा wiimote_data *wdata)
अणु
	__u8 exttype, extdata[6], mpdata[6];
	__u32 flags;
	bool mp;

	hid_dbg(wdata->hdev, "detect extensions..\n");

	wiimote_cmd_acquire_noपूर्णांक(wdata);

	spin_lock_irq(&wdata->state.lock);

	/* get state snapshot that we will then work on */
	flags = wdata->state.flags;

	/* disable event क्रमwarding temporarily */
	wdata->state.flags &= ~WIIPROTO_FLAG_EXT_ACTIVE;
	wdata->state.flags &= ~WIIPROTO_FLAG_MP_ACTIVE;

	spin_unlock_irq(&wdata->state.lock);

	/* init extension and MP (deactivates current extension or MP) */
	wiimote_cmd_init_ext(wdata);
	अगर (flags & WIIPROTO_FLAG_NO_MP) अणु
		mp = false;
	पूर्ण अन्यथा अणु
		wiimote_cmd_init_mp(wdata);
		mp = wiimote_cmd_पढ़ो_mp(wdata, mpdata);
	पूर्ण
	exttype = wiimote_cmd_पढ़ो_ext(wdata, extdata);

	wiimote_cmd_release(wdata);

	/* load/unload extension module अगर it changed */
	अगर (exttype != wdata->state.exttype) अणु
		/* unload previous extension */
		wiimote_ext_unload(wdata);

		अगर (exttype == WIIMOTE_EXT_UNKNOWN) अणु
			hid_info(wdata->hdev, "cannot detect extension; %6phC\n",
				 extdata);
		पूर्ण अन्यथा अगर (exttype == WIIMOTE_EXT_NONE) अणु
			spin_lock_irq(&wdata->state.lock);
			wdata->state.exttype = WIIMOTE_EXT_NONE;
			spin_unlock_irq(&wdata->state.lock);
		पूर्ण अन्यथा अणु
			hid_info(wdata->hdev, "detected extension: %s\n",
				 wiimote_exttype_names[exttype]);
			/* try loading new extension */
			wiimote_ext_load(wdata, exttype);
		पूर्ण
	पूर्ण

	/* load/unload MP module अगर it changed */
	अगर (mp) अणु
		अगर (!wdata->state.mp) अणु
			hid_info(wdata->hdev, "detected extension: Nintendo Wii Motion Plus\n");
			wiimote_mp_load(wdata);
		पूर्ण
	पूर्ण अन्यथा अगर (wdata->state.mp) अणु
		wiimote_mp_unload(wdata);
	पूर्ण

	/* अगर MP is not used, करो not map or activate it */
	अगर (!(flags & WIIPROTO_FLAG_MP_USED))
		mp = false;

	/* map MP पूर्णांकo मुख्य extension रेजिस्टरs अगर used */
	अगर (mp) अणु
		wiimote_cmd_acquire_noपूर्णांक(wdata);
		wiimote_cmd_map_mp(wdata, exttype);
		wiimote_cmd_release(wdata);

		/* delete MP hotplug समयr */
		del_समयr_sync(&wdata->समयr);
	पूर्ण अन्यथा अणु
		/* reschedule MP hotplug समयr */
		अगर (!(flags & WIIPROTO_FLAG_BUILTIN_MP) &&
		    !(flags & WIIPROTO_FLAG_NO_MP))
			mod_समयr(&wdata->समयr, jअगरfies + HZ * 4);
	पूर्ण

	spin_lock_irq(&wdata->state.lock);

	/* enable data क्रमwarding again and set expected hotplug state */
	अगर (mp) अणु
		wdata->state.flags |= WIIPROTO_FLAG_MP_ACTIVE;
		अगर (wdata->state.exttype == WIIMOTE_EXT_NONE) अणु
			wdata->state.flags &= ~WIIPROTO_FLAG_EXT_PLUGGED;
			wdata->state.flags &= ~WIIPROTO_FLAG_MP_PLUGGED;
		पूर्ण अन्यथा अणु
			wdata->state.flags &= ~WIIPROTO_FLAG_EXT_PLUGGED;
			wdata->state.flags |= WIIPROTO_FLAG_MP_PLUGGED;
			wdata->state.flags |= WIIPROTO_FLAG_EXT_ACTIVE;
		पूर्ण
	पूर्ण अन्यथा अगर (wdata->state.exttype != WIIMOTE_EXT_NONE) अणु
		wdata->state.flags |= WIIPROTO_FLAG_EXT_ACTIVE;
	पूर्ण

	/* request status report क्रम hotplug state updates */
	wiiproto_req_status(wdata);

	spin_unlock_irq(&wdata->state.lock);

	hid_dbg(wdata->hdev, "detected extensions: MP: %d EXT: %d\n",
		wdata->state.mp, wdata->state.exttype);
पूर्ण

अटल व्योम wiimote_init_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wiimote_data *wdata = container_of(work, काष्ठा wiimote_data,
						  init_worker);
	bool changed = false;

	अगर (wdata->state.devtype == WIIMOTE_DEV_PENDING) अणु
		wiimote_init_detect(wdata);
		changed = true;
	पूर्ण

	अगर (changed || !wiimote_init_check(wdata))
		wiimote_init_hotplug(wdata);

	अगर (changed)
		kobject_uevent(&wdata->hdev->dev.kobj, KOBJ_CHANGE);
पूर्ण

व्योम __wiimote_schedule(काष्ठा wiimote_data *wdata)
अणु
	अगर (!(wdata->state.flags & WIIPROTO_FLAG_EXITING))
		schedule_work(&wdata->init_worker);
पूर्ण

अटल व्योम wiimote_schedule(काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	__wiimote_schedule(wdata);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल व्योम wiimote_init_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा wiimote_data *wdata = from_समयr(wdata, t, समयr);

	wiimote_schedule(wdata);
पूर्ण

/* protocol handlers */

अटल व्योम handler_keys(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	स्थिर __u8 *iter, *mods;
	स्थिर काष्ठा wiimod_ops *ops;

	ops = wiimod_ext_table[wdata->state.exttype];
	अगर (ops->in_keys) अणु
		ops->in_keys(wdata, payload);
		वापस;
	पूर्ण

	mods = wiimote_devtype_mods[wdata->state.devtype];
	क्रम (iter = mods; *iter != WIIMOD_शून्य; ++iter) अणु
		ops = wiimod_table[*iter];
		अगर (ops->in_keys) अणु
			ops->in_keys(wdata, payload);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम handler_accel(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	स्थिर __u8 *iter, *mods;
	स्थिर काष्ठा wiimod_ops *ops;

	ops = wiimod_ext_table[wdata->state.exttype];
	अगर (ops->in_accel) अणु
		ops->in_accel(wdata, payload);
		वापस;
	पूर्ण

	mods = wiimote_devtype_mods[wdata->state.devtype];
	क्रम (iter = mods; *iter != WIIMOD_शून्य; ++iter) अणु
		ops = wiimod_table[*iter];
		अगर (ops->in_accel) अणु
			ops->in_accel(wdata, payload);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool valid_ext_handler(स्थिर काष्ठा wiimod_ops *ops, माप_प्रकार len)
अणु
	अगर (!ops->in_ext)
		वापस false;
	अगर ((ops->flags & WIIMOD_FLAG_EXT8) && len < 8)
		वापस false;
	अगर ((ops->flags & WIIMOD_FLAG_EXT16) && len < 16)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम handler_ext(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload,
			माप_प्रकार len)
अणु
	अटल स्थिर __u8 invalid[21] = अणु 0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff पूर्ण;
	स्थिर __u8 *iter, *mods;
	स्थिर काष्ठा wiimod_ops *ops;
	bool is_mp;

	अगर (len > 21)
		len = 21;
	अगर (len < 6 || !स_भेद(payload, invalid, len))
		वापस;

	/* अगर MP is active, track MP slot hotplugging */
	अगर (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) अणु
		/* this bit is set क्रम invalid events (eg. during hotplug) */
		अगर (payload[5] & 0x01)
			वापस;

		अगर (payload[4] & 0x01) अणु
			अगर (!(wdata->state.flags & WIIPROTO_FLAG_MP_PLUGGED)) अणु
				hid_dbg(wdata->hdev, "MP hotplug: 1\n");
				wdata->state.flags |= WIIPROTO_FLAG_MP_PLUGGED;
				__wiimote_schedule(wdata);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (wdata->state.flags & WIIPROTO_FLAG_MP_PLUGGED) अणु
				hid_dbg(wdata->hdev, "MP hotplug: 0\n");
				wdata->state.flags &= ~WIIPROTO_FLAG_MP_PLUGGED;
				wdata->state.flags &= ~WIIPROTO_FLAG_EXT_ACTIVE;
				__wiimote_schedule(wdata);
			पूर्ण
		पूर्ण

		/* detect MP data that is sent पूर्णांकerleaved with EXT data */
		is_mp = payload[5] & 0x02;
	पूर्ण अन्यथा अणु
		is_mp = false;
	पूर्ण

	/* ignore EXT events अगर no extension is active */
	अगर (!(wdata->state.flags & WIIPROTO_FLAG_EXT_ACTIVE) && !is_mp)
		वापस;

	/* try क्रमwarding to extension handler, first */
	ops = wiimod_ext_table[wdata->state.exttype];
	अगर (is_mp && ops->in_mp) अणु
		ops->in_mp(wdata, payload);
		वापस;
	पूर्ण अन्यथा अगर (!is_mp && valid_ext_handler(ops, len)) अणु
		ops->in_ext(wdata, payload);
		वापस;
	पूर्ण

	/* try क्रमwarding to MP handler */
	ops = &wiimod_mp;
	अगर (is_mp && ops->in_mp) अणु
		ops->in_mp(wdata, payload);
		वापस;
	पूर्ण अन्यथा अगर (!is_mp && valid_ext_handler(ops, len)) अणु
		ops->in_ext(wdata, payload);
		वापस;
	पूर्ण

	/* try क्रमwarding to loaded modules */
	mods = wiimote_devtype_mods[wdata->state.devtype];
	क्रम (iter = mods; *iter != WIIMOD_शून्य; ++iter) अणु
		ops = wiimod_table[*iter];
		अगर (is_mp && ops->in_mp) अणु
			ops->in_mp(wdata, payload);
			वापस;
		पूर्ण अन्यथा अगर (!is_mp && valid_ext_handler(ops, len)) अणु
			ops->in_ext(wdata, payload);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा ir_to_input0(wdata, ir, packed) handler_ir((wdata), (ir), (packed), 0)
#घोषणा ir_to_input1(wdata, ir, packed) handler_ir((wdata), (ir), (packed), 1)
#घोषणा ir_to_input2(wdata, ir, packed) handler_ir((wdata), (ir), (packed), 2)
#घोषणा ir_to_input3(wdata, ir, packed) handler_ir((wdata), (ir), (packed), 3)

अटल व्योम handler_ir(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload,
		       bool packed, अचिन्हित पूर्णांक id)
अणु
	स्थिर __u8 *iter, *mods;
	स्थिर काष्ठा wiimod_ops *ops;

	ops = wiimod_ext_table[wdata->state.exttype];
	अगर (ops->in_ir) अणु
		ops->in_ir(wdata, payload, packed, id);
		वापस;
	पूर्ण

	mods = wiimote_devtype_mods[wdata->state.devtype];
	क्रम (iter = mods; *iter != WIIMOD_शून्य; ++iter) अणु
		ops = wiimod_table[*iter];
		अगर (ops->in_ir) अणु
			ops->in_ir(wdata, payload, packed, id);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* reduced status report with "BB BB" key data only */
अटल व्योम handler_status_K(काष्ठा wiimote_data *wdata,
			     स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);

	/* on status reports the drm is reset so we need to resend the drm */
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
पूर्ण

/* extended status report with "BB BB LF 00 00 VV" data */
अटल व्योम handler_status(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_status_K(wdata, payload);

	/* update extension status */
	अगर (payload[2] & 0x02) अणु
		अगर (!(wdata->state.flags & WIIPROTO_FLAG_EXT_PLUGGED)) अणु
			hid_dbg(wdata->hdev, "EXT hotplug: 1\n");
			wdata->state.flags |= WIIPROTO_FLAG_EXT_PLUGGED;
			__wiimote_schedule(wdata);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (wdata->state.flags & WIIPROTO_FLAG_EXT_PLUGGED) अणु
			hid_dbg(wdata->hdev, "EXT hotplug: 0\n");
			wdata->state.flags &= ~WIIPROTO_FLAG_EXT_PLUGGED;
			wdata->state.flags &= ~WIIPROTO_FLAG_MP_PLUGGED;
			wdata->state.flags &= ~WIIPROTO_FLAG_EXT_ACTIVE;
			wdata->state.flags &= ~WIIPROTO_FLAG_MP_ACTIVE;
			__wiimote_schedule(wdata);
		पूर्ण
	पूर्ण

	wdata->state.cmd_battery = payload[5];
	अगर (wiimote_cmd_pending(wdata, WIIPROTO_REQ_SREQ, 0))
		wiimote_cmd_complete(wdata);
पूर्ण

/* reduced generic report with "BB BB" key data only */
अटल व्योम handler_generic_K(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);
पूर्ण

अटल व्योम handler_data(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	__u16 offset = payload[3] << 8 | payload[4];
	__u8 size = (payload[2] >> 4) + 1;
	__u8 err = payload[2] & 0x0f;

	handler_keys(wdata, payload);

	अगर (wiimote_cmd_pending(wdata, WIIPROTO_REQ_RMEM, offset)) अणु
		अगर (err)
			size = 0;
		अन्यथा अगर (size > wdata->state.cmd_पढ़ो_size)
			size = wdata->state.cmd_पढ़ो_size;

		wdata->state.cmd_पढ़ो_size = size;
		अगर (wdata->state.cmd_पढ़ो_buf)
			स_नकल(wdata->state.cmd_पढ़ो_buf, &payload[5], size);
		wiimote_cmd_complete(wdata);
	पूर्ण
पूर्ण

अटल व्योम handler_वापस(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	__u8 err = payload[3];
	__u8 cmd = payload[2];

	handler_keys(wdata, payload);

	अगर (wiimote_cmd_pending(wdata, cmd, 0)) अणु
		wdata->state.cmd_err = err;
		wiimote_cmd_complete(wdata);
	पूर्ण अन्यथा अगर (err) अणु
		hid_warn(wdata->hdev, "Remote error %u on req %u\n", err,
									cmd);
	पूर्ण
पूर्ण

अटल व्योम handler_drm_KA(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);
	handler_accel(wdata, payload);
पूर्ण

अटल व्योम handler_drm_KE(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);
	handler_ext(wdata, &payload[2], 8);
पूर्ण

अटल व्योम handler_drm_KAI(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);
	handler_accel(wdata, payload);
	ir_to_input0(wdata, &payload[5], false);
	ir_to_input1(wdata, &payload[8], false);
	ir_to_input2(wdata, &payload[11], false);
	ir_to_input3(wdata, &payload[14], false);
पूर्ण

अटल व्योम handler_drm_KEE(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);
	handler_ext(wdata, &payload[2], 19);
पूर्ण

अटल व्योम handler_drm_KIE(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);
	ir_to_input0(wdata, &payload[2], false);
	ir_to_input1(wdata, &payload[4], true);
	ir_to_input2(wdata, &payload[7], false);
	ir_to_input3(wdata, &payload[9], true);
	handler_ext(wdata, &payload[12], 9);
पूर्ण

अटल व्योम handler_drm_KAE(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);
	handler_accel(wdata, payload);
	handler_ext(wdata, &payload[5], 16);
पूर्ण

अटल व्योम handler_drm_KAIE(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);
	handler_accel(wdata, payload);
	ir_to_input0(wdata, &payload[5], false);
	ir_to_input1(wdata, &payload[7], true);
	ir_to_input2(wdata, &payload[10], false);
	ir_to_input3(wdata, &payload[12], true);
	handler_ext(wdata, &payload[15], 6);
पूर्ण

अटल व्योम handler_drm_E(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_ext(wdata, payload, 21);
पूर्ण

अटल व्योम handler_drm_SKAI1(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	handler_keys(wdata, payload);

	wdata->state.accel_split[0] = payload[2];
	wdata->state.accel_split[1] = (payload[0] >> 1) & (0x10 | 0x20);
	wdata->state.accel_split[1] |= (payload[1] << 1) & (0x40 | 0x80);

	ir_to_input0(wdata, &payload[3], false);
	ir_to_input1(wdata, &payload[12], false);
पूर्ण

अटल व्योम handler_drm_SKAI2(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload)
अणु
	__u8 buf[5];

	handler_keys(wdata, payload);

	wdata->state.accel_split[1] |= (payload[0] >> 5) & (0x01 | 0x02);
	wdata->state.accel_split[1] |= (payload[1] >> 3) & (0x04 | 0x08);

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = wdata->state.accel_split[0];
	buf[3] = payload[2];
	buf[4] = wdata->state.accel_split[1];
	handler_accel(wdata, buf);

	ir_to_input2(wdata, &payload[3], false);
	ir_to_input3(wdata, &payload[12], false);
पूर्ण

काष्ठा wiiproto_handler अणु
	__u8 id;
	माप_प्रकार size;
	व्योम (*func)(काष्ठा wiimote_data *wdata, स्थिर __u8 *payload);
पूर्ण;

अटल स्थिर काष्ठा wiiproto_handler handlers[] = अणु
	अणु .id = WIIPROTO_REQ_STATUS, .size = 6, .func = handler_status पूर्ण,
	अणु .id = WIIPROTO_REQ_STATUS, .size = 2, .func = handler_status_K पूर्ण,
	अणु .id = WIIPROTO_REQ_DATA, .size = 21, .func = handler_data पूर्ण,
	अणु .id = WIIPROTO_REQ_DATA, .size = 2, .func = handler_generic_K पूर्ण,
	अणु .id = WIIPROTO_REQ_RETURN, .size = 4, .func = handler_वापस पूर्ण,
	अणु .id = WIIPROTO_REQ_RETURN, .size = 2, .func = handler_generic_K पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_K, .size = 2, .func = handler_keys पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KA, .size = 5, .func = handler_drm_KA पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KA, .size = 2, .func = handler_generic_K पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KE, .size = 10, .func = handler_drm_KE पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KE, .size = 2, .func = handler_generic_K पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KAI, .size = 17, .func = handler_drm_KAI पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KAI, .size = 2, .func = handler_generic_K पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KEE, .size = 21, .func = handler_drm_KEE पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KEE, .size = 2, .func = handler_generic_K पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KAE, .size = 21, .func = handler_drm_KAE पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KAE, .size = 2, .func = handler_generic_K पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KIE, .size = 21, .func = handler_drm_KIE पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KIE, .size = 2, .func = handler_generic_K पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KAIE, .size = 21, .func = handler_drm_KAIE पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_KAIE, .size = 2, .func = handler_generic_K पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_E, .size = 21, .func = handler_drm_E पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_SKAI1, .size = 21, .func = handler_drm_SKAI1 पूर्ण,
	अणु .id = WIIPROTO_REQ_DRM_SKAI2, .size = 21, .func = handler_drm_SKAI2 पूर्ण,
	अणु .id = 0 पूर्ण
पूर्ण;

अटल पूर्णांक wiimote_hid_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
							u8 *raw_data, पूर्णांक size)
अणु
	काष्ठा wiimote_data *wdata = hid_get_drvdata(hdev);
	स्थिर काष्ठा wiiproto_handler *h;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (size < 1)
		वापस -EINVAL;

	क्रम (i = 0; handlers[i].id; ++i) अणु
		h = &handlers[i];
		अगर (h->id == raw_data[0] && h->size < size) अणु
			spin_lock_irqsave(&wdata->state.lock, flags);
			h->func(wdata, &raw_data[1]);
			spin_unlock_irqrestore(&wdata->state.lock, flags);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!handlers[i].id)
		hid_warn(hdev, "Unhandled report %hhu size %d\n", raw_data[0],
									size);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार wiimote_ext_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा wiimote_data *wdata = dev_to_wii(dev);
	__u8 type;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	type = wdata->state.exttype;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	चयन (type) अणु
	हाल WIIMOTE_EXT_NONE:
		वापस प्र_लिखो(buf, "none\n");
	हाल WIIMOTE_EXT_NUNCHUK:
		वापस प्र_लिखो(buf, "nunchuk\n");
	हाल WIIMOTE_EXT_CLASSIC_CONTROLLER:
		वापस प्र_लिखो(buf, "classic\n");
	हाल WIIMOTE_EXT_BALANCE_BOARD:
		वापस प्र_लिखो(buf, "balanceboard\n");
	हाल WIIMOTE_EXT_PRO_CONTROLLER:
		वापस प्र_लिखो(buf, "procontroller\n");
	हाल WIIMOTE_EXT_DRUMS:
		वापस प्र_लिखो(buf, "drums\n");
	हाल WIIMOTE_EXT_GUITAR:
		वापस प्र_लिखो(buf, "guitar\n");
	हाल WIIMOTE_EXT_UNKNOWN:
	शेष:
		वापस प्र_लिखो(buf, "unknown\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार wiimote_ext_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा wiimote_data *wdata = dev_to_wii(dev);

	अगर (!म_भेद(buf, "scan")) अणु
		wiimote_schedule(wdata);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस strnlen(buf, PAGE_SIZE);
पूर्ण

अटल DEVICE_ATTR(extension, S_IRUGO | S_IWUSR | S_IWGRP, wiimote_ext_show,
		   wiimote_ext_store);

अटल sमाप_प्रकार wiimote_dev_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा wiimote_data *wdata = dev_to_wii(dev);
	__u8 type;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	type = wdata->state.devtype;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	चयन (type) अणु
	हाल WIIMOTE_DEV_GENERIC:
		वापस प्र_लिखो(buf, "generic\n");
	हाल WIIMOTE_DEV_GEN10:
		वापस प्र_लिखो(buf, "gen10\n");
	हाल WIIMOTE_DEV_GEN20:
		वापस प्र_लिखो(buf, "gen20\n");
	हाल WIIMOTE_DEV_BALANCE_BOARD:
		वापस प्र_लिखो(buf, "balanceboard\n");
	हाल WIIMOTE_DEV_PRO_CONTROLLER:
		वापस प्र_लिखो(buf, "procontroller\n");
	हाल WIIMOTE_DEV_PENDING:
		वापस प्र_लिखो(buf, "pending\n");
	हाल WIIMOTE_DEV_UNKNOWN:
	शेष:
		वापस प्र_लिखो(buf, "unknown\n");
	पूर्ण
पूर्ण

अटल DEVICE_ATTR(devtype, S_IRUGO, wiimote_dev_show, शून्य);

अटल काष्ठा wiimote_data *wiimote_create(काष्ठा hid_device *hdev)
अणु
	काष्ठा wiimote_data *wdata;

	wdata = kzalloc(माप(*wdata), GFP_KERNEL);
	अगर (!wdata)
		वापस शून्य;

	wdata->hdev = hdev;
	hid_set_drvdata(hdev, wdata);

	spin_lock_init(&wdata->queue.lock);
	INIT_WORK(&wdata->queue.worker, wiimote_queue_worker);

	spin_lock_init(&wdata->state.lock);
	init_completion(&wdata->state.पढ़ोy);
	mutex_init(&wdata->state.sync);
	wdata->state.drm = WIIPROTO_REQ_DRM_K;
	wdata->state.cmd_battery = 0xff;

	INIT_WORK(&wdata->init_worker, wiimote_init_worker);
	समयr_setup(&wdata->समयr, wiimote_init_समयout, 0);

	वापस wdata;
पूर्ण

अटल व्योम wiimote_destroy(काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;

	wiidebug_deinit(wdata);

	/* prevent init_worker from being scheduled again */
	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_EXITING;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	cancel_work_sync(&wdata->init_worker);
	del_समयr_sync(&wdata->समयr);

	device_हटाओ_file(&wdata->hdev->dev, &dev_attr_devtype);
	device_हटाओ_file(&wdata->hdev->dev, &dev_attr_extension);

	wiimote_mp_unload(wdata);
	wiimote_ext_unload(wdata);
	wiimote_modules_unload(wdata);
	cancel_work_sync(&wdata->queue.worker);
	hid_hw_बंद(wdata->hdev);
	hid_hw_stop(wdata->hdev);

	kमुक्त(wdata);
पूर्ण

अटल पूर्णांक wiimote_hid_probe(काष्ठा hid_device *hdev,
				स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा wiimote_data *wdata;
	पूर्णांक ret;

	hdev->quirks |= HID_QUIRK_NO_INIT_REPORTS;

	wdata = wiimote_create(hdev);
	अगर (!wdata) अणु
		hid_err(hdev, "Can't alloc device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "HID parse failed\n");
		जाओ err;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret) अणु
		hid_err(hdev, "HW start failed\n");
		जाओ err;
	पूर्ण

	ret = hid_hw_खोलो(hdev);
	अगर (ret) अणु
		hid_err(hdev, "cannot start hardware I/O\n");
		जाओ err_stop;
	पूर्ण

	ret = device_create_file(&hdev->dev, &dev_attr_extension);
	अगर (ret) अणु
		hid_err(hdev, "cannot create sysfs attribute\n");
		जाओ err_बंद;
	पूर्ण

	ret = device_create_file(&hdev->dev, &dev_attr_devtype);
	अगर (ret) अणु
		hid_err(hdev, "cannot create sysfs attribute\n");
		जाओ err_ext;
	पूर्ण

	ret = wiidebug_init(wdata);
	अगर (ret)
		जाओ err_मुक्त;

	hid_info(hdev, "New device registered\n");

	/* schedule device detection */
	wiimote_schedule(wdata);

	वापस 0;

err_मुक्त:
	wiimote_destroy(wdata);
	वापस ret;

err_ext:
	device_हटाओ_file(&wdata->hdev->dev, &dev_attr_extension);
err_बंद:
	hid_hw_बंद(hdev);
err_stop:
	hid_hw_stop(hdev);
err:
	input_मुक्त_device(wdata->ir);
	input_मुक्त_device(wdata->accel);
	kमुक्त(wdata);
	वापस ret;
पूर्ण

अटल व्योम wiimote_hid_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा wiimote_data *wdata = hid_get_drvdata(hdev);

	hid_info(hdev, "Device removed\n");
	wiimote_destroy(wdata);
पूर्ण

अटल स्थिर काष्ठा hid_device_id wiimote_hid_devices[] = अणु
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_NINTENDO,
				USB_DEVICE_ID_NINTENDO_WIIMOTE) पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_NINTENDO,
				USB_DEVICE_ID_NINTENDO_WIIMOTE2) पूर्ण,
	अणु पूर्ण
पूर्ण;

bool wiimote_dpad_as_analog = false;
module_param_named(dpad_as_analog, wiimote_dpad_as_analog, bool, 0644);
MODULE_PARM_DESC(dpad_as_analog, "Use D-Pad as main analog input");

MODULE_DEVICE_TABLE(hid, wiimote_hid_devices);

अटल काष्ठा hid_driver wiimote_hid_driver = अणु
	.name = "wiimote",
	.id_table = wiimote_hid_devices,
	.probe = wiimote_hid_probe,
	.हटाओ = wiimote_hid_हटाओ,
	.raw_event = wiimote_hid_event,
पूर्ण;
module_hid_driver(wiimote_hid_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Herrmann <dh.herrmann@gmail.com>");
MODULE_DESCRIPTION("Driver for Nintendo Wii / Wii U peripherals");
