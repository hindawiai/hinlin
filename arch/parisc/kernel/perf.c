<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Parisc perक्रमmance counters
 *  Copyright (C) 2001 Ranकरोlph Chung <tausq@debian.org>
 *
 *  This code is derived, with permission, from HP/UX sources.
 */

/*
 *  Edited comment from original sources:
 *
 *  This driver programs the PCX-U/PCX-W perक्रमmance counters
 *  on the PA-RISC 2.0 chips.  The driver keeps all images now
 *  पूर्णांकernally to the kernel to hopefully eliminate the possibility
 *  of a bad image halting the CPU.  Also, there are dअगरferent
 *  images क्रम the PCX-W and later chips vs the PCX-U chips.
 *
 *  Only 1 process is allowed to access the driver at any समय,
 *  so the only protection that is needed is at खोलो and बंद.
 *  A variable "perf_enabled" is used to hold the state of the
 *  driver.  The spinlock "perf_lock" is used to protect the
 *  modअगरication of the state during खोलो/बंद operations so
 *  multiple processes करोn't get पूर्णांकo the driver simultaneously.
 *
 *  This driver accesses the processor directly vs going through
 *  the PDC INTRIGUE calls.  This is करोne to eliminate bugs पूर्णांकroduced
 *  in various PDC revisions.  The code is much more मुख्यtainable
 *  and reliable this way vs having to debug on every version of PDC
 *  on every box.
 */

#समावेश <linux/capability.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/perf.h>
#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/runway.h>
#समावेश <यंत्र/पन.स>		/* क्रम __raw_पढ़ो() */

#समावेश "perf_images.h"

#घोषणा MAX_RDR_WORDS	24
#घोषणा PERF_VERSION	2	/* derived from hpux's PI v2 पूर्णांकerface */

/* definition of RDR regs */
काष्ठा rdr_tbl_ent अणु
	uपूर्णांक16_t	width;
	uपूर्णांक8_t		num_words;
	uपूर्णांक8_t		ग_लिखो_control;
पूर्ण;

अटल पूर्णांक perf_processor_पूर्णांकerface __पढ़ो_mostly = UNKNOWN_INTF;
अटल पूर्णांक perf_enabled __पढ़ो_mostly;
अटल DEFINE_SPINLOCK(perf_lock);
काष्ठा parisc_device *cpu_device __पढ़ो_mostly;

/* RDRs to ग_लिखो क्रम PCX-W */
अटल स्थिर पूर्णांक perf_rdrs_W[] =
	अणु 0, 1, 4, 5, 6, 15, 16, 17, 18, 20, 21, 22, 23, 24, 25, -1 पूर्ण;

/* RDRs to ग_लिखो क्रम PCX-U */
अटल स्थिर पूर्णांक perf_rdrs_U[] =
	अणु 0, 1, 4, 5, 6, 7, 16, 17, 18, 20, 21, 22, 23, 24, 25, -1 पूर्ण;

/* RDR रेजिस्टर descriptions क्रम PCX-W */
अटल स्थिर काष्ठा rdr_tbl_ent perf_rdr_tbl_W[] = अणु
	अणु 19,	1,	8 पूर्ण,   /* RDR 0 */
	अणु 16,	1,	16 पूर्ण,  /* RDR 1 */
	अणु 72,	2,	0 पूर्ण,   /* RDR 2 */
	अणु 81,	2,	0 पूर्ण,   /* RDR 3 */
	अणु 328,	6,	0 पूर्ण,   /* RDR 4 */
	अणु 160,	3,	0 पूर्ण,   /* RDR 5 */
	अणु 336,	6,	0 पूर्ण,   /* RDR 6 */
	अणु 164,	3,	0 पूर्ण,   /* RDR 7 */
	अणु 0,	0,	0 पूर्ण,   /* RDR 8 */
	अणु 35,	1,	0 पूर्ण,   /* RDR 9 */
	अणु 6,	1,	0 पूर्ण,   /* RDR 10 */
	अणु 18,	1,	0 पूर्ण,   /* RDR 11 */
	अणु 13,	1,	0 पूर्ण,   /* RDR 12 */
	अणु 8,	1,	0 पूर्ण,   /* RDR 13 */
	अणु 8,	1,	0 पूर्ण,   /* RDR 14 */
	अणु 8,	1,	0 पूर्ण,   /* RDR 15 */
	अणु 1530,	24,	0 पूर्ण,   /* RDR 16 */
	अणु 16,	1,	0 पूर्ण,   /* RDR 17 */
	अणु 4,	1,	0 पूर्ण,   /* RDR 18 */
	अणु 0,	0,	0 पूर्ण,   /* RDR 19 */
	अणु 152,	3,	24 पूर्ण,  /* RDR 20 */
	अणु 152,	3,	24 पूर्ण,  /* RDR 21 */
	अणु 233,	4,	48 पूर्ण,  /* RDR 22 */
	अणु 233,	4,	48 पूर्ण,  /* RDR 23 */
	अणु 71,	2,	0 पूर्ण,   /* RDR 24 */
	अणु 71,	2,	0 पूर्ण,   /* RDR 25 */
	अणु 11,	1,	0 पूर्ण,   /* RDR 26 */
	अणु 18,	1,	0 पूर्ण,   /* RDR 27 */
	अणु 128,	2,	0 पूर्ण,   /* RDR 28 */
	अणु 0,	0,	0 पूर्ण,   /* RDR 29 */
	अणु 16,	1,	0 पूर्ण,   /* RDR 30 */
	अणु 16,	1,	0 पूर्ण,   /* RDR 31 */
