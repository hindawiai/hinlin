<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dvb_ca.c: generic DVB functions क्रम EN50221 CAM पूर्णांकerfaces
 *
 * Copyright (C) 2004 Andrew de Quincey
 *
 * Parts of this file were based on sources as follows:
 *
 * Copyright (C) 2003 Ralph Metzler <rjkm@metzlerbros.de>
 *
 * based on code:
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 */

#घोषणा pr_fmt(fmt) "dvb_ca_en50221: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/nospec.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kthपढ़ो.h>

#समावेश <media/dvb_ca_en50221.h>
#समावेश <media/dvb_ringbuffer.h>

अटल पूर्णांक dvb_ca_en50221_debug;

module_param_named(cam_debug, dvb_ca_en50221_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(cam_debug, "enable verbose debug messages");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (dvb_ca_en50221_debug)					\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt), __func__, ##arg);\
पूर्ण जबतक (0)

#घोषणा INIT_TIMEOUT_SECS 10

#घोषणा HOST_LINK_BUF_SIZE 0x200

#घोषणा RX_BUFFER_SIZE 65535

#घोषणा MAX_RX_PACKETS_PER_ITERATION 10

#घोषणा CTRLIF_DATA      0
#घोषणा CTRLIF_COMMAND   1
#घोषणा CTRLIF_STATUS    1
#घोषणा CTRLIF_SIZE_LOW  2
#घोषणा CTRLIF_SIZE_HIGH 3

#घोषणा CMDREG_HC        1	/* Host control */
#घोषणा CMDREG_SW        2	/* Size ग_लिखो */
#घोषणा CMDREG_SR        4	/* Size पढ़ो */
#घोषणा CMDREG_RS        8	/* Reset पूर्णांकerface */
#घोषणा CMDREG_FRIE   0x40	/* Enable FR पूर्णांकerrupt */
#घोषणा CMDREG_DAIE   0x80	/* Enable DA पूर्णांकerrupt */
#घोषणा IRQEN (CMDREG_DAIE)

#घोषणा STATUSREG_RE     1	/* पढ़ो error */
#घोषणा STATUSREG_WE     2	/* ग_लिखो error */
#घोषणा STATUSREG_FR  0x40	/* module मुक्त */
#घोषणा STATUSREG_DA  0x80	/* data available */

#घोषणा DVB_CA_SLOTSTATE_NONE           0
#घोषणा DVB_CA_SLOTSTATE_UNINITIALISED  1
#घोषणा DVB_CA_SLOTSTATE_RUNNING        2
#घोषणा DVB_CA_SLOTSTATE_INVALID        3
#घोषणा DVB_CA_SLOTSTATE_WAITREADY      4
#घोषणा DVB_CA_SLOTSTATE_VALIDATE       5
#घोषणा DVB_CA_SLOTSTATE_WAITFR         6
#घोषणा DVB_CA_SLOTSTATE_LINKINIT       7

/* Inक्रमmation on a CA slot */
काष्ठा dvb_ca_slot अणु
	/* current state of the CAM */
	पूर्णांक slot_state;

	/* mutex used क्रम serializing access to one CI slot */
	काष्ठा mutex slot_lock;

	/* Number of CAMCHANGES that have occurred since last processing */
	atomic_t camchange_count;

	/* Type of last CAMCHANGE */
	पूर्णांक camchange_type;

	/* base address of CAM config */
	u32 config_base;

	/* value to ग_लिखो पूर्णांकo Config Control रेजिस्टर */
	u8 config_option;

	/* अगर 1, the CAM supports DA IRQs */
	u8 da_irq_supported:1;

	/* size of the buffer to use when talking to the CAM */
	पूर्णांक link_buf_size;

	/* buffer क्रम incoming packets */
	काष्ठा dvb_ringbuffer rx_buffer;

	/* समयr used during various states of the slot */
	अचिन्हित दीर्घ समयout;
पूर्ण;

/* Private CA-पूर्णांकerface inक्रमmation */
काष्ठा dvb_ca_निजी अणु
	काष्ठा kref refcount;

	/* poपूर्णांकer back to the खुला data काष्ठाure */
	काष्ठा dvb_ca_en50221 *pub;

	/* the DVB device */
	काष्ठा dvb_device *dvbdev;

	/* Flags describing the पूर्णांकerface (DVB_CA_FLAG_*) */
	u32 flags;

	/* number of slots supported by this CA पूर्णांकerface */
	अचिन्हित पूर्णांक slot_count;

	/* inक्रमmation on each slot */
	काष्ठा dvb_ca_slot *slot_info;

	/* रुको queues क्रम पढ़ो() and ग_लिखो() operations */
	रुको_queue_head_t रुको_queue;

	/* PID of the monitoring thपढ़ो */
	काष्ठा task_काष्ठा *thपढ़ो;

	/* Flag indicating अगर the CA device is खोलो */
	अचिन्हित पूर्णांक खोलो:1;

	/* Flag indicating the thपढ़ो should wake up now */
	अचिन्हित पूर्णांक wakeup:1;

	/* Delay the मुख्य thपढ़ो should use */
	अचिन्हित दीर्घ delay;

	/*
	 * Slot to start looking क्रम data to पढ़ो from in the next user-space
	 * पढ़ो operation
	 */
	पूर्णांक next_पढ़ो_slot;

	/* mutex serializing ioctls */
	काष्ठा mutex ioctl_mutex;
पूर्ण;

अटल व्योम dvb_ca_निजी_मुक्त(काष्ठा dvb_ca_निजी *ca)
अणु
	अचिन्हित पूर्णांक i;

	dvb_मुक्त_device(ca->dvbdev);
	क्रम (i = 0; i < ca->slot_count; i++)
		vमुक्त(ca->slot_info[i].rx_buffer.data);

	kमुक्त(ca->slot_info);
	kमुक्त(ca);
पूर्ण

अटल व्योम dvb_ca_निजी_release(काष्ठा kref *ref)
अणु
	काष्ठा dvb_ca_निजी *ca;

	ca = container_of(ref, काष्ठा dvb_ca_निजी, refcount);
	dvb_ca_निजी_मुक्त(ca);
पूर्ण

अटल व्योम dvb_ca_निजी_get(काष्ठा dvb_ca_निजी *ca)
अणु
	kref_get(&ca->refcount);
पूर्ण

अटल व्योम dvb_ca_निजी_put(काष्ठा dvb_ca_निजी *ca)
अणु
	kref_put(&ca->refcount, dvb_ca_निजी_release);
पूर्ण

अटल व्योम dvb_ca_en50221_thपढ़ो_wakeup(काष्ठा dvb_ca_निजी *ca);
अटल पूर्णांक dvb_ca_en50221_पढ़ो_data(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot,
				    u8 *ebuf, पूर्णांक ecount);
अटल पूर्णांक dvb_ca_en50221_ग_लिखो_data(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot,
				     u8 *ebuf, पूर्णांक ecount);

/**
 * findstr - Safely find needle in haystack.
 *
 * @haystack: Buffer to look in.
 * @hlen: Number of bytes in haystack.
 * @needle: Buffer to find.
 * @nlen: Number of bytes in needle.
 * वापस: Poपूर्णांकer पूर्णांकo haystack needle was found at, or शून्य अगर not found.
 */
अटल अक्षर *findstr(अक्षर *haystack, पूर्णांक hlen, अक्षर *needle, पूर्णांक nlen)
अणु
	पूर्णांक i;

	अगर (hlen < nlen)
		वापस शून्य;

	क्रम (i = 0; i <= hlen - nlen; i++) अणु
		अगर (!म_भेदन(haystack + i, needle, nlen))
			वापस haystack + i;
	पूर्ण

	वापस शून्य;
पूर्ण

/* ************************************************************************** */
/* EN50221 physical पूर्णांकerface functions */

/*
 * dvb_ca_en50221_check_camstatus - Check CAM status.
 */
अटल पूर्णांक dvb_ca_en50221_check_camstatus(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];
	पूर्णांक slot_status;
	पूर्णांक cam_present_now;
	पूर्णांक cam_changed;

	/* IRQ mode */
	अगर (ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE)
		वापस (atomic_पढ़ो(&sl->camchange_count) != 0);

	/* poll mode */
	slot_status = ca->pub->poll_slot_status(ca->pub, slot, ca->खोलो);

	cam_present_now = (slot_status & DVB_CA_EN50221_POLL_CAM_PRESENT) ? 1 : 0;
	cam_changed = (slot_status & DVB_CA_EN50221_POLL_CAM_CHANGED) ? 1 : 0;
	अगर (!cam_changed) अणु
		पूर्णांक cam_present_old = (sl->slot_state != DVB_CA_SLOTSTATE_NONE);

		cam_changed = (cam_present_now != cam_present_old);
	पूर्ण

	अगर (cam_changed) अणु
		अगर (!cam_present_now)
			sl->camchange_type = DVB_CA_EN50221_CAMCHANGE_REMOVED;
		अन्यथा
			sl->camchange_type = DVB_CA_EN50221_CAMCHANGE_INSERTED;
		atomic_set(&sl->camchange_count, 1);
	पूर्ण अन्यथा अणु
		अगर ((sl->slot_state == DVB_CA_SLOTSTATE_WAITREADY) &&
		    (slot_status & DVB_CA_EN50221_POLL_CAM_READY)) अणु
			/* move to validate state अगर reset is completed */
			sl->slot_state = DVB_CA_SLOTSTATE_VALIDATE;
		पूर्ण
	पूर्ण

	वापस cam_changed;
