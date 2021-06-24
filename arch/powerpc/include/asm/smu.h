<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SMU_H
#घोषणा _SMU_H

/*
 * Definitions क्रम talking to the SMU chip in newer G5 PowerMacs
 */
#अगर_घोषित __KERNEL__
#समावेश <linux/list.h>
#पूर्ण_अगर
#समावेश <linux/types.h>

/*
 * Known SMU commands
 *
 * Most of what is below comes from looking at the Open Firmware driver,
 * though this is still incomplete and could use better करोcumentation here
 * or there...
 */


/*
 * Partition info commands
 *
 * These commands are used to retrieve the sdb-partition-XX datas from
 * the SMU. The length is always 2. First byte is the subcommand code
 * and second byte is the partition ID.
 *
 * The reply is 6 bytes:
 *
 *  - 0..1 : partition address
 *  - 2    : a byte containing the partition ID
 *  - 3    : length (maybe other bits are rest of header ?)
 *
 * The data must then be obtained with calls to another command:
 * SMU_CMD_MISC_ee_GET_DATABLOCK_REC (described below).
 */
#घोषणा SMU_CMD_PARTITION_COMMAND		0x3e
#घोषणा   SMU_CMD_PARTITION_LATEST		0x01
#घोषणा   SMU_CMD_PARTITION_BASE		0x02
#घोषणा   SMU_CMD_PARTITION_UPDATE		0x03


/*
 * Fan control
 *
 * This is a "mux" क्रम fan control commands. The command seem to
 * act dअगरferently based on the number of arguments. With 1 byte
 * of argument, this seem to be queries क्रम fans status, setpoपूर्णांक,
 * etc..., जबतक with 0xe arguments, we will set the fans speeds.
 *
 * Queries (1 byte arg):
 * ---------------------
 *
 * arg=0x01: पढ़ो RPM fans status
 * arg=0x02: पढ़ो RPM fans setpoपूर्णांक
 * arg=0x11: पढ़ो PWM fans status
 * arg=0x12: पढ़ो PWM fans setpoपूर्णांक
 *
 * the "status" queries वापस the current speed जबतक the "setpoint" ones
 * वापस the programmed/target speed. It _seems_ that the result is a bit
 * mask in the first byte of active/available fans, followed by 6 words (16
 * bits) containing the requested speed.
 *
 * Setpoपूर्णांक (14 bytes arg):
 * ------------------------
 *
 * first arg byte is 0 क्रम RPM fans and 0x10 क्रम PWM. Second arg byte is the
 * mask of fans affected by the command. Followed by 6 words containing the
 * setpoपूर्णांक value क्रम selected fans in the mask (or 0 अगर mask value is 0)
 */
#घोषणा SMU_CMD_FAN_COMMAND			0x4a


/*
 * Battery access
 *
 * Same command number as the PMU, could it be same syntax ?
 */
#घोषणा SMU_CMD_BATTERY_COMMAND			0x6f
#घोषणा   SMU_CMD_GET_BATTERY_INFO		0x00

/*
 * Real समय घड़ी control
 *
 * This is a "mux", first data byte contains the "sub" command.
 * The "RTC" part of the SMU controls the date, समय, घातerup
 * समयr, but also a PRAM
 *
 * Dates are in BCD क्रमmat on 7 bytes:
 * [sec] [min] [hour] [weekday] [month day] [month] [year]
 * with month being 1 based and year minus 100
 */
