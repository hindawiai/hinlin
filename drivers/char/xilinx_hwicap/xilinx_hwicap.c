<शैली गुरु>
/*****************************************************************************
 *
 *     Author: Xilinx, Inc.
 *
 *     This program is मुक्त software; you can redistribute it and/or modअगरy it
 *     under the terms of the GNU General Public License as published by the
 *     Free Software Foundation; either version 2 of the License, or (at your
 *     option) any later version.
 *
 *     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
 *     AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
 *     SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
 *     OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
 *     APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
 *     THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
 *     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
 *     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
 *     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
 *     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
 *     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
 *     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE.
 *
 *     (c) Copyright 2002 Xilinx Inc., Systems Engineering Group
 *     (c) Copyright 2004 Xilinx Inc., Systems Engineering Group
 *     (c) Copyright 2007-2008 Xilinx Inc.
 *     All rights reserved.
 *
 *     You should have received a copy of the GNU General Public License aदीर्घ
 *     with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *     675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *****************************************************************************/

/*
 * This is the code behind /dev/icap* -- it allows a user-space
 * application to use the Xilinx ICAP subप्रणाली.
 *
 * The following operations are possible:
 *
 * खोलो         खोलो the port and initialize क्रम access.
 * release      release port
 * ग_लिखो        Write a bitstream to the configuration processor.
 * पढ़ो         Read a data stream from the configuration processor.
 *
 * After being खोलोed, the port is initialized and accessed to aव्योम a
 * corrupted first पढ़ो which may occur with some hardware.  The port
 * is left in a desynched state, requiring that a synch sequence be
 * transmitted beक्रमe any valid configuration data.  A user will have
 * exclusive access to the device जबतक it reमुख्यs खोलो, and the state
 * of the ICAP cannot be guaranteed after the device is बंदd.  Note
 * that a complete reset of the core and the state of the ICAP cannot
 * be perक्रमmed on many versions of the cores, hence users of this
 * device should aव्योम making inconsistent accesses to the device.  In
 * particular, accessing the पढ़ो पूर्णांकerface, without first generating
 * a ग_लिखो containing a पढ़ोback packet can leave the ICAP in an
 * inaccessible state.
 *
 * Note that in order to use the पढ़ो पूर्णांकerface, it is first necessary
 * to ग_लिखो a request packet to the ग_लिखो पूर्णांकerface.  i.e., it is not
 * possible to simply पढ़ोback the bitstream (or any configuration
 * bits) from a device without specअगरically requesting them first.
 * The code to craft such packets is पूर्णांकended to be part of the
 * user-space application code that uses this device.  The simplest
 * way to use this पूर्णांकerface is simply:
 *
 * cp foo.bit /dev/icap0
 *
 * Note that unless foo.bit is an appropriately स्थिरructed partial
 * bitstream, this has a high likelihood of overwriting the design
 * currently programmed in the FPGA.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/fs.h>
#समावेश <linux/cdev.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#अगर_घोषित CONFIG_OF
/* For खोलो firmware. */
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#पूर्ण_अगर

#समावेश "xilinx_hwicap.h"
#समावेश "buffer_icap.h"
#समावेश "fifo_icap.h"

#घोषणा DRIVER_NAME "icap"

#घोषणा HWICAP_REGS   (0x10000)

#घोषणा XHWICAP_MAJOR 259
#घोषणा XHWICAP_MINOR 0
#घोषणा HWICAP_DEVICES 1

/* An array, which is set to true when the device is रेजिस्टरed. */
अटल DEFINE_MUTEX(hwicap_mutex);
अटल bool probed_devices[HWICAP_DEVICES];
अटल काष्ठा mutex icap_sem;

अटल काष्ठा class *icap_class;

#घोषणा UNIMPLEMENTED 0xFFFF

अटल स्थिर काष्ठा config_रेजिस्टरs v2_config_रेजिस्टरs = अणु
	.CRC = 0,
	.FAR = 1,
	.FDRI = 2,
	.FDRO = 3,
	.CMD = 4,
	.CTL = 5,
	.MASK = 6,
	.STAT = 7,
	.LOUT = 8,
	.COR = 9,
	.MFWR = 10,
	.FLR = 11,
	.KEY = 12,
	.CBC = 13,
	.IDCODE = 14,
	.AXSS = UNIMPLEMENTED,
	.C0R_1 = UNIMPLEMENTED,
	.CSOB = UNIMPLEMENTED,
	.WBSTAR = UNIMPLEMENTED,
	.TIMER = UNIMPLEMENTED,
	.BOOTSTS = UNIMPLEMENTED,
	.CTL_1 = UNIMPLEMENTED,
