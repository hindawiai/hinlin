<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018-2020 Broadcom.
 */

#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>

#समावेश "bcm_vk.h"

/* TTYVK base offset is 0x30000 पूर्णांकo BAR1 */
#घोषणा BAR1_TTYVK_BASE_OFFSET	0x300000
/* Each TTYVK channel (TO or FROM) is 0x10000 */
#घोषणा BAR1_TTYVK_CHAN_OFFSET	0x100000
/* Each TTYVK channel has TO and FROM, hence the * 2 */
#घोषणा BAR1_TTYVK_BASE(index)	(BAR1_TTYVK_BASE_OFFSET + \
				 ((index) * BAR1_TTYVK_CHAN_OFFSET * 2))
/* TO TTYVK channel base comes beक्रमe FROM क्रम each index */
#घोषणा TO_TTYK_BASE(index)	BAR1_TTYVK_BASE(index)
#घोषणा FROM_TTYK_BASE(index)	(BAR1_TTYVK_BASE(index) + \
				 BAR1_TTYVK_CHAN_OFFSET)

काष्ठा bcm_vk_tty_chan अणु
	u32 reserved;
	u32 size;
	u32 wr;
	u32 rd;
	u32 *data;
पूर्ण;

#घोषणा VK_BAR_CHAN(v, सूची, e)	((v)->सूची##_offset \
				 + दुरत्व(काष्ठा bcm_vk_tty_chan, e))
#घोषणा VK_BAR_CHAN_SIZE(v, सूची)	VK_BAR_CHAN(v, सूची, size)
#घोषणा VK_BAR_CHAN_WR(v, सूची)		VK_BAR_CHAN(v, सूची, wr)
#घोषणा VK_BAR_CHAN_RD(v, सूची)		VK_BAR_CHAN(v, सूची, rd)
#घोषणा VK_BAR_CHAN_DATA(v, सूची, off)	(VK_BAR_CHAN(v, सूची, data) + (off))

#घोषणा VK_BAR0_REGSEG_TTY_DB_OFFSET	0x86c

/* Poll every 1/10 of second - temp hack till we use MSI पूर्णांकerrupt */
#घोषणा SERIAL_TIMER_VALUE (HZ / 10)

अटल व्योम bcm_vk_tty_poll(काष्ठा समयr_list *t)
अणु
	काष्ठा bcm_vk *vk = from_समयr(vk, t, serial_समयr);

	queue_work(vk->tty_wq_thपढ़ो, &vk->tty_wq_work);
	mod_समयr(&vk->serial_समयr, jअगरfies + SERIAL_TIMER_VALUE);
पूर्ण