पूर्ण;

/* RDR रेजिस्टर descriptions क्रम PCX-U */
अटल स्थिर काष्ठा rdr_tbl_ent perf_rdr_tbl_U[] = अणु
	अणु 19,	1,	8 पूर्ण,              /* RDR 0 */
	अणु 32,	1,	16 पूर्ण,             /* RDR 1 */
	अणु 20,	1,	0 पूर्ण,              /* RDR 2 */
	अणु 0,	0,	0 पूर्ण,              /* RDR 3 */
	अणु 344,	6,	0 पूर्ण,              /* RDR 4 */
	अणु 176,	3,	0 पूर्ण,              /* RDR 5 */
	अणु 336,	6,	0 पूर्ण,              /* RDR 6 */
	अणु 0,	0,	0 पूर्ण,              /* RDR 7 */
	अणु 0,	0,	0 पूर्ण,              /* RDR 8 */
	अणु 0,	0,	0 पूर्ण,              /* RDR 9 */
	अणु 28,	1,	0 पूर्ण,              /* RDR 10 */
	अणु 33,	1,	0 पूर्ण,              /* RDR 11 */
	अणु 0,	0,	0 पूर्ण,              /* RDR 12 */
	अणु 230,	4,	0 पूर्ण,              /* RDR 13 */
	अणु 32,	1,	0 पूर्ण,              /* RDR 14 */
	अणु 128,	2,	0 पूर्ण,              /* RDR 15 */
	अणु 1494,	24,	0 पूर्ण,              /* RDR 16 */
	अणु 18,	1,	0 पूर्ण,              /* RDR 17 */
	अणु 4,	1,	0 पूर्ण,              /* RDR 18 */
	अणु 0,	0,	0 पूर्ण,              /* RDR 19 */
	अणु 158,	3,	24 पूर्ण,             /* RDR 20 */
	अणु 158,	3,	24 पूर्ण,             /* RDR 21 */
	अणु 194,	4,	48 पूर्ण,             /* RDR 22 */
	अणु 194,	4,	48 पूर्ण,             /* RDR 23 */
	अणु 71,	2,	0 पूर्ण,              /* RDR 24 */
	अणु 71,	2,	0 पूर्ण,              /* RDR 25 */
	अणु 28,	1,	0 पूर्ण,              /* RDR 26 */
	अणु 33,	1,	0 पूर्ण,              /* RDR 27 */
	अणु 88,	2,	0 पूर्ण,              /* RDR 28 */
	अणु 32,	1,	0 पूर्ण,              /* RDR 29 */
	अणु 24,	1,	0 पूर्ण,              /* RDR 30 */
	अणु 16,	1,	0 पूर्ण,              /* RDR 31 */
पूर्ण;

/*
 * A non-zero ग_लिखो_control in the above tables is a byte offset पूर्णांकo
 * this array.
 */
अटल स्थिर uपूर्णांक64_t perf_biपंचांगasks[] = अणु
	0x0000000000000000ul,     /* first dbl word must be zero */
	0xfdffe00000000000ul,     /* RDR0 biपंचांगask */
	0x003f000000000000ul,     /* RDR1 biपंचांगask */
	0x00fffffffffffffful,     /* RDR20-RDR21 biपंचांगask (152 bits) */
	0xfffffffffffffffful,
	0xfffffffc00000000ul,
	0xfffffffffffffffful,     /* RDR22-RDR23 biपंचांगask (233 bits) */
	0xfffffffffffffffful,
	0xfffffffffffffffcul,
	0xff00000000000000ul
