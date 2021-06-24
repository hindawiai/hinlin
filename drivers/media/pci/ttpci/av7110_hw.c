<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * av7110_hw.c: av7110 low level hardware access and firmware पूर्णांकerface
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * originally based on code by:
 * Copyright (C) 1998,1999 Christian Theiss <mistert@rz.fh-augsburg.de>
 *
 * the project's page is at https://linuxtv.org
 */

/* क्रम debugging ARM communication: */
//#घोषणा COM_DEBUG

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>

#समावेश "av7110.h"
#समावेश "av7110_hw.h"

#घोषणा _NOHANDSHAKE

/*
 * Max transfer size करोne by av7110_fw_cmd()
 *
 * The maximum size passed to this function is 6 bytes. The buffer also
 * uses two additional ones क्रम type and size. So, 8 bytes is enough.
 */
#घोषणा MAX_XFER_SIZE  8

/****************************************************************************
 * DEBI functions
 ****************************************************************************/

/* This DEBI code is based on the Stradis driver
   by Nathan Lareकरो <lareकरो@gnu.org> */

पूर्णांक av7110_debiग_लिखो(काष्ठा av7110 *av7110, u32 config,
		     पूर्णांक addr, u32 val, अचिन्हित पूर्णांक count)
अणु
	काष्ठा saa7146_dev *dev = av7110->dev;

	अगर (count > 32764) अणु
		prपूर्णांकk("%s: invalid count %d\n", __func__, count);
		वापस -1;
	पूर्ण
	अगर (saa7146_रुको_क्रम_debi_करोne(av7110->dev, 0) < 0) अणु
		prपूर्णांकk("%s: wait_for_debi_done failed\n", __func__);
		वापस -1;
	पूर्ण
	saa7146_ग_लिखो(dev, DEBI_CONFIG, config);
	अगर (count <= 4)		/* immediate transfer */
		saa7146_ग_लिखो(dev, DEBI_AD, val);
	अन्यथा			/* block transfer */
		saa7146_ग_लिखो(dev, DEBI_AD, av7110->debi_bus);
	saa7146_ग_लिखो(dev, DEBI_COMMAND, (count << 17) | (addr & 0xffff));
	saa7146_ग_लिखो(dev, MC2, (2 << 16) | 2);
	वापस 0;
पूर्ण

u32 av7110_debiपढ़ो(काष्ठा av7110 *av7110, u32 config, पूर्णांक addr, अचिन्हित पूर्णांक count)
अणु
	काष्ठा saa7146_dev *dev = av7110->dev;
	u32 result = 0;

	अगर (count > 32764) अणु
		prपूर्णांकk("%s: invalid count %d\n", __func__, count);
		वापस 0;
	पूर्ण
	अगर (saa7146_रुको_क्रम_debi_करोne(av7110->dev, 0) < 0) अणु
		prपूर्णांकk("%s: wait_for_debi_done #1 failed\n", __func__);
		वापस 0;
	पूर्ण
	saa7146_ग_लिखो(dev, DEBI_AD, av7110->debi_bus);
	saa7146_ग_लिखो(dev, DEBI_COMMAND, (count << 17) | 0x10000 | (addr & 0xffff));

	saa7146_ग_लिखो(dev, DEBI_CONFIG, config);
	saa7146_ग_लिखो(dev, MC2, (2 << 16) | 2);
	अगर (count > 4)
		वापस count;
	अगर (saa7146_रुको_क्रम_debi_करोne(av7110->dev, 0) < 0) अणु
		prपूर्णांकk("%s: wait_for_debi_done #2 failed\n", __func__);
		वापस 0;
	पूर्ण

	result = saa7146_पढ़ो(dev, DEBI_AD);
	result &= (0xffffffffUL >> ((4 - count) * 8));
	वापस result;
पूर्ण



/* av7110 ARM core boot stuff */
#अगर 0
व्योम av7110_reset_arm(काष्ठा av7110 *av7110)
अणु
	saa7146_setgpio(av7110->dev, RESET_LINE, SAA7146_GPIO_OUTLO);

	/* Disable DEBI and GPIO irq */
	SAA7146_IER_DISABLE(av7110->dev, MASK_19 | MASK_03);
	SAA7146_ISR_CLEAR(av7110->dev, MASK_19 | MASK_03);

	saa7146_setgpio(av7110->dev, RESET_LINE, SAA7146_GPIO_OUTHI);
	msleep(30);	/* the firmware needs some समय to initialize */

	ARM_ResetMailBox(av7110);

	SAA7146_ISR_CLEAR(av7110->dev, MASK_19 | MASK_03);
	SAA7146_IER_ENABLE(av7110->dev, MASK_03);

	av7110->arm_पढ़ोy = 1;
	dprपूर्णांकk(1, "reset ARM\n");
पूर्ण
#पूर्ण_अगर  /*  0  */

अटल पूर्णांक रुकोdebi(काष्ठा av7110 *av7110, पूर्णांक adr, पूर्णांक state)
अणु
	पूर्णांक k;

	dprपूर्णांकk(4, "%p\n", av7110);

	क्रम (k = 0; k < 100; k++) अणु
		अगर (irdebi(av7110, DEBINOSWAP, adr, 0, 2) == state)
			वापस 0;
		udelay(5);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक load_dram(काष्ठा av7110 *av7110, u32 *data, पूर्णांक len)
