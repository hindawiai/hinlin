<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* envctrl.c: Temperature and Fan monitoring on Machines providing it.
 *
 * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)
 * Copyright (C) 2000  Vinh Truong    (vinh.truong@eng.sun.com)
 * VT - The implementation is to support Sun Microelectronics (SME) platक्रमm
 *      environment monitoring.  SME platक्रमms use pcf8584 as the i2c bus 
 *      controller to access pcf8591 (8-bit A/D and D/A converter) and 
 *      pcf8571 (256 x 8-bit अटल low-voltage RAM with I2C-bus पूर्णांकerface).
 *      At board level, it follows SME Firmware I2C Specअगरication. Reference:
 * 	http://www-eu2.semiconductors.com/pip/PCF8584P
 * 	http://www-eu2.semiconductors.com/pip/PCF8574AP
 * 	http://www-eu2.semiconductors.com/pip/PCF8591P
 *
 * EB - Added support क्रम CP1500 Global Address and PS/Voltage monitoring.
 * 		Eric Brower <ebrower@usa.net>
 *
 * DB - Audit every copy_to_user in envctrl_पढ़ो.
 *              Daniele Bellucci <bellucda@tiscali.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/kmod.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/envctrl.h>
#समावेश <यंत्र/पन.स>

#घोषणा DRIVER_NAME	"envctrl"
#घोषणा PFX		DRIVER_NAME ": "

#घोषणा PCF8584_ADDRESS	0x55

#घोषणा CONTROL_PIN	0x80
#घोषणा CONTROL_ES0	0x40
#घोषणा CONTROL_ES1	0x20
#घोषणा CONTROL_ES2	0x10
#घोषणा CONTROL_ENI	0x08
#घोषणा CONTROL_STA	0x04
#घोषणा CONTROL_STO	0x02
#घोषणा CONTROL_ACK	0x01

#घोषणा STATUS_PIN	0x80
#घोषणा STATUS_STS	0x20
#घोषणा STATUS_BER	0x10
#घोषणा STATUS_LRB	0x08
#घोषणा STATUS_AD0	0x08
#घोषणा STATUS_AAB	0x04
#घोषणा STATUS_LAB	0x02
#घोषणा STATUS_BB	0x01

/*
 * CLK Mode Register.
 */
#घोषणा BUS_CLK_90	0x00
#घोषणा BUS_CLK_45	0x01
#घोषणा BUS_CLK_11	0x02
#घोषणा BUS_CLK_1_5	0x03

#घोषणा CLK_3		0x00
#घोषणा CLK_4_43	0x10
#घोषणा CLK_6		0x14
#घोषणा CLK_8		0x18
#घोषणा CLK_12		0x1c

#घोषणा OBD_SEND_START	0xc5    /* value to generate I2c_bus START condition */
#घोषणा OBD_SEND_STOP 	0xc3    /* value to generate I2c_bus STOP condition */

/* Monitor type of i2c child device.
 * Firmware definitions.
 */
#घोषणा PCF8584_MAX_CHANNELS            8
#घोषणा PCF8584_GLOBALADDR_TYPE			6  /* global address monitor */
#घोषणा PCF8584_FANSTAT_TYPE            3  /* fan status monitor */
#घोषणा PCF8584_VOLTAGE_TYPE            2  /* voltage monitor    */
#घोषणा PCF8584_TEMP_TYPE	        	1  /* temperature monitor*/

/* Monitor type of i2c child device.
 * Driver definitions.
 */
#घोषणा ENVCTRL_NOMON				0
#घोषणा ENVCTRL_CPUTEMP_MON			1    /* cpu temperature monitor */
#घोषणा ENVCTRL_CPUVOLTAGE_MON	  	2    /* voltage monitor         */
#घोषणा ENVCTRL_FANSTAT_MON  		3    /* fan status monitor      */
#घोषणा ENVCTRL_ETHERTEMP_MON		4    /* ethernet temperature */
					     /* monitor                     */
#घोषणा ENVCTRL_VOLTAGESTAT_MON	  	5    /* voltage status monitor  */
#घोषणा ENVCTRL_MTHRBDTEMP_MON		6    /* motherboard temperature */
#घोषणा ENVCTRL_SCSITEMP_MON		7    /* scsi temperature */
#घोषणा ENVCTRL_GLOBALADDR_MON		8    /* global address */

/* Child device type.
 * Driver definitions.
 */
#घोषणा I2C_ADC				0    /* pcf8591 */
#घोषणा I2C_GPIO			1    /* pcf8571 */

/* Data पढ़ो from child device may need to decode
 * through a data table and a scale.
 * Translation type as defined by firmware.
 */
#घोषणा ENVCTRL_TRANSLATE_NO		0
#घोषणा ENVCTRL_TRANSLATE_PARTIAL	1
#घोषणा ENVCTRL_TRANSLATE_COMBINED	2
#घोषणा ENVCTRL_TRANSLATE_FULL		3     /* table[data] */
#घोषणा ENVCTRL_TRANSLATE_SCALE		4     /* table[data]/scale */

/* Driver miscellaneous definitions. */
#घोषणा ENVCTRL_MAX_CPU			4
#घोषणा CHANNEL_DESC_SZ			256

/* Mask values क्रम combined GlobalAddress/PowerStatus node */
#घोषणा ENVCTRL_GLOBALADDR_ADDR_MASK 	0x1F
#घोषणा ENVCTRL_GLOBALADDR_PSTAT_MASK	0x60

/* Node 0x70 ignored on CompactPCI CP1400/1500 platक्रमms 
 * (see envctrl_init_i2c_child)
 */