पूर्ण

/**
 * dvb_ca_en50221_रुको_अगर_status - Wait क्रम flags to become set on the STATUS
 *	 रेजिस्टर on a CAM पूर्णांकerface, checking क्रम errors and समयout.
 *
 * @ca: CA instance.
 * @slot: Slot on पूर्णांकerface.
 * @रुकोक्रम: Flags to रुको क्रम.
 * @समयout_hz: Timeout in milliseconds.
 *
 * वापस: 0 on success, nonzero on error.
 */
अटल पूर्णांक dvb_ca_en50221_रुको_अगर_status(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot,
					 u8 रुकोक्रम, पूर्णांक समयout_hz)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ start;

	dprपूर्णांकk("%s\n", __func__);

	/* loop until समयout elapsed */
	start = jअगरfies;
	समयout = jअगरfies + समयout_hz;
	जबतक (1) अणु
		पूर्णांक res;

		/* पढ़ो the status and check क्रम error */
		res = ca->pub->पढ़ो_cam_control(ca->pub, slot, CTRLIF_STATUS);
		अगर (res < 0)
			वापस -EIO;

		/* अगर we got the flags, it was successful! */
		अगर (res & रुकोक्रम) अणु
			dprपूर्णांकk("%s succeeded timeout:%lu\n",
				__func__, jअगरfies - start);
			वापस 0;
		पूर्ण

		/* check क्रम समयout */
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;

		/* रुको क्रम a bit */
		usleep_range(1000, 1100);
	पूर्ण

	dprपूर्णांकk("%s failed timeout:%lu\n", __func__, jअगरfies - start);

	/* अगर we get here, we've समयd out */
	वापस -ETIMEDOUT;
पूर्ण

/**
 * dvb_ca_en50221_link_init - Initialise the link layer connection to a CAM.
 *
 * @ca: CA instance.
 * @slot: Slot id.
 *
 * वापस: 0 on success, nonzero on failure.
 */
अटल पूर्णांक dvb_ca_en50221_link_init(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];
	पूर्णांक ret;
	पूर्णांक buf_size;
	u8 buf[2];

	dprपूर्णांकk("%s\n", __func__);

	/* we'll be determining these during this function */
	sl->da_irq_supported = 0;

	/*
	 * set the host link buffer size temporarily. it will be overwritten
	 * with the real negotiated size later.
	 */
	sl->link_buf_size = 2;

	/* पढ़ो the buffer size from the CAM */
	ret = ca->pub->ग_लिखो_cam_control(ca->pub, slot, CTRLIF_COMMAND,
					 IRQEN | CMDREG_SR);
	अगर (ret)
		वापस ret;
	ret = dvb_ca_en50221_रुको_अगर_status(ca, slot, STATUSREG_DA, HZ);
	अगर (ret)
		वापस ret;
	ret = dvb_ca_en50221_पढ़ो_data(ca, slot, buf, 2);
	अगर (ret != 2)
		वापस -EIO;
	ret = ca->pub->ग_लिखो_cam_control(ca->pub, slot, CTRLIF_COMMAND, IRQEN);
	अगर (ret)
		वापस ret;

	/*
	 * store it, and choose the minimum of our buffer and the CAM's buffer
	 * size
	 */
	buf_size = (buf[0] << 8) | buf[1];
	अगर (buf_size > HOST_LINK_BUF_SIZE)
		buf_size = HOST_LINK_BUF_SIZE;
	sl->link_buf_size = buf_size;
	buf[0] = buf_size >> 8;
	buf[1] = buf_size & 0xff;
	dprपूर्णांकk("Chosen link buffer size of %i\n", buf_size);

	/* ग_लिखो the buffer size to the CAM */
	ret = ca->pub->ग_लिखो_cam_control(ca->pub, slot, CTRLIF_COMMAND,
					 IRQEN | CMDREG_SW);
	अगर (ret)
		वापस ret;
	ret = dvb_ca_en50221_रुको_अगर_status(ca, slot, STATUSREG_FR, HZ / 10);
	अगर (ret)
		वापस ret;
	ret = dvb_ca_en50221_ग_लिखो_data(ca, slot, buf, 2);
	अगर (ret != 2)
		वापस -EIO;
	ret = ca->pub->ग_लिखो_cam_control(ca->pub, slot, CTRLIF_COMMAND, IRQEN);
	अगर (ret)
		वापस ret;

	/* success */
	वापस 0;
पूर्ण

/**
 * dvb_ca_en50221_पढ़ो_tuple - Read a tuple from attribute memory.
 *
 * @ca: CA instance.
 * @slot: Slot id.
 * @address: Address to पढ़ो from. Updated.
 * @tuple_type: Tuple id byte. Updated.
 * @tuple_length: Tuple length. Updated.
 * @tuple: Dest buffer क्रम tuple (must be 256 bytes). Updated.
 *
 * वापस: 0 on success, nonzero on error.
 */
अटल पूर्णांक dvb_ca_en50221_पढ़ो_tuple(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot,
				     पूर्णांक *address, पूर्णांक *tuple_type,
				     पूर्णांक *tuple_length, u8 *tuple)
अणु
	पूर्णांक i;
	पूर्णांक _tuple_type;
	पूर्णांक _tuple_length;
	पूर्णांक _address = *address;

	/* grab the next tuple length and type */
	_tuple_type = ca->pub->पढ़ो_attribute_mem(ca->pub, slot, _address);
	अगर (_tuple_type < 0)
		वापस _tuple_type;
	अगर (_tuple_type == 0xff) अणु
		dprपूर्णांकk("END OF CHAIN TUPLE type:0x%x\n", _tuple_type);
		*address += 2;
		*tuple_type = _tuple_type;
		*tuple_length = 0;
		वापस 0;
	पूर्ण
	_tuple_length = ca->pub->पढ़ो_attribute_mem(ca->pub, slot,
						    _address + 2);
	अगर (_tuple_length < 0)
		वापस _tuple_length;
	_address += 4;

	dprपूर्णांकk("TUPLE type:0x%x length:%i\n", _tuple_type, _tuple_length);

	/* पढ़ो in the whole tuple */
	क्रम (i = 0; i < _tuple_length; i++) अणु
		tuple[i] = ca->pub->पढ़ो_attribute_mem(ca->pub, slot,
						       _address + (i * 2));
		dprपूर्णांकk("  0x%02x: 0x%02x %c\n",
			i, tuple[i] & 0xff,
			((tuple[i] > 31) && (tuple[i] < 127)) ? tuple[i] : '.');
	पूर्ण
	_address += (_tuple_length * 2);

	/* success */
	*tuple_type = _tuple_type;
	*tuple_length = _tuple_length;
	*address = _address;
	वापस 0;
पूर्ण

/**
 * dvb_ca_en50221_parse_attributes - Parse attribute memory of a CAM module,
 *	extracting Config रेजिस्टर, and checking it is a DVB CAM module.
 *
 * @ca: CA instance.
 * @slot: Slot id.
 *
 * वापस: 0 on success, <0 on failure.
 */
