<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Miscellaneous Mac68K-specअगरic stuff
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>
#समावेश <linux/rtc.h>
#समावेश <linux/mm.h>

#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#समावेश <linux/pmu.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/mac_via.h>
#समावेश <यंत्र/mac_oss.h>

#समावेश <यंत्र/machdep.h>

/*
 * Offset between Unix समय (1970-based) and Mac समय (1904-based). Cuda and PMU
 * बार wrap in 2040. If we need to handle later बार, the पढ़ो_समय functions
 * need to be changed to पूर्णांकerpret wrapped बार as post-2040.
 */

#घोषणा RTC_OFFSET 2082844800

अटल व्योम (*rom_reset)(व्योम);

#अगर IS_ENABLED(CONFIG_NVRAM)
#अगर_घोषित CONFIG_ADB_CUDA
अटल अचिन्हित अक्षर cuda_pram_पढ़ो_byte(पूर्णांक offset)
अणु
	काष्ठा adb_request req;

	अगर (cuda_request(&req, शून्य, 4, CUDA_PACKET, CUDA_GET_PRAM,
			 (offset >> 8) & 0xFF, offset & 0xFF) < 0)
		वापस 0;
	जबतक (!req.complete)
		cuda_poll();
	वापस req.reply[3];
पूर्ण

अटल व्योम cuda_pram_ग_लिखो_byte(अचिन्हित अक्षर data, पूर्णांक offset)
अणु
	काष्ठा adb_request req;

	अगर (cuda_request(&req, शून्य, 5, CUDA_PACKET, CUDA_SET_PRAM,
			 (offset >> 8) & 0xFF, offset & 0xFF, data) < 0)
		वापस;
	जबतक (!req.complete)
		cuda_poll();
पूर्ण
#पूर्ण_अगर /* CONFIG_ADB_CUDA */

#अगर_घोषित CONFIG_ADB_PMU
अटल अचिन्हित अक्षर pmu_pram_पढ़ो_byte(पूर्णांक offset)
अणु
	काष्ठा adb_request req;

	अगर (pmu_request(&req, शून्य, 3, PMU_READ_XPRAM,
	                offset & 0xFF, 1) < 0)
		वापस 0;
	pmu_रुको_complete(&req);

	वापस req.reply[0];
पूर्ण

अटल व्योम pmu_pram_ग_लिखो_byte(अचिन्हित अक्षर data, पूर्णांक offset)
अणु
	काष्ठा adb_request req;

	अगर (pmu_request(&req, शून्य, 4, PMU_WRITE_XPRAM,
	                offset & 0xFF, 1, data) < 0)
		वापस;
	pmu_रुको_complete(&req);
पूर्ण
#पूर्ण_अगर /* CONFIG_ADB_PMU */
#पूर्ण_अगर /* CONFIG_NVRAM */

/*
 * VIA PRAM/RTC access routines
 *
 * Must be called with पूर्णांकerrupts disabled and
 * the RTC should be enabled.
 */

अटल __u8 via_rtc_recv(व्योम)
अणु
	पूर्णांक i, reg;
	__u8 data;

	reg = via1[vBufB] & ~VIA1B_vRTCClk;

	/* Set the RTC data line to be an input. */

	via1[vDirB] &= ~VIA1B_vRTCData;

	/* The bits of the byte come out in MSB order */

	data = 0;
	क्रम (i = 0 ; i < 8 ; i++) अणु
		via1[vBufB] = reg;
		via1[vBufB] = reg | VIA1B_vRTCClk;
		data = (data << 1) | (via1[vBufB] & VIA1B_vRTCData);
	पूर्ण

	/* Return RTC data line to output state */

	via1[vDirB] |= VIA1B_vRTCData;

	वापस data;
पूर्ण

अटल व्योम via_rtc_send(__u8 data)
अणु
	पूर्णांक i, reg, bit;

	reg = via1[vBufB] & ~(VIA1B_vRTCClk | VIA1B_vRTCData);

	/* The bits of the byte go in in MSB order */

	क्रम (i = 0 ; i < 8 ; i++) अणु
		bit = data & 0x80? 1 : 0;
		data <<= 1;
		via1[vBufB] = reg | bit;
		via1[vBufB] = reg | bit | VIA1B_vRTCClk;
	पूर्ण