#घोषणा ENVCTRL_CPCI_IGNORED_NODE		0x70

#घोषणा PCF8584_DATA	0x00
#घोषणा PCF8584_CSR	0x01

/* Each child device can be monitored by up to PCF8584_MAX_CHANNELS.
 * Property of a port or channel as defined by the firmware.
 */
काष्ठा pcf8584_channel अणु
        अचिन्हित अक्षर chnl_no;
        अचिन्हित अक्षर io_direction;
        अचिन्हित अक्षर type;
        अचिन्हित अक्षर last;
पूर्ण;

/* Each child device may have one or more tables of bytes to help decode
 * data. Table property as defined by the firmware.
 */ 
काष्ठा pcf8584_tblprop अणु
        अचिन्हित पूर्णांक type;
        अचिन्हित पूर्णांक scale;  
        अचिन्हित पूर्णांक offset; /* offset from the beginning of the table */
        अचिन्हित पूर्णांक size;
पूर्ण;

/* i2c child */
काष्ठा i2c_child_t अणु
	/* Either ADC or GPIO. */
	अचिन्हित अक्षर i2ctype;
        अचिन्हित दीर्घ addr;    
        काष्ठा pcf8584_channel chnl_array[PCF8584_MAX_CHANNELS];

	/* Channel info. */ 
	अचिन्हित पूर्णांक total_chnls;	/* Number of monitor channels. */
	अचिन्हित अक्षर fan_mask;		/* Byte mask क्रम fan status channels. */
	अचिन्हित अक्षर voltage_mask;	/* Byte mask क्रम voltage status channels. */
        काष्ठा pcf8584_tblprop tblprop_array[PCF8584_MAX_CHANNELS];

	/* Properties of all monitor channels. */
	अचिन्हित पूर्णांक total_tbls;	/* Number of monitor tables. */
        अक्षर *tables;			/* Poपूर्णांकer to table(s). */
	अक्षर chnls_desc[CHANNEL_DESC_SZ]; /* Channel description. */
	अक्षर mon_type[PCF8584_MAX_CHANNELS];
पूर्ण;

अटल व्योम __iomem *i2c;
अटल काष्ठा i2c_child_t i2c_childlist[ENVCTRL_MAX_CPU*2];
अटल अचिन्हित अक्षर chnls_mask[] = अणु 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 पूर्ण;
अटल अचिन्हित पूर्णांक warning_temperature = 0;
अटल अचिन्हित पूर्णांक shutकरोwn_temperature = 0;
अटल अक्षर पढ़ो_cpu;

/* Forward declarations. */
अटल काष्ठा i2c_child_t *envctrl_get_i2c_child(अचिन्हित अक्षर);

/* Function Description: Test the PIN bit (Pending Interrupt Not) 
 * 			 to test when serial transmission is completed .
 * Return : None.
 */
अटल व्योम envtrl_i2c_test_pin(व्योम)
अणु
	पूर्णांक limit = 1000000;

	जबतक (--limit > 0) अणु
		अगर (!(पढ़ोb(i2c + PCF8584_CSR) & STATUS_PIN)) 
			अवरोध;
		udelay(1);
	पूर्ण 

	अगर (limit <= 0)
		prपूर्णांकk(KERN_INFO PFX "Pin status will not clear.\n");
पूर्ण

/* Function Description: Test busy bit.
 * Return : None.
 */
अटल व्योम envctrl_i2c_test_bb(व्योम)
अणु
	पूर्णांक limit = 1000000;

	जबतक (--limit > 0) अणु
		/* Busy bit 0 means busy. */
		अगर (पढ़ोb(i2c + PCF8584_CSR) & STATUS_BB)
			अवरोध;
		udelay(1);
	पूर्ण 

	अगर (limit <= 0)
		prपूर्णांकk(KERN_INFO PFX "Busy bit will not clear.\n");
पूर्ण

/* Function Description: Send the address क्रम a पढ़ो access.
 * Return : 0 अगर not acknowledged, otherwise acknowledged.
 */
अटल पूर्णांक envctrl_i2c_पढ़ो_addr(अचिन्हित अक्षर addr)
अणु
	envctrl_i2c_test_bb();

	/* Load address. */
	ग_लिखोb(addr + 1, i2c + PCF8584_DATA);

	envctrl_i2c_test_bb();

	ग_लिखोb(OBD_SEND_START, i2c + PCF8584_CSR);

	/* Wait क्रम PIN. */
	envtrl_i2c_test_pin();

	/* CSR 0 means acknowledged. */
	अगर (!(पढ़ोb(i2c + PCF8584_CSR) & STATUS_LRB)) अणु
		वापस पढ़ोb(i2c + PCF8584_DATA);
	पूर्ण अन्यथा अणु
		ग_लिखोb(OBD_SEND_STOP, i2c + PCF8584_CSR);
		वापस 0;
	पूर्ण
पूर्ण

/* Function Description: Send the address क्रम ग_लिखो mode.  
 * Return : None.
 */
अटल व्योम envctrl_i2c_ग_लिखो_addr(अचिन्हित अक्षर addr)
अणु
	envctrl_i2c_test_bb();
	ग_लिखोb(addr, i2c + PCF8584_DATA);

	/* Generate Start condition. */
	ग_लिखोb(OBD_SEND_START, i2c + PCF8584_CSR);
पूर्ण

/* Function Description: Read 1 byte of data from addr 
 *			 set by envctrl_i2c_पढ़ो_addr() 
 * Return : Data from address set by envctrl_i2c_पढ़ो_addr().
 */