अणु
	पूर्णांक i;
	पूर्णांक blocks, rest;
	u32 base, bootblock = AV7110_BOOT_BLOCK;

	dprपूर्णांकk(4, "%p\n", av7110);

	blocks = len / AV7110_BOOT_MAX_SIZE;
	rest = len % AV7110_BOOT_MAX_SIZE;
	base = DRAM_START_CODE;

	क्रम (i = 0; i < blocks; i++) अणु
		अगर (रुकोdebi(av7110, AV7110_BOOT_STATE, BOOTSTATE_BUFFER_EMPTY) < 0) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: load_dram(): timeout at block %d\n", i);
			वापस -ETIMEDOUT;
		पूर्ण
		dprपूर्णांकk(4, "writing DRAM block %d\n", i);
		mwdebi(av7110, DEBISWAB, bootblock,
		       ((u8 *)data) + i * AV7110_BOOT_MAX_SIZE, AV7110_BOOT_MAX_SIZE);
		bootblock ^= 0x1400;
		iwdebi(av7110, DEBISWAB, AV7110_BOOT_BASE, swab32(base), 4);
		iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_SIZE, AV7110_BOOT_MAX_SIZE, 2);
		iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_STATE, BOOTSTATE_BUFFER_FULL, 2);
		base += AV7110_BOOT_MAX_SIZE;
	पूर्ण

	अगर (rest > 0) अणु
		अगर (रुकोdebi(av7110, AV7110_BOOT_STATE, BOOTSTATE_BUFFER_EMPTY) < 0) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: load_dram(): timeout at last block\n");
			वापस -ETIMEDOUT;
		पूर्ण
		अगर (rest > 4)
			mwdebi(av7110, DEBISWAB, bootblock,
			       ((u8 *)data) + i * AV7110_BOOT_MAX_SIZE, rest);
		अन्यथा
			mwdebi(av7110, DEBISWAB, bootblock,
			       ((u8 *)data) + i * AV7110_BOOT_MAX_SIZE - 4, rest + 4);

		iwdebi(av7110, DEBISWAB, AV7110_BOOT_BASE, swab32(base), 4);
		iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_SIZE, rest, 2);
		iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_STATE, BOOTSTATE_BUFFER_FULL, 2);
	पूर्ण
	अगर (रुकोdebi(av7110, AV7110_BOOT_STATE, BOOTSTATE_BUFFER_EMPTY) < 0) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: load_dram(): timeout after last block\n");
		वापस -ETIMEDOUT;
	पूर्ण
	iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_SIZE, 0, 2);
	iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_STATE, BOOTSTATE_BUFFER_FULL, 2);
	अगर (रुकोdebi(av7110, AV7110_BOOT_STATE, BOOTSTATE_AV7110_BOOT_COMPLETE) < 0) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: load_dram(): final handshake timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण


/* we cannot ग_लिखो av7110 DRAM directly, so load a bootloader पूर्णांकo
 * the DPRAM which implements a simple boot protocol */
पूर्णांक av7110_bootarm(काष्ठा av7110 *av7110)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name = "av7110/bootcode.bin";
	काष्ठा saa7146_dev *dev = av7110->dev;
	u32 ret;
	पूर्णांक i;

	dprपूर्णांकk(4, "%p\n", av7110);

	av7110->arm_पढ़ोy = 0;

	saa7146_setgpio(dev, RESET_LINE, SAA7146_GPIO_OUTLO);

	/* Disable DEBI and GPIO irq */
	SAA7146_IER_DISABLE(av7110->dev, MASK_03 | MASK_19);
	SAA7146_ISR_CLEAR(av7110->dev, MASK_19 | MASK_03);

	/* enable DEBI */
	saa7146_ग_लिखो(av7110->dev, MC1, 0x08800880);
	saa7146_ग_लिखो(av7110->dev, DD1_STREAM_B, 0x00000000);
	saa7146_ग_लिखो(av7110->dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	/* test DEBI */
	iwdebi(av7110, DEBISWAP, DPRAM_BASE, 0x76543210, 4);
	/* FIXME: Why करोes Nexus CA require 2x iwdebi क्रम first init? */
	iwdebi(av7110, DEBISWAP, DPRAM_BASE, 0x76543210, 4);

	अगर ((ret=irdebi(av7110, DEBINOSWAP, DPRAM_BASE, 0, 4)) != 0x10325476) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: debi test in av7110_bootarm() failed: %08x != %08x (check your BIOS 'Plug&Play OS' settings)\n",
		       ret, 0x10325476);
		वापस -1;
	पूर्ण
	क्रम (i = 0; i < 8192; i += 4)
		iwdebi(av7110, DEBISWAP, DPRAM_BASE + i, 0x00, 4);
	dprपूर्णांकk(2, "debi test OK\n");

	/* boot */
	dprपूर्णांकk(1, "load boot code\n");
	saa7146_setgpio(dev, ARM_IRQ_LINE, SAA7146_GPIO_IRQLO);
	//saa7146_setgpio(dev, DEBI_DONE_LINE, SAA7146_GPIO_INPUT);
	//saa7146_setgpio(dev, 3, SAA7146_GPIO_INPUT);

	ret = request_firmware(&fw, fw_name, &dev->pci->dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: Failed to load firmware \"%s\"\n",
			fw_name);
		वापस ret;
	पूर्ण

	mwdebi(av7110, DEBISWAB, DPRAM_BASE, fw->data, fw->size);
	release_firmware(fw);
	iwdebi(av7110, DEBINOSWAP, AV7110_BOOT_STATE, BOOTSTATE_BUFFER_FULL, 2);

	अगर (saa7146_रुको_क्रम_debi_करोne(av7110->dev, 1)) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: av7110_bootarm(): saa7146_wait_for_debi_done() timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण
	saa7146_setgpio(dev, RESET_LINE, SAA7146_GPIO_OUTHI);
	mdelay(1);

	dprपूर्णांकk(1, "load dram code\n");
	अगर (load_dram(av7110, (u32 *)av7110->bin_root, av7110->size_root) < 0) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: av7110_bootarm(): load_dram() failed\n");
		वापस -1;
	पूर्ण

	saa7146_setgpio(dev, RESET_LINE, SAA7146_GPIO_OUTLO);
	mdelay(1);

	dprपूर्णांकk(1, "load dpram code\n");
	mwdebi(av7110, DEBISWAB, DPRAM_BASE, av7110->bin_dpram, av7110->size_dpram);

	अगर (saa7146_रुको_क्रम_debi_करोne(av7110->dev, 1)) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: av7110_bootarm(): saa7146_wait_for_debi_done() timed out after loading DRAM\n");
		वापस -ETIMEDOUT;
	पूर्ण
	saa7146_setgpio(dev, RESET_LINE, SAA7146_GPIO_OUTHI);
	msleep(30);	/* the firmware needs some समय to initialize */

	//ARM_ClearIrq(av7110);
	ARM_ResetMailBox(av7110);
	SAA7146_ISR_CLEAR(av7110->dev, MASK_19 | MASK_03);
	SAA7146_IER_ENABLE(av7110->dev, MASK_03);

	av7110->arm_errors = 0;
	av7110->arm_पढ़ोy = 1;
	वापस 0;