पूर्ण;

अटल स्थिर काष्ठा config_रेजिस्टरs v4_config_रेजिस्टरs = अणु
	.CRC = 0,
	.FAR = 1,
	.FDRI = 2,
	.FDRO = 3,
	.CMD = 4,
	.CTL = 5,
	.MASK = 6,
	.STAT = 7,
	.LOUT = 8,
	.COR = 9,
	.MFWR = 10,
	.FLR = UNIMPLEMENTED,
	.KEY = UNIMPLEMENTED,
	.CBC = 11,
	.IDCODE = 12,
	.AXSS = 13,
	.C0R_1 = UNIMPLEMENTED,
	.CSOB = UNIMPLEMENTED,
	.WBSTAR = UNIMPLEMENTED,
	.TIMER = UNIMPLEMENTED,
	.BOOTSTS = UNIMPLEMENTED,
	.CTL_1 = UNIMPLEMENTED,
पूर्ण;

अटल स्थिर काष्ठा config_रेजिस्टरs v5_config_रेजिस्टरs = अणु
	.CRC = 0,
	.FAR = 1,
	.FDRI = 2,
	.FDRO = 3,
	.CMD = 4,
	.CTL = 5,
	.MASK = 6,
	.STAT = 7,
	.LOUT = 8,
	.COR = 9,
	.MFWR = 10,
	.FLR = UNIMPLEMENTED,
	.KEY = UNIMPLEMENTED,
	.CBC = 11,
	.IDCODE = 12,
	.AXSS = 13,
	.C0R_1 = 14,
	.CSOB = 15,
	.WBSTAR = 16,
	.TIMER = 17,
	.BOOTSTS = 18,
	.CTL_1 = 19,
पूर्ण;

अटल स्थिर काष्ठा config_रेजिस्टरs v6_config_रेजिस्टरs = अणु
	.CRC = 0,
	.FAR = 1,
	.FDRI = 2,
	.FDRO = 3,
	.CMD = 4,
	.CTL = 5,
	.MASK = 6,
	.STAT = 7,
	.LOUT = 8,
	.COR = 9,
	.MFWR = 10,
	.FLR = UNIMPLEMENTED,
	.KEY = UNIMPLEMENTED,
	.CBC = 11,
	.IDCODE = 12,
	.AXSS = 13,
	.C0R_1 = 14,
	.CSOB = 15,
	.WBSTAR = 16,
	.TIMER = 17,
	.BOOTSTS = 22,
	.CTL_1 = 24,
पूर्ण;

/**
 * hwicap_command_desync - Send a DESYNC command to the ICAP port.
 * @drvdata: a poपूर्णांकer to the drvdata.
 *
 * Returns: '0' on success and failure value on error
 *
 * This command desynchronizes the ICAP After this command, a
 * bitstream containing a शून्य packet, followed by a SYNCH packet is
 * required beक्रमe the ICAP will recognize commands.
 */
अटल पूर्णांक hwicap_command_desync(काष्ठा hwicap_drvdata *drvdata)
अणु
	u32 buffer[4];
	u32 index = 0;

	/*
	 * Create the data to be written to the ICAP.
	 */
	buffer[index++] = hwicap_type_1_ग_लिखो(drvdata->config_regs->CMD) | 1;
	buffer[index++] = XHI_CMD_DESYNCH;
	buffer[index++] = XHI_NOOP_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;

	/*
	 * Write the data to the FIFO and पूर्णांकiate the transfer of data present
	 * in the FIFO to the ICAP device.
	 */
	वापस drvdata->config->set_configuration(drvdata,
			&buffer[0], index);
पूर्ण

/**
 * hwicap_get_configuration_रेजिस्टर - Query a configuration रेजिस्टर.
 * @drvdata: a poपूर्णांकer to the drvdata.
 * @reg: a स्थिरant which represents the configuration
 * रेजिस्टर value to be वापसed.
 * Examples: XHI_IDCODE, XHI_FLR.
 * @reg_data: वापसs the value of the रेजिस्टर.
 *
 * Returns: '0' on success and failure value on error
 *
 * Sends a query packet to the ICAP and then receives the response.
 * The icap is left in Synched state.
 */