अटल अचिन्हित अक्षर envctrl_i2c_पढ़ो_data(व्योम)
अणु
	envtrl_i2c_test_pin();
	ग_लिखोb(CONTROL_ES0, i2c + PCF8584_CSR);  /* Send neg ack. */
	वापस पढ़ोb(i2c + PCF8584_DATA);
पूर्ण

/* Function Description: Inकाष्ठा the device which port to पढ़ो data from.  
 * Return : None.
 */
अटल व्योम envctrl_i2c_ग_लिखो_data(अचिन्हित अक्षर port)
अणु
	envtrl_i2c_test_pin();
	ग_लिखोb(port, i2c + PCF8584_DATA);
पूर्ण

/* Function Description: Generate Stop condition after last byte is sent.
 * Return : None.
 */
अटल व्योम envctrl_i2c_stop(व्योम)
अणु
	envtrl_i2c_test_pin();
	ग_लिखोb(OBD_SEND_STOP, i2c + PCF8584_CSR);
पूर्ण

/* Function Description: Read adc device.
 * Return : Data at address and port.
 */
अटल अचिन्हित अक्षर envctrl_i2c_पढ़ो_8591(अचिन्हित अक्षर addr, अचिन्हित अक्षर port)
अणु
	/* Send address. */
	envctrl_i2c_ग_लिखो_addr(addr);

	/* Setup port to पढ़ो. */
	envctrl_i2c_ग_लिखो_data(port);
	envctrl_i2c_stop();

	/* Read port. */
	envctrl_i2c_पढ़ो_addr(addr);

	/* Do a single byte पढ़ो and send stop. */
	envctrl_i2c_पढ़ो_data();
	envctrl_i2c_stop();

	वापस पढ़ोb(i2c + PCF8584_DATA);
पूर्ण

/* Function Description: Read gpio device.
 * Return : Data at address.
 */
अटल अचिन्हित अक्षर envctrl_i2c_पढ़ो_8574(अचिन्हित अक्षर addr)
अणु
	अचिन्हित अक्षर rd;

	envctrl_i2c_पढ़ो_addr(addr);

	/* Do a single byte पढ़ो and send stop. */
	rd = envctrl_i2c_पढ़ो_data();
	envctrl_i2c_stop();
	वापस rd;
पूर्ण

/* Function Description: Decode data पढ़ो from an adc device using firmware
 *                       table.
 * Return: Number of पढ़ो bytes. Data is stored in bufdata in ascii क्रमmat.
 */
अटल पूर्णांक envctrl_i2c_data_translate(अचिन्हित अक्षर data, पूर्णांक translate_type,
				      पूर्णांक scale, अक्षर *tbl, अक्षर *bufdata)
अणु
	पूर्णांक len = 0;

	चयन (translate_type) अणु
	हाल ENVCTRL_TRANSLATE_NO:
		/* No decode necessary. */
		len = 1;
		bufdata[0] = data;
		अवरोध;

	हाल ENVCTRL_TRANSLATE_FULL:
		/* Decode this way: data = table[data]. */
		len = 1;
		bufdata[0] = tbl[data];
		अवरोध;

	हाल ENVCTRL_TRANSLATE_SCALE:
		/* Decode this way: data = table[data]/scale */
		प्र_लिखो(bufdata,"%d ", (tbl[data] * 10) / (scale));
		len = म_माप(bufdata);
		bufdata[len - 1] = bufdata[len - 2];
		bufdata[len - 2] = '.';
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस len;
पूर्ण

/* Function Description: Read cpu-related data such as cpu temperature, voltage.
 * Return: Number of पढ़ो bytes. Data is stored in bufdata in ascii क्रमmat.
 */
अटल पूर्णांक envctrl_पढ़ो_cpu_info(पूर्णांक cpu, काष्ठा i2c_child_t *pchild,
				 अक्षर mon_type, अचिन्हित अक्षर *bufdata)
अणु
	अचिन्हित अक्षर data;
	पूर्णांक i;
	अक्षर *tbl, j = -1;

	/* Find the right monitor type and channel. */
	क्रम (i = 0; i < PCF8584_MAX_CHANNELS; i++) अणु
		अगर (pchild->mon_type[i] == mon_type) अणु
			अगर (++j == cpu) अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (j != cpu)
		वापस 0;

        /* Read data from address and port. */
	data = envctrl_i2c_पढ़ो_8591((अचिन्हित अक्षर)pchild->addr,
				     (अचिन्हित अक्षर)pchild->chnl_array[i].chnl_no);

	/* Find decoding table. */
	tbl = pchild->tables + pchild->tblprop_array[i].offset;

	वापस envctrl_i2c_data_translate(data, pchild->tblprop_array[i].type,
					  pchild->tblprop_array[i].scale,
					  tbl, bufdata);
पूर्ण

/* Function Description: Read noncpu-related data such as motherboard 
 *                       temperature.
 * Return: Number of पढ़ो bytes. Data is stored in bufdata in ascii क्रमmat.
 */
अटल पूर्णांक envctrl_पढ़ो_noncpu_info(काष्ठा i2c_child_t *pchild,
				    अक्षर mon_type, अचिन्हित अक्षर *bufdata)
अणु
	अचिन्हित अक्षर data;
	पूर्णांक i;
	अक्षर *tbl = शून्य;

	क्रम (i = 0; i < PCF8584_MAX_CHANNELS; i++) अणु
		अगर (pchild->mon_type[i] == mon_type)
			अवरोध;
	पूर्ण

	अगर (i >= PCF8584_MAX_CHANNELS)
		वापस 0;

        /* Read data from address and port. */
	data = envctrl_i2c_पढ़ो_8591((अचिन्हित अक्षर)pchild->addr,
				     (अचिन्हित अक्षर)pchild->chnl_array[i].chnl_no);

	/* Find decoding table. */
	tbl = pchild->tables + pchild->tblprop_array[i].offset;

	वापस envctrl_i2c_data_translate(data, pchild->tblprop_array[i].type,
					  pchild->tblprop_array[i].scale,
					  tbl, bufdata);