पूर्ण

/*
 * These values can be found in Inside Macपूर्णांकosh vol. III ch. 2
 * which has a description of the RTC chip in the original Mac.
 */

#घोषणा RTC_FLG_READ            BIT(7)
#घोषणा RTC_FLG_WRITE_PROTECT   BIT(7)
#घोषणा RTC_CMD_READ(r)         (RTC_FLG_READ | (r << 2))
#घोषणा RTC_CMD_WRITE(r)        (r << 2)
#घोषणा RTC_REG_SECONDS_0       0
#घोषणा RTC_REG_SECONDS_1       1
#घोषणा RTC_REG_SECONDS_2       2
#घोषणा RTC_REG_SECONDS_3       3
#घोषणा RTC_REG_WRITE_PROTECT   13

/*
 * Inside Mac has no inक्रमmation about two-byte RTC commands but
 * the MAME/MESS source code has the essentials.
 */

#घोषणा RTC_REG_XPRAM           14
#घोषणा RTC_CMD_XPRAM_READ      (RTC_CMD_READ(RTC_REG_XPRAM) << 8)
#घोषणा RTC_CMD_XPRAM_WRITE     (RTC_CMD_WRITE(RTC_REG_XPRAM) << 8)
#घोषणा RTC_CMD_XPRAM_ARG(a)    (((a & 0xE0) << 3) | ((a & 0x1F) << 2))

/*
 * Execute a VIA PRAM/RTC command. For पढ़ो commands
 * data should poपूर्णांक to a one-byte buffer क्रम the
 * resulting data. For ग_लिखो commands it should poपूर्णांक
 * to the data byte to क्रम the command.
 *
 * This function disables all पूर्णांकerrupts जबतक running.
 */

अटल व्योम via_rtc_command(पूर्णांक command, __u8 *data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक is_पढ़ो;

	local_irq_save(flags);

	/* The least signअगरicant bits must be 0b01 according to Inside Mac */

	command = (command & ~3) | 1;

	/* Enable the RTC and make sure the strobe line is high */

	via1[vBufB] = (via1[vBufB] | VIA1B_vRTCClk) & ~VIA1B_vRTCEnb;

	अगर (command & 0xFF00) अणु		/* extended (two-byte) command */
		via_rtc_send((command & 0xFF00) >> 8);
		via_rtc_send(command & 0xFF);
		is_पढ़ो = command & (RTC_FLG_READ << 8);
	पूर्ण अन्यथा अणु			/* one-byte command */
		via_rtc_send(command);
		is_पढ़ो = command & RTC_FLG_READ;
	पूर्ण
	अगर (is_पढ़ो) अणु
		*data = via_rtc_recv();
	पूर्ण अन्यथा अणु
		via_rtc_send(*data);
	पूर्ण

	/* All करोne, disable the RTC */

	via1[vBufB] |= VIA1B_vRTCEnb;

	local_irq_restore(flags);
पूर्ण

#अगर IS_ENABLED(CONFIG_NVRAM)
अटल अचिन्हित अक्षर via_pram_पढ़ो_byte(पूर्णांक offset)
अणु
	अचिन्हित अक्षर temp;

	via_rtc_command(RTC_CMD_XPRAM_READ | RTC_CMD_XPRAM_ARG(offset), &temp);

	वापस temp;
पूर्ण

अटल व्योम via_pram_ग_लिखो_byte(अचिन्हित अक्षर data, पूर्णांक offset)
अणु
	अचिन्हित अक्षर temp;

	temp = 0x55;
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_WRITE_PROTECT), &temp);

	temp = data;
	via_rtc_command(RTC_CMD_XPRAM_WRITE | RTC_CMD_XPRAM_ARG(offset), &temp);

	temp = 0x55 | RTC_FLG_WRITE_PROTECT;
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_WRITE_PROTECT), &temp);
पूर्ण
#पूर्ण_अगर /* CONFIG_NVRAM */

/*
 * Return the current समय in seconds since January 1, 1904.
 *
 * This only works on machines with the VIA-based PRAM/RTC, which
 * is basically any machine with Mac II-style ADB.
 */