अटल पूर्णांक hwicap_get_configuration_रेजिस्टर(काष्ठा hwicap_drvdata *drvdata,
		u32 reg, u32 *reg_data)
अणु
	पूर्णांक status;
	u32 buffer[6];
	u32 index = 0;

	/*
	 * Create the data to be written to the ICAP.
	 */
	buffer[index++] = XHI_DUMMY_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;
	buffer[index++] = XHI_SYNC_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;

	/*
	 * Write the data to the FIFO and initiate the transfer of data present
	 * in the FIFO to the ICAP device.
	 */
	status = drvdata->config->set_configuration(drvdata,
						    &buffer[0], index);
	अगर (status)
		वापस status;

	/* If the syncword was not found, then we need to start over. */
	status = drvdata->config->get_status(drvdata);
	अगर ((status & XHI_SR_DALIGN_MASK) != XHI_SR_DALIGN_MASK)
		वापस -EIO;

	index = 0;
	buffer[index++] = hwicap_type_1_पढ़ो(reg) | 1;
	buffer[index++] = XHI_NOOP_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;

	/*
	 * Write the data to the FIFO and पूर्णांकiate the transfer of data present
	 * in the FIFO to the ICAP device.
	 */
	status = drvdata->config->set_configuration(drvdata,
			&buffer[0], index);
	अगर (status)
		वापस status;

	/*
	 * Read the configuration रेजिस्टर
	 */
	status = drvdata->config->get_configuration(drvdata, reg_data, 1);
	अगर (status)
		वापस status;

	वापस 0;
पूर्ण

अटल पूर्णांक hwicap_initialize_hwicap(काष्ठा hwicap_drvdata *drvdata)
अणु
	पूर्णांक status;
	u32 idcode;

	dev_dbg(drvdata->dev, "initializing\n");

	/* Abort any current transaction, to make sure we have the
	 * ICAP in a good state.
	 */
	dev_dbg(drvdata->dev, "Reset...\n");
	drvdata->config->reset(drvdata);

	dev_dbg(drvdata->dev, "Desync...\n");
	status = hwicap_command_desync(drvdata);
	अगर (status)
		वापस status;

	/* Attempt to पढ़ो the IDCODE from ICAP.  This
	 * may not be वापसed correctly, due to the design of the
	 * hardware.
	 */
	dev_dbg(drvdata->dev, "Reading IDCODE...\n");
	status = hwicap_get_configuration_रेजिस्टर(
			drvdata, drvdata->config_regs->IDCODE, &idcode);
	dev_dbg(drvdata->dev, "IDCODE = %x\n", idcode);
	अगर (status)
		वापस status;

	dev_dbg(drvdata->dev, "Desync...\n");
	status = hwicap_command_desync(drvdata);
	अगर (status)
		वापस status;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
