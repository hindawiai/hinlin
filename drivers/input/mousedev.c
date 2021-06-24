<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Input driver to ExplorerPS/2 device driver module.
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 * Copyright (c) 2004      Dmitry Torokhov
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MOUSEDEV_MINOR_BASE	32
#घोषणा MOUSEDEV_MINORS		31
#घोषणा MOUSEDEV_MIX		63

#समावेश <linux/bitops.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/major.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/kernel.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Mouse (ExplorerPS/2) device interfaces");
MODULE_LICENSE("GPL");

#अगर_अघोषित CONFIG_INPUT_MOUSEDEV_SCREEN_X
#घोषणा CONFIG_INPUT_MOUSEDEV_SCREEN_X	1024
#पूर्ण_अगर
#अगर_अघोषित CONFIG_INPUT_MOUSEDEV_SCREEN_Y
#घोषणा CONFIG_INPUT_MOUSEDEV_SCREEN_Y	768
#पूर्ण_अगर

अटल पूर्णांक xres = CONFIG_INPUT_MOUSEDEV_SCREEN_X;
module_param(xres, uपूर्णांक, 0644);
MODULE_PARM_DESC(xres, "Horizontal screen resolution");

अटल पूर्णांक yres = CONFIG_INPUT_MOUSEDEV_SCREEN_Y;
module_param(yres, uपूर्णांक, 0644);
MODULE_PARM_DESC(yres, "Vertical screen resolution");

अटल अचिन्हित tap_समय = 200;
module_param(tap_समय, uपूर्णांक, 0644);
MODULE_PARM_DESC(tap_समय, "Tap time for touchpads in absolute mode (msecs)");

काष्ठा mousedev_hw_data अणु
	पूर्णांक dx, dy, dz;
	पूर्णांक x, y;
	पूर्णांक असल_event;
	अचिन्हित दीर्घ buttons;
पूर्ण;

काष्ठा mousedev अणु
	पूर्णांक खोलो;
	काष्ठा input_handle handle;
	रुको_queue_head_t रुको;
	काष्ठा list_head client_list;
	spinlock_t client_lock; /* protects client_list */
	काष्ठा mutex mutex;
	काष्ठा device dev;
	काष्ठा cdev cdev;
	bool exist;

	काष्ठा list_head mixdev_node;
	bool खोलोed_by_mixdev;

	काष्ठा mousedev_hw_data packet;
	अचिन्हित पूर्णांक pkt_count;
	पूर्णांक old_x[4], old_y[4];
	पूर्णांक frac_dx, frac_dy;
	अचिन्हित दीर्घ touch;

	पूर्णांक (*खोलो_device)(काष्ठा mousedev *mousedev);
	व्योम (*बंद_device)(काष्ठा mousedev *mousedev);
पूर्ण;

क्रमागत mousedev_emul अणु
	MOUSEDEV_EMUL_PS2,
	MOUSEDEV_EMUL_IMPS,
	MOUSEDEV_EMUL_EXPS
पूर्ण;

काष्ठा mousedev_motion अणु
	पूर्णांक dx, dy, dz;
	अचिन्हित दीर्घ buttons;
पूर्ण;

#घोषणा PACKET_QUEUE_LEN	16
काष्ठा mousedev_client अणु
	काष्ठा fasync_काष्ठा *fasync;
	काष्ठा mousedev *mousedev;
	काष्ठा list_head node;

	काष्ठा mousedev_motion packets[PACKET_QUEUE_LEN];
	अचिन्हित पूर्णांक head, tail;
	spinlock_t packet_lock;
	पूर्णांक pos_x, pos_y;

	u8 ps2[6];
	अचिन्हित अक्षर पढ़ोy, buffer, bufsiz;
	अचिन्हित अक्षर imexseq, impsseq;
	क्रमागत mousedev_emul mode;
	अचिन्हित दीर्घ last_buttons;
पूर्ण;

#घोषणा MOUSEDEV_SEQ_LEN	6

अटल अचिन्हित अक्षर mousedev_imps_seq[] = अणु 0xf3, 200, 0xf3, 100, 0xf3, 80 पूर्ण;
अटल अचिन्हित अक्षर mousedev_imex_seq[] = अणु 0xf3, 200, 0xf3, 200, 0xf3, 80 पूर्ण;

अटल काष्ठा mousedev *mousedev_mix;
अटल LIST_HEAD(mousedev_mix_list);

#घोषणा fx(i)  (mousedev->old_x[(mousedev->pkt_count - (i)) & 03])
#घोषणा fy(i)  (mousedev->old_y[(mousedev->pkt_count - (i)) & 03])

