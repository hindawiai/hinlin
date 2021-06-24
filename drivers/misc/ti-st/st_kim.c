<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Shared Transport Line discipline driver Core
 *	Init Manager module responsible क्रम GPIO control
 *	and firmware करोwnload
 *  Copyright (C) 2009-2010 Texas Instruments
 *  Author: Pavan Savoy <pavan_savoy@ti.com>
 */

#घोषणा pr_fmt(fmt) "(stk) :" fmt
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/tty.h>

#समावेश <linux/skbuff.h>
#समावेश <linux/ti_wilink_st.h>
#समावेश <linux/module.h>

#घोषणा MAX_ST_DEVICES	3	/* Imagine 1 on each UART क्रम now */
अटल काष्ठा platक्रमm_device *st_kim_devices[MAX_ST_DEVICES];

/**********************************************************************/
/* पूर्णांकernal functions */

/*
 * st_get_plat_device -
 *	function which वापसs the reference to the platक्रमm device
 *	requested by id. As of now only 1 such device exists (id=0)
 *	the context requesting क्रम reference can get the id to be
 *	requested by a. The protocol driver which is रेजिस्टरing or
 *	b. the tty device which is खोलोed.
 */
अटल काष्ठा platक्रमm_device *st_get_plat_device(पूर्णांक id)
अणु
	वापस st_kim_devices[id];
पूर्ण

/*
 * validate_firmware_response -
 *	function to वापस whether the firmware response was proper
 *	in हाल of error करोn't complete so that रुकोing क्रम proper
 *	response बार out
 */
अटल व्योम validate_firmware_response(काष्ठा kim_data_s *kim_gdata)
अणु
	काष्ठा sk_buff *skb = kim_gdata->rx_skb;
	अगर (!skb)
		वापस;

	/*
	 * these magic numbers are the position in the response buffer which
	 * allows us to distinguish whether the response is क्रम the पढ़ो
	 * version info. command
	 */
	अगर (skb->data[2] == 0x01 && skb->data[3] == 0x01 &&
			skb->data[4] == 0x10 && skb->data[5] == 0x00) अणु
		/* fw version response */
		स_नकल(kim_gdata->resp_buffer,
				kim_gdata->rx_skb->data,
				kim_gdata->rx_skb->len);
		kim_gdata->rx_state = ST_W4_PACKET_TYPE;
		kim_gdata->rx_skb = शून्य;
		kim_gdata->rx_count = 0;
	पूर्ण अन्यथा अगर (unlikely(skb->data[5] != 0)) अणु
		pr_err("no proper response during fw download");
		pr_err("data6 %x", skb->data[5]);
		kमुक्त_skb(skb);
		वापस;		/* keep रुकोing क्रम the proper response */
	पूर्ण
	/* becos of all the script being करोwnloaded */
	complete_all(&kim_gdata->kim_rcvd);
	kमुक्त_skb(skb);
पूर्ण

/*
 * check क्रम data len received inside kim_पूर्णांक_recv
 * most often hit the last हाल to update state to रुकोing क्रम data
 */
अटल अंतरभूत पूर्णांक kim_check_data_len(काष्ठा kim_data_s *kim_gdata, पूर्णांक len)
अणु
	रेजिस्टर पूर्णांक room = skb_tailroom(kim_gdata->rx_skb);

	pr_debug("len %d room %d", len, room);

	अगर (!len) अणु
		validate_firmware_response(kim_gdata);
	पूर्ण अन्यथा अगर (len > room) अणु
		/*
		 * Received packet's payload length is larger.
		 * We can't accommodate it in created skb.
		 */
		pr_err("Data length is too large len %d room %d", len,
			   room);
		kमुक्त_skb(kim_gdata->rx_skb);
	पूर्ण अन्यथा अणु
		/*
		 * Packet header has non-zero payload length and
		 * we have enough space in created skb. Lets पढ़ो
		 * payload data */
		kim_gdata->rx_state = ST_W4_DATA;
		kim_gdata->rx_count = len;
		वापस len;
	पूर्ण

	/*
	 * Change ST LL state to जारी to process next
	 * packet
	 */
	kim_gdata->rx_state = ST_W4_PACKET_TYPE;
	kim_gdata->rx_skb = शून्य;
	kim_gdata->rx_count = 0;

	वापस 0;