पूर्ण

/* Function Description: Read fan status.
 * Return : Always 1 byte. Status stored in bufdata.
 */
अटल पूर्णांक envctrl_i2c_fan_status(काष्ठा i2c_child_t *pchild,
				  अचिन्हित अक्षर data,
				  अक्षर *bufdata)
अणु
	अचिन्हित अक्षर पंचांगp, ret = 0;
	पूर्णांक i, j = 0;

	पंचांगp = data & pchild->fan_mask;

	अगर (पंचांगp == pchild->fan_mask) अणु
		/* All bits are on. All fans are functioning. */
		ret = ENVCTRL_ALL_FANS_GOOD;
	पूर्ण अन्यथा अगर (पंचांगp == 0) अणु
		/* No bits are on. No fans are functioning. */
		ret = ENVCTRL_ALL_FANS_BAD;
	पूर्ण अन्यथा अणु
		/* Go through all channels, mark 'on' the matched bits.
		 * Notice that fan_mask may have discontiguous bits but
		 * वापस mask are always contiguous. For example अगर we
		 * monitor 4 fans at channels 0,1,2,4, the वापस mask
		 * should be 00010000 अगर only fan at channel 4 is working.
		 */
		क्रम (i = 0; i < PCF8584_MAX_CHANNELS;i++) अणु
			अगर (pchild->fan_mask & chnls_mask[i]) अणु
				अगर (!(chnls_mask[i] & पंचांगp))
					ret |= chnls_mask[j];

				j++;
			पूर्ण
		पूर्ण
	पूर्ण

	bufdata[0] = ret;
	वापस 1;
पूर्ण

/* Function Description: Read global addressing line.
 * Return : Always 1 byte. Status stored in bufdata.
 */
अटल पूर्णांक envctrl_i2c_globaladdr(काष्ठा i2c_child_t *pchild,
				  अचिन्हित अक्षर data,
				  अक्षर *bufdata)
अणु
	/* Translatation table is not necessary, as global
	 * addr is the पूर्णांकeger value of the GA# bits.
	 *
	 * NOTE: MSB is करोcumented as zero, but I see it as '1' always....
	 *
	 * -----------------------------------------------
	 * | 0 | FAL | DEG | GA4 | GA3 | GA2 | GA1 | GA0 |
	 * -----------------------------------------------
	 * GA0 - GA4	पूर्णांकeger value of Global Address (backplane slot#)
	 * DEG			0 = cPCI Power supply output is starting to degrade
	 * 				1 = cPCI Power supply output is OK
	 * FAL			0 = cPCI Power supply has failed
	 * 				1 = cPCI Power supply output is OK
	 */
	bufdata[0] = (data & ENVCTRL_GLOBALADDR_ADDR_MASK);
	वापस 1;
पूर्ण

/* Function Description: Read standard voltage and घातer supply status.
 * Return : Always 1 byte. Status stored in bufdata.
 */
अटल अचिन्हित अक्षर envctrl_i2c_voltage_status(काष्ठा i2c_child_t *pchild,
						अचिन्हित अक्षर data,
						अक्षर *bufdata)
अणु
	अचिन्हित अक्षर पंचांगp, ret = 0;
	पूर्णांक i, j = 0;

	पंचांगp = data & pchild->voltage_mask;

	/* Two channels are used to monitor voltage and घातer supply. */
	अगर (पंचांगp == pchild->voltage_mask) अणु
		/* All bits are on. Voltage and घातer supply are okay. */
		ret = ENVCTRL_VOLTAGE_POWERSUPPLY_GOOD;
	पूर्ण अन्यथा अगर (पंचांगp == 0) अणु
		/* All bits are off. Voltage and घातer supply are bad */
		ret = ENVCTRL_VOLTAGE_POWERSUPPLY_BAD;
	पूर्ण अन्यथा अणु
		/* Either voltage or घातer supply has problem. */
		क्रम (i = 0; i < PCF8584_MAX_CHANNELS; i++) अणु
			अगर (pchild->voltage_mask & chnls_mask[i]) अणु
				j++;

				/* Break out when there is a mismatch. */
				अगर (!(chnls_mask[i] & पंचांगp))
					अवरोध; 
			पूर्ण
		पूर्ण

		/* Make a wish that hardware will always use the
		 * first channel क्रम voltage and the second क्रम
		 * घातer supply.
		 */
		अगर (j == 1)
			ret = ENVCTRL_VOLTAGE_BAD;
		अन्यथा
			ret = ENVCTRL_POWERSUPPLY_BAD;
	पूर्ण

	bufdata[0] = ret;
	वापस 1;
पूर्ण

/* Function Description: Read a byte from /dev/envctrl. Mapped to user पढ़ो().
 * Return: Number of पढ़ो bytes. 0 क्रम error.
 */
