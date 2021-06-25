<शैली गुरु>
/*
 * dump_psb. (c) 2004, Dave Jones, Red Hat Inc.
 * Licensed under the GPL v2.
 */

#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#घोषणा _GNU_SOURCE
#समावेश <getopt.h>

#समावेश <sys/mman.h>

#घोषणा LEN (0x100000 - 0xc0000)
#घोषणा OFFSET (0xc0000)

#अगर_अघोषित __packed
#घोषणा __packed __attribute((packed))
#पूर्ण_अगर

अटल दीर्घ relevant;

अटल स्थिर पूर्णांक fid_to_mult[32] = अणु
	110, 115, 120, 125, 50, 55, 60, 65,
	70, 75, 80, 85, 90, 95, 100, 105,
	30, 190, 40, 200, 130, 135, 140, 210,
	150, 225, 160, 165, 170, 180, -1, -1,
पूर्ण;

अटल स्थिर पूर्णांक vid_to_voltage[32] = अणु
	2000, 1950, 1900, 1850, 1800, 1750, 1700, 1650,
	1600, 1550, 1500, 1450, 1400, 1350, 1300, 0,
	1275, 1250, 1225, 1200, 1175, 1150, 1125, 1100,
	1075, 1050, 1024, 1000, 975, 950, 925, 0,
पूर्ण;

काष्ठा psb_header अणु
	अक्षर signature[10];
	u_अक्षर version;
	u_अक्षर flags;
	u_लघु settlingसमय;
	u_अक्षर res1;
	u_अक्षर numpst;
पूर्ण __packed;

काष्ठा pst_header अणु
	u_पूर्णांक32_t cpuid;
	u_अक्षर fsb;
	u_अक्षर maxfid;
	u_अक्षर startvid;
	u_अक्षर numpstates;
पूर्ण __packed;

अटल u_पूर्णांक fsb;
अटल u_पूर्णांक sgtc;

अटल पूर्णांक
decode_pst(अक्षर *p, पूर्णांक npstates)
अणु
	पूर्णांक i;
	पूर्णांक freq, fid, vid;

	क्रम (i = 0; i < npstates; ++i) अणु
		fid = *p++;
		vid = *p++;
		freq = 100 * fid_to_mult[fid] * fsb;

		म_लिखो("   %2d %8dkHz  FID %02x (%2d.%01d)  VID %02x (%4dmV)\n",
		       i,
		       freq,
		       fid, fid_to_mult[fid]/10, fid_to_mult[fid]%10,
		       vid, vid_to_voltage[vid]);
	पूर्ण

	वापस 0;
पूर्ण

अटल
व्योम decode_psb(अक्षर *p, पूर्णांक numpst)
अणु
	पूर्णांक i;
	काष्ठा psb_header *psb;
	काष्ठा pst_header *pst;

	psb = (काष्ठा psb_header*) p;

	अगर (psb->version != 0x12)
		वापस;

	म_लिखो("PSB version: %hhx flags: %hhx settling time %hhuus res1 %hhx num pst %hhu\n",
			psb->version,
			psb->flags,
			psb->settlingसमय,
			psb->res1,
			psb->numpst);
	sgtc = psb->settlingसमय * 100;

	अगर (sgtc < 10000)
		sgtc = 10000;

	p = ((अक्षर *) psb) + माप(काष्ठा psb_header);

	अगर (numpst < 0)
		numpst = psb->numpst;
	अन्यथा
		म_लिखो("Overriding number of pst :%d\n", numpst);

	क्रम (i = 0; i < numpst; i++) अणु
		pst = (काष्ठा pst_header*) p;

		अगर (relevant != 0) अणु
			अगर (relevant!= pst->cpuid)
				जाओ next_one;
		पूर्ण

		म_लिखो("  PST %d  cpuid %.3x fsb %hhu mfid %hhx svid %hhx numberstates %hhu\n",
				i+1,
				pst->cpuid,
				pst->fsb,
				pst->maxfid,
				pst->startvid,
				pst->numpstates);

		fsb = pst->fsb;
		decode_pst(p + माप(काष्ठा pst_header), pst->numpstates);

next_one:
		p += माप(काष्ठा pst_header) + 2*pst->numpstates;
	पूर्ण

पूर्ण

अटल काष्ठा option info_opts[] = अणु
     अणु"numpst", no_argument, शून्य, 'n'पूर्ण,
पूर्ण;

व्योम prपूर्णांक_help(व्योम)
अणु
	म_लिखो ("Usage: dump_psb [options]\n");
	म_लिखो ("Options:\n");
	म_लिखो ("  -n, --numpst     Set number of PST tables to scan\n");
	म_लिखो ("  -r, --relevant   Only display PSTs relevant to cpuid N\n");
पूर्ण

पूर्णांक
मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक fd;
	पूर्णांक numpst=-1;
	पूर्णांक ret=0, cont=1;
	अक्षर *mem = शून्य;
	अक्षर *p;

	करो अणु
		ret = getopt_दीर्घ(argc, argv, "hr:n:", info_opts, शून्य);
		चयन (ret)अणु
		हाल '?':
		हाल 'h':
			prपूर्णांक_help();
			cont = 0;
			अवरोध;
		हाल 'r':
			relevant = म_से_दीर्घ(optarg, शून्य, 16);
			अवरोध;
		हाल 'n':
			numpst = म_से_दीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल -1:
			cont = 0;
			अवरोध;
		पूर्ण

	पूर्ण जबतक(cont);

	fd = खोलो("/dev/mem", O_RDONLY);
	अगर (fd < 0) अणु
		म_लिखो ("Couldn't open /dev/mem. Are you root?\n");
		निकास(1);
	पूर्ण

	mem = mmap(mem, 0x100000 - 0xc0000, PROT_READ, MAP_SHARED, fd, 0xc0000);
	बंद(fd);

	क्रम (p = mem; p - mem < LEN; p+=16) अणु
		अगर (स_भेद(p, "AMDK7PNOW!", 10) == 0) अणु
			decode_psb(p, numpst);
			अवरोध;
		पूर्ण
	पूर्ण

	munmap(mem, LEN);
	वापस 0;
पूर्ण
