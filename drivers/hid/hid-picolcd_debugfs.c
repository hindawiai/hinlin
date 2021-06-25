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

#समावेश <linux/fb.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>

#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

#समावेश "hid-picolcd.h"


अटल पूर्णांक picolcd_debug_reset_show(काष्ठा seq_file *f, व्योम *p)
अणु
	अगर (picolcd_fbinfo((काष्ठा picolcd_data *)f->निजी))
		seq_म_लिखो(f, "all fb\n");
	अन्यथा
		seq_म_लिखो(f, "all\n");
	वापस 0;
पूर्ण

अटल पूर्णांक picolcd_debug_reset_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	वापस single_खोलो(f, picolcd_debug_reset_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार picolcd_debug_reset_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *user_buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा picolcd_data *data = ((काष्ठा seq_file *)f->निजी_data)->निजी;
	अक्षर buf[32];
	माप_प्रकार cnt = min(count, माप(buf)-1);
	अगर (copy_from_user(buf, user_buf, cnt))
		वापस -EFAULT;

	जबतक (cnt > 0 && (buf[cnt-1] == ' ' || buf[cnt-1] == '\n'))
		cnt--;
	buf[cnt] = '\0';
	अगर (म_भेद(buf, "all") == 0) अणु
		picolcd_reset(data->hdev);
		picolcd_fb_reset(data, 1);
	पूर्ण अन्यथा अगर (म_भेद(buf, "fb") == 0) अणु
		picolcd_fb_reset(data, 1);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations picolcd_debug_reset_fops = अणु
	.owner    = THIS_MODULE,
	.खोलो     = picolcd_debug_reset_खोलो,
	.पढ़ो     = seq_पढ़ो,
	.llseek   = seq_lseek,
	.ग_लिखो    = picolcd_debug_reset_ग_लिखो,
	.release  = single_release,
पूर्ण;

/*
 * The "eeprom" file
 */
अटल sमाप_प्रकार picolcd_debug_eeprom_पढ़ो(काष्ठा file *f, अक्षर __user *u,
		माप_प्रकार s, loff_t *off)
अणु
	काष्ठा picolcd_data *data = f->निजी_data;
	काष्ठा picolcd_pending *resp;
	u8 raw_data[3];
	sमाप_प्रकार ret = -EIO;

	अगर (s == 0)
		वापस -EINVAL;
	अगर (*off > 0x0ff)
		वापस 0;

	/* prepare buffer with info about what we want to पढ़ो (addr & len) */
	raw_data[0] = *off & 0xff;
	raw_data[1] = (*off >> 8) & 0xff;
	raw_data[2] = s < 20 ? s : 20;
	अगर (*off + raw_data[2] > 0xff)
		raw_data[2] = 0x100 - *off;
	resp = picolcd_send_and_रुको(data->hdev, REPORT_EE_READ, raw_data,
			माप(raw_data));
	अगर (!resp)
		वापस -EIO;

	अगर (resp->in_report && resp->in_report->id == REPORT_EE_DATA) अणु
		/* successful पढ़ो :) */
		ret = resp->raw_data[2];
		अगर (ret > s)
			ret = s;
		अगर (copy_to_user(u, resp->raw_data+3, ret))
			ret = -EFAULT;
		अन्यथा
			*off += ret;
	पूर्ण /* anything अन्यथा is some kind of IO error */

	kमुक्त(resp);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार picolcd_debug_eeprom_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *u,
		माप_प्रकार s, loff_t *off)