पूर्ण

/*
 * kim_पूर्णांक_recv - receive function called during firmware करोwnload
 *	firmware करोwnload responses on dअगरferent UART drivers
 *	have been observed to come in bursts of dअगरferent
 *	tty_receive and hence the logic
 */
अटल व्योम kim_पूर्णांक_recv(काष्ठा kim_data_s *kim_gdata,
	स्थिर अचिन्हित अक्षर *data, दीर्घ count)
अणु
	स्थिर अचिन्हित अक्षर *ptr;
	पूर्णांक len = 0;
	अचिन्हित अक्षर *plen;

	pr_debug("%s", __func__);
	/* Decode received bytes here */
	ptr = data;
	अगर (unlikely(ptr == शून्य)) अणु
		pr_err(" received null from TTY ");
		वापस;
	पूर्ण

	जबतक (count) अणु
		अगर (kim_gdata->rx_count) अणु
			len = min_t(अचिन्हित पूर्णांक, kim_gdata->rx_count, count);
			skb_put_data(kim_gdata->rx_skb, ptr, len);
			kim_gdata->rx_count -= len;
			count -= len;
			ptr += len;

			अगर (kim_gdata->rx_count)
				जारी;

			/* Check ST RX state machine , where are we? */
			चयन (kim_gdata->rx_state) अणु
				/* Waiting क्रम complete packet ? */
			हाल ST_W4_DATA:
				pr_debug("Complete pkt received");
				validate_firmware_response(kim_gdata);
				kim_gdata->rx_state = ST_W4_PACKET_TYPE;
				kim_gdata->rx_skb = शून्य;
				जारी;
				/* Waiting क्रम Bluetooth event header ? */
			हाल ST_W4_HEADER:
				plen =
				(अचिन्हित अक्षर *)&kim_gdata->rx_skb->data[1];
				pr_debug("event hdr: plen 0x%02x\n", *plen);
				kim_check_data_len(kim_gdata, *plen);
				जारी;
			पूर्ण	/* end of चयन */
		पूर्ण		/* end of अगर rx_state */
		चयन (*ptr) अणु
			/* Bluetooth event packet? */
		हाल 0x04:
			kim_gdata->rx_state = ST_W4_HEADER;
			kim_gdata->rx_count = 2;
			अवरोध;
		शेष:
			pr_info("unknown packet");
			ptr++;
			count--;
			जारी;
		पूर्ण
		ptr++;
		count--;
		kim_gdata->rx_skb =
			alloc_skb(1024+8, GFP_ATOMIC);
		अगर (!kim_gdata->rx_skb) अणु
			pr_err("can't allocate mem for new packet");
			kim_gdata->rx_state = ST_W4_PACKET_TYPE;
			kim_gdata->rx_count = 0;
			वापस;
		पूर्ण
		skb_reserve(kim_gdata->rx_skb, 8);
		kim_gdata->rx_skb->cb[0] = 4;
		kim_gdata->rx_skb->cb[1] = 0;

	पूर्ण
	वापस;
पूर्ण