पूर्ण
MODULE_FIRMWARE("av7110/bootcode.bin");

/****************************************************************************
 * DEBI command polling
 ****************************************************************************/

पूर्णांक av7110_रुको_msgstate(काष्ठा av7110 *av7110, u16 flags)
अणु
	अचिन्हित दीर्घ start;
	u32 stat;
	पूर्णांक err;

	अगर (FW_VERSION(av7110->arm_app) <= 0x261c) अणु
		/* not supported by old firmware */
		msleep(50);
		वापस 0;
	पूर्ण

	/* new firmware */
	start = jअगरfies;
	क्रम (;;) अणु
		err = समय_after(jअगरfies, start + ARM_WAIT_FREE);
		अगर (mutex_lock_पूर्णांकerruptible(&av7110->dcomlock))
			वापस -ERESTARTSYS;
		stat = rdebi(av7110, DEBINOSWAP, MSGSTATE, 0, 2);
		mutex_unlock(&av7110->dcomlock);
		अगर ((stat & flags) == 0)
			अवरोध;
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout waiting for MSGSTATE %04x\n",
				__func__, stat & flags);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __av7110_send_fw_cmd(काष्ठा av7110 *av7110, u16* buf, पूर्णांक length)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ start;
	अक्षर *type = शून्य;
	u16 flags[2] = अणु0, 0पूर्ण;
	u32 stat;
	पूर्णांक err;

//	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (!av7110->arm_पढ़ोy) अणु
		dprपूर्णांकk(1, "arm not ready.\n");
		वापस -ENXIO;
	पूर्ण

	start = jअगरfies;
	जबतक (1) अणु
		err = समय_after(jअगरfies, start + ARM_WAIT_FREE);
		अगर (rdebi(av7110, DEBINOSWAP, COMMAND, 0, 2) == 0)
			अवरोध;
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: %s(): timeout waiting for COMMAND idle\n", __func__);
			av7110->arm_errors++;
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण

	अगर (FW_VERSION(av7110->arm_app) <= 0x261f)
		wdebi(av7110, DEBINOSWAP, COM_IF_LOCK, 0xffff, 2);

#अगर_अघोषित _NOHANDSHAKE
	start = jअगरfies;
	जबतक (1) अणु
		err = समय_after(jअगरfies, start + ARM_WAIT_SHAKE);
		अगर (rdebi(av7110, DEBINOSWAP, HANDSHAKE_REG, 0, 2) == 0)
			अवरोध;
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: %s(): timeout waiting for HANDSHAKE_REG\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण
#पूर्ण_अगर

	चयन ((buf[0] >> 8) & 0xff) अणु
	हाल COMTYPE_PIDFILTER:
	हाल COMTYPE_ENCODER:
	हाल COMTYPE_REC_PLAY:
	हाल COMTYPE_MPEGDECODER:
		type = "MSG";
		flags[0] = GPMQOver;
		flags[1] = GPMQFull;
		अवरोध;
	हाल COMTYPE_OSD:
		type = "OSD";
		flags[0] = OSDQOver;
		flags[1] = OSDQFull;
		अवरोध;
	हाल COMTYPE_MISC:
		अगर (FW_VERSION(av7110->arm_app) >= 0x261d) अणु
			type = "MSG";
			flags[0] = GPMQOver;
			flags[1] = GPMQBusy;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (type != शून्य) अणु
		/* non-immediate COMMAND type */
		start = jअगरfies;
		क्रम (;;) अणु
			err = समय_after(jअगरfies, start + ARM_WAIT_FREE);
			stat = rdebi(av7110, DEBINOSWAP, MSGSTATE, 0, 2);
			अगर (stat & flags[0]) अणु
				prपूर्णांकk(KERN_ERR "%s: %s QUEUE overflow\n",
					__func__, type);
				वापस -1;
			पूर्ण
			अगर ((stat & flags[1]) == 0)
				अवरोध;
			अगर (err) अणु
				prपूर्णांकk(KERN_ERR "%s: timeout waiting on busy %s QUEUE\n",
					__func__, type);
				av7110->arm_errors++;
				वापस -ETIMEDOUT;
			पूर्ण
			msleep(1);
		पूर्ण
	पूर्ण

	क्रम (i = 2; i < length; i++)
		wdebi(av7110, DEBINOSWAP, COMMAND + 2 * i, (u32) buf[i], 2);

	अगर (length)
		wdebi(av7110, DEBINOSWAP, COMMAND + 2, (u32) buf[1], 2);
	अन्यथा
		wdebi(av7110, DEBINOSWAP, COMMAND + 2, 0, 2);

	wdebi(av7110, DEBINOSWAP, COMMAND, (u32) buf[0], 2);

	अगर (FW_VERSION(av7110->arm_app) <= 0x261f)
		wdebi(av7110, DEBINOSWAP, COM_IF_LOCK, 0x0000, 2);

#अगर_घोषित COM_DEBUG
	start = jअगरfies;
	जबतक (1) अणु
		err = समय_after(jअगरfies, start + ARM_WAIT_FREE);
		अगर (rdebi(av7110, DEBINOSWAP, COMMAND, 0, 2) == 0)
			अवरोध;
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: %s(): timeout waiting for COMMAND %d to complete\n",
			       __func__, (buf[0] >> 8) & 0xff);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण

	stat = rdebi(av7110, DEBINOSWAP, MSGSTATE, 0, 2);
	अगर (stat & GPMQOver) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: %s(): GPMQOver\n", __func__);
		वापस -ENOSPC;
	पूर्ण
	अन्यथा अगर (stat & OSDQOver) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: %s(): OSDQOver\n", __func__);
		वापस -ENOSPC;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक av7110_send_fw_cmd(काष्ठा av7110 *av7110, u16* buf, पूर्णांक length)