#घोषणा SMU_CMD_RTC_COMMAND			0x8e
#घोषणा   SMU_CMD_RTC_SET_PWRUP_TIMER		0x00 /* i: 7 bytes date */
#घोषणा   SMU_CMD_RTC_GET_PWRUP_TIMER		0x01 /* o: 7 bytes date */
#घोषणा   SMU_CMD_RTC_STOP_PWRUP_TIMER		0x02
#घोषणा   SMU_CMD_RTC_SET_PRAM_BYTE_ACC		0x20 /* i: 1 byte (address?) */
#घोषणा   SMU_CMD_RTC_SET_PRAM_AUTOINC		0x21 /* i: 1 byte (data?) */
#घोषणा   SMU_CMD_RTC_SET_PRAM_LO_BYTES 	0x22 /* i: 10 bytes */
#घोषणा   SMU_CMD_RTC_SET_PRAM_HI_BYTES 	0x23 /* i: 10 bytes */
#घोषणा   SMU_CMD_RTC_GET_PRAM_BYTE		0x28 /* i: 1 bytes (address?) */
#घोषणा   SMU_CMD_RTC_GET_PRAM_LO_BYTES 	0x29 /* o: 10 bytes */
#घोषणा   SMU_CMD_RTC_GET_PRAM_HI_BYTES 	0x2a /* o: 10 bytes */
#घोषणा	  SMU_CMD_RTC_SET_DATETIME		0x80 /* i: 7 bytes date */
#घोषणा   SMU_CMD_RTC_GET_DATETIME		0x81 /* o: 7 bytes date */

 /*
  * i2c commands
  *
  * To issue an i2c command, first is to send a parameter block to
  * the SMU. This is a command of type 0x9a with 9 bytes of header
  * eventually followed by data क्रम a ग_लिखो:
  *
  * 0: bus number (from device-tree usually, SMU has lots of busses !)
  * 1: transfer type/क्रमmat (see below)
  * 2: device address. For combined and combined4 type transfers, this
  *    is the "write" version of the address (bit 0x01 cleared)
  * 3: subaddress length (0..3)
  * 4: subaddress byte 0 (or only byte क्रम subaddress length 1)
  * 5: subaddress byte 1
  * 6: subaddress byte 2
  * 7: combined address (device address क्रम combined mode data phase)
  * 8: data length
  *
  * The transfer types are the same good old Apple ones it seems,
  * that is:
  *   - 0x00: Simple transfer
  *   - 0x01: Subaddress transfer (addr ग_लिखो + data tx, no restart)
  *   - 0x02: Combined transfer (addr ग_लिखो + restart + data tx)
  *
  * This is then followed by actual data क्रम a ग_लिखो.
  *
  * At this poपूर्णांक, the OF driver seems to have a limitation on transfer
  * sizes of 0xd bytes on पढ़ोs and 0x5 bytes on ग_लिखोs. I करो not know
  * whether this is just an OF limit due to some temporary buffer size
  * or अगर this is an SMU imposed limit. This driver has the same limitation
  * क्रम now as I use a 0x10 bytes temporary buffer as well
  *
  * Once that is completed, a response is expected from the SMU. This is
  * obtained via a command of type 0x9a with a length of 1 byte containing
  * 0 as the data byte. OF also fills the rest of the data buffer with 0xff's
  * though I can't tell yet अगर this is actually necessary. Once this command
  * is complete, at this poपूर्णांक, all I can tell is what OF करोes. OF tests
  * byte 0 of the reply:
  *   - on पढ़ो, 0xfe or 0xfc : bus is busy, रुको (see below) or nak ?
  *   - on पढ़ो, 0x00 or 0x01 : reply is in buffer (after the byte 0)
  *   - on ग_लिखो, < 0 -> failure (immediate निकास)
  *   - अन्यथा, OF just exists (without error, weird)
  *
  * So on पढ़ो, there is this रुको-क्रम-busy thing when getting a 0xfc or
  * 0xfe result. OF करोes a loop of up to 64 retries, रुकोing 20ms and
  * करोing the above again until either the retries expire or the result
  * is no दीर्घer 0xfe or 0xfc
  *
  * The Darwin I2C driver is less subtle though. On any non-success status
  * from the response command, it रुकोs 5ms and tries again up to 20 बार,
  * it करोesn't dअगरferentiate between fatal errors or "busy" status.
  *
  * This driver provides an asynchronous paramblock based i2c command
  * पूर्णांकerface to be used either directly by low level code or by a higher
  * level driver पूर्णांकerfacing to the linux i2c layer. The current
  * implementation of this relies on working समयrs & समयr पूर्णांकerrupts
  * though, so be careful of calling context क्रम now. This may be "fixed"
  * in the future by adding a polling facility.
  */