अटल दीर्घ पढ़ो_local_version(काष्ठा kim_data_s *kim_gdata, अक्षर *bts_scr_name)
अणु
	अचिन्हित लघु version = 0, chip = 0, min_ver = 0, maj_ver = 0;
	अटल स्थिर अक्षर पढ़ो_ver_cmd[] = अणु 0x01, 0x01, 0x10, 0x00 पूर्ण;
	दीर्घ समयout;

	pr_debug("%s", __func__);

	reinit_completion(&kim_gdata->kim_rcvd);
	अगर (4 != st_पूर्णांक_ग_लिखो(kim_gdata->core_data, पढ़ो_ver_cmd, 4)) अणु
		pr_err("kim: couldn't write 4 bytes");
		वापस -EIO;
	पूर्ण

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&kim_gdata->kim_rcvd, msecs_to_jअगरfies(CMD_RESP_TIME));
	अगर (समयout <= 0) अणु
		pr_err(" waiting for ver info- timed out or received signal");
		वापस समयout ? -ERESTARTSYS : -ETIMEDOUT;
	पूर्ण
	reinit_completion(&kim_gdata->kim_rcvd);
	/*
	 * the positions 12 & 13 in the response buffer provide with the
	 * chip, major & minor numbers
	 */

	version =
		MAKEWORD(kim_gdata->resp_buffer[12],
				kim_gdata->resp_buffer[13]);
	chip = (version & 0x7C00) >> 10;
	min_ver = (version & 0x007F);
	maj_ver = (version & 0x0380) >> 7;

	अगर (version & 0x8000)
		maj_ver |= 0x0008;

	प्र_लिखो(bts_scr_name, "ti-connectivity/TIInit_%d.%d.%d.bts",
		chip, maj_ver, min_ver);

	/* to be accessed later via sysfs entry */
	kim_gdata->version.full = version;
	kim_gdata->version.chip = chip;
	kim_gdata->version.maj_ver = maj_ver;
	kim_gdata->version.min_ver = min_ver;

	pr_info("%s", bts_scr_name);
	वापस 0;
पूर्ण

अटल व्योम skip_change_remote_baud(अचिन्हित अक्षर **ptr, दीर्घ *len)
अणु
	अचिन्हित अक्षर *nxt_action, *cur_action;
	cur_action = *ptr;

	nxt_action = cur_action + माप(काष्ठा bts_action) +
		((काष्ठा bts_action *) cur_action)->size;

	अगर (((काष्ठा bts_action *) nxt_action)->type != ACTION_WAIT_EVENT) अणु
		pr_err("invalid action after change remote baud command");
	पूर्ण अन्यथा अणु
		*ptr = *ptr + माप(काष्ठा bts_action) +
			((काष्ठा bts_action *)cur_action)->size;
		*len = *len - (माप(काष्ठा bts_action) +
				((काष्ठा bts_action *)cur_action)->size);
		/* warn user on not commenting these in firmware */
		pr_warn("skipping the wait event of change remote baud");
	पूर्ण
पूर्ण

/*
 * करोwnload_firmware -
 *	पूर्णांकernal function which parses through the .bts firmware
 *	script file पूर्णांकreprets SEND, DELAY actions only as of now
 */