अणु
	पूर्णांक ret;

//	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (!av7110->arm_पढ़ोy) अणु
		dprपूर्णांकk(1, "arm not ready.\n");
		वापस -1;
	पूर्ण
	अगर (mutex_lock_पूर्णांकerruptible(&av7110->dcomlock))
		वापस -ERESTARTSYS;

	ret = __av7110_send_fw_cmd(av7110, buf, length);
	mutex_unlock(&av7110->dcomlock);
	अगर (ret && ret!=-ERESTARTSYS)
		prपूर्णांकk(KERN_ERR "dvb-ttpci: %s(): av7110_send_fw_cmd error %d\n",
		       __func__, ret);
	वापस ret;
पूर्ण

पूर्णांक av7110_fw_cmd(काष्ठा av7110 *av7110, पूर्णांक type, पूर्णांक com, पूर्णांक num, ...)
अणु
	बहु_सूची args;
	u16 buf[MAX_XFER_SIZE];
	पूर्णांक i, ret;

//	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (2 + num > ARRAY_SIZE(buf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: %s len=%d is too big!\n",
		       KBUILD_MODNAME, __func__, num);
		वापस -EINVAL;
	पूर्ण

	buf[0] = ((type << 8) | com);
	buf[1] = num;

	अगर (num) अणु
		बहु_शुरू(args, num);
		क्रम (i = 0; i < num; i++)
			buf[i + 2] = बहु_तर्क(args, u32);
		बहु_पूर्ण(args);
	पूर्ण

	ret = av7110_send_fw_cmd(av7110, buf, num + 2);
	अगर (ret && ret != -ERESTARTSYS)
		prपूर्णांकk(KERN_ERR "dvb-ttpci: av7110_fw_cmd error %d\n", ret);
	वापस ret;
पूर्ण

#अगर 0
पूर्णांक av7110_send_ci_cmd(काष्ठा av7110 *av7110, u8 subcom, u8 *buf, u8 len)
अणु
	पूर्णांक i, ret;
	u16 cmd[18] = अणु ((COMTYPE_COMMON_IF << 8) + subcom),
		16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	dprपूर्णांकk(4, "%p\n", av7110);

	क्रम(i = 0; i < len && i < 32; i++)
	अणु
		अगर(i % 2 == 0)
			cmd[(i / 2) + 2] = (u16)(buf[i]) << 8;
		अन्यथा
			cmd[(i / 2) + 2] |= buf[i];
	पूर्ण

	ret = av7110_send_fw_cmd(av7110, cmd, 18);
	अगर (ret && ret != -ERESTARTSYS)
		prपूर्णांकk(KERN_ERR "dvb-ttpci: av7110_send_ci_cmd error %d\n", ret);
	वापस ret;
पूर्ण
#पूर्ण_अगर  /*  0  */

पूर्णांक av7110_fw_request(काष्ठा av7110 *av7110, u16 *request_buf,
		      पूर्णांक request_buf_len, u16 *reply_buf, पूर्णांक reply_buf_len)
अणु
	पूर्णांक err;
	s16 i;
	अचिन्हित दीर्घ start;
#अगर_घोषित COM_DEBUG
	u32 stat;
#पूर्ण_अगर

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (!av7110->arm_पढ़ोy) अणु
		dprपूर्णांकk(1, "arm not ready.\n");
		वापस -1;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&av7110->dcomlock))
		वापस -ERESTARTSYS;

	अगर ((err = __av7110_send_fw_cmd(av7110, request_buf, request_buf_len)) < 0) अणु
		mutex_unlock(&av7110->dcomlock);
		prपूर्णांकk(KERN_ERR "dvb-ttpci: av7110_fw_request error %d\n", err);
		वापस err;
	पूर्ण

	start = jअगरfies;
	जबतक (1) अणु
		err = समय_after(jअगरfies, start + ARM_WAIT_FREE);
		अगर (rdebi(av7110, DEBINOSWAP, COMMAND, 0, 2) == 0)
			अवरोध;
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout waiting for COMMAND to complete\n", __func__);
			mutex_unlock(&av7110->dcomlock);
			वापस -ETIMEDOUT;
		पूर्ण
#अगर_घोषित _NOHANDSHAKE
		msleep(1);
#पूर्ण_अगर
	पूर्ण

#अगर_अघोषित _NOHANDSHAKE
	start = jअगरfies;
	जबतक (1) अणु
		err = समय_after(jअगरfies, start + ARM_WAIT_SHAKE);
		अगर (rdebi(av7110, DEBINOSWAP, HANDSHAKE_REG, 0, 2) == 0)
			अवरोध;
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: timeout waiting for HANDSHAKE_REG\n", __func__);
			mutex_unlock(&av7110->dcomlock);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित COM_DEBUG
	stat = rdebi(av7110, DEBINOSWAP, MSGSTATE, 0, 2);
	अगर (stat & GPMQOver) अणु
		prपूर्णांकk(KERN_ERR "%s: GPMQOver\n", __func__);
		mutex_unlock(&av7110->dcomlock);
		वापस -1;
	पूर्ण
	अन्यथा अगर (stat & OSDQOver) अणु
		prपूर्णांकk(KERN_ERR "%s: OSDQOver\n", __func__);
		mutex_unlock(&av7110->dcomlock);
		वापस -1;
	पूर्ण
#पूर्ण_अगर

	क्रम (i = 0; i < reply_buf_len; i++)
		reply_buf[i] = rdebi(av7110, DEBINOSWAP, COM_BUFF + 2 * i, 0, 2);

	mutex_unlock(&av7110->dcomlock);
	वापस 0;
पूर्ण

अटल पूर्णांक av7110_fw_query(काष्ठा av7110 *av7110, u16 tag, u16* buf, s16 length)
अणु
	पूर्णांक ret;
	ret = av7110_fw_request(av7110, &tag, 0, buf, length);
	अगर (ret)
		prपूर्णांकk(KERN_ERR "dvb-ttpci: av7110_fw_query error %d\n", ret);
	वापस ret;
पूर्ण


/****************************************************************************
 * Firmware commands
 ****************************************************************************/

