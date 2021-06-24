<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Reset a Jazz machine.
 *
 * We करोn't trust the firmware so we करो it the classic way by poking and
 * stabbing at the keyboard controller ...
 */
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/jazz.h>

#घोषणा KBD_STAT_IBF		0x02	/* Keyboard input buffer full */

अटल व्योम jazz_ग_लिखो_output(अचिन्हित अक्षर val)
अणु
	पूर्णांक status;

	करो अणु
		status = jazz_kh->command;
	पूर्ण जबतक (status & KBD_STAT_IBF);
	jazz_kh->data = val;
पूर्ण

अटल व्योम jazz_ग_लिखो_command(अचिन्हित अक्षर val)
अणु
	पूर्णांक status;

	करो अणु
		status = jazz_kh->command;
	पूर्ण जबतक (status & KBD_STAT_IBF);
	jazz_kh->command = val;
पूर्ण

अटल अचिन्हित अक्षर jazz_पढ़ो_status(व्योम)
अणु
	वापस jazz_kh->command;
पूर्ण

अटल अंतरभूत व्योम kb_रुको(व्योम)
अणु
	अचिन्हित दीर्घ start = jअगरfies;
	अचिन्हित दीर्घ समयout = start + HZ/2;

	करो अणु
		अगर (! (jazz_पढ़ो_status() & 0x02))
			वापस;
	पूर्ण जबतक (समय_beक्रमe_eq(jअगरfies, समयout));
पूर्ण

व्योम jazz_machine_restart(अक्षर *command)
अणु
	जबतक(1) अणु
		kb_रुको();
		jazz_ग_लिखो_command(0xd1);
		kb_रुको();
		jazz_ग_लिखो_output(0x00);
	पूर्ण
पूर्ण