irqवापस_t bcm_vk_tty_irqhandler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm_vk *vk = dev_id;

	queue_work(vk->tty_wq_thपढ़ो, &vk->tty_wq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bcm_vk_tty_wq_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bcm_vk *vk = container_of(work, काष्ठा bcm_vk, tty_wq_work);
	काष्ठा bcm_vk_tty *vktty;
	पूर्णांक card_status;
	पूर्णांक count;
	अचिन्हित अक्षर c;
	पूर्णांक i;
	पूर्णांक wr;

	card_status = vkपढ़ो32(vk, BAR_0, BAR_CARD_STATUS);
	अगर (BCM_VK_INTF_IS_DOWN(card_status))
		वापस;

	क्रम (i = 0; i < BCM_VK_NUM_TTY; i++) अणु
		count = 0;
		/* Check the card status that the tty channel is पढ़ोy */
		अगर ((card_status & BIT(i)) == 0)
			जारी;

		vktty = &vk->tty[i];

		/* Don't increment पढ़ो index अगर tty app is बंदd */
		अगर (!vktty->is_खोलोed)
			जारी;

		/* Fetch the wr offset in buffer from VK */
		wr = vkपढ़ो32(vk, BAR_1, VK_BAR_CHAN_WR(vktty, from));

		/* safe to ignore until bar पढ़ो gives proper size */
		अगर (vktty->from_size == 0)
			जारी;

		अगर (wr >= vktty->from_size) अणु
			dev_err(&vk->pdev->dev,
				"ERROR: wq handler ttyVK%d wr:0x%x > 0x%x\n",
				i, wr, vktty->from_size);
			/* Need to संकेत and बंद device in this हाल */
			जारी;
		पूर्ण

		/*
		 * Simple पढ़ो of circular buffer and
		 * insert पूर्णांकo tty flip buffer
		 */
		जबतक (vk->tty[i].rd != wr) अणु
			c = vkपढ़ो8(vk, BAR_1,
				    VK_BAR_CHAN_DATA(vktty, from, vktty->rd));
			vktty->rd++;
			अगर (vktty->rd >= vktty->from_size)
				vktty->rd = 0;
			tty_insert_flip_अक्षर(&vktty->port, c, TTY_NORMAL);
			count++;
		पूर्ण

		अगर (count) अणु
			tty_flip_buffer_push(&vktty->port);

			/* Update पढ़ो offset from shaकरोw रेजिस्टर to card */
			vkग_लिखो32(vk, vktty->rd, BAR_1,
				  VK_BAR_CHAN_RD(vktty, from));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_vk_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	पूर्णांक card_status;
	काष्ठा bcm_vk *vk;
	काष्ठा bcm_vk_tty *vktty;
	पूर्णांक index;

	/* initialize the poपूर्णांकer in हाल something fails */
	tty->driver_data = शून्य;

	vk = (काष्ठा bcm_vk *)dev_get_drvdata(tty->dev);
	index = tty->index;

	अगर (index >= BCM_VK_NUM_TTY)
		वापस -EINVAL;

	vktty = &vk->tty[index];

	vktty->pid = task_pid_nr(current);
	vktty->to_offset = TO_TTYK_BASE(index);
	vktty->from_offset = FROM_TTYK_BASE(index);

	/* Do not allow tty device to be खोलोed अगर tty on card not पढ़ोy */
	card_status = vkपढ़ो32(vk, BAR_0, BAR_CARD_STATUS);
	अगर (BCM_VK_INTF_IS_DOWN(card_status) || ((card_status & BIT(index)) == 0))
		वापस -EBUSY;

	/*
	 * Get shaकरोw रेजिस्टरs of the buffer sizes and the "to" ग_लिखो offset
	 * and "from" पढ़ो offset
	 */
	vktty->to_size = vkपढ़ो32(vk, BAR_1, VK_BAR_CHAN_SIZE(vktty, to));
	vktty->wr = vkपढ़ो32(vk, BAR_1,  VK_BAR_CHAN_WR(vktty, to));
	vktty->from_size = vkपढ़ो32(vk, BAR_1, VK_BAR_CHAN_SIZE(vktty, from));
	vktty->rd = vkपढ़ो32(vk, BAR_1,  VK_BAR_CHAN_RD(vktty, from));
	vktty->is_खोलोed = true;

	अगर (tty->count == 1 && !vktty->irq_enabled) अणु
		समयr_setup(&vk->serial_समयr, bcm_vk_tty_poll, 0);
		mod_समयr(&vk->serial_समयr, jअगरfies + SERIAL_TIMER_VALUE);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bcm_vk_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा bcm_vk *vk = dev_get_drvdata(tty->dev);

	अगर (tty->index >= BCM_VK_NUM_TTY)
		वापस;

	vk->tty[tty->index].is_खोलोed = false;

	अगर (tty->count == 1)
		del_समयr_sync(&vk->serial_समयr);
पूर्ण

अटल व्योम bcm_vk_tty_करोorbell(काष्ठा bcm_vk *vk, u32 db_val)
अणु
	vkग_लिखो32(vk, db_val, BAR_0,
		  VK_BAR0_REGSEG_DB_BASE + VK_BAR0_REGSEG_TTY_DB_OFFSET);
पूर्ण

अटल पूर्णांक bcm_vk_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty,
			    स्थिर अचिन्हित अक्षर *buffer,
			    पूर्णांक count)
अणु
	पूर्णांक index;
	काष्ठा bcm_vk *vk;
	काष्ठा bcm_vk_tty *vktty;
	पूर्णांक i;

	index = tty->index;
	vk = dev_get_drvdata(tty->dev);
	vktty = &vk->tty[index];

	/* Simple ग_लिखो each byte to circular buffer */
	क्रम (i = 0; i < count; i++) अणु
		vkग_लिखो8(vk, buffer[i], BAR_1,
			 VK_BAR_CHAN_DATA(vktty, to, vktty->wr));
		vktty->wr++;
		अगर (vktty->wr >= vktty->to_size)
			vktty->wr = 0;
	पूर्ण
	/* Update ग_लिखो offset from shaकरोw रेजिस्टर to card */
	vkग_लिखो32(vk, vktty->wr, BAR_1, VK_BAR_CHAN_WR(vktty, to));
	bcm_vk_tty_करोorbell(vk, 0);

	वापस count;
पूर्ण

अटल पूर्णांक bcm_vk_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा bcm_vk *vk = dev_get_drvdata(tty->dev);

	वापस vk->tty[tty->index].to_size - 1;
पूर्ण