पूर्ण;

/*
 * Write control biपंचांगasks क्रम Pa-8700 processor given
 * some things have changed slightly.
 */
अटल स्थिर uपूर्णांक64_t perf_biपंचांगasks_piranha[] = अणु
	0x0000000000000000ul,     /* first dbl word must be zero */
	0xfdffe00000000000ul,     /* RDR0 biपंचांगask */
	0x003f000000000000ul,     /* RDR1 biपंचांगask */
	0x00fffffffffffffful,     /* RDR20-RDR21 biपंचांगask (158 bits) */
	0xfffffffffffffffful,
	0xfffffffc00000000ul,
	0xfffffffffffffffful,     /* RDR22-RDR23 biपंचांगask (210 bits) */
	0xfffffffffffffffful,
	0xfffffffffffffffful,
	0xfffc000000000000ul
पूर्ण;

अटल स्थिर uपूर्णांक64_t *biपंचांगask_array;   /* array of biपंचांगasks to use */

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/
अटल पूर्णांक perf_config(uपूर्णांक32_t *image_ptr);
अटल पूर्णांक perf_release(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक perf_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार perf_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार cnt, loff_t *ppos);
अटल sमाप_प्रकार perf_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
	माप_प्रकार count, loff_t *ppos);
अटल दीर्घ perf_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल व्योम perf_start_counters(व्योम);
अटल पूर्णांक perf_stop_counters(uपूर्णांक32_t *raddr);
अटल स्थिर काष्ठा rdr_tbl_ent * perf_rdr_get_entry(uपूर्णांक32_t rdr_num);
अटल पूर्णांक perf_rdr_पढ़ो_ubuf(uपूर्णांक32_t	rdr_num, uपूर्णांक64_t *buffer);
अटल पूर्णांक perf_rdr_clear(uपूर्णांक32_t rdr_num);
अटल पूर्णांक perf_ग_लिखो_image(uपूर्णांक64_t *memaddr);
अटल व्योम perf_rdr_ग_लिखो(uपूर्णांक32_t rdr_num, uपूर्णांक64_t *buffer);

/* External Assembly Routines */
बाह्य uपूर्णांक64_t perf_rdr_shअगरt_in_W (uपूर्णांक32_t rdr_num, uपूर्णांक16_t width);
बाह्य uपूर्णांक64_t perf_rdr_shअगरt_in_U (uपूर्णांक32_t rdr_num, uपूर्णांक16_t width);
बाह्य व्योम perf_rdr_shअगरt_out_W (uपूर्णांक32_t rdr_num, uपूर्णांक64_t buffer);
बाह्य व्योम perf_rdr_shअगरt_out_U (uपूर्णांक32_t rdr_num, uपूर्णांक64_t buffer);
बाह्य व्योम perf_पूर्णांकrigue_enable_perf_counters (व्योम);
बाह्य व्योम perf_पूर्णांकrigue_disable_perf_counters (व्योम);

/******************************************************************************
 * Function Definitions
 *****************************************************************************/


/*
 * configure:
 *
 * Configure the cpu with a given data image.  First turn off the counters,
 * then करोwnload the image, then turn the counters back on.
 */
अटल पूर्णांक perf_config(uपूर्णांक32_t *image_ptr)
अणु
	दीर्घ error;
	uपूर्णांक32_t raddr[4];

	/* Stop the counters*/
	error = perf_stop_counters(raddr);
	अगर (error != 0) अणु
		prपूर्णांकk("perf_config: perf_stop_counters = %ld\n", error);
		वापस -EINVAL;
	पूर्ण

prपूर्णांकk("Preparing to write image\n");
	/* Write the image to the chip */
	error = perf_ग_लिखो_image((uपूर्णांक64_t *)image_ptr);
	अगर (error != 0) अणु
		prपूर्णांकk("perf_config: DOWNLOAD = %ld\n", error);
		वापस -EINVAL;
	पूर्ण

prपूर्णांकk("Preparing to start counters\n");

	/* Start the counters */
	perf_start_counters();

	वापस माप(uपूर्णांक32_t);
पूर्ण

/*
 * Open the device and initialize all of its memory.  The device is only
 * खोलोed once, but can be "queried" by multiple processes that know its
 * file descriptor.
 */
अटल पूर्णांक perf_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&perf_lock);
	अगर (perf_enabled) अणु
		spin_unlock(&perf_lock);
		वापस -EBUSY;
	पूर्ण
	perf_enabled = 1;
 	spin_unlock(&perf_lock);

	वापस 0;
