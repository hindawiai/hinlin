<शैली गुरु>
/*
 * linux/arch/m68k/atari/atasound.c
 *
 * ++Geert: Moved almost all stuff to linux/drivers/sound/
 *
 * The author of atari_nosound, atari_mksound and atari_microwire_cmd is
 * unknown. (++roman: That's me... :-)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 * 1998-05-31 ++andreas: atari_mksound rewritten to always use the envelope,
 *			 no समयr, atari_nosound हटाओd.
 *
 */


#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/major.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/atariपूर्णांकs.h>


/*
 * stuff from the old atasound.c
 */

व्योम atari_microwire_cmd (पूर्णांक cmd)
अणु
	tt_microwire.mask = 0x7ff;
	tt_microwire.data = MW_LM1992_ADDR | cmd;

	/* Busy रुको क्रम data being completely sent :-( */
	जबतक( tt_microwire.mask != 0x7ff)
		;
पूर्ण
EXPORT_SYMBOL(atari_microwire_cmd);


/* PSG base frequency */
#घोषणा	PSG_FREQ	125000
/* PSG envelope base frequency बार 10 */
#घोषणा PSG_ENV_FREQ_10	78125

व्योम atari_mksound (अचिन्हित पूर्णांक hz, अचिन्हित पूर्णांक ticks)
अणु
	/* Generates sound of some frequency क्रम some number of घड़ी
	   ticks.  */
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक period;

	local_irq_save(flags);


	/* Disable generator A in mixer control.  */
	sound_ym.rd_data_reg_sel = 7;
	पंचांगp = sound_ym.rd_data_reg_sel;
	पंचांगp |= 011;
	sound_ym.wd_data = पंचांगp;

	अगर (hz) अणु
	    /* Convert from frequency value to PSG period value (base
	       frequency 125 kHz).  */

	    period = PSG_FREQ / hz;

	    अगर (period > 0xfff) period = 0xfff;

	/* Set generator A frequency to hz.  */
	sound_ym.rd_data_reg_sel = 0;
	sound_ym.wd_data = period & 0xff;
	sound_ym.rd_data_reg_sel = 1;
	sound_ym.wd_data = (period >> 8) & 0xf;
	अगर (ticks) अणु
		/* Set length of envelope (max 8 sec).  */
		पूर्णांक length = (ticks * PSG_ENV_FREQ_10) / HZ / 10;

		अगर (length > 0xffff) length = 0xffff;
		sound_ym.rd_data_reg_sel = 11;
		sound_ym.wd_data = length & 0xff;
		sound_ym.rd_data_reg_sel = 12;
		sound_ym.wd_data = length >> 8;
		/* Envelope क्रमm: max -> min single.  */
		sound_ym.rd_data_reg_sel = 13;
		sound_ym.wd_data = 0;
		/* Use envelope क्रम generator A.  */
		sound_ym.rd_data_reg_sel = 8;
		sound_ym.wd_data = 0x10;
	पूर्ण अन्यथा अणु
		/* Set generator A level to maximum, no envelope.  */
		sound_ym.rd_data_reg_sel = 8;
		sound_ym.wd_data = 15;
	पूर्ण
	/* Turn on generator A in mixer control.  */
	sound_ym.rd_data_reg_sel = 7;
	पंचांगp &= ~1;
	sound_ym.wd_data = पंचांगp;
	पूर्ण
	local_irq_restore(flags);
पूर्ण