#घोषणा SMU_CMD_I2C_COMMAND			0x9a
          /* transfer types */
#घोषणा   SMU_I2C_TRANSFER_SIMPLE	0x00
#घोषणा   SMU_I2C_TRANSFER_STDSUB	0x01
#घोषणा   SMU_I2C_TRANSFER_COMBINED	0x02

/*
 * Power supply control
 *
 * The "sub" command is an ASCII string in the data, the
 * data length is that of the string.
 *
 * The VSLEW command can be used to get or set the voltage slewing.
 *  - length 5 (only "VSLEW") : it वापसs "DONE" and 3 bytes of
 *    reply at data offset 6, 7 and 8.
 *  - length 8 ("VSLEWxyz") has 3 additional bytes appended, and is
 *    used to set the voltage slewing poपूर्णांक. The SMU replies with "DONE"
 * I yet have to figure out their exact meaning of those 3 bytes in
 * both हालs. They seem to be:
 *  x = processor mask
 *  y = op. poपूर्णांक index
 *  z = processor freq. step index
 * I haven't yet deciphered result codes
 *
 */
#घोषणा SMU_CMD_POWER_COMMAND			0xaa
#घोषणा   SMU_CMD_POWER_RESTART		       	"RESTART"
#घोषणा   SMU_CMD_POWER_SHUTDOWN		"SHUTDOWN"
#घोषणा   SMU_CMD_POWER_VOLTAGE_SLEW		"VSLEW"

/*
 * Read ADC sensors
 *
 * This command takes one byte of parameter: the sensor ID (or "reg"
 * value in the device-tree) and वापसs a 16 bits value
 */
#घोषणा SMU_CMD_READ_ADC			0xd8


/* Misc commands
 *
 * This command seem to be a grab bag of various things
 *
 * Parameters:
 *   1: subcommand
 */
#घोषणा SMU_CMD_MISC_df_COMMAND			0xdf

/*
 * Sets "system ready" status
 *
 * I did not yet understand how it exactly works or what it करोes.
 *
 * Guessing from OF code, 0x02 activates the display backlight. Apple uses/used
 * the same codebase क्रम all OF versions. On PowerBooks, this command would
 * enable the backlight. For the G5s, it only activates the front LED. However,
 * करोn't take this क्रम granted.
 *
 * Parameters:
 *   2: status [0x00, 0x01 or 0x02]
 */
#घोषणा   SMU_CMD_MISC_df_SET_DISPLAY_LIT	0x02

/*
 * Sets mode of घातer चयन.
 *
 * What this actually करोes is not yet known. Maybe it enables some पूर्णांकerrupt.
 *
 * Parameters:
 *   2: enable घातer चयन? [0x00 or 0x01]
 *   3 (optional): enable nmi? [0x00 or 0x01]
 *
 * Returns:
 *   If parameter 2 is 0x00 and parameter 3 is not specअगरied, वापसs whether
 *   NMI is enabled. Otherwise unknown.
 */
#घोषणा   SMU_CMD_MISC_df_NMI_OPTION		0x04

/* Sets LED dimm offset.
 *
 * The front LED dimms itself during sleep. Its brightness (or, well, the PWM
 * frequency) depends on current समय. Thereक्रमe, the SMU needs to know the
 * समयzone.
 *
 * Parameters:
 *   2-8: unknown (BCD coding)
 */
#घोषणा   SMU_CMD_MISC_df_DIMM_OFFSET		0x99


/*
 * Version info commands
 *
 * Parameters:
 *   1 (optional): Specअगरies version part to retrieve
 *
 * Returns:
 *   Version value
 */