अटल समय64_t via_पढ़ो_समय(व्योम)
अणु
	जोड़ अणु
		__u8 cdata[4];
		__u32 idata;
	पूर्ण result, last_result;
	पूर्णांक count = 1;

	via_rtc_command(RTC_CMD_READ(RTC_REG_SECONDS_0), &last_result.cdata[3]);
	via_rtc_command(RTC_CMD_READ(RTC_REG_SECONDS_1), &last_result.cdata[2]);
	via_rtc_command(RTC_CMD_READ(RTC_REG_SECONDS_2), &last_result.cdata[1]);
	via_rtc_command(RTC_CMD_READ(RTC_REG_SECONDS_3), &last_result.cdata[0]);

	/*
	 * The NetBSD guys say to loop until you get the same पढ़ोing
	 * twice in a row.
	 */

	जबतक (1) अणु
		via_rtc_command(RTC_CMD_READ(RTC_REG_SECONDS_0),
		                &result.cdata[3]);
		via_rtc_command(RTC_CMD_READ(RTC_REG_SECONDS_1),
		                &result.cdata[2]);
		via_rtc_command(RTC_CMD_READ(RTC_REG_SECONDS_2),
		                &result.cdata[1]);
		via_rtc_command(RTC_CMD_READ(RTC_REG_SECONDS_3),
		                &result.cdata[0]);

		अगर (result.idata == last_result.idata)
			वापस (समय64_t)result.idata - RTC_OFFSET;

		अगर (++count > 10)
			अवरोध;

		last_result.idata = result.idata;
	पूर्ण

	pr_err("%s: failed to read a stable value; got 0x%08x then 0x%08x\n",
	       __func__, last_result.idata, result.idata);

	वापस 0;
पूर्ण

/*
 * Set the current समय to a number of seconds since January 1, 1904.
 *
 * This only works on machines with the VIA-based PRAM/RTC, which
 * is basically any machine with Mac II-style ADB.
 */

अटल व्योम via_set_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	जोड़ अणु
		__u8 cdata[4];
		__u32 idata;
	पूर्ण data;
	__u8 temp;
	समय64_t समय;

	समय = स_गढ़ो64(पंचांग->पंचांग_year + 1900, पंचांग->पंचांग_mon + 1, पंचांग->पंचांग_mday,
	                पंचांग->पंचांग_hour, पंचांग->पंचांग_min, पंचांग->पंचांग_sec);

	/* Clear the ग_लिखो protect bit */

	temp = 0x55;
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_WRITE_PROTECT), &temp);

	data.idata = lower_32_bits(समय + RTC_OFFSET);
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_SECONDS_0), &data.cdata[3]);
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_SECONDS_1), &data.cdata[2]);
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_SECONDS_2), &data.cdata[1]);
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_SECONDS_3), &data.cdata[0]);

	/* Set the ग_लिखो protect bit */

	temp = 0x55 | RTC_FLG_WRITE_PROTECT;
	via_rtc_command(RTC_CMD_WRITE(RTC_REG_WRITE_PROTECT), &temp);
पूर्ण

अटल व्योम via_shutकरोwn(व्योम)
अणु
	अगर (rbv_present) अणु
		via2[rBufB] &= ~0x04;
	पूर्ण अन्यथा अणु
		/* Direction of vDirB is output */
		via2[vDirB] |= 0x04;
		/* Send a value of 0 on that line */
		via2[vBufB] &= ~0x04;
		mdelay(1000);
	पूर्ण
पूर्ण

अटल व्योम oss_shutकरोwn(व्योम)
अणु
	oss->rom_ctrl = OSS_POWEROFF;
पूर्ण

#अगर_घोषित CONFIG_ADB_CUDA
अटल व्योम cuda_restart(व्योम)
अणु
	काष्ठा adb_request req;

	अगर (cuda_request(&req, शून्य, 2, CUDA_PACKET, CUDA_RESET_SYSTEM) < 0)
		वापस;
	जबतक (!req.complete)
		cuda_poll();
पूर्ण