अणु
	काष्ठा picolcd_data *data = f->निजी_data;
	काष्ठा picolcd_pending *resp;
	sमाप_प्रकार ret = -EIO;
	u8 raw_data[23];

	अगर (s == 0)
		वापस -EINVAL;
	अगर (*off > 0x0ff)
		वापस -ENOSPC;

	स_रखो(raw_data, 0, माप(raw_data));
	raw_data[0] = *off & 0xff;
	raw_data[1] = (*off >> 8) & 0xff;
	raw_data[2] = min_t(माप_प्रकार, 20, s);
	अगर (*off + raw_data[2] > 0xff)
		raw_data[2] = 0x100 - *off;

	अगर (copy_from_user(raw_data+3, u, min((u8)20, raw_data[2])))
		वापस -EFAULT;
	resp = picolcd_send_and_रुको(data->hdev, REPORT_EE_WRITE, raw_data,
			माप(raw_data));

	अगर (!resp)
		वापस -EIO;

	अगर (resp->in_report && resp->in_report->id == REPORT_EE_DATA) अणु
		/* check अगर written data matches */
		अगर (स_भेद(raw_data, resp->raw_data, 3+raw_data[2]) == 0) अणु
			*off += raw_data[2];
			ret = raw_data[2];
		पूर्ण
	पूर्ण
	kमुक्त(resp);
	वापस ret;
पूर्ण

/*
 * Notes:
 * - पढ़ो/ग_लिखो happens in chunks of at most 20 bytes, it's up to userspace
 *   to loop in order to get more data.
 * - on ग_लिखो errors on otherwise correct ग_लिखो request the bytes
 *   that should have been written are in undefined state.
 */
अटल स्थिर काष्ठा file_operations picolcd_debug_eeprom_fops = अणु
	.owner    = THIS_MODULE,
	.खोलो     = simple_खोलो,
	.पढ़ो     = picolcd_debug_eeprom_पढ़ो,
	.ग_लिखो    = picolcd_debug_eeprom_ग_लिखो,
	.llseek   = generic_file_llseek,
पूर्ण;

/*
 * The "flash" file
 */
/* record a flash address to buf (bounds check to be करोne by caller) */
अटल पूर्णांक _picolcd_flash_setaddr(काष्ठा picolcd_data *data, u8 *buf, दीर्घ off)
अणु
	buf[0] = off & 0xff;
	buf[1] = (off >> 8) & 0xff;
	अगर (data->addr_sz == 3)
		buf[2] = (off >> 16) & 0xff;
	वापस data->addr_sz == 2 ? 2 : 3;
पूर्ण

/* पढ़ो a given size of data (bounds check to be करोne by caller) */
अटल sमाप_प्रकार _picolcd_flash_पढ़ो(काष्ठा picolcd_data *data, पूर्णांक report_id,
		अक्षर __user *u, माप_प्रकार s, loff_t *off)
अणु
	काष्ठा picolcd_pending *resp;
	u8 raw_data[4];
	sमाप_प्रकार ret = 0;
	पूर्णांक len_off, err = -EIO;

	जबतक (s > 0) अणु
		err = -EIO;
		len_off = _picolcd_flash_setaddr(data, raw_data, *off);
		raw_data[len_off] = s > 32 ? 32 : s;
		resp = picolcd_send_and_रुको(data->hdev, report_id, raw_data, len_off+1);
		अगर (!resp || !resp->in_report)
			जाओ skip;
		अगर (resp->in_report->id == REPORT_MEMORY ||
			resp->in_report->id == REPORT_BL_READ_MEMORY) अणु
			अगर (स_भेद(raw_data, resp->raw_data, len_off+1) != 0)
				जाओ skip;
			अगर (copy_to_user(u+ret, resp->raw_data+len_off+1, raw_data[len_off])) अणु
				err = -EFAULT;
				जाओ skip;
			पूर्ण
			*off += raw_data[len_off];
			s    -= raw_data[len_off];
			ret  += raw_data[len_off];
			err   = 0;
		पूर्ण
skip:
		kमुक्त(resp);
		अगर (err)
			वापस ret > 0 ? ret : err;
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार picolcd_debug_flash_पढ़ो(काष्ठा file *f, अक्षर __user *u,
		माप_प्रकार s, loff_t *off)
अणु
	काष्ठा picolcd_data *data = f->निजी_data;

	अगर (s == 0)
		वापस -EINVAL;
	अगर (*off > 0x05fff)
		वापस 0;
	अगर (*off + s > 0x05fff)
		s = 0x06000 - *off;

	अगर (data->status & PICOLCD_BOOTLOADER)
		वापस _picolcd_flash_पढ़ो(data, REPORT_BL_READ_MEMORY, u, s, off);
	अन्यथा
		वापस _picolcd_flash_पढ़ो(data, REPORT_READ_MEMORY, u, s, off);