अटल sमाप_प्रकार
envctrl_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा i2c_child_t *pchild;
	अचिन्हित अक्षर data[10];
	पूर्णांक ret = 0;

	/* Get the type of पढ़ो as decided in ioctl() call.
	 * Find the appropriate i2c child.
	 * Get the data and put back to the user buffer.
	 */

	चयन ((पूर्णांक)(दीर्घ)file->निजी_data) अणु
	हाल ENVCTRL_RD_WARNING_TEMPERATURE:
		अगर (warning_temperature == 0)
			वापस 0;

		data[0] = (अचिन्हित अक्षर)(warning_temperature);
		ret = 1;
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;

	हाल ENVCTRL_RD_SHUTDOWN_TEMPERATURE:
		अगर (shutकरोwn_temperature == 0)
			वापस 0;

		data[0] = (अचिन्हित अक्षर)(shutकरोwn_temperature);
		ret = 1;
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;

	हाल ENVCTRL_RD_MTHRBD_TEMPERATURE:
		अगर (!(pchild = envctrl_get_i2c_child(ENVCTRL_MTHRBDTEMP_MON)))
			वापस 0;
		ret = envctrl_पढ़ो_noncpu_info(pchild, ENVCTRL_MTHRBDTEMP_MON, data);
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;

	हाल ENVCTRL_RD_CPU_TEMPERATURE:
		अगर (!(pchild = envctrl_get_i2c_child(ENVCTRL_CPUTEMP_MON)))
			वापस 0;
		ret = envctrl_पढ़ो_cpu_info(पढ़ो_cpu, pchild, ENVCTRL_CPUTEMP_MON, data);

		/* Reset cpu to the शेष cpu0. */
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;

	हाल ENVCTRL_RD_CPU_VOLTAGE:
		अगर (!(pchild = envctrl_get_i2c_child(ENVCTRL_CPUVOLTAGE_MON)))
			वापस 0;
		ret = envctrl_पढ़ो_cpu_info(पढ़ो_cpu, pchild, ENVCTRL_CPUVOLTAGE_MON, data);

		/* Reset cpu to the शेष cpu0. */
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;

	हाल ENVCTRL_RD_SCSI_TEMPERATURE:
		अगर (!(pchild = envctrl_get_i2c_child(ENVCTRL_SCSITEMP_MON)))
			वापस 0;
		ret = envctrl_पढ़ो_noncpu_info(pchild, ENVCTRL_SCSITEMP_MON, data);
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;

	हाल ENVCTRL_RD_ETHERNET_TEMPERATURE:
		अगर (!(pchild = envctrl_get_i2c_child(ENVCTRL_ETHERTEMP_MON)))
			वापस 0;
		ret = envctrl_पढ़ो_noncpu_info(pchild, ENVCTRL_ETHERTEMP_MON, data);
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;

	हाल ENVCTRL_RD_FAN_STATUS:
		अगर (!(pchild = envctrl_get_i2c_child(ENVCTRL_FANSTAT_MON)))
			वापस 0;
		data[0] = envctrl_i2c_पढ़ो_8574(pchild->addr);
		ret = envctrl_i2c_fan_status(pchild,data[0], data);
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;
	
	हाल ENVCTRL_RD_GLOBALADDRESS:
		अगर (!(pchild = envctrl_get_i2c_child(ENVCTRL_GLOBALADDR_MON)))
			वापस 0;
		data[0] = envctrl_i2c_पढ़ो_8574(pchild->addr);
		ret = envctrl_i2c_globaladdr(pchild, data[0], data);
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;

	हाल ENVCTRL_RD_VOLTAGE_STATUS:
		अगर (!(pchild = envctrl_get_i2c_child(ENVCTRL_VOLTAGESTAT_MON)))
			/* If voltage monitor not present, check क्रम CPCI equivalent */
			अगर (!(pchild = envctrl_get_i2c_child(ENVCTRL_GLOBALADDR_MON)))
				वापस 0;
		data[0] = envctrl_i2c_पढ़ो_8574(pchild->addr);
		ret = envctrl_i2c_voltage_status(pchild, data[0], data);
		अगर (copy_to_user(buf, data, ret))
			ret = -EFAULT;
		अवरोध;

	शेष:
		अवरोध;

	पूर्ण

	वापस ret;
पूर्ण

/* Function Description: Command what to पढ़ो.  Mapped to user ioctl().
 * Return: Gives 0 क्रम implemented commands, -EINVAL otherwise.
 */
अटल दीर्घ
envctrl_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अक्षर __user *infobuf;

	चयन (cmd) अणु
	हाल ENVCTRL_RD_WARNING_TEMPERATURE:
	हाल ENVCTRL_RD_SHUTDOWN_TEMPERATURE:
	हाल ENVCTRL_RD_MTHRBD_TEMPERATURE:
	हाल ENVCTRL_RD_FAN_STATUS:
	हाल ENVCTRL_RD_VOLTAGE_STATUS:
	हाल ENVCTRL_RD_ETHERNET_TEMPERATURE:
	हाल ENVCTRL_RD_SCSI_TEMPERATURE:
	हाल ENVCTRL_RD_GLOBALADDRESS:
		file->निजी_data = (व्योम *)(दीर्घ)cmd;
		अवरोध;

	हाल ENVCTRL_RD_CPU_TEMPERATURE:
	हाल ENVCTRL_RD_CPU_VOLTAGE:
		/* Check to see अगर application passes in any cpu number,
		 * the शेष is cpu0.
		 */
		infobuf = (अक्षर __user *) arg;
		अगर (infobuf == शून्य) अणु
			पढ़ो_cpu = 0;
		पूर्णअन्यथा अणु
			get_user(पढ़ो_cpu, infobuf);
		पूर्ण

		/* Save the command क्रम use when पढ़ोing. */
		file->निजी_data = (व्योम *)(दीर्घ)cmd;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Function Description: खोलो device. Mapped to user खोलो().
 * Return: Always 0.
 */
अटल पूर्णांक
envctrl_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = शून्य;
	वापस 0;
पूर्ण

/* Function Description: Open device. Mapped to user बंद().
 * Return: Always 0.
 */