अटल दीर्घ करोwnload_firmware(काष्ठा kim_data_s *kim_gdata)
अणु
	दीर्घ err = 0;
	दीर्घ len = 0;
	अचिन्हित अक्षर *ptr = शून्य;
	अचिन्हित अक्षर *action_ptr = शून्य;
	अचिन्हित अक्षर bts_scr_name[40] = अणु 0 पूर्ण;	/* 40 अक्षर दीर्घ bts scr name? */
	पूर्णांक wr_room_space;
	पूर्णांक cmd_size;
	अचिन्हित दीर्घ समयout;

	err = पढ़ो_local_version(kim_gdata, bts_scr_name);
	अगर (err != 0) अणु
		pr_err("kim: failed to read local ver");
		वापस err;
	पूर्ण
	err =
	    request_firmware(&kim_gdata->fw_entry, bts_scr_name,
			     &kim_gdata->kim_pdev->dev);
	अगर (unlikely((err != 0) || (kim_gdata->fw_entry->data == शून्य) ||
		     (kim_gdata->fw_entry->size == 0))) अणु
		pr_err(" request_firmware failed(errno %ld) for %s", err,
			   bts_scr_name);
		वापस -EINVAL;
	पूर्ण
	ptr = (व्योम *)kim_gdata->fw_entry->data;
	len = kim_gdata->fw_entry->size;
	/*
	 * bts_header to हटाओ out magic number and
	 * version
	 */
	ptr += माप(काष्ठा bts_header);
	len -= माप(काष्ठा bts_header);

	जबतक (len > 0 && ptr) अणु
		pr_debug(" action size %d, type %d ",
			   ((काष्ठा bts_action *)ptr)->size,
			   ((काष्ठा bts_action *)ptr)->type);

		चयन (((काष्ठा bts_action *)ptr)->type) अणु
		हाल ACTION_SEND_COMMAND:	/* action send */
			pr_debug("S");
			action_ptr = &(((काष्ठा bts_action *)ptr)->data[0]);
			अगर (unlikely
			    (((काष्ठा hci_command *)action_ptr)->opcode ==
			     0xFF36)) अणु
				/*
				 * ignore remote change
				 * baud rate HCI VS command
				 */
				pr_warn("change remote baud"
				    " rate command in firmware");
				skip_change_remote_baud(&ptr, &len);
				अवरोध;
			पूर्ण
			/*
			 * Make sure we have enough मुक्त space in uart
			 * tx buffer to ग_लिखो current firmware command
			 */
			cmd_size = ((काष्ठा bts_action *)ptr)->size;
			समयout = jअगरfies + msecs_to_jअगरfies(CMD_WR_TIME);
			करो अणु
				wr_room_space =
					st_get_uart_wr_room(kim_gdata->core_data);
				अगर (wr_room_space < 0) अणु
					pr_err("Unable to get free "
							"space info from uart tx buffer");
					release_firmware(kim_gdata->fw_entry);
					वापस wr_room_space;
				पूर्ण
				mdelay(1); /* रुको 1ms beक्रमe checking room */
			पूर्ण जबतक ((wr_room_space < cmd_size) &&
					समय_beक्रमe(jअगरfies, समयout));

			/* Timeout happened ? */
			अगर (समय_after_eq(jअगरfies, समयout)) अणु
				pr_err("Timeout while waiting for free "
						"free space in uart tx buffer");
				release_firmware(kim_gdata->fw_entry);
				वापस -ETIMEDOUT;
			पूर्ण
			/*
			 * reinit completion beक्रमe sending क्रम the
			 * relevant रुको
			 */
			reinit_completion(&kim_gdata->kim_rcvd);

			/*
			 * Free space found in uart buffer, call st_पूर्णांक_ग_लिखो
			 * to send current firmware command to the uart tx
			 * buffer.
			 */
			err = st_पूर्णांक_ग_लिखो(kim_gdata->core_data,
			((काष्ठा bts_action_send *)action_ptr)->data,
					   ((काष्ठा bts_action *)ptr)->size);
			अगर (unlikely(err < 0)) अणु
				release_firmware(kim_gdata->fw_entry);
				वापस err;
			पूर्ण
			/*
			 * Check number of bytes written to the uart tx buffer
			 * and requested command ग_लिखो size
			 */
			अगर (err != cmd_size) अणु
				pr_err("Number of bytes written to uart "
						"tx buffer are not matching with "
						"requested cmd write size");
				release_firmware(kim_gdata->fw_entry);
				वापस -EIO;
			पूर्ण
			अवरोध;
		हाल ACTION_WAIT_EVENT:  /* रुको */
			pr_debug("W");
			err = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
					&kim_gdata->kim_rcvd,
					msecs_to_jअगरfies(CMD_RESP_TIME));
			अगर (err <= 0) अणु
				pr_err("response timeout/signaled during fw download ");
				/* समयd out */
				release_firmware(kim_gdata->fw_entry);
				वापस err ? -ERESTARTSYS : -ETIMEDOUT;
			पूर्ण
			reinit_completion(&kim_gdata->kim_rcvd);
			अवरोध;
		हाल ACTION_DELAY:	/* sleep */
			pr_info("sleep command in scr");
			action_ptr = &(((काष्ठा bts_action *)ptr)->data[0]);
			mdelay(((काष्ठा bts_action_delay *)action_ptr)->msec);
			अवरोध;
		पूर्ण
		len =
		    len - (माप(काष्ठा bts_action) +
			   ((काष्ठा bts_action *)ptr)->size);
		ptr =
		    ptr + माप(काष्ठा bts_action) +
		    ((काष्ठा bts_action *)ptr)->size;
	पूर्ण
	/* fw करोwnload complete */
	release_firmware(kim_gdata->fw_entry);
	वापस 0;
