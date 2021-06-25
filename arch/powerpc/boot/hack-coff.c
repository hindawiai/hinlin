<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * hack-coff.c - hack the header of an xcoff file to fill in
 * a few fields needed by the Open Firmware xcoff loader on
 * Power Macs but not initialized by objcopy.
 *
 * Copyright (C) Paul Mackerras 1997.
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश "rs6000.h"

#घोषणा AOUT_MAGIC	0x010b

#घोषणा get_16be(x)	((((अचिन्हित अक्षर *)(x))[0] << 8) \
			 + ((अचिन्हित अक्षर *)(x))[1])
#घोषणा put_16be(x, v)	(((अचिन्हित अक्षर *)(x))[0] = (v) >> 8, \
			 ((अचिन्हित अक्षर *)(x))[1] = (v) & 0xff)
#घोषणा get_32be(x)	((((अचिन्हित अक्षर *)(x))[0] << 24) \
			 + (((अचिन्हित अक्षर *)(x))[1] << 16) \
			 + (((अचिन्हित अक्षर *)(x))[2] << 8) \
			 + ((अचिन्हित अक्षर *)(x))[3])

पूर्णांक
मुख्य(पूर्णांक ac, अक्षर **av)
अणु
    पूर्णांक fd;
    पूर्णांक i, nsect;
    पूर्णांक aoutsz;
    काष्ठा बाह्यal_filehdr fhdr;
    AOUTHDR aout;
    काष्ठा बाह्यal_scnhdr shdr;

    अगर (ac != 2) अणु
	ख_लिखो(मानक_त्रुटि, "Usage: hack-coff coff-file\n");
	निकास(1);
    पूर्ण
    अगर ((fd = खोलो(av[1], 2)) == -1) अणु
	लिखो_त्रुटि(av[2]);
	निकास(1);
    पूर्ण
    अगर (पढ़ो(fd, &fhdr, माप(fhdr)) != माप(fhdr))
	जाओ पढ़ोerr;
    i = get_16be(fhdr.f_magic);
    अगर (i != U802TOCMAGIC && i != U802WRMAGIC && i != U802ROMAGIC) अणु
	ख_लिखो(मानक_त्रुटि, "%s: not an xcoff file\n", av[1]);
	निकास(1);
    पूर्ण
    aoutsz = get_16be(fhdr.f_opthdr);
    अगर (पढ़ो(fd, &aout, aoutsz) != aoutsz)
	जाओ पढ़ोerr;
    nsect = get_16be(fhdr.f_nscns);
    क्रम (i = 0; i < nsect; ++i) अणु
	अगर (पढ़ो(fd, &shdr, माप(shdr)) != माप(shdr))
	    जाओ पढ़ोerr;
	अगर (म_भेद(shdr.s_name, ".text") == 0) अणु
	    put_16be(aout.o_snentry, i+1);
	    put_16be(aout.o_sntext, i+1);
	पूर्ण अन्यथा अगर (म_भेद(shdr.s_name, ".data") == 0) अणु
	    put_16be(aout.o_sndata, i+1);
	पूर्ण अन्यथा अगर (म_भेद(shdr.s_name, ".bss") == 0) अणु
	    put_16be(aout.o_snbss, i+1);
	पूर्ण
    पूर्ण
    put_16be(aout.magic, AOUT_MAGIC);
    अगर (lseek(fd, (दीर्घ) माप(काष्ठा बाह्यal_filehdr), 0) == -1
	|| ग_लिखो(fd, &aout, aoutsz) != aoutsz) अणु
	ख_लिखो(मानक_त्रुटि, "%s: write error\n", av[1]);
	निकास(1);
    पूर्ण
    बंद(fd);
    निकास(0);

पढ़ोerr:
    ख_लिखो(मानक_त्रुटि, "%s: read error or file too short\n", av[1]);
    निकास(1);
पूर्ण