#घोषणा SMU_CMD_VERSION_COMMAND			0xea
#घोषणा   SMU_VERSION_RUNNING			0x00
#घोषणा   SMU_VERSION_BASE			0x01
#घोषणा   SMU_VERSION_UPDATE			0x02


/*
 * Switches
 *
 * These are चयनes whose status seems to be known to the SMU.
 *
 * Parameters:
 *   none
 *
 * Result:
 *   Switch bits (ORed, see below)
 */
#घोषणा SMU_CMD_SWITCHES			0xdc

/* Switches bits */
#घोषणा SMU_SWITCH_CASE_CLOSED			0x01
#घोषणा SMU_SWITCH_AC_POWER			0x04
#घोषणा SMU_SWITCH_POWER_SWITCH			0x08


/*
 * Misc commands
 *
 * This command seem to be a grab bag of various things
 *
 * SMU_CMD_MISC_ee_GET_DATABLOCK_REC is used, among others, to
 * transfer blocks of data from the SMU. So far, I've decrypted it's
 * usage to retrieve partition data. In order to करो that, you have to
 * अवरोध your transfer in "chunks" since that command cannot transfer
 * more than a chunk at a समय. The chunk size used by OF is 0xe bytes,
 * but it seems that the darwin driver will let you करो 0x1e bytes अगर
 * your "PMU" version is >= 0x30. You can get the "PMU" version apparently
 * either in the last 16 bits of property "smu-version-pmu" or as the 16
 * bytes at offset 1 of "smu-version-info"
 *
 * For each chunk, the command takes 7 bytes of arguments:
 *  byte 0: subcommand code (0x02)
 *  byte 1: 0x04 (always, I करोn't know what it means, maybe the address
 *                space to use or some other nicety. It's hard coded in OF)
 *  byte 2..5: SMU address of the chunk (big endian 32 bits)
 *  byte 6: size to transfer (up to max chunk size)
 *
 * The data is वापसed directly
 */
#घोषणा SMU_CMD_MISC_ee_COMMAND			0xee
#घोषणा   SMU_CMD_MISC_ee_GET_DATABLOCK_REC	0x02

/* Retrieves currently used watts.
 *
 * Parameters:
 *   1: 0x03 (Meaning unknown)
 */
#घोषणा   SMU_CMD_MISC_ee_GET_WATTS		0x03

#घोषणा   SMU_CMD_MISC_ee_LEDS_CTRL		0x04 /* i: 00 (00,01) [00] */
#घोषणा   SMU_CMD_MISC_ee_GET_DATA		0x05 /* i: 00 , o: ?? */


/*
 * Power related commands
 *
 * Parameters:
 *   1: subcommand
 */
#घोषणा SMU_CMD_POWER_EVENTS_COMMAND		0x8f

/* SMU_POWER_EVENTS subcommands */
क्रमागत अणु
	SMU_PWR_GET_POWERUP_EVENTS      = 0x00,
	SMU_PWR_SET_POWERUP_EVENTS      = 0x01,
	SMU_PWR_CLR_POWERUP_EVENTS      = 0x02,
	SMU_PWR_GET_WAKEUP_EVENTS       = 0x03,
	SMU_PWR_SET_WAKEUP_EVENTS       = 0x04,
	SMU_PWR_CLR_WAKEUP_EVENTS       = 0x05,

	/*
	 * Get last shutकरोwn cause
	 *
	 * Returns:
	 *   1 byte (चिन्हित अक्षर): Last shutकरोwn cause. Exact meaning unknown.
	 */
	SMU_PWR_LAST_SHUTDOWN_CAUSE	= 0x07,

	/*
	 * Sets or माला_लो server ID. Meaning or use is unknown.
	 *
	 * Parameters:
	 *   2 (optional): Set server ID (1 byte)
	 *
	 * Returns:
	 *   1 byte (server ID?)
	 */
	SMU_PWR_SERVER_ID		= 0x08,
पूर्ण;