अटल पूर्णांक
envctrl_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations envctrl_fops = अणु
	.owner =		THIS_MODULE,
	.पढ़ो =			envctrl_पढ़ो,
	.unlocked_ioctl =	envctrl_ioctl,
	.compat_ioctl =		compat_ptr_ioctl,
	.खोलो =			envctrl_खोलो,
	.release =		envctrl_release,
	.llseek =		noop_llseek,
पूर्ण;	

अटल काष्ठा miscdevice envctrl_dev = अणु
	ENVCTRL_MINOR,
	"envctrl",
	&envctrl_fops
पूर्ण;

/* Function Description: Set monitor type based on firmware description.
 * Return: None.
 */
अटल व्योम envctrl_set_mon(काष्ठा i2c_child_t *pchild,
			    स्थिर अक्षर *chnl_desc,
			    पूर्णांक chnl_no)
अणु
	/* Firmware only has temperature type.  It करोes not distinguish
	 * dअगरferent kinds of temperatures.  We use channel description
	 * to disinguish them.
	 */
	अगर (!(म_भेद(chnl_desc,"temp,cpu")) ||
	    !(म_भेद(chnl_desc,"temp,cpu0")) ||
	    !(म_भेद(chnl_desc,"temp,cpu1")) ||
	    !(म_भेद(chnl_desc,"temp,cpu2")) ||
	    !(म_भेद(chnl_desc,"temp,cpu3")))
		pchild->mon_type[chnl_no] = ENVCTRL_CPUTEMP_MON;

	अगर (!(म_भेद(chnl_desc,"vddcore,cpu0")) ||
	    !(म_भेद(chnl_desc,"vddcore,cpu1")) ||
	    !(म_भेद(chnl_desc,"vddcore,cpu2")) ||
	    !(म_भेद(chnl_desc,"vddcore,cpu3")))
		pchild->mon_type[chnl_no] = ENVCTRL_CPUVOLTAGE_MON;

	अगर (!(म_भेद(chnl_desc,"temp,motherboard")))
		pchild->mon_type[chnl_no] = ENVCTRL_MTHRBDTEMP_MON;

	अगर (!(म_भेद(chnl_desc,"temp,scsi")))
		pchild->mon_type[chnl_no] = ENVCTRL_SCSITEMP_MON;

	अगर (!(म_भेद(chnl_desc,"temp,ethernet")))
		pchild->mon_type[chnl_no] = ENVCTRL_ETHERTEMP_MON;
पूर्ण

/* Function Description: Initialize monitor channel with channel desc,
 *                       decoding tables, monitor type, optional properties.
 * Return: None.
 */
अटल व्योम envctrl_init_adc(काष्ठा i2c_child_t *pchild, काष्ठा device_node *dp)
अणु
	पूर्णांक i = 0, len;
	स्थिर अक्षर *pos;
	स्थिर अचिन्हित पूर्णांक *pval;

	/* Firmware describe channels पूर्णांकo a stream separated by a '\0'. */
	pos = of_get_property(dp, "channels-description", &len);

	जबतक (len > 0) अणु
		पूर्णांक l = म_माप(pos) + 1;
		envctrl_set_mon(pchild, pos, i++);
		len -= l;
		pos += l;
	पूर्ण

	/* Get optional properties. */
	pval = of_get_property(dp, "warning-temp", शून्य);
	अगर (pval)
		warning_temperature = *pval;

	pval = of_get_property(dp, "shutdown-temp", शून्य);
	अगर (pval)
		shutकरोwn_temperature = *pval;
पूर्ण

/* Function Description: Initialize child device monitoring fan status.
 * Return: None.
 */
अटल व्योम envctrl_init_fanstat(काष्ठा i2c_child_t *pchild)
अणु
	पूर्णांक i;

	/* Go through all channels and set up the mask. */
	क्रम (i = 0; i < pchild->total_chnls; i++)
		pchild->fan_mask |= chnls_mask[(pchild->chnl_array[i]).chnl_no];

	/* We only need to know अगर this child has fan status monitored.
	 * We करोn't care which channels since we have the mask alपढ़ोy.
	 */
	pchild->mon_type[0] = ENVCTRL_FANSTAT_MON;
पूर्ण

/* Function Description: Initialize child device क्रम global addressing line.
 * Return: None.
 */
अटल व्योम envctrl_init_globaladdr(काष्ठा i2c_child_t *pchild)
अणु
	पूर्णांक i;

	/* Voltage/PowerSupply monitoring is piggybacked 
	 * with Global Address on CompactPCI.  See comments
	 * within envctrl_i2c_globaladdr क्रम bit assignments.
	 *
	 * The mask is created here by assigning mask bits to each
	 * bit position that represents PCF8584_VOLTAGE_TYPE data.
	 * Channel numbers are not consecutive within the globaladdr
	 * node (why?), so we use the actual counter value as chnls_mask
	 * index instead of the chnl_array[x].chnl_no value.
	 *
	 * NOTE: This loop could be replaced with a स्थिरant representing
	 * a mask of bits 5&6 (ENVCTRL_GLOBALADDR_PSTAT_MASK).
	 */
	क्रम (i = 0; i < pchild->total_chnls; i++) अणु
		अगर (PCF8584_VOLTAGE_TYPE == pchild->chnl_array[i].type) अणु
			pchild->voltage_mask |= chnls_mask[i];
		पूर्ण
	पूर्ण

	/* We only need to know अगर this child has global addressing 
	 * line monitored.  We करोn't care which channels since we know 
	 * the mask alपढ़ोy (ENVCTRL_GLOBALADDR_ADDR_MASK).
	 */
	pchild->mon_type[0] = ENVCTRL_GLOBALADDR_MON;