पूर्ण

/**********************************************************************/
/* functions called from ST core */
/* called from ST Core, when REG_IN_PROGRESS (registration in progress)
 * can be because of
 * 1. response to पढ़ो local version
 * 2. during send/recv's of firmware करोwnload
 */
व्योम st_kim_recv(व्योम *disc_data, स्थिर अचिन्हित अक्षर *data, दीर्घ count)
अणु
	काष्ठा st_data_s	*st_gdata = (काष्ठा st_data_s *)disc_data;
	काष्ठा kim_data_s	*kim_gdata = st_gdata->kim_data;

	/*
	 * proceed to gather all data and distinguish पढ़ो fw version response
	 * from other fw responses when data gathering is complete
	 */
	kim_पूर्णांक_recv(kim_gdata, data, count);
	वापस;
पूर्ण

/*
 * to संकेत completion of line discipline installation
 * called from ST Core, upon tty_खोलो
 */
व्योम st_kim_complete(व्योम *kim_data)
अणु
	काष्ठा kim_data_s	*kim_gdata = (काष्ठा kim_data_s *)kim_data;
	complete(&kim_gdata->ldisc_installed);
पूर्ण

/*
 * st_kim_start - called from ST Core upon 1st registration
 *	This involves toggling the chip enable gpio, पढ़ोing
 *	the firmware version from chip, क्रमming the fw file name
 *	based on the chip version, requesting the fw, parsing it
 *	and perक्रमm करोwnload(send/recv).
 */
दीर्घ st_kim_start(व्योम *kim_data)
अणु
	दीर्घ err = 0;
	दीर्घ retry = POR_RETRY_COUNT;
	काष्ठा ti_st_plat_data	*pdata;
	काष्ठा kim_data_s	*kim_gdata = (काष्ठा kim_data_s *)kim_data;

	pr_info(" %s", __func__);
	pdata = kim_gdata->kim_pdev->dev.platक्रमm_data;

	करो अणु
		/* platक्रमm specअगरic enabling code here */
		अगर (pdata->chip_enable)
			pdata->chip_enable(kim_gdata);

		/* Configure BT nShutकरोwn to HIGH state */
		gpio_set_value_cansleep(kim_gdata->nshutकरोwn, GPIO_LOW);
		mdelay(5);	/* FIXME: a proper toggle */
		gpio_set_value_cansleep(kim_gdata->nshutकरोwn, GPIO_HIGH);
		mdelay(100);
		/* re-initialize the completion */
		reinit_completion(&kim_gdata->ldisc_installed);
		/* send notअगरication to UIM */
		kim_gdata->ldisc_install = 1;
		pr_info("ldisc_install = 1");
		sysfs_notअगरy(&kim_gdata->kim_pdev->dev.kobj,
				शून्य, "install");
		/* रुको क्रम ldisc to be installed */
		err = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&kim_gdata->ldisc_installed, msecs_to_jअगरfies(LDISC_TIME));
		अगर (!err) अणु
			/*
			 * ldisc installation समयout,
			 * flush uart, घातer cycle BT_EN
			 */
			pr_err("ldisc installation timeout");
			err = st_kim_stop(kim_gdata);
			जारी;
		पूर्ण अन्यथा अणु
			/* ldisc installed now */
			pr_info("line discipline installed");
			err = करोwnload_firmware(kim_gdata);
			अगर (err != 0) अणु
				/*
				 * ldisc installed but fw करोwnload failed,
				 * flush uart & घातer cycle BT_EN
				 */
				pr_err("download firmware failed");
				err = st_kim_stop(kim_gdata);
				जारी;
			पूर्ण अन्यथा अणु	/* on success करोn't retry */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (retry--);
	वापस err;
पूर्ण

