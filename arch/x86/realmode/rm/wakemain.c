<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "wakeup.h"
#समावेश "boot.h"

अटल व्योम udelay(पूर्णांक loops)
अणु
	जबतक (loops--)
		io_delay();	/* Approximately 1 us */
पूर्ण

अटल व्योम beep(अचिन्हित पूर्णांक hz)
अणु
	u8 enable;

	अगर (!hz) अणु
		enable = 0x00;		/* Turn off speaker */
	पूर्ण अन्यथा अणु
		u16 भाग = 1193181/hz;

		outb(0xb6, 0x43);	/* Ctr 2, squarewave, load, binary */
		io_delay();
		outb(भाग, 0x42);	/* LSB of counter */
		io_delay();
		outb(भाग >> 8, 0x42);	/* MSB of counter */
		io_delay();

		enable = 0x03;		/* Turn on speaker */
	पूर्ण
	inb(0x61);		/* Dummy पढ़ो of System Control Port B */
	io_delay();
	outb(enable, 0x61);	/* Enable समयr 2 output to speaker */
	io_delay();
पूर्ण

#घोषणा DOT_HZ		880
#घोषणा DASH_HZ		587
#घोषणा US_PER_DOT	125000

/* Okay, this is totally silly, but it's kind of fun. */
अटल व्योम send_morse(स्थिर अक्षर *pattern)
अणु
	अक्षर s;

	जबतक ((s = *pattern++)) अणु
		चयन (s) अणु
		हाल '.':
			beep(DOT_HZ);
			udelay(US_PER_DOT);
			beep(0);
			udelay(US_PER_DOT);
			अवरोध;
		हाल '-':
			beep(DASH_HZ);
			udelay(US_PER_DOT * 3);
			beep(0);
			udelay(US_PER_DOT);
			अवरोध;
		शेष:	/* Assume it's a space */
			udelay(US_PER_DOT * 3);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम मुख्य(व्योम)
अणु
	/* Kill machine अगर काष्ठाures are wrong */
	अगर (wakeup_header.real_magic != 0x12345678)
		जबतक (1)
			;

	अगर (wakeup_header.realmode_flags & 4)
		send_morse("...-");

	अगर (wakeup_header.realmode_flags & 1)
		यंत्र अस्थिर("lcallw   $0xc000,$3");

	अगर (wakeup_header.realmode_flags & 2) अणु
		/* Need to call BIOS */
		probe_cards(0);
		set_mode(wakeup_header.video_mode);
	पूर्ण
पूर्ण