hwicap_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hwicap_drvdata *drvdata = file->निजी_data;
	sमाप_प्रकार bytes_to_पढ़ो = 0;
	u32 *kbuf;
	u32 words;
	u32 bytes_reमुख्यing;
	पूर्णांक status;

	status = mutex_lock_पूर्णांकerruptible(&drvdata->sem);
	अगर (status)
		वापस status;

	अगर (drvdata->पढ़ो_buffer_in_use) अणु
		/* If there are leftover bytes in the buffer, just */
		/* वापस them and करोn't try to पढ़ो more from the */
		/* ICAP device. */
		bytes_to_पढ़ो =
			(count < drvdata->पढ़ो_buffer_in_use) ? count :
			drvdata->पढ़ो_buffer_in_use;

		/* Return the data currently in the पढ़ो buffer. */
		अगर (copy_to_user(buf, drvdata->पढ़ो_buffer, bytes_to_पढ़ो)) अणु
			status = -EFAULT;
			जाओ error;
		पूर्ण
		drvdata->पढ़ो_buffer_in_use -= bytes_to_पढ़ो;
		स_हटाओ(drvdata->पढ़ो_buffer,
		       drvdata->पढ़ो_buffer + bytes_to_पढ़ो,
		       4 - bytes_to_पढ़ो);
	पूर्ण अन्यथा अणु
		/* Get new data from the ICAP, and वापस was was requested. */
		kbuf = (u32 *) get_zeroed_page(GFP_KERNEL);
		अगर (!kbuf) अणु
			status = -ENOMEM;
			जाओ error;
		पूर्ण

		/* The ICAP device is only able to पढ़ो complete */
		/* words.  If a number of bytes that करो not correspond */
		/* to complete words is requested, then we पढ़ो enough */
		/* words to get the required number of bytes, and then */
		/* save the reमुख्यing bytes क्रम the next पढ़ो. */

		/* Determine the number of words to पढ़ो, rounding up */
		/* अगर necessary. */
		words = ((count + 3) >> 2);
		bytes_to_पढ़ो = words << 2;

		अगर (bytes_to_पढ़ो > PAGE_SIZE)
			bytes_to_पढ़ो = PAGE_SIZE;

		/* Ensure we only पढ़ो a complete number of words. */
		bytes_reमुख्यing = bytes_to_पढ़ो & 3;
		bytes_to_पढ़ो &= ~3;
		words = bytes_to_पढ़ो >> 2;

		status = drvdata->config->get_configuration(drvdata,
				kbuf, words);

		/* If we didn't पढ़ो correctly, then bail out. */
		अगर (status) अणु
			मुक्त_page((अचिन्हित दीर्घ)kbuf);
			जाओ error;
		पूर्ण

		/* If we fail to वापस the data to the user, then bail out. */
		अगर (copy_to_user(buf, kbuf, bytes_to_पढ़ो)) अणु
			मुक्त_page((अचिन्हित दीर्घ)kbuf);
			status = -EFAULT;
			जाओ error;
		पूर्ण
		स_नकल(drvdata->पढ़ो_buffer,
		       kbuf,
		       bytes_reमुख्यing);
		drvdata->पढ़ो_buffer_in_use = bytes_reमुख्यing;
		मुक्त_page((अचिन्हित दीर्घ)kbuf);
	पूर्ण
	status = bytes_to_पढ़ो;
 error:
	mutex_unlock(&drvdata->sem);
	वापस status;
पूर्ण

अटल sमाप_प्रकार
hwicap_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hwicap_drvdata *drvdata = file->निजी_data;
	sमाप_प्रकार written = 0;
	sमाप_प्रकार left = count;
	u32 *kbuf;
	sमाप_प्रकार len;
	sमाप_प्रकार status;

	status = mutex_lock_पूर्णांकerruptible(&drvdata->sem);
	अगर (status)
		वापस status;

	left += drvdata->ग_लिखो_buffer_in_use;

	/* Only ग_लिखो multiples of 4 bytes. */
	अगर (left < 4) अणु
		status = 0;
		जाओ error;
	पूर्ण

	kbuf = (u32 *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!kbuf) अणु
		status = -ENOMEM;
		जाओ error;
	पूर्ण

	जबतक (left > 3) अणु
		/* only ग_लिखो multiples of 4 bytes, so there might */
		/* be as many as 3 bytes left (at the end). */
		len = left;

		अगर (len > PAGE_SIZE)
			len = PAGE_SIZE;
		len &= ~3;

		अगर (drvdata->ग_लिखो_buffer_in_use) अणु
			स_नकल(kbuf, drvdata->ग_लिखो_buffer,
					drvdata->ग_लिखो_buffer_in_use);
			अगर (copy_from_user(
			    (((अक्षर *)kbuf) + drvdata->ग_लिखो_buffer_in_use),
			    buf + written,
			    len - (drvdata->ग_लिखो_buffer_in_use))) अणु
				मुक्त_page((अचिन्हित दीर्घ)kbuf);
				status = -EFAULT;
				जाओ error;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (copy_from_user(kbuf, buf + written, len)) अणु
				मुक्त_page((अचिन्हित दीर्घ)kbuf);
				status = -EFAULT;
				जाओ error;
			पूर्ण
		पूर्ण

		status = drvdata->config->set_configuration(drvdata,
				kbuf, len >> 2);

		अगर (status) अणु
			मुक्त_page((अचिन्हित दीर्घ)kbuf);
			status = -EFAULT;
			जाओ error;
		पूर्ण
		अगर (drvdata->ग_लिखो_buffer_in_use) अणु
			len -= drvdata->ग_लिखो_buffer_in_use;
			left -= drvdata->ग_लिखो_buffer_in_use;
			drvdata->ग_लिखो_buffer_in_use = 0;
		पूर्ण
		written += len;
		left -= len;
	पूर्ण
	अगर ((left > 0) && (left < 4)) अणु
		अगर (!copy_from_user(drvdata->ग_लिखो_buffer,
						buf + written, left)) अणु
			drvdata->ग_लिखो_buffer_in_use = left;
			written += left;
			left = 0;
		पूर्ण
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)kbuf);
	status = written;
 error:
	mutex_unlock(&drvdata->sem);
	वापस status;