पूर्ण

/* erase block aligned to 64bytes boundary */
अटल sमाप_प्रकार _picolcd_flash_erase64(काष्ठा picolcd_data *data, पूर्णांक report_id,
		loff_t *off)
अणु
	काष्ठा picolcd_pending *resp;
	u8 raw_data[3];
	पूर्णांक len_off;
	sमाप_प्रकार ret = -EIO;

	अगर (*off & 0x3f)
		वापस -EINVAL;

	len_off = _picolcd_flash_setaddr(data, raw_data, *off);
	resp = picolcd_send_and_रुको(data->hdev, report_id, raw_data, len_off);
	अगर (!resp || !resp->in_report)
		जाओ skip;
	अगर (resp->in_report->id == REPORT_MEMORY ||
		resp->in_report->id == REPORT_BL_ERASE_MEMORY) अणु
		अगर (स_भेद(raw_data, resp->raw_data, len_off) != 0)
			जाओ skip;
		ret = 0;
	पूर्ण
skip:
	kमुक्त(resp);
	वापस ret;
पूर्ण

/* ग_लिखो a given size of data (bounds check to be करोne by caller) */
अटल sमाप_प्रकार _picolcd_flash_ग_लिखो(काष्ठा picolcd_data *data, पूर्णांक report_id,
		स्थिर अक्षर __user *u, माप_प्रकार s, loff_t *off)
अणु
	काष्ठा picolcd_pending *resp;
	u8 raw_data[36];
	sमाप_प्रकार ret = 0;
	पूर्णांक len_off, err = -EIO;

	जबतक (s > 0) अणु
		err = -EIO;
		len_off = _picolcd_flash_setaddr(data, raw_data, *off);
		raw_data[len_off] = s > 32 ? 32 : s;
		अगर (copy_from_user(raw_data+len_off+1, u, raw_data[len_off])) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		resp = picolcd_send_and_रुको(data->hdev, report_id, raw_data,
				len_off+1+raw_data[len_off]);
		अगर (!resp || !resp->in_report)
			जाओ skip;
		अगर (resp->in_report->id == REPORT_MEMORY ||
			resp->in_report->id == REPORT_BL_WRITE_MEMORY) अणु
			अगर (स_भेद(raw_data, resp->raw_data, len_off+1+raw_data[len_off]) != 0)
				जाओ skip;
			*off += raw_data[len_off];
			s    -= raw_data[len_off];
			ret  += raw_data[len_off];
			err   = 0;
		पूर्ण
skip:
		kमुक्त(resp);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस ret > 0 ? ret : err;
पूर्ण

अटल sमाप_प्रकार picolcd_debug_flash_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *u,
		माप_प्रकार s, loff_t *off)
अणु
	काष्ठा picolcd_data *data = f->निजी_data;
	sमाप_प्रकार err, ret = 0;
	पूर्णांक report_erase, report_ग_लिखो;

	अगर (s == 0)
		वापस -EINVAL;
	अगर (*off > 0x5fff)
		वापस -ENOSPC;
	अगर (s & 0x3f)
		वापस -EINVAL;
	अगर (*off & 0x3f)
		वापस -EINVAL;

	अगर (data->status & PICOLCD_BOOTLOADER) अणु
		report_erase = REPORT_BL_ERASE_MEMORY;
		report_ग_लिखो = REPORT_BL_WRITE_MEMORY;
	पूर्ण अन्यथा अणु
		report_erase = REPORT_ERASE_MEMORY;
		report_ग_लिखो = REPORT_WRITE_MEMORY;
	पूर्ण
	mutex_lock(&data->mutex_flash);
	जबतक (s > 0) अणु
		err = _picolcd_flash_erase64(data, report_erase, off);
		अगर (err)
			अवरोध;
		err = _picolcd_flash_ग_लिखो(data, report_ग_लिखो, u, 64, off);
		अगर (err < 0)
			अवरोध;
		ret += err;
		*off += err;
		s -= err;
		अगर (err != 64)
			अवरोध;
	पूर्ण
	mutex_unlock(&data->mutex_flash);
	वापस ret > 0 ? ret : err;