/* get version of the firmware ROM, RTSL, video ucode and ARM application  */
पूर्णांक av7110_firmversion(काष्ठा av7110 *av7110)
अणु
	u16 buf[20];
	u16 tag = ((COMTYPE_REQUEST << 8) + ReqVersion);

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (av7110_fw_query(av7110, tag, buf, 16)) अणु
		prपूर्णांकk("dvb-ttpci: failed to boot firmware @ card %d\n",
		       av7110->dvb_adapter.num);
		वापस -EIO;
	पूर्ण

	av7110->arm_fw = (buf[0] << 16) + buf[1];
	av7110->arm_rtsl = (buf[2] << 16) + buf[3];
	av7110->arm_vid = (buf[4] << 16) + buf[5];
	av7110->arm_app = (buf[6] << 16) + buf[7];
	av7110->avtype = (buf[8] << 16) + buf[9];

	prपूर्णांकk("dvb-ttpci: info @ card %d: firm %08x, rtsl %08x, vid %08x, app %08x\n",
	       av7110->dvb_adapter.num, av7110->arm_fw,
	       av7110->arm_rtsl, av7110->arm_vid, av7110->arm_app);

	/* prपूर्णांक firmware capabilities */
	अगर (FW_CI_LL_SUPPORT(av7110->arm_app))
		prपूर्णांकk("dvb-ttpci: firmware @ card %d supports CI link layer interface\n",
		       av7110->dvb_adapter.num);
	अन्यथा
		prपूर्णांकk("dvb-ttpci: no firmware support for CI link layer interface @ card %d\n",
		       av7110->dvb_adapter.num);

	वापस 0;
पूर्ण


पूर्णांक av7110_diseqc_send(काष्ठा av7110 *av7110, पूर्णांक len, u8 *msg, अचिन्हित दीर्घ burst)
अणु
	पूर्णांक i, ret;
	u16 buf[18] = अणु ((COMTYPE_AUDIODAC << 8) + SendDiSEqC),
			16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (len > 10)
		len = 10;

	buf[1] = len + 2;
	buf[2] = len;

	अगर (burst != -1)
		buf[3] = burst ? 0x01 : 0x00;
	अन्यथा
		buf[3] = 0xffff;

	क्रम (i = 0; i < len; i++)
		buf[i + 4] = msg[i];

	ret = av7110_send_fw_cmd(av7110, buf, 18);
	अगर (ret && ret!=-ERESTARTSYS)
		prपूर्णांकk(KERN_ERR "dvb-ttpci: av7110_diseqc_send error %d\n", ret);
	वापस ret;
पूर्ण


#अगर_घोषित CONFIG_DVB_AV7110_OSD

अटल अंतरभूत पूर्णांक SetColorBlend(काष्ठा av7110 *av7110, u8 winकरोwnr)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, SetCBlend, 1, winकरोwnr);
पूर्ण

अटल अंतरभूत पूर्णांक SetBlend_(काष्ठा av7110 *av7110, u8 winकरोwnr,
		     क्रमागत av7110_osd_palette_type colordepth, u16 index, u8 blending)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, SetBlend, 4,
			     winकरोwnr, colordepth, index, blending);
पूर्ण

अटल अंतरभूत पूर्णांक SetColor_(काष्ठा av7110 *av7110, u8 winकरोwnr,
		     क्रमागत av7110_osd_palette_type colordepth, u16 index, u16 colorhi, u16 colorlo)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, SetColor, 5,
			     winकरोwnr, colordepth, index, colorhi, colorlo);
पूर्ण

अटल अंतरभूत पूर्णांक SetFont(काष्ठा av7110 *av7110, u8 winकरोwnr, u8 fontsize,
			  u16 colorfg, u16 colorbg)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, Set_Font, 4,
			     winकरोwnr, fontsize, colorfg, colorbg);
पूर्ण

अटल पूर्णांक FlushText(काष्ठा av7110 *av7110)
अणु
	अचिन्हित दीर्घ start;
	पूर्णांक err;

	अगर (mutex_lock_पूर्णांकerruptible(&av7110->dcomlock))
		वापस -ERESTARTSYS;
	start = jअगरfies;
	जबतक (1) अणु
		err = समय_after(jअगरfies, start + ARM_WAIT_OSD);
		अगर (rdebi(av7110, DEBINOSWAP, BUFF1_BASE, 0, 2) == 0)
			अवरोध;
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: %s(): timeout waiting for BUFF1_BASE == 0\n",
			       __func__);
			mutex_unlock(&av7110->dcomlock);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण
	mutex_unlock(&av7110->dcomlock);
	वापस 0;
पूर्ण

अटल पूर्णांक WriteText(काष्ठा av7110 *av7110, u8 win, u16 x, u16 y, अक्षर *buf)
अणु
	पूर्णांक i, ret;
	अचिन्हित दीर्घ start;
	पूर्णांक length = म_माप(buf) + 1;
	u16 cbuf[5] = अणु (COMTYPE_OSD << 8) + DText, 3, win, x, y पूर्ण;

	अगर (mutex_lock_पूर्णांकerruptible(&av7110->dcomlock))
		वापस -ERESTARTSYS;

	start = jअगरfies;
	जबतक (1) अणु
		ret = समय_after(jअगरfies, start + ARM_WAIT_OSD);
		अगर (rdebi(av7110, DEBINOSWAP, BUFF1_BASE, 0, 2) == 0)
			अवरोध;
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: %s: timeout waiting for BUFF1_BASE == 0\n",
			       __func__);
			mutex_unlock(&av7110->dcomlock);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण
#अगर_अघोषित _NOHANDSHAKE
	start = jअगरfies;
	जबतक (1) अणु
		ret = समय_after(jअगरfies, start + ARM_WAIT_SHAKE);
		अगर (rdebi(av7110, DEBINOSWAP, HANDSHAKE_REG, 0, 2) == 0)
			अवरोध;
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: %s: timeout waiting for HANDSHAKE_REG\n",
			       __func__);
			mutex_unlock(&av7110->dcomlock);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण
#पूर्ण_अगर
	क्रम (i = 0; i < length / 2; i++)
		wdebi(av7110, DEBINOSWAP, BUFF1_BASE + i * 2,
		      swab16(*(u16 *)(buf + 2 * i)), 2);
	अगर (length & 1)
		wdebi(av7110, DEBINOSWAP, BUFF1_BASE + i * 2, 0, 2);
	ret = __av7110_send_fw_cmd(av7110, cbuf, 5);
	mutex_unlock(&av7110->dcomlock);
	अगर (ret && ret!=-ERESTARTSYS)
		prपूर्णांकk(KERN_ERR "dvb-ttpci: WriteText error %d\n", ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक DrawLine(काष्ठा av7110 *av7110, u8 winकरोwnr,
			   u16 x, u16 y, u16 dx, u16 dy, u16 color)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, DLine, 6,
			     winकरोwnr, x, y, dx, dy, color);
पूर्ण

अटल अंतरभूत पूर्णांक DrawBlock(काष्ठा av7110 *av7110, u8 winकरोwnr,
			    u16 x, u16 y, u16 dx, u16 dy, u16 color)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, DBox, 6,
			     winकरोwnr, x, y, dx, dy, color);
पूर्ण

अटल अंतरभूत पूर्णांक HideWinकरोw(काष्ठा av7110 *av7110, u8 winकरोwnr)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, WHide, 1, winकरोwnr);
पूर्ण

अटल अंतरभूत पूर्णांक MoveWinकरोwRel(काष्ठा av7110 *av7110, u8 winकरोwnr, u16 x, u16 y)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, WMoveD, 3, winकरोwnr, x, y);
पूर्ण

अटल अंतरभूत पूर्णांक MoveWinकरोwAbs(काष्ठा av7110 *av7110, u8 winकरोwnr, u16 x, u16 y)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, WMoveA, 3, winकरोwnr, x, y);
पूर्ण

अटल अंतरभूत पूर्णांक DestroyOSDWinकरोw(काष्ठा av7110 *av7110, u8 winकरोwnr)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, WDestroy, 1, winकरोwnr);
पूर्ण

अटल अंतरभूत पूर्णांक CreateOSDWinकरोw(काष्ठा av7110 *av7110, u8 winकरोwnr,
				  osd_raw_winकरोw_t disptype,
				  u16 width, u16 height)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, WCreate, 4,
			     winकरोwnr, disptype, width, height);
पूर्ण


अटल क्रमागत av7110_osd_palette_type bpp2pal[8] = अणु
	Pal1Bit, Pal2Bit, 0, Pal4Bit, 0, 0, 0, Pal8Bit
पूर्ण;
अटल osd_raw_winकरोw_t bpp2bit[8] = अणु
	OSD_BITMAP1, OSD_BITMAP2, 0, OSD_BITMAP4, 0, 0, 0, OSD_BITMAP8
पूर्ण;

अटल अंतरभूत पूर्णांक WaitUntilBmpLoaded(काष्ठा av7110 *av7110)
अणु
	पूर्णांक ret = रुको_event_समयout(av7110->bmpq,
				av7110->bmp_state != BMP_LOADING, 10*HZ);
	अगर (ret == 0) अणु
		prपूर्णांकk("dvb-ttpci: warning: timeout waiting in LoadBitmap: %d, %d\n",
		       ret, av7110->bmp_state);
		av7110->bmp_state = BMP_NONE;
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक LoadBiपंचांगap(काष्ठा av7110 *av7110,
			     u16 dx, u16 dy, पूर्णांक inc, u8 __user * data)
अणु
	u16 क्रमmat;
	पूर्णांक bpp;
	पूर्णांक i;
	पूर्णांक d, delta;
	u8 c;
	पूर्णांक ret;

	dprपूर्णांकk(4, "%p\n", av7110);

	क्रमmat = bpp2bit[av7110->osdbpp[av7110->osdwin]];

	av7110->bmp_state = BMP_LOADING;
	अगर	(क्रमmat == OSD_BITMAP8) अणु
		bpp=8; delta = 1;
	पूर्ण अन्यथा अगर (क्रमmat == OSD_BITMAP4) अणु
		bpp=4; delta = 2;
	पूर्ण अन्यथा अगर (क्रमmat == OSD_BITMAP2) अणु
		bpp=2; delta = 4;
	पूर्ण अन्यथा अगर (क्रमmat == OSD_BITMAP1) अणु
		bpp=1; delta = 8;
	पूर्ण अन्यथा अणु
		av7110->bmp_state = BMP_NONE;
		वापस -EINVAL;
	पूर्ण
	av7110->bmplen = ((dx * dy * bpp + 7) & ~7) / 8;
	av7110->bmpp = 0;
	अगर (av7110->bmplen > 32768) अणु
		av7110->bmp_state = BMP_NONE;
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < dy; i++) अणु
		अगर (copy_from_user(av7110->bmpbuf + 1024 + i * dx, data + i * inc, dx)) अणु
			av7110->bmp_state = BMP_NONE;
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (क्रमmat != OSD_BITMAP8) अणु
		क्रम (i = 0; i < dx * dy / delta; i++) अणु
			c = ((u8 *)av7110->bmpbuf)[1024 + i * delta + delta - 1];
			क्रम (d = delta - 2; d >= 0; d--) अणु
				c |= (((u8 *)av7110->bmpbuf)[1024 + i * delta + d]
				      << ((delta - d - 1) * bpp));
				((u8 *)av7110->bmpbuf)[1024 + i] = c;
			पूर्ण
		पूर्ण
	पूर्ण
	av7110->bmplen += 1024;
	dprपूर्णांकk(4, "av7110_fw_cmd: LoadBmp size %d\n", av7110->bmplen);
	ret = av7110_fw_cmd(av7110, COMTYPE_OSD, LoadBmp, 3, क्रमmat, dx, dy);
	अगर (!ret)
		ret = WaitUntilBmpLoaded(av7110);
	वापस ret;
पूर्ण

अटल पूर्णांक BlitBiपंचांगap(काष्ठा av7110 *av7110, u16 x, u16 y)
अणु
	dprपूर्णांकk(4, "%p\n", av7110);

	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, BlitBmp, 4, av7110->osdwin, x, y, 0);