/* Power events wakeup bits */
क्रमागत अणु
	SMU_PWR_WAKEUP_KEY              = 0x01, /* Wake on key press */
	SMU_PWR_WAKEUP_AC_INSERT        = 0x02, /* Wake on AC adapter plug */
	SMU_PWR_WAKEUP_AC_CHANGE        = 0x04,
	SMU_PWR_WAKEUP_LID_OPEN         = 0x08,
	SMU_PWR_WAKEUP_RING             = 0x10,
पूर्ण;


/*
 * - Kernel side पूर्णांकerface -
 */

#अगर_घोषित __KERNEL__

/*
 * Asynchronous SMU commands
 *
 * Fill up this काष्ठाure and submit it via smu_queue_command(),
 * and get notअगरied by the optional करोne() callback, or because
 * status becomes != 1
 */

काष्ठा smu_cmd;

काष्ठा smu_cmd
अणु
	/* खुला */
	u8			cmd;		/* command */
	पूर्णांक			data_len;	/* data len */
	पूर्णांक			reply_len;	/* reply len */
	व्योम			*data_buf;	/* data buffer */
	व्योम			*reply_buf;	/* reply buffer */
	पूर्णांक			status;		/* command status */
	व्योम			(*करोne)(काष्ठा smu_cmd *cmd, व्योम *misc);
	व्योम			*misc;

	/* निजी */
	काष्ठा list_head	link;
पूर्ण;

/*
 * Queues an SMU command, all fields have to be initialized
 */
बाह्य पूर्णांक smu_queue_cmd(काष्ठा smu_cmd *cmd);

/*
 * Simple command wrapper. This काष्ठाure embeds a small buffer
 * to ease sending simple SMU commands from the stack
 */
काष्ठा smu_simple_cmd
अणु
	काष्ठा smu_cmd	cmd;
	u8	       	buffer[16];
पूर्ण;

/*
 * Queues a simple command. All fields will be initialized by that
 * function
 */
बाह्य पूर्णांक smu_queue_simple(काष्ठा smu_simple_cmd *scmd, u8 command,
			    अचिन्हित पूर्णांक data_len,
			    व्योम (*करोne)(काष्ठा smu_cmd *cmd, व्योम *misc),
			    व्योम *misc,
			    ...);

/*
 * Completion helper. Pass it to smu_queue_simple or as 'done'
 * member to smu_queue_cmd, it will call complete() on the काष्ठा
 * completion passed in the "misc" argument
 */
बाह्य व्योम smu_करोne_complete(काष्ठा smu_cmd *cmd, व्योम *misc);

/*
 * Synchronous helpers. Will spin-रुको क्रम completion of a command
 */
बाह्य व्योम smu_spinरुको_cmd(काष्ठा smu_cmd *cmd);

अटल अंतरभूत व्योम smu_spinरुको_simple(काष्ठा smu_simple_cmd *scmd)
अणु
	smu_spinरुको_cmd(&scmd->cmd);
पूर्ण

/*
 * Poll routine to call अगर blocked with irqs off
 */
बाह्य व्योम smu_poll(व्योम);


/*
 * Init routine, presence check....
 */
बाह्य पूर्णांक smu_init(व्योम);
बाह्य पूर्णांक smu_present(व्योम);
काष्ठा platक्रमm_device;
बाह्य काष्ठा platक्रमm_device *smu_get_ofdev(व्योम);


/*
 * Common command wrappers
 */
बाह्य व्योम smu_shutकरोwn(व्योम);
बाह्य व्योम smu_restart(व्योम);
काष्ठा rtc_समय;
बाह्य पूर्णांक smu_get_rtc_समय(काष्ठा rtc_समय *समय, पूर्णांक spinरुको);
बाह्य पूर्णांक smu_set_rtc_समय(काष्ठा rtc_समय *समय, पूर्णांक spinरुको);

/*
 * Kernel asynchronous i2c पूर्णांकerface
 */

#घोषणा SMU_I2C_READ_MAX	0x1d
#घोषणा SMU_I2C_WRITE_MAX	0x15