पूर्ण

/*
 * Notes:
 * - concurrent writing is prevented by mutex and all ग_लिखोs must be
 *   n*64 bytes and 64-byte aligned, each ग_लिखो being preceded by an
 *   ERASE which erases a 64byte block.
 *   If less than requested was written or an error is वापसed क्रम an
 *   otherwise correct ग_लिखो request the next 64-byte block which should
 *   have been written is in undefined state (mostly: original, erased,
 *   (half-)written with ग_लिखो error)
 * - पढ़ोing can happen without special restriction
 */
अटल स्थिर काष्ठा file_operations picolcd_debug_flash_fops = अणु
	.owner    = THIS_MODULE,
	.खोलो     = simple_खोलो,
	.पढ़ो     = picolcd_debug_flash_पढ़ो,
	.ग_लिखो    = picolcd_debug_flash_ग_लिखो,
	.llseek   = generic_file_llseek,
पूर्ण;


/*
 * Helper code क्रम HID report level dumping/debugging
 */
अटल स्थिर अक्षर * स्थिर error_codes[] = अणु
	"success", "parameter missing", "data_missing", "block readonly",
	"block not erasable", "block too big", "section overflow",
	"invalid command length", "invalid data length",
पूर्ण;

अटल व्योम dump_buff_as_hex(अक्षर *dst, माप_प्रकार dst_sz, स्थिर u8 *data,
		स्थिर माप_प्रकार data_len)
अणु
	पूर्णांक i, j;
	क्रम (i = j = 0; i < data_len && j + 4 < dst_sz; i++) अणु
		dst[j++] = hex_asc[(data[i] >> 4) & 0x0f];
		dst[j++] = hex_asc[data[i] & 0x0f];
		dst[j++] = ' ';
	पूर्ण
	dst[j]   = '\0';
	अगर (j > 0)
		dst[j-1] = '\n';
	अगर (i < data_len && j > 2)
		dst[j-2] = dst[j-3] = '.';
पूर्ण

व्योम picolcd_debug_out_report(काष्ठा picolcd_data *data,
		काष्ठा hid_device *hdev, काष्ठा hid_report *report)
अणु
	u8 *raw_data;
	पूर्णांक raw_size = (report->size >> 3) + 1;
	अक्षर *buff;