अटल व्योम cuda_shutकरोwn(व्योम)
अणु
	काष्ठा adb_request req;

	अगर (cuda_request(&req, शून्य, 2, CUDA_PACKET, CUDA_POWERDOWN) < 0)
		वापस;

	/* Aव्योम infinite polling loop when PSU is not under Cuda control */
	चयन (macपूर्णांकosh_config->ident) अणु
	हाल MAC_MODEL_C660:
	हाल MAC_MODEL_Q605:
	हाल MAC_MODEL_Q605_ACC:
	हाल MAC_MODEL_P475:
	हाल MAC_MODEL_P475F:
		वापस;
	पूर्ण

	जबतक (!req.complete)
		cuda_poll();
पूर्ण
#पूर्ण_अगर /* CONFIG_ADB_CUDA */

/*
 *-------------------------------------------------------------------
 * Below this poपूर्णांक are the generic routines; they'll dispatch to the
 * correct routine क्रम the hardware on which we're running.
 *-------------------------------------------------------------------
 */

#अगर IS_ENABLED(CONFIG_NVRAM)
अचिन्हित अक्षर mac_pram_पढ़ो_byte(पूर्णांक addr)
अणु
	चयन (macपूर्णांकosh_config->adb_type) अणु
	हाल MAC_ADB_IOP:
	हाल MAC_ADB_II:
	हाल MAC_ADB_PB1:
		वापस via_pram_पढ़ो_byte(addr);