पूर्ण

/*
 * Close the device.
 */
अटल पूर्णांक perf_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	spin_lock(&perf_lock);
	perf_enabled = 0;
	spin_unlock(&perf_lock);

	वापस 0;
पूर्ण

/*
 * Read करोes nothing क्रम this driver
 */
अटल sमाप_प्रकार perf_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस 0;
पूर्ण

/*
 * ग_लिखो:
 *
 * This routine करोwnloads the image to the chip.  It must be
 * called on the processor that the करोwnload should happen
 * on.
 */
अटल sमाप_प्रकार perf_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
	माप_प्रकार count, loff_t *ppos)
अणु
	माप_प्रकार image_size;
	uपूर्णांक32_t image_type;
	uपूर्णांक32_t पूर्णांकerface_type;
	uपूर्णांक32_t test;

	अगर (perf_processor_पूर्णांकerface == ONYX_INTF)
		image_size = PCXU_IMAGE_SIZE;
	अन्यथा अगर (perf_processor_पूर्णांकerface == CUDA_INTF)
		image_size = PCXW_IMAGE_SIZE;
	अन्यथा
		वापस -EFAULT;

	अगर (!perfmon_capable())
		वापस -EACCES;

	अगर (count != माप(uपूर्णांक32_t))
		वापस -EIO;

	अगर (copy_from_user(&image_type, buf, माप(uपूर्णांक32_t)))
		वापस -EFAULT;

	/* Get the पूर्णांकerface type and test type */
   	पूर्णांकerface_type = (image_type >> 16) & 0xffff;
	test           = (image_type & 0xffff);

	/* Make sure everything makes sense */

	/* First check the machine type is correct क्रम
	   the requested image */
	अगर (((perf_processor_पूर्णांकerface == CUDA_INTF) &&
			(पूर्णांकerface_type != CUDA_INTF)) ||
		((perf_processor_पूर्णांकerface == ONYX_INTF) &&
			(पूर्णांकerface_type != ONYX_INTF)))
		वापस -EINVAL;

	/* Next check to make sure the requested image
	   is valid */
	अगर (((पूर्णांकerface_type == CUDA_INTF) &&
		       (test >= MAX_CUDA_IMAGES)) ||
	    ((पूर्णांकerface_type == ONYX_INTF) &&
		       (test >= MAX_ONYX_IMAGES)))
		वापस -EINVAL;

	/* Copy the image पूर्णांकo the processor */
	अगर (पूर्णांकerface_type == CUDA_INTF)
		वापस perf_config(cuda_images[test]);
	अन्यथा
		वापस perf_config(onyx_images[test]);

	वापस count;
पूर्ण

/*
 * Patch the images that need to know the IVA addresses.
 */
