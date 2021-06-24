<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2004 Bruno Ducrot <ducrot@poupinou.org>
 *
 * Based on code found in
 * linux/arch/i386/kernel/cpu/cpufreq/घातernow-k8.c
 * and originally developed by Paul Devriendt
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>

#घोषणा MCPU 32

#घोषणा MSR_FIDVID_STATUS	0xc0010042

#घोषणा MSR_S_HI_CURRENT_VID	0x0000001f
#घोषणा MSR_S_LO_CURRENT_FID	0x0000003f

अटल पूर्णांक get_fidvid(uपूर्णांक32_t cpu, uपूर्णांक32_t *fid, uपूर्णांक32_t *vid)
अणु
	पूर्णांक err = 1;
	uपूर्णांक64_t msr = 0;
	पूर्णांक fd;
	अक्षर file[20];

	अगर (cpu > MCPU)
		जाओ out;

	प्र_लिखो(file, "/dev/cpu/%d/msr", cpu);

	fd = खोलो(file, O_RDONLY);
	अगर (fd < 0)
		जाओ out;
	lseek(fd, MSR_FIDVID_STATUS, प्रस्तुत_से);
	अगर (पढ़ो(fd, &msr, 8) != 8)
		जाओ err1;

	*fid = ((uपूर्णांक32_t )(msr & 0xffffffffull)) & MSR_S_LO_CURRENT_FID;
	*vid = ((uपूर्णांक32_t )(msr>>32 & 0xffffffffull)) & MSR_S_HI_CURRENT_VID;
	err = 0;
err1:
	बंद(fd);
out:
	वापस err;
पूर्ण


/* Return a frequency in MHz, given an input fid */
अटल uपूर्णांक32_t find_freq_from_fid(uपूर्णांक32_t fid)
अणु
	वापस 800 + (fid * 100);
पूर्ण

/* Return a voltage in miliVolts, given an input vid */
अटल uपूर्णांक32_t find_millivolts_from_vid(uपूर्णांक32_t vid)
अणु
	वापस 1550-vid*25;
पूर्ण

पूर्णांक मुख्य (पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक err;
	पूर्णांक cpu;
	uपूर्णांक32_t fid, vid;

	अगर (argc < 2)
		cpu = 0;
	अन्यथा
		cpu = म_से_अदीर्घ(argv[1], शून्य, 0);

	err = get_fidvid(cpu, &fid, &vid);

	अगर (err) अणु
		म_लिखो("can't get fid, vid from MSR\n");
		म_लिखो("Possible trouble: you don't run a powernow-k8 capable cpu\n");
		म_लिखो("or you are not root, or the msr driver is not present\n");
		निकास(1);
	पूर्ण

	
	म_लिखो("cpu %d currently at %d MHz and %d mV\n",
			cpu,
			find_freq_from_fid(fid),
			find_millivolts_from_vid(vid));
	
	वापस 0;
पूर्ण