अटल पूर्णांक dvb_ca_en50221_parse_attributes(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_ca_slot *sl;
	पूर्णांक address = 0;
	पूर्णांक tuple_length;
	पूर्णांक tuple_type;
	u8 tuple[257];
	अक्षर *dvb_str;
	पूर्णांक rasz;
	पूर्णांक status;
	पूर्णांक got_cftableentry = 0;
	पूर्णांक end_chain = 0;
	पूर्णांक i;
	u16 manfid = 0;
	u16 devid = 0;

	/* CISTPL_DEVICE_0A */
	status = dvb_ca_en50221_पढ़ो_tuple(ca, slot, &address, &tuple_type,
					   &tuple_length, tuple);
	अगर (status < 0)
		वापस status;
	अगर (tuple_type != 0x1D)
		वापस -EINVAL;

	/* CISTPL_DEVICE_0C */
	status = dvb_ca_en50221_पढ़ो_tuple(ca, slot, &address, &tuple_type,
					   &tuple_length, tuple);
	अगर (status < 0)
		वापस status;
	अगर (tuple_type != 0x1C)
		वापस -EINVAL;

	/* CISTPL_VERS_1 */
	status = dvb_ca_en50221_पढ़ो_tuple(ca, slot, &address, &tuple_type,
					   &tuple_length, tuple);
	अगर (status < 0)
		वापस status;
	अगर (tuple_type != 0x15)
		वापस -EINVAL;

	/* CISTPL_MANFID */
	status = dvb_ca_en50221_पढ़ो_tuple(ca, slot, &address, &tuple_type,
					   &tuple_length, tuple);
	अगर (status < 0)
		वापस status;
	अगर (tuple_type != 0x20)
		वापस -EINVAL;
	अगर (tuple_length != 4)
		वापस -EINVAL;
	manfid = (tuple[1] << 8) | tuple[0];
	devid = (tuple[3] << 8) | tuple[2];

	/* CISTPL_CONFIG */
	status = dvb_ca_en50221_पढ़ो_tuple(ca, slot, &address, &tuple_type,
					   &tuple_length, tuple);
	अगर (status < 0)
		वापस status;
	अगर (tuple_type != 0x1A)
		वापस -EINVAL;
	अगर (tuple_length < 3)
		वापस -EINVAL;

	/* extract the configbase */
	rasz = tuple[0] & 3;
	अगर (tuple_length < (3 + rasz + 14))
		वापस -EINVAL;
	sl = &ca->slot_info[slot];
	sl->config_base = 0;
	क्रम (i = 0; i < rasz + 1; i++)
		sl->config_base |= (tuple[2 + i] << (8 * i));

	/* check it contains the correct DVB string */
	dvb_str = findstr((अक्षर *)tuple, tuple_length, "DVB_CI_V", 8);
	अगर (!dvb_str)
		वापस -EINVAL;
	अगर (tuple_length < ((dvb_str - (अक्षर *)tuple) + 12))
		वापस -EINVAL;

	/* is it a version we support? */
	अगर (म_भेदन(dvb_str + 8, "1.00", 4)) अणु
		pr_err("dvb_ca adapter %d: Unsupported DVB CAM module version %c%c%c%c\n",
		       ca->dvbdev->adapter->num, dvb_str[8], dvb_str[9],
		       dvb_str[10], dvb_str[11]);
		वापस -EINVAL;
	पूर्ण

	/* process the CFTABLE_ENTRY tuples, and any after those */
	जबतक ((!end_chain) && (address < 0x1000)) अणु
		status = dvb_ca_en50221_पढ़ो_tuple(ca, slot, &address,
						   &tuple_type, &tuple_length,
						   tuple);
		अगर (status < 0)
			वापस status;
		चयन (tuple_type) अणु
		हाल 0x1B:	/* CISTPL_CFTABLE_ENTRY */
			अगर (tuple_length < (2 + 11 + 17))
				अवरोध;

			/* अगर we've alपढ़ोy parsed one, just use it */
			अगर (got_cftableentry)
				अवरोध;

			/* get the config option */
			sl->config_option = tuple[0] & 0x3f;

			/* OK, check it contains the correct strings */
			अगर (!findstr((अक्षर *)tuple, tuple_length,
				     "DVB_HOST", 8) ||
			    !findstr((अक्षर *)tuple, tuple_length,
				     "DVB_CI_MODULE", 13))
				अवरोध;

			got_cftableentry = 1;
			अवरोध;

		हाल 0x14:	/* CISTPL_NO_LINK */
			अवरोध;

		हाल 0xFF:	/* CISTPL_END */
			end_chain = 1;
			अवरोध;

		शेष:	/* Unknown tuple type - just skip this tuple */
			dprपूर्णांकk("dvb_ca: Skipping unknown tuple type:0x%x length:0x%x\n",
				tuple_type, tuple_length);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((address > 0x1000) || (!got_cftableentry))
		वापस -EINVAL;

	dprपूर्णांकk("Valid DVB CAM detected MANID:%x DEVID:%x CONFIGBASE:0x%x CONFIGOPTION:0x%x\n",
		manfid, devid, sl->config_base, sl->config_option);

	/* success! */
	वापस 0;
पूर्ण

/**
 * dvb_ca_en50221_set_configoption - Set CAM's configoption correctly.
 *
 * @ca: CA instance.
 * @slot: Slot containing the CAM.
 */
अटल पूर्णांक dvb_ca_en50221_set_configoption(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];
	पूर्णांक configoption;

	dprपूर्णांकk("%s\n", __func__);

	/* set the config option */
	ca->pub->ग_लिखो_attribute_mem(ca->pub, slot, sl->config_base,
				     sl->config_option);

	/* check it */
	configoption = ca->pub->पढ़ो_attribute_mem(ca->pub, slot,
						   sl->config_base);
	dprपूर्णांकk("Set configoption 0x%x, read configoption 0x%x\n",
		sl->config_option, configoption & 0x3f);

	/* fine! */
	वापस 0;
पूर्ण

/**
 * dvb_ca_en50221_पढ़ो_data - This function talks to an EN50221 CAM control
 *	पूर्णांकerface. It पढ़ोs a buffer of data from the CAM. The data can either
 *	be stored in a supplied buffer, or स्वतःmatically be added to the slot's
 *	rx_buffer.
 *
 * @ca: CA instance.
 * @slot: Slot to पढ़ो from.
 * @ebuf: If non-शून्य, the data will be written to this buffer. If शून्य,
 *	  the data will be added पूर्णांकo the buffering प्रणाली as a normal
 *	  fragment.
 * @ecount: Size of ebuf. Ignored अगर ebuf is शून्य.
 *
 * वापस: Number of bytes पढ़ो, or < 0 on error
 */
अटल पूर्णांक dvb_ca_en50221_पढ़ो_data(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot,
				    u8 *ebuf, पूर्णांक ecount)
अणु
	काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];
	पूर्णांक bytes_पढ़ो;
	पूर्णांक status;
	u8 buf[HOST_LINK_BUF_SIZE];
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	/* check अगर we have space क्रम a link buf in the rx_buffer */
	अगर (!ebuf) अणु
		पूर्णांक buf_मुक्त;

		अगर (!sl->rx_buffer.data) अणु
			status = -EIO;
			जाओ निकास;
		पूर्ण
		buf_मुक्त = dvb_ringbuffer_मुक्त(&sl->rx_buffer);

		अगर (buf_मुक्त < (sl->link_buf_size +
				DVB_RINGBUFFER_PKTHDRSIZE)) अणु
			status = -EAGAIN;
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (ca->pub->पढ़ो_data &&
	    (sl->slot_state != DVB_CA_SLOTSTATE_LINKINIT)) अणु
		अगर (!ebuf)
			status = ca->pub->पढ़ो_data(ca->pub, slot, buf,
						    माप(buf));
		अन्यथा
			status = ca->pub->पढ़ो_data(ca->pub, slot, buf, ecount);
		अगर (status < 0)
			वापस status;
		bytes_पढ़ो =  status;
		अगर (status == 0)
			जाओ निकास;
	पूर्ण अन्यथा अणु
		/* check अगर there is data available */
		status = ca->pub->पढ़ो_cam_control(ca->pub, slot,
						   CTRLIF_STATUS);
		अगर (status < 0)
			जाओ निकास;
		अगर (!(status & STATUSREG_DA)) अणु
			/* no data */
			status = 0;
			जाओ निकास;
		पूर्ण

		/* पढ़ो the amount of data */
		status = ca->pub->पढ़ो_cam_control(ca->pub, slot,
						   CTRLIF_SIZE_HIGH);
		अगर (status < 0)
			जाओ निकास;
		bytes_पढ़ो = status << 8;
		status = ca->pub->पढ़ो_cam_control(ca->pub, slot,
						   CTRLIF_SIZE_LOW);
		अगर (status < 0)
			जाओ निकास;
		bytes_पढ़ो |= status;

		/* check it will fit */
		अगर (!ebuf) अणु
			अगर (bytes_पढ़ो > sl->link_buf_size) अणु
				pr_err("dvb_ca adapter %d: CAM tried to send a buffer larger than the link buffer size (%i > %i)!\n",
				       ca->dvbdev->adapter->num, bytes_पढ़ो,
				       sl->link_buf_size);
				sl->slot_state = DVB_CA_SLOTSTATE_LINKINIT;
				status = -EIO;
				जाओ निकास;
			पूर्ण
			अगर (bytes_पढ़ो < 2) अणु
				pr_err("dvb_ca adapter %d: CAM sent a buffer that was less than 2 bytes!\n",
				       ca->dvbdev->adapter->num);
				sl->slot_state = DVB_CA_SLOTSTATE_LINKINIT;
				status = -EIO;
				जाओ निकास;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bytes_पढ़ो > ecount) अणु
				pr_err("dvb_ca adapter %d: CAM tried to send a buffer larger than the ecount size!\n",
				       ca->dvbdev->adapter->num);
				status = -EIO;
				जाओ निकास;
			पूर्ण
		पूर्ण

		/* fill the buffer */
		क्रम (i = 0; i < bytes_पढ़ो; i++) अणु
			/* पढ़ो byte and check */
			status = ca->pub->पढ़ो_cam_control(ca->pub, slot,
							   CTRLIF_DATA);
			अगर (status < 0)
				जाओ निकास;

			/* OK, store it in the buffer */
			buf[i] = status;
		पूर्ण

		/* check क्रम पढ़ो error (RE should now be 0) */
		status = ca->pub->पढ़ो_cam_control(ca->pub, slot,
						   CTRLIF_STATUS);
		अगर (status < 0)
			जाओ निकास;
		अगर (status & STATUSREG_RE) अणु
			sl->slot_state = DVB_CA_SLOTSTATE_LINKINIT;
			status = -EIO;
			जाओ निकास;
		पूर्ण
	पूर्ण

	/*
	 * OK, add it to the receive buffer, or copy पूर्णांकo बाह्यal buffer अगर
	 * supplied
	 */
	अगर (!ebuf) अणु
		अगर (!sl->rx_buffer.data) अणु
			status = -EIO;
			जाओ निकास;
		पूर्ण
		dvb_ringbuffer_pkt_ग_लिखो(&sl->rx_buffer, buf, bytes_पढ़ो);
	पूर्ण अन्यथा अणु
		स_नकल(ebuf, buf, bytes_पढ़ो);
	पूर्ण

	dprपूर्णांकk("Received CA packet for slot %i connection id 0x%x last_frag:%i size:0x%x\n", slot,
		buf[0], (buf[1] & 0x80) == 0, bytes_पढ़ो);

	/* wake up पढ़ोers when a last_fragment is received */
	अगर ((buf[1] & 0x80) == 0x00)
		wake_up_पूर्णांकerruptible(&ca->रुको_queue);

	status = bytes_पढ़ो;