#घोषणा BUFF_SZ 256

	/* Aव्योम unnecessary overhead अगर debugfs is disabled */
	अगर (list_empty(&hdev->debug_list))
		वापस;

	buff = kदो_स्मृति(BUFF_SZ, GFP_ATOMIC);
	अगर (!buff)
		वापस;

	raw_data = hid_alloc_report_buf(report, GFP_ATOMIC);
	अगर (!raw_data) अणु
		kमुक्त(buff);
		वापस;
	पूर्ण

	snम_लिखो(buff, BUFF_SZ, "\nout report %d (size %d) =  ",
			report->id, raw_size);
	hid_debug_event(hdev, buff);
	raw_data[0] = report->id;
	hid_output_report(report, raw_data);
	dump_buff_as_hex(buff, BUFF_SZ, raw_data, raw_size);
	hid_debug_event(hdev, buff);

	चयन (report->id) अणु
	हाल REPORT_LED_STATE:
		/* 1 data byte with GPO state */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_LED_STATE", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tGPO state: 0x%02x\n", raw_data[1]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_BRIGHTNESS:
		/* 1 data byte with brightness */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_BRIGHTNESS", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tBrightness: 0x%02x\n", raw_data[1]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_CONTRAST:
		/* 1 data byte with contrast */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_CONTRAST", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tContrast: 0x%02x\n", raw_data[1]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_RESET:
		/* 2 data bytes with reset duration in ms */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_RESET", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tDuration: 0x%02x%02x (%dms)\n",
				raw_data[2], raw_data[1], raw_data[2] << 8 | raw_data[1]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_LCD_CMD:
		/* 63 data bytes with LCD commands */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_LCD_CMD", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		/* TODO: क्रमmat decoding */
		अवरोध;
	हाल REPORT_LCD_DATA:
		/* 63 data bytes with LCD data */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_LCD_CMD", report->id, raw_size-1);
		/* TODO: क्रमmat decoding */
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_LCD_CMD_DATA:
		/* 63 data bytes with LCD commands and data */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_LCD_CMD", report->id, raw_size-1);
		/* TODO: क्रमmat decoding */
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_EE_READ:
		/* 3 data bytes with पढ़ो area description */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_EE_READ", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tData address: 0x%02x%02x\n",
				raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n", raw_data[3]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_EE_WRITE:
		/* 3+1..20 data bytes with ग_लिखो area description */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_EE_WRITE", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tData address: 0x%02x%02x\n",
				raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n", raw_data[3]);
		hid_debug_event(hdev, buff);
		अगर (raw_data[3] == 0) अणु
			snम_लिखो(buff, BUFF_SZ, "\tNo data\n");
		पूर्ण अन्यथा अगर (raw_data[3] + 4 <= raw_size) अणु
			snम_लिखो(buff, BUFF_SZ, "\tData: ");
			hid_debug_event(hdev, buff);
			dump_buff_as_hex(buff, BUFF_SZ, raw_data+4, raw_data[3]);
		पूर्ण अन्यथा अणु
			snम_लिखो(buff, BUFF_SZ, "\tData overflowed\n");
		पूर्ण
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_ERASE_MEMORY:
	हाल REPORT_BL_ERASE_MEMORY:
		/* 3 data bytes with poपूर्णांकer inside erase block */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_ERASE_MEMORY", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		चयन (data->addr_sz) अणु
		हाल 2:
			snम_लिखो(buff, BUFF_SZ, "\tAddress inside 64 byte block: 0x%02x%02x\n",
					raw_data[2], raw_data[1]);
			अवरोध;
		हाल 3:
			snम_लिखो(buff, BUFF_SZ, "\tAddress inside 64 byte block: 0x%02x%02x%02x\n",
					raw_data[3], raw_data[2], raw_data[1]);
			अवरोध;
		शेष:
			snम_लिखो(buff, BUFF_SZ, "\tNot supported\n");
		पूर्ण
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_READ_MEMORY:
	हाल REPORT_BL_READ_MEMORY:
		/* 4 data bytes with पढ़ो area description */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_READ_MEMORY", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		चयन (data->addr_sz) अणु
		हाल 2:
			snम_लिखो(buff, BUFF_SZ, "\tData address: 0x%02x%02x\n",
					raw_data[2], raw_data[1]);
			hid_debug_event(hdev, buff);
			snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n", raw_data[3]);
			अवरोध;
		हाल 3:
			snम_लिखो(buff, BUFF_SZ, "\tData address: 0x%02x%02x%02x\n",
					raw_data[3], raw_data[2], raw_data[1]);
			hid_debug_event(hdev, buff);
			snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n", raw_data[4]);
			अवरोध;
		शेष:
			snम_लिखो(buff, BUFF_SZ, "\tNot supported\n");
		पूर्ण
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_WRITE_MEMORY:
	हाल REPORT_BL_WRITE_MEMORY:
		/* 4+1..32 data bytes with ग_लिखो adrea description */
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_WRITE_MEMORY", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		चयन (data->addr_sz) अणु
		हाल 2:
			snम_लिखो(buff, BUFF_SZ, "\tData address: 0x%02x%02x\n",
					raw_data[2], raw_data[1]);
			hid_debug_event(hdev, buff);
			snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n", raw_data[3]);
			hid_debug_event(hdev, buff);
			अगर (raw_data[3] == 0) अणु
				snम_लिखो(buff, BUFF_SZ, "\tNo data\n");
			पूर्ण अन्यथा अगर (raw_data[3] + 4 <= raw_size) अणु
				snम_लिखो(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, raw_data+4, raw_data[3]);
			पूर्ण अन्यथा अणु
				snम_लिखो(buff, BUFF_SZ, "\tData overflowed\n");
			पूर्ण
			अवरोध;
		हाल 3:
			snम_लिखो(buff, BUFF_SZ, "\tData address: 0x%02x%02x%02x\n",
					raw_data[3], raw_data[2], raw_data[1]);
			hid_debug_event(hdev, buff);
			snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n", raw_data[4]);
			hid_debug_event(hdev, buff);
			अगर (raw_data[4] == 0) अणु
				snम_लिखो(buff, BUFF_SZ, "\tNo data\n");
			पूर्ण अन्यथा अगर (raw_data[4] + 5 <= raw_size) अणु
				snम_लिखो(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, raw_data+5, raw_data[4]);
			पूर्ण अन्यथा अणु
				snम_लिखो(buff, BUFF_SZ, "\tData overflowed\n");
			पूर्ण
			अवरोध;
		शेष:
			snम_लिखो(buff, BUFF_SZ, "\tNot supported\n");
		पूर्ण
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_SPLASH_RESTART:
		/* TODO */
		अवरोध;
	हाल REPORT_EXIT_KEYBOARD:
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_EXIT_KEYBOARD", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tRestart delay: %dms (0x%02x%02x)\n",
				raw_data[1] | (raw_data[2] << 8),
				raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_VERSION:
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_VERSION", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_DEVID:
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_DEVID", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_SPLASH_SIZE:
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_SPLASH_SIZE", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_HOOK_VERSION:
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_HOOK_VERSION", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_EXIT_FLASHER:
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"REPORT_VERSION", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tRestart delay: %dms (0x%02x%02x)\n",
				raw_data[1] | (raw_data[2] << 8),
				raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		अवरोध;
	शेष:
		snम_लिखो(buff, BUFF_SZ, "out report %s (%d, size=%d)\n",
			"<unknown>", report->id, raw_size-1);
		hid_debug_event(hdev, buff);
		अवरोध;
	पूर्ण
	wake_up_पूर्णांकerruptible(&hdev->debug_रुको);
	kमुक्त(raw_data);
	kमुक्त(buff);