पूर्ण

/* Initialize child device monitoring voltage status. */
अटल व्योम envctrl_init_voltage_status(काष्ठा i2c_child_t *pchild)
अणु
	पूर्णांक i;

	/* Go through all channels and set up the mask. */
	क्रम (i = 0; i < pchild->total_chnls; i++)
		pchild->voltage_mask |= chnls_mask[(pchild->chnl_array[i]).chnl_no];

	/* We only need to know अगर this child has voltage status monitored.
	 * We करोn't care which channels since we have the mask alपढ़ोy.
	 */
	pchild->mon_type[0] = ENVCTRL_VOLTAGESTAT_MON;
पूर्ण

/* Function Description: Initialize i2c child device.
 * Return: None.
 */
अटल व्योम envctrl_init_i2c_child(काष्ठा device_node *dp,
				   काष्ठा i2c_child_t *pchild)
अणु
	पूर्णांक len, i, tbls_size = 0;
	स्थिर व्योम *pval;

	/* Get device address. */
	pval = of_get_property(dp, "reg", &len);
	स_नकल(&pchild->addr, pval, len);

	/* Get tables property.  Read firmware temperature tables. */
	pval = of_get_property(dp, "translation", &len);
	अगर (pval && len > 0) अणु
		स_नकल(pchild->tblprop_array, pval, len);
                pchild->total_tbls = len / माप(काष्ठा pcf8584_tblprop);
		क्रम (i = 0; i < pchild->total_tbls; i++) अणु
			अगर ((pchild->tblprop_array[i].size + pchild->tblprop_array[i].offset) > tbls_size) अणु
				tbls_size = pchild->tblprop_array[i].size + pchild->tblprop_array[i].offset;
			पूर्ण
		पूर्ण

                pchild->tables = kदो_स्मृति(tbls_size, GFP_KERNEL);
		अगर (pchild->tables == शून्य)अणु
			prपूर्णांकk(KERN_ERR PFX "Failed to allocate table.\n");
			वापस;
		पूर्ण
		pval = of_get_property(dp, "tables", &len);
                अगर (!pval || len <= 0) अणु
			prपूर्णांकk(KERN_ERR PFX "Failed to get table.\n");
			वापस;
		पूर्ण
		स_नकल(pchild->tables, pval, len);
	पूर्ण

	/* SPARCengine ASM Reference Manual (ref. SMI करोc 805-7581-04)
	 * sections 2.5, 3.5, 4.5 state node 0x70 क्रम CP1400/1500 is
	 * "For Factory Use Only."
	 *
	 * We ignore the node on these platक्रमms by assigning the
	 * 'NULL' monitor type.
	 */
	अगर (ENVCTRL_CPCI_IGNORED_NODE == pchild->addr) अणु
		काष्ठा device_node *root_node;
		पूर्णांक len;

		root_node = of_find_node_by_path("/");
		अगर (of_node_name_eq(root_node, "SUNW,UltraSPARC-IIi-cEngine")) अणु
			क्रम (len = 0; len < PCF8584_MAX_CHANNELS; ++len) अणु
				pchild->mon_type[len] = ENVCTRL_NOMON;
			पूर्ण
			of_node_put(root_node);
			वापस;
		पूर्ण
		of_node_put(root_node);
	पूर्ण

	/* Get the monitor channels. */
	pval = of_get_property(dp, "channels-in-use", &len);
	स_नकल(pchild->chnl_array, pval, len);
	pchild->total_chnls = len / माप(काष्ठा pcf8584_channel);

	क्रम (i = 0; i < pchild->total_chnls; i++) अणु
		चयन (pchild->chnl_array[i].type) अणु
		हाल PCF8584_TEMP_TYPE:
			envctrl_init_adc(pchild, dp);
			अवरोध;

		हाल PCF8584_GLOBALADDR_TYPE:
			envctrl_init_globaladdr(pchild);
			i = pchild->total_chnls;
			अवरोध;

		हाल PCF8584_FANSTAT_TYPE:
			envctrl_init_fanstat(pchild);
			i = pchild->total_chnls;
			अवरोध;

		हाल PCF8584_VOLTAGE_TYPE:
			अगर (pchild->i2ctype == I2C_ADC) अणु
				envctrl_init_adc(pchild,dp);
			पूर्ण अन्यथा अणु
				envctrl_init_voltage_status(pchild);
			पूर्ण
			i = pchild->total_chnls;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Function Description: Search the child device list क्रम a device.
 * Return : The i2c child अगर found. शून्य otherwise.
 */
अटल काष्ठा i2c_child_t *envctrl_get_i2c_child(अचिन्हित अक्षर mon_type)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < ENVCTRL_MAX_CPU*2; i++) अणु
		क्रम (j = 0; j < PCF8584_MAX_CHANNELS; j++) अणु
			अगर (i2c_childlist[i].mon_type[j] == mon_type) अणु
				वापस (काष्ठा i2c_child_t *)(&(i2c_childlist[i]));
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम envctrl_करो_shutकरोwn(व्योम)
अणु
	अटल पूर्णांक inprog = 0;

	अगर (inprog != 0)
		वापस;

	inprog = 1;
	prपूर्णांकk(KERN_CRIT "kenvctrld: WARNING: Shutting down the system now.\n");
	orderly_घातeroff(true);
पूर्ण

अटल काष्ठा task_काष्ठा *kenvctrld_task;

