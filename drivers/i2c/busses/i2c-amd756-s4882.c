<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * i2c-amd756-s4882.c - i2c-amd756 extras क्रम the Tyan S4882 motherboard
 *
 * Copyright (C) 2004, 2008 Jean Delvare <jdelvare@suse.de>
 */
 
/*
 * We select the channels by sending commands to the Philips
 * PCA9556 chip at I2C address 0x18. The मुख्य adapter is used क्रम
 * the non-multiplexed part of the bus, and 4 भव adapters
 * are defined क्रम the multiplexed addresses: 0x50-0x53 (memory
 * module EEPROM) located on channels 1-4, and 0x4c (LM63)
 * located on multiplexed channels 0 and 5-7. We define one
 * भव adapter per CPU, which corresponds to two multiplexed
 * channels:
 *   CPU0: भव adapter 1, channels 1 and 0
 *   CPU1: भव adapter 2, channels 2 and 5
 *   CPU2: भव adapter 3, channels 3 and 6
 *   CPU3: भव adapter 4, channels 4 and 7
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

बाह्य काष्ठा i2c_adapter amd756_smbus;

अटल काष्ठा i2c_adapter *s4882_adapter;
अटल काष्ठा i2c_algorithm *s4882_algo;

/* Wrapper access functions क्रम multiplexed SMBus */
अटल DEFINE_MUTEX(amd756_lock);

अटल s32 amd756_access_virt0(काष्ठा i2c_adapter * adap, u16 addr,
			       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			       u8 command, पूर्णांक size,
			       जोड़ i2c_smbus_data * data)
अणु
	पूर्णांक error;

	/* We exclude the multiplexed addresses */
	अगर (addr == 0x4c || (addr & 0xfc) == 0x50 || (addr & 0xfc) == 0x30
	 || addr == 0x18)
		वापस -ENXIO;

	mutex_lock(&amd756_lock);

	error = amd756_smbus.algo->smbus_xfer(adap, addr, flags, पढ़ो_ग_लिखो,
					      command, size, data);

	mutex_unlock(&amd756_lock);

	वापस error;
पूर्ण

/* We remember the last used channels combination so as to only चयन
   channels when it is really needed. This greatly reduces the SMBus
   overhead, but also assumes that nobody will be writing to the PCA9556
   in our back. */
अटल u8 last_channels;

अटल अंतरभूत s32 amd756_access_channel(काष्ठा i2c_adapter * adap, u16 addr,
					अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
					u8 command, पूर्णांक size,
					जोड़ i2c_smbus_data * data,
					u8 channels)
अणु
	पूर्णांक error;

	/* We exclude the non-multiplexed addresses */
	अगर (addr != 0x4c && (addr & 0xfc) != 0x50 && (addr & 0xfc) != 0x30)
		वापस -ENXIO;

	mutex_lock(&amd756_lock);

	अगर (last_channels != channels) अणु
		जोड़ i2c_smbus_data mplxdata;
		mplxdata.byte = channels;

		error = amd756_smbus.algo->smbus_xfer(adap, 0x18, 0,
						      I2C_SMBUS_WRITE, 0x01,
						      I2C_SMBUS_BYTE_DATA,
						      &mplxdata);
		अगर (error)
			जाओ UNLOCK;
		last_channels = channels;
	पूर्ण
	error = amd756_smbus.algo->smbus_xfer(adap, addr, flags, पढ़ो_ग_लिखो,
					      command, size, data);

UNLOCK:
	mutex_unlock(&amd756_lock);
	वापस error;
पूर्ण

अटल s32 amd756_access_virt1(काष्ठा i2c_adapter * adap, u16 addr,
			       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			       u8 command, पूर्णांक size,
			       जोड़ i2c_smbus_data * data)
अणु
	/* CPU0: channels 1 and 0 enabled */
	वापस amd756_access_channel(adap, addr, flags, पढ़ो_ग_लिखो, command,
				     size, data, 0x03);
पूर्ण

अटल s32 amd756_access_virt2(काष्ठा i2c_adapter * adap, u16 addr,
			       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			       u8 command, पूर्णांक size,
			       जोड़ i2c_smbus_data * data)
अणु
	/* CPU1: channels 2 and 5 enabled */
	वापस amd756_access_channel(adap, addr, flags, पढ़ो_ग_लिखो, command,
				     size, data, 0x24);
पूर्ण

अटल s32 amd756_access_virt3(काष्ठा i2c_adapter * adap, u16 addr,
			       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			       u8 command, पूर्णांक size,
			       जोड़ i2c_smbus_data * data)
अणु
	/* CPU2: channels 3 and 6 enabled */
	वापस amd756_access_channel(adap, addr, flags, पढ़ो_ग_लिखो, command,
				     size, data, 0x48);