पूर्ण

अटल अंतरभूत पूर्णांक ReleaseBiपंचांगap(काष्ठा av7110 *av7110)
अणु
	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (av7110->bmp_state != BMP_LOADED && FW_VERSION(av7110->arm_app) < 0x261e)
		वापस -1;
	अगर (av7110->bmp_state == BMP_LOADING)
		dprपूर्णांकk(1,"ReleaseBitmap called while BMP_LOADING\n");
	av7110->bmp_state = BMP_NONE;
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, ReleaseBmp, 0);
पूर्ण

अटल u32 RGB2YUV(u16 R, u16 G, u16 B)
अणु
	u16 y, u, v;
	u16 Y, Cr, Cb;

	y = R * 77 + G * 150 + B * 29;	/* Luma=0.299R+0.587G+0.114B 0..65535 */
	u = 2048 + B * 8 -(y >> 5);	/* Cr 0..4095 */
	v = 2048 + R * 8 -(y >> 5);	/* Cb 0..4095 */

	Y = y / 256;
	Cb = u / 16;
	Cr = v / 16;

	वापस Cr | (Cb << 16) | (Y << 8);
पूर्ण

अटल पूर्णांक OSDSetColor(काष्ठा av7110 *av7110, u8 color, u8 r, u8 g, u8 b, u8 blend)
अणु
	पूर्णांक ret;

	u16 ch, cl;
	u32 yuv;

	yuv = blend ? RGB2YUV(r,g,b) : 0;
	cl = (yuv & 0xffff);
	ch = ((yuv >> 16) & 0xffff);
	ret = SetColor_(av7110, av7110->osdwin, bpp2pal[av7110->osdbpp[av7110->osdwin]],
			color, ch, cl);
	अगर (!ret)
		ret = SetBlend_(av7110, av7110->osdwin, bpp2pal[av7110->osdbpp[av7110->osdwin]],
				color, ((blend >> 4) & 0x0f));
	वापस ret;
पूर्ण

अटल पूर्णांक OSDSetPalette(काष्ठा av7110 *av7110, u32 __user * colors, u8 first, u8 last)
अणु
	पूर्णांक i;
	पूर्णांक length = last - first + 1;

	अगर (length * 4 > DATA_BUFF3_SIZE)
		वापस -EINVAL;

	क्रम (i = 0; i < length; i++) अणु
		u32 color, blend, yuv;

		अगर (get_user(color, colors + i))
			वापस -EFAULT;
		blend = (color & 0xF0000000) >> 4;
		yuv = blend ? RGB2YUV(color & 0xFF, (color >> 8) & 0xFF,
				     (color >> 16) & 0xFF) | blend : 0;
		yuv = ((yuv & 0xFFFF0000) >> 16) | ((yuv & 0x0000FFFF) << 16);
		wdebi(av7110, DEBINOSWAP, DATA_BUFF3_BASE + i * 4, yuv, 4);
	पूर्ण
	वापस av7110_fw_cmd(av7110, COMTYPE_OSD, Set_Palette, 4,
			    av7110->osdwin,
			    bpp2pal[av7110->osdbpp[av7110->osdwin]],
			    first, last);
पूर्ण

अटल पूर्णांक OSDSetBlock(काष्ठा av7110 *av7110, पूर्णांक x0, पूर्णांक y0,
		       पूर्णांक x1, पूर्णांक y1, पूर्णांक inc, u8 __user * data)
अणु
	uपूर्णांक w, h, bpp, bpl, size, lpb, bnum, brest;
	पूर्णांक i;
	पूर्णांक rc,release_rc;

	w = x1 - x0 + 1;
	h = y1 - y0 + 1;
	अगर (inc <= 0)
		inc = w;
	अगर (w <= 0 || w > 720 || h <= 0 || h > 576)
		वापस -EINVAL;
	bpp = av7110->osdbpp[av7110->osdwin] + 1;
	bpl = ((w * bpp + 7) & ~7) / 8;
	size = h * bpl;
	lpb = (32 * 1024) / bpl;
	bnum = size / (lpb * bpl);
	brest = size - bnum * lpb * bpl;

	अगर (av7110->bmp_state == BMP_LOADING) अणु
		/* possible अगर syscall is repeated by -ERESTARTSYS and अगर firmware cannot पात */
		BUG_ON (FW_VERSION(av7110->arm_app) >= 0x261e);
		rc = WaitUntilBmpLoaded(av7110);
		अगर (rc)
			वापस rc;
		/* just जारी. This should work क्रम all fw versions
		 * अगर bnum==1 && !brest && LoadBiपंचांगap was successful
		 */
	पूर्ण

	rc = 0;
	क्रम (i = 0; i < bnum; i++) अणु
		rc = LoadBiपंचांगap(av7110, w, lpb, inc, data);
		अगर (rc)
			अवरोध;
		rc = BlitBiपंचांगap(av7110, x0, y0 + i * lpb);
		अगर (rc)
			अवरोध;
		data += lpb * inc;
	पूर्ण
	अगर (!rc && brest) अणु
		rc = LoadBiपंचांगap(av7110, w, brest / bpl, inc, data);
		अगर (!rc)
			rc = BlitBiपंचांगap(av7110, x0, y0 + bnum * lpb);
	पूर्ण
	release_rc = ReleaseBiपंचांगap(av7110);
	अगर (!rc)
		rc = release_rc;
	अगर (rc)
		dprपूर्णांकk(1,"returns %d\n",rc);
	वापस rc;
पूर्ण