अटल व्योम mousedev_touchpad_event(काष्ठा input_dev *dev,
				    काष्ठा mousedev *mousedev,
				    अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	पूर्णांक size, पंचांगp;
	क्रमागत अणु FRACTION_DENOM = 128 पूर्ण;

	चयन (code) अणु

	हाल ABS_X:

		fx(0) = value;
		अगर (mousedev->touch && mousedev->pkt_count >= 2) अणु
			size = input_असल_get_max(dev, ABS_X) -
					input_असल_get_min(dev, ABS_X);
			अगर (size == 0)
				size = 256 * 2;

			पंचांगp = ((value - fx(2)) * 256 * FRACTION_DENOM) / size;
			पंचांगp += mousedev->frac_dx;
			mousedev->packet.dx = पंचांगp / FRACTION_DENOM;
			mousedev->frac_dx =
				पंचांगp - mousedev->packet.dx * FRACTION_DENOM;
		पूर्ण
		अवरोध;

	हाल ABS_Y:
		fy(0) = value;
		अगर (mousedev->touch && mousedev->pkt_count >= 2) अणु
			/* use X size क्रम ABS_Y to keep the same scale */
			size = input_असल_get_max(dev, ABS_X) -
					input_असल_get_min(dev, ABS_X);
			अगर (size == 0)
				size = 256 * 2;

			पंचांगp = -((value - fy(2)) * 256 * FRACTION_DENOM) / size;
			पंचांगp += mousedev->frac_dy;
			mousedev->packet.dy = पंचांगp / FRACTION_DENOM;
			mousedev->frac_dy = पंचांगp -
				mousedev->packet.dy * FRACTION_DENOM;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mousedev_असल_event(काष्ठा input_dev *dev, काष्ठा mousedev *mousedev,
				अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	पूर्णांक min, max, size;

	चयन (code) अणु

	हाल ABS_X:
		min = input_असल_get_min(dev, ABS_X);
		max = input_असल_get_max(dev, ABS_X);

		size = max - min;
		अगर (size == 0)
			size = xres ? : 1;

		value = clamp(value, min, max);

		mousedev->packet.x = ((value - min) * xres) / size;
		mousedev->packet.असल_event = 1;
		अवरोध;

	हाल ABS_Y:
		min = input_असल_get_min(dev, ABS_Y);
		max = input_असल_get_max(dev, ABS_Y);

		size = max - min;
		अगर (size == 0)
			size = yres ? : 1;

		value = clamp(value, min, max);

		mousedev->packet.y = yres - ((value - min) * yres) / size;
		mousedev->packet.असल_event = 1;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mousedev_rel_event(काष्ठा mousedev *mousedev,
				अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	चयन (code) अणु
	हाल REL_X:
		mousedev->packet.dx += value;
		अवरोध;

	हाल REL_Y:
		mousedev->packet.dy -= value;
		अवरोध;

	हाल REL_WHEEL:
		mousedev->packet.dz -= value;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mousedev_key_event(काष्ठा mousedev *mousedev,
				अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	पूर्णांक index;

	चयन (code) अणु

	हाल BTN_TOUCH:
	हाल BTN_0:
	हाल BTN_LEFT:		index = 0; अवरोध;

	हाल BTN_STYLUS:
	हाल BTN_1:
	हाल BTN_RIGHT:		index = 1; अवरोध;

	हाल BTN_2:
	हाल BTN_FORWARD:
	हाल BTN_STYLUS2:
	हाल BTN_MIDDLE:	index = 2; अवरोध;

	हाल BTN_3:
	हाल BTN_BACK:
	हाल BTN_SIDE:		index = 3; अवरोध;

	हाल BTN_4:
	हाल BTN_EXTRA:		index = 4; अवरोध;

	शेष:		वापस;
	पूर्ण

	अगर (value) अणु
		set_bit(index, &mousedev->packet.buttons);
		set_bit(index, &mousedev_mix->packet.buttons);
	पूर्ण अन्यथा अणु
		clear_bit(index, &mousedev->packet.buttons);
		clear_bit(index, &mousedev_mix->packet.buttons);
	पूर्ण
पूर्ण

अटल व्योम mousedev_notअगरy_पढ़ोers(काष्ठा mousedev *mousedev,
				    काष्ठा mousedev_hw_data *packet)
अणु
	काष्ठा mousedev_client *client;
	काष्ठा mousedev_motion *p;
	अचिन्हित पूर्णांक new_head;
	पूर्णांक wake_पढ़ोers = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(client, &mousedev->client_list, node) अणु

		/* Just acquire the lock, पूर्णांकerrupts alपढ़ोy disabled */
		spin_lock(&client->packet_lock);

		p = &client->packets[client->head];
		अगर (client->पढ़ोy && p->buttons != mousedev->packet.buttons) अणु
			new_head = (client->head + 1) % PACKET_QUEUE_LEN;
			अगर (new_head != client->tail) अणु
				p = &client->packets[client->head = new_head];
				स_रखो(p, 0, माप(काष्ठा mousedev_motion));
			पूर्ण
		पूर्ण

		अगर (packet->असल_event) अणु
			p->dx += packet->x - client->pos_x;
			p->dy += packet->y - client->pos_y;
			client->pos_x = packet->x;
			client->pos_y = packet->y;
		पूर्ण

		client->pos_x += packet->dx;
		client->pos_x = clamp_val(client->pos_x, 0, xres);

		client->pos_y += packet->dy;
		client->pos_y = clamp_val(client->pos_y, 0, yres);

		p->dx += packet->dx;
		p->dy += packet->dy;
		p->dz += packet->dz;
		p->buttons = mousedev->packet.buttons;

		अगर (p->dx || p->dy || p->dz ||
		    p->buttons != client->last_buttons)
			client->पढ़ोy = 1;

		spin_unlock(&client->packet_lock);

		अगर (client->पढ़ोy) अणु
			समाप्त_fasync(&client->fasync, SIGIO, POLL_IN);
			wake_पढ़ोers = 1;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (wake_पढ़ोers)
		wake_up_पूर्णांकerruptible(&mousedev->रुको);
पूर्ण

अटल व्योम mousedev_touchpad_touch(काष्ठा mousedev *mousedev, पूर्णांक value)
अणु
	अगर (!value) अणु
		अगर (mousedev->touch &&
		    समय_beक्रमe(jअगरfies,
				mousedev->touch + msecs_to_jअगरfies(tap_समय))) अणु
			/*
			 * Toggle left button to emulate tap.
			 * We rely on the fact that mousedev_mix always has 0
			 * motion packet so we won't mess current position.
			 */
			set_bit(0, &mousedev->packet.buttons);
			set_bit(0, &mousedev_mix->packet.buttons);
			mousedev_notअगरy_पढ़ोers(mousedev, &mousedev_mix->packet);
			mousedev_notअगरy_पढ़ोers(mousedev_mix,
						&mousedev_mix->packet);
			clear_bit(0, &mousedev->packet.buttons);
			clear_bit(0, &mousedev_mix->packet.buttons);
		पूर्ण
		mousedev->touch = mousedev->pkt_count = 0;
		mousedev->frac_dx = 0;
		mousedev->frac_dy = 0;

	पूर्ण अन्यथा अगर (!mousedev->touch)
		mousedev->touch = jअगरfies;
पूर्ण

अटल व्योम mousedev_event(काष्ठा input_handle *handle,
			   अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा mousedev *mousedev = handle->निजी;

	चयन (type) अणु

	हाल EV_ABS:
		/* Ignore joysticks */
		अगर (test_bit(BTN_TRIGGER, handle->dev->keybit))
			वापस;

		अगर (test_bit(BTN_TOOL_FINGER, handle->dev->keybit))
			mousedev_touchpad_event(handle->dev,
						mousedev, code, value);
		अन्यथा
			mousedev_असल_event(handle->dev, mousedev, code, value);

		अवरोध;

	हाल EV_REL:
		mousedev_rel_event(mousedev, code, value);
		अवरोध;

	हाल EV_KEY:
		अगर (value != 2) अणु
			अगर (code == BTN_TOUCH &&
			    test_bit(BTN_TOOL_FINGER, handle->dev->keybit))
				mousedev_touchpad_touch(mousedev, value);
			अन्यथा
				mousedev_key_event(mousedev, code, value);
		पूर्ण
		अवरोध;

	हाल EV_SYN:
		अगर (code == SYN_REPORT) अणु
			अगर (mousedev->touch) अणु
				mousedev->pkt_count++;
				/*
				 * Input प्रणाली eats duplicate events,
				 * but we need all of them to करो correct
				 * averaging so apply present one क्रमward
				 */
				fx(0) = fx(1);
				fy(0) = fy(1);
			पूर्ण

			mousedev_notअगरy_पढ़ोers(mousedev, &mousedev->packet);
			mousedev_notअगरy_पढ़ोers(mousedev_mix, &mousedev->packet);

			mousedev->packet.dx = mousedev->packet.dy =
				mousedev->packet.dz = 0;
			mousedev->packet.असल_event = 0;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mousedev_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा mousedev_client *client = file->निजी_data;

	वापस fasync_helper(fd, file, on, &client->fasync);
पूर्ण

अटल व्योम mousedev_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा mousedev *mousedev = container_of(dev, काष्ठा mousedev, dev);

	input_put_device(mousedev->handle.dev);
	kमुक्त(mousedev);
पूर्ण

अटल पूर्णांक mousedev_खोलो_device(काष्ठा mousedev *mousedev)
अणु
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&mousedev->mutex);
	अगर (retval)
		वापस retval;

	अगर (!mousedev->exist)
		retval = -ENODEV;
	अन्यथा अगर (!mousedev->खोलो++) अणु
		retval = input_खोलो_device(&mousedev->handle);
		अगर (retval)
			mousedev->खोलो--;
	पूर्ण

	mutex_unlock(&mousedev->mutex);
	वापस retval;
पूर्ण

अटल व्योम mousedev_बंद_device(काष्ठा mousedev *mousedev)
अणु
	mutex_lock(&mousedev->mutex);

	अगर (mousedev->exist && !--mousedev->खोलो)
		input_बंद_device(&mousedev->handle);

	mutex_unlock(&mousedev->mutex);
पूर्ण

/*
 * Open all available devices so they can all be multiplexed in one.
 * stream. Note that this function is called with mousedev_mix->mutex
 * held.
 */
अटल पूर्णांक mixdev_खोलो_devices(काष्ठा mousedev *mixdev)
अणु
	पूर्णांक error;

	error = mutex_lock_पूर्णांकerruptible(&mixdev->mutex);
	अगर (error)
		वापस error;

	अगर (!mixdev->खोलो++) अणु
		काष्ठा mousedev *mousedev;

		list_क्रम_each_entry(mousedev, &mousedev_mix_list, mixdev_node) अणु
			अगर (!mousedev->खोलोed_by_mixdev) अणु
				अगर (mousedev_खोलो_device(mousedev))
					जारी;

				mousedev->खोलोed_by_mixdev = true;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&mixdev->mutex);
	वापस 0;
पूर्ण

/*
 * Close all devices that were खोलोed as part of multiplexed
 * device. Note that this function is called with mousedev_mix->mutex
 * held.
 */
अटल व्योम mixdev_बंद_devices(काष्ठा mousedev *mixdev)
अणु
	mutex_lock(&mixdev->mutex);

	अगर (!--mixdev->खोलो) अणु
		काष्ठा mousedev *mousedev;

		list_क्रम_each_entry(mousedev, &mousedev_mix_list, mixdev_node) अणु
			अगर (mousedev->खोलोed_by_mixdev) अणु
				mousedev->खोलोed_by_mixdev = false;
				mousedev_बंद_device(mousedev);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&mixdev->mutex);
पूर्ण


अटल व्योम mousedev_attach_client(काष्ठा mousedev *mousedev,
				   काष्ठा mousedev_client *client)
अणु
	spin_lock(&mousedev->client_lock);
	list_add_tail_rcu(&client->node, &mousedev->client_list);
	spin_unlock(&mousedev->client_lock);
पूर्ण

अटल व्योम mousedev_detach_client(काष्ठा mousedev *mousedev,
				   काष्ठा mousedev_client *client)
अणु
	spin_lock(&mousedev->client_lock);
	list_del_rcu(&client->node);
	spin_unlock(&mousedev->client_lock);
	synchronize_rcu();
पूर्ण

अटल पूर्णांक mousedev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mousedev_client *client = file->निजी_data;
	काष्ठा mousedev *mousedev = client->mousedev;

	mousedev_detach_client(mousedev, client);
	kमुक्त(client);

	mousedev->बंद_device(mousedev);

	वापस 0;
पूर्ण

अटल पूर्णांक mousedev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mousedev_client *client;
	काष्ठा mousedev *mousedev;
	पूर्णांक error;

#अगर_घोषित CONFIG_INPUT_MOUSEDEV_PSAUX
	अगर (imajor(inode) == MISC_MAJOR)
		mousedev = mousedev_mix;
	अन्यथा
#पूर्ण_अगर
		mousedev = container_of(inode->i_cdev, काष्ठा mousedev, cdev);

	client = kzalloc(माप(काष्ठा mousedev_client), GFP_KERNEL);
	अगर (!client)
		वापस -ENOMEM;

	spin_lock_init(&client->packet_lock);
	client->pos_x = xres / 2;
	client->pos_y = yres / 2;
	client->mousedev = mousedev;
	mousedev_attach_client(mousedev, client);

	error = mousedev->खोलो_device(mousedev);
	अगर (error)
		जाओ err_मुक्त_client;

	file->निजी_data = client;
	stream_खोलो(inode, file);

	वापस 0;

 err_मुक्त_client:
	mousedev_detach_client(mousedev, client);
	kमुक्त(client);
	वापस error;
पूर्ण

अटल व्योम mousedev_packet(काष्ठा mousedev_client *client, u8 *ps2_data)
अणु
	काष्ठा mousedev_motion *p = &client->packets[client->tail];
	s8 dx, dy, dz;

	dx = clamp_val(p->dx, -127, 127);
	p->dx -= dx;

	dy = clamp_val(p->dy, -127, 127);
	p->dy -= dy;

	ps2_data[0] = BIT(3);
	ps2_data[0] |= ((dx & BIT(7)) >> 3) | ((dy & BIT(7)) >> 2);
	ps2_data[0] |= p->buttons & 0x07;
	ps2_data[1] = dx;
	ps2_data[2] = dy;

	चयन (client->mode) अणु
	हाल MOUSEDEV_EMUL_EXPS:
		dz = clamp_val(p->dz, -7, 7);
		p->dz -= dz;

		ps2_data[3] = (dz & 0x0f) | ((p->buttons & 0x18) << 1);
		client->bufsiz = 4;
		अवरोध;

	हाल MOUSEDEV_EMUL_IMPS:
		dz = clamp_val(p->dz, -127, 127);
		p->dz -= dz;

		ps2_data[0] |= ((p->buttons & 0x10) >> 3) |
			       ((p->buttons & 0x08) >> 1);
		ps2_data[3] = dz;

		client->bufsiz = 4;
		अवरोध;

	हाल MOUSEDEV_EMUL_PS2:
	शेष:
		p->dz = 0;

		ps2_data[0] |= ((p->buttons & 0x10) >> 3) |
			       ((p->buttons & 0x08) >> 1);

		client->bufsiz = 3;
		अवरोध;
	पूर्ण

	अगर (!p->dx && !p->dy && !p->dz) अणु
		अगर (client->tail == client->head) अणु
			client->पढ़ोy = 0;
			client->last_buttons = p->buttons;
		पूर्ण अन्यथा
			client->tail = (client->tail + 1) % PACKET_QUEUE_LEN;
	पूर्ण
पूर्ण

अटल व्योम mousedev_generate_response(काष्ठा mousedev_client *client,
					पूर्णांक command)
अणु
	client->ps2[0] = 0xfa; /* ACK */

	चयन (command) अणु

	हाल 0xeb: /* Poll */
		mousedev_packet(client, &client->ps2[1]);
		client->bufsiz++; /* account क्रम leading ACK */
		अवरोध;

	हाल 0xf2: /* Get ID */
		चयन (client->mode) अणु
		हाल MOUSEDEV_EMUL_PS2:
			client->ps2[1] = 0;
			अवरोध;
		हाल MOUSEDEV_EMUL_IMPS:
			client->ps2[1] = 3;
			अवरोध;
		हाल MOUSEDEV_EMUL_EXPS:
			client->ps2[1] = 4;
			अवरोध;
		पूर्ण
		client->bufsiz = 2;
		अवरोध;

	हाल 0xe9: /* Get info */
		client->ps2[1] = 0x60; client->ps2[2] = 3; client->ps2[3] = 200;
		client->bufsiz = 4;
		अवरोध;

	हाल 0xff: /* Reset */
		client->impsseq = client->imexseq = 0;
		client->mode = MOUSEDEV_EMUL_PS2;
		client->ps2[1] = 0xaa; client->ps2[2] = 0x00;
		client->bufsiz = 3;
		अवरोध;

	शेष:
		client->bufsiz = 1;
		अवरोध;
	पूर्ण
	client->buffer = client->bufsiz;
पूर्ण

अटल sमाप_प्रकार mousedev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mousedev_client *client = file->निजी_data;
	अचिन्हित अक्षर c;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु

		अगर (get_user(c, buffer + i))
			वापस -EFAULT;

		spin_lock_irq(&client->packet_lock);

		अगर (c == mousedev_imex_seq[client->imexseq]) अणु
			अगर (++client->imexseq == MOUSEDEV_SEQ_LEN) अणु
				client->imexseq = 0;
				client->mode = MOUSEDEV_EMUL_EXPS;
			पूर्ण
		पूर्ण अन्यथा
			client->imexseq = 0;

		अगर (c == mousedev_imps_seq[client->impsseq]) अणु
			अगर (++client->impsseq == MOUSEDEV_SEQ_LEN) अणु
				client->impsseq = 0;
				client->mode = MOUSEDEV_EMUL_IMPS;
			पूर्ण
		पूर्ण अन्यथा
			client->impsseq = 0;

		mousedev_generate_response(client, c);

		spin_unlock_irq(&client->packet_lock);
		cond_resched();
	पूर्ण

	समाप्त_fasync(&client->fasync, SIGIO, POLL_IN);
	wake_up_पूर्णांकerruptible(&client->mousedev->रुको);

	वापस count;
पूर्ण

अटल sमाप_प्रकार mousedev_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mousedev_client *client = file->निजी_data;
	काष्ठा mousedev *mousedev = client->mousedev;
	u8 data[माप(client->ps2)];
	पूर्णांक retval = 0;

	अगर (!client->पढ़ोy && !client->buffer && mousedev->exist &&
	    (file->f_flags & O_NONBLOCK))
		वापस -EAGAIN;

	retval = रुको_event_पूर्णांकerruptible(mousedev->रुको,
			!mousedev->exist || client->पढ़ोy || client->buffer);
	अगर (retval)
		वापस retval;

	अगर (!mousedev->exist)
		वापस -ENODEV;

	spin_lock_irq(&client->packet_lock);

	अगर (!client->buffer && client->पढ़ोy) अणु
		mousedev_packet(client, client->ps2);
		client->buffer = client->bufsiz;
	पूर्ण

	अगर (count > client->buffer)
		count = client->buffer;

	स_नकल(data, client->ps2 + client->bufsiz - client->buffer, count);
	client->buffer -= count;

	spin_unlock_irq(&client->packet_lock);

	अगर (copy_to_user(buffer, data, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

/* No kernel lock - fine */
अटल __poll_t mousedev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा mousedev_client *client = file->निजी_data;
	काष्ठा mousedev *mousedev = client->mousedev;
	__poll_t mask;

	poll_रुको(file, &mousedev->रुको, रुको);

	mask = mousedev->exist ? EPOLLOUT | EPOLLWRNORM : EPOLLHUP | EPOLLERR;
	अगर (client->पढ़ोy || client->buffer)
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations mousedev_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= mousedev_पढ़ो,
	.ग_लिखो		= mousedev_ग_लिखो,
	.poll		= mousedev_poll,
	.खोलो		= mousedev_खोलो,
	.release	= mousedev_release,
	.fasync		= mousedev_fasync,
	.llseek		= noop_llseek,
पूर्ण;

/*
 * Mark device non-existent. This disables ग_लिखोs, ioctls and
 * prevents new users from खोलोing the device. Alपढ़ोy posted
 * blocking पढ़ोs will stay, however new ones will fail.
 */
अटल व्योम mousedev_mark_dead(काष्ठा mousedev *mousedev)
अणु
	mutex_lock(&mousedev->mutex);
	mousedev->exist = false;
	mutex_unlock(&mousedev->mutex);
पूर्ण

/*
 * Wake up users रुकोing क्रम IO so they can disconnect from
 * dead device.
 */
अटल व्योम mousedev_hangup(काष्ठा mousedev *mousedev)
अणु
	काष्ठा mousedev_client *client;

	spin_lock(&mousedev->client_lock);
	list_क्रम_each_entry(client, &mousedev->client_list, node)
		समाप्त_fasync(&client->fasync, SIGIO, POLL_HUP);
	spin_unlock(&mousedev->client_lock);

	wake_up_पूर्णांकerruptible(&mousedev->रुको);
पूर्ण

अटल व्योम mousedev_cleanup(काष्ठा mousedev *mousedev)
अणु
	काष्ठा input_handle *handle = &mousedev->handle;

	mousedev_mark_dead(mousedev);
	mousedev_hangup(mousedev);

	/* mousedev is marked dead so no one अन्यथा accesses mousedev->खोलो */
	अगर (mousedev->खोलो)
		input_बंद_device(handle);
पूर्ण

अटल पूर्णांक mousedev_reserve_minor(bool mixdev)
अणु
	पूर्णांक minor;

	अगर (mixdev) अणु
		minor = input_get_new_minor(MOUSEDEV_MIX, 1, false);
		अगर (minor < 0)
			pr_err("failed to reserve mixdev minor: %d\n", minor);
	पूर्ण अन्यथा अणु
		minor = input_get_new_minor(MOUSEDEV_MINOR_BASE,
					    MOUSEDEV_MINORS, true);
		अगर (minor < 0)
			pr_err("failed to reserve new minor: %d\n", minor);
	पूर्ण

	वापस minor;
पूर्ण

अटल काष्ठा mousedev *mousedev_create(काष्ठा input_dev *dev,
					काष्ठा input_handler *handler,
					bool mixdev)
अणु
	काष्ठा mousedev *mousedev;
	पूर्णांक minor;
	पूर्णांक error;

	minor = mousedev_reserve_minor(mixdev);
	अगर (minor < 0) अणु
		error = minor;
		जाओ err_out;
	पूर्ण

	mousedev = kzalloc(माप(काष्ठा mousedev), GFP_KERNEL);
	अगर (!mousedev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_minor;
	पूर्ण

	INIT_LIST_HEAD(&mousedev->client_list);
	INIT_LIST_HEAD(&mousedev->mixdev_node);
	spin_lock_init(&mousedev->client_lock);
	mutex_init(&mousedev->mutex);
	lockdep_set_subclass(&mousedev->mutex,
			     mixdev ? SINGLE_DEPTH_NESTING : 0);
	init_रुकोqueue_head(&mousedev->रुको);

	अगर (mixdev) अणु
		dev_set_name(&mousedev->dev, "mice");

		mousedev->खोलो_device = mixdev_खोलो_devices;
		mousedev->बंद_device = mixdev_बंद_devices;
	पूर्ण अन्यथा अणु
		पूर्णांक dev_no = minor;
		/* Normalize device number अगर it falls पूर्णांकo legacy range */
		अगर (dev_no < MOUSEDEV_MINOR_BASE + MOUSEDEV_MINORS)
			dev_no -= MOUSEDEV_MINOR_BASE;
		dev_set_name(&mousedev->dev, "mouse%d", dev_no);

		mousedev->खोलो_device = mousedev_खोलो_device;
		mousedev->बंद_device = mousedev_बंद_device;
	पूर्ण

	mousedev->exist = true;
	mousedev->handle.dev = input_get_device(dev);
	mousedev->handle.name = dev_name(&mousedev->dev);
	mousedev->handle.handler = handler;
	mousedev->handle.निजी = mousedev;

	mousedev->dev.class = &input_class;
	अगर (dev)
		mousedev->dev.parent = &dev->dev;
	mousedev->dev.devt = MKDEV(INPUT_MAJOR, minor);
	mousedev->dev.release = mousedev_मुक्त;
	device_initialize(&mousedev->dev);

	अगर (!mixdev) अणु
		error = input_रेजिस्टर_handle(&mousedev->handle);
		अगर (error)
			जाओ err_मुक्त_mousedev;
	पूर्ण

	cdev_init(&mousedev->cdev, &mousedev_fops);

	error = cdev_device_add(&mousedev->cdev, &mousedev->dev);
	अगर (error)
		जाओ err_cleanup_mousedev;

	वापस mousedev;

 err_cleanup_mousedev:
	mousedev_cleanup(mousedev);
	अगर (!mixdev)
		input_unरेजिस्टर_handle(&mousedev->handle);
 err_मुक्त_mousedev:
	put_device(&mousedev->dev);
 err_मुक्त_minor:
	input_मुक्त_minor(minor);
 err_out:
	वापस ERR_PTR(error);
पूर्ण

अटल व्योम mousedev_destroy(काष्ठा mousedev *mousedev)
अणु
	cdev_device_del(&mousedev->cdev, &mousedev->dev);
	mousedev_cleanup(mousedev);
	input_मुक्त_minor(MINOR(mousedev->dev.devt));
	अगर (mousedev != mousedev_mix)
		input_unरेजिस्टर_handle(&mousedev->handle);
	put_device(&mousedev->dev);
पूर्ण

अटल पूर्णांक mixdev_add_device(काष्ठा mousedev *mousedev)
अणु
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&mousedev_mix->mutex);
	अगर (retval)
		वापस retval;

	अगर (mousedev_mix->खोलो) अणु
		retval = mousedev_खोलो_device(mousedev);
		अगर (retval)
			जाओ out;

		mousedev->खोलोed_by_mixdev = true;
	पूर्ण

	get_device(&mousedev->dev);
	list_add_tail(&mousedev->mixdev_node, &mousedev_mix_list);

 out:
	mutex_unlock(&mousedev_mix->mutex);
	वापस retval;
पूर्ण

अटल व्योम mixdev_हटाओ_device(काष्ठा mousedev *mousedev)
अणु
	mutex_lock(&mousedev_mix->mutex);

	अगर (mousedev->खोलोed_by_mixdev) अणु
		mousedev->खोलोed_by_mixdev = false;
		mousedev_बंद_device(mousedev);
	पूर्ण

	list_del_init(&mousedev->mixdev_node);
	mutex_unlock(&mousedev_mix->mutex);

	put_device(&mousedev->dev);
पूर्ण

अटल पूर्णांक mousedev_connect(काष्ठा input_handler *handler,
			    काष्ठा input_dev *dev,
			    स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा mousedev *mousedev;
	पूर्णांक error;

	mousedev = mousedev_create(dev, handler, false);
	अगर (IS_ERR(mousedev))
		वापस PTR_ERR(mousedev);

	error = mixdev_add_device(mousedev);
	अगर (error) अणु
		mousedev_destroy(mousedev);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mousedev_disconnect(काष्ठा input_handle *handle)
अणु
	काष्ठा mousedev *mousedev = handle->निजी;

	mixdev_हटाओ_device(mousedev);
	mousedev_destroy(mousedev);
पूर्ण

अटल स्थिर काष्ठा input_device_id mousedev_ids[] = अणु
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT |
				INPUT_DEVICE_ID_MATCH_RELBIT,
		.evbit = अणु BIT_MASK(EV_KEY) | BIT_MASK(EV_REL) पूर्ण,
		.keybit = अणु [BIT_WORD(BTN_LEFT)] = BIT_MASK(BTN_LEFT) पूर्ण,
		.relbit = अणु BIT_MASK(REL_X) | BIT_MASK(REL_Y) पूर्ण,
	पूर्ण,	/* A mouse like device, at least one button,
		   two relative axes */
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_RELBIT,
		.evbit = अणु BIT_MASK(EV_KEY) | BIT_MASK(EV_REL) पूर्ण,
		.relbit = अणु BIT_MASK(REL_WHEEL) पूर्ण,
	पूर्ण,	/* A separate scrollwheel */
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = अणु BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) पूर्ण,
		.keybit = अणु [BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH) पूर्ण,
		.असलbit = अणु BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) पूर्ण,
	पूर्ण,	/* A tablet like device, at least touch detection,
		   two असलolute axes */
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = अणु BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) पूर्ण,
		.keybit = अणु [BIT_WORD(BTN_TOOL_FINGER)] =
				BIT_MASK(BTN_TOOL_FINGER) पूर्ण,
		.असलbit = अणु BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
				BIT_MASK(ABS_PRESSURE) |
				BIT_MASK(ABS_TOOL_WIDTH) पूर्ण,
	पूर्ण,	/* A touchpad */
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
			INPUT_DEVICE_ID_MATCH_KEYBIT |
			INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = अणु BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) पूर्ण,
		.keybit = अणु [BIT_WORD(BTN_LEFT)] = BIT_MASK(BTN_LEFT) पूर्ण,
		.असलbit = अणु BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) पूर्ण,
	पूर्ण,	/* Mouse-like device with असलolute X and Y but ordinary
		   clicks, like hp ILO2 High Perक्रमmance mouse */

	अणु पूर्ण,	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(input, mousedev_ids);

