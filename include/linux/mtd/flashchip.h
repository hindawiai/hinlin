<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright तऊ 2000      Red Hat UK Limited
 * Copyright तऊ 2000-2010 David Woodhouse <dwmw2@infradead.org>
 */

#अगर_अघोषित __MTD_FLASHCHIP_H__
#घोषणा __MTD_FLASHCHIP_H__

/* For spinlocks. sched.h includes spinlock.h from whichever directory it
 * happens to be in - so we करोn't have to care whether we're on 2.2, which
 * has यंत्र/spinlock.h, or 2.4, which has linux/spinlock.h
 */
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>

प्रकार क्रमागत अणु
	FL_READY,
	FL_STATUS,
	FL_CFI_QUERY,
	FL_JEDEC_QUERY,
	FL_ERASING,
	FL_ERASE_SUSPENDING,
	FL_ERASE_SUSPENDED,
	FL_WRITING,
	FL_WRITING_TO_BUFFER,
	FL_OTP_WRITE,
	FL_WRITE_SUSPENDING,
	FL_WRITE_SUSPENDED,
	FL_PM_SUSPENDED,
	FL_SYNCING,
	FL_UNLOADING,
	FL_LOCKING,
	FL_UNLOCKING,
	FL_POINT,
	FL_XIP_WHILE_ERASING,
	FL_XIP_WHILE_WRITING,
	FL_SHUTDOWN,
	/* These 2 come from nand_state_t, which has been unअगरied here */
	FL_READING,
	FL_CACHEDPRG,
	/* These 4 come from onenand_state_t, which has been unअगरied here */
	FL_RESETTING,
	FL_OTPING,
	FL_PREPARING_ERASE,
	FL_VERIFYING_ERASE,

	FL_UNKNOWN
पूर्ण flstate_t;



/* NOTE: confusingly, this can be used to refer to more than one chip at a समय,
   अगर they're पूर्णांकerleaved.  This can even refer to inभागidual partitions on
   the same physical chip when present. */

काष्ठा flchip अणु
	अचिन्हित दीर्घ start; /* Offset within the map */
	//	अचिन्हित दीर्घ len;
	/* We omit len क्रम now, because when we group them together
	   we insist that they're all of the same size, and the chip size
	   is held in the next level up. If we get more versatile later,
	   it'll make it a damn sight harder to find which chip we want from
	   a given offset, and we'll want to add the per-chip length field
	   back in.
	*/
	पूर्णांक ref_poपूर्णांक_counter;
	flstate_t state;
	flstate_t oldstate;

	अचिन्हित पूर्णांक ग_लिखो_suspended:1;
	अचिन्हित पूर्णांक erase_suspended:1;
	अचिन्हित दीर्घ in_progress_block_addr;
	अचिन्हित दीर्घ in_progress_block_mask;

	काष्ठा mutex mutex;
	रुको_queue_head_t wq; /* Wait on here when we're रुकोing क्रम the chip
			     to be पढ़ोy */
	पूर्णांक word_ग_लिखो_समय;
	पूर्णांक buffer_ग_लिखो_समय;
	पूर्णांक erase_समय;

	पूर्णांक word_ग_लिखो_समय_max;
	पूर्णांक buffer_ग_लिखो_समय_max;
	पूर्णांक erase_समय_max;

	व्योम *priv;
पूर्ण;

/* This is used to handle contention on ग_लिखो/erase operations
   between partitions of the same physical chip. */
काष्ठा flchip_shared अणु
	काष्ठा mutex lock;
	काष्ठा flchip *writing;
	काष्ठा flchip *erasing;
पूर्ण;


#पूर्ण_अगर /* __MTD_FLASHCHIP_H__ */