अटल पूर्णांक kenvctrld(व्योम *__unused)
अणु
	पूर्णांक poll_पूर्णांकerval;
	पूर्णांक whichcpu;
	अक्षर tempbuf[10];
	काष्ठा i2c_child_t *cputemp;

	अगर (शून्य == (cputemp = envctrl_get_i2c_child(ENVCTRL_CPUTEMP_MON))) अणु
		prपूर्णांकk(KERN_ERR  PFX
		       "kenvctrld unable to monitor CPU temp-- exiting\n");
		वापस -ENODEV;
	पूर्ण

	poll_पूर्णांकerval = 5000; /* TODO env_mon_पूर्णांकerval */

	prपूर्णांकk(KERN_INFO PFX "%s starting...\n", current->comm);
	क्रम (;;) अणु
		msleep_पूर्णांकerruptible(poll_पूर्णांकerval);

		अगर (kthपढ़ो_should_stop())
			अवरोध;
		
		क्रम (whichcpu = 0; whichcpu < ENVCTRL_MAX_CPU; ++whichcpu) अणु
			अगर (0 < envctrl_पढ़ो_cpu_info(whichcpu, cputemp,
						      ENVCTRL_CPUTEMP_MON,
						      tempbuf)) अणु
				अगर (tempbuf[0] >= shutकरोwn_temperature) अणु
					prपूर्णांकk(KERN_CRIT 
						"%s: WARNING: CPU%i temperature %i C meets or exceeds "\
						"shutdown threshold %i C\n", 
						current->comm, whichcpu, 
						tempbuf[0], shutकरोwn_temperature);
					envctrl_करो_shutकरोwn();
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_INFO PFX "%s exiting...\n", current->comm);
	वापस 0;
पूर्ण

अटल पूर्णांक envctrl_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp;
	पूर्णांक index, err;

	अगर (i2c)
		वापस -EINVAL;

	i2c = of_ioremap(&op->resource[0], 0, 0x2, DRIVER_NAME);
	अगर (!i2c)
		वापस -ENOMEM;

	index = 0;
	dp = op->dev.of_node->child;
	जबतक (dp) अणु
		अगर (of_node_name_eq(dp, "gpio")) अणु
			i2c_childlist[index].i2ctype = I2C_GPIO;
			envctrl_init_i2c_child(dp, &(i2c_childlist[index++]));
		पूर्ण अन्यथा अगर (of_node_name_eq(dp, "adc")) अणु
			i2c_childlist[index].i2ctype = I2C_ADC;
			envctrl_init_i2c_child(dp, &(i2c_childlist[index++]));
		पूर्ण

		dp = dp->sibling;
	पूर्ण

	/* Set device address. */
	ग_लिखोb(CONTROL_PIN, i2c + PCF8584_CSR);
	ग_लिखोb(PCF8584_ADDRESS, i2c + PCF8584_DATA);

	/* Set प्रणाली घड़ी and SCL frequencies. */ 
	ग_लिखोb(CONTROL_PIN | CONTROL_ES1, i2c + PCF8584_CSR);
	ग_लिखोb(CLK_4_43 | BUS_CLK_90, i2c + PCF8584_DATA);

	/* Enable serial पूर्णांकerface. */
	ग_लिखोb(CONTROL_PIN | CONTROL_ES0 | CONTROL_ACK, i2c + PCF8584_CSR);
	udelay(200);

	/* Register the device as a minor miscellaneous device. */
	err = misc_रेजिस्टर(&envctrl_dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to get misc minor %d\n",
		       envctrl_dev.minor);
		जाओ out_iounmap;
	पूर्ण

	/* Note above traversal routine post-incremented 'i' to accommodate 
	 * a next child device, so we decrement beक्रमe reverse-traversal of
	 * child devices.
	 */
	prपूर्णांकk(KERN_INFO PFX "Initialized ");
	क्रम (--index; index >= 0; --index) अणु
		prपूर्णांकk("[%s 0x%lx]%s", 
			(I2C_ADC == i2c_childlist[index].i2ctype) ? "adc" : 
			((I2C_GPIO == i2c_childlist[index].i2ctype) ? "gpio" : "unknown"), 
			i2c_childlist[index].addr, (0 == index) ? "\n" : " ");
	पूर्ण

	kenvctrld_task = kthपढ़ो_run(kenvctrld, शून्य, "kenvctrld");
	अगर (IS_ERR(kenvctrld_task)) अणु
		err = PTR_ERR(kenvctrld_task);
		जाओ out_deरेजिस्टर;
	पूर्ण

	वापस 0;

out_deरेजिस्टर:
	misc_deरेजिस्टर(&envctrl_dev);
out_iounmap:
	of_iounmap(&op->resource[0], i2c, 0x2);
	क्रम (index = 0; index < ENVCTRL_MAX_CPU * 2; index++)
		kमुक्त(i2c_childlist[index].tables);

	वापस err;
पूर्ण

अटल पूर्णांक envctrl_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	पूर्णांक index;

	kthपढ़ो_stop(kenvctrld_task);

	of_iounmap(&op->resource[0], i2c, 0x2);
	misc_deरेजिस्टर(&envctrl_dev);

	क्रम (index = 0; index < ENVCTRL_MAX_CPU * 2; index++)
		kमुक्त(i2c_childlist[index].tables);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id envctrl_match[] = अणु
	अणु
		.name = "i2c",
		.compatible = "i2cpcf,8584",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, envctrl_match);

अटल काष्ठा platक्रमm_driver envctrl_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = envctrl_match,
	पूर्ण,
	.probe		= envctrl_probe,
	.हटाओ		= envctrl_हटाओ,
पूर्ण;

module_platक्रमm_driver(envctrl_driver);

MODULE_LICENSE("GPL");