पूर्ण

अटल s32 amd756_access_virt4(काष्ठा i2c_adapter * adap, u16 addr,
			       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			       u8 command, पूर्णांक size,
			       जोड़ i2c_smbus_data * data)
अणु
	/* CPU3: channels 4 and 7 enabled */
	वापस amd756_access_channel(adap, addr, flags, पढ़ो_ग_लिखो, command,
				     size, data, 0x90);
पूर्ण

अटल पूर्णांक __init amd756_s4882_init(व्योम)
अणु
	पूर्णांक i, error;
	जोड़ i2c_smbus_data ioconfig;

	अगर (!amd756_smbus.dev.parent)
		वापस -ENODEV;

	/* Configure the PCA9556 multiplexer */
	ioconfig.byte = 0x00; /* All I/O to output mode */
	error = i2c_smbus_xfer(&amd756_smbus, 0x18, 0, I2C_SMBUS_WRITE, 0x03,
			       I2C_SMBUS_BYTE_DATA, &ioconfig);
	अगर (error) अणु
		dev_err(&amd756_smbus.dev, "PCA9556 configuration failed\n");
		error = -EIO;
		जाओ ERROR0;
	पूर्ण

	/* Unरेजिस्टर physical bus */
	i2c_del_adapter(&amd756_smbus);

	prपूर्णांकk(KERN_INFO "Enabling SMBus multiplexing for Tyan S4882\n");
	/* Define the 5 भव adapters and algorithms काष्ठाures */
	अगर (!(s4882_adapter = kसुस्मृति(5, माप(काष्ठा i2c_adapter),
				      GFP_KERNEL))) अणु
		error = -ENOMEM;
		जाओ ERROR1;
	पूर्ण
	अगर (!(s4882_algo = kसुस्मृति(5, माप(काष्ठा i2c_algorithm),
				   GFP_KERNEL))) अणु
		error = -ENOMEM;
		जाओ ERROR2;
	पूर्ण

	/* Fill in the new काष्ठाures */
	s4882_algo[0] = *(amd756_smbus.algo);
	s4882_algo[0].smbus_xfer = amd756_access_virt0;
	s4882_adapter[0] = amd756_smbus;
	s4882_adapter[0].algo = s4882_algo;
	s4882_adapter[0].dev.parent = amd756_smbus.dev.parent;
	क्रम (i = 1; i < 5; i++) अणु
		s4882_algo[i] = *(amd756_smbus.algo);
		s4882_adapter[i] = amd756_smbus;
		snम_लिखो(s4882_adapter[i].name, माप(s4882_adapter[i].name),
			 "SMBus 8111 adapter (CPU%d)", i-1);
		s4882_adapter[i].algo = s4882_algo+i;
		s4882_adapter[i].dev.parent = amd756_smbus.dev.parent;
	पूर्ण
	s4882_algo[1].smbus_xfer = amd756_access_virt1;
	s4882_algo[2].smbus_xfer = amd756_access_virt2;
	s4882_algo[3].smbus_xfer = amd756_access_virt3;
	s4882_algo[4].smbus_xfer = amd756_access_virt4;

	/* Register भव adapters */
	क्रम (i = 0; i < 5; i++) अणु
		error = i2c_add_adapter(s4882_adapter+i);
		अगर (error) अणु
			prपूर्णांकk(KERN_ERR "i2c-amd756-s4882: "
			       "Virtual adapter %d registration "
			       "failed, module not inserted\n", i);
			क्रम (i--; i >= 0; i--)
				i2c_del_adapter(s4882_adapter+i);
			जाओ ERROR3;
		पूर्ण
	पूर्ण

	वापस 0;

ERROR3:
	kमुक्त(s4882_algo);
	s4882_algo = शून्य;
ERROR2:
	kमुक्त(s4882_adapter);
	s4882_adapter = शून्य;
ERROR1:
	/* Restore physical bus */
	i2c_add_adapter(&amd756_smbus);
ERROR0:
	वापस error;
पूर्ण

अटल व्योम __निकास amd756_s4882_निकास(व्योम)
अणु
	अगर (s4882_adapter) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 5; i++)
			i2c_del_adapter(s4882_adapter+i);
		kमुक्त(s4882_adapter);
		s4882_adapter = शून्य;
	पूर्ण
	kमुक्त(s4882_algo);
	s4882_algo = शून्य;

	/* Restore physical bus */
	अगर (i2c_add_adapter(&amd756_smbus))
		prपूर्णांकk(KERN_ERR "i2c-amd756-s4882: "
		       "Physical bus restoration failed\n");
पूर्ण

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("S4882 SMBus multiplexing");
MODULE_LICENSE("GPL");

module_init(amd756_s4882_init);
module_निकास(amd756_s4882_निकास);