/* SMU i2c header, exactly matches i2c header on wire */
काष्ठा smu_i2c_param
अणु
	u8	bus;		/* SMU bus ID (from device tree) */
	u8	type;		/* i2c transfer type */
	u8	devaddr;	/* device address (includes direction) */
	u8	sublen;		/* subaddress length */
	u8	subaddr[3];	/* subaddress */
	u8	caddr;		/* combined address, filled by SMU driver */
	u8	datalen;	/* length of transfer */
	u8	data[SMU_I2C_READ_MAX];	/* data */
पूर्ण;

काष्ठा smu_i2c_cmd
अणु
	/* खुला */
	काष्ठा smu_i2c_param	info;
	व्योम			(*करोne)(काष्ठा smu_i2c_cmd *cmd, व्योम *misc);
	व्योम			*misc;
	पूर्णांक			status; /* 1 = pending, 0 = ok, <0 = fail */

	/* निजी */
	काष्ठा smu_cmd		scmd;
	पूर्णांक			पढ़ो;
	पूर्णांक			stage;
	पूर्णांक			retries;
	u8			pdata[32];
	काष्ठा list_head	link;
पूर्ण;

/*
 * Call this to queue an i2c command to the SMU. You must fill info,
 * including info.data क्रम a ग_लिखो, करोne and misc.
 * For now, no polling पूर्णांकerface is provided so you have to use completion
 * callback.
 */
बाह्य पूर्णांक smu_queue_i2c(काष्ठा smu_i2c_cmd *cmd);


#पूर्ण_अगर /* __KERNEL__ */


/*
 * - SMU "sdb" partitions inक्रमmations -
 */


/*
 * Partition header क्रमmat
 */
काष्ठा smu_sdbp_header अणु
	__u8	id;
	__u8	len;
	__u8	version;
	__u8	flags;
पूर्ण;


 /*
 * demangle 16 and 32 bits पूर्णांकeger in some SMU partitions
 * (currently, afaik, this concerns only the FVT partition
 * (0x12)
 */
#घोषणा SMU_U16_MIX(x)	le16_to_cpu(x)
#घोषणा SMU_U32_MIX(x)  ((((x) & 0xff00ff00u) >> 8)|(((x) & 0x00ff00ffu) << 8))


/* This is the definition of the SMU sdb-partition-0x12 table (called
 * CPU F/V/T operating poपूर्णांकs in Darwin). The definition क्रम all those
 * SMU tables should be moved to some separate file
 */
#घोषणा SMU_SDB_FVT_ID			0x12

काष्ठा smu_sdbp_fvt अणु
	__u32	sysclk;			/* Base SysClk frequency in Hz क्रम
					 * this operating poपूर्णांक. Value need to
					 * be unmixed with SMU_U32_MIX()
					 */
	__u8	pad;
	__u8	maxtemp;		/* Max temp. supported by this
					 * operating poपूर्णांक
					 */

	__u16	volts[3];		/* CPU core voltage क्रम the 3
					 * PowerTune modes, a mode with
					 * 0V = not supported. Value need
					 * to be unmixed with SMU_U16_MIX()
					 */
पूर्ण;

/* This partition contains voltage & current sensor calibration
 * inक्रमmations
 */
#घोषणा SMU_SDB_CPUVCP_ID		0x21

काष्ठा smu_sdbp_cpuvcp अणु
	__u16	volt_scale;		/* u4.12 fixed poपूर्णांक */
	__s16	volt_offset;		/* s4.12 fixed poपूर्णांक */
	__u16	curr_scale;		/* u4.12 fixed poपूर्णांक */
	__s16	curr_offset;		/* s4.12 fixed poपूर्णांक */
	__s32	घातer_quads[3];		/* s4.28 fixed poपूर्णांक */
पूर्ण;

/* This partition contains CPU thermal diode calibration
 */
#घोषणा SMU_SDB_CPUDIODE_ID		0x18