#अगर_घोषित CONFIG_ADB_CUDA
	हाल MAC_ADB_EGRET:
	हाल MAC_ADB_CUDA:
		वापस cuda_pram_पढ़ो_byte(addr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
	हाल MAC_ADB_PB2:
		वापस pmu_pram_पढ़ो_byte(addr);
#पूर्ण_अगर
	शेष:
		वापस 0xFF;
	पूर्ण
पूर्ण

व्योम mac_pram_ग_लिखो_byte(अचिन्हित अक्षर val, पूर्णांक addr)
अणु
	चयन (macपूर्णांकosh_config->adb_type) अणु
	हाल MAC_ADB_IOP:
	हाल MAC_ADB_II:
	हाल MAC_ADB_PB1:
		via_pram_ग_लिखो_byte(val, addr);
		अवरोध;
#अगर_घोषित CONFIG_ADB_CUDA
	हाल MAC_ADB_EGRET:
	हाल MAC_ADB_CUDA:
		cuda_pram_ग_लिखो_byte(val, addr);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
	हाल MAC_ADB_PB2:
		pmu_pram_ग_लिखो_byte(val, addr);
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

sमाप_प्रकार mac_pram_get_size(व्योम)
अणु
	वापस 256;
पूर्ण
#पूर्ण_अगर /* CONFIG_NVRAM */

व्योम mac_घातeroff(व्योम)
अणु
	अगर (oss_present) अणु
		oss_shutकरोwn();
	पूर्ण अन्यथा अगर (macपूर्णांकosh_config->adb_type == MAC_ADB_II) अणु
		via_shutकरोwn();
#अगर_घोषित CONFIG_ADB_CUDA
	पूर्ण अन्यथा अगर (macपूर्णांकosh_config->adb_type == MAC_ADB_EGRET ||
	           macपूर्णांकosh_config->adb_type == MAC_ADB_CUDA) अणु
		cuda_shutकरोwn();
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
	पूर्ण अन्यथा अगर (macपूर्णांकosh_config->adb_type == MAC_ADB_PB2) अणु
		pmu_shutकरोwn();
#पूर्ण_अगर
	पूर्ण

	pr_crit("It is now safe to turn off your Macintosh.\n");
	local_irq_disable();
	जबतक(1);
पूर्ण

व्योम mac_reset(व्योम)
अणु
	अगर (macपूर्णांकosh_config->adb_type == MAC_ADB_II &&
	    macपूर्णांकosh_config->ident != MAC_MODEL_SE30) अणु
		/* need ROMBASE in booter */
		/* indeed, plus need to MAP THE ROM !! */

		अगर (mac_bi_data.rombase == 0)
			mac_bi_data.rombase = 0x40800000;

		/* works on some */
		rom_reset = (व्योम *) (mac_bi_data.rombase + 0xa);

		local_irq_disable();
		rom_reset();
#अगर_घोषित CONFIG_ADB_CUDA
	पूर्ण अन्यथा अगर (macपूर्णांकosh_config->adb_type == MAC_ADB_EGRET ||
	           macपूर्णांकosh_config->adb_type == MAC_ADB_CUDA) अणु
		cuda_restart();
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
	पूर्ण अन्यथा अगर (macपूर्णांकosh_config->adb_type == MAC_ADB_PB2) अणु
		pmu_restart();
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (CPU_IS_030) अणु

		/* 030-specअगरic reset routine.  The idea is general, but the
		 * specअगरic रेजिस्टरs to reset are '030-specअगरic.  Until I
		 * have a non-030 machine, I can't test anything अन्यथा.
		 *  -- C. Scott Ananian <cananian@alumni.princeton.edu>
		 */

		अचिन्हित दीर्घ rombase = 0x40000000;

		/* make a 1-to-1 mapping, using the transparent tran. reg. */
		अचिन्हित दीर्घ virt = (अचिन्हित दीर्घ) mac_reset;
		अचिन्हित दीर्घ phys = virt_to_phys(mac_reset);
		अचिन्हित दीर्घ addr = (phys&0xFF000000)|0x8777;
		अचिन्हित दीर्घ offset = phys-virt;

		local_irq_disable(); /* lets not screw this up, ok? */
		__यंत्र__ __अस्थिर__(".chip 68030\n\t"
				     "pmove %0,%/tt0\n\t"
				     ".chip 68k"
				     : : "m" (addr));
		/* Now jump to physical address so we can disable MMU */
		__यंत्र__ __अस्थिर__(
		    ".chip 68030\n\t"
		    "lea %/pc@(1f),%/a0\n\t"
		    "addl %0,%/a0\n\t"/* fixup target address and stack ptr */
		    "addl %0,%/sp\n\t"
		    "pflusha\n\t"
		    "jmp %/a0@\n\t" /* jump पूर्णांकo physical memory */
		    "0:.long 0\n\t" /* a स्थिरant zero. */
		    /* OK.  Now reset everything and jump to reset vector. */
		    "1:\n\t"
		    "lea %/pc@(0b),%/a0\n\t"
		    "pmove %/a0@, %/tc\n\t" /* disable mmu */
		    "pmove %/a0@, %/tt0\n\t" /* disable tt0 */
		    "pmove %/a0@, %/tt1\n\t" /* disable tt1 */
		    "movel #0, %/a0\n\t"
		    "movec %/a0, %/vbr\n\t" /* clear vector base रेजिस्टर */
		    "movec %/a0, %/cacr\n\t" /* disable caches */
		    "movel #0x0808,%/a0\n\t"
		    "movec %/a0, %/cacr\n\t" /* flush i&d caches */
		    "movew #0x2700,%/sr\n\t" /* set up status रेजिस्टर */
		    "movel %1@(0x0),%/a0\n\t"/* load पूर्णांकerrupt stack poपूर्णांकer */
		    "movec %/a0, %/isp\n\t"
		    "movel %1@(0x4),%/a0\n\t" /* load reset vector */
		    "reset\n\t" /* reset बाह्यal devices */
		    "jmp %/a0@\n\t" /* jump to the reset vector */
		    ".chip 68k"
		    : : "r" (offset), "a" (rombase) : "a0");
	पूर्ण

	/* should never get here */
	pr_crit("Restart failed. Please restart manually.\n");
	local_irq_disable();
	जबतक(1);
पूर्ण

/*
 * This function translates seconds since 1970 पूर्णांकo a proper date.
 *
 * Algorithm cribbed from glibc2.1, __offसमय().
 *
 * This is roughly same as rtc_समय64_to_पंचांग(), which we should probably
 * use here, but it's only available when CONFIG_RTC_LIB is enabled.
 */
#घोषणा SECS_PER_MINUTE (60)
#घोषणा SECS_PER_HOUR  (SECS_PER_MINUTE * 60)
#घोषणा SECS_PER_DAY   (SECS_PER_HOUR * 24)

अटल व्योम unस_गढ़ो(समय64_t समय, दीर्घ offset,
		     पूर्णांक *yearp, पूर्णांक *monp, पूर्णांक *dayp,
		     पूर्णांक *hourp, पूर्णांक *minp, पूर्णांक *secp)
अणु
        /* How many days come beक्रमe each month (0-12).  */
	अटल स्थिर अचिन्हित लघु पूर्णांक __mon_yday[2][13] =
	अणु
		/* Normal years.  */
		अणु 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 पूर्ण,
		/* Leap years.  */
		अणु 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 पूर्ण
	पूर्ण;
	पूर्णांक days, rem, y, wday, yday;
	स्थिर अचिन्हित लघु पूर्णांक *ip;

	days = भाग_u64_rem(समय, SECS_PER_DAY, &rem);
	rem += offset;
	जबतक (rem < 0) अणु
		rem += SECS_PER_DAY;
		--days;
	पूर्ण
	जबतक (rem >= SECS_PER_DAY) अणु
		rem -= SECS_PER_DAY;
		++days;
	पूर्ण
	*hourp = rem / SECS_PER_HOUR;
	rem %= SECS_PER_HOUR;
	*minp = rem / SECS_PER_MINUTE;
	*secp = rem % SECS_PER_MINUTE;
	/* January 1, 1970 was a Thursday. */
	wday = (4 + days) % 7; /* Day in the week. Not currently used */
	अगर (wday < 0) wday += 7;
	y = 1970;

#घोषणा DIV(a, b) ((a) / (b) - ((a) % (b) < 0))
#घोषणा LEAPS_THRU_END_OF(y) (DIV (y, 4) - DIV (y, 100) + DIV (y, 400))
#घोषणा __isleap(year)	\
  ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))

	जबतक (days < 0 || days >= (__isleap (y) ? 366 : 365))
	अणु
		/* Guess a corrected year, assuming 365 days per year.  */
		दीर्घ पूर्णांक yg = y + days / 365 - (days % 365 < 0);

		/* Adjust DAYS and Y to match the guessed year.  */
		days -= (yg - y) * 365 +
			LEAPS_THRU_END_OF(yg - 1) - LEAPS_THRU_END_OF(y - 1);
		y = yg;
	पूर्ण
	*yearp = y - 1900;
	yday = days; /* day in the year.  Not currently used. */
	ip = __mon_yday[__isleap(y)];
	क्रम (y = 11; days < (दीर्घ पूर्णांक) ip[y]; --y)
		जारी;
	days -= ip[y];
	*monp = y;
	*dayp = days + 1; /* day in the month */
	वापस;
