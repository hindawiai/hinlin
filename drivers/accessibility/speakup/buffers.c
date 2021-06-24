<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/console.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#समावेश "speakup.h"
#समावेश "spk_priv.h"

#घोषणा SYNTH_BUF_SIZE 8192	/* currently 8K bytes */

अटल u16 synth_buffer[SYNTH_BUF_SIZE];	/* guess what this is क्रम! */
अटल u16 *buff_in = synth_buffer;
अटल u16 *buff_out = synth_buffer;
अटल u16 *buffer_end = synth_buffer + SYNTH_BUF_SIZE - 1;

/* These try to throttle applications by stopping the TTYs
 * Note: we need to make sure that we will restart them eventually, which is
 * usually not possible to करो from the notअगरiers. TODO: it should be possible
 * starting from linux 2.6.26.
 *
 * So we only stop when we know alive == 1 (अन्यथा we discard the data anyway),
 * and the alive synth will eventually call start_ttys from the thपढ़ो context.
 */
व्योम speakup_start_ttys(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		अगर (speakup_console[i] && speakup_console[i]->tty_stopped)
			जारी;
		अगर (vc_cons[i].d && vc_cons[i].d->port.tty)
			start_tty(vc_cons[i].d->port.tty);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(speakup_start_ttys);

अटल व्योम speakup_stop_ttys(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		अगर (vc_cons[i].d && vc_cons[i].d->port.tty)
			stop_tty(vc_cons[i].d->port.tty);
पूर्ण

अटल पूर्णांक synth_buffer_मुक्त(व्योम)
अणु
	पूर्णांक अक्षरs_मुक्त;

	अगर (buff_in >= buff_out)
		अक्षरs_मुक्त = SYNTH_BUF_SIZE - (buff_in - buff_out);
	अन्यथा
		अक्षरs_मुक्त = buff_out - buff_in;
	वापस अक्षरs_मुक्त;
पूर्ण

पूर्णांक synth_buffer_empty(व्योम)
अणु
	वापस (buff_in == buff_out);
पूर्ण
EXPORT_SYMBOL_GPL(synth_buffer_empty);

व्योम synth_buffer_add(u16 ch)
अणु
	अगर (!synth->alive) अणु
		/* This makes sure that we won't stop TTYs अगर there is no synth
		 * to restart them
		 */
		वापस;
	पूर्ण
	अगर (synth_buffer_मुक्त() <= 100) अणु
		synth_start();
		speakup_stop_ttys();
	पूर्ण
	अगर (synth_buffer_मुक्त() <= 1)
		वापस;
	*buff_in++ = ch;
	अगर (buff_in > buffer_end)
		buff_in = synth_buffer;
	/* We have written something to the speech synthesis, so we are not
	 * छोड़ोd any more.
	 */
	spk_छोड़ोd = false;
पूर्ण

u16 synth_buffer_अ_लो(व्योम)
अणु
	u16 ch;

	अगर (buff_out == buff_in)
		वापस 0;
	ch = *buff_out++;
	अगर (buff_out > buffer_end)
		buff_out = synth_buffer;
	वापस ch;
पूर्ण
EXPORT_SYMBOL_GPL(synth_buffer_अ_लो);

u16 synth_buffer_peek(व्योम)
अणु
	अगर (buff_out == buff_in)
		वापस 0;
	वापस *buff_out;
पूर्ण
EXPORT_SYMBOL_GPL(synth_buffer_peek);

व्योम synth_buffer_skip_nonlatin1(व्योम)
अणु
	जबतक (buff_out != buff_in) अणु
		अगर (*buff_out < 0x100)
			वापस;
		buff_out++;
		अगर (buff_out > buffer_end)
			buff_out = synth_buffer;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(synth_buffer_skip_nonlatin1);

व्योम synth_buffer_clear(व्योम)
अणु
	buff_in = synth_buffer;
	buff_out = synth_buffer;
पूर्ण
EXPORT_SYMBOL_GPL(synth_buffer_clear);