अटल व्योम perf_patch_images(व्योम)
अणु
#अगर 0 /* FIXME!! */
/*
 * NOTE:  this routine is VERY specअगरic to the current TLB image.
 * If the image is changed, this routine might also need to be changed.
 */
	बाह्य व्योम $i_itlb_miss_2_0();
	बाह्य व्योम $i_dtlb_miss_2_0();
	बाह्य व्योम PA2_0_iva();

	/*
	 * We can only use the lower 32-bits, the upper 32-bits should be 0
	 * anyway given this is in the kernel
	 */
	uपूर्णांक32_t itlb_addr  = (uपूर्णांक32_t)&($i_itlb_miss_2_0);
	uपूर्णांक32_t dtlb_addr  = (uपूर्णांक32_t)&($i_dtlb_miss_2_0);
	uपूर्णांक32_t IVAaddress = (uपूर्णांक32_t)&PA2_0_iva;

	अगर (perf_processor_पूर्णांकerface == ONYX_INTF) अणु
		/* clear last 2 bytes */
		onyx_images[TLBMISS][15] &= 0xffffff00;
		/* set 2 bytes */
		onyx_images[TLBMISS][15] |= (0x000000ff&((dtlb_addr) >> 24));
		onyx_images[TLBMISS][16] = (dtlb_addr << 8)&0xffffff00;
		onyx_images[TLBMISS][17] = itlb_addr;

		/* clear last 2 bytes */
		onyx_images[TLBHANDMISS][15] &= 0xffffff00;
		/* set 2 bytes */
		onyx_images[TLBHANDMISS][15] |= (0x000000ff&((dtlb_addr) >> 24));
		onyx_images[TLBHANDMISS][16] = (dtlb_addr << 8)&0xffffff00;
		onyx_images[TLBHANDMISS][17] = itlb_addr;

		/* clear last 2 bytes */
		onyx_images[BIG_CPI][15] &= 0xffffff00;
		/* set 2 bytes */
		onyx_images[BIG_CPI][15] |= (0x000000ff&((dtlb_addr) >> 24));
		onyx_images[BIG_CPI][16] = (dtlb_addr << 8)&0xffffff00;
		onyx_images[BIG_CPI][17] = itlb_addr;

	    onyx_images[PANIC][15] &= 0xffffff00;  /* clear last 2 bytes */
	 	onyx_images[PANIC][15] |= (0x000000ff&((IVAaddress) >> 24)); /* set 2 bytes */
		onyx_images[PANIC][16] = (IVAaddress << 8)&0xffffff00;


	पूर्ण अन्यथा अगर (perf_processor_पूर्णांकerface == CUDA_INTF) अणु
		/* Cuda पूर्णांकerface */
		cuda_images[TLBMISS][16] =
			(cuda_images[TLBMISS][16]&0xffff0000) |
			((dtlb_addr >> 8)&0x0000ffff);
		cuda_images[TLBMISS][17] =
			((dtlb_addr << 24)&0xff000000) | ((itlb_addr >> 16)&0x000000ff);
		cuda_images[TLBMISS][18] = (itlb_addr << 16)&0xffff0000;

		cuda_images[TLBHANDMISS][16] =
			(cuda_images[TLBHANDMISS][16]&0xffff0000) |
			((dtlb_addr >> 8)&0x0000ffff);
		cuda_images[TLBHANDMISS][17] =
			((dtlb_addr << 24)&0xff000000) | ((itlb_addr >> 16)&0x000000ff);
		cuda_images[TLBHANDMISS][18] = (itlb_addr << 16)&0xffff0000;

		cuda_images[BIG_CPI][16] =
			(cuda_images[BIG_CPI][16]&0xffff0000) |
			((dtlb_addr >> 8)&0x0000ffff);
		cuda_images[BIG_CPI][17] =
			((dtlb_addr << 24)&0xff000000) | ((itlb_addr >> 16)&0x000000ff);
		cuda_images[BIG_CPI][18] = (itlb_addr << 16)&0xffff0000;
	पूर्ण अन्यथा अणु
		/* Unknown type */
	पूर्ण
#पूर्ण_अगर
पूर्ण


/*
 * ioctl routine
 * All routines effect the processor that they are executed on.  Thus you
 * must be running on the processor that you wish to change.
 */

अटल दीर्घ perf_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ error_start;
	uपूर्णांक32_t raddr[4];
	पूर्णांक error = 0;

	चयन (cmd) अणु

	    हाल PA_PERF_ON:
			/* Start the counters */
			perf_start_counters();
			अवरोध;

	    हाल PA_PERF_OFF:
			error_start = perf_stop_counters(raddr);
			अगर (error_start != 0) अणु
				prपूर्णांकk(KERN_ERR "perf_off: perf_stop_counters = %ld\n", error_start);
				error = -EFAULT;
				अवरोध;
			पूर्ण

			/* copy out the Counters */
			अगर (copy_to_user((व्योम __user *)arg, raddr,
					माप (raddr)) != 0) अणु
				error =  -EFAULT;
				अवरोध;
			पूर्ण
			अवरोध;

	    हाल PA_PERF_VERSION:
  	  		/* Return the version # */
			error = put_user(PERF_VERSION, (पूर्णांक *)arg);
			अवरोध;

	    शेष:
  	 		error = -ENOTTY;
	पूर्ण

	वापस error;
पूर्ण

अटल स्थिर काष्ठा file_operations perf_fops = अणु
	.llseek = no_llseek,
	.पढ़ो = perf_पढ़ो,
	.ग_लिखो = perf_ग_लिखो,
	.unlocked_ioctl = perf_ioctl,
	.compat_ioctl = perf_ioctl,
	.खोलो = perf_खोलो,
	.release = perf_release
पूर्ण;

अटल काष्ठा miscdevice perf_dev = अणु
	MISC_DYNAMIC_MINOR,
	PA_PERF_DEV,
	&perf_fops
पूर्ण;

/*
 * Initialize the module
 */