निकास:
	वापस status;
पूर्ण

/**
 * dvb_ca_en50221_ग_लिखो_data - This function talks to an EN50221 CAM control
 *				पूर्णांकerface. It ग_लिखोs a buffer of data to a CAM.
 *
 * @ca: CA instance.
 * @slot: Slot to ग_लिखो to.
 * @buf: The data in this buffer is treated as a complete link-level packet to
 *	 be written.
 * @bytes_ग_लिखो: Size of ebuf.
 *
 * वापस: Number of bytes written, or < 0 on error.
 */
अटल पूर्णांक dvb_ca_en50221_ग_लिखो_data(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot,
				     u8 *buf, पूर्णांक bytes_ग_लिखो)
अणु
	काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];
	पूर्णांक status;
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	/* sanity check */
	अगर (bytes_ग_लिखो > sl->link_buf_size)
		वापस -EINVAL;

	अगर (ca->pub->ग_लिखो_data &&
	    (sl->slot_state != DVB_CA_SLOTSTATE_LINKINIT))
		वापस ca->pub->ग_लिखो_data(ca->pub, slot, buf, bytes_ग_लिखो);

	/*
	 * it is possible we are dealing with a single buffer implementation,
	 * thus अगर there is data available क्रम पढ़ो or अगर there is even a पढ़ो
	 * alपढ़ोy in progress, we करो nothing but awake the kernel thपढ़ो to
	 * process the data अगर necessary.
	 */
	status = ca->pub->पढ़ो_cam_control(ca->pub, slot, CTRLIF_STATUS);
	अगर (status < 0)
		जाओ निकासnoग_लिखो;
	अगर (status & (STATUSREG_DA | STATUSREG_RE)) अणु
		अगर (status & STATUSREG_DA)
			dvb_ca_en50221_thपढ़ो_wakeup(ca);

		status = -EAGAIN;
		जाओ निकासnoग_लिखो;
	पूर्ण

	/* OK, set HC bit */
	status = ca->pub->ग_लिखो_cam_control(ca->pub, slot, CTRLIF_COMMAND,
					    IRQEN | CMDREG_HC);
	अगर (status)
		जाओ निकास;

	/* check अगर पूर्णांकerface is still मुक्त */
	status = ca->pub->पढ़ो_cam_control(ca->pub, slot, CTRLIF_STATUS);
	अगर (status < 0)
		जाओ निकास;
	अगर (!(status & STATUSREG_FR)) अणु
		/* it wasn't मुक्त => try again later */
		status = -EAGAIN;
		जाओ निकास;
	पूर्ण

	/*
	 * It may need some समय क्रम the CAM to settle करोwn, or there might
	 * be a race condition between the CAM, writing HC and our last
	 * check क्रम DA. This happens, अगर the CAM निश्चितs DA, just after
	 * checking DA beक्रमe we are setting HC. In this हाल it might be
	 * a bug in the CAM to keep the FR bit, the lower layer/HW
	 * communication requires a दीर्घer समयout or the CAM needs more
	 * समय पूर्णांकernally. But this happens in reality!
	 * We need to पढ़ो the status from the HW again and करो the same
	 * we did क्रम the previous check क्रम DA
	 */
	status = ca->pub->पढ़ो_cam_control(ca->pub, slot, CTRLIF_STATUS);
	अगर (status < 0)
		जाओ निकास;

	अगर (status & (STATUSREG_DA | STATUSREG_RE)) अणु
		अगर (status & STATUSREG_DA)
			dvb_ca_en50221_thपढ़ो_wakeup(ca);

		status = -EAGAIN;
		जाओ निकास;
	पूर्ण

	/* send the amount of data */
	status = ca->pub->ग_लिखो_cam_control(ca->pub, slot, CTRLIF_SIZE_HIGH,
					    bytes_ग_लिखो >> 8);
	अगर (status)
		जाओ निकास;
	status = ca->pub->ग_लिखो_cam_control(ca->pub, slot, CTRLIF_SIZE_LOW,
					    bytes_ग_लिखो & 0xff);
	अगर (status)
		जाओ निकास;

	/* send the buffer */
	क्रम (i = 0; i < bytes_ग_लिखो; i++) अणु
		status = ca->pub->ग_लिखो_cam_control(ca->pub, slot, CTRLIF_DATA,
						    buf[i]);
		अगर (status)
			जाओ निकास;
	पूर्ण

	/* check क्रम ग_लिखो error (WE should now be 0) */
	status = ca->pub->पढ़ो_cam_control(ca->pub, slot, CTRLIF_STATUS);
	अगर (status < 0)
		जाओ निकास;
	अगर (status & STATUSREG_WE) अणु
		sl->slot_state = DVB_CA_SLOTSTATE_LINKINIT;
		status = -EIO;
		जाओ निकास;
	पूर्ण
	status = bytes_ग_लिखो;

	dprपूर्णांकk("Wrote CA packet for slot %i, connection id 0x%x last_frag:%i size:0x%x\n", slot,
		buf[0], (buf[1] & 0x80) == 0, bytes_ग_लिखो);

निकास:
	ca->pub->ग_लिखो_cam_control(ca->pub, slot, CTRLIF_COMMAND, IRQEN);

निकासnoग_लिखो:
	वापस status;
पूर्ण

/* ************************************************************************** */
/* EN50221 higher level functions */

/**
 * dvb_ca_en50221_slot_shutकरोwn - A CAM has been हटाओd => shut it करोwn.
 *
 * @ca: CA instance.
 * @slot: Slot to shut करोwn.
 */
अटल पूर्णांक dvb_ca_en50221_slot_shutकरोwn(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot)
अणु
	dprपूर्णांकk("%s\n", __func__);

	ca->pub->slot_shutकरोwn(ca->pub, slot);
	ca->slot_info[slot].slot_state = DVB_CA_SLOTSTATE_NONE;

	/*
	 * need to wake up all processes to check अगर they're now trying to
	 * ग_लिखो to a defunct CAM
	 */
	wake_up_पूर्णांकerruptible(&ca->रुको_queue);

	dprपूर्णांकk("Slot %i shutdown\n", slot);

	/* success */
	वापस 0;
पूर्ण

/**
 * dvb_ca_en50221_camchange_irq - A CAMCHANGE IRQ has occurred.
 *
 * @pubca: CA instance.
 * @slot: Slot concerned.
 * @change_type: One of the DVB_CA_CAMCHANGE_* values.
 */
व्योम dvb_ca_en50221_camchange_irq(काष्ठा dvb_ca_en50221 *pubca, पूर्णांक slot,
				  पूर्णांक change_type)