पूर्ण

अटल पूर्णांक hwicap_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hwicap_drvdata *drvdata;
	पूर्णांक status;

	mutex_lock(&hwicap_mutex);
	drvdata = container_of(inode->i_cdev, काष्ठा hwicap_drvdata, cdev);

	status = mutex_lock_पूर्णांकerruptible(&drvdata->sem);
	अगर (status)
		जाओ out;

	अगर (drvdata->is_खोलो) अणु
		status = -EBUSY;
		जाओ error;
	पूर्ण

	status = hwicap_initialize_hwicap(drvdata);
	अगर (status) अणु
		dev_err(drvdata->dev, "Failed to open file");
		जाओ error;
	पूर्ण

	file->निजी_data = drvdata;
	drvdata->ग_लिखो_buffer_in_use = 0;
	drvdata->पढ़ो_buffer_in_use = 0;
	drvdata->is_खोलो = 1;

 error:
	mutex_unlock(&drvdata->sem);
 out:
	mutex_unlock(&hwicap_mutex);
	वापस status;
पूर्ण

अटल पूर्णांक hwicap_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hwicap_drvdata *drvdata = file->निजी_data;
	पूर्णांक i;
	पूर्णांक status = 0;

	mutex_lock(&drvdata->sem);

	अगर (drvdata->ग_लिखो_buffer_in_use) अणु
		/* Flush ग_लिखो buffer. */
		क्रम (i = drvdata->ग_लिखो_buffer_in_use; i < 4; i++)
			drvdata->ग_लिखो_buffer[i] = 0;

		status = drvdata->config->set_configuration(drvdata,
				(u32 *) drvdata->ग_लिखो_buffer, 1);
		अगर (status)
			जाओ error;
	पूर्ण

	status = hwicap_command_desync(drvdata);
	अगर (status)
		जाओ error;

 error:
	drvdata->is_खोलो = 0;
	mutex_unlock(&drvdata->sem);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा file_operations hwicap_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = hwicap_ग_लिखो,
	.पढ़ो = hwicap_पढ़ो,
	.खोलो = hwicap_खोलो,
	.release = hwicap_release,
	.llseek = noop_llseek,
पूर्ण;

अटल पूर्णांक hwicap_setup(काष्ठा device *dev, पूर्णांक id,
		स्थिर काष्ठा resource *regs_res,
		स्थिर काष्ठा hwicap_driver_config *config,
		स्थिर काष्ठा config_रेजिस्टरs *config_regs)