अटल पूर्णांक __init perf_init(व्योम)
अणु
	पूर्णांक ret;

	/* Determine correct processor पूर्णांकerface to use */
	biपंचांगask_array = perf_biपंचांगasks;

	अगर (boot_cpu_data.cpu_type == pcxu ||
	    boot_cpu_data.cpu_type == pcxu_) अणु
		perf_processor_पूर्णांकerface = ONYX_INTF;
	पूर्ण अन्यथा अगर (boot_cpu_data.cpu_type == pcxw ||
		 boot_cpu_data.cpu_type == pcxw_ ||
		 boot_cpu_data.cpu_type == pcxw2 ||
		 boot_cpu_data.cpu_type == mako ||
		 boot_cpu_data.cpu_type == mako2) अणु
		perf_processor_पूर्णांकerface = CUDA_INTF;
		अगर (boot_cpu_data.cpu_type == pcxw2 ||
		    boot_cpu_data.cpu_type == mako ||
		    boot_cpu_data.cpu_type == mako2)
			biपंचांगask_array = perf_biपंचांगasks_piranha;
	पूर्ण अन्यथा अणु
		perf_processor_पूर्णांकerface = UNKNOWN_INTF;
		prपूर्णांकk("Performance monitoring counters not supported on this processor\n");
		वापस -ENODEV;
	पूर्ण

	ret = misc_रेजिस्टर(&perf_dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Performance monitoring counters: "
			"cannot register misc device.\n");
		वापस ret;
	पूर्ण

	/* Patch the images to match the प्रणाली */
    	perf_patch_images();

	/* TODO: this only lets us access the first cpu.. what to करो क्रम SMP? */
	cpu_device = per_cpu(cpu_data, 0).dev;
	prपूर्णांकk("Performance monitoring counters enabled for %s\n",
		per_cpu(cpu_data, 0).dev->name);

	वापस 0;
पूर्ण
device_initcall(perf_init);

/*
 * perf_start_counters(व्योम)
 *
 * Start the counters.
 */
अटल व्योम perf_start_counters(व्योम)
अणु
	/* Enable perक्रमmance monitor counters */
	perf_पूर्णांकrigue_enable_perf_counters();
पूर्ण

/*
 * perf_stop_counters
 *
 * Stop the perक्रमmance counters and save counts
 * in a per_processor array.
 */
अटल पूर्णांक perf_stop_counters(uपूर्णांक32_t *raddr)
अणु
	uपूर्णांक64_t userbuf[MAX_RDR_WORDS];

	/* Disable perक्रमmance counters */
	perf_पूर्णांकrigue_disable_perf_counters();

	अगर (perf_processor_पूर्णांकerface == ONYX_INTF) अणु
		uपूर्णांक64_t पंचांगp64;
		/*
		 * Read the counters
		 */
		अगर (!perf_rdr_पढ़ो_ubuf(16, userbuf))
			वापस -13;

		/* Counter0 is bits 1398 to 1429 */
		पंचांगp64 =  (userbuf[21] << 22) & 0x00000000ffc00000;
		पंचांगp64 |= (userbuf[22] >> 42) & 0x00000000003fffff;
		/* OR sticky0 (bit 1430) to counter0 bit 32 */
		पंचांगp64 |= (userbuf[22] >> 10) & 0x0000000080000000;
		raddr[0] = (uपूर्णांक32_t)पंचांगp64;

		/* Counter1 is bits 1431 to 1462 */
		पंचांगp64 =  (userbuf[22] >> 9) & 0x00000000ffffffff;
		/* OR sticky1 (bit 1463) to counter1 bit 32 */
		पंचांगp64 |= (userbuf[22] << 23) & 0x0000000080000000;
		raddr[1] = (uपूर्णांक32_t)पंचांगp64;

		/* Counter2 is bits 1464 to 1495 */
		पंचांगp64 =  (userbuf[22] << 24) & 0x00000000ff000000;
		पंचांगp64 |= (userbuf[23] >> 40) & 0x0000000000ffffff;
		/* OR sticky2 (bit 1496) to counter2 bit 32 */
		पंचांगp64 |= (userbuf[23] >> 8) & 0x0000000080000000;
		raddr[2] = (uपूर्णांक32_t)पंचांगp64;

		/* Counter3 is bits 1497 to 1528 */
		पंचांगp64 =  (userbuf[23] >> 7) & 0x00000000ffffffff;
		/* OR sticky3 (bit 1529) to counter3 bit 32 */
		पंचांगp64 |= (userbuf[23] << 25) & 0x0000000080000000;
		raddr[3] = (uपूर्णांक32_t)पंचांगp64;

		/*
		 * Zero out the counters
		 */

		/*
		 * The counters and sticky-bits comprise the last 132 bits
		 * (1398 - 1529) of RDR16 on a U chip.  We'll zero these
		 * out the easy way: zero out last 10 bits of dword 21,
		 * all of dword 22 and 58 bits (plus 6 करोn't care bits) of
		 * dword 23.
		 */
		userbuf[21] &= 0xfffffffffffffc00ul;	/* 0 to last 10 bits */
		userbuf[22] = 0;
		userbuf[23] = 0;

		/*
		 * Write back the zeroed bytes + the image given
		 * the पढ़ो was deकाष्ठाive.
		 */
		perf_rdr_ग_लिखो(16, userbuf);
	पूर्ण अन्यथा अणु

		/*
		 * Read RDR-15 which contains the counters and sticky bits
		 */
		अगर (!perf_rdr_पढ़ो_ubuf(15, userbuf)) अणु
			वापस -13;
		पूर्ण

		/*
		 * Clear out the counters
		 */
		perf_rdr_clear(15);

		/*
		 * Copy the counters 
		 */
		raddr[0] = (uपूर्णांक32_t)((userbuf[0] >> 32) & 0x00000000ffffffffUL);
		raddr[1] = (uपूर्णांक32_t)(userbuf[0] & 0x00000000ffffffffUL);
		raddr[2] = (uपूर्णांक32_t)((userbuf[1] >> 32) & 0x00000000ffffffffUL);
		raddr[3] = (uपूर्णांक32_t)(userbuf[1] & 0x00000000ffffffffUL);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * perf_rdr_get_entry
 *
 * Retrieve a poपूर्णांकer to the description of what this
 * RDR contains.
 */