पूर्ण

व्योम picolcd_debug_raw_event(काष्ठा picolcd_data *data,
		काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *raw_data, पूर्णांक size)
अणु
	अक्षर *buff;

#घोषणा BUFF_SZ 256
	/* Aव्योम unnecessary overhead अगर debugfs is disabled */
	अगर (list_empty(&hdev->debug_list))
		वापस;

	buff = kदो_स्मृति(BUFF_SZ, GFP_ATOMIC);
	अगर (!buff)
		वापस;

	चयन (report->id) अणु
	हाल REPORT_ERROR_CODE:
		/* 2 data bytes with affected report and error code */
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_ERROR_CODE", report->id, size-1);
		hid_debug_event(hdev, buff);
		अगर (raw_data[2] < ARRAY_SIZE(error_codes))
			snम_लिखो(buff, BUFF_SZ, "\tError code 0x%02x (%s) in reply to report 0x%02x\n",
					raw_data[2], error_codes[raw_data[2]], raw_data[1]);
		अन्यथा
			snम_लिखो(buff, BUFF_SZ, "\tError code 0x%02x in reply to report 0x%02x\n",
					raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_KEY_STATE:
		/* 2 data bytes with key state */
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_KEY_STATE", report->id, size-1);
		hid_debug_event(hdev, buff);
		अगर (raw_data[1] == 0)
			snम_लिखो(buff, BUFF_SZ, "\tNo key pressed\n");
		अन्यथा अगर (raw_data[2] == 0)
			snम_लिखो(buff, BUFF_SZ, "\tOne key pressed: 0x%02x (%d)\n",
					raw_data[1], raw_data[1]);
		अन्यथा
			snम_लिखो(buff, BUFF_SZ, "\tTwo keys pressed: 0x%02x (%d), 0x%02x (%d)\n",
					raw_data[1], raw_data[1], raw_data[2], raw_data[2]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_IR_DATA:
		/* Up to 20 byes of IR scancode data */
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_IR_DATA", report->id, size-1);
		hid_debug_event(hdev, buff);
		अगर (raw_data[1] == 0) अणु
			snम_लिखो(buff, BUFF_SZ, "\tUnexpectedly 0 data length\n");
			hid_debug_event(hdev, buff);
		पूर्ण अन्यथा अगर (raw_data[1] + 1 <= size) अणु
			snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n\tIR Data: ",
					raw_data[1]);
			hid_debug_event(hdev, buff);
			dump_buff_as_hex(buff, BUFF_SZ, raw_data+2, raw_data[1]);
			hid_debug_event(hdev, buff);
		पूर्ण अन्यथा अणु
			snम_लिखो(buff, BUFF_SZ, "\tOverflowing data length: %d\n",
					raw_data[1]-1);
			hid_debug_event(hdev, buff);
		पूर्ण
		अवरोध;
	हाल REPORT_EE_DATA:
		/* Data buffer in response to REPORT_EE_READ or REPORT_EE_WRITE */
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_EE_DATA", report->id, size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tData address: 0x%02x%02x\n",
				raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n", raw_data[3]);
		hid_debug_event(hdev, buff);
		अगर (raw_data[3] == 0) अणु
			snम_लिखो(buff, BUFF_SZ, "\tNo data\n");
			hid_debug_event(hdev, buff);
		पूर्ण अन्यथा अगर (raw_data[3] + 4 <= size) अणु
			snम_लिखो(buff, BUFF_SZ, "\tData: ");
			hid_debug_event(hdev, buff);
			dump_buff_as_hex(buff, BUFF_SZ, raw_data+4, raw_data[3]);
			hid_debug_event(hdev, buff);
		पूर्ण अन्यथा अणु
			snम_लिखो(buff, BUFF_SZ, "\tData overflowed\n");
			hid_debug_event(hdev, buff);
		पूर्ण
		अवरोध;
	हाल REPORT_MEMORY:
		/* Data buffer in response to REPORT_READ_MEMORY or REPORT_WRITE_MEMORY */
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_MEMORY", report->id, size-1);
		hid_debug_event(hdev, buff);
		चयन (data->addr_sz) अणु
		हाल 2:
			snम_लिखो(buff, BUFF_SZ, "\tData address: 0x%02x%02x\n",
					raw_data[2], raw_data[1]);
			hid_debug_event(hdev, buff);
			snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n", raw_data[3]);
			hid_debug_event(hdev, buff);
			अगर (raw_data[3] == 0) अणु
				snम_लिखो(buff, BUFF_SZ, "\tNo data\n");
			पूर्ण अन्यथा अगर (raw_data[3] + 4 <= size) अणु
				snम_लिखो(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, raw_data+4, raw_data[3]);
			पूर्ण अन्यथा अणु
				snम_लिखो(buff, BUFF_SZ, "\tData overflowed\n");
			पूर्ण
			अवरोध;
		हाल 3:
			snम_लिखो(buff, BUFF_SZ, "\tData address: 0x%02x%02x%02x\n",
					raw_data[3], raw_data[2], raw_data[1]);
			hid_debug_event(hdev, buff);
			snम_लिखो(buff, BUFF_SZ, "\tData length: %d\n", raw_data[4]);
			hid_debug_event(hdev, buff);
			अगर (raw_data[4] == 0) अणु
				snम_लिखो(buff, BUFF_SZ, "\tNo data\n");
			पूर्ण अन्यथा अगर (raw_data[4] + 5 <= size) अणु
				snम_लिखो(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, raw_data+5, raw_data[4]);
			पूर्ण अन्यथा अणु
				snम_लिखो(buff, BUFF_SZ, "\tData overflowed\n");
			पूर्ण
			अवरोध;
		शेष:
			snम_लिखो(buff, BUFF_SZ, "\tNot supported\n");
		पूर्ण
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_VERSION:
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_VERSION", report->id, size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tFirmware version: %d.%d\n",
				raw_data[2], raw_data[1]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_BL_ERASE_MEMORY:
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_BL_ERASE_MEMORY", report->id, size-1);
		hid_debug_event(hdev, buff);
		/* TODO */
		अवरोध;
	हाल REPORT_BL_READ_MEMORY:
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_BL_READ_MEMORY", report->id, size-1);
		hid_debug_event(hdev, buff);
		/* TODO */
		अवरोध;
	हाल REPORT_BL_WRITE_MEMORY:
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_BL_WRITE_MEMORY", report->id, size-1);
		hid_debug_event(hdev, buff);
		/* TODO */
		अवरोध;
	हाल REPORT_DEVID:
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_DEVID", report->id, size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tSerial: 0x%02x%02x%02x%02x\n",
				raw_data[1], raw_data[2], raw_data[3], raw_data[4]);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tType: 0x%02x\n",
				raw_data[5]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_SPLASH_SIZE:
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_SPLASH_SIZE", report->id, size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tTotal splash space: %d\n",
				(raw_data[2] << 8) | raw_data[1]);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tUsed splash space: %d\n",
				(raw_data[4] << 8) | raw_data[3]);
		hid_debug_event(hdev, buff);
		अवरोध;
	हाल REPORT_HOOK_VERSION:
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"REPORT_HOOK_VERSION", report->id, size-1);
		hid_debug_event(hdev, buff);
		snम_लिखो(buff, BUFF_SZ, "\tFirmware version: %d.%d\n",
				raw_data[1], raw_data[2]);
		hid_debug_event(hdev, buff);
		अवरोध;
	शेष:
		snम_लिखो(buff, BUFF_SZ, "report %s (%d, size=%d)\n",
			"<unknown>", report->id, size-1);
		hid_debug_event(hdev, buff);
		अवरोध;
	पूर्ण
	wake_up_पूर्णांकerruptible(&hdev->debug_रुको);
	kमुक्त(buff);