/*
 * st_kim_stop - stop communication with chip.
 *	This can be called from ST Core/KIM, on the-
 *	(a) last un-रेजिस्टर when chip need not be घातered there-after,
 *	(b) upon failure to either install ldisc or करोwnload firmware.
 *	The function is responsible to (a) notअगरy UIM about un-installation,
 *	(b) flush UART अगर the ldisc was installed.
 *	(c) reset BT_EN - pull करोwn nshutकरोwn at the end.
 *	(d) invoke platक्रमm's chip disabling routine.
 */
दीर्घ st_kim_stop(व्योम *kim_data)
अणु
	दीर्घ err = 0;
	काष्ठा kim_data_s	*kim_gdata = (काष्ठा kim_data_s *)kim_data;
	काष्ठा ti_st_plat_data	*pdata =
		kim_gdata->kim_pdev->dev.platक्रमm_data;
	काष्ठा tty_काष्ठा	*tty = kim_gdata->core_data->tty;

	reinit_completion(&kim_gdata->ldisc_installed);

	अगर (tty) अणु	/* can be called beक्रमe ldisc is installed */
		/* Flush any pending अक्षरacters in the driver and discipline. */
		tty_ldisc_flush(tty);
		tty_driver_flush_buffer(tty);
	पूर्ण

	/* send uninstall notअगरication to UIM */
	pr_info("ldisc_install = 0");
	kim_gdata->ldisc_install = 0;
	sysfs_notअगरy(&kim_gdata->kim_pdev->dev.kobj, शून्य, "install");

	/* रुको क्रम ldisc to be un-installed */
	err = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&kim_gdata->ldisc_installed, msecs_to_jअगरfies(LDISC_TIME));
	अगर (!err) अणु		/* समयout */
		pr_err(" timed out waiting for ldisc to be un-installed");
		err = -ETIMEDOUT;
	पूर्ण

	/* By शेष configure BT nShutकरोwn to LOW state */
	gpio_set_value_cansleep(kim_gdata->nshutकरोwn, GPIO_LOW);
	mdelay(1);
	gpio_set_value_cansleep(kim_gdata->nshutकरोwn, GPIO_HIGH);
	mdelay(1);
	gpio_set_value_cansleep(kim_gdata->nshutकरोwn, GPIO_LOW);

	/* platक्रमm specअगरic disable */
	अगर (pdata->chip_disable)
		pdata->chip_disable(kim_gdata);
	वापस err;
पूर्ण

/**********************************************************************/
/* functions called from subप्रणालीs */
/* called when debugfs entry is पढ़ो from */

अटल पूर्णांक version_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा kim_data_s *kim_gdata = (काष्ठा kim_data_s *)s->निजी;
	seq_म_लिखो(s, "%04X %d.%d.%d\n", kim_gdata->version.full,
			kim_gdata->version.chip, kim_gdata->version.maj_ver,
			kim_gdata->version.min_ver);
	वापस 0;
पूर्ण