पूर्णांक av7110_osd_cmd(काष्ठा av7110 *av7110, osd_cmd_t *dc)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&av7110->osd_mutex))
		वापस -ERESTARTSYS;

	चयन (dc->cmd) अणु
	हाल OSD_Close:
		ret = DestroyOSDWinकरोw(av7110, av7110->osdwin);
		अवरोध;
	हाल OSD_Open:
		av7110->osdbpp[av7110->osdwin] = (dc->color - 1) & 7;
		ret = CreateOSDWinकरोw(av7110, av7110->osdwin,
				bpp2bit[av7110->osdbpp[av7110->osdwin]],
				dc->x1 - dc->x0 + 1, dc->y1 - dc->y0 + 1);
		अगर (ret)
			अवरोध;
		अगर (!dc->data) अणु
			ret = MoveWinकरोwAbs(av7110, av7110->osdwin, dc->x0, dc->y0);
			अगर (ret)
				अवरोध;
			ret = SetColorBlend(av7110, av7110->osdwin);
		पूर्ण
		अवरोध;
	हाल OSD_Show:
		ret = MoveWinकरोwRel(av7110, av7110->osdwin, 0, 0);
		अवरोध;
	हाल OSD_Hide:
		ret = HideWinकरोw(av7110, av7110->osdwin);
		अवरोध;
	हाल OSD_Clear:
		ret = DrawBlock(av7110, av7110->osdwin, 0, 0, 720, 576, 0);
		अवरोध;
	हाल OSD_Fill:
		ret = DrawBlock(av7110, av7110->osdwin, 0, 0, 720, 576, dc->color);
		अवरोध;
	हाल OSD_SetColor:
		ret = OSDSetColor(av7110, dc->color, dc->x0, dc->y0, dc->x1, dc->y1);
		अवरोध;
	हाल OSD_SetPalette:
		अगर (FW_VERSION(av7110->arm_app) >= 0x2618)
			ret = OSDSetPalette(av7110, dc->data, dc->color, dc->x0);
		अन्यथा अणु
			पूर्णांक i, len = dc->x0-dc->color+1;
			u8 __user *colors = (u8 __user *)dc->data;
			u8 r, g = 0, b = 0, blend = 0;
			ret = 0;
			क्रम (i = 0; i<len; i++) अणु
				अगर (get_user(r, colors + i * 4) ||
				    get_user(g, colors + i * 4 + 1) ||
				    get_user(b, colors + i * 4 + 2) ||
				    get_user(blend, colors + i * 4 + 3)) अणु
					ret = -EFAULT;
					अवरोध;
				    पूर्ण
				ret = OSDSetColor(av7110, dc->color + i, r, g, b, blend);
				अगर (ret)
					अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल OSD_SetPixel:
		ret = DrawLine(av7110, av7110->osdwin,
			 dc->x0, dc->y0, 0, 0, dc->color);
		अवरोध;
	हाल OSD_SetRow:
		dc->y1 = dc->y0;
		fallthrough;
	हाल OSD_SetBlock:
		ret = OSDSetBlock(av7110, dc->x0, dc->y0, dc->x1, dc->y1, dc->color, dc->data);
		अवरोध;
	हाल OSD_FillRow:
		ret = DrawBlock(av7110, av7110->osdwin, dc->x0, dc->y0,
			  dc->x1-dc->x0+1, dc->y1, dc->color);
		अवरोध;
	हाल OSD_FillBlock:
		ret = DrawBlock(av7110, av7110->osdwin, dc->x0, dc->y0,
			  dc->x1 - dc->x0 + 1, dc->y1 - dc->y0 + 1, dc->color);
		अवरोध;
	हाल OSD_Line:
		ret = DrawLine(av7110, av7110->osdwin,
			 dc->x0, dc->y0, dc->x1 - dc->x0, dc->y1 - dc->y0, dc->color);
		अवरोध;
	हाल OSD_Text:
	अणु
		अक्षर textbuf[240];

		अगर (म_नकलन_from_user(textbuf, dc->data, 240) < 0) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		textbuf[239] = 0;
		अगर (dc->x1 > 3)
			dc->x1 = 3;
		ret = SetFont(av7110, av7110->osdwin, dc->x1,
			(u16) (dc->color & 0xffff), (u16) (dc->color >> 16));
		अगर (!ret)
			ret = FlushText(av7110);
		अगर (!ret)
			ret = WriteText(av7110, av7110->osdwin, dc->x0, dc->y0, textbuf);
		अवरोध;
	पूर्ण
	हाल OSD_SetWinकरोw:
		अगर (dc->x0 < 1 || dc->x0 > 7)
			ret = -EINVAL;
		अन्यथा अणु
			av7110->osdwin = dc->x0;
			ret = 0;
		पूर्ण
		अवरोध;
	हाल OSD_MoveWinकरोw:
		ret = MoveWinकरोwAbs(av7110, av7110->osdwin, dc->x0, dc->y0);
		अगर (!ret)
			ret = SetColorBlend(av7110, av7110->osdwin);
		अवरोध;
	हाल OSD_OpenRaw:
		अगर (dc->color < OSD_BITMAP1 || dc->color > OSD_CURSOR) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (dc->color >= OSD_BITMAP1 && dc->color <= OSD_BITMAP8HR)
			av7110->osdbpp[av7110->osdwin] = (1 << (dc->color & 3)) - 1;
		अन्यथा
			av7110->osdbpp[av7110->osdwin] = 0;
		ret = CreateOSDWinकरोw(av7110, av7110->osdwin, (osd_raw_winकरोw_t)dc->color,
				dc->x1 - dc->x0 + 1, dc->y1 - dc->y0 + 1);
		अगर (ret)
			अवरोध;
		अगर (!dc->data) अणु
			ret = MoveWinकरोwAbs(av7110, av7110->osdwin, dc->x0, dc->y0);
			अगर (!ret)
				ret = SetColorBlend(av7110, av7110->osdwin);
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&av7110->osd_mutex);
	अगर (ret==-ERESTARTSYS)
		dprपूर्णांकk(1, "av7110_osd_cmd(%d) returns with -ERESTARTSYS\n",dc->cmd);
	अन्यथा अगर (ret)
		dprपूर्णांकk(1, "av7110_osd_cmd(%d) returns with %d\n",dc->cmd,ret);

	वापस ret;
पूर्ण

पूर्णांक av7110_osd_capability(काष्ठा av7110 *av7110, osd_cap_t *cap)
अणु
	चयन (cap->cmd) अणु
	हाल OSD_CAP_MEMSIZE:
		अगर (FW_4M_SDRAM(av7110->arm_app))
			cap->val = 1000000;
		अन्यथा
			cap->val = 92000;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_AV7110_OSD */