अणु
	काष्ठा dvb_ca_निजी *ca = pubca->निजी;
	काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];

	dprपूर्णांकk("CAMCHANGE IRQ slot:%i change_type:%i\n", slot, change_type);

	चयन (change_type) अणु
	हाल DVB_CA_EN50221_CAMCHANGE_REMOVED:
	हाल DVB_CA_EN50221_CAMCHANGE_INSERTED:
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	sl->camchange_type = change_type;
	atomic_inc(&sl->camchange_count);
	dvb_ca_en50221_thपढ़ो_wakeup(ca);
पूर्ण
EXPORT_SYMBOL(dvb_ca_en50221_camchange_irq);

/**
 * dvb_ca_en50221_camपढ़ोy_irq - A CAMREADY IRQ has occurred.
 *
 * @pubca: CA instance.
 * @slot: Slot concerned.
 */
व्योम dvb_ca_en50221_camपढ़ोy_irq(काष्ठा dvb_ca_en50221 *pubca, पूर्णांक slot)
अणु
	काष्ठा dvb_ca_निजी *ca = pubca->निजी;
	काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];

	dprपूर्णांकk("CAMREADY IRQ slot:%i\n", slot);

	अगर (sl->slot_state == DVB_CA_SLOTSTATE_WAITREADY) अणु
		sl->slot_state = DVB_CA_SLOTSTATE_VALIDATE;
		dvb_ca_en50221_thपढ़ो_wakeup(ca);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dvb_ca_en50221_camपढ़ोy_irq);

/**
 * dvb_ca_en50221_frda_irq - An FR or DA IRQ has occurred.
 *
 * @pubca: CA instance.
 * @slot: Slot concerned.
 */
व्योम dvb_ca_en50221_frda_irq(काष्ठा dvb_ca_en50221 *pubca, पूर्णांक slot)
अणु
	काष्ठा dvb_ca_निजी *ca = pubca->निजी;
	काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];
	पूर्णांक flags;

	dprपूर्णांकk("FR/DA IRQ slot:%i\n", slot);

	चयन (sl->slot_state) अणु
	हाल DVB_CA_SLOTSTATE_LINKINIT:
		flags = ca->pub->पढ़ो_cam_control(pubca, slot, CTRLIF_STATUS);
		अगर (flags & STATUSREG_DA) अणु
			dprपूर्णांकk("CAM supports DA IRQ\n");
			sl->da_irq_supported = 1;
		पूर्ण
		अवरोध;

	हाल DVB_CA_SLOTSTATE_RUNNING:
		अगर (ca->खोलो)
			dvb_ca_en50221_thपढ़ो_wakeup(ca);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dvb_ca_en50221_frda_irq);

/* ************************************************************************** */
/* EN50221 thपढ़ो functions */

/**
 * dvb_ca_en50221_thपढ़ो_wakeup - Wake up the DVB CA thपढ़ो
 *
 * @ca: CA instance.
 */
अटल व्योम dvb_ca_en50221_thपढ़ो_wakeup(काष्ठा dvb_ca_निजी *ca)
अणु
	dprपूर्णांकk("%s\n", __func__);

	ca->wakeup = 1;
	mb();
	wake_up_process(ca->thपढ़ो);
पूर्ण

/**
 * dvb_ca_en50221_thपढ़ो_update_delay - Update the delay used by the thपढ़ो.
 *
 * @ca: CA instance.
 */
अटल व्योम dvb_ca_en50221_thपढ़ो_update_delay(काष्ठा dvb_ca_निजी *ca)
अणु
	पूर्णांक delay;
	पूर्णांक curdelay = 100000000;
	पूर्णांक slot;

	/*
	 * Beware of too high polling frequency, because one polling
	 * call might take several hundred milliseconds until समयout!
	 */
	क्रम (slot = 0; slot < ca->slot_count; slot++) अणु
		काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];

		चयन (sl->slot_state) अणु
		शेष:
		हाल DVB_CA_SLOTSTATE_NONE:
			delay = HZ * 60;  /* 60s */
			अगर (!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE))
				delay = HZ * 5;  /* 5s */
			अवरोध;
		हाल DVB_CA_SLOTSTATE_INVALID:
			delay = HZ * 60;  /* 60s */
			अगर (!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE))
				delay = HZ / 10;  /* 100ms */
			अवरोध;

		हाल DVB_CA_SLOTSTATE_UNINITIALISED:
		हाल DVB_CA_SLOTSTATE_WAITREADY:
		हाल DVB_CA_SLOTSTATE_VALIDATE:
		हाल DVB_CA_SLOTSTATE_WAITFR:
		हाल DVB_CA_SLOTSTATE_LINKINIT:
			delay = HZ / 10;  /* 100ms */
			अवरोध;

		हाल DVB_CA_SLOTSTATE_RUNNING:
			delay = HZ * 60;  /* 60s */
			अगर (!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE))
				delay = HZ / 10;  /* 100ms */
			अगर (ca->खोलो) अणु
				अगर ((!sl->da_irq_supported) ||
				    (!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_DA)))
					delay = HZ / 10;  /* 100ms */
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (delay < curdelay)
			curdelay = delay;
	पूर्ण

	ca->delay = curdelay;
पूर्ण

/**
 * dvb_ca_en50221_poll_cam_gone - Poll अगर the CAM is gone.
 *
 * @ca: CA instance.
 * @slot: Slot to process.
 * वापस:: 0 .. no change
 *          1 .. CAM state changed
 */

अटल पूर्णांक dvb_ca_en50221_poll_cam_gone(काष्ठा dvb_ca_निजी *ca, पूर्णांक slot)
अणु
	पूर्णांक changed = 0;
	पूर्णांक status;

	/*
	 * we need this extra check क्रम annoying पूर्णांकerfaces like the
	 * budget-av
	 */
	अगर ((!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE)) &&
	    (ca->pub->poll_slot_status)) अणु
		status = ca->pub->poll_slot_status(ca->pub, slot, 0);
		अगर (!(status &
			DVB_CA_EN50221_POLL_CAM_PRESENT)) अणु
			ca->slot_info[slot].slot_state = DVB_CA_SLOTSTATE_NONE;
			dvb_ca_en50221_thपढ़ो_update_delay(ca);
			changed = 1;
		पूर्ण
	पूर्ण
	वापस changed;
पूर्ण

/**
 * dvb_ca_en50221_thपढ़ो_state_machine - Thपढ़ो state machine क्रम one CA slot
 *	to perक्रमm the data transfer.
 *
 * @ca: CA instance.
 * @slot: Slot to process.
 */
अटल व्योम dvb_ca_en50221_thपढ़ो_state_machine(काष्ठा dvb_ca_निजी *ca,
						पूर्णांक slot)