अटल स्थिर काष्ठा rdr_tbl_ent * perf_rdr_get_entry(uपूर्णांक32_t rdr_num)
अणु
	अगर (perf_processor_पूर्णांकerface == ONYX_INTF) अणु
		वापस &perf_rdr_tbl_U[rdr_num];
	पूर्ण अन्यथा अणु
		वापस &perf_rdr_tbl_W[rdr_num];
	पूर्ण
पूर्ण

/*
 * perf_rdr_पढ़ो_ubuf
 *
 * Read the RDR value पूर्णांकo the buffer specअगरied.
 */
अटल पूर्णांक perf_rdr_पढ़ो_ubuf(uपूर्णांक32_t	rdr_num, uपूर्णांक64_t *buffer)
अणु
	uपूर्णांक64_t	data, data_mask = 0;
	uपूर्णांक32_t	width, xbits, i;
	स्थिर काष्ठा rdr_tbl_ent *tentry;

	tentry = perf_rdr_get_entry(rdr_num);
	अगर ((width = tentry->width) == 0)
		वापस 0;

	/* Clear out buffer */
	i = tentry->num_words;
	जबतक (i--) अणु
		buffer[i] = 0;
	पूर्ण

	/* Check क्रम bits an even number of 64 */
	अगर ((xbits = width & 0x03f) != 0) अणु
		data_mask = 1;
		data_mask <<= (64 - xbits);
		data_mask--;
	पूर्ण

	/* Grab all of the data */
	i = tentry->num_words;
	जबतक (i--) अणु

		अगर (perf_processor_पूर्णांकerface == ONYX_INTF) अणु
			data = perf_rdr_shअगरt_in_U(rdr_num, width);
		पूर्ण अन्यथा अणु
			data = perf_rdr_shअगरt_in_W(rdr_num, width);
		पूर्ण
		अगर (xbits) अणु
			buffer[i] |= (data << (64 - xbits));
			अगर (i) अणु
				buffer[i-1] |= ((data >> xbits) & data_mask);
			पूर्ण
		पूर्ण अन्यथा अणु
			buffer[i] = data;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/*
 * perf_rdr_clear
 *
 * Zero out the given RDR रेजिस्टर
 */
अटल पूर्णांक perf_rdr_clear(uपूर्णांक32_t	rdr_num)
अणु
	स्थिर काष्ठा rdr_tbl_ent *tentry;
	पूर्णांक32_t		i;

	tentry = perf_rdr_get_entry(rdr_num);

	अगर (tentry->width == 0) अणु
		वापस -1;
	पूर्ण

	i = tentry->num_words;
	जबतक (i--) अणु
		अगर (perf_processor_पूर्णांकerface == ONYX_INTF) अणु
			perf_rdr_shअगरt_out_U(rdr_num, 0UL);
		पूर्ण अन्यथा अणु
			perf_rdr_shअगरt_out_W(rdr_num, 0UL);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/*
 * perf_ग_लिखो_image
 *
 * Write the given image out to the processor
 */