पूर्ण

व्योम picolcd_init_devfs(काष्ठा picolcd_data *data,
		काष्ठा hid_report *eeprom_r, काष्ठा hid_report *eeprom_w,
		काष्ठा hid_report *flash_r, काष्ठा hid_report *flash_w,
		काष्ठा hid_report *reset)
अणु
	काष्ठा hid_device *hdev = data->hdev;

	mutex_init(&data->mutex_flash);

	/* reset */
	अगर (reset)
		data->debug_reset = debugfs_create_file("reset", 0600,
				hdev->debug_dir, data, &picolcd_debug_reset_fops);

	/* eeprom */
	अगर (eeprom_r || eeprom_w)
		data->debug_eeprom = debugfs_create_file("eeprom",
			(eeprom_w ? S_IWUSR : 0) | (eeprom_r ? S_IRUSR : 0),
			hdev->debug_dir, data, &picolcd_debug_eeprom_fops);

	/* flash */
	अगर (flash_r && flash_r->maxfield == 1 && flash_r->field[0]->report_size == 8)
		data->addr_sz = flash_r->field[0]->report_count - 1;
	अन्यथा
		data->addr_sz = -1;
	अगर (data->addr_sz == 2 || data->addr_sz == 3) अणु
		data->debug_flash = debugfs_create_file("flash",
			(flash_w ? S_IWUSR : 0) | (flash_r ? S_IRUSR : 0),
			hdev->debug_dir, data, &picolcd_debug_flash_fops);
	पूर्ण अन्यथा अगर (flash_r || flash_w)
		hid_warn(hdev, "Unexpected FLASH access reports, please submit rdesc for review\n");
पूर्ण

व्योम picolcd_निकास_devfs(काष्ठा picolcd_data *data)
अणु
	काष्ठा dentry *dent;

	dent = data->debug_reset;
	data->debug_reset = शून्य;
	debugfs_हटाओ(dent);
	dent = data->debug_eeprom;
	data->debug_eeprom = शून्य;
	debugfs_हटाओ(dent);
	dent = data->debug_flash;
	data->debug_flash = शून्य;
	debugfs_हटाओ(dent);
	mutex_destroy(&data->mutex_flash);
पूर्ण