काष्ठा smu_sdbp_cpudiode अणु
	__u16	m_value;		/* u1.15 fixed poपूर्णांक */
	__s16	b_value;		/* s10.6 fixed poपूर्णांक */

पूर्ण;

/* This partition contains Slots घातer calibration
 */
#घोषणा SMU_SDB_SLOTSPOW_ID		0x78

काष्ठा smu_sdbp_slotsघात अणु
	__u16	घात_scale;		/* u4.12 fixed poपूर्णांक */
	__s16	घात_offset;		/* s4.12 fixed poपूर्णांक */
पूर्ण;

/* This partition contains machine specअगरic version inक्रमmation about
 * the sensor/control layout
 */
#घोषणा SMU_SDB_SENSORTREE_ID		0x25

काष्ठा smu_sdbp_sensortree अणु
	__u8	model_id;
	__u8	unknown[3];
पूर्ण;

/* This partition contains CPU thermal control PID inक्रमmations. So far
 * only single CPU machines have been seen with an SMU, so we assume this
 * carries only inक्रमmations क्रम those
 */
#घोषणा SMU_SDB_CPUPIDDATA_ID		0x17

काष्ठा smu_sdbp_cpupiddata अणु
	__u8	unknown1;
	__u8	target_temp_delta;
	__u8	unknown2;
	__u8	history_len;
	__s16	घातer_adj;
	__u16	max_घातer;
	__s32	gp,gr,gd;
पूर्ण;


/* Other partitions without known काष्ठाures */
#घोषणा SMU_SDB_DEBUG_SWITCHES_ID	0x05

#अगर_घोषित __KERNEL__
/*
 * This वापसs the poपूर्णांकer to an SMU "sdb" partition data or शून्य
 * अगर not found. The data क्रमmat is described below
 */
बाह्य स्थिर काष्ठा smu_sdbp_header *smu_get_sdb_partition(पूर्णांक id,
					अचिन्हित पूर्णांक *size);

/* Get "sdb" partition data from an SMU satellite */
बाह्य काष्ठा smu_sdbp_header *smu_sat_get_sdb_partition(अचिन्हित पूर्णांक sat_id,
					पूर्णांक id, अचिन्हित पूर्णांक *size);


#पूर्ण_अगर /* __KERNEL__ */


/*
 * - Userland पूर्णांकerface -
 */

/*
 * A given instance of the device can be configured क्रम 2 dअगरferent
 * things at the moment:
 *
 *  - sending SMU commands (शेष at खोलो() समय)
 *  - receiving SMU events (not yet implemented)
 *
 * Commands are written with ग_लिखो() of a command block. They can be
 * "driver" commands (क्रम example to चयन to event reception mode)
 * or real SMU commands. They are made of a header followed by command
 * data अगर any.
 *
 * For SMU commands (not क्रम driver commands), you can then पढ़ो() back
 * a reply. The पढ़ोer will be blocked or not depending on how the device
 * file is खोलोed. poll() isn't implemented yet. The reply will consist
 * of a header as well, followed by the reply data अगर any. You should
 * always provide a buffer large enough क्रम the maximum reply data, I
 * recommand one page.
 *
 * It is illegal to send SMU commands through a file descriptor configured
 * क्रम events reception
 *
 */
काष्ठा smu_user_cmd_hdr
अणु
	__u32		cmdtype;
#घोषणा SMU_CMDTYPE_SMU			0	/* SMU command */
#घोषणा SMU_CMDTYPE_WANTS_EVENTS	1	/* चयन fd to events mode */
#घोषणा SMU_CMDTYPE_GET_PARTITION	2	/* retrieve an sdb partition */

	__u8		cmd;			/* SMU command byte */
	__u8		pad[3];			/* padding */
	__u32		data_len;		/* Length of data following */
पूर्ण;

काष्ठा smu_user_reply_hdr
अणु
	__u32		status;			/* Command status */
	__u32		reply_len;		/* Length of data follwing */
पूर्ण;

#पूर्ण_अगर /*  _SMU_H */