अणु
	काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];
	पूर्णांक flags;
	पूर्णांक pktcount;
	व्योम *rxbuf;

	mutex_lock(&sl->slot_lock);

	/* check the cam status + deal with CAMCHANGEs */
	जबतक (dvb_ca_en50221_check_camstatus(ca, slot)) अणु
		/* clear करोwn an old CI slot अगर necessary */
		अगर (sl->slot_state != DVB_CA_SLOTSTATE_NONE)
			dvb_ca_en50221_slot_shutकरोwn(ca, slot);

		/* अगर a CAM is NOW present, initialise it */
		अगर (sl->camchange_type == DVB_CA_EN50221_CAMCHANGE_INSERTED)
			sl->slot_state = DVB_CA_SLOTSTATE_UNINITIALISED;

		/* we've handled one CAMCHANGE */
		dvb_ca_en50221_thपढ़ो_update_delay(ca);
		atomic_dec(&sl->camchange_count);
	पूर्ण

	/* CAM state machine */
	चयन (sl->slot_state) अणु
	हाल DVB_CA_SLOTSTATE_NONE:
	हाल DVB_CA_SLOTSTATE_INVALID:
		/* no action needed */
		अवरोध;

	हाल DVB_CA_SLOTSTATE_UNINITIALISED:
		sl->slot_state = DVB_CA_SLOTSTATE_WAITREADY;
		ca->pub->slot_reset(ca->pub, slot);
		sl->समयout = jअगरfies + (INIT_TIMEOUT_SECS * HZ);
		अवरोध;

	हाल DVB_CA_SLOTSTATE_WAITREADY:
		अगर (समय_after(jअगरfies, sl->समयout)) अणु
			pr_err("dvb_ca adaptor %d: PC card did not respond :(\n",
			       ca->dvbdev->adapter->num);
			sl->slot_state = DVB_CA_SLOTSTATE_INVALID;
			dvb_ca_en50221_thपढ़ो_update_delay(ca);
			अवरोध;
		पूर्ण
		/*
		 * no other action needed; will स्वतःmatically change state when
		 * पढ़ोy
		 */
		अवरोध;

	हाल DVB_CA_SLOTSTATE_VALIDATE:
		अगर (dvb_ca_en50221_parse_attributes(ca, slot) != 0) अणु
			अगर (dvb_ca_en50221_poll_cam_gone(ca, slot))
				अवरोध;

			pr_err("dvb_ca adapter %d: Invalid PC card inserted :(\n",
			       ca->dvbdev->adapter->num);
			sl->slot_state = DVB_CA_SLOTSTATE_INVALID;
			dvb_ca_en50221_thपढ़ो_update_delay(ca);
			अवरोध;
		पूर्ण
		अगर (dvb_ca_en50221_set_configoption(ca, slot) != 0) अणु
			pr_err("dvb_ca adapter %d: Unable to initialise CAM :(\n",
			       ca->dvbdev->adapter->num);
			sl->slot_state = DVB_CA_SLOTSTATE_INVALID;
			dvb_ca_en50221_thपढ़ो_update_delay(ca);
			अवरोध;
		पूर्ण
		अगर (ca->pub->ग_लिखो_cam_control(ca->pub, slot,
					       CTRLIF_COMMAND,
					       CMDREG_RS) != 0) अणु
			pr_err("dvb_ca adapter %d: Unable to reset CAM IF\n",
			       ca->dvbdev->adapter->num);
			sl->slot_state = DVB_CA_SLOTSTATE_INVALID;
			dvb_ca_en50221_thपढ़ो_update_delay(ca);
			अवरोध;
		पूर्ण
		dprपूर्णांकk("DVB CAM validated successfully\n");

		sl->समयout = jअगरfies + (INIT_TIMEOUT_SECS * HZ);
		sl->slot_state = DVB_CA_SLOTSTATE_WAITFR;
		ca->wakeup = 1;
		अवरोध;

	हाल DVB_CA_SLOTSTATE_WAITFR:
		अगर (समय_after(jअगरfies, sl->समयout)) अणु
			pr_err("dvb_ca adapter %d: DVB CAM did not respond :(\n",
			       ca->dvbdev->adapter->num);
			sl->slot_state = DVB_CA_SLOTSTATE_INVALID;
			dvb_ca_en50221_thपढ़ो_update_delay(ca);
			अवरोध;
		पूर्ण

		flags = ca->pub->पढ़ो_cam_control(ca->pub, slot, CTRLIF_STATUS);
		अगर (flags & STATUSREG_FR) अणु
			sl->slot_state = DVB_CA_SLOTSTATE_LINKINIT;
			ca->wakeup = 1;
		पूर्ण
		अवरोध;

	हाल DVB_CA_SLOTSTATE_LINKINIT:
		अगर (dvb_ca_en50221_link_init(ca, slot) != 0) अणु
			अगर (dvb_ca_en50221_poll_cam_gone(ca, slot))
				अवरोध;

			pr_err("dvb_ca adapter %d: DVB CAM link initialisation failed :(\n",
			       ca->dvbdev->adapter->num);
			sl->slot_state = DVB_CA_SLOTSTATE_UNINITIALISED;
			dvb_ca_en50221_thपढ़ो_update_delay(ca);
			अवरोध;
		पूर्ण

		अगर (!sl->rx_buffer.data) अणु
			rxbuf = vदो_स्मृति(RX_BUFFER_SIZE);
			अगर (!rxbuf) अणु
				pr_err("dvb_ca adapter %d: Unable to allocate CAM rx buffer :(\n",
				       ca->dvbdev->adapter->num);
				sl->slot_state = DVB_CA_SLOTSTATE_INVALID;
				dvb_ca_en50221_thपढ़ो_update_delay(ca);
				अवरोध;
			पूर्ण
			dvb_ringbuffer_init(&sl->rx_buffer, rxbuf,
					    RX_BUFFER_SIZE);
		पूर्ण

		ca->pub->slot_ts_enable(ca->pub, slot);
		sl->slot_state = DVB_CA_SLOTSTATE_RUNNING;
		dvb_ca_en50221_thपढ़ो_update_delay(ca);
		pr_info("dvb_ca adapter %d: DVB CAM detected and initialised successfully\n",
			ca->dvbdev->adapter->num);
		अवरोध;

	हाल DVB_CA_SLOTSTATE_RUNNING:
		अगर (!ca->खोलो)
			अवरोध;

		/* poll slots क्रम data */
		pktcount = 0;
		जबतक (dvb_ca_en50221_पढ़ो_data(ca, slot, शून्य, 0) > 0) अणु
			अगर (!ca->खोलो)
				अवरोध;

			/*
			 * अगर a CAMCHANGE occurred at some poपूर्णांक, करो not करो any
			 * more processing of this slot
			 */
			अगर (dvb_ca_en50221_check_camstatus(ca, slot)) अणु
				/*
				 * we करोn't want to sleep on the next iteration
				 * so we can handle the cam change
				 */
				ca->wakeup = 1;
				अवरोध;
			पूर्ण

			/* check अगर we've hit our limit this समय */
			अगर (++pktcount >= MAX_RX_PACKETS_PER_ITERATION) अणु
				/*
				 * करोn't sleep; there is likely to be more data
				 * to पढ़ो
				 */
				ca->wakeup = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	mutex_unlock(&sl->slot_lock);
पूर्ण

/*
 * Kernel thपढ़ो which monitors CA slots क्रम CAM changes, and perक्रमms data
 * transfers.
 */
अटल पूर्णांक dvb_ca_en50221_thपढ़ो(व्योम *data)
अणु
	काष्ठा dvb_ca_निजी *ca = data;
	पूर्णांक slot;

	dprपूर्णांकk("%s\n", __func__);

	/* choose the correct initial delay */
	dvb_ca_en50221_thपढ़ो_update_delay(ca);

	/* मुख्य loop */
	जबतक (!kthपढ़ो_should_stop()) अणु
		/* sleep क्रम a bit */
		अगर (!ca->wakeup) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_समयout(ca->delay);
			अगर (kthपढ़ो_should_stop())
				वापस 0;
		पूर्ण
		ca->wakeup = 0;

		/* go through all the slots processing them */
		क्रम (slot = 0; slot < ca->slot_count; slot++)
			dvb_ca_en50221_thपढ़ो_state_machine(ca, slot);
	पूर्ण

	वापस 0;
पूर्ण

/* ************************************************************************** */
/* EN50221 IO पूर्णांकerface functions */

/**
 * dvb_ca_en50221_io_करो_ioctl - Real ioctl implementation.
 *
 * @file: File concerned.
 * @cmd: IOCTL command.
 * @parg: Associated argument.
 *
 * NOTE: CA_SEND_MSG/CA_GET_MSG ioctls have userspace buffers passed to them.
 *
 * वापस: 0 on success, <0 on error.
 */
अटल पूर्णांक dvb_ca_en50221_io_करो_ioctl(काष्ठा file *file,
				      अचिन्हित पूर्णांक cmd, व्योम *parg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_ca_निजी *ca = dvbdev->priv;
	पूर्णांक err = 0;
	पूर्णांक slot;

	dprपूर्णांकk("%s\n", __func__);

	अगर (mutex_lock_पूर्णांकerruptible(&ca->ioctl_mutex))
		वापस -ERESTARTSYS;

	चयन (cmd) अणु
	हाल CA_RESET:
		क्रम (slot = 0; slot < ca->slot_count; slot++) अणु
			काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];

			mutex_lock(&sl->slot_lock);
			अगर (sl->slot_state != DVB_CA_SLOTSTATE_NONE) अणु
				dvb_ca_en50221_slot_shutकरोwn(ca, slot);
				अगर (ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE)
					dvb_ca_en50221_camchange_irq(ca->pub,
								     slot,
								     DVB_CA_EN50221_CAMCHANGE_INSERTED);
			पूर्ण
			mutex_unlock(&sl->slot_lock);
		पूर्ण
		ca->next_पढ़ो_slot = 0;
		dvb_ca_en50221_thपढ़ो_wakeup(ca);
		अवरोध;

	हाल CA_GET_CAP: अणु
		काष्ठा ca_caps *caps = parg;

		caps->slot_num = ca->slot_count;
		caps->slot_type = CA_CI_LINK;
		caps->descr_num = 0;
		caps->descr_type = 0;
		अवरोध;
	पूर्ण

	हाल CA_GET_SLOT_INFO: अणु
		काष्ठा ca_slot_info *info = parg;
		काष्ठा dvb_ca_slot *sl;

		slot = info->num;
		अगर ((slot >= ca->slot_count) || (slot < 0)) अणु
			err = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		info->type = CA_CI_LINK;
		info->flags = 0;
		sl = &ca->slot_info[slot];
		अगर ((sl->slot_state != DVB_CA_SLOTSTATE_NONE) &&
		    (sl->slot_state != DVB_CA_SLOTSTATE_INVALID)) अणु
			info->flags = CA_CI_MODULE_PRESENT;
		पूर्ण
		अगर (sl->slot_state == DVB_CA_SLOTSTATE_RUNNING)
			info->flags |= CA_CI_MODULE_READY;
		अवरोध;
	पूर्ण

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