अटल पूर्णांक perf_ग_लिखो_image(uपूर्णांक64_t *memaddr)
अणु
	uपूर्णांक64_t buffer[MAX_RDR_WORDS];
	uपूर्णांक64_t *bptr;
	uपूर्णांक32_t dwords;
	स्थिर uपूर्णांक32_t *पूर्णांकrigue_rdr;
	स्थिर uपूर्णांक64_t *पूर्णांकrigue_biपंचांगask;
	uपूर्णांक64_t पंचांगp64;
	व्योम __iomem *runway;
	स्थिर काष्ठा rdr_tbl_ent *tentry;
	पूर्णांक i;

	/* Clear out counters */
	अगर (perf_processor_पूर्णांकerface == ONYX_INTF) अणु

		perf_rdr_clear(16);

		/* Toggle perक्रमmance monitor */
		perf_पूर्णांकrigue_enable_perf_counters();
		perf_पूर्णांकrigue_disable_perf_counters();

		पूर्णांकrigue_rdr = perf_rdrs_U;
	पूर्ण अन्यथा अणु
		perf_rdr_clear(15);
		पूर्णांकrigue_rdr = perf_rdrs_W;
	पूर्ण

	/* Write all RDRs */
	जबतक (*पूर्णांकrigue_rdr != -1) अणु
		tentry = perf_rdr_get_entry(*पूर्णांकrigue_rdr);
		perf_rdr_पढ़ो_ubuf(*पूर्णांकrigue_rdr, buffer);
		bptr   = &buffer[0];
		dwords = tentry->num_words;
		अगर (tentry->ग_लिखो_control) अणु
			पूर्णांकrigue_biपंचांगask = &biपंचांगask_array[tentry->ग_लिखो_control >> 3];
			जबतक (dwords--) अणु
				पंचांगp64 = *पूर्णांकrigue_biपंचांगask & *memaddr++;
				पंचांगp64 |= (~(*पूर्णांकrigue_biपंचांगask++)) & *bptr;
				*bptr++ = पंचांगp64;
			पूर्ण
		पूर्ण अन्यथा अणु
			जबतक (dwords--) अणु
				*bptr++ = *memaddr++;
			पूर्ण
		पूर्ण

		perf_rdr_ग_लिखो(*पूर्णांकrigue_rdr, buffer);
		पूर्णांकrigue_rdr++;
	पूर्ण

	/*
	 * Now copy out the Runway stuff which is not in RDRs
	 */

	अगर (cpu_device == शून्य)
	अणु
		prपूर्णांकk(KERN_ERR "write_image: cpu_device not yet initialized!\n");
		वापस -1;
	पूर्ण

	runway = ioremap(cpu_device->hpa.start, 4096);
	अगर (!runway) अणु
		pr_err("perf_write_image: ioremap failed!\n");
		वापस -ENOMEM;
	पूर्ण

	/* Merge पूर्णांकrigue bits पूर्णांकo Runway STATUS 0 */
	पंचांगp64 = __raw_पढ़ोq(runway + RUNWAY_STATUS) & 0xffecfffffffffffful;
	__raw_ग_लिखोq(पंचांगp64 | (*memaddr++ & 0x0013000000000000ul),
		     runway + RUNWAY_STATUS);

	/* Write RUNWAY DEBUG रेजिस्टरs */
	क्रम (i = 0; i < 8; i++) अणु
		__raw_ग_लिखोq(*memaddr++, runway + RUNWAY_DEBUG);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * perf_rdr_ग_लिखो
 *
 * Write the given RDR रेजिस्टर with the contents
 * of the given buffer.
 */
अटल व्योम perf_rdr_ग_लिखो(uपूर्णांक32_t rdr_num, uपूर्णांक64_t *buffer)
अणु
	स्थिर काष्ठा rdr_tbl_ent *tentry;
	पूर्णांक32_t		i;

prपूर्णांकk("perf_rdr_write\n");
	tentry = perf_rdr_get_entry(rdr_num);
	अगर (tentry->width == 0) अणु वापस; पूर्ण

	i = tentry->num_words;
	जबतक (i--) अणु
		अगर (perf_processor_पूर्णांकerface == ONYX_INTF) अणु
			perf_rdr_shअगरt_out_U(rdr_num, buffer[i]);
		पूर्ण अन्यथा अणु
			perf_rdr_shअगरt_out_W(rdr_num, buffer[i]);
		पूर्ण
	पूर्ण
prपूर्णांकk("perf_rdr_write done\n");
पूर्ण