अणु
	dev_t devt;
	काष्ठा hwicap_drvdata *drvdata = शून्य;
	पूर्णांक retval = 0;

	dev_info(dev, "Xilinx icap port driver\n");

	mutex_lock(&icap_sem);

	अगर (id < 0) अणु
		क्रम (id = 0; id < HWICAP_DEVICES; id++)
			अगर (!probed_devices[id])
				अवरोध;
	पूर्ण
	अगर (id < 0 || id >= HWICAP_DEVICES) अणु
		mutex_unlock(&icap_sem);
		dev_err(dev, "%s%i too large\n", DRIVER_NAME, id);
		वापस -EINVAL;
	पूर्ण
	अगर (probed_devices[id]) अणु
		mutex_unlock(&icap_sem);
		dev_err(dev, "cannot assign to %s%i; it is already in use\n",
			DRIVER_NAME, id);
		वापस -EBUSY;
	पूर्ण

	probed_devices[id] = 1;
	mutex_unlock(&icap_sem);

	devt = MKDEV(XHWICAP_MAJOR, XHWICAP_MINOR + id);

	drvdata = kzalloc(माप(काष्ठा hwicap_drvdata), GFP_KERNEL);
	अगर (!drvdata) अणु
		retval = -ENOMEM;
		जाओ failed0;
	पूर्ण
	dev_set_drvdata(dev, (व्योम *)drvdata);

	अगर (!regs_res) अणु
		dev_err(dev, "Couldn't get registers resource\n");
		retval = -EFAULT;
		जाओ failed1;
	पूर्ण

	drvdata->mem_start = regs_res->start;
	drvdata->mem_end = regs_res->end;
	drvdata->mem_size = resource_size(regs_res);

	अगर (!request_mem_region(drvdata->mem_start,
					drvdata->mem_size, DRIVER_NAME)) अणु
		dev_err(dev, "Couldn't lock memory region at %Lx\n",
			(अचिन्हित दीर्घ दीर्घ) regs_res->start);
		retval = -EBUSY;
		जाओ failed1;
	पूर्ण

	drvdata->devt = devt;
	drvdata->dev = dev;
	drvdata->base_address = ioremap(drvdata->mem_start, drvdata->mem_size);
	अगर (!drvdata->base_address) अणु
		dev_err(dev, "ioremap() failed\n");
		retval = -ENOMEM;
		जाओ failed2;
	पूर्ण

	drvdata->config = config;
	drvdata->config_regs = config_regs;

	mutex_init(&drvdata->sem);
	drvdata->is_खोलो = 0;

	dev_info(dev, "ioremap %llx to %p with size %llx\n",
		 (अचिन्हित दीर्घ दीर्घ) drvdata->mem_start,
		 drvdata->base_address,
		 (अचिन्हित दीर्घ दीर्घ) drvdata->mem_size);

	cdev_init(&drvdata->cdev, &hwicap_fops);
	drvdata->cdev.owner = THIS_MODULE;
	retval = cdev_add(&drvdata->cdev, devt, 1);
	अगर (retval) अणु
		dev_err(dev, "cdev_add() failed\n");
		जाओ failed3;
	पूर्ण

	device_create(icap_class, dev, devt, शून्य, "%s%d", DRIVER_NAME, id);
	वापस 0;		/* success */

 failed3:
	iounmap(drvdata->base_address);

 failed2:
	release_mem_region(regs_res->start, drvdata->mem_size);

 failed1:
	kमुक्त(drvdata);

 failed0:
	mutex_lock(&icap_sem);
	probed_devices[id] = 0;
	mutex_unlock(&icap_sem);

	वापस retval;
पूर्ण

अटल काष्ठा hwicap_driver_config buffer_icap_config = अणु
	.get_configuration = buffer_icap_get_configuration,
	.set_configuration = buffer_icap_set_configuration,
	.get_status = buffer_icap_get_status,
	.reset = buffer_icap_reset,
पूर्ण;

अटल काष्ठा hwicap_driver_config fअगरo_icap_config = अणु
	.get_configuration = fअगरo_icap_get_configuration,
	.set_configuration = fअगरo_icap_set_configuration,
	.get_status = fअगरo_icap_get_status,
	.reset = fअगरo_icap_reset,
पूर्ण;

अटल पूर्णांक hwicap_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा hwicap_drvdata *drvdata;

	drvdata = dev_get_drvdata(dev);

	अगर (!drvdata)
		वापस 0;

	device_destroy(icap_class, drvdata->devt);
	cdev_del(&drvdata->cdev);
	iounmap(drvdata->base_address);
	release_mem_region(drvdata->mem_start, drvdata->mem_size);
	kमुक्त(drvdata);

	mutex_lock(&icap_sem);
	probed_devices[MINOR(dev->devt)-XHWICAP_MINOR] = 0;
	mutex_unlock(&icap_sem);
	वापस 0;		/* success */
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक hwicap_of_probe(काष्ठा platक्रमm_device *op,
				     स्थिर काष्ठा hwicap_driver_config *config)