out_unlock:
	mutex_unlock(&ca->ioctl_mutex);
	वापस err;
पूर्ण

/**
 * dvb_ca_en50221_io_ioctl - Wrapper क्रम ioctl implementation.
 *
 * @file: File concerned.
 * @cmd: IOCTL command.
 * @arg: Associated argument.
 *
 * वापस: 0 on success, <0 on error.
 */
अटल दीर्घ dvb_ca_en50221_io_ioctl(काष्ठा file *file,
				    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस dvb_usercopy(file, cmd, arg, dvb_ca_en50221_io_करो_ioctl);
पूर्ण

/**
 * dvb_ca_en50221_io_ग_लिखो - Implementation of ग_लिखो() syscall.
 *
 * @file: File काष्ठाure.
 * @buf: Source buffer.
 * @count: Size of source buffer.
 * @ppos: Position in file (ignored).
 *
 * वापस: Number of bytes पढ़ो, or <0 on error.
 */
अटल sमाप_प्रकार dvb_ca_en50221_io_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *buf, माप_प्रकार count,
				       loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_ca_निजी *ca = dvbdev->priv;
	काष्ठा dvb_ca_slot *sl;
	u8 slot, connection_id;
	पूर्णांक status;
	u8 fragbuf[HOST_LINK_BUF_SIZE];
	पूर्णांक fragpos = 0;
	पूर्णांक fraglen;
	अचिन्हित दीर्घ समयout;
	पूर्णांक written;

	dprपूर्णांकk("%s\n", __func__);

	/*
	 * Incoming packet has a 2 byte header.
	 * hdr[0] = slot_id, hdr[1] = connection_id
	 */
	अगर (count < 2)
		वापस -EINVAL;

	/* extract slot & connection id */
	अगर (copy_from_user(&slot, buf, 1))
		वापस -EFAULT;
	अगर (copy_from_user(&connection_id, buf + 1, 1))
		वापस -EFAULT;
	buf += 2;
	count -= 2;

	अगर (slot >= ca->slot_count)
		वापस -EINVAL;
	slot = array_index_nospec(slot, ca->slot_count);
	sl = &ca->slot_info[slot];

	/* check अगर the slot is actually running */
	अगर (sl->slot_state != DVB_CA_SLOTSTATE_RUNNING)
		वापस -EINVAL;

	/* fragment the packets & store in the buffer */
	जबतक (fragpos < count) अणु
		fraglen = sl->link_buf_size - 2;
		अगर (fraglen < 0)
			अवरोध;
		अगर (fraglen > HOST_LINK_BUF_SIZE - 2)
			fraglen = HOST_LINK_BUF_SIZE - 2;
		अगर ((count - fragpos) < fraglen)
			fraglen = count - fragpos;

		fragbuf[0] = connection_id;
		fragbuf[1] = ((fragpos + fraglen) < count) ? 0x80 : 0x00;
		status = copy_from_user(fragbuf + 2, buf + fragpos, fraglen);
		अगर (status) अणु
			status = -EFAULT;
			जाओ निकास;
		पूर्ण

		समयout = jअगरfies + HZ / 2;
		written = 0;
		जबतक (!समय_after(jअगरfies, समयout)) अणु
			/*
			 * check the CAM hasn't been हटाओd/reset in the
			 * meanसमय
			 */
			अगर (sl->slot_state != DVB_CA_SLOTSTATE_RUNNING) अणु
				status = -EIO;
				जाओ निकास;
			पूर्ण

			mutex_lock(&sl->slot_lock);
			status = dvb_ca_en50221_ग_लिखो_data(ca, slot, fragbuf,
							   fraglen + 2);
			mutex_unlock(&sl->slot_lock);
			अगर (status == (fraglen + 2)) अणु
				written = 1;
				अवरोध;
			पूर्ण
			अगर (status != -EAGAIN)
				जाओ निकास;

			usleep_range(1000, 1100);
		पूर्ण
		अगर (!written) अणु
			status = -EIO;
			जाओ निकास;
		पूर्ण

		fragpos += fraglen;
	पूर्ण
	status = count + 2;

निकास:
	वापस status;
पूर्ण

/*
 * Condition क्रम waking up in dvb_ca_en50221_io_पढ़ो_condition
 */
अटल पूर्णांक dvb_ca_en50221_io_पढ़ो_condition(काष्ठा dvb_ca_निजी *ca,
					    पूर्णांक *result, पूर्णांक *_slot)
अणु
	पूर्णांक slot;
	पूर्णांक slot_count = 0;
	पूर्णांक idx;
	माप_प्रकार fraglen;
	पूर्णांक connection_id = -1;
	पूर्णांक found = 0;
	u8 hdr[2];

	slot = ca->next_पढ़ो_slot;
	जबतक ((slot_count < ca->slot_count) && (!found)) अणु
		काष्ठा dvb_ca_slot *sl = &ca->slot_info[slot];

		अगर (sl->slot_state != DVB_CA_SLOTSTATE_RUNNING)
			जाओ nextslot;

		अगर (!sl->rx_buffer.data)
			वापस 0;

		idx = dvb_ringbuffer_pkt_next(&sl->rx_buffer, -1, &fraglen);
		जबतक (idx != -1) अणु
			dvb_ringbuffer_pkt_पढ़ो(&sl->rx_buffer, idx, 0, hdr, 2);
			अगर (connection_id == -1)
				connection_id = hdr[0];
			अगर ((hdr[0] == connection_id) &&
			    ((hdr[1] & 0x80) == 0)) अणु
				*_slot = slot;
				found = 1;
				अवरोध;
			पूर्ण

			idx = dvb_ringbuffer_pkt_next(&sl->rx_buffer, idx,
						      &fraglen);
		पूर्ण

nextslot:
		slot = (slot + 1) % ca->slot_count;
		slot_count++;
	पूर्ण

	ca->next_पढ़ो_slot = slot;
	वापस found;
पूर्ण

/**
 * dvb_ca_en50221_io_पढ़ो - Implementation of पढ़ो() syscall.
 *
 * @file: File काष्ठाure.
 * @buf: Destination buffer.
 * @count: Size of destination buffer.
 * @ppos: Position in file (ignored).
 *
 * वापस: Number of bytes पढ़ो, or <0 on error.
 */
अटल sमाप_प्रकार dvb_ca_en50221_io_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_ca_निजी *ca = dvbdev->priv;
	काष्ठा dvb_ca_slot *sl;
	पूर्णांक status;
	पूर्णांक result = 0;
	u8 hdr[2];
	पूर्णांक slot;
	पूर्णांक connection_id = -1;
	माप_प्रकार idx, idx2;
	पूर्णांक last_fragment = 0;
	माप_प्रकार fraglen;
	पूर्णांक pktlen;
	पूर्णांक dispose = 0;

	dprपूर्णांकk("%s\n", __func__);

	/*
	 * Outgoing packet has a 2 byte header.
	 * hdr[0] = slot_id, hdr[1] = connection_id
	 */
	अगर (count < 2)
		वापस -EINVAL;

	/* रुको क्रम some data */
	status = dvb_ca_en50221_io_पढ़ो_condition(ca, &result, &slot);
	अगर (status == 0) अणु
		/* अगर we're in nonblocking mode, निकास immediately */
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EWOULDBLOCK;

		/* रुको क्रम some data */
		status = रुको_event_पूर्णांकerruptible(ca->रुको_queue,
						  dvb_ca_en50221_io_पढ़ो_condition
						  (ca, &result, &slot));
	पूर्ण
	अगर ((status < 0) || (result < 0)) अणु
		अगर (result)
			वापस result;
		वापस status;
	पूर्ण

	sl = &ca->slot_info[slot];
	idx = dvb_ringbuffer_pkt_next(&sl->rx_buffer, -1, &fraglen);
	pktlen = 2;
	करो अणु
		अगर (idx == -1) अणु
			pr_err("dvb_ca adapter %d: BUG: read packet ended before last_fragment encountered\n",
			       ca->dvbdev->adapter->num);
			status = -EIO;
			जाओ निकास;
		पूर्ण

		dvb_ringbuffer_pkt_पढ़ो(&sl->rx_buffer, idx, 0, hdr, 2);
		अगर (connection_id == -1)
			connection_id = hdr[0];
		अगर (hdr[0] == connection_id) अणु
			अगर (pktlen < count) अणु
				अगर ((pktlen + fraglen - 2) > count)
					fraglen = count - pktlen;
				अन्यथा
					fraglen -= 2;

				status =
				   dvb_ringbuffer_pkt_पढ़ो_user(&sl->rx_buffer,
								idx, 2,
								buf + pktlen,
								fraglen);
				अगर (status < 0)
					जाओ निकास;

				pktlen += fraglen;
			पूर्ण

			अगर ((hdr[1] & 0x80) == 0)
				last_fragment = 1;
			dispose = 1;
		पूर्ण

		idx2 = dvb_ringbuffer_pkt_next(&sl->rx_buffer, idx, &fraglen);
		अगर (dispose)
			dvb_ringbuffer_pkt_dispose(&sl->rx_buffer, idx);
		idx = idx2;
		dispose = 0;
	पूर्ण जबतक (!last_fragment);

	hdr[0] = slot;
	hdr[1] = connection_id;
	status = copy_to_user(buf, hdr, 2);
	अगर (status) अणु
		status = -EFAULT;
		जाओ निकास;
	पूर्ण
	status = pktlen;

निकास:
	वापस status;
पूर्ण

/**
 * dvb_ca_en50221_io_खोलो - Implementation of file खोलो syscall.
 *
 * @inode: Inode concerned.
 * @file: File concerned.
 *
 * वापस: 0 on success, <0 on failure.
 */
अटल पूर्णांक dvb_ca_en50221_io_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_ca_निजी *ca = dvbdev->priv;
	पूर्णांक err;
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	अगर (!try_module_get(ca->pub->owner))
		वापस -EIO;

	err = dvb_generic_खोलो(inode, file);
	अगर (err < 0) अणु
		module_put(ca->pub->owner);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < ca->slot_count; i++) अणु
		काष्ठा dvb_ca_slot *sl = &ca->slot_info[i];

		अगर (sl->slot_state == DVB_CA_SLOTSTATE_RUNNING) अणु
			अगर (!sl->rx_buffer.data) अणु
				/*
				 * it is safe to call this here without locks
				 * because ca->खोलो == 0. Data is not पढ़ो in
				 * this हाल
				 */
				dvb_ringbuffer_flush(&sl->rx_buffer);
			पूर्ण
		पूर्ण
	पूर्ण

	ca->खोलो = 1;
	dvb_ca_en50221_thपढ़ो_update_delay(ca);
	dvb_ca_en50221_thपढ़ो_wakeup(ca);

	dvb_ca_निजी_get(ca);

	वापस 0;