अटल काष्ठा input_handler mousedev_handler = अणु
	.event		= mousedev_event,
	.connect	= mousedev_connect,
	.disconnect	= mousedev_disconnect,
	.legacy_minors	= true,
	.minor		= MOUSEDEV_MINOR_BASE,
	.name		= "mousedev",
	.id_table	= mousedev_ids,
पूर्ण;

#अगर_घोषित CONFIG_INPUT_MOUSEDEV_PSAUX
#समावेश <linux/miscdevice.h>

अटल काष्ठा miscdevice psaux_mouse = अणु
	.minor	= PSMOUSE_MINOR,
	.name	= "psaux",
	.fops	= &mousedev_fops,
पूर्ण;

अटल bool psaux_रेजिस्टरed;

अटल व्योम __init mousedev_psaux_रेजिस्टर(व्योम)
अणु
	पूर्णांक error;

	error = misc_रेजिस्टर(&psaux_mouse);
	अगर (error)
		pr_warn("could not register psaux device, error: %d\n",
			   error);
	अन्यथा
		psaux_रेजिस्टरed = true;
पूर्ण

अटल व्योम __निकास mousedev_psaux_unरेजिस्टर(व्योम)
अणु
	अगर (psaux_रेजिस्टरed)
		misc_deरेजिस्टर(&psaux_mouse);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mousedev_psaux_रेजिस्टर(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम mousedev_psaux_unरेजिस्टर(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init mousedev_init(व्योम)
अणु
	पूर्णांक error;

	mousedev_mix = mousedev_create(शून्य, &mousedev_handler, true);
	अगर (IS_ERR(mousedev_mix))
		वापस PTR_ERR(mousedev_mix);

	error = input_रेजिस्टर_handler(&mousedev_handler);
	अगर (error) अणु
		mousedev_destroy(mousedev_mix);
		वापस error;
	पूर्ण

	mousedev_psaux_रेजिस्टर();

	pr_info("PS/2 mouse device common for all mice\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास mousedev_निकास(व्योम)
अणु
	mousedev_psaux_unरेजिस्टर();
	input_unरेजिस्टर_handler(&mousedev_handler);
	mousedev_destroy(mousedev_mix);
पूर्ण

module_init(mousedev_init);
module_निकास(mousedev_निकास);