अटल स्थिर काष्ठा tty_operations serial_ops = अणु
	.खोलो = bcm_vk_tty_खोलो,
	.बंद = bcm_vk_tty_बंद,
	.ग_लिखो = bcm_vk_tty_ग_लिखो,
	.ग_लिखो_room = bcm_vk_tty_ग_लिखो_room,
पूर्ण;

पूर्णांक bcm_vk_tty_init(काष्ठा bcm_vk *vk, अक्षर *name)
अणु
	पूर्णांक i;
	पूर्णांक err;
	काष्ठा tty_driver *tty_drv;
	काष्ठा device *dev = &vk->pdev->dev;

	tty_drv = tty_alloc_driver
				(BCM_VK_NUM_TTY,
				 TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV);
	अगर (IS_ERR(tty_drv))
		वापस PTR_ERR(tty_drv);

	/* Save काष्ठा tty_driver क्रम uninstalling the device */
	vk->tty_drv = tty_drv;

	/* initialize the tty driver */
	tty_drv->driver_name = KBUILD_MODNAME;
	tty_drv->name = kstrdup(name, GFP_KERNEL);
	अगर (!tty_drv->name) अणु
		err = -ENOMEM;
		जाओ err_put_tty_driver;
	पूर्ण
	tty_drv->type = TTY_DRIVER_TYPE_SERIAL;
	tty_drv->subtype = SERIAL_TYPE_NORMAL;
	tty_drv->init_termios = tty_std_termios;
	tty_set_operations(tty_drv, &serial_ops);

	/* रेजिस्टर the tty driver */
	err = tty_रेजिस्टर_driver(tty_drv);
	अगर (err) अणु
		dev_err(dev, "tty_register_driver failed\n");
		जाओ err_kमुक्त_tty_name;
	पूर्ण

	क्रम (i = 0; i < BCM_VK_NUM_TTY; i++) अणु
		काष्ठा device *tty_dev;

		tty_port_init(&vk->tty[i].port);
		tty_dev = tty_port_रेजिस्टर_device(&vk->tty[i].port, tty_drv,
						   i, dev);
		अगर (IS_ERR(tty_dev)) अणु
			err = PTR_ERR(tty_dev);
			जाओ unwind;
		पूर्ण
		dev_set_drvdata(tty_dev, vk);
		vk->tty[i].is_खोलोed = false;
	पूर्ण

	INIT_WORK(&vk->tty_wq_work, bcm_vk_tty_wq_handler);
	vk->tty_wq_thपढ़ो = create_singlethपढ़ो_workqueue("tty");
	अगर (!vk->tty_wq_thपढ़ो) अणु
		dev_err(dev, "Fail to create tty workqueue thread\n");
		err = -ENOMEM;
		जाओ unwind;
	पूर्ण
	वापस 0;

unwind:
	जबतक (--i >= 0)
		tty_port_unरेजिस्टर_device(&vk->tty[i].port, tty_drv, i);
	tty_unरेजिस्टर_driver(tty_drv);

err_kमुक्त_tty_name:
	kमुक्त(tty_drv->name);
	tty_drv->name = शून्य;

err_put_tty_driver:
	put_tty_driver(tty_drv);

	वापस err;
पूर्ण

व्योम bcm_vk_tty_निकास(काष्ठा bcm_vk *vk)
अणु
	पूर्णांक i;

	del_समयr_sync(&vk->serial_समयr);
	क्रम (i = 0; i < BCM_VK_NUM_TTY; ++i) अणु
		tty_port_unरेजिस्टर_device(&vk->tty[i].port,
					   vk->tty_drv,
					   i);
		tty_port_destroy(&vk->tty[i].port);
	पूर्ण
	tty_unरेजिस्टर_driver(vk->tty_drv);

	kमुक्त(vk->tty_drv->name);
	vk->tty_drv->name = शून्य;

	put_tty_driver(vk->tty_drv);
पूर्ण

व्योम bcm_vk_tty_terminate_tty_user(काष्ठा bcm_vk *vk)
अणु
	काष्ठा bcm_vk_tty *vktty;
	पूर्णांक i;

	क्रम (i = 0; i < BCM_VK_NUM_TTY; ++i) अणु
		vktty = &vk->tty[i];
		अगर (vktty->pid)
			समाप्त_pid(find_vpid(vktty->pid), SIGKILL, 1);
	पूर्ण
पूर्ण

व्योम bcm_vk_tty_wq_निकास(काष्ठा bcm_vk *vk)
अणु
	cancel_work_sync(&vk->tty_wq_work);
	destroy_workqueue(vk->tty_wq_thपढ़ो);
पूर्ण