अणु
	काष्ठा resource res;
	स्थिर अचिन्हित पूर्णांक *id;
	स्थिर अक्षर *family;
	पूर्णांक rc;
	स्थिर काष्ठा config_रेजिस्टरs *regs;


	rc = of_address_to_resource(op->dev.of_node, 0, &res);
	अगर (rc) अणु
		dev_err(&op->dev, "invalid address\n");
		वापस rc;
	पूर्ण

	id = of_get_property(op->dev.of_node, "port-number", शून्य);

	/* It's most likely that we're using V4, अगर the family is not
	 * specअगरied
	 */
	regs = &v4_config_रेजिस्टरs;
	family = of_get_property(op->dev.of_node, "xlnx,family", शून्य);

	अगर (family) अणु
		अगर (!म_भेद(family, "virtex2p"))
			regs = &v2_config_रेजिस्टरs;
		अन्यथा अगर (!म_भेद(family, "virtex4"))
			regs = &v4_config_रेजिस्टरs;
		अन्यथा अगर (!म_भेद(family, "virtex5"))
			regs = &v5_config_रेजिस्टरs;
		अन्यथा अगर (!म_भेद(family, "virtex6"))
			regs = &v6_config_रेजिस्टरs;
	पूर्ण
	वापस hwicap_setup(&op->dev, id ? *id : -1, &res, config,
			regs);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक hwicap_of_probe(काष्ठा platक्रमm_device *op,
				  स्थिर काष्ठा hwicap_driver_config *config)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल स्थिर काष्ठा of_device_id hwicap_of_match[];
अटल पूर्णांक hwicap_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *res;
	स्थिर काष्ठा config_रेजिस्टरs *regs;
	स्थिर अक्षर *family;

	match = of_match_device(hwicap_of_match, &pdev->dev);
	अगर (match)
		वापस hwicap_of_probe(pdev, match->data);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	/* It's most likely that we're using V4, अगर the family is not
	 * specअगरied
	 */
	regs = &v4_config_रेजिस्टरs;
	family = pdev->dev.platक्रमm_data;

	अगर (family) अणु
		अगर (!म_भेद(family, "virtex2p"))
			regs = &v2_config_रेजिस्टरs;
		अन्यथा अगर (!म_भेद(family, "virtex4"))
			regs = &v4_config_रेजिस्टरs;
		अन्यथा अगर (!म_भेद(family, "virtex5"))
			regs = &v5_config_रेजिस्टरs;
		अन्यथा अगर (!म_भेद(family, "virtex6"))
			regs = &v6_config_रेजिस्टरs;
	पूर्ण

	वापस hwicap_setup(&pdev->dev, pdev->id, res,
			&buffer_icap_config, regs);
पूर्ण

अटल पूर्णांक hwicap_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस hwicap_हटाओ(&pdev->dev);
पूर्ण

#अगर_घोषित CONFIG_OF
/* Match table क्रम device tree binding */
अटल स्थिर काष्ठा of_device_id hwicap_of_match[] = अणु
	अणु .compatible = "xlnx,opb-hwicap-1.00.b", .data = &buffer_icap_configपूर्ण,
	अणु .compatible = "xlnx,xps-hwicap-1.00.a", .data = &fअगरo_icap_configपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hwicap_of_match);
#अन्यथा
#घोषणा hwicap_of_match शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver hwicap_platक्रमm_driver = अणु
	.probe = hwicap_drv_probe,
	.हटाओ = hwicap_drv_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = hwicap_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hwicap_module_init(व्योम)
अणु
	dev_t devt;
	पूर्णांक retval;

	icap_class = class_create(THIS_MODULE, "xilinx_config");
	mutex_init(&icap_sem);

	devt = MKDEV(XHWICAP_MAJOR, XHWICAP_MINOR);
	retval = रेजिस्टर_chrdev_region(devt,
					HWICAP_DEVICES,
					DRIVER_NAME);
	अगर (retval < 0)
		वापस retval;

	retval = platक्रमm_driver_रेजिस्टर(&hwicap_platक्रमm_driver);
	अगर (retval)
		जाओ failed;

	वापस retval;

 failed:
	unरेजिस्टर_chrdev_region(devt, HWICAP_DEVICES);

	वापस retval;
पूर्ण

अटल व्योम __निकास hwicap_module_cleanup(व्योम)
अणु
	dev_t devt = MKDEV(XHWICAP_MAJOR, XHWICAP_MINOR);

	class_destroy(icap_class);

	platक्रमm_driver_unरेजिस्टर(&hwicap_platक्रमm_driver);

	unरेजिस्टर_chrdev_region(devt, HWICAP_DEVICES);
पूर्ण

module_init(hwicap_module_init);
module_निकास(hwicap_module_cleanup);

MODULE_AUTHOR("Xilinx, Inc; Xilinx Research Labs Group");
MODULE_DESCRIPTION("Xilinx ICAP Port Driver");
MODULE_LICENSE("GPL");
