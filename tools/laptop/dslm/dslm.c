<शैली गुरु>
/*
 * dslm.c
 * Simple Disk Sleep Monitor
 *  by Bartek Kania
 * Licensed under the GPL
 */
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <समय.स>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <sys/ioctl.h>
#समावेश <linux/hdreg.h>

#अगर_घोषित DEBUG
#घोषणा D(x) x
#अन्यथा
#घोषणा D(x)
#पूर्ण_अगर

पूर्णांक endit = 0;

/* Check अगर the disk is in घातersave-mode
 * Most of the code is stolen from hdparm.
 * 1 = active, 0 = standby/sleep, -1 = unknown */
अटल पूर्णांक check_घातermode(पूर्णांक fd)
अणु
    अचिन्हित अक्षर args[4] = अणुWIN_CHECKPOWERMODE1,0,0,0पूर्ण;
    पूर्णांक state;

    अगर (ioctl(fd, HDIO_DRIVE_CMD, &args)
	&& (args[0] = WIN_CHECKPOWERMODE2) /* try again with 0x98 */
	&& ioctl(fd, HDIO_DRIVE_CMD, &args)) अणु
	अगर (त्रुटि_सं != EIO || args[0] != 0 || args[1] != 0) अणु
	    state = -1; /* "unknown"; */
	पूर्ण अन्यथा
	    state = 0; /* "sleeping"; */
    पूर्ण अन्यथा अणु
	state = (args[2] == 255) ? 1 : 0;
    पूर्ण
    D(म_लिखो(" drive state is:  %d\n", state));

    वापस state;
पूर्ण

अटल अक्षर *state_name(पूर्णांक i)
अणु
    अगर (i == -1) वापस "unknown";
    अगर (i == 0) वापस "sleeping";
    अगर (i == 1) वापस "active";

    वापस "internal error";
पूर्ण

अटल अक्षर *myस_समय(समय_प्रकार समय)
अणु
    अक्षर *ts = स_समय(&समय);
    ts[म_माप(ts) - 1] = 0;

    वापस ts;
पूर्ण

अटल व्योम measure(पूर्णांक fd)
अणु
    समय_प्रकार start_समय;
    पूर्णांक last_state;
    समय_प्रकार last_समय;
    पूर्णांक curr_state;
    समय_प्रकार curr_समय = 0;
    समय_प्रकार समय_dअगरf;
    समय_प्रकार active_समय = 0;
    समय_प्रकार sleep_समय = 0;
    समय_प्रकार unknown_समय = 0;
    समय_प्रकार total_समय = 0;
    पूर्णांक changes = 0;
    भग्न पंचांगp;

    म_लिखो("Starting measurements\n");

    last_state = check_घातermode(fd);
    start_समय = last_समय = समय(0);
    म_लिखो("  System is in state %s\n\n", state_name(last_state));

    जबतक(!endit) अणु
	sleep(1);
	curr_state = check_घातermode(fd);

	अगर (curr_state != last_state || endit) अणु
	    changes++;
	    curr_समय = समय(0);
	    समय_dअगरf = curr_समय - last_समय;

	    अगर (last_state == 1) active_समय += समय_dअगरf;
	    अन्यथा अगर (last_state == 0) sleep_समय += समय_dअगरf;
	    अन्यथा unknown_समय += समय_dअगरf;

	    last_state = curr_state;
	    last_समय = curr_समय;

	    म_लिखो("%s: State-change to %s\n", myस_समय(curr_समय),
		   state_name(curr_state));
	पूर्ण
    पूर्ण
    changes--; /* Compensate क्रम संक_विघ्न */

    total_समय = समय(0) - start_समय;
    म_लिखो("\nTotal running time:  %lus\n", curr_समय - start_समय);
    म_लिखो(" State changed %d times\n", changes);

    पंचांगp = (भग्न)sleep_समय / (भग्न)total_समय * 100;
    म_लिखो(" Time in sleep state:   %lus (%.2f%%)\n", sleep_समय, पंचांगp);
    पंचांगp = (भग्न)active_समय / (भग्न)total_समय * 100;
    म_लिखो(" Time in active state:  %lus (%.2f%%)\n", active_समय, पंचांगp);
    पंचांगp = (भग्न)unknown_समय / (भग्न)total_समय * 100;
    म_लिखो(" Time in unknown state: %lus (%.2f%%)\n", unknown_समय, पंचांगp);
पूर्ण

अटल व्योम ender(पूर्णांक s)
अणु
    endit = 1;
पूर्ण

अटल व्योम usage(व्योम)
अणु
    माला_दो("usage: dslm [-w <time>] <disk>");
    निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
    पूर्णांक fd;
    अक्षर *disk = 0;
    पूर्णांक settle_समय = 60;

    /* Parse the simple command-line */
    अगर (argc == 2)
	disk = argv[1];
    अन्यथा अगर (argc == 4) अणु
	settle_समय = म_से_प(argv[2]);
	disk = argv[3];
    पूर्ण अन्यथा
	usage();

    अगर (!(fd = खोलो(disk, O_RDONLY|O_NONBLOCK))) अणु
	म_लिखो("Can't open %s, because: %s\n", disk, म_त्रुटि(त्रुटि_सं));
	निकास(-1);
    पूर्ण

    अगर (settle_समय) अणु
	म_लिखो("Waiting %d seconds for the system to settle down to "
	       "'normal'\n", settle_समय);
	sleep(settle_समय);
    पूर्ण अन्यथा
	माला_दो("Not waiting for system to settle down");

    संकेत(संक_विघ्न, ender);

    measure(fd);

    बंद(fd);

    वापस 0;
पूर्ण