पूर्ण

/*
 * Read/ग_लिखो the hardware घड़ी.
 */

पूर्णांक mac_hwclk(पूर्णांक op, काष्ठा rtc_समय *t)
अणु
	समय64_t now;

	अगर (!op) अणु /* पढ़ो */
		चयन (macपूर्णांकosh_config->adb_type) अणु
		हाल MAC_ADB_IOP:
		हाल MAC_ADB_II:
		हाल MAC_ADB_PB1:
			now = via_पढ़ो_समय();
			अवरोध;
#अगर_घोषित CONFIG_ADB_CUDA
		हाल MAC_ADB_EGRET:
		हाल MAC_ADB_CUDA:
			now = cuda_get_समय();
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
		हाल MAC_ADB_PB2:
			now = pmu_get_समय();
			अवरोध;
#पूर्ण_अगर
		शेष:
			now = 0;
		पूर्ण

		t->पंचांग_wday = 0;
		unस_गढ़ो(now, 0,
			 &t->पंचांग_year, &t->पंचांग_mon, &t->पंचांग_mday,
			 &t->पंचांग_hour, &t->पंचांग_min, &t->पंचांग_sec);
		pr_debug("%s: read %ptR\n", __func__, t);
	पूर्ण अन्यथा अणु /* ग_लिखो */
		pr_debug("%s: tried to write %ptR\n", __func__, t);

		चयन (macपूर्णांकosh_config->adb_type) अणु
		हाल MAC_ADB_IOP:
		हाल MAC_ADB_II:
		हाल MAC_ADB_PB1:
			via_set_rtc_समय(t);
			अवरोध;
#अगर_घोषित CONFIG_ADB_CUDA
		हाल MAC_ADB_EGRET:
		हाल MAC_ADB_CUDA:
			cuda_set_rtc_समय(t);
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ADB_PMU
		हाल MAC_ADB_PB2:
			pmu_set_rtc_समय(t);
			अवरोध;
#पूर्ण_अगर
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