पूर्ण

/**
 * dvb_ca_en50221_io_release - Implementation of file बंद syscall.
 *
 * @inode: Inode concerned.
 * @file: File concerned.
 *
 * वापस: 0 on success, <0 on failure.
 */
अटल पूर्णांक dvb_ca_en50221_io_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_ca_निजी *ca = dvbdev->priv;
	पूर्णांक err;

	dprपूर्णांकk("%s\n", __func__);

	/* mark the CA device as बंदd */
	ca->खोलो = 0;
	dvb_ca_en50221_thपढ़ो_update_delay(ca);

	err = dvb_generic_release(inode, file);

	module_put(ca->pub->owner);

	dvb_ca_निजी_put(ca);

	वापस err;
पूर्ण

/**
 * dvb_ca_en50221_io_poll - Implementation of poll() syscall.
 *
 * @file: File concerned.
 * @रुको: poll रुको table.
 *
 * वापस: Standard poll mask.
 */
अटल __poll_t dvb_ca_en50221_io_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_ca_निजी *ca = dvbdev->priv;
	__poll_t mask = 0;
	पूर्णांक slot;
	पूर्णांक result = 0;

	dprपूर्णांकk("%s\n", __func__);

	poll_रुको(file, &ca->रुको_queue, रुको);

	अगर (dvb_ca_en50221_io_पढ़ो_condition(ca, &result, &slot) == 1)
		mask |= EPOLLIN;

	/* अगर there is something, वापस now */
	अगर (mask)
		वापस mask;

	अगर (dvb_ca_en50221_io_पढ़ो_condition(ca, &result, &slot) == 1)
		mask |= EPOLLIN;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations dvb_ca_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = dvb_ca_en50221_io_पढ़ो,
	.ग_लिखो = dvb_ca_en50221_io_ग_लिखो,
	.unlocked_ioctl = dvb_ca_en50221_io_ioctl,
	.खोलो = dvb_ca_en50221_io_खोलो,
	.release = dvb_ca_en50221_io_release,
	.poll = dvb_ca_en50221_io_poll,
	.llseek = noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा dvb_device dvbdev_ca = अणु
	.priv = शून्य,
	.users = 1,
	.पढ़ोers = 1,
	.ग_लिखोrs = 1,
#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-ca-en50221",
#पूर्ण_अगर
	.fops = &dvb_ca_fops,
पूर्ण;

/* ************************************************************************** */
/* Initialisation/shutकरोwn functions */

/**
 * dvb_ca_en50221_init - Initialise a new DVB CA EN50221 पूर्णांकerface device.
 *
 * @dvb_adapter: DVB adapter to attach the new CA device to.
 * @pubca: The dvb_ca instance.
 * @flags: Flags describing the CA device (DVB_CA_FLAG_*).
 * @slot_count: Number of slots supported.
 *
 * वापस: 0 on success, nonzero on failure
 */
पूर्णांक dvb_ca_en50221_init(काष्ठा dvb_adapter *dvb_adapter,
			काष्ठा dvb_ca_en50221 *pubca, पूर्णांक flags, पूर्णांक slot_count)
अणु
	पूर्णांक ret;
	काष्ठा dvb_ca_निजी *ca = शून्य;
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	अगर (slot_count < 1)
		वापस -EINVAL;

	/* initialise the प्रणाली data */
	ca = kzalloc(माप(*ca), GFP_KERNEL);
	अगर (!ca) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण
	kref_init(&ca->refcount);
	ca->pub = pubca;
	ca->flags = flags;
	ca->slot_count = slot_count;
	ca->slot_info = kसुस्मृति(slot_count, माप(काष्ठा dvb_ca_slot),
				GFP_KERNEL);
	अगर (!ca->slot_info) अणु
		ret = -ENOMEM;
		जाओ मुक्त_ca;
	पूर्ण
	init_रुकोqueue_head(&ca->रुको_queue);
	ca->खोलो = 0;
	ca->wakeup = 0;
	ca->next_पढ़ो_slot = 0;
	pubca->निजी = ca;

	/* रेजिस्टर the DVB device */
	ret = dvb_रेजिस्टर_device(dvb_adapter, &ca->dvbdev, &dvbdev_ca, ca,
				  DVB_DEVICE_CA, 0);
	अगर (ret)
		जाओ मुक्त_slot_info;

	/* now initialise each slot */
	क्रम (i = 0; i < slot_count; i++) अणु
		काष्ठा dvb_ca_slot *sl = &ca->slot_info[i];

		स_रखो(sl, 0, माप(काष्ठा dvb_ca_slot));
		sl->slot_state = DVB_CA_SLOTSTATE_NONE;
		atomic_set(&sl->camchange_count, 0);
		sl->camchange_type = DVB_CA_EN50221_CAMCHANGE_REMOVED;
		mutex_init(&sl->slot_lock);
	पूर्ण

	mutex_init(&ca->ioctl_mutex);

	अगर (संकेत_pending(current)) अणु
		ret = -EINTR;
		जाओ unरेजिस्टर_device;
	पूर्ण
	mb();

	/* create a kthपढ़ो क्रम monitoring this CA device */
	ca->thपढ़ो = kthपढ़ो_run(dvb_ca_en50221_thपढ़ो, ca, "kdvb-ca-%i:%i",
				 ca->dvbdev->adapter->num, ca->dvbdev->id);
	अगर (IS_ERR(ca->thपढ़ो)) अणु
		ret = PTR_ERR(ca->thपढ़ो);
		pr_err("dvb_ca_init: failed to start kernel_thread (%d)\n",
		       ret);
		जाओ unरेजिस्टर_device;
	पूर्ण
	वापस 0;

unरेजिस्टर_device:
	dvb_unरेजिस्टर_device(ca->dvbdev);
मुक्त_slot_info:
	kमुक्त(ca->slot_info);
मुक्त_ca:
	kमुक्त(ca);
निकास:
	pubca->निजी = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_ca_en50221_init);

/**
 * dvb_ca_en50221_release - Release a DVB CA EN50221 पूर्णांकerface device.
 *
 * @pubca: The associated dvb_ca instance.
 */
व्योम dvb_ca_en50221_release(काष्ठा dvb_ca_en50221 *pubca)
अणु
	काष्ठा dvb_ca_निजी *ca = pubca->निजी;
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	/* shutकरोwn the thपढ़ो अगर there was one */
	kthपढ़ो_stop(ca->thपढ़ो);

	क्रम (i = 0; i < ca->slot_count; i++)
		dvb_ca_en50221_slot_shutकरोwn(ca, i);

	dvb_हटाओ_device(ca->dvbdev);
	dvb_ca_निजी_put(ca);
	pubca->निजी = शून्य;
पूर्ण
EXPORT_SYMBOL(dvb_ca_en50221_release);