अटल पूर्णांक list_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा kim_data_s *kim_gdata = (काष्ठा kim_data_s *)s->निजी;
	kim_st_list_protocols(kim_gdata->core_data, s);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_install(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kim_data_s *kim_data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", kim_data->ldisc_install);
पूर्ण

#अगर_घोषित DEBUG
अटल sमाप_प्रकार store_dev_name(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kim_data_s *kim_data = dev_get_drvdata(dev);
	pr_debug("storing dev name >%s<", buf);
	म_नकलन(kim_data->dev_name, buf, count);
	pr_debug("stored dev name >%s<", kim_data->dev_name);
	वापस count;
पूर्ण

अटल sमाप_प्रकार store_baud_rate(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kim_data_s *kim_data = dev_get_drvdata(dev);
	pr_debug("storing baud rate >%s<", buf);
	माला_पूछो(buf, "%ld", &kim_data->baud_rate);
	pr_debug("stored baud rate >%ld<", kim_data->baud_rate);
	वापस count;
पूर्ण
#पूर्ण_अगर	/* अगर DEBUG */

अटल sमाप_प्रकार show_dev_name(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kim_data_s *kim_data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%s\n", kim_data->dev_name);
पूर्ण

अटल sमाप_प्रकार show_baud_rate(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kim_data_s *kim_data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", kim_data->baud_rate);
पूर्ण

अटल sमाप_प्रकार show_flow_cntrl(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kim_data_s *kim_data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", kim_data->flow_cntrl);
पूर्ण

/* काष्ठाures specअगरic क्रम sysfs entries */
अटल काष्ठा kobj_attribute ldisc_install =
__ATTR(install, 0444, (व्योम *)show_install, शून्य);

अटल काष्ठा kobj_attribute uart_dev_name =
#अगर_घोषित DEBUG	/* TODO: move this to debug-fs अगर possible */
__ATTR(dev_name, 0644, (व्योम *)show_dev_name, (व्योम *)store_dev_name);
#अन्यथा
__ATTR(dev_name, 0444, (व्योम *)show_dev_name, शून्य);
#पूर्ण_अगर

अटल काष्ठा kobj_attribute uart_baud_rate =
#अगर_घोषित DEBUG	/* TODO: move to debugfs */
__ATTR(baud_rate, 0644, (व्योम *)show_baud_rate, (व्योम *)store_baud_rate);
#अन्यथा
__ATTR(baud_rate, 0444, (व्योम *)show_baud_rate, शून्य);
#पूर्ण_अगर

अटल काष्ठा kobj_attribute uart_flow_cntrl =
__ATTR(flow_cntrl, 0444, (व्योम *)show_flow_cntrl, शून्य);

अटल काष्ठा attribute *uim_attrs[] = अणु
	&ldisc_install.attr,
	&uart_dev_name.attr,
	&uart_baud_rate.attr,
	&uart_flow_cntrl.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group uim_attr_grp = अणु
	.attrs = uim_attrs,
पूर्ण;

/*
 * st_kim_ref - reference the core's data
 *	This references the per-ST platक्रमm device in the arch/xx/
 *	board-xx.c file.
 *	This would enable multiple such platक्रमm devices to exist
 *	on a given platक्रमm
 */
व्योम st_kim_ref(काष्ठा st_data_s **core_data, पूर्णांक id)
अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा kim_data_s	*kim_gdata;
	/* get kim_gdata reference from platक्रमm device */
	pdev = st_get_plat_device(id);
	अगर (!pdev)
		जाओ err;
	kim_gdata = platक्रमm_get_drvdata(pdev);
	अगर (!kim_gdata)
		जाओ err;

	*core_data = kim_gdata->core_data;
	वापस;
err:
	*core_data = शून्य;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(version);
DEFINE_SHOW_ATTRIBUTE(list);

/**********************************************************************/
/* functions called from platक्रमm device driver subप्रणाली
 * need to have a relevant platक्रमm device entry in the platक्रमm's
 * board-*.c file
 */

अटल काष्ठा dentry *kim_debugfs_dir;
अटल पूर्णांक kim_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kim_data_s	*kim_gdata;
	काष्ठा ti_st_plat_data	*pdata = pdev->dev.platक्रमm_data;
	पूर्णांक err;

	अगर ((pdev->id != -1) && (pdev->id < MAX_ST_DEVICES)) अणु
		/* multiple devices could exist */
		st_kim_devices[pdev->id] = pdev;
	पूर्ण अन्यथा अणु
		/* platक्रमm's sure about existence of 1 device */
		st_kim_devices[0] = pdev;
	पूर्ण

	kim_gdata = kzalloc(माप(काष्ठा kim_data_s), GFP_KERNEL);
	अगर (!kim_gdata) अणु
		pr_err("no mem to allocate");
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(pdev, kim_gdata);

	err = st_core_init(&kim_gdata->core_data);
	अगर (err != 0) अणु
		pr_err(" ST core init failed");
		err = -EIO;
		जाओ err_core_init;
	पूर्ण
	/* refer to itself */
	kim_gdata->core_data->kim_data = kim_gdata;

	/* Claim the chip enable nShutकरोwn gpio from the प्रणाली */
	kim_gdata->nshutकरोwn = pdata->nshutकरोwn_gpio;
	err = gpio_request(kim_gdata->nshutकरोwn, "kim");
	अगर (unlikely(err)) अणु
		pr_err(" gpio %d request failed ", kim_gdata->nshutकरोwn);
		जाओ err_sysfs_group;
	पूर्ण

	/* Configure nShutकरोwn GPIO as output=0 */
	err = gpio_direction_output(kim_gdata->nshutकरोwn, 0);
	अगर (unlikely(err)) अणु
		pr_err(" unable to configure gpio %d", kim_gdata->nshutकरोwn);
		जाओ err_sysfs_group;
	पूर्ण
	/* get reference of pdev क्रम request_firmware */
	kim_gdata->kim_pdev = pdev;
	init_completion(&kim_gdata->kim_rcvd);
	init_completion(&kim_gdata->ldisc_installed);

	err = sysfs_create_group(&pdev->dev.kobj, &uim_attr_grp);
	अगर (err) अणु
		pr_err("failed to create sysfs entries");
		जाओ err_sysfs_group;
	पूर्ण

	/* copying platक्रमm data */
	म_नकलन(kim_gdata->dev_name, pdata->dev_name, UART_DEV_NAME_LEN);
	kim_gdata->flow_cntrl = pdata->flow_cntrl;
	kim_gdata->baud_rate = pdata->baud_rate;
	pr_info("sysfs entries created\n");

	kim_debugfs_dir = debugfs_create_dir("ti-st", शून्य);

	debugfs_create_file("version", S_IRUGO, kim_debugfs_dir,
				kim_gdata, &version_fops);
	debugfs_create_file("protocols", S_IRUGO, kim_debugfs_dir,
				kim_gdata, &list_fops);
	वापस 0;

err_sysfs_group:
	st_core_निकास(kim_gdata->core_data);

err_core_init:
	kमुक्त(kim_gdata);

	वापस err;
पूर्ण

अटल पूर्णांक kim_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* मुक्त the GPIOs requested */
	काष्ठा ti_st_plat_data	*pdata = pdev->dev.platक्रमm_data;
	काष्ठा kim_data_s	*kim_gdata;

	kim_gdata = platक्रमm_get_drvdata(pdev);

	/*
	 * Free the Bluetooth/FM/GPIO
	 * nShutकरोwn gpio from the प्रणाली
	 */
	gpio_मुक्त(pdata->nshutकरोwn_gpio);
	pr_info("nshutdown GPIO Freed");

	debugfs_हटाओ_recursive(kim_debugfs_dir);
	sysfs_हटाओ_group(&pdev->dev.kobj, &uim_attr_grp);
	pr_info("sysfs entries removed");

	kim_gdata->kim_pdev = शून्य;
	st_core_निकास(kim_gdata->core_data);

	kमुक्त(kim_gdata);
	kim_gdata = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक kim_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा ti_st_plat_data	*pdata = pdev->dev.platक्रमm_data;

	अगर (pdata->suspend)
		वापस pdata->suspend(pdev, state);

	वापस 0;
पूर्ण

अटल पूर्णांक kim_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_st_plat_data	*pdata = pdev->dev.platक्रमm_data;

	अगर (pdata->resume)
		वापस pdata->resume(pdev);

	वापस 0;
पूर्ण

/**********************************************************************/
/* entry poपूर्णांक क्रम ST KIM module, called in from ST Core */
अटल काष्ठा platक्रमm_driver kim_platक्रमm_driver = अणु
	.probe = kim_probe,
	.हटाओ = kim_हटाओ,
	.suspend = kim_suspend,
	.resume = kim_resume,
	.driver = अणु
		.name = "kim",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(kim_platक्रमm_driver);

MODULE_AUTHOR("Pavan Savoy <pavan_savoy@ti.com>");
MODULE_DESCRIPTION("Shared Transport Driver for TI BT/FM/GPS combo chips ");
MODULE_LICENSE("GPL");
